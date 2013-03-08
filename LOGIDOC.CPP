// Logidoc.cpp : implementation of the CLogiDoc class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//Now AnodeNULL is now document specific. Use
// pLogiObj->m_pDocument->m_pAnodeNULL or
// pView->GetDocument()->m_pAnodeNULL to access.
//Anode AnodeNULL(UNKNOWN,"xyz",FLOAT);

/////////////////////////////////////////////////////////////////////////////
// CLogiDoc

IMPLEMENT_DYNCREATE(CLogiDoc, CDocument)

BEGIN_MESSAGE_MAP(CLogiDoc, CDocument)
   //{{AFX_MSG_MAP(CLogiDoc)
   ON_COMMAND(ID_VIEW_PAPERCOLOR, OnViewPaperColor)
   ON_COMMAND(ID_SIMULATE_RUN, OnSimulateRun)
   ON_COMMAND(ID_SIMULATE_SETUP, OnSimulateSetup)
   ON_COMMAND(ID_SIMULATE_STOP, OnSimulateStop)
   ON_UPDATE_COMMAND_UI(ID_SIMULATE_RUN, OnUpdateSimulateRun)
   ON_UPDATE_COMMAND_UI(ID_SIMULATE_SETUP, OnUpdateSimulateSetup)
   ON_UPDATE_COMMAND_UI(ID_SIMULATE_STOP, OnUpdateSimulateStop)
   ON_COMMAND(ID_VIEW_PALETTE, OnSimulateDraw)
   ON_UPDATE_COMMAND_UI(ID_VIEW_PALETTE, OnUpdateSimulateDraw)
   ON_COMMAND(ID_SIMULATE_DRAW, OnSimulateDraw)
   ON_UPDATE_COMMAND_UI(ID_SIMULATE_DRAW, OnUpdateSimulateDraw)
   ON_COMMAND(ID_SIMULATE_PAUSE, OnSimulatePause)
   ON_UPDATE_COMMAND_UI(ID_SIMULATE_PAUSE, OnUpdateSimulatePause)
   ON_COMMAND(ID_SIMULATE_STEP, OnSimulateStep)
   ON_UPDATE_COMMAND_UI(ID_SIMULATE_STEP, OnUpdateSimulateStep)
   ON_COMMAND(ID_SIMULATE_RESET, OnSimulateReset)
   ON_UPDATE_COMMAND_UI(ID_SIMULATE_RESET, OnUpdateSimulateReset)
   ON_COMMAND(ID_SIMULATE_PROBE, OnSimulateProbe)
   ON_UPDATE_COMMAND_UI(ID_SIMULATE_PROBE, OnUpdateSimulateProbe)
   ON_COMMAND(ID_VIEW_GRID, OnViewGrid)
   ON_UPDATE_COMMAND_UI(ID_VIEW_GRID, OnUpdateViewGrid)
   ON_COMMAND(ID_SIMULATE_ANALYZE, OnSimulateAnalyze)
   ON_UPDATE_COMMAND_UI(ID_SIMULATE_ANALYZE, OnUpdateSimulateAnalyze)
   ON_COMMAND(ID_VIEW_ZOOM_IN, OnViewZoomIn)
   ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_IN, OnUpdateViewZoomIn)
   ON_COMMAND(ID_VIEW_ZOOM_NORMAL, OnViewZoomNormal)
   ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_NORMAL, OnUpdateViewZoomNormal)
   ON_COMMAND(ID_VIEW_ZOOM_OUT, OnViewZoomOut)
   ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_OUT, OnUpdateViewZoomOut)
   ON_COMMAND(ID_VIEW_SNAPTOGRID, OnViewSnapToGrid)
   ON_UPDATE_COMMAND_UI(ID_VIEW_SNAPTOGRID, OnUpdateViewSnapToGrid)
   ON_COMMAND(ID_VIEW_COLORWIRES, OnViewColorWires)
   ON_UPDATE_COMMAND_UI(ID_VIEW_COLORWIRES, OnUpdateViewColorWires)
   ON_COMMAND(ID_ESCAPE, OnEscape)

   //}}AFX_MSG_MAP
   ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogiDoc construction/destruction

CLogiDoc::CLogiDoc()
{
   LOGFONT lf;

   m_iZoom = 0;
   m_bGrid = TRUE;
   m_bSnapToGrid = FALSE;
   m_uGridWidth = 6;
   m_uGridHeight = 6;
   m_uCanvasWidth = XDEFAULTDOCSIZE;
   m_uCanvasHeight = YDEFAULTDOCSIZE;
   m_nMapMode = MM_TEXT;
   m_paperColor = RGB(255, 255, 255);
   m_bSimulating = FALSE;
   //TODO: Color wires should probably be an option retained from one session to another.
   m_bColorWires = FALSE;
   m_iUnconnected = 0;
   m_bKeepGoing = FALSE;
   m_bWasUp = FALSE;
   m_bPause = 0;
   m_uProbe = 0;
   m_uAnalyze = 0;
   KeyBoardObj = NULL;
   ComputePageSize();
   ::GetObject(GetStockObject(SYSTEM_FONT), sizeof(LOGFONT), &lf);
   //   if (lf.lfHeight > 0)
   //      {
   //      lf.lfHeight = -lf.lfHeight;
   //      lf.lfWidth = 0;
   //      lf.lfQuality = 1;
   //      }
   m_cfScreen.CreateFontIndirect(&lf);
   m_cpBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
   m_cpGreen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
   m_cpRed.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
   m_cpPurple.CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
   m_cbWhite.CreateSolidBrush(RGB(255, 255, 255));
   m_cpBlue.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
   m_cbBlue.CreateSolidBrush(RGB(0, 0, 255));
   m_cpGrey.CreatePen(PS_SOLID, 1, RGB(192, 192, 192));
   m_cbGrey.CreateSolidBrush(RGB(192, 192, 192));

   m_uCycleCount = 0;

   m_iVersionMajor = VERSION_MAJOR;
   m_iVersionMinor = VERSION_MINOR;

   m_bReadOnly = ((CLogiApp *)AfxGetApp())->m_bReadOnly;

   m_bSimRateSpecified = FALSE;
   m_iSimRate = DEFAULTSIMRATE;

   //   pAnodeDummy = new Anode(UNKNOWN,"xyz");
   m_pAnodeNULL = new Anode(UNKNOWN,"xyz",FLOAT);
}

CLogiDoc::~CLogiDoc()
{
   POSITION pos;
   CObject* pObj;
   CObList Temp;

   // Clear the undo/redo stack
   // (Necessary to avoid wires in the undo stack referencing
   // objects we are about to delete.)
   m_undo.Reset();

   // Copy the object list because it gets munged as we delete

   pos = m_objects.GetHeadPosition();

   while (pos != NULL)
   {
      pObj = m_objects.GetNext( pos );
      if (!pObj->IsKindOf(RUNTIME_CLASS(CLogiWire))) Temp.AddTail(pObj);
      else 
         delete pObj; // delete wires first
   }

   // Now do the deletes of non-wires

   pos = Temp.GetHeadPosition();

   while (pos != NULL)
   {
      pObj = Temp.GetNext( pos );
      delete pObj;
   }

   // Now delete nodes

   pos = NodeList.GetHeadPosition();

   while (pos != NULL)
   {
      pObj = NodeList.GetNext( pos );
      delete pObj;
   }

   // Now delete events (due to self inited devices)

   EventQueue.RemoveAll();
   PostEventQueue.RemoveAll();
   while (!KeyboardMessageQueue.IsEmpty()) delete (AKeyboardMessage*) KeyboardMessageQueue.RemoveHead();
   while (!MouseMessageQueue.IsEmpty()) delete (AMouseMessage*) MouseMessageQueue.RemoveHead();
   while (!NetworkMessageQueue.IsEmpty()) delete (ANetworkMessage*) NetworkMessageQueue.RemoveHead();
   UpdateNodeQueue.RemoveAll();
   UpdateNodeQueue2.RemoveAll();
   CallPostQueue.RemoveAll();

   m_cfScreen.DeleteObject();
   m_cpBlack.DeleteObject();
   m_cpGreen.DeleteObject();
   m_cpRed.DeleteObject();
   m_cpPurple.DeleteObject();
   m_cbWhite.DeleteObject();
   m_cpBlue.DeleteObject();
   m_cbBlue.DeleteObject();

   // Delete the default NULL node

   delete m_pAnodeNULL;
}

int CLogiDoc::GetZoom(int i)
{
   if      (m_iZoom == 0) return i;
   else if (m_iZoom  > 0) return i<<m_iZoom;
   else                   return i>>(-m_iZoom);
}

BOOL CLogiDoc::CheckForStrays()
{
   POSITION pos;
   //POSITION vpos;

   BOOL bOutSide = FALSE;

   CRect rect;
   //   rect.left = -GetSize().cx / 2;
   //   rect.top = -GetSize().cy / 2;
   rect.left   = 0;
   rect.top    = 0;
   rect.right  = rect.left + GetSize().cx;
   rect.bottom = rect.top + GetSize().cy;

   rect.NormalizeRect();

   // check each non-wire device to be fully on the page

   pos = m_objects.GetHeadPosition();
   while (pos != NULL)
   {
      CLogiObj* pObj = (CLogiObj*)m_objects.GetNext(pos);

      // only non-wires

      if (pObj->m_Logishape != wire)
      {
         CRect position = pObj->m_position;

         // if any edge of device off any edge of page then fix

         if ((position.left < rect.left)
            || (position.bottom < rect.top)
            || (position.right > rect.right)
            || (position.top > rect.bottom))
         {
            /*
            int delta;

            // fix appropriate edge

            if (position.left < rect.left)
            {
            delta = position.left - rect.left;
            position.right -= delta;
            position.left -= delta;
            }
            if (position.bottom < rect.top)
            {
            delta = position.bottom - rect.top;
            position.bottom -= delta;
            position.top -= delta;
            }
            if (position.right > rect.right)
            {
            delta = rect.right - position.right;
            position.right += delta;
            position.left += delta;
            }
            if (position.top > rect.bottom)
            {
            delta = rect.bottom - position.top;
            position.bottom += delta;
            position.top += delta;
            }

            // move it in each view

            vpos = GetFirstViewPosition();
            while (vpos != NULL)
            {
            CLogiView* pView = (CLogiView*)GetNextView(vpos);
            pObj->MoveTo(position, pView);
            pView->SetPage(pObj->m_iPage);
            pView->Select(pObj, TRUE);
            }
            */
            bOutSide = TRUE;
         }
      }
   }

   // let user know we fiddled with his work.

   if (bOutSide)
   {
      UpdateAllViews(NULL);
      //::MessageBox(::GetFocus(),"The selected devices were off page and have been moved onto the page", "Warning", MB_OK | MB_ICONEXCLAMATION);
      ::MessageBox(::GetFocus(),"Some devices are off of the page. They will not appear when printing.", "Warning", MB_OK | MB_ICONEXCLAMATION);
   }

   return bOutSide;
}

void CLogiDoc::Halt()
{
   // This method is called by CLogiGate::Initialize and CLogiGate::Simulate
   // methods if an error occurs. Now, it sets a halt flag and just delegates
   // to OnSimulateStop().

   // When halt is called the simulator might be running or it might
   // be resetting (i.e., initializing).

   // Set the halt flag (so any pending Reset() fails by returning FALSE)

   m_bHalt = TRUE;

   // If simulator running or stepping, stop it

   if (m_bKeepGoing || m_bPause)
      OnSimulateStop();
}

