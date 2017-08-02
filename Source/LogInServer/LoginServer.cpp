#include "stdafx.h"
#include <sstream>
#include "../shared/Ini.h"
#include "../shared/DateTime.h"

extern bool g_bRunning;
std::vector<Thread *> g_timerThreads;

LoginServer::LoginServer() : m_sLastVersion(__VERSION), m_fpLoginServer(nullptr)
{
}

bool LoginServer::Startup()
{
	GetInfoFromIni();
	DateTime time;

	color_c("", FOREGROUND_INTENSITY + FOREGROUND_RED);
		printf("########################################################################################################################");
		printf("########################################################################################################################");
		printf("#############################         EuroPvP 21xx KNIGHT ONLINE SERVER PROJECT        ##################################");
		printf("#############################             PROJECT DEVELOPED BY TopraK                 ##################################");
		printf("########################################################################################################################");
		printf("########################################################################################################################\n");

	color_c("Project started date: ", FOREGROUND_INTENSITY + 0x6); color_c("03.10.2013\n", FOREGROUND_BLUE + FOREGROUND_GREEN);
	color_c("Project version: ", FOREGROUND_INTENSITY +  0x6); color_c("", FOREGROUND_BLUE + FOREGROUND_GREEN); printf("%d\n", GetVersion());
	color_c("Database connection: ", FOREGROUND_INTENSITY +  0x6); color_c("Succesfully.", FOREGROUND_BLUE + FOREGROUND_GREEN);

	color_c("", FOREGROUND_INTENSITY +  0x7);

	CreateDirectory("Logs",NULL);

	m_fpLoginServer = fopen("./Logs/LoginServer.log", "a");
	if (m_fpLoginServer == nullptr)
	{
		printf("ERROR: Unable to open log file.\n");
		return false;
	}

	m_fpUser = fopen(string_format("./Logs/Login_%d_%d_%d.log",time.GetDay(),time.GetMonth(),time.GetYear()).c_str(), "a");
	if (m_fpUser == nullptr)
	{
		printf("ERROR: Unable to open user log file.\n");
		return false;
	}

	if (!m_DBProcess.Connect(m_ODBCName, m_ODBCLogin, m_ODBCPwd)) 
	{
		printf("ERROR: Unable to connect to the database using the details configured.\n");
		return false;
	}

	if (!m_DBProcess.LoadVersionList())
	{
		printf("ERROR: Unable to load the version list.\n");
		return false;
	}

	InitPacketHandlers();

	for(int i=0; i<10 ; i++)
		if (!m_socketMgr[i].Listen(m_LoginServerPort+i, MAX_USER))
		{
			printf("ERROR: Failed to listen on server port.\n");
			return false;
		}

	for(int i=0; i<10 ; i++)
		m_socketMgr[i].RunServer();

	g_timerThreads.push_back(new Thread(Timer_UpdateUserCount));
	return true;
}

uint32 LoginServer::Timer_UpdateUserCount(void * lpParam)
{
	while (g_bRunning)
	{
		g_pMain->UpdateServerList();
		sleep(60 * SECOND);
	}
	return 0;
}

void LoginServer::GetServerList(Packet & result)
{
	Guard lock(m_serverListLock);
	result.append(m_serverListPacket.contents(), m_serverListPacket.size());
}

void LoginServer::UpdateServerList()
{
	m_DBProcess.LoadUserCountList();

	Guard lock(m_serverListLock);
	Packet & result = m_serverListPacket;

	result.clear();
	result << uint8(m_ServerList.size());
	foreach (itr, m_ServerList) 
	{		
		_SERVER_INFO *pServer = *itr;

		result << pServer->strServerIP;
		result << pServer->strLanIP;
		result << pServer->strServerName;

		if (pServer->sUserCount <= pServer->sPlayerCap)
			result << pServer->sUserCount;
		else
			result << int16(-1);

		result << pServer->sServerID << pServer->sGroupID;
		result << pServer->sPlayerCap << pServer->sFreePlayerCap;

		result << uint8(0); 

		result	<< pServer->strKarusKingName << pServer->strKarusNotice 
			<< pServer->strElMoradKingName << pServer->strElMoradNotice;
	}
}

