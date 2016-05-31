// EVENTBOX.H : Eventbox Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the eventbox related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/05/04 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __EVENTBOX_H__
#define __EVENTBOX_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CEventBoxPrintJobInfo

class CEventBoxPrintJobInfo : public CObject
{
	// Construction
public:
	CEventBoxPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbProfile;
		INT  cbComments;
		UINT  nPrintMode;
		UINT  nPrintAtCount;
		UINT  nPrintByCount;
		UINT  nPrintCount[3];
		UINT  nRepeatStopByCount[2];
		TIMEKEY  tPrintAtTime;
		TIMEKEY  tPrintAtDailyTime;
		TIMEKEY  tPrintByDailyStartTime;
		TIMEKEY  tPrintByDailyStopTime;
		TIMEKEY  tPrintLastTime[2];
		TIMEKEY  tRepeatInterval;
		TIMEKEY  tRepeatStopByTime[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szProfile;
	CString  m_szComments;
	UINT  m_nPrintMode;
	UINT  m_nPrintFlags;
	UINT  m_nPrintAtCount;
	UINT  m_nPrintByCount;
	UINT  m_nPrintCount[3];
	UINT  m_nRepeatStopByCount[2];
	CTimeKey  m_tPrintAtTime;
	CTimeKey  m_tPrintLastTime[2];
	CTimeKey  m_tRepeatStopByTime[2];
	CTimeSpan  m_tPrintByDailyStartTime;
	CTimeSpan  m_tPrintByDailyStopTime;
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
	BOOL SetPrintByTime(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime);
	BOOL GetPrintByTime(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
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
	BOOL SetPrintAtCount(UINT nCount);
	BOOL GetPrintAtCount(UINT &nCount) CONST;
	BOOL SetPrintCount(UINT nCount);
	BOOL GetPrintCount(UINT &nCount) CONST;
	BOOL SetPrintDailyCount(UINT nCount);
	BOOL GetPrintDailyCount(UINT &nCount) CONST;
	BOOL SetPrintLastCount(UINT nCount);
	BOOL GetPrintLastCount(UINT &nCount) CONST;
	BOOL SetPrintLastTime(CONST CTimeKey &tTime);
	BOOL GetPrintLastTime(CTimeKey &tTime) CONST;
	BOOL SetPrintLastDailyTime(CONST CTimeKey &tTime);
	BOOL GetPrintLastDailyTime(CTimeKey &tTime) CONST;

	VOID Copy(CONST CEventBoxPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CEventBoxPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxPrintJobs

class CEventBoxPrintJobs : public CPtrArray
{
	// Construction
public:
	CEventBoxPrintJobs();
	~CEventBoxPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CEventBoxPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CEventBoxPrintJobInfo *GetAt(INT nIndex) CONST;
	CEventBoxPrintJobInfo *operator[](INT nIndex) CONST;

	TIMEKEY Schedule(UINT nCount);

	VOID RemoveAll();

	BOOL Copy(CONST CEventBoxPrintJobs *pPrintJobs);
	BOOL Compare(CONST CEventBoxPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsLayoutPage dialog

#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TIMEITEM   1003
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_CATEGORYITEM   1004
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TYPEITEM   1005
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_MESSAGEITEM   1006
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_COMMENTSITEM   1007
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_RECIPIENTSITEM   1008
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_USERITEM   1009
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS   1010
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1011
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1012
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS   1013
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1014
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1015
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES   1016
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1017
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE   1018
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1019
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE   1020
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1021
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1022
#define IDC_EVENTBOXSETTINGS_LAYOUTPAGE_DEFAULT   1023

class CEventBoxSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CEventBoxSettingsLayoutPage)

	// Construction
public:
	CEventBoxSettingsLayoutPage();

	// Attributes
private:
	UINT  m_nColumns[2];
	LOGFONT  m_fntTitle[2];
	LOGFONT  m_fntItems[2];
private:
	CString  m_szFontSampleText;
	BOOL  m_bDefault;

	// Dialog Data
	//{{AFX_DATA(CEventBoxSettingsLayoutPage)
	enum { IDD = IDD_EVENTBOX_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetTitle(UINT &nColumns) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetListFont(LPLOGFONT pListFont) CONST;

	BOOL UseAsDefault(BOOL &bDefault) CONST;

	class CEventBoxSettingsDialog *GetParentDialog() CONST;
	class CEventBoxWnd *GetParentDisplay() CONST;

private:
	VOID ShowLayoutFontDetails();
	VOID ShowLayoutFontSample();

	BOOL CheckPrivilege(UINT nPrivilege) CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSettingsLayoutPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEventBoxSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTitleItems();
	afx_msg void OnTitleFont();
	afx_msg void OnItemsFont();
	afx_msg void OnUseAsDefault();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxFilterDialog dialog

#define IDC_EVENTBOX_FILTER_DETAILS   1001
#define IDC_EVENTBOX_FILTER_TYPES_STATIC   1002
#define IDC_EVENTBOX_FILTER_TYPES   1003
#define IDC_EVENTBOX_FILTER_TYPE_ADD   1004
#define IDC_EVENTBOX_FILTER_TYPE_REMOVE   1005
#define IDC_EVENTBOX_FILTER_TYPE_REMOVEALL   1006
#define IDC_EVENTBOX_FILTER_SUBTYPES_STATIC   1007
#define IDC_EVENTBOX_FILTER_SUBTYPES   1008
#define IDC_EVENTBOX_FILTER_SUBTYPE_ADD   1009
#define IDC_EVENTBOX_FILTER_SUBTYPE_REMOVE   1010
#define IDC_EVENTBOX_FILTER_SUBTYPE_REMOVEALL   1011
#define IDC_EVENTBOX_FILTER_HELP   1012

class CEventBoxFilterDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxFilterDialog)

	// Construction
public:
	CEventBoxFilterDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szTypes[2];
	CStringArray  m_szSubtypes[2];

	// Dialog Data
	//{{AFX_DATA(CEventBoxFilterDialog)
	enum { IDD = IDD_EVENTBOX_FILTER_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	VOID SetFilterInfo(CONST CStringArray &szTypes, CONST CStringArray &szSubtypes);
	VOID GetFilterInfo(CStringArray &szTypes, CStringArray &szSubtypes) CONST;

	class CEventBoxSettingsFilteringPage *GetParentDialog() CONST;
	class CEventBoxWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTypes();
	BOOL EnumSubtypes();

	BOOL CheckPrivilege(UINT nPrivilege) CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxFilterDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxFilterDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddType();
	afx_msg void OnRemoveType();
	afx_msg void OnRemoveAllTypes();
	afx_msg void OnAddSubtype();
	afx_msg void OnRemoveSubtype();
	afx_msg void OnRemoveAllSubtypes();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeSubtype();
	afx_msg void OnEditchangeType();
	afx_msg void OnEditchangeSubtype();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsFilteringPage dialog

#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_DETAILS   1001
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORIES   1002
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SYSTEM   1003
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SPACECRAFT   1004
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_USER   1005
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_TYPES   1006
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CONTENTS   1007
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME   1008
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME   1009
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TOTIME   1010
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STOPTIME   1011
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS   1012
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_STATIC   1013
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT   1014
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR   1015
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS   1016
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_STATIC   1017
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT   1018
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGEVENTS   1019
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_LISTEVENTS   1020
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE   1021
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_NOTIFY   1022
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_USESOUND   1023
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS   1024
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY_STATIC   1025
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY   1026
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE_STATIC   1027
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE   1028
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_USE   1029
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_LIST   1030
#define IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TEXT   1031

// Specify the eventbox settings filtering page related limits
#define EVENTBOXSETTINGSFILTERINGPAGE_LIMITATION_DEFAULTINTERVAL   SECONDSPERHOUR
#define EVENTBOXSETTINGSFILTERINGPAGE_LIMITATION_MINIMUMEVENTS   10
#define EVENTBOXSETTINGSFILTERINGPAGE_LIMITATION_MAXIMUMEVENTS   10000
#define EVENTBOXSETTINGSFILTERINGPAGE_LIMITATION_DEFAULTEVENTS   1000
#define EVENTBOXSETTINGSFILTERINGPAGE_BEHAVIOR_MINIMUMEVENTS   1
#define EVENTBOXSETTINGSFILTERINGPAGE_BEHAVIOR_MAXIMUMEVENTS   1000
#define EVENTBOXSETTINGSFILTERINGPAGE_BEHAVIOR_DEFAULTEVENTS   10

class CEventBoxSettingsFilteringPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CEventBoxSettingsFilteringPage)

	// Construction
public:
	CEventBoxSettingsFilteringPage();

	// Attributes
private:
	UINT  m_nMode[2];
	UINT  m_nLimit[2];
	UINT  m_nCount[2];
	CTimeKey  m_tStartTime[2];
	CTimeKey  m_tStopTime[2];
	CUIntArray  m_nColors[2];
	CStringArray  m_szTypes[2];
	CStringArray  m_szSubtypes[2];

	// Dialog Data
	//{{AFX_DATA(CEventBoxSettingsFilteringPage)
	enum { IDD = IDD_EVENTBOX_SETTINGS_FILTERINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetMode(UINT &nMode) CONST;
	BOOL GetBehavior(UINT &nCount) CONST;
	BOOL GetBehavior(CStringArray &szTypes, CStringArray &szSubtypes) CONST;
	BOOL GetLimitation(UINT &nLimit) CONST;
	BOOL GetLimitation(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL GetColors(CUIntArray &nColors) CONST;

	class CEventBoxSettingsDialog *GetParentDialog() CONST;
	class CEventBoxWnd *GetParentDisplay() CONST;

private:
	BOOL CheckPrivilege(UINT nPrivilege) CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSettingsFilteringPage)
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
	//{{AFX_MSG(CEventBoxSettingsFilteringPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnFilterSystem();
	afx_msg void OnFilterSpacecraft();
	afx_msg void OnFilterUser();
	afx_msg void OnFilterTypes();
	afx_msg void OnLimitByTime();
	afx_msg void OnLimitByEvents();
	afx_msg void OnSpinchangeLimitByStartTime();
	afx_msg void OnSpinchangeLimitByStopTime();
	afx_msg void OnSpinchangeLimitByEvents();
	afx_msg void OnBehaviorAutoEvents();
	afx_msg void OnBehaviorBringEvents();
	afx_msg void OnBehaviorListEvents();
	afx_msg void OnBehaviorAutoAcknowledge();
	afx_msg void OnBehaviorNotify();
	afx_msg void OnBehaviorUseSound();
	afx_msg void OnSpinchangeBehaviorAutoEvents();
	afx_msg void OnSelchangeColorsCategory();
	afx_msg void OnSelchangeColorsType();
	afx_msg void OnSelchangeColorsList();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsPrintingComments window

class CEventBoxSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CEventBoxSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CEventBoxSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsPrintingPage dialog

#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME_STATIC   1002
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME   1003
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_ADDNAME   1004
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVENAME   1005
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES   1006
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES   1007
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC   1008
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE   1009
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS   1010
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL   1011
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE   1012
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE   1013
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC   1014
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT   1015
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME   1016
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME   1017
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC   1018
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME   1019
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS   1020
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC   1021
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT   1022
#define IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS   1023

// Specify the eventbox settings printing page related limits
#define EVENTBOXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTINTERVAL   (2*SECONDSPERHOUR)
#define EVENTBOXSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMEVENTS   1
#define EVENTBOXSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMEVENTS   10000
#define EVENTBOXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTEVENTS   25

class CEventBoxSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CEventBoxSettingsPrintingPage)

	// Construction
public:
	CEventBoxSettingsPrintingPage();

	// Attributes
private:
	CEventBoxPrintJobs  m_pJobs[2];
private:
	CEventBoxSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CEventBoxSettingsPrintingPage)
	enum { IDD = IDD_EVENTBOX_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CEventBoxPrintJobs &pJobs) CONST;

	class CEventBoxSettingsDialog *GetParentDialog() CONST;
	class CEventBoxWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CEventBoxPrintJobInfo *FindJobInfo() CONST;

	BOOL CheckPrivilege(UINT nPrivilege) CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CEventBoxPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEventBoxSettingsPrintingPage)
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
// CEventBoxSettingsPrintJobsPage dialog

#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DETAILS   1001
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC   1002
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS   1003
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB   1004
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC   1005
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS   1006
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_REMOVEJOB   1007
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR   1008
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME   1009
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME   1010
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME   1011
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC   1012
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME   1013
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT   1014
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT_STATIC   1015
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT   1016
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION   1017
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC   1018
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE   1019
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME  1020
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC   1021
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME   1022
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC   1023
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES   1024
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC   1025
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES   1026
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME   1027
#define IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME   1028

// Specify the eventbox settings print jobs page related repetition types
#define EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY   1
#define EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY   2
// Specify the eventbox settings print jobs page related limits
#define EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL   1
#define EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL   MINUTESPERHOUR
#define EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES   1
#define EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES   10000
#define EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES   10

class CEventBoxSettingsPrintJobsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CEventBoxSettingsPrintJobsPage)

	// Construction
public:
	CEventBoxSettingsPrintJobsPage();

	// Attributes
private:
	CEventBoxPrintJobs  m_pJobs[2];

	// Dialog Data
	//{{AFX_DATA(CEventBoxSettingsPrintJobsPage)
	enum { IDD = IDD_EVENTBOX_SETTINGS_PRINTJOBSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CEventBoxPrintJobs &pJobs) CONST;

	class CEventBoxSettingsDialog *GetParentDialog() CONST;
	class CEventBoxWnd *GetParentDisplay() CONST;

private:
	BOOL EnumJobs();

	VOID ShowJobInfo();
	BOOL CheckJobInfo() CONST;
	CEventBoxPrintJobInfo *FindJobInfo(BOOL bActive = FALSE) CONST;

	VOID SetJobRepetitionInfo();
	UINT GetJobRepetitionType() CONST;

	BOOL CheckPrivilege(UINT nPrivilege) CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSettingsPrintJobsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CEventBoxPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEventBoxSettingsPrintJobsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddJob();
	afx_msg void OnRemoveJob();
	afx_msg void OnSelchangeDefinedJob();
	afx_msg void OnSelchangeActiveJob();
	afx_msg void OnPrintAtTime();
	afx_msg void OnPrintAtDailyTime();
	afx_msg void OnPrintAtCount();
	afx_msg void OnSelchangeRepetitionType();
	afx_msg void OnRepeatByTime();
	afx_msg void OnRepetitionStopByCopies();
	afx_msg void OnRepetitionStopByTime();
	afx_msg void OnSpinchangePrintTime();
	afx_msg void OnSpinchangePrintDailyTime();
	afx_msg void OnSpinchangePrintCount();
	afx_msg void OnSpinchangeRepeatTime();
	afx_msg void OnSpinchangeRepetitionStopCopies();
	afx_msg void OnSpinchangeRepetitionStopTime();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsTabCtrl window

class CEventBoxSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CEventBoxSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CEventBoxSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsDialog

class CEventBoxSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CEventBoxSettingsDialog)

