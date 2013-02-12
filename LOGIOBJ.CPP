// Logiobj.cpp - implementation for Drawing objects
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

IMPLEMENT_SERIAL(CLogiObj, CObject, 0)

CLogiObj::CLogiObj()
{
}

CLogiObj::~CLogiObj()
{
}

CLogiObj::CLogiObj(const CRect& position, LogiShape shape, int ipage, CLogiDoc* pdoc)
{
   m_Logishape = shape;
   m_position = position;
   m_pDocument = pdoc;
   m_iPage = ipage;
}

void CLogiObj::Serialize(CArchive& ar)
{

   CObject::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_position;
      ar << m_size;
      ar.Write(&m_Logishape, sizeof(m_Logishape));
   }
   else
   {
      // get the document back pointer from the archive
      m_pDocument = (CLogiDoc*)ar.m_pDocument;
      ASSERT_VALID(m_pDocument);
      ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLogiDoc)));

      ar >> m_position;
      ar >> m_size;
      ar.Read(&m_Logishape,sizeof(m_Logishape));
   }
}

void CLogiObj::Draw(CDC* /*pDC*/, CLogiView* /*pView*/)
{
}

void CLogiObj::DrawTracker(CDC* pDC, TrackerState state)
{
   ASSERT_VALID(this);

   switch (state)
   {
   case normal:
      break;

   case selected:
   case active:
      {
         int nHandleCount = GetHandleCount();
         for (int nHandle = 1; nHandle <= nHandleCount; nHandle++)
         {
            CPoint handle = GetHandle(nHandle);
            pDC->PatBlt(handle.x - 3, handle.y - 3, 7, 7, DSTINVERT);
         }
      }
      break;
   }
}

// position is in logical
void CLogiObj::MoveTo(const CRect& position, CLogiView* pView)
{
   ASSERT_VALID(this);

   if (position == m_position) return;

   if (pView == NULL)
   {
      Invalidate();
      m_position = position;
      Invalidate();
   }
   else
   {
      pView->InvalObj(this);
      m_position = position;
      pView->InvalObj(this);
   }
   m_pDocument->SetModifiedFlag();
}

// Note: if bSelected, hit-codes start at one for the top-left
// and increment clockwise, 0 means no hit.
// If !bSelected, 0 = no hit, 1 = hit (anywhere)

// point is in logical coordinates
int CLogiObj::HitTest(CPoint point, CLogiView* pView, BOOL bSelected)
{
   ASSERT_VALID(this);
   ASSERT(pView != NULL);

   if (IsKindOf(RUNTIME_CLASS(CLogiWire))) return 0;

   if (bSelected)
   {
      int nHandleCount = GetHandleCount();
      for (int nHandle = 1; nHandle <= nHandleCount; nHandle += 1)
      {
         // GetHandleRect returns in logical coords
         CRect rc = GetHandleRect(nHandle,pView);
         //if (point.x >= rc.left && point.x < rc.right && point.y <= rc.top && point.y > rc.bottom)
         if (point.x >= rc.left && point.x < rc.right && point.y >= rc.top && point.y < rc.bottom)
         {
            return nHandle;
         }
      }
   }
   else
   {
      if (point.x >= m_position.left && point.x < m_position.right && point.y <= m_position.top && point.y > m_position.bottom)
      {
         return 1;
      }
   }
   return 0;
}

// rect must be in logical coordinates
BOOL CLogiObj::Intersects(const CRect& rect)
{
   ASSERT_VALID(this);

   CRect fixed = m_position;
   fixed.NormalizeRect();
   CRect rectT = rect;
   rectT.NormalizeRect();

   return !(rectT & fixed).IsRectEmpty();
}

int CLogiObj::GetHandleCount()
{
   ASSERT_VALID(this);
   return 8;
}

// returns logical coords of center of handle
CPoint CLogiObj::GetHandle(int nHandle)
{
   ASSERT_VALID(this);
   int x;
   int y;
   int xCenter;
   int yCenter;

   // this gets the center regardless of left/right and top/bottom ordering
   xCenter = m_position.left + m_position.Width()  / 2;
   yCenter = m_position.top  + m_position.Height() / 2;

   switch (nHandle)
   {
   default:
      ASSERT(FALSE);

   case 1:
      x = m_position.left;
      y = m_position.top;
      break;

   case 2:
      x = xCenter;
      y = m_position.top;
      break;

   case 3:
      x = m_position.right;
      y = m_position.top;
      break;

   case 4:
      x = m_position.right;
      y = yCenter;
      break;

   case 5:
      x = m_position.right;
      y = m_position.bottom;
      break;

   case 6:
      x = xCenter;
      y = m_position.bottom;
      break;

   case 7:
      x = m_position.left;
      y = m_position.bottom;
      break;

   case 8:
      x = m_position.left;
      y = yCenter;
      break;
   }

   return CPoint(x, y);
}

// return rectange of handle in logical coords
CRect CLogiObj::GetHandleRect(int nHandleID, CLogiView* pView)
{
   ASSERT_VALID(this);
   ASSERT(pView != NULL);

   CRect rect;

   // get the center of the handle in logical coords
   CPoint point = GetHandle(nHandleID);

   // convert to client/device coords
   pView->DocToClient(point);

   // return CRect of handle in device coords
   rect.SetRect(point.x-3, point.y-3, point.x+3, point.y+3);
   pView->ClientToDoc(rect);

   return rect;
}

HCURSOR CLogiObj::GetHandleCursor(int nHandle)
{
   ASSERT_VALID(this);

   LPCSTR id;
   switch (nHandle)
   {
   default:
      ASSERT(FALSE);

   case 1:
   case 5:
      id = IDC_SIZENWSE;
      break;

   case 2:
   case 6:
      id = IDC_SIZENS;
      break;

   case 3:
   case 7:
      id = IDC_SIZENESW;
      break;

   case 4:
   case 8:
      id = IDC_SIZEWE;
      break;
   }

   return AfxGetApp()->LoadStandardCursor(id);
}

// point must be in logical
void CLogiObj::MoveHandleTo(int nHandle, CPoint point, CLogiView* pView)
{
   ASSERT_VALID(this);

   CRect position = m_position;
   switch (nHandle)
   {
   default:
      ASSERT(FALSE);

   case 1:
      position.left = point.x;
      position.top = point.y;
      break;

   case 2:
      position.top = point.y;
      break;

   case 3:
      position.right = point.x;
      position.top = point.y;
      break;

   case 4:
      position.right = point.x;
      break;

   case 5:
      position.right = point.x;
      position.bottom = point.y;
      break;

   case 6:
      position.bottom = point.y;
      break;

   case 7:
      position.left = point.x;
      position.bottom = point.y;
      break;

   case 8:
      position.left = point.x;
      break;
   }

   MoveTo(position, pView);
}

void CLogiObj::Invalidate()
{
   ASSERT_VALID(this);
   m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_LOGIOBJ, this);
}

void CLogiObj::Remove()
{
   ASSERT_VALID(this);
   m_pDocument->UpdateAllViews(NULL, HINT_REMOVE_LOGIOBJ, this);
}

CLogiObj* CLogiObj::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiObj* pClone = new CLogiObj(m_position, m_Logishape, m_iPage, pDoc);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   return pClone;
}

BOOL CLogiObj::HasText()
{
   ASSERT_VALID(this);

   return FALSE;
}

CString CLogiObj::GetText()
{
   ASSERT_VALID(this);

   return ""; // does not support text
}

void CLogiObj::SetText(LPCTSTR /*text*/)
{
   ASSERT_VALID(this);

   // default - do nothing
}

#ifdef _DEBUG
void CLogiObj::AssertValid()
{
   ASSERT(m_position.left <= m_position.right);
   ASSERT(m_position.bottom <= m_position.top);
}
#endif

////////////////////////////////////////////////////////////////////////////
// CLogiGate

IMPLEMENT_SERIAL(CLogiGate, CLogiObj, 0)

CLogiGate::CLogiGate()
{
   bInitialized = FALSE;
}

CLogiGate::~CLogiGate()
{
   CleanupReferences();
}

CLogiGate::CLogiGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int outputs, int inputs, UINT gateID, LogiShape Logishape): CLogiObj(position, Logishape, ipage, pdoc)
{
   int i;
   ASSERT_VALID(this);

   Name = name;
   Outputs = outputs;
   Inputs = inputs;
   GateID = gateID;
   Contacts = Outputs + Inputs;
   m_size.cx = position.Width();
   m_size.cy = -position.Height();

   rgbTransparent.rgbRed = 128; // puke green
   rgbTransparent.rgbGreen = 128;
   rgbTransparent.rgbBlue = 0;
   rgbTransparent.rgbReserved = 0;

   rgbWhite.rgbRed = 255;
   rgbWhite.rgbGreen = 255;
   rgbWhite.rgbBlue = 255;
   rgbWhite.rgbReserved = 0;

   rgbBlack.rgbRed = 0;
   rgbBlack.rgbGreen = 0;
   rgbBlack.rgbBlue = 0;
   rgbBlack.rgbReserved = 0;

   for (i=0;i<Contacts;i++) Node[i] = m_pDocument->m_pAnodeNULL;
   bInitialized = TRUE;
}

void CLogiGate::CleanupReferences()
{
   int i;
   CLogiWire* CurrentWire;
   POSITION pos;

   ASSERT(bInitialized);

   if (!bInitialized)
      return;

   // Clean all references (Nodes and Graphical Wires) to all contacts.

   for (i=0;i<Contacts;i++)
   {

      // If contact in use then clean up
      if (Node[i])
      {

         // delete all wires connected
         for( pos = Wire[i].GetHeadPosition(); pos != NULL; )
         {
            CurrentWire = (CLogiWire*) Wire[i].GetNext( pos );

            // Remove graphics representation
            CurrentWire->Remove();

            // Note deleting the wire will take care of references to the other end and this gate

            CurrentWire->CleanupReferences();
            // delete CurrentWire; // Now undo's responsibility
         }

         Node[i] = m_pDocument->m_pAnodeNULL;
      }
   }
}

void CLogiGate::Connect(int io, Anode* pAnode)
{
   Node[io] = pAnode;
   if (io >= Outputs) pAnode->DeviceList.AddTail(this);
   else pAnode->pDriverGate = this;
}

void CLogiGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiObj::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << (WORD)Outputs;
      ar << (WORD)Inputs;
      ar << (WORD)GateID;
      ar << (WORD)Contacts;
   }
   else
   {
      WORD wTemp;
      int i;

      ar >> wTemp; Outputs = (int)wTemp;
      ar >> wTemp; Inputs = (int)wTemp;
      ar >> wTemp; GateID = (UINT)wTemp;
      ar >> wTemp; Contacts = (int)wTemp;

      rgbTransparent.rgbRed = 128; // puke green
      rgbTransparent.rgbGreen = 128;
      rgbTransparent.rgbBlue = 0;
      rgbTransparent.rgbReserved = 0;

      rgbWhite.rgbRed = 255;
      rgbWhite.rgbGreen = 255;
      rgbWhite.rgbBlue = 255;
      rgbWhite.rgbReserved = 0;

      rgbBlack.rgbRed = 0;
      rgbBlack.rgbGreen = 0;
      rgbBlack.rgbBlue = 0;
      rgbBlack.rgbReserved = 0;

      // If serialize is called to deserialize to an already initialized
      // object, then preserve the nodes. This allows
      // the Undo system to restore an object to a previous state.

      if (!bInitialized)
         for (i=0;i<Contacts;i++) Node[i] = m_pDocument->m_pAnodeNULL;
      bInitialized = TRUE;
   }
}

void CLogiGate::MoveTo(const CRect& /*position*/, CLogiView* pView)
{
   CLogiWire* CurrentWire;
   CRect dummy;
   POSITION pos;
   int i;

   // for each contact (node) modify each wire position

   for (i=0;i<Contacts;i++)
   {

      // skip if not connected
      if (Node[i] != m_pDocument->m_pAnodeNULL)
      {

         //  modify all wires associated with this output contact (node)
         for( pos = Wire[i].GetHeadPosition(); pos != NULL; )
         {
            CurrentWire = (CLogiWire*) Wire[i].GetNext( pos );
            dummy = CurrentWire->m_position;

            // Find the correct end, depends on which end want and direction it was drawn
            if (i<Outputs)
            {
               if (CurrentWire->StartIO >= CurrentWire->pStartGateObj->Outputs)
               {
                  dummy.left = Contact[i].x;
                  dummy.top  = Contact[i].y;
               }
               else
               {
                  dummy.right  = Contact[i].x;
                  dummy.bottom = Contact[i].y;
               }
            }
            else
            {
               if (CurrentWire->StartIO >= CurrentWire->pStartGateObj->Outputs)
               {
                  dummy.right  = Contact[i].x;
                  dummy.bottom = Contact[i].y;
               }
               else
               {
                  dummy.left = Contact[i].x;
                  dummy.top  = Contact[i].y;
               }
            }
            CurrentWire->MoveTo(dummy, pView);
         }
      }
   }
}

void CLogiGate::Draw(CDC* pDC, CLogiView* /* pView */)
{
   ASSERT_VALID(this);

   hResource = FindResource(AfxGetInstanceHandle(),MAKEINTRESOURCE(GateID),RT_BITMAP);
   hBitmap = LoadResource(AfxGetInstanceHandle(),hResource);
   pBmi = (BITMAPINFO *) LockResource(hBitmap);

   memcpy(&m_Bmi, pBmi, sizeof(BITMAPINFOHEADER));

   m_position.right = m_position.left + m_size.cx;
   m_position.bottom = m_position.top - m_size.cy;
   rect = m_position;

   size = sizeof(BITMAPINFOHEADER) + ((1 << m_Bmi.bmiHeader.biBitCount) * sizeof(RGBQUAD));

   // backup color table and mung the orignal to build a mask

   for (i=0;i<16;i++)
   {
      if (*(DWORD *) &pBmi->bmiColors[i] == *(DWORD *) &rgbTransparent)
      {
         m_Bmi.bmiColors[i] = rgbWhite;
      }
      else
      {
         m_Bmi.bmiColors[i] = rgbBlack;
      }
   }

   // Draw Mask

   ::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.bottom, m_size.cx, m_size.cy, 0, 0, m_size.cx, m_size.cy, (void *)(((DWORD) pBmi)+size), (BITMAPINFO *)&m_Bmi, DIB_RGB_COLORS, SRCAND);

   // Now modify color table to properly overlay the image

   for (i=0;i<16;i++)
   {
      if (*(DWORD *) &m_Bmi.bmiColors[i] == *(DWORD *) &rgbWhite)
      {
         m_Bmi.bmiColors[i] = rgbBlack;
      }
      else
      {
         m_Bmi.bmiColors[i] = pBmi->bmiColors[i];
      }
   }

   // draw overlay

   ::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.bottom, m_size.cx, m_size.cy, 0, 0, m_size.cx, m_size.cy, (void *)(((DWORD) pBmi)+size), (BITMAPINFO *) &m_Bmi, DIB_RGB_COLORS, SRCPAINT);

#ifdef _DEBUG
   UnlockResource(hBitmap);
   FreeResource(hBitmap);
#endif

}

int CLogiGate::GetHandleCount()
{
   ASSERT_VALID(this);

   return CLogiObj::GetHandleCount();
}

// returns center of handle in logical coordinates
CPoint CLogiGate::GetHandle(int nHandle)
{
   ASSERT_VALID(this);

   return CLogiObj::GetHandle(nHandle);
}

HCURSOR CLogiGate::GetHandleCursor(int nHandle)
{
   ASSERT_VALID(this);

   return CLogiObj::GetHandleCursor(nHandle);
}

// point is in logical coordinates
void CLogiGate::MoveHandleTo(int nHandle, CPoint point, CLogiView* pView)
{
   ASSERT_VALID(this);

   CLogiObj::MoveHandleTo(nHandle, point, pView);
}

// rect must be in logical coordinates
void CLogiGate::Animate(CLogiView* /*pView*/)
{

   // Only Some devices will overide this to perform animation

}

void CLogiGate::Action(CLogiView* /*pView*/, BOOL /*bDown*/, const CPoint& /*point*/)
{

   // Only Some devices will overide this to perform actions

}

void CLogiGate::Initialize(CLogiView* /*pView*/, UINT /*iMode*/)
{

   // Only Some devices will overide this to perform initialization
   EventCycle = -1;

}

void CLogiGate::Cleanup(CLogiView* /*pView*/)
{

   // Only Some devices will overide this to perform cleanup

}

void CLogiGate::Simulate(CLogiDoc* pDoc)
{
   POSITION pos;
   CLogiGate* CurrentGate;
   //CLogiWire* CurrentWire;

   // for each output node

   for (int i=0;i<Outputs;i++)
   {

      // Only if the state Changed will we bother to Queue it

      if ((Node[i]->State != Node[i]->NextState) || (Node[i]->DriveState != Node[i]->NextDriveState))
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            ASSERT(pDoc->UpdateNodeQueue.Find(Node[i]) == NULL);
            pDoc->UpdateNodeQueue.AddTail(Node[i]);
         }

         // Queue an Event for each effected fanout

         for( pos = Node[i]->DeviceList.GetHeadPosition(); pos != NULL; )
         {
            ASSERT(Node[i] != m_pDocument->m_pAnodeNULL);

            CurrentGate = (CLogiGate*) Node[i]->DeviceList.GetNext( pos );

            if (CurrentGate->m_Logishape == signalsendergate ||
               CurrentGate->m_Logishape == busgate ||
               CurrentGate->m_Logishape == nullgate)
            {
               pDoc->CallPostQueue.AddTail(CurrentGate);
            }

            // if this device has already been queued no need to do it again

            if (CurrentGate->EventCycle != pDoc->m_uCycleCount)
            {
               pDoc->EventQueue.AddTail(CurrentGate);
               CurrentGate->EventCycle = pDoc->m_uCycleCount;
            }
         }


         //color wires
         //  this method, although probably faster than updating the whole window,
         //  is not very accurate, so CLogiDoc::Simulate has code to invalidate the whole window
         //for( pos = Wire[i].GetHeadPosition(); pos != NULL; )
         //   {
         //	   CurrentWire = (CLogiWire*) Wire[i].GetNext( pos );

         //	   CurrentWire->Invalidate();
         //   }
      }
   }
}

BOOL CLogiGate::PostSimulate(CLogiDoc* /* pDoc */)
{
   return FALSE;
}

CLogiObj* CLogiGate::Clone(CLogiDoc* /*pDoc*/)
{
   // here so I don't break the seialize chain
   return NULL;
}

////////////////////////////////////////////////////////////////////////////
// CLogiANDGate

IMPLEMENT_SERIAL(CLogiANDGate, CLogiGate, 0)

CLogiANDGate::CLogiANDGate()
{
}

CLogiANDGate::CLogiANDGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iAnd2inputs, BOOL bAndDemorgan) : CLogiGate(position, name, ipage, pdoc, 1, 2+iAnd2inputs, IDB_AND2, andgate)
{

   m_iInputs = iAnd2inputs;
   m_bDemorgan = bAndDemorgan;

   SetGateID();
   SetContacts();

}

void CLogiANDGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iInputs;
      ar << m_bDemorgan;
   }
   else
   {
      ar >> m_iInputs;
      ar >> m_bDemorgan;

      SetGateID();
      SetContacts();
   }

}

void CLogiANDGate::Simulate(CLogiDoc* pDoc)
{
   int i;

   // Perform Simulation

   if (m_bDemorgan)
   {
      (Node[0])->NextState = LO;

      for (i=1;i<=Inputs;i++)
      {
         if ((Node[i])->State == LO)
         {
            (Node[0])->NextState = HI;
            break;
         }

         if ((Node[i])->State == UNKNOWN)
         {
            (Node[0])->NextState = UNKNOWN;
         }
      }
   }
   else
   {
      (Node[0])->NextState = HI;

      for (i=1;i<=Inputs;i++)
      {
         if ((Node[i])->State == LO)
         {
            (Node[0])->NextState = LO;
            break;
         }

         if ((Node[i])->State == UNKNOWN)
         {
            (Node[0])->NextState = UNKNOWN;
         }
      }
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiANDGate::SetGateID(void)
{
   Inputs = 2 + m_iInputs;
   Contacts = Outputs + Inputs;

   if (m_bDemorgan)
   {
      switch (Inputs)
      {
      case 2: GateID = IDB_NAND2; break;
      case 3: GateID = IDB_NAND3; break;
      case 4: GateID = IDB_NAND4; break;
      }
   }
   else
   {
      switch (Inputs)
      {
      case 2: GateID = IDB_AND2; break;
      case 3: GateID = IDB_AND3; break;
      case 4: GateID = IDB_AND4; break;
      }
   }
}

void CLogiANDGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   switch (Inputs)
   {
   case 2:
      {
         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_IN_Y_2_2;

         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_IN_Y_2_1;
         break;
      }
   case 3:
      {
         Contact[3].x += CONTACT_X_IN;
         Contact[3].y -= CONTACT_IN_Y_3_3;

         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_IN_Y_3_2;

         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_IN_Y_3_1;
         break;
      }
   case 4:
      {
         Contact[4].x += CONTACT_X_IN;
         Contact[4].y -= CONTACT_IN_Y_4_4;

         Contact[3].x += CONTACT_X_IN;
         Contact[3].y -= CONTACT_IN_Y_4_3;

         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_IN_Y_4_2;

         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_IN_Y_4_1;
         break;
      }
   }

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_OUT_Y_1_1;
}


void CLogiANDGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiANDGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiANDGate* pClone = new CLogiANDGate(m_position, Name, m_iPage, pDoc, m_iInputs, m_bDemorgan);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiANDGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   int i;
   CAndDlg dlg;

   dlg.m_iInputs = m_iInputs;
   dlg.m_bDemorgan = m_bDemorgan;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   if (m_iInputs != dlg.m_iInputs)
   {
      for (i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing number of inputs", "Error", MB_ICONEXCLAMATION);
            return;
         }
      }

      for (i=0;i<(Outputs + 2 + dlg.m_iInputs);i++) Node[i] = m_pDocument->m_pAnodeNULL;
   }

   m_iInputs = dlg.m_iInputs;
   m_bDemorgan = dlg.m_bDemorgan;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiXORGate

IMPLEMENT_SERIAL(CLogiXORGate, CLogiGate, 0)

CLogiXORGate::CLogiXORGate()
{
}

CLogiXORGate::CLogiXORGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iXor2inputs, BOOL bXorDemorgan) : CLogiGate(position, name, ipage, pdoc, 1, 2+iXor2inputs, IDB_XOR2, xorgate)
{

   m_iInputs = iXor2inputs;
   m_bDemorgan = bXorDemorgan;

   SetGateID();
   SetContacts();

}

void CLogiXORGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iInputs;
      ar << m_bDemorgan;
   }
   else
   {
      ar >> m_iInputs;
      ar >> m_bDemorgan;

      SetGateID();
      SetContacts();
   }
}

void CLogiXORGate::Simulate(CLogiDoc* pDoc)
{
   int i;
   int iCountHI = 0;

   // Perform Simulation

   // Count Number of HI inputs

   for (i=1;i<=Inputs;i++)
   {
      if      ((Node[i])->State == HI     ) iCountHI++;
      else if ((Node[i])->State == UNKNOWN)
      {
         (Node[0])->NextState = UNKNOWN;
         goto XORUNKNOWN;
      }
   }

   // If true (exactly 1) set appropriate output

   if (iCountHI % 2 == 1)
   {
      if (m_bDemorgan)
      {
         (Node[0])->NextState = LO;
      }
      else
      {
         (Node[0])->NextState = HI;
      }
   }
   else
   {
      if (m_bDemorgan)
      {
         (Node[0])->NextState = HI;
      }
      else
      {
         (Node[0])->NextState = LO;
      }
   }

XORUNKNOWN:

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiXORGate::SetGateID(void)
{
   Inputs = 2 + m_iInputs;
   Contacts = Outputs + Inputs;

   if (m_bDemorgan)
   {
      switch (Inputs)
      {
      case 2: GateID = IDB_XNOR2; break;
      case 3: GateID = IDB_XNOR3; break;
      case 4: GateID = IDB_XNOR4; break;
      }
   }
   else
   {
      switch (Inputs)
      {
      case 2: GateID = IDB_XOR2; break;
      case 3: GateID = IDB_XOR3; break;
      case 4: GateID = IDB_XOR4; break;
      }
   }
}

void CLogiXORGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   switch (Inputs)
   {
   case 2:
      {
         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_IN_Y_2_2;

         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_IN_Y_2_1;
         break;
      }
   case 3:
      {
         Contact[3].x += CONTACT_X_IN;
         Contact[3].y -= CONTACT_IN_Y_3_3;

         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_IN_Y_3_2;

         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_IN_Y_3_1;
         break;
      }
   case 4:
      {
         Contact[4].x += CONTACT_X_IN;
         Contact[4].y -= CONTACT_IN_Y_4_4;

         Contact[3].x += CONTACT_X_IN;
         Contact[3].y -= CONTACT_IN_Y_4_3;

         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_IN_Y_4_2;

         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_IN_Y_4_1;
         break;
      }
   }

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_OUT_Y_1_1;
}


void CLogiXORGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiXORGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiXORGate* pClone = new CLogiXORGate(m_position, Name, m_iPage, pDoc, m_iInputs, m_bDemorgan);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiXORGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   int i;
   CXorDlg dlg;

   dlg.m_i2Inputs = m_iInputs;
   dlg.m_bDemorgan = m_bDemorgan;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   if (m_iInputs != dlg.m_i2Inputs)
   {
      for (i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing number of inputs", "Error", MB_ICONEXCLAMATION);
            return;
         }
      }

      for (i=0;i<(Outputs + 2 + dlg.m_i2Inputs);i++) Node[i] = m_pDocument->m_pAnodeNULL;
   }

   m_iInputs = dlg.m_i2Inputs;
   m_bDemorgan = dlg.m_bDemorgan;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiORGate

IMPLEMENT_SERIAL(CLogiORGate, CLogiGate, 0)

CLogiORGate::CLogiORGate()
{
}

CLogiORGate::CLogiORGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iOr2inputs, BOOL bOrDemorgan) : CLogiGate(position, name, ipage, pdoc, 1, 2+iOr2inputs, IDB_OR2, orgate)
{

   m_iInputs = iOr2inputs;
   m_bDemorgan = bOrDemorgan;

   SetGateID();
   SetContacts();

}

void CLogiORGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iInputs;
      ar << m_bDemorgan;
   }
   else
   {
      ar >> m_iInputs;
      ar >> m_bDemorgan;

      SetGateID();
      SetContacts();
   }
}

void CLogiORGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   if (m_bDemorgan)
   {
      (Node[0])->NextState = HI;

      for (int i=1;i<=Inputs;i++)
      {
         if ((Node[i])->State == HI)
         {
            (Node[0])->NextState = LO;
            break;
         }

         if ((Node[i])->State == UNKNOWN)
         {
            (Node[0])->NextState = UNKNOWN;
         }
      }
   }
   else
   {
      (Node[0])->NextState = LO;

      for (int i=1;i<=Inputs;i++)
      {
         if ((Node[i])->State == HI)
         {
            (Node[0])->NextState = HI;
            break;
         }

         if ((Node[i])->State == UNKNOWN)
         {
            (Node[0])->NextState = UNKNOWN;
         }
      }
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiORGate::SetGateID(void)
{
   Inputs = 2 + m_iInputs;
   Contacts = Outputs + Inputs;

   if (m_bDemorgan)
   {
      switch (Inputs)
      {
      case 2: GateID = IDB_NOR2; break;
      case 3: GateID = IDB_NOR3; break;
      case 4: GateID = IDB_NOR4; break;
      }
   }
   else
   {
      switch (Inputs)
      {
      case 2: GateID = IDB_OR2; break;
      case 3: GateID = IDB_OR3; break;
      case 4: GateID = IDB_OR4; break;
      }
   }
}

void CLogiORGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   switch (Inputs)
   {
   case 2:
      {
         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_IN_Y_2_2;

         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_IN_Y_2_1;
         break;
      }
   case 3:
      {
         Contact[3].x += CONTACT_X_IN;
         Contact[3].y -= CONTACT_IN_Y_3_3;

         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_IN_Y_3_2;

         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_IN_Y_3_1;
         break;
      }
   case 4:
      {
         Contact[4].x += CONTACT_X_IN;
         Contact[4].y -= CONTACT_IN_Y_4_4;

         Contact[3].x += CONTACT_X_IN;
         Contact[3].y -= CONTACT_IN_Y_4_3;

         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_IN_Y_4_2;

         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_IN_Y_4_1;
         break;
      }
   }

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_OUT_Y_1_1;
}


void CLogiORGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiORGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiORGate* pClone = new CLogiORGate(m_position, Name, m_iPage, pDoc, m_iInputs, m_bDemorgan);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiORGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   int i;
   COrDlg dlg;

   dlg.m_iInputs = m_iInputs;
   dlg.m_bDemorgan = m_bDemorgan;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   if (m_iInputs != dlg.m_iInputs)
   {
      for (i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing number of inputs", "Error", MB_ICONEXCLAMATION);
            return;
         }
      }

      for (i=0;i<(Outputs + 2 + dlg.m_iInputs);i++) Node[i] = m_pDocument->m_pAnodeNULL;
   }

   m_iInputs = dlg.m_iInputs;
   m_bDemorgan = dlg.m_bDemorgan;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiOscillatorGate

IMPLEMENT_SERIAL(CLogiOscillatorGate, CLogiGate, 0)

CLogiOscillatorGate::CLogiOscillatorGate()
{
}

CLogiOscillatorGate::CLogiOscillatorGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int CountHI, int CountLO) : CLogiGate(position, name, ipage, pdoc, 1, 0, IDB_OSCILLATOR, oscillatorgate)
{

   m_iCountHI = CountHI;
   m_iCountLO = CountLO;

   SetGateID();
   SetContacts();
}

void CLogiOscillatorGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iCountHI;
      ar << m_iCountLO;
   }
   else
   {
      ar >> m_iCountHI;
      ar >> m_iCountLO;

      SetGateID();
      SetContacts();
   }
}

void CLogiOscillatorGate::Initialize(CLogiView* pView, UINT iMode)
{
   // Simulate will decrement this and test for equality with
   // zero. Then the state will become LO.
   m_Fire = 1;

   CLogiGate::Initialize(pView, iMode);
}

void CLogiOscillatorGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   m_Fire--;

   if (m_Fire == 0)
   {
      if (((Node[0])->State) == LO)
      {
         (Node[0])->NextState = HI;
         m_Fire = m_iCountHI;
      }
      else
      {
         (Node[0])->NextState = LO;
         m_Fire = m_iCountLO;
      }

      // Call base class to Queue Events for Driven Devices

      CLogiGate::Simulate(pDoc);
   }
   else
   {
      (Node[0])->NextState = (Node[0])->State;
   }

   // Oscillator also must ReQueue itself

   pDoc->EventQueue.AddTail(this);
}

void CLogiOscillatorGate::SetGateID(void)
{
   GateID = IDB_OSCILLATOR;
}

void CLogiOscillatorGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_OUT_Y_1_1;
}


void CLogiOscillatorGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiOscillatorGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiOscillatorGate* pClone = new CLogiOscillatorGate(m_position, Name, m_iPage, pDoc, m_iCountHI, m_iCountLO);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiOscillatorGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   COscillatorDlg dlg;

   dlg.m_iOscillatorHi = m_iCountHI;
   dlg.m_iOscillatorLo = m_iCountLO;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iCountHI = dlg.m_iOscillatorHi;
   m_iCountLO = dlg.m_iOscillatorLo;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiINVERTGate

IMPLEMENT_SERIAL(CLogiINVERTGate, CLogiGate, 0)

CLogiINVERTGate::CLogiINVERTGate()
{
}

CLogiINVERTGate::CLogiINVERTGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bInvertDemorgan) : CLogiGate(position, name, ipage, pdoc, 1, 1, IDB_INVERT, invertgate)
{

   m_bDemorgan = bInvertDemorgan;

   SetGateID();
   SetContacts();

}

void CLogiINVERTGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      //      ar << m_iInvert2inputs;
      ar << m_bDemorgan;
   }
   else
   {
      //      ar >> m_iInvert2inputs;
      ar >> m_bDemorgan;

      SetGateID();
      SetContacts();
   }
}

void CLogiINVERTGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   if (m_bDemorgan)
   {
      (Node[0])->NextState = (Node[1])->State;
   }
   else
   {
      if      ((Node[1])->State == LO) (Node[0])->NextState = HI;
      else if ((Node[1])->State == HI) (Node[0])->NextState = LO;
      else                             (Node[0])->NextState = UNKNOWN;
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiINVERTGate::SetGateID(void)
{
   if (m_bDemorgan)
   {
      GateID = IDB_BUFFER;
   }
   else
   {
      GateID = IDB_INVERT;
   }
}

void CLogiINVERTGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[1].x += CONTACT_X_IN;
   Contact[1].y -= CONTACT_IN_Y_1_1;

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_OUT_Y_1_1;
}


void CLogiINVERTGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiINVERTGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiINVERTGate* pClone = new CLogiINVERTGate(m_position, Name, m_iPage, pDoc, m_bDemorgan);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiINVERTGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CInvertDlg dlg;

   dlg.m_bDemorgan = m_bDemorgan;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_bDemorgan = dlg.m_bDemorgan;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiTristateGate

IMPLEMENT_SERIAL(CLogiTristateGate, CLogiGate, 0)

CLogiTristateGate::CLogiTristateGate()
{
}

CLogiTristateGate::CLogiTristateGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bDemorgan, BOOL bAssertLO) : CLogiGate(position, name, ipage, pdoc, 1, 2, IDB_TRISTATE_BUFFER_LO, tristategate)
{

   m_bDemorgan = bDemorgan;
   m_bAssertLO = bAssertLO;

   SetGateID();
   SetContacts();

}

void CLogiTristateGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_bAssertLO;
      ar << m_bDemorgan;
   }
   else
   {
      ar >> m_bAssertLO;
      ar >> m_bDemorgan;

      SetGateID();
      SetContacts();
   }
}

void CLogiTristateGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   BOOL bAsserted = FALSE;

   if (m_bAssertLO)
   {
      if ((Node[1])->State == LO) bAsserted = TRUE;
   }
   else
   {
      if ((Node[1])->State == HI) bAsserted = TRUE;
   }

   if (bAsserted)
   {
      if (m_bDemorgan)
      {
         (Node[0])->NextState = (Node[2])->State;
      }
      else
      {
         if      ((Node[2])->State == LO) (Node[0])->NextState = HI;
         else if ((Node[2])->State == HI) (Node[0])->NextState = LO;
         else                             (Node[0])->NextState = UNKNOWN;
      }

      Node[0]->NextDriveState = DRIVE;
   }
   else
   {
      Node[0]->NextState = UNKNOWN;
      Node[0]->NextDriveState = FLOAT;
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiTristateGate::SetGateID(void)
{
   if (m_bAssertLO)
   {
      if (m_bDemorgan)
      {
         GateID = IDB_TRISTATE_BUFFER_LO;
      }
      else
      {
         GateID = IDB_TRISTATE_INVERT_LO;
      }
   }
   else
   {
      if (m_bDemorgan)
      {
         GateID = IDB_TRISTATE_BUFFER_HI;
      }
      else
      {
         GateID = IDB_TRISTATE_INVERT_HI;
      }
   }
}

void CLogiTristateGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[2].x += CONTACT_X_IN;
   Contact[2].y -= CONTACT_IN_Y_1_1;

   Contact[1].x += CONTACT_X_IN;
   Contact[1].y -= CONTACT_Y_1;

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_OUT_Y_1_1;
}


void CLogiTristateGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiTristateGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiTristateGate* pClone = new CLogiTristateGate(m_position, Name, m_iPage, pDoc, m_bDemorgan, m_bAssertLO);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiTristateGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CTristateDlg dlg;

   dlg.m_bDemorgan = m_bDemorgan;
   dlg.m_bAssertLO = m_bAssertLO;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_bDemorgan = dlg.m_bDemorgan;
   m_bAssertLO = dlg.m_bAssertLO;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiBusGate

IMPLEMENT_SERIAL(CLogiBusGate, CLogiGate, 0)

CLogiBusGate::CLogiBusGate()
{
}

CLogiBusGate::CLogiBusGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iInputs, BOOL bDummy2) : CLogiGate(position, name, ipage, pdoc, 1, 8, IDB_BUS_8, busgate)
{

   m_iInputs = iInputs;
   m_bDummy2 = bDummy2;

   SetGateID();
   SetContacts();

}

void CLogiBusGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iInputs;
      ar << m_bDummy2;
   }
   else
   {
      ar >> m_iInputs;
      ar >> m_bDummy2;

      SetGateID();
      SetContacts();
   }
}

void CLogiBusGate::Simulate(CLogiDoc* /* pDoc */)
{

   // This Method must exist so that the Base Class is not called
   // for performance reasons. PostSimulate will take care of it

   // Call base class to Queue Events for Driven Devices

   // CLogiGate::Simulate(pDoc);
}

BOOL CLogiBusGate::PostSimulate(CLogiDoc* pDoc)
{
   int PrevState;
   int PrevDriveState;

   if (Node[0] == m_pDocument->m_pAnodeNULL) return FALSE;

   PrevState = Node[0]->NextState;
   PrevDriveState = Node[0]->NextDriveState;

   int iDriver = -1;
   BOOL bBadDriver = FALSE;
   int iPuller = -1;
   BOOL bBadPuller = FALSE;
   int iPullerState = UNKNOWN;

   for (int i=0;i<Inputs;i++)
   {
      if (Node[i+1]->NextDriveState == DRIVE)
      {
         if (iDriver != -1)
         {
            bBadDriver = TRUE;
            break;
         }
         iDriver = i;
      }
      else if (Node[i+1]->NextState != UNKNOWN)
      {
         if ((iPuller != -1) && (iPullerState != Node[i+1]->NextState))
         {
            bBadPuller = TRUE;
            break;
         }
         iPuller = i;
         iPullerState = Node[i+1]->NextState;
      }
   }

   if (bBadDriver)
   {
      Node[0]->NextState = UNKNOWN;
      Node[0]->NextDriveState = DRIVE;
   }
   else if (iDriver == -1)
   {
      if (bBadPuller)
      {
         Node[0]->NextState = UNKNOWN;
         Node[0]->NextDriveState = FLOAT;
      }
      else
      {
         Node[0]->NextState = iPullerState;
         Node[0]->NextDriveState = FLOAT;
      }
   }
   else
   {
      Node[0]->NextState = Node[iDriver+1]->NextState;
      Node[0]->NextDriveState = DRIVE;
   }

   if ((PrevState != Node[0]->NextState) || (PrevDriveState != Node[0]->NextDriveState) )
   {
      // Call base class to Queue Events for Driven Devices

      Node[0]->State = !Node[0]->NextState; // Force difference to propagate

      CLogiGate::Simulate(pDoc);

      return TRUE;
   }

   return FALSE;
}


void CLogiBusGate::SetGateID(void)
{
   switch (m_iInputs)
   {
   case 0:
      {
         GateID = IDB_BUS_2;
         Inputs = 2;
         Outputs = 1;

         break;
      }
   case 1:
      {
         GateID = IDB_BUS_4;
         Inputs = 4;
         Outputs = 1;

         break;
      }
   case 2:
      {
         GateID = IDB_BUS_8;
         Inputs = 8;
         Outputs = 1;

         break;
      }
   }

   Contacts = Outputs + Inputs;
}

void CLogiBusGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   switch (m_iInputs)
   {
   case 0:
      {
         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_Y_5;
         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_Y_4;

         Contact[0].x += CONTACT_X_OUT;
         Contact[0].y -= CONTACT_Y_8;
         break;
      }
   case 1:
      {
         Contact[4].x += CONTACT_X_IN;
         Contact[4].y -= CONTACT_Y_6;
         Contact[3].x += CONTACT_X_IN;
         Contact[3].y -= CONTACT_Y_5;
         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_Y_4;
         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_Y_3;

         Contact[0].x += CONTACT_X_OUT;
         Contact[0].y -= CONTACT_Y_8;
         break;
      }
   case 2:
      {
         Contact[8].x += CONTACT_X_IN;
         Contact[8].y -= CONTACT_Y_8;
         Contact[7].x += CONTACT_X_IN;
         Contact[7].y -= CONTACT_Y_7;
         Contact[6].x += CONTACT_X_IN;
         Contact[6].y -= CONTACT_Y_6;
         Contact[5].x += CONTACT_X_IN;
         Contact[5].y -= CONTACT_Y_5;
         Contact[4].x += CONTACT_X_IN;
         Contact[4].y -= CONTACT_Y_4;
         Contact[3].x += CONTACT_X_IN;
         Contact[3].y -= CONTACT_Y_3;
         Contact[2].x += CONTACT_X_IN;
         Contact[2].y -= CONTACT_Y_2;
         Contact[1].x += CONTACT_X_IN;
         Contact[1].y -= CONTACT_Y_1;

         Contact[0].x += CONTACT_X_OUT;
         Contact[0].y -= CONTACT_Y_8;
         break;
      }
   }

}


void CLogiBusGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiBusGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiBusGate* pClone = new CLogiBusGate(m_position, Name, m_iPage, pDoc, m_iInputs, m_bDummy2);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiBusGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CBusDlg dlg;

   dlg.m_iInputs = m_iInputs;
   // dlg.m_bDummy2 = m_bDummy2;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   if (m_iInputs != dlg.m_iInputs)
   {
      for (int i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing number of inputs", "Error", MB_ICONEXCLAMATION);
            return;
         }
      }

      for (/*jal int */  i=0;i<(Outputs + (2<<dlg.m_iInputs));i++) Node[i] = m_pDocument->m_pAnodeNULL;
   }

   m_iInputs = dlg.m_iInputs;
   // m_bDummy2 = dlg.m_bDummy2;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiClockGate

IMPLEMENT_SERIAL(CLogiClockGate, CLogiGate, 0)

CLogiClockGate::CLogiClockGate()
{
}

CLogiClockGate::CLogiClockGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int Seconds, BOOL Spare) : CLogiGate(position, name, ipage, pdoc, 8, 0, IDB_CLOCK, clockgate)
{
   m_iSeconds = Seconds;
   m_bSpare = Spare;

   SetGateID();
   SetContacts();
}

void CLogiClockGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iSeconds;
      ar << m_bSpare;
   }
   else
   {
      ar >> m_iSeconds;
      ar >> m_bSpare;

      SetGateID();
      SetContacts();
   }
}

void CLogiClockGate::Initialize(CLogiView* pView, UINT iMode)
{
   m_uTemp = 0xFFFF;

   CLogiGate::Initialize(pView, iMode);
}

void CLogiClockGate::Simulate(CLogiDoc* pDoc)
{
   UINT uTemp = 0;

   // Perform Simulation

   CTime ctCurrent = CTime::GetCurrentTime();

   switch (m_iSeconds)
   {
   case 0: uTemp = ctCurrent.GetSecond(); break;
   case 1: uTemp = ctCurrent.GetMinute(); break;
   case 2: uTemp = ctCurrent.GetHour(); break;
   case 3: uTemp = ctCurrent.GetDay(); break;
   case 4: uTemp = ctCurrent.GetMonth(); break;
   case 5: uTemp = ctCurrent.GetYear(); break;
   }

   for (i=0;i<8;i++)
   {
      if (uTemp & (1<<i)) (Node[i])->NextState = HI; else (Node[i])->NextState = LO;
   }

   // Call base class to Queue Events for Driven Devices (if a change occured)

   if (uTemp != m_uTemp)
   {
      m_uTemp = uTemp;
      CLogiGate::Simulate(pDoc);
   }

   // Clock also must ReQueue itself

   pDoc->EventQueue.AddTail(this);
}

void CLogiClockGate::SetGateID(void)
{
   GateID = IDB_CLOCK;
}

void CLogiClockGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[7].x += CONTACT_X_OUT;
   Contact[7].y -= CONTACT_Y_8;
   Contact[6].x += CONTACT_X_OUT;
   Contact[6].y -= CONTACT_Y_7;
   Contact[5].x += CONTACT_X_OUT;
   Contact[5].y -= CONTACT_Y_6;
   Contact[4].x += CONTACT_X_OUT;
   Contact[4].y -= CONTACT_Y_5;
   Contact[3].x += CONTACT_X_OUT;
   Contact[3].y -= CONTACT_Y_4;
   Contact[2].x += CONTACT_X_OUT;
   Contact[2].y -= CONTACT_Y_3;
   Contact[1].x += CONTACT_X_OUT;
   Contact[1].y -= CONTACT_Y_2;
   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_Y_1;
}


void CLogiClockGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiClockGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiClockGate* pClone = new CLogiClockGate(m_position, Name, m_iPage, pDoc, m_iSeconds, m_bSpare);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiClockGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CClockDlg dlg;

   dlg.m_iSeconds = m_iSeconds;
   dlg.m_bSpare = m_bSpare;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iSeconds = dlg.m_iSeconds;
   m_bSpare = dlg.m_bSpare;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiTimerGate

IMPLEMENT_SERIAL(CLogiTimerGate, CLogiGate, 0)

CLogiTimerGate::CLogiTimerGate()
{
}

CLogiTimerGate::CLogiTimerGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, UINT Delay, BOOL Spare) : CLogiGate(position, name, ipage, pdoc, 1, 1, IDB_TIMER, timergate)
{
   m_uDelay = Delay;
   m_bSpare = Spare;

   SetGateID();
   SetContacts();
}

void CLogiTimerGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_uDelay;
      ar << m_bSpare;
   }
   else
   {
      ar >> m_uDelay;
      ar >> m_bSpare;

      SetGateID();
      SetContacts();
   }
}

void CLogiTimerGate::Initialize(CLogiView* pView, UINT iMode)
{
   m_tFire = clock();

   CLogiGate::Initialize(pView, iMode);
}

void CLogiTimerGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   if ((Node[1])->State == HI)
   {
      m_tFire = clock();
   }
   else
   {
      if (clock() > (clock_t) (m_tFire + m_uDelay))
      {
         m_tFire += m_uDelay;

         (Node[0])->NextState = HI;
      }
      else
      {
         (Node[0])->NextState = LO;
      }
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);

   // Timer also must ReQueue itself

   if (EventCycle != pDoc->m_uCycleCount)
   {
      pDoc->EventQueue.AddTail(this);
      EventCycle = pDoc->m_uCycleCount;
   }
}

void CLogiTimerGate::SetGateID(void)
{
   GateID = IDB_TIMER;
}

void CLogiTimerGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_OUT_Y_1_1;
   Contact[1].x += CONTACT_X_IN;
   Contact[1].y -= CONTACT_IN_Y_1_1;
}


void CLogiTimerGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiTimerGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiTimerGate* pClone = new CLogiTimerGate(m_position, Name, m_iPage, pDoc, m_uDelay, m_bSpare);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiTimerGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CTimerDlg dlg;

   dlg.m_uDelay = m_uDelay;
   dlg.m_bSpare = m_bSpare;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_uDelay = dlg.m_uDelay;
   m_bSpare = dlg.m_bSpare;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiLedGate

IMPLEMENT_SERIAL(CLogiLedGate, CLogiGate, 0)

CLogiLedGate::CLogiLedGate()
{
}

CLogiLedGate::CLogiLedGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iLedRed, int iLedBlink) : CLogiGate(position, name, ipage, pdoc, 0, 1, IDB_LED_UNKNOWN, ledgate)
{

   m_iRed = iLedRed;
   m_iBlink = iLedBlink;

   SetGateID();
   SetContacts();

}

void CLogiLedGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iRed;
      ar << m_iBlink;
   }
   else
   {
      ar >> m_iRed;
      ar >> m_iBlink;

      SetGateID();
      SetContacts();
   }

}

void CLogiLedGate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   pView->InvalObj(this);
}

void CLogiLedGate::Initialize(CLogiView* pView, UINT iMode)
{

   // Draw Device in its initialized state (BitMap ID held in GateID)

   SetGateID();

   if ((iMode == ID_SIMULATE_RUN) || (iMode == ID_SIMULATE_STEP))
   {
      GateID = IDB_LED_UNKNOWN;
   }

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiLedGate::Simulate(CLogiDoc* /*pDoc*/)
{

   // Perform Simulation

   if (((Node[0])->State) == HI)
   {
      switch (m_iRed)
      {
      case 0: GateID = IDB_LED_ONR; break;
      case 1: GateID = IDB_LED_ONG; break;
      case 2: GateID = IDB_LED_ONY; break;
      }
   }
   else if (((Node[0])->State) == UNKNOWN)
   {
      GateID = IDB_LED_UNKNOWN;
   }
   else
   {
      GateID = IDB_LED_OFF;
   }
}

void CLogiLedGate::SetGateID(void)
{
   GateID = IDB_LED_OFF;
}

void CLogiLedGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_IN_Y_1_1;
}


void CLogiLedGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiLedGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiLedGate* pClone = new CLogiLedGate(m_position, Name, m_iPage, pDoc, m_iRed, m_iBlink);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiLedGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CLedDlg dlg;

   dlg.m_iRed = m_iRed;
   dlg.m_iBlink = m_iBlink;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iRed = dlg.m_iRed;
   m_iBlink = dlg.m_iBlink;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiSwitchGate

IMPLEMENT_SERIAL(CLogiSwitchGate, CLogiGate, 0)

CLogiSwitchGate::CLogiSwitchGate()
{
}

CLogiSwitchGate::CLogiSwitchGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int SwitchOn, int SwitchToggle) : CLogiGate(position, name, ipage, pdoc, 1, 0, IDB_SWITCH_OFF, switchgate)
{

   m_iOn = SwitchOn;
   m_iToggle = SwitchToggle;

   SetGateID();
   SetContacts();

}

void CLogiSwitchGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iOn;
      ar << m_iToggle;
   }
   else
   {
      ar >> m_iOn;
      ar >> m_iToggle;

      SetGateID();
      SetContacts();
   }

}

void CLogiSwitchGate::Action(CLogiView* pView, BOOL bDown, const CPoint& /*point*/)
{

   // if momentary then

   if (m_iToggle == 1)
   {
      if (bDown)
      {
         if (m_iOn == 0)
         {
            GateID = IDB_SWITCHM_OFF;
         }
         else
         {
            GateID = IDB_SWITCHM_ON;
         }
      }
      else
      {
         if (m_iOn == 0)
         {
            GateID = IDB_SWITCHM_ON;
         }
         else
         {
            GateID = IDB_SWITCHM_OFF;
         }
      }
   }

   // else only do action on button up

   else if (!bDown)
   {
      if (GateID == IDB_SWITCH_OFF)
      {
         GateID = IDB_SWITCH_ON;
      }
      else
      {
         GateID = IDB_SWITCH_OFF;
      }
   }

   // Now schedule our self

   pView->GetDocument()->EventQueue.AddTail(this);
}

void CLogiSwitchGate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   pView->InvalObj(this);
}

void CLogiSwitchGate::Initialize(CLogiView* pView, UINT iMode)
{

   // Draw Device in its initialized state (BitMap ID held in GateID)

   SetGateID();

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiSwitchGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   if ((GateID == IDB_SWITCH_ON) || (GateID == IDB_SWITCHM_ON))
   {
      (Node[0])->NextState = HI;
   }
   else
   {
      (Node[0])->NextState = LO;
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiSwitchGate::SetGateID(void)
{
   if (m_iToggle == 0)
   {
      if (m_iOn == 0)
      {
         GateID = IDB_SWITCH_ON;
      }
      else
      {
         GateID = IDB_SWITCH_OFF;
      }
   }
   else
   {
      if (m_iOn == 0)
      {
         GateID = IDB_SWITCHM_ON;
      }
      else
      {
         GateID = IDB_SWITCHM_OFF;
      }
   }
}

void CLogiSwitchGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_OUT_Y_1_1;

}

void CLogiSwitchGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiSwitchGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiSwitchGate* pClone = new CLogiSwitchGate(m_position, Name, m_iPage, pDoc, m_iOn, m_iToggle);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiSwitchGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CSwitchDlg dlg;

   dlg.m_iOn = m_iOn;
   dlg.m_iToggle = m_iToggle;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iOn = dlg.m_iOn;
   m_iToggle = dlg.m_iToggle;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiSelectGate

IMPLEMENT_SERIAL(CLogiSelectGate, CLogiGate, 0)

CLogiSelectGate::CLogiSelectGate()
{
}

CLogiSelectGate::CLogiSelectGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iInitial, int iDummy) : CLogiGate(position, name, ipage, pdoc, 4, 0, IDB_SELECT_0, selectgate)
{

   m_iInitial = iInitial;
   m_iDummy = iDummy;

   SetGateID();
   SetContacts();

}

void CLogiSelectGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iInitial;
      ar << m_iDummy;
   }
   else
   {
      ar >> m_iInitial;
      ar >> m_iDummy;

      SetGateID();
      SetContacts();
   }

}

void CLogiSelectGate::Action(CLogiView* pView, BOOL bDown, const CPoint& /*point*/)
{

   if (bDown)
   {
      GateID++;

      if (GateID > IDB_SELECT_F) GateID = IDB_SELECT_0;

      // Now schedule our self

      pView->GetDocument()->EventQueue.AddTail(this);
   }
}

void CLogiSelectGate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   pView->InvalObj(this);
}

