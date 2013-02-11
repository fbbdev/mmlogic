// LogiWire.cpp - implementation for LogiWire objects
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

////////////////////////////////////////////////////////////////////////////
// CLogiWire

IMPLEMENT_SERIAL(CLogiWire, CLogiObj, 0)

CLogiWire::CLogiWire()
{
   pStartGateObj = NULL;
   pEndGateObj = NULL;

   StartIO = -1;
   EndIO = -1;
}

CLogiWire::~CLogiWire()
{
   CleanupReferences();
}

CLogiWire::CLogiWire(const CRect& position, char *name, int ipage, CLogiDoc* pdoc) : CLogiObj(position, wire, ipage, pdoc)
{
   ASSERT_VALID(this);

   pStartGateObj = NULL;
   pEndGateObj = NULL;

   StartIO = -1;
   EndIO = -1;

   Name = name;
}

void CLogiWire::CleanupReferences()
{
   CLogiWire* CurrentWire;
   CLogiGate* CurrentGate;
   POSITION pos1;
   POSITION pos2;

   // If this end is connected proceed with clean up
   if (pStartGateObj)
   {

      // remove contact of gates' graphical pointer to this wire
      for( pos2 = pos1 = pStartGateObj->Wire[StartIO].GetHeadPosition(); (pos2 = pos1) != NULL; )
      {
         CurrentWire = (CLogiWire*) pStartGateObj->Wire[StartIO].GetNext( pos1 );
         if (CurrentWire == this)
         {
            pStartGateObj->Wire[StartIO].RemoveAt( pos2 );
            break;
         }
      }

      // tell node to no longer "drive" the gate the other end was connected to
      for( pos2 = pos1 = pStartGateObj->Node[StartIO]->DeviceList.GetHeadPosition(); (pos2 = pos1) != NULL; )
      {
         CurrentGate = (CLogiGate*) pStartGateObj->Node[StartIO]->DeviceList.GetNext( pos1 );
         if (CurrentGate == pStartGateObj)
         {
            ASSERT(pStartGateObj->Node[StartIO] !=  m_pDocument->m_pAnodeNULL);
            pStartGateObj->Node[StartIO]->DeviceList.RemoveAt( pos2 );
            break;
         }
      }

      if (StartIO >= pStartGateObj->Outputs)
      {
         pStartGateObj->Node[StartIO] = m_pDocument->m_pAnodeNULL;
      }
      else
      {
         // if nothing left then flag it so
         if (pStartGateObj->Wire[StartIO].IsEmpty())
         {
            //             if (pStartGateObj->Node[StartIO]->DeviceList.IsEmpty())
            //             delete pStartGateObj->Node[StartIO];
            pStartGateObj->Node[StartIO] = m_pDocument->m_pAnodeNULL;
         }
      }
   }

   // If this end is connected proceed with clean up
   if (pEndGateObj)
   {

      // remove contact of gates' graphical pointer to this wire
      for( pos2 = pos1 = pEndGateObj->Wire[EndIO].GetHeadPosition(); (pos2 = pos1) != NULL; )
      {
         CurrentWire = (CLogiWire*) pEndGateObj->Wire[EndIO].GetNext( pos1 );
         if (CurrentWire == this)
         {
            pEndGateObj->Wire[EndIO].RemoveAt( pos2 );
            break;
         }
      }

      // tell node to no longer "drive" the gate the other end was connected to
      for( pos2 = pos1 = pEndGateObj->Node[EndIO]->DeviceList.GetHeadPosition(); (pos2 = pos1) != NULL; )
      {
         CurrentGate = (CLogiGate*) pEndGateObj->Node[EndIO]->DeviceList.GetNext( pos1 );
         if (CurrentGate == pEndGateObj)
         {
            ASSERT(pEndGateObj->Node[EndIO] != m_pDocument->m_pAnodeNULL);
            pEndGateObj->Node[EndIO]->DeviceList.RemoveAt( pos2 );
            break;
         }
      }

      if (EndIO >= pEndGateObj->Outputs)
      {
         pEndGateObj->Node[EndIO] = m_pDocument->m_pAnodeNULL;
      }
      else
      {
         // if nothing left then flag it so
         if (pEndGateObj->Node[EndIO]->DeviceList.IsEmpty())
         {
            //             if (pEndGateObj->Wire[EndIO].IsEmpty())
            //             delete pEndGateObj->Node[EndIO];
            pEndGateObj->Node[EndIO] = m_pDocument->m_pAnodeNULL;
         }
      }
   }

   // Must clear these to avoid double cleanup since
   // the destructor also calls this method.
   pStartGateObj = NULL;
   pEndGateObj = NULL;
}

void CLogiWire::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiObj::Serialize(ar);

   if (ar.IsStoring())
   {
      //      ar << m_iInputs;
      //      ar << m_bDemorgan;
   }
   else
   {
      //      ar >> m_iInputs;
      //      ar >> m_bDemorgan;
      //      m_pDocument->ReWire(m_position, this);
   }

}

