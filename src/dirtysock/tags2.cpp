#include "common.h"

INCLUDE_ASM("dirtysock/tags2", LobbyMan_NullLobbyCallback);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_CompareUserNames);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_CompareRoomNames);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_ctor);

INCLUDE_ASM("dirtysock/tags2", func_00259628);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnRecvDebug);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnDisconnect);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnRoomListChanged);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnRankListChanged);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnMessage);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnGameStart);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_CreatePeerTable);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_DestroyPeerTable);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_LookupPeerAddr);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_CreateLists);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_ReleaseSnapshotLists);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_DestroyLists);

INCLUDE_ASM("dirtysock/tags2", func_0025A948);

INCLUDE_ASM("dirtysock/tags2", func_0025AA98);

INCLUDE_ASM("dirtysock/tags2", func_0025AAE0);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_PostChatEvent);

INCLUDE_ASM("dirtysock/tags2", func_0025AC50);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_SendRequest);

INCLUDE_ASM("dirtysock/tags2", func_0025B650);

INCLUDE_ASM("dirtysock/tags2", func_0025B688);

INCLUDE_ASM("dirtysock/tags2", func_0025B6D8);

INCLUDE_ASM("dirtysock/tags2", func_0025B800);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnConnectReply);

INCLUDE_ASM("dirtysock/tags2", func_0025B9C8);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_ParseNameSuggestions);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnCreateAccountReply);

INCLUDE_ASM("dirtysock/tags2", func_0025BF18);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnEditAccountReply);

INCLUDE_ASM("dirtysock/tags2", func_0025C1E0);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnLostByEmailReply);

INCLUDE_ASM("dirtysock/tags2", func_0025C3F8);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnLostByNameReply);

INCLUDE_ASM("dirtysock/tags2", func_0025C610);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnLoginReply);

INCLUDE_ASM("dirtysock/tags2", func_0025CD28);

INCLUDE_ASM("dirtysock/tags2", func_0025CD50);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnSelectPersonaReply);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_QueryOwnStats);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnOwnStatsReply);

INCLUDE_ASM("dirtysock/tags2", func_0025D1B8);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnCreatePersonaReply);

INCLUDE_ASM("dirtysock/tags2", func_0025D428);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnDeletePersonaReply);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnUserListChanged);

INCLUDE_ASM("dirtysock/tags2", func_0025D770);

INCLUDE_ASM("dirtysock/tags2", func_0025D800);

INCLUDE_ASM("dirtysock/tags2", func_0025D860);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnMoveToRoomReply);

INCLUDE_ASM("dirtysock/tags2", func_0025DA90);

INCLUDE_ASM("dirtysock/tags2", func_0025DAC0);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnCreateRoomReply);

INCLUDE_ASM("dirtysock/tags2", func_0025DD08);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnPingReply);

INCLUDE_ASM("dirtysock/tags2", func_0025DF00);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnReportUserReply);

INCLUDE_ASM("dirtysock/tags2", func_0025E0C8);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnNewsReply);

INCLUDE_ASM("dirtysock/tags2", func_0025E348);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_SendSnapshot);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnSnapshotReply);

INCLUDE_ASM("dirtysock/tags2", func_0025E6D0);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnLookupUserReply);

INCLUDE_ASM("dirtysock/tags2", func_0025EE20);

INCLUDE_ASM("dirtysock/tags2", func_0025EED8);

INCLUDE_ASM("dirtysock/tags2", func_0025F030);

INCLUDE_ASM("dirtysock/tags2", func_0025F120);

INCLUDE_ASM("dirtysock/tags2", func_0025F150);

INCLUDE_ASM("dirtysock/tags2", func_0025F180);

INCLUDE_ASM("dirtysock/tags2", func_0025F1B0);

INCLUDE_ASM("dirtysock/tags2", func_0025F1E0);

INCLUDE_ASM("dirtysock/tags2", func_0025F248);

INCLUDE_ASM("dirtysock/tags2", func_0025F288);

INCLUDE_ASM("dirtysock/tags2", func_0025F338);

