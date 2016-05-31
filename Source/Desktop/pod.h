// POD.H : Parameter Observation Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the parameter observation display related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/25 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __POD_H__
#define __POD_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CPODPrintJobInfo

class CPODPrintJobInfo : public CObject
{
	// Construction
public:
	CPODPrintJobInfo();

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

	VOID Copy(CONST CPODPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CPODPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODPrintJobs

class CPODPrintJobs : public CPtrArray
{
	// Construction
public:
	CPODPrintJobs();
	~CPODPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CPODPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CPODPrintJobInfo *GetAt(INT nIndex) CONST;
	CPODPrintJobInfo *operator[](INT nIndex) CONST;

	TIMEKEY Schedule();

	VOID RemoveAll();

	BOOL Copy(CONST CPODPrintJobs *pPrintJobs);
	BOOL Compare(CONST CPODPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsLayoutPage dialog

#define IDC_PODSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS   1002
#define IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TIME   1003
#define IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_VALUE   1004
#define IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_STATUS   1005
#define IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_QUALITY   1006
#define IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TOOLTIPS_STATIC   1007
#define IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TOOLTIPS   1008
#define IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_STATIC   1009
#define IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST   1010
#define IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED   1011
#define IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_COLOR   1012
#define IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_ADD   1013
#define IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVE   1014
#define IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVEALL   1015
#define IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_STATIC   1016
#define IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST   1017
#define IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED   1018
#define IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_COLOR   1019
#define IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_ADD   1020
#define IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_REMOVE   1021
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS   1022
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1023
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION   1024
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_COMMENT_STATIC   1025
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1026
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES   1027
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1028
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE   1029
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1030
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE   1031
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1032
#define IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1033

class CPODSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CPODSettingsLayoutPage)

	// Construction
public:
	CPODSettingsLayoutPage();

	// Attributes
private:
	CPODLayout  m_cLayout[2];
	LOGFONT  m_fntTitle[2][3];
	LOGFONT  m_fntItems[2][3];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;

	// Dialog Data
	//{{AFX_DATA(CPODSettingsLayoutPage)
	enum { IDD = IDD_POD_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CPODLayout &cLayout) CONST;
	BOOL GetTitleFonts(LPLOGFONT pDataFont, LPLOGFONT pParametersFont, LPLOGFONT pFunctionsFont) CONST;
	BOOL GetItemsFonts(LPLOGFONT pDataFont, LPLOGFONT pParametersFont, LPLOGFONT pFunctionsFont) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CPODSettingsDialog *GetParentDialog() CONST;
	class CPODWnd *GetParentDisplay() CONST;

private:
	BOOL EnumFunctions();
	BOOL EnumParameters();
	BOOL EnumFontLocations();

	VOID ShowLayoutFontDetails();
	VOID ShowLayoutFontSample();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPODSettingsLayoutPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CPODLayout &cLayout);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPODSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnColumnTime();
	afx_msg void OnColumnValue();
	afx_msg void OnColumnStatus();
	afx_msg void OnColumnQuality();
	afx_msg void OnShowToolTips();
	afx_msg void OnAddFunction();
	afx_msg void OnRemoveFunction();
	afx_msg void OnRemoveAllFunctions();
	afx_msg void OnAddParameter();
	afx_msg void OnRemoveParameter();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeFunctionList();
	afx_msg void OnSelchangeFunctionUsed();
	afx_msg void OnSelchangeFunctionColor();
	afx_msg void OnSelchangeParameterList();
	afx_msg void OnSelchangeParameterUsed();
	afx_msg void OnSelchangeParameterColor();
	afx_msg void OnSelchangeFontLocation();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsContentsPage dialog

#define IDC_PODSETTINGS_CONTENTSPAGE_DETAILS   1001
#define IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_STATIC   1002
#define IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER   1003
#define IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_DEFAULT   1004
#define IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_CODED   1005
#define IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_SAMPLE_STATIC   1006
#define IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_SAMPLE   1007
#define IDC_PODSETTINGS_CONTENTSPAGE_STACK_STATIC   1008
#define IDC_PODSETTINGS_CONTENTSPAGE_STACK   1009
#define IDC_PODSETTINGS_CONTENTSPAGE_COLOR_STATIC   1010
#define IDC_PODSETTINGS_CONTENTSPAGE_COLOR   1011
#define IDC_PODSETTINGS_CONTENTSPAGE_STACK_ADD   1012
#define IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVE   1013
#define IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVEALL   1014
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_7   1015
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_8   1016
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_9   1017
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_4   1018
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_5   1019
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_6   1020
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_1   1021
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_2   1022
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_3   1023
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_0   1024
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_SIGN   1025
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_POINT   1026
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_DIV   1027
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_MUL   1028
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_SUB   1029
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_ADD   1030
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_SIN   1031
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_COS   1032
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_TAN   1033
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_ASIN   1034
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_ACOS   1035
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_ATAN   1036
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_ABS   1037
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_INT   1038
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_SQRT   1039
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_X2   1040
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_XY   1041
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_LN   1042
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_LOG   1043
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_EXP   1044
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_PI   1045
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_E   1046
#define IDC_PODSETTINGS_CONTENTSPAGE_KEY_ENTER   1047

// Specify the parameter observation display settings contents page related values
#define PODSETTINGSCONTENTSPAGE_STACKPOSINDICATOR_WIDTH   3
// Specify the parameter observation display settings contents page related limits
#define PODSETTINGSCONTENTSPAGE_MINIMUMSAMPLE   -100
#define PODSETTINGSCONTENTSPAGE_MAXIMUMSAMPLE   100
#define PODSETTINGSCONTENTSPAGE_DEFAULTSAMPLE   0

class CPODSettingsContentsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CPODSettingsContentsPage)

	// Construction
public:
	CPODSettingsContentsPage();

	// Attributes
private:
	CPODLayout  m_cLayout[2];
private:
	INT  m_nStackPos[2];

	// Dialog Data
	//{{AFX_DATA(CPODSettingsContentsPage)
	enum { IDD = IDD_POD_SETTINGS_CONTENTSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CPODLayout &cLayout) CONST;

	class CPODSettingsDialog *GetParentDialog() CONST;
	class CPODWnd *GetParentDisplay() CONST;

private:
	BOOL EnumParameters();
	UINT EnumExpressions();

	VOID Key(INT nDigit);
	VOID Key(LPCTSTR pszKey);

	INT CheckStackOperands() CONST;
	BOOL CheckStackContents(LPCTSTR pszKey) CONST;
	VOID UpdateStackContents();

