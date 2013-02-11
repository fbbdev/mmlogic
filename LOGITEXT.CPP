// LogiText.cpp - implementation for LogiText objects
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

////////////////////////////////////////////////////////////////////////////
// CLogiTextGate

IMPLEMENT_SERIAL(CLogiTextGate, CLogiGate, 0)

CLogiTextGate::CLogiTextGate()
{
   pcbGate = NULL;
   m_bLoaded = FALSE;
}

CLogiTextGate::~CLogiTextGate()
{
}

CLogiTextGate::CLogiTextGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iStyle, const char *pFileName, const char *ptext) : CLogiGate(position, name, ipage, pdoc, 0, 4, IDB_TEXT, textgate)
{
   ASSERT_VALID(this);

   Name = name;
   m_iStyle = iStyle;
   m_pTextText = ptext;
   m_csFileName = pFileName;
   m_bLoaded = FALSE;

   if (m_iStyle == 1)
   {
      Inputs = 4;
   }
   else
   {
      Inputs = 0;
   }

   Contacts = Outputs + Inputs;

   pcbGate = NULL;

   SetContacts();
}

void CLogiTextGate::ResizeRect()
{
   CDC pDC;
   pDC.CreateCompatibleDC(NULL);
   CSize csExtent;

   pOldFont = pDC.SelectObject(&m_pDocument->m_cfScreen);

   if (m_bLoaded)
   {
      csExtent = pDC.GetTextExtent( m_pTextArray[m_uIndex], m_pTextArray[m_uIndex].GetLength() ) + CSize(4,4);
   }
   else
   {
      csExtent = pDC.GetTextExtent( m_pTextText, m_pTextText.GetLength() ) + CSize(4,4);
   }

   pDC.GetTextMetrics(&tm);

   pDC.SelectObject(pOldFont);
   pDC.DeleteDC();

   if (tm.tmItalic) csExtent += CSize(tm.tmHeight/4,0);

   if (m_iStyle == 1)
   {
      csExtent += CSize((BITX_TXT-1),0);
      if (csExtent.cy < BITY_TXT) csExtent.cy = BITY_TXT;
   }

   m_position = CRect(m_position.TopLeft(), CSize(csExtent.cx, -csExtent.cy));
   m_size = csExtent;
}

void CLogiTextGate::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   CLogiGate::Serialize(ar);

   if (ar.IsStoring())
   {
      ar << m_iStyle;
      ar << m_csFileName;
      ar << m_pTextText;
   }
   else
   {
      ar >> m_iStyle;
      ar >> m_csFileName;
      ar >> m_pTextText;

      SetContacts();
   }

   //   CLogiGate::Serialize(ar);

   if (!ar.IsStoring())
   {
      ResizeRect();
   }
}

