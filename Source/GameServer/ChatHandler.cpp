#include "stdafx.h"
#include "DBAgent.h"
#include "../shared/DateTime.h"

using std::string;

ServerCommandTable CGameServerDlg::s_commandTable;
ChatCommandTable CUser::s_commandTable;

void CGameServerDlg::InitServerCommands()
{
	static Command<CGameServerDlg> commandTable[] = 
	{
		// Command				Handler												Help message
		{ "notice",				&CGameServerDlg::HandleNoticeCommand,				"Sends a server-wide chat notice." },
		{ "bdwopen",			&CGameServerDlg::HandleBdwOpenCommand,				"Bdw Open Beta." },
		{ "noticeall",			&CGameServerDlg::HandleNoticeallCommand,			"Sends a server-wide chat notice." },
		{ "kill",				&CGameServerDlg::HandleKillUserCommand,				"Disconnects the specified player" },
		{ "open1",				&CGameServerDlg::HandleWar1OpenCommand,				"Opens war zone 1" },
		{ "open2",				&CGameServerDlg::HandleWar2OpenCommand,				"Opens war zone 2" },
		{ "open3",				&CGameServerDlg::HandleWar3OpenCommand,				"Opens war zone 3" },
		{ "open4",				&CGameServerDlg::HandleWar4OpenCommand,				"Opens war zone 4" },
		{ "open5",				&CGameServerDlg::HandleWar5OpenCommand,				"Opens war zone 5" },
		{ "open6",				&CGameServerDlg::HandleWar6OpenCommand,				"Opens war zone 6" },
		{ "snowopen",			&CGameServerDlg::HandleSnowWarOpenCommand,			"Opens the snow war zone" },
		{ "snowclose",			&CGameServerDlg::HandleSnowWarCloseCommand,			"Snow Closes the active snowwar zone" },
		{ "siegewarfare",		&CGameServerDlg::HandleSiegeWarOpenCommand,			"Opens the Castle Siege War zone" },
		{ "close",				&CGameServerDlg::HandleWarCloseCommand,				"Closes the active war zone" },
		{ "discount",			&CGameServerDlg::HandleDiscountCommand,				"Enables server discounts for the winning nation of the last war" },
		{ "alldiscount",		&CGameServerDlg::HandleGlobalDiscountCommand,		"Enables server discounts for everyone" },
		{ "offdiscount",		&CGameServerDlg::HandleDiscountOffCommand,			"Disables server discounts" },
		{ "captain",			&CGameServerDlg::HandleCaptainCommand,				"Sets the captains/commanders for the war" },
		{ "santa",				&CGameServerDlg::HandleSantaCommand,				"Enables a flying Santa Claus." },
		{ "offsanta",			&CGameServerDlg::HandleSantaOffCommand,				"Disables a flying Santa Claus/angel." },
		{ "angel",				&CGameServerDlg::HandleAngelCommand,				"Enables a flying angel." },
		{ "offangel",			&CGameServerDlg::HandleSantaOffCommand,				"Disables a flying Santa Claus/angel." },
		{ "permanent",			&CGameServerDlg::HandlePermanentChatCommand,		"Sets the permanent chat bar to the specified text." },
		{ "offpermanent",		&CGameServerDlg::HandlePermanentChatOffCommand,		"Resets the permanent chat bar text." },
		{ "reload_notice",		&CGameServerDlg::HandleReloadNoticeCommand,			"Reloads the in-game notice list." },
		{ "reload_tables",		&CGameServerDlg::HandleReloadTablesCommand,			"Reloads the in-game tables." },
		{ "reload_magics",		&CGameServerDlg::HandleReloadMagicsCommand,			"Reloads the in-game magic tables." },
		{ "reload_op",			&CGameServerDlg::HandleReloadItemOPCommand,			"Recarrega a tabela ITEM_OP"},
		{ "reload_dupe",		&CGameServerDlg::HandleReloadDupeCommand,			"Recarrega a tabela ITEMS_DUPE"},
		{ "reload_ilegal",		&CGameServerDlg::HandleReloadIlegalItemsCommand,	"Recarrega a tabela ILEGAL_ITEMS"},
		{ "reload_siege",		&CGameServerDlg::HandleReloadSiegeCommand,			"Recarrega a tabela KNIGHTS_SIEGE_WARFARE"},
		{ "reload_quests",		&CGameServerDlg::HandleReloadQuestCommand,			"Reloads the in-game quest tables." },
		{ "reload_ranks",		&CGameServerDlg::HandleReloadRanksCommand,			"Reloads the in-game rank tables." },
		{ "count",				&CGameServerDlg::HandleCountCommand,				"Get online user count." },
		{ "permitconnect",		&CGameServerDlg::HandlePermitConnectCommand,        "Player unban" },
		{ "give_item",				&CGameServerDlg::HandleGiveItemCommand,				"Gives a player an item. Arguments: character name | item ID | [optional stack size]" },
		{ "exp_add",			&CGameServerDlg::HandleExpAddCommand,				"Sets the server-wide XP event. If bonusPercent is set to 0, the event is ended. Arguments: bonusPercent" },
		{ "np_add",				&CGameServerDlg::HandleNPAddCommand,				"Sets the server-wide NP event. If bonusPercent is set to 0, the event is ended. Arguments: bonusPercent" },
		{ "money_add",			&CGameServerDlg::HandleMoneyAddCommand,				"Sets the server-wide coin event. If bonusPercent is set to 0, the event is ended. Arguments: bonusPercent" },
		{ "tp_all",				&CGameServerDlg::HandleTeleportAllCommand,			"Players send to home zone." },
		{ "warresult",			&CGameServerDlg::HandleWarResultCommand,			"Set result for War" },
		{ "summonmonster",		&CGameServerDlg::HandleMonSummonCommand,			"Sets the server-wide coin event. If bonusPercent is set to 0, the event is ended. Arguments: bonusPercent" },
		{ "giveachieve",		&CGameServerDlg::HandleGiveAchieveCommand,			"Gives Achieve to User"},
		{ "resetachieve",		&CGameServerDlg::HandleResetAchieveCommand,			"Reset all Achieve Stats to User"},
	};

	init_command_table(CGameServerDlg, commandTable, s_commandTable);
}

