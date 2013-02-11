// Logiobj.h - interface for CLogiObj and derivatives
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

class CLogiView;
class CLogiDoc;
class CLogiGate;
class Anode;

typedef struct tagBITMAPINFO16
{
   BITMAPINFOHEADER bmiHeader;
   RGBQUAD          bmiColors[16];
}
BITMAPINFO16;

typedef struct tagLOGPALETTE16
{
   WORD         palVersion;
   WORD         palNumEntries;
   PALETTEENTRY palPalEntry[16];
}
LOGPALETTE16;

extern CObList NodeList;
extern CObList EventQueue;

/////////////////////////////////////////////////////////////////////////////
// CLogiObj - base class for all 'Logiable objects'

class CLogiObj : public CObject
{
protected:
   DECLARE_SERIAL(CLogiObj);
   CLogiObj();

   // Constructors
public:
   CLogiObj(const CRect& position, LogiShape shape, int ipage, CLogiDoc* pdoc);

   // Attributes
   CRect m_position;
   CSize m_size;
   CLogiDoc* m_pDocument;
   LogiShape m_Logishape;
   int m_iPage;
   int m_iUndo; // not used

   virtual int GetHandleCount();
   virtual CPoint GetHandle(int nHandle);
   CRect GetHandleRect(int nHandleID, CLogiView* pView);
   virtual HCURSOR GetHandleCursor(int nHandle);

   // Operations
   virtual void Draw(CDC* pDC, CLogiView* pView = NULL);
   enum TrackerState
   {
      normal, selected, active
   }
   ;
   virtual void DrawTracker(CDC* pDC, TrackerState state);
   virtual void MoveTo(const CRect& positon, CLogiView* pView = NULL);
   virtual int HitTest(CPoint point, CLogiView* pView, BOOL bSelected);
   virtual BOOL Intersects(const CRect& rect);
   virtual void MoveHandleTo(int nHandle, CPoint point, CLogiView* pView = NULL);
   virtual CLogiObj* Clone(CLogiDoc* pDoc = NULL);
   virtual BOOL HasText();
   virtual CString GetText();
   virtual void SetText(LPCTSTR text);

   virtual void OnOpen(CLogiView* /*pView*/)
   {
   }
   ;
   void Invalidate();
   void Remove();

   // Implementation
public:
   virtual ~CLogiObj();
   virtual void Serialize(CArchive& ar);
#ifdef _DEBUG
   void AssertValid();
#endif

   // implementation data
protected:
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiGate : public CLogiObj
{
protected:
   DECLARE_SERIAL(CLogiGate);
   CLogiGate();

public:
   CString Name;
   Anode* Node[48];
   CObList Wire[48];
   CPoint Contact[48];
   int Contacts;
   int Inputs;
   int Outputs;
   UINT GateID;
   UINT GateIDs[8];
   long EventCycle;
   unsigned int i;
   CRect rect;
   //   RGBQUAD rgbOrig[16];
   BITMAPINFO16 m_Bmi;
   RGBQUAD rgbTransparent;
   RGBQUAD rgbWhite;
   RGBQUAD rgbBlack;
   HRSRC hResource;
   HGLOBAL hBitmap;
   BITMAPINFO* pBmi;
   DWORD size;
   BOOL bInitialized;

   CLogiGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int outputs, int inputs, UINT gateID, LogiShape Logishape);
   virtual void CleanupReferences();
   virtual void Simulate(CLogiDoc* pDoc);
   virtual BOOL PostSimulate(CLogiDoc* pDoc);
   virtual void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual void Cleanup(CLogiView* pView);
   virtual void Action(CLogiView* pView, BOOL bDown, const CPoint& point);
   void Connect(int io, Anode* pAnode);

