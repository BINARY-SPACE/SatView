// TOOLS.CPP : Tools Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the tools related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/10/15 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#include "compression.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CCompressionTools

CCompressionTools::CCompressionTools() : CObject()
{
	lzo_init();
}

INT CCompressionTools::Compress(CONST CByteArray &nData, CByteArray &nCompressedData) CONST
{
	UINT  in_len;
	lzo_uint  out_len;
	lzo_align_t __LZO_MMODEL  nBuffer[(LZO1X_1_MEM_COMPRESS + (sizeof(lzo_align_t) - 1)) / sizeof(lzo_align_t)];

	try
	{
		for (nCompressedData.SetSize(nData.GetSize() + nData.GetSize() / 16 + 64 + 3); lzo1x_1_compress(nData.GetData(), (in_len = (UINT)nData.GetSize()), nCompressedData.GetData(), &out_len, nBuffer) == LZO_E_OK; )
		{
			nCompressedData.SetSize(out_len + sizeof(in_len));
			CopyMemory(nCompressedData.GetData() + nCompressedData.GetSize() - sizeof(in_len), &in_len, sizeof(in_len));
			return((INT)nCompressedData.GetSize());
		}
	}
	catch (...) {}
	nCompressedData.RemoveAll();
	return -1;
}

BOOL CCompressionTools::Decompress(CONST CByteArray &nCompressedData, CByteArray &nData) CONST
{
	UINT  in_len;
	lzo_uint  out_len;

	try
	{
		for (nData.RemoveAll(); nCompressedData.GetSize() >= sizeof(in_len); )
		{
			for (CopyMemory(&in_len, nCompressedData.GetData() + nCompressedData.GetSize() - sizeof(in_len), sizeof(in_len)); in_len > 0; )
			{
				for (nData.SetSize(in_len); lzo1x_decompress(nCompressedData.GetData(), nCompressedData.GetSize() - sizeof(in_len), nData.GetData(), &out_len, (LPVOID *)NULL) == LZO_E_OK; )
				{
					nData.SetSize(out_len);
					return TRUE;
				}
				break;
			}
			return TRUE;
		}
	}
	catch (...) {}
	nData.RemoveAll();
	return FALSE;
}

INT CCompressionTools::CompressText(LPCTSTR pszText, CByteArray &nCompressedData) CONST
{
	INT  cbData;
	CByteArray  nData;

	nData.SetSize((cbData = (lstrlen(pszText) + 1)*sizeof(TCHAR)));
	CopyMemory(nData.GetData(), pszText, (nData.GetSize() == cbData) ? cbData : 0);
	return Compress(nData, nCompressedData);
}

