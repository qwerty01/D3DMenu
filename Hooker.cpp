#include <Windows.h>
#include "Utility.h"
#include "Hooker.h"

const struct HookStrategy Hooker::LJmp = { new byte[2] {0xFF, 0x25}, NULL, 2, 6 };

Hooker::Hooker()
{
	srcFunc = NULL;
	hookFunc = NULL;
	strategy.Hook = NULL;
	strategy.HookLen = 0;
	strategy.Original = NULL;
}

Hooker::~Hooker()
{
	if (Hooked())
		Unhook();
	delete[] this->strategy.Original;
	delete[] this->strategy.Hook;
}

void Hooker::Initialize(INT_PTR srcFunc, INT_PTR hookFunc, HookStrategy strategy)
{
	if (this->strategy.Hook != NULL)
		delete[] this->strategy.Hook;
	if (this->strategy.Original != NULL)
		delete[] this->strategy.Original;

	this->srcFunc = srcFunc;
	this->hookFunc = hookFunc;
	this->strategy.Original = new byte[strategy.OrigLen];
	this->strategy.Hook = new byte[strategy.HookLen];
	this->strategy.HookLen = strategy.HookLen;
	this->strategy.OrigLen = strategy.OrigLen;

	memcpy(this->strategy.Hook, strategy.Hook, strategy.HookLen);
}

bool Hooker::Initialized()
{
	return (srcFunc != NULL && hookFunc != NULL && strategy.Hook != NULL && strategy.Original != NULL);
}

bool Hooker::Hook(bool force)
{
	DWORD oldProtect;
	DWORD tmpProtect;

	if (!Initialized())
		return false;

	if (!force && Hooked())
		return false;
	
	VirtualProtect((LPVOID)srcFunc, strategy.HookLen + sizeof(INT_PTR), PAGE_EXECUTE_READWRITE, &oldProtect);
	
	q_memcpy(strategy.Original, (LPBYTE)srcFunc, strategy.OrigLen); // backup original
	q_nopMem((LPBYTE)srcFunc, strategy.OrigLen); // NOP extra memory
	q_memcpy((LPBYTE)srcFunc, strategy.Hook, strategy.HookLen); // overwrite opcodes
	q_memcpy((LPBYTE)(srcFunc + strategy.HookLen), (LPBYTE)(&hookFunc), sizeof(INT_PTR)); // add address
	
	VirtualProtect((LPVOID)srcFunc, strategy.HookLen + sizeof(INT_PTR), oldProtect, &tmpProtect);
	
	return true;
}

bool Hooker::Hooked()
{
	DWORD oldProtect;
	DWORD tmpProtect;
	bool ret = false;
	
	VirtualProtect((LPVOID)srcFunc, strategy.HookLen + sizeof(INT_PTR), PAGE_EXECUTE_READWRITE, &oldProtect);
	
	if (barrcmp((PBYTE)srcFunc, strategy.Hook, strategy.HookLen))
		ret = true;
	
	VirtualProtect((LPVOID)srcFunc, strategy.HookLen + sizeof(INT_PTR), oldProtect, &tmpProtect);
	
	return ret;
}

bool Hooker::Unhook(bool force)
{
	DWORD oldProtect;
	DWORD tmpProtect;

	if (!Initialized())
		return false;

	if (!force && !Hooked())
		return false;
	
	VirtualProtect((LPVOID)srcFunc, strategy.HookLen + sizeof(INT_PTR), PAGE_EXECUTE_READWRITE, &oldProtect);
	
	q_memcpy((LPBYTE)srcFunc, strategy.Original, strategy.HookLen + sizeof(INT_PTR));
	ZeroMemory(strategy.Original, strategy.HookLen + sizeof(INT_PTR));
	
	VirtualProtect((LPVOID)srcFunc, strategy.HookLen + sizeof(INT_PTR), oldProtect, &tmpProtect);
	
	return true;
}
