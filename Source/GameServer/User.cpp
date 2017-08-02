#include "stdafx.h"
#include "Map.h"
#include "KnightsManager.h"
#include "KingSystem.h"
#include "MagicInstance.h"
#include "DBAgent.h"
#include <algorithm>
#include "../shared/DateTime.h"

using namespace std;

CUser::CUser(uint16 socketID, SocketMgr *mgr) : KOSocket(socketID, mgr, -1, 16384, 3172), Unit(UnitPlayer)
{
}

void CUser::OnConnect()
{
	KOSocket::OnConnect();
	Initialize();
}

void CUser::Initialize()
{
	Unit::Initialize();

	m_strUserID.clear();
	m_strMemo.clear();
	m_strAccountID.clear();
	m_bLogout = 0;

	m_FlashExpBonus = 0;
	m_FlashDcBonus = 0;
	m_FlashWarBonus = 0;

	m_LastConferedTime = UNIXTIME;
	m_LastTraining = UNIXTIME;
	m_GenieTime = 0; 
	memset(m_GenieOptions, 0, sizeof(m_GenieOptions));
	m_tGenieTimeNormal = UNIXTIME;

	m_bAuthority = 1;
	m_sBind = -1;

	m_TrainingExp = 0;
	m_TrainingTime = 0;

	m_VipKeyTime = 0;
	m_VipPass = 0;
	nPassError = 0;

	m_AchieveTimeIn = 0;
	m_AchieveTimeOut = 0;
	m_tAchieveGameStartTime = UNIXTIME;
	MonDefeatCount = 0;
	UserDefeatCount = 0;
	UserDeathCount = 0;
	c_AchieveNP = 0;
	c_AchieveXP = 0;
	ActiveAchieveChallenge = 0;
	aChallengeTime = 0;
	aUserContrib = 0;
	aKnightContrib = 0;

	m_state = GAME_STATE_CONNECTED;

	m_bSelectedCharacter = false;
	m_bStoreOpen = false;
	m_bPartyLeader = false;
	m_bIsChicken = false;
	m_bIsHidingHelmet = false;
	m_bIsHidingCospre = false;
	m_bMining = false;
	m_bPremiumMerchant = false;
	m_bInParty = false;

	m_tLastMiningAttempt = 0;

	m_bMerchantState = MERCHANT_STATE_NONE;
	m_bInvisibilityType = INVIS_NONE;

	m_sDirection = 0;

	m_sItemMaxHp = m_sItemMaxMp = 0;
	m_sItemWeight = 0;
	m_sItemAc = 0;

	m_sExpGainAmount = m_bNPGainAmount = m_bNoahGainAmount = 100;
	m_bItemExpGainAmount = m_bItemNoahGainAmount = 0;
	m_bItemNPBonus = m_bSkillNPBonus = 0;

	m_byAPBonusAmount = 0;
	memset(&m_byAPClassBonusAmount, 0, sizeof(m_byAPClassBonusAmount));
	memset(&m_byAcClassBonusAmount, 0, sizeof(m_byAcClassBonusAmount));

	memset(&m_bStats, 0, sizeof(m_bStats));
	memset(&m_sStatItemBonuses, 0, sizeof(m_sStatItemBonuses));
	memset(&m_bStatBuffs, 0, sizeof(m_bStatBuffs));
	memset(&m_bStatBuffs2, 0, sizeof(m_bStatBuffs2));
	memset(&m_bStatBuffs3, 0, sizeof(m_bStatBuffs3));
	memset(&m_bRebStatBuffs, 0, sizeof(m_bRebStatBuffs));
	memset(&m_bstrSkill, 0, sizeof(m_bstrSkill));

	m_bPlayerAttackAmount = 100;

	m_bAddWeaponDamage = 0;
	m_bPctArmourAc = 100;
	m_sAddArmourAc = 0;

	m_sItemHitrate = 100;
	m_sItemEvasionrate = 100;

	m_sSpeed = 0;

	m_bAuthority = AUTHORITY_PLAYER;
	m_bLevel = 1;
	m_iExp = 0;
	m_iBank = m_iGold = 0;
	m_iLoyalty = m_iLoyaltyMonthly = 0;
	m_iMannerPoint = 0;
	m_sHp = m_sMp = m_sSp = 0;

	m_iMaxHp = 0;
	m_iMaxMp = 1;
	m_iMaxSp = 0;
	m_iMaxExp = 0;
	m_sMaxWeight = 0;
	m_sMaxWeightBonus = 0;

	m_bResHpType = USER_STANDING;
	m_bWarp = false;

	m_sMerchantsSocketID = -1;
	m_sChallengeUser = -1;
	m_sPartyIndex = -1;		
	m_sExchangeUser = -1;
	m_ChatRoomIndex	= 1;
	m_bRequestingChallenge = 0;
	m_bChallengeRequested = 0;
	m_bExchangeOK = 0x00;
	m_bBlockPrivateChat = false;
	m_sPrivateChatUser = -1;
	m_bNeedParty = 0x01;

	m_tHPLastTimeNormal = 0;
	m_tHPStartTimeNormal = 0;
	m_bHPAmountNormal = 0;
	m_bHPDurationNormal = 0;
	m_bHPIntervalNormal = 5;

	m_tGameStartTimeSavedMagic = 0;

	m_fSpeedHackClientTime = 0;
	m_fSpeedHackServerTime = 0;
	m_bSpeedHackCheck = 0;

	m_tBlinkExpiryTime = 0;

	m_bAbnormalType = ABNORMAL_NORMAL;
	m_nOldAbnormalType = m_bAbnormalType;

	m_sWhoKilledMe = -1;
	m_iLostExp = 0;

	m_tLastTrapAreaTime = 0;

	memset(m_iSelMsgEvent, -1,  MAX_MESSAGE_EVENT);

	m_sEventNid = m_sEventSid = -1;
	m_nQuestHelperID = 0;
	m_bZoneChangeFlag = false;
	m_bRegeneType = 0;
	m_tLastRegeneTime = 0;
	m_bZoneChangeSameZone = false;

	m_transformationType = TransformationNone;
	m_sTransformID = 0;
	m_tTransformationStartTime = 0;
	m_sTransformationDuration = 0;

	memset(&m_aKillCounts, 0, sizeof(m_aKillCounts));
	memset(&m_bKillCounts, 0, sizeof(m_bKillCounts));
	
	m_sEventDataIndex = 0;

	m_pKnightsUser = nullptr;

	m_sRivalID = -1;
	m_tRivalExpiryTime = 0;

	m_byAngerGauge = 0;

	m_bWeaponsDisabled = false;

	m_teamColour = TeamColourNone;
	m_iLoyaltyDaily = 0;
	m_iLoyaltyPremiumBonus = 0;
	m_KillCount = 0;
	m_DeathCount = 0;
	
	m_bGenieStatus = false;

	m_bAccountStatus = 0;
	m_bPremiumInUse = 0;
	m_bPremiumCount = 0;

	m_LastX = 0;
	m_LastZ = 0;

	JuraidSpot = 0;	

	sCordKarusX[0] = 800;
	sCordKarusX[1] = 690;
	sCordKarusX[2] = 512;
	sCordKarusZ[0] = 334;
	sCordKarusZ[1] = 172;
	sCordKarusZ[2] = 282;

	sCordElmoradX[0] = 223;
	sCordElmoradX[1] = 340;
	sCordElmoradX[2] = 512;
	sCordElmoradZ[0] = 672;
	sCordElmoradZ[1] = 847;
	sCordElmoradZ[2] = 736;

	nExpRebirth[0] = 8705986960;
	nExpRebirth[1] = 9576585656;
	nExpRebirth[2] = 10534244222;
	nExpRebirth[3] = 11587668644;
	nExpRebirth[4] = 12746435508;
	nExpRebirth[5] = 14021079059;
}

void CUser::OnDisconnect()
{
	KOSocket::OnDisconnect();

	g_pMain->RemoveSessionNames(this);

	if (isInGame())
	{
		UserInOut(INOUT_OUT);

		if (isInParty())
			if (isPartyLeader())
			{
				_PARTY_GROUP * pParty = g_pMain->GetPartyPtr(GetPartyID());
				PartyPromote(pParty->uid[1]);
			}
			PartyRemove(GetSocketID());

		if (isInClan())
		{
			CKnights *pKnights = g_pMain->GetClanPtr(GetClanID());
			_KNIGHTS_ALLIANCE *pAllianceKnights = g_pMain->GetAlliancePtr(pKnights->GetAllianceID());
			if (pAllianceKnights != nullptr)
				pKnights->OnLogoutAlliance(this);
			else if (pKnights != nullptr)
				pKnights->OnLogout(this);
		}

		ResetWindows();

		if (hasRival())
			RemoveRival();
	}
	LogOut();
}


bool CUser::HandlePacket(Packet & pkt)
{
	uint8 command = pkt.GetOpcode();

	if (command == WIZ_VIP_INN)
		TRACE("[SID=%d] Packet: %X (len=%d)\n", GetSocketID(), command, pkt.size());

	if (!isCryptoEnabled())
	{
		if (command == WIZ_VERSION_CHECK)
			VersionCheck(pkt);

		return true;
	}
	else if (m_strAccountID.empty())
	{
		if (command == WIZ_LOGIN)
			LoginProcess(pkt);

		return true;
	}

	else if (!m_bSelectedCharacter)
	{
		switch (command)
		{
		case WIZ_SEL_NATION:
			SelNationToAgent(pkt);
			break;
		case WIZ_ALLCHAR_INFO_REQ:
			AllCharInfo(pkt);
			break;
		case WIZ_CHANGE_HAIR:
			ChangeHair(pkt);
			break;
		case WIZ_NEW_CHAR:
			NewCharToAgent(pkt);
			break;
		case WIZ_DEL_CHAR:
			DelCharToAgent(pkt);
			break;
		case WIZ_SEL_CHAR:
			SelCharToAgent(pkt);
			break;
		case WIZ_SPEEDHACK_CHECK:
			SpeedHackTime(pkt);
			break;
		case WIZ_LOAD_GAME:
			LoadGame(pkt);
			break;

		default:
			printf("[SID=%d] Unhandled packet (%X) prior to selecting character\n", GetSocketID(), command);
			break;
		}
		return true;
	}

	switch (command)
	{
	case WIZ_GAMESTART:
		GameStart(pkt);
		break;
	case WIZ_SERVER_INDEX:
		SendServerIndex();
		break;
	case WIZ_RENTAL:
		RentalSystem(pkt);
		break;
	case WIZ_SKILLDATA:
		SkillDataProcess(pkt);
		break;
	case WIZ_MOVE:
		MoveProcess(pkt);
		break;
	case WIZ_ROTATE:
		Rotate(pkt);
		break;
	case WIZ_ATTACK:
		Attack(pkt);
		break;
	case WIZ_CHAT:
		Chat(pkt);
		break;
	case WIZ_CHAT_TARGET:
		ChatTargetSelect(pkt);
		break;
	case WIZ_REGENE:	
		Regene(pkt.read<uint8>());
		break;
	case WIZ_REQ_USERIN:
		RequestUserIn(pkt);
		break;
	case WIZ_REQ_NPCIN:
		RequestNpcIn(pkt);
		break;
	case WIZ_WARP:
		if (isGM())
			RecvWarp(pkt);
		break;
	case WIZ_ITEM_MOVE:
		ItemMove(pkt);
		break;
	case WIZ_NPC_EVENT:
		NpcEvent(pkt);
		break;
	case WIZ_ITEM_TRADE:
		ItemTrade(pkt);
		break;
	case WIZ_TARGET_HP:
		{
			uint16 uid = pkt.read<uint16>();
			uint8 echo = pkt.read<uint8>();
			m_targetID = uid;
			SendTargetHP(echo, uid);
		}
		break;
	case WIZ_BUNDLE_OPEN_REQ:
		BundleOpenReq(pkt);
		break;
	case WIZ_ITEM_GET:
		ItemGet(pkt);
		break;
	case WIZ_ZONE_CHANGE:
		RecvZoneChange(pkt);
		break;
	case WIZ_POINT_CHANGE:
		PointChange(pkt);
		break;
	case WIZ_STATE_CHANGE:
		StateChange(pkt);
		break;
	case WIZ_PARTY:
		PartyProcess(pkt);
		break;
	case WIZ_EXCHANGE:
		ExchangeProcess(pkt);
		break;
	case WIZ_QUEST:
		QuestV2PacketProcess(pkt);
		break;
	case WIZ_MERCHANT:
		MerchantProcess(pkt);
		break;
	case WIZ_MAGIC_PROCESS:
		CMagicProcess::MagicPacket(pkt, this);
		break;
	case WIZ_SKILLPT_CHANGE:
		SkillPointChange(pkt);
		break;
	case WIZ_OBJECT_EVENT:
		ObjectEvent(pkt);
		break;
	case WIZ_WEATHER:
	case WIZ_TIME:
		UpdateGameWeather(pkt);
		break;
	case WIZ_CLASS_CHANGE:
		ClassChange(pkt);
		break;
	case WIZ_CONCURRENTUSER:
		CountConcurrentUser();
		break;
	case WIZ_DATASAVE:
		UserDataSaveToAgent();
		break;
	case WIZ_ITEM_REPAIR:
		ItemRepair(pkt);
		break;
	case WIZ_KNIGHTS_PROCESS:
		CKnightsManager::PacketProcess(this, pkt);
		break;
	case WIZ_ITEM_REMOVE:
		ItemRemove(pkt);
		break;
	case WIZ_OPERATOR:
		OperatorCommand(pkt);
		break;
	case WIZ_SPEEDHACK_CHECK:
		SpeedHackTime(pkt);
		break;
	case WIZ_WAREHOUSE:
		WarehouseProcess(pkt);
		break;
	case WIZ_VIP_INN:
		VIPhouseProcess(pkt);
		break;
	case WIZ_HOME:
		Home();
		break; 
	case WIZ_FRIEND_PROCESS:
		FriendProcess(pkt);
		break;
	case WIZ_WARP_LIST:
		SelectWarpList(pkt);
		break;
	case WIZ_VIRTUAL_SERVER:
		ServerChangeOk(pkt);
		break;
	case WIZ_PARTY_BBS:
		PartyBBS(pkt);
		break;
	case WIZ_MAP_EVENT:
		break;
	case WIZ_CLIENT_EVENT:
		ClientEvent(pkt.read<uint16>());
		break;
	case WIZ_SELECT_MSG:
		RecvSelectMsg(pkt);
		break;
	case WIZ_ITEM_UPGRADE:
		ItemUpgradeProcess(pkt);
		break;
	case WIZ_EVENT:
		TempleProcess(pkt);
		break;
	case WIZ_SHOPPING_MALL:
		ShoppingMall(pkt);
		break;
	case WIZ_NAME_CHANGE:
		HandleNameChange(pkt);
		break;
	case WIZ_KING:
		CKingSystem::PacketProcess(this, pkt);
		break;
	case WIZ_HELMET:
        HandleHelmet(pkt);
    break;
	case WIZ_CAPE:
		HandleCapeChange(pkt);
		break;
	case WIZ_CHALLENGE:
		HandleChallenge(pkt);
		break;
	case WIZ_RANK:
		HandlePlayerRankings(pkt);
		break;
	case WIZ_MINING:
		HandleMiningSystem(pkt);
		break;
	case WIZ_SIEGE:
		SiegeWarFareNpc(pkt);
		break;
	case WIZ_LOGOSSHOUT:
		LogosShout(pkt);
		break;
	case WIZ_GENIE:
		HandleGenie(pkt);
		break;
	case WIZ_CAPTURE:
		HandleCapture(pkt);
		break;
	case WIZ_USER_INFO:
		HandleUserInfo(pkt);
		break;
	case WIZ_ACHIEVE:
		Achieve(pkt);
		break;
	case WIZ_NATION_CHAT:
		ChatRoomHandle(pkt);
		break;
	case WIZ_ALLCHAR_INFO_REQ:
		AllCharInfo(pkt);
		break;
	case WIZ_EXP_SEAL:
		ExpSealSystem(pkt);
		break;
	case WIZ_CHANGE_HAIR:
		CanChangeHair(pkt);
		break;
	case WIZ_NATION_TRANSFER:
		RecvNationTransfer(pkt);
		break;
	case WIZ_PREMIUM:
		RecvPremium(pkt);
		break;
	case WIZ_GENDER_CHANGE:
		RecvGenderChange(pkt);
		break;
	case WIZ_PET:
		PetHandle(pkt);
		break;

	default:
		TRACE("[SID=%d] Unknown packet %X\n", GetSocketID(), command);
		return false;
	}

	Update();
	return true;
}

void CUser::Update()
{
	if (m_tGameStartTimeSavedMagic != 0 && (UNIXTIME - m_tGameStartTimeSavedMagic) >= 2)
	{
		m_tGameStartTimeSavedMagic = 0;
		InitType4();
		RecastSavedMagic();
	}

	if (!isBlinking() && m_tHPLastTimeNormal != 0 && (UNIXTIME - m_tHPLastTimeNormal) > m_bHPIntervalNormal)
		HPTimeChange();

	if ((UNIXTIME - m_tSPLastTimeNormal) > PLAYER_STAMINA_INTERVAL)
		StaminaTimeChange();

	if (m_VipKeyTime != 0 && UNIXTIME >= m_VipKeyTime)
	{
		m_VipKeyTime = 0;

		Packet result(WIZ_VIP_INN);
		result << uint8(VIPHOUSE_KEY_EXPIRE)
			<< uint8(1);
		Send(&result);
	}

	if ((UNIXTIME - m_tLastPremiumCheck) > PREMIUM_TIME_CHECK)
	{
		m_tLastPremiumCheck = UNIXTIME;
		m_bPremiumExCount = 0;
		bool Expiration = false;

		for (int i = 0; i < PREMIUM_TOTAL; i++)
		{
			_PREMIUM_DATA * uPrem = GetPremiumPtr(i);

			if (!uPrem)
				continue;
			if (uPrem->pType == 0)
				continue;
			if (uPrem->pType != 0 && uPrem->pTime > UNIXTIME)
			{
				m_bPremiumExCount++;
				continue;
			}

			uPrem->pType = 0;
			uPrem->pTime = 0;
			Expiration = true;
		}

		if (Expiration)
			SendPremiumExpire();
	}

	if (m_bType3Flag) 
		HPTimeChangeType3();	

	Type4Duration();
	CheckSavedMagic();

	if (isTransformed())
		CMagicProcess::CheckExpiredType6Skills(this);

	CMagicProcess::CheckExpiredType9Skills(this);

	if (isBlinking())
		BlinkTimeCheck();

	if (hasRival() && hasRivalryExpired())
		RemoveRival();

	if ((UNIXTIME - m_lastUpdatedAchieveTime) >= ACHIEVE_TIME_UPDATE)
		m_AchieveTimeOut = uint32(m_AchieveTimeIn + ((UNIXTIME- m_tAchieveGameStartTime) / 60));

	if ((UNIXTIME - m_LastTraining) >= PLAYER_TRAINING_INTERVAL)
		SetTrainingMode();

	if ((UNIXTIME - m_LastConferedTime) >= PLAYER_CONF_INTERVAL)
	{
		m_LastConferedTime = UNIXTIME;
		IlegalItemsBanned();
		ItemsDupeDelete();
	}

	if (aChallengeTime != 0)
	{
		_ACHIEVE_MAIN * pAMain = g_pMain->m_AchieveMainArray.GetData(ActiveAchieveChallenge);
		if ((UNIXTIME - aChallengeTime) > pAMain->mTime)
			HandleChallengeFailed(0);
	}

	if ((UNIXTIME - m_lastSaveTime) >= PLAYER_SAVE_INTERVAL)
	{
		m_lastSaveTime = UNIXTIME;
		UserDataSaveToAgent();
	}
	for (int i = 0; i < WAREHOUSE_MAX; i++)
	{
		_ITEM_DATA *pItem = &m_sWarehouseArray[i];

		if(pItem == nullptr)
		continue; 

		if (pItem->nExpirationTime < (uint32)UNIXTIME && pItem->nExpirationTime != 0)
			memset(pItem, 0, sizeof(_ITEM_DATA));
	}

	if(m_tGenieTimeNormal + PLAYER_GENIE_INTERVAL < UNIXTIME  && isGenieActive())
	{
		m_tGenieTimeNormal = UNIXTIME;
		UpdateGenieTime(--m_GenieTime);
	}

	for (int i = 0; i < INVENTORY_TOTAL; i++)
	{
		_ITEM_DATA *pItem = &m_sItemArray[i];

		if(pItem == nullptr)
			continue; 

		if (pItem->nExpirationTime < (uint32)UNIXTIME && pItem->nExpirationTime != 0)
			memset(pItem, 0, sizeof(_ITEM_DATA));
	}
}

void CUser::ExpSealSystem(Packet & pkt)
{
     uint8 opcode;
     pkt >> opcode;

     switch (opcode)
	 {
		case On:
			ExpSealOn(pkt);
			break;
		case Off:
			ExpSealOff(pkt);
			break;
		default:
			printf("Unhandled ExpSeal system opcode: %X\n", opcode);
     }
}

void CUser::ExpSealOn(Packet & pkt) 
{    
    Packet result(WIZ_EXP_SEAL,uint8(On));
    result << uint8(1)
		<< uint8(0)
		<< uint8(3);
    Send(&result);
}

void CUser::ExpSealOff(Packet & pkt) 
{    
    Packet result(WIZ_EXP_SEAL,uint8(Off));
    result << uint8(1)
		<< uint8(0)
		<< uint8(3);
    Send(&result);
}

void CUser::SetRival(CUser * pRival)
{
	if (pRival == nullptr
		|| hasRival())
		return;

	Packet result(WIZ_PVP, uint8(PVPAssignRival));
	CKnights * pKnights = nullptr;

	result	<< pRival->GetID()
		<< GetCoins() << GetLoyalty();

	if (pRival->isInClan() 
		&& (pKnights = g_pMain->GetClanPtr(pRival->GetClanID())))
		result << pKnights->GetName();
	else
		result << uint16(0);

	result << pRival->GetName();

	m_sRivalID = pRival->GetID();
	m_tRivalExpiryTime = UNIXTIME + RIVALRY_DURATION;

	Send(&result);
}

void CUser::RemoveRival()
{
	if (!hasRival())
		return;

	m_tRivalExpiryTime = 0;
	m_sRivalID = -1;

	Packet result(WIZ_PVP, uint8(PVPRemoveRival));
	Send(&result);
}

void CUser::SendLoyaltyChange(int32 nChangeAmount /*= 0*/, bool bIsKillReward /* false */, bool bIsBonusReward /* false */, bool bIsAddLoyaltyMonthly /* true */)
{
	Packet result(WIZ_LOYALTY_CHANGE, uint8(NATIONAL_POINTS_NEW));
	uint32 nClanLoyaltyAmount = 0;
	aUserContrib = nChangeAmount;
	uint16 iNationBonus = 0, iLeaderBonus = 0;
	uint32 iOldLoyalt, iOldLeader, iNationAmount;

	int32 nChangeAmountLoyaltyMonthly = nChangeAmount;
	iNationAmount = nChangeAmount;

	if (nChangeAmount < 0)
	{
		uint32 amt = -nChangeAmount;

		if (amt > m_iLoyalty)
			m_iLoyalty = 0;
		else
			m_iLoyalty += nChangeAmount;

		if (bIsKillReward)
		{
			if (bIsAddLoyaltyMonthly)
			{
				if (amt > m_iLoyaltyMonthly)
					m_iLoyaltyMonthly = 0;
				else
					m_iLoyaltyMonthly += nChangeAmountLoyaltyMonthly;
			}
		}
	}
	else
	{
		iOldLoyalt = m_iLoyalty;
		iOldLeader = m_iLoyaltyMonthly;

		nChangeAmount = m_bNPGainAmount * nChangeAmount / 100;
		nChangeAmountLoyaltyMonthly = m_bNPGainAmount * nChangeAmount / 100;

		nChangeAmount = nChangeAmount * (100 + g_pMain->m_byNPEventAmount) / 100;
		nChangeAmountLoyaltyMonthly = nChangeAmountLoyaltyMonthly * (100 + g_pMain->m_byNPEventAmount) / 100;

		if (bIsKillReward)
		{
			nChangeAmount += m_bItemNPBonus + m_bSkillNPBonus;
			nChangeAmountLoyaltyMonthly += m_bItemNPBonus + m_bSkillNPBonus + m_FlashWarBonus;

			if (GetZoneID() == ZONE_RONARK_LAND && GetPVPMonumentNation() == GetNation())
			{
				nChangeAmount += PVP_MONUMENT_NP_BONUS;
				nChangeAmountLoyaltyMonthly += PVP_MONUMENT_NP_BONUS;
			}

			else if ((GetZoneID() == ZONE_BORDER_DEFENSE_WAR || GetZoneID() == ZONE_ARDREAM || GetZoneID() == ZONE_PVP_EVENT || GetZoneID() == ZONE_RONARK_LAND_BASE) 
				&& GetEventMonumentNation() == GetNation())
			{
				nChangeAmount += EVENT_MONUMENT_NP_BONUS;
				nChangeAmountLoyaltyMonthly += EVENT_MONUMENT_NP_BONUS;
			}
		}

		if (m_iLoyalty + nChangeAmount > LOYALTY_MAX)
			m_iLoyalty = LOYALTY_MAX;
		else
			m_iLoyalty += nChangeAmount;

		if (isInPKZone() && !bIsBonusReward)
		{
			m_iLoyaltyDaily += nChangeAmount;
			UpdatePlayerRank();
		}

		if (!bIsBonusReward)
		{
			if (bIsAddLoyaltyMonthly)
			{
				if (m_iLoyaltyMonthly + nChangeAmountLoyaltyMonthly > LOYALTY_MAX)
					m_iLoyaltyMonthly = LOYALTY_MAX;
				else
					m_iLoyaltyMonthly += nChangeAmountLoyaltyMonthly;
			}
		}

		if (bIsKillReward)
		{
			if (GetPremiumProperty(PremiumBonusLoyalty) > 0)
			{
				m_iLoyalty += GetPremiumProperty(PremiumBonusLoyalty);

				if (bIsAddLoyaltyMonthly)
					m_iLoyaltyMonthly += GetPremiumProperty(PremiumBonusLoyalty);

				m_iLoyaltyPremiumBonus += GetPremiumProperty(PremiumBonusLoyalty);
			}
		}

		CKnights * pKnights = g_pMain->GetClanPtr(GetClanID());

		if (pKnights && pKnights->m_byFlag >= ClanTypeAccredited5 && pKnights->GetClanPointMethod() == 0 && !bIsBonusReward)
		{
			if (pKnights->m_sMembers > 0 && pKnights->m_sMembers <= MAX_CLAN_USERS)
			{
				if (pKnights->m_sMembers <= 5)
					nClanLoyaltyAmount = 1;
				else if (pKnights->m_sMembers <= 10)
					nClanLoyaltyAmount = 2;
				else if (pKnights->m_sMembers <= 15)
					nClanLoyaltyAmount = 3;
				else if (pKnights->m_sMembers <= 20)
					nClanLoyaltyAmount = 4;
				else if (pKnights->m_sMembers <= 25)
					nClanLoyaltyAmount = 5;
				else if (pKnights->m_sMembers <= 30)
					nClanLoyaltyAmount = 6;
				else if (pKnights->m_sMembers > 30)
					nClanLoyaltyAmount = 7;

				m_iLoyalty -= nClanLoyaltyAmount;

				nClanLoyaltyAmount += c_AchieveNP;

				CKnightsManager::AddUserDonatedNP(GetClanID(), m_strUserID, nClanLoyaltyAmount, true);
			}
		}
	}

	if (aUserContrib > 0)
		AchieveMainCount(0, 0, 0, 2);

	if (nChangeAmount > 0)
	{
		iNationBonus += ((m_iLoyalty - iOldLoyalt) - iNationAmount);
		iLeaderBonus += ((m_iLoyaltyMonthly - iOldLeader) - iNationAmount);
	}

	result << m_iLoyalty << m_iLoyaltyMonthly
		<< uint32(0)				
		<< nClanLoyaltyAmount
		<< iNationBonus	
		<< iLeaderBonus;

	Send(&result);

	if (bIsKillReward && nChangeAmount > 0)
	{
		if (m_bPremiumInUse > 0 && (isInPKZone() || GetMap()->isWarZone()))
			GoldGain(PVP_BONUS_GOLD+PVP_BONUS_GOLD/2);
		else if (m_bPremiumInUse == 0 && (isInPKZone() || GetMap()->isWarZone()))
			GoldGain(PVP_BONUS_GOLD);

		if (isInPKZone())
			GiveItem(ITEM_MEAT_DUMPLING);
	}
}

