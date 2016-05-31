// GRD.H : Graphic Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the graphic display related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/25 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __GRD_H__
#define __GRD_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CGRDPrintJobInfo

class CGRDPrintJobInfo : public CObject
{
	// Construction
public:
	CGRDPrintJobInfo();

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

	VOID Copy(CONST CGRDPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CGRDPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDPrintJobs

class CGRDPrintJobs : public CPtrArray
{
	// Construction
public:
	CGRDPrintJobs();
	~CGRDPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CGRDPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CGRDPrintJobInfo *GetAt(INT nIndex) CONST;
	CGRDPrintJobInfo *operator[](INT nIndex) CONST;

	TIMEKEY Schedule();

	VOID RemoveAll();

	BOOL Copy(CONST CGRDPrintJobs *pPrintJobs);
	BOOL Compare(CONST CGRDPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDParameterSample

class CGRDParameterSample : public CTMParameter
{
	// Construction
public:
	CGRDParameterSample();

	// Attributes
private:
	CPoint  m_ptSample;
	BOOL  m_bConnected;

	// Operations
public:
	VOID SetUpdateTMUnit(LPCTSTR pszTag);
	CString GetUpdateTMUnit() CONST;
	VOID SetUpdateTime(CONST CTimeTag &tTime);
	CTimeTag GetUpdateTime() CONST;

	VOID SetPosition(CONST POINT &point);
	CPoint GetPosition() CONST;

	VOID DoConnect(BOOL bEnable = TRUE);
	BOOL IsConnected() CONST;

	BOOL IsDummy() CONST;

	BOOL Copy(CONST CGRDParameterSample *pParameterSample);
	BOOL Compare(CONST CGRDParameterSample *pParameterSample) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDParameterSamples

class CGRDParameterSamples : public CPtrArray
{
	// Construction
public:
	CGRDParameterSamples();
	CGRDParameterSamples(LPCTSTR pszName);
	~CGRDParameterSamples();

	// Attributes
private:
	CString  m_szName;
	CTimeTag  m_tPlot;
	double  m_fRange[2];
	BOOL  m_bInterruption;
	BOOL  m_bRange;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetRange(double fMinimum, double fMaximum);
	BOOL GetRange(double &fMinimum, double &fMaximum) CONST;
	VOID SetLastPlotTime(CONST CTimeTag &tTime);
	CTimeTag GetLastPlotTime() CONST;
	VOID SetInterruptionFlag(BOOL bEnable = FALSE);
	BOOL GetInterruptionFlag() CONST;

	INT Add(CONST CGRDLayoutParameter *pParameter, CGRDParameterSample *pParameterSample);

	INT Find(CONST CTimeTag &tTime) CONST;
	INT Find(CONST CTimeTag &tTime, CONST POINT &point, CONST SIZE &size) CONST;
	INT Find(CONST CGRDParameterSample *pParameterSample) CONST;

	CGRDParameterSample *GetAt(INT nIndex) CONST;
	CGRDParameterSample *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CGRDParameterSamples *pParameterSamples);
	BOOL Compare(CONST CGRDParameterSamples *pParameterSamples) CONST;

private:
	INT FindIndex(CONST CGRDParameterSample *pParameterSample, BOOL bInsert = FALSE) CONST;
	INT FindIndex(CONST CTimeTag &tTime, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDParameterPlots

class CGRDParameterPlots : public CPtrArray
{
	// Construction
public:
	CGRDParameterPlots();
	~CGRDParameterPlots();

	// Attributes
private:
	CTimeTag  m_tRange[2];
	BOOL  m_bRange;

	// Operations
public:
	VOID SetUpdateRange(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime);
	BOOL GetUpdateRange(CTimeTag &tStartTime, CTimeTag &tStopTime) CONST;

	INT Add(CGRDParameterSamples *pParameterSamples);

	CGRDParameterSamples *GetAt(INT nIndex) CONST;
	CGRDParameterSamples *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CGRDParameterPlots *pPlots);
	BOOL Compare(CONST CGRDParameterPlots *pPlots) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDMarker

class CGRDMarker : public CPoint
{
	// Construction
public:
	CGRDMarker();
	CGRDMarker(CONST POINT &pt);

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		POINT  ptPosition;
	} DATA, *PDATA, *LPDATA;

	// Operations
public:
	VOID Copy(CONST CGRDMarker *pMarker);
	BOOL Compare(CONST CGRDMarker *pMarker) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDMarkers

class CGRDMarkers : public CPtrArray
{
	// Construction
public:
	CGRDMarkers();
	~CGRDMarkers();

	// Attributes
public:

	// Operations
public:
	INT Add(CGRDMarker *pMarker);

	INT Find(CONST POINT &pt, INT nScope = 0) CONST;

	CGRDMarker *GetAt(INT nIndex) CONST;
	CGRDMarker *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CGRDMarkers *pMarkers);
	BOOL Compare(CONST CGRDMarkers *pMarkers) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(CONST POINT &pt, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsLayoutPage dialog

#define IDC_GRDSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC   1003
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME   1004
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW   1005
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE   1006
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER   1007
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_REMOVE   1008
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_SHOWDATA   1009
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA   1010
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA   1011
#define IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS   1012
#define IDC_GRDSETTINGS_LAYOUTPAGE_COLORS   1013
#define IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS_STATIC   1014
#define IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS   1015
#define IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_COLOR_STATIC   1016
#define IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_COLOR   1017
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS   1018
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1019
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION   1020
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_COMMENT_STATIC   1021
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1022
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES   1023
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1024
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE   1025
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1026
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE   1027
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1028
#define IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1029

class CGRDSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CGRDSettingsLayoutPage)

	// Construction
public:
	CGRDSettingsLayoutPage();

	// Attributes
private:
	CUIntArray  m_nColumns[2];
	CUIntArray  m_nColors[2];
	LOGFONT  m_fntTitle[2];
	LOGFONT  m_fntItems[2];
	LOGFONT  m_fntValues[2];
	LOGFONT  m_fntAxes[2];
	BOOL  m_bInvalidData[2];
	BOOL  m_bBadData[2];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;
	CStringArray  m_szColumns;
	INT  m_nColumnIndex;

	// Dialog Data
	//{{AFX_DATA(CGRDSettingsLayoutPage)
	enum { IDD = IDD_GRD_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetColors(CUIntArray &nColors) CONST;
	BOOL GetTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetValuesFont(LPLOGFONT pValuesFont) CONST;
	BOOL GetAxesFont(LPLOGFONT pAxesFont) CONST;
	BOOL GetInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetBadDataMode(BOOL &bEnable) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CGRDSettingsDialog *GetParentDialog() CONST;
	class CGRDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumLayoutColumns();
	BOOL EnumLayoutColors();
	BOOL EnumFontLocations();

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
	//{{AFX_VIRTUAL(CGRDSettingsLayoutPage)
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
	//{{AFX_MSG(CGRDSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnInsertColumnBefore();
	afx_msg void OnInsertColumnAfter();
	afx_msg void OnRemoveColumn();
	afx_msg void OnInvalidData();
	afx_msg void OnBadData();
	afx_msg void OnToolTips();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeColumnName();
	afx_msg void OnSelchangeColorLocation();
	afx_msg void OnSelchangeColor();
	afx_msg void OnSelchangeFontLocation();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsChartPage dialog

#define IDC_GRDSETTINGS_CHARTPAGE_DETAILS   1001
#define IDC_GRDSETTINGS_CHARTPAGE_TYPE   1002
#define IDC_GRDSETTINGS_CHARTPAGE_TYPE_NORMAL   1003
#define IDC_GRDSETTINGS_CHARTPAGE_TYPE_STRIPCHART   1004
#define IDC_GRDSETTINGS_CHARTPAGE_TYPE_STACKCHART   1005
#define IDC_GRDSETTINGS_CHARTPAGE_TYPE_DIAGRAM   1006
#define IDC_GRDSETTINGS_CHARTPAGE_MODES   1007
#define IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING   1008
#define IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_NORMAL   1009
#define IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_AREA   1010
#define IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR   1011
#define IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL   1012
#define IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_OVERWRITE   1013
#define IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_RESTART   1014
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH   1015
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH   1016
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_USE   1017
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_STATIC   1018
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_NUMBER   1019
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT   1020
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_USE   1021
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_STATIC   1022
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_NUMBER   1023
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS   1024
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL   1025
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL_NUMBER   1026
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_WIDTH   1027
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL   1028
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL_NUMBER   1029
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_COLOR_STATIC   1030
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_COLOR   1031
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS   1032
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL   1033
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL_NUMBER   1034
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_WIDTH   1035
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL   1036
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL_NUMBER   1037
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_COLOR_STATIC   1038
#define IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_COLOR   1039
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION   1040
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS_STATIC   1041
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS   1042
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS_STATIC   1043
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS   1044
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES_STATIC   1045
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES   1046
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL   1047
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER   1048
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_STATIC   1049
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_STATIC   1050
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER   1051
#define IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_MINUTES_STATIC   1052
#define IDC_GRDSETTINGS_CHARTPAGE_COLORS   1053
#define IDC_GRDSETTINGS_CHARTPAGE_BACKGROUND_COLOR_STATIC   1054
#define IDC_GRDSETTINGS_CHARTPAGE_BACKGROUND_COLOR   1055
#define IDC_GRDSETTINGS_CHARTPAGE_LABEL_COLOR_STATIC   1056
#define IDC_GRDSETTINGS_CHARTPAGE_LABEL_COLOR   1057

// Specify the graphic display settings chart page related limits
#define GRDSETTINGSCHARTPAGE_MINIMUMGRIDS   1
#define GRDSETTINGSCHARTPAGE_MAXIMUMGRIDS   100
#define GRDSETTINGSCHARTPAGE_DEFAULTGRIDS   1
#define GRDSETTINGSCHARTPAGE_MINIMUMTICKS   1
#define GRDSETTINGSCHARTPAGE_MAXIMUMTICKS   100
#define GRDSETTINGSCHARTPAGE_DEFAULTTICKS   1
#define GRDSETTINGSCHARTPAGE_MINIMUMGRIDSWIDTH   1
#define GRDSETTINGSCHARTPAGE_MAXIMUMGRIDSWIDTH   4
#define GRDSETTINGSCHARTPAGE_DEFAULTGRIDSWIDTH   1
#define GRDSETTINGSCHARTPAGE_MINIMUMTICKSWIDTH   1
#define GRDSETTINGSCHARTPAGE_MAXIMUMTICKSWIDTH   4
#define GRDSETTINGSCHARTPAGE_DEFAULTTICKSWIDTH   1
#define GRDSETTINGSCHARTPAGE_MINIMUMDURATION   1
#define GRDSETTINGSCHARTPAGE_MAXIMUMDURATION   (100*MINUTESPERDAY)
#define GRDSETTINGSCHARTPAGE_DEFAULTDURATION   MINUTESPERHOUR
#define GRDSETTINGSCHARTPAGE_MINIMUMPERCENTAGE   1
#define GRDSETTINGSCHARTPAGE_MAXIMUMPERCENTAGE   100
#define GRDSETTINGSCHARTPAGE_DEFAULTPERCENTAGE   100
#define GRDSETTINGSCHARTPAGE_MINIMUMUPDATE   0
#define GRDSETTINGSCHARTPAGE_MAXIMUMUPDATE   MINUTESPERDAY
#define GRDSETTINGSCHARTPAGE_DEFAULTUPDATE   1

class CGRDSettingsChartPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CGRDSettingsChartPage)

	// Construction
public:
	CGRDSettingsChartPage();

	// Attributes
private:
	CGRDLayout  m_cLayout[2];

	// Dialog Data
	//{{AFX_DATA(CGRDSettingsChartPage)
	enum { IDD = IDD_GRD_SETTINGS_CHARTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CGRDLayout &cLayout) CONST;

	class CGRDSettingsDialog *GetParentDialog() CONST;
	class CGRDWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGRDSettingsChartPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CGRDLayout &cLayout);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGRDSettingsChartPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTypeNormal();
	afx_msg void OnTypeStripchart();
	afx_msg void OnTypeStackchart();
	afx_msg void OnTypeDiagram();
	afx_msg void OnPlottingNormal();
	afx_msg void OnPlottingArea();
	afx_msg void OnPlottingScroll();
	afx_msg void OnPlottingOverwrite();
	afx_msg void OnPlottingRestart();
	afx_msg void OnGraphWidth();
	afx_msg void OnGraphHeight();
	afx_msg void OnHorizontalGrids();
	afx_msg void OnVerticalGrids();
	afx_msg void OnHorizontalTicks();
	afx_msg void OnVerticalTicks();
	afx_msg void OnDurationInterval();
	afx_msg void OnSelchangeGridsColor();
	afx_msg void OnSelchangeTicksColor();
	afx_msg void OnSelchangeBackgroundColor();
	afx_msg void OnSelchangeLabelColor();
	afx_msg void OnSpinchangeWidth();
	afx_msg void OnSpinchangeHeight();
	afx_msg void OnSpinchangeHorizontalGrids();
	afx_msg void OnSpinchangeVerticalGrids();
	afx_msg void OnSpinchangeHorizontalTicks();
	afx_msg void OnSpinchangeVerticalTicks();
	afx_msg void OnSpinchangeGridsWidth();
	afx_msg void OnSpinchangeTicksWidth();
	afx_msg void OnSpinchangeDurationDays();
	afx_msg void OnSpinchangeDurationHours();
	afx_msg void OnSpinchangeDurationMinutes();
	afx_msg void OnSpinchangeDurationInterval();
	afx_msg void OnSpinchangeUpdateInterval();
	afx_msg void OnKillFocusDurationDays();
	afx_msg void OnKillFocusDurationHours();
	afx_msg void OnKillFocusDurationMinutes();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsParametersPage dialog

#define IDC_GRDSETTINGS_PARAMETERSPAGE_DETAILS   1001
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER_STATIC   1002
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER   1003
#define IDC_GRDSETTINGS_PARAMETERSPAGE_ADD   1004
#define IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY   1005
#define IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVE   1006
#define IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVEALL   1007
#define IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS_STATIC   1008
#define IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS   1009
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES   1010
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE_STATIC   1011
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE   1012
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS   1013
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT   1014
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE   1015
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER   1016
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM_STATIC   1017
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM   1018
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM_STATIC   1019
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM   1020
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COMMENTS_STATIC   1021
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COMMENTS   1022
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR_STATIC   1023
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR   1024
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE   1025
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH_STATIC   1026
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH   1027
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH_PIXELS   1028
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE_STATIC   1029
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE   1030
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL_STATIC   1031
#define IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL   1032

// Specify the graphic display settings parameters page related limits
#define GRDSETTINGSPARAMETERSPAGE_MINIMUMVALUEOCCURRENCE   0
#define GRDSETTINGSPARAMETERSPAGE_MAXIMUMVALUEOCCURRENCE   999
#define GRDSETTINGSPARAMETERSPAGE_DEFAULTVALUEOCCURRENCE   0
#define GRDSETTINGSPARAMETERSPAGE_MINIMUMVALUEDIGITS   1
#define GRDSETTINGSPARAMETERSPAGE_MAXIMUMVALUEDIGITS   16
#define GRDSETTINGSPARAMETERSPAGE_DEFAULTVALUEDIGITS   DEFAULTFLOATINGPOINTDECIMALPLACES
#define GRDSETTINGSPARAMETERSPAGE_MINIMUMLINEWIDTH   1
#define GRDSETTINGSPARAMETERSPAGE_MAXIMUMLINEWIDTH   4
#define GRDSETTINGSPARAMETERSPAGE_DEFAULTLINEWIDTH   1

class CGRDSettingsParametersPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CGRDSettingsParametersPage)

	// Construction
public:
	CGRDSettingsParametersPage();

	// Attributes
private:
	CGRDLayout  m_cLayout[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CGRDSettingsParametersPage)
	enum { IDD = IDD_GRD_SETTINGS_PARAMETERSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CGRDLayout &cLayout) CONST;

	class CGRDSettingsDialog *GetParentDialog() CONST;
	class CGRDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumParameters();
	BOOL EnumContents();
	BOOL EnumValueCoding();
	BOOL EnumValueRanges();
	BOOL EnumLineStyle();
	BOOL EnumLineSymbol();

	VOID SetParameterInfo();
	BOOL GetParameterInfo(CString &szName, CString &szComments, ULONGLONG &nAttributes, INT &nOccurrence, INT &nDigits, double &fMinimum, double &fMaximum, INT &nLineWidth, INT &nLineStyle, INT &nLineSymbol, COLORREF &nColor) CONST;

	VOID SetCurParameter(INT nIndex = -1);
	INT GetCurParameter() CONST;

	CGRDLayoutParameter *FindParameter() CONST;
	BOOL CheckParameter(BOOL bModify = TRUE) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGRDSettingsParametersPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CGRDLayout &cLayout);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGRDSettingsParametersPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddParameter();
	afx_msg void OnModifyParameter();
	afx_msg void OnRemoveParameter();
	afx_msg void OnRemoveAllParameters();
	afx_msg void OnDigits();
	afx_msg void OnOccurrence();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeValueCoding();
	afx_msg void OnSelchangeMinimum();
	afx_msg void OnSelchangeMaximum();
	afx_msg void OnSelchangeColor();
	afx_msg void OnSelchangeLineStyle();
	afx_msg void OnSelchangeLineSymbol();
	afx_msg void OnSpinchangeDigits();
	afx_msg void OnSpinchangeOccurrence();
	afx_msg void OnSpinchangeLineWidth();
	afx_msg void OnEditchangeMinimum();
	afx_msg void OnEditchangeMaximum();
	afx_msg void OnEditchangeComments();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsRetrievingPage dialog

#define IDC_GRDSETTINGS_RETRIEVINGPAGE_DETAILS   1001
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC   1002
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE   1003
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_INSPECT   1004
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO   1005
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS   1006
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC   1007
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT   1008
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC   1009
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY   1010
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC   1011
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT   1012
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC   1013
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE   1014
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC   1015
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME   1016
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO   1017
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME   1018
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC   1019
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME   1020
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC   1021
#define IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE   1022

class CGRDSettingsRetrievingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CGRDSettingsRetrievingPage)

	// Construction
public:
	CGRDSettingsRetrievingPage();

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CGRDSettingsRetrievingPage)
	enum { IDD = IDD_GRD_SETTINGS_RETRIEVINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetDataSourceFileName(CString &szFileName) CONST;

