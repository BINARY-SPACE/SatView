/*
Module : SSLWrappers.h
Purpose: Defines the interface for a C++ wrapper class for a SSL SChannel Security Support Provider 
         Interface (SSPI) on Windows
History: PJN / 22-10-2014 1. Initial public release
         PJN / 26-11-2014 1. Changed the CSSL class to contain a credentials reference rather than an actual 
                          instance. A new class called CCachedCredentials is what the CSSL maintains a 
                          reference to. 
         PJN / 16-12-2014 1. Removed the unused variable CCachedCredentials::m_Credentials.
                          2. Removed the memset call and the setting of the dwVersion member variable of the 
                          m_sslCredentials member variable in the AcquireClient and AcquireServer methods of 
                          CCachedCredentials. This allows client code to set specific values into this structure 
                          prior to it being used in these methods.
                          3. The default value for CSSL::m_dwAuditFlags is now 0 for debug builds in addition to 
                          release builds.
                          4. Addition of a CSSL::GetSecPkgStreamSizes method to allow access to the internal
                          m_SecPkgSizes member variable
                          5. Addition of a CSSL::SendEncrypted method which handles making multiple calls to 
                          SendEncryptedMessage if the data to send exceeds the maximum SSL message size.
         PJN / 08-02-2015 1. Updated copyright details
                          2. Fixed a bug in the CSSL constructor where the "m_lExtraReadData" was not being 
                          initialized to 0. This causes a bug later when GetEncryptedMessage is called and
                          you have compiled your application without the VC 2013 /sdl compiler flag which 
                          resulted in the bug being hidden as /sdl auto initializes member variables. Thanks
                          to Bostjan Erzen for reporting this bug
         PJN / 04-11-2015 1. Updated the code to compile cleanly in VC 2015.
                          2. Fixed a bug in CSSL::VerifyServerCertificate where the code was using wrong math
                          to calculate the size of the pCerts local variable.
                          3. Fixed a bug in the demo app's DisplayCertChain method when calculating the size
                          of the buffer to pass to CertNameToStr API.
                          4. Reworked various places which allocates heap memory to use ATL::CHeapPtr instead 
                          of raw calls to HeapAlloc.

Copyright (c) 2014 - 2015 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


////////////////////////// Macros / Defines ///////////////////////////////////

#pragma once

#ifndef __SSLWRAPPERS_H__
#define __SSLWRAPPERS_H__

#include "CryptoStore.h"


////////////////////////// Classes ////////////////////////////////////////////

namespace SSLWrappers
{
//Encapsulates a SChannel CredHandle
class CCredentials
{
public:
//Constructors / Destructors
  CCredentials()
  {
    m_Handle.dwUpper = 0;
    m_Handle.dwLower = 0;
  }
  
  CCredentials(_In_ CCredentials& credentials)
  {
    m_Handle.dwUpper = 0;
    m_Handle.dwLower = 0;
    Attach(credentials.Detach());
  }
  
  explicit CCredentials(_In_ const CredHandle& handle)
  {
    m_Handle.dwUpper = handle.dwUpper;
    m_Handle.dwLower = handle.dwLower;
  }

  ~CCredentials()
  {
    if (ValidHandle())
      Free();
  }
  
//Methods
  CCredentials& operator=(_In_ CCredentials& credentials)
  {
    if (this != &credentials)
    {
      if (ValidHandle())
        Free();
      Attach(credentials.Detach());
    }
    
    return *this;
  }

  CredHandle Handle() const
  {
    return m_Handle;
  }

  void Attach(_In_ const CredHandle& handle)
  {
    //Validate our parameters
    ATLASSERT(m_Handle.dwUpper == 0);
    ATLASSERT(m_Handle.dwLower == 0);
    
    m_Handle.dwUpper = handle.dwUpper;
    m_Handle.dwLower = handle.dwLower;
  }

  CredHandle Detach()
  {
    CredHandle handle;
    handle.dwUpper = m_Handle.dwUpper;
    handle.dwLower = m_Handle.dwLower;
    m_Handle.dwUpper = 0;
    m_Handle.dwLower = 0;
    return handle;
  }

  _Check_return_
  SECURITY_STATUS Acquire(_In_ unsigned long fCredentialUse, _In_opt_ SCHANNEL_CRED* pAuthData, _Out_opt_ PTimeStamp ptsExpiry = nullptr)
  {
    //Validate our parameters
    ATLASSERT(!ValidHandle());
    
    return AcquireCredentialsHandle(nullptr, UNISP_NAME, fCredentialUse, nullptr, pAuthData, nullptr, nullptr, &m_Handle, ptsExpiry);
  }

  SECURITY_STATUS Free()
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    SECURITY_STATUS status = FreeCredentialsHandle(&m_Handle);
    m_Handle.dwUpper = 0;
    m_Handle.dwLower = 0;
    return status;
  }

  SECURITY_STATUS QueryAttibute(_In_ unsigned long ulAttribute, _Inout_ void* pBuffer)
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    return QueryCredentialsAttributes(&m_Handle, ulAttribute, pBuffer);
  }

  BOOL ValidHandle() const
  {
    return (m_Handle.dwUpper != 0) || (m_Handle.dwLower != 0);
  }

//Member variables
  CredHandle m_Handle;
};


//Encapsulates a SChannel CtxtHandle
class CContext
{
public:
//Constructors / Destructors
  CContext()
  {
    m_Handle.dwUpper = 0;
    m_Handle.dwLower = 0;
  }
  
  CContext(_In_ CContext& context)
  {
    m_Handle.dwUpper = 0;
    m_Handle.dwLower = 0;
    Attach(context.Detach());
  }
  
  explicit CContext(_In_ const CtxtHandle& handle)
  {
    m_Handle.dwUpper = handle.dwUpper;
    m_Handle.dwLower = handle.dwLower;
  }

  ~CContext()
  {
    if (ValidHandle())
      Delete();
  }
  
//Methods
  CContext& operator=(_In_ CContext& context)
  {
    if (this != &context)
    {
      if (ValidHandle())
        Delete();
      Attach(context.Detach());
    }
    
    return *this;
  }

  CtxtHandle Handle() const
  {
    return m_Handle;
  }

  void Attach(_In_ const CtxtHandle& handle)
  {
    //Validate our parameters
    ATLASSERT(!ValidHandle());
    
    m_Handle.dwUpper = handle.dwUpper;
    m_Handle.dwLower = handle.dwLower;
  }

  CtxtHandle Detach()
  {
    CtxtHandle handle;
    handle.dwUpper = m_Handle.dwUpper;
    handle.dwLower = m_Handle.dwLower;
    m_Handle.dwUpper = 0;
    m_Handle.dwLower = 0;
    return handle;
  }

  _Check_return_
  SECURITY_STATUS Initialize(_In_ CCredentials& credentials,
                           #ifdef _UNICODE
                             _In_opt_ SEC_WCHAR* pszTargetName, 
                           #else
                             _In_opt_ SEC_CHAR* pszTargetName, 
                           #endif //#ifdef _UNICODE
                             _In_ unsigned long fContextReq, _In_opt_ PSecBufferDesc pInput, _Inout_opt_ PSecBufferDesc pOutput, _Out_ unsigned long* pfContextAttr, _Out_opt_ PTimeStamp ptsExpiry = nullptr)
  {
    return InitializeSecurityContext(&credentials.m_Handle, ValidHandle() ? &m_Handle : nullptr, pszTargetName, fContextReq, 0, 0, pInput, 0, &m_Handle, pOutput, pfContextAttr, ptsExpiry);
  }

  _Check_return_
  SECURITY_STATUS Accept(_In_ CCredentials& credentials, _In_opt_ PSecBufferDesc pInput, _In_ unsigned long fContextReq, _Inout_opt_ PSecBufferDesc pOutput,
                         _Out_ unsigned long* pfContextAttr, _Out_opt_ PTimeStamp ptsExpiry = nullptr)
  {
    return AcceptSecurityContext(&credentials.m_Handle, ValidHandle() ? &m_Handle : nullptr, pInput, fContextReq, 0, &m_Handle, pOutput, pfContextAttr, ptsExpiry);
  }

  SECURITY_STATUS Delete()
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    SECURITY_STATUS status = DeleteSecurityContext(&m_Handle);
    m_Handle.dwUpper = 0;
    m_Handle.dwLower = 0;
    return status;
  }

  SECURITY_STATUS SetAttribute(_In_ unsigned long ulAttribute, _In_reads_bytes_(cbBuffer) void* pBuffer, _In_ unsigned long cbBuffer)
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    return SetContextAttributes(&m_Handle, ulAttribute, pBuffer, cbBuffer);
  }

  SECURITY_STATUS QueryAttribute(_In_ unsigned long ulAttribute, _Out_ void* pBuffer)
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    return QueryContextAttributes(&m_Handle, ulAttribute, pBuffer);
  }

  SECURITY_STATUS DecryptMessage(_In_ PSecBufferDesc pMessage)
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    return ::DecryptMessage(&m_Handle, pMessage, 0, nullptr);
  }

  SECURITY_STATUS EncryptMessage(_In_ PSecBufferDesc pMessage, _In_ unsigned long fQOP = 0)
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    return ::EncryptMessage(&m_Handle, fQOP, pMessage, 0);
  }

  SECURITY_STATUS ApplyControlToken(_In_ PSecBufferDesc pInput)
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    return ::ApplyControlToken(&m_Handle, pInput);
  }

  SECURITY_STATUS Impersonate()
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    return ImpersonateSecurityContext(&m_Handle);
  }

  SECURITY_STATUS Revert()
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    return RevertSecurityContext(&m_Handle);
  }

  SECURITY_STATUS QueryToken(_Out_ void** phToken)
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    return QuerySecurityContextToken(&m_Handle, phToken);
  }

  SECURITY_STATUS Export(_In_ ULONG fFlags, _Out_ PSecBuffer pPackedContext, _Out_ void** pToken)
  {
    //Validate our parameters
    ATLASSERT(ValidHandle());

    return ExportSecurityContext(&m_Handle, fFlags, pPackedContext, pToken);
  }

  SECURITY_STATUS Import(_In_ PSecBuffer pPackedContext, _In_ VOID* Token)
  {
    //Validate our parameters
    ATLASSERT(!ValidHandle());

    return ImportSecurityContext(UNISP_NAME, pPackedContext, Token, &m_Handle);
  }

  BOOL ValidHandle() const
  {
    return (m_Handle.dwUpper != 0) || (m_Handle.dwLower != 0);
  }

//Member variables
  CtxtHandle m_Handle;
};


//A simple class which encapsulates a single received message
class CMessage
{
public:
//Constructors / Destructors
  CMessage() : m_pbyData(nullptr),
               m_lSize(0)
  {
  }

  CMessage(_In_ const CMessage& message) = delete;

  CMessage(_In_ CMessage&& message) : m_pbyData(message.m_pbyData),
                                      m_lSize(message.m_lSize)
  {
    message.m_pbyData = nullptr;
    message.m_lSize = 0;
  }

  virtual ~CMessage()
  {
    //Free up the heap memory we have used
    if (m_pbyData != nullptr)
      Deallocate();
  }

//Methods
  CMessage& operator=(_In_ const CMessage& message) = delete;

  CMessage& operator=(_In_ CMessage&& message) = delete;

  virtual SECURITY_STATUS Allocate(_In_ ULONG lSize)
  {
    //Validate our parameters
    ATLASSERT(m_pbyData == nullptr);

    //By default CMessage will use the raw Win32 Heap allocation API. Derived classes are
    //free to use their own preferred heap allocation API
    m_pbyData = static_cast<BYTE*>(HeapAlloc(GetProcessHeap(), 0, lSize));
    if (m_pbyData == nullptr)
      return SEC_E_INSUFFICIENT_MEMORY;
    m_lSize = lSize;

    return SEC_E_OK;
  }

  virtual SECURITY_STATUS Deallocate()
  {
    //Validate our parameters
    ATLASSERT(m_pbyData != nullptr);

    //Free up the heap memory we have used
    BOOL bSuccess = HeapFree(GetProcessHeap(), 0, m_pbyData);
    m_pbyData = nullptr;
    m_lSize = 0;

    return bSuccess ? SEC_E_OK : MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, GetLastError());
  }

//Member variables
  BYTE* m_pbyData;
  ULONG m_lSize;
};


//A class which caches the certificate details for credentials 
class CCachedCredentials : public CCredentials
{
public:
//Constructors / Destructors
  CCachedCredentials()
  {
    memset(&m_sslCredentials, 0, sizeof(m_sslCredentials));
    m_sslCredentials.dwVersion = SCHANNEL_CRED_VERSION;
  }

//Methods
  SECURITY_STATUS AcquireClient(_In_opt_ LPTSTR pszClientCertificateName = nullptr, _In_ LPCSTR lpszStoreProvider = CERT_STORE_PROV_SYSTEM, _In_ DWORD dwCertOpenStoreFlags = CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_READONLY_FLAG, _In_opt_ const void* pvCertOpenStorePara = L"MY")
  {
    //Find the client certificate if required
    if (pszClientCertificateName != nullptr)
    {
      //Open the specified certificate store
      CryptoWrappers::CStore certStore;
      if (!certStore.Open(lpszStoreProvider, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, dwCertOpenStoreFlags, pvCertOpenStorePara))
        return GetLastError();

      //Fill in an attribute structure for the certificate common name we are looking for
      CERT_RDN_ATTR certRDNAttr[1];
      certRDNAttr[0].pszObjId = szOID_COMMON_NAME;
      certRDNAttr[0].dwValueType = CERT_RDN_PRINTABLE_STRING;
      certRDNAttr[0].Value.pbData = reinterpret_cast<BYTE*>(pszClientCertificateName);
      certRDNAttr[0].Value.cbData = static_cast<DWORD>(_tcslen(pszClientCertificateName) * sizeof(TCHAR));
      CERT_RDN certRDN;
      certRDN.cRDNAttr = 1;
      certRDN.rgRDNAttr = certRDNAttr;

      //Find the certificate context
      CryptoWrappers::CCertificate prevCertificate;
      m_Certificate = certStore.FindCertificate(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                                                    #ifdef _UNICODE 
                                                      CERT_UNICODE_IS_RDN_ATTRS_FLAG, 
                                                    #else
                                                      0,
                                                    #endif //#ifdef _UNICODE
                                                      CERT_FIND_SUBJECT_ATTR, &certRDN, prevCertificate);
      if (m_Certificate.Handle() == nullptr)
        return GetLastError();
    }

    if (m_Certificate.Handle() != nullptr)
    {
      m_sslCredentials.cCreds = 1;
      m_sslCredentials.paCred = &m_Certificate.m_pCert;
    }
    return Acquire(SECPKG_CRED_OUTBOUND, &m_sslCredentials);
  }

  SECURITY_STATUS AcquireServer(_In_ LPTSTR pszServerCertificateName, _In_ LPCSTR lpszStoreProvider = CERT_STORE_PROV_SYSTEM, _In_ DWORD dwCertOpenStoreFlags = CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_READONLY_FLAG, _In_opt_ const void* pvCertOpenStorePara = L"MY")
  {
    //Open the specified certificate store
    CryptoWrappers::CStore certStore;
    if (!certStore.Open(lpszStoreProvider, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, dwCertOpenStoreFlags, pvCertOpenStorePara))
      return GetLastError();

    //Fill in an attribute structure for the certificate common name we are looking for
    CERT_RDN_ATTR certRDNAttr[1];
    certRDNAttr[0].pszObjId = szOID_COMMON_NAME;
    certRDNAttr[0].dwValueType = CERT_RDN_PRINTABLE_STRING;
    certRDNAttr[0].Value.pbData = reinterpret_cast<BYTE*>(pszServerCertificateName);
    certRDNAttr[0].Value.cbData = static_cast<DWORD>(_tcslen(pszServerCertificateName) * sizeof(TCHAR));
    CERT_RDN certRDN;
    certRDN.cRDNAttr = 1;
    certRDN.rgRDNAttr = certRDNAttr;

    //Find the certificate context
    CryptoWrappers::CCertificate prevCertificate;
    m_Certificate = certStore.FindCertificate(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                                                  #ifdef _UNICODE 
                                                    CERT_UNICODE_IS_RDN_ATTRS_FLAG, 
                                                  #else
                                                    0,
                                                  #endif //#ifdef _UNICODE
                                                    CERT_FIND_SUBJECT_ATTR, &certRDN, prevCertificate);
    if (m_Certificate.Handle() == nullptr)
      return GetLastError();

    m_sslCredentials.cCreds = 1;
    m_sslCredentials.paCred = &m_Certificate.m_pCert;
    return Acquire(SECPKG_CRED_INBOUND, &m_sslCredentials);
  }

//Member variables
  SCHANNEL_CRED                m_sslCredentials;
  CryptoWrappers::CCertificate m_Certificate;
};



//The higher level class which provides a base class implementation of SSL using SSPI
class CSSL : public CContext
{
public:
//Defines
  enum
  {
      AUDIT_DATA   = 0x01,
      AUDIT_EVENTS = 0x02,
      AUDIT_ERRORS = 0x04
  };


//Constructors / Destructors
  CSSL() : m_lReadBufferLen(0),
           m_lWriteBufferLen(0),
           m_LastStatus(SEC_E_OK),
           m_bVerifyServerCertificate(FALSE),
           m_bVerifyClientCertificate(FALSE),
           m_dwCertVerifyCertificateChainPolicyFlags(0),
           m_dwCertGetCertificateChainFlags(CERT_CHAIN_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT),
           m_bCheckServerCertificateRevocation(FALSE),
           m_pCachedCredentials(nullptr),
           m_dwAuditFlags(0),
           m_lExtraReadData(0)
  {
    memset(&m_SecPkgSizes, 0, sizeof(m_SecPkgSizes));

    //Allocate the read buffer, the size of the max packet for this SSPI
    PSecPkgInfo pSecInfo = nullptr;
    m_LastStatus = QuerySecurityPackageInfo(UNISP_NAME, &pSecInfo);
    if (m_LastStatus == SEC_E_OK) 
    {
      if (!m_ReadBuffer.AllocateBytes(pSecInfo->cbMaxToken))
        m_LastStatus = SEC_E_INSUFFICIENT_MEMORY;
      else
        m_lReadBufferLen = pSecInfo->cbMaxToken;
      FreeContextBuffer(pSecInfo);
    }
  }

//Virtual methods
  virtual SECURITY_STATUS SendData(_In_reads_bytes_opt_(lSize) const BYTE* pbyData, ULONG lSize)
  {
    ATLASSERT(FALSE); //Derived classes need to implement this method

    UNREFERENCED_PARAMETER(pbyData);
    UNREFERENCED_PARAMETER(lSize);

    return E_NOTIMPL;
  }

  virtual SECURITY_STATUS ReceiveData(_Out_writes_bytes_to_(lSize, lReceived) BYTE* pbyData, _In_ ULONG lSize, _Out_ ULONG& lReceived)
  {
    ATLASSERT(FALSE); //Derived classes need to implement this method

    UNREFERENCED_PARAMETER(pbyData);
    UNREFERENCED_PARAMETER(lSize);

    lReceived = 0;
    return E_NOTIMPL;
  }

//Non virtual methods
  void SetCachedCredentials(_In_ CCachedCredentials* pCredentials)
  {
    m_pCachedCredentials = pCredentials;
  }

  CCachedCredentials* GetCachedCredentials() const
  {
    return m_pCachedCredentials;
  }

  void SetAuditFlags(_In_ DWORD dwAuditFlags)
  {
    m_dwAuditFlags = dwAuditFlags;
  }

  DWORD GetAuditFlags() const
  {
    return m_dwAuditFlags;
  }

  void SetVerifyServerCertificate(_In_ BOOL bVerifyServerCertificate)
  {
    m_bVerifyServerCertificate = bVerifyServerCertificate;
  }

  BOOL GetVerifyServerCertificate() const
  {
    return m_bVerifyServerCertificate;
  }

  void SetVerifyClientCertificate(_In_ BOOL bVerifyClientCertificate)
  {
    m_bVerifyClientCertificate = bVerifyClientCertificate;
  }

  BOOL GetVerifyClientCertificate() const
  {
    return m_bVerifyClientCertificate;
  }

  void SetCertVerifyCertificateChainPolicyFlags(_In_ DWORD dwFlags)
  {
    m_dwCertVerifyCertificateChainPolicyFlags = dwFlags;
  }

  DWORD GetCertVerifyCertificateChainPolicyFlags() const
  {
    return m_dwCertVerifyCertificateChainPolicyFlags;
  }

  void SetCertGetCertificateChainFlags(_In_ DWORD dwFlags)
  {
    m_dwCertGetCertificateChainFlags = dwFlags;
  }

  DWORD GetCertGetCertificateChainFlags() const
  {
    return m_dwCertGetCertificateChainFlags;
  }

  void SetCheckServerCertificateRevocation(_In_ BOOL bCheckServerCertificateRevocation)
  {
    m_bCheckServerCertificateRevocation = bCheckServerCertificateRevocation;
  }

  BOOL GetCheckServerCertificateRevocation() const
  {
    return m_bCheckServerCertificateRevocation;
  }

  const SecPkgContext_StreamSizes& GetSecPkgStreamSizes() const
  {
    return m_SecPkgSizes;
  }

  virtual unsigned long GetClientContextRequest()
  {
    //Validate our parameters
    ATLASSERT(m_pCachedCredentials != nullptr);

    //Work out the context request flags to use
    unsigned long nContextRequest = ISC_REQ_SEQUENCE_DETECT | 
                                    ISC_REQ_REPLAY_DETECT   |
                                    ISC_REQ_CONFIDENTIALITY | 
                                    ISC_RET_EXTENDED_ERROR  |
                                    ISC_REQ_ALLOCATE_MEMORY | 
                                    ISC_REQ_STREAM;
    if (m_pCachedCredentials->m_sslCredentials.cCreds)
      nContextRequest |= ISC_REQ_MUTUAL_AUTH;

    return nContextRequest;
  }

  virtual SECURITY_STATUS SSLConnect(_In_ LPCTSTR pszServerName)
  {
    //Validate our parameters
    ATLASSERT(m_pCachedCredentials != nullptr);

    //Check the last security status value before we go any further
    if (m_LastStatus != SEC_E_OK)
      return m_LastStatus;

    //Work out the context request flags to use
    unsigned long nContextRequest = GetClientContextRequest();

    //Initialize the out buffers
    SecBuffer OutBuffers[1];
    OutBuffers[0].pvBuffer   = nullptr;
    OutBuffers[0].BufferType = SECBUFFER_TOKEN;
    OutBuffers[0].cbBuffer   = 0;
    SecBufferDesc OutBuffer;
    OutBuffer.cBuffers = 1;
    OutBuffer.pBuffers = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

    //Work with a non const local copy of pszServerName 
    TCHAR* pszLocalServerName = _tcsdup(pszServerName);
    if (pszLocalServerName == nullptr)
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)
        Audit(_T("CSSL::SSLConnect, Failed to duplicate pszServerName parameter\n"));

      return SEC_E_INSUFFICIENT_MEMORY;
    }

    //Call InitializeSecurityContext for the first time
    unsigned long nContextRequestOut = 0;
    ATLASSERT(m_pCachedCredentials->ValidHandle());
    SECURITY_STATUS status = Initialize(*m_pCachedCredentials, pszLocalServerName, nContextRequest, nullptr, &OutBuffer, &nContextRequestOut);
    free(pszLocalServerName);
    if (status != SEC_I_CONTINUE_NEEDED)
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)
        Audit(_T("CSSL::SSLConnect, InitializeSecurityContext failed, Error:0x%08X\n"), status);

      return status;
    }

    //Write out any data which SSPI provided to us if required
    if (OutBuffers[0].cbBuffer != 0)
    {
      //Validate our parameters
      ATLASSERT(OutBuffers[0].pvBuffer != nullptr);

      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_EVENTS)
        Audit(_T("CSSL::SSLConnect, InitializeSecurityContext has provided %u bytes of data to send to server\n"), OutBuffers[0].cbBuffer);
      if (m_dwAuditFlags & AUDIT_DATA)
        AuditData(_T("CSSL::SSLConnect, sending data to server"), static_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);
      
      status = SendData(static_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);
      if (status != SEC_E_OK)
      {
        if (m_dwAuditFlags & AUDIT_ERRORS)  
          Audit(_T("CSSL::SSLConnect, An error occured sending data to the server, Error:0x%08X\n"), status);
      }
    }

    //Free output buffer if required
    if (OutBuffers[0].pvBuffer != nullptr)
    {
      FreeContextBuffer(OutBuffers[0].pvBuffer);
      OutBuffers[0].pvBuffer = nullptr;
    }

    //Delegate most of the rest of the work to the internal helper method
    if (status == SEC_E_OK)
      status = ClientHandshakeLoop(pszServerName, nContextRequest, TRUE);

    //Allocate the send buffer before we return
    if (status == SEC_E_OK)
      status = AllocateSendBuffer();

    return status;
  }

  virtual SECURITY_STATUS SSLRequestRenegotiationClient(_In_ LPCTSTR pszServerName)
  {
    //Validate our parameters
    ATLASSERT(m_pCachedCredentials != nullptr);

    //Work out the context request flags to use
    unsigned long nContextRequest = GetClientContextRequest();

    //Initialize the out buffers
    SecBuffer OutBuffers[1];
    OutBuffers[0].pvBuffer   = nullptr;
    OutBuffers[0].BufferType = SECBUFFER_TOKEN;
    OutBuffers[0].cbBuffer   = 0;
    SecBufferDesc OutBuffer;
    OutBuffer.cBuffers = 1;
    OutBuffer.pBuffers = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

    //Work with a non const local copy of pszServerName 
    TCHAR* pszLocalServerName = _tcsdup(pszServerName);
    if (pszLocalServerName == nullptr)
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)
        Audit(_T("CSSL::SSLRequestRenegotiationClient, Failed to duplicate pszServerName parameter\n"));

      return SEC_E_INSUFFICIENT_MEMORY;
    }

    //Call InitializeSecurityContext for the first time
    unsigned long nContextRequestOut = 0;
    ATLASSERT(m_pCachedCredentials->ValidHandle());
    SECURITY_STATUS status = Initialize(*m_pCachedCredentials, pszLocalServerName, nContextRequest, nullptr, &OutBuffer, &nContextRequestOut);
    free(pszLocalServerName);
    if (status != SEC_I_CONTINUE_NEEDED)
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)
        Audit(_T("CSSL::SSLRequestRenegotiationClient, InitializeSecurityContext failed, Error:0x%08X\n"), status);

      return status;
    }

    //Write out any data which SSPI provided to us if required
    if (OutBuffers[0].cbBuffer != 0)
    {
      //Validate our parameters
      ATLASSERT(OutBuffers[0].pvBuffer != nullptr);

      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_EVENTS)
        Audit(_T("CSSL::SSLRequestRenegotiationClient, InitializeSecurityContext has provided %u bytes of data to send to server\n"), OutBuffers[0].cbBuffer);
      if (m_dwAuditFlags & AUDIT_DATA)
        AuditData(_T("CSSL::SSLRequestRenegotiationClient, sending data to server"), static_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);
      
      status = SendData(static_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);
      if (status != SEC_E_OK)
      {
        if (m_dwAuditFlags & AUDIT_ERRORS)  
          Audit(_T("CSSL::SSLRequestRenegotiationClient, An error occured sending data to the server, Error:0x%08X\n"), status);
      }
    }

    //Free output buffer if required
    if (OutBuffers[0].pvBuffer != nullptr)
    {
      FreeContextBuffer(OutBuffers[0].pvBuffer);
      OutBuffers[0].pvBuffer = nullptr;
    }

    //Delegate most of the rest of the work to the internal helper method
    if (status == SEC_E_OK)
      status = ClientHandshakeLoop(pszServerName, nContextRequest, TRUE);

    return status;
  }

  virtual SECURITY_STATUS SSLHandleRenegotiationClient(_In_ LPCTSTR pszServerName)
  {
    return ClientHandshakeLoop(pszServerName, GetClientContextRequest(), FALSE);
  }

  virtual SECURITY_STATUS SSLAccept(_In_ BOOL bClientAuth)
  {
    //Check the last security status value before we go any further
    if (m_LastStatus != SEC_E_OK)
      return m_LastStatus;

    //Delegate most of the rest of the work to the internal helper method
    SECURITY_STATUS status = ServerHandshakeLoop(GetServerContextRequest(bClientAuth), TRUE);

    //Allocate the send buffer before we return
    if (status == SEC_E_OK)
      status = AllocateSendBuffer();

    return status;
  }

  virtual SECURITY_STATUS SSLRequestRenegotiationServer(_In_ BOOL bClientAuth)
  {
    //Validate our parameters
    ATLASSERT(m_pCachedCredentials != nullptr);

    //Work out the context request flags to use
    unsigned long nContextRequest = GetServerContextRequest(bClientAuth);

    //Initialize the out buffers
    SecBuffer OutBuffers[1];
    OutBuffers[0].pvBuffer   = nullptr;
    OutBuffers[0].BufferType = SECBUFFER_TOKEN;
    OutBuffers[0].cbBuffer   = 0;
    SecBufferDesc OutBuffer;
    OutBuffer.cBuffers = 1;
    OutBuffer.pBuffers = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

    //Call AcceptSecurityContext
    unsigned long nContextRequestOut = 0;
    ATLASSERT(m_pCachedCredentials->ValidHandle());
    SECURITY_STATUS status = Accept(*m_pCachedCredentials, nullptr, nContextRequest, &OutBuffer, &nContextRequestOut);
    if (status != SEC_E_OK)
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)
        Audit(_T("CSSL::SSLRequestRenegotiationServer, InitializeSecurityContext failed, Error:0x%08X\n"), status);

      return status;
    }

    //Write out any data which SSPI provided to us if required
    if (OutBuffers[0].cbBuffer != 0)
    {
      //Validate our parameters
      ATLASSUME(OutBuffers[0].pvBuffer != nullptr);

      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_EVENTS)
        Audit(_T("CSSL::SSLRequestRenegotiationServer, InitializeSecurityContext has provided %u bytes of data to send to server\n"), OutBuffers[0].cbBuffer);
      if (m_dwAuditFlags & AUDIT_DATA)
        AuditData(_T("CSSL::SSLRequestRenegotiationServer, sending data to client"), static_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);
      
      status = SendData(static_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);
      if (status != SEC_E_OK)
      {
        if (m_dwAuditFlags & AUDIT_ERRORS)  
          Audit(_T("CSSL::SSLRequestRenegotiationServer, An error occured sending data to the client, Error:0x%08X\n"), status);
      }
    }

    //Free output buffer if required
    if (OutBuffers[0].pvBuffer != nullptr)
    {
      FreeContextBuffer(OutBuffers[0].pvBuffer);
      OutBuffers[0].pvBuffer = nullptr;
    }

    //Delegate most of the rest of the work to the internal helper method
    if (status == SEC_E_OK)
      status = ServerHandshakeLoop(nContextRequest, TRUE);

    return status;
  }

  virtual SECURITY_STATUS SSLHandleRenegotiationServer(_In_ BOOL bClientAuth)
  {
    return ServerHandshakeLoop(GetServerContextRequest(bClientAuth), TRUE);
  }

  virtual unsigned long GetServerContextRequest(_In_ BOOL bClientAuth)
  {
    //Work out the context request flags to use
    unsigned long nContextRequest = ASC_REQ_SEQUENCE_DETECT | 
                                    ASC_REQ_REPLAY_DETECT   | 
                                    ASC_REQ_CONFIDENTIALITY | 
                                    ASC_RET_EXTENDED_ERROR  | 
                                    ASC_REQ_ALLOCATE_MEMORY | 
                                    ASC_REQ_STREAM;
    if (bClientAuth)
      nContextRequest |= ASC_REQ_MUTUAL_AUTH;

    return nContextRequest;
  }

  virtual SECURITY_STATUS SendEncryptedMessage(_In_reads_bytes_(lSize) const BYTE* pbyData, _In_ ULONG lSize)
  {
    //Validate our parameters
    ATLASSERT(m_WriteBuffer.m_pData != nullptr);

    //Send the data
    if (m_dwAuditFlags & AUDIT_DATA)
      AuditData(_T("CSSL::SendEncryptedMessage, data to send"), pbyData, lSize);
  
    //Check to see if we can handle this sized message
    if ((lSize + m_SecPkgSizes.cbHeader + m_SecPkgSizes.cbTrailer) > m_lWriteBufferLen)
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)
        Audit(_T("CSSL::SendEncryptedMessage, message is too large\n"));

      return SEC_E_INVALID_PARAMETER;
    }

    //Setup the buffers
    memcpy_s(m_WriteBuffer.m_pData + m_SecPkgSizes.cbHeader, m_lWriteBufferLen - m_SecPkgSizes.cbHeader, pbyData, lSize);
    SecBuffer Buffers[4];
    Buffers[0].BufferType = SECBUFFER_STREAM_HEADER;
    Buffers[0].pvBuffer   = m_WriteBuffer.m_pData;
    Buffers[0].cbBuffer   = m_SecPkgSizes.cbHeader;
    Buffers[1].BufferType = SECBUFFER_DATA;
    Buffers[1].pvBuffer   = m_WriteBuffer.m_pData + m_SecPkgSizes.cbHeader;
    Buffers[1].cbBuffer   = lSize;
    Buffers[2].BufferType = SECBUFFER_STREAM_TRAILER;
    Buffers[2].pvBuffer   = m_WriteBuffer.m_pData + m_SecPkgSizes.cbHeader + lSize;
    Buffers[2].cbBuffer   = m_SecPkgSizes.cbTrailer;
    SecBufferDesc outBuffer;
    outBuffer.ulVersion = SECBUFFER_VERSION;
    outBuffer.cBuffers  = 3;
    outBuffer.pBuffers  = Buffers;

    //Encrypt the data
    SECURITY_STATUS status = EncryptMessage(&outBuffer, 0);
    if (status != SEC_E_OK)
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)  
        Audit(_T("CSSL::SendEncryptedMessage failed to encrypt data, Error:0x%08X\n"), status);

      return status;
    }

    //Do auditing if necessary
    if (m_dwAuditFlags & AUDIT_DATA)
      AuditData(_T("CSSL::SendEncryptedMessage, sending data"), m_WriteBuffer.m_pData, Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer);

    //Send the data
    status = SendData(m_WriteBuffer.m_pData, Buffers[0].cbBuffer + Buffers[1].cbBuffer + Buffers[2].cbBuffer);

    if ((status != SEC_E_OK) && (m_dwAuditFlags & AUDIT_ERRORS))
      Audit(_T("CSSL::SendEncryptedMessage, failed to send data, Error:0x%08X\n"), status);

    return status;
  }

  virtual SECURITY_STATUS SendEncrypted(_In_reads_bytes_(lSize) const BYTE* pbyData, _In_ ULONG lSize)
  {
    //Send the data (Note we send it a chunk at a time to ensure we do not exceed the max SSL message length)
    BOOL bMoreDataToSend = TRUE;
    ULONG lDataRemaining = lSize;
    const BYTE* pCurrentBuffer = pbyData;
    while (bMoreDataToSend)
    {
      ULONG lDataToSend = min(lDataRemaining, m_SecPkgSizes.cbMaximumMessage);
      SECURITY_STATUS ss = SendEncryptedMessage(pCurrentBuffer, lDataToSend);
      if (ss != SEC_E_OK)
        return ss;

      //Prepare for the next loop
      lDataRemaining -= lDataToSend;
      pCurrentBuffer += lDataToSend;
      bMoreDataToSend = (lDataRemaining > 0);
    }

    return SEC_E_OK;
  }

  virtual SECURITY_STATUS GetEncryptedMessage(_Inout_ CMessage& message)
  {
    //Validate our parameters
    ATLASSERT(message.m_lSize == 0);
    ATLASSERT(message.m_pbyData == nullptr);
    ATLASSERT(m_lReadBufferLen != 0);
    ATLASSERT(m_ReadBuffer.m_pData != nullptr);

    //Setup the buffers
    SecBuffer buffers[4];
    memset(buffers, 0, sizeof(buffers));
    SecBufferDesc secBufDesc;
    secBufDesc.ulVersion = SECBUFFER_VERSION;
    secBufDesc.cBuffers = 4;
    secBufDesc.pBuffers = buffers;

    //Loop around calling DecryptMessage and calling ReadData as necessary
    SECURITY_STATUS status = SEC_E_INCOMPLETE_MESSAGE;
    ULONG cbData = m_lExtraReadData;
    BYTE* pbyData = m_ReadBuffer.m_pData;
    do
    {
      //Setup the buffers with the received data
      buffers[0].BufferType = SECBUFFER_DATA;
      buffers[0].pvBuffer   = pbyData;
      buffers[0].cbBuffer   = cbData;
      buffers[1].BufferType = SECBUFFER_EMPTY;
      buffers[2].BufferType = SECBUFFER_EMPTY;
      buffers[3].BufferType = SECBUFFER_EMPTY;

      //If we have some data, try to decrypt it
      if (cbData != 0)
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::GetEncryptedMessage, calling DecryptMessage with %u bytes of data\n"), cbData);

        status = DecryptMessage(&secBufDesc);
      }

      //Get more data if required
      if (status == SEC_E_INCOMPLETE_MESSAGE)
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::GetEncryptedMessage, Going to network to read more data because status is SEC_E_INCOMPLETE_MESSAGE\n"));

        ULONG lReadBufferSize = m_lReadBufferLen - cbData;
        ULONG lReceived = 0;
        SECURITY_STATUS status2 = ReceiveData(pbyData + cbData, lReadBufferSize, lReceived);
        if (SUCCEEDED(status2))
        {
          if (lReceived)
          {
            //Do auditing if necessary
            if (m_dwAuditFlags & AUDIT_DATA)
              AuditData(_T("CSSL::GetEncryptedMessage, received data"), pbyData + cbData, lReceived);

            cbData += lReceived;
          }
          else
          {
            //Do auditing if necessary
            if (m_dwAuditFlags & AUDIT_ERRORS)
              Audit(_T("CSSL::GetEncryptedMessage, A graceful disconnect occured reading data\n"));

            status = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_GRACEFUL_DISCONNECT);
          }
        }
        else
        {
          //Do auditing if necessary
          if (m_dwAuditFlags & AUDIT_ERRORS)
            Audit(_T("CSSL::GetEncryptedMessage failed, Error:0x%08X\n"), status);

          status = status2;
        }
      }
      else if ((status != SEC_E_OK) && (m_dwAuditFlags & AUDIT_ERRORS)) //Do auditing if necessary
      {
        Audit(_T("CSSL::GetEncryptedMessage failed to decrypt data, Error:0x%08X\n"), status);
      }
    }
    while (status == SEC_E_INCOMPLETE_MESSAGE);

    if (status == SEC_E_OK)
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_EVENTS)
        Audit(_T("CSSL::GetEncryptedMessage was successful\n"));

      //Locate the data buffer
      int nIndexDataBuffer = -1;
      for (int i=1; (i<4) && (nIndexDataBuffer == -1); i++)
      {
        if (buffers[i].BufferType == SECBUFFER_DATA)
          nIndexDataBuffer = i;    
      }
      if (nIndexDataBuffer == -1)
      {
        status = SEC_E_DECRYPT_FAILURE;

        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_ERRORS)
          Audit(_T("CSSL::GetEncryptedMessage failed to locate data buffer for message\n"));

        return status;
      }

      //Setup the message output parameter
      ULONG nMessageSize = buffers[nIndexDataBuffer].cbBuffer;
      status = message.Allocate(nMessageSize);
      if (status != SEC_E_OK)
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_ERRORS)
          Audit(_T("CSSL::GetEncryptedMessage failed to allocate memory for message, Error:0x%08X\n"), status);

        return status;
      }
      memcpy_s(message.m_pbyData, message.m_lSize, buffers[1].pvBuffer, nMessageSize);
    }

    if ((status == SEC_E_OK) || (status == SEC_I_RENEGOTIATE))
    {
      //Locate the extra buffer
      int nIndexExtraBuffer = -1;
      for (int i=1; (i<4) && (nIndexExtraBuffer == -1); i++)
      {
        if (buffers[i].BufferType == SECBUFFER_EXTRA)
          nIndexExtraBuffer = i;    
      }

      //Move the extra data into the read buffer ready for the next call to GetEncryptedMessage
      if (nIndexExtraBuffer != -1)
      {
        m_lExtraReadData = buffers[nIndexExtraBuffer].cbBuffer;
        memcpy_s(m_ReadBuffer.m_pData, m_lReadBufferLen, pbyData + (cbData - m_lExtraReadData), m_lExtraReadData);

        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::GetEncryptedMessage, DecryptMessage returned %u bytes of additional unprocessed data\n"), buffers[nIndexExtraBuffer].cbBuffer);
      }
      else
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::GetEncryptedMessage, DecryptMessage returned no additional unprocessed data\n"));

        m_lExtraReadData = 0;
      }
    }

    return status;
  }

  virtual SECURITY_STATUS SendCloseNotify(_In_ BOOL bOperatingAsClient)
  {
    //Validate our parameters
    ATLASSERT(m_pCachedCredentials != nullptr);

    //Create the buffer description for the close notify
    DWORD dwType = SCHANNEL_SHUTDOWN;
    SecBuffer OutBuffers[1];
    OutBuffers[0].pvBuffer   = &dwType;
    OutBuffers[0].BufferType = SECBUFFER_TOKEN;
    OutBuffers[0].cbBuffer   = sizeof(dwType);
    SecBufferDesc OutBuffer;
    OutBuffer.cBuffers  = 1;
    OutBuffer.pBuffers  = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

    //Tell SSPI about our intent to shutdown
    SECURITY_STATUS status = ApplyControlToken(&OutBuffer);
    if (status != SEC_E_OK) 
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)   
        Audit(_T("CSSL::SendCloseNotify, ApplyControlToken failed, Error:0x%08X\n"), status);

      return status;
    }

    //Build the output buffer
    OutBuffers[0].pvBuffer   = NULL;
    OutBuffers[0].BufferType = SECBUFFER_TOKEN;
    OutBuffers[0].cbBuffer   = 0;
    OutBuffer.cBuffers  = 1;
    OutBuffer.pBuffers  = OutBuffers;
    OutBuffer.ulVersion = SECBUFFER_VERSION;

    //Work out the context request flags to use
    unsigned long nContextRequest = bOperatingAsClient ? GetClientContextRequest() : GetServerContextRequest(FALSE);

    unsigned long nContextRequestOut = 0;
    ATLASSERT(m_pCachedCredentials->ValidHandle());
    if (bOperatingAsClient)
      status = Initialize(*m_pCachedCredentials, nullptr, nContextRequest, nullptr, &OutBuffer, &nContextRequestOut);
    else
      status = Accept(*m_pCachedCredentials, nullptr, nContextRequest, &OutBuffer, &nContextRequestOut);

    if (status != SEC_E_OK)
    {
      //Do auditing if necessary  
      if (m_dwAuditFlags & AUDIT_ERRORS)
        Audit(_T("CSSL::SendCloseNotify failed, Error:0x%08X\n"), status);

      return status;
    }

    //Send the close notify message to the other side
    if (OutBuffers[0].cbBuffer != 0)
    {
      //Validate our parameters
      ATLASSERT(OutBuffers[0].pvBuffer != NULL);

      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_DATA) 
        AuditData(_T("CSSL::SendCloseNotify, Sending data"), reinterpret_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);

      status = SendData(reinterpret_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);

      if ((status != SEC_E_OK) && (m_dwAuditFlags & AUDIT_ERRORS))
        Audit(_T("CSSL::SendCloseNotify failed to send data, Error:0x%08X\n"), status);

      FreeContextBuffer(OutBuffers[0].pvBuffer);
    }

    return status;
  }

  virtual BOOL Audit(_In_z_ _Printf_format_string_ LPCTSTR pszFormat, ...)
  {
    //Work out the size of the buffer we need
    va_list argptr;
    va_start(argptr, pszFormat);
    int nBufferLen = _vsctprintf(pszFormat, argptr) + 1;

    //Allocate the buffer for the string and write into it
    ATL::CHeapPtr<TCHAR> auditBuffer;
    if (!auditBuffer.Allocate(nBufferLen))
      return FALSE;
    _vstprintf_s(auditBuffer.m_pData, nBufferLen, pszFormat, argptr);

    //Audit the data via OutputDebugString
    OutputDebugString(auditBuffer.m_pData);

    va_end(argptr);

    return TRUE;
  }

  virtual BOOL AuditData(_In_ LPCTSTR pszTitle, _In_reads_bytes_(lSize) const BYTE* pbyData, _In_ ULONG lSize)
  {
    LPTSTR pszString = nullptr;
    ATL::CHeapPtr<TCHAR> auditString;
    if (lSize != 0)
    {
      //First call to get the length of the buffer to allocate
      DWORD cchString = 0;
      if (!CryptBinaryToString(pbyData, lSize, CRYPT_STRING_HEXASCIIADDR, NULL, &cchString))
      {
        if (m_dwAuditFlags & AUDIT_ERRORS)
          Audit(_T("CSSL::AuditData, %s, failed call to CryptBinaryToString, Error:%u\n"), pszTitle, GetLastError());

        return FALSE;
      }

      //Allocate enough memory and recall    
      if (!auditString.Allocate(cchString))
      {
        if (m_dwAuditFlags & AUDIT_ERRORS)
          Audit(_T("CSSL::AuditData, %s, failed call to HeapAlloc, Error:%u\n"), pszTitle, GetLastError());

        return FALSE;
      }
      auditString.m_pData[0] = _T('\0');
      if (!CryptBinaryToString(pbyData, lSize, CRYPT_STRING_HEXASCIIADDR, auditString.m_pData, &cchString))
      {
        if (m_dwAuditFlags & AUDIT_ERRORS)
          Audit(_T("CSSL::AuditData, %s, failed call to CryptBinaryToString, Error:%u\n"), pszTitle, GetLastError());

        return FALSE;
      }
      pszString = auditString.m_pData;
    }

    //Audit the data via OutputDebugString
    OutputDebugString(pszTitle);
    OutputDebugString(_T("\n"));
    if (pszString != nullptr)
      OutputDebugString(pszString);
    else
      OutputDebugString(_T("<NULL>\n"));

    return TRUE;
  }

  unsigned long PendingReadSize() const
  {
      return m_lExtraReadData;
  }

protected:
//Methods
  virtual SECURITY_STATUS AllocateSendBuffer()
  {
    //Free the heap memory if already allocated
    if (m_WriteBuffer.m_pData != nullptr)
      m_WriteBuffer.Free();
    m_lWriteBufferLen = 0;

    //Qeury for the size details
    SECURITY_STATUS status = QueryAttribute(SECPKG_ATTR_STREAM_SIZES, &m_SecPkgSizes);
    if (status != SEC_E_OK)
      return status;

    //Allocate the buffer based on the size values returned
    ULONG lWriteBufferLen = m_SecPkgSizes.cbHeader + m_SecPkgSizes.cbMaximumMessage + m_SecPkgSizes.cbTrailer;
    if (!m_WriteBuffer.Allocate(lWriteBufferLen))
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)  
        Audit(_T("CSSL::AllocateSendBuffer, failed call to HeapAlloc, Error:%u\n"), GetLastError());

      return SEC_E_INSUFFICIENT_MEMORY;
    }
    m_lWriteBufferLen = lWriteBufferLen;

    return SEC_E_OK;
  }

  virtual SECURITY_STATUS ServerHandshakeLoop(_In_ unsigned long nContextRequest, _In_ BOOL bDoInitialRead)
  {
    //Validate our parameters
    ATLASSERT(m_lReadBufferLen != 0);
    ATLASSERT(m_ReadBuffer.m_pData != nullptr);
    ATLASSERT(m_pCachedCredentials != nullptr);

    //Loop around calling AcceptSecurityContext until we are finished
    unsigned long nInputDataRead = m_lExtraReadData;
    SecBuffer InBuffers[2];
    SECURITY_STATUS status = SEC_E_INCOMPLETE_MESSAGE;
    if (nInputDataRead || !bDoInitialRead)
      status = SEC_E_OK;
    do
    {
      //Read data from the client if we currently have an incomplete message or if we have just send some data to the cient because of a "SEC_I_CONTINUE_NEEDED"
      if ((status == SEC_E_INCOMPLETE_MESSAGE) || (status == SEC_I_CONTINUE_NEEDED))
      {
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ServerHandshakeLoop, Going to network to read more data\n"));

        ULONG lReceived = 0;
        SECURITY_STATUS status2 = ReceiveData(m_ReadBuffer.m_pData + nInputDataRead, m_lReadBufferLen - nInputDataRead, lReceived);
        if (status2 != SEC_E_OK)
        {
          if (m_dwAuditFlags & AUDIT_ERRORS)
            Audit(_T("CSSL::ServerHandshakeLoop, An error occured reading data from the client, Error:0x%08X\n"), status2);

          status = status2;
          break;
        }
        if (lReceived == 0)
        {
          if (m_dwAuditFlags & AUDIT_ERRORS)
            Audit(_T("CSSL::ServerHandshakeLoop, A graceful disconnect occured reading data from the client\n"));

          status = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_GRACEFUL_DISCONNECT);
          break;
        }

        if (m_dwAuditFlags & AUDIT_DATA)
          AuditData(_T("CSSL::ServerHandshakeLoop, received data from client"), m_ReadBuffer.m_pData + nInputDataRead, lReceived);

        nInputDataRead += lReceived;

        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ServerHandshakeLoop, Setting input data to %u\n"), nInputDataRead);
      }

      //Setup our input buffers
      InBuffers[0].BufferType = SECBUFFER_TOKEN;
      InBuffers[0].pvBuffer   = m_ReadBuffer.m_pData;
      InBuffers[0].cbBuffer   = nInputDataRead;
      InBuffers[1].BufferType = SECBUFFER_EMPTY;
      InBuffers[1].pvBuffer   = nullptr;
      InBuffers[1].cbBuffer   = 0;
      SecBufferDesc InBuffer;
      InBuffer.cBuffers       = 2;
      InBuffer.pBuffers       = InBuffers;
      InBuffer.ulVersion      = SECBUFFER_VERSION;

      //Setup our output buffers
      SecBuffer OutBuffers[1];
      OutBuffers[0].BufferType = SECBUFFER_TOKEN;
      OutBuffers[0].pvBuffer   = nullptr;
      OutBuffers[0].cbBuffer   = 0;
      SecBufferDesc OutBuffer;
      OutBuffer.cBuffers       = 1;
      OutBuffer.pBuffers       = OutBuffers;
      OutBuffer.ulVersion      = SECBUFFER_VERSION;

      //Call AcceptSecurityContext (again)
      if (m_dwAuditFlags & AUDIT_EVENTS)
        Audit(_T("CSSL::ServerHandshakeLoop, Calling AcceptSecurityContext with %u bytes of input data\n"), InBuffers[0].cbBuffer);
      unsigned long nContextRequestOut = 0;
      ATLASSERT(m_pCachedCredentials->ValidHandle());
      status = Accept(*m_pCachedCredentials, &InBuffer, nContextRequest, &OutBuffer, &nContextRequestOut);

      //Send any data to the server which SSPI provided to us if required
      if ((status == SEC_E_OK) || (status == SEC_I_CONTINUE_NEEDED) || (FAILED(status) && (nContextRequestOut & ISC_RET_EXTENDED_ERROR)))
      {  
        if (OutBuffers[0].cbBuffer != 0)
        {
          //Validate our parameters
          ATLASSUME(OutBuffers[0].pvBuffer != nullptr);

          //Do auditing if necessary
          if (m_dwAuditFlags & AUDIT_EVENTS)
            Audit(_T("CSSL::ServerHandshakeLoop, AcceptSecurityContext has provided %u bytes of data to send to client\n"), OutBuffers[0].cbBuffer);
          if (m_dwAuditFlags & AUDIT_DATA)
            AuditData(_T("CSSL::ServerHandshakeLoop, sending data to client"), static_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);
      
          SECURITY_STATUS status2 = SendData(static_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);
          if (status2 != SEC_E_OK)
          {
            if (m_dwAuditFlags & AUDIT_ERRORS)  
              Audit(_T("CSSL::ServerHandshakeLoop, An error occured sending data to the client, Error:0x%08X\n"), status2);

            status = status2;
          }
        }
      }

      //Free output buffer if required
      if (OutBuffers[0].pvBuffer != nullptr)
      {
        FreeContextBuffer(OutBuffers[0].pvBuffer);
        OutBuffers[0].pvBuffer = nullptr;
      }

      //Copy any data from the unprocessed extra bufer if provided back to the start of the read buffer
      if (InBuffers[1].BufferType == SECBUFFER_EXTRA)
      {
        memcpy_s(m_ReadBuffer.m_pData, m_lReadBufferLen, m_ReadBuffer.m_pData + (nInputDataRead - InBuffers[1].cbBuffer), InBuffers[1].cbBuffer);
        nInputDataRead = InBuffers[1].cbBuffer;

        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ServerHandshakeLoop, AcceptSecurityContext returned %u bytes of additional unprocessed data\n"), nInputDataRead);
        if (m_dwAuditFlags & AUDIT_DATA)
          AuditData(_T("CSSL::ServerHandshakeLoop, Additional unprocessed data"), m_ReadBuffer.m_pData, nInputDataRead);
      }
      else if (status != SEC_E_INCOMPLETE_MESSAGE)
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ServerHandshakeLoop, resetting nInputDataRead to 0 because input buffers indicate no additional unprocessed data, status:%08X\n"), status);

        nInputDataRead = 0;
      }
    }
    while ((status == SEC_I_CONTINUE_NEEDED) || (status == SEC_E_INCOMPLETE_MESSAGE));

    //Do validation of the client certificate  if required   
    if ((status == SEC_E_OK) && m_bVerifyClientCertificate)
    {
      CryptoWrappers::CCertificate remoteCertificate;
      status = QueryAttribute(SECPKG_ATTR_REMOTE_CERT_CONTEXT, &remoteCertificate.m_pCert);
      if (status != SEC_E_OK)
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ServerHandshakeLoop, Failed to obtain remote cert context, status:%08X\n"), status);
      }
      else
        status = VerifyClientCertificate(remoteCertificate);
    }

    if (status == SEC_E_OK)
    {
      //If the "extra" input buffer contains data, this is encrypted application protocol layer stuff. 
      //It needs to be saved and returned to the application layer so that it can be decrypt later using
      //the DecryptMessage method
      if (InBuffers[1].BufferType == SECBUFFER_EXTRA)
      {
        memcpy_s(m_ReadBuffer.m_pData, m_lReadBufferLen, m_ReadBuffer.m_pData + (nInputDataRead - InBuffers[1].cbBuffer), InBuffers[1].cbBuffer);
        m_lExtraReadData = InBuffers[1].cbBuffer;

        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ServerHandshakeLoop, AcceptSecurityContext has provided %u bytes of additional unprocessed data\n"), m_lExtraReadData);
        if (m_dwAuditFlags & AUDIT_DATA)
          AuditData(_T("CSSL::ServerHandshakeLoop, Additional unprocessed data"), m_ReadBuffer.m_pData, m_lExtraReadData);
      }
      else
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ServerHandshakeLoop, AcceptSecurityContext has provided no additional unprocessed data\n"));

        m_lExtraReadData = 0;
      }

      if (m_dwAuditFlags & AUDIT_EVENTS)
        Audit(_T("CSSL::ServerHandshakeLoop handshake was successful\n"));
    }
    else
    {
      if (m_dwAuditFlags & AUDIT_ERRORS)
        Audit(_T("CSSL::ServerHandshakeLoop failed, Error:0x%08X\n"), status);

      //Release the context if the function failed
      if (ValidHandle())
        Delete();
    }

    return status;
  }

  virtual SECURITY_STATUS ClientHandshakeLoop(_In_ LPCTSTR pszServerName, _In_ unsigned long nContextRequest, _In_ BOOL bDoInitialRead)
  {
    //Validate our parameters
    ATLASSERT(m_lReadBufferLen != 0);
    ATLASSERT(m_ReadBuffer.m_pData != nullptr);
    ATLASSERT(m_pCachedCredentials != nullptr);

    //Loop around calling InitializeSecurityContext until we are finished
    unsigned long nInputDataRead = m_lExtraReadData;
    SecBuffer InBuffers[2];
    SECURITY_STATUS status = SEC_E_INCOMPLETE_MESSAGE;
    if (nInputDataRead || !bDoInitialRead)
      status = SEC_E_OK;
    do
    {
      //Read data from the server if we currently have an incomplete message or if we have just send some data to the server because of a "SEC_I_CONTINUE_NEEDED"
      if ((status == SEC_E_INCOMPLETE_MESSAGE) || (status == SEC_I_CONTINUE_NEEDED))
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ClientHandshakeLoop, Going to network to read more data\n"));

        ULONG lReceived = 0;
        SECURITY_STATUS status2 = ReceiveData(m_ReadBuffer.m_pData + nInputDataRead, m_lReadBufferLen - nInputDataRead, lReceived);
        if (status2 != SEC_E_OK)
        {
          //Do auditing if necessary
          if (m_dwAuditFlags & AUDIT_ERRORS)
            Audit(_T("CSSL::ClientHandshakeLoop, An error occured reading data from the server, Error:0x%08X\n"), status2);

          status = status2;
          break;
        }
        if (lReceived == 0)
        {
          //Do auditing if necessary
          if (m_dwAuditFlags & AUDIT_ERRORS)
            Audit(_T("CSSL::ClientHandshakeLoop, A graceful disconnect occured reading data from the server\n"));

          status = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_GRACEFUL_DISCONNECT);
          break;
        }

        if (m_dwAuditFlags & AUDIT_DATA)
          AuditData(_T("CSSL::ClientHandshakeLoop, received data from server"), m_ReadBuffer.m_pData + nInputDataRead, lReceived);

        nInputDataRead += lReceived;
      }

      //Setup our input buffers
      InBuffers[0].pvBuffer   = m_ReadBuffer.m_pData;
      InBuffers[0].cbBuffer   = nInputDataRead;
      InBuffers[0].BufferType = SECBUFFER_TOKEN;
      InBuffers[1].pvBuffer   = nullptr;
      InBuffers[1].cbBuffer   = 0;
      InBuffers[1].BufferType = SECBUFFER_EMPTY;
      SecBufferDesc InBuffer;
      InBuffer.cBuffers       = 2;
      InBuffer.pBuffers       = InBuffers;
      InBuffer.ulVersion      = SECBUFFER_VERSION;

      //Setup our output buffers
      SecBuffer OutBuffers[1];
      OutBuffers[0].pvBuffer   = nullptr;
      OutBuffers[0].BufferType = SECBUFFER_TOKEN;
      OutBuffers[0].cbBuffer   = 0;
      SecBufferDesc OutBuffer;
      OutBuffer.cBuffers = 1;
      OutBuffer.pBuffers = OutBuffers;
      OutBuffer.ulVersion = SECBUFFER_VERSION;

      //Call InitializeSecurityContext (again)
      if (m_dwAuditFlags & AUDIT_EVENTS)
        Audit(_T("CSSL::ClientHandshakeLoop, Calling InitializeSecurityContext with %u bytes of input data\n"), InBuffers[0].cbBuffer);
      unsigned long nContextRequestOut = 0;
      ATLASSERT(m_pCachedCredentials->ValidHandle());
      status = Initialize(*m_pCachedCredentials, nullptr, nContextRequest, &InBuffer, &OutBuffer, &nContextRequestOut);

      //Send any data to the server which SSPI provided to us if required
      if ((status == SEC_E_OK) || (status == SEC_I_CONTINUE_NEEDED) || (FAILED(status) && (nContextRequestOut & ISC_RET_EXTENDED_ERROR)))
      {  
        if (OutBuffers[0].cbBuffer != 0)
        {
          //Validate our parameters
          ATLASSERT(OutBuffers[0].pvBuffer != nullptr);

          //Do auditing if necessary
          if (m_dwAuditFlags & AUDIT_EVENTS)
            Audit(_T("CSSL::ClientHandshakeLoop, InitializeSecurityContext has provided %u bytes of data to send to server\n"), OutBuffers[0].cbBuffer);
          if (m_dwAuditFlags & AUDIT_DATA)
            AuditData(_T("CSSL::ClientHandshakeLoop, sending data to server"), static_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);
      
          SECURITY_STATUS status2 = SendData(static_cast<const BYTE*>(OutBuffers[0].pvBuffer), OutBuffers[0].cbBuffer);
          if (status2 != SEC_E_OK)
          {
            if (m_dwAuditFlags & AUDIT_ERRORS)  
              Audit(_T("CSSL::ClientHandshakeLoop, An error occured sending data to the server, Error:0x%08X\n"), status2);

            status = status2;
          }
        }
      }

      //Free output buffer if required
      if (OutBuffers[0].pvBuffer != nullptr)
      {
        FreeContextBuffer(OutBuffers[0].pvBuffer);
        OutBuffers[0].pvBuffer = nullptr;
      }

      //Copy any data from the unprocessed extra bufer if provided back to the start of the read buffer
      if (InBuffers[1].BufferType == SECBUFFER_EXTRA)
      {
        memcpy_s(m_ReadBuffer.m_pData, m_lReadBufferLen, m_ReadBuffer.m_pData + (nInputDataRead - InBuffers[1].cbBuffer), InBuffers[1].cbBuffer);
        nInputDataRead = InBuffers[1].cbBuffer;

        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ClientHandshakeLoop, InitializeSecurityContext returned %u bytes of additional unprocessed data\n"), nInputDataRead);
        if (m_dwAuditFlags & AUDIT_DATA)
          AuditData(_T("CSSL::ClientHandshakeLoop, Additional unprocessed data"), m_ReadBuffer.m_pData, nInputDataRead);
      }
      else if (status != SEC_E_INCOMPLETE_MESSAGE)
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ClientHandshakeLoop, resetting nInputDataRead to 0 because input buffers indicate no additional unprocessed data, status:%08X\n"), status);

        nInputDataRead = 0;
      }
    }
    while ((status == SEC_I_CONTINUE_NEEDED) || (status == SEC_E_INCOMPLETE_MESSAGE) || (status == SEC_I_INCOMPLETE_CREDENTIALS));

    //Do custom validation of the server certificate if required via the virtual method "VerifyServerCertificate"
    if ((status == SEC_E_OK) && m_bVerifyServerCertificate)
    {
      //Convert server name to unicode if required
    #ifndef _UNICODE
      DWORD cchServerName = MultiByteToWideChar(CP_ACP, 0, pszServerName, -1, NULL, 0);
      ATL::CHeapPtr<wchar_t> unicodeServerName;
      if (!unicodeServerName.Allocate(cchServerName))
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_ERRORS)
          Audit(_T("CSSL::ClientHandshakeLoop, Failed to allocate memory to convert pszServerName parameter to Unicode, Error:%u\n"), GetLastError());

        status = SEC_E_INSUFFICIENT_MEMORY;
      }
      else
      {
        cchServerName = MultiByteToWideChar(CP_ACP, 0, pszServerName, -1, unicodeServerName.m_pData, cchServerName);
        if (cchServerName == 0)
        {
          //Do auditing if necessary
          if (m_dwAuditFlags & AUDIT_ERRORS)
            Audit(_T("CSSL::ClientHandshakeLoop, Failed to convert pszServerName parameter to Unicode, Error:%u\n"), GetLastError());

          status = SEC_E_WRONG_PRINCIPAL;
        }
      }
      LPCWSTR pwszUnicodeServerName = unicodeServerName.m_pData;
    #else
      LPCWSTR pwszUnicodeServerName = pszServerName;
    #endif //#ifndef _UNICODE

      if (status == SEC_E_OK)
      {
        CryptoWrappers::CCertificate remoteCertificate;
        status = QueryAttribute(SECPKG_ATTR_REMOTE_CERT_CONTEXT, &remoteCertificate.m_pCert);
        if (status != SEC_E_OK)
        {
          //Do auditing if necessary
          if (m_dwAuditFlags & AUDIT_EVENTS)
            Audit(_T("CSSL::ClientHandshakeLoop, Failed to obtain remote cert context, status:%08X\n"), status);
        }
        else
          status = VerifyServerCertificate(remoteCertificate, pwszUnicodeServerName, m_dwCertGetCertificateChainFlags, m_dwCertVerifyCertificateChainPolicyFlags);
      }
    }

    if (status == SEC_E_OK)
    {
      //Do auditing if necessary  
      if (m_dwAuditFlags & AUDIT_EVENTS)
        Audit(_T("CSSL::ClientHandshakeLoop handshake was successful\n"));

      //If the "extra" input buffer contains data, this is encrypted application protocol layer stuff. 
      //It needs to be saved and returned to the application layer so that it can be decrypted later using
      //the GetEncryptedMessage method
      if (InBuffers[1].BufferType == SECBUFFER_EXTRA)
      {
        memcpy_s(m_ReadBuffer.m_pData, m_lReadBufferLen, m_ReadBuffer.m_pData + (nInputDataRead - InBuffers[1].cbBuffer), InBuffers[1].cbBuffer);
        m_lExtraReadData = InBuffers[1].cbBuffer;

        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ClientHandshakeLoop, InitializeSecurityContext returned %u bytes of additional unprocessed data\n"), m_lExtraReadData);
        if (m_dwAuditFlags & AUDIT_DATA)
          AuditData(_T("CSSL::ClientHandshakeLoop, Additional unprocessed data"), m_ReadBuffer.m_pData, m_lExtraReadData);
      }
      else
      {
        m_lExtraReadData = 0;

        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_EVENTS)
          Audit(_T("CSSL::ClientHandshakeLoop, InitializeSecurityContext has provided no additional unprocessed data\n"));
      }
    }
    else
    {
      //Do auditing if necessary  
      if (m_dwAuditFlags & AUDIT_ERRORS)
        Audit(_T("CSSL::ClientHandshakeLoop failed, Error:0x%08X\n"), status);

      //Release the context if the function failed
      if (ValidHandle())
        Delete();
    }

    return status;
  }

  virtual SECURITY_STATUS VerifyClientCertificate(_In_ CryptoWrappers::CCertificate& /*clientCertificate*/)
  {
    //Note the default implementation does not do any real work. 
    //Derived classes are free to do their own custom validation. To enable VerifyClientCertificate
    //to be called at runtime you should use SetVerifyClientCertificate(TRUE)
    return SEC_E_OK;
  }

  virtual SECURITY_STATUS VerifyServerCertificate(_In_ CryptoWrappers::CCertificate& serverCertificate, _In_opt_ LPCWSTR pszServerName, _In_ DWORD dwCertGetCertificateChainFlags, _In_ DWORD dwCertVerifyCertificateChainPolicyFlags)
  {
    //Note the default implementation of VerifyServerCertificate does a comprehensive check of the server certificate.
    //Derived classes are free to do their own custom validation. Note that if you do want to do custom validation 
    //then you should probably turn of auto validation of the server certificate by Schannel by using the 
    //SCH_CRED_MANUAL_CRED_VALIDATION flag and then to enable VerifyServerCertificate to be called at runtime, 
    //you should use SetVerifyServerCertificate(TRUE)

    //Verify the server name
    if ((pszServerName == nullptr) || (wcslen(pszServerName) == 0))
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_EVENTS)
        Audit(_T("CSSL::VerifyServerCertificate, Server name is NULL or empty\n"));

      return SEC_E_WRONG_PRINCIPAL;
    }

    //Work with a non const local copy of pszServerName as required by SSL_EXTRA_CERT_CHAIN_POLICY_PARA::pwszServerName
    LPWSTR pszLocalServerName = _wcsdup(pszServerName);
    if (pszLocalServerName == nullptr)
    {
      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)
        Audit(_T("CSSL::VerifyServerCertificate, Failed to duplicate pszServerName parameter\n"));

      return SEC_E_INSUFFICIENT_MEMORY;
    }

    //Build the certificate chain
    CERT_CHAIN_PARA chainPara;
    memset(&chainPara, 0, sizeof(chainPara));
    chainPara.cbSize = sizeof(chainPara);
    chainPara.RequestedUsage.dwType = USAGE_MATCH_TYPE_OR;
    LPSTR rgszUsages[] = { szOID_PKIX_KP_SERVER_AUTH, szOID_SERVER_GATED_CRYPTO, szOID_SGC_NETSCAPE };
    DWORD cUsages = sizeof(rgszUsages) / sizeof(LPSTR);
    chainPara.RequestedUsage.Usage.cUsageIdentifier  = cUsages;
    chainPara.RequestedUsage.Usage.rgpszUsageIdentifier = rgszUsages;
    CryptoWrappers::CChain chain;
    if (!CertGetCertificateChain(nullptr, serverCertificate.m_pCert, nullptr, serverCertificate.m_pCert->hCertStore, &chainPara, dwCertGetCertificateChainFlags, nullptr, &chain.m_pChain))
    {
      SECURITY_STATUS status = GetLastError();

      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)  
        Audit(_T("CSSL::VerifyServerCertificate, An error occurred building the certificate chain, Error:0x%08X\n"), status);

      free(pszLocalServerName);
      return status;
    }

    //Validate the certificate chain
    SSL_EXTRA_CERT_CHAIN_POLICY_PARA extraPolicyPara;
    memset(&extraPolicyPara, 0, sizeof(extraPolicyPara));
    extraPolicyPara.cbStruct = sizeof(extraPolicyPara);
    extraPolicyPara.dwAuthType = AUTHTYPE_SERVER;
    extraPolicyPara.fdwChecks = dwCertVerifyCertificateChainPolicyFlags;
    extraPolicyPara.pwszServerName = pszLocalServerName;
    CERT_CHAIN_POLICY_PARA policyPara;
    memset(&policyPara, 0, sizeof(policyPara));
    policyPara.cbSize = sizeof(policyPara);
    policyPara.pvExtraPolicyPara = &extraPolicyPara;
    CERT_CHAIN_POLICY_STATUS policyStatus;
    memset(&policyStatus, 0, sizeof(policyStatus));
    policyStatus.cbSize = sizeof(policyStatus);
    if (!chain.VerifyPolicy(CERT_CHAIN_POLICY_SSL, &policyPara, &policyStatus))
    {
        SECURITY_STATUS status = GetLastError();

        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_ERRORS)  
          Audit(_T("CSSL::VerifyServerCertificate, An error occurred verifying the certificate chain, Error:0x%08X\n"), status);

        free(pszLocalServerName);
        return status;
    }

    //Clean up our resources used
    free(pszLocalServerName);

    //Check to see if the chain validated ok
    SECURITY_STATUS status = SEC_E_OK;
    if (policyStatus.dwError)
    {
      status = policyStatus.dwError;

      //Do auditing if necessary
      if (m_dwAuditFlags & AUDIT_ERRORS)  
        Audit(_T("CSSL::VerifyServerCertificate, certificate validation failed, Error:0x%08X\n"), status);
    }

    //Check all the certificates in the chain for revocation if required
    if (m_bCheckServerCertificateRevocation)
    {
      ATL::CHeapPtr<PCERT_CONTEXT> certsBuffer;
      if (!certsBuffer.Allocate(chain.m_pChain->cChain))
      {
        //Do auditing if necessary
        if (m_dwAuditFlags & AUDIT_ERRORS)  
          Audit(_T("CSSL::VerifyServerCertificate, Failed to allocate memory required for certificate revocation check\n"));

        status = SEC_E_INSUFFICIENT_MEMORY;
      }
      else
      {
        for (DWORD i=0; i<chain.m_pChain->cChain; i++)
          certsBuffer.m_pData[i] = const_cast<PCERT_CONTEXT>(chain.m_pChain->rgpChain[i]->rgpElement[0]->pCertContext);
        CERT_REVOCATION_STATUS revStat;
        revStat.cbSize = sizeof(revStat);
        if (!CertVerifyRevocation(X509_ASN_ENCODING, CERT_CONTEXT_REVOCATION_TYPE, chain.m_pChain->cChain, reinterpret_cast<PVOID*>(certsBuffer.m_pData), CERT_VERIFY_REV_CHAIN_FLAG, nullptr, &revStat))
        {
          //Do auditing if necessary
          if (m_dwAuditFlags & AUDIT_ERRORS)  
            Audit(_T("CSSL::VerifyServerCertificate, Failed to check revocation of certificate, Error:0x%08X\n"), revStat.dwError);

          status = revStat.dwError;
        }
      }
    }

    return status;
  }

