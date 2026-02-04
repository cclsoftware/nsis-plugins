//************************************************************************************************
//
// CCL Tools NSIS Plugin
// 
// Copyright (c) 2026 CCL Software Licensing GmbH.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of
//    conditions and the following disclaimer in the documentation and /or other materials provided
//    with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to
//    endorse or promote products derived from this software without specific prior written
//    permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
// FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Filename    : dllmain.cpp
// Description : DLL export functions and main entry point
//
//************************************************************************************************

#include "ccltools.h"
#include <string>
#include <nsis/pluginapi.h>

#define PLUGIN_API __declspec(dllexport)

#ifdef _DEBUG
#define WAIT_FOR_DEBUGGER() \
	MessageBox (g_hwndParent, L"Attach debugger now, then click \"OK\" to continue.", L"Debug", MB_OK | MB_ICONHAND)
#else
#define WAIT_FOR_DEBUGGER() ((void)0)
#endif

static HINSTANCE g_hInstance = nullptr;
static HWND g_hwndParent = nullptr;

///////////////////////////////////////////////////////////////////////////////////////////////////

static bool popStdString (std::wstring &str)
{
	str.resize (g_stringsize);

	int result = popstring (&str[0]);
	int length = result ? 0 : wcslen (str.c_str ());

	str.resize (length);
	return result == 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" void PLUGIN_API runFromExplorer (HWND hwndParent, int string_size, LPTSTR variables, stack_t** stacktop, extra_parameters* extra)
{
	EXDLL_INIT ();
	g_hwndParent = hwndParent;

	WAIT_FOR_DEBUGGER ();

	std::wstring file;
	if(popStdString (file))
	{
		if(shellExecute (file.c_str (), nullptr, nullptr, nullptr, SW_SHOW))
		{
			pushint (1); // success;
			return;
		}
	}

	pushint (0); // failure
}

///////////////////////////////////////////////////////////////////////////////////////////////////

extern "C" BOOL WINAPI DllMain (HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	g_hInstance = hInstDLL;
	return TRUE;
}
