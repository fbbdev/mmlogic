// Logivw.h : interface of the CLogiView class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

// Hints for UpdateAllViews/OnUpdate
#define HINT_UPDATE_WINDOW      0
#define HINT_UPDATE_LOGIOBJ     1
#define HINT_UPDATE_SELECTION   2
#define HINT_DELETE_SELECTION   3
#define HINT_UPDATE_ZOOM        4
#define HINT_REMOVE_LOGIOBJ     5

class CLogiObj;

class CLogiView : public CAutoScrollView
{
protected: // create from serialization only
   CLogiView();
   DECLARE_DYNCREATE(CLogiView)

   // Attributes
public:
   CLogiDoc* GetDocument()
   {
      return (CLogiDoc*)m_pDocument;
   }
   void SetPageSize(CSize size);
   CRect GetInitialPosition();

   // Operations
public:
   void DocToClient(CRect& rect);
   void DocToClient(CPoint& point);
   void ClientToDoc(CPoint& point);
   void ClientToDoc(CRect& rect);
   void Select(CLogiObj* pObj, BOOL bAdd = FALSE);
   void SelectWithinRect(CRect rect, int iPage, BOOL bAdd = FALSE);
   void Deselect(CLogiObj* pObj);
   void CloneSelection();
   void UpdateActiveItem();
   void InvalObj(CLogiObj* pObj);
   void Remove(CLogiObj* pObj);
   void PasteNative(COleDataObject& dataObject);
   void SetPage(int iPage);

protected:
   void DisplayFindReplace(BOOL bFind);
   void RemoveFromFindReplace(CLogiObj* pObj);

   // Implementation
public:
   virtual ~CLogiView();

#ifdef _DEBUG
   virtual void AssertValid() const;
   virtual void Dump(CDumpContext& dc) const;
#endif

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CLogiView)
public:
   virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo );
   virtual void OnDraw(CDC* pDC);  // overridden to Logi this view
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
   virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
   virtual void OnActivateView(BOOL bActivate, CView* pActiveView, CView* pDeactiveView);
   virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll);
   virtual BOOL IsSelected(const CObject* pDocItem) const;
protected:
   virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
   virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
   virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
   virtual void OnInitialUpdate(); // called first time after construct
   //   virtual BOOL PreTranslateMessage(MSG* pMsg); 
   //}}AFX_VIRTUAL

public:
   void DrawGrid(CDC* pDC);
   virtual void OnAutoScroll(CPoint point, BOOL bBefore);

   static CLIPFORMAT m_cfLogi; // custom clipboard format

   CObList m_selection;
   CObList m_selectionTemp;
   COLORREF m_gridColor;
   BOOL m_bActive; // is the view active?
   int m_iPage;

   CRect m_rLastDraw; // rect of last draw

   CFindReplaceDialog *m_frDialog; // NULL if not displayed
   BOOL m_bfrFind; // in Find mode, not Replace mode
   BOOL m_bfrInitSearch; // initial search?
   BOOL m_bfrDown; // search down?
   POSITION m_frPos; // current find/replace position, if applicable
   CLogiObj *m_pLastMatch; // object of last match, if applicable
   CObList m_frObjects; // find/replace selection

   // Generated message map functions