void CGameServerDlg::CleanupServerCommands() { free_command_table(s_commandTable); }

void CUser::InitChatCommands()
{
	static Command<CUser> commandTable[] = 
	{
		// Command				Handler											Help message
		{ "give_item",			&CUser::HandleGiveItemCommand,					"Gives a player an item. Arguments: character name | item ID | [optional stack size]" },
		{ "bdwopen",			&CUser::HandleBdwOpenCommand,				    "Bdw Open Beta." },
		{ "zonechange",			&CUser::HandleZoneChangeCommand,				"Teleports you to the specified zone. Arguments: zone ID" },
		{ "monster",			&CUser::HandleMonsterSummonCommand,				"Spawns the specified monster (does not respawn). Arguments: monster's database ID" },
		{ "npc",			    &CUser::HandleNPCSummonCommand,					"Spawns the specified NPC (does not respawn). Arguments: NPC's database ID" },
		{ "kill",				&CUser::HandleMonKillCommand,					"Kill a NPC or Monster, Arguments: select an Npc and monster than use this command" },
		{ "open1",				&CUser::HandleWar1OpenCommand,					"Opens war zone 1" },
		{ "open2",				&CUser::HandleWar2OpenCommand,					"Opens war zone 2" },
		{ "open3",				&CUser::HandleWar3OpenCommand,					"Opens war zone 3" },
		{ "open4",				&CUser::HandleWar4OpenCommand,					"Opens war zone 4" },
		{ "open5",				&CUser::HandleWar5OpenCommand,					"Opens war zone 5" },
		{ "open6",				&CUser::HandleWar6OpenCommand,					"Opens war zone 6" },
		{ "captain",			&CUser::HandleCaptainCommand,					"Sets the captains/commanders for the war" },
		{ "snowopen",			&CUser::HandleSnowWarOpenCommand,				"Opens the snow war zone" },
		{ "snowclose",			&CUser::HandleSnowWarCloseCommand,				"Snow Closes the active Snowwar zone" },
		{ "siegewarfare",		&CUser::HandleSiegeWarOpenCommand,				"Opens the Castle Siege War zone" },
		{ "close",				&CUser::HandleWarCloseCommand,					"Closes the active war zone" },
		{ "np_change",			&CUser::HandleLoyaltyChangeCommand,				"Change a player an loyalty" },
		{ "exp_change",			&CUser::HandleExpChangeCommand,					"Change a player an exp" },
		{ "noah_change",		&CUser::HandleGoldChangeCommand,				"Change a player an gold" },
		{ "exp_add",			&CUser::HandleExpAddCommand,					"Sets the server-wide XP event. If bonusPercent is set to 0, the event is ended. Arguments: bonusPercent" },
		{ "np_add",				&CUser::HandleNPAddCommand,						"Sets the server-wide NP event. If bonusPercent is set to 0, the event is ended. Arguments: bonusPercent" },
		{ "money_add",			&CUser::HandleMoneyAddCommand,					"Sets the server-wide coin event. If bonusPercent is set to 0, the event is ended. Arguments: bonusPercent" },
		{ "permitconnect",		&CUser::HandlePermitConnectCommand,				"Player unban" },
		{ "tp_all",				&CUser::HandleTeleportAllCommand,				"Players send to home zone." },
		{ "summonknights",		&CUser::HandleKnightsSummonCommand,				"Teleport the clan users. Arguments: clan name" },
		{ "warresult",			&CUser::HandleWarResultCommand,					"Set result for War"},
		{ "resetranking",		&CUser::HandleResetPlayerRankingCommand,		"Reset player ranking. Arguments : Zone ID"},
		{ "giveachieve",		&CUser::HandleGiveAchieveCommand,				"Gives aAchieve to User"},
		{ "test",				&CUser::HandlePacketCommand,					"to send packets for Test"}
	};

	init_command_table(CUser, commandTable, s_commandTable);
}

void CUser::CleanupChatCommands() { free_command_table(s_commandTable); }

