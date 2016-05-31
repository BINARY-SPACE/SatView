// HEX.H : Hexadecimal Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the hexadecimal display related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/25 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __HEX_H__
#define __HEX_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CHEXPrintJobInfo

class CHEXPrintJobInfo : public CObject
{
	// Construction
public:
	CHEXPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbEvent;
		INT  cbProfile;
		INT  cbComments;
		UINT  nPrintMode;
		UINT  nPrintCount[2];
		UINT  nPrintByCount[2];
		UINT  nRepeatStopByCount[2];
		TIMEKEY  tPrintAtTime;
		TIMEKEY  tPrintAtDailyTime;
		TIMEKEY  tPrintLastTime[2];
		TIMEKEY  tRepeatInterval;
		TIMEKEY  tRepeatStopByTime[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szEvent;
	CString  m_szProfile;
	CString  m_szComments;
	UINT  m_nPrintMode;
	UINT  m_nPrintFlags;
	UINT  m_nPrintCount[2];
	UINT  m_nPrintByCount[2];
	UINT  m_nRepeatStopByCount[2];
	CTimeKey  m_tPrintAtTime;
	CTimeKey  m_tPrintLastTime[2];
	CTimeKey  m_tRepeatStopByTime[2];
	CTimeSpan  m_tPrintAtDailyTime;
	CTimeSpan  m_tRepeatInterval;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetProfile(LPCTSTR pszProfile);
	CString GetProfile() CONST;
	VOID SetComments(LPCTSTR pszComments);
	CString GetComments() CONST;

	BOOL SetPrintMode(UINT nMode);
	UINT GetPrintMode() CONST;
	BOOL SetPrintFlags(UINT nFlags);
	UINT GetPrintFlags() CONST;
	BOOL SetPrintBySide(UINT nDataCount, UINT nSpyCount);
	BOOL GetPrintBySide(UINT &nDataCount, UINT &nSpyCount) CONST;
	BOOL SetPrintAtTime(CONST CTimeKey &tTime);
	BOOL SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval);
	BOOL SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, UINT nStopCount);
	BOOL SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime);
	BOOL GetPrintAtTime(CTimeKey &tTime) CONST;
	BOOL GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval) CONST;
	BOOL GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, UINT &nStopCount) CONST;
	BOOL GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	BOOL SetPrintAtDailyTime(CONST CTimeSpan &tTime);
	BOOL SetPrintAtDailyTime(CONST CTimeSpan &tTime, UINT nStopCount);
	BOOL SetPrintAtDailyTime(CONST CTimeSpan &tTime, CONST CTimeKey &tStopTime);
	BOOL GetPrintAtDailyTime(CTimeSpan &tTime) CONST;
	BOOL GetPrintAtDailyTime(CTimeSpan &tTime, UINT &nStopCount) CONST;
	BOOL GetPrintAtDailyTime(CTimeSpan &tTime, CTimeKey &tStopTime) CONST;
	BOOL SetPrintAtEvent(LPCTSTR pszEvent);
	BOOL GetPrintAtEvent(CString &szEvent) CONST;
	BOOL SetPrintCount(UINT nCount);
	BOOL GetPrintCount(UINT &nCount) CONST;
	BOOL SetPrintDailyCount(UINT nCount);
	BOOL GetPrintDailyCount(UINT &nCount) CONST;
	BOOL SetPrintLastTime(CONST CTimeKey &tTime);
	BOOL GetPrintLastTime(CTimeKey &tTime) CONST;
	BOOL SetPrintLastDailyTime(CONST CTimeKey &tTime);
	BOOL GetPrintLastDailyTime(CTimeKey &tTime) CONST;

	VOID Copy(CONST CHEXPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CHEXPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXPrintJobs

class CHEXPrintJobs : public CPtrArray
{
	// Construction
public:
	CHEXPrintJobs();
	~CHEXPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CHEXPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CHEXPrintJobInfo *GetAt(INT nIndex) CONST;
	CHEXPrintJobInfo *operator[](INT nIndex) CONST;

	TIMEKEY Schedule();

	VOID RemoveAll();

	BOOL Copy(CONST CHEXPrintJobs *pPrintJobs);
	BOOL Compare(CONST CHEXPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSpyLocation

// Specify the hexadecimal spy location coding types
#define HEXSPYLOCATION_CODING_BINARY   2
#define HEXSPYLOCATION_CODING_OCTAL   8
#define HEXSPYLOCATION_CODING_DECIMAL   10
#define HEXSPYLOCATION_CODING_HEXADECIMAL   16
#define HEXSPYLOCATION_CODING_DEFAULT   HEXSPYLOCATION_CODING_HEXADECIMAL

class CHEXSpyLocation : public CObject
{
	// Construction
public:
	CHEXSpyLocation();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		UINT  nByte;
		UINT  nBit;
		UINT  nLength;
		UINT  nCoding;
		COLORREF  nColor[2];
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nByte;
	UINT  m_nBit;
	UINT  m_nLength;
	UINT  m_nCoding;
	COLORREF  m_nColor[2];
	CString  m_szName;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	BOOL SetPosition(UINT nByte, UINT nBit, UINT nLength);
	BOOL GetPosition(UINT &nByte, UINT &nBit, UINT &nLength) CONST;
	BOOL SetCoding(UINT nCoding);
	UINT GetCoding() CONST;
	VOID SetDetailsColor(COLORREF nColor);
	COLORREF GetDetailsColor() CONST;
	VOID SetValueColor(COLORREF nColor);
	COLORREF GetValueColor() CONST;

	VOID Copy(CONST CHEXSpyLocation *pLocation);
	BOOL Compare(CONST CHEXSpyLocation *pLocation) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSpyLocations

class CHEXSpyLocations : public CPtrArray
{
	// Construction
public:
	CHEXSpyLocations();
	~CHEXSpyLocations();

	// Attributes
public:

	// Operations
public:
	INT Add(CHEXSpyLocation *pLocation);

	INT Find(LPCTSTR pszName) CONST;

	CHEXSpyLocation *GetAt(INT nIndex) CONST;
	CHEXSpyLocation *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CHEXSpyLocations *pLocations);
	BOOL Compare(CONST CHEXSpyLocations *pLocations) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsLayoutPage dialog

#define IDC_HEXSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_LINELENGTH_PHRASEBEGIN   1003
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_LINELENGTH   1004
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_LINELENGTH_PHRASEEND   1005
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS_PHRASEBEGIN   1006
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORSTEXT   1007
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS_PHRASEEND   1008
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS   1009
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES   1010
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_PHRASEBEGIN   1011
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_INTERVAL   1012
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_PHRASEEND   1013
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS   1014
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_PHRASEBEGIN   1015
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_INTERVAL   1016
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_PHRASEEND   1017
#define IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_BADDATA   1018
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS   1019
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1020
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1021
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA   1022
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_STATIC   1023
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER   1024
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS   1025
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1026
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1027
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES   1028
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1029
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE   1030
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1031
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE   1032
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1033
#define IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1034

// Specify the hexadecimal display settings layout page related limits
#define HEXSETTINGSLAYOUTPAGE_LINE_MINIMUMLENGTH   1
#define HEXSETTINGSLAYOUTPAGE_LINE_MAXIMUMLENGTH   1024
#define HEXSETTINGSLAYOUTPAGE_LINE_DEFAULTLENGTH   32
#define HEXSETTINGSLAYOUTPAGE_ENUMERATION_MINIMUMINTERVAL   1
#define HEXSETTINGSLAYOUTPAGE_ENUMERATION_MAXIMUMINTERVAL   1024
#define HEXSETTINGSLAYOUTPAGE_ENUMERATION_DEFAULTINTERVAL   1

class CHEXSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CHEXSettingsLayoutPage)

	// Construction
public:
	CHEXSettingsLayoutPage();

	// Attributes
private:
	CUIntArray  m_nColors[2];
	LOGFONT  m_fntTitle[2];
	LOGFONT  m_fntData[2];
	LOGFONT  m_fntSpy[2][2];
	UINT  m_nEnumeration[2][2];
	UINT  m_nLineLength[2];
	BOOL  m_bBadData[2];
private:
	CString  m_szFontSampleText;

	// Dialog Data
	//{{AFX_DATA(CHEXSettingsLayoutPage)
	enum { IDD = IDD_HEX_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetFormat(UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetDataFont(LPLOGFONT pDataFont) CONST;
	BOOL GetSpyFont(LPLOGFONT pHeaderFont, LPLOGFONT pLocationsFont) CONST;
	BOOL GetBadDataMode(BOOL &bEnable) CONST;

	class CHEXSettingsDialog *GetParentDialog() CONST;
	class CHEXWnd *GetParentDisplay() CONST;

private:
	VOID ShowLayoutFormatInfo(UINT nType);
	VOID ShowLayoutFontDetails();
	VOID ShowLayoutFontSample();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHEXSettingsLayoutPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHEXSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnEnumerateLines();
	afx_msg void OnEnumerateColumns();
	afx_msg void OnBadData();
	afx_msg void OnTitleFont();
	afx_msg void OnDataFont();
	afx_msg void OnSpyHeaderFont();
	afx_msg void OnSpyLocationsFont();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeDataColorText();
	afx_msg void OnSelchangeDataColor();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSpinchangeLineLength();
	afx_msg void OnSpinchangeLineEnumeration();
	afx_msg void OnSpinchangeColumnEnumeration();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsContentsPage dialog

#define IDC_HEXSETTINGS_CONTENTSPAGE_DETAILS   1001
#define IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS_STATIC   1002
#define IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS   1003
#define IDC_HEXSETTINGS_CONTENTSPAGE_ADD   1004
#define IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY   1005
#define IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE   1006
#define IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL   1007
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES   1008
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING   1009
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_HEXADECIMAL   1010
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_DECIMAL   1011
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_OCTAL   1012
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_BINARY   1013
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT_STATIC   1014
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT   1015
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR_STATIC   1016
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR   1017
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION   1018
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BYTE_STATIC   1019
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BYTE   1020
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT_STATIC   1021
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT   1022
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH_STATIC   1023
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH   1024
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION_STATIC   1025
#define IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION   1026

// Specify the hexadecimal display settings contents page related limits
#define HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MINIMUMBIT   0
#define HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MAXIMUMBIT   7
#define HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MINIMUMLENGTH   1
#define HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MAXIMUMLENGTH   32

class CHEXSettingsContentsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CHEXSettingsContentsPage)

	// Construction
public:
	CHEXSettingsContentsPage();

	// Attributes
private:
	CHEXSpyLocations  m_pSpyLocations[2];
	COLORREF  m_nColors[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CHEXSettingsContentsPage)
	enum { IDD = IDD_HEX_SETTINGS_CONTENTSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetSpyLocations(CHEXSpyLocations &pSpyLocations) CONST;

	class CHEXSettingsDialog *GetParentDialog() CONST;
	class CHEXWnd *GetParentDisplay() CONST;

private:
	BOOL EnumSpyLocations();

	VOID SetSpyLocation(CONST CHEXSpyLocation *pLocation = NULL);
	BOOL GetSpyLocation(CHEXSpyLocation *pLocation) CONST;
	CHEXSpyLocation *FindSpyLocation() CONST;
	BOOL CheckSpyLocation() CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHEXSettingsContentsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHEXSettingsContentsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddLocation();
	afx_msg void OnModifyLocation();
	afx_msg void OnRemoveLocation();
	afx_msg void OnRemoveAllLocations();
	afx_msg void OnCodingHexadecimal();
	afx_msg void OnCodingDecimal();
	afx_msg void OnCodingOctal();
	afx_msg void OnCodingBinary();
	afx_msg void OnEditchangeByte();
	afx_msg void OnEditchangeBit();
	afx_msg void OnEditchangeLength();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnSelchangeColorText();
	afx_msg void OnSelchangeColor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsRetrievingPage dialog

#define IDC_HEXSETTINGS_RETRIEVINGPAGE_DETAILS   1001
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC   1002
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE   1003
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_INSPECT   1004
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO   1005
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS   1006
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC   1007
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT   1008
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC   1009
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY   1010
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC   1011
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT   1012
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC   1013
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE   1014
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC   1015
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME   1016
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO   1017
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME   1018
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC   1019
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME   1020
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC   1021
#define IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE   1022

class CHEXSettingsRetrievingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CHEXSettingsRetrievingPage)

	// Construction
public:
	CHEXSettingsRetrievingPage();

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CHEXSettingsRetrievingPage)
	enum { IDD = IDD_HEX_SETTINGS_RETRIEVINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetDataSourceFileName(CString &szFileName) CONST;

	class CHEXSettingsDialog *GetParentDialog() CONST;
	class CHEXWnd *GetParentDisplay() CONST;

private:
	VOID EnumDataSources();
	VOID ShowDataSourceInfo();

	BOOL CheckDataSource(LPCTSTR pszFileName) CONST;
	BOOL CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST;

	CString FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHEXSettingsRetrievingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHEXSettingsRetrievingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnInspect();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeFileName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsPrintingComments window

class CHEXSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CHEXSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsPrintingPage dialog

#define IDC_HEXSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_HEXSETTINGS_PRINTINGPAGE_NAME_STATIC   1002
#define IDC_HEXSETTINGS_PRINTINGPAGE_NAME   1003
#define IDC_HEXSETTINGS_PRINTINGPAGE_ADDNAME   1004
#define IDC_HEXSETTINGS_PRINTINGPAGE_REMOVENAME   1005
#define IDC_HEXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES   1006
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES   1007
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC   1008
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE   1009
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS   1010
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE_STATIC   1011
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE   1012
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL   1013
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE   1014
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE   1015
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC   1016
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT   1017
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS   1018
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS   1019
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC   1020
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT   1021
#define IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS   1022

// Specify the hexadecimal display settings printing page related limits
#define HEXSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMLINES   1
#define HEXSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMLINES   10000
#define HEXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTLINES   25

class CHEXSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CHEXSettingsPrintingPage)

	// Construction
public:
	CHEXSettingsPrintingPage();

	// Attributes
private:
	INT  m_nPrintOptions[2];
	CHEXPrintJobs  m_pJobs[2];
private:
	CHEXSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CHEXSettingsPrintingPage)
	enum { IDD = IDD_HEX_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CHEXPrintJobs &pJobs) CONST;

	class CHEXSettingsDialog *GetParentDialog() CONST;
	class CHEXWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CHEXPrintJobInfo *FindJobInfo() CONST;

	BOOL IsTelemetryDataOptions() CONST;
	BOOL IsSpyLocationsOptions() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHEXSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CHEXPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHEXSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnAddName();
	afx_msg void OnRemoveName();
	afx_msg void OnRemoveAllNames();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnSelchangeChoice();
	afx_msg void OnPrintAll();
	afx_msg void OnPrintBySide();
	afx_msg void OnPrintSpyLocations();
	afx_msg void OnChangePrintSide();
	afx_msg void OnSpinchangePrintSideCount();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsPrintJobsPage dialog

#define IDC_HEXSETTINGS_PRINTJOBSPAGE_DETAILS   1001
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC   1002
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS   1003
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB   1004
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC   1005
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS   1006
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_REMOVEJOB   1007
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR   1008
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME   1009
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME   1010
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME   1011
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC   1012
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME   1013
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT   1014
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT   1015
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC   1016
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION   1017
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC   1018
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE   1019
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME  1020
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC   1021
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME   1022
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC   1023
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES   1024
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC   1025
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES   1026
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME   1027
#define IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME   1028

// Specify the hexadecimal display settings print jobs page related repetition types
#define HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY   1
#define HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY   2
// Specify the hexadecimal display settings print jobs page related limits
#define HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL   1
#define HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL   MINUTESPERHOUR
#define HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES   1
#define HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES   10000
#define HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES   10

class CHEXSettingsPrintJobsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CHEXSettingsPrintJobsPage)

	// Construction
public:
	CHEXSettingsPrintJobsPage();

	// Attributes
private:
	CHEXPrintJobs  m_pJobs[2];

	// Dialog Data
	//{{AFX_DATA(CHEXSettingsPrintJobsPage)
	enum { IDD = IDD_HEX_SETTINGS_PRINTJOBSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CHEXPrintJobs &pJobs) CONST;

	class CHEXSettingsDialog *GetParentDialog() CONST;
	class CHEXWnd *GetParentDisplay() CONST;

private:
	BOOL EnumJobs();
	BOOL EnumEvents();

	VOID ShowJobInfo();
	BOOL CheckJobInfo() CONST;
	CHEXPrintJobInfo *FindJobInfo(BOOL bActive = FALSE) CONST;

	VOID SetJobRepetitionInfo();
	UINT GetJobRepetitionType() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHEXSettingsPrintJobsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CHEXPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHEXSettingsPrintJobsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddJob();
	afx_msg void OnRemoveJob();
	afx_msg void OnSelchangeDefinedJob();
	afx_msg void OnSelchangeActiveJob();
	afx_msg void OnPrintAtTime();
	afx_msg void OnPrintAtDailyTime();
	afx_msg void OnPrintAtEvent();
	afx_msg void OnSelchangeEvent();
	afx_msg void OnSelchangeRepetitionType();
	afx_msg void OnRepeatByTime();
	afx_msg void OnRepetitionStopByCopies();
	afx_msg void OnRepetitionStopByTime();
	afx_msg void OnSpinchangePrintTime();
	afx_msg void OnSpinchangePrintDailyTime();
	afx_msg void OnSpinchangeRepeatTime();
	afx_msg void OnSpinchangeRepetitionStopCopies();
	afx_msg void OnSpinchangeRepetitionStopTime();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsTabCtrl window

class CHEXSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CHEXSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsDialog

class CHEXSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CHEXSettingsDialog)

	// Construction
