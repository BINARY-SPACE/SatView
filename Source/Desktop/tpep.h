// TPEP.H : TPEP Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the TPEP display related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/11/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TPEP_H__
#define __TPEP_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CTPEPPrintJobInfo

class CTPEPPrintJobInfo : public CObject
{
	// Construction
public:
	CTPEPPrintJobInfo();

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

	VOID Copy(CONST CTPEPPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CTPEPPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPPrintJobs

class CTPEPPrintJobs : public CPtrArray
{
	// Construction
public:
	CTPEPPrintJobs();
	~CTPEPPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CTPEPPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CTPEPPrintJobInfo *GetAt(INT nIndex) CONST;
	CTPEPPrintJobInfo *operator[](INT nIndex) CONST;

	TIMEKEY Schedule();

	VOID RemoveAll();

	BOOL Copy(CONST CTPEPPrintJobs *pPrintJobs);
	BOOL Compare(CONST CTPEPPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPAlert

// Specify the TPEP alert options
#define TPEPALERT_OPTION_ACTIVATED  (1<<0)
#define TPEPALERT_OPTION_DISABLED  (1<<1)
// Specify the TPEP alert operators
#define TPEPALERT_OPERATOR_BELOW   1
#define TPEPALERT_OPERATOR_EQUAL   2
#define TPEPALERT_OPERATOR_ABOVE   3
#define TPEPALERT_OPERATOR_UNEQUAL   4
#define TPEPALERT_OPERATOR_BELOWEQUAL   5
#define TPEPALERT_OPERATOR_ABOVEEQUAL   6

class CTPEPAlert : public CObject
{
	// Construction
public:
	CTPEPAlert();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbText;
		INT  cbValue;
		INT  cbParameter;
		INT  cbAudition;
		INT  cbNotification;
		UINT  nOptions;
		UINT  nOperator;
		double  fValue[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szText;
	CString  m_szValue;
	CString  m_szParameter;
	CString  m_szAudition;
	CString  m_szNotification;
	double  m_fValue[2];
	UINT  m_nOperator;
	UINT  m_nOptions;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;

	VOID SetParameter(LPCTSTR pszParameter);
	CString GetParameter() CONST;
	VOID SetOperator(UINT nOperator);
	UINT GetOperator() CONST;
	VOID SetValue(LPCTSTR pszValue);
	VOID SetValue(double fValue);
	VOID SetValue(double fLowValue, double fHighValue);
	CString GetValue() CONST;
	BOOL GetValue(double &fValue) CONST;
	BOOL GetValue(double &fLowValue, double &fHighValue) CONST;
	VOID SetAudition(LPCTSTR pszAudition);
	CString GetAudition() CONST;
	VOID SetNotification(LPCTSTR pszNotification);
	CString GetNotification() CONST;
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;
	VOID SetOptions(UINT nOptions);
	UINT GetOptions() CONST;

	VOID Copy(CONST CTPEPAlert *pAlert);
	BOOL Compare(CONST CTPEPAlert *pAlert) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPAlerts

class CTPEPAlerts : public CPtrArray
{
	// Construction
public:
	CTPEPAlerts();
	~CTPEPAlerts();

	// Attributes
public:

	// Operations
public:
	INT Add(CTPEPAlert *pAlert);

	INT Find(LPCTSTR pszName) CONST;

	CTPEPAlert *GetAt(INT nIndex) CONST;
	CTPEPAlert *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTPEPAlerts *pAlerts);
	BOOL Compare(CONST CTPEPAlerts *pAlerts) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsLayoutPage dialog

#define IDC_TPEPSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC   1003
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME   1004
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW   1005
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE   1006
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER   1007
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_REMOVE   1008
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_SHOWDATA   1009
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS   1010
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS   1011
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1012
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1013
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_MESSAGES   1014
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1015
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1016
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES   1017
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1018
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE   1019
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1020
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE   1021
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1022
#define IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1023

class CTPEPSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTPEPSettingsLayoutPage)

	// Construction
public:
	CTPEPSettingsLayoutPage();

	// Attributes
private:
	CUIntArray  m_nColumns[2];
	LOGFONT  m_fntMessages[2];
	LOGFONT  m_fntTitle[2];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;
	CStringArray  m_szColumns;
	UINT  m_nColumnType;
	INT  m_nColumnIndex;

	// Dialog Data
	//{{AFX_DATA(CTPEPSettingsLayoutPage)
	enum { IDD = IDD_TPEP_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetMessagesFont(LPLOGFONT pMessagesFont) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CTPEPSettingsDialog *GetParentDialog() CONST;
	class CTPEPWnd *GetParentDisplay() CONST;

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
	//{{AFX_VIRTUAL(CTPEPSettingsLayoutPage)
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
	//{{AFX_MSG(CTPEPSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnInsertColumnBefore();
	afx_msg void OnInsertColumnAfter();
	afx_msg void OnRemoveColumn();
	afx_msg void OnToolTips();
	afx_msg void OnTitleFont();
	afx_msg void OnMessagesFont();
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
// CTPEPSettingsFilteringPage dialog

#define IDC_TPEPSETTINGS_FILTERINGPAGE_DETAILS   1001
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATIC   1002
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL   1003
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME   1004
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STATIC   1005
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME   1006
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY   1007
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME   1008
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STATIC   1009
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME   1010
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL   1011
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL_STATIC   1012
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL   1013
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START   1014
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME   1015
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP   1016
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME   1017
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES   1018
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_STATIC   1019
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_NUMBER   1020
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS   1021
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER   1022
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS   1023
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL   1024
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL   1025
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL   1026
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL   1027
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL   1028
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID   1029
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID   1030
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY   1031
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD   1032
#define IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD   1033
#define IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS   1034
#define IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_MESSAGES_STATIC   1035
#define IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_MESSAGES   1036
#define IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS_STATIC   1037
#define IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS   1038
#define IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_COLOR_STATIC 1039
#define IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_COLOR   1040

// Specify the TPEP display settings filtering page related limits
#define TPEPSETTINGSFILTERINGPAGE_DEFAULTDAILYSTARTTIME   HOURS(8)
#define TPEPSETTINGSFILTERINGPAGE_DEFAULTDAILYSTOPTIME   HOURS(17)
#define TPEPSETTINGSFILTERINGPAGE_MINIMUMINTERVAL   1
#define TPEPSETTINGSFILTERINGPAGE_MAXIMUMINTERVAL   MINUTESPERDAY
#define TPEPSETTINGSFILTERINGPAGE_DEFAULTINTERVAL   5
#define TPEPSETTINGSFILTERINGPAGE_MINIMUMMESSAGES   1
#define TPEPSETTINGSFILTERINGPAGE_MAXIMUMMESSAGES   1000
#define TPEPSETTINGSFILTERINGPAGE_DEFAULTMESSAGES   100
#define TPEPSETTINGSFILTERINGPAGE_MINIMUMDIGITS   1
#define TPEPSETTINGSFILTERINGPAGE_MAXIMUMDIGITS   16
#define TPEPSETTINGSFILTERINGPAGE_DEFAULTDIGITS   8
#define TPEPSETTINGSFILTERINGPAGE_DEFAULTRANGE   MINUTESPERHOUR

class CTPEPSettingsFilteringPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTPEPSettingsFilteringPage)

	// Construction
public:
	CTPEPSettingsFilteringPage();

	// Attributes
private:
	UINT  m_nType;
	UINT  m_nMode[2];
	UINT  m_nLimit[2];
	UINT  m_nDigits[2];
	UINT  m_nStatus[2];
	COLORREF  m_nColor[2];
	CTimeKey  m_tRange[2][2][2];
	CTimeSpan  m_tDailyRange[2][2];
	CTimeSpan  m_tPeriodical[2];
	CUIntArray  m_nOOLColors[2];

	// Dialog Data
	//{{AFX_DATA(CTPEPSettingsFilteringPage)
	enum { IDD = IDD_TPEP_SETTINGS_FILTERINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetMode(UINT &nMode) CONST;
	BOOL GetLimit(UINT &nLimit) CONST;
	BOOL GetDigits(UINT &nDigits) CONST;
	BOOL GetStatus(UINT &nStatus) CONST;
	BOOL GetRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL GetDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL GetPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	BOOL GetColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST;

	class CTPEPSettingsDialog *GetParentDialog() CONST;
	class CTPEPWnd *GetParentDisplay() CONST;

private:
	BOOL EnumFilterStatus();

	UINT GetFilterStatus() CONST;

	VOID ShowFilterInfo();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTPEPSettingsFilteringPage)
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
	//{{AFX_MSG(CTPEPSettingsFilteringPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnFilterByTime();
	afx_msg void OnFilterByDailyTime();
	afx_msg void OnFilterByPeriodicalTime();
	afx_msg void OnFilterByPeriodicalStartTime();
	afx_msg void OnFilterByPeriodicalStopTime();
	afx_msg void OnFilterByLimit();
	afx_msg void OnFilterByDigits();
	afx_msg void OnFilterByStatus();
	afx_msg void OnFilterByStatusValue();
	afx_msg void OnFilterByQuality();
	afx_msg void OnFilterByQualityValue();
	afx_msg void OnSpinchangeFilterStartTime();
	afx_msg void OnSpinchangeFilterStopTime();
	afx_msg void OnSpinchangeFilterDailyStartTime();
	afx_msg void OnSpinchangeFilterDailyStopTime();
	afx_msg void OnSpinchangeFilterPeriodicalInterval();
	afx_msg void OnSpinchangeFilterPeriodicalStartTime();
	afx_msg void OnSpinchangeFilterPeriodicalStopTime();
	afx_msg void OnSpinchangeFilterLimit();
	afx_msg void OnSpinchangeFilterDigits();
	afx_msg void OnSelchangeFilterColorMessages();
	afx_msg void OnSelchangeFilterColorLocation();
	afx_msg void OnSelchangeFilterColor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsPrintingComments window

class CTPEPSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CTPEPSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsPrintingPage dialog

#define IDC_TPEPSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_TPEPSETTINGS_PRINTINGPAGE_NAME_STATIC   1002
#define IDC_TPEPSETTINGS_PRINTINGPAGE_NAME   1003
#define IDC_TPEPSETTINGS_PRINTINGPAGE_ADDNAME   1004
#define IDC_TPEPSETTINGS_PRINTINGPAGE_REMOVENAME   1005
#define IDC_TPEPSETTINGS_PRINTINGPAGE_REMOVEALLNAMES   1006
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES   1007
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC   1008
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE   1009
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS   1010
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL   1011
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE   1012
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE   1013
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC   1014
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT   1015
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL   1016
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND   1017
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS   1018
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC   1019
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT   1020
#define IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS   1021

// Specify the TPEP display settings printing page related limits
#define TPEPSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMMESSAGES   1
#define TPEPSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMMESSAGES   1000
#define TPEPSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTMESSAGES   25

class CTPEPSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTPEPSettingsPrintingPage)

	// Construction
public:
	CTPEPSettingsPrintingPage();

	// Attributes
private:
	CTPEPPrintJobs  m_pJobs[2];
private:
	CTPEPSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CTPEPSettingsPrintingPage)
	enum { IDD = IDD_TPEP_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CTPEPPrintJobs &pJobs) CONST;

	class CTPEPSettingsDialog *GetParentDialog() CONST;
	class CTPEPWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CTPEPPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTPEPSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CTPEPPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTPEPSettingsPrintingPage)
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
	afx_msg void OnChangePrintSide();
	afx_msg void OnSpinchangePrintSideCount();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsPrintJobsPage dialog

#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_DETAILS   1001
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC   1002
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS   1003
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB   1004
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC   1005
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS   1006
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_REMOVEJOB   1007
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR   1008
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME   1009
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME   1010
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME   1011
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC   1012
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME   1013
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT   1014
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT   1015
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC   1016
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION   1017
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC   1018
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE   1019
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME  1020
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC   1021
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME   1022
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC   1023
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES   1024
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC   1025
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES   1026
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME   1027
#define IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME   1028

// Specify the TPEP display settings print jobs page related repetition types
#define TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY   1
#define TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY   2
// Specify the TPEP display settings print jobs page related limits
#define TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL   1
#define TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL   MINUTESPERHOUR
#define TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES   1
#define TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES   10000
#define TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES   10

class CTPEPSettingsPrintJobsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTPEPSettingsPrintJobsPage)

