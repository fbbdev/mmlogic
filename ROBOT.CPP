// Logivw.cpp : implementation of the CLogiRobotGate class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
// CLogiRobotGate

IMPLEMENT_SERIAL(CLogiRobotGate, CLogiGate, 0)

BOOL CLogiRobotGate::ConnectOn()
{
   CFile cf;

   if (!m_bConnected)
   {
      if (m_csFileName != "\\NUL")
      {
         CString csTemp;

         CString csCheck = m_csFileName.Right(5);
         csCheck.MakeUpper();

         if (csCheck != "0.BMP") return FALSE;

         CString csFullPath;
         CString csPathName = m_pDocument->GetPathName();

         RelativeToFullPath(m_csFileName, csPathName, csFullPath);

         BOOL bError = TRUE;

         for (int i=0;i<16;i++)
         {
            csTemp.Format("%s%d.BMP",csFullPath.Left(csFullPath.GetLength()-5),i);

            if (!cf.Open(csTemp, CFile::modeRead | CFile::shareDenyWrite))
            {
               continue;
            }

            if (!m_cdRobots[i].Read(&cf))
            {
               cf.Close();
               continue;
            }

            bError = FALSE;

            cf.Close();
         }

         if (bError) return(FALSE);
      }

      CSize size = m_Playground->m_size;

      switch (m_iPosition)
      {
      case 0: m_xPos = size.cx/2;    m_yPos = size.cy/2;    break;
      case 1: m_xPos = 0;            m_yPos = 0;            break;
      case 2: m_xPos = size.cx-1;    m_yPos = 0;            break;
      case 3: m_xPos = 0;            m_yPos = size.cy-1;    break;
      case 4: m_xPos = size.cx-1;    m_yPos = size.cy-1;    break;
      case 5: m_xPos = m_iPositionX; m_yPos = m_iPositionY; break;
      }

      m_bConnected = TRUE;
   }

   return(TRUE);
}

int CLogiRobotGate::ChooseRobot()
{
   return m_Playground->m_cdPicture.GetPixelIndex(m_xPos, m_yPos);
}

CLogiRobotGate::CLogiRobotGate()
{
   m_bConnected = FALSE;    // Flag that send socket is connected

   m_xPos = 100;
   m_yPos = 100;

   m_crLastdraw = CRect(CPoint(0,0), CSize(0,0));
   m_crNewdraw = CRect(CPoint(0,0), CSize(0,0));

   m_uIndex = 0;
   m_Playground = NULL;
}

CLogiRobotGate::CLogiRobotGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc,
                               int iStyle,
                               int iPosition,
                               int iPositionX,
                               int iPositionY,
                               int iHotspot,
                               int iHotspotX,
                               int iHotspotY,
                               const char *pFileName) : CLogiGate(position, name, ipage, pdoc, 5, 12, IDB_ROBOT, robotgate)
{
   m_csFileName = pFileName;
   m_iStyle     = iStyle;
   m_iPosition  = iPosition;
   m_iPositionX = iPositionX;
   m_iPositionY = iPositionY;
   m_iHotspot   = iHotspot;
   m_iHotspotX  = iHotspotX;
   m_iHotspotY  = iHotspotY;

   m_bConnected = FALSE;    // Flag that send socket is connected

   m_uIndex = 0;
   m_Playground = NULL;

   switch (m_iStyle)
   {
   case 0: // Seeing
      {
         Inputs = 7;
         Outputs = 5;

         GateID = IDB_ROBOT;
         break;
      }
   case 1: // Drawing
      {
         Inputs = 12;
         Outputs = 1;

         GateID = IDB_ROBOTD;
         break;
      }
   }

   Contacts = Outputs + Inputs;

   SetContacts();

}

void CLogiRobotGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_csFileName;
      ar << m_csFileName;
      ar << m_iStyle;
      ar << m_iPosition;
      ar << m_iPositionX;
      ar << m_iPositionY;
      ar << m_iHotspot;
      ar << m_iHotspotX;
      ar << m_iHotspotY;
   }
   else
   {
      ar >> m_csFileName;
      ar >> m_csFileName;
      ar >> m_iStyle;
      ar >> m_iPosition;
      ar >> m_iPositionX;
      ar >> m_iPositionY;
      ar >> m_iHotspot;
      ar >> m_iHotspotX;
      ar >> m_iHotspotY;
      SetContacts();
   }
}

