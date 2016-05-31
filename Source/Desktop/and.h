// AND.H : Alphanumeric Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the alphanumeric display related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/25 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __AND_H__
#define __AND_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CANDPrintJobInfo

class CANDPrintJobInfo : public CObject
{
	// Construction
public:
	CANDPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbEvent;
		INT  cbProfile;
		INT  cbComments;
		UINT  nPrintMode;
		UINT  nPrintColumns;
		UINT  nPrintByCount;
		UINT  nPrintCount[2];
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
	UINT  m_nPrintColumns;
	UINT  m_nPrintByCount;
	UINT  m_nPrintCount[2];
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
	BOOL SetPrintBySide(UINT nCount);
	BOOL GetPrintBySide(UINT &nCount) CONST;
	BOOL SetPrintFormat(UINT nColumns);
	BOOL GetPrintFormat(UINT &nColumns) CONST;
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

	VOID Copy(CONST CANDPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CANDPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDPrintJobs

class CANDPrintJobs : public CPtrArray
{
	// Construction
public:
	CANDPrintJobs();
	~CANDPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CANDPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CANDPrintJobInfo *GetAt(INT nIndex) CONST;
	CANDPrintJobInfo *operator[](INT nIndex) CONST;

	TIMEKEY Schedule();

	VOID RemoveAll();

	BOOL Copy(CONST CANDPrintJobs *pPrintJobs);
	BOOL Compare(CONST CANDPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsLayoutPage dialog

#define IDC_ANDSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC   1003
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME   1004
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW   1005
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE   1006
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER   1007
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_REMOVE   1008
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_SHOWDATA   1009
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA   1010
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA   1011
#define IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS   1012
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS   1013
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1014
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1015
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS   1016
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS   1017
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES   1018
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1019
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1020
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES   1021
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1022
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE   1023
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1024
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE   1025
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED   1026
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1027
#define IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1028

class CANDSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CANDSettingsLayoutPage)

	// Construction
public:
	CANDSettingsLayoutPage();

	// Attributes
private:
	CUIntArray  m_nColumns[2];
	LOGFONT  m_fntTitle[2];
	LOGFONT  m_fntItems[2];
	LOGFONT  m_fntLabels[2];
	LOGFONT  m_fntValues[2];
	BOOL  m_bInvalidData[2];
	BOOL  m_bBadData[2];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;
	CStringArray  m_szColumns;
	INT  m_nColumnIndex;

	// Dialog Data
	//{{AFX_DATA(CANDSettingsLayoutPage)
	enum { IDD = IDD_AND_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLabelsFont(LPLOGFONT pLabelsFont) CONST;
	BOOL GetItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetValuesFont(LPLOGFONT pValuesFont) CONST;
	BOOL GetInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetBadDataMode(BOOL &bEnable) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CANDSettingsDialog *GetParentDialog() CONST;
	class CANDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumLayoutColumns();

	BOOL ShowLayoutColumns();
	VOID ShowLayoutFontDetails();
	VOID ShowLayoutFontSample();

	BOOL InsertLayoutColumn(INT nIndex, LPCTSTR pszText);
	BOOL ModifyLayoutColumn(INT nIndex, LPCTSTR pszText);
	BOOL RemoveLayoutColumn(INT nIndex);
	BOOL SetCurLayoutColumn(INT nIndex = 0);
	INT GetCurLayoutColumn() CONST;
	BOOL CheckLayoutColumn() CONST;

	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);
	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CANDSettingsLayoutPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CUIntArray &nColumns);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CANDSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnInsertColumnBefore();
	afx_msg void OnInsertColumnAfter();
	afx_msg void OnRemoveColumn();
	afx_msg void OnInvalidData();
	afx_msg void OnBadData();
	afx_msg void OnToolTips();
	afx_msg void OnTitleFont();
	afx_msg void OnLabelsFont();
	afx_msg void OnItemsFont();
	afx_msg void OnValuesFont();
	afx_msg void OnUnderlineFont();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeColumnName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsDirectoryDialog dialog

#define IDC_ANDSETTINGS_DIRECTORY_DETAILS   1001
#define IDC_ANDSETTINGS_DIRECTORY_TYPE   1002
#define IDC_ANDSETTINGS_DIRECTORY_TYPE_NORMAL   1003
#define IDC_ANDSETTINGS_DIRECTORY_TYPE_GENERIC   1004
#define IDC_ANDSETTINGS_DIRECTORY_TYPE_TEMPORARY   1005
#define IDC_ANDSETTINGS_DIRECTORY_LIST_STATIC   1006
#define IDC_ANDSETTINGS_DIRECTORY_LIST   1007
#define IDC_ANDSETTINGS_DIRECTORY_HELP   1008

class CANDSettingsDirectoryDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CANDSettingsDirectoryDialog)

	// Construction
public:
	CANDSettingsDirectoryDialog();   // standard constructor

	// Attributes
private:
	CANDLayout  m_cLayout;

	// Dialog Data
	//{{AFX_DATA(CANDSettingsDirectoryDialog)
	enum { IDD = IDD_AND_SETTINGS_DIRECTORY_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	BOOL GetLayout(CANDLayout &cLayout) CONST;