void CUser::Chat(Packet & pkt)
{
	Packet result;
	uint16 sessID;
	uint8 type = pkt.read<uint8>(), bOutType = type, seekingPartyOptions, bNation;
	string chatstr, finalstr, strSender, * strMessage, chattype;
	CUser *pUser;
	CKnights * pKnights;
	DateTime time;

	bool isAnnouncement = false;

	if (isMuted() || (GetZoneID() == ZONE_PRISON && !isGM()))
		return;

	pkt >> chatstr;
	if (chatstr.empty() || chatstr.size() > 128)
		return;

	if (isGM() && ProcessChatCommand(chatstr))
	{
		chattype = "GAME MASTER";
		g_pMain->WriteGMLogFile(string_format("[ %s - %d:%d:%d ] %s : %s ( Zone=%d, X=%d, Z=%d )\n",chattype.c_str(),time.GetHour(),time.GetMinute(),time.GetSecond(),GetName().c_str(),chatstr.c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ())));
		return;
	}

	if (type == SEEKING_PARTY_CHAT)
		pkt >> seekingPartyOptions;

	if (type == PUBLIC_CHAT || type == ANNOUNCEMENT_CHAT)
	{
		if (!isGM())
			return;

		if (type == ANNOUNCEMENT_CHAT)
			type = WAR_SYSTEM_CHAT;

		bOutType = type;

		g_pMain->GetServerResource(IDP_ANNOUNCEMENT, &finalstr, chatstr.c_str());
		isAnnouncement = true;
	}


	if (isAnnouncement)
	{
		strMessage = &finalstr;
		bNation = KARUS;
		sessID = -1;
	}
	else
	{
		strMessage = &chatstr;
		strSender = GetName();
		bNation = GetNation();
		sessID = GetSocketID();
	}

	if (type == GENERAL_CHAT && isGM())
		bOutType = GM_CHAT;

	ChatPacket::Construct(&result, bOutType, strMessage, &strSender, bNation, sessID);

	switch (type) 
	{
	case GENERAL_CHAT:
		g_pMain->Send_NearRegion(&result, GetMap(), GetRegionX(), GetRegionZ(), GetX(), GetZ(), nullptr,  m_bEventRoom);
		chattype = "GENERAL_CHAT";
		break;

	case PRIVATE_CHAT:
		{
			pUser = g_pMain->GetUserPtr(m_sPrivateChatUser);
			if (pUser == nullptr || !pUser->isInGame()) 
				return;

			chattype = "PRIVATE_CHAT";
		}
	case COMMAND_PM_CHAT:
		{
			if (type == COMMAND_PM_CHAT && GetFame() != COMMAND_CAPTAIN)
				return;

			pUser = g_pMain->GetUserPtr(m_sPrivateChatUser);
			if (pUser != nullptr) 
				pUser->Send(&result);
		}
		break;
	case PARTY_CHAT:
		if (isInParty())
		{
			g_pMain->Send_PartyMember(GetPartyID(), &result);
			chattype = "PARTY_CHAT";
		}
		break;
	case SHOUT_CHAT:
		if (m_sMp < (m_iMaxMp / 5))
			break;

		if (!isGM()
			&& GetLevel() < 35
			&& !GoldLose(SHOUT_COIN_REQUIREMENT))
			break;

		MSpChange(-(m_iMaxMp / 5));
		SendToRegion(&result);
		chattype = "SHOUT_CHAT";
		break;
	case KNIGHTS_CHAT:
		if (isInClan())
		{
			pKnights = g_pMain->GetClanPtr(GetClanID());
			g_pMain->Send_KnightsMember(GetClanID(), &result);
			chattype = "KNIGHTS_CHAT";
		}
		break;
	case CLAN_NOTICE:
		if (isInClan() 
			&& isClanLeader())
		{
			pKnights = g_pMain->GetClanPtr(GetClanID());
			if (pKnights == nullptr)
				return;

			pKnights->UpdateClanNotice(chatstr);
		}
		break;
	case PUBLIC_CHAT:
	case ANNOUNCEMENT_CHAT:
		if (isGM())
			g_pMain->Send_All(&result);
		break;
	case COMMAND_CHAT:
		if (GetFame() == COMMAND_CAPTAIN)
		{
			g_pMain->Send_CommandChat(&result, m_bNation, this);
			chattype = "COMMAND_CHAT";
		}
		break;
	case MERCHANT_CHAT:
		if (isMerchanting())
			SendToRegion(&result);
		break;
	case ALLIANCE_CHAT:
		if (isInClan())
		{
			pKnights = g_pMain->GetClanPtr(GetClanID());
			if (pKnights != nullptr && pKnights->isInAlliance())
				g_pMain->Send_KnightsAlliance(pKnights->GetAllianceID(), &result);
			chattype = "ALLIANCE_CHAT";
		}
		break;
	case WAR_SYSTEM_CHAT:
		if (isGM())
			g_pMain->Send_All(&result);
		break;
	case SEEKING_PARTY_CHAT:
		if (m_bNeedParty == 2)
		{
			Send(&result);
			g_pMain->Send_Zone_Matched_Class(&result, GetZoneID(), this, GetNation(), seekingPartyOptions);
		}
		break;
	case NOAH_KNIGHTS:
		if (GetLevel() > 50)
			break;
		g_pMain->NoahKnights(&result);
		chattype = "NOAH_KNIGHTS";
		break;
	case CHATROM_CHAT:
		  ChatRoomChat(strMessage,strSender); 
		  chattype = "CHATROM_CHAT";
		  break; 
	}

	if (!chattype.empty())
	{
		if (pUser && type == 2)
			g_pMain->WriteChatLogFile(string_format("[ %s - %d:%d:%d ] %s > %s : %s ( Zone=%d, X=%d, Z=%d )\n",chattype.c_str(),time.GetHour(),time.GetMinute(),time.GetSecond(),strSender.c_str(),pUser->GetName().c_str(),chatstr.c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ())));
		else if (pKnights && (type == 6 || type == 15))
			g_pMain->WriteChatLogFile(string_format("[ %s - %d:%d:%d ] %s > %s : %s ( Zone=%d, X=%d, Z=%d )\n",chattype.c_str(),time.GetHour(),time.GetMinute(),time.GetSecond(),strSender.c_str(),pKnights->GetName().c_str(),chatstr.c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ())));
		else
			g_pMain->WriteChatLogFile(string_format("[ %s - %d:%d:%d ] %s : %s ( Zone=%d, X=%d, Z=%d )\n",chattype.c_str(),time.GetHour(),time.GetMinute(),time.GetSecond(),strSender.c_str(),chatstr.c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ())));
	}
}

void CUser::ChatTargetSelect(Packet & pkt)
{
	uint8 type = pkt.read<uint8>();

	if (type == 1)
	{
		Packet result(WIZ_CHAT_TARGET, type);
		std::string strUserID;
		pkt >> strUserID;
		if (strUserID.empty() || strUserID.size() > MAX_ID_SIZE)
			return;

		CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
		if (pUser == nullptr || pUser == this)
			result << int16(0); 
		else if (pUser->isBlockingPrivateChat())
			result << int16(-1) << pUser->GetName();
		else
		{
			m_sPrivateChatUser = pUser->GetSocketID();
			result << int16(1) << pUser->GetName();
		}
		Send(&result);
	}
	else if (type == 3)
	{
		uint8 sSubType;
		uint8 sMessageLen;
		std::string sMessage;
		pkt >> sSubType >> sMessageLen >> sMessage;
	}
	else
	{
		m_bBlockPrivateChat = pkt.read<bool>(); 
	}
}

