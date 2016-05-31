// TCONBOARD.H : Telecommand On-Board Software Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telecommand on-board software related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2008/04/22 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TCONBOARD_H__
#define __TCONBOARD_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesItem

// Specify the telecommand on-board buffer queues display item types
#define TCONBOARDBUFFERQUEUESITEM_TYPE_NONE   TCITEM_TYPE_NONE
#define TCONBOARDBUFFERQUEUESITEM_TYPE_FUNCTION   TCITEM_TYPE_FUNCTION
#define TCONBOARDBUFFERQUEUESITEM_TYPE_SEQUENCE   TCITEM_TYPE_SEQUENCE
#define TCONBOARDBUFFERQUEUESITEM_TYPE_PROCEDURE   TCITEM_TYPE_PROCEDURE
// Specify the telecommand on-board buffer queues display item flags
#define TCONBOARDBUFFERQUEUESITEM_CHECKFLAG_OVERRIDEPTV   TCITEM_CHECKFLAG_OVERRIDEPTV
#define TCONBOARDBUFFERQUEUESITEM_CHECKFLAG_OVERRIDEPEV   TCITEM_CHECKFLAG_OVERRIDEPEV
#define TCONBOARDBUFFERQUEUESITEM_CHECKFLAG_OVERRIDECEV   TCITEM_CHECKFLAG_OVERRIDECEV
#define TCONBOARDBUFFERQUEUESITEM_CHECKFLAG_DISABLEPTV   TCITEM_CHECKFLAG_DISABLEPTV
#define TCONBOARDBUFFERQUEUESITEM_CHECKFLAG_DISABLEPEV   TCITEM_CHECKFLAG_DISABLEPEV
#define TCONBOARDBUFFERQUEUESITEM_CHECKFLAG_DISABLECEV   TCITEM_CHECKFLAG_DISABLECEV
#define TCONBOARDBUFFERQUEUESITEM_CHECKFLAG_PREAUTHORIZED   TCITEM_CHECKFLAG_PREAUTHORIZED
#define TCONBOARDBUFFERQUEUESITEM_LINKAGEFLAG_GROUPED   TCITEM_LINKAGEFLAG_GROUPED
#define TCONBOARDBUFFERQUEUESITEM_LINKAGEFLAG_BLOCKED   TCITEM_LINKAGEFLAG_BLOCKED
#define TCONBOARDBUFFERQUEUESITEM_RELEASEFLAG_AFTERBEGIN   TCITEM_RELEASEFLAG_AFTERBEGIN
#define TCONBOARDBUFFERQUEUESITEM_RELEASEFLAG_AFTERPREVIOUS   TCITEM_RELEASEFLAG_AFTERPREVIOUS
#define TCONBOARDBUFFERQUEUESITEM_EXECUTIONFLAG_AFTERBEGIN   TCITEM_EXECUTIONFLAG_AFTERBEGIN
#define TCONBOARDBUFFERQUEUESITEM_EXECUTIONFLAG_AFTERPREVIOUS   TCITEM_EXECUTIONFLAG_AFTERPREVIOUS
#define TCONBOARDBUFFERQUEUESITEM_EXECUTIONFLAG_IMMEDIATE   TCITEM_EXECUTIONFLAG_IMMEDIATE
#define TCONBOARDBUFFERQUEUESITEM_EXECUTIONFLAG_TIMETAGGED   TCITEM_EXECUTIONFLAG_TIMETAGGED
#define TCONBOARDBUFFERQUEUESITEM_EXECUTIONFLAG_1STSTEP   TCITEM_EXECUTIONFLAG_1STSTEP
#define TCONBOARDBUFFERQUEUESITEM_EXECUTIONFLAG_2NDSTEP   TCITEM_EXECUTIONFLAG_2NDSTEP
#define TCONBOARDBUFFERQUEUESITEM_DUMPFLAG_SYNCHRONIZED   TCITEM_DUMPFLAG_SYNCHRONIZED
#define TCONBOARDBUFFERQUEUESITEM_DUMPFLAG_NOTSYNCHRONIZED   TCITEM_DUMPFLAG_NOTSYNCHRONIZED
#define TCONBOARDBUFFERQUEUESITEM_ACKNOWLEDGEFLAG_ACCEPTANCE   TCITEM_ACKNOWLEDGEFLAG_ACCEPTANCE
#define TCONBOARDBUFFERQUEUESITEM_ACKNOWLEDGEFLAG_START   TCITEM_ACKNOWLEDGEFLAG_START
#define TCONBOARDBUFFERQUEUESITEM_ACKNOWLEDGEFLAG_PROGRESS   TCITEM_ACKNOWLEDGEFLAG_PROGRESS
#define TCONBOARDBUFFERQUEUESITEM_ACKNOWLEDGEFLAG_COMPLETION   TCITEM_ACKNOWLEDGEFLAG_COMPLETION
#define TCONBOARDBUFFERQUEUESITEM_ACKNOWLEDGEFLAG_ALL   TCITEM_ACKNOWLEDGEFLAG_ALL
// Specify the telecommand on-board buffer queues display item authorization status
#define TCONBOARDBUFFERQUEUESITEM_AUTHORIZATIONSTATUS_NONE   TCITEM_AUTHORIZATIONSTATUS_NONE
#define TCONBOARDBUFFERQUEUESITEM_AUTHORIZATIONSTATUS_GRANTED   TCITEM_AUTHORIZATIONSTATUS_GRANTED
#define TCONBOARDBUFFERQUEUESITEM_AUTHORIZATIONSTATUS_DENIED   TCITEM_AUTHORIZATIONSTATUS_DENIED
// Specify the telecommand on-board buffer queues display item check results
#define TCONBOARDBUFFERQUEUESITEM_RESULT_NONE   TCITEM_RESULT_NONE
#define TCONBOARDBUFFERQUEUESITEM_RESULT_PTV_GO   TCITEM_RESULT_PTV_GO
#define TCONBOARDBUFFERQUEUESITEM_RESULT_PTV_WAIT   TCITEM_RESULT_PTV_WAIT
#define TCONBOARDBUFFERQUEUESITEM_RESULT_PTV_FAIL   TCITEM_RESULT_PTV_FAIL
#define TCONBOARDBUFFERQUEUESITEM_RESULT_PEV_GO   TCITEM_RESULT_PEV_GO
#define TCONBOARDBUFFERQUEUESITEM_RESULT_PEV_NOGO   TCITEM_RESULT_PEV_NOGO
#define TCONBOARDBUFFERQUEUESITEM_RESULT_CEV_IDLE   TCITEM_RESULT_CEV_IDLE
#define TCONBOARDBUFFERQUEUESITEM_RESULT_CEV_PENDING   TCITEM_RESULT_CEV_PENDING
#define TCONBOARDBUFFERQUEUESITEM_RESULT_CEV_PASSED   TCITEM_RESULT_CEV_PASSED
#define TCONBOARDBUFFERQUEUESITEM_RESULT_CEV_FAILED   TCITEM_RESULT_CEV_FAILED
#define TCONBOARDBUFFERQUEUESITEM_RESULT_CEV_UNKNOWN   TCITEM_RESULT_CEV_UNKNOWN
#define TCONBOARDBUFFERQUEUESITEM_RESULT_CEV_UNVERIFIED   TCITEM_RESULT_CEV_UNVERIFIED
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PTV_UPLINK   TCITEM_FAILURE_PTV_UPLINK
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PTV_RELEASETIMEWINDOW   TCITEM_FAILURE_PTV_RELEASETIMEWINDOW
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PTV_EXECUTIONTIME   TCITEM_FAILURE_PTV_EXECUTIONTIME
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PTV_INTERLOCK   TCITEM_FAILURE_PTV_INTERLOCK
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PTV_SUBSYSTEM   TCITEM_FAILURE_PTV_SUBSYSTEM
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PTV_ONBOARDBUFFER   TCITEM_FAILURE_PTV_ONBOARDBUFFER
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PTV_ENCODING   TCITEM_FAILURE_PTV_ENCODING
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PEV_TELEMETRY   TCITEM_FAILURE_PEV_TELEMETRY
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PEV_CORRELATION   TCITEM_FAILURE_PEV_CORRELATION
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PEV_2NDSTEP   TCITEM_FAILURE_PEV_2NDSTEP
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_PEV_PARAMETERS   TCITEM_FAILURE_PEV_PARAMETERS
#define TCONBOARDBUFFERQUEUESITEM_FAILURE_CEV_PARAMETERS   TCITEM_FAILURE_CEV_PARAMETERS
// Specify the telecommand on-board buffer queues display item status flags
#define TCONBOARDBUFFERQUEUESITEM_STATUS_NONE   TCITEM_STATUS_NONE
#define TCONBOARDBUFFERQUEUESITEM_STATUS_RELEASED   TCITEM_STATUS_RELEASED
#define TCONBOARDBUFFERQUEUESITEM_STATUS_NOTRELEASED   TCITEM_STATUS_NOTRELEASED
#define TCONBOARDBUFFERQUEUESITEM_STATUS_FAILEDRELEASE   TCITEM_STATUS_FAILEDRELEASE
#define TCONBOARDBUFFERQUEUESITEM_STATUS_SENT   TCITEM_STATUS_SENT
#define TCONBOARDBUFFERQUEUESITEM_STATUS_FAILEDSEND   TCITEM_STATUS_FAILEDSEND
#define TCONBOARDBUFFERQUEUESITEM_STATUS_UPLINKED   TCITEM_STATUS_UPLINKED
#define TCONBOARDBUFFERQUEUESITEM_STATUS_FAILEDUPLINK   TCITEM_STATUS_FAILEDUPLINK
#define TCONBOARDBUFFERQUEUESITEM_STATUS_EXECUTED   TCITEM_STATUS_EXECUTED
#define TCONBOARDBUFFERQUEUESITEM_STATUS_NOTEXECUTED   TCITEM_STATUS_NOTEXECUTED
#define TCONBOARDBUFFERQUEUESITEM_STATUS_FAILEDEXECUTION   TCITEM_STATUS_FAILEDEXECUTION
// Specify the telecommand on-board buffer queues display item status colors
#define TCONBOARDBUFFERQUEUESITEM_STATUSCOLOR_NONE   0
#define TCONBOARDBUFFERQUEUESITEM_STATUSCOLOR_IDLE   1
#define TCONBOARDBUFFERQUEUESITEM_STATUSCOLOR_PENDING   2
#define TCONBOARDBUFFERQUEUESITEM_STATUSCOLOR_PASSED   3
#define TCONBOARDBUFFERQUEUESITEM_STATUSCOLOR_NOTPASSED   4
// Specify the telecommand on-board buffer queues display item alert types
#define TCONBOARDBUFFERQUEUESITEM_ALERTTYPE_NONE   0
#define TCONBOARDBUFFERQUEUESITEM_ALERTTYPE_INFORMATION   1
#define TCONBOARDBUFFERQUEUESITEM_ALERTTYPE_WARNING   2
#define TCONBOARDBUFFERQUEUESITEM_ALERTTYPE_ERROR   3
#define TCONBOARDBUFFERQUEUESITEM_ALERTTYPE_ANY   (-1)

class CTCOnBoardBufferQueuesItem : public CTCItem
{
	// Construction
public:
	CTCOnBoardBufferQueuesItem();

	// Attributes
private:
	typedef struct tagPROPERTIESDATA {
		INT  cbSize;
		INT  cbAlertTypes;
		INT  cbAlertMessages[2];
	} PROPERTIESDATA, *PPROPERTIESDATA, *LPPROPERTIESDATA;
private:
	CUIntArray  m_nAlertTypes;
	CUIntArray  m_nAlertMessages;
	CStringArray  m_szAlertMessages;
private:
	BOOL  m_bSelected;

	// Operations
public:
	BOOL SetAlerts(CONST CByteArray &nAlertsInfo);
	BOOL GetAlerts(CByteArray &nAlertsInfo) CONST;

	BOOL Alert(UINT nType, UINT nMessage, LPCTSTR pszMessage, BOOL bOverwrite = TRUE);
	BOOL Alert(UINT nType, UINT nMessage = -1, BOOL bEnable = FALSE);
	UINT IsAlerted(UINT nMessage, CString &szMessage) CONST;
	UINT IsAlerted(UINT nMessage = -1) CONST;

	INT GetAlertCount(UINT nType) CONST;

	VOID Select(BOOL bSelect = TRUE);
	BOOL IsSelected() CONST;

	BOOL Copy(CONST CTCOnBoardBufferQueuesItem *pItem);
	BOOL Compare(CONST CTCOnBoardBufferQueuesItem *pItem) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesItems

class CTCOnBoardBufferQueuesItems : public CTCItems
{
	// Construction
public:
	CTCOnBoardBufferQueuesItems();
	~CTCOnBoardBufferQueuesItems();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCOnBoardBufferQueuesItem *pItem);

	INT Collect(INT nIndex, CTCOnBoardBufferQueuesItems &pItems) CONST;
	INT Collect(INT nIndex, CUIntArray &nItemIDs) CONST;
	INT Collect(INT nIndex, CPtrArray &pItems) CONST;

	CTCOnBoardBufferQueuesItem *GetAt(INT nIndex) CONST;
	CTCOnBoardBufferQueuesItem *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCOnBoardBufferQueuesItems *pItems);
	BOOL Compare(CONST CTCOnBoardBufferQueuesItems *pItems) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesPrintJobInfo

class CTCOnBoardBufferQueuesPrintJobInfo : public CObject
{
	// Construction
public:
	CTCOnBoardBufferQueuesPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbProfile;
		INT  cbComments;
		INT  cbPrintBuffer;
		INT  cbPrintQueue;
		UINT  nPrintMode;
		UINT  nPrintQueueID;
		UINT  nPrintRange[2];
		TIMEKEY  tPrintRange[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szProfile;
	CString  m_szComments;
	CString  m_szPrintBuffer;
	CString  m_szPrintQueue;
	CTimeKey  m_tPrintRange[2];
	UINT  m_nPrintRange[2];
	UINT  m_nPrintQueueID;
	UINT  m_nPrintMode;

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
	BOOL SetPrintBuffer(LPCTSTR pszBuffer);
	CString GetPrintBuffer() CONST;
	BOOL SetPrintQueue(LPCTSTR pszQueue);
	CString GetPrintQueue() CONST;
	BOOL SetPrintQueueID(UINT nID);
	UINT GetPrintQueueID() CONST;
	BOOL SetPrintRange(UINT nMin, UINT nMax);
	BOOL SetPrintRange(CONST CTimeKey &tMin, CONST CTimeKey &tMax);
	BOOL GetPrintRange(UINT &nMin, UINT &nMax) CONST;
	BOOL GetPrintRange(CTimeKey &tMin, CTimeKey &tMax) CONST;

	VOID Copy(CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesPrintJobs

class CTCOnBoardBufferQueuesPrintJobs : public CPtrArray
{
	// Construction
public:
	CTCOnBoardBufferQueuesPrintJobs();
	~CTCOnBoardBufferQueuesPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CTCOnBoardBufferQueuesPrintJobInfo *GetAt(INT nIndex) CONST;
	CTCOnBoardBufferQueuesPrintJobInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCOnBoardBufferQueuesPrintJobs *pPrintJobs);
	BOOL Compare(CONST CTCOnBoardBufferQueuesPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSettingsLayoutPage dialog

#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_PANE_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_PANE   1003
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_TOOLTIPS   1004
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FORMAT   1005
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC   1006
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FORMAT_NAME   1007
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FORMAT_VIEW   1008
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER   1009
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FORMAT_REMOVE   1010
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FORMAT_GRID   1011
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FORMAT_GRIDCOLOR   1012
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS   1013
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1014
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1015
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS   1016
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1017
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1018
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_NAMES   1019
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1020
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_STYLE   1021
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1022
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_SIZE   1023
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1024
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1025

class CTCOnBoardBufferQueuesSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSettingsLayoutPage)

	// Construction
public:
	CTCOnBoardBufferQueuesSettingsLayoutPage();

	// Attributes
private:
	CPtrArray  m_pColumns[2][2];
	CPtrArray  m_plfTitle[2][2];
	CPtrArray  m_plfItems[2][2];
	CUIntArray  m_nGridBackgroundColor[2][2];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;
	CStringArray  m_szPages;
	CStringArray  m_szColumns;
	INT  m_nColumnIndex;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSettingsLayoutPage)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetColumns(LPCTSTR pszPage, UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(LPCTSTR pszPage, UINT nPane, LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(LPCTSTR pszPage, UINT nPane, LPLOGFONT pItemsFont) CONST;
	BOOL GetGridBackgroundColor(LPCTSTR pszPage, UINT nPane, COLORREF &nColor) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CTCOnBoardBufferQueuesSettingsDialog *GetParentDialog() CONST;
	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumLayoutPanes();
	BOOL EnumLayoutColumns();

	BOOL ShowLayoutColumns();
	VOID ShowLayoutBackground();
	VOID ShowLayoutFontDetails();
	VOID ShowLayoutFontSample();

	BOOL InsertLayoutColumn(INT nIndex, LPCTSTR pszText);
	BOOL ModifyLayoutColumn(INT nIndex, LPCTSTR pszText);
	BOOL RemoveLayoutColumn(INT nIndex);
	BOOL SetCurLayoutColumn(INT nIndex = 0);
	INT GetCurLayoutColumn() CONST;
	BOOL CheckLayoutColumn() CONST;

	CString LookupColumnName(INT nIndex, UINT nColumn) CONST;
	UINT LookupColumnName(INT nIndex, LPCTSTR pszColumn) CONST;
	INT CalcColumnsWidth(INT nIndex, CONST CUIntArray &nColumns, CUIntArray &nWidths);
	INT CalcColumnWidth(INT nIndex, LPCTSTR pszColumn);
	INT CalcColumnIndent() CONST;

	INT FindPageIndex() CONST;
	INT FindPageIndex(LPCTSTR pszPage) CONST;
	INT FindPaneIndex() CONST;
	INT FindPaneIndex(UINT nPane) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSettingsLayoutPage)
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
	//{{AFX_MSG(CTCOnBoardBufferQueuesSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnInsertColumnBefore();
	afx_msg void OnInsertColumnAfter();
	afx_msg void OnRemoveColumn();
	afx_msg void OnGridBackground();
	afx_msg void OnToolTips();
	afx_msg void OnTitleFont();
	afx_msg void OnItemsFont();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangePane();
	afx_msg void OnSelchangeColumnName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeGridBackgroundColor();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSettingsPrintingComments window

class CTCOnBoardBufferQueuesSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSettingsPrintingPage dialog

#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_PROFILE_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_PROFILE   1003
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS   1004
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_BUFFER_STATIC   1005
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_BUFFER   1006
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_STATIC   1007
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_SUMMARY   1008
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_QUEUE   1009
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_QUEUE_NAME   1010
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_CONTENTS   1011
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_CONTENTS_NUMBER   1012
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_CONTENTS_NUMBER_LOW   1013
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_CONTENTS_NUMBER_TO_STATIC   1014
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_CONTENTS_NUMBER_HIGH   1015
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_CONTENTS_EXECUTIONTIME   1016
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_CONTENTS_EXECUTIONTIME_START   1017
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_CONTENTS_EXECUTIONTIME_TO_STATIC   1018
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_OPTIONS_CONTENTS_EXECUTIONTIME_STOP   1019
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_COMMENTS   1020
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_COMMENTSTEXT_STATIC   1021
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_COMMENTSTEXT   1022
#define IDC_TCONBOARDBUFFERQUEUESSETTINGS_PRINTINGPAGE_CLEARCOMMENTS   1023

// Specify the telecommand on-board buffer queues display settings printing page related limits
#define TCONBOARDBUFFERQUEUESSETTINGSPRINTINGPAGE_MINIMUMITEMRANGE   1
#define TCONBOARDBUFFERQUEUESSETTINGSPRINTINGPAGE_MAXIMUMITEMRANGE   10000
#define TCONBOARDBUFFERQUEUESSETTINGSPRINTINGPAGE_DEFAULTITEMRANGE   100

class CTCOnBoardBufferQueuesSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSettingsPrintingPage)

	// Construction
public:
	CTCOnBoardBufferQueuesSettingsPrintingPage();

	// Attributes
private:
	CTCOnBoardBufferQueues  m_pQueues;
	CTCOnBoardBufferQueuesPrintJobs  m_pJobs[2];
private:
	CTCOnBoardBufferQueuesSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSettingsPrintingPage)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CTCOnBoardBufferQueuesPrintJobs &pJobs) CONST;

	class CTCOnBoardBufferQueuesSettingsDialog *GetParentDialog() CONST;
	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CTCOnBoardBufferQueuesPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSettingsPrintingPage)
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
	//{{AFX_MSG(CTCOnBoardBufferQueuesSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrintSummary();
	afx_msg void OnPrintBufferQueue();
	afx_msg void OnPrintItemRange();
	afx_msg void OnPrintTimeRange();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnSelchangeBuffer();
	afx_msg void OnSelchangeBufferQueue();
	afx_msg void OnSpinchangeLowItemRange();
	afx_msg void OnSpinchangeHighItemRange();
	afx_msg void OnSpinchangeStartTimeRange();
	afx_msg void OnSpinchangeStopTimeRange();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSettingsTabCtrl window

class CTCOnBoardBufferQueuesSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSettingsDialog

class CTCOnBoardBufferQueuesSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSettingsDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSettingsDialog();

	// Attributes
private:
	CTCOnBoardBufferQueuesSettingsTabCtrl  m_wndTabCtrl;
	CTCOnBoardBufferQueuesSettingsLayoutPage  m_pageLayout;
	CTCOnBoardBufferQueuesSettingsPrintingPage  m_pagePrinting;

	// Operations
public:
	BOOL GetColumns(LPCTSTR pszPage, UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(LPCTSTR pszPage, UINT nPane, LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(LPCTSTR pszPage, UINT nPane, LPLOGFONT pItemsFont) CONST;
	BOOL GetGridBackgroundColor(LPCTSTR pszPage, UINT nPane, COLORREF &nColor) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetPrintJobs(CTCOnBoardBufferQueuesPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSettingsDialog)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesSettingsDialog)
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
// CTCOnBoardBufferQueuesItemPropertiesParametersCalibrationPage dialog

#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCOnBoardBufferQueuesItemPropertiesParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesItemPropertiesParametersCalibrationPage)

	// Construction
public:
	CTCOnBoardBufferQueuesItemPropertiesParametersCalibrationPage();

	// Attributes
private:
	UINT  m_nCalTableType;
	CUIntArray  m_nCalTableIDs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesItemPropertiesParametersCalibrationPage)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);
	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCOnBoardBufferQueuesItemPropertiesParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesItemPropertiesParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesItemPropertiesParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesItemPropertiesParametersFolderTabCtrl window

class CTCOnBoardBufferQueuesItemPropertiesParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesItemPropertiesParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCOnBoardBufferQueuesItemPropertiesParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesItemPropertiesParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesItemPropertiesParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesItemPropertiesParametersFolder

class CTCOnBoardBufferQueuesItemPropertiesParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesItemPropertiesParametersFolder)

	// Construction
public:
	CTCOnBoardBufferQueuesItemPropertiesParametersFolder();

	// Attributes
private:
	CTCOnBoardBufferQueuesItemPropertiesParametersFolderTabCtrl  m_wndTabCtrl;
	CTCOnBoardBufferQueuesItemPropertiesParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter = NULL);

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCOnBoardBufferQueuesItemPropertiesParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesItemPropertiesParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesItemPropertiesParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesItemPropertiesParametersDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_ITEM_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_ITEM   1003
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_FOLDER   1004
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_HELP   1005

class CTCOnBoardBufferQueuesItemPropertiesParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesItemPropertiesParametersDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesItemPropertiesParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szParameter;
private:
	CTCOnBoardBufferQueuesItemPropertiesParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesItemPropertiesParametersDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_ITEMPROPERTIESPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, LPCTSTR pszParameter);

	VOID SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CDisplayDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesItemPropertiesParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesItemPropertiesParametersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesItemPropertiesDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_NAME_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_NAME   1003
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_DESCRIPTION   1005
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS   1006
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPTV   1007
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_OVERRIDEPEV   1008
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_OVERRIDECEV   1009
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_DISABLEPTV   1010
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_DISABLEPEV   1011
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_DISABLECEV   1012
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_PREAUTHORIZED   1013
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW   1014
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_STATIC   1015
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME   1016
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC   1017
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME   1018
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED   1019
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_STATIC   1020
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME   1021
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC   1022
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_CONSTRAINTS_RELEASETIMEWINDOW_DELAY   1023
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_ONBOARDEXECUTION   1024
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_ONBOARDEXECUTION_IMMEDIATELY   1025
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG   1026
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_ONBOARDEXECUTION_TIMETAG_TIME   1027
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_ONBOARDEXECUTION_FIRSTSTEP   1028
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_ONBOARDEXECUTION_SECONDSTEP   1029
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_PARAMETERS   1030
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_PARAMETERS_LIST   1031
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_PARAMETERS_REMARK   1032
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_PARAMETERS_SHOWALL   1033
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_RAWDATA   1034
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_RAWDATA_AREA   1035
#define IDC_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_HELP   1036

class CTCOnBoardBufferQueuesItemPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesItemPropertiesDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesItemPropertiesDialog();   // standard constructor

	// Attributes
private:
	CTCOnBoardBufferQueuesItem  m_cItem;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesItemPropertiesDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_ITEMPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCOnBoardBufferQueuesItem *pItem);

	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();
	VOID ShowParameters();
	VOID ShowRawData();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesItemPropertiesDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowAllParameters();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesComposedItemPropertiesDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_NAME_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_NAME   1003
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_DESCRIPTION   1005
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_STATIC   1006
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY   1007
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_PROPERTIES   1008
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS   1009
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPTV   1010
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDEPEV   1011
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_OVERRIDECEV   1012
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPTV   1013
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLEPEV   1014
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_DISABLECEV   1015
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_PREAUTHORIZED   1016
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW   1017
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_STATIC   1018
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME   1019
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STARTTIME_NONE   1020
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_STATIC   1021
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME   1022
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_STOPTIME_NONE   1023
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_UNLIMITED   1024
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_STATIC   1025
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME   1026
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_TRANSMISSIONTIME_NONE   1027
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_EXECUTIONTIME_STATIC   1028
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_STATIC   1029
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY   1030
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_CONSTRAINTS_RELEASETIMEWINDOW_DELAY_NONE   1031
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION   1032
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_IMMEDIATELY   1033
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG   1034
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_TIMETAG_TIME   1035
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_FIRSTSTEP   1036
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_ONBOARDEXECUTION_SECONDSTEP   1037
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS   1038
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_LIST   1039
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_REMARK   1040
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWFORMALLIST   1041
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_PARAMETERS_SHOWALL   1042
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA   1043
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_ENTRY_RAWDATA_AREA   1044
#define IDC_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_HELP   1045

class CTCOnBoardBufferQueuesComposedItemPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesComposedItemPropertiesDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesComposedItemPropertiesDialog();   // standard constructor

	// Attributes
private:
	CString  m_szName;
	CString  m_szDescription;
	CString  m_szRawData[2];
	CTCOnBoardBufferQueuesItems  m_pItems;
	CDatabaseTCParameters  m_pParameters;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesComposedItemPropertiesDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_COMPOSEDITEMPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CTCOnBoardBufferQueuesItems &pItems);

	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumEntries();

	VOID ShowProperties();
	VOID ShowParameters();
	VOID ShowRawData();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesComposedItemPropertiesDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesComposedItemPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeEntry();
	afx_msg void OnShowAllParameters();
	afx_msg void OnShowFormalParameters();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesStartPropertiesDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_NAME_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_NAME   1003
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_DESCRIPTION   1005
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_EXECUTION_STATIC   1006
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_EXECUTION_IMMEDIATELY   1007
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_EXECUTION_ATTIME   1008
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_EXECUTION_TIME   1009
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_PARAMETERS_STATIC   1010
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_PARAMETERS   1011
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_REMARK_ILLEGALCOMMAND   1012
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_REMARK_OOLPARAMETER   1013
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_DESTINATION_STATIC   1014
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_DESTINATION_MANUALSTACK   1015
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_DESTINATION_AUTOMATICSTACK   1016
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_RELEASE_STATIC   1017
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_RELEASE_IMMEDIATELY   1018
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_RELEASE_ATTIME   1019
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_RELEASE_TIME   1020
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_PREAUTHORIZED   1021
#define IDC_TCONBOARDBUFFERQUEUES_START_PROPERTIES_HELP   1022

class CTCOnBoardBufferQueuesStartPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesStartPropertiesDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesStartPropertiesDialog();   // standard constructor

	// Attributes
private:
	CString  m_szName;
	CString  m_szType;
private:
	BOOL  m_bFunction;
	CDatabaseTCFunction  m_cFunction;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesStartPropertiesDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_START_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	VOID ShowContents();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesStartPropertiesDialog)
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
	//{{AFX_MSG(CTCOnBoardBufferQueuesStartPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesStopPropertiesDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_NAME_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_NAME   1003
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_DESCRIPTION   1005
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_EXECUTION_STATIC   1006
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_EXECUTION_IMMEDIATELY   1007
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_EXECUTION_ATTIME   1008
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_EXECUTION_TIME   1009
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_PARAMETERS_STATIC   1010
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_PARAMETERS   1011
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_REMARK_ILLEGALCOMMAND   1012
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_REMARK_OOLPARAMETER   1013
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_DESTINATION_STATIC   1014
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_DESTINATION_MANUALSTACK   1015
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_DESTINATION_AUTOMATICSTACK   1016
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_RELEASE_STATIC   1017
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_RELEASE_IMMEDIATELY   1018
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_RELEASE_ATTIME   1019
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_RELEASE_TIME   1020
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_PREAUTHORIZED   1021
#define IDC_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_HELP   1022

class CTCOnBoardBufferQueuesStopPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesStopPropertiesDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesStopPropertiesDialog();   // standard constructor

	// Attributes
private:
	CString  m_szName;
	CString  m_szType;
private:
	BOOL  m_bFunction;
	CDatabaseTCFunction  m_cFunction;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesStopPropertiesDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_STOP_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	VOID ShowContents();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesStopPropertiesDialog)
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
	//{{AFX_MSG(CTCOnBoardBufferQueuesStopPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesDumpDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_DUMP_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_NAME_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_NAME   1003
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_APID_STATIC   1004
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_APID   1005
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_SUBSCHEDULEID_STATIC   1006
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_SUBSCHEDULEID   1007
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_STATIC   1008
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADALL   1009
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYRANGE   1010
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYRANGE_LOWENTRY   1011
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYRANGE_TO_STATIC   1012
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYRANGE_HIGHENTRY   1013
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYTIMERANGE   1014
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYTIMERANGE_STARTTIME   1015
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYTIMERANGE_TO_STATIC   1016
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYTIMERANGE_STOPTIME   1017
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYSUBSYSTEM   1018
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYSUBSYSTEM_NAME   1019
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYSEQUENCECOUNTER   1020
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYSEQUENCECOUNTER_NUMBER   1021
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYSEQUENCECOUNTER_HEXNUMBER_STATIC   1022
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_ACTION_DOWNLOADBYSEQUENCECOUNTER_HEXNUMBER   1023
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_UPDATEBYDOWNLOAD   1024
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_CLEARDOWNLOADSTATUS   1025
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_SEND   1026
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_HELP   1027

class CTCOnBoardBufferQueuesDumpDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesDumpDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesDumpDialog();   // standard constructor

	// Attributes
private:
	CTCOnBoardBufferQueue  m_cQueue;
	BOOL  m_bTelecommand;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesDumpDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_DUMP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumSubSystems();

	VOID ShowQueueOptions();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesDumpDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesDumpDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDownloadAllEntries();
	afx_msg void OnDownloadByRange();
	afx_msg void OnDownloadByTimeRange();
	afx_msg void OnDownloadBySubSystem();
	afx_msg void OnDownloadBySequenceCounter();
	afx_msg void OnUpdateByDownload();
	afx_msg void OnClearDownloadStatus();
	afx_msg void OnSelchangeSubSystem();
	afx_msg void OnSpinchangeLowEntry();
	afx_msg void OnSpinchangeHighEntry();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnSpinchangeSequenceCounter();
	afx_msg void OnTelecommands();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesDumpPropertiesDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_NAME_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_NAME   1003
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_DESCRIPTION   1005
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_EXECUTION_STATIC   1006
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_EXECUTION_IMMEDIATELY   1007
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_EXECUTION_ATTIME   1008
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_EXECUTION_TIME   1009
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_PARAMETERS_STATIC   1010
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_PARAMETERS   1011
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_REMARK_ILLEGALCOMMAND   1012
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_REMARK_OOLPARAMETER   1013
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_DESTINATION_STATIC   1014
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_DESTINATION_MANUALSTACK   1015
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_DESTINATION_AUTOMATICSTACK   1016
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_RELEASE_STATIC   1017
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_RELEASE_IMMEDIATELY   1018
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_RELEASE_ATTIME   1019
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_RELEASE_TIME   1020
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_PREAUTHORIZED   1021
#define IDC_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_HELP   1022

class CTCOnBoardBufferQueuesDumpPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesDumpPropertiesDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesDumpPropertiesDialog();   // standard constructor

	// Attributes
private:
	CString  m_szName;
	CString  m_szType;
	CTimeKey  m_tRange[2];
	UINT  m_nRange[2];
	UINT  m_nFlags;
	UINT  m_nAPID;
	UINT  m_nPSC;
private:
	BOOL  m_bFunction;
	CDatabaseTCFunction  m_cFunction;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesDumpPropertiesDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_DUMP_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, LPCTSTR pszType, LPCTSTR pszName, UINT nFlags, UINT nAPID = -1, UINT nPSC = -1, INT nLowEntry = -1, INT nHighEntry = -1, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0);

	class CTCOnBoardBufferQueuesDumpDialog *GetParentDialog() CONST;
	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	VOID ShowContents();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesDumpPropertiesDialog)
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
	//{{AFX_MSG(CTCOnBoardBufferQueuesDumpPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesResetDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_RESET_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUES_RESET_NAME_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUES_RESET_NAME   1003
#define IDC_TCONBOARDBUFFERQUEUES_RESET_APID_STATIC   1004
#define IDC_TCONBOARDBUFFERQUEUES_RESET_APID   1005
#define IDC_TCONBOARDBUFFERQUEUES_RESET_SUBSCHEDULEID_STATIC   1006
#define IDC_TCONBOARDBUFFERQUEUES_RESET_SUBSCHEDULEID   1007
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_STATIC   1008
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEALL   1009
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYRANGE   1010
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYRANGE_LOWENTRY   1011
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYRANGE_TO_STATIC   1012
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYRANGE_HIGHENTRY   1013
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYTIMERANGE   1014
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYTIMERANGE_STARTTIME   1015
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYTIMERANGE_TO_STATIC   1016
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYTIMERANGE_STOPTIME   1017
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYSUBSYSTEM   1018
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYSUBSYSTEM_NAME   1019
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYSEQUENCECOUNTER   1020
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYSEQUENCECOUNTER_NUMBER   1021
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYSEQUENCECOUNTER_HEXNUMBER_STATIC   1022
#define IDC_TCONBOARDBUFFERQUEUES_RESET_ACTION_DELETEBYSEQUENCECOUNTER_HEXNUMBER   1023
#define IDC_TCONBOARDBUFFERQUEUES_RESET_UPDATEIMMEDIATELY   1024
#define IDC_TCONBOARDBUFFERQUEUES_RESET_SEND   1025
#define IDC_TCONBOARDBUFFERQUEUES_RESET_HELP   1026

class CTCOnBoardBufferQueuesResetDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesResetDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesResetDialog();   // standard constructor

	// Attributes
private:
	CTCOnBoardBufferQueue  m_cQueue;
	BOOL  m_bTelecommand;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesResetDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_RESET_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumSubSystems();

	VOID ShowQueueOptions();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesResetDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesResetDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeleteAllEntries();
	afx_msg void OnDeleteByRange();
	afx_msg void OnDeleteByTimeRange();
	afx_msg void OnDeleteBySubSystem();
	afx_msg void OnDeleteBySequenceCounter();
	afx_msg void OnUpdateImmediately();
	afx_msg void OnSelchangeSubSystem();
	afx_msg void OnSpinchangeLowEntry();
	afx_msg void OnSpinchangeHighEntry();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnSpinchangeSequenceCounter();
	afx_msg void OnTelecommands();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesResetPropertiesDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_DETAILS   1001
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_NAME_STATIC   1002
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_NAME   1003
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_DESCRIPTION   1005
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_EXECUTION_STATIC   1006
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_EXECUTION_IMMEDIATELY   1007
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_EXECUTION_ATTIME   1008
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_EXECUTION_TIME   1009
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_PARAMETERS_STATIC   1010
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_PARAMETERS   1011
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_REMARK_ILLEGALCOMMAND   1012
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_REMARK_OOLPARAMETER   1013
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_DESTINATION_STATIC   1014
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_DESTINATION_MANUALSTACK   1015
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_DESTINATION_AUTOMATICSTACK   1016
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_RELEASE_STATIC   1017
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_RELEASE_IMMEDIATELY   1018
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_RELEASE_ATTIME   1019
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_RELEASE_TIME   1020
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_PREAUTHORIZED   1021
#define IDC_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_HELP   1022

class CTCOnBoardBufferQueuesResetPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesResetPropertiesDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesResetPropertiesDialog();   // standard constructor

	// Attributes
private:
	CString  m_szName;
	CString  m_szType;
	CTCPacket  m_cTCPacket;
	CTimeKey  m_tRange[2];
	UINT  m_nRange[2];
	UINT  m_nFlags;
	UINT  m_nAPID;
	UINT  m_nPSC;
private:
	BOOL  m_bFunction;
	CDatabaseTCFunction  m_cFunction;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesResetPropertiesDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_RESET_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, LPCTSTR pszType, LPCTSTR pszName, UINT nFlags, UINT nAPID = -1, UINT nPSC = -1, INT nLowEntry = -1, INT nHighEntry = -1, CONST CTimeKey &tStartTime = 0, CONST CTimeKey &tStopTime = 0, CONST CTCPacket *pTCPacket = NULL);

	class CTCOnBoardBufferQueuesResetDialog *GetParentDialog() CONST;
	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	VOID ShowContents();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesResetPropertiesDialog)
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
	//{{AFX_MSG(CTCOnBoardBufferQueuesResetPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchNumberDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNUMBER_NUMBER_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNUMBER_NUMBER   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNUMBER_GOTO   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNUMBER_COMMENT_STATIC   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNUMBER_COMMENT   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNUMBER_CLOSE   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNUMBER_HELP   1007

class CTCOnBoardBufferQueuesSearchNumberDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchNumberDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchNumberDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchNumberDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHNUMBER_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchNumberDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchNumberDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnGotoNumber();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchNameDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNAME_NAME_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNAME_NAME   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNAME_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNAME_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNAME_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNAME_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNAME_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHNAME_HELP   1008

class CTCOnBoardBufferQueuesSearchNameDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchNameDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchNameDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szNames;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchNameDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHNAME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchNameDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchNameDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	afx_msg void OnEditchangeName();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchComputerDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMPUTER_NAME_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMPUTER_NAME   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMPUTER_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMPUTER_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMPUTER_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMPUTER_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMPUTER_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMPUTER_HELP   1008

class CTCOnBoardBufferQueuesSearchComputerDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchComputerDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchComputerDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szComputers;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchComputerDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHCOMPUTER_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchComputerDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchComputerDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComputer();
	afx_msg void OnEditchangeComputer();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchCommandSourceDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMMANDSOURCE_TYPE_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMMANDSOURCE_TYPE   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMMANDSOURCE_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMMANDSOURCE_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMMANDSOURCE_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMMANDSOURCE_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMMANDSOURCE_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCOMMANDSOURCE_HELP   1008

class CTCOnBoardBufferQueuesSearchCommandSourceDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchCommandSourceDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchCommandSourceDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchCommandSourceDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHCOMMANDSOURCE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumCommandSources();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchCommandSourceDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchCommandSourceDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchDescriptionDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_TEXT_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_TEXT   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_CASE   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_WORD   1008
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_FIND   1009
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_HELP   1010

class CTCOnBoardBufferQueuesSearchDescriptionDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchDescriptionDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchDescriptionDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szDescriptions;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchDescriptionDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHDESCRIPTION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchDescriptionDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchDescriptionDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDescription();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchCategoryDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCATEGORY_CATEGORY_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCATEGORY_CATEGORY   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCATEGORY_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCATEGORY_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCATEGORY_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCATEGORY_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCATEGORY_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCATEGORY_HELP   1008

class CTCOnBoardBufferQueuesSearchCategoryDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchCategoryDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchCategoryDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchCategoryDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHCATEGORY_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumCategories();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchCategoryDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchCategoryDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchSubSystemDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSUBSYSTEM_NAME_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSUBSYSTEM_NAME   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSUBSYSTEM_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSUBSYSTEM_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSUBSYSTEM_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSUBSYSTEM_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSUBSYSTEM_CASE   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSUBSYSTEM_FIND   1008
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSUBSYSTEM_HELP   1009

class CTCOnBoardBufferQueuesSearchSubSystemDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchSubSystemDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchSubSystemDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szSubSystems;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchSubSystemDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHSUBSYSTEM_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchSubSystemDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchSubSystemDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSubSystem();
	afx_msg void OnEditchangeSubSystem();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchArgumentsDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHARGUMENTS_ARGUMENT_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHARGUMENTS_ARGUMENT   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHARGUMENTS_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHARGUMENTS_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHARGUMENTS_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHARGUMENTS_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHARGUMENTS_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHARGUMENTS_HELP   1008

class CTCOnBoardBufferQueuesSearchArgumentsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchArgumentsDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchArgumentsDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szArguments;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchArgumentsDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHARGUMENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchArgumentsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchArgumentsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeArgument();
	afx_msg void OnEditchangeArgument();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchFlagsDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_FLAG_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_FLAG_INTERLOCKING   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_FLAG_INTERLOCKED   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_FLAG_GROUPED   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_FLAG_BLOCKED   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_DIRECTION   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_DIRECTION_UP   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_DIRECTION_DOWN   1008
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_ALL   1009
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_FIND   1010
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_HELP   1011

class CTCOnBoardBufferQueuesSearchFlagsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchFlagsDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchFlagsDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchFlagsDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHFLAGS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchFlagsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchFlagsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnInterlockingFlag();
	afx_msg void OnInterlockedFlag();
	afx_msg void OnGroupedFlag();
	afx_msg void OnBlockedFlag();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchTCPacketDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTCPACKET_TAG_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTCPACKET_TAG   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTCPACKET_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTCPACKET_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTCPACKET_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTCPACKET_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTCPACKET_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTCPACKET_HELP   1008

class CTCOnBoardBufferQueuesSearchTCPacketDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchTCPacketDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchTCPacketDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchTCPacketDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHTCPACKET_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumTCPackets();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchTCPacketDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchTCPacketDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchPSCDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPSC_NUMBER_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPSC_NUMBER   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPSC_NUMBER_RADIX_STATIC   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPSC_DIRECTION   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPSC_DIRECTION_UP   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPSC_DIRECTION_DOWN   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPSC_ALL   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPSC_FIND   1008
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPSC_HELP   1009

// Specify the telecommand on-board buffer queues display search packet sequence counter dialog related identifiers
#define TCONBOARDBUFFERQUEUESSEARCHPSC_MINIMUMINTERVAL   0
#define TCONBOARDBUFFERQUEUESSEARCHPSC_MAXIMUMINTERVAL   0xFFFF
#define TCONBOARDBUFFERQUEUESSEARCHPSC_DEFAULTINTERVAL   0

class CTCOnBoardBufferQueuesSearchPSCDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchPSCDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchPSCDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchPSCDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHPSC_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchPSCDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchPSCDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchDispatchTimeDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_TIME_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_TIME   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_MATCH   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_INTERVAL   1008
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_INTERVAL_TIME   1009
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_INTERVAL_STATIC   1010
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_FIND   1011
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_HELP   1012

// Specify the telecommand on-board buffer queues display search dispatch time dialog related identifiers
#define TCONBOARDBUFFERQUEUESSEARCHDISPATCHTIME_MINIMUMINTERVAL   1
#define TCONBOARDBUFFERQUEUESSEARCHDISPATCHTIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCONBOARDBUFFERQUEUESSEARCHDISPATCHTIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCOnBoardBufferQueuesSearchDispatchTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchDispatchTimeDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchDispatchTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchDispatchTimeDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHDISPATCHTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchDispatchTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchDispatchTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchReleaseTimeDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_TIME_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_TIME   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_MATCH   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_INTERVAL   1008
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_INTERVAL_TIME   1009
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_INTERVAL_STATIC   1010
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_FIND   1011
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_HELP   1012

// Specify the telecommand on-board buffer queues display search release time dialog related identifiers
#define TCONBOARDBUFFERQUEUESSEARCHRELEASETIME_MINIMUMINTERVAL   1
#define TCONBOARDBUFFERQUEUESSEARCHRELEASETIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCONBOARDBUFFERQUEUESSEARCHRELEASETIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCOnBoardBufferQueuesSearchReleaseTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchReleaseTimeDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchReleaseTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchReleaseTimeDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchReleaseTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchReleaseTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchReleaseTimeOffsetDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_OFFSET_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_OFFSET   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_MATCH   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_INTERVAL   1008
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_INTERVAL_TIME   1009
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_INTERVAL_STATIC   1010
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_FIND   1011
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_HELP   1012

// Specify the telecommand on-board buffer queues display search release time offset dialog related identifiers
#define TCONBOARDBUFFERQUEUESSEARCHRELEASETIMEOFFSET_MINIMUMINTERVAL   1
#define TCONBOARDBUFFERQUEUESSEARCHRELEASETIMEOFFSET_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCONBOARDBUFFERQUEUESSEARCHRELEASETIMEOFFSET_DEFAULTINTERVAL   SECONDSPERMINUTE

class CTCOnBoardBufferQueuesSearchReleaseTimeOffsetDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchReleaseTimeOffsetDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchReleaseTimeOffsetDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchReleaseTimeOffsetDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHRELEASETIMEOFFSET_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchReleaseTimeOffsetDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchReleaseTimeOffsetDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTimeOffset();
	afx_msg void OnIntervalTimeOffset();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchTransmissionTimeDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_TIME_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_TIME   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_MATCH   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_INTERVAL   1008
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_INTERVAL_TIME   1009
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_INTERVAL_STATIC   1010
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_FIND   1011
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_HELP   1012

// Specify the telecommand on-board buffer queues display search transmission time dialog related identifiers
#define TCONBOARDBUFFERQUEUESSEARCHTRANSMISSIONTIME_MINIMUMINTERVAL   1
#define TCONBOARDBUFFERQUEUESSEARCHTRANSMISSIONTIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCONBOARDBUFFERQUEUESSEARCHTRANSMISSIONTIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCOnBoardBufferQueuesSearchTransmissionTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchTransmissionTimeDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchTransmissionTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchTransmissionTimeDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHTRANSMISSIONTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchTransmissionTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchTransmissionTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchExecutionTimeDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_TIME_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_TIME   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_MATCH   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_INTERVAL   1008
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_INTERVAL_TIME   1009
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_INTERVAL_STATIC   1010
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_FIND   1011
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_HELP   1012

// Specify the telecommand on-board buffer queues display search execution time dialog related identifiers
#define TCONBOARDBUFFERQUEUESSEARCHEXECUTIONTIME_MINIMUMINTERVAL   1
#define TCONBOARDBUFFERQUEUESSEARCHEXECUTIONTIME_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCONBOARDBUFFERQUEUESSEARCHEXECUTIONTIME_DEFAULTINTERVAL   SECONDSPERHOUR

class CTCOnBoardBufferQueuesSearchExecutionTimeDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchExecutionTimeDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchExecutionTimeDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchExecutionTimeDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchExecutionTimeDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchExecutionTimeDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTime();
	afx_msg void OnIntervalTime();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchExecutionTimeOffsetDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_OFFSET_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_OFFSET   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_MATCH   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_INTERVAL   1008
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_TIME   1009
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_INTERVAL_STATIC   1010
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_FIND   1011
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_HELP   1012

// Specify the telecommand on-board buffer queues display search execution time offset dialog related identifiers
#define TCONBOARDBUFFERQUEUESSEARCHEXECUTIONTIMEOFFSET_MINIMUMOFFSET   -(365*SECONDSPERDAY)
#define TCONBOARDBUFFERQUEUESSEARCHEXECUTIONTIMEOFFSET_MAXIMUMOFFSET   (365*SECONDSPERDAY)
#define TCONBOARDBUFFERQUEUESSEARCHEXECUTIONTIMEOFFSET_DEFAULTOFFSET   0
#define TCONBOARDBUFFERQUEUESSEARCHEXECUTIONTIMEOFFSET_MINIMUMINTERVAL   1
#define TCONBOARDBUFFERQUEUESSEARCHEXECUTIONTIMEOFFSET_MAXIMUMINTERVAL   SECONDSPERDAY
#define TCONBOARDBUFFERQUEUESSEARCHEXECUTIONTIMEOFFSET_DEFAULTINTERVAL   SECONDSPERMINUTE

class CTCOnBoardBufferQueuesSearchExecutionTimeOffsetDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchExecutionTimeOffsetDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchExecutionTimeOffsetDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchExecutionTimeOffsetDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHEXECUTIONTIMEOFFSET_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchExecutionTimeOffsetDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchExecutionTimeOffsetDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDirectionUp();
	afx_msg void OnDirectionDown();
	afx_msg void OnMatchTimeOffset();
	afx_msg void OnIntervalTimeOffset();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchAuthorizationDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHAUTHORIZATION_TYPE_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHAUTHORIZATION_TYPE   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHAUTHORIZATION_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHAUTHORIZATION_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHAUTHORIZATION_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHAUTHORIZATION_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHAUTHORIZATION_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHAUTHORIZATION_HELP   1008

class CTCOnBoardBufferQueuesSearchAuthorizationDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchAuthorizationDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchAuthorizationDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchAuthorizationDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHAUTHORIZATION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumAuthorizations();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchAuthorizationDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchAuthorizationDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchPTVTimeWindowDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVTIMEWINDOW_TIME_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVTIMEWINDOW_TIME   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVTIMEWINDOW_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVTIMEWINDOW_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVTIMEWINDOW_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVTIMEWINDOW_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVTIMEWINDOW_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVTIMEWINDOW_HELP   1008

class CTCOnBoardBufferQueuesSearchPTVTimeWindowDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchPTVTimeWindowDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchPTVTimeWindowDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchPTVTimeWindowDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHPTVTIMEWINDOW_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchPTVTimeWindowDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchPTVTimeWindowDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchPTVCheckDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVCHECK_CHECK_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVCHECK_CHECK   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVCHECK_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVCHECK_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVCHECK_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVCHECK_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVCHECK_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVCHECK_HELP   1008

class CTCOnBoardBufferQueuesSearchPTVCheckDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchPTVCheckDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchPTVCheckDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchPTVCheckDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHPTVCHECK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumCheckFlags();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchPTVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchPTVCheckDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchPTVResultDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVRESULT_RESULT_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVRESULT_RESULT   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVRESULT_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVRESULT_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVRESULT_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVRESULT_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVRESULT_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPTVRESULT_HELP   1008

class CTCOnBoardBufferQueuesSearchPTVResultDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchPTVResultDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchPTVResultDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchPTVResultDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHPTVRESULT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumCheckResults();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchPTVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchPTVResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchPEVCheckDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVCHECK_CHECK_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVCHECK_CHECK   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVCHECK_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVCHECK_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVCHECK_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVCHECK_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVCHECK_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVCHECK_HELP   1008

class CTCOnBoardBufferQueuesSearchPEVCheckDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchPEVCheckDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchPEVCheckDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchPEVCheckDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHPEVCHECK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumCheckFlags();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchPEVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchPEVCheckDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchPEVResultDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVRESULT_RESULT_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVRESULT_RESULT   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVRESULT_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVRESULT_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVRESULT_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVRESULT_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVRESULT_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHPEVRESULT_HELP   1008

class CTCOnBoardBufferQueuesSearchPEVResultDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchPEVResultDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchPEVResultDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchPEVResultDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHPEVRESULT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumCheckResults();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchPEVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchPEVResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchCEVTimeWindowDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVTIMEWINDOW_TIME_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVTIMEWINDOW_TIME   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVTIMEWINDOW_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVTIMEWINDOW_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVTIMEWINDOW_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVTIMEWINDOW_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVTIMEWINDOW_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVTIMEWINDOW_HELP   1008

class CTCOnBoardBufferQueuesSearchCEVTimeWindowDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchCEVTimeWindowDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchCEVTimeWindowDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchCEVTimeWindowDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHCEVTIMEWINDOW_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchCEVTimeWindowDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchCEVTimeWindowDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchCEVCheckDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVCHECK_CHECK_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVCHECK_CHECK   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVCHECK_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVCHECK_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVCHECK_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVCHECK_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVCHECK_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVCHECK_HELP   1008

class CTCOnBoardBufferQueuesSearchCEVCheckDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchCEVCheckDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchCEVCheckDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchCEVCheckDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHCEVCHECK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumCheckFlags();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchCEVCheckDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchCEVCheckDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchCEVResultDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVRESULT_RESULT_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVRESULT_RESULT   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVRESULT_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVRESULT_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVRESULT_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVRESULT_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVRESULT_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHCEVRESULT_HELP   1008

class CTCOnBoardBufferQueuesSearchCEVResultDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchCEVResultDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchCEVResultDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchCEVResultDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHCEVRESULT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumCheckResults();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchCEVResultDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchCEVResultDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesSearchStatusDialog dialog

#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSTATUS_STATUS_STATIC   1001
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSTATUS_STATUS   1002
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSTATUS_DIRECTION   1003
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSTATUS_DIRECTION_UP   1004
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSTATUS_DIRECTION_DOWN   1005
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSTATUS_ALL   1006
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSTATUS_FIND   1007
#define IDC_TCONBOARDBUFFERQUEUES_SEARCHSTATUS_HELP   1008

class CTCOnBoardBufferQueuesSearchStatusDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesSearchStatusDialog)

	// Construction
public:
	CTCOnBoardBufferQueuesSearchStatusDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardBufferQueuesSearchStatusDialog)
	enum { IDD = IDD_TCONBOARDBUFFERQUEUES_SEARCHSTATUS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCOnBoardBufferQueuesPageDetailsTextView *GetParent() CONST;

private:
	VOID EnumStatus();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesSearchStatusDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesSearchStatusDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindTelecommand();
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesToolBar window

class CTCOnBoardBufferQueuesToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesToolBar)

	// Construction
public:
	CTCOnBoardBufferQueuesToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesStatusBar window

class CTCOnBoardBufferQueuesStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesStatusBar)

	// Construction
public:
	CTCOnBoardBufferQueuesStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CTCOnBoardBufferQueuesWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesStatusBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesToolTip window

class CTCOnBoardBufferQueuesToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesToolTip)

	// Construction
public:
	CTCOnBoardBufferQueuesToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesDocument

class CTCOnBoardBufferQueuesDocument : public CDocument
{
	DECLARE_DYNAMIC(CTCOnBoardBufferQueuesDocument)