	// Construction
public:
	CEventBoxSettingsDialog();

	// Attributes
private:
	CEventBoxSettingsTabCtrl  m_wndTabCtrl;
	CEventBoxSettingsLayoutPage  m_pageLayout;
	CEventBoxSettingsFilteringPage  m_pageFiltering;
	CEventBoxSettingsPrintingPage  m_pagePrinting;
	CEventBoxSettingsPrintJobsPage  m_pagePrintJobs;

	// Operations
public:
	BOOL GetLayoutTitle(UINT &nColumns) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutListFont(LPLOGFONT pListFont) CONST;
	BOOL UseLayoutAsDefault(BOOL &bDefault) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL GetFilterBehavior(UINT &nCount) CONST;
	BOOL GetFilterBehavior(CStringArray &szTypes, CStringArray &szSubtypes) CONST;
	BOOL GetFilterLimitation(UINT &nLimit) CONST;
	BOOL GetFilterLimitation(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL GetFilterColors(CUIntArray &nColors) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetPrintJobs(CEventBoxPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CEventBoxOpenDialog *GetParentDialog() CONST;
	class CEventBoxWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSettingsDialog)
public:
	virtual BOOL OnDataExchange(HWND hPage, CONST CEventBoxPrintJobs &pJobs);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CEventBoxSettingsDialog)
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
// CEventBoxScheduleInfoDialog dialog

#define IDC_EVENTBOX_SCHEDULEINFO_DETAILS   1001
#define IDC_EVENTBOX_SCHEDULEINFO_CATEGORY_STATIC   1002
#define IDC_EVENTBOX_SCHEDULEINFO_CATEGORY   1003
#define IDC_EVENTBOX_SCHEDULEINFO_TYPE_STATIC   1004
#define IDC_EVENTBOX_SCHEDULEINFO_TYPE   1005
#define IDC_EVENTBOX_SCHEDULEINFO_COMMENTS_STATIC   1006
#define IDC_EVENTBOX_SCHEDULEINFO_COMMENTS   1007
#define IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS   1008
#define IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION_STATIC   1009
#define IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION   1010
#define IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS_STATIC   1011
#define IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS   1012
#define IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION   1013
#define IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE_STATIC   1014
#define IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE   1015
#define IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE_BROWSE   1016
#define IDC_EVENTBOX_SCHEDULEINFO_HELP   1017

class CEventBoxScheduleInfoDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxScheduleInfoDialog)

	// Construction
public:
	CEventBoxScheduleInfoDialog();   // standard constructor

	// Attributes