/**
* @brief	Sends a notice to all users in the current zone
* 			upon death.
*
* @param	pKiller	The killer.
*/
void CUser::SendDeathNotice(Unit * pKiller, DeathNoticeType noticeType) 
{
	if (pKiller == nullptr)
		return;

	Packet result(WIZ_CHAT, uint8(DEATH_NOTICE));

	result.SByte();
	result	<< GetNation()
		<< uint8(noticeType)
		<< pKiller->GetID()
		<< pKiller->GetName()
		<< GetID()
		<< GetName()
		<< uint16(GetX()) << uint16(GetZ());

	SendToZone(&result,this,pKiller->GetEventRoom(),(isInArena() ? RANGE_20M : 0.0f));
}

bool CUser::ProcessChatCommand(std::string & message)
{
	if (message.size() <= 1
			|| message[0] != CHAT_COMMAND_PREFIX
			|| message[1] == CHAT_COMMAND_PREFIX)
			return false;

	CommandArgs vargs = StrSplit(message, " ");
	std::string command = vargs.front();
	vargs.pop_front();

	STRTOLOWER(command);

	ChatCommandTable::iterator itr = s_commandTable.find(command.c_str() + 1); // skip the prefix character
	if (itr == s_commandTable.end())
		return false;

	return (this->*(itr->second->Handler))(vargs, message.c_str() + command.size() + 1, itr->second->Help);
}

COMMAND_HANDLER(CUser::HandleWarResultCommand) { return !isGM() ? false : g_pMain->HandleWarResultCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleWarResultCommand)
{
	if (vargs.size() < 1)
	{
		printf("Using Sample : +warresult 1/2 (KARUS/HUMAN)\n");
		return true;
	}
	
	if (!isWarOpen())
	{
		printf("Warning : Battle is not open.\n");
		return true;
	}

	uint8 winner_nation;
	winner_nation = atoi(vargs.front().c_str());
	
	if (winner_nation > 0 && winner_nation < 3)
		BattleZoneResult(winner_nation);
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleGiveItemCommand)
	{
	if (vargs.size() < 2)
	{
		printf("Using Sample : /give_item CharacterName ItemID StackSize.\n");
		return true;
	}

	std::string strUserID = vargs.front();
	vargs.pop_front();

	CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
	if (pUser == nullptr)
	{
		printf("Error : User is not online");
		return true;
	}

	uint32 nItemID = atoi(vargs.front().c_str());
	vargs.pop_front();
	_ITEM_TABLE *pItem = g_pMain->GetItemPtr(nItemID);
	if (pItem == nullptr)
	{
		return true;
	}

	uint16 sCount = 1;
	if (!vargs.empty())
	{
		sCount = atoi(vargs.front().c_str());
		vargs.pop_front();
	}

	uint32 Time = 0;
	if (!vargs.empty())
		Time = atoi(vargs.front().c_str());


	if (!pUser->GiveItem(nItemID, sCount, true, Time))
	{
	}

	return true;
}

COMMAND_HANDLER(CUser::HandleGiveItemCommand)
{
	if (!isGM())
		return false;

	if (vargs.size() < 2)
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +mind_start CharacterName ItemID StackSize");
		return true;
	}

	std::string strUserID = vargs.front();
	vargs.pop_front();

	CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
	if (pUser == nullptr)
	{
		g_pMain->SendHelpDescription(this, "Error : User is not online");
		return true;
	}

	uint32 nItemID = atoi(vargs.front().c_str());
	vargs.pop_front();
	_ITEM_TABLE *pItem = g_pMain->GetItemPtr(nItemID);
	if (pItem == nullptr)
	{
		return true;
	}

	uint16 sCount = 1;
	if (!vargs.empty())
	{
		sCount = atoi(vargs.front().c_str());
		vargs.pop_front();
	}

	uint32 Time = 0;
	if (!vargs.empty())
		Time = atoi(vargs.front().c_str());


	if (!pUser->GiveItem(nItemID, sCount, true, Time))
		g_pMain->SendHelpDescription(this, "Error : Item couldn't be added");

	return true;
}

COMMAND_HANDLER(CUser::HandleZoneChangeCommand)
{
	if (!isGM())
		return false;

	if (vargs.empty())
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +zonechange ZoneNumber");
		return true;
	}

	int nZoneID = atoi(vargs.front().c_str());
	
	_START_POSITION * pStartPosition = g_pMain->GetStartPosition(nZoneID);
	if (pStartPosition == nullptr) 
		return false;
	
	ZoneChange(nZoneID, 
		(float)(GetNation() == KARUS ? pStartPosition->sKarusX : pStartPosition->sElmoradX + myrand(0, pStartPosition->bRangeX)), 
		(float)(GetNation() == KARUS ? pStartPosition->sKarusZ : pStartPosition->sElmoradZ + myrand(0, pStartPosition->bRangeZ)));

	return true;
}

COMMAND_HANDLER(CUser::HandleMonsterSummonCommand)
{
	if (!isGM())
		return false;

	if (vargs.empty())
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +monsummon MonsterSID Count");
		return true;
	}

	int sSid = 0;
	uint16 sCount = 1;

	if (vargs.size() == 1)
		sSid = atoi(vargs.front().c_str());

	if (vargs.size() == 2)
	{
		sSid = atoi(vargs.front().c_str());
		vargs.pop_front();
		sCount = atoi(vargs.front().c_str());
	}
	
	g_pMain->SpawnEventNpc(sSid, true, GetZoneID(), GetX(), GetY(), GetZ(),sCount);

	return true;
}

COMMAND_HANDLER(CUser::HandleNPCSummonCommand)
{
	if (!isGM())
		return false;

	if (vargs.empty())
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +npcsummon NPCSID");
		return true;
	}

	int sSid = atoi(vargs.front().c_str());
	g_pMain->SpawnEventNpc(sSid, false, GetZoneID(), GetX(), GetY(), GetZ());

	return true;
}

