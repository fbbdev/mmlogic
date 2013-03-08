// LogiText.h - interface for CLogiTextGate and derivatives
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

class CLogiView;
class CLogiDoc;
class CLogiGate;
class CLogiRobotGate;

/////////////////////////////////////////////////////////////////////////////

class CLogiBitmapGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiBitmapGate);
   CLogiBitmapGate();

   CLogiBitmapGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iStyle=0, BOOL bPlayground=FALSE, const char *pSoundCommands="\\NUL");
   void Draw(CDC* pDC, CLogiView* pView);
   void Simulate(CLogiDoc* pDoc);
   void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   void ResizeRect();
   void LoadBase();

   // Implementation
public:
   CString m_csFileName;
   UINT m_uIndex;
   int m_iStyle;
   BOOL m_bPlayground;
   CDib m_cdPictures[256];
   CDib m_cdPicture;
   BOOL m_bLoaded;
   CLogiRobotGate* m_Robot[16];

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;
