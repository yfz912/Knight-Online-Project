#pragma once

class CIAchieveCom : public OdbcRecordset
{
public:
	CIAchieveCom(OdbcConnection * dbConnection, AchieveComArray * pMap) 
		: OdbcRecordset(dbConnection), m_pMap(pMap) {}

	virtual tstring GetTableName() { return _T("ACHIEVE_COM"); }
	virtual tstring GetColumns() { return _T("cAchieveID, cType, cQuest1, cQuest2"); }

	virtual bool Fetch()
	{
		_ACHIEVE_COM * pData = new _ACHIEVE_COM;

		_dbCommand->FetchUInt16(1, pData->cAchieveID);
		_dbCommand->FetchByte(2, pData->cType);
		_dbCommand->FetchUInt32(3, pData->cQuest1);
		_dbCommand->FetchUInt32(4, pData->cQuest2);


		if (!m_pMap->PutData(pData->cAchieveID, pData))
			delete pData;

		return true;
	}

	AchieveComArray *m_pMap;
};