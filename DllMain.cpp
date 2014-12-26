#include <Windows.h>
#include "Utility.h"

DWORD __stdcall InitThread(HANDLE hDllMainThread)
{
	if (hDllMainThread)
	{
		WaitForSingleObject(hDllMainThread, INFINITE);
		CloseHandle(hDllMainThread);
	}

	WaitD3D9();

	MessageBox(NULL, L"Testing", L"Qw3rtyMenu Test", NULL);
	
	return NULL;
}

BOOL __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{

	DisableThreadLibraryCalls(hModule);
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		HANDLE hThread = NULL;

		HANDLE hDllMainThread = OpenThread(THREAD_ALL_ACCESS, NULL, GetCurrentThreadId());

		if (!(hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitThread, (LPVOID)hDllMainThread, 0, 0)))
		{
			CloseHandle(hDllMainThread);
			return FALSE;
		}

		CloseHandle(hThread);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		//DeleteHook();
	}

	return TRUE;
}