void CLogiRobotGate::Animate(CLogiView* pView)
{
   // Draw Device in its current state (BitMap ID held in GateID)

   // pView->InvalObj(this); the robot device itself is not animated

   //   if (m_Playground) pView->InvalObj(m_Playground);
   CRect crTemp(m_crNewdraw);
   pView->DocToClient(crTemp);
   pView->InvalidateRect(crTemp);
   pView->InvalidateRect(m_crLastdraw);
}

void CLogiRobotGate::DrawRobot(CDC* pDC, CLogiView* pView)
{
   ASSERT_VALID(this);

   if (m_Playground)
   {
      m_cdRobots[m_uIndex].DrawTransparent(pDC, m_cpPoint, m_csSize);
      m_crLastdraw = CRect(m_cpPoint, m_csSize);
      pView->DocToClient(m_crLastdraw);
   }
}

void CLogiRobotGate::Draw(CDC* pDC, CLogiView* pView )
{
   ASSERT_VALID(this);

   CLogiGate::Draw(pDC, pView);
}

void CLogiRobotGate::Action(CLogiView* /* pView */, BOOL /* bDown */, const CPoint& /*point*/)
{
}

void CLogiRobotGate::Initialize(CLogiView* pView, UINT iMode)
{

   pView->InvalidateRect(m_crLastdraw);
   m_crLastdraw = CRect(CPoint(0,0), CSize(0,0));
   //   pView->InvalidateRect(m_crNewdraw);
   m_crNewdraw = CRect(CPoint(0,0), CSize(0,0));

   m_iLastState = UNKNOWN;
   m_uTemp = 0;
   m_uDirection = 0;

   if (m_bConnected)
   {
      for (int i=0;i<16;i++)
      {
         if (!m_cdRobots[i].IsEmpty())
         {
            m_cdRobots[i].Empty();
         }
      }
   }

   m_bConnected = FALSE;

   pView->GetDocument()->EventQueue.AddTail(this);

   pView->InvalObj(this);

   CLogiGate::Initialize(pView, iMode);
}