INCLUDE_ASM("dirtysock/tags2", func_0025F388);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_IsInRoom);

INCLUDE_ASM("dirtysock/tags2", func_0025F4C0);

INCLUDE_ASM("dirtysock/tags2", func_0025F628);

INCLUDE_ASM("dirtysock/tags2", func_0025F740);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_ResetChalState);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnChalReply);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_ChalRequestHost);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_ChalRequestJoin);

INCLUDE_ASM("dirtysock/tags2", func_0025FB58);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_SendPrivateMessage);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_OnMesgReply);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_SendDecline);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_SendAbortChal);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_SendLockChal);

INCLUDE_ASM("dirtysock/tags2", func_0025FD50);

INCLUDE_ASM("dirtysock/tags2", func_00260C68);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_GetErrorString);

INCLUDE_ASM("dirtysock/tags2", func_00260F10);

INCLUDE_ASM("dirtysock/tags2", func_00260F80);

INCLUDE_ASM("dirtysock/tags2", func_00261008);

INCLUDE_ASM("dirtysock/tags2", func_00261058);

INCLUDE_ASM("dirtysock/tags2", func_00261070);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_AddMessageSendersToRoster);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_Connect);

INCLUDE_ASM("dirtysock/tags2", func_002613C8);

INCLUDE_ASM("dirtysock/tags2", func_00261408);

INCLUDE_ASM("dirtysock/tags2", func_00261460);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_Update);

INCLUDE_ASM("dirtysock/tags2", func_002614E8);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_DestroyApi);

INCLUDE_ASM("dirtysock/tags2", func_002615C8);

INCLUDE_ASM("dirtysock/tags2", func_00261770);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_OnRosterAddReply);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_OnRosterRemoveReply);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_OnSendMessageReply);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_OnMessageReceived);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_AddMessage);

INCLUDE_ASM("dirtysock/tags2", func_00261EF8);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_AddRosterEntry);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_CountPermanentEntries);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_CountTempEntries);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_IsBuddy);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_IsBuddyAt);

INCLUDE_ASM("dirtysock/tags2", func_002623B0);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_IsBlockedAt);

INCLUDE_ASM("dirtysock/tags2", func_00262400);

INCLUDE_ASM("dirtysock/tags2", func_00262438);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_FindRosterEntry);

INCLUDE_ASM("dirtysock/tags2", func_002624F8);

INCLUDE_ASM("dirtysock/tags2", func_00262598);

INCLUDE_ASM("dirtysock/tags2", func_002625C8);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_GetBuddyAt);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_GetBlockedAt);

INCLUDE_ASM("dirtysock/tags2", func_00262690);

INCLUDE_ASM("dirtysock/tags2", func_00262768);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_MapPresenceState);

INCLUDE_ASM("dirtysock/tags2", func_00262938);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_CountMessagesFromAt);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_CountMessagesFrom);

INCLUDE_ASM("dirtysock/tags2", func_00262A38);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_OnChallengeReceived);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_FindChallengerIndex);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_RemoveTempEntryAt);

INCLUDE_ASM("dirtysock/tags2", func_00263018);

INCLUDE_ASM("dirtysock/tags2", func_00263128);

INCLUDE_ASM("dirtysock/tags2", func_00263270);

INCLUDE_ASM("dirtysock/tags2", func_00263308);

INCLUDE_ASM("dirtysock/tags2", func_00263338);

INCLUDE_ASM("dirtysock/tags2", func_002633C8);

INCLUDE_ASM("dirtysock/tags2", func_002633F8);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_IsSameProduct);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_RosterCompare);

INCLUDE_ASM("dirtysock/tags2", func_002635A8);

INCLUDE_ASM("dirtysock/tags2", func_00263630);

INCLUDE_ASM("dirtysock/tags2", func_00263660);

INCLUDE_ASM("dirtysock/tags2", func_00263678);

INCLUDE_ASM("dirtysock/tags2", func_002636A8);

INCLUDE_ASM("dirtysock/tags2", func_002636F0);

INCLUDE_ASM("dirtysock/tags2", func_00263828);