	// Construction
public:
	CTCOnBoardBufferQueuesDocument();
	virtual ~CTCOnBoardBufferQueuesDocument();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesPageSummaryTextView window

// Specify the telecommand on-board buffer queues display summary text view command alert symbol identifiers
#define TCONBOARDBUFFERQUEUESPAGESUMMARYTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION   0
#define TCONBOARDBUFFERQUEUESPAGESUMMARYTEXTVIEW_COMMANDALERTSYMBOL_WARNING   1
#define TCONBOARDBUFFERQUEUESPAGESUMMARYTEXTVIEW_COMMANDALERTSYMBOL_ERROR   2
#define TCONBOARDBUFFERQUEUESPAGESUMMARYTEXTVIEW_COMMANDALERTSYMBOLS   3

class CTCOnBoardBufferQueuesPageSummaryTextView : public CTextView
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesPageSummaryTextView)

	// Construction
public:
	CTCOnBoardBufferQueuesPageSummaryTextView();

	// Attributes
private:
	CTCOnBoardBufferQueues  m_pQueues;
private:
	CSize  m_sizeAlertSymbols;
	CImage  *m_pAlertSymbols[TCONBOARDBUFFERQUEUESPAGESUMMARYTEXTVIEW_COMMANDALERTSYMBOLS];
	CTCOnBoardBufferQueuesToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bToolTips;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle);

	BOOL SetLayout(UINT nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(UINT &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL StopMonitoring();

	BOOL SetQueues(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetQueues(CTCOnBoardBufferQueues &pQueues) CONST;

	BOOL SetCurQueue(INT nIndex);
	BOOL CheckCurQueue(UINT nFlags) CONST;
	INT GetCurQueue() CONST;

	UINT GetQueueCount() CONST;

	BOOL DoAcknowledgeQueue();
	BOOL CanAcknowledgeQueue() CONST;

	BOOL GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContent(BOOL bRedraw = TRUE);

	class CTCOnBoardBufferQueuesPageSummaryView *GetParent() CONST;
	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

private:
	CString TranslateQueue(CONST CTCOnBoardBufferQueue *pQueue) CONST;
	BOOL TranslateQueue(CONST CTCOnBoardBufferQueue *pQueue, CTextViewAttribute *pAttribute) CONST;

private:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;
	COLORREF LookupColumnColor(UINT nColumn) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);

	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST;

	CString ConstructToolTipTitle(CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;
	CString ConstructToolTipText(CONST CTCOnBoardBufferQueue *pQueue, CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;

	BOOL LoadTelecommandSymbols();
	VOID FreeTelecommandSymbols();

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

public:
	static TCHAR GetSymbolDelimiter();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesPageSummaryTextView)
public:
	virtual BOOL SetLayoutInfo(INT nQueue, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nQueue, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RefreshContent();
public:
	virtual VOID DrawContent();
	virtual VOID DrawContent(CDC *pDC);
	virtual VOID DrawText(INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(INT nItem, INT nColumn, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText);
	virtual BOOL DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rItem);
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
	//{{AFX_MSG(CTCOnBoardBufferQueuesPageSummaryTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesPageSummaryView view

class CTCOnBoardBufferQueuesPageSummaryView : public CView
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesPageSummaryView)

	// Construction
public:
	CTCOnBoardBufferQueuesPageSummaryView();
	~CTCOnBoardBufferQueuesPageSummaryView();

	// Attributes
private:
	CTCOnBoardBufferQueuesPageSummaryTextView  *m_pwndList;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetLayout(UINT nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(UINT &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL StopMonitoring();

	BOOL SetQueues(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetQueues(CTCOnBoardBufferQueues &pQueues) CONST;

	BOOL SetCurQueue(INT nIndex);
	BOOL CheckCurQueue(UINT nFlags) CONST;
	INT GetCurQueue() CONST;

	UINT GetQueueCount() CONST;

	BOOL DoAcknowledgeQueue();
	BOOL CanAcknowledgeQueue() CONST;

	BOOL GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContent(BOOL bRedraw = TRUE);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesPageSummaryView)
public:
	virtual BOOL SetLayoutInfo(INT nQueue, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nQueue, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesPageSummaryView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesPageDetailsTextView window

// Specify the telecommand on-board buffer queues display details text view command flag symbol identifiers
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDFLAGSYMBOL_INTERLOCK   0
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDFLAGSYMBOL_INTERLOCKIDLE   1
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDFLAGSYMBOL_INTERLOCKPENDING   2
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDFLAGSYMBOL_INTERLOCKSUCCESS   3
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDFLAGSYMBOL_INTERLOCKFAILURE   4
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDFLAGSYMBOL_GROUPED   5
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDFLAGSYMBOL_BLOCKED   6
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDFLAGSYMBOLS   7
// Specify the telecommand on-board buffer queues display details text view command check flag symbol identifiers
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDCHECKFLAGSYMBOL_NONE   0
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDCHECKFLAGSYMBOL_ON   1
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDCHECKFLAGSYMBOL_OFF   2
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDCHECKFLAGSYMBOL_DISABLED   3
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDCHECKFLAGSYMBOLS   4
// Specify the telecommand on-board buffer queues display details text view command result symbol identifiers
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_PTV_GO   0
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_PTV_WAIT   1
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_PTV_FAIL   2
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_PEV_GO   3
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_PEV_NOGO   4
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_CEV_IDLE   5
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_CEV_PENDING   6
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_CEV_PASSED   7
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_CEV_FAILED   8
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_CEV_UNKNOWN   9
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOL_CEV_UNVERIFIED   10
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOLS   11
// Specify the telecommand on-board buffer queues display details text view command alert symbol identifiers
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDALERTSYMBOL_INFORMATION   0
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDALERTSYMBOL_WARNING   1
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDALERTSYMBOL_ERROR   2
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDALERTSYMBOLS   3
// Specify the telecommand on-board buffer queues display details text view command update timer identifiers
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDUPDATE_TIMERID   100
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDUPDATE_TIMEOUT   1000
// Specify the telecommand on-board buffer queues display visual aspect related identifiers
#define TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COLUMNTRANSPARENCY   0x30

class CTCOnBoardBufferQueuesPageDetailsTextView : public CTextView
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesPageDetailsTextView)

	// Construction
public:
	CTCOnBoardBufferQueuesPageDetailsTextView();

	// Attributes
private:
	INT  m_nIndex;
	INT  m_nSearchIndex;
	BOOL  m_bProperties;
	BOOL  m_bFullViewMode;
private:
	CSize  m_sizeFlagSymbols;
	CSize  m_sizeAlertSymbols;
	CSize  m_sizeResultSymbols;
	CSize  m_sizeCheckFlagSymbols;
	CImage  *m_pFlagSymbols[TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDFLAGSYMBOLS];
	CImage  *m_pCheckFlagSymbols[TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDCHECKFLAGSYMBOLS];
	CImage  *m_pResultSymbols[TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDRESULTSYMBOLS];
	CImage  *m_pAlertSymbols[TCONBOARDBUFFERQUEUESPAGEDETAILSTEXTVIEW_COMMANDALERTSYMBOLS];
	CTCOnBoardBufferQueuesToolTip  m_wndToolTip;
	COLORREF  m_nBackgroundColor[2];
	CUIntArray  m_nStatusColors;
	HCURSOR  m_hToolTipCursor;
	UINT  m_nClipboardFormat;
	BOOL  m_bToolTips;
private:
	CTCOnBoardBufferQueues  m_pQueues;
private:
	CTCOnBoardBufferQueuesSearchPSCDialog  m_dlgSearchPSC;
	CTCOnBoardBufferQueuesSearchNameDialog  m_dlgSearchName;
	CTCOnBoardBufferQueuesSearchFlagsDialog  m_dlgSearchFlags;
	CTCOnBoardBufferQueuesSearchNumberDialog  m_dlgSearchNumber;
	CTCOnBoardBufferQueuesSearchStatusDialog  m_dlgSearchStatus;
	CTCOnBoardBufferQueuesSearchComputerDialog  m_dlgSearchComputer;
	CTCOnBoardBufferQueuesSearchCategoryDialog  m_dlgSearchCategory;
	CTCOnBoardBufferQueuesSearchTCPacketDialog  m_dlgSearchTCPacket;
	CTCOnBoardBufferQueuesSearchPTVCheckDialog  m_dlgSearchPTVCheck;
	CTCOnBoardBufferQueuesSearchPEVCheckDialog  m_dlgSearchPEVCheck;
	CTCOnBoardBufferQueuesSearchCEVCheckDialog  m_dlgSearchCEVCheck;
	CTCOnBoardBufferQueuesSearchSubSystemDialog  m_dlgSearchSubSystem;
	CTCOnBoardBufferQueuesSearchArgumentsDialog  m_dlgSearchArguments;
	CTCOnBoardBufferQueuesSearchPTVResultDialog  m_dlgSearchPTVResult;
	CTCOnBoardBufferQueuesSearchPEVResultDialog  m_dlgSearchPEVResult;
	CTCOnBoardBufferQueuesSearchCEVResultDialog  m_dlgSearchCEVResult;
	CTCOnBoardBufferQueuesSearchDescriptionDialog  m_dlgSearchDescription;
	CTCOnBoardBufferQueuesSearchReleaseTimeDialog  m_dlgSearchReleaseTime;
	CTCOnBoardBufferQueuesSearchDispatchTimeDialog  m_dlgSearchDispatchTime;
	CTCOnBoardBufferQueuesSearchExecutionTimeDialog  m_dlgSearchExecutionTime;
	CTCOnBoardBufferQueuesSearchPTVTimeWindowDialog  m_dlgSearchPTVTimeWindow;
	CTCOnBoardBufferQueuesSearchCEVTimeWindowDialog  m_dlgSearchCEVTimeWindow;
	CTCOnBoardBufferQueuesSearchCommandSourceDialog  m_dlgSearchCommandSource;
	CTCOnBoardBufferQueuesSearchAuthorizationDialog  m_dlgSearchAuthorization;
	CTCOnBoardBufferQueuesSearchTransmissionTimeDialog  m_dlgSearchTransmissionTime;
	CTCOnBoardBufferQueuesSearchReleaseTimeOffsetDialog  m_dlgSearchReleaseTimeOffset;
	CTCOnBoardBufferQueuesSearchExecutionTimeOffsetDialog  m_dlgSearchExecutionTimeOffset;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle);

	BOOL SetLayout(UINT nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(UINT &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(COLORREF nColor);
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;

	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL StopMonitoring();

	BOOL SetQueues(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetQueues(CTCOnBoardBufferQueues &pQueues) CONST;

	BOOL SetCurQueue(INT nIndex);
	BOOL CheckCurQueue(UINT nFlags) CONST;
	INT GetCurQueue() CONST;

	UINT GetQueueCount() CONST;

	BOOL SetCurTelecommand(INT nIndex);
	INT GetCurTelecommand() CONST;

	BOOL SelectTelecommand(INT nIndex);
	BOOL HasSelectedTelecommands() CONST;

	UINT GetTelecommandCount() CONST;

	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;
	BOOL DoDeleteTelecommand();
	BOOL CanDeleteTelecommand() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL SearchTelecommandByNumber(INT nNumber);
	BOOL SearchTelecommandByName(LPCTSTR pszName, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByComputer(LPCTSTR pszComputer, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCommandSource(UINT nSourceType, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByDescription(LPCTSTR pszDescription, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL SearchTelecommandByCategory(LPCTSTR pszCategory, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandBySubSystem(LPCTSTR pszSubSystem, BOOL bDown, BOOL bAll, BOOL bCase);
	BOOL SearchTelecommandByArgument(LPCTSTR pszArgument, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByFlags(BOOL bDown, BOOL bAll, BOOL bInterlocking, BOOL bInterlocked, BOOL bGrouped, BOOL bBlocked);
	BOOL SearchTelecommandByTCPacket(LPCTSTR pszPacket, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPSC(UINT nPSC, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByDispatchTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByReleaseTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByReleaseTimeOffset(DWORD dwOffset, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByTransmissionTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByExecutionTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByExecutionTimeOffset(CONST CTimeSpan &tOffset, CONST CTimeSpan &tInterval, BOOL bDown, BOOL bAll, BOOL bMatch);
	BOOL SearchTelecommandByAuthorization(UINT nAuthorization, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVTimeWindow(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPTVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPEVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByPEVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVTimeWindow(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVCheck(UINT nCheck, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByCEVResult(UINT nResult, BOOL bDown, BOOL bAll);
	BOOL SearchTelecommandByStatus(LPCTSTR pszStatus, BOOL bDown, BOOL bAll);

	BOOL GetPrintProperties(CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContent(BOOL bRedraw = TRUE);

	class CTCOnBoardBufferQueuesPageDetailsView *GetParent() CONST;
	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

protected:
	BOOL ShowTelecommandProperties(INT nIndex);

	BOOL ActivateTelecommand(INT nIndex, BOOL bActivate = TRUE, BOOL bRedraw = TRUE);
	BOOL IsActivatedTelecommand(INT nIndex) CONST;

	BOOL UpdateTelecommand(CTCOnBoardBufferQueuesItem *pItem);

	CString TranslateTelecommand(CONST CTCOnBoardBufferQueuesItem *pItem) CONST;
	BOOL TranslateTelecommand(CONST CTCOnBoardBufferQueuesItem *pItem, CTextViewAttribute *pAttribute) CONST;

	BOOL AdjustTelecommandAlerts(CONST CTCItem *pAlertItem, CTCOnBoardBufferQueuesItem *pItem) CONST;

protected:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;
	COLORREF LookupColumnColor(UINT nColumn) CONST;
	COLORREF LookupStatusColor(UINT nResult, UINT nStatus) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);

	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST;
	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, INT nCount, INT nIndex) CONST;

	CString ConstructToolTipTitle(CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;
	CString ConstructToolTipText(CONST CTCOnBoardBufferQueuesItem *pItem, CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;

	BOOL SetClipboardFormat(UINT nFormat);
	UINT GetClipboardFormat() CONST;
	BOOL CopyToClipboard();

	BOOL LoadTelecommandSymbols();
	VOID FreeTelecommandSymbols();

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

public:
	static TCHAR GetSymbolDelimiter();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesPageDetailsTextView)
public:
	virtual BOOL SetLayoutInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RefreshContent();
public:
	virtual VOID DrawContent();
	virtual VOID DrawContent(CDC *pDC);
	virtual VOID DrawText(INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(INT nItem, INT nColumn, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText);
	virtual BOOL DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rItem);
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesPageDetailsTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesPageDetailsView view

class CTCOnBoardBufferQueuesPageDetailsView : public CView
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesPageDetailsView)

	// Construction
public:
	CTCOnBoardBufferQueuesPageDetailsView();
	~CTCOnBoardBufferQueuesPageDetailsView();

	// Attributes
private:
	CTCOnBoardBufferQueuesPageDetailsTextView  *m_pwndList;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetLayout(UINT nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(UINT &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(COLORREF nColor);
	BOOL GetGridBackgroundColor(COLORREF &nColor) CONST;

	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL StopMonitoring();

	BOOL SetQueues(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetQueues(CTCOnBoardBufferQueues &pQueues) CONST;

	BOOL SetCurQueue(INT nIndex);
	BOOL CheckCurQueue(UINT nFlags) CONST;
	INT GetCurQueue() CONST;

	UINT GetQueueCount() CONST;

	BOOL SetCurTelecommand(INT nIndex);
	INT GetCurTelecommand() CONST;

	BOOL SelectTelecommand(INT nIndex);
	BOOL HasSelectedTelecommands() CONST;

	UINT GetTelecommandCount() CONST;

	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;
	BOOL DoDeleteTelecommand();
	BOOL CanDeleteTelecommand() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL GetPrintProperties(CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContent(BOOL bRedraw = TRUE);

	class CTCOnBoardBufferQueuesWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesPageDetailsView)
public:
	virtual BOOL SetLayoutInfo(CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesPageDetailsView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesPage window

class CTCOnBoardBufferQueuesPage : public CSplitterWndEx
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesPage)

	// Construction
public:
	CTCOnBoardBufferQueuesPage();

	// Attributes
private:
	CTCOnBoardBufferQueuesPageSummaryView  *m_pSummaryView;
	CTCOnBoardBufferQueuesPageDetailsView  *m_pDetailsView;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST CUIntArray *pSummaryPaneColumns, CONST CUIntArray *pSummaryPaneColumnWidths, CONST SIZE *pSummaryPaneList, CONST LOGFONT *plfSummaryTitleFont, CONST LOGFONT *plfSummaryItemsFont, CONST CUIntArray *pDetailsPaneColumns, CONST CUIntArray *pDetailsPaneColumnWidths, CONST SIZE *pDetailsPaneList, CONST LOGFONT *plfDetailsTitleFont, CONST LOGFONT *plfDetailsItemsFont, BOOL bVisible = TRUE);

	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizePane);
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizePane) CONST;

	BOOL SetListTitleFont(UINT nPane, CFont *pFont);
	BOOL SetListTitleFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListTitleFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(UINT nPane, CFont *pFont);
	BOOL SetListItemsFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetListItemsFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(UINT nPane, COLORREF nColor);
	BOOL GetGridBackgroundColor(UINT nPane, COLORREF &nColor) CONST;

	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL StopMonitoring();

	BOOL SetQueues(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetQueues(CTCOnBoardBufferQueues &pQueues) CONST;

	BOOL SetCurQueue(INT nIndex);
	BOOL CheckCurQueue(UINT nFlags) CONST;
	INT GetCurQueue() CONST;

	UINT GetQueueCount() CONST;

	BOOL DoAcknowledgeQueue();
	BOOL CanAcknowledgeQueue() CONST;

	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;
	BOOL DoDeleteTelecommand();
	BOOL CanDeleteTelecommand() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL GetPrintProperties(CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo, CStringArray &szSummaryColumns, CStringArray &szSummaryContents, CTextViewAttributes &pSummaryAttributes, LOGFONT *pSummaryTitleFont, LOGFONT *pSummaryItemsFont, CStringArray &szDetailsColumns, CStringArray &szDetailsContents, CTextViewAttributes &pDetailsAttributes, LOGFONT *pDetailsTitleFont, LOGFONT *pDetailsItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContents(BOOL bRedraw = TRUE);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	CTCOnBoardBufferQueuesPageSummaryView *GetSummaryView() CONST;
	CTCOnBoardBufferQueuesPageDetailsView *GetDetailsView() CONST;

	class CTCOnBoardBufferQueuesView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesPage)
public:
	virtual BOOL SetLayoutInfo(UINT nPane, INT nQueue, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(UINT nPane, INT &nQueue, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
protected:
	virtual void StartTracking(int ht);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardBufferQueuesPage)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesView window

class CTCOnBoardBufferQueuesView : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCOnBoardBufferQueuesView)

	// Construction
public:
	CTCOnBoardBufferQueuesView();

	// Attributes
private:
	INT  m_nIndex;
	CFont  m_cTabFont;
	CSize  m_sizeTabMargins;
	CStringArray  m_szPages;
	CPtrArray  m_pPages;
private:
	CPtrArray  m_pPanes[2];
	CPtrArray  m_pColumns[2];
	CPtrArray  m_pColumnWidths[2];
	CPtrArray  m_pFonts[2][2];
	CDWordArray  m_nColors[2];
	BOOL  m_bFullView;
	BOOL  m_bToolTips;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle);

	BOOL SetLayout(LPCTSTR pszPage, UINT nPane, CONST CUIntArray &nColumns);
	BOOL SetLayout(LPCTSTR pszPage, UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(LPCTSTR pszPage, UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizePane);
	BOOL GetLayout(LPCTSTR pszPage, UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetLayout(LPCTSTR pszPage, UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(LPCTSTR pszPage, UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizePane) CONST;

	BOOL SetListTitleFont(LPCTSTR pszPage, UINT nPane, CFont *pFont);
	BOOL SetListTitleFont(LPCTSTR pszPage, UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(LPCTSTR pszPage, UINT nPane, CFont *pFont) CONST;
	BOOL GetListTitleFont(LPCTSTR pszPage, UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(LPCTSTR pszPage, UINT nPane, CFont *pFont);
	BOOL SetListItemsFont(LPCTSTR pszPage, UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(LPCTSTR pszPage, UINT nPane, CFont *pFont) CONST;
	BOOL GetListItemsFont(LPCTSTR pszPage, UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(LPCTSTR pszPage, UINT nPane, COLORREF nColor);
	BOOL GetGridBackgroundColor(LPCTSTR pszPage, UINT nPane, COLORREF &nColor) CONST;

	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL StopMonitoring();

	INT EnumQueuePages(CStringArray &szPages) CONST;
	BOOL SetQueuePage(LPCTSTR pszPage);
	CString GetQueuePage() CONST;

	BOOL SetQueues(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL SetQueues(LPCTSTR pszPage, CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetQueues(CTCOnBoardBufferQueues &pQueues) CONST;
	BOOL GetQueues(LPCTSTR pszPage, CTCOnBoardBufferQueues &pQueues) CONST;

	BOOL SetCurQueue(INT nIndex);
	BOOL SetCurQueue(LPCTSTR pszPage, INT nIndex);
	BOOL CheckCurQueue(UINT nFlags) CONST;
	BOOL CheckCurQueue(LPCTSTR pszPage, UINT nFlags) CONST;
	INT GetCurQueue() CONST;
	INT GetCurQueue(LPCTSTR pszPage) CONST;

	UINT GetQueueCount() CONST;
	UINT GetQueueCount(LPCTSTR pszPage) CONST;

	BOOL DoAcknowledgeQueue();
	BOOL CanAcknowledgeQueue() CONST;

	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;
	BOOL DoDeleteTelecommand();
	BOOL CanDeleteTelecommand() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL GetPrintProperties(CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo, CStringArray &szSummaryColumns, CStringArray &szSummaryContents, CTextViewAttributes &pSummaryAttributes, LOGFONT *pSummaryTitleFont, LOGFONT *pSummaryItemsFont, CStringArray &szDetailsColumns, CStringArray &szDetailsContents, CTextViewAttributes &pDetailsAttributes, LOGFONT *pDetailsTitleFont, LOGFONT *pDetailsItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContents(BOOL bRedraw = TRUE);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	CSize GetMargins() CONST;

	class CTCOnBoardBufferQueuesWnd *GetParent() CONST;

private:
	INT EnumPages(CStringArray &szPages) CONST;

	INT FindPage(LPCTSTR pszPage) CONST;
	INT FindPage(CTCOnBoardBufferQueue *pQueue) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesView)
public:
	virtual BOOL SetLayoutInfo(LPCTSTR pszPage, UINT nPane, INT nQueue, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(LPCTSTR pszPage, UINT nPane, INT &nQueue, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RecalcLayout();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSelchangePage(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueuesWnd frame

// Specify the telecommand on-board buffer queues display panes
#define TCONBOARDBUFFERQUEUES_PANE_SUMMARY   (1<<0)
#define TCONBOARDBUFFERQUEUES_PANE_DETAILS   (1<<1)
#define TCONBOARDBUFFERQUEUES_PANES   2
// Specify the telecommand on-board buffer queues display title items
#define TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_NAME   (1<<0)
#define TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_APID   (1<<1)
#define TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_SUBSCHEDULEID   (1<<2)
#define TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_LIMIT   (1<<3)
#define TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_COUNT   (1<<4)
#define TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_UPDATETIME   (1<<5)
#define TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_STATUS   (1<<6)
#ifndef RC_INVOKED
#define TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEMS_DEFAULT   (TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_NAME | TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_APID | TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_SUBSCHEDULEID | TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_LIMIT | TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_COUNT | TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_STATUS)
#define TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEMS_ALL   (TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEMS_DEFAULT | TCONBOARDBUFFERQUEUESSUMMARY_TITLEITEM_UPDATETIME)
#endif
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_NUMBER   (1<<0)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_NAME   (1<<1)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_COMPUTER   (1<<2)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_COMMANDSOURCE   (1<<3)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_DESCRIPTION   (1<<4)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_CATEGORY   (1<<5)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_SUBSYSTEM   (1<<6)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_ARGUMENTS   (1<<7)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_FLAGS   (1<<8)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_TCPACKET   (1<<9)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PSC   (1<<10)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_DISPATCHTIME   (1<<11)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_RELEASETIME   (1<<12)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_RELEASETIMEOFFSET   (1<<13)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_TRANSMISSIONTIME   (1<<14)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_EXECUTIONTIME   (1<<15)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_EXECUTIONTIMEOFFSET   (1<<16)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_AUTHORIZATION   (1<<17)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PTVTIMEWINDOW   (1<<18)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PTVCHECKS   (1<<19)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PTVRESULT   (1<<20)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PEVCHECKS   (1<<21)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PEVRESULT   (1<<22)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_CEVTIMEWINDOW   (1<<23)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_CEVCHECKS   (1<<24)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_CEVRESULT   (1<<25)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_STATUS   (1<<26)
#ifndef RC_INVOKED
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEMS_DEFAULT   (TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_NUMBER | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_NAME | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_DESCRIPTION | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_ARGUMENTS | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_FLAGS | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_RELEASETIME | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_RELEASETIMEOFFSET | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_TRANSMISSIONTIME | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_EXECUTIONTIME | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_EXECUTIONTIMEOFFSET | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_CEVCHECKS | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_CEVRESULT | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_STATUS)
#define TCONBOARDBUFFERQUEUESDETAILS_TITLEITEMS_ALL   (TCONBOARDBUFFERQUEUESDETAILS_TITLEITEMS_DEFAULT | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_COMPUTER | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_COMMANDSOURCE | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_CATEGORY | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_SUBSYSTEM | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_TCPACKET | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PSC | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_DISPATCHTIME | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PTVTIMEWINDOW | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PTVCHECKS | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PTVRESULT | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PEVCHECKS | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_PEVRESULT | TCONBOARDBUFFERQUEUESDETAILS_TITLEITEM_CEVTIMEWINDOW)
#endif
// Specify the telecommand on-board buffer queues display print modes
#define TCONBOARDBUFFERQUEUES_PRINT_SUMMARY   (1<<0)
#define TCONBOARDBUFFERQUEUES_PRINT_QUEUE   (1<<1)
#define TCONBOARDBUFFERQUEUES_PRINT_ITEMRANGE   (1<<2)
#define TCONBOARDBUFFERQUEUES_PRINT_TIMERANGE   (1<<3)
#define TCONBOARDBUFFERQUEUES_PRINT_CLEARCOMMENTS   (1<<4)
// Specify the telecommand on-board buffer queues display print fonts
#define TCONBOARDBUFFERQUEUES_PRINTFONT_TITLE   0
#define TCONBOARDBUFFERQUEUES_PRINTFONT_SUBTITLE   1
#define TCONBOARDBUFFERQUEUES_PRINTFONT_DETAILS   2
#define TCONBOARDBUFFERQUEUES_PRINTFONT_COMMENTS   3
#define TCONBOARDBUFFERQUEUES_PRINTFONT_SUMMARYTITLE   4
#define TCONBOARDBUFFERQUEUES_PRINTFONT_SUMMARYLISTITEMSTITLE   5
#define TCONBOARDBUFFERQUEUES_PRINTFONT_SUMMARYLISTITEMS   6
#define TCONBOARDBUFFERQUEUES_PRINTFONT_DETAILSTITLE   7
#define TCONBOARDBUFFERQUEUES_PRINTFONT_DETAILSLISTITEMSTITLE   8
#define TCONBOARDBUFFERQUEUES_PRINTFONT_DETAILSLISTITEMS   9
#define TCONBOARDBUFFERQUEUES_PRINTFONT_FOOTER   10
#define TCONBOARDBUFFERQUEUES_PRINTFONT_NOTICE   11
#define TCONBOARDBUFFERQUEUES_PRINTFONT_LOGO   12
#define TCONBOARDBUFFERQUEUES_PRINTFONTS   13
// Specify the telecommand on-board buffer queues display statusbar pane identifiers
#define ID_TCONBOARDBUFFERQUEUES_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_TCONBOARDBUFFERQUEUES_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_TCONBOARDBUFFERQUEUES_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class CTCOnBoardBufferQueuesWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CTCOnBoardBufferQueuesWnd)

	// Construction
public:
	CTCOnBoardBufferQueuesWnd();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  nIndex;
		INT  cbPages;
	} DATA, *PDATA, *LPDATA;
	typedef struct tagPAGEDATA {
		INT  cbSize;
		INT  cbName;
		INT  nQueue;
		INT  cbColumns[2][2];
		SIZE  sizePanes[2];
		LOGFONT  sFont[2][2];
		COLORREF  nColor;
		SCROLLINFO  sScrollInfo[2][2];
	} PAGEDATA, *PPAGEDATA, *LPPAGEDATA;
private:
	CTCOnBoardBufferQueuesToolBar  m_wndToolBar;
	CTCOnBoardBufferQueuesStatusBar  m_wndStatusBar;
	CTCOnBoardBufferQueuesView  m_wndView;
private:
	CTCOnBoardBufferQueuesSettingsDialog  m_dlgSettings;
	CTCOnBoardBufferQueuesStartPropertiesDialog  m_dlgStart;
	CTCOnBoardBufferQueuesStopPropertiesDialog  m_dlgStop;
	CTCOnBoardBufferQueuesDumpDialog  m_dlgDump;
	CTCOnBoardBufferQueuesResetDialog  m_dlgReset;
private:
	CTCOnBoardBufferQueuesPrintJobs  m_pPrintJobs;

	// Operations
public:
	BOOL SetLayout(LPCTSTR pszPage, UINT nPane, CONST CUIntArray &nColumns);
	BOOL SetLayout(LPCTSTR pszPage, UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(LPCTSTR pszPage, UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizePane);
	BOOL GetLayout(LPCTSTR pszPage, UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetLayout(LPCTSTR pszPage, UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(LPCTSTR pszPage, UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizePane) CONST;

	BOOL SetListTitleFont(LPCTSTR pszPage, UINT nPane, CFont *pFont);
	BOOL SetListTitleFont(LPCTSTR pszPage, UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(LPCTSTR pszPage, UINT nPane, CFont *pFont) CONST;
	BOOL GetListTitleFont(LPCTSTR pszPage, UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(LPCTSTR pszPage, UINT nPane, CFont *pFont);
	BOOL SetListItemsFont(LPCTSTR pszPage, UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(LPCTSTR pszPage, UINT nPane, CFont *pFont) CONST;
	BOOL GetListItemsFont(LPCTSTR pszPage, UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetGridBackgroundColor(LPCTSTR pszPage, UINT nPane, COLORREF nColor);
	BOOL GetGridBackgroundColor(LPCTSTR pszPage, UINT nPane, COLORREF &nColor) CONST;

	BOOL EnableFullViewMode(BOOL bEnable = TRUE);
	BOOL IsFullViewModeEnabled() CONST;
	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL StopMonitoring();

	INT EnumQueuePages(CStringArray &szPages) CONST;
	BOOL SetQueuePage(LPCTSTR pszPage);
	CString GetQueuePage() CONST;

	BOOL SetQueues(CONST CTCOnBoardBufferQueues &pQueues);
	BOOL SetQueues(LPCTSTR pszPage, CONST CTCOnBoardBufferQueues &pQueues);
	BOOL GetQueues(CTCOnBoardBufferQueues &pQueues) CONST;
	BOOL GetQueues(LPCTSTR pszPage, CTCOnBoardBufferQueues &pQueues) CONST;

	BOOL SetCurQueue(INT nIndex);
	BOOL SetCurQueue(LPCTSTR pszPage, INT nIndex);
	BOOL CheckCurQueue(UINT nFlags) CONST;
	BOOL CheckCurQueue(LPCTSTR pszPage, UINT nFlags) CONST;
	INT GetCurQueue() CONST;
	INT GetCurQueue(LPCTSTR pszPage) CONST;

	UINT GetQueueCount() CONST;
	UINT GetQueueCount(LPCTSTR pszPage) CONST;

	BOOL DoAcknowledgeQueue();
	BOOL CanAcknowledgeQueue() CONST;

	BOOL DoCopyTelecommand();
	BOOL CanCopyTelecommand() CONST;
	BOOL DoDeleteTelecommand();
	BOOL CanDeleteTelecommand() CONST;

	BOOL ShowTelecommandProperties();
	BOOL CanShowTelecommandProperties() CONST;
	BOOL IsShowingTelecommandProperties() CONST;

	BOOL SetPrintJobs(CONST CTCOnBoardBufferQueuesPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CTCOnBoardBufferQueuesPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);

private:
	BOOL CreateToolBar();
	BOOL CreateStatusBar();
	BOOL CreateView();

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateModePane();
	VOID UpdateTypePane();

	VOID UpdateContents();

	BOOL SetLayoutInfo(CONST CStringArray &szPages, CONST CUIntArray &nSummaryColumns, CONST CUIntArray &nSummaryWidths, CONST SIZE &sizeSummaryList, CONST CUIntArray &nDetailsColumns, CONST CUIntArray &nDetailsWidths, CONST SIZE &sizeDetailsList, CONST CDWordArray &dwDetailsGridColors);
	BOOL GetLayoutInfo(CStringArray &szPages, CUIntArray &nSummaryColumns, CUIntArray &nSummaryWidths, CSize &sizeSummaryList, CUIntArray &nDetailsColumns, CUIntArray &nDetailsWidths, CSize &sizeDetailsList, CDWordArray &dwDetailsGridColors) CONST;
	BOOL SetFontsInfo(CONST CByteArray &nFontsInfo);
	BOOL GetFontsInfo(CByteArray &nFontsInfo) CONST;

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo, CStringArray &szSummaryColumns, CStringArray &szSummaryContents, CTextViewAttributes &pSummaryAttributes, LOGFONT *pSummaryTitleFont, LOGFONT *pSummaryItemsFont, CStringArray &szDetailsColumns, CStringArray &szDetailsContents, CTextViewAttributes &pDetailsAttributes, LOGFONT *pDetailsTitleFont, LOGFONT *pDetailsItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CStringArray &szSummaryColumns, CONST CStringArray &szSummaryContents, CONST CTextViewAttributes &pSummaryAttributes, CONST LOGFONT *pSummaryTitleFont, CONST LOGFONT *pSummaryItemsFont, CONST CStringArray &szDetailsColumns, CONST CStringArray &szDetailsContents, CONST CTextViewAttributes &pDetailsAttributes, CONST LOGFONT *pDetailsTitleFont, CONST LOGFONT *pDetailsItemsFont, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszTitle, CONST CStringArray &szColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszType, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSymbol(CDC &cDC, LPRECT prClip, UINT nSymbolID, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(LPCTSTR pszType) CONST;
	CString GetPrintDocDetails(CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocComments(CONST CTCOnBoardBufferQueuesPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocListTitle(LPCTSTR pszTitle, LPCTSTR pszQueue, UINT nSubScheduleID) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CONST RECT &rArea, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

private:
	BOOL SetLayoutInfo(INT nIndex, CONST CByteArray &nPagesInfo);
	BOOL GetLayoutInfo(INT &nIndex, CByteArray &nPagesInfo) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardBufferQueuesWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Check() CONST;
	virtual BOOL Stop();
	virtual BOOL Prepare(BOOL bDialog);
	virtual VOID Update();
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
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseSettingsDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardBufferQueuesWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettings();
	afx_msg void OnDetails();
	afx_msg void OnDelete();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnAcknowledge();
	afx_msg void OnDump();
	afx_msg void OnReset();
	afx_msg void OnFullViewMode();
	afx_msg void OnPrint();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDetails(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAcknowledge(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDump(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReset(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFullViewMode(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarModePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarTypePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesProcessorItem

// Specify the various memory image versioning formats
#define TCONBOARDMEMORYIMAGE_VERSIONING_NONE   0
#define TCONBOARDMEMORYIMAGE_VERSIONING_NONUMBER   (1<<0)
#define TCONBAORDMEMORYIMAGE_VERSIONING_SIMPLENUMBER   (1<<1)
#define TCONBAORDMEMORYIMAGE_VERSIONING_COMPLEXTIMENUMBER   (1<<2)
#define TCONBAORDMEMORYIMAGE_VERSIONING_COMPLEXDATANUMBER   (1<<3)

class CTCOnBoardMemoryImagesProcessorItem : public CDatabaseOBProcessor
{
	// Construction
public:
	CTCOnBoardMemoryImagesProcessorItem();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbDumpPacket;
		INT  cbDumpCommand;
		INT  cbPatchCommand;
		INT  cbMemoryImageVersioning;
		UINT  nMemoryImageVersioning[2];
		UINT  nMemoryImageVersionLimit;
		UINT  nDumpIntervalTolerance;
		UINT  nAddressRange[2][2];
		TIMETAG  tLastPatchTime;
		TIMETAG  tLastDumpTime;
	} DATA, *PDATA, *LPDATA;
private:
	CDatabaseOBProcessorMemoryImage  m_cMasterImage;
	CMemoryDumps  m_pMemoryDumps;
	CStringArray  m_szDumpAlerts;
	CTimeKeyArray  m_tDumpAlerts;
	CUIntArray  m_nDumpAlerts;
	CTimeTag  m_tLastDumpTime;
	CTimeTag  m_tLastPatchTime;
	CString  m_szMemoryImageVersioning;
	UINT  m_nMemoryImageVersioning[2];
	UINT  m_nMemoryImageVersionLimit;
	UINT  m_nDumpIntervalTolerance;

	// Operations
public:
	BOOL SetMasterImage(CONST CDatabaseOBProcessorMemoryImage *pImage);
	BOOL GetMasterImage(CDatabaseOBProcessorMemoryImage *pImage) CONST;
	CString GetMasterImage() CONST;
	VOID SetMemoryImageVersioning(LPCTSTR pszPrefix, UINT nFormat, UINT nInfo = 0);
	BOOL GetMemoryImageVersioning(CString &szPrefix, UINT &nFormat, UINT &nInfo) CONST;
	VOID SetMemoryImageVersionLimit(UINT nLimit);
	UINT GetMemoryImageVersionLimit() CONST;
	CString GetMemoryImageVersion(LPCTSTR pszName, INT nIndex) CONST;
	INT FindMemoryImageVersion(LPCTSTR pszName, LPCTSTR pszVersion) CONST;
	INT GetMemoryImageVersionCount(LPCTSTR pszName) CONST;
	BOOL SetMemoryDumps(CONST CMemoryDumps &pDumps);
	INT GetMemoryDumps(CMemoryDumps &pDumps) CONST;
	VOID SetDumpIntervalTolerance(UINT nTolerance);
	UINT GetDumpIntervalTolerance() CONST;
	VOID SetLastPatchTime(CONST CTimeTag &tTime);
	CTimeTag GetLastPatchTime() CONST;
	VOID SetLastDumpTime(CONST CTimeTag &tTime);
	CTimeTag GetLastDumpTime() CONST;
	VOID SetDumpAlerts(CONST CUIntArray &nAlertTypes, CONST CStringArray &szAlerts, CONST CTimeKeyArray &tAlerts);
	INT GetDumpAlerts(CUIntArray &nAlertTypes, CStringArray &szAlerts, CTimeKeyArray &tAlerts) CONST;
	INT GetDumpAlerts(UINT nAlertType = -1) CONST;
	VOID SetLastDumpAlert(UINT nAlertType = -1, LPCTSTR pszAlert = NULL, CONST CTimeKey &tAlert = 0);
	BOOL GetLastDumpAlert(UINT &nAlertType, CString &szAlert, CTimeKey &tAlert) CONST;

	BOOL Copy(CONST CTCOnBoardMemoryImagesProcessorItem *pItem);
	BOOL Compare(CONST CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesProcessorItems

class CTCOnBoardMemoryImagesProcessorItems : public CPtrArray
{
	// Construction
public:
	CTCOnBoardMemoryImagesProcessorItems();
	~CTCOnBoardMemoryImagesProcessorItems();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCOnBoardMemoryImagesProcessorItem *pItem);

	INT Find(LPCTSTR pszName) CONST;

	CTCOnBoardMemoryImagesProcessorItem *GetAt(INT nIndex) CONST;
	CTCOnBoardMemoryImagesProcessorItem *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCOnBoardMemoryImagesProcessorItems *pItems);
	BOOL Compare(CONST CTCOnBoardMemoryImagesProcessorItems *pItems) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDatabaseThread thread

// Specify the on-board memory images database thread related identifiers
#define TCONBOARDMEMORYIMAGESDATABASETHREAD_DBMS_INTERVAL   SECONDSPERMINUTE

class CTCOnBoardMemoryImagesDatabaseThread : public CThread
{
	DECLARE_DYNAMIC(CTCOnBoardMemoryImagesDatabaseThread)

	// Construction
public:
	CTCOnBoardMemoryImagesDatabaseThread();

	// Attributes
private:
	CMutex  *m_pDatabaseMutex;
	CEvent  m_bDatabaseUpdate;
private:
	CStringArray  m_szProcessors;
	CStringArray  m_szErrors[2];
	CDatabaseOBProcessorMemoryImages  m_pMemoryImages;
	CTimeKeyArray  m_tUpdates;
	CUIntArray  m_nActions;
	CTimeSpan  m_tDBMSDelay;
	CString  m_szDBMSDetails;
	BOOL  m_bDBMSStatus;
	BOOL  m_bDBMSQueue;
	BOOL  m_bDBMS;
	BOOL  m_bFile;
private:
	class CTCOnBoardMemoryImagesWnd  *m_pTCOnBoardMemoryImagesWnd;

	// Operations
public:
	BOOL Start(class CTCOnBoardMemoryImagesWnd *pTCOnBoardMemoryImagesWnd, CMutex *pDatabaseMutex);
	BOOL Stop();

	BOOL UpdateMemoryImage(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);

	BOOL SetFlushDelay(CONST CTimeSpan &tDelay);
	BOOL GetFlushDelay(CTimeSpan &tDelay) CONST;
	BOOL EnableFlush(BOOL bDBMS = TRUE, BOOL bFile = TRUE);
	BOOL IsFlushEnabled(BOOL &bDBMS, BOOL &bFile) CONST;

	CString GetDBMSDetails() CONST;
	BOOL IsDBMSOnline() CONST;

private:
	BOOL FlushToDBMS(LPCTSTR pszProcessor, CDatabaseOBProcessorMemoryImage *pImage, UINT nAction);
	BOOL CanFlushToDBMS() CONST;
	BOOL FlushToFile();
	BOOL CanFlushToFile() CONST;

	VOID UpdateDBMSStatus();

	CString ConstructDBMSStatus() CONST;

	VOID ShowErrors();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDatabaseThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesDatabaseThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesPrintJobInfo

class CTCOnBoardMemoryImagesPrintJobInfo : public CObject
{
	// Construction
public:
	CTCOnBoardMemoryImagesPrintJobInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbEvent;
		INT  cbDumps;
		INT  cbProfile;
		INT  cbComments;
		INT  cbProcessor;
		UINT  nPrintMode;
		UINT  nPrintCount;
		UINT  nPrintByCount;
		UINT  nPrintByRange[2];
		UINT  nPrintColumns;
		UINT  nPrintDataBits;
		UINT  nRepeatStopByCount;
		TIMEKEY  tRepeatStopByTime;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szEvent;
	CString  m_szProfile;
	CString  m_szComments;
	CString  m_szProcessor;
	CStringArray  m_szDumps;
	UINT  m_nPrintMode;
	UINT  m_nPrintCount;
	UINT  m_nPrintByCount;
	UINT  m_nPrintByRange[2];
	UINT  m_nPrintColumns;
	UINT  m_nPrintDataBits;
	UINT  m_nRepeatStopByCount;
	CTimeKey  m_tRepeatStopByTime;

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
	BOOL SetPrintBySide(UINT nCount);
	BOOL GetPrintBySide(UINT &nCount) CONST;
	BOOL SetPrintByRange(UINT nFirst, UINT nLast);
	BOOL GetPrintByRange(UINT &nFirst, UINT &nLast) CONST;
	BOOL SetPrintFormat(UINT nColumns, UINT nBits);
	BOOL GetPrintFormat(UINT &nColumns, UINT &nBits) CONST;
	BOOL SetPrintProcessor(LPCTSTR pszProcessor);
	CString GetPrintProcessor() CONST;
	BOOL SetPrintDumps(CONST CStringArray &szDumps);
	INT GetPrintDumps(CStringArray &szDumps) CONST;
	BOOL SetPrintAtEvent(LPCTSTR pszEvent, CONST CTimeKey &tStopTime);
	BOOL SetPrintAtEvent(LPCTSTR pszEvent, UINT nStopCount);
	BOOL GetPrintAtEvent(CString &szEvent, CTimeKey &tStopTime) CONST;
	BOOL GetPrintAtEvent(CString &szEvent, UINT &nStopCount) CONST;
	BOOL SetPrintAtDownload(CONST CTimeKey &tStopTime);
	BOOL SetPrintAtDownload(UINT nStopCount);
	BOOL GetPrintAtDownload(CTimeKey &tStopTime) CONST;
	BOOL GetPrintAtDownload(UINT &nStopCount) CONST;
	BOOL SetPrintCount(UINT nCount);
	BOOL GetPrintCount(UINT &nCount) CONST;

	VOID Copy(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo);
	BOOL Compare(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesPrintJobs

class CTCOnBoardMemoryImagesPrintJobs : public CPtrArray
{
	// Construction
public:
	CTCOnBoardMemoryImagesPrintJobs();
	~CTCOnBoardMemoryImagesPrintJobs();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo);

	INT Find(LPCTSTR pszName) CONST;

	CTCOnBoardMemoryImagesPrintJobInfo *GetAt(INT nIndex) CONST;
	CTCOnBoardMemoryImagesPrintJobInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCOnBoardMemoryImagesPrintJobs *pPrintJobs);
	BOOL Compare(CONST CTCOnBoardMemoryImagesPrintJobs *pPrintJobs) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesSettingsLayoutPage dialog

#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FORMAT   1002
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC   1003
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FORMAT_NAME   1004
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FORMAT_VIEW   1005
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE   1006
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER   1007
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FORMAT_REMOVE   1008
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS   1009
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS   1010
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC   1011
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE   1012
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS   1013
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PAGES   1014
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TABLES   1015
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS   1016
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC   1017
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_NAMES   1018
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC   1019
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_STYLE   1020
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC   1021
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_SIZE   1022
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_SAMPLE   1023
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT   1024

class CTCOnBoardMemoryImagesSettingsLayoutPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesSettingsLayoutPage)

	// Construction
public:
	CTCOnBoardMemoryImagesSettingsLayoutPage();

	// Attributes
private:
	CUIntArray  m_nColumns[2];
	LOGFONT  m_fntTitle[2];
	LOGFONT  m_fntItems[2];
	LOGFONT  m_fntPages[2][2];
	LOGFONT  m_fntTables[2][2];
	COLORREF  m_nTableColors[2][2];
	COLORREF  m_nTableFontColors[2][2];
	BOOL  m_bToolTips[2];
private:
	CString  m_szFontSampleText;
	CStringArray  m_szColumns;
	INT  m_nColumnIndex;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesSettingsLayoutPage)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_SETTINGS_LAYOUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetTitleFont(UINT nPane, LPLOGFONT pTitleFont) CONST;
	BOOL GetItemsFont(UINT nPane, LPLOGFONT pItemsFont) CONST;
	BOOL GetTablesOutline(LPLOGFONT pTitleFont, LPLOGFONT pItemsFont, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, COLORREF &nTitleBackgroundColor, COLORREF &nItemsBackgroundColor) CONST;
	BOOL GetToolTipMode(BOOL &bEnable) CONST;

	class CTCOnBoardMemoryImagesSettingsDialog *GetParentDialog() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

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

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesSettingsLayoutPage)
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
	//{{AFX_MSG(CTCOnBoardMemoryImagesSettingsLayoutPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnInsertColumnBefore();
	afx_msg void OnInsertColumnAfter();
	afx_msg void OnRemoveColumn();
	afx_msg void OnToolTips();
	afx_msg void OnTitleFont();
	afx_msg void OnItemsFont();
	afx_msg void OnPagesFont();
	afx_msg void OnTableProperties();
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
// CTCOnBoardMemoryImagesSettingsDumpsPage dialog

#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_DATABASE_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_DATABASE_DBMS   1003
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_DATABASE_FILE   1004
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_DATABASE_FLUSHDELAY_STATIC   1005
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_DATABASE_FLUSHDELAY_PERIOD   1006
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_DATABASE_FLUSHDELAY_PERIOD_STATIC   1007
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING   1008
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_PROCESSOR_STATIC   1009
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_PROCESSOR   1010
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_STATIC   1011
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_NONE   1012
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_BYNUMBERS   1013
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_COMMENT   1014
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_BYTIME   1015
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_BYTIME_INTERVAL   1016
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_BYTIME_INTERVAL_STATIC   1017
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_BYDATA   1018
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_BYDATA_CHANGES   1019
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_BYDATA_CHANGES_STATIC   1020
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_PREFIX_STATIC   1021
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_PREFIX   1022
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_LIMIT_STATIC   1023
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_LIMIT_COUNT   1024
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_DUMPSPAGE_VERSIONING_LIMIT_COUNT_STATIC   1025

// Specify the telecommand on-board memory images settings dumps page related limits
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_MINIMUMDATABASEFLUSHDELAY   0
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_MAXIMUMDATABASEFLUSHDELAY   SECONDSPERDAY
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_DEFAULTDATABASEFLUSHDELAY   TCONBOARDMEMORYIMAGESDATABASETHREAD_DBMS_INTERVAL
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_MINIMUMVERSIONINGTIMEINTERVAL   1
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_MAXIMUMVERSIONINGTIMEINTERVAL   (52*MINUTESPERWEEK)
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_DEFAULTVERSIONINGTIMEINTERVAL   MINUTESPERDAY
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_MINIMUMVERSIONINGDATACHANGES   1
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_MAXIMUMVERSIONINGDATACHANGES   100
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_DEFAULTVERSIONINGDATACHANGES   10
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_MINIMUMVERSIONINGLIMIT   1
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_MAXIMUMVERSIONINGLIMIT   1000
#define TCONBOARDMEMORYIMAGESSETTINGSDUMPSPAGE_DEFAULTVERSIONINGLIMIT   10

class CTCOnBoardMemoryImagesSettingsDumpsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesSettingsDumpsPage)

	// Construction
public:
	CTCOnBoardMemoryImagesSettingsDumpsPage();

	// Attributes
private:
	BOOL  m_bFlushDumps[2][2];
	CTimeSpan  m_tFlushDumps[2];
	CTCOnBoardMemoryImagesProcessorItems  m_pProcessors[2];

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesSettingsDumpsPage)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_SETTINGS_DUMPSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetVersioning(CTCOnBoardMemoryImagesProcessorItems &pProcessors) CONST;
	BOOL GetFlashBehavior(CTimeSpan &tDelay, BOOL &bDBMS, BOOL &bFile) CONST;

	class CTCOnBoardMemoryImagesSettingsDialog *GetParentDialog() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumProcessors();

	CTCOnBoardMemoryImagesProcessorItem *FindProcessor() CONST;

	VOID ShowProcessorVersioning();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesSettingsDumpsPage)
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
	//{{AFX_MSG(CTCOnBoardMemoryImagesSettingsDumpsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnFlushDBMS();
	afx_msg void OnFlushFile();
	afx_msg void OnVersioningNone();
	afx_msg void OnVersioningByNumbers();
	afx_msg void OnVersioningByTime();
	afx_msg void OnVersioningByData();
	afx_msg void OnEditchangeVersioningPrefix();
	afx_msg void OnSelchangeProcessor();
	afx_msg void OnSpinchangeFlushInterval();
	afx_msg void OnSpinchangeVersioningTimeInterval();
	afx_msg void OnSpinchangeVersioningDataChanges();
	afx_msg void OnSpinchangeVersioningDumpsLimit();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesSettingsLoggingPage dialog

#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_LIST   1002
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_OPTIONS   1003
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_MODE_STATIC   1004
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_REALTIME   1005
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_RELOAD   1006
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_RELOAD_COUNT   1007
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_RELOAD_COUNT_STATIC   1008
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_HISTORICAL   1009
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME_STATIC   1010
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_HISTORICAL_STARTTIME   1011
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATTIME   1012
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_HISTORICAL_STOPTIME   1013
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT   1014
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT   1015
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_HISTORICAL_STOPLIMIT_STATIC   1016
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_HISTORICAL_NOLIMIT   1017
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_HISTORICAL_RETRIEVE   1018
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_LOGGINGPAGE_SHOWASEVENT   1019

// Specify the telecommand on-board memory images settings logging page related limits
#define TCONBOARDMEMORYIMAGESSETTINGSLOGGINGPAGE_MINIMUMRELOADCOUNT   1
#define TCONBOARDMEMORYIMAGESSETTINGSLOGGINGPAGE_MAXIMUMRELOADCOUNT   1000
#define TCONBOARDMEMORYIMAGESSETTINGSLOGGINGPAGE_DEFAULTRELOADCOUNT   25
#define TCONBOARDMEMORYIMAGESSETTINGSLOGGINGPAGE_MINIMUMRETRIEVALSTOPCOUNT   1
#define TCONBOARDMEMORYIMAGESSETTINGSLOGGINGPAGE_MAXIMUMRETRIEVALSTOPCOUNT   10000
#define TCONBOARDMEMORYIMAGESSETTINGSLOGGINGPAGE_DEFAULTRETRIEVALSTOPCOUNT   100
// Specify the telecommand on-board memory images settings logging page related timer identifiers
#define TCONBOARDMEMORYIMAGESSETTINGSLOGGINGPAGE_TIMERID   100
#define TCONBOARDMEMORYIMAGESSETTINGSLOGGINGPAGE_TIMEOUT   500

class CTCOnBoardMemoryImagesSettingsLoggingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesSettingsLoggingPage)

	// Construction
public:
	CTCOnBoardMemoryImagesSettingsLoggingPage();

	// Attributes
private:
	UINT  m_nArchivalPolicy[2];
	UINT  m_nRetrievalReloadCount[2];
	CString  m_szArchivalFileName[2];
	CString  m_szRetrievalFileName[2];
	DWORDLONG  m_dwArchivalRetention[2];
	CTimeSpan  m_tArchivalRetention[2];
	BOOL  m_bShowAsEvent[2];
private:
	CLogFile  m_cRetrievalFile;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesSettingsLoggingPage)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_SETTINGS_LOGGINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	class CTCOnBoardMemoryImagesSettingsDialog *GetParentDialog() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowLoggingDetails();
	VOID ShowLogEntries(CONST CTCLogEntries &pEntries);
	VOID ShowLogEntry(CONST CTCLogEntry *pEntry, INT nIndex = -1);

	BOOL RetrieveLogEntries();
	BOOL RetrieveLogEntries(CTCLogEntries &pEntries);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesSettingsLoggingPage)
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
	//{{AFX_MSG(CTCOnBoardMemoryImagesSettingsLoggingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnRealtime();
	afx_msg void OnHistorical();
	afx_msg void OnReloadCount();
	afx_msg void OnStopAtTime();
	afx_msg void OnStopAtLimit();
	afx_msg void OnStopAtEnd();
	afx_msg void OnOptions();
	afx_msg void OnRetrieve();
	afx_msg void OnShowAsEvent();
	afx_msg void OnSpinchangeReloadCount();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesSettingsPrintingComments window

class CTCOnBoardMemoryImagesSettingsPrintingComments : public CEdit
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesSettingsPrintingComments)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesSettingsPrintingComments)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesSettingsPrintingComments)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesSettingsPrintingPage dialog

#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_NAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_NAME   1003
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_ADDNAME   1004
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_REMOVENAME   1005
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_REMOVEALLNAMES   1006
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES   1007
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC   1008
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE   1009
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS   1010
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL   1011
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE   1012
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE   1013
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC   1014
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT   1015
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYRANGE   1016
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTFROMROW   1017
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYRANGE_STATIC   1018
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTTOROW   1019
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTROW_STATIC   1020
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT   1021
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_COLUMNS_STATIC   1022
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_COLUMNS   1023
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_DATAWIDTH_STATIC   1024
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_DATAWIDTH_BITS   1025
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_DATAWIDTH_BITS_STATIC   1026
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS   1027
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC   1028
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT   1029
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS   1030

// Specify the telecommand on-board memory images settings printing page related limits
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMROWS   1
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMROWS   10000
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTROWS   20
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMCOLUMNS   1
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMCOLUMNS   32
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTCOLUMNS   16
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMDATAWIDTH   4
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMDATAWIDTH   32
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTDATAWIDTH   16

class CTCOnBoardMemoryImagesSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesSettingsPrintingPage)

	// Construction
public:
	CTCOnBoardMemoryImagesSettingsPrintingPage();

	// Attributes
private:
	CTCOnBoardMemoryImagesPrintJobs  m_pJobs[2];
private:
	CTCOnBoardMemoryImagesSettingsPrintingComments  m_wndComments;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesSettingsPrintingPage)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CTCOnBoardMemoryImagesPrintJobs &pJobs) CONST;

	class CTCOnBoardMemoryImagesSettingsDialog *GetParentDialog() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowJobInfo();
	CTCOnBoardMemoryImagesPrintJobInfo *FindJobInfo() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesSettingsPrintingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CTCOnBoardMemoryImagesPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnAddName();
	afx_msg void OnRemoveName();
	afx_msg void OnRemoveAllNames();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnPrintAll();
	afx_msg void OnPrintBySide();
	afx_msg void OnPrintByRange();
	afx_msg void OnPrintByCompleteDump();
	afx_msg void OnChangePrintSide();
	afx_msg void OnSpinchangePrintRows();
	afx_msg void OnSpinchangePrintFromRow();
	afx_msg void OnSpinchangePrintToRow();
	afx_msg void OnSpinchangePrintColumns();
	afx_msg void OnSpinchangePrintDataBits();
	afx_msg void OnEditchangeComments();
	afx_msg void OnResetComments();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesSettingsPrintJobsPage dialog

#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS   1003
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_ADDJOB   1004
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC   1005
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS   1006
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_REMOVEJOB   1007
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR   1008
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PROCESSOR_STATIC   1009
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PROCESSOR   1010
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_DUMPS_STATIC   1011
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_DUMPS   1012
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT   1013
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT   1014
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDOWNLOAD   1015
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOMPLETEDUMPSONLY   1016
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC   1017
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME   1018
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME   1019
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES   1020
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES   1021
#define IDC_TCONBOARDMEMORYIMAGESSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC   1022

// Specify the telecommand on-board memory images settings print jobs page related limits
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTJOBSPAGE_OPTIONS_MINIMUMCOPIES   1
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTJOBSPAGE_OPTIONS_MAXIMUMCOPIES   10000
#define TCONBOARDMEMORYIMAGESSETTINGSPRINTJOBSPAGE_OPTIONS_DEFAULTCOPIES   10

class CTCOnBoardMemoryImagesSettingsPrintJobsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesSettingsPrintJobsPage)

	// Construction
public:
	CTCOnBoardMemoryImagesSettingsPrintJobsPage();

	// Attributes
private:
	CTCOnBoardMemoryImagesPrintJobs  m_pJobs[2];
	CTCOnBoardMemoryImagesProcessorItems  m_pProcessors;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesSettingsPrintJobsPage)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_SETTINGS_PRINTJOBSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	BOOL GetJobs(CTCOnBoardMemoryImagesPrintJobs &pJobs) CONST;

	class CTCOnBoardMemoryImagesSettingsDialog *GetParentDialog() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumJobs();
	BOOL EnumProcessors();
	BOOL EnumDumps();
	BOOL EnumEvents();

	VOID ShowJobInfo();
	BOOL CheckJobInfo() CONST;
	CTCOnBoardMemoryImagesPrintJobInfo *FindJobInfo(BOOL bActive = FALSE) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesSettingsPrintJobsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnDataExchange(CONST CTCOnBoardMemoryImagesPrintJobs &pJobs);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesSettingsPrintJobsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddJob();
	afx_msg void OnRemoveJob();
	afx_msg void OnSelchangeDefinedJob();
	afx_msg void OnSelchangeActiveJob();
	afx_msg void OnSelchangeProcessor();
	afx_msg void OnSelchangeDump();
	afx_msg void OnPrintAtEvent();
	afx_msg void OnPrintAtDownload();
	afx_msg void OnPrintCompleteDumps();
	afx_msg void OnSelchangeEvent();
	afx_msg void OnRepetitionStopByTime();
	afx_msg void OnRepetitionStopByCopies();
	afx_msg void OnSpinchangeRepetitionStopTime();
	afx_msg void OnSpinchangeRepetitionStopCopies();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesSettingsTabCtrl window

class CTCOnBoardMemoryImagesSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesSettingsDialog

class CTCOnBoardMemoryImagesSettingsDialog : public CDisplayPropertySheetDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesSettingsDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesSettingsDialog();

	// Attributes
private:
	CTCOnBoardMemoryImagesSettingsTabCtrl  m_wndTabCtrl;
	CTCOnBoardMemoryImagesSettingsLayoutPage  m_pageLayout;
	CTCOnBoardMemoryImagesSettingsDumpsPage  m_pageDumps;
	CTCOnBoardMemoryImagesSettingsLoggingPage  m_pageLogging;
	CTCOnBoardMemoryImagesSettingsPrintingPage  m_pagePrinting;
	CTCOnBoardMemoryImagesSettingsPrintJobsPage  m_pagePrintJobs;

	// Operations
public:
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayoutTitleFont(UINT nPane, LPLOGFONT pTitleFont) CONST;
	BOOL GetLayoutItemsFont(UINT nPane, LPLOGFONT pItemsFont) CONST;
	BOOL GetLayoutTablesOutline(LPLOGFONT pTitleFont, LPLOGFONT pItemsFont, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, COLORREF &nTitleBackgroundColor, COLORREF &nItemsBackgroundColor) CONST;
	BOOL GetLayoutToolTipMode(BOOL &bEnable) CONST;
	BOOL IsLayoutModified() CONST;

	BOOL GetDumpsVersioning(CTCOnBoardMemoryImagesProcessorItems &pProcessors) CONST;
	BOOL GetDumpsFlashBehavior(CTimeSpan &tDelay, BOOL &bDBMS, BOOL &bFile) CONST;
	BOOL IsDumpsModified() CONST;

	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;
	BOOL IsLoggingModified() CONST;

	BOOL GetPrintJobs(CTCOnBoardMemoryImagesPrintJobs &pPrintJobs) CONST;
	BOOL IsPrintingModified() CONST;

	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesSettingsDialog)
public:
	virtual BOOL OnDataExchange(HWND hPage, CONST CTCOnBoardMemoryImagesPrintJobs &pJobs);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesSettingsDialog)
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
// CTCOnBoardMemoryImagesTablePropertiesDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_TITLE   1003
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_ITEMS   1004
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_NAME_STATIC   1005
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_NAME   1006
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_STYLE_STATIC   1007
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_STYLE   1008
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_SIZE_STATIC   1009
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_SIZE   1010
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_COLOR_STATIC   1011
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_COLOR   1012
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_SAMPLE   1013
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_FONTS_SAMPLETEXT   1014
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_COLORS_STATIC   1015
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_COLORS_TITLE_STATIC 1016
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_COLORS_TITLE   1017
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_COLORS_KEYS_STATIC   1018
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_COLORS_KEYS   1019
#define IDC_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_HELP   1020

class CTCOnBoardMemoryImagesTablePropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesTablePropertiesDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesTablePropertiesDialog();   // standard constructor

	// Attributes
private:
	LOGFONT  m_lfTable[2][2];
	COLORREF  m_nTableColors[2][2];
	COLORREF  m_nTableFontColors[2][2];
	CString  m_szFontSampleText;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesTablePropertiesDialog)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_TABLEPROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, LOGFONT *plfTitleFont, LOGFONT *plfItemsFont, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, COLORREF &nTitleBackgroundColor, COLORREF &nItemsBackgroundColor);

	class CTCOnBoardMemoryImagesSettingsLayoutPage *GetParentDialog() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowFontDetails();
	VOID ShowFontSample();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesTablePropertiesDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesTablePropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg void OnTitleFont();
	afx_msg void OnItemsFont();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeFontColor();
	afx_msg void OnSelchangeTitleBackgroundColor();
	afx_msg void OnSelchangeKeysBackgroundColor();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesLoggingOptionsDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_FILENAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_FILENAME   1003
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_BROWSE   1004
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_DISABLED   1005
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_RETRIEVALS   1006
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_POLICY   1007
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_POLICY_OVERWRITE   1008
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_POLICY_OLDOVERWRITE   1009
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_POLICY_DAYS_STATIC   1010
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_POLICY_DAYS   1011
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_POLICY_NOOVERWRITE   1012
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_SIZE   1013
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_SIZE_UNLIMITED   1014
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_SIZE_LIMITED   1015
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_SIZE_MAXIMUM_STATIC   1016
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_SIZE_MAXIMUM   1017
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_SIZE_RESET   1018
#define IDC_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_HELP   1019

// Specify the telecommand on-board memory images logging options dialog related settings
#define TCONBOARDMEMORYIMAGESLOGGINGOPTIONS_MINIMUMDAYS   1
#define TCONBOARDMEMORYIMAGESLOGGINGOPTIONS_MAXIMUMDAYS   10000
#define TCONBOARDMEMORYIMAGESLOGGINGOPTIONS_DEFAULTDAYS   DAYSPERWEEK
#define TCONBOARDMEMORYIMAGESLOGGINGOPTIONS_MINIMUMSIZE   8
#define TCONBOARDMEMORYIMAGESLOGGINGOPTIONS_MAXIMUMSIZE   2147483647
#define TCONBOARDMEMORYIMAGESLOGGINGOPTIONS_DEFAULTSIZE   (LOGFILE_DEFAULT_SIZE/1024)

class CTCOnBoardMemoryImagesLoggingOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesLoggingOptionsDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesLoggingOptionsDialog();   // standard constructor

	// Attributes
private:
	CString  m_szArchivalFileName[2];
	CString  m_szRetrievalFileName[2];
	DWORDLONG  m_dwArchivalRetention[2];
	CTimeSpan  m_tArchivalRetention[2];
	UINT  m_nArchivalPolicy[2];

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesLoggingOptionsDialog)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_LOGGINGOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CString &szArchivalFileName, UINT &nArchivalPolicy, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName);

	class CTCOnBoardMemoryImagesLoggingPage *GetParentDialog() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowLoggingOptions();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesLoggingOptionsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesLoggingOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRetrievals();
	afx_msg void OnBrowseFileName();
	afx_msg void OnOverwriteLogs();
	afx_msg void OnOverwriteOldLogs();
	afx_msg void OnOverwriteNoLogs();
	afx_msg void OnUnlimitedSize();
	afx_msg void OnLimitedSize();
	afx_msg void OnResetSize();
	afx_msg void OnDisabled();
	afx_msg void OnSpinchangeDays();
	afx_msg void OnSpinchangeSize();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesRetrievalOptionsDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_RETRIEVALOPTIONS_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_RETRIEVALOPTIONS_FILENAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_RETRIEVALOPTIONS_FILENAME   1003
#define IDC_TCONBOARDMEMORYIMAGES_RETRIEVALOPTIONS_BROWSE   1004
#define IDC_TCONBOARDMEMORYIMAGES_RETRIEVALOPTIONS_HELP   1005

class CTCOnBoardMemoryImagesRetrievalOptionsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesRetrievalOptionsDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesRetrievalOptionsDialog();   // standard constructor

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesRetrievalOptionsDialog)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_RETRIEVALOPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CString &szFileName);

	class CTCOnBoardMemoryImagesLoggingOptionsDialog *GetParentDialog() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesRetrievalOptionsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesRetrievalOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowseFileName();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesToolBar window

class CTCOnBoardMemoryImagesToolBar : public CDisplayToolBar
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesToolBar)

	// Construction
public:
	CTCOnBoardMemoryImagesToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesStatusBar window

// Specify the telecommand on-board memory images statusbar related timer identifiers
#define TCONBOARDMEMORYIMAGESSTATUSBAR_UPDATE_TIMERID   100
#define TCONBOARDMEMORYIMAGESSTATUSBAR_UPDATE_TIMEOUT   (1000*TCONBOARDMEMORYIMAGESDATABASETHREAD_DBMS_INTERVAL)

class CTCOnBoardMemoryImagesStatusBar : public CDisplayStatusBar
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesStatusBar)

	// Construction
public:
	CTCOnBoardMemoryImagesStatusBar();

	// Attributes
private:
	CToolTipCtrl  m_wndToolTip;
	CString  m_szToolTipText;
	BOOL  m_bToolTipText;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	class CTCOnBoardMemoryImagesWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesToolTip window

class CTCOnBoardMemoryImagesToolTip : public CDisplayToolTip
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesToolTip)

	// Construction
public:
	CTCOnBoardMemoryImagesToolTip();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesToolTip)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesTableViewUndoItem

class CTCOnBoardMemoryImagesTableViewUndoItem : public CObject
{
	// Construction
public:
	CTCOnBoardMemoryImagesTableViewUndoItem();

	// Attributes
private:
	CString  m_szTable;
	CString  m_szContext;
	CString  m_szText[2];
	CPoint  m_ptCell;
	BOOL  m_bUpdates;
	BOOL  m_bActivation;
	BOOL  m_bSelection;
	INT  m_nAlignment;
	INT  m_nSel[2];
private:
	BOOL  m_bCollected;

	// Operations
public:
	VOID SetInfo(LPCTSTR pszTable, CONST POINT &ptCell, INT nAlignment, LPCTSTR pszText, LPCTSTR pszInitialText, INT nStartPos = -1, INT nEndPos = -1);
	VOID GetInfo(CString &szTable, CPoint &ptCell, INT &nAlignment, CString &szText, CString &szInitialText, INT &nStartPos, INT &nEndPos) CONST;
	VOID SetCell(LPCTSTR pszTable, CONST POINT &ptCell);
	BOOL GetCell(CString &szTable, CPoint &ptCell) CONST;
	VOID SetContext(LPCTSTR pszContext);
	CString GetContext() CONST;
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;
	VOID SetInitialText(LPCTSTR pszText);
	CString GetInitialText() CONST;
	VOID SetSel(INT nStartPos, INT nEndPos);
	VOID GetSel(INT &nStartPos, INT &nEndPos) CONST;
	VOID SetAlignment(INT nAlignment);
	INT GetAlignment() CONST;
	VOID AllowUpdates(BOOL bEnable = TRUE);
	BOOL CanUpdate() CONST;
	VOID AllowActivation(BOOL bEnable = TRUE);
	BOOL CanActivate() CONST;
	VOID AllowSelection(BOOL bEnable = TRUE);
	BOOL CanSelect() CONST;

	VOID Collect(BOOL bEnable = TRUE);
	BOOL IsCollected() CONST;

	VOID Clear();

	VOID Copy(CONST CTCOnBoardMemoryImagesTableViewUndoItem *pItem);
	BOOL Compare(CONST CTCOnBoardMemoryImagesTableViewUndoItem *pItem) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesTableViewUndoList

class CTCOnBoardMemoryImagesTableViewUndoList : public CPtrArray
{
	// Construction
public:
	CTCOnBoardMemoryImagesTableViewUndoList();
	~CTCOnBoardMemoryImagesTableViewUndoList();

	// Attributes
private:
	INT  m_nIndex;
	INT  m_nCount;
	BOOL  m_bUndoing;
	BOOL  m_bCollecting;
private:
	UINT  m_nLocks;

	// Operations
public:
	BOOL Add(CONST CTCOnBoardMemoryImagesTableViewUndoItem *pItem, BOOL bUpdates = FALSE);

	BOOL Undo(CTCOnBoardMemoryImagesTableViewUndoItem *pItem, BOOL bFocus);
	BOOL Undo(CONST CTableViewCell *pCell, CString &szText);
	BOOL CanUndo(BOOL bFocus) CONST;
	BOOL CanCollectUndo() CONST;
	BOOL Redo(CTCOnBoardMemoryImagesTableViewUndoItem *pItem, BOOL bFocus);
	BOOL Redo(CONST CTableViewCell *pCell, CString &szText);
	BOOL CanRedo(BOOL bFocus) CONST;
	BOOL CanCollectRedo() CONST;

	VOID Collect(BOOL bEnable = TRUE, INT nAfter = 0);
	BOOL IsCollecting() CONST;

	CTCOnBoardMemoryImagesTableViewUndoItem *GetAt(INT nIndex) CONST;
	CTCOnBoardMemoryImagesTableViewUndoItem *operator[](INT nIndex) CONST;

	VOID Reset();

	BOOL Lock();
	BOOL IsLocked() CONST;
	BOOL Unlock();

private:
	BOOL IsCellAction(INT nIndex) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesTableViewUndoLists

class CTCOnBoardMemoryImagesTableViewUndoLists : public CPtrArray
{
	// Construction
public:
	CTCOnBoardMemoryImagesTableViewUndoLists();
	~CTCOnBoardMemoryImagesTableViewUndoLists();

	// Attributes
private:
	CString  m_szKey[3];
	CStringArray  m_szKeys;

	// Operations
public:
	INT Add(LPCTSTR pszMemoryArea, LPCTSTR pszMemoryImage, LPCTSTR pszImageVersion, CTCOnBoardMemoryImagesTableViewUndoList *pUndoList);
	BOOL Remove(LPCTSTR pszMemoryArea, LPCTSTR pszMemoryImage, LPCTSTR pszImageVersion);

	BOOL Select(LPCTSTR pszMemoryArea, LPCTSTR pszMemoryImage, LPCTSTR pszImageVersion);
	INT Find(LPCTSTR pszMemoryArea, LPCTSTR pszMemoryImage, LPCTSTR pszImageVersion) CONST;

	CTCOnBoardMemoryImagesTableViewUndoList *GetAt(INT nIndex) CONST;
	CTCOnBoardMemoryImagesTableViewUndoList *operator[](INT nIndex) CONST;

	VOID RemoveAll();

public:
	BOOL Add(CONST CTCOnBoardMemoryImagesTableViewUndoItem *pItem, BOOL bUpdates = FALSE);

	BOOL Undo(CTCOnBoardMemoryImagesTableViewUndoItem *pItem, BOOL bFocus);
	BOOL Undo(CONST CTableViewCell *pCell, CString &szText);
	BOOL CanUndo(BOOL bFocus) CONST;
	BOOL CanCollectUndo() CONST;
	BOOL Redo(CTCOnBoardMemoryImagesTableViewUndoItem *pItem, BOOL bFocus);
	BOOL Redo(CONST CTableViewCell *pCell, CString &szText);
	BOOL CanRedo(BOOL bFocus) CONST;
	BOOL CanCollectRedo() CONST;

	VOID Collect(BOOL bEnable = TRUE, INT nAfter = 0);
	BOOL IsCollecting() CONST;

	VOID Reset();

	BOOL Lock();
	BOOL IsLocked() CONST;
	BOOL Unlock();

private:
	INT FindIndex(LPCTSTR pszMemoryArea, LPCTSTR pszMemoryImage, LPCTSTR pszImageVersion, BOOL bInsert = FALSE) CONST;

	CString ConstructKey(LPCTSTR pszMemoryArea, LPCTSTR pszMemoryImage, LPCTSTR pszImageVersion) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDocument

class CTCOnBoardMemoryImagesDocument : public CDocument
{
	DECLARE_DYNAMIC(CTCOnBoardMemoryImagesDocument)

	// Construction
public:
	CTCOnBoardMemoryImagesDocument();
	virtual ~CTCOnBoardMemoryImagesDocument();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesTableView view

// Specify the telecommand on-board memory images table view form related timer identifiers
#define TCONBOARDMEMORYIMAGESTABLEVIEW_ACTIVATION_TIMERID   100
#define TCONBOARDMEMORYIMAGESTABLEVIEW_ACTIVATION_TIMEOUT   0

class CTCOnBoardMemoryImagesTableView : public CDatabaseTableView
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesTableView)

	// Construction
public:
	CTCOnBoardMemoryImagesTableView();

	// Attributes
private:
	CBitmap  m_cImage;
	LOGFONT  m_lfTable[2];
	CString  m_szImage[2][2];
	CString  m_szMemoryArea;
	CString  m_szLastError;
	CStringArray  m_szTables;
	CTCOnBoardMemoryImagesToolTip  m_wndToolTip;
	CTCOnBoardMemoryImagesTableViewUndoLists  m_cUndoLists;
	COLORREF  m_nTableFontColors[2];
	COLORREF  m_nTableColors[2];
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bToolTips;
	BOOL  m_bShowAll;
	BOOL  m_bUndo[2];
	BOOL  m_bUpdate;
	BOOL  m_bImage;
private:
	CTCOnBoardMemoryImagesProcessorItem  m_cItem[2];

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, LPCTSTR pszTable);

	BOOL SetTableContents();
	BOOL SetTableContents(CONST CMemoryDump *pDump);
	BOOL SetTableContents(CONST CMemoryDumps &pDumps);
	BOOL SetTableContents(CONST CTCOnBoardMemoryImagesProcessorItem *pItem, BOOL bAll = TRUE);
	BOOL SetTableContents(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL SetTableContents(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, BOOL bOverwrite, BOOL bDelete);
	BOOL SetTableContents(LPCTSTR pszMemoryArea, LPCTSTR pszImage, LPCTSTR pszVersion, LPCTSTR pszComparedImage = EMPTYSTRING, LPCTSTR pszComparedVersion = EMPTYSTRING, BOOL bShowAll = FALSE, BOOL bUpdate = TRUE);
	BOOL GetTableContents(CString &szMemoryArea, CString &szImage, CString &szVersion, CString &szComparedImage, CString &szComparedVersion) CONST;
	BOOL GetTableContents(CDatabaseOBProcessorMemoryImage *pMemoryImage, BOOL bComparedImage = FALSE) CONST;
	BOOL GetTableContents(CDatabaseOBProcessorMemoryArea *pMemoryArea, BOOL bComparedArea = FALSE) CONST;
	BOOL GetTableContents(CMemoryDump *pDump) CONST;
	BOOL GetTableContents(CMemoryDumps &pDumps) CONST;
	UINT GetTableContents(CString &szContents) CONST;
	CTCOnBoardMemoryImagesProcessorItem *GetTableContents() CONST;
	VOID SetTableFonts(CONST LOGFONT *plfTitleFont, CONST LOGFONT *plfItemsFont);
	VOID SetTableFonts(CTableViewObject *pTable, CONST LOGFONT *plfTitleFont, CONST LOGFONT *plfItemsFont);
	BOOL GetTableFonts(LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST;
	BOOL GetTableFonts(CONST CTableViewObject *pTable, LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST;
	VOID SetTableFontColors(COLORREF nTitleColor, COLORREF nItemsColor);
	VOID GetTableFontColors(COLORREF &nTitleColor, COLORREF &nItemsColor) CONST;
	VOID SetTableColors(COLORREF nTitleBackground, COLORREF nKeysBackground);
	VOID GetTableColors(COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;
	VOID SetTableError(LPCTSTR pszError);
	BOOL GetTableError(CString &szError) CONST;

	BOOL DoSaveTable();
	BOOL CanSaveTable() CONST;
	BOOL DoDeleteTable();
	BOOL CanDeleteTable() CONST;
	BOOL DoImportTables();
	BOOL CanImportTables() CONST;
	BOOL DoExportTables();
	BOOL CanExportTables() CONST;
	BOOL DoDiscardTables();
	BOOL CanDiscardTables() CONST;
	BOOL DoDiscardAllTables();
	BOOL CanDiscardAllTables() CONST;
	BOOL DoResetTables();
	BOOL CanResetTables() CONST;
	BOOL DoInsertTableRowAbove();
	BOOL CanInsertTableRowAbove() CONST;
	BOOL DoInsertTableRowBelow();
	BOOL CanInsertTableRowBelow() CONST;
	BOOL DoInsertTableColumnBefore();
	BOOL CanInsertTableColumnBefore() CONST;
	BOOL DoInsertTableColumnAfter();
	BOOL CanInsertTableColumnAfter() CONST;
	BOOL DoClearTableRow();
	BOOL CanClearTableRow() CONST;
	BOOL DoDeleteTableRow();
	BOOL CanDeleteTableRow() CONST;
	BOOL DoDeleteTableColumn();
	BOOL CanDeleteTableColumn() CONST;
	BOOL DoCopyTableRow();
	BOOL CanCopyTableRow() CONST;
	BOOL DoPasteTableRow();
	BOOL CanPasteTableRow() CONST;

	VOID DoSelectAll();
	BOOL CanSelectAll() CONST;
	VOID UnSelectAll();
	VOID DoCutSel();
	BOOL CanCutSel() CONST;
	VOID DoCopySel();
	BOOL CanCopySel() CONST;
	VOID DoPasteSel();
	BOOL CanPasteSel() CONST;
	VOID DoDeleteSel();
	BOOL CanDeleteSel() CONST;
	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;
	BOOL DoEmpty();
	BOOL IsEmpty() CONST;

	BOOL Print(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, CMetaFileDC &cMetaDC);

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL Check(CString &szError) CONST;
	BOOL IsModified() CONST;

	class CLocaleDialog *GetParent() CONST;

private:
	VOID BeginTableUpdate();
	VOID EndTableUpdate();

	VOID RefreshTables(BOOL bAll = TRUE);
	VOID RefreshTables(CONST CStringArray &szTables, BOOL bAll = TRUE);
	VOID RefreshTables(CONST CTableViewObject *pTable, BOOL bAll = TRUE);
	VOID RefreshTables(UINT nControlID);
	VOID RefreshTables(CONST CStringArray &szTables, UINT nControlID);
	VOID RefreshTable(LPCTSTR pszTable, BOOL bAll = TRUE);
	VOID RefreshTable(CTableViewObject *pTable, LPCTSTR pszValue, UINT nControlID);

	VOID RepositionTables(CONST CTableViewObjects *pTables, LPCTSTR pszTable, INT nOffset);
	VOID RepositionTables(CONST CTableViewObjects *pTables, LPCTSTR pszTable, CStringArray &szTables);
	BOOL InsertTableRow(CTableViewObject *pTable, INT nRow);
	BOOL RemoveTableRow(CTableViewObject *pTable, INT nRow);
	BOOL DeleteTableRow(CTableViewObject *pTable, INT nRow);
	BOOL ResizeTableColumns(CTableViewObject *pTable, INT nCount);
	BOOL InsertTableColumn(CTableViewObject *pTable, INT nCol);
	BOOL DeleteTableColumn(CTableViewObject *pTable, INT nCol);
	INT CalcTableOrder(CONST CTableViewObjects *pTables, LPCTSTR pszTable) CONST;
	VOID CalcTableOrder(CONST CTableViewObjects *pTables, LPCTSTR pszTable, INT &nOrder) CONST;
	INT CalcDefaultTableWidth(CONST CTableViewObject *pTable);
	INT CalcDefaultTableHeight(CONST CTableViewObject *pTable);
	INT CalcDefaultTableMargin(CONST CTableViewObject *pTable);
	INT CalcDefaultCellWidth(CONST CTableViewCell *pCell, UINT nColumnWidth, INT nWidth);
	INT CalcDefaultCellHeight(CONST CTableViewCell *pCell, INT nWidth);
	INT CalcDefaultCellHeight(CONST CTableViewObjects *pTables, CONST CTableViewCell *pCell, INT nWidth);
	INT CalcCellTextFromPoint(CONST CTableViewCell *pCell, CONST POINT &ptCell);
	VOID AdjustCellStyle(CONST CTableViewObject *pTable, CTableViewCell *pCell);

	BOOL ConvertUndoItem(LPCTSTR pszTable, CTCOnBoardMemoryImagesTableViewUndoItem *pItem, BOOL bUpdates = TRUE) CONST;
	BOOL ConvertUndoItem(CWnd *pControl, CTCOnBoardMemoryImagesTableViewUndoItem *pItem, BOOL bUpdates = TRUE) CONST;
	BOOL ConvertUndoItem(CONST CTCOnBoardMemoryImagesTableViewUndoItem *pItem, BOOL bUndo = TRUE);

	INT ExtractTextItems(LPCTSTR pszText, CStringArray &szItems) CONST;

	BOOL CollectData(CByteArray &nData, BYTE nValue, INT nBytePos) CONST;
	BOOL CollectData(CByteArray &nData, ULONGLONG nValue, INT nBytePos, INT nBitPos, INT nLength) CONST;
	BOOL ExtractData(CONST CByteArray &nData, INT nBytePos, BYTE &nValue) CONST;
	BOOL ExtractData(CONST CByteArray &nData, INT nBytePos, INT nBitPos, INT nLength, ULONGLONG &nValue) CONST;

	CString ConstructToolTipTitle(LPCTSTR pszTip, LPCTSTR pszInfo) CONST;
	CString ConstructToolTipText(LPCTSTR pszTip, LPCTSTR pszInfo, LPCTSTR pszValue) CONST;

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesTableView)
private:
	virtual INT EnumTables(CStringArray &szTables, CUIntArray &nTypes, BOOL bMenu, BOOL bResetable = FALSE) CONST;
	virtual BOOL GetTableTitle(LPCTSTR pszTable, CString &szTitle) CONST;
	virtual BOOL GetTableLayout(LPCTSTR pszTable, CUIntArray &nWidths) CONST;
	virtual BOOL GetTableLayout(LPCTSTR pszTable, LPCTSTR pszItem, CUIntArray &nWidths) CONST;
	virtual BOOL GetTablePosition(LPCTSTR pszTable, CString &szTable, CRect &rPosition) CONST;
	virtual BOOL SetTableFloatingAlignment(LPCTSTR pszTable, INT nRow);
	virtual INT GetTableFloatingAlignment(LPCTSTR pszTable) CONST;
	virtual BOOL AlignFloatingTable(LPCTSTR pszTable);
	virtual BOOL GetTableOutline(LPCTSTR pszTable, COLORREF &nTitleRowColor, COLORREF &nFirstRowColor, COLORREF &nFirstColumnColor, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, INT &nOuterBorderSize, INT &nOuterBorderStyle, COLORREF &nOuterBorderColor, INT &nInnerBorderSize, INT &nInnerBorderStyle, COLORREF &nInnerBorderColor) CONST;
	virtual BOOL GetTableOutlineFonts(LPCTSTR pszTable, LOGFONT *plfTitleFont, LOGFONT *plfItemsFont) CONST;
	virtual BOOL GetTableOutlineLimits(LPCTSTR pszTable, INT &nMinRows, INT &nMaxRows) CONST;
	virtual BOOL GetTableContents(LPCTSTR pszTable, LPCTSTR pszItem, INT nRows, CStringArray &szContents, CStringArray &szDescriptions, CStringArray &szDataTypes, CUIntArray &nFormats, CUIntArray &nIDs, BOOL &bResize, BOOL &bVisible) CONST;
	virtual INT EnumTableFieldValues(LPCTSTR pszTable, LPCTSTR pszField, CStringArray &szValues, CLongUIntArray &nValues) CONST;
	virtual BOOL GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, INT &nLow, INT &nHigh) CONST;
	virtual BOOL GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, UINT &uLow, UINT &uHigh) CONST;
	virtual BOOL GetTableFieldLimits(LPCTSTR pszTable, LPCTSTR pszField, double &fLow, double &fHigh) CONST;
	virtual BOOL GetTableContext(LPCTSTR pszTable, CString &szTable, UINT &nControlID, CString &szValue) CONST;
	virtual INT EnumTableUpdates(UINT nControlID, CStringArray &szTables) CONST;
	virtual BOOL GetTableUpdateContents(LPCTSTR pszTable, UINT nControlID, LPCTSTR pszValue, CString &szItem, CStringArray &szContents) CONST;
	virtual BOOL UpdateTableFieldData(UINT nControlID, LPCTSTR pszValue, LPCTSTR pszOldValue = NULL);
	virtual INT InsertTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue);
	virtual BOOL InsertTableFieldData(LPCTSTR pszTable, INT nRow, INT nCol = -1);
	virtual BOOL CheckTableFieldData(LPCTSTR pszTable, BOOL bModified = FALSE, BOOL bExist = FALSE) CONST;
	virtual BOOL CheckTableFieldData(LPCTSTR pszTable, CString &szError, BOOL bModified = FALSE) CONST;
	virtual BOOL CheckTableFieldData(LPCTSTR pszTable, CStringArray &szIssues) CONST;
	virtual BOOL SelectTableFieldData(LPCTSTR pszTable, CONST POINT &pt);
	virtual BOOL SelectTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue);
	virtual BOOL SaveTableFieldData(LPCTSTR pszTable, BOOL bPrompt = FALSE);
	virtual BOOL ProtectTableFieldData(LPCTSTR pszTable, BOOL bUndo = FALSE);
	virtual BOOL DeleteTableFieldData(LPCTSTR pszTable);
	virtual INT DeleteTableFieldData(LPCTSTR pszTable, LPCTSTR pszValue);
	virtual BOOL DeleteTableFieldData(LPCTSTR pszTable, INT nRow, INT nCol = -1);
	virtual BOOL GetTableFieldFlag(LPCTSTR pszTable, INT nRow, INT nCol, CString &szFlag) CONST;
	virtual INT EnumTableDropTargets(ULONGLONG nComponent, CStringArray &szTables, CStringArray &szFields) CONST;
	virtual BOOL FindTableDropTargetCell(LPCTSTR pszTable, LPCTSTR pszField, ULONGLONG nComponent, LPCTSTR pszItem, CString &szItem, INT &nRow, INT &nCol) CONST;
	virtual INT EnumPrintTables(LPCTSTR pszTable, CStringArray &szTables) CONST;
	virtual INT EnumPrintTables(LPCTSTR pszTable, UINT nFlags, CStringArray &szTables) CONST;
	virtual BOOL GetPrintTableContents(LPCTSTR pszTable, LPCTSTR pszItem, CStringArray &szContents) CONST;
	virtual BOOL GetPrintTableContents(LPCTSTR pszTable, UINT nFirstRow, UINT nLastRow, CStringArray &szContents) CONST;
	virtual BOOL PrintTable(LPCTSTR pszTable, LPCTSTR pszItem, CMetaFileDC &cMetaDC);
	virtual BOOL PrintTable(LPCTSTR pszTable, UINT nFirstRow, UINT nLastRow, CMetaFileDC &cMetaDC);
	virtual ULONGLONG TranslateTableNameToComponent(LPCTSTR pszTable) CONST;
	virtual CString TranslateComponentToTableName(ULONGLONG nComponent) CONST;
	virtual INT TranslateTableFieldToIndex(LPCTSTR pszTable, LPCTSTR pszField) CONST;
	virtual UINT TranslateTableFieldToID(LPCTSTR pszTable, LPCTSTR pszField) CONST;
private:
	virtual INT EnumTables(CTableViewObjects *pTables) CONST;
	virtual VOID RepositionTables(CONST CTableViewObjects *pTables);
	virtual VOID RepositionTables();
	virtual VOID ArrangeTables();
	virtual VOID ArrangeTables(UINT nControlID);
	virtual BOOL ActivateTable();
	virtual BOOL ActivateTable(CTableViewObject *pTable, BOOL bPrevious = FALSE);
	virtual BOOL ActivateNextTable(BOOL bPrevious = FALSE);
	virtual BOOL ActivateNextTableCell(BOOL bPrevious = FALSE);
	virtual VOID RecalcTable(CTableViewObject *pTable, BOOL bWidth, BOOL bAdjust, BOOL bRedraw = TRUE);
	virtual VOID RecalcTable(CTableViewObject *pTable, CONST CUIntArray &nWidths, BOOL bAdjust, BOOL bRedraw = TRUE);
	virtual VOID RecalcTable(CONST CTableViewObjects *pTables, CTableViewObject *pTable, CONST CUIntArray &nWidths, BOOL bAdjust, BOOL bRedraw = TRUE);
	virtual VOID RecalcTableRow(CTableViewObject *pTable, INT nRow, BOOL bRedraw = TRUE);
	virtual VOID RecalcTableRow(CONST CTableViewObjects *pTables, CTableViewObject *pTable, INT nRow, BOOL bAdjust);
	virtual VOID UpdateTableContents(CTableViewObject *pTable, CONST CStringArray &szContents);
	virtual VOID UpdateTableContents(CONST CTableViewObjects *pTables, CTableViewObject *pTable, LPCTSTR pszTable, CONST CStringArray &szContents);
	virtual BOOL EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszItem);
	virtual BOOL EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, CONST CStringArray &szValues, CUIntArray &nValues);
	virtual BOOL EnumTableCellValues(CTableViewObject *pTable, CTableViewCell *pCell, CONST CStringArray &szValues, CLongUIntArray &nValues);
	virtual BOOL LimitTableCellValues(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszItem);
	virtual VOID UpdateTableCellValue(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszValue);
	virtual VOID EnableTableCellValue(CONST CTableViewObject *pTable, CTableViewCell *pCell, LPCTSTR pszDefault, BOOL bEnable = TRUE);
	virtual BOOL IsTableRowEmpty(CONST CTableViewObject *pTable, INT nRow) CONST;
	virtual BOOL IsTableRowFull(CONST CTableViewObject *pTable, INT nRow) CONST;
	virtual BOOL IsSubTable(CONST CTableViewObject *pTable) CONST;
private:
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CANDLayout *pLayout, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CGRDLayout *pLayout, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CPODLayout *pLayout, INT nIndex, BOOL bDelete = FALSE);
private:
	virtual VOID UpdateTables(CONST CDatabaseTMPackets &pDatabaseTMPackets);
	virtual VOID UpdateTables(CONST CDatabaseTCFunctions &pDatabaseTCFunctions);
	virtual VOID UpdateTables(CONST CDatabaseTCSequences &pDatabaseTCSequences);
	virtual VOID UpdateTables(CONST CDatabaseOBProcessors &pDatabaseOBProcessors);
	virtual VOID UpdateTables(CONST CDatabaseTMParameters &pDatabaseTMParameters);
	virtual VOID UpdateTables(CONST CDatabaseTCParameters &pDatabaseTCParameters);
	virtual VOID UpdateTables(CONST CANDLayouts &pANDLayouts);
	virtual VOID UpdateTables(CONST CGRDLayouts &pGRDLayouts);
	virtual VOID UpdateTables(CONST CPODLayouts &pPODLayouts);
	virtual BOOL UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete);
	virtual BOOL UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete);
	virtual VOID UpdateTables(ULONGLONG nComponent);
	virtual VOID UpdateTables();
private:
	virtual VOID DrawTables();
	virtual VOID DrawTables(CDC *pDC);
	virtual VOID DrawTables(CDC *pDC, CONST CTableViewObjects *pTables, BOOL bPrinting = FALSE);
	virtual VOID DrawTable(CDC *pDC, CONST CTableViewObject *pTable, BOOL bPrinting = FALSE);
public:
	virtual BOOL EnableTablesAlignment(BOOL bEnable, BOOL bRealign);
	virtual BOOL EnableTablesAlignment(BOOL bEnable);
public:
	virtual BOOL EnableUndo(BOOL bEnable = TRUE);
	virtual BOOL IsUndoing() CONST;
	virtual BOOL IsRedoing() CONST;
	virtual BOOL ClearUndo(LPCTSTR pszMemoryArea, LPCTSTR pszImage, LPCTSTR pszVersion);
	virtual VOID ClearUndo();
private:
	virtual BOOL CheckPrivilege() CONST;
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnActivateView(BOOL bActivate, CView *pActivateView, CView *pDeactiveView);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesTableView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesSummaryTextView window

// Specify the telecommand on-board memory images summary text view command alert symbol identifiers
#define TCONBOARDMEMORYIMAGESSUMMARYTEXTVIEW_ALERTSYMBOL_INFORMATION   0
#define TCONBOARDMEMORYIMAGESSUMMARYTEXTVIEW_ALERTSYMBOL_WARNING   1
#define TCONBOARDMEMORYIMAGESSUMMARYTEXTVIEW_ALERTSYMBOL_ERROR   2
#define TCONBOARDMEMORYIMAGESSUMMARYTEXTVIEW_ALERTSYMBOLS   3
// Specify the telecommand on-board memory images summary text view related timer identifiers
#define TCONBOARDMEMORYIMAGESSUMMARYTEXTVIEW_PROCESSDATA_TIMERID   100
#define TCONBOARDMEMORYIMAGESSUMMARYTEXTVIEW_PROCESSDATA_TIMEOUT   0

class CTCOnBoardMemoryImagesSummaryTextView : public CTextView
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesSummaryTextView)

	// Construction
public:
	CTCOnBoardMemoryImagesSummaryTextView();

	// Attributes
private:
	CStringArray  m_szItems;
	CTCOnBoardMemoryImagesProcessorItems  m_pItems;
private:
	CStringArray  m_szMemoryImages[2];
	CDatabaseOBProcessorMemoryImages  m_pMemoryImages;
private:
	CSize  m_sizeAlertSymbols;
	CImage  *m_pAlertSymbols[TCONBOARDMEMORYIMAGESSUMMARYTEXTVIEW_ALERTSYMBOLS];
	CTCOnBoardBufferQueuesToolTip  m_wndToolTip;
	HCURSOR  m_hToolTipCursor;
	BOOL  m_bToolTips;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle);

	BOOL SetLayout(UINT nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(UINT &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetTitleFont(CFont *pFont);
	BOOL SetTitleFont(CONST LOGFONT *plfFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL GetTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetItemsFont(CFont *pFont);
	BOOL SetItemsFont(CONST LOGFONT *plfFont);
	BOOL GetItemsFont(CFont *pFont) CONST;
	BOOL GetItemsFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetProcessors(CONST CTCOnBoardMemoryImagesProcessorItems &pItems, BOOL bAll = TRUE);
	BOOL GetProcessors(CTCOnBoardMemoryImagesProcessorItems &pItems, BOOL bAll = TRUE) CONST;

	BOOL SetCurProcessor(INT nIndex);
	BOOL SetCurProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem);
	INT GetCurProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem = NULL) CONST;
	BOOL GetCurProcessor(CString &szProcessor) CONST;

	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);

	UINT GetProcessorCount() CONST;

	BOOL DoAcknowledgeProcessor();
	BOOL CanAcknowledgeProcessor() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL GetPrintProperties(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContent(BOOL bRedraw = TRUE);

	class CTCOnBoardMemoryImagesSummaryView *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	CString LookupColumnName(UINT nColumn) CONST;
	UINT LookupColumnName(LPCTSTR pszColumn) CONST;
	INT LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST;
	COLORREF LookupColumnColor(UINT nColumn) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	INT CalcColumnWidth(LPCTSTR pszColumn);
	INT CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths);

	CRect CalcTelecommandSymbolPosition(INT nRow, INT nColumn, LPCTSTR pszText) CONST;

	CString ConstructToolTipTitle(CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;
	CString ConstructToolTipText(CONST CTCOnBoardMemoryImagesProcessorItem *pItem, CONST POINT &ptTip, LPCTSTR pszTip, UINT nTip) CONST;

	BOOL LogDumpVersioning(LPCTSTR pszProcessor);

	BOOL LoadTelecommandSymbols();
	VOID FreeTelecommandSymbols();

	BOOL LoadToolTipCursor();
	HCURSOR GetToolTipCursor() CONST;
	BOOL FreeToolTipCursor();

public:
	static TCHAR GetSymbolDelimiter();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesSummaryTextView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RefreshContent();
public:
	virtual VOID DrawContent();
	virtual VOID DrawContent(CDC *pDC);
	virtual VOID DrawText(INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, LPCTSTR pszText);
	virtual VOID DrawText(INT nItem, INT nColumn, LPCTSTR pszText);
	virtual VOID DrawText(CDC *pDC, INT nItem, INT nColumn, LPCTSTR pszText);
	virtual BOOL DrawBackground(CDC *pDC, INT nItem, INT nColumn, CONST RECT &rItem);
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
	//{{AFX_MSG(CTCOnBoardMemoryImagesSummaryTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesSummaryView view

class CTCOnBoardMemoryImagesSummaryView : public CView
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesSummaryView)

	// Construction
public:
	CTCOnBoardMemoryImagesSummaryView();
	~CTCOnBoardMemoryImagesSummaryView();

	// Attributes
private:
	CTCOnBoardMemoryImagesSummaryTextView  *m_pwndList;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetLayout(UINT nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns);
	BOOL SetLayout(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL GetLayout(UINT &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns) CONST;
	BOOL GetLayout(CUIntArray &nColumns, CUIntArray &nWidths) CONST;

	BOOL SetListTitleFont(CFont *pFont);
	BOOL SetListTitleFont(CONST LOGFONT *plfFont);
	BOOL GetListTitleFont(CFont *pFont) CONST;
	BOOL GetListTitleFont(LOGFONT *plfFont) CONST;
	BOOL SetListItemsFont(CFont *pFont);
	BOOL SetListItemsFont(CONST LOGFONT *plfFont);
	BOOL GetListItemsFont(CFont *pFont) CONST;
	BOOL GetListItemsFont(LOGFONT *plfFont) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetProcessors(CONST CTCOnBoardMemoryImagesProcessorItems &pItems, BOOL bAll = TRUE);
	BOOL GetProcessors(CTCOnBoardMemoryImagesProcessorItems &pItems, BOOL bAll = TRUE) CONST;

	BOOL SetCurProcessor(INT nIndex);
	BOOL SetCurProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem);
	INT GetCurProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem = NULL) CONST;
	BOOL GetCurProcessor(CString &szProcessor) CONST;

	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);

	UINT GetProcessorCount() CONST;

	BOOL DoAcknowledgeProcessor();
	BOOL CanAcknowledgeProcessor() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL GetPrintProperties(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	VOID UpdateContent(BOOL bRedraw = TRUE);

	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesSummaryView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
protected:
	virtual void OnActivateView(BOOL bActivate, CView *pActivateView, CView *pDeactiveView);
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesSummaryView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsDownloadAreasPropertiesDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_NAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_NAME   1003
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_DESCRIPTION   1005
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_EXECUTION_STATIC   1006
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_EXECUTION_IMMEDIATELY   1007
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_EXECUTION_ATTIME   1008
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_EXECUTION_TIME   1009
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_PARAMETERS_STATIC   1010
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_PARAMETERS   1011
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_REMARK_ILLEGALCOMMAND   1012
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_REMARK_OOLPARAMETER   1013
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_DESTINATION_STATIC   1014
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_DESTINATION_MANUALSTACK   1015
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_DESTINATION_AUTOMATICSTACK   1016
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_RELEASE_STATIC   1017
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_RELEASE_IMMEDIATELY   1018
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_RELEASE_ATTIME   1019
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_RELEASE_TIME   1020
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_PREAUTHORIZED   1021
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADAREAS_PROPERTIES_HELP   1022

class CTCOnBoardMemoryImagesDetailsDownloadAreasPropertiesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsDownloadAreasPropertiesDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsDownloadAreasPropertiesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseOBProcessor  m_cProcessor;
	CDatabaseOBProcessorMemoryImage  m_cImage;
private:
	BOOL  m_bFunction;
	CDatabaseTCFunction  m_cFunction;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsDownloadAreasPropertiesDialog)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSAREASDOWNLOAD_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCOnBoardMemoryImagesDetailsAreasPageDialog *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowContents();

	BOOL LogDumpRequest();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsDownloadAreasPropertiesDialog)
public:
	virtual INT DoModal(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage);
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
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsDownloadAreasPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsUploadAreasPropertiesDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_COMMANDS_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_COMMANDS   1003
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_INFORMATION   1004
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_EXECUTION_STATIC   1005
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_EXECUTION_IMMEDIATELY   1006
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_EXECUTION_ATTIME   1007
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_EXECUTION_TIME   1008
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_PARAMETERS_STATIC   1009
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_PARAMETERS   1010
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_REMARK_ILLEGALCOMMAND   1011
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_REMARK_OOLPARAMETER   1012
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_DESTINATION_STATIC   1013
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_DESTINATION_MANUALSTACK   1014
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_DESTINATION_AUTOMATICSTACK   1015
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_RELEASE_STATIC   1016
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_RELEASE_IMMEDIATELY   1017
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_RELEASE_ATTIME   1018
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_RELEASE_TIME   1019
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_PREAUTHORIZED   1020
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADAREAS_PROPERTIES_HELP   1021

class CTCOnBoardMemoryImagesDetailsUploadAreasPropertiesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsUploadAreasPropertiesDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsUploadAreasPropertiesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseOBProcessor  m_cProcessor;
	CDatabaseOBProcessorMemoryImage  m_cImage;
private:
	CDatabaseTCPackets  m_pPackets;
	CDatabaseTCFunctions  m_pFunctions;
	BOOL  m_bFunctions;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsUploadAreasPropertiesDialog)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSAREASUPLOAD_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCOnBoardMemoryImagesDetailsAreasPageDialog *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTelecommands();

	VOID ShowContents();

	BOOL LogPatchRequest();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsUploadAreasPropertiesDialog)
public:
	virtual INT DoModal(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage);
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
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsUploadAreasPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSelchangeTelecommand();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsAreasPageDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_NAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_NAME   1003
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_DESCRIPTION_STATIC   1004
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_DESCRIPTION   1005
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_FLAGS_STATIC   1006
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_FLAGS_PATCHABLE   1007
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_FLAGS_DUMPABLE   1008
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_UPDATES_STATIC   1009
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_UPDATES_AUTOMATIC   1010
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_UPDATES_INHIBITAUTOMATIC   1011
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_ERRORSYMBOL   1012
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_ERRORMESSAGE   1013
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES   1014
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_IMAGE   1015
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_IMAGENAME   1016
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_IMAGEVERSION_STATIC   1017
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_IMAGEVERSION   1018
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_LIST   1019
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_UNDO   1020
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_REDO   1021
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_TRANSACT   1022
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_SAVE   1023
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_UNICODE   1024
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_PRINT   1025
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_DUMP   1026
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSAREAS_PROPERTIES_PATCH   1027

// Specify the telecommand on-board memory images areas page related timer identifiers
#define TCONBOARDMEMORYIMAGESAREAS_CHECKDATA_TIMERID   100
#define TCONBOARDMEMORYIMAGESAREAS_CHECKDATA_TIMEOUT   500

class CTCOnBoardMemoryImagesDetailsAreasPageDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsAreasPageDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsAreasPageDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CWnd  m_wndTableViewCtrl;
	CTCOnBoardMemoryImagesTableView  m_wndTableView;
private:
	CFont  m_cFont;
	CImage  m_cSymbol;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsAreasPageDialog)
public:
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSAREAS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL SetLayout(CONST LOGFONT *plfFont, CONST LOGFONT *plfTableTitleFont, CONST LOGFONT *plfTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL GetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;
	BOOL GetLayout(LOGFONT *plfFont, LOGFONT *plfTableTitleFont, LOGFONT *plfTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;

	BOOL SetProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem, BOOL bAll = TRUE);
	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);
	BOOL GetProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoTransactOnBoardMemoryImage();
	BOOL CanTransactOnBoardMemoryImage() CONST;
	BOOL DoPrintOnBoardMemoryImageTable();
	BOOL CanPrintOnBoardMemoryImageTable() CONST;
	BOOL DoDiscardOnBoardMemoryImageTable();
	BOOL CanDiscardOnBoardMemoryImageTable() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	class CTCOnBoardMemoryImagesDetailsAreasPage *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowProcessorDetails();
	VOID ShowProcessorMemoryAreaDetails();
	VOID ShowProcessorMemoryAreaContents();
	VOID ShowProcessorMemoryAreaContents(LPCTSTR pszMemoryArea, LPCTSTR pszImage = EMPTYSTRING, LPCTSTR pszVersion = EMPTYSTRING, BOOL bUpdate = FALSE);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, LPCTSTR pszArea, LPCTSTR pszImage, LPCTSTR pszVersion, CONST CPtrArray &pFonts, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(LPCTSTR pszArea, LPCTSTR pszImage, LPCTSTR pszVersion) CONST;
	CString GetPrintDocDetails(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocComments(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

	BOOL CanDumpOnBoardMemoryImage() CONST;
	BOOL CanPatchOnBoardMemoryImage() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsAreasPageDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnSetFont(CFont *pFont);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsAreasPageDialog)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nCtrlID, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnMemoryImage();
	afx_msg void OnPatchableMemoryImage();
	afx_msg void OnDumpableMemoryImage();
	afx_msg void OnUpdateableMemoryImage();
	afx_msg void OnInhibitableMemoryImage();
	afx_msg void OnTransactMemoryImage();
	afx_msg void OnSaveMemoryArea();
	afx_msg void OnDumpMemoryArea();
	afx_msg void OnPatchMemoryArea();
	afx_msg void OnPrintMemoryArea();
	afx_msg void OnUndoMemoryArea();
	afx_msg void OnRedoMemoryArea();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeMemoryImage();
	afx_msg void OnSelchangeMemoryImageVersion();
	afx_msg void OnEditchangeMemoryImageVersion();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsAreasPage view

class CTCOnBoardMemoryImagesDetailsAreasPage : public CScrollView
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsAreasPage)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsAreasPage();

	// Attributes
private:
	CTCOnBoardMemoryImagesDetailsAreasPageDialog  *m_pDialog;
	CRect  m_rDialog[2];
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, BOOL bVisible = TRUE);

	BOOL SetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL SetLayout(CONST LOGFONT *plfFont, CONST LOGFONT *plfTableTitleFont, CONST LOGFONT *plfTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL GetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;
	BOOL GetLayout(LOGFONT *plfFont, LOGFONT *plfTableTitleFont, LOGFONT *plfTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;

	BOOL SetProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem, BOOL bAll = TRUE);
	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);
	BOOL GetProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoTransactOnBoardMemoryImage();
	BOOL CanTransactOnBoardMemoryImage() CONST;
	BOOL DoPrintOnBoardMemoryImageTable();
	BOOL CanPrintOnBoardMemoryImageTable() CONST;
	BOOL DoDiscardOnBoardMemoryImageTable();
	BOOL CanDiscardOnBoardMemoryImageTable() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	VOID UpdateLayout(BOOL bActivate);

	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsAreasPage)
protected:
	virtual void OnActivateView(BOOL bActivate, CView *pActivateView, CView *pDeactiveView);
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsAreasPage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsImportDumpsDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_IMPORTDUMPS_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_IMPORTDUMPS_FILENAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_IMPORTDUMPS_FILENAME   1003
#define IDC_TCONBOARDMEMORYIMAGES_IMPORTDUMPS_FILENAME_BROWSE   1004
#define IDC_TCONBOARDMEMORYIMAGES_IMPORTDUMPS_INSPECT   1005
#define IDC_TCONBOARDMEMORYIMAGES_IMPORTDUMPS_CONTENTS_STATIC   1006
#define IDC_TCONBOARDMEMORYIMAGES_IMPORTDUMPS_CONTENTS   1007
#define IDC_TCONBOARDMEMORYIMAGES_IMPORTDUMPS_COMMENTS   1008
#define IDC_TCONBOARDMEMORYIMAGES_IMPORTDUMPS_OVERWRITEDATA   1009
#define IDC_TCONBOARDMEMORYIMAGES_IMPORTDUMPS_HELP   1010

class CTCOnBoardMemoryImagesDetailsImportDumpsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsImportDumpsDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsImportDumpsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTCOnBoardMemoryImagesProcessorItem  m_cItem;
	CDatabaseOBProcessorMemoryImages  m_pMemoryImages;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsImportDumpsDialog)
public:
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSDUMPSIMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCOnBoardMemoryImagesDetailsDumpsPageDialog *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumMemoryImages();

	BOOL LogDump(LPCTSTR pszDump, LPCTSTR pszVersion, LPCTSTR pszActivity);
	BOOL LogDumpTemplate(LPCTSTR pszDump, LPCTSTR pszActivity);

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsImportDumpsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsImportDumpsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowseFileName();
	afx_msg void OnInspect();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsExportDumpsDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_EXPORTDUMPS_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_EXPORTDUMPS_CONTENTS_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_EXPORTDUMPS_CONTENTS   1003
#define IDC_TCONBOARDMEMORYIMAGES_EXPORTDUMPS_COMMENTS   1004
#define IDC_TCONBOARDMEMORYIMAGES_EXPORTDUMPS_RESETFILE   1005
#define IDC_TCONBOARDMEMORYIMAGES_EXPORTDUMPS_OVERWRITEDATA   1006
#define IDC_TCONBOARDMEMORYIMAGES_EXPORTDUMPS_FILENAME_STATIC   1007
#define IDC_TCONBOARDMEMORYIMAGES_EXPORTDUMPS_FILENAME   1008
#define IDC_TCONBOARDMEMORYIMAGES_EXPORTDUMPS_FILENAME_BROWSE   1009
#define IDC_TCONBOARDMEMORYIMAGES_EXPORTDUMPS_HELP   1010

class CTCOnBoardMemoryImagesDetailsExportDumpsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsExportDumpsDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsExportDumpsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTCOnBoardMemoryImagesProcessorItem  m_cItem;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsExportDumpsDialog)
public:
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSDUMPSEXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCOnBoardMemoryImagesDetailsDumpsPageDialog *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumMemoryImages();

	BOOL LogDump(LPCTSTR pszDump, LPCTSTR pszVersion, LPCTSTR pszActivity);
	BOOL LogDumpTemplate(LPCTSTR pszDump, LPCTSTR pszActivity);

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsExportDumpsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsExportDumpsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowseFileName();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsDownloadDumpsPropertiesDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_NAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_NAME   1003
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_DESCRIPTION   1005
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_EXECUTION_STATIC   1006
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_EXECUTION_IMMEDIATELY   1007
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_EXECUTION_ATTIME   1008
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_EXECUTION_TIME   1009
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_PARAMETERS_STATIC   1010
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_PARAMETERS   1011
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_REMARK_ILLEGALCOMMAND   1012
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_REMARK_OOLPARAMETER   1013
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_DESTINATION_STATIC   1014
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_DESTINATION_MANUALSTACK   1015
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_DESTINATION_AUTOMATICSTACK   1016
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_RELEASE_STATIC   1017
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_RELEASE_IMMEDIATELY   1018
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_RELEASE_ATTIME   1019
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_RELEASE_TIME   1020
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_PREAUTHORIZED   1021
#define IDC_TCONBOARDMEMORYIMAGES_DOWNLOADDUMPS_PROPERTIES_HELP   1022

class CTCOnBoardMemoryImagesDetailsDownloadDumpsPropertiesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsDownloadDumpsPropertiesDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsDownloadDumpsPropertiesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseOBProcessor  m_cProcessor;
	CDatabaseOBProcessorMemoryImage  m_cImage;
private:
	BOOL  m_bFunction;
	CDatabaseTCFunction  m_cFunction;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsDownloadDumpsPropertiesDialog)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSDUMPSDOWNLOAD_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCOnBoardMemoryImagesDetailsDumpsPageDialog *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowContents();

	BOOL LogDumpRequest();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsDownloadDumpsPropertiesDialog)
public:
	virtual INT DoModal(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage);
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
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsDownloadDumpsPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsUploadDumpsPropertiesDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_COMMANDS_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_COMMANDS   1003
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_INFORMATION   1004
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_EXECUTION_STATIC   1005
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_EXECUTION_IMMEDIATELY   1006
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_EXECUTION_ATTIME   1007
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_EXECUTION_TIME   1008
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_PARAMETERS_STATIC   1009
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_PARAMETERS   1010
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_REMARK_ILLEGALCOMMAND   1011
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_REMARK_OOLPARAMETER   1012
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_DESTINATION_STATIC   1013
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_DESTINATION_MANUALSTACK   1014
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_DESTINATION_AUTOMATICSTACK   1015
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_RELEASE_STATIC   1016
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_RELEASE_IMMEDIATELY   1017
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_RELEASE_ATTIME   1018
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_RELEASE_TIME   1019
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_PREAUTHORIZED   1020
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADDUMPS_PROPERTIES_HELP   1021

class CTCOnBoardMemoryImagesDetailsUploadDumpsPropertiesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsUploadDumpsPropertiesDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsUploadDumpsPropertiesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseOBProcessor  m_cProcessor;
	CDatabaseOBProcessorMemoryImage  m_cImage;
private:
	CDatabaseTCPackets  m_pPackets;
	CDatabaseTCFunctions  m_pFunctions;
	BOOL  m_bFunctions;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsUploadDumpsPropertiesDialog)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSDUMPSUPLOAD_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCOnBoardMemoryImagesDetailsDumpsPageDialog *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTelecommands();

	VOID ShowContents();

	BOOL LogPatchRequest();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsUploadDumpsPropertiesDialog)
public:
	virtual INT DoModal(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage);
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
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsUploadDumpsPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSelchangeTelecommand();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsDumpsPageDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_NAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_NAME   1003
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_VERSION_STATIC   1004
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_VERSION   1005
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_FLAGS_STATIC   1006
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_FLAGS_PATCHABLE   1007
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_FLAGS_DUMPABLE   1008
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_UPDATES_STATIC   1009
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_UPDATES_AUTOMATIC   1010
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_UPDATES_INHIBITAUTOMATIC   1011
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_IMPORT   1012
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_EXPORT   1013
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_ERRORSYMBOL   1014
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_ERRORMESSAGE   1015
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_LIST   1016
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_UNDO   1017
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_REDO   1018
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_TRANSACT   1019
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_SAVE   1020
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_UNICODE   1021
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_DELETE   1022
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_PRINT   1023
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_DUMP   1024
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_PATCH   1025

// Specify the telecommand on-board memory images dumps page related timer identifiers
#define TCONBOARDMEMORYIMAGESDUMPS_CHECKDATA_TIMERID   100
#define TCONBOARDMEMORYIMAGESDUMPS_CHECKDATA_TIMEOUT   500

class CTCOnBoardMemoryImagesDetailsDumpsPageDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsDumpsPageDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsDumpsPageDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CWnd  m_wndTableViewCtrl;
	CTCOnBoardMemoryImagesTableView  m_wndTableView;
