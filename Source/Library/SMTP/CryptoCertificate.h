/*
Module : CryptoCertificate.h
Purpose: Defines the interface for a C++ wrapper class for a CryptoAPI PCCERT_CONTEXT
History: PJN / 01-08-2014 1. Initial public release
         PJN / 21-09-2014 1. Added missing include of CryptoHelpers.h
         PJN / 01-11-2015 1. Updated code to clean compile on VC 2015

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

#ifndef __CRYPTOCERTIFICATE_H__
#define __CRYPTOCERTIFICATE_H__

#include "CryptoHelpers.h"


////////////////////////// Classes ////////////////////////////////////////////

namespace CryptoWrappers
{
//Encapsulates a CryptoAPI PCCERT_CONTEXT
class CCertificate
{
public:
//Constructors / Destructors
  CCertificate() : m_pCert(nullptr)
  {
  }
  
  CCertificate(_In_ CCertificate&& cert) : m_pCert(nullptr)
  {
    Attach(cert.Detach());
  }

  CCertificate(_In_ const CCertificate& cert) : m_pCert(nullptr)
  {
    if (!cert.Duplicate(*this))
      m_pCert = nullptr;
  }
  
  explicit CCertificate(_In_opt_ PCCERT_CONTEXT pCertificate) : m_pCert(pCertificate)
  {
  }

  ~CCertificate()
  {
    if (m_pCert != nullptr)
      Free();
  }
  
//Methods
  CCertificate& operator=(_In_ const CCertificate& certificate)
  {
    if (this != &certificate)
    {
      if (m_pCert != nullptr)
        Free();
      if (!certificate.Duplicate(*this))
        m_pCert = nullptr;
    }
    
    return *this;
  }

  CCertificate& operator=(_In_ CCertificate&& certificate)
  {
    if (m_pCert != nullptr)
      Free();
    Attach(certificate.Detach());
    
    return *this;
  }

  PCCERT_CONTEXT Handle() const
  {
    return m_pCert;
  }

  void Attach(_In_opt_ PCCERT_CONTEXT pCertificate)
  {
    //Validate our parameters
    ATLASSERT(m_pCert == nullptr);
    
    m_pCert = pCertificate;
  }

  PCCERT_CONTEXT Detach()
  {
    PCCERT_CONTEXT pCertificate = m_pCert;
    m_pCert = nullptr;
    return pCertificate;
  }

  _Success_(return != FALSE)
  BOOL Create(_In_ DWORD dwCertEncodingType, _In_reads_bytes_(cbCertEncoded) const BYTE* pbCertEncoded, _In_ DWORD cbCertEncoded)
  {
    //Validate our parameters
    ATLASSERT(m_pCert == nullptr);
    
    m_pCert = CertCreateCertificateContext(dwCertEncodingType, pbCertEncoded, cbCertEncoded);
    return (m_pCert != nullptr);
  }

  _Success_(return != FALSE)
  BOOL Free()
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    BOOL bResult = CertFreeCertificateContext(m_pCert);
    m_pCert = nullptr;
    return bResult;
  }

  _Success_(return != FALSE)
  BOOL Duplicate(_Inout_ CCertificate& certificate) const
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);
    ATLASSERT(certificate.m_pCert == nullptr);

    certificate.m_pCert = CertDuplicateCertificateContext(m_pCert);
    return (certificate.m_pCert != nullptr);
  }

  _Success_(return != FALSE)
  BOOL DeleteFromStore()
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);
    
    BOOL bResult = CertDeleteCertificateFromStore(m_pCert);
    m_pCert = nullptr; //Required because CertDeleteCertificateFromStore frees the pPrevCertContext parameter
    return bResult;
  }

  _Success_(return != FALSE)
  BOOL RetrieveLogoOrBiometricInfo(_In_ LPCSTR lpszLogoOrBiometricType, _In_ DWORD dwRetrievalFlags, _In_ DWORD dwTimeout, 
                                   _Outptr_result_bytebuffer_(*pcbData) BYTE** ppbData, _Out_ DWORD* pcbData, _Outptr_opt_result_maybenull_ LPWSTR* ppwszMimeType)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertRetrieveLogoOrBiometricInfo(m_pCert, lpszLogoOrBiometricType, dwRetrievalFlags, dwTimeout, 0, nullptr, ppbData, pcbData, ppwszMimeType);
  }

  _Success_(return != FALSE)
  BOOL SerializStoreElement(_Out_writes_bytes_to_opt_(*pcbElement, *pcbElement) BYTE* pbElement, _Inout_ DWORD* pcbElement)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertSerializeCertificateStoreElement(m_pCert, 0, pbElement, pcbElement);
  }

  _Success_(return != FALSE)
  BOOL DlgView(_In_opt_ HWND hwnd, _In_opt_ LPCWSTR pwszTitle)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CryptUIDlgViewContext(CERT_STORE_CERTIFICATE_CONTEXT, m_pCert, hwnd, pwszTitle, 0, nullptr);
  }

  DWORD EnumProperties(_In_ DWORD dwPropId)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertEnumCertificateContextProperties(m_pCert, dwPropId);
  }

  _Success_(return != FALSE)
  BOOL GetProperty(_In_ DWORD dwPropId, _Out_writes_bytes_to_opt_(*pcbData, *pcbData) void* pvData, _Inout_ DWORD* pcbData)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertGetCertificateContextProperty(m_pCert, dwPropId, pvData, pcbData);
  }

  _Success_(return != FALSE)
  BOOL SetProperty(_In_ DWORD dwPropId, _In_ DWORD dwFlags, _In_opt_ const void* pvData)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertSetCertificateContextProperty(m_pCert, dwPropId, dwFlags, pvData);
  }

  DWORD GetNameString(_In_ DWORD dwType, _In_ DWORD dwFlags, _In_opt_ void* pvTypePara, _Out_writes_to_opt_(cchNameString, return) LPTSTR pszNameString, _In_ DWORD cchNameString)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertGetNameString(m_pCert, dwType, dwFlags, pvTypePara, pszNameString, cchNameString);
  }

  _Success_(return != 0) 
  DWORD GetNameString(_In_ DWORD dwType, _In_ DWORD dwFlags, _In_opt_ void* pvTypePara, _Out_ String& sName)
  {
    //First call to get the length of the buffer to allocate
    DWORD dwNameLen = GetNameString(dwType, dwFlags, pvTypePara, nullptr, 0);
    if (dwNameLen == 0)
      return dwNameLen;

    //Allocate enough memory and recall      
    std::vector<TCHAR> sTemp;
    sTemp.resize(dwNameLen);

    //Recall
    dwNameLen = GetNameString(dwType, dwFlags, pvTypePara, &(sTemp[0]), dwNameLen);
    if (dwNameLen)
      sName = &(sTemp[0]);
    return dwNameLen;
  }

  _Success_(return != FALSE)
  BOOL AddEnhancedKeyUsageIdentifier(_In_ LPCSTR pszUsageIdentifier)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertAddEnhancedKeyUsageIdentifier(m_pCert, pszUsageIdentifier);
  }

  _Success_(return != FALSE)
  BOOL RemoveEnhancedKeyUsageIdentifier(_In_ LPCSTR pszUsageIdentifier)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertRemoveEnhancedKeyUsageIdentifier(m_pCert, pszUsageIdentifier);
  }

  _Success_(return != FALSE)
  BOOL SetEnhancedKeyUsageIdentifier(_In_ PCERT_ENHKEY_USAGE pUsage)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertSetEnhancedKeyUsage(m_pCert, pUsage);
  }

  _Success_(return != FALSE)
  BOOL GetEnhancedKeyUsage(_In_ DWORD dwFlags, _Out_writes_bytes_to_opt_(*pcbUsage, *pcbUsage) PCERT_ENHKEY_USAGE pUsage, _Inout_ DWORD* pcbUsage)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertGetEnhancedKeyUsage(m_pCert, dwFlags, pUsage, pcbUsage);
  }

  _Success_(return != FALSE)
  BOOL CreateCTLEntry(_In_ DWORD cOptAttr, _In_ PCRYPT_ATTRIBUTE rgOptAttr, _In_ DWORD dwFlags, _Out_ PCTL_ENTRY pCtlEntry, _Inout_ DWORD* pcbCtlEntry)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertCreateCTLEntryFromCertificateContextProperties(m_pCert, cOptAttr, rgOptAttr, dwFlags, nullptr, pCtlEntry, pcbCtlEntry);
  }

  _Success_(return != FALSE)
  BOOL IsValidCRL(_In_ PCCRL_CONTEXT pCRL)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertIsValidCRLForCertificate(m_pCert, pCRL, 0, nullptr);
  }

  _Success_(return != FALSE)
  BOOL SetPropertiesFromCTLEntry(_In_ PCTL_ENTRY pCtlEntry, _In_ DWORD dwFlags)
  {
    //Validate our parameters
    ATLASSERT(m_pCert != nullptr);

    return CertSetCertificateContextPropertiesFromCTLEntry(m_pCert, pCtlEntry, dwFlags);
  }

//Member variables
  PCCERT_CONTEXT m_pCert;

  friend class CStore;
};
}; //namespace CryptoWrappers

#endif //#ifndef __CRYPTOCERTIFICATE_H__
