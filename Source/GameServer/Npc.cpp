#include "stdafx.h"
#include "Map.h"
#include "MagicInstance.h"
#include "../shared/DateTime.h"

using namespace std;

CNpc::CNpc() : Unit(UnitNPC)
{
	Initialize();
}


CNpc::~CNpc()
{
}

void CNpc::Initialize()
{
	Unit::Initialize();

	m_sSid = 0;
	m_sPid = 0;	
	m_sSize = 100;	
	m_strName.clear();	
	m_iMaxHP = 0;
	m_iHP = 0;					
	m_byState = 0;	
	m_tNpcType = 0;			
	m_iSellingGroup = 0;
	m_byDirection = 0;
	m_iWeapon_1 = 0;
	m_iWeapon_2 = 0;
	m_NpcState = NPC_LIVE;
	m_byGateOpen = true;
	m_byObjectType = NORMAL_OBJECT;
	m_byTrapNumber = 0;
	m_oSocketID = -1;
	m_bEventRoom = 0;

	InitType3();
	InitType4(true);
}

void CNpc::AddToRegion(int16 new_region_x, int16 new_region_z)
{
	GetRegion()->Remove(this);
	SetRegion(new_region_x, new_region_z);
	GetRegion()->Add(this);
}

void CNpc::MoveResult(float fPosX, float fPosY, float fPosZ, float fSpeed)
{
	Packet result(WIZ_NPC_MOVE);

	SetPosition(fPosX, fPosY, fPosZ);
	RegisterRegion();

	result << uint8(1);

	result << GetID() << GetSPosX() << GetSPosZ() << GetSPosY() << uint16(fSpeed * 10);
	SendToRegion(&result);
}

void CNpc::GetInOut(Packet & result, uint8 bType)
{
	result.Initialize(WIZ_NPC_INOUT);
	result << bType << GetID();
	if (bType != INOUT_OUT)
		GetNpcInfo(result);

	if (bType == INOUT_IN)
		OnRespawn();
}

void CNpc::SendInOut(uint8 bType, float fX, float fZ, float fY)
{
	if (GetRegion() == nullptr)
	{
		SetRegion(GetNewRegionX(), GetNewRegionZ());
		if (GetRegion() == nullptr)
			return;
	}

	if (bType == INOUT_OUT)
	{
		GetRegion()->Remove(this);
	}
	else	
	{
		GetRegion()->Add(this);
		SetPosition(fX, fY, fZ);
	}

	Packet result;
	GetInOut(result, bType);
	SendToRegion(&result);
}

void CNpc::GetNpcInfo(Packet & pkt)
{
	pkt.SByte();

	pkt << GetProtoID()
		<< uint8(isMonster() ? 1 : 2)
		<< m_sPid
		<< m_iSellingGroup
		<< GetType()
		<< uint32(0)
		<< m_sSize
		<< uint32(m_iWeapon_1) << uint32(m_iWeapon_2)
		<< uint8(isMonster() ? 0 : GetNation())
		<< GetLevel()
		<< GetSPosX() << GetSPosZ() << GetSPosY();
		if (GetProtoID() == 8110)
			pkt << uint32(2);
		else
			pkt << uint32(isGateOpen());
		pkt << m_byObjectType
		<< uint16(0) << uint16(0)
		<< int16(m_byDirection);
}

void CNpc::SendGateFlag(uint8 bFlag /*= -1*/, bool bSendAI /*= true*/)
{
	 uint8 objectType = OBJECT_FLAG_LEVER;
	 
	 _OBJECT_EVENT * pObjectEvent = GetMap()->GetObjectEvent(GetProtoID());
	 
	 if (pObjectEvent)
		 objectType = (uint8)pObjectEvent->sType;
	 
	 Packet result(WIZ_OBJECT_EVENT, objectType);

	if (bFlag >= 0)
		m_byGateOpen = (bFlag == 1);

	result << uint8(1) << GetID() << m_byGateOpen;
	SendToRegion(&result);

	if (bSendAI)
	{
		result.Initialize(AG_NPC_GATE_OPEN);
		result << GetID() << GetProtoID() << m_byGateOpen;
		Send_AIServer(&result);
	}
}