	// Construction
public:
	CTPEPSettingsPrintJobsPage();

	// Attributes
private:
	CTPEPPrintJobs  m_pJobs[2];

	// Dialog Data
	//{{AFX_DATA(CTPEPSettingsPrintJobsPage)
	enum { IDD = IDD_TPEP_SETTINGS_PRINTJOBSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CTPEPPrintJobs &pJobs) CONST;

	class CTPEPSettingsDialog *GetParentDialog() CONST;
	class CTPEPWnd *GetParentDisplay() CONST;

private:
	BOOL EnumJobs();
	BOOL EnumEvents();

	VOID ShowJobInfo();
	BOOL CheckJobInfo() CONST;
	CTPEPPrintJobInfo *FindJobInfo(BOOL bActive = FALSE) CONST;

	VOID SetJobRepetitionInfo();
	UINT GetJobRepetitionType() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTPEPSettingsPrintJobsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CTPEPPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTPEPSettingsPrintJobsPage)
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
// CTPEPSettingsTabCtrl window

class CTPEPSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTPEPSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsDialog

class CTPEPSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CTPEPSettingsDialog)

	// Construction
public:
	CTPEPSettingsDialog();

	// Attributes
private:
	CTPEPSettingsTabCtrl  m_wndTabCtrl;
	CTPEPSettingsLayoutPage  m_pageLayout;
	CTPEPSettingsFilteringPage  m_pageFiltering;
	CTPEPSettingsPrintingPage  m_pagePrinting;
	CTPEPSettingsPrintJobsPage  m_pagePrintJobs;

	// Operations
