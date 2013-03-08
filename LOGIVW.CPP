// Logivw.cpp : implementation of the CLogiView class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// private clipboard format (list of Draw objects)
CLIPFORMAT CLogiView::m_cfLogi = (CLIPFORMAT)::RegisterClipboardFormat("Logic Program");

static UINT WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);

/////////////////////////////////////////////////////////////////////////////
// CLogiView

IMPLEMENT_DYNCREATE(CLogiView, CAutoScrollView)

BEGIN_MESSAGE_MAP(CLogiView, CAutoScrollView)
   //{{AFX_MSG_MAP(CLogiView)
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
   ON_WM_LBUTTONDBLCLK()
   ON_WM_SETCURSOR()
   ON_COMMAND(ID_DRAW_SELECTOR_INTERNAL, OnDrawSelector)
   ON_COMMAND(ID_DRAW_SELECTOR, OnDrawSelector)
   ON_COMMAND(ID_DRAW_WIRE, OnDrawWire)
   ON_COMMAND(ID_DRAW_ANDGATE, OnDrawANDGate)
   ON_COMMAND(ID_DRAW_ORGATE, OnDrawORGate)
   ON_COMMAND(ID_DRAW_INVERTGATE, OnDrawINVERTGate)
   ON_COMMAND(ID_DRAW_OSCILLATORGATE, OnDrawOscillatorGate)
   ON_COMMAND(ID_DRAW_LEDGATE, OnDrawLedGate)
   ON_COMMAND(ID_DRAW_SWITCHGATE, OnDrawSwitchGate)
   ON_COMMAND(ID_DRAW_BUZZERGATE, OnDrawBuzzerGate)
   ON_COMMAND(ID_DRAW_NULLGATE, OnDrawNULLGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_SELECTOR, OnUpdateDrawSelector)
   ON_UPDATE_COMMAND_UI(ID_DRAW_WIRE, OnUpdateDrawWire)
   ON_UPDATE_COMMAND_UI(ID_DRAW_ANDGATE, OnUpdateDrawANDGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_ORGATE, OnUpdateDrawORGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_INVERTGATE, OnUpdateDrawINVERTGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_OSCILLATORGATE, OnUpdateDrawOscillatorGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_LEDGATE, OnUpdateDrawLedGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_SWITCHGATE, OnUpdateDrawSwitchGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_BUZZERGATE, OnUpdateDrawBuzzerGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_NULLGATE, OnUpdateDrawNULLGate)
   ON_UPDATE_COMMAND_UI(ID_OBJECT_MOVEBACK, OnUpdateSingleSelect)
   ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR, OnUpdateAnySelect)
   ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
   ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
   ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
   ON_UPDATE_COMMAND_UI(ID_EDIT_PROPERTIES, OnUpdateEditProperties)
   ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, OnUpdateEditSelectAll)
   ON_UPDATE_COMMAND_UI(ID_EDIT_FIND, OnUpdateEditFind)
   ON_UPDATE_COMMAND_UI(ID_EDIT_REPLACE, OnUpdateEditReplace)
   ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
   ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
   ON_WM_SIZE()
   ON_WM_ERASEBKGND()
   ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
   ON_COMMAND(ID_EDIT_CUT, OnEditCut)
   ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
   ON_WM_SETFOCUS()
   ON_COMMAND(ID_EDIT_PROPERTIES, OnEditProperties)
   ON_COMMAND(ID_DRAW_LED7GATE, OnDrawLed7Gate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_LED7GATE, OnUpdateDrawLed7Gate)
   ON_COMMAND(ID_DRAW_ASCIIDISPLAY, OnDrawAsciidisplayGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_ASCIIDISPLAY, OnUpdateDrawAsciidisplayGate)
   ON_COMMAND(ID_DRAW_ASCIIKEYBOARD, OnDrawAsciikeyboardGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_ASCIIKEYBOARD, OnUpdateDrawAsciikeyboardGate)
   ON_COMMAND(ID_DRAW_GROUND, OnDrawGroundGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_GROUND, OnUpdateDrawGroundGate)
   ON_COMMAND(ID_DRAW_PLUS, OnDrawPlusGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_PLUS, OnUpdateDrawPlusGate)
   ON_COMMAND(ID_DRAW_PORTIN, OnDrawPortinGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_PORTIN, OnUpdateDrawPortinGate)
   ON_COMMAND(ID_DRAW_PORTOUT, OnDrawPortoutGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_PORTOUT, OnUpdateDrawPortoutGate)
   ON_COMMAND(ID_DRAW_READFILE, OnDrawReadfileGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_READFILE, OnUpdateDrawReadfileGate)
   ON_COMMAND(ID_DRAW_SIGNALRECEIVER, OnDrawSignalreceiverGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_SIGNALRECEIVER, OnUpdateDrawSignalreceiverGate)
   ON_COMMAND(ID_DRAW_SIGNALSENDER, OnDrawSignalsenderGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_SIGNALSENDER, OnUpdateDrawSignalsenderGate)
   ON_COMMAND(ID_DRAW_SOUNDWAVE, OnDrawSoundwaveGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_SOUNDWAVE, OnUpdateDrawSoundwaveGate)
   ON_COMMAND(ID_DRAW_TEXT, OnDrawTextGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_TEXT, OnUpdateDrawTextGate)
   ON_COMMAND(ID_DRAW_WRITEFILE, OnDrawWritefileGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_WRITEFILE, OnUpdateDrawWritefileGate)
   ON_COMMAND(ID_DRAW_FLIPFLOP, OnDrawFlipflopGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_FLIPFLOP, OnUpdateDrawFlipflopGate)
   ON_COMMAND(ID_DRAW_KEYPAD, OnDrawKeypadGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_KEYPAD, OnUpdateDrawKeypadGate)
   ON_COMMAND(ID_DRAW_BITMAP, OnDrawBitmapGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_BITMAP, OnUpdateDrawBitmapGate)
   ON_COMMAND(ID_DRAW_COUNTER, OnDrawCounterGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_COUNTER, OnUpdateDrawCounterGate)
   ON_COMMAND(ID_DRAW_BREAK, OnDrawBreakGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_BREAK, OnUpdateDrawBreakGate)
   ON_WM_CHAR()
   ON_COMMAND(ID_DRAW_MEMORY, OnDrawMemoryGate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_MEMORY, OnUpdateDrawMemoryGate)
   ON_WM_KEYDOWN()
   ON_WM_KEYUP()
   ON_COMMAND(ID_SET_FONT, OnSetFont)
   ON_COMMAND(ID_DRAW_MUX, OnDrawMux)
   ON_UPDATE_COMMAND_UI(ID_DRAW_MUX, OnUpdateDrawMux)
   ON_COMMAND(ID_DRAW_BITBUCKET, OnDrawBitbucket)
   ON_UPDATE_COMMAND_UI(ID_DRAW_BITBUCKET, OnUpdateDrawBitbucket)
   ON_COMMAND(ID_DRAW_ALU, OnDrawAlu)
   ON_UPDATE_COMMAND_UI(ID_DRAW_ALU, OnUpdateDrawAlu)
   ON_COMMAND(ID_DRAW_RANDOM, OnDrawRandom)
   ON_UPDATE_COMMAND_UI(ID_DRAW_RANDOM, OnUpdateDrawRandom)
   ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
   ON_COMMAND(ID_DRAW_XORGATE, OnDrawXor)
   ON_UPDATE_COMMAND_UI(ID_DRAW_XORGATE, OnUpdateDrawXor)
   ON_COMMAND(ID_DRAW_CLOCK, OnDrawClock)
   ON_UPDATE_COMMAND_UI(ID_DRAW_CLOCK, OnUpdateDrawClock)
   ON_COMMAND(ID_DRAW_TIMER, OnDrawTimer)
   ON_UPDATE_COMMAND_UI(ID_DRAW_TIMER, OnUpdateDrawTimer)
   ON_COMMAND(ID_VIEW_NEXTPAGE, OnViewNextpage)
   ON_UPDATE_COMMAND_UI(ID_VIEW_NEXTPAGE, OnUpdateViewNextpage)
   ON_COMMAND(ID_VIEW_PREVIOUSPAGE, OnViewPreviouspage)
   ON_UPDATE_COMMAND_UI(ID_VIEW_PREVIOUSPAGE, OnUpdateViewPreviouspage)
   ON_COMMAND(ID_DRAW_ROBOT, OnDrawRobot)
   ON_UPDATE_COMMAND_UI(ID_DRAW_ROBOT, OnUpdateDrawRobot)
   ON_COMMAND(ID_DRAW_NETWORK, OnDrawNetwork)
   ON_UPDATE_COMMAND_UI(ID_DRAW_NETWORK, OnUpdateDrawNetwork)
   ON_COMMAND(ID_DRAW_SELECT, OnDrawSelectgate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_SELECT, OnUpdateDrawSelectgate)
   ON_COMMAND(ID_VIEW_SNAPSELECTIONTOGRID, OnViewSnapSelectiontogrid)
   ON_UPDATE_COMMAND_UI(ID_VIEW_SNAPSELECTIONTOGRID, OnUpdateViewSnapSelectiontogrid)
   ON_COMMAND(ID_DRAW_TRISTATE, OnDrawTristategate)
   ON_UPDATE_COMMAND_UI(ID_DRAW_TRISTATE, OnUpdateDrawTristategate)
   ON_COMMAND(ID_DRAW_BUS, OnDrawBus)
   ON_UPDATE_COMMAND_UI(ID_DRAW_BUS, OnUpdateDrawBus)
   ON_COMMAND(ID_DRAW_ANALYZE, OnDrawAnalyze)
   ON_UPDATE_COMMAND_UI(ID_DRAW_ANALYZE, OnUpdateDrawAnalyze)
   ON_COMMAND(ID_DRAW_TAPEDRIVE, OnDrawTapedrive)
   ON_UPDATE_COMMAND_UI(ID_DRAW_TAPEDRIVE, OnUpdateDrawTapedrive)
   ON_WM_RBUTTONDOWN()
   ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
   ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
   ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
   ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
   ON_COMMAND(ID_VIEW_GOTOPAGE, OnViewGotoPage)
   ON_UPDATE_COMMAND_UI(ID_VIEW_GOTOPAGE, OnUpdateGotoPage)
   ON_REGISTERED_MESSAGE(WM_FINDREPLACE, OnFindReplace)
   ON_COMMAND(ID_EDIT_FIND, OnEditFind)
   ON_COMMAND(ID_EDIT_REPLACE, OnEditReplace)
   ON_COMMAND(ID_DRAW_BISECTWIRE, OnDrawBisectwire)
   ON_UPDATE_COMMAND_UI(ID_DRAW_BISECTWIRE, OnUpdateDrawBisectwire)
   //}}AFX_MSG_MAP
   // Standard printing commands
   ON_UPDATE_COMMAND_UI(ID_INDICATOR_CYCLE, OnUpdateIndicatorCycle)
   ON_UPDATE_COMMAND_UI(ID_INDICATOR_PAGE, OnUpdateIndicatorPage)
   ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogiView construction/destruction

