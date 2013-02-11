#include "stdafx.h"

// WinSock is loaded on the fly these are pointers to functions used

LPWSAASYNCSELECT lpWSAAsyncSelect;
LPCONNECT lpconnect;
LPRECV lprecv;
LPWSAGETLASTERROR lpWSAGetLastError;
LPACCEPT lpaccept;
LPHTONS lphtons;
LPHTONL lphtonl;
LPINET_ADDR lpinet_addr;
LPSETSOCKOPT lpsetsockopt;
LPBIND lpbind;
LPLISTEN lplisten;
LPCLOSESOCKET lpclosesocket;
LPSEND lpsend;
LPSHUTDOWN lpshutdown;
LPSOCKET lpsocket;
LPGETHOSTNAME lpgethostname;
LPGETHOSTBYNAME lpgethostbyname;
LPWSASTARTUP lpWSAStartup;
LPWSACLEANUP lpWSACleanup;
LPWSASETLASTERROR lpWSASetLastError;
LPWSAASYNCGETHOSTBYNAME lpWSAAsyncGetHostByName;
LPWSAASYNCGETHOSTBYADDR lpWSAAsyncGetHostByAddr;

HMODULE hWinSockDLL = NULL;

// converts winsock errorcode to string

LPSTR WSAGetLastErrorString( int error_arg )
{
   int error;

   if (error_arg != 0)
   {
      error = error_arg;
   }
   else
   {
      error = lpWSAGetLastError();
   }

   switch( error )
   {
   case WSAENAMETOOLONG :
      return "Name too long";

   case WSANOTINITIALISED :
      return "Not initialized";

   case WSASYSNOTREADY :
      return "System not ready";

   case WSAVERNOTSUPPORTED :
      return "Version is not supported";

   case WSAESHUTDOWN :
      return "Can't send after socket shutdown";

   case WSAEINTR :
      return "Interrupted system call";

   case WSAHOST_NOT_FOUND :
      return "Authoritative Answer: Host not found";

   case WSATRY_AGAIN :
      return "Non-Authoritative: Host not found, See NetworkStartup";

   case WSANO_RECOVERY :
      return "Non-recoverable error";

   case WSANO_DATA :
      return "No data record available";

   case WSAEBADF :
      return "Bad file number";

   case WSAEWOULDBLOCK :
      return "Operation would block";

   case WSAEINPROGRESS :
      return "Operation now in progress";

   case WSAEALREADY :
      return "Operation already in progress";

   case WSAEFAULT :
      return "Bad address";

   case WSAEDESTADDRREQ :
      return "Destination address required";

   case WSAEMSGSIZE :
      return "Message too long";

   case WSAEPFNOSUPPORT :
      return "Protocol family not supported";

   case WSAENOTEMPTY :
      return "Directory not empty";

   case WSAEPROCLIM :
      return "EPROCLIM returned";

   case WSAEUSERS :
      return "EUSERS returned";

   case WSAEDQUOT :
      return "Disk quota exceeded";

   case WSAESTALE :
      return "ESTALE returned";

   case WSAEINVAL :
      return "Invalid argument";

   case WSAEMFILE :
      return "Too many open files";

   case WSAEACCES :
      return "Access denied";

   case WSAELOOP :
      return "Too many levels of symbolic links";

   case WSAEREMOTE :
      return "The object is remote";

   case WSAENOTSOCK :
      return "Socket operation on non-socket";

   case WSAEADDRNOTAVAIL :
      return "Can't assign requested address";

   case WSAEADDRINUSE :
      return "Address already in use";

   case WSAEAFNOSUPPORT :
      return "Address family not supported by protocol family";

   case WSAESOCKTNOSUPPORT :
      return "Socket type not supported";

   case WSAEPROTONOSUPPORT :
      return "Protocol not supported";

   case WSAENOBUFS :
      return "No buffer space is supported";

   case WSAETIMEDOUT :
      return "Connection timed out";

   case WSAEISCONN :
      return "Socket is already connected";

   case WSAENOTCONN :
      return "Socket is not connected";

   case WSAENOPROTOOPT :
      return "Bad protocol option";

   case WSAECONNRESET :
      return "Connection reset by peer";

   case WSAECONNABORTED :
      return "Software caused connection abort";

   case WSAENETDOWN :
      return "Network is down";

   case WSAENETRESET :
      return "Network was reset";

   case WSAECONNREFUSED :
      return "Connection refused";

   case WSAEHOSTDOWN :
      return "Host is down";

   case WSAEHOSTUNREACH :
      return "Host is unreachable";

   case WSAEPROTOTYPE :
      return "Protocol is wrong type for socket";

   case WSAEOPNOTSUPP :
      return "Operation not supported on socket";

   case WSAENETUNREACH :
      return "ICMP network unreachable";

   case WSAETOOMANYREFS :
      return "Too many references";

   default :
      {
         static char Buffer[32];
         sprintf(Buffer,"Unknown %d",error);
         return Buffer;
      }
   }
}

