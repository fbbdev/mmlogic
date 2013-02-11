// Logiwire.h - interface for CLogiWire and derivatives
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

class CLogiView;
class CLogiDoc;
class CLogiGate;

/////////////////////////////////////////////////////////////////////////////

class CLogiWire : public CLogiObj
{
protected:
   DECLARE_SERIAL(CLogiWire);
   CLogiWire();

public:
   CString Name;
   int StartIO;
   int EndIO;
   int m_iRoute;
   BOOL m_bHide;
   CLogiGate *pStartGateObj;
   CLogiGate *pEndGateObj;
   CPen* pOldPen;

   CLogiWire(const CRect& position, char *name, int ipage, CLogiDoc* pdoc);

   // Implementation
public:
   virtual ~CLogiWire();
   virtual void CleanupReferences();
   virtual void Serialize(CArchive& ar);
   virtual void Draw(CDC* pDC, CLogiView* pView = NULL);
   virtual BOOL Intersects(const CRect& rect);
   virtual int GetHandleCount();
   virtual CPoint GetHandle(int nHandle);
   virtual HCURSOR GetHandleCursor(int nHandle);
   virtual void MoveHandleTo(int nHandle, CPoint point, CLogiView* pView = NULL);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);

protected:

   friend class CRectTool;
}
;
