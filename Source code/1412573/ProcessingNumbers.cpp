#include "stdafx.h"
#include "ProcessingNumbers.h"

#define MSG_EMPTY_ERROR L"Money and Interest Rate must be fill in completely.", L"Empty error"
#define MSG_DOT_ERROR L"You wrote invalid dots.\
					\n  Some invalid dots:\n    + 1.2.\n    + 10.5.256\n\
					\n  Some valid dots:\n    + 5.\n    + .5\n    + 10.000.000", L"Dot error"
#define MSG_CHARACTER_ERROR L"You wrote invalid characters. Valid characters:\
					\n    + Dot (.)\n\n    + Whitespace\n\n    + 0 -> 9", L"Character error"

LPWSTR GetInfoFrom(_In_ HWND hWnd, _Out_ size_t& uiInfoLength)
{
	uiInfoLength = GetWindowTextLength(hWnd);
	if (uiInfoLength)
	{
		LPWSTR lpwStr = new WCHAR[uiInfoLength + 1];
		GetWindowText(hWnd, lpwStr, uiInfoLength + 1);
		return lpwStr;
	}
	return nullptr;
}
//Clear whitespaces
size_t CleanWString(_Inout_opt_ LPWSTR& lpwStr)
{
	INT k = 0;
	LPWSTR lpwNewStr = new WCHAR[wcslen(lpwStr) + 1];
	for (INT i = 0; lpwStr[i]; ++i)
		if (lpwStr[i] != 32)
			lpwNewStr[k++] = lpwStr[i];

	lpwNewStr[k] = 0;
	delete[]lpwStr;
	lpwStr = lpwNewStr;

	return wcslen(lpwStr);
}
_Success_(return == FALSE)
BOOL IsInvalid(_In_opt_ LPWSTR lpwStr)
{
	if (lpwStr == nullptr)
	{
		MessageBox(0, MSG_EMPTY_ERROR, 0);
		return TRUE;
	}

	BOOL fValidSyntax = TRUE;
	SHORT countDigit = 0; //the number of digit after dot.
	SHORT countDot = 0;
	for (INT i = wcslen(lpwStr) - 1; i >= 0; --i)
	{
		if (lpwStr[i] == '.') //checking if it's real or integer number
		{
			++countDot;
			if (countDigit != 3)
				fValidSyntax = FALSE; //maybe this number is a real number, so the first wrong we ignore
			if (countDot > 1 && !fValidSyntax)
			{
				MessageBox(0, MSG_DOT_ERROR, 0);
				return TRUE;
			}
			countDigit = 0;
		}
		else if (lpwStr[i] != 32 && ((lpwStr[i] - 48) > 9 || (lpwStr[i] - 48) < 0)) //whether string contains invalid character
		{
			MessageBox(0, MSG_CHARACTER_ERROR, 0);
			return TRUE;
		}
		else if (lpwStr[i] != 32) ++countDigit;
	}

	return FALSE;
}
//Before running this function, you should run IsInvalid funtion
//Clear whitespaces and dots to calculate conveniently. Ex: 10.000.000 => 10000000
size_t Standardize(_Inout_opt_ LPWSTR& lpwStr)
{
	SHORT countDot = 0, i = -1;
	INT oldLen = wcslen(lpwStr);
	LPWSTR lpwNewStr = new WCHAR[oldLen + 1];
	//Clear dots if it's not the decimal point
	while (lpwStr[++i])
	{
		if (lpwStr[i] == '.')
		{
			++countDot;
			if (countDot == 1) lpwNewStr[i] = lpwStr[i]; //suppose that this Dot is decimal point
		}
		else lpwNewStr[i - (countDot > 1 ? countDot - 1 : 0)] = lpwStr[i]; //countDot - 1 <=> eliminate decimal point
	}
	lpwNewStr[i - (countDot > 1 ? countDot - 1 : 0)] = 0;

	delete[]lpwStr;
	if (countDot > 1) //it's not a decimal point
	{
		lpwStr = new WCHAR[oldLen - countDot + 1];
		int j = 0;
		for (int i = 0; lpwNewStr[i]; ++i)
		{
			if (lpwNewStr[i] != '.') lpwStr[j++] = lpwNewStr[i];
		}
		lpwStr[j] = 0;
	}
	else lpwStr = _wcsdup(lpwNewStr);
	delete[]lpwNewStr;
	//Clear whitespaces
	CleanWString(lpwStr);

	return wcslen(lpwStr);
}
//Convert integer or real number to UNICODE (LPWSTR)
LPWSTR NumberToWCS(_In_ double number, _In_ SHORT nDecimalPlaces)
{
	LPWSTR lpwTemp = new WCHAR[20];
	LPWSTR lpwStr = new WCHAR[20];
	lpwStr[0] = 0;
	if (number < 0) wcscat(lpwStr, L"-");
	//Get integer place (lpwTemp saves integer place of number now)
	double integer = floor(number);
	if (integer != 0) {
		INT numberOfDigit = (INT)log10(integer) + 1;
		lpwTemp[numberOfDigit] = 0;
		WCHAR wcDigit[2];
		while (numberOfDigit > 0)
		{
			INT digit = INT(integer - 10 * floor(integer / 10));
			_itow(digit, wcDigit, 10);
			lpwTemp[--numberOfDigit] = wcDigit[0];
			integer /= 10;
		}
	}
	else
	{
		lpwTemp[0] = '0', lpwTemp[1] = 0;
	}
	wcscat(lpwStr, lpwTemp);
	//Get decimal place (lpwTemp saves decimal place of number now)
	integer = floor(number);
	double decimal = (number - integer) * pow(10, nDecimalPlaces); //get n decimal places
	if (decimal != 0) //it has decimal place
	{
		wcscat(lpwStr, L"."); //decimal point
		wcscat(lpwStr, _itow(decimal, lpwTemp, 10));
	}
	delete[]lpwTemp;

	return lpwStr;
}
//Before running this function, you should run Standardize function
//Ex: 10000 => 10.000
size_t AddDots(_Inout_opt_ LPWSTR& lpwStr)
{
	SHORT numberOfDots = wcslen(lpwStr) / 3; //the number of dot need to add in number
	if (numberOfDots * 3 == wcslen(lpwStr)) --numberOfDots; //Ex: 500 => numberOfDots = 0, 50 000 => numberOfDots = 1
	
	SHORT countDigit = 0;
	INT k = numberOfDots + wcslen(lpwStr) - 1;
	LPWSTR lpwNewStr = new WCHAR[k + 2];
	for (INT i = wcslen(lpwStr) - 1; i >= 0; --i)
	{
		if (lpwStr[i] == '.') //this number is a real number
		{
			delete[]lpwNewStr;
			return wcslen(lpwStr);
		}

		++countDigit;
		lpwNewStr[k--] = lpwStr[i];
		if (countDigit == 3 && i > 0)
		{
			countDigit = 0;
			lpwNewStr[k--] = ',';
		}
	}
	lpwNewStr[numberOfDots + wcslen(lpwStr)] = 0;

	delete[]lpwStr;
	lpwStr = lpwNewStr;

	return wcslen(lpwStr);
}