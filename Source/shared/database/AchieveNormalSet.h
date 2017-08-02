#pragma once

class CIAchieveNormal : public OdbcRecordset
{
public:
	CIAchieveNormal(OdbcConnection * dbConnection, AchieveNormalArray * pMap) 
		: OdbcRecordset(dbConnection), m_pMap(pMap) {}

	virtual tstring GetTableName() { return _T("ACHIEVE_NORMAL"); }
	virtual tstring GetColumns() { return _T("nAchieveID, nType, nTypeCount"); }

	virtual bool Fetch()
	{
		_ACHIEVE_NORMAL * pData = new _ACHIEVE_NORMAL;

		_dbCommand->FetchUInt16(1, pData->nAchieveID);
		_dbCommand->FetchByte(2, pData->nType);
		_dbCommand->FetchUInt32(3, pData->nTypeCount);


		if (!m_pMap->PutData(pData->nAchieveID, pData))
			delete pData;

		return true;
	}

	AchieveNormalArray *m_pMap;
};