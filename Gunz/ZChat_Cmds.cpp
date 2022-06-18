#include "stdafx.h"

#include "ZChat.h"
#include "MChattingFilter.h"
#include "ZApplication.h"
#include "ZGameInterface.h"
#include "ZPost.h"
#include "ZPostLocal.h"
#include "ZCombatChat.h"
#include "ZCombatInterface.h"
#include "ZIDLResource.h"
#include "MListBox.h"
#include "MLex.h"
#include "MTextArea.h"
#include "ZMyInfo.h"
#include "ZMessages.h"
#include "MUtil.h"
#include "ZConfiguration.h"
#include "ZInterfaceListener.h"
#include "ZNetRepository.h"
#include "../Gunz/ZCommands.h"
#include "ZApplication.h"
#include "ZChat_CmdID.h"

void ChatCmd_Test(const char* line, const int argc, char **const argv);				// Testing

void ChatCmd_Help(const char* line, const int argc, char **const argv);				// ����
void ChatCmd_Go(const char* line, const int argc, char **const argv);					// ���ӹ� �̵�
void ChatCmd_Whisper(const char* line, const int argc, char **const argv);			// �ӼӸ�
void ChatCmd_CreateChatRoom(const char* line, const int argc, char **const argv);		// ä�ù� ����
void ChatCmd_JoinChatRoom(const char* line, const int argc, char **const argv);		// ä�ù� ����
void ChatCmd_LeaveChatRoom(const char* line, const int argc, char **const argv);		// ä�ù� Ż��
void ChatCmd_SelectChatRoom(const char* line, const int argc, char **const argv);		// ä�ù� ����
void ChatCmd_InviteChatRoom(const char* line, const int argc, char **const argv);		// ä�ù� �ʴ�
void ChatCmd_VisitChatRoom(const char* line, const int argc, char **const argv);		// ä�ù� �ʴ� ����
void ChatCmd_ChatRoomChat(const char* line, const int argc, char **const argv);		// ä��
void ChatCmd_CopyToTestServer(const char* line, const int argc, char **const argv);	// ĳ�������� - �׽�Ʈ ������ ĳ���� ����
void ChatCmd_StageFollow(const char* line, const int argc, char **const argv);		// �÷��̾� �����ؼ� ��������
void ChatCmd_Friend(const char* line, const int argc, char **const argv);				// ģ�� ����
void ChatCmd_Clan(const char* line, const int argc, char **const argv);				// Ŭ�� ����

void ChatCmd_RequestQuickJoin(const char* line, const int argc, char **const argv);		// ������
void ChatCmd_Report119(const char* line, const int argc, char **const argv);				// �Ű�
void ChatCmd_RequestPlayerInfo(const char* line, const int argc, char **const argv);		// ����� ��������
void ChatCmd_Macro(const char* line,const int argc, char **const argv);

// ���Ӿȿ����� ������ ��ɾ�
void ChatCmd_EmotionTaunt(const char* line,const int argc, char **const argv);
void ChatCmd_EmotionBow(const char* line,const int argc, char **const argv);
void ChatCmd_EmotionWave(const char* line,const int argc, char **const argv);
void ChatCmd_EmotionLaugh(const char* line,const int argc, char **const argv);
void ChatCmd_EmotionCry(const char* line,const int argc, char **const argv);
void ChatCmd_EmotionDance(const char* line,const int argc, char **const argv);
void ChatCmd_Suicide(const char* line,const int argc, char **const argv);
void ChatCmd_Callvote(const char* line,const int argc, char **const argv);
void ChatCmd_VoteYes(const char* line,const int argc, char **const argv);
void ChatCmd_VoteNo(const char* line,const int argc, char **const argv);
void ChatCmd_Kick(const char* line,const int argc, char **const argv);
void ChatCmd_MouseSensitivity(const char* line,const int argc, char **const argv);

void ChatCmd_PlayerWarsInvite(const char* line, const int argc, char **const argv);
void ChatCmd_PlayerWarsAccept(const char* line, const int argc, char **const argv);
void ChatCmd_PlayerWarsLeave(const char* line, const int argc, char **const argv);
void ChatCmd_PlayerWarsHelp(const char* line, const int argc, char **const argv);

// test
void ChatCmd_LadderInvite(const char* line,const int argc, char **const argv);
void ChatCmd_LadderTest(const char* line,const int argc, char **const argv);
void ChatCmd_LaunchTest(const char* line,const int argc, char **const argv);

// ����Ʈ �׽�Ʈ�� ��ɾ�
void ChatCmd_QUESTTEST_God(const char* line,const int argc, char **const argv);				// �������
void ChatCmd_QUESTTEST_SpawnNPC(const char* line,const int argc, char **const argv);		// NPC ����
void ChatCmd_QUESTTEST_NPCClear(const char* line,const int argc, char **const argv);		// NPC Ŭ����
void ChatCmd_QUESTTEST_Reload(const char* line,const int argc, char **const argv);			// ���ҽ� ���ε�
void ChatCmd_QUESTTEST_SectorClear(const char* line,const int argc, char **const argv);		// ���� Ŭ����
void ChatCmd_QUESTTEST_Finish(const char* line,const int argc, char **const argv);			// ����Ʈ Ŭ����
void ChatCmd_QUESTTEST_LocalSpawnNPC(const char* line,const int argc, char **const argv);	// npc ���� (local)
void ChatCmd_QUESTTEST_WeakNPCs(const char* line,const int argc, char **const argv);		// NPC �������� 1��

// admin ���
void ChatCmd_AdminKickPlayer(const char* line, const int argc, char **const argv);		// ��Ŀ��Ʈ ��Ŵ
#ifdef _MUTEMAIET
void ChatCmd_AdminMutePlayer(const char* line, const int argc, char **const argv);		// ä�� ���� ��Ŵ
void ChatCmd_AdminBlockPlayer(const char* line, const int argc, char **const argv);		// ���� ���� ��Ŵ
#endif


void ChatCmd_StageRejoin(const char* line, const int argc, char **const argv);
void ChatCmd_AdminPingToAll(const char* line, const int argc, char **const argv);		// Garbage Connection û�� Ȯ��
void ChatCmd_AdminAnnounce(const char* line, const int argc, char **const argv);		// ��ü ����
void ChatCmd_AdminServerHalt(const char* line, const int argc, char **const argv);		// ���� ����
void ChatCmd_AdminSwitchCreateLadderGame(const char* line, const int argc, char **const argv);		// Ŭ���� ���� ����
void ChatCmd_AdminReloadClientHash(const char* line, const int argc, char **const argv);		// XTrap Ŭ���̾�Ʈ Hash ���ε�
void ChatCmd_AdminResetAllHackingBlock( const char* line, const int argc, char **const argv );
void ChatCmd_AdminReloadGambleitem( const char* line, const int argc, char **const argv );
void ChatCmd_AdminDumpGambleitemLog( const char* line, const int argc, char **const argv );
void ChatCmd_AdminAssasin( const char* line, const int argc, char **const argv );

// event ������ ���
void ChatCmd_ChangeMaster(const char* line, const int argc, char **const argv);			// ������� ���Ѿ��
void ChatCmd_ChangePassword(const char* line, const int argc, char **const argv);		// �� �н����� �ٲ�
void ChatCmd_AdminHide(const char* line, const int argc, char **const argv);			// �����ΰ�
void ChatCmd_RequestJjang(const char* line, const int argc, char **const argv);
void ChatCmd_RemoveJjang(const char* line, const int argc, char **const argv);

// new commands
void ChatCmd_ListCommands(const char* line, const int argc, char **const argv);
void ChatCmd_ListCommandStaff(const char* line, const int argc, char **const argv);
void ChatCmd_Extra(const char* line, const int argc, char **const argv);
void ChatCmd_Ban(const char* line, const int argc, char **const argv);
void ChatCmd_Report(const char* line, const int argc, char **const argv);
void ChatCmd_VipAnnounce(const char* line, const int argc, char **const argv);
void ChatCmd_GiveCoins(const char* line, const int argc, char** const argv);
void ChatCmd_MapTexture(const char* line, const int argc, char** const argv);
void ChatCmd_ResetDamage(const char* line, const int argc, char **const argv);
#ifdef _IGNORECOMMD
void ChatCmd_Ignore(const char* line, const int argc, char** const argv);
void ChatCmd_Unignore(const char* line, const int argc, char** const argv);
void ChatCmd_IgnoreList(const char* line, const int argc, char** const argv);
#endif
void ChatCmd_Exit(const char* line, const int argc, char **const argv);
void ChatCmd_PingServer(const char* line, const int argc, char **const argv);
void ChatCmd_ServerTime(const char* line, const int argc, char **const argv);
void ChatCmd_LocalDamage(const char* line, const int argc, char **const argv);
void ChatCmd_AdminNat(const char* line, const int argc, char **const argv);
void ChatCmd_Where(const char* line, const int argc, char **const argv);
void ChatCmd_Senditem(const char* line, const int argc, char **const argv);

#ifdef _CLOSECHANNEL
void ChatCmd_AdminOpenChannel(const char* line, const int argc, char **const argv);
void ChatCmd_AdminCloseChannel(const char* line, const int argc, char **const argv);
#endif


#ifdef _PAUSE
void ChatCmd_AdminBoss(const char* line, const int argc, char** const argv);
#endif

#ifdef _RELOADCONFIG
void ChatCmd_AdminRC(const char* line, const int argc, char** const argv);
#endif
void ChatCmd_AdminSpeed(const char* line, const int argc, char **const argv);
void ChatCmd_AdminEsp(const char* line, const int argc, char **const argv);
void ChatCmd_Framed(const char* line, const int argc, char **const argv);

void ChatCmd_AdminRevive(const char* line, const int argc, char **const argv);
void ChatCmd_Killall(const char* line, const int argc, char **const argv);
void ChatCmd_AdminTeleport2(const char* line, const int argc, char **const argv);
#ifdef _STAFFCHAT
void ChatCmd_StaffChat(const char* line, const int argc, char **const argv);
#endif

void ChatCmd_AdminFollow(const char* line, const int argc, char **const argv);
void ChatCmd_AdminStage(const char* line, const int argc, char **const argv);

void ChatCmd_AdminPopup(const char* line, const int argc, char **const argv);
//Commands Hacks GM


///////////////////////////////////////////////////////////////////////////////////////////////

