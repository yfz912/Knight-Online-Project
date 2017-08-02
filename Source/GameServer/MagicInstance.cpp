#include "stdafx.h"
#include "Map.h"
#include "../shared/KOSocketMgr.h"
#include "MagicProcess.h"
#include "MagicInstance.h"

using std::string;
using std::vector;


void MagicInstance::Run()
{
	SkillUseResult result;
	if (pSkill == nullptr)
		pSkill = g_pMain->m_MagictableArray.GetData(nSkillID);

	if (pSkillCaster == nullptr)
		pSkillCaster = g_pMain->GetUnitPtr(sCasterID);

	if(pSkill!=nullptr&&pSkillCaster!=nullptr&&pSkillCaster->isPlayer())
	{
		int8 moral = pSkill->bMoral;
		if(moral==MORAL_SELF)
		{
			if(pSkillCaster->isPlayer())
			{
				sTargetID=pSkillCaster->GetID();
			}
		}
		
		if(moral==MORAL_FRIEND_WITHME)
		{
			if(sTargetID!=-1)
			{
				Unit*cstr = g_pMain->GetUnitPtr(sTargetID);
				if(cstr!=nullptr)
				{
					if(cstr!=pSkillCaster&&pSkillCaster->isHostileTo(cstr))
						sTargetID=pSkillCaster->GetID();
				}
			}
		}
	}

	if (sTargetID != -1 && pSkillTarget == nullptr)
		pSkillTarget = g_pMain->GetUnitPtr(sTargetID);
	
	if (pSkill == nullptr
		|| pSkillCaster == nullptr
		|| CheckSkillPrerequisites() == SkillUseFail
		|| (result = UserCanCast()) == SkillUseFail)
	{
		SendSkillFailed();
		return;
	}

	if (result == SkillUseHandled)
		return;

	bool bInitialResult;
	switch (bOpcode)
	{
	case MAGIC_CASTING:
	case MAGIC_FAIL:
		SendSkill(bOpcode == MAGIC_CASTING);
		break;

	case MAGIC_FLYING:
		{
			if (pSkillCaster->isPlayer())
			{
				CUser * pCaster = TO_USER(pSkillCaster);
				_MAGIC_TYPE2 * pType = g_pMain->m_Magictype2Array.GetData(nSkillID);

				if (pType != nullptr)
				{
					uint8 bCount = pType->bNeedArrow;
					if (!bCount)
						bCount = 1;

					if (pType == nullptr
							|| (!pCaster->CheckExistItem(pSkill->iUseItem, bCount))
							|| pSkill->sMsp > pSkillCaster->GetMana()
							|| pSkill->ssSp > pCaster->GetStamina())
					{
						SendSkillFailed();
						return;
					}

					Guard lock(pCaster->m_arrowLock);
					for (size_t i = 0; i < bCount; i++)
						pCaster->m_flyingArrows.push_back(Arrow(pType->iNum, UNIXTIME));

					pCaster->RobItem(pSkill->iUseItem, bCount);
				}
				else if (pSkill->sMsp > pSkillCaster->GetMana())
				{
					SendSkillFailed();
					return;
				}

				if (pSkill->ssSp > pCaster->GetStamina())
				{
					SendSkillFailed();
					return;
				}

				if (!pCaster -> isBlinking())
				{
					pCaster->MSpChange(-(pSkill->sMsp));
					pCaster->SpChange(-(pSkill->ssSp));
				}
			}

			SendSkill(true);
		} break;

	case MAGIC_EFFECTING:
		if (!bIsRecastingSavedMagic
			&& (pSkill->bType[0] == 0 && pSkill->bType[1] != 0 && pSkill->iUseItem != 0
			&& (pSkillCaster->isPlayer() && TO_USER(pSkillCaster)->CheckExistItem(pSkill->iUseItem)))
			&& !TO_USER(pSkillCaster)->isInPKZone())
		{
			SendTransformationList();
			return;
		}

		bInitialResult = ExecuteSkill(pSkill->bType[0]);

		if (bInitialResult)
		{
			if (pSkillCaster->isPlayer())
			{
				CUser *pCaster = TO_USER(pSkillCaster);

				if (!pSkillCaster->hasBuff(BUFF_TYPE_INSTANT_MAGIC)) 
				{
					pCaster->m_CoolDownList.insert(std::make_pair(nSkillID, UNIXTIME));

					if (pSkill->bType[0] != 0)
						pCaster->m_MagicTypeCooldownList.insert(std::make_pair(pSkill->bType[0], UNIXTIME));

					if (pSkill->bType[1] != 0)
						pCaster->m_MagicTypeCooldownList.insert(std::make_pair(pSkill->bType[1], UNIXTIME));
				}
			}

			ExecuteSkill(pSkill->bType[1]);

			if (pSkill->bType[0] != 2)
				ConsumeItem();
		}
		break;

	case MAGIC_CANCEL:
	case MAGIC_CANCEL2:
		Type3Cancel();
		Type4Cancel();
		Type6Cancel();
		Type9Cancel();
		break;

	case MAGIC_TYPE4_EXTEND:
		Type4Extend();
		break;
	}
}

SkillUseResult MagicInstance::UserCanCast()
{
	if (pSkill == nullptr)
		return SkillUseFail;

	if (bOpcode == MAGIC_CANCEL || bOpcode == MAGIC_CANCEL2
			|| bOpcode == MAGIC_FAIL
			|| bIsRecastingSavedMagic)
			return SkillUseOK;

	if (!pSkillCaster->canUseSkills()
		|| (pSkillCaster->isDead() && pSkill->bType[0] != 5)) 
		return SkillUseFail;

	if ((pSkill->bMoral >= MORAL_AREA_ENEMY && pSkill->bMoral <= MORAL_SELF_AREA) && sTargetID != -1)
	{
		if (!bIsItemProc)
			return SkillUseFail;

		sTargetID = -1;
	}

	if (pSkillCaster->isPlayer())
	{
		CUser * pCaster = TO_USER(pSkillCaster);
		if ((pSkill->sSkill != 0
			&& (TO_USER(pSkillCaster)->m_sClass != (pSkill->sSkill / 10)
			|| pSkillCaster->GetLevel() < pSkill->sSkillLevel)) 
			&& pSkillCaster->GetZoneID() != ZONE_CHAOS_DUNGEON)
			return SkillUseFail;

		if (pSkillCaster->GetZoneID() == ZONE_CHAOS_DUNGEON && !g_pMain->pTempleEvent.isAttackable)
			return SkillUseFail;

		if (pSkillCaster->GetZoneID() == ZONE_BORDER_DEFENSE_WAR && !g_pMain->pTempleEvent.isAttackable)
			return SkillUseFail;

		if (pSkillCaster->GetZoneID() == ZONE_JURAD_MOUNTAIN && !g_pMain->pTempleEvent.isAttackable)
			return SkillUseFail;
	
		if (	TO_USER(pSkillCaster)->isTrading() 
			||	TO_USER(pSkillCaster)->isMerchanting() 
			||	TO_USER(pSkillCaster)->isSellingMerchant()
			||	TO_USER(pSkillCaster)->isBuyingMerchant())
			return SkillUseFail;

		if ((pSkillCaster->GetMana() - pSkill->sMsp) < 0)
			return SkillUseFail;

		if ((pCaster->GetStamina() - pSkill->ssSp) < 0)
			return SkillUseFail;

		if (pSkillCaster->GetZoneID() == ZONE_SNOW_BATTLE && g_pMain->m_byBattleOpen == SNOW_BATTLE && nSkillID != SNOW_EVENT_SKILL)
			return SkillUseFail;

		if (pSkillTarget != nullptr
			&& pSkill->bMoral == MORAL_ENEMY
			&& pSkill->bType[0] == 3 
			&& pSkill->bType[1] == 0
			&& pSkillTarget->isDead())
		{
			_MAGIC_TYPE3 * pType3 = g_pMain->m_Magictype3Array.GetData(pSkill->iNum);
			if (pType3 == nullptr)
				return SkillUseFail;

			if (pType3->bDirectType == 0 && pType3->sFirstDamage == 0 && pType3->sTimeDamage == 0)
			{
				bOpcode = MAGIC_EFFECTING;
				sData[1] = 1;
				SendSkill();
				return SkillUseHandled;
			}
		}

		_MAGIC_TYPE5 * pType5;

		uint8 bType = 0;
		uint16 sNeedStone = 0;

		if (pSkill->bType[0] == 5)
		{
			pType5 = g_pMain->m_Magictype5Array.GetData(pSkill->iNum);

			if (pType5)
			{
				bType = pType5->bType;
				sNeedStone = pType5->sNeedStone;
			}
		}

		if ((pSkill->bType[0] != 2 && pSkill->bType[0] != 6) 
				&& (pSkill->iUseItem != 0 && !TO_USER(bType == RESURRECTION ? pSkillTarget : pSkillCaster)->CanUseItem(pSkill->iUseItem, (bType == RESURRECTION ? sNeedStone : 1))))
				return SkillUseFail;

		if (pSkill->nBeforeAction >= ClassWarrior && pSkill->nBeforeAction <= ClassPriest)
			nConsumeItem = CLASS_STONE_BASE_ID + (pSkill->nBeforeAction * 1000);
		else
			nConsumeItem = pSkill->iUseItem;

		if ((pSkill->bType[0] != 2 && pSkill->bType[0] != 6) 
				&& (pSkill->iUseItem != 0 && !TO_USER(pSkillCaster)->CanUseItem(nConsumeItem)) && bType != RESURRECTION)
				return SkillUseFail;

		if (pSkill->bType[0] == 6
			&& (nSkillID / 10000) == 45
			&& pSkillCaster->GetZoneID() != ZONE_DELOS)
			return SkillUseFail;

#if !defined(DEBUG)
		if (!TO_USER(pSkillCaster)->isGM() && pSkill->sEtc != 0 && !TO_USER(pSkillCaster)->CheckExistEvent(pSkill->sEtc, 2))
			return SkillUseFail;
#endif

		if (pSkill->bType[0] < 4 && pSkillTarget != nullptr && !pSkillCaster->isInAttackRange(pSkillTarget, pSkill))
			return SkillUseFail;
	}

	if ((bOpcode == MAGIC_EFFECTING || bOpcode == MAGIC_CASTING) && !IsAvailable())
		return SkillUseFail;

	if (bOpcode == MAGIC_EFFECTING && pSkillCaster->canInstantCast())
		bInstantCast = true;

	return SkillUseOK;
}

