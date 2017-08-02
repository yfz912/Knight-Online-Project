#include "stdafx.h"
#include "../shared/signal_handler.h"

LoginServer * g_pMain;
static Condition s_hEvent;
bool g_bRunning = true;

BOOL WINAPI _ConsoleHandler(DWORD dwCtrlType);

int main()
{
	SetConsoleTitle("Login Server");

	SetConsoleCtrlHandler(_ConsoleHandler, TRUE);
	HookSignals(&s_hEvent);

	g_pMain = new LoginServer();

	if (g_pMain->Startup())
	{
		printf("\n\nLogin server started is succesfully!\n\n");

		s_hEvent.Wait();
	}
	else
	{
		system("pause");
	}

	printf("Server shutting down, please wait...\n");

	g_bRunning = false; 
	delete g_pMain;
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