	class CANDSettingsDialog *GetParentDialog() CONST;
	class CANDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumDisplays();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDSettingsDirectoryDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANDSettingsDirectoryDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnNormalANDs();
	afx_msg void OnGenericANDs();
	afx_msg void OnTemporaryANDs();
	afx_msg void OnEditchangeAND();
	afx_msg void OnSelchangeAND();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsContentsPage dialog

#define IDC_ANDSETTINGS_CONTENTSPAGE_DETAILS   1001
#define IDC_ANDSETTINGS_CONTENTSPAGE_VIEW   1002
#define IDC_ANDSETTINGS_CONTENTSPAGE_ADD   1003
#define IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY   1004
#define IDC_ANDSETTINGS_CONTENTSPAGE_REMOVE   1005
#define IDC_ANDSETTINGS_CONTENTSPAGE_REMOVEALL   1006
#define IDC_ANDSETTINGS_CONTENTSPAGE_MOVEUPDOWN   1007
#define IDC_ANDSETTINGS_CONTENTSPAGE_IMPORT   1008
#define IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT_STATIC   1009
#define IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT   1010
#define IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR_STATIC   1011
#define IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR   1012
#define IDC_ANDSETTINGS_CONTENTSPAGE_POSITION   1013
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS   1014
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC   1015
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME   1016
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC   1017
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR_STATIC   1018
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR   1019
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_STATIC   1020
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT   1021
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL   1022
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY   1023
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL   1024
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL   1025
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT   1026
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE   1027
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_STATIC   1028
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT   1029
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_CENTER   1030
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT   1031
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_STATIC   1032
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT   1033
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE   1034
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST   1035
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER   1036
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_STATIC   1037
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT   1038
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS   1039
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT   1040
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS   1041
#define IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT   1042

// Specify the alphanumeric display settings contents page related limits
#define ANDSETTINGSCONTENTSPAGE_DEFAULT_ROWS   256
#define ANDSETTINGSCONTENTSPAGE_PARAMETER_MINIMUMOCCURRENCE   1
#define ANDSETTINGSCONTENTSPAGE_PARAMETER_MAXIMUMOCCURRENCE   999
#define ANDSETTINGSCONTENTSPAGE_PARAMETER_DEFAULTOCCURRENCE   1
#define ANDSETTINGSCONTENTSPAGE_PARAMETER_MINIMUMDIGITS   1
#define ANDSETTINGSCONTENTSPAGE_PARAMETER_MAXIMUMDIGITS   16
#define ANDSETTINGSCONTENTSPAGE_PARAMETER_DEFAULTDIGITS   DEFAULTFLOATINGPOINTDECIMALPLACES

class CANDSettingsContentsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CANDSettingsContentsPage)

	// Construction
public:
	CANDSettingsContentsPage();

	// Attributes
private:
	CPoint  m_ptLayout;
	CANDLayout  m_cLayout[2];
	CUIntArray  m_nColors[2];
	CUIntArray  m_nLayoutColumns;
	CStringArray  m_szLayoutColumns;
	CStringArray  m_szTopicsText;

	// Dialog Data
	//{{AFX_DATA(CANDSettingsContentsPage)
	enum { IDD = IDD_AND_SETTINGS_CONTENTSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CANDLayout &cLayout) CONST;
	BOOL GetLayout(CANDLayout &cLayout, CUIntArray &nColumns) CONST;
	BOOL GetColors(CUIntArray &nColors) CONST;

	class CANDSettingsDialog *GetParentDialog() CONST;
	class CANDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumParameters();
	BOOL EnumOOLs();
	BOOL EnumTopics();

	VOID ShowContents();

	VOID SetParameterInfo();
	BOOL GetParameterInfo(CString &szName, CString &szDescription, CString &szComments, ULONGLONG &nAttributes, COLORREF &nColor, UINT &nAlignment, INT &nOccurrence, INT &nDigits) CONST;

	BOOL SetCurRow(INT nRow = 0);
	INT GetCurRow() CONST;
	BOOL SetCurColumn(INT nColumn = 0);
	INT GetCurColumn() CONST;

	CANDLayoutParameter *FindParameter() CONST;
	BOOL CheckParameter() CONST;
	INT LookupParameter() CONST;

	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CANDSettingsContentsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CUIntArray &nColumns);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CANDSettingsContentsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddParameter();
	afx_msg void OnModifyParameter();
	afx_msg void OnRemoveParameter();
	afx_msg void OnRemoveAllParameters();
	afx_msg void OnImportParameters();
	afx_msg void OnSelchangeOolText();
	afx_msg void OnSelchangeOolColor();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeColor();
	afx_msg void OnEditchangeName();
	afx_msg void OnCodingDefault();
	afx_msg void OnCodingDecimal();
	afx_msg void OnCodingBinary();
	afx_msg void OnCodingOctal();
	afx_msg void OnCodingHexadecimal();
	afx_msg void OnCodingFloat();
	afx_msg void OnCodingInverse();
	afx_msg void OnAlignLeft();
	afx_msg void OnAlignCenter();
	afx_msg void OnAlignRight();
	afx_msg void OnOccurrenceDefault();
	afx_msg void OnOccurrencePast();
	afx_msg void OnOccurrenceNumber();
	afx_msg void OnSpinchangeOccurrence();
	afx_msg void OnDigitsDefault();
	afx_msg void OnDigitsCount();
	afx_msg void OnSpinchangeDigits();
	afx_msg void OnSelchangeTopics();
	afx_msg void OnEditchangeTopicsText();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsRetrievingPage dialog

#define IDC_ANDSETTINGS_RETRIEVINGPAGE_DETAILS   1001
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC   1002
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE   1003
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_INSPECT   1004
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO   1005
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS   1006
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC   1007
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT   1008
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC   1009
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY   1010
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC   1011
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT   1012
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC   1013
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE   1014
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC   1015
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME   1016
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO   1017
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME   1018
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC   1019
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME   1020
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC   1021
#define IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE   1022

class CANDSettingsRetrievingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CANDSettingsRetrievingPage)

	// Construction
public:
	CANDSettingsRetrievingPage();

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CANDSettingsRetrievingPage)
	enum { IDD = IDD_AND_SETTINGS_RETRIEVINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetDataSourceFileName(CString &szFileName) CONST;

	class CANDSettingsDialog *GetParentDialog() CONST;
	class CANDWnd *GetParentDisplay() CONST;

private:
	VOID EnumDataSources();
	VOID ShowDataSourceInfo();

	BOOL CheckDataSource(LPCTSTR pszFileName) CONST;
	BOOL CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST;

	CString FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CANDSettingsRetrievingPage)
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
	//{{AFX_MSG(CANDSettingsRetrievingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnInspect();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeFileName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsPrintingComments window

class CANDSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CANDSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CANDSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsPrintingPage dialog

#define IDC_ANDSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_ANDSETTINGS_PRINTINGPAGE_NAME_STATIC   1002
#define IDC_ANDSETTINGS_PRINTINGPAGE_NAME   1003
#define IDC_ANDSETTINGS_PRINTINGPAGE_ADDNAME   1004
#define IDC_ANDSETTINGS_PRINTINGPAGE_REMOVENAME   1005
#define IDC_ANDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES   1006
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES   1007
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC   1008
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE   1009
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS   1010
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL   1011
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE   1012
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE   1013
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC   1014
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT   1015
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL   1016
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND   1017
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT   1018
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_STATIC   1019
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_GENERIC   1020
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS   1021
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_STATIC   1022
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT   1023
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS   1024
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC   1025
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT   1026
#define IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS   1027

// Specify the alphanumeric display settings printing page related limits
#define ANDSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMPARAMETERS   1
#define ANDSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMPARAMETERS   10000
#define ANDSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTPARAMETERS   25
#define ANDSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMCOLUMNS   2
#define ANDSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMCOLUMNS   4
#define ANDSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTCOLUMNS   2

class CANDSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CANDSettingsPrintingPage)

	// Construction
public:
	CANDSettingsPrintingPage();

	// Attributes
private:
	CANDPrintJobs  m_pJobs[2];
private:
	CANDSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CANDSettingsPrintingPage)
	enum { IDD = IDD_AND_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CANDPrintJobs &pJobs) CONST;

	class CANDSettingsDialog *GetParentDialog() CONST;
	class CANDWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CANDPrintJobInfo *FindJobInfo() CONST;

	BOOL HasMultipleColumns() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CANDSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CANDPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CANDSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnAddName();
	afx_msg void OnRemoveName();
	afx_msg void OnRemoveAllNames();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnPrintAll();
	afx_msg void OnPrintBySide();
	afx_msg void OnPrintUnderlineOOL();
	afx_msg void OnPrintColorLegend();
	afx_msg void OnPrintGenericFormat();
	afx_msg void OnPrintCustomFormat();
	afx_msg void OnChangePrintSide();
	afx_msg void OnSpinchangePrintSideCount();
	afx_msg void OnSpinchangePrintColumns();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsPrintJobsPage dialog

#define IDC_ANDSETTINGS_PRINTJOBSPAGE_DETAILS   1001
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC   1002
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS   1003
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB   1004
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC   1005
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS   1006
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_REMOVEJOB   1007
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR   1008
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME   1009
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME   1010
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME   1011
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC   1012
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME   1013
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT   1014
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT   1015
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC   1016
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION   1017
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC   1018
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE   1019
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME  1020
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC   1021
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME   1022
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC   1023
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES   1024
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC   1025
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES   1026
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME   1027
#define IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME   1028

// Specify the alphanumeric display settings print jobs page related repetition types
#define ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY   1
#define ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY   2
// Specify the alphanumeric display settings print jobs page related limits
#define ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL   1
#define ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL   MINUTESPERHOUR
#define ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES   1
#define ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES   10000
#define ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES   10

class CANDSettingsPrintJobsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CANDSettingsPrintJobsPage)

	// Construction
public:
	CANDSettingsPrintJobsPage();

	// Attributes
private:
	CANDPrintJobs  m_pJobs[2];

	// Dialog Data
	//{{AFX_DATA(CANDSettingsPrintJobsPage)
	enum { IDD = IDD_AND_SETTINGS_PRINTJOBSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CANDPrintJobs &pJobs) CONST;

	class CANDSettingsDialog *GetParentDialog() CONST;
	class CANDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumJobs();
	BOOL EnumEvents();

	VOID ShowJobInfo();
	BOOL CheckJobInfo() CONST;
	CANDPrintJobInfo *FindJobInfo(BOOL bActive = FALSE) CONST;

	VOID SetJobRepetitionInfo();
	UINT GetJobRepetitionType() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CANDSettingsPrintJobsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CANDPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CANDSettingsPrintJobsPage)
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
// CANDSettingsTabCtrl window

class CANDSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CANDSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CANDSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsDialog

class CANDSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CANDSettingsDialog)

	// Construction
public:
	CANDSettingsDialog();

	// Attributes
private:
	CANDSettingsTabCtrl  m_wndTabCtrl;
	CANDSettingsLayoutPage  m_pageLayout;
	CANDSettingsContentsPage  m_pageContents;
	CANDSettingsRetrievingPage  m_pageRetrieving;
	CANDSettingsPrintingPage  m_pagePrinting;
	CANDSettingsPrintJobsPage  m_pagePrintJobs;

	// Operations
public:
	BOOL GetLayout(CANDLayout &cLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayoutColors(CUIntArray &nColors) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutLabelsFont(LPLOGFONT pLabelsFont) CONST;
	BOOL GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutValuesFont(LPLOGFONT pValuesFont) CONST;
	BOOL GetLayoutInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CANDPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CANDOpenDialog *GetParentDialog() CONST;
	class CANDWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDSettingsDialog)
public:
	virtual BOOL OnDataExchange(HWND hPage, CONST CUIntArray &nColumns);
	virtual BOOL OnDataExchange(HWND hPage, CONST CANDPrintJobs &pJobs);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CANDSettingsDialog)
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
// CANDLinkagesDialog dialog