private:
	CFont  m_cFont;
	CImage  m_cSymbol;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsDumpsPageDialog)
public:
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSDUMPS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL SetLayout(CONST LOGFONT *plfFont, CONST LOGFONT *plfTableTitleFont, CONST LOGFONT *plfTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL GetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;
	BOOL GetLayout(LOGFONT *plfFont, LOGFONT *plfTableTitleFont, LOGFONT *plfTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;

	BOOL SetProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem, BOOL bAll = TRUE);
	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);
	BOOL GetProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoTransactOnBoardMemoryImage();
	BOOL CanTransactOnBoardMemoryImage() CONST;
	BOOL DoImportOnBoardMemoryImage();
	BOOL CanImportOnBoardMemoryImage() CONST;
	BOOL DoExportOnBoardMemoryImage();
	BOOL CanExportOnBoardMemoryImage() CONST;
	BOOL DoDeleteOnBoardMemoryImage();
	BOOL CanDeleteOnBoardMemoryImage() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowAbove();
	BOOL CanInsertOnBoardMemoryImageTableRowAbove() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowBelow();
	BOOL CanInsertOnBoardMemoryImageTableRowBelow() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnBefore();
	BOOL CanInsertOnBoardMemoryImageTableColumnBefore() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnAfter();
	BOOL CanInsertOnBoardMemoryImageTableColumnAfter() CONST;
	BOOL DoClearOnBoardMemoryImageTableRow();
	BOOL CanClearOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableRow();
	BOOL CanDeleteOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableColumn();
	BOOL CanDeleteOnBoardMemoryImageTableColumn() CONST;
	BOOL DoCopyOnBoardMemoryImageTableRow();
	BOOL CanCopyOnBoardMemoryImageTableRow() CONST;
	BOOL DoPasteOnBoardMemoryImageTableRow();
	BOOL CanPasteOnBoardMemoryImageTableRow() CONST;
	BOOL DoPrintOnBoardMemoryImageTable();
	BOOL CanPrintOnBoardMemoryImageTable() CONST;
	BOOL DoDiscardOnBoardMemoryImageTable();
	BOOL CanDiscardOnBoardMemoryImageTable() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	class CTCOnBoardMemoryImagesDetailsDumpsPage *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowProcessorDetails();
	VOID ShowProcessorMemoryImageDetails();
	VOID ShowProcessorMemoryImageContents(LPCTSTR pszImage, LPCTSTR pszVersion, BOOL bUpdate = FALSE);
	VOID ShowProcessorMemoryImageStatus(LPCTSTR pszImage, LPCTSTR pszVersion);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, LPCTSTR pszImage, LPCTSTR pszVersion, CONST CPtrArray &pFonts, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(LPCTSTR pszImage, LPCTSTR pszVersion) CONST;
	CString GetPrintDocDetails(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocComments(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

	BOOL CanDumpOnBoardMemoryImage() CONST;
	BOOL CanPatchOnBoardMemoryImage() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsDumpsPageDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnSetFont(CFont *pFont);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsDumpsPageDialog)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nCtrlID, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnImportMemoryImage();
	afx_msg void OnExportMemoryImage();
	afx_msg void OnPatchableMemoryImage();
	afx_msg void OnDumpableMemoryImage();
	afx_msg void OnUpdateableMemoryImage();
	afx_msg void OnInhibitableMemoryImage();
	afx_msg void OnTransactMemoryImage();
	afx_msg void OnSaveMemoryImage();
	afx_msg void OnDeleteMemoryImage();
	afx_msg void OnDumpMemoryImage();
	afx_msg void OnPatchMemoryImage();
	afx_msg void OnPrintMemoryImage();
	afx_msg void OnUndoMemoryImage();
	afx_msg void OnRedoMemoryImage();
	afx_msg void OnSelchangeMemoryImage();
	afx_msg void OnSelchangeMemoryImageVersion();
	afx_msg void OnEditchangeMemoryImage();
	afx_msg void OnEditchangeMemoryImageVersion();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsDumpsPage view

class CTCOnBoardMemoryImagesDetailsDumpsPage : public CScrollView
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsDumpsPage)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsDumpsPage();

	// Attributes