	BOOL TranslateNumber(CPODLayoutExpression *pExpression, INT nDigit, double &fNumber);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPODSettingsContentsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CPODLayout &cLayout);
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPODSettingsContentsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nCtlID, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnAddParameter();
	afx_msg void OnRemoveExpression();
	afx_msg void OnRemoveAllExpressions();
	afx_msg void OnKey0();
	afx_msg void OnKey1();
	afx_msg void OnKey2();
	afx_msg void OnKey3();
	afx_msg void OnKey4();
	afx_msg void OnKey5();
	afx_msg void OnKey6();
	afx_msg void OnKey7();
	afx_msg void OnKey8();
	afx_msg void OnKey9();
	afx_msg void OnKeyPoint();
	afx_msg void OnKeyDiv();
	afx_msg void OnKeyMul();
	afx_msg void OnKeySub();
	afx_msg void OnKeyAdd();
	afx_msg void OnKeyChg();
	afx_msg void OnKeySin();
	afx_msg void OnKeyCos();
	afx_msg void OnKeyTan();
	afx_msg void OnKeyASin();
	afx_msg void OnKeyACos();
	afx_msg void OnKeyATan();
	afx_msg void OnKeyAbs();
	afx_msg void OnKeyInt();
	afx_msg void OnKeySqrt();
	afx_msg void OnKeyPow2();
	afx_msg void OnKeyPowY();
	afx_msg void OnKeyLn();
	afx_msg void OnKeyLog();
	afx_msg void OnKeyExp();
	afx_msg void OnKeyPI();
	afx_msg void OnKeyE();
	afx_msg void OnKeyEnter();
	afx_msg void OnSelchangeColor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsFilteringPage dialog

#define IDC_PODSETTINGS_FILTERINGPAGE_DETAILS   1001
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATIC   1002
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL   1003
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME   1004
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STATIC   1005
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME   1006
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY   1007
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME   1008
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STATIC   1009
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME   1010
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL   1011
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL_STATIC   1012
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL   1013
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START   1014
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME   1015
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP   1016
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME   1017
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES   1018
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_STATIC   1019
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_NUMBER   1020
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS   1021
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER   1022
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS   1023
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL   1024
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL   1025
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL   1026
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL   1027
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL   1028
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID   1029
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID   1030
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY   1031
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD   1032
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD   1033
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW   1034
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_UPDATES   1035
#define IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_CHANGES   1036
#define IDC_PODSETTINGS_FILTERINGPAGE_COLORS   1037
#define IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS_STATIC   1038
#define IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS   1039
#define IDC_PODSETTINGS_FILTERINGPAGE_COLORS_COLOR_STATIC 1040
#define IDC_PODSETTINGS_FILTERINGPAGE_COLORS_COLOR   1041

// Specify the parameter observation display settings filtering page related limits
#define PODSETTINGSFILTERINGPAGE_DEFAULTDAILYSTARTTIME   HOURS(8)
#define PODSETTINGSFILTERINGPAGE_DEFAULTDAILYSTOPTIME   HOURS(17)
#define PODSETTINGSFILTERINGPAGE_MINIMUMINTERVAL   1
#define PODSETTINGSFILTERINGPAGE_MAXIMUMINTERVAL   MINUTESPERDAY
#define PODSETTINGSFILTERINGPAGE_DEFAULTINTERVAL   5
#define PODSETTINGSFILTERINGPAGE_MINIMUMVALUES   1
#define PODSETTINGSFILTERINGPAGE_MAXIMUMVALUES   1000
#define PODSETTINGSFILTERINGPAGE_DEFAULTVALUES   100
#define PODSETTINGSFILTERINGPAGE_MINIMUMDIGITS   1
#define PODSETTINGSFILTERINGPAGE_MAXIMUMDIGITS   16
#define PODSETTINGSFILTERINGPAGE_DEFAULTDIGITS   8
#define PODSETTINGSFILTERINGPAGE_DEFAULTRANGE   MINUTESPERHOUR

class CPODSettingsFilteringPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CPODSettingsFilteringPage)

	// Construction
public:
	CPODSettingsFilteringPage();

	// Attributes
private:
	UINT  m_nMode[2];
	UINT  m_nLimit[2];
	UINT  m_nDigits[2];
	UINT  m_nStatus[2];
	CTimeKey  m_tRange[2][2][2];
	CTimeSpan  m_tDailyRange[2][2];
	CTimeSpan  m_tPeriodical[2];
	CUIntArray  m_nColors[2];

	// Dialog Data
	//{{AFX_DATA(CPODSettingsFilteringPage)
	enum { IDD = IDD_POD_SETTINGS_FILTERINGPAGE };
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
	BOOL GetColors(CUIntArray &nColors) CONST;

	class CPODSettingsDialog *GetParentDialog() CONST;
	class CPODWnd *GetParentDisplay() CONST;

private:
	BOOL EnumFilterStatus();

	UINT GetFilterStatus() CONST;

	VOID ShowFilterInfo();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPODSettingsFilteringPage)
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
	//{{AFX_MSG(CPODSettingsFilteringPage)
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
	afx_msg void OnFilterByShow();
	afx_msg void OnFilterByShowUpdates();
	afx_msg void OnFilterByShowChanges();
	afx_msg void OnSpinchangeFilterStartTime();
	afx_msg void OnSpinchangeFilterStopTime();
	afx_msg void OnSpinchangeFilterDailyStartTime();
	afx_msg void OnSpinchangeFilterDailyStopTime();
	afx_msg void OnSpinchangeFilterPeriodicalInterval();
	afx_msg void OnSpinchangeFilterPeriodicalStartTime();
	afx_msg void OnSpinchangeFilterPeriodicalStopTime();
	afx_msg void OnSpinchangeFilterLimit();
	afx_msg void OnSpinchangeFilterDigits();
	afx_msg void OnSelchangeFilterColorLocation();
	afx_msg void OnSelchangeFilterColor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsRetrievingPage dialog

#define IDC_PODSETTINGS_RETRIEVINGPAGE_DETAILS   1001
#define IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC   1002
#define IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE   1003
#define IDC_PODSETTINGS_RETRIEVINGPAGE_INSPECT   1004
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO   1005
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS   1006
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC   1007
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT   1008
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC   1009
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY   1010
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC   1011
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT   1012
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC   1013
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE   1014
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC   1015
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME   1016
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO   1017
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME   1018
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC   1019
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME   1020
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC   1021
#define IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE   1022

class CPODSettingsRetrievingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CPODSettingsRetrievingPage)

	// Construction
public:
	CPODSettingsRetrievingPage();

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CPODSettingsRetrievingPage)
	enum { IDD = IDD_POD_SETTINGS_RETRIEVINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetDataSourceFileName(CString &szFileName) CONST;

	class CPODSettingsDialog *GetParentDialog() CONST;
	class CPODWnd *GetParentDisplay() CONST;

private:
	VOID EnumDataSources();
	VOID ShowDataSourceInfo();

	BOOL CheckDataSource(LPCTSTR pszFileName) CONST;
	BOOL CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST;

	CString FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPODSettingsRetrievingPage)
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
	//{{AFX_MSG(CPODSettingsRetrievingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnInspect();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeFileName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsPrintingComments window

class CPODSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CPODSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CPODSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsPrintingPage dialog

#define IDC_PODSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_PODSETTINGS_PRINTINGPAGE_NAME_STATIC   1002
#define IDC_PODSETTINGS_PRINTINGPAGE_NAME   1003
#define IDC_PODSETTINGS_PRINTINGPAGE_ADDNAME   1004
#define IDC_PODSETTINGS_PRINTINGPAGE_REMOVENAME   1005
#define IDC_PODSETTINGS_PRINTINGPAGE_REMOVEALLNAMES   1006
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES   1007
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC   1008
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE   1009
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS   1010
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL   1011
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE   1012
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE   1013
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC   1014
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT   1015
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL   1016
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND   1017
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_STATIC   1018
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_PARAMETERS   1019
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_FUNCTIONS   1020
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS   1021
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC   1022
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT   1023
#define IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS   1024

// Specify the parameter observation display settings printing page related limits
#define PODSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMVALUES   1
#define PODSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMVALUES   1000
#define PODSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTVALUES   25

class CPODSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CPODSettingsPrintingPage)

	// Construction
public:
	CPODSettingsPrintingPage();

	// Attributes
private:
	CPODPrintJobs  m_pJobs[2];
private:
	CPODSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CPODSettingsPrintingPage)
	enum { IDD = IDD_POD_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CPODPrintJobs &pJobs) CONST;

	class CPODSettingsDialog *GetParentDialog() CONST;
	class CPODWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CPODPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPODSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CPODPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPODSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnAddName();
	afx_msg void OnRemoveName();
	afx_msg void OnRemoveAllNames();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnPrintAll();
	afx_msg void OnPrintBySide();
	afx_msg void OnPrintParameters();
	afx_msg void OnPrintFunctions();
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
// CPODSettingsPrintJobsPage dialog

#define IDC_PODSETTINGS_PRINTJOBSPAGE_DETAILS   1001
#define IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC   1002
#define IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS   1003
#define IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB   1004
#define IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC   1005
#define IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS   1006
#define IDC_PODSETTINGS_PRINTJOBSPAGE_REMOVEJOB   1007
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR   1008
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME   1009
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME   1010
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME   1011
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC   1012
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME   1013
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT   1014
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT   1015
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC   1016
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION   1017
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC   1018
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE   1019
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME  1020
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC   1021
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME   1022
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC   1023
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES   1024
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC   1025
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES   1026
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME   1027
#define IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME   1028

// Specify the parameter observation display settings print jobs page related repetition types
#define PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY   1
#define PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY   2
// Specify the parameter observation display settings print jobs page related limits
#define PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL   1
#define PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL   MINUTESPERHOUR
#define PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES   1
#define PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES   10000
#define PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES   10

class CPODSettingsPrintJobsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CPODSettingsPrintJobsPage)

	// Construction
public:
	CPODSettingsPrintJobsPage();

	// Attributes
private:
	CPODPrintJobs  m_pJobs[2];

	// Dialog Data
	//{{AFX_DATA(CPODSettingsPrintJobsPage)
	enum { IDD = IDD_POD_SETTINGS_PRINTJOBSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CPODPrintJobs &pJobs) CONST;

	class CPODSettingsDialog *GetParentDialog() CONST;
	class CPODWnd *GetParentDisplay() CONST;

private:
	BOOL EnumJobs();
	BOOL EnumEvents();

	VOID ShowJobInfo();
	BOOL CheckJobInfo() CONST;
	CPODPrintJobInfo *FindJobInfo(BOOL bActive = FALSE) CONST;

	VOID SetJobRepetitionInfo();
	UINT GetJobRepetitionType() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPODSettingsPrintJobsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CPODPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPODSettingsPrintJobsPage)
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
// CPODSettingsTabCtrl window

class CPODSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CPODSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CPODSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsDialog

class CPODSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CPODSettingsDialog)

	// Construction
public:
	CPODSettingsDialog();

	// Attributes
private:
	CPODSettingsTabCtrl  m_wndTabCtrl;
	CPODSettingsLayoutPage  m_pageLayout;
	CPODSettingsContentsPage  m_pageContents;
	CPODSettingsFilteringPage  m_pageFiltering;
	CPODSettingsRetrievingPage  m_pageRetrieving;
	CPODSettingsPrintingPage  m_pagePrinting;
	CPODSettingsPrintJobsPage  m_pagePrintJobs;

	// Operations
public:
	BOOL GetLayout(CPODLayout &cLayout) CONST;
	BOOL GetLayoutTitleFonts(LPLOGFONT pDataFont, LPLOGFONT pParametersFont, LPLOGFONT pFunctionsFont) CONST;
	BOOL GetLayoutItemsFonts(LPLOGFONT pDataFont, LPLOGFONT pParametersFont, LPLOGFONT pFunctionsFont) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL GetFilterLimit(UINT &nLimit) CONST;
	BOOL GetFilterDigits(UINT &nDigits) CONST;
	BOOL GetFilterStatus(UINT &nStatus) CONST;
	BOOL GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	BOOL GetFilterColors(CUIntArray &nColors) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CPODPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CPODOpenDialog *GetParentDialog() CONST;
	class CPODWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODSettingsDialog)
public:
	virtual BOOL OnDataExchange(HWND hPage, CONST CPODLayout &cLayout);
	virtual BOOL OnDataExchange(HWND hPage, CONST CPODPrintJobs &pJobs);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CPODSettingsDialog)
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
// CPODLinkagesDialog dialog

#define IDC_POD_LINKAGES_DETAILS   1001
#define IDC_POD_LINKAGES_NAME_STATIC   1002
#define IDC_POD_LINKAGES_NAME   1003
#define IDC_POD_LINKAGES_DISPLAYS_STATIC  1004
#define IDC_POD_LINKAGES_DISPLAYS   1005
#define IDC_POD_LINKAGES_LIST_STATIC   1006
#define IDC_POD_LINKAGES_LIST   1007
#define IDC_POD_LINKAGES_ADD   1008
#define IDC_POD_LINKAGES_REMOVE   1009
#define IDC_POD_LINKAGES_REMOVEALL   1010
#define IDC_POD_LINKAGES_HELP   1011

class CPODLinkagesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CPODLinkagesDialog)

	// Construction
public:
	CPODLinkagesDialog();   // standard constructor

	// Attributes
