// MIMICSTOOLS.CPP : Mimics Tools Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics tools
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/22 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



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