COMMAND_HANDLER(CUser::HandleMonKillCommand)
{
	if (!isGM())
		return false;
	
	if (GetTargetID() == 0 && GetTargetID() < NPC_BAND)
	{
		g_pMain->SendHelpDescription(this, "Using Sample : Select a NPC or Monster than use +monkills");
		return false;
	}
	
	CNpc *pNpc = g_pMain->GetNpcPtr(GetTargetID());
	
	if (pNpc)
		g_pMain->KillNpc(GetTargetID());
	
	return true;
}

bool CGameServerDlg::ProcessServerCommand(std::string & message)
{
	if (message.size() <= 1
			|| message[0] != SERVER_COMMAND_PREFIX)
			return false;

	CommandArgs vargs = StrSplit(message, " ");
	std::string command = vargs.front();
	vargs.pop_front();

	STRTOLOWER(command);

	ServerCommandTable::iterator itr = s_commandTable.find(command.c_str() + 1);
	if (itr == s_commandTable.end())
		return false;

	return (this->*(itr->second->Handler))(vargs, message.c_str() + command.size() + 1, itr->second->Help);
}

COMMAND_HANDLER(CGameServerDlg::HandleNoticeCommand)
{
	if (vargs.empty())
		return true;

	SendNotice(args);
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleBdwOpenCommand)
{
	g_pMain->pTempleEvent.ActiveEvent = TEMPLE_EVENT_BORDER_DEFENCE_WAR;
	g_pMain->pTempleEvent.ZoneID = ZONE_BORDER_DEFENSE_WAR;
	g_pMain->m_nTempleEventRemainSeconds = 10;
	g_pMain->TempleEventStart();

	Sleep(10000);
	g_pMain->m_nTempleEventRemainSeconds = 0; 
	g_pMain->pTempleEvent.LastEventRoom = 1;
	g_pMain->pTempleEvent.isActive = true;
	g_pMain->TempleEventStart();
	g_pMain->TempleEventTeleportUsers();
	g_pMain->TempleEventSummon();
	return true;
}


COMMAND_HANDLER(CUser::HandleBdwOpenCommand)
{
	if (!isGM())
		return false;

	g_pMain->pTempleEvent.ActiveEvent = TEMPLE_EVENT_BORDER_DEFENCE_WAR;
	g_pMain->pTempleEvent.ZoneID = ZONE_BORDER_DEFENSE_WAR;
	g_pMain->m_nTempleEventRemainSeconds = 10;
	g_pMain->TempleEventStart();

	Sleep(10000);
	g_pMain->m_nTempleEventRemainSeconds = 0; 
	g_pMain->pTempleEvent.LastEventRoom = 1;
	g_pMain->pTempleEvent.isActive = true;
	g_pMain->TempleEventStart();
	g_pMain->TempleEventTeleportUsers();
	g_pMain->TempleEventSummon();

	return true;
}


COMMAND_HANDLER(CGameServerDlg::HandleNoticeallCommand)
{
	if (vargs.empty())
		return true;

	SendAnnouncement(args);
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleKillUserCommand)
{
	if (vargs.empty())
	{
		printf("Using Sample : +kill CharacterName\n");
		return true;
	}

	std::string strUserID = vargs.front();
	CUser *pUser = GetUserPtr(strUserID, TYPE_CHARACTER);
	if (pUser == nullptr)
	{
		printf("Error : User is not online\n");
		return true;
	}

	pUser->Disconnect();

	return true;
}


COMMAND_HANDLER(CUser::HandleWar1OpenCommand) { return !isGM() ? false : g_pMain->HandleWar1OpenCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleWar1OpenCommand)
{
	BattleZoneOpen(BATTLEZONE_OPEN, 1);
	LunarGoldShells();
	return true;
}

COMMAND_HANDLER(CUser::HandleWar2OpenCommand) { return !isGM() ? false : g_pMain->HandleWar2OpenCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleWar2OpenCommand)
{
	BattleZoneOpen(BATTLEZONE_OPEN, 2);
	LunarGoldShells();
	return true;
}

COMMAND_HANDLER(CUser::HandleWar3OpenCommand) { return !isGM() ? false : g_pMain->HandleWar3OpenCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleWar3OpenCommand)
{
	BattleZoneOpen(BATTLEZONE_OPEN, 3);
	LunarGoldShells();
	return true;
}

COMMAND_HANDLER(CUser::HandleWar4OpenCommand) { return !isGM() ? false : g_pMain->HandleWar4OpenCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleWar4OpenCommand)
{
	BattleZoneOpen(BATTLEZONE_OPEN, 4);
	LunarGoldShells();
	return true;
}

COMMAND_HANDLER(CUser::HandleWar5OpenCommand) { return !isGM() ? false : g_pMain->HandleWar5OpenCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleWar5OpenCommand)
{
	BattleZoneOpen(BATTLEZONE_OPEN, 5);
	LunarGoldShells();
	return true;
}

COMMAND_HANDLER(CUser::HandleWar6OpenCommand) { return !isGM() ? false : g_pMain->HandleWar6OpenCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleWar6OpenCommand)
{
	BattleZoneOpen(BATTLEZONE_OPEN, 6);
	LunarGoldShells();
	return true;
}

COMMAND_HANDLER(CUser::HandleSnowWarOpenCommand) { return !isGM() ? false : g_pMain->HandleSnowWarOpenCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleSnowWarOpenCommand)
{
	BattleZoneOpen(SNOW_BATTLEZONE_OPEN);
	return true;
}

COMMAND_HANDLER(CUser::HandleSnowWarCloseCommand) { return !isGM() ? false : g_pMain->HandleSnowWarCloseCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleSnowWarCloseCommand)
{
	SnowBattleZoneClose();
	return true;
}