void CUser::TempleEventJoin()
{
	if (g_pMain->pTempleEvent.ActiveEvent == TEMPLE_EVENT_JURAD_MOUNTAIN && !isEventUser())
	{
		Packet result (WIZ_SELECT_MSG);
		TempleOperations(TEMPLE_EVENT_JOIN);
		result << uint16(0x00) << uint8(0x07) << uint64(0x00) << uint32(0x06) << g_pMain->pTempleEvent.KarusUserCount << uint16(0x00) << g_pMain->pTempleEvent.ElMoradUserCount << uint16(0x00) << g_pMain->m_nTempleEventRemainSeconds << uint16(0x00);
		Send(&result);
	}
}

void CUser::TempleEventLeave()
{
	if (g_pMain->pTempleEvent.ActiveEvent == TEMPLE_EVENT_JURAD_MOUNTAIN && isEventUser())
	{
		Packet result (WIZ_SELECT_MSG);
		TempleOperations(TEMPLE_EVENT_DISBAND);
		result << uint16(0x00) << uint8(0x07) << uint64(0x00) << uint32(0x06) << g_pMain->pTempleEvent.KarusUserCount << uint16(0x00) << g_pMain->pTempleEvent.ElMoradUserCount << uint16(0x00) << g_pMain->m_nTempleEventRemainSeconds << uint16(0x00);
		Send(&result);
	}
}

void  CUser::SendKnightCash(int32 nCashPoint /*= 0*/)
{
	if (nCashPoint == 0)
		return;

	g_DBAgent.UpdateAccountKnightCash(GetAccountName(), nCashPoint);
}


uint8 CUser::GetRankReward(bool isMonthly)
{
	enum RankErrorCodes
	{
		NoRank				= 0,
		RewardSuccessfull	= 1,
		RewardAlreadyTaken	= 2
	};

	int8 nRank = -1;
	int32 nGoldAmount = 0;

	Guard lock(g_pMain->m_userRankingsLock);

	string strUserID = GetName();
	STRTOUPPER(strUserID);

	UserNameRankMap::iterator itr;

	if (isMonthly)
	{
		itr = g_pMain->m_UserPersonalRankMap.find(strUserID);
		nRank = itr != g_pMain->m_UserPersonalRankMap.end() ? int8(itr->second->nRank) : -1;
	}
	else
	{
		itr = g_pMain->m_UserKnightsRankMap.find(strUserID);
		nRank = itr != g_pMain->m_UserKnightsRankMap.end() ? int8(itr->second->nRank) : -1;
	}

	nRank = 1;

	if (nRank > 0 && nRank <= 100)
	{
		if (nRank == 1)
			nGoldAmount = 1000000;
		else if (nRank >= 2 && nRank <= 4)
			nGoldAmount = 700000;
		else if (nRank >= 5 && nRank <= 10)
			nGoldAmount = 500000;
		else if (nRank >= 11 && nRank <= 40)
			nGoldAmount = 300000;
		else if (nRank >= 41 && nRank <= 100)
			nGoldAmount = 200000;
		else
			nGoldAmount = 0;

		if (nGoldAmount > 0) 
		{
			if (GetUserDailyOp(isMonthly ? DAILY_USER_PERSONAL_RANK_REWARD : DAILY_USER_RANK_REWARD) == 0)
				return RewardAlreadyTaken;

			GoldGain(nGoldAmount);
			return RewardSuccessfull;

		}
	}

	return NoRank;
}


void CUser::ChangeFame(uint8 bFame)
{
	Packet result(WIZ_AUTHORITY_CHANGE, uint8(COMMAND_AUTHORITY));

	m_bFame = bFame;
	result << GetSocketID() << GetFame();
	SendToRegion(&result);
}


void CUser::SendServerIndex()
{
	Packet result(WIZ_SERVER_INDEX);
	result << uint16(1) << uint16(g_pMain->m_nServerNo);
	Send(&result);
}


void CUser::SkillDataProcess(Packet & pkt)
{
	uint8 opcode = pkt.read<uint8>();
	switch (opcode)
	{
	case SKILL_DATA_SAVE:
		SkillDataSave(pkt);
		break;

	case SKILL_DATA_LOAD:
		SkillDataLoad();
		break;
	}
}


void CUser::SkillDataSave(Packet & pkt)
{
	Packet result(WIZ_SKILLDATA, uint8(SKILL_DATA_SAVE));
	uint16 sCount = pkt.read<uint16>();
	if (sCount == 0 || sCount > 64)
		return;

	result	<< sCount;
	for (int i = 0; i < sCount; i++)
		result << pkt.read<uint32>();

	g_pMain->AddDatabaseRequest(result, this);
}


void CUser::SkillDataLoad()
{
	Packet result(WIZ_SKILLDATA, uint8(SKILL_DATA_LOAD));
	g_pMain->AddDatabaseRequest(result, this);
}


void CUser::UserDataSaveToAgent()
{
	if (!isInGame())
		return;

	Packet result(WIZ_DATASAVE);
	result << GetAccountName() << GetName();
	g_pMain->AddDatabaseRequest(result, this);
}