SkillUseResult MagicInstance::CheckSkillPrerequisites()
{
	if (pSkill == nullptr)
		return SkillUseFail;

	if (bOpcode != MAGIC_FLYING && bOpcode != MAGIC_EFFECTING)
	{
		if (bOpcode == MAGIC_CASTING 
			&& pSkillTarget
			&& (pSkill->sRange > 0 
			&& pSkill->sUseStanding == 1
			&& (pSkillCaster->GetDistanceSqrt(pSkillTarget) >= (float)pSkill->sRange)))
			return SkillUseFail;
		else
			return SkillUseOK;
	}

	if (pSkillCaster == nullptr)
	{
		TRACE("#### CheckSkillPrerequisites : pSkillCaster == nullptr ####\n");
		return SkillUseFail;
	}

	if (nSkillID > 299999 && nSkillID < 399999) {
		if (pSkillCaster->isPlayer())
			return SkillUseFail;
	}

	if (nSkillID == 120011 || nSkillID == 120021 || nSkillID == 220011 || nSkillID == 220021) {
		if (pSkillCaster->GetZoneID() != ZONE_DELOS)
			return SkillUseFail;
	}

	if (pSkillCaster->isPlayer())
	{
		CUser *pCaster = TO_USER(pSkillCaster);

		if (pCaster)
		{
			if (pCaster->GetZoneID() == ZONE_PRISON)
				return SkillUseFail;

			if (pSkill->sUseStanding == 1
				&& pCaster->m_sSpeed != 0) // Hacking prevention!
				return SkillUseFail;

			if (pSkill->bType[0] == 3 || pSkill->bType[1] == 3)
			{
				_MAGIC_TYPE3 * pType = g_pMain->m_Magictype3Array.GetData(nSkillID);

				if (pType == nullptr)
					TRACE("[%s] Used skill %d but it does not exist in MagicType3.\n", pSkillCaster->GetName().c_str(), nSkillID);

				else if (pType->bAttribute == AttributeNone)
				{
					if (pSkill->bType[0] != 0)
						pCaster->m_MagicTypeCooldownList.erase(pSkill->bType[0]);

					if (pSkill->bType[1] != 0)
						pCaster->m_MagicTypeCooldownList.erase(pSkill->bType[1]);
				}
			}

			if (pSkillTarget != nullptr)
			{
				if ((pSkill->sRange > 0 
					&& pSkill->sUseStanding == 0 
					&& (pSkillCaster->GetDistanceSqrt(pSkillTarget) >= (float)pSkill->sRange))
					|| (pCaster->isInSafetyArea() && nSkillID < 400000)
					|| (pCaster->isInTempEventZone() && !pCaster->isSameEventRoom(pSkillTarget)))
					return SkillUseFail;
			}

			if (bOpcode != MAGIC_TYPE4_EXTEND && pCaster->m_CoolDownList.find(nSkillID) != pCaster->m_CoolDownList.end())
			{
				SkillCooldownList::iterator itr = pCaster->m_CoolDownList.find(nSkillID);

				int64 DiffrentMilliseconds = (int64(UNIXTIME) * 1000) - (int64(itr->second) * 1000);

				if (DiffrentMilliseconds > 0 && DiffrentMilliseconds < int32(pSkill->sReCastTime * 100) && pSkill->bType[0] != 9 && !bIsRecastingSavedMagic)
					return SkillUseFail;
				else
					pCaster->m_CoolDownList.erase(nSkillID);
			}

			if (pCaster->isRogue() && pSkill->bType[0] == 2 && pSkill -> iUseItem != 370007000)
			{
				_ITEM_TABLE * pLeftHand  = TO_USER(pSkillCaster)->GetItemPrototype(LEFTHAND);
				_ITEM_TABLE * pRightHand  = TO_USER(pSkillCaster)->GetItemPrototype(RIGHTHAND);

				if ((pLeftHand == nullptr && pRightHand == nullptr)
					|| ((pLeftHand && !pLeftHand->isBow())
					|| (pRightHand && !pRightHand->isBow())))
					return SkillUseFail;

				if (bOpcode == MAGIC_EFFECTING)
					return SkillUseOK;						
			}

			MagicTypeCooldownList::iterator itr;
			if ((pSkill->bType[0] == 1 
				|| pSkill->bType[0] == 2
				|| pSkill->bType[0] == 3
				|| pSkill->bType[0] == 4
				|| pSkill->bType[0] == 5
				|| pSkill->bType[0] == 6
				|| pSkill->bType[0] == 7)
				&& nSkillID < 400000 
				&& pCaster->m_MagicTypeCooldownList.find(pSkill->bType[0]) != pCaster->m_MagicTypeCooldownList.end())
			{
				itr = pCaster->m_MagicTypeCooldownList.find(pSkill->bType[0]);

				if ((float(UNIXTIME - itr->second) < PLAYER_SKILL_REQUEST_INTERVAL))
					return SkillUseFail;
				else
					pCaster->m_MagicTypeCooldownList.erase(pSkill->bType[0]);
			} 

			if ((pSkill->bType[1] == 1 
				|| pSkill->bType[1] == 2
				|| pSkill->bType[1] == 3
				|| pSkill->bType[1] == 4
				|| pSkill->bType[1] == 5
				|| pSkill->bType[1] == 6
				|| pSkill->bType[1] == 7)
				&& nSkillID < 400000 
				&& pCaster->m_MagicTypeCooldownList.find(pSkill->bType[1]) != pCaster->m_MagicTypeCooldownList.end())
			{
				itr = pCaster->m_MagicTypeCooldownList.find(pSkill->bType[1]);

				if ((float(UNIXTIME - itr->second) < PLAYER_SKILL_REQUEST_INTERVAL))
					return SkillUseFail;
				else
					pCaster->m_MagicTypeCooldownList.erase(pSkill->bType[1]);
			}
		}
	}

	if (pSkillTarget != nullptr)
	{
		if (pSkillTarget->isNPC() && !pSkillTarget->isAttackable(pSkillTarget))
			return SkillUseFail;
		else
		{
			if (TO_USER(pSkillTarget)->hasBuff(BUFF_TYPE_FREEZE)) // Effect Sorunu ve Blink Sorunu Var...
				return SkillUseFail;
		}
	}

	return SkillUseOK;
}

bool MagicInstance::CheckType3Prerequisites()
{
	_MAGIC_TYPE3 * pType = g_pMain->m_Magictype3Array.GetData(nSkillID);
	if (pType == nullptr)
		return false;

	if (sTargetID == -1)
	{
		if (!pSkillCaster->isPlayer())
			return true;

		if (TO_USER(pSkillCaster)->isInSafetyArea())
			return false;

		if (pSkill->bMoral == MORAL_PARTY_ALL && pType->sTimeDamage > 0)
		{
			if (TO_USER(pSkillCaster)->isMonsterTransformation())
				return false;

			for (int i = 0; i < MAX_TYPE3_REPEAT; i++)
			{
				if (pSkillCaster->m_durationalSkills[i].m_sHPAmount > 0)
					return false;
			}
		}

		return true;
	}
	else if (sTargetID >= NPC_BAND)
	{
		if (pSkillTarget == nullptr)
			return false;

		if (pSkillCaster->GetZoneID() != 30 || (pType->sFirstDamage <= 0 && pType->sTimeDamage <= 0))
			return true;

		if (TO_NPC(pSkillTarget)->GetType() == NPC_GATE)
			return false;
		return true;
	}
	else
	{
		if (pSkill->bMoral > MORAL_PARTY)
			return true;

		if (pSkillTarget == nullptr 
			|| !pSkillTarget->isPlayer()
			|| pSkillTarget->isDead())
			return false;

		if (pType->sTimeDamage > 0)
		{
			for (int i = 0; i < MAX_TYPE3_REPEAT; i++)
			{
				if (pSkillTarget->m_durationalSkills[i].m_sHPAmount > 0)
					return false;
			}
		}

 		if (TO_USER(pSkillTarget)->isSiegeTransformation() && !pSkillCaster->CanAttack(pSkillTarget))
			return false;

		return true;
	}
}

bool MagicInstance::CheckType4Prerequisites()
{
	_MAGIC_TYPE4 * pType = g_pMain->m_Magictype4Array.GetData(nSkillID);

	if (pType == nullptr)
		return (pSkill->bType[0] == 6);

	if (sTargetID < 0 || sTargetID >= MAX_USER)
	{
		if (sTargetID < NPC_BAND
			|| pType->bBuffType != BUFF_TYPE_HP_MP 
			|| pType->sMaxHPPct != 99)
			return true;

		return false;
	}

	if (pSkillTarget == nullptr
		|| !pSkillTarget->isPlayer())
		return false;

	if (TO_USER(pSkillTarget)->isTransformed())
	{
		if (!TO_USER(pSkillTarget)->isNPCTransformation() 
			&& (nSkillID >= 500000
			|| pType->bBuffType == BUFF_TYPE_SIZE))
		{
			SendSkillFailed();
			return false;
		}
	}

	if (pType->isBuff())
	{
		Guard lock(pSkillTarget->m_buffLock);
		if (pSkillTarget->m_buffMap.find(pType->bBuffType) 
			!= pSkillTarget->m_buffMap.end())
			return false;
	}

	return true;
}

bool MagicInstance::CheckType6Prerequisites()
{
	if (!pSkillCaster->isPlayer())
		return true;

	_MAGIC_TYPE6 * pType = g_pMain->m_Magictype6Array.GetData(nSkillID);
	if (pType == nullptr)
		return false;

	CUser * pCaster = TO_USER(pSkillCaster);
	switch (pType->bUserSkillUse)
	{
	case TransformationSkillUseMonster:
		if ((!pCaster->CanUseItem(pSkill->nBeforeAction)
				|| !pCaster->CanUseItem(pSkill->iUseItem)) && !pCaster->CheckExistItem(381001000))
				return false;

		break;

	default:
		if (!pCaster->CanUseItem(pSkill->iUseItem))
			return false;
		break;
	}

	bool bAllowedClass = (pType->sClass == 0);
	if (bAllowedClass)
		return true;

	switch (pCaster->GetBaseClassType())
	{
	case ClassWarrior:
		bAllowedClass = ((pType->sClass / 1000)) == 1;
		break;

	case ClassRogue:
		bAllowedClass = ((pType->sClass % 1000) / 100) == 1;
		break;

	case ClassMage:
		bAllowedClass = (((pType->sClass % 1000) % 100) / 10) == 1;
		break;

	case ClassPriest:
		bAllowedClass = (((pType->sClass % 1000) % 100) % 10) == 1;
		break;

	case ClassKurPor:
		bAllowedClass = (((pType->sClass % 1000) % 100) % 10) == 1;
		break;
	}

	return bAllowedClass;
}

bool MagicInstance::ExecuteSkill(uint8 bType)
{
	if (bType == 0 || (pSkillCaster -> isBlinking() && bType != 4 && pSkill->iNum < 300000))
		return false;

	if (pSkillCaster->isPlayer())
	{
		if ((bType >= 1 && bType <= 3) || (bType == 7))
			TO_USER(pSkillCaster)->RemoveStealth();
	}

	switch (bType)
	{
	case 1: return ExecuteType1();
	case 2: return ExecuteType2();
	case 3: return ExecuteType3();
	case 4: return ExecuteType4();
	case 5: return ExecuteType5();
	case 6: return ExecuteType6();
	case 7: return ExecuteType7();
	case 8: return ExecuteType8();
	case 9: return ExecuteType9();
	}

	return false;
}

void MagicInstance::SendTransformationList()
{
	if (!pSkillCaster->isPlayer())
		return;

	Packet result(WIZ_MAGIC_PROCESS, uint8(MAGIC_TRANSFORM_LIST));
	result << nSkillID;
	TO_USER(pSkillCaster)->Send(&result);
}

void MagicInstance::SendSkillNotEffect()
{
	if (pSkillCaster == nullptr)
		return;

	Packet result;
	sData[3] = (bOpcode == MAGIC_CASTING ? SKILLMAGIC_FAIL_CASTING : SKILLMAGIC_FAIL_NOEFFECT);
	BuildSkillPacket(result, sCasterID, sTargetID, MAGIC_EFFECTING, nSkillID, sData);

	if (!bSendFail || !pSkillCaster->isPlayer())
 		return;
 
 	TO_USER(pSkillCaster)->Send(&result);
 }
 
void MagicInstance::SendSkillFailed(int16 sTargetID /*= -1*/)
{
	if (pSkillCaster == nullptr)
		return;

	Packet result;
	sData[3] = (bOpcode == MAGIC_CASTING ? SKILLMAGIC_FAIL_CASTING : SKILLMAGIC_FAIL_NOEFFECT);
	BuildSkillPacket(result, sCasterID, sTargetID == -1 ? this->sTargetID : sTargetID, MAGIC_FAIL, nSkillID, sData);

	if (!bSendFail
		|| !pSkillCaster->isPlayer())
		return;

	TO_USER(pSkillCaster)->Send(&result);
}

void MagicInstance::BuildSkillPacket(Packet & result, int16 sSkillCaster, int16 sSkillTarget, int8 opcode, 
									 uint32 nSkillID, int16 sData[7])
{
	if (opcode == MAGIC_FAIL)
	{
		bSkillSuccessful = false;

		if (!bSendFail)
			return;
	}	

	result.Initialize(WIZ_MAGIC_PROCESS);
	result	<< opcode << nSkillID << sSkillCaster << sSkillTarget
		<< sData[0] << sData[1] << sData[2] << sData[3]
	<< sData[4] << sData[5] << sData[6];
}

void MagicInstance::BuildAndSendSkillPacket(Unit * pUnit, bool bSendToRegion, int16 sSkillCaster, int16 sSkillTarget, int8 opcode, uint32 nSkillID, int16 sData[7])
{
	Packet result;
	BuildSkillPacket(result, sSkillCaster, sSkillTarget, opcode, nSkillID, sData);

	if (opcode == MAGIC_FAIL
		&& !bSendFail)
		return;

	if (bSendToRegion || !pUnit->isPlayer())
		pUnit->SendToRegion(&result);
	else
		TO_USER(pUnit)->SendToRegion(&result);
}

void MagicInstance::SendSkill(bool bSendToRegion /*= true*/, Unit * pUnit /*= nullptr*/)
{
	if (pUnit == nullptr)
		pUnit = pSkillCaster;

	BuildAndSendSkillPacket(pUnit, bSendToRegion, 
		this->sCasterID, this->sTargetID, this->bOpcode, this->nSkillID, this->sData);
}

