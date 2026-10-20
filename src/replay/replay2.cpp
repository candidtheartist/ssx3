#include "common.h"

INCLUDE_ASM("replay/replay2", cReplay_addCache);

INCLUDE_ASM("replay/replay2", func_002700D8);

INCLUDE_ASM("replay/replay2", func_00270130);

INCLUDE_ASM("replay/replay2", func_002701A0);

INCLUDE_ASM("replay/replay2", func_00270238);

INCLUDE_ASM("replay/replay2", Replay_IsPaused);

INCLUDE_ASM("replay/replay2", Replay_SeekToSnapshot);

INCLUDE_ASM("replay/replay2", func_00270378);

INCLUDE_ASM("replay/replay2", Replay_StepFrame);

INCLUDE_ASM("replay/replay2", Replay_PruneSnapshots);

INCLUDE_ASM("replay/replay2", func_002705A8);

INCLUDE_ASM("replay/replay2", Replay_CheckInstantReplay);

INCLUDE_ASM("replay/replay2", Replay_CancelInstantReplay);

INCLUDE_ASM("replay/replay2", Replay_RequestInstantReplay);

INCLUDE_ASM("replay/replay2", Replay_EndInstantReplay);

INCLUDE_ASM("replay/replay2", func_002706B8);

INCLUDE_ASM("replay/replay2", cReplay_stopAutoReplay__FPv);

INCLUDE_ASM("replay/replay2", Replay_FindRiderIndex);

INCLUDE_ASM("replay/replay2", Replay_OnRiderLaunch);

INCLUDE_ASM("replay/replay2", Replay_OnRiderLand);

INCLUDE_ASM("replay/replay2", Replay_OnRiderWipeout);

INCLUDE_ASM("replay/replay2", Replay_OnRiderReset);

INCLUDE_ASM("replay/replay2", func_002709D8);

INCLUDE_ASM("replay/replay2", Replay_OnRiderCheckpoint);

INCLUDE_ASM("replay/replay2", Replay_BeginHighlight);

INCLUDE_ASM("replay/replay2", Replay_CountHighlights);

INCLUDE_ASM("replay/replay2", func_00270C40);

INCLUDE_ASM("replay/replay2", Replay_FindWeakestHighlight);

INCLUDE_ASM("replay/replay2", Replay_EndHighlight);

INCLUDE_ASM("replay/replay2", Replay_CancelHighlight);

INCLUDE_ASM("replay/replay2", Replay_ClearAllHighlights);

INCLUDE_ASM("replay/replay2", func_00270E68);

INCLUDE_ASM("replay/replay2", func_00270ED8);

INCLUDE_ASM("replay/replay2", Replay_ResetOnLoad);

INCLUDE_ASM("replay/replay2", func_00270F18);

INCLUDE_ASM("replay/replay2", Replay_AllocSaveBuffers);

INCLUDE_ASM("replay/replay2", Replay_FreeSaveBuffers);

INCLUDE_ASM("replay/replay2", Replay_FlushSaveOutput);

INCLUDE_ASM("replay/replay2", Replay_SaveEmit);

INCLUDE_ASM("replay/replay2", Replay_WriteSaveBlock);

INCLUDE_ASM("replay/replay2", Replay_SaveBuildHeader);

INCLUDE_ASM("replay/replay2", Replay_SaveWriteHeader);

INCLUDE_ASM("replay/replay2", Replay_CountSaveSnapshots);

INCLUDE_ASM("replay/replay2", Replay_SaveBeginSnapshots);

INCLUDE_ASM("replay/replay2", Replay_SaveWriteSnapshot);

INCLUDE_ASM("replay/replay2", Replay_SaveBeginCaches);

INCLUDE_ASM("replay/replay2", Replay_SaveWriteCache);

INCLUDE_ASM("replay/replay2", Replay_SaveComputePadding);

INCLUDE_ASM("replay/replay2", Replay_SaveWritePadding);