public:
	BOOL GetLayoutColumns(CUIntArray &nColumns) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutMessagesFont(LPLOGFONT pMessagesFont) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL GetFilterLimit(UINT &nLimit) CONST;
	BOOL GetFilterDigits(UINT &nDigits) CONST;
	BOOL GetFilterStatus(UINT &nStatus) CONST;
	BOOL GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	BOOL GetFilterColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetPrintJobs(CTPEPPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTPEPOpenDialog *GetParentDialog() CONST;
	class CTPEPWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPSettingsDialog)
public:
	virtual BOOL OnDataExchange(HWND hPage, CONST CTPEPPrintJobs &pJobs);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPSettingsDialog)
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
// CTPEPConnectionDialog dialog

#define IDC_TPEP_CONNECTION_DETAILS   1001
#define IDC_TPEP_CONNECTION_SERVER_STATIC   1002
#define IDC_TPEP_CONNECTION_SERVER   1003
#define IDC_TPEP_CONNECTION_CLIENT_STATIC   1004
#define IDC_TPEP_CONNECTION_CLIENT   1005
#define IDC_TPEP_CONNECTION_PROPERTIES   1006
#define IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_STATIC   1007
#define IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_PACKETS   1008
#define IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_PARAMETERS   1009
#define IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS   1010
#define IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_STATIC   1011
#define IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_HOT   1012
#define IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_COLD   1013
#define IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_STATIC   1014
#define IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_RAW   1015
#define IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE   1016
#define IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE_NUMBER   1017
#define IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_STATIC   1018
#define IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_UPDATE   1019
#define IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_CHANGE   1020
#define IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STATIC   1021
#define IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_REALTIME   1022
#define IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_RANDOM   1023
#define IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_HISTORICAL   1024
#define IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME_STATIC   1025
#define IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME   1026
#define IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME_STATIC   1027
#define IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME   1028
#define IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_SPEED_STATIC   1029
#define IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_SPEED   1030
#define IDC_TPEP_CONNECTION_HELP   1031

class CTPEPConnectionDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTPEPConnectionDialog)

	// Construction
public:
	CTPEPConnectionDialog();   // standard constructor

	// Attributes
private:
	BOOL  m_bConnection;
	CString  m_szComputer;
	CTPEPConnection  m_cConnection;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTPEPConnectionDialog)
	enum { IDD = IDD_TPEP_CONNECTION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, LPCTSTR pszComputer, CONST CTPEPConnection *pConnection, BOOL bConnection);

	class CTPEPWnd *GetParent() CONST;

private:
	BOOL ShowConnectionInfo();

	INT CalcColumnExtent(LPCTSTR pszColumn);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPConnectionDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTPEPConnectionDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersCalibrationPage dialog

#define IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTPEPParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTPEPParametersCalibrationPage)

	// Construction
public:
	CTPEPParametersCalibrationPage();

	// Attributes
private:
	ULONGLONG  m_nCalTableType;
	CUIntArray  m_nCalTableRefs;
	CUIntArray  m_nCalValidityRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTPEPParametersCalibrationPage)
	enum { IDD = IDD_TPEP_PARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(LPCTSTR pszParameter);

	VOID ShowCalibrationInfo();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTPEPParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTPEPParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersFolderTabCtrl window

class CTPEPParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTPEPParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTPEPParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersFolder

class CTPEPParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTPEPParametersFolder)

	// Construction
public:
	CTPEPParametersFolder();

	// Attributes
