#pragma once

#include "../shared/database/OdbcConnection.h"

class CDBProcess  
{
public:
	bool Connect(std::string & szDSN, std::string & szUser, std::string & szPass);

	bool LoadVersionList();
	bool LoadUserCountList();

	uint8 PremiumInsert(std::string & strAccountID, uint8 pType, uint8 pDays);
	uint16 AccountLogin(std::string & strAccountID, std::string & strPasswd);
	int16 AccountPremium(std::string & strAccountID);

private:
	OdbcConnection m_dbConnection;
};