BOOL CLogiDoc::Reset(UINT iMode)
{
   // To properly start the simulator, the following logic must
   // be observed:
   // if (!Reset(ID_SIMULATE_RUN)) // initialize all devices
   //   Reset(ID_SIMULATE_RESET); // if error, deinitialize all devices
   // else
   //   Simulate(ID_SIMULATE_RUN); // no errors, run the simulator

   POSITION pos;
   POSITION pos2;
   POSITION vpos;
   CLogiObj* CurrentObj;
   CLogiObj* CurrentObj2;
   Anode* CurrentNode;
   CLogiView* pView = NULL;
   BOOL bWinNT;

   m_uCycleCount = 0;
   KeyBoardObj = NULL;

   if (m_bWasUp)
   {
      CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
      pMainFrm->ShowControlBar(&pMainFrm->m_wndPaletteBar, TRUE, FALSE);
      m_bWasUp = FALSE;
   }

   // Erase grid in all views because it will not be updated during simulation

   if (GetGridOn())
   {
      pos = GetFirstViewPosition();
      while (pos != NULL)
      {
         pView = (CLogiView*)GetNextView(pos);
         pView->Invalidate(FALSE);
      }
   }

   // Start with everything deselected
   // (However, do not deselect if switching to a stopped mode,
   // since simulator may have selected components having detected errors.)

   if (iMode == ID_SIMULATE_RUN || iMode == ID_SIMULATE_STEP)
   {
      vpos = GetFirstViewPosition();
      while (vpos != NULL)
      {
         pView = (CLogiView*)GetNextView(vpos);
         pView->Select(NULL);
      }
   }

   // Check for lost little souls

   //if(CheckForStrays()) return false;

   // Init all Nodes to Unknown

   for( pos = NodeList.GetHeadPosition(); pos != NULL; )
   {
      CurrentNode = (Anode*) NodeList.GetNext( pos );
      CurrentNode->State = UNKNOWN;
      CurrentNode->NextState = UNKNOWN;
      CurrentNode->PrevState = UNKNOWN;
      CurrentNode->DriveState = DRIVE;
      CurrentNode->NextDriveState = DRIVE;
      CurrentNode->PrevDriveState = DRIVE;
   }

   switch (m_iUnconnected)
   {
   case 0:
      {
         m_pAnodeNULL->State = UNKNOWN;
         m_pAnodeNULL->DriveState = DRIVE;
         break;
      }
   case 1:
      {
         m_pAnodeNULL->State = LO;
         m_pAnodeNULL->DriveState = DRIVE;
         break;
      }
   case 2:
      {
         m_pAnodeNULL->State = LO;
         m_pAnodeNULL->DriveState = FLOAT;
         break;
      }
   case 3:
      {
         m_pAnodeNULL->State = UNKNOWN;
         m_pAnodeNULL->DriveState = FLOAT;
         break;
      }
   }

   // Some of the PostSimulate devices, such as the null node
   // care about these values.

   m_pAnodeNULL->NextState = m_pAnodeNULL->State;
   m_pAnodeNULL->NextDriveState = m_pAnodeNULL->DriveState;

   m_pAnodeNULL->PrevState = m_pAnodeNULL->State;
   m_pAnodeNULL->PrevDriveState = m_pAnodeNULL->DriveState;

   // Start with a clean Queue(s)

   EventQueue.RemoveAll();
   PostEventQueue.RemoveAll();
   while (!KeyboardMessageQueue.IsEmpty()) delete (AKeyboardMessage*) KeyboardMessageQueue.RemoveHead();
   while (!MouseMessageQueue.IsEmpty()) delete (AMouseMessage*) MouseMessageQueue.RemoveHead();
   while (!NetworkMessageQueue.IsEmpty()) delete (ANetworkMessage*) NetworkMessageQueue.RemoveHead();
   UpdateNodeQueue.RemoveAll();
   UpdateNodeQueue2.RemoveAll();
   CallPostQueue.RemoveAll();

   // Initialize all devices (switches off, lights off, etc.)

   bWinNT = IsWindowsNT();

   for( pos = m_objects.GetHeadPosition(); pos != NULL; )
   {
      CurrentObj = (CLogiObj*) m_objects.GetNext( pos );

      if (CurrentObj->IsKindOf(RUNTIME_CLASS(CLogiGate)))
      {
         // Disallow port I/O gates on WinNT

         if (bWinNT && (iMode == ID_SIMULATE_RUN || iMode == ID_SIMULATE_STEP))
         {
            if (
               (CurrentObj->m_Logishape == portingate)  ||
               (CurrentObj->m_Logishape == portoutgate)
               )
            {
               vpos = GetFirstViewPosition();
               while (vpos != NULL)
               {
                  pView = (CLogiView*)GetNextView(vpos);
                  pView->SetPage(CurrentObj->m_iPage);
                  pView->Select(CurrentObj, TRUE);
               }
               ::MessageBox(::GetFocus(),"The Port In and Port Out devices do not work with Windows NT and above.\n\nSecurity features in recent versions of Windows do not allow direct access to your computer's ports.", "Error", MB_OK | MB_ICONEXCLAMATION);
               //TODO: Implement NT Port In and Out devices.
               return FALSE;         
            }
         }

         // Initialize the device

         vpos = GetFirstViewPosition();
         while (vpos != NULL)
         {
            pView = (CLogiView*)GetNextView(vpos);
            // m_bHalt is workaround since Initialize does not return a value.
            // The Halt method in this class sets this flag.
            m_bHalt = FALSE;
            ((CLogiGate *)CurrentObj)->Initialize(pView, iMode);
            if (m_bHalt && (iMode == ID_SIMULATE_RUN || iMode == ID_SIMULATE_STEP))
               return FALSE; 
         }
      }
   }

   PlaySound(NULL, NULL, SND_PURGE);

   NetworkShutdown();


   // No need to do anything further if RESETting.
   if (iMode != ID_SIMULATE_RUN && iMode != ID_SIMULATE_STEP)
      return TRUE;

   // Queue up all self generating devices (oscillators)

   for( pos = m_objects.GetHeadPosition(); pos != NULL; )
   {
      CurrentObj= (CLogiObj*) m_objects.GetNext( pos );
      if (CurrentObj->IsKindOf(RUNTIME_CLASS(CLogiGate)))
      {
         if (
            (CurrentObj->m_Logishape == oscillatorgate)    ||
            (CurrentObj->m_Logishape == switchgate)        ||
            (CurrentObj->m_Logishape == selectgate)        ||
            (CurrentObj->m_Logishape == groundgate)        ||
            (CurrentObj->m_Logishape == plusgate)          ||
            (CurrentObj->m_Logishape == asciikeyboardgate) ||
            (CurrentObj->m_Logishape == keypadgate)        ||
            (CurrentObj->m_Logishape == clockgate)         ||
            (CurrentObj->m_Logishape == portingate)
            )
         {
            EventQueue.AddTail(CurrentObj);
         }
      }
   }

   // Queue up PostSimulate devices for the first cycle.
   // Afterwards these devices enqueue themselves if input changes.

   for( pos = m_objects.GetHeadPosition(); pos != NULL; )
   {
      CurrentObj = (CLogiObj*) m_objects.GetNext( pos );
      if (CurrentObj->IsKindOf(RUNTIME_CLASS(CLogiGate)))
      {
         if (
            (CurrentObj->m_Logishape == nullgate)         ||
            (CurrentObj->m_Logishape == busgate)          ||
            (CurrentObj->m_Logishape == signalsendergate)
            )
         {
            CallPostQueue.AddTail(CurrentObj);
         }
      }
   }


   // Init all Robots and Playgrounds

   for( pos = m_objects.GetHeadPosition(); pos != NULL; )
   {
      CurrentObj = (CLogiObj*) m_objects.GetNext( pos );

      if (CurrentObj->m_Logishape == robotgate)
      {
         ((CLogiRobotGate*) CurrentObj)->m_Playground = NULL;
      }
      else if (CurrentObj->m_Logishape == bitmapgate)
      {
         if (((CLogiBitmapGate*) CurrentObj)->m_bPlayground)
         {
            for (int i=0;i<16;i++) ((CLogiBitmapGate*) CurrentObj)->m_Robot[i] = NULL;
         }
      }
   }

   // Pair Robots and Playgrounds

   for( pos = m_objects.GetHeadPosition(); pos != NULL; )
   {
      CurrentObj = (CLogiObj*) m_objects.GetNext( pos );

      if (CurrentObj->m_Logishape == robotgate)
      {

         // Try robots on same page first

         for( pos2 = m_objects.GetHeadPosition(); pos2 != NULL; )
         {
            CurrentObj2 = (CLogiObj*) m_objects.GetNext( pos2 );

            if (CurrentObj2->m_Logishape == bitmapgate)
            {
               if ((((CLogiBitmapGate*) CurrentObj2)->m_bPlayground) && (CurrentObj->m_iPage == CurrentObj2->m_iPage ))
               {
                  for (int i=0;i<16;i++)
                  {
                     if (((CLogiBitmapGate*) CurrentObj2)->m_Robot[i] == NULL)
                     {
                        ((CLogiBitmapGate*) CurrentObj2)->m_Robot[i] = (CLogiRobotGate*) CurrentObj;
                        ((CLogiRobotGate*) CurrentObj)->m_Playground = (CLogiBitmapGate*) CurrentObj2;
                        pos2 = NULL;
                        break;
                     }
                  }
               }
            }
         }

         // If still no home, try on any page

         if (((CLogiRobotGate*) CurrentObj)->m_Playground == NULL)
         {
            for( pos2 = m_objects.GetHeadPosition(); pos2 != NULL; )
            {
               CurrentObj2 = (CLogiObj*) m_objects.GetNext( pos2 );

               if (CurrentObj2->m_Logishape == bitmapgate)
               {
                  if (((CLogiBitmapGate*) CurrentObj2)->m_bPlayground)
                  {
                     for (int i=0;i<16;i++)
                     {
                        if (((CLogiBitmapGate*) CurrentObj2)->m_Robot[i] == NULL)
                        {
                           ((CLogiBitmapGate*) CurrentObj2)->m_Robot[i] = (CLogiRobotGate*) CurrentObj;
                           ((CLogiRobotGate*) CurrentObj)->m_Playground = (CLogiBitmapGate*) CurrentObj2;
                           pos2 = NULL;
                           break;
                        }
                     }
                  }
               }
            }
         }

         // if still no home select robot and let user know

         if (((CLogiRobotGate*) CurrentObj)->m_Playground == NULL)
         {
            vpos = GetFirstViewPosition();
            while (vpos != NULL)
            {
               pView = (CLogiView*)GetNextView(vpos);
               pView->SetPage(CurrentObj->m_iPage);
               pView->Select(CurrentObj, TRUE);
            }
            ::MessageBox(::GetFocus(),"The selected Robot has no Bitmap Playground", "Error", MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
         }
      }
   }

   // Pair Signal Senders and Signal Receivers (init pointers first)

   for( pos = m_objects.GetHeadPosition(); pos != NULL; )
   {
      CurrentObj = (CLogiObj*) m_objects.GetNext( pos );

      // init sender or receiver mates'

      if (CurrentObj->m_Logishape == signalsendergate)
      {
         ((CLogiSignalsenderGate*) CurrentObj)->m_Mates.RemoveAll();
      }
      else if (CurrentObj->m_Logishape == signalreceivergate)
      {
         ((CLogiSignalreceiverGate*) CurrentObj)->m_Mate = NULL;
      }
   }

   CObList receivers;
   CObList sendersSatisfied;

   // make list of all receivers
   for (pos = m_objects.GetHeadPosition(); pos != NULL; )
   {
      CurrentObj2 = (CLogiObj*) m_objects.GetNext(pos);
      if (CurrentObj2->m_Logishape == signalreceivergate)
         receivers.AddTail(CurrentObj2);
   }


   // now look for senders
   for (pos = m_objects.GetHeadPosition(); pos != NULL; )
   {
      CurrentObj = (CLogiObj*) m_objects.GetNext(pos);

      if (CurrentObj->m_Logishape == signalsendergate)
      {
         CString signalname = ((CLogiSignalsenderGate*) CurrentObj)->m_csSignalName;
         // find receiver(s)
         for (pos2 = receivers.GetHeadPosition(); pos2 != NULL; )
         {
            POSITION thispos = pos2;
            CurrentObj2 = (CLogiObj*) receivers.GetNext(pos2);
            if (((CLogiSignalreceiverGate*) CurrentObj2)->m_csSignalName == signalname)
            {
               // add
               ((CLogiSignalsenderGate*) CurrentObj)->m_Mates.AddTail(CurrentObj2);
               receivers.RemoveAt(thispos);
            }
         }

         // sender with no receivers?
         if (((CLogiSignalsenderGate*) CurrentObj)->m_Mates.IsEmpty())
         {
            vpos = GetFirstViewPosition();
            while (vpos != NULL)
            {
               pView = (CLogiView*)GetNextView(vpos);
               pView->SetPage(CurrentObj->m_iPage);
               pView->Select(CurrentObj, TRUE);
            }

            // is this because we previously satisfied a duplicate receiver,
            // or because there is no such named receiver
            for (pos2 = sendersSatisfied.GetHeadPosition(); pos2 != NULL ;)
            {
               CurrentObj2 = (CLogiObj*) sendersSatisfied.GetNext(pos2);
               if (((CLogiSignalsenderGate*) CurrentObj2)->m_csSignalName == signalname)
               {
                  pView->Select(CurrentObj2, TRUE);
                  ::MessageBox(::GetFocus(),"The selected Signal Senders have the same name", "Error", MB_OK | MB_ICONEXCLAMATION);
                  return FALSE;
               }
            }

            ::MessageBox(::GetFocus(),"The selected Signal Sender has no Receiver", "Error", MB_OK | MB_ICONEXCLAMATION);
            return FALSE;
         }

         // done handling this sender
         sendersSatisfied.AddTail(CurrentObj);
      }
   }

   // leftover receivers without senders?
   if (!receivers.IsEmpty())
   {
      CurrentObj = (CLogiObj*) receivers.GetHead();
      vpos = GetFirstViewPosition();
      while (vpos != NULL)
      {
         pView = (CLogiView*)GetNextView(vpos);
         pView->SetPage(CurrentObj->m_iPage);
         pView->Select(CurrentObj, TRUE);
      }
      ::MessageBox(::GetFocus(),"The selected Signal Receiver has no Sender", "Error", MB_OK | MB_ICONEXCLAMATION);
      return FALSE;        
   }

   // Add marker event

   EventQueue.AddTail((CObject*) NULL);

   return TRUE;
}

void CLogiDoc::UpdateProbe()
{
   switch (pAnodeProbe->PrevDriveState)
   {
   case DRIVE:
      {
         switch (pAnodeProbe->PrevState)
         {
         case LO:
            {
               m_uProbe = IDC_PROBE_OFF;
               SetCursor(AfxGetApp()->LoadCursor(m_uProbe));
               break;
            }
         case HI:
            {
               m_uProbe = IDC_PROBE_ON;
               SetCursor(AfxGetApp()->LoadCursor(m_uProbe));
               break;
            }
         case UNKNOWN:
            {
               m_uProbe = IDC_PROBE_UNKNOWN;
               SetCursor(AfxGetApp()->LoadCursor(m_uProbe));
               break;
            }
         }
         break;
      }
   case FLOAT:
      {
         switch (pAnodeProbe->PrevState)
         {
         case LO:
            {
               m_uProbe = IDC_PROBE_MINUS;
               SetCursor(AfxGetApp()->LoadCursor(m_uProbe));
               break;
            }
         case HI:
            {
               m_uProbe = IDC_PROBE_PLUS;
               SetCursor(AfxGetApp()->LoadCursor(m_uProbe));
               break;
            }
         case UNKNOWN:
            {
               m_uProbe = IDC_PROBE_FLOAT;
               SetCursor(AfxGetApp()->LoadCursor(m_uProbe));
               break;
            }
         }
         break;
      }
   }
}

void CLogiDoc::Simulate(UINT iMode)
{
   // To properly start the simulator, the following logic must
   // be observed:
   // if (!Reset(ID_SIMULATE_RUN)) // initialize all devices
   //   Reset(ID_SIMULATE_RESET); // if error, deinitialize all devices
   // else
   //   Simulate(ID_SIMULATE_RUN); // no errors, run the simulator

   POSITION pos;
   POSITION pos2;
   CLogiGate* CurrentEventGate;
   AKeyboardMessage* CurrentKeyboardMessage;
   AMouseMessage* CurrentMouseMessage;
   ANetworkMessage* CurrentNetworkMessage;
   Anode* CurrentNode;
   MSG msg;
   CLogiView* pView;
   unsigned int uCurrentTime;
   unsigned int uWorkUnitStartTime;  // when was unit of work started? (micro seconds)
   int iWorkUnitExpectedTimeuS; // how much time is work unit supposed to take?
   unsigned int uuSPerCycle = 0; // how many microseconds per cycle to keep desired rate?

   // Set all views to select mode
   // We call the "internal" version of the command because
   // the usual version is already disabled at this point.

   AfxGetApp()->m_pMainWnd->SendMessage(WM_COMMAND, ID_DRAW_SELECTOR_INTERNAL, 0L);

   m_bKeepGoing = TRUE;
   m_bForceStopAndExitApp = FALSE;
   m_bForceStopAndCloseDoc = FALSE;
   m_bCloseNotExit = FALSE;
   m_bForceStopAndChangeDoc = FALSE;

   // If palette is up shut it down on 1st cycle

   if (m_uCycleCount == 0)
   {
      m_bWasUp = FALSE;

      CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();

      if ((pMainFrm->m_wndPaletteBar.GetStyle() & WS_VISIBLE) != 0)
      {
         pMainFrm->ShowControlBar(&pMainFrm->m_wndPaletteBar, FALSE, FALSE);
         m_bWasUp = TRUE;
      }
   }

   // Compute microseconds to spend per cycle

   if (m_bSimRateSpecified)
      uuSPerCycle = 1000000/m_iSimRate;

   uCurrentTime = GetCurrentTime();

   // While User Allows Simulation to Continue, do so

   uWorkUnitStartTime = GetTickCount();
   iWorkUnitExpectedTimeuS = 0; // no work done yet

   while (m_bKeepGoing)
   {
      // Simulate a Cycle (until a NULL "Marker" is seen)

      while (1)
      {
         // Get and remove the event

         CurrentEventGate = (CLogiGate*) EventQueue.RemoveHead();

         // if NULL "Marker" then end of Cycle

         if (CurrentEventGate == NULL)
         {
            break;
         }

         // Perform Simulation for this device

         CurrentEventGate->Simulate(this);
         // Check for Halt() call by Simulate
         // This is a hack because Simulate does not return a value
         if (!m_bKeepGoing)
            break;

         // Now Animate the Device in all Views

         pos = GetFirstViewPosition();
         while (pos != NULL)
         {
            pView = (CLogiView*)GetNextView(pos);
            if (pView->m_iPage == CurrentEventGate->m_iPage)
            {
               CurrentEventGate->Animate(pView);
            }
         }
      }

      // If any keyboard events then process just one
      //TODO: Look here for hotkeys while simulating?
      if (!KeyboardMessageQueue.IsEmpty())
      {

         CurrentKeyboardMessage = (AKeyboardMessage*) KeyboardMessageQueue.RemoveHead();

         ((CLogiAsciikeyboardGate *) CurrentKeyboardMessage->pLogiGate)->Message(CurrentKeyboardMessage->pView, CurrentKeyboardMessage->nChar, CurrentKeyboardMessage->bDown);

         delete CurrentKeyboardMessage;
      }

      // If any mouse events (actions) then process just one

      if (!MouseMessageQueue.IsEmpty())
      {

         CurrentMouseMessage = (AMouseMessage*) MouseMessageQueue.RemoveHead();

         CurrentMouseMessage->pLogiGate->Action(CurrentMouseMessage->pView, CurrentMouseMessage->bDown, CurrentMouseMessage->aPoint);

         delete CurrentMouseMessage;
      }

      // If any network events then process just one (of each device)

      if (!NetworkMessageQueue.IsEmpty())
      {
         for( pos = NetworkMessageQueue.GetHeadPosition(); pos != NULL; )
         {
            CurrentNetworkMessage = (ANetworkMessage*) NetworkMessageQueue.GetNext( pos );

            ((CLogiNetworkGate *) CurrentNetworkMessage->pLogiGate)->m_bQueue = FALSE;
         }

         for( pos = NetworkMessageQueue.GetHeadPosition(); pos != NULL; )
         {
            pos2 = pos;

            CurrentNetworkMessage = (ANetworkMessage*) NetworkMessageQueue.GetNext( pos );

            if (!((CLogiNetworkGate *) CurrentNetworkMessage->pLogiGate)->m_bQueue)
            {
               ((CLogiNetworkGate *) CurrentNetworkMessage->pLogiGate)->m_bQueue = TRUE;
               ((CLogiNetworkGate *) CurrentNetworkMessage->pLogiGate)->Message(CurrentNetworkMessage->pDoc, CurrentNetworkMessage->lParam, CurrentNetworkMessage->wParam);

               NetworkMessageQueue.RemoveAt(pos2);
               delete CurrentNetworkMessage;
            }
         }
      }

      // Process PostEvents

      // Copy "NextState" of Signal Senders input to Signal Receivers Output
      // Copy "NextState" of Node input to Node Output

      BOOL bChanged = TRUE;

      while (bChanged)
      {
         bChanged = FALSE;

         // These are objects that PostSimulate is always called on

         for( pos = PostEventQueue.GetHeadPosition(); pos != NULL; )
         {
            CurrentEventGate = (CLogiGate*) PostEventQueue.GetNext( pos );

            if (CurrentEventGate->PostSimulate(this)) bChanged = TRUE;
         }
      }

      // These objects have indicated they need PostSimulate by
      // enqueueing themselves

      while (!CallPostQueue.IsEmpty())
      {
         CurrentEventGate = (CLogiGate*) CallPostQueue.RemoveHead();
         CurrentEventGate->PostSimulate(this);
      }

      // Add NULL cycle "marker"

      EventQueue.AddTail((CLogiGate*) NULL);

      // Transfer Nodes from "Current" State to "Previous" State

      while (!UpdateNodeQueue2.IsEmpty())
      {
         CurrentNode = (Anode *) UpdateNodeQueue2.RemoveHead();
         CurrentNode->Update();
         CurrentNode->LastCycle = m_uCycleCount;
      }

      // Transfer "Next" Node states to "Current" State

      while (!UpdateNodeQueue.IsEmpty())
      {
         CurrentNode = (Anode *) UpdateNodeQueue.RemoveHead();
         // Must only call Update once per cycle
         if (CurrentNode->LastCycle != m_uCycleCount)
         {
            CurrentNode->Update();
            CurrentNode->LastCycle = m_uCycleCount;
         }

         // We store 1 cycle of previous state, so queue
         // an additional update
         UpdateNodeQueue2.AddTail(CurrentNode);
      }

      //color wires
      if(m_bColorWires)
      {
         // call update for each view, to draw the new wire colors
         POSITION pos = GetFirstViewPosition();
         while (pos != NULL)  ((CLogiView*)GetNextView(pos))->OnUpdate(NULL, HINT_UPDATE_WINDOW, NULL);
      }

      // Tally Cycle Count

      if (m_uCycleCount == LONG_MAX)
         m_uCycleCount = 0;
      else
         m_uCycleCount++;

      if (m_uProbe != 0)
      {
         if (m_uProbe != IDC_PROBE_NULL)
         {
            UpdateProbe();
         }
      }

      // Yield to other processes including Our self
      while (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
      {
         TranslateMessage ( &msg );
         DispatchMessage ( &msg );
      }

      if ((GetCurrentTime() - uCurrentTime) > 100)
      {
         AfxGetApp()->OnIdle(0);
         uCurrentTime = GetCurrentTime();
      }

      // Accumulate the time the cycle is supposed to take
      iWorkUnitExpectedTimeuS += uuSPerCycle;

      unsigned int currentTick = GetTickCount();

      if (iMode == ID_SIMULATE_STEP) 
         m_bKeepGoing = FALSE;
      else if (m_bSimRateSpecified)
      {
         if (currentTick < uWorkUnitStartTime)
         {
            // System clock wraparound, must reset
            // Note that this is a very rare event
            uWorkUnitStartTime = GetTickCount();
            iWorkUnitExpectedTimeuS = 0; 
         }
         else if (iWorkUnitExpectedTimeuS > 0 && (signed int)(currentTick - uWorkUnitStartTime)*1000 >= iWorkUnitExpectedTimeuS)
         {
            // Running too slow, reset the time
            // so any momentary stall won't backlog forever
            uWorkUnitStartTime = GetTickCount();
            iWorkUnitExpectedTimeuS = 0;
         }
         else if (iWorkUnitExpectedTimeuS - (signed int)(currentTick - uWorkUnitStartTime)*1000 >= 100000)
         {
            // Give credit for time actually taken
            iWorkUnitExpectedTimeuS -= (currentTick - uWorkUnitStartTime)*1000;
            uWorkUnitStartTime = GetTickCount();      

            unsigned int waitUntilTick = currentTick + iWorkUnitExpectedTimeuS / 1000;

            while (GetTickCount() < waitUntilTick && m_bKeepGoing)
            {
               // Waste time until ready for next cycle
               while (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
               {
                  TranslateMessage ( &msg );
                  DispatchMessage ( &msg );
               }

               if ((GetCurrentTime() - uCurrentTime) > 100)
               {
                  AfxGetApp()->OnIdle(0);
                  uCurrentTime = GetCurrentTime();
               }
            } 

            // Give credit for time spent in loop
            // iWorkUnitExpectedTimeuS can go negative if
            // the loop took too long. This is okay and desired
            // to keep the timing fairly accurate.
            currentTick = GetTickCount();
            iWorkUnitExpectedTimeuS -= (currentTick-uWorkUnitStartTime)*1000;
            // And start a new frame of reference
            uWorkUnitStartTime = currentTick; 
         }
      }
   }
}

BOOL CLogiDoc::OnNewDocument()
{
   if (!CDocument::OnNewDocument()) return FALSE;

   // TODO: add reinitialization code here
   // (SDI documents will reuse this document)

   return TRUE;
}

CLogiWire* CLogiDoc::ReWire(const CRect& rect, CLogiWire* pWireObj, int iPage)
{
   CLogiGate* pStartGateObj;
   CLogiGate* pEndGateObj;
   Anode* pStartAnode;
   Anode* pEndAnode;
   //   CLogiWire* pWireObj;

   int StartIO;
   int EndIO;

   CRect rectT = rect;

   // Find out if we hit a gate contact if so return contact
   pStartGateObj = (CLogiGate*)ObjectAtContactExact(rectT.BottomRight(), &StartIO, iPage);
   if (pStartGateObj == NULL)
   {
      ::MessageBox(::GetFocus(),"Bad Wire found at StartGate, skipping.","Error", MB_OK | MB_ICONEXCLAMATION);
      ((CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR))->SetPaneText(0, "Bad Wire found at StartGate, skipping.");
      return NULL;
   }

   // if pAnode is NULL and StartIO is an input this means we must create a new node
   pStartAnode = pStartGateObj->Node[StartIO];
   if ((pStartAnode == m_pAnodeNULL) && (StartIO < pStartGateObj->Outputs)) NodeList.AddHead(pStartAnode = new Anode(UNKNOWN,"xyz",DRIVE));

   //Now do other End
   pEndGateObj = (CLogiGate*)ObjectAtContactExact(rectT.TopLeft(), &EndIO, iPage);
   if (pEndGateObj == NULL)
   {
      ::MessageBox(::GetFocus(),"Bad Wire found at EndGate, skipping.","Error", MB_OK | MB_ICONEXCLAMATION);
      ((CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR))->SetPaneText(0, "Bad Wire found at EndGate, skipping.");
      return NULL;
   }

   // if pAnode is NULL and EndIO is an input this means we must create a new node
   pEndAnode = pEndGateObj->Node[EndIO];
   if ((pEndAnode == m_pAnodeNULL) && (EndIO < pEndGateObj->Outputs)) NodeList.AddHead(pEndAnode = new Anode(UNKNOWN,"xyz",DRIVE));

   // Create wire
   if (pWireObj == NULL)
   {
      pWireObj = new CLogiWire(rect, "Wire", iPage, this);
      Add(pWireObj);
   }

   // if both nodes then do special procesing
   if ((pEndGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate)))
      && (pStartGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate))))
   {
      /*
      * This if statement is sort of sloppy, and has some odd consequences. 
      * It used to be that this block would actively break wires that, to the user, seem fine. 
      * It is now mostly fixed, but there still may be cases that break this. 
      *   I've gotten a heap error since making this change, but have been unable to reproduce it.
      */
      // if endgate's output connected and input not then switch to input
      if ((pEndGateObj->Node[EndIO] != m_pAnodeNULL) && (pEndGateObj->Node[1] == m_pAnodeNULL) && StartIO != 1)
      {
         EndIO = 1;
         pEndAnode = pEndGateObj->Node[EndIO];
      }
      // if startgate's output connected and input not then switch to input
      else if ((pStartGateObj->Node[StartIO] != m_pAnodeNULL) && (pStartGateObj->Node[1] == m_pAnodeNULL) && EndIO != 1)
      {
         StartIO = 1;
         pStartAnode = pStartGateObj->Node[StartIO];
      }
      else if(EndIO == 0 && StartIO == 0)
      {
         // turn the wire around, set the end to 1. 
         //this will only happen when a wire is drawn from something to a node that has already had a wire end at it
         CLogiGate* pTmpGateObj = pStartGateObj;
         pStartGateObj = pEndGateObj;
         pEndGateObj = pTmpGateObj;
         EndIO = 1;
         pEndAnode = pEndGateObj->Node[EndIO];
         if ((pEndAnode == m_pAnodeNULL) && (EndIO < pEndGateObj->Outputs)) NodeList.AddHead(pEndAnode = new Anode(UNKNOWN,"xyz",DRIVE));
      }
   }

   else if (pEndGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate)))
   {

      // if other gate is output then switch to input

      if (StartIO < pStartGateObj->Outputs)
      {
         EndIO = 1;
         pEndAnode = pEndGateObj->Node[EndIO];
      }
   }

   else if (pStartGateObj->IsKindOf(RUNTIME_CLASS(CLogiNULLGate)))
   {

      // if other gate is output then switch to input

      if (EndIO < pEndGateObj->Outputs)
      {
         StartIO = 1;
         pStartAnode = pStartGateObj->Node[StartIO];
      }
   }

   //	  this first case doesn't actually seem to cause a problem.
   //   if((pStartAnode != m_pAnodeNULL) && (pEndAnode != m_pAnodeNULL))
   //	  {
   //      ::MessageBox(::GetFocus(),"Bad Wire found, skipping. Both nodes NOT NULL", "Error", MB_OK | MB_ICONEXCLAMATION);
   //		return NULL;
   //	  }
   if((pStartAnode == m_pAnodeNULL) && (pEndAnode == m_pAnodeNULL))
   {
      ::MessageBox(::GetFocus(),"Bad Wire found, skipping. Both nodes NULL", "Error", MB_OK | MB_ICONEXCLAMATION);
      //MessageBeep(0xFFFFFFFF);
      //((CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR))->SetPaneText(0, "Bad Wire found, not skipping, may cause errors");
      //((CStatusBar*) AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR))->SetPaneText(0, "Bad Wire found, skipping");
      //Remove(pWireObj);
      return NULL;
   }

   //what purpose does this serve?
   if (pStartAnode == m_pAnodeNULL) pStartAnode = pEndAnode;

   // hook it up
   pStartGateObj->Connect(StartIO, pStartAnode);
   pEndGateObj->Connect(EndIO, pStartAnode);

   // Add this Wire to the wirelist of each contact
   pStartGateObj->Wire[StartIO].AddHead(pWireObj);
   pEndGateObj->Wire[EndIO].AddHead(pWireObj);

   // Let wire know gate and contact
   pWireObj->pStartGateObj = pStartGateObj;
   pWireObj->StartIO = StartIO;
   pWireObj->pEndGateObj = pEndGateObj;
   pWireObj->EndIO = EndIO;

   return pWireObj;
}

