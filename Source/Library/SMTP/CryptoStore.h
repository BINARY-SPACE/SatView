/*
Module : CryptoStore.h
Purpose: Defines the interface for a C++ wrapper class for a CryptoAPI HCERTSTORE
History: PJN / 01-08-2014 1. Initial public release

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

#ifndef __CRYPTOSTORE_H__
#define __CRYPTOSTORE_H__

#include "CryptoCertificate.h"
#include "CryptoCRL.h"
#include "CryptoCTL.h"
#include "CryptoChain.h"


////////////////////////// Classes ////////////////////////////////////////////

namespace CryptoWrappers
{


//Encapsulates a CryptoAPI HCERTSTORE
class CStore
{
public:
//Constructors / Destructors
  CStore() : m_hStore(nullptr)
  {
  }
  
  CStore(_In_ const CStore& store) : m_hStore(nullptr)
  {
    if (!store.Duplicate(*this))
      m_hStore = nullptr;
  }
  
  CStore(_In_ CStore&& store) : m_hStore(nullptr)
  {
    Attach(store.Detach());
  }

  explicit CStore(_In_opt_ HCERTSTORE hStore) : m_hStore(hStore)
  {
  }

  ~CStore()
  {
    if (m_hStore != nullptr)
      Close();
  }
  
//Methods
  CStore& operator=(_In_ const CStore& store)
  {
    if (this != &store)
    {
      if (m_hStore != nullptr)
        Close();
      if (!store.Duplicate(*this))
        m_hStore = nullptr;
    }
    
    return *this;
  }

  CStore& operator=(_In_ CStore&& store)
  {
    if (m_hStore != nullptr)
      Close();
    Attach(store.Detach());
    
    return *this;
  }

  HCERTSTORE Handle() const
  {
    return m_hStore;
  }

  void Attach(_In_opt_ HCERTSTORE hStore)
  {
    //Validate our parameters
    ATLASSERT(m_hStore == nullptr);
    
    m_hStore = hStore;
  }

  HCERTSTORE Detach()
  {
    HCERTSTORE hStore = m_hStore;
    m_hStore = nullptr;
    return hStore;
  }

  _Must_inspect_result_
  BOOL Open(_In_ LPCSTR lpszStoreProvider, _In_ DWORD dwEncodingType, _In_ DWORD dwFlags, _In_opt_ const void* pvPara)
  {
    //Validate our parameters
    ATLASSERT(m_hStore == nullptr);

    m_hStore = CertOpenStore(lpszStoreProvider, dwEncodingType, NULL, dwFlags, pvPara);
    return (m_hStore != nullptr);
  }

  _Must_inspect_result_
  BOOL OpenSystemStore(_In_ LPCTSTR szSubsystemProtocol)
  {
    //Validate our parameters
    ATLASSERT(m_hStore == nullptr);

    m_hStore = CertOpenSystemStore(NULL, szSubsystemProtocol);
    return (m_hStore != nullptr);
  }

  _Success_(return != FALSE)
  BOOL Close(_In_ DWORD dwFlags = 0)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    BOOL bResult = CertCloseStore(m_hStore, dwFlags);
    m_hStore = nullptr;
    return bResult;
  }

  _Success_(return != FALSE)
  BOOL Control(_In_ DWORD dwFlags, _In_ DWORD dwCtrlType, _In_opt_ void const* pvCtrlPara)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    return CertControlStore(m_hStore, dwFlags, dwCtrlType, pvCtrlPara);
  }

  _Success_(return != FALSE)
  BOOL Duplicate(_Inout_ CStore& store) const
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);
    ATLASSERT(store.m_hStore == nullptr);

    store.m_hStore = CertDuplicateStore(m_hStore);
    return (store.m_hStore != nullptr);
  }

  _Success_(return != FALSE)
  BOOL AddStoreToCollection(_In_opt_ HCERTSTORE hSiblingStore, _In_ DWORD dwUpdateFlags, _In_ DWORD dwPriority)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    return CertAddStoreToCollection(m_hStore, hSiblingStore, dwUpdateFlags, dwPriority);
  }

  void RemoveStoreToCollection(_In_ const CStore& siblingStore)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CertRemoveStoreFromCollection(m_hStore, siblingStore.m_hStore);
  }

  _Success_(return != FALSE)
  BOOL Save(_In_ DWORD dwEncodingType, _In_ DWORD dwSaveAs, _In_ DWORD dwSaveTo, _Inout_ void* pvSaveToPara)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    return CertSaveStore(m_hStore, dwEncodingType, dwSaveAs, dwSaveTo, pvSaveToPara, 0);
  }

  _Success_(return != FALSE)
  BOOL SetProperty(_In_ DWORD dwPropId, _In_opt_ const void* pvData)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    return CertSetStoreProperty(m_hStore, dwPropId, 0, pvData);
  }

  _Success_(return != FALSE)
  BOOL GetProperty(_In_ DWORD dwPropId, _Out_writes_bytes_to_opt_(*pcbData, *pcbData) void* pvData, _Inout_ DWORD* pcbData)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    return CertGetStoreProperty(m_hStore, dwPropId, pvData, pcbData);
  }

  _Success_(return != FALSE)
  BOOL AddSerializedElement(_In_reads_bytes_(cbElement) const BYTE *pbElement, _In_ DWORD cbElement, _In_ DWORD dwAddDisposition, _In_ DWORD dwContextTypeFlags, _Out_opt_ DWORD* pdwContextType, _Outptr_opt_ const void** ppvContext)
  {
    return CertAddSerializedElementToStore(m_hStore, pbElement, cbElement, dwAddDisposition, 0, dwContextTypeFlags, pdwContextType, ppvContext);
  }

  _Success_(return != FALSE)
  BOOL AddCertifcate(_In_ CCertificate& cert, _In_ DWORD dwAddDisposition, _Inout_opt_ CCertificate* pStoreCertificate)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);
    if (pStoreCertificate != nullptr)
      ATLASSERT(pStoreCertificate->m_pCert == nullptr);

    return CertAddCertificateContextToStore(m_hStore, cert.m_pCert, dwAddDisposition, pStoreCertificate ? &pStoreCertificate->m_pCert : nullptr);
  }

  _Success_(return != FALSE)
  BOOL AddCRL(_In_ CCRL& crl, _In_ DWORD dwAddDisposition, _Inout_opt_ CCRL* pStoreCRL)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);
    if (pStoreCRL != nullptr)
      ATLASSERT(pStoreCRL->m_pCRL == nullptr);

    return CertAddCRLContextToStore(m_hStore, crl.m_pCRL, dwAddDisposition, pStoreCRL ? &pStoreCRL->m_pCRL : nullptr);
  }

  _Success_(return != FALSE)
  BOOL AddCTL(_In_ CCTL& ctl, _In_ DWORD dwAddDisposition, _Inout_opt_ CCTL* pStoreCTL)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);
    if (pStoreCTL != nullptr)
      ATLASSERT(pStoreCTL->m_pCTL == nullptr);

    return CertAddCTLContextToStore(m_hStore, ctl.m_pCTL, dwAddDisposition, pStoreCTL ? &pStoreCTL->m_pCTL : nullptr);
  }

  CCertificate SelectCertificate(_In_opt_ HWND hwnd, _In_opt_ LPCWSTR pwszTitle, _In_opt_ LPCWSTR pwszDisplayString, _In_ DWORD dwDontUseColumn)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CCertificate certificate(CryptUIDlgSelectCertificateFromStore(m_hStore, hwnd, pwszTitle, pwszDisplayString, dwDontUseColumn, 0, nullptr));
    return certificate;
  }

  CCertificate EnumCertificates(_In_ CCertificate& prevCertificate)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CCertificate certificate(CertEnumCertificatesInStore(m_hStore, prevCertificate.m_pCert));
    prevCertificate.m_pCert = nullptr; //Required because CertEnumCertificatesInStore auto frees any non nullptr pPrevCertContext parameter
    return certificate;
  }

  CCRL EnumCRLs(_In_ CCRL& prevCRL)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CCRL crl(CertEnumCRLsInStore(m_hStore, prevCRL.m_pCRL));
    prevCRL.m_pCRL = nullptr; //Required because CertEnumCRLsInStore auto frees any non nullptr pPrevCrlContext parameter
    return crl;
  }

  CCTL EnumCTLs(_In_ CCTL& prevCTL)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CCTL crl(CertEnumCTLsInStore(m_hStore, prevCTL.m_pCTL));
    prevCTL.m_pCTL = nullptr; //Required because CertEnumCTLsInStore auto frees any non nullptr pPrevCtlContext parameter
    return crl;
  }

  CCertificate FindCertificate(_In_ DWORD dwCertEncodingType, _In_ DWORD dwFindFlags, _In_ DWORD dwFindType, _In_opt_ const void* pvFindPara, _In_ CCertificate& prevCertificate)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CCertificate certificate(CertFindCertificateInStore(m_hStore, dwCertEncodingType, dwFindFlags, dwFindType, pvFindPara, prevCertificate.m_pCert));
    prevCertificate.m_pCert = nullptr; //Required because CertFindCertificateInStore auto frees any non nullptr pPrevCertContext parameter
    return certificate;
  }

  CCRL FindCRL(_In_ DWORD dwCertEncodingType, _In_ DWORD dwFindFlags, _In_ DWORD dwFindType, _In_opt_ const void* pvFindPara, _In_ CCRL& prevCRL)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CCRL crl(CertFindCRLInStore(m_hStore, dwCertEncodingType, dwFindFlags, dwFindType, pvFindPara, prevCRL.m_pCRL));
    prevCRL.m_pCRL = nullptr; //Required because CertFindCRLInStore auto frees any non nullptr pPrevCertContext parameter
    return crl;
  }

  CCTL FindCTL(_In_ DWORD dwMsgAndCertEncodingType, _In_ DWORD dwFindFlags, _In_ DWORD dwFindType, _In_opt_ const void* pvFindPara, _In_ CCTL& prevCTL)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CCTL ctl(CertFindCTLInStore(m_hStore, dwMsgAndCertEncodingType, dwFindFlags, dwFindType, pvFindPara, prevCTL.m_pCTL));
    prevCTL.m_pCTL = nullptr; //Required because CertFindCRLInStore auto frees any non nullptr pPrevCertContext parameter
    return ctl;
  }

  CChain FindChain(_In_ DWORD dwCertEncodingType, _In_ DWORD dwFindFlags, _In_ DWORD dwFindType, _In_opt_ const void* pvFindPara, _In_  CChain& prevChain)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CChain chain(CertFindChainInStore(m_hStore, dwCertEncodingType, dwFindFlags, dwFindType, pvFindPara, prevChain.m_pChain));
    prevChain.m_pChain = nullptr; //Required because CertFindChainInStore auto frees any non nullptr pPrevCertContext parameter
    return chain;
  }

  _Success_(return != FALSE)
  BOOL AddCertificateLink(_In_ CCertificate& certificate, _In_ DWORD dwAddDisposition, _Inout_opt_ CCertificate* pStoreCertificate)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);
    if (pStoreCertificate != nullptr)
      ATLASSERT(pStoreCertificate->m_pCert == nullptr);

    return CertAddCertificateLinkToStore(m_hStore, certificate.m_pCert, dwAddDisposition, pStoreCertificate ? &pStoreCertificate->m_pCert : nullptr);
  }

  _Success_(return != FALSE)
  BOOL AddCRLLink(_In_ CCRL& crl, _In_ DWORD dwAddDisposition, _Inout_opt_ CCRL* pStoreCRL)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);
    if (pStoreCRL != nullptr)
      ATLASSERT(pStoreCRL->m_pCRL == nullptr);

    return CertAddCRLLinkToStore(m_hStore, crl.m_pCRL, dwAddDisposition, pStoreCRL ? &pStoreCRL->m_pCRL : nullptr);
  }

  _Success_(return != FALSE)
  BOOL AddCTLLink(_In_ CCTL& ctl, _In_ DWORD dwAddDisposition, _Inout_opt_ CCTL* pStoreCTL)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);
    if (pStoreCTL != nullptr)
      ATLASSERT(pStoreCTL->m_pCTL == nullptr);

    return CertAddCTLLinkToStore(m_hStore, ctl.m_pCTL, dwAddDisposition, pStoreCTL ? &pStoreCTL->m_pCTL : nullptr);
  }

  _Success_(return != FALSE)
  BOOL AddEncodedCertificate(_In_ DWORD dwCertEncodingType, _In_reads_bytes_(cbCertEncoded) const BYTE* pbCertEncoded, _In_ DWORD cbCertEncoded, _In_ DWORD dwAddDisposition, _Inout_opt_ CCertificate* pCertificate)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);
    if (pCertificate != nullptr)
      ATLASSERT(pCertificate->m_pCert == nullptr);

    return CertAddEncodedCertificateToStore(m_hStore, dwCertEncodingType, pbCertEncoded, cbCertEncoded, dwAddDisposition, (pCertificate != NULL) ? &pCertificate->m_pCert : nullptr);
  }

  _Success_(return != FALSE)
  BOOL AddEncodedCRL(_In_ DWORD dwCertEncodingType, _In_reads_bytes_(cbCrlEncoded) const BYTE* pbCrlEncoded, _In_ DWORD cbCrlEncoded, _In_ DWORD dwAddDisposition, _Inout_opt_ CCRL* pCRL)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);
    if (pCRL != nullptr)
      ATLASSERT(pCRL->m_pCRL == nullptr);

    return CertAddEncodedCRLToStore(m_hStore, dwCertEncodingType, pbCrlEncoded, cbCrlEncoded, dwAddDisposition, (pCRL != NULL) ? &pCRL->m_pCRL : nullptr);
  }

  _Success_(return != FALSE)
  BOOL AddEncodedCTL(_In_ DWORD dwMsgAndCertEncodingType, _In_reads_bytes_(cbCtlEncoded) const BYTE* pbCtlEncoded, _In_ DWORD cbCtlEncoded, _In_ DWORD dwAddDisposition, _Inout_opt_ CCTL* pCTL)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);
    if (pCTL != nullptr)
      ATLASSERT(pCTL->m_pCTL == nullptr);

    return CertAddEncodedCTLToStore(m_hStore, dwMsgAndCertEncodingType, pbCtlEncoded, cbCtlEncoded, dwAddDisposition, (pCTL != NULL) ? &pCTL->m_pCTL : nullptr);
  }

  CCertificate GetIssuerCertificate(_In_ CCertificate& subjectContext, _In_ CCertificate& prevIssuerContext, _Inout_ DWORD* pdwFlags)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CCertificate certificate(CertGetIssuerCertificateFromStore(m_hStore, subjectContext.Handle(), prevIssuerContext.m_pCert, pdwFlags));
    prevIssuerContext.m_pCert = nullptr; //Required because CertGetIssuerCertificateFromStore auto frees any non nullptr pPrevCertContext parameter
    return certificate;
  }

  CCertificate GetSubjectCertificate(_In_ DWORD dwCertEncodingType, _In_ PCERT_INFO pCertId)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CCertificate certificate(CertGetSubjectCertificateFromStore(m_hStore, dwCertEncodingType, pCertId));
    return certificate;
  }

#if (NTDDI_VERSION >= NTDDI_WIN7)
  _Success_(return != FALSE)
  BOOL SelectCertificateChains(_In_opt_ LPCGUID pSelectionContext, _In_ DWORD dwFlags, _In_opt_ PCCERT_SELECT_CHAIN_PARA pChainParameters, _In_ DWORD cCriteria,
                               _In_opt_ PCCERT_SELECT_CRITERIA rgpCriteria, _Out_ PDWORD pcSelection, _Out_ PCCERT_CHAIN_CONTEXT** pprgpSelection)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    return CertSelectCertificateChains(pSelectionContext, dwFlags, pChainParameters, cCriteria, rgpCriteria, m_hStore, pcSelection, pprgpSelection);
  }
#endif //#if (NTDDI_VERSION >= NTDDI_WIN7)

  CCRL GetCRL(_In_ CCertificate& issuer, _In_ CCRL& prevCRL, _Inout_ DWORD* pdwFlags)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    CCRL crl;
    crl.m_pCRL = CertGetCRLFromStore(m_hStore, issuer.Handle(), prevCRL.Handle(), pdwFlags);
    return crl;
  }

  _Success_(return != FALSE)
  BOOL PFXExport(_Inout_ CRYPT_DATA_BLOB* pPFX, _In_ LPCWSTR szPassword, _In_opt_ void* pvPara, _In_ DWORD dwFlags)
  {
    //Validate our parameters
    ATLASSERT(m_hStore != nullptr);

    #pragma warning(suppress: 6387)
    return PFXExportCertStoreEx(m_hStore, pPFX, szPassword, pvPara, dwFlags);
  }

  _Success_(return != FALSE)
  BOOL PFXImport(_In_ CRYPT_DATA_BLOB* pPFX, _In_ LPCWSTR szPassword, _In_ DWORD dwFlags)
  {
    //Validate our parameters
    ATLASSERT(m_hStore == nullptr);

    m_hStore = PFXImportCertStore(pPFX, szPassword, dwFlags);
    return (m_hStore != nullptr);
  }

//Member variables
  HCERTSTORE m_hStore;
};
}; //namespace CryptoWrappers

#endif //#ifndef __CRYPTOSTORE_H__
