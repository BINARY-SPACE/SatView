// MMD.H : Mimics Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics display related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/25 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MMD_H__
#define __MMD_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CMMDPrintJobInfo

class CMMDPrintJobInfo : public CObject
{
	// Construction
public:
	CMMDPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbEvent;
		INT  cbProfile;
		INT  cbComments;
		UINT  nPrintMode;
		UINT  nPrintScale;
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
	UINT  m_nPrintScale;
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
	BOOL SetPrintScale(UINT nScale);
	BOOL GetPrintScale(UINT &nScale) CONST;
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

	VOID Copy(CONST CMMDPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CMMDPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDPrintJobs

class CMMDPrintJobs : public CPtrArray
{
	// Construction
public:
	CMMDPrintJobs();
	~CMMDPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CMMDPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CMMDPrintJobInfo *GetAt(INT nIndex) CONST;
	CMMDPrintJobInfo *operator[](INT nIndex) CONST;

	TIMEKEY Schedule();

	VOID RemoveAll();

	BOOL Copy(CONST CMMDPrintJobs *pPrintJobs);
	BOOL Compare(CONST CMMDPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsLayoutPage dialog

#define IDC_MMDSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_STATIC   1003
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_DEFAULT   1004
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED   1005
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X   1006
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_STATIC   1007
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_Y   1008
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_UNITS   1009
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_STATIC   1010
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT_STATIC   1011
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT   1012
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP_STATIC   1013
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP   1014
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP_PIXELS   1015
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_RIGHT_STATIC   1016
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_RIGHT   1017
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM_STATIC   1018
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM   1019
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM_PIXELS   1020
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BACKGROUND_STATIC   1021
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BACKGROUND   1022
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_STATIC   1023
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS   1024
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES   1025
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL_STATIC   1026
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL   1027
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL_UNITS   1028
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL_STATIC   1029
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL   1030
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL_UNITS   1031
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR_STATIC   1032
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR   1033
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SHOW   1034
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA   1035
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA   1036
#define IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS   1037
#define IDC_MMDSETTINGS_LAYOUTPAGE_SOURCECODE_CONTENTS   1038

// Specify the mimics display settings layout page default values
#define MMDSETTINGSLAYOUTPAGE_DEFAULT_IMAGEWIDTH   450
#define MMDSETTINGSLAYOUTPAGE_DEFAULT_IMAGEHEIGHT   300
#define MMDSETTINGSLAYOUTPAGE_DEFAULT_GRIDINTERVAL   50

class CMMDSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMMDSettingsLayoutPage)

	// Construction
public:
	CMMDSettingsLayoutPage();

	// Attributes
private:
	INT  m_nImage[2][4];
	CSize  m_sizeGrid[2];
	CSize  m_sizeImage[2];
	COLORREF  m_nImageGrid[2];
	COLORREF  m_nImageBkgnd[2];
	BOOL  m_bUsedGrid[2];
	BOOL  m_bInvalidData[2];
	BOOL  m_bBadData[2];
	BOOL  m_bToolTips[2];
private:
	CFont  m_cCodeFont;
private:
	CMMDLayout  m_cLayout;

	// Dialog Data
	//{{AFX_DATA(CMMDSettingsLayoutPage)
	enum { IDD = IDD_MMD_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CMMDLayout &cLayout) CONST;

	BOOL GetInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetBadDataMode(BOOL &bEnable) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CMMDSettingsDialog *GetParentDialog() CONST;
	class CMMDWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

private:
	static DWORD CALLBACK SetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMMDSettingsLayoutPage)
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
	//{{AFX_MSG(CMMDSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDefaultSize();
	afx_msg void OnFixedSize();
	afx_msg void OnGridPoints();
	afx_msg void OnGridLines();
	afx_msg void OnInvalidData();
	afx_msg void OnBadData();
	afx_msg void OnToolTips();
	afx_msg void OnSelchangeBackgroundColor();
	afx_msg void OnSelchangeGridColor();
	afx_msg void OnSpinchangeHorizontalSize();
	afx_msg void OnSpinchangeVerticalSize();
	afx_msg void OnSpinchangeLeftMargin();
	afx_msg void OnSpinchangeRightMargin();
	afx_msg void OnSpinchangeTopMargin();
	afx_msg void OnSpinchangeBottomMargin();
	afx_msg void OnSpinchangeHorizontalGridInterval();
	afx_msg void OnSpinchangeVerticalGridInterval();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsRetrievingPage dialog

#define IDC_MMDSETTINGS_RETRIEVINGPAGE_DETAILS   1001
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC   1002
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE   1003
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_INSPECT   1004
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO   1005
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS   1006
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC   1007
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT   1008
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC   1009
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY   1010
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC   1011
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT   1012
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC   1013
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE   1014
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC   1015
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME   1016
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO   1017
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME   1018
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC   1019
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME   1020
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC   1021
#define IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE   1022

class CMMDSettingsRetrievingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMMDSettingsRetrievingPage)

	// Construction
public:
	CMMDSettingsRetrievingPage();

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CMMDSettingsRetrievingPage)
	enum { IDD = IDD_MMD_SETTINGS_RETRIEVINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetDataSourceFileName(CString &szFileName) CONST;

	class CMMDSettingsDialog *GetParentDialog() CONST;
	class CMMDWnd *GetParentDisplay() CONST;

private:
	VOID EnumDataSources();
	VOID ShowDataSourceInfo();

	BOOL CheckDataSource(LPCTSTR pszFileName) CONST;
	BOOL CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST;

	CString FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMMDSettingsRetrievingPage)
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
	//{{AFX_MSG(CMMDSettingsRetrievingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnInspect();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeFileName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsPrintingComments window

class CMMDSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CMMDSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsPrintingPage dialog

#define IDC_MMDSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_MMDSETTINGS_PRINTINGPAGE_NAME_STATIC   1002
#define IDC_MMDSETTINGS_PRINTINGPAGE_NAME   1003
#define IDC_MMDSETTINGS_PRINTINGPAGE_ADDNAME   1004
#define IDC_MMDSETTINGS_PRINTINGPAGE_REMOVENAME   1005
#define IDC_MMDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES   1006
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES   1007
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC   1008
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE   1009
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS   1010
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT_STATIC   1011
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT   1012
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL   1013
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS   1014
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT   1015
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE   1016
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE   1017
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_STATIC   1018
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER   1019
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS   1020
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC   1021
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT   1022
#define IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS   1023

// Specify the mimics display settings printing page related limits
#define MMDSETTINGSPRINTINGPAGE_MINIMUMSCALE   1
#define MMDSETTINGSPRINTINGPAGE_MAXIMUMSCALE   100
#define MMDSETTINGSPRINTINGPAGE_DEFAULTSCALE   100

class CMMDSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMMDSettingsPrintingPage)

	// Construction
public:
	CMMDSettingsPrintingPage();

	// Attributes
private:
	CMMDPrintJobs  m_pJobs[2];
private:
	CMMDSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CMMDSettingsPrintingPage)
	enum { IDD = IDD_MMD_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CMMDPrintJobs &pJobs) CONST;

	class CMMDSettingsDialog *GetParentDialog() CONST;
	class CMMDWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CMMDPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMMDSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CMMDPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMMDSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnAddName();
	afx_msg void OnRemoveName();
	afx_msg void OnRemoveAllNames();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnPrintUnderlineOOL();
	afx_msg void OnPrintNoColors();
	afx_msg void OnPrintAutomaticScale();
	afx_msg void OnPrintFixedScale();
	afx_msg void OnSelchangePrintAdjustment();
	afx_msg void OnSpinchangePrintFixedScale();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsPrintJobsPage dialog

