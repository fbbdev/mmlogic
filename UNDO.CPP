// Undo.cpp - implementation for UndoStack objects
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

////////////////////////////////////////////////////////////////////////////
// CUndoStack

///////////////////////////
// Constructs a CUndoStack.

CUndoStack::CUndoStack()
{
   m_iCurrentState = NotInProgress;
   m_iTransactionCookie = 0;
}

///////////////////////////////////////////////////////
// Begins a transaction, which is a sequence of actions
// performed as a group. When undo/redo encounters
// a transaction, it executes the entire transaction.
// EndTransaction must be called after all actions
// to be grouped are Pushed. Transactions may be nested.
//
// For example, if the user highlights several objects
// then chooses cut, a single transaction will contain
// all of the delete actions performed.
//
// Parameters: description - a string which describes
//             the transaction to the user.

int CUndoStack::BeginTransaction(LPCTSTR description)
{
   m_iTransactionCookie++;

   CUndoElement *pUndo = new CUndoElement();
   pUndo->m_iTransactionCookie = m_iTransactionCookie;
   pUndo->m_iAction = CUndoElement::StartOfTransaction;
   pUndo->m_str = description;

   InternalPush(pUndo);
   return 0;
}

/////////////////////////////////////////////////////
// Ends a transaction started with BeginTransaction.
// The description parameter should be the same
// string passed to the call to BeginTransaction.
//
// Parameters: description - a string which describes
//             the transaction to the user.

void CUndoStack::EndTransaction(LPCTSTR description)
{  
   CUndoElement *pUndo = new CUndoElement();
   pUndo->m_iTransactionCookie = m_iTransactionCookie;
   pUndo->m_iAction = CUndoElement::EndOfTransaction;
   pUndo->m_str = description;

   InternalPush(pUndo);

   m_iTransactionCookie--;
}

///////////////////////////////////////////////////////
// Pushes an action onto the stack. An action describes
// a command that can be undone/redone.
//
// Parameters: pLogiObj - pointer to CLogiObj involved.
//
//             iActionType - the action performed.
//			   From CUndoElement::enum
//
//             str - (default: NULL) a string; the
//             meaning depends on iActionType.

void CUndoStack::Push(CLogiObj* pLogiObj, int iActionType, LPCTSTR str)
{
   CUndoElement *pUndo = new CUndoElement();
   pUndo->m_pLogiObj = pLogiObj;
   pUndo->m_iAction = iActionType;
   pUndo->m_str = str;

   InternalPush(pUndo);
}

///////////////////////////////////////////////////////
// Pushes a Move action onto the stack.
//
// Parameters: pLogiObj - pointer to CLogiObj involved.
//
//             rect - the rectangle describing
//             the object's previous position.

void CUndoStack::PushMove(CLogiObj* pLogiObj, CRect &rect)
{
   CUndoElement *pUndo = new CUndoElement();
   pUndo->m_pLogiObj = pLogiObj;
   pUndo->m_iAction = CUndoElement::Move;
   pUndo->m_rect = rect;

   InternalPush(pUndo);
}

///////////////////////////////////////////////////////
// Pushes an Edit action onto the stack.
// PushEdit is called prior to making changes
// to the object state. The state is saved
// through serialization.
//
// Parameters: pLogiObj - pointer to CLogiObj involved.

void CUndoStack::PushEdit(CLogiObj* pLogiObj)
{
   CUndoElement *pUndo = new CUndoElement();
   pUndo->m_pLogiObj = pLogiObj;
   pUndo->m_iAction = CUndoElement::Edit;

   CMemFile memFile(4);   
   CArchive ar(&memFile, CArchive::store);

   ASSERT(pLogiObj->m_pDocument != NULL);
   ar.m_pDocument = pLogiObj->m_pDocument;
   pLogiObj->Serialize(ar);
   ar.Close();

   pUndo->m_dwLen = (DWORD) memFile.GetLength();
   pUndo->m_pVar = memFile.Detach();

   InternalPush(pUndo);
}

////////////////////////////////////////////////////////
// Private method called by public PushXXX() methods.
// If an undo is not in progress, pushes pUndo to the
// undo stack, otherwise pushes pUndo to the redo stack.
// Whenever a push is made to the undo stack, the
// redo stack is cleared.
//
// Parameters: pUndo - the CUndoElement describing
//             the action to be pushed.