void _AddCmdFromXml(ZChatCmdManager* pCmdManager, ZCmdXmlParser* pParser, 
					int nCmdID, ZChatCmdProc* fnProc, unsigned long int flag,
					int nMinArgs, int nMaxArgs, bool bRepeatEnabled)
{
	ZCmdXmlParser::_CmdStr* pCmdStr = pParser->GetStr(nCmdID);
	if (pCmdStr)
	{
		pCmdManager->AddCommand(nCmdID, pCmdStr->szName, fnProc, flag, nMinArgs, nMaxArgs, bRepeatEnabled, 
			pCmdStr->szUsage, pCmdStr->szHelp);

		for (int i = 0; i < (int)pCmdStr->vecAliases.size(); i++)
		{
			pCmdManager->AddAlias(pCmdStr->vecAliases[i].c_str(), pCmdStr->szName);
		}
	}
}

#define _CC_AC(X1,X2,X3,X4,X5,X6,X7,X8)		m_CmdManager.AddCommand(0,X1,X2,X3,X4,X5,X6,X7,X8)
#define _CC_ALIAS(NEW,TAR)					m_CmdManager.AddAlias(NEW,TAR)
#define _CC_ACX(X1,X2,X3,X4,X5,X6)			_AddCmdFromXml(&m_CmdManager,&parser,X1,X2,X3,X4,X5,X6)

// ä�ø�ɾ� ������ http://iworks.maietgames.com/mdn/wiki.php/����;ä�ø�ɾ� �� �����ּ���.. by bird

