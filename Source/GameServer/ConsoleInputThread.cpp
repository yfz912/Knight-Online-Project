#include "stdafx.h"
#include "ConsoleInputThread.h"
#include <conio.h>

static Thread s_consoleInputThread;

void StartConsoleInputThread()
{
	s_consoleInputThread.start(ConsoleInputThread, nullptr);
}

void CleanupConsoleInputThread()
{
	s_consoleInputThread.waitForExit();
}

uint32 THREADCALL ConsoleInputThread(void * lpParam)
{
	size_t i = 0;
	size_t len;
	char cmd[300];

	while (g_bRunning)
	{
		if (!_kbhit())
		{
			sleep(100);
			continue;
		}

		memset(cmd, 0, sizeof(cmd)); 
		if (fgets(cmd, sizeof(cmd), stdin) == nullptr)
		{
			break;
		}

		if (!g_bRunning)
			break;

		len = strlen(cmd);
		for (i = 0; i < len; i++)
		{
			if (cmd[i] == '\n' || cmd[i] == '\r')
				cmd[i] = '\0';
		}

		g_pMain->HandleConsoleCommand(cmd);
	}

	return 0;
}