void CNpc::HpChange(int amount, Unit *pAttacker /*= nullptr*/, bool bSendToAI /*= true*/) 
{
	uint16 tid = (pAttacker != nullptr ? pAttacker->GetID() : -1);

	if (amount < -MAX_DAMAGE)
		amount = -MAX_DAMAGE;
	else if (amount > MAX_DAMAGE)
		amount = MAX_DAMAGE;

	if (amount < 0 && -amount > m_iHP)
		m_iHP = 0;
	else if (amount >= 0 && m_iHP + amount > m_iMaxHP)
		m_iHP = m_iMaxHP;
	else
		m_iHP += amount;

	if (bSendToAI)
		SendHpChangeToAI(tid, amount);

	if (pAttacker != nullptr && pAttacker->isPlayer())
		TO_USER(pAttacker)->SendTargetHP(0, GetID(), amount);
}

void CNpc::HpChangeMagic(int amount, Unit *pAttacker /*= nullptr*/, AttributeType attributeType /*= AttributeNone*/)
{
	uint16 tid = (pAttacker != nullptr ? pAttacker->GetID() : -1);

	if (amount < -MAX_DAMAGE)
		amount = -MAX_DAMAGE;
	else if (amount > MAX_DAMAGE)
		amount = MAX_DAMAGE;

	HpChange(amount, pAttacker, false);
	SendHpChangeToAI(tid, amount, attributeType);
}

void CNpc::SendHpChangeToAI(uint16 sTargetID, int amount, AttributeType attributeType)
{
	Packet result(AG_NPC_HP_CHANGE);
	result << GetID() << sTargetID << m_iHP << amount << uint8(attributeType);
	Send_AIServer(&result);
}

void CNpc::MSpChange(int amount)
{

}

bool CNpc::CastSkill(Unit * pTarget, uint32 nSkillID)
{
	if (pTarget == nullptr)
		return false;

	MagicInstance instance;

	instance.bSendFail = false;
	instance.nSkillID = nSkillID;
	instance.sCasterID = GetID();
	instance.sTargetID = pTarget->GetID();

	instance.Run();

	return (instance.bSkillSuccessful);
}

float CNpc::GetRewardModifier(uint8 byLevel)
{
	int iLevelDifference = GetLevel() - byLevel;

	if (iLevelDifference <= -14)	
		return 0.2f;
	else if (iLevelDifference <= -8 && iLevelDifference >= -13)
		return 0.5f;
	else if (iLevelDifference <= -2 && iLevelDifference >= -7)
		return 0.8f;

	return 1.0f;
}

float CNpc::GetPartyRewardModifier(uint32 nPartyLevel, uint32 nPartyMembers)
{
	int iLevelDifference = GetLevel() - (nPartyLevel / nPartyMembers);

	if (iLevelDifference >= 8)
		return 2.0f;
	else if (iLevelDifference >= 5)
		return 1.5f;
	else if (iLevelDifference >= 2)
		return 1.2f;

	return 1.0f;
}

void CNpc::OnDeath(Unit *pKiller)
{
	if (m_NpcState == NPC_DEAD)
		return;

	ASSERT(GetMap() != nullptr);
	ASSERT(GetRegion() != nullptr);

	m_NpcState = NPC_DEAD;
	m_sACPercent = 100;

	if (m_byObjectType == SPECIAL_OBJECT)
	{
		_OBJECT_EVENT *pEvent = GetMap()->GetObjectEvent(GetProtoID());
		if (pEvent != nullptr)
			pEvent->byLife = 0;
	}

	Unit::OnDeath(pKiller);
	OnDeathProcess(pKiller);

	GetRegion()->Remove(TO_NPC(this));
	SetRegion();
}

