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
// Filename    : shellexecute.cpp
// Description : Provides a function that uses the automation facilities of Explorer to run the
//               specified operation on the specified file.
//
//               Code adapted from https://devblogs.microsoft.com/oldnewthing/20131118-00/?p=2643
// 
//************************************************************************************************

#include "ccltools.h"
#include <ShlObj.h>
#include <comdef.h>

_COM_SMARTPTR_TYPEDEF (IShellDispatch2, IID_IShellDispatch2);

///////////////////////////////////////////////////////////////////////////////////////////////////

static inline void throwIfFailed (HRESULT hr)
{
	if(FAILED (hr))
		_com_issue_error (hr);
}

///////////////////////////////////////////////////////////////////////////////////////////////////                         

static void findDesktopFolderView (REFIID riid, void** ppv)
{
	IShellWindowsPtr shellWindows;
	throwIfFailed (shellWindows.CreateInstance (CLSID_ShellWindows));

	_variant_t empty;
	_variant_t loc (CSIDL_DESKTOP);
	long hwnd = 0;
	IDispatchPtr dispatch;
	throwIfFailed (shellWindows->FindWindowSW (&loc, &empty, SWC_DESKTOP, &hwnd, SWFO_NEEDDISPATCH, &dispatch));

	IShellBrowserPtr browser;
	IServiceProviderPtr provider = dispatch;
	throwIfFailed (provider->QueryService (SID_STopLevelBrowser, IID_PPV_ARGS (&browser)));

	IShellViewPtr view;
	throwIfFailed (browser->QueryActiveShellView (&view));
	throwIfFailed (view->QueryInterface (riid, ppv));
}

///////////////////////////////////////////////////////////////////////////////////////////////////

static void getDesktopAutomationObject (REFIID riid, void** ppv)
{
	IShellViewPtr view;
	findDesktopFolderView (IID_PPV_ARGS (&view));

	IDispatchPtr dispView;
	throwIfFailed (view->GetItemObject (SVGIO_BACKGROUND, IID_PPV_ARGS (&dispView)));
	throwIfFailed (dispView->QueryInterface (riid, ppv));
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool shellExecute (LPCWSTR file, LPCWSTR args, LPCWSTR directory, LPCWSTR operation, int showCmd)
{
	try
	{
		IShellFolderViewDualPtr folderView;
		getDesktopAutomationObject (IID_PPV_ARGS (&folderView));

		IDispatchPtr dispShell;
		throwIfFailed (folderView->get_Application (&dispShell));

		IShellDispatch2Ptr dispShell2 = dispShell;
		throwIfFailed (dispShell2->ShellExecute (
			_bstr_t (file),
			_variant_t (args ? args : L""),
			_variant_t (directory ? directory : L""),
			_variant_t (operation ? operation : L""),
			_variant_t (showCmd)));

		return true;
	}
	catch(const _com_error& e)
	{
		UNREFERENCED_PARAMETER (e); // unused in release build
		TRACE (L"shellExecute failed (HR: 0x%08x, reason: %s)", e.Error (), e.ErrorMessage ());
		return false;
	}
}