private:
	CEventObject  m_cEvent[2];
	CNotificationProfiles  m_pProfiles;

	// Dialog Data
	//{{AFX_DATA(CEventBoxScheduleInfoDialog)
	enum { IDD = IDD_EVENTBOX_SCHEDULEINFO_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CEventObject *pEvent);

	VOID SetScheduleInfo(CONST CEventObject *pEvent);
	BOOL GetScheduleInfo(CEventObject *pEvent) CONST;

	class CEventBoxScheduleDialog *GetParentDialog() CONST;
	class CEventBoxWnd *GetParentDisplay() CONST;

private:
	BOOL EnumNotifications();
	BOOL EnumRecipients();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxScheduleInfoDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxScheduleInfoDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowseProcedure();
	afx_msg void OnEditchangeComments();
	afx_msg void OnEditchangeProcedure();
	afx_msg void OnSelchangeNotification();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxScheduleDialog dialog

#define IDC_EVENTBOX_SCHEDULE_DETAILS   1001
#define IDC_EVENTBOX_SCHEDULE_MESSAGE_STATIC   1002
#define IDC_EVENTBOX_SCHEDULE_MESSAGE   1003
#define IDC_EVENTBOX_SCHEDULE_CHARACTERISTICS   1004
#define IDC_EVENTBOX_SCHEDULE_CATEGORY_STATIC   1005
#define IDC_EVENTBOX_SCHEDULE_CATEGORY   1006
#define IDC_EVENTBOX_SCHEDULE_TYPE_STATIC   1007
#define IDC_EVENTBOX_SCHEDULE_TYPE   1008
#define IDC_EVENTBOX_SCHEDULE_AUDITION_STATIC   1009
#define IDC_EVENTBOX_SCHEDULE_AUDITION   1010
#define IDC_EVENTBOX_SCHEDULE_COLOR_STATIC   1011
#define IDC_EVENTBOX_SCHEDULE_COLOR   1012
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE   1013
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME_STATIC   1014
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME   1015
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT   1016
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL_STATIC   1017
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL   1018
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP   1019
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME   1020
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME   1021
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES   1022
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES_STATIC   1023
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES   1024
#define IDC_EVENTBOX_SCHEDULE_OCCURRENCE_AUTOACKNOWLEDGE   1025
#define IDC_EVENTBOX_SCHEDULE_MORE   1026
#define IDC_EVENTBOX_SCHEDULE_HELP   1027

// Specify the eventbox schedule dialog related settings
#define EVENTBOXSCHEDULEDIALOG_MINIMUMINTERVAL   1
#define EVENTBOXSCHEDULEDIALOG_MAXIMUMINTERVAL   (365*SECONDSPERDAY)
#define EVENTBOXSCHEDULEDIALOG_DEFAULTINTERVAL   SECONDSPERHOUR
#define EVENTBOXSCHEDULEDIALOG_MINIMUMCYCLES   1
#define EVENTBOXSCHEDULEDIALOG_MAXIMUMCYCLES   100000
#define EVENTBOXSCHEDULEDIALOG_DEFAULTCYCLES   10

class CEventBoxScheduleDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxScheduleDialog)

	// Construction
public:
	CEventBoxScheduleDialog();   // standard constructor

	// Attributes
private:
	CEventObject  m_cEvent[2];

	// Dialog Data
	//{{AFX_DATA(CEventBoxScheduleDialog)
	enum { IDD = IDD_EVENTBOX_SCHEDULE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CEventObject *pEvent = NULL);

	VOID SetScheduleInfo(CONST CEventObject *pEvent);
	BOOL GetScheduleInfo(CEventObject *pEvent) CONST;

	class CEventBoxWatchDialog *GetParentDialog() CONST;
	class CEventBoxWnd *GetParentDisplay() CONST;

private:
	BOOL EnumCategories();
	BOOL EnumTypes();
	BOOL EnumAuditions();

	CString FindAudition(CONST CEventObject *pEvent) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxScheduleDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxScheduleDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRepeat();
	afx_msg void OnRepeatStop();
	afx_msg void OnRepeatStopByTime();
	afx_msg void OnRepeatStopByCycles();
	afx_msg void OnEditchangeMessage();
	afx_msg void OnEditchangeType();
	afx_msg void OnSelchangeCategory();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeColor();
	afx_msg void OnSelchangeAudition();
	afx_msg void OnSpinchangeTime();
	afx_msg void OnSpinchangeRepeatInterval();
	afx_msg void OnSpinchangeRepeatStopTime();
	afx_msg void OnSpinchangeRepeatStopCycles();
	afx_msg void OnAutoAcknowledge();
	afx_msg void OnMore();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxDetailsDialog dialog

#define IDC_EVENTBOX_ITEM_DETAILS   1001
#define IDC_EVENTBOX_ITEM_TEXT_STATIC   1002
#define IDC_EVENTBOX_ITEM_TEXT_MESSAGE   1003
#define IDC_EVENTBOX_ITEM_TEXT_COMMENTS   1004
#define IDC_EVENTBOX_ITEM_TEXT   1005
#define IDC_EVENTBOX_ITEM_CHARACTERISTICS   1006
#define IDC_EVENTBOX_ITEM_CATEGORY_STATIC   1007
#define IDC_EVENTBOX_ITEM_CATEGORY   1008
#define IDC_EVENTBOX_ITEM_TYPE_STATIC   1009
#define IDC_EVENTBOX_ITEM_TYPE   1010
#define IDC_EVENTBOX_ITEM_USER_STATIC   1011
#define IDC_EVENTBOX_ITEM_USER   1012
#define IDC_EVENTBOX_ITEM_AUDITION_STATIC   1013
#define IDC_EVENTBOX_ITEM_AUDITION   1014
#define IDC_EVENTBOX_ITEM_OCCURRENCE   1015
#define IDC_EVENTBOX_ITEM_OCCURRENCE_TIME_STATIC   1016
#define IDC_EVENTBOX_ITEM_OCCURRENCE_TIME   1017
#define IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATSTOP_TIME_STATIC   1018
#define IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATSTOP_TIME   1019
#define IDC_EVENTBOX_ITEM_OCCURRENCE_REPEAT_STATIC   1020
#define IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATINTERVAL   1021
#define IDC_EVENTBOX_ITEM_OCCURRENCE_NOREPETITION_STATIC   1022
#define IDC_EVENTBOX_ITEM_RECIPIENTS   1023
#define IDC_EVENTBOX_ITEM_RECIPIENTS_NOTIFICATION_STATIC   1024
#define IDC_EVENTBOX_ITEM_RECIPIENTS_NOTIFICATION   1025
#define IDC_EVENTBOX_ITEM_RECIPIENTS_LIST_STATIC   1026
#define IDC_EVENTBOX_ITEM_RECIPIENTS_LIST   1027
#define IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT_STATIC   1028
#define IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT   1029
#define IDC_EVENTBOX_ITEM_ACKNOWLEDGE   1030
#define IDC_EVENTBOX_ITEM_HELP   1031

class CEventBoxDetailsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxDetailsDialog)

	// Construction
public:
	CEventBoxDetailsDialog();   // standard constructor

	// Attributes
private:
	CEventObject  m_cEvent[2];

	// Dialog Data
	//{{AFX_DATA(CEventBoxDetailsDialog)
	enum { IDD = IDD_EVENTBOX_DETAILS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CEventObject *pEvent);

	VOID SetInfo(CONST CEventObject *pEvent);
	BOOL GetInfo(CEventObject *pEvent) CONST;

	class CEventBoxWatchDialog *GetParentDialog() CONST;
	class CEventBoxWnd *GetParentDisplay() CONST;

private:
	BOOL CheckPrivilege(UINT nPrivilege) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxDetailsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxDetailsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnMessageText();
	afx_msg void OnCommentsText();
	afx_msg void OnAcknowledge();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxWatchClockThread thread

// Specify the eventbox watch clock update interval
#define EVENTBOXWATCH_UPDATE_INTERVAL   500

class CEventBoxWatchClockThread : public CThread
{
	DECLARE_DYNCREATE(CEventBoxWatchClockThread)

	// Construction
public:

	// Attributes
private:
	CEventList  *m_pEventList;
	CFont  m_cFont;
private:
	CStringArray  m_szColumns;

	// Operations
public:
	BOOL Start(CDialog *pDlg, CONST CStringArray &szColumns, CEventList *pEventList);
	BOOL Stop();

private:
	VOID UpdateList(CDialog *pDlg, CEventList *pEventList);

