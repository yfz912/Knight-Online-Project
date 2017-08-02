#include "stdafx.h"
#include "DBAgent.h"

using std::string;
using std::vector;

void CGameServerDlg::SendEventRemainingTime(bool bSendAll, CUser *pUser, uint8 ZoneID)
{
	Packet result(WIZ_BIFROST,uint8(BIFROST_EVENT));
	uint16 nRemainingTime = 0;

	if (ZoneID == ZONE_BATTLE4)
		nRemainingTime = m_byBattleRemainingTime / 2;
	else if (ZoneID == ZONE_BIFROST || ZoneID ==  ZONE_RONARK_LAND)
		nRemainingTime = m_sBifrostRemainingTime;

	result << nRemainingTime;

	if (pUser)
		pUser->Send(&result);
	else if (bSendAll)
	{
		if (ZoneID == ZONE_BATTLE4)
			Send_All(&result,nullptr, 0, ZONE_BATTLE4);
		else
		{
			Send_All(&result,nullptr, 0, ZONE_RONARK_LAND);
			Send_All(&result,nullptr, 0, ZONE_BIFROST);
		}
	}
}
void CUser::CastleSiegeWarProcess(CUser * pUser)
{
	if (pUser == nullptr || GetClanID() <= 0)
		return;

	_KNIGHTS_SIEGE_WARFARE *pKnightSiegeWar = g_pMain->GetSiegeMasterKnightsPtr(1);
	CKnights * pKnights = g_pMain->GetClanPtr(pUser->m_bKnights);

	pKnightSiegeWar->sMasterKnights = pKnights->m_sIndex;
	
	g_pMain->UpdateSiege(pKnightSiegeWar->sCastleIndex, pKnightSiegeWar->sMasterKnights, pKnightSiegeWar->bySiegeType, pKnightSiegeWar->byWarDay, pKnightSiegeWar->byWarTime, pKnightSiegeWar->byWarMinute);
	g_pMain->m_KnightsSiegeWarfareArray.GetData(pKnightSiegeWar->sMasterKnights);

	g_pMain->m_SiegeWarWinKnightsNotice = pKnights->GetName();
	g_pMain->Announcement(IDS_NPC_GUIDON_DESTORY);
	g_pMain->m_byBattleSiegeWarMomument = true;
	g_pMain->m_byBattleSiegeWarTown = true;
	g_pMain->m_lastCrystalKilled = UNIXTIME;
	//g_pMain->KickOutZoneUsers(ZONE_DELOS, ZONE_DELOS);
	if (pKnightSiegeWar != nullptr)
	{
		Packet result(WIZ_SIEGE, uint8(2));
		result << uint8(0) << pKnights->GetID() << pKnights->m_sMarkVersion;
		g_pMain->Send_Zone(&result,ZONE_DELOS);
	}
}
void CUser::BifrostProcess(CUser * pUser)
{
	if (pUser == nullptr)
		return;

	if (g_pMain->m_BifrostVictory == 0 && g_pMain->m_bAttackBifrostMonument)
	{
		g_pMain->m_sBifrostTime = g_pMain->m_xBifrostTime;
		g_pMain->m_sBifrostRemainingTime = g_pMain->m_sBifrostTime;
		g_pMain->m_BifrostVictory = pUser->GetNation();
		g_pMain->SendFormattedResource(pUser->GetNation() == ELMORAD ? IDS_BEEF_ROAST_VICTORY_ELMORAD : IDS_BEEF_ROAST_VICTORY_KARUS, Nation::ALL,false);
		g_pMain->SendEventRemainingTime(true, nullptr, ZONE_BIFROST);

		if (g_pMain->m_bAttackBifrostMonument)
			g_pMain->m_bAttackBifrostMonument = false;
	}
	else if (g_pMain->m_BifrostVictory == 1 || g_pMain->m_BifrostVictory == 2) 
	{
		if (pUser->GetNation() != g_pMain->m_BifrostVictory && g_pMain->m_bAttackBifrostMonument)
		{
			g_pMain->m_BifrostVictory = 3;
			g_pMain->SendFormattedResource(pUser->GetNation() == ELMORAD ? IDS_BEEF_ROAST_VICTORY_ELMORAD : IDS_BEEF_ROAST_VICTORY_KARUS, Nation::ALL,false);

			if (g_pMain->m_bAttackBifrostMonument)
				g_pMain->m_bAttackBifrostMonument = false;
		}
	}
}