#define IDC_AND_LINKAGES_DETAILS   1001
#define IDC_AND_LINKAGES_NAME_STATIC   1002
#define IDC_AND_LINKAGES_NAME   1003
#define IDC_AND_LINKAGES_DISPLAYS_STATIC  1004
#define IDC_AND_LINKAGES_DISPLAYS   1005
#define IDC_AND_LINKAGES_LIST_STATIC   1006
#define IDC_AND_LINKAGES_LIST   1007
#define IDC_AND_LINKAGES_ADD   1008
#define IDC_AND_LINKAGES_REMOVE   1009
#define IDC_AND_LINKAGES_REMOVEALL   1010
#define IDC_AND_LINKAGES_HELP   1011

class CANDLinkagesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CANDLinkagesDialog)

	// Construction
public:
	CANDLinkagesDialog();   // standard constructor

	// Attributes
private:
	CPtrArray  m_pDisplays[3];

	// Dialog Data
	//{{AFX_DATA(CANDLinkagesDialog)
	enum { IDD = IDD_AND_LINKAGES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CANDWnd *GetParent() CONST;

private:
	BOOL EnumDisplays();

	INT FindDisplay(LPCTSTR pszName, BOOL bLinked = FALSE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDLinkagesDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANDLinkagesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddDisplay();
	afx_msg void OnRemoveLinkedDisplay();
	afx_msg void OnRemoveAllLinkedDisplays();
	afx_msg void OnEditchangeDisplay();
	afx_msg void OnSelchangeDisplay();
	afx_msg void OnSelchangeLinkedDisplay();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDParametersCalibrationPage dialog

#define IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC   1007
#define IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS   1008
#define IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1009
#define IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS   1010

class CANDParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CANDParametersCalibrationPage)

	// Construction
public:
	CANDParametersCalibrationPage();

	// Attributes
private:
	INT  m_nCalTableID;
	ULONGLONG  m_nCalTableType;
	CUIntArray  m_nCalTableRefs;
	CUIntArray  m_nCalValidityRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CANDParametersCalibrationPage)
	enum { IDD = IDD_AND_PARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter);
	VOID ShowCalibrationInfo();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CANDParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CANDParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDParametersFolderTabCtrl window

class CANDParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CANDParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CANDParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CANDParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDParametersFolder

class CANDParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CANDParametersFolder)

	// Construction
public:
	CANDParametersFolder();

	// Attributes
private:
	CANDParametersFolderTabCtrl  m_wndTabCtrl;
	CANDParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter);

	class CANDParametersDialog *GetParentDialog() CONST;
	class CANDWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CANDParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDParametersDialog dialog

#define IDC_AND_PARAMETERS_DETAILS   1001
#define IDC_AND_PARAMETERS_ITEM_STATIC   1002
#define IDC_AND_PARAMETERS_ITEM   1003
#define IDC_AND_PARAMETERS_FOLDER   1004
#define IDC_AND_PARAMETERS_HELP   1005

class CANDParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CANDParametersDialog)

	// Construction
public:
	CANDParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szParameter;
private:
	CANDParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CANDParametersDialog)
	enum { IDD = IDD_AND_PARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter);

	class CANDWnd *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANDParametersDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDRetrieveDialog dialog

#define IDC_AND_RETRIEVE_DETAILS   1001
#define IDC_AND_RETRIEVE_TITLE_STATIC   1002
#define IDC_AND_RETRIEVE_TITLE   1003
#define IDC_AND_RETRIEVE_TYPE_STATIC   1004
#define IDC_AND_RETRIEVE_TYPE   1005
#define IDC_AND_RETRIEVE_REALTIME   1006
#define IDC_AND_RETRIEVE_HISTORY   1007
#define IDC_AND_RETRIEVE_HISTORY_START_STATIC   1008
#define IDC_AND_RETRIEVE_HISTORY_STARTTIME   1009
#define IDC_AND_RETRIEVE_HISTORY_EXACTTIME   1010
#define IDC_AND_RETRIEVE_HISTORY_STOP_STATIC   1011
#define IDC_AND_RETRIEVE_HISTORY_STOPBYTIME   1012
#define IDC_AND_RETRIEVE_HISTORY_STOPTIME   1013
#define IDC_AND_RETRIEVE_HISTORY_STOPBYEND   1014
#define IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME   1015
#define IDC_AND_RETRIEVE_HISTORY_PLAYBACKMODE   1016
#define IDC_AND_RETRIEVE_HISTORY_AUTOMATIC   1017
#define IDC_AND_RETRIEVE_HISTORY_PSEUDOREALTIME   1018
#define IDC_AND_RETRIEVE_HISTORY_MANUAL   1019
#define IDC_AND_RETRIEVE_HISTORY_SPEED_STATIC   1020
#define IDC_AND_RETRIEVE_HISTORY_SPEED   1021
#define IDC_AND_RETRIEVE_HISTORY_SLOW   1022
#define IDC_AND_RETRIEVE_HISTORY_FAST   1023
#define IDC_AND_RETRIEVE_HISTORY_INTERVAL   1024
#define IDC_AND_RETRIEVE_HISTORY_INTERVALTIME   1025
#define IDC_AND_RETRIEVE_HISTORY_INTERVALTIME_STATIC   1026
#define IDC_AND_RETRIEVE_HELP   1027

// Specify the alphanumeric display retrieve dialog related limits
#define ANDRETRIEVEDIALOG_MINIMUMINTERVAL   1
#define ANDRETRIEVEDIALOG_MAXIMUMINTERVAL   MINUTESPERWEEK
#define ANDRETRIEVEDIALOG_DEFAULTINTERVAL   5

class CANDRetrieveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CANDRetrieveDialog)

	// Construction
public:
	CANDRetrieveDialog();   // standard constructor

	// Attributes
private:
	CString  m_szTitle;
	CString  m_szType;

	// Dialog Data
	//{{AFX_DATA(CANDRetrieveDialog)
	enum { IDD = IDD_AND_RETRIEVE_DIALOG };
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

	class CANDOpenDialog *GetParentDialog() CONST;
	class CANDWnd *GetParentDisplay() CONST;

