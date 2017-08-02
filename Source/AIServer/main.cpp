#include "stdafx.h"
#include "../shared/signal_handler.h"

CServerDlg * g_pMain;
static Condition s_hEvent;

BOOL WINAPI _ConsoleHandler(DWORD dwCtrlType);

bool g_bRunning = true;

int main()
{
	SetConsoleTitle("AI Server");

	SetConsoleCtrlHandler(_ConsoleHandler, TRUE);
	HookSignals(&s_hEvent);

	StartTimeThread();
	g_pMain = new CServerDlg();

	if (g_pMain->Startup())
	{
		printf("AIServer started succesfully all mob and npc loaded.\n");
		s_hEvent.Wait();
	}
	else
	{
		system("pause");
	}

	printf("AIServer is shutdown please wait...\n");

	g_bRunning = false;

	delete g_pMain;

	CleanupTimeThread();
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