void CNpc::OnDeathProcess(Unit *pKiller)
{
	if (TO_NPC(this) == nullptr && !pKiller->isPlayer())
		return;

	CUser * pUser = TO_USER(pKiller);

	if (pUser == nullptr)
		return;

	_PARTY_GROUP * pParty = g_pMain->GetPartyPtr(pUser->GetPartyID());

	if (!m_bMonster)
	{
		switch (m_tNpcType)
		{
		case NPC_BIFROST_MONUMENT:
			pUser->BifrostProcess(pUser);
			break;
		case NPC_PVP_MONUMENT:
			PVPMonumentProcess(pUser);
			break;
		case NPC_CZ_MONUMENT:
			CZMonumentProcess(pUser);
			break;
		case NPC_BORDER_MONUMENT:
			BorderMonumentProcess(pUser);
			break;
		case NPC_BATTLE_MONUMENT:
			BattleMonumentProcess(pUser);
			break;
		case NPC_HUMAN_MONUMENT:
			NationMonumentProcess(pUser);
			break;
		case NPC_KARUS_MONUMENT:
			NationMonumentProcess(pUser);
			break;
		case NPC_DESTROYED_ARTIFACT:
			pUser->CastleSiegeWarProcess(pUser);
			break;
		}
	}
	else if (m_bMonster)
	{
		if (GetProtoID() == 700 || GetProtoID() == 750 || GetProtoID() == 701 || GetProtoID() == 751)
		{
			if (pUser->CheckExistEvent(STARTER_SEED_QUEST, 1))
			{
				_QUEST_HELPER * pQuestHelper ;
				if (pUser->GetNation() == ELMORAD)
					pQuestHelper = g_pMain->m_QuestHelperArray.GetData(5005);
				else
					pQuestHelper = g_pMain->m_QuestHelperArray.GetData(5002);

				pUser->QuestV2RunEvent(pQuestHelper,pQuestHelper->nEventTriggerIndex);
			}
		}
		else if (g_pMain->m_MonsterRespawnListArray.GetData(GetProtoID()) != nullptr)
		{
			if (pUser->isInPKZone() || GetZoneID() == ZONE_JURAD_MOUNTAIN)
			{
				g_pMain->SpawnEventNpc(g_pMain->m_MonsterRespawnListArray.GetData(GetProtoID())->sSid, true, GetZoneID(), GetX(), GetY(), GetZ(), g_pMain->m_MonsterRespawnListArray.GetData(GetProtoID())->sCount,5);
				if (GetProtoID () == 8100)
				{
					pUser->GetNation() == KARUS ? g_pMain->LeechKig++ : g_pMain->e_LeechKig++;
				}
				if (GetProtoID () == 8104)
				{
					pUser->GetNation() == KARUS ? g_pMain->BoneDragon++ : g_pMain->e_BoneDragon++;
				}
				if (GetProtoID () == 8103)
				{
					pUser->GetNation() == KARUS ? g_pMain->Minotaur++ : g_pMain->e_Minotaur++;
				}
			}
		}
		else if (m_sSid == 6917 && GetZoneID() == ZONE_JURAD_MOUNTAIN)
		{
			pUser->GetNation() == KARUS ? g_pMain->Apostle++ : g_pMain->e_Apostle++;

			if (g_pMain->Apostle >= 16|| g_pMain->e_Apostle >= 16 )
			{
				if (pUser->GetNation() == KARUS)
				{
					g_pMain->LeechKig = 0;
					g_pMain->Apostle = 0;
					pUser->ZoneChangeParty(GetZoneID(),800,343);
				}
				else
				{
					g_pMain->e_LeechKig = 0;
					g_pMain->e_Apostle = 0;
					pUser->ZoneChangeParty(GetZoneID(),223,672);
				}

				if (pParty == nullptr)
				{
					pUser->JuraidSpot = 1;
				}
				else
				{
					for (int i = 0; i < MAX_PARTY_USERS; i++)
					{
						CUser * pUserX = g_pMain->GetUserPtr(pParty->uid[i]);
						if (pUserX != nullptr)
							pUserX->JuraidSpot = 1;
					}
				}
			}
		}
		else if (m_sSid == 6918 && GetZoneID() == ZONE_JURAD_MOUNTAIN)
		{
			pUser->GetNation() == KARUS ? g_pMain->TrollWarrior++ : g_pMain->e_TrollWarrior++;

			if (g_pMain->TrollWarrior >= 16|| g_pMain->e_TrollWarrior >= 16 )
			{
				if (pUser->GetNation() == KARUS)
				{
					g_pMain->BoneDragon = 0;
					g_pMain->TrollWarrior = 0;
					pUser->ZoneChangeParty(GetZoneID(),690,172);
				}
				else
				{
					g_pMain->e_BoneDragon = 0;
					g_pMain->e_TrollWarrior = 0;
					pUser->ZoneChangeParty(GetZoneID(),340,847);
				}

				if (pParty == nullptr)
				{
					pUser->JuraidSpot =2;
				}
				else
				{
					for (int i = 0; i < MAX_PARTY_USERS; i++)
					{
						CUser * pUserX = g_pMain->GetUserPtr(pParty->uid[i]);
						if (pUserX != nullptr)
							pUserX->JuraidSpot = 2;
					}
				}
			}
		}
		else if (m_sSid == 8057 && GetZoneID() == ZONE_JURAD_MOUNTAIN)
		{
			pUser->GetNation() == KARUS ? g_pMain->DoomSoldier++ : g_pMain->e_DoomSoldier++;

			if (g_pMain->DoomSoldier >= 16|| g_pMain->e_DoomSoldier >= 16 )
			{
				if (pUser->GetNation() == KARUS)
				{
					g_pMain->Minotaur = 0;
					g_pMain->DoomSoldier = 0;
					pUser->ZoneChangeParty(GetZoneID(),512,282);
				}
				else
				{
					g_pMain->e_Minotaur = 0;
					g_pMain->e_DoomSoldier = 0;
					pUser->ZoneChangeParty(GetZoneID(),512,736);
				}

				if (pParty == nullptr)
					pUser->JuraidSpot = 3;
				else
				{
					for (int i = 0; i < MAX_PARTY_USERS; i++)
					{
						CUser * pUserX = g_pMain->GetUserPtr(pParty->uid[i]);
						if (pUserX != nullptr)
							pUserX->JuraidSpot = 3;
					}
				}
			}
		}
		else if (m_sSid == 8106 && GetZoneID() == ZONE_JURAD_MOUNTAIN)
		{
			g_pMain->pTempleEvent.isDevaControl = true;
			g_pMain->pTempleEvent.isDevaFlag = true;
		}

		else if (m_tNpcType == NPC_CHAOS_STONE && pUser->isInPKZone()) 
		{
			ChaosStoneProcess(pUser,5);
		}
		else if (m_tNpcType == NPC_BORDER_MONUMENT && pUser->isInEventZone() || m_tNpcType == NPC_KJWAR && pUser->isInEventZone())
			BorderMonumentProcess(pUser);
		if (g_pMain->m_bForgettenTempleIsActive && GetZoneID() == ZONE_FORGOTTEN_TEMPLE)
			g_pMain->m_ForgettenTempleMonsterList.erase(m_sNid);

		if (pUser->isInParty())
		{
			_PARTY_GROUP *pParty = g_pMain->GetPartyPtr(pUser->GetPartyID());
			if (pParty != nullptr)
			{
				for (int i = 0; i < 8; i++)
				{
					if (pParty->uid[i] >= 0)
					{
						CUser * pUserRange = g_pMain->GetUserPtr(pParty->uid[i]);
						if (!isInRangeSlow(pUserRange, 50.0f) || pUserRange == nullptr)
							continue;

						CUser * pUserParty = g_pMain->GetUserPtr(pParty->uid[i]);
						if (pUserParty)
						{
							//pUserParty->QuestV2MonsterCountAdd(GetProtoID()); KONTROL EDILECEK
							pUserParty->QuestV3MainCount(GetProtoID());
							pUserParty->MonDefeatCount++;
						}
					}
				}
			}
		}

		else
		{
			//pUser->QuestV2MonsterCountAdd(GetProtoID()); KONTROL EDILECEK
			pUser->QuestV3MainCount(GetProtoID());
			pUser->MonDefeatCount++;
		}
	}

	if (pParty != nullptr)
	{
		for (int i = 0; i < 8; i++)
		{
			if (pParty->uid[i] >= 0)
			{
				CUser * pUserRange = g_pMain->GetUserPtr(pParty->uid[i]);
				if (!isInRangeSlow(pUserRange, 50.0f) || pUserRange == nullptr)
					continue;

				CUser * pUserParty = g_pMain->GetUserPtr(pParty->uid[i]);
				if (pUserParty)
				{
					pUserParty->AchieveUpdateKills(GetProtoID());
					pUserParty->AchieveMainCount(0, 20, 0, 0);
				}
			}
		}
	}
	else
	{
		pUser->AchieveUpdateKills(GetProtoID());
		pUser->AchieveMainCount(0, 20, 0, 0);
	}

	DateTime time;
	string pKillerPartyUsers;

	if (pUser->isInParty())
	{
		CUser *pPartyUser;
		_PARTY_GROUP *pParty = g_pMain->GetPartyPtr(pUser->GetPartyID());
		if (pParty)
		{
			for (int i = 0; i < MAX_PARTY_USERS; i++)
			{
				pPartyUser = g_pMain->GetUserPtr(pParty->uid[i]);
				if (pPartyUser)
					pKillerPartyUsers += string_format("%s,",pPartyUser->GetName().c_str());
			}
		}

		if (!pKillerPartyUsers.empty())
			pKillerPartyUsers = pKillerPartyUsers.substr(0,pKillerPartyUsers.length() - 1);
	}

	if (pKillerPartyUsers.empty())
		g_pMain->WriteDeathNpcLogFile(string_format("[ %s - %d:%d:%d ] Killer=%s,SID=%d,Target=%s,Zone=%d,X=%d,Z=%d\n",m_bMonster ? "MONSTER" : "NPC",time.GetHour(),time.GetMinute(),time.GetSecond(),pKiller->GetName().c_str(),GetProtoID(),GetName().c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ())));
	else
		g_pMain->WriteDeathNpcLogFile(string_format("[ %s - %d:%d:%d ] Killer=%s,KillerParty=%s,SID=%d,Target=%s,Zone=%d,X=%d,Z=%d\n",m_bMonster ? "MONSTER" : "NPC",time.GetHour(),time.GetMinute(),time.GetSecond(),pKiller->GetName().c_str(),pKillerPartyUsers.c_str(),GetProtoID(),GetName().c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ())));
	
	InitType3();
	InitType4(false);
}

