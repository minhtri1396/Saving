#pragma once

#include "resource.h"
#include "ProcessingNumbers.h"

void	OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void	OnPaint(HWND hwnd);
void	OnDestroy(HWND hwnd);
BOOL	OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