void CLogiTextGate::Draw(CDC* pDC, CLogiView* pView)
{
   ASSERT_VALID(this);

   // Draw the Bitmap Portion

   if (m_iStyle == 1)
   {
      CRect crBackup = m_position;
      CSize csBackup = m_size;

      m_position = CRect(m_position.TopLeft(), CSize(BITX_TXT, -BITY_TXT));
      m_size = CSize(BITX_TXT, BITY_TXT);

      CLogiGate::Draw(pDC, pView);

      m_position = crBackup;
      m_size     = csBackup;
   }

   // if printing build a bitmap on the fly for the Text.

   if (pDC->IsPrinting() || m_pDocument->m_iZoom)
   {
      CDC MemDC;

      MemDC.CreateCompatibleDC(NULL);

      pOldFont = MemDC.SelectObject(&m_pDocument->m_cfScreen);
      pOldPen = MemDC.SelectObject(&m_pDocument->m_cpBlack);
      pOldBrush = MemDC.SelectObject(&m_pDocument->m_cbWhite);
      int oldBkMode = MemDC.SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = MemDC.SetTextColor(RGB(0, 0, 0));

      // calculate the surrounding rectangle of the text only

      CSize csExtent;

      if (m_bLoaded)
      {
         csExtent = MemDC.GetTextExtent( m_pTextArray[m_uIndex], m_pTextArray[m_uIndex].GetLength() ) + CSize(4,4);
      }
      else
      {
         csExtent = MemDC.GetTextExtent( m_pTextText, m_pTextText.GetLength() ) + CSize(4,4);
      }

      MemDC.GetTextMetrics(&tm);
      if (tm.tmItalic) csExtent += CSize(tm.tmHeight/4,0);

      // crate a temperary bitmap to draw the text to (can't be MemDC?)

      CBitmap cbGate;

      CDC screenDC;
      screenDC.CreateDC("DISPLAY", NULL, NULL, NULL);
      cbGate.CreateCompatibleBitmap(&screenDC, csExtent.cx, csExtent.cy);
      screenDC.DeleteDC();

      pOldBmp = MemDC.SelectObject(&cbGate);

      // draw rectangle also inits bitmap with brush

      MemDC.Rectangle(CRect(CPoint(0,0),csExtent));

      // draw text

      if (m_bLoaded)
      {
         MemDC.TextOut(2, 2, m_pTextArray[m_uIndex], m_pTextArray[m_uIndex].GetLength());
      }
      else
      {
         MemDC.TextOut(2, 2, m_pTextText, m_pTextText.GetLength());
      }

      MemDC.SelectObject(pOldPen);
      MemDC.SelectObject(pOldBrush);
      MemDC.SetTextColor(oldTextColor);
      MemDC.SetBkMode(oldBkMode);
      MemDC.SelectObject(pOldFont);
      MemDC.SelectObject(pOldBmp);

      // build a DIB from the bitmap

      m_Bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      m_Bmi.bmiHeader.biHeight = csExtent.cy;
      m_Bmi.bmiHeader.biWidth = csExtent.cx;
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

      // determine where to draw the dib

      CPoint origin;

      if (m_iStyle == 1)
      {
         origin = CPoint(m_position.left+(BITX_TXT-1), m_position.top-csExtent.cy);
      }
      else
      {
         origin = CPoint(m_position.left, m_position.bottom);
      }

      // draw it

      ::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y, csExtent.cx, csExtent.cy, 0, 0, m_Bmi.bmiHeader.biWidth, m_Bmi.bmiHeader.biHeight, lpImage, (LPBITMAPINFO) &m_Bmi, DIB_RGB_COLORS, SRCCOPY);

      delete [] lpImage;
   }

   // Else not printing do direct

   else
   {
      pOldPen = pDC->SelectObject(&m_pDocument->m_cpBlack);
      pOldFont = pDC->SelectObject(&m_pDocument->m_cfScreen);
      pOldBrush = pDC->SelectObject(&m_pDocument->m_cbWhite);
      int oldBkMode = pDC->SetBkMode(TRANSPARENT);
      COLORREF oldTextColor = pDC->SetTextColor(RGB(0, 0, 0));

      // calculate the surrounding rectangle of text only

      CSize csExtent;

      if (m_bLoaded)
      {
         csExtent = pDC->GetTextExtent(m_pTextArray[m_uIndex], m_pTextArray[m_uIndex].GetLength() ) + CSize(4,4);
      }
      else
      {
         csExtent = pDC->GetTextExtent(m_pTextText, m_pTextText.GetLength() ) + CSize(4,4);
      }

      pDC->GetTextMetrics(&tm);
      if (tm.tmItalic) csExtent += CSize(tm.tmHeight/4,0);

      // determine where to draw things

      CPoint origin;

      if (m_iStyle == 1)
      {
         origin = CPoint(m_position.left+(BITX_TXT-1), m_position.top-csExtent.cy);
      }
      else
      {
         origin = CPoint(m_position.left, m_position.bottom);
      }

      pDC->Rectangle(CRect(origin,csExtent));

      if (m_bLoaded)
      {
         pDC->TextOut(origin.x+2, origin.y+2, m_pTextArray[m_uIndex], m_pTextArray[m_uIndex].GetLength());
      }
      else
      {
         pDC->TextOut(origin.x+2, origin.y+2, m_pTextText, m_pTextText.GetLength());
      }

      pDC->SelectObject(pOldFont);
      pDC->SelectObject(pOldPen);
      pDC->SetTextColor(oldTextColor);
      pDC->SelectObject(pOldBrush);
      pDC->SetBkMode(oldBkMode);
   }
}

void CLogiTextGate::Animate(CLogiView* pView)
{

   // Draw Device in its current state (BitMap ID held in GateID)

   if (m_iStyle == 1)
   {
      pView->InvalObj(this);
      ResizeRect();
      pView->InvalObj(this);
   }
}

void CLogiTextGate::Initialize(CLogiView* pView, UINT iMode)
{
   if (m_iStyle == 1)
   {
      m_bLoaded = FALSE;

      pView->InvalObj(this);
      ResizeRect();
      pView->InvalObj(this);

      for (int i=0;i<16;i++) m_pTextArray[i].Empty();

      CLogiGate::Initialize(pView, iMode);
      pView->GetDocument()->EventQueue.AddTail(this);
   }
}