void CLogiRobotGate::Simulate(CLogiDoc* pDoc)
{

   BOOL bDontKnow;
   COLORREF iHit;
   BOOL bHit;

   if (!ConnectOn())
   {
      ::MessageBox(::GetFocus(), m_csFileName, "Could not load File", MB_OK | MB_ICONEXCLAMATION);
      pDoc->Halt();
      //      pDoc->m_bKeepGoing = FALSE;
      return;
   }

   if (!m_Playground) return;

   switch (m_iStyle)
   {
   case 0: // Seeing
      {
         switch ((Node[5])->State)
         {
         case HI:
            {
               UINT uTemp = 0;

               // Get direction

               for (i=0;i<2;i++)
               {
                  switch ((Node[i+6])->State)
                  {
                  case HI:      uTemp |= 1<<i; break;
                  case UNKNOWN: bDontKnow = TRUE; break;
                  }
               }

               // Move in the specified direction

               m_uDirection = uTemp;

               switch (uTemp)
               {
               case 0: m_xPos++; break;
               case 1: m_xPos--; break;
               case 2: m_yPos++; break;
               case 3: m_yPos--; break;
               }

               // Init output color index

               for (i=0;i<4;i++) Node[i+1]->NextState = LO;

               // Find color at new position

               iHit = ChooseRobot();

               // If we missed backup and set error

               if (iHit == -1)
               {
                  Node[0]->NextState = HI;

                  switch (uTemp)
                  {
                  case 0: m_xPos--; break;
                  case 1: m_xPos++; break;
                  case 2: m_yPos--; break;
                  case 3: m_yPos++; break;
                  }
               }

               // else no error and drive color we saw

               else
               {
                  Node[0]->NextState = LO;

                  for (i=0;i<4;i++)
                  {
                     if (((1<<i) & iHit) != 0)
                     {
                        Node[i+1]->NextState = HI;
                     }
                     else
                     {
                        Node[i+1]->NextState = LO;
                     }
                  }
               }

               // Get bitmap index

               m_uIndex = 0;

               for (i=0;i<4;i++)
               {
                  switch ((Node[i+8])->State)
                  {
                  case HI:      m_uIndex |= 1<<i; break;
                  case UNKNOWN: bDontKnow = TRUE; break;
                  }
               }
               break;
            }
         case LO:
            {
               //         m_iNextState = LO;
               break;
            }
         }
         break;
      }

   case 1: // Drawing
      {
         switch ((Node[1])->State)
         {
         case HI:
            {
               UINT uDir = 0;
               UINT uCol = 0;

               // Get color index

               for (i=0;i<4;i++)
               {
                  switch ((Node[i+8])->State)
                  {
                  case HI:      uCol |= 1<<i; break;
                  case UNKNOWN: bDontKnow = TRUE; break;
                  }
               }

               // Get direction

               for (i=0;i<2;i++)
               {
                  switch ((Node[i+2])->State)
                  {
                  case HI:      uDir |= 1<<i; break;
                  case UNKNOWN: bDontKnow = TRUE; break;
                  }
               }

               // Move in the specified direction

               m_uDirection = uDir;

               switch (uDir)
               {
               case 0: m_xPos++; break;
               case 1: m_xPos--; break;
               case 2: m_yPos++; break;
               case 3: m_yPos--; break;
               }

               bHit = m_Playground->m_cdPicture.SetPixelIndex(m_xPos, m_yPos, uCol, (Node[12])->State != HI);

               if (!bHit)
               {
                  Node[0]->NextState = HI;

                  switch (uDir)
                  {
                  case 0: m_xPos--; break;
                  case 1: m_xPos++; break;
                  case 2: m_yPos--; break;
                  case 3: m_yPos++; break;
                  }
               }
               else
               {
                  Node[0]->NextState = LO;
               }

               // Get bitmap index

               m_uIndex = 0;

               for (i=0;i<4;i++)
               {
                  switch ((Node[i+4])->State)
                  {
                  case HI:      m_uIndex |= 1<<i; break;
                  case UNKNOWN: bDontKnow = TRUE; break;
                  }
               }


               break;
            }
         case LO:
            {
               //         m_iNextState = LO;
               break;
            }
         }
         break;
      }
   }

   rect = m_Playground->m_position;

   m_csSize = m_cdRobots[m_uIndex].GetDimensions();

   switch (m_iHotspot)
   {
   case 0: m_iHotspotX = m_csSize.cx/2; m_iHotspotY = m_csSize.cy/2; break;
   case 1: m_iHotspotX = 0;             m_iHotspotY = 0;             break;
   case 2: m_iHotspotX = m_csSize.cx-1; m_iHotspotY = 0;             break;
   case 3: m_iHotspotX = 0;             m_iHotspotY = m_csSize.cy-1; break;
   case 4: m_iHotspotX = m_csSize.cx-1; m_iHotspotY = m_csSize.cy-1; break;
      //       case 5: // custom don't touch
   }

   switch (m_uDirection)
   {
   case 0: m_cpPoint = CPoint(rect.left+m_xPos-(m_csSize.cy-m_iHotspotY), rect.bottom+m_yPos-(            m_iHotspotX)); break;
   case 1: m_cpPoint = CPoint(rect.left+m_xPos-(            m_iHotspotY), rect.bottom+m_yPos-(m_csSize.cx-m_iHotspotX)); break;
   case 2: m_cpPoint = CPoint(rect.left+m_xPos-(m_csSize.cx-m_iHotspotX), rect.bottom+m_yPos-(m_csSize.cy-m_iHotspotY)); break;
   case 3: m_cpPoint = CPoint(rect.left+m_xPos-(            m_iHotspotX), rect.bottom+m_yPos-(            m_iHotspotY)); break;
   }

   m_crNewdraw = CRect(m_cpPoint, m_csSize);

   // Call base class to Queue Events for Driven Devices

   CLogiGate::Simulate(pDoc);
}

