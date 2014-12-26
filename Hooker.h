#pragma once

struct HookStrategy
{
	PBYTE Hook;
	PBYTE Original;
	SIZE_T HookLen;
	SIZE_T OrigLen;
};

class Hooker
{
public:
	Hooker();
	~Hooker();
	void Initialize(INT_PTR srcFunc, INT_PTR hookFunc, HookStrategy strategy);
	bool Initialized();
	bool Hook(bool force = false);
	bool Hooked();
	bool Unhook(bool force = false);
	static const struct HookStrategy LJmp;
private:
	INT_PTR srcFunc;
	INT_PTR hookFunc;
	HookStrategy strategy;
};

