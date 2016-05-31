// MIMICSTOOLS.H : Mimics Tools Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics tools related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/22 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSTOOLS_H__
#define __MIMICSTOOLS_H__


/////////////////////////////////////////////////////////////////////////////
// CFontTools

class CFontTools : public CObject
{
	// Construction
public:
	CFontTools();
	CFontTools(CFont *pFont);
	CFontTools(LOGFONT *plf);
	CFontTools(INT nType, LOGFONT *plf);

	// Attributes
public:

	// Operations
public:
	INT EnumerateFonts(CStringArray &szFonts) CONST;
	INT EnumerateFonts(CDC *pDC, CStringArray &szFonts) CONST;
	BOOL EnumerateFont(LPCTSTR pszFont, CStringArray &szStyles, CStringArray &szSizes, BOOL &bUnderlined) CONST;
	BOOL EnumerateFont(CDC *pDC, LPCTSTR pszFont, CStringArray &szStyles, CStringArray &szSizes, BOOL &bUnderlined) CONST;
	BOOL EnumerateFontCharacteristics(LOGFONT *plf) CONST;
	BOOL EnumerateFontCharacteristics(CDC *pDC, LOGFONT *plf) CONST;

	CString TranslateFontStyle(CONST LOGFONT *plf) CONST;
	VOID TranslateFontStyle(LPCTSTR pszStyle, LONG &lWeight, BYTE &bItalic) CONST;
	CString TranslateFontSize(CONST LOGFONT *plf) CONST;
	VOID TranslateFontSize(LPCTSTR pszSize, LONG &lHeight) CONST;

	BOOL QueryDefaultFont(CFont *pFont) CONST;
	BOOL QueryDefaultFont(LOGFONT *plf) CONST;
	BOOL QueryStockFont(INT nType, LOGFONT *plf) CONST;

	INT QueryPoints(CFont *pFont) CONST;
	INT QueryPoints(CONST LOGFONT *plf) CONST;
	INT QueryPoints(CDC *pDC, CFont *pFont) CONST;
	INT QueryPoints(CDC *pDC, CONST LOGFONT *plf) CONST;

	INT QueryPixels(INT nPts) CONST;
	INT QueryPixels(CDC *pDC, INT nPts) CONST;

	INT QueryHeight(CONST LOGFONT *plf) CONST;
	INT QueryHeight(CDC *pDC, CONST LOGFONT *plf) CONST;

private:
	static INT CALLBACK EnumerateFontsProc(ENUMLOGFONTEX *plf, NEWTEXTMETRICEX *ptm, DWORD nFontType, LPARAM lParam);
	static INT CALLBACK EnumerateFontStylesProc(ENUMLOGFONTEX *plf, NEWTEXTMETRICEX *ptm, DWORD nFontType, LPARAM lParam);
	static INT CALLBACK EnumerateFontSizesProc(ENUMLOGFONTEX *plf, NEWTEXTMETRICEX *ptm, DWORD nFontType, LPARAM lParam);
	static INT CALLBACK EnumerateFontUnderlinedProc(ENUMLOGFONTEX *plf, NEWTEXTMETRICEX *ptm, DWORD nFontType, LPARAM lParam);
	static INT CALLBACK EnumerateFontCharacteristicsProc(ENUMLOGFONTEX *plf, NEWTEXTMETRICEX *ptm, DWORD nFontType, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CStringTools

class CStringTools : public CObject
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	CString ConvertIntToString(INT n) CONST;
	CString ConvertIntToString(INT n, INT nRadix) CONST;
	CString ConvertLongIntToString(LONGLONG n) CONST;
	CString ConvertLongIntToString(LONGLONG n, INT nRadix) CONST;
	CString ConvertUIntToString(UINT n) CONST;
	CString ConvertUIntToString(UINT n, INT nRadix) CONST;
	CString ConvertLongUIntToString(ULONGLONG n) CONST;
	CString ConvertLongUIntToString(ULONGLONG n, INT nRadix) CONST;
	CString ConvertFloatToString(double f) CONST;
	CString ConvertFloatToString(double f, INT nDigits) CONST;
	CString ConvertFloatToTruncatedString(double f) CONST;
	CString ConvertFloatToTruncatedString(double f, INT nDigits) CONST;
	CString ConvertIntToPaddedString(INT n, INT nDigits) CONST;
	CString ConvertIntToPaddedString(INT n, INT nDigits, INT nRadix) CONST;
	CString ConvertLongIntToPaddedString(LONGLONG n, INT nDigits) CONST;
	CString ConvertLongIntToPaddedString(LONGLONG n, INT nDigits, INT nRadix) CONST;
	CString ConvertUIntToPaddedString(UINT n, INT nDigits) CONST;
	CString ConvertUIntToPaddedString(UINT n, INT nDigits, INT nRadix) CONST;
	CString ConvertLongUIntToPaddedString(ULONGLONG n, INT nDigits) CONST;
	CString ConvertLongUIntToPaddedString(ULONGLONG n, INT nDigits, INT nRadix) CONST;
	CString ConvertIntToStructuredString(INT n) CONST;
	CString ConvertLongIntToStructuredString(LONGLONG n) CONST;
	CString ConvertUIntToStructuredString(UINT n) CONST;
	CString ConvertLongUIntToStructuredString(ULONGLONG n) CONST;

	CString AddIntToString(INT n, LPCTSTR pszText) CONST;
	CString AddIntToString(INT n, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST;
	CString AddLongIntToString(LONGLONG n, LPCTSTR pszText) CONST;
	CString AddLongIntToString(LONGLONG n, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST;
	CString AddUIntToString(UINT n, LPCTSTR pszText) CONST;
	CString AddUIntToString(UINT n, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST;
	CString AddLongUIntToString(ULONGLONG n, LPCTSTR pszText) CONST;
	CString AddLongUIntToString(ULONGLONG n, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST;
	CString AddFloatToString(double f, LPCTSTR pszText) CONST;
	CString AddFloatToString(double f, LPCTSTR pszText, INT nDigits) CONST;
	CString AddFloatToString(double f, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog) CONST;
	CString AddFloatToString(double f, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog) CONST;
	CString AddFloatToTruncatedString(double f, LPCTSTR pszText) CONST;
	CString AddFloatToTruncatedString(double f, LPCTSTR pszText, INT nDigits) CONST;
	CString AddFloatToTruncatedString(double f, LPCTSTR pszText, LPCTSTR pszProlog, LPCTSTR pszEpilog) CONST;
	CString AddFloatToTruncatedString(double f, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog) CONST;
	CString AddIntToPaddedString(INT n, LPCTSTR pszText, INT nDigits) CONST;
	CString AddIntToPaddedString(INT n, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST;
	CString AddLongIntToPaddedString(LONGLONG n, LPCTSTR pszText, INT nDigits) CONST;
	CString AddLongIntToPaddedString(LONGLONG n, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST;
	CString AddUIntToPaddedString(UINT n, LPCTSTR pszText, INT nDigits) CONST;
	CString AddUIntToPaddedString(UINT n, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST;
	CString AddLongUIntToPaddedString(ULONGLONG n, LPCTSTR pszText, INT nDigits) CONST;
	CString AddLongUIntToPaddedString(ULONGLONG n, LPCTSTR pszText, INT nDigits, LPCTSTR pszProlog, LPCTSTR pszEpilog, INT nRadix) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHourglassCursor

class CHourglassCursor : public CWaitCursor
{
	// Construction
public:
	CHourglassCursor();
	~CHourglassCursor();

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSTOOLS_H__