CLogiView::CLogiView()
{
   m_gridColor = RGB(128, 128, 128);
   m_bActive = FALSE;
   m_iPage = 1;
   m_frDialog = NULL;
}

CLogiView::~CLogiView()
{
   if (m_frDialog != NULL)
      m_frDialog->DestroyWindow();
}

void CLogiView::OnPrint( CDC* pDC, CPrintInfo* pInfo )
{
   int devHorz;
   int devVert;
   int devXppi;
   int devYppi;
   float Aspectdoc;
   float Aspectppi;
   float Aspectdev;
   UINT uXDocSize = 0;
   UINT uYDocSize = 0;

   uXDocSize = GetDocument()->m_uCanvasWidth;
   uYDocSize = GetDocument()->m_uCanvasHeight;

   // custom MM_LOENGLISH with positive y down
   pDC->SetMapMode(MM_ANISOTROPIC);

   // set the origin of the coordinate system to the center of the page
   //   CPoint ptOrg;
   //   ptOrg.x = GetDocument()->GetSize().cx / 2;
   //   ptOrg.y = GetDocument()->GetSize().cy / 2;

   // ptOrg is in logical coordinates
   //   pDC->SetWindowOrg(-ptOrg.x,-ptOrg.y);
   pDC->SetWindowOrg(0, 0);
   pDC->SetWindowExt(uXDocSize, uYDocSize);

   // get device size in pixels

   devHorz = pDC->GetDeviceCaps(HORZRES);
   devVert = pDC->GetDeviceCaps(VERTRES);

   // get pixels per inch

   devXppi = pDC->GetDeviceCaps(LOGPIXELSX);
   devYppi = pDC->GetDeviceCaps(LOGPIXELSY);

   // Normalize the device Size, this allows us to handle devices in which ppi in X and Y differ

   if (devYppi < devXppi)
   {
      Aspectppi = ((float) devYppi) / ((float) devXppi);
      devHorz = (int) (devHorz*Aspectppi);
   }
   else
   {
      Aspectppi = ((float) devYppi) / ((float) devXppi);
      devVert = (int) (devVert*Aspectppi);
   }

   // Now modify size such that it's a best fit

   //ASSERT(YDOCSIZE < XDOCSIZE);

   Aspectdev = ((float) devVert) / ((float) devHorz);
   Aspectdoc = ((float) uYDocSize) / ((float) uXDocSize);

   if (Aspectdev > Aspectdoc)
   {
      devVert = (int) (devHorz*Aspectdoc);
   }
   else
   {
      devHorz = (int) (devVert/Aspectdoc);
   }

   // Unnormalize

   if (devYppi < devXppi)
   {
      devHorz = (int) (devHorz/Aspectppi);
   }
   else
   {
      devVert = (int) (devVert/Aspectppi);
   }

   pDC->SetViewportOrg(0, 0);
   pDC->SetViewportExt(devHorz, devVert);

   //   int iPenWidth = (devHorz/XDOCSIZE);
   //   if (iPenWidth < 10) iPenWidth = 1;

   //   CPen pen;
   //   pen.CreatePen(PS_SOLID, iPenWidth, RGB(0,0,0));
   //   CPen* pOldPen = pDC->SelectObject(&pen);

   int iSavePage = m_iPage;

   SetPage(pInfo->m_nCurPage);
   OnDraw(pDC);
   SetPage(iSavePage);

   //   pDC->SelectObject(pOldPen);
}

BOOL CLogiView::PreCreateWindow(CREATESTRUCT& cs)
{
   ASSERT(cs.style & WS_CHILD);
   if (cs.lpszClass == NULL) cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS);
   return TRUE;
}

void CLogiView::OnActivateView(BOOL bActivate, CView* pActiveView, CView* pDeactiveView)
{
   CView::OnActivateView(bActivate, pActiveView, pDeactiveView);

   // invalidate selections when active status changes
   if (m_bActive != bActivate)
   {
      // if becoming active update as if active
      if (bActivate) m_bActive = bActivate;
      if (!m_selection.IsEmpty()) OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);
      m_bActive = bActivate;
   }
}

/////////////////////////////////////////////////////////////////////////////
// CLogiView Drawing

void CLogiView::InvalObj(CLogiObj* pObj)
{
   CRect rect = pObj->m_position;

   rect.NormalizeRect();

   if (m_bActive && IsSelected(pObj))
   {
      rect.InflateRect(4, 4, 4, 4);
   }
   else
   {
      rect.InflateRect(2, 2, 2, 2);
   }

   DocToClient(rect);

   InvalidateRect(rect, FALSE);
}

void CLogiView::OnUpdate(CView *, LPARAM lHint, CObject* pHint)
{
   switch (lHint)
   {
   case HINT_UPDATE_ZOOM:      // reLogi entire window
      {
         // Compute centering point for zoom

         CPoint center = m_rLastDraw.CenterPoint();
         CSize docsize = GetDocument()->GetSize();

         // If current center outside of document, center on document

         if (center.x > docsize.cx)
            center.x = docsize.cx / 2;
         if (center.y > docsize.cy)
            center.y = docsize.cy / 2;

         // Update scrollbars

         CSize size;
         size = GetDocument()->GetSize();
         size.cx = GetDocument()->GetZoom(size.cx);
         size.cy = GetDocument()->GetZoom(size.cy);
         SetScrollSizes(MM_TEXT, size);

         CRect rect;
         GetClientRect(&rect);
         ClientToDoc(rect);

         // Scroll to center desired center position

         center.Offset(-rect.Width()/2, -rect.Height()/2);
         center.x = GetDocument()->GetZoom(center.x);
         center.y = GetDocument()->GetZoom(center.y);

         if (center.x < 0)
            center.x = 0;

         if (center.y < 0)
            center.y = 0;

         if (center.x > GetScrollLimit(SB_HORZ))
            center.x = GetScrollLimit(SB_HORZ);

         if (center.y > GetScrollLimit(SB_VERT))
            center.y = GetScrollLimit(SB_VERT);

         ScrollToPosition(center);
         SetScrollSizes(MM_TEXT, size);
      }

   case HINT_UPDATE_WINDOW:    // reLogi entire window
      Invalidate(FALSE);
      break;

   case HINT_UPDATE_LOGIOBJ:   // a single object has changed
      InvalObj((CLogiObj*)pHint);
      break;

   case HINT_REMOVE_LOGIOBJ:   // a single object has changed
      InvalObj((CLogiObj*)pHint);
      GetDocument()->Remove((CLogiObj*)pHint);
      RemoveFromFindReplace((CLogiObj*)pHint);
      break;

   case HINT_UPDATE_SELECTION: // an entire selection has changed
      {
         CObList* pList = pHint != NULL ? (CObList*)pHint : &m_selection;
         POSITION pos = pList->GetHeadPosition();
         while (pos != NULL) InvalObj((CLogiObj*)pList->GetNext(pos));
      }
      break;

   case HINT_DELETE_SELECTION: // an entire selection has been removed
      {
         CObList* pList = (CObList*)pHint;
         if (pHint != &m_selection)
         {
            POSITION pos = pList->GetHeadPosition();
            while (pos != NULL)
            {
               CLogiObj* pObj = (CLogiObj*)pList->GetNext(pos);
               InvalObj(pObj);
               Remove(pObj);   // remove it from this view's selection
            }
         }

         POSITION pos = pList->GetHeadPosition();
         while (pos != NULL)
            RemoveFromFindReplace((CLogiObj*)pList->GetNext(pos));
         break;
      }

   default:
      ASSERT(FALSE);
      break;
   }
}

