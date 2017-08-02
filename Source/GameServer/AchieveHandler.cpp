#include "stdafx.h"
#include "Map.h"
#include "../shared/DateTime.h"
#include <cmath>

void CUser::Achieve(Packet & pkt)
{
	uint8 opcode = pkt.read<uint8>();
	switch (opcode)
	{
		case AchieveGetItem:
			HandleAchieveGetItem(pkt);
			break;
		case AchieveInfo:
			HandleAchieveInfo(pkt);
			break;
		case AchieveSumary:
			HandleAchieveShow(pkt);
			break;
		case AchieveChallengeStart:
			HandleChallengeStart(pkt);
			break;
		case AchieveChallengeCancel:
			HandleChallengeCancel(pkt);
			break;
		case AchieveCover:
			HandleAchieveCoverTitle(pkt);
			break;
		case AchieveSkill:
			HandleAchieveSkillTitle(pkt);
			break;
		case AchieveCoverReset:
			HandleAchieveCoverTitleReset(pkt);
			break;
		case AchieveSkillReset:
			HandleAchieveSkillTitleReset(pkt);
			break;
		default:
			printf("Unhandled Achieve: %X\n", opcode);
			TRACE("Unhandled Achieve: %X\n", opcode);
			break;
	}
}

void CUser::HandleAchieveGetItem(Packet &pkt)
{
	uint16 rMainID = pkt.read<uint16>();
	uint32 iItemID = 0;
	uint16 ItemCount = 0;

	_ACHIEVE_MAIN * gAchieveM = nullptr;
	_ACHIEVE_DATA * aUser = GetAchieve(rMainID);

	if (aUser->dstats == 5)
		return;

	foreach_stlmap(itr, g_pMain->m_AchieveMainArray)
	{
		gAchieveM  = itr->second;

		if (!gAchieveM)
			continue;

		if (gAchieveM->mMainID != rMainID)
			continue;

		iItemID = gAchieveM->mItemID;
		ItemCount = gAchieveM->mItemCount;
	}

	aUser->dstats = 5;

	Packet result(WIZ_ACHIEVE, uint8(AchieveGetItem)); 
	result << uint16(rMainID)
		<< uint16(1);

	GiveItem(iItemID, ItemCount);

	Send(&result);
}

void CUser::HandleAchieveInfo(Packet & pkt)
{
	uint16 List = pkt.read<uint16>();
	 
	Packet result (WIZ_ACHIEVE, uint8(AchieveInfo));
	result << List;

	for (int i = 0; i < List; i++)
	{					
		uint16 Achive = pkt.read<uint16>();	

		_ACHIEVE_DATA * pAUser = GetAchieve(Achive);

		result << Achive 
			<< pAUser->dstats
			<< pAUser->dSlot1
			<< pAUser->dSlot2;
	}

	Send(&result);
}

void CUser::HandleAchieveShow(Packet & pkt)
{
	Packet result(WIZ_ACHIEVE, uint8(AchieveSumary));

	result << m_AchieveTimeOut
		<< MonDefeatCount
		<< UserDefeatCount
		<< UserDeathCount;

	result << aPoints
		<< iRecently1
		<< iRecently2
		<< iRecently3;

	uint16 Quest = 0, Normal = 0, War = 0, Adventure = 0, Challenge = 0;
	_ACHIEVE_MAIN * AchieveC = nullptr;

	foreach_stlmap(itr, g_pMain->m_AchieveMainArray)
	{
		AchieveC = itr->second;

		if (!AchieveC)
			continue;

		_ACHIEVE_DATA * UserData = GetAchieve(AchieveC->mMainID);

		if (UserData->dstats > 3)
		{
			switch(AchieveC->mType)
			{
			case 0:
				Normal++;
				break;
			case 1:
				Quest++;
				break;
			case 2:
				War++;
				break;
			case 3:
				Adventure++;
				break;
			case 4:
				Challenge++;
				break;
			}
		}
	}

	result << Normal
		<< Quest
		<< War
		<< Adventure
		<< Challenge;
	Send(&result);
}

