/*

nsResize NSIS plug-in

Author:  Stuart 'Afrow UK' Welch
Company: Afrow Soft Ltd.
Website: http://www.afrowsoft.co.uk
E-mail:  afrowuk@afrowsoft.co.uk
Date:    13th April 2013
Version: 1.0.0.0

A small NSIS plug-in for resizing windows. Uses code from nsDialogs for unit/RTL conversion.

*/

#include <windows.h>
#include "nsResize.h"

#ifdef UNICODE
#include "nsis_unicode\pluginapi.h"
#else
#include "nsis_ansi\pluginapi.h"
#endif

HANDLE g_hInstance;
HWND g_hWndParent;
BOOL g_rtl;

BOOL WINAPI DllMain(HANDLE hInst, ULONG ul_reason_for_call, LPVOID lpReserved)
{
  g_hInstance = hInst;
  return TRUE;
}

static UINT_PTR PluginCallback(enum NSPIM msg)
{
  return 0;
}

static int ConvertPlacement(TCHAR* str, int total, BOOL height, BOOL add)
{
  TCHAR unit = *CharPrev(str, str + lstrlen(str));
  int x = myatoi(str);

  if (unit == TEXT('%'))
  {
    if (x < 0 && !add)
      return MulDiv(total, 100 + x, 100);
    return MulDiv(total, x, 100);
  }
  
  if (unit == TEXT('u'))
  {
    RECT r;
    r.left = r.top = x;
    r.right = r.bottom = 0;
    MapDialogRect(g_hWndParent, &r);

    if (height)
      return x >= 0 || add ? r.top : total + r.top;
    return x >= 0 || add ? r.left : total + r.left;
  }

  if (x < 0 && !add)
    return total + x;
  return x;
}

static void ConvertPosToRTL(int *x, int width, int dialogWidth)
{
  if (!g_rtl)
    return;

  *x = dialogWidth - width - *x;
}

static BOOL PopPlacement(HWND hWndControl, int* x, int* y, int* width, int* height, UINT* uFlags, BOOL add)
{
  RECT dialogRect;
  int  dialogWidth;
  int  dialogHeight;
  TCHAR buf[1024];
  
  GetClientRect(GetParent(hWndControl), &dialogRect);
  dialogWidth = dialogRect.right;
  dialogHeight = dialogRect.bottom;

  if (popstringn(buf, 1024))
    return FALSE;

  if (!*buf)
    *uFlags |= SWP_NOMOVE;
  else
    *x = ConvertPlacement(buf, dialogWidth, FALSE, add);

  if (popstringn(buf, 1024))
    return FALSE;

  if (!*buf)
    *uFlags |= SWP_NOMOVE;
  else
    *y = ConvertPlacement(buf, dialogHeight, TRUE, add);

  if (popstringn(buf, 1024))
    return FALSE;

  if (!*buf)
    *uFlags |= SWP_NOSIZE;
  else
    *width = ConvertPlacement(buf, dialogWidth, FALSE, add);

  if (popstringn(buf, 1024))
    return FALSE;

  if (!*buf)
    *uFlags |= SWP_NOSIZE;
  else
    *height = ConvertPlacement(buf, dialogHeight, TRUE, add);

  if (*uFlags & SWP_NOMOVE)
    *x = *y = 0;
  
  if (*uFlags & SWP_NOSIZE)
    *width = *height = 0;

  if (!add)
  {
    if (*uFlags & SWP_NOSIZE)
    {
      GetClientRect(hWndControl, &dialogRect);
      ConvertPosToRTL(x, dialogRect.right, dialogWidth);
    }
    else
    {
      ConvertPosToRTL(x, *width, dialogWidth);
    }
  }

  return TRUE;
}

static void GetRect(HWND hWnd, RECT* r)
{
  GetWindowRect(hWnd, r);
  MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)r, 2);
}

NSISFUNC(SetRTL)
{
  DLL_INIT();
  extra->RegisterPluginCallback((HMODULE)g_hInstance, PluginCallback);
  g_rtl = (BOOL)popint();
}

NSISFUNC(Set)
{
  DLL_INIT();
  {
    HWND hWndCtl = (HWND)popint();
    if (IsWindow(hWndCtl))
    {
      int x, y, width, height;
      UINT uFlags = SWP_NOZORDER;
      if (PopPlacement(hWndCtl, &x, &y, &width, &height, &uFlags, FALSE))
        SetWindowPos(hWndCtl, NULL, x, y, width, height, uFlags);
    }
  }
}

NSISFUNC(Add)
{
  DLL_INIT();
  {
    HWND hWndCtl = (HWND)popint();
    if (IsWindow(hWndCtl))
    {
      int x, y, width, height;
      UINT uFlags = SWP_NOZORDER;
      if (PopPlacement(hWndCtl, &x, &y, &width, &height, &uFlags, TRUE))
      {
        RECT pos;
        GetRect(hWndCtl, &pos);
        SetWindowPos(hWndCtl, NULL, pos.left + x, pos.top + y, (pos.right - pos.left) + width, (pos.bottom - pos.top) + height, uFlags);
      }
    }
  }
}

NSISFUNC(Top)
{
  DLL_INIT();
  {
    HWND hWndCtl = (HWND)popint();
    if (IsWindow(hWndCtl))
    {
      SetWindowPos(hWndCtl, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
    }
  }
}

NSISFUNC(GetPosPx)
{
  DLL_INIT();
  {
    HWND hWndCtl = (HWND)popint();
    if (IsWindow(hWndCtl))
    {
      RECT pos;
      GetRect(hWndCtl, &pos);
      MapDialogRect(g_hWndParent, &pos);
      pushint(pos.top);
      pushint(pos.left);
    }
  }
}

NSISFUNC(GetPos)
{
  DLL_INIT();
  {
    HWND hWndCtl = (HWND)popint();
    if (IsWindow(hWndCtl))
    {
      RECT pos;
      GetRect(hWndCtl, &pos);
      pushint(pos.top);
      pushint(pos.left);
    }
  }
}

NSISFUNC(GetSizePx)
{
  DLL_INIT();
  {
    HWND hWndCtl = (HWND)popint();
    if (IsWindow(hWndCtl))
    {
      RECT pos;
      GetRect(hWndCtl, &pos);
      MapDialogRect(g_hWndParent, &pos);
      pushint(pos.bottom);
      pushint(pos.right);
    }
  }
}

NSISFUNC(GetSize)
{
  DLL_INIT();
  {
    HWND hWndCtl = (HWND)popint();
    if (IsWindow(hWndCtl))
    {
      RECT pos;
      GetRect(hWndCtl, &pos);
      pushint(pos.bottom);
      pushint(pos.right);
    }
  }
}