void CUser::TempleProcess(Packet &pkt )
{
	uint8 opcode = pkt.read<uint8>();

	switch (opcode)
	{
	case MONSTER_STONE:
		MonsterStoneProcess();
		break;
	case TEMPLE_EVENT_JOIN:
		TempleOperations(opcode);
		break;
	case TEMPLE_EVENT_DISBAND:
		TempleOperations(opcode);
		break;
	}
}

void CUser::MonsterStoneProcess()
{
	if(CheckExistItem(ITEM_MONSTER_STONE,1))
	{
		RobItem(ITEM_MONSTER_STONE,1);
		ZoneChange(myrand(81,83),0.0f,0.0f);
		if (GetZoneID() == ZONE_STONE1)
			CheckWaiting(81, 1501);
		else if (GetZoneID() == ZONE_STONE2)
			CheckWaiting(82, 1501);
		else if (GetZoneID() == ZONE_STONE3)
			CheckWaiting(83, 1501);
	}
} 

void CUser::TempleOperations(uint8 bType)
{
	uint16 nActiveEvent = (uint16)g_pMain->pTempleEvent.ActiveEvent;

	uint8 bResult = 1;
	Packet result(WIZ_EVENT);

	if(bType == TEMPLE_EVENT_JOIN && !isEventUser())
	{
		if (nActiveEvent == TEMPLE_EVENT_CHAOS)
		{
			if (CheckExistItem(CHAOS_MAP,1))
				bResult = 1;
			else if (m_sItemArray[RIGHTHAND].nNum == MATTOCK || m_sItemArray[RIGHTHAND].nNum == GOLDEN_MATTOCK || isMining())
				bResult = 4; 
			else
				bResult = 3;
		}

		else if (nActiveEvent == TEMPLE_EVENT_BORDER_DEFENCE_WAR)
		{
			if (GetLevel() < 35)
				bResult = WarpListMinLevel;
		}

		result << bType << bResult << nActiveEvent;
		Send(&result);

		if (bResult == 1) 
		{
			GetNation() == KARUS ? g_pMain->pTempleEvent.KarusUserCount++ :g_pMain->pTempleEvent.ElMoradUserCount++;
			g_pMain->pTempleEvent.AllUserCount = (g_pMain->pTempleEvent.KarusUserCount + g_pMain->pTempleEvent.ElMoradUserCount);
			g_pMain->AddEventUser(this);
			TempleOperations(TEMPLE_EVENT_COUNTER);
		}
	}
	else if (bType == TEMPLE_EVENT_DISBAND && isEventUser())
	{
		GetNation() == KARUS ? g_pMain->pTempleEvent.KarusUserCount-- : g_pMain->pTempleEvent.ElMoradUserCount--;
		g_pMain->pTempleEvent.AllUserCount = g_pMain->pTempleEvent.KarusUserCount + g_pMain->pTempleEvent.ElMoradUserCount;
		g_pMain->RemoveEventUser(this);
		result <<  bType << bResult << nActiveEvent;
		Send(&result);
		TempleOperations(TEMPLE_EVENT_COUNTER);
	}
	else if (bType == TEMPLE_EVENT_COUNTER)
	{
		result << bType << nActiveEvent;

		if(nActiveEvent == TEMPLE_EVENT_CHAOS)
			result << g_pMain->pTempleEvent.AllUserCount;
		else
			result << g_pMain->pTempleEvent.KarusUserCount << g_pMain->pTempleEvent.ElMoradUserCount;

		g_pMain->Send_All(&result,nullptr,Nation::ALL,0,true,0);
	}
}