void CNpc::InitType3()
{
	for (int i = 0; i < MAX_TYPE3_REPEAT; i++)
		m_durationalSkills[i].Reset();

	m_bType3Flag = false;
}

void CNpc::InitType4(bool bRemoveSavedMagic /*= false*/, uint8 buffType /* = 0 */)
{
	Guard lock(m_buffLock);
	Type4BuffMap buffMap = m_buffMap;

	for (auto itr = buffMap.begin(); itr != buffMap.end(); itr++)
	{
#ifdef GAMESERVER
		if (buffType > 0 && itr->second.m_bBuffType != buffType)
			continue;

		CMagicProcess::RemoveType4Buff(itr->first, this, bRemoveSavedMagic, buffType > 0 ? true : false);
#endif
	}
}

void CNpc::OnRespawn()
{
	if (GetProtoID() == BORDER_WAR_MONUMENT_SID
		|| (g_pMain->m_byBattleOpen == NATION_BATTLE
		&& (GetProtoID() == ELMORAD_MONUMENT_SID
		|| GetProtoID() == ASGA_VILLAGE_MONUMENT_SID
		|| GetProtoID() == RAIBA_VILLAGE_MONUMENT_SID
		|| GetProtoID() == DODO_CAMP_MONUMENT_SID
		|| GetProtoID() == LUFERSON_MONUMENT_SID
		|| GetProtoID() == LINATE_MONUMENT_SID
		|| GetProtoID() == BELLUA_MONUMENT_SID
		|| GetProtoID() == LAON_CAMP_MONUMENT_SID)))
	{
		_MONUMENT_INFORMATION * pData = new	_MONUMENT_INFORMATION();
		pData->sSid = GetProtoID();
		pData->sNid = m_sNid;
		pData->RepawnedTime = int32(UNIXTIME);

		if (GetProtoID() == DODO_CAMP_MONUMENT_SID || GetProtoID() == LAON_CAMP_MONUMENT_SID)
			g_pMain->m_bMiddleStatueNation = m_bNation; 

		if (!g_pMain->m_NationMonumentInformationArray.PutData(pData->sSid, pData))
			delete pData;
	}
	else if (g_pMain->m_bForgettenTempleIsActive && GetZoneID() == ZONE_FORGOTTEN_TEMPLE)
		g_pMain->m_ForgettenTempleMonsterList.insert(std::make_pair(m_sNid, GetProtoID()));
}