BOOL CCompressionTools::DecompressText(CONST CByteArray &nCompressedData, CString &szText) CONST
{
	CByteArray  nData;

	if (Decompress(nCompressedData, nData))
	{
		szText = (LPCTSTR)nData.GetData();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CCryptographyTools

CCryptographyTools::CCryptographyTools() : CObject()
{
	SetBaseData(STRING(IDS_CRYPTOGRAPHY_DEFAULTBASEDATA));
}

VOID CCryptographyTools::SetBaseData(LPCTSTR pszBaseData)
{
	m_nBaseData.SetSize(lstrlen(pszBaseData));
#ifndef UNICODE
	CopyMemory(m_nBaseData.GetData(), pszBaseData, strlen(pszBaseData));
#else
	WideCharToMultiByte(CP_ACP, 0, pszBaseData, -1, (LPSTR)m_nBaseData.GetData(), lstrlen(pszBaseData), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
}

CString CCryptographyTools::GetBaseData() CONST
{
	CString  szBaseData;

#ifndef UNICODE
	CopyMemory(szBaseData.GetBufferSetLength((INT)m_nBaseData.GetSize()), m_nBaseData.GetData(), (INT)m_nBaseData.GetSize());
#else
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)m_nBaseData.GetData(), (INT)m_nBaseData.GetSize(), szBaseData.GetBufferSetLength((INT)m_nBaseData.GetSize()), (INT)m_nBaseData.GetSize());
#endif
	szBaseData.ReleaseBuffer();
	return szBaseData;
}

INT CCryptographyTools::Encrypt(CONST CByteArray &nData, CByteArray &nEncryptedData) CONST
{
	DWORD  cbCryptData;
	HCRYPTKEY  hCryptKey;
	HCRYPTHASH  hCryptHashKey;
	HCRYPTPROV  hCryptProvider;

	if (CryptAcquireContext(&hCryptProvider, (LPCTSTR)NULL, MS_DEF_PROV, PROV_RSA_FULL, 0) || CryptAcquireContext(&hCryptProvider, (LPCTSTR)NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET))
	{
		if (CryptCreateHash(hCryptProvider, CALG_MD5, (HCRYPTKEY)NULL, 0, &(hCryptHashKey = (HCRYPTHASH)NULL)) && CryptHashData(hCryptHashKey, (CONST BYTE *) m_nBaseData.GetData(), (DWORD)m_nBaseData.GetSize(), 0))
		{
			if (CryptDeriveKey(hCryptProvider, CALG_RC2, hCryptHashKey, CRYPT_EXPORTABLE, &(hCryptKey = (HCRYPTKEY)NULL)))
			{
				if (CryptEncrypt(hCryptKey, (HCRYPTHASH)NULL, TRUE, 0, (LPBYTE)NULL, &(cbCryptData = (DWORD)nData.GetSize()), 0))
				{
					for (nEncryptedData.Copy(nData), nEncryptedData.SetSize(cbCryptData); nEncryptedData.GetSize() == cbCryptData; )
					{
						if (CryptEncrypt(hCryptKey, (HCRYPTHASH)NULL, TRUE, 0, nEncryptedData.GetData(), &(cbCryptData = (DWORD)nData.GetSize()), (DWORD)nEncryptedData.GetSize()))
						{
							CryptDestroyKey(hCryptKey);
							CryptDestroyHash(hCryptHashKey);
							CryptReleaseContext(hCryptProvider, 0);
							nEncryptedData.SetSize(cbCryptData);
							return cbCryptData;
						}
						break;
					}
				}
				CryptDestroyKey(hCryptKey);
			}
		}
		if (hCryptHashKey != (HCRYPTHASH)NULL) CryptDestroyHash(hCryptHashKey);
		CryptReleaseContext(hCryptProvider, 0);
	}
	return 0;
}

BOOL CCryptographyTools::Decrypt(CONST CByteArray &nEncryptedData, CByteArray &nData) CONST
{
	DWORD  cbCryptData;
	HCRYPTKEY  hCryptKey;
	HCRYPTHASH  hCryptHashKey;
	HCRYPTPROV  hCryptProvider;

	if (CryptAcquireContext(&hCryptProvider, (LPCTSTR)NULL, MS_DEF_PROV, PROV_RSA_FULL, 0) || CryptAcquireContext(&hCryptProvider, (LPCTSTR)NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET))
	{
		if (CryptCreateHash(hCryptProvider, CALG_MD5, (HCRYPTKEY)NULL, 0, &(hCryptHashKey = (HCRYPTHASH)NULL)) && CryptHashData(hCryptHashKey, (CONST BYTE *) m_nBaseData.GetData(), (DWORD)m_nBaseData.GetSize(), 0))
		{
			if (CryptDeriveKey(hCryptProvider, CALG_RC2, hCryptHashKey, CRYPT_EXPORTABLE, &(hCryptKey = (HCRYPTKEY)NULL)))
			{
				for (nData.Copy(nEncryptedData); CryptDecrypt(hCryptKey, (HCRYPTHASH)NULL, TRUE, 0, nData.GetData(), &(cbCryptData = (DWORD)nData.GetSize())); )
				{
					CryptDestroyKey(hCryptKey);
					CryptDestroyHash(hCryptHashKey);
					CryptReleaseContext(hCryptProvider, 0);
					nData.SetSize(cbCryptData);
					return TRUE;
				}
				CryptDestroyKey(hCryptKey);
			}
		}
		if (hCryptHashKey != (HCRYPTHASH)NULL) CryptDestroyHash(hCryptHashKey);
		CryptReleaseContext(hCryptProvider, 0);
	}
	nData.RemoveAll();
	return FALSE;
}

INT CCryptographyTools::EncryptText(LPCTSTR pszText, CByteArray &nEncryptedData) CONST
{
	CByteArray  nData;

	nData.SetSize((lstrlen(pszText) + 1)*sizeof(TCHAR));
	CopyMemory(nData.GetData(), pszText, (lstrlen(pszText) + 1)*sizeof(TCHAR));
	return Encrypt(nData, nEncryptedData);
}

BOOL CCryptographyTools::DecryptText(CONST CByteArray &nEncryptedData, CString &szText) CONST
{
	CByteArray  nData;

	if (Decrypt(nEncryptedData, nData))
	{
		if (nData.GetSize() == strlen((LPCSTR)nData.GetData()) + 1)
		{
#ifndef UNICODE
			szText = (LPCSTR)nData.GetData();
#else
			MultiByteToWideChar(CP_ACP, 0, (LPCSTR)nData.GetData(), (INT)(nData.GetSize() - 1), szText.GetBufferSetLength((INT)(nData.GetSize() - 1)), (INT)(nData.GetSize() - 1));
			szText.ReleaseBuffer();
#endif
			return TRUE;
		}
		if (nData.GetSize() == (wcslen((LPCWSTR)nData.GetData()) + 1)*sizeof(WCHAR))
		{
#ifndef UNICODE
			WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)nData.GetData(), (INT)((nData.GetSize() / sizeof(WCHAR)) - 1), szText.GetBufferSetLength((INT)((nData.GetSize() / sizeof(WCHAR)) - 1)), (INT)((nData.GetSize() / sizeof(WCHAR)) - 1), (LPCSTR)NULL, (LPBOOL)NULL);
			szText.ReleaseBuffer();
#else
			szText = (LPCWSTR)nData.GetData();
#endif
			return TRUE;
		}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CFontTools

CFontTools::CFontTools() : CObject()
{
	return;
}
CFontTools::CFontTools(CFont *pFont)
{
	QueryDefaultFont(pFont);
}
CFontTools::CFontTools(LOGFONT *plf)
{
	QueryDefaultFont(plf);
}
CFontTools::CFontTools(INT nType, LOGFONT *plf) : CObject()
{
	QueryStockFont(nType, plf);
}

INT CFontTools::EnumerateFonts(CStringArray &szFonts) CONST
{
	CClientDC  cDC(NULL);

	return EnumerateFonts(&cDC, szFonts);
}
INT CFontTools::EnumerateFonts(CDC *pDC, CStringArray &szFonts) CONST
{
	LOGFONT  slf;

	for (szFonts.RemoveAll(); QueryDefaultFont(&slf); )
	{
		_tcscpy_s(slf.lfFaceName, sizeof(slf.lfFaceName) / sizeof(TCHAR), EMPTYSTRING);
		EnumFontFamiliesEx(pDC->GetSafeHdc(), &slf, (FONTENUMPROC)EnumerateFontsProc, (LPARAM)&szFonts, 0);
		break;
	}
	return((INT)szFonts.GetSize());
}

BOOL CFontTools::EnumerateFont(LPCTSTR pszFont, CStringArray &szStyles, CStringArray &szSizes, BOOL &bUnderlined) CONST
{
	CClientDC  cDC(NULL);

	return EnumerateFont(&cDC, pszFont, szStyles, szSizes, bUnderlined);
}
BOOL CFontTools::EnumerateFont(CDC *pDC, LPCTSTR pszFont, CStringArray &szStyles, CStringArray &szSizes, BOOL &bUnderlined) CONST
{
	LOGFONT  slf;

	for (szStyles.RemoveAll(), szSizes.RemoveAll(), bUnderlined = FALSE; QueryDefaultFont(&slf); )
	{
		_tcscpy_s(slf.lfFaceName, sizeof(slf.lfFaceName) / sizeof(TCHAR), pszFont);
		EnumFontFamiliesEx(pDC->GetSafeHdc(), &slf, (FONTENUMPROC)EnumerateFontStylesProc, (LPARAM)&szStyles, 0);
		EnumFontFamiliesEx(pDC->GetSafeHdc(), &slf, (FONTENUMPROC)EnumerateFontSizesProc, (LPARAM)&szSizes, 0);
		EnumFontFamiliesEx(pDC->GetSafeHdc(), &slf, (FONTENUMPROC)EnumerateFontUnderlinedProc, (LPARAM)&bUnderlined, 0);
		break;
	}
	return((szStyles.GetSize() > 0 && szSizes.GetSize() > 0) ? TRUE : FALSE);
}

BOOL CFontTools::EnumerateFontCharacteristics(LOGFONT *plf) CONST
{
	CClientDC  cDC(NULL);

	return EnumerateFontCharacteristics(&cDC, plf);
}
BOOL CFontTools::EnumerateFontCharacteristics(CDC *pDC, LOGFONT *plf) CONST
{
	return((!EnumFontFamiliesEx(pDC->GetSafeHdc(), plf, (FONTENUMPROC)EnumerateFontCharacteristicsProc, (LPARAM)plf, 0)) ? TRUE : FALSE);
}

CString CFontTools::TranslateFontStyle(CONST LOGFONT *plf) CONST
{
	if (plf->lfWeight <= FW_REGULAR  &&  !plf->lfItalic) return STRING(IDS_FONTSTYLE_REGULAR);
	if (plf->lfWeight <= FW_REGULAR  &&  plf->lfItalic) return STRING(IDS_FONTSTYLE_ITALIC);
	if (plf->lfWeight > FW_REGULAR  &&  !plf->lfItalic) return STRING(IDS_FONTSTYLE_BOLD);
	if (plf->lfWeight > FW_REGULAR  &&  plf->lfItalic) return STRING(IDS_FONTSTYLE_BOLDITALIC);
	return EMPTYSTRING;
}
VOID CFontTools::TranslateFontStyle(LPCTSTR pszStyle, LONG &lWeight, BYTE &bItalic) CONST
{
	lWeight = (!lstrcmp(pszStyle, STRING(IDS_FONTSTYLE_REGULAR)) || !lstrcmp(pszStyle, STRING(IDS_FONTSTYLE_ITALIC))) ? FW_NORMAL : FW_BOLD;
	bItalic = (!lstrcmp(pszStyle, STRING(IDS_FONTSTYLE_ITALIC)) || !lstrcmp(pszStyle, STRING(IDS_FONTSTYLE_BOLDITALIC))) ? TRUE : FALSE;
}

CString CFontTools::TranslateFontSize(CONST LOGFONT *plf) CONST
{
	CStringTools  cStringTools;

	return cStringTools.ConvertIntToString(QueryPoints(plf));
}
VOID CFontTools::TranslateFontSize(LPCTSTR pszSize, LONG &lHeight) CONST
{
	lHeight = QueryPixels(_ttoi(pszSize));
}

BOOL CFontTools::QueryDefaultFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((QueryDefaultFont(&lfFont)) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}
BOOL CFontTools::QueryDefaultFont(LOGFONT *plf) CONST
{
	NONCLIENTMETRICS  sMetrics;

	if (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, (sMetrics.cbSize = sizeof(sMetrics)), &sMetrics, 0))
	{
		CopyMemory(plf, &sMetrics.lfMessageFont, sizeof(LOGFONT));
		plf->lfHeight = QueryHeight(plf);
		plf->lfWidth = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL CFontTools::QueryStockFont(INT nType, LOGFONT *plf) CONST
{
	CFont  cFont;

	if (cFont.CreateStockObject(nType) && cFont.GetLogFont(plf) > 0)
	{
		plf->lfHeight = QueryHeight(plf);
		plf->lfWidth = 0;
		return TRUE;
	}
	return FALSE;
}

INT CFontTools::QueryPoints(CFont *pFont) CONST
{
	INT  nPts;
	CClientDC  cDC(NULL);

	nPts = QueryPoints(&cDC, pFont);
	return nPts;
}
INT CFontTools::QueryPoints(CONST LOGFONT *plf) CONST
{
	INT  nPts;
	CFont  cFont;

	if (cFont.CreateFontIndirect(plf))
	{
		nPts = QueryPoints(&cFont);
		cFont.DeleteObject();
		return nPts;
	}
	return 0;
}
INT CFontTools::QueryPoints(CDC *pDC, CFont *pFont) CONST
{
	INT  nPts;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pOldFont = pDC->SelectObject(pFont)))
	{
		if (pDC->GetTextMetrics(&tmFont))
		{
			nPts = MulDiv(72, tmFont.tmHeight - tmFont.tmInternalLeading, pDC->GetDeviceCaps(LOGPIXELSY));
			pDC->SelectObject(pOldFont);
			return nPts;
		}
		pDC->SelectObject(pOldFont);
	}
	return 0;
}
INT CFontTools::QueryPoints(CDC *pDC, CONST LOGFONT *plf) CONST
{
	INT  nPts;
	CFont  cFont;

	if (cFont.CreateFontIndirect(plf))
	{
		nPts = QueryPoints(pDC, &cFont);
		cFont.DeleteObject();
		return nPts;
	}
	return 0;
}