void CLogiView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
   CScrollView::OnPrepareDC(pDC, pInfo);

   // mapping mode is MM_ANISOTROPIC
   // these extents setup a mode similar to MM_LOENGLISH
   // MM_LOENGLISH is in .01 physical inches
   // these extents provide .01 logical inches

   pDC->SetMapMode(MM_ANISOTROPIC);

   //   pDC->SetViewportOrg(0, 0); // why does this cause scroll to fail
   pDC->SetViewportExt(GetDocument()->GetZoom(XVIEWSIZE), GetDocument()->GetZoom(YVIEWSIZE));

   // set the origin of the coordinate system to the center of the page
   //   CPoint ptOrg;
   //   ptOrg.x = GetDocument()->GetSize().cx / 2;
   //   ptOrg.y = GetDocument()->GetSize().cy / 2;

   // ptOrg is in logical coordinates
   //   pDC->SetWindowOrg(-ptOrg.x, -ptOrg.y);
   pDC->SetWindowOrg(0, 0);
   pDC->SetWindowExt(XVIEWSIZE, YVIEWSIZE);
}

BOOL CLogiView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll)
{
   // do the scroll
   if (!CScrollView::OnScrollBy(sizeScroll, bDoScroll)) return FALSE;

   // update the position of any in-place active item
   if (bDoScroll)
   {
      UpdateActiveItem();
      UpdateWindow();
   }
   return TRUE;
}

void CLogiView::OnDraw(CDC* pDC)
{
   CLogiDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   CDC dc;
   CDC* pLogiDC = pDC;
   CBitmap bitmap;
   CBitmap* pOldBitmap = NULL;

   // only paint the rect that needs repainting
   CRect client;
   pDC->GetClipBox(client);

   int zoomx = GetDocument()->GetZoom(XVIEWSIZE);
   int zoomy = GetDocument()->GetZoom(YVIEWSIZE);

   // fudge rectangle to dance around DP/LP rounding errors
   // adjustment is proportional to zoom magnitude
   int ratx, raty;

   if (GetDocument()->GetZoom(XVIEWSIZE) > XVIEWSIZE)
   {
      ratx = zoomx/XVIEWSIZE;
      raty = zoomy/YVIEWSIZE;
   }
   else
   {
      if (zoomx != 0)
         ratx = XVIEWSIZE/zoomx;
      else
         ratx = 0;

      if (zoomy != 0)
         raty = YVIEWSIZE/zoomy;
      else
         raty = 0;
   }

   client.InflateRect(ratx, raty);

   if (client.left < 0)
      client.left = 0;
   if (client.top < 0)
      client.top = 0;

   CRect rect = client;
   DocToClient(rect);

   if (!pDC->IsPrinting())
   {
      // Draw to offscreen bitmap for fast looking repaints
      if (dc.CreateCompatibleDC(pDC))
      {
         if (bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
         {
            OnPrepareDC(&dc, NULL);
            pLogiDC = &dc;

            // offset origin more because bitmap is just piece of the whole Logiing
            dc.OffsetViewportOrg(-rect.left, -rect.top);
            pOldBitmap = dc.SelectObject(&bitmap);
            dc.SetBrushOrg(rect.left % 8, rect.top % 8);

            // might as well clip to the same rectangle
            dc.IntersectClipRect(client);
         }
      }
   }

   // paint background
   CBrush brush;
   if (!brush.CreateSolidBrush(pDoc->GetPaperColor())) return;

   brush.UnrealizeObject();
   pLogiDC->FillRect(client, &brush);

   if (pDoc->GetGridOn())
   {
      if (!(GetDocument()->m_bKeepGoing || GetDocument()->m_bPause))
      {
         DrawGrid(pLogiDC);
      }
   }

   pDoc->Draw(pLogiDC, this);

   if (pLogiDC != pDC)
   {
      pDC->SetViewportOrg(0, 0);
      pDC->SetWindowOrg(0,0);
      pDC->SetMapMode(MM_TEXT);

      dc.SetViewportOrg(0, 0);
      dc.SetWindowOrg(0,0);
      dc.SetMapMode(MM_TEXT);

      pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY);
      dc.SelectObject(pOldBitmap);
   }

   GetClientRect(&m_rLastDraw);
   ClientToDoc(m_rLastDraw);
}

void CLogiView::Remove(CLogiObj* pObj)
{
   POSITION pos = m_selection.Find(pObj);
   if (pos != NULL) m_selection.RemoveAt(pos);
}

void CLogiView::PasteNative(COleDataObject& dataObject)
{
   // get file refering to clipboard data
   CFile* pFile = dataObject.GetFileData(m_cfLogi);
   if (pFile == NULL) return;

   // connect the file to the archive
   CArchive ar(pFile, CArchive::load);
   TRY
   {
      ar.m_pDocument = GetDocument(); // set back-pointer in archive

      // read the selection

      m_selection.Serialize(ar);
   }
   CATCH_ALL(e)
   {
      ar.Close();
      delete pFile;
      THROW_LAST();
   }
   END_CATCH_ALL

      ar.Close();
   delete pFile;
}

void CLogiView::DrawGrid(CDC* pDC)
{
   CPen* pOldPen;
   CLogiDoc* pDoc = GetDocument();

   COLORREF oldBkColor = pDC->SetBkColor(pDoc->GetPaperColor());

   if (!pDC->IsPrinting())
   {
      pDC->SetWindowOrg(0,0);

      CRect rect;
      pDC->GetClipBox(&rect);
      rect.NormalizeRect();

      CPen penDot;
      penDot.CreatePen(PS_SOLID, 1, m_gridColor);
      pOldPen = pDC->SelectObject(&penDot);

      if (GetDocument()->GetZoom(pDoc->m_uGridWidth) <= 1 ||
         GetDocument()->GetZoom(pDoc->m_uGridHeight) <= 1)
      {
         // If user zooms out too far, it is ineffecient
         // to oversample the grid dots. So, just color
         // the entire rectangle for the same effect.

         CBrush brush(m_gridColor);
         pDC->FillRect(&rect, &brush);
      }
      else 
      {
         if (rect.left % pDoc->m_uGridWidth)
            rect.left += (pDoc->m_uGridWidth - (rect.left % pDoc->m_uGridWidth));

         if (rect.top % pDoc->m_uGridHeight)
            rect.top += (pDoc->m_uGridHeight - (rect.top % pDoc->m_uGridHeight));

         for (int x = rect.left; x <= rect.right; x += pDoc->m_uGridWidth)
         {
            for (int y = rect.top; y <= rect.bottom; y += pDoc->m_uGridHeight)
            {
               pDC->SetPixel(x, y, m_gridColor);
            }
         }

         // set the origin of the coordinate system to the center of the page
         //      CPoint ptOrg;
         //      ptOrg.x = GetDocument()->GetSize().cx / 2;
         //      ptOrg.y = GetDocument()->GetSize().cy / 2;

         // ptOrg is in logical coordinates
         //      pDC->SetWindowOrg(-ptOrg.x,-ptOrg.y);
         pDC->SetWindowOrg(0, 0);
      }

      pDC->SelectObject(pOldPen);
   }

   // Outlines

   CRect rect;
   //   rect.left = -pDoc->GetSize().cx / 2;
   //   rect.top = -pDoc->GetSize().cy / 2;
   rect.left   = 0;
   rect.top    = 0;
   rect.right  = rect.left + pDoc->GetSize().cx;
   rect.bottom = rect.top  + pDoc->GetSize().cy;

   pDC->MoveTo(rect.left,    rect.top);
   pDC->LineTo(rect.right-1, rect.top);
   pDC->LineTo(rect.right-1, rect.bottom-1);
   pDC->LineTo(rect.left,    rect.bottom-1);
   pDC->LineTo(rect.left,    rect.top);

   //   pDC->SelectObject(pOldPen);

   pDC->SetBkColor(oldBkColor);
}