   // Implementation
public:
   virtual ~CLogiGate();
   virtual void Serialize(CArchive& ar);
   virtual void Draw(CDC* pDC, CLogiView* pView = NULL);
   virtual int GetHandleCount();
   virtual CPoint GetHandle(int nHandle);
   virtual HCURSOR GetHandleCursor(int nHandle);
   virtual void MoveHandleTo(int nHandle, CPoint point, CLogiView* pView = NULL);
   virtual CLogiObj* Clone(CLogiDoc* pDoc); // should be = 0
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiANDGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiANDGate);
   CLogiANDGate();

   CLogiANDGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iAnd2inputs=0, BOOL bAndDemorgan=FALSE);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iInputs;
   BOOL m_bDemorgan;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiXORGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiXORGate);
   CLogiXORGate();

   CLogiXORGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iAnd2inputs=0, BOOL bAndDemorgan=FALSE);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iInputs;
   BOOL m_bDemorgan;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiORGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiORGate);
   CLogiORGate();

   CLogiORGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iOr2inputs=0, BOOL bOrDemorgan=FALSE);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iInputs;
   BOOL m_bDemorgan;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiINVERTGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiINVERTGate);
   CLogiINVERTGate();

   CLogiINVERTGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bInvertDemorgan=FALSE);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   BOOL m_bDemorgan;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiTristateGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiTristateGate);
   CLogiTristateGate();

   CLogiTristateGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bTristateDemorgan=FALSE, BOOL bTristateLO=FALSE);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   BOOL m_bDemorgan;
   BOOL m_bAssertLO;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiBusGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiBusGate);
   CLogiBusGate();

   CLogiBusGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iInputs=0, BOOL bDummy2=FALSE);
   void Simulate(CLogiDoc* pDoc);
   BOOL PostSimulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iInputs;
   BOOL m_bDummy2;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiOscillatorGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiOscillatorGate);
   CLogiOscillatorGate();

   CLogiOscillatorGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int CountHI=1, int CountLO=1);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_Fire;
   int m_iCountHI;
   int m_iCountLO;

   virtual void Serialize(CArchive& ar);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();
   virtual void OnOpen(CLogiView* pView);

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiClockGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiClockGate);
   CLogiClockGate();

   CLogiClockGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int Seconds=0, BOOL Spare=FALSE);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   UINT m_uTemp;
   int m_iSeconds;
   int m_bSpare;

   virtual void Serialize(CArchive& ar);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();
   virtual void OnOpen(CLogiView* pView);

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiTimerGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiTimerGate);
   CLogiTimerGate();

   CLogiTimerGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, UINT Delay=1000, BOOL Spare=FALSE);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   clock_t m_tFire;
   UINT m_uDelay;
   BOOL m_bSpare;

   virtual void Serialize(CArchive& ar);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();
   virtual void OnOpen(CLogiView* pView);

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiLedGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiLedGate);
   CLogiLedGate();

   CLogiLedGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iLedRed=0, int iLedBlink=1);
   void Simulate(CLogiDoc* pDoc);
   void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);

   // Implementation
public:
   int m_iRed;
   int m_iBlink;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;


/////////////////////////////////////////////////////////////////////////////

class CLogiSwitchGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiSwitchGate);
   CLogiSwitchGate();

   CLogiSwitchGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int SwitchOn=1, int SwitchToggle=0);
   void Simulate(CLogiDoc* pDoc);
   void Action(CLogiView* pView, BOOL bDown, const CPoint& point);
   void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);

   // Implementation
public:
   int m_iOn;
   int m_iToggle;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiSelectGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiSelectGate);
   CLogiSelectGate();

   CLogiSelectGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iInitial=0, int iDummy=0);
   void Simulate(CLogiDoc* pDoc);
   void Action(CLogiView* pView, BOOL bDown, const CPoint& point);
   void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);

   // Implementation
public:
   UINT m_uTemp;
   int m_iInitial;
   int m_iDummy;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiBuzzerGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiBuzzerGate);
   CLogiBuzzerGate();

   CLogiBuzzerGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int m_iFreq=1000, int m_iDuration=20);
   void Simulate(CLogiDoc* pDoc);
   void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);

   // Implementation
public:
   int m_iFreq;
   int m_iDuration;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;


/////////////////////////////////////////////////////////////////////////////

class CLogiNULLGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiNULLGate);
   CLogiNULLGate();

   CLogiNULLGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int ipass=0, int ifloat=0);
   void Simulate(CLogiDoc* pDoc);
   BOOL PostSimulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iPass;
   int m_iFloat;
   BOOL m_bDemorgan;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiLed7Gate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiLed7Gate);
   CLogiLed7Gate();

   CLogiLed7Gate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iLed7Red=0, int iLed7Inputs=1);
   void Draw(CDC* pDC, CLogiView* pView);
   void Simulate(CLogiDoc* pDoc);
   void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);

   // Implementation
public:
   int m_iRed;
   int m_iInputs;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiAsciidisplayGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiAsciidisplayGate);
   CLogiAsciidisplayGate();

   CLogiAsciidisplayGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc);
   void Animate(CLogiView* pView);
   void Draw(CDC* pDC, CLogiView* pView);
   void Simulate(CLogiDoc* pDoc);
   virtual void Initialize(CLogiView* pView, UINT iMode);

   // Implementation