void CGameServerDlg::AddEventUser(CUser *pUser)
{
	if (pUser == nullptr)
	{
		TRACE("#### AddEventUser : pUser == nullptr ####\n");
		return;
	}

	_TEMPLE_EVENT_USER * pEventUser = new _TEMPLE_EVENT_USER;

	pEventUser->m_socketID =  pUser->GetSocketID();
	pEventUser->m_bEventRoom = pUser->GetEventRoom();

	if (!g_pMain->m_TempleEventUserArray.PutData(pEventUser->m_socketID, pEventUser))
		delete pEventUser;
}

void CGameServerDlg::RemoveEventUser(CUser *pUser)
{
	if (pUser == nullptr)
	{
		TRACE("#### RemoveEventUser : pUser == nullptr ####\n");
		return;
	}

	if (g_pMain->m_TempleEventUserArray.GetData(pUser->GetSocketID()) != nullptr)
		g_pMain->m_TempleEventUserArray.DeleteData(pUser->GetSocketID());

	pUser->m_bEventRoom = 0;
}

void CGameServerDlg::UpdateEventUser(CUser *pUser, uint16 nEventRoom)
{
	if (pUser == nullptr)
	{
		TRACE("#### UpdateEventUser : pUser == nullptr ####\n");
		return;
	}

	_TEMPLE_EVENT_USER * pEventUser = g_pMain->m_TempleEventUserArray.GetData(pUser->GetSocketID());

	if (pEventUser)
	{
		pEventUser->m_bEventRoom = nEventRoom;
		pUser->m_bEventRoom = nEventRoom;
	}
}

void CGameServerDlg::SetEventUser(CUser *pUser)
{
	if (pUser == nullptr)
	{
		TRACE("#### SetEventUser : pUser == nullptr ####\n");
		return;
	}

	uint8 nMaxUserCount = 0;

	switch (g_pMain->pTempleEvent.ActiveEvent)
	{
	case TEMPLE_EVENT_BORDER_DEFENCE_WAR:
		nMaxUserCount = 16;//SANAL ODA
		break;
	case TEMPLE_EVENT_CHAOS:
		nMaxUserCount = 20;
		break;
	case TEMPLE_EVENT_JURAD_MOUNTAIN:
		nMaxUserCount = 16;
		break;
	}

	if (g_pMain->TempleEventGetRoomUsers(g_pMain->pTempleEvent.LastEventRoom) >= nMaxUserCount)
		g_pMain->pTempleEvent.LastEventRoom++;

	if (g_pMain->TempleEventGetRoomUsers(g_pMain->pTempleEvent.LastEventRoom) < nMaxUserCount)
		g_pMain->UpdateEventUser(pUser, g_pMain->pTempleEvent.LastEventRoom);
	
	/*
	if( g_pMain->pTempleEvent.ActiveEvent == TEMPLE_EVENT_CAVE_DEFENCE_WAR)
	{

		int nRoomKW  = 1, nRoomKR  = 1, nRoomKM = 1, nRoomKP = 1;
		int nRoomEW  = 1, nRoomER  = 1, nRoomEM = 1, nRoomEP = 1;

		foreach_stlmap(itr, m_TempleEventUserArray) 
		{
				CUser * pUser = GetUserPtr(itr->second->m_socketID);

				if (pUser == nullptr ||	!pUser->isInGame())
					continue;

				switch(pUser->m_sClass)
				{
					case 101:
					case 105:
					case 106:
						g_pMain->UpdateEventUser(pUser, nRoomKW);
						nRoomKW++;
						break;

					case 102:
					case 107:
					case 108:
						g_pMain->UpdateEventUser(pUser, nRoomKR);
						nRoomKR++;
						break;

					case 103:
					case 109:
					case 110:
						g_pMain->UpdateEventUser(pUser, nRoomKM);
						nRoomKM++;
						break;

					case 104:
					case 111:
					case 112:
						g_pMain->UpdateEventUser(pUser, nRoomKP);
						nRoomKP++;
						break;

						///////////////////////////////////
					case 201:
					case 205:
					case 206:
						g_pMain->UpdateEventUser(pUser, nRoomEW);
						nRoomEW++;
						break;

					case 202:
					case 207:
					case 208:
						g_pMain->UpdateEventUser(pUser, nRoomER);
						nRoomER++;
						break;

					case 203:
					case 209:
					case 210:
						g_pMain->UpdateEventUser(pUser, nRoomEM);
						nRoomEM++;
						break;

					case 204:
					case 211:
					case 212:
						g_pMain->UpdateEventUser(pUser, nRoomEP);
						nRoomEP++;
						break;

				}
		}
	}
	*/
}