void CUser::HandleChallengeFailed(uint8 bType)
{
	if (bType != 1)
		UpdateChallengeStatus(ActiveAchieveChallenge, 0);

	Packet result(WIZ_ACHIEVE, uint8(AchieveChallengeDone));
	result << ActiveAchieveChallenge;

	Send(&result);
}

void CUser::HandleChallengeStart(Packet & pkt)
{
	if (ActiveAchieveChallenge != 0)
	{
		HandleChallengeFailed(1);
		return;
	}

	uint16 cMainID = pkt.read<uint16>();
	_ACHIEVE_MAIN * pAchieveMain = g_pMain->m_AchieveMainArray.GetData(cMainID);

	StartChallengeStatus(cMainID);

	Packet result(WIZ_ACHIEVE,uint8(AchieveChallengeStart));
	result << cMainID
		<< uint16(AchieveSuccess)
		<< uint16(pAchieveMain->mTime);
	Send(&result);
}

void CUser::HandleChallengeCancel(Packet & pkt)
{
	uint16 cMainID = pkt.read<uint16>();

	UpdateChallengeStatus(cMainID, 0);

	Packet result(WIZ_ACHIEVE,uint8(AchieveChallengeCancel));
	result << cMainID
		<< uint16(AchieveSuccess);
	Send(&result);
}

void CUser::HandleAchieveCoverTitle(Packet & pkt)
{
	uint16 tMainID = pkt.read<uint16>();
	uint16 tAchieveID = pkt.read<uint16>();
	
	iCoverTitle = tAchieveID;

	Packet result (WIZ_ACHIEVE, uint8(AchieveCover));
	result << tMainID
		<< tAchieveID
		<< uint8(AchieveSuccess)
		<< uint16(0)
		<< uint8(0);

	Send(&result);
}

void CUser::HandleAchieveSkillTitle(Packet & pkt)
{
	uint16 tMainID = pkt.read<uint16>();
	uint16 tAchieveID = pkt.read<uint16>();

	iSkillTitle = tAchieveID;
	SetUserAbility();

	Packet result (WIZ_ACHIEVE, uint8(AchieveSkill));
	result << tMainID
		<< tAchieveID
		<< uint8(AchieveSuccess)
		<< uint16(0)
		<< uint8(0);

	Send(&result);
}

void CUser::HandleAchieveCoverTitleReset(Packet & pkt)
{
	iCoverTitle = 0;
	Packet result(WIZ_ACHIEVE, uint8(AchieveCoverReset));
	result << uint8(AchieveSuccess)
		<< uint16(0)
		<< uint8(0);

	Send(&result);
}

void CUser::HandleAchieveSkillTitleReset(Packet & pkt)
{
	iSkillTitle = 0;
	SetUserAbility();

	Packet result(WIZ_ACHIEVE, uint8(AchieveSkillReset));
	result << uint8(AchieveSuccess)
		<< uint16(0)
		<< uint8(0);

	Send(&result);
}

void CUser::UpdateAchieveStatus(uint32 SkillID)
{
	_ACHIEVE_TITLE * pAchieveT = g_pMain->m_AchieveTitleArray.GetData(SkillID);
	ItemBonusMap bonusMap;

	if (!pAchieveT)
		return;

	SetStatBuff3(STAT_STR, pAchieveT->cStrB);
	SetStatBuff3(STAT_STA, pAchieveT->cStaB);
	SetStatBuff3(STAT_DEX, pAchieveT->cDexB);
	SetStatBuff3(STAT_INT, pAchieveT->cIntB);
	SetStatBuff3(STAT_CHA, pAchieveT->cChaB);
	m_sTotalHit		+= pAchieveT->cAttack;
	m_sTotalAc		+= pAchieveT->cAC;
	c_AchieveNP		+= pAchieveT->cNPContribu;
	c_AchieveXP		+= pAchieveT->cExpPct;
	m_sDaggerR += pAchieveT->cSSwordAC;
	m_sJamadarR += pAchieveT->cJamadarAC;
	m_sSwordR += pAchieveT->cSwordAC;
	m_sAxeR += pAchieveT->cAxeAC;
	m_sMaceR += pAchieveT->cBlowAC;
	m_sSpearR += pAchieveT->cSpearAC;
	m_sBowR += pAchieveT->cArrowAC;
	bonusMap.insert(std::make_pair(ITEM_TYPE_FIRE, pAchieveT->cFlameB));
	bonusMap.insert(std::make_pair(ITEM_TYPE_COLD, pAchieveT->cIceB));
	bonusMap.insert(std::make_pair(ITEM_TYPE_LIGHTNING, pAchieveT->cLightB));
	m_sFireR += pAchieveT->cFireR;
	m_sColdR += pAchieveT->cIceR;
	m_sLightningR += pAchieveT->cLightR;
	m_sMagicR += pAchieveT->cMagicR;
	m_sDiseaseR += pAchieveT->cCurseR;
	m_sPoisonR += pAchieveT->cPoisonR;
}

