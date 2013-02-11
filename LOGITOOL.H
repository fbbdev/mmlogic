// Logitool.h - interface for CLogiTool and derivatives
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

class CLogiView;

class CLogiTool
{
   // Constructors
public:
   CLogiTool(LogiShape nLogiShape);

   // Overridables
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnLButtonDblClk(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnLButtonUp(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnRButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnMouseMove(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual BOOL OnSetCursor(CLogiView* pView, CWnd* pWnd, UINT nHitTest, UINT message);
   virtual void OnCancel();
   virtual void OnAutoScroll(CLogiView* pView, const CPoint& point, BOOL bBefore);

   // Attributes
   LogiShape m_LogiShape;
   CPoint m_cpDownPoint;

   static CLogiTool* FindTool(LogiShape LogiShape);
   static CPtrList c_tools;
   static CPoint c_down;
   //   static CPoint c_downt;
   static UINT c_nDownFlags;
   static CPoint c_last;
   //   static CPoint c_lastt;
   static LogiShape c_LogiShape;
}
;

class CSelectTool : public CLogiTool
{
   // Constructors
public:
   CSelectTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnLButtonDblClk(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnLButtonUp(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnRButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnMouseMove(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual BOOL OnSetCursor(CLogiView* pView, CWnd* pWnd, UINT nHitTest, UINT message);
   virtual void OnAutoScroll(CLogiView* pView, const CPoint& point, BOOL bBefore);

   // Attributes
   CObList m_prevPositions; // original positions of moved objects
   BOOL m_bUserMove; // previous positions should be stored
}
;

class CGateTool : public CLogiTool
{
   // Constructors
public:
   CGateTool(LogiShape nLogiShape);

   // Implementation
   virtual void OnLButtonDblClk(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnLButtonUp(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnRButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnMouseMove(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual BOOL OnSetCursor(CLogiView* pView, CWnd* pWnd, UINT nHitTest, UINT message);
}
;

class CANDGateTool : public CGateTool
{
   // Constructors
public:
   CANDGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CXORGateTool : public CGateTool
{
   // Constructors
public:
   CXORGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CORGateTool : public CGateTool
{
   // Constructors
public:
   CORGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CINVERTGateTool : public CGateTool
{
   // Constructors
public:
   CINVERTGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CTristateGateTool : public CGateTool
{
   // Constructors
public:
   CTristateGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CBusGateTool : public CGateTool
{
   // Constructors
public:
   CBusGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class COscillatorGateTool : public CGateTool
{
   // Constructors
public:
   COscillatorGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CClockGateTool : public CGateTool
{
   // Constructors
public:
   CClockGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CTimerGateTool : public CGateTool
{
   // Constructors
public:
   CTimerGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CLedGateTool : public CGateTool
{
   // Constructors
public:
   CLedGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CSwitchGateTool : public CGateTool
{
   // Constructors
public:
   CSwitchGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CSelectGateTool : public CGateTool
{
   // Constructors
public:
   CSelectGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CBuzzerGateTool : public CGateTool
{
   // Constructors
public:
   CBuzzerGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CNULLGateTool : public CGateTool
{
   // Constructors
public:
   CNULLGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CLed7GateTool : public CGateTool
{
   // Constructors
public:
   CLed7GateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CAsciidisplayGateTool : public CGateTool
{
   // Constructors
public:
   CAsciidisplayGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CAsciikeyboardGateTool : public CGateTool
{
   // Constructors
public:
   CAsciikeyboardGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CGroundGateTool : public CGateTool
{
   // Constructors
public:
   CGroundGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CPlusGateTool : public CGateTool
{
   // Constructors
public:
   CPlusGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CPortinGateTool : public CGateTool
{
   // Constructors
public:
   CPortinGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CPortoutGateTool : public CGateTool
{
   // Constructors
public:
   CPortoutGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CReadfileGateTool : public CGateTool
{
   // Constructors
public:
   CReadfileGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CSignalreceiverGateTool : public CGateTool
{
   // Constructors
public:
   CSignalreceiverGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CSignalsenderGateTool : public CGateTool
{
   // Constructors
public:
   CSignalsenderGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CAnalyzeGateTool : public CGateTool
{
   // Constructors
public:
   CAnalyzeGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CSoundwaveGateTool : public CGateTool
{
   // Constructors
public:
   CSoundwaveGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CWritefileGateTool : public CGateTool
{
   // Constructors
public:
   CWritefileGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CFlipflopGateTool : public CGateTool
{
   // Constructors
public:
   CFlipflopGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CKeypadGateTool : public CGateTool
{
   // Constructors
public:
   CKeypadGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CBitmapGateTool : public CGateTool
{
   // Constructors
public:
   CBitmapGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CCounterGateTool : public CGateTool
{
   // Constructors
public:
   CCounterGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CRandomGateTool : public CGateTool
{
   // Constructors
public:
   CRandomGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CBreakGateTool : public CGateTool
{
   // Constructors
public:
   CBreakGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CBitbucketGateTool : public CGateTool
{
   // Constructors
public:
   CBitbucketGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CNetworkGateTool : public CGateTool
{
   // Constructors
public:
   CNetworkGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CRobotGateTool : public CGateTool
{
   // Constructors
public:
   CRobotGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CMemoryGateTool : public CGateTool
{
   // Constructors
public:
   CMemoryGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CTapedriveGateTool : public CGateTool
{
   // Constructors
public:
   CTapedriveGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CMuxGateTool : public CGateTool
{
   // Constructors
public:
   CMuxGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CAluGateTool : public CGateTool
{
   // Constructors
public:
   CAluGateTool();

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CWireTool : public CLogiTool
{
   // Constructors
public:
   Anode* pStartAnode;
   Anode* pEndAnode;
   CLogiWire* m_pObj;
   BOOL m_bShowErrorCursor;
   CWireTool();
   CLogiGate* pStartGateObj;
   CLogiGate* pEndGateObj;
   int StartIO;
   int EndIO;

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnLButtonDblClk(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnLButtonUp(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnRButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnMouseMove(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual BOOL OnSetCursor(CLogiView* pView, CWnd* pWnd, UINT nHitTest, UINT message);
}
;

class CTextTool : public CLogiTool
{
   // Constructors
public:
   //   Anode* pStartAnode;
   //   Anode* pEndAnode;
   CLogiTextGate* m_pObj;
   CTextTool();
   //   CLogiGate* pStartGateObj;
   //   CLogiGate* pEndGateObj;
   //   int StartIO;
   //   int EndIO;

   // Implementation
   virtual void OnLButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnLButtonDblClk(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnLButtonUp(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnRButtonDown(CLogiView* pView, UINT nFlags, const CPoint& point);
   virtual void OnMouseMove(CLogiView* pView, UINT nFlags, const CPoint& point);
}
;

class CPreviousPosition : public CObject
{
public:
   CPreviousPosition(CLogiObj *pLogiObj, CRect &rect)
      : m_pLogiObj(pLogiObj), m_rect(rect) {};

   CLogiObj *m_pLogiObj;
   CRect m_rect;
}
;

////////////////////////////////////////////////////////////////////////////
