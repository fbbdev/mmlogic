// Socket.cpp : implementation of the CSocketWnd class
//
// Copyright (C) 1993-1994 George Mills and Softronics, Inc. Corporation
// All rights reserved.
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MAX_PENDING_CONNECTS 4  /* The backlog allowed for listen() */
#define MAX_PACKET_SIZE 1024
#define SD_BOTH 2

/////////////////////////////////////////////////////////////////////////////
// CSocketWnd

IMPLEMENT_DYNCREATE(CSocketWnd, CWnd)

BEGIN_MESSAGE_MAP(CSocketWnd, CWnd)
   //{{AFX_MSG_MAP(CSocketWnd)
   ON_MESSAGE(ID_NET_ACCEPTFINISH, OnNetAcceptfinish)
   ON_MESSAGE(ID_NET_CONNECTACK, OnNetConnectack)
   ON_MESSAGE(ID_NET_CONNECTFINISH, OnNetConnectfinish)
   //}}AFX_MSG_MAP
   // Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSocketWnd construction/destruction

CSocketWnd::CSocketWnd()
{
   bConnected = FALSE;    // Flag that send socket is connected
   bBusy      = FALSE;    // Flag that send socket is busy
   bNetworkOn = FALSE;    // flag for send enabled (enables message processing)

   phe = NULL;            // Pointer to Host Entry for send
}

CSocketWnd::~CSocketWnd()
{
}

// void CSocketWnd::SetView(CLogiView *pview)
//   {
//   pView = pview;
//   }

