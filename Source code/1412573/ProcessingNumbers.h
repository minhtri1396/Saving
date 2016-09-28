#pragma once

#include <math.h>
#include <Windows.h>

LPWSTR GetInfoFrom(_In_ HWND hWnd, _Out_ size_t& infoLength);
//Clear whitespaces
size_t CleanWString(_Inout_opt_ LPWSTR& wstr);
_Success_(return == FALSE)
BOOL IsInvalid(_In_opt_ LPWSTR wstr);
//Clear whitespaces and dots to calculate conveniently. Ex: 10.000.000 => 10000000
size_t Standardize(_Inout_opt_ LPWSTR& wstr);
//Convert integer or real number to UNICODE (LPWSTR)
LPWSTR NumberToWCS(_In_ double number, _In_ SHORT nDecimalPlaces);
size_t AddDots(_Inout_opt_ LPWSTR& wstr);