bool MagicInstance::IsAvailable()
{
	CUser* pParty = nullptr;
	int modulator = 0, Class = 0, skill_mod = 0;

	if (pSkill == nullptr || (pSkillCaster->GetZoneID() == ZONE_CHAOS_DUNGEON && !g_pMain->pTempleEvent.isAttackable))
		goto fail_return;

	if (pSkill == nullptr || (pSkillCaster->GetZoneID() == ZONE_BORDER_DEFENSE_WAR && !g_pMain->pTempleEvent.isAttackable))
		goto fail_return;

	if (pSkill == nullptr || (pSkillCaster->GetZoneID() == ZONE_JURAD_MOUNTAIN && !g_pMain->pTempleEvent.isAttackable))
 		goto fail_return;

	switch (pSkill->bMoral)
	{
	case MORAL_SELF:
		if (pSkillCaster->isPlayer() 
			&& pSkillCaster != pSkillTarget)
			goto fail_return;
		break;

	case MORAL_FRIEND_WITHME:
		if (pSkillTarget != pSkillCaster 
			&& pSkillCaster->isHostileTo(pSkillTarget))
			goto fail_return;
		break;

	case MORAL_FRIEND_EXCEPTME:
		if (pSkillCaster == pSkillTarget
			|| pSkillCaster->isHostileTo(pSkillTarget))
			goto fail_return;
		break;

	case MORAL_PARTY:
		{
			if (pSkillCaster->isNPC()
				|| (pSkillTarget != nullptr && pSkillTarget->isNPC()))
				goto fail_return;

			CUser *pCaster = TO_USER(pSkillCaster);

			if ((!pCaster->isInParty() && pSkillCaster != pSkillTarget)
					|| (pSkillTarget != nullptr && 
					TO_USER(pSkillTarget)->GetPartyID() != pCaster->GetPartyID()))
					goto fail_return;
		} break;

	case MORAL_NPC:
		if (pSkillTarget == nullptr
			|| !pSkillTarget->isNPC()
			|| pSkillCaster->isHostileTo(pSkillTarget)
			&& pSkill->iUseItem != 379105000)
			goto fail_return;
		break;

	case MORAL_ENEMY:
		if (pSkillTarget != nullptr
						&& !pSkillCaster->isHostileTo(pSkillTarget))
						goto fail_return;
		break;	

	case MORAL_CORPSE_FRIEND:
		if (pSkillTarget == nullptr
				|| pSkillCaster->isHostileTo(pSkillTarget)
				|| pSkillCaster == pSkillTarget
				|| pSkillTarget->isAlive())
				goto fail_return;
		break;

	case MORAL_CLAN:
		{
			if (pSkillCaster->isNPC()
				|| (pSkillTarget != nullptr && pSkillTarget->isNPC()))
				goto fail_return;

			CUser * pCaster = TO_USER(pSkillCaster);

			if ((!pCaster->isInClan() && pSkillCaster != pSkillTarget)
					|| (pSkillTarget != nullptr 
					&& TO_USER(pSkillTarget)->GetClanID() != pCaster->GetClanID()))
					goto fail_return;
		} break;

	case MORAL_SIEGE_WEAPON:
		if (pSkillCaster->isPlayer()
			|| !TO_USER(pSkillCaster)->isSiegeTransformation())
			goto fail_return;
		break;
	}

	for (int i = 0; i < 2; i++) 
	{
		switch (pSkill->bType[i])
		{
		case 3: 
			if (!CheckType3Prerequisites())
				return false;
			break;

		case 4:
			if (!CheckType4Prerequisites())
				return false;
			break;

		case 6:
			if (!CheckType6Prerequisites())
				return false;
			else
			{
				if (TO_USER(pSkillCaster)->CheckExistItem(381001000))
					TO_USER(pSkillCaster)->RobItem(381001000);
			}
			break;
		}
	}

	if (pSkillCaster->isPlayer())
	{
		if (pSkill->bType[0] == 3)
		{
			_MAGIC_TYPE3 * pType3 = g_pMain->m_Magictype3Array.GetData(pSkill->iNum);
			_ITEM_TABLE * pTable;
			if (pType3 == nullptr)
				goto fail_return;

			if (!pSkillCaster->canUsePotions()
				&& pType3->bDirectType == 1	
				&& pType3->sFirstDamage > 0
				&& pSkill->iUseItem != 0
				&& (pTable = g_pMain->GetItemPtr(pSkill->iUseItem)) != nullptr
				&& pTable->m_bClass == 0)
				goto fail_return;
		}

		modulator = pSkill->sSkill % 10;  
		if( modulator != 0 ) {	
			Class = pSkill->sSkill / 10;
			if(Class != TO_USER(pSkillCaster)->GetClass()) goto fail_return;
			if((pSkill->sSkillLevel > TO_USER(pSkillCaster)->m_bstrSkill[modulator]) && TO_USER(pSkillCaster)->GetFame() != COMMAND_CAPTAIN) goto fail_return;
		}
		else if (pSkill->sSkillLevel > pSkillCaster->GetLevel()) 
			goto fail_return;

		if (pSkill->bType[0] == 1) 
		{
			if (pSkill->sSkill == 1055 || pSkill->sSkill == 2055) {
				if (TO_USER(pSkillCaster)->isWeaponsDisabled())
					return false;

				_ITEM_TABLE	*pLeftHand = TO_USER(pSkillCaster)->GetItemPrototype(LEFTHAND);
				_ITEM_TABLE	*pRightHand = TO_USER(pSkillCaster)->GetItemPrototype(RIGHTHAND);

				if ((pLeftHand != nullptr 
					&& !pLeftHand->isSword() && !pLeftHand->isAxe() 
					&& !pLeftHand->isMace() && !pLeftHand->isSpear())
					|| (pRightHand != nullptr 
					&& !pRightHand->isSword() && !pRightHand->isAxe() 
					&& !pRightHand->isMace() && !pRightHand->isSpear()))
					return false;
			}
			else if (pSkill->sSkill == 1056 || pSkill->sSkill == 2056) 
			{
				if (TO_USER(pSkillCaster)->isWeaponsDisabled())
					return false;

				_ITEM_TABLE	*pRightHand = TO_USER(pSkillCaster)->GetItemPrototype(RIGHTHAND);

				if (TO_USER(pSkillCaster)->GetItem(LEFTHAND)->nNum != 0
					|| (pRightHand != nullptr 
					&& !pRightHand->isSword() && !pRightHand->isAxe() 
					&& !pRightHand->isMace() && !pRightHand->isSpear()))
					return false;
			}
		}

		if (bOpcode == MAGIC_EFFECTING) 
		{
			CUser * pCaster = TO_USER(pSkillCaster);
			int total_hit = pSkillCaster->m_sTotalHit;

			if (pSkill->bType[0] == 2 && pSkill->bFlyingEffect != 0)
				return true;

#if 0 
			if (pSkill->bType[0] == 1 && sData[0] > 1)
				return true;
#endif

			if (pSkill->sMsp > pSkillCaster->GetMana())
				goto fail_return;

			if (pSkill->ssSp > pCaster->GetStamina())
				goto fail_return;

			if (pSkillCaster->isPlayer()
				&& (pSkill->bType[0] == 3 || pSkill->bType[0] == 4))
			{
				if (pSkill->iUseItem != 0) {
					_ITEM_TABLE* pItem = nullptr;	
					pItem = g_pMain->GetItemPtr(pSkill->iUseItem);
					if( !pItem ) return false;

					if ((pItem->m_bClass != 0 && !TO_USER(pSkillCaster)->JobGroupCheck(pItem->m_bClass))
						|| (pItem->m_bReqLevel != 0 && TO_USER(pSkillCaster)->GetLevel() < pItem->m_bReqLevel))	
						return false;
				}
			}
			if (pSkill->bType[0] != 4 || (pSkill->bType[0] == 4 && sTargetID == -1) && !pSkillCaster -> isBlinking())
			{
				pSkillCaster->MSpChange(-(pSkill->sMsp));
				pCaster->SpChange(-(pSkill->ssSp));
			}

			if (pSkill->sHP > 0 
				&& pSkill->sMsp == 0 
				&& pSkill->sHP < 10000)
			{
				if (pSkill->sHP > pSkillCaster->GetHealth()) goto fail_return;
				pSkillCaster->HpChange(-pSkill->sHP);
			}

			if (pSkill->sHP >= 10000)
			{
				if (pSkillCaster == pSkillTarget)
					return false;

				pSkillCaster->HpChange(-10000); 
			}
		}
	}

	return true;

fail_return: 
	SendSkillFailed();

	return false;
}

bool MagicInstance::ExecuteType1()
{	
	if (pSkill == nullptr)
		return false;

	_MAGIC_TYPE1* pType = g_pMain->m_Magictype1Array.GetData(nSkillID);
	if (pType == nullptr)
		return false;

	int damage = 0;
	bool bResult = false;

	if (pSkillTarget != nullptr && !pSkillTarget->isDead())
	{
		bResult = 1;

		uint16 sAdditionalDamage = pType->sAddDamage;

		if (pSkillCaster->isPlayer()
			&& pSkillTarget->isPlayer())
		{
			if (pSkillCaster->GetMap()->isWarZone())
				sAdditionalDamage /= 2;
			else
				sAdditionalDamage /= 3;
		}

		damage = pSkillCaster->GetDamage(pSkillTarget, pSkill);

		if (!pSkillTarget->m_bBlockPhysical)
			damage += sAdditionalDamage;

		if (pSkillCaster->GetZoneID() == ZONE_CHAOS_DUNGEON)
			damage = pType->sAddDamage / 10;

		pSkillTarget->HpChange(-damage, pSkillCaster);

		if (pSkillTarget->m_bReflectArmorType != 0 && pSkillCaster != pSkillTarget)
			ReflectDamage(damage, pSkillTarget);
	}

	sData[3] = (damage == 0 ? SKILLMAGIC_FAIL_ATTACKZERO : 0);

	if (pSkill->iNum !=106520 && pSkill->iNum !=106802 && pSkill->iNum !=206520 && pSkill->iNum !=105520 && pSkill->iNum !=205520 && pSkill->iNum !=206802 && pSkill->iNum !=106820 && pSkill->iNum !=206820)
		SendSkill();

	return bResult;
}

bool MagicInstance::ExecuteType2()
{
	if (pSkill == nullptr)
		return false;

	_MAGIC_TYPE2 *pType = g_pMain->m_Magictype2Array.GetData(nSkillID);
	if (pType == nullptr)
		return false;

	int damage = 0;
	bool bResult = false;
	float total_range = 0.0f;
	int sx, sz, tx, tz;
	int range = 0;

	if (pType->bNeedArrow > 0)
	{
		_ITEM_TABLE * pTable = nullptr;
		if (pSkillCaster->isPlayer())
		{
			if (TO_USER(pSkillCaster)->isWeaponsDisabled())
				return false;

			pTable = TO_USER(pSkillCaster)->GetItemPrototype(LEFTHAND);
			if (pTable == nullptr || !pTable->isBow())
			{
				pTable = TO_USER(pSkillCaster)->GetItemPrototype(RIGHTHAND);

				if (pTable == nullptr || !pTable->isBow())
					return false;
			}
		}
		else 
		{
			pTable = g_pMain->GetItemPtr(TO_NPC(pSkillCaster)->m_iWeapon_1);
			if (pTable == nullptr)
				return false; 
		}

		range = pTable->m_sRange;
	}
	else
	{
		range = pSkill->sRange;
	}

	if (pSkillTarget == nullptr || pSkillTarget->isDead())
		goto packet_send;

	total_range = pow(((pType->sAddRange * range) / 100.0f), 2.0f);
	sx = (int)pSkillCaster->GetX(); tx = (int)pSkillTarget->GetX();
	sz = (int)pSkillCaster->GetZ(); tz = (int)pSkillTarget->GetZ();

	if ((pow((float)(sx - tx), 2.0f) + pow((float)(sz - tz), 2.0f)) > total_range)
		goto packet_send;

	if (pSkillCaster->isPlayer())
	{
		CUser * pUser = TO_USER(pSkillCaster);
		Guard lock(pUser->m_arrowLock);

		if (pUser->m_flyingArrows.empty())
			goto packet_send;

		ArrowList::iterator arrowItr;
		bool bFoundArrow = false;
		for (auto itr = pUser->m_flyingArrows.begin(); itr != pUser->m_flyingArrows.end();)
		{
			if (UNIXTIME >= itr->tFlyingTime + ARROW_EXPIRATION_TIME)
			{
				itr = pUser->m_flyingArrows.erase(itr);
			}
			else
			{
				if (itr->nSkillID == nSkillID)
				{
					arrowItr = itr;
					bFoundArrow = true;
				}

				++itr;
			}
		}

		if (!bFoundArrow)
			goto packet_send;

		pUser->m_flyingArrows.erase(arrowItr);
	}

	damage = pSkillCaster->GetDamage(pSkillTarget, pSkill);

	pSkillTarget->HpChange(-damage, pSkillCaster);
	if (pSkillTarget->m_bReflectArmorType != 0 && pSkillCaster != pSkillTarget)
		ReflectDamage(damage, pSkillTarget);

	bResult = true;

packet_send:
	sData[3] = (damage == 0 ? SKILLMAGIC_FAIL_ATTACKZERO : 0);

	SendSkill();

	return bResult;
}

