#include "stdafx.h"
#include "Map.h"
#include "DBAgent.h"
#include "../shared/DateTime.h"

using std::string;

void CUser::SelNationToAgent(Packet & pkt)
{
	Packet result(WIZ_SEL_NATION);
	uint8 nation = pkt.read<uint8>();
	if (nation != KARUS && nation != ELMORAD)
	{
		result << uint8(0);
		Send(&result);
		return;
	}

	result << nation; 
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::AllCharInfo(Packet &pkt)
{
	uint8 opcode = pkt.read<uint8>();
	//TRACE("Opecode = %d", opcode);

	switch (opcode)
	{
	case 1:
		AllCharInfoToAgent();
		break;
	case 3:
		CharacterLocationSend();
		break;
	case 4:
		CharacterLocationRecv(pkt);
		break;
	default:
		TRACE("Unhandle AllCharInfo Opecode %d", opcode);
		break;
	}
}

void CUser::AllCharInfoToAgent()
{
	Packet result(WIZ_ALLCHAR_INFO_REQ);
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::CharacterLocationSend()
{
	Packet result(WIZ_ALLCHAR_INFO_REQ, uint8(3));

	string strCharID1, strCharID2, strCharID3, strCharID4;

	g_DBAgent.GetAllCharID(m_strAccountID, strCharID1, strCharID2, strCharID3, strCharID4);
	
	if(strCharID1.length() != 0)
		result << strCharID1;
	else
		result << "";
	if(strCharID2.length() != 0)
		result << strCharID2;
	else
		result << "";
	if(strCharID3.length() != 0)
		result << strCharID3;
	else
		result << "";
	if(strCharID4.length() != 0)
		result << strCharID4;
	else
		result << "";

	Send(&result);
}

void CUser::CharacterLocationRecv(Packet & pkt)
{
	uint8 Charpos1, Charpos2, Charpos3, Charpos4;
	string strCharID1, strCharID2, strCharID3, strCharID4;
	string ID1, ID2, ID3, ID4;

	Packet result(WIZ_ALLCHAR_INFO_REQ, uint8(4));

	RobItem(ARRANGE_LINE);

	pkt >> Charpos1 >> Charpos2 >> Charpos3 >> Charpos4;

	g_DBAgent.GetAllCharID(m_strAccountID, strCharID1, strCharID2, strCharID3, strCharID4);

	if(strCharID1.length() != 0)
	{
		switch(Charpos1)
		{
		case 1:
			ID1 = strCharID1;
			break;
		case 2:
			ID2 = strCharID1;
			break;
		case 3:
			ID3 = strCharID1;
			break;
		case 4:
			ID4 = strCharID1;
			break;
		}
	}
	else
	{
		switch (Charpos1)
		{
			case 1:
			case 2:
			case 3:
			case 4:
				ID1 = "";
				break;
		}
	}
	if(strCharID2.length() != 0)
	{
		switch(Charpos2)
		{
		case 1:
			ID1 = strCharID2;
			break;
		case 2:
			ID2 = strCharID2;
			break;
		case 3:
			ID3 = strCharID2;
			break;
		case 4:
			ID4 = strCharID2;
			break;
		}
	}
	else
	{
		switch (Charpos2)
		{
			case 1:
			case 2:
			case 3:
			case 4:
				ID2 = "";
				break;
		}
	}
	if(strCharID3.length() != 0)
	{
		switch(Charpos3)
		{
		case 1:
			ID1 = strCharID3;
			break;
		case 2:
			ID2 = strCharID3;
			break;
		case 3:
			ID3 = strCharID3;
			break;
		case 4:
			ID4 = strCharID3;
			break;
		}
	}
	else
	{
		switch (Charpos3)
		{
			case 1:
			case 2:
			case 3:
			case 4:
				ID3 = "";
				break;
		}
	}
	if(strCharID4.length() != 0)
	{
		switch(Charpos4)
		{
		case 1:
			ID1 = strCharID4;
			break;
		case 2:
			ID2 = strCharID4;
			break;
		case 3:
			ID3 = strCharID4;
			break;
		case 4:
			ID4 = strCharID4;
			break;
		}
	}
	else
	{
		switch (Charpos4)
		{
			case 1:
			case 2:
			case 3:
			case 4:
				ID4 = "";
				break;
		}
	}

	g_DBAgent.SetAllCharID(m_strAccountID, ID1, ID2, ID3, ID4);

	result << uint8(1);		// 0 = Failed || 1 = Success
	Send(&result);
}

void CUser::ChangeHair(Packet & pkt)
{
	std::string strUserID;
	uint32 nHair;
	uint8 bOpcode, bFace;

	// The opcode:
	// 0 seems to be an in-game implementation for converting from old -> new hair data
	// 2 seems to be used with the hair change item(?).
	// Another note: there's 4 bytes at the end of the packet data that I can't account for (maybe a[nother] checksum?)

	pkt.SByte();
	pkt >> bOpcode >> strUserID >> bFace >> nHair;

	Packet result(WIZ_CHANGE_HAIR);
	result.SByte();
	result << bOpcode << strUserID << bFace << nHair;
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::NewCharToAgent(Packet & pkt)
{
	Packet result(WIZ_NEW_CHAR);
	uint32 nHair;
	uint16 sClass;
	uint8 bCharIndex, bRace, bFace, str, sta, dex, intel, cha, errorCode = 0;
	std::string strUserID;

	pkt	>> bCharIndex >> strUserID >> bRace >> sClass >> bFace >> nHair
		>> str >> sta >> dex >> intel >> cha;

	_CLASS_COEFFICIENT* p_TableCoefficient = g_pMain->m_CoefficientArray.GetData(sClass);

	if (bCharIndex > 3)
		errorCode = NEWCHAR_NO_MORE;
	else if (p_TableCoefficient == nullptr
		|| (str + sta + dex + intel + cha) > 300) 
		errorCode = NEWCHAR_INVALID_DETAILS;
	else if (str < 50 || sta < 50 || dex < 50 || intel < 50 || cha < 50) 
		errorCode = NEWCHAR_STAT_TOO_LOW;

	if (errorCode != 0)
	{
		result << errorCode;
		Send(&result);
		return;
	}

	result	<< bCharIndex 
		<< strUserID << bRace << sClass << bFace << nHair
		<< str << sta << dex << intel << cha;
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::DelCharToAgent(Packet & pkt)
{
	Packet result(WIZ_DEL_CHAR);
	std::string strUserID, strSocNo;
	uint8 bCharIndex;
	pkt >> bCharIndex >> strUserID >> strSocNo; 

	if (bCharIndex > 2
		|| strUserID.empty() || strUserID.size() > MAX_ID_SIZE
		|| strSocNo.empty() || strSocNo.size() > 15
		|| isClanLeader())
	{
		result << uint8(0) << uint8(-1);
		Send(&result);
		return;
	}

	// Process the deletion request in the database
	result	<< bCharIndex << strUserID << strSocNo;
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::SelCharToAgent(Packet & pkt)
{
	Packet result(WIZ_SEL_CHAR);
	std::string strUserID, strAccountID;
	uint8 bInit;

	pkt >> strAccountID >> strUserID >> bInit;
	if (strAccountID.empty() || strAccountID.size() > MAX_ID_SIZE
		|| strUserID.empty() || strUserID.size() > MAX_ID_SIZE
		|| strAccountID != m_strAccountID)
	{
		Disconnect();
		return;
	}

	// Disconnect any currently logged in sessions.
	CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);

	if (pUser && (pUser->GetSocketID() != GetSocketID()))
	{
		pUser->Disconnect();

		// And reject the login attempt (otherwise we'll probably desync char data)
		result << uint8(0);
		Send(&result);
		return;
	}

	result << strUserID << bInit;
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::SelectCharacter(Packet & pkt)
{
	Packet result(WIZ_SEL_CHAR);
	uint8 bResult, bInit;

	if (isBanned())
	{
		Disconnect();
		return;
	}

	pkt >> bResult >> bInit;
	result << bResult;

	if (bResult == 0 || !GetZoneID()) 
		goto fail_return;

	m_pMap = g_pMain->GetZoneByID(GetZoneID());
	if (GetMap() == nullptr)
		goto fail_return;

	if (g_pMain->m_nServerNo != GetMap()->m_nServerNo)
	{
		_ZONE_SERVERINFO *pInfo = g_pMain->m_ServerArray.GetData(GetMap()->m_nServerNo);
		if (pInfo == nullptr) 
			goto fail_return;

		SendServerChange(pInfo->strServerIP, bInit);
		return;
	}

	if (!g_pMain->isWarOpen() && GetFame() == COMMAND_CAPTAIN)
		m_bFame = CHIEF;

	// Disallow players from relogging in the opposite nation's home zone when an invasion's not running.
	if (((GetZoneID() != GetNation() && GetZoneID() <= ZONE_ELMORAD && !g_pMain->m_byBattleOpen)
		// also disallow players from logging back into war zones that aren't currently active...
			|| (GetMap()->isWarZone() && !g_pMain->m_byBattleOpen)
			// Chaos, bdw and juraid montuain
			|| isInTempleEventZone()
			// forgetten temple
			|| GetZoneID() == ZONE_FORGOTTEN_TEMPLE
			// Ardream, Ronark Land Base, Ronark Land, Bifrost, Krowaz Dominion.
			|| (g_pMain->m_byBattleOpen && (GetZoneID() == ZONE_ARDREAM 
			|| GetZoneID() == ZONE_RONARK_LAND_BASE
			|| GetZoneID() == ZONE_RONARK_LAND 
			|| GetZoneID() == ZONE_BIFROST
			|| GetZoneID() == ZONE_KROWAZ_DOMINION))) && !isGM())
	{
		NativeZoneReturn();
		UserDataSaveToAgent();
		Disconnect();
		return;
	}

	// Disallow players from relogging in the Delos/CZ during CSW running.
	if (!isGM() && (GetZoneID() == ZONE_DELOS && g_pMain->m_byBattleOpen == CLAN_BATTLE && !g_pMain->m_byBattleSiegeWarTeleport
		|| GetZoneID() == ZONE_DELOS  && g_pMain->m_byBattleOpen == CLAN_BATTLE  && GetClanID() <= 0
		|| GetZoneID() == ZONE_RONARK_LAND && (g_pMain->m_byBattleOpen == CLAN_BATTLE || g_pMain->m_byBattleOpen == NATION_BATTLE)))
		{
			NativeZoneReturn();
			UserDataSaveToAgent();
			Disconnect();
			return;
		}

	SetLogInInfoToDB(bInit);

	result << GetZoneID() << GetSPosX() << GetSPosZ() << GetSPosY() << g_pMain->m_byOldVictory;
	m_bSelectedCharacter = true;
	Send(&result);

	SetUserAbility(false);

	if (GetLevel() > MAX_LEVEL) 
	{
		Disconnect();
		return;
	}

	if (GetRebLevel() > 5) 
	{
		printf("Player rebirth State bad, update to 4, Player name %s", GetName().c_str());
		m_reblvl = 4;
		Disconnect();
		return;
	}

	if(m_reblvl!= 0)
		m_iMaxExp = nExpRebirth[m_reblvl];
	else
		m_iMaxExp = g_pMain->GetExpByLevel(GetLevel());

	SetRegion(GetNewRegionX(), GetNewRegionZ());

	if (GetClanID() == -1)
	{
		SetClanID(0);
		m_bFame = 0;
		return;
	}
	else if (GetClanID() != 0
		&& GetZoneID() > 2)
	{
		result.Initialize(WIZ_KNIGHTS_PROCESS);
		result << uint8(KNIGHTS_LIST_REQ) << GetClanID();
		g_pMain->AddDatabaseRequest(result, this);
	}
	return;

fail_return:
	Send(&result);
}


void CUser::SendServerChange(std::string & ip, uint8 bInit)
{
	Packet result(WIZ_SERVER_CHANGE);
	result << ip << uint16(g_pMain->m_GameServerPort) << bInit << GetZoneID() << g_pMain->m_byOldVictory;
	Send(&result);
}

// happens on character selection
void CUser::SetLogInInfoToDB(uint8 bInit)
{
	_ZONE_SERVERINFO *pInfo = g_pMain->m_ServerArray.GetData(g_pMain->m_nServerNo);
	if (pInfo == nullptr) 
	{
		Disconnect();
		return;
	}

	Packet result(WIZ_LOGIN_INFO);
	result	<< GetName() 
		<< pInfo->strServerIP << uint16(g_pMain->m_GameServerPort) << GetRemoteIP() 
		<< bInit;
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::RecvLoginInfo(Packet & pkt)
{
	int8 bResult = pkt.read<uint8>();
	if (bResult < 0)
		Disconnect();
}

// This packet actually contains the char name after the opcode
void CUser::GameStart(Packet & pkt)
{
	if (isInGame())
		return;

	uint8 opcode = pkt.read<uint8>();

	if (opcode == 1)
	{
		SendMyInfo();
		g_pMain->UserInOutForMe(this);
		g_pMain->MerchantUserInOutForMe(this);
		g_pMain->NpcInOutForMe(this);
		HandleUserInfo(pkt);
		SendNotice();
		TopSendNotice();
		SendTime();
		SendWeather();
		if (GetLevel() == 1)
			AchieveMainCount(0, 0, 0, 3);		// Valid Level 1 AchieveCount
		Packet result(WIZ_GAMESTART);
		Send(&result);
	}
	else if (opcode == 2)
	{
		m_state = GAME_STATE_INGAME;
		UserInOut(INOUT_RESPAWN);

		if (!m_bCity && m_sHp <= 0)
			m_bCity = -1;

		if (m_bCity > 0)
		{
			int level = GetLevel();
			if (m_bCity <= 100)
				level--;

			// make sure we don't exceed bounds
			if (level > MAX_LEVEL)
				level = MAX_LEVEL;
			else if (level < 1)
				level = 1;

			m_iLostExp = (g_pMain->GetExpByLevel(level) * (m_bCity % 10) / 100);
			if (((m_bCity % 10) / 100) == 1)
				m_iLostExp /= 2;
		}
		else
		{
			m_iLostExp = 0;
		}

		BlinkStart();
		SetUserAbility();

		// If we've relogged while dead, we need to make sure the client 
		// is still given the option to revive.
		if (isDead())
			SendDeathAnimation();

		g_pMain->TempleEventGetActiveEventTime(this);

		m_tGameStartTimeSavedMagic = UNIXTIME;

		m_LastX = GetX();
		m_LastZ = GetZ();
	}

	m_tHPLastTimeNormal = UNIXTIME;
}

void CUser::LoadGame(Packet & pkt)
{
    Packet result(WIZ_LOAD_GAME, uint8(1));
    result << int32(0); 
    Send(&result);
}