private:
	CPtrArray  m_pDisplays[3];

	// Dialog Data
	//{{AFX_DATA(CPODLinkagesDialog)
	enum { IDD = IDD_POD_LINKAGES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CPODWnd *GetParent() CONST;

private:
	BOOL EnumDisplays();

	INT FindDisplay(LPCTSTR pszName, BOOL bLinked = FALSE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODLinkagesDialog)
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
	//{{AFX_MSG(CPODLinkagesDialog)
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
// CPODRetrieveDialog dialog

#define IDC_POD_RETRIEVE_DETAILS   1001
#define IDC_POD_RETRIEVE_TITLE_STATIC   1002
#define IDC_POD_RETRIEVE_TITLE   1003
#define IDC_POD_RETRIEVE_TYPE_STATIC   1004
#define IDC_POD_RETRIEVE_TYPE   1005
#define IDC_POD_RETRIEVE_REALTIME   1006
#define IDC_POD_RETRIEVE_HISTORY   1007
#define IDC_POD_RETRIEVE_HISTORY_START_STATIC   1008
#define IDC_POD_RETRIEVE_HISTORY_STARTTIME   1009
#define IDC_POD_RETRIEVE_HISTORY_EXACTTIME   1010
#define IDC_POD_RETRIEVE_HISTORY_STOP_STATIC   1011
#define IDC_POD_RETRIEVE_HISTORY_STOPBYTIME   1012
#define IDC_POD_RETRIEVE_HISTORY_STOPTIME   1013
#define IDC_POD_RETRIEVE_HISTORY_STOPBYEND   1014
#define IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME   1015
#define IDC_POD_RETRIEVE_HISTORY_PLAYBACKMODE   1016
#define IDC_POD_RETRIEVE_HISTORY_AUTOMATIC   1017
#define IDC_POD_RETRIEVE_HISTORY_PSEUDOREALTIME   1018
#define IDC_POD_RETRIEVE_HISTORY_MANUAL   1019
#define IDC_POD_RETRIEVE_HISTORY_SPEED_STATIC   1020
#define IDC_POD_RETRIEVE_HISTORY_SPEED   1021
#define IDC_POD_RETRIEVE_HISTORY_SLOW   1022
#define IDC_POD_RETRIEVE_HISTORY_FAST   1023
#define IDC_POD_RETRIEVE_HISTORY_INTERVAL   1024
#define IDC_POD_RETRIEVE_HISTORY_INTERVALTIME   1025
#define IDC_POD_RETRIEVE_HISTORY_INTERVALTIME_STATIC   1026
#define IDC_POD_RETRIEVE_HELP   1027

// Specify the parameter observation display retrieve dialog related limits
#define PODRETRIEVEDIALOG_MINIMUMINTERVAL   1
#define PODRETRIEVEDIALOG_MAXIMUMINTERVAL   MINUTESPERWEEK
#define PODRETRIEVEDIALOG_DEFAULTINTERVAL   5

class CPODRetrieveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CPODRetrieveDialog)

	// Construction
public:
	CPODRetrieveDialog();   // standard constructor

	// Attributes
private:
	CString  m_szTitle;
	CString  m_szType;

	// Dialog Data
	//{{AFX_DATA(CPODRetrieveDialog)
	enum { IDD = IDD_POD_RETRIEVE_DIALOG };
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

	class CPODOpenDialog *GetParentDialog() CONST;
	class CPODWnd *GetParentDisplay() CONST;

private:
	BOOL SetRetrieveInfo();
	BOOL GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODRetrieveDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPODRetrieveDialog)
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
// CPODImportDialog dialog

#define IDC_POD_IMPORT_DETAILS   1001
#define IDC_POD_IMPORT_FILENAME_STATIC   1002
#define IDC_POD_IMPORT_FILENAME   1003
#define IDC_POD_IMPORT_BROWSE   1004
#define IDC_POD_IMPORT_INSPECT   1005
#define IDC_POD_IMPORT_DIRECTORY_STATIC   1006
#define IDC_POD_IMPORT_DIRECTORY   1007
#define IDC_POD_IMPORT_ADD   1008
#define IDC_POD_IMPORT_ADDALL   1009
#define IDC_POD_IMPORT_ATTENTION   1010
#define IDC_POD_IMPORT_ATTENTION_TEXT   1011
#define IDC_POD_IMPORT_LIST_STATIC   1012
#define IDC_POD_IMPORT_LIST   1013
#define IDC_POD_IMPORT_REMOVE   1014
#define IDC_POD_IMPORT_REMOVEALL   1015
#define IDC_POD_IMPORT_HELP   1016

class CPODImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CPODImportDialog)

	// Construction
public:
	CPODImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CPODLayouts  m_pDisplays[3];

	// Operations
private:
	VOID EnumDisplays();

	// Dialog Data
	//{{AFX_DATA(CPODImportDialog)
	enum { IDD = IDD_POD_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODImportDialog)
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
	//{{AFX_MSG(CPODImportDialog)
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
// CPODExportDialog dialog

#define IDC_POD_EXPORT_DETAILS   1001
#define IDC_POD_EXPORT_DIRECTORY_STATIC   1002
#define IDC_POD_EXPORT_DIRECTORY   1003
#define IDC_POD_EXPORT_ADD   1004
#define IDC_POD_EXPORT_ADDALL   1005
#define IDC_POD_EXPORT_LIST_STATIC   1006
#define IDC_POD_EXPORT_LIST   1007
#define IDC_POD_EXPORT_REMOVE   1008
#define IDC_POD_EXPORT_REMOVEALL   1009
#define IDC_POD_EXPORT_FILENAME_STATIC   1010
#define IDC_POD_EXPORT_FILENAME   1011
#define IDC_POD_EXPORT_BROWSE   1012
#define IDC_POD_EXPORT_HELP   1013

class CPODExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CPODExportDialog)

	// Construction
public:
	CPODExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CPODLayouts  m_pDisplays[2];

	// Operations
private:
	BOOL EnumDisplays();

	// Dialog Data
	//{{AFX_DATA(CPODExportDialog)
	enum { IDD = IDD_POD_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODExportDialog)
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
	//{{AFX_MSG(CPODExportDialog)
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
// CPODFindDialog dialog

#define IDC_POD_FIND_KEY_STATIC   1001
#define IDC_POD_FIND_KEY   1002
#define IDC_POD_FIND_VALUE_STATIC   1003
#define IDC_POD_FIND_VALUE   1004
#define IDC_POD_FIND_RESULTS_STATIC   1005
#define IDC_POD_FIND_RESULTS   1006
#define IDC_POD_FIND_SEARCH   1007
#define IDC_POD_FIND_OPEN   1008
#define IDC_POD_FIND_HELP   1009

class CPODFindDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CPODFindDialog)

	// Construction
public:
	CPODFindDialog();   // standard constructor

	// Attributes
private:
	INT  m_nType;
	CPODLayouts  m_pLayouts[2];
	CStringArray  m_szDescriptions;

	// Dialog Data
	//{{AFX_DATA(CPODFindDialog)
	enum { IDD = IDD_POD_FIND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, INT nType, CPODLayout &cLayout);

	class CPODWnd *GetParent() CONST;

