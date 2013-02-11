#include "stdafx.h"

// Ignores all right mouse button clicks to the toolbar.
// This works around a bug in Windows XP toolbar where
// a button gets "stuck" if user clicks on it with
// both the left and right mouse buttons down.

LRESULT CToolBarEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam )
{
   // Mask reporting of right mouse button

   if (message == WM_LBUTTONUP ||
      message == WM_LBUTTONDOWN ||
      message == WM_LBUTTONDBLCLK)
      wParam = wParam & ~MK_RBUTTON;

   // Gobble messages dealing with right mouse button

   if (message == WM_RBUTTONUP ||
      message == WM_RBUTTONDOWN ||
      message == WM_RBUTTONDBLCLK)
      return 0;

   // Call superclass to process message

   return CToolBar::WindowProc(message, wParam, lParam);
}
