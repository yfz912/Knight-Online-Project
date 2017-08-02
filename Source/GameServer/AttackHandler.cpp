#include "stdafx.h"
#include "Map.h"

void CUser::Attack(Packet & pkt)
{
	int16 sid = -1, tid = -1, damage, delaytime, distance;	
	uint8 bType, bResult = 0;	
	Unit * pTarget = nullptr;

	pkt >> bType >> bResult >> tid >> delaytime >> distance;

	if (isIncapacitated())
		return;

	if (isInSafetyArea())
		return;

	RemoveStealth();

	_ITEM_TABLE *pTable = GetItemPrototype(RIGHTHAND);
	if (pTable != nullptr && !isMage()) 
	{
		if (delaytime < (pTable->m_sDelay + 10)
			|| distance > pTable->m_sRange)
			return;	
	}

	else if (delaytime < 100)
		return;			

	pTarget = g_pMain->GetUnitPtr(tid);
	bResult = ATTACK_FAIL;

	if (pTarget != nullptr && isInAttackRange(pTarget) && CanAttack(pTarget))
	{
		if (isAttackable(pTarget) && CanCastRHit(GetSocketID()))
		{
			if (isInTempleEventZone() && (!isSameEventRoom(pTarget) || !g_pMain->pTempleEvent.isAttackable))
				return;

			if (pTarget->hasBuff(BUFF_TYPE_FREEZE))
				return;

			CUser *pUser = g_pMain->GetUserPtr(GetSocketID());

			if (pUser != nullptr)
				pUser->m_RHitRepeatList.insert(std::make_pair(GetSocketID(), UNIXTIME));

			damage = GetDamage(pTarget);

			if (GetZoneID() == ZONE_SNOW_BATTLE && g_pMain->m_byBattleOpen == SNOW_BATTLE)
				damage = 0;
			else if (GetZoneID() == ZONE_CHAOS_DUNGEON && g_pMain->pTempleEvent.isAttackable)
				damage = 500 / 10;
			else if (GetZoneID() == ZONE_PRISON)
			{
				if (GetMana() < (m_iMaxMp / 5))
					return;

				damage = 1;
				MSpChange(-(m_iMaxMp / 5));
			}

			if (damage > 0)
			{
				pTarget->HpChange(-damage, this);
				if (pTarget->isDead())
					bResult = ATTACK_TARGET_DEAD;
				else
					bResult = ATTACK_SUCCESS;

				ItemWoreOut(ATTACK, damage);

				if (pTarget->isPlayer())
					TO_USER(pTarget)->ItemWoreOut(DEFENCE, damage);
			}
		}
	}

	Packet result(WIZ_ATTACK, bType);
	result << bResult << GetSocketID() << tid;
	SendToRegion(&result);
}

