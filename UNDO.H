// Undo.h - interface for CUndoStack
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

class CUndoElement : public CObject
{
public:
   enum { Illegal = 0, Delete = 1, Add = 2, Move = 3, Rename = 4, Edit = 5,
      StartOfTransaction = 98, EndOfTransaction = 99 };
   int m_iAction;
   int m_iTransactionCookie;
   CString m_str;
   CLogiObj *m_pLogiObj;
   CRect m_rect;
   DWORD m_dwLen;
   void *m_pVar;

   CString GetUndoDescription();
   CString GetRedoDescription();
   void Init();
   void Undo(CLogiDoc* pDoc);
   void Cleanup(int iPass);
};

class CUndoStack : public CObject
{
public:
   CUndoStack();
   ~CUndoStack();
   void Push(CLogiObj* pLogiObj, int iActionType, LPCTSTR str = NULL);
   void PushMove(CLogiObj* pLogiObj, CRect &rect);
   void PushEdit(CLogiObj* pLogiObj);

   int BeginTransaction(LPCTSTR description);
   void EndTransaction(LPCTSTR description);

   void Undo(CLogiDoc* pDoc);
   void Redo(CLogiDoc* pDoc);
   void Reset();

   BOOL CanUndo();
   BOOL CanRedo();
   CString GetUndoDescription();
   CString GetRedoDescription();

private:
   enum {NotInProgress = 0, UndoInProgress = 1, RedoInProgress = 2};
   BOOL m_iCurrentState;
   int m_iTransactionCookie;

   CObList m_undo;
   CObList m_redo;

   void InternalPush(CUndoElement *pUndo);
   void InternalUndo(CLogiDoc* pDoc, CObList *pUndoList);
   void InternalReset(CObList *pList);
};