INCLUDE_ASM("dirtysock/tags2", func_00263998);

INCLUDE_ASM("dirtysock/tags2", func_002639B0);

INCLUDE_ASM("dirtysock/tags2", Net_StartGameSetup);

INCLUDE_ASM("dirtysock/tags2", func_00263BA8);

INCLUDE_ASM("dirtysock/tags2", func_00263CF0);

INCLUDE_ASM("dirtysock/tags2", func_00264030);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_Destroy);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_ctor);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_dtor);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_Update);

INCLUDE_ASM("dirtysock/tags2", func_00264960);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_FreePacket);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_PopPacket);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_ReceivePackets);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_FlushSendQueue);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_SendPacket);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_SendHello);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_SetLocalCharacter);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_SetRemoteCharacter);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_SendCharacterMsg);

INCLUDE_ASM("dirtysock/tags2", func_00264F88);

INCLUDE_ASM("dirtysock/tags2", func_00265018);

INCLUDE_ASM("dirtysock/tags2", func_00265140);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_HostRecvSelect);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_HostRecvConfirm);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_HostRecvCancel);

INCLUDE_ASM("dirtysock/tags2", func_00265458);

INCLUDE_ASM("dirtysock/tags2", func_00265568);

INCLUDE_ASM("dirtysock/tags2", func_00265688);

INCLUDE_ASM("dirtysock/tags2", cSetupMan_SendBragMsg12);

INCLUDE_ASM("dirtysock/tags2", func_00265768);

INCLUDE_ASM("dirtysock/tags2", func_00265880);

INCLUDE_ASM("dirtysock/tags2", func_002658B8);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_ctor);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_dtor);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_Init);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_Shutdown);

INCLUDE_ASM("dirtysock/tags2", func_002659E8);

INCLUDE_ASM("dirtysock/tags2", func_00265A38);

INCLUDE_ASM("dirtysock/tags2", func_00265A68);

INCLUDE_ASM("dirtysock/tags2", func_00265CB0);

INCLUDE_ASM("dirtysock/tags2", func_00265D08);

INCLUDE_ASM("dirtysock/tags2", func_00265D38);

INCLUDE_ASM("dirtysock/tags2", func_00265D68);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_DoLoad);

INCLUDE_ASM("dirtysock/tags2", func_00265DF0);

INCLUDE_ASM("dirtysock/tags2", func_00265E00);

INCLUDE_ASM("dirtysock/tags2", func_00265E10);

INCLUDE_ASM("dirtysock/tags2", func_00265E20);

INCLUDE_ASM("dirtysock/tags2", func_00265E30);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_DoUpdate);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_DoCreate);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_DoDelete);

INCLUDE_ASM("dirtysock/tags2", func_00265F00);

INCLUDE_ASM("dirtysock/tags2", func_00265F18);

INCLUDE_ASM("dirtysock/tags2", func_00265F68);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McListDir);

INCLUDE_ASM("dirtysock/tags2", func_00266010);

INCLUDE_ASM("dirtysock/tags2", func_00266038);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McGetInfo);

INCLUDE_ASM("dirtysock/tags2", func_002660A0);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McOpen);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McClose);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McMkdir);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McDeleteFile);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McDeletePath);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McRead);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McWrite);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McSeek);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McFlush);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McCb_State0F);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McPoll);

INCLUDE_ASM("dirtysock/tags2", func_00266550);

INCLUDE_ASM("dirtysock/tags2", cSharedLoginMan_McMapError);

INCLUDE_ASM("dirtysock/tags2", func_00266728);

INCLUDE_ASM("dirtysock/tags2", TibExtMemFree);

INCLUDE_ASM("dirtysock/tags2", func_00266788);

INCLUDE_ASM("dirtysock/tags2", cUsbKeyboard_ctor);

INCLUDE_ASM("dirtysock/tags2", cUsbKeyboard_OnConnect);

INCLUDE_ASM("dirtysock/tags2", cUsbKeyboard_Update);

INCLUDE_ASM("dirtysock/tags2", cUsbKeyboard_GetKey);

INCLUDE_ASM("dirtysock/tags2", func_00266CA0);

