// OOL.H : Out-of-limit Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the out-of-limit display related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/25 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __OOL_H__
#define __OOL_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// COOLPrintJobInfo

class COOLPrintJobInfo : public CObject
{
	// Construction
public:
	COOLPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbEvent;
		INT  cbProfile;
		INT  cbComments;
		UINT  nPrintMode;
		UINT  nPrintByCount;
		UINT  nPrintCount[2];
		UINT  nRepeatStopByCount[2];
		TIMEKEY  tPrintAtTime;
		TIMEKEY  tPrintAtDailyTime;
		TIMEKEY  tPrintByTime[2];
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
	UINT  m_nPrintByCount;
	UINT  m_nPrintCount[2];
	UINT  m_nRepeatStopByCount[2];
	CTimeKey  m_tPrintAtTime;
	CTimeKey  m_tPrintByTime[2];
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
	BOOL SetPrintByTime(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetPrintByTime(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
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

	VOID Copy(CONST COOLPrintJobInfo *pJobInfo);
	BOOL Compare(CONST COOLPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLPrintJobs

class COOLPrintJobs : public CPtrArray
{
	// Construction
public:
	COOLPrintJobs();
	~COOLPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(COOLPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	COOLPrintJobInfo *GetAt(INT nIndex) CONST;
	COOLPrintJobInfo *operator[](INT nIndex) CONST;

	TIMEKEY Schedule();

	VOID RemoveAll();

	BOOL Copy(CONST COOLPrintJobs *pPrintJobs);
	BOOL Compare(CONST COOLPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLParameterFilter

#define OOLPARAMETERFILTER_SHOW_ALLTIME   (1<<0)
#define OOLPARAMETERFILTER_SHOW_NEVER   (1<<1)
#define OOLPARAMETERFILTER_SHOW_INTERVAL   (1<<2)
#define OOLPARAMETERFILTER_BEHAVIOR_EVENT   (1<<3)
#define OOLPARAMETERFILTER_BEHAVIOR_BRINGTOTOP   (1<<4)
#define OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE   (1<<5)
#define OOLPARAMETERFILTER_BEHAVIOR_INLIMIT   (1<<6)
#define OOLPARAMETERFILTER_BEHAVIOR_FLASH   (1<<7)
#define OOLPARAMETERFILTER_BEHAVIOR_AUTOSCROLL   (1<<8)
#define OOLPARAMETERFILTER_ALERT_AUDITION   (1<<9)
#define OOLPARAMETERFILTER_ALERT_NOTIFICATION   (1<<10)

class COOLParameterFilter : public CObject
{
	// Construction
public:
	COOLParameterFilter();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbTag;
		INT  cbAudition;
		INT  cbNotification;
		UINT  nOptions;
		TIMEKEY  tRange[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szTag;
	CString  m_szAudition;
	CString  m_szNotification;
	CTimeKey  m_tRange[2];
	UINT  m_nOptions;

	// Operations
public:
	VOID SetTag(LPCTSTR pszTag);
	CString GetTag() CONST;

	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;
	BOOL SetTimeRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetTimeRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetAudition(LPCTSTR pszAudition);
	CString GetAudition() CONST;
	BOOL SetNotification(LPCTSTR pszNotification);
	CString GetNotification() CONST;

	VOID Copy(CONST COOLParameterFilter *pFilter);
	BOOL Compare(CONST COOLParameterFilter *pFilter) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLParameterFilters

class COOLParameterFilters : public CPtrArray
{
	// Construction
public:
	COOLParameterFilters();
	~COOLParameterFilters();

	// Attributes
public:

	// Operations
public:
	INT Add(COOLParameterFilter *pFilter);

	INT Find(LPCTSTR pszTag) CONST;

	COOLParameterFilter *GetAt(INT nIndex) CONST;
	COOLParameterFilter *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST COOLParameterFilters *pFilters);
	BOOL Compare(CONST COOLParameterFilters *pFilters) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszTag, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsLayoutPage dialog

#define IDC_OOLSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC   1003
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME   1004
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW   1005
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE   1006
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER   1007
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_REMOVE   1008
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_SHOWDATA   1009
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA   1010
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_BADDATA   1011
#define IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS   1012
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS   1013
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1014
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1015
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS   1016
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1017
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1018
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES   1019
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1020
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE   1021
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1022
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE   1023
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1024
#define IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1025

class COOLSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(COOLSettingsLayoutPage)

	// Construction
public:
	COOLSettingsLayoutPage();

	// Attributes
private:
	CUIntArray  m_nColumns[2];
	LOGFONT  m_fntTitle[2];
	LOGFONT  m_fntItems[2];
	BOOL  m_bInvalidData[2];
	BOOL  m_bBadData[2];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;
	CStringArray  m_szColumns;
	INT  m_nColumnIndex;

	// Dialog Data
	//{{AFX_DATA(COOLSettingsLayoutPage)
	enum { IDD = IDD_OOL_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetBadDataMode(BOOL &bEnable) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class COOLSettingsDialog *GetParentDialog() CONST;
	class COOLWnd *GetParentDisplay() CONST;

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
	//{{AFX_VIRTUAL(COOLSettingsLayoutPage)
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
	//{{AFX_MSG(COOLSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnInsertColumnBefore();
	afx_msg void OnInsertColumnAfter();
	afx_msg void OnRemoveColumn();
	afx_msg void OnInvalidData();
	afx_msg void OnBadData();
	afx_msg void OnToolTips();
	afx_msg void OnTitleFont();
	afx_msg void OnItemsFont();
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
// COOLSettingsFilteringPage dialog

#define IDC_OOLSETTINGS_FILTERINGPAGE_DETAILS   1001
#define IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER_STATIC   1002
#define IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER   1003
#define IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS   1004
#define IDC_OOLSETTINGS_FILTERINGPAGE_ADD   1005
#define IDC_OOLSETTINGS_FILTERINGPAGE_REMOVE   1006
#define IDC_OOLSETTINGS_FILTERINGPAGE_REMOVEALL   1007
#define IDC_OOLSETTINGS_FILTERINGPAGE_OPTIONS   1008
#define IDC_OOLSETTINGS_FILTERINGPAGE_SHOW   1009
#define IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_ALLTIME   1010
#define IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_NEVER   1011
#define IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME   1012
#define IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME   1013
#define IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME_STATIC   1014
#define IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME   1015
#define IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR   1016
#define IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_ALERTASEVENT   1017
#define IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP   1018
#define IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE   1019
#define IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT   1020
#define IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH   1021
#define IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOSCROLL   1022
#define IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION_STATIC   1023
#define IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION   1024
#define IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION_STATIC   1025
#define IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION   1026
#define IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS_STATIC   1027
#define IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS   1028
#define IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_COLOR_STATIC   1029
#define IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_COLOR   1030

// Specify the out-of-limit display settings filtering page related limits
#define OOLSETTINGSFILTERINGPAGE_SHOW_DEFAULTINTERVAL   MINUTESPERHOUR

class COOLSettingsFilteringPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(COOLSettingsFilteringPage)

	// Construction
public:
	COOLSettingsFilteringPage();

	// Attributes
private:
	COOLParameterFilters  m_pFilters[2];
	CUIntArray  m_nColors[2];

	// Dialog Data
	//{{AFX_DATA(COOLSettingsFilteringPage)
	enum { IDD = IDD_OOL_SETTINGS_FILTERINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetFilters(COOLParameterFilters &pFilters) CONST;
	BOOL GetColors(CUIntArray &nColors) CONST;

	class COOLSettingsDialog *GetParentDialog() CONST;
	class COOLWnd *GetParentDisplay() CONST;

private:
	BOOL EnumParameters();
	BOOL EnumFilters();
	BOOL EnumAuditions();
	BOOL EnumNotifications();
	BOOL EnumStatusColors();

	VOID SetFilterInfo();
	VOID GetFilterInfo(COOLParameterFilter *pFilter) CONST;
	COOLParameterFilter *FindFilter() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COOLSettingsFilteringPage)
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
	//{{AFX_MSG(COOLSettingsFilteringPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddFilter();
	afx_msg void OnRemoveFilter();
	afx_msg void OnRemoveAllFilters();
	afx_msg void OnShowAllTime();
	afx_msg void OnShowNever();
	afx_msg void OnShowIntervalTime();
	afx_msg void OnBehaviorAsEvent();
	afx_msg void OnBehaviorBringToTop();
	afx_msg void OnBehaviorAutoacknowledge();
	afx_msg void OnBehaviorInLimit();
	afx_msg void OnBehaviorFlash();
	afx_msg void OnBehaviorAutoscroll();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeFilter();
	afx_msg void OnSelchangeAudition();
	afx_msg void OnSelchangeNotification();
	afx_msg void OnSelchangeColorsStatus();
	afx_msg void OnSelchangeColorsColor();
	afx_msg void OnSpinchangeIntervalStartTime();
	afx_msg void OnSpinchangeIntervalStopTime();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsRetrievingPage dialog

#define IDC_OOLSETTINGS_RETRIEVINGPAGE_DETAILS   1001
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC   1002
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE   1003
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_INSPECT   1004
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO   1005
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS   1006
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC   1007
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT   1008
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC   1009
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY   1010
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC   1011
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT   1012
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC   1013
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE   1014
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC   1015
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME   1016
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO   1017
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME   1018
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC   1019
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME   1020
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC   1021
#define IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE   1022

class COOLSettingsRetrievingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(COOLSettingsRetrievingPage)

	// Construction
public:
	COOLSettingsRetrievingPage();

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(COOLSettingsRetrievingPage)
	enum { IDD = IDD_OOL_SETTINGS_RETRIEVINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetDataSourceFileName(CString &szFileName) CONST;

	class COOLSettingsDialog *GetParentDialog() CONST;
	class COOLWnd *GetParentDisplay() CONST;

private:
	VOID EnumDataSources();
	VOID ShowDataSourceInfo();

	BOOL CheckDataSource(LPCTSTR pszFileName) CONST;
	BOOL CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST;

	CString FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COOLSettingsRetrievingPage)
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
	//{{AFX_MSG(COOLSettingsRetrievingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnInspect();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeFileName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsPrintingComments window

class COOLSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(COOLSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COOLSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsPrintingPage dialog

#define IDC_OOLSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_OOLSETTINGS_PRINTINGPAGE_NAME_STATIC   1002
#define IDC_OOLSETTINGS_PRINTINGPAGE_NAME   1003
#define IDC_OOLSETTINGS_PRINTINGPAGE_ADDNAME   1004
#define IDC_OOLSETTINGS_PRINTINGPAGE_REMOVENAME   1005
#define IDC_OOLSETTINGS_PRINTINGPAGE_REMOVEALLNAMES   1006
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES   1007
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC   1008
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE   1009
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS   1010
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL   1011
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE   1012
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE   1013
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC   1014
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT   1015
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME   1016
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME   1017
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC   1018
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME   1019
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND   1020
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS   1021
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC   1022
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT   1023
#define IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS   1024

// Specify the out-of-limit display settings printing page related limits
#define OOLSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMOOLS   1
#define OOLSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMOOLS   10000
#define OOLSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTOOLS   25
#define OOLSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTINTERVAL   MINUTESPERHOUR

class COOLSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(COOLSettingsPrintingPage)

	// Construction
public:
	COOLSettingsPrintingPage();

	// Attributes
private:
	COOLPrintJobs  m_pJobs[2];
private:
	COOLSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(COOLSettingsPrintingPage)
	enum { IDD = IDD_OOL_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(COOLPrintJobs &pJobs) CONST;

	class COOLSettingsDialog *GetParentDialog() CONST;
	class COOLWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	COOLPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COOLSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST COOLPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COOLSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnAddName();
	afx_msg void OnRemoveName();
	afx_msg void OnRemoveAllNames();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnPrintAll();
	afx_msg void OnPrintBySide();
	afx_msg void OnPrintByTime();
	afx_msg void OnPrintColorLegend();
	afx_msg void OnChangePrintSide();
	afx_msg void OnSpinchangePrintSideCount();
	afx_msg void OnSpinchangePrintStartTime();
	afx_msg void OnSpinchangePrintStopTime();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsPrintJobsPage dialog

#define IDC_OOLSETTINGS_PRINTJOBSPAGE_DETAILS   1001
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC   1002
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS   1003
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB   1004
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC   1005
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS   1006
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_REMOVEJOB   1007
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR   1008
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME   1009
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME   1010
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME   1011
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC   1012
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME   1013
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT   1014
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT   1015
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC   1016
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION   1017
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC   1018
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE   1019
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME  1020
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC   1021
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME   1022
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC   1023
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES   1024
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC   1025
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES   1026
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME   1027
#define IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME   1028

// Specify the out-of-limit display settings print jobs page related repetition types
#define OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY   1
#define OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY   2
// Specify the out-of-limit display settings print jobs page related limits
#define OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL   1
#define OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL   MINUTESPERHOUR
#define OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES   1
#define OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES   10000
#define OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES   10

class COOLSettingsPrintJobsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(COOLSettingsPrintJobsPage)

	// Construction
public:
	COOLSettingsPrintJobsPage();

	// Attributes
private:
	COOLPrintJobs  m_pJobs[2];

	// Dialog Data
	//{{AFX_DATA(COOLSettingsPrintJobsPage)
	enum { IDD = IDD_OOL_SETTINGS_PRINTJOBSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(COOLPrintJobs &pJobs) CONST;

	class COOLSettingsDialog *GetParentDialog() CONST;
	class COOLWnd *GetParentDisplay() CONST;

private:
	BOOL EnumJobs();
	BOOL EnumEvents();

	VOID ShowJobInfo();
	BOOL CheckJobInfo() CONST;
	COOLPrintJobInfo *FindJobInfo(BOOL bActive = FALSE) CONST;

	VOID SetJobRepetitionInfo();
	UINT GetJobRepetitionType() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COOLSettingsPrintJobsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST COOLPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COOLSettingsPrintJobsPage)
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
// COOLSettingsTabCtrl window

class COOLSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(COOLSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COOLSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsDialog

class COOLSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(COOLSettingsDialog)

	// Construction
public:
	COOLSettingsDialog();

	// Attributes
private:
	COOLSettingsTabCtrl  m_wndTabCtrl;
	COOLSettingsLayoutPage  m_pageLayout;
	COOLSettingsFilteringPage  m_pageFiltering;
	COOLSettingsRetrievingPage  m_pageRetrieving;
	COOLSettingsPrintingPage  m_pagePrinting;
	COOLSettingsPrintJobsPage  m_pagePrintJobs;

	// Operations
public:
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetParameterFilters(COOLParameterFilters &pFilters) CONST;
	BOOL GetFilterColors(CUIntArray &nColors) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(COOLPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class COOLOpenDialog *GetParentDialog() CONST;
	class COOLWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSettingsDialog)
public:
	virtual BOOL OnDataExchange(HWND hPage, CONST COOLPrintJobs &pJobs);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COOLSettingsDialog)
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
// COOLLinkagesDialog dialog

#define IDC_OOL_LINKAGES_DETAILS   1001
#define IDC_OOL_LINKAGES_NAME_STATIC   1002
#define IDC_OOL_LINKAGES_NAME   1003
#define IDC_OOL_LINKAGES_DISPLAYS_STATIC  1004
#define IDC_OOL_LINKAGES_DISPLAYS   1005
#define IDC_OOL_LINKAGES_LIST_STATIC   1006
#define IDC_OOL_LINKAGES_LIST   1007
#define IDC_OOL_LINKAGES_ADD   1008
#define IDC_OOL_LINKAGES_REMOVE   1009
#define IDC_OOL_LINKAGES_REMOVEALL   1010
#define IDC_OOL_LINKAGES_HELP   1011

class COOLLinkagesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLLinkagesDialog)

	// Construction
public:
	COOLLinkagesDialog();   // standard constructor

	// Attributes
private:
	CPtrArray  m_pDisplays[3];

	// Dialog Data
	//{{AFX_DATA(COOLLinkagesDialog)
	enum { IDD = IDD_OOL_LINKAGES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class COOLWnd *GetParent() CONST;

private:
	BOOL EnumDisplays();

	INT FindDisplay(LPCTSTR pszName, BOOL bLinked = FALSE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLLinkagesDialog)
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
	//{{AFX_MSG(COOLLinkagesDialog)
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
// COOLParametersLimitsPage dialog

#define IDC_OOL_PARAMETERS_LIMITSPAGE_NAME_STATIC   1001
#define IDC_OOL_PARAMETERS_LIMITSPAGE_NAME   1002
#define IDC_OOL_PARAMETERS_LIMITSPAGE_ID_STATIC   1003
#define IDC_OOL_PARAMETERS_LIMITSPAGE_ID   1004
#define IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE_STATIC   1005
#define IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE   1006
#define IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS_STATIC   1007
#define IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS   1008
#define IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS_STATIC   1009
#define IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS   1010

class COOLParametersLimitsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(COOLParametersLimitsPage)

	// Construction
public:
	COOLParametersLimitsPage();

	// Attributes
private:
	INT  m_nOolTableID;
	INT  m_nOolLimitID;
	ULONGLONG  m_nOolTableType;
	CUIntArray  m_nOolTableRefs;
	CUIntArray  m_nOolValidityRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(COOLParametersLimitsPage)
	enum { IDD = IDD_OOL_PARAMETERS_LIMITSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST COolParameter *pOolParameter);
	VOID ShowLimitsInfo();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COOLParametersLimitsPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COOLParametersLimitsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLParametersFolderTabCtrl window

class COOLParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(COOLParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class COOLParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COOLParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLParametersFolder

class COOLParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(COOLParametersFolder)

	// Construction
public:
	COOLParametersFolder();

	// Attributes
private:
	COOLParametersFolderTabCtrl  m_wndTabCtrl;
	COOLParametersLimitsPage  m_pageLimits;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST COolParameter *pOolParameter = NULL);

	class COOLParametersDialog *GetParentDialog() CONST;
	class COOLWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COOLParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLParametersDialog dialog

#define IDC_OOL_PARAMETERS_DETAILS   1001
#define IDC_OOL_PARAMETERS_ITEM_STATIC   1002
#define IDC_OOL_PARAMETERS_ITEM   1003
#define IDC_OOL_PARAMETERS_FOLDER   1004
#define IDC_OOL_PARAMETERS_HELP   1005

class COOLParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLParametersDialog)

	// Construction
public:
	COOLParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szParameter;
private:
	COOLParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(COOLParametersDialog)
	enum { IDD = IDD_OOL_PARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter);

	class COOLWnd *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLParametersDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLAcknowledgeDialog dialog

#define IDC_OOL_ACKNOWLEDGE_DETAILS   1001
#define IDC_OOL_ACKNOWLEDGE_COMMENT   1002
#define IDC_OOL_ACKNOWLEDGE_PARAMETERS_STATIC   1003
#define IDC_OOL_ACKNOWLEDGE_PARAMETERS   1004
#define IDC_OOL_ACKNOWLEDGE_PARAMETERS_REMOVE   1005
#define IDC_OOL_ACKNOWLEDGE_PARAMETERS_REMOVEALL   1006
#define IDC_OOL_ACKNOWLEDGE_AUDITIONS_STATIC   1007
#define IDC_OOL_ACKNOWLEDGE_AUDITIONS   1008
#define IDC_OOL_ACKNOWLEDGE_AUDITIONS_REMOVE   1009
#define IDC_OOL_ACKNOWLEDGE_AUDITIONS_REMOVEALL   1010
#define IDC_OOL_ACKNOWLEDGE_HELP   1011

class COOLAcknowledgeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLAcknowledgeDialog)

	// Construction
public:
	COOLAcknowledgeDialog();   // standard constructor

	// Attributes
private:
	COolParameters  m_pOolParameters;
	CEventList  m_pOolAuditions;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(COOLAcknowledgeDialog)
	enum { IDD = IDD_OOL_ACKNOWLEDGE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

private:
	BOOL EnumParameters();
	BOOL EnumAuditions();

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	class COOLWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLAcknowledgeDialog)
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
	//{{AFX_MSG(COOLAcknowledgeDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRemoveParameter();
	afx_msg void OnRemoveAllParameters();
	afx_msg void OnRemoveAudition();
	afx_msg void OnRemoveAllAuditions();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLRetrieveDialog dialog

#define IDC_OOL_RETRIEVE_DETAILS   1001
#define IDC_OOL_RETRIEVE_TITLE_STATIC   1002
#define IDC_OOL_RETRIEVE_TITLE   1003
#define IDC_OOL_RETRIEVE_TYPE_STATIC   1004
#define IDC_OOL_RETRIEVE_TYPE   1005
#define IDC_OOL_RETRIEVE_HISTORY   1006
#define IDC_OOL_RETRIEVE_HISTORY_START_STATIC   1007
#define IDC_OOL_RETRIEVE_HISTORY_STARTTIME   1008
#define IDC_OOL_RETRIEVE_HISTORY_EXACTTIME   1009
#define IDC_OOL_RETRIEVE_HISTORY_STOP_STATIC   1010
#define IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME   1011
#define IDC_OOL_RETRIEVE_HISTORY_STOPTIME   1012
#define IDC_OOL_RETRIEVE_HISTORY_STOPBYEND   1013
#define IDC_OOL_RETRIEVE_HISTORY_PLAYBACKMODE   1014
#define IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC   1015
#define IDC_OOL_RETRIEVE_HISTORY_PSEUDOREALTIME   1016
#define IDC_OOL_RETRIEVE_HISTORY_MANUAL   1017
#define IDC_OOL_RETRIEVE_HISTORY_SPEED_STATIC   1018
#define IDC_OOL_RETRIEVE_HISTORY_SPEED   1019
#define IDC_OOL_RETRIEVE_HISTORY_SLOW   1020
#define IDC_OOL_RETRIEVE_HISTORY_FAST   1021
#define IDC_OOL_RETRIEVE_HISTORY_INTERVAL   1022
#define IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME   1023
#define IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME_STATIC   1024
#define IDC_OOL_RETRIEVE_HELP   1025

// Specify the out-of-limit display retrieve dialog related limits
#define OOLRETRIEVEDIALOG_MINIMUMINTERVAL   1
#define OOLRETRIEVEDIALOG_MAXIMUMINTERVAL   MINUTESPERWEEK
#define OOLRETRIEVEDIALOG_DEFAULTINTERVAL   5

class COOLRetrieveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLRetrieveDialog)

	// Construction
public:
	COOLRetrieveDialog();   // standard constructor

	// Attributes
private:
	CString  m_szTitle;

	// Dialog Data
	//{{AFX_DATA(COOLRetrieveDialog)
	enum { IDD = IDD_OOL_RETRIEVE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);
	INT Create(CWnd *pParentWnd, LPCTSTR pszTitle);

	BOOL GetMode(UINT &nMode) CONST;
	BOOL GetSpeed(UINT &nSpeed) CONST;
	BOOL GetInterval(CTimeSpan &tInterval) CONST;
	BOOL GetStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetStopTime(CTimeKey &tTimeKey) CONST;

	class COOLOpenDialog *GetParentDialog() CONST;
	class COOLWnd *GetParentDisplay() CONST;

private:
	BOOL SetRetrieveInfo();
	BOOL GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLRetrieveDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLRetrieveDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRetrieveByTime();
	afx_msg void OnRetrieveByEnd();
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
// COOLSearchIDDialog dialog

#define IDC_OOL_SEARCHID_ID_STATIC   1001
#define IDC_OOL_SEARCHID_ID   1002
#define IDC_OOL_SEARCHID_DIRECTION   1003
#define IDC_OOL_SEARCHID_DIRECTION_UP   1004
#define IDC_OOL_SEARCHID_DIRECTION_DOWN   1005
#define IDC_OOL_SEARCHID_ALL   1006
#define IDC_OOL_SEARCHID_FIND   1007
#define IDC_OOL_SEARCHID_HELP   1008

class COOLSearchIDDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLSearchIDDialog)

	// Construction
public:
	COOLSearchIDDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(COOLSearchIDDialog)
	enum { IDD = IDD_OOL_SEARCHID_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class COOLWnd *GetParent() CONST;

private:
	VOID EnumParameters();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSearchIDDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLSearchIDDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSearchDescriptionDialog dialog

#define IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION_STATIC   1001
#define IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION   1002
#define IDC_OOL_SEARCHDESCRIPTION_DIRECTION   1003
#define IDC_OOL_SEARCHDESCRIPTION_DIRECTION_UP   1004
#define IDC_OOL_SEARCHDESCRIPTION_DIRECTION_DOWN   1005
#define IDC_OOL_SEARCHDESCRIPTION_ALL   1006
#define IDC_OOL_SEARCHDESCRIPTION_CASE   1007
#define IDC_OOL_SEARCHDESCRIPTION_WORD   1008
#define IDC_OOL_SEARCHDESCRIPTION_FIND   1009
#define IDC_OOL_SEARCHDESCRIPTION_HELP   1010

class COOLSearchDescriptionDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLSearchDescriptionDialog)

	// Construction
public:
	COOLSearchDescriptionDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szDescriptions;

	// Dialog Data
	//{{AFX_DATA(COOLSearchDescriptionDialog)
	enum { IDD = IDD_OOL_SEARCHDESCRIPTION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class COOLWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSearchDescriptionDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLSearchDescriptionDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindDescription();
	afx_msg void OnSelchangeDescription();
	afx_msg void OnEditchangeDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSearchValueDialog dialog

#define IDC_OOL_SEARCHVALUE_VALUE_STATIC   1001
#define IDC_OOL_SEARCHVALUE_VALUE   1002
#define IDC_OOL_SEARCHVALUE_DIRECTION   1003
#define IDC_OOL_SEARCHVALUE_DIRECTION_UP   1004
#define IDC_OOL_SEARCHVALUE_DIRECTION_DOWN   1005
#define IDC_OOL_SEARCHVALUE_ALL   1006
#define IDC_OOL_SEARCHVALUE_CASE   1007
#define IDC_OOL_SEARCHVALUE_FIND   1008
#define IDC_OOL_SEARCHVALUE_HELP   1009

class COOLSearchValueDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLSearchValueDialog)

	// Construction
public:
	COOLSearchValueDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szValues;

	// Dialog Data
	//{{AFX_DATA(COOLSearchValueDialog)
	enum { IDD = IDD_OOL_SEARCHVALUE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class COOLWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSearchValueDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLSearchValueDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindValue();
	afx_msg void OnSelchangeValue();
	afx_msg void OnEditchangeValue();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSearchLimitDialog dialog

#define IDC_OOL_SEARCHLIMIT_LIMIT_STATIC   1001
#define IDC_OOL_SEARCHLIMIT_LIMIT   1002
#define IDC_OOL_SEARCHLIMIT_DIRECTION   1003
#define IDC_OOL_SEARCHLIMIT_DIRECTION_UP   1004
#define IDC_OOL_SEARCHLIMIT_DIRECTION_DOWN   1005
#define IDC_OOL_SEARCHLIMIT_ALL   1006
#define IDC_OOL_SEARCHLIMIT_FIND   1007
#define IDC_OOL_SEARCHLIMIT_HELP   1008

class COOLSearchLimitDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLSearchLimitDialog)

	// Construction
public:
	COOLSearchLimitDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(COOLSearchLimitDialog)
	enum { IDD = IDD_OOL_SEARCHLIMIT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class COOLWnd *GetParent() CONST;

private:
	VOID EnumLimits();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSearchLimitDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLSearchLimitDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindLimit();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSearchUnitDialog dialog

#define IDC_OOL_SEARCHUNIT_UNIT_STATIC   1001
#define IDC_OOL_SEARCHUNIT_UNIT   1002
#define IDC_OOL_SEARCHUNIT_DIRECTION   1003
#define IDC_OOL_SEARCHUNIT_DIRECTION_UP   1004
#define IDC_OOL_SEARCHUNIT_DIRECTION_DOWN   1005
#define IDC_OOL_SEARCHUNIT_ALL   1006
#define IDC_OOL_SEARCHUNIT_CASE   1007
#define IDC_OOL_SEARCHUNIT_FIND   1008
#define IDC_OOL_SEARCHUNIT_HELP   1009

class COOLSearchUnitDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLSearchUnitDialog)

	// Construction
public:
	COOLSearchUnitDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szUnits;

	// Dialog Data
	//{{AFX_DATA(COOLSearchUnitDialog)
	enum { IDD = IDD_OOL_SEARCHUNIT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class COOLWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSearchUnitDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLSearchUnitDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindUnit();
	afx_msg void OnSelchangeUnit();
	afx_msg void OnEditchangeUnit();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSearchOolTypeDialog dialog

#define IDC_OOL_SEARCHOOLTYPE_TYPE_STATIC   1001
#define IDC_OOL_SEARCHOOLTYPE_TYPE   1002
#define IDC_OOL_SEARCHOOLTYPE_DIRECTION   1003
#define IDC_OOL_SEARCHOOLTYPE_DIRECTION_UP   1004
#define IDC_OOL_SEARCHOOLTYPE_DIRECTION_DOWN   1005
#define IDC_OOL_SEARCHOOLTYPE_ALL   1006
#define IDC_OOL_SEARCHOOLTYPE_FIND   1007
#define IDC_OOL_SEARCHOOLTYPE_HELP   1008

class COOLSearchOolTypeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLSearchOolTypeDialog)

	// Construction
public:
	COOLSearchOolTypeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(COOLSearchOolTypeDialog)
	enum { IDD = IDD_OOL_SEARCHOOLTYPE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class COOLWnd *GetParent() CONST;

private:
	VOID EnumOolTypes();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSearchOolTypeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLSearchOolTypeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindOolType();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSearchOolUnitDialog dialog

#define IDC_OOL_SEARCHOOLUNIT_UNIT_STATIC   1001
#define IDC_OOL_SEARCHOOLUNIT_UNIT   1002
#define IDC_OOL_SEARCHOOLUNIT_DIRECTION   1003
#define IDC_OOL_SEARCHOOLUNIT_DIRECTION_UP   1004
#define IDC_OOL_SEARCHOOLUNIT_DIRECTION_DOWN   1005
#define IDC_OOL_SEARCHOOLUNIT_ALL   1006
#define IDC_OOL_SEARCHOOLUNIT_FIND   1007
#define IDC_OOL_SEARCHOOLUNIT_HELP   1008

class COOLSearchOolUnitDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLSearchOolUnitDialog)

	// Construction
public:
	COOLSearchOolUnitDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szOolUnits;

	// Dialog Data
	//{{AFX_DATA(COOLSearchOolUnitDialog)
	enum { IDD = IDD_OOL_SEARCHOOLUNIT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class COOLWnd *GetParent() CONST;

private:
	VOID EnumOolUnits();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSearchOolUnitDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLSearchOolUnitDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindOolUnit();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLSearchOolTimeDialog dialog

#define IDC_OOL_SEARCHOOLTIME_TIME_STATIC   1001
#define IDC_OOL_SEARCHOOLTIME_TIME   1002
#define IDC_OOL_SEARCHOOLTIME_DIRECTION   1003
#define IDC_OOL_SEARCHOOLTIME_DIRECTION_UP   1004
#define IDC_OOL_SEARCHOOLTIME_DIRECTION_DOWN   1005
#define IDC_OOL_SEARCHOOLTIME_ALL   1006
#define IDC_OOL_SEARCHOOLTIME_MATCH   1007
#define IDC_OOL_SEARCHOOLTIME_FIND   1008
#define IDC_OOL_SEARCHOOLTIME_HELP   1009

class COOLSearchOolTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLSearchOolTimeDialog)

	// Construction
public:
	COOLSearchOolTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(COOLSearchOolTimeDialog)
	enum { IDD = IDD_OOL_SEARCHOOLTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class COOLWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLSearchOolTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLSearchOolTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindOolTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLOpenDialog dialog

#define IDC_OOL_OPEN_DETAILS   1001
#define IDC_OOL_OPEN_DISPLAY_STATIC   1002
#define IDC_OOL_OPEN_DISPLAY   1003
#define IDC_OOL_OPEN_SETTINGS   1004
#define IDC_OOL_OPEN_TYPE   1005
#define IDC_OOL_OPEN_TYPE_NORMAL   1006
#define IDC_OOL_OPEN_MODE   1007
#define IDC_OOL_OPEN_MODE_REALTIME   1008
#define IDC_OOL_OPEN_MODE_HISTORY   1009
#define IDC_OOL_OPEN_HELP   1010

class COOLOpenDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(COOLOpenDialog)

	// Construction
public:
	COOLOpenDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	BOOL  m_bLayoutBadData;
	BOOL  m_bLayoutToolTips;
	BOOL  m_bLayoutInvalidData;
	LOGFONT  m_fntLayoutTitle;
	LOGFONT  m_fntLayoutItems;
	CString  m_szRetrieveFileName;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CTimeSpan  m_tRetrieveInterval;
	CUIntArray  m_nLayoutColumns;
	CUIntArray  m_nFilterColors;
	COOLPrintJobs  m_pPrintJobs;
	COOLParameterFilters  m_pParameterFilters;
private:
	COOLSettingsDialog  m_dlgSettings;
	COOLRetrieveDialog  m_dlgRetrievals;

	// Dialog Data
	//{{AFX_DATA(COOLOpenDialog)
	enum { IDD = IDD_OOL_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	CString GetTitle() CONST;
	UINT GetType() CONST;
	UINT GetMode() CONST;

	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetParameterFilters(COOLParameterFilters &pFilters) CONST;
	BOOL GetFilterColors(CUIntArray &nColors) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetRetrieveMode(UINT &nMode) CONST;
	BOOL GetRetrieveSpeed(UINT &nSpeed) CONST;
	BOOL GetRetrieveInterval(CTimeSpan &tInterval) CONST;
	BOOL GetRetrieveStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveStopTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(COOLPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class COOLWnd *GetParent() CONST;

private:
	VOID EnumLayouts();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLOpenDialog)
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
	//{{AFX_MSG(COOLOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSettings();
	afx_msg void OnEditchangeTitle();
	afx_msg void OnSelchangeTitle();
	afx_msg void OnTypeNormal();
	afx_msg void OnRealtimeMode();
	afx_msg void OnHistoryMode();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLRetrieveThread thread

// Specify the out-of-limit display retrieve thread action codes
#define OOLRETRIEVETHREAD_ACTION_STOP   0
#define OOLRETRIEVETHREAD_ACTION_AUTOFORWARD   1
#define OOLRETRIEVETHREAD_ACTION_AUTOBACKWARD   2
#define OOLRETRIEVETHREAD_ACTION_MANUALFORWARD   3
#define OOLRETRIEVETHREAD_ACTION_MANUALBACKWARD   4
#define OOLRETRIEVETHREAD_ACTION_PSEUDOREALTIME   5
#define OOLRETRIEVETHREAD_ACTION_TYPES   6

class COOLRetrieveThread : public CThread
{
	DECLARE_DYNCREATE(COOLRetrieveThread)

	// Construction
public:
	COOLRetrieveThread();

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
	HANDLE  m_hAction[OOLRETRIEVETHREAD_ACTION_TYPES];
private:
	CHistoryTMProcessEngine  m_cTMProcessEngine;
	CTMEnvironment  m_cTMEnvironment;

	// Operations
public:
	BOOL Start(class COOLWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime);
	BOOL Stop();

	BOOL InitializeTMData(COolParameters &pOolParameters, BOOL bBadData = FALSE);
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
	//{{AFX_VIRTUAL(COOLRetrieveThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLRetrieveThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLPrintThread thread

class COOLPrintThread : public CThread
{
	DECLARE_DYNCREATE(COOLPrintThread)

	// Construction
public:

	// Attributes
private:
	COOLPrintJobs  m_pPrintJobs;
private:
	CEvent  m_cEvent;

	// Operations
public:
	BOOL Start(class COOLWnd *pParentWnd);
	BOOL Stop();

	BOOL SetPrintJobs(CONST COOLPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(COOLPrintJobs &pPrintJobs) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLPrintThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COOLPrintThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLToolBar window

class COOLToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(COOLToolBar)

	// Construction
public:
	COOLToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COOLToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLStatusBar window

class COOLStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(COOLStatusBar)

	// Construction
public:
	COOLStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class COOLWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COOLStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLToolTip window

class COOLToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(COOLToolTip)

	// Construction
public:
	COOLToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COOLToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLView window

// Specify the out-of-limit view timer related identifiers
#define OOLVIEW_SEARCH_TIMERID   100
#define OOLVIEW_SEARCH_TIMEOUT   0

class COOLView : public CTextView
{
	DECLARE_DYNCREATE(COOLView)

	// Construction
public:
	COOLView();

	// Attributes
private:
	CString  m_szLayout;
	CUIntArray  m_nLayoutColumns;
private:
	CUIntArray  m_nColors;
	CEventList  m_cAuditions;
	CByteArray  m_bParameters;
	COolParameters  m_pParameters[3];
	COOLParameterFilters  m_pFilters;
	CString  m_szSearchItem;
private:
	COOLToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bInvalidDataMode;
	BOOL  m_bBadDataMode;
	BOOL  m_bToolTipMode;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle);

	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(LPCTSTR pszLayout, UINT nColumns);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemsFont(CFont *pFont);
	BOOL SetItemsFont(CONST LOGFONT *plfFont);
	BOOL GetItemsFont(CFont *pFont) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilters(CONST COOLParameterFilters &pFilters);
	BOOL GetFilters(COOLParameterFilters &pFilters) CONST;
	BOOL SetColors(CONST CUIntArray &nColors);
	BOOL GetColors(CUIntArray &nColors) CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment);
	BOOL Initialize(CString &szTag, CTimeTag &tTag);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL);
	VOID Reset(CTMEnvironment *pTMEnvironment = NULL);

	BOOL Acknowledge(LPCTSTR pszParameter);
	BOOL IsAcknowledged(LPCTSTR pszParameter) CONST;
	BOOL IsAlerted() CONST;

	BOOL SetParameterAlerts(CONST COolParameters &pOolParameters, CEventList &pOolAuditions);
	BOOL GetParameterAlerts(COolParameters &pOolParameters, CEventList &pOolAuditions) CONST;
	BOOL GetParameterInfo(LPCTSTR pszTag, COolParameter *pOolParameter) CONST;
	BOOL GetParameterInfo(COolParameter *pOolParameter) CONST;
	INT GetParameters(COolParameters &pOolParameters) CONST;
	INT GetParametersCount() CONST;
	BOOL HasParameters() CONST;

	BOOL SearchParameterByID(LPCTSTR pszID, BOOL bDown, BOOL bAll);
	BOOL SearchParameterByDescription(LPCTSTR pszDescription, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL SearchParameterByValue(LPCTSTR pszValue, BOOL bDown, BOOL bAll, BOOL bCase);
	BOOL SearchParameterByLimit(LPCTSTR pszLimit, BOOL bDown, BOOL bAll);
	BOOL SearchParameterByUnit(LPCTSTR pszUnit, BOOL bDown, BOOL bAll, BOOL bCase);
	BOOL SearchParameterByOolType(LPCTSTR pszOolType, BOOL bDown, BOOL bAll);
	BOOL SearchParameterByOolUnit(LPCTSTR pszOolUnit, BOOL bDown, BOOL bAll);
	BOOL SearchParameterByOolTime(CONST CTimeKey &tOolTime, BOOL bDown, BOOL bAll, BOOL bMatch);

	BOOL GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, COolParameters &pOolParameters, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST;

	class COOLWnd *GetParent() CONST;

private:
	VOID Alert(CONST CTMEnvironment *pTMEnvironment, CONST CPtrArray &pParameters, CONST CPtrArray &pOolParameters);

	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);

	INT FindParameter(LPCTSTR pszParameter, BOOL bInsert = FALSE) CONST;

	INT FindParameterIndex(INT nIndex) CONST;
	INT DetermineParameterIndex(INT nIndex, BOOL bReverse = FALSE) CONST;

	UINT PointToRow(CONST POINT &point) CONST;
	UINT PointToColumn(CONST POINT &point) CONST;

	CString ConstructToolTipTitle(INT nRow) CONST;
	CString ConstructToolTipText(INT nRow, LPCTSTR pszColumn) CONST;

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

	VOID AdjustColumns();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RecalcLayout();
	virtual VOID RefreshContent();
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
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
	//{{AFX_MSG(COOLView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COOLWnd frame

// Specify the out-of-limit display types
#define OOL_TYPE_GLOBAL   1
#define OOL_TYPE_NORMAL   2
// Specify the out-of-limit display title items
#define OOL_TITLEITEM_ID   (1<<0)
#define OOL_TITLEITEM_DESCRIPTION   (1<<1)
#define OOL_TITLEITEM_VALUE   (1<<2)
#define OOL_TITLEITEM_LIMIT   (1<<3)
#define OOL_TITLEITEM_UNIT   (1<<4)
#define OOL_TITLEITEM_OOLTYPE   (1<<5)
#define OOL_TITLEITEM_OOLTIME   (1<<6)
#define OOL_TITLEITEM_OOLUNIT   (1<<7)
#ifndef RC_INVOKED
#define OOL_TITLEITEMS_DEFAULT   (OOL_TITLEITEM_ID | OOL_TITLEITEM_DESCRIPTION | OOL_TITLEITEM_VALUE | OOL_TITLEITEM_LIMIT | OOL_TITLEITEM_UNIT | OOL_TITLEITEM_OOLTIME)
#define OOL_TITLEITEMS_ALL   (OOL_TITLEITEMS_DEFAULT | OOL_TITLEITEM_OOLTYPE | OOL_TITLEITEM_OOLUNIT)
#endif
// Specify the out-of-limit display retrieval modes
#define OOL_RETRIEVE_EXACTTIME   (1<<0)
#define OOL_RETRIEVE_STOPBYTIME   (1<<1)
#define OOL_RETRIEVE_STOPBYEND   (1<<2)
#define OOL_RETRIEVE_STOPPED   (1<<3)
#define OOL_RETRIEVE_RELATIVE   (1<<4)
#define OOL_RETRIEVE_AUTOFORWARD   (1<<5)
#define OOL_RETRIEVE_AUTOBACKWARD   (1<<6)
#define OOL_RETRIEVE_MANUALFORWARD   (1<<7)
#define OOL_RETRIEVE_MANUALBACKWARD   (1<<8)
#define OOL_RETRIEVE_PSEUDOREALTIME   (1<<9)
// Specify the out-of-limit display print modes
#define OOL_PRINT_ALL   (1<<0)
#define OOL_PRINT_FIRSTSIDE   (1<<1)
#define OOL_PRINT_LASTSIDE   (1<<2)
#define OOL_PRINT_BYTIME   (1<<3)
#define OOL_PRINT_COLORLEGEND   (1<<4)
#define OOL_PRINT_CLEARCOMMENTS   (1<<5)
#define OOL_PRINT_ATTIME   (1<<6)
#define OOL_PRINT_ATDAILYTIME   (1<<7)
#define OOL_PRINT_ATEVENT   (1<<8)
#define OOL_PRINT_REPEATBYINTERVAL   (1<<9)
#define OOL_PRINT_REPEATSTOPBYCOUNT   (1<<10)
#define OOL_PRINT_REPEATSTOPBYTIME   (1<<11)
#define OOL_PRINT_DAILYREPEATSTOPBYCOUNT   (1<<12)
#define OOL_PRINT_DAILYREPEATSTOPBYTIME   (1<<13)
#define OOL_PRINT_ACTIVE   (1<<14)
// Specify the out-of-limit display print fonts
#define OOL_PRINTFONT_TITLE   0
#define OOL_PRINTFONT_SUBTITLE   1
#define OOL_PRINTFONT_OPERATINGDETAILS   2
#define OOL_PRINTFONT_OPERATINGMODE   3
#define OOL_PRINTFONT_LISTITEMSTITLE   4
#define OOL_PRINTFONT_LISTITEMS   5
#define OOL_PRINTFONT_FOOTER   6
#define OOL_PRINTFONT_NOTICE   7
#define OOL_PRINTFONT_LOGO   8
#define OOL_PRINTFONTS   9
// Specify the out-of-limit display colors
#define OOL_OOLCOLOR_SOFTLIMIT   0
#define OOL_OOLCOLOR_HARDLIMIT   1
#define OOL_OOLCOLOR_DELTALIMIT   2
#define OOL_OOLCOLOR_CONSISTENCYLIMIT   3
// Specify the out-of-limit display statusbar pane identifiers
#define ID_OOL_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_OOL_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_OOL_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class COOLWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(COOLWnd)

	// Construction
public:
	COOLWnd();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  nIndex;
		INT  nCount;
		INT  cbColumns[2];
		LOGFONT  sFont[2];
		SCROLLINFO  sScrollInfo[2];
	} DATA, *PDATA, *LPDATA;
private:
	COOLToolBar  m_wndToolBar;
	COOLStatusBar  m_wndStatusBar;
	COOLView  m_wndView;
private:
	COOLOpenDialog  m_dlgOpen;
	COOLSettingsDialog  m_dlgSettings;
	COOLLinkagesDialog  m_dlgLinkages;
	COOLRetrieveDialog  m_dlgRetrievals;
	COOLParametersDialog  m_dlgParameters;
	COOLAcknowledgeDialog  m_dlgAcknowledge;
	COOLSearchIDDialog  m_dlgSearchID;
	COOLSearchUnitDialog  m_dlgSearchUnit;
	COOLSearchValueDialog  m_dlgSearchValue;
	COOLSearchLimitDialog  m_dlgSearchLimit;
	COOLSearchOolTypeDialog  m_dlgSearchOolType;
	COOLSearchOolUnitDialog  m_dlgSearchOolUnit;
	COOLSearchOolTimeDialog  m_dlgSearchOolTime;
	COOLSearchDescriptionDialog  m_dlgSearchDescription;
private:
	COOLRetrieveThread  m_cRetrieveThread;
	COOLPrintThread  m_cPrintThread;
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
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemsFont(CFont *pFont);
	BOOL SetItemsFont(CONST LOGFONT *plfFont);
	BOOL GetItemsFont(CFont *pFont) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetParameterFilters(CONST COOLParameterFilters &pFilters);
	BOOL GetParameterFilters(COOLParameterFilters &pFilters) CONST;
	BOOL SetFilterColors(CONST CUIntArray &nColors);
	BOOL GetFilterColors(CUIntArray &nColors) CONST;

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

	VOID ShowSearchParameterIDDetails();
	VOID ShowSearchParameterDescriptionDetails();
	VOID ShowSearchParameterValueDetails();
	VOID ShowSearchParameterLimitDetails();
	VOID ShowSearchParameterUnitDetails();
	VOID ShowSearchParameterOolTypeDetails();
	VOID ShowSearchParameterOolUnitDetails();
	VOID ShowSearchParameterOolTimeDetails();

	BOOL SearchParameterByID(LPCTSTR pszID, BOOL bDown, BOOL bAll);
	BOOL SearchParameterByDescription(LPCTSTR pszDescription, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL SearchParameterByValue(LPCTSTR pszValue, BOOL bDown, BOOL bAll, BOOL bCase);
	BOOL SearchParameterByLimit(LPCTSTR pszLimit, BOOL bDown, BOOL bAll);
	BOOL SearchParameterByUnit(LPCTSTR pszUnit, BOOL bDown, BOOL bAll, BOOL bCase);
	BOOL SearchParameterByOolType(LPCTSTR pszOolType, BOOL bDown, BOOL bAll);
	BOOL SearchParameterByOolUnit(LPCTSTR pszOolUnit, BOOL bDown, BOOL bAll);
	BOOL SearchParameterByOolTime(CONST CTimeKey &tOolTime, BOOL bDown, BOOL bAll, BOOL bMatch);

	BOOL SetParameterAlerts(CONST COolParameters &pOolParameters, CEventList &pOolAuditions);
	BOOL GetParameterAlerts(COolParameters &pOolParameters, CEventList &pOolAuditions) CONST;
	VOID SetParameterInfo(LPCTSTR pszTag);
	BOOL GetParameterInfo(LPCTSTR pszTag, COolParameter *pOolParameter) CONST;
	BOOL GetParameterInfo(COolParameter *pOolParameter) CONST;

	INT GetParameters(COolParameters &pOolParameters) CONST;
	INT GetParametersCount() CONST;
	BOOL HasParameters() CONST;

	BOOL SetPrintJobs(CONST COOLPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(COOLPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST COOLPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	COOLWnd *Find(INT nType, UINT nMode, LPCTSTR pszName) CONST;

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

	BOOL StartSchedulePrintJobs();
	BOOL IsSchedulingPrintJobs() CONST;
	BOOL StopSchedulePrintJobs();

	BOOL SetParameterFilters(CONST CByteArray &nFilterInfo);
	BOOL GetParameterFilters(CByteArray &nFilterInfo) CONST;

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST COOLPrintJobInfo *pJobInfo, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, INT &nOOLCount, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST COOLPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTextViewAttributes &pAttributes, INT nOOLCount, CONST CUIntArray &nOOLColors, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST COOLPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, INT nOOLCount, CONST CUIntArray &nOOLColors, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszLayout, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CONST CUIntArray &nOOLColors, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(LPCTSTR pszLayout) CONST;
	CString GetPrintDocOperatingDetails(CONST COOLPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST;
	CString GetPrintDocOperatingMode(CONST COOLPrintJobInfo *pJobInfo, INT nOOLCount, CONST CUIntArray &nOOLColors) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CStringArray &szContents, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

private:
	BOOL SetLayoutInfo(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	BOOL GetLayoutInfo(CUIntArray &nColumns, CUIntArray &nWidths, LOGFONT *pTitleFont, LOGFONT *pItemsFont, INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COOLWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Initialize(BOOL bFlag);
	virtual BOOL Initialize(CTMEnvironment *pTMEnvironment);
	virtual BOOL Initialize(CString &szTag, CTimeTag &tTag);
	virtual BOOL InitializeTMData(UINT nMode);
	virtual BOOL InitializeTMData(COolParameters &pOolParameters, BOOL bBadData = FALSE);
	virtual BOOL InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData = FALSE);
	virtual BOOL Check() CONST;
	virtual VOID Update();
	virtual BOOL Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags = 0);
	virtual VOID Reset(CTMEnvironment *pTMEnvironment = NULL);
	virtual BOOL Stop();
public:
	virtual BOOL SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo);
	virtual BOOL LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo);
	virtual BOOL SetLayoutInfo(LPCVOID pData);
	virtual INT GetLayoutInfo(LPVOID *pData = NULL) CONST;
	virtual BOOL QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST;
	virtual BOOL QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST;
	virtual VOID UpdateBars();
public:
	virtual BOOL Print(PRINTDLG *pPrintInfo = NULL);
	virtual BOOL CanPrint() CONST;
	virtual BOOL IsAlerted() CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseOpenDialog(UINT nCode);
	BOOL OnCloseSettingsDialog(UINT nCode);
	BOOL OnCloseRetrieveDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(COOLWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettings();
	afx_msg void OnLinkages();
	afx_msg void OnParameters();
	afx_msg void OnAcknowledge();
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
	afx_msg void OnUpdateAcknowledge(CCmdUI *pCmdUI);
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


#endif // __OOL_H__