private:
	CTPEPParametersFolderTabCtrl  m_wndTabCtrl;
	CTPEPParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(LPCTSTR pszParameter = NULL);

	class CTPEPParametersDialog *GetParentDialog() CONST;
	class CTPEPWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersDialog dialog

#define IDC_TPEP_PARAMETERS_DETAILS   1001
#define IDC_TPEP_PARAMETERS_ITEM_STATIC   1002
#define IDC_TPEP_PARAMETERS_ITEM   1003
#define IDC_TPEP_PARAMETERS_FOLDER   1004
#define IDC_TPEP_PARAMETERS_HELP   1005

class CTPEPParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTPEPParametersDialog)

	// Construction
public:
	CTPEPParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szParameter;
private:
	CTPEPParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTPEPParametersDialog)
	enum { IDD = IDD_TPEP_PARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter);

	class CTPEPWnd *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTPEPParametersDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPAlertsDialog dialog

#define IDC_TPEP_ALERTS_DETAILS   1001
#define IDC_TPEP_ALERTS_NAME_STATIC   1002
#define IDC_TPEP_ALERTS_NAME   1003
#define IDC_TPEP_ALERTS_LIST_STATIC   1004
#define IDC_TPEP_ALERTS_LIST   1005
#define IDC_TPEP_ALERTS_ADD   1006
#define IDC_TPEP_ALERTS_REMOVE   1007
#define IDC_TPEP_ALERTS_REMOVEALL   1008
#define IDC_TPEP_ALERTS_PROPERTIES   1009
#define IDC_TPEP_ALERTS_PROPERTIES_WATCH_STATIC   1010
#define IDC_TPEP_ALERTS_PROPERTIES_WATCH_PARAMETER   1011
#define IDC_TPEP_ALERTS_PROPERTIES_WATCH_OPERATOR   1012
#define IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE   1013
#define IDC_TPEP_ALERTS_PROPERTIES_AUDITION_STATIC   1014
#define IDC_TPEP_ALERTS_PROPERTIES_AUDITION   1015
#define IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION_STATIC   1016
#define IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION   1017
#define IDC_TPEP_ALERTS_PROPERTIES_TEXT_STATIC   1018
#define IDC_TPEP_ALERTS_PROPERTIES_TEXT   1019
#define IDC_TPEP_ALERTS_PROPERTIES_DISABLED   1020
#define IDC_TPEP_ALERTS_HELP   1021

class CTPEPAlertsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTPEPAlertsDialog)

	// Construction
public:
	CTPEPAlertsDialog();   // standard constructor

	// Attributes
private:
	CTPEPAlerts  m_pAlerts[2];
	CTPEPConnection  m_cConnection;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTPEPAlertsDialog)
	enum { IDD = IDD_TPEP_ALERTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTPEPAlerts &pAlerts, CONST CTPEPConnection *pConnection);

	class CTPEPWnd *GetParent() CONST;

private:
	BOOL EnumAlerts();
	BOOL EnumParameters();
	BOOL EnumOperators();
	BOOL EnumValues();
	BOOL EnumAuditions();
	BOOL EnumNotifications();

	VOID ShowAlertInfo();
	VOID ShowAlertInfo(INT nIndex);
	BOOL CheckAlertInfo() CONST;
	CTPEPAlert *FindAlertInfo() CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPAlertsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTPEPAlertsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnDisabled();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeText();
	afx_msg void OnEditchangeValue();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeOperator();
	afx_msg void OnSelchangeValue();
	afx_msg void OnSelchangeAudition();
	afx_msg void OnSelchangeNotification();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPFindDialog dialog

#define IDC_TPEP_FIND_KEY_STATIC   1001
#define IDC_TPEP_FIND_KEY   1002
#define IDC_TPEP_FIND_VALUE_STATIC   1003
#define IDC_TPEP_FIND_VALUE   1004
#define IDC_TPEP_FIND_RESULTS_STATIC   1005
#define IDC_TPEP_FIND_RESULTS   1006
#define IDC_TPEP_FIND_SEARCH   1007
#define IDC_TPEP_FIND_OPEN   1008
#define IDC_TPEP_FIND_HELP   1009

class CTPEPFindDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTPEPFindDialog)

	// Construction
public:
	CTPEPFindDialog();   // standard constructor

private:
	CStringArray  m_szServers;
	CStringArray  m_szClients;
	CStringArray  m_szConnections;
	CTPEPConnections  m_pConnections;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTPEPFindDialog)
	enum { IDD = IDD_TPEP_FIND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CString &szServer, CString &szClient, CTPEPConnection *pConnection);

	class CTPEPWnd *GetParent() CONST;

private:
	BOOL EnumSearchKeys();
	BOOL EnumSearchValues();

	VOID DoFindByPacket(LPCTSTR pszPacket);
	VOID DoFindByPackets(CONST CStringArray &szPackets);
	VOID DoFindByParameter(LPCTSTR pszParameter);
	VOID DoFindByParameters(CONST CStringArray &szParameters);

	VOID ShowConnection(LPCTSTR pszServer, LPCTSTR pszClient, CONST CTPEPConnection *pConnection);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTPEPFindDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSearch();
	afx_msg void OnOpen();
	afx_msg void OnSelchangeKey();
	afx_msg void OnSelchangeValue();
	afx_msg void OnEditchangeValue();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPOpenDialog dialog

#define IDC_TPEP_OPEN_DETAILS   1001
#define IDC_TPEP_OPEN_CONNECTION_STATIC   1002
#define IDC_TPEP_OPEN_CONNECTION   1003
#define IDC_TPEP_OPEN_SETTINGS   1004
#define IDC_TPEP_OPEN_FIND   1005
#define IDC_TPEP_OPEN_TYPE   1006
#define IDC_TPEP_OPEN_TYPE_NORMAL   1007
#define IDC_TPEP_OPEN_TYPE_SIMPLE   1008
#define IDC_TPEP_OPEN_HELP   1009

class CTPEPOpenDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTPEPOpenDialog)

	// Construction
public:
	CTPEPOpenDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nFilterMode;
	UINT  m_nFilterLimit;
	UINT  m_nFilterDigits;
	UINT  m_nFilterStatus;
	BOOL  m_bLayoutToolTips;
	LOGFONT  m_fntLayoutTitle;
	LOGFONT  m_fntLayoutMessages;
	COLORREF  m_nFilterColor;
	CTimeKey  m_tFilterRange[2][2];
	CTimeSpan  m_tFilterDailyRange[2];
	CTimeSpan  m_tFilterPeriodical;
	CUIntArray  m_nFilterOOLColors;
	CUIntArray  m_nLayoutColumns;
	CStringArray  m_szServers;
	CStringArray  m_szClients;
	CTPEPPrintJobs  m_pPrintJobs;
	CTPEPConnections  m_pConnections[2];
private:
	CStringArray  m_szColumns;
private:
	CTPEPSettingsDialog  m_dlgSettings;
	CTPEPFindDialog  m_dlgFindDisplay;

	// Dialog Data
	//{{AFX_DATA(CTPEPOpenDialog)
	enum { IDD = IDD_TPEP_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	CString GetTitle() CONST;
	UINT GetType() CONST;
	BOOL GetConnection(CString &szComputer, CTPEPConnection *pConnection, BOOL &bConnection) CONST;

	BOOL GetLayoutColumns(CUIntArray &nColumns) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutMessagesFont(LPLOGFONT pMessagesFont) CONST;
	BOOL GetLayoutInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL GetFilterLimit(UINT &nLimit) CONST;
	BOOL GetFilterDigits(UINT &nDigits) CONST;
	BOOL GetFilterStatus(UINT &nStatus) CONST;
	BOOL GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	BOOL GetFilterColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetPrintJobs(CTPEPPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTPEPWnd *GetParent() CONST;

private:
	BOOL EnumConnections();

	INT FindConnection(LPCTSTR pszServer, LPCTSTR pszClient, CONST CTPEPConnection *pConnection) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPOpenDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseSettingsDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSettings();
	afx_msg void OnFind();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPPrintThread thread

class CTPEPPrintThread : public CThread
{
	DECLARE_DYNCREATE(CTPEPPrintThread)

	// Construction
public:

	// Attributes
private:
	CTPEPPrintJobs  m_pPrintJobs;
private:
	CEvent  m_cEvent;

	// Operations
public:
	BOOL Start(class CTPEPWnd *pParentWnd);
	BOOL Stop();

	BOOL SetPrintJobs(CONST CTPEPPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CTPEPPrintJobs &pPrintJobs) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPPrintThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTPEPPrintThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPToolBar window

class CTPEPToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CTPEPToolBar)

	// Construction
public:
	CTPEPToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPStatusBar window

class CTPEPStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CTPEPStatusBar)

	// Construction
public:
	CTPEPStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CTPEPWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPToolTip window

class CTPEPToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CTPEPToolTip)

	// Construction
public:
	CTPEPToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPDataContainer window

class CTPEPDataContainer : public CTextView
{
	DECLARE_DYNCREATE(CTPEPDataContainer)

	// Construction
public:
	CTPEPDataContainer();

	// Attributes
private:
	UINT  m_nType;
private:
	CUIntArray  m_nLayoutColumns;
private:
	UINT  m_nFilterMode;
	UINT  m_nFilterLimit;
	UINT  m_nFilterDigits;
	UINT  m_nFilterStatus;
	COLORREF  m_nFilterColor;
	CTimeKey  m_tFilterRange[2][2];
	CTimeSpan  m_tFilterDailyRange[2];
	CTimeSpan  m_tFilterPeriodical;
	CUIntArray  m_nFilterOOLColors;
private:
	INT  m_nParameterCount;
	CUIntArray  m_nParameterStatus;
	CStringArray  m_szParameterIDs;
	CStringArray  m_szParameterValues[2];
	CStringArray  m_szParameterPackets[2];
	CStringArray  m_szParameterTimeTags[2][2];
private:
	CString  m_szConnectionComputer;
	CTPEPConnection  m_cConnection;
	BOOL  m_bConnection;
private:
	CTPEPAlerts  m_pAlerts;
private:
	CTPEPToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bToolTipMode;

	// Operations
public:
	BOOL SetLayout(UINT nType);
	BOOL GetLayout(UINT &nType) CONST;
	BOOL SetLayoutColumns(CONST CUIntArray &nColumns);
	BOOL SetLayoutColumns(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayoutColumns(CUIntArray &nColumns) CONST;
	BOOL GetLayoutColumns(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetMessagesFont(CONST LOGFONT *plfFont);
	BOOL GetMessagesFont(LOGFONT *plfFont, BOOL bValues = FALSE) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterLimit(UINT nLimit);
	BOOL GetFilterLimit(UINT &nLimit) CONST;
	BOOL SetFilterStatus(UINT nStatus);
	BOOL GetFilterStatus(UINT &nStatus) CONST;
	BOOL SetFilterRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetFilterDailyRange(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL SetFilterPeriodicalRange(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime);
	BOOL GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	BOOL SetFilterDigits(UINT nDigits);
	BOOL GetFilterDigits(UINT &nDigits) CONST;
	BOOL SetFilterColors();
	BOOL SetFilterColors(COLORREF nColor, CONST CUIntArray &nOOLColors);
	BOOL GetFilterColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST;

	BOOL SetAlerts(CONST CTPEPAlerts &pAlerts);
	BOOL GetAlerts(CTPEPAlerts &pAlerts) CONST;

	BOOL AddMessage(LPCTSTR pszMessage);
	BOOL ClearAllMessages();
	INT GetMessageCount() CONST;

	BOOL SetConnectionProperties(CONST CTPEPConnection *pConnection);
	BOOL SetConnectionProperties(LPCTSTR pszComputer, CONST CTPEPConnection *pConnection, BOOL bConnection = TRUE);
	BOOL GetConnectionProperties(CTPEPConnection *pConnection) CONST;
	BOOL GetConnectionProperties(CString &szComputer, CTPEPConnection *pConnection, BOOL &bConnection) CONST;

	BOOL GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CStringArray &szParameterValues, CUIntArray &nParameterStatus, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pMessagesFont, LOGFONT *pValuesFont) CONST;

	class CTPEPView *GetParent() CONST;
	class CTPEPWnd *GetParentDisplay() CONST;

private:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CStringArray &szColumns, CUIntArray &nWidths);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);