INT CFontTools::QueryPixels(INT nPts) CONST
{
	CClientDC  cDC(NULL);

	return QueryPixels(&cDC, nPts);
}
INT CFontTools::QueryPixels(CDC *pDC, INT nPts) CONST
{
	return -MulDiv(nPts, pDC->GetDeviceCaps(LOGPIXELSY), 72);
}

INT CFontTools::QueryHeight(CONST LOGFONT *plf) CONST
{
	CClientDC  cDC(NULL);

	return QueryHeight(&cDC, plf);
}
INT CFontTools::QueryHeight(CDC *pDC, CONST LOGFONT *plf) CONST
{
	INT  nHeight;
	CFont  cFont;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if (cFont.CreateFontIndirect(plf))
	{
		if ((pOldFont = pDC->SelectObject(&cFont)))
		{
			if (pDC->GetTextMetrics(&tmFont))
			{
				nHeight = tmFont.tmHeight;
				pDC->SelectObject(pOldFont);
				cFont.DeleteObject();
				return nHeight;
			}
			pDC->SelectObject(pOldFont);
		}
		cFont.DeleteObject();
	}
	return 0;
}

INT CALLBACK CFontTools::EnumerateFontsProc(ENUMLOGFONTEX *plf, NEWTEXTMETRICEX *ptm, DWORD nFontType, LPARAM lParam)
{
	CStringArray  *pszFonts = (CStringArray *)lParam;

	pszFonts->Add(plf->elfLogFont.lfFaceName);
	return TRUE;
}

INT CALLBACK CFontTools::EnumerateFontStylesProc(ENUMLOGFONTEX *plf, NEWTEXTMETRICEX *ptm, DWORD nFontType, LPARAM lParam)
{
	INT  nFontStyle;
	INT  nFontStyles;
	CStringArray  *pszStyles = (CStringArray *)lParam;

	for (nFontStyle = 0, nFontStyles = (INT)pszStyles->GetSize(); nFontStyle < nFontStyles; nFontStyle++)
	{
		if (plf->elfLogFont.lfWeight <= FW_REGULAR  &&  !plf->elfLogFont.lfItalic  &&  pszStyles->GetAt(nFontStyle) == STRING(IDS_FONTSTYLE_REGULAR)) break;
		if (plf->elfLogFont.lfWeight <= FW_REGULAR  &&  plf->elfLogFont.lfItalic  &&  pszStyles->GetAt(nFontStyle) == STRING(IDS_FONTSTYLE_ITALIC)) break;
		if (plf->elfLogFont.lfWeight > FW_REGULAR  &&  !plf->elfLogFont.lfItalic  &&  pszStyles->GetAt(nFontStyle) == STRING(IDS_FONTSTYLE_BOLD)) break;
		if (plf->elfLogFont.lfWeight > FW_REGULAR  &&  plf->elfLogFont.lfItalic  &&  pszStyles->GetAt(nFontStyle) == STRING(IDS_FONTSTYLE_BOLDITALIC)) break;
	}
	for (; nFontStyle == nFontStyles; )
	{
		if (plf->elfLogFont.lfWeight <= FW_REGULAR  &&  !plf->elfLogFont.lfItalic)
		{
			pszStyles->Add(STRING(IDS_FONTSTYLE_REGULAR));
			break;
		}
		if (plf->elfLogFont.lfWeight <= FW_REGULAR  &&  plf->elfLogFont.lfItalic)
		{
			pszStyles->Add(STRING(IDS_FONTSTYLE_ITALIC));
			break;
		}
		if (plf->elfLogFont.lfWeight > FW_REGULAR  &&  !plf->elfLogFont.lfItalic)
		{
			pszStyles->Add(STRING(IDS_FONTSTYLE_BOLD));
			break;
		}
		if (plf->elfLogFont.lfWeight > FW_REGULAR  &&  plf->elfLogFont.lfItalic)
		{
			pszStyles->Add(STRING(IDS_FONTSTYLE_BOLDITALIC));
			break;
		}
		break;
	}
	return TRUE;
}