	class CGRDSettingsDialog *GetParentDialog() CONST;
	class CGRDWnd *GetParentDisplay() CONST;

private:
	VOID EnumDataSources();
	VOID ShowDataSourceInfo();

	BOOL CheckDataSource(LPCTSTR pszFileName) CONST;
	BOOL CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST;

	CString FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGRDSettingsRetrievingPage)
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
	//{{AFX_MSG(CGRDSettingsRetrievingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnInspect();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeFileName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsPrintingComments window

class CGRDSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CGRDSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsPrintingPage dialog

#define IDC_GRDSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_GRDSETTINGS_PRINTINGPAGE_NAME_STATIC   1002
#define IDC_GRDSETTINGS_PRINTINGPAGE_NAME   1003
#define IDC_GRDSETTINGS_PRINTINGPAGE_ADDNAME   1004
#define IDC_GRDSETTINGS_PRINTINGPAGE_REMOVENAME   1005
#define IDC_GRDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES   1006
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES   1007
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC   1008
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE   1009
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS   1010
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND   1011
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL   1012
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS   1013
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT   1014
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE   1015
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE   1016
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_STATIC   1017
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER   1018
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS   1019
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC   1020
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT   1021
#define IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS   1022

// Specify the graphic display settings printing page related limits
#define GRDSETTINGSPRINTINGPAGE_MINIMUMSCALE   1
#define GRDSETTINGSPRINTINGPAGE_MAXIMUMSCALE   100
#define GRDSETTINGSPRINTINGPAGE_DEFAULTSCALE   100

class CGRDSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CGRDSettingsPrintingPage)

	// Construction