void CLogiWire::Draw(CDC* pDC, CLogiView* pView)
{
   ASSERT_VALID(this);

   CRect rect = m_position;

   CPoint ptFrom;
   CPoint ptTo;
   CPoint m_ptMid1;
   CPoint m_ptMid2;
   UINT uYDocSize;

   uYDocSize = pView->GetDocument()->m_uCanvasHeight;

   ptFrom = rect.TopLeft();
   ptTo   = rect.BottomRight();

   if (ptFrom.x < ptTo.x)
   {
      if(ptFrom.y < ptTo.y)
         m_ptMid1.x = ptFrom.x + abs(rect.Width()) - (int) ((((float) ptFrom.y) / ((float) uYDocSize)) * (abs(rect.Width())));
      else
         m_ptMid1.x = ptFrom.x + (int) ((((float) ptFrom.y) / ((float) uYDocSize)) * (abs(rect.Width())));
   }
   else
   {
      if(ptFrom.y > ptTo.y)
         m_ptMid1.x = ptTo.x + abs(rect.Width()) - (int) ((((float) ptTo.y) / ((float) uYDocSize)) * (abs(rect.Width())));
      else
         m_ptMid1.x = ptTo.x + (int) ((((float) ptTo.y) / ((float) uYDocSize)) * (abs(rect.Width())));
   }

   m_ptMid2.x = m_ptMid1.x;
   m_ptMid1.y = ptFrom.y;
   m_ptMid2.y = ptTo.y;

   //pick draw color
   if(pStartGateObj == NULL)
   {
      pOldPen = pDC->SelectObject(&m_pDocument->m_cpPurple);
   }
   else if(pView->GetDocument()->m_bSimulating && pView->GetDocument()->m_bColorWires)
   {
      if(pStartGateObj->Node[StartIO]->State == HI)
         pOldPen = pDC->SelectObject(&m_pDocument->m_cpGreen);
      else if(pStartGateObj->Node[StartIO]->State == LO)
         pOldPen = pDC->SelectObject(&m_pDocument->m_cpBlack);
      else
         pOldPen = pDC->SelectObject(&m_pDocument->m_cpRed);
   }
   else
   {
      pOldPen = pDC->SelectObject(&m_pDocument->m_cpBlack);
   }

   pDC->MoveTo(ptFrom);
   pDC->LineTo(m_ptMid1);
   pDC->LineTo(m_ptMid2);
   pDC->LineTo(ptTo);

   pDC->SelectObject(pOldPen);

}

// rect must be in logical coordinates
BOOL CLogiWire::Intersects(const CRect& rect)
{
   ASSERT_VALID(this);

   CRect rectT = rect;
   rectT.NormalizeRect();

   if (rectT.PtInRect(m_position.BottomRight())) return TRUE;
   if (rectT.PtInRect(m_position.TopLeft())) return TRUE;

   return FALSE;
}

int CLogiWire::GetHandleCount()
{
   ASSERT_VALID(this);

   return 2;
   //   return CLogiObj::GetHandleCount();
}

// returns center of handle in logical coordinates
CPoint CLogiWire::GetHandle(int nHandle)
{
   ASSERT_VALID(this);
   int x;
   int y;
   int xCenter;
   int yCenter;

   // this gets the center regardless of left/right and top/bottom ordering
   xCenter = m_position.left + m_position.Width() / 2;
   yCenter = m_position.top + m_position.Height() / 2;

   switch (nHandle)
   {
   default:
      ASSERT(FALSE);

   case 1:
      x = m_position.left;
      y = m_position.top;
      break;

   case 2:
      x = m_position.right;
      y = m_position.bottom;
      break;

   case 3:
      x = xCenter;
      y = m_position.top;
      break;

   case 4:
      x = xCenter;
      y = m_position.bottom;
      break;
   }

   return CPoint(x, y);
}

HCURSOR CLogiWire::GetHandleCursor(int nHandle)
{
   ASSERT_VALID(this);

   return CLogiObj::GetHandleCursor(nHandle);
}

// point is in logical coordinates
void CLogiWire::MoveHandleTo(int nHandle, CPoint point, CLogiView* pView)
{
   ASSERT_VALID(this);

   CLogiObj::MoveHandleTo(nHandle, point, pView);
}

// rect must be in logical coordinates
CLogiObj* CLogiWire::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiWire* pClone = new CLogiWire(m_position, "WIRE", m_iPage, pDoc);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiWire::OnOpen(CLogiView* /*pView*/)
{
   ASSERT_VALID(this);

   CWireDlg dlg;

   dlg.m_iRoute = m_iRoute;
   dlg.m_bHide = m_bHide;

   if (dlg.DoModal() != IDOK) return;

   m_iRoute = dlg.m_iRoute;
   m_bHide = dlg.m_bHide;

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

/////////////////////////////////////////////////////////////////////////////