INT CALLBACK CFontTools::EnumerateFontSizesProc(ENUMLOGFONTEX *plf, NEWTEXTMETRICEX *ptm, DWORD nFontType, LPARAM lParam)
{
	INT  nFontSize[2];
	INT  nFontSizes[2];
	CString  szFontSize;
	CFontTools  cFontTools;
	CStringArray  *pszSizes;
	CStringTools  cStringTools;
	static INT  nFontSizeTable[] = { 4,5,6,7,8,9,10,11,12,14,16,18,20,22,24 };

	for (nFontSize[0] = 0, nFontSizes[0] = (nFontType == TRUETYPE_FONTTYPE) ? sizeof(nFontSizeTable) / sizeof(INT) : 0, pszSizes = (CStringArray *)lParam; nFontSize[0] < nFontSizes[0]; nFontSize[0]++)
	{
		for (nFontSize[1] = 0, nFontSizes[1] = (INT)pszSizes->GetSize(), szFontSize = cStringTools.ConvertIntToString(nFontSizeTable[nFontSize[0]]); nFontSize[1] < nFontSizes[1]; nFontSize[1]++)
		{
			if (pszSizes->GetAt(nFontSize[1]) == szFontSize) break;
			continue;
		}
		if (nFontSize[1] == nFontSizes[1])
		{
			pszSizes->Add(szFontSize);
			continue;
		}
	}
	for (nFontSize[0] = 0, nFontSizes[0] = (nFontType != TRUETYPE_FONTTYPE) ? (INT)pszSizes->GetSize() : 0; nFontSize[0] < nFontSizes[0]; nFontSize[0]++)
	{
		if (_ttoi(pszSizes->GetAt(nFontSize[0])) > _ttoi((szFontSize = cStringTools.ConvertIntToString(cFontTools.QueryPoints(&plf->elfLogFont)))))
		{
			pszSizes->InsertAt(nFontSize[0], szFontSize);
			break;
		}
		if (_ttoi(pszSizes->GetAt(nFontSize[0])) == _ttoi(szFontSize)) break;
	}
	for (; nFontType != TRUETYPE_FONTTYPE && nFontSize[0] == nFontSizes[0]; )
	{
		pszSizes->Add(cStringTools.ConvertIntToString(cFontTools.QueryPoints(&plf->elfLogFont)));
		break;
	}
	return TRUE;
}

INT CALLBACK CFontTools::EnumerateFontUnderlinedProc(ENUMLOGFONTEX *plf, NEWTEXTMETRICEX *ptm, DWORD nFontType, LPARAM lParam)
{
	BOOL  *pbUnderlined = (BOOL *)lParam;

	if (plf->elfLogFont.lfUnderline)
	{
		*pbUnderlined = TRUE;
		return FALSE;
	}
	return TRUE;
}

