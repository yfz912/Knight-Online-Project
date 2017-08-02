#pragma once

class CIAchieveTitle : public OdbcRecordset
{
public:
	CIAchieveTitle(OdbcConnection * dbConnection, AchieveTitleArray * pMap) 
		: OdbcRecordset(dbConnection), m_pMap(pMap) {}

	virtual tstring GetTableName() { return _T("ACHIEVE_TITLE"); }
	virtual tstring GetColumns() { return _T("cAchieveID, cMainID, cStrB, cStaB, cDexB, cIntB, cChaB, cAttack, cAC, cNPContribu, cExpPct, cSSwordAC, cJamadarAC, cSwordAC, cBlowAC, cAxeAC, cSpearAC, cArrowAC, cFlameB, cIceB, cLightB, cFireR, cIceR, cLightR, cMagicR, cCurseR, cPoisonR"); }

	virtual bool Fetch()
	{
		_ACHIEVE_TITLE * pData = new _ACHIEVE_TITLE;

		_dbCommand->FetchUInt16(1, pData->cAchieveID);
		_dbCommand->FetchUInt16(2, pData->cMainID);
		_dbCommand->FetchByte(3, pData->cStrB);
		_dbCommand->FetchByte(4, pData->cStaB);
		_dbCommand->FetchByte(5, pData->cDexB);
		_dbCommand->FetchByte(6, pData->cIntB);
		_dbCommand->FetchByte(7, pData->cChaB);
		_dbCommand->FetchUInt16(8, pData->cAttack);
		_dbCommand->FetchUInt16(9, pData->cAC);
		_dbCommand->FetchByte(10, pData->cNPContribu);
		_dbCommand->FetchByte(11, pData->cExpPct);
		_dbCommand->FetchUInt16(12, pData->cSSwordAC);
		_dbCommand->FetchUInt16(13, pData->cJamadarAC);
		_dbCommand->FetchUInt16(14, pData->cSwordAC);
		_dbCommand->FetchUInt16(15, pData->cBlowAC);
		_dbCommand->FetchUInt16(16, pData->cAxeAC);
		_dbCommand->FetchUInt16(17, pData->cSpearAC);
		_dbCommand->FetchUInt16(18, pData->cArrowAC);
		_dbCommand->FetchUInt16(19, pData->cFlameB);
		_dbCommand->FetchUInt16(20, pData->cIceB);
		_dbCommand->FetchUInt16(21, pData->cLightB);
		_dbCommand->FetchUInt16(22, pData->cFireR);
		_dbCommand->FetchUInt16(23, pData->cIceR);
		_dbCommand->FetchUInt16(24, pData->cLightR);
		_dbCommand->FetchUInt16(25, pData->cMagicR);
		_dbCommand->FetchUInt16(26, pData->cCurseR);
		_dbCommand->FetchUInt16(27, pData->cPoisonR);


		if (!m_pMap->PutData(pData->cAchieveID, pData))
			delete pData;

		return true;
	}

	AchieveTitleArray *m_pMap;
};