int CLogiDoc::GetMaxPage()
{
   CLogiObj* CurrentObj;
   POSITION pos;

   int iMaxPage = 0;

   for( pos = m_objects.GetHeadPosition(); pos != NULL; )
   {
      CurrentObj = (CLogiObj*) m_objects.GetNext( pos );
      iMaxPage = max(CurrentObj->m_iPage,iMaxPage);
   }

   return iMaxPage;
}

/////////////////////////////////////////////////////////////////////////////
// CLogiDoc serialization

void CLogiDoc::Serialize(CArchive& ar)
{
   char Buffer[1024];

   int iPage = 1;

   if (ar.IsStoring())
   {
      POSITION pos;
      CLogiObj* CurrentGate;
      CLogiObj* CurrentWire;
      CStringArray* PageNames;
      int iLastPage;

      // m_PageNames cannot be accessed for reading directly, as
      // GetPageNames performs some pre-processing

      PageNames = GetPageNames();
      iLastPage = PageNames->GetUpperBound() + 1;

      // CheckForStrays();

      sprintf(Buffer,"%d %d %d\015\012", version, VERSION_MAJOR, VERSION_MINOR);
      ar.Write(Buffer,strlen(Buffer));

      for( iPage=1; iPage <= iLastPage; iPage++ )
      {
         sprintf(Buffer,"%d %d\015\012", pagechange, iPage);
         ar.Write(Buffer,strlen(Buffer));

         // Write page name, if any
         if (!PageNames->GetAt(iPage-1).IsEmpty())
         {
            sprintf(Buffer,"%d %s\015\012", pagename, PageNames->GetAt(iPage-1));
            ar.Write(Buffer,strlen(Buffer));
         }

         for( pos = m_objects.GetHeadPosition(); pos != NULL; )
         {
            CurrentGate = (CLogiObj*) m_objects.GetNext( pos );
            if (  (!CurrentGate->IsKindOf(RUNTIME_CLASS(CLogiWire)))
               && (CurrentGate->m_iPage == iPage))
            {
               switch (CurrentGate->m_Logishape)
               {
               case asciidisplaygate:
               case groundgate:
               case plusgate:
               case keypadgate:
               case breakgate:
               case bitbucketgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case countergate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiCounterGate*) CurrentGate)->m_iSize,
                        ((CLogiCounterGate*) CurrentGate)->m_iInit);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case robotgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d %d %d %d %d %d %s\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiRobotGate*) CurrentGate)->m_iStyle,
                        ((CLogiRobotGate*) CurrentGate)->m_iPosition,
                        ((CLogiRobotGate*) CurrentGate)->m_iPositionX,
                        ((CLogiRobotGate*) CurrentGate)->m_iPositionY,
                        ((CLogiRobotGate*) CurrentGate)->m_iHotspot,
                        ((CLogiRobotGate*) CurrentGate)->m_iHotspotX,
                        ((CLogiRobotGate*) CurrentGate)->m_iHotspotY,
                        ((CLogiRobotGate*) CurrentGate)->m_csFileName.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case networkgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d %s\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiNetworkGate*) CurrentGate)->m_iDirection,
                        ((CLogiNetworkGate*) CurrentGate)->m_uPort,
                        ((CLogiNetworkGate*) CurrentGate)->m_csName.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case buzzergate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiBuzzerGate*) CurrentGate)->m_iFreq,
                        ((CLogiBuzzerGate*) CurrentGate)->m_iDuration);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case soundwavegate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %s\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiSoundwaveGate*) CurrentGate)->m_bWait,
                        ((CLogiSoundwaveGate*) CurrentGate)->m_csFileName.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case bitmapgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %s %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiBitmapGate*) CurrentGate)->m_iStyle,
                        ((CLogiBitmapGate*) CurrentGate)->m_csFileName.GetBuffer(1),
                        ((CLogiBitmapGate*) CurrentGate)->m_bPlayground);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case textgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %s\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiTextGate*) CurrentGate)->m_iStyle,
                        ((CLogiTextGate*) CurrentGate)->m_csFileName.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));

                     sprintf(Buffer,"%s\015\012",((CLogiTextGate*) CurrentGate)->m_pTextText.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case signalreceivergate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiSignalreceiverGate*) CurrentGate)->m_iDummy);
                     ar.Write(Buffer,strlen(Buffer));

                     sprintf(Buffer,"%s\015\012",((CLogiSignalreceiverGate*) CurrentGate)->m_csSignalName.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case signalsendergate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiSignalsenderGate*) CurrentGate)->m_iDummy);
                     ar.Write(Buffer,strlen(Buffer));

                     sprintf(Buffer,"%s\015\012",((CLogiSignalsenderGate*) CurrentGate)->m_csSignalName.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case writefilegate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %s\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiWritefileGate*) CurrentGate)->m_iFormat,
                        ((CLogiWritefileGate*) CurrentGate)->m_csFileName.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case readfilegate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %s\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiReadfileGate*) CurrentGate)->m_iFormat,
                        ((CLogiReadfileGate*) CurrentGate)->m_csFileName.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case led7gate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiLed7Gate*) CurrentGate)->m_iRed,
                        ((CLogiLed7Gate*) CurrentGate)->m_iInputs);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case randomgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiRandomGate*) CurrentGate)->m_iSpare,
                        ((CLogiRandomGate*) CurrentGate)->m_uSeed);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case portingate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiPortinGate*) CurrentGate)->m_iAddress,
                        ((CLogiPortinGate*) CurrentGate)->m_iInitial);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case portoutgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiPortoutGate*) CurrentGate)->m_iAddress,
                        ((CLogiPortoutGate*) CurrentGate)->m_iInitial);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case orgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiORGate*) CurrentGate)->m_iInputs,
                        ((CLogiORGate*) CurrentGate)->m_bDemorgan);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case muxgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiMuxGate*) CurrentGate)->m_bDeMux,
                        ((CLogiMuxGate*) CurrentGate)->m_iStyle);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case alugate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiAluGate*) CurrentGate)->m_bDeAlu,
                        ((CLogiAluGate*) CurrentGate)->m_iInputs);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case asciikeyboardgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiAsciikeyboardGate*) CurrentGate)->m_bAscii);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case invertgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiINVERTGate*) CurrentGate)->m_bDemorgan);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case tristategate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiTristateGate*) CurrentGate)->m_bDemorgan,
                        ((CLogiTristateGate*) CurrentGate)->m_bAssertLO);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case busgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiBusGate*) CurrentGate)->m_iInputs,
                        ((CLogiBusGate*) CurrentGate)->m_bDummy2);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case flipflopgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiFlipflopGate*) CurrentGate)->m_iStyle,
                        ((CLogiFlipflopGate*) CurrentGate)->m_bEdge,
                        ((CLogiFlipflopGate*) CurrentGate)->m_bPresetClear);
                     ar.Write(Buffer,strlen(Buffer));

                     break;
                  }
               case nullgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiNULLGate*) CurrentGate)->m_iPass,
                        ((CLogiNULLGate*) CurrentGate)->m_iFloat);
                     ar.Write(Buffer,strlen(Buffer));

                     break;
                  }
               case andgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiANDGate*) CurrentGate)->m_iInputs,
                        ((CLogiANDGate*) CurrentGate)->m_bDemorgan);
                     ar.Write(Buffer,strlen(Buffer));

                     break;
                  }
               case xorgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiXORGate*) CurrentGate)->m_iInputs,
                        ((CLogiXORGate*) CurrentGate)->m_bDemorgan);
                     ar.Write(Buffer,strlen(Buffer));

                     break;
                  }
               case ledgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiLedGate*) CurrentGate)->m_iRed,
                        ((CLogiLedGate*) CurrentGate)->m_iBlink);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case switchgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiSwitchGate*) CurrentGate)->m_iOn,
                        ((CLogiSwitchGate*) CurrentGate)->m_iToggle);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case selectgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiSelectGate*) CurrentGate)->m_iInitial,
                        ((CLogiSelectGate*) CurrentGate)->m_iDummy);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case oscillatorgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiOscillatorGate*) CurrentGate)->m_iCountHI,
                        ((CLogiOscillatorGate*) CurrentGate)->m_iCountLO);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case clockgate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiClockGate*) CurrentGate)->m_iSeconds,
                        ((CLogiClockGate*) CurrentGate)->m_bSpare);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case timergate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiTimerGate*) CurrentGate)->m_uDelay,
                        ((CLogiTimerGate*) CurrentGate)->m_bSpare);
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case memorygate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %s\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiMemoryGate*) CurrentGate)->m_iFormat,
                        ((CLogiMemoryGate*) CurrentGate)->m_csFileName.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               case tapedrivegate:
                  {
                     sprintf(Buffer,"%d %d %d %d %d %d %d %d %s\015\012",
                        CurrentGate->m_Logishape,
                        CurrentGate->m_position.TopLeft().x,
                        CurrentGate->m_position.TopLeft().y,
                        CurrentGate->m_position.BottomRight().x,
                        CurrentGate->m_position.BottomRight().y,
                        ((CLogiTapedriveGate*) CurrentGate)->m_iFormat,
                        ((CLogiTapedriveGate*) CurrentGate)->m_iSize,
                        ((CLogiTapedriveGate*) CurrentGate)->m_iStartPosition,
                        ((CLogiTapedriveGate*) CurrentGate)->m_csFileName.GetBuffer(1));
                     ar.Write(Buffer,strlen(Buffer));
                     break;
                  }
               }
            }
         }

         for( pos = m_objects.GetHeadPosition(); pos != NULL; )
         {
            CurrentWire = (CLogiObj*) m_objects.GetNext( pos );
            if ((CurrentWire->IsKindOf(RUNTIME_CLASS(CLogiWire)))
               && (CurrentWire->m_iPage == iPage))
            {
               sprintf(Buffer,"%d %d %d %d %d\015\012",
                  CurrentWire->m_Logishape,
                  CurrentWire->m_position.BottomRight().x,
                  CurrentWire->m_position.BottomRight().y,
                  CurrentWire->m_position.TopLeft().x,
                  CurrentWire->m_position.TopLeft().y);
               ar.Write(Buffer,strlen(Buffer));
            }
         }
      }

      sprintf(Buffer,"%d %d\015\012", pagecolor, m_paperColor);
      ar.Write(Buffer,strlen(Buffer));

      sprintf(Buffer,"%d %d\015\012", unconnected, m_iUnconnected);
      ar.Write(Buffer,strlen(Buffer));

      sprintf(Buffer,"%d %d %d %d\015\012", pagegrid, m_bGrid, m_uGridWidth, m_uGridHeight);
      ar.Write(Buffer,strlen(Buffer));

      // New fields for canvas size and simulation rate

      sprintf(Buffer,"%d %d %d\015\012", canvassize, m_uCanvasWidth, m_uCanvasHeight);
      ar.Write(Buffer,strlen(Buffer));

      sprintf(Buffer, "%d %d %d\015\012", simrate, m_bSimRateSpecified, m_iSimRate);
      ar.Write(Buffer,strlen(Buffer));

      LOGFONT lf;

      m_cfScreen.GetLogFont(&lf);

      sprintf(Buffer,"%d\015\012",endgate);
      ar.WriteString(Buffer);
      sprintf(Buffer,"%s\015\012",lf.lfFaceName);
      ar.WriteString(Buffer);
      sprintf(Buffer,"%d\015\012",lf.lfHeight);
      ar.WriteString(Buffer);
      sprintf(Buffer,"%d\015\012",lf.lfWeight);
      ar.WriteString(Buffer);
      sprintf(Buffer,"%d\015\012",lf.lfItalic);
      ar.WriteString(Buffer);
      sprintf(Buffer,"%d\015\012",lf.lfCharSet);
      ar.WriteString(Buffer);
      sprintf(Buffer,"%d\015\012",lf.lfOutPrecision);
      ar.WriteString(Buffer);
      sprintf(Buffer,"%d\015\012",lf.lfClipPrecision);
      ar.WriteString(Buffer);
      sprintf(Buffer,"%d\015\012",lf.lfQuality);
      ar.WriteString(Buffer);
      sprintf(Buffer,"%d\015\012",lf.lfPitchAndFamily);
      ar.WriteString(Buffer);

      //      ar << m_paperColor;
      //        m_objects.Serialize(ar);
   }
   else
   {
      int xo;
      int yo;
      int x1;
      int y1;
      int x2;
      int y2;
      int tmp1;
      int tmp2;
      int tmp3;
      int tmp4;
      int tmp5;
      int tmp6;
      int tmp7;
      //      int tmp8;
      int shape;
      char buf1[1024];
      //      char buf2[1024];
      char *pcTemp;
      CRect pos;
      BOOL bDone;

      m_iVersionMajor = 0;
      m_iVersionMinor = 0;

      int bSaveReadOnly = m_bReadOnly;
      m_bReadOnly = 0;

      SetPathName(ar.GetFile()->GetFilePath(), FALSE );

      bDone = FALSE;

      xo = 0;
      yo = 0;

      while ((!bDone) && (ar.ReadString(Buffer,1024-1) != NULL))
      {
         sscanf(Buffer,"%d",&shape);
         switch (shape)
         {
         case asciidisplaygate:
            {
               sscanf(Buffer,"%*d %d %d %d %d",&x1,&y1,&x2,&y2);
               Add(new CLogiAsciidisplayGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "DISPLAY", iPage, this));
               break;
            }
         case groundgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d",&x1,&y1,&x2,&y2);
               Add(new CLogiGroundGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "GROUND", iPage, this));
               break;
            }
         case plusgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d",&x1,&y1,&x2,&y2);
               Add(new CLogiPlusGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "PLUS", iPage, this));
               break;
            }
         case portingate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiPortinGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "PORTIN", iPage, this, tmp1, tmp2));
               break;
            }
         case portoutgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiPortoutGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "PORTOUT", iPage, this, tmp1, tmp2));
               break;
            }
         case readfilegate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %[^\0]",&x1,&y1,&x2,&y2,&tmp1,&buf1);
               Add(new CLogiReadfileGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "READFILE", iPage, this, tmp1, buf1));
               break;
            }
         case signalreceivergate:
            {
               sscanf(Buffer,"%*d %d %d %d %d",&x1,&y1,&x2,&y2);
               ar.ReadString(Buffer,1024-1);
               Add(new CLogiSignalreceiverGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "SIGNALRX", iPage, this, 0, Buffer));
               break;
            }
         case signalsendergate:
            {
               sscanf(Buffer,"%*d %d %d %d %d",&x1,&y1,&x2,&y2);
               ar.ReadString(Buffer,1024-1);
               Add(new CLogiSignalsenderGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "SIGNALTX", iPage, this, 0, Buffer));
               break;
            }
         case analyzegate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d",&x1,&y1,&x2,&y2, &tmp1);
               ar.ReadString(Buffer,1024-1);
               Add(new CLogiAnalyzeGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "ANALYZE", iPage, this, tmp1, Buffer));
               break;
            }
         case soundwavegate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %[^\0]",&x1,&y1,&x2,&y2,&tmp1,&buf1);
               Add(new CLogiSoundwaveGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "SOUNDWAVE", iPage, this, tmp1, buf1));
               break;
            }
         case memorygate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %[^\0]",&x1,&y1,&x2,&y2,&tmp1,&buf1);
               Add(new CLogiMemoryGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "MEMORY", iPage, this, tmp1, buf1));
               break;
            }
         case tapedrivegate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d %d %[^\0]",&x1,&y1,&x2,&y2,&tmp1,&tmp2,&tmp3,&buf1);
               Add(new CLogiTapedriveGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "TAPEDRIVE", iPage, this, tmp1, tmp2, tmp3, buf1));
               break;
            }
         case textgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %[^\0]",&x1,&y1,&x2,&y2,&tmp1,&buf1);
               ar.ReadString(Buffer,1024-1);
               Add(new CLogiTextGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "TEXT", iPage, this, tmp1, buf1, Buffer));
               break;
            }
         case writefilegate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %[^\0]",&x1,&y1,&x2,&y2,&tmp1,&buf1);
               Add(new CLogiWritefileGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "WRITEFILE", iPage, this, tmp1, buf1));
               break;
            }
         case flipflopgate:
            {
               tmp3 = 0; // backwards compatibility for bPresetClear flag
               sscanf(Buffer,"%*d %d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2,&tmp3);
               Add(new CLogiFlipflopGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "FLIPFLOP", iPage, this, tmp1, tmp2, tmp3));
               break;
            }
         case muxgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiMuxGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "MUX", iPage, this, tmp1, tmp2));
               break;
            }
         case alugate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiAluGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "ALU", iPage, this, tmp1, tmp2));
               break;
            }
         case keypadgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d",&x1,&y1,&x2,&y2);
               Add(new CLogiKeypadGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "KEYPAD", iPage, this));
               break;
            }
         case bitmapgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %[^\0]",&x1,&y1,&x2,&y2,&tmp1,&buf1);
               // This gets a little interesting because the serialize code was not
               // aware that the filename could contain spaces. Thus we find the
               // last integer parameter after the last space in the line.
               pcTemp = strrchr(buf1, ' ');
               tmp2 = 0;
               if (pcTemp != NULL) // defensive
               {
                  *pcTemp = '\0';
                  sscanf(pcTemp + 1, "%d", &tmp2);
               }
               Add(new CLogiBitmapGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "BITMAP", iPage, this, tmp1, tmp2, buf1));
               break;
            }
         case countergate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiCounterGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "COUNTER", iPage, this, tmp1, tmp2));
               break;
            }
         case randomgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiRandomGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "RANDOM", iPage, this, tmp1, tmp2));
               break;
            }
         case breakgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d",&x1,&y1,&x2,&y2);
               Add(new CLogiBreakGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "BREAK", iPage, this));
               break;
            }
         case bitbucketgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d",&x1,&y1,&x2,&y2);
               Add(new CLogiBitbucketGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "BITBUCKET", iPage, this));
               break;
            }
         case networkgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d %[^\0]",&x1,&y1,&x2,&y2,&tmp1, &tmp2, &buf1);
               Add(new CLogiNetworkGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "NETWORK", iPage, this, tmp1, tmp2, buf1));
               break;
            }
         case robotgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d %d %d %d %d %d %[^\0]",&x1,&y1,&x2,&y2,&tmp1,&tmp2,&tmp3,&tmp4,&tmp5,&tmp6,&tmp7,&buf1);
               Add(new CLogiRobotGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "ROBOT", iPage, this, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, buf1));
               break;
            }
         case andgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiANDGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "AND", iPage, this, tmp1, tmp2));
               break;
            }
         case xorgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiXORGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "XOR", iPage, this, tmp1, tmp2));
               break;
            }
         case orgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiORGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "OR", iPage, this, tmp1, tmp2));
               break;
            }
         case invertgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1);
               Add(new CLogiINVERTGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "INVERT", iPage, this, tmp1));
               break;
            }
         case tristategate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiTristateGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "TRISTATE", iPage, this, tmp1, tmp2));
               break;
            }
         case busgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiBusGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "BUS", iPage, this, tmp1, tmp2));
               break;
            }
         case asciikeyboardgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1);
               Add(new CLogiAsciikeyboardGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "KEYBOARD", iPage, this, tmp1));
               break;
            }
         case oscillatorgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiOscillatorGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "OSCILLATOR", iPage, this, tmp1, tmp2));
               break;
            }
         case clockgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiClockGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "CLOCK", iPage, this, tmp1, tmp2));
               break;
            }
         case timergate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiTimerGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "TIMER", iPage, this, tmp1, tmp2));
               break;
            }
         case ledgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiLedGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "LED", iPage, this, tmp1, tmp2));
               break;
            }
         case switchgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiSwitchGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "SWITCH", iPage, this, tmp1, tmp2));
               break;
            }
         case selectgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiSelectGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "SELECT", iPage, this, tmp1, tmp2));
               break;
            }
         case buzzergate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiBuzzerGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "BUZZER", iPage, this, tmp1, tmp2));
               break;
            }
         case nullgate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiNULLGate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "NULL", iPage, this, tmp1, tmp2));
               break;
            }
         case led7gate:
            {
               sscanf(Buffer,"%*d %d %d %d %d %d %d",&x1,&y1,&x2,&y2,&tmp1,&tmp2);
               Add(new CLogiLed7Gate(CRect(x1+xo,y1+yo,x2+xo,y2+yo), "LED7", iPage, this, tmp1, tmp2));
               break;
            }
         case wire:
            {
               sscanf(Buffer,"%*d %d %d %d %d",&x1,&y1,&x2,&y2);
               ReWire(CRect(x1+xo,y1+yo,x2+xo,y2+yo), NULL, iPage);
               break;
            }
         case pagechange:
            {
               sscanf(Buffer,"%*d %d",&tmp1);
               iPage = tmp1;
               break;
            }
         case pagecolor:
            {
               sscanf(Buffer,"%*d %d",&tmp1);
               m_paperColor = (COLORREF) tmp1;
               break;
            }
         case unconnected:
            {
               sscanf(Buffer,"%*d %d",&tmp1);
               m_iUnconnected = tmp1;
               break;
            }
         case pagegrid:
            {
               sscanf(Buffer,"%*d %d %d %d",&tmp1, &tmp2, &tmp3);
               m_bGrid = tmp1;
               m_uGridWidth = tmp2;
               m_uGridHeight = tmp3;
               if ((m_uGridWidth < 2) || (m_uGridWidth > 200)) m_uGridWidth = 6;
               if ((m_uGridHeight < 2) || (m_uGridHeight > 200)) m_uGridHeight = 6;
               break;
            }
         case canvassize:
            {
               sscanf(Buffer,"%*d %d %d",&tmp1, &tmp2);
               m_uCanvasWidth = tmp1;
               m_uCanvasHeight = tmp2;
               break;
            }
         case simrate:
            {
               sscanf(Buffer,"%*d %d %d",&tmp1, &tmp2);
               m_bSimRateSpecified = tmp1;
               m_iSimRate = tmp2;
               break;
            }
         case pagename:
            {
               m_PageNames.SetAtGrow(iPage-1, &Buffer[3]);
               break;
            }
         case version:
            {
               sscanf(Buffer,"%*d %d %d",&tmp1, &tmp2);
               m_iVersionMajor = tmp1;
               m_iVersionMinor = tmp2;
               if (m_iVersionMajor < 2)
               {
                  xo = 400;
                  yo = 300;
               }
               break;
            }
         case endgate:
            {
               int tmp;
               LOGFONT lf;

               memset(&lf,0,sizeof(lf));

               ar.ReadString(lf.lfFaceName,LF_FACESIZE);
               ar.ReadString(Buffer,1024-1);
               sscanf(Buffer,"%d",&tmp); lf.lfHeight = tmp;
               ar.ReadString(Buffer,1024-1);
               sscanf(Buffer,"%d",&tmp); lf.lfWeight = tmp;
               ar.ReadString(Buffer,1024-1);
               sscanf(Buffer,"%d",&tmp); lf.lfItalic = (BYTE) tmp;
               ar.ReadString(Buffer,1024-1);
               sscanf(Buffer,"%d",&tmp); lf.lfCharSet = (BYTE) tmp;
               ar.ReadString(Buffer,1024-1);
               sscanf(Buffer,"%d",&tmp); lf.lfOutPrecision = (BYTE) tmp;
               ar.ReadString(Buffer,1024-1);
               sscanf(Buffer,"%d",&tmp); lf.lfClipPrecision = (BYTE) tmp;
               ar.ReadString(Buffer,1024-1);
               sscanf(Buffer,"%d",&tmp); lf.lfQuality = (BYTE) tmp;
               ar.ReadString(Buffer,1024-1);
               sscanf(Buffer,"%d",&tmp); lf.lfPitchAndFamily = (BYTE) tmp;

               m_cfScreen.DeleteObject();
               //               if (m_iVersionMajor < 2)
               //                  {
               //                  if (lf.lfHeight > 0)
               //                     {
               //                     lf.lfHeight = -lf.lfHeight;
               //                     lf.lfWidth = 0;
               //                     lf.lfQuality = 1;
               //                     }
               //                  }
               m_cfScreen.CreateFontIndirect(&lf);

               bDone = TRUE;

               break;
            }
         default: ASSERT(FALSE);
         }
      }

      m_bReadOnly = bSaveReadOnly;
      //      ar >> m_paperColor;
      //      m_objects.Serialize(ar);

      // Resize to canvas size
      ComputePageSize();

      // Remove undo information for the
      // items added as a result of deserialization
      m_undo.Reset();
   }

   // By calling the base class COleDocument, we enable serialization
   //  of the container document's COleClientItem objects automatically.
   CDocument::Serialize(ar);
}