private:
	BOOL SetRetrieveInfo();
	BOOL GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDRetrieveDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANDRetrieveDialog)
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
	afx_msg void OnRetrieveInterval();
	afx_msg void OnSpinchangeRetrieveStartTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDImportDialog dialog

#define IDC_AND_IMPORT_DETAILS   1001
#define IDC_AND_IMPORT_FILENAME_STATIC   1002
#define IDC_AND_IMPORT_FILENAME   1003
#define IDC_AND_IMPORT_BROWSE   1004
#define IDC_AND_IMPORT_INSPECT   1005
#define IDC_AND_IMPORT_DIRECTORY_STATIC   1006
#define IDC_AND_IMPORT_DIRECTORY   1007
#define IDC_AND_IMPORT_ADD   1008
#define IDC_AND_IMPORT_ADDALL   1009
#define IDC_AND_IMPORT_ATTENTION   1010
#define IDC_AND_IMPORT_ATTENTION_TEXT   1011
#define IDC_AND_IMPORT_LIST_STATIC   1012
#define IDC_AND_IMPORT_LIST   1013
#define IDC_AND_IMPORT_REMOVE   1014
#define IDC_AND_IMPORT_REMOVEALL   1015
#define IDC_AND_IMPORT_HELP   1016

class CANDImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CANDImportDialog)

	// Construction
public:
	CANDImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CANDLayouts  m_pDisplays[3];

	// Operations
private:
	VOID EnumDisplays();

	// Dialog Data
	//{{AFX_DATA(CANDImportDialog)
	enum { IDD = IDD_AND_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDImportDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANDImportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowse();
	afx_msg void OnInspect();
	afx_msg void OnAdd();
	afx_msg void OnAddAll();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeSource();
	afx_msg void OnSelchangeDestination();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDExportDialog dialog

#define IDC_AND_EXPORT_DETAILS   1001
#define IDC_AND_EXPORT_DIRECTORY_STATIC   1002
#define IDC_AND_EXPORT_DIRECTORY   1003
#define IDC_AND_EXPORT_ADD   1004
#define IDC_AND_EXPORT_ADDALL   1005
#define IDC_AND_EXPORT_LIST_STATIC   1006
#define IDC_AND_EXPORT_LIST   1007
#define IDC_AND_EXPORT_REMOVE   1008
#define IDC_AND_EXPORT_REMOVEALL   1009
#define IDC_AND_EXPORT_FILENAME_STATIC   1010
#define IDC_AND_EXPORT_FILENAME   1011
#define IDC_AND_EXPORT_BROWSE   1012
#define IDC_AND_EXPORT_HELP   1013

class CANDExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CANDExportDialog)

	// Construction
public:
	CANDExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CANDLayouts  m_pDisplays[2];

	// Operations
private:
	BOOL EnumDisplays();

	// Dialog Data
	//{{AFX_DATA(CANDExportDialog)
	enum { IDD = IDD_AND_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDExportDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANDExportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnAddAll();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnBrowse();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeSource();
	afx_msg void OnSelchangeDestination();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDFindDialog dialog

#define IDC_AND_FIND_KEY_STATIC   1001
#define IDC_AND_FIND_KEY   1002
#define IDC_AND_FIND_VALUE_STATIC   1003
#define IDC_AND_FIND_VALUE   1004
#define IDC_AND_FIND_RESULTS_STATIC   1005
#define IDC_AND_FIND_RESULTS   1006
#define IDC_AND_FIND_SEARCH   1007
#define IDC_AND_FIND_OPEN   1008
#define IDC_AND_FIND_HELP   1009

class CANDFindDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CANDFindDialog)

	// Construction
public:
	CANDFindDialog();   // standard constructor

	// Attributes
private:
	INT  m_nType;
	CANDLayouts  m_pLayouts[2];
	CStringArray  m_szDescriptions;

	// Dialog Data
	//{{AFX_DATA(CANDFindDialog)
	enum { IDD = IDD_AND_FIND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, INT nType, CANDLayout &cLayout);

	class CANDWnd *GetParent() CONST;

private:
	BOOL EnumSearchKeys();
	BOOL EnumSearchValues();

	VOID DoFindByParameter(LPCTSTR pszParameter);
	VOID DoFindByParameters(CONST CStringArray &szParameters);
	VOID DoFindByDescription(LPCTSTR pszDescription);
	VOID DoFindByDescriptions(CONST CStringArray &szDescriptions);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANDFindDialog)
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
// CANDOpenDialog dialog

#define IDC_AND_OPEN_DETAILS   1001
#define IDC_AND_OPEN_DISPLAY_STATIC   1002
#define IDC_AND_OPEN_DISPLAY   1003
#define IDC_AND_OPEN_SETTINGS   1004
#define IDC_AND_OPEN_FIND   1005
#define IDC_AND_OPEN_TYPE   1006
#define IDC_AND_OPEN_TYPE_NORMAL   1007
#define IDC_AND_OPEN_TYPE_GENERIC   1008
#define IDC_AND_OPEN_TYPE_TEMPORARY   1009
#define IDC_AND_OPEN_REMOVE   1010
#define IDC_AND_OPEN_MODE   1011
#define IDC_AND_OPEN_MODE_REALTIME   1012
#define IDC_AND_OPEN_MODE_HISTORY   1013
#define IDC_AND_OPEN_HELP   1014

class CANDOpenDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CANDOpenDialog)

	// Construction
public:
	CANDOpenDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	BOOL  m_bLayoutBadData;
	BOOL  m_bLayoutToolTips;
	BOOL  m_bLayoutInvalidData;
	LOGFONT  m_fntLayoutTitle;
	LOGFONT  m_fntLayoutItems;
	LOGFONT  m_fntLayoutLabels;
	LOGFONT  m_fntLayoutValues;
	CString  m_szRetrieveFileName;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CTimeSpan  m_tRetrieveInterval;
	CUIntArray  m_nLayoutColors;
	CUIntArray  m_nLayoutColumns;
	CANDPrintJobs  m_pPrintJobs;
	CANDLayout  m_cLayout;
