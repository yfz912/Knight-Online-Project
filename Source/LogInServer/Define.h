#pragma once

#include "../shared/globals.h"

#define CONF_LOGIN_SERVER	"./Settings/LogInServer.ini"

#define LETRA_TOTAL	50

struct _SERVER_INFO
{
	std::string strServerIP;
	std::string strLanIP;
	std::string strServerName;
	std::string strKarusKingName;
	std::string strKarusNotice;
	std::string strElMoradKingName;
	std::string strElMoradNotice;

	short sUserCount;
	short sServerID;
	short sGroupID;
	short sPlayerCap;
	short sFreePlayerCap;

	_SERVER_INFO()
	{
		sUserCount = sServerID = sGroupID = sPlayerCap = sFreePlayerCap = 0;
	}
};

struct News
{
	uint8 Content[4096];
	size_t Size;
};

struct _VERSION_INFO
{
	uint16 sVersion;
	uint16 sHistoryVersion;
	std::string strFilename;
};

enum LoginErrorCode
{
	AUTH_SUCCESS	= 0x01,
	AUTH_NOT_FOUND	= 0x02,
	AUTH_INVALID	= 0x03,
	AUTH_BANNED		= 0x04,
	AUTH_IN_GAME	= 0x05,
	AUTH_ERROR		= 0x06,
	AUTH_AGREEMENT	= 0xF,
	AUTH_FAILED		= 0xFF
};