INT CALLBACK CFontTools::EnumerateFontCharacteristicsProc(ENUMLOGFONTEX *plf, NEWTEXTMETRICEX *ptm, DWORD nFontType, LPARAM lParam)
{
	LONG  lfHeight;
	LOGFONT  *pLogFont = (LOGFONT *)lParam;

	for (lfHeight = pLogFont->lfHeight; plf->elfLogFont.lfWeight == pLogFont->lfWeight && plf->elfLogFont.lfItalic == pLogFont->lfItalic && plf->elfLogFont.lfUnderline == pLogFont->lfUnderline; )
	{
		CopyMemory(pLogFont, &plf->elfLogFont, sizeof(LOGFONT));
		pLogFont->lfHeight = lfHeight;
		pLogFont->lfWidth = 0;
		return FALSE;
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CStringTools

CString CStringTools::ConvertIntToString(INT n) CONST
{
	TCHAR  szNumber[sizeof(n) * 8 + 1];

	return((!_itot_s(n, szNumber, sizeof(szNumber) / sizeof(TCHAR), 10)) ? szNumber : EMPTYSTRING);
}
CString CStringTools::ConvertIntToString(INT n, INT nRadix) CONST
{
	TCHAR  szNumber[sizeof(n) * 8 + 1];

	return((!_itot_s(n, szNumber, sizeof(szNumber) / sizeof(TCHAR), nRadix) && !_tcsupr_s(szNumber, sizeof(szNumber) / sizeof(TCHAR))) ? szNumber : EMPTYSTRING);
}

CString CStringTools::ConvertLongIntToString(LONGLONG n) CONST
{
	TCHAR  szNumber[sizeof(n) * 8 + 1];

	return((!_i64tot_s(n, szNumber, sizeof(szNumber) / sizeof(TCHAR), 10)) ? szNumber : EMPTYSTRING);
}
CString CStringTools::ConvertLongIntToString(LONGLONG n, INT nRadix) CONST
{
	TCHAR  szNumber[sizeof(n) * 8 + 1];

	return((!_i64tot_s(n, szNumber, sizeof(szNumber) / sizeof(TCHAR), nRadix) && !_tcsupr_s(szNumber, sizeof(szNumber) / sizeof(TCHAR))) ? szNumber : EMPTYSTRING);
}

CString CStringTools::ConvertUIntToString(UINT n) CONST
{
	TCHAR  szNumber[sizeof(n) * 8 + 1];

	return((!_ultot_s(n, szNumber, sizeof(szNumber) / sizeof(TCHAR), 10)) ? szNumber : EMPTYSTRING);
}
CString CStringTools::ConvertUIntToString(UINT n, INT nRadix) CONST
{
	TCHAR  szNumber[sizeof(n) * 8 + 1];

	return((!_ultot_s(n, szNumber, sizeof(szNumber) / sizeof(TCHAR), nRadix) && !_tcsupr_s(szNumber, sizeof(szNumber) / sizeof(TCHAR))) ? szNumber : EMPTYSTRING);
}

CString CStringTools::ConvertLongUIntToString(ULONGLONG n) CONST
{
	TCHAR  szNumber[sizeof(n) * 8 + 1];

	return((!_ui64tot_s(n, szNumber, sizeof(szNumber) / sizeof(TCHAR), 10)) ? szNumber : EMPTYSTRING);
}
CString CStringTools::ConvertLongUIntToString(ULONGLONG n, INT nRadix) CONST
{
	TCHAR  szNumber[sizeof(n) * 8 + 1];

	return((!_ui64tot_s(n, szNumber, sizeof(szNumber) / sizeof(TCHAR), nRadix) && !_tcsupr_s(szNumber, sizeof(szNumber) / sizeof(TCHAR))) ? szNumber : EMPTYSTRING);
}

CString CStringTools::ConvertFloatToString(double f) CONST
{
	return ConvertFloatToString(f, -1);
}
CString CStringTools::ConvertFloatToString(double f, INT nDigits) CONST
{
	INT  nPos[2];
	INT  nLength;
	double  fValue;
	CString  szResult;
	CHAR  szPrefix[16];
	CHAR  szNumber[2][_CVTBUFSIZE];

	for (; nDigits != 0; )
	{
		if ((fValue = fabs(f)) < 1.0)
		{
			if (!_fcvt_s(szNumber[0], sizeof(szNumber[0]) / sizeof(CHAR), f, (nDigits = (nDigits > 0) ? nDigits : DEFAULTFLOATINGPOINTDECIMALPLACES), &nPos[0], &nPos[1]) && strlen(szNumber[0]) > 0 && !_gcvt_s(szPrefix, sizeof(szPrefix) / sizeof(CHAR), -0.1, 1))
			{
				for (strncpy_s(szNumber[1], sizeof(szNumber[1]) / sizeof(CHAR), &szPrefix[(1 - nPos[1])], (nLength = 1 + nPos[1] + 1)); nPos[0] < 0; nPos[0]++)
				{
					szNumber[1][nLength] = szPrefix[1];
					nLength++;
				}
				while (strlen(szNumber[0]) > 0)
				{
					if (szNumber[0][strlen(szNumber[0]) - 1] == szPrefix[1])
					{
						szNumber[0][strlen(szNumber[0]) - 1] = EOS;
						continue;
					}
					break;
				}
				strcpy_s(&szNumber[1][nLength], sizeof(szNumber[1]) / sizeof(CHAR) - nLength, szNumber[0]);
				break;
			}
		}
		if (!_gcvt_s(szNumber[1], sizeof(szNumber[1]) / sizeof(CHAR), f, (nDigits > 0) ? ((fValue >= 10.0) ? (int)min(log10(fValue) + nDigits + 1, DEFAULTFLOATINGPOINTNUMBERPLACES) : (nDigits + 1)) : ((fValue >= 10.0) ? (int)min(log10(fValue) + DEFAULTFLOATINGPOINTDECIMALPLACES + 1, DEFAULTFLOATINGPOINTNUMBERPLACES) : (DEFAULTFLOATINGPOINTDECIMALPLACES + 1)))) break;
		szNumber[1][0] = EOS;
		break;
	}
#ifndef UNICODE
	szResult = szNumber[1];
#else
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szNumber[1], -1, szResult.GetBufferSetLength((INT)strlen(szNumber[1])), (INT)strlen(szNumber[1]) + 1);
	szResult.ReleaseBuffer();
#endif
	if (!szResult.IsEmpty() && !_istdigit(szResult.GetAt((nLength = szResult.GetLength()) - 1)))
	{
		_itot_s(0, szResult.GetBufferSetLength(nLength + 1) + nLength, 2, 10);
		szResult.ReleaseBuffer();
	}
	return szResult;
}

CString CStringTools::ConvertFloatToTruncatedString(double f) CONST
{
	return ConvertFloatToTruncatedString(f, -1);
}
CString CStringTools::ConvertFloatToTruncatedString(double f, INT nDigits) CONST
{
	CString  szResult;

	if (floor(f) != f)
	{
		szResult = ConvertFloatToString(f, nDigits);
		return szResult;
	}
	if (f >= 0.0)
	{
		szResult = ConvertLongUIntToString((ULONGLONG)f);
		return szResult;
	}
	return ConvertLongIntToString((LONGLONG)f);
}

CString CStringTools::ConvertIntToPaddedString(INT n, INT nDigits) CONST
{
	CString  szSign;
	CString  szDigit;
	CString  szNumber;
	CString  szResult;

	szSign = ConvertIntToString(-1);
	szDigit = ConvertIntToString(0);
	szNumber = ConvertUIntToString(abs(n));
	szResult = szSign.Left((n < 0) ? (szSign.GetLength() - 1) : 0);
	szResult += CString(szDigit.GetAt(0), max(nDigits - szNumber.GetLength() - szResult.GetLength(), 0)) + szNumber;
	return szResult;
}
CString CStringTools::ConvertIntToPaddedString(INT n, INT nDigits, INT nRadix) CONST
{
	CString  szSign;
	CString  szDigit;
	CString  szNumber;
	CString  szResult;

	szSign = ConvertIntToString(-1);
	szDigit = ConvertIntToString(0);
	szNumber = ConvertUIntToString(abs(n), nRadix);
	szResult = szSign.Left((n < 0) ? (szSign.GetLength() - 1) : 0);
	szResult += CString(szDigit.GetAt(0), max(nDigits - szNumber.GetLength() - szResult.GetLength(), 0)) + szNumber;
	return szResult;
}

CString CStringTools::ConvertLongIntToPaddedString(LONGLONG n, INT nDigits) CONST
{
	CString  szSign;
	CString  szDigit;
	CString  szNumber;
	CString  szResult;

	szSign = ConvertLongIntToString(-1);
	szDigit = ConvertLongIntToString(0);
	szNumber = ConvertLongUIntToString((n < 0) ? -n : n);
	szResult = szSign.Left((n < 0) ? (szSign.GetLength() - 1) : 0);
	szResult += CString(szDigit.GetAt(0), max(nDigits - szNumber.GetLength() - szResult.GetLength(), 0)) + szNumber;
	return szResult;
}
CString CStringTools::ConvertLongIntToPaddedString(LONGLONG n, INT nDigits, INT nRadix) CONST
{
	CString  szSign;
	CString  szDigit;
	CString  szNumber;
	CString  szResult;

	szSign = ConvertLongIntToString(-1);
	szDigit = ConvertLongIntToString(0);
	szNumber = ConvertLongUIntToString((n < 0) ? -n : n, nRadix);
	szResult = szSign.Left((n < 0) ? (szSign.GetLength() - 1) : 0);
	szResult += CString(szDigit.GetAt(0), max(nDigits - szNumber.GetLength() - szResult.GetLength(), 0)) + szNumber;
	return szResult;
}

CString CStringTools::ConvertUIntToPaddedString(UINT n, INT nDigits) CONST
{
	CString  szDigit;
	CString  szNumber;
	CString  szResult;

	szDigit = ConvertUIntToString(0);
	szNumber = ConvertUIntToString(n);
	szResult = CString(szDigit.GetAt(0), max(nDigits - szNumber.GetLength(), 0)) + szNumber;
	return szResult;
}
CString CStringTools::ConvertUIntToPaddedString(UINT n, INT nDigits, INT nRadix) CONST
{
	CString  szDigit;
	CString  szNumber;
	CString  szResult;

	szDigit = ConvertUIntToString(0);
	szNumber = ConvertUIntToString(n, nRadix);
	szResult = CString(szDigit.GetAt(0), max(nDigits - szNumber.GetLength(), 0)) + szNumber;
	return szResult;
}

CString CStringTools::ConvertLongUIntToPaddedString(ULONGLONG n, INT nDigits) CONST
{
	CString  szDigit;
	CString  szNumber;
	CString  szResult;

	szDigit = ConvertLongUIntToString(0);
	szNumber = ConvertLongUIntToString(n);
	szResult = CString(szDigit.GetAt(0), max(nDigits - szNumber.GetLength(), 0)) + szNumber;
	return szResult;
}
CString CStringTools::ConvertLongUIntToPaddedString(ULONGLONG n, INT nDigits, INT nRadix) CONST
{
	CString  szDigit;
	CString  szNumber;
	CString  szResult;

	szDigit = ConvertLongUIntToString(0);
	szNumber = ConvertLongUIntToString(n, nRadix);
	szResult = CString(szDigit.GetAt(0), max(nDigits - szNumber.GetLength(), 0)) + szNumber;
	return szResult;
}

CString CStringTools::ConvertIntToStructuredString(INT n) CONST
{
	INT  cPos;
	INT  cbDelimiter;
	CString  szDigits;
	CString  szNumber;
	CString  szResult;
	CString  szDelimiter;

	szResult = ConvertIntToString(n);
	if ((cbDelimiter = GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, (LPTSTR)NULL, 0)))
	{
		if (GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, szDelimiter.GetBufferSetLength(cbDelimiter - 1), cbDelimiter))
		{
			for (cPos = szResult.GetLength() - 3, szNumber = szResult, szDelimiter.ReleaseBuffer(); cPos > 0; cPos -= 3)
			{
				if (_istdigit(szNumber[cPos - 1]))
				{
					szDigits = szResult.Mid(cPos);
					szResult = szNumber.Left(cPos);
					szResult += szDelimiter + szDigits;
				}
			}
			return szResult;
		}
		szDelimiter.ReleaseBuffer();
	}
	return szResult;
}

