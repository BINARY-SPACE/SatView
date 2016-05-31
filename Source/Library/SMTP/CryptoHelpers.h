/*
Module : CryptoHelpers.h
Purpose: Defines the interface for some helper functions provided by the CryptoWrappers class framework.
History: PJN / 01-08-2014 1. Initial public release
         PJN / 31-01-2015 1. Updated copyright details
                          2. Marked functions in CryptoHelpers.h as inline.

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

#ifndef __CRYPTOHELPERS_H__
#define __CRYPTOHELPERS_H__

#include <string>
#include <vector>


////////////////////////// Classes ////////////////////////////////////////////

namespace CryptoWrappers
{
//Typedefs
#ifdef _UNICODE
typedef std::wstring String; 
#else
typedef std::string String; 
#endif //#ifdef _UNICODE


//Data conversion functions
  _Success_(return != FALSE)
  inline BOOL BinaryToString(_In_ const BYTE* pbBinary, _In_ DWORD cbBinary, _In_ DWORD dwFlags, _Out_ String& sReturn)
  {
    //First call to get the length of the buffer to allocate
    DWORD cchString = 0;
    if (!CryptBinaryToString(pbBinary, cbBinary, dwFlags, NULL, &cchString))
      return FALSE;

    //Allocate enough memory and recall      
    std::vector<TCHAR> sTemp;
    sTemp.resize(cchString);
    if (!CryptBinaryToString(pbBinary, cbBinary, dwFlags, &(sTemp[0]), &cchString))
      return FALSE;

    sReturn = &(sTemp[0]);
    return TRUE;
  }

#ifdef _AFX
  _Success_(return != FALSE)
  inline BOOL BinaryToString(_In_ const BYTE* pbBinary, _In_ DWORD cbBinary, _In_ DWORD dwFlags, _Out_ CString& sReturn)
  {
    //First call to get the length of the buffer to allocate
    DWORD cchString = 0;
    if (!CryptBinaryToString(pbBinary, cbBinary, dwFlags, NULL, &cchString))
      return FALSE;

    //Allocate enough memory and recall      
    LPTSTR pszReturn = sReturn.GetBufferSetLength(cchString);
    BOOL bSuccess = CryptBinaryToString(pbBinary, cbBinary, dwFlags, pszReturn, &cchString);
    sReturn.ReleaseBuffer();
    return bSuccess;
  }
#endif //#ifdef _AFX

  _Success_(return != FALSE)
  inline BOOL StringToBinary(_In_ LPCTSTR pszString, _In_ DWORD cchString, _In_ DWORD dwFlags, _Out_ std::vector<BYTE>& binary, _Out_opt_ DWORD* pdwSkip = nullptr, _Out_opt_ DWORD* pdwFlags = nullptr)
  {
    //First call to get the length of the buffer to allocate
    DWORD cbBinary = 0;
    if (!CryptStringToBinary(pszString, cchString, dwFlags, NULL, &cbBinary, pdwSkip, pdwFlags))
        return FALSE;

    //Allocate enough memory and recall      
    binary.resize(cbBinary);
    if (!CryptStringToBinary(pszString, cchString, dwFlags, &(binary[0]), &cbBinary, pdwSkip, pdwFlags))
      return FALSE;

    return TRUE;
  }

  _Success_(return != FALSE)
  inline BOOL FormatObject(_In_ DWORD dwCertEncodingType, _In_ DWORD dwFormatStrType, _In_opt_ LPCSTR lpszStructType, _In_reads_bytes_(cbEncoded) const BYTE* pbEncoded, _In_ DWORD cbEncoded, _Out_ std::wstring& sFormat)
  {
    //First call to get the length of the buffer to allocate
    DWORD cbFormat = 0;
    if (!CryptFormatObject(dwCertEncodingType, 0, dwFormatStrType, nullptr, lpszStructType, pbEncoded, cbEncoded, NULL, &cbFormat))
        return FALSE;

    //Allocate enough memory and recall      
    std::vector<BYTE> sTemp;
    sTemp.resize(cbFormat);
    if (!CryptFormatObject(dwCertEncodingType, 0, dwFormatStrType, nullptr, lpszStructType, pbEncoded, cbEncoded, &(sTemp[0]), &cbFormat))
        return FALSE;

    sFormat = reinterpret_cast<wchar_t*>(&(sTemp[0]));
    return TRUE;
  }

#ifdef _AFX
  _Success_(return != FALSE)
  inline BOOL FormatObject(_In_ DWORD dwCertEncodingType, _In_ DWORD dwFormatStrType, _In_opt_ LPCSTR lpszStructType, _In_reads_bytes_(cbEncoded) const BYTE* pbEncoded, _In_ DWORD cbEncoded, _Out_ CStringW& sFormat)
  {
    //First call to get the length of the buffer to allocate
    DWORD cbFormat = 0;
    if (!CryptFormatObject(dwCertEncodingType, 0, dwFormatStrType, nullptr, lpszStructType, pbEncoded, cbEncoded, NULL, &cbFormat))
        return FALSE;

    //Allocate enough memory and recall      
    LPWSTR pszFormat = sFormat.GetBufferSetLength(cbFormat / sizeof(wchar_t));
    BOOL bSuccess = CryptFormatObject(dwCertEncodingType, 0, dwFormatStrType, nullptr, lpszStructType, pbEncoded, cbEncoded, pszFormat, &cbFormat);
    sFormat.ReleaseBuffer();
    return bSuccess;
  }
#endif //#ifdef _AFX
}; //namespace CryptoWrappers

#endif //#ifndef __CRYPTOHELPERS_H__