bool MagicInstance::ExecuteType3()
{	
	if (pSkill == nullptr)
		return false;

	_MAGIC_TYPE3* pType = g_pMain->m_Magictype3Array.GetData(nSkillID);
	if (pType == nullptr) 
		return false;

	int damage = 0, duration_damage = 0;
	vector<Unit *> casted_member;

	if (sTargetID == -1)
	{
		std::vector<uint16> unitList;
		g_pMain->GetUnitListFromSurroundingRegions(pSkillCaster, &unitList);
		if(pType->sFirstDamage > 0 || pType->sTimeDamage > 0)
			casted_member.push_back(pSkillCaster);
		foreach (itr, unitList)
		{		
			Unit * pTarget = g_pMain->GetUnitPtr(*itr);

			if(pTarget == nullptr)
				continue; 

			if (pTarget->isPlayer() && TO_USER(pTarget)->isGM())
				continue;

			if (pSkillCaster != pTarget
				&& !pTarget->isDead() && !pTarget->isBlinking() && pTarget->isAttackable()
				&& CMagicProcess::UserRegionCheck(pSkillCaster, pTarget, pSkill, pType->bRadius, sData[0], sData[2]))
				casted_member.push_back(pTarget);
		}

		if (casted_member.empty() || (sTargetID == -1 && casted_member.empty()))
		{
			SendSkill();
			return true;			
		}
	}
	else
	{
		if (pSkillTarget == nullptr 
			|| pSkillTarget->isDead() 
			|| (pSkillTarget->isPlayer() 
			&& TO_USER(pSkillTarget)->isBlinking())) 
			return false;

		casted_member.push_back(pSkillTarget);
	}

	if (pType->bDirectType == 18)
	{
		if (!pSkillCaster->isPlayer()
			|| !TO_USER(pSkillCaster)->hasFullAngerGauge())
			return false;

		TO_USER(pSkillCaster)->UpdateAngerGauge(0);
	}

	sData[1] = 1;
	foreach (itr, casted_member)
	{
		Unit * pTarget = *itr;

		if(pTarget == nullptr)
			continue;

		if (pSkill->sRange > 0 
			&& (pSkillCaster->GetDistanceSqrt(pTarget) >= (float)pSkill->sRange))
			continue;

		if ((pType->sFirstDamage < 0) && (pType->bDirectType == 1 || pType->bDirectType == 8) 
			&& (nSkillID < 400000) 
			&& (pType->bDirectType != 11 && pType->bDirectType != 13))
			damage = GetMagicDamage(pTarget, pType->sFirstDamage, pType->bAttribute);
		else 
			damage = pType->sFirstDamage;

		if (damage < 0 && pTarget->m_bBlockMagic)
			continue;

		if (pSkillCaster->isPlayer())
		{
			if (pSkillCaster->GetZoneID() == ZONE_SNOW_BATTLE && g_pMain->m_byBattleOpen == SNOW_BATTLE)
				damage = -10;
		}

		bool mSendStunCold = true;
		if (pType->bDirectType == 1 && nSkillID < 400000 
			&& (pType->bAttribute == AttributeLightning || pType->bAttribute == AttributeIce)
			&& pTarget->isPlayer())
		{
			if (pSkill->bSuccessRate < 100 && pSkill->bSuccessRate <= myrand(0, 100))
				mSendStunCold = false;
			else
			{
				uint16 nMaxRessitance = 250;
				uint16 nTargetResistance = pType->bAttribute == AttributeIce ? pTarget->m_sColdR : pTarget->m_sLightningR;

				if (nTargetResistance > nMaxRessitance)
					nMaxRessitance = nTargetResistance;

				if (nTargetResistance >= myrand(0, nMaxRessitance - nTargetResistance))
					mSendStunCold = false;
			}
		}
		if (pType->bDuration == 0) 
		{
			switch (pType->bDirectType)
			{
			case 1:
				if ((pTarget->isNPC() && pType->sTimeDamage > 0) || (pTarget->isNPC() && pType->sFirstDamage > 0))
					return false;

				if (damage > 0 && pSkillCaster->hasBuff(BUFF_TYPE_DAMAGE_DOUBLE)
					&& CheckPercent(500))
					damage *= 2;
				/*
				if (damage > 0 && pTarget->isDevil())						//Created by Anderson
				{
					if (pTarget->haveSkill())								//Edited by Obede
					{
						damage = 250 * damage / 100;;
					}
					else if (pTarget->haveSkill2())
					{
						damage = 280 * damage / 100;
					}
					else
						damage *= 2; 
				}*/

				pTarget->HpChangeMagic(damage, pSkillCaster, (AttributeType) pType->bAttribute);

				if (pTarget->m_bReflectArmorType != 0 && pTarget != pSkillCaster && damage < 0)
					ReflectDamage(damage, pTarget);

				break;
			case 2:
				if (!pTarget->isDead() && pTarget->isPlayer())
					pTarget->MSpChange(pType->sFirstDamage);
				else if (!pTarget->isDead())
					pTarget->HpChange(pType->sFirstDamage,pSkillCaster);
				break;
			case 3:
				pTarget->MSpChange(damage);
				break;

			case 4:
				if (pTarget->isPlayer())
				{
					if (damage > 0)
						TO_USER(pTarget)->ItemWoreOut(REPAIR_ALL, damage);
					else
						TO_USER(pTarget)->ItemWoreOut(ACID_ALL, -damage);
				}
				break;

			case 5:
				if (pType->sFirstDamage < 100)
					damage = (pType->sFirstDamage * pTarget->GetHealth()) / -100;
				else
					damage = (pTarget->GetMaxHealth() * (pType->sFirstDamage - 100)) / 100;

				pTarget->HpChangeMagic(damage, pSkillCaster);
				break;

			case 8:
				if (pType->sFirstDamage > 0)
				{
					if (pType->sFirstDamage < 100)
						damage = (pTarget->GetHealth() * 100) / pType->sFirstDamage;
					else
						damage = (pTarget->GetMaxHealth() - 100 * 100) / pType->sFirstDamage;
				}

				if (!pTarget->isDead() && pTarget->isPlayer())
				{	
					pTarget->HpChangeMagic(damage, pSkillCaster);
					pSkillCaster->HpChangeMagic(-(damage));
				}
				else
					pTarget->HpChange(damage,pSkillCaster);

				break;

			case 9:
				if (pType->sFirstDamage < 100)
					damage = (pType->sFirstDamage * pTarget->GetHealth()) / -100;
				else
					damage = (pTarget->GetMaxHealth() * (pType->sFirstDamage - 100)) / 100;

				pTarget->HpChangeMagic(damage, pSkillCaster);
				if (pTarget->isPlayer()) 
					pSkillCaster->HpChangeMagic(-(damage));
				break;

			case 11:
				pTarget->HpChange(damage, pSkillCaster);
				break;

			case 12:
				continue;

			case 13:
				if (pTarget->isPlayer() && CheckPercent(500)) 
				{
					TO_USER(pTarget)->ItemWoreOut(ATTACK, damage);
					TO_USER(pTarget)->ItemWoreOut(DEFENCE, damage);
				}
				break;

			case 16:
				if (pTarget->isPlayer())
				{
					pTarget->MSpChange(pType->sFirstDamage);
					pSkillCaster->HpChangeMagic(-(pType->sFirstDamage) / 2);
				}
				break;
			case 17:
				if (!pTarget->isNPC() && !pTarget->isDead() && pSkillCaster->GetZoneID() == ZONE_DELOS && !pSkillCaster->isDead())
				{
					pTarget->HpChangeMagic(pType->sFirstDamage,pSkillCaster, (AttributeType) pType->bAttribute);
				}
				break;
			case 19:
				if (pTarget->isPlayer())
				{
					pTarget->HpChangeMagic(damage / 10, pSkillCaster, (AttributeType) pType->bAttribute);

					if (pTarget != pSkillCaster)
						ReflectDamage(damage, pTarget);
				}
				break;
			case 255:
				if (TO_USER(pSkillCaster)->isPlayer())
				{

				}
				break;
			}
		}
		else if (pType->bDuration != 0) 
		{
			if (pType->bDirectType == 18)
				damage = -(int)(pSkillCaster->GetLevel() * 12.5);

			if (damage != 0)
				pTarget->HpChangeMagic(damage, pSkillCaster);

			if (pTarget->isAlive()) 
			{
				CUser *pUser = TO_USER(pSkillCaster);

				if (pType->bDirectType == 14)
					duration_damage = (int)(pSkillCaster->GetLevel() * (1 + pSkillCaster->GetLevel() / 30.0)) + 3;
				else if (pType->bDirectType == 19)
					duration_damage = (pType->sTimeDamage / 10);
				else if (pSkillCaster->isPlayer() && pUser->isKurPor())
					duration_damage = (pType->sTimeDamage * 2);
				else if (pType->sTimeDamage < 0 && pType->bAttribute != 4) 
					duration_damage = GetMagicDamage(pTarget, pType->sTimeDamage, pType->bAttribute);
				else 
					duration_damage = pType->sTimeDamage;

				if (duration_damage < 0 && pTarget->m_bBlockMagic)
					continue;

				if (pType->bDirectType == 18)
					duration_damage = -(int)((pSkillCaster->GetLevel() * 12.5) * (pType->bDuration / 2));

				for (int k = 0; k < MAX_TYPE3_REPEAT; k++) 
				{
					Unit::MagicType3 * pEffect = &pTarget->m_durationalSkills[k];

					if(pEffect == nullptr)
						continue; 

					if (pEffect->m_byUsed)
						continue;

					pEffect->m_byUsed = true;
					pEffect->m_tHPLastTime = 0;
					pEffect->m_bHPInterval = 2;	

					float tickCount = (float)pType->bDuration / (float)pEffect->m_bHPInterval;

					if (pSkillCaster->GetZoneID() == ZONE_CHAOS_DUNGEON)
						tickCount *=2;
					else
						tickCount = float(tickCount /1.5);

					pEffect->m_sHPAmount = (int16)(duration_damage / tickCount);

					pEffect->m_bTickCount = 0;
					pEffect->m_bTickLimit = (uint8) tickCount;
					pEffect->m_sSourceID = sCasterID;
					pEffect->m_byAttribute = pType->bAttribute;
					break;
				}

				pTarget->m_bType3Flag = true;
			}

			if (pTarget->isPlayer()
					&& pType->sTimeDamage < 0)
			{
				if (mSendStunCold)
					TO_USER(pTarget)->SendUserStatusUpdate(pType->bAttribute == POISON_R ? USER_STATUS_POISON : USER_STATUS_DOT, USER_STATUS_INFLICT);
			}
		}

		if (!mSendStunCold)
			sData[1] = 0;
		
		if (mSendStunCold && (LightStunSkills() && pTarget->isPlayer() || ColdSkills() && pTarget->isPlayer()))
		{
			MagicInstance instance;
			nSkillID += 80000;
			instance.nSkillID = nSkillID;
			if (LightStunSkillsNot() || ColdSkillsNot() && pTarget->isPlayer())
			{
				if (LightStunSkillsNot())
					TO_USER(pTarget)->SendUserStatusUpdate(USER_STATUS_POISON, USER_STATUS_INFLICT);
				else
					TO_USER(pTarget)->SendUserStatusUpdate(USER_STATUS_SPEED, USER_STATUS_INFLICT);

				ExecuteType4();
					
				_MAGIC_TYPE4 * pType2 = g_pMain->m_Magictype4Array.GetData(nSkillID);
				if (pType2 == nullptr)
					return false;
					
				uint8 bResult = 1;
				uint16 sDuration = pType2->sDuration;
				uint8 nTargetSpeedAmount = pType2->bSpeed;

				Unit * pTmp = (pSkillCaster->isPlayer() ? pSkillCaster : pTarget);
				int16 sDataCopy[] = 
				{
					sData[0], bResult, sData[2], sDuration,
					sData[4], pType2->bSpeed, sData[6]
				};

				sDataCopy[5] = nTargetSpeedAmount;
				BuildAndSendSkillPacket(pTmp, true, sCasterID, pTarget->GetID(), bOpcode, nSkillID, sDataCopy);
			}
		}
		else if (pSkill->bType[1] == 0 || pSkill->bType[1] == 3)
			BuildAndSendSkillPacket(pSkillCaster, true, sCasterID, pTarget->GetID(), bOpcode, nSkillID, sData);

		if (pType->bDirectType == 1 && damage > 0 && sCasterID != sTargetID)
		{
			Packet result(AG_HEAL_MAGIC);
			result << sCasterID;
			g_pMain->Send_AIServer(&result);
		}
	}

	if (sTargetID == -1 && pSkill->bType[0] == 3)
		SendSkill();

	return true;
}