void CUndoStack::InternalPush(CUndoElement *pUndo)
{
   pUndo->Init();

   if (m_iCurrentState == NotInProgress)
      InternalReset(&m_redo);

   if (m_iCurrentState == UndoInProgress)
      m_redo.AddHead(pUndo);
   else
   {
      m_undo.AddHead(pUndo);
   }
}

///////////////////////////////////////////
// Reverts the action at the top
// of the undo stack.
//
// Parameters: pDoc - the current CLogiDoc.

void CUndoStack::Undo(CLogiDoc* pDoc)
{
   m_iCurrentState = UndoInProgress;
   InternalUndo(pDoc, &m_undo);
   m_iCurrentState = NotInProgress;
}

///////////////////////////////////////////
// Reverts the action at the top
// of the redo stack.
//
// Parameters: pDoc - the current CLogiDoc.

void CUndoStack::Redo(CLogiDoc* pDoc)
{
   m_iCurrentState = RedoInProgress;
   InternalUndo(pDoc, &m_redo);
   m_iCurrentState = NotInProgress;
}

///////////////////////////////////////////////////////////////
// Private method called by Undo() and Redo() to
// revert an action on either the undo or the redo stack.
// If the element at the top of the stack is a transaction,
// all actions in the transaction (and any nested transactions)
// are reverted.
//
// Parameters: pDoc - the current CLogiDoc.
//             pUndoList - which stack (undo/redo).

void CUndoStack::InternalUndo(CLogiDoc* pDoc, CObList *pUndoList)
{
   CUndoElement* pUndo;
   int i_WhichTransaction = -1;

   if (pUndoList->IsEmpty()) return;

   BOOL bKeepGoing = FALSE;

   do
   {

      pUndo = (CUndoElement*) pUndoList->RemoveHead();
      if (i_WhichTransaction == -1)
      {
         if (pUndo->m_iAction == CUndoElement::EndOfTransaction)
         {
            i_WhichTransaction = pUndo->m_iTransactionCookie;
            BeginTransaction(pUndo->m_str);
            bKeepGoing = TRUE;
         }
      }
      else if (pUndo->m_iAction == CUndoElement::StartOfTransaction)
      {
         if (i_WhichTransaction == pUndo->m_iTransactionCookie)
         {
            EndTransaction(pUndo->m_str);
            bKeepGoing = FALSE;
         }
      }

      pUndo->Undo(pDoc);

      delete pUndo;
      pUndo = NULL;
   }
   while (bKeepGoing);

   pDoc->UpdateAllViews(NULL);
}

////////////////////////////////////////
// Clears both the undo and redo stacks.

void CUndoStack::Reset()
{
   InternalReset(&m_redo);
   InternalReset(&m_undo);
}

//////////////////////////////////////////////////
// Private method called by Reset() and other
// methods to clear either the undo or redo stack.
//
// Parameters: pList - which stack (undo/redo).

void CUndoStack::InternalReset(CObList *pList)
{
   POSITION pos;
   CUndoElement *und;
   int pass;

   // Two passes. Delete wires first, other objects second.

   for (pass=0; pass<=1; pass++)
   {
      //TEDO: this seems like an odd for loop, would a while be better?
      for (pos = pList->GetHeadPosition(); pos != NULL; )
      {
         und = (CUndoElement *) pList->GetNext(pos);
         und->Cleanup(pass);

         // On last pass, delete CUndoElement too
         if (pass == 1)
         {
            delete und;
            und = NULL;
         }
      }
   }

   pList->RemoveAll();
}

/////////////////////////////////////////
// Checks status of undo stack.

BOOL CUndoStack::CanUndo()
{
   return !m_undo.IsEmpty();
}

/////////////////////////////////////////
// Checks status of redo stack.

BOOL CUndoStack::CanRedo()
{
   return !m_redo.IsEmpty();
}

////////////////////////////////////////////////
// Retrieves the description associated with
// the item on the top of the undo stack.

CString CUndoStack::GetUndoDescription()
{
   if (m_undo.IsEmpty())
      return "";

   return ((CUndoElement *) m_undo.GetHead())->GetUndoDescription();
}

////////////////////////////////////////////////
// Retrieves the description associated with
// the item on the top of the redo stack.

CString CUndoStack::GetRedoDescription()
{
   if (m_redo.IsEmpty())
      return "";

   return ((CUndoElement *) m_redo.GetHead())->GetRedoDescription();
}