public:
	CHEXSettingsDialog();

	// Attributes
private:
	CHEXSettingsTabCtrl  m_wndTabCtrl;
	CHEXSettingsLayoutPage  m_pageLayout;
	CHEXSettingsContentsPage  m_pageContents;
	CHEXSettingsRetrievingPage  m_pageRetrieving;
	CHEXSettingsPrintingPage  m_pagePrinting;
	CHEXSettingsPrintJobsPage  m_pagePrintJobs;

	// Operations
public:
	BOOL GetLayoutFormat(UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutDataFont(LPLOGFONT pDataFont) CONST;
	BOOL GetLayoutSpyFont(LPLOGFONT pHeaderFont, LPLOGFONT pLocationsFont) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetSpyLocations(CHEXSpyLocations &pSpyLocations) CONST;
	BOOL IsContentsModified() CONST;

	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CHEXPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CHEXOpenDialog *GetParentDialog() CONST;
	class CHEXWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXSettingsDialog)
public:
	virtual BOOL OnDataExchange(HWND hPage, CONST CHEXPrintJobs &pJobs);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXSettingsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXRetrieveDialog dialog

#define IDC_HEX_RETRIEVE_DETAILS   1001
#define IDC_HEX_RETRIEVE_TITLE_STATIC   1002
#define IDC_HEX_RETRIEVE_TITLE   1003
#define IDC_HEX_RETRIEVE_TYPE_STATIC   1004
#define IDC_HEX_RETRIEVE_TYPE   1005
#define IDC_HEX_RETRIEVE_REALTIME   1006
#define IDC_HEX_RETRIEVE_HISTORY   1007
#define IDC_HEX_RETRIEVE_HISTORY_START_STATIC   1008
#define IDC_HEX_RETRIEVE_HISTORY_STARTTIME   1009
#define IDC_HEX_RETRIEVE_HISTORY_EXACTTIME   1010
#define IDC_HEX_RETRIEVE_HISTORY_STOP_STATIC   1011
#define IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME   1012
#define IDC_HEX_RETRIEVE_HISTORY_STOPTIME   1013
#define IDC_HEX_RETRIEVE_HISTORY_STOPBYEND   1014
#define IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME   1015
#define IDC_HEX_RETRIEVE_HISTORY_REDODUMPS   1016
#define IDC_HEX_RETRIEVE_HISTORY_ARCHIVEDUMPS   1017
#define IDC_HEX_RETRIEVE_HISTORY_NOTIFYDUMPS   1018
#define IDC_HEX_RETRIEVE_HISTORY_PLAYBACKMODE   1019
#define IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC   1020
#define IDC_HEX_RETRIEVE_HISTORY_PSEUDOREALTIME   1021
#define IDC_HEX_RETRIEVE_HISTORY_MANUAL   1022
#define IDC_HEX_RETRIEVE_HISTORY_SPEED_STATIC   1023
#define IDC_HEX_RETRIEVE_HISTORY_SPEED   1024
#define IDC_HEX_RETRIEVE_HISTORY_SLOW   1025
#define IDC_HEX_RETRIEVE_HISTORY_FAST   1026
#define IDC_HEX_RETRIEVE_HISTORY_INTERVAL   1027
#define IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME   1028
#define IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME_STATIC   1029
#define IDC_HEX_RETRIEVE_HELP   1030