protected:
   //{{AFX_MSG(CLogiView)
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
   afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
   afx_msg void OnDrawSelector();
   afx_msg void OnDrawWire();
   afx_msg void OnDrawANDGate();
   afx_msg void OnDrawORGate();
   afx_msg void OnDrawINVERTGate();
   afx_msg void OnDrawOscillatorGate();
   afx_msg void OnDrawLedGate();
   afx_msg void OnDrawSwitchGate();
   afx_msg void OnDrawBuzzerGate();
   afx_msg void OnDrawNULLGate();
   afx_msg void OnUpdateDrawSelector(CCmdUI* pCmdUI);
   afx_msg void OnUpdateDrawWire(CCmdUI* pCmdUI);
   afx_msg void OnUpdateDrawANDGate(CCmdUI* pCmdUI);
   afx_msg void OnUpdateDrawORGate(CCmdUI* pCmdUI);
   afx_msg void OnUpdateDrawINVERTGate(CCmdUI* pCmdUI);
   afx_msg void OnUpdateDrawOscillatorGate(CCmdUI* pCmdUI);
   afx_msg void OnUpdateDrawLedGate(CCmdUI* pCmdUI);
   afx_msg void OnUpdateDrawSwitchGate(CCmdUI* pCmdUI);
   afx_msg void OnUpdateDrawBuzzerGate(CCmdUI* pCmdUI);
   afx_msg void OnUpdateDrawNULLGate(CCmdUI* pCmdUI);
   afx_msg void OnUpdateSingleSelect(CCmdUI* pCmdUI);
   afx_msg void OnUpdateAnySelect(CCmdUI* pCmdUI);
   afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
   afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
   afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
   afx_msg void OnUpdateEditProperties(CCmdUI* pCmdUI);
   afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
   afx_msg void OnEditSelectAll();
   afx_msg void OnEditClear();
   afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
   afx_msg void OnUpdateEditReplace(CCmdUI* pCmdUI);
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnEditCopy();
   afx_msg void OnEditCut();
   afx_msg void OnEditPaste();
   afx_msg void OnSetFocus(CWnd* pOldWnd);
   afx_msg void OnEditProperties();
   afx_msg void OnDrawLed7Gate();
   afx_msg void OnUpdateDrawLed7Gate(CCmdUI* pCmdUI);
   afx_msg void OnDrawAsciidisplayGate();
   afx_msg void OnUpdateDrawAsciidisplayGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawAsciikeyboardGate();
   afx_msg void OnUpdateDrawAsciikeyboardGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawGroundGate();
   afx_msg void OnUpdateDrawGroundGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawPlusGate();
   afx_msg void OnUpdateDrawPlusGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawPortinGate();
   afx_msg void OnUpdateDrawPortinGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawPortoutGate();
   afx_msg void OnUpdateDrawPortoutGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawReadfileGate();
   afx_msg void OnUpdateDrawReadfileGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawSignalreceiverGate();
   afx_msg void OnUpdateDrawSignalreceiverGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawSignalsenderGate();
   afx_msg void OnUpdateDrawSignalsenderGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawSoundwaveGate();
   afx_msg void OnUpdateDrawSoundwaveGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawTextGate();
   afx_msg void OnUpdateDrawTextGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawWritefileGate();
   afx_msg void OnUpdateDrawWritefileGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawFlipflopGate();
   afx_msg void OnUpdateDrawFlipflopGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawKeypadGate();
   afx_msg void OnUpdateDrawKeypadGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawBitmapGate();
   afx_msg void OnUpdateDrawBitmapGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawCounterGate();
   afx_msg void OnUpdateDrawCounterGate(CCmdUI* pCmdUI);
   afx_msg void OnDrawBreakGate();
   afx_msg void OnUpdateDrawBreakGate(CCmdUI* pCmdUI);
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnDrawMemoryGate();
   afx_msg void OnUpdateDrawMemoryGate(CCmdUI* pCmdUI);
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnSetFont();
   afx_msg void OnDrawMux();
   afx_msg void OnUpdateDrawMux(CCmdUI* pCmdUI);
   afx_msg void OnDrawBitbucket();
   afx_msg void OnUpdateDrawBitbucket(CCmdUI* pCmdUI);
   afx_msg void OnDrawAlu();
   afx_msg void OnUpdateDrawAlu(CCmdUI* pCmdUI);
   afx_msg void OnDrawRandom();
   afx_msg void OnUpdateDrawRandom(CCmdUI* pCmdUI);
   afx_msg void OnFilePrint();
   afx_msg void OnDrawXor();
   afx_msg void OnUpdateDrawXor(CCmdUI* pCmdUI);
   afx_msg void OnDrawClock();
   afx_msg void OnUpdateDrawClock(CCmdUI* pCmdUI);
   afx_msg void OnDrawTimer();
   afx_msg void OnUpdateDrawTimer(CCmdUI* pCmdUI);
   afx_msg void OnViewNextpage();
   afx_msg void OnUpdateViewNextpage(CCmdUI* pCmdUI);
   afx_msg void OnViewPreviouspage();
   afx_msg void OnUpdateViewPreviouspage(CCmdUI* pCmdUI);
   afx_msg void OnDrawRobot();
   afx_msg void OnUpdateDrawRobot(CCmdUI* pCmdUI);
   afx_msg void OnDrawNetwork();
   afx_msg void OnUpdateDrawNetwork(CCmdUI* pCmdUI);
   afx_msg void OnDrawSelectgate();
   afx_msg void OnUpdateDrawSelectgate(CCmdUI* pCmdUI);
   afx_msg void OnViewSnapSelectiontogrid();
   afx_msg void OnUpdateViewSnapSelectiontogrid(CCmdUI* pCmdUI);
   afx_msg void OnDrawTristategate();
   afx_msg void OnUpdateDrawTristategate(CCmdUI* pCmdUI);
   afx_msg void OnDrawBus();
   afx_msg void OnUpdateDrawBus(CCmdUI* pCmdUI);
   afx_msg void OnDrawAnalyze();
   afx_msg void OnUpdateDrawAnalyze(CCmdUI* pCmdUI);
   afx_msg void OnDrawTapedrive();
   afx_msg void OnUpdateDrawTapedrive(CCmdUI* pCmdUI);
   afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnEditUndo();
   afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
   afx_msg void OnEditRedo();
   afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
   afx_msg void OnViewGotoPage();
   afx_msg void OnUpdateGotoPage(CCmdUI* pCmdUI);
   afx_msg LONG OnFindReplace(WPARAM wParam, LPARAM lParam);
   afx_msg void OnEditFind();
   afx_msg void OnEditReplace();
   afx_msg void OnDrawBisectwire();
   afx_msg void OnUpdateDrawBisectwire(CCmdUI* pCmdUI);
   //}}AFX_MSG
   afx_msg void OnUpdateIndicatorCycle(CCmdUI* pCmdUI);
   afx_msg void OnUpdateIndicatorPage(CCmdUI* pCmdUI);
   afx_msg void OnEscape();
   DECLARE_MESSAGE_MAP()
}
;

/////////////////////////////////////////////////////////////////////////////