private:
	BOOL EnumSearchKeys();
	BOOL EnumSearchValues();

	VOID DoFindByParameter(LPCTSTR pszParameter);
	VOID DoFindByParameters(CONST CStringArray &szParameters);
	VOID DoFindByDescription(LPCTSTR pszDescription);
	VOID DoFindByDescriptions(CONST CStringArray &szDescriptions);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPODFindDialog)
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
// CPODOpenDialog dialog

#define IDC_POD_OPEN_DETAILS   1001
#define IDC_POD_OPEN_DISPLAY_STATIC   1002
#define IDC_POD_OPEN_DISPLAY   1003
#define IDC_POD_OPEN_SETTINGS   1004
#define IDC_POD_OPEN_FIND   1005
#define IDC_POD_OPEN_TYPE   1006
#define IDC_POD_OPEN_TYPE_NORMAL   1007
#define IDC_POD_OPEN_TYPE_TEMPORARY   1008
#define IDC_POD_OPEN_REMOVE   1009
#define IDC_POD_OPEN_MODE   1010
#define IDC_POD_OPEN_MODE_REALTIME   1011
#define IDC_POD_OPEN_MODE_HISTORY   1012
#define IDC_POD_OPEN_HELP   1013

class CPODOpenDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CPODOpenDialog)

	// Construction
public:
	CPODOpenDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nFilterMode;
	UINT  m_nFilterLimit;
	UINT  m_nFilterDigits;
	UINT  m_nFilterStatus;
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	BOOL  m_bLayoutToolTips;
	LOGFONT  m_fntLayoutTitle[3];
	LOGFONT  m_fntLayoutItems[3];
	CString  m_szRetrieveFileName;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CTimeKey  m_tFilterRange[2][2];
	CTimeSpan  m_tFilterDailyRange[2];
	CTimeSpan  m_tFilterPeriodical;
	CTimeSpan  m_tRetrieveInterval;
	CUIntArray  m_nFilterColors;
	CPODPrintJobs  m_pPrintJobs;
	CPODLayout  m_cLayout;
private:
	CPODSettingsDialog  m_dlgSettings;
	CPODRetrieveDialog  m_dlgRetrievals;
	CPODFindDialog  m_dlgFindDisplay;

	// Dialog Data
	//{{AFX_DATA(CPODOpenDialog)
	enum { IDD = IDD_POD_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	CString GetTitle() CONST;
	UINT GetType() CONST;
	UINT GetMode() CONST;

	BOOL GetLayout(CPODLayout &cLayout) CONST;
	BOOL GetLayoutTitleFonts(LPLOGFONT plfDataFont, LPLOGFONT plfParametersFont, LPLOGFONT plfFunctionsFont) CONST;
	BOOL GetLayoutItemsFonts(LPLOGFONT plfDataFont, LPLOGFONT plfParametersFont, LPLOGFONT plfFunctionsFont) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL GetFilterLimit(UINT &nLimit) CONST;
	BOOL GetFilterDigits(UINT &nDigits) CONST;
	BOOL GetFilterStatus(UINT &nStatus) CONST;
	BOOL GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST;
	BOOL GetFilterColors(CUIntArray &nColors) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetRetrieveMode(UINT &nMode) CONST;
	BOOL GetRetrieveSpeed(UINT &nSpeed) CONST;
	BOOL GetRetrieveInterval(CTimeSpan &tInterval) CONST;
	BOOL GetRetrieveStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveStopTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CPODPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CPODWnd *GetParent() CONST;

private:
	VOID EnumLayouts();

	BOOL FindLayout() CONST;
	BOOL FindLayout(CPODLayout &cLayout) CONST;

	BOOL InitializeLayout(CPODLayout &cLayout) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODOpenDialog)
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
	//{{AFX_MSG(CPODOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSettings();
	afx_msg void OnFind();
	afx_msg void OnRemove();
	afx_msg void OnEditchangeTitle();
	afx_msg void OnSelchangeTitle();
	afx_msg void OnTypeNormal();
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
// CPODRetrieveThread thread

// Specify the parameter observation display retrieve thread action codes
#define PODRETRIEVETHREAD_ACTION_STOP   0
#define PODRETRIEVETHREAD_ACTION_AUTOFORWARD   1
#define PODRETRIEVETHREAD_ACTION_AUTOBACKWARD   2
#define PODRETRIEVETHREAD_ACTION_MANUALFORWARD   3
#define PODRETRIEVETHREAD_ACTION_MANUALBACKWARD   4
#define PODRETRIEVETHREAD_ACTION_PSEUDOREALTIME   5
#define PODRETRIEVETHREAD_ACTION_TYPES   6

class CPODRetrieveThread : public CThread
{
	DECLARE_DYNCREATE(CPODRetrieveThread)

	// Construction
public:
	CPODRetrieveThread();

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
	HANDLE  m_hAction[PODRETRIEVETHREAD_ACTION_TYPES];
private:
	CHistoryTMProcessEngine  m_cTMProcessEngine;
	CTMEnvironment  m_cTMEnvironment;

	// Operations
public:
	BOOL Start(class CPODWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime);
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
	//{{AFX_VIRTUAL(CPODRetrieveThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPODRetrieveThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODPrintThread thread

class CPODPrintThread : public CThread
{
	DECLARE_DYNCREATE(CPODPrintThread)

	// Construction
public:

	// Attributes
private:
	CPODPrintJobs  m_pPrintJobs;
private:
	CEvent  m_cEvent;

	// Operations
public:
	BOOL Start(class CPODWnd *pParentWnd);
	BOOL Stop();

	BOOL SetPrintJobs(CONST CPODPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CPODPrintJobs &pPrintJobs) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODPrintThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPODPrintThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODToolBar window

class CPODToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CPODToolBar)

	// Construction
public:
	CPODToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CPODToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODStatusBar window

class CPODStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CPODStatusBar)

	// Construction
public:
	CPODStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CPODWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CPODStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODToolTip window

class CPODToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CPODToolTip)

	// Construction
public:
	CPODToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CPODToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODSplitterBarCtrl window

class CPODSplitterBarCtrl : public CWnd
{
	DECLARE_DYNCREATE(CPODSplitterBarCtrl)

	// Construction
public:
	CPODSplitterBarCtrl();

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
	//{{AFX_VIRTUAL(CPODSplitterBarCtrl)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CPODSplitterBarCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODDataView window

class CPODDataView : public CTextView
{
	DECLARE_DYNCREATE(CPODDataView)

	// Construction
public:
	CPODDataView();

