/*
Module : SMTPSockets.h
Purpose: Interface for an MFC wrapper class for sockets
Created: PJN / 05-08-1998

Copyright (c) 2002 - 2015 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


/////////////////////////////// Macros / Defines //////////////////////////////

#pragma once

#ifndef __SMTPSOCKETS_H__
#define __SMTPSOCKETS_H__

__if_not_exists(ADDRESS_FAMILY)
{
  typedef USHORT ADDRESS_FAMILY;
}

__if_not_exists(SOCKADDR_INET)
{
  typedef union _SOCKADDR_INET 
  {
      SOCKADDR_IN Ipv4;
      SOCKADDR_IN6 Ipv6;
      ADDRESS_FAMILY si_family;    
  } SOCKADDR_INET, *PSOCKADDR_INET;
}


////////////////////////////// Classes ////////////////////////////////////////

#ifdef SOCKET_MFC_EXTENSTIONS
class CWSocketException : public CException
#else
class CWSocketException : public std::exception
#endif //#ifdef SOCKET_MFC_EXTENSTIONS
{
public:
//Constructors / Destructors
  CWSocketException(int nError);

//Methods
#ifdef SOCKET_MFC_EXTENSTIONS
#ifdef _DEBUG
  virtual void Dump(CDumpContext& dc) const;
#endif //#ifdef _DEBUG
#endif //#ifdef SOCKET_MFC_EXTENSTIONS

#if _MSC_VER >= 1700
  virtual BOOL GetErrorMessage(_Out_z_cap_(nMaxError) LPTSTR lpszError, _In_ UINT nMaxError,	_Out_opt_ PUINT pnHelpContext = NULL);
#else	
  virtual BOOL GetErrorMessage(__out_ecount_z(nMaxError) LPTSTR lpszError, __in UINT nMaxError, __out_opt PUINT pnHelpContext = NULL);
#endif
  
#ifdef SOCKET_MFC_EXTENSTIONS
  CString GetErrorMessage();
#endif //#ifdef SOCKET_MFC_EXTENSTIONS

//Data members
  int m_nError;
};

class CWSocket
{
public:
//Constructors / Destructors
  CWSocket();
  virtual ~CWSocket();

//typedefs
#ifdef SOCKET_MFC_EXTENSTIONS
  typedef CString String;
#else
  #ifdef _UNICODE
    typedef std::wstring String; 
  #else
    typedef std::string String;
  #endif //#ifdef _UNICODE
#endif //#ifdef SOCKET_MFC_EXTENSTIONS

//Attributes
  void    Attach(SOCKET hSocket);
  SOCKET  Detach(); 
  void    GetPeerName(String& sPeerAddress, UINT& nPeerPort, int nAddressToStringFlags = 0);
  void    GetPeerName(SOCKADDR* pSockaddr, int* pSockAddrLen);
  void    GetSockName(String& sSocketAddress, UINT& nSocketPort, int nAddressToStringFlags = 0);
  void    GetSockName(SOCKADDR* pSockAddr, int* pSockAddrLen);
  void    SetSockOpt(int nOptionName, const void* pOptionValue, int nOptionLen, int nLevel = SOL_SOCKET);
  void    GetSockOpt(int nOptionName, void* pOptionValue, int* pOptionLen, int nLevel = SOL_SOCKET);
  BOOL    IsCreated() const; 
  BOOL    IsReadible(DWORD dwTimeout);
  BOOL    IsWritable(DWORD dwTimeout);
  void    SetBindAddress(const String& sBindAddress) { m_sBindAddress = sBindAddress; };
  String  GetBindAddress() const { return m_sBindAddress; };

//Methods
  void    Create(BOOL bUDP = FALSE, BOOL bIPv6 = FALSE);
  void    Create(int nSocketType, int nProtocolType, int nAddressFormat);
  void    Accept(CWSocket& connectedSocket, SOCKADDR* pSockAddr = NULL, int* pSockAddrLen = NULL);
  void    CreateAndBind(UINT nSocketPort, int nSocketType = SOCK_STREAM, int nDefaultAddressFormat = AF_INET);
  void    Bind(const SOCKADDR* pSockAddr, int nSockAddrLen);
  void    Close();
  void    Connect(const SOCKADDR* pSockAddr, int nSockAddrLen);
  void    CreateAndConnect(LPCTSTR pszHostAddress, UINT nHostPort, int nSocketType = SOCK_STREAM, int nFamily = AF_UNSPEC, int nProtocolType = 0);
  void    CreateAndConnect(LPCTSTR pszHostAddress, LPCTSTR pszPortOrServiceName, int nSocketType = SOCK_STREAM, int nFamily = AF_UNSPEC, int nProtocolType = 0);
  void    Connect(const SOCKADDR* pSockAddr, int nSockAddrLen, DWORD dwTimeout, BOOL bResetToBlockingMode = TRUE);
  void    CreateAndConnect(LPCTSTR pszHostAddress, UINT nHostPort, DWORD dwTimeout, BOOL bResetToBlockingMode, int nSocketType = SOCK_STREAM);
  void    CreateAndConnect(LPCTSTR pszHostAddress, LPCTSTR pszPortOrServiceName, DWORD dwTimeout, BOOL bResetToBlockingMode, int nSocketType = SOCK_STREAM);
  void    IOCtl(long lCommand, DWORD* pArgument);
  void    Listen(int nConnectionBacklog = SOMAXCONN);
  int     Receive(void* pBuf, int nBufLen, int nFlags = 0);
  int     ReceiveFrom(void* pBuf, int nBufLen, SOCKADDR* pSockAddr, int* pSockAddrLen, int nFlags = 0);
  int     ReceiveFrom(void* pBuf, int nBufLen, String& sSocketAddress, UINT& nSocketPort, int nReceiveFromFlags = 0, int nAddressToStringFlags = 0);
  int     Send(const void* pBuffer, int nBufLen, int nFlags = 0);
  int     SendTo(const void* pBuf, int nBufLen, const SOCKADDR* pSockAddr, int nSockAddrLen, int nFlags = 0);
  int     SendTo(const void* pBuf, int nBufLen, UINT nHostPort, LPCTSTR pszHostAddress = NULL, int nFlags = 0);
  void    ShutDown(int nHow = SD_SEND);

//Operators
  operator SOCKET();

//Static methods
  static void ThrowWSocketException(int nError = 0);
  static String AddressToString(const SOCKADDR* pSockAddr, int nSockAddrLen, int nFlags = 0, UINT* pnSocketPort = NULL);
  static String AddressToString(const SOCKADDR_INET& sockAddr, int nFlags = 0, UINT* pnSocketPort = NULL);

protected:
//Methods
  void _Connect(LPCTSTR pszHostAddress, LPCTSTR pszPortOrServiceName);
  void _Bind(LPCTSTR pszPortOrServiceName);

//Member variables
  SOCKET m_hSocket;
  String m_sBindAddress;
};

#endif //__SMTPSOCKETS_H__