//Member variables
  SECURITY_STATUS              m_LastStatus;
  unsigned long                m_lReadBufferLen;
  ATL::CHeapPtr<BYTE>          m_ReadBuffer;
  unsigned long                m_lWriteBufferLen;
  unsigned long                m_lExtraReadData;
  ATL::CHeapPtr<BYTE>          m_WriteBuffer;
  SecPkgContext_StreamSizes    m_SecPkgSizes;
  DWORD                        m_dwAuditFlags;
  BOOL                         m_bVerifyServerCertificate;
  BOOL                         m_bCheckServerCertificateRevocation;
  BOOL                         m_bVerifyClientCertificate;
  DWORD                        m_dwCertVerifyCertificateChainPolicyFlags;
  DWORD                        m_dwCertGetCertificateChainFlags;
  CCachedCredentials*          m_pCachedCredentials;
};


//The class which provides a socket based implementation of SSL using SSPI
class CSocket : public CSSL
{
public:
//Constructors / Destructors
  CSocket() : m_hSocket(INVALID_SOCKET),
              m_dwReadTimeout(5000),
              m_dwWriteTimeout(5000)
  {
  }

//Virtual methods
  virtual SECURITY_STATUS SendData(_In_reads_bytes_(lSize) const BYTE* pbyData, _In_ ULONG lSize)
  {
    //Validate our parameters
    ATLASSERT(m_hSocket != INVALID_SOCKET);

    //Loop around sending all the data down the socket
    ULONG nSent = 0;
    while (nSent != lSize) 
    {
      //Check for writability on the socket before we try to send
      int nWritable = IsWritable(m_hSocket, m_dwWriteTimeout);
      if (nWritable == SOCKET_ERROR)
        return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSAGetLastError());
      else if (nWritable == 0)
        return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_TIMEOUT);

