// Logitool.cpp - implementation for Drawing tools
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// CLogiTool implementation

CPtrList CLogiTool::c_tools;

// Add each tool to the pool of tools

static CSelectTool selectTool;
static CANDGateTool andgateTool;
static CXORGateTool xorgateTool;
static CORGateTool orgateTool;
static CINVERTGateTool invertgateTool;
static CTristateGateTool tristategateTool;
static CBusGateTool busgateTool;
static COscillatorGateTool oscillatorgateTool;
static CClockGateTool clockgateTool;
static CTimerGateTool timergateTool;
static CLedGateTool ledgateTool;
static CSwitchGateTool switchgateTool;
static CSelectGateTool selectgateTool;
static CBuzzerGateTool buzzergateTool;
static CNULLGateTool nullgateTool;
static CLed7GateTool led7gateTool;
static CAsciidisplayGateTool asciidisplaygateTool;
static CAsciikeyboardGateTool asciikeyboardgateTool;
static CGroundGateTool groundgateTool;
static CPlusGateTool plusgateTool;
static CPortinGateTool portingateTool;
static CPortoutGateTool portoutgateTool;
static CReadfileGateTool readfilegateTool;
static CSignalreceiverGateTool signalreceivergateTool;
static CSignalsenderGateTool signalsendergateTool;
static CAnalyzeGateTool analyzegateTool;
static CSoundwaveGateTool soundwavegateTool;
static CWritefileGateTool writefilegateTool;
static CFlipflopGateTool flipflopgateTool;
static CKeypadGateTool keypadgateTool;
static CBitmapGateTool bitmapgateTool;
static CCounterGateTool countergateTool;
static CRandomGateTool randomgateTool;
static CBreakGateTool breakgateTool;
static CBitbucketGateTool bitbucketgateTool;
static CNetworkGateTool networkgateTool;
static CRobotGateTool robotgateTool;
static CMemoryGateTool memorygateTool;
static CTapedriveGateTool tapedrivegateTool;
static CMuxGateTool muxgateTool;
static CAluGateTool alugateTool;
static CWireTool wireTool;
static CTextTool textTool;

CPoint CLogiTool::c_down;
UINT CLogiTool::c_nDownFlags;
CPoint CLogiTool::c_last;
LogiShape CLogiTool::c_LogiShape = selector;

CLogiTool::CLogiTool(LogiShape LogiShape)
{
   m_LogiShape = LogiShape;
   c_tools.AddTail(this);
}

void CLogiTool::OnAutoScroll(CLogiView* /*pView*/, const CPoint& /*point*/, BOOL /*bBefore*/)
{
}

CLogiTool* CLogiTool::FindTool(LogiShape LogiShape)
{
   POSITION pos = c_tools.GetHeadPosition();
   while (pos != NULL)
   {
      CLogiTool* pTool = (CLogiTool*)c_tools.GetNext(pos);
      if (pTool->m_LogiShape == LogiShape) return pTool;
   }

   return NULL;
}

void CLogiTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   pView->SetCapture();
   c_nDownFlags = nFlags;
   c_down = point;
   pView->ClientToDoc(c_down);
   c_last = c_down;
}

void CLogiTool::OnLButtonDblClk(CLogiView * /*pView*/, UINT, const CPoint& /*point*/)
{
}

void CLogiTool::OnLButtonUp(CLogiView* pView, UINT, const CPoint& point)
{
   ReleaseCapture();

   CPoint c_downt = c_down;
   pView->DocToClient(c_downt);
   if (point == c_downt) c_LogiShape = selector;
}

void CLogiTool::OnRButtonDown(CLogiView * /*pView*/, UINT, const CPoint& /*point*/)
{
}

void CLogiTool::OnMouseMove(CLogiView* pView, UINT /*nFlags*/, const CPoint& point)
{
   c_last = point;
   pView->ClientToDoc(c_last);
}

BOOL CLogiTool::OnSetCursor(CLogiView* /*pView*/, CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/)
{
   SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
   return TRUE;
}

void CLogiTool::OnCancel()
{
   c_LogiShape = selector;
}

////////////////////////////////////////////////////////////////////////////
// CResizeTool

enum SelectMode
{
   none,
   netSelect,
   move,
   size
}
;

SelectMode selectMode = none;
int nDragHandle;

CPoint lastPoint;

CSelectTool::CSelectTool() : CLogiTool(selector)
{
   m_bUserMove = FALSE;
}

void CSelectTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   ASSERT(m_prevPositions.IsEmpty());

   int io = -1;
   CPoint local = point;
   pView->ClientToDoc(local);

   CLogiObj* pObj;
   selectMode = none;
   CLogiGate* pGateObj;

   // If simulation is running then perform action
   if ((pView->GetDocument()->m_bKeepGoing) || (pView->GetDocument()->m_bPause))
   {
      pGateObj = (CLogiGate*)pView->GetDocument()->ObjectAt(local, pView->m_iPage);

      // If probe is enabled then check if we are on a gate
      if (pView->GetDocument()->m_uProbe != 0)
      {

         // If we hit a gate check if we hit a node
         if (pGateObj != NULL)
         {
            CLogiGate* pGateObj = (CLogiGate*) pView->GetDocument()->ObjectAtContact(local, &io, pView->m_iPage);
            if ((pGateObj) && (pGateObj->Node[io] != pView->GetDocument()->m_pAnodeNULL))
            {
               pView->GetDocument()->pAnodeProbe = pGateObj->Node[io];
               pView->GetDocument()->UpdateProbe();
            }
         }
      }
      else
      {

         if (pGateObj != NULL)
         {
            if (pGateObj->IsKindOf(RUNTIME_CLASS(CLogiGate)))
            {
               CPoint local2 = local;
               local2 -= pGateObj->m_position.TopLeft();
               // Queue the Mouse Message
               pView->GetDocument()->MouseMessageQueue.AddTail(new AMouseMessage(pGateObj, pView, TRUE, local2));
            }
         }
      }

      m_cpDownPoint = local;
      pView->SetCapture();

      return;
   }

   // See if the click was on an object, select and start move if so
   if (selectMode == none)
   {
      pObj = pView->GetDocument()->ObjectAt(local, pView->m_iPage);

      if (pObj != NULL)
      {

         CLogiGate* pGateObj = (CLogiGate*)pView->GetDocument()->ObjectAtContact(local, &io, pView->m_iPage);
         if ((pGateObj) && (pGateObj->Node[io]))
         {
            CLogiWire* CurrentWire;
            POSITION pos;

            selectMode = move;
            m_bUserMove = TRUE; // positions to be saved for undo/redo

            // select all connected wires
            if ((nFlags & MK_SHIFT) == 0) pView->Select(NULL);
            for( pos = pGateObj->Wire[io].GetHeadPosition(); pos != NULL; )
            {
               CurrentWire = (CLogiWire*) pGateObj->Wire[io].GetNext( pos );
               pView->Select(CurrentWire, TRUE);
            }
         }
         else
         {
            selectMode = move;
            m_bUserMove = TRUE; // positions to be saved for undo/redo

            if (!pView->IsSelected(pObj))
            {
               pView->Select(pObj, (nFlags & MK_SHIFT) != 0);
            }
            else
            {
               if ((nFlags & MK_SHIFT) != 0)
               {
                  pView->Deselect(pObj);
               }
            }

            // Ctrl+Click clones the selection...
            if ((nFlags & MK_CONTROL) != 0) pView->CloneSelection();
         }
      }
   }

   // Click on background, start a net-selection
   if (selectMode == none)
   {
      if ((nFlags & MK_SHIFT) == 0) pView->Select(NULL);

      selectMode = netSelect;

      CClientDC dc(pView);
      CRect rect(point.x, point.y, point.x, point.y);
      rect.NormalizeRect();

      // do DP->LP->DP conversion to avoid rounding error
      pView->ClientToDoc(rect);
      pView->DocToClient(rect);

      dc.DrawFocusRect(rect);
   }

   lastPoint = local;
   CLogiTool::OnLButtonDown(pView, nFlags, point);
}

void CSelectTool::OnLButtonDblClk(CLogiView* pView, UINT nFlags, const CPoint& point)
{

   CPoint local = point;
   pView->ClientToDoc(local);

   CLogiGate* pGateObj;

   // If simulation is running then perform action

   if ((pView->GetDocument()->m_bKeepGoing) || (pView->GetDocument()->m_bPause))
   {
      pGateObj = (CLogiGate*)pView->GetDocument()->ObjectAt(m_cpDownPoint, pView->m_iPage);

      if (pGateObj != NULL)
      {
         if (pGateObj->IsKindOf(RUNTIME_CLASS(CLogiGate)))
         {
            CPoint local2 = local;
            local2 -= pGateObj->m_position.TopLeft();
            // We still seem to get a single down and up so just add one more pair
            pView->GetDocument()->MouseMessageQueue.AddTail(new AMouseMessage(pGateObj, pView, FALSE, local2));
            pView->GetDocument()->MouseMessageQueue.AddTail(new AMouseMessage(pGateObj, pView, TRUE, local2));
         }
      }
      return;
   }

   // "Normal" DblClk opens properties
   if (pView->m_selection.GetCount() == 1) ((CLogiObj*)pView->m_selection.GetHead())->OnOpen(pView);

   CLogiTool::OnLButtonDblClk(pView, nFlags, point);
}