void CUser::GiveAchieve(uint16 Title)
{ 
	if (Title >= ACHIEVE_TOTAL)
		return;

	_ACHIEVE_DATA * aUser = GetAchieve(Title);
	_ACHIEVE_MAIN * pMain = g_pMain->m_AchieveMainArray.GetData(Title);

	aUser->dstats = 4;
	aPoints += pMain->mPoints;
	iRecently3 = iRecently2;
	iRecently2 = iRecently1;
	iRecently1 = Title;


	Packet result(WIZ_ACHIEVE);
	result << uint8(AchieveSuccess)
		<< uint16(Title);
	Send(&result);
}

void CUser::ResetAchieve()
{
	for (int p = 1; p < ACHIEVE_TOTAL; p++)
	{
		_ACHIEVE_DATA * aUser = GetAchieve(p);

		aUser->dstats = 0;
		aUser->dSlot1 = 0;
		aUser->dSlot2 = 0;
	}

	iCoverTitle = 0;
	iSkillTitle = 0;
	m_AchieveTimeIn = 0;
	MonDefeatCount = 0;
	UserDefeatCount = 0;
	UserDeathCount = 0;
	aPoints = 0;
	iRecently1 = 0;
	iRecently2 = 0;
	iRecently3 = 0;
}

bool CUser::aIsPlayer(uint16 ID)
{
	if (ID > 0)
		return false;

	return true;
}

void CUser::StartChallengeStatus(uint16 ID)
{
	_ACHIEVE_DATA * aUser = GetAchieve(ID);

	ActiveAchieveChallenge = ID;
	aChallengeTime = UNIXTIME;
	aCount = 1;
	aUser->dstats = 3;
	aUser->dSlot1 = 0;
}

void CUser::UpdateChallengeStatus(uint16 ID, uint8 bType)
{
	_ACHIEVE_DATA * aUser = GetAchieve(ID);
	if (bType == 0)
	{
		aUser->dSlot1 = aCount;
		aUser->dstats = 0;
		memset(&m_aKillCounts, 0, sizeof(m_aKillCounts));
	}

	ActiveAchieveChallenge = 0;
	aChallengeTime = 0;
	aCount = 1;
}

void CUser::AchieveUpdateKills(uint16 sNpcID)
{
	ChallengeMonsterCountAdd(sNpcID);
	AchieveMainCount(sNpcID, 0, 0, 0);
}