void CNpc::ChaosStoneProcess(CUser *pUser, uint16 MonsterCount)
{
	if (pUser == nullptr)
		return;

	g_pMain->SendNotice<CHAOS_STONE_ENEMY_NOTICE>("",GetZoneID(), Nation::ALL);

	std::vector<uint32> MonsterSpawned;
	std::vector<uint32> MonsterSpawnedFamily;
	bool bLoopBack = true;

	for (uint16 i = 0; i < MonsterCount;i++)
	{
		uint32 nMonsterNum = myrand(0, g_pMain->m_MonsterSummonListZoneArray.GetSize());
		_MONSTER_SUMMON_LIST_ZONE * pMonsterSummonListZone = g_pMain->m_MonsterSummonListZoneArray.GetData(nMonsterNum);

		if (pMonsterSummonListZone != nullptr)
		{
			if (pMonsterSummonListZone->ZoneID == GetZoneID())
			{
				if (std::find(MonsterSpawned.begin(),MonsterSpawned.end(),nMonsterNum) == MonsterSpawned.end())
				{
					if (std::find(MonsterSpawnedFamily.begin(),MonsterSpawnedFamily.end(),pMonsterSummonListZone->byFamily) == MonsterSpawnedFamily.end())
					{
						g_pMain->SpawnEventNpc(pMonsterSummonListZone->sSid, true,GetZoneID(), GetX(), GetY(), GetZ(), 1, CHAOS_STONE_MONSTER_RESPAWN_RADIUS, CHAOS_STONE_MONSTER_LIVE_TIME);
						MonsterSpawned.push_back(nMonsterNum);
						MonsterSpawnedFamily.push_back(pMonsterSummonListZone->byFamily);
						bLoopBack = false;
					}
				}
			}
		}

		if (bLoopBack)
			i--;
		else
			bLoopBack = true;
	}
}