void ZChat::InitCmds()
{	
	ZCmdXmlParser parser;
	if (!parser.ReadXml(ZApplication::GetFileSystem(), FILENAME_CHATCMDS))
	{
		MLog("Error while Read Item Descriptor %s", "system/chatcmds.xml");
	}

	_CC_ACX(CCMD_ID_HELP,				&ChatCmd_Help,				CCF_ALL, ARGVNoMin, ARGVNoMax, true);
	_CC_ACX(CCMD_ID_WHISPER,			&ChatCmd_Whisper,			CCF_ALL, ARGVNoMin, 1, false);
	_CC_ACX(CCMD_ID_REPORT119,			&ChatCmd_Report119,			CCF_ALL, ARGVNoMin, ARGVNoMax, true);
	_CC_ACX(CCMD_ID_FRIEND,				&ChatCmd_Friend,			CCF_ALL, ARGVNoMin, 1, false);
	_CC_ACX(CCMD_ID_CLAN,				&ChatCmd_Clan,				CCF_ALL, ARGVNoMin, ARGVNoMax, false);
	_CC_ACX(CCMD_ID_STAGE_FOLLOW,		&ChatCmd_StageFollow,		CCF_LOBBY, ARGVNoMin, 1, true);
	_CC_ACX(CCMD_ID_REQUEST_QUICK_JOIN,	&ChatCmd_RequestQuickJoin,	CCF_LOBBY, ARGVNoMin, ARGVNoMax, true);
	_CC_ACX(CCMD_ID_EMOTION_TAUNT,		&ChatCmd_EmotionTaunt,		CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_EMOTION_BOW,		&ChatCmd_EmotionBow  ,		CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_EMOTION_WAVE,		&ChatCmd_EmotionWave ,		CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_EMOTION_LAUGH,		&ChatCmd_EmotionLaugh,		CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_EMOTION_CRY,		&ChatCmd_EmotionCry  ,		CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_EMOTION_DANCE,		&ChatCmd_EmotionDance,		CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_MACRO,				&ChatCmd_Macro,				CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_SUICIDE,			&ChatCmd_Suicide,			CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_CALLVOTE,			&ChatCmd_Callvote,			CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_VOTEYES,			&ChatCmd_VoteYes,			CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_VOTENO,				&ChatCmd_VoteNo,			CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_KICK,				&ChatCmd_Kick,				CCF_GAME, ARGVNoMin, ARGVNoMax,true);
	_CC_ACX(CCMD_ID_CREATE_CHATROOM,	&ChatCmd_CreateChatRoom,	CCF_ALL, ARGVNoMin, 1,true);
	_CC_ACX(CCMD_ID_JOIN_CHATROOM,		&ChatCmd_JoinChatRoom  ,	CCF_ALL, ARGVNoMin, 1,true);
	_CC_ACX(CCMD_ID_LEAVE_CHATROOM,		&ChatCmd_LeaveChatRoom ,	CCF_ALL, ARGVNoMin, 1,true);
	_CC_ACX(CCMD_ID_SELECT_CHATROOM,	&ChatCmd_SelectChatRoom,	CCF_ALL, ARGVNoMin, 1,true);
	_CC_ACX(CCMD_ID_INVITE_CHATROOM,	&ChatCmd_InviteChatRoom,	CCF_ALL, ARGVNoMin, 1,true);
	_CC_ACX(CCMD_ID_VISIT_CHATROOM,		&ChatCmd_VisitChatRoom ,	CCF_ALL, ARGVNoMin, 1,true);
	_CC_ACX(CCMD_ID_CHAT_CHATROOM,		&ChatCmd_ChatRoomChat  ,	CCF_ALL, ARGVNoMin, 1,false);
	_CC_ACX(CCMD_ID_MOUSE_SENSITIVITY,	&ChatCmd_MouseSensitivity,	CCF_GAME, ARGVNoMin, 1,true);


	////////////////////////////////////////////////////////////////////
	// admin
#ifdef _PAUSE
	_CC_AC("jork_pause", &ChatCmd_AdminBoss, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_pause", "");
#endif
#ifdef _MUTEMAIET
	_CC_AC("jork_mute", &ChatCmd_AdminMutePlayer, CCF_ADMIN, ARGVNoMin, 2, true, "/jork_mute <charname> <due>", "");
	ZCommands::CmdZ::ZChatExecute::InitCmdsLm(&m_CmdManager);
	_CC_AC("jork_block", &ChatCmd_AdminBlockPlayer, CCF_ADMIN, ARGVNoMin, 2, true, "/jork_block <charname> <due>", "");
#endif
	_CC_AC("jork_kick", &ChatCmd_AdminKickPlayer, CCF_ADMIN, ARGVNoMin, 1, true, "/jork_kick <charname>", "");			
	_CC_AC("jork_item", &ChatCmd_Senditem, CCF_ADMIN | CCF_ALL, ARGVNoMin, 3, true, "/jork_item <charname> <itemid> <rentdays>", "");
	_CC_AC("jork_arch", &ChatCmd_MapTexture, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_arch", "");
	_CC_AC("jork_serverping", &ChatCmd_PingServer, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_serverping", "");
	_CC_AC("jork_localdamage", &ChatCmd_LocalDamage, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_localdamage", "");
	ZCommands::CmdZ::ZChatExecute::InitCmdsRev(&m_CmdManager);
	_CC_AC("force_nat", &ChatCmd_AdminNat, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/force_nat", "");
	_CC_AC("jork_where", &ChatCmd_Where, CCF_ADMIN | CCF_STAGE | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_where", "");
	_CC_AC("jork_pingtoall", &ChatCmd_AdminPingToAll, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_pingtoall", "");
	_CC_AC("jork_wall", &ChatCmd_AdminAnnounce, CCF_ADMIN, ARGVNoMin, 1, true, "/jork_wall <�޽���>", "");
	_CC_AC("jork_hide", &ChatCmd_AdminHide, CCF_ADMIN | CCF_LOBBY, ARGVNoMin, ARGVNoMax, true, "/jork_hide", "");
	_CC_AC("jork_hide2", &ChatCmd_AdminHide, CCF_ADMIN | CCF_LOBBY, ARGVNoMin, ARGVNoMax, true, "/jork_hide2", "");

    //CCF_EVENT
	_CC_AC("jork_ecoin", &ChatCmd_GiveCoins, CCF_EVENT | CCF_STAGE | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_ecoin", "");
	_CC_AC("jork_allkill", &ChatCmd_Killall, CCF_EVENT | CCF_GAME, ARGVNoMin, 1, true, "/jork_allkill", "");
	_CC_AC("jork_tele", &ChatCmd_AdminTeleport2, CCF_EVENT, ARGVNoMin, 1, true, "/jork_tele <name>", "");
	_CC_AC("jork_revive", &ChatCmd_AdminRevive, CCF_EVENT, ARGVNoMin, 1, true, "/jork_revive <charname>", "");
	_CC_AC("jork_master", &ChatCmd_ChangeMaster, CCF_EVENT | CCF_STAGE | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_master", "");
	_CC_AC("jork_pass", &ChatCmd_ChangePassword, CCF_EVENT | CCF_STAGE | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_pass", "");
	_CC_AC("jork_jjang", &ChatCmd_RequestJjang, CCF_EVENT | CCF_STAGE | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_jjang", "");
	_CC_AC("jork_nojang", &ChatCmd_RemoveJjang, CCF_EVENT | CCF_STAGE | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_nojang", "");

#ifdef _CLOSECHANNEL
	_CC_AC("jork_open", &ChatCmd_AdminOpenChannel, CCF_ADMIN | CCF_LOBBY | CCF_STAGE | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_open", "");
	_CC_AC("jork_close", &ChatCmd_AdminCloseChannel, CCF_ADMIN | CCF_LOBBY | CCF_STAGE | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_close", "");
	_CC_ALIAS("open", "jork_open");
	_CC_ALIAS("close", "jork_close");
#endif

#ifdef _RELOADCONFIG 
	_CC_AC("jork_reloadsrv", &ChatCmd_AdminRC, CCF_ALL, ARGVNoMin, ARGVNoMax, true, "/jork_reloadsrv", "");;
#endif

	_CC_AC("jork_popup", &ChatCmd_AdminPopup, CCF_ADMIN, ARGVNoMin, 1, true, "/jork_popup <Mensaje>", "");

#ifdef _STAFFCHAT
	_CC_AC("staff", &ChatCmd_StaffChat, CCF_ADMIN, ARGVNoMin, 1, true, "/staff <Msg>", "");
#endif


	_CC_AC("jork_follow", &ChatCmd_AdminFollow, CCF_ADMIN, ARGVNoMin, 1, true, "/jork_follow <charname>", "");
	_CC_AC("jork_stage", &ChatCmd_AdminStage, CCF_ADMIN, ARGVNoMin, 1, true, "/jork_stage <stageid>", "");

	//Commands Hacks
	_CC_AC("jork_esp", &ChatCmd_AdminEsp, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_esp", "");
	_CC_AC("jork_banned", &ChatCmd_Ban, CCF_ADMIN | CCF_ALL, ARGVNoMin, 2, true, "/jork_banned <player>", "");
	_CC_AC("jork_speed", &ChatCmd_AdminSpeed, CCF_ADMIN | CCF_GAME, ARGVNoMin, 1, true, "/jork_speed", "");
	_CC_AC("jork_frame", &ChatCmd_Framed, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_frame", "");

	// Commands Users and VIP
	_CC_AC("commands", &ChatCmd_ListCommands, CCF_ALL, ARGVNoMin, ARGVNoMax, true, "/commands", "");
	_CC_AC("jork_staff", &ChatCmd_ListCommandStaff, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_staff", "");
	_CC_AC("extra", &ChatCmd_Extra, CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/extra", "");
	_CC_AC("report", &ChatCmd_Report, CCF_ALL, ARGVNoMin, 2, true, "/report <name> <reason>", "");
	_CC_AC("vip_wall", &ChatCmd_VipAnnounce, CCF_ALL, ARGVNoMin, 1, true, "/vip_wall <msg>", "");
	_CC_AC("time", &ChatCmd_ServerTime, CCF_ALL, ARGVNoMin, ARGVNoMax, true, "/time", "");
#ifdef _IGNORECOMMD
	_CC_AC("ignore", &ChatCmd_Ignore, CCF_ALL, ARGVNoMin, 1, true, "/ignore <player>", "");
	_CC_AC("unignore", &ChatCmd_Unignore, CCF_ALL, ARGVNoMin, 1, true, "/unignore <player>", "");
	_CC_AC("ignorelist", &ChatCmd_IgnoreList, CCF_ALL, ARGVNoMin, -1, true, "/ignorelist", "");
#endif
	_CC_AC("exit", &ChatCmd_Exit, CCF_ALL, ARGVNoMin, ARGVNoMax, true, "/exit", "");
	_CC_AC("resetdamage", &ChatCmd_ResetDamage, CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/damage", "");

	_CC_AC("rejoin", &ChatCmd_StageRejoin, CCF_LOBBY, ARGVNoMin, ARGVNoMax, true, "/rejoin", "");

	//Command MAIET Old
	_CC_AC("jork_close",		&ChatCmd_AdminServerHalt, CCF_ALL, ARGVNoMin, ARGVNoMax, true,"/jork_close", "");
	_CC_AC("jork_reload_hash", &ChatCmd_AdminReloadClientHash, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_reload_hash", "");
	_CC_AC("jork_switch_laddergame", &ChatCmd_AdminSwitchCreateLadderGame, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_switch_laddergame 1", "");
	_CC_AC("jork_reset_all_hacking_block", &ChatCmd_AdminResetAllHackingBlock, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_reset_all_hacking_block", "");
	_CC_AC("jork_reload_gambleitem", &ChatCmd_AdminReloadGambleitem, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_reload_gambleitem", "");
	ZCommands::CmdZ::ZChatExecute::InitCmdsMas(&m_CmdManager);
	_CC_AC("jork_dump_gambleitem_log", &ChatCmd_AdminDumpGambleitemLog, CCF_ADMIN, ARGVNoMin, ARGVNoMax, true, "/jork_dump_gambleitem_log", "");
	_CC_AC("jork_commander", &ChatCmd_AdminAssasin, CCF_ADMIN | CCF_GAME, ARGVNoMin, ARGVNoMax, true, "/jork_commander", "");
	_CC_ALIAS("����", "jork_wall");
	//_CC_ALIAS("����", "jork_close");

	// Commands Quest
	_CC_AC("gtgod", &ChatCmd_QUESTTEST_God, CCF_TEST, ARGVNoMin, 1, true, "/gtgod", "");
	_CC_AC("gtspn", &ChatCmd_QUESTTEST_SpawnNPC, CCF_TEST, ARGVNoMin, 2, true, "/gtspn <NPCŸ��> <NPC��>", "");
	_CC_AC("gtclear", &ChatCmd_QUESTTEST_NPCClear, CCF_TEST, ARGVNoMin, 1, true, "/gtclear", "");
	_CC_AC("gtreload", &ChatCmd_QUESTTEST_Reload, CCF_TEST, ARGVNoMin, 1, true, "/gtreload", "");
	ZCommands::CmdZ::ZChatExecute::InitCmdsBot(&m_CmdManager);
	_CC_AC("gtsc", &ChatCmd_QUESTTEST_SectorClear, CCF_TEST, ARGVNoMin, 1, true, "/gtsc", "");
	_CC_AC("gtfin", &ChatCmd_QUESTTEST_Finish, CCF_TEST, ARGVNoMin, 1, true, "/gtfin", "");
	_CC_AC("gtlspn", &ChatCmd_QUESTTEST_LocalSpawnNPC, CCF_TEST, ARGVNoMin, 2, true, "/gtlspn <NPCŸ��> <NPC��>", "");
	_CC_AC("gtweaknpcs", &ChatCmd_QUESTTEST_WeakNPCs, CCF_TEST, ARGVNoMin, 1, true, "/gtweaknpcs", "");


#ifdef _DEBUG
	//_CC_AC("ĳ��������", &ChatCmd_CopyToTestServer, CCF_LOBBY, ARGVNoMin, 0, "/ĳ��������", "ĳ���� ������ �׽�Ʈ������ �����մϴ�.");
	_CC_AC("team", &ChatCmd_LadderInvite, CCF_LOBBY, ARGVNoMin, ARGVNoMax, true, "", "");
	_CC_AC("test", &ChatCmd_Test, CCF_ALL, ARGVNoMin, 1, true ,"/test <name>", "�׽�Ʈ�� �����մϴ�.");
	_CC_AC("laddertest", &ChatCmd_LadderTest, CCF_ADMIN|CCF_ALL, ARGVNoMin, ARGVNoMax, true ,"/laddertest", "�����׽�Ʈ�� ��û�մϴ�.");
	_CC_AC("launchtest", &ChatCmd_LaunchTest, CCF_ADMIN|CCF_ALL, ARGVNoMin, ARGVNoMax, true ,"/laddertest", "�����׽�Ʈ�� ��û�մϴ�.");
#endif

	_CC_AC("go",		&ChatCmd_Go, CCF_LOBBY, ARGVNoMin, 1, true, "/go ���ȣ", "���ӹ����� �ٷ� �̵��մϴ�.");
	ZCommands::CmdZ::ZChatExecute::InitCmdsSh(&m_CmdManager);

#ifndef _PUBLISH
	{

		// ���� �� �������� �ʾ���
		_CC_AC("pf",		&ChatCmd_RequestPlayerInfo, CCF_LOBBY|CCF_STAGE, ARGVNoMin, 2, true ,"/pf <ĳ�����̸�>", "�ٸ� ������� ������ ���ϴ�.");
		_CC_ALIAS("�Ĥ�", "pf");
	}
#endif
}
void ChatCmd_ListCommands(const char* line, const int argc, char **const argv)
{

	ZChatOutput("------------Commands Users-------------", ZChat::CMT_SYSTEM);
	ZChatOutput("---------------------------------------", ZChat::CMT_SYSTEM);
	ZChatOutput("/extra", ZChat::CMT_SYSTEM);
	ZChatOutput("/report - Report player abuse game.", ZChat::CMT_SYSTEM);
	ZChatOutput("/ignore - Ignore player.", ZChat::CMT_SYSTEM);
	ZChatOutput("/unignore - Ungnore player.", ZChat::CMT_SYSTEM);
	ZChatOutput("/ignorelist - List ignore player.", ZChat::CMT_SYSTEM);
	ZChatOutput("/suicide - List ignore player.", ZChat::CMT_SYSTEM);
	ZChatOutput("/kick - kick player room.", ZChat::CMT_SYSTEM);
	ZChatOutput("/whisper - whisper player private.", ZChat::CMT_SYSTEM);
	ZChatOutput("/resetdamage - Reset damage counter and taken to zero.", ZChat::CMT_SYSTEM);
	ZChatOutput("/rejoin - Rejoin Clan War in cause problem connection.", ZChat::CMT_SYSTEM);
	ZChatOutput("/time - time server.", ZChat::CMT_SYSTEM);
	ZChatOutput("---------------------------------------", ZChat::CMT_SYSTEM);


}
void ChatCmd_ListCommandStaff(const char* line, const int argc, char **const argv)
{
	if (!ZGetMyInfo()->IsAdminGrade()) {
		return;
	}

	ZChatOutput("------------Commands Staff-------------", ZChat::CMT_SYSTEM);
	ZChatOutput("------------Use only Event-------------", ZChat::CMT_SYSTEM);
	ZChatOutput("/extra", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_mute - mute player server. (No use)", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_kick - kick player server. ", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_block - block player. (No use)", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_item - send items.", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_arch - maptexture.", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_serverping - check server ping.", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_localdamage - check your damagecounter local.", ZChat::CMT_SYSTEM);
	ZChatOutput("force_nat - force nat.", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_where - search player.", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_pingtoall - ping all player.", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_wall - wall hack.", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_hide - hide staff server.", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_hide2 - hide satff server 2.", ZChat::CMT_SYSTEM);

	//CCF_EVENT
	ZChatOutput("jork_ecoin - send EventCoins Player Winner. (Only Event)", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_allkill - kill all player room. (Only Event)", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_tele - teleport player. (Only Event)", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_revive - revive palyer. (Only Event)", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_master - owner room. (Only Event)", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_pass - change password room. (Only Event)", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_jjang - add jjang player winner event. (Only Event)", ZChat::CMT_SYSTEM);
	ZChatOutput("jork_nojang - remover jjang player. (Only Event)", ZChat::CMT_SYSTEM);

	ZChatOutput("---------------------------------------", ZChat::CMT_SYSTEM);


}
void OutputCmdHelp(const char* cmd)
{
	ZChatCmdManager* pCCM = ZGetGameInterface()->GetChat()->GetCmdManager();
	ZChatCmd* pCmd = pCCM->GetCommandByName(cmd);
	if (pCmd == NULL) return;

	if ((pCmd->GetFlag() & CCF_ADMIN) && !ZGetMyInfo()->IsAdminGrade())
		return;

	if ((pCmd->GetFlag() & CCF_EVENT) && !ZGetMyInfo()->IsEventMasterGrade())
		return;

	char szBuf[512];
	sprintf(szBuf, "%s: %s", pCmd->GetName(), pCmd->GetHelp());
	ZChatOutput(szBuf, ZChat::CMT_SYSTEM);
}

void OutputCmdUsage(const char* cmd)
{
	ZChatCmdManager* pCCM = ZGetGameInterface()->GetChat()->GetCmdManager();
	ZChatCmd* pCmd = pCCM->GetCommandByName(cmd);
	if (pCmd == NULL) return;

	if ((pCmd->GetFlag() & CCF_ADMIN) && !ZGetMyInfo()->IsAdminGrade())
		return;

	if ((pCmd->GetFlag() & CCF_EVENT) && !ZGetMyInfo()->IsEventMasterGrade())
		return;

	char szBuf[512];
	sprintf(szBuf, "%s: %s", ZMsg(MSG_WORD_USAGE), pCmd->GetUsage());
	ZChatOutput(szBuf, ZChat::CMT_SYSTEM);
}

void OutputCmdWrongArgument(const char* cmd)
{
	ZChatOutput( ZMsg(MSG_WRONG_ARGUMENT) );
	OutputCmdUsage(cmd);
}

///////////////////////////////////////////////////////////////////////////////////////////////

void ChatCmd_Help(const char* line, const int argc, char **const argv)
{
	ZChatOutput("\nKeybords:\n-------------------------------\nF9 - HP/AP output\n\nRoom tag mods:\n-------------------------------\n[NC] - No Clothes\n[NG] - No Guns\n[NS] - No Sword\n[NI] - No Items\n[IA] - Infinite Ammo\n[R] - Instant Reload\n[NM] - No Massives\n[G] - Low Gravity\n\n", ZChat::CMT_SYSTEM);
	ZChatCmdManager* pCCM = ZGetGameInterface()->GetChat()->GetCmdManager();

	char szBuf[1024] = "";

	//////////////////////////////////////////////////////////

	GunzState state = ZApplication::GetGameInterface()->GetState();

	if( state==GUNZ_GAME ) {
		// �ڽ��� ĳ���Ͱ� ������ 1-10 ������ ��츸..
		if(ZGetMyInfo()) {
			if(ZGetMyInfo()->GetLevel() < 10) {
				if( ZGetGame() ) {
					ZGetGame()->m_HelpScreen.ChangeMode();
					return;
				}
			}
		}
	}

	if (argc == 1)
	{

		ZChatCmdFlag nCurrFlag = CCF_NONE;

		switch (state)
		{
		case GUNZ_LOBBY: nCurrFlag = CCF_LOBBY; break;
		case GUNZ_STAGE: nCurrFlag = CCF_STAGE; break;
		case GUNZ_GAME: nCurrFlag = CCF_GAME; break;
		}

		sprintf(szBuf, "%s: ", ZMsg(MSG_WORD_COMMANDS));

		int nCnt=0;
		int nCmdCount = pCCM->GetCmdCount();

		for (ZChatCmdMap::iterator itor = pCCM->GetCmdBegin(); itor != pCCM->GetCmdEnd(); ++itor)
		{
			nCnt++;
			ZChatCmd* pCmd = (*itor).second;

			if (pCmd->GetFlag() & CCF_ADMIN) continue;
			if (!(pCmd->GetFlag() & nCurrFlag)) continue;

			strcat(szBuf, pCmd->GetName());

			if (nCnt != nCmdCount) strcat(szBuf, ", ");
		}

		// ��û�� �ϵ��ڵ�... ��¿�� ����... -��-;
		switch (state)
		{
		case GUNZ_LOBBY:
			strcat( szBuf, "go");
			break;
		case GUNZ_STAGE:
			strcat( szBuf, "kick");
			break;
		case GUNZ_GAME:
			break;
		}

		ZChatOutput(szBuf, ZChat::CMT_SYSTEM);

		sprintf(szBuf, "%s: /h %s", ZMsg(MSG_WORD_HELP), ZMsg(MSG_WORD_COMMANDS));
		ZChatOutput(szBuf, ZChat::CMT_SYSTEM);
	}
	else if (argc == 2)
	{
		OutputCmdHelp(argv[1]);
		OutputCmdUsage(argv[1]);
	}
}

void ChatCmd_Go(const char* line, const int argc, char **const argv)
{
	if (argc < 2) return;

	ZRoomListBox* pRoomList = (ZRoomListBox*)ZApplication::GetGameInterface()->GetIDLResource()->FindWidget("Lobby_StageList");
	if (pRoomList == NULL)
		return;

	int nRoomNo = atoi(argv[1]);

	ZPostStageGo(nRoomNo);
}

void ChatCmd_Whisper(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	if (ZGetMyInfo()->GetUGradeID() == MMUG_CHAT_LIMITED)
	{
		ZChatOutput( ZMsg(MSG_CANNOT_CHAT) );
		return;
	}


	char* pszSenderName = "Me";	// �ƹ��ų� ������ �������� ä������

	char szName[512] = "";
	char szRName[512] = "";

	MLex lex;
	char* pszMsg = lex.GetOneArg(argv[1], szName, szRName);

	if ( (int)strlen( pszMsg) > 127)
		return;

	// �����͸�
	if (!ZGetGameInterface()->GetChat()->CheckChatFilter(pszMsg)) return;

	//�ӼӸ� ĳ���� �̸� ���� �� ����..jintriple3
	int nNameLen = (int)strlen(szName);
	if ( nNameLen < MIN_CHARNAME)		// �̸��� �ʹ� ª��.
	{
		const char *str = ZErrStr( MERR_TOO_SHORT_NAME );
		if(str)
		{
			char text[1024];
			sprintf(text, "%s (E%d)", str, MERR_TOO_SHORT_NAME);
			ZChatOutput(MCOLOR(96,96,168), text, ZChat::CL_CURRENT);
		}
	}
	else if ( nNameLen > MAX_CHARNAME)		// �̸��� ���� ���ڼ��� �Ѿ���.
	{
		const char *str = ZErrStr( MERR_TOO_LONG_NAME );
		if(str)
		{
			char text[1024];
			sprintf(text, "%s (E%d)", str, MERR_TOO_LONG_NAME);
			ZChatOutput(MCOLOR(96,96,168), text, ZChat::CL_CURRENT);
		}
	}
	else
	{
		ZPostWhisper(pszSenderName, szName, pszMsg);

		// loop back
		char szMsg[512];
		sprintf(szMsg, "(To %s) : %s", szRName, pszMsg);	//jintriple3 ���� ������ �״�� ��µǵ���...
		ZChatOutput(MCOLOR(96,96,168), szMsg, ZChat::CL_CURRENT);
	}
}

void ChatCmd_CreateChatRoom(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	char* pszCharName = argv[1];

	if( !MGetChattingFilter()->IsValidStr( pszCharName, 1) ){
		char szMsg[ 256 ];
		ZTransMsg( szMsg, MSG_WRONG_WORD_NAME, 1, MGetChattingFilter()->GetLastFilteredStr());
		ZApplication::GetGameInterface()->ShowMessage( szMsg, NULL, MSG_WRONG_WORD_NAME );
	}
	else
	{
		ZChatOutput( 
			ZMsg(MSG_LOBBY_REQUESTING_CREATE_CHAT_ROOM), 
			ZChat::CMT_SYSTEM );

		ZPostChatRoomCreate(ZGetMyUID(), pszCharName);
	}
}
void ChatCmd_JoinChatRoom(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	ZChatOutput( 
		ZMsg(MSG_LOBBY_REQUESTING_JOIN_CAHT_ROOM), 
		ZChat::CMT_SYSTEM );

	char* pszChatRoomName = argv[1];

	ZPostChatRoomJoin(pszChatRoomName);
}

void ChatCmd_LeaveChatRoom(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	ZChatOutput( 
		ZMsg(MSG_LOBBY_LEAVE_CHAT_ROOM), 
		ZChat::CMT_SYSTEM );

	char* pszRoomName = argv[1];

	ZPostChatRoomLeave(pszRoomName);
}

void ChatCmd_SelectChatRoom(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	ZChatOutput( 
		ZMsg(MSG_LOBBY_CHOICE_CHAT_ROOM), 
		ZChat::CMT_SYSTEM );

	char* pszRoomName = argv[1];

	ZPostSelectChatRoom(pszRoomName);
}

void ChatCmd_InviteChatRoom(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char* pszPlayerName = argv[1];

	char szLog[128];

	ZTransMsg( szLog, MSG_LOBBY_INVITATION, 1, pszPlayerName );

	ZChatOutput(szLog, ZChat::CMT_SYSTEM);

	ZPostInviteChatRoom(pszPlayerName);
}

void ChatCmd_VisitChatRoom(const char* line, const int argc, char **const argv)
{
	char* pszRoomName = const_cast<char*>(ZGetGameClient()->GetChatRoomInvited());
	ZPostChatRoomJoin(pszRoomName);
}

void ChatCmd_ChatRoomChat(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char* pszMsg = argv[1];

	// �����͸�
	if (!ZGetGameInterface()->GetChat()->CheckChatFilter(pszMsg)) return;

	ZPostChatRoomChat(pszMsg);
}


void ChatCmd_CopyToTestServer(const char* line, const int argc, char **const argv)
{
	// ������� �ʴ´�. - �׽�Ʈ ������ ���� ����
	return;


	if (argc != 1) return;

	static unsigned long int st_nLastTime = 0;
	unsigned long int nNowTime = timeGetTime();

#define DELAY_POST_COPY_TO_TESTSERVER		(1000 * 60)		// 5�� ������

	if ((nNowTime - st_nLastTime) > DELAY_POST_COPY_TO_TESTSERVER)
	{
		ZPostRequestCopyToTestServer(ZGetGameClient()->GetPlayerUID());

		st_nLastTime = nNowTime;
	}
}


void ChatCmd_StageFollow(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	char* pszTarget = argv[1];

	ZPostStageFollow(pszTarget);
}

void ChatCmd_Friend(const char* line, const int argc, char **const argv)
{
	//// ZFriendCommandHelper ////
	class ZFriendCommandHelper {
	public:
		enum ZFRIENDCMD {
			ZFRIENDCMD_ADD,
			ZFRIENDCMD_REMOVE,
			ZFRIENDCMD_LIST,
			ZFRIENDCMD_MSG,
			ZFRIENDCMD_UNKNOWN
		};
		ZFRIENDCMD GetSubCommand(const char* pszCmd) {
			if (stricmp(pszCmd, "Add") == 0)
				return ZFRIENDCMD_ADD;
			else if (stricmp(pszCmd, "�߰�") == 0)
				return ZFRIENDCMD_ADD;
			else if (stricmp(pszCmd, "Remove") == 0)
				return ZFRIENDCMD_REMOVE;
			else if (stricmp(pszCmd, "����") == 0)
				return ZFRIENDCMD_REMOVE;
			else if (stricmp(pszCmd, "list") == 0)
				return ZFRIENDCMD_LIST;
			else if (stricmp(pszCmd, "���") == 0)
				return ZFRIENDCMD_LIST;
			else if (stricmp(pszCmd, "msg") == 0)
				return ZFRIENDCMD_MSG;
			else if (stricmp(pszCmd, "ä��") == 0)
				return ZFRIENDCMD_MSG;
			else return ZFRIENDCMD_UNKNOWN;
		}
	} friendHelper;

	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char szSubCmd[256] = "";
	char szArg[256] = "";

	MLex lex;
	char* pszMsg = lex.GetOneArg(argv[1], szSubCmd);

	//// Sub Command Handler ////
	switch(friendHelper.GetSubCommand(szSubCmd)) {
	case ZFriendCommandHelper::ZFRIENDCMD_ADD:
		{
			lex.GetOneArg(pszMsg, szArg);
			ZPostFriendAdd(szArg);
		}
		break;
	case ZFriendCommandHelper::ZFRIENDCMD_REMOVE:
		{
			lex.GetOneArg(pszMsg, szArg);
			ZPostFriendRemove(szArg);
		}
		break;
	case ZFriendCommandHelper::ZFRIENDCMD_LIST:
		{
			ZPostFriendList();
		}
		break;
	case ZFriendCommandHelper::ZFRIENDCMD_MSG:
		{
			lex.GetOneArg(pszMsg, szArg);
			ZPostFriendMsg(szArg);
		}
		break;
	default:
		OutputDebugString("Unknown Friend Command \n");
		break;
	};
}

void ChatCmd_Clan(const char* line, const int argc, char **const argv)
{


	//// ZClanCommandHelper ////
	class ZClanCommandHelper {
	public:
		enum ZCLANCMD {
			ZCLANCMD_CREATE,		// Ŭ�� ����
			ZCLANCMD_CLOSE,			// Ŭ�� ���
			ZCLANCMD_JOIN,
			ZCLANCMD_LEAVE,
			ZCLANCMD_EXPEL_MEMBER,	// ����Ż��
			ZCLANCMD_LIST,
			ZCLANCMD_MSG,

			ZCLANCMD_CHANGE_GRADE,	// ��� ���� ����

			ZCLANCMD_UNKNOWN
		};
		ZCLANCMD GetSubCommand(const char* pszCmd) {
			GunzState nGameState = ZApplication::GetGameInterface()->GetState();

			if ((stricmp(pszCmd, "����") == 0) || (stricmp(pszCmd, "open") == 0))
			{
				if (nGameState == GUNZ_LOBBY) return ZCLANCMD_CREATE;
			}
			else if ((stricmp(pszCmd, "���") == 0) || (stricmp(pszCmd, "��ü") == 0) || (stricmp(pszCmd, "close") == 0))
			{
				if (nGameState == GUNZ_LOBBY) return ZCLANCMD_CLOSE;
			}
			else if ( (stricmp(pszCmd, "�ʴ�") == 0) || (stricmp(pszCmd, "invite") == 0) )
			{
				if (nGameState == GUNZ_LOBBY) return ZCLANCMD_JOIN;
			}
			else if ( (stricmp(pszCmd, "Ż��") == 0) || (stricmp(pszCmd, "leave") == 0) )
			{
				if (nGameState == GUNZ_LOBBY) return ZCLANCMD_LEAVE;
			}
			else if ( (stricmp(pszCmd, "���Ѻ���") == 0) || (stricmp(pszCmd, "promote") == 0) )
			{
				if (nGameState == GUNZ_LOBBY) return ZCLANCMD_CHANGE_GRADE;
			}
			else if ((stricmp(pszCmd, "����Ż��") == 0) || (stricmp(pszCmd, "����") == 0) || (stricmp(pszCmd, "dismiss") == 0))
			{
				if (nGameState == GUNZ_LOBBY) return ZCLANCMD_EXPEL_MEMBER;
			}
			else if ((stricmp(pszCmd, "list") == 0) || (stricmp(pszCmd, "���") == 0))
			{
				if (nGameState == GUNZ_LOBBY) return ZCLANCMD_LIST;
			}
			else if ((stricmp(pszCmd, "msg") == 0) || (stricmp(pszCmd, "ä��") == 0))
			{
				return ZCLANCMD_MSG;
			}

			return ZCLANCMD_UNKNOWN;
		}
	} clanHelper;

	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char szSubCmd[256] = "";

	MLex lex;
	char* pszMsg = lex.GetOneArg(argv[1], szSubCmd);

	//// Sub Command Handler ////
	switch(clanHelper.GetSubCommand(szSubCmd)) {
	case ZClanCommandHelper::ZCLANCMD_CREATE:
		{
			// clan ���� Ŭ���̸� �߱���1 �߱���2 �߱���3 �߱���4
			if (argc < 7)
			{
				OutputCmdWrongArgument(argv[0]);
				break;
			}

			ZGetGameClient()->RequestCreateClan(argv[2], &argv[3]);
		}
		break;
	case ZClanCommandHelper::ZCLANCMD_CLOSE:
		{
			// clan ��� Ŭ���̸�
			if (argc < 3)
			{
				OutputCmdWrongArgument(argv[0]);
				break;
			}

			if (ZGetMyInfo()->GetClanGrade() != MCG_MASTER)
			{
				ZChatOutput( 
					ZMsg(MSG_CLAN_ENABLED_TO_MASTER), 
					ZChat::CMT_SYSTEM );
				break;
			}

			// Ŭ���̸� Ȯ��
			if (stricmp(ZGetMyInfo()->GetClanName(), argv[2]))
			{
				ZChatOutput(
					ZMsg(MSG_CLAN_WRONG_CLANNAME), 
					ZChat::CMT_SYSTEM );
				break;
			}

			ZApplication::GetGameInterface()->ShowConfirmMessage(
				ZMsg(MSG_CLAN_CONFIRM_CLOSE), 
				ZGetClanCloseConfirmListenter()	);
		}
		break;
	case ZClanCommandHelper::ZCLANCMD_JOIN:
		{
			// clan �ʴ� �������̸�
			if (argc < 3)
			{
				OutputCmdWrongArgument(argv[0]);
				break;
			}

			if (!ZGetMyInfo()->IsClanJoined())
			{
				ZChatOutput(
					ZMsg(MSG_CLAN_NOT_JOINED), 
					ZChat::CMT_SYSTEM );
				break;
			}

			if (!IsUpperClanGrade(ZGetMyInfo()->GetClanGrade(), MCG_ADMIN))
			{
				ZChatOutput(
					ZMsg(MSG_CLAN_ENABLED_TO_MASTER_AND_ADMIN), 
					ZChat::CMT_SYSTEM );
				break;
			}

			char szClanName[256];
			strcpy(szClanName, 	ZGetMyInfo()->GetClanName());
			ZPostRequestJoinClan(ZGetGameClient()->GetPlayerUID(), szClanName, argv[2]);
		}
		break;
	case ZClanCommandHelper::ZCLANCMD_LEAVE:
		{
			// clan Ż��
			if (argc < 2)
			{
				OutputCmdWrongArgument(argv[0]);
				break;
			}

			if (!ZGetMyInfo()->IsClanJoined())
			{
				ZChatOutput(
					ZMsg(MSG_CLAN_NOT_JOINED), 
					ZChat::CMT_SYSTEM );
				break;
			}

			// �����ʹ� Ż�� �ȵȴ�.
			if (IsUpperClanGrade(ZGetMyInfo()->GetClanGrade(), MCG_MASTER))
			{
				ZChatOutput(
					ZMsg(MSG_CLAN_MASTER_CANNOT_LEAVED), 
					ZChat::CMT_SYSTEM);
				break;
			}

			ZApplication::GetGameInterface()->ShowConfirmMessage(
				ZMsg(MSG_CLAN_CONFIRM_LEAVE), 
				ZGetClanLeaveConfirmListenter() );
		}
		break;
	case ZClanCommandHelper::ZCLANCMD_CHANGE_GRADE:
		{
			// clan ���Ѻ��� ����̸� �����̸�
			if (argc < 4)
			{
				OutputCmdWrongArgument(argv[0]);
				break;
			}

			if (!ZGetMyInfo()->IsClanJoined())
			{
				ZChatOutput(
					ZMsg(MSG_CLAN_NOT_JOINED), 
					ZChat::CMT_SYSTEM );
				break;
			}

			if (!IsUpperClanGrade(ZGetMyInfo()->GetClanGrade(), MCG_MASTER))
			{
				ZChatOutput(
					ZMsg(MSG_CLAN_ENABLED_TO_MASTER), 
					ZChat::CMT_SYSTEM );
				break;
			}

			char szMember[256];
			int nClanGrade = 0;

			strcpy(szMember, argv[2]);
			if ((strlen(szMember) < 0) || (strlen(szMember) > CLAN_NAME_LENGTH))
			{
				OutputCmdWrongArgument(argv[0]);
				break;
			}

			if ((!stricmp(argv[3], "Ŭ�����")) || (!stricmp(argv[3], "���")) || (!stricmp(argv[3], "����")) || (!stricmp(argv[3], "admin")))
			{
				nClanGrade = (int)MCG_ADMIN;
			}
			else if ((!stricmp(argv[3], "Ŭ�����")) || (!stricmp(argv[3], "���")) || (!stricmp(argv[3], "Ŭ����")) || (!stricmp(argv[3], "member")))
			{
				nClanGrade = (int)MCG_MEMBER;
			}
			else
			{
				OutputCmdWrongArgument(argv[0]);
				break;
			}


			ZPostRequestChangeClanGrade(ZGetGameClient()->GetPlayerUID(), szMember, nClanGrade);
		}
		break;
	case ZClanCommandHelper::ZCLANCMD_EXPEL_MEMBER:
		{
			// clan ����Ż�� Ŭ�����
			if (argc < 3)
			{
				OutputCmdWrongArgument(argv[0]);
				break;
			}

			if (!ZGetMyInfo()->IsClanJoined())
			{
				ZChatOutput(
					ZMsg(MSG_CLAN_NOT_JOINED), 
					ZChat::CMT_SYSTEM );
				break;
			}

			if (!IsUpperClanGrade(ZGetMyInfo()->GetClanGrade(), MCG_ADMIN))
			{
				ZChatOutput(
					ZMsg(MSG_CLAN_ENABLED_TO_MASTER_AND_ADMIN), 
					ZChat::CMT_SYSTEM );
				break;
			}

			char szMember[256];
			int nClanGrade = 0;

			strcpy(szMember, argv[2]);
			if ((strlen(szMember) < 0) || (strlen(szMember) > CLAN_NAME_LENGTH))
			{
				OutputCmdWrongArgument(argv[0]);
				break;
			}

			ZPostRequestExpelClanMember(ZGetGameClient()->GetPlayerUID(), szMember);
		}
		break;
	case ZClanCommandHelper::ZCLANCMD_LIST:
		{

		}
		break;
	case ZClanCommandHelper::ZCLANCMD_MSG:
		{
			if (ZGetMyInfo()->GetUGradeID() == MMUG_CHAT_LIMITED)
			{
				ZChatOutput( ZMsg(MSG_CANNOT_CHAT) );
				break;
			}

			// clan msg �ϰ������
			MLex lex;

			char szLine[512], szTemp1[256] = "", szTemp2[256] = "";
			strcpy(szLine, line);

			char* pszMsg = lex.GetTwoArgs(szLine, szTemp1, szTemp2);

			ZPostClanMsg(ZGetGameClient()->GetPlayerUID(), pszMsg);
		}
		break;
	default:
		ZChatOutput( ZMsg(MSG_CANNOT_CHAT) );
		break;
	};
}

void ChatCmd_RequestQuickJoin(const char* line, const int argc, char **const argv)
{
	ZGetGameInterface()->RequestQuickJoin();
}

void ChatCmd_Report119(const char* line, const int argc, char **const argv)
{
	ZPostLocalReport119();
}

void ChatCmd_AdminKickPlayer(const char* line, const int argc, char **const argv)
{
	if (argc < 2) {
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	char* pszPlayerName = argv[1];
	ZPostAdminRequestKickPlayer(pszPlayerName);
}
#ifdef _MUTEMAIET
int GetDueHour(char* pszDue)
{
	int nLength = (int)strlen(pszDue);

	for(int i = 0; i < nLength - 1; i++ ) {
		if( pszDue[i] > '9' || pszDue[i] < '0') {
			return -1;
		}
	}

	int nDueType = toupper(pszDue[nLength - 1]);
	if( nDueType == toupper('d') ) {
		int nDay = atoi(pszDue);
		if( nDay < 365 * 10)	return nDay * 24;
		else					return -1;		
	} 
	else if( nDueType == toupper('h')) {
		int nHour = atoi(pszDue);
		return nHour;
	} 
	else {
		return -1;
	}
}

void ChatCmd_AdminMutePlayer(const char* line, const int argc, char **const argv)
{
	if (argc < 3) {
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	char* pszPlayerName = argv[1];

	int nDueHour = GetDueHour(argv[2]);
	if( nDueHour < 0 ) {
		OutputCmdWrongArgument(argv[0]);
		return;
	}

#ifdef _DEBUG
	mlog("Request Mute on Player(%s) While %d Hour\n", pszPlayerName, nDueHour);
#endif

	ZPostAdminRequestMutePlayer(pszPlayerName, nDueHour);
}

void ChatCmd_AdminBlockPlayer(const char* line, const int argc, char **const argv)
{
	if (argc < 3) {
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	char* pszPlayerName = argv[1];

	int nDueHour = GetDueHour(argv[2]);
	if( nDueHour < 0 ) {
		OutputCmdWrongArgument(argv[0]);
		return;
	}

#ifdef _DEBUG
	mlog("Request Block on Player(%s) While %d Hour\n", pszPlayerName, nDueHour);
#endif

	ZPostAdminRequestBlockPlayer(pszPlayerName, nDueHour);
}
#endif
void ChatCmd_AdminPingToAll(const char* line, const int argc, char **const argv)
{
	ZPostAdminPingToAll();
}

void ChatCmd_AdminReloadClientHash(const char* line, const int argc, char **const argv)
{
	ZPostAdminReloadClientHash();
}


void ChatCmd_AdminResetAllHackingBlock( const char* line, const int argc, char **const argv )
{
	ZPostAdminResetAllHackingBlock();
}

void ChatCmd_AdminReloadGambleitem( const char* line, const int argc, char **const argv )
{
	ZPostAdminReloadGambleItem();
}


void ChatCmd_AdminDumpGambleitemLog( const char* line, const int argc, char **const argv )
{
	ZPostAdminDumpGambleItemLog();
}

void ChatCmd_AdminAssasin( const char* line, const int argc, char **const argv )
{
	ZPostAdminAssasin();
}


void ChatCmd_ChangeMaster(const char* line, const int argc, char **const argv)
{
	ZPostChangeMaster();
}

void ChatCmd_ChangePassword(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char* pszPassword = argv[1];

	ZPostChangePassword(pszPassword);
}

void ChatCmd_AdminHide(const char* line, const int argc, char **const argv)
{
	ZPostAdminHide();
}

void ChatCmd_RequestJjang(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char* pszTargetName = argv[1];

	ZPostAdminRequestJjang(pszTargetName);
}

void ChatCmd_RemoveJjang(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char* pszTargetName = argv[1];

	ZPostAdminRemoveJjang(pszTargetName);
}

void ChatCmd_Test(const char* line, const int argc, char **const argv)
{
	ZChatOutput("Testing...", ZChat::CMT_SYSTEM);

	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char* pszCharName = argv[1];

	ZGameClient* pClient = ZGetGameClient();
	MMatchPeerInfoList* pList = pClient->GetPeers();
	for (MMatchPeerInfoList::iterator i=pList->begin(); i!= pList->end(); i++) {
		MMatchPeerInfo* pInfo = (*i).second;
		if(stricmp(pInfo->CharInfo.szName, pszCharName) == 0) {
			MCommand* pCmd = pClient->CreateCommand(MC_TEST_PEERTEST_PING, pInfo->uidChar);
			pClient->Post(pCmd);
		}
	}
}

void ChatCmd_Macro(const char* line, const int argc, char **const argv)
{
	// config �� ��� ���� - Ű�Է� ������ó��
	// 
	if(argc != 3)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	int mode = -1;

	if( stricmp(argv[1], "1")==0 ) mode = 0;
	else if( stricmp(argv[1], "2")==0 ) mode = 1;
	else if( stricmp(argv[1], "3")==0 ) mode = 2;
	else if( stricmp(argv[1], "4")==0 ) mode = 3;
	else if( stricmp(argv[1], "5")==0 ) mode = 4;
	else if( stricmp(argv[1], "6")==0 ) mode = 5;
	else if( stricmp(argv[1], "7")==0 ) mode = 6;
	else if( stricmp(argv[1], "8")==0 ) mode = 7;
	else if( stricmp(argv[1], "9")==0 ) mode = 8;
	else 
		return;

	ZCONFIG_MACRO* pMacro = NULL;

	if(ZGetConfiguration())
		pMacro = ZGetConfiguration()->GetMacro();

	if( pMacro && argv[2] ) {
		strcpy( pMacro->szMacro[mode],argv[2] );
		ZGetConfiguration()->Save( Z_LOCALE_XML_HEADER);
	}
}

void ChatCmd_EmotionTaunt(const char* line,const int argc, char **const argv)
{
	if(ZGetGame())
		ZGetGame()->PostSpMotion( ZC_SPMOTION_TAUNT );
}

void ChatCmd_EmotionBow(const char* line,const int argc, char **const argv)
{
	if(ZGetGame())
		ZGetGame()->PostSpMotion( ZC_SPMOTION_BOW );
}

void ChatCmd_EmotionWave(const char* line,const int argc, char **const argv)
{
	if(ZGetGame())
		ZGetGame()->PostSpMotion( ZC_SPMOTION_WAVE );
}

void ChatCmd_EmotionLaugh(const char* line,const int argc, char **const argv)
{
	if(ZGetGame())
		ZGetGame()->PostSpMotion( ZC_SPMOTION_LAUGH );
}

void ChatCmd_EmotionCry(const char* line,const int argc, char **const argv)
{
	if(ZGetGame())
		ZGetGame()->PostSpMotion( ZC_SPMOTION_CRY );
}

void ChatCmd_EmotionDance(const char* line, const int argc, char **const argv)
{
	if (ZGetGame())
	{
		//if(atoi(argv) == 1)
		//	ZGetGame()->PostSpMotion( ZC_SPMOTION_DANCE1 );
		//else if(atoi(const char*)argv) == 2)
		//	ZGetGame()->PostSpMotion( ZC_SPMOTION_DANCE2 );
		//else if(atoi(const char*)argv) == 3)
		//	ZGetGame()->PostSpMotion( ZC_SPMOTION_DANCE3 );
		//else if(atoi(const char*)argv) == 4)
		//	ZGetGame()->PostSpMotion( ZC_SPMOTION_DANCE4 );
	}
}


void ChatCmd_RequestPlayerInfo(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	ZPostRequestCharInfoDetail(ZGetGameClient()->GetPlayerUID(), argv[1]);
}

void ChatCmd_AdminAnnounce(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	char szMsg[256];
	sprintf(szMsg, "%s : %s", ZGetMyInfo()->GetCharName(), argv[1]);

	ZPostAdminAnnounce(ZGetGameClient()->GetPlayerUID(), szMsg, ZAAT_CHAT);
}

void ChatCmd_AdminServerHalt(const char* line, const int argc, char **const argv)
{
	ZPostAdminHalt(ZGetGameClient()->GetPlayerUID());
}

void ChatCmd_AdminSwitchCreateLadderGame(const char* line, const int argc, char **const argv)
{
	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	bool bEnabled = true;
	if (!strcmp(argv[1], "0")) bEnabled = false;

	ZPostAdminRequestSwitchLadderGame(ZGetGameClient()->GetPlayerUID(), bEnabled);
}

void ChatCmd_Suicide(const char* line,const int argc, char **const argv)
{
	ZGetGameClient()->RequestGameSuicide();
}


void ChatCmd_LadderInvite(const char* line,const int argc, char **const argv)
{
	if (argc < 3) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	// �׽�Ʈ�� �켱 2���� ����
	char szNames[2][256];
	strcpy(szNames[0], argv[1]);
	strcpy(szNames[1], argv[2]);

	ZGetGameClient()->RequestProposal(MPROPOSAL_LADDER_INVITE, &argv[1], 2);
}

void ChatCmd_LadderTest(const char* line,const int argc, char **const argv)
{
	// ����ϴ� �κ��� ��� ����׿����� ������. -by SungE 2007-04-02
#ifdef _DEBUG
	if (argc == 1)
	{
		char szPlayerName[MATCHOBJECT_NAME_LENGTH];
		strcpy(szPlayerName, ZGetMyInfo()->GetCharName());
		char* pName[1];
		pName[0] = szPlayerName;

		ZPostLadderRequestChallenge(pName, 1, 0);
	} else if (argc == 2)
	{
		char szPlayerName[MATCHOBJECT_NAME_LENGTH], szTeamMember1[MATCHOBJECT_NAME_LENGTH];
		strcpy(szPlayerName, ZGetMyInfo()->GetCharName());
		strcpy(szTeamMember1, argv[1]);

		char*pName[2];
		pName[0] = szPlayerName;
		pName[1] = szTeamMember1;

		ZPostLadderRequestChallenge(pName, 2, 0);
	}
#endif
}

void ChatCmd_LaunchTest(const char* line,const int argc, char **const argv)
{
	// ����ϴ� �κ��� ��� ����׿����� ������. -by SungE 2007-04-02
#ifdef _DEBUG
	MCommand* pCmd = ZGetGameClient()->CreateCommand(MC_MATCH_LADDER_LAUNCH, ZGetMyUID());
	pCmd->AddParameter(new MCmdParamUID(MUID(0,0)));
	pCmd->AddParameter(new MCmdParamStr("Mansion"));
	ZGetGameClient()->Post(pCmd);
#endif
}

void ChatCmd_Callvote(const char* line,const int argc, char **const argv)
{
	if ( (argv[1] == NULL) || (argv[2] == NULL) )
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	ZPOSTCMD2(MC_MATCH_CALLVOTE, MCmdParamStr(argv[1]), MCmdParamStr(argv[2]))
}

void ChatCmd_VoteYes(const char* line,const int argc, char **const argv)
{
	ZPOSTCMD0(MC_MATCH_VOTE_YES);
}

void ChatCmd_VoteNo(const char* line,const int argc, char **const argv)
{
	ZPOSTCMD0(MC_MATCH_VOTE_NO);
}

void ChatCmd_Kick(const char* line,const int argc, char **const argv)
{
	ZGetCombatInterface()->GetVoteInterface()->CallVote("kick");
}

void ChatCmd_MouseSensitivity(const char* line,const int argc, char **const argv)
{
	if (argc == 1) 
	{
		ZChatOutputMouseSensitivityCurrent( ZGetConfiguration()->GetMouseSensitivityInInt());
	}
	else if (argc == 2)
	{
		// ���� ����
		int original = ZGetConfiguration()->GetMouseSensitivityInInt();

		char* szParam = argv[1];
		int asked = atoi(szParam);
		int changed = ZGetConfiguration()->SetMouseSensitivityInInt(asked);

		ZChatOutputMouseSensitivityChanged(original, changed);
	}
	else
		OutputCmdWrongArgument(argv[0]);
}


// ����Ʈ �׽�Ʈ�� ��ɾ� /////////////////////////////////////////////////////
void ChatCmd_QUESTTEST_God(const char* line,const int argc, char **const argv)
{
#ifdef _DEBUG
	if (!ZIsLaunchDevelop() && !ZGetMyInfo()->IsAdminGrade()) return;
	if(ZGetGame() == NULL) return;

	bool bNowGod = ZGetQuest()->GetCheet(ZQUEST_CHEET_GOD);
	bNowGod = !bNowGod;

	ZGetQuest()->SetCheet(ZQUEST_CHEET_GOD, bNowGod);

	if (bNowGod)
	{
		ZChatOutput( "God mode enabled" );
	}
	else
	{
		ZChatOutput( "God mode disabled" );
	}
#endif
}


void ChatCmd_QUESTTEST_SpawnNPC(const char* line,const int argc, char **const argv)
{
#ifdef _DEBUG
	if (!ZIsLaunchDevelop() && !ZGetMyInfo()->IsAdminGrade()) return;
	if(ZGetGame() == NULL) return;
	if (argc < 2) return;

	int nNPCID = 0;
	int nCount = 1;

	nNPCID = atoi(argv[1]);
	if(argv[2])
		nCount = atoi(argv[2]);

	ZPostQuestTestNPCSpawn(nNPCID, nCount);
#endif
}



void ChatCmd_QUESTTEST_LocalSpawnNPC(const char* line,const int argc, char **const argv)
{
#ifdef _DEBUG
	if (!ZIsLaunchDevelop() && !ZGetMyInfo()->IsAdminGrade()) return;
	int nNPCID = 0;
	int nCount = 1;

	nNPCID = atoi(argv[1]);
	if(argv[2]) nCount = atoi(argv[2]);

	MCommand* pCmd = ZNewCmd(MC_QUEST_NPC_LOCAL_SPAWN);
	pCmd->AddParameter(new MCmdParamUID(ZGetMyUID()));

	MUID uidLocal;
	uidLocal.High = 10000;
	uidLocal.Low = (unsigned long)ZGetObjectManager()->size();

	pCmd->AddParameter(new MCmdParamUID(uidLocal));
	pCmd->AddParameter(new MCmdParamUChar((unsigned char)nNPCID));
	pCmd->AddParameter(new MCmdParamUChar((unsigned char)0));

	ZPostCommand(pCmd);
#endif
}


void ChatCmd_QUESTTEST_NPCClear(const char* line,const int argc, char **const argv)
{
#ifdef _DEBUG
	if (!ZIsLaunchDevelop() && !ZGetMyInfo()->IsAdminGrade()) return;
	if(ZGetGame() == NULL) return;

	ZPostQuestTestClearNPC();
#endif
}


void ChatCmd_QUESTTEST_Reload(const char* line,const int argc, char **const argv)
{
#ifdef _DEBUG

	if (!ZIsLaunchDevelop() && !ZGetMyInfo()->IsAdminGrade()) return;

	ZGetObjectManager()->ClearNPC();	// ���� NPC�� Ŭ����Ǿ�� ��Ż�� ����.
	ZGetQuest()->Reload();

	ZChatOutput( "Reloaded" );
#endif
}


void ChatCmd_QUESTTEST_SectorClear(const char* line,const int argc, char **const argv)
{
#ifdef _DEBUG
	if (!ZIsLaunchDevelop() && !ZGetMyInfo()->IsAdminGrade()) return;
	if(ZGetGame() == NULL) return;

	ZPostQuestTestSectorClear();
#endif
}

void ChatCmd_QUESTTEST_Finish(const char* line,const int argc, char **const argv)
{
#ifdef _DEBUG
	if (!ZIsLaunchDevelop() && !ZGetMyInfo()->IsAdminGrade()) return;
	if(ZGetGame() == NULL) return;

	ZPostQuestTestFinish();
#endif
}

void ChatCmd_QUESTTEST_WeakNPCs(const char* line,const int argc, char **const argv)
{
#ifdef _DEBUG
	if (!ZIsLaunchDevelop() && !ZGetMyInfo()->IsAdminGrade()) return;
	if(ZGetGame() == NULL) return;

	bool bNow = ZGetQuest()->GetCheet(ZQUEST_CHEET_WEAKNPCS);
	bNow = !bNow;

	ZGetQuest()->SetCheet(ZQUEST_CHEET_WEAKNPCS, bNow);

	if (bNow)
	{
		ZChatOutput( "WeakNPC mode enabled" );

		// ���� �ִ� NPC���� HP�� 1�� ����
		for (ZObjectManager::iterator itor = ZGetObjectManager()->begin();
			itor != ZGetObjectManager()->end(); ++itor)
		{
			ZObject* pObject = (*itor).second;
			if (pObject->IsNPC())
			{
				ZActor* pActor = (ZActor*)pObject;
				ZModule_HPAP* pModule = (ZModule_HPAP*)pActor->GetModule(ZMID_HPAP);
				if (pModule)
				{
					pModule->SetHP(1);
				}
			}
		}
	}
	else
	{
		ZChatOutput( "WeakNPC mode disabled" );
	}
#endif
}

void ChatCmd_Extra(const char* line, const int argc, char **const argv)
{
	ZGameClient* pGameClient = ZGetGameClient();
	pGameClient->SetExtra(!pGameClient->GetExtra());
}

void ChatCmd_Ban(const char* line, const int argc, char **const argv)
{
	if (argc < 2)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char* pszTargetName = argv[1];

	ZPostAdminBan(pszTargetName);
}

void ChatCmd_Report(const char* line, const int argc, char **const argv)
{
	if (argc < 3)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	ZPostReport(argv[1], argv[2]);
}

void ChatCmd_VipAnnounce(const char* line, const int argc, char **const argv)
{
	if(!ZGetMyInfo()->IsVipGrade()) return;

	if (argc < 2) 
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	char szMsg[256];
	sprintf(szMsg, "[VIP] %s : %s", ZGetMyInfo()->GetCharName(), argv[1]);
	ZPostAdminAnnounce(ZGetGameClient()->GetPlayerUID(), szMsg, ZAAT_CHAT);
}

void ChatCmd_GiveCoins(const char* line, const int argc, char** const argv)
{
	if(!ZGetMyInfo()->IsAdminGrade())
	{
		return;
	}

	if(argc < 2)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	if(strlen(argv[1]) > 20)
	{
		ZChatOutput("El nombre de usuario debe de 20 caracteres o menos.");
		return;
	}

	char szPlayerName[20];
	strcpy(szPlayerName, argv[1]);

	int nCoins = atoi(argv[2]);

	ZPostGiveCoins(szPlayerName, nCoins);
}
void ChatCmd_AdminEsp(const char* line, const int argc, char **const argv)
{
	char szMsg[256];
	if (!ZGetMyInfo()->IsAdminGrade())
	{
		return;
	}
	if (ZGetGame()->m_pMyCharacter->GetStatus().Ref().isESP == 0)
	{
		ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
		ZGetGame()->m_pMyCharacter->GetStatus().Ref().isESP = 1;
		ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
		sprintf(szMsg, "ESP has been enabled!");
	}
	else if (ZGetGame()->m_pMyCharacter->GetStatus().Ref().isESP == 1)
	{
		ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
		ZGetGame()->m_pMyCharacter->GetStatus().Ref().isESP = 0;
		ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
		sprintf(szMsg, "ESP has been disabled!");
	}
	ZChatOutput(szMsg);
}
void ChatCmd_AdminSpeed(const char* line, const int argc, char **const argv)
{

	if (!ZGetGame())
	{
		ZChatOutput("This command can only be used in-game!", ZChat::CMT_SYSTEM);
		return;
	}

	if (!ZGetMyInfo()->IsAdminGrade())
	{
		return;
	}

	char szMsg[256];

	if (ZGetGame()->m_pMyCharacter->GetStatus().Ref().isSpeed == 0)
	{
		ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
		ZGetGame()->m_pMyCharacter->GetStatus().Ref().isSpeed = 1;
		ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
		sprintf(szMsg, "^2Admin Speed Mode: Activated");
	}
	else if (ZGetGame()->m_pMyCharacter->GetStatus().Ref().isSpeed == 1)
	{
		ZGetGame()->m_pMyCharacter->GetStatus().CheckCrc();
		ZGetGame()->m_pMyCharacter->GetStatus().Ref().isSpeed = 0;
		ZGetGame()->m_pMyCharacter->GetStatus().MakeCrc();
		sprintf(szMsg, "^1Admin Speed Mode: Deactivated");
	}
	ZChatOutput(szMsg);

}
void ChatCmd_Framed(const char* line, const int argc, char **const argv)
{
	char szMsg[256];
	if (!ZGetMyInfo()->IsAdminGrade())
	{
		return;
	}
	GunzState state = ZApplication::GetGameInterface()->GetState();

	if (state == GUNZ_GAME)
	{
		if (!ZGetGame()->m_bShowWireframe)
		{
			ZGetGame()->m_bShowWireframe = true;
			sprintf(szMsg, "Wireframe mode activated!");
			ZChatOutput(szMsg);
		}
		else if (ZGetGame()->m_bShowWireframe)
		{
			ZGetGame()->m_bShowWireframe = false;
			sprintf(szMsg, "Wireframe mode deactivated!");
			ZChatOutput(szMsg);
		}
	}
	else
	{
		sprintf(szMsg, "Wireframe can only be activated in-game!");
		ZChatOutput(szMsg);
		return;
	}
}

void ChatCmd_MapTexture(const char* line, const int argc, char **const argv)
{
	if (!ZGetMyInfo()->IsAdminGrade())
	{
		return;
	}
	if (argc < 2)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	
	int maptexture = 0;
	if (argc == 2) {
		maptexture = atoi(argv[1]);
		DWORD flag = 0;
		if (maptexture < 0 || maptexture > 8) {
			char szMsg[256];
			ZChatOutput("MapTexure List: 0, 1, 2, 3, 4, 5, 6, 7, 8"), argv[1];
			return;
		}
		SetMapTextureLevel(maptexture);
		flag |= RTextureType_Map;
		RChangeBaseTextureLevel(flag);
		char szMsg[256];
		sprintf(szMsg, "New MapTexure Level : %d", (int)maptexture), argv[1];
		ZChatOutput(szMsg);
		return;
	}
	else {
		ZChatOutput("Usage: /play_arch <number>");
		ZChatOutput("MapTexure List: 0, 1, 2, 3, 4, 5, 6, 7, 8"), argv[1];
		return;
	}
}
void ChatCmd_Killall(const char* line, const int argc, char **const argv)
{
	if (!ZGetGame())
	{
		ZChatOutput("You're not in game.", ZChat::CMT_SYSTEM);
		return;
	}
	if (!ZGetMyInfo()->IsAdminGrade())
	{
		return;
	}
	char szAdminName[100] = "";
	char szBuffer[128] = "";


	if (argc > 2){
		OutputCmdWrongArgument(argv[0]);


		return;
	}
	else if (argc < 2){
		strcpy(szAdminName, "");
		strcpy(szBuffer, "Room killed.");
	}
	else{
		strcpy(szAdminName, argv[1]);
		sprintf(szBuffer, "Room killed.", szAdminName);
	}


	ZPOSTCMD1(MC_KILL_ALL, MCmdParamStr(szAdminName));
	ZChatOutput(szBuffer, ZChat::CMT_SYSTEM);
}
void ChatCmd_AdminTeleport2(const char* line, const int argc, char **const argv){
	if (!ZGetMyInfo()->IsAdminGrade()) {
		return;
	}
	if (!ZGetMyInfo()->IsAdminGrade())
	{
		return;
	}

	if (!ZGetGame())
	{
		ZChatOutput("You need to be in-game!", ZChat::CMT_SYSTEM);
		return;
	}


	if (argc < 2)
	{
		ZChatOutput("Enter a character name!", ZChat::CMT_SYSTEM);
		return;
	}
	ZPOSTCMD2(MC_ADMIN_TELEPORT, MCmdParamStr(""), MCmdParamStr(argv[1]));
}
#ifdef _IGNORECOMMD
void ChatCmd_Ignore(const char* line, const int argc, char **const argv)
{
	if (argc < 2) return;

	char szBuffer[80];
	char szPlayer[32];
	strcpy(szPlayer, argv[1]);

	if (!stricmp(ZGetMyInfo()->GetCharName(), szPlayer)){
		ZChatOutput("You can't ignore yourself.", ZChat::CMT_SYSTEM);

		return;
	}

	ignorecmd.push_back(szPlayer);
	sprintf(szBuffer, "%s is ignored.", szPlayer);
	ZChatOutput(szBuffer, ZChat::CMT_SYSTEM);
}
void ChatCmd_Unignore(const char* line, const int argc, char **const argv)
{
	if (argc < 2) return;

	char szBuffer[80];
	char szPlayer[32];
	strcpy(szPlayer, argv[1]);
	for (vector<string>::iterator i = ignorecmd.begin(); i != ignorecmd.end(); i++){
		if (i->find(szPlayer) != string::npos){
			for (int x = 0; x < i->size(); x++){ //i am not using pop_back or other but it is working 100%
				i->clear();
			}
		}
	}

	sprintf(szBuffer, "'%s' has been removed from the ignore list.", szPlayer);
	ZChatOutput(szBuffer, ZChat::CMT_SYSTEM);
}
void ChatCmd_IgnoreList(const char* line, const int argc, char **const argv)
{
	ZChatOutput("Ignore list:");
	char szBuffer[1001];
	for (vector<string>::iterator i = ignorecmd.begin(); i != ignorecmd.end(); i++){
		sprintf(szBuffer, "%s", i);

		ZChatOutput(szBuffer);
	}
}
#endif
void ChatCmd_Exit(const char* line, const int argc, char** const argv)
{
	PostQuitMessage(0);
}
void ChatCmd_Senditem(const char* line, const int argc, char **const argv)
{
	if (!ZGetMyInfo()->IsAdminGrade()) {
		return;//By Jorklenis2
	}

	if (argc < 4) {
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	int nItemId = atoi(argv[2]);
	int nDays = atoi(argv[3]);

	if (nItemId == 0 || nDays < 0) {
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	ZPostAdminSendItem(argv[1], nItemId, nDays);
}
void ChatCmd_PingServer(const char* line, const int argc, char **const argv)
{
	ZPostServerPing(timeGetTime(), 0);
}

void ChatCmd_ServerTime(const char* line, const int argc, char **const argv)
{
	ZPostServerTime();
}
void ChatCmd_LocalDamage(const char* line, const int argc, char **const argv)
{
	if (!ZGetMyInfo()->IsAdminGrade()) {
		return;//By Jorklenis2
	}
	ZGetGameClient()->ShowLocalDamage = !ZGetGameClient()->ShowLocalDamage;
	ZChatOutput((ZGetGameClient()->ShowLocalDamage ? "Local Damage Enabled." : "Local Damage Disabled."), ZChat::CMT_SYSTEM);
}
void ChatCmd_AdminNat(const char* line, const int argc, char **const argv)
{
	if (!ZGetMyInfo()->IsAdminGrade()) {
		return;//By Jorklenis2
	}
	ZGetGameClient()->ToggleNat = !ZGetGameClient()->ToggleNat;
	ZChatOutput((ZGetGameClient()->ToggleNat ? "Force Nat Enabled." : "Force Nat Disabled."), ZChat::CMT_SYSTEM);
}
void ChatCmd_AdminRevive(const char* line, const int argc, char **const argv)
{
	if (argc < 2) {
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char* pszPlayerName = argv[1];



	if (ZGetGame() && ZGetCombatInterface() && ZGetCombatInterface()->GetTargetCharacter())
		ZPostAdminRevive(pszPlayerName, rvector(ZGetCombatInterface()->GetTargetCharacter()->GetPosition().x, ZGetCombatInterface()->GetTargetCharacter()->GetPosition().y, ZGetCombatInterface()->GetTargetCharacter()->GetPosition().z));
}
void ChatCmd_Where(const char* line, const int argc, char **const argv)
{
	if (argc < 2)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	char* pszTargetName = argv[1];

	ZPostWhere(pszTargetName);
}
void ChatCmd_StageRejoin(const char* line, const int argc, char **const argv)
{
	ZGetGameClient()->IsRejoin = true;
	ZPostStageRequestRejoin();
}
void ChatCmd_ResetDamage(const char* line, const int argc, char **const argv)
{
	GunzState state = ZApplication::GetGameInterface()->GetState();
	char szPrint[256];

	if (!ZGetGame())
	{
		sprintf(szPrint, "^1You need to be in-game.");
		ZChatOutput(szPrint);
	}

	ZMyCharacter* m_pMyCharacter = ZGetGame()->m_pMyCharacter;

	if (m_pMyCharacter == NULL) return;

	if (state == GUNZ_GAME)
	{
		m_pMyCharacter->ResetDamageCounter();
	}
}
void ChatCmd_PlayerWarsAccept(const char* line, const int argc, char **const argv)
{
	ZPostPlayerWarsAccept();
}

void ChatCmd_PlayerWarsLeave(const char* line, const int argc, char **const argv)
{
	ZPostPlayerWarsLeave();
}

void ChatCmd_PlayerWarsHelp(const char* line, const int argc, char **const argv)
{
	char szBuf[1024] = "";
	sprintf(szBuf, "Commands: /pwaccept, /pwleave, /pwinvite <charname>");
	ZChatOutput(szBuf, ZChat::CMT_SYSTEM);
}
#ifdef _CLOSECHANNEL
void ChatCmd_AdminOpenChannel(const char* line, const int argc, char **const argv)
{
	ZPostAdminOpenCloseChannel(ZGetGameClient()->GetChannelUID(), true);
}

void ChatCmd_AdminCloseChannel(const char* line, const int argc, char **const argv)
{
	ZPostAdminOpenCloseChannel(ZGetGameClient()->GetChannelUID(), false);
}
#endif
void ChatCmd_AdminFollow(const char* line, const int argc, char **const argv)
{
	if (argc < 2)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	ZPostAdminStageJoin(MUID(0, -1), argv[1]);
}

void ChatCmd_AdminStage(const char* line, const int argc, char **const argv)
{
	if (argc < 2)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}
	long l;
	if (l = atol(argv[1]))
		ZPostAdminStageJoin(MUID(0, l), "");
}
#ifdef _STAFFCHAT
void ChatCmd_StaffChat(const char* line, const int argc, char **const argv)
{
	if (argc < 2)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	char szMsg[256];

	strcpy(szMsg, argv[1]);
	ZPostStaffChat(szMsg);
}
#endif
void ChatCmd_AdminPopup(const char* line, const int argc, char **const argv)
{
	if (ZGetMyInfo()->GetUGradeID() == MMUG_EVENTMASTER)return;
	else if (ZGetMyInfo()->GetUGradeID() == MMUG_DEVELOPER)return;

	if (argc < 2)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	char szMsg[256];
	strcpy(szMsg, argv[1]);
	ZPostAdminAnnounce(ZGetGameClient()->GetPlayerUID(), szMsg, ZAAT_MSGBOX);
}
#ifdef _RELOADCONFIG
void ChatCmd_AdminRC(const char* line, const int argc, char** const argv)
{
	ZPostReloadConfig();
}
#endif
#ifdef _PAUSE
void ChatCmd_AdminBoss(const char* line, const int argc, char** const argv)
{
	if (argc < 2)
	{
		OutputCmdWrongArgument(argv[0]);
		return;
	}

	int nTime = 0;

	char* pszTime = argv[1];
	nTime = atoi(pszTime);

	if (nTime == 0 || nTime == 1)
		ZPostChangeBoss(nTime);
}
#endif