// Specify the retrieve dialog related settings
#define HEXRETRIEVEDIALOG_MINIMUMINTERVAL   1
#define HEXRETRIEVEDIALOG_MAXIMUMINTERVAL   MINUTESPERWEEK
#define HEXRETRIEVEDIALOG_DEFAULTINTERVAL   5

class CHEXRetrieveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CHEXRetrieveDialog)

	// Construction
public:
	CHEXRetrieveDialog();   // standard constructor

	// Attributes
private:
	CString  m_szTitle;
	CString  m_szType;

	// Dialog Data
	//{{AFX_DATA(CHEXRetrieveDialog)
	enum { IDD = IDD_HEX_RETRIEVE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);
	INT Create(CWnd *pParentWnd, LPCTSTR pszTitle, LPCTSTR pszType);

	BOOL GetMode(UINT &nMode) CONST;
	BOOL GetSpeed(UINT &nSpeed) CONST;
	BOOL GetInterval(CTimeSpan &tInterval) CONST;
	BOOL GetStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetStopTime(CTimeKey &tTimeKey) CONST;

	class CHEXOpenDialog *GetParentDialog() CONST;
	class CHEXWnd *GetParentDisplay() CONST;

private:
	BOOL SetRetrieveInfo();
	BOOL GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXRetrieveDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHEXRetrieveDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRetrieveRealtime();
	afx_msg void OnRetrieveByTime();
	afx_msg void OnRetrieveByEnd();
	afx_msg void OnRetrieveByRealtime();
	afx_msg void OnRetrieveAutomatic();
	afx_msg void OnRetrievePseudoRealtime();
	afx_msg void OnRetrieveManual();
	afx_msg void OnRetrieveRedoDumps();
	afx_msg void OnRetrieveInterval();
	afx_msg void OnSpinchangeRetrieveStartTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXFindDialog dialog