	// Attributes
private:
	CPODLayout  m_cLayout;
	CTMParameters  m_pLayoutValues[2];
	CPtrArray  m_pExpressionValues;
private:
	UINT  m_nFilterMode;
	UINT  m_nFilterLimit;
	UINT  m_nFilterDigits;
	UINT  m_nFilterStatus;
	CTimeKey  m_tFilterRange[2][2];
	CTimeSpan  m_tFilterDailyRange[2];
	CTimeSpan  m_tFilterPeriodical;
	CUIntArray  m_nFilterColors;
private:
	CString  m_szTag;
	CTimeTag  m_tTag;
	CFloatArray  m_fValues;
	BOOL  m_bValues;
private:
	BOOL  m_bUpdate;
private:
	CPODToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bToolTipMode;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetLayout(CONST CPODLayout &cLayout);
	BOOL SetLayout(CONST CPODLayout &cLayout, CONST CUIntArray &nWidths);
	BOOL GetLayout(CPODLayout &cLayout) CONST;
	BOOL GetLayout(CPODLayout &cLayout, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetTextFont(CONST LOGFONT *plfFont);
	BOOL GetTextFont(LOGFONT *plfFont, BOOL bValues = FALSE) CONST;

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
	BOOL SetFilterColors(CONST CUIntArray &nColors);
	BOOL GetFilterColors(CUIntArray &nColors) CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment, BOOL bBadData = FALSE);
	BOOL Initialize(CString &szTag, CTimeTag &tTag, BOOL bBadData = FALSE);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL, BOOL bBadData = FALSE);
	VOID Reset(CTMEnvironment *pTMEnvironment = NULL);

	BOOL SetValues(LPCTSTR pszTag, CONST CTimeTag &tTag, CONST CFloatArray &fValues, BOOL bInitialized);
	BOOL GetValues(CString &szTag, CTimeTag &tTag, CFloatArray &fValues, BOOL &bInitialized) CONST;
	VOID UpdateValues(LPCTSTR pszTag = EMPTYSTRING, CONST CTimeTag &tTag = 0);
	VOID DeleteValues(INT nIndex);
	VOID DeleteAllValues();

	VOID SetHoldFlag(BOOL bEnable = FALSE);
	BOOL GetHoldFlag() CONST;
	BOOL HasHoldFlag() CONST;

	BOOL GetPrintProperties(CPODLayout &cLayout, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CPtrArray &pFonts) CONST;

	BOOL AdjustColumns();

	class CPODWnd *GetParent() CONST;

private:
	INT LookupColumnNames(CONST CPODLayout &cLayout, CStringArray &szColumns) CONST;
	INT LookupColumnNames(UINT nColumns, CStringArray &szColumns) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;

	BOOL CalcColumnWidths(CONST CPODLayout &cLayout, CUIntArray &nWidths);
	BOOL CalcColumnWidths(CONST CStringArray &szColumns, CUIntArray &nWidths);
	BOOL CalcColumnWidths(UINT nColumns, CUIntArray &nWidths);

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	UINT PointToRow(CONST POINT &point) CONST;
	UINT PointToColumn(CONST POINT &point) CONST;

	CString ConstructToolTipTitle(INT nColumn) CONST;
	CString ConstructToolTipText(INT nRow, INT nColumn) CONST;

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODDataView)
public:
	virtual VOID RefreshContent();
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPODDataView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODParametersView window

class CPODParametersView : public CTextView
{
	DECLARE_DYNCREATE(CPODParametersView)

	// Construction
public:
	CPODParametersView();

	// Attributes
private:
	CPODLayout  m_cLayout;
	CTMParameters  m_pLayoutValues[2];
private:
	UINT  m_nFilterMode;
	UINT  m_nFilterLimit;
	UINT  m_nFilterDigits;
	UINT  m_nFilterStatus;
	CTimeKey  m_tFilterRange[2][2];
	CTimeSpan  m_tFilterDailyRange[2];
	CTimeSpan  m_tFilterPeriodical;
	CUIntArray  m_nFilterColors;
private:
	CPODToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bToolTipMode;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetLayout(CONST CPODLayout &cLayout);
	BOOL SetLayout(CONST CPODLayout &cLayout, CONST CUIntArray &nWidths);
	BOOL GetLayout(CPODLayout &cLayout) CONST;
	BOOL GetLayout(CPODLayout &cLayout, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetTextFont(CONST LOGFONT *plfFont);
	BOOL GetTextFont(LOGFONT *plfFont, BOOL bValues = FALSE) CONST;

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
	BOOL SetFilterColors(CONST CUIntArray &nColors);
	BOOL GetFilterColors(CUIntArray &nColors) CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment, BOOL bBadData = FALSE);
	BOOL Initialize(CString &szTag, CTimeTag &tTag, BOOL bBadData = FALSE);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL, BOOL bBadData = FALSE);
	VOID Reset(CTMEnvironment *pTMEnvironment = NULL);

	BOOL GetPrintProperties(CONST CPODLayout &cLayout, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CTMParameters &pValues, CPtrArray &pFonts) CONST;

	BOOL AdjustColumns();

	class CPODWnd *GetParent() CONST;

private:
	INT LookupColumnNames(CStringArray &szColumns) CONST;

	BOOL CalcColumnWidths(CUIntArray &nWidths);
	BOOL CalcColumnWidths(CONST CStringArray &szColumns, CUIntArray &nWidths);

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	UINT PointToRow(CONST POINT &point) CONST;
	UINT PointToColumn(CONST POINT &point) CONST;

	CString ConstructToolTipTitle(INT nRow) CONST;
	CString ConstructToolTipText(INT nRow, LPCTSTR pszColumn) CONST;

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODParametersView)
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPODParametersView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODFunctionsView window

class CPODFunctionsView : public CTextView
{
	DECLARE_DYNCREATE(CPODFunctionsView)

	// Construction
public:
	CPODFunctionsView();

	// Attributes
private:
	CPODLayout  m_cLayout;
private:
	UINT  m_nFilterMode;
	UINT  m_nFilterLimit;
	UINT  m_nFilterDigits;
	UINT  m_nFilterStatus;
	CTimeKey  m_tFilterRange[2][2];
	CTimeSpan  m_tFilterDailyRange[2];
	CTimeSpan  m_tFilterPeriodical;
	CUIntArray  m_nFilterColors;
private:
	CString  m_szTag;
	CTimeTag  m_tTag;
	ULONGLONG  m_nValues;
	CFloatArray  m_fValues;
	CTimeTag  m_tValueData[7];
	double  m_fValueData[7];
	BOOL  m_bValueData[7];
	BOOL  m_bValues;
private:
	CString  m_szUpdate;
	CTimeTag  m_tUpdate;
	BOOL  m_bUpdate;
private:
	CPODToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bToolTipMode;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetLayout(CONST CPODLayout &cLayout);
	BOOL SetLayout(CONST CPODLayout &cLayout, CONST CUIntArray &nWidths);
	BOOL GetLayout(CPODLayout &cLayout) CONST;
	BOOL GetLayout(CPODLayout &cLayout, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetTextFont(CONST LOGFONT *plfFont);
	BOOL GetTextFont(LOGFONT *plfFont, BOOL bValues = FALSE) CONST;

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
	BOOL SetFilterColors(CONST CUIntArray &nColors);
	BOOL GetFilterColors(CUIntArray &nColors) CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment, BOOL bBadData = FALSE);
	BOOL Initialize(CString &szTag, CTimeTag &tTag, BOOL bBadData = FALSE);
	BOOL Update(CTMEnvironment *pTMEnvironment = NULL, BOOL bBadData = FALSE);
	VOID Reset(CTMEnvironment *pTMEnvironment = NULL);

