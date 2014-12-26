#pragma once

inline BOOL iarrcmp(PINT arr1, PINT arr2, SIZE_T len)
{
	for (unsigned int i = 0; i < len; i++)
	if (arr1[i] != arr2[i])
		return false;
	return true;
}

inline BOOL barrcmp(PBYTE arr1, PBYTE arr2, SIZE_T len)
{
	for (unsigned int i = 0; i < len; i++)
	if (arr1[i] != arr2[i])
		return false;
	return true;
}

inline void WaitD3D9()
{
	while (GetModuleHandle(L"d3d9.dll") == NULL)
		Sleep(100);
}

inline void q_memcpy(LPBYTE _Dst, LPBYTE _Src, SIZE_T _Size)
{
	for (unsigned int i = 0; i < _Size; i++)
		*(_Dst + i) = *(_Src + i);
}

inline void q_ZeroMemory(LPBYTE _Dst, SIZE_T _Size)
{
	for (unsigned int i = 0; i < _Size; i++)
		*(_Dst + i) = 0x00;
}

inline void q_nopMem(LPBYTE _Dst, SIZE_T _Size)
{
	for (unsigned int i = 0; i < _Size; i++)
		*(_Dst + i) = 0x90;
}

inline bool bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
	if (*szMask == 'x' && *pData != *bMask)   return 0;
	return (*szMask) == NULL;
}

inline DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, char * szMask)
{
	for (DWORD i = 0; i<dwLen; i++)
	if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))  return (DWORD)(dwAddress + i);
	return 0;
}