      //Send the rest of the data
      int nSentThisTime = send(m_hSocket, reinterpret_cast<const char*>(pbyData + nSent), lSize - nSent, 0);
      if (nSentThisTime == SOCKET_ERROR) 
        return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSAGetLastError());

      //Prepare for the next loop
      nSent += nSentThisTime;
    }

    return SEC_E_OK;
  }

  virtual SECURITY_STATUS ReceiveData(_Out_writes_bytes_to_(lSize, lReceived) BYTE* pbyData, _In_ ULONG lSize, _Out_ ULONG& lReceived)
  {
    //Validate our parameters
    ATLASSERT(m_hSocket != INVALID_SOCKET);

    //Initialize the output parameter
    lReceived = 0;

    //Check the socket for readability
    int nReadable = IsReadible(m_hSocket, m_dwReadTimeout);
    if (nReadable == SOCKET_ERROR)
      return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSAGetLastError());
    else if (nReadable == 0)
      return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_TIMEOUT);

    //Do the actual receive
    lReceived = recv(m_hSocket, reinterpret_cast<char*>(pbyData), lSize, 0);
    if (lReceived == SOCKET_ERROR) 
      return MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, WSAGetLastError());

    return SEC_E_OK;
  }

//Non virtual methods
  void Attach(_In_ SOCKET hSocket)
  {
    m_hSocket = hSocket;
  }

  SOCKET Detach()
  {
    SOCKET hSocket = m_hSocket;
    m_hSocket = INVALID_SOCKET;
    return hSocket;
  }

  static int IsReadible(_In_ SOCKET hSocket, _In_ DWORD dwTimeout)
  {
    //Check the socket for readability
    timeval timeout;
    timeout.tv_sec = dwTimeout / 1000;
    timeout.tv_usec = (dwTimeout % 1000) * 1000;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(hSocket, &fds);
    return select(0, &fds, NULL, NULL, &timeout);
  }

  static int IsWritable(_In_ SOCKET hSocket, _In_ DWORD dwTimeout)
  {
    //Check the socket for writability
    timeval timeout;
    timeout.tv_sec = dwTimeout / 1000;
    timeout.tv_usec = (dwTimeout % 1000) * 1000;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(hSocket, &fds);
    return select(0, NULL, &fds, NULL, &timeout);
  }

  void SetReadTimeout(_In_ DWORD dwReadTimeout)
  {
    m_dwReadTimeout = dwReadTimeout;
  }

  DWORD GetReadTimeout() const
  {
    return m_dwReadTimeout;
  }

  void SetWriteTimeout(_In_ DWORD dwWriteTimeout)
  {
    m_dwWriteTimeout = dwWriteTimeout;
  }

  DWORD GetWriteTimeout() const
  {
    return m_dwWriteTimeout;
  }

  SOCKET GetSocket()
  {
    return m_hSocket;
  }

protected:
//Member variables
  SOCKET m_hSocket;
  DWORD  m_dwReadTimeout;
  DWORD  m_dwWriteTimeout;
};
}; //namespace SSLWrappers

#endif //#ifndef __SSLWRAPPERS_H__