// SetContacts
void CLogiRobotGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   switch (m_iStyle)
   {
   case 0: // Seeing
      {
         Contact[0].x += CONTACT_X_OUT; // Error
         Contact[0].y -= CONTACT_Y_1;

         Contact[1].x += CONTACT_X_OUT; // Color
         Contact[1].y -= CONTACT_Y_3;
         Contact[2].x += CONTACT_X_OUT;
         Contact[2].y -= CONTACT_Y_4;
         Contact[3].x += CONTACT_X_OUT;
         Contact[3].y -= CONTACT_Y_5;
         Contact[4].x += CONTACT_X_OUT;
         Contact[4].y -= CONTACT_Y_6;

         Contact[5].x += CONTACT_X_IN; // Move
         Contact[5].y -= CONTACT_Y_1;

         Contact[6].x += CONTACT_X_IN; // Direction
         Contact[6].y -= CONTACT_Y_3;
         Contact[7].x += CONTACT_X_IN;
         Contact[7].y -= CONTACT_Y_4;

         Contact[8].x += CONTACT_X_IN; // Bitmap
         Contact[8].y -= CONTACT_Y_6;
         Contact[9].x += CONTACT_X_IN;
         Contact[9].y -= CONTACT_Y_7;
         Contact[10].x += CONTACT_X_IN;
         Contact[10].y -= CONTACT_Y_8;
         Contact[11].x += CONTACT_X_IN;
         Contact[11].y -= CONTACT_Y_9;
         break;
      }
   case 1: // Drawing
      {
         Contact[0].x += CONTACT_X_OUT; // Error
         Contact[0].y -= CONTACT_Y_1;

         Contact[1].x += CONTACT_X_IN; // Move
         Contact[1].y -= CONTACT_Y_1;

         Contact[2].x += CONTACT_X_IN; // Direction
         Contact[2].y -= CONTACT_Y_3;
         Contact[3].x += CONTACT_X_IN;
         Contact[3].y -= CONTACT_Y_4;

         Contact[4].x += CONTACT_X_IN; // Bitmap
         Contact[4].y -= CONTACT_Y_6;
         Contact[5].x += CONTACT_X_IN;
         Contact[5].y -= CONTACT_Y_7;
         Contact[6].x += CONTACT_X_IN;
         Contact[6].y -= CONTACT_Y_8;
         Contact[7].x += CONTACT_X_IN;
         Contact[7].y -= CONTACT_Y_9;

         Contact[8].x += CONTACT_X_IN; // Color
         Contact[8].y -= CONTACT_Y_11;
         Contact[9].x += CONTACT_X_IN;
         Contact[9].y -= CONTACT_Y_12;
         Contact[10].x += CONTACT_X_IN;
         Contact[10].y -= CONTACT_Y_13;
         Contact[11].x += CONTACT_X_IN;
         Contact[11].y -= CONTACT_Y_14;

         Contact[12].x += CONTACT_X_IN; // Pen
         Contact[12].y -= CONTACT_Y_16;
         break;
      }
   }
}

// position must be in logical coordinates
void CLogiRobotGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();

   CLogiGate::MoveTo(position, pView);

}

CLogiObj* CLogiRobotGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiRobotGate* pClone = new CLogiRobotGate(m_position, Name, m_iPage, pDoc,
      m_iStyle,
      m_iPosition,
      m_iPositionX,
      m_iPositionY,
      m_iHotspot,
      m_iHotspotX,
      m_iHotspotY,
      m_csFileName
      );

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiRobotGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CRobotDlg dlg;

   dlg.m_csFileName = m_csFileName;
   dlg.m_iStyle     = m_iStyle;
   dlg.m_iPosition  = m_iPosition;
   dlg.m_iPositionX = m_iPositionX;
   dlg.m_iPositionY = m_iPositionY;
   dlg.m_iHotspot   = m_iHotspot;
   dlg.m_iHotspotX  = m_iHotspotX;
   dlg.m_iHotspotY  = m_iHotspotY;

   dlg.m_csPathName = pView->GetDocument()->GetPathName();

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   if (m_iStyle != dlg.m_iStyle)
   {
      for (int i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing Robot type", "Error");
            return;
         }
      }

      for (/*jal int */  i=0;i<Contacts;i++) Node[i] = m_pDocument->m_pAnodeNULL;
   }

   m_csFileName = dlg.m_csFileName;
   m_iStyle     = dlg.m_iStyle;
   m_iPosition  = dlg.m_iPosition;
   m_iPositionX = dlg.m_iPositionX;
   m_iPositionY = dlg.m_iPositionY;
   m_iHotspot   = dlg.m_iHotspot;
   m_iHotspotX  = dlg.m_iHotspotX;
   m_iHotspotY  = dlg.m_iHotspotY;

   switch (m_iStyle)
   {
   case 0: // Seeing
      {
         Inputs = 7;
         Outputs = 5;

         GateID = IDB_ROBOT;
         break;
      }
   case 1: // Drawing
      {
         Inputs = 12;
         Outputs = 1;

         GateID = IDB_ROBOTD;
         break;
      }
   }

   Contacts = Outputs + Inputs;

   SetContacts();
   Invalidate();
   m_pDocument->SetModifiedFlag();
}