private:
	CANDSettingsDialog  m_dlgSettings;
	CANDRetrieveDialog  m_dlgRetrievals;
	CANDFindDialog  m_dlgFindDisplay;

	// Dialog Data
	//{{AFX_DATA(CANDOpenDialog)
	enum { IDD = IDD_AND_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	CString GetTitle() CONST;
	UINT GetType() CONST;
	UINT GetMode() CONST;

	BOOL GetLayout(CANDLayout &cLayout) CONST;
	BOOL GetLayout(CANDLayout &cLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayoutColors(CUIntArray &nColors) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutLabelsFont(LPLOGFONT pLabelsFont) CONST;
	BOOL GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutValuesFont(LPLOGFONT pValuesFont) CONST;
	BOOL GetLayoutInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetRetrieveMode(UINT &nMode) CONST;
	BOOL GetRetrieveSpeed(UINT &nSpeed) CONST;
	BOOL GetRetrieveInterval(CTimeSpan &tInterval) CONST;
	BOOL GetRetrieveStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveStopTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CANDPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CANDWnd *GetParent() CONST;

private:
	VOID EnumLayouts();

	BOOL FindLayout() CONST;
	BOOL FindLayout(CANDLayout &cLayout) CONST;

	BOOL InitializeLayout(CANDLayout &cLayout) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDOpenDialog)
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
	//{{AFX_MSG(CANDOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSettings();
	afx_msg void OnFind();
	afx_msg void OnRemove();
	afx_msg void OnEditchangeTitle();
	afx_msg void OnSelchangeTitle();
	afx_msg void OnTypeNormal();
	afx_msg void OnTypeGeneric();
	afx_msg void OnTypeTemporary();
	afx_msg void OnRealtimeMode();
	afx_msg void OnHistoryMode();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDRetrieveThread thread

// Specify the alphanumeric display retrieve thread action codes
#define ANDRETRIEVETHREAD_ACTION_STOP   0
#define ANDRETRIEVETHREAD_ACTION_AUTOFORWARD   1
#define ANDRETRIEVETHREAD_ACTION_AUTOBACKWARD   2
#define ANDRETRIEVETHREAD_ACTION_MANUALFORWARD   3
#define ANDRETRIEVETHREAD_ACTION_MANUALBACKWARD   4
#define ANDRETRIEVETHREAD_ACTION_PSEUDOREALTIME   5
#define ANDRETRIEVETHREAD_ACTION_TYPES   6

class CANDRetrieveThread : public CThread
{
	DECLARE_DYNCREATE(CANDRetrieveThread)

	// Construction
public:
	CANDRetrieveThread();

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
	HANDLE  m_bInit[2];
	HANDLE  m_hAction[ANDRETRIEVETHREAD_ACTION_TYPES];
private:
	CHistoryTMProcessEngine  m_cTMProcessEngine;
	CTMEnvironment  m_cTMEnvironment;

	// Operations
public:
	BOOL Start(class CANDWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime);
	BOOL Stop();

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
	//{{AFX_VIRTUAL(CANDRetrieveThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANDRetrieveThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDPrintThread thread

class CANDPrintThread : public CThread
{
	DECLARE_DYNCREATE(CANDPrintThread)

	// Construction
public:

	// Attributes
private:
	CANDPrintJobs  m_pPrintJobs;
private:
	CEvent  m_cEvent;

	// Operations
public:
	BOOL Start(class CANDWnd *pParentWnd);
	BOOL Stop();

	BOOL SetPrintJobs(CONST CANDPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CANDPrintJobs &pPrintJobs) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDPrintThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANDPrintThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDToolBar window

class CANDToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CANDToolBar)

	// Construction
public:
	CANDToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CANDToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDStatusBar window

class CANDStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CANDStatusBar)

	// Construction
public:
	CANDStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CANDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CANDStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDToolTip window

class CANDToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CANDToolTip)

	// Construction
public:
	CANDToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CANDToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDView window

class CANDView : public CTextView
{
	DECLARE_DYNCREATE(CANDView)

	// Construction
public:
	CANDView();

	// Attributes
private:
	CANDLayout  m_cLayout;
	CUIntArray  m_nLayoutColors;
	CUIntArray  m_nLayoutColumns;
	CByteArray  m_nLayoutStatus;
	CByteArray  m_bLayoutValues;
	CStringArray  m_szLayoutTables;
	CTMParameters  m_pLayoutValues;
	LOGFONT  m_lfLayoutDefault[4];
	CFont  m_cLayoutFont[2];
	BOOL  m_bLayoutFont;
private:
	CANDToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bInvalidDataMode;
	BOOL  m_bBadDataMode;
	BOOL  m_bToolTipMode;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle);

	BOOL SetLayout(CONST CANDLayout &cLayout);
	BOOL SetLayout(CONST CANDLayout &cLayout, UINT nColumns);
	BOOL SetLayout(CONST CANDLayout &cLayout, CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CANDLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, BOOL bAdjust = FALSE);
	BOOL GetLayout(CANDLayout &cLayout) CONST;
	BOOL GetLayout(CANDLayout &cLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayout(CANDLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetTitleFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetTitleFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetLabelsFont(CFont *pFont = NULL, BOOL bDefault = TRUE);
	BOOL SetLabelsFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetLabelsFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetLabelsFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetItemsFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetItemsFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetItemsFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetValuesFont(CFont *pFont = NULL, BOOL bDefault = TRUE);
	BOOL SetValuesFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetValuesFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetValuesFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;

	BOOL SetOolColors(CONST CUIntArray &nColors);
	BOOL GetOolColors(CUIntArray &nColors) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment);
	BOOL Initialize(CString &szTag, CTimeTag &tTag);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL);
	VOID Reset(CTMEnvironment *pTMEnvironment = NULL);

	BOOL GetParameterInfo(LPCTSTR pszTag, CTMParameter *pTMParameter) CONST;
	BOOL HasParameters() CONST;

	VOID ReduceFonts(BOOL bRestore = FALSE);
	BOOL CanReduceFonts(BOOL bRestore = FALSE) CONST;

	BOOL GetPrintProperties(CANDLayout &cLayout, CStringArray &szColumns, CStringArray &szContents, CTMParameters &pValues, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pLabelsFont, CPtrArray &pItemsFonts) CONST;

	class CANDWnd *GetParent() CONST;

private:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;
	COLORREF LookupColumnColor(UINT nColumn, BYTE nStatus = 0) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnWidth(UINT nColumn, LPCTSTR pszText, BOOL bLabel);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);
	CSize CalcColumnsWidth(CUIntArray &nWidths);

	BOOL ConvertColumnToIndex(INT nColumnGroup, UINT nColumn, INT &nIndex) CONST;
	BOOL ConvertIndexToColumn(INT nIndex, INT &nColumnGroup, UINT &nColumn) CONST;
	BOOL ConvertIndexToColumn(INT nIndex, INT &nColumnGroup) CONST;

	CANDLayoutParameter *FindParameter(INT nRow, INT nIndex) CONST;

	CString ConstructToolTipTitle(CONST CANDLayoutParameter *pParameter, UINT nTip) CONST;
	CString ConstructToolTipText(CONST CANDLayoutParameter *pParameter, UINT nTip) CONST;

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDView)
public:
	virtual VOID RecalcLayout();
public:
	virtual VOID DrawContent(CDC *pDC);
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
	//{{AFX_MSG(CANDView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDWnd frame

// Specify the alphanumeric display types
#define AND_TYPE_NORMAL   1
#define AND_TYPE_GENERIC   2
#define AND_TYPE_TEMPORARY   3
// Specify the alphanumeric display title items
#define AND_TITLEITEM_ID   (1<<0)
#define AND_TITLEITEM_DESCRIPTION   (1<<1)
#define AND_TITLEITEM_LABELS   (1<<1)
#define AND_TITLEITEM_VALUE   (1<<2)
#define AND_TITLEITEM_UNIT   (1<<3)
#define AND_TITLEITEM_CHANGETMUNIT   (1<<4)
#define AND_TITLEITEM_CHANGETIME   (1<<5)
#define AND_TITLEITEM_UPDATETMUNIT   (1<<6)
#define AND_TITLEITEM_UPDATETIME   (1<<7)
#define AND_TITLEITEM_EXPECTEDVALUES   (1<<8)
#ifndef RC_INVOKED
#define AND_TITLEITEMS_DEFAULT   (AND_TITLEITEM_ID | AND_TITLEITEM_DESCRIPTION | AND_TITLEITEM_VALUE | AND_TITLEITEM_UNIT)
#define AND_TITLEITEMS_ALL   (AND_TITLEITEMS_DEFAULT | AND_TITLEITEM_CHANGETMUNIT | AND_TITLEITEM_CHANGETIME | AND_TITLEITEM_UPDATETMUNIT | AND_TITLEITEM_UPDATETIME | AND_TITLEITEM_EXPECTEDVALUES)
#endif
// Specify the alphanumeric display retrieval modes
#define AND_RETRIEVE_EXACTTIME   (1<<0)
#define AND_RETRIEVE_STOPBYTIME   (1<<1)
#define AND_RETRIEVE_STOPBYEND   (1<<2)
#define AND_RETRIEVE_STOPBYREALTIME   (1<<3)
#define AND_RETRIEVE_STOPPED   (1<<4)
#define AND_RETRIEVE_RELATIVE   (1<<5)
#define AND_RETRIEVE_AUTOFORWARD   (1<<6)
#define AND_RETRIEVE_AUTOBACKWARD   (1<<7)
#define AND_RETRIEVE_MANUALFORWARD   (1<<8)
#define AND_RETRIEVE_MANUALBACKWARD   (1<<9)
#define AND_RETRIEVE_PSEUDOREALTIME   (1<<10)
// Specify the alphanumeric display print modes
#define AND_PRINT_ALL   (1<<0)
#define AND_PRINT_FIRSTSIDE   (1<<1)
#define AND_PRINT_LASTSIDE   (1<<2)
#define AND_PRINT_UNDERLINEOOL   (1<<3)
#define AND_PRINT_COLORLEGEND   (1<<4)
#define AND_PRINT_CUSTOMLAYOUT   (1<<5)
#define AND_PRINT_CLEARCOMMENTS   (1<<6)
#define AND_PRINT_ATTIME   (1<<7)
#define AND_PRINT_ATDAILYTIME   (1<<8)
#define AND_PRINT_ATEVENT   (1<<9)
#define AND_PRINT_REPEATBYINTERVAL   (1<<10)
#define AND_PRINT_REPEATSTOPBYCOUNT   (1<<11)
#define AND_PRINT_REPEATSTOPBYTIME   (1<<12)
#define AND_PRINT_DAILYREPEATSTOPBYCOUNT   (1<<13)
#define AND_PRINT_DAILYREPEATSTOPBYTIME   (1<<14)
#define AND_PRINT_ACTIVE   (1<<15)
// Specify the alphanumeric display print fonts
#define AND_PRINTFONT_TITLE   0
#define AND_PRINTFONT_SUBTITLE   1
#define AND_PRINTFONT_OPERATINGDETAILS   2
#define AND_PRINTFONT_OPERATINGMODE   3
#define AND_PRINTFONT_LISTITEMSTITLE   4
#define AND_PRINTFONT_LISTITEMSLABELS   5
#define AND_PRINTFONT_FOOTER   6
#define AND_PRINTFONT_NOTICE   7
#define AND_PRINTFONT_LOGO   8
#define AND_PRINTFONTS   9
// Specify the alphanumeric display out-of-limit colors
#define AND_OOLCOLOR_NOLIMIT   0
#define AND_OOLCOLOR_SOFTLIMIT   1
#define AND_OOLCOLOR_HARDLIMIT   2
#define AND_OOLCOLOR_DELTALIMIT   3
#define AND_OOLCOLOR_CONSISTENCYLIMIT   4
// Specify the alphanumeric display statusbar pane identifiers
#define ID_AND_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_AND_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_AND_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class CANDWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CANDWnd)

	// Construction