	VOID DrawTime(CDialog *pDlg, CONST CTimeKey &tTime, INT nCount);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxWatchClockThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxWatchClockThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxWatchDialog dialog

#define IDC_EVENTBOX_WATCH_DETAILS   1001
#define IDC_EVENTBOX_WATCH_TIME_STATIC   1002
#define IDC_EVENTBOX_WATCH_TIME   1003
#define IDC_EVENTBOX_WATCH_COUNT_STATIC   1004
#define IDC_EVENTBOX_WATCH_COUNT   1005
#define IDC_EVENTBOX_WATCH_NEXTTIME_STATIC   1006
#define IDC_EVENTBOX_WATCH_NEXTTIME   1007
#define IDC_EVENTBOX_WATCH_REMAININGTIME_STATIC   1008
#define IDC_EVENTBOX_WATCH_REMAININGTIME   1009
#define IDC_EVENTBOX_WATCH_LIST_STATIC   1010
#define IDC_EVENTBOX_WATCH_LIST   1011
#define IDC_EVENTBOX_WATCH_LIST_DETAILS   1012
#define IDC_EVENTBOX_WATCH_LIST_CHANGE   1013
#define IDC_EVENTBOX_WATCH_LIST_REMOVE   1014
#define IDC_EVENTBOX_WATCH_LIST_REMOVEALL   1015
#define IDC_EVENTBOX_WATCH_HELP   1016

class CEventBoxWatchDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxWatchDialog)

	// Construction
public:
	CEventBoxWatchDialog();   // standard constructor

	// Attributes
private:
	CEventList  *m_pEventList[2];
private:
	CStringArray  m_szColumns;
private:
	CEventBoxWatchClockThread  m_cClockThread;

	// Dialog Data
	//{{AFX_DATA(CEventBoxWatchDialog)
	enum { IDD = IDD_EVENTBOX_WATCH_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CEventList *pEventList);

	BOOL SetScheduleInfo(CEventList *pEventList);
	BOOL GetScheduleInfo(CEventList *pEventList) CONST;

	class CEventBoxWnd *GetParent() CONST;

private:
	VOID DrawTime(CDC *pDC);

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	BOOL CheckPrivilege(UINT nPrivilege) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxWatchDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxWatchDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnDetails();
	afx_msg void OnChange();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxAcknowledgeDialog dialog

#define IDC_EVENTBOX_ACKNOWLEDGE_DETAILS   1001
#define IDC_EVENTBOX_ACKNOWLEDGE_LIST_STATIC   1002
#define IDC_EVENTBOX_ACKNOWLEDGE_LIST   1003
#define IDC_EVENTBOX_ACKNOWLEDGE_LISTUPDATE   1004
#define IDC_EVENTBOX_ACKNOWLEDGE_LISTREMOVE   1005
#define IDC_EVENTBOX_ACKNOWLEDGE_LISTREMOVEALL   1006
#define IDC_EVENTBOX_ACKNOWLEDGE_CHARACTERISTICS   1007
#define IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY   1008
#define IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_SYSTEM   1009
#define IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_SPACECRAFT   1010
#define IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_USER   1011
#define IDC_EVENTBOX_ACKNOWLEDGE_TYPE   1012
#define IDC_EVENTBOX_ACKNOWLEDGE_TYPE_ALL   1013
#define IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICT   1014
#define IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST   1015
#define IDC_EVENTBOX_ACKNOWLEDGE_USER   1016
#define IDC_EVENTBOX_ACKNOWLEDGE_USER_ALL   1017
#define IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICT   1018
#define IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST   1019
#define IDC_EVENTBOX_ACKNOWLEDGE_TIME   1020
#define IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT   1021
#define IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTARTTIME   1022
#define IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT_STATIC   1023
#define IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTOPTIME   1024
#define IDC_EVENTBOX_ACKNOWLEDGE_HELP   1025

// Specify the eventbox acknowledge dialog related categories
#define EVENTBOXACKNOWLEDGEDIALOG_SYSTEMCATEGORY   (1<<0)
#define EVENTBOXACKNOWLEDGEDIALOG_SPACECRAFTCATEGORY   (1<<1)
#define EVENTBOXACKNOWLEDGEDIALOG_USERCATEGORY   (1<<2)
// Specify the eventbox acknowledge dialog related settings
#define EVENTBOXACKNOWLEDGEDIALOG_DEFAULTINTERVAL   SECONDSPERHOUR

class CEventBoxAcknowledgeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxAcknowledgeDialog)

	// Construction
public:
	CEventBoxAcknowledgeDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nCategory;
	CString  m_szType;
	CString  m_szUser;
	CTimeKey  m_tTime[2];
	CPtrArray  m_pEvents;
	CEventList  *m_pEventList;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CEventBoxAcknowledgeDialog)
	enum { IDD = IDD_EVENTBOX_ACKNOWLEDGE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CEventList *pEventList);

	class CEventBoxWnd *GetParent() CONST;

private:
	BOOL UpdateList();

	BOOL EnumType(CONST CEventObject *pEvent);
	BOOL EnumUser(CONST CEventObject *pEvent);
	BOOL CheckEvent(CONST CEventObject *pEvent) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxAcknowledgeDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxAcknowledgeDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnListUpdate();
	afx_msg void OnListRemove();
	afx_msg void OnListRemoveAll();
	afx_msg void OnSystemCategory();
	afx_msg void OnSpacecraftCategory();
	afx_msg void OnUserCategory();
	afx_msg void OnTypeAll();
	afx_msg void OnUserAll();
	afx_msg void OnTypeRestriction();
	afx_msg void OnUserRestriction();
	afx_msg void OnTimeRestriction();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeUser();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxRetrieveDialog dialog

#define IDC_EVENTBOX_RETRIEVE_DETAILS   1001
#define IDC_EVENTBOX_RETRIEVE_COMPUTERNAME_STATIC   1002
#define IDC_EVENTBOX_RETRIEVE_COMPUTERNAME   1003
#define IDC_EVENTBOX_RETRIEVE_SPACECRAFTNAME_STATIC   1004
#define IDC_EVENTBOX_RETRIEVE_SPACECRAFTNAME   1005
#define IDC_EVENTBOX_RETRIEVE_USERNAME_STATIC   1006
#define IDC_EVENTBOX_RETRIEVE_USERNAME   1007
#define IDC_EVENTBOX_RETRIEVE_REALTIME   1008
#define IDC_EVENTBOX_RETRIEVE_HISTORY   1009
#define IDC_EVENTBOX_RETRIEVE_HISTORY_START_STATIC   1010
#define IDC_EVENTBOX_RETRIEVE_HISTORY_STARTTIME   1011
#define IDC_EVENTBOX_RETRIEVE_HISTORY_STOP_STATIC   1012
#define IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME   1013
#define IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME   1014
#define IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEVENTS   1015
#define IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS_STATIC   1016
#define IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS   1017
#define IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEND   1018
#define IDC_EVENTBOX_RETRIEVE_HISTORY_PLAYBACKMODE   1019
#define IDC_EVENTBOX_RETRIEVE_HISTORY_ALLATONCE   1020
#define IDC_EVENTBOX_RETRIEVE_HISTORY_PSEUDOREALTIME   1021
#define IDC_EVENTBOX_RETRIEVE_HISTORY_MANUAL   1022
#define IDC_EVENTBOX_RETRIEVE_HELP   1023

// Specify the eventbox retrieve dialog related settings
#define EVENTBOXRETRIEVEDIALOG_MINIMUMEVENTS   1
#define EVENTBOXRETRIEVEDIALOG_MAXIMUMEVENTS   1000
#define EVENTBOXRETRIEVEDIALOG_DEFAULTEVENTS   50

class CEventBoxRetrieveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxRetrieveDialog)

	// Construction
public:
	CEventBoxRetrieveDialog();   // standard constructor

	// Attributes
private:
	CString  m_szComputerName;
	CString  m_szSpacecraftName;
	CString  m_szUserName;
	BOOL  m_bLocal;

	// Dialog Data
	//{{AFX_DATA(CEventBoxRetrieveDialog)
	enum { IDD = IDD_EVENTBOX_RETRIEVE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal);

	BOOL GetMode(UINT &nMode) CONST;
	BOOL GetLimit(UINT &nCount) CONST;
	BOOL GetStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetStopTime(CTimeKey &tTimeKey) CONST;

	class CEventBoxOpenDialog *GetParentDialog() CONST;
	class CEventBoxWnd *GetParentDisplay() CONST;

private:
	BOOL SetRetrieveInfo();
	BOOL GetRetrieveInfo(UINT &nMode, UINT &nCount, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxRetrieveDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxRetrieveDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRetrieveRealtime();
	afx_msg void OnRetrieveByTime();
	afx_msg void OnRetrieveByEvents();
	afx_msg void OnRetrieveByEnd();
	afx_msg void OnRetrieveAllAtOnce();
	afx_msg void OnRetrievePseudoRealtime();
	afx_msg void OnRetrieveManual();
	afx_msg void OnSpinchangeRetrieveStartTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchTimeDialog dialog

#define IDC_EVENTBOX_SEARCHTIME_TIME_STATIC   1001
#define IDC_EVENTBOX_SEARCHTIME_TIME   1002
#define IDC_EVENTBOX_SEARCHTIME_DIRECTION   1003
#define IDC_EVENTBOX_SEARCHTIME_DIRECTION_UP   1004
#define IDC_EVENTBOX_SEARCHTIME_DIRECTION_DOWN   1005
#define IDC_EVENTBOX_SEARCHTIME_ALL   1006
#define IDC_EVENTBOX_SEARCHTIME_MATCH   1007
#define IDC_EVENTBOX_SEARCHTIME_FIND   1008
#define IDC_EVENTBOX_SEARCHTIME_HELP   1009

class CEventBoxSearchTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxSearchTimeDialog)

	// Construction