BOOL CSocketWnd::ConnectOn(int iport, const char *networkaddress, CLogiDoc* pdoc,  CLogiNetworkGate *pobj)
{
   long ConnectMessage;
   char szThisHost[80];

   pObj = pobj;
   pDoc = pdoc;

   // start network in case it's not up

   NetworkStartup();

   // sanity check first

   if (hWinSockDLL == NULL)
   {
      return(FALSE);
   }

   if (bNetworkOn)
   {
      return(FALSE);
   }

   bNetworkOn = TRUE;

   // bring up hidden window to receive messages for "this" connection

   //   if (!Create(NULL, "Socket", WS_CHILD, CRect(0,0,0,0), pView, 99))
   if (!Create(NULL, "Socket", WS_CHILD, CRect(0,0,0,0), AfxGetMainWnd(), IDR_MAINFRAME))
   {
      return(FALSE);
   }

   // save the port

   iPort = iport;

   // get sockets

   if ((iSocket = lpsocket( AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
   {
      MessageBox( WSAGetLastErrorString(0), "socket(iSocketet)");
      return(FALSE);
   }

   // if no address then listen

   if (networkaddress == NULL)
   {
      lpgethostname(szThisHost, sizeof(szThisHost));
      ConnectMessage = ID_NET_ACCEPTFINISH;
   }

   // else call

   else
   {
      strncpy(szThisHost, networkaddress, sizeof(szThisHost));
      ConnectMessage = ID_NET_CONNECTFINISH;
   }

   if (phe == NULL)
   {
      phe = (PHOSTENT) malloc(MAXGETHOSTSTRUCT);
      memset(phe, 0, MAXGETHOSTSTRUCT);
   }

   unsigned long sockAddr;

   // if not IP address then must IP name

   if ((sockAddr = lpinet_addr(szThisHost)) == INADDR_NONE)
   {

      // get address of remote machine

      if (!lpWSAAsyncGetHostByName ( m_hWnd, ConnectMessage, szThisHost, (LPSTR) phe, MAXGETHOSTSTRUCT ))
      {
         MessageBox( WSAGetLastErrorString(0), "WSAAsyncGetHostByName()");
         return(FALSE);
      }
   }

   // else build a fake HOSTENT

   else
   {

      phe->h_length = sizeof(sockAddr);
      phe->h_addr_list = (char **) (phe + sizeof(HOSTENT));
      phe->h_addr_list[0] = (char *) (phe->h_addr_list + sizeof(void *));
      memcpy(phe->h_addr, (LPCSTR) &sockAddr, sizeof(sockAddr));

      // now fake success

      PostMessage(ConnectMessage);

      // I don't know why this won't work, also it still needs DNS.

      //      if (!lpWSAAsyncGetHostByAddr ( m_hWnd, ConnectMessage, (LPCSTR) &sockAddr, 4, PF_INET, (LPSTR) phe, MAXGETHOSTSTRUCT ))
      //         {
      //         MessageBox( WSAGetLastErrorString(0), "WSAAsyncGetHostByAddr()");
      //         return(FALSE);
      //         }
   }

   // wait for callback

   return(TRUE);

}

void CSocketWnd::ConnectOff(void)
{

   // tell handler not to do anything with messages for network send

   if (bNetworkOn)
   {
      bNetworkOn = FALSE;
      bConnected = FALSE;    // Flag that send socket is connected
      bBusy      = FALSE;    // Flag that send socket is busy

      if (lpshutdown(iSocket,SD_BOTH) == SOCKET_ERROR)
      {
         MessageBox( WSAGetLastErrorString(0), "shutdown()");
      }

      if (lpclosesocket(iSocket) == SOCKET_ERROR)
      {
         MessageBox( WSAGetLastErrorString(0), "closesocket()");
      }

      if (phe)
      {
         free(phe);
         phe = NULL;           // Pointer to Host Entry for send
      }

      //      HWND hWnd = Detach();
      //      if (IsWindow(hWnd))
      //         {
      //         ::DestroyWindow(hWnd);
      //         }

      DestroyWindow();
      //      ::DestroyWindow(Detach());
   }
}

BOOL CSocketWnd::SendData(char *Data)
{
   if (bConnected && !bBusy)
   {

      // send the data

      if ((lpsend( iSocket, Data, 1, 0 )) == SOCKET_ERROR)
      {

         if (lpWSAGetLastError() != WSAEWOULDBLOCK)
         {
            MessageBox(WSAGetLastErrorString(0), "send(iSocket)");
            return(FALSE);
         }

         // Idle Until it's ok again.

         MessageBox("UtOh1", "Unexpected Programing error");

         bBusy = TRUE;
         return(TRUE);

      }
   }
   else
   {
      return(FALSE);
   }

   return(TRUE);

}

LRESULT CSocketWnd::OnNetConnectack( WPARAM /*wParam*/, LPARAM lParam)
{
   //   SOCKADDR_IN acc_sin;    /* Accept socket address - internet style */
   //   int acc_sin_len;        /* Accept socket address length */
   char Buffer[MAX_PACKET_SIZE];
   int status;

   if (WSAGETASYNCERROR(lParam) != 0)
   {
      MessageBox(WSAGetLastErrorString(WSAGETASYNCERROR(lParam)), "WSAAsyncGetHostByNameCallBack()");
      return 0L;
   }

   // queue message if enabled

   if (bNetworkOn)
   {

      // update flags based on event type

      switch (WSAGETSELECTEVENT(lParam))
      {
      case FD_READ:
         {
            memset(Buffer, 0, MAX_PACKET_SIZE);

            // get the data

            if ((status = lprecv( iSocket, Buffer, MAX_PACKET_SIZE-1, 0)) == SOCKET_ERROR)
            {
               int iErrorCode;

               // if block wait til we get called again

               if ((iErrorCode = lpWSAGetLastError()) == WSAEWOULDBLOCK)
               {
                  MessageBox("UtOh2", "Unexpected Programing error");
                  return 0L;
               }

               MessageBox(WSAGetLastErrorString(0), "recv(iSocket)");
               return 0L;
            }

            // if something is there (better be) then process it

            if (status != 0)
            {
               int i;

               // Queue up each char

               for (i=0;i<status;i++)
               {
                  pDoc->NetworkMessageQueue.AddTail(new ANetworkMessage(pObj, pDoc, WSAGETSELECTEVENT(lParam), Buffer[i]));
                  pDoc->NetworkMessageQueue.AddTail(new ANetworkMessage(pObj, pDoc, 0L, 0));
               }
            }

            return 0L;
         }

      case FD_WRITE:
         {
            // allow another frame to go out.

            bBusy = FALSE;
            break;
         }

      case FD_CONNECT:
         {
            // flag it's ok to start firing

            bConnected = TRUE;
            pDoc->NetworkMessageQueue.AddTail(new ANetworkMessage(pObj, pDoc, WSAGETSELECTEVENT(lParam), 0));
            break;
         }

      case FD_ACCEPT:
         {
            bConnected = TRUE;

            //            acc_sin_len = sizeof(acc_sin);

            //            if ((iSocket = lpaccept( iSocket,(struct sockaddr FAR *) &acc_sin, (int FAR *) &acc_sin_len )) == INVALID_SOCKET)
            if ((iSocket = lpaccept( iSocket, NULL, NULL )) == INVALID_SOCKET)
            {
               MessageBox(WSAGetLastErrorString(0), "accept(receivesock)");
            }
            pDoc->NetworkMessageQueue.AddTail(new ANetworkMessage(pObj, pDoc, WSAGETSELECTEVENT(lParam), 0));
            break;
         }

      case FD_CLOSE:
         {
            // done

            bConnected = FALSE;
            pDoc->NetworkMessageQueue.AddTail(new ANetworkMessage(pObj, pDoc, WSAGETSELECTEVENT(lParam), 0));
            break;
         }
      }
   }

   return 0L;
}

LRESULT CSocketWnd::OnNetConnectfinish( WPARAM /*wParam*/, LPARAM lParam)
{

   // should these not be automatic?
   SOCKADDR_IN sockAddr;

   if (WSAGETASYNCERROR(lParam) != 0)
   {
      MessageBox(WSAGetLastErrorString(WSAGETASYNCERROR(lParam)), "WSAAsyncGetHostByNameCallBack()");
      return 0L;
   }

   // always start clean

   memset(&sockAddr, 0, sizeof(SOCKADDR_IN));

   // what else is there

   sockAddr.sin_family = AF_INET;

   // I wonder if this in network order

   memcpy((char FAR *)&(sockAddr.sin_addr), phe->h_addr, phe->h_length);

   // set ports

   sockAddr.sin_port = lphtons((unsigned short) iPort);        /* Convert to network ordering */

   //   Associate an address with a socket. (bind)

   //   if (lpbind( iSocket, (struct sockaddr FAR *) &sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
   //      {
   //      MessageBox(WSAGetLastErrorString(0), "bind(sendsock)");
   //      return 0L;
   //      }

   // watch for connect

   if (lpWSAAsyncSelect( iSocket, m_hWnd, ID_NET_CONNECTACK, FD_ACCEPT | FD_CONNECT | FD_WRITE | FD_READ | FD_CLOSE) == SOCKET_ERROR)
   {
      MessageBox(WSAGetLastErrorString(0), "WSAAsyncSelect(iSocket) FD_CONNECT");
   }

   // lets try now

   if (lpconnect( iSocket, (PSOCKADDR) &sockAddr, sizeof( sockAddr)) == SOCKET_ERROR)
   {
      int iErrorCode;

      if ((iErrorCode = lpWSAGetLastError()) != WSAEWOULDBLOCK)
      {
         MessageBox(WSAGetLastErrorString(0), "connect(iSocket)");
         return 0L;
      }
   }

   // fire event that connection is made

   if (bNetworkOn)
   {
      // xxxx
   }

   return 0L;
}

LRESULT CSocketWnd::OnNetAcceptfinish( WPARAM /*wParam*/, LPARAM lParam)
{

   SOCKADDR_IN sockAddr;  /* Local socket - internet style */

   if (WSAGETASYNCERROR(lParam) != 0)
   {
      MessageBox(WSAGetLastErrorString(WSAGETASYNCERROR(lParam)), "WSAAsyncGetHostByNameCallBack()");
      return 0L;
   }

   // always start clean

   memset(&sockAddr, 0, sizeof(SOCKADDR_IN));

   // what else is there

   sockAddr.sin_family = AF_INET;

   sockAddr.sin_addr.s_addr = lphtonl(INADDR_ANY);

   // memcpy((char FAR *)&(sockAddr.sin_addr), phe->h_addr, phe->h_length);

   // set ports

   sockAddr.sin_port = lphtons((unsigned short) iPort);        /* Convert to network ordering */

   // int flag = 1;

   // lpsetsockopt(iSocket, SOL_SOCKET, SO_REUSEADDR, (LPCSTR) &flag, sizeof(int));

   // Associate an address with a socket. (bind)

   if (lpbind( iSocket, (struct sockaddr FAR *) &sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
   {
      MessageBox(WSAGetLastErrorString(0), "bind(receivesock)");
      return 0L;
   }

   // listen for connect

   if (lplisten( iSocket, MAX_PENDING_CONNECTS ) == SOCKET_ERROR)
   {
      MessageBox(WSAGetLastErrorString(0), "listen(receivesock)");
      return 0L;
   }

   // watch for when connect happens

   if (lpWSAAsyncSelect( iSocket, m_hWnd, ID_NET_CONNECTACK, FD_ACCEPT | FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
   {
      MessageBox(WSAGetLastErrorString(0), "WSAAsyncSelect(receivesock) FD_ACCEPT");
   }

   // queue this event

   if (bNetworkOn)
   {
      // xxx
   }

   return 0L;
}