	BOOL SetValues(LPCTSTR pszTag, CONST CTimeTag &tTag, CONST CFloatArray &fValues, BOOL bInitialized);
	BOOL GetValues(CString &szTag, CTimeTag &tTag, CFloatArray &fValues, BOOL &bInitialized) CONST;

	VOID SetHoldFlag(BOOL bEnable = FALSE);
	BOOL GetHoldFlag() CONST;
	BOOL HasHoldFlag() CONST;

	BOOL GetPrintProperties(CONST CPODLayout &cLayout, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CPtrArray &pFonts) CONST;

	BOOL AdjustColumns();

	class CPODWnd *GetParent() CONST;

private:
	INT LookupColumnNames(CStringArray &szColumns) CONST;

	BOOL CalcColumnWidths(CUIntArray &nWidths);
	BOOL CalcColumnWidths(CONST CStringArray &szColumns, CUIntArray &nWidths);

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	UINT PointToRow(CONST POINT &point) CONST;
	UINT PointToColumn(CONST POINT &point) CONST;

	CString ConstructToolTipTitle(INT nRow) CONST;
	CString ConstructToolTipText(INT nRow, LPCTSTR pszColumn) CONST;

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODFunctionsView)
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPODFunctionsView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODWnd frame

// Specify the parameter observation display types
#define POD_TYPE_NORMAL   1
#define POD_TYPE_TEMPORARY   2
// Specify the parameter observation display views
#define POD_VIEW_DATA   0
#define POD_VIEW_PARAMETERS   1
#define POD_VIEW_FUNCTIONS   2
// Specify the parameter observation display title items
#define POD_TITLEITEM_TIME   (1<<0)
#define POD_TITLEITEM_VALUE   (1<<1)
#define POD_TITLEITEM_STATUS   (1<<2)
#define POD_TITLEITEM_QUALITY   (1<<3)
#ifndef RC_INVOKED
#define POD_TITLEITEMS_DEFAULT   (POD_TITLEITEM_TIME | POD_TITLEITEM_VALUE | POD_TITLEITEM_STATUS | POD_TITLEITEM_QUALITY)
#define POD_TITLEITEMS_ALL   POD_TITLEITEMS_DEFAULT
#endif
// Specify the parameter observation display filter modes
#define POD_FILTER_RANGE   (1<<0)
#define POD_FILTER_DAILYRANGE   (1<<1)
#define POD_FILTER_PERIODICALRANGE   (1<<2)
#define POD_FILTER_LIMIT   (1<<3)
#define POD_FILTER_STATUS   (1<<4)
#define POD_FILTER_UPDATES   (1<<5)
#define POD_FILTER_CHANGES   (1<<6)
// Specify the parameter observation display default filter settings
#define POD_FILTER_DEFAULTMODE   0
#define POD_FILTER_DEFAULTNOLIMIT   1000
#define POD_FILTER_DEFAULTLIMIT   100
// Specify the parameter observation display retrieval modes
#define POD_RETRIEVE_EXACTTIME   (1<<0)
#define POD_RETRIEVE_STOPBYTIME   (1<<1)
#define POD_RETRIEVE_STOPBYEND   (1<<2)
#define POD_RETRIEVE_STOPBYREALTIME   (1<<3)
#define POD_RETRIEVE_STOPPED   (1<<4)
#define POD_RETRIEVE_RELATIVE   (1<<5)
#define POD_RETRIEVE_AUTOFORWARD   (1<<6)
#define POD_RETRIEVE_AUTOBACKWARD   (1<<7)
#define POD_RETRIEVE_MANUALFORWARD   (1<<8)
#define POD_RETRIEVE_MANUALBACKWARD   (1<<9)
#define POD_RETRIEVE_PSEUDOREALTIME   (1<<10)
// Specify the parameter observation display print modes
#define POD_PRINT_ALL   (1<<0)
#define POD_PRINT_FIRSTSIDE   (1<<1)
#define POD_PRINT_LASTSIDE   (1<<2)
#define POD_PRINT_PARAMETERS   (1<<3)
#define POD_PRINT_FUNCTIONS   (1<<4)
#define POD_PRINT_UNDERLINEOOL   (1<<5)
#define POD_PRINT_COLORLEGEND   (1<<6)
#define POD_PRINT_CLEARCOMMENTS   (1<<7)
#define POD_PRINT_ATTIME   (1<<8)
#define POD_PRINT_ATDAILYTIME   (1<<9)
#define POD_PRINT_ATEVENT   (1<<10)
#define POD_PRINT_REPEATBYINTERVAL   (1<<11)
#define POD_PRINT_REPEATSTOPBYCOUNT   (1<<12)
#define POD_PRINT_REPEATSTOPBYTIME   (1<<13)
#define POD_PRINT_DAILYREPEATSTOPBYCOUNT   (1<<14)
#define POD_PRINT_DAILYREPEATSTOPBYTIME   (1<<15)
#define POD_PRINT_ACTIVE   (1<<16)
// Specify the parameter observation display print fonts
#define POD_PRINTFONT_TITLE   0
#define POD_PRINTFONT_SUBTITLE   1
#define POD_PRINTFONT_OPERATINGDETAILS   2
#define POD_PRINTFONT_OPERATINGMODE   3
#define POD_PRINTFONT_DATATITLE   4
#define POD_PRINTFONT_DATALISTITEMSTITLE   5
#define POD_PRINTFONT_DATALISTITEMS   6
#define POD_PRINTFONT_DATALISTVALUES   7
#define POD_PRINTFONT_PARAMETERSTITLE   8
#define POD_PRINTFONT_PARAMETERSLISTITEMSTITLE   9
#define POD_PRINTFONT_PARAMETERSLISTITEMS   10
#define POD_PRINTFONT_PARAMETERSLISTVALUES   11
#define POD_PRINTFONT_FUNCTIONSTITLE   12
#define POD_PRINTFONT_FUNCTIONSLISTITEMSTITLE   13
#define POD_PRINTFONT_FUNCTIONSLISTITEMS   14
#define POD_PRINTFONT_FUNCTIONSLISTVALUES   15
#define POD_PRINTFONT_FOOTER   16
#define POD_PRINTFONT_NOTICE   17
#define POD_PRINTFONT_LOGO   18
#define POD_PRINTFONTS   19
// Specify the parameter observation display OOL colors
#define POD_OOLCOLOR_NOLIMIT   0
#define POD_OOLCOLOR_SOFTLIMIT   1
#define POD_OOLCOLOR_HARDLIMIT   2
#define POD_OOLCOLOR_DELTALIMIT   3
#define POD_OOLCOLOR_CONSISTENCYLIMIT   4
// Specify the parameter observation display statusbar pane identifiers
#define ID_POD_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_POD_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_POD_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class CPODWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CPODWnd)

	// Construction