public:
	CGRDSettingsPrintingPage();

	// Attributes
private:
	CGRDPrintJobs  m_pJobs[2];
private:
	CGRDSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CGRDSettingsPrintingPage)
	enum { IDD = IDD_GRD_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CGRDPrintJobs &pJobs) CONST;

	class CGRDSettingsDialog *GetParentDialog() CONST;
	class CGRDWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CGRDPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGRDSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CGRDPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGRDSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnAddName();
	afx_msg void OnRemoveName();
	afx_msg void OnRemoveAllNames();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnPrintColorLegend();
	afx_msg void OnPrintUnderlineOOL();
	afx_msg void OnPrintNoColors();
	afx_msg void OnPrintAutomaticScale();
	afx_msg void OnPrintFixedScale();
	afx_msg void OnSpinchangePrintFixedScale();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsPrintJobsPage dialog

#define IDC_GRDSETTINGS_PRINTJOBSPAGE_DETAILS   1001
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC   1002
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS   1003
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB   1004
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC   1005
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS   1006
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_REMOVEJOB   1007
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR   1008
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME   1009
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME   1010
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME   1011
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC   1012
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME   1013
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT   1014
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT   1015
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC   1016
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEXPIRATION   1017
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION   1018
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC   1019
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE   1020
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME  1021
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC   1022
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME   1023
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC   1024
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES   1025
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC   1026
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES   1027
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME   1028
#define IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME   1029

// Specify the graphic display settings print jobs page related repetition types
#define GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY   1
#define GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY   2
// Specify the graphic display settings print jobs page related limits
#define GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL   1
#define GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL   MINUTESPERHOUR
#define GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES   1
#define GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES   10000
#define GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES   10

class CGRDSettingsPrintJobsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CGRDSettingsPrintJobsPage)

	// Construction
public:
	CGRDSettingsPrintJobsPage();

	// Attributes
private:
	CGRDPrintJobs  m_pJobs[2];

	// Dialog Data
	//{{AFX_DATA(CGRDSettingsPrintJobsPage)
	enum { IDD = IDD_GRD_SETTINGS_PRINTJOBSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CGRDPrintJobs &pJobs) CONST;

	class CGRDSettingsDialog *GetParentDialog() CONST;
	class CGRDWnd *GetParentDisplay() CONST;

private:
	BOOL EnumJobs();
	BOOL EnumEvents();

	VOID ShowJobInfo();
	BOOL CheckJobInfo() CONST;
	CGRDPrintJobInfo *FindJobInfo(BOOL bActive = FALSE) CONST;

	VOID SetJobRepetitionInfo();
	UINT GetJobRepetitionType() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGRDSettingsPrintJobsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CGRDPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGRDSettingsPrintJobsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddJob();
	afx_msg void OnRemoveJob();
	afx_msg void OnSelchangeDefinedJob();
	afx_msg void OnSelchangeActiveJob();
	afx_msg void OnPrintAtTime();
	afx_msg void OnPrintAtDailyTime();
	afx_msg void OnPrintAtEvent();
	afx_msg void OnPrintAtExpiration();
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
// CGRDSettingsTabCtrl window

class CGRDSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CGRDSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsDialog

class CGRDSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CGRDSettingsDialog)

	// Construction
public:
	CGRDSettingsDialog();

	// Attributes
private:
	CGRDSettingsTabCtrl  m_wndTabCtrl;
	CGRDSettingsLayoutPage  m_pageLayout;
	CGRDSettingsChartPage  m_pageChart;
	CGRDSettingsParametersPage  m_pageParameters;
	CGRDSettingsRetrievingPage  m_pageRetrieving;
	CGRDSettingsPrintingPage  m_pagePrinting;
	CGRDSettingsPrintJobsPage  m_pagePrintJobs;

	// Operations
public:
	BOOL GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayoutColors(CUIntArray &nColors) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutValuesFont(LPLOGFONT pValuesFont) CONST;
	BOOL GetLayoutAxesFont(LPLOGFONT pAxesFont) CONST;
	BOOL GetLayoutInvalidDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutBadDataMode(BOOL &bEnable) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetRetrieveFileName(CString &szFileName) CONST;
	BOOL IsRetrievingModified() CONST;

	BOOL GetPrintJobs(CGRDPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CGRDOpenDialog *GetParentDialog() CONST;
	class CGRDWnd *GetParentDisplay() CONST;

private:
	BOOL CheckLayout(CGRDLayout &cLayout) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDSettingsDialog)