public:
	CEventBoxSearchTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CEventBoxSearchTimeDialog)
	enum { IDD = IDD_EVENTBOX_SEARCHTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CEventBoxWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSearchTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxSearchTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchCategoryDialog dialog

#define IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY_STATIC   1001
#define IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY   1002
#define IDC_EVENTBOX_SEARCHCATEGORY_DIRECTION   1003
#define IDC_EVENTBOX_SEARCHCATEGORY_DIRECTION_UP   1004
#define IDC_EVENTBOX_SEARCHCATEGORY_DIRECTION_DOWN   1005
#define IDC_EVENTBOX_SEARCHCATEGORY_ALL   1006
#define IDC_EVENTBOX_SEARCHCATEGORY_FIND   1007
#define IDC_EVENTBOX_SEARCHCATEGORY_HELP   1008

class CEventBoxSearchCategoryDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxSearchCategoryDialog)

	// Construction
public:
	CEventBoxSearchCategoryDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CEventBoxSearchCategoryDialog)
	enum { IDD = IDD_EVENTBOX_SEARCHCATEGORY_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CEventBoxWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSearchCategoryDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxSearchCategoryDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindCategory();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchTypeDialog dialog

#define IDC_EVENTBOX_SEARCHTYPE_TYPE_STATIC   1001
#define IDC_EVENTBOX_SEARCHTYPE_TYPE   1002
#define IDC_EVENTBOX_SEARCHTYPE_DIRECTION   1003
#define IDC_EVENTBOX_SEARCHTYPE_DIRECTION_UP   1004
#define IDC_EVENTBOX_SEARCHTYPE_DIRECTION_DOWN   1005
#define IDC_EVENTBOX_SEARCHTYPE_ALL   1006
#define IDC_EVENTBOX_SEARCHTYPE_CASE   1007
#define IDC_EVENTBOX_SEARCHTYPE_FIND   1008
#define IDC_EVENTBOX_SEARCHTYPE_HELP   1009

class CEventBoxSearchTypeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxSearchTypeDialog)

	// Construction
public:
	CEventBoxSearchTypeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CEventBoxSearchTypeDialog)
	enum { IDD = IDD_EVENTBOX_SEARCHTYPE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CEventBoxWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSearchTypeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxSearchTypeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindType();
	afx_msg void OnEditchangeType();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchMessageDialog dialog

#define IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE_STATIC   1001
#define IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE   1002
#define IDC_EVENTBOX_SEARCHMESSAGE_DIRECTION   1003
#define IDC_EVENTBOX_SEARCHMESSAGE_DIRECTION_UP   1004
#define IDC_EVENTBOX_SEARCHMESSAGE_DIRECTION_DOWN   1005
#define IDC_EVENTBOX_SEARCHMESSAGE_ALL   1006
#define IDC_EVENTBOX_SEARCHMESSAGE_CASE   1007
#define IDC_EVENTBOX_SEARCHMESSAGE_WORD   1008
#define IDC_EVENTBOX_SEARCHMESSAGE_FIND   1009
#define IDC_EVENTBOX_SEARCHMESSAGE_HELP   1010

class CEventBoxSearchMessageDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxSearchMessageDialog)

	// Construction
public:
	CEventBoxSearchMessageDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szMessages;

	// Dialog Data
	//{{AFX_DATA(CEventBoxSearchMessageDialog)
	enum { IDD = IDD_EVENTBOX_SEARCHMESSAGE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CEventBoxWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSearchMessageDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxSearchMessageDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindMessage();
	afx_msg void OnSelchangeMessage();
	afx_msg void OnEditchangeMessage();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchCommentsDialog dialog

#define IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS_STATIC   1001
#define IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS   1002
#define IDC_EVENTBOX_SEARCHCOMMENTS_DIRECTION   1003
#define IDC_EVENTBOX_SEARCHCOMMENTS_DIRECTION_UP   1004
#define IDC_EVENTBOX_SEARCHCOMMENTS_DIRECTION_DOWN   1005
#define IDC_EVENTBOX_SEARCHCOMMENTS_ALL   1006
#define IDC_EVENTBOX_SEARCHCOMMENTS_CASE   1007
#define IDC_EVENTBOX_SEARCHCOMMENTS_WORD   1008
#define IDC_EVENTBOX_SEARCHCOMMENTS_FIND   1009
#define IDC_EVENTBOX_SEARCHCOMMENTS_HELP   1010

class CEventBoxSearchCommentsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxSearchCommentsDialog)

	// Construction
public:
	CEventBoxSearchCommentsDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szComments;

	// Dialog Data
	//{{AFX_DATA(CEventBoxSearchCommentsDialog)
	enum { IDD = IDD_EVENTBOX_SEARCHCOMMENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CEventBoxWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSearchCommentsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxSearchCommentsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindComments();
	afx_msg void OnSelchangeComments();
	afx_msg void OnEditchangeComments();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchRecipientsDialog dialog

#define IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT_STATIC   1001
#define IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT   1002
#define IDC_EVENTBOX_SEARCHRECIPIENTS_DIRECTION   1003
#define IDC_EVENTBOX_SEARCHRECIPIENTS_DIRECTION_UP   1004
#define IDC_EVENTBOX_SEARCHRECIPIENTS_DIRECTION_DOWN   1005
#define IDC_EVENTBOX_SEARCHRECIPIENTS_ALL   1006
#define IDC_EVENTBOX_SEARCHRECIPIENTS_FIND   1007
#define IDC_EVENTBOX_SEARCHRECIPIENTS_HELP   1008

class CEventBoxSearchRecipientsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxSearchRecipientsDialog)

	// Construction
public:
	CEventBoxSearchRecipientsDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szRecipients;

	// Dialog Data
	//{{AFX_DATA(CEventBoxSearchRecipientsDialog)
	enum { IDD = IDD_EVENTBOX_SEARCHRECIPIENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CEventBoxWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSearchRecipientsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxSearchRecipientsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindRecipient();
	afx_msg void OnSelchangeRecipient();
	afx_msg void OnEditchangeRecipient();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchUserDialog dialog

#define IDC_EVENTBOX_SEARCHUSER_USER_STATIC   1001
#define IDC_EVENTBOX_SEARCHUSER_USER   1002
#define IDC_EVENTBOX_SEARCHUSER_DIRECTION   1003
#define IDC_EVENTBOX_SEARCHUSER_DIRECTION_UP   1004
#define IDC_EVENTBOX_SEARCHUSER_DIRECTION_DOWN   1005
#define IDC_EVENTBOX_SEARCHUSER_ALL   1006
#define IDC_EVENTBOX_SEARCHUSER_FIND   1007
#define IDC_EVENTBOX_SEARCHUSER_HELP   1008

class CEventBoxSearchUserDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxSearchUserDialog)

	// Construction
public:
	CEventBoxSearchUserDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szUsers;

	// Dialog Data
	//{{AFX_DATA(CEventBoxSearchUserDialog)
	enum { IDD = IDD_EVENTBOX_SEARCHUSER_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CEventBoxWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxSearchUserDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventBoxSearchUserDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindUser();
	afx_msg void OnSelchangeUser();
	afx_msg void OnEditchangeUser();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxOpenDialog dialog

#define IDC_EVENTBOX_OPEN_DETAILS   1001
#define IDC_EVENTBOX_OPEN_COMPUTERNAME_STATIC   1002
#define IDC_EVENTBOX_OPEN_COMPUTERNAME   1003
#define IDC_EVENTBOX_OPEN_CONNECT   1004
#define IDC_EVENTBOX_OPEN_SPACECRAFTNAME_STATIC   1005
#define IDC_EVENTBOX_OPEN_SPACECRAFTNAME   1006
#define IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME   1007
#define IDC_EVENTBOX_OPEN_USERNAME_STATIC   1008
#define IDC_EVENTBOX_OPEN_USERNAME   1009
#define IDC_EVENTBOX_OPEN_SETTINGS   1010
#define IDC_EVENTBOX_OPEN_MODE   1011
#define IDC_EVENTBOX_OPEN_MODE_REALTIME   1012
#define IDC_EVENTBOX_OPEN_MODE_HISTORY   1013
#define IDC_EVENTBOX_OPEN_HELP   1014

class CEventBoxOpenDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CEventBoxOpenDialog)

	// Construction