void CLogiView::OnInitialUpdate()
{
   CSize size = GetDocument()->GetSize();
   SetScrollSizes(MM_TEXT, size);
   ResizeParentToFit(TRUE);
}

void CLogiView::SetPageSize(CSize size)
{
   SetScrollSizes(MM_TEXT, size);
   ResizeParentToFit(TRUE);
   GetDocument()->UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CLogiView printing

BOOL CLogiView::OnPreparePrinting(CPrintInfo* pInfo)
{

   pInfo->SetMaxPage(GetDocument()->GetMaxPage());

   return DoPreparePrinting(pInfo);
}

void CLogiView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
   CScrollView::OnBeginPrinting(pDC,pInfo);

   // check page size -- user could have gone into print setup
   // from print dialog and changed paper or orientation
   GetDocument()->ComputePageSize();
}

void CLogiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
   // TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CLogiView::IsSelected(const CObject* pDocItem) const
{
   CLogiObj* pLogiObj = (CLogiObj*)pDocItem;
   return m_selection.Find(pLogiObj) != NULL;
}


void CLogiView::OnSetFocus(CWnd* pOldWnd)
{
   CScrollView::OnSetFocus(pOldWnd);
}

CRect CLogiView::GetInitialPosition()
{
   CRect rect(10, 10, 10, 10);
   ClientToDoc(rect);
   return rect;
}

void CLogiView::ClientToDoc(CPoint& point)
{
   CClientDC dc(this);
   OnPrepareDC(&dc, NULL);
   dc.DPtoLP(&point);
}

void CLogiView::ClientToDoc(CRect& rect)
{
   CClientDC dc(this);
   OnPrepareDC(&dc, NULL);
   dc.DPtoLP(rect);
   ASSERT(rect.left <= rect.right);
   ASSERT(rect.bottom >= rect.top);
}

void CLogiView::DocToClient(CPoint& point)
{
   CClientDC dc(this);
   OnPrepareDC(&dc, NULL);
   dc.LPtoDP(&point);
}

void CLogiView::DocToClient(CRect& rect)
{
   CClientDC dc(this);
   OnPrepareDC(&dc, NULL);
   dc.LPtoDP(rect);
   rect.NormalizeRect();
}

void CLogiView::Select(CLogiObj* pObj, BOOL bAdd)
{
   if (!bAdd)
   {
      OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);
      m_selection.RemoveAll();
   }

   if (pObj == NULL || IsSelected(pObj)) return;

   m_selection.AddTail(pObj);
   InvalObj(pObj);
}

// rect is in device coordinates
void CLogiView::SelectWithinRect(CRect rect, int iPage, BOOL bAdd)
{
   if (!bAdd) Select(NULL);

   //   ClientToDoc(rect);

   CObList* pObList = GetDocument()->GetObjects();
   POSITION posObj = pObList->GetHeadPosition();
   while (posObj != NULL)
   {
      CLogiObj* pObj = (CLogiObj*)pObList->GetNext(posObj);
      if ((pObj->Intersects(rect)) && (pObj->m_iPage == iPage))
      {
         //         if (!pObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
         Select(pObj, TRUE);
      }
   }
}

void CLogiView::Deselect(CLogiObj* pObj)
{
   POSITION pos = m_selection.Find(pObj);
   if (pos != NULL)
   {
      InvalObj(pObj);
      m_selection.RemoveAt(pos);
   }
}

void CLogiView::CloneSelection()
{
   POSITION pos;
   CLogiObj* pObj;
   CLogiObj* pObjClone;

   m_selectionTemp.RemoveAll();

   // clone all but wires

   pos = m_selection.GetHeadPosition();
   while (pos != NULL)
   {
      pObj = (CLogiObj*)m_selection.GetNext(pos);

      // don't clone the wires (we'll make new ones)

      if (!pObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
      {
         // copies object and adds it to the document
         pObjClone = pObj->Clone(pObj->m_pDocument);
         m_selectionTemp.AddTail(pObjClone);
      }
   }

   // now rewire just the wire objects with NEW wires

   pos = m_selection.GetHeadPosition();
   while (pos != NULL)
   {
      pObj = (CLogiObj*)m_selection.GetNext(pos);

      if (pObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
      {
         // now create a new wire base on the original being cloned.
         // since the new devices are at the front they will get hit first.
         pObjClone = GetDocument()->ReWire(pObj->m_position, (CLogiWire*) NULL, m_iPage);
         if (pObjClone) m_selectionTemp.AddTail(pObjClone);
      }
   }

   // Make clones the new selection

   m_selection.RemoveAll();

   pos = m_selectionTemp.GetHeadPosition();
   while (pos != NULL)
   {
      pObj = (CLogiObj*)m_selectionTemp.GetNext(pos);
      m_selection.AddTail(pObj);
   }
}

void CLogiView::UpdateActiveItem()
{
}

/////////////////////////////////////////////////////////////////////////////
// CLogiView message handlers

void CLogiView::OnLButtonDown(UINT nFlags, CPoint point)
{

   if (!m_bActive) return;
   CLogiTool* pTool = CLogiTool::FindTool(CLogiTool::c_LogiShape);
   if (pTool != NULL) pTool->OnLButtonDown(this, nFlags, point);

   // if simultion not running it's ok to autoscroll, otherwise
   // down and up comes in immediate pair

   if (!GetDocument()->m_bKeepGoing) CAutoScrollView::OnLButtonDown(nFlags, point);
}

void CLogiView::OnLButtonUp(UINT nFlags, CPoint point)
{
   if (!m_bActive) return;
   CLogiTool* pTool = CLogiTool::FindTool(CLogiTool::c_LogiShape);
   if (pTool != NULL) pTool->OnLButtonUp(this, nFlags, point);
}

void CLogiView::OnAutoScroll(CPoint point, BOOL bBefore)
{
   if (!m_bActive) return;
   CLogiTool* pTool = CLogiTool::FindTool(CLogiTool::c_LogiShape);
   if (pTool != NULL) pTool->OnAutoScroll(this, point, bBefore);
}

void CLogiView::OnMouseMove(UINT nFlags, CPoint point)
{
   if (!m_bActive) return;
   CLogiTool* pTool = CLogiTool::FindTool(CLogiTool::c_LogiShape);
   if (pTool != NULL) pTool->OnMouseMove(this, nFlags, point);
}

void CLogiView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
   if (!m_bActive) return;
   CLogiTool* pTool = CLogiTool::FindTool(CLogiTool::c_LogiShape);
   if (pTool != NULL) pTool->OnLButtonDblClk(this, nFlags, point);
}

BOOL CLogiView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
   // Do not check for active view, cursor might be hovering.
   // if (!m_bActive) return FALSE;
   CLogiTool* pTool = CLogiTool::FindTool(CLogiTool::c_LogiShape);
   if (pTool != NULL)
      return pTool->OnSetCursor(this, pWnd, nHitTest, message);
   else
   {
      AfxGetApp()->LoadStandardCursor(IDC_ARROW);
      return TRUE;
   }
}

void CLogiView::OnRButtonDown(UINT nFlags, CPoint point)
{
   if (!m_bActive) return;

   // Don't interrupt an operation that has the mouse captured.
   // Such action causes an access violation delayed until window closes.
   if (GetCapture() != NULL) return;

   CLogiTool* pTool = CLogiTool::FindTool(CLogiTool::c_LogiShape);
   if (pTool != NULL) pTool->OnLButtonDown(this, nFlags, point);
   if (pTool != NULL) pTool->OnLButtonUp(this, nFlags, point);
   if (pTool != NULL) pTool->OnRButtonDown(this, nFlags, point);
}

void CLogiView::OnDrawSelector()
{

   OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);
   m_selection.RemoveAll();

   CLogiTool::c_LogiShape = selector;
}

void CLogiView::OnDrawANDGate()
{
   CLogiTool::c_LogiShape = andgate;
}

void CLogiView::OnDrawORGate()
{
   CLogiTool::c_LogiShape = orgate;
}

void CLogiView::OnDrawINVERTGate()
{
   CLogiTool::c_LogiShape = invertgate;
}

void CLogiView::OnDrawOscillatorGate()
{
   CLogiTool::c_LogiShape = oscillatorgate;
}

void CLogiView::OnDrawLedGate()
{
   CLogiTool::c_LogiShape = ledgate;
}

void CLogiView::OnDrawSwitchGate()
{
   CLogiTool::c_LogiShape = switchgate;
}

void CLogiView::OnDrawBuzzerGate()
{
   CLogiTool::c_LogiShape = buzzergate;
}

void CLogiView::OnDrawNULLGate()
{
   CLogiTool::c_LogiShape = nullgate;
}

void CLogiView::OnDrawLed7Gate()
{
   CLogiTool::c_LogiShape = led7gate;
}

