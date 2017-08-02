#pragma once

class CIAchieveMon : public OdbcRecordset
{
public:
	CIAchieveMon(OdbcConnection * dbConnection, AchieveMonArray * pMap) 
		: OdbcRecordset(dbConnection), m_pMap(pMap) {}

	virtual tstring GetTableName() { return _T("ACHIEVE_MON"); }
	virtual tstring GetColumns() { return _T("oMainID, oType, oType2, oSsid1, oSsid2, oSsid3, oSsid4, oCount, oSsid5, oSsid6, oSsid7, oSsid8, oCount2"); }

	virtual bool Fetch()
	{
		_ACHIEVE_MON * pData = new _ACHIEVE_MON;
		uint32 col = 1;

		_dbCommand->FetchUInt16(col++, pData->oMainID);
		_dbCommand->FetchByte(col++, pData->oType);
		_dbCommand->FetchByte(col++, pData->oType2);
		for (uint32 group = 0; group < ACHIEVE_MOB_GROUPS; group++)
		{
			for (uint32 i = 0; i < ACHIEVE_MOBS_PER_GROUP; i++)
				_dbCommand->FetchUInt16(col++, pData->oSsid[group][i]);
			_dbCommand->FetchUInt16(col++, pData->oCount[group]);
		}

		if (!m_pMap->PutData(pData->oMainID, pData))
			delete pData;

		return true;
	}

	AchieveMonArray *m_pMap;
};