void CUser::LogOut()
{
	if (m_strUserID.empty()) 
		return; 

	Packet result(AG_USER_LOG_OUT);
	result << GetID() << GetName();
	Send_AIServer(&result);
	UserInOut(INOUT_OUT);
	result.Initialize(WIZ_LOGOUT);
	m_deleted = true;
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::SendMyInfo()
{
		C3DMap* pMap = GetMap();
	CKnights* pKnights = nullptr;

	if (!pMap->IsValidPosition(GetX(), GetZ(), 0.0f))
	{
		short x = 0, z = 0;
		GetStartPosition(x, z); 

		m_curx = (float)x;
		m_curz = (float)z;
	}

	QuestDataRequest();
	ServerNews();
	Packet result(WIZ_MYINFO);

	g_pMain->GetUserRank(this);

	CKingSystem * pData = g_pMain->m_KingSystemArray.GetData(GetNation());
	if (pData != nullptr
		&& STRCASECMP(pData->m_strKingName.c_str(), m_strUserID.c_str()) == 0)
	{
		m_bRank = 1; 
		AchieveMainCount(0, 0, 0, 1);
	}
	else
		m_bRank = 0;

	result.SByte();
	result	<< GetSocketID()
		<< GetName()
		<< GetSPosX() << GetSPosZ() << GetSPosY()
		<< GetNation() 
		<< m_bRace << m_sClass << m_bFace
		<< m_nHair
		<< m_bRank << m_bTitle;

		result << uint8(1) << uint8(0);

		result << GetLevel()
			<< m_sPoints
			<< m_iMaxExp << m_iExp
			<< GetLoyalty() << GetMonthlyLoyalty()
			<< GetClanID() << GetFame();

	if (isInClan())
		pKnights = g_pMain->GetClanPtr(GetClanID());

	if (pKnights == nullptr)
	{
		result	<< uint64(0) << uint16(-1) << uint32(0);
	}
	else 
	{
		CKnights *aKnights = g_pMain->GetClanPtr(pKnights->GetAllianceID());

		if (pKnights->m_sAlliance != 0)
			pKnights->OnLoginAlliance(this);

		else if (isInClan())
			pKnights->OnLogin(this);

		if (aKnights != nullptr && aKnights->isInAlliance())
		{
			result	<< pKnights->GetAllianceID()
			<< pKnights->m_byFlag
			<< pKnights->m_strName
			<< pKnights->m_byGrade << pKnights->m_byRanking
			<< uint16(pKnights->m_sMarkVersion)
			<< pKnights->GetCapeID(aKnights)
			<< pKnights->m_bCapeR << pKnights->m_bCapeG << pKnights->m_bCapeB << uint8(0);
		}
		else
		{
			result	<< pKnights->GetAllianceID()
			<< pKnights->m_byFlag
			<< pKnights->m_strName
			<< pKnights->m_byGrade << pKnights->m_byRanking
			<< uint16(pKnights->m_sMarkVersion)
			<< uint16(pKnights->m_sCape)
			<< pKnights->m_bCapeR << pKnights->m_bCapeG << pKnights->m_bCapeB << uint8(0);
		}
	}

	result	<< uint8(2) << uint8(3) << uint8(4) << uint8(5)
		<< m_iMaxHp << m_sHp
		<< m_iMaxMp << m_sMp
		<< m_sMaxWeight << m_sItemWeight
		<< GetStat(STAT_STR) << uint8(GetStatItemBonus(STAT_STR))
		<< GetStat(STAT_STA) << uint8(GetStatItemBonus(STAT_STA))
		<< GetStat(STAT_DEX) << uint8(GetStatItemBonus(STAT_DEX))
		<< GetStat(STAT_INT) << uint8(GetStatItemBonus(STAT_INT))
		<< GetStat(STAT_CHA) << uint8(GetStatItemBonus(STAT_CHA))
		<< m_sTotalHit << m_sTotalAc
		<< uint8(m_sFireR) << uint8(m_sColdR) << uint8(m_sLightningR)
		<< uint8(m_sMagicR) << uint8(m_sDiseaseR) << uint8(m_sPoisonR)
		<< m_iGold
		<< m_bAuthority
		<< m_bKnightsRank 
		<< m_bPersonalRank;
	
	result.append(m_bstrSkill, 9);

	for (int i = 0; i < INVENTORY_TOTAL; i++)
	{
		_ITEM_DATA *pItem = GetItem(i);

		if(i == BAG1)
			pItem = GetItem(FAIRY);
		else if(i== FAIRY)
			pItem = GetItem(BAG1);

		if((pItem->nExpirationTime - UNIXTIME < 0 && pItem->nExpirationTime != 0) || pItem->sCount < 1) 
		{
			result << uint32(0)	<< uint16(0) << uint16(0) << uint8(0) << uint16(0) << uint32(0) << uint32(0);
			pItem->nNum = 0;
		}
		else 
		{
			result	<< pItem->nNum << pItem->sDuration << pItem->sCount << pItem->bFlag
				<< pItem->sRemainingRentalTime;
			
			if (pItem->isSpecial())
				LoadSpecialItem(result, pItem->SealSerial);
			else
				result << uint32(0);

		result		<< pItem->nExpirationTime;
		}
	}

	m_bIsChicken = CheckExistEvent(50, 1);
	result << m_bAccountStatus
		<< m_bPremiumCount;

	for (int i = 0; i < PREMIUM_TOTAL; i++)
	{
		uint32 TimeRest;
		uint16 TimeShow;
		_PREMIUM_DATA * uPrem = GetPremiumPtr(i);

		if (!uPrem)
			continue;
		if (uPrem->pTime == 0)
			continue;

		TimeRest = uint32(uPrem->pTime - UNIXTIME);

		if (TimeRest >= 1 && TimeRest <= 3600)
			TimeShow = 1;
		else
			TimeShow = TimeRest / 3600;

		result << uPrem->pType
			<< TimeShow;
	}
	
	result << m_bPremiumInUse
		<< uint8(0)
		<< m_iMannerPoint;

	result << CastleMilitary
		<< CastleMilitary		
		<< EslantMilitary		
		<< EslantMilitary		
		<< MoradonMilitary		
		<< uint8(0)				
		<< GetGenieTime();
	
	result << GetRebLevel();
	result << GetRebStatBuff(STAT_STR)	    
		<< GetRebStatBuff(STAT_STA)		
		<< GetRebStatBuff(STAT_DEX)		
		<< GetRebStatBuff(STAT_INT)		
		<< GetRebStatBuff(STAT_CHA)		
		<< uint32(0)					
		<< uint16(0)					
		<< uint16(0)					
		<< GetCoverTitle()				
		<< GetSkillTitle()				
		<< GetReturnStatus()            // R SYMBOL
		<< uint16(0); 					
	    

	SendCompressed(&result);

	g_pMain->AddCharacterName(this);

	SetZoneAbilityChange(GetZoneID());
	Send2AI_UserUpdateInfo(true); 
}

void CUser::LoadSpecialItem(Packet & pkt, uint32 rSealSerial)
{
	_SPECIAL_ITEM * pSpecial = g_pMain->m_SpecialItemArray.GetData(rSealSerial);

	if (pSpecial != nullptr)
	{
		pkt.DByte();

		pkt << pSpecial->SealSerial
			<< pSpecial->sCharID
			<< uint8(pSpecial->sClass)
			<< uint8(pSpecial->bLevel)
			<< uint16(pSpecial->sExpPercent)
			<< uint16(pSpecial->bRaceSatis);
	}
	else
		pkt << uint32(0);
}

void CUser::ServerNews()
{
	DateTime time;
	std::string ServerNews1;
	std::string ServerNews2;
	std::string Welcome;
	
		ServerNews2 = string_format("EuroPvP Server Time : %02d-%02d-%04d  %02d:%02d", time.GetDay(), time.GetMonth(), time.GetYear(), time.GetHour(), time.GetMinute());
		ServerNews1 = string_format("The server security and code is protected By TopraK");
		Welcome = string_format("Hello %s, good games!", GetName().c_str());

	Packet SecurityNotice(WIZ_CHAT, uint8(GENERAL_CHAT));
	SecurityNotice << GetNation() << GetSocketID() << uint8(0) << ServerNews1;
	Send(&SecurityNotice);

	Packet NewsNotice(WIZ_CHAT, uint8(PUBLIC_CHAT));
	NewsNotice << GetNation() << GetSocketID() << uint8(0) << ServerNews2;
	Send(&NewsNotice);

	Packet WelcomeNotice(WIZ_CHAT, uint8(PUBLIC_CHAT));
	WelcomeNotice << GetNation() << GetSocketID() << uint8(0) << Welcome;
	Send(&WelcomeNotice);
}

void CUser::SetMaxHp(int iFlag)
{
	_CLASS_COEFFICIENT* p_TableCoefficient = nullptr;
	p_TableCoefficient = g_pMain->m_CoefficientArray.GetData( m_sClass );
	if( !p_TableCoefficient ) return;

	int temp_sta = getStatTotal(STAT_STA);

	if (GetZoneID() == ZONE_SNOW_BATTLE && iFlag == 0)
		if(GetFame() == COMMAND_CAPTAIN || isKing())
		m_iMaxHp = 300;
		else
		m_iMaxHp = 100;

	else if (GetZoneID() == ZONE_CHAOS_DUNGEON && iFlag == 0)
		m_iMaxHp = 10000 / 10;
	else	
	{
		m_iMaxHp = (short)(((p_TableCoefficient->HP * GetLevel() * GetLevel() * temp_sta ) 
			+ 0.1 * (GetLevel() * temp_sta) + (temp_sta / 5)) + m_sMaxHPAmount + m_sItemMaxHp + 20);

		if (m_iMaxHp > MAX_PLAYER_HP && !isGM()) 
			m_iMaxHp = MAX_PLAYER_HP;

		if (iFlag == 1)
			m_sHp = m_iMaxHp;
		else if (iFlag == 2)
			m_iMaxHp = 100;
	}

	if(m_iMaxHp < m_sHp) {
		m_sHp = m_iMaxHp;
		HpChange( m_sHp );
	}
}


void CUser::SetMaxMp()
{
	_CLASS_COEFFICIENT* p_TableCoefficient = nullptr;
	p_TableCoefficient = g_pMain->m_CoefficientArray.GetData( m_sClass );
	if( !p_TableCoefficient )
		return;

	int temp_intel = 0, temp_sta = 0;
	temp_intel = getStatTotal(STAT_INT) + 30;
	temp_sta = getStatTotal(STAT_STA);

	if( p_TableCoefficient->MP != 0)
	{
		m_iMaxMp = (short)((p_TableCoefficient->MP * GetLevel() * GetLevel() * temp_intel)
			+ (0.1f * GetLevel() * 2 * temp_intel) + (temp_intel / 5) + m_sMaxMPAmount + m_sItemMaxMp + 20);
	}
	else if( p_TableCoefficient->SP != 0)
	{
		m_iMaxMp = (short)((p_TableCoefficient->SP * GetLevel() * GetLevel() * temp_sta )
			+ (0.1f * GetLevel() * temp_sta) + (temp_sta / 5) + m_sMaxMPAmount + m_sItemMaxMp);
	}

	if(m_iMaxMp < m_sMp) {
		m_sMp = m_iMaxMp;
		MSpChange( m_sMp );
	}
}

void CUser::SetMaxSp()
{
	m_iMaxSp = 100;
	m_sSp = m_iMaxSp;
	SpChange(m_sSp);
}


void CUser::SendTime()
{
	Packet result(WIZ_TIME);
	result	<< uint16(g_pMain->m_sYear) << uint16(g_pMain->m_sMonth) << uint16(g_pMain->m_sDate)
		<< uint16(g_pMain->m_sHour) << uint16(g_pMain->m_sMin);
	Send(&result);
}


void CUser::SendWeather()
{
	Packet result(WIZ_WEATHER);
	result << g_pMain->m_byWeather << g_pMain->m_sWeatherAmount;
	Send(&result);
}


void CUser::SetZoneAbilityChange(uint16 sNewZone)
{
	C3DMap * pMap = g_pMain->GetZoneByID(sNewZone);
	_KNIGHTS_SIEGE_WARFARE *pSiegeWar = g_pMain->GetSiegeMasterKnightsPtr(1);
	CKingSystem *pKingSystem = g_pMain->m_KingSystemArray.GetData(GetNation());
	if (pMap == nullptr)
		return;
	if (pSiegeWar != nullptr && pKingSystem != nullptr)
	{
		switch (sNewZone)
		{
		case ZONE_KARUS:
			pMap->SetTariff(pKingSystem->m_nTerritoryTariff);
			break;
		case ZONE_ELMORAD:
			pMap->SetTariff(pKingSystem->m_nTerritoryTariff);
			break;
		case ZONE_MORADON:
			pMap->SetTariff((uint8)pSiegeWar->sMoradonTariff);
			break;
		case ZONE_MORADON2:
			pMap->SetTariff((uint8)pSiegeWar->sMoradonTariff);
			break;
		case ZONE_MORADON3:
			pMap->SetTariff((uint8)pSiegeWar->sMoradonTariff);
			break;
		case ZONE_MORADON4:
			pMap->SetTariff((uint8)pSiegeWar->sMoradonTariff);
			break;
		case ZONE_MORADON5:
			pMap->SetTariff((uint8)pSiegeWar->sMoradonTariff);
			break;
		case ZONE_DELOS:
			pMap->SetTariff((uint8)pSiegeWar->sDellosTariff);
			break;
		default:
			break;
		}
	}
	Packet result(WIZ_ZONEABILITY, uint8(1));

	result	<< pMap->canTradeWithOtherNation()
		<< pMap->GetZoneType()
		<< pMap->canTalkToOtherNation()
		<< uint16(pMap->GetTariff());

	Send(&result);

	if (!isGM())
		PlayerRankingProcess(sNewZone,false);

	g_pMain->KillNpc(GetSocketID());

	if (sNewZone == ZONE_BIFROST || sNewZone == ZONE_BATTLE4  || sNewZone ==  ZONE_RONARK_LAND)
		g_pMain->SendEventRemainingTime(false, this, (uint8)sNewZone);

	m_RHitRepeatList.clear();
	m_CoolDownList.clear();
	m_MagicTypeCooldownList.clear();
}


void CUser::SendPremiumInfo()
{
	Packet result (WIZ_PREMIUM, uint8(1));
	result << m_bPremiumCount;

	for (int i = 0; i < PREMIUM_TOTAL; i++)
	{
		uint32 TimeRest;
		uint16 TimeShow;
		_PREMIUM_DATA * uPrem = GetPremiumPtr(i);

		TimeRest = uint32(uPrem->pTime - UNIXTIME);

		if (TimeRest >= 1 && TimeRest <= 3600)
			TimeShow = 1;
		else
			TimeShow = TimeRest / 3600;

		result << uPrem->pType
			<< TimeShow;
	}

	result << m_bPremiumInUse
		<< uint32(0);
	Send(&result);
}

void CUser::RequestUserIn(Packet & pkt)
{
	Packet result(WIZ_REQ_USERIN);
	short user_count = pkt.read<uint16>(), online_count = 0;
	if (user_count > 1000)
		user_count = 1000;

	result << uint16(0);

	for (int i = 0; i < user_count; i++)
	{
		CUser *pUser = g_pMain->GetUserPtr(pkt.read<uint16>());
		if (pUser == nullptr || !pUser->isInGame())
			continue;

		if (m_bEventRoom > 0 && m_bEventRoom != GetEventRoom())
			continue;

		result << uint8(0) << pUser->GetSocketID();
		pUser->GetUserInfo(result);

		online_count++;
	}
	result.put(0, online_count);
	SendCompressed(&result);
}


void CUser::RequestNpcIn(Packet & pkt)
{
	if (g_pMain->m_bPointCheckFlag == false)
		return;

	Packet result(WIZ_REQ_NPCIN);
	uint16 npc_count = pkt.read<uint16>();
	if (npc_count > 1000)
		npc_count = 1000;

	result << uint16(0);
	CKnights *pKnights = g_pMain->GetClanPtr(m_bKnights);
	_KNIGHTS_SIEGE_WARFARE *pSiegeWars = g_pMain->GetSiegeMasterKnightsPtr(1);
	for (int i = 0; i < npc_count; i++)
	{
		  uint16 nid = pkt.read<uint16>();
		  if (nid < 0 || nid > INVALID_BAND)
			  continue;

		CNpc *pNpc = g_pMain->GetNpcPtr(nid);
		if (pNpc == nullptr || pNpc->isDead() || pNpc->GetZoneID() != GetZoneID() || !isInRange(pNpc, RANGE_50M*3))
			continue;

		if (pNpc->m_sSid == 541 && pNpc->GetType() == NPC_DESTROYED_ARTIFACT && pNpc->m_bZone == ZONE_DELOS)
		{
			if ( pKnights != nullptr && pSiegeWars != nullptr)
			{
				if (pSiegeWars->sMasterKnights == pKnights->m_sAlliance || pSiegeWars->sMasterKnights == pKnights->m_sIndex)
					pNpc->m_bNation = 3;
				else
					pNpc->m_bNation = 0;
			}
		}

		result << pNpc->GetID();
		pNpc->GetNpcInfo(result);
	}

	result.put(0, npc_count);
	SendCompressed(&result);
}


void CUser::SetSlotItemValue()
{
	_ITEM_TABLE* pTable = nullptr;
	int item_hit = 0, item_ac = 0;

	m_sItemMaxHp = m_sItemMaxMp = 0;
	m_sItemAc = 0; 
	m_sItemWeight = m_sMaxWeightBonus = 0;	
	m_sItemHitrate = m_sItemEvasionrate = 100; 

	memset(m_sStatItemBonuses, 0, sizeof(uint16) * STAT_COUNT);
	m_sFireR = m_sColdR = m_sLightningR = m_sMagicR = m_sDiseaseR = m_sPoisonR = 0;
	m_sDaggerR = m_sJamadarR = m_sSwordR = m_sAxeR = m_sMaceR = m_sSpearR = m_sBowR = 0;

	m_byAPBonusAmount = 0;
	memset(&m_byAPClassBonusAmount, 0, sizeof(m_byAPClassBonusAmount));
	memset(&m_byAcClassBonusAmount, 0, sizeof(m_byAcClassBonusAmount));

	m_bItemExpGainAmount = m_bItemNPBonus = m_bItemNoahGainAmount = 0;

	Guard lock(m_equippedItemBonusLock);
	m_equippedItemBonuses.clear();

	map<uint16, uint32> setItems;

	for (int i = 0; i < INVENTORY_TOTAL; i++)
	{
		_ITEM_DATA * pItem = nullptr;
		pTable = GetItemPrototype(i, pItem);
		if (pTable == nullptr)
			continue;

		if (i == INVENTORY_COSP + COSP_BAG1
			|| i == INVENTORY_COSP + COSP_BAG2)
		{
			m_sMaxWeightBonus += pTable->m_sDuration;
		}
		else
		{	
			if (pTable->GetKind() == 255)
				m_sItemWeight += pTable->m_sWeight;
			else
				m_sItemWeight += pTable->m_sWeight * pItem->sCount;
		}

		if ((i >= SLOT_MAX && i < INVENTORY_COSP)
				|| (isWeaponsDisabled() 
				&& (i == RIGHTHAND || i == LEFTHAND) 
				&& !pTable->isShield())
				|| i >= INVENTORY_MBAG
				|| pItem->isDuplicate())
				continue;

		item_ac = pTable->m_sAc;
		if (pItem->sDuration == 0) 
			item_ac /= 10;

		m_sItemMaxHp += pTable->m_MaxHpB;
		m_sItemMaxMp += pTable->m_MaxMpB;
		m_sItemAc += item_ac;
		m_sStatItemBonuses[STAT_STR] += pTable->m_sStrB;
		m_sStatItemBonuses[STAT_STA] += pTable->m_sStaB;
		m_sStatItemBonuses[STAT_DEX] += pTable->m_sDexB;
		m_sStatItemBonuses[STAT_INT] += pTable->m_sIntelB;
		m_sStatItemBonuses[STAT_CHA] += pTable->m_sChaB;
		m_sItemHitrate += pTable->m_sHitrate;
		m_sItemEvasionrate += pTable->m_sEvarate;

		m_sFireR += pTable->m_bFireR;
		m_sColdR += pTable->m_bColdR;
		m_sLightningR += pTable->m_bLightningR;
		m_sMagicR += pTable->m_bMagicR;
		m_sDiseaseR += pTable->m_bCurseR;
		m_sPoisonR += pTable->m_bPoisonR;

		m_sDaggerR += pTable->m_sDaggerAc;
		m_sJamadarR += pTable->m_sJamadarAc;
		m_sSwordR += pTable->m_sSwordAc;
		m_sAxeR += pTable->m_sAxeAc;
		m_sMaceR += pTable->m_sMaceAc;
		m_sSpearR += pTable->m_sSpearAc;
		m_sBowR += pTable->m_sBowAc;

		ItemBonusMap bonusMap;
		if (pTable->m_bFireDamage)
			bonusMap.insert(std::make_pair(ITEM_TYPE_FIRE, pTable->m_bFireDamage));

		if (pTable->m_bIceDamage)
			bonusMap.insert(std::make_pair(ITEM_TYPE_COLD, pTable->m_bIceDamage));

		if (pTable->m_bLightningDamage)
			bonusMap.insert(std::make_pair(ITEM_TYPE_LIGHTNING, pTable->m_bLightningDamage));

		if (pTable->m_bPoisonDamage)
			bonusMap.insert(std::make_pair(ITEM_TYPE_POISON, pTable->m_bPoisonDamage));

		if (pTable->m_bHPDrain)
			bonusMap.insert(std::make_pair(ITEM_TYPE_HP_DRAIN, pTable->m_bHPDrain));

		if (pTable->m_bMPDamage)
			bonusMap.insert(std::make_pair(ITEM_TYPE_MP_DAMAGE, pTable->m_bMPDamage));

		if (pTable->m_bMPDrain)
			bonusMap.insert(std::make_pair(ITEM_TYPE_MP_DRAIN, pTable->m_bMPDrain));

		if (pTable->m_bMirrorDamage)
			bonusMap.insert(std::make_pair(ITEM_TYPE_MIRROR_DAMAGE, pTable->m_bMirrorDamage));

		if (!bonusMap.empty())
			m_equippedItemBonuses[i] = bonusMap;

		if (pTable->GetKind() == ITEM_KIND_COSPRE)
		{
			_SET_ITEM * pSetItem = g_pMain->m_SetItemArray.GetData(pTable->m_iNum);
			if (pSetItem != nullptr)
				ApplySetItemBonuses(pSetItem);
		}

		if (pTable->m_bRace < 100)
			continue;

		auto itr = setItems.find(pTable->m_bRace);

		if (itr == setItems.end())
		{
			setItems.insert(make_pair(pTable->m_bRace, pTable->m_bRace * 10000));
			itr = setItems.find(pTable->m_bRace);
		}

		switch (pTable->m_bSlot)
		{
		case ItemSlotHelmet:
			itr->second += 2;
			break;
		case ItemSlotPauldron:
			itr->second += 16;
			break;
		case ItemSlotPads:
			itr->second += 512;
			break;
		case ItemSlotGloves:
			itr->second += 2048;
			break;
		case ItemSlotBoots:
			itr->second += 4096;
			break;
		}
	}

	foreach (itr, setItems)
	{
		_SET_ITEM * pItem = g_pMain->m_SetItemArray.GetData(itr->second);
		if (pItem == nullptr)
			continue;

		ApplySetItemBonuses(pItem);
	}

	if (m_sAddArmourAc > 0)
		m_sItemAc += m_sAddArmourAc;
	else
		m_sItemAc = m_sItemAc * m_bPctArmourAc / 100;

	for (int i = 0; i < INVENTORY_TOTAL; i++)
	{
		_ITEM_DATA *pItem = GetItem(i);
		
		if(i == BAG1)
			pItem = GetItem(FAIRY);
		else if(i== FAIRY)
			pItem = GetItem(BAG1);

		if((pItem->nExpirationTime - UNIXTIME < 0 && pItem->nExpirationTime != 0) || pItem->sCount < 1) 
		{
			RobItem(i);
		}
	}
}

void CUser::ApplySetItemBonuses(_SET_ITEM * pItem)
{
	m_sItemAc += pItem->ACBonus;
	m_sItemMaxHp += pItem->HPBonus;
	m_sItemMaxMp += pItem->MPBonus;

	m_sStatItemBonuses[STAT_STR] += pItem->StrengthBonus;
	m_sStatItemBonuses[STAT_STA] += pItem->StaminaBonus;
	m_sStatItemBonuses[STAT_DEX] += pItem->DexterityBonus;
	m_sStatItemBonuses[STAT_INT] += pItem->IntelBonus;
	m_sStatItemBonuses[STAT_CHA] += pItem->CharismaBonus;

	m_sFireR += pItem->FlameResistance;
	m_sColdR += pItem->GlacierResistance;
	m_sLightningR += pItem->LightningResistance;
	m_sMagicR += pItem->MagicResistance;
	m_sDiseaseR += pItem->CurseResistance;
	m_sPoisonR += pItem->PoisonResistance;

	m_bItemExpGainAmount += pItem->XPBonusPercent;
	m_bItemNoahGainAmount += pItem->CoinBonusPercent;
	m_bItemNPBonus += pItem->NPBonus;

	m_sMaxWeightBonus += pItem->MaxWeightBonus;

	m_byAPBonusAmount += pItem->APBonusPercent; 
	if (pItem->APBonusClassType >= 1 && pItem->APBonusClassType <= 4)
		m_byAPClassBonusAmount[pItem->APBonusClassType - 1] += pItem->APBonusClassPercent;

	if (pItem->ACBonusClassType >= 1 && pItem->ACBonusClassType <= 4)
		m_byAcClassBonusAmount[pItem->ACBonusClassType - 1] += pItem->ACBonusClassPercent;
}

void CUser::RecvUserExp(Packet & pkt)
{
	CNpc * pNpc;
	_PARTY_GROUP * pParty;
	uint16 sNpcID;
	int32 iDamage, iTotalDamage, iNpcExp, iNpcLoyalty;
	uint32 nFinalExp, nFinalLoyalty;
	double TempValue = 0;

	pkt >> sNpcID >> iDamage >> iTotalDamage >> iNpcExp >> iNpcLoyalty;

	pNpc = g_pMain->GetNpcPtr(sNpcID);
	if (pNpc == nullptr
		|| !isInRangeSlow(pNpc, RANGE_50M)
		|| (iNpcExp <= 0 && iNpcLoyalty <= 0))
		return;

	if (iNpcExp > 0)
	{
		TempValue = iNpcExp * ((double)iDamage / (double)iTotalDamage);
		nFinalExp = (int) TempValue;
		if (TempValue > nFinalExp)
			nFinalExp++;
	}

	if (iNpcLoyalty > 0)
	{
		TempValue = iNpcLoyalty * ((double)iDamage / (double)iTotalDamage);
		nFinalLoyalty = (int) TempValue;
		if (TempValue > nFinalLoyalty)
			nFinalLoyalty++;
	}

	if (!isInParty()
		|| (pParty = g_pMain->GetPartyPtr(GetPartyID())) == nullptr)
	{
		if (isDead())
			return;

		float fModifier = pNpc->GetRewardModifier(GetLevel());

		if (iNpcExp > 0)
		{
			TempValue = nFinalExp * fModifier;
			nFinalExp = (int) TempValue;
			if (TempValue > nFinalExp)
				nFinalExp++;

			ExpChange(nFinalExp);
			ExpEvent(nFinalExp);
		}

		if (iNpcLoyalty > 0)
		{
			bool UseModifier = false;

			if (UseModifier)
			{
				TempValue = nFinalLoyalty * fModifier;
				nFinalLoyalty = (int) TempValue;
				if (TempValue > nFinalLoyalty)
					nFinalLoyalty++;
			}

			SendLoyaltyChange(nFinalLoyalty);
		}

		return;
	}

	std::vector<CUser *> partyUsers;
	uint32 nTotalLevel = 0;
	for (int i = 0; i < MAX_PARTY_USERS; i++)
	{
		CUser * pUser = g_pMain->GetUserPtr(pParty->uid[i]);
		if (pUser == nullptr)
			continue;

		partyUsers.push_back(pUser);
		nTotalLevel += pUser->GetLevel();
	}

	const float fPartyModifierXP = 0.3f;
	const float fPartyModifierNP = 0.2f;

	uint32 nPartyMembers = (uint32) partyUsers.size();

	float fModifier = pNpc->GetPartyRewardModifier(nTotalLevel, nPartyMembers);

	if (iNpcExp > 0)
	{
		TempValue = nFinalExp * fModifier;
		nFinalExp = (int) TempValue;
		if (TempValue > nFinalExp)
			nFinalExp++;
	}

	if (iNpcLoyalty > 0)
	{
		TempValue = nFinalLoyalty * fModifier;
		nFinalLoyalty = (int) TempValue;
		if (TempValue > nFinalLoyalty)
			nFinalLoyalty++;
	}

	foreach (itr, partyUsers)
	{
		CUser * pUser = (*itr);

		if (pUser == nullptr)
			continue;

		if (pUser->isDead()
			|| !pUser->isInRange(pNpc, RANGE_50M))
			continue;

		if (iNpcExp > 0)
		{
			TempValue = (nFinalExp * (1 + fPartyModifierXP * (nPartyMembers - 1))) * (double)pUser->GetLevel() / (double)nTotalLevel;
			int iExp = (int) TempValue;
			if (TempValue > iExp)
				iExp++;

			pUser->ExpChange(iExp);
		}

		if (iNpcLoyalty > 0)
		{
			TempValue = (nFinalLoyalty * (1 + fPartyModifierNP * (nPartyMembers - 1))) * (double)pUser->GetLevel() / (double)nTotalLevel;
			int iLoyalty = (int) TempValue;
			if (TempValue > iLoyalty)
				iLoyalty++;

			pUser->SendLoyaltyChange(iLoyalty);
		}
	}
}

void CUser::ExpChange(int64 iExp, bool bIsBonusReward)
{	
	if (iExp < 0)
		return;

	if ((GetLevel() < 6 && iExp < 0)
			|| (GetMap()->isWarZone() && iExp < 0))
			return;

	ASSERT(m_iExp >= 0);

	if (iExp > 0)
	{
		if (!bIsBonusReward)
		{
			iExp = iExp * (m_sExpGainAmount + m_bItemExpGainAmount) / 100;
			iExp = iExp * (100 + g_pMain->m_byExpEventAmount) / 100;
			iExp = iExp * (m_sExpGainAmount+m_FlashExpBonus) /100;

			if (GetPremiumProperty(PremiumExpPercent) > 0 && !isDead())
				iExp = iExp * (100 + GetPremiumProperty(PremiumExpPercent)) / 100;
		}
	}

	iExp += iExp * c_AchieveXP /100;
	
	bool bLevel = true;
	if (iExp < 0 
		&& (m_iExp + iExp) < 0)
		bLevel = false;
	else
		m_iExp += iExp;

	if (!bLevel)
	{
		m_bLevel--;

		int64 diffXP = m_iExp + iExp;

		m_iExp = g_pMain->GetExpByLevel(GetLevel());

		LevelChange(GetLevel(), false);
		ExpChange(diffXP);
		return;
	}
	else if (m_iExp >= m_iMaxExp)
	{
		if (GetLevel() < MAX_LEVEL)
		{
			m_iExp -= m_iMaxExp;
			LevelChange(++m_bLevel);
			return;
		}
		m_iExp = m_iMaxExp;
	}

	Packet result(WIZ_EXP_CHANGE);
	result << uint8(0) << m_iExp;
	Send(&result);

	if (iExp < 0)
		m_iLostExp = -iExp;
}


uint16 CUser::GetPremiumProperty(PremiumPropertyOpCodes type)
{
	if (m_bPremiumInUse <= 0)
		return 0;

	_PREMIUM_ITEM * pPremiumItem = g_pMain->m_PremiumItemArray.GetData(m_bPremiumInUse);
	if (pPremiumItem == nullptr)
		return 0;

	switch (type)
	{
	case PremiumExpRestorePercent:
		return pPremiumItem->ExpRestorePercent;
	case PremiumNoahPercent:
		return pPremiumItem->NoahPercent;
	case PremiumDropPercent:
		return pPremiumItem->DropPercent;
	case PremiumBonusLoyalty:
		return pPremiumItem->BonusLoyalty;
	case PremiumRepairDiscountPercent:
		return pPremiumItem->RepairDiscountPercent;
	case PremiumItemSellPercent:
		return pPremiumItem->ItemSellPercent;
	case PremiumExpPercent:
		{
			foreach_stlmap (itr, g_pMain->m_PremiumItemExpArray)
			{
				_PREMIUM_ITEM_EXP *pPremiumItemExp = g_pMain->m_PremiumItemExpArray.GetData(itr->first);

				if (pPremiumItemExp == nullptr)
					continue;

				if (m_bPremiumInUse == pPremiumItemExp->Type && GetLevel() >= pPremiumItemExp->MinLevel && GetLevel() <= pPremiumItemExp->MaxLevel)
					return pPremiumItemExp->sPercent;
			}
		}
	}

	return 0;
}

void CUser::LevelChange(uint8 level, bool bLevelUp)
{
	if (level < 1 || level > MAX_LEVEL)
		return;

	if (bLevelUp && level > GetLevel() + 1)
	{
		int16 nStatTotal = 300 + (level - 1) * 3;
		uint8 nSkillTotal = (level - 9) * 2;

		if (level > 60)
			nStatTotal += 2 * (level - 60);

		m_sPoints += nStatTotal - GetStatTotal();
		m_bstrSkill[SkillPointFree] += nSkillTotal - GetTotalSkillPoints();
		m_bLevel = level;
	}
	else if (bLevelUp)
	{
		int levelsAfter60 = (level > 60 ? level - 60 : 0);
		if ((m_sPoints + GetStatTotal()) < int32(297 + (3 * level) + (2 * levelsAfter60)))
			m_sPoints += (levelsAfter60 == 0 ? 3 : 5);

		if (level >= 10 && GetTotalSkillPoints() < 2 * (level - 9))
			m_bstrSkill[SkillPointFree] += 2;
	}
	
	m_iMaxExp = g_pMain->GetExpByLevel(level);
	SetUserAbility();

	m_sMp = m_iMaxMp;
	HpChange(GetMaxHealth()); 

	Send2AI_UserUpdateInfo();

	Packet result(WIZ_LEVEL_CHANGE);
	result	<< GetSocketID()
		<< GetLevel() << m_sPoints << m_bstrSkill[SkillPointFree]
		<< m_iMaxExp << m_iExp
		<< m_iMaxHp << m_sHp 
		<< m_iMaxMp << m_sMp
		<< m_sMaxWeight << m_sItemWeight;

	AchieveMainCount(0, 0, 0, 3);

	g_pMain->Send_Region(&result, GetMap(), GetRegionX(), GetRegionZ());
	if (isInParty())
	{
		result.Initialize(WIZ_PARTY);
		result << uint8(PARTY_LEVELCHANGE) << GetSocketID() << GetLevel();
		g_pMain->Send_PartyMember(GetPartyID(), &result);

		if (m_bIsChicken)
			GrantChickenManner();
	}

	if (GetLevel() < GetMap()->GetMinLevelReq() || GetLevel() > GetMap()->GetMaxLevelReq())
		KickOutZoneUser();
}


void CUser::PointChange(Packet & pkt)
{
	uint8 type = pkt.read<uint8>();
	StatType statType = (StatType)(type - 1);

	if (statType < STAT_STR || statType >= STAT_COUNT 
		|| m_sPoints < 1
		|| GetStat(statType) >= STAT_MAX) 
		return;

	Packet result(WIZ_POINT_CHANGE, type);

	m_sPoints--;
	result << uint16(++m_bStats[statType]);
	SetUserAbility();
	result << m_iMaxHp << m_iMaxMp << m_sTotalHit << m_sMaxWeight;
	Send(&result);
	SendItemMove(1);
}


void CUser::HpChange(int amount, Unit *pAttacker /*= nullptr*/, bool bSendToAI /*= true*/) 
{
	Packet result(WIZ_HP_CHANGE);
	uint16 tid = (pAttacker != nullptr ? pAttacker->GetID() : -1);
	int16 oldHP = m_sHp;
	int originalAmount = amount;
	int mirrorDamage = 0;

	if (pAttacker && pAttacker->GetZoneID() != GetZoneID())
		return; 

	if (amount < -MAX_DAMAGE)
		amount = -MAX_DAMAGE;
	else if (amount > MAX_DAMAGE)
		amount = MAX_DAMAGE;

	if (amount < 0)
	{
		if (isGM())
			return;

		RemoveStealth();

		if (m_bMirrorDamage && isInParty() && GetZoneID() != ZONE_CHAOS_DUNGEON)
		{
			_PARTY_GROUP *pParty = nullptr;
			CUser *pUser = nullptr;
			mirrorDamage = (m_byMirrorAmount * amount) / 100;
			amount -= mirrorDamage;
			pParty = g_pMain->GetPartyPtr(GetPartyID());
			if (pParty != nullptr)
			{
				mirrorDamage = mirrorDamage / (GetPartyMemberAmount(pParty) - 1);
				for (int i = 0; i < MAX_PARTY_USERS; i++)
				{
					pUser = g_pMain->GetUserPtr(pParty->uid[i]);
					if(pUser == nullptr || pUser == this)
						continue;

					pUser->HpChange(mirrorDamage);
				}
			}
		}

		if (m_bManaAbsorb > 0 && GetZoneID() != ZONE_CHAOS_DUNGEON)
		{
			int toBeAbsorbed = 0;
			toBeAbsorbed = (originalAmount*m_bManaAbsorb) / 100;
			amount -= toBeAbsorbed;

			if (m_bManaAbsorb == 15)
				toBeAbsorbed *= 4;

			MSpChange(toBeAbsorbed);
		}

		if (isMastered() && GetZoneID() != ZONE_CHAOS_DUNGEON)
		{
			if (CheckSkillPoint(SkillPointMaster, 10, MAX_LEVEL))
				amount = (85 * amount) / 100;
			else if (CheckSkillPoint(SkillPointMaster, 5, 9))
				amount = (90 * amount) / 100;
		}
	}
	else if (m_bIsUndead)
	{
		amount = -amount;
		originalAmount = amount;
	}

	if (amount < 0 && -amount >= m_sHp)
		m_sHp = 0;
	else if (amount >= 0 && m_sHp + amount > m_iMaxHp)
		m_sHp = m_iMaxHp;
	else
		m_sHp += amount;

	result << m_iMaxHp << m_sHp << tid;

	if (GetHealth() > 0
		&& isMastered()
		&& !isMage() && GetZoneID() != ZONE_CHAOS_DUNGEON)
	{
		const uint16 hp30Percent = (30 * GetMaxHealth()) / 100;
		if ((oldHP >= hp30Percent && m_sHp < hp30Percent)
			|| (m_sHp > hp30Percent))
		{
			SetUserAbility();

			if (m_sHp < hp30Percent)
				ShowEffect(106800);
		}
	}

	Send(&result);

	if (bSendToAI)
	{
		result.Initialize(AG_USER_SET_HP);
		result << GetSocketID() << m_sHp << tid;
		Send_AIServer(&result);
	}

	if (isInParty() && GetZoneID() != ZONE_CHAOS_DUNGEON)
		SendPartyHPUpdate();

	if (pAttacker != nullptr
		&& pAttacker->isPlayer())
		TO_USER(pAttacker)->SendTargetHP(0, GetID(), originalAmount);

	if (m_sHp == 0)
		OnDeath(pAttacker);
}


void CUser::MSpChange(int amount)
{
	Packet result(WIZ_MSP_CHANGE);
	int16 oldMP = m_sMp;

	if (isGM() && amount < 0)
		return;

	m_sMp += amount;
	if (m_sMp < 0)
		m_sMp = 0;
	else if (m_sMp > m_iMaxMp)
		m_sMp = m_iMaxMp;

	if (isMasteredMage())
	{
		const uint16 mp30Percent = (30 * GetMaxMana()) / 100;
		if (oldMP >= mp30Percent
			&& GetMana() < mp30Percent)
			ShowEffect(106800);
	}

	result << m_iMaxMp << m_sMp;
	Send(&result);

	if (isInParty())
		SendPartyHPUpdate();
}


void CUser::SendPartyHPUpdate()
{
	Packet result(WIZ_PARTY);
	result	<< uint8(PARTY_HPCHANGE)
		<< GetSocketID()
		<< m_iMaxHp << m_sHp
		<< m_iMaxMp << m_sMp;
	g_pMain->Send_PartyMember(GetPartyID(), &result);
}


void CUser::ShowEffect(uint32 nSkillID)
{
	Packet result(WIZ_EFFECT);
	result << GetID() << nSkillID;
	SendToRegion(&result);
}


void CUser::ShowNpcEffect(uint32 nEffectID, bool bSendToRegion)
{
	Packet result(WIZ_OBJECT_EVENT, uint8(OBJECT_NPC));
	result << uint8(3) << m_sEventNid << nEffectID;
	if (bSendToRegion)
		SendToRegion(&result);
	else
		Send(&result);
}


void CUser::Send2AI_UserUpdateInfo(bool initialInfo /*= false*/)
{
	Packet result(initialInfo ? AG_USER_INFO : AG_USER_UPDATE);
	GetUserInfoForAI(result);
	Send_AIServer(&result);
}


void CUser::SetUserAbility(bool bSendPacket /*= true*/)
{
	bool bHaveBow = false;
	_CLASS_COEFFICIENT* p_TableCoefficient = g_pMain->m_CoefficientArray.GetData(GetClass());
	uint16 sItemDamage = 0;
	if (p_TableCoefficient == nullptr)
		return;

	float hitcoefficient = 0.0f;

	if (!isWeaponsDisabled())
	{
		_ITEM_TABLE * pRightHand = GetItemPrototype(RIGHTHAND);
		_ITEM_DATA * pRightData = GetItem(RIGHTHAND);
		if (pRightHand != nullptr)
		{
			switch (pRightHand->m_bKind/10)
			{
			case WEAPON_DAGGER:
				hitcoefficient = p_TableCoefficient->ShortSword;
				break;
			case WEAPON_JAMADAR:
				hitcoefficient = p_TableCoefficient->ShortSword;
				break;
			case WEAPON_SWORD:
				hitcoefficient = p_TableCoefficient->Sword;
				break;
			case WEAPON_AXE:
				hitcoefficient = p_TableCoefficient->Axe;
				break;
			case WEAPON_MACE:
			case WEAPON_MACE2:
				hitcoefficient = p_TableCoefficient->Club;
				break;
			case WEAPON_SPEAR:
				hitcoefficient = p_TableCoefficient->Spear;
				break;
			case WEAPON_BOW:
			case WEAPON_LONGBOW:
			case WEAPON_LAUNCHER:
				hitcoefficient = p_TableCoefficient->Bow;
				bHaveBow = true;
				break;
			case WEAPON_STAFF:
				hitcoefficient = p_TableCoefficient->Staff;
				break;
			}

			if (pRightData->sDuration == 0)
				sItemDamage += (pRightHand->m_sDamage + m_bAddWeaponDamage)/2;
			else
				sItemDamage += pRightHand->m_sDamage + m_bAddWeaponDamage;
		}

		_ITEM_TABLE *pLeftHand = GetItemPrototype(LEFTHAND);
		_ITEM_DATA * pLeftData = GetItem(LEFTHAND);
		if (pLeftHand != nullptr)
		{
			if (pLeftHand->isBow())
			{
				hitcoefficient = p_TableCoefficient->Bow;
				bHaveBow = true;
				if (pLeftData->sDuration == 0)
					sItemDamage = (pLeftHand->m_sDamage + m_bAddWeaponDamage)/2;
				else
					sItemDamage = pLeftHand->m_sDamage + m_bAddWeaponDamage;
			}
			else
			{
				if (pLeftData->sDuration == 0)
					sItemDamage += ((pLeftHand->m_sDamage + m_bAddWeaponDamage) / 2) /2;
				else
					sItemDamage += (pLeftHand->m_sDamage + m_bAddWeaponDamage) / 2;
			}
		}
	}

	if (m_sACAmount < 0)
		m_sACAmount = 0;

	m_sTotalHit = 0;

	if (sItemDamage < 3)
		sItemDamage = 3;

	SetSlotItemValue();

	int temp_str = GetStat(STAT_STR), temp_dex = getStatTotal(STAT_DEX), temp_cha = getStatTotal(STAT_CHA);

	uint32 baseAP = 0, ap_stat = 0, additionalAP = 3;
	if (temp_str > 150)
		baseAP = temp_str - 150;

	if (temp_str == 160)
		baseAP--;

	temp_str += GetStatBonusTotal(STAT_STR);

	m_sMaxWeight = ((((GetStatWithItemBonus(STAT_STR) + GetLevel()) * 50) + m_sMaxWeightBonus)  * (m_bMaxWeightAmount <= 0 ? 1 :  m_bMaxWeightAmount / 100))/2;

	if (isRogue()) 
		ap_stat = temp_dex;
	else if (isMage())
		ap_stat = temp_cha;
	else
	{
		ap_stat = temp_str;
		additionalAP += baseAP;
	}
	if (isWarrior() || isPriest()|| isKurPor())
	{
		m_sTotalHit = (uint16)((0.010f * sItemDamage * (ap_stat + 40)) + (hitcoefficient * sItemDamage * GetLevel() * ap_stat));
		m_sTotalHit = (m_sTotalHit + additionalAP) * (100 + m_byAPBonusAmount) / 100;
 	}
	if(isRogue())
	{
		m_sTotalHit = (uint16)((0.007f * sItemDamage * (ap_stat + 40)) + (hitcoefficient * sItemDamage * GetLevel() * ap_stat));
		m_sTotalHit = (m_sTotalHit + additionalAP) * (100 + m_byAPBonusAmount) / 100;
	}
	else if(isMage())
	{
		m_sTotalHit = (uint16)((0.005f * sItemDamage * (ap_stat + 40)) + (hitcoefficient * sItemDamage * GetLevel() * ap_stat));
		m_sTotalHit = (m_sTotalHit + additionalAP) * (100 + m_byAPBonusAmount) / 100;
	}
	m_sTotalHit = (m_sTotalHit + additionalAP) * (100 + m_byAPBonusAmount) / 100;

	m_sTotalAc = (short)(p_TableCoefficient->AC * (GetLevel() + m_sItemAc));
	if (m_sACPercent <= 0)
		m_sACPercent = 100;
	m_sTotalAc = m_sTotalAc * m_sACPercent / 100;

	m_fTotalHitrate = ((1 + p_TableCoefficient->Hitrate * GetLevel() *  temp_dex ) * m_sItemHitrate/100 ) * (m_bHitRateAmount/100);

	m_fTotalEvasionrate = ((1 + p_TableCoefficient->Evasionrate * GetLevel() * temp_dex ) * m_sItemEvasionrate/100) * (m_sAvoidRateAmount/100);

	SetMaxHp();
	SetMaxMp();
	if (isKurPor() || isNoviceKurPor() || isMasteredKurPor())
	{
		SetMaxSp();
	}

	uint8 bDefenseBonus = 0, bResistanceBonus = 0;
	m_bResistanceBonus = 0;

	if (isWarrior())
	{
		if (CheckSkillPoint(PRO_SKILL2, 5, 14))
			bDefenseBonus = 20;
		else if (CheckSkillPoint(PRO_SKILL2, 15, 34))
			bDefenseBonus = 30;
		else if (CheckSkillPoint(PRO_SKILL2, 35, 54))
			bDefenseBonus = 40;
		else if (CheckSkillPoint(PRO_SKILL2, 55, 69))
			bDefenseBonus = 50;
		else if (CheckSkillPoint(PRO_SKILL2, 70, MAX_LEVEL))
		{
			if (CheckExistEvent(51, 2))
				bDefenseBonus = 60;
			else
				bDefenseBonus = 50;
		}

		if (CheckSkillPoint(PRO_SKILL2, 10, 19))
			bResistanceBonus = 30;
		else if (CheckSkillPoint(PRO_SKILL2, 20, 39))
			bResistanceBonus = 60;
		else if (CheckSkillPoint(PRO_SKILL2, 40, MAX_LEVEL))
			bResistanceBonus = 90;

		_ITEM_TABLE *pLeftHand = GetItemPrototype(LEFTHAND);
		if (pLeftHand == nullptr || !pLeftHand->isShield())
		{
			bResistanceBonus /= 2;
			bDefenseBonus /= 2;
		}

		m_bResistanceBonus = bResistanceBonus;
		m_sTotalAc += bDefenseBonus * m_sTotalAc / 100;
	}

	if (CheckClass(6, 12))
	{
		if (m_sHp < 30 * m_iMaxHp / 100)
		{
			m_sTotalAc += 20 * m_sTotalAc / 100;
		}
	}
	else if (isKurPor())
	{
		if (CheckSkillPoint(PRO_SKILL1, 45, 83))
			m_PassiveRush = true;
		if (CheckSkillPoint(PRO_SKILL2, 5, 14))
			bDefenseBonus = 20;
		else if (CheckSkillPoint(PRO_SKILL2, 15, 34))
			bDefenseBonus = 30;
		else if (CheckSkillPoint(PRO_SKILL2, 35, 54))
			bDefenseBonus = 40;
		else if (CheckSkillPoint(PRO_SKILL2, 55, 69))
			bDefenseBonus = 50;
		else if (CheckSkillPoint(PRO_SKILL2, 70, 83))
		{
			if (CheckExistEvent(51, 2))
				bDefenseBonus = 60;
			else
				bDefenseBonus = 50;
		}
		if (CheckSkillPoint(PRO_SKILL3, 45, 69))
			m_bSkillActive = true;
		else if(CheckSkillPoint(PRO_SKILL3, 70, 83))
		{
			m_bSkillActive = false;
			m_bSkillActive2 = true;
		}

		if (CheckSkillPoint(PRO_SKILL2, 10, 19))
			bResistanceBonus = 30;
		else if (CheckSkillPoint(PRO_SKILL2, 20, 39))
			bResistanceBonus = 60;
		else if (CheckSkillPoint(PRO_SKILL2, 40, MAX_LEVEL))
			bResistanceBonus = 90;

		_ITEM_TABLE *pLeftHand = GetItemPrototype(LEFTHAND);
		if (pLeftHand == nullptr || !pLeftHand->isShield())
		{
			bResistanceBonus /= 2;
			bDefenseBonus /= 2;
		}

		m_bResistanceBonus = bResistanceBonus;
		m_sTotalAc += bDefenseBonus * m_sTotalAc / 100;
	}
	if (CheckClass(15))
	{
		if (m_sHp < 30 * m_iMaxHp / 100)
		{
			m_sTotalAc = 20 * m_sTotalAc / 100;
		}
	}
	else if (isRogue())
	{
		if (m_sHp < 30 * m_iMaxHp / 100)
			m_bResistanceBonus += 50;
	}

	if (m_bAddWeaponDamage > 0)
		++m_sTotalHit;

	if (m_sAddArmourAc > 0 || m_bPctArmourAc > 100)
		++m_sTotalAc;

	uint8 bSta = GetStat(STAT_STA);
	if (bSta > 100)
	{
		m_sTotalAc += bSta - 100;
	}

	uint8 bInt = GetStat(STAT_INT);
	if (bInt > 100)
		m_bResistanceBonus += (bInt - 100) / 2;

	if(isGM())
	{
		m_sTotalHit += 500 * m_sTotalHit / 100;
		m_sTotalAc += 400 * m_sTotalAc / 100;
	}

	UpdateAchieveStatus(iSkillTitle);

	if (bSendPacket)
		SendItemMove(2);

	_KNIGHTS_SIEGE_WARFARE *pKnightSiege = g_pMain->GetSiegeMasterKnightsPtr(1);
	CKnights *pKnightsMaster = g_pMain->GetClanPtr(pKnightSiege->sMasterKnights);

	if (pKnightsMaster != nullptr && GetZoneID() == ZONE_DELOS)
	{
		Packet result(WIZ_SIEGE, uint8(2));
		result << uint8(0) << pKnightsMaster->GetID() << pKnightsMaster->m_sMarkVersion;
		Send(&result);	
	}

	Send2AI_UserUpdateInfo();
}


void CUser::SendTargetHP( uint8 echo, int tid, int damage )
{
 	int hp = 0, maxhp = 0;

	Unit *pTarget = nullptr;

	if (tid >= NPC_BAND)
	{
		if (g_pMain->m_bPointCheckFlag == false) return;
		CNpc *pNpc = g_pMain->GetNpcPtr(tid);
		if (pNpc == nullptr)
			return;

		hp = pNpc->m_iHP;	
		maxhp = pNpc->m_iMaxHP;
		pTarget = pNpc;
	}
	else 
	{
		CUser *pUser = g_pMain->m_socketMgr [tid];
		if (pUser == nullptr || pUser->isDead()) 
			return;

		hp = pUser->m_sHp;	
		maxhp = pUser->m_iMaxHp;
		pTarget = pUser;
	}

	Packet result(WIZ_TARGET_HP);
	g_pMain->SendHelpDescription(this, string_format("Target ID : %d",tid));
	result << uint16(tid) << echo << maxhp << hp << uint16(damage);
	Send(&result);
}


void CUser::BundleOpenReq(Packet & pkt)
{
	Packet result(WIZ_BUNDLE_OPEN_REQ);
	uint32 bundle_index = pkt.read<uint32>();
	C3DMap* pMap = GetMap();
	CRegion * pRegion = GetRegion();

	if (pMap == nullptr
		|| bundle_index < 1 
		|| pRegion == nullptr
		|| isDead())
		return;

	Guard lock(pRegion->m_RegionItemArray.m_lock);
	_LOOT_BUNDLE *pBundle = pRegion->m_RegionItemArray.GetData(bundle_index);
	if (pBundle == nullptr
		|| !isInRange(pBundle->x, pBundle->z, MAX_LOOT_RANGE))
		return;

	result << bundle_index << uint8(1);

	foreach (itr, pBundle->Items)
		result << itr->nItemID << itr->sCount;

	for (uint32 i = pBundle->Items.size(); i < LOOT_ITEMS; i++)
		result << uint32(0) << uint16(0);

	Send(&result);
}


void CUser::ItemGet(Packet & pkt)
{
	Packet result(WIZ_ITEM_GET);
	uint32 nBundleID = pkt.read<uint32>(), nItemID = pkt.read<uint32>();
	_LOOT_BUNDLE * pBundle = nullptr;
	_LOOT_ITEM * pItem = nullptr;
	CRegion* pRegion = GetRegion();
	CUser * pReceiver = nullptr;

	Guard lock(pRegion->m_RegionItemArray.m_lock);

	if (pRegion == nullptr
		|| isTrading()
		|| isDead()
		|| (pBundle = pRegion->m_RegionItemArray.GetData(nBundleID)) == nullptr
		|| !isInRange(pBundle->x, pBundle->z, MAX_LOOT_RANGE))
		goto fail_return;

	foreach (itr, pBundle->Items)
	{
		if (itr->nItemID == nItemID)
		{
			pItem = &(*itr);
			break;
		}
	}

	if (pItem == nullptr
		|| pItem->sCount == 0
		|| (pReceiver = GetLootUser(pBundle, pItem)) == nullptr)
		goto fail_return;

	if (nItemID == ITEM_GOLD)
	{
		_PARTY_GROUP * pParty;
		uint32 pGold = 0;
		if (!isInParty()
			|| (pParty = g_pMain->GetPartyPtr(GetPartyID())) == nullptr)
		{
			if (GetPremiumProperty(PremiumNoahPercent) > 0)
				pGold = pItem->sCount * (100 + GetPremiumProperty(PremiumNoahPercent)) / 100;
			else
				pGold = pItem->sCount;

			GoldGain(pGold, false, true);
			result << uint8(LootSolo) << nBundleID << int8(-1) << nItemID << pItem->sCount << GetCoins();
			pReceiver->Send(&result);
			GoldEvent(pGold);
		}
		else
		{
			uint16 sumOfLevels = 0;
			vector<CUser *> partyUsers;
			for (int i = 0; i < MAX_PARTY_USERS; i++)
			{
				CUser * pUser = g_pMain->GetUserPtr(pParty->uid[i]);
				if (pUser == nullptr)
					continue;

				sumOfLevels += pUser->GetLevel();
				partyUsers.push_back(pUser);
			}

			if (partyUsers.empty())
				goto fail_return;

			foreach (itr, partyUsers)
			{
				if ((*itr)->isDead() || 
					!(*itr)->isInRange(pBundle->x, pBundle->z, RANGE_50M))
					continue;

				int coins = (int)(pItem->sCount * (float)((*itr)->GetLevel() / (float)sumOfLevels));

				if ((*itr)->GetPremiumProperty(PremiumNoahPercent) > 0)
					pGold = coins * (100 + (*itr)->GetPremiumProperty(PremiumNoahPercent)) / 100;
				else
					pGold = coins;

				(*itr)->GoldGain(pGold, false, true);

				result.clear();
				result << uint8(LootPartyCoinDistribution) << nBundleID << uint8(-1) << nItemID << (*itr)->GetCoins();
				(*itr)->Send(&result);
				(*itr)->GoldEvent(pGold);
			}
		}
	}
	else
	{
		if (pReceiver->isDead() || 
			!pReceiver->isInRange(pBundle->x, pBundle->z, RANGE_50M))
			(pReceiver = GetLootUser(pBundle, pItem));

		int8 bDstPos = pReceiver->FindSlotForItem(pItem->nItemID, pItem->sCount);

		if (bDstPos < 0)
			goto fail_return;

		if (!pReceiver->CheckWeight(pItem->nItemID, pItem->sCount))
		{
			result << uint8(LootNoRoom);
			pReceiver->Send(&result);
			return;
		}

		_ITEM_TABLE * pTable = g_pMain->GetItemPtr(nItemID);
		_ITEM_DATA * pDstItem = &pReceiver->m_sItemArray[bDstPos];

		pDstItem->nNum    = pItem->nItemID;
		pDstItem->sCount += pItem->sCount;

		if (pDstItem->sCount == pItem->sCount)
		{
			pDstItem->nSerialNum = g_pMain->GenerateItemSerial();
			pDstItem->sDuration  = pTable->m_sDuration; 
		}

		if (pDstItem->sCount > MAX_ITEM_COUNT)
			pDstItem->sCount = MAX_ITEM_COUNT;

		result	<< uint8(pReceiver == this ? LootSolo : LootPartyItemGivenToUs)
			<< nBundleID 
			<< uint8(bDstPos - SLOT_MAX) 
			<< pDstItem->nNum << pDstItem->sCount
			<< pReceiver->GetCoins();

		pReceiver->Send(&result);

		pReceiver->SetUserAbility(false);
		pReceiver->SendItemWeight();

		bool HasObtained = false;

		if (pTable->m_ItemType == 4 && pTable->Getnum() != ITEM_MONSTER_STONE) 
			HasObtained = true;

		if (HasObtained)
		{
			Packet drop(WIZ_LOGOSSHOUT, uint8(0x02));
			drop.SByte();
			drop << uint8(0x04) << pReceiver->GetName() << pTable->Getnum();
			g_pMain->Send_All(&drop);
		}
		if (isInParty())
		{
			result.clear();
			result << uint8(LootPartyNotification) << nBundleID << nItemID << pReceiver->GetName();
			g_pMain->Send_PartyMember(GetPartyID(), &result);

			if (pReceiver != this)
			{
				result.clear();
				result << uint8(LootPartyItemGivenAway);
				Send(&result);
			}
		}
	}

	GetMap()->RegionItemRemove(pRegion, pBundle, pItem);
	return;

fail_return:
	result << uint8(LootError);
	Send(&result);
}


CUser * CUser::GetLootUser(_LOOT_BUNDLE * pBundle, _LOOT_ITEM * pItem)
{
	CUser * pReceiver = nullptr;

	if (pBundle == nullptr
		|| pItem == nullptr)
		return nullptr;

	if (pItem->nItemID == ITEM_GOLD)
	{
		if (!isInParty())
		{
			if ((GetCoins() + pItem->sCount) > COIN_MAX)
				return nullptr;
		}
		return this; 
	}

	if (isInParty())
	{
		return GetItemRoutingUser(pItem->nItemID, pItem->sCount);
	}
	else
	{
		pReceiver = this;
	}

	return pReceiver;
}

void CUser::StateChange(Packet & pkt)
{
	if (isDead())
		return;

	uint8 bType = pkt.read<uint8>(), buff;
	uint32 nBuff = pkt.read<uint32>();
	buff = *(uint8 *)&nBuff;

	switch (bType)
	{
	case 1:
		if (buff != USER_STANDING && buff != USER_SITDOWN)
			return;
		if (buff == USER_STANDING)
		{
			m_TrainingExp = 0;
			m_TrainingTime = 0;
			m_LastTraining = UNIXTIME;
		}
		break;

	case 3:
		if ((buff == 1 || buff == 5)
			&& !isGM())
			return;
		break;

	case 4:
		switch (buff)
		{
		case 1:
		case 2:
		case 3:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			break;

		default:
			TRACE("[SID=%d] StateChange: %s tripped (bType=%d, buff=%d, nBuff=%d) somehow, HOW!?\n", 
				GetSocketID(), GetName().c_str(), bType, buff, nBuff);
			break;
		}
		break;

	case 5:
		if (!isGM())
			return;
		break;

	case 7:
		return;
		break;

	case 13:
		return;
		break;

	default:
		TRACE("[SID=%d] StateChange: %s tripped (bType=%d, buff=%d, nBuff=%d) somehow, HOW!?\n", 
			GetSocketID(), GetName().c_str(), bType, buff, nBuff);
		return;
	}

	StateChangeServerDirect(bType, nBuff);
}


void CUser::StateChangeServerDirect(uint8 bType, uint32 nBuff)
{
	uint8 buff = *(uint8 *)&nBuff;
	switch (bType)
	{
	case 1:
		m_bResHpType = buff;
		break;

	case 2:
		m_bNeedParty = buff;
		break;

	case 3:
		m_nOldAbnormalType = m_bAbnormalType;

		if (isGM())
			StateChangeServerDirect(5, 1);

		m_bAbnormalType = nBuff;
		break;

	case 5:
		m_bAbnormalType = nBuff;
		break;

	case 6:
		nBuff = m_bPartyLeader;
		break;

	case 7:
		UpdateVisibility((InvisibilityType)buff);
		break;

	case 8:
		break;
	}

	Packet result(WIZ_STATE_CHANGE);
	result << GetSocketID() << bType << nBuff; 
	SendToRegion(&result);
}

void CUser::LoyaltyChange(int16 tid, uint16 bonusNP /*= 0*/)
{
	short loyalty_source = 0, loyalty_target = 0;

	if (!GetMap()->isNationPVPZone() && !g_pMain->m_byBattleSiegeWarOpen
		|| GetZoneID() == ZONE_DESPERATION_ABYSS 
		|| GetZoneID() == ZONE_HELL_ABYSS 
		|| GetZoneID() == ZONE_DRAGON_CAVE 
		|| GetZoneID() == ZONE_CAITHAROS_ARENA)
		return;

	CUser* pTUser = g_pMain->GetUserPtr(tid);  
	if (pTUser == nullptr) 
		return;

	if (pTUser->GetNation() != GetNation() || g_pMain->m_byBattleSiegeWarOpen) 
	{
		if (pTUser->GetLoyalty() == 0) 
		{
			loyalty_source = 0;
			loyalty_target = 0;
		}
		else if (pTUser->GetZoneID() == ZONE_ARDREAM)
		{
			loyalty_source = g_pMain->m_Loyalty_Ardream_Source; 
			loyalty_target = g_pMain->m_Loyalty_Ardream_Target;
		}
		else if (pTUser->GetZoneID() == ZONE_RONARK_LAND_BASE)
		{
			loyalty_source = g_pMain->m_Loyalty_Ronark_Land_Base_Source; 
			loyalty_target = g_pMain->m_Loyalty_Ronark_Land_Base_Target;
		}
		else if (pTUser->GetZoneID() == ZONE_RONARK_LAND) 
		{
			loyalty_source = g_pMain->m_Loyalty_Ronark_Land_Source;
			loyalty_target = g_pMain->m_Loyalty_Ronark_Land_Target;
		}
		else if (pTUser->GetZoneID() == ZONE_PVP_EVENT) 
		{
			loyalty_source = g_pMain->m_Loyalty_Mini_Pvp_Source;
			loyalty_target = g_pMain->m_Loyalty_Mini_Pvp_Target;
		}
		else 
		{
			loyalty_source = g_pMain->m_Loyalty_Other_Zone_Source;
			loyalty_target = g_pMain->m_Loyalty_Other_Zone_Target;
		}
	}

	loyalty_source += bonusNP;

	SendLoyaltyChange(loyalty_source, true, false, pTUser->GetMonthlyLoyalty() > 0 ? true : false);

	pTUser->SendLoyaltyChange(loyalty_target, true, false, pTUser->GetMonthlyLoyalty() > 0 ? true : false);

	if (g_pMain->m_byBattleOpen && GetMap()->isWarZone())
	{
		if (pTUser->GetNation() == KARUS)
			g_pMain->m_sKarusDead++;
		else 
			g_pMain->m_sElmoradDead++;
	}
}

void CUser::UserLookChange(int pos, int itemid, int durability)
{
	if (pos >= SLOT_MAX)
		return;
	
	Packet result(WIZ_USERLOOK_CHANGE);
	result << GetSocketID() << uint8(pos) << itemid << uint16(durability);

	if (g_pMain->pTempleEvent.ActiveEvent != -1 && GetZoneID() == uint8(isInTempleEventZone()))
		SendToRegion(&result, this, GetEventRoom());
	else
		SendToRegion(&result);
}

void CUser::RecvOpenDeletedItems(Packet & pkt)
{
	uint8 rows = pkt.read<uint8>();

	Packet result(WIZ_ITEM_TRADE, uint8(5));
	result << uint8(1)
		   << uint8(1)
		   << uint16(rows);

	for(int x = 1; x <= rows; x++)
	{
	  uint32 temp1 = pkt.read<uint32>();
      uint32 temp2 = pkt.read<uint32>();
	  uint32 temp3 = pkt.read<uint32>();
	  
	  result << temp1
		  << temp2
		  << temp3
		  << uint8(0);
	}
	Send(&result);
}

void CUser::SendNotice()
{
	Packet result(WIZ_NOTICE);
	uint8 count = 0;

	result << uint8(2); 
	result << count;

	for (int i = 0; i < 10; i += 2)
		AppendNoticeEntry(result, count, g_pMain->m_ppNotice[i + 1], g_pMain->m_ppNotice[i]);

	AppendExtraNoticeData(result, count);
	result.put(1, count);

	Send(&result);
}

void CUser::TopSendNotice()
{
	Packet result(WIZ_NOTICE);
    uint8 count = 0;

    result << uint8(1);
    result << count;
	result.SByte();
  
    for (int i = 0; i < 20; i++)
		AppendNoticeEntryOld(result, count, g_pMain->m_peNotice[i]);

	AppendExtraNoticeData(result, count);
    result.put(1, count);
    Send(&result);
}

void CUser::AppendNoticeEntryOld(Packet & pkt, uint8 & elementCount, const char * message)
{
        if (message == nullptr || *message == '\0')
                return;
		pkt << message;
        elementCount++;
}

void CUser::AppendNoticeEntry(Packet & pkt, uint8 & elementCount, const char * message, const char * title)
{
	if (message == nullptr || *message == '\0'
		|| title == nullptr || *title == '\0')
		return;

	pkt << title << message;
	elementCount++;
}

void CUser::AppendExtraNoticeData(Packet & pkt, uint8 & elementCount)
{
	string message;

	if (g_pMain->m_byExpEventAmount > 0)
	{
		g_pMain->GetServerResource(IDS_EXP_REPAY_EVENT, &message, g_pMain->m_byExpEventAmount);
		AppendNoticeEntry(pkt, elementCount, message.c_str(), "EXP Event"); 
	}

	if (g_pMain->m_byCoinEventAmount > 0)
	{
		g_pMain->GetServerResource(IDS_MONEY_REPAY_EVENT, &message, g_pMain->m_byCoinEventAmount);
		AppendNoticeEntry(pkt, elementCount, message.c_str(), "NOAH Event"); 
	}

	if (g_pMain->m_byNPEventAmount > 0)
	{
		g_pMain->GetServerResource(IDS_NP_REPAY_EVENT, &message, g_pMain->m_byNPEventAmount);
		AppendNoticeEntry(pkt, elementCount, message.c_str(), "NP Event"); 
	}

	if (m_FlashExpBonus > 0)
	{
		g_pMain->GetServerResource(IDS_EXP_REPAY_FLASH, &message, m_FlashExpBonus);
		AppendNoticeEntry(pkt,elementCount,message.c_str(),"Experience");
	}

	if ( m_FlashDcBonus > 0)
	{
		g_pMain->GetServerResource(IDS_DC_REPAY_FLASH, &message, m_FlashDcBonus);
		AppendNoticeEntry(pkt,elementCount,message.c_str(),"Iteam Drop");
	}

	if ( m_FlashWarBonus > 0)
	{
		g_pMain->GetServerResource(IDS_WAR_REPAY_FLASH, &message, m_FlashWarBonus);
		AppendNoticeEntry(pkt,elementCount,message.c_str(),"National Point");
	}
}


void CUser::SkillPointChange(Packet & pkt)
{
	uint8 type = pkt.read<uint8>();
	Packet result(WIZ_SKILLPT_CHANGE, type);
	bool Error = false;
	if (isKurPor())
		if (type < SkillPointCat1 || type > SkillPointMaster 
			|| m_bstrSkill[0] < 1 
			|| m_bstrSkill[type] + 1 > GetLevel()
			|| (GetClass() % 100) <= 4
			|| (type == SkillPointMaster
			&& ((GetClass() % 2) != 1 || (GetClass() % 100) < 6
			|| m_bstrSkill[type] >= (MAX_LEVEL  - 60) 
			|| m_bstrSkill[type] >= (GetLevel() - 60))))
			Error = true;
	if (!isKurPor())
		if (type < SkillPointCat1 || type > SkillPointMaster 
			|| m_bstrSkill[0] < 1 
			|| m_bstrSkill[type] + 1 > GetLevel()
			|| (GetClass() % 100) <= 4
			|| (type == SkillPointMaster
			&& ((GetClass() % 2) != 0 || (GetClass() % 100) < 6
			|| m_bstrSkill[type] >= (MAX_LEVEL  - 60) 
			|| m_bstrSkill[type] >= (GetLevel() - 60))))
			Error = true;
	
	if (Error == true)
	{
		result << m_bstrSkill[type];
		Send(&result);
		return;
	}

	--m_bstrSkill[0];
	++m_bstrSkill[type];
}

void CUser::UpdateGameWeather(Packet & pkt)
{
	if (!isGM())
		return;

	if (pkt.GetOpcode() == WIZ_WEATHER)
	{
		pkt >> g_pMain->m_byWeather >> g_pMain->m_sWeatherAmount;
	}
	else
	{
		uint16 y, m, d;
		pkt >> y >> m >> d >> g_pMain->m_sHour >> g_pMain->m_sMin;
	}
	Send(&pkt);
}

void CUser::GetUserInfoForAI(Packet & result)
{
	Guard lock(m_equippedItemBonusLock);

	result.SByte(); 
	result	<< GetSocketID()
		<< GetName() << GetZoneID() << GetNation() << GetLevel()
		<< m_sHp << m_sMp 
		<< m_sTotalHit << m_bAttackAmount
		<< m_sTotalAc << m_sACAmount
		<< m_fTotalHitrate << m_fTotalEvasionrate
		<< m_sItemAc
		<< GetPartyID() << GetAuthority()
		<< m_bInvisibilityType
		<< uint32(m_equippedItemBonuses.size());

	foreach (itr, m_equippedItemBonuses)
	{
		result << itr->first << uint32(itr->second.size());
		foreach (bonusItr, itr->second)
			result << bonusItr->first << bonusItr->second;
	}
}

void CUser::CountConcurrentUser()
{
	if (!isGM())
		return;

	uint16 count = 0;
	SessionMap sessMap = g_pMain->m_socketMgr.GetActiveSessionMap();
	foreach (itr, sessMap)
	{
		if (TO_USER(itr->second)->isInGame())
			count++;
	}

	Packet result(WIZ_CONCURRENTUSER);
	result << count;
	Send(&result);
}

void CUser::LoyaltyDivide(int16 tid, uint16 bonusNP /*= 0*/)
{
	if (m_bZone == ZONE_SNOW_BATTLE
		|| m_bZone == ZONE_DESPERATION_ABYSS 
		|| m_bZone == ZONE_HELL_ABYSS 
		|| m_bZone == ZONE_DRAGON_CAVE 
		|| m_bZone == ZONE_CAITHAROS_ARENA)
		return;
	int16 loyalty_source = 0, loyalty_target = 0;
	uint8 total_member = 0;

	if (!isInParty())
		return;

	_PARTY_GROUP *pParty = g_pMain->GetPartyPtr(GetPartyID());
	if (pParty == nullptr)
		return;

	CUser* pTUser = g_pMain->GetUserPtr(tid);
	if (pTUser == nullptr) 
		return;

	for (int i = 0; i < MAX_PARTY_USERS; i++)
	{
		CUser *pUser = g_pMain->GetUserPtr(pParty->uid[i]);
		if (pUser == nullptr)
			continue;

		total_member++;
	}

	if (total_member <= 0)
		return;

	if (g_pMain->m_byBattleOpen
		&& GetZoneID() == (ZONE_BATTLE_BASE + g_pMain->m_byBattleZone))
	{
		if (pTUser->GetNation() == KARUS)
			g_pMain->m_sKarusDead++;
		else
			g_pMain->m_sElmoradDead++;
	}

	if (pTUser->GetNation() != GetNation())
	{
		if (pTUser->GetLoyalty() == 0)
		{
			loyalty_source = 0;
			loyalty_target = 0;
		}
		else
		{
			loyalty_source = GetLoyaltyDivideSource(total_member);
			loyalty_target = GetLoyaltyDivideTarget();

			if (loyalty_source == 0)
			{
				loyalty_source = 0;
				loyalty_target = 0;
			}
		}
	}
	else 
		return;

	for (int j = 0; j < MAX_PARTY_USERS; j++)
	{
		CUser *pUser = g_pMain->GetUserPtr(pParty->uid[j]);
		if (pUser == nullptr)
			continue;

		if (pUser->isAlive() && ((pUser->hasRival()
			&& !pUser->hasRivalryExpired()
			&& (pUser->GetRivalID() == pTUser->GetID())
			|| (pUser->GetRivalID() == pTUser->GetID()
			&& pUser->isPriest()))))
		{
			pUser->SendLoyaltyChange(loyalty_source + bonusNP, true, false, pTUser->GetMonthlyLoyalty() > 0 ? true : false);
			pUser->RemoveRival();
		}
		else
			pUser->SendLoyaltyChange(loyalty_source, true, false, pTUser->GetMonthlyLoyalty() > 0 ? true : false);
	}

	pTUser->SendLoyaltyChange(loyalty_target, true, false, pTUser->GetMonthlyLoyalty() > 0 ? true : false);
}

int16 CUser::GetLoyaltyDivideSource(uint8 totalmember)
{
	int16 nBaseLoyalty = 0;

	if (GetZoneID() == ZONE_ARDREAM)
		nBaseLoyalty = g_pMain->m_Loyalty_Ardream_Source;
	else if (GetZoneID() == ZONE_RONARK_LAND_BASE)
		nBaseLoyalty = g_pMain->m_Loyalty_Ronark_Land_Base_Source;
	else if (GetZoneID() == ZONE_RONARK_LAND)
		nBaseLoyalty = g_pMain->m_Loyalty_Ronark_Land_Source;
	else
		nBaseLoyalty = g_pMain->m_Loyalty_Other_Zone_Source;

	int16 nMaxLoyalty = (nBaseLoyalty * 3) - 2;
	int16 nMinLoyalty = nMaxLoyalty / MAX_PARTY_USERS;
	int16 nLoyaltySource = nMinLoyalty;

	if (nLoyaltySource > 0)
	{
		for (int i = 0; i < (MAX_PARTY_USERS - totalmember); i++)
			nLoyaltySource += 2;
	}

	return nLoyaltySource -1;
}

int16 CUser::GetLoyaltyDivideTarget()
{
	if (GetZoneID() == ZONE_ARDREAM)
		return g_pMain->m_Loyalty_Ardream_Target;
	else if (GetZoneID() == ZONE_RONARK_LAND_BASE)
		return g_pMain->m_Loyalty_Ronark_Land_Base_Target;
	else if (GetZoneID() == ZONE_RONARK_LAND)
		return g_pMain->m_Loyalty_Ronark_Land_Target;
	else if (GetZoneID() == ZONE_PVP_EVENT)
		return g_pMain->m_Loyalty_Mini_Pvp_Target;
	else
		return g_pMain->m_Loyalty_Other_Zone_Target;

	return 0;
}

void CUser::ItemWoreOut(int type, int damage)
{
	static uint8 armourTypes[] = {HEAD, BREAST, LEG, GLOVE, FOOT };
	static uint8 weaponsTypes[] = {RIGHTHAND, LEFTHAND};
	uint8 totalSlots;
	int worerate;

	if (type == ACID_ALL)
	worerate = damage;
	else
	worerate = (int)sqrt(damage / 10.0f);

	if (worerate == 0) return;

	ASSERT(type == ATTACK || type == DEFENCE || type == REPAIR_ALL || type == ACID_ALL);

	if (type == ATTACK)
		totalSlots = sizeof(weaponsTypes) / sizeof(*weaponsTypes);
	else if (type == DEFENCE)
		totalSlots = sizeof(armourTypes) / sizeof(*armourTypes);
	else if (type == REPAIR_ALL)
		totalSlots = sizeof(armourTypes) / sizeof(*armourTypes); 
	else if (type == ACID_ALL)
		totalSlots = sizeof(armourTypes) / sizeof(*armourTypes); 

	for (uint8 i = 0; i < totalSlots; i++) 
	{
		uint8 slot;
		if (type == DEFENCE)
		slot = armourTypes[i];
		else if (type == ATTACK)
		slot = weaponsTypes[i];
		else
		slot = armourTypes[i];

		_ITEM_DATA * pItem = GetItem(slot);
		_ITEM_TABLE * pTable = nullptr;

		if (pItem == nullptr 
			|| (pItem->sDuration <= 0 && type != REPAIR_ALL) 
			|| (pTable = g_pMain->GetItemPtr(pItem->nNum)) == nullptr
			|| (type == ATTACK 
			&& ((slot == LEFTHAND || slot == RIGHTHAND) && pTable->m_bSlot == ItemSlot1HLeftHand))) 
			continue;

		if (type == REPAIR_ALL)
		{
			pItem->sDuration = pTable->m_sDuration;
			SendDurability(slot, pItem->sDuration); 
			UserLookChange(slot, pItem->nNum, pItem->sDuration);
			continue;
		}

		int beforepercent = (int)((pItem->sDuration / (double)pTable->m_sDuration) * 100);
		int curpercent;

		if (worerate > pItem->sDuration)
			pItem->sDuration = 0;
		else 
			pItem->sDuration -= worerate;

		if (m_sItemArray[slot].sDuration == 0)
		{
			SendDurability(slot, 0);
			SetUserAbility(false);
			SendItemMove(1);
			continue;
		}

		SendDurability(slot, pItem->sDuration); 

		curpercent = (int)((pItem->sDuration / (double)pTable->m_sDuration) * 100);

		if ((curpercent / 5) != (beforepercent / 5)) 
		{
			if (curpercent >= 65 && curpercent < 70
				|| curpercent >= 25 && curpercent < 30)
				UserLookChange(slot, pItem->nNum, pItem->sDuration);
		}
	}
}

void CUser::SendDurability(uint8 slot, uint16 durability)
{
	Packet result(WIZ_DURATION, slot);
	result << durability;
	Send(&result);
}

void CUser::SendItemMove(uint8 subcommand)
{
	Packet result(WIZ_ITEM_MOVE, uint8(1));
	if (m_bAttackAmount == 0)
		m_bAttackAmount = 100;

	if (subcommand != 0)
	{
		result << subcommand
			<< uint16(m_sTotalHit * m_bAttackAmount / 100) 
			<< uint16(m_sTotalAc + m_sACAmount)
			<< m_sMaxWeight
			<< uint8(1)
			<< m_iMaxHp << m_iMaxMp
			<< GetStatBonusTotal(STAT_STR) << GetStatBonusTotal(STAT_STA)
			<< GetStatBonusTotal(STAT_DEX) << GetStatBonusTotal(STAT_INT)
			<< GetStatBonusTotal(STAT_CHA)
			<< uint16(((m_sFireR + m_bAddFireR) * m_bPctFireR / 100) + m_bResistanceBonus) 
			<< uint16(((m_sColdR + m_bAddColdR) * m_bPctColdR / 100) + m_bResistanceBonus) 
			<< uint16(((m_sLightningR + m_bAddLightningR) * m_bPctLightningR / 100) + m_bResistanceBonus) 
			<< uint16(((m_sMagicR + m_bAddMagicR) * m_bPctMagicR / 100) + m_bResistanceBonus) 
			<< uint16(((m_sDiseaseR + m_bAddDiseaseR) * m_bPctDiseaseR / 100) + m_bResistanceBonus) 
			<< uint16(((m_sPoisonR + m_bAddPoisonR) * m_bPctPoisonR / 100) + m_bResistanceBonus);
	}
	Send(&result);
}

void CUser::SendItemArranging()
{
	Packet result(WIZ_ITEM_MOVE, uint8(2));
	result << uint8(1);

	result << uint8(0)
		<< uint8(15)
		<< uint32(379068000);

	Send(&result);
}

void CUser::SetTrainingMode()
{
	m_LastTraining = UNIXTIME;

	if (isMining() || isDead())
		return;

	if (m_bResHpType == USER_STANDING)
		return;

	uint64 myExp = g_pMain->GetExpByLevel(GetLevel());

	if (GetLevel() >= MAX_LEVEL && m_iExp == myExp || GetRebLevel() > 4)
		return;

	if (m_bResHpType == USER_SITDOWN)
	{
		uint8 level;
		uint32 iExp = 0;

		level = GetLevel();
		if(level >= 10 && level <= 20)
			iExp = 50;
		else if(level > 20 && level <= 40)
			iExp = 200;
		else if(level > 40 && level <= 60)
			iExp = 1000;
		else if(level > 60 && level <= 70)
			iExp = 2000;
		else if(level > 70 && level <= 80)
			iExp = 2500;
		else if(level > 80)
			iExp = 5000;

		m_TrainingExp += iExp;
		m_TrainingTime += 10;

		if(m_TrainingTime >= 7200 )
		{
			m_GenieTime += 20;

			Packet Genie(WIZ_GENIE, uint8(1));
			Genie << uint8(6)
				<< m_GenieTime;

			Send(&Genie);

			m_TrainingTime = 0;

			Packet result(WIZ_MINING, uint8(18));
			result << uint8(2);

			Send(&result);
		}

		ExpChange(iExp);

		Packet Training(WIZ_MINING, uint8(18));
		Training << uint8(3)
			<< m_TrainingExp;

		Send(&Training);
	}
		
}

void CUser::StaminaTimeChange()
{
	m_tSPLastTimeNormal = UNIXTIME;

	if (isDead())
		return;

	if (m_iMaxSp != m_sSp)
		SpChange(30);
}

void CUser::HPTimeChange()
{
	m_tHPLastTimeNormal = UNIXTIME;

	if (isDead())
		return;

	int mpPercent = 100;

	if (GetZoneID() == ZONE_SNOW_BATTLE 
		&& g_pMain->m_byBattleOpen == SNOW_BATTLE)
	{
		HpChange(5);
		return;
	}

	if (CheckClass(110, 210)
		&& m_sMp < (30 * m_iMaxMp / 100))
		mpPercent = 120;

	if (m_bResHpType == USER_STANDING)
	{
		if (isTransformed())
		{
			// TODO: Apply transformation rates
		}
		else if (m_iMaxMp != m_sMp)
		{
			MSpChange((int)(((GetLevel() * (1 + GetLevel() / 60.0) + 1) * 0.2) + 3) * mpPercent / 100);
		}
	}
	else if (m_bResHpType == USER_SITDOWN)
	{
		if (isGM())
		{
			HpChange(m_iMaxHp);
			MSpChange(m_iMaxMp);
		}
		else
		{
			if (m_iMaxHp != m_sHp)
				HpChange((int)(GetLevel() * (1 + GetLevel() / 30.0)) + 3);

			if (m_iMaxMp != m_sMp)
				MSpChange((int)(((m_iMaxMp * 5) / ((GetLevel() - 1) + 30 )) + 3) * mpPercent / 100);
		}
	}
}

void CUser::HPTimeChangeType3()
{
	if (isDead()
		|| !m_bType3Flag)
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

				Send(&result);

				if (pEffect->m_byAttribute == POISON_R)
					SendUserStatusUpdate(USER_STATUS_POISON, USER_STATUS_CURE);

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

	if (bIsDOT && totalActiveDOTSkills == 0)
		SendUserStatusUpdate(USER_STATUS_DOT, USER_STATUS_CURE);
}

void CUser::Type4Duration()
{
	Guard lock(m_buffLock);
	if (m_buffMap.empty())
		return;

	foreach (itr, m_buffMap)
	{
		if (itr->second.m_tEndTime > UNIXTIME)
			continue;

		CMagicProcess::RemoveType4Buff(itr->first, this, true, isLockableScroll(itr->second.m_bBuffType));
		break;
	}

	if (!isDebuffed())
		SendUserStatusUpdate(USER_STATUS_POISON, USER_STATUS_CURE);
}

void CUser::SendAllKnightsID()
{
	Packet result(WIZ_KNIGHTS_LIST, uint8(1));
	uint16 count = 0;

	foreach_stlmap (itr, g_pMain->m_KnightsArray)
	{
		CKnights *pKnights = itr->second;
		if (pKnights == nullptr)
			continue;
		result << pKnights->m_sIndex << pKnights->m_strName;
		count++;
	}

	result.put(0, count);
	SendCompressed(&result);
}

void CUser::OperatorCommand(Packet & pkt)
{
	if (!isGM())
		return;

	std::string strUserID;
	uint8 opcode;
	bool bIsOnline = false;
	std::string sNoticeMessage, sOperatorCommandType;
	pkt >> opcode >> strUserID;

	if (strUserID.empty() || strUserID.size() > MAX_ID_SIZE)
		return;

	CUser *pUser = g_pMain->GetUserPtr(strUserID, TYPE_CHARACTER);
	if (pUser == nullptr)
		bIsOnline = false;
	else
		bIsOnline = true;

	switch (opcode)
	{
	case OPERATOR_ARREST:
		if (bIsOnline)
		{
			ZoneChange(pUser->GetZoneID(), pUser->m_curx, pUser->m_curz);
			sOperatorCommandType = "OPERATOR_ARREST";
		}
		break;
	case OPERATOR_SUMMON:
		if (bIsOnline)
		{
			pUser->ZoneChange(GetZoneID(), m_curx, m_curz);
			sOperatorCommandType = "OPERATOR_SUMMON";
		}
		break;
	case OPERATOR_CUTOFF:
		if (bIsOnline)
		{
			pUser->Disconnect();
			sOperatorCommandType = "OPERATOR_CUTOFF";
		}
		break;
	case OPERATOR_BAN:
	case OPERATOR_BAN_ACCOUNT:
		if (bIsOnline)
		{
			pUser->m_bAuthority = AUTHORITY_BANNED;
			pUser->Disconnect();
		}
		else 
			g_DBAgent.UpdateUserAuthority(strUserID,AUTHORITY_BANNED);

		sOperatorCommandType = "OPERATOR_BAN_ACCOUNT";
		sNoticeMessage = string_format("%s is currently blocked for illegal activity.", strUserID.c_str());
		break;
	case OPERATOR_MUTE:
		if (bIsOnline)
			pUser->m_bAuthority = AUTHORITY_MUTED;
		else
			g_DBAgent.UpdateUserAuthority(strUserID,AUTHORITY_MUTED);

		sOperatorCommandType = "OPERATOR_MUTE";
		sNoticeMessage = string_format("%s is currently muted.", strUserID.c_str());
		break;
	case OPERATOR_DISABLE_ATTACK:
		if (bIsOnline) 
			pUser->m_bAuthority = AUTHORITY_ATTACK_DISABLED;
		else
			g_DBAgent.UpdateUserAuthority(strUserID,AUTHORITY_ATTACK_DISABLED);
		sOperatorCommandType = "OPERATOR_DISABLE_ATTACK";
		sNoticeMessage = string_format("%s is currently attack disabled.", strUserID.c_str());
		break;
	case OPERATOR_ENABLE_ATTACK:
		if (bIsOnline)
			pUser->m_bAuthority = AUTHORITY_PLAYER;
		else
			g_DBAgent.UpdateUserAuthority(strUserID,AUTHORITY_PLAYER);
		sOperatorCommandType = "OPERATOR_ENABLE_ATTACK";
		sNoticeMessage = string_format("%s is currently attack enabled.", strUserID.c_str());
		break;
	case OPERATOR_UNMUTE:
		if (bIsOnline)
			pUser->m_bAuthority = AUTHORITY_PLAYER;
		else
			g_DBAgent.UpdateUserAuthority(strUserID,AUTHORITY_PLAYER);
		sOperatorCommandType = "OPERATOR_UNMUTE";
		sNoticeMessage = string_format("%s is currently unmuted.", strUserID.c_str());
		break;
	}

	if (!sNoticeMessage.empty())
		g_pMain->SendNotice(sNoticeMessage.c_str(),Nation::ALL);

	if (!sOperatorCommandType.empty())
	{
		DateTime time;
		g_pMain->WriteGMLogFile(string_format("[ GAME MASTER - %d:%d:%d ] %s : %s %s ( Zone=%d, X=%d, Z=%d )\n",time.GetHour(),time.GetMinute(),time.GetSecond(),GetName().c_str(),sOperatorCommandType.c_str(),strUserID.c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ())));
	}
}