COMMAND_HANDLER(CUser::HandleSiegeWarOpenCommand) { return !isGM() ? false : g_pMain->HandleSiegeWarOpenCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleSiegeWarOpenCommand)
{
	CastleSiegeWarZoneOpen(CLAN_BATTLE);
	return true;
}

COMMAND_HANDLER(CUser::HandleWarCloseCommand) { return !isGM() ? false : g_pMain->HandleWarCloseCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleWarCloseCommand)
{
	BattleZoneClose();
	return true;
}

COMMAND_HANDLER(CUser::HandleLoyaltyChangeCommand)
{
	if (!isGM())
		return false;

	if (vargs.size() < 2)
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +np_change CharacterName Loyalty(+/-)");
		return true;
	}

	std::string strUserID = vargs.front();
	vargs.pop_front();

	CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
	if (pUser == nullptr)
	{
		g_pMain->SendHelpDescription(this, "Error : User is not online");
		return true;
	}

	uint32 nLoyalty = atoi(vargs.front().c_str());

	if (nLoyalty != 0)
		pUser->SendLoyaltyChange(nLoyalty, false);

	return true;
}

COMMAND_HANDLER(CUser::HandleExpChangeCommand)
{
	if (!isGM())
		return false;

	if (vargs.size() < 2)
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +exp_change CharacterName Exp(+/-)");
		return true;
	}

	std::string strUserID = vargs.front();
	vargs.pop_front();

	CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
	if (pUser == nullptr)
	{
		g_pMain->SendHelpDescription(this, "Error : User is not online");
		return true;
	}

	int64 nExp = atoi(vargs.front().c_str());

	if (nExp != 0)
		pUser->ExpChange(nExp);

	return true;
}

COMMAND_HANDLER(CUser::HandleGoldChangeCommand)
{
	if (!isGM())
		return false;

	if (vargs.size() < 2)
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +gold_change CharacterName Gold(+/-)");
		return true;
	}

	std::string strUserID = vargs.front();
	vargs.pop_front();

	CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
	if (pUser == nullptr)
	{
		g_pMain->SendHelpDescription(this, "Error : User is not online");
		return true;
	}

	uint32 nGold = atoi(vargs.front().c_str());

	if (nGold != 0)
	{
		if (nGold > 0)
			pUser->GoldGain(nGold);
		else
			pUser->GoldLose(nGold);
	}

	return true;
}

COMMAND_HANDLER(CUser::HandleExpAddCommand) { return !isGM() ? false : g_pMain->HandleExpAddCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleExpAddCommand)
{
	if (vargs.empty())
		return true;
	

	g_pMain->m_byExpEventAmount = (uint8) atoi(vargs.front().c_str());

	if (g_pMain->m_byExpEventAmount == 0)
		return true;

	g_pMain->SendFormattedResource(IDS_EXP_REPAY_EVENT, Nation::ALL, false, g_pMain->m_byExpEventAmount);
	return true;
}

COMMAND_HANDLER(CUser::HandleNPAddCommand) { return !isGM() ? false : g_pMain->HandleNPAddCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleNPAddCommand)
{
	if (vargs.empty())
		return true;

	g_pMain->m_byNPEventAmount = (uint8) atoi(vargs.front().c_str());

	if (g_pMain->m_byNPEventAmount == 0)
		return true;

	g_pMain->SendFormattedResource(IDS_NP_REPAY_EVENT, Nation::ALL, false, g_pMain->m_byNPEventAmount);
	return true;
}

COMMAND_HANDLER(CUser::HandleMoneyAddCommand) { return !isGM() ? false : g_pMain->HandleMoneyAddCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleMoneyAddCommand)
{
	if (vargs.empty())
		return true;

	g_pMain->m_byCoinEventAmount = (uint8) atoi(vargs.front().c_str());

	if (g_pMain->m_byCoinEventAmount == 0)
		return true;

	g_pMain->SendFormattedResource(IDS_MONEY_REPAY_EVENT, Nation::ALL, false, g_pMain->m_byCoinEventAmount);
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleMonSummonCommand)
{
	if (vargs.size() < 1)
	{
		printf("Using Sample : /monsummon MonsterID Zoneid X Y");
		return true;
	}
	int sSid = 0;
	int nZoneID = 0;
	int nX = 0;
	int nZ = 0;

	if (vargs.size() == 1)
		sSid = atoi(vargs.front().c_str());

	if (vargs.size() == 2)
	{
		sSid = atoi(vargs.front().c_str());
		vargs.pop_front();
		nZoneID = atoi(vargs.front().c_str());
	}

	if (vargs.size() == 3)
	{
		sSid = atoi(vargs.front().c_str());
		vargs.pop_front();
		nZoneID = atoi(vargs.front().c_str());
		vargs.pop_front();
		nX = atoi(vargs.front().c_str());
	}

	if (vargs.size() == 4)
	{
		sSid = atoi(vargs.front().c_str());
		vargs.pop_front();
		nZoneID = atoi(vargs.front().c_str());
		vargs.pop_front();
		nX = atoi(vargs.front().c_str());
		vargs.pop_front();
		nZ = atoi(vargs.front().c_str());
	}

	if (nZoneID > 0)
		g_pMain->SpawnEventNpc(sSid, true, nZoneID, (float)nX, 0, (float)nZ);

	return true;
}

COMMAND_HANDLER(CUser::HandlePermitConnectCommand) { return !isGM() ? false : g_pMain->HandlePermitConnectCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandlePermitConnectCommand)
{
	if (vargs.size() < 1)
	{
		printf("Using Sample : +permitconnect CharacterName\n");
		return true;
	}

	std::string strUserID = vargs.front();
	vargs.pop_front();

	g_DBAgent.UpdateUserAuthority(strUserID,AUTHORITY_PLAYER);

	std::string sNoticeMessage = string_format("%s has been unbanned..!", strUserID.c_str());

	if (!sNoticeMessage.empty())
		g_pMain->SendNotice(sNoticeMessage.c_str(),Nation::ALL);

	return true;
}

