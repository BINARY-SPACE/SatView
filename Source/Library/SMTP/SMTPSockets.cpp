/*
Module : SMTPSockets.cpp
Purpose: Implementation for an MFC wrapper class for sockets
Created: PJN / 05-08-1998
History: PJN / 03-03-2003 1. Now implements support for connecting via Socks 4 and Socks 5 proxies
         PJN / 21-09-2003 1. Now supports UDP sockets.
                          2. Now supports UDP relaying via Socks 5 proxy.
         PJN / 26-09-2003 1. Now supports connection via HTTP proxies which support the CONNECT verb
         PJN / 13-01-2004 1. Used newer form of #pragma pack to avoid problems with non standard 
                          packing sizes.
         PJN / 25-10-2004 1. Updated to compile cleanly when Detect 64 bit issues and Force conformance 
                          in for loop options are enabled in Visual Studio .NET
         PJN / 29-12-2004 Almost all of the following updates were to match the functionality provided
                          by the MFC CAsyncSocket class but without the overhead of hidden windows and 
                          its async behaviour.
                          1. Now automatically links to Winsock via #pragma comment
                          2. Addition of a GetPeerName method.
                          3. Replaced all calls to ZeroMemory to memset.
                          4. Addtion of a GetSockName method.
                          5. Addition of a SetSockOpt method.
                          6. Addition of a Flags parameter to Receive method.
                          7. Addition of a IOCtl method.
                          8. Optimized the code in Listen.
                          9. Addition of a ReceiveFrom method.
                          10. Addition of a ShutDown method.
                          11. Optimized the code in Close.
                          12. Remove of pszLocalBoundAddress parameter from Connect methods to make it 
                          consistent with CAsyncSocket.
                          13. Addition of a Flags parameter to Send method.
                          14. Optimized code in CWSocket destructor
                          15. Addition of an overloaded Create method which allows all of the socket
                          parameters to be set
                          16. Use of _tcslen has been minimized when NULL string parameters can be passed
                          to various CWSocket methods.
                          17. Change of various parameter names to be consistent with names as used in
                          CAsyncSocket.
         PJN / 31-01-2005 1. Fixed a bug in CWSocket::Receive where it throws an error when a graceful 
                          disconnect occurs. Now the code only throws an exception if the return value
                          from recv is SOCKET_ERROR
         PJN / 01-05-2005 1. Send method now uses a const void* parameter.
         PJN / 21-06-2005 1. Provision of connect methods which allows a timeout to be specified. Please note
                          that if you use a host name in these calls as opposed to an IP address, the DNS
                          lookup is still done using the OS supplied timeout. Only the actual connection
                          to the server is implemented using a timeout after the DNS lookup is done (if it
                          is necessary).
         PJN / 04-11-2005 1. Send method now returns the number of bytes written. Thanks to Owen O'Flaherty
                          for pointing out this omission.
         PJN / 19-02-2006 1. Replaced all calls to ZeroMemory and CopyMemory with memset and memcpy
         PJN / 27-06-2006 1. Updated copyright details.
                          2. Made ThrowWSocketException part of CWSocket class and renamed to 
                          ThrowWSocketException.
                          3. CWSocketException::GetErrorMessage now uses safestring functionality.
                          4. Optimized CWSocketException constructor code.
                          5. Removed unnecessary CWSocketException destructor
                          6. Code now uses new C++ style casts rather than old style C casts where necessary. 
         PJN / 19-11-2007 1. Updated copyright details.
         PJN / 26-12-2007 1. CWSocketException::GetErrorMessage now uses the FORMAT_MESSAGE_IGNORE_INSERTS flag. 
                          For more information please see Raymond Chen's blog at 
                          http://blogs.msdn.com/oldnewthing/archive/2007/11/28/6564257.aspx. Thanks to Alexey 
                          Kuznetsov for reporting this issue.
                          2. All username and password temp strings are now securely destroyed using 
                          SecureZeroMemory. This version of the code and onwards will be supported only
                          on VC 2005 or later.
         PJN / 27-12-2007 1. CWSocketException::GetErrorMessage now uses Checked::tcsncpy_s similiar to the 
                          built in MFC exception classes
         PJN / 31-12-2007 1. Minor coding updates to CWSocketException::GetErrorMessage
         PJN / 02-02-2008 1. Updated copyright details.
                          2. Fixed potential heap memory leaks in CWSocket::ReadHTTPProxyResponse.Thanks to 
                          Michal Urbanczyk for reporting this bug.
                          3. Fixed a memory leak in CWSocket::ConnectViaSocks5
                          4. Restructured CWSocket::ReadSocks5ConnectReply to avoid the need to allocate 
                          heap memory
         PJN / 01-03-2008 1. Since the code is now for VC 2005 or later only, the code now uses the Base64 
                          encoding support from the ATL atlenc.h header file. Thanks to Mat Berchtold for 
                          reporting this optimization. This means that client projects no longer need to include 
                          Base64.cpp/h in their projects.
         PJN / 31-05-2008 1. Code now compiles cleanly using Code Analysis (/analyze)
                          2. Tidied up the CWSocket::ReadHTTPProxyResponse implementation
         PJN / 23-05-2009 1. Removed use of CT2A throughout the code
         PJN / 09-01-2011 1. Updated copyright details.
                          2. Updated Create method which takes a BOOL to include another default parameter to 
                          indicate IPv6
                          3. Updated CWSocket::GetPeerName to operate for IPv6 as well as IPv4
                          4. All Connect methods now try to connect all addresses returned from address lookups
                          5. Addition of a CreateAndBind method which support IPv6 binding
                          6. ReceiveFrom(void* pBuf, int nBufLen, CString& sSocketAddress, UINT& nSocketPort, int nFlags)
                          method has been updated to support IPv6.
                          7. SendTo(const void* pBuf, int nBufLen, UINT nHostPort, LPCTSTR pszHostAddress, int nFlags) 
                          method has been updated to support IPv6 as well as connecting to all addresses returned from
                          address lookups.
                          8. Removed all _alloca calls
                          9. Addition of a number of CreateConnect methods which support IPv6
         PJN / 08-02-2011 1. The state of whether a socket should be bound or not is now decided by a new m_sBindAddress 
                          member variable. This variable can be modified through new Get/SetBindAddress methods.
                          2. Fixed a number of compile problems in VC 2005 related to ATL::CSocketAddr::GetAddrInfoList()
                          return value.
         PJN / 03-04-2011 1. Fix for a bug in CreateAndConnect where the wrong family socket type was being passed to
                          Create.
         PJN / 11-08-2012 1. Updated copyright details.
                          2. Updated the code to compile cleanly on VC 2012
         PJN / 16-03-2014 1. Updated copyright details
                          2. Reworked Shutdown to use standard SDK defines rather than enums in the class
                          3. Removed all the proxy connection methods as they cannot be easily supported / tested by the author.
                          4. Reworked the CWSocket and CWSocketException classes to optionally compile without MFC. By default 
                          the classes now use STL classes and idioms but if you define SOCKET_MFC_EXTENSTIONS the classes will 
                          revert back to the MFC behaviour.
                          5. Reworked CWSocket::ReceiveFrom to use GetNameInfoW / getnameinfo.
                          6. Reworked CWSocket::AddressToString to use GetNameInfoW / getnameinfo.
                          7. CWSocket::AddressToString now also returns the port number
                          8. Provided an overloaded version of AddressToString which takes a SOCKADDR& parameter
                          9. AddressToString method now takes a nFlags parameter
                          10. The CreateAndConnect method has been enhanced to include nFamily and nProtocolType parameters. 
                          This allows client code for example to explicitly connect to IPv4 or IPv6 addresses.
         PJN / 26-11-2014 1. Removed CWSocket methods which were deprecated in previous versions of the code.
                          2. Updated the class to clean compile on VC 2013 Update 3 and higher
         PJN / 28-10-2015 1. Updated the code to clean compile on VC 2015
                          2. Updated copyright details.
                          3. CWSocket::GetPeerName & CWSocket::GetSockName now have an extra default parameter called 
                          "nAddressToStringFlags" which is passed to the AddressToString method.
                          4. CWSocket::ReceiveFrom now has extra default parameter called "nAddressToStringFlags" which is 
                          passed to the AddressToString method.

Copyright (c) 2002 - 2015 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


//////////////// Includes /////////////////////////////////////////////////////

#include "..\SatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////// Implementation ///////////////////////////////////////////////

class _SOCMFC_DATA
{
public:
//Constructors /Destructors
  _SOCMFC_DATA();

//Typedefs
  typedef INT (WSAAPI GETNAMEINFOW)(const SOCKADDR*, socklen_t, PWCHAR, DWORD, PWCHAR, DWORD, INT);

//Member variables
  GETNAMEINFOW* m_pfnGetNameInfoW;
};

_SOCMFC_DATA::_SOCMFC_DATA() : m_pfnGetNameInfoW(NULL)
{
  //Get the function pointer
  HMODULE hWs32DLL = GetModuleHandle(_T("Ws2_32.dll"));
  if (hWs32DLL != NULL)
    m_pfnGetNameInfoW = reinterpret_cast<GETNAMEINFOW*>(GetProcAddress(hWs32DLL, "GetNameInfoW"));
}

//the one and only _SOCMFC_DATA
_SOCMFC_DATA _SocMFCData;

#if _MSC_VER >= 1700
BOOL CWSocketException::GetErrorMessage(_Out_z_cap_(nMaxError) LPTSTR lpszError, _In_ UINT nMaxError,	_Out_opt_ PUINT pnHelpContext)
#else	
BOOL CWSocketException::GetErrorMessage(__out_ecount_z(nMaxError) LPTSTR lpszError, __in UINT nMaxError, __out_opt PUINT pnHelpContext)
#endif //#if _MSC_VER >= 1700
{
  //Validate our parameters
  ATLASSERT(lpszError != NULL);

  if (pnHelpContext != NULL)
    *pnHelpContext = 0;

  //What will be the return value from this function (assume the worst)
  BOOL bSuccess = FALSE;

  LPTSTR lpBuffer;
  DWORD dwReturn = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL,  m_nError, MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT),
                                 reinterpret_cast<LPTSTR>(&lpBuffer), 0, NULL);
  if (dwReturn == 0)
    *lpszError = _T('\0');
  else
  {
    bSuccess = TRUE;
    Checked::tcsncpy_s(lpszError, nMaxError, lpBuffer, _TRUNCATE);
    LocalFree(lpBuffer);
  }

  return bSuccess;
}

#ifdef SOCKET_MFC_EXTENSTIONS
CString CWSocketException::GetErrorMessage()
{
  CString rVal;
  LPTSTR pstrError = rVal.GetBuffer(4096);
  GetErrorMessage(pstrError, 4096, NULL);
  rVal.ReleaseBuffer();
  return rVal;
}
#endif //#ifdef SOCKET_MFC_EXTENSTIONS

CWSocketException::CWSocketException(int nError) : m_nError(nError)
{
}

#ifdef SOCKET_MFC_EXTENSTIONS
#ifdef _DEBUG
void CWSocketException::Dump(CDumpContext& dc) const
{
  CObject::Dump(dc);

  dc << _T("m_nError = ") << m_nError << _T("\n");
}
#endif //#ifdef _DEBUG
#endif //#ifdef SOCKET_MFC_EXTENSTIONS


CWSocket::CWSocket() : m_hSocket(INVALID_SOCKET)
{
}

CWSocket::~CWSocket()
{
  if (m_hSocket != INVALID_SOCKET)
    Close();
}

void CWSocket::ThrowWSocketException(int nError)
{
  if (nError == 0)
    nError = ::WSAGetLastError();

  ATLTRACE(_T("Warning: throwing CWSocketException for error %d\n"), nError);
#ifdef SOCKET_MFC_EXTENSTIONS
  CWSocketException* pException = new CWSocketException(nError);
  THROW(pException);
#else
  CWSocketException e(nError);
  throw e;
#endif //#ifdef SOCKET_MFC_EXTENSTIONS
}

void CWSocket::Attach(SOCKET hSocket)
{
  //Validate our parameters
  ATLASSERT(hSocket != INVALID_SOCKET);

  if (m_hSocket != INVALID_SOCKET)
    Close();

  m_hSocket = hSocket;
}

SOCKET CWSocket::Detach()
{
  SOCKET socket = m_hSocket;
  m_hSocket = INVALID_SOCKET;
  return socket;
}

void CWSocket::GetPeerName(String& sPeerAddress, UINT& nPeerPort, int nAddressToStringFlags)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  SOCKADDR_STORAGE sockAddr;
  memset(&sockAddr, 0, sizeof(sockAddr));
  int nSockAddrLen = sizeof(sockAddr);
  GetPeerName(reinterpret_cast<SOCKADDR*>(&sockAddr), &nSockAddrLen);

  sPeerAddress = AddressToString(reinterpret_cast<const SOCKADDR*>(&sockAddr), sizeof(sockAddr), nAddressToStringFlags, &nPeerPort);
}

void CWSocket::GetSockName(String& sSocketAddress, UINT& nSocketPort, int nAddressToStringFlags)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  SOCKADDR_STORAGE sockAddr;
  memset(&sockAddr, 0, sizeof(sockAddr));
  int nSockAddrLen = sizeof(sockAddr);
  GetSockName(reinterpret_cast<SOCKADDR*>(&sockAddr), &nSockAddrLen);

  sSocketAddress = AddressToString(reinterpret_cast<const SOCKADDR*>(&sockAddr), sizeof(sockAddr), nAddressToStringFlags, &nSocketPort);
}

void CWSocket::GetPeerName(SOCKADDR* pSockAddr, int* pSockAddrLen)
{ 
  //Validate our parameters
  ATLASSERT(IsCreated()); //Must have been created first

  if (getpeername(m_hSocket, pSockAddr, pSockAddrLen) == SOCKET_ERROR)
    ThrowWSocketException();
}

void CWSocket::GetSockName(SOCKADDR* pSockAddr, int* pSockAddrLen)
{ 
  //Validate our parameters
  ATLASSERT(IsCreated()); //Must have been created first

  if (getsockname(m_hSocket, pSockAddr, pSockAddrLen) == SOCKET_ERROR)
    ThrowWSocketException();
}

void CWSocket::Accept(CWSocket& connectedSocket, SOCKADDR* pSockAddr, int* pSockAddrLen)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first
  ATLASSERT(!connectedSocket.IsCreated()); //Must be an unitialized socket

  //Call the SDK accept function  
  SOCKET socket = accept(m_hSocket, pSockAddr, pSockAddrLen);
  if (socket == INVALID_SOCKET)
    ThrowWSocketException(); 

  //Wrap the return value up into a C++ instance
  connectedSocket.Attach(socket);
}

void CWSocket::SetSockOpt(int nOptionName, const void* pOptionValue, int nOptionLen, int nLevel)
{ 
  //Validate our parameters
  ATLASSERT(IsCreated()); //Must have been created first

  if (setsockopt(m_hSocket, nLevel, nOptionName, static_cast<LPCSTR>(pOptionValue), nOptionLen) == SOCKET_ERROR)
    ThrowWSocketException();
}

void CWSocket::GetSockOpt(int nOptionName, void* pOptionValue, int* pOptionLen, int nLevel)
{ 
  //Validate our parameters
  ATLASSERT(IsCreated()); //Must have been created first

  if (getsockopt(m_hSocket, nLevel, nOptionName, static_cast<LPSTR>(pOptionValue), pOptionLen) == SOCKET_ERROR)
    ThrowWSocketException();
}

void CWSocket::Bind(const SOCKADDR* pSockAddr, int nSockAddrLen)
{ 
  //Validate our parameters
  ATLASSERT(IsCreated()); //Must have been created first

  if (bind(m_hSocket, pSockAddr, nSockAddrLen) == SOCKET_ERROR)
    ThrowWSocketException();
}

void CWSocket::CreateAndBind(UINT nSocketPort, int nSocketType, int nDefaultAddressFormat)
{
  //Validate our parameters
  ATLASSERT(!IsCreated()); //must not be created for a v6 style connect

  //Do we need to bind to a specific IP address?
#ifdef SOCKET_MFC_EXTENSTIONS
  if (m_sBindAddress.GetLength())
#else
  if (m_sBindAddress.length())
#endif //#ifdef SOCKET_MFC_EXTENSTIONS
  {
    TCHAR szPort[32];
    szPort[0] = _T('\0');
    _stprintf_s(szPort, sizeof(szPort)/sizeof(TCHAR), _T("%u"), nSocketPort);

    //Do the address lookup
    ATL::CSocketAddr lookup;
  #ifdef SOCKET_MFC_EXTENSTIONS
    int nError = lookup.FindAddr(m_sBindAddress, szPort, AI_PASSIVE, 0, 0, 0);
  #else
    int nError = lookup.FindAddr(m_sBindAddress.c_str(), szPort, AI_PASSIVE, 0, 0, 0);
  #endif //#ifdef SOCKET_MFC_EXTENSTIONS
    if (nError != 0)
      ThrowWSocketException(nError);

    ADDRINFOT* const pAddress = lookup.GetAddrInfoList();
    ATLASSUME(pAddress != NULL);

    //Create the socket
    Create(nSocketType, 0, pAddress->ai_family);

    //Finally bind the socket
    Bind(pAddress->ai_addr, static_cast<int>(pAddress->ai_addrlen));
  }
  else
  {
    switch (nDefaultAddressFormat)
    {
      case AF_INET6:
      {
        //Setup the structure used in sdk "bind" calls
        SOCKADDR_IN6 sockAddr;
        memset(&sockAddr, 0, sizeof(sockAddr));
        sockAddr.sin6_family = AF_INET6;
        sockAddr.sin6_port = htons(static_cast<USHORT>(nSocketPort));
        sockAddr.sin6_addr = in6addr_any; //Bind to any IP address;

        //Create the socket
        Create(nSocketType, 0, nDefaultAddressFormat);

        //Finally bind the socket
        Bind(reinterpret_cast<SOCKADDR*>(&sockAddr), sizeof(sockAddr));
        break;
      }
      case AF_INET:
      {

        //Setup the structure used in sdk "bind" calls
        SOCKADDR_IN sockAddr;
        memset(&sockAddr, 0, sizeof(sockAddr));
        sockAddr.sin_family = AF_INET;
        sockAddr.sin_port = htons(static_cast<USHORT>(nSocketPort));
        sockAddr.sin_addr = in4addr_any; //Bind to any IP address;

        //Create the socket
        Create(nSocketType, 0, nDefaultAddressFormat);

        //Finally bind the socket
        Bind(reinterpret_cast<SOCKADDR*>(&sockAddr), sizeof(sockAddr));
        break;
      }
      default:
      {
        ATLASSERT(FALSE);
        break;
      }
    }
  }
}

void CWSocket::Close()
{
  if (m_hSocket != INVALID_SOCKET)
  {
    closesocket(m_hSocket);
    m_hSocket = INVALID_SOCKET;
  }
}

void CWSocket::Connect(const SOCKADDR* pSockAddr, int nSockAddrLen)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  if (connect(m_hSocket, pSockAddr, nSockAddrLen) == SOCKET_ERROR)
    ThrowWSocketException();
}

void CWSocket::_Connect(LPCTSTR pszHostAddress, LPCTSTR pszPortOrServiceName)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first
  ATLASSUME(pszHostAddress != NULL); //must have a valid host

  //Do the address lookup
  ATL::CSocketAddr lookup;
  int nError = lookup.FindAddr(pszHostAddress, pszPortOrServiceName, 0, 0, 0, 0);
  if (nError != 0)
    ThrowWSocketException(nError);

  //Iterate through the list of addresses trying to connect
  BOOL bSuccess = FALSE;
  int nLastError = 0;
  ADDRINFOT* const pAddress = lookup.GetAddrInfoList();
  ADDRINFOT* pCurrentAddress = pAddress;
  while ((pCurrentAddress != NULL) && !bSuccess) 
  {
    try
    {
      //Call the other version of Connect which does the actual work
      Connect(pCurrentAddress->ai_addr, static_cast<int>(pCurrentAddress->ai_addrlen));
      bSuccess = TRUE;
    }
  #ifdef SOCKET_MFC_EXTENSTIONS
    catch(CWSocketException* pEx)
    {
      //Prepare for the next time around
      nLastError = pEx->m_nError;
      pEx->Delete();
      pCurrentAddress = pCurrentAddress->ai_next;
    }
  #else
    catch(CWSocketException& e)
    {
      //Prepare for the next time around
      nLastError = e.m_nError;
      pCurrentAddress = pCurrentAddress->ai_next;
    }
  #endif //#ifdef SOCKET_MFC_EXTENSTIONS
  }
  if (!bSuccess)
    ThrowWSocketException(nLastError);
}

void CWSocket::CreateAndConnect(LPCTSTR pszHostAddress, UINT nHostPort, int nSocketType, int nFamily, int nProtocolType)
{
  TCHAR szHostPort[32];
  szHostPort[0] = _T('\0');
  _stprintf_s(szHostPort, sizeof(szHostPort)/sizeof(TCHAR), _T("%u"), nHostPort);
  CreateAndConnect(pszHostAddress, szHostPort, nSocketType, nFamily, nProtocolType);
}

void CWSocket::_Bind(LPCTSTR pszPortOrServiceName)
{
  //Do we need to bind to a specific IP address?
#ifdef SOCKET_MFC_EXTENSTIONS
  if (m_sBindAddress.GetLength())
#else
  if (m_sBindAddress.length())
#endif //#ifdef SOCKET_MFC_EXTENSTIONS
  {
    //Do the address lookup
    ATL::CSocketAddr lookup;
  #ifdef SOCKET_MFC_EXTENSTIONS
    int nError = lookup.FindAddr(m_sBindAddress, pszPortOrServiceName, AI_PASSIVE, 0, 0, 0);
  #else
    int nError = lookup.FindAddr(m_sBindAddress.c_str(), pszPortOrServiceName, AI_PASSIVE, 0, 0, 0);
  #endif //#ifdef SOCKET_MFC_EXTENSTIONS
    if (nError != 0)
      ThrowWSocketException(nError);

    ADDRINFOT* const pBindAddress = lookup.GetAddrInfoList();
    ATLASSUME(pBindAddress != NULL);

    //Finally bind the socket
    Bind(pBindAddress->ai_addr, static_cast<int>(pBindAddress->ai_addrlen));
  }
}

void CWSocket::CreateAndConnect(LPCTSTR pszHostAddress, LPCTSTR pszPortOrServiceName, int nSocketType, int nFamily, int nProtocolType)
{
  //Validate our parameters
  ATLASSERT(!IsCreated()); //must not be created for a v6 style connect
  ATLASSUME(pszHostAddress != NULL); //must have a valid host

  //Do the address lookup
  ATL::CSocketAddr lookup;
  int nError = lookup.FindAddr(pszHostAddress, pszPortOrServiceName, 0, nFamily, nSocketType, nProtocolType);
  if (nError != 0)
    ThrowWSocketException(nError);

  //Iterate through the list of addresses trying to connect
  BOOL bSuccess = FALSE;
  int nLastError = 0;
  ADDRINFOT* const pAddress = lookup.GetAddrInfoList();
  ADDRINFOT* pCurrentAddress = pAddress;
  while ((pCurrentAddress != NULL) && !bSuccess) 
  {
    try
    {
      //Create the socket now that we know the family type via the lookup
      Close();
      Create(nSocketType, pCurrentAddress->ai_protocol, pCurrentAddress->ai_family);
      _Bind(pszPortOrServiceName);      

      //Call the other version of Connect which does the actual work
      Connect(pCurrentAddress->ai_addr, static_cast<int>(pCurrentAddress->ai_addrlen));
      bSuccess = TRUE;
    }
  #ifdef SOCKET_MFC_EXTENSTIONS
    catch(CWSocketException* pEx)
    {
      //Prepare for the next time around
      nLastError = pEx->m_nError;
      pEx->Delete();
      pCurrentAddress = pCurrentAddress->ai_next;
    }
  #else
    catch(CWSocketException& e)
    {
      //Prepare for the next time around
      nLastError = e.m_nError;
      pCurrentAddress = pCurrentAddress->ai_next;
    }
  #endif //#ifdef SOCKET_MFC_EXTENSTIONS
  }
  if (!bSuccess)
    ThrowWSocketException(nLastError);
}

void CWSocket::Connect(const SOCKADDR* pSockAddr, int nSockAddrLen, DWORD dwTimeout, BOOL bResetToBlockingMode)
{
  //Create an event to wait on
  WSAEVENT hConnectedEvent = WSACreateEvent();
  if (hConnectedEvent == WSA_INVALID_EVENT)
    ThrowWSocketException();
  ATLASSUME(hConnectedEvent != NULL);

  //Setup event selection on the socket
  if (WSAEventSelect(m_hSocket, hConnectedEvent, FD_CONNECT) == SOCKET_ERROR)
  {
    //Hive away the last error
    DWORD dwLastError = GetLastError();

    //Close the event before we return
    WSACloseEvent(hConnectedEvent);

    //Throw the exception that we could not setup event selection
    ThrowWSocketException(dwLastError);
  }

  //Call the SDK "connect" function
  int nConnected = connect(m_hSocket, pSockAddr, nSockAddrLen);
  if (nConnected == SOCKET_ERROR)
  {
    //Check to see if the call should be completed by waiting for the event to be signalled
    DWORD dwLastError = GetLastError();
    if (dwLastError == WSAEWOULDBLOCK)
    {
      DWORD dwWait = WaitForSingleObject(hConnectedEvent, dwTimeout);
      if (dwWait == WAIT_OBJECT_0)
      {
        //Get the error value returned using WSAEnumNetworkEvents
        WSANETWORKEVENTS networkEvents;
        int nEvents = WSAEnumNetworkEvents(m_hSocket, hConnectedEvent, &networkEvents);
        if (nEvents == SOCKET_ERROR)
        {
          //Hive away the last error
          dwLastError = GetLastError();

          //Close the event before we return
          WSACloseEvent(hConnectedEvent);

          //Throw the exception that we could not call WSAEnumNetworkEvents
          ThrowWSocketException(dwLastError);
        }
        else
        {
          ATLASSERT(networkEvents.lNetworkEvents & FD_CONNECT);

          //Has an error occured in the connect call
          if (networkEvents.iErrorCode[FD_CONNECT_BIT] != ERROR_SUCCESS)
          {
            //Close the event before we return
            WSACloseEvent(hConnectedEvent);

            //Throw the exception that an error has occurred in calling connect
            ThrowWSocketException(networkEvents.iErrorCode[FD_CONNECT_BIT]);
          }
        }
      }
      else
      {
        //Close the event before we return
        WSACloseEvent(hConnectedEvent);

        //Throw the exception that we could not connect in a timely fashion
        ThrowWSocketException(WSAETIMEDOUT);
      }
    }
    else
    {
      //Close the event before we return
      WSACloseEvent(hConnectedEvent);

      //Throw the exception that the connect call failed unexpectedly
      ThrowWSocketException(dwLastError);
    }
  }

  //Remove the event notification on the socket
  WSAEventSelect(m_hSocket, hConnectedEvent, 0);

  //Destroy the event now that we are finished with it
  WSACloseEvent(hConnectedEvent);

  //Reset the socket to blocking mode if required
  if (bResetToBlockingMode)
  {
    DWORD dwNonBlocking = 0;
    if (ioctlsocket(m_hSocket, FIONBIO, &dwNonBlocking) == SOCKET_ERROR)
    {
      //Throw the exception that we could not reset the socket to blocking mode
      ThrowWSocketException();
    }
  }    
}

void CWSocket::CreateAndConnect(LPCTSTR pszHostAddress, LPCTSTR pszPortOrServiceName, DWORD dwTimeout, BOOL bResetToBlockingMode, int nSocketType)
{
  //Validate our parameters
  ATLASSERT(!IsCreated()); //must not be created for a v6 style connect
  ATLASSUME(pszHostAddress != NULL); //must have a valid host

  //Do the address lookup
  ATL::CSocketAddr lookup;
  int nError = lookup.FindAddr(pszHostAddress, pszPortOrServiceName, 0, 0, 0, 0);
  if (nError != 0)
    ThrowWSocketException(nError);

  BOOL bSuccess = FALSE;
  int nLastError = 0;
  ADDRINFOT* const pAddress = lookup.GetAddrInfoList();
  ADDRINFOT* pCurrentAddress = pAddress;
  while ((pCurrentAddress != NULL) && !bSuccess) 
  {
    try
    {
      //Create the socket now that we now the family type
      Close();
      Create(nSocketType, 0, pCurrentAddress->ai_family);
      _Bind(pszPortOrServiceName);

      //Call the other version of Connect which does the actual work
      Connect(pCurrentAddress->ai_addr, static_cast<int>(pCurrentAddress->ai_addrlen), dwTimeout, bResetToBlockingMode);
      bSuccess = TRUE;
    }
  #ifdef SOCKET_MFC_EXTENSTIONS
    catch(CWSocketException* pEx)
    {
      //Prepare for the next time around
      nLastError = pEx->m_nError;
      pEx->Delete();
      pCurrentAddress = pCurrentAddress->ai_next;
    }
  #else
    catch(CWSocketException& e)
    {
      //Prepare for the next time around
      nLastError = e.m_nError;
      pCurrentAddress = pCurrentAddress->ai_next;
    }
  #endif //#ifdef SOCKET_MFC_EXTENSTIONS
  }
  if (!bSuccess)
    ThrowWSocketException(nLastError);
}

void CWSocket::CreateAndConnect(LPCTSTR pszHostAddress, UINT nHostPort, DWORD dwTimeout, BOOL bResetToBlockingMode, int nSocketType)
{
  TCHAR szHostPort[32];
  szHostPort[0] = _T('\0');
  _stprintf_s(szHostPort, sizeof(szHostPort)/sizeof(TCHAR), _T("%u"), nHostPort);
  CreateAndConnect(pszHostAddress, szHostPort, dwTimeout, bResetToBlockingMode, nSocketType);
}

int CWSocket::Receive(void* pBuf, int nBufLen, int nFlags)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  int nReceived = recv(m_hSocket, static_cast<LPSTR>(pBuf), nBufLen, nFlags); 
  if (nReceived == SOCKET_ERROR)
    ThrowWSocketException();

  return nReceived;
}

int CWSocket::ReceiveFrom(void* pBuf, int nBufLen, SOCKADDR* pSockAddr, int* pSockAddrLen, int nFlags)
{ 
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  int nReceived = recvfrom(m_hSocket, static_cast<LPSTR>(pBuf), nBufLen, nFlags, pSockAddr, pSockAddrLen);
  if (nReceived == SOCKET_ERROR)
    ThrowWSocketException();

  return nReceived;
}

CWSocket::String CWSocket::AddressToString(const SOCKADDR* pSockAddr, int nSockAddrLen, int nFlags, UINT* pnSocketPort)
{
  //What will be the return value from this function
  String sSocketAddress;

#ifdef _UNICODE
  if (_SocMFCData.m_pfnGetNameInfoW == NULL)
    ThrowWSocketException(ERROR_CALL_NOT_IMPLEMENTED);
  ATLASSUME(_SocMFCData.m_pfnGetNameInfoW != NULL);
  wchar_t szName[NI_MAXHOST];
  szName[0] = L'\0';
  int nResult = _SocMFCData.m_pfnGetNameInfoW(pSockAddr, nSockAddrLen, szName, NI_MAXHOST, NULL, 0, nFlags);
#else
  char szName[NI_MAXHOST];
  szName[0] = '\0';
  int nResult = getnameinfo(pSockAddr, nSockAddrLen, szName, NI_MAXHOST, NULL, 0, nFlags);
#endif
  if (nResult == 0)
  {
    sSocketAddress = szName;
    if (pnSocketPort != NULL)
      *pnSocketPort = ntohs(SS_PORT(&pSockAddr));
  }
  else
    ThrowWSocketException();

  return sSocketAddress;
}

CWSocket::String CWSocket::AddressToString(const SOCKADDR_INET& sockAddr, int nFlags, UINT* pnSocketPort)
{
  //What will be the return value from this function
  String sSocketAddress;

  if (sockAddr.si_family == AF_INET)
    sSocketAddress = AddressToString(reinterpret_cast<const SOCKADDR*>(&sockAddr.Ipv4), sizeof(sockAddr.Ipv4), nFlags, pnSocketPort);
  else if (sockAddr.si_family == AF_INET6)
    sSocketAddress = AddressToString(reinterpret_cast<const SOCKADDR*>(&sockAddr.Ipv6), sizeof(sockAddr.Ipv6), nFlags, pnSocketPort);
  else
    ThrowWSocketException(WSAEAFNOSUPPORT);

  return sSocketAddress;
}

int CWSocket::ReceiveFrom(void* pBuf, int nBufLen, String& sSocketAddress, UINT& nSocketPort, int nReceiveFromFlags, int nAddressToStringFlags)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  SOCKADDR_STORAGE sockAddr;
  memset(&sockAddr, 0, sizeof(sockAddr));
  int nSockAddrLen = sizeof(sockAddr);
  int nResult = ReceiveFrom(pBuf, nBufLen, reinterpret_cast<SOCKADDR*>(&sockAddr), &nSockAddrLen, nReceiveFromFlags);
  if (nResult == SOCKET_ERROR)
    ThrowWSocketException();

  sSocketAddress = AddressToString(reinterpret_cast<const SOCKADDR*>(&sockAddr), sizeof(sockAddr), nAddressToStringFlags, &nSocketPort);
  return nResult;
}

int CWSocket::Send(const void* pBuffer, int nBufLen, int nFlags)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  int nSent = send(m_hSocket, static_cast<const char*>(pBuffer), nBufLen, nFlags);
  if (nSent == SOCKET_ERROR)
    ThrowWSocketException();

  return nSent;
}

int CWSocket::SendTo(const void* pBuf, int nBufLen, const SOCKADDR* pSockAddr, int nSockAddrLen, int nFlags)
{ 
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  int nSent = sendto(m_hSocket, static_cast<const char*>(pBuf), nBufLen, nFlags, pSockAddr, nSockAddrLen);
  if (nSent == SOCKET_ERROR)
    ThrowWSocketException();

  return nSent; 
}

int CWSocket::SendTo(const void* pBuf, int nBufLen, UINT nHostPort, LPCTSTR pszHostAddress, int nFlags)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  //Do the address lookup
  ATL::CSocketAddr lookup;
  TCHAR szPort[32];
  szPort[0] = _T('\0');
  _stprintf_s(szPort, sizeof(szPort)/sizeof(TCHAR), _T("%u"), nHostPort);
  int nError = lookup.FindAddr(pszHostAddress, szPort, 0, 0, 0, 0);
  if (nError != 0)
    ThrowWSocketException(nError);

  //Iterate through the list of addresses trying to send to
  BOOL bSuccess = FALSE;
  int nLastError = 0;
  ADDRINFOT* const pAddress = lookup.GetAddrInfoList();
  ADDRINFOT* pCurrentAddress = pAddress;
  int nSent = 0;
  while ((pCurrentAddress != NULL) && !bSuccess) 
  {
    try
    {
      //Call the other version of send to which does the actual work
      nSent = SendTo(pBuf, nBufLen, pCurrentAddress->ai_addr, static_cast<int>(pCurrentAddress->ai_addrlen), nFlags);
      bSuccess = TRUE;
    }
  #ifdef SOCKET_MFC_EXTENSTIONS
    catch(CWSocketException* pEx)
    {
      //Prepare for the next time around
      nLastError = pEx->m_nError;
      pEx->Delete();
      pCurrentAddress = pCurrentAddress->ai_next;
    }
  #else
    catch(CWSocketException& e)
    {
      //Prepare for the next time around
      nLastError = e.m_nError;
      pCurrentAddress = pCurrentAddress->ai_next;
    }
  #endif //#ifdef SOCKET_MFC_EXTENSTIONS
  }
  if (!bSuccess)
    ThrowWSocketException(nLastError);

  return nSent;
}

void CWSocket::IOCtl(long lCommand, DWORD* pArgument)
{ 
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  if (ioctlsocket(m_hSocket, lCommand, pArgument) == SOCKET_ERROR)
    ThrowWSocketException();
}

void CWSocket::Listen(int nConnectionBacklog)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  if (listen(m_hSocket, nConnectionBacklog) == SOCKET_ERROR)
    ThrowWSocketException();
}

void CWSocket::ShutDown(int nHow)
{ 
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  if (shutdown(m_hSocket, nHow) == SOCKET_ERROR)
    ThrowWSocketException();
}

void CWSocket::Create(BOOL bUDP, BOOL bIPv6)
{
  //Validate our parameters
  ATLASSERT(!IsCreated()); //must not have been already created

  Create(bUDP ? SOCK_DGRAM : SOCK_STREAM, 0, bIPv6 ? AF_INET6 : PF_INET);
}

void CWSocket::Create(int nSocketType, int nProtocolType, int nAddressFormat)
{
  //Validate our parameters
  ATLASSERT(!IsCreated()); //must not have been already created

  m_hSocket = socket(nAddressFormat, nSocketType, nProtocolType);
  if (m_hSocket == INVALID_SOCKET)
    ThrowWSocketException();
}

BOOL CWSocket::IsReadible(DWORD dwTimeout)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  timeval timeout;
  timeout.tv_sec = dwTimeout/1000;
  timeout.tv_usec = (dwTimeout%1000)*1000;
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(m_hSocket, &fds);
  int nStatus = select(0, &fds, NULL, NULL, &timeout);
  if (nStatus == SOCKET_ERROR)
    ThrowWSocketException();

  return !(nStatus == 0);
}

BOOL CWSocket::IsWritable(DWORD dwTimeout)
{
  //Validate our parameters
  ATLASSERT(IsCreated()); //must have been created first

  timeval timeout;
  timeout.tv_sec = dwTimeout/1000;
  timeout.tv_usec = (dwTimeout%1000)*1000;
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(m_hSocket, &fds);
  int nStatus = select(0, NULL, &fds, NULL, &timeout);
  if (nStatus == SOCKET_ERROR)
    ThrowWSocketException();

  return !(nStatus == 0);
}

BOOL CWSocket::IsCreated() const
{
  return (m_hSocket != INVALID_SOCKET);
}

CWSocket::operator SOCKET()
{
  return m_hSocket;
}