bool MagicInstance::ExecuteType4()
{
	if (pSkill == nullptr)
		return false;

	_MAGIC_TYPE4* pType = g_pMain->m_Magictype4Array.GetData(nSkillID);
	if (pType == nullptr)
		return false;

	int damage = 0;
	vector<Unit *> casted_member;

	if (!bIsRecastingSavedMagic 
		&& sTargetID >= 0 
		&& (pSkillTarget && pSkillTarget->HasSavedMagic(nSkillID)))
		return false;

	if (sTargetID == -1)
	{
		std::vector<uint16> unitList;

		g_pMain->GetUnitListFromSurroundingRegions(pSkillCaster, &unitList);
		foreach (itr, unitList)
		{		
			Unit * pTarget = g_pMain->GetUnitPtr(*itr);

			if(pTarget == nullptr)
				continue; 

			if (TO_USER(pSkillCaster)->isInArena() && pSkillCaster == pTarget)
				continue;

			if (pTarget->isPlayer())
			{
				if (TO_USER(pTarget)->isGM())
					continue;

				if (pSkillCaster->GetNation() != pTarget->GetNation() || pTarget->GetZoneID() == ZONE_ARENA)
					TO_USER(pTarget)->RemoveStealth();
			}

			if (!pTarget->isDead() && !pTarget->isBlinking() && pTarget->isAttackable()
				&& CMagicProcess::UserRegionCheck(pSkillCaster, pTarget, pSkill, pType->bRadius, sData[0], sData[2]))
				casted_member.push_back(pTarget);
		}

		if (casted_member.empty())
		{		
			CUser * pCaster = TO_USER(pSkillCaster);
			if (pSkillCaster->isPlayer())
			{
				if (pSkill->bMoral == MORAL_PARTY_ALL)
					casted_member.push_back(pSkillCaster);
				else if (pSkill->bMoral == MORAL_ENEMY_PARTY)
					casted_member.push_back(pSkillCaster);
				else if (pSkill->bType[0] == 4)
				{
					SendSkill();
					return false;
				}
				else if (pSkill->bType[1] == 4)
					return false;
			}
		}
	}
	else 
	{
		if (pSkillTarget == nullptr 
			|| pSkillTarget->isDead() || (pSkillTarget->isBlinking() && !bIsRecastingSavedMagic)) 
			return false;

		casted_member.push_back(pSkillTarget);
	}

	foreach (itr, casted_member)
	{
		Unit * pTarget = *itr;

		if(pTarget == nullptr)
			continue;

		if (pSkill->sRange > 0 && (pSkillCaster->GetDistanceSqrt(pTarget) >= (float)pSkill->sRange) && pType->bBuffType != BUFF_TYPE_HP_MP)
			continue;

		if (pTarget->isPlayer())
		{
			if ((pSkillCaster->GetNation() != pTarget->GetNation()) || TO_USER(pTarget)->isInArena())
				TO_USER(pTarget)->RemoveStealth();
		}

		uint8 bResult = 1;
		_BUFF_TYPE4_INFO pBuffInfo;
		bool bAllowCastOnSelf = false;
		uint16 sDuration = pType->sDuration;
		uint8 nTargetSpeedAmount = pType->bSpeed;

		switch (pType->bBuffType)
		{
		case BUFF_TYPE_UNDEAD:
		case BUFF_TYPE_UNSIGHT:
		case BUFF_TYPE_BLOCK_PHYSICAL_DAMAGE:
		case BUFF_TYPE_BLOCK_MAGICAL_DAMAGE:
			if (!pSkillCaster->isPlayer() && pSkillCaster->GetZoneID() != ZONE_CHAOS_DUNGEON)
				continue;

			pTarget = pSkillCaster;
			bAllowCastOnSelf = true;
			break;
		}

		bool bBlockingDebuffs = pTarget->m_bBlockCurses;

		if (pType->isDebuff() && pTarget->m_bReflectCurses)
		{
			const short reflectChance = 25;
			if (CheckPercent(reflectChance * 10))
			{
				pTarget = pSkillCaster;
				bBlockingDebuffs = (pTarget->m_bBlockCurses || pTarget->m_bReflectCurses); 
				bAllowCastOnSelf = true;
			}
			else 
			{
				bBlockingDebuffs = true;
			}
		}

		pTarget->m_buffLock.lock();
		Type4BuffMap::iterator buffItr = pTarget->m_buffMap.find(pType->bBuffType);

		bool bSkillTypeAlreadyOnTarget = (!bIsRecastingSavedMagic && buffItr != pTarget->m_buffMap.end());

		pTarget->m_buffLock.unlock();

		if (bSkillTypeAlreadyOnTarget && pType->isDebuff())
		{
			CMagicProcess::RemoveType4Buff(pType->bBuffType, pTarget, false);
			bSkillTypeAlreadyOnTarget = false;
		}

		if (!bAllowCastOnSelf 
			&& pType->isDebuff() && pTarget == pSkillCaster)
			continue;

		if ((bSkillTypeAlreadyOnTarget && pType->isBuff())
				|| (pType->isDebuff() && bBlockingDebuffs)
				|| !CMagicProcess::GrantType4Buff(pSkill, pType, pSkillCaster, pTarget, bIsRecastingSavedMagic))
		{
			if (sTargetID != -1 
					&& (pType->isBuff() || (pType->isDebuff() && bBlockingDebuffs)))
			{
				bResult = 0;
				goto fail_return;
			}
			continue;
		}

		if (nSkillID > 500000 && pTarget->isPlayer())
		{
			if (!bIsRecastingSavedMagic)
				pTarget->InsertSavedMagic(nSkillID, pType->sDuration);
			else
				sDuration = pTarget->GetSavedMagicDuration(nSkillID);
		}

		if (pSkillCaster->isPlayer()
			&& (sTargetID != -1 && pSkill->bType[0] == 4))
		{
			CUser * pCaster = TO_USER(pSkillCaster);
			pSkillCaster->MSpChange( -(pSkill->sMsp) );
			pCaster->SpChange( -(pSkill->ssSp) );
		}

		if (!bSkillTypeAlreadyOnTarget)
		{
			pBuffInfo.m_nSkillID = nSkillID;
			pBuffInfo.m_bBuffType = pType->bBuffType;
			pBuffInfo.m_bIsBuff = pType->bIsBuff;

			pBuffInfo.m_bDurationExtended = false;
			pBuffInfo.m_tEndTime = UNIXTIME + sDuration;

			pTarget->AddType4Buff(pType->bBuffType, pBuffInfo);
		}

		bool mSendSpeed = true;
		if (pTarget -> isPlayer() || pTarget->isNPC())
		{
			if ((pSkill->bMoral == MORAL_ENEMY 
				|| pSkill->bMoral == MORAL_AREA_ENEMY) 
				&& (pType->bBuffType == BUFF_TYPE_SPEED2 
				|| pType->bBuffType == BUFF_TYPE_SPEED
				|| pType->bBuffType == BUFF_TYPE_STUN))
			{
				if (pSkill->bSuccessRate < 100 && pSkill->bSuccessRate <= myrand(0, 100))
					mSendSpeed = false;
				else
				{
					uint16 nMaxRessitance = 250;
					uint16 nTargetResistance = pType->bBuffType == BUFF_TYPE_SPEED2 ? pTarget->m_sColdR : pTarget->m_sLightningR;

					if (nTargetResistance > nMaxRessitance)
						nMaxRessitance = nTargetResistance;

					if (nTargetResistance >= myrand(0, nMaxRessitance - nTargetResistance))
						mSendSpeed = false;
				}

				if (mSendSpeed)
				{
					_MAGIC_TYPE4 * pTypeTarget;
					Guard lock(pTarget->m_buffLock);
					auto itr = pTarget->m_buffMap.find(BUFF_TYPE_SPEED);
					if (itr != pTarget->m_buffMap.end() && (pTypeTarget = g_pMain->m_Magictype4Array.GetData(itr->second.m_nSkillID)))
						nTargetSpeedAmount = pTypeTarget->bSpeed;
				}

				if (!mSendSpeed)
					goto fail_return;
			}
		}

		if (pTarget->isPlayer())
		{
			TO_USER(pTarget)->SetUserAbility();
			TO_USER(pTarget)->Send2AI_UserUpdateInfo();

			if (pType->isBuff() && pType->bBuffType == BUFF_TYPE_HP_MP)
				TO_USER(pTarget)->HpChange(pTarget->m_sMaxHPAmount);
		}

fail_return:
		if (pSkill->bType[1] == 0 || pSkill->bType[1] == 4)
		{
			Unit *pTmp = (pSkillCaster->isPlayer() ? pSkillCaster : pTarget);
			int16 sDataCopy[] = 
			{
				sData[0], bResult, sData[2], sDuration,
				sData[4], pType->bSpeed, sData[6]
			};

			if (!mSendSpeed)
			{
				sDataCopy[1] = 0;
				BuildAndSendSkillPacket(pTmp, true, sCasterID, pTarget->GetID(), bOpcode, nSkillID, sDataCopy);
			}
			else
				BuildAndSendSkillPacket(pTmp, true, sCasterID, pTarget->GetID(), bOpcode, nSkillID, sDataCopy);

			BuildAndSendSkillPacket(pTmp, true, sCasterID, pTarget->GetID(), bOpcode, nSkillID, sDataCopy);

			if ((pSkill->bMoral >= MORAL_ENEMY || pSkill->bMoral >= MORAL_AREA_ENEMY) && pTarget->isPlayer())
			{
				UserStatus status = USER_STATUS_POISON;
				if (pType->bBuffType == BUFF_TYPE_SPEED || pType->bBuffType == BUFF_TYPE_SPEED2)
					status = USER_STATUS_SPEED;

				TO_USER(pTarget)->SendUserStatusUpdate(status, USER_STATUS_INFLICT);
			}

			if (pType->bBuffType == BUFF_TYPE_DECREASE_RESIST
				|| pType->bBuffType == BUFF_TYPE_DISABLE_TARGETING)
				SendSkill();
		}

		if (bResult == 0
			&& pSkillCaster->isPlayer())
			SendSkillFailed((*itr)->GetID());
	}
	return true;
}