//////////////////////////
// CUndoStack desctructor.

CUndoStack::~CUndoStack()
{
   Reset();
}

////////////////////////////////////////////////////////////////////////////
// CUndoElement

/////////////////////////////////////////
// Returns the description describing the
// element in the "undo" context.
//
// Therefore, the string describes the
// action that was performed.

CString CUndoElement::GetUndoDescription()
{
   switch (m_iAction)
   {
   case CUndoElement::StartOfTransaction:
   case CUndoElement::EndOfTransaction:
      return m_str;
   case CUndoElement::Delete:
      return "Delete";
   case CUndoElement::Add:
      return "Add";
   case CUndoElement::Move:
      return "Move";
   case CUndoElement::Rename:
      return "Rename";
   case CUndoElement::Edit:
      return "Edit";
   default:
      ASSERT(FALSE);
      return "";
   }
}

/////////////////////////////////////////
// Returns the description describing the
// element in the "redo" context.
//
// Therefore, the string describes the
// INVERSE operation of the action that
// was performed.

CString CUndoElement::GetRedoDescription()
{
   switch (m_iAction)
   {
   case CUndoElement::StartOfTransaction:
   case CUndoElement::EndOfTransaction:
      return m_str;
   case CUndoElement::Delete:
      return "Add";
   case CUndoElement::Add:
      return "Delete";
   case CUndoElement::Move:
      return "Move";
   case CUndoElement::Rename:
      return "Rename";
   case CUndoElement::Edit:
      return "Edit";
   default:
      ASSERT(FALSE);
      return "";
   }
}

////////////////////////////////////////////////
// Init is called when new item pushed on stack.

void CUndoElement::Init()
{
   switch (m_iAction)
   {
   case CUndoElement::Delete:
      if (m_pLogiObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
         ((CLogiWire *) m_pLogiObj)->CleanupReferences();
      else
         ((CLogiGate *) m_pLogiObj)->CleanupReferences();
      break;
   }
}

///////////////////////////////////////
// Undo is called to reverse the action
// described by the CUndoElement.

void CUndoElement::Undo(CLogiDoc* pDoc)
{
   switch (m_iAction)
   {
   case CUndoElement::Delete:
      pDoc->Add(m_pLogiObj);
      if (m_pLogiObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
         pDoc->ReWire(m_pLogiObj->m_position, (CLogiWire*) m_pLogiObj, m_pLogiObj->m_iPage);
      break;
   case CUndoElement::Add:
      pDoc->Remove(m_pLogiObj);
      break;
   case CUndoElement::Move:
      pDoc->Move(m_pLogiObj, m_rect);
      break;
   case CUndoElement::Rename:
      pDoc->Rename(m_pLogiObj, m_str);
      break;
   case CUndoElement::Edit:
      CMemFile memFile((BYTE *) m_pVar, m_dwLen, 0);
      CArchive ar(&memFile, CArchive::load);
      ASSERT(m_pLogiObj->m_pDocument != NULL);
      ar.m_pDocument = m_pLogiObj->m_pDocument;
      pDoc->Edit(m_pLogiObj, ar);
      ar.Close();
      memFile.Close();
      delete m_pVar;
      m_pVar = NULL;

      break;
   }
}

////////////////////////////////////////////////
// Cleanup is called when a stack containing
// the object is reset.
//
// Currently, the cleanup has two passes, where
// wires are deleted on pass 0 and everything
// else is deleted on pass 1.
//
// Parameters: pass - the pass number,
//             which is 0 or 1.

void CUndoElement::Cleanup(int pass)
{
   if (pass == 0)
   {
      // Delete wires on first pass
      if (m_iAction == CUndoElement::Delete)
      {
         if (m_pLogiObj->IsKindOf(RUNTIME_CLASS(CLogiWire)))
         {
            delete m_pLogiObj;
            m_pLogiObj = NULL;
         }
      }
      else if (m_iAction == CUndoElement::Edit)
      {
         delete m_pVar;
         m_pVar = NULL;
      }
   }
   else if (pass == 1)
   {
      // Delete everything else on second pass
      if (m_iAction == CUndoElement::Delete)
      {
         if (m_pLogiObj != NULL)
         {
            delete m_pLogiObj;
            m_pLogiObj = NULL;
         }
      }
   }
}

/////////////////////////////////////////////////////////////////////////////
