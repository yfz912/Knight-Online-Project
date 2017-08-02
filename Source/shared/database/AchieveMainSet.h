#pragma once

class CIAchieveMain : public OdbcRecordset
{
public:
	CIAchieveMain(OdbcConnection * dbConnection, AchieveMainArray * pMap) 
		: OdbcRecordset(dbConnection), m_pMap(pMap) {}

	virtual tstring GetTableName() { return _T("ACHIEVE_MAIN"); }
	virtual tstring GetColumns() { return _T("mMainID, mKind, mAchieveID, mPoints, mItemID, mItemCount, mZoneNum, mKilled, mType, mTime, mSize, Category"); }

	virtual bool Fetch()
	{
		_ACHIEVE_MAIN * pData = new _ACHIEVE_MAIN;

		_dbCommand->FetchUInt16(1, pData->mMainID);
		_dbCommand->FetchByte(2, pData->mKind);
		_dbCommand->FetchUInt16(3, pData->mAchieveID);
		_dbCommand->FetchUInt16(4, pData->mPoints);
		_dbCommand->FetchUInt32(5, pData->mItemID);
		_dbCommand->FetchUInt32(6, pData->mItemCount);
		_dbCommand->FetchByte(7, pData->mZoneNum);
		_dbCommand->FetchByte(8, pData->mKilledType);
		_dbCommand->FetchByte(9, pData->mType);
		_dbCommand->FetchUInt16(10, pData->mTime);
		_dbCommand->FetchByte(11, pData->mSize);
		_dbCommand->FetchByte(12, pData->Category);

		if (!m_pMap->PutData(pData->mMainID, pData))
			delete pData;

		return true;
	}

	AchieveMainArray *m_pMap;
};