int CUser::FindSlotForItem(uint32 nItemID, uint16 sCount /*= 1*/)
{
	int result = -1;
	_ITEM_TABLE *pTable = g_pMain->GetItemPtr(nItemID);
	if (pTable == nullptr)
		return result;

	if (pTable->m_bCountable)
	{
		for (int i = SLOT_MAX; i < SLOT_MAX+HAVE_MAX; i++)
		{
			_ITEM_DATA *pItem = GetItem(i);

			if(pItem == nullptr)
				continue; 

			if (pItem
				&& pItem->nNum == nItemID 
				&& pItem->sCount + sCount <= ITEMCOUNT_MAX)
				return i;

			if (pItem->nNum == 0
				&& result < 0)
				result = i;
		}
		return result;
	}
	return GetEmptySlot();
}

int CUser::GetEmptySlot()
{
	for (int i = SLOT_MAX; i < SLOT_MAX+HAVE_MAX; i++)
	{
		_ITEM_DATA *pItem = GetItem(i);

		if (!pItem) 
			continue; 

		if (pItem->nNum == 0)
			return i;
	}

	return -1;
}

int CUser::GetCountEmptySlot()
{
	int  sFreeSlots  = 0;
	for (int i = SLOT_MAX; i < SLOT_MAX+HAVE_MAX; i++)
	{
		if (GetItem(i)->nNum == 0)
		{
			sFreeSlots++;
		}
	}

	return sFreeSlots;
}