private:
	CTCOnBoardMemoryImagesDetailsDumpsPageDialog  *m_pDialog;
	CRect  m_rDialog[2];
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, BOOL bVisible = TRUE);

	BOOL SetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL SetLayout(CONST LOGFONT *plfFont, CONST LOGFONT *plfTableTitleFont, CONST LOGFONT *plfTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL GetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;
	BOOL GetLayout(LOGFONT *plfFont, LOGFONT *plfTableTitleFont, LOGFONT *plfTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;

	BOOL SetProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem, BOOL bAll = TRUE);
	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);
	BOOL GetProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoTransactOnBoardMemoryImage();
	BOOL CanTransactOnBoardMemoryImage() CONST;
	BOOL DoImportOnBoardMemoryImage();
	BOOL CanImportOnBoardMemoryImage() CONST;
	BOOL DoExportOnBoardMemoryImage();
	BOOL CanExportOnBoardMemoryImage() CONST;
	BOOL DoDeleteOnBoardMemoryImage();
	BOOL CanDeleteOnBoardMemoryImage() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowAbove();
	BOOL CanInsertOnBoardMemoryImageTableRowAbove() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowBelow();
	BOOL CanInsertOnBoardMemoryImageTableRowBelow() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnBefore();
	BOOL CanInsertOnBoardMemoryImageTableColumnBefore() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnAfter();
	BOOL CanInsertOnBoardMemoryImageTableColumnAfter() CONST;
	BOOL DoClearOnBoardMemoryImageTableRow();
	BOOL CanClearOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableRow();
	BOOL CanDeleteOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableColumn();
	BOOL CanDeleteOnBoardMemoryImageTableColumn() CONST;
	BOOL DoCopyOnBoardMemoryImageTableRow();
	BOOL CanCopyOnBoardMemoryImageTableRow() CONST;
	BOOL DoPasteOnBoardMemoryImageTableRow();
	BOOL CanPasteOnBoardMemoryImageTableRow() CONST;
	BOOL DoPrintOnBoardMemoryImageTable();
	BOOL CanPrintOnBoardMemoryImageTable() CONST;
	BOOL DoDiscardOnBoardMemoryImageTable();
	BOOL CanDiscardOnBoardMemoryImageTable() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	VOID UpdateLayout(BOOL bActivate);

	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsDumpsPage)
protected:
	virtual void OnActivateView(BOOL bActivate, CView *pActivateView, CView *pDeactiveView);
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsDumpsPage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsUploadAnalysisPropertiesDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_COMMANDS_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_COMMANDS   1003
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_INFORMATION   1004
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_EXECUTION_STATIC   1005
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_EXECUTION_IMMEDIATELY   1006
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_EXECUTION_ATTIME   1007
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_EXECUTION_TIME   1008
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_PARAMETERS_STATIC   1009
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_PARAMETERS   1010
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_REMARK_ILLEGALCOMMAND   1011
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_REMARK_OOLPARAMETER   1012
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_DESTINATION_STATIC   1013
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_DESTINATION_MANUALSTACK   1014
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_DESTINATION_AUTOMATICSTACK   1015
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_RELEASE_STATIC   1016
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_RELEASE_IMMEDIATELY   1017
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_RELEASE_ATTIME   1018
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_RELEASE_TIME   1019
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_PREAUTHORIZED   1020
#define IDC_TCONBOARDMEMORYIMAGES_UPLOADANALYSIS_PROPERTIES_HELP   1021

class CTCOnBoardMemoryImagesDetailsUploadAnalysisPropertiesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsUploadAnalysisPropertiesDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsUploadAnalysisPropertiesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseOBProcessor  m_cProcessor;
	CDatabaseOBProcessorMemoryImage  m_cImage;
private:
	CDatabaseTCPackets  m_pPackets;
	CDatabaseTCFunctions  m_pFunctions;
	BOOL  m_bFunctions;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsUploadAnalysisPropertiesDialog)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSANALYSISUPLOAD_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCOnBoardMemoryImagesDetailsAnalysisPageDialog *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTelecommands();

	VOID ShowContents();

	BOOL LogPatchRequest();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsUploadAnalysisPropertiesDialog)
public:
	virtual INT DoModal(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage);
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
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsUploadAnalysisPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSelchangeTelecommand();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsAnalysisPageDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_NAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_NAME   1003
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_VERSION_STATIC   1004
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_VERSION   1005
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_VERSUS   1006
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_COMPAREDNAME_STATIC   1007
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_COMPAREDNAME   1008
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_COMPAREDVERSION_STATIC   1009
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_COMPAREDVERSION   1010
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_SHOWALLRESULTS   1011
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_RESULTS_STATIC   1012
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_RESULTS   1013
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_RESULTS_COUNT   1014
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_PRINT   1015
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_SAVE   1016
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_UNICODE   1017
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_PATCH   1018

class CTCOnBoardMemoryImagesDetailsAnalysisPageDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsAnalysisPageDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsAnalysisPageDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CWnd  m_wndTableViewCtrl;
	CTCOnBoardMemoryImagesTableView  m_wndTableView;
private:
	CFont  m_cFont;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsAnalysisPageDialog)
public:
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSANALYSIS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL SetLayout(CONST LOGFONT *plfFont, CONST LOGFONT *plfTableTitleFont, CONST LOGFONT *plfTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL GetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;
	BOOL GetLayout(LOGFONT *plfFont, LOGFONT *plfTableTitleFont, LOGFONT *plfTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;

	BOOL SetProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem, BOOL bAll = TRUE);
	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);
	BOOL GetProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoPrintOnBoardMemoryImageTable();
	BOOL CanPrintOnBoardMemoryImageTable() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	class CTCOnBoardMemoryImagesDetailsAnalysisPage *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowProcessorDetails();
	VOID ShowProcessorMemoryImageDetails(BOOL bComparedImage = FALSE);
	VOID ShowMemoryImageAnalysisResults(LPCTSTR pszImage, LPCTSTR pszImageVersion, LPCTSTR pszComparedImage, LPCTSTR pszComparedImageVersion, BOOL bResults = TRUE);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, LPCTSTR pszImage, LPCTSTR pszVersion, LPCTSTR pszComparedImage, LPCTSTR pszComparedVersion, CONST CPtrArray &pFonts, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(LPCTSTR pszImage, LPCTSTR pszVersion, LPCTSTR pszComparedImage, LPCTSTR pszComparedVersion) CONST;
	CString GetPrintDocDetails(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocComments(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

	BOOL ConstructOnBoardMemoryImagePatch(CDatabaseOBProcessorMemoryImage *pImage) CONST;
	BOOL CanPatchOnBoardMemoryImage() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsAnalysisPageDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnSetFont(CFont *pFont);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsAnalysisPageDialog)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnCompareMemoryImages();
	afx_msg void OnSaveResults();
	afx_msg void OnPatchResults();
	afx_msg void OnPrintResults();
	afx_msg void OnSelchangeMemoryImage();
	afx_msg void OnSelchangeMemoryImageVersion();
	afx_msg void OnSelchangeComparedMemoryImage();
	afx_msg void OnSelchangeComparedMemoryImageVersion();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsAnalysisPage view

class CTCOnBoardMemoryImagesDetailsAnalysisPage : public CScrollView
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsAnalysisPage)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsAnalysisPage();

	// Attributes
private:
	CTCOnBoardMemoryImagesDetailsAnalysisPageDialog  *m_pDialog;
	CRect  m_rDialog[2];
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, BOOL bVisible = TRUE);

	BOOL SetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL SetLayout(CONST LOGFONT *plfFont, CONST LOGFONT *plfTableTitleFont, CONST LOGFONT *plfTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL GetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;
	BOOL GetLayout(LOGFONT *plfFont, LOGFONT *plfTableTitleFont, LOGFONT *plfTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;

	BOOL SetProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem, BOOL bAll = TRUE);
	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);
	BOOL GetProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoPrintOnBoardMemoryImageTable();
	BOOL CanPrintOnBoardMemoryImageTable() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	VOID UpdateLayout(BOOL bActivate);

	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsAnalysisPage)
protected:
	virtual void OnActivateView(BOOL bActivate, CView *pActivateView, CView *pDeactiveView);
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsAnalysisPage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsStopDownloadsPropertiesDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_NAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_NAME   1003
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_DESCRIPTION_STATIC   1004
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_DESCRIPTION   1005
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_EXECUTION_STATIC   1006
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_EXECUTION_IMMEDIATELY   1007
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_EXECUTION_ATTIME   1008
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_EXECUTION_TIME   1009
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_PARAMETERS_STATIC   1010
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_PARAMETERS   1011
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_REMARK_ILLEGALCOMMAND   1012
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_REMARK_OOLPARAMETER   1013
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_DESTINATION_STATIC   1014
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_DESTINATION_MANUALSTACK   1015
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_DESTINATION_AUTOMATICSTACK   1016
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_RELEASE_STATIC   1017
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_RELEASE_IMMEDIATELY   1018
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_RELEASE_ATTIME   1019
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_RELEASE_TIME   1020
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_PREAUTHORIZED   1021
#define IDC_TCONBOARDMEMORYIMAGES_STOPDOWNLOADS_PROPERTIES_HELP   1022

class CTCOnBoardMemoryImagesDetailsStopDownloadsPropertiesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsStopDownloadsPropertiesDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsStopDownloadsPropertiesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseOBProcessor  m_cProcessor;
	CDatabaseOBProcessorMemoryImage  m_cImage;
private:
	BOOL  m_bFunction;
	CDatabaseTCFunction  m_cFunction;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsStopDownloadsPropertiesDialog)
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADSSTOP_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	class CTCOnBoardMemoryImagesDetailsDownloadsPageDialog *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowContents();

	BOOL LogDumpRequest();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsStopDownloadsPropertiesDialog)
public:
	virtual INT DoModal(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage);
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
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsStopDownloadsPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnReleaseImmediately();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnPreauthorized();
	afx_msg void OnDestinationManualStack();
	afx_msg void OnDestinationAutomaticStack();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsDownloadsPageDialog dialog

#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_DETAILS   1001
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_NAME_STATIC   1002
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_NAME   1003
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_VERSION_STATIC   1004
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_VERSION   1005
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_ADDRESSRANGE_STATIC   1006
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_ADDRESSRANGE   1007
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_BYTES_STATIC   1008
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_BYTES   1009
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_TIME_STATIC   1010
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_TIME   1011
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_ERRORSYMBOL   1012
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_ERRORMESSAGE   1013
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_DATA   1014
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_PREVIOUS   1015
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_NEXT   1016
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_TRANSACT   1017
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_SAVE   1018
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_UNICODE   1019
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_DELETE   1020
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_SHOW   1021
#define IDC_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_STOP   1022

// Specify the telecommand on-board memory images downloads page related timer identifiers
#define TCONBOARDMEMORYIMAGESDOWNLOADS_PROCESSDATA_TIMERID   100
#define TCONBOARDMEMORYIMAGESDOWNLOADS_PROCESSDATA_TIMEOUT   0

class CTCOnBoardMemoryImagesDetailsDownloadsPageDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsDownloadsPageDialog)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsDownloadsPageDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CWnd  m_wndTableViewCtrl;
	CTCOnBoardMemoryImagesTableView  m_wndTableView;
private:
	CString  m_szDump[3];
	CMemoryDumps  m_pMemoryDumps;
private:
	CFont  m_cFont;
	CImage  m_cSymbol;

	// Dialog Data
	//{{AFX_DATA(CTCOnBoardMemoryImagesDetailsDownloadsPageDialog)
public:
	enum { IDD = IDD_TCONBOARDMEMORYIMAGES_DETAILSDOWNLOADS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL SetLayout(CONST LOGFONT *plfFont, CONST LOGFONT *plfTableTitleFont, CONST LOGFONT *plfTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL GetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;
	BOOL GetLayout(LOGFONT *plfFont, LOGFONT *plfTableTitleFont, LOGFONT *plfTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;

	BOOL SetProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem, BOOL bAll = TRUE);
	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);
	BOOL GetProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoTransactOnBoardMemoryImage();
	BOOL CanTransactOnBoardMemoryImage() CONST;
	BOOL DoDeleteOnBoardMemoryImage();
	BOOL CanDeleteOnBoardMemoryImage() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	class CTCOnBoardMemoryImagesDetailsDownloadsPage *GetParent() CONST;
	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

private:
	VOID ShowProcessorDetails();
	VOID ShowProcessorMemoryImageDetails();
	VOID ShowProcessorMemoryImageDownloadDetails(BOOL bLogging = FALSE);

	BOOL CanShowPreviousOnBoardMemoryImage() CONST;
	BOOL CanShowNextOnBoardMemoryImage() CONST;

	BOOL LogDumpDownload(LPCTSTR pszDump, double fData);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsDownloadsPageDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnSetFont(CFont *pFont);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsDownloadsPageDialog)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nCtrlID, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnPreviousMemoryImage();
	afx_msg void OnNextMemoryImage();
	afx_msg void OnTransactMemoryImage();
	afx_msg void OnSaveMemoryImage();
	afx_msg void OnDeleteMemoryImage();
	afx_msg void OnStopDumpMemoryImage();
	afx_msg void OnSelchangeMemoryImage();
	afx_msg void OnSelchangeMemoryImageVersion();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsDownloadsPage view

class CTCOnBoardMemoryImagesDetailsDownloadsPage : public CScrollView
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsDownloadsPage)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsDownloadsPage();

	// Attributes
private:
	CTCOnBoardMemoryImagesDetailsDownloadsPageDialog  *m_pDialog;
	CRect  m_rDialog[2];
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, BOOL bVisible = TRUE);

	BOOL SetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL SetLayout(CONST LOGFONT *plfFont, CONST LOGFONT *plfTableTitleFont, CONST LOGFONT *plfTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL GetLayout(CFont *pFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;
	BOOL GetLayout(LOGFONT *plfFont, LOGFONT *plfTableTitleFont, LOGFONT *plfTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;

	BOOL SetProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem, BOOL bAll = TRUE);
	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);
	BOOL GetProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoTransactOnBoardMemoryImage();
	BOOL CanTransactOnBoardMemoryImage() CONST;
	BOOL DoDeleteOnBoardMemoryImage();
	BOOL CanDeleteOnBoardMemoryImage() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	VOID UpdateLayout(BOOL bActivate);

	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsDownloadsPage)
protected:
	virtual void OnActivateView(BOOL bActivate, CView *pActivateView, CView *pDeactiveView);
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsDownloadsPage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsPane window

class CTCOnBoardMemoryImagesDetailsPane : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsPane)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsPane();

	// Attributes
private:
	INT  m_nIndex;
	CFont  m_cTabFont;
	CSize  m_sizeTabMargins;
