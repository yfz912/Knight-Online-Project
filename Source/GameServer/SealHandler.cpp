#include "stdafx.h"
#include "DBAgent.h"

using std::string;

#define ITEM_SEAL_PRICE 1000000

/**
* @brief	Packet handler for the item sealing system.
*
* @param	pkt	The packet.
*/
void CUser::ItemSealProcess(Packet & pkt)
{
	// Seal type
	uint8 opcode = pkt.read<uint8>();

	Packet result(WIZ_ITEM_UPGRADE, uint8(ITEM_SEAL));
	result << opcode;

	switch (opcode)
	{
		// Used when sealing an item.
	case SEAL_TYPE_SEAL:
		{
			string strPasswd;
			uint32 nItemID; 
			int16 unk0; // set to -1 in this case
			uint8 bSrcPos, bResponse = SealErrorNone;
			pkt >> unk0 >> nItemID >> bSrcPos >> strPasswd;

			/* 
			Most of these checks are handled client-side, so we shouldn't need to provide error messages.
			Also, item sealing requires certain premium types (gold, platinum, etc) - need to double-check 
			these before implementing this check.
			*/

			// is this a valid position? (need to check if it can be taken from new slots)
			if (bSrcPos >= HAVE_MAX 
				// does the item exist where the client says it does?
					|| GetItem(SLOT_MAX + bSrcPos)->nNum != nItemID
					// i ain't be allowin' no stealth items to be sealed!
					|| GetItem(SLOT_MAX + bSrcPos)->nSerialNum == 0)
					bResponse = SealErrorFailed;
			// is the password valid by client limits?
			else if (strPasswd.empty() || strPasswd.length() > 8)
				bResponse = SealErrorInvalidCode;
			// do we have enough coins?
			else if (!hasCoins(ITEM_SEAL_PRICE))
				bResponse = SealErrorNeedCoins;

			_ITEM_TABLE* pItem = g_pMain->m_ItemtableArray.GetData(nItemID);

			if(pItem == nullptr)
				return;

			// If no error, pass it along to the database.
			if (bResponse == SealErrorNone)
			{
				result << nItemID << bSrcPos << strPasswd << bResponse;
				g_pMain->AddDatabaseRequest(result, this);
			}
			// If there's an error, tell the client.
			// From memory though, there was no need -- it handled all of these conditions itself
			// so there was no need to differentiate (just ignore the packet). Need to check this.
			else 
			{
				result << bResponse;
				Send(&result);
			}
		} break;

		// Used when unsealing an item.
	case SEAL_TYPE_UNSEAL:
		{
			string strPasswd;
			uint32 nItemID; 
			int16 unk0; // set to -1 in this case
			uint8 bSrcPos, bResponse = SealErrorNone;
			pkt >> unk0 >> nItemID >> bSrcPos >> strPasswd;

			if (bSrcPos >= HAVE_MAX
				|| GetItem(SLOT_MAX+bSrcPos)->bFlag != ITEM_FLAG_SEALED
				|| GetItem(SLOT_MAX+bSrcPos)->nNum != nItemID)
				bResponse = SealErrorFailed;
			else if (strPasswd.empty() || strPasswd.length() > 8)
				bResponse = SealErrorInvalidCode;

			// If no error, pass it along to the database.
			if (bResponse == SealErrorNone)
			{
				result << nItemID << bSrcPos << strPasswd << bResponse;
				g_pMain->AddDatabaseRequest(result, this);
			}
			// If there's an error, tell the client.
			// From memory though, there was no need -- it handled all of these conditions itself
			// so there was no need to differentiate (just ignore the packet). Need to check this.
			else
			{
				result << bResponse;
				Send(&result);
			}
		} break;

		// Used when binding a Krowaz item (used to take it from not bound -> bound)
	case SEAL_TYPE_KROWAZ:
		{
			string strPasswd = "0"; //Dummy, not actually used.
			uint32 nItemID;
			uint8 bSrcPos = 0 , unk2, unk3, bResponse = SealErrorNone;
			uint16 unk1;
			pkt >> unk1 >> nItemID >> bSrcPos >> unk2 >> unk3;

			_ITEM_TABLE * pTable = g_pMain->m_ItemtableArray.GetData(nItemID);
			_ITEM_DATA * pData = GetItem(SLOT_MAX+bSrcPos);

			if (pTable == nullptr || pData == nullptr)
				bResponse = SealErrorFailed;
			else if (bSrcPos >= HAVE_MAX
				|| pTable->m_Bound != 1
				|| pData->nNum != nItemID)
				bResponse = SealErrorFailed;

			if (bResponse == SealErrorNone)
			{
				result << nItemID << bSrcPos << strPasswd << bResponse;
				g_pMain->AddDatabaseRequest(result, this);
			}
			else
			{
				result << bResponse;
				Send(&result);
			}
		} 
		break;
	}
}