void CNpc::PVPMonumentProcess(CUser *pUser)
{
	if (pUser == nullptr)
		return;

	std::string sKillMonuPvP;
	std::string sKillMonuEvent;
	std::string sMonuNation;

	Packet result(WIZ_CHAT, uint8(MONUMENT_NOTICE));
	result << uint8(FORCE_CHAT) << pUser->GetNation() << pUser->GetName().c_str();
	g_pMain->Send_Zone(&result, GetZoneID(), nullptr, Nation::ALL);

	if (pUser->GetNation() == KARUS)
		sMonuNation = "Karus";
	else
		sMonuNation = "Human";

	sKillMonuPvP = string_format("%s has destroyed the %s. %s nation get +5 NPs per kill!",pUser->GetName().c_str(),GetName().c_str(),sMonuNation.c_str());
	sKillMonuEvent = string_format("%s has destroyed the %s. %s nation get +10 NPs per kill!",pUser->GetName().c_str(),GetName().c_str(),sMonuNation.c_str());

	if (GetZoneID() == ZONE_RONARK_LAND)
	{
		g_pMain->m_nPVPMonumentNation[GetZoneID()] = pUser->GetNation();
		g_pMain->SendAnnouncement(sKillMonuPvP.c_str());
	}
	else
	{
		g_pMain->m_nEventMonumentNation[GetZoneID()] = pUser->GetNation();
		g_pMain->SendAnnouncement(sKillMonuEvent.c_str());
	}

	g_pMain->NpcUpdate(GetProtoID(), m_bMonster, pUser->GetNation(), pUser->GetNation() == KARUS ? MONUMENT_KARUS_SPID : MONUMENT_ELMORAD_SPID);
	pUser->GiveItem(BLUE_TREASURE_CHEST,1);
}