INCLUDE_ASM("replay/replay2", func_002716F0);

INCLUDE_ASM("replay/replay2", Replay_SaveWriteFooter);

INCLUDE_ASM("replay/replay2", Replay_LoadSaved);

INCLUDE_ASM("replay/replay2", Replay_StaticInitDestroy);

INCLUDE_ASM("replay/replay2", func_002721D0);

INCLUDE_ASM("replay/replay2", func_00272258);

INCLUDE_ASM("replay/replay2", Replay_HighlightSlotInit);

INCLUDE_ASM("replay/replay2", Replay_GlobalCtors);

INCLUDE_ASM("replay/replay2", InSeq_HeapInit);

INCLUDE_ASM("replay/replay2", InSeq_HeapAlloc);

INCLUDE_ASM("replay/replay2", InSeq_HeapFree);

INCLUDE_ASM("replay/replay2", InSeq_HeapNew);

INCLUDE_ASM("replay/replay2", InSeq_HeapNewArray);

INCLUDE_ASM("replay/replay2", InSeq_HeapDelete);

INCLUDE_ASM("replay/replay2", InSeq_HeapDeleteArray);

INCLUDE_ASM("replay/replay2", Math_EvalCubic);

INCLUDE_ASM("replay/replay2", InSeq_CurveTrack_ctor);

INCLUDE_ASM("replay/replay2", InSeq_CurveTrackStart);

INCLUDE_ASM("replay/replay2", InSeq_CurveTrackStop);

INCLUDE_ASM("replay/replay2", InSeq_CurveTrackUpdate);

INCLUDE_ASM("replay/replay2", func_00272788);

INCLUDE_ASM("replay/replay2", func_002728D0);

INCLUDE_ASM("replay/replay2", func_002728F8);

INCLUDE_ASM("replay/replay2", func_00272938);

INCLUDE_ASM("replay/replay2", func_002729A8);

INCLUDE_ASM("replay/replay2", func_00272AD0);

INCLUDE_ASM("replay/replay2", func_00272B58);

INCLUDE_ASM("replay/replay2", func_00272CC0);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrack_ctor);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrack_dtor);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrackStart);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrackStop);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrackUpdate);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrackGetNextEventTime);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrackActivateKey);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrackNextKey);

INCLUDE_ASM("replay/replay2", InSeq_EventTrack_ctor);

INCLUDE_ASM("replay/replay2", InSeq_EventTrack_dtor);

INCLUDE_ASM("replay/replay2", InSeq_EventTrackStart);

INCLUDE_ASM("replay/replay2", InSeq_EventTrackStop);

INCLUDE_ASM("replay/replay2", InSeq_EventTrackUpdate);

INCLUDE_ASM("replay/replay2", InSeq_EventTrackGetNextEventTime);

INCLUDE_ASM("replay/replay2", InSeq_EventTrackFireKey);

INCLUDE_ASM("replay/replay2", InSeq_EventTrackNextKey);

INCLUDE_ASM("replay/replay2", InSeq_RampTrack_ctor);

INCLUDE_ASM("replay/replay2", InSeq_RampTrack_dtor);

INCLUDE_ASM("replay/replay2", InSeq_RampTrackStart);

INCLUDE_ASM("replay/replay2", InSeq_RampTrackStop);

INCLUDE_ASM("replay/replay2", InSeq_RampTrackUpdate);

INCLUDE_ASM("replay/replay2", InSeq_RampTrackGetNextEventTime);

INCLUDE_ASM("replay/replay2", InSeq_RampTrackActivateKey);

INCLUDE_ASM("replay/replay2", InSeq_RampTrackNextKey);

INCLUDE_ASM("replay/replay2", InSeq_Channel_ctor);

INCLUDE_ASM("replay/replay2", InSeq_Channel_dtor);

INCLUDE_ASM("replay/replay2", InSeq_ChannelSetup);

INCLUDE_ASM("replay/replay2", InSeq_ChannelRelease);