	BOOL FilterMessage(LPCTSTR pszMessage);
	BOOL ParseMessage(LPCTSTR pszMessage, CString &szMessage, CTextViewAttribute *pAttribute);
	BOOL ParseMessage(LPCTSTR pszMessage, CStringArray &szPackets, CStringArray &szParameters, CStringArray &szErrros);
	BOOL ParseMessage(CONST POINT &point, CString &szParameter, CString &szError);

	BOOL ReadMessageText(LPCTSTR pszMessage, CString &szText, INT &nPos) CONST;
	BOOL ReadMessageNumber(LPCTSTR pszMessage, double &fNumber, INT &nPos) CONST;

	BOOL ConvertMessageTextToTimeTag(LPCTSTR pszTimeTag, CTimeTag &tTimeTag) CONST;
	CString ConvertMessagePositionToParameter(CONST POINT &point) CONST;
	INT ConvertMessagePositionToIndex(CONST POINT &point) CONST;

	UINT PointToRow(CONST POINT &point) CONST;
	UINT PointToColumn(CONST POINT &point) CONST;
	POINT PointToPoint(CONST POINT &point) CONST;

	CString ConstructToolTipTitle(LPCTSTR pszParameter, LPCTSTR pszError) CONST;
	CString ConstructToolTipTitle(CONST CStringArray &szPackets, CONST CStringArray &szParameters) CONST;
	CString ConstructToolTipText(CONST POINT &point, LPCTSTR pszParameter, LPCTSTR pszError) CONST;
	CString ConstructToolTipText(CONST CStringArray &szPackets, CONST CStringArray &szParameters, CONST CStringArray &szErrors) CONST;

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

	VOID DoAlert(CTPEPAlert *pAlert);

	BOOL AdjustColumns();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPDataContainer)
public:
	virtual VOID RecalcLayout();
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
	//{{AFX_MSG(CTPEPDataContainer)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPDataHeaderCtrl window

class CTPEPDataHeaderCtrl : public CMFCHeaderCtrl
{
	DECLARE_DYNCREATE(CTPEPDataHeaderCtrl)

	// Construction
public:
	CTPEPDataHeaderCtrl();

	// Attributes
private:
	CString  m_szTitle;
private:
	WORD  m_wTextIndent[2];
	WORD  m_wTextSpacing[2];
private:
	CFont  m_cFont;
private:
	class CTPEPView  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CTPEPView *pParentWnd, DWORD dwStyle, UINT nID);

	BOOL SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;

	BOOL SetFont(CFont *pFont);
	BOOL SetFont(CONST LOGFONT *plfFont);
	BOOL GetFont(CFont *pFont) CONST;
	BOOL GetFont(LOGFONT *plfFont) CONST;

	class CTPEPView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPDataHeaderCtrl)
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
	//{{AFX_MSG(CTPEPDataHeaderCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPView window

class CTPEPView : public CWnd
{
	DECLARE_DYNCREATE(CTPEPView)

	// Construction
public:
	CTPEPView();
	~CTPEPView();

	// Attributes
private:
	CSize  m_sizeTrackLayout;
private:
	CTPEPDataHeaderCtrl  *m_pwndHeaderCtrl;
	CTPEPDataContainer  *m_pwndView;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetTitle(LPCTSTR pszTitle);
	BOOL GetTitle(CString &szTitle) CONST;

