nsResize NSIS plug-in

Author:  Stuart 'Afrow UK' Welch
Company: Afrow Soft Ltd
Date:    13th April 2013
Version: 1.0.0.0

A small NSIS plug-in for moving or resizing windows/controls.

See Examples\nsResize\*.

------------------------------------------------------------------------
Macros
------------------------------------------------------------------------

nsResize.nsh includes macros used by the LargeWindow example script.

------------------------------------------------------------------------
Functions
------------------------------------------------------------------------

  nsResize::SetRTL $(^RTL)

  Sets right-to-left mode on or off. This is only needed when using the
  nsResize::Set function.

------------------------------------------------------------------------

  nsResize::Set control_HWND x y width height

  Sets a control's new X and Y coordinates and a new width and height.
  You may use the same unit values as nsDialogs. An empty string for x
  or y will ensure the control is not moved. An empty string for width
  or height will ensure the control is not resized.

------------------------------------------------------------------------

  nsResize::Add control_HWND x y width height

  Adds the given X, Y, width and height values. You may use the same
  unit values as nsDialogs. Note that special treatment must be done for
  right-to-left languages.

------------------------------------------------------------------------

  nsResize::Top control_HWND

  Moves a control to the top of the Z-order.

------------------------------------------------------------------------

  nsResize::GetPos control_HWND
  Pop $X
  Pop $Y

  Gets the control position in dialog units relative to its parent
  window.

------------------------------------------------------------------------

  nsResize::GetPosPx control_HWND
  Pop $X
  Pop $Y

  Gets the control position in pixels relative to its parent window.

------------------------------------------------------------------------

  nsResize::GetSize control_HWND
  Pop $Width
  Pop $Height

  Gets the control size in dialog units.

------------------------------------------------------------------------

  nsResize::GetSizePx control_HWND
  Pop $Width
  Pop $Height

  Gets the control size in pixels.

------------------------------------------------------------------------
Change Log
------------------------------------------------------------------------

1.0.0.0 - 13th April 2013
* First version.

------------------------------------------------------------------------
License
------------------------------------------------------------------------

This plug-in is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this plug-in.

Permission is granted to anyone to use this plug-in for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this plug-in must not be misrepresented; you must not
   claim that you wrote the original plug-in.
   If you use this plug-in in a product, an acknowledgment in the
   product documentation would be appreciated but is not required.
2. Altered versions must be plainly marked as such, and must not be
   misrepresented as being the original plug-in.
3. This notice may not be removed or altered from any distribution.