#define IDC_MMDSETTINGS_PRINTJOBSPAGE_DETAILS   1001
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC   1002
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS   1003
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB   1004
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC   1005
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS   1006
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_REMOVEJOB   1007
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR   1008
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME   1009
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME   1010
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME   1011
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC   1012
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME   1013
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT   1014
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT   1015
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC   1016
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION   1017
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC   1018
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE   1019
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME  1020
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC   1021
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME   1022
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC   1023
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES   1024
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC   1025
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES   1026
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME   1027
#define IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME   1028

// Specify the mimics display settings print jobs page related repetition types
#define MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY   1
#define MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY   2
// Specify the mimics display settings print jobs page related limits
#define MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL   1
#define MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL   MINUTESPERHOUR
#define MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES   1
#define MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES   10000
#define MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES   10

class CMMDSettingsPrintJobsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMMDSettingsPrintJobsPage)

	// Construction
public:
	CMMDSettingsPrintJobsPage();

	// Attributes
private:
	CMMDPrintJobs  m_pJobs[2];

	// Dialog Data
	//{{AFX_DATA(CMMDSettingsPrintJobsPage)
	enum { IDD = IDD_MMD_SETTINGS_PRINTJOBSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CMMDPrintJobs &pJobs) CONST;

	class CMMDSettingsDialog *GetParentDialog() CONST;
	class CMMDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumJobs();
	BOOL EnumEvents();

	VOID ShowJobInfo();
	BOOL CheckJobInfo() CONST;
	CMMDPrintJobInfo *FindJobInfo(BOOL bActive = FALSE) CONST;

	VOID SetJobRepetitionInfo();
	UINT GetJobRepetitionType() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMMDSettingsPrintJobsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CMMDPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMMDSettingsPrintJobsPage)
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
// CMMDSettingsTabCtrl window

class CMMDSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CMMDSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsDialog

class CMMDSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CMMDSettingsDialog)

	// Construction
public:
	CMMDSettingsDialog();

	// Attributes
private:
	CMMDSettingsTabCtrl  m_wndTabCtrl;
	CMMDSettingsLayoutPage  m_pageLayout;
	CMMDSettingsRetrievingPage  m_pageRetrieving;
	CMMDSettingsPrintingPage  m_pagePrinting;
	CMMDSettingsPrintJobsPage  m_pagePrintJobs;

	// Operations
public:
	BOOL GetLayout(CMMDLayout &cLayout) CONST;
	BOOL GetLayoutInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CMMDPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CMMDOpenDialog *GetParentDialog() CONST;
	class CMMDWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDSettingsDialog)
public:
	virtual BOOL OnDataExchange(HWND hPage, CONST CMMDPrintJobs &pJobs);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDSettingsDialog)
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
// CMMDLinkagesDialog dialog

#define IDC_MMD_LINKAGES_DETAILS   1001
#define IDC_MMD_LINKAGES_NAME_STATIC   1002
#define IDC_MMD_LINKAGES_NAME   1003
#define IDC_MMD_LINKAGES_DISPLAYS_STATIC  1004
#define IDC_MMD_LINKAGES_DISPLAYS   1005
#define IDC_MMD_LINKAGES_LIST_STATIC   1006
#define IDC_MMD_LINKAGES_LIST   1007
#define IDC_MMD_LINKAGES_ADD   1008
#define IDC_MMD_LINKAGES_REMOVE   1009
#define IDC_MMD_LINKAGES_REMOVEALL   1010
#define IDC_MMD_LINKAGES_HELP   1011

class CMMDLinkagesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDLinkagesDialog)

	// Construction
public:
	CMMDLinkagesDialog();   // standard constructor

	// Attributes
private:
	CPtrArray  m_pDisplays[3];

	// Dialog Data
	//{{AFX_DATA(CMMDLinkagesDialog)
	enum { IDD = IDD_MMD_LINKAGES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CMMDWnd *GetParent() CONST;

private:
	BOOL EnumDisplays();

	INT FindDisplay(LPCTSTR pszName, BOOL bLinked = FALSE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDLinkagesDialog)
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
	//{{AFX_MSG(CMMDLinkagesDialog)
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
// CMMDRetrieveDialog dialog

#define IDC_MMD_RETRIEVE_DETAILS   1001
#define IDC_MMD_RETRIEVE_TITLE_STATIC   1002
#define IDC_MMD_RETRIEVE_TITLE   1003
#define IDC_MMD_RETRIEVE_TYPE_STATIC   1004
#define IDC_MMD_RETRIEVE_TYPE   1005
#define IDC_MMD_RETRIEVE_REALTIME   1006
#define IDC_MMD_RETRIEVE_HISTORY   1007
#define IDC_MMD_RETRIEVE_HISTORY_START_STATIC   1008
#define IDC_MMD_RETRIEVE_HISTORY_STARTTIME   1009
#define IDC_MMD_RETRIEVE_HISTORY_EXACTTIME   1010
#define IDC_MMD_RETRIEVE_HISTORY_STOP_STATIC   1011
#define IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME   1012
#define IDC_MMD_RETRIEVE_HISTORY_STOPTIME   1013
#define IDC_MMD_RETRIEVE_HISTORY_STOPBYEND   1014
#define IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME   1015
#define IDC_MMD_RETRIEVE_HISTORY_PLAYBACKMODE   1016
#define IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC   1017
#define IDC_MMD_RETRIEVE_HISTORY_PSEUDOREALTIME   1018
#define IDC_MMD_RETRIEVE_HISTORY_MANUAL   1019
#define IDC_MMD_RETRIEVE_HISTORY_SPEED_STATIC   1020
#define IDC_MMD_RETRIEVE_HISTORY_SPEED   1021
#define IDC_MMD_RETRIEVE_HISTORY_SLOW   1022
#define IDC_MMD_RETRIEVE_HISTORY_FAST   1023
#define IDC_MMD_RETRIEVE_HISTORY_INTERVAL   1024
#define IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME   1025
#define IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME_STATIC   1026
#define IDC_MMD_RETRIEVE_HELP   1027

// Specify the mimics display retrieve dialog related limits
#define MMDRETRIEVEDIALOG_MINIMUMINTERVAL   1
#define MMDRETRIEVEDIALOG_MAXIMUMINTERVAL   MINUTESPERWEEK
#define MMDRETRIEVEDIALOG_DEFAULTINTERVAL   5

class CMMDRetrieveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDRetrieveDialog)

	// Construction
public:
	CMMDRetrieveDialog();   // standard constructor

	// Attributes
private:
	CString  m_szTitle;
	CString  m_szType;

	// Dialog Data
	//{{AFX_DATA(CMMDRetrieveDialog)
	enum { IDD = IDD_MMD_RETRIEVE_DIALOG };
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

	class CMMDOpenDialog *GetParentDialog() CONST;
	class CMMDWnd *GetParentDisplay() CONST;

private:
	BOOL SetRetrieveInfo();
	BOOL GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDRetrieveDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDRetrieveDialog)
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
// CMMDFindDialog dialog