void CLogiSelectGate::Initialize(CLogiView* pView, UINT iMode)
{

   // Draw Device in its initialized state (BitMap ID held in GateID)

   SetGateID();

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiSelectGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   m_uTemp = GateID - IDB_SELECT_0;

   for (i=0;i<4;i++)
   {
      if (m_uTemp & (1<<i)) (Node[i])->NextState = HI; else (Node[i])->NextState = LO;
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiSelectGate::SetGateID(void)
{
   GateID = IDB_SELECT_0 + m_iInitial;
}

// SetContacts
void CLogiSelectGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_Y_2;
   Contact[1].x += CONTACT_X_OUT;
   Contact[1].y -= CONTACT_Y_3;
   Contact[2].x += CONTACT_X_OUT;
   Contact[2].y -= CONTACT_Y_4;
   Contact[3].x += CONTACT_X_OUT;
   Contact[3].y -= CONTACT_Y_5;

}


void CLogiSelectGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiSelectGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiSelectGate* pClone = new CLogiSelectGate(m_position, Name, m_iPage, pDoc, m_iInitial, m_iDummy);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiSelectGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CSelectDlg dlg;

   dlg.m_iInitial = m_iInitial;
   // dlg.m_iDummy = m_iDummy;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iInitial = dlg.m_iInitial;
   // m_iDummy = dlg.m_iDummy;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiBuzzerGate

IMPLEMENT_SERIAL(CLogiBuzzerGate, CLogiGate, 0)

CLogiBuzzerGate::CLogiBuzzerGate()
{
}

CLogiBuzzerGate::CLogiBuzzerGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iFreq, int iDuration) : CLogiGate(position, name, ipage, pdoc, 0, 1, IDB_BUZZER_OFF, buzzergate)
{

   m_iFreq = iFreq;
   m_iDuration = iDuration;

   SetGateID();
   SetContacts();

}

void CLogiBuzzerGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iFreq;
      ar << m_iDuration;
   }
   else
   {
      ar >> m_iFreq;
      ar >> m_iDuration;

      SetGateID();
      SetContacts();
   }
}

void CLogiBuzzerGate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   pView->InvalObj(this);
}

void CLogiBuzzerGate::Initialize(CLogiView* pView, UINT iMode)
{

   // Draw Device in its initialized state (BitMap ID held in GateID)

   SetGateID();

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiBuzzerGate::Simulate(CLogiDoc* /*pDoc*/)
{
   long frequency;

   OSVERSIONINFO VersionInformation;
   memset(&VersionInformation, 0, sizeof(OSVERSIONINFO));
   VersionInformation.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   // Perform Simulation

   if (((Node[0])->State) == HI)
   {

      frequency = m_iFreq;

      GetVersionEx(&VersionInformation);
      if (VersionInformation.dwPlatformId == VER_PLATFORM_WIN32_NT)
      {
         Beep(frequency, m_iDuration);
      }
      else
      {
         MyBeep(frequency, m_iDuration);
      }

      GateID = IDB_BUZZER_ON;
   }
   else
   {
      GateID = IDB_BUZZER_OFF;
   }
}

void CLogiBuzzerGate::SetGateID(void)
{
   GateID = IDB_BUZZER_OFF;
}

void CLogiBuzzerGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_IN_Y_1_1;

}


void CLogiBuzzerGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiBuzzerGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiBuzzerGate* pClone = new CLogiBuzzerGate(m_position, Name, m_iPage, pDoc, m_iFreq, m_iDuration);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiBuzzerGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CBuzzerDlg dlg;

   dlg.m_iFreq = m_iFreq;
   dlg.m_iDuration = m_iDuration;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iFreq = dlg.m_iFreq;
   m_iDuration = dlg.m_iDuration;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiNULLGate

IMPLEMENT_SERIAL(CLogiNULLGate, CLogiGate, 0)

CLogiNULLGate::CLogiNULLGate()
{
}

CLogiNULLGate::CLogiNULLGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iPass, int iFloat) : CLogiGate(position, name, ipage, pdoc, 1, 1, IDB_NULL, nullgate)
{

   m_iPass = iPass;
   m_iFloat = iFloat;

   SetGateID();
   SetContacts();

}

void CLogiNULLGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iPass;
      ar << m_iFloat;
   }
   else
   {
      ar >> m_iPass;
      ar >> m_iFloat;

      SetGateID();
      SetContacts();
   }
}

void CLogiNULLGate::Simulate(CLogiDoc* /* pDoc */)
{

   // Perform Simulation

   // This Method must exist so that the Base Class is not called
   // for performance reasons. PostSimulate will take care of it

   // Call base class to Queue Events for Driven Devices

   // CLogiGate::Simulate(pDoc);
}

BOOL CLogiNULLGate::PostSimulate(CLogiDoc* pDoc)
{
   int PrevState;
   int PrevDriveState;

   if (Node[0] == m_pDocument->m_pAnodeNULL) return FALSE;

   PrevState = Node[0]->NextState;
   PrevDriveState = Node[0]->NextDriveState;

   if (Node[1]->NextDriveState == DRIVE)
   {
      if (Node[1]->NextState == UNKNOWN)
      {
         switch (m_iPass)
         {
         case 0: Node[0]->NextState = UNKNOWN; break;
         case 1: Node[0]->NextState = HI; break;
         case 2: Node[0]->NextState = LO; break;
         }
      }
      else
      {
         Node[0]->NextState = Node[1]->NextState;
      }

      Node[0]->NextDriveState = DRIVE;
   }
   else
   {
      switch (m_iFloat)
      {
      case 0: Node[0]->NextState = Node[1]->NextState; break;
      case 1: Node[0]->NextState = HI; break;
      case 2: Node[0]->NextState = LO; break;
      }

      Node[0]->NextDriveState = FLOAT;
   }

   if ((PrevState != Node[0]->NextState) || (PrevDriveState != Node[0]->NextDriveState))
   {
      // Call base class to Queue Events for Driven Devices

      Node[0]->State = !Node[0]->NextState; // Force difference to propagate

      CLogiGate::Simulate(pDoc);

      return TRUE;
   }

   return FALSE;
}

void CLogiNULLGate::SetGateID(void)
{
   switch (m_iFloat)
   {
   case 0:
      {
         switch (m_iPass)
         {
         case 0: GateID = IDB_NULL; break;
         case 1: GateID = IDB_NULL_1; break;
         case 2: GateID = IDB_NULL_0; break;
         }
         break;
      }
   case 1:
      {
         switch (m_iPass)
         {
         case 0: GateID = IDB_NULL_PU; break;
         case 1: GateID = IDB_NULL_PU1; break;
         case 2: GateID = IDB_NULL_PU0; break;
         }
         break;
      }
   case 2:
      {
         switch (m_iPass)
         {
         case 0: GateID = IDB_NULL_PD; break;
         case 1: GateID = IDB_NULL_PD1; break;
         case 2: GateID = IDB_NULL_PD0; break;
         }
         break;
      }
   }
}

void CLogiNULLGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[1].x += CONTACT_NULL_X-1;
   Contact[1].y -= CONTACT_NULL_Y;

   Contact[0].x += CONTACT_NULL_X;
   Contact[0].y -= CONTACT_NULL_Y;
}

void CLogiNULLGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiNULLGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiNULLGate* pClone = new CLogiNULLGate(m_position, Name, m_iPage, pDoc, m_iPass, m_iFloat);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiNULLGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CNodeDlg dlg;

   dlg.m_iPass = m_iPass;
   dlg.m_iFloat = m_iFloat;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iPass = dlg.m_iPass;
   m_iFloat = dlg.m_iFloat;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiLed7Gate

IMPLEMENT_SERIAL(CLogiLed7Gate, CLogiGate, 0)

CLogiLed7Gate::CLogiLed7Gate()
{
}

CLogiLed7Gate::CLogiLed7Gate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iLed7Red, int iLed7Inputs) : CLogiGate(position, name, ipage, pdoc, 0, 8, IDB_LED7_OFF, led7gate)
{

   m_iRed = iLed7Red;
   m_iInputs = iLed7Inputs;

   SetGateID();
   SetContacts();

}

void CLogiLed7Gate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iRed;
      ar << m_iInputs;
   }
   else
   {
      ar >> m_iRed;
      ar >> m_iInputs;

      SetGateID();
      SetContacts();
   }
}

void CLogiLed7Gate::Draw(CDC* pDC, CLogiView* pView )
{
   ASSERT_VALID(this);

   if (m_iInputs == 0)
   {
      GateID = IDB_LED7_OFF;
   }

   CLogiGate::Draw(pDC, pView);

   if (m_iInputs == 0)
   {
      m_position.right = m_position.left + m_size.cx;
      m_position.bottom = m_position.top - m_size.cy;
      rect = m_position;

      for (i=0;i<8;i++)
      {
         GateID = GateIDs[i];

         hResource = FindResource(AfxGetInstanceHandle(),MAKEINTRESOURCE(GateID),RT_BITMAP);
         hBitmap = LoadResource(AfxGetInstanceHandle(),hResource);
         pBmi = (BITMAPINFO *) LockResource(hBitmap);

         ::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.bottom, m_size.cx, m_size.cy, 0, 0, m_size.cx, m_size.cy, (void *)(((DWORD) pBmi)+size), pBmi, DIB_RGB_COLORS, SRCPAINT);

#ifdef _DEBUG
         UnlockResource(hBitmap);
         FreeResource(hBitmap);
#endif
      }
   }
}

void CLogiLed7Gate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   pView->InvalObj(this);
}

void CLogiLed7Gate::Initialize(CLogiView* pView, UINT iMode)
{

   // Draw Device in its initialized state (BitMap ID held in GateID)

   SetGateID();

   if (m_iInputs == 1)
   {
      if ((iMode == ID_SIMULATE_RUN) || (iMode == ID_SIMULATE_STEP))
      {
         GateID = IDB_LED4PONU;
      }
   }

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiLed7Gate::Simulate(CLogiDoc* /*pDoc*/)
{

   // Perform Simulation

   if (m_iInputs == 0)
   {
      if (((Node[0])->State) == HI) GateIDs[0] = IDB_LED7_ON0; else GateIDs[0] = IDB_LED7_OF0;
      if (((Node[1])->State) == HI) GateIDs[1] = IDB_LED7_ON1; else GateIDs[1] = IDB_LED7_OF1;
      if (((Node[2])->State) == HI) GateIDs[2] = IDB_LED7_ON2; else GateIDs[2] = IDB_LED7_OF2;
      if (((Node[3])->State) == HI) GateIDs[3] = IDB_LED7_ON3; else GateIDs[3] = IDB_LED7_OF3;
      if (((Node[4])->State) == HI) GateIDs[4] = IDB_LED7_ON4; else GateIDs[4] = IDB_LED7_OF4;
      if (((Node[5])->State) == HI) GateIDs[5] = IDB_LED7_ON5; else GateIDs[5] = IDB_LED7_OF5;
      if (((Node[6])->State) == HI) GateIDs[6] = IDB_LED7_ON6; else GateIDs[6] = IDB_LED7_OF6;
      if (((Node[7])->State) == HI) GateIDs[7] = IDB_LED7_ON7; else GateIDs[7] = IDB_LED7_OF7;
   }
   else
   {
      UINT uTemp = 0;

      for (i=0;i<4;i++)
      {
         switch ((Node[i])->State)
         {
         case HI: uTemp |= 1<<i; break;
         case UNKNOWN: uTemp = 31; break;
         }
      }

      if ((Node[i])->State == HI)
      {
         switch (uTemp)
         {
         case  0: GateID = IDB_LED4PON0; break;
         case  1: GateID = IDB_LED4PON1; break;
         case  2: GateID = IDB_LED4PON2; break;
         case  3: GateID = IDB_LED4PON3; break;
         case  4: GateID = IDB_LED4PON4; break;
         case  5: GateID = IDB_LED4PON5; break;
         case  6: GateID = IDB_LED4PON6; break;
         case  7: GateID = IDB_LED4PON7; break;
         case  8: GateID = IDB_LED4PON8; break;
         case  9: GateID = IDB_LED4PON9; break;
         case 10: GateID = IDB_LED4PONA; break;
         case 11: GateID = IDB_LED4PONB; break;
         case 12: GateID = IDB_LED4PONC; break;
         case 13: GateID = IDB_LED4POND; break;
         case 14: GateID = IDB_LED4PONE; break;
         case 15: GateID = IDB_LED4PONF; break;
         case 31: GateID = IDB_LED4PONU; break;
         }
      }
      else
      {
         switch (uTemp)
         {
         case  0: GateID = IDB_LED4_ON0; break;
         case  1: GateID = IDB_LED4_ON1; break;
         case  2: GateID = IDB_LED4_ON2; break;
         case  3: GateID = IDB_LED4_ON3; break;
         case  4: GateID = IDB_LED4_ON4; break;
         case  5: GateID = IDB_LED4_ON5; break;
         case  6: GateID = IDB_LED4_ON6; break;
         case  7: GateID = IDB_LED4_ON7; break;
         case  8: GateID = IDB_LED4_ON8; break;
         case  9: GateID = IDB_LED4_ON9; break;
         case 10: GateID = IDB_LED4_ONA; break;
         case 11: GateID = IDB_LED4_ONB; break;
         case 12: GateID = IDB_LED4_ONC; break;
         case 13: GateID = IDB_LED4_OND; break;
         case 14: GateID = IDB_LED4_ONE; break;
         case 15: GateID = IDB_LED4_ONF; break;
         case 31: GateID = IDB_LED4_ONU; break;
         }
      }
   }
}

void CLogiLed7Gate::SetGateID(void)
{
   if (m_iInputs == 0)
   {
      GateIDs[0] = IDB_LED7_OF0;
      GateIDs[1] = IDB_LED7_OF1;
      GateIDs[2] = IDB_LED7_OF2;
      GateIDs[3] = IDB_LED7_OF3;
      GateIDs[4] = IDB_LED7_OF4;
      GateIDs[5] = IDB_LED7_OF5;
      GateIDs[6] = IDB_LED7_OF6;
      GateIDs[7] = IDB_LED7_OF7;
      Inputs = 8;
   }
   else
   {
      GateID = IDB_LED4_OFF;
      Inputs = 5;
   }

   Contacts = Outputs + Inputs;

}

void CLogiLed7Gate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   if (m_iInputs == 0)
   {
      Contact[0].x += CONTACT_X_IN;
      Contact[0].y -= CONTACT_Y_2;
      Contact[1].x += CONTACT_X_IN;
      Contact[1].y -= CONTACT_Y_3;
      Contact[2].x += CONTACT_X_IN;
      Contact[2].y -= CONTACT_Y_4;
      Contact[3].x += CONTACT_X_IN;
      Contact[3].y -= CONTACT_Y_5;
      Contact[4].x += CONTACT_X_IN;
      Contact[4].y -= CONTACT_Y_6;
      Contact[5].x += CONTACT_X_IN;
      Contact[5].y -= CONTACT_Y_7;
      Contact[6].x += CONTACT_X_IN;
      Contact[6].y -= CONTACT_Y_8;
      Contact[7].x += CONTACT_X_IN;
      Contact[7].y -= CONTACT_Y_1;
   }
   else
   {
      Contact[0].x += CONTACT_X_IN;
      Contact[0].y -= CONTACT_Y_3;
      Contact[1].x += CONTACT_X_IN;
      Contact[1].y -= CONTACT_Y_4;
      Contact[2].x += CONTACT_X_IN;
      Contact[2].y -= CONTACT_Y_5;
      Contact[3].x += CONTACT_X_IN;
      Contact[3].y -= CONTACT_Y_6;

      Contact[4].x += CONTACT_X_IN;
      Contact[4].y -= CONTACT_Y_1;
   }
}


void CLogiLed7Gate::MoveTo(const CRect& position, CLogiView* pView)
{
   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);
}

CLogiObj* CLogiLed7Gate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiLed7Gate* pClone = new CLogiLed7Gate(m_position, Name, m_iPage, pDoc, m_iRed, m_iInputs);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiLed7Gate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CLed7Dlg dlg;

   dlg.m_iRed = m_iRed;
   dlg.m_iInputs = m_iInputs;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   if (m_iInputs != dlg.m_iInputs)
   {
      for (int i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing number of inputs", "Error", MB_ICONEXCLAMATION);
            return;
         }
      }

      for (/*jal int */  i=0;i<7;i++) Node[i] = m_pDocument->m_pAnodeNULL;
   }

   m_iRed = dlg.m_iRed;
   m_iInputs = dlg.m_iInputs;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiAsciidisplayGate

IMPLEMENT_SERIAL(CLogiAsciidisplayGate, CLogiGate, 0)

CLogiAsciidisplayGate::CLogiAsciidisplayGate()
{
}

CLogiAsciidisplayGate::CLogiAsciidisplayGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc) : CLogiGate(position, name, ipage, pdoc, 0, 10, IDB_DISPLAY, asciidisplaygate)
{

   SetGateID();
   SetContacts();

}

void CLogiAsciidisplayGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      //      ar << m_iCountHI;
      //      ar << m_iCountLO;
   }
   else
   {
      //      ar >> m_iCountHI;
      //      ar >> m_iCountLO;

      SetGateID();
      SetContacts();
   }
}

void CLogiAsciidisplayGate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   pView->InvalObj(this);
}

void CLogiAsciidisplayGate::Draw(CDC* pDC, CLogiView* pView)
{
   ASSERT_VALID(this);

   CLogiGate::Draw(pDC, pView);

   // if printing build a bitmap on the fly for the Text.

   if (pDC->IsPrinting() || m_pDocument->m_iZoom)
   {
      CDC MemDC;

      MemDC.CreateCompatibleDC(NULL);

      pOldFont = MemDC.SelectObject(&m_font);
      pOldPen = MemDC.SelectObject(&m_pDocument->m_cpBlue);
      pOldBrush = MemDC.SelectObject(&m_pDocument->m_cbBlue);
      int oldBkMode = MemDC.SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = MemDC.SetTextColor(RGB(255,255,0));

      CSize csExtent = MemDC.GetTextExtent( "A", 1);

      CPoint cpTemp(1, 1);

      CSize csSize(BITX_SCR, BITY_SCR);

      // create bitmap based on display (MemDC doesn't work?)

      CBitmap cbGate;
      CDC screenDC;
      screenDC.CreateDC("DISPLAY", NULL, NULL, NULL);
      cbGate.CreateCompatibleBitmap(&screenDC, csSize.cx, csSize.cy);
      screenDC.DeleteDC();

      pOldBmp = MemDC.SelectObject(&cbGate);

      // init bitmap with brush

      MemDC.Rectangle(CRect(CPoint(0,0), csSize));

      // draw text

      for (int iRow=0;iRow<8;iRow++)
      {
         MemDC.TextOut(cpTemp.x, cpTemp.y+(iRow*csExtent.cy), (char *) &m_cText[iRow][0], m_iCol[iRow]);
      }

      // draw cursor

      if (m_iCol[m_iRow] == 16)
      {
         MemDC.TextOut(cpTemp.x, cpTemp.y+((m_iRow)*csExtent.cy), "_", 1);
      }
      else
      {
         MemDC.TextOut(cpTemp.x+(m_iCol[m_iRow]*csExtent.cx), cpTemp.y+(m_iRow*csExtent.cy), "_", 1);
      }

      MemDC.SelectObject(pOldBmp);
      MemDC.SelectObject(pOldPen);
      MemDC.SelectObject(pOldBrush);
      MemDC.SetTextColor(oldTextColor);
      MemDC.SetBkMode(oldBkMode);
      MemDC.SelectObject(pOldFont);

      // build a DIB from the bitmap

      m_Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      m_Bmi.bmiHeader.biHeight = csSize.cy;
      m_Bmi.bmiHeader.biWidth = csSize.cx;
      m_Bmi.bmiHeader.biPlanes = 1;
      m_Bmi.bmiHeader.biBitCount = 4;
      m_Bmi.bmiHeader.biCompression = BI_RGB;
      m_Bmi.bmiHeader.biSizeImage = 0;
      m_Bmi.bmiHeader.biXPelsPerMeter = 0;
      m_Bmi.bmiHeader.biYPelsPerMeter = 0;
      m_Bmi.bmiHeader.biClrUsed = 16;
      m_Bmi.bmiHeader.biClrImportant = 16;

      if(!::GetDIBits(MemDC.GetSafeHdc(), (HBITMAP) cbGate.m_hObject, 0, (UINT) m_Bmi.bmiHeader.biHeight, NULL, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS)) return;

      if (m_Bmi.bmiHeader.biSizeImage == 0) return;

      LPBYTE lpImage = (LPBYTE) new char[m_Bmi.bmiHeader.biSizeImage];
      ::GetDIBits(MemDC.GetSafeHdc(), (HBITMAP) cbGate.m_hObject, 0, (UINT) m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS);

      MemDC.DeleteDC();

      // draw it

      ::StretchDIBits(pDC->GetSafeHdc(), m_position.left+17, m_position.bottom+7, csSize.cx, csSize.cy, 0, 0, m_Bmi.bmiHeader.biWidth, m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS, SRCCOPY);

      delete [] lpImage;
   }

   // Else not printing do direct

   else
   {

      pOldFont = pDC->SelectObject(&m_font);
      int oldBkMode = pDC->SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = pDC->SetTextColor(RGB(255,255,0));

      CRect rect = m_position;
      rect.NormalizeRect();

      CSize csExtent = pDC->GetTextExtent( "A", 1);

      CPoint cpTemp = rect.TopLeft() + CSize(18, 8);

      // draw text

      for (int iRow=0;iRow<8;iRow++)
      {
         pDC->TextOut(cpTemp.x, cpTemp.y+(iRow*csExtent.cy), (char *) &m_cText[iRow][0], m_iCol[iRow]);
      }

      // draw cursor

      if (m_iCol[m_iRow] == 16)
      {
         pDC->TextOut(cpTemp.x, cpTemp.y+((m_iRow)*csExtent.cy), "_", 1);
      }
      else
      {
         pDC->TextOut(cpTemp.x+(m_iCol[m_iRow]*csExtent.cx), cpTemp.y+(m_iRow*csExtent.cy), "_", 1);
      }

      pDC->SetTextColor(oldTextColor);
      pDC->SetBkMode(oldBkMode);
      pDC->SelectObject(pOldFont);
   }

}

void CLogiAsciidisplayGate::Initialize(CLogiView* pView, UINT iMode)
{

   SetGateID();

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiAsciidisplayGate::Simulate(CLogiDoc* /*pDoc*/)
{

   // Perform Simulation

   if (Node[9]->State == HI)
   {
      for (i=0;i<8;i++) m_iCol[i] = 0;

      m_iRow = 0;
   }
   else
   {

      if ((Node[8]->State == HI) && (m_iLastState == LO))
      {
         char uTemp = 0;

         for (i=0;i<8;i++)
         {
            switch ((Node[i])->State)
            {
            case HI: uTemp |= 1<<i; break;
            case UNKNOWN: uTemp = 'U'; goto UTOH;
            }
         }

UTOH:

         switch (uTemp)
         {
         case '\015':
            {
               m_iRow++;

               if (m_iRow == 8)
               {
                  for (int i=0;i<7;i++)
                  {
                     m_iCol[i] = m_iCol[i+1];
                     memmove(m_cText[i],m_cText[i+1],m_iCol[i]);
                  }
                  m_iRow = 7;
                  m_iCol[m_iRow] = 0;
               }
               break;
            }
         case '\010':
            {
               if (m_iCol[m_iRow] == 0)
               {
                  m_iRow--;
                  if (m_iRow == -1) m_iRow = 0;
               }
               else
               {
                  m_iCol[m_iRow] = (m_iCol[m_iRow] - 1);
               }
               break;
            }
         default:
            {
               if (m_iCol[m_iRow] == 16)
               {
                  m_cText[m_iRow][0] = uTemp;
                  m_iCol[m_iRow] = 1;
               }
               else
               {
                  m_cText[m_iRow][m_iCol[m_iRow]] = uTemp;
                  m_iCol[m_iRow]++;
               }
               break;
            }
         }
      }
   }

   // capture current state so as to detect an edge

   m_iLastState = Node[8]->State;
}

void CLogiAsciidisplayGate::SetGateID(void)
{
   int iRow;
   int iCol;

   LOGFONT lf;

   memset(&lf,0,sizeof(lf));

   strcpy(lf.lfFaceName,"Terminal");
   lf.lfHeight         = -12;
   lf.lfWidth          = 0;
   lf.lfOrientation    = 0;
   lf.lfWeight         = 400;
   lf.lfItalic         = 0;
   lf.lfUnderline      = 0;
   lf.lfStrikeOut      = 0;
   lf.lfCharSet        = 255;
   lf.lfOutPrecision   = 1;
   lf.lfClipPrecision  = 2;
   lf.lfQuality        = 1;
   lf.lfPitchAndFamily = 49;

   m_font.DeleteObject();
   m_font.CreateFontIndirect(&lf);

   for (iRow=0;iRow<8;iRow++)
   {
      for (iCol=0;iCol<16;iCol++) m_cText[iRow][iCol] = 0;
      m_iCol[iRow] = 0;
   }

   m_iRow = 0;

   GateID = IDB_DISPLAY;
}

void CLogiAsciidisplayGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_Y_3;
   Contact[1].x += CONTACT_X_IN;
   Contact[1].y -= CONTACT_Y_4;
   Contact[2].x += CONTACT_X_IN;
   Contact[2].y -= CONTACT_Y_5;
   Contact[3].x += CONTACT_X_IN;
   Contact[3].y -= CONTACT_Y_6;
   Contact[4].x += CONTACT_X_IN;
   Contact[4].y -= CONTACT_Y_7;
   Contact[5].x += CONTACT_X_IN;
   Contact[5].y -= CONTACT_Y_8;
   Contact[6].x += CONTACT_X_IN;
   Contact[6].y -= CONTACT_Y_9;
   Contact[7].x += CONTACT_X_IN;
   Contact[7].y -= CONTACT_Y_10;

   Contact[8].x += CONTACT_X_IN;
   Contact[8].y -= CONTACT_Y_1;

   Contact[9].x += CONTACT_X_IN;
   Contact[9].y -= CONTACT_Y_12;
}


void CLogiAsciidisplayGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiAsciidisplayGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiAsciidisplayGate* pClone = new CLogiAsciidisplayGate(m_position, Name, m_iPage, pDoc);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiAsciidisplayGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CDisplayDlg dlg;

   //   dlg.m_iOscillatorHi = m_iCountHI;
   //   dlg.m_iOscillatorLo = m_iCountLO;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   //   m_iCountHI = dlg.m_iOscillatorHi;
   //   m_iCountLO = dlg.m_iOscillatorLo;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiAsciikeyboardGate

IMPLEMENT_SERIAL(CLogiAsciikeyboardGate, CLogiGate, 0)

CLogiAsciikeyboardGate::CLogiAsciikeyboardGate()
{
}

CLogiAsciikeyboardGate::CLogiAsciikeyboardGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bAscii) : CLogiGate(position, name, ipage, pdoc, 9, 0, IDB_KEYBOARD_ON, asciikeyboardgate)
{

   m_bAscii = bAscii;

   SetGateID();
   SetContacts();

}

void CLogiAsciikeyboardGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_bAscii;
      //      ar << m_iCountLO;
   }
   else
   {
      ar >> m_bAscii;
      //      ar >> m_iCountLO;

      SetGateID();
      SetContacts();
   }
}

void CLogiAsciikeyboardGate::Message(CLogiView* pView, UINT nChar, BOOL bDown)
{

   if (bDown)
   {
      m_nChar = nChar;
      m_iDown = 1;
   }
   else
   {
      m_iDown = 0;
   }

   // Now schedule our self

   pView->GetDocument()->EventQueue.AddTail(this);
}

void CLogiAsciikeyboardGate::Action(CLogiView* pView, BOOL bDown, const CPoint& /*point*/)
{

   // Perform Action (for selecting Keyboard Only)

   if (!bDown)
   {
      if ((pView->GetDocument()->KeyBoardObj == NULL) || (pView->GetDocument()->KeyBoardObj == this))
      {
         if ((GateID == IDB_KEYBOARD_OFF) && (pView->GetDocument()->KeyBoardObj == NULL))
         {
            GateID = IDB_KEYBOARD_ON;
            pView->GetDocument()->KeyBoardObj = this;
         }
         else
         {
            GateID = IDB_KEYBOARD_OFF;
            pView->GetDocument()->KeyBoardObj = NULL;
         }
      }
      else
      {
         pView->MessageBox("A Keyboard is already Enabled", "Error", MB_ICONEXCLAMATION);
         return;
      }
   }

   // This Action is not simulated but we still need to animate in all views

   POSITION pos;
   CLogiView* pNextView;

   pos = pView->GetDocument()->GetFirstViewPosition();
   while (pos != NULL)
   {
      pNextView = (CLogiView*)pView->GetDocument()->GetNextView(pos);
      Animate(pNextView);
   }
}

void CLogiAsciikeyboardGate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   pView->InvalObj(this);
}

void CLogiAsciikeyboardGate::Initialize(CLogiView* pView, UINT iMode)
{

   // Draw Device in its initialized state (BitMap ID held in GateID)

   m_nChar = 0;
   m_iDown = 0;

   SetGateID();

   if ((iMode == ID_SIMULATE_RUN) || (iMode == ID_SIMULATE_STEP))
   {
      GateID = IDB_KEYBOARD_OFF;
   }

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiAsciikeyboardGate::Simulate(CLogiDoc* pDoc)
{

   int i;

   // Perform Simulation

   for (i=0;i<8;i++)
   {
      if (((1<<i) & m_nChar) != 0)
      {
         Node[i]->NextState = HI;
      }
      else
      {
         Node[i]->NextState = LO;
      }
   }

   if (m_iDown > 0)
   {
      Node[8]->NextState = HI;
   }
   else
   {
      Node[8]->NextState = LO;
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiAsciikeyboardGate::SetGateID(void)
{
   GateID = IDB_KEYBOARD_ON;
}

void CLogiAsciikeyboardGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_Y_3;
   Contact[1].x += CONTACT_X_OUT;
   Contact[1].y -= CONTACT_Y_4;
   Contact[2].x += CONTACT_X_OUT;
   Contact[2].y -= CONTACT_Y_5;
   Contact[3].x += CONTACT_X_OUT;
   Contact[3].y -= CONTACT_Y_6;
   Contact[4].x += CONTACT_X_OUT;
   Contact[4].y -= CONTACT_Y_7;
   Contact[5].x += CONTACT_X_OUT;
   Contact[5].y -= CONTACT_Y_8;
   Contact[6].x += CONTACT_X_OUT;
   Contact[6].y -= CONTACT_Y_9;
   Contact[7].x += CONTACT_X_OUT;
   Contact[7].y -= CONTACT_Y_10;
   Contact[8].x += CONTACT_X_OUT;
   Contact[8].y -= CONTACT_Y_1;

}


void CLogiAsciikeyboardGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiAsciikeyboardGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiAsciikeyboardGate* pClone = new CLogiAsciikeyboardGate(m_position, Name, m_iPage, pDoc, m_bAscii);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiAsciikeyboardGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CKeyboardDlg dlg;

   dlg.m_bAscii = m_bAscii;
   //   dlg.m_iOscillatorLo = m_iCountLO;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_bAscii = dlg.m_bAscii;
   //   m_iCountLO = dlg.m_iOscillatorLo;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiGroundGate

IMPLEMENT_SERIAL(CLogiGroundGate, CLogiGate, 0)

CLogiGroundGate::CLogiGroundGate()
{
}

CLogiGroundGate::CLogiGroundGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc) : CLogiGate(position, name, ipage, pdoc, 1, 0, IDB_GROUND, groundgate)
{

   SetGateID();
   SetContacts();

}

void CLogiGroundGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      //      ar << m_iCountHI;
      //      ar << m_iCountLO;
   }
   else
   {
      //      ar >> m_iCountHI;
      //      ar >> m_iCountLO;

      SetGateID();
      SetContacts();
   }
}

void CLogiGroundGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   (Node[0])->NextState = LO;

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiGroundGate::SetGateID(void)
{
   GateID = IDB_GROUND;
}

void CLogiGroundGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_OUT_Y_1_1;
}


void CLogiGroundGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiGroundGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiGroundGate* pClone = new CLogiGroundGate(m_position, Name, m_iPage, pDoc);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiGroundGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CGroundDlg dlg;

   //   dlg.m_iOscillatorHi = m_iCountHI;
   //   dlg.m_iOscillatorLo = m_iCountLO;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   //   m_iCountHI = dlg.m_iOscillatorHi;
   //   m_iCountLO = dlg.m_iOscillatorLo;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiPlusGate

IMPLEMENT_SERIAL(CLogiPlusGate, CLogiGate, 0)

CLogiPlusGate::CLogiPlusGate()
{
}

CLogiPlusGate::CLogiPlusGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc) : CLogiGate(position, name, ipage, pdoc, 1, 0, IDB_PLUS, plusgate)
{

   SetContacts();

}

void CLogiPlusGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      //      ar << m_iCountHI;
      //      ar << m_iCountLO;
   }
   else
   {
      //      ar >> m_iCountHI;
      //      ar >> m_iCountLO;

      SetGateID();
      SetContacts();
   }
}

void CLogiPlusGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   (Node[0])->NextState = HI;

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiPlusGate::SetGateID(void)
{
   GateID = IDB_PLUS;
}

void CLogiPlusGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_OUT_Y_1_1;
}


void CLogiPlusGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiPlusGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiPlusGate* pClone = new CLogiPlusGate(m_position, Name, m_iPage, pDoc);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiPlusGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CPlusDlg dlg;

   //   dlg.m_iOscillatorHi = m_iCountHI;
   //   dlg.m_iOscillatorLo = m_iCountLO;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   //   m_iCountHI = dlg.m_iOscillatorHi;
   //   m_iCountLO = dlg.m_iOscillatorLo;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiPortinGate

IMPLEMENT_SERIAL(CLogiPortinGate, CLogiGate, 0)

CLogiPortinGate::CLogiPortinGate()
{
}

CLogiPortinGate::CLogiPortinGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, UINT iIoinAddress, UINT iIoinInitial) : CLogiGate(position, name, ipage, pdoc, 8, 1, IDB_IO_IN, portingate)
{

   m_iAddress = iIoinAddress;
   m_iInitial = iIoinInitial;

   SetGateID();
   SetContacts();

}

void CLogiPortinGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iAddress;
      ar << m_iInitial;
   }
   else
   {
      ar >> m_iAddress;
      ar >> m_iInitial;

      SetGateID();
      SetContacts();
   }
}

void CLogiPortinGate::Initialize(CLogiView* pView, UINT iMode)
{
   m_uTemp = 0xFFFF;

   CLogiGate::Initialize(pView, iMode);
}

void CLogiPortinGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   if ((Node[8]->State == HI) && (m_iLastState == LO))
   {
      UINT uTemp;

      uTemp = _inp((unsigned short) m_iAddress);

      for (i=0;i<8;i++)
      {
         if (uTemp & (1<<i)) (Node[i])->NextState = HI; else (Node[i])->NextState = LO;
      }

      // Call base class to Queue Events for Driven Devices

      CLogiGate::Simulate(pDoc);
   }

   // capture current state so as to detect an edge

   m_iLastState = Node[8]->State;
}

void CLogiPortinGate::SetGateID(void)
{
   GateID = IDB_IO_IN;
}

void CLogiPortinGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_Y_3;
   Contact[1].x += CONTACT_X_OUT;
   Contact[1].y -= CONTACT_Y_4;
   Contact[2].x += CONTACT_X_OUT;
   Contact[2].y -= CONTACT_Y_5;
   Contact[3].x += CONTACT_X_OUT;
   Contact[3].y -= CONTACT_Y_6;
   Contact[4].x += CONTACT_X_OUT;
   Contact[4].y -= CONTACT_Y_7;
   Contact[5].x += CONTACT_X_OUT;
   Contact[5].y -= CONTACT_Y_8;
   Contact[6].x += CONTACT_X_OUT;
   Contact[6].y -= CONTACT_Y_9;
   Contact[7].x += CONTACT_X_OUT;
   Contact[7].y -= CONTACT_Y_10;

   Contact[8].x += CONTACT_X_IN;
   Contact[8].y -= CONTACT_Y_1;
}

void CLogiPortinGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiPortinGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiPortinGate* pClone = new CLogiPortinGate(m_position, Name, m_iPage, pDoc, m_iAddress, m_iInitial);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiPortinGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CIoinDlg dlg;

   dlg.m_iAddress = m_iAddress;
   dlg.m_iInitial = m_iInitial;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iAddress = dlg.m_iAddress;
   m_iInitial = dlg.m_iInitial;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiPortoutGate

IMPLEMENT_SERIAL(CLogiPortoutGate, CLogiGate, 0)

CLogiPortoutGate::CLogiPortoutGate()
{
}

CLogiPortoutGate::CLogiPortoutGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, UINT iIooutAddress, UINT iIooutInitial) : CLogiGate(position, name, ipage, pdoc, 0, 9, IDB_IO_OUT, portoutgate)
{

   m_iAddress = iIooutAddress;
   m_iInitial = iIooutInitial;

   SetGateID();
   SetContacts();

}

void CLogiPortoutGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iAddress;
      ar << m_iInitial;
   }
   else
   {
      ar >> m_iAddress;
      ar >> m_iInitial;

      SetGateID();
      SetContacts();
   }
}

void CLogiPortoutGate::Simulate(CLogiDoc* /*pDoc*/)
{

   // Perform Simulation

   if ((Node[8]->State == HI) && (m_iLastState == LO))
   {
      UINT uTemp = 0;

      for (i=0;i<8;i++)
      {
         if ((Node[i])->State == HI) uTemp |= 1<<i;
      }

      _outp((unsigned short) m_iAddress, uTemp);

   }

   // capture current state so as to detect an edge

   m_iLastState = Node[8]->State;

}

void CLogiPortoutGate::SetGateID(void)
{
   GateID = IDB_IO_OUT;
}

void CLogiPortoutGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_Y_3;
   Contact[1].x += CONTACT_X_IN;
   Contact[1].y -= CONTACT_Y_4;
   Contact[2].x += CONTACT_X_IN;
   Contact[2].y -= CONTACT_Y_5;
   Contact[3].x += CONTACT_X_IN;
   Contact[3].y -= CONTACT_Y_6;
   Contact[4].x += CONTACT_X_IN;
   Contact[4].y -= CONTACT_Y_7;
   Contact[5].x += CONTACT_X_IN;
   Contact[5].y -= CONTACT_Y_8;
   Contact[6].x += CONTACT_X_IN;
   Contact[6].y -= CONTACT_Y_9;
   Contact[7].x += CONTACT_X_IN;
   Contact[7].y -= CONTACT_Y_10;

   Contact[8].x += CONTACT_X_IN;
   Contact[8].y -= CONTACT_Y_1;
}


void CLogiPortoutGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiPortoutGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiPortoutGate* pClone = new CLogiPortoutGate(m_position, Name, m_iPage, pDoc, m_iAddress, m_iInitial);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiPortoutGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CIooutDlg dlg;

   dlg.m_iAddress = m_iAddress;
   dlg.m_iInitial = m_iInitial;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iAddress = dlg.m_iAddress;
   m_iInitial = dlg.m_iInitial;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiReadfileGate

IMPLEMENT_SERIAL(CLogiReadfileGate, CLogiGate, 0)

CLogiReadfileGate::CLogiReadfileGate()
{
   m_pFile = NULL;
}

CLogiReadfileGate::CLogiReadfileGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iFormat, const char *pFileName) : CLogiGate(position, name, ipage, pdoc, 9, 2, IDB_FILE_IN, readfilegate)
{

   m_csFileName = pFileName;
   m_iFormat = iFormat;
   m_pFile = NULL;

   SetGateID();
   SetContacts();

}

void CLogiReadfileGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_csFileName;
      ar << m_iFormat;
   }
   else
   {
      ar >> m_csFileName;
      ar >> m_iFormat;

      SetGateID();
      SetContacts();
   }
}

void CLogiReadfileGate::Animate(CLogiView* pView)
{

   pView->InvalObj(this);

}

void CLogiReadfileGate::Initialize(CLogiView* pView, UINT iMode)
{
   if (m_pFile) fclose(m_pFile);
   m_pFile = NULL;

   m_iLastState = UNKNOWN;

   SetGateID();

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiReadfileGate::Simulate(CLogiDoc* pDoc)
{

   unsigned int uTemp;

   // Perform Simulation

   // If reset close file and skip read

   if (Node[9]->State == HI)
   {
      if (m_pFile) fclose(m_pFile);
      m_pFile = NULL;
      GateID = IDB_FILE_IN;
      m_iLastState = UNKNOWN;
   }
   else
   {
      // if rising edge do the read

      if ((Node[10]->State == HI) && (m_iLastState == LO))
      {

         // if not open yet then do so

         if (!m_pFile)
         {
            CString csFullPath;
            CString csPathName = m_pDocument->GetPathName();

            RelativeToFullPath(m_csFileName, csPathName, csFullPath);

            if (m_iFormat == 0)
               m_pFile = fopen(csFullPath, "rb");
            else
               m_pFile = fopen(csFullPath, "r");

            if (!m_pFile)
            {
               ::MessageBox(::GetFocus(), csFullPath, "Could not open File", MB_OK | MB_ICONEXCLAMATION);
               pDoc->Halt();
               //               pDoc->m_bKeepGoing = FALSE;
               return;
            }

         }

         // if read fails then handle it

         int iStatus;

         if (m_iFormat == 0)
         {
            iStatus = fread(&uTemp, 1, 1, m_pFile);
         }
         else
         {
            iStatus = fscanf(m_pFile, "%x\n", &uTemp);
         }

         if (iStatus != 1)
         {

            // if not end of file tell user

            if (!feof(m_pFile))
            {
               CString csFullPath;
               CString csPathName = m_pDocument->GetPathName();

               RelativeToFullPath(m_csFileName, csPathName, csFullPath);

               ::MessageBox(::GetFocus(), csFullPath, "Could not read File", MB_OK | MB_ICONEXCLAMATION);
               pDoc->Halt();
               //               pDoc->m_bKeepGoing = FALSE;
               return;
            }

            // else just signal it

            else
            {
               (Node[0])->NextState = HI;
               GateID = IDB_FILE_IN;

               for (i=1;i<9;i++)
               {
                  (Node[i])->NextState = UNKNOWN;
               }
            }
         }

         // else no error

         else
         {

            // convert the byte to signals

            for (i=0;i<8;i++)
            {
               if (uTemp & (1<<i)) (Node[i+1])->NextState = HI; else (Node[i+1])->NextState = LO;
            }

            (Node[0])->NextState = LO;

            GateID = IDB_FILEO_IN;
         }
      }
      else
      {
         GateID = IDB_FILE_IN;
      }
   }

   // capture current state so as to detect an edge

   m_iLastState = Node[10]->State;

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiReadfileGate::SetGateID(void)
{
   m_pFile = NULL;
   GateID = IDB_FILE_IN;
}

void CLogiReadfileGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_Y_1;

   Contact[1].x += CONTACT_X_OUT;
   Contact[1].y -= CONTACT_Y_3;
   Contact[2].x += CONTACT_X_OUT;
   Contact[2].y -= CONTACT_Y_4;
   Contact[3].x += CONTACT_X_OUT;
   Contact[3].y -= CONTACT_Y_5;
   Contact[4].x += CONTACT_X_OUT;
   Contact[4].y -= CONTACT_Y_6;
   Contact[5].x += CONTACT_X_OUT;
   Contact[5].y -= CONTACT_Y_7;
   Contact[6].x += CONTACT_X_OUT;
   Contact[6].y -= CONTACT_Y_8;
   Contact[7].x += CONTACT_X_OUT;
   Contact[7].y -= CONTACT_Y_9;
   Contact[8].x += CONTACT_X_OUT;
   Contact[8].y -= CONTACT_Y_10;

   Contact[9].x += CONTACT_X_IN;
   Contact[9].y -= CONTACT_Y_5;

   Contact[10].x += CONTACT_X_IN;
   Contact[10].y -= CONTACT_Y_8;
}


void CLogiReadfileGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiReadfileGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiReadfileGate* pClone = new CLogiReadfileGate(m_position, Name, m_iPage, pDoc, m_iFormat, m_csFileName);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiReadfileGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CFileinDlg dlg;

   dlg.m_csFileName = m_csFileName;
   dlg.m_iFormat = m_iFormat;
   dlg.m_csPathName = pView->GetDocument()->GetPathName();

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_csFileName = dlg.m_csFileName;
   m_iFormat = dlg.m_iFormat;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiSignalreceiverGate

IMPLEMENT_SERIAL(CLogiSignalreceiverGate, CLogiGate, 0)

CLogiSignalreceiverGate::CLogiSignalreceiverGate()
{

}

CLogiSignalreceiverGate::CLogiSignalreceiverGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int idummy, const char *psignalname) : CLogiGate(position, name, ipage, pdoc, 1, 0, IDB_PAGE_IN, signalreceivergate)
{

   m_iDummy = idummy;
   m_csSignalName = psignalname;

   SetGateID();
   SetContacts();

}

void CLogiSignalreceiverGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iDummy;
      ar << m_csSignalName;
   }
   else
   {
      ar >> m_iDummy;
      ar >> m_csSignalName;

      SetGateID();
      SetContacts();
   }
}

void CLogiSignalreceiverGate::Draw(CDC* pDC, CLogiView* pView)
{
   ASSERT_VALID(this);

   CLogiGate::Draw(pDC, pView);

   // if printing build a bitmap on the fly for the Text.

   if (pDC->IsPrinting() || m_pDocument->m_iZoom)
   {
      CDC MemDC;

      MemDC.CreateCompatibleDC(NULL);

      pOldFont = MemDC.SelectObject(&m_font);
      pOldPen = MemDC.SelectObject(&m_pDocument->m_cpGrey);
      pOldBrush = MemDC.SelectObject(&m_pDocument->m_cbGrey);
      int oldBkMode = MemDC.SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = MemDC.SetTextColor(RGB(0, 0, 0));

      CSize csSize(BITX_NAM, BITY_NAM);

      // create bitmap based on display (MemDC doesn't work?)

      CBitmap cbGate;
      CDC screenDC;
      screenDC.CreateDC("DISPLAY", NULL, NULL, NULL);
      cbGate.CreateCompatibleBitmap(&screenDC, csSize.cx, csSize.cy);
      screenDC.DeleteDC();

      pOldBmp = MemDC.SelectObject(&cbGate);

      // init bitmap with brush

      MemDC.Rectangle(CRect(CPoint(0,0), csSize));

      // draw text

      MemDC.TextOut(0, 0, m_csSignalName, min(m_csSignalName.GetLength(),6));

      MemDC.SelectObject(pOldBmp);
      MemDC.SelectObject(pOldPen);
      MemDC.SelectObject(pOldBrush);
      MemDC.SetTextColor(oldTextColor);
      MemDC.SetBkMode(oldBkMode);
      MemDC.SelectObject(pOldFont);

      // build a DIB from the bitmap

      m_Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      m_Bmi.bmiHeader.biHeight = csSize.cy;
      m_Bmi.bmiHeader.biWidth = csSize.cx;
      m_Bmi.bmiHeader.biPlanes = 1;
      m_Bmi.bmiHeader.biBitCount = 4;
      m_Bmi.bmiHeader.biCompression = BI_RGB;
      m_Bmi.bmiHeader.biSizeImage = 0;
      m_Bmi.bmiHeader.biXPelsPerMeter = 0;
      m_Bmi.bmiHeader.biYPelsPerMeter = 0;
      m_Bmi.bmiHeader.biClrUsed = 16;
      m_Bmi.bmiHeader.biClrImportant = 16;

      if(!::GetDIBits(MemDC.GetSafeHdc(), (HBITMAP) cbGate.m_hObject, 0, (UINT) m_Bmi.bmiHeader.biHeight, NULL, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS)) return;

      if (m_Bmi.bmiHeader.biSizeImage == 0) return;

      LPBYTE lpImage = (LPBYTE) new char[m_Bmi.bmiHeader.biSizeImage];
      ::GetDIBits(MemDC.GetSafeHdc(), (HBITMAP) cbGate.m_hObject, 0, (UINT) m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS);

      MemDC.DeleteDC();

      // draw it

      ::StretchDIBits(pDC->GetSafeHdc(), m_position.left+9, m_position.bottom+2, csSize.cx, csSize.cy, 0, 0, m_Bmi.bmiHeader.biWidth, m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS, SRCCOPY);

      delete [] lpImage;
   }

   // Else not printing do direct

   else
   {
      pOldFont = pDC->SelectObject(&m_font);
      int oldBkMode = pDC->SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = pDC->SetTextColor(RGB(0, 0, 0));

      CRect rect = m_position;
      rect.NormalizeRect();

      pDC->TextOut(rect.left+9, rect.top+2, m_csSignalName, min(m_csSignalName.GetLength(),6));

      pDC->SetTextColor(oldTextColor);
      pDC->SetBkMode(oldBkMode);
      pDC->SelectObject(pOldFont);
   }

}

void CLogiSignalreceiverGate::Simulate(CLogiDoc* /* pDoc */)
{

   // Perform Simulation

   // This Method must exist so that the Base Class is not called
   // for performance reasons. PostSimulate (of sender) will take
   // care of it

   // Call base class to Queue Events for Driven Devices

   // CLogiGate::Simulate(pDoc);
}

void CLogiSignalreceiverGate::SetGateID(void)
{
   LOGFONT lf;
   memset(&lf,0,sizeof(lf));

   strcpy(lf.lfFaceName,"Courier New");
   lf.lfHeight         = -11;
   lf.lfWidth          = 0;
   lf.lfOrientation    = 0;
   lf.lfWeight         = 400;
   lf.lfItalic         = 0;
   lf.lfUnderline      = 0;
   lf.lfStrikeOut      = 0;
   lf.lfCharSet        = 0;
   lf.lfOutPrecision   = 3;
   lf.lfClipPrecision  = 2;
   lf.lfQuality        = 1;
   lf.lfPitchAndFamily = 49;

   m_font.DeleteObject();
   m_font.CreateFontIndirect(&lf);

   GateID = IDB_PAGE_IN;
}

void CLogiSignalreceiverGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT_SIG;
   Contact[0].y -= CONTACT_Y_2;
}

BOOL CLogiSignalreceiverGate::HasText()
{
   return TRUE;
}

CString CLogiSignalreceiverGate::GetText()
{
   return m_csSignalName;
}

void CLogiSignalreceiverGate::SetText(LPCTSTR text)
{
   m_csSignalName = text;
   Invalidate();
}

void CLogiSignalreceiverGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiSignalreceiverGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiSignalreceiverGate* pClone = new CLogiSignalreceiverGate(m_position, Name, m_iPage, pDoc, m_iDummy, m_csSignalName);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiSignalreceiverGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CSignalreceiverDlg dlg;

   dlg.m_csSignalName = m_csSignalName;
   dlg.m_iDummy = m_iDummy;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_csSignalName = dlg.m_csSignalName;
   m_iDummy = dlg.m_iDummy;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiSignalsenderGate

IMPLEMENT_SERIAL(CLogiSignalsenderGate, CLogiGate, 0)

CLogiSignalsenderGate::CLogiSignalsenderGate()
{
}

CLogiSignalsenderGate::CLogiSignalsenderGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int idummy, const char *psignalname) : CLogiGate(position, name, ipage, pdoc, 0, 1, IDB_PAGE_OUT, signalsendergate)
{
   m_iDummy = idummy;
   m_csSignalName = psignalname;

   SetGateID();
   SetContacts();
}

void CLogiSignalsenderGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iDummy;
      ar << m_csSignalName;
   }
   else
   {
      ar >> m_iDummy;
      ar >> m_csSignalName;

      SetGateID();
      SetContacts();
   }
}

void CLogiSignalsenderGate::Draw(CDC* pDC, CLogiView* pView)
{
   ASSERT_VALID(this);

   CLogiGate::Draw(pDC, pView);

   if (pDC->IsPrinting() || m_pDocument->m_iZoom)
   {
      CDC MemDC;

      MemDC.CreateCompatibleDC(NULL);

      pOldFont = MemDC.SelectObject(&m_font);
      pOldPen = MemDC.SelectObject(&m_pDocument->m_cpGrey);
      pOldBrush = MemDC.SelectObject(&m_pDocument->m_cbGrey);
      int oldBkMode = MemDC.SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = MemDC.SetTextColor(RGB(0, 0, 0));

      CSize csSize(BITX_NAM, BITY_NAM);

      // create bitmap based on display (MemDC doesn't work?)

      CBitmap cbGate;
      CDC screenDC;
      screenDC.CreateDC("DISPLAY", NULL, NULL, NULL);
      cbGate.CreateCompatibleBitmap(&screenDC, csSize.cx, csSize.cy);
      screenDC.DeleteDC();

      pOldBmp = MemDC.SelectObject(&cbGate);

      // init bitmap with brush

      MemDC.Rectangle(CRect(CPoint(0,0), csSize));

      // draw text

      MemDC.TextOut(0, 0, m_csSignalName, min(m_csSignalName.GetLength(),6));

      MemDC.SelectObject(pOldBmp);
      MemDC.SelectObject(pOldPen);
      MemDC.SelectObject(pOldBrush);
      MemDC.SetTextColor(oldTextColor);
      MemDC.SetBkMode(oldBkMode);
      MemDC.SelectObject(pOldFont);

      // build a DIB from the bitmap

      m_Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      m_Bmi.bmiHeader.biHeight = csSize.cy;
      m_Bmi.bmiHeader.biWidth = csSize.cx;
      m_Bmi.bmiHeader.biPlanes = 1;
      m_Bmi.bmiHeader.biBitCount = 4;
      m_Bmi.bmiHeader.biCompression = BI_RGB;
      m_Bmi.bmiHeader.biSizeImage = 0;
      m_Bmi.bmiHeader.biXPelsPerMeter = 0;
      m_Bmi.bmiHeader.biYPelsPerMeter = 0;
      m_Bmi.bmiHeader.biClrUsed = 16;
      m_Bmi.bmiHeader.biClrImportant = 16;

      if(!::GetDIBits(MemDC.GetSafeHdc(), (HBITMAP) cbGate.m_hObject, 0, (UINT) m_Bmi.bmiHeader.biHeight, NULL, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS)) return;

      if (m_Bmi.bmiHeader.biSizeImage == 0) return;

      LPBYTE lpImage = (LPBYTE) new char[m_Bmi.bmiHeader.biSizeImage];
      ::GetDIBits(MemDC.GetSafeHdc(), (HBITMAP) cbGate.m_hObject, 0, (UINT) m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS);

      MemDC.DeleteDC();

      // draw it

      ::StretchDIBits(pDC->GetSafeHdc(), m_position.left+8, m_position.bottom+2, csSize.cx, csSize.cy, 0, 0, m_Bmi.bmiHeader.biWidth, m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS, SRCCOPY);

      delete [] lpImage;
   }

   // Else not printing do direct

   else
   {
      pOldFont = pDC->SelectObject(&m_font);
      int oldBkMode = pDC->SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = pDC->SetTextColor(RGB(0,0,0));

      CRect rect = m_position;
      rect.NormalizeRect();

      pDC->TextOut(rect.left+8, rect.top+2, m_csSignalName, min(m_csSignalName.GetLength(),6));

      pDC->SetTextColor(oldTextColor);
      pDC->SetBkMode(oldBkMode);
      pDC->SelectObject(pOldFont);
   }

}