public:
	virtual BOOL OnDataExchange(HWND hPage, CONST CGRDLayout &cLayout);
	virtual BOOL OnDataExchange(HWND hPage, CONST CGRDPrintJobs &pJobs);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDSettingsDialog)
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
// CGRDLinkagesDialog dialog

#define IDC_GRD_LINKAGES_DETAILS   1001
#define IDC_GRD_LINKAGES_NAME_STATIC   1002
#define IDC_GRD_LINKAGES_NAME   1003
#define IDC_GRD_LINKAGES_DISPLAYS_STATIC  1004
#define IDC_GRD_LINKAGES_DISPLAYS   1005
#define IDC_GRD_LINKAGES_LIST_STATIC   1006
#define IDC_GRD_LINKAGES_LIST   1007
#define IDC_GRD_LINKAGES_ADD   1008
#define IDC_GRD_LINKAGES_REMOVE   1009
#define IDC_GRD_LINKAGES_REMOVEALL   1010
#define IDC_GRD_LINKAGES_HELP   1011

class CGRDLinkagesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CGRDLinkagesDialog)

	// Construction
public:
	CGRDLinkagesDialog();   // standard constructor

	// Attributes
private:
	CPtrArray  m_pDisplays[3];

	// Dialog Data
	//{{AFX_DATA(CGRDLinkagesDialog)
	enum { IDD = IDD_GRD_LINKAGES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CGRDWnd *GetParent() CONST;

private:
	BOOL EnumDisplays();

	INT FindDisplay(LPCTSTR pszName, BOOL bLinked = FALSE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDLinkagesDialog)
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
	//{{AFX_MSG(CGRDLinkagesDialog)
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
// CGRDParametersCalibrationPage dialog

#define IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC   1007
#define IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS   1008
#define IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1009
#define IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS   1010

class CGRDParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CGRDParametersCalibrationPage)

	// Construction
public:
	CGRDParametersCalibrationPage();

	// Attributes
private:
	INT  m_nCalTableID;
	ULONGLONG  m_nCalTableType;
	CUIntArray  m_nCalTableRefs;
	CUIntArray  m_nCalValidityRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CGRDParametersCalibrationPage)
	enum { IDD = IDD_GRD_PARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter);
	VOID ShowCalibrationInfo();

	class CGRDParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGRDParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGRDParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDParametersScalingPage dialog

#define IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_STATIC   1001
#define IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM_STATIC   1002
#define IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM   1003
#define IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM_STATIC   1004
#define IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM   1005
#define IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_REFRESH   1006
#define IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_STATIC   1007
#define IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_LOW_STATIC   1008
#define IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_LOW   1009
#define IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW_STATIC   1010
#define IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW   1011
#define IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_HIGH_STATIC   1012
#define IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_HIGH   1013
#define IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH_STATIC   1014
#define IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH   1015
#define IDC_GRD_PARAMETERS_SCALINGPAGE_MARGINS_STATIC   1016
#define IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER   1017
#define IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT   1018
#define IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT_STATIC   1019
#define IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER   1020
#define IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT   1021
#define IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT_STATIC   1022
#define IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC   1023
#define IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES_STATIC   1024
#define IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES   1025
#define IDC_GRD_PARAMETERS_SCALINGPAGE_RESET   1026
#define IDC_GRD_PARAMETERS_SCALINGPAGE_DEFAULT   1027

// Specify the graphic display parameters scaling page related limits
#define GRDSCALINGPAGE_MARGIN_MINIMUM   0
#define GRDSCALINGPAGE_MARGIN_MAXIMUM   100
#define GRDSCALINGPAGE_MARGIN_DEFAULT   10
#define GRDSCALINGPAGE_AUTOSCALEDELAY_MINIMUM   0
#define GRDSCALINGPAGE_AUTOSCALEDELAY_MAXIMUM   MINUTESPERDAY
#define GRDSCALINGPAGE_AUTOSCALEDELAY_DEFAULT   1

class CGRDParametersScalingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CGRDParametersScalingPage)

	// Construction
public:
	CGRDParametersScalingPage();

	// Attributes
private:
	INT  m_nIndex;
	CString  m_szRange[2];
	CGRDLayout  m_cLayout[3];

	// Dialog Data
	//{{AFX_DATA(CGRDParametersScalingPage)
	enum { IDD = IDD_GRD_PARAMETERS_SCALINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL SetParameters(CONST CGRDLayout &cLayout);
	BOOL GetParameters(CGRDLayout &cLayout) CONST;

	VOID ShowParameterInfo(INT nIndex = -1);
	VOID ShowParameterInfo(CONST CGRDParameterSamples &pSamples, INT nIndex);
	VOID RefreshParameterInfo();
	VOID RefreshParameterInfo(CONST CGRDParameterSamples &pParameterSamples, INT nIndex);

	class CGRDParametersFolder *GetParent() CONST;

private:
	BOOL ConvertRangeValues(LPCTSTR pszMinimum, LPCTSTR pszMaximum, double &fMinimum, double &fMaximum) CONST;
	VOID ConvertRangeValues(CONST CGRDLayoutParameter *pParameter, double fMinimum, double fMaximum, CString &szMinimum, CString &szMaximum) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGRDParametersScalingPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL IsModified(INT nIndex, BOOL bDefault) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGRDParametersScalingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnRefresh();
	afx_msg void OnReset();
	afx_msg void OnDefault();
	afx_msg void OnUpperMargin();
	afx_msg void OnLowerMargin();
	afx_msg void OnAutoscale();
	afx_msg void OnEditchangeUpperMargin();
	afx_msg void OnEditchangeLowerMargin();
	afx_msg void OnSpinchangeUpperMargin();
	afx_msg void OnSpinchangeLowerMargin();
	afx_msg void OnSpinchangeAutoscaleDelay();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDParametersFolderTabCtrl window

class CGRDParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CGRDParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CGRDParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDParametersFolder

class CGRDParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CGRDParametersFolder)

	// Construction
public:
	CGRDParametersFolder();

	// Attributes
private:
	CGRDParametersFolderTabCtrl  m_wndTabCtrl;
	CGRDParametersCalibrationPage  m_pageCalibration;
	CGRDParametersScalingPage  m_pageScaling;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	BOOL SetParameters(CONST CGRDLayout &cLayout);
	BOOL GetParameters(CGRDLayout &cLayout) CONST;

	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter, CONST CGRDParameterSamples &pParameterSamples, INT nIndex);
	VOID RefreshParameterInfo();
	VOID RefreshParameterInfo(CONST CTMParameter *pTMParameter, CONST CGRDParameterSamples &pParameterSamples, INT nIndex);

	class CGRDParametersDialog *GetParentDialog() CONST;
	class CGRDWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDParametersDialog dialog

#define IDC_GRD_PARAMETERS_DETAILS   1001
#define IDC_GRD_PARAMETERS_ITEM_STATIC   1002
#define IDC_GRD_PARAMETERS_ITEM   1003
#define IDC_GRD_PARAMETERS_FOLDER   1004
#define IDC_GRD_PARAMETERS_HELP   1005

class CGRDParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CGRDParametersDialog)

	// Construction
public:
	CGRDParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szParameter;
private:
	CGRDParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CGRDParametersDialog)
	enum { IDD = IDD_GRD_PARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter);

	BOOL SetParameters(CONST CGRDLayout &cLayout);
	BOOL GetParameters(CGRDLayout &cLayout) CONST;

	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter, CONST CGRDParameterSamples &pParameterSamples, INT nIndex);
	VOID RefreshParameterInfo();
	VOID RefreshParameterInfo(CONST CTMParameter *pTMParameter, CONST CGRDParameterSamples &pParameterSamples, INT nIndex);

	class CGRDWnd *GetParent() CONST;

private:
	BOOL EnumParameters();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDParametersDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDParametersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDRetrieveDialog dialog