void CLogiTextGate::Simulate(CLogiDoc* pDoc)
{

   // Perform Simulation

   if (m_iStyle == 1)
   {

      UINT uTemp = 0;

      for (int i=0;i<4;i++)
      {
         switch ((Node[i])->State)
         {
         case HI: uTemp |= 1<<i; break;
         case UNKNOWN: uTemp = 16; goto NOWAY;
         }
      }

NOWAY:

      m_uIndex = uTemp;

      if (!m_bLoaded)
      {
         CStdioFile cf;

         CString csFullPath;
         CString csPathName = m_pDocument->GetPathName();

         RelativeToFullPath(m_csFileName, csPathName, csFullPath);

         if (!cf.Open(csFullPath, CFile::modeRead | CFile::shareDenyWrite))
         {
            ::MessageBox(::GetFocus(), csFullPath, "Could not open File", MB_OK | MB_ICONEXCLAMATION);
            pDoc->Halt();
            //            pDoc->m_bKeepGoing = FALSE;
            return;
         }

         for (int i=0;i<16;i++) if (!cf.ReadString(m_pTextArray[i])) break;

         m_bLoaded = TRUE;

         m_pTextArray[16] = "Unknown";

         cf.Close();
      }
   }
}

// SetContacts
void CLogiTextGate::SetContacts(void)
{
   int i;

   // compute new contact points

   for (i=0;i<Contacts;i++) Contact[i] = m_position.TopLeft();

   Contact[0].x += CONTACT_X_IN;
   Contact[0].y -= CONTACT_Y_1;
   Contact[1].x += CONTACT_X_IN;
   Contact[1].y -= CONTACT_Y_2;
   Contact[2].x += CONTACT_X_IN;
   Contact[2].y -= CONTACT_Y_3;
   Contact[3].x += CONTACT_X_IN;
   Contact[3].y -= CONTACT_Y_4;
}

BOOL CLogiTextGate::HasText()
{
   return TRUE;
}

CString CLogiTextGate::GetText()
{
   return m_pTextText;
}

void CLogiTextGate::SetText(LPCTSTR text)
{
   m_pTextText = text;
   Invalidate();
}

void CLogiTextGate::MoveTo(const CRect& position, CLogiView* pView)
{

   CLogiObj::MoveTo(position, pView);

   SetContacts();
   ResizeRect();

   CLogiGate::MoveTo(position, pView);

}

// rect must be in logical coordinates
CLogiObj* CLogiTextGate::Clone(CLogiDoc* pDoc)
{
   ASSERT_VALID(this);

   CLogiTextGate* pClone = new CLogiTextGate(m_position, "TEXT", m_iPage, pDoc, m_iStyle, m_csFileName, m_pTextText);

   ASSERT_VALID(pClone);

   if (pDoc != NULL) pDoc->Add(pClone);

   ASSERT_VALID(pClone);
   return pClone;
}

void CLogiTextGate::OnOpen(CLogiView* pView)
{
   ASSERT_VALID(this);

   CTextDlg dlg;

   dlg.m_pTextText = m_pTextText;
   dlg.m_csFileName = m_csFileName;
   dlg.m_iStyle = m_iStyle;
   dlg.m_csPathName = pView->GetDocument()->GetPathName();

   if (dlg.DoModal() != IDOK) return;

   pView->GetDocument()->BeginManualEdit(this); // for undo system

   if (m_iStyle != dlg.m_iStyle)
   {
      for (int i=0;i<Contacts;i++)
      {
         if (Node[i] != m_pDocument->m_pAnodeNULL)
         {
            pView->MessageBox("Device cannot be connected when changing number of inputs", "Error");
            return;
         }
      }

      for (/*jal int */  i=0;i<4;i++) Node[i] = m_pDocument->m_pAnodeNULL;
   }

   m_pTextText = dlg.m_pTextText;
   m_csFileName = dlg.m_csFileName;
   m_iStyle = dlg.m_iStyle;

   if (m_iStyle == 1)
   {
      Inputs = 4;
   }
   else
   {
      Inputs = 0;
   }

   Contacts = Outputs + Inputs;

   Invalidate();
   ResizeRect();
   Invalidate();

   SetContacts();
   m_pDocument->SetModifiedFlag();
}

/////////////////////////////////////////////////////////////////////////////