CString CStringTools::ConvertLongIntToStructuredString(LONGLONG n) CONST
{
	INT  cPos;
	INT  cbDelimiter;
	CString  szDigits;
	CString  szNumber;
	CString  szResult;
	CString  szDelimiter;

	szResult = ConvertLongIntToString(n);
	if ((cbDelimiter = GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, (LPTSTR)NULL, 0)))
	{
		if (GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, szDelimiter.GetBufferSetLength(cbDelimiter - 1), cbDelimiter))
		{
			for (cPos = szResult.GetLength() - 3, szNumber = szResult, szDelimiter.ReleaseBuffer(); cPos > 0; cPos -= 3)
			{
				if (_istdigit(szNumber[cPos - 1]))
				{
					szDigits = szResult.Mid(cPos);
					szResult = szNumber.Left(cPos);
					szResult += szDelimiter + szDigits;
				}
			}
			return szResult;
		}
		szDelimiter.ReleaseBuffer();
	}
	return szResult;
}

CString CStringTools::ConvertUIntToStructuredString(UINT n) CONST
{
	INT  cPos;
	INT  cbDelimiter;
	CString  szDigits;
	CString  szNumber;
	CString  szResult;
	CString  szDelimiter;

	szResult = ConvertUIntToString(n);
	if ((cbDelimiter = GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, (LPTSTR)NULL, 0)))
	{
		if (GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, szDelimiter.GetBufferSetLength(cbDelimiter - 1), cbDelimiter))
		{
			for (cPos = szResult.GetLength() - 3, szNumber = szResult, szDelimiter.ReleaseBuffer(); cPos > 0; cPos -= 3)
			{
				if (_istdigit(szNumber[cPos - 1]))
				{
					szDigits = szResult.Mid(cPos);
					szResult = szNumber.Left(cPos);
					szResult += szDelimiter + szDigits;
				}
			}
			return szResult;
		}
		szDelimiter.ReleaseBuffer();
	}
	return szResult;
}

CString CStringTools::ConvertLongUIntToStructuredString(ULONGLONG n) CONST
{
	INT  cPos;
	INT  cbDelimiter;
	CString  szDigits;
	CString  szNumber;
	CString  szResult;
	CString  szDelimiter;

	szResult = ConvertLongUIntToString(n);
	if ((cbDelimiter = GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, (LPTSTR)NULL, 0)))
	{
		if (GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, szDelimiter.GetBufferSetLength(cbDelimiter - 1), cbDelimiter))
		{
			for (cPos = szResult.GetLength() - 3, szNumber = szResult, szDelimiter.ReleaseBuffer(); cPos > 0; cPos -= 3)
			{
				if (_istdigit(szNumber[cPos - 1]))
				{
					szDigits = szResult.Mid(cPos);
					szResult = szNumber.Left(cPos);
					szResult += szDelimiter + szDigits;
				}
			}
			return szResult;
		}
		szDelimiter.ReleaseBuffer();
	}
	return szResult;
}

CString CStringTools::AddIntToString(INT n, LPCTSTR pszText) CONST
{
	CString  szResult;

	szResult = pszText + ConvertIntToString(n);
	return szResult;
}
CString CStringTools::AddIntToString(INT n, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertIntToString(n, nRadix);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}

CString CStringTools::AddLongIntToString(LONGLONG n, LPCTSTR pszText) CONST
{
	CString  szResult;

	szResult = pszText + ConvertLongIntToString(n);
	return szResult;
}
CString CStringTools::AddLongIntToString(LONGLONG n, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertLongIntToString(n, nRadix);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}

CString CStringTools::AddUIntToString(UINT n, LPCTSTR pszText) CONST
{
	CString  szResult;

	szResult = pszText + ConvertUIntToString(n);
	return szResult;
}
CString CStringTools::AddUIntToString(UINT n, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertUIntToString(n, nRadix);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}

CString CStringTools::AddLongUIntToString(ULONGLONG n, LPCTSTR pszText) CONST
{
	CString  szResult;

	szResult = pszText + ConvertLongUIntToString(n);
	return szResult;
}
CString CStringTools::AddLongUIntToString(ULONGLONG n, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertLongUIntToString(n, nRadix);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}

CString CStringTools::AddFloatToString(double f, LPCTSTR pszText) CONST
{
	CString  szResult;

	szResult = pszText + ConvertFloatToString(f);
	return szResult;
}
CString CStringTools::AddFloatToString(double f, LPCTSTR pszText, INT nDigits) CONST
{
	CString  szResult;

	szResult = pszText + ConvertFloatToString(f, nDigits);
	return szResult;
}
CString CStringTools::AddFloatToString(double f, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertFloatToString(f);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}
CString CStringTools::AddFloatToString(double f, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertFloatToString(f, nDigits);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}

CString CStringTools::AddFloatToTruncatedString(double f, LPCTSTR pszText) CONST
{
	CString  szResult;

	szResult = pszText + ConvertFloatToTruncatedString(f);
	return szResult;
}
CString CStringTools::AddFloatToTruncatedString(double f, LPCTSTR pszText, INT nDigits) CONST
{
	CString  szResult;

	szResult = pszText + ConvertFloatToTruncatedString(f, nDigits);
	return szResult;
}
CString CStringTools::AddFloatToTruncatedString(double f, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertFloatToTruncatedString(f);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}
CString CStringTools::AddFloatToTruncatedString(double f, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertFloatToTruncatedString(f, nDigits);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}

CString CStringTools::AddIntToPaddedString(INT n, LPCTSTR pszText, INT nDigits) CONST
{
	CString  szResult;

	szResult = pszText + ConvertIntToPaddedString(n, nDigits);
	return szResult;
}
CString CStringTools::AddIntToPaddedString(INT n, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertIntToPaddedString(n, nDigits, nRadix);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}

CString CStringTools::AddLongIntToPaddedString(LONGLONG n, LPCTSTR pszText, INT nDigits) CONST
{
	CString  szResult;

	szResult = pszText + ConvertLongIntToPaddedString(n, nDigits);
	return szResult;
}
CString CStringTools::AddLongIntToPaddedString(LONGLONG n, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertLongIntToPaddedString(n, nDigits, nRadix);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}

CString CStringTools::AddUIntToPaddedString(UINT n, LPCTSTR pszText, INT nDigits) CONST
{
	CString  szResult;

	szResult = pszText + ConvertUIntToPaddedString(n, nDigits);
	return szResult;
}
CString CStringTools::AddUIntToPaddedString(UINT n, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertUIntToPaddedString(n, nDigits, nRadix);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}

