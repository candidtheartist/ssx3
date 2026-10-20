#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Turn spimdisasm's --function-info CSV into the function map ps2_recomp reads.

Usage: gen_funcs.py FUNCINFO_CSV SPLITS_TXT OUT_CSV
"""
import csv
import sys


def main(funcinfo, splits_path, out_path):
    funcs = []
    with open(funcinfo, newline="") as f:
        for row in csv.DictReader(f):
            start = int(row["address"], 16)
            funcs.append([start, start + int(row["length"], 16), row["name"]])

    splits = []
    with open(splits_path) as f:
        for line in f:
            line = line.split("#", 1)[0].split()
            if line:
                splits.append((int(line[0], 16), line[1]))

    for addr, name in splits:
        owner = next((fn for fn in funcs if fn[0] < addr < fn[1]), None)
        if owner is None:
            sys.exit(f"split 0x{addr:08X} is not inside any function")
        funcs.append([addr, owner[1], name])
        owner[1] = addr

    funcs.sort()
    with open(out_path, "w", newline="\n") as f:
        f.write("Name,Start,End,Size\n")
        for start, end, name in funcs:
            f.write(f"{name},0x{start:08X},0x{end:08X},{end - start}\n")
    print(f"{len(funcs)} functions, {len(splits)} split")


if __name__ == "__main__":
    if len(sys.argv) != 4:
        sys.exit(__doc__)
    main(*sys.argv[1:])