void CLogiView::OnDrawWire()
{
   CLogiTool::c_LogiShape = wire;
   Select(NULL);
}

void CLogiView::OnUpdateDrawWire(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == wire);
}

void CLogiView::OnUpdateDrawANDGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == andgate);
}

void CLogiView::OnUpdateDrawORGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == orgate);
}

void CLogiView::OnUpdateDrawINVERTGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == invertgate);
}

void CLogiView::OnUpdateDrawOscillatorGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == oscillatorgate);
}

void CLogiView::OnUpdateDrawLedGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == ledgate);
}

void CLogiView::OnUpdateDrawSwitchGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == switchgate);
}

void CLogiView::OnUpdateDrawBuzzerGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == buzzergate);
}

void CLogiView::OnUpdateDrawNULLGate(CCmdUI* pCmdUI)
{
   //   pCmdUI->Enable(FALSE); return;

   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == nullgate);
}

void CLogiView::OnUpdateDrawLed7Gate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == led7gate);
}

void CLogiView::OnUpdateDrawSelector(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == selector);
}

void CLogiView::OnUpdateSingleSelect(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(m_selection.GetCount() == 1);
}

void CLogiView::OnEditSelectAll()
{
   //   m_selection.RemoveAll(); // Not needed since Select checks

   CLogiTool::c_LogiShape = selector;
   CObList* pObList = GetDocument()->GetObjects();
   POSITION pos = pObList->GetHeadPosition();
   while (pos != NULL)
   {
      CLogiObj* pObj = (CLogiObj*)pObList->GetNext(pos);
      if (pObj->m_iPage == m_iPage) Select(pObj, TRUE);
   }
}

void CLogiView::OnUpdateEditSelectAll(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(!GetDocument()->m_bKeepGoing &&
      !GetDocument()->m_bPause &&
      GetDocument()->GetObjects()->GetCount() != 0);
}

void CLogiView::OnEditClear()
{
   POSITION pos;

   // update all the views before the selection goes away
   GetDocument()->UpdateAllViews(NULL, HINT_DELETE_SELECTION, &m_selection);
   OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);

   // begin group of items to undo together
   GetDocument()->m_undo.BeginTransaction("Delete");

   // now remove the selection from the document (wires first)
   pos = m_selection.GetHeadPosition();
   while (pos != NULL)
   {
      CLogiWire* pObj = (CLogiWire*)m_selection.GetNext(pos);
      if (pObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
      {
         GetDocument()->Remove(pObj);
         // undo will delete object when ready
      }
   }

   // now remove the selection from the document (All else last)
   pos = m_selection.GetHeadPosition();
   while (pos != NULL)
   {
      CLogiGate* pObj = (CLogiGate*)m_selection.GetNext(pos);
      if (!pObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
      {
         GetDocument()->Remove(pObj);
         // undo will delete object when ready
      }
   }

   m_selection.RemoveAll();

   // end group of items to undo together
   GetDocument()->m_undo.EndTransaction("Delete");
}

void CLogiView::OnUpdateAnySelect(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(!m_selection.IsEmpty());
}

void CLogiView::OnSize(UINT nType, int cx, int cy)
{
   CScrollView::OnSize(nType, cx, cy);
   UpdateActiveItem();
}

BOOL CLogiView::OnEraseBkgnd(CDC* /*pDC*/)
{
   return TRUE;
}

void CLogiView::OnEditCopy()
{
   ASSERT_VALID(this);
   ASSERT(m_cfLogi != NULL);

   // Create a shared file and associate a CArchive with it
   CSharedFile file;
   CArchive ar(&file, CArchive::store);

   // Serialize selected objects to the archive
   m_selection.Serialize(ar);
   ar.Close();

   COleDataSource* pDataSource = NULL;

   TRY
   {
      pDataSource = new COleDataSource;
      // put on local format instead of or in addation to
      pDataSource->CacheGlobalData(m_cfLogi, file.Detach());

      pDataSource->SetClipboard();
   }
   CATCH_ALL(e)
   {
      delete pDataSource;
      THROW_LAST();
   }
   END_CATCH_ALL
}

void CLogiView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(!m_selection.IsEmpty());
}

void CLogiView::OnEditCut()
{
   GetDocument()->m_undo.BeginTransaction("Cut");
   OnEditCopy();
   OnEditClear();
   GetDocument()->m_undo.EndTransaction("Cut");
   // An interesting comment: If the user undos and then redos
   // a cut, and the user modifies the clipboard in the intervening time,
   // the cut data is not reposted to the clipboard. This is the
   // same behavior as Microsoft Word.
}

void CLogiView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(!m_selection.IsEmpty());
}

void CLogiView::OnEditPaste()
{
   POSITION pos;
   COleDataObject dataObject;
   BOOL bShiftPositions;
   RECT temp;

   dataObject.AttachClipboard();

   // invalidate current selection since it will be deselected
   OnUpdate(NULL, HINT_UPDATE_SELECTION, NULL);

   // If there is a current selection, shift
   // positions of objects so as to avoid
   // covering the previous selected items
   bShiftPositions = !m_selection.IsEmpty();
   m_selection.RemoveAll();

   if (dataObject.IsDataAvailable(m_cfLogi))
   {
      PasteNative(dataObject);

      // begin group of items to undo togeher
      GetDocument()->m_undo.BeginTransaction("Paste");

      // now add all items in m_selection to document
      pos = m_selection.GetHeadPosition();
      while (pos != NULL)
      {
         CLogiObj* pLogiObj;
         pLogiObj = (CLogiObj*)m_selection.GetNext(pos);
         pLogiObj->m_iPage = m_iPage;
         if (bShiftPositions)
         {
            temp = pLogiObj->m_position + CPoint(5,5);
            pLogiObj->MoveTo(temp, NULL);
         }
         GetDocument()->Add(pLogiObj);
      }

      // now rewire just the wire objects
      pos = m_selection.GetHeadPosition();
      while (pos != NULL)
      {
         CLogiObj* pLogiObj;
         pLogiObj = (CLogiObj*)m_selection.GetNext(pos);

         if (pLogiObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
         {
            if (GetDocument()->ReWire(pLogiObj->m_position, (CLogiWire*) pLogiObj, m_iPage) == NULL)
            {
               // if unable to re-wire, remove the wire
               // for example, if an endpoint gate missing from selection
               GetDocument()->Remove(pLogiObj);
            }
         }
      }

      // end group of items to undo together
      GetDocument()->m_undo.EndTransaction("Paste");
   }

   GetDocument()->SetModifiedFlag();

   // invalidate new pasted stuff
   GetDocument()->UpdateAllViews(NULL, HINT_UPDATE_SELECTION, &m_selection);

}

void CLogiView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
   // determine if private or standard OLE formats are on the clipboard
   COleDataObject dataObject;
   BOOL bEnable = dataObject.AttachClipboard() &&
      (dataObject.IsDataAvailable(m_cfLogi) /*||
                                            COleClientItem::CanCreateFromData(&dataObject)*/);

                                            // enable command based on availability
                                            pCmdUI->Enable(!GetDocument()->m_bKeepGoing &&
                                            !GetDocument()->m_bPause &&
                                            bEnable);
}

void CLogiView::OnUpdateEditFind(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(TRUE);
}


void CLogiView::OnUpdateEditReplace(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(!GetDocument()->m_bKeepGoing &&
      !GetDocument()->m_bPause);
}

void CLogiView::OnFilePrint()
{
   GetDocument()->CheckForStrays();

   CScrollView::OnFilePrint();
   GetDocument()->ComputePageSize();
}

void CLogiView::OnEditProperties()
{
   if ((m_selection.GetCount() == 1) && (CLogiTool::c_LogiShape == selector))
   {
      CLogiTool* pTool = CLogiTool::FindTool(CLogiTool::c_LogiShape);
      ASSERT(pTool != NULL);
      pTool->OnLButtonDblClk(this, 0, CPoint(0, 0));
   }
}

void CLogiView::OnUpdateEditProperties(CCmdUI* pCmdUI)
{
   pCmdUI->Enable((m_selection.GetCount() == 1) && (CLogiTool::c_LogiShape == selector));
}

/////////////////////////////////////////////////////////////////////////////
// CLogiView diagnostics

#ifdef _DEBUG
void CLogiView::AssertValid() const
{
   CScrollView::AssertValid();
}

void CLogiView::Dump(CDumpContext& dc) const
{
   CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////


void CLogiView::OnDrawAsciidisplayGate()
{
   CLogiTool::c_LogiShape = asciidisplaygate;
}

void CLogiView::OnUpdateDrawAsciidisplayGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == asciidisplaygate);
}

void CLogiView::OnDrawAsciikeyboardGate()
{
   CLogiTool::c_LogiShape = asciikeyboardgate;
}