public:
	CPODWnd();

	// Attributes
private:
	CPODToolBar  m_wndToolBar;
	CPODStatusBar  m_wndStatusBar;
	CPODDataView  m_wndDataView;
	CPODParametersView  m_wndParametersView;
	CPODFunctionsView  m_wndFunctionsView;
	CPODSplitterBarCtrl  m_wndSplitterBarCtrl[3];
private:
	CPODOpenDialog  m_dlgOpen;
	CPODSettingsDialog  m_dlgSettings;
	CPODLinkagesDialog  m_dlgLinkages;
	CPODRetrieveDialog  m_dlgRetrievals;
private:
	CPODRetrieveThread  m_cRetrieveThread;
	CPODPrintThread  m_cPrintThread;
private:
	LONG  m_bRetrieveFlag;
	LONG  m_nRetrieveMode;
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
private:
	CSize  m_sizeViews[3];
	BOOL  m_bViews[3];

	// Operations
public:
	BOOL SetLayout(LPCTSTR pszLayout);
	BOOL SetLayout(CONST CPODLayout &cLayout);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nDataViewWidths, CONST CUIntArray &nParametersViewWidths, CONST CUIntArray &nFunctionsViewWidths);
	BOOL SetLayout(CONST CPODLayout &cLayout, CONST CUIntArray &nDataViewWidths, CONST CUIntArray &nParametersViewWidths, CONST CUIntArray &nFunctionsViewWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CPODLayout &cLayout) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nDataViewWidths, CUIntArray &nParametersViewWidths, CUIntArray &nFunctionsViewWidths) CONST;
	BOOL GetLayout(CPODLayout &cLayout, CUIntArray &nDataViewWidths, CUIntArray &nParametersViewWidths, CUIntArray &nFunctionsViewWidths) CONST;

	BOOL SetTitleFonts(CONST LOGFONT *plfDataFont, CONST LOGFONT *plfParametersFont, CONST LOGFONT *plfFunctionsFont);
	BOOL GetTitleFonts(LPLOGFONT plfDataFont, LPLOGFONT plfParametersFont, LPLOGFONT plfFunctionsFont) CONST;
	BOOL SetItemsFonts(CONST LOGFONT *plfDataFont, CONST LOGFONT *plfParametersFont, CONST LOGFONT *plfFunctionsFont);
	BOOL GetItemsFonts(LPLOGFONT plfDataFont, LPLOGFONT plfParametersFont, LPLOGFONT plfFunctionsFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetFilterMode(UINT nMode = POD_FILTER_DEFAULTMODE);
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
	BOOL SetFilterColors(CONST CUIntArray &nColors);
	BOOL GetFilterColors(CUIntArray &nColors) CONST;

	INT GetSampleCount() CONST;

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

	BOOL SetPrintJobs(CONST CPODPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CPODPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CPODPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	CPODWnd *Find(INT nType, UINT nMode, LPCTSTR pszName) CONST;

	VOID SetUpdateInfo();
	VOID SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, WORD wQuality);
	BOOL GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, WORD &wQuality) CONST;

private:
	BOOL CreateToolBar();
	BOOL CreateStatusBar();
	BOOL CreateSplitterBars();
	BOOL CreateViews();

	VOID InitializeViews();
	CRect RepositionViews(BOOL bAdjust = TRUE);
	BOOL SetViewSize(UINT nView, CONST CSize &size);
	CSize GetViewSize(UINT nView) CONST;
	CRect RepositionView(UINT nView = POD_VIEW_DATA);
	BOOL IsViewVisible(UINT nView = POD_VIEW_DATA) CONST;
	CRect RepositionViewSplitterBar(BOOL bUpper = TRUE) CONST;

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateModePane();
	VOID UpdateTypePane();

	VOID UpdateData(BOOL bInfo = TRUE);

	BOOL LoadLayout(LPCTSTR pszLayout, CPODLayout &cLayout);

	VOID SetHoldFlag(BOOL bEnable = FALSE);
	BOOL GetHoldFlag() CONST;
	BOOL HasHoldFlag() CONST;

	BOOL StartSchedulePrintJobs();
	BOOL IsSchedulingPrintJobs() CONST;
	BOOL StopSchedulePrintJobs();

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CPODPrintJobInfo *pJobInfo, CPODLayout &cLayout, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szDataColumns, CStringArray &szDataContents, CTextViewAttributes &pDataAttributes, CStringArray &szParametersColumns, CStringArray &szParametersContents, CTextViewAttributes &pParametersAttributes, CStringArray &szFunctionsColumns, CStringArray &szFunctionsContents, CTextViewAttributes &pFunctionsAttributes, CTMParameters &pValues, CUIntArray &nOOLColors, CPtrArray &pFonts) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CPODPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CPODLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szDataColumns, CONST CStringArray &szDataContents, CONST CTextViewAttributes &pDataAttributes, CONST CStringArray &szParametersColumns, CONST CStringArray &szParametersContents, CONST CTextViewAttributes &pParametersAttributes, CONST CStringArray &szFunctionsColumns, CONST CStringArray &szFunctionsContents, CONST CTextViewAttributes &pFunctionsAttributes, CONST CTMParameters &pValues, CONST CUIntArray &nOOLColors, CONST CPtrArray &pItemFonts);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CPODPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, CONST CPODLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, LPCTSTR pszTitle, CONST CStringArray &szColumns, CONST CUIntArray &nOOLColors, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CONST CUIntArray &nOOLColors, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(CONST CPODLayout &cLayout) CONST;
	CString GetPrintDocOperatingDetails(CONST CPODPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST;
	CString GetPrintDocOperatingMode(CONST CPODPrintJobInfo *pJobInfo, CONST CUIntArray &nOOLColors) CONST;
	CString GetPrintDocListTitle(LPCTSTR pszTitle) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListTitleFont(CDC &cDC, INT nView, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, INT nView, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST LOGFONT *pValuesFont, CFont &cTitleFont, CFont &cItemsFont, CFont &cValuesFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, INT nView, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, INT nView, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CFont *pValuesFont, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, INT nView, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont, CFont *pValuesFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPODWnd)
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
	//{{AFX_MSG(CPODWnd)
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
	afx_msg void OnLinkages();
	afx_msg void OnHold();
	afx_msg void OnClearAll();
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
	afx_msg void OnUpdateHold(CCmdUI *pCmdUI);
	afx_msg void OnUpdateClearAll(CCmdUI *pCmdUI);
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


#endif // __POD_H__