#define IDC_MMD_FIND_KEY_STATIC   1001
#define IDC_MMD_FIND_KEY   1002
#define IDC_MMD_FIND_VALUE_STATIC   1003
#define IDC_MMD_FIND_VALUE   1004
#define IDC_MMD_FIND_RESULTS_STATIC   1005
#define IDC_MMD_FIND_RESULTS   1006
#define IDC_MMD_FIND_SEARCH   1007
#define IDC_MMD_FIND_OPEN   1008
#define IDC_MMD_FIND_HELP   1009

class CMMDFindDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDFindDialog)

	// Construction
public:
	CMMDFindDialog();   // standard constructor

	// Attributes
private:
	CMMDLayouts  m_pLayouts[2];
	CStringArray  m_szDescriptions;

	// Dialog Data
	//{{AFX_DATA(CMMDFindDialog)
	enum { IDD = IDD_MMD_FIND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CMMDLayout &cLayout);

	class CMMDWnd *GetParent() CONST;

private:
	BOOL EnumSearchKeys();
	BOOL EnumSearchValues();

	VOID DoFindByDescription(LPCTSTR pszDescription);
	VOID DoFindByDescriptions(CONST CStringArray &szDescriptions);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDFindDialog)
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
// CMMDOpenDialog dialog

#define IDC_MMD_OPEN_DETAILS   1001
#define IDC_MMD_OPEN_DISPLAY_STATIC   1002
#define IDC_MMD_OPEN_DISPLAY   1003
#define IDC_MMD_OPEN_SETTINGS   1004
#define IDC_MMD_OPEN_FIND   1005
#define IDC_MMD_OPEN_TYPE   1006
#define IDC_MMD_OPEN_TYPE_NORMAL   1007
#define IDC_MMD_OPEN_MODE   1008
#define IDC_MMD_OPEN_MODE_REALTIME   1009
#define IDC_MMD_OPEN_MODE_HISTORY   1010
#define IDC_MMD_OPEN_HELP   1011

class CMMDOpenDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CMMDOpenDialog)

	// Construction
public:
	CMMDOpenDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	BOOL  m_bLayoutBadData;
	BOOL  m_bLayoutToolTips;
	BOOL  m_bLayoutInvalidData;
	CString  m_szRetrieveFileName;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CTimeSpan  m_tRetrieveInterval;
	CMMDPrintJobs  m_pPrintJobs;
	CMMDLayout  m_cLayout;