void CLogiView::OnUpdateDrawAsciikeyboardGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == asciikeyboardgate);
}

void CLogiView::OnDrawGroundGate()
{
   CLogiTool::c_LogiShape = groundgate;
}

void CLogiView::OnUpdateDrawGroundGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == groundgate);
}

void CLogiView::OnDrawPlusGate()
{
   CLogiTool::c_LogiShape = plusgate;
}

void CLogiView::OnUpdateDrawPlusGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == plusgate);
}

void CLogiView::OnDrawPortinGate()
{
   CLogiTool::c_LogiShape = portingate;
}

void CLogiView::OnUpdateDrawPortinGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == portingate);
}

void CLogiView::OnDrawPortoutGate()
{
   CLogiTool::c_LogiShape = portoutgate;
}

void CLogiView::OnUpdateDrawPortoutGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == portoutgate);
}

void CLogiView::OnDrawReadfileGate()
{
   CLogiTool::c_LogiShape = readfilegate;
}

void CLogiView::OnUpdateDrawReadfileGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == readfilegate);
}

void CLogiView::OnDrawSignalreceiverGate()
{
   CLogiTool::c_LogiShape = signalreceivergate;
}

void CLogiView::OnUpdateDrawSignalreceiverGate(CCmdUI* pCmdUI)
{
   //   pCmdUI->Enable(FALSE); return;

   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == signalreceivergate);
}

void CLogiView::OnDrawSignalsenderGate()
{
   CLogiTool::c_LogiShape = signalsendergate;
}

void CLogiView::OnUpdateDrawSignalsenderGate(CCmdUI* pCmdUI)
{
   //   pCmdUI->Enable(FALSE); return;

   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == signalsendergate);
}

void CLogiView::OnDrawSoundwaveGate()
{
   CLogiTool::c_LogiShape = soundwavegate;
}

void CLogiView::OnUpdateDrawSoundwaveGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == soundwavegate);
}

void CLogiView::OnDrawTextGate()
{
   CLogiTool::c_LogiShape = textgate;
}

void CLogiView::OnUpdateDrawTextGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == textgate);
}

void CLogiView::OnDrawWritefileGate()
{
   CLogiTool::c_LogiShape = writefilegate;
}

void CLogiView::OnUpdateDrawWritefileGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == writefilegate);
}

void CLogiView::OnDrawFlipflopGate()
{
   CLogiTool::c_LogiShape = flipflopgate;
}

void CLogiView::OnUpdateDrawFlipflopGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == flipflopgate);
}

void CLogiView::OnDrawKeypadGate()
{
   CLogiTool::c_LogiShape = keypadgate;
}

void CLogiView::OnUpdateDrawKeypadGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == keypadgate);
}

void CLogiView::OnDrawBitmapGate()
{
   CLogiTool::c_LogiShape = bitmapgate;
}

void CLogiView::OnUpdateDrawBitmapGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == bitmapgate);
}

void CLogiView::OnDrawCounterGate()
{
   CLogiTool::c_LogiShape = countergate;
}

void CLogiView::OnUpdateDrawCounterGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == countergate);
}

void CLogiView::OnDrawBreakGate()
{
   CLogiTool::c_LogiShape = breakgate;
}

void CLogiView::OnUpdateDrawBreakGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == breakgate);
}

void CLogiView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   CView::OnChar(nChar, nRepCnt, nFlags);

   // If simulator is running and a keyboard exists then queue a down and up event
   if (((GetDocument()->m_bKeepGoing) || (GetDocument()->m_bPause)) && (GetDocument()->KeyBoardObj))
   {
      if (((CLogiAsciikeyboardGate*) GetDocument()->KeyBoardObj)->m_bAscii)
      {
         GetDocument()->KeyboardMessageQueue.AddTail(new AKeyboardMessage((CLogiGate*) GetDocument()->KeyBoardObj, this, TRUE, nChar));
         GetDocument()->KeyboardMessageQueue.AddTail(new AKeyboardMessage((CLogiGate*) GetDocument()->KeyBoardObj, this, FALSE, nChar));
      }
   }
}

void CLogiView::OnDrawMemoryGate()
{
   CLogiTool::c_LogiShape = memorygate;
}

void CLogiView::OnUpdateDrawMemoryGate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == memorygate);
}

void CLogiView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   CView::OnKeyDown(nChar, nRepCnt, nFlags);

   // If simulator is running and a keyboard exists the queue a down event

   if (((GetDocument()->m_bKeepGoing) || (GetDocument()->m_bPause)) && (GetDocument()->KeyBoardObj))
   {
      if (!((CLogiAsciikeyboardGate*) GetDocument()->KeyBoardObj)->m_bAscii)
      {
         GetDocument()->KeyboardMessageQueue.AddTail(new AKeyboardMessage((CLogiGate*) GetDocument()->KeyBoardObj, this, TRUE, nChar));
      }
   }
}

void CLogiView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   CView::OnKeyUp(nChar, nRepCnt, nFlags);

   // If simulator is running and a keyboard exists the queue an up event

   if (((GetDocument()->m_bKeepGoing) || (GetDocument()->m_bPause)) && (GetDocument()->KeyBoardObj))
   {
      if (!((CLogiAsciikeyboardGate*) GetDocument()->KeyBoardObj)->m_bAscii)
      {
         GetDocument()->KeyboardMessageQueue.AddTail(new AKeyboardMessage((CLogiGate*) GetDocument()->KeyBoardObj, this, FALSE, nChar));
      }
   }
}

void CLogiView::OnSetFont()
{
   LOGFONT lf;

   GetDocument()->m_cfScreen.GetLogFont(&lf);
   CFontDialog dlg(&lf, CF_SCREENFONTS|CF_INITTOLOGFONTSTRUCT);

   if (dlg.DoModal() == IDOK)
   {

      // switch to new font.

      GetDocument()->m_cfScreen.DeleteObject();
      if (GetDocument()->m_cfScreen.CreateFontIndirect(&lf))
      {

         // This should probably be a hint in update all views

         CLogiObj* CurrentObj;
         POSITION pos;

         for( pos = GetDocument()->m_objects.GetHeadPosition(); pos != NULL; )
         {
            CurrentObj = (CLogiObj*) GetDocument()->m_objects.GetNext( pos );
            if (CurrentObj->IsKindOf(RUNTIME_CLASS(CLogiTextGate)))
            {
               ((CLogiTextGate* ) CurrentObj)->ResizeRect();
            }
         }

         GetDocument()->UpdateAllViews(NULL);
         GetDocument()->SetModifiedFlag();
      }
   }
}


void CLogiView::OnDrawMux()
{
   CLogiTool::c_LogiShape = muxgate;
}

void CLogiView::OnUpdateDrawMux(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == muxgate);
}

void CLogiView::OnDrawBitbucket()
{
   CLogiTool::c_LogiShape = bitbucketgate;
}

void CLogiView::OnUpdateDrawBitbucket(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == bitbucketgate);
}

void CLogiView::OnDrawAlu()
{
   CLogiTool::c_LogiShape = alugate;
}

void CLogiView::OnUpdateDrawAlu(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == alugate);
}

void CLogiView::OnDrawRandom()
{
   CLogiTool::c_LogiShape = randomgate;
}

void CLogiView::OnUpdateDrawRandom(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == randomgate);
}

//void CLogiView::OnHelpTutorial()
//   {
//   ::HtmlHelp(NULL, "mmlogic.chm", HH_DISPLAY_TOPIC, (DWORD) "html\\tutorial.htm");
//   }

void CLogiView::OnDrawXor()
{
   CLogiTool::c_LogiShape = xorgate;
}

void CLogiView::OnUpdateDrawXor(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == xorgate);
}

void CLogiView::OnDrawClock()
{
   CLogiTool::c_LogiShape = clockgate;
}

void CLogiView::OnUpdateDrawClock(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == clockgate);
}

void CLogiView::OnDrawTimer()
{
   CLogiTool::c_LogiShape = timergate;
}

void CLogiView::OnUpdateDrawTimer(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == timergate);
}

void CLogiView::SetPage(int iPage)
{
   if (m_iPage != iPage)
   {
      m_iPage = iPage;
      Select(NULL);
      Invalidate(FALSE);
   }
}

void CLogiView::OnViewNextpage()
{
   SetPage(m_iPage+1);
}

void CLogiView::OnUpdateViewNextpage(CCmdUI* /*pCmdUI*/)
{
}

void CLogiView::OnUpdateIndicatorCycle(CCmdUI* /*pCmdUI*/)
{
   char StatusText[32];

   wsprintf(StatusText, "Cycle: %d", GetDocument()->m_uCycleCount);
   ((CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR))->SetPaneText(1, StatusText);
}