void CLogiSignalsenderGate::Simulate(CLogiDoc* /* pDoc */)
{

   // Perform Simulation (nothing to do)
   // The simulator will "steal" the state from the node that drives
   // this copy it to the "Mate" of this Sender.
   // The "Mate" will then Queue any Devices it drives.

}

BOOL CLogiSignalsenderGate::PostSimulate(CLogiDoc* pDoc)
{
   POSITION pos;
   BOOL changed = FALSE;

   for (pos = m_Mates.GetHeadPosition(); pos != NULL; )
   {
      CLogiGate *mate = (CLogiGate *) m_Mates.GetNext(pos);

      if (mate->Node[0] != m_pDocument->m_pAnodeNULL)
      {
         if (mate->Node[0]->NextState != Node[0]->NextState || mate->Node[0]->NextDriveState != Node[0]->NextDriveState)
         {
            mate->Node[0]->NextState = Node[0]->NextState;
            mate->Node[0]->NextDriveState = Node[0]->NextDriveState;

            // Call base class to Queue Events for Driven Devices

            mate->Node[0]->State = !mate->Node[0]->NextState; // Force difference to propagate
            mate->Node[0]->DriveState = !mate->Node[0]->NextDriveState; // Force difference to propagate

            mate->CLogiGate::Simulate(pDoc);

            changed = TRUE;
         }
      }
   }

   return changed;
}

void CLogiSignalsenderGate::SetGateID(void)
{

   LOGFONT lf;
   memset(&lf,0,sizeof(lf));

   strcpy(lf.lfFaceName,"Courier New");
   lf.lfHeight         = -11;
   lf.lfWidth          = 0;
   lf.lfOrientation    = 0;
   lf.lfWeight         = 400;
   lf.lfItalic         = 0;
   lf.lfUnderline      = 0;
   lf.lfStrikeOut      = 0;
   lf.lfCharSet        = 0;
   lf.lfOutPrecision   = 3;
   lf.lfClipPrecision  = 2;
   lf.lfQuality        = 1;
   lf.lfPitchAndFamily = 49;

   m_font.DeleteObject();
   m_font.CreateFontIndirect(&lf);

   GateID = IDB_PAGE_OUT;

}

void CLogiSignalsenderGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_Y_2;
}

BOOL CLogiSignalsenderGate::HasText()
{
   return TRUE;
}

CString CLogiSignalsenderGate::GetText()
{
   return m_csSignalName;
}

void CLogiSignalsenderGate::SetText(LPCTSTR text)
{
   m_csSignalName = text;
   Invalidate();
}

void CLogiSignalsenderGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiSignalsenderGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiSignalsenderGate* pClone = new CLogiSignalsenderGate(m_position, Name, m_iPage, pDoc, m_iDummy, m_csSignalName);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiSignalsenderGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CSignalsenderDlg dlg;

   dlg.m_csSignalName = m_csSignalName;
   dlg.m_iDummy = m_iDummy;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_csSignalName = dlg.m_csSignalName;
   m_iDummy = dlg.m_iDummy;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiAnalyzeGate

IMPLEMENT_SERIAL(CLogiAnalyzeGate, CLogiGate, 0)

CLogiAnalyzeGate::CLogiAnalyzeGate()
{
}

CLogiAnalyzeGate::CLogiAnalyzeGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int idummy, const char *psignalname) : CLogiGate(position, name, ipage, pdoc, 0, 1, IDB_ANALYZE, analyzegate)
{

   m_iDummy = idummy;
   m_csSignalName = psignalname;

   SetGateID();
   SetContacts();

}

void CLogiAnalyzeGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iDummy;
      ar << m_csSignalName;
   }
   else
   {
      ar >> m_iDummy;
      ar >> m_csSignalName;

      SetGateID();
      SetContacts();
   }
}

void CLogiAnalyzeGate::Draw(CDC* pDC, CLogiView* pView)
{
   ASSERT_VALID(this);

   CLogiGate::Draw(pDC, pView);

   if (pDC->IsPrinting() || m_pDocument->m_iZoom)
   {
      CDC MemDC;

      MemDC.CreateCompatibleDC(NULL);

      pOldFont = MemDC.SelectObject(&m_font);
      pOldPen = MemDC.SelectObject(&m_pDocument->m_cpGrey);
      pOldBrush = MemDC.SelectObject(&m_pDocument->m_cbGrey);
      int oldBkMode = MemDC.SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = MemDC.SetTextColor(RGB(0, 0, 0));

      CSize csSize(BITX_NAM, BITY_NAM);

      // create bitmap based on display (MemDC doesn't work?)

      CBitmap cbGate;
      CDC screenDC;
      screenDC.CreateDC("DISPLAY", NULL, NULL, NULL);
      cbGate.CreateCompatibleBitmap(&screenDC, csSize.cx, csSize.cy);
      screenDC.DeleteDC();

      pOldBmp = MemDC.SelectObject(&cbGate);

      // init bitmap with brush

      MemDC.Rectangle(CRect(CPoint(0,0), csSize));

      // draw text

      MemDC.TextOut(0, 0, m_csSignalName, min(m_csSignalName.GetLength(),6));

      MemDC.SelectObject(pOldBmp);
      MemDC.SelectObject(pOldPen);
      MemDC.SelectObject(pOldBrush);
      MemDC.SetTextColor(oldTextColor);
      MemDC.SetBkMode(oldBkMode);
      MemDC.SelectObject(pOldFont);

      // build a DIB from the bitmap

      m_Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      m_Bmi.bmiHeader.biHeight = csSize.cy;
      m_Bmi.bmiHeader.biWidth = csSize.cx;
      m_Bmi.bmiHeader.biPlanes = 1;
      m_Bmi.bmiHeader.biBitCount = 4;
      m_Bmi.bmiHeader.biCompression = BI_RGB;
      m_Bmi.bmiHeader.biSizeImage = 0;
      m_Bmi.bmiHeader.biXPelsPerMeter = 0;
      m_Bmi.bmiHeader.biYPelsPerMeter = 0;
      m_Bmi.bmiHeader.biClrUsed = 16;
      m_Bmi.bmiHeader.biClrImportant = 16;

      if(!::GetDIBits(MemDC.GetSafeHdc(), (HBITMAP) cbGate.m_hObject, 0, (UINT) m_Bmi.bmiHeader.biHeight, NULL, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS)) return;

      if (m_Bmi.bmiHeader.biSizeImage == 0) return;

      LPBYTE lpImage = (LPBYTE) new char[m_Bmi.bmiHeader.biSizeImage];
      ::GetDIBits(MemDC.GetSafeHdc(), (HBITMAP) cbGate.m_hObject, 0, (UINT) m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS);

      MemDC.DeleteDC();

      // draw it

      ::StretchDIBits(pDC->GetSafeHdc(), m_position.left+12, m_position.bottom+2, csSize.cx, csSize.cy, 0, 0, m_Bmi.bmiHeader.biWidth, m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS, SRCCOPY);

      delete [] lpImage;
   }

   // Else not printing do direct

   else
   {
      pOldFont = pDC->SelectObject(&m_font);
      int oldBkMode = pDC->SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = pDC->SetTextColor(RGB(0,0,0));

      CRect rect = m_position;
      rect.NormalizeRect();

      pDC->TextOut(rect.left+12, rect.top+2, m_csSignalName, min(m_csSignalName.GetLength(),6));

      pDC->SetTextColor(oldTextColor);
      pDC->SetBkMode(oldBkMode);
      pDC->SelectObject(pOldFont);
   }

}

void CLogiAnalyzeGate::Simulate(CLogiDoc* /* pDoc */)
{
   m_wlHistory.AddTail(((Node[0])->State<<1) | (Node[0])->DriveState);
}

void CLogiAnalyzeGate::SetGateID(void)
{
   LOGFONT lf;
   memset(&lf,0,sizeof(lf));

   strcpy(lf.lfFaceName,"Courier New");
   lf.lfHeight         = -11;
   lf.lfWidth          = 0;
   lf.lfOrientation    = 0;
   lf.lfWeight         = 400;
   lf.lfItalic         = 0;
   lf.lfUnderline      = 0;
   lf.lfStrikeOut      = 0;
   lf.lfCharSet        = 0;
   lf.lfOutPrecision   = 3;
   lf.lfClipPrecision  = 2;
   lf.lfQuality        = 1;
   lf.lfPitchAndFamily = 49;

   m_font.DeleteObject();
   m_font.CreateFontIndirect(&lf);

   GateID = IDB_ANALYZE;

}

void CLogiAnalyzeGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_Y_2;
}

BOOL CLogiAnalyzeGate::HasText()
{
   return TRUE;
}

CString CLogiAnalyzeGate::GetText()
{
   return m_csSignalName;
}

void CLogiAnalyzeGate::SetText(LPCTSTR text)
{
   m_csSignalName = text;
   Invalidate();
}

void CLogiAnalyzeGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiAnalyzeGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiAnalyzeGate* pClone = new CLogiAnalyzeGate(m_position, Name, m_iPage, pDoc, m_iDummy, m_csSignalName);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiAnalyzeGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CAnalyzeDlg dlg;

   dlg.m_csSignalName = m_csSignalName;
   dlg.m_iDummy = m_iDummy;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_csSignalName = dlg.m_csSignalName;
   m_iDummy = dlg.m_iDummy;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiSoundwaveGate

IMPLEMENT_SERIAL(CLogiSoundwaveGate, CLogiGate, 0)

CLogiSoundwaveGate::CLogiSoundwaveGate()
{
}

CLogiSoundwaveGate::CLogiSoundwaveGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bSoundWait, const char *pSoundCommands) : CLogiGate(position, name, ipage, pdoc, 0, 1, IDB_WAV, soundwavegate)
{

   m_csFileName = pSoundCommands;
   m_bWait = bSoundWait;

   SetGateID();
   SetContacts();

}

void CLogiSoundwaveGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_csFileName;
      ar << m_bWait;
   }
   else
   {
      ar >> m_csFileName;
      ar >> m_bWait;

      SetGateID();
      SetContacts();
   }
}

void CLogiSoundwaveGate::Initialize(CLogiView* pView, UINT iMode)
{
   m_iLastState = UNKNOWN;

   CLogiGate::Initialize(pView, iMode);
}

void CLogiSoundwaveGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   if ((Node[0]->State == HI) && (m_iLastState == LO))
   {
      CString csFullPath;
      CString csPathName = m_pDocument->GetPathName();

      RelativeToFullPath(m_csFileName, csPathName, csFullPath);

      if (m_bWait)
      {
         if (!PlaySound(csFullPath, NULL, SND_FILENAME | SND_SYNC))
         {
            ::MessageBox(::GetFocus(), csFullPath, "Error, Can not Play", MB_OK | MB_ICONEXCLAMATION);
            pDoc->Halt();
            return;
         }
      }
      else
      {
         if (!PlaySound(csFullPath, NULL, SND_FILENAME | SND_ASYNC))
         {
            ::MessageBox(::GetFocus(), csFullPath, "Error, Can not Play", MB_OK | MB_ICONEXCLAMATION);
            pDoc->Halt();
            return;
         }
      }
   }

   m_iLastState = Node[0]->State;
}

void CLogiSoundwaveGate::SetGateID(void)
{
   GateID = IDB_WAV;
}

void CLogiSoundwaveGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_IN_Y_1_1;
}


void CLogiSoundwaveGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiSoundwaveGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiSoundwaveGate* pClone = new CLogiSoundwaveGate(m_position, Name, m_iPage, pDoc, m_bWait, m_csFileName);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiSoundwaveGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CSoundDlg dlg;

   dlg.m_csFileName = m_csFileName;
   dlg.m_bWait = m_bWait;
   dlg.m_csPathName = pView->GetDocument()->GetPathName();

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_csFileName = dlg.m_csFileName;
   m_bWait = dlg.m_bWait;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiWritefileGate

IMPLEMENT_SERIAL(CLogiWritefileGate, CLogiGate, 0)

CLogiWritefileGate::CLogiWritefileGate()
{
   m_pFile = NULL;
}

CLogiWritefileGate::CLogiWritefileGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iFormat, const char *pFileName) : CLogiGate(position, name, ipage, pdoc, 0, 9, IDB_FILE_OUT, writefilegate)
{

   m_csFileName = pFileName;
   m_iFormat = iFormat;
   m_pFile = NULL;

   SetGateID();
   SetContacts();

}

void CLogiWritefileGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_csFileName;
      ar << m_iFormat;
   }
   else
   {
      ar >> m_csFileName;
      ar >> m_iFormat;

      SetGateID();
      SetContacts();
   }
}

void CLogiWritefileGate::Animate(CLogiView* pView)
{

   pView->InvalObj(this);

}

void CLogiWritefileGate::Initialize(CLogiView* pView, UINT iMode)
{

   if (m_pFile) fclose(m_pFile);
   m_pFile = NULL;
   m_iLastState = UNKNOWN;

   SetGateID();

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiWritefileGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   if ((Node[8]->State == HI) && (m_iLastState == LO))
   {

      if (!m_pFile)
      {
         CString csFullPath;
         CString csPathName = m_pDocument->GetPathName();

         RelativeToFullPath(m_csFileName, csPathName, csFullPath);

         m_pFile = fopen(csFullPath, "wb");

         if (!m_pFile)
         {
            ::MessageBox(::GetFocus(), csFullPath, "Could not open File", MB_OK | MB_ICONEXCLAMATION);
            pDoc->Halt();
            return;
         }
      }

      UINT uTemp = 0;

      for (i=0;i<8;i++)
      {
         if ((Node[i])->State == HI) uTemp |= 1<<i;
      }

      int iStatus;

      if (m_iFormat == 0)
      {
         iStatus = fwrite(&uTemp, 1, 1, m_pFile);
      }
      else
      {
         iStatus = fprintf(m_pFile,"%02x\r\n",uTemp);
      }

      if (iStatus < 1)
      {
         CString csFullPath;
         CString csPathName = m_pDocument->GetPathName();

         RelativeToFullPath(m_csFileName, csPathName, csFullPath);

         ::MessageBox(::GetFocus(), csFullPath, "Could not write File", MB_OK | MB_ICONEXCLAMATION);
         pDoc->m_bKeepGoing = FALSE;
         return;
      }

      GateID = IDB_FILEO_OUT;
   }
   else
   {
      GateID = IDB_FILE_OUT;
   }

   m_iLastState = Node[8]->State;

}

void CLogiWritefileGate::SetGateID(void)
{
   m_pFile = NULL;
   GateID = IDB_FILE_OUT;
}

void CLogiWritefileGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_Y_3;
   Contact[1].x += CONTACT_X_IN;
   Contact[1].y -= CONTACT_Y_4;
   Contact[2].x += CONTACT_X_IN;
   Contact[2].y -= CONTACT_Y_5;
   Contact[3].x += CONTACT_X_IN;
   Contact[3].y -= CONTACT_Y_6;
   Contact[4].x += CONTACT_X_IN;
   Contact[4].y -= CONTACT_Y_7;
   Contact[5].x += CONTACT_X_IN;
   Contact[5].y -= CONTACT_Y_8;
   Contact[6].x += CONTACT_X_IN;
   Contact[6].y -= CONTACT_Y_9;
   Contact[7].x += CONTACT_X_IN;
   Contact[7].y -= CONTACT_Y_10;

   Contact[8].x += CONTACT_X_IN;
   Contact[8].y -= CONTACT_Y_1;

}


void CLogiWritefileGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiWritefileGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiWritefileGate* pClone = new CLogiWritefileGate(m_position, Name, m_iPage, pDoc, m_iFormat, m_csFileName);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiWritefileGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CFileoutDlg dlg;

   dlg.m_csFileName = m_csFileName;
   dlg.m_iFormat = m_iFormat;
   dlg.m_csPathName = pView->GetDocument()->GetPathName();

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_csFileName = dlg.m_csFileName;
   m_iFormat = dlg.m_iFormat;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiFlipflopGate

IMPLEMENT_SERIAL(CLogiFlipflopGate, CLogiGate, 0)

CLogiFlipflopGate::CLogiFlipflopGate()
{
}

CLogiFlipflopGate::CLogiFlipflopGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iStyle, BOOL bEdge, BOOL bPresetClear) : CLogiGate(position, name, ipage, pdoc, 2, 5, IDB_FF_RS, flipflopgate)
{

   m_iStyle = iStyle;
   m_bEdge  = bEdge;
   m_bPresetClear = bPresetClear;

   SetGateID();
   SetContacts();
   ResizeRect();

}

void CLogiFlipflopGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iStyle;
      ar << m_bEdge;
      ar << m_bPresetClear;
   }
   else
   {
      ar >> m_iStyle;
      ar >> m_bEdge;
      ar >> m_bPresetClear;

      SetGateID();
      SetContacts();
   }
}

void CLogiFlipflopGate::Initialize(CLogiView* pView, UINT iMode)
{
   m_iState = UNKNOWN;
   m_iMasterState = UNKNOWN;
   m_iLastState = UNKNOWN;

   SetGateID();

   CLogiGate::Initialize(pView, iMode);
}

void CLogiFlipflopGate::Simulate(CLogiDoc* pDoc)
{
   // Assume state is unchanged until found otherwise
   int m_iNextState = m_iState; //-1;
   int m_iNextMasterState = m_iMasterState; //-1;
   BOOL bDontKnow = FALSE;

   switch (m_iStyle)
   {
   case 0: // IDB_FF_RS
      {
         switch ((Node[2])->State) // Reset
         {
         case UNKNOWN:
            {
               switch ((Node[3])->State) // Set
               {
               case UNKNOWN: m_iNextState = UNKNOWN; break;
               case HI:      m_iNextState = UNKNOWN; break;
               case LO:      m_iNextState = LO; bDontKnow = TRUE; break;
               }
               break;
            }
         case HI:
            {
               switch ((Node[3])->State)
               {
               case UNKNOWN: m_iNextState = UNKNOWN; break;
               case HI:      m_iNextState = UNKNOWN; break;
               case LO:      m_iNextState = LO;      break;
               }
               break;
            }
         case LO:
            {
               switch ((Node[3])->State)
               {
               case UNKNOWN: m_iNextState = HI; bDontKnow = TRUE; break;
               case HI:      m_iNextState = HI;      break;
               case LO:                              break;
               }
               break;
            }
         }

         break;
      }
   case 1: // IDB_FF_DL
      {
         if (m_bEdge)
         {
            if (m_iLastState != LO) break;
         }

         switch ((Node[2])->State) // Clock
         {
         case UNKNOWN: m_iNextState = (Node[3])->State; bDontKnow = TRUE; break;
         case HI:      m_iNextState = (Node[3])->State; break;
         case LO:                                       break;
         }
         break;
      }
   case 2: // IDB_FF_CRS
      {
         if (m_bEdge)
         {
            if (m_iLastState != LO) break;
         }

         if ((Node[2])->State != LO) // Clock
         {
            if ((Node[2])->State == UNKNOWN) bDontKnow = TRUE;

            switch ((Node[3])->State) // Reset
            {
            case UNKNOWN:
               {
                  switch ((Node[4])->State) // Set
                  {
                  case UNKNOWN: m_iNextState = UNKNOWN; break;
                  case HI:      m_iNextState = UNKNOWN; break;
                  case LO:      m_iNextState = LO; bDontKnow = TRUE; break;
                  }
                  break;
               }
            case HI:
               {
                  switch ((Node[4])->State)
                  {
                  case UNKNOWN: m_iNextState = UNKNOWN; break;
                  case HI:      m_iNextState = UNKNOWN; break;
                  case LO:      m_iNextState = LO;      break;
                  }
                  break;
               }
            case LO:
               {
                  switch ((Node[4])->State)
                  {
                  case UNKNOWN: m_iNextState = HI; bDontKnow = TRUE; break;
                  case HI:      m_iNextState = HI;      break;
                  case LO:                              break;
                  }
                  break;
               }
            }
         }
         break;
      }
   case 3: // IDB_FF_MSRS
      {
         if ((Node[2])->State == UNKNOWN) bDontKnow = TRUE;

         if (m_bEdge)
         {
            if (((Node[2])->State != HI) && (m_iLastState != HI)) break;
         }

         switch ((Node[2])->State) // Clock
         {
         case UNKNOWN:
         case LO:
            {

               switch ((Node[3])->State) // Reset
               {
               case UNKNOWN:
                  {
                     switch ((Node[4])->State) // Set
                     {
                     case UNKNOWN: m_iNextMasterState = UNKNOWN; break;
                     case HI:      m_iNextMasterState = UNKNOWN; break;
                     case LO:      m_iNextMasterState = LO; bDontKnow = TRUE; break;
                     }
                     break;
                  }
               case HI:
                  {
                     switch ((Node[4])->State)
                     {
                     case UNKNOWN: m_iNextMasterState = UNKNOWN; break;
                     case HI:      m_iNextMasterState = UNKNOWN; break;
                     case LO:      m_iNextMasterState = LO;      break;
                     }
                     break;
                  }
               case LO:
                  {
                     switch ((Node[4])->State)
                     {
                     case UNKNOWN: m_iNextMasterState = HI; bDontKnow = TRUE; break;
                     case HI:      m_iNextMasterState = HI;      break;
                     case LO:                                    break;
                     }
                     break;
                  }
               }

               if (m_iNextMasterState != m_iMasterState)
               {
                  if (bDontKnow)
                  {
                     m_iNextMasterState = UNKNOWN;
                  }

                  m_iMasterState = m_iNextMasterState;
               }

               break;
            }
         case HI:
            {
               m_iNextState = m_iMasterState;
               break;
            }
         }
         break;
      }
   case 4: // IDB_FF_MSDL
      {
         if ((Node[2])->State == UNKNOWN) bDontKnow = TRUE;

         if (m_bEdge)
         {
            if (((Node[3])->State != HI) && (m_iLastState != HI)) break;
         }

         switch ((Node[2])->State) // Clock
         {
         case UNKNOWN:
         case LO:
            {
               m_iNextMasterState = (Node[3])->State;

               if (m_iNextMasterState != m_iMasterState)
               {
                  if (bDontKnow)
                  {
                     m_iNextMasterState = UNKNOWN;
                  }

                  m_iMasterState = m_iNextMasterState;
               }

               break;
            }
         case HI:
            {
               m_iNextState = m_iMasterState;
               break;
            }
         }
         break;
      }
   case 5: // IDB_FF_JK
      {
         if ((Node[2])->State == UNKNOWN) bDontKnow = TRUE;

         if (m_bEdge)
         {
            if (((Node[2])->State != HI) && (m_iLastState != HI)) break;
         }

         switch ((Node[2])->State) // Clock
         {
         case UNKNOWN:
         case LO:
            {

               switch ((Node[3])->State) // Reset
               {
               case UNKNOWN:
                  {
                     switch ((Node[4])->State) // Set
                     {
                     case UNKNOWN: m_iNextMasterState = UNKNOWN; break;
                     case HI:      m_iNextMasterState = UNKNOWN; break;
                     case LO:      m_iNextMasterState = LO; bDontKnow = TRUE; break;
                     }
                     break;
                  }
               case HI:
                  {
                     switch ((Node[4])->State)
                     {
                     case UNKNOWN: m_iNextMasterState = UNKNOWN; break;
                     case HI:
                        {
                           switch (m_iMasterState)
                           {
                           case UNKNOWN: m_iNextMasterState = UNKNOWN; break;
                           case HI:      m_iNextMasterState = LO;      break;
                           case LO:      m_iNextMasterState = HI;      break;
                           }
                           break;
                        }
                     case LO:      m_iNextMasterState = LO;      break;
                     }
                     break;
                  }
               case LO:
                  {
                     switch ((Node[4])->State)
                     {
                     case UNKNOWN: m_iNextMasterState = HI; bDontKnow = TRUE; break;
                     case HI:      m_iNextMasterState = HI;      break;
                     case LO:                                    break;
                     }
                     break;
                  }
               }

               if (m_iNextMasterState != m_iMasterState)
               {
                  if (bDontKnow)
                  {
                     m_iNextMasterState = UNKNOWN;
                  }

                  m_iMasterState = m_iNextMasterState;
               }

               break;
            }
         case HI:
            {
               m_iNextState = m_iMasterState;
               break;
            }
         }
         break;
      }
   }

   if (m_iNextState != m_iState)
      if (bDontKnow)
         m_iNextState = UNKNOWN;

   if (m_bPresetClear)
   {
      // Note: The Preset and Clear lines are active LO.

      if ((Node[m_iPresetLine]->State == LO && Node[m_iClearLine]->State == LO) ||
         (Node[m_iPresetLine]->State == UNKNOWN && Node[m_iClearLine]->State == UNKNOWN) ||
         (Node[m_iPresetLine]->State == UNKNOWN && Node[m_iClearLine]->State == LO) ||
         (Node[m_iPresetLine]->State == LO && Node[m_iClearLine]->State == UNKNOWN))
      {
         m_iNextState = UNKNOWN;
         m_iMasterState = UNKNOWN;
      }
      else if (Node[m_iPresetLine]->State == LO)
      {
         ASSERT(Node[m_iClearLine]->State == HI);
         m_iNextState = HI;
         m_iMasterState = HI;
      }
      else if (Node[m_iClearLine]->State == LO)
      {
         ASSERT(Node[m_iPresetLine]->State == HI);
         m_iNextState = LO;
         m_iMasterState = LO;
      }
      else if (Node[m_iPresetLine]->State == UNKNOWN)
      {
         ASSERT(Node[m_iClearLine]->State == HI);
         if (m_iNextState != HI)
            m_iNextState = UNKNOWN;
         if (m_iMasterState != HI)
            m_iMasterState = UNKNOWN;
      }
      else if (Node[m_iClearLine]->State == UNKNOWN)
      {
         ASSERT(Node[m_iPresetLine]->State == HI);
         if (m_iNextState != LO)
            m_iNextState = UNKNOWN;
         if (m_iMasterState != LO)
            m_iMasterState = UNKNOWN;
      }
   }

   if (m_iNextState != m_iState)
   {
      m_iState = m_iNextState;

      switch (m_iState)
      {
      case UNKNOWN:
         {
            (Node[0])->NextState = UNKNOWN;
            (Node[1])->NextState = UNKNOWN;
            break;
         }
      case HI:
         {
            (Node[0])->NextState = LO;
            (Node[1])->NextState = HI;
            break;
         }
      case LO:
         {
            (Node[0])->NextState = HI;
            (Node[1])->NextState = LO;
            break;
         }
      }

      // Call base class to Queue Events for Driven Devices

      CLogiGate::Simulate(pDoc);
   }

   m_iLastState = Node[2]->State;
}

