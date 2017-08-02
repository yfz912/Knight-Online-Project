#include "stdafx.h"
#include "../shared/Condition.h"
#include "ConsoleInputThread.h"
#include "../shared/signal_handler.h"

CGameServerDlg * g_pMain;

static Condition s_hEvent;

BOOL WINAPI _ConsoleHandler(DWORD dwCtrlType);

bool g_bRunning = true;

int main()
{
	SetConsoleTitle("Game Server");

	SetConsoleCtrlHandler(_ConsoleHandler, TRUE);

	HookSignals(&s_hEvent);
	StartTimeThread();
	StartConsoleInputThread();

	g_pMain = new CGameServerDlg();

	if (g_pMain->Startup())
	{
		g_pMain->ResetBattleZone();
		printf("\nGame server is started succesfully good game!\n");
		s_hEvent.Wait();
	}
	else
	{
		system("pause");
	}

	g_bRunning = false; 

	delete g_pMain;

	CleanupTimeThread();
	CleanupConsoleInputThread();
	UnhookSignals();

	return 0;
}

BOOL WINAPI _ConsoleHandler(DWORD dwCtrlType)
{
	s_hEvent.BeginSynchronized();
	s_hEvent.Signal();
	s_hEvent.EndSynchronized();
	sleep(10000);
	return TRUE;
}