public:
   char m_cText[16][16];
   int m_iCol[16];
   int m_iRow;
   CFont m_font;
   CFont* pOldFont;
   CPen* pOldPen;
   CBitmap* pOldBmp;
   CBrush* pOldBrush;
   int m_iLastState;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiAsciikeyboardGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiAsciikeyboardGate);
   CLogiAsciikeyboardGate();

   CLogiAsciikeyboardGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bAscii=FALSE);
   void Simulate(CLogiDoc* pDoc);
   void Action(CLogiView* pView, BOOL bDown, const CPoint& point);
   void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   void Message(CLogiView* pView, UINT nChar, BOOL bDown);

   // Implementation
public:
   int m_iSpare;
   BOOL m_bAscii;
   UINT m_nChar;
   int m_iDown;
   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiGroundGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiGroundGate);
   CLogiGroundGate();

   CLogiGroundGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiPlusGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiPlusGate);
   CLogiPlusGate();

   CLogiPlusGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiPortinGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiPortinGate);
   CLogiPortinGate();

   CLogiPortinGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, UINT iIooutAddress = 0, UINT iIooutInitial = 0);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   UINT m_uTemp;
   UINT m_iAddress;
   UINT m_iInitial;
   int m_iLastState;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiPortoutGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiPortoutGate);
   CLogiPortoutGate();

   CLogiPortoutGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, UINT iIooutAddress = 0, UINT iIooutInitial = 0);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   UINT m_iAddress;
   UINT m_iInitial;
   int m_iLastState;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiReadfileGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiReadfileGate);
   CLogiReadfileGate();

   CLogiReadfileGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iFormat=0, const char *pFileName="\\NUL");
   void Simulate(CLogiDoc* pDoc);
   void Animate(CLogiView* pView);

   // Implementation
public:
   CString m_csFileName;
   int m_iFormat;
   FILE *m_pFile;
   int m_iLastState;

   virtual void Serialize(CArchive& ar);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiSignalreceiverGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiSignalreceiverGate);
   CLogiSignalreceiverGate();

   CLogiSignalreceiverGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iDummy=0, const char *pSignalName="None");
   void Draw(CDC* pDC, CLogiView* pView);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   CString m_csSignalName;
   int m_iDummy;
   CLogiGate* m_Mate;
   CFont m_font;
   CFont* pOldFont;
   CPen* pOldPen;
   CBitmap* pOldBmp;
   CBrush* pOldBrush;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();
   virtual BOOL HasText();
   virtual CString GetText();
   virtual void SetText(LPCTSTR text);

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiSignalsenderGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiSignalsenderGate);
   CLogiSignalsenderGate();

   CLogiSignalsenderGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iDummy=0, const char *pSignalName="None");
   void Draw(CDC* pDC, CLogiView* pView);
   void Simulate(CLogiDoc* pDoc);
   BOOL PostSimulate(CLogiDoc* pDoc);

   // Implementation
public:
   CString m_csSignalName;
   int m_iDummy;
   //CLogiGate* m_Mate;
   CObList m_Mates;
   CFont m_font;
   CFont* pOldFont;
   CPen* pOldPen;
   CBitmap* pOldBmp;
   CBrush* pOldBrush;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();;
   virtual BOOL HasText();
   virtual CString GetText();
   virtual void SetText(LPCTSTR text);

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiAnalyzeGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiAnalyzeGate);
   CLogiAnalyzeGate();

   CLogiAnalyzeGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iDummy=0, const char *pSignalName="None");
   void Draw(CDC* pDC, CLogiView* pView);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   CString m_csSignalName;
   int m_iDummy;
   CLogiGate* m_Mate;
   CFont m_font;
   CFont* pOldFont;
   CPen* pOldPen;
   CBitmap* pOldBmp;
   CBrush* pOldBrush;
   CList< int, int > m_wlHistory;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();
   virtual BOOL HasText();
   virtual CString GetText();
   virtual void SetText(LPCTSTR text);

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiSoundwaveGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiSoundwaveGate);
   CLogiSoundwaveGate();

   CLogiSoundwaveGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bSoundWait=1, const char *pSoundCommands="\\NUL");
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   CString m_csFileName;
   BOOL m_bWait;
   int m_iLastState;

   virtual void Serialize(CArchive& ar);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiWritefileGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiWritefileGate);
   CLogiWritefileGate();

   CLogiWritefileGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iFormat=0, const char *pFileName="\\NUL");
   void Simulate(CLogiDoc* pDoc);
   void Animate(CLogiView* pView);

   // Implementation