private:
	CMMDSettingsDialog  m_dlgSettings;
	CMMDRetrieveDialog  m_dlgRetrievals;
	CMMDFindDialog  m_dlgFindDisplay;

	// Dialog Data
	//{{AFX_DATA(CMMDOpenDialog)
	enum { IDD = IDD_MMD_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	CString GetTitle() CONST;
	UINT GetType() CONST;
	UINT GetMode() CONST;

	BOOL GetLayout(CMMDLayout &cLayout) CONST;
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

	BOOL GetPrintJobs(CMMDPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CMMDWnd *GetParent() CONST;

private:
	VOID EnumLayouts();

	BOOL FindLayout() CONST;
	BOOL FindLayout(CMMDLayout &cLayout) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDOpenDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseSettingsDialog(UINT nCode);
	BOOL OnCloseRetrieveDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSettings();
	afx_msg void OnFind();
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
// CMMDRetrieveThread thread

// Specify the mimics display retrieve thread action codes
#define MMDRETRIEVETHREAD_ACTION_STOP   0
#define MMDRETRIEVETHREAD_ACTION_AUTOFORWARD   1
#define MMDRETRIEVETHREAD_ACTION_AUTOBACKWARD   2
#define MMDRETRIEVETHREAD_ACTION_MANUALFORWARD   3
#define MMDRETRIEVETHREAD_ACTION_MANUALBACKWARD   4
#define MMDRETRIEVETHREAD_ACTION_PSEUDOREALTIME   5
#define MMDRETRIEVETHREAD_ACTION_TYPES   6

class CMMDRetrieveThread : public CThread
{
	DECLARE_DYNCREATE(CMMDRetrieveThread)

	// Construction
public:
	CMMDRetrieveThread();

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
	HANDLE  m_hAction[MMDRETRIEVETHREAD_ACTION_TYPES];
private:
	CHistoryTMProcessEngine  m_cTMProcessEngine;
	CTMEnvironment  m_cTMEnvironment;

	// Operations
public:
	BOOL Start(class CMMDWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime);
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
	//{{AFX_VIRTUAL(CMMDRetrieveThread)
public:
	virtual BOOL InitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDRetrieveThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDPrintThread thread

class CMMDPrintThread : public CThread
{
	DECLARE_DYNCREATE(CMMDPrintThread)

	// Construction
public:

	// Attributes
private:
	CMMDPrintJobs  m_pPrintJobs;
private:
	CEvent  m_cEvent;

	// Operations
public:
	BOOL Start(class CMMDWnd *pParentWnd);
	BOOL Stop();

	BOOL SetPrintJobs(CONST CMMDPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CMMDPrintJobs &pPrintJobs) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDPrintThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDPrintThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDDocument document

class CMMDDocument : public COleDocument
{
	DECLARE_DYNCREATE(CMMDDocument)

	// Construction
public:
	CMMDDocument();
	virtual ~CMMDDocument();

	// Attributes
private:
	BOOL  m_bAutoClose;

	// Operations
public:
	INT EnumItems(CPtrArray &pItems) CONST;

	POSITION FindItem(CMimicsClientItem *pItem) CONST;

	UINT GetItemCount() CONST;

	BOOL Copy(CONST CMMDDocument *pDocument);
	BOOL Compare(CONST CMMDDocument *pDocument) CONST;

	BOOL Map(CMMDLayout &cLayout) CONST;
	BOOL Unmap(CONST CMMDLayout &cLayout);

private:
	BOOL EnumItemsInList(CONST CMMDDocument *pDocument, CPtrArray &pItems) CONST;

	POSITION FindItemInList(CONST CMMDDocument *pDocument, CMimicsClientItem *pItem) CONST;
	CONST CMMDDocument *FindPositionInList(CONST CMMDDocument *pDocument, POSITION lPosition) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDDocument)
public:
	virtual POSITION GetStartPosition() CONST;
	virtual POSITION GetStopPosition() CONST;
	virtual CDocItem *GetNextItem(POSITION &lPosition) CONST;
	virtual CDocItem *GetPreviousItem(POSITION &lPosition) CONST;
	virtual void Serialize(CArchive &ar);   // overridden for document i/o
	virtual BOOL SaveModified();
	virtual BOOL OnNewDocument();
	virtual void OnCloseDocument();
	virtual BOOL CanCloseFrame(CFrameWnd *pFrame);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDDocument)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsItemDispatchDriver wrapper class

class CMimicsItemDispatchDriver : public COleDispatchDriver
{
	// Construction
public:
	CMimicsItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsItemDispatchDriver(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CMimicsItemDispatchDriver(const CMimicsItemDispatchDriver &cDispatchSource) : COleDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetType(LPCTSTR pszType);
	CString GetType() CONST;
	VOID SetToolTipText(LPCTSTR pszText);
	CString GetToolTipText() CONST;
	VOID SetInitialSize(CONST SIZE &size);
	CSize GetInitialSize() CONST;

	VOID Show();
	VOID Hide();
	BOOL IsVisible() CONST;
	BOOL Blink(INT nInterval);

	VOID Draw(HDC hDC, CONST RECT *pRect, CONST XFORM *pxForm, BOOL bShape = FALSE);

protected:
	COleDispatchDriver *GetDispatchDriver() CONST;
	DISPID GetDispatchID(OLECHAR FAR *pszMethod) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineItemDispatchDriver wrapper class

class CMimicsLineItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsLineItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsLineItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsLineItemDispatchDriver(const CMimicsLineItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID Arrow(BOOL bEnable);
	VOID DoubleArrow(BOOL bEnable);
	VOID Cross(BOOL bEnable);
	BOOL SetCrossPt(double fPt);
	BOOL GetCrossPt(double *fPt) CONST;
	BOOL IsArrow() CONST;
	BOOL IsDoubleArrow() CONST;
	BOOL IsCross() CONST;
	VOID SetColor(COLORREF nColor);
	COLORREF GetColor() CONST;
	VOID SetThickness(INT nWidth);
	INT GetThickness() CONST;
	VOID Solid();
	VOID Dash();
	VOID Dot();
	VOID DashDot();
	VOID DashDotDot();
	BOOL IsSolid() CONST;
	BOOL IsDashed() CONST;
	BOOL IsDotted() CONST;
	BOOL IsDashDotted() CONST;
	BOOL IsDashDotDotted() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItemDispatchDriver wrapper class

class CMimicsRectangleItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsRectangleItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsRectangleItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsRectangleItemDispatchDriver(const CMimicsRectangleItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch, COLORREF nColor);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItemDispatchDriver wrapper class

class CMimicsEllipseItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsEllipseItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsEllipseItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsEllipseItemDispatchDriver(const CMimicsEllipseItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch, COLORREF nColor);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcItemDispatchDriver wrapper class

class CMimicsArcItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsArcItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsArcItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsArcItemDispatchDriver(const CMimicsArcItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch, COLORREF nColor);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;
	VOID SetRadials(double fRadial1, double fRadial2);
	VOID GetRadials(double &fRadial1, double &fRadial2) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItemDispatchDriver wrapper class

class CMimicsTriangleItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsTriangleItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsTriangleItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsTriangleItemDispatchDriver(const CMimicsTriangleItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch, COLORREF nColor);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;
	VOID SetEdges(double x1, double y1, double x2, double y2, double x3, double y3);
	VOID GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItemDispatchDriver wrapper class

class CMimicsSwitchItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsSwitchItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsSwitchItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsSwitchItemDispatchDriver(const CMimicsSwitchItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID SetColor(COLORREF nColor);
	COLORREF GetColor() CONST;
	VOID SetFrameColor(COLORREF nColor);
	COLORREF GetFrameColor() CONST;
	VOID SetInteriorFrameColor(COLORREF nColor);
	COLORREF GetInteriorFrameColor() CONST;
	VOID SetCenterColor(COLORREF nColor);
	COLORREF GetCenterColor() CONST;
	VOID SetInteriorCenterColor(COLORREF nColor);
	COLORREF GetInteriorCenterColor() CONST;
	VOID SetBarColor(COLORREF nColor);
	COLORREF GetBarColor() CONST;
	VOID SetStubsColor(COLORREF nColor);
	COLORREF GetStubsColor() CONST;
	VOID SetThickness(INT nWidth);
	INT GetThickness() CONST;
	VOID SetFrameThickness(INT nWidth);
	INT GetFrameThickness() CONST;
	VOID SetCenterThickness(INT nWidth);
	INT GetCenterThickness() CONST;
	VOID SetBarThickness(INT nWidth);
	INT GetBarThickness() CONST;
	VOID SetStubsThickness(INT nWidth);
	INT GetStubsThickness() CONST;

public:
	VOID Open();
	BOOL IsOpen() CONST;
	BOOL IsClosed() CONST;
	VOID Close();
	VOID Pos1();
	BOOL IsPos1() CONST;
	VOID Pos2();
	BOOL IsPos2() CONST;
	VOID Pos3();
	BOOL IsPos3() CONST;
	VOID Broken();
	BOOL IsBroken() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextItemDispatchDriver wrapper class

class CMimicsTextItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsTextItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsTextItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsTextItemDispatchDriver(const CMimicsTextItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;
	VOID SetMode(INT nMode);
	INT GetMode() CONST;
	VOID SetColor(COLORREF nColor);
	COLORREF GetColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor);
	COLORREF GetBackgroundColor() CONST;
	BOOL SetFont(CONST LOGFONT *pFont);
	BOOL GetFont(LOGFONT *pFont) CONST;
	VOID AlignLeft();
	VOID AlignCenter();
	VOID AlignRight();
	VOID AlignVertical(BOOL bEnable);
	BOOL IsLeftAligned() CONST;
	BOOL IsCenterAligned() CONST;
	BOOL IsRightAligned() CONST;
	BOOL IsVerticalAligned() CONST;
	VOID LeftToRightReading();
	VOID TopToBottomReading();
	BOOL IsLeftToRightReading() CONST;
	BOOL IsTopToBottomReading() CONST;
	VOID SetTabChars(INT nChars);
	INT GetTabChars() CONST;
	VOID WrapWords(BOOL bEnable);
	BOOL IsWrappingWords() CONST;
	VOID SingleLine(BOOL bEnable);
	BOOL IsSingleLine() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageItemDispatchDriver wrapper class

class CMimicsImageItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsImageItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsImageItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsImageItemDispatchDriver(const CMimicsImageItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
	VOID SetStyle(INT nStyle);
	INT GetStyle() CONST;
	VOID SetFileName(LPCTSTR pszFileName);
	CString GetFileName() CONST;
	VOID SetImageOrigin(CONST POINT &pt);
	CPoint GetImageOrigin() CONST;
	VOID SetImageSize(CONST SIZE &size);
	CSize GetImageSize() CONST;
	VOID SetImageTransparency(BYTE nFactor);
	BYTE GetImageTransparency() CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupItemDispatchDriver wrapper class

class CMimicsGroupItemDispatchDriver : public CMimicsItemDispatchDriver
{
	// Construction
public:
	CMimicsGroupItemDispatchDriver() {}		// Calls COleDispatchDriver default constructor
	CMimicsGroupItemDispatchDriver(LPDISPATCH pDispatch) : CMimicsItemDispatchDriver(pDispatch) {}
	CMimicsGroupItemDispatchDriver(const CMimicsGroupItemDispatchDriver &cDispatchSource) : CMimicsItemDispatchDriver(cDispatchSource) {}

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsItem

// Specify the mimics item thumb size
#define MIMICSITEM_THUMB_SIZE   6

class CMimicsItem : public CMimicsClientItem
{
	DECLARE_DYNCREATE(CMimicsItem)

	// Construction
public:
	CMimicsItem(CMMDDocument *pContainerDoc = NULL);
	~CMimicsItem();

	// Attributes
protected:
	CLSID  m_clsid;
	CString  m_szName;
	CString  m_szType;
	CString  m_szText;
	CString  m_szLink;
	XFORM  m_xForm[2];
	CRect  m_rPosition[3];
	CPoint  m_ptCenter[2];
	BOOL  m_bVisible;
protected:
	CByteArray  m_nInfo;
protected:
	CMimicsItem  *m_pContainerItem;
	CView  *m_pImageView;
private:
	LONG  m_bLocked;

	// Operations
public:
	static CMimicsItem *Create(CMimicsItem *pItem, CView *pView, CMMDDocument *pDocument);

	static CMimicsItem *AllocateFromItem(CMimicsItem *pItem);
	static CMimicsItem *AllocateFromItem(CMMDLayoutItem *pItem);
	static CMimicsItem *AllocateFromData(CONST CByteArray &nData);

	VOID SetItemName(LPCTSTR pszName = NULL);
	CString GetItemName() CONST;
	VOID SetItemClassID(CLSID clsid);
	CLSID GetItemClassID() CONST;
	VOID SetItemType(LPCTSTR pszType = NULL);
	CString GetItemType() CONST;
	VOID SetItemLink(LPCTSTR pszName);
	CString GetItemLink() CONST;
	VOID SetItemSize(INT cx = 0, INT cy = 0);
	CSize GetItemSize() CONST;
	VOID SetItemToolTipText(LPCTSTR pszText = NULL);
	CString GetItemToolTipText() CONST;
	VOID SetItemVisibility(UINT bVisible = -1);
	BOOL GetItemVisibility() CONST;
	VOID SetItemProperties(CONST CByteArray &nInfo);
	BOOL GetItemProperties(CByteArray &nInfo) CONST;
	VOID SetItemContainer(CMimicsItem *pItem = NULL);
	CMimicsItem *GetItemContainer() CONST;
	VOID AdjustItemContainer();
	VOID SetItemImage(CView *pView);
	CView *GetItemImage() CONST;

	CRect DoTransformation(CONST RECT &rect) CONST;
	CPoint DoTransformation(CONST POINT &point) CONST;
	VOID DoTransformation(XFORM &xForm, CRect &rPosition) CONST;
	VOID DoTransformation(CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST;
	VOID DoTransformation(CONST CMimicsItem *pItem, CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST;
	CPoint DoInverseTransformation(CONST POINT &point) CONST;
	VOID DoInverseTransformation(XFORM &xForm, CRect &rPosition) CONST;
	VOID DoInverseTransformation(CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST;
	VOID DoInverseTransformation(CONST CMimicsItem *pItem, CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST;
	CPoint CalcTransform(CONST POINT &point) CONST;
	CPoint CalcTransform(CONST XFORM &xForm, CONST POINT &point) CONST;
	CPoint CalcTransform(CONST POINT &ptCenter, CONST POINT &point) CONST;
	CPoint CalcTransform(CONST POINT &ptCenter, CONST XFORM &xForm, CONST POINT &point) CONST;
	CRect CalcTransform(CONST RECT &rect) CONST;
	CRect CalcTransform(CONST XFORM &xForm, CONST RECT &rect) CONST;
	CRect CalcTransform(CONST POINT &ptCenter, CONST RECT &rect) CONST;
	CRect CalcTransform(CONST POINT &ptCenter, CONST XFORM &xForm, CONST RECT &rect) CONST;

	BOOL Lock();
	BOOL IsLocked() CONST;
	BOOL Unlock();

protected:
	VOID BuildInverseTransform(XFORM &xForm) CONST;

	VOID DrawItem();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsItem)
public:
	virtual	BOOL CreateNewItem(REFCLSID clsid, CView *pView, OLERENDER render = OLERENDER_DRAW, CLIPFORMAT cfFormat = 0, LPFORMATETC lpFormatEtc = NULL);
	virtual BOOL Draw(CDC *pDC, BOOL bShape = FALSE);
	virtual VOID SetPosition(CONST RECT &rect);
	virtual CRect GetPosition() CONST;
	virtual VOID FlipHorizontal();
	virtual VOID FlipVertical();
	virtual VOID Rotate(double fAngle);
	virtual VOID Reset();
public:
	virtual VOID SetItemPosition(CONST RECT &rect);
	virtual CRect GetItemPosition() CONST;
	virtual VOID NormalizeItemPosition(BOOL bUndo = FALSE);
	virtual VOID AdjustItemPosition();
	virtual VOID AdjustItemPosition(CONST RECT &rect);
	virtual VOID SetItemDefaultPosition(CONST RECT &rect);
	virtual CRect GetItemDefaultPosition() CONST;
	virtual VOID AdjustItemDefaultPosition();
	virtual VOID SetItemCenterPoint();
	virtual VOID SetItemCenterPoint(CONST POINT &ptCenter);
	virtual CPoint GetItemCenterPoint() CONST;
	virtual VOID AdjustItemCenterPoint();
	virtual VOID SaveItemDefaultState();
	virtual VOID LoadItemDefaultState();
	virtual BOOL IsItemFlippedOrRotated() CONST;
	virtual BOOL IsItemSizeable() CONST;
	virtual CRect CalcItemFrameExtent() CONST;
	virtual BOOL CalcItemShape(CBitmap *pBitmap);
	virtual BOOL CheckPointOnItem(CONST POINT &ptPosition);
	virtual BOOL CheckPointInsideItem(CONST POINT &ptPosition);
	virtual BOOL Copy(CONST CMimicsItem *pItem);
	virtual BOOL Compare(CONST CMimicsItem *pItem) CONST;
	virtual BOOL Map(CMMDLayoutItem *pItem);
	virtual BOOL Map(CByteArray &nData);
	virtual BOOL Unmap(CONST CMMDLayoutItem *pItem);
	virtual BOOL Unmap(CONST CByteArray &nData);
	virtual BOOL MapProperties(CByteArray &nInfo);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	virtual VOID UpdateProperties();
protected:
	virtual void OnChange(OLE_NOTIFICATION nCode, DWORD dwParam);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineItem

class CMimicsLineItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsLineItem)

	// Construction
public:
	CMimicsLineItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nWidth;
		BOOL  bCrossing;
		BOOL  bArrow[2];
		double  fPtCross;
		COLORREF  nColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nWidth;
	BOOL  m_bCrossing;
	BOOL  m_bArrow[2];
	double  m_fPtCross;
	COLORREF  m_nColor;

	// Operations
public:
	VOID SetStyle(INT nStyle = PS_SOLID);
	INT GetStyle() CONST;
	VOID Arrow(BOOL bEnable = FALSE);
	VOID DoubleArrow(BOOL bEnable = FALSE);
	VOID Cross(BOOL bEnable = FALSE);
	BOOL SetCrossPt(double fPt = 0.0);
	BOOL GetCrossPt(double *fPt) CONST;
	BOOL IsArrow() CONST;
	BOOL IsDoubleArrow() CONST;
	BOOL IsCross() CONST;
	VOID SetColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetColor() CONST;
	VOID SetThickness(INT nWidth = 1);
	INT GetThickness() CONST;
	VOID Solid();
	VOID Dash();
	VOID Dot();
	VOID DashDot();
	VOID DashDotDot();
	BOOL IsSolid() CONST;
	BOOL IsDashed() CONST;
	BOOL IsDotted() CONST;
	BOOL IsDashDotted() CONST;
	BOOL IsDashDotDotted() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsLineItem)
public:
	virtual INT CalcItemFrameOutlinePoints(CONST RECT &rect, LPPOINT pPoints = NULL, INT nPoints = 0) CONST;
	virtual BOOL CheckPointInsideItem(CONST POINT &ptPosition);
	virtual BOOL Copy(CONST CMimicsItem *pItem);
	virtual BOOL Compare(CONST CMimicsItem *pItem) CONST;
	virtual BOOL MapProperties(CByteArray &nInfo);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	virtual VOID UpdateProperties();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsLineItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItem

class CMimicsRectangleItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsRectangleItem)

	// Construction
public:
	CMimicsRectangleItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nBorderSize;
		INT  nBorderStyle;
		INT  nInteriorHatch;
		COLORREF  nHatchColor;
		COLORREF  nBorderColor;
		COLORREF  nInteriorColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nBorderSize;
	INT  m_nBorderStyle;
	INT  m_nInteriorHatch;
	COLORREF  m_nHatchColor;
	COLORREF  m_nBorderColor;
	COLORREF  m_nInteriorColor;

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize = 1);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle = PS_SOLID);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch = -1, COLORREF nColor = VGA_COLOR_BLACK);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsRectangleItem)
public:
	virtual BOOL Copy(CONST CMimicsItem *pItem);
	virtual BOOL Compare(CONST CMimicsItem *pItem) CONST;
	virtual BOOL MapProperties(CByteArray &nInfo);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	virtual VOID UpdateProperties();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsRectangleItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItem

class CMimicsEllipseItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsEllipseItem)

	// Construction
public:
	CMimicsEllipseItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nBorderSize;
		INT  nBorderStyle;
		INT  nInteriorHatch;
		COLORREF  nHatchColor;
		COLORREF  nBorderColor;
		COLORREF  nInteriorColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nBorderSize;
	INT  m_nBorderStyle;
	INT  m_nInteriorHatch;
	COLORREF  m_nHatchColor;
	COLORREF  m_nBorderColor;
	COLORREF  m_nInteriorColor;

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize = 1);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle = PS_SOLID);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch = -1, COLORREF nColor = VGA_COLOR_BLACK);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsEllipseItem)
public:
	virtual BOOL Copy(CONST CMimicsItem *pItem);
	virtual BOOL Compare(CONST CMimicsItem *pItem) CONST;
	virtual BOOL MapProperties(CByteArray &nInfo);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	virtual VOID UpdateProperties();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsEllipseItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcItem

class CMimicsArcItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsArcItem)

	// Construction