void LoginServer::GetInfoFromIni()
{
	CIni ini(CONF_LOGIN_SERVER);

	ini.GetString("DOWNLOAD", "URL", "ftp.yoursite.net", m_strFtpUrl, false);
	ini.GetString("DOWNLOAD", "PATH", "/", m_strFilePath, false);

	ini.GetString("ODBC", "DSN", "KO_MAIN", m_ODBCName, false);
	ini.GetString("ODBC", "UID", "username", m_ODBCLogin, false);
	ini.GetString("ODBC", "PWD", "password", m_ODBCPwd, false);

	m_LoginServerPort = ini.GetInt("SETTINGS","PORT", 15100);

	m_PremiumType = ini.GetInt("PREMIUM_START","TYPE", 3);
	m_PremiumDays = ini.GetInt("PREMIUM_START","DAYS", 3);

	int nServerCount = ini.GetInt("SERVER_LIST", "COUNT", 1);
	if (nServerCount <= 0) 
		nServerCount = 1;

	char key[20]; 
	_SERVER_INFO* pInfo = nullptr;

	m_ServerList.reserve(nServerCount);

	for (int i = 0; i < nServerCount; i++)
	{
		pInfo = new _SERVER_INFO;

		_snprintf(key, sizeof(key), "SERVER_%02d", i);
		ini.GetString("SERVER_LIST", key, "127.0.0.1", pInfo->strServerIP, false);

		_snprintf(key, sizeof(key), "LANIP_%02d", i);
		ini.GetString("SERVER_LIST", key, "127.0.0.1", pInfo->strLanIP, false);

		_snprintf(key, sizeof(key), "NAME_%02d", i);
		ini.GetString("SERVER_LIST", key, "TEST|Server 1", pInfo->strServerName, false);

		_snprintf(key, sizeof(key), "ID_%02d", i);
		pInfo->sServerID = ini.GetInt("SERVER_LIST", key, 1);

		_snprintf(key, sizeof(key), "GROUPID_%02d", i);
		pInfo->sGroupID = ini.GetInt("SERVER_LIST", key, 1);

		_snprintf(key, sizeof(key), "PREMLIMIT_%02d", i);
		pInfo->sPlayerCap = ini.GetInt("SERVER_LIST", key, MAX_USER);

		_snprintf(key, sizeof(key), "FREELIMIT_%02d", i);
		pInfo->sFreePlayerCap = ini.GetInt("SERVER_LIST", key, MAX_USER);

		_snprintf(key, sizeof(key), "KING1_%02d", i);
		ini.GetString("SERVER_LIST", key, "", pInfo->strKarusKingName);

		_snprintf(key, sizeof(key), "KING2_%02d", i);
		ini.GetString("SERVER_LIST", key, "", pInfo->strElMoradKingName);

		_snprintf(key, sizeof(key), "KINGMSG1_%02d", i);
		ini.GetString("SERVER_LIST", key, "", pInfo->strKarusNotice);

		_snprintf(key, sizeof(key), "KINGMSG2_%02d", i);
		ini.GetString("SERVER_LIST", key, "", pInfo->strElMoradNotice);

		m_ServerList.push_back(pInfo);
	}

	// Read news from INI (max 3 blocks)
#define BOX_START '#' << uint8(0) << '\n'
#define LINE_ENDING uint8(0) << '\n'
#define BOX_END BOX_START << LINE_ENDING

	m_news.Size = 0;
	std::stringstream ss;
	for (int i = 0; i < 3; i++)
	{
		string title, message;

		_snprintf(key, sizeof(key), "TITLE_%02d", i);
		ini.GetString("NEWS", key, "", title);
		if (title.empty())
			continue;

		_snprintf(key, sizeof(key), "MESSAGE_%02d", i);
		ini.GetString("NEWS", key, "", message);
		if (message.empty())
			continue;

		size_t oldPos = 0, pos = 0;
		ss << title << BOX_START;
		ss << message << LINE_ENDING << BOX_END;
	}

	m_news.Size = ss.str().size();
	if (m_news.Size)
		memcpy(&m_news.Content, ss.str().c_str(), m_news.Size);
}

void LoginServer::WriteLogFile(string & logMessage)
{
	Guard lock(m_lock);
	fwrite(logMessage.c_str(), logMessage.length(), 1, m_fpLoginServer);
	fflush(m_fpLoginServer);
}

void LoginServer::WriteUserLogFile(string & logMessage)
{
	Guard lock(m_lock);
	fwrite(logMessage.c_str(), logMessage.length(), 1, m_fpUser);
	fflush(m_fpUser);
}

void LoginServer::ReportSQLError(OdbcError *pError)
{
	if (pError == nullptr)
		return;

	string errorMessage = string_format(_T("ODBC error occurred.\r\nSource: %s\r\nError: %s\r\nDescription: %s\n"),
		pError->Source.c_str(), pError->ExtendedErrorMessage.c_str(), pError->ErrorMessage.c_str());

	TRACE("%s", errorMessage.c_str());
	WriteLogFile(errorMessage);
	delete pError;
}

LoginServer::~LoginServer() 
{
	printf("Waiting for timer threads to exit...");
	foreach (itr, g_timerThreads)
	{
		(*itr)->waitForExit();
		delete (*itr);
	}
	printf(" exited.\n");

	foreach (itr, m_ServerList)
		delete *itr;
	m_ServerList.clear();

	foreach (itr, m_VersionList)
		delete itr->second;
	m_VersionList.clear();

	if (m_fpLoginServer != nullptr)
		fclose(m_fpLoginServer);

	if (m_fpUser != nullptr)
		fclose(m_fpUser);

	printf("Shutting down socket system...");

	for(int i=0; i<10 ; i++)
		m_socketMgr[i].Shutdown();

	printf(" done.\n");
}

void LoginServer::color_c(char* buff, WORD color)
{
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	SetConsoleTextAttribute(hstdout, color);
	WriteConsole(hstdout, buff, strlen(buff), new DWORD, 0);
}

void LoginServer::SendConsoleFAIL()
{
	color_c("[   ", FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	color_c("FAIL", FOREGROUND_RED + FOREGROUND_INTENSITY);
	color_c("   ]\n", FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void LoginServer::SendConsoleOK()
{
	color_c("[    ", FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	color_c("OK", FOREGROUND_GREEN + FOREGROUND_INTENSITY);
	color_c("    ]\n", FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void LoginServer::Yaz(char* yazi, WORD color)
{
	char data[105];
	memset(data, 0x00, 105);

	strcpy(data, yazi);

	int i2 = 0;
	i2 = 100 - strlen(yazi);

	for (int i = 0; i < i2; i++)
		sprintf(data, "%s ", data);

	if (color == 0)
		color_c((char*)(LPCTSTR)data, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	else
		color_c((char*)(LPCTSTR)data, color);
}