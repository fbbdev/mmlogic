// Ignores all right mouse button clicks to the toolbar.
// This works around a bug in Windows XP toolbar where
// a button gets "stuck" if user clicks on it with
// both the left and right mouse buttons down.

class CToolBarEx : public CToolBar
{
protected:
   LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
}
;