void CNpc::BattleMonumentProcess(CUser *pUser)
{
	if (pUser && g_pMain->m_byBattleOpen == NATION_BATTLE)
	{
		g_pMain->NpcUpdate(GetProtoID(), m_bMonster, pUser->GetNation(), pUser->GetNation() == KARUS ? MONUMENT_KARUS_SPID : MONUMENT_ELMORAD_SPID);
		g_pMain->Announcement(DECLARE_BATTLE_MONUMENT_STATUS, Nation::ALL, m_byTrapNumber, pUser);

		if (pUser->GetNation() == KARUS)
		{	
			g_pMain->m_sKarusMonumentPoint +=10;
			g_pMain->m_sKarusMonuments++;

			if (g_pMain->m_sElmoMonuments != 0)
				g_pMain->m_sElmoMonuments--;
		}
		else
		{
			g_pMain->m_sElmoMonumentPoint += 10;
			g_pMain->m_sElmoMonuments++;

			if (g_pMain->m_sKarusMonuments != 0)
				g_pMain->m_sKarusMonuments--;
		}
	}
}

void CNpc::NationMonumentProcess(CUser *pUser)
{
	if (!pUser)
		return;

	if (g_pMain->m_byBattleOpen == NATION_BATTLE)
	{
		g_pMain->NpcUpdate(GetProtoID(), m_bMonster, pUser->GetNation());
		g_pMain->Announcement(DECLARE_NATION_MONUMENT_STATUS, Nation::ALL, GetProtoID(), pUser);

		uint16 sSid = 0;

		foreach_stlmap (itr, g_pMain->m_NationMonumentInformationArray)
			if (itr->second->sSid == (pUser->GetNation() == KARUS ? GetProtoID() + 10000 : GetProtoID() - 10000))
				sSid = itr->second->sSid;

		if (sSid != 0)
			g_pMain->m_NationMonumentInformationArray.DeleteData(sSid);
	}
	else
	{
		g_pMain->NpcUpdate(GetProtoID(), m_bMonster, pUser->GetNation());

		uint16 sSid = 0;

		foreach_stlmap (itr, g_pMain->m_NationMonumentInformationArray)
			if (itr->second->sSid == (pUser->GetNation() == KARUS ? GetProtoID() + 10000 : GetProtoID() - 10000))
				sSid = itr->second->sSid;

		if (sSid != 0)
			g_pMain->m_NationMonumentInformationArray.DeleteData(sSid);
	}
}


void CNpc::CZMonumentProcess(CUser *pUser)
{
	if (pUser == nullptr)
		return;

	std::string sKillMonu;
	std::string sRecoMonu;

	sKillMonu = string_format("%s has destroyed the %s at Ronark Land!",pUser->GetName().c_str(),GetName().c_str());
	sRecoMonu = string_format("%s has recovered the %s at Ronark Land!",pUser->GetName().c_str(),GetName().c_str());

	g_pMain->NpcUpdate(GetProtoID(), m_bMonster, pUser->GetNation());

	if (pUser->GetNation() == KARUS)
	{
		if (GetSpid() == 30092)
		{
			g_pMain->SendAnnouncement(sKillMonu.c_str());
			pUser->GiveItem(BLUE_TREASURE_CHEST,1);
			pUser->SendLoyaltyChange(150);
		}
		else
		{
			g_pMain->SendAnnouncement(sRecoMonu.c_str());
		}
	}
	else
	{
		if (GetSpid() == 30091)
		{
			g_pMain->SendAnnouncement(sKillMonu.c_str());
			pUser->GiveItem(BLUE_TREASURE_CHEST,1);
			pUser->SendLoyaltyChange(150);
		}
		else
		{
			g_pMain->SendAnnouncement(sRecoMonu.c_str());
		}
	}
}