public:
	CMimicsArcItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nBorderSize;
		INT  nBorderStyle;
		INT  nInteriorHatch;
		double  ptRadial[2];
		COLORREF  nHatchColor;
		COLORREF  nBorderColor;
		COLORREF  nInteriorColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nBorderSize;
	INT  m_nBorderStyle;
	INT  m_nInteriorHatch;
	double  m_ptRadial[2];
	COLORREF  m_nHatchColor;
	COLORREF  m_nBorderColor;
	COLORREF  m_nInteriorColor;

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize = 1);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle = PS_SOLID);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch = -1, COLORREF nColor = VGA_COLOR_BLACK);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;
	VOID SetRadials(double fRadial1 = 0.0, double fRadial2 = 0.0);
	VOID GetRadials(double &fRadial1, double &fRadial2) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsArcItem)
public:
	virtual BOOL Copy(CONST CMimicsItem *pItem);
	virtual BOOL Compare(CONST CMimicsItem *pItem) CONST;
	virtual BOOL MapProperties(CByteArray &nInfo);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	virtual VOID UpdateProperties();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsArcItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItem

class CMimicsTriangleItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsTriangleItem)

	// Construction
public:
	CMimicsTriangleItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nBorderSize;
		INT  nBorderStyle;
		INT  nInteriorHatch;
		double  ptEdges[3][2];
		COLORREF  nHatchColor;
		COLORREF  nBorderColor;
		COLORREF  nInteriorColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nBorderSize;
	INT  m_nBorderStyle;
	INT  m_nInteriorHatch;
	double  m_ptEdges[3][2];
	COLORREF  m_nHatchColor;
	COLORREF  m_nBorderColor;
	COLORREF  m_nInteriorColor;

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetBorderSize(INT nSize = 1);
	INT GetBorderSize() CONST;
	VOID SetBorderStyle(INT nStyle = PS_SOLID);
	INT GetBorderStyle() CONST;
	VOID SetBorderColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetBorderColor() CONST;
	VOID SetInteriorColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorColor() CONST;
	VOID SetInteriorHatch(INT nHatch = -1, COLORREF nColor = VGA_COLOR_BLACK);
	BOOL GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST;
	VOID SetEdges(double x1 = 0.0, double y1 = 0.0, double x2 = 0.0, double y2 = 0.0, double x3 = 0.0, double y3 = 0.0);
	VOID GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsTriangleItem)