bool MagicInstance::ExecuteType5()
{
	if (!pSkillCaster->isPlayer()
		|| pSkill == nullptr)
		return false;

	_MAGIC_TYPE5* pType = g_pMain->m_Magictype5Array.GetData(nSkillID);
	if (pType == nullptr)
		return false;

	vector<CUser *> casted_member;

	if (sTargetID == -1)
	{
		SessionMap sessMap = g_pMain->m_socketMgr.GetActiveSessionMap();
		foreach (itr, sessMap)
		{
			CUser * pTUser = TO_USER(itr->second);
			if (!pTUser->isInGame())
				continue;

			if (pTUser->isDead() 
				&& (pType->bType != RESURRECTION && pType->bType != RESURRECTION_SELF))
				continue;

			if (!pTUser->isDead() 
				&& (pType->bType == RESURRECTION || pType->bType == RESURRECTION_SELF))
				continue;

			if (CMagicProcess::UserRegionCheck(pSkillCaster, pTUser, pSkill, pSkill->sRange, sData[0], sData[2]))
				casted_member.push_back(pTUser);
		}
	}
	else
	{
		if (pSkillTarget == nullptr
			|| !pSkillTarget->isPlayer())
			return false;

		if (pSkillTarget->isDead() 
			&& (pType->bType != RESURRECTION && pType->bType != RESURRECTION_SELF))
			return false;

		if (!pSkillTarget->isDead() 
			&& (pType->bType == RESURRECTION || pType->bType == RESURRECTION_SELF))
			return false;

		casted_member.push_back(TO_USER(pSkillTarget));
	}

	foreach (itr, casted_member)
	{
		Type4BuffMap::iterator buffIterator;
		CUser * pTUser = (*itr);

		if(pTUser == nullptr)
			continue; 

		int skillCount = 0;
		bool bRemoveDOT = false;

		switch (pType->bType)
		{
		case REMOVE_TYPE3:
			for (int i = 0; i < MAX_TYPE3_REPEAT; i++)
			{
				Unit::MagicType3 * pEffect = &pTUser->m_durationalSkills[i];

				if(pEffect == nullptr)
					continue; 

				if (!pEffect->m_byUsed)
					continue;

				if (pEffect->m_sHPAmount >= 0)
				{
					skillCount++;
					continue;
				}

				pEffect->Reset();
				Packet result(WIZ_MAGIC_PROCESS, uint8(MAGIC_DURATION_EXPIRED));
				result << uint8(200);
				pTUser->Send(&result); 
				bRemoveDOT = true;
			}

			if (skillCount == 0)
			{
				pTUser->m_bType3Flag = false;
				if (bRemoveDOT)
					pTUser->SendUserStatusUpdate(USER_STATUS_DOT, USER_STATUS_CURE);
			}
			break;

		case REMOVE_TYPE4:
			{
				Guard lock(pTUser->m_buffLock);
				Type4BuffMap buffMap = pTUser->m_buffMap;

				foreach (itr, buffMap)
				{
					if (itr->second.isDebuff())
					{
						CMagicProcess::RemoveType4Buff(itr->first, pTUser);

						if (pTUser->isLockableScroll(itr->second.m_bBuffType))
							pTUser->RecastLockableScrolls(itr->second.m_bBuffType);
					}
				}

				pTUser->SendUserStatusUpdate(USER_STATUS_POISON, USER_STATUS_CURE);
			} break;

		case RESURRECTION_SELF:
			if (pSkillCaster != pTUser || pTUser->m_iLostExp == 0)
				continue;

			pTUser->Regene(1,nSkillID);
			break;
		case RESURRECTION:
			if (pTUser->CheckExistItem(pSkill->iUseItem, pType->sNeedStone))
			{
				if (pTUser->RobItem(pSkill->iUseItem, pType->sNeedStone))
				{
					TO_USER(pSkillCaster)->GiveItem(pSkill->iUseItem, (pType->sNeedStone / 2) + 1);
					pTUser->Regene(1,nSkillID);
				}
			}
			break;

		case REMOVE_BLESS:
			{
				if (CMagicProcess::RemoveType4Buff(BUFF_TYPE_HP_MP, pTUser))
				{
					if (!pTUser->isDebuffed()) 
						pTUser->SendUserStatusUpdate(USER_STATUS_POISON, USER_STATUS_CURE);
				}
			} break;
		}

		if (pSkill->bType[1] == 0 || pSkill->bType[1] == 5)
		{
			sData[1] = 1;
			BuildAndSendSkillPacket(pSkillCaster, true, sCasterID, (*itr)->GetID(), bOpcode, nSkillID, sData); 
		}
	}

	return true;
}

bool MagicInstance::ExecuteType6()
{
	if (pSkill == nullptr
		|| !pSkillCaster->isPlayer())
		return false;

	_MAGIC_TYPE6 * pType = g_pMain->m_Magictype6Array.GetData(nSkillID);

	CUser * pCaster = TO_USER(pSkillCaster);
	uint16 sDuration = 0;

	if (pType == nullptr
			|| (pType->bUserSkillUse != TransformationSkillUseNPC
			&& pSkillCaster->GetMap()->canAttackOtherNation()
			&& (pSkillCaster->GetZoneID() > ELMORAD 
			&& !(pSkillCaster->GetZoneID() == ZONE_KARUS_ESLANT || pSkillCaster->GetZoneID() == ZONE_KARUS_ESLANT2 || pSkillCaster->GetZoneID() == ZONE_KARUS_ESLANT3
			|| pSkillCaster->GetZoneID() == ZONE_ELMORAD_ESLANT || pSkillCaster->GetZoneID() == ZONE_ELMORAD_ESLANT2 || pSkillCaster->GetZoneID() == ZONE_ELMORAD_ESLANT3)))
			|| (!bIsRecastingSavedMagic && pCaster->isTransformed())
			|| (pType->bUserSkillUse != TransformationSkillUseNPC && pSkillCaster->isBuffed(true))
			|| (pType->bNation != 0 && pType->bNation != pCaster->GetNation()))
	{
		if (bIsRecastingSavedMagic)
			Type6Cancel(true);

		return false;
	}

	if (!bIsRecastingSavedMagic)
	{
		if (pSkillTarget->HasSavedMagic(nSkillID))
			return false;

		if (pType->bUserSkillUse == TransformationMonster)
			pCaster->RobItem(pSkill->nBeforeAction);

		sDuration = pType->sDuration;
	}
	else 
	{
		int16 tmp = pSkillCaster->GetSavedMagicDuration(nSkillID);

		if (tmp <= 0)
			return false;

		sDuration = tmp;
	}

	switch (pType->bUserSkillUse)
	{
	case TransformationSkillUseMonster:
		pCaster->m_transformationType = TransformationMonster;
		break;

	case TransformationSkillUseNPC:
		pCaster->m_transformationType = TransformationNPC;
		break;

	case TransformationSkillUseSiege:
	case TransformationSkillUseSiege2:
		pCaster->m_transformationType = TransformationSiege;
		break;

	default:
		return false;
	}

	pCaster->m_sTransformID = pType->sTransformID;
	pCaster->m_tTransformationStartTime = UNIXTIME;
	pCaster->m_sTransformationDuration = sDuration;

	pSkillCaster->StateChangeServerDirect(3, nSkillID);

	if (pType->bUserSkillUse == TransformationSkillUseSiege 
		|| pType->bUserSkillUse == TransformationSkillUseSiege2)
	{	
		pCaster->m_sTotalHit	= pType->sTotalHit;
		pCaster->m_sTotalAc		= pType->sTotalAc;
		pCaster->m_iMaxHp		= pType->sMaxHp;
		pCaster->m_iMaxMp		= pType->sMaxMp;
		pCaster->m_sSpeed		= pType->bSpeed;
		pCaster->m_sFireR		= pType->sTotalFireR;
		pCaster->m_sColdR		= pType->sTotalColdR;
		pCaster->m_sLightningR	= pType->sTotalLightningR;
		pCaster->m_sMagicR		= pType->sTotalMagicR;
		pCaster->m_sDiseaseR	= pType->sTotalDiseaseR;
		pCaster->m_sPoisonR		= pType->sTotalPoisonR;

		pCaster->UpdateStatusCSW();
	}

	sData[1] = 1;
	sData[3] = sDuration;
	SendSkill();

	pSkillCaster->InsertSavedMagic(nSkillID, sDuration);
	return true;
}

bool MagicInstance::ExecuteType7()
{
	if (pSkill == nullptr)
		return false;

	_MAGIC_TYPE7* pType = g_pMain->m_Magictype7Array.GetData(nSkillID);
	if (pType == nullptr)
		return false;

	vector<Unit *> casted_member;

	int damage = pType->sDamage;

	if (sTargetID == -1)
	{
		std::vector<uint16> unitList;
		g_pMain->GetUnitListFromSurroundingRegions(pSkillCaster, &unitList);
		if(pType->sDamage > 0)
			casted_member.push_back(pSkillCaster);

		foreach (itr, unitList)
		{		
			Unit * pTarget = g_pMain->GetUnitPtr(*itr);

			if(pTarget == nullptr)
				continue; 

			if (pTarget->isPlayer() && TO_USER(pTarget)->isGM())
				continue;

			if (pSkillCaster != pTarget && !pTarget->isDead() && !pTarget->isBlinking() && pTarget->isAttackable()
				&& CMagicProcess::UserRegionCheck(pSkillCaster, pTarget, pSkill, pType->bRadius, sData[0], sData[2]))
				casted_member.push_back(pTarget);
		}

		if (casted_member.empty() || (sTargetID == -1 && casted_member.empty()))
			return false;
	}
	else
	{
		if (pSkillTarget != nullptr && !pSkillTarget->isDead())
		{
			if (pType->bTargetChange == 1)
			{
				if (damage < 0)
					return false;

				pSkillTarget->HpChange(-damage, pSkillCaster);

				return true;
			}
		}
	}

	foreach (itr, casted_member)
	{
		Unit * pTarget = *itr;

		if(pTarget == nullptr)
			continue;

		if (pType->bTargetChange == 1)
		{
			if (damage < 0)
				continue;

			pTarget->HpChange(-damage, pSkillCaster);
		}
	}

	return false;
}

