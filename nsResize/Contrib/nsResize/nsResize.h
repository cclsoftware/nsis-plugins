#ifndef __NsThread_H__
#define __NsThread_H__

#define NSISFUNC(name) void __declspec(dllexport) name(HWND hWndParent, int string_size, TCHAR* variables, stack_t** stacktop, extra_parameters* extra)
#define DLL_INIT() { EXDLL_INIT(); g_hWndParent = hWndParent; }

#endif