#define IDC_HEX_FIND_KEY_STATIC   1001
#define IDC_HEX_FIND_KEY   1002
#define IDC_HEX_FIND_VALUE_STATIC   1003
#define IDC_HEX_FIND_VALUE   1004
#define IDC_HEX_FIND_RESULTS_STATIC   1005
#define IDC_HEX_FIND_RESULTS   1006
#define IDC_HEX_FIND_SEARCH   1007
#define IDC_HEX_FIND_OPEN   1008
#define IDC_HEX_FIND_HELP   1009

class CHEXFindDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CHEXFindDialog)

	// Construction
public:
	CHEXFindDialog();   // standard constructor

	// Attributes
private:
	INT  m_nType;
	CMemoryDumps  m_pDumps;
	CDatabaseTMPackets  m_pPackets;
	CStringArray  m_szDescriptions;

	// Dialog Data
	//{{AFX_DATA(CHEXFindDialog)
	enum { IDD = IDD_HEX_FIND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, INT nType, CString &szLayout);

	class CHEXWnd *GetParent() CONST;

private:
	BOOL EnumSearchKeys();
	BOOL EnumSearchValues();

	VOID DoFindByPacket(LPCTSTR pszPacket);
	VOID DoFindByPackets(CONST CStringArray &szPackets);
	VOID DoFindByDescription(LPCTSTR pszDescription);
	VOID DoFindByDescriptions(CONST CStringArray &szDescriptions);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHEXFindDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSearch();
	afx_msg void OnOpen();
	afx_msg void OnSelchangeKey();
	afx_msg void OnSelchangeValue();
	afx_msg void OnSelchangeResult();
	afx_msg void OnEditchangeValue();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXOpenDialog dialog