void CLogiView::OnUpdateIndicatorPage(CCmdUI* /*pCmdUI*/)
{
   char StatusText[32];

   wsprintf(StatusText, "Page: %d", m_iPage);
   ((CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR))->SetPaneText(2, StatusText);

   wsprintf(StatusText, "Cycle: %d", GetDocument()->m_uCycleCount);
   ((CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR))->SetPaneText(1, StatusText);
}

void CLogiView::OnViewPreviouspage()
{
   if (m_iPage > 1)
   {
      SetPage(m_iPage-1);
   }
}

void CLogiView::OnUpdateViewPreviouspage(CCmdUI* pCmdUI)
{
   if (m_iPage == 1) pCmdUI->Enable(FALSE);
}

void CLogiView::OnDrawRobot()
{
   CLogiTool::c_LogiShape = robotgate;
}

void CLogiView::OnUpdateDrawRobot(CCmdUI* pCmdUI)
{
   //   pCmdUI->Enable(FALSE);
   //   return;

   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == robotgate);
}

void CLogiView::OnDrawNetwork()
{
   CLogiTool::c_LogiShape = networkgate;
}

void CLogiView::OnUpdateDrawNetwork(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == networkgate);
}

void CLogiView::OnDrawSelectgate()
{
   CLogiTool::c_LogiShape = selectgate;
}

void CLogiView::OnUpdateDrawSelectgate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == selectgate);
}

void CLogiView::OnViewSnapSelectiontogrid()
{
   int iDeltax;
   int iDeltay;
   int iDeltax1;
   int iDeltay1;
   int iDeltax2;
   int iDeltay2;

   POSITION pos;

   CRect position;

   CPoint point;
   CPoint ptOrg;

   // Get center of document

   //   ptOrg.x = GetDocument()->GetSize().cx / 2;
   //   ptOrg.y = GetDocument()->GetSize().cy / 2;
   ptOrg.x = 0;
   ptOrg.y = 0;

   // assume nothing moved

   BOOL bMoved = FALSE;

   pos = m_selection.GetHeadPosition();

   if (pos == NULL)
   {
      ::MessageBox(::GetFocus(),"No devices are selected to Snap to grid", "Warning", MB_OK | MB_ICONEXCLAMATION);
      return;
   }

   // Start undo transaction
   GetDocument()->m_undo.BeginTransaction("Snap Selection");

   while (pos != NULL)
   {
      CLogiObj* pObj = (CLogiObj*)m_selection.GetNext(pos);
      if (!pObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
      {

         // Work in an easier coordinate system

         point = pObj->m_position.TopLeft() + ptOrg;

         // Why this can't be inline I don't know

         int iGridx = GetDocument()->m_uGridWidth;
         int iGridy = GetDocument()->m_uGridHeight;

         // Find nearest grid point in x

         iDeltax1 = (iGridx - (point.x % iGridx));
         iDeltax2 = - (point.x % iGridx);
         if (abs(iDeltax1) < abs(iDeltax2)) iDeltax = iDeltax1; else iDeltax = iDeltax2;

         // Find nearest grid point in y

         iDeltay1 = (iGridy - (point.y % iGridy));
         iDeltay2 = - (point.y % iGridy);
         if (abs(iDeltay1) < abs(iDeltay2)) iDeltay = iDeltay1; else iDeltay = iDeltay2;

         // If it needs adjustment then do it

         if (iDeltax || iDeltay)
         {

            // Determine new position for object

            position = pObj->m_position;
            position.OffsetRect(iDeltax, iDeltay);

            // Move (must use move to adjust wires)

            GetDocument()->Move(pObj, position, TRUE);

            bMoved = TRUE;
         }
      }
   }

   // End undo transaction
   GetDocument()->m_undo.EndTransaction("Snap Selection");

   // Why is this needed (also in devices off page code)

   if (bMoved)
   {
      GetDocument()->UpdateAllViews(NULL);
   }
}

void CLogiView::OnUpdateViewSnapSelectiontogrid(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(!GetDocument()->m_bKeepGoing &&
      !GetDocument()->m_bPause &&
      !m_selection.IsEmpty());
}

void CLogiView::OnDrawTristategate()
{
   CLogiTool::c_LogiShape = tristategate;
}

void CLogiView::OnUpdateDrawTristategate(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == tristategate);
}

void CLogiView::OnDrawBus()
{
   CLogiTool::c_LogiShape = busgate;
}

void CLogiView::OnUpdateDrawBus(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == busgate);
}

void CLogiView::OnDrawAnalyze()
{
   CLogiTool::c_LogiShape = analyzegate;
}

void CLogiView::OnUpdateDrawAnalyze(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == analyzegate);
}

void CLogiView::OnDrawTapedrive()
{
   CLogiTool::c_LogiShape = tapedrivegate;
}

void CLogiView::OnUpdateDrawTapedrive(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
   pCmdUI->SetRadio(CLogiTool::c_LogiShape == tapedrivegate);
}

void CLogiView::OnEditUndo()
{
   GetDocument()->m_undo.Undo(GetDocument());
}

void CLogiView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause)
   {
      pCmdUI->Enable(FALSE);
      return;
   }

   if (pCmdUI->m_pMenu != NULL)
      pCmdUI->m_pMenu->ModifyMenu(ID_EDIT_UNDO, MF_BYCOMMAND, ID_EDIT_UNDO,
      "Undo " + GetDocument()->m_undo.GetUndoDescription() + "\tCtrl-Z");

   if (!GetDocument()->m_undo.CanUndo()) pCmdUI->Enable(FALSE);
}

void CLogiView::OnEditRedo()
{
   GetDocument()->m_undo.Redo(GetDocument());
}

void CLogiView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause)
   {
      pCmdUI->Enable(FALSE);
      return;
   }

   if (pCmdUI->m_pMenu != NULL)
      pCmdUI->m_pMenu->ModifyMenu(ID_EDIT_REDO, MF_BYCOMMAND, ID_EDIT_REDO,
      "Redo " + GetDocument()->m_undo.GetRedoDescription() + "\tCtrl-Y");

   if (!GetDocument()->m_undo.CanRedo()) pCmdUI->Enable(FALSE);
}

void CLogiView::OnViewGotoPage()
{
   CGotoPageDlg dlg;
   CStringArray *pPageNames = GetDocument()->GetPageNames();

   dlg.m_iPageNumber = m_iPage;
   dlg.m_pPageNames = pPageNames;
   if (dlg.DoModal() == IDOK)
   {
      SetPage(dlg.m_iPageNumber);
      GetDocument()->SetModifiedFlag();
   }
}

void CLogiView::OnUpdateGotoPage(CCmdUI* /*pCmdUI*/)
{
}

LONG CLogiView::OnFindReplace(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
   BOOL bReplaceTransactionStarted = FALSE;

   if (m_frDialog->IsTerminating())
   {
      m_frDialog = NULL;
      m_frObjects.RemoveAll();
      AfxGetMainWnd()->EnableWindow(TRUE); // lose modality
      return TRUE;
   }

   // User wants to do replace. Allow if we have a current item.
   if ((m_frDialog->ReplaceCurrent() || m_frDialog->ReplaceAll()) && m_pLastMatch != NULL)
   {
      if (!bReplaceTransactionStarted)
      {
         GetDocument()->m_undo.BeginTransaction("Replace");
         bReplaceTransactionStarted = TRUE;
      }

      CString text = m_pLastMatch->GetText();
      text.Replace(m_frDialog->GetFindString(), m_frDialog->GetReplaceString());
      GetDocument()->Rename(m_pLastMatch, text);
      m_pLastMatch = NULL;
   }

   // Initial search, set position to start or end
   // of list depending on chosen direction.

   if (m_bfrInitSearch)
   {
      m_bfrInitSearch = FALSE;
      m_bfrDown = m_frDialog->SearchDown();
      if (m_bfrDown)
         m_frPos = m_frObjects.GetHeadPosition();
      else
         m_frPos = m_frObjects.GetTailPosition();
   }

   // Detect and handle change in direction.

   if (m_frDialog->SearchDown() != m_bfrDown)
      if (m_frDialog->SearchDown())
      {
         if (m_frPos == NULL)
            m_frPos = m_frObjects.GetHeadPosition();
         else
            m_frObjects.GetNext(m_frPos);

         if (m_frPos == NULL)
            m_frPos = m_frObjects.GetHeadPosition();

         if (m_frPos != NULL)
            m_frObjects.GetNext(m_frPos);

         if (m_frPos == NULL)
            m_frPos = m_frObjects.GetHeadPosition();

         m_bfrDown = TRUE;
      }  
      else
      {
         if (m_frPos == NULL)
            m_frPos = m_frObjects.GetTailPosition();
         else
            m_frObjects.GetPrev(m_frPos);

         if (m_frPos == NULL)
            m_frPos = m_frObjects.GetTailPosition();

         if (m_frPos != NULL)
            m_frObjects.GetPrev(m_frPos);

         if (m_frPos == NULL)
            m_frPos = m_frObjects.GetTailPosition();

         m_bfrDown = FALSE;
      }

      // Loop looking for a matching object.

      while (m_frPos != NULL)
      {
         CLogiObj *pObj;
         if (m_frDialog->SearchDown())
            pObj = (CLogiObj *) m_frObjects.GetNext(m_frPos);         
         else
            pObj = (CLogiObj *) m_frObjects.GetPrev(m_frPos);

         if (pObj->HasText())
         {
            CString text = pObj->GetText();
            if (text.Find(m_frDialog->GetFindString()) != -1)
            {
               if (m_frDialog->ReplaceAll())
               {
                  if (!bReplaceTransactionStarted)
                  {
                     GetDocument()->m_undo.BeginTransaction("Replace");
                     bReplaceTransactionStarted = TRUE;
                  }

                  text.Replace(m_frDialog->GetFindString(), m_frDialog->GetReplaceString());
                  GetDocument()->Rename(pObj, text);
               }
               else
               {
                  if (bReplaceTransactionStarted)
                     GetDocument()->m_undo.EndTransaction("Replace");

                  Select(NULL, FALSE); // select nothing
                  SetPage(pObj->m_iPage);
                  // Not permitted to make new highlight if simulator active
                  // But we have changed the page, which should help
                  // the user somewhat
                  if (!GetDocument()->m_bKeepGoing && !GetDocument()->m_bPause)
                     Select(pObj, TRUE); // select the current object
                  m_pLastMatch = pObj;
                  return TRUE;
               }
            }
         }
      }

      if (bReplaceTransactionStarted)
         GetDocument()->m_undo.EndTransaction("Replace");

      m_frDialog->MessageBox(CString(AfxGetAppName()) + " has finished searching the selected items.", NULL, MB_ICONINFORMATION | MB_OK);
      m_pLastMatch = NULL;

      // Wrap around search

      if (m_frDialog->SearchDown())
         m_frPos = m_frObjects.GetHeadPosition();     
      else
         m_frPos = m_frObjects.GetTailPosition();  

      return TRUE;
}

