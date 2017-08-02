#pragma once

class CIlegalItems : public OdbcRecordset
{
public:
	CIlegalItems(OdbcConnection * dbConnection, IlegalItemsArray * pMap) 
		: OdbcRecordset(dbConnection), m_pMap(pMap) {}

	virtual tstring GetTableName() { return _T("ILEGAL_ITEMS"); }
	virtual tstring GetColumns() { return _T("nIndex, nItemID"); }

	virtual bool Fetch()
	{
		_ILEGAL_ITEMS * pData = new _ILEGAL_ITEMS;

		_dbCommand->FetchUInt32(1, pData->i_Index);
		_dbCommand->FetchUInt32(2, pData->i_ItemID);

		if (!m_pMap->PutData(pData->i_Index, pData))
			delete pData;

		return true;
	}

	IlegalItemsArray *m_pMap;
};