public:
   CString m_csFileName;
   BOOL m_iFormat;
   FILE *m_pFile;
   int m_iLastState;

   virtual void Serialize(CArchive& ar);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiFlipflopGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiFlipflopGate);
   CLogiFlipflopGate();

   CLogiFlipflopGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int istyle=0, BOOL bedge=FALSE, BOOL bPresetClear=FALSE);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iState;
   int m_iMasterState;
   int m_iStyle;
   BOOL m_bEdge;
   BOOL m_bPresetClear;
   int m_iLastState;
   int m_iPresetLine; // contact number
   int m_iClearLine; // contact number

   virtual void Serialize(CArchive& ar);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();
   virtual void ResizeRect();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiKeypadGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiKeypadGate);
   CLogiKeypadGate();

   CLogiKeypadGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc);
   void Action(CLogiView* pView, BOOL bDown, const CPoint& point);
   void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   WORD m_nKey;
   BOOL m_bDown;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiCounterGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiCounterGate);
   CLogiCounterGate();

   CLogiCounterGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iSize=0, UINT iInit=0);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iLastState;
   UINT m_uTemp;
   int m_iSize;
   UINT m_iInit;

   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiRandomGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiRandomGate);
   CLogiRandomGate();

   CLogiRandomGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iSpare=0, unsigned int uSeed=0);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iLastState;
   UINT m_uTemp;
   int m_iSpare;
   UINT m_uSeed;
   UINT m_uSeedLast;

   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiBreakGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiBreakGate);
   CLogiBreakGate();

   CLogiBreakGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc);
   void Simulate(CLogiDoc* pDoc);
   void Animate(CLogiView* pView);
   virtual void Initialize(CLogiView* pView, UINT iMode);

   // Implementation
public:
   int m_iLastState;
   UINT m_uTemp;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiBitbucketGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiBitbucketGate);
   CLogiBitbucketGate();

   CLogiBitbucketGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iLastState;
   UINT m_uTemp;

   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiNetworkGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiNetworkGate);
   CLogiNetworkGate();
   ~CLogiNetworkGate();

   CLogiNetworkGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iDirection=0, UINT uPort=4096, const char *pName="remote.host.name");
   void Simulate(CLogiDoc* pDoc);
   virtual void Animate(CLogiView* pView);
   void Message(CLogiDoc* pDoc, LPARAM lParam, WPARAM wParam);

   // Implementation
public:
   int m_iDirection;
   int m_uPort;
   CString m_csName;
   CSocketWnd m_soSocket;
   UINT m_nChar;
   int m_nEnable;
   LPARAM m_lParam;
   BOOL m_bQueue;
   int m_nCount;

   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual void Cleanup(CLogiView* pView);
   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiMemoryGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiMemoryGate);
   CLogiMemoryGate();

   CLogiMemoryGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iFormat=1, const char *pFileName="\\NUL");
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   CString m_csFileName;
   int m_iFormat;
   int m_iAddressBits;
   int m_iMemorySize;
   int m_iWriteNodeNumber;
   CArray< unsigned short, unsigned short > m_cMemory; // type must be at least 16 bits

   virtual void Serialize(CArchive& ar);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();
   virtual void ResizeRect();

protected:

   friend class CRectTool;
}
;

class CLogiTapedriveGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiTapedriveGate);
   CLogiTapedriveGate();

   CLogiTapedriveGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, int iFormat=1, int iSize=1024, int iStart=0, const char *pFileName="\\NUL");
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   CString m_csFileName;
   int m_iLastState;
   int m_iFormat;
   int m_iPosition;
   int m_iStartPosition;
   int m_iSize;
   CArray< unsigned short, unsigned short > m_cMemory;

   virtual void Serialize(CArchive& ar);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiMuxGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiMuxGate);
   CLogiMuxGate();

   CLogiMuxGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bMuxDeMux=0, int iStyle=0);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iStyle;
   BOOL m_bDeMux;
   int m_iState;

   virtual void Serialize(CArchive& ar);
   virtual void Initialize(CLogiView* pView, UINT iMode);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;

/////////////////////////////////////////////////////////////////////////////

class CLogiAluGate : public CLogiGate
{
protected:
   DECLARE_SERIAL(CLogiAluGate);
   CLogiAluGate();

   CLogiAluGate(const CRect& position, const char *name, int ipage, CLogiDoc* pdoc, BOOL bAluDeAlu=0, int iAlu2Inputs=0);
   void Simulate(CLogiDoc* pDoc);

   // Implementation
public:
   int m_iInputs;
   BOOL m_bDeAlu;

   virtual void Serialize(CArchive& ar);
   virtual CLogiObj* Clone(CLogiDoc* pDoc);
   virtual void OnOpen(CLogiView* pView);
   virtual void MoveTo(const CRect& position, CLogiView* pView = NULL);
   virtual void SetGateID();
   virtual void SetContacts();

protected:

   friend class CRectTool;
}
;