INCLUDE_ASM("dirtysock/tags2", func_00266CD8);

INCLUDE_ASM("dirtysock/tags2", cVoipMan_ctor);

INCLUDE_ASM("dirtysock/tags2", cVoipMan_dtor);

INCLUDE_ASM("dirtysock/tags2", cVoipMan_Start);

INCLUDE_ASM("dirtysock/tags2", func_00266DF8);

INCLUDE_ASM("dirtysock/tags2", cVoipMan_Activate);

INCLUDE_ASM("dirtysock/tags2", func_00266E88);

INCLUDE_ASM("dirtysock/tags2", func_00266F38);

INCLUDE_ASM("dirtysock/tags2", cVoipMan_SetVolume);

INCLUDE_ASM("dirtysock/tags2", cVoipMan_GetStatus);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_MessageVectorInsert);

INCLUDE_ASM("dirtysock/tags2", BuddyMan_ChallengerVectorInsert);

INCLUDE_ASM("dirtysock/tags2", LobbyMan_StaticInit);

INCLUDE_ASM("dirtysock/tags2", cDSockChannel_Base_Disconnect);

INCLUDE_ASM("dirtysock/tags2", cDSockChannel_Base_Update);

INCLUDE_ASM("dirtysock/tags2", cDSockChannel_Base_IsConnected);

INCLUDE_ASM("dirtysock/tags2", cDSockChannel_Base_v05);

INCLUDE_ASM("dirtysock/tags2", cDSockChannel_Base_v06);

INCLUDE_ASM("dirtysock/tags2", cDSockChannel_Base_Recv);

INCLUDE_ASM("dirtysock/tags2", cDSockChannel_Base_Send);

INCLUDE_ASM("dirtysock/tags2", cDSockChannel_IsConnected);

INCLUDE_ASM("dirtysock/tags2", cDSockChannel_v06);

INCLUDE_ASM("dirtysock/tags2", NetEvent_dtor);

INCLUDE_ASM("dirtysock/tags2", NetEvent_Clone);

INCLUDE_ASM("dirtysock/tags2", NetEvent102_dtor);

INCLUDE_ASM("dirtysock/tags2", NetEvent102_Clone);

INCLUDE_ASM("dirtysock/tags2", func_00267F28);

INCLUDE_ASM("dirtysock/tags2", func_00267F58);

INCLUDE_ASM("dirtysock/tags2", NetErrorEvent_dtor);

INCLUDE_ASM("dirtysock/tags2", NetErrorEvent_Clone);

INCLUDE_ASM("dirtysock/tags2", func_00268048);

INCLUDE_ASM("dirtysock/tags2", func_002680A8);

INCLUDE_ASM("dirtysock/tags2", func_00268158);

INCLUDE_ASM("dirtysock/tags2", func_002681B0);

INCLUDE_ASM("dirtysock/tags2", NetEvent102Tooy_dtor);

INCLUDE_ASM("dirtysock/tags2", NetEvent102Tooy_Clone);

INCLUDE_ASM("dirtysock/tags2", NetEvent102Lock_dtor);

INCLUDE_ASM("dirtysock/tags2", NetEvent102Lock_Clone);

INCLUDE_ASM("dirtysock/tags2", NetEvent102Down_dtor);

INCLUDE_ASM("dirtysock/tags2", NetEvent102Down_Clone);

INCLUDE_ASM("dirtysock/tags2", func_00268460);

INCLUDE_ASM("dirtysock/tags2", func_002684C0);

INCLUDE_ASM("dirtysock/tags2", func_00268588);

INCLUDE_ASM("dirtysock/tags2", func_002685E0);

INCLUDE_ASM("dirtysock/tags2", func_00268658);

INCLUDE_ASM("dirtysock/tags2", func_00268688);

INCLUDE_ASM("dirtysock/tags2", func_002686F0);

INCLUDE_ASM("dirtysock/tags2", func_00268720);

INCLUDE_ASM("dirtysock/tags2", func_00268790);

INCLUDE_ASM("dirtysock/tags2", func_002687C0);