void CLogiFlipflopGate::SetGateID(void)
{
   if (m_bEdge)
   {
      if (m_bPresetClear)
      {
         switch (m_iStyle)
         {
         case 0: GateID = IDB_FF_RS_PC;    break;
         case 1: GateID = IDB_FF_DLE_PC;   break;
         case 2: GateID = IDB_FF_CRSE_PC;  break;
         case 3: GateID = IDB_FF_MSRSE_PC; break;
         case 4: GateID = IDB_FF_MSDLE_PC; break;
         case 5: GateID = IDB_FF_JKE_PC;   break;
         }
      }
      else
      {
         switch (m_iStyle)
         {
         case 0: GateID = IDB_FF_RS;    break;
         case 1: GateID = IDB_FF_DLE;   break;
         case 2: GateID = IDB_FF_CRSE;  break;
         case 3: GateID = IDB_FF_MSRSE; break;
         case 4: GateID = IDB_FF_MSDLE; break;
         case 5: GateID = IDB_FF_JKE;   break;
         }
      }
   }
   else
   {
      if (m_bPresetClear)
      {
         switch (m_iStyle)
         {
         case 0: GateID = IDB_FF_RS_PC;   break;
         case 1: GateID = IDB_FF_DL_PC;   break;
         case 2: GateID = IDB_FF_CRS_PC;  break;
         case 3: GateID = IDB_FF_MSRS_PC; break;
         case 4: GateID = IDB_FF_MSDL_PC; break;
         case 5: GateID = IDB_FF_JK_PC;   break;
         }
      }
      else
      {
         switch (m_iStyle)
         {
         case 0: GateID = IDB_FF_RS;   break;
         case 1: GateID = IDB_FF_DL;   break;
         case 2: GateID = IDB_FF_CRS;  break;
         case 3: GateID = IDB_FF_MSRS; break;
         case 4: GateID = IDB_FF_MSDL; break;
         case 5: GateID = IDB_FF_JK;   break;
         }
      }
   }
}

void CLogiFlipflopGate::SetContacts(void)
{
   int i;

   switch (m_iStyle)
   {
   case 0:
   case 1:
   case 4: Inputs = 2; break;
   case 2:
   case 3:
   case 5: Inputs = 3; break;
   }

   if (m_bPresetClear)
      Inputs += 2;

   Contacts = Outputs + Inputs;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   if (m_bPresetClear)
   {
      switch (m_iStyle)
      {
      case 0:
         {
            Contact[0].x += CONTACT_X_OUT;
            Contact[0].y -= CONTACT_Y_4;
            Contact[1].x += CONTACT_X_OUT;
            Contact[1].y -= CONTACT_Y_9;

            Contact[2].x += CONTACT_X_IN;
            Contact[2].y -= CONTACT_Y_4;
            Contact[3].x += CONTACT_X_IN;
            Contact[3].y -= CONTACT_Y_9;

            m_iClearLine = 4;
            Contact[4].x += CONTACT_X_IN_FFPC;
            Contact[4].y -= CONTACT_Y_1;

            m_iPresetLine = 5;
            Contact[5].x += CONTACT_X_IN_FFPC;
            Contact[5].y -= CONTACT_Y_12;
            break;
         }
      case 1:
      case 4:
         {
            Contact[0].x += CONTACT_X_OUT;
            Contact[0].y -= CONTACT_Y_4;
            Contact[1].x += CONTACT_X_OUT;
            Contact[1].y -= CONTACT_Y_9;

            Contact[2].x += CONTACT_X_IN;
            Contact[2].y -= CONTACT_Y_6;
            Contact[3].x += CONTACT_X_IN;
            Contact[3].y -= CONTACT_Y_9;

            m_iClearLine = 4;
            Contact[4].x += CONTACT_X_IN_FFPC;
            Contact[4].y -= CONTACT_Y_1;

            m_iPresetLine = 5;
            Contact[5].x += CONTACT_X_IN_FFPC;
            Contact[5].y -= CONTACT_Y_12;
            break;
         }
      case 2:
      case 3:
      case 5:
         {
            Contact[0].x += CONTACT_X_OUT;
            Contact[0].y -= CONTACT_Y_4;
            Contact[1].x += CONTACT_X_OUT;
            Contact[1].y -= CONTACT_Y_9;

            Contact[3].x += CONTACT_X_IN;
            Contact[3].y -= CONTACT_Y_4;
            Contact[2].x += CONTACT_X_IN;
            Contact[2].y -= CONTACT_Y_6;
            Contact[4].x += CONTACT_X_IN;
            Contact[4].y -= CONTACT_Y_9;

            m_iClearLine = 5;
            Contact[5].x += CONTACT_X_IN_FFPC;
            Contact[5].y -= CONTACT_Y_1;

            m_iPresetLine = 6;
            Contact[6].x += CONTACT_X_IN_FFPC;
            Contact[6].y -= CONTACT_Y_12;
            break;
         }
      }
   }
   else
   {
      switch (m_iStyle)
      {
      case 0:
         {
            Contact[0].x += CONTACT_X_OUT;
            Contact[0].y -= CONTACT_Y_2;
            Contact[1].x += CONTACT_X_OUT;
            Contact[1].y -= CONTACT_Y_7;

            Contact[2].x += CONTACT_X_IN;
            Contact[2].y -= CONTACT_Y_2;
            Contact[3].x += CONTACT_X_IN;
            Contact[3].y -= CONTACT_Y_7;
            break;
         }
      case 1:
      case 4:
         {
            Contact[0].x += CONTACT_X_OUT;
            Contact[0].y -= CONTACT_Y_2;
            Contact[1].x += CONTACT_X_OUT;
            Contact[1].y -= CONTACT_Y_7;

            Contact[2].x += CONTACT_X_IN;
            Contact[2].y -= CONTACT_Y_4;
            Contact[3].x += CONTACT_X_IN;
            Contact[3].y -= CONTACT_Y_7;
            break;
         }
      case 2:
      case 3:
      case 5:
         {
            Contact[0].x += CONTACT_X_OUT;
            Contact[0].y -= CONTACT_Y_2;
            Contact[1].x += CONTACT_X_OUT;
            Contact[1].y -= CONTACT_Y_7;

            Contact[3].x += CONTACT_X_IN;
            Contact[3].y -= CONTACT_Y_2;
            Contact[2].x += CONTACT_X_IN;
            Contact[2].y -= CONTACT_Y_4;
            Contact[4].x += CONTACT_X_IN;
            Contact[4].y -= CONTACT_Y_7;
            break;
         }
      }
   }
}

void CLogiFlipflopGate::ResizeRect()
{
   if (m_bPresetClear)
      m_size = CSize(BITX_FFPC, BITY_FFPC);
   else
      m_size = CSize(BITX, BITY);

   m_position = CRect(m_position.TopLeft(), CSize(m_size.cx, -m_size.cy));
}

void CLogiFlipflopGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiFlipflopGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiFlipflopGate* pClone = new CLogiFlipflopGate(m_position, Name, m_iPage, pDoc, m_iStyle, m_bEdge, m_bPresetClear);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiFlipflopGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CFlipflopDlg dlg;

   dlg.m_iStyle = m_iStyle;
   dlg.m_bEdge  = m_bEdge;
   dlg.m_bPresetClear = m_bPresetClear;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   if (m_iStyle != dlg.m_iStyle || m_bPresetClear != dlg.m_bPresetClear)
   {
      for (int i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing style", "Error", MB_ICONEXCLAMATION);
            return;
         }
      }

      // Here, 7 is maximum number of contacts
      ASSERT(Contacts <= 7);
      for (/*jal int */  i=0;i<7;i++) Node[i] = m_pDocument->m_pAnodeNULL;
   }

   m_iStyle = dlg.m_iStyle;
   m_bEdge  = dlg.m_bEdge;
   m_bPresetClear = dlg.m_bPresetClear;

   SetGateID();
   SetContacts();
   ASSERT(Contacts <= 7);
   // If this ASSERT fails because more Contacts have been added,
   // you must change the 7 a few lines above also.

   Invalidate(); // erase old rectangle
   ResizeRect();
   Invalidate(); // update new rectangle

   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiKeypadGate

IMPLEMENT_SERIAL(CLogiKeypadGate, CLogiGate, 0)

CLogiKeypadGate::CLogiKeypadGate()
{
}

CLogiKeypadGate::CLogiKeypadGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc) : CLogiGate(position, name, ipage, pdoc, 5, 0, IDB_KEYPAD, keypadgate)
{

   SetGateID();
   SetContacts();

}

void CLogiKeypadGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      //      ar << m_iCountHI;
      //      ar << m_iCountLO;
   }
   else
   {
      //      ar >> m_iCountHI;
      //      ar >> m_iCountLO;

      SetGateID();
      SetContacts();
   }
}

void CLogiKeypadGate::Action(CLogiView* pView, BOOL bDown, const CPoint& point)
{

   // Perform Action

   CRect crButton;
   WORD nKey;

   crButton.SetRect( 6,-89,24,-72); nKey = 0;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(29,-89,47,-72); nKey = 1;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(52,-89,70,-72); nKey = 2;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(75,-89,93,-72); nKey = 3;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect( 6,-67,24,-50); nKey = 4;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(29,-67,47,-50); nKey = 5;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(52,-67,70,-50); nKey = 6;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(75,-67,93,-50); nKey = 7;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect( 6,-45,24,-28); nKey = 8;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(29,-45,47,-28); nKey = 9;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(52,-45,70,-28); nKey = 10;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(75,-45,93,-28); nKey = 11;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect( 6,-23,24, -6); nKey = 12;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(29,-23,47, -6); nKey = 13;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(52,-23,70, -6); nKey = 14;
   if (crButton.PtInRect(point)) goto done;
   crButton.SetRect(75,-23,93, -6); nKey = 15;
   if (crButton.PtInRect(point)) goto done;

   return;

done:

   if (bDown)
   {
      m_nKey = nKey;
      m_bDown = TRUE;
      GateID = IDB_KEYPAD_0 + nKey;
   }
   else
   {
      m_bDown = FALSE;
      GateID = IDB_KEYPAD;
   }

   // Now schedule our self

   pView->GetDocument()->EventQueue.AddTail(this);
}

void CLogiKeypadGate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   pView->InvalObj(this);
}

void CLogiKeypadGate::Initialize(CLogiView* pView, UINT iMode)
{

   // Draw Device in its initialized state (BitMap ID held in GateID)

   m_nKey = 0;
   m_bDown = FALSE;

   SetGateID();

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiKeypadGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   for (i=0;i<4;i++)
   {
      if (((1<<i) & m_nKey) != 0)
      {
         Node[i]->NextState = HI;
      }
      else
      {
         Node[i]->NextState = LO;
      }
   }

   if (m_bDown)
   {
      Node[4]->NextState = HI;
   }
   else
   {
      Node[4]->NextState = LO;
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiKeypadGate::SetGateID(void)
{
   GateID = IDB_KEYPAD;
}

void CLogiKeypadGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT_KP;
   Contact[0].y -= CONTACT_Y_2;

   Contact[1].x += CONTACT_X_OUT_KP;
   Contact[1].y -= CONTACT_Y_3;

   Contact[2].x += CONTACT_X_OUT_KP;
   Contact[2].y -= CONTACT_Y_4;

   Contact[3].x += CONTACT_X_OUT_KP;
   Contact[3].y -= CONTACT_Y_5;

   Contact[4].x += CONTACT_X_OUT_KP;
   Contact[4].y -= CONTACT_Y_7;

}

void CLogiKeypadGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiKeypadGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiKeypadGate* pClone = new CLogiKeypadGate(m_position, Name, m_iPage, pDoc);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiKeypadGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CKeypadDlg dlg;

   //   dlg.m_iOscillatorHi = m_iCountHI;
   //   dlg.m_iOscillatorLo = m_iCountLO;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   //   m_iCountHI = dlg.m_iOscillatorHi;
   //   m_iCountLO = dlg.m_iOscillatorLo;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiCounterGate

IMPLEMENT_SERIAL(CLogiCounterGate, CLogiGate, 0)

CLogiCounterGate::CLogiCounterGate()
{
}

CLogiCounterGate::CLogiCounterGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iSize, UINT iInit) : CLogiGate(position, name, ipage, pdoc, 9, 3, IDB_COUNTER4, countergate)
{

   m_iSize = iSize;
   m_iInit = iInit;

   SetGateID();
   SetContacts();

}

void CLogiCounterGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iSize;
      ar << m_iInit;
   }
   else
   {
      ar >> m_iSize;
      ar >> m_iInit;

      SetGateID();
      SetContacts();
   }
}

void CLogiCounterGate::Initialize(CLogiView* pView, UINT iMode)
{

   m_iLastState = UNKNOWN;
   m_uTemp = m_iInit;

   SetGateID();

   CLogiGate::Initialize(pView, iMode);
}

void CLogiCounterGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   switch (m_iSize)
   {
   case 0:
      {
         Node[4]->NextState = LO;

         if (Node[5]->State == HI)
         {
            m_uTemp = m_iInit;
         }
         else
         {
            if ((Node[7]->State == HI) && (m_iLastState == LO))
            {
               if (Node[6]->State == HI)
               {
                  if (m_uTemp == 0)
                  {
                     Node[4]->NextState = HI;
                     m_uTemp = 15;
                  }
                  else
                  {
                     m_uTemp--;
                  }
               }
               else
               {
                  if (m_uTemp == 15)
                  {
                     Node[4]->NextState = HI;
                     m_uTemp = 0;
                  }
                  else
                  {
                     m_uTemp++;
                  }
               }
            }
         }

         for (i=0;i<4;i++)
         {
            if (m_uTemp & (1<<i)) (Node[i])->NextState = HI; else (Node[i])->NextState = LO;
         }

         m_iLastState = Node[7]->State;

         break;
      }

   case 1:
      {
         Node[8]->NextState = LO;

         if (Node[9]->State == HI)
         {
            m_uTemp = m_iInit;
         }
         else
         {
            if ((Node[11]->State == HI) && (m_iLastState == LO))
            {
               if (Node[10]->State == HI)
               {
                  if (m_uTemp == 0)
                  {
                     Node[8]->NextState = HI;
                     m_uTemp = 255;
                  }
                  else
                  {
                     m_uTemp--;
                  }
               }
               else
               {
                  if (m_uTemp == 255)
                  {
                     Node[8]->NextState = HI;
                     m_uTemp = 0;
                  }
                  else
                  {
                     m_uTemp++;
                  }
               }
            }
         }

         for (i=0;i<8;i++)
         {
            if (m_uTemp & (1<<i)) (Node[i])->NextState = HI; else (Node[i])->NextState = LO;
         }

         m_iLastState = Node[11]->State;

         break;
      }
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiCounterGate::SetGateID(void)
{
   switch (m_iSize)
   {
   case 0:
      {
         Outputs = 5;
         Inputs = 3;

         GateID = IDB_COUNTER4;

         break;
      }
   case 1:
      {
         Outputs = 9;
         Inputs = 3;

         GateID = IDB_COUNTER8;

         break;
      }
   }

   Contacts = Inputs + Outputs;
}

void CLogiCounterGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   switch (m_iSize)
   {
   case 0: // 4Bit
      {
         Contact[7].x += CONTACT_X_IN;  // Clock
         Contact[7].y -= CONTACT_Y_11;

         Contact[6].x += CONTACT_X_IN;  // Down
         Contact[6].y -= CONTACT_Y_4;

         Contact[5].x += CONTACT_X_IN;  // Reset
         Contact[5].y -= CONTACT_Y_2;

         Contact[4].x += CONTACT_X_OUT; // Carry
         Contact[4].y -= CONTACT_Y_11;

         Contact[3].x += CONTACT_X_OUT; // Data
         Contact[3].y -= CONTACT_Y_5;
         Contact[2].x += CONTACT_X_OUT;
         Contact[2].y -= CONTACT_Y_4;
         Contact[1].x += CONTACT_X_OUT;
         Contact[1].y -= CONTACT_Y_3;
         Contact[0].x += CONTACT_X_OUT;
         Contact[0].y -= CONTACT_Y_2;

         break;
      }
   case 1: // 8Bit
      {
         Contact[11].x += CONTACT_X_IN;  // Clock
         Contact[11].y -= CONTACT_Y_11;

         Contact[10].x += CONTACT_X_IN;  // Down
         Contact[10].y -= CONTACT_Y_4;

         Contact[ 9].x += CONTACT_X_IN;  // Reset
         Contact[ 9].y -= CONTACT_Y_2;

         Contact[ 8].x += CONTACT_X_OUT; // Carry
         Contact[ 8].y -= CONTACT_Y_11;

         Contact[ 7].x += CONTACT_X_OUT; // Data
         Contact[ 7].y -= CONTACT_Y_9;
         Contact[ 6].x += CONTACT_X_OUT;
         Contact[ 6].y -= CONTACT_Y_8;
         Contact[ 5].x += CONTACT_X_OUT;
         Contact[ 5].y -= CONTACT_Y_7;
         Contact[ 4].x += CONTACT_X_OUT;
         Contact[ 4].y -= CONTACT_Y_6;
         Contact[ 3].x += CONTACT_X_OUT;
         Contact[ 3].y -= CONTACT_Y_5;
         Contact[ 2].x += CONTACT_X_OUT;
         Contact[ 2].y -= CONTACT_Y_4;
         Contact[ 1].x += CONTACT_X_OUT;
         Contact[ 1].y -= CONTACT_Y_3;
         Contact[ 0].x += CONTACT_X_OUT;
         Contact[ 0].y -= CONTACT_Y_2;

         break;
      }
   }
}


void CLogiCounterGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiCounterGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiCounterGate* pClone = new CLogiCounterGate(m_position, Name, m_iPage, pDoc, m_iSize, m_iInit);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiCounterGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CCounterDlg dlg;

   dlg.m_iSize = m_iSize;
   dlg.m_iInit = m_iInit;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   if (m_iSize != dlg.m_iSize)
   {
      for (int i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing size", "Error", MB_ICONEXCLAMATION);
            return;
         }
      }

      for (/*jal int */  i=0;i<Contacts;i++) Node[i] = m_pDocument->m_pAnodeNULL;
   }

   m_iSize = dlg.m_iSize;
   m_iInit = dlg.m_iInit;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiRandomGate

IMPLEMENT_SERIAL(CLogiRandomGate, CLogiGate, 0)

CLogiRandomGate::CLogiRandomGate()
{
}

CLogiRandomGate::CLogiRandomGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iSpare, unsigned int uSeed) : CLogiGate(position, name, ipage, pdoc, 8, 2, IDB_RANDOM, randomgate)
{

   m_iSpare = iSpare;
   m_uSeed = uSeed;

   SetGateID();
   SetContacts();

}

void CLogiRandomGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iSpare;
      ar << m_uSeed;
   }
   else
   {
      ar >> m_iSpare;
      ar >> m_uSeed;

      SetGateID();
      SetContacts();
   }
}

void CLogiRandomGate::Initialize(CLogiView* pView, UINT iMode)
{

   m_iLastState = UNKNOWN;

   // Init random number generator

   if (m_uSeed == 0)
   {
      m_uSeedLast = (unsigned)timeGetTime();
      srand( m_uSeedLast );
   }
   else
   {
      m_uSeedLast = m_uSeed;
      srand( m_uSeedLast );
   }

   m_uTemp = m_uSeedLast;

   SetGateID();

   CLogiGate::Initialize(pView, iMode);
}

void CLogiRandomGate::Simulate(CLogiDoc* pDoc)
{

   // if reset restore back to seed state

   if (Node[9]->State == HI)
   {
      m_uTemp = m_uSeedLast;
      srand( m_uSeedLast );
   }
   else
   {

      // if triggered then fire

      if ((Node[8]->State == HI) && (m_iLastState == LO))
      {

         // Restore random number generator before using

         srand( m_uTemp );

         m_uTemp = rand();

      }
   }

   for (i=0;i<8;i++)
   {
      if (m_uTemp & (1<<i)) (Node[i])->NextState = HI; else (Node[i])->NextState = LO;
   }

   m_iLastState = Node[8]->State;

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiRandomGate::SetGateID(void)
{
   GateID = IDB_RANDOM;
}

void CLogiRandomGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[8].x += CONTACT_X_IN;
   Contact[8].y -= CONTACT_Y_7;
   Contact[9].x += CONTACT_X_IN;
   Contact[9].y -= CONTACT_Y_2;

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_Y_1;
   Contact[1].x += CONTACT_X_OUT;
   Contact[1].y -= CONTACT_Y_2;
   Contact[2].x += CONTACT_X_OUT;
   Contact[2].y -= CONTACT_Y_3;
   Contact[3].x += CONTACT_X_OUT;
   Contact[3].y -= CONTACT_Y_4;
   Contact[4].x += CONTACT_X_OUT;
   Contact[4].y -= CONTACT_Y_5;
   Contact[5].x += CONTACT_X_OUT;
   Contact[5].y -= CONTACT_Y_6;
   Contact[6].x += CONTACT_X_OUT;
   Contact[6].y -= CONTACT_Y_7;
   Contact[7].x += CONTACT_X_OUT;
   Contact[7].y -= CONTACT_Y_8;

}


void CLogiRandomGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiRandomGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiRandomGate* pClone = new CLogiRandomGate(m_position, Name, m_iPage, pDoc, m_iSpare, m_uSeed);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiRandomGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CRandomDlg dlg;

   dlg.m_iSpare = m_iSpare;
   dlg.m_uSeed = m_uSeed;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iSpare = dlg.m_iSpare;
   m_uSeed = dlg.m_uSeed;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiBreakGate

IMPLEMENT_SERIAL(CLogiBreakGate, CLogiGate, 0)

CLogiBreakGate::CLogiBreakGate()
{
}

CLogiBreakGate::CLogiBreakGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc) : CLogiGate(position, name, ipage, pdoc, 0, 1, IDB_BREAK, breakgate)
{

   SetGateID();
   SetContacts();

}

void CLogiBreakGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      //      ar << m_iCountHI;
      //      ar << m_iCountLO;
   }
   else
   {
      //      ar >> m_iCountHI;
      //      ar >> m_iCountLO;

      SetGateID();
      SetContacts();
   }
}

void CLogiBreakGate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   pView->InvalObj(this);
}

void CLogiBreakGate::Initialize(CLogiView* pView, UINT iMode)
{

   m_iLastState = UNKNOWN;
   m_uTemp = 0;

   SetGateID();

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiBreakGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   // Determine if new bitmap needed

   UINT uNewGateID;

   if (Node[0]->State == HI)
      uNewGateID = IDB_BREAKON;
   else
      uNewGateID = IDB_BREAK;

   // Yes, apply new bitmap

   if (uNewGateID != GateID)
   {
      GateID = uNewGateID;
      Invalidate();
   }

   // If input HI, break gate pauses simulator

   if (Node[0]->State == HI)
   {
      // Determine if any view is displaying this gate
      BOOL bIsShown = FALSE;
      POSITION pos;
      for (pos = pDoc->GetFirstViewPosition(); pos != NULL;)
      {
         CView *view = pDoc->GetNextView(pos);
         if (view->IsKindOf(RUNTIME_CLASS(CLogiView)))
            if (view->IsWindowVisible() && ((CLogiView *)view)->m_iPage == m_iPage)
            {
               bIsShown = TRUE;
               break;
            }
      }

      // If not shown, display in first visible view

      if (!bIsShown)
      {
         pos = pDoc->GetFirstViewPosition();
         for (pos = pDoc->GetFirstViewPosition(); pos != NULL;)
         {
            CView *view = pDoc->GetNextView(pos);
            if (view->IsKindOf(RUNTIME_CLASS(CLogiView)))
               if (view->IsWindowVisible())
               {
                  ((CLogiView *)view)->SetPage(m_iPage);
                  break;
               }
         }
      }

      pDoc->OnSimulatePause();
   }
}

void CLogiBreakGate::SetGateID(void)
{
   GateID = IDB_BREAK;
}

void CLogiBreakGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_IN_Y_1_1;
}

void CLogiBreakGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiBreakGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiBreakGate* pClone = new CLogiBreakGate(m_position, Name, m_iPage, pDoc);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiBreakGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CPauseDlg dlg;

   //   dlg.m_iOscillatorHi = m_iCountHI;
   //   dlg.m_iOscillatorLo = m_iCountLO;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   //   m_iCountHI = dlg.m_iOscillatorHi;
   //   m_iCountLO = dlg.m_iOscillatorLo;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiBitbucketGate

IMPLEMENT_SERIAL(CLogiBitbucketGate, CLogiGate, 0)

CLogiBitbucketGate::CLogiBitbucketGate()
{
}

CLogiBitbucketGate::CLogiBitbucketGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc) : CLogiGate(position, name, ipage, pdoc, 0, 8, IDB_BITBUCKET, bitbucketgate)
{

   SetGateID();
   SetContacts();

}

void CLogiBitbucketGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      //      ar << m_iCountHI;
      //      ar << m_iCountLO;
   }
   else
   {
      //      ar >> m_iCountHI;
      //      ar >> m_iCountLO;

      SetGateID();
      SetContacts();
   }
}

void CLogiBitbucketGate::Initialize(CLogiView* pView, UINT iMode)
{

   m_iLastState = UNKNOWN;
   m_uTemp = 0;

   CLogiGate::Initialize(pView, iMode);
}

void CLogiBitbucketGate::Simulate(CLogiDoc* /*pDoc*/)
{

   // Perform Simulation

   // easy eh?

}

