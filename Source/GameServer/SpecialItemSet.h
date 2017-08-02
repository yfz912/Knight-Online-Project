#pragma once

class CISpecialItem : public OdbcRecordset
{
public:
	CISpecialItem(OdbcConnection * dbConnection, SpecialItemArray * pMap)
		: OdbcRecordset(dbConnection), m_pMap(pMap) {}

	virtual tstring GetTableName() { return _T("SPECIAL_ITEM"); }
	virtual tstring GetColumns() { return _T("strUserID, strSerial, SealSerial, bRaceSatis, sClass, bLevel, lExp, Stat_STR, Stat_STA, Stat_DEX, Stat_INT, Stat_CHA, bGold, bSkillPoints, strItem"); }

	virtual bool Fetch()
	{
		_SPECIAL_ITEM * pData = new _SPECIAL_ITEM;

		int i = 1;
		_dbCommand->FetchString(i++, pData->sCharID);
		_dbCommand->FetchUInt64(i++, pData->iSerial);
		_dbCommand->FetchUInt32(i++, pData->SealSerial);
		_dbCommand->FetchByte(i++, pData->bRaceSatis);
		_dbCommand->FetchUInt16(i++, pData->sClass);
		_dbCommand->FetchByte(i++, pData->bLevel);
		_dbCommand->FetchUInt16(i++, pData->sExpPercent);
		_dbCommand->FetchByte(i++, pData->Stat_STR);
		_dbCommand->FetchByte(i++, pData->Stat_STA);
		_dbCommand->FetchByte(i++, pData->Stat_DEX);
		_dbCommand->FetchByte(i++, pData->Stat_INT);
		_dbCommand->FetchByte(i++, pData->Stat_CHA);
		_dbCommand->FetchUInt32(i++, pData->sGold);
		_dbCommand->FetchBinary(i++, strSkill, sizeof(strSkill));
		_dbCommand->FetchBinary(i++, stritem, sizeof(stritem));

		ByteBuffer SkillBuffer, ItemBuffer;
		SkillBuffer.append(strSkill, sizeof(strSkill));
		ItemBuffer.append(stritem, sizeof(stritem));

		pData->Skill_Points[0] = strSkill[0] + strSkill[1] + strSkill[2] + strSkill[3] + strSkill[4];
		pData->Skill_Points[1] = strSkill[5];
		pData->Skill_Points[2] = strSkill[6];
		pData->Skill_Points[3] = strSkill[7];
		pData->Skill_Points[4] = strSkill[8];

		for (int i = 0; i < INVENTORY_COSP; i++)
		{
			uint32 rNum;
			uint16 nDuration, nCount;

			ItemBuffer >> rNum >> nDuration >> nCount;

			_ITEM_TABLE *pTable = g_pMain->GetItemPtr(rNum);
			if (pTable == nullptr || nCount <= 0)
				continue;

			if (!pTable->m_bCountable && nCount > 1)
				nCount = 1;
			else if (nCount > ITEMCOUNT_MAX)
				nCount = ITEMCOUNT_MAX;

			pData->Item_Num[i] = rNum;
			pData->Item_Duration[i] = nDuration;
			pData->Item_Count[i] = nCount;
			pData->Item_Flag[i] = ITEM_FLAG_CHAR_SEAL;
		}

		if (!m_pMap->PutData(pData->SealSerial, pData))
			delete pData;

		return true;
	}

	SpecialItemArray *m_pMap;
	uint32 bIndex;
	char stritem[INVENTORY_COSP * 9];
	char strSkill[10];
};