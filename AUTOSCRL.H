// autoscrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAutoScrollView view

class CAutoScrollView : public CScrollView
{
   DECLARE_DYNAMIC(CAutoScrollView)
protected:
   CAutoScrollView(); // protected constructor used by dynamic creation

   // Attributes
public:
   BOOL        m_bAutoScroll;
   BOOL        m_bIsScrolling;

   // Operations
public:
   BOOL         IsAutoScrolling()
   {
      return m_bIsScrolling;
   }
   ;
   void         EnableAutoScrolling (BOOL bMode)
   {
      m_bAutoScroll = bMode;
   }
   ;
protected:
   virtual void OnAutoScroll(CPoint point, BOOL bBeforeScroll);

   // Operations
public:

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CAutoScrollView)
public:
   virtual void OnDraw(CDC* pDC);
protected:
   //}}AFX_VIRTUAL

   // Implementation
protected:
   void AutoScroll(UINT nRefMessage);

   //{{AFX_MSG(CAutoScrollView)
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
}
;
/////////////////////////////////////////////////////////////////////////////