void CUser::AchieveMainCount(uint16 nNpcID, uint16 wType, uint16 cQuestNum, uint16 gKind, bool bKilled /* false */)
{
	uint8 aZoneNum;

	if (GetZoneID() == 21 || GetZoneID() == 22 || GetZoneID() == 23	
		|| GetZoneID() == 24 || GetZoneID() == 25)
		aZoneNum = 21;
	else if (GetZoneID() == 1 || GetZoneID() == 5 || GetZoneID() == 6 
		|| GetZoneID() == 2 || GetZoneID() == 7	|| GetZoneID() == 8)
		aZoneNum = 1;
	else if (GetZoneID() == 61 || GetZoneID() == 62	|| GetZoneID() == 63
		|| GetZoneID() == 64 || GetZoneID() == 65)
		aZoneNum = 61;
	else
		aZoneNum = GetZoneID();

	for (int g = 0; g < ACHIEVE_TOTAL; g++)
	{
		_ACHIEVE_MAIN * pMain = g_pMain->m_AchieveMainArray.GetData(g);

		if(!pMain)
			continue;

		if (pMain->mKind == 4 && pMain->mType == 4)
			continue;

		if (pMain->mZoneNum > 2)
			if (pMain->mZoneNum != aZoneNum)
				continue;

		switch (pMain->mKind)
		{
			case 1:
				UserControl(pMain->mMainID, wType, bKilled);
				break;
			case 2:
				NpcKillControl(pMain->mMainID, nNpcID, bKilled);
				break;
			case 3:	
				QuestControl(pMain->mMainID, cQuestNum);
				break;
			case 4:	
				TitlesControl(pMain->mMainID, gKind);
				break;
			case 5:	
				break;
			default:
				TRACE("Unhandle Main King = %d", pMain->mKind);
				break;
		}
	}	
}

void CUser::UserControl(uint16 MainID, uint16 wType, bool wKilled /* default false*/)
{
	if (wType == 0)
		return;

	_ACHIEVE_DATA * aUser = GetAchieve(MainID);
	_ACHIEVE_WAR * pWar = g_pMain->m_AchieveWarArray.GetData(MainID);
	_ACHIEVE_MAIN * pMain = g_pMain->m_AchieveMainArray.GetData(MainID);

	if (pWar->wType != wType)
		return;

	switch (pWar->wType)
	{
		case 1:	
			{
				if (aUser->dstats > 0)
					return;

				aUser->dSlot1++;
			
				if (aUser->dSlot1 >= pWar->wKillCount)
					GiveAchieve(MainID);					
			}
			break;
		case 3:	
			{
				if (aUser->dstats > 0)
					return;

				aUser->dSlot1++;
			
				if (aUser->dSlot1 >= pWar->wKillCount)
					GiveAchieve(MainID);					
			}
			break;
		case 4:
			{
				if (aUser->dstats > 0)
					return;

				aUser->dSlot1++;
			
				if (aUser->dSlot1 >= pWar->wKillCount)
					GiveAchieve(MainID);					
			}
			break;
		case 5:	

			break;
		case 6:	
			{
				if (aUser->dstats > 0)
					return;

				aUser->dSlot1++;
			
				if (aUser->dSlot1 >= pWar->wKillCount)
					GiveAchieve(MainID);	
			}
			break;
		case 7:	
			{
				if (aUser->dstats > 0)
					return;

				aUser->dSlot1++;
			
				if (aUser->dSlot1 >= pWar->wKillCount)
					GiveAchieve(MainID);	
			}
			break;
		case 8:	
			{
				if (aUser->dstats > 0)
					return;

				aUser->dSlot1++;
			
				if (aUser->dSlot1 >= pWar->wKillCount)
					GiveAchieve(MainID);	
			}
			break;
		case 9:	
			{
				if (aUser->dstats > 0)
					return;

				aUser->dSlot1++;
			
				if (aUser->dSlot1 >= pWar->wKillCount)
					GiveAchieve(MainID);	
			}
			break;
		case 10:
			{
				if (aUser->dstats > 0)
					return;

				aUser->dSlot1++;
			
				if (aUser->dSlot1 >= pWar->wKillCount)
					GiveAchieve(MainID);	
			}
			break;
		case 20:
			if (wKilled)
			{
				if (pMain->mKilledType == 5)
				{
					if (aUser->dstats > 0)
						return;

					aUser->dSlot1 = 0;
					aUser->dSlot2 = 0;
				}
			}
			else
			{
				if (aUser->dstats > 0)
				return;

				aUser->dSlot1++;
			
				if (aUser->dSlot1 >= pWar->wKillCount)
					GiveAchieve(MainID);
			}
			break;


		default:
			TRACE("Unhandle WarType = %d", pWar->wType);
			break;
	}
}