	BOOL SetLayout(UINT nType);
	BOOL GetLayout(UINT &nType) CONST;
	BOOL SetLayoutColumns(CONST CUIntArray &nColumns);
	BOOL SetLayoutColumns(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayoutColumns(CUIntArray &nColumns) CONST;
	BOOL GetLayoutColumns(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetMessagesFont(CONST LOGFONT *plfFont);
	BOOL GetMessagesFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterLimit(UINT nLimit);
	BOOL GetFilterLimit(UINT &nLimit) CONST;
	BOOL SetFilterStatus(UINT nStatus);
	BOOL GetFilterStatus(UINT &nStatus) CONST;
	BOOL SetFilterRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetFilterDailyRange(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL SetFilterPeriodicalRange(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime);
	BOOL GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	BOOL SetFilterDigits(UINT nDigits);
	BOOL GetFilterDigits(UINT &nDigits) CONST;
	BOOL SetFilterColors();
	BOOL SetFilterColors(COLORREF nColor, CONST CUIntArray &nOOLColors);
	BOOL GetFilterColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST;

	BOOL SetAlerts(CONST CTPEPAlerts &pAlerts);
	BOOL GetAlerts(CTPEPAlerts &pAlerts) CONST;

	BOOL AddMessage(LPCTSTR pszMessage);
	BOOL ClearAllMessages();
	INT GetMessageCount() CONST;

	BOOL SetConnectionProperties(CONST CTPEPConnection *pConnection);
	BOOL SetConnectionProperties(LPCTSTR pszComputer, CONST CTPEPConnection *pConnection, BOOL bConnection = TRUE);
	BOOL GetConnectionProperties(CTPEPConnection *pConnection) CONST;
	BOOL GetConnectionProperties(CString &szComputer, CTPEPConnection *pConnection, BOOL &bConnection) CONST;

	BOOL GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CStringArray &szParameterValues, CUIntArray &nParameterStatus, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pMessagesFont, LOGFONT *pValuesFont) CONST;

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	class CTPEPWnd *GetParent() CONST;

	BOOL Lock();
	BOOL Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPView)
public:
	virtual VOID RecalcLayout();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPWnd frame

// Specify the TPEP display types
#define TPEP_TYPE_NORMAL   1
#define TPEP_TYPE_SIMPLE   2
// Specify the TPEP display title items
#define TPEP_TITLEITEM_ID   (1<<0)
#define TPEP_TITLEITEM_DESCRIPTION   (1<<1)
#define TPEP_TITLEITEM_VALUE   (1<<2)
#define TPEP_TITLEITEM_UNIT   (1<<3)
#define TPEP_TITLEITEM_CHANGETMUNIT   (1<<4)
#define TPEP_TITLEITEM_CHANGETIME   (1<<5)
#define TPEP_TITLEITEM_UPDATETMUNIT   (1<<6)
#define TPEP_TITLEITEM_UPDATETIME   (1<<7)
#define TPEP_TITLEITEM_MESSAGES   (1<<8)
#ifndef RC_INVOKED
#define TPEP_TITLEITEMS_DEFAULT   (TPEP_TITLEITEM_ID | TPEP_TITLEITEM_DESCRIPTION | TPEP_TITLEITEM_VALUE | TPEP_TITLEITEM_UNIT)
#define TPEP_TITLEITEMS_ALL   (TPEP_TITLEITEMS_DEFAULT | TPEP_TITLEITEM_CHANGETMUNIT | TPEP_TITLEITEM_CHANGETIME | TPEP_TITLEITEM_UPDATETMUNIT | TPEP_TITLEITEM_UPDATETIME)
#endif
// Specify the TPEP display filter modes
#define TPEP_FILTER_RANGE   (1<<0)
#define TPEP_FILTER_DAILYRANGE   (1<<1)
#define TPEP_FILTER_PERIODICALRANGE   (1<<2)
#define TPEP_FILTER_LIMIT   (1<<3)
#define TPEP_FILTER_STATUS   (1<<4)
// Specify the TPEP display default filter settings
#define TPEP_FILTER_DEFAULTMODE   0
#define TPEP_FILTER_DEFAULTNOLIMIT   1000
#define TPEP_FILTER_DEFAULTLIMIT   100
// Specify the TPEP display print modes
#define TPEP_PRINT_ALL   (1<<0)
#define TPEP_PRINT_FIRSTSIDE   (1<<1)
#define TPEP_PRINT_LASTSIDE   (1<<2)
#define TPEP_PRINT_UNDERLINEOOL   (1<<3)
#define TPEP_PRINT_COLORLEGEND   (1<<4)
#define TPEP_PRINT_CLEARCOMMENTS   (1<<5)
#define TPEP_PRINT_ATTIME   (1<<6)
#define TPEP_PRINT_ATDAILYTIME   (1<<7)
#define TPEP_PRINT_ATEVENT   (1<<8)
#define TPEP_PRINT_REPEATBYINTERVAL   (1<<9)
#define TPEP_PRINT_REPEATSTOPBYCOUNT   (1<<10)
#define TPEP_PRINT_REPEATSTOPBYTIME   (1<<11)
#define TPEP_PRINT_DAILYREPEATSTOPBYCOUNT   (1<<12)
#define TPEP_PRINT_DAILYREPEATSTOPBYTIME   (1<<13)
#define TPEP_PRINT_ACTIVE   (1<<14)
// Specify the TPEP display print fonts
#define TPEP_PRINTFONT_TITLE   0
#define TPEP_PRINTFONT_SUBTITLE   1
#define TPEP_PRINTFONT_OPERATINGDETAILS   2
#define TPEP_PRINTFONT_OPERATINGMODE   3
#define TPEP_PRINTFONT_MESSAGESTITLE   4
#define TPEP_PRINTFONT_MESSAGESTEXT   5
#define TPEP_PRINTFONT_MESSAGESVALUES   6
#define TPEP_PRINTFONT_FOOTER   7
#define TPEP_PRINTFONT_NOTICE   8
#define TPEP_PRINTFONT_LOGO   9
#define TPEP_PRINTFONTS   10
// Specify the TPEP display OOL colors
#define TPEP_OOLCOLOR_NOLIMIT   0
#define TPEP_OOLCOLOR_SOFTLIMIT   1
#define TPEP_OOLCOLOR_HARDLIMIT   2
#define TPEP_OOLCOLOR_DELTALIMIT   3
#define TPEP_OOLCOLOR_CONSISTENCYLIMIT   4
// Specify the TPEP display statusbar pane identifiers
#define ID_TPEP_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_TPEP_STATUSBAR_COMPUTERPANE   ID_STATUSBAR_PANE1
#define ID_TPEP_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE2
#define ID_TPEP_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE3

class CTPEPWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CTPEPWnd)

	// Construction
public:
	CTPEPWnd();

	// Attributes
private:
	CTPEPToolBar  m_wndToolBar;
	CTPEPStatusBar  m_wndStatusBar;
	CTPEPView  m_wndView;
private:
	CTPEPOpenDialog  m_dlgOpen;
	CTPEPSettingsDialog  m_dlgSettings;
	CTPEPConnectionDialog  m_dlgConnection;
	CTPEPParametersDialog  m_dlgParameters;
	CTPEPAlertsDialog  m_dlgAlerts;
private:
	CTPEPPrintThread  m_cPrintThread;
private:
	CString  m_szTMUnit;
	CTimeTag  m_tTMUnit;
	UINT  m_nTMUnit;
	BOOL  m_bTMUnit;
	BOOL  m_bUpdate;
private:
	LONG  m_bRetrieveFlag;
	UINT  m_nRetrieveMode;