#define IDC_HEX_OPEN_DETAILS   1001
#define IDC_HEX_OPEN_DISPLAY_STATIC   1002
#define IDC_HEX_OPEN_DISPLAY   1003
#define IDC_HEX_OPEN_SETTINGS   1004
#define IDC_HEX_OPEN_FIND   1005
#define IDC_HEX_OPEN_TYPE   1006
#define IDC_HEX_OPEN_TYPE_NORMAL   1007
#define IDC_HEX_OPEN_TYPE_STREAM   1008
#define IDC_HEX_OPEN_TYPE_DUMPS   1009
#define IDC_HEX_OPEN_MODE   1010
#define IDC_HEX_OPEN_MODE_REALTIME   1011
#define IDC_HEX_OPEN_MODE_HISTORY   1012
#define IDC_HEX_OPEN_HELP   1013

class CHEXOpenDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CHEXOpenDialog)

	// Construction
public:
	CHEXOpenDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	UINT  m_nLayoutEnum[2];
	UINT  m_nLayoutLineLength;
	BOOL  m_bLayoutBadData;
	LOGFONT  m_fntLayoutTitle;
	LOGFONT  m_fntLayoutData;
	LOGFONT  m_fntLayoutSpy[2];
	CString  m_szRetrieveFileName;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CTimeSpan  m_tRetrieveInterval;
	CUIntArray  m_nLayoutColors;
	CHEXPrintJobs  m_pPrintJobs;
	CHEXSpyLocations  m_pSpyLocations;
private:
	CHEXSettingsDialog  m_dlgSettings;
	CHEXRetrieveDialog  m_dlgRetrievals;
	CHEXFindDialog  m_dlgFindDisplay;

	// Dialog Data
	//{{AFX_DATA(CHEXOpenDialog)
	enum { IDD = IDD_HEX_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	CString GetTitle() CONST;
	UINT GetType() CONST;
	UINT GetMode() CONST;

	BOOL GetLayout(CString &szLayout, CMemoryDump &cLayout) CONST;
	BOOL GetLayoutFormat(UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutDataFont(LPLOGFONT pDataFont) CONST;
	BOOL GetLayoutSpyFont(LPLOGFONT pHeaderFont, LPLOGFONT pLocationsFont) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetSpyLocations(CHEXSpyLocations &pSpyLocations) CONST;
	BOOL IsContentsModified() CONST;

	BOOL GetRetrieveMode(UINT &nMode) CONST;
	BOOL GetRetrieveSpeed(UINT &nSpeed) CONST;
	BOOL GetRetrieveInterval(CTimeSpan &tInterval) CONST;
	BOOL GetRetrieveStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveStopTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CHEXPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CHEXWnd *GetParent() CONST;

private:
	VOID EnumLayouts();

	BOOL FindLayout() CONST;
	BOOL FindLayout(CString &szLayout) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXOpenDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseSettingsDialog(UINT nCode);
	BOOL OnCloseRetrieveDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSettings();
	afx_msg void OnFind();
	afx_msg void OnEditchangeTitle();
	afx_msg void OnSelchangeTitle();
	afx_msg void OnTypeNormal();
	afx_msg void OnTypeStream();
	afx_msg void OnTypeDumps();
	afx_msg void OnRealtimeMode();
	afx_msg void OnHistoryMode();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXRetrieveThread thread

// Specify the hexadecimal display retrieve thread action codes
#define HEXRETRIEVETHREAD_ACTION_STOP   0
#define HEXRETRIEVETHREAD_ACTION_AUTOFORWARD   1
#define HEXRETRIEVETHREAD_ACTION_AUTOBACKWARD   2
#define HEXRETRIEVETHREAD_ACTION_MANUALFORWARD   3
#define HEXRETRIEVETHREAD_ACTION_MANUALBACKWARD   4
#define HEXRETRIEVETHREAD_ACTION_PSEUDOREALTIME   5
#define HEXRETRIEVETHREAD_ACTION_TYPES   6

class CHEXRetrieveThread : public CThread
{
	DECLARE_DYNCREATE(CHEXRetrieveThread)

	// Construction
public:
	CHEXRetrieveThread();

	// Attributes
private:
	UINT  m_nMode;
	UINT  m_nSpeed;
	CTimeSpan  m_tInterval;
	CTimeKey  m_tStartTime;
	CTimeKey  m_tStopTime;
	CString  m_szFileName;
private:
	LONG  *m_pbFlag;
	HANDLE  m_bInit;
	HANDLE  m_hAction[HEXRETRIEVETHREAD_ACTION_TYPES];
private:
	CHistoryTMProcessEngine  m_cTMProcessEngine;
	CTMEnvironment  m_cTMEnvironment;

	// Operations
public:
	BOOL Start(class CHEXWnd *pParentWnd, HANDLE bInit, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime);
	BOOL Stop();

	BOOL InitializeTMUnit(CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	BOOL InitializeTMUnit(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	BOOL InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData = FALSE);

private:
	VOID StartRetrieving();
	VOID StopRetrieving();

	UINT GetRetrieveMode() CONST;
	UINT GetRetrieveSpeed() CONST;
	CTimeSpan GetRetrieveInterval() CONST;
	CTimeKey GetRetrieveStartTime() CONST;
	CTimeKey GetRetrieveStopTime() CONST;
	CString GetRetrieveFileName() CONST;

	VOID BeginWaitCursor(BOOL bForced = FALSE);
	VOID EndWaitCursor();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXRetrieveThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHEXRetrieveThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXPrintThread thread

class CHEXPrintThread : public CThread
{
	DECLARE_DYNCREATE(CHEXPrintThread)

	// Construction
public:

	// Attributes
private:
	CHEXPrintJobs  m_pPrintJobs;
private:
	CEvent  m_cEvent;

	// Operations
public:
	BOOL Start(class CHEXWnd *pParentWnd);
	BOOL Stop();

	BOOL SetPrintJobs(CONST CHEXPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CHEXPrintJobs &pPrintJobs) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXPrintThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHEXPrintThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXToolBar window

class CHEXToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CHEXToolBar)

	// Construction
public:
	CHEXToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXStatusBar window

class CHEXStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CHEXStatusBar)

	// Construction
public:
	CHEXStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CHEXWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSplitterBarCtrl window

class CHEXSplitterBarCtrl : public CWnd
{
	DECLARE_DYNCREATE(CHEXSplitterBarCtrl)

	// Construction
public:
	CHEXSplitterBarCtrl();

	// Attributes
private:
	CPoint  m_ptBar[2];

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, CONST POINT &point);

	VOID Translate(CONST POINT &point);

	INT CalcTranslation(CONST POINT &point) CONST;
	INT CalcTranslation() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXSplitterBarCtrl)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXSplitterBarCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXDataContainer window

class CHEXDataContainer : public CTextView
{
	DECLARE_DYNCREATE(CHEXDataContainer)

	// Construction
public:
	CHEXDataContainer();

	// Attributes
public:

	// Operations
public:
	class CHEXDataView *GetParent() CONST;
	class CHEXWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXDataContainer)
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXDataContainer)
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXDataHeaderCtrl window

class CHEXDataHeaderCtrl : public CMFCHeaderCtrl
{
	DECLARE_DYNCREATE(CHEXDataHeaderCtrl)

	// Construction
public:
	CHEXDataHeaderCtrl();

	// Attributes
private:
	CString  m_szTitle;
private:
	WORD  m_wTextIndent[2];
	WORD  m_wTextSpacing[2];
private:
	CFont  m_cFont;
private:
	class CHEXDataView  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CHEXDataView *pParentWnd, DWORD dwStyle, UINT nID);

	BOOL SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;

	BOOL SetFont(CFont *pFont);
	BOOL SetFont(CONST LOGFONT *plfFont);
	BOOL GetFont(CFont *pFont) CONST;
	BOOL GetFont(LOGFONT *plfFont) CONST;

	class CHEXDataView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXDataHeaderCtrl)