#define IDC_GRD_RETRIEVE_DETAILS   1001
#define IDC_GRD_RETRIEVE_TITLE_STATIC   1002
#define IDC_GRD_RETRIEVE_TITLE   1003
#define IDC_GRD_RETRIEVE_TYPE_STATIC   1004
#define IDC_GRD_RETRIEVE_TYPE   1005
#define IDC_GRD_RETRIEVE_REALTIME   1006
#define IDC_GRD_RETRIEVE_HISTORY   1007
#define IDC_GRD_RETRIEVE_HISTORY_START_STATIC   1008
#define IDC_GRD_RETRIEVE_HISTORY_STARTTIME   1009
#define IDC_GRD_RETRIEVE_HISTORY_EXACTTIME   1010
#define IDC_GRD_RETRIEVE_HISTORY_STOP_STATIC   1011
#define IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME   1012
#define IDC_GRD_RETRIEVE_HISTORY_STOPTIME   1013
#define IDC_GRD_RETRIEVE_HISTORY_STOPBYEND   1014
#define IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME   1015
#define IDC_GRD_RETRIEVE_HISTORY_PLAYBACKMODE   1016
#define IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC   1017
#define IDC_GRD_RETRIEVE_HISTORY_PSEUDOREALTIME   1018
#define IDC_GRD_RETRIEVE_HISTORY_MANUAL   1019
#define IDC_GRD_RETRIEVE_HISTORY_SPEED_STATIC   1020
#define IDC_GRD_RETRIEVE_HISTORY_SPEED   1021
#define IDC_GRD_RETRIEVE_HISTORY_SLOW   1022
#define IDC_GRD_RETRIEVE_HISTORY_FAST   1023
#define IDC_GRD_RETRIEVE_HISTORY_INTERVAL   1024
#define IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME   1025
#define IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME_STATIC   1026
#define IDC_GRD_RETRIEVE_HELP   1027

// Specify the graphic display retrieve dialog related limits
#define GRDRETRIEVEDIALOG_MINIMUMINTERVAL   1
#define GRDRETRIEVEDIALOG_MAXIMUMINTERVAL   MINUTESPERWEEK
#define GRDRETRIEVEDIALOG_DEFAULTINTERVAL   5

class CGRDRetrieveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CGRDRetrieveDialog)

	// Construction
public:
	CGRDRetrieveDialog();   // standard constructor

	// Attributes
private:
	CString  m_szTitle;
	CString  m_szType;

	// Dialog Data
	//{{AFX_DATA(CGRDRetrieveDialog)
	enum { IDD = IDD_GRD_RETRIEVE_DIALOG };
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

	class CGRDOpenDialog *GetParentDialog() CONST;
	class CGRDWnd *GetParentDisplay() CONST;

private:
	BOOL SetRetrieveInfo();
	BOOL GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDRetrieveDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDRetrieveDialog)
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
// CGRDImportDialog dialog

#define IDC_GRD_IMPORT_DETAILS   1001
#define IDC_GRD_IMPORT_FILENAME_STATIC   1002
#define IDC_GRD_IMPORT_FILENAME   1003
#define IDC_GRD_IMPORT_BROWSE   1004
#define IDC_GRD_IMPORT_INSPECT   1005
#define IDC_GRD_IMPORT_DIRECTORY_STATIC   1006
#define IDC_GRD_IMPORT_DIRECTORY   1007
#define IDC_GRD_IMPORT_ADD   1008
#define IDC_GRD_IMPORT_ADDALL   1009
#define IDC_GRD_IMPORT_ATTENTION   1010
#define IDC_GRD_IMPORT_ATTENTION_TEXT   1011
#define IDC_GRD_IMPORT_LIST_STATIC   1012
#define IDC_GRD_IMPORT_LIST   1013
#define IDC_GRD_IMPORT_REMOVE   1014
#define IDC_GRD_IMPORT_REMOVEALL   1015
#define IDC_GRD_IMPORT_HELP   1016

class CGRDImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CGRDImportDialog)

	// Construction
public:
	CGRDImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CGRDLayouts  m_pDisplays[3];

	// Operations
private:
	VOID EnumDisplays();

	// Dialog Data
	//{{AFX_DATA(CGRDImportDialog)
	enum { IDD = IDD_GRD_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDImportDialog)
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
	//{{AFX_MSG(CGRDImportDialog)
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
// CGRDExportDialog dialog

#define IDC_GRD_EXPORT_DETAILS   1001
#define IDC_GRD_EXPORT_DIRECTORY_STATIC   1002
#define IDC_GRD_EXPORT_DIRECTORY   1003
#define IDC_GRD_EXPORT_ADD   1004
#define IDC_GRD_EXPORT_ADDALL   1005
#define IDC_GRD_EXPORT_LIST_STATIC   1006
#define IDC_GRD_EXPORT_LIST   1007
#define IDC_GRD_EXPORT_REMOVE   1008
#define IDC_GRD_EXPORT_REMOVEALL   1009
#define IDC_GRD_EXPORT_FILENAME_STATIC   1010
#define IDC_GRD_EXPORT_FILENAME   1011
#define IDC_GRD_EXPORT_BROWSE   1012
#define IDC_GRD_EXPORT_HELP   1013

class CGRDExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CGRDExportDialog)

	// Construction
public:
	CGRDExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CGRDLayouts  m_pDisplays[2];

	// Operations
private:
	BOOL EnumDisplays();

	// Dialog Data
	//{{AFX_DATA(CGRDExportDialog)
	enum { IDD = IDD_GRD_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDExportDialog)
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
	//{{AFX_MSG(CGRDExportDialog)
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
// CGRDFindDialog dialog

#define IDC_GRD_FIND_KEY_STATIC   1001
#define IDC_GRD_FIND_KEY   1002
#define IDC_GRD_FIND_VALUE_STATIC   1003
#define IDC_GRD_FIND_VALUE   1004
#define IDC_GRD_FIND_RESULTS_STATIC   1005
#define IDC_GRD_FIND_RESULTS   1006
#define IDC_GRD_FIND_SEARCH   1007
#define IDC_GRD_FIND_OPEN   1008
#define IDC_GRD_FIND_HELP   1009

class CGRDFindDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CGRDFindDialog)

	// Construction
public:
	CGRDFindDialog();   // standard constructor

	// Attributes
private:
	INT  m_nType;
	CGRDLayouts  m_pLayouts[2];
	CStringArray  m_szDescriptions;

	// Dialog Data
	//{{AFX_DATA(CGRDFindDialog)
	enum { IDD = IDD_GRD_FIND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, INT nType, CGRDLayout &cLayout);

	class CGRDWnd *GetParent() CONST;

private:
	BOOL EnumSearchKeys();
	BOOL EnumSearchValues();

	VOID DoFindByParameter(LPCTSTR pszParameter);
	VOID DoFindByParameters(CONST CStringArray &szParameters);
	VOID DoFindByDescription(LPCTSTR pszDescription);
	VOID DoFindByDescriptions(CONST CStringArray &szDescriptions);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDFindDialog)
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
// CGRDOpenDialog dialog

#define IDC_GRD_OPEN_DETAILS   1001
#define IDC_GRD_OPEN_DISPLAY_STATIC   1002
#define IDC_GRD_OPEN_DISPLAY   1003
#define IDC_GRD_OPEN_SETTINGS   1004
#define IDC_GRD_OPEN_FIND   1005
#define IDC_GRD_OPEN_TYPE   1006
#define IDC_GRD_OPEN_TYPE_NORMAL   1007
#define IDC_GRD_OPEN_TYPE_TEMPORARY   1008
#define IDC_GRD_OPEN_REMOVE   1009
#define IDC_GRD_OPEN_MODE   1010
#define IDC_GRD_OPEN_MODE_REALTIME   1011
#define IDC_GRD_OPEN_MODE_HISTORY   1012
#define IDC_GRD_OPEN_HELP   1013

class CGRDOpenDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CGRDOpenDialog)

	// Construction
public:
	CGRDOpenDialog();   // standard constructor

	// Attributes