/////////////////////////////////////////////////////////////////////////////
// CLogiDoc implementation

void CLogiDoc::Draw(CDC* pDC, CLogiView* pView)
{
   POSITION pos;

   CRect intersectRect;
   CRect posRect;
   CRect updateRect;

   pDC->GetClipBox(&updateRect);
   updateRect.NormalizeRect();

   pos = m_objects.GetHeadPosition();
   while (pos != NULL)
   {
      CLogiObj* pObj = (CLogiObj*)m_objects.GetNext(pos);
      if (!pObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
      {
         if (pObj->m_iPage == pView->m_iPage)
         {
            posRect = pObj->m_position;
            posRect.NormalizeRect();
            if (intersectRect.IntersectRect(&posRect,&updateRect))
            {
               pObj->Draw(pDC, pView);
               if (pView->m_bActive && !pDC->IsPrinting() && pView->IsSelected(pObj))
               {
                  pObj->DrawTracker(pDC, CLogiObj::selected);
               }
            }
         }
      }
   }

   pos = m_objects.GetHeadPosition();
   while (pos != NULL)
   {
      CLogiObj* pObj = (CLogiObj*)m_objects.GetNext(pos);
      if (pObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
      {
         if (pObj->m_iPage == pView->m_iPage)
         {
            posRect = pObj->m_position;
            posRect.NormalizeRect();
            posRect.InflateRect(1,1);
            if (intersectRect.IntersectRect(&posRect,&updateRect))
            {
               pObj->Draw(pDC, pView);
               if (pView->m_bActive && !pDC->IsPrinting() && pView->IsSelected(pObj))
               {
                  pObj->DrawTracker(pDC, CLogiObj::selected);
               }
            }
         }
      }
   }
}

void CLogiDoc::Add(CLogiObj* pObj, BOOL bAllowUndo)
{
   if (m_bReadOnly)
   {
      MessageBeep(0xFFFFFFFF);
      return;
   }
   m_objects.AddTail(pObj);
   pObj->m_pDocument = this;
   if (bAllowUndo)
      m_undo.Push(pObj, CUndoElement::Add);
   SetModifiedFlag();
}

void CLogiDoc::Remove(CLogiObj* pObj, BOOL bAllowUndo)
{
   // If bAllowUndo is TRUE, you must not call delete
   // on pObj as the undo system handles the delete
   // when necessary. However, if bAllowUndo is FALSE
   // you are responsible for deleting pObj.

   // Find and remove from document
   POSITION pos = m_objects.Find(pObj);
   if (pos != NULL)
   {
      //      CLogiObj* pObjClone = pObj->Clone(pObj->m_pDocument);
      if (bAllowUndo)
         m_undo.Push(pObj, CUndoElement::Delete);
      m_objects.RemoveAt(pos);
   }
   // set document modified flag
   SetModifiedFlag();

   // call remove for each view so that the view can remove from m_selection
   pos = GetFirstViewPosition();
   while (pos != NULL) ((CLogiView*)GetNextView(pos))->Remove(pObj);
}

void CLogiDoc::Move(CLogiObj* pObj, CRect &rect, BOOL bAllowUndo)
{
   // Store old position for undo/redo
   if (bAllowUndo)
      m_undo.PushMove(pObj, pObj->m_position);

   pObj->MoveTo(rect);
   SetModifiedFlag();
}

void CLogiDoc::Rename(CLogiObj* pObj, LPCTSTR newname, BOOL bAllowUndo)
{
   if (bAllowUndo)
      m_undo.Push(pObj, CUndoElement::Rename, pObj->GetText());

   pObj->SetText(newname);
   SetModifiedFlag();
}

void CLogiDoc::Edit(CLogiObj* pObj, CArchive &ar, BOOL bAllowUndo)
{
   if (bAllowUndo)
      m_undo.PushEdit(pObj);

   pObj->Serialize(ar);
   pObj->Invalidate();

   SetModifiedFlag();
}

void CLogiDoc::BeginManualEdit(CLogiObj *pObj, BOOL bAllowUndo)
{
   if (bAllowUndo)
      m_undo.PushEdit(pObj);

   SetModifiedFlag();
}

// point is in logical coordinates
CLogiObj* CLogiDoc::ObjectAt(const CPoint& point, int ipage)
{
   CRect rect(point, CSize(2, 2));
   POSITION pos = m_objects.GetTailPosition();
   while (pos != NULL)
   {
      CLogiObj* pObj = (CLogiObj*)m_objects.GetPrev(pos);
      if ((pObj->m_iPage == ipage) && (pObj->Intersects(rect)) && (!pObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))) return pObj;
      //      if (pObj->Intersects(rect)) return pObj;
   }

   return NULL;
}

// point is in logical coordinates

CLogiObj* CLogiDoc::ObjectAtContact(const CPoint& point, int *io, int ipage)
{
   int i;
   CRect rect(point, CSize(7, 7));
   rect.OffsetRect(-3,-3);
   POSITION pos = m_objects.GetTailPosition();

   while (pos != NULL)
   {
      CLogiObj* pObj = (CLogiObj*)m_objects.GetPrev(pos);
      if ((pObj->m_iPage == ipage) && pObj->IsKindOf(RUNTIME_CLASS(CLogiGate)) && pObj->Intersects(rect))
      {
         for (i=0;i<((CLogiGate *)pObj)->Contacts;i++)
         {
            if (rect.PtInRect(((CLogiGate *)pObj)->Contact[i]))
            {
               *io = i;
               return pObj;
            }
         }
      }
   }

   return NULL;
}

// point is in logical coordinates

CLogiObj* CLogiDoc::ObjectAtContactExact(const CPoint& point, int *io, int ipage)
{
   int i;
   CRect rect(point, CSize(7, 7));
   rect.OffsetRect(-3,-3);
   POSITION pos = m_objects.GetTailPosition();

   while (pos != NULL)
   {
      CLogiObj* pObj = (CLogiObj*)m_objects.GetPrev(pos);
      if ((pObj->m_iPage == ipage) && pObj->IsKindOf(RUNTIME_CLASS(CLogiGate)) && pObj->Intersects(rect))
      {
         for (i=0;i<((CLogiGate *)pObj)->Contacts;i++)
         {
            if (point == ((CLogiGate *)pObj)->Contact[i])
            {
               *io = i;
               return pObj;
            }
         }
      }
   }

   return NULL;
}

// Resize page based on user-defined canvas size

void CLogiDoc::ComputePageSize()
{
   CSize new_size(m_uCanvasWidth, m_uCanvasHeight);

   // if size changed then iterate over views and reset
   if (new_size != m_size)
   {
      m_size = new_size;
      POSITION pos = GetFirstViewPosition();
      while (pos != NULL) ((CLogiView*)GetNextView(pos))->SetPageSize(m_size);
   }
}


void CLogiDoc::OnViewPaperColor()
{
   // Load color dialog with current color selected
   CColorDialog dlg(GetPaperColor());
   if (dlg.DoModal() != IDOK) return;

   m_paperColor = dlg.GetColor();
   SetModifiedFlag();
   UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CLogiDoc diagnostics

#ifdef _DEBUG
void CLogiDoc::AssertValid() const
{
   CDocument::AssertValid();
}

void CLogiDoc::Dump(CDumpContext& dc) const
{
   CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLogiDoc commands

void CLogiDoc::OnSimulateRun()
{
   CLogiDoc *pDocument;
   int msgboxID;
   //Load accelerator table
   //m_haccel = LoadAccelerators(AfxGetInstanceHandle() ,MAKEINTRESOURCE(IDR_LOGICLTYPE_CNTR_IP));

   // Get pointer to our one and only CDocTemplate

   POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition();
   CDocTemplate* pTemplate = AfxGetApp()->GetNextDocTemplate( pos );

   // Look to see if a document is already running. If it is, then it must be
   // stopped before another can be started. So, ask the user if they want to
   // stop the running doc and start this one.

   POSITION pos2 = pTemplate->GetFirstDocPosition();

   while (pos2) {
      pDocument = (CLogiDoc*)pTemplate->GetNextDoc(pos2);
      if (pDocument != NULL && pDocument != this && pDocument->m_bKeepGoing) {
         msgboxID = ::MessageBox(::GetFocus(),"Stop the running simulation and run this one?","Multimedia Logic", MB_OKCANCEL | MB_ICONQUESTION);
         if (msgboxID == IDOK) {
            pDocument->m_bForceStopAndChangeDoc = TRUE;
            pDocument->OnSimulateStop();
         }
         return;
      }
   }

   //I'm not entirely sure where to put this:
   m_bSimulating = TRUE;

   if (m_bKeepGoing)
      return;

   if (m_bPause) {
      m_bPause = 0;
   }
   else if (!Reset(ID_SIMULATE_RUN))
   {
      // Return simulation to RESET mode.
      Reset(ID_SIMULATE_RESET);
      return;
   }


   Simulate(ID_SIMULATE_RUN);
   // Now that the simulation has been stopped, let's check to see what
   // the user wanted to happen next, if anything...

   if (m_bForceStopAndExitApp) {
      AfxGetApp()->m_pMainWnd->PostMessage(WM_COMMAND, ID_APP_EXIT, 0L);
   }
   if (m_bForceStopAndCloseDoc) {
      AfxGetApp()->m_pMainWnd->PostMessage(WM_COMMAND, ID_FILE_CLOSE, 0L);
   }
   if (m_bForceStopAndChangeDoc) {
      AfxGetApp()->m_pMainWnd->PostMessage(WM_COMMAND, ID_SIMULATE_RUN, 0L);
   }

}


void CLogiDoc::OnUpdateSimulateRun(CCmdUI* pCmdUI)
{
   if (m_bKeepGoing)
   {
      pCmdUI->Enable(FALSE);
   }
}

void CLogiDoc::OnSimulateStop()
{
   m_bKeepGoing = FALSE;
   m_bSimulating = FALSE;
   m_uProbe = 0;
   Reset(ID_SIMULATE_STOP);

   // call update for each view, to draw the wires black
   POSITION vpos = GetFirstViewPosition();
   while (vpos != NULL)  ((CLogiView*)GetNextView(vpos))->OnUpdate(NULL, HINT_UPDATE_WINDOW, NULL);
}

void CLogiDoc::OnUpdateSimulateStop(CCmdUI* pCmdUI)
{
   if (!m_bKeepGoing)
   {
      pCmdUI->Enable(FALSE);
   }
}

void CLogiDoc::OnSimulatePause()
{
   if (!m_bPause)
   {
      m_bKeepGoing = FALSE;
      m_bPause = 1;
   }
}

void CLogiDoc::OnUpdateSimulatePause(CCmdUI* pCmdUI)
{
   if (!m_bKeepGoing)
   {
      pCmdUI->Enable(FALSE);
   }
}

void CLogiDoc::OnSimulateStep()
{
   if (!m_bSimulating) m_bSimulating = TRUE;
   if (!m_bKeepGoing)
   {
      if (!m_bPause)
      {
         if (!Reset(ID_SIMULATE_STEP)) return;
         m_bPause = 1;
      }

      Simulate(ID_SIMULATE_STEP);
   }
}

void CLogiDoc::OnUpdateSimulateStep(CCmdUI* pCmdUI)
{
   if (m_bKeepGoing)
   {
      pCmdUI->Enable(FALSE);
   }
}

void CLogiDoc::OnSimulateReset()
{
   m_uProbe = 0;

   if (!m_bKeepGoing)
   {
      Reset(ID_SIMULATE_RESET);
      m_bPause = 0;

      m_bSimulating = FALSE;
      // call update for each view, to draw the wires black
      POSITION vpos = GetFirstViewPosition();
      while (vpos != NULL)  ((CLogiView*)GetNextView(vpos))->OnUpdate(NULL, HINT_UPDATE_WINDOW, NULL);
   }
}

void CLogiDoc::OnUpdateSimulateReset(CCmdUI* pCmdUI)
{
   if (m_bKeepGoing)
   {
      pCmdUI->Enable(FALSE);
   }
}

void CLogiDoc::OnSimulateSetup()
{
   CSetupDlg dlg;

   dlg.m_iUnconnected = m_iUnconnected;
   dlg.m_iSimRate = m_iSimRate;
   if (m_bSimRateSpecified)
      dlg.m_iSimRateType = 1;
   else
      dlg.m_iSimRateType = 0;

   if (dlg.DoModal() == IDOK)
   {
      m_iUnconnected = dlg.m_iUnconnected;
      m_bSimRateSpecified = (dlg.m_iSimRateType == 1);
      if (m_bSimRateSpecified)
         if (dlg.m_iSimRate > 0)
            m_iSimRate = dlg.m_iSimRate;
         else
            m_iSimRate = 1;

      SetModifiedFlag();
   }
}

void CLogiDoc::OnUpdateSimulateSetup(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(!m_bKeepGoing && !m_bPause);
}

void CLogiDoc::OnSimulateDraw()
{
   CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();

   // if palette not up then put it up

   if ((pMainFrm->m_wndPaletteBar.GetStyle() & WS_VISIBLE) == 0)
   {
      pMainFrm->ShowControlBar(&pMainFrm->m_wndPaletteBar, TRUE, FALSE);
   }

   // else hide palette window

   else
   {
      pMainFrm->ShowControlBar(&pMainFrm->m_wndPaletteBar, FALSE, FALSE);
   }

}

void CLogiDoc::OnUpdateSimulateDraw(CCmdUI* pCmdUI)
{
   if (m_bKeepGoing || m_bPause) pCmdUI->Enable(FALSE);
   CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
   pCmdUI->SetCheck(((pMainFrm->m_wndPaletteBar.GetStyle() & WS_VISIBLE) != 0)/* && !m_bKeepGoing*/);
}


void CLogiDoc::OnSimulateProbe()
{
   if (m_uProbe == 0)
   {
      m_uProbe = IDC_PROBE_NULL;
   }
   else
   {
      m_uProbe = 0;
   }
}

void CLogiDoc::OnUpdateSimulateProbe(CCmdUI* pCmdUI)
{
   if (!m_bKeepGoing && !m_bPause)
   {
      pCmdUI->Enable(FALSE);
   }

   pCmdUI->SetCheck(m_uProbe != 0);
}

BOOL CLogiDoc::SaveModified()
{
   int msgboxID;
   CLogiDoc *pDocument;
   // This check fixes bug where palette does not
   // reappear if user closes window during pause state.
   // Also necessary to ensure gates get the Initialize(ID_SIMULATE_RESET)
   // call which does various cleanup tasks for some components.
   if (m_bPause)
      Reset(ID_SIMULATE_RESET);

   // Clear flags used to indicate what to do after simulation stops.
   m_bForceStopAndExitApp = FALSE;
   m_bForceStopAndCloseDoc = FALSE;


   POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition();
   CDocTemplate* pTemplate = AfxGetApp()->GetNextDocTemplate( pos );

   // For any document where m_bKeepGoing is set, then the app is currently in the Simulate()
   // method and we got here by the Simulate() message loop. It is thus
   // not safe to just close, because Simulate() would still be running
   // when this method returns. So, prompt the user to choose to stop the simulation
   // or continue the simulation, and set a flag variable
   // to indicate what to do after falling out of the Simulate() message loop.

   // If user is closing app, find if there is a running document,
   // in which case we ask if the user wants to stop the simulation,
   // and exit. If they do, stop the running document, and check
   // for unsaved modified docs. User will have many chances to abort
   // the exit before the splash down.

   POSITION pos2 = pTemplate->GetFirstDocPosition();

   while (pos2)
   {
      pDocument = (CLogiDoc*)pTemplate->GetNextDoc(pos2);

      if (pDocument != NULL && pDocument->m_bKeepGoing && !pDocument->m_bCloseNotExit) {
         msgboxID = ::MessageBox(::GetFocus(),"Stop the running simulation and exit?","Multimedia Logic", MB_OKCANCEL | MB_ICONQUESTION);
         if (msgboxID == IDOK) {
            pDocument->m_bForceStopAndExitApp = TRUE;
            pDocument->OnSimulateStop();
         }
         return FALSE;
      }
   }

   // Handle the case where the user chose to close a window while it was running
   // in simulation mode.

   if (m_bKeepGoing && m_bCloseNotExit) {
      msgboxID = ::MessageBox(::GetFocus(),"Stop the running simulation and close?","Multimedia Logic", MB_OKCANCEL | MB_ICONQUESTION);
      if (msgboxID == IDOK) {
         OnSimulateStop();
         m_bForceStopAndCloseDoc = TRUE;
      }
      return FALSE;
   }

   // We get here only if a running document has been stopped.
   return CDocument::SaveModified();
}

void CLogiDoc::OnViewGrid()
{
   CGridDlg dlg;
   //   m_bGrid = !m_bGrid;
   dlg.m_bEnable = m_bGrid;
   dlg.m_uWidth = m_uGridWidth;
   dlg.m_uHeight = m_uGridHeight;
   dlg.m_uCanvasWidth = m_uCanvasWidth;
   dlg.m_uCanvasHeight = m_uCanvasHeight;

   if (dlg.DoModal() != IDOK) return;

   m_bGrid = dlg.m_bEnable;
   m_uGridWidth = dlg.m_uWidth;
   m_uGridHeight = dlg.m_uHeight;
   m_uCanvasWidth = dlg.m_uCanvasWidth;
   m_uCanvasHeight = dlg.m_uCanvasHeight;
   ComputePageSize();

   SetModifiedFlag();
   UpdateAllViews(NULL);
}

void CLogiDoc::OnUpdateViewGrid(CCmdUI* pCmdUI)
{
   if (m_bKeepGoing || m_bPause)
   {
      pCmdUI->Enable(FALSE);
   }
}

void CLogiDoc::OnSimulateAnalyze()
{
   if (m_uAnalyze == 0)
   {
      m_uAnalyze = 1;
   }
   else
   {
      m_uAnalyze = 0;
   }
}

void CLogiDoc::OnUpdateSimulateAnalyze(CCmdUI* pCmdUI)
{
   //pCmdUI->SetCheck(m_uAnalyze != 0);
   // Not Implemented, disable button
   pCmdUI->Enable(FALSE);
}

void CLogiDoc::OnViewZoomIn()
{
   m_iZoom++;
   UpdateAllViews(NULL, HINT_UPDATE_ZOOM);
}

void CLogiDoc::OnUpdateViewZoomIn(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(m_iZoom < MAXZOOMFACTOR ? TRUE : FALSE);
}

void CLogiDoc::OnViewZoomNormal()
{
   m_iZoom = 0;
   UpdateAllViews(NULL, HINT_UPDATE_ZOOM);
}

void CLogiDoc::OnUpdateViewZoomNormal(CCmdUI* /* pCmdUI */)
{
}

void CLogiDoc::OnViewZoomOut()
{
   m_iZoom--;
   UpdateAllViews(NULL, HINT_UPDATE_ZOOM);
}

void CLogiDoc::OnUpdateViewZoomOut(CCmdUI* pCmdUI)
{
   pCmdUI->Enable(m_iZoom > -MAXZOOMFACTOR ? TRUE : FALSE);
}

void CLogiDoc::OnViewSnapToGrid()
{
   m_bSnapToGrid = !m_bSnapToGrid;
}

void CLogiDoc::OnUpdateViewSnapToGrid(CCmdUI* pCmdUI)
{
   if (m_bSnapToGrid)
      pCmdUI->SetCheck(1);
   else
      pCmdUI->SetCheck(0);
}

void CLogiDoc::OnViewColorWires()
{
   m_bColorWires = !m_bColorWires;
   if (!m_bColorWires)
   {
      // revert colored wires to black
      POSITION pos = GetFirstViewPosition();
      while (pos != NULL)  ((CLogiView*)GetNextView(pos))->OnUpdate(NULL, HINT_UPDATE_WINDOW, NULL);
   }
}

void CLogiDoc::OnUpdateViewColorWires(CCmdUI* pCmdUI)
{
   if (m_bColorWires)
      pCmdUI->SetCheck(1);
   else
      pCmdUI->SetCheck(0);
}

//OnEscape is intended to Stop or Reset the Simulator if it is Running or Paused
//In draw mode it is intended to make the Selector the active tool
//TODO: Get this working properly
void CLogiDoc::OnEscape()
{
   ::MessageBox(::GetFocus(),"Who hit escape?","Error", MB_OK | MB_ICONEXCLAMATION);
   /* When accel keys in simulation mode is fixed, this will be a problem.
   Processing escape as described below may interfere with the keyboard device.
   Must not use any normal ASCII (code < 127) key characters as accel keys when a
   keyboard device has the focus.

   if (m_bKeepGoing)
   {
   // || m_bPause
   OnSimulateStop();
   ::MessageBox(::GetFocus(),"The simulator should have stopped","Error", MB_OK | MB_ICONEXCLAMATION);
   return;
   }
   else
   //CLogiView::OnDrawSelector();
   return;
   */
}

// Returns modifiable list of page names.

CStringArray *CLogiDoc::GetPageNames()
{
   // Count how many pages there are
   int iMaxPage = GetMaxPage();

   // Truncate page name array to number of pages
   m_PageNames.SetSize(iMaxPage);

   // Pad m_PageNames with blank strings for untitled pages
   int index;
   for (index = m_PageNames.GetUpperBound() + 1; index <= iMaxPage-1; index++)
      m_PageNames.Add("");

   return &m_PageNames;
}

//Seems we needed to catch SC_CLOSE in SPLITFRM.CPP
void CLogiDoc::OnFileClose()
{
   m_bCloseNotExit=TRUE;
   CDocument::OnFileClose();
}