public:
	CANDWnd();

	// Attributes
private:
	CANDToolBar  m_wndToolBar;
	CANDStatusBar  m_wndStatusBar;
	CANDView  m_wndView;
private:
	CANDOpenDialog  m_dlgOpen;
	CANDSettingsDialog  m_dlgSettings;
	CANDLinkagesDialog  m_dlgLinkages;
	CANDRetrieveDialog  m_dlgRetrievals;
	CANDParametersDialog  m_dlgParameters;
private:
	CANDRetrieveThread  m_cRetrieveThread;
	CANDPrintThread  m_cPrintThread;
private:
	LONG  m_bRetrieveFlag;
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
private:
	CString  m_szTMUnit;
	CTimeTag  m_tTMUnit;
	UINT  m_nTMUnit;
	WORD  m_wTMUnit;

	// Operations
public:
	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(CONST CANDLayout &cLayout);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CANDLayout &cLayout, CONST CUIntArray &nColumns);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(CONST CANDLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CANDLayout &cLayout) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayout(CANDLayout &cLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(CANDLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetTitleFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetTitleFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetLabelsFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetLabelsFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetLabelsFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetLabelsFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetItemsFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetItemsFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetItemsFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetValuesFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetValuesFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetValuesFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetValuesFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;

	BOOL SetOolColors(CONST CUIntArray &nColors);
	BOOL GetOolColors(CUIntArray &nColors) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL ProcessRealtimeData();

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

	VOID SetParameterInfo(LPCTSTR pszTag);
	BOOL GetParameterInfo(LPCTSTR pszTag, CTMParameter *pTMParameter) CONST;

	BOOL SetPrintJobs(CONST CANDPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CANDPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CANDPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	CANDWnd *Find(INT nType, UINT nMode, LPCTSTR pszName) CONST;

	VOID SetUpdateInfo();
	VOID SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, WORD wQuality);
	BOOL GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, WORD &wQuality) CONST;

private:
	BOOL CreateToolBar();
	BOOL CreateStatusBar();
	BOOL CreateView();

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateModePane();
	VOID UpdateTypePane();

	VOID UpdateData();

	BOOL LoadLayout(LPCTSTR pszLayout, CANDLayout &cLayout);
	BOOL HasLayout() CONST;

	BOOL StartSchedulePrintJobs();
	BOOL IsSchedulingPrintJobs() CONST;
	BOOL StopSchedulePrintJobs();

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CANDPrintJobInfo *pJobInfo, CANDLayout &cLayout, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szColumns, CStringArray &szContents, CTMParameters &pValues, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pLabelsFont, CPtrArray &pItemsFonts) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CANDPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CANDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTMParameters &pValues, CONST CUIntArray &nOOLColors, CONST LOGFONT *pTitleFont, CONST LOGFONT *pLabelsFont, CONST CPtrArray &pItemsFonts);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CANDPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, CONST CANDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CUIntArray &nOOLColors, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CONST CUIntArray &nOOLColors, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(CONST CANDLayout &cLayout) CONST;
	CString GetPrintDocOperatingDetails(CONST CANDPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST;
	CString GetPrintDocOperatingMode(CONST CANDPrintJobInfo *pJobInfo, CONST CUIntArray &nOOLColors) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	BOOL GetPrintDocParameterAttributes(CONST CANDLayout &cLayout, CONST CStringArray &szColumns, CONST CTMParameters &pValues, CONST CUIntArray &nOOLColors, INT nRow, INT nColumn, UINT &nAlignment, UINT &nStatus, COLORREF &nColor) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CANDLayout &cLayout, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pLabelsFont, CONST CPtrArray &pItemsFonts, CFont &cTitleFont, CFont &cLabelsFont, CPtrArray &cItemsFonts) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST CANDLayout &cLayout, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pLabelsFont, CONST CPtrArray &pItemsFonts, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CONST CANDLayout &cLayout, INT nColumn, CStringArray &szContents, CFont *pLabelsFont, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CANDWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Initialize(BOOL bFlag);
	virtual BOOL Initialize(CTMEnvironment *pTMEnvironment);
	virtual BOOL Initialize(CString &szTag, CTimeTag &tTag);
	virtual BOOL InitializeTMData(UINT nMode);
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
	virtual VOID ReduceFonts(BOOL bRestore = FALSE);
	virtual BOOL CanReduceFonts(BOOL bRestore = FALSE) CONST;
	virtual VOID UpdateSysMenu(CMenu *pMenu);
	virtual VOID UpdateBars();
public:
	virtual BOOL Print(PRINTDLG *pPrintInfo = NULL);
	virtual BOOL CanPrint() CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseOpenDialog(UINT nCode);
	BOOL OnCloseSettingsDialog(UINT nCode);
	BOOL OnCloseRetrieveDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CANDWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettings();
	afx_msg void OnLinkages();
	afx_msg void OnParameters();
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
	afx_msg void OnUpdateLinkages(CCmdUI *pCmdUI);
	afx_msg void OnUpdateParameters(CCmdUI *pCmdUI);
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


#endif // __AND_H__