void CUser::Regene(uint8 regene_type, uint32 magicid /*= 0*/)
{
	ASSERT(GetMap() != nullptr);

	_OBJECT_EVENT* pEvent = nullptr;
	_START_POSITION* pStartPosition = nullptr;
	float x = 0.0f, z = 0.0f;

	if (!isDead())
		return;

	if (regene_type != 1 && regene_type != 2)
		regene_type = 1;

	if (regene_type == 2) 
	{
		if (GetLevel() <= 5
				|| !RobItem(379006000, 3 * GetLevel()))
				return;
	}

	pStartPosition = g_pMain->m_StartPositionArray.GetData(GetZoneID());
	if (pStartPosition == nullptr)
		return;

	UserInOut(INOUT_OUT);

	pEvent = GetMap()->GetObjectEvent(m_sBind);	

	if (magicid == 0) 
	{
		if(JuraidSpot != 0 && GetZoneID() == ZONE_JURAD_MOUNTAIN)
		{
			if(GetNation() == KARUS)
			{
				x = (float)sCordKarusX[JuraidSpot-1];
				z = (float)sCordKarusZ[JuraidSpot-1];
			}
			else
			{
				x = (float)sCordElmoradX[JuraidSpot-1];
				z = (float)sCordElmoradZ[JuraidSpot-1];
			}
		}
		else if (pEvent && pEvent->byLife == 1 && GetZoneID() != ZONE_DELOS)
		{
			SetPosition(pEvent->fPosX + x, 0.0f, pEvent->fPosZ + z);
			x = pEvent->fPosX;
			z = pEvent->fPosZ;
		}
		else if ((GetZoneID() <= ZONE_ELMORAD) || (GetZoneID() != ZONE_SNOW_BATTLE && GetZoneID() == (ZONE_BATTLE_BASE + g_pMain->m_byBattleZone))) 
		{
			x = (float)((GetNation() == KARUS ? pStartPosition->sKarusX :  pStartPosition->sElmoradX) + myrand(0, pStartPosition->bRangeX));
			z = (float)((GetNation() == KARUS ? pStartPosition->sKarusZ :  pStartPosition->sElmoradZ) + myrand(0, pStartPosition->bRangeZ));
		}
		else
		{
			short sx, sz;

			if ((GetZoneID() == ZONE_MORADON || GetZoneID() == ZONE_MORADON2  
				|| GetZoneID() == ZONE_MORADON3 || GetZoneID() == ZONE_MORADON4 
				|| GetZoneID() == ZONE_MORADON5) && isInArena())
			{
				x = (float)(MINI_ARENA_RESPAWN_X + myrand(-MINI_ARENA_RESPAWN_RADIUS, MINI_ARENA_RESPAWN_RADIUS));
				z = (float)(MINI_ARENA_RESPAWN_Z + myrand(-MINI_ARENA_RESPAWN_RADIUS, MINI_ARENA_RESPAWN_RADIUS));
			}
			else if (GetZoneID() == ZONE_CHAOS_DUNGEON)
			{
				GetStartPositionRandom(sx, sz);
				x = sx;
				z = sz;
			}
			else
			{
				GetStartPosition(sx, sz);
				x = sx;
				z = sz;
			}
		}

		SetPosition(x, 0.0f, z);

		m_LastX = x;
		m_LastZ = z;

		m_bResHpType = USER_STANDING;	
		m_bRegeneType = REGENE_NORMAL;
	}
	else
	{
		_MAGIC_TYPE5 * pType = g_pMain->m_Magictype5Array.GetData(magicid);     
		if (pType == nullptr)
			return;

		MSpChange(-m_iMaxMp); // reset us to 0 MP. 

		if (m_sWhoKilledMe == -1) 
			ExpChange((m_iLostExp * pType->bExpRecover) / 100); // Restore 

		m_bResHpType = USER_STANDING;
		m_bRegeneType = REGENE_MAGIC;
	}

	Packet result(WIZ_REGENE);
	result << GetSPosX() << GetSPosZ() << GetSPosY();
	Send(&result);

	m_tLastRegeneTime = UNIXTIME;
	m_sWhoKilledMe = -1;
	m_iLostExp = 0;

	if (!isBlinking())
	{
		result.Initialize(AG_USER_REGENE);
		result << GetSocketID() << m_sHp;
		Send_AIServer(&result);
	}

	SetRegion(GetNewRegionX(), GetNewRegionZ());

	g_pMain->RegionUserInOutForMe(this);
	g_pMain->RegionNpcInfoForMe(this);

	UserInOut(INOUT_RESPAWN);

	InitializeStealth();
	SendUserStatusUpdate(USER_STATUS_DOT, USER_STATUS_CURE);
	SendUserStatusUpdate(USER_STATUS_POISON, USER_STATUS_CURE);

	if (isInArena())
		SendUserStatusUpdate(USER_STATUS_SPEED, USER_STATUS_CURE);

	HpChange(GetMaxHealth());

	InitType4();
	RecastSavedMagic();

	HpChange(GetMaxHealth());

	if (magicid == 0)
	{
		BlinkStart();
		if (GetLoyalty() == 0 
			&& (GetMap()->isWarZone()
			|| isInPKZone()))
			KickOutZoneUser();
	}
}