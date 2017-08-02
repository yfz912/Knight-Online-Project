#pragma once

class CMineListSet : public OdbcRecordset
{
public:
	CMineListSet(OdbcConnection * dbConnection, MineListArray * pMap) 
		: OdbcRecordset(dbConnection), m_pMap(pMap) {}

	virtual tstring GetTableName() { return _T("MINE_LIST"); }
	virtual tstring GetColumns() { return _T("nIndex, Item, Count"); }

	virtual bool Fetch()
	{
		_MINE_LIST pData;

		_dbCommand->FetchUInt32(1, pData.nIndex);
		_dbCommand->FetchUInt32(2, pData.Item);
		_dbCommand->FetchUInt16(3, pData.Count);

		auto itr = m_pMap->GetData(pData.Count);
		if (itr == nullptr)
		{
			itr = new MineList();
			m_pMap->PutData(pData.Count, itr);
		}

		itr->push_back(pData);
		return true;
	}

	MineListArray *m_pMap;
};