bool MagicInstance::ExecuteType8()
{	
	if (pSkill == nullptr)
		return false;

	_MAGIC_TYPE8* pType = g_pMain->m_Magictype8Array.GetData(nSkillID);
	if (pType == nullptr)
		return false;

	vector<CUser *> casted_member;

	if (sTargetID == -1)
	{
		SessionMap sessMap = g_pMain->m_socketMgr.GetActiveSessionMap();
		foreach (itr, sessMap)
		{		
			CUser* pTUser = TO_USER(itr->second);
			if (CMagicProcess::UserRegionCheck(pSkillCaster, pTUser, pSkill, pType->sRadius, sData[0], sData[2]))
				casted_member.push_back(pTUser);
		}

		if (casted_member.empty()) 
			return false;	
	}
	else 
	{
		CUser* pTUser = g_pMain->GetUserPtr(sTargetID);
		if (pTUser == nullptr) 
			return false;

		casted_member.push_back(pTUser);
	}

	foreach (itr, casted_member)
	{
		CUser* pTUser = *itr;

		if(pTUser == nullptr)
			continue; 

		uint8 bResult = 0;
		_OBJECT_EVENT* pEvent = nullptr;

		if (pType->bWarpType != 11) 
		{ 
			if (pTUser->isDead()
					|| !pTUser->canTeleport())
					goto packet_send;
		}
		else if (!pTUser->isDead()) 
			goto packet_send;

		if (pTUser->m_bWarp)
			goto packet_send;

		switch(pType->bWarpType)
		{
		case 0:
		{
			CUser * pCaster = TO_USER(pSkillCaster);
			if (KurianStuns() && (*itr)->isPlayer() && pCaster->isPassiveRush())
			{
				MagicInstance instance;
				nSkillID += 80000;
				instance.nSkillID = nSkillID;
				if (KurianStunsNot() && (*itr)->isPlayer())
				{
					(*itr)->SendUserStatusUpdate(USER_STATUS_POISON, USER_STATUS_INFLICT);

					ExecuteType4();
					
					_MAGIC_TYPE4* pType2 = g_pMain->m_Magictype4Array.GetData(nSkillID);
					nSkillID -= 80000;

					if (pType2 == nullptr)
						return false;
					
					uint8 bResult = 1;
					uint16 sDuration = pType2->sDuration;
					uint8 nTargetSpeedAmount = pType2->bSpeed;

					Unit *pTmp = (pSkillCaster->isPlayer() ? pSkillCaster : *itr);
					int16 sDataCopy[] = 
					{
						sData[0], bResult, sData[2], sDuration,
						sData[4], pType2->bSpeed, sData[6]
					};
				}
			}
		}
			break;
		case 1:
			if (pTUser->GetZoneID() > ZONE_BIFROST
				&& (nSkillID == 109035
				|| nSkillID == 110035
				|| nSkillID == 209035
				|| nSkillID == 210035))
			{
				SendSkillFailed();
				return false;
			}

			sData[1] = 1;

			BuildAndSendSkillPacket(*itr, true, sCasterID, (*itr)->GetID(), bOpcode, nSkillID, sData); 

			if (pTUser->GetMap() == nullptr)
				continue;

			pEvent = pTUser->GetMap()->GetObjectEvent(pTUser->m_sBind);

			if (pEvent != nullptr)
				pTUser->Warp(uint16(pEvent->fPosX * 10), uint16(pEvent->fPosZ * 10));	
			else if (pTUser->GetZoneID() <= ELMORAD || pTUser->GetMap()->isWarZone() || pTUser->GetMap()->canAttackOtherNation())
			{
				_START_POSITION * pStartPosition = g_pMain->m_StartPositionArray.GetData(pTUser->GetZoneID());
				if (pStartPosition)
					pTUser->Warp((uint16)((pTUser->GetNation() == KARUS ? pStartPosition->sKarusX : pStartPosition->sElmoradX) + myrand(0, pStartPosition->bRangeX)) * 10,(uint16)((pTUser->GetNation() == KARUS ? pStartPosition->sKarusZ : pStartPosition->sElmoradZ) + myrand(0, pStartPosition->bRangeZ)) * 10);
				else
					return false;
			}
			else
				pTUser->Warp(uint16(pTUser->GetMap()->m_fInitX * 10), uint16(pTUser->GetMap()->m_fInitZ * 10));

			break;
		case 2:		// Send target to teleport point WITHIN the zone.
			break;
		case 3:		// Send target to teleport point OUTSIDE the zone.
			break;
		case 5:		// Send target to a hidden zone.
			break;

		case 11:
			{
				sData[1] = 1;
				BuildAndSendSkillPacket(*itr, true, sCasterID, (*itr)->GetID(), bOpcode, nSkillID, sData); 

				pTUser->m_bResHpType = USER_STANDING;
				pTUser->HpChange(pTUser->m_iMaxHp, pSkillCaster);
				pTUser->ExpChange( pType->sExpRecover/100 ,true);

				Packet result(AG_USER_REGENE);
				result << uint16((*itr)->GetSocketID()) << uint16(pTUser->GetHealth());
				g_pMain->Send_AIServer(&result);
			} break;

		case 12:
			if(pTUser->GetZoneID() == ZONE_FORGOTTEN_TEMPLE 
				|| (pTUser->GetZoneID() > ZONE_BIFROST && (nSkillID == 490042 || nSkillID == 490050)))
			{
				SendSkillFailed();
				return false;
			}
			if (pSkillCaster->GetZoneID() != pTUser->GetZoneID()
					|| pSkillCaster == pTUser)
					goto packet_send;

			sData[1] = 1;
			BuildAndSendSkillPacket(*itr, true, sCasterID, (*itr)->GetID(), bOpcode, nSkillID, sData); 
			pTUser->Warp(pSkillCaster->GetSPosX(), pSkillCaster->GetSPosZ());
			break;

		case 13:		
			if (pSkillCaster->GetZoneID() == pTUser->GetZoneID())
				goto packet_send;

			sData[1] = 1;
			BuildAndSendSkillPacket(*itr, true, sCasterID, (*itr)->GetID(), bOpcode, nSkillID, sData); 

			pTUser->ZoneChange(pSkillCaster->GetZoneID(), pSkillCaster->GetX(), pSkillCaster->GetZ()) ;
			pTUser->UserInOut(INOUT_RESPAWN);
			break;

		case 20:
			{
				float warp_x = pTUser->GetX() - pTUser->m_oldx, 
					warp_z = pTUser->GetZ() - pTUser->m_oldz;

				float	distance = sqrtf(warp_x*warp_x + warp_z*warp_z);
				if (distance == 0.0f)
					goto packet_send;

				warp_x /= distance; warp_z /= distance;
				warp_x *= pType->sRadius; warp_z *= pType->sRadius;
				warp_x += pTUser->m_oldx; warp_z += pTUser->m_oldz;

				sData[1] = 1;
				BuildAndSendSkillPacket(*itr, true, sCasterID, (*itr)->GetID(), bOpcode, nSkillID, sData); 
				pTUser->Warp(uint16(warp_x * 10), uint16(warp_z * 10));
			} break;

		case 21:
			{
				MonsterSummonList * pMonsterSummonList = g_pMain->m_MonsterSummonList.GetData(1);

				if (pMonsterSummonList)
				{
					int nCurrentMonster = 0;
					int nRandom = myrand(0, (int32)pMonsterSummonList->size());

					for (std::vector<_MONSTER_SUMMON_LIST>::iterator itr = pMonsterSummonList->begin(); itr != pMonsterSummonList->end(); ++itr)
					{
						if (nCurrentMonster == nRandom)
						{
							g_pMain->SpawnEventNpc(itr->sSid,true,pSkillCaster->GetZoneID(),pSkillCaster->GetX(),pSkillCaster->GetY(),pSkillCaster->GetZ(),1,(pType->sRadius/1000));
							break;
						}

						nCurrentMonster++;
					}
				}
			}
			break;
		case 25:
			float dest_x, dest_z = 0.0f;
			if (pTUser->GetZoneID() != pSkillCaster->GetZoneID()
				|| (pSkill->bMoral < MORAL_ENEMY && pSkillCaster->isHostileTo(pTUser))
				|| (pSkill->iNum > 500000 && pSkillCaster->GetZoneID() > ZONE_MORADON))
				return false;

			dest_x = pTUser->GetX();
			dest_z = pTUser->GetZ();

			if (pSkillCaster->isPlayer() && (pSkillCaster->GetDistanceSqrt(pSkillTarget) <= (float)pType->sRadius))
				TO_USER(pSkillCaster)->Warp(uint16(dest_x * 10), uint16(dest_z * 10));
			else
				SendSkillFailed();
			break;
		}

		bResult = 1;

packet_send:
		sData[1] = bResult;
		BuildAndSendSkillPacket(pSkillCaster, true, sCasterID, (*itr)->GetID(), bOpcode, nSkillID, sData); 
	}
	return true;
}

bool MagicInstance::ExecuteType9()
{
	if (pSkill == nullptr
			|| !pSkillCaster->isPlayer())
			return false;

	_MAGIC_TYPE9* pType = g_pMain->m_Magictype9Array.GetData(nSkillID);
	if (pType == nullptr)
		return false;

	CUser * pCaster = TO_USER(pSkillCaster);

	if(pCaster == nullptr)
		return false; 

	Guard lock(pCaster->m_buffLock);
	Type9BuffMap & buffMap = pCaster->m_type9BuffMap;

	if (buffMap.find(pType->bStateChange) != buffMap.end())
	{
		sData[1] = 0;
		SendSkillFailed();
		return false;
	}

	sData[1] = 1;

	if (pType->bStateChange <= 2 && pCaster->canStealth() && pCaster->GetZoneID() != ZONE_FORGOTTEN_TEMPLE)
	{
		if (pCaster->m_bInvisibilityType != INVIS_NONE)
		{
			sData[1] = 0;
			SendSkillFailed();
			return false;
		}

		if (pSkillTarget->isPlayer())
		{
			pCaster->StateChangeServerDirect(7, pType->bStateChange);
			buffMap.insert(std::make_pair(pType->bStateChange, _BUFF_TYPE9_INFO(nSkillID, UNIXTIME + pType->sDuration)));
		}

		SendSkill();
	}
	else if (pType->bStateChange >= 3 && pType->bStateChange <= 4)
	{
		Packet result(WIZ_STEALTH, uint8(1));
		result << pType->sRadius;

		if (pCaster->isInParty() && pType->bStateChange == 4)
		{
			_PARTY_GROUP * pParty = g_pMain->GetPartyPtr(pCaster->GetPartyID());
			if (pParty == nullptr)
				return false;

			for (int i = 0; i < MAX_PARTY_USERS; i++)
			{
				CUser *pUser = g_pMain->GetUserPtr(pParty->uid[i]);
				if (pUser == nullptr)
					continue;

				Guard buffLock(pUser->m_buffLock);

				if (pUser->m_type9BuffMap.find(pType->bStateChange) 
					!= pUser->m_type9BuffMap.end())
					continue;

				pUser->m_type9BuffMap.insert(std::make_pair(pType->bStateChange, _BUFF_TYPE9_INFO(nSkillID, UNIXTIME + pType->sDuration)));
				pUser->Send(&result);

				BuildAndSendSkillPacket(pUser, false, sCasterID, pUser->GetID(), bOpcode, nSkillID, sData);
			}
		}
		else
		{
			buffMap.insert(std::make_pair(pType->bStateChange, _BUFF_TYPE9_INFO(nSkillID, UNIXTIME + pType->sDuration)));
			pCaster->Send(&result);

			SendSkill(false);
		}
	}
	else if (pType->bStateChange == 8)
	{
		
	}
	else if (pType->bStateChange == 9)
	{
		buffMap.insert(std::make_pair(pType->bStateChange, _BUFF_TYPE9_INFO(nSkillID, UNIXTIME + pType->sDuration)));
		g_pMain->SpawnEventNpc(pType->sMonsterNum,true,pCaster->GetZoneID(),pCaster->GetX(),pCaster->GetY(),pCaster->GetZ(),1,2, pType->sDuration, pCaster->GetNation(), pCaster->GetSocketID());
	}

	return true;
}

short MagicInstance::GetMagicDamage(Unit *pTarget, int total_hit, int attribute)
{	
	short damage = 0, pDamage = 0, temp_hit = 0, righthand_damage = 0, attribute_damage = 0;
	int random = 0, total_r = 0 ;
	uint8 result;

	if (pTarget == nullptr
		|| pSkillCaster == nullptr
		|| pTarget->isDead()
		|| pSkillCaster->isDead())
		return 0;

	if (pTarget->isPlayer()
		&& pSkillCaster->isPlayer())
	{
		pSkillCaster->OnAttack(pTarget, AttackTypeMagic);
		pTarget->OnDefend(pSkillCaster, AttackTypeMagic);
	}

	if (pTarget->m_bBlockMagic)
		return 0;

	int16 sMagicAmount = 0;
	if (pSkillCaster->isNPC())
	{
		result = pSkillCaster->GetHitRate(pTarget->m_fTotalHitrate / pSkillCaster->m_fTotalEvasionrate); 
	}
	else
	{
		CUser *pUser = TO_USER(pSkillCaster);

		uint8 bCha = pUser->GetStat(STAT_CHA);
		if (bCha > 86)
			sMagicAmount = bCha - 86;

		sMagicAmount += pUser->m_sMagicAttackAmount;
		total_hit = total_hit * bCha / 186;
		if (pUser->m_sMagicAttackAmount != 0)
			total_hit = (total_hit - sMagicAmount);
		result = SUCCESS;
	}

	if (result != FAIL) 
	{
		switch (attribute)
		{
		case FIRE_R: 
			total_r = (pTarget->m_sFireR + pTarget->m_bAddFireR) * pTarget->m_bPctFireR / 100;
			break;
		case COLD_R:
			total_r = (pTarget->m_sColdR + pTarget->m_bAddColdR) * pTarget->m_bPctColdR / 100;
			break;
		case LIGHTNING_R:
			total_r = (pTarget->m_sLightningR + pTarget->m_bAddLightningR) * pTarget->m_bPctLightningR / 100;
			break;
		case MAGIC_R:
			total_r = (pTarget->m_sMagicR + pTarget->m_bAddMagicR) * pTarget->m_bPctMagicR / 100;
			break;
		case DISEASE_R:
			total_r = (pTarget->m_sDiseaseR + pTarget->m_bAddDiseaseR) * pTarget->m_bPctDiseaseR / 100;
			break;
		case POISON_R:			
			total_r = (pTarget->m_sPoisonR + pTarget->m_bAddPoisonR) * pTarget->m_bPctPoisonR / 100;
			break;
		}

		total_r += pTarget->m_bResistanceBonus;

		if (pSkillCaster->isPlayer()) 
		{
			CUser *pUser = TO_USER(pSkillCaster);

			_ITEM_TABLE *pRightHand = pUser->GetItemPrototype(RIGHTHAND);
			if (!pUser->isWeaponsDisabled()
				&& pRightHand != nullptr && pRightHand->isStaff()
				&& pUser->GetItemPrototype(LEFTHAND) == nullptr)
			{
				Guard lock(pSkillCaster->m_equippedItemBonusLock);
				righthand_damage = pRightHand->m_sDamage + pUser->m_bAddWeaponDamage;
				auto itr = pSkillCaster->m_equippedItemBonuses.find(RIGHTHAND);
				if (itr != pSkillCaster->m_equippedItemBonuses.end())
				{
					auto bonusItr = itr->second.find(attribute);
					if (bonusItr != itr->second.end()) 
						attribute_damage *= 2; 
				}
			}
			else 
			{
				righthand_damage = 0;
			}

			Guard lock(pSkillCaster->m_equippedItemBonusLock);
			foreach (itr, pSkillCaster->m_equippedItemBonuses)
			{
				uint8 bSlot = itr->first;
				foreach (bonusItr, itr->second)
				{
					uint8 bType = bonusItr->first; 
					int16 sAmount = bonusItr->second;
					int16 sTempResist = 0;

					switch (bType)
					{
					case ITEM_TYPE_FIRE: 
						sTempResist = (pTarget->m_sFireR + pTarget->m_bAddFireR) * pTarget->m_bPctFireR / 100;
						break;
					case ITEM_TYPE_COLD:
						sTempResist = (pTarget->m_sColdR + pTarget->m_bAddColdR) * pTarget->m_bPctColdR / 100;
						break;
					case ITEM_TYPE_LIGHTNING:
						sTempResist = (pTarget->m_sLightningR + pTarget->m_bAddLightningR) * pTarget->m_bPctLightningR / 100;
						break;
					case ITEM_TYPE_POISON:
						sTempResist = (pTarget->m_sPoisonR + pTarget->m_bAddPoisonR) * pTarget->m_bPctPoisonR / 100;
						break;
					}

					sTempResist += pTarget->m_bResistanceBonus;
					if (bType >= ITEM_TYPE_FIRE 
						&& bType <= ITEM_TYPE_POISON)
					{
						if (sTempResist > 200) 
							sTempResist = 200;

						righthand_damage += sAmount - sAmount * sTempResist / 200;
					}
				}
			}

		}

		damage = (230 * total_hit / (total_r + 250));
		random = myrand(0, damage);
		damage = (short)(random * 0.3f + (damage * 0.85f)) - sMagicAmount;

		if (pSkillCaster->isNPC())
			damage -= ((3 * righthand_damage) + (3 * attribute_damage));
		else if (attribute != MAGIC_R)
			damage -= (short)(((righthand_damage * 0.8f) + (righthand_damage * pSkillCaster->GetLevel()) / 60) + ((attribute_damage * 0.8f) + (attribute_damage * pSkillCaster->GetLevel()) / 30));
		if (pTarget->m_bMagicDamageReduction < 100)
			damage = damage * pTarget->m_bMagicDamageReduction / 100;
	}

	GetWeatherDamage(damage, attribute);


	pDamage = damage /6;

	if (pTarget->isPlayer())
		damage = (damage /3) + pDamage;

	if (damage > MAX_DAMAGE)
		damage = MAX_DAMAGE;

/*		
	if (pSkillCaster->isPlayer())
	{
		CUser *pUser = TO_USER(pSkillCaster);
		_MAGIC_TYPE3 * pMagic = g_pMain->m_Magictype3Array.GetData(nSkillID);

		if (pMagic != nullptr && pUser != nullptr && pUser->isMage())
		{
			if (pMagic->bAttribute == AttributeFire)
				damage += 40 * damage / 100;
			else if (pMagic->bAttribute == AttributeIce
				|| pMagic->bAttribute == AttributeLightning)
				damage += 20 * damage / 100;
		}
	}
	
*/
	return damage;
}

