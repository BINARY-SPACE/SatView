// TOOLS.H : Tools Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the tools related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/10/15 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TOOLS_H__
#define __TOOLS_H__


/////////////////////////////////////////////////////////////////////////////
// CCompressionTools

class AFX_EXT_CLASS CCompressionTools : public CObject
{
	// Construction
public:
	CCompressionTools();

	// Attributes
public:

	// Operations
public:
	INT Compress(CONST CByteArray &nData, CByteArray &nCompressedData) CONST;
	BOOL Decompress(CONST CByteArray &nCompressedData, CByteArray &nData) CONST;
	INT CompressText(LPCTSTR pszText, CByteArray &nCompressedData) CONST;
	BOOL DecompressText(CONST CByteArray &nCompressedData, CString &szText) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCryptographyTools

class AFX_EXT_CLASS CCryptographyTools : public CObject
{
	// Construction
public:
	CCryptographyTools();

	// Attributes
private:
	CByteArray  m_nBaseData;

	// Operations
public:
	VOID SetBaseData(LPCTSTR pszBaseData);
	CString GetBaseData() CONST;

	INT Encrypt(CONST CByteArray &nData, CByteArray &nEncryptedData) CONST;
	BOOL Decrypt(CONST CByteArray &nEncryptedData, CByteArray &nData) CONST;
	INT EncryptText(LPCTSTR pszText, CByteArray &nEncryptedData) CONST;
	BOOL DecryptText(CONST CByteArray &nEncryptedData, CString &szText) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CFontTools

class AFX_EXT_CLASS CFontTools : public CObject
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

class AFX_EXT_CLASS CStringTools : public CObject
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
// CLongUIntArray

class AFX_EXT_CLASS CLongUIntArray : public CArray<ULONGLONG>
{
	// Construction
public:
	CLongUIntArray();
	CLongUIntArray(CONST CLongUIntArray &nArray);
	CLongUIntArray(CONST CUIntArray &nArray);

	// Attributes
public:

	// Operations
public:
	CLongUIntArray &operator=(CONST CUIntArray &nArray);
	BOOL operator==(CONST CUIntArray &nArray) CONST;
	BOOL operator!=(CONST CUIntArray &nArray) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CFloatArray

class AFX_EXT_CLASS CFloatArray : public CArray<double>
{
	// Construction
public:
	CFloatArray();
	CFloatArray(CONST CFloatArray &nArray);

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CFileEx

class AFX_EXT_CLASS CFileEx : public CFile
{
	// Construction
public:
	CFileEx();
	CFileEx(HANDLE hFile);
	CFileEx(LPCTSTR pszFileName, UINT nOpenFlags);

	// Attributes
public:

	// Operations
public:
	virtual BOOL Open(LPCTSTR pszFileName, UINT nOpenFlags, CFileException *pError = NULL);

	BOOL GetStatus(CFileStatus &status) CONST;

public:
	static BOOL SetAttributes(LPCTSTR pszFileName, DWORD dwAttributes);
	static DWORD GetAttributes(LPCTSTR pszFileName);
	static BOOL SetStatus(LPCTSTR pszFileName, CONST CFileStatus &status);
	static BOOL GetStatus(LPCTSTR pszFileName, CFileStatus &status);

	static BOOL Move(LPCTSTR pszOldName, LPCTSTR pszNewName, DWORD dwFlags = MOVEFILE_REPLACE_EXISTING);
	static BOOL Copy(LPCTSTR pszOldName, LPCTSTR pszNewName, BOOL bOverwrite = TRUE);
	static BOOL Rename(LPCTSTR pszOldName, LPCTSTR pszNewName);
	static BOOL Remove(LPCTSTR pszFileName);

	static CString TranslateToUNCName(LPCTSTR pszFileName);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CFileFindEx

class AFX_EXT_CLASS CFileFindEx : public CFileFind
{
	// Construction
public:
	CFileFindEx();

	// Attributes
public:

	// Operations
public:
	virtual BOOL FindFile(LPCTSTR pszFileName = NULL);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLogicalDrives

class AFX_EXT_CLASS CLogicalDrives : public CObject
{
	// Construction
public:
	CLogicalDrives();

	// Attributes
private:
	TCHAR  m_szDelimiter[3];

	// Operations
public:
	INT EnumDrives(CStringArray &szDrives) CONST;
	CString ExtractDrive(LPCTSTR pszFileName) CONST;
	BOOL IsDrive(LPCTSTR pszDrive) CONST;

	double GetFreeDriveSpace(LPCTSTR pszFileName) CONST;
	DWORDLONG GetFreeDriveBytes(LPCTSTR pszFileName) CONST;

	TCHAR GetDriveDelimiter() CONST;
	TCHAR GetPathDelimiter() CONST;
	TCHAR GetFileExtensionDelimiter() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CIdle

class AFX_EXT_CLASS CIdle : public CObject
{
	// Construction
public:
	CIdle();
	CIdle(DWORD dwInterval);
	~CIdle();

	// Attributes
private:
	DWORD  m_dwInterval;
	DWORD  m_dwLastTime;

	// Operations
public:
	VOID DoIdleProcessing();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUpdateUI

class AFX_EXT_CLASS CUpdateUI : public CObject
{
	// Construction
public:
	CUpdateUI();
	~CUpdateUI();

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHourglassCursor

class AFX_EXT_CLASS CHourglassCursor : public CWaitCursor
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


#endif // __TOOLS_H__