COMMAND_HANDLER(CUser::HandleTeleportAllCommand)
{
	if (!isGM())
		return false;

	if (vargs.size() < 1)
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +tp_all ZoneNumber | +tp_all ZoneNumber TargetZoneNumber");
		return true;
	}

	int nZoneID = 0;
	int nTargetZoneID = 0;

	if (vargs.size() == 1)
		nZoneID = atoi(vargs.front().c_str());

	if (vargs.size() == 2)
	{
		nZoneID = atoi(vargs.front().c_str());
		vargs.pop_front();
		nTargetZoneID = atoi(vargs.front().c_str());
	}

	if (nZoneID > 0 || nTargetZoneID > 0)
		g_pMain->KickOutZoneUsers(nZoneID,nTargetZoneID);
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleTeleportAllCommand)
{
	if (vargs.size() < 1)
	{
		printf("Using Sample : /tp_all ZoneNumber | /tp_all ZoneNumber TargetZoneNumber.\n");
		return true;
	}

	int nZoneID = 0;
	int nTargetZoneID = 0;

	if (vargs.size() == 1)
		nZoneID = atoi(vargs.front().c_str());

	if (vargs.size() == 2)
	{
		nZoneID = atoi(vargs.front().c_str());
		vargs.pop_front();
		nTargetZoneID = atoi(vargs.front().c_str());
	}

	if (nZoneID > 0 || nTargetZoneID > 0)
		g_pMain->KickOutZoneUsers(nZoneID,nTargetZoneID);
	return true;
}

COMMAND_HANDLER(CUser::HandleKnightsSummonCommand)
{
	if (!isGM())
		return false;

	if(vargs.empty())
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +summonknights ClanName");
		return true;
	}

	CKnights * pKnights;
	foreach_stlmap (itr,g_pMain->m_KnightsArray)
	{
		if(itr->second->GetName() == vargs.front().c_str())
		{
			pKnights = g_pMain->GetClanPtr(itr->first);
			break;
		}
	}

	if(pKnights == nullptr)
		return true;

	foreach_array(i,pKnights->m_arKnightsUser)
	{
		_KNIGHTS_USER *p = &pKnights->m_arKnightsUser[i];
		if (!p->byUsed || p->pSession == nullptr)
			continue;

		CUser* pUser = p->pSession;
		if(!pUser->isInGame() || pUser->GetName() == GetName())
			continue;

		pUser->ZoneChange(GetZoneID(), m_curx, m_curz);
	}

	return true;
}

COMMAND_HANDLER(CUser::HandleResetPlayerRankingCommand)
{
	if (!isGM())
		return false;
	
	if(vargs.empty())
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +resetranking ZoneID");
		return true;
	}
	
	uint8 nZoneID;
	nZoneID = atoi(vargs.front().c_str());
	
	if (nZoneID > 0)
		g_pMain->ResetPlayerRankings(nZoneID);
	
	return true;
}

COMMAND_HANDLER(CUser::HandleGiveAchieveCommand)
{
	if (!isGM())
		return false;

	if (vargs.size() < 2)
	{
		g_pMain->SendHelpDescription(this, "Using Sample : +giveachieve CharacterName MainID");
		return true;
	}

	std::string strUserID = vargs.front();
	vargs.pop_front();

	CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
	if (pUser == nullptr)
	{
		g_pMain->SendHelpDescription(this, "Error : User is not online");
		return true;
	}

	uint16 nAchieveID = atoi(vargs.front().c_str());
		vargs.pop_front();

	if (nAchieveID < 1)
	{
		g_pMain->SendHelpDescription(this, "Error : AchieveID 0 not found");
		return true;
	}
	else
		pUser->GiveAchieve(nAchieveID);

	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleResetAchieveCommand)
{
	if (vargs.size() < 1)
	{
		printf("Using Sample : +resetachieve CharacterName \n");
		return true;
	}

	std::string strUserID = vargs.front();
	vargs.pop_front();

	CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
	if (pUser == nullptr)
	{
		printf("Error : User is not online \n");
		return true;
	}

	pUser->ResetAchieve();

	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleGiveAchieveCommand)
{
	if (vargs.size() < 2)
	{
		printf("Using Sample : +giveachieve CharacterName MainID \n");
		return true;
	}

	std::string strUserID = vargs.front();
	vargs.pop_front();

	CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
	if (pUser == nullptr)
	{
		printf("Error : User is not online \n");
		return true;
	}

	uint16 nAchieveID = atoi(vargs.front().c_str());
		vargs.pop_front();

		if (nAchieveID < 1)
	{
		printf("Error : not find value 0");
		return true;
	}
	else
		pUser->GiveAchieve(nAchieveID);

	return true;
}

COMMAND_HANDLER(CUser::HandlePacketCommand)
{
	if (!isGM())
		return false;

	UpdateStatusPacket();

	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleDiscountCommand)
{
	m_sDiscount = 1;
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleGlobalDiscountCommand)
{
	m_sDiscount = 2;
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleDiscountOffCommand)
{
	m_sDiscount = 0;
	return true;
}

COMMAND_HANDLER(CUser::HandleCaptainCommand) { return !isGM() ? false : g_pMain->HandleCaptainCommand(vargs, args, description); }
COMMAND_HANDLER(CGameServerDlg::HandleCaptainCommand)
{
	m_KnightsRatingArray[KARUS_ARRAY].DeleteAllData();
	m_KnightsRatingArray[ELMORAD_ARRAY].DeleteAllData();
	LoadKnightsRankTable(true, true);
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleSantaCommand)
{
	m_bSantaOrAngel = FLYING_SANTA;
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleSantaOffCommand)
{
	m_bSantaOrAngel = FLYING_NONE;
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleAngelCommand)
{
	m_bSantaOrAngel = FLYING_ANGEL;
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandlePermanentChatCommand)
{
	if (vargs.empty())
	{
		return true;
	}

	SetPermanentMessage("%s", args);
	return true;
}