void CLogiBitbucketGate::SetGateID(void)
{
   GateID = IDB_BITBUCKET;
}

void CLogiBitbucketGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[7].x += CONTACT_X_IN;
   Contact[7].y -= CONTACT_Y_8;
   Contact[6].x += CONTACT_X_IN;
   Contact[6].y -= CONTACT_Y_7;
   Contact[5].x += CONTACT_X_IN;
   Contact[5].y -= CONTACT_Y_6;
   Contact[4].x += CONTACT_X_IN;
   Contact[4].y -= CONTACT_Y_5;
   Contact[3].x += CONTACT_X_IN;
   Contact[3].y -= CONTACT_Y_4;
   Contact[2].x += CONTACT_X_IN;
   Contact[2].y -= CONTACT_Y_3;
   Contact[1].x += CONTACT_X_IN;
   Contact[1].y -= CONTACT_Y_2;
   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_Y_1;
}


void CLogiBitbucketGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiBitbucketGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiBitbucketGate* pClone = new CLogiBitbucketGate(m_position, Name, m_iPage, pDoc);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiBitbucketGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CBitBucketDlg dlg;

   //   dlg.m_iOscillatorHi = m_iCountHI;
   //   dlg.m_iOscillatorLo = m_iCountLO;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   //   m_iCountHI = dlg.m_iOscillatorHi;
   //   m_iCountLO = dlg.m_iOscillatorLo;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiNetworkGate

IMPLEMENT_SERIAL(CLogiNetworkGate, CLogiGate, 0)

CLogiNetworkGate::CLogiNetworkGate()
{
}

CLogiNetworkGate::~CLogiNetworkGate()
{
   m_soSocket.ConnectOff();
}

CLogiNetworkGate::CLogiNetworkGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iDirection, UINT uPort, const char *pName) : CLogiGate(position, name, ipage, pdoc, 9, 9, IDB_NETWORK_CALL, networkgate)
{

   m_iDirection = iDirection;
   m_uPort = uPort;
   m_csName = pName;

   SetGateID();
   SetContacts();

}

void CLogiNetworkGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iDirection;
      ar << m_uPort;
      ar << m_csName;
   }
   else
   {
      ar >> m_iDirection;
      ar >> m_uPort;
      ar >> m_csName;

      SetGateID();
      SetContacts();
   }
}

void CLogiNetworkGate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   pView->InvalObj(this);
}

void CLogiNetworkGate::Message(CLogiDoc* pDoc, LPARAM lParam, WPARAM wParam)
{
   m_nChar = (unsigned char) wParam;
   m_nEnable = 1;
   m_lParam = lParam;

   // Now schedule our self

   pDoc->EventQueue.AddTail(this);
}

void CLogiNetworkGate::Initialize(CLogiView* pView, UINT iMode)
{
   //   m_soSocket.SetView(pView);

   m_nCount = 0;

   m_soSocket.ConnectOff();

   SetGateID();

   // Now schedule our self (to establish connection)

   pView->GetDocument()->EventQueue.AddTail(this);

   pView->InvalObj(this);
   CLogiGate::Initialize(pView, iMode);
}

void CLogiNetworkGate::Cleanup(CLogiView* /*pView*/)
{
}

void CLogiNetworkGate::Simulate(CLogiDoc* pDoc)
{

   // if (m_lParam == FD_CLOSE)
   //   {
   //   m_soSocket.ConnectOff();
   //   }

   // if connected display connected ICON

   if (m_soSocket.bConnected)
   {
      GateID = IDB_NETWORK;
   }
   else
   {
      if (m_iDirection == 0) // make call
      {
         GateID = IDB_NETWORK_CALL;
      }
      else
      {
         GateID = IDB_NETWORK_WAIT;
      }
   }

   //   if (m_lParam == FD_CLOSE)
   //      {
   //      return;
   //      }

   // if the network is off fire it up

   if (!m_soSocket.bNetworkOn)
   {
      if (m_iDirection == 0) // make call
      {
         m_soSocket.ConnectOn(m_uPort, m_csName, pDoc, this);
      }
      else
      {
         m_soSocket.ConnectOn(m_uPort, NULL, pDoc, this);
      }
   }

   // Perform Simulation

   if ((Node[9])->State == HI)
   {
      char uTemp = 0;

      for (int i=0;i<8;i++)
      {
         if ((Node[i+10])->State == HI) uTemp |= 1<<i;
      }

      m_soSocket.SendData((char *) &uTemp);
   }

   // if called by Message then process outputs

   if (m_nEnable == 1)
   {

      // if lParam is FD_READ then this was a network character to process

      if (m_lParam == FD_READ)
      {
         for (int i=0;i<8;i++)
         {
            if (((1<<i) & m_nChar) != 0)
            {
               Node[i+1]->NextState = HI;
            }
            else
            {
               Node[i+1]->NextState = LO;
            }
         }

         Node[0]->NextState = HI;
      }

      // else bring Node[0] back down

      else
      {
         Node[0]->NextState = LO;
      }

      // assume disable next time around

      m_nEnable = 0;

   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

void CLogiNetworkGate::SetGateID(void)
{
   if (m_iDirection == 0) // make call
   {
      GateID = IDB_NETWORK_CALL;
   }
   else
   {
      GateID = IDB_NETWORK_WAIT;
   }
}

void CLogiNetworkGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_OUT;
   Contact[0].y -= CONTACT_Y_1;

   Contact[1].x += CONTACT_X_OUT;
   Contact[1].y -= CONTACT_Y_3;
   Contact[2].x += CONTACT_X_OUT;
   Contact[2].y -= CONTACT_Y_4;
   Contact[3].x += CONTACT_X_OUT;
   Contact[3].y -= CONTACT_Y_5;
   Contact[4].x += CONTACT_X_OUT;
   Contact[4].y -= CONTACT_Y_6;
   Contact[5].x += CONTACT_X_OUT;
   Contact[5].y -= CONTACT_Y_7;
   Contact[6].x += CONTACT_X_OUT;
   Contact[6].y -= CONTACT_Y_8;
   Contact[7].x += CONTACT_X_OUT;
   Contact[7].y -= CONTACT_Y_9;
   Contact[8].x += CONTACT_X_OUT;
   Contact[8].y -= CONTACT_Y_10;

   Contact[9].x += CONTACT_X_IN;
   Contact[9].y -= CONTACT_Y_1;

   Contact[10].x += CONTACT_X_IN;
   Contact[10].y -= CONTACT_Y_3;
   Contact[11].x += CONTACT_X_IN;
   Contact[11].y -= CONTACT_Y_4;
   Contact[12].x += CONTACT_X_IN;
   Contact[12].y -= CONTACT_Y_5;
   Contact[13].x += CONTACT_X_IN;
   Contact[13].y -= CONTACT_Y_6;
   Contact[14].x += CONTACT_X_IN;
   Contact[14].y -= CONTACT_Y_7;
   Contact[15].x += CONTACT_X_IN;
   Contact[15].y -= CONTACT_Y_8;
   Contact[16].x += CONTACT_X_IN;
   Contact[16].y -= CONTACT_Y_9;
   Contact[17].x += CONTACT_X_IN;
   Contact[17].y -= CONTACT_Y_10;

}


void CLogiNetworkGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiNetworkGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiNetworkGate* pClone = new CLogiNetworkGate(m_position, Name, m_iPage, pDoc, m_iDirection, m_uPort, m_csName);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiNetworkGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CNetworkDlg dlg;

   dlg.m_iDirection = m_iDirection;
   dlg.m_uPort = m_uPort;
   dlg.m_csName = m_csName;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_iDirection = dlg.m_iDirection;
   m_uPort = dlg.m_uPort;
   m_csName = dlg.m_csName;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiMemoryGate

IMPLEMENT_SERIAL(CLogiMemoryGate, CLogiGate, 0)

CLogiMemoryGate::CLogiMemoryGate()
{
}

CLogiMemoryGate::CLogiMemoryGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iFormat, const char *pFileName) : CLogiGate(position, name, ipage, pdoc, 8, 25, IDB_MEMORY, memorygate)
{
   // m_iFormat flags:
   //  Bit 0: (0) ASCII hex (1) binary
   //  Bit 1: (0) 8-bit address (1) 16-bit address
   // This format gives backwards compatibility for 8-bit.

   m_iFormat = iFormat;
   m_csFileName = pFileName;

   SetGateID();
   SetContacts();

}

void CLogiMemoryGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_csFileName;
      ar << m_iFormat;
   }
   else
   {
      ar >> m_csFileName;
      ar >> m_iFormat;

      SetGateID();
      SetContacts();
   }
}

void CLogiMemoryGate::Initialize(CLogiView* pView, UINT iMode)
{
   int i;
   FILE *pFile;
   unsigned int uTemp = 0;
   int iStatus;
   char szBuffer[81];

   if ((iMode == ID_SIMULATE_RUN) || (iMode == ID_SIMULATE_STEP))
   {
      m_cMemory.SetSize(m_iMemorySize);

      for (i=0;i<m_iMemorySize;i++) m_cMemory[i] = 0xAAAA;

      if (m_csFileName != "\\NUL")
      {
         CString csFullPath;
         CString csPathName = m_pDocument->GetPathName();

         RelativeToFullPath(m_csFileName, csPathName, csFullPath);

         if ((m_iFormat & 1) == 0)
            pFile = fopen(csFullPath, "rb");
         else
            pFile = fopen(csFullPath, "r");

         if (pFile == NULL)
         {
            ::MessageBox(::GetFocus(), csFullPath, "Could not open File", MB_OK | MB_ICONEXCLAMATION);
            m_pDocument->Halt();
            //            m_pDocument->m_bKeepGoing = FALSE;
            m_cMemory.RemoveAll();
            m_cMemory.FreeExtra();
            return;
         }

         // This must be set to loop 1 extra time, to
         // check for too much data. Hence the <= operator.

         for (i=0;i<=m_iMemorySize;i++)
         {
            if ((m_iFormat & 1) == 0) // binary
            {
               iStatus = fread(&uTemp, 1, 1, pFile);
            }
            else // hexadecimal
            {
               if (fgets(szBuffer, 80, pFile))
               {
                  iStatus = sscanf(szBuffer, "%x", &uTemp);
               }
               else
               {
                  iStatus = 0;
               }
            }

            if (iStatus != 1)
            {
               // if not end of file tell user

               if (!feof(pFile))
               {
                  ::MessageBox(::GetFocus(), csFullPath, "Could not read File", MB_OK | MB_ICONEXCLAMATION);
                  m_pDocument->Halt();
                  //            m_pDocument->m_bKeepGoing = FALSE;
                  fclose(pFile);
                  m_cMemory.RemoveAll();
                  m_cMemory.FreeExtra();
                  return;
               }

               break;
            }

            if (i==m_iMemorySize)
            {
               pView->MessageBox("Memory Device full, ignoring excess data", "Warning");
               break;
            }

            m_cMemory[i] = 0;
            for (int j=0;j<8;j++)
            {
               if (uTemp & (1<<j)) m_cMemory[i] |= 1<<(j*2);
            }
         }

         fclose(pFile);
      }
   }
   else // simulation RESET
   {
      m_cMemory.RemoveAll();
      m_cMemory.FreeExtra();
   }

   SetGateID();

   CLogiGate::Initialize(pView, iMode);
}

void CLogiMemoryGate::Simulate(CLogiDoc* pDoc)
{
   unsigned int uTemp; // don't declare this short, VC++ 6 optimizer bug
   unsigned int uAddr;
   int i;

   // Perform Simulation

   uAddr = 0;

   // Get Address

   for (i=0;i<m_iAddressBits;i++)
   {
      switch ((Node[i+8])->State)
      {
      case HI: uAddr |= 1<<i; break;
         // Note that this dummy value MUST be bigger than 16 bits
         // so that it is not a valid 16-bit address.
      case UNKNOWN: uAddr = 0xFFFFFFFF; break;
      }
   }

   // if Write to memory

   if ((Node[m_iWriteNodeNumber])->State == HI)
   {
      uTemp = 0;

      for (i=0;i<8;i++)
      {
         // The data input nodes follow the WriteNode

         switch ((Node[m_iWriteNodeNumber + 1 + i])->State)
         {
         case HI:      uTemp |= HI<<(i*2); break;
         case UNKNOWN: uTemp |= UNKNOWN<<(i*2); break;
         }
      }

      if (uAddr == 0xFFFFFFFF)
      {
         for (i=0;i<m_iMemorySize;i++) m_cMemory[i] = 0xAAAA;
      }
      else
      {
         m_cMemory[uAddr] = (unsigned short) uTemp;
      }
   }

   // assume read

   else
   {
      if (uAddr == 0xFFFFFFFF)
      {
         uTemp = 0xAAAA;
      }
      else
      {
         uTemp = m_cMemory[uAddr];
      }

      for (i=0;i<8;i++)
      {
         (Node[i])->NextState = ((uTemp>>(i*2)) & 3);
      }

      // Call base class to Queue Events for Driven Devices

      CLogiGate::Simulate(pDoc);
   }

}

void CLogiMemoryGate::ResizeRect()
{
   if (m_iAddressBits == 16)
      m_size = CSize(BITX_MEM16, BITY_MEM16);
   else // m_iAddressBits == 8
      m_size = CSize(BITX_MEM, BITY_MEM);

   m_position = CRect(m_position.TopLeft(), CSize(m_size.cx, -m_size.cy));
}

void CLogiMemoryGate::SetGateID(void)
{
   if (m_iFormat & 2)
   {
      m_iAddressBits = 16;
      m_iMemorySize = 65536;
      m_iWriteNodeNumber = 24; // pos of "W" input
      Inputs = 25;
      GateID = IDB_MEMORY16;
   }
   else
   {
      m_iAddressBits = 8;
      m_iMemorySize = 256;
      m_iWriteNodeNumber = 16; // pos of "W" input
      Inputs = 17;
      GateID = IDB_MEMORY;
   }

   Contacts = Inputs + Outputs;
}

void CLogiMemoryGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   if (m_iAddressBits == 8)
   {
      Contact[ 0].x += CONTACT_X_OUT;
      Contact[ 0].y -= CONTACT_Y_12;
      Contact[ 1].x += CONTACT_X_OUT;
      Contact[ 1].y -= CONTACT_Y_13;
      Contact[ 2].x += CONTACT_X_OUT;
      Contact[ 2].y -= CONTACT_Y_14;
      Contact[ 3].x += CONTACT_X_OUT;
      Contact[ 3].y -= CONTACT_Y_15;
      Contact[ 4].x += CONTACT_X_OUT;
      Contact[ 4].y -= CONTACT_Y_16;
      Contact[ 5].x += CONTACT_X_OUT;
      Contact[ 5].y -= CONTACT_Y_17;
      Contact[ 6].x += CONTACT_X_OUT;
      Contact[ 6].y -= CONTACT_Y_18;
      Contact[ 7].x += CONTACT_X_OUT;
      Contact[ 7].y -= CONTACT_Y_19;
   }
   else // m_iAddressBits == 16
   {
      Contact[ 0].x += CONTACT_X_OUT;
      Contact[ 0].y -= CONTACT_Y_20;
      Contact[ 1].x += CONTACT_X_OUT;
      Contact[ 1].y -= CONTACT_Y_21;
      Contact[ 2].x += CONTACT_X_OUT;
      Contact[ 2].y -= CONTACT_Y_22;
      Contact[ 3].x += CONTACT_X_OUT;
      Contact[ 3].y -= CONTACT_Y_23;
      Contact[ 4].x += CONTACT_X_OUT;
      Contact[ 4].y -= CONTACT_Y_24;
      Contact[ 5].x += CONTACT_X_OUT;
      Contact[ 5].y -= CONTACT_Y_25;
      Contact[ 6].x += CONTACT_X_OUT;
      Contact[ 6].y -= CONTACT_Y_26;
      Contact[ 7].x += CONTACT_X_OUT;
      Contact[ 7].y -= CONTACT_Y_27;
   }

   Contact[ 8].x += CONTACT_X_IN;
   Contact[ 8].y -= CONTACT_Y_1;
   Contact[ 9].x += CONTACT_X_IN;
   Contact[ 9].y -= CONTACT_Y_2;
   Contact[10].x += CONTACT_X_IN;
   Contact[10].y -= CONTACT_Y_3;
   Contact[11].x += CONTACT_X_IN;
   Contact[11].y -= CONTACT_Y_4;
   Contact[12].x += CONTACT_X_IN;
   Contact[12].y -= CONTACT_Y_5;
   Contact[13].x += CONTACT_X_IN;
   Contact[13].y -= CONTACT_Y_6;
   Contact[14].x += CONTACT_X_IN;
   Contact[14].y -= CONTACT_Y_7;
   Contact[15].x += CONTACT_X_IN;
   Contact[15].y -= CONTACT_Y_8;

   if (m_iAddressBits == 8)
   {
      Contact[16].x += CONTACT_X_IN;
      Contact[16].y -= CONTACT_Y_10;

      Contact[17].x += CONTACT_X_IN;
      Contact[17].y -= CONTACT_Y_12;
      Contact[18].x += CONTACT_X_IN;
      Contact[18].y -= CONTACT_Y_13;
      Contact[19].x += CONTACT_X_IN;
      Contact[19].y -= CONTACT_Y_14;
      Contact[20].x += CONTACT_X_IN;
      Contact[20].y -= CONTACT_Y_15;
      Contact[21].x += CONTACT_X_IN;
      Contact[21].y -= CONTACT_Y_16;
      Contact[22].x += CONTACT_X_IN;
      Contact[22].y -= CONTACT_Y_17;
      Contact[23].x += CONTACT_X_IN;
      Contact[23].y -= CONTACT_Y_18;
      Contact[24].x += CONTACT_X_IN;
      Contact[24].y -= CONTACT_Y_19;

   }
   else // m_iAddressBits == 16
   {
      Contact[16].x += CONTACT_X_IN;
      Contact[16].y -= CONTACT_Y_9;
      Contact[17].x += CONTACT_X_IN;
      Contact[17].y -= CONTACT_Y_10;
      Contact[18].x += CONTACT_X_IN;
      Contact[18].y -= CONTACT_Y_11;
      Contact[19].x += CONTACT_X_IN;
      Contact[19].y -= CONTACT_Y_12;
      Contact[20].x += CONTACT_X_IN;
      Contact[20].y -= CONTACT_Y_13;
      Contact[21].x += CONTACT_X_IN;
      Contact[21].y -= CONTACT_Y_14;
      Contact[22].x += CONTACT_X_IN;
      Contact[22].y -= CONTACT_Y_15;
      Contact[23].x += CONTACT_X_IN;
      Contact[23].y -= CONTACT_Y_16;

      Contact[24].x += CONTACT_X_IN;
      Contact[24].y -= CONTACT_Y_18;

      Contact[25].x += CONTACT_X_IN;
      Contact[25].y -= CONTACT_Y_20;
      Contact[26].x += CONTACT_X_IN;
      Contact[26].y -= CONTACT_Y_21;
      Contact[27].x += CONTACT_X_IN;
      Contact[27].y -= CONTACT_Y_22;
      Contact[28].x += CONTACT_X_IN;
      Contact[28].y -= CONTACT_Y_23;
      Contact[29].x += CONTACT_X_IN;
      Contact[29].y -= CONTACT_Y_24;
      Contact[30].x += CONTACT_X_IN;
      Contact[30].y -= CONTACT_Y_25;
      Contact[31].x += CONTACT_X_IN;
      Contact[31].y -= CONTACT_Y_26;
      Contact[32].x += CONTACT_X_IN;
      Contact[32].y -= CONTACT_Y_27;
   }

}


void CLogiMemoryGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiMemoryGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiMemoryGate* pClone = new CLogiMemoryGate(m_position, Name, m_iPage, pDoc, m_iFormat, m_csFileName);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiMemoryGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CMemoryDlg dlg;

   dlg.m_csFileName = m_csFileName;
   dlg.m_iBinaryMode = m_iFormat & 1;
   dlg.m_iAddressMode = (m_iFormat & 2) >> 1;
   dlg.m_csPathName = pView->GetDocument()->GetPathName();

   if (dlg.DoModal() != IDOK) return;

   int iNewAddressBits = dlg.m_iAddressMode ? 16 : 8;

   if (m_iAddressBits != iNewAddressBits)
   {
      for (int i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing number of inputs", "Error", MB_ICONEXCLAMATION);
            return;
         }
      }

      // The + 9 is due to the "W" (write) input and 8-bit data input

      for (/*jal int */  i=Outputs;i<Outputs + iNewAddressBits + 9;i++) 
      {
         Node[Outputs] = m_pDocument->m_pAnodeNULL;
      }
   }

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_csFileName = dlg.m_csFileName;
   m_iFormat = dlg.m_iBinaryMode | (dlg.m_iAddressMode << 1);

   SetGateID();

   Invalidate(); // erase old rectangle
   ResizeRect();
   Invalidate(); // update new rectangle

   SetContacts();

   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiTapedriveGate

IMPLEMENT_SERIAL(CLogiTapedriveGate, CLogiGate, 0)

CLogiTapedriveGate::CLogiTapedriveGate()
{
}

CLogiTapedriveGate::CLogiTapedriveGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iFormat, int iSize, int iStart, const char *pFileName) : CLogiGate(position, name, ipage, pdoc, 9, 13, IDB_TAPEDRIVE, tapedrivegate)
{

   m_iFormat = iFormat;
   m_csFileName = pFileName;
   m_iSize = iSize;
   m_iStartPosition = iStart;

   SetGateID();
   SetContacts();

}

void CLogiTapedriveGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_csFileName;
      ar << m_iFormat;
      ar << m_iSize;
      ar << m_iStartPosition;
   }
   else
   {
      ar >> m_csFileName;
      ar >> m_iFormat;
      ar >> m_iSize;
      ar >> m_iStartPosition;

      SetGateID();
      SetContacts();
   }
}

void CLogiTapedriveGate::Initialize(CLogiView* pView, UINT iMode)
{
   int i;
   FILE *pFile;
   unsigned int uTemp = 0;
   int iStatus;
   char szBuffer[81];

   if ((iMode == ID_SIMULATE_RUN) || (iMode == ID_SIMULATE_STEP))
   {

      for (i=0;i<m_iSize;i++) m_cMemory[i] = 0xAAAA;
      m_iPosition = m_iStartPosition;

      if (m_csFileName != "\\NUL")
      {
         CString csFullPath;
         CString csPathName = m_pDocument->GetPathName();

         RelativeToFullPath(m_csFileName, csPathName, csFullPath);

         if (m_iFormat == 0)
            pFile = fopen(csFullPath, "rb");
         else
            pFile = fopen(csFullPath, "r");

         if (pFile == NULL)
         {
            ::MessageBox(::GetFocus(), csFullPath, "Could not open File", MB_OK | MB_ICONEXCLAMATION);
            pView->GetDocument()->Halt();
            return;
         }

         for (i=0;i<m_iSize+1;i++)
         {
            if (m_iFormat == 0)
            {
               iStatus = fread(&uTemp, 1, 1, pFile);
            }
            else
            {
               if (fgets(szBuffer, 80, pFile))
               {
                  iStatus = sscanf(szBuffer, "%x", &uTemp);
               }
               else
               {
                  iStatus = 0;
               }
            }

            if (iStatus != 1)
            {
               // if not end of file tell user

               if (!feof(pFile))
               {
                  ::MessageBox(::GetFocus(), csFullPath, "Could not read File", MB_OK | MB_ICONEXCLAMATION);
                  m_pDocument->Halt();
                  //            m_pDocument->m_bKeepGoing = FALSE;
                  fclose(pFile);
                  pFile = NULL;
                  return;
               }

               break;
            }

            if (i==m_iSize)
            {
               pView->MessageBox("Tape Drive Device full, ignoring excess data", "Warning");
               break;
            }

            m_cMemory[i] = 0;
            for (int j=0;j<8;j++)
            {
               if (uTemp & (1<<j)) m_cMemory[i] |= 1<<(j*2);
            }
         }

         ASSERT(pFile != NULL);
         fclose(pFile);
      }
   } // if ((iMode == ID_SIMULATE_RUN) || (iMode == ID_SIMULATE_STEP))

   SetGateID();

   CLogiGate::Initialize(pView, iMode);
}

void CLogiTapedriveGate::Simulate(CLogiDoc* pDoc)
{
   unsigned short uTemp;

   // Perform Simulation

   if ((Node[13]->State == HI) && (m_iLastState == LO))
   {

      // Process direction bits

      (Node[0])->NextState = LO;

      if ((Node[11])->State == HI)
      {
         if (m_iPosition == (m_iSize-1))
         {
            (Node[0])->NextState = HI;
         }
         else
         {
            m_iPosition++;
         }
      }

      if ((Node[10])->State == HI)
      {
         if (m_iPosition == 0)
         {
            (Node[0])->NextState = HI;
         }
         else
         {
            m_iPosition--;
         }
      }

      if ((Node[ 9])->State == HI)
      {
         m_iPosition = m_iStartPosition;
         (Node[0])->NextState = LO;
      }

      if ((Node[0])->NextState != HI)
      {

         // if Write to memory

         if ((Node[12])->State == HI)
         {
            uTemp = 0;

            // Get Data to write

            for (i=0;i<8;i++)
            {
               switch ((Node[i+14])->State)
               {
               case HI:      uTemp |= HI<<(i*2); break;
               case UNKNOWN: uTemp |= UNKNOWN<<(i*2); break;
               }
            }

            m_cMemory[m_iPosition] = uTemp;
         }

         // assume read

         else
         {
            uTemp = m_cMemory[m_iPosition];

            // Output data

            for (i=0;i<8;i++)
            {
               (Node[i+1])->NextState = ((uTemp>>(i*2)) & 3);
            }
         }
      }

      // Call base class to Queue Events for Driven Devices

      CLogiGate::Simulate(pDoc);
   }

   // capture current state so as to detect an edge

   m_iLastState = Node[13]->State;
}

void CLogiTapedriveGate::SetGateID(void)
{
   m_cMemory.SetSize(m_iSize);

   GateID = IDB_TAPEDRIVE;
}

void CLogiTapedriveGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[21].x += CONTACT_X_IN; // Data In
   Contact[21].y -= CONTACT_Y_17;
   Contact[20].x += CONTACT_X_IN;
   Contact[20].y -= CONTACT_Y_16;
   Contact[19].x += CONTACT_X_IN;
   Contact[19].y -= CONTACT_Y_15;
   Contact[18].x += CONTACT_X_IN;
   Contact[18].y -= CONTACT_Y_14;
   Contact[17].x += CONTACT_X_IN;
   Contact[17].y -= CONTACT_Y_13;
   Contact[16].x += CONTACT_X_IN;
   Contact[16].y -= CONTACT_Y_12;
   Contact[15].x += CONTACT_X_IN;
   Contact[15].y -= CONTACT_Y_11;
   Contact[14].x += CONTACT_X_IN;
   Contact[14].y -= CONTACT_Y_10;

   Contact[13].x += CONTACT_X_IN; // Clock
   Contact[13].y -= CONTACT_Y_8;

   Contact[12].x += CONTACT_X_IN; // Write
   Contact[12].y -= CONTACT_Y_6;

   Contact[11].x += CONTACT_X_IN; // Forward
   Contact[11].y -= CONTACT_Y_4;
   Contact[10].x += CONTACT_X_IN; // Back
   Contact[10].y -= CONTACT_Y_3;

   Contact[ 9].x += CONTACT_X_IN; // Rewind
   Contact[ 9].y -= CONTACT_Y_1;

   Contact[ 8].x += CONTACT_X_OUT_TAP; // Data Out
   Contact[ 8].y -= CONTACT_Y_17;
   Contact[ 7].x += CONTACT_X_OUT_TAP;
   Contact[ 7].y -= CONTACT_Y_16;
   Contact[ 6].x += CONTACT_X_OUT_TAP;
   Contact[ 6].y -= CONTACT_Y_15;
   Contact[ 5].x += CONTACT_X_OUT_TAP;
   Contact[ 5].y -= CONTACT_Y_14;
   Contact[ 4].x += CONTACT_X_OUT_TAP;
   Contact[ 4].y -= CONTACT_Y_13;
   Contact[ 3].x += CONTACT_X_OUT_TAP;
   Contact[ 3].y -= CONTACT_Y_12;
   Contact[ 2].x += CONTACT_X_OUT_TAP;
   Contact[ 2].y -= CONTACT_Y_11;
   Contact[ 1].x += CONTACT_X_OUT_TAP;
   Contact[ 1].y -= CONTACT_Y_10;

   Contact[ 0].x += CONTACT_X_OUT_TAP; // End of Tape
   Contact[ 0].y -= CONTACT_Y_8;
}


void CLogiTapedriveGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiTapedriveGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiTapedriveGate* pClone = new CLogiTapedriveGate(m_position, Name, m_iPage, pDoc, m_iFormat, m_iSize, m_iStartPosition, m_csFileName);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiTapedriveGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CTapedriveDlg dlg;

   dlg.m_csFileName     = m_csFileName;
   dlg.m_iFormat        = m_iFormat;
   dlg.m_uCapacity      = m_iSize;
   dlg.m_uStartPosition = m_iStartPosition;
   dlg.m_csPathName     = pView->GetDocument()->GetPathName();

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   m_csFileName     = dlg.m_csFileName;
   m_iFormat        = dlg.m_iFormat;
   m_iSize          = dlg.m_uCapacity;
   m_iStartPosition = dlg.m_uStartPosition;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();
}

////////////////////////////////////////////////////////////////////////////
// CLogiMuxGate

IMPLEMENT_SERIAL(CLogiMuxGate, CLogiGate, 0)

CLogiMuxGate::CLogiMuxGate()
{
}

CLogiMuxGate::CLogiMuxGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bMuxDeMux, int iStyle) : CLogiGate(position, name, ipage, pdoc, 16, 16, IDB_MUX_8TO1, muxgate)
{

   m_iStyle = iStyle;
   m_bDeMux = bMuxDeMux;

   SetGateID();
   SetContacts();

}

void CLogiMuxGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iStyle;
      ar << m_bDeMux;
   }
   else
   {
      ar >> m_iStyle;
      ar >> m_bDeMux;

      SetGateID();
      SetContacts();
   }
}

void CLogiMuxGate::Initialize(CLogiView* pView, UINT iMode)
{
   m_iState = UNKNOWN;

   CLogiGate::Initialize(pView, iMode);
}

void CLogiMuxGate::Simulate(CLogiDoc* pDoc)
{

   // Perform simulation

   int m_iNextState = -1;
   BOOL bDontKnow = FALSE;

   switch (m_iStyle)
   {
   case 0: // 8to1
      {
         switch ((Node[2])->State) // Strobe (L)
         {
         case UNKNOWN:
            {
               bDontKnow = TRUE;
               m_iNextState = UNKNOWN;
               break;
            }
         case LO:
            {
               UINT uTemp = 0;

               for (i=0;i<3;i++)
               {
                  switch ((Node[i+3])->State)
                  {
                  case HI:      uTemp |= 1<<i; break;
                  case UNKNOWN: bDontKnow = TRUE; break;
                  }
               }

               if (bDontKnow)
               {
                  m_iNextState = UNKNOWN;
               }
               else
               {
                  m_iNextState = Node[6+uTemp]->State;
               }

               break;
            }
         case HI:
            {
               m_iNextState = LO;
               break;
            }
         }
         break;
      }
   case 1: // 4to1
      {
         switch ((Node[2])->State) // Strobe (L)
         {
         case UNKNOWN:
            {
               bDontKnow = TRUE;
               m_iNextState = UNKNOWN;
               break;
            }
         case LO:
            {
               UINT uTemp = 0;

               for (i=0;i<2;i++)
               {
                  switch ((Node[i+3])->State)
                  {
                  case HI:      uTemp |= 1<<i; break;
                  case UNKNOWN: bDontKnow = TRUE; break;
                  }
               }

               if (bDontKnow)
               {
                  m_iNextState = UNKNOWN;
               }
               else
               {
                  m_iNextState = Node[5+uTemp]->State;
               }

               break;
            }
         case HI:
            {
               m_iNextState = LO;
               break;
            }
         }
         break;
      }
   case 2: // 2to1
      {
         switch ((Node[2])->State) // Strobe (L)
         {
         case UNKNOWN:
            {
               bDontKnow = TRUE;
               m_iNextState = UNKNOWN;
               break;
            }
         case LO:
            {
               UINT uTemp = 0;

               switch ((Node[3])->State)
               {
               case HI:      uTemp |= 1; break;
               case UNKNOWN: bDontKnow = TRUE; break;
               }

               if (bDontKnow)
               {
                  m_iNextState = UNKNOWN;
               }
               else
               {
                  m_iNextState = Node[4+uTemp]->State;
               }

               break;
            }
         case HI:
            {
               m_iNextState = LO;
               break;
            }
         }
         break;
      }
   case 3: // 3to8
      {
         switch ((Node[8])->State) // Strobe (L)
         {
         case UNKNOWN:
            {
               for (i=0;i<8;i++)
               {
                  Node[i]->NextState = UNKNOWN;
               }
               break;
            }
         case LO:
            {
               UINT uTemp = 0;

               for (i=0;i<3;i++)
               {
                  switch ((Node[i+9])->State)
                  {
                  case HI:      uTemp |= 1<<i; break;
                  case UNKNOWN: bDontKnow = TRUE; break;
                  }
               }

               if (bDontKnow)
               {
                  for (i=0;i<8;i++)
                  {
                     Node[i]->NextState = UNKNOWN;
                  }
               }
               else
               {
                  for (i=0;i<8;i++)
                  {
                     Node[i]->NextState = HI;
                  }
                  Node[uTemp]->NextState = LO;
               }

               break;
            }
         case HI:
            {
               for (i=0;i<8;i++)
               {
                  Node[i]->NextState = HI;
               }
               break;
            }
         }
         break;
      }
   case 4: // 2to4
      {
         switch ((Node[4])->State) // Strobe
         {
         case UNKNOWN:
            {
               for (i=0;i<4;i++)
               {
                  Node[i]->NextState = UNKNOWN;
               }
               break;
            }
         case LO:
            {
               UINT uTemp = 0;

               for (i=0;i<2;i++)
               {
                  switch ((Node[i+5])->State)
                  {
                  case HI:      uTemp |= 1<<i; break;
                  case UNKNOWN: bDontKnow = TRUE; break;
                  }
               }

               if (bDontKnow)
               {
                  for (i=0;i<4;i++)
                  {
                     Node[i]->NextState = UNKNOWN;
                  }
               }
               else
               {
                  for (i=0;i<4;i++)
                  {
                     Node[i]->NextState = HI;
                  }
                  Node[uTemp]->NextState = LO;
               }

               break;
            }
         case HI:
            {
               for (i=0;i<4;i++)
               {
                  Node[i]->NextState = HI;
               }
               break;
            }
         }
         break;
      }
   case 5: // 1to2
      {
         switch ((Node[2])->State) // Strobe
         {
         case UNKNOWN:
            {
               for (i=0;i<2;i++)
               {
                  Node[i]->NextState = UNKNOWN;
               }
               break;
            }
         case LO:
            {
               UINT uTemp = 0;

               switch ((Node[3])->State)
               {
               case HI:      uTemp |= 1; break;
               case UNKNOWN: bDontKnow = TRUE; break;
               }

               if (bDontKnow)
               {
                  for (i=0;i<2;i++)
                  {
                     Node[i]->NextState = UNKNOWN;
                  }
               }
               else
               {
                  for (i=0;i<2;i++)
                  {
                     Node[i]->NextState = HI;
                  }
                  Node[uTemp]->NextState = LO;
               }

               break;
            }
         case HI:
            {
               for (i=0;i<2;i++)
               {
                  Node[i]->NextState = HI;
               }
               break;
            }
         }
         break;
      }
   }

   switch (m_iStyle)
   {
   case 0: // Mux
   case 1:
   case 2:
      {
         if (m_iNextState != m_iState)
         {
            //            if (bDontKnow)
            //               {
            //               m_iNextState = UNKNOWN;
            //               if (m_iNextState == m_iState) return;
            //               }

            m_iState = m_iNextState;

            switch (m_iState)
            {
            case UNKNOWN:
               {
                  (Node[0])->NextState = UNKNOWN;
                  (Node[1])->NextState = UNKNOWN;
                  break;
               }
            case HI:
               {
                  (Node[0])->NextState = LO;
                  (Node[1])->NextState = HI;
                  break;
               }
            case LO:
               {
                  (Node[0])->NextState = HI;
                  (Node[1])->NextState = LO;
                  break;
               }
            }

            // Call base class to Queue Events for Driven Devices

            CLogiGate::Simulate(pDoc);

         }
         break;
      }
   case 3: // Demux
   case 4:
   case 5:
      {
         // Call base class to Queue Events for Driven Devices

         CLogiGate::Simulate(pDoc);

         break;
      }
   }

}

void CLogiMuxGate::SetGateID(void)
{

   switch (m_iStyle)
   {
   case 0: // 8to1
      {
         Inputs = 12;
         Outputs = 2;

         GateID = IDB_MUX_8TO1;
         break;
      }
   case 1: // 4to1
      {
         Inputs = 7;
         Outputs = 2;

         GateID = IDB_MUX_4TO1;
         break;
      }
   case 2: // 2to1
      {
         Inputs = 4;
         Outputs = 2;

         GateID = IDB_MUX_2TO1;
         break;
      }
   case 3: // 3to8
      {
         Inputs = 4;
         Outputs = 8;

         GateID = IDB_DEMUX_3TO8;
         break;
      }
   case 4: // 2to4
      {
         Inputs = 3;
         Outputs = 4;

         GateID = IDB_DEMUX_2TO4;
         break;
      }
   case 5: // 1to2
      {
         Inputs = 2;
         Outputs = 2;

         GateID = IDB_DEMUX_1TO2;
         break;
      }
   }

   Contacts = Outputs + Inputs;
}

void CLogiMuxGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   switch (m_iStyle)
   {
   case 0: // 8to1
      {
         Contact[0].x += CONTACT_X_OUT; // W
         Contact[0].y -= CONTACT_Y_7;
         Contact[1].x += CONTACT_X_OUT; // Y
         Contact[1].y -= CONTACT_Y_8;

         Contact[2].x += CONTACT_X_IN; // C
         Contact[2].y -= CONTACT_Y_1;

         Contact[3].x += CONTACT_X_IN; // S0
         Contact[3].y -= CONTACT_Y_3;
         Contact[4].x += CONTACT_X_IN;
         Contact[4].y -= CONTACT_Y_4;
         Contact[5].x += CONTACT_X_IN;
         Contact[5].y -= CONTACT_Y_5;

         Contact[6].x += CONTACT_X_IN; // D0
         Contact[6].y -= CONTACT_Y_7;
         Contact[7].x += CONTACT_X_IN;
         Contact[7].y -= CONTACT_Y_8;
         Contact[8].x += CONTACT_X_IN;
         Contact[8].y -= CONTACT_Y_9;
         Contact[9].x += CONTACT_X_IN;
         Contact[9].y -= CONTACT_Y_10;
         Contact[10].x += CONTACT_X_IN;
         Contact[10].y -= CONTACT_Y_11;
         Contact[11].x += CONTACT_X_IN;
         Contact[11].y -= CONTACT_Y_12;
         Contact[12].x += CONTACT_X_IN;
         Contact[12].y -= CONTACT_Y_13;
         Contact[13].x += CONTACT_X_IN;
         Contact[13].y -= CONTACT_Y_14;

         break;
      }
   case 1: // 4to1
      {
         Contact[0].x += CONTACT_X_OUT; // W
         Contact[0].y -= CONTACT_Y_7;
         Contact[1].x += CONTACT_X_OUT; // Y
         Contact[1].y -= CONTACT_Y_8;

         Contact[2].x += CONTACT_X_IN; // C
         Contact[2].y -= CONTACT_Y_1;

         Contact[3].x += CONTACT_X_IN; // S0
         Contact[3].y -= CONTACT_Y_3;
         Contact[4].x += CONTACT_X_IN;
         Contact[4].y -= CONTACT_Y_4;

         Contact[5].x += CONTACT_X_IN; // D0
         Contact[5].y -= CONTACT_Y_7;
         Contact[6].x += CONTACT_X_IN;
         Contact[6].y -= CONTACT_Y_8;
         Contact[7].x += CONTACT_X_IN;
         Contact[7].y -= CONTACT_Y_9;
         Contact[8].x += CONTACT_X_IN;
         Contact[8].y -= CONTACT_Y_10;

         break;
      }
   case 2: // 2to1
      {
         Contact[0].x += CONTACT_X_OUT; // W
         Contact[0].y -= CONTACT_Y_7;
         Contact[1].x += CONTACT_X_OUT; // Y
         Contact[1].y -= CONTACT_Y_8;

         Contact[2].x += CONTACT_X_IN; // C
         Contact[2].y -= CONTACT_Y_1;

         Contact[3].x += CONTACT_X_IN; // S0
         Contact[3].y -= CONTACT_Y_3;

         Contact[4].x += CONTACT_X_IN; // D0
         Contact[4].y -= CONTACT_Y_7;
         Contact[5].x += CONTACT_X_IN;
         Contact[5].y -= CONTACT_Y_8;

         break;
      }
   case 3: // 3to8
      {
         Contact[0].x += CONTACT_X_OUT; // E0
         Contact[0].y -= CONTACT_Y_7;
         Contact[1].x += CONTACT_X_OUT;
         Contact[1].y -= CONTACT_Y_8;
         Contact[2].x += CONTACT_X_OUT;
         Contact[2].y -= CONTACT_Y_9;
         Contact[3].x += CONTACT_X_OUT;
         Contact[3].y -= CONTACT_Y_10;
         Contact[4].x += CONTACT_X_OUT;
         Contact[4].y -= CONTACT_Y_11;
         Contact[5].x += CONTACT_X_OUT;
         Contact[5].y -= CONTACT_Y_12;
         Contact[6].x += CONTACT_X_OUT;
         Contact[6].y -= CONTACT_Y_13;
         Contact[7].x += CONTACT_X_OUT;
         Contact[7].y -= CONTACT_Y_14;

         Contact[8].x += CONTACT_X_IN; // C
         Contact[8].y -= CONTACT_Y_1;

         Contact[9].x += CONTACT_X_IN; // S0
         Contact[9].y -= CONTACT_Y_3;
         Contact[10].x += CONTACT_X_IN;
         Contact[10].y -= CONTACT_Y_4;
         Contact[11].x += CONTACT_X_IN;
         Contact[11].y -= CONTACT_Y_5;

         break;
      }
   case 4: // 2to4
      {
         Contact[0].x += CONTACT_X_OUT; // E0
         Contact[0].y -= CONTACT_Y_7;
         Contact[1].x += CONTACT_X_OUT;
         Contact[1].y -= CONTACT_Y_8;
         Contact[2].x += CONTACT_X_OUT;
         Contact[2].y -= CONTACT_Y_9;
         Contact[3].x += CONTACT_X_OUT;
         Contact[3].y -= CONTACT_Y_10;

         Contact[4].x += CONTACT_X_IN; // C
         Contact[4].y -= CONTACT_Y_1;

         Contact[5].x += CONTACT_X_IN; // S0
         Contact[5].y -= CONTACT_Y_3;
         Contact[6].x += CONTACT_X_IN;
         Contact[6].y -= CONTACT_Y_4;
         Contact[7].x += CONTACT_X_IN;
         Contact[7].y -= CONTACT_Y_5;

         break;
      }
   case 5: // 1to2
      {
         Contact[0].x += CONTACT_X_OUT; // E0
         Contact[0].y -= CONTACT_Y_7;
         Contact[1].x += CONTACT_X_OUT;
         Contact[1].y -= CONTACT_Y_8;

         Contact[2].x += CONTACT_X_IN; // C
         Contact[2].y -= CONTACT_Y_1;

         Contact[3].x += CONTACT_X_IN; // S0
         Contact[3].y -= CONTACT_Y_3;
         Contact[4].x += CONTACT_X_IN;
         Contact[4].y -= CONTACT_Y_4;
         Contact[5].x += CONTACT_X_IN;
         Contact[5].y -= CONTACT_Y_5;

         break;
      }

   }

}

void CLogiMuxGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiMuxGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiMuxGate* pClone = new CLogiMuxGate(m_position, Name, m_iPage, pDoc, m_bDeMux, m_iStyle);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiMuxGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CMuxDlg dlg;
   int i;

   dlg.m_iStyle = m_iStyle;
   dlg.m_bDeMux = m_bDeMux;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   if (m_iStyle != dlg.m_iStyle)
   {
      for (i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing Mux type", "Error", MB_ICONEXCLAMATION);
            return;
         }
      }

      for (i=0;i<Contacts;i++) Node[i] = m_pDocument->m_pAnodeNULL;
   }

   m_iStyle = dlg.m_iStyle;
   m_bDeMux = dlg.m_bDeMux;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();

}

////////////////////////////////////////////////////////////////////////////
// CLogiAluGate

IMPLEMENT_SERIAL(CLogiAluGate, CLogiGate, 0)

CLogiAluGate::CLogiAluGate()
{
}

CLogiAluGate::CLogiAluGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bAluDeAlu, int iAlu2Inputs) : CLogiGate(position, name, ipage, pdoc, 12, 20, IDB_ALU, alugate)
{

   m_iInputs = iAlu2Inputs;
   m_bDeAlu = bAluDeAlu;

   SetGateID();
   SetContacts();

}

void CLogiAluGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iInputs;
      ar << m_bDeAlu;
   }
   else
   {
      ar >> m_iInputs;
      ar >> m_bDeAlu;

      SetGateID();
      SetContacts();
   }
}

void CLogiAluGate::Simulate(CLogiDoc* pDoc)
{
   UINT uTempF = 0;
   UINT uTempCin = 0;
   UINT uTempA = 0;
   UINT uTempB = 0;
   UINT uTempS = 0;

   // Perform simulation

   (Node[ 8])->NextState = LO; // N
   (Node[10])->NextState = LO; // V

   (Node[11])->NextState = LO; // Cout

   for (i=0;i<8;i++)
   {
      switch ((Node[i+24])->State)
      {
      case HI: uTempA |= 1<<i; break;
      case UNKNOWN: /* uTempA = 511; break; */ goto SORRYPAL;
      }
   }

   for (i=0;i<8;i++)
   {
      switch ((Node[i+16])->State)
      {
      case HI: uTempB |= 1<<i; break;
      case UNKNOWN: /* uTempB = 511; break; */ goto SORRYPAL;
      }
   }

   for (i=0;i<3;i++)
   {
      switch ((Node[i+13])->State)
      {
      case HI: uTempS |= 1<<i; break;
      case UNKNOWN: /* uTempS = 15; break; */ goto SORRYPAL;
      }
   }

   switch ((Node[12])->State)
   {
   case HI: uTempCin = 1; break;
   case LO: uTempCin = 0; break;
   case UNKNOWN: /* uTempCin = 2; break; */ goto SORRYPAL;
   }

   switch (uTempS)
   {
   case 0: // Add
      {
         uTempF = uTempA + uTempB + uTempCin;
         if (uTempF & 0xFF00) (Node[11])->NextState = HI;
         break;
      }
   case 1: // Subtract
      {
         uTempF = uTempA - (uTempB + uTempCin);
         if ((uTempB + uTempCin) > uTempA) (Node[11])->NextState = HI;
         break;
      }
   case 2: // Multiply
      {
         uTempF = uTempA * uTempB;
         if (uTempF & 0xFF00) (Node[10])->NextState = HI;
         break;
      }
   case 3: // Divide
      {
         if (uTempB == 0)
         {
            uTempF = 0xFF;
            (Node[10])->NextState = HI;
         }
         else
         {
            uTempF = uTempA / uTempB;
         }
         break;
      }
   case 4: // Compare
      {
         uTempF = uTempA == uTempB;
         break;
      }
   case 5: // Less
      {
         uTempF = uTempA < uTempB;
         break;
      }
   case 6: // Shift Left
      {
         uTempF = uTempA;

         for (i=0;i<min(uTempB,9);i++)
         {
            uTempF = (uTempF << 1) | uTempCin;
         }
         if (uTempF & 0x0100) (Node[11])->NextState = HI;
         break;
      }
   case 7: // Shift Right
      {
         uTempF = uTempA<<1;

         for (i=0;i<min(uTempB,9);i++)
         {
            uTempF = (uTempF >> 1) | (uTempCin<<8);
         }
         if (uTempF & 1) (Node[11])->NextState = HI;

         uTempF = uTempF>>1;
         break;
      }
   }

   for (i=0;i<8;i++)
   {
      if (uTempF & (1<<i)) (Node[i])->NextState = HI; else (Node[i])->NextState = LO;
   }

   if (uTempF & 0xFF)
   {
      (Node[9])->NextState = LO; // Z
   }
   else
   {
      (Node[9])->NextState = HI; // Z
   }

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);

   return;

SORRYPAL:

   for (i=0;i<8;i++)
   {
      (Node[i])->NextState = UNKNOWN;
   }

   (Node[ 8])->NextState = UNKNOWN; // N
   (Node[ 9])->NextState = UNKNOWN; // Z
   (Node[10])->NextState = UNKNOWN; // V
   (Node[11])->NextState = UNKNOWN; // Cout

   CLogiGate::Simulate(pDoc);

}

void CLogiAluGate::SetGateID(void)
{
   GateID = IDB_ALU;
}

void CLogiAluGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[ 0].x += CONTACT_X_OUT; // Data Out
   Contact[ 0].y -= CONTACT_Y_14;
   Contact[ 1].x += CONTACT_X_OUT;
   Contact[ 1].y -= CONTACT_Y_15;
   Contact[ 2].x += CONTACT_X_OUT;
   Contact[ 2].y -= CONTACT_Y_16;
   Contact[ 3].x += CONTACT_X_OUT;
   Contact[ 3].y -= CONTACT_Y_17;
   Contact[ 4].x += CONTACT_X_OUT;
   Contact[ 4].y -= CONTACT_Y_18;
   Contact[ 5].x += CONTACT_X_OUT;
   Contact[ 5].y -= CONTACT_Y_19;
   Contact[ 6].x += CONTACT_X_OUT;
   Contact[ 6].y -= CONTACT_Y_20;
   Contact[ 7].x += CONTACT_X_OUT;
   Contact[ 7].y -= CONTACT_Y_21;

   Contact[ 8].x += CONTACT_X_OUT; // Status V
   Contact[ 8].y -= CONTACT_Y_10;
   Contact[ 9].x += CONTACT_X_OUT;
   Contact[ 9].y -= CONTACT_Y_11;
   Contact[10].x += CONTACT_X_OUT;
   Contact[10].y -= CONTACT_Y_12;

   Contact[11].x += CONTACT_X_OUT; // COUT
   Contact[11].y -= CONTACT_Y_23;

   Contact[12].x += CONTACT_X_IN;  // CIN
   Contact[12].y -= CONTACT_Y_1;

   Contact[13].x += CONTACT_X_IN;  // Function
   Contact[13].y -= CONTACT_Y_3;
   Contact[14].x += CONTACT_X_IN;
   Contact[14].y -= CONTACT_Y_4;
   Contact[15].x += CONTACT_X_IN;
   Contact[15].y -= CONTACT_Y_5;

   Contact[16].x += CONTACT_X_IN;  // Operand B
   Contact[16].y -= CONTACT_Y_7;
   Contact[17].x += CONTACT_X_IN;
   Contact[17].y -= CONTACT_Y_8;
   Contact[18].x += CONTACT_X_IN;
   Contact[18].y -= CONTACT_Y_9;
   Contact[19].x += CONTACT_X_IN;
   Contact[19].y -= CONTACT_Y_10;
   Contact[20].x += CONTACT_X_IN;
   Contact[20].y -= CONTACT_Y_11;
   Contact[21].x += CONTACT_X_IN;
   Contact[21].y -= CONTACT_Y_12;
   Contact[22].x += CONTACT_X_IN;
   Contact[22].y -= CONTACT_Y_13;
   Contact[23].x += CONTACT_X_IN;
   Contact[23].y -= CONTACT_Y_14;

   Contact[24].x += CONTACT_X_IN;  // Operand A
   Contact[24].y -= CONTACT_Y_16;
   Contact[25].x += CONTACT_X_IN;
   Contact[25].y -= CONTACT_Y_17;
   Contact[26].x += CONTACT_X_IN;
   Contact[26].y -= CONTACT_Y_18;
   Contact[27].x += CONTACT_X_IN;
   Contact[27].y -= CONTACT_Y_19;
   Contact[28].x += CONTACT_X_IN;
   Contact[28].y -= CONTACT_Y_20;
   Contact[29].x += CONTACT_X_IN;
   Contact[29].y -= CONTACT_Y_21;
   Contact[30].x += CONTACT_X_IN;
   Contact[30].y -= CONTACT_Y_22;
   Contact[31].x += CONTACT_X_IN;
   Contact[31].y -= CONTACT_Y_23;
}


void CLogiAluGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiAluGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiAluGate* pClone = new CLogiAluGate(m_position, Name, m_iPage, pDoc, m_bDeAlu, m_iInputs);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiAluGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CAluDlg dlg;

   //   dlg.m_iInputs = m_iInputs;
   //   dlg.m_bDeMux = m_bDeAlu;

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   //   m_iInputs = dlg.m_iInputs;
   //   m_bDeAlu = dlg.m_bDeMux;

   SetGateID();
   SetContacts();

   Invalidate();
   m_pDocument->SetModifiedFlag();

}

/////////////////////////////////////////////////////////////////////////////