void CLogiView::OnEditFind()
{
   DisplayFindReplace(TRUE);
   return;
}

void CLogiView::OnEditReplace()
{
   DisplayFindReplace(FALSE);
   return;
}

void CLogiView::DisplayFindReplace(BOOL bFind)
{
   if (m_frDialog != NULL)
   {
      if (bFind == m_bfrFind)
         m_frDialog->SetFocus();
      else
         m_frDialog->DestroyWindow();
   }

   m_bfrFind = bFind;
   m_bfrDown = TRUE;
   m_bfrInitSearch = TRUE;

   m_frDialog = new CFindReplaceDialog();
   m_frDialog->Create(bFind, "", "", FR_DOWN | FR_HIDEMATCHCASE | FR_HIDEWHOLEWORD, this);

   if (!m_selection.IsEmpty())
      m_frObjects.AddTail(&m_selection);
   else
      m_frObjects.AddTail(GetDocument()->GetObjects());

   m_frPos = NULL;
   m_pLastMatch = NULL;

   // Make dialog modal
   AfxGetMainWnd()->EnableWindow(FALSE);
   m_frDialog->EnableWindow(TRUE);
}

// Removes an object from the list of objects
// eligable to be searched by find/replace.

void CLogiView::RemoveFromFindReplace(CLogiObj* pObj)
{
   POSITION pos = m_frObjects.Find(pObj);
   if (pos != NULL)
   {
      // If this would have been next object to find/replace, skip over it
      if (pos == m_frPos)
         if (m_bfrDown)
            m_frObjects.GetNext(m_frPos);
         else
            m_frObjects.GetPrev(m_frPos);

      // If this was the last match, clear m_pLastMatch
      if (pObj == m_pLastMatch)
         m_pLastMatch = NULL;

      m_frObjects.RemoveAt(pos);
   }
}

void CLogiView::OnDrawBisectwire()
{
   CLogiObj *pObj;
   POSITION pos;
   int StartIO;
   int EndIO;

   m_selectionTemp.RemoveAll();

   pos = m_selection.GetHeadPosition();
   while (pos != NULL)
   {
      pObj = (CLogiObj*)m_selection.GetNext(pos);

      if (pObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
      {
         CLogiGate *pNewNullGate;
         CLogiWire *pWire1;
         CLogiWire *pWire2;

         // Adapted from CLogiWire::Draw, find the bend in the wire
         CPoint ptFrom;
         CPoint ptTo;
         CPoint myPt;
         CPoint ptMidl;
         CRect rect = ((CLogiWire*)pObj)->m_position;
         ptFrom = rect.BottomRight();
         ptTo   = rect.TopLeft();

         //to draw wires in the right order we figure out which end the input is and make sure we start there
         StartIO = ((CLogiWire*)pObj)->StartIO,
            EndIO = ((CLogiWire*)pObj)->EndIO;
         CLogiGate* pStartGateObj = ((CLogiWire*)pObj)->pStartGateObj;
         CLogiGate* pEndGateObj = ((CLogiWire*)pObj)->pEndGateObj;
         StartIO = ((CLogiWire*)pObj)->StartIO;
         EndIO = ((CLogiWire*)pObj)->EndIO;

         if (ptFrom.x < ptTo.x)
         {
            if(ptFrom.y < ptTo.y)
               ptMidl.x = ptFrom.x + abs(rect.Width()) - (int) ((((float) ptFrom.y) / ((float) (GetDocument()->m_uCanvasHeight))) * (abs(rect.Width())));
            else
               ptMidl.x = ptFrom.x + (int) ((((float) ptFrom.y) / ((float) (GetDocument()->m_uCanvasHeight))) * (abs(rect.Width())));
         }
         else
         {
            if(ptFrom.y > ptTo.y)
               ptMidl.x = ptTo.x + abs(rect.Width()) - (int) ((((float) ptTo.y) / ((float) (GetDocument()->m_uCanvasHeight))) * (abs(rect.Width())));
            else
               ptMidl.x = ptTo.x + (int) ((((float) ptTo.y) / ((float) (GetDocument()->m_uCanvasHeight))) * (abs(rect.Width())));
         }
         ptMidl.y = rect.top + rect.Height()/2 + BITY_NUL/2;
         ptMidl.x -= BITX_NUL/2;

         // begin group of items to undo together
         GetDocument()->m_undo.BeginTransaction("Bisect");

         //create a new node at the bend in the wire
         pNewNullGate = new CLogiNULLGate(CRect(ptMidl, CSize(BITX_NUL,-BITY_NUL)), "NULL", m_iPage, GetDocument(), 0, 0);
         GetDocument()->Add(pNewNullGate);
         m_selectionTemp.AddTail(pNewNullGate);


         //remove the old wire
         GetDocument()->Remove(pObj);
         // undo will delete object when ready

         // if start is an input wire from from to to
         if(StartIO < pStartGateObj->Outputs)
         {
            pWire1 = GetDocument()->ReWire(CRect(pNewNullGate->m_position.CenterPoint(), ptFrom), (CLogiWire*) NULL, m_iPage);
            if(pWire1) m_selectionTemp.AddTail(pWire1);
            myPt = pNewNullGate->m_position.CenterPoint();
            myPt.x += 1;
            pWire2 = GetDocument()->ReWire(CRect(ptTo, myPt), (CLogiWire*) NULL, m_iPage);
            if(pWire2) m_selectionTemp.AddTail(pWire2);
         }
         // else wire from to to from
         else if(EndIO < pEndGateObj->Outputs)
         {
            pWire1 = GetDocument()->ReWire(CRect(pNewNullGate->m_position.CenterPoint(), ptTo), (CLogiWire*) NULL, m_iPage);
            if(pWire1) m_selectionTemp.AddTail(pWire1);
            myPt = pNewNullGate->m_position.CenterPoint();
            myPt.x += 1;
            pWire2 = GetDocument()->ReWire(CRect(ptFrom, myPt), (CLogiWire*) NULL, m_iPage);
            if(pWire2) m_selectionTemp.AddTail(pWire2);
         }
         else
         {
            //clearly, this should never happen
            ASSERT(FALSE);
         }
         // end group of items to undo together
         GetDocument()->m_undo.EndTransaction("Bisect");
      }
   }

   m_selection.RemoveAll();
   pos = m_selectionTemp.GetHeadPosition();
   while (pos != NULL)
   {
      pObj = (CLogiObj*)m_selectionTemp.GetNext(pos);
      m_selection.AddTail(pObj);
   }
   OnUpdate(NULL, HINT_UPDATE_WINDOW, NULL);
}

void CLogiView::OnUpdateDrawBisectwire(CCmdUI* pCmdUI)
{
   if (GetDocument()->m_bKeepGoing || GetDocument()->m_bPause) pCmdUI->Enable(FALSE);
}