void CUser::Home()
{
	if (isDead()
			|| isKaul()
			|| GetHealth() < (GetMaxHealth() / 2)
			|| GetZoneID() == ZONE_CHAOS_DUNGEON
			|| GetZoneID() == ZONE_JURAD_MOUNTAIN
			|| GetZoneID() == ZONE_BORDER_DEFENSE_WAR
			|| hasBuff(BUFF_TYPE_FREEZE))
			return;

	short x = 0, z = 0;

	_OBJECT_EVENT* pEvent = nullptr;
	pEvent = GetMap()->GetObjectEvent(m_sBind);	

	if (pEvent && pEvent->byLife == 1 && GetZoneID() != ZONE_DELOS && pEvent->sIndex != 101 && pEvent->sIndex != 201)
	{
		SetPosition(pEvent->fPosX + x, 0.0f, pEvent->fPosZ + z);
		x = short(pEvent->fPosX);
		z = short(pEvent->fPosZ);
		Warp(x * 10, z * 10);
		return;
	}

	if (GetZoneID() == ZONE_FORGOTTEN_TEMPLE)
	{
		KickOutZoneUser(true);
		return;
	}
	else if ((GetZoneID() / 10) == 5
		|| !GetStartPosition(x, z))
		return;
	Warp(x * 10, z * 10);
}

bool CUser::GetStartPosition(short & x, short & z, uint8 bZone /*= 0 */)
{
	int nZoneID = (bZone == 0 ? GetZoneID() : bZone);
	_START_POSITION *pData = g_pMain->GetStartPosition(nZoneID);
	_KNIGHTS_SIEGE_WARFARE *pKnightSiege = g_pMain->GetSiegeMasterKnightsPtr(1);
	CKnights *pKnights = g_pMain->GetClanPtr(pKnightSiege->sMasterKnights);
	if (pData == nullptr)
		return false;

	if (pKnightSiege->sMasterKnights == GetClanID() && GetZoneID() == ZONE_DELOS && GetClanID() != 0)
	{
		x = 505 + myrand(0, pData->bRangeX);
		z = 840 + myrand(0, pData->bRangeZ);
	}
	else
	{
		if (GetNation() == KARUS)
		{
			x = pData->sKarusX + myrand(0, pData->bRangeX);
			z = pData->sKarusZ + myrand(0, pData->bRangeZ);
		}
		else
		{
			x = pData->sElmoradX + myrand(0, pData->bRangeX);
			z = pData->sElmoradZ + myrand(0, pData->bRangeZ);
		}
	}

	return true;
}

bool CUser::GetStartPositionRandom(short & x, short & z, uint8 bZone)
{
	int nRandom = myrand(0, g_pMain->m_StartPositionRandomArray.GetSize() - 1);
	goto GetPosition;

GetPosition:
	{
		if (g_pMain->m_StartPositionRandomArray.GetData(nRandom)->ZoneID == (bZone == 0 ? GetZoneID() : bZone))
		{
			x = g_pMain->m_StartPositionRandomArray.GetData(nRandom)->PosX + myrand(0, g_pMain->m_StartPositionRandomArray.GetData(nRandom)->Radius);
			z = g_pMain->m_StartPositionRandomArray.GetData(nRandom)->PosZ + myrand(0, g_pMain->m_StartPositionRandomArray.GetData(nRandom)->Radius);
			return true;
		}

		nRandom = myrand(0, g_pMain->m_StartPositionRandomArray.GetSize() - 1);
		goto GetPosition;
	}

	return GetStartPosition(x, z);
}

void CUser::ResetWindows()
{
	if (isTrading())
		ExchangeCancel();

	if (m_bRequestingChallenge)
		HandleChallengeCancelled(m_bRequestingChallenge);

	if (m_bChallengeRequested)
		HandleChallengeRejected(m_bChallengeRequested);

	if (isMerchanting())
		MerchantClose();

	if (m_sMerchantsSocketID >= 0)
		CancelMerchant();

	if(isMining())
	{
		HandleMiningStop((Packet)(WIZ_MINING, MiningStop));
		HandleFishingStop((Packet)(WIZ_MINING,FishingStop));
	}
}

CUser * CUser::GetItemRoutingUser(uint32 nItemID, uint16 sCount)
{
	if (!isInParty())
		return this;

	_ITEM_TABLE * pTable;
	_PARTY_GROUP * pParty = g_pMain->GetPartyPtr(GetPartyID());
	if (pParty == nullptr
		|| (pTable = g_pMain->GetItemPtr(nItemID)) == nullptr
		|| pParty->bItemRouting >= MAX_PARTY_USERS)
		return nullptr;

	for (int i = 0; i < MAX_PARTY_USERS; i++)
	{
		CUser * pUser = g_pMain->GetUserPtr(pParty->uid[pParty->bItemRouting]);

		if (pParty->bItemRouting > 6)
			pParty->bItemRouting = 0;
		else
			pParty->bItemRouting++;

		if (pUser != nullptr 
			&& pUser->CheckWeight(pTable, nItemID, sCount))
			return pUser;
	}

	return nullptr;
}