public:
	virtual BOOL Copy(CONST CMimicsItem *pItem);
	virtual BOOL Compare(CONST CMimicsItem *pItem) CONST;
	virtual BOOL MapProperties(CByteArray &nInfo);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	virtual VOID UpdateProperties();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsTriangleItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItem

class CMimicsSwitchItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsSwitchItem)

	// Construction
public:
	CMimicsSwitchItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  nStyle;
		INT  nWidth;
		INT  nBarWidth;
		INT  nStubsWidth;
		INT  nFrameWidth;
		INT  nCenterWidth;
		COLORREF  nColor;
		COLORREF  nBarColor;
		COLORREF  nStubsColor;
		COLORREF  nFrameColor[2];
		COLORREF  nCenterColor[2];
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	INT  m_nWidth;
	INT  m_nBarWidth;
	INT  m_nStubsWidth;
	INT  m_nFrameWidth;
	INT  m_nCenterWidth;
	COLORREF  m_nColor;
	COLORREF  m_nBarColor;
	COLORREF  m_nStubsColor;
	COLORREF  m_nFrameColor[2];
	COLORREF  m_nCenterColor[2];

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetColor() CONST;
	VOID SetFrameColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetFrameColor() CONST;
	VOID SetInteriorFrameColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorFrameColor() CONST;
	VOID SetCenterColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetCenterColor() CONST;
	VOID SetInteriorCenterColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetInteriorCenterColor() CONST;
	VOID SetBarColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetBarColor() CONST;
	VOID SetStubsColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetStubsColor() CONST;
	VOID SetThickness(INT nWidth = 1);
	INT GetThickness() CONST;
	VOID SetFrameThickness(INT nWidth = 2);
	INT GetFrameThickness() CONST;
	VOID SetCenterThickness(INT nWidth = 1);
	INT GetCenterThickness() CONST;
	VOID SetBarThickness(INT nWidth = 1);
	INT GetBarThickness() CONST;
	VOID SetStubsThickness(INT nWidth = 1);
	INT GetStubsThickness() CONST;

public:
	VOID Open();
	BOOL IsOpen() CONST;
	BOOL IsClosed() CONST;
	VOID Close();
	VOID Pos1();
	BOOL IsPos1() CONST;
	VOID Pos2();
	BOOL IsPos2() CONST;
	VOID Pos3();
	BOOL IsPos3() CONST;
	VOID Broken();
	BOOL IsBroken() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsSwitchItem)
public:
	virtual BOOL Copy(CONST CMimicsItem *pItem);
	virtual BOOL Compare(CONST CMimicsItem *pItem) CONST;
	virtual BOOL MapProperties(CByteArray &nInfo);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	virtual VOID UpdateProperties();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsSwitchItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextItem

class CMimicsTextItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsTextItem)

	// Construction
public:
	CMimicsTextItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbText;
		INT  nMode;
		INT  nTabs;
		UINT  nFormat;
		BOOL  bReading;
		LOGFONT  lfFont;
		COLORREF  nColor;
		COLORREF  nBkColor;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nMode;
	INT  m_nTabs;
	UINT  m_nFormat;
	BOOL  m_bReading;
	LOGFONT  m_lfFont;
	CString  m_szText;
	COLORREF  m_nColor;
	COLORREF  m_nBkColor;

	// Operations