int32 MagicInstance::GetWeatherDamage(int32 damage, int attribute)
{
	if ((g_pMain->m_byWeather == WEATHER_FINE && attribute == AttributeFire)
		|| (g_pMain->m_byWeather == WEATHER_RAIN && attribute == AttributeLightning)
		|| (g_pMain->m_byWeather == WEATHER_SNOW && attribute == AttributeIce))
		damage = (damage * 110) / 100;

	return damage;
}

void MagicInstance::Type6Cancel(bool bForceRemoval /*= false*/)
{
	if (!pSkillCaster->isPlayer() || !TO_USER(pSkillCaster)->isTransformed())
		return;

	Packet result(WIZ_MAGIC_PROCESS, uint8(MAGIC_CANCEL_TRANSFORMATION));
	TO_USER(pSkillCaster)->m_transformationType = TransformationNone;
	TO_USER(pSkillCaster)->Send(&result);
	TO_USER(pSkillCaster)->SetUserAbility();
	TO_USER(pSkillCaster)->RemoveSavedMagic(nSkillID);
	TO_USER(pSkillCaster)->StateChangeServerDirect(3, ABNORMAL_NORMAL);
	TO_USER(pSkillCaster)->m_savedMagicMap.erase(TO_USER(pSkillCaster)->m_bAbnormalType);
}

void MagicInstance::Type9Cancel(bool bRemoveFromMap /*= true*/)
{
	if (pSkillCaster == nullptr
		|| !pSkillCaster->isPlayer())
		return;

	_MAGIC_TYPE9 * pType = g_pMain->m_Magictype9Array.GetData(nSkillID);
	if (pType == nullptr)
		return;

	uint8 bResponse = 0;
	CUser * pCaster = TO_USER(pSkillCaster);
	Guard lock(pCaster->m_buffLock);
	Type9BuffMap & buffMap = pCaster->m_type9BuffMap;

	if (buffMap.find(pType->bStateChange) == buffMap.end())
		return;

	if (bRemoveFromMap)
		buffMap.erase(pType->bStateChange);

	if (pType->bStateChange <= 2 
		|| (pType->bStateChange >= 5 && pType->bStateChange < 7))
	{
		pCaster->StateChangeServerDirect(7, INVIS_NONE);
		bResponse = 91;
	}
	else if (pType->bStateChange >= 3 && pType->bStateChange <= 4) 
	{
		pCaster->InitializeStealth();
		bResponse = 92;
	}
	else if (pType->bStateChange == 7)
	{
		Packet pet(WIZ_PET, uint8(1));
		pet << uint16(1) << uint16(6);
		pCaster->Send(&pet);
		bResponse = 93;
	}
	else if (pType->bStateChange == 9)
	{
		g_pMain->KillNpc(pCaster->GetSocketID());
	}

	Packet result(WIZ_MAGIC_PROCESS, uint8(MAGIC_DURATION_EXPIRED));
	result << bResponse;
	pCaster->Send(&result);
}

void MagicInstance::Type4Cancel()
{
	if (pSkill == nullptr
		|| pSkillTarget != pSkillCaster)
		return;

	_MAGIC_TYPE4* pType = g_pMain->m_Magictype4Array.GetData(nSkillID);
	if (pType == nullptr
		|| pType->isDebuff())
		return;

	if (nSkillID > 500000 
		&& TO_USER(pSkillCaster)->isLockableScroll(pType->bBuffType)
		&& pSkillCaster->hasDebuff(pType->bBuffType))
		return;

	if (!CMagicProcess::RemoveType4Buff(pType->bBuffType, TO_USER(pSkillCaster)))
		return;

	TO_USER(pSkillCaster)->RemoveSavedMagic(nSkillID);
}

void MagicInstance::Type3Cancel()
{
	if (pSkill == nullptr
		|| pSkillCaster != pSkillTarget)
		return;

	_MAGIC_TYPE3* pType = g_pMain->m_Magictype3Array.GetData(nSkillID);
	if (pType == nullptr)
		return;

	for (int i = 0; i < MAX_TYPE3_REPEAT; i++)
	{
		Unit::MagicType3 * pEffect = &pSkillCaster->m_durationalSkills[i];

		if(pEffect == nullptr)
			continue; 

		if (!pEffect->m_byUsed
					|| pEffect->m_sHPAmount <= 0)
					continue;

		pEffect->Reset();
		break;
	}

	if (pSkillCaster->isPlayer())
	{
		Packet result(WIZ_MAGIC_PROCESS, uint8(MAGIC_DURATION_EXPIRED));
		result << uint8(100);
		TO_USER(pSkillCaster)->Send(&result); 
	}

	int buff_test = 0;
	for (int j = 0; j < MAX_TYPE3_REPEAT; j++)
	{
		if (pSkillCaster->m_durationalSkills[j].m_byUsed)
		{
			buff_test++;
			break;
		}
	}

	if (buff_test == 0) 
		pSkillCaster->m_bType3Flag = false;	

	if (pSkillCaster->isPlayer() 
		&& !pSkillCaster->m_bType3Flag)
		TO_USER(pSkillCaster)->SendUserStatusUpdate(USER_STATUS_DOT, USER_STATUS_CURE);
}

void MagicInstance::Type4Extend()
{
	if (pSkill == nullptr
			|| !pSkillCaster->isPlayer()
			|| nSkillID >= 500000)
			return;

	_MAGIC_TYPE4 *pType = g_pMain->m_Magictype4Array.GetData(nSkillID);
	if (pType == nullptr
		|| pType->isDebuff())
		return;

	Guard lock(pSkillTarget->m_buffLock);
	Type4BuffMap::iterator itr = pSkillTarget->m_buffMap.find(pType->bBuffType);

	if (itr == pSkillCaster->m_buffMap.end()
			|| itr->second.m_bDurationExtended)
			return;

	bool bItemFound = false;
	for (int i = SLOT_MAX; i < INVENTORY_TOTAL; i++)
	{
		_ITEM_DATA * pItem = nullptr;
		_ITEM_TABLE * pTable = TO_USER(pSkillCaster)->GetItemPrototype(i, pItem);
		if (pTable == nullptr
			|| pTable->m_bKind != 255
			|| pTable->m_iEffect1 == 0)
			continue;

		_MAGIC_TABLE * pEffect = g_pMain->m_MagictableArray.GetData(pTable->m_iEffect1);
		if (pEffect == nullptr
			|| pEffect->bMoral != MORAL_EXTEND_DURATION
			|| !TO_USER(pSkillCaster)->RobItem(i, pTable))
			continue;

		bItemFound = true;
		break;
	}

	if (!bItemFound)
		return;

	itr->second.m_tEndTime += pType->sDuration;

	itr->second.m_bDurationExtended = true;

	Packet result(WIZ_MAGIC_PROCESS, uint8(MAGIC_TYPE4_EXTEND));
	result << uint32(nSkillID);
	TO_USER(pSkillTarget)->Send(&result);
}

void MagicInstance::ReflectDamage(int32 damage, Unit * pTarget)
{
	if (pSkillCaster == nullptr
		|| pTarget == nullptr)
		return;

	if (damage < 0)
		damage *= -1;

	int16 total_resistance_caster = 0;
	int32 reflect_damage = 0;

	switch (pTarget->m_bReflectArmorType)
	{
	case FIRE_DAMAGE:
		total_resistance_caster = (pSkillCaster->m_sFireR + pSkillCaster->m_bAddFireR) * pTarget->m_bPctFireR / 100;
		reflect_damage = ((230 * damage) / (total_resistance_caster + 250)) / 100 * 35;
		pSkillCaster->HpChange(-damage, pTarget);
		break;

	case ICE_DAMAGE:
		total_resistance_caster = (pSkillCaster->m_sColdR + pSkillCaster->m_bAddColdR) * pTarget->m_bPctColdR / 100;
		reflect_damage = ((230 * damage) / (total_resistance_caster + 250)) / 100 * 35;
		pSkillCaster->HpChange(-damage, pTarget);
		break;

	case LIGHTNING_DAMAGE:
		total_resistance_caster = (pSkillCaster->m_sLightningR + pSkillCaster->m_bAddLightningR) * pTarget->m_bPctLightningR / 100;
		reflect_damage = ((230 * damage) / (total_resistance_caster + 250)) / 100 * 35;
		pSkillCaster->HpChange(-damage, pTarget);
		break;
	}

	CMagicProcess::RemoveType4Buff(BUFF_TYPE_MAGE_ARMOR,pTarget,true); 
}

void MagicInstance::ConsumeItem()
{
	if (nConsumeItem != 0 && pSkillCaster->isPlayer())
		if( nConsumeItem == 370001000 ||
			nConsumeItem == 370002000 ||
			nConsumeItem == 370003000 ||
			nConsumeItem == 379069000 ||
			nConsumeItem == 379070000 ||
			nConsumeItem == 379063000 ||
			nConsumeItem == 379064000 ||
			nConsumeItem == 379065000 ||
			nConsumeItem == 379066000 )
			TO_USER(pSkillCaster)->RobItem(0);
		else
			TO_USER(pSkillCaster)->RobItem(nConsumeItem);

	if (bInstantCast)
		CMagicProcess::RemoveType4Buff(BUFF_TYPE_INSTANT_MAGIC, pSkillCaster);
}