void CUser::ClassChangeReq()
{
	Packet result(WIZ_CLASS_CHANGE, uint8(CLASS_CHANGE_RESULT));
	if (GetLevel() < 10)
		result << uint8(2);
	else if ((m_sClass % 100) > 4)
		result << uint8(3);
	else
		result << uint8(1);
	Send(&result);
}

void CUser::SendStatSkillDistribute()
{
	m_bSkillActive = false;
	m_bSkillActive2 = false;
	m_PassiveRush = false;
	Packet result(WIZ_CLASS_CHANGE,uint8(CLASS_CHANGE_REQ));
	Send(&result); 
}

void CUser::AllSkillPointChange(bool bIsFree)
{
	Packet result(WIZ_CLASS_CHANGE, uint8(ALL_SKILLPT_CHANGE));
	int index = 0, skill_point = 0, money = 0, temp_value = 0, old_money = 0;
	uint8 type = 0;

	temp_value = (int)pow((GetLevel() * 2.0f), 3.4f);
	if (GetLevel() < 30)		
		temp_value = (int)(temp_value * 0.4f);
	else if (GetLevel() >= 60)
		temp_value = (int)(temp_value * 1.5f);

	temp_value = (int)(temp_value * 1.5f);

	if (g_pMain->m_sDiscount == 2
		|| (g_pMain->m_sDiscount == 1 && g_pMain->m_byOldVictory == m_bNation))
		temp_value /= 2;

	if (GetLevel() < 10)
		goto fail_return;

	for (int i = 1; i < 9; i++)
		skill_point += m_bstrSkill[i];

	if (skill_point <= 0)
	{
		type = 2;
		goto fail_return;
	}

	if (!bIsFree & !GoldLose(temp_value, false))
		goto fail_return;

	m_bstrSkill[0] = (GetLevel() - 9) * 2;
	for (int i = 1; i < 9; i++)	
		m_bstrSkill[i] = 0;

	result << uint8(1) << GetCoins() << m_bstrSkill[0];
	Send(&result);
	return;

fail_return:
	result << type << temp_value;
	Send(&result);
}

void CUser::AllPointChange(bool bIsFree)
{
	Packet result(WIZ_CLASS_CHANGE, uint8(ALL_POINT_CHANGE));
	int temp_money;
	uint16 statTotal;

	uint16 byStr, bySta, byDex, byInt, byCha;
	uint8 bResult = 0;

	if (GetLevel() > MAX_LEVEL)
		goto fail_return;

	temp_money = (int)pow((GetLevel() * 2.0f ), 3.4f);
	if (GetLevel() < 30)
		temp_money = (int)(temp_money * 0.4f);
	else if (GetLevel() >= 60) 
		temp_money = (int)(temp_money * 1.5f);

	if ((g_pMain->m_sDiscount == 1 && g_pMain->m_byOldVictory == GetNation())
		|| g_pMain->m_sDiscount == 2)
		temp_money /= 2;

	for (int i = 0; i < SLOT_MAX; i++)
	{
		if (m_sItemArray[i].nNum) {
			bResult = 4;
			goto fail_return;
		}
	}

	if (GetStatTotal() == 290)
	{
		bResult = 2;
		goto fail_return;
	}

	if (!bIsFree & !GoldLose(temp_money, false))
		goto fail_return;

	switch (m_bRace)
	{
	case KARUS_BIG:	
		if(isWarrior())
		{
		SetStat(STAT_STR, 65);
		SetStat(STAT_STA, 65);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		break;
	case KARUS_MIDDLE:
		if(isWarrior())
		{
		SetStat(STAT_STR, 65);
		SetStat(STAT_STA, 65);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		else
		{
		SetStat(STAT_STR, 60);
		SetStat(STAT_STA, 60);
		SetStat(STAT_DEX, 70);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		break;
	case KARUS_SMALL:
		if (isWarrior())
		{
		SetStat(STAT_STR, 65);
		SetStat(STAT_STA, 65);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		else if(isRogue())
		{
		SetStat(STAT_STR, 60);
		SetStat(STAT_STA, 60);
		SetStat(STAT_DEX, 70);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		else if(isPriest())
		{
		SetStat(STAT_STR, 50);
		SetStat(STAT_STA, 50);
		SetStat(STAT_DEX, 70);
		SetStat(STAT_INT, 70);
		SetStat(STAT_CHA, 50);
		}
		else  if(isMage())
		{
		SetStat(STAT_STR, 50);
		SetStat(STAT_STA, 60);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 70);
		SetStat(STAT_CHA, 50);
		}
		break;
	case KARUS_WOMAN:
		if (isWarrior())
		{
		SetStat(STAT_STR, 65);
		SetStat(STAT_STA, 65);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		else if(isRogue())
		{
		SetStat(STAT_STR, 60);
		SetStat(STAT_STA, 60);
		SetStat(STAT_DEX, 70);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		else if(isPriest())
		{
		SetStat(STAT_STR, 50);
		SetStat(STAT_STA, 50);
		SetStat(STAT_DEX, 70);
		SetStat(STAT_INT, 70);
		SetStat(STAT_CHA, 50);
		}
		else  if(isMage())
		{
		SetStat(STAT_STR, 50);
		SetStat(STAT_STA, 60);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 70);
		SetStat(STAT_CHA, 50);
		}
		break;
	case BABARIAN:
		if (isWarrior())
		{
		SetStat(STAT_STR, 65);
		SetStat(STAT_STA, 65);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		break;
	case ELMORAD_MAN:
		if (isWarrior())
		{
		SetStat(STAT_STR, 65);
		SetStat(STAT_STA, 65);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		else if(isRogue())
		{
		SetStat(STAT_STR, 60);
		SetStat(STAT_STA, 60);
		SetStat(STAT_DEX, 70);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		else if(isPriest())
		{
		SetStat(STAT_STR, 50);
		SetStat(STAT_STA, 50);
		SetStat(STAT_DEX, 70);
		SetStat(STAT_INT, 70);
		SetStat(STAT_CHA, 50);
		}
		else  if(isMage())
		{
		SetStat(STAT_STR, 50);
		SetStat(STAT_STA, 60);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 70);
		SetStat(STAT_CHA, 50);
		}
		break;
	case ELMORAD_WOMAN:	
		if (isWarrior())
		{
		SetStat(STAT_STR, 65);
		SetStat(STAT_STA, 65);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		else if(isRogue())
		{
		SetStat(STAT_STR, 60);
		SetStat(STAT_STA, 60);
		SetStat(STAT_DEX, 70);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		else if(isPriest())
		{
		SetStat(STAT_STR, 50);
		SetStat(STAT_STA, 50);
		SetStat(STAT_DEX, 70);
		SetStat(STAT_INT, 70);
		SetStat(STAT_CHA, 50);
		}
		else  if(isMage())
		{
		SetStat(STAT_STR, 50);
		SetStat(STAT_STA, 60);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 70);
		SetStat(STAT_CHA, 50);
		}
		break;
	case KARUS_KURIAN:
		if (isKurPor())
		{
		SetStat(STAT_STR, 65);
		SetStat(STAT_STA, 65);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		break;
	case ELMORAD_PORTU:
		if (isKurPor())
		{
		SetStat(STAT_STR, 65);
		SetStat(STAT_STA, 65);
		SetStat(STAT_DEX, 60);
		SetStat(STAT_INT, 50);
		SetStat(STAT_CHA, 50);
		}
		break;
	}

	m_sPoints = 10 + (GetLevel() - 1) * 3;

	if (GetLevel() > 60)
		m_sPoints += 2 * (GetLevel() - 60);

	statTotal = GetStatTotal();
	ASSERT(statTotal == 290);

	SetUserAbility();
	Send2AI_UserUpdateInfo();

	byStr = GetStat(STAT_STR);
	bySta = GetStat(STAT_STA), 
	byDex = GetStat(STAT_DEX);
	byInt = GetStat(STAT_INT),
	byCha = GetStat(STAT_CHA);

	RobItem(700001000, 1);

	result << uint8(1)
		<< GetCoins()
		<< byStr << bySta << byDex << byInt << byCha 
		<< m_iMaxHp << m_iMaxMp << m_sTotalHit << m_sMaxWeight << m_sPoints;
	Send(&result);
	return;

fail_return:
	result << bResult << temp_money;
	Send(&result);
}

void CUser::GiveKnightCash(uint32 nKnightCash)
{
	if (nKnightCash <= 0)
		return;

	m_nKnightCash += nKnightCash;
	g_DBAgent.UpdateAccountKnightCash(m_strAccountID,nKnightCash);
}
void CUser::GoldChange(short tid, int gold)
{
	if (m_bZone == ZONE_SNOW_BATTLE
		|| m_bZone == ZONE_DESPERATION_ABYSS 
		|| m_bZone == ZONE_HELL_ABYSS 
		|| m_bZone == ZONE_DRAGON_CAVE 
		|| m_bZone == ZONE_CAITHAROS_ARENA) 
		return;

	CUser* pTUser = g_pMain->GetUserPtr(tid);
	if (pTUser == nullptr || pTUser->m_iGold <= 0)
		return;

	if (gold == 0)
	{
		if (!isInParty())
		{
			GoldGain((pTUser->m_iGold * 4) / 10);
			pTUser->GoldLose(pTUser->m_iGold / 2);
			return;
		}

		_PARTY_GROUP* pParty = g_pMain->GetPartyPtr(GetPartyID());
		if (pParty == nullptr)
			return;

		int userCount = 0, levelSum = 0, temp_gold = (pTUser->m_iGold * 4) / 10;
		pTUser->GoldLose(pTUser->m_iGold / 2);

		for (int i = 0; i < MAX_PARTY_USERS; i++)
		{
			CUser *pUser = g_pMain->GetUserPtr(pParty->uid[i]);
			if (pUser == nullptr)
				continue;

			userCount++;
			levelSum += pUser->GetLevel();
		}

		if (userCount == 0) 
			return;

		for (int i = 0; i < MAX_PARTY_USERS; i++)
		{		
			CUser * pUser = g_pMain->GetUserPtr(pParty->uid[i]);
			if (pUser == nullptr)
				continue;

			pUser->GoldGain((int)(temp_gold * (float)(pUser->GetLevel() / (float)levelSum)));
		}			
		return;
	}

	if (gold > 0)
	{
		GoldGain(gold);
		pTUser->GoldLose(gold);
	}
	else
	{
		GoldLose(gold);
		pTUser->GoldGain(gold);
	}
}

void CUser::SelectWarpList(Packet & pkt)
{
	if (isDead())
		return;

	uint16 npcid, warpid;
	pkt >> npcid >> warpid;

	_WARP_INFO *pWarp = GetMap()->GetWarp(warpid);
	if (pWarp == nullptr
		|| (pWarp->sNation != 0 && pWarp->sNation != GetNation()))
		return;

	C3DMap *pMap = g_pMain->GetZoneByID(pWarp->sZone);
	if (pMap == nullptr)
		return;

	_ZONE_SERVERINFO *pInfo = g_pMain->m_ServerArray.GetData(pMap->m_nServerNo);
	if (pInfo == nullptr)
		return;

	float rx = 0.0f, rz = 0.0f;
	rx = (float)myrand(0, (int)pWarp->fR * 2);
	if (rx < pWarp->fR)
		rx = -rx;

	rz = (float)myrand(0, (int)pWarp->fR * 2);
	if (rz < pWarp->fR)
		rz = -rz;

	if (m_bZone == pWarp->sZone) 
	{
		m_bZoneChangeSameZone = true;

		Packet result(WIZ_WARP_LIST, uint8(2));
		result << uint8(1);
		Send(&result);
	}

	ZoneChange(pWarp->sZone, pWarp->fX + rx, pWarp->fZ + rz);

	if (GetZoneID() == pWarp->sZone && pWarp->dwPay > 0 && hasCoins(pWarp->dwPay))
		GoldLose(pWarp->dwPay);
}

void CUser::ServerChangeOk(Packet & pkt)
{
	return;
	C3DMap* pMap = GetMap();
	if (pMap == nullptr)
		return;

	uint16 warpid = pkt.read<uint16>();
	_WARP_INFO* pWarp = pMap->GetWarp(warpid);
	if (pWarp == nullptr)
		return;

	float rx = 0.0f, rz = 0.0f;
	rx = (float)myrand(0, (int)pWarp->fR * 2);
	if (rx < pWarp->fR)
		rx = -rx;

	rz = (float)myrand(0, (int)pWarp->fR * 2);
	if (rz < pWarp->fR)
		rz = -rz;

	ZoneChange(pWarp->sZone, pWarp->fX + rx, pWarp->fZ + rz);
}

bool CUser::GetWarpList(int warp_group)
{
	Packet result(WIZ_WARP_LIST, uint8(1));
	C3DMap* pMap = GetMap();
	set<_WARP_INFO*> warpList;

	if(pMap == nullptr)
		return false; 

	pMap->GetWarpList(warp_group, warpList);

	result << uint16(warpList.size());
	foreach (itr, warpList)
	{
		C3DMap *pDstMap = g_pMain->GetZoneByID((*itr)->sZone);
		if (pDstMap == nullptr)
			continue;

		if (g_pMain->isWarOpen()
			&& ((g_pMain->m_byBattleZoneType != ZONE_ARDREAM
			&& ((*itr)->sZone == ZONE_ARDREAM
			|| (*itr)->sZone == ZONE_RONARK_LAND_BASE
			|| (*itr)->sZone == ZONE_RONARK_LAND))
			|| (g_pMain->m_byBattleZoneType == ZONE_ARDREAM
			&& (*itr)->sZone == ZONE_ARDREAM)))
			continue;

		if (g_pMain->m_bEventZoneIsActive
			&& g_pMain->m_nEventZoneTime == 5
			&& (*itr)->sZone == ZONE_RONARK_LAND)
			continue;

		result	<< (*itr)->sWarpID 
			<< (*itr)->strWarpName << (*itr)->strAnnounce
			<< (*itr)->sZone
			<< pDstMap->m_sMaxUser
			<< uint32((*itr)->dwPay);
	}

	Send(&result);
	return true;
}

bool CUser::BindObjectEvent(_OBJECT_EVENT *pEvent)
{
	if (pEvent->sBelong != 0 && pEvent->sBelong != GetNation())
		return false;

	Packet result(WIZ_OBJECT_EVENT, uint8(pEvent->sType));

	m_sBind = pEvent->sIndex;

	result << uint8(1);
	Send(&result);
	return true;
}

bool CUser::GateLeverObjectEvent(_OBJECT_EVENT *pEvent, int nid)
{
	_OBJECT_EVENT *pGateEvent;
	CNpc* pNpc, *pGateNpc;
	_KNIGHTS_SIEGE_WARFARE *pKnightSiegewars = g_pMain->GetSiegeMasterKnightsPtr(1);
	CKnights *pKnight = g_pMain->GetClanPtr(GetClanID());
	if ((pNpc = g_pMain->GetNpcPtr(nid)) == nullptr
			|| (pGateEvent = GetMap()->GetObjectEvent(pEvent->sControlNpcID)) == nullptr
			|| (pGateNpc = g_pMain->FindNpcInZone(pEvent->sControlNpcID,GetZoneID())) == nullptr
			|| !pGateNpc->isGate()
			|| (pNpc->isGateClosed() && pNpc->GetNation() != 0 && pNpc->GetNation() != GetNation()))
			return false;

		pNpc->SendGateFlag(!pNpc->m_byGateOpen);
		pGateNpc->SendGateFlag(!pGateNpc->m_byGateOpen);

	return true;
}


bool CUser::FlagObjectEvent(_OBJECT_EVENT *pEvent, int nid)
{
	_OBJECT_EVENT *pFlagEvent;
	CNpc *pNpc, *pFlagNpc;

	if ((pNpc = g_pMain->GetNpcPtr(nid)) == nullptr
			|| (pFlagEvent = GetMap()->GetObjectEvent(pEvent->sControlNpcID)) == nullptr
			|| (pFlagNpc = g_pMain->FindNpcInZone(pEvent->sControlNpcID, GetZoneID())) == nullptr
			|| !pFlagNpc->isGate()
			|| g_pMain->m_bVictory > 0 || pNpc->isGateClosed())
			return false;

	pNpc->SendGateFlag(0);
	pFlagNpc->SendGateFlag(0);

	if (GetNation() == KARUS) 
		g_pMain->m_bKarusFlag++;
	else
		g_pMain->m_bElmoradFlag++;

	g_pMain->BattleZoneVictoryCheck();	
	return true;
}

bool CUser::WarpListObjectEvent(_OBJECT_EVENT *pEvent)
{
	if (pEvent->sBelong != 0 && pEvent->sBelong != GetNation()
			|| (GetZoneID() != GetNation() && GetZoneID() <= ELMORAD)
			|| !GetWarpList(pEvent->sControlNpcID)) 
			return false;

	return true;
}

void CUser::ObjectEvent(Packet & pkt)
{
	if (g_pMain->m_bPointCheckFlag == false
		|| isDead())
		return;

	bool bSuccess = false;
	uint16 objectindex, nid;
	pkt >> objectindex >> nid;

	_OBJECT_EVENT * pEvent = GetMap()->GetObjectEvent(objectindex);
	if (pEvent != nullptr
		&& isInRange(pEvent->fPosX, pEvent->fPosZ, MAX_OBJECT_RANGE))
	{
		switch (pEvent->sType)
		{
		case OBJECT_GATE:
		case OBJECT_BIND:
		case OBJECT_REMOVE_BIND:
			bSuccess = BindObjectEvent(pEvent);
			break;

		case OBJECT_GATE_LEVER:
			bSuccess = GateLeverObjectEvent(pEvent, nid);
			break;

		case OBJECT_FLAG_LEVER:
			bSuccess = FlagObjectEvent(pEvent, nid);
			break;

		case OBJECT_WARP_GATE:
			bSuccess = WarpListObjectEvent(pEvent);
			if (bSuccess)
				return;
			break;

		case OBJECT_ANVIL:
			SendAnvilRequest(nid);
			return;
		}

	}

	if (!bSuccess)
	{
		Packet result(WIZ_OBJECT_EVENT, uint8(pEvent == nullptr ? 0 : pEvent->sType));
		result << uint8(0);
		Send(&result);
	}
}

void CUser::SendAnvilRequest(uint16 sNpcID, uint8 bType /*= ITEM_UPGRADE_REQ*/)
{
	Packet result(WIZ_ITEM_UPGRADE, uint8(bType));
	result << sNpcID;
	Send(&result);
}

void CUser::UpdateVisibility(InvisibilityType bNewType)
{
	Packet result(AG_USER_VISIBILITY);
	m_bInvisibilityType = (uint8)(bNewType);
	result << GetID() << m_bInvisibilityType;
	Send_AIServer(&result);
}


void CUser::ResetGMVisibility()
{
	if (!isGM()
		|| isTransformed())
		return;

	if (m_bAbnormalType != ABNORMAL_INVISIBLE)
	{
		Packet result(WIZ_STATE_CHANGE);
		result << GetID() << uint8(5) << uint8(0);
		Send(&result);
	}

	m_bAbnormalType = ABNORMAL_INVISIBLE;
}

void CUser::BlinkStart()
{
	if (isGM()
		|| GetZoneID() == ZONE_ARDREAM
		|| GetZoneID() == ZONE_PVP_EVENT
		|| GetZoneID() == ZONE_RONARK_LAND
		|| GetZoneID() == ZONE_UNDER_THE_CASTLE
		|| GetZoneID() == ZONE_JURAD_MOUNTAIN
		|| GetZoneID() == ZONE_CHAOS_DUNGEON
		|| GetZoneID() == ZONE_BORDER_DEFENSE_WAR
		|| GetMap()->isWarZone()
		|| isMonsterTransformation()
		|| isNPCTransformation()
		|| isSiegeTransformation())
		return;

	m_bAbnormalType = ABNORMAL_BLINKING;
	m_tBlinkExpiryTime = UNIXTIME + BLINK_TIME;
	m_bRegeneType = REGENE_ZONECHANGE;

	UpdateVisibility(INVIS_DISPEL_ON_ATTACK); 
	m_bInvisibilityType = INVIS_NONE;

	StateChangeServerDirect(3, ABNORMAL_BLINKING);
}

void CUser::BlinkTimeCheck()
{
	if (UNIXTIME < m_tBlinkExpiryTime)
		return;

	m_bRegeneType = REGENE_NORMAL;

	m_bCanUseSkills = true;

	StateChangeServerDirect(3, ABNORMAL_NORMAL);

	Packet result(AG_USER_REGENE);
	result	<< GetSocketID() << m_sHp;
	Send_AIServer(&result);

	result.Initialize(AG_USER_INOUT);
	result.SByte();
	result	<< uint8(INOUT_RESPAWN) << GetSocketID()
		<< GetName()
		<< GetX() << GetZ();
	Send_AIServer(&result);

	UpdateVisibility(INVIS_NONE);
}

void CUser::GoldGain(uint32 gold, bool bSendPacket /*= true*/, bool bApplyBonus /*= false*/)
{
	if (bApplyBonus)
		gold = gold * (m_bNoahGainAmount + m_bItemNoahGainAmount) / 100;

	if (m_iGold + gold > COIN_MAX)
		m_iGold = COIN_MAX;
	else
		m_iGold += gold;

	if (bSendPacket)
	{
		Packet result(WIZ_GOLD_CHANGE, uint8(CoinGain));
		result << gold << GetCoins();
		Send(&result);	
	}
}

bool CUser::GoldLose(uint32 gold, bool bSendPacket /*= true*/)
{
	if (!hasCoins(gold)) 
		return false;

	m_iGold -= gold;

	if (bSendPacket)
	{
		Packet result(WIZ_GOLD_CHANGE, uint8(CoinLoss));
		result << gold << GetCoins();
		Send(&result);	
	}
	return true;
}

bool CUser::CheckSkillPoint(uint8 skillnum, uint8 min, uint8 max)
{
	if (skillnum < 5 || skillnum > 8) 
		return false;

	return (m_bstrSkill[skillnum] >= min && m_bstrSkill[skillnum] <= max);
}

bool CUser::CheckClass(short class1, short class2, short class3, short class4, short class5)
{
	return (JobGroupCheck(class1) || JobGroupCheck(class2) || JobGroupCheck(class3) || JobGroupCheck(class4) || JobGroupCheck(class5));
}

bool CUser::JobGroupCheck(short jobgroupid)
{
	if (jobgroupid > 100) 
		return GetClass() == jobgroupid;

	ClassType subClass = GetBaseClassType();
	switch (jobgroupid) 
	{
	case GROUP_WARRIOR:
		return (subClass == ClassWarrior || subClass == ClassWarriorNovice || subClass == ClassWarriorMaster);

	case GROUP_ROGUE:
		return (subClass == ClassRogue || subClass == ClassRogueNovice || subClass == ClassRogueMaster);

	case GROUP_MAGE:
		return (subClass == ClassMage || subClass == ClassMageNovice || subClass == ClassMageMaster);

	case GROUP_CLERIC:	
		return (subClass == ClassPriest || subClass == ClassPriestNovice || subClass == ClassPriestMaster);

	case GROUP_KURIAN_PORTU:
		return (subClass == ClassKurPor || subClass == ClassKurPorNovice || subClass == ClassKurPorMaster);

	}

	return (subClass == jobgroupid);
}

void CUser::TrapProcess()
{
	if ((UNIXTIME - m_tLastTrapAreaTime) >= ZONE_TRAP_INTERVAL)
	{
		if(GetZoneID() == ZONE_BIFROST)
			SendUserStatusUpdate(USER_STATUS_BLIND,USER_STATUS_INFLICT);

		HpChange(-ZONE_TRAP_DAMAGE, this);
		m_tLastTrapAreaTime = UNIXTIME;
	}
}

void CUser::KickOutZoneUser(bool home, uint8 nZoneID)
{
	if (home)
	{
		C3DMap* pMap = g_pMain->GetZoneByID(nZoneID);
		if (pMap == nullptr) 
			return;

		int eventID = 0;
		int random = myrand(0, 9000);
		if (random >= 0 && random < 3000)			eventID = 0;
		else if (random >= 3000 && random < 6000)	eventID = 1;
		else if (random >= 6000 && random < 9001)	eventID = 2;

		_REGENE_EVENT* pRegene = pMap->GetRegeneEvent(eventID);
		if (pRegene == nullptr) 
		{
			KickOutZoneUser();
			return;
		}

		ZoneChange(pMap->m_nZoneNumber, 
			pRegene->fRegenePosX + (float)myrand(0, (int)pRegene->fRegeneAreaX), 
			pRegene->fRegenePosZ + (float)myrand(0, (int)pRegene->fRegeneAreaZ));
		return;
	}

	short x, z;

	if (GetStartPosition(x,z,GetNation()))
		ZoneChange(GetNation(), x, z);
	else
	{
		TRACE("### KickOutZoneUser - StartPosition not found : Nation=%d",GetNation());
	}
}

void CUser::NativeZoneReturn()
{
	_START_POSITION *pStartPosition = g_pMain->m_StartPositionArray.GetData(m_bNation);
	if (pStartPosition == nullptr) 
		return; 

	m_bZone = m_bNation;

	m_curx = (float)((m_bNation == KARUS ? pStartPosition->sKarusX : pStartPosition->sElmoradX) + myrand(0, pStartPosition->bRangeX));
	m_curz = (float)((m_bNation == KARUS ? pStartPosition->sKarusZ : pStartPosition->sElmoradZ) + myrand(0, pStartPosition->bRangeZ)); 
}

void CUser::SendToRegion(Packet *pkt, CUser *pExceptUser /*= nullptr*/, uint16 nEventRoom /*-1*/)
{
	g_pMain->Send_Region(pkt, GetMap(), GetRegionX(), GetRegionZ(), pExceptUser, nEventRoom);
}

void CUser::SendToZone(Packet *pkt, CUser *pExceptUser /*= nullptr*/, uint16 nEventRoom /*-1*/, float fRange)
{
	g_pMain->Send_Zone(pkt, GetZoneID(), pExceptUser, 0, nEventRoom, fRange);
}

void CUser::OnDeath(Unit *pKiller)
{
	if (m_bResHpType == USER_DEAD)
		return;

	m_bResHpType = USER_DEAD;

	ResetWindows();

	if (GetFame() == COMMAND_CAPTAIN)
	{
		if (GetNation() == KARUS)
			g_pMain->Announcement(KARUS_CAPTAIN_DEPRIVE_NOTIFY, KARUS, 8, this);
		else
			g_pMain->Announcement(ELMORAD_CAPTAIN_DEPRIVE_NOTIFY, ELMORAD, 8, this);
	}

	InitType3();
	InitType4();

	DateTime time;

	if (pKiller != nullptr)
	{
		DeathNoticeType noticeType = DeathNoticeNone;

		if (pKiller->isNPC())
		{
			CNpc *pNpc = TO_NPC(pKiller);

			AchieveMainCount(0, 20, 0, 0, true);
			AchieveMainCount(1, 0, 0, 0, true);
			
			int64 nExpLost = 0;
			if (pNpc->GetType() == NPC_PATROL_GUARD || (GetZoneID() != GetNation() && GetZoneID() <= ELMORAD))
				nExpLost = m_iMaxExp / 100;
			else
				nExpLost = m_iMaxExp / 20;

			if ((pNpc->GetType() == NPC_GUARD_TOWER1 || pNpc->GetType() == NPC_GUARD_TOWER2) && isInPKZone())
				noticeType = DeathNotice;

			if (GetPremiumProperty(PremiumExpRestorePercent) > 0)
				nExpLost = nExpLost * (GetPremiumProperty(PremiumExpRestorePercent)) / 100;

			g_pMain->WriteDeathUserLogFile(string_format("[ NPC/MONSTER - %d:%d:%d ] SID=%d,Killer=%s,Target=%s,Zone=%d,X=%d,Z=%d,TargetExp=%d,LostExp=%d\n",time.GetHour(),time.GetMinute(),time.GetSecond(),pNpc->GetProtoID(),pKiller->GetName().c_str(),GetName().c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ()),m_iExp, nExpLost));
			
			if (GetZoneID() != ZONE_FORGOTTEN_TEMPLE)
				ExpChange(-nExpLost);		

			if (GetZoneID() == ZONE_FORGOTTEN_TEMPLE)
			{
				KickOutZoneUser(true);
				return;
			}
		}
		else
		{
			CUser *pUser = TO_USER(pKiller);

			if (!pUser->isInArena()) 
			{
				pUser->AchieveUpdateKills(0);
				pUser->UserDefeatCount++;
				UserDeathCount++;
			}

			if (pUser == this)
			{
				m_sWhoKilledMe = -1;
			}
			else
			{
				if (GetZoneID() == ZONE_CHAOS_DUNGEON)
				{
					noticeType = DeathNoticeCoordinates;
					RobChaosSkillItems();
					m_DeathCount++;
					UpdatePlayerRank();

					pUser->m_KillCount++;
					pUser->UpdatePlayerRank();
				}
				else if (GetZoneID() == ZONE_BORDER_DEFENSE_WAR || GetZoneID() == ZONE_JURAD_MOUNTAIN)
				{
					Packet result(WIZ_EVENT, uint8(TEMPLE_EVENT_BORDER_COUNTER));
					noticeType = DeathNoticeCoordinates;

					GetNation() == KARUS ? g_pMain->pTempleEvent.KarusDeathCount[GetEventRoom()]++ : g_pMain->pTempleEvent.ElmoDeathCount[GetEventRoom()]++;
					 
					if (!pUser->isInParty())
						pUser->LoyaltyChange(GetID());
					else
						pUser->LoyaltyDivide(GetID());

					pUser->m_iLoyaltyDaily++;
					pUser->UpdatePlayerRank();
					result << g_pMain->pTempleEvent.ElmoDeathCount[GetEventRoom()] << uint16(0x00) << g_pMain->pTempleEvent.KarusDeathCount[GetEventRoom()] << uint16(0x00);
					g_pMain->Send_Zone(&result, GetZoneID(), this, Nation::ALL,GetEventRoom());

					if (g_pMain->pTempleEvent.ElmoDeathCount[GetEventRoom()] > 59 || g_pMain->pTempleEvent.KarusDeathCount[GetEventRoom()] > 59)
						g_pMain->TempleEventFinish();
				}
				else
				{
					if (GetZoneID() == ZONE_SNOW_BATTLE
						&& g_pMain->m_byBattleOpen == SNOW_BATTLE)
					{
						pUser->GoldGain(SNOW_EVENT_MONEY);

						if (!pUser->isInParty())
							pUser->LoyaltyChange(GetID());
						else
							pUser->LoyaltyChange(GetID());

						if (GetNation() == KARUS)
							g_pMain->m_sKarusDead++;
						else
							g_pMain->m_sElmoradDead++;
					}
					else if (GetZoneID() == ZONE_DELOS
						&& g_pMain->m_byBattleOpen == CLAN_BATTLE)
					{
						noticeType = DeathNotice;
						if (!pUser->isInParty())
							pUser->LoyaltyChange(GetID());
						else
							pUser->LoyaltyChange(GetID());
					}
					else
					{
						if (isInArena())
						{
							noticeType = DeathNoticeCoordinates;
						}
						else
						{
							uint16 bonusNP = 0;
							bool bKilledByRival = false;

							if (!GetMap()->isWarZone() && g_pMain->m_byBattleOpen != NATION_BATTLE)
							{
								noticeType = DeathNoticeCoordinates;

								bKilledByRival = (!pUser->hasRivalryExpired() && pUser->GetRivalID() == GetID());
								if (bKilledByRival)
								{
									noticeType = DeathNoticeRival;

									if (GetZoneID() == ZONE_PVP_EVENT)
										bonusNP += MINIRIVALRY_NP_BONUS;
									else
										bonusNP += RIVALRY_NP_BONUS;

									pUser->RemoveRival();
									AchieveMainCount(0, 3, 0, 0);

								}

								if (!hasFullAngerGauge())
									UpdateAngerGauge(++m_byAngerGauge);

							}

							if (!pUser->isInParty())
								pUser->LoyaltyChange(GetID(), bonusNP);
							else
								pUser->LoyaltyDivide(GetID(), bonusNP);

							if (GetZoneID() != GetNation() && GetZoneID() <= ELMORAD)
							{
								int64 nExpLost = m_iMaxExp / 100;

								if (GetPremiumProperty(PremiumExpRestorePercent) > 0)
									nExpLost = nExpLost * (GetPremiumProperty(PremiumExpRestorePercent)) / 100;

								ExpChange(-nExpLost);
							}

							if (isInPKZone()
								&& !hasRival())
								SetRival(pUser);

							if (GetNation() == KARUS && !pUser->isInParty())
								pUser->QuestV3MainCount(KARUS);
							else if(GetNation() == ELMORAD && !pUser->isInParty())
								pUser->QuestV3MainCount(ELMORAD);

							if (pUser->isInParty() && (GetNation() == KARUS || GetNation() == ELMORAD))
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

											if (GetNation() == KARUS)
												pUserParty->QuestV3MainCount(KARUS);
											else if (GetNation() == ELMORAD)
												pUserParty->QuestV3MainCount(ELMORAD);
										}
									}
								}
							}
						}
					}
				}

				m_sWhoKilledMe = pUser->GetID();
			}

			string pKillerPartyUsers;
			string pTargetPartyUsers;

			if (GetZoneID() != ZONE_CHAOS_DUNGEON && (pUser->isInParty() || isInParty()))
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

				pParty = g_pMain->GetPartyPtr(GetPartyID());
				if (pParty)
				{
					for (int i = 0; i < MAX_PARTY_USERS; i++)
					{
						pPartyUser = g_pMain->GetUserPtr(pParty->uid[i]);
						if (pPartyUser)
							pTargetPartyUsers += string_format("%s,",pPartyUser->GetName().c_str());
					}
				}

				if (!pKillerPartyUsers.empty())
					pKillerPartyUsers = pKillerPartyUsers.substr(0,pKillerPartyUsers.length() - 1);

				if (!pTargetPartyUsers.empty())
					pTargetPartyUsers = pTargetPartyUsers.substr(0,pTargetPartyUsers.length() - 1);
			}

			if (pKillerPartyUsers.empty() && pTargetPartyUsers.empty())
				g_pMain->WriteDeathUserLogFile(string_format("[ USER - %d:%d:%d ] Killer=%s,Target=%s,Zone=%d,X=%d,Z=%d,LoyaltyKiller=%d,LoyaltyMonthlyKiller=%d,LoyaltyTarget=%d,LoyaltyMonthlyTarget=%d\n",time.GetHour(),time.GetMinute(),time.GetSecond(),pKiller->GetName().c_str(),GetName().c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ()),TO_USER(pKiller)->GetLoyalty(),TO_USER(pKiller)->GetMonthlyLoyalty(),GetLoyalty(),GetMonthlyLoyalty()));
			else if (pKillerPartyUsers.empty() && !pTargetPartyUsers.empty())
				g_pMain->WriteDeathUserLogFile(string_format("[ USER - %d:%d:%d ] Killer=%s,Target=%s,TargetParty=%s,Zone=%d,X=%d,Z=%d,LoyaltyKiller=%d,LoyaltyMonthlyKiller=%d,LoyaltyTarget=%d,LoyaltyMonthlyTarget=%d\n",time.GetHour(),time.GetMinute(),time.GetSecond(),pKiller->GetName().c_str(),GetName().c_str(), pTargetPartyUsers.c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ()),TO_USER(pKiller)->GetLoyalty(),TO_USER(pKiller)->GetMonthlyLoyalty(),GetLoyalty(),GetMonthlyLoyalty()));
			else if (!pKillerPartyUsers.empty() && pTargetPartyUsers.empty())
				g_pMain->WriteDeathUserLogFile(string_format("[ USER - %d:%d:%d ] Killer=%s,KillerParty=%s,Target=%s,Zone=%d,X=%d,Z=%d,LoyaltyKiller=%d,LoyaltyMonthlyKiller=%d,LoyaltyTarget=%d,LoyaltyMonthlyTarget=%d\n",time.GetHour(),time.GetMinute(),time.GetSecond(),pKiller->GetName().c_str(),pKillerPartyUsers.c_str(),GetName().c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ()),TO_USER(pKiller)->GetLoyalty(),TO_USER(pKiller)->GetMonthlyLoyalty(),GetLoyalty(),GetMonthlyLoyalty()));
			else if (!pKillerPartyUsers.empty() && !pTargetPartyUsers.empty())
				g_pMain->WriteDeathUserLogFile(string_format("[ USER - %d:%d:%d ] Killer=%s,KillerParty=%s,Target=%s,TargetParty=%s,Zone=%d,X=%d,Z=%d,LoyaltyKiller=%d,LoyaltyMonthlyKiller=%d,LoyaltyTarget=%d,LoyaltyMonthlyTarget=%d\n",time.GetHour(),time.GetMinute(),time.GetSecond(),pKiller->GetName().c_str(),pKillerPartyUsers.c_str(),GetName().c_str(), pTargetPartyUsers.c_str(),GetZoneID(),uint16(GetX()),uint16(GetZ()),TO_USER(pKiller)->GetLoyalty(),TO_USER(pKiller)->GetMonthlyLoyalty(),GetLoyalty(),GetMonthlyLoyalty()));
		}

		if (noticeType != DeathNoticeNone)
			SendDeathNotice(pKiller,noticeType); 
	}

	Unit::OnDeath(pKiller);
}