public:
	CEventBoxOpenDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nFilterMode;
	UINT  m_nFilterLimit;
	UINT  m_nFilterCount;
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveLimit;
	UINT  m_nLayoutColumns;
	BOOL  m_bLayoutDefault;
	LOGFONT  m_fntLayoutTitle;
	LOGFONT  m_fntLayoutList;
	CTimeKey  m_tFilterStartTime;
	CTimeKey  m_tFilterStopTime;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CUIntArray  m_nFilterColors;
	CStringArray  m_szFilterTypes;
	CStringArray  m_szFilterSubtypes;
	CEventBoxPrintJobs  m_pPrintJobs;
private:
	CEventBoxSettingsDialog  m_dlgSettings;
	CEventBoxRetrieveDialog  m_dlgRetrievals;

	// Dialog Data
	//{{AFX_DATA(CEventBoxOpenDialog)
	enum { IDD = IDD_EVENTBOX_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	CString GetComputerName() CONST;
	CString GetSpacecraftName() CONST;
	CString GetUserName() CONST;
	BOOL UseGlobal() CONST;
	UINT GetMode() CONST;

	BOOL GetLayoutTitle(UINT &nColumns) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutListFont(LPLOGFONT pListFont) CONST;
	BOOL UseLayoutAsDefault() CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL GetFilterBehavior(UINT &nCount) CONST;
	BOOL GetFilterBehavior(CStringArray &szTypes, CStringArray &szSubtypes) CONST;
	BOOL GetFilterLimitation(UINT &nLimit) CONST;
	BOOL GetFilterLimitation(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL GetFilterColors(CUIntArray &nColors) CONST;
	BOOL IsFilteringModified() CONST;

	BOOL GetRetrieveMode(UINT &nMode) CONST;
	BOOL GetRetrieveLimit(UINT &nCount) CONST;
	BOOL GetRetrieveStartTime(CTimeKey &tTimeKey) CONST;
	BOOL GetRetrieveStopTime(CTimeKey &tTimeKey) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CEventBoxPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CEventBoxWnd *GetParent() CONST;

private:
	BOOL EnumComputers();
	BOOL EnumSpacecrafts();
	BOOL EnumUsers();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxOpenDialog)
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
	//{{AFX_MSG(CEventBoxOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeComputerName();
	afx_msg void OnSelchangeSpacecraftName();
	afx_msg void OnSelchangeUserName();
	afx_msg void OnEditchangeComputerName();
	afx_msg void OnConnectComputer();
	afx_msg void OnSettings();
	afx_msg void OnGlobalEventlog();
	afx_msg void OnRealtimeMode();
	afx_msg void OnHistoryMode();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventScheduleThread thread

// Specify the event schedule update interval
#define EVENTSCHEDULE_UPDATE_INTERVAL   500

class CEventScheduleThread : public CThread
{
	DECLARE_DYNCREATE(CEventScheduleThread)

	// Construction
public:

	// Attributes
private:
	HANDLE  m_hEvent;

	// Operations
public:
	BOOL Start(class CEventBoxWnd *pParentWnd, HANDLE hEvent);
	BOOL Stop();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventScheduleThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventScheduleThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventRetrieveThread thread

class CEventRetrieveThread : public CThread
{
	DECLARE_DYNCREATE(CEventRetrieveThread)

	// Construction
public:
	CEventRetrieveThread();

	// Attributes
private:
	UINT  m_nLogs;
	UINT  m_nMode;
	UINT  m_nLimit;
	LONG  *m_pbFlag;
	HANDLE  m_bRetrieve;
	CTimeKey  m_tStartTime;
	CTimeKey  m_tStopTime;
private:
	HANDLE  m_bInit;

	// Operations
public:
	BOOL Start(class CEventBoxWnd *pParentWnd, HANDLE bInit, UINT nLogs, UINT nMode, UINT nLimit, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieve);
	BOOL Stop();

private:
	VOID StartRetrieving(BOOL bManual = FALSE);
	VOID StopRetrieving(BOOL bManual = FALSE);

	EVENT_DESCRIPTOR RetrieveAllAtOnce(CEventList &cEventList);
	EVENT_DESCRIPTOR RetrievePseudoRealtime(CEventList &cEventList);
	EVENT_DESCRIPTOR RetrieveManual(CEventList &cEventList);

	UINT GetRetrieveMode() CONST;
	UINT GetRetrieveLogs() CONST;
	UINT GetRetrieveLimit() CONST;
	CTimeKey GetRetrieveStartTime() CONST;
	CTimeKey GetRetrieveStopTime() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventRetrieveThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventRetrieveThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventWatchThread thread

class CEventWatchThread : public CThread
{
	DECLARE_DYNCREATE(CEventWatchThread)

	// Construction
public:
	CEventWatchThread();

	// Attributes
private:
	UINT  m_nLogs;
private:
	HANDLE  m_bInit;

	// Operations
public:
	BOOL Start(class CEventBoxWnd *pParentWnd, HANDLE bInit, UINT nLogs);
	BOOL Stop();

	UINT GetWatchLogs() CONST;

private:
	INT StartWatching(LPHANDLE *phLogs);
	BOOL StopWatching(LPHANDLE hLogs);

	EVENT_DESCRIPTOR Watch(CEventList &cEventList);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventWatchThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventWatchThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventPrintThread thread

class CEventPrintThread : public CThread
{
	DECLARE_DYNCREATE(CEventPrintThread)

	// Construction
public:

	// Attributes
private:
	CEventBoxPrintJobs  m_pPrintJobs;
private:
	CEvent  m_cEvent;

	// Operations
public:
	BOOL Start(class CEventBoxWnd *pParentWnd);
	BOOL Stop();

	BOOL SetPrintJobs(CONST CEventBoxPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CEventBoxPrintJobs &pPrintJobs) CONST;

	BOOL Schedule();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventPrintThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventPrintThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxToolBar window

class CEventBoxToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CEventBoxToolBar)

	// Construction
public:
	CEventBoxToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CEventBoxToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxStatusBar window

class CEventBoxStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CEventBoxStatusBar)

	// Construction
public:
	CEventBoxStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CEventBoxWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CEventBoxStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxView window

// Specify the eventbox view timer related identifiers
#define EVENTBOXVIEW_SEARCH_TIMERID   100
#define EVENTBOXVIEW_SEARCH_TIMEOUT   0

class CEventBoxView : public CTextView
{
	DECLARE_DYNCREATE(CEventBoxView)

	// Construction
public:
	CEventBoxView();

	// Attributes
private:
	CPtrArray  m_pEvents;
	CString  m_szSearchItem;
	BOOL  m_bSortInverse;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle);

	BOOL SetTitle(UINT nColumns);
	BOOL SetTitle(UINT nColumns, CONST CUIntArray &nWidths);
	BOOL GetTitle(UINT &nColumns) CONST;
	BOOL GetTitle(UINT &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetTitle(CStringArray &szColumns) CONST;
	BOOL GetTitle(CStringArray &szColumns, CUIntArray &nWidths) CONST;

	INT AddItem(CEventObject *pEvent, BOOL bRedraw = TRUE);
	BOOL SetItem(INT nIndex, CEventObject *pEvent, BOOL bRedraw = TRUE);
	BOOL GetItem(INT nIndex, CEventObject *pEvent) CONST;
	BOOL DeleteItem(CEventObject *pEvent);

	INT FindItem(CONST CEventObject *pEvent) CONST;

	BOOL SetCurItem(CONST CEventObject *pEvent);
	INT GetCurItem(CEventObject *pEvent) CONST;

	BOOL AcknowledgeItem(CONST CEventObject *pEvent);

	VOID CopyItems(UINT nCode);
	BOOL SortItems(BOOL bInverse = FALSE);
	VOID RefreshItems(BOOL bSelect = TRUE);
	BOOL DeleteAllItems();

	class CEventBoxWnd *GetParent() CONST;

private:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(UINT nColumns, CStringArray &szColumns) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(UINT nColumns, CUIntArray &nWidths);

	CString ConstructText(CONST CEventObject *pEvent) CONST;
	CTextViewAttribute *ConstructAttribute(CONST CEventObject *pEvent, CTextViewAttribute *pAttribute) CONST;

	INT FindIndex(CONST CEventObject *pEvent, BOOL bInsert = FALSE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxView)
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
	//{{AFX_MSG(CEventBoxView)
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nEventID);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEventBoxWnd frame

// Specify the eventbox title items
#define EVENTBOX_TITLEITEM_TIME   (1<<0)
#define EVENTBOX_TITLEITEM_CATEGORY   (1<<1)
#define EVENTBOX_TITLEITEM_TYPE   (1<<2)
#define EVENTBOX_TITLEITEM_MESSAGE   (1<<3)
#define EVENTBOX_TITLEITEM_COMMENTS   (1<<4)
#define EVENTBOX_TITLEITEM_RECIPIENTS   (1<<5)
#define EVENTBOX_TITLEITEM_USER   (1<<6)
#ifndef RC_INVOKED
#define EVENTBOX_TITLEITEMS_DEFAULT   (EVENTBOX_TITLEITEM_TIME | EVENTBOX_TITLEITEM_CATEGORY | EVENTBOX_TITLEITEM_TYPE | EVENTBOX_TITLEITEM_MESSAGE)
#define EVENTBOX_TITLEITEMS_ALL   (EVENTBOX_TITLEITEMS_DEFAULT | EVENTBOX_TITLEITEM_COMMENTS | EVENTBOX_TITLEITEM_RECIPIENTS | EVENTBOX_TITLEITEM_USER)
#endif
// Specify the eventbox filter modes
#define EVENTBOX_FILTER_SYSTEM   (1<<0)
#define EVENTBOX_FILTER_SPACECRAFT   (1<<1)
#define EVENTBOX_FILTER_USER   (1<<2)
#define EVENTBOX_FILTER_LIMITBYTIME   (1<<3)
#define EVENTBOX_FILTER_LIMITBYEVENTS   (1<<4)
#define EVENTBOX_FILTER_AUTOEVENTS   (1<<5)
#define EVENTBOX_FILTER_LISTEVENTS   (1<<6)
#define EVENTBOX_FILTER_BRINGEVENTS   (1<<7)
#define EVENTBOX_FILTER_AUTOACKNOWLEDGE   (1<<8)
#define EVENTBOX_FILTER_NOTIFY   (1<<9)
#define EVENTBOX_FILTER_USESOUND   (1<<10)
// Specify the eventbox default filter settings
#ifndef RC_INVOKED
#define EVENTBOX_FILTER_DEFAULTMODE   (EVENTBOX_FILTER_SYSTEM | EVENTBOX_FILTER_SPACECRAFT | EVENTBOX_FILTER_USER | EVENTBOX_FILTER_LIMITBYEVENTS | EVENTBOX_FILTER_USESOUND)
#endif
#define EVENTBOX_FILTER_DEFAULTNOLIMIT   10000
#define EVENTBOX_FILTER_DEFAULTLIMIT   1000
// Specify the eventbox retrieval modes
#define EVENTBOX_RETRIEVE_STOPBYTIME   (1<<0)
#define EVENTBOX_RETRIEVE_STOPBYEVENTS   (1<<1)
#define EVENTBOX_RETRIEVE_STOPBYEND   (1<<2)
#define EVENTBOX_RETRIEVE_ALLATONCE   (1<<3)
#define EVENTBOX_RETRIEVE_PSEUDOREALTIME   (1<<4)
#define EVENTBOX_RETRIEVE_MANUAL   (1<<5)
// Specify the eventbox print modes
#define EVENTBOX_PRINT_ALL   (1<<0)
#define EVENTBOX_PRINT_FIRSTSIDE   (1<<1)
#define EVENTBOX_PRINT_LASTSIDE   (1<<2)
#define EVENTBOX_PRINT_DAILY   (1<<3)
#define EVENTBOX_PRINT_CLEARCOMMENTS   (1<<4)
#define EVENTBOX_PRINT_ATTIME   (1<<5)
#define EVENTBOX_PRINT_ATDAILYTIME   (1<<6)
#define EVENTBOX_PRINT_ATCOUNT   (1<<7)
#define EVENTBOX_PRINT_REPEATBYINTERVAL   (1<<8)
#define EVENTBOX_PRINT_REPEATSTOPBYCOUNT   (1<<9)
#define EVENTBOX_PRINT_REPEATSTOPBYTIME   (1<<10)
#define EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT   (1<<11)
#define EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME   (1<<12)
#define EVENTBOX_PRINT_ACTIVE   (1<<13)
// Specify the eventbox print fonts
#define EVENTBOX_PRINTFONT_TITLE   0
#define EVENTBOX_PRINTFONT_DETAILS  1
#define EVENTBOX_PRINTFONT_COMMENTS   2
#define EVENTBOX_PRINTFONT_LISTITEMSTITLE   3
#define EVENTBOX_PRINTFONT_LISTITEMS   4
#define EVENTBOX_PRINTFONT_FOOTER   5
#define EVENTBOX_PRINTFONT_NOTICE   6
#define EVENTBOX_PRINTFONT_LOGO   7
#define EVENTBOX_PRINTFONTS   8
// Specify the eventbox clipboard copy codes
#define EVENTBOX_CLIPBOARD_ALLEVENTS   (1<<0)
#define EVENTBOX_CLIPBOARD_SINGLEEVENT   (1<<1)
#define EVENTBOX_CLIPBOARD_UPTOEVENT   (1<<2)
#define EVENTBOX_CLIPBOARD_FROMEVENT   (1<<3)
// Specify the eventbox statusbar pane identifiers
#define ID_EVENTBOX_STATUSBAR_ITEMPANE   ID_SEPARATOR
#define ID_EVENTBOX_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_EVENTBOX_STATUSBAR_SYSTEMPANE   ID_STATUSBAR_PANE2
#define ID_EVENTBOX_STATUSBAR_SPACECRAFTPANE   ID_STATUSBAR_PANE3
#define ID_EVENTBOX_STATUSBAR_USERPANE   ID_STATUSBAR_PANE4

class CEventBoxWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CEventBoxWnd)

	// Construction
public:
	CEventBoxWnd();
	~CEventBoxWnd();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  nIndex;
		INT  nCount;
		INT  cbColumns;
		UINT  nColumns;
		LOGFONT  sFont[2];
		SCROLLINFO  sScrollInfo[2];
	} DATA, *PDATA, *LPDATA;
private:
	CEventBoxToolBar  m_wndToolBar;
	CEventBoxStatusBar  m_wndStatusBar;
	CEventBoxView  m_wndView;
private:
	CEventBoxOpenDialog  m_dlgOpen;
	CEventBoxWatchDialog  m_dlgWatch;
	CEventBoxDetailsDialog  m_dlgDetails;
	CEventBoxSettingsDialog  m_dlgSettings;
	CEventBoxScheduleDialog  m_dlgSchedule;
	CEventBoxRetrieveDialog  m_dlgRetrievals;
	CEventBoxAcknowledgeDialog  m_dlgAcknowledge;
	CEventBoxSearchTimeDialog  m_dlgSearchTime;
	CEventBoxSearchTypeDialog  m_dlgSearchType;
	CEventBoxSearchUserDialog  m_dlgSearchUser;
	CEventBoxSearchMessageDialog  m_dlgSearchMessage;
	CEventBoxSearchCategoryDialog  m_dlgSearchCategory;
	CEventBoxSearchCommentsDialog  m_dlgSearchComments;
	CEventBoxSearchRecipientsDialog  m_dlgSearchRecipients;
private:
	CEventScheduleThread  m_cScheduleThread;
	CEventRetrieveThread  m_cRetrieveThread;
	CEventWatchThread  m_cWatchThread;
	CEventPrintThread  m_cPrintThread;
private:
	CEventList  *m_pEventList;
	CEventLog  *m_pEventLog;
private:
	UINT  m_nFilterMode;
	UINT  m_nFilterLimit;
	UINT  m_nFilterCount;
	CTimeKey  m_tFilterStartTime;
	CTimeKey  m_tFilterStopTime;
	CUIntArray  m_nFilterColors;
	CStringArray  m_szFilterTypes;
	CStringArray  m_szFilterSubtypes;
private:
	LONG  m_bRetrieveFlag;
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveLimit;
	CEvent  m_cRetrieveManual;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
private:
	CEvent  m_cAlertStatus;
	HICON  m_hAlertIcon[2];

	// Operations
public:
	BOOL SetTitle(UINT nColumns);
	BOOL SetTitle(UINT nColumns, CONST CUIntArray &nWidths);
	BOOL GetTitle(UINT &nColumns) CONST;
	BOOL GetTitle(UINT &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetTitle(CStringArray &szColumns) CONST;
	BOOL GetTitle(CStringArray &szColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemsFont(CFont *pFont);
	BOOL SetItemsFont(CONST LOGFONT *plfFont);
	BOOL GetItemsFont(CFont *pFont) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont) CONST;

	BOOL ActivateAccount(BOOL bStart = TRUE);
	BOOL ActivateAccount(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal, UINT nMode);
	BOOL SetAccountName(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal);
	BOOL GetAccountName(CString &szComputerName, CString &szSpacecraftName, CString &szUserName, BOOL &bLocal) CONST;
	BOOL GetAccountName(CString &szComputerName, CString &szSpacecraftName, CString &szUserName) CONST;

	BOOL SetFilterMode(UINT nMode = EVENTBOX_FILTER_DEFAULTMODE);
	BOOL GetFilterMode(UINT &nMode) CONST;
	BOOL SetFilterBehavior(UINT nCount);
	BOOL SetFilterBehavior(CONST CStringArray &szTypes, CONST CStringArray &szSubtypes);
	BOOL GetFilterBehavior(UINT &nCount) CONST;
	BOOL GetFilterBehavior(CStringArray &szTypes, CStringArray &szSubtypes) CONST;
	BOOL SetFilterLimitation(UINT nLimit = EVENTBOX_FILTER_DEFAULTLIMIT);
	BOOL SetFilterLimitation(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetFilterLimitation(UINT &nLimit) CONST;
	BOOL GetFilterLimitation(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetFilterColors(CONST CUIntArray &nColors);
	BOOL GetFilterColors(CUIntArray &nColors) CONST;

	BOOL DoFilter(CONST CEventObject *pEvent) CONST;
	BOOL DoFilterBehavior(CEventObject *pEvent, UINT nFlag = EVENTBOX_FILTER_AUTOACKNOWLEDGE);
	BOOL DoFilterLimit(CEventObject *pEvent);
	BOOL DoFilterColor(CEventObject *pEvent);

	BOOL ShowEvent(UINT nFlags, LPCTSTR pszEvent, BOOL bAudition = TRUE);
	BOOL ShowEvent(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition = TRUE);
	BOOL ShowEvent(CEventObject *pEvent, BOOL bSelect = TRUE, BOOL bRedraw = TRUE);

	BOOL SetCurEvent(CONST CEventObject *pEvent = NULL);
	INT GetCurEvent(CEventObject *pEvent) CONST;

	BOOL ScheduleEvent(CEventObject *pEvent);

	BOOL AcknowledgeEvent(CEventObject *pEvent);
	BOOL AcknowledgeAllEvents();

	VOID DoEventNotification(CONST CEventObject *pEvent);

	VOID FlushAllEvents();
	BOOL CanFlushEvents() CONST;
	VOID CopyEvents(UINT nCode);
	VOID RefreshAllEvents(BOOL bSelect = TRUE);
	BOOL DeleteAllEvents(BOOL bAll = TRUE);

	INT GetEventCount(BOOL bAll = FALSE) CONST;

	BOOL StartRetrieveEvents(UINT nMode, UINT nLimit, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL StartRetrieveEvents();
	BOOL IsRetrievingEvents(BOOL bManual = FALSE) CONST;
	BOOL RetrieveMoreEvents();
	BOOL RetrieveAutoEvents();
	BOOL StopRetrieveEvents();
	BOOL SetRetrieveMode(UINT nMode = 0);
	BOOL GetRetrieveMode(UINT &nMode) CONST;
	UINT GetRetrieveMode() CONST;
	BOOL SetRetrieveLimit(UINT nLimit = 0);
	BOOL GetRetrieveLimit(UINT &nLimit) CONST;
	UINT GetRetrieveLimit() CONST;
	BOOL SetRetrieveStartTime(TIMEKEY tStartTime = 0);
	BOOL SetRetrieveStartTime(CONST CTimeKey &tStartTime);
	BOOL GetRetrieveStartTime(CTimeKey &tStartTime) CONST;
	CTimeKey GetRetrieveStartTime() CONST;
	BOOL SetRetrieveStopTime(TIMEKEY tStopTime = 0);
	BOOL SetRetrieveStopTime(CONST CTimeKey &tStopTime);
	BOOL GetRetrieveStopTime(CTimeKey &tStopTime) CONST;
	CTimeKey GetRetrieveStopTime() CONST;

	VOID ShowEventDetails(CEventObject *pEvent);

	VOID ShowSearchEventTimeDetails();
	VOID ShowSearchEventCategoryDetails();
	VOID ShowSearchEventTypeDetails();
	VOID ShowSearchEventMessageDetails();
	VOID ShowSearchEventCommentsDetails();
	VOID ShowSearchEventUserDetails();
	VOID ShowSearchEventRecipientsDetails();

	BOOL SearchEventByTime(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchEventByCategory(UINT nCategory, BOOL bDown, BOOL bAll);
	BOOL SearchEventByType(LPCTSTR pszType, BOOL bDown, BOOL bAll, BOOL bCase);
	BOOL SearchEventByMessage(LPCTSTR pszMessage, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL SearchEventByComments(LPCTSTR pszComments, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL SearchEventByUser(LPCTSTR pszUser, BOOL bDown, BOOL bAll);
	BOOL SearchEventByRecipient(LPCTSTR pszRecipient, BOOL bDown, BOOL bAll);

	BOOL SetPrintJobs(CONST CEventBoxPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CEventBoxPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CEventBoxPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	CEventBoxWnd *Find(UINT nMode, LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bGlobal) CONST;

	VOID DrawAlertIcon(BOOL bAlert, BOOL bParent = FALSE);

	CEventList *GetEventList() CONST;
	CEventLog *GetEventLog() CONST;

private:
	BOOL CreateToolBar();
	BOOL CreateStatusBar();
	BOOL CreateView();

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateItemPane();
	VOID UpdateModePane();
	VOID UpdateSystemPane();
	VOID UpdateSpacecraftPane();
	VOID UpdateUserPane();

	BOOL UpdateAlertStatus();
	BOOL UpdatePrintStatus();

	BOOL StartWatchEvents();
	BOOL IsWatchingEvents() CONST;
	BOOL StopWatchEvents();
	BOOL StartScheduleEvents();
	BOOL IsSchedulingEvents() CONST;
	BOOL StopScheduleEvents();
	BOOL StartSchedulePrintJobs();
	BOOL IsSchedulingPrintJobs() CONST;
	BOOL StopSchedulePrintJobs();

	BOOL SetScheduleInfo(CONST CByteArray &nScheduleInfo);
	BOOL GetScheduleInfo(CByteArray &nScheduleInfo) CONST;

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CEventBoxPrintJobInfo *pJobInfo, UINT &nColumns, CEventList &cEventList, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CEventBoxPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, UINT nColumns, CONST CEventList &cEventList, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CEventBoxPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, UINT nColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocDetails(CONST CEventBoxPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocComments(CONST CEventBoxPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocListItemsTitle(UINT nColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, UINT nColumns, CONST CEventList &cEventList, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocItemsTitleWidth(CDC &cDC, LPCTSTR pszItem, CFont *pTitleFont) CONST;
	INT CalcPrintDocItemsTitleWidth(CDC &cDC, CONST RECT &rArea, UINT nColumns, CONST CEventList &cEventList, CFont *pTitleFont, CFont *pItemsFont, BOOL bDefault, CUIntArray &nTabs, INT &nIndent) CONST;
	INT CalcPrintDocTimeItemWidth(CDC &cDC, CFont *pItemsFont) CONST;
	INT CalcPrintDocCategoryItemWidth(CDC &cDC, CFont *pItemsFont) CONST;
	INT CalcPrintDocTypeItemWidth(CDC &cDC, CONST CEventList &cEventList, CFont *pItemsFont) CONST;
	INT CalcPrintDocMessageItemWidth(CDC &cDC, CFont *pItemsFont) CONST;
	INT CalcPrintDocCommentsItemWidth(CDC &cDC, CFont *pItemsFont) CONST;
	INT CalcPrintDocRecipientsItemWidth(CDC &cDC, CONST CEventList &cEventList, CFont *pItemsFont) CONST;
	INT CalcPrintDocUserItemWidth(CDC &cDC, CONST CEventList &cEventList, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

private:
	BOOL SetLayoutInfo(UINT nColumns, CONST CUIntArray &nWidths, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	BOOL GetLayoutInfo(UINT &nColumns, CUIntArray &nWidths, LOGFONT *pTitleFont, LOGFONT *pItemsFont, INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;

	BOOL LoadAlertIcons();
	VOID FreeAlertIcons();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventBoxWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Check() CONST;
	virtual VOID Update();
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
	BOOL OnCloseScheduleDialog(UINT nCode);
	BOOL OnCloseWatchDialog(UINT nCode);
	BOOL OnCloseRetrieveDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CEventBoxWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettings();
	afx_msg void OnSchedule();
	afx_msg void OnWatch();
	afx_msg void OnDetails();
	afx_msg void OnAcknowledge();
	afx_msg void OnClearAll();
	afx_msg void OnRetrievals();
	afx_msg void OnRetrieveManualForward();
	afx_msg void OnPrint();
	afx_msg void OnCopyAllEvents();
	afx_msg void OnCopySingleEvent();
	afx_msg void OnCopyUpToEvent();
	afx_msg void OnCopyFromEvent();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSchedule(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWatch(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDetails(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAcknowledge(CCmdUI *pCmdUI);
	afx_msg void OnUpdateClearAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrievals(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveManualForward(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCopyAllEvents(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCopySingleEvent(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCopyUpToEvent(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCopyFromEvent(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarItemPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarModePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarSystemPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarSpacecraftPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarUserPane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __EVENTBOX_H__