CString CStringTools::AddLongUIntToPaddedString(ULONGLONG n, LPCTSTR pszText, INT nDigits) CONST
{
	CString  szResult;

	szResult = pszText + ConvertLongUIntToPaddedString(n, nDigits);
	return szResult;
}
CString CStringTools::AddLongUIntToPaddedString(ULONGLONG n, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST
{
	CString  szResult;

	szResult = pszText;
	szResult += (AfxIsValidString(pszProlog)) ? pszProlog : EMPTYSTRING;
	szResult += ConvertLongUIntToPaddedString(n, nDigits, nRadix);
	szResult += (AfxIsValidString(pszEpilog)) ? pszEpilog : EMPTYSTRING;
	return szResult;
}


/////////////////////////////////////////////////////////////////////////////
// CFileEx

CFileEx::CFileEx() : CFile()
{
	return;
}
CFileEx::CFileEx(HANDLE hFile) : CFile(hFile)
{
	return;
}
CFileEx::CFileEx(LPCTSTR pszFileName, UINT nOpenFlags) : CFile(TranslateToUNCName(pszFileName), nOpenFlags)
{
	return;
}

BOOL CFileEx::Open(LPCTSTR pszFileName, UINT nOpenFlags, CFileException *pError)
{
	return CFile::Open(TranslateToUNCName(pszFileName), nOpenFlags, pError);
}

BOOL CFileEx::SetAttributes(LPCTSTR pszFileName, DWORD dwAttributes)
{
	return SetFileAttributes(TranslateToUNCName(pszFileName), dwAttributes);
}

DWORD CFileEx::GetAttributes(LPCTSTR pszFileName)
{
	return GetFileAttributes(TranslateToUNCName(pszFileName));
}

BOOL CFileEx::SetStatus(LPCTSTR pszFileName, CONST CFileStatus &status)
{
	try
	{
		CFile::SetStatus(TranslateToUNCName(pszFileName), status);
		return TRUE;
	}
	catch (CException *pException)
	{
		pException->Delete();
	}
	return FALSE;
}

BOOL CFileEx::GetStatus(LPCTSTR pszFileName, CFileStatus &status)
{
	return CFile::GetStatus(TranslateToUNCName(pszFileName), status);
}
BOOL CFileEx::GetStatus(CFileStatus &status) CONST
{
	return CFile::GetStatus(status);
}

BOOL CFileEx::Move(LPCTSTR pszOldName, LPCTSTR pszNewName, DWORD dwFlags)
{
	return MoveFileEx(TranslateToUNCName(pszOldName), TranslateToUNCName(pszNewName), dwFlags);
}

BOOL CFileEx::Copy(LPCTSTR pszOldName, LPCTSTR pszNewName, BOOL bOverwrite)
{
	return CopyFile(TranslateToUNCName(pszOldName), TranslateToUNCName(pszNewName), !bOverwrite);
}

BOOL CFileEx::Rename(LPCTSTR pszOldName, LPCTSTR pszNewName)
{
	try
	{
		CFile::Rename(TranslateToUNCName(pszOldName), TranslateToUNCName(pszNewName));
		return TRUE;
	}
	catch (CException *pException)
	{
		pException->Delete();
	}
	return FALSE;
}

BOOL CFileEx::Remove(LPCTSTR pszFileName)
{
	try
	{
		CFile::Remove(TranslateToUNCName(pszFileName));
		return TRUE;
	}
	catch (CException *pException)
	{
		pException->Delete();
	}
	return FALSE;
}

CString CFileEx::TranslateToUNCName(LPCTSTR pszFileName)
{
	DWORD  cbSize;
	TCHAR  szUNCInfo[1024];
	CString  szFileName[2];
	UNIVERSAL_NAME_INFO  *pUNCName;

	if (WNetGetUniversalName((szFileName[0] = pszFileName), UNIVERSAL_NAME_INFO_LEVEL, (pUNCName = (UNIVERSAL_NAME_INFO *)szUNCInfo), &(cbSize = sizeof(szUNCInfo))) == NO_ERROR)
	{
		szFileName[1] = pUNCName->lpUniversalName;
		return szFileName[1];
	}
	return szFileName[0];
}


/////////////////////////////////////////////////////////////////////////////
// CLongUIntArray

CLongUIntArray::CLongUIntArray() : CArray<ULONGLONG>()
{
	return;
}
CLongUIntArray::CLongUIntArray(CONST CLongUIntArray &nArray) : CArray<ULONGLONG>()
{
	Copy(nArray);
}
CLongUIntArray::CLongUIntArray(CONST CUIntArray &nArray) : CArray<ULONGLONG>()
{
	INT_PTR  nIndex;
	INT_PTR  nCount;

	for (nIndex = 0, nCount = nArray.GetSize(); nIndex < nCount; nIndex++)
	{
		Add(nArray.GetAt(nIndex));
		continue;
	}
}

CLongUIntArray &CLongUIntArray::operator=(CONST CUIntArray &nArray)
{
	INT_PTR  nIndex;
	INT_PTR  nCount;

	for (nIndex = 0, nCount = nArray.GetSize(), RemoveAll(); nIndex < nCount; nIndex++)
	{
		Add(nArray.GetAt(nIndex));
		continue;
	}
	return *this;
}

BOOL CLongUIntArray::operator==(CONST CUIntArray &nArray) CONST
{
	INT_PTR  nIndex;
	INT_PTR  nCount;

	for (nIndex = 0, nCount = (nArray.GetSize() == GetSize()) ? nArray.GetSize() : -1; nIndex < nCount; nIndex++)
	{
		if (nArray.GetAt(nIndex) != GetAt(nIndex)) break;
		continue;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL CLongUIntArray::operator!=(CONST CUIntArray &nArray) CONST
{
	INT_PTR  nIndex;
	INT_PTR  nCount;

	for (nIndex = 0, nCount = (nArray.GetSize() == GetSize()) ? nArray.GetSize() : -1; nIndex < nCount; nIndex++)
	{
		if (nArray.GetAt(nIndex) != GetAt(nIndex)) break;
		continue;
	}
	return((nIndex != nCount) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CFloatArray

CFloatArray::CFloatArray() : CArray<double>()
{
	return;
}
CFloatArray::CFloatArray(CONST CFloatArray &nArray) : CArray<double>()
{
	Copy(nArray);
}


/////////////////////////////////////////////////////////////////////////////
// CFileFindEx

CFileFindEx::CFileFindEx() : CFileFind()
{
	return;
}

BOOL CFileFindEx::FindFile(LPCTSTR pszFileName)
{
	return CFileFind::FindFile(CFileEx::TranslateToUNCName(pszFileName));
}


/////////////////////////////////////////////////////////////////////////////
// CLogicalDrives

CLogicalDrives::CLogicalDrives() : CObject()
{
	CString  szFile;
	CString  szDrive;
	CStringArray  szDrives;
	CFileFindEx  cFileFind;
	CModuleToken  cModuleToken;

	for (m_szDelimiter[0] = m_szDelimiter[1] = m_szDelimiter[2] = EOS; EnumDrives(szDrives) > 0; )
	{
		szDrive = szDrives.GetAt(szDrives.GetUpperBound());
		m_szDelimiter[0] = szDrive.GetAt(szDrive.GetLength() - 1 - 1);
		m_szDelimiter[1] = szDrive.GetAt(szDrive.GetLength() - 1);
		break;
	}
	if (cFileFind.FindFile(cModuleToken.GetModuleName()) && !cFileFind.FindNextFile())
	{
		m_szDelimiter[2] = cFileFind.GetFileName().GetAt(cFileFind.GetFileTitle().GetLength());
		cFileFind.Close();
	}
}

INT CLogicalDrives::EnumDrives(CStringArray &szDrives) CONST
{
	DWORD  cbDrives[2];
	TCHAR  szDriveStrings[1024];

	for (cbDrives[0] = GetLogicalDriveStrings(sizeof(szDriveStrings) / sizeof(TCHAR), szDriveStrings), cbDrives[1] = 0, szDrives.RemoveAll(); cbDrives[1] < cbDrives[0]; cbDrives[1] += lstrlen(szDriveStrings + cbDrives[1]) + 1)
	{
		szDrives.Add(szDriveStrings + cbDrives[1]);
		continue;
	}
	return((INT)szDrives.GetSize());
}

CString CLogicalDrives::ExtractDrive(LPCTSTR pszFileName) CONST
{
	INT  nPos;
	INT  nCount;
	INT  nDrive;
	INT  nDrives;
	CString  szDrive;
	CString  szDirectory;
	CStringArray  szDrives;
	CModuleToken  cModuleToken;

	for (nDrive = 0, nDrives = EnumDrives(szDrives); nDrive < nDrives; nDrive++)
	{
		if (!_tcsnicmp(pszFileName, szDrives.GetAt(nDrive), szDrives.GetAt(nDrive).GetLength() - 1)) break;
		continue;
	}
	if (nDrive < nDrives)
	{
		szDrive = szDrives.GetAt(nDrive);
		return szDrive;
	}
	for (nPos = (!_tcsncmp(pszFileName, STRING(IDS_LOCALNET_DELIMITER), lstrlen(STRING(IDS_LOCALNET_DELIMITER)))) ? lstrlen(STRING(IDS_LOCALNET_DELIMITER)) : -1, nCount = 0; nPos < lstrlen(pszFileName) && nPos >= 0; nPos++)
	{
		if (pszFileName[nPos] == GetPathDelimiter())
		{
			if (!nCount)
			{
				nCount++;
				continue;
			}
			szDirectory = CString(pszFileName).Left(nPos + 1);
			break;
		}
		if (nPos == lstrlen(pszFileName) - 1 && nCount > 0)
		{
			szDirectory = CString(pszFileName) + GetPathDelimiter();
			break;
		}
	}
	return((szDirectory.IsEmpty()) ? ((_tcsnicmp(cModuleToken.GetModuleFileRoot(), pszFileName, cModuleToken.GetModuleFileRoot().GetLength()) && !_tcsstr(pszFileName, CString(GetDriveDelimiter()))) ? (LPCTSTR)ExtractDrive(cModuleToken.GetModuleFileRoot()) : EMPTYSTRING) : szDirectory);
}

BOOL CLogicalDrives::IsDrive(LPCTSTR pszDrive) CONST
{
	INT  nDrive;
	INT  nDrives;
	CStringArray  szDrives;

	for (nDrive = 0, nDrives = EnumDrives(szDrives); nDrive < nDrives; nDrive++)
	{
		if (!_tcsnicmp(pszDrive, szDrives.GetAt(nDrive), szDrives.GetAt(nDrive).GetLength() - 1)) break;
		continue;
	}
	return((nDrive < nDrives) ? TRUE : FALSE);
}

double CLogicalDrives::GetFreeDriveSpace(LPCTSTR pszFileName) CONST
{
	DWORDLONG  dwDiskSpace[2];
	ULARGE_INTEGER  nDiskSpace[3];

	if (GetDiskFreeSpaceEx(ExtractDrive(pszFileName), &nDiskSpace[0], &nDiskSpace[1], &nDiskSpace[2]))
	{
		dwDiskSpace[0] = ((DWORDLONG)nDiskSpace[0].HighPart << 32) + nDiskSpace[0].LowPart;
		dwDiskSpace[1] = ((DWORDLONG)nDiskSpace[1].HighPart << 32) + nDiskSpace[1].LowPart;
		return((double)dwDiskSpace[0] / (double)dwDiskSpace[1]);
	}
	return(-1.0);
}

DWORDLONG CLogicalDrives::GetFreeDriveBytes(LPCTSTR pszFileName) CONST
{
	ULARGE_INTEGER  nDiskSpace[3];

	return((GetDiskFreeSpaceEx(ExtractDrive(pszFileName), &nDiskSpace[0], &nDiskSpace[1], &nDiskSpace[2])) ? (((DWORDLONG)nDiskSpace[0].HighPart << 32) + nDiskSpace[0].LowPart) : (DWORDLONG)-1);
}

TCHAR CLogicalDrives::GetDriveDelimiter() CONST
{
	return m_szDelimiter[0];
}

TCHAR CLogicalDrives::GetPathDelimiter() CONST
{
	return m_szDelimiter[1];
}

TCHAR CLogicalDrives::GetFileExtensionDelimiter() CONST
{
	return m_szDelimiter[2];
}


/////////////////////////////////////////////////////////////////////////////
// CIdle

CIdle::CIdle() : CObject()
{
	m_dwLastTime = 0;
	m_dwInterval = 0;
	DoIdleProcessing();
}
CIdle::CIdle(DWORD dwInterval) : CObject()
{
	m_dwLastTime = 0;
	m_dwInterval = dwInterval;
	DoIdleProcessing();
}

CIdle::~CIdle()
{
	DoIdleProcessing();
}

VOID CIdle::DoIdleProcessing()
{
	MSG  sMsg;
	DWORD  dwLastTime;

	if (((dwLastTime = GetTickCount()) >= m_dwLastTime  &&  dwLastTime - m_dwLastTime >= m_dwInterval) || (dwLastTime < m_dwLastTime  &&  UINT_MAX - m_dwLastTime + dwLastTime + 1 >= m_dwInterval))
	{
		for (PeekMessage(&sMsg, (HWND)NULL, 0, 0, PM_NOREMOVE); PeekMessage(&sMsg, (HWND)NULL, 0, 0, PM_QS_PAINT | PM_REMOVE) || PeekMessage(&sMsg, (HWND)NULL, WM_MEASUREITEM, WM_MEASUREITEM, PM_REMOVE) || PeekMessage(&sMsg, (HWND)NULL, WM_DRAWITEM, WM_DRAWITEM, PM_REMOVE); )
		{
			TranslateMessage(&sMsg);
			DispatchMessage(&sMsg);
		}
		m_dwLastTime = GetTickCount();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CUpdateUI

CUpdateUI::CUpdateUI() : CObject()
{
	return;
}

CUpdateUI::~CUpdateUI()
{
	CWnd  *pWnd;
	CLocaleFrameWnd  *pLocaleFrameWnd;
	CLocaleMDIFrameWnd  *pLocaleMDIFrameWnd;

	if ((pWnd = GetLocaleApp()->GetMainWnd()))
	{
		if ((pLocaleFrameWnd = (pWnd->IsKindOf(RUNTIME_CLASS(CLocaleFrameWnd))) ? (CLocaleFrameWnd *)pWnd : (CLocaleFrameWnd *)NULL))
		{
			pLocaleFrameWnd->DoUpdateUI();
			return;
		}
		if ((pLocaleMDIFrameWnd = (pWnd->IsKindOf(RUNTIME_CLASS(CLocaleMDIFrameWnd))) ? (CLocaleMDIFrameWnd *)pWnd : (CLocaleMDIFrameWnd *)NULL))
		{
			pLocaleMDIFrameWnd->DoUpdateUI();
			return;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// CHourglassCursor

CHourglassCursor::CHourglassCursor() : CWaitCursor()
{
	return;
}

CHourglassCursor::~CHourglassCursor()
{
	POINT  ptCursor;

	GetCursorPos(&ptCursor);
	SetCursorPos(ptCursor.x, ptCursor.y);
};