void CUser::UpdateAngerGauge(uint8 byAngerGauge)
{
	Packet result(WIZ_PVP, uint8(byAngerGauge == 0 ? PVPResetHelmet : PVPUpdateHelmet));

	if (byAngerGauge > MAX_ANGER_GAUGE)
		byAngerGauge = MAX_ANGER_GAUGE;

	m_byAngerGauge = byAngerGauge;
	if (byAngerGauge > 0)
		result << uint8(byAngerGauge) << hasFullAngerGauge();

	Send(&result);
}

void CUser::SendClanUserStatusUpdate(bool bToRegion /*= true*/)
{
	Packet result(WIZ_KNIGHTS_PROCESS, uint8(KNIGHTS_MODIFY_FAME));
	result	<< uint8(1) << GetSocketID() 
		<< GetClanID() << GetFame();

	if (bToRegion)
		SendToRegion(&result);
	else
		Send(&result);
}

void CUser::SendPartyStatusUpdate(uint8 bStatus, uint8 bResult /*= 0*/)
{
	if (!isInParty())
		return;

	Packet result(WIZ_PARTY, uint8(PARTY_STATUSCHANGE));
	result << GetSocketID() << bStatus << bResult;
	g_pMain->Send_PartyMember(GetPartyID(), &result);
}

void CUser::HandleHelmet(Packet & pkt)
{
	 if (isDead())
	  return;

	 Packet result(WIZ_HELMET);
	 pkt >> m_bIsHidingHelmet;
	 pkt >> m_bIsHidingCospre;
	 result << m_bIsHidingHelmet;
	 result << m_bIsHidingCospre;
	 result<< uint32(GetSocketID());
	 SendToRegion(&result);
}

bool Unit::isInAttackRange(Unit * pTarget, _MAGIC_TABLE * pSkill /*= nullptr*/)
{
	if (pTarget == nullptr)
		return false;

	if (pTarget == this
		|| !isPlayer())
		return true;

	const float fBaseMeleeRange		= 15.0f;
	const float fBaseRangedRange	= 65.0f;

	float fRange = fBaseMeleeRange, fWeaponRange = 0.0f;

	_ITEM_DATA * pItem = nullptr;
	_ITEM_TABLE * pTable = TO_USER(this)->GetItemPrototype(RIGHTHAND, pItem);

	if (pTable != nullptr
		&& pItem->sDuration > 0)
	{
		fWeaponRange = pTable->m_sRange;
	}
	else
	{
		pTable = TO_USER(this)->GetItemPrototype(LEFTHAND, pItem);
		if (pTable != nullptr
			&& pItem->sDuration != 0)
			fWeaponRange = pTable->m_sRange;
	}

	if (pSkill != nullptr)
	{
		if (pSkill->bMoral != MORAL_ENEMY && pSkill->bMoral > MORAL_PARTY)
			return true;

		if (pSkill->bType[0] != 3)
			fRange = fWeaponRange;

		if (pSkill->bType[0] != 2)
		{
			return isInRangeSlow(pTarget, fBaseMeleeRange + (pSkill->sRange == 0 ? fRange : pSkill->sRange) + (pSkill->bType[0] == 1 ? fWeaponRange : 0)); 
		}
		else
		{
			_MAGIC_TYPE2 * pType2 = g_pMain->m_Magictype2Array.GetData(pSkill->iNum);
			return pType2 != nullptr && isInRangeSlow(pTarget, fRange + pType2->sAddRange + fBaseRangedRange);
		}
	}

	if (fWeaponRange != 0.0f)
		fRange = fBaseMeleeRange + fWeaponRange;

	return isInRangeSlow(pTarget, fRange);
}

bool CUser::CanUseItem(uint32 nItemID, uint16 sCount /*= 1*/)
{
	_ITEM_TABLE* pItem = pItem = g_pMain->GetItemPtr(nItemID);
	if (pItem == nullptr)
		return false;

	if (isTransformed())
	{
		if (isNPCTransformation() && isSiegeTransformation())
			return false;
	}

	if ((pItem->m_bClass != 0 && !JobGroupCheck(pItem->m_bClass))
			|| (GetLevel() < pItem->m_bReqLevel || GetLevel() > pItem->m_bReqLevelMax)
			|| !CheckExistItem(nItemID, sCount))
			return false;

	return true;
}

void CUser::SendUserStatusUpdate(UserStatus type, UserStatusBehaviour status)
{
	Packet result(WIZ_ZONEABILITY, uint8(2));
	result << uint8(type) << uint8(status);
	Send(&result);

	if (isInParty())
		SendPartyStatusUpdate(type, status);
}

_ITEM_TABLE* CUser::GetItemPrototype(uint8 pos, _ITEM_DATA *& pItem)
{
	if (pos >= INVENTORY_TOTAL)
		return nullptr;

	pItem = GetItem(pos);
	return pItem->nNum == 0 ? nullptr : g_pMain->GetItemPtr(pItem->nNum);
}

void CUser::CheckSavedMagic()
{
	Guard lock(m_savedMagicLock);
	if (m_savedMagicMap.empty())
		return;

	set<uint32> deleteSet;
	foreach (itr, m_savedMagicMap)
	{
		if (itr->second <= UNIXTIME)
			deleteSet.insert(itr->first);
	}
	foreach (itr, deleteSet)
		m_savedMagicMap.erase(*itr);
}


void CUser::InsertSavedMagic(uint32 nSkillID, uint16 sDuration)
{
	Guard lock(m_savedMagicLock);
	UserSavedMagicMap::iterator itr = m_savedMagicMap.find(nSkillID);

	if (itr != m_savedMagicMap.end())
		return;

	m_savedMagicMap.insert(make_pair(nSkillID, UNIXTIME + sDuration));
}


void CUser::RemoveSavedMagic(uint32 nSkillID)
{
	Guard lock(m_savedMagicLock);
	m_savedMagicMap.erase(nSkillID);
}


bool CUser::HasSavedMagic(uint32 nSkillID)
{
	Guard lock(m_savedMagicLock);
	return m_savedMagicMap.find(nSkillID) != m_savedMagicMap.end();
}


int16 CUser::GetSavedMagicDuration(uint32 nSkillID)
{
	Guard lock(m_savedMagicLock);
	auto itr = m_savedMagicMap.find(nSkillID);
	if (itr == m_savedMagicMap.end())
		return 0;

	return int16(itr->second - UNIXTIME);
}


void CUser::RecastSavedMagic(uint8 buffType /* = 0*/)
{
	Guard lock(m_savedMagicLock);
	UserSavedMagicMap castSet;
	foreach (itr, m_savedMagicMap)
	{
		if (itr->first != 0 || itr->second != 0) 
			castSet.insert(make_pair(itr->first, itr->second));
	}

	if (castSet.empty())
		return;

	foreach (itr, castSet)
	{
		if (buffType > 0)
		{
			_MAGIC_TYPE4 * pType = g_pMain->m_Magictype4Array.GetData(itr->first);

			if (pType == nullptr)
				continue;

			if (pType->bBuffType != buffType)
				continue;
		}

		MagicInstance instance;
		instance.sCasterID = GetID();
		instance.sTargetID = GetID();
		instance.nSkillID = itr->first;
		instance.bIsRecastingSavedMagic = true;

		instance.Run();
	}
}


void CUser::RecastLockableScrolls(uint8 buffType)
{
	InitType4(false, buffType);
	RecastSavedMagic(buffType);
}


void CUser::HandlePlayerRankings(Packet & pkt)
{
	if (g_pMain->m_IsPlayerRankingUpdateProcess)
		return;

	uint8 nRankType = 0;
	pkt >> nRankType;

	Packet result(WIZ_RANK, nRankType);

	uint16 nMyRank = 0;
	uint16 sCount = 0;
	size_t wpos = 0;

	std::vector<_USER_RANKING> UserRankingSorted[NONE];

	for (int nation = KARUS_ARRAY; nation <= ELMORAD_ARRAY; nation++)
	{
		foreach_stlmap (itr, g_pMain->m_UserRankingArray[nation])
			UserRankingSorted[nRankType == RANK_TYPE_CHAOS_DUNGEON ? NONE - 1 : nation].push_back(*itr->second);

		if (nRankType == RANK_TYPE_PK_ZONE
			|| nRankType == RANK_TYPE_ZONE_BORDER_DEFENSE_WAR)
		{
			sCount = 0;
			wpos = result.wpos();
			result << sCount;

			std::sort(UserRankingSorted[nation].begin(), UserRankingSorted[nation].end(),
				[] (_USER_RANKING const &a, _USER_RANKING const &b ){ return a.m_iLoyaltyDaily > b.m_iLoyaltyDaily; });

			if ((uint32)UserRankingSorted[nation].size() > 0)
			{
				if ((nation + 1) == GetNation())
				{
					for (int i = 0; i < (int32)UserRankingSorted[nation].size(); i++)
					{
						if (GetZoneID() != UserRankingSorted[nation][i].m_bZone)
							continue;

						nMyRank++;

						if (UserRankingSorted[nation][i].m_socketID == GetSocketID())
							break;
					}
				}

				for (int i = 0; i < (int32)UserRankingSorted[nation].size(); i++)
				{
					if ((nRankType == RANK_TYPE_PK_ZONE && sCount > 9) 
						|| (nRankType == RANK_TYPE_ZONE_BORDER_DEFENSE_WAR && sCount > 7))
						break;

					_USER_RANKING * pRankInfo = &UserRankingSorted[nation][i];

					if (pRankInfo == nullptr)
						continue;

					if (GetZoneID() == pRankInfo->m_bZone 
						&& GetEventRoom() == pRankInfo->m_bEventRoom)
					{
						CUser *pUser = g_pMain->GetUserPtr(pRankInfo->m_socketID);

						if (pUser == nullptr)
							continue;

						if (!pUser->isInGame())
							continue;

						result << pUser->GetName() << true;

						CKnights * pKnights = g_pMain->GetClanPtr(pUser->GetClanID());

						if (pKnights == nullptr)
							result	<< uint16(0) << uint16(0) << (std::string)"";
						else
							result	<< pKnights->GetID() << pKnights->m_sMarkVersion << pKnights->GetName();

						result << pRankInfo->m_iLoyaltyDaily;

						if(nRankType == RANK_TYPE_PK_ZONE)
							result << pRankInfo->m_iLoyaltyPremiumBonus;

						sCount++;
					}
				}
			}

			result.put(wpos, sCount);
			wpos = result.wpos();
		}
	}

	if (nRankType == RANK_TYPE_CHAOS_DUNGEON && (uint32)UserRankingSorted[NONE-1].size() > 0)
	{
		std::sort(UserRankingSorted[NONE-1].begin(), UserRankingSorted[NONE-1].end(),
			[]( _USER_RANKING const &a, _USER_RANKING const &b ){ return a.m_KillCount > b.m_KillCount; });

		result << uint8(g_pMain->TempleEventGetRoomUsers(GetEventRoom()));

		for (int i = 0; i < (int32)UserRankingSorted[NONE-1].size(); i++)
		{
			_USER_RANKING * pRankInfo = &UserRankingSorted[NONE-1][i];

			if (pRankInfo == nullptr)
				continue;

			if (GetSocketID() == pRankInfo->m_socketID)
				continue;

			if (GetZoneID() == pRankInfo->m_bZone 
				&& GetEventRoom() == pRankInfo->m_bEventRoom)
			{
				CUser *pUser = g_pMain->GetUserPtr(pRankInfo->m_socketID);

				if (pUser == nullptr)
					continue;

				if (!pUser->isInGame())
					continue;

				result << pUser->GetName()
					<< pRankInfo->m_KillCount << pRankInfo->m_DeathCount;
			}
		}
	}

	if (nRankType == RANK_TYPE_PK_ZONE)
		result  << nMyRank << m_iLoyaltyDaily << m_iLoyaltyPremiumBonus;
	else if (nRankType == RANK_TYPE_ZONE_BORDER_DEFENSE_WAR)
		result << int32(100000) << int32(50000);
	else if (nRankType == RANK_TYPE_CHAOS_DUNGEON)
	{
		int64 nGainedExp = int64(pow(GetLevel(),3) * 0.15 * (5 * m_KillCount - m_DeathCount));
		int64 nPremiumGainedExp = nGainedExp * 2;

		if (nGainedExp > 8000000)
			nGainedExp = 8000000;

		if (nPremiumGainedExp > 8000000)
			nPremiumGainedExp = 8000000;

		result << GetName()
			<< m_KillCount << m_DeathCount
			<< nGainedExp << nPremiumGainedExp;
	}

	Send(&result);
}

uint16 CUser::GetPlayerRank(uint8 nRankType)
{
	uint16 nMyRank = 0;
	uint8 nRankArrayIndex = (nRankType == RANK_TYPE_PK_ZONE 
		|| nRankType == RANK_TYPE_ZONE_BORDER_DEFENSE_WAR 
		? GetNation() -1
		:  NONE-1);

	std::vector<_USER_RANKING> UserRankingSorted[NONE];

	for (int nation = KARUS_ARRAY; nation <= ELMORAD_ARRAY; nation++)
	{
		foreach_stlmap (itr, g_pMain->m_UserRankingArray[nation])
			UserRankingSorted[nRankType == RANK_TYPE_CHAOS_DUNGEON ? NONE -1 : nation].push_back(*itr->second);
	}

	if (nRankArrayIndex < ELMORAD)
	{
		std::sort(UserRankingSorted[nRankArrayIndex].begin(), UserRankingSorted[nRankArrayIndex].end(),
			[] (_USER_RANKING const &a, _USER_RANKING const &b ){ return a.m_iLoyaltyDaily > b.m_iLoyaltyDaily; });
	}
	else if (nRankArrayIndex == ELMORAD)
	{
		std::sort(UserRankingSorted[nRankArrayIndex].begin(), UserRankingSorted[nRankArrayIndex].end(),
			[]( _USER_RANKING const &a, _USER_RANKING const &b ){ return a.m_KillCount > b.m_KillCount; });
	}

	for (int i = 0; i < (int32)UserRankingSorted[nRankArrayIndex].size(); i++)
	{
		_USER_RANKING * pRankInfo = &UserRankingSorted[nRankArrayIndex][i];

		if (pRankInfo)
		{
			if  (GetZoneID() == pRankInfo->m_bZone
				&& GetEventRoom() == pRankInfo->m_bEventRoom)
			{

				nMyRank++;

				if (GetSocketID() == pRankInfo->m_socketID)
					break;
			}
		}
	}

	return nMyRank;
}

void CUser::InitializeStealth()
{
	Packet pkt(WIZ_STEALTH);
	pkt << uint8(0) << uint16(0);
	Send(&pkt);
}

void CUser::GrantChickenManner()
{
	uint8 bLevel = GetLevel(), bManner = 0;
	if (!m_bIsChicken || !isInParty())
		return;

	_PARTY_GROUP *pParty = nullptr;
	pParty = g_pMain->GetPartyPtr(GetPartyID());

	if(pParty == nullptr)
		return;

	for (int i = 0; i < MAX_PARTY_USERS; i++)
	{
		CUser *pTargetUser = nullptr;
		if (pParty->uid[i] != GetSocketID())
			pTargetUser = g_pMain->GetUserPtr(pParty->uid[i]);

		if (pTargetUser == nullptr 
			|| pTargetUser->isDead() 
			|| pTargetUser->m_bIsChicken)
			continue;

		if (!isInRange(pTargetUser, RANGE_50M))
			continue;

		if (pTargetUser->GetLevel() > 20 && pTargetUser->GetLevel() < 40)
			bManner = pTargetUser->GetLevel() / 10;
		else
			bManner = 1;

		pTargetUser->SendMannerChange(bManner);
	}
}