private:
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	BOOL  m_bLayoutBadData;
	BOOL  m_bLayoutToolTips;
	BOOL  m_bLayoutInvalidData;
	LOGFONT  m_fntLayoutTitle;
	LOGFONT  m_fntLayoutItems;
	LOGFONT  m_fntLayoutValues;
	LOGFONT  m_fntLayoutAxes;
	CString  m_szRetrieveFileName;
	CTimeKey  m_tRetrieveStartTime;
	CTimeKey  m_tRetrieveStopTime;
	CTimeSpan  m_tRetrieveInterval;
	CUIntArray  m_nLayoutColors;
	CUIntArray  m_nLayoutColumns;
	CGRDPrintJobs  m_pPrintJobs;
	CGRDLayout  m_cLayout;
private:
	CGRDSettingsDialog  m_dlgSettings;
	CGRDRetrieveDialog  m_dlgRetrievals;
	CGRDFindDialog  m_dlgFindDisplay;

	// Dialog Data
	//{{AFX_DATA(CGRDOpenDialog)
	enum { IDD = IDD_GRD_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	CString GetTitle() CONST;
	UINT GetType() CONST;
	UINT GetMode() CONST;

	BOOL GetLayout(CGRDLayout &cLayout) CONST;
	BOOL GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayoutColors(CUIntArray &nColors) CONST;
	BOOL GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutValuesFont(LPLOGFONT pValuesFont) CONST;
	BOOL GetLayoutAxesFont(LPLOGFONT pAxesFont) CONST;
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

	BOOL GetPrintJobs(CGRDPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CGRDWnd *GetParent() CONST;

private:
	VOID EnumLayouts();

	BOOL FindLayout() CONST;
	BOOL FindLayout(CGRDLayout &cLayout) CONST;

	BOOL InitializeLayout(CGRDLayout &cLayout) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDOpenDialog)
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
	//{{AFX_MSG(CGRDOpenDialog)
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
// CGRDRetrieveThread thread

// Specify the graphic display retrieve thread action codes
#define GRDRETRIEVETHREAD_ACTION_STOP   0
#define GRDRETRIEVETHREAD_ACTION_AUTOFORWARD   1
#define GRDRETRIEVETHREAD_ACTION_MANUALFORWARD   2
#define GRDRETRIEVETHREAD_ACTION_PSEUDOREALTIME   3
#define GRDRETRIEVETHREAD_ACTION_TYPES   4

class CGRDRetrieveThread : public CThread
{
	DECLARE_DYNCREATE(CGRDRetrieveThread)

	// Construction
public:
	CGRDRetrieveThread();

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
	HANDLE  m_hAction[GRDRETRIEVETHREAD_ACTION_TYPES];
private:
	CHistoryTMProcessEngine  m_cTMProcessEngine;
	CTMEnvironment  m_cTMEnvironment;

	// Operations
public:
	BOOL Start(class CGRDWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveManualForward, HANDLE bRetrievePseudoRealtime);
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
	//{{AFX_VIRTUAL(CGRDRetrieveThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDRetrieveThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDPrintThread thread

class CGRDPrintThread : public CThread
{
	DECLARE_DYNCREATE(CGRDPrintThread)

	// Construction
public:

	// Attributes
private:
	CGRDPrintJobs  m_pPrintJobs;
private:
	CEvent  m_cEvent;

	// Operations
public:
	BOOL Start(class CGRDWnd *pParentWnd);
	BOOL Stop();

	BOOL SetPrintJobs(CONST CGRDPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CGRDPrintJobs &pPrintJobs) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDPrintThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDPrintThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDToolBar window

class CGRDToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CGRDToolBar)

	// Construction
public:
	CGRDToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDStatusBar window

class CGRDStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CGRDStatusBar)

	// Construction
public:
	CGRDStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CGRDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDToolTip window

class CGRDToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CGRDToolTip)

	// Construction
public:
	CGRDToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDRulerTimeTip window

class CGRDRulerTimeTip : public CWnd
{
	DECLARE_DYNCREATE(CGRDRulerTimeTip)

	// Construction
public:
	CGRDRulerTimeTip();

	// Attributes
private:
	CFont  m_cFont;
	CString  m_szRange;
	CString  m_szDuration;
	CUIntArray  m_nTabs;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);
	BOOL Destroy();

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;

	VOID SetTabstops(CONST CUIntArray &nTabs);
	INT GetTabstops(CUIntArray &nTabs) CONST;

	VOID SetRange(LPCTSTR pszRange);
	CString GetRange() CONST;
	VOID SetDuration(LPCTSTR pszDuration);
	CString GetDuration() CONST;

	VOID Update(CONST POINT &point, LPCTSTR pszRange, LPCTSTR pszDuration);

private:
	CSize CalcExtent(LPCTSTR pszRange, LPCTSTR pszDuration, CPoint &ptRange, CPoint &ptDuration);
	VOID CalcTabstops(LPCTSTR pszRange, LPCTSTR pszDuration);

	VOID DrawContent(CDC *pDC);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDRulerTimeTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDRulerTimeTip)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDRulerTip window

// Specify the graphic display ruler tip related settings
#define GRDRULERTIP_TICKSINTERVAL   5

class CGRDRulerTip : public CWnd
{
	DECLARE_DYNCREATE(CGRDRulerTip)

	// Construction
public:
	CGRDRulerTip();

	// Attributes
private:
	CFont  m_cFont;
	CPoint  m_ptTime;
	CTimeTag  m_tTime[2];
	CGRDRulerTimeTip  m_wndTimeTip;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime);
	BOOL Destroy();

	BOOL SetFont(CFont *pFont);
	BOOL GetFont(CFont *pFont) CONST;
	BOOL SetTimeTipFont(CFont *pFont);
	BOOL GetTimeTipFont(CFont *pFont) CONST;

	BOOL SetRange(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime);
	BOOL GetRange(CTimeTag &tStartTime, CTimeTag &tStopTime) CONST;

	VOID Update();
	VOID Update(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime, CONST POINT &point);

private:
	BOOL CalcRange(CONST POINT &point, CTimeTag &tStartTime, CTimeTag &tStopTime) CONST;

	VOID DrawContent(CDC *pDC);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDRulerTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDRulerTip)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDView window

class CGRDView : public CTextView
{
	DECLARE_DYNCREATE(CGRDView)

	// Construction
public:
	CGRDView();

	// Attributes
private:
	CGRDLayout  m_cLayout;
	CUIntArray  m_nLayoutSlots;
	CUIntArray  m_nLayoutColors;
	CUIntArray  m_nLayoutColumns;
	CByteArray  m_nLayoutStatus;
	CByteArray  m_bLayoutValues;
	CGRDMarkers  m_pLayoutMarkers;
	CStringArray  m_szLayoutTables;
	CTMParameters  m_pLayoutValues;
	LOGFONT  m_lfLayoutDefault[4];
	CSize  m_sizeLayoutDefault;
	CSize  m_sizeLayoutFont;
	CFont  m_cLayoutFont[2];
	BOOL  m_bLayoutFont;
private:
	CPoint  m_ptGraph;
	CTimeTag  m_tGraph[3];
	CGRDParameterPlots  m_cGraphPlots;
	CUIntArray  m_nGraphTimerIDs;
	CByteArray  m_cGraphBits;
	BOOL  m_bGraphUpdate;
private:
	CGRDRulerTip  m_wndRulerTip;
	CGRDToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bInvalidDataMode;
	BOOL  m_bBadDataMode;
	BOOL  m_bToolTipMode;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle);

	BOOL SetLayout(CONST CGRDLayout &cLayout);
	BOOL SetLayout(CONST CGRDLayout &cLayout, UINT nColumns);
	BOOL SetLayout(CONST CGRDLayout &cLayout, CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CGRDLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, BOOL bAdjust = FALSE);
	BOOL GetLayout(CGRDLayout &cLayout) CONST;
	BOOL GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetTitleFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetTitleFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetItemsFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetItemsFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetItemsFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetValuesFont(CFont *pFont = NULL, BOOL bDefault = TRUE);
	BOOL SetValuesFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetValuesFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetValuesFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetAxesFont(CFont *pFont = NULL, BOOL bDefault = TRUE);
	BOOL SetAxesFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetAxesFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetAxesFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;

	BOOL SetMarkers(CONST CGRDMarkers &pMarkers);
	BOOL GetMarkers(CGRDMarkers &pMarkers) CONST;

	BOOL SetOolColors(CONST CUIntArray &nColors);
	BOOL GetOolColors(CUIntArray &nColors) CONST;

	BOOL InitializeScalingData();
	BOOL SetScalingData(CONST CByteArray &nScalingData);
	BOOL GetScalingData(CByteArray &nScalingData) CONST;

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

	VOID SetHoldFlag(BOOL bEnable = FALSE);
	BOOL GetHoldFlag() CONST;
	BOOL HasHoldFlag() CONST;

	BOOL GetParameterInfo(LPCTSTR pszTag, INT nIndex, CTMParameter *pTMParameter, CGRDParameterSamples &pParameterSamples) CONST;
	BOOL HasParameters() CONST;

	VOID ReduceFonts(BOOL bRestore = FALSE);
	BOOL CanReduceFonts(BOOL bRestore = FALSE) CONST;
	VOID ReducePlotArea(BOOL bRestore = FALSE);

	BOOL GetPrintProperties(CGRDLayout &cLayout, CStringArray &szColumns, CStringArray &szContents, CTMParameters &pValues, CUIntArray &nOOLColors, LOGFONT *pTitleFont, CPtrArray &pItemsFonts, CMetaFileDC &cMetaDC, CSize &sizeImage, UINT &nImageIndent) CONST;

	class CGRDWnd *GetParent() CONST;