INCLUDE_ASM("replay/replay2", func_00273A60);

INCLUDE_ASM("replay/replay2", InSeq_ChannelStart);

INCLUDE_ASM("replay/replay2", func_00273D20);

INCLUDE_ASM("replay/replay2", InSeq_ChannelStop);

INCLUDE_ASM("replay/replay2", InSeq_ChannelRestart);

INCLUDE_ASM("replay/replay2", InSeq_ChannelAdvance);

INCLUDE_ASM("replay/replay2", func_00274240);

INCLUDE_ASM("replay/replay2", InSeq_ChannelGetTrack);

INCLUDE_ASM("replay/replay2", func_002742E0);

INCLUDE_ASM("replay/replay2", InSeq_ChannelGetLength);

INCLUDE_ASM("replay/replay2", func_00274388);

INCLUDE_ASM("replay/replay2", func_002743C8);

INCLUDE_ASM("replay/replay2", InSeq_ChannelUpdateTracks);

INCLUDE_ASM("replay/replay2", InSeq_Instance_ctor);

INCLUDE_ASM("replay/replay2", InSeq_InstanceSetup);

INCLUDE_ASM("replay/replay2", InSeq_InstanceRelease);

INCLUDE_ASM("replay/replay2", func_00274808);

INCLUDE_ASM("replay/replay2", InSeq_InstanceRestart);

INCLUDE_ASM("replay/replay2", InSeq_InstanceStart);

INCLUDE_ASM("replay/replay2", InSeq_InstanceStop);

INCLUDE_ASM("replay/replay2", func_002749E8);

INCLUDE_ASM("replay/replay2", func_00274A08);

INCLUDE_ASM("replay/replay2", func_00274A30);

INCLUDE_ASM("replay/replay2", func_00274C10);

INCLUDE_ASM("replay/replay2", InSeq_InstanceGetChannel);

INCLUDE_ASM("replay/replay2", func_00274C38);

INCLUDE_ASM("replay/replay2", InSeq_InstanceGetLength);

INCLUDE_ASM("replay/replay2", func_00274D08);

INCLUDE_ASM("replay/replay2", InSeq_InstanceGetListener);

INCLUDE_ASM("replay/replay2", InSeq_InstanceTick);

INCLUDE_ASM("replay/replay2", InSeq_InstanceAdvance);

INCLUDE_ASM("replay/replay2", InSeq_CurveTrackGetValuePtr);

INCLUDE_ASM("replay/replay2", InSeq_CurveTrack_v05);

INCLUDE_ASM("replay/replay2", InSeq_CurveTrackGetNextEventTime);

INCLUDE_ASM("replay/replay2", InSeq_CurveTrackGetType);

INCLUDE_ASM("replay/replay2", InSeq_CurveTrackGetChannel);

INCLUDE_ASM("replay/replay2", InSeq_CurveTrackIsStarted);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrackGetValuePtr);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrack_v05);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrackGetType);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrackGetChannel);

INCLUDE_ASM("replay/replay2", InSeq_SpanTrackIsStarted);

INCLUDE_ASM("replay/replay2", InSeq_EventTrackGetValuePtr);

INCLUDE_ASM("replay/replay2", InSeq_EventTrack_v05);

INCLUDE_ASM("replay/replay2", InSeq_EventTrackGetType);

INCLUDE_ASM("replay/replay2", InSeq_EventTrackGetChannel);

INCLUDE_ASM("replay/replay2", InSeq_EventTrackIsStarted);

INCLUDE_ASM("replay/replay2", InSeq_RampTrackGetValuePtr);

INCLUDE_ASM("replay/replay2", InSeq_RampTrack_v05);

INCLUDE_ASM("replay/replay2", InSeq_RampTrackGetType);

INCLUDE_ASM("replay/replay2", InSeq_RampTrackGetChannel);

INCLUDE_ASM("replay/replay2", InSeq_RampTrackIsStarted);