void CUser::SealItem(uint8 bSealType, uint8 bSrcPos)
{
	_ITEM_DATA * pItem = GetItem(SLOT_MAX + bSrcPos);
	if (pItem == nullptr)
		return;

	switch (bSealType)
	{
	case SEAL_TYPE_SEAL:
		pItem->bFlag = ITEM_FLAG_SEALED;
		GoldLose(ITEM_SEAL_PRICE);
		break;

	case SEAL_TYPE_UNSEAL:
		pItem->bFlag = 0;
		break;

	case SEAL_TYPE_KROWAZ:
		pItem->bFlag = ITEM_FLAG_BOUND;
		break;
	}
}

/**
* @brief	Packet handler for the character sealing system.
*
* @param	pkt	The packet.
*/

void CUser::Listopen(Packet & pkt)
{
	Packet result(WIZ_ITEM_UPGRADE, uint8(ITEM_CHARACTER_SEAL));
	string strPasswd;
	string strCharID1, strCharID2, strCharID3, strCharID4;
	uint8 bResponse = SealSuccess;
	uint8 opcode;
	uint32 nItemID = CYPHER_RING;
	_ITEM_DATA * pDstItem = nullptr;

	pkt >> opcode;


	switch (opcode)
	{
		case Characterlistopen:
		{
			result << opcode << uint8(1);
			g_DBAgent.GetAllCharID(m_strAccountID, strCharID1, strCharID2, strCharID3, strCharID4);
			g_DBAgent.LoadCharInfo(strCharID1, result);
			g_DBAgent.LoadCharInfo(strCharID2, result);
			g_DBAgent.LoadCharInfo(strCharID3, result);
			g_DBAgent.LoadCharInfo(strCharID4, result);

			Send(&result);
			return;
		}
		break;
		case SealSuccess:
		{
			string RecvCharID, RecvPass, SealPass;
			uint8 RecvSlot, blevel = 0, bRace = 0, nStr, nSta, nDex, nInt, nCha;
			uint16 Unkw, bJob = 0;
			uint32 RecvItemID, nGold;
			uint16 bExp = 0;
			ByteBuffer strSkill, strItem;

			pkt >> Unkw >> RecvSlot >> RecvItemID >> RecvCharID >> RecvPass;

			g_DBAgent.LoadSealPasswd(m_strAccountID, SealPass); 

			if (RecvSlot >= INVENTORY_COSP)
				bResponse = SealFailed;
			if (RecvPass.empty() || RecvPass.length() > 8 || strPasswd != SealPass)
				bResponse = SealErrorInvalidCode;
			if (!g_DBAgent.LoadSealInfo(RecvCharID, blevel, bExp, bRace, bJob, nStr, nSta, nDex, nInt, nCha, nGold, strSkill, strItem))
				bResponse = SealFailed;

			if (bResponse == SealSuccess)
			{
				uint64 iSerial = g_pMain->GenerateItemSerial(); // This get Serial Number
				uint32 sSerial = 1;
				int tamanho = g_pMain->m_SpecialItemArray.GetSize();

				for (int i = 1; i < tamanho; i++)
				{
					_SPECIAL_ITEM * Special = g_pMain->m_SpecialItemArray.GetData(i);

					if (Special != nullptr)
					{
						sSerial++;
						continue;						
					}

					sSerial = i;
					break;
				}

				bool tSuccess = g_DBAgent.CharacterSealSave(RecvCharID, iSerial, sSerial, bRace, bJob, blevel, bExp, nStr, nSta, nDex, nInt, nCha, nGold, strSkill, strItem);

				if (!tSuccess)
				{
					result << uint8(SealSuccess) << uint8(SealFailed);
					Send(&result);
					return;
				}

				pDstItem = GetItem(SLOT_MAX + RecvSlot);

				memset(pDstItem, 0, sizeof(_ITEM_DATA));

				pDstItem->nNum = CYPHER_RING;
				pDstItem->sDuration = 1;
				pDstItem->sCount = 1;
				pDstItem->bFlag = 1;
				pDstItem->sRemainingRentalTime = 0;
				pDstItem->nExpirationTime = 0;
				pDstItem->nSerialNum = iSerial;
				pDstItem->SealSerial = sSerial;

				if (blevel >= 83)  // is Only for test, latter i remnove this
					bExp = 10000;
				else
					bExp = 5000;

				g_DBAgent.UpdateAccountChar(m_strAccountID, RecvCharID);

				SetUserAbility(true);
				SendItemWeight();

				result << uint8(SealSuccess) << uint8(1)
					<< RecvSlot
					<< pDstItem->nNum
					<< sSerial
					<< RecvCharID
					<< uint8(bJob)
					<< uint8(blevel)
					<< uint16(bExp)
					<< uint16(bRace)
					<< uint32(0);

				Send(&result);
				return;
			}
			else
				result << uint8(SealSuccess) << uint8(SealFailed);
			Send(&result);
		}
		break;
		case Sealhasbeenlifted: // To unlock
		{
			uint8 InvSlot, AccSlot;
			uint16 Unkw;
			uint32 RecvItemID;

			pkt >> Unkw >> InvSlot >> RecvItemID >> AccSlot;

			pDstItem = GetItem(SLOT_MAX + InvSlot);

			_SPECIAL_ITEM * pSpecial = g_pMain->m_SpecialItemArray.GetData(pDstItem->SealSerial);

			if (GetNation() == KARUS && pSpecial->bRaceSatis > 10)
			{
				result << uint8(SealSuccess) << uint8(SealFailed);
				Send(&result);
				return;
			}
			else if (GetNation() == ELMORAD && pSpecial->bRaceSatis < 10)
			{
				result << uint8(SealSuccess) << uint8(SealFailed);
				Send(&result);
				return;
			}

			g_DBAgent.UpdateAccountChar(m_strAccountID, pSpecial->sCharID, AccSlot);
			g_DBAgent.CharacterSealDelete(pSpecial->sCharID);
			g_pMain->m_SpecialItemArray.DeleteData(pSpecial->SealSerial);

			memset(pDstItem, 0, sizeof(_ITEM_DATA));

			result << opcode << uint8(1)
				<< InvSlot;

			Send(&result);
		}
		break;
		case InventoryShow:
		{
			uint32 sSerial;

			pkt >> sSerial;

			_SPECIAL_ITEM * Special = g_pMain->m_SpecialItemArray.GetData(sSerial);

			if(Special == nullptr)
			{
				result << uint8(0);
				Send(&result);
				return;
			}

			result.DByte();
			result << uint8(InventoryShow) << uint8(1)
				<< Special->sCharID 
				<< Special->bRaceSatis
				<< Special->sClass
				<< Special->bLevel

				<< Special->Stat_STR
				<< Special->Stat_STA
				<< Special->Stat_DEX
				<< Special->Stat_INT
				<< Special->Stat_CHA

				<< Special->sGold
				<< Special->Skill_Points[0]
				<< uint32(1)
				<< Special->Skill_Points[1]
				<< Special->Skill_Points[2]
				<< Special->Skill_Points[3]
				<< Special->Skill_Points[4];

			for (int i = 0; i < INVENTORY_COSP; i++)
			{
				if (Special->Item_Num[i] == 0)
					continue;

				result << Special->Item_Num[i] << Special->Item_Duration[i] << Special->Item_Count[i]
					<< Special->Item_Flag[i];
			}

			Send(&result);
		}
		break;
	}
}