private:
	VOID DrawImage();
	VOID DrawImage(CDC *pDC);
	VOID DrawGraph(CDC *pDC);
	VOID DrawLegend(CDC *pDC);
	VOID DrawSlider(CDC *pDC);
	VOID DrawSymbol(CDC *pDC, INT nSymbol, INT nWidth, COLORREF nColor, CONST POINT &pt, BOOL bFirst);
	VOID DrawSample(CDC *pDC, CONST CGRDLayout &cLayout, INT nPlot, CGRDParameterSample *pParameterSample, CGRDParameterSample *pPreviousSample = NULL);
	VOID DrawSample(CDC *pDC, CONST CGRDLayout &cLayout, INT nPlot, CONST CPtrArray &pParameterSamples, CGRDParameterSample *pPreviousSample = NULL);
	VOID DrawSample(CDC *pDC, CONST CGRDLayout &cLayout, INT nXPlot, INT nYPlot, CGRDParameterSample *pParameterXSample, CGRDParameterSample *pParameterYSample, CGRDParameterSample *pPreviousXSample = NULL, CGRDParameterSample *pPreviousYSample = NULL);

	VOID UpdateGraph();
	VOID UpdateGraph(CDC *pDC);
	VOID UpdateGraph(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime);
	VOID UpdateGraphScaling();

	VOID RestartGraph(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime);
	VOID ScrollGraph(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime, CONST CTimeTag &tTime);
	VOID OverwriteGraph(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime, CONST CTimeTag &tTime);

	CPoint GetImageOffset() CONST;
	CPoint GetGraphOffset() CONST;
	CRect GetImagePosition() CONST;
	CRect GetGraphPosition() CONST;
	CRect GetLegendPosition() CONST;
	CSize GetGraphSize() CONST;
	CSize GetAxesStubs() CONST;

	BOOL FindSamplePosition(CONST POINT &point) CONST;
	CGRDLayoutParameter *FindSamplePosition(CONST POINT &point, CGRDParameterSample &cSample) CONST;

	CSize CalcPlotAreaExtent() CONST;
	CPoint CalcSamplePosition(INT nPlot, CONST CGRDParameterSample *pParameterSample, double fValue, CRect &rPlot) CONST;
	CPoint CalcSamplePosition(INT nPlot, CONST CGRDParameterSample *pParameterSample, double *pMinValues, double *pMaxValues, double fValue, CRect &rPlot) CONST;
	CPoint CalcSamplePosition(INT nXPlot, INT nYPlot, double fXValue, double fYValue, CRect &rPlot) CONST;
	CPoint CalcSamplePosition(CONST CTimeTag &tTime) CONST;
	CSize CalcSampleSymbolSize(INT nWidth) CONST;
	INT CalcAxesSymbolWidth(LPCTSTR pszText) CONST;
	INT CalcAxesSymbolHeight(LPCTSTR pszText = NULL) CONST;

	VOID CreateLinePen(CDC *pDC, CONST SIZE &sizeGraph, INT nStyle, INT nWidth, COLORREF nColor, LOGBRUSH *pBrush);
	VOID DestroyLinePen(LOGBRUSH *pBrush);

	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;
	COLORREF LookupColumnColor(UINT nColumn, BYTE nStatus = 0) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnWidth(UINT nColumn, LPCTSTR pszText);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);
	CSize CalcColumnsWidth(CUIntArray &nWidths);

	BOOL ConvertColumnToIndex(UINT nColumn, INT &nIndex) CONST;

	VOID ConvertAxesRangeValues(CONST CGRDLayoutParameter *pParameter, double fMinimum, double fMaximum, CString &szMinimum, CString &szMaximum) CONST;

	CString ConstructToolTipTitle() CONST;
	CString ConstructToolTipTitle(CONST CGRDLayoutParameter *pParameter, UINT nTip) CONST;
	CString ConstructToolTipTitle(CONST CGRDLayoutParameter *pParameter) CONST;
	CString ConstructToolTipText() CONST;
	CString ConstructToolTipText(CONST CGRDLayoutParameter *pParameter, INT nOccurrence, UINT nTip) CONST;
	CString ConstructToolTipText(CONST CGRDLayoutParameter *pParameter, CONST CGRDParameterSample &cSample) CONST;

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDView)
public:
	virtual VOID RecalcLayout();
public:
	virtual VOID DrawContent(CDC *pDC);
public:
	virtual BOOL CalcContentExtent(CSize &size) CONST;
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
	//{{AFX_MSG(CGRDView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDWnd frame

