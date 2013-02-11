// Message.h : interface of the CLogiView class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

/////////////////////////////////////////////////////////////////////////////

class CLogiRobotGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiRobotGate);
   CLogiRobotGate();

   CLogiRobotGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc,
      int iStyle = 0,
      int iPosition = 0,
      int iPositionX = 0,
      int iPositionY = 0,
      int iHotspot = 0,
      int iHotspotX = 0,
      int iHotspotY = 0,
      const char *pFileName="\\NUL");
   void Simulate(CLogiDoc* pDoc);
   void Draw(CDC* pDC, CLogiView* pView);
   void DrawRobot(CDC* pDC, CLogiView* pView);
   void Animate(CLogiView* pView);
   void Action(CLogiView* pView, BOOL bDown, const CPoint& point);

   // Implementation
public:
   int m_iLastState;
   UINT m_uTemp;
   CString m_csFileName;
   int m_iStyle;
   int m_iPosition;
   int m_iPositionX;
   int m_iPositionY;
   int m_iHotspot;
   int m_iHotspotX;
   int m_iHotspotY;
   CLogiBitmapGate* m_Playground;
   CRect m_crLastdraw;
   CRect m_crNewdraw;
   CSize m_csSize;
   CPoint m_cpPoint;

   BOOL m_bConnected;    // Flag that send socket is connected
   //   CDib m_cdBackGround;
   CDib m_cdRobots[16];

   int m_xPos;
   int m_yPos;
   int m_uIndex;
   int m_uDirection;

   int ChooseRobot();
   BOOL ConnectOn();

   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