void CUser::NpcKillControl(uint16 MainID, uint16 mNpcID, bool mKilled /* false */)
{
	if (mNpcID == 0)
		return;

	_ACHIEVE_DATA * aUser = GetAchieve(MainID);
	_ACHIEVE_MON * pMon = g_pMain->m_AchieveMonArray.GetData(MainID);
	_ACHIEVE_MAIN * pMain = g_pMain->m_AchieveMainArray.GetData(MainID);

	if (aUser->dstats > 0)
		return;

	if (pMain->mKilledType == 5)
		if (mKilled)
		{
			aUser->dSlot1 = 0;
			aUser->dSlot2 = 0;
			return;
		}

	int Count = 0;
	bool AlreadyUp = false;
	for (int i = 0; i < ACHIEVE_MOBS_PER_GROUP; i++)
	{
		if (pMon->oSsid[Count][i] != mNpcID)
			continue;
		if (AlreadyUp)
			continue;
		if (aUser->dSlot1 >= pMon->oCount[Count])
			continue;
				
		aUser->dSlot1++;
		AlreadyUp = true;
	}

	Count = 1;
	AlreadyUp = false;
	if (pMon->oType2 != 0)
		for (int i = 0; i < ACHIEVE_MOBS_PER_GROUP; i++)
		{
			if (pMon->oSsid[Count][i] != mNpcID)
				continue;
			if (AlreadyUp)
				continue;
			if (aUser->dSlot2 >= pMon->oCount[Count])
				continue;
					
			aUser->dSlot2++;
			AlreadyUp = true;
		}

	if (aUser->dSlot1 >= pMon->oCount[0])
		if (pMon->oType2 != 0)
		{
			if (aUser->dSlot2 >= pMon->oCount[1])
				GiveAchieve(MainID);
		}
		else
			GiveAchieve(MainID);
}

void CUser::QuestControl(uint16 MainID, uint16 cQuestNum)
{
	if (cQuestNum == 0)
		return;

	_ACHIEVE_DATA * aUser = GetAchieve(MainID);
	_ACHIEVE_COM * pCom = g_pMain->m_AchieveComArray.GetData(MainID);
	_ACHIEVE_MAIN * pMain = g_pMain->m_AchieveMainArray.GetData(MainID);

	if (aUser->dstats > 0)
		return;

	if (pCom->cQuest1 == cQuestNum)
			aUser->dSlot1++;
	if (pCom->cQuest2 != 0)
		if (pCom->cQuest2 == cQuestNum)
			aUser->dSlot2++;

	if (pCom->cQuest2 == 0)
	{
		if (aUser->dSlot1 >= 1)
			GiveAchieve(MainID);
	}
	else
	{
		if (aUser->dSlot1 >= 1 && aUser->dSlot2 >= 1)
			GiveAchieve(MainID);
	}
}

void CUser::TitlesControl(uint16 MainID, uint16 gKind)
{
	if (gKind == 0)
		return;

	_ACHIEVE_DATA * aUser = GetAchieve(MainID);
	_ACHIEVE_NORMAL * pNor = g_pMain->m_AchieveNormalArray.GetData(MainID);
	_KNIGHTS_SIEGE_WARFARE *pKnightSiege = g_pMain->GetSiegeMasterKnightsPtr(1);

	if (pNor->nType != gKind)
		return;
	
	switch (pNor->nType)
		{
			case 1:
				{
					if (!isKing())
						return;

					if (aUser->dstats > 0)
						return;

					aUser->dSlot1++;

					if (aUser->dSlot1 >= pNor->nTypeCount)
						GiveAchieve(MainID);
				}
				 break;
			case 2:	
				{
					if (aUser->dstats > 0)
						return;

					aUser->dSlot1 += aUserContrib;

					if (aUser->dSlot1 >= pNor->nTypeCount)
						GiveAchieve(MainID);
				}
				 break;
			case 3:	
				{
					if (aUser->dstats > 0)
						return;

					aUser->dSlot1 = GetLevel();

					if (aUser->dSlot1 >= pNor->nTypeCount)
						GiveAchieve(MainID);
				}
				 break;
			case 5:
				{
					if (aUser->dstats > 0)
						return;

					aUser->dSlot1 += aKnightContrib;

					if (aUser->dSlot1 >= pNor->nTypeCount)
						GiveAchieve(MainID);
				}
				 break;
			case 10:
				{
					if (MainID == 419)
					{
						if (aUser->dstats > 0)
							return;
					}
					if (MainID == 420)
					{
						if (aUser->dstats > 0)
							return;

						aUser->dSlot1++;

						if (aUser->dSlot1 >= pNor->nTypeCount)
							GiveAchieve(MainID);
					}
					if (MainID = 421)
					{
						if (aUser->dstats > 0)
						return;

						if (m_bKnights != pKnightSiege->sChallengeList_1)
							return;

						aUser->dSlot1++;

						if (aUser->dSlot1 >= pNor->nTypeCount)
							GiveAchieve(MainID);
					}
				}
				 break;
			default:
				break;
		}
}