// Specify the graphic display types
#define GRD_TYPE_NORMAL   1
#define GRD_TYPE_TEMPORARY   2
// Specify the graphic display title items
#define GRD_TITLEITEM_ID   (1<<0)
#define GRD_TITLEITEM_DESCRIPTION   (1<<1)
#define GRD_TITLEITEM_VALUE   (1<<2)
#define GRD_TITLEITEM_UNIT   (1<<3)
#define GRD_TITLEITEM_RANGE   (1<<4)
#define GRD_TITLEITEM_LINE   (1<<5)
#define GRD_TITLEITEM_CHANGETMUNIT   (1<<6)
#define GRD_TITLEITEM_CHANGETIME   (1<<7)
#define GRD_TITLEITEM_UPDATETMUNIT   (1<<8)
#define GRD_TITLEITEM_UPDATETIME   (1<<9)
#ifndef RC_INVOKED
#define GRD_TITLEITEMS_DEFAULT   (GRD_TITLEITEM_ID | GRD_TITLEITEM_DESCRIPTION | GRD_TITLEITEM_VALUE | GRD_TITLEITEM_UNIT | GRD_TITLEITEM_RANGE | GRD_TITLEITEM_LINE)
#define GRD_TITLEITEMS_ALL   (GRD_TITLEITEMS_DEFAULT | GRD_TITLEITEM_CHANGETMUNIT | GRD_TITLEITEM_CHANGETIME | GRD_TITLEITEM_UPDATETMUNIT | GRD_TITLEITEM_UPDATETIME)
#endif
// Specify the graphic display retrieval modes
#define GRD_RETRIEVE_EXACTTIME   (1<<0)
#define GRD_RETRIEVE_STOPBYTIME   (1<<1)
#define GRD_RETRIEVE_STOPBYEND   (1<<2)
#define GRD_RETRIEVE_STOPBYREALTIME   (1<<3)
#define GRD_RETRIEVE_STOPPED   (1<<4)
#define GRD_RETRIEVE_RELATIVE   (1<<5)
#define GRD_RETRIEVE_AUTOFORWARD   (1<<6)
#define GRD_RETRIEVE_MANUALFORWARD   (1<<7)
#define GRD_RETRIEVE_PSEUDOREALTIME   (1<<8)
// Specify the graphic display print modes
#define GRD_PRINT_COLORLEGEND   (1<<0)
#define GRD_PRINT_UNDERLINEOOL   (1<<1)
#define GRD_PRINT_NOCOLORS   (1<<2)
#define GRD_PRINT_AUTOSCALE   (1<<3)
#define GRD_PRINT_FIXEDSCALE   (1<<4)
#define GRD_PRINT_CLEARCOMMENTS   (1<<5)
#define GRD_PRINT_ATTIME   (1<<6)
#define GRD_PRINT_ATDAILYTIME   (1<<7)
#define GRD_PRINT_ATEVENT   (1<<8)
#define GRD_PRINT_ATEXPIRATION   (1<<9)
#define GRD_PRINT_REPEATBYINTERVAL   (1<<10)
#define GRD_PRINT_REPEATSTOPBYCOUNT   (1<<11)
#define GRD_PRINT_REPEATSTOPBYTIME   (1<<12)
#define GRD_PRINT_DAILYREPEATSTOPBYCOUNT   (1<<13)
#define GRD_PRINT_DAILYREPEATSTOPBYTIME   (1<<14)
#define GRD_PRINT_ACTIVE   (1<<15)
// Specify the graphic display print fonts
#define GRD_PRINTFONT_TITLE   0
#define GRD_PRINTFONT_SUBTITLE   1
#define GRD_PRINTFONT_OPERATINGDETAILS   2
#define GRD_PRINTFONT_OPERATINGMODE   3
#define GRD_PRINTFONT_LISTITEMSTITLE   4
#define GRD_PRINTFONT_FOOTER   5
#define GRD_PRINTFONT_NOTICE   6
#define GRD_PRINTFONT_LOGO   7
#define GRD_PRINTFONTS   8
// Specify the graphic display OOL colors
#define GRD_OOLCOLOR_NOLIMIT   0
#define GRD_OOLCOLOR_SOFTLIMIT   1
#define GRD_OOLCOLOR_HARDLIMIT   2
#define GRD_OOLCOLOR_DELTALIMIT   3
#define GRD_OOLCOLOR_CONSISTENCYLIMIT   4
// Specify the graphic display statusbar pane identifiers
#define ID_GRD_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_GRD_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_GRD_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class CGRDWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CGRDWnd)

	// Construction
public:
	CGRDWnd();

	// Attributes
private:
	CGRDToolBar  m_wndToolBar;
	CGRDStatusBar  m_wndStatusBar;
	CGRDView  m_wndView;
private:
	CGRDOpenDialog  m_dlgOpen;
	CGRDSettingsDialog  m_dlgSettings;
	CGRDLinkagesDialog  m_dlgLinkages;
	CGRDRetrieveDialog  m_dlgRetrievals;
	CGRDParametersDialog  m_dlgParameters;
private:
	CGRDRetrieveThread  m_cRetrieveThread;
	CGRDPrintThread  m_cPrintThread;
private:
	LONG  m_bRetrieveFlag;
	UINT  m_nRetrieveMode;
	UINT  m_nRetrieveSpeed;
	CEvent  m_cRetrieveStop;
	CEvent  m_cRetrieveAutoForward;
	CEvent  m_cRetrieveManualForward;
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
	BOOL SetLayout(CONST CGRDLayout &cLayout);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CGRDLayout &cLayout, CONST CUIntArray &nColumns);
	BOOL SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(CONST CGRDLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(CString &szLayout) CONST;
	BOOL GetLayout(CGRDLayout &cLayout) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns) CONST;
	BOOL GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetTitleFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetTitleFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetItemsFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetItemsFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetItemsFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetValuesFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetValuesFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetValuesFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetValuesFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;
	BOOL SetAxesFont(CFont *pFont, BOOL bDefault = TRUE);
	BOOL SetAxesFont(CONST LOGFONT *plfFont, BOOL bDefault = TRUE);
	BOOL GetAxesFont(CFont *pFont, BOOL bDefault = TRUE) CONST;
	BOOL GetAxesFont(LOGFONT *plfFont, BOOL bDefault = TRUE) CONST;

	BOOL SetMarkers(CONST CGRDMarkers &pMarkers);
	BOOL GetMarkers(CGRDMarkers &pMarkers) CONST;

	BOOL SetOolColors(CONST CUIntArray &nColors);
	BOOL GetOolColors(CUIntArray &nColors) CONST;

	BOOL SetScalingData(CONST CByteArray &nScalingData);
	BOOL GetScalingData(CByteArray &nScalingData) CONST;

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
	BOOL GetParameterInfo(LPCTSTR pszTag, INT nIndex, CTMParameter *pTMParameter, CGRDParameterSamples &pParameterSamples) CONST;

	BOOL SetPrintJobs(CONST CGRDPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CGRDPrintJobs &pPrintJobs) CONST;
	VOID ExecutePrintJobs();

	BOOL Print(CONST CGRDPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

	CGRDWnd *Find(INT nType, UINT nMode, LPCTSTR pszName) CONST;

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

	BOOL LoadLayout(LPCTSTR pszLayout, CGRDLayout &cLayout);
	BOOL HasLayout() CONST;

	VOID SetHoldFlag(BOOL bEnable = FALSE);
	BOOL GetHoldFlag() CONST;
	BOOL HasHoldFlag() CONST;

	BOOL StartSchedulePrintJobs();
	BOOL IsSchedulingPrintJobs() CONST;
	BOOL StopSchedulePrintJobs();

	BOOL SetMarkerData(CONST CByteArray &nMarkerInfo);
	BOOL GetMarkerData(CByteArray &nMarkerInfo) CONST;

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CGRDPrintJobInfo *pJobInfo, CGRDLayout &cLayout, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szColumns, CStringArray &szContents, CTMParameters &pValues, CUIntArray &nOOLColors, LOGFONT *pTitleFont, CPtrArray &pItemsFonts, CMetaFileDC &cMetaDC, CSize &sizeImage, UINT &nImageIndent) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CGRDPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CGRDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTMParameters &pValues, CONST CUIntArray &nOOLColors, CONST LOGFONT *pTitleFont, CONST CPtrArray &pItemsFonts, CMetaFileDC &cMetaDC, CONST SIZE &sizeImage, UINT nImageIndent);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CGRDPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, CONST CGRDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CUIntArray &nOOLColors, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nTabOffset, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CONST CUIntArray &nOOLColors, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, INT nTabOffset, BOOL bCalc = FALSE);
	VOID DrawPrintDocLineSymbol(CDC &cDC, INT nSymbol, INT nWidth, COLORREF nColor, CONST POINT &pt);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(CONST CGRDLayout &cLayout) CONST;
	CString GetPrintDocOperatingDetails(CONST CGRDPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST;
	CString GetPrintDocOperatingMode(CONST CGRDPrintJobInfo *pJobInfo, CONST CUIntArray &nOOLColors) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	BOOL GetPrintDocParameterAttributes(CONST CGRDLayout &cLayout, CONST CStringArray &szColumns, CONST CTMParameters &pValues, CONST CUIntArray &nOOLColors, INT nRow, INT nColumn, UINT &nStatus, COLORREF &nColor) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST SIZE &sizeImage, INT nImageIndent, INT nScale, CONST LOGFONT *pTitleFont, CONST CPtrArray &pItemsFonts, CFont &cTitleFont, CPtrArray &cItemsFonts) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CONST CPtrArray &pItemsFonts, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CStringArray &szContents, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDWnd)
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
	virtual VOID ReducePlotArea(BOOL bRestore = FALSE);
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
	//{{AFX_MSG(CGRDWnd)
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
	afx_msg void OnHold();
	afx_msg void OnRetrievals();
	afx_msg void OnRetrieveStop();
	afx_msg void OnRetrieveAutoForward();
	afx_msg void OnRetrieveManualForward();
	afx_msg void OnRetrievePseudoRealtime();
	afx_msg void OnPrint();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLinkages(CCmdUI *pCmdUI);
	afx_msg void OnUpdateParameters(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHold(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrievals(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrieveManualForward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarModePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarTypePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __GRD_H__
