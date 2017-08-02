#pragma once

class CIAchieveWar : public OdbcRecordset
{
public:
	CIAchieveWar(OdbcConnection * dbConnection, AchieveWarArray * pMap) 
		: OdbcRecordset(dbConnection), m_pMap(pMap) {}

	virtual tstring GetTableName() { return _T("ACHIEVE_WAR"); }
	virtual tstring GetColumns() { return _T("wMainID, wType, Unknow, wKillCount, Unknow2"); }

	virtual bool Fetch()
	{
		_ACHIEVE_WAR * pData = new _ACHIEVE_WAR;

		_dbCommand->FetchUInt16(1, pData->wMainID);
		_dbCommand->FetchByte(2, pData->wType);
		_dbCommand->FetchByte(3, pData->Unknow);
		_dbCommand->FetchUInt32(4, pData->wKillCount);
		_dbCommand->FetchByte(5, pData->Unknow2);


		if (!m_pMap->PutData(pData->wMainID, pData))
			delete pData;

		return true;
	}

	AchieveWarArray *m_pMap;
};