bool CUser::isEventUser()
{
	_TEMPLE_EVENT_USER * pEventUser = g_pMain->m_TempleEventUserArray.GetData(GetSocketID());

	if (pEventUser != nullptr)
		return true;

	return false;
}

uint8 CUser::GetMonsterChallengeTime() 
{ 
	if (g_pMain->m_bForgettenTempleIsActive
		&& g_pMain->m_nForgettenTempleLevelMin != 0 
		&& g_pMain->m_nForgettenTempleLevelMax != 0
		&& GetLevel() >= g_pMain->m_nForgettenTempleLevelMin 
		&& GetLevel() <= g_pMain->m_nForgettenTempleLevelMax
		&& !g_pMain->m_bForgettenTempleSummonMonsters)
		return g_pMain->m_nForgettenTempleChallengeTime; 

	return 0;
}

uint8 CUser::GetEventZoneTime() 
{ 
	if (g_pMain->m_bEventZoneIsActive
		&& g_pMain->m_nEventZoneLevelMin != 0 
		&& g_pMain->m_nEventZoneLevelMax != 0
		&& GetLevel() >= g_pMain->m_nEventZoneLevelMin 
		&& GetLevel() <= g_pMain->m_nEventZoneLevelMax)
		return g_pMain->m_nEventZoneTime; 

	return 0;
}
void CUser::HandleCapture(Packet & pkt)
{
	if ((UNIXTIME - m_tBorderCapure) < 10)
		return;

	uint16 KO = 360;
	
	g_pMain->pTempleEvent.m_sBdwMiniTimer[GetEventRoom()] = KO;
	g_pMain->pTempleEvent.m_sMiniTimerNation[GetEventRoom()] = GetNation();
	
	GetNation() == KARUS ? g_pMain->pTempleEvent.ElmoDeathCount[GetEventRoom()] = g_pMain->pTempleEvent.ElmoDeathCount[GetEventRoom()] + 2 : g_pMain->pTempleEvent.KarusDeathCount[GetEventRoom()] = g_pMain->pTempleEvent.KarusDeathCount[GetEventRoom()] + 2;

	Packet result1(WIZ_CAPTURE, uint8(0x05));
	result1 << GetNation() << GetName().c_str();
	Packet result(WIZ_CAPTURE, uint8(0x04));
	result << GetNation() << uint16(KO);

	g_pMain->Send_Zone(&result1, GetZoneID(), nullptr, Nation::ALL,GetEventRoom());
	g_pMain->Send_Zone(&result, GetZoneID(), nullptr, Nation::ALL,GetEventRoom());


	result.Initialize(WIZ_EVENT);
	result << uint8(TEMPLE_EVENT_BORDER_COUNTER);
	m_iLoyaltyDaily += 2 ;
	UpdatePlayerRank();
	result << g_pMain->pTempleEvent.ElmoDeathCount[GetEventRoom()] << uint16(0x00) << g_pMain->pTempleEvent.KarusDeathCount[GetEventRoom()] << uint16(0x00);
	g_pMain->Send_Zone(&result, GetZoneID(), nullptr, Nation::ALL,GetEventRoom());

}
uint8 CUser::GetMonsterChallengeUserCount() { return g_pMain->m_nForgettenTempleUsers.size(); }
uint8 CUser::GetEventZoneUserCount() { return g_pMain->m_nEventZoneUsers.size(); }