void CSelectTool::OnLButtonUp(CLogiView* pView, UINT nFlags, const CPoint& point)
{

   POSITION pos;

   // Save any stored positions of objects moved for undo/redo

   if (!m_prevPositions.IsEmpty())
   {
      pView->GetDocument()->m_undo.BeginTransaction("Move");
      for (pos = m_prevPositions.GetHeadPosition(); pos != NULL; )
      {
         CPreviousPosition *pPrev = (CPreviousPosition *) m_prevPositions.GetNext(pos);
         pView->GetDocument()->m_undo.PushMove(pPrev->m_pLogiObj, pPrev->m_rect);
         delete pPrev;
      }
      pView->GetDocument()->m_undo.EndTransaction("Move");
      m_prevPositions.RemoveAll();
   }

   m_bUserMove = FALSE; // no longer moving

   CPoint local = point;
   pView->ClientToDoc(local);

   CLogiGate* pGateObj;

   // If simulation is running then perform action
   if ((pView->GetDocument()->m_bKeepGoing) || (pView->GetDocument()->m_bPause))
   {
      if (pView->GetDocument()->m_uProbe != 0)
      {
         pView->GetDocument()->m_uProbe = IDC_PROBE_NULL;
         SetCursor(AfxGetApp()->LoadCursor(pView->GetDocument()->m_uProbe));
      }
      else
      {

         pGateObj = (CLogiGate*)pView->GetDocument()->ObjectAt(m_cpDownPoint, pView->m_iPage);

         if (pGateObj != NULL)
         {
            if (pGateObj->IsKindOf(RUNTIME_CLASS(CLogiGate)))
            {
               CPoint local2 = m_cpDownPoint;
               local2 -= pGateObj->m_position.TopLeft();
               // Queue the Mouse Message
               pView->GetDocument()->MouseMessageQueue.AddTail(new AMouseMessage(pGateObj, pView, FALSE, local2));
            }
         }
      }

      ReleaseCapture();
      return;
   }

   if (pView->GetCapture() == pView)
   {
      if (selectMode == netSelect)
      {
         CClientDC dc(pView);
         CPoint c_lastt = c_last;
         CPoint c_downt = c_down;
         pView->DocToClient(c_lastt);
         pView->DocToClient(c_downt);
         CRect rect(c_downt.x, c_downt.y, c_lastt.x, c_lastt.y);
         rect.NormalizeRect();
         dc.DrawFocusRect(rect);

         CRect rect2(c_down.x, c_down.y, c_last.x, c_last.y);
         rect2.NormalizeRect();
         pView->SelectWithinRect(rect2, pView->m_iPage, TRUE);
      }
      else if (selectMode != none)
      {
         pView->GetDocument()->UpdateAllViews(pView);
      }
   }

   OnMouseMove(pView, nFlags, point);
   CLogiTool::OnLButtonUp(pView, nFlags, point);
}

void CSelectTool::OnRButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CMenu menu;
   RECT ViewRect;

   if (!pView->GetDocument()->m_bKeepGoing && !pView->GetDocument()->m_bPause)
   {

      VERIFY(menu.LoadMenu(IDR_OBJECT_POPUP));
      CMenu* pPopup = menu.GetSubMenu(0);
      ASSERT(pPopup != NULL);

      pView->GetWindowRect(&ViewRect);

      // Use AfxGetMainWnd(), not pView, so that OnUpdate is called to
      // enable/disable the menu items as needed.
      pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ViewRect.left+point.x, ViewRect.top+point.y, AfxGetMainWnd());

      CLogiTool::OnRButtonDown(pView, nFlags, point);
   }
}

void CSelectTool::OnMouseMove(CLogiView* pView, UINT nFlags, const CPoint& point)
{

   if (pView->GetDocument()->m_uProbe != 0)
   {
      SetCursor(AfxGetApp()->LoadCursor(pView->GetDocument()->m_uProbe));
      return;
   }

   if (pView->GetCapture() != pView)
   {
      if (c_LogiShape == selector) CLogiTool::OnMouseMove(pView, nFlags, point);
      return;
   }

   if (selectMode == netSelect)
   {
      if (!pView->IsAutoScrolling())
      {
         CClientDC dc(pView);
         CPoint c_lastt = c_last;
         CPoint c_downt = c_down;
         pView->DocToClient(c_lastt);
         pView->DocToClient(c_downt);
         CRect rect(c_downt.x, c_downt.y, c_lastt.x, c_lastt.y);
         rect.NormalizeRect();
         dc.DrawFocusRect(rect);

         // do DP->LP->DP conversion to avoid rounding error
         CPoint pt = point;
         pView->ClientToDoc(pt);
         pView->DocToClient(pt);

         rect.SetRect(c_downt.x, c_downt.y, pt.x, pt.y);
         rect.NormalizeRect();
         dc.DrawFocusRect(rect);

         CLogiTool::OnMouseMove(pView, nFlags, point);
      }
      return;
   }

   CPoint local = point;
   pView->ClientToDoc(local);

   // Offset position if snap to grid mode is on

   BOOL bSnapToGrid = pView->GetDocument()->GetSnapToGrid();
   // If drawing single wire, do not snap it
   if (selectMode == move || selectMode == size)
      if (pView->m_selection.GetCount() == 1)
         if (((CLogiObj *) pView->m_selection.GetHead())->m_Logishape == wire)
            bSnapToGrid = FALSE;
   CPoint grid = pView->GetDocument()->GetGridSizes();
   if (bSnapToGrid)
      local -= CPoint(local.x % grid.x - c_down.x % grid.x,
      local.y % grid.y - c_down.y % grid.y);

   CPoint delta = (CPoint)(local - lastPoint);

   // If not internal move and first call to move since mouse button
   // down, then store positions of objects before move for undo/redo.
   BOOL bSavePositions = m_bUserMove && m_prevPositions.IsEmpty();

   if (selectMode == move)
   {
      POSITION pos = pView->m_selection.GetHeadPosition();
      while (pos != NULL)
      {
         CLogiObj* pObj = (CLogiObj*)pView->m_selection.GetNext(pos);

         if (pObj->m_Logishape != wire)
         {
            CRect position = pObj->m_position;

            if (bSavePositions)
               m_prevPositions.AddTail(new CPreviousPosition(pObj, position));

            // Before moving, ensure that the item is aligned
            // with the grid if Snap to Grid mode is in use
            if (bSnapToGrid)
               position -= CPoint(position.left % grid.x, position.top % grid.y);

            position += delta;

            pObj->MoveTo(position, pView);
         }
      }
   }

   else if (nDragHandle != 0)
   {
      POSITION pos = pView->m_selection.GetHeadPosition();
      while (pos != NULL)
      {
         CLogiObj* pObj = (CLogiObj*)pView->m_selection.GetNext(pos);

         pObj->MoveHandleTo(nDragHandle, local, pView);
      }
   }

   lastPoint = local;

   c_last = point;
   pView->ClientToDoc(c_last);

   if (c_LogiShape == selector) CLogiTool::OnMouseMove(pView, nFlags, point);
}