private:
	CTCOnBoardMemoryImagesDetailsAreasPage  *m_pMemoryAreasPage;
	CTCOnBoardMemoryImagesDetailsDumpsPage  *m_pMemoryDumpsPage;
	CTCOnBoardMemoryImagesDetailsAnalysisPage  *m_pMemoryAnalysisPage;
	CTCOnBoardMemoryImagesDetailsDownloadsPage  *m_pMemoryDownloadsPage;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, DWORD dwStyle);

	BOOL SetLayout(CFont *pTitleFont, CFont *pItemsFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL SetLayout(CONST LOGFONT *plfTitleFont, CONST LOGFONT *plfItemsFont, CONST LOGFONT *plfTableTitleFont, CONST LOGFONT *plfTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL GetLayout(CFont *pTitleFont, CFont *pItemsFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;
	BOOL GetLayout(LOGFONT *plfTitleFont, LOGFONT *plfItemsFont, LOGFONT *plfTableTitleFont, LOGFONT *plfTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetCurProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem);
	BOOL GetCurProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoTransactOnBoardMemoryImage();
	BOOL CanTransactOnBoardMemoryImage() CONST;
	BOOL DoImportOnBoardMemoryImage();
	BOOL CanImportOnBoardMemoryImage() CONST;
	BOOL DoExportOnBoardMemoryImage();
	BOOL CanExportOnBoardMemoryImage() CONST;
	BOOL DoDeleteOnBoardMemoryImage();
	BOOL CanDeleteOnBoardMemoryImage() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowAbove();
	BOOL CanInsertOnBoardMemoryImageTableRowAbove() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowBelow();
	BOOL CanInsertOnBoardMemoryImageTableRowBelow() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnBefore();
	BOOL CanInsertOnBoardMemoryImageTableColumnBefore() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnAfter();
	BOOL CanInsertOnBoardMemoryImageTableColumnAfter() CONST;
	BOOL DoClearOnBoardMemoryImageTableRow();
	BOOL CanClearOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableRow();
	BOOL CanDeleteOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableColumn();
	BOOL CanDeleteOnBoardMemoryImageTableColumn() CONST;
	BOOL DoCopyOnBoardMemoryImageTableRow();
	BOOL CanCopyOnBoardMemoryImageTableRow() CONST;
	BOOL DoPasteOnBoardMemoryImageTableRow();
	BOOL CanPasteOnBoardMemoryImageTableRow() CONST;
	BOOL DoPrintOnBoardMemoryImageTable();
	BOOL CanPrintOnBoardMemoryImageTable() CONST;
	BOOL DoDiscardOnBoardMemoryImageTable();
	BOOL CanDiscardOnBoardMemoryImageTable() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	VOID UpdateLayout(BOOL bActivate);

	CSize GetMargins() CONST;

	CTCOnBoardMemoryImagesDetailsAreasPage *GetMemoryAreasPage() CONST;
	CTCOnBoardMemoryImagesDetailsDumpsPage *GetMemoryDumpsPage() CONST;
	CTCOnBoardMemoryImagesDetailsAnalysisPage *GetMemoryAnalysisPage() CONST;
	CTCOnBoardMemoryImagesDetailsDownloadsPage *GetMemoryDownloadsPage() CONST;

	class CTCOnBoardMemoryImagesDetailsView *GetParent() CONST;

private:
	BOOL SelectPage();
	BOOL SelectPage(INT nIndex);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsPane)
public:
	virtual BOOL SetLayoutInfo(INT nIndex);
	virtual BOOL GetLayoutInfo(INT &nIndex) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsPane)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSelchangePage(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesDetailsView view

// Specify the telecommand on-board memory images display details tab identifiers
#define TCONBOARDMEMORYIMAGESDETAILSVIEW_AREASTAB   0
#define TCONBOARDMEMORYIMAGESDETAILSVIEW_DUMPSTAB   1
#define TCONBOARDMEMORYIMAGESDETAILSVIEW_ANALYSISTAB   2
#define TCONBOARDMEMORYIMAGESDETAILSVIEW_DOWNLOADSTAB   3

class CTCOnBoardMemoryImagesDetailsView : public CView
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesDetailsView)

	// Construction
public:
	CTCOnBoardMemoryImagesDetailsView();

	// Attributes
private:
	CTCOnBoardMemoryImagesDetailsPane  m_wndPane;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetLayout(CFont *pTitleFont, CFont *pItemsFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL SetLayout(CONST LOGFONT *plfTitleFont, CONST LOGFONT *plfItemsFont, CONST LOGFONT *plfTableTitleFont, CONST LOGFONT *plfTableItemsFont, COLORREF nTableTitleFontColor, COLORREF nTableItemsFontColor, COLORREF nTableTitleBackgroundColor, COLORREF nTableItemsBackgroundColor);
	BOOL GetLayout(CFont *pTitleFont, CFont *pItemsFont, CFont *pTableTitleFont, CFont *pTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;
	BOOL GetLayout(LOGFONT *plfTitleFont, LOGFONT *plfItemsFont, LOGFONT *plfTableTitleFont, LOGFONT *plfTableItemsFont, COLORREF &nTableTitleFontColor, COLORREF &nTableItemsFontColor, COLORREF &nTableTitleBackgroundColor, COLORREF &nTableItemsBackgroundColor) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetCurProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem);
	BOOL GetCurProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem) CONST;

	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoTransactOnBoardMemoryImage();
	BOOL CanTransactOnBoardMemoryImage() CONST;
	BOOL DoImportOnBoardMemoryImage();
	BOOL CanImportOnBoardMemoryImage() CONST;
	BOOL DoExportOnBoardMemoryImage();
	BOOL CanExportOnBoardMemoryImage() CONST;
	BOOL DoDeleteOnBoardMemoryImage();
	BOOL CanDeleteOnBoardMemoryImage() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowAbove();
	BOOL CanInsertOnBoardMemoryImageTableRowAbove() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowBelow();
	BOOL CanInsertOnBoardMemoryImageTableRowBelow() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnBefore();
	BOOL CanInsertOnBoardMemoryImageTableColumnBefore() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnAfter();
	BOOL CanInsertOnBoardMemoryImageTableColumnAfter() CONST;
	BOOL DoClearOnBoardMemoryImageTableRow();
	BOOL CanClearOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableRow();
	BOOL CanDeleteOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableColumn();
	BOOL CanDeleteOnBoardMemoryImageTableColumn() CONST;
	BOOL DoCopyOnBoardMemoryImageTableRow();
	BOOL CanCopyOnBoardMemoryImageTableRow() CONST;
	BOOL DoPasteOnBoardMemoryImageTableRow();
	BOOL CanPasteOnBoardMemoryImageTableRow() CONST;
	BOOL DoPrintOnBoardMemoryImageTable();
	BOOL CanPrintOnBoardMemoryImageTable() CONST;
	BOOL DoDiscardOnBoardMemoryImageTable();
	BOOL CanDiscardOnBoardMemoryImageTable() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	VOID UpdateLayout(BOOL bActivate);

	class CTCOnBoardMemoryImagesWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesDetailsView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex);
	virtual BOOL GetLayoutInfo(INT &nIndex) CONST;
protected:
	virtual void OnActivateView(BOOL bActivate, CView *pActivateView, CView *pDeactiveView);
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesDetailsView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesView window

class CTCOnBoardMemoryImagesView : public CSplitterWndEx
{
	DECLARE_DYNCREATE(CTCOnBoardMemoryImagesView)

	// Construction
public:
	CTCOnBoardMemoryImagesView();

	// Attributes
private:
	CSize  m_sizePanes[2];
	CUIntArray  m_nColumns;
	CUIntArray  m_nColumnWidths;
	COLORREF  m_nTableColors[2][2];
	LOGFONT  m_lfPaneTitleFont[2];
	LOGFONT  m_lfPaneItemsFont[2];
	LOGFONT  m_lfTableFont[2];
	BOOL  m_bToolTips;
	BOOL  m_bUndo;
private:
	CTCOnBoardMemoryImagesProcessorItems  m_pItems;
private:
	CTCOnBoardMemoryImagesSummaryView  *m_pSummaryView;
	CTCOnBoardMemoryImagesDetailsView  *m_pDetailsView;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizePane);
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizePane) CONST;

	BOOL SetPaneTitleFont(UINT nPane, CFont *pFont);
	BOOL SetPaneTitleFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetPaneTitleFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetPaneTitleFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetPaneItemsFont(UINT nPane, CFont *pFont);
	BOOL SetPaneItemsFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetPaneItemsFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetPaneItemsFont(UINT nPane, LOGFONT *plfFont) CONST;

	BOOL SetTablesOutline(CFont *pTitleFont, CFont *pItemsFont, COLORREF nTitleFontColor, COLORREF nItemsFontColor, COLORREF nTitleBackgroundColor, COLORREF nItemsBackgroundColor);
	BOOL SetTablesOutline(CONST LOGFONT *plfTitleFont, CONST LOGFONT *plfItemsFont, COLORREF nTitleFontColor, COLORREF nItemsFontColor, COLORREF nTitleBackgroundColor, COLORREF nItemsBackgroundColor);
	BOOL GetTablesOutline(CFont *pTitleFont, CFont *pItemsFont, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, COLORREF &nTitleBackgroundColor, COLORREF &nItemsBackgroundColor) CONST;
	BOOL GetTablesOutline(LOGFONT *plfTitleFont, LOGFONT *plfItemsFont, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, COLORREF &nTitleBackgroundColor, COLORREF &nItemsBackgroundColor) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetProcessors(CONST CTCOnBoardMemoryImagesProcessorItems &pItems, BOOL bAll = TRUE);
	BOOL GetProcessors(CTCOnBoardMemoryImagesProcessorItems &pItems, BOOL bAll = TRUE) CONST;

	BOOL SetCurProcessor(INT nIndex);
	BOOL SetCurProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem);
	INT GetCurProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem = NULL) CONST;
	BOOL GetCurProcessor(CString &szProcessor) CONST;

	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);

	UINT GetProcessorCount() CONST;

	BOOL DoAcknowledgeProcessor();
	BOOL CanAcknowledgeProcessor() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(LPCTSTR pszProcessor, CONST CTimeTag &tLastDumpTime, CONST CTimeTag &tLastPatchTime);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	BOOL DoTransactOnBoardMemoryImage();
	BOOL CanTransactOnBoardMemoryImage() CONST;
	BOOL DoImportOnBoardMemoryImage();
	BOOL CanImportOnBoardMemoryImage() CONST;
	BOOL DoExportOnBoardMemoryImage();
	BOOL CanExportOnBoardMemoryImage() CONST;
	BOOL DoDeleteOnBoardMemoryImage();
	BOOL CanDeleteOnBoardMemoryImage() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowAbove();
	BOOL CanInsertOnBoardMemoryImageTableRowAbove() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowBelow();
	BOOL CanInsertOnBoardMemoryImageTableRowBelow() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnBefore();
	BOOL CanInsertOnBoardMemoryImageTableColumnBefore() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnAfter();
	BOOL CanInsertOnBoardMemoryImageTableColumnAfter() CONST;
	BOOL DoClearOnBoardMemoryImageTableRow();
	BOOL CanClearOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableRow();
	BOOL CanDeleteOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableColumn();
	BOOL CanDeleteOnBoardMemoryImageTableColumn() CONST;
	BOOL DoCopyOnBoardMemoryImageTableRow();
	BOOL CanCopyOnBoardMemoryImageTableRow() CONST;
	BOOL DoPasteOnBoardMemoryImageTableRow();
	BOOL CanPasteOnBoardMemoryImageTableRow() CONST;
	BOOL DoPrintOnBoardMemoryImageTable();
	BOOL CanPrintOnBoardMemoryImageTable() CONST;
	BOOL DoDiscardOnBoardMemoryImageTable();
	BOOL CanDiscardOnBoardMemoryImageTable() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	BOOL GetPrintProperties(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;

	VOID UpdateContents(BOOL bRedraw = TRUE);
	VOID UpdateLayout(BOOL bActivate);

	VOID SetTrackSize(CONST SIZE &size);
	CSize GetTrackSize() CONST;

	CTCOnBoardMemoryImagesSummaryView *GetSummaryView() CONST;
	CTCOnBoardMemoryImagesDetailsView *GetDetailsView() CONST;

	class CTCOnBoardMemoryImagesWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesView)
public:
	virtual BOOL SetLayoutInfo(INT nIndex, INT nPage, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	virtual BOOL GetLayoutInfo(INT &nIndex, INT &nPage, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;
public:
	virtual VOID RecalcLayout();
	virtual VOID RecalcLayout(BOOL bRecalc);
protected:
	virtual void StartTracking(int ht);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CTCOnBoardMemoryImagesView)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardMemoryImagesWnd frame

// Specify the telecommand on-board memory images display panes
#define TCONBOARDMEMORYIMAGES_PANE_SUMMARY   (1<<0)
#define TCONBOARDMEMORYIMAGES_PANE_DETAILS   (1<<1)
#define TCONBOARDMEMORYIMAGES_PANES   2
// Specify the telecommand on-board memory images display title items
#define TCONBOARDMEMORYIMAGES_TITLEITEM_PROCESSOR   (1<<0)
#define TCONBOARDMEMORYIMAGES_TITLEITEM_ADDRESSRANGE   (1<<1)
#define TCONBOARDMEMORYIMAGES_TITLEITEM_SIZE   (1<<2)
#define TCONBOARDMEMORYIMAGES_TITLEITEM_PATCHTC   (1<<3)
#define TCONBOARDMEMORYIMAGES_TITLEITEM_LASTPATCHTIME   (1<<4)
#define TCONBOARDMEMORYIMAGES_TITLEITEM_DUMPTC   (1<<5)
#define TCONBOARDMEMORYIMAGES_TITLEITEM_DUMPTM   (1<<6)
#define TCONBOARDMEMORYIMAGES_TITLEITEM_LASTDUMPTIME   (1<<7)
#ifndef RC_INVOKED
#define TCONBOARDMEMORYIMAGES_TITLEITEMS_DEFAULT   (TCONBOARDMEMORYIMAGES_TITLEITEM_PROCESSOR | TCONBOARDMEMORYIMAGES_TITLEITEM_ADDRESSRANGE | TCONBOARDMEMORYIMAGES_TITLEITEM_SIZE | TCONBOARDMEMORYIMAGES_TITLEITEM_PATCHTC | TCONBOARDMEMORYIMAGES_TITLEITEM_DUMPTC | TCONBOARDMEMORYIMAGES_TITLEITEM_DUMPTM)
#define TCONBOARDMEMORYIMAGES_TITLEITEMS_ALL   (TCONBOARDMEMORYIMAGES_TITLEITEMS_DEFAULT | TCONBOARDMEMORYIMAGES_TITLEITEM_LASTPATCHTIME | TCONBOARDMEMORYIMAGES_TITLEITEM_LASTDUMPTIME)
#endif
// Specify the telecommand on-board memory images display print modes
#define TCONBOARDMEMORYIMAGES_PRINT_ALL   (1<<0)
#define TCONBOARDMEMORYIMAGES_PRINT_FIRSTSIDE   (1<<1)
#define TCONBOARDMEMORYIMAGES_PRINT_LASTSIDE   (1<<2)
#define TCONBOARDMEMORYIMAGES_PRINT_RANGE   (1<<3)
#define TCONBOARDMEMORYIMAGES_PRINT_COMPLETEONLY   (1<<4)
#define TCONBOARDMEMORYIMAGES_PRINT_CUSTOMLAYOUT   (1<<5)
#define TCONBOARDMEMORYIMAGES_PRINT_CLEARCOMMENTS   (1<<6)
#define TCONBOARDMEMORYIMAGES_PRINT_ATEVENT   (1<<7)
#define TCONBOARDMEMORYIMAGES_PRINT_ATDOWNLOAD   (1<<8)
#define TCONBOARDMEMORYIMAGES_PRINT_REPEATSTOPBYTIME   (1<<9)
#define TCONBOARDMEMORYIMAGES_PRINT_REPEATSTOPBYCOUNT   (1<<10)
#define TCONBOARDMEMORYIMAGES_PRINT_ACTIVE   (1<<11)
// Specify the telecommand on-board memory images display print fonts
#define TCONBOARDMEMORYIMAGES_PRINTFONT_TITLE   0
#define TCONBOARDMEMORYIMAGES_PRINTFONT_SUBTITLE   1
#define TCONBOARDMEMORYIMAGES_PRINTFONT_DETAILS   2
#define TCONBOARDMEMORYIMAGES_PRINTFONT_COMMENTS   3
#define TCONBOARDMEMORYIMAGES_PRINTFONT_SUMMARYLISTITEMSTITLE   4
#define TCONBOARDMEMORYIMAGES_PRINTFONT_SUMMARYLISTITEMS   5
#define TCONBOARDMEMORYIMAGES_PRINTFONT_FOOTER   6
#define TCONBOARDMEMORYIMAGES_PRINTFONT_NOTICE   7
#define TCONBOARDMEMORYIMAGES_PRINTFONT_LOGO   8
#define TCONBOARDMEMORYIMAGES_PRINTFONTS   9
// Specify the telecommand on-board memory images display toolbar related identifiers
#define ID_TCONBOARDMEMORYIMAGES_TOOLBAR_PROPERTIES   AFX_IDW_TOOLBAR
#define ID_TCONBOARDMEMORYIMAGES_TOOLBAR_OPERATIONS   (AFX_IDW_TOOLBAR+1)
// Specify the telecommand on-board memory images display statusbar pane identifiers
#define ID_TCONBOARDMEMORYIMAGES_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_TCONBOARDMEMORYIMAGES_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_TCONBOARDMEMORYIMAGES_STATUSBAR_DBMSPANE   ID_STATUSBAR_PANE2

class CTCOnBoardMemoryImagesWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CTCOnBoardMemoryImagesWnd)

	// Construction
public:
	CTCOnBoardMemoryImagesWnd();
	~CTCOnBoardMemoryImagesWnd();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  nIndex;
		INT  nPage;
		INT  cbColumns[2];
		RECT  rToolBar[2];
		SIZE  sizePanes[2];
		LOGFONT  sFont[3][2];
		COLORREF  nColor[2][2];
		SCROLLINFO  sScrollInfo[2];
	} DATA, *PDATA, *LPDATA;
private:
	CTCOnBoardMemoryImagesToolBar  m_wndToolBar[2];
	CTCOnBoardMemoryImagesStatusBar  m_wndStatusBar;
	CTCOnBoardMemoryImagesView  m_wndView;
private:
	CTCOnBoardMemoryImagesSettingsDialog  m_dlgSettings;
private:
	CMutex  *m_pDatabaseMutex;
	CTCOnBoardMemoryImagesDatabaseThread  m_cDatabaseThread;
private:
	CTCOnBoardMemoryImagesPrintJobs  m_pPrintJobs;
private:
	UINT  m_nLoggingPolicy;
	UINT  m_nLoggingReloadCount;
	CString  m_szLoggingFileName[2];
	CTimeSpan  m_tLoggingRetention;
	DWORDLONG  m_dwLoggingRetention;
	BOOL  m_bLoggingAsEvent;

	// Operations
public:
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths);
	BOOL SetLayout(UINT nPane, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizePane);
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths) CONST;
	BOOL GetLayout(UINT nPane, CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizePane) CONST;

	BOOL SetPaneTitleFont(UINT nPane, CFont *pFont);
	BOOL SetPaneTitleFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetPaneTitleFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetPaneTitleFont(UINT nPane, LOGFONT *plfFont) CONST;
	BOOL SetPaneItemsFont(UINT nPane, CFont *pFont);
	BOOL SetPaneItemsFont(UINT nPane, CONST LOGFONT *plfFont);
	BOOL GetPaneItemsFont(UINT nPane, CFont *pFont) CONST;
	BOOL GetPaneItemsFont(UINT nPane, LOGFONT *plfFont) CONST;

	BOOL SetTablesOutline(CFont *pTitleFont, CFont *pItemsFont, COLORREF nTitleFontColor, COLORREF nItemsFontColor, COLORREF nTitleBackgroundColor, COLORREF nItemsBackgroundColor);
	BOOL SetTablesOutline(CONST LOGFONT *plfTitleFont, CONST LOGFONT *plfItemsFont, COLORREF nTitleFontColor, COLORREF nItemsFontColor, COLORREF nTitleBackgroundColor, COLORREF nItemsBackgroundColor);
	BOOL GetTablesOutline(CFont *pTitleFont, CFont *pItemsFont, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, COLORREF &nTitleBackgroundColor, COLORREF &nItemsBackgroundColor) CONST;
	BOOL GetTablesOutline(LOGFONT *plfTitleFont, LOGFONT *plfItemsFont, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, COLORREF &nTitleBackgroundColor, COLORREF &nItemsBackgroundColor) CONST;

	BOOL EnableToolTipMode(BOOL bEnable = TRUE);
	BOOL IsToolTipModeEnabled() CONST;

	BOOL SetProcessors(CONST CTCOnBoardMemoryImagesProcessorItems &pItems, BOOL bAll = TRUE);
	BOOL GetProcessors(CTCOnBoardMemoryImagesProcessorItems &pItems, BOOL bAll = TRUE) CONST;

	BOOL SetCurProcessor(INT nIndex);
	BOOL SetCurProcessor(CONST CTCOnBoardMemoryImagesProcessorItem *pItem);
	INT GetCurProcessor(CTCOnBoardMemoryImagesProcessorItem *pItem = NULL) CONST;
	BOOL GetCurProcessor(CString &szProcessor) CONST;

	BOOL UpdateProcessor(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage = NULL, BOOL bOverwrite = FALSE, BOOL bDelete = FALSE, BOOL bDelayed = FALSE);

	UINT GetProcessorCount() CONST;

	BOOL DoAcknowledgeProcessor();
	BOOL CanAcknowledgeProcessor() CONST;

	BOOL StartMonitoring();
	BOOL UpdateMonitoring(CONST CTCItems &pItems, BOOL bAll = FALSE);
	BOOL UpdateMonitoring(CONST CTMEnvironment *pTMEnvironment);
	BOOL StopMonitoring();

	INT EnumOnBoardMemoryImages(CDatabaseOBProcessorMemoryImages &pImages) CONST;
	BOOL InsertOnBoardMemoryImage(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tUpdate, BOOL bDelayed = FALSE);
	BOOL UpdateOnBoardMemoryImage(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tUpdate, BOOL bOverwrite, BOOL bDelayed = FALSE);
	BOOL DeleteOnBoardMemoryImage(LPCTSTR pszProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, BOOL bDelayed = FALSE);

	BOOL DoTransactOnBoardMemoryImage();
	BOOL CanTransactOnBoardMemoryImage() CONST;
	BOOL DoImportOnBoardMemoryImage();
	BOOL CanImportOnBoardMemoryImage() CONST;
	BOOL DoExportOnBoardMemoryImage();
	BOOL CanExportOnBoardMemoryImage() CONST;
	BOOL DoDeleteOnBoardMemoryImage();
	BOOL CanDeleteOnBoardMemoryImage() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowAbove();
	BOOL CanInsertOnBoardMemoryImageTableRowAbove() CONST;
	BOOL DoInsertOnBoardMemoryImageTableRowBelow();
	BOOL CanInsertOnBoardMemoryImageTableRowBelow() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnBefore();
	BOOL CanInsertOnBoardMemoryImageTableColumnBefore() CONST;
	BOOL DoInsertOnBoardMemoryImageTableColumnAfter();
	BOOL CanInsertOnBoardMemoryImageTableColumnAfter() CONST;
	BOOL DoClearOnBoardMemoryImageTableRow();
	BOOL CanClearOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableRow();
	BOOL CanDeleteOnBoardMemoryImageTableRow() CONST;
	BOOL DoDeleteOnBoardMemoryImageTableColumn();
	BOOL CanDeleteOnBoardMemoryImageTableColumn() CONST;
	BOOL DoCopyOnBoardMemoryImageTableRow();
	BOOL CanCopyOnBoardMemoryImageTableRow() CONST;
	BOOL DoPasteOnBoardMemoryImageTableRow();
	BOOL CanPasteOnBoardMemoryImageTableRow() CONST;
	BOOL DoPrintOnBoardMemoryImageTable();
	BOOL CanPrintOnBoardMemoryImageTable() CONST;
	BOOL DoDiscardOnBoardMemoryImageTable();
	BOOL CanDiscardOnBoardMemoryImageTable() CONST;
	BOOL DoResetOnBoardMemoryImageTable();
	BOOL CanResetOnBoardMemoryImageTable() CONST;

	BOOL SetLoggingOptions();
	BOOL SetLoggingOptions(UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent);
	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	BOOL LogActivity(CONST CTCLogEntry *pEntry);

	BOOL SetPrintJobs(CONST CTCOnBoardMemoryImagesPrintJobs &pPrintJobs);
	BOOL GetPrintJobs(CTCOnBoardMemoryImagesPrintJobs &pPrintJobs) CONST;

	BOOL Print(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo = NULL);
	BOOL Print(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tUpdate);

	BOOL SetDBMSBehavior(CONST CTimeSpan &tDelay, BOOL bFlush, BOOL bFile);
	BOOL GetDBMSBehavior(CTimeSpan &tDelay, BOOL &bFlush, BOOL &bFile) CONST;
	CString GetDBMSDetails() CONST;
	BOOL IsDBMSOnline() CONST;

private:
	BOOL CreateToolBars();
	BOOL CreateStatusBar();
	BOOL CreateView();

	BOOL Customize(BOOL bDefault);

	BOOL UpdateAllPanes();
	VOID UpdateMessagePane();
	VOID UpdateModePane();
	VOID UpdateDBMSPane();

	VOID UpdateContents();

	BOOL LogDump(LPCTSTR pszDump, LPCTSTR pszVersion, LPCTSTR pszActivity);
	BOOL LogDumpTemplate(LPCTSTR pszDump, LPCTSTR pszActivity);
	BOOL LogDumpFlags(LPCTSTR pszDump, CONST CStringArray &szFlags);
	BOOL LogDumpBehavior(BOOL bDBMS);

	BOOL SetContents(CONST CByteArray &nContentsInfo);
	BOOL GetContents(CByteArray &nContentsInfo) CONST;

	BOOL SetPrintJobs(CONST CByteArray &nPrintInfo);
	BOOL GetPrintJobs(CByteArray &nPrintInfo) CONST;

	BOOL GetPrintProperties(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, CString &szTitle, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont, CPtrArray &pSymbols, CUIntArray &nSymbolIDs) CONST;
	BOOL GetPrintProperties(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, CString &szTitle, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST;

private:
	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszTitle, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTextViewAttributes &pAttributes, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszTitle, CONST CStringArray &szColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc = FALSE);
	BOOL DrawPrintDocSymbol(CDC &cDC, LPRECT prClip, UINT nSymbolID, CONST CPtrArray &pSymbols, CONST CUIntArray &nSymbolIDs);
	BOOL DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc = FALSE);
	BOOL DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocSubTitle(LPCTSTR pszTitle) CONST;
	CString GetPrintDocDetails(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocComments(CONST CTCOnBoardMemoryImagesPrintJobInfo *pJobInfo) CONST;
	CString GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST;

	INT ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST;

	BOOL CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST;
	BOOL CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST;

	INT CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST;
	INT CalcPrintDocTitleWidth(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST;
	INT CalcPrintDocColumnWidth(CDC &cDC, CONST RECT &rArea, LPCTSTR pszColumn, CStringArray &szContents, CFont *pItemsFont) CONST;

	BOOL CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;

private:
	BOOL SetLayoutInfo(CONST RECT &rPropertiesToolBar, CONST RECT &rOperationsToolBar, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST SIZE &sizeSummaryPane, CONST SIZE &sizeDetailsPane, CONST LOGFONT *pSummaryPaneTitleFont, CONST LOGFONT *pSummaryPaneItemsFont, CONST LOGFONT *pDetailsPaneTitleFont, CONST LOGFONT *pDetailsPaneItemsFont, CONST LOGFONT *pDetailsPaneTableTitleFont, CONST LOGFONT *pDetailsPaneTableItemsFont, COLORREF nDetailsPaneTableTitleFontColor, COLORREF nDetailsPaneTableItemsFontColor, COLORREF nDetailsPaneTableTitleBackgroundColor, COLORREF nDetailsPaneTableItemsBackgroundColor, INT nIndex, INT nPage, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo);
	BOOL GetLayoutInfo(RECT &rPropertiesToolBar, RECT &rOperationsToolBar, CUIntArray &nColumns, CUIntArray &nWidths, CSize &sizeSummaryPane, CSize &sizeDetailsPane, LOGFONT *pSummaryPaneTitleFont, LOGFONT *pSummaryPaneItemsFont, LOGFONT *pDetailsPaneTitleFont, LOGFONT *pDetailsPaneItemsFont, LOGFONT *pDetailsPaneTableTitleFont, LOGFONT *pDetailsPaneTableItemsFont, COLORREF &nDetailsPaneTableTitleFontColor, COLORREF &nDetailsPaneTableItemsFontColor, COLORREF &nDetailsPaneTableTitleBackgroundColor, COLORREF &nDetailsPaneTableItemsBackgroundColor, INT &nIndex, INT &nPage, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCOnBoardMemoryImagesWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
	virtual void RecalcLayout(CDisplayToolBar *pToolBar);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Check() CONST;
	virtual BOOL Stop();
	virtual BOOL Prepare(BOOL bDialog);
	virtual VOID Update();
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
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:
	BOOL OnCloseSettingsDialog(UINT nCode);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCOnBoardMemoryImagesWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSettings();
	afx_msg void OnAcknowledge();
	afx_msg void OnPrint();
	afx_msg void OnTableTransact();
	afx_msg void OnTableDelete();
	afx_msg void OnTableImport();
	afx_msg void OnTableExport();
	afx_msg void OnTableInsertRowAbove();
	afx_msg void OnTableInsertRowBelow();
	afx_msg void OnTableInsertColumnBefore();
	afx_msg void OnTableInsertColumnAfter();
	afx_msg void OnTableClearRow();
	afx_msg void OnTableDeleteRow();
	afx_msg void OnTableDeleteColumn();
	afx_msg void OnTableCopyRow();
	afx_msg void OnTablePasteRow();
	afx_msg void OnTableDiscard();
	afx_msg void OnTableReset();
	afx_msg void OnTablePrint();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAcknowledge(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableTransact(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableExport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableInsertRowAbove(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableInsertRowBelow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableInsertColumnBefore(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableInsertColumnAfter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableClearRow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableDeleteRow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableDeleteColumn(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableCopyRow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTablePasteRow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableDiscard(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTableReset(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTablePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarModePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarDBMSPane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TCONBOARD_H__