void CUser::SendMannerChange(int32 iMannerPoints)
{
	if(m_iMannerPoint + iMannerPoints > LOYALTY_MAX)
		m_iMannerPoint = LOYALTY_MAX;
	else if (m_iMannerPoint + iMannerPoints < 0)
		m_iMannerPoint = 0;
	else
		m_iMannerPoint += iMannerPoints;

	Packet pkt(WIZ_LOYALTY_CHANGE, uint8(MANNER_POINTS));
	pkt << m_iMannerPoint;
	Send(&pkt);
}

uint8 CUser::GetUserDailyOp(uint8 type)
{
	if (type == 0)
		return 0;

	int32 nUnixTime = -1;

	UserDailyOpMap::iterator itr = g_pMain->m_UserDailyOpMap.find(GetName());

	if (itr != g_pMain->m_UserDailyOpMap.end())
	{
		if (type == DAILY_CHAOS_MAP)
			nUnixTime = int(itr->second->ChaosMapTime);
		else if (type == DAILY_USER_RANK_REWARD)
			nUnixTime = int(itr->second->UserRankRewardTime);
		else if (type == DAILY_USER_PERSONAL_RANK_REWARD)
			nUnixTime = int(itr->second->PersonalRankRewardTime);
		else if (type == DAILY_KING_WING)
			nUnixTime = int(itr->second->KingWingTime);
		else if (type == DAILY_WARDER_KILLER_WING1)
			nUnixTime = int(itr->second->WarderKillerTime1);
		else if (type == DAILY_WARDER_KILLER_WING2)
			nUnixTime = int(itr->second->WarderKillerTime2);
		else if (type == DAILY_KEEPER_KILLER_WING)
			nUnixTime = int(itr->second->KeeperKillerTime);
		else if (type == DAILY_USER_LOYALTY_WING_REWARD)
			nUnixTime = int(itr->second->UserLoyaltyWingRewardTime);

		if (nUnixTime == -1)
			SetUserDailyOp(type);
		else
		{
			if (((int32(UNIXTIME) - nUnixTime) / 60) > DAILY_OPERATIONS_MINUTE)
				SetUserDailyOp(type);
			else
				return 0;
		}
	}
	else
		SetUserDailyOp(type, true);

	return 1;
}

void CUser::SetUserDailyOp(uint8 type, bool isInsert)
{
	if (type == 0)
		return;

	int32 nUnixTime = int32(UNIXTIME);

	if (isInsert)
	{
		_USER_DAILY_OP * pData = new _USER_DAILY_OP;

		pData->strUserId = GetName();
		pData->ChaosMapTime = -1;
		pData->UserRankRewardTime = -1;
		pData->PersonalRankRewardTime = -1;
		pData->KingWingTime = -1;
		pData->WarderKillerTime1 = -1;
		pData->WarderKillerTime2 = -1;
		pData->KeeperKillerTime = -1;
		pData->UserLoyaltyWingRewardTime = -1;

		if (type ==  DAILY_CHAOS_MAP)
			pData->ChaosMapTime = nUnixTime;
		else if (type == DAILY_USER_RANK_REWARD)
			pData->UserRankRewardTime = nUnixTime;
		else if (type == DAILY_USER_PERSONAL_RANK_REWARD)
			pData->PersonalRankRewardTime = nUnixTime;
		else if (type == DAILY_KING_WING)
			pData->KingWingTime = nUnixTime;
		else if (type == DAILY_WARDER_KILLER_WING1)
			pData->WarderKillerTime1 = nUnixTime;
		else if (type == DAILY_WARDER_KILLER_WING2)
			pData->WarderKillerTime2 = nUnixTime;
		else if (type == DAILY_KEEPER_KILLER_WING)
			pData->KeeperKillerTime = nUnixTime;
		else if (type == DAILY_USER_LOYALTY_WING_REWARD)
			pData->UserLoyaltyWingRewardTime = nUnixTime;

		g_pMain->m_UserDailyOpMap.insert(make_pair(pData->strUserId, pData));
		g_DBAgent.InsertUserDailyOp(pData);
	}
	else
	{
		UserDailyOpMap::iterator itr = g_pMain->m_UserDailyOpMap.find(GetName());
		if (itr != g_pMain->m_UserDailyOpMap.end())
		{
			if (type == DAILY_CHAOS_MAP)
				itr->second->ChaosMapTime = nUnixTime;
			else if (type == DAILY_USER_RANK_REWARD)
				itr->second->UserRankRewardTime = nUnixTime;
			else if (type == DAILY_USER_PERSONAL_RANK_REWARD)
				itr->second->PersonalRankRewardTime = nUnixTime;
			else if (type == DAILY_KING_WING)
				itr->second->KingWingTime = nUnixTime;
			else if (type == DAILY_WARDER_KILLER_WING1)
				itr->second->WarderKillerTime1 = nUnixTime;
			else if (type == DAILY_WARDER_KILLER_WING2)
				itr->second->WarderKillerTime2 = nUnixTime;
			else if (type == DAILY_KEEPER_KILLER_WING)
				itr->second->KeeperKillerTime = nUnixTime;
			else if (type == DAILY_USER_LOYALTY_WING_REWARD)
				itr->second->UserLoyaltyWingRewardTime = nUnixTime;

			g_DBAgent.UpdateUserDailyOp(GetName(), type, nUnixTime);
		}
	}
}

uint32 CUser::GetEventTrigger()
{
	CNpc *pNpc = g_pMain->GetNpcPtr(GetTargetID());
	if (pNpc == nullptr)
		return 0;

	foreach_stlmap (itr, g_pMain->m_EventTriggerArray) {
		_EVENT_TRIGGER *pEventTrigger = g_pMain->m_EventTriggerArray.GetData(itr->first);

		if (pEventTrigger == nullptr)
			continue;

		if (pNpc->m_tNpcType != pEventTrigger->bNpcType)
			continue;

		if (pNpc->m_byTrapNumber == pEventTrigger->sNpcID)
			return pEventTrigger->nTriggerNum;
	}

	return 0;
}

void CUser::RemoveStealth()
{
	if (this->m_bInvisibilityType != INVIS_NONE)
	{
		CMagicProcess::RemoveStealth(this, INVIS_DISPEL_ON_MOVE);
		CMagicProcess::RemoveStealth(this, INVIS_DISPEL_ON_ATTACK);
	}
}

void CUser::GivePremium(uint8 bPremiumType, uint16 sPremiumTime)
{
	uint32 pTimeResult = 0;
	uint8 restcount = 0;
	uint8 initcount = 0;
	if(bPremiumType!=11 && bPremiumType!=12 && bPremiumType!=13 &&bPremiumType!=10)
		return;
	if(bPremiumType <= 0 
		|| bPremiumType > 13
		|| sPremiumTime <= 0
		|| m_bPremiumCount > PREMIUM_TOTAL)
		return;
	if (bPremiumType == 13 && m_bPremiumCount > 3)
		return;

	for (int i = 0; i < PREMIUM_TOTAL; i++)
	{
		_PREMIUM_DATA * uPrem = GetPremiumPtr(i);

		if (bPremiumType == 13 && uPrem->pType == 10 || uPrem->pType == 11 || uPrem->pType == 12)
			return;
		else if(bPremiumType < 13 && bPremiumType == m_bPremiumInUse)
			return;
	}

	pTimeResult = uint32(UNIXTIME+24*60*60*sPremiumTime);

	if (bPremiumType < 13)
	{
		restcount = 1;
		m_bPremiumInUse = bPremiumType;
		m_bPremiumCount += 1;
	}
	else if (bPremiumType == 13)
	{
		restcount = 3;
		bPremiumType = 10;
		m_bPremiumInUse = 10;
		m_bPremiumCount += 3;
	}

	for (int i = 0; i < PREMIUM_TOTAL; i++)
	{
		_PREMIUM_DATA * uPrem = GetPremiumPtr(i);
		initcount++;

		if (uPrem->pType != 0)
			continue;

		if (restcount <= 0)
			continue;

		uPrem->pType = bPremiumType++;
		uPrem->pTime = pTimeResult;
		restcount--;
	}

	m_bAccountStatus = 1;
	g_DBAgent.SavePremiumServiceUser(this);
	SendPremiumInfo();
}

void CUser::RobChaosSkillItems()
{
	if (GetItemCount(ITEM_LIGHT_PIT) > 0)
		RobItem(ITEM_LIGHT_PIT, GetItemCount(ITEM_LIGHT_PIT));
	if (GetItemCount(ITEM_DRAIN_RESTORE) > 0)
		RobItem(ITEM_DRAIN_RESTORE, GetItemCount(ITEM_DRAIN_RESTORE));
	if (GetItemCount(ITEM_KILLING_BLADE) > 0)
		RobItem(ITEM_KILLING_BLADE, GetItemCount(ITEM_KILLING_BLADE));
}

void CUser::SiegeWarFareNpc(Packet & pkt)
{
		uint8 opcode , type ;
		uint16 tarrif;
		pkt >> opcode >> type >> tarrif;
		_KNIGHTS_SIEGE_WARFARE *pKnightSiegeWarFare = g_pMain->GetSiegeMasterKnightsPtr(1);
		CKnights *pKnight = g_pMain->GetClanPtr(pKnightSiegeWarFare->sMasterKnights);
			
		Packet result(WIZ_SIEGE);
		switch (opcode)
		{
		case 3:
			{
				result << opcode << type;
					switch (type)
				{
					case 2:
						result << pKnightSiegeWarFare->sCastleIndex 
						<< uint16(pKnightSiegeWarFare->bySiegeType)
						<< pKnightSiegeWarFare->byWarDay
						<< pKnightSiegeWarFare->byWarTime 
						<< pKnightSiegeWarFare->byWarMinute;
						Send(&result);
						break;

					case 4:
						result.SByte();
						result 
						<< pKnightSiegeWarFare->sCastleIndex
						<< uint8(1)
						<< pKnight->GetName()
						<< pKnight->m_byNation 
						<< pKnight->m_sMembers
						<< pKnightSiegeWarFare->byWarRequestDay
						<< pKnightSiegeWarFare->byWarRequestTime 
						<< pKnightSiegeWarFare->byWarRequestMinute;
						Send(&result);
						break;

					case 5:
						result.SByte();
					result 
						<< pKnightSiegeWarFare->sCastleIndex 
						<< pKnightSiegeWarFare->bySiegeType
						<< pKnight->GetName()
						<< pKnight->m_byNation 
						<< pKnight->m_sMembers;
						Send(&result);
						break;

					default:
						break;
				}
			}break;

		case 4:
			{
				result << opcode << type;
					switch (type)
					{
					case 2:
						pKnightSiegeWarFare->nDungeonCharge += pKnightSiegeWarFare->nDellosTax + pKnightSiegeWarFare->nMoradonTax;
						pKnightSiegeWarFare->nDellosTax = 0;
						pKnightSiegeWarFare->nMoradonTax = 0;
						GoldGain(pKnightSiegeWarFare->nDungeonCharge,true);
						pKnightSiegeWarFare->nDungeonCharge = 0;
						g_pMain->UpdateSiegeTax(0 , 0);
						break;
					case 3:
						result << pKnightSiegeWarFare->sCastleIndex
						<< pKnightSiegeWarFare->sMoradonTariff
						<< pKnightSiegeWarFare->sDellosTariff
						<< (pKnightSiegeWarFare->nDungeonCharge += pKnightSiegeWarFare->nDellosTax + pKnightSiegeWarFare->nMoradonTax);
						pKnightSiegeWarFare->nDellosTax = 0;
						pKnightSiegeWarFare->nMoradonTax = 0;
						Send(&result);
						break;
					case 4:
						pKnightSiegeWarFare->sMoradonTariff = tarrif;
						g_pMain->UpdateSiegeTax(ZONE_MORADON , tarrif);
						result << uint16(1) << tarrif << uint8(ZONE_MORADON);
						g_pMain->Send_All(&result);
						g_pMain->m_KnightsSiegeWarfareArray.GetData(pKnightSiegeWarFare->sMasterKnights);
						break;
					case 5:
						pKnightSiegeWarFare->sDellosTariff = tarrif;
						g_pMain->UpdateSiegeTax(ZONE_DELOS , tarrif);
						result << uint16(1) << tarrif << uint8(ZONE_DELOS);
						g_pMain->Send_All(&result);
						g_pMain->m_KnightsSiegeWarfareArray.GetData(pKnightSiegeWarFare->sMasterKnights);
						break;
					default:
						break;
					}
			}break;
		default:
			break;
		}
}

void CUser::LogosShout(Packet & pkt)
{
	uint8 opcode;
	string Notice;

	pkt >> opcode >> Notice;

	Packet result(WIZ_LOGOSSHOUT);
	result << opcode << Notice;
	Send(&result);
}

// BURALAR DÜZELTİLECEK.
void CUser::EXPFlash()
{
	uint16 EXPFlash;

	EXPFlash = GetItemCount(810306000);

	if(EXPFlash < 1 )
		return;

	else if(EXPFlash > 0 )
		RobItem(399127000);

	if(m_bPremiumInUse == 11)
	{
		if(m_FlashExpBonus == 1)
			m_FlashExpBonus = 0;

		m_FlashExpBonus += 10;

		if(m_FlashExpBonus > 100)
			m_FlashExpBonus = 100;

		SendNotice();
	}
}

void CUser::DCFlash()
{
	if(m_bPremiumInUse == 10)
	{
		if(m_FlashDcBonus == 1)
			m_FlashDcBonus = 0;

		m_FlashDcBonus += 10;

		if(m_FlashDcBonus > 100)
			m_FlashDcBonus = 100;

		SendNotice();
	}
}

void CUser::WARFlash()
{
	if(m_bPremiumInUse == 12)
	{
		if(m_FlashWarBonus == 1)
			m_FlashWarBonus = 0;

		m_FlashWarBonus += 10;

		if(m_FlashWarBonus > 100)
			m_FlashWarBonus = 100;

		SendNotice();
	}
}

/*
void CUser::StaminaChange(int amount)
{
	Packet result(WIZ_SP_CHANGE);
	int16 oldSP = m_sSp;

	oldSP += amount;

	if (m_sSp < 0)
		m_sSp = 0;
	else if (m_sSp >= m_iMaxSp)
		m_sSp = m_iMaxSp;
	
	result << m_iMaxSp << m_sSp;
	
	result << uint8(1) << uint8(1);
	result << uint8(m_iMaxSp) << uint16(oldSP);
	Send(&result);
 }
 */

void CUser::SpChange(int amount)
{
	Packet result(WIZ_SP_CHANGE);

	m_iMaxSp = 100;
	m_sSp += amount;

	if (m_sSp > m_iMaxSp)
		m_sSp = m_iMaxSp;

	result << uint8(1) << uint8(1);
	result << uint8(m_iMaxSp) << uint16(m_sSp);
	Send(&result);
}

/*
//SucessRate by Obede & Anderson
bool CUser::isMagicEffected(CUser* pCaster, uint32 nSkillID)
{
    bool bResult = false;
    uint16 sCasterTotalDamage = 0; uint16 sTargetTotalResist = 0;
    double CasterAmount = 0.00; double TargetAmount = 0.00; double SkillAmount = 0.00;

	int HandEnable = 0;
    _ITEM_TABLE* pRightHand = nullptr;
    pRightHand = g_pMain->GetItemPtr( pCaster->m_sItemArray[RIGHTHAND].nNum );
    if(pRightHand != nullptr)
	{
		HandEnable = RIGHTHAND;
    }
	else
	{	 
		pRightHand = g_pMain->GetItemPtr( pCaster->m_sItemArray[LEFTHAND].nNum );
		if(pRightHand != nullptr)
		{
			 HandEnable =LEFTHAND;
		}
	}

	if(pRightHand  == nullptr)
	{  
		return bResult;
	}


    _MAGIC_TABLE* pMagic = nullptr;
    pMagic = g_pMain->m_MagictableArray.GetData(nSkillID);
    if(pMagic == nullptr) {
        return bResult;
    }


    _MAGIC_TYPE4* pType4 = nullptr;
    pType4 = g_pMain->m_Magictype4Array.GetData(nSkillID);
    if(pType4 == nullptr) {
        return bResult;
    }


    for(int i = 0; i < SLOT_MAX; i++)
    {
        _ITEM_TABLE* pTable = nullptr;
        pTable = g_pMain->GetItemPtr( pCaster->m_sItemArray[i].nNum );
        if(pTable == nullptr) {
            continue;
        }


        if(!pCaster->isMage())
        {
            if(pRightHand->m_bIceDamage)
            {
                sCasterTotalDamage += pTable->m_bIceDamage;
            }
            else if(pRightHand->m_bFireDamage)
            {
                sCasterTotalDamage += pTable->m_bFireDamage;
            }
            else if(pRightHand->m_bLightningDamage)
            {
                sCasterTotalDamage += pTable->m_bLightningDamage;
            }
            else if(pRightHand->m_bPoisonDamage)
            {
                sCasterTotalDamage += pTable->m_bPoisonDamage;
            }
        }
        else if(pCaster->isMage())
        {
            if(pRightHand->m_bIceDamage && pType4->bBuffType == BUFF_TYPE_SLOW) 
            {
                sCasterTotalDamage += pTable->m_bIceDamage;
            }
            else if(pRightHand->m_bLightningDamage && pType4->bBuffType == BUFF_TYPE_STUNN) 
            {
                sCasterTotalDamage += pTable->m_bLightningDamage;
            }
        }
    }


    if(pRightHand->m_bIceDamage) {
        sTargetTotalResist =  uint16(((m_sColdR + m_bAddColdR) * m_bPctColdR / 100) + m_bResistanceBonus);//m_sColdR + m_bAddColdR;
    }


    if(pRightHand->m_bLightningDamage) {
        sTargetTotalResist = uint16(((m_sLightningR + m_bAddLightningR) * m_bPctLightningR / 100) + m_bResistanceBonus);// m_sLightningR + m_bAddLightningR;
    }


    if(pRightHand->m_bPoisonDamage) {
        sTargetTotalResist = uint16(((m_sPoisonR + m_bAddPoisonR) * m_bPctPoisonR / 100) + m_bResistanceBonus);//m_sPoisonR + m_bAddPoisonR;
    }


    if(pRightHand->m_bFireDamage) {
        sTargetTotalResist =  uint16(((m_sFireR + m_bAddFireR) * m_bPctFireR / 100) + m_bResistanceBonus);//m_sFireR + m_bAddFireR;
    }


    if(sTargetTotalResist >= MAX_RESSIT) {
        return bResult;
    }


    if(sTargetTotalResist == 0) {
        return !bResult;
    }
        
    SkillAmount = pMagic->bSuccessRate  / 2;
    CasterAmount = SkillAmount + (100 - ((MAX_RESSIT - (sCasterTotalDamage / 4)) / 2.55));
    TargetAmount = 100 - (MAX_RESSIT - sTargetTotalResist) / (2.55);

    if(CasterAmount > TargetAmount) {
        bResult = true;
    }


    return bResult;
}*/

void CUser::UpdateStatusCSW()
{
	uint8 command = 2;

	Packet result(WIZ_ITEM_MOVE, command);

			result << command
			<< uint16(m_sTotalHit * m_bAttackAmount / 100) 
			<< uint16(m_sTotalAc + m_sACAmount)
			<< m_sMaxWeight
			<< uint8(1)
			<< m_iMaxHp << m_iMaxMp
			<< GetStatBonusTotal(STAT_STR) << GetStatBonusTotal(STAT_STA)
			<< GetStatBonusTotal(STAT_DEX) << GetStatBonusTotal(STAT_INT)
			<< GetStatBonusTotal(STAT_CHA)
			<< uint16(((m_sFireR + m_bAddFireR) * m_bPctFireR / 100) + m_bResistanceBonus) 
			<< uint16(((m_sColdR + m_bAddColdR) * m_bPctColdR / 100) + m_bResistanceBonus) 
			<< uint16(((m_sLightningR + m_bAddLightningR) * m_bPctLightningR / 100) + m_bResistanceBonus) 
			<< uint16(((m_sMagicR + m_bAddMagicR) * m_bPctMagicR / 100) + m_bResistanceBonus) 
			<< uint16(((m_sDiseaseR + m_bAddDiseaseR) * m_bPctDiseaseR / 100) + m_bResistanceBonus) 
			<< uint16(((m_sPoisonR + m_bAddPoisonR) * m_bPctPoisonR / 100) + m_bResistanceBonus);

	Send(&result);
}

void CUser::ExpEvent(int64 exp)
{
	if ((GetLevel() == 83 && m_iExp == m_iMaxExp))
		return;

	int rand = 0;
	int64 m_bExpEvent = 0;
	rand = myrand(1,5000);
    
	if(rand > 1200)
		return;

    if(rand > 0 && rand < 1000)
        rand = 2;
    else if(rand >= 1000 && rand < 1100) 
        rand = 10;
    else if(rand >= 1100 && rand < 1150)    
        rand = 50;
    else if(rand >= 1150 && rand < 1175)    
        rand = 100;
    else if(rand >= 1175 && rand < 1192) 
        rand = 500;
    else if(rand >= 1192 && rand < 1201) 
        rand = 1000;
   
	m_bExpEvent = rand * exp;
	
	Packet result(WIZ_EXP_CHANGE,uint8(2));
	result << GetID() << rand << m_iExp;
	SendToRegion(&result);
	ExpChange(m_bExpEvent);
}

void CUser::GoldEvent(uint32 gold)
{
	if (m_iGold == 2100000000)
		return;

	if (ITEM_GOLD) {
		uint16 m_bGoldEvent = 0;
		int rand = 0;
		rand = myrand(1,5000);
   
		if(rand > 2000)
			return;

		if(rand > 0 && rand < 1100)
			rand = 2;
		else if(rand >= 1100 && rand < 1300)
			rand = 10;
		else if(rand >= 1300 && rand < 1500)
			rand = 50;
		else if(rand >= 1500 && rand < 1900)
			rand = 100;
		else if(rand >= 1900 && rand < 1950)
			rand = 500;
		else if(rand >= 1950 && rand < 2001)
			rand = 1000;
   
		m_bGoldEvent = rand;

		Packet result(WIZ_GOLD_CHANGE,uint8(CoinEvent));
		result.SByte();
		result << uint16(740) << uint16(0) << uint32(0) << m_bGoldEvent << GetID();
		SendToRegion(&result);
		gold = gold * (rand);
		GoldGain(gold,true,false);
	}
}

void CUser::CanChangeHair(Packet & pkt)
{
	std::string strUserID;
	uint32 nHair;
	uint8 bOpcode, bFace;

	RobItem(ITEM_MAKE_OVER);

	pkt.SByte();
	pkt >> bOpcode >> strUserID >> bFace >> nHair;

	Packet result(WIZ_CHANGE_HAIR);
	result.SByte();
	result << bOpcode << strUserID << bFace << nHair;
	g_pMain->AddDatabaseRequest(result, this);
}

void CUser::ShowBulletinBoard()
{
	Packet result(WIZ_BATTLE_EVENT,uint8(13));
	result 	<< uint8(31)
		<< uint8(232);

	result << uint8(3)
		<< uint8(9)
		<< uint8(1);

	CKnights * pKnights = g_pMain->GetClanPtr(GetClanID());
	result << "Obede"
		<< uint64(0)
		<< uint64(0)
		<< uint64(0)
		<< uint64(0)
		<< uint64(0)
		<< uint64(0)
		<< uint64(0)
		<< uint64(0)
		<< uint64(0)
		<< uint64(0)
		<< uint64(0)
		<< uint64(0);

	Send(&result);
}

void CUser::RecvPremium(Packet & pkt)
{
	uint8 opcode, pType;

	pkt >> opcode >> pType;

	m_bPremiumInUse = pType;

	Packet result(WIZ_PREMIUM, uint8(opcode));
	result << m_bPremiumInUse
		<< uint32(1);
	Send(&result);

	g_DBAgent.SavePremiumServiceUser(this);
}

void  CUser::SendPremiumExpire()
{
	bool InUseEmpty = true;
	Packet result (WIZ_PREMIUM, uint8(1));
	result << m_bPremiumExCount;

	for (int i = 0; i < PREMIUM_TOTAL; i++)
	{
		uint32 TimeRest;
		uint16 TimeShow;
		_PREMIUM_DATA * uPrem = GetPremiumPtr(i);

		if (!uPrem)
			continue;
		if (uPrem->pTime == 0)
			continue;

		TimeRest = uint32(uPrem->pTime - UNIXTIME);

		if (TimeRest >= 1 && TimeRest <= 3600)
			TimeShow = 1;
		else
			TimeShow = TimeRest / 3600;

		if (uPrem->pType == m_bPremiumInUse)
			InUseEmpty = false;

		result << uPrem->pType
			<< TimeShow;
	}

	if (InUseEmpty)
	{
		if (m_bPremiumExCount > 0)
			m_bPremiumInUse = m_sPremiumArray[0].pType;
		else
			m_bPremiumInUse = 0;
	}

	g_DBAgent.SavePremiumServiceUser(this);	
	result << m_bPremiumInUse
		<< uint32(0); // Unknow
	Send(&result);
}

void CUser::Check_Expire()
{
	for (int i = 0; i < INVENTORY_TOTAL; i++)
	{
		_ITEM_DATA *pItem = &(m_sItemArray[i]);
		if(pItem->nExpirationTime <= UNIXTIME && 0 != pItem->nExpirationTime)
		{
			RobItem(pItem->nNum, 1);
		}
	}
}

void CUser::UpdateStatusPacket()
{
	Packet result(WIZ_VIP_INN);
	result << uint8(VIPHOUSE_OPEN);
	result << uint8(4)
			<< uint8(1)
			<< uint8(1);
	Send(&result);
}