BOOL CSelectTool::OnSetCursor(CLogiView* pView, CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/)
{
   if (pView->GetDocument()->m_uProbe != 0)
      SetCursor(AfxGetApp()->LoadCursor(pView->GetDocument()->m_uProbe));
   else
      SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
   return TRUE;
}

void CSelectTool::OnAutoScroll(CLogiView* pView, const CPoint& point, BOOL bBefore)
{
   if (selectMode == netSelect)
   {
      CClientDC dc(pView);
      CPoint c_lastt = c_last;
      CPoint c_downt = c_down;
      pView->DocToClient(c_lastt);
      pView->DocToClient(c_downt);

      if (bBefore)
      {
         CRect rect(c_downt.x, c_downt.y, c_lastt.x, c_lastt.y);
         rect.NormalizeRect();
         dc.DrawFocusRect(rect);
      }
      else
      {
         // do DP->LP->DP conversion to avoid rounding error conversion to avoid rounding error
         CPoint pt = point;
         pView->ClientToDoc(pt);
         pView->DocToClient(pt);

         CRect rect(c_downt.x, c_downt.y, pt.x, pt.y);
         rect.NormalizeRect();
         dc.DrawFocusRect(rect);
         c_last = point;
         pView->ClientToDoc(c_last);
      }
   }

   return;
}

////////////////////////////////////////////////////////////////////////////
// CGateTool

CGateTool::CGateTool(LogiShape nLogiShape) : CLogiTool(nLogiShape)
{
}

void CGateTool::OnLButtonDblClk(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CLogiTool::OnLButtonDblClk(pView, nFlags, point);
}

void CGateTool::OnLButtonUp(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint c_downt = c_down;
   pView->DocToClient(c_downt);
   if ((point == c_downt) && 0)
   {
      // Don't create empty objects...
      CLogiObj *pObj = (CLogiObj*)pView->m_selection.GetTail();
      pView->GetDocument()->Remove(pObj, FALSE);
      delete pObj;
      selectTool.OnLButtonDown(pView, nFlags, point); // try a select!
   }

   // When dropping a new gate unselect
   pView->Select(NULL);

   selectTool.OnLButtonUp(pView, nFlags, point);
}

void CGateTool::OnRButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CLogiTool::OnRButtonDown(pView, nFlags, point);
}

void CGateTool::OnMouseMove(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
   selectTool.OnMouseMove(pView, nFlags, point);
}

BOOL CGateTool::OnSetCursor(CLogiView* /*pView*/, CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/)
{
   SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
   return TRUE;
}

////////////////////////////////////////////////////////////////////////////
// CANDGateTool

CANDGateTool::CANDGateTool() : CGateTool(andgate)
{
}

void CANDGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiANDGate(CRect(local, CSize(BITX,-BITY)), "AND", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CXORGateTool

CXORGateTool::CXORGateTool() : CGateTool(xorgate)
{
}

void CXORGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiXORGate(CRect(local, CSize(BITX,-BITY)), "XOR", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CORGateTool

CORGateTool::CORGateTool() : CGateTool(orgate)
{
}

void CORGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiORGate(CRect(local, CSize(BITX,-BITY)), "OR", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CINVERTGateTool

CINVERTGateTool::CINVERTGateTool() : CGateTool(invertgate)
{
}

void CINVERTGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiINVERTGate(CRect(local, CSize(BITX,-BITY)), "INVERT", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CTristateGateTool

CTristateGateTool::CTristateGateTool() : CGateTool(tristategate)
{
}

void CTristateGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiTristateGate(CRect(local, CSize(BITX,-BITY)), "TRISTATE", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CBusGateTool

CBusGateTool::CBusGateTool() : CGateTool(busgate)
{
}

void CBusGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiBusGate(CRect(local, CSize(BITX,-BITY)), "BUS", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// COscillatorGateTool

COscillatorGateTool::COscillatorGateTool() : CGateTool(oscillatorgate)
{
}

void COscillatorGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiOscillatorGate(CRect(local, CSize(BITX,-BITY)), "OSCILLATOR", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CClockGateTool

CClockGateTool::CClockGateTool() : CGateTool(clockgate)
{
}

void CClockGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiClockGate(CRect(local, CSize(BITX,-BITY)), "CLOCK", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CTimerGateTool

CTimerGateTool::CTimerGateTool() : CGateTool(timergate)
{
}

void CTimerGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiTimerGate(CRect(local, CSize(BITX,-BITY)), "TIMER", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CLedGateTool

CLedGateTool::CLedGateTool() : CGateTool(ledgate)
{
}

void CLedGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiLedGate(CRect(local, CSize(BITX,-BITY)), "LED", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CSwitchGateTool

CSwitchGateTool::CSwitchGateTool() : CGateTool(switchgate)
{
}

void CSwitchGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiSwitchGate(CRect(local, CSize(BITX,-BITY)), "SWITCH", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CSelectGateTool

CSelectGateTool::CSelectGateTool() : CGateTool(selectgate)
{
}

void CSelectGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiSelectGate(CRect(local, CSize(BITX,-BITY)), "SELECT", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CBuzzerGateTool

CBuzzerGateTool::CBuzzerGateTool() : CGateTool(buzzergate)
{
}

void CBuzzerGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiBuzzerGate(CRect(local, CSize(BITX,-BITY)), "BUZZER", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CNULLGateTool

CNULLGateTool::CNULLGateTool() : CGateTool(nullgate)
{
}

void CNULLGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_NUL;
   oldpoint.y -= BITY_NUL;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiNULLGate(CRect(local, CSize(BITX_NUL,-BITY_NUL)), "NULL", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CLed7GateTool

CLed7GateTool::CLed7GateTool() : CGateTool(led7gate)
{
}

void CLed7GateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_LED;
   oldpoint.y -= BITY_LED;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiLed7Gate(CRect(local, CSize(BITX_LED,-BITY_LED)), "LED7", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CAsciidisplayGateTool

CAsciidisplayGateTool::CAsciidisplayGateTool() : CGateTool(asciidisplaygate)
{
}

void CAsciidisplayGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_DSP;
   oldpoint.y -= BITY_DSP;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiAsciidisplayGate(CRect(local, CSize(BITX_DSP,-BITY_DSP)), "DISPLAY", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CAsciikeyboardGateTool

CAsciikeyboardGateTool::CAsciikeyboardGateTool() : CGateTool(asciikeyboardgate)
{
}

void CAsciikeyboardGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_KB;
   oldpoint.y -= BITY_KB;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiAsciikeyboardGate(CRect(local, CSize(BITX_KB,-BITY_KB)), "KEYBOARD", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CGroundGateTool

CGroundGateTool::CGroundGateTool() : CGateTool(groundgate)
{
}

void CGroundGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiGroundGate(CRect(local, CSize(BITX,-BITY)), "GROUND", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CPlusGateTool

CPlusGateTool::CPlusGateTool() : CGateTool(plusgate)
{
}

void CPlusGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiPlusGate(CRect(local, CSize(BITX,-BITY)), "PLUS", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CPortinGateTool

CPortinGateTool::CPortinGateTool() : CGateTool(portingate)
{
}

void CPortinGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_KB;
   oldpoint.y -= BITY_KB;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiPortinGate(CRect(local, CSize(BITX_KB,-BITY_KB)), "PORTIN", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CPortoutGateTool

CPortoutGateTool::CPortoutGateTool() : CGateTool(portoutgate)
{
}

void CPortoutGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_KB;
   oldpoint.y -= BITY_KB;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiPortoutGate(CRect(local, CSize(BITX_KB,-BITY_KB)), "PORTOUT", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CReadfileGateTool

CReadfileGateTool::CReadfileGateTool() : CGateTool(readfilegate)
{
}

void CReadfileGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_KB;
   oldpoint.y -= BITY_KB;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiReadfileGate(CRect(local, CSize(BITX_KB,-BITY_KB)), "READFILE", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CSignalreceiverGateTool

CSignalreceiverGateTool::CSignalreceiverGateTool() : CGateTool(signalreceivergate)
{
}

void CSignalreceiverGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_SIG;
   oldpoint.y -= BITY_SIG;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiSignalreceiverGate(CRect(local, CSize(BITX_SIG,-BITY_SIG)), "SIGNALRX", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CSignalsenderGateTool

CSignalsenderGateTool::CSignalsenderGateTool() : CGateTool(signalsendergate)
{
}

void CSignalsenderGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_SIG;
   oldpoint.y -= BITY_SIG;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiSignalsenderGate(CRect(local, CSize(BITX_SIG,-BITY_SIG)), "SIGNALTX", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CAnalyzeGateTool

CAnalyzeGateTool::CAnalyzeGateTool() : CGateTool(analyzegate)
{
}

void CAnalyzeGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_SIG;
   oldpoint.y -= BITY_SIG;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiAnalyzeGate(CRect(local, CSize(BITX_SIG,-BITY_SIG)), "ANALYZE", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CSoundwaveGateTool

CSoundwaveGateTool::CSoundwaveGateTool() : CGateTool(soundwavegate)
{
}

void CSoundwaveGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiSoundwaveGate(CRect(local, CSize(BITX,-BITY)), "SOUNDWAVE", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CWritefileGateTool

CWritefileGateTool::CWritefileGateTool() : CGateTool(writefilegate)
{
}

void CWritefileGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_KB;
   oldpoint.y -= BITY_KB;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiWritefileGate(CRect(local, CSize(BITX_KB,-BITY_KB)), "WRITEFILE", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CFlipflopGateTool

CFlipflopGateTool::CFlipflopGateTool() : CGateTool(flipflopgate)
{
}

void CFlipflopGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiFlipflopGate(CRect(local, CSize(BITX,-BITY)), "FLIPFLOP", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CKeypadGateTool

CKeypadGateTool::CKeypadGateTool() : CGateTool(keypadgate)
{
}

void CKeypadGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_KP;
   oldpoint.y -= BITY_KP;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiKeypadGate(CRect(local, CSize(BITX_KP,-BITY_KP)), "KEYPAD", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CBitmapGateTool

CBitmapGateTool::CBitmapGateTool() : CGateTool(bitmapgate)
{
}

void CBitmapGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiBitmapGate(CRect(local, CSize(BITX,-BITY)), "BITMAP", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   ((CLogiBitmapGate *) pObj)->ResizeRect();

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CCounterGateTool

CCounterGateTool::CCounterGateTool() : CGateTool(countergate)
{
}

void CCounterGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_CNT;
   oldpoint.y -= BITY_CNT;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiCounterGate(CRect(local, CSize(BITX_CNT,-BITY_CNT)), "COUNTER", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CRandomGateTool

CRandomGateTool::CRandomGateTool() : CGateTool(randomgate)
{
}

void CRandomGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiRandomGate(CRect(local, CSize(BITX,-BITY)), "RANDOM", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CBreakGateTool

CBreakGateTool::CBreakGateTool() : CGateTool(breakgate)
{
}

void CBreakGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiBreakGate(CRect(local, CSize(BITX,-BITY)), "BREAK", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CBitbucketGateTool

CBitbucketGateTool::CBitbucketGateTool() : CGateTool(bitbucketgate)
{
}

void CBitbucketGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiBitbucketGate(CRect(local, CSize(BITX,-BITY)), "BITBUCKET", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CNetworkGateTool

CNetworkGateTool::CNetworkGateTool() : CGateTool(networkgate)
{
}

void CNetworkGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_KB;
   oldpoint.y -= BITY_KB;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiNetworkGate(CRect(local, CSize(BITX_KB,-BITY_KB)), "NETWORK", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CRobotGateTool

CRobotGateTool::CRobotGateTool() : CGateTool(robotgate)
{
}

void CRobotGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_RBT;
   oldpoint.y -= BITY_RBT;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiRobotGate(CRect(local, CSize(BITX_RBT,-BITY_RBT)), "ROBOT", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CMemoryGateTool

CMemoryGateTool::CMemoryGateTool() : CGateTool(memorygate)
{
}

void CMemoryGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_MEM;
   oldpoint.y -= BITY_MEM;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiMemoryGate(CRect(local, CSize(BITX_MEM,-BITY_MEM)), "MEMORY", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CTapedriveGateTool

CTapedriveGateTool::CTapedriveGateTool() : CGateTool(tapedrivegate)
{
}

void CTapedriveGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_TAP;
   oldpoint.y -= BITY_TAP;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiTapedriveGate(CRect(local, CSize(BITX_TAP,-BITY_TAP)), "TAPEDRIVE", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CMuxGateTool

CMuxGateTool::CMuxGateTool() : CGateTool(muxgate)
{
}

void CMuxGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_MUX;
   oldpoint.y -= BITY_MUX;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiMuxGate(CRect(local, CSize(BITX_MUX,-BITY_MUX)), "MUX", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CAluGateTool

CAluGateTool::CAluGateTool() : CGateTool(alugate)
{
}

void CAluGateTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;
   oldpoint.x += BITX_ALU;
   oldpoint.y -= BITY_ALU;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   CLogiGate* pObj = new CLogiAluGate(CRect(local, CSize(BITX_ALU,-BITY_ALU)), "ALU", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(pObj);
   pView->Select(pObj);

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

////////////////////////////////////////////////////////////////////////////
// CWireTool

CWireTool::CWireTool() : CLogiTool(wire)
{
   m_bShowErrorCursor = FALSE;
   m_pObj = NULL;
}

void CWireTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   // While Drawing a wire make sure nothing is selected
   pView->Select(NULL);

   // Assume we are always on an output of a gate for now on down
   CLogiTool::OnLButtonDown(pView, nFlags, point);

   CPoint local = point;
   pView->ClientToDoc(local);

   pStartAnode = pView->GetDocument()->m_pAnodeNULL;
   m_pObj = NULL;

   // Find out if we hit a gate contact if so return contact
   pStartGateObj = (CLogiGate*)pView->GetDocument()->ObjectAtContact(local, &StartIO, pView->m_iPage);

   if (pStartGateObj != NULL)
   {
      pStartAnode = pStartGateObj->Node[StartIO];

      // If pointer exists then flag user and abort
      if (pStartAnode != pView->GetDocument()->m_pAnodeNULL)
      {
         if (StartIO >= pStartGateObj->Outputs)
         {
            //MessageBeep(0xFFFFFFFF);
            SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));
            m_bShowErrorCursor = TRUE;
            return;
         }
      }
      else
      {
         if (StartIO < pStartGateObj->Outputs)
         {
            pView->GetDocument()->NodeList.AddHead(pStartAnode = new Anode(UNKNOWN,"xyz",DRIVE));
         }
      }

      m_pObj = new CLogiWire(CRect(pStartGateObj->Contact[StartIO], CSize(0,0)), "WIRE", pView->m_iPage, pView->GetDocument());

      // FALSE prevents adding the wire to the undo buffer.
      // This is necessary since user might draw a bad wire,
      // causing it to never have logically existed.

      pView->GetDocument()->Add(m_pObj, FALSE);
      pView->Select(m_pObj);

      selectMode = size;
      nDragHandle = 1;
      lastPoint = local;
   }

   // If we did not create a wire then just beep for now

   if (!m_pObj)
   {
      //MessageBeep(0xFFFFFFFF);
      SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));
      m_bShowErrorCursor = TRUE;
   }

}

void CWireTool::OnLButtonDblClk(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CLogiTool::OnLButtonDblClk(pView, nFlags, point);
}

void CWireTool::OnLButtonUp(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   Anode *pAnodeNULL = pView->GetDocument()->m_pAnodeNULL;

   CPoint local = point;
   pView->ClientToDoc(local);
   CPoint c_downt = c_down;
   pView->DocToClient(c_downt);

   // Restore normal cursor
   m_bShowErrorCursor = FALSE;
   SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));

   pEndAnode = pAnodeNULL;

   // Make sure a wire exists
   if (!m_pObj)
   {
      if (pStartAnode != pAnodeNULL)
      {
         // Now handled by displaying an error cursor,
         // thus eliminating this annoying message box.
         //pView->MessageBox("Input already Driven", NULL, MB_ICONEXCLAMATION | MB_OK);
      }
      else
      {
         // Now handled by displaying an error cursor,
         // thus eliminating this annoying message box.
         //pView->MessageBox("Nothing to connect to", NULL, MB_ICONEXCLAMATION | MB_OK);
      }
      goto EXITWIRE;
   }

   // Don't 0 length wires
   if (point == c_downt) goto ABORTWIRE;

   // check for a contact hit
   pEndGateObj = (CLogiGate*)pView->GetDocument()->ObjectAtContact(local, &EndIO, pView->m_iPage);
   if (pEndGateObj != NULL)
   {
      pEndAnode = pEndGateObj->Node[EndIO];

      // If pointer exists then flag user and abort
      if (pEndAnode != pAnodeNULL)
      {
         if (EndIO >= pEndGateObj->Outputs)
         {
            pView->MessageBox("Input already Driven", NULL, MB_ICONEXCLAMATION | MB_OK);
            goto ABORTWIRE;
         }
      }
      else
      {
         if (EndIO < pEndGateObj->Outputs)
         {
            pView->GetDocument()->NodeList.AddHead(pEndAnode = new Anode(UNKNOWN,"xyz",DRIVE));
         }
      }

      // if both nodes then do special procesing
      //***********************************************************************************************************************************************************//
      if ((pEndGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate)))
         && (pStartGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate))))
      {

         // if end has no input connected
         if (pEndGateObj->Node[1] == pAnodeNULL)
         {
            EndIO = 1;
            pEndAnode = pEndGateObj->Node[EndIO];
         }
         // if start has no input connected
         if (pStartGateObj->Node[1] == pAnodeNULL)
         {
            // if end has an input connected then change start to input
            if (pEndGateObj->Node[1] != pAnodeNULL)
            {
               StartIO = 1;
               pStartAnode = pStartGateObj->Node[StartIO];
            }
         }
      }
      // if end is a node
      else if (pEndGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate)))
      {

         // if other gate is an input
         if (StartIO < pStartGateObj->Outputs)
         {
            // if end has an input connected then trouble
            // but it'll be caught further down?
            EndIO = 1;
            pEndAnode = pEndGateObj->Node[EndIO];
         }
      }

      // if start is a node
      else if (pStartGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate)))
      {

         // if other gate is an input
         if (EndIO < pEndGateObj->Outputs)
         {
            StartIO = 1;
            pStartAnode = pStartGateObj->Node[StartIO];
         }
      }

      //***********************************************************************************************************************************************************//
      //if ((pEndGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate)))
      //&& (pStartGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate))))
      //   {

      //   // if start has an input connected
      //   if (pStartGateObj->Node[1] != pAnodeNULL)
      //      {

      //      // if end has an input connected then trouble
      //      if (pEndGateObj->Node[1] != pAnodeNULL)
      //         {
      //         // Error do nothing
      //         }

      //      // else change end to input
      //      else
      //         {
      //         EndIO = 1;
      //         pEndAnode = pEndGateObj->Node[EndIO];
      //         }
      //      }

      //   // else start has no input connected
      //   else
      //      {

      //      // if end has an input connected then change start to input
      //      if (pEndGateObj->Node[1] != pAnodeNULL)
      //         {
      //         StartIO = 1;
      //         pStartAnode = pStartGateObj->Node[StartIO];
      //         }

      //      // else change end to input
      //      else
      //         {
      //         EndIO = 1;
      //         pEndAnode = pEndGateObj->Node[EndIO];
      //         }
      //      }
      //   }

      //// else check one of them is a node
      //else
      //   {

      //   // is end a node
      //   if (pEndGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate)))
      //      {

      //      // if other gate is an input
      //      if (StartIO >= pStartGateObj->Outputs)
      //         {
      //         // Ok do nothing
      //         }
      //      else
      //         {

      //         // if end has an input connected then trouble
      //         if (pEndGateObj->Node[1] != pAnodeNULL)
      //            {
      //            // Error, this will force an error
      //            EndIO = 1;
      //            pEndAnode = pEndGateObj->Node[EndIO];
      //            }

      //         // else change end to input
      //         else
      //            {
      //            EndIO = 1;
      //            pEndAnode = pEndGateObj->Node[EndIO];
      //            }
      //         }
      //      }

      //   // else check the other guy if it's a node
      //   else if (pStartGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate)))
      //      {

      //      // if other gate is an input
      //      if (EndIO >= pEndGateObj->Outputs)
      //         {
      //         // ok do nothing
      //         }
      //      else
      //         {

      //         // if start has an input connected then trouble
      //         if (pStartGateObj->Node[1] != pAnodeNULL)
      //            {
      //            // Error, this will force an error
      //            StartIO = 1;
      //            pStartAnode = pStartGateObj->Node[StartIO];
      //            }

      //         // else change start to input
      //         else
      //            {
      //            StartIO = 1;
      //            pStartAnode = pStartGateObj->Node[StartIO];
      //            }
      //         }
      //      }
      //   }
      //***********************************************************************************************************************************************************//
      if ((pStartAnode != pAnodeNULL) && (pEndAnode != pAnodeNULL))
      {
         pView->MessageBox("Cannot connect 2 Drivers", NULL, MB_ICONEXCLAMATION | MB_OK);
         goto ABORTWIRE;
      }

      if ((pStartAnode == pAnodeNULL) && (pEndAnode == pAnodeNULL))
      {
         pView->MessageBox("Cannot connect 2 Inputs", NULL, MB_ICONEXCLAMATION | MB_OK);
         goto ABORTWIRE;
      }

      if (pStartAnode == pAnodeNULL) pStartAnode = pEndAnode;

      // hook it up
      pEndGateObj->Connect(EndIO, pStartAnode);
      pStartGateObj->Connect(StartIO, pStartAnode);

      // Add this Wire to the wirelist of each contact
      pStartGateObj->Wire[StartIO].AddHead(m_pObj);
      pEndGateObj->Wire[EndIO].AddHead(m_pObj);

      // Snap it to the contact
      CPoint point = pEndGateObj->Contact[EndIO];
      pView->DocToClient(point);

      // Cannot jump to EXITWIRE since point is a new point
      selectTool.OnLButtonUp(pView, nFlags, point);
      pView->Select(NULL);

      // Let wire know gates and contacts (swap if user started on input)
      m_pObj->pEndGateObj = pEndGateObj;
      m_pObj->EndIO = EndIO;
      m_pObj->pStartGateObj = pStartGateObj;
      m_pObj->StartIO = StartIO;

      // Success. The wire undo is a special case for undo
      // because it has already been added to the doc but we had
      // to wait until now to know that it is valid.
      if (m_pObj)
         pView->GetDocument()->m_undo.Push(m_pObj, CUndoElement::Add);

      return;
   }
   else
   {
      // Don't create unconnected wire objects...
      goto ABORTWIRE;
   }


EXITWIRE:

   //   selectTool.OnLButtonUp(pView, nFlags, point);
   pView->Select(NULL);

   return;

ABORTWIRE:

   pView->InvalObj(m_pObj);

   // FALSE means the user can't undo this remove
   pView->GetDocument()->Remove(m_pObj, FALSE);
   delete m_pObj;
   m_pObj = NULL;

   goto EXITWIRE;

}

void CWireTool::OnRButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CLogiTool::OnRButtonDown(pView, nFlags, point);
}

void CWireTool::OnMouseMove(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   // If we have a wire, let the select tool move it
   if (m_pObj != NULL)
      selectTool.OnMouseMove(pView, nFlags, point);
}

BOOL CWireTool::OnSetCursor(CLogiView* /*pView*/, CWnd* /*pWnd*/, UINT /*nHitTest*/, UINT /*message*/)
{
   if (m_bShowErrorCursor)
      SetCursor(AfxGetApp()->LoadStandardCursor(IDC_NO));
   else
      SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
   return TRUE;
}

////////////////////////////////////////////////////////////////////////////
// CTextTool

CTextTool::CTextTool() : CLogiTool(textgate)
{
}

void CTextTool::OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint oldpoint = point;

   oldpoint.x += BITX;
   oldpoint.y -= BITY;

   CLogiTool::OnLButtonDown(pView, nFlags, oldpoint);

   CPoint local = oldpoint;
   pView->ClientToDoc(local);

   m_pObj = new CLogiTextGate(CRect(local, CSize(BITX,-BITY)), "TEXT", pView->m_iPage, pView->GetDocument());

   pView->GetDocument()->Add(m_pObj);
   pView->Select(m_pObj);

   ((CLogiTextGate *) m_pObj)->ResizeRect();

   selectMode = move;
   nDragHandle = 8;
   lastPoint = local;

   OnMouseMove(pView, nFlags, point);
}

void CTextTool::OnLButtonDblClk(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CLogiTool::OnLButtonDblClk(pView, nFlags, point);
}

void CTextTool::OnLButtonUp(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CPoint local = point;
   pView->ClientToDoc(local);

   pView->Select(NULL);
   selectTool.OnLButtonUp(pView, nFlags, point);
}

void CTextTool::OnRButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   CLogiTool::OnRButtonDown(pView, nFlags, point);
}

void CTextTool::OnMouseMove(CLogiView* pView, UINT nFlags, const CPoint& point)
{
   SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
   selectTool.OnMouseMove(pView, nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