public:
	virtual WORD CalcDefaultIndent() CONST;
	virtual WORD CalcDefaultSpacing() CONST;
protected:
	virtual void OnDrawItem(CDC *pDC, int iItem, CRect rect, BOOL bIsPressed, BOOL bIsHighlighted);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXDataHeaderCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXDataView window

class CHEXDataView : public CWnd
{
	DECLARE_DYNCREATE(CHEXDataView)

	// Construction
public:
	CHEXDataView();
	~CHEXDataView();

	// Attributes
private:
	CString  m_szLayout;
	CMemoryDump  m_cLayout;
	CUIntArray  m_nLayoutColors;
	CTMUnit  m_pLayoutData;
	CSize  m_sizeTrackLayout;
	UINT  m_nLayoutLineLength;
	UINT  m_nLayoutLineNumbers[2];
	BOOL  m_bBadDataMode;
private:
	CHEXDataHeaderCtrl  *m_pwndHeaderCtrl;
	CHEXDataContainer  *m_pwndView;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetTitle(LPCTSTR pszTitle);
	BOOL GetTitle(CString &szTitle) CONST;

	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CMemoryDump &cLayout);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CString &szLayout, CMemoryDump &cLayout) CONST;
	BOOL SetLayoutFormat(UINT nHorzEnum, UINT nVertEnum, UINT nLineLength, CONST CUIntArray &nColors);
	BOOL GetLayoutFormat(UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetTextFont(CFont *pFont);
	BOOL SetTextFont(CONST LOGFONT *plfFont);
	BOOL GetTextFont(CFont *pFont) CONST;
	BOOL GetTextFont(LOGFONT *plfFont) CONST;

	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;

	BOOL Initialize(CString &szTag, CTimeTag &tTag, WORD &wQuality);
	BOOL Update(LPCTSTR pszFileName, CString &szTag, CTimeTag &tTag, WORD &wQuality);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL);
	VOID Reset(CTMEnvironment *pTMEnvironment);

	BOOL IsInitialized() CONST;
	BOOL IsEmpty() CONST;

	BOOL GetPrintProperties(CString &szTitle, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pContentsFont) CONST;

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	BOOL AdjustColumns();

	class CHEXWnd *GetParent() CONST;

private:
	BOOL ShowRawData(CONST CTMUnit &cTMUnit);
	BOOL ShowDumpData(LPCTSTR pszDump = NULL, BOOL bReset = TRUE);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXDataView)
public:
	virtual VOID RecalcLayout();
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXDataView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXSpyView window

class CHEXSpyView : public CTextView
{
	DECLARE_DYNCREATE(CHEXSpyView)

	// Construction
public:
	CHEXSpyView();

	// Attributes
private:
	CString  m_szLayout;
	CTMUnit  m_pLayoutData;
	CHEXSpyLocations  m_pSpyLocations;
	BOOL  m_bBadDataMode;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL SetLayoutContents(CONST CHEXSpyLocations &pSpyLocations);
	BOOL GetLayoutContents(CHEXSpyLocations &pSpyLocations) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL SetTextFont(CFont *pFont);
	BOOL SetTextFont(CONST LOGFONT *plfFont);

	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;

	BOOL Initialize();
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL);
	VOID Reset(CTMEnvironment *pTMEnvironment);

	BOOL IsInitialized() CONST;

	BOOL GetPrintProperties(CString &szTitle, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pContentsFont) CONST;

	BOOL AdjustColumns();
	BOOL AdjustColumns(CONST CHEXSpyLocations &pSpyLocations);

	class CHEXWnd *GetParent() CONST;

private:
	BOOL ShowRawData(CONST CTMUnit &cTMUnit);

	CString ConvertText(INT nColumn, LPCTSTR pszText, LPCTSTR pszValue) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXSpyView)
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXSpyView)
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHEXWnd frame