void CUser::ChallengeMonsterCountAdd(uint16 sNpcID)
{
	if (ActiveAchieveChallenge == 0)
		return;

	uint16 ChallengeNum = ActiveAchieveChallenge;
	_ACHIEVE_MAIN * pMain = g_pMain->m_AchieveMainArray.GetData(ChallengeNum);
	_ACHIEVE_MON * pMon = g_pMain->m_AchieveMonArray.GetData(ChallengeNum);
	_ACHIEVE_WAR * pWar = g_pMain->m_AchieveWarArray.GetData(ChallengeNum);
	_ACHIEVE_DATA * aUser = GetAchieve(ChallengeNum);

	if (!aIsPlayer(sNpcID))
	{
		if (pMain->mZoneNum > 2)
			if (pMain->mZoneNum != GetZoneID())
				return;

			int Count = 0;
			for (int i = 0; i < ACHIEVE_MOBS_PER_GROUP; i++)
			{
				if (pMon->oSsid[Count][i] != sNpcID)
					continue;
				
				if (m_aKillCounts[Count] + 1 > pMon->oCount[Count])
					return;

				m_aKillCounts[Count]++;
			}

			Count = 1;
			if (pMon->oType2 != 0)
				for (int i = 0; i < ACHIEVE_MOBS_PER_GROUP; i++)
				{
					if (pMon->oSsid[Count][i] != sNpcID)
						continue;
						
					if (m_aKillCounts[Count] + 1 > pMon->oCount[Count])
						return;

					m_aKillCounts[Count]++;
				}


		Packet result(WIZ_ACHIEVE, uint8(AchieveChallengeCount));
		result << ChallengeNum << uint8(0) << uint16(m_aKillCounts[0]) << uint16(m_aKillCounts[1]);
		Send(&result);

		if (m_aKillCounts[0] >= pMon->oCount[0])
			if (pMon->oType2 != 0)
			{
				if (m_aKillCounts[1] >= pMon->oCount[1])
				{
					GiveAchieve(ChallengeNum);
					aUser->dSlot1 = pMon->oCount[0];
					aUser->dSlot2 = pMon->oCount[1];
					UpdateChallengeStatus(ChallengeNum, 1);
					aUser->dstats = 5;
				}
			}
			else
			{
				GiveAchieve(ChallengeNum);
				aUser->dSlot1 = pMon->oCount[0];
				UpdateChallengeStatus(ChallengeNum, 1);
				aUser->dstats = 5;
			}
	}
	else
	{
		if (pMain->mZoneNum != 0)
			if (pMain->mZoneNum != GetZoneID())
				return;

		Packet result(WIZ_ACHIEVE, uint8(AchieveChallengeCount));
		result << ChallengeNum << uint8(0) << aCount << uint16(0);
		Send(&result);

		if (aCount >= pWar->wKillCount)
		{
			GiveAchieve(ChallengeNum);
			aUser->dSlot1 = aCount;
			UpdateChallengeStatus(ChallengeNum, 1);
			aUser->dstats = 5;
		}

		aCount++;
	}
}