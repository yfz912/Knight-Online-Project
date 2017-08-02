#pragma once

class CItemDuper : public OdbcRecordset
{
public:
	CItemDuper(OdbcConnection * dbConnection, ItemDupersArray * pMap) 
		: OdbcRecordset(dbConnection), m_pMap(pMap) {}

	virtual tstring GetTableName() { return _T("ITEMS_DUPER"); }
	virtual tstring GetColumns() { return _T("nIndex, nItemID, nSerial"); }

	virtual bool Fetch()
	{
		_ITEM_DUPER * pData = new _ITEM_DUPER;

		_dbCommand->FetchUInt32(1, pData->n_Index);
		_dbCommand->FetchUInt32(2, pData->d_ItemID);
		_dbCommand->FetchUInt64(3, pData->d_Serial);


		if (!m_pMap->PutData(pData->n_Index, pData))
			delete pData;

		return true;
	}

	ItemDupersArray *m_pMap;
};