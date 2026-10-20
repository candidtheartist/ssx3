#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pick the decompiled functions the PC build can run as native code.

Run from the repository root after a full decomp build (it reads obj/ and
out/SLUS_207.72.map), with a Python that has pyelftools:

    python port/recomp/native/select_native.py

It writes port/recomp/native/native_functions.txt (the units to compile and the
functions to swap in) and native_symbols.txt (EE addresses for every symbol
those units leave undefined). Both are committed; the port build reads them and
needs no decomp build.

A function is picked when all of these hold:
  - it is matched C (not INCLUDE_ASM), and the host compiler builds its unit;
  - its EE code has no syscall, COP0, VU0, MMI or 64-bit memory/arith, no
    indirect call and no hardware register address: what it does to memory is
    then exactly what its C says, at 32 bits;
  - its arguments and result are ints, pointers or floats, at most 8 of each
    (the EE EABI passes them in a0-a3/t0-t3 and f12-f19); no long, long long,
    double or struct by value anywhere in it;
  - on the host it touches no data the unit defines (that copy would not be the
    game's): only extern data, which resolves to its EE address, the compiler's
    own constants and jump tables;
  - everything it calls is picked too, or is a C library function with the same
    behaviour. The recompiled code switches EE threads by unwinding the host
    stack, which would lose a native frame, so native code never calls back into
    recompiled code yet.
"""
import os
import re
import subprocess
import sys
from collections import defaultdict

from elftools.elf.elffile import ELFFile

ROOT = os.getcwd()
HERE = os.path.dirname(os.path.abspath(__file__))
OBJDUMP_EE = "mips-linux-gnu-objdump"
WORK = os.path.join(ROOT, "build", "native-select")

sys.path.insert(0, HERE)
from native_flags import HOST_CXXFLAGS  # noqa: E402

# EE library functions the host C library does the same job for. The decomp
# names some of them by address; native code is linked against these instead.
LIBC_ALIASES = {
    "strlen": "strlen",
    "strchr": "strchr",
    "strcmp": "strcmp",
    "strcpy": "strcpy",
    "strncpy": "strncpy",
    "strncmp": "strncmp",
    "memset": "memset",
    "func_0041605C": "memmove",  # newlib memcpy (forward copy)
}
# Symbols the host compiler itself may reference.
HOST_OK = {"_GLOBAL_OFFSET_TABLE_", "memcpy", "memset", "memmove"}

BAD_EE_OPS = {
    "syscall", "sync", "sync.l", "sync.p", "ei", "di", "eret", "mfc0", "mtc0", "cache",
    "dsll32", "dsrl32", "dsra32", "dsll", "dsrl", "dsra", "dsllv", "dsrlv", "dsrav", "dmult", "ddiv",
    "dadd", "dsub", "dsubu", "daddi", "daddiu", "lwu",
    "mult1", "div1", "divu1", "madd", "madd1", "maddu", "maddu1", "mflo1", "mfhi1", "mtlo1", "mthi1",
    "mfsa", "mtsa", "pmfhl", "pmthl", "qmfc2", "qmtc2", "lqc2", "sqc2", "cfc2", "ctc2", "jalr",
}


def run(cmd, **kw):
    return subprocess.run(cmd, check=True, capture_output=True, text=True, **kw).stdout


def ee_map():
    """EE symbol -> address, from the linked build's map."""
    addrs = {}
    for line in open(os.path.join(ROOT, "out", "SLUS_207.72.map")):
        m = re.match(r"^\s+0x([0-9a-f]{8})\s+([A-Za-z_][\w.$]*)\s*$", line)
        if m and not m.group(2).endswith(".NON_MATCHING"):
            addrs.setdefault(m.group(2), int(m.group(1), 16))
    return addrs


def ee_base(name):
    """gcc 2.95 mangles free functions as name__F<args>."""
    i = name.find("__F")
    return name[:i] if i > 0 else name


def units():
    out = []
    for line in open(os.path.join(ROOT, "build.ninja")):
        m = re.match(r"^build obj/(src/\S+\.cpp)\.o: ", line)
        if m:
            out.append(m.group(1))
    return sorted(set(out))


def asm_names(src):
    return set(re.findall(r"INCLUDE_ASM\(\s*\"[^\"]*\"\s*,\s*(\w+)\s*\)", open(src, errors="replace").read()))


def scan_ee(unit):
    """Per function in the unit's EE object: (calls, problems)."""
    txt = run([OBJDUMP_EE, "-dr", "-z", os.path.join(ROOT, "obj", unit + ".o")])
    funcs = {}
    cur = None
    pending = None
    for line in txt.splitlines():
        m = re.match(r"^[0-9a-f]+ <([^>]+)>:$", line)
        if m:
            cur = funcs.setdefault(m.group(1), {"calls": set(), "bad": set()})
            continue
        if cur is None:
            continue
        m = re.match(r"^\s+[0-9a-f]+: R_MIPS_26\s+(\S+)", line)
        if m:
            # the jal just printed; an external target shows as offset 0 until relocated
            if m.group(1) != ".text" and pending is not None:
                cur["calls"].discard(pending)
                cur["calls"].add(m.group(1))
            continue
        m = re.match(r"^\s+[0-9a-f]+:\s+[0-9a-f]{8}\s+(\S+)\s*(.*)$", line)
        if not m:
            continue
        op, args = m.groups()
        pending = None
        if op == "jal":
            t = re.search(r"<([^>+]+)", args)
            pending = t.group(1) if t else args
            cur["calls"].add(pending)
        elif op in ("lq", "sq", "ld", "sd", "ldl", "ldr", "sdl", "sdr", "break", "teq"):
            pass  # block copies and divide-by-zero traps; 64-bit types are caught from DWARF
        elif op in BAD_EE_OPS:
            cur["bad"].add(op)
        elif re.match(r"p(?!ref)[a-z]+", op) or op.startswith("v"):
            cur["bad"].add(op)
        elif op == "jr" and args.strip() != "ra":
            pass  # jump table: the host compiler makes its own
        elif op == "lui":
            imm = int(args.split(",")[1], 0)
            if 0x1000 <= imm < 0x1400:
                cur["bad"].add("hw")
    return funcs


TYPE_TAGS = ("DW_TAG_typedef", "DW_TAG_const_type", "DW_TAG_volatile_type")


def type_class(die):
    """'int', 'ptr', 'float', 'void' or a reason it is unsupported."""
    seen = 0
    while die is not None and die.tag in TYPE_TAGS and seen < 32:
        die = die.get_DIE_from_attribute("DW_AT_type") if "DW_AT_type" in die.attributes else None
        seen += 1
    if die is None:
        return "void"
    if die.tag in ("DW_TAG_pointer_type", "DW_TAG_reference_type"):
        return "ptr"
    if die.tag == "DW_TAG_enumeration_type":
        return "int"
    if die.tag == "DW_TAG_base_type":
        name = die.attributes["DW_AT_name"].value.decode()
        size = die.attributes["DW_AT_byte_size"].value
        if name == "float":
            return "float"
        if "long" in name or name in ("double", "bool") or size > 4:
            return "unsupported type " + name
        return "int"
    return "unsupported " + die.tag


def uses_wide_type(die, depth=0):
    """long/long long/double/bool anywhere in a function's locals (sizes differ from the EE)."""
    for child in die.iter_children():
        if "DW_AT_type" in child.attributes:
            t = child.get_DIE_from_attribute("DW_AT_type")
            for _ in range(8):
                if t.tag == "DW_TAG_base_type":
                    name = t.attributes["DW_AT_name"].value.decode()
                    if "long" in name or name in ("double", "bool"):
                        return name
                    break
                if "DW_AT_type" not in t.attributes:
                    break
                t = t.get_DIE_from_attribute("DW_AT_type")
        if depth < 6:
            r = uses_wide_type(child, depth + 1)
            if r:
                return r
    return None


def prototype(decl):
    """(parameter kinds, result kind, variadic) as the DWARF declaration gives them."""
    params, variadic = [], False
    for p in decl.iter_children():
        if p.tag == "DW_TAG_unspecified_parameters":
            variadic = True
        elif p.tag == "DW_TAG_formal_parameter":
            params.append(type_class(p.get_DIE_from_attribute("DW_AT_type")))
    ret = type_class(decl.get_DIE_from_attribute("DW_AT_type")) if "DW_AT_type" in decl.attributes else "void"
    return (tuple(params), ret, variadic)


def host_functions(obj):
    """Host symbol -> {sig, problem} from DWARF, for defined functions; and the
    prototypes the unit declares for functions it calls but does not define."""
    out, decls = {}, {}
    with open(obj, "rb") as f:
        elf = ELFFile(f)
        if not elf.has_dwarf_info():
            return out, decls
        for cu in elf.get_dwarf_info().iter_CUs():
            for die in cu.iter_DIEs():
                if die.tag == "DW_TAG_subprogram" and "DW_AT_declaration" in die.attributes:
                    link = (die.attributes.get("DW_AT_linkage_name") or die.attributes.get("DW_AT_name"))
                    if link is not None:
                        decls[link.value.decode()] = prototype(die)
                if die.tag != "DW_TAG_subprogram" or "DW_AT_low_pc" not in die.attributes:
                    continue
                decl = die
                if "DW_AT_specification" in die.attributes:
                    decl = die.get_DIE_from_attribute("DW_AT_specification")
                if "DW_AT_abstract_origin" in die.attributes:
                    decl = die.get_DIE_from_attribute("DW_AT_abstract_origin")
                    if "DW_AT_specification" in decl.attributes:
                        decl = decl.get_DIE_from_attribute("DW_AT_specification")
                attrs = decl.attributes
                link = attrs.get("DW_AT_linkage_name") or attrs.get("DW_AT_MIPS_linkage_name") or attrs.get("DW_AT_name")
                if link is None:
                    continue
                sym = link.value.decode()
                problem = None
                ints = floats = 0
                params = []
                if decl.get_parent() is not None and decl.get_parent().tag in ("DW_TAG_class_type", "DW_TAG_structure_type"):
                    problem = "member function"
                for p in decl.iter_children():
                    if p.tag == "DW_TAG_unspecified_parameters":
                        problem = "variadic"
                    if p.tag != "DW_TAG_formal_parameter":
                        continue
                    c = type_class(p.get_DIE_from_attribute("DW_AT_type"))
                    params.append(c)
                    if c == "float":
                        floats += 1
                    elif c in ("int", "ptr"):
                        ints += 1
                    else:
                        problem = problem or "parameter: " + c
                ret = type_class(decl.get_DIE_from_attribute("DW_AT_type")) if "DW_AT_type" in attrs else "void"
                if ret not in ("void", "int", "ptr", "float"):
                    problem = problem or "returns " + ret
                if ints > 8 or floats > 8:
                    problem = problem or "more than 8 register arguments"
                wide = uses_wide_type(die)
                if wide:
                    problem = problem or "uses " + wide
                out[sym] = {"params": params, "ret": ret, "problem": problem, "proto": prototype(decl)}
    return out, decls


def host_relocs(obj):
    """Per .text.<sym> section: [(reloc type, target)]; and the set of defined symbols."""
    txt = run(["objdump", "-r", obj])
    relocs = defaultdict(list)
    section = None
    for line in txt.splitlines():
        m = re.match(r"^RELOCATION RECORDS FOR \[(.+)\]:", line)
        if m:
            section = m.group(1)
            continue
        m = re.match(r"^[0-9a-f]+ (R_386_\w+)\s+(\S+)", line)
        if m and section and section.startswith(".text."):
            relocs[section[len(".text."):]].append(m.groups())
    sections = {}
    for line in run(["objdump", "-t", obj]).splitlines():
        m = re.match(r"^[0-9a-f]{8} .{7} (\S+)\s+[0-9a-f]+ (\S+)$", line)
        if m:
            sections[m.group(2)] = m.group(1)
    defined, undefined, kinds = set(), set(), {}
    for line in run(["nm", obj]).splitlines():
        parts = line.split()
        if len(parts) == 2 and parts[0] in ("U", "w"):
            undefined.add(parts[1])
        elif len(parts) == 3:
            defined.add(parts[2])
            kinds[parts[2]] = parts[1]
    return relocs, defined, undefined, kinds, sections


def demangle(names):
    names = list(names)
    if not names:
        return {}
    out = run(["c++filt"], input="\n".join(names) + "\n").splitlines()
    return dict(zip(names, out))


def main():
    os.makedirs(WORK, exist_ok=True)
    addrs = ee_map()
    by_base = defaultdict(set)
    for name, a in addrs.items():
        by_base[ee_base(name)].add(a)

    def addresses(base):
        # bss symbols the map leaves out are still named for their address
        a = by_base.get(base)
        if not a and re.fullmatch(r"D_[0-9A-F]{8}", base):
            a = {int(base[2:], 16)}
        return a or set()
    code_addrs = set()
    with open(os.path.join(ROOT, "out", "SLUS_207.72.elf"), "rb") as f:
        for sym in ELFFile(f).get_section_by_name(".symtab").iter_symbols():
            if sym["st_info"]["type"] == "STT_FUNC":
                code_addrs.add(sym["st_value"])

    report = []
    cand = {}         # host symbol -> info
    host_units = {}   # unit -> host object
    unit_undef = {}
    for unit in units():
        obj = os.path.join(WORK, unit.replace("/", "_") + ".o")
        cmd = ["g++"] + HOST_CXXFLAGS + ["-g", "-Iinclude", "-Isrc", "-c", unit, "-o", obj]
        if subprocess.run(cmd, capture_output=True).returncode != 0:
            report.append(f"# {unit}: host compile fails")
            continue
        host_units[unit] = obj
        skip = asm_names(unit)
        ee = scan_ee(unit)
        ee_by_base = {ee_base(n): v for n, v in ee.items()}
        sigs, decls = host_functions(obj)
        relocs, defined, undefined, kinds, sections = host_relocs(obj)
        unit_undef[unit] = undefined
        dem = demangle(sigs.keys())
        for sym, sig in sigs.items():
            base = dem.get(sym, sym).split("(")[0]
            if base in skip or base not in ee_by_base:
                continue
            info = {"unit": unit, "base": base, "sym": sym, "sig": sig, "deps": set(), "why": None, "protos": []}
            cand[sym] = info
            eeinfo = ee_by_base[base]
            a = by_base.get(base, set())
            if len(a) != 1:
                info["why"] = "no unique EE address"
                continue
            info["addr"] = next(iter(a))
            if eeinfo["bad"]:
                info["why"] = "EE code uses " + ",".join(sorted(eeinfo["bad"]))
                continue
            if sig["problem"]:
                info["why"] = sig["problem"]
                continue
            for c in eeinfo["calls"]:
                if c not in LIBC_ALIASES:
                    info["deps"].add(("ee", ee_base(c)))
            # host side: what does the compiled function reference?
            todo, seen = [sym], set()
            while todo and not info["why"]:
                s = todo.pop()
                if s in seen:
                    continue
                seen.add(s)
                for kind, tgt in relocs.get(s, []):
                    tname = tgt.split("+")[0].split("-")[0]
                    if tname.startswith("__x86.get_pc_thunk") or tname in HOST_OK:
                        continue
                    sect = sections.get(tname, tname) if tname.startswith(".L") else tname
                    if sect.startswith(".rodata.cst") or sect in (".rodata", ".rodata." + s) or sect.startswith(".text."):
                        continue
                    if tname.startswith("."):
                        info["why"] = f"uses the unit's own data ({tname})"
                        break
                    if tname in undefined:
                        b = ee_base(demangle([tname])[tname].split("(")[0])
                        if b in LIBC_ALIASES:
                            continue
                        aset = addresses(b)
                        if len(aset) != 1:
                            info["why"] = f"references {tname}, which has no unique EE address"
                            break
                        ta = next(iter(aset))
                        if ta in code_addrs:
                            info["deps"].add(("ee", b))
                            # the EE passes arguments in registers, so a caller that declares
                            # fewer or other ones than the callee takes still "works" there
                            info["protos"].append((b, decls.get(tname)))
                        continue
                    if kinds.get(tname, "").upper() in ("T", "W"):
                        if tname in sigs and tname != s and dem.get(tname, tname).split("(")[0] in ee_by_base:
                            info["deps"].add(("host", tname))
                        else:
                            todo.append(tname)  # a host-only helper (static/inline): check it too
                        continue
                    info["why"] = f"uses data defined in the unit ({tname})"
                    break

    # closure: drop anything that needs something not picked
    by_ee = {}
    for sym, info in cand.items():
        if not info["why"]:
            by_ee.setdefault(info["base"], info)
    changed = True
    while changed:
        changed = False
        for sym, info in cand.items():
            if info["why"]:
                continue
            for b, proto in info["protos"]:
                callee = by_ee.get(b)
                if callee is not None and proto != callee["sig"]["proto"]:
                    info["why"] = "declares " + b + " with other arguments than it takes"
                    changed = True
                    break
            if info["why"]:
                continue
            for kind, d in info["deps"]:
                ok = (by_ee.get(d) is not None and not by_ee[d]["why"]) if kind == "ee" else (d in cand and not cand[d]["why"])
                if not ok:
                    info["why"] = "calls " + d + ", which stays recompiled"
                    changed = True
                    break

    picked = sorted((i for i in cand.values() if not i["why"]), key=lambda i: i["addr"])
    picked_units = sorted({i["unit"] for i in picked})

    with open(os.path.join(HERE, "native_functions.txt"), "w") as f:
        f.write("# Generated by select_native.py; do not edit by hand.\n")
        f.write("# unit  EE-address  name\n")
        for i in picked:
            f.write(f"{i['unit']} 0x{i['addr']:08X} {i['base']}\n")

    # every symbol the picked units leave undefined gets its EE address (or a stub)
    need = set()
    for u in picked_units:
        need |= unit_undef[u]
    dem = demangle(need)
    with open(os.path.join(HERE, "native_symbols.txt"), "w") as f:
        f.write("# Generated by select_native.py; do not edit by hand.\n")
        f.write("# host-symbol  data|code|libc  EE-address\n")
        for s in sorted(need):
            b = ee_base(dem[s].split("(")[0])
            if s in HOST_OK or s.startswith("__x86.") or s == "_GLOBAL_OFFSET_TABLE_":
                continue
            if b in LIBC_ALIASES:
                f.write(f"{s} libc {LIBC_ALIASES[b]}\n")
                continue
            aset = addresses(b)
            if len(aset) != 1:
                f.write(f"{s} missing 0\n")
                continue
            a = next(iter(aset))
            kind = "code" if a in code_addrs else "data"
            f.write(f"{s} {kind} 0x{a:08X}\n")

    with open(os.path.join(WORK, "reasons.txt"), "w") as f:
        for i in sorted(cand.values(), key=lambda i: (i["unit"], i["base"])):
            f.write(f"{i['unit']} {i['base']}: {i['why'] or 'picked'}\n")
    why = defaultdict(int)
    for i in cand.values():
        if i["why"]:
            why[re.sub(r" \(.*|calls .*|references .*", lambda m: m.group(0)[:6], i["why"])] += 1
    print(f"{len(picked)} of {len(cand)} matched C functions picked, from {len(picked_units)} units")
    for k, v in sorted(why.items(), key=lambda kv: -kv[1])[:15]:
        print(f"  {v:5d}  {k}")
    for r in report:
        print(r)


if __name__ == "__main__":
    main()
