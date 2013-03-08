// Logidoc.h : interface of the CLogiDoc class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

//Now AnodeNULL is document specific. Use
// pLogiObj->m_pDocument->m_pAnodeNULL or
// pView->GetDocument()->m_pAnodeNULL to access.
//extern Anode AnodeNULL;

class CLogiView;
class CLogiObj;
class CLogiWire;

class CLogiDoc : public CDocument
{
protected: // create from serialization only
   CLogiDoc();
   DECLARE_DYNCREATE(CLogiDoc)

   // Attributes
public:

   CObList* GetObjects()
   {
      return &m_objects;
   }

   const CSize& GetSize() const
   {
      return m_size;
   }

   int GetMapMode() const
   {
      return m_nMapMode;
   }

   COLORREF GetPaperColor() const
   {
      return m_paperColor;
   }

   BOOL GetGridOn() const
   {
      return m_bGrid;
   }

   BOOL GetSnapToGrid() const
   {
      return m_bSnapToGrid;
   }

   CPoint GetGridSizes() const
   {
      return CPoint(m_uGridWidth, m_uGridHeight);
   }

   void ComputePageSize();

   // Operations
public:
   int GetZoom(int i);
   CLogiObj* ObjectAt(const CPoint& point, int iPage);
   CLogiObj* ObjectAtContact(const CPoint& point, int* io, int iPage);
   CLogiObj* ObjectAtContactExact(const CPoint& point, int* io, int iPage);
   void Draw(CDC* pDC, CLogiView* pView);
   void Add(CLogiObj* pObj, BOOL bAllowUndo = TRUE);
   void Remove(CLogiObj* pObj, BOOL bAllowUndo = TRUE);
   void Move(CLogiObj* pObj, CRect &rect, BOOL bAllowUndo = TRUE);
   void Rename(CLogiObj* pObj, LPCTSTR newname, BOOL bAllowUndo = TRUE);
   void Edit(CLogiObj* pObj, CArchive &ar, BOOL bAllowUndo = TRUE);
   void BeginManualEdit(CLogiObj* pObj, BOOL bAllowUndo = TRUE);
   void UpdateProbe();
   void Simulate(UINT iMode);
   BOOL Reset(UINT iMode);
   void Halt();
   CLogiWire* ReWire(const CRect& rect, CLogiWire* pWireObj, int iPage);
   int CLogiDoc::GetMaxPage();
   BOOL CheckForStrays();
   CStringArray *CLogiDoc::GetPageNames();
   //   void TrySetModifiedFlag( BOOL bModified = TRUE );

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CLogiDoc)
public:
   virtual void Serialize(CArchive& ar);   // overridden for document i/o
   virtual BOOL OnNewDocument();
protected:
   virtual BOOL SaveModified();
   //}}AFX_VIRTUAL

   // Implementation
public:
   virtual ~CLogiDoc();
#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

   CObList NodeList;
   CObList EventQueue;
   CObList PostEventQueue;
   CObList KeyboardMessageQueue;
   CObList MouseMessageQueue;
   CObList NetworkMessageQueue;
   CObList UpdateNodeQueue;
   CObList UpdateNodeQueue2;
   CObList CallPostQueue;
   HACCEL m_haccel;

   //are we in the middle of simulation?
   BOOL m_bSimulating;
   //should we color the wires?
   BOOL m_bColorWires;
   //does the user want to stop simulation and close doc / exit app?
   BOOL  m_bForceStopAndExitApp;
   BOOL m_bForceStopAndCloseDoc;
   BOOL m_bCloseNotExit;

   //does the user want to stop simulation to run another?
   BOOL m_bForceStopAndChangeDoc;

   BOOL m_bKeepGoing;
   BOOL m_bWasUp;
   BOOL m_bPause;
   BOOL m_bHalt; // flag if a component fails to Initialize
   long m_uProbe;
   long m_uAnalyze;
   Anode* pAnodeProbe;
   //   Anode* pAnodeDummy;
   long m_uCycleCount;
   CLogiObj* KeyBoardObj;
   Anode *m_pAnodeNULL;

   //   protected:

   CObList m_objects;
   CUndoStack m_undo;
   CSize m_size;
   int m_nMapMode;
   COLORREF m_paperColor;
   int m_iUnconnected;
   BOOL m_bReadOnly;
   CFont m_cfScreen;
   CPen m_cpBlack;
   CPen m_cpBlue;
   CPen m_cpGreen;
   CPen m_cpRed;
   CPen m_cpPurple;
   CPen m_cpGrey;
   CBrush m_cbWhite;
   CBrush m_cbBlue;
   CBrush m_cbGrey;
   BOOL m_bGrid;
   BOOL m_bSnapToGrid;
   int m_iZoom;
   UINT m_uGridWidth;
   UINT m_uGridHeight;
   UINT m_uCanvasWidth;
   UINT m_uCanvasHeight;
   int m_iVersionMinor;
   int m_iVersionMajor;
   BOOL m_bSimRateSpecified; // FALSE - as fast as possible
   int m_iSimRate; // in Hz, if m_bSimRateSpecified == TRUE
   CStringArray m_PageNames;

   // Generated message map functions
   //   protected:
   //{{AFX_MSG(CLogiDoc)
   afx_msg void OnViewPaperColor();
   afx_msg void OnSimulateRun();
   afx_msg void OnSimulateSetup();
   afx_msg void OnSimulateStop();
   afx_msg void OnUpdateSimulateRun(CCmdUI* pCmdUI);
   afx_msg void OnUpdateSimulateSetup(CCmdUI* pCmdUI);
   afx_msg void OnUpdateSimulateStop(CCmdUI* pCmdUI);
   afx_msg void OnSimulateDraw();
   afx_msg void OnUpdateSimulateDraw(CCmdUI* pCmdUI);
   afx_msg void OnSimulatePause();
   afx_msg void OnUpdateSimulatePause(CCmdUI* pCmdUI);
   afx_msg void OnSimulateStep();
   afx_msg void OnUpdateSimulateStep(CCmdUI* pCmdUI);
   afx_msg void OnSimulateReset();
   afx_msg void OnUpdateSimulateReset(CCmdUI* pCmdUI);
   afx_msg void OnSimulateProbe();
   afx_msg void OnUpdateSimulateProbe(CCmdUI* pCmdUI);
   afx_msg void OnViewGrid();
   afx_msg void OnUpdateViewGrid(CCmdUI* pCmdUI);
   afx_msg void OnSimulateAnalyze();
   afx_msg void OnUpdateSimulateAnalyze(CCmdUI* pCmdUI);
   afx_msg void OnViewZoomIn();
   afx_msg void OnUpdateViewZoomIn(CCmdUI* pCmdUI);
   afx_msg void OnViewZoomNormal();
   afx_msg void OnUpdateViewZoomNormal(CCmdUI* pCmdUI);
   afx_msg void OnViewZoomOut();
   afx_msg void OnUpdateViewZoomOut(CCmdUI* pCmdUI);
   afx_msg void OnViewSnapToGrid();
   afx_msg void OnUpdateViewSnapToGrid(CCmdUI* pCmdUI);
   afx_msg void OnViewColorWires();
   afx_msg void OnUpdateViewColorWires(CCmdUI* pCmdUI);
   afx_msg void OnEscape();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
public:
   void OnFileClose();
}
;

/////////////////////////////////////////////////////////////////////////////