// startup network

BOOL NetworkStartup()
{
   WSADATA WSAData;

   // check if already started

   if (hWinSockDLL != NULL)
   {
      return FALSE;
   }

   // load appropriate library

   hWinSockDLL = LoadLibrary((LPSTR) "WSOCK32.DLL");

   if (hWinSockDLL == NULL)
   {
      ::MessageBox(::GetFocus(), "Cannot load WSOCK32.DLL", "Network Error", MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL);
      return FALSE;
   }

   // fetch the routines

   lpaccept = (LPACCEPT) GetProcAddress(hWinSockDLL, (LPSTR) "accept");
   lpbind = (LPBIND) GetProcAddress(hWinSockDLL, (LPSTR) "bind");
   lpclosesocket = (LPCLOSESOCKET) GetProcAddress(hWinSockDLL, (LPSTR) "closesocket");
   lpconnect = (LPCONNECT) GetProcAddress(hWinSockDLL, (LPSTR) "connect");
   lphtons = (LPHTONS) GetProcAddress(hWinSockDLL, (LPSTR) "htons");
   lphtonl = (LPHTONL) GetProcAddress(hWinSockDLL, (LPSTR) "htonl");
   lpinet_addr = (LPINET_ADDR) GetProcAddress(hWinSockDLL, (LPSTR) "inet_addr");
   lpsetsockopt = (LPSETSOCKOPT) GetProcAddress(hWinSockDLL, (LPSTR) "setsockopt");
   lplisten = (LPLISTEN) GetProcAddress(hWinSockDLL, (LPSTR) "listen");
   lprecv = (LPRECV) GetProcAddress(hWinSockDLL, (LPSTR) "recv");
   lpsend = (LPSEND) GetProcAddress(hWinSockDLL, (LPSTR) "send");
   lpshutdown = (LPSHUTDOWN) GetProcAddress(hWinSockDLL, (LPSTR) "shutdown");
   lpsocket = (LPSOCKET) GetProcAddress(hWinSockDLL, (LPSTR) "socket");
   lpgethostname = (LPGETHOSTNAME) GetProcAddress(hWinSockDLL, (LPSTR) "gethostname");
   lpWSAStartup = (LPWSASTARTUP) GetProcAddress(hWinSockDLL, (LPSTR) "WSAStartup");
   lpWSACleanup = (LPWSACLEANUP) GetProcAddress(hWinSockDLL, (LPSTR) "WSACleanup");
   lpWSAGetLastError = (LPWSAGETLASTERROR) GetProcAddress(hWinSockDLL, (LPSTR) "WSAGetLastError");
   lpWSAAsyncGetHostByName = (LPWSAASYNCGETHOSTBYNAME) GetProcAddress(hWinSockDLL, (LPSTR) "WSAAsyncGetHostByName");
   lpWSAAsyncGetHostByAddr = (LPWSAASYNCGETHOSTBYADDR) GetProcAddress(hWinSockDLL, (LPSTR) "WSAAsyncGetHostByAddr");
   lpgethostbyname = (LPGETHOSTBYNAME) GetProcAddress(hWinSockDLL, (LPSTR) "gethostbyname");
   lpWSAAsyncSelect = (LPWSAASYNCSELECT) GetProcAddress(hWinSockDLL, (LPSTR) "WSAAsyncSelect");

   // tell winsock to wakeup

   if (lpWSAStartup(MAKEWORD(1,1), &WSAData) != 0)
   {
      ::MessageBox(::GetFocus(), WSAGetLastErrorString(0), "WSAStartup()", MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL);
      return FALSE;
   }

   return TRUE;
}

// put everything back to original state

void NetworkShutdown()
{

   // cleanup library

   if (hWinSockDLL != NULL)
   {
      lpWSACleanup();
      FreeLibrary(hWinSockDLL);
      hWinSockDLL = NULL;
   }

}
