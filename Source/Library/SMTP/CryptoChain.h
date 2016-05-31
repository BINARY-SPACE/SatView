/*
Module : CryptoChain.h
Purpose: Defines the interface for a C++ wrapper class for a CryptoAPI PCCERT_CHAIN_CONTEXT
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

#ifndef __CRYPTOCHAIN_H__
#define __CRYPTOCHAIN_H__


////////////////////////// Classes ////////////////////////////////////////////

namespace CryptoWrappers
{
//Encapsulates a CryptoAPI PCERT_CHAIN_CONTEXT
class CChain
{
public:
//Constructors / Destructors
  CChain() : m_pChain(nullptr)
  {
  }
  
  CChain(_In_ const CChain& chain) : m_pChain(nullptr)
  {
    if (!chain.Duplicate(*this))
      m_pChain = nullptr;
  }
  
  CChain(_In_ CChain&& chain) : m_pChain(nullptr)
  {
    Attach(chain.Detach());
  }
  
  explicit CChain(_In_opt_ PCCERT_CHAIN_CONTEXT pChain) : m_pChain(pChain)
  {
  }

  ~CChain()
  {
    if (m_pChain != nullptr)
      Free();
  }
  
//Methods
  CChain& operator=(_In_ const CChain& chain)
  {
    if (this != &chain)
    {
      if (m_pChain != nullptr)
        Free();
      if (!chain.Duplicate(*this))
        m_pChain = nullptr;
    }
    
    return *this;
  }

  CChain& operator=(_In_ CChain&& chain)
  {
    if (m_pChain != nullptr)
      Free();
    Attach(chain.Detach());
    
    return *this;
  }

  PCCERT_CHAIN_CONTEXT Handle() const
  {
    return m_pChain;
  }

  void Attach(_In_opt_ PCCERT_CHAIN_CONTEXT pChain)
  {
    //Validate our parameters
    ATLASSERT(m_pChain == nullptr);
    
    m_pChain = pChain;
  }

  PCCERT_CHAIN_CONTEXT Detach()
  {
    PCCERT_CHAIN_CONTEXT pChain = m_pChain;
    m_pChain = nullptr;
    return pChain;
  }

  void Free()
  {
    //Validate our parameters
    ATLASSERT(m_pChain != nullptr);

    CertFreeCertificateChain(m_pChain);
    m_pChain = nullptr;
  }

  _Success_(return != FALSE)
  BOOL Duplicate(_Inout_ CChain& chain) const
  {
    //Validate our parameters
    ATLASSERT(m_pChain != nullptr);
    ATLASSERT(chain.m_pChain == nullptr);

    chain.m_pChain = CertDuplicateCertificateChain(m_pChain);
    return (chain.m_pChain != nullptr);
  }

  _Success_(return != FALSE)
  BOOL VerifyPolicy(_In_ LPCSTR pszPolicyOID, _In_ PCERT_CHAIN_POLICY_PARA pPolicyPara, _Inout_ PCERT_CHAIN_POLICY_STATUS pPolicyStatus)
  {
    //Validate our parameters
    ATLASSERT(m_pChain != nullptr);

    return CertVerifyCertificateChainPolicy(pszPolicyOID, m_pChain, pPolicyPara, pPolicyStatus);
  }

//Member variables
  PCCERT_CHAIN_CONTEXT m_pChain;

  friend class CStore;
  friend class CChainEngine;
};
}; //namespace CryptoWrappers

#endif //#ifndef __CRYPTOCHAIN_H__