void CNpc::BorderMonumentProcess(CUser *pUser)
{
	if (pUser == nullptr || (UNIXTIME - pUser->m_tBorderCapure) < 10)
		return;

	std::string sKillMonuKarus;
	std::string sKillMonuHuman;

	sKillMonuKarus = string_format("%s has destroyed the %s.Bosses will appear on Karus Base.Orcs get +10 NPs per kill!",pUser->GetName().c_str(),GetName().c_str());
	sKillMonuHuman = string_format("%s has destroyed the %s.Bosses will appear on Human Base.Humans get +10 NPs per kill!",pUser->GetName().c_str(),GetName().c_str());

	g_pMain->m_nEventMonumentNation[GetZoneID()] = pUser->GetNation();

	if (pUser->GetNation() == KARUS)
		g_pMain->SendAnnouncement(sKillMonuKarus.c_str());
	else
		g_pMain->SendAnnouncement(sKillMonuHuman.c_str());

	uint16 KO = 360;
	
	g_pMain->pTempleEvent.m_sBdwMiniTimer[GetEventRoom()] = KO;
	g_pMain->pTempleEvent.m_sMiniTimerNation[GetEventRoom()] = GetNation();
	
	GetNation() == KARUS ? g_pMain->pTempleEvent.ElMoradUserCount += 2 : g_pMain->pTempleEvent.KarusUserCount+= 2 ;

	Packet result1(WIZ_CAPTURE, uint8(0x05));
	result1 << GetNation() << GetName().c_str();
	Packet result(WIZ_CAPTURE, uint8(0x04));
	result << GetNation() << uint16(KO);

	g_pMain->Send_Zone(&result1, GetZoneID(), nullptr, Nation::ALL,GetEventRoom());
	g_pMain->Send_Zone(&result, GetZoneID(), nullptr, Nation::ALL,GetEventRoom());


	result.Initialize(WIZ_EVENT);
	result << uint8(TEMPLE_EVENT_BORDER_COUNTER);
	pUser->m_iLoyaltyDaily += 2 ;
	pUser->UpdatePlayerRank();
	result << g_pMain->pTempleEvent.ElMoradUserCount << uint16(0x00) << g_pMain->pTempleEvent.KarusUserCount << uint16(0x00);
	g_pMain->Send_Zone(&result, GetZoneID(), nullptr, Nation::ALL,GetEventRoom());

	pUser->GiveItem(BLUE_TREASURE_CHEST,1);
}

void CNpc::HPTimeChangeType3()
{
	if (isDead()
		|| !m_bType3Flag || isPlayer())
		return;

	uint16	totalActiveDurationalSkills = 0, 
		totalActiveDOTSkills = 0;

	bool bIsDOT = false;
	for (int i = 0; i < MAX_TYPE3_REPEAT; i++)
	{
		MagicType3 * pEffect = &m_durationalSkills[i];
		if (!pEffect->m_byUsed)
			continue;

		if ((UNIXTIME - pEffect->m_tHPLastTime) >= pEffect->m_bHPInterval)
		{
			Unit * pUnit = g_pMain->GetUnitPtr(pEffect->m_sSourceID);

			if (pUnit == nullptr)
				continue;

			if (!isInRangeSlow(pUnit, 50.0f))
				m_bType3Flag = false;

			HpChange(pEffect->m_sHPAmount, pUnit);
			pEffect->m_tHPLastTime = UNIXTIME;

			if (pEffect->m_sHPAmount < 0)
				bIsDOT = true;

			if (++pEffect->m_bTickCount == pEffect->m_bTickLimit)
			{
				Packet result(WIZ_MAGIC_PROCESS, uint8(MAGIC_DURATION_EXPIRED));

				if (pEffect->m_sHPAmount > 0)
					result << uint8(100);
				else
					result << uint8(200);

				Send_AIServer(&result);

				pEffect->Reset();
			}
		}

		if (pEffect->m_byUsed)
		{
			totalActiveDurationalSkills++;
			if (pEffect->m_sHPAmount < 0)
				totalActiveDOTSkills++;
		}
	}

	if (totalActiveDurationalSkills == 0)
		m_bType3Flag = false;
}

void CNpc::Type4Duration()
{
	Guard lock(m_buffLock);
	if (m_buffMap.empty())
		return;

	foreach (itr, m_buffMap)
	{
		if (itr->second.m_tEndTime > UNIXTIME)
			continue;

		CMagicProcess::RemoveType4Buff(itr->first, this, true, false);
		break;
	}
}
