// LogiText.h - interface for CLogiTextGate and derivatives
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

class CLogiView;
class CLogiDoc;
class CLogiGate;

/////////////////////////////////////////////////////////////////////////////

class CLogiTextGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiTextGate);
   CLogiTextGate();

public:
   CString Name;
   CString m_pTextText;
   CString m_pTextArray[17];
   CString m_csFileName;
   BOOL m_bLoaded;
   int m_iStyle;
   UINT m_uIndex;

   CFont* pOldFont;
   CPen* pOldPen;
   CBrush* pOldBrush;
   CBitmap* pOldBmp;
   TEXTMETRIC tm;
   LOGFONT lf;
   CBitmap* pcbGate;

   CLogiTextGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iStyle=0, const char *pFileName = "\\NUL", const char *pText="Text");

   // Implementation
public:
   virtual ~CLogiTextGate();
   virtual void Serialize(CArchive& ar);
   virtual void Draw(CDC* pDC, CLogiView* pView = NULL);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);

   virtual void Simulate(CLogiDoc* pDoc);
   virtual void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetContacts();
   virtual BOOL HasText();
   virtual CString GetText();
   virtual void SetText(LPCTSTR text);

   void ResizeRect();

protected:

   friend class CRectTool;
}
;