public:
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;
	VOID SetMode(INT nMode = TRANSPARENT);
	INT GetMode() CONST;
	VOID SetColor(COLORREF nColor = VGA_COLOR_BLACK);
	COLORREF GetColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor = VGA_COLOR_WHITE);
	COLORREF GetBackgroundColor() CONST;
	BOOL SetFont(CONST LOGFONT *plfFont = NULL);
	BOOL GetFont(LOGFONT *plfFont) CONST;
	VOID AlignLeft();
	VOID AlignCenter();
	VOID AlignRight();
	VOID AlignVertical(BOOL bEnable);
	BOOL IsLeftAligned() CONST;
	BOOL IsCenterAligned() CONST;
	BOOL IsRightAligned() CONST;
	BOOL IsVerticalAligned() CONST;
	VOID LeftToRightReading();
	VOID TopToBottomReading();
	BOOL IsLeftToRightReading() CONST;
	BOOL IsTopToBottomReading() CONST;
	VOID SetTabChars(INT nChars = -1);
	INT GetTabChars() CONST;
	VOID WrapWords(BOOL bEnable = FALSE);
	BOOL IsWrappingWords() CONST;
	VOID SingleLine(BOOL bEnable = FALSE);
	BOOL IsSingleLine() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsTextItem)
public:
	virtual BOOL Copy(CONST CMimicsItem *pItem);
	virtual BOOL Compare(CONST CMimicsItem *pItem) CONST;
	virtual BOOL MapProperties(CByteArray &nInfo);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	virtual VOID UpdateProperties();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsTextItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageItem

class CMimicsImageItem : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsImageItem)

	// Construction
public:
	CMimicsImageItem(CMMDDocument *pContainerDoc = NULL);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbFileName;
		INT  nStyle;
		POINT  ptImage;
		SIZE  sizeImage;
		BYTE  nImageTransparency;
	} DATA, *PDATA, *LPDATA;
private:
	INT  m_nStyle;
	CString  m_szFileName;
	CPoint  m_ptImage;
	CSize  m_sizeImage;
	BYTE  m_nImageTransparency;

	// Operations
public:
	VOID SetStyle(INT nStyle = 0);
	INT GetStyle() CONST;
	VOID SetFileName(LPCTSTR pszFileName = EMPTYSTRING);
	CString GetFileName() CONST;
	VOID SetImageOrigin(CONST POINT &pt = CPoint(0, 0));
	CPoint GetImageOrigin() CONST;
	VOID SetImageSize(CONST SIZE &size = CSize(100, 100));
	CSize GetImageSize() CONST;
	VOID SetImageTransparency(BYTE nFactor = 0xFF);
	BYTE GetImageTransparency() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsImageItem)
public:
	virtual BOOL Copy(CONST CMimicsItem *pItem);
	virtual BOOL Compare(CONST CMimicsItem *pItem) CONST;
	virtual BOOL MapProperties(CByteArray &nInfo);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	virtual VOID UpdateProperties();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsImageItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroup

class CMimicsGroup : public CMimicsItem
{
	DECLARE_DYNCREATE(CMimicsGroup)

	// Construction
public:
	CMimicsGroup(CMMDDocument *pContainerDoc = NULL);
	CMimicsGroup(LPCTSTR pszName, CMMDDocument *pContainerDoc = NULL);
	~CMimicsGroup();

	// Attributes
private:
	CMMDDocument  *m_pItemList;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;

	VOID AddItem(CMimicsItem *pItem);
	VOID RemoveItem(CMimicsItem *pItem);

	CMimicsItem *GetAt(INT nIndex) CONST;
	CMimicsItem *operator[](INT nIndex) CONST;

	CMMDDocument *GetItemList() CONST;

	INT GetItemCount() CONST;

	VOID RemoveAllItems();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsGroup)
public:
	virtual	BOOL CreateNewItem(REFCLSID clsid, CView *pView, OLERENDER render = OLERENDER_DRAW, CLIPFORMAT cfFormat = 0, LPFORMATETC lpFormatEtc = NULL);
	virtual BOOL Draw(CDC *pDC, BOOL bShape = FALSE);
	virtual VOID Reset();
public:
	virtual VOID SetItemPosition(CONST RECT &rect);
	virtual CRect GetItemPosition() CONST;
	virtual VOID NormalizeItemPosition(BOOL bUndo = FALSE);
	virtual VOID AdjustItemPosition();
	virtual VOID AdjustItemPosition(CONST RECT &rect);
	virtual VOID AdjustItemCenterPoint();
	virtual BOOL IsItemSizeable() CONST;
	virtual BOOL CheckPointInsideItem(CONST POINT &ptPosition);
	virtual BOOL Copy(CONST CMimicsItem *pItem);
	virtual BOOL Compare(CONST CMimicsItem *pItem) CONST;
	virtual BOOL MapProperties(CByteArray &nInfo);
	virtual BOOL UnmapProperties(CONST CByteArray &nInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsGroup)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDToolBar window

class CMMDToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CMMDToolBar)

	// Construction
public:
	CMMDToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDStatusBar window

class CMMDStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CMMDStatusBar)

	// Construction
public:
	CMMDStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CMMDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDToolTip window

class CMMDToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CMMDToolTip)

	// Construction
public:
	CMMDToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMMDToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDView window

class CMMDView : public CScrollView, public CDisplayLockable
{
	DECLARE_DYNCREATE(CMMDView)

	// Construction
public:
	CMMDView();

	// Attributes
private:
	INT  m_nImage[4];
	BOOL  m_bUseGrid;
	CSize  m_sizeGrid;
	CSize  m_sizeImage;
	CPoint  m_ptScroll;
	COLORREF  m_nImageGrid;
	COLORREF  m_nImageBkgnd;
	CMMDDocument  *m_pDocument;
	CMMDToolTip  m_wndToolTip;
	CMMDLayout  m_cLayout;
private:
	HCURSOR  m_hToolTipCursor;
	HCURSOR  m_hLinkTipCursor;
	BOOL  m_bInvalidDataMode;
	BOOL  m_bBadDataMode;
	BOOL  m_bToolTipMode;
private:
	BOOL  m_bItems;
	CPtrArray  m_pItems;
	CPtrArray  m_pItemsCode;
	CStringArray  m_szItemsParameters;
	HINSTANCE  m_hImageCode;
private:
	IUnknown  *m_pIUnknown;
	IClassFactory  *m_pIClassFactory;
	IEnumMimicsCtrls  *m_pIEnumMimicsCtrls;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetLayout(CONST CMMDLayout &cLayout, CString &szMessage);
	BOOL GetLayout(CMMDLayout &cLayout) CONST;

	BOOL EnableInvalidDataMode(BOOL bEnable = TRUE);
	BOOL IsInvalidDataModeEnabled() CONST;
	BOOL EnableBadDataMode(BOOL bEnable = TRUE);
	BOOL IsBadDataModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL Initialize(CTMEnvironment *pTMEnvironment);
	BOOL Initialize(CString &szTag, CTimeTag &tTag);
	BOOL Update(CTMEnvironment *pTMEnvironment);
	BOOL Reset(CTMEnvironment *pTMEnvironment);

	VOID DrawImage();
	BOOL HasImage() CONST;

	BOOL SetImageSize(CONST SIZE &size);
	BOOL GetImageSize(CSize &size) CONST;
	VOID AdjustToImageSize();