// Specify the hexadecimal display types
#define HEX_TYPE_NORMAL   1
#define HEX_TYPE_STREAM   2
#define HEX_TYPE_DUMPS   3
// Specify the hexadecimal display views
#define HEX_VIEW_DATA   0
#define HEX_VIEW_SPY   1
// Specify the hexadecimal display retrieval modes
#define HEX_RETRIEVE_EXACTTIME   (1<<0)
#define HEX_RETRIEVE_REDODUMPS   (1<<1)
#define HEX_RETRIEVE_ARCHIVEDUMPS   (1<<2)
#define HEX_RETRIEVE_NOTIFYDUMPS   (1<<3)
#define HEX_RETRIEVE_STOPBYTIME   (1<<4)
#define HEX_RETRIEVE_STOPBYEND   (1<<5)
#define HEX_RETRIEVE_STOPBYREALTIME   (1<<6)
#define HEX_RETRIEVE_STOPPED   (1<<7)
#define HEX_RETRIEVE_RELATIVE   (1<<8)
#define HEX_RETRIEVE_AUTOFORWARD   (1<<9)
#define HEX_RETRIEVE_AUTOBACKWARD   (1<<10)
#define HEX_RETRIEVE_MANUALFORWARD   (1<<11)
#define HEX_RETRIEVE_MANUALBACKWARD   (1<<12)
#define HEX_RETRIEVE_PSEUDOREALTIME   (1<<13)
// Specify the hexadecimal display print modes
#define HEX_PRINT_ALLDATA   (1<<0)
#define HEX_PRINT_FIRSTDATASIDE   (1<<1)
#define HEX_PRINT_LASTDATASIDE   (1<<2)
#define HEX_PRINT_SPYLOCATIONS   (1<<3)
#define HEX_PRINT_ALLSPYLOCATIONS   (1<<4)
#define HEX_PRINT_FIRSTSPYLOCATIONSSIDE   (1<<5)
#define HEX_PRINT_LASTSPYLOCATIONSSIDE   (1<<6)
#define HEX_PRINT_CLEARCOMMENTS   (1<<7)
#define HEX_PRINT_ATTIME   (1<<8)
#define HEX_PRINT_ATDAILYTIME   (1<<9)
#define HEX_PRINT_ATEVENT   (1<<10)
#define HEX_PRINT_REPEATBYINTERVAL   (1<<11)
#define HEX_PRINT_REPEATSTOPBYCOUNT   (1<<12)
#define HEX_PRINT_REPEATSTOPBYTIME   (1<<13)
#define HEX_PRINT_DAILYREPEATSTOPBYCOUNT   (1<<14)
#define HEX_PRINT_DAILYREPEATSTOPBYTIME   (1<<15)
#define HEX_PRINT_ACTIVE   (1<<16)
// Specify the hexadecimal display print fonts
#define HEX_PRINTFONT_TITLE   0
#define HEX_PRINTFONT_SUBTITLE   1
#define HEX_PRINTFONT_OPERATINGDETAILS   2
#define HEX_PRINTFONT_OPERATINGMODE   3
#define HEX_PRINTFONT_DATATITLE   4
#define HEX_PRINTFONT_DATALISTITEMSTITLE   5
#define HEX_PRINTFONT_DATALISTITEMS   6
#define HEX_PRINTFONT_SPYTITLE   7
#define HEX_PRINTFONT_SPYLISTITEMSTITLE   8
#define HEX_PRINTFONT_SPYLISTITEMS   9
#define HEX_PRINTFONT_FOOTER   10
#define HEX_PRINTFONT_NOTICE   11
#define HEX_PRINTFONT_LOGO   12
#define HEX_PRINTFONTS   13
// Specify the hexadecimal display layout colors
#define HEX_LAYOUTCOLOR_NORMALDATA   0
#define HEX_LAYOUTCOLOR_RAWDATA   1
#define HEX_LAYOUTCOLOR_ENUMERATIONS   2
// Specify the hexadecimal display statusbar pane identifiers
#define ID_HEX_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_HEX_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_HEX_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class CHEXWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CHEXWnd)

	// Construction
public:
	CHEXWnd();

	// Attributes
private:
	CHEXToolBar  m_wndToolBar;
	CHEXStatusBar  m_wndStatusBar;
	CHEXDataView  m_wndDataView;
	CHEXSpyView  m_wndSpyView;
	CHEXSplitterBarCtrl  m_wndSplitterBarCtrl[2];
private:
	CHEXOpenDialog  m_dlgOpen;
	CHEXSettingsDialog  m_dlgSettings;
	CHEXRetrieveDialog  m_dlgRetrievals;
private:
	CHEXRetrieveThread  m_cRetrieveThread;
	CHEXPrintThread  m_cPrintThread;
private:
	CMemoryDumps  m_pMemoryDumps;
private:
	LONG  m_bRetrieveFlag;
	BOOL  m_bRetrieveDump;
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	CEvent  m_cRetrieveStop;
	CEvent  m_cRetrieveAutoForward;
	CEvent  m_cRetrieveAutoBackward;
	CEvent  m_cRetrieveManualForward;
	CEvent  m_cRetrieveManualBackward;
	CEvent  m_cRetrievePseudoRealtime;
	CTimeSpan  m_tRetrieveInterval;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CString  m_szRetrieveFileName;
	CString  m_szRetrieveDumpFileName[3];
private:
	CString  m_szTMUnit;
	CTimeTag  m_tTMUnit;
	UINT  m_nTMUnit;
	WORD  m_wTMUnit;
private:
	CSize  m_sizeViews[2];
	BOOL  m_bViews[2];

	// Operations
