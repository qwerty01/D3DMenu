#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include "Hooker.h"
#include "Hook.h"
#include "Utility.h"

typedef HRESULT(WINAPI *tReset)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS *a);
typedef HRESULT(WINAPI *tRelease)(LPDIRECT3DDEVICE9 pDevice);
typedef HRESULT(WINAPI *tEndScene)(LPDIRECT3DDEVICE9 pDevice);

HMODULE hD3D9Dll = NULL;

Hooker hEndScene;
Hooker hReset;