	// Operations
public:
	BOOL SetLayout(UINT nType);
	BOOL GetLayout(UINT &nType) CONST;
	BOOL SetLayoutColumns(CONST CUIntArray &nColumns);
	BOOL SetLayoutColumns(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayoutColumns(CUIntArray &nColumns) CONST;
	BOOL GetLayoutColumns(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetMessagesFont(CONST LOGFONT *plfFont);
	BOOL GetMessagesFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL AddMessage(LPCTSTR pszMessage);
	BOOL ClearAllMessages();
	INT GetMessageCount() CONST;

	BOOL SetFilterMode(UINT nMode = TPEP_FILTER_DEFAULTMODE);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterLimit(UINT nLimit = 0);
	BOOL GetFilterLimit(UINT &nLimit) CONST;
	BOOL SetFilterStatus(UINT nStatus = 0);
	BOOL GetFilterStatus(UINT &nStatus) CONST;
	BOOL SetFilterRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetFilterDailyRange(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL SetFilterPeriodicalRange(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime);
	BOOL GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	BOOL SetFilterDigits(UINT nDigits = 0);
	BOOL GetFilterDigits(UINT &nDigits) CONST;
	BOOL SetFilterColors();
	BOOL SetFilterColors(COLORREF nColor, CONST CUIntArray &nOOLColors);
	BOOL GetFilterColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST;

	BOOL SetAlerts(CONST CTPEPAlerts &pAlerts);
	BOOL GetAlerts(CTPEPAlerts &pAlerts) CONST;

	BOOL ProcessRealtimeData();

	BOOL StartRetrieveData();
	BOOL IsRetrievingData() CONST;
	BOOL StopRetrieveData();
	BOOL SetRetrieveMode(UINT nMode = 0);
	BOOL GetRetrieveMode(UINT &nMode) CONST;
	UINT GetRetrieveMode() CONST;

	BOOL SetConnectionProperties(CONST CTPEPConnection *pConnection);
	BOOL SetConnectionProperties(LPCTSTR pszComputer, CONST CTPEPConnection *pConnection, BOOL bConnection = TRUE);
	BOOL GetConnectionProperties(CTPEPConnection *pConnection) CONST;
	BOOL GetConnectionProperties(CString &szComputer, CTPEPConnection *pConnection, BOOL &bConnection) CONST;

	VOID SetParameterInfo(LPCTSTR pszTag);

	BOOL SetPrintJobs(CONST CTPEPPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CTPEPPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CTPEPPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	CTPEPWnd *Find(INT nType, LPCTSTR pszComputer, CONST CTPEPConnection *pConnection, BOOL bClient) CONST;

	VOID SetUpdateInfo();
	VOID SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, BOOL bQuality);
	BOOL GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, BOOL &bQuality) CONST;

private:
	BOOL CreateToolBar();
	BOOL CreateStatusBar();
	BOOL CreateView();

	CRect RepositionView(BOOL bAdjust = TRUE);

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateComputerPane();
	VOID UpdateModePane();
	VOID UpdateTypePane();

	BOOL ParseData(LPCTSTR pszData, CString &szTag, CTimeTag &tTag, UINT &nTag, BOOL &bQuality) CONST;

	VOID SetHoldFlag(BOOL bEnable = FALSE);
	BOOL GetHoldFlag() CONST;
	BOOL HasHoldFlag() CONST;

	BOOL StartConnection();
	BOOL ProcessConnection();
	BOOL StopConnection();

	BOOL StartSchedulePrintJobs();
	BOOL IsSchedulingPrintJobs() CONST;
	BOOL StopSchedulePrintJobs();

	BOOL SetAlerts(CONST CByteArray &nAlertInfo);
	BOOL GetAlerts(CByteArray &nAlertInfo) CONST;

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CTPEPPrintJobInfo *pJobInfo, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CStringArray &szParameterValues, CUIntArray &nParameterStatus, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pMessagesFont, LOGFONT *pValuesFont) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CTPEPPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CTPEPConnection *pConnection, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTextViewAttributes &pAttributes, CONST CStringArray &szParameterValues, CONST CUIntArray &nParameterStatus, CONST CUIntArray &nOOLColors, CONST LOGFONT *pTitleFont, CONST LOGFONT *pMessagesFont, CONST LOGFONT *pValuesFont);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTPEPPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, CONST CTPEPConnection *pConnection, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CUIntArray &nOOLColors, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CONST CUIntArray &nOOLColors, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocMessagesTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(CONST CTPEPConnection *pConnection) CONST;
	CString GetPrintDocOperatingDetails(CONST CTPEPPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST;
	CString GetPrintDocOperatingMode(CONST CTPEPPrintJobInfo *pJobInfo, CONST CUIntArray &nOOLColors) CONST;
	CString GetPrintDocMessagesTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;
	INT CalcPrintDocText(CDC &cDC, CFont *pFont, LPCTSTR pszColumnsText, INT nWidth, CString &szText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocMessagesFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pMessagesFont, CONST LOGFONT *pValuesFont, CFont &cTitleFont, CFont &cMessagesFont, CFont &cValuesFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pMessagesFont, CFont *pValuesFont, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, LPCTSTR pszColumn, CStringArray &szContents, CFont *pMessagesFont, CFont *pValuesFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Check() CONST;
	virtual VOID Update();
	virtual BOOL Update(LPVOID pData);
	virtual BOOL Update(LPCTSTR pszData);
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
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseOpenDialog(UINT nCode);
	BOOL OnCloseSettingsDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPEPWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnSettings();
	afx_msg void OnConnection();
	afx_msg void OnParameters();
	afx_msg void OnAlerts();
	afx_msg void OnHold();
	afx_msg void OnClearAll();
	afx_msg void OnPrint();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateConnection(CCmdUI *pCmdUI);
	afx_msg void OnUpdateParameters(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAlerts(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHold(CCmdUI *pCmdUI);
	afx_msg void OnUpdateClearAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarComputerPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarModePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarTypePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TPEP_H__
