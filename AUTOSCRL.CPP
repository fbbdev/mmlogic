// autoscvw.cpp : implementation file
//
//
// CAutoScrollView is derived from CScrollView. It adds the AutoScroll feature
// that is needed in many applications. AutoScrolling means that the window
// begins to scroll as soon as the mouse cursor leaves the client area of the
// current View while the left mouse button is pressed. You can customize the
// button used to autoscroll using the SetAutoButton inline member function.
// SetAutoButton accepts one parameter of type _AutoButton: mbLeft, mbRight or
// mbMiddle. SetAutoButton returns the button type that was active before the
// call.
//
// The amount by which the View is scrolled depends on the distance between the
// the window border and the mouse cursor. The greater the distance, the faster
// the View scrolls.
//
// You can enable or disable the AutoScroll feature by using the
// EnableAutoScrolling() inline member function. It accepts one parameter
// of type BOOL.
//
// By default, autoscrolling is enabled with the left button.
//
// BOOL IsAutoScrolling() tells you whether autoscrolling operations are
// underway.
//
// To give your application's View a chance to properly update the screen while
// autoscrolling, CAutoScrollView calls its OnAutoScroll() virtual member
// function just before and just after scrolling. Override this function in
// your View if you want to take some action whenever autoscrolling occurs.
// By default, OnAutoScroll does nothing.
//
// OnAutoScroll accepts two parameters:
//
// virtual void OnAutoScroll(CPoint point, BOOL bBeforeScroll);
//
// point indicates the current position of the mouse cursor in client device
// coordinates. That is, the ScreenToClient() function has been applied to point
// but no DPtoLP operation has been done.
//
// bBeforeScroll is TRUE when OnAutoScroll is called before scrolling and
// FALSE otherwise.
//
// Most of the time you will not have any opportunity to initialize a
// CAutoScrollView yourself. So, member variables are initialized in the
// constructor directly.
//
// CAutoScrollView automatically adapts to the mapping mode. For example, if
// you have set a metric mapping mode, the nMapFactor will be used to
// reverse y coordinates.
//
// CAutoScrollView also corrects an annoying behavior of
// CScrollView::ScrollToPosition. This member function doesn't check whether
// the scroll limit has already been reached and always tries to scroll. This
// wouldn't be a problem if a call to ScrollWindow was not made systematically.
// This generates flicker. When AutoScrolling, this condition doesn't occur.
//

#include "stdafx.h"
//#include "autoscrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoScrollView

IMPLEMENT_DYNAMIC(CAutoScrollView, CScrollView)

CAutoScrollView::CAutoScrollView()
{
   m_bAutoScroll = TRUE;
   m_bIsScrolling = FALSE;
}

BEGIN_MESSAGE_MAP(CAutoScrollView, CScrollView)
   //{{AFX_MSG_MAP(CAutoScrollView)
   ON_WM_LBUTTONDOWN()
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoScrollView drawing

void CAutoScrollView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CAutoScrollView message handlers

void CAutoScrollView::AutoScroll(UINT nRefMessage)
{
   MSG   msg;             // dummmy message structure to process incoming
   // messages while autoscrolling.
   CPoint ptScrollPos,    // Current scroll position - logical units
      ptDevScrollPos, // Current scroll position - device units
      ptCursorPos;    // Current mouse cursor position
   CRect  rc;          // Client area
   long   dx, dy;         // Scrolling increment
   SIZE   sizeTotal,      // CScrollView scroll data
      sizePage,
      sizeLine;
   int    nMapMode,       // Mapping mode
      nMapFactor,     // Accounts for mapping mode
      xMin, xMax,
      yMin, yMax;   // Scroll range

   if (!m_bAutoScroll)
      return;

   msg.message = 0;   // forces at least one loop.
   SetCapture();
   GetDeviceScrollSizes(nMapMode, sizeTotal, sizePage, sizeLine);

   // We keep track of the scroll range because CScrollView::ScrollToPosition always
   // try to scroll even if the scroll limit has been reached. This results in screen
   // flickering when ScrollWindow is called.
   GetScrollRange(SB_HORZ, &xMin, &xMax);
   GetScrollRange(SB_VERT, &yMin, &yMax);

   // Process all messages until the relevant mouse button
   // has been released. nRefMessage depends on which button
   // has been used to trigger autoscrolling.
   //   while (msg.message != nRefMessage)
   BOOL bSawRefMessage = FALSE;

   while (!bSawRefMessage)
   {
      // Process incoming messages until autoscroll button is released

      // You cannot peek here because it may process an invalidate
      // due to the scrolling.

      /*
      if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
      {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
      }
      */

      ptScrollPos = GetScrollPosition();
      ptDevScrollPos = GetDeviceScrollPosition();
      GetCursorPos(&ptCursorPos);
      ScreenToClient(&ptCursorPos);
      GetClientRect(&rc);
      dx = 0L;
      dy = 0L;

      if ((ptCursorPos.y < 0) && (ptDevScrollPos.y != yMin))
         // Cursor is above client area
         dy = min(-sizeLine.cy, max(-sizePage.cy, (ptCursorPos.y/10) * sizeLine.cy));
      else if ((ptCursorPos.y > rc.bottom) &&  (ptDevScrollPos.y != yMax))
         // Cursor is below client area
         dy = max(sizeLine.cy, min(sizePage.cy, ((ptCursorPos.y - rc.bottom)/10) * sizeLine.cy));
      // otherwise we can't scroll anyway

      if ((ptCursorPos.x < 0) && (ptDevScrollPos.x != xMin))
         // Cursor is on the left of the client area
         dx = min(-sizeLine.cx, max(-sizePage.cx, (ptCursorPos.x/10) * sizeLine.cx));
      else if ((ptCursorPos.x > rc.right) && (ptDevScrollPos.x != xMax))
         // Cursor is on the right of the client area
         dx = max(sizeLine.cx, min(sizePage.cx, ((ptCursorPos.x - rc.right)/10) * sizeLine.cx));
      // otherwise we can't scroll anyway

      // if mouse cursor is dragging outside the client area, scrolling occurs
      if ((dx != 0) || (dy != 0))
      {
         // Flip the Y coordinate if we're not in MM_TEXT
         nMapFactor = (nMapMode == MM_TEXT) ? 1 : -1;
         ptScrollPos.y += (int) dy * nMapFactor;
         ptScrollPos.x += (int) dx;
         m_bIsScrolling = TRUE;
         OnAutoScroll(ptCursorPos, TRUE);
         ScrollToPosition(ptScrollPos);

         while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            //            if (msg.message == nRefMessage) break;
            if (msg.message == nRefMessage) bSawRefMessage = TRUE;
         }

         //         if (!bSawRefMessage)
         OnAutoScroll(ptCursorPos, FALSE);
      }
      else
      {

         while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            //            if (msg.message == nRefMessage) break;
            if (msg.message == nRefMessage) bSawRefMessage = TRUE;
         }

         m_bIsScrolling = FALSE;
      }
   }
   ReleaseCapture();
   m_bIsScrolling = FALSE;
}

void CAutoScrollView::OnLButtonDown(UINT nFlags, CPoint point)
{
   CScrollView::OnLButtonDown(nFlags, point);
   AutoScroll(WM_LBUTTONUP);
}

void CAutoScrollView::OnAutoScroll(CPoint /*point*/, BOOL /*bBeforeScroll*/)
{
}