	BOOL GetPrintProperties(CMMDLayout &cLayout, CMetaFileDC &cMetaDC) CONST;

	CMMDDocument *GetDocument() CONST;

	class CMMDWnd *GetParent() CONST;

private:
	BOOL InstallMimicsCtrlInterface();
	VOID DestroyMimicsCtrlInterface();

	BOOL CreateDocument();
	VOID DestroyDocument();

	BOOL LoadLayoutCode(CString &szMessage);
	VOID FreeLayoutCode();

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();
	BOOL LoadLinkTipCursor();
	HCURSOR GetLinkTipCursor() CONST;
	BOOL FreeLinkTipCursor();

	BOOL DrawImage(CDC *pDC);
	VOID DrawBackground(CDC *pDC, INT x, INT y, CONST RECT &rect, CONST SIZE &size);

	VOID AdjustToImageSize(BOOL bResize);
	VOID CalcImageSize(CSize &size) CONST;

	CSize CalcScrollSizes() CONST;

	VOID UpdateScrollBars();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDView)
public:
	virtual VOID RecalcLayout();
protected:
	virtual BOOL OnScrollBy(CSize sizeScroll, BOOL bDoScroll);
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
protected:
	virtual void PostNcDestroy();
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMMDView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMMDWnd frame

// Specify the mimics display types
#define MMD_TYPE_NORMAL   1
// Specify the mimics display retrieval modes
#define MMD_RETRIEVE_EXACTTIME   (1<<0)
#define MMD_RETRIEVE_STOPBYTIME   (1<<1)
#define MMD_RETRIEVE_STOPBYEND   (1<<2)
#define MMD_RETRIEVE_STOPBYREALTIME   (1<<3)
#define MMD_RETRIEVE_STOPPED   (1<<4)
#define MMD_RETRIEVE_RELATIVE   (1<<5)
#define MMD_RETRIEVE_AUTOFORWARD   (1<<6)
#define MMD_RETRIEVE_AUTOBACKWARD   (1<<7)
#define MMD_RETRIEVE_MANUALFORWARD   (1<<8)
#define MMD_RETRIEVE_MANUALBACKWARD   (1<<9)
#define MMD_RETRIEVE_PSEUDOREALTIME   (1<<10)
// Specify the mimics display print modes
#define MMD_PRINT_ALIGNHLEFTVTOP   1
#define MMD_PRINT_ALIGNHLEFTVCENTER   2
#define MMD_PRINT_ALIGNHLEFTVBOTTOM   3
#define MMD_PRINT_ALIGNHCENTERVTOP   4
#define MMD_PRINT_ALIGNHCENTERVCENTER   5
#define MMD_PRINT_ALIGNHCENTERVBOTTOM   6
#define MMD_PRINT_ALIGNHRIGHTVTOP   7
#define MMD_PRINT_ALIGNHRIGHTVCENTER   8
#define MMD_PRINT_ALIGNHRIGHTVBOTTOM   9
#define MMD_PRINT_ALIGNDEFAULT   4
#define MMD_PRINT_ALIGNMENT   0x000F
#define MMD_PRINT_AUTOSCALE   (1<<4)
#define MMD_PRINT_FIXEDSCALE   (1<<5)
#define MMD_PRINT_UNDERLINEOOL   (1<<6)
#define MMD_PRINT_NOCOLORS   (1<<7)
#define MMD_PRINT_CLEARCOMMENTS   (1<<8)
#define MMD_PRINT_ATTIME   (1<<9)
#define MMD_PRINT_ATDAILYTIME   (1<<10)
#define MMD_PRINT_ATEVENT   (1<<11)
#define MMD_PRINT_REPEATBYINTERVAL   (1<<12)
#define MMD_PRINT_REPEATSTOPBYCOUNT   (1<<13)
#define MMD_PRINT_REPEATSTOPBYTIME   (1<<14)
#define MMD_PRINT_DAILYREPEATSTOPBYCOUNT   (1<<15)
#define MMD_PRINT_DAILYREPEATSTOPBYTIME   (1<<16)
#define MMD_PRINT_ACTIVE   (1<<17)
// Specify the mimics display print fonts
#define MMD_PRINTFONT_TITLE   0
#define MMD_PRINTFONT_SUBTITLE   1
#define MMD_PRINTFONT_OPERATINGDETAILS   2
#define MMD_PRINTFONT_OPERATINGMODE   3
#define MMD_PRINTFONT_FOOTER   4
#define MMD_PRINTFONT_NOTICE   5
#define MMD_PRINTFONT_LOGO   6
#define MMD_PRINTFONTS   7
// Specify the mimics display statusbar pane identifiers
#define ID_MMD_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_MMD_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_MMD_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class CMMDWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CMMDWnd)

	// Construction
public:
	CMMDWnd();

	// Attributes
private:
	CMMDToolBar  m_wndToolBar;
	CMMDStatusBar  m_wndStatusBar;
	CMMDView  m_wndView;
private:
	CMMDOpenDialog  m_dlgOpen;
	CMMDSettingsDialog  m_dlgSettings;
	CMMDLinkagesDialog  m_dlgLinkages;
	CMMDRetrieveDialog  m_dlgRetrievals;
private:
	CMMDRetrieveThread  m_cRetrieveThread;
	CMMDPrintThread  m_cPrintThread;
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
	BOOL SetLayout(LPCTSTR pszLayout, CONST SIZE &sizeImage, INT nMarginLeft, INT nMarginTop, INT nMarginRight, INT nMarginBottom, COLORREF nImageBkgnd, CONST SIZE &sizeGrid, COLORREF nImageGrid, BOOL bUseGrid);
	BOOL SetLayout(CONST CMMDLayout &cLayout, CString &szMessage);
	BOOL GetLayout(CString &szLayout, CSize &sizeImage, INT &nMarginLeft, INT &nMarginTop, INT &nMarginRight, INT &nMarginBottom, COLORREF &nImageBkgnd, CSize &sizeGrid, COLORREF &nImageGrid, BOOL &bUseGrid) CONST;
	BOOL GetLayout(CMMDLayout &cLayout) CONST;

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

	BOOL SetPrintJobs(CONST CMMDPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CMMDPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CMMDPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	CMMDWnd *Find(INT nType, UINT nMode, LPCTSTR pszName) CONST;

	VOID AdjustToDefaultSize();
	VOID AdjustToDefaultSize(CSize &size);

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

	BOOL LoadLayout(LPCTSTR pszLayout, CMMDLayout &cLayout);
	BOOL HasLayout() CONST;

	BOOL StartSchedulePrintJobs();
	BOOL IsSchedulingPrintJobs() CONST;
	BOOL StopSchedulePrintJobs();

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CMMDPrintJobInfo *pJobInfo, CMMDLayout &cLayout, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CMetaFileDC &cMetaDC) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CMMDPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CMMDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CMetaFileDC &cMetaDC);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CMMDPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CMMDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CPtrArray &pFonts, LPRECT prClip, BOOL bCalc = FALSE);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nAlignment, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nAlignment, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, UINT nAlignment, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CFont *pFont, UINT nAlignment, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, UINT nAlignment, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, UINT nAlignment, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(CONST CMMDLayout &cLayout) CONST;
	CString GetPrintDocOperatingDetails(CONST CMMDPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST;
	CString GetPrintDocOperatingMode(CONST CMMDPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMMDWnd)
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
	//{{AFX_MSG(CMMDWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSettings();
	afx_msg void OnLinkages();
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


#endif // __MMD_H__