void CGameServerDlg::SendHelpDescription(CUser *pUser, std::string sHelpMessage)
{
	if (pUser == nullptr || sHelpMessage == "")
		return;

	Packet result(WIZ_CHAT, (uint8)PUBLIC_CHAT);
	result << pUser->GetNation() << pUser->GetSocketID() << (uint8)0 << sHelpMessage;
	pUser->Send(&result);
}

void CGameServerDlg::SetPermanentMessage(const char * format, ...)
{
	char buffer[128];
	va_list ap;
	va_start(ap, format);
	vsnprintf(buffer, 128, format, ap);
	va_end(ap);

	m_bPermanentChatMode = true;
	m_strPermanentChat = buffer;

	Packet result;
	ChatPacket::Construct(&result, PERMANENT_CHAT, &m_strPermanentChat);
	Send_All(&result);
}

COMMAND_HANDLER(CGameServerDlg::HandlePermanentChatOffCommand)
{
	Packet result;
	ChatPacket::Construct(&result, END_PERMANENT_CHAT);
	m_bPermanentChatMode = false;
	Send_All(&result);
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleReloadNoticeCommand)
{
	LoadNoticeData();
	LoadNoticeUpData();

	SessionMap sessMap = g_pMain->m_socketMgr.GetActiveSessionMap();
	foreach (itr, sessMap)
	{
		CUser * pUser = TO_USER(itr->second);
		if (pUser->isInGame())
			pUser->SendNotice();
			pUser->TopSendNotice();
	}
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleReloadTablesCommand)
{
	m_StartPositionArray.DeleteAllData();
	LoadStartPositionTable();

	m_StartPositionRandomArray.DeleteAllData();
	LoadStartPositionRandomTable();

	m_ItemExchangeArray.DeleteAllData();
	LoadItemExchangeTable();

	m_ItemUpgradeArray.DeleteAllData();
	LoadItemUpgradeTable();

	m_EventTriggerArray.DeleteAllData();
	LoadEventTriggerTable();

	m_ServerResourceArray.DeleteAllData();
	LoadServerResourceTable();

	m_MonsterChallengeArray.DeleteAllData();
	LoadMonsterChallengeTable();

	m_MonsterChallengeSummonListArray.DeleteAllData();
	LoadMonsterChallengeSummonListTable();

	m_EventTimesArray.DeleteAllData();
	LoadEventTimesTable();

	m_MonsterRespawnListArray.DeleteAllData();
	LoadMonsterRespawnListTable();

	m_MonsterRespawnListInformationArray.DeleteAllData();
	LoadMonsterRespawnListInformationTable();

	ReloadKnightAndUserRanks();

	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleReloadMagicsCommand)
{
	m_IsMagicTableInUpdateProcess = true;
	m_MagictableArray.DeleteAllData();
	m_Magictype1Array.DeleteAllData();
	m_Magictype2Array.DeleteAllData();
	m_Magictype3Array.DeleteAllData();
	m_Magictype4Array.DeleteAllData();
	m_Magictype5Array.DeleteAllData();
	m_Magictype6Array.DeleteAllData();
	m_Magictype8Array.DeleteAllData();
	m_Magictype9Array.DeleteAllData();
	LoadMagicTable();
	LoadMagicType1();
	LoadMagicType2();
	LoadMagicType3();
	LoadMagicType4();
	LoadMagicType5();
	LoadMagicType6();
	LoadMagicType7();
	LoadMagicType8();
	LoadMagicType9();
	m_IsMagicTableInUpdateProcess = false;

	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleReloadItemOPCommand)
{
	m_IsItemOPUpdateProcess = true;
	m_ItemOpArray.DeleteAllData();
	LoadItemOpTable();
	m_IsItemOPUpdateProcess = false;

	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleReloadIlegalItemsCommand)
{
	m_IlegalItemsUpdateProcess = true;
	m_IlegalItemsArray.DeleteAllData();
	LoadIlegalItems();
	m_IlegalItemsUpdateProcess = false;

	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleReloadSiegeCommand)
{
	m_SiegeUpdateProcess = true;
	m_KnightsSiegeWarfareArray.DeleteAllData();
	LoadKnightsSiegeWarsTable();
	m_SiegeUpdateProcess = false;

	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleReloadDupeCommand)
{
	m_IsDupeUpdateProcess = true;
	m_ItemDupersArray.DeleteAllData();
	LoadItemDuper();
	m_IsDupeUpdateProcess = false;

	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleReloadQuestCommand)
{
	m_QuestHelperArray.DeleteAllData();
	LoadQuestHelperTable();
	m_QuestMonsterArray.DeleteAllData();
	LoadQuestMonsterTable();
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleReloadRanksCommand)
{
	ReloadKnightAndUserRanks();
	return true;
}

COMMAND_HANDLER(CGameServerDlg::HandleCountCommand)
{
	uint16 count = 0;
	SessionMap sessMap = g_pMain->m_socketMgr.GetActiveSessionMap();
	foreach (itr, sessMap)
	{
     if (TO_USER(itr->second)->isInGame())
       count++;
	}

	printf("Online User Count : %d\n",count);
	return true;
 }

void CGameServerDlg::SendFormattedResource(uint32 nResourceID, uint8 byNation, bool bIsNotice, ...)
{
	_SERVER_RESOURCE *pResource = m_ServerResourceArray.GetData(nResourceID);
	if (pResource == nullptr)
		return;

	string buffer;
	va_list ap;
	va_start(ap, bIsNotice);
	_string_format(pResource->strResource, &buffer, ap);
	va_end(ap);

	if (bIsNotice)
		SendNotice(buffer.c_str(), byNation);
	else
		SendAnnouncement(buffer.c_str(), byNation);
}