public:
	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CMemoryDump &cLayout);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CString &szLayout, CMemoryDump &cLayout) CONST;
	BOOL SetLayoutContents(CONST CHEXSpyLocations &pSpyLocations);
	BOOL GetLayoutContents(CHEXSpyLocations &pSpyLocations) CONST;
	BOOL SetLayoutFormat(UINT nHorzEnum, UINT nVertEnum, UINT nLineLength, CONST CUIntArray &nColors);
	BOOL GetLayoutFormat(UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetDataFont(CFont *pFont);
	BOOL SetDataFont(CONST LOGFONT *plfFont);
	BOOL GetDataFont(CFont *pFont) CONST;
	BOOL GetDataFont(LOGFONT *plfFont) CONST;
	BOOL SetSpyFont(CFont *pHeaderFont, CFont *pLocationsFont);
	BOOL SetSpyFont(CONST LOGFONT *plfHeaderFont, CONST LOGFONT *plfLocationsFont);
	BOOL GetSpyFont(CFont *pFont, BOOL bHeader = TRUE) CONST;
	BOOL GetSpyFont(LOGFONT *plfHeaderFont, LOGFONT *plfLocationsFont) CONST;

	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;

	BOOL ProcessRealtimeData();

	UINT ProcessMemoryDumps(CTimeKey &tTimeKey, CONST CTimeSpan &tInterval);

	BOOL StartRetrieveData(UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL StartRetrieveData();
	LONG IsRetrievingData() CONST;
	BOOL RetrieveMoreData(UINT nAction);
	BOOL StopRetrieveData();
	BOOL SetRetrieveMode(UINT nMode = 0);
	BOOL GetRetrieveMode(UINT &nMode) CONST;
	UINT GetRetrieveMode() CONST;
	BOOL SetRetrieveSpeed(UINT nSpeed = 0);
	BOOL GetRetrieveSpeed(UINT &nSpeed) CONST;
	UINT GetRetrieveSpeed() CONST;
	BOOL SetRetrieveInterval(CONST CTimeSpan &tInterval = 0);
	BOOL GetRetrieveInterval(CTimeSpan &tInterval) CONST;
	CTimeSpan GetRetrieveInterval() CONST;
	BOOL SetRetrieveStartTime(CONST CTimeKey &tStartTime = 0);
	BOOL GetRetrieveStartTime(CTimeKey &tStartTime) CONST;
	CTimeKey GetRetrieveStartTime() CONST;
	BOOL SetRetrieveStopTime(CONST CTimeKey &tStopTime = 0);
	BOOL GetRetrieveStopTime(CTimeKey &tStopTime) CONST;
	CTimeKey GetRetrieveStopTime() CONST;
	BOOL SetRetrieveFileName(LPCTSTR pszFileName);
	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	CString GetRetrieveFileName() CONST;
	BOOL SetRetrieveDumpFileName();
	BOOL SetRetrieveDumpFileName(LPCTSTR pszFileName);
	BOOL GetRetrieveDumpFileName(CString &szFileName) CONST;
	CString GetRetrieveDumpFileName() CONST;
	BOOL SetRetrieveDumpLastFileName(LPCTSTR pszFileName);
	BOOL GetRetrieveDumpLastFileName(CString &szFileName) CONST;
	CString GetRetrieveDumpLastFileName() CONST;
	BOOL SetRetrieveDumpSearchFileName(LPCTSTR pszFileName);
	BOOL GetRetrieveDumpSearchFileName(CString &szFileName) CONST;
	CString GetRetrieveDumpSearchFileName() CONST;
	BOOL SetRetrieveDumpStatus(BOOL bStatus);
	BOOL GetRetrieveDumpStatus() CONST;

	BOOL SetPrintJobs(CONST CHEXPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CHEXPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CHEXPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	CHEXWnd *Find(INT nType, UINT nMode, LPCTSTR pszName) CONST;

	VOID SetUpdateInfo();
	VOID SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, WORD wQuality);
	BOOL GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, WORD &wQuality) CONST;

private:
	BOOL CreateToolBar();
	BOOL CreateStatusBar();
	BOOL CreateSplitterBar();
	BOOL CreateViews();

	VOID InitializeViews();
	CRect RepositionViews(BOOL bAdjust = TRUE);
	BOOL SetViewSize(UINT nView, CONST CSize &size);
	CSize GetViewSize(UINT nView) CONST;
	CRect RepositionView(UINT nView = HEX_VIEW_DATA);
	CRect RepositionViewSplitterBar() CONST;
	BOOL IsViewVisible(UINT nView) CONST;

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateModePane();
	VOID UpdateTypePane();

	VOID UpdateData();

	BOOL StartSchedulePrintJobs();
	BOOL IsSchedulingPrintJobs() CONST;
	BOOL StopSchedulePrintJobs();

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CHEXPrintJobInfo *pJobInfo, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CString &szDataTitle, CString &szSpyTitle, CStringArray &szDataColumns, CStringArray &szSpyColumns, CStringArray &szDataContents, CStringArray &szSpyContents, CTextViewAttributes &pDataAttributes, CTextViewAttributes &pSpyAttributes, LOGFONT *pDataTitleFont, LOGFONT *pSpyTitleFont, LOGFONT *pDataContentsFont, LOGFONT *pSpyContentsFont) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CHEXPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, LPCTSTR pszDataTitle, LPCTSTR pszSpyTitle, CONST CStringArray &szDataColumns, CONST CStringArray &szSpyColumns, CONST CStringArray &szDataContents, CONST CStringArray &szSpyContents, CONST CTextViewAttributes &pDataAttributes, CONST CTextViewAttributes &pSpyAttributes, CONST LOGFONT *pDataTitleFont, CONST LOGFONT *pSpyTitleFont, CONST LOGFONT *pDataContentsFont, CONST LOGFONT *pSpyContentsFont);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CHEXPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, LPCTSTR pszTitle, CONST CStringArray &szColumns, BOOL bSpy, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDataTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDataOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSpyTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSpyOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSpyListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(LPCTSTR pszLayout) CONST;
	CString GetPrintDocOperatingDetails(CONST CHEXPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST;
	CString GetPrintDocOperatingMode(CONST CHEXPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocDataTitle(LPCTSTR pszTitle) CONST;
	CString GetPrintDocDataOperatingMode(CONST CHEXPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocSpyTitle(LPCTSTR pszTitle) CONST;
	CString GetPrintDocSpyOperatingMode(CONST CHEXPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocSpyListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFonts, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CStringArray &szContents, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHEXWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Initialize(BOOL bFlag);
	virtual BOOL Initialize(CTMEnvironment *pTMEnvironment);
	virtual BOOL Initialize(CString &szTag, CTimeTag &tTag);
	virtual BOOL InitializeTMData(UINT nMode);
	virtual BOOL InitializeTMData(CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	virtual BOOL InitializeTMData(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	virtual BOOL InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData = FALSE);
	virtual BOOL Check() CONST;
	virtual VOID Update();
	virtual BOOL Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags = 0);
	virtual VOID Reset(CTMEnvironment *pTMEnvironment = NULL);
	virtual BOOL Stop();
public:
	virtual BOOL SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo);
	virtual BOOL LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo);
	virtual BOOL QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST;
	virtual BOOL QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST;
	virtual VOID UpdateBars();
public:
	virtual BOOL Print(PRINTDLG *pPrintInfo = NULL);
	virtual BOOL CanPrint() CONST;
	virtual BOOL IsLinkable() CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseOpenDialog(UINT nCode);
	BOOL OnCloseSettingsDialog(UINT nCode);
	BOOL OnCloseRetrieveDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CHEXWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSettings();
	afx_msg void OnRetrievals();
	afx_msg void OnRetrieveStop();
	afx_msg void OnRetrieveAutoForward();
	afx_msg void OnRetrieveAutoBackward();
	afx_msg void OnRetrieveManualForward();
	afx_msg void OnRetrieveManualBackward();
	afx_msg void OnRetrievePseudoRealtime();
	afx_msg void OnPrint();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrievals(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveAutoBackward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveManualForward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveManualBackward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarModePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarTypePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __HEX_H__
