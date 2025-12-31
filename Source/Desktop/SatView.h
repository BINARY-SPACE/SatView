// SATVIEW.H : SatView Desktop Application.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the application related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/04/02 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SATVIEW_H__
#define __SATVIEW_H__

#define SPACETRAVELLERENVIRONMENT
#define SOCKET_MFC_EXTENSTIONS
#define SECURITY_WIN32

#define _USE_MATH_DEFINES

#ifndef RC_INVOKED
#include <afxwin.h>
#include <afxext.h>
#include <afxwinappex.h>
#include <afxdialogex.h>
#include <afxsplitterwndex.h>
#include <afxcontrolbars.h>
#include <afxheaderctrl.h>
#include <afxctl.h>
#include <afxdisp.h>
#include <afxhtml.h>
#include <afxinet.h>
#include <afxpriv.h>
#include <afxsock.h>
#include <afxcmn.h>
#include <afxdb.h>
#include <afxmt.h>

#include <atlenc.h>
#include <atlfile.h>
#include <atlimage.h>
#include <atlsocket.h>
#include <atlsecurity.h>

#include <cryptuiapi.h>

#include <comdef.h>

#include <evntprov.h>

#include <float.h>

#include <math.h>

#include <pdh.h>
#include <pdhmsg.h>

#include <ras.h>
#include <raserror.h>
#include <tapi3.h>

#include <sapi.h>
#pragma warning(push)
#pragma warning(disable: 4996)
#include <sphelper.h>
#pragma warning(pop)

#include <schannel.h>
#include <security.h>
#include <sspi.h>

#include <windns.h>
#include <wininet.h>
#include <winioctl.h>
#include <winfax.h>

#include <ws2tcpip.h>


#include "audio.h"
#include "books.h"
#include "event.h"
#include "mutex.h"
#include "views.h"
#include "token.h"
#include "tools.h"
#include "macros.h"
#include "mimics.h"
#include "thread.h"
#include "archive.h"
#include "devices.h"
#include "jscript.h"
#include "logfile.h"
#include "network.h"
#include "strings.h"
#include "timekey.h"
#include "version.h"
#include "accounts.h"
#include "controls.h"
#include "database.h"
#include "eventlog.h"
#include "language.h"
#include "messages.h"
#include "profiles.h"
#include "registry.h"
#include "security.h"
#include "assistant.h"
#include "ttcprocess.h"
#include "tcprocedures.h"

#include "MimicsCtlEnum.h"

#ifdef SATELLITETRACKING
#include "Speech.h"
#endif
#endif

#include "resource.h"		// main symbols
#include "SatView.rh"

#include "tc.h"
#include "tm.h"
#include "cpu.h"
#include "and.h"
#include "grd.h"
#include "hex.h"
#include "ool.h"
#include "mmd.h"
#include "pod.h"
#include "logo.h"
#include "tpep.h"
#include "jcode.h"
#include "profile.h"
#include "displays.h"
#include "eventbox.h"
#include "tcstacks.h"
#include "tchistory.h"
#include "tcmonitor.h"
#include "tconboard.h"
#include "tcdiagnostics.h"
#ifndef NOSTDLIB
#include "satellitetracking.h"
#endif

#include "dialogs.h"


/////////////////////////////////////////////////////////////////////////////
// CMainRibbonBar window

class CMainRibbonBar : public CMFCRibbonBar
{
	DECLARE_DYNCREATE(CMainRibbonBar)

	// Construction
public:
	CMainRibbonBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainRibbonBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainRibbonBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainRibbonButton

class CMainRibbonButton : public CMFCRibbonButton
{
	DECLARE_DYNCREATE(CMainRibbonButton)

	// Construction
public:
	CMainRibbonButton(UINT nID = 0, LPCTSTR pszText = NULL, HICON hIcon = NULL, HICON hSmallIcon = NULL);
	~CMainRibbonButton();

	// Attributes
private:
	HICON  m_hIcon[2];

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainRibbonBar)
public:
	virtual CSize GetImageSize(RibbonImageType type) const;
	virtual CSize GetIntermediateSize(CDC *pDC);
	virtual BOOL HasLargeMode() const;
protected:
	virtual void OnUpdateCmdUI(CMFCRibbonCmdUI *pCmdUI, CFrameWnd *pTarget, BOOL bDisableIfNoHndler);
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainStatusBarClockThread thread

// Specify the main statusbar clock update interval
#define MAINSTATUSBARCLOCK_UPDATE_INTERVAL   500

class CMainStatusBarClockThread : public CThread
{
	DECLARE_DYNCREATE(CMainStatusBarClockThread)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL Start(class CMainStatusBar *pStatusBar);
	BOOL Stop();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainStatusBarClockThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainStatusBarClockThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainStatusBarToolTipCtrl window

class CMainStatusBarToolTipCtrl : public CToolTipCtrl
{
	DECLARE_DYNCREATE(CMainStatusBarToolTipCtrl)

	// Construction
public:

	// Attributes
private:
	CString  m_szText;
	TOOLINFO  m_sInfo;

	// Operations
public:
	BOOL UpdateTipText(LPCTSTR pszText, CWnd *pWnd, UINT nToolID = 0);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainStatusBarToolTipCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainStatusBarToolTipCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainStatusBar window

// Specify the statusbar pane identifiers
#define ID_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_STATUSBAR_PROGRESSPANE   ID_STATUSBAR_PANE1
#define ID_STATUSBAR_SEPARATORPANE   ID_STATUSBAR_PANE2
#define ID_STATUSBAR_NETWORKPANE   ID_STATUSBAR_PANE3
#define ID_STATUSBAR_TELEMETRYPANE   ID_STATUSBAR_PANE4
#define ID_STATUSBAR_TELECOMMANDPANE   ID_STATUSBAR_PANE5
#define ID_STATUSBAR_ARCHIVINGPANE   ID_STATUSBAR_PANE6
#define ID_STATUSBAR_CPUPERFORMANCEPANE   ID_STATUSBAR_PANE7
#define ID_STATUSBAR_CLOCKPANE   ID_STATUSBAR_PANE8
// Specify the statusbar progress pane width
#define STATUSBAR_PROGRESSPANE_WIDTH   250
// Specify the statusbar performance samples
#define STATUSBAR_CPUPERFORMANCEPANE_SAMPLES   16
#define STATUSBAR_CPUPERFORMANCEPANEAVERAGE_SAMPLES   ((1000*SECONDSPERHOUR)/STATUSBAR_CPUPERFORMANCEPANE_UPDATE_INTERVAL)
#define STATUSBAR_CPUPERFORMANCEPANE_UPDATE_INTERVAL   5000
// Specify the statusbar timer related identifiers
#define STATUSBAR_TIMERID   100
#define STATUSBAR_TIMEOUT   1000

class CMainStatusBar : public CMFCStatusBar
{
	DECLARE_DYNCREATE(CMainStatusBar)

	// Construction
public:
	CMainStatusBar();
	~CMainStatusBar();

	// Attributes
private:
	CFont  m_cPanesFont;
	CUIntArray  m_nPaneIDs;
	CRect  m_rNetworkPane;
	CRect  m_rTelemetryPane;
	CRect  m_rTelecommandPane;
	CRect  m_rArchivingPane;
	CRect  m_rCPUPerformancePane;
	CRect  m_rClockPane;
	BOOL  m_bPanes[6];
private:
	CString  m_szTMDevice[2];
	CString  m_szTCDevice[2];
	CString  m_szArchiveFile;
	CString  m_szNetworkServer;
	CString  m_szBackupDirectory;
	CString  m_szCPUPerformanceStatus;
	RASCONNSTATE  m_nNetworkState;
	UINT  m_nArchiveFreeSpace;
	UINT  m_nBackupFreeSpace;
	UINT  m_nTMDeviceStatus;
	UINT  m_nTCDeviceStatus;
	BOOL  m_bArchiveStatus;
	BOOL  m_bBackupStatus;
private:
	UINT  m_nCPUPerformanceValueCount;
	double  m_fCPUPerformanceValueAverage;
	CUIntArray  m_nCPUPerformanceValues;
	CCPUPerformanceMonitor  m_cCPUPerformanceMonitor;
private:
	CString  m_szToolTipText[6];
	CMainStatusBarToolTipCtrl  m_wndToolTip[6];
private:
	CImage  m_cNetwork[2];
	CImage  m_cLamps[2][4];
	CImage  m_cDisks[11];
	CImage  m_cCPUChart;
private:
	CMainStatusBarClockThread  m_cClockThread;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, UINT nID = AFX_IDW_STATUS_BAR);

	BOOL SetIndicators();
	BOOL SetIndicators(CONST UINT *pID, INT nSize);
	VOID SetIndicators(CONST CUIntArray &nPaneIDs);
	INT GetIndicators(CUIntArray &nPaneIDs) CONST;

	VOID UpdateNetworkPane();
	VOID UpdateNetworkPane(LPCTSTR pszServer, RASCONNSTATE nState);
	VOID UpdateTelemetryPane();
	VOID UpdateTelemetryPane(CONST CTMProviderDevice *pDevice);
	VOID UpdateTelecommandPane();
	VOID UpdateTelecommandPane(CONST CTCUplinkDevice *pDevice);
	VOID UpdateArchivingPane();
	VOID UpdateArchivingPane(LPCTSTR pszArchiveFile, UINT nArchiveFreeSpace, BOOL bArchiveStatus, LPCTSTR pszBackupDirectory, UINT nBackupFreeSpace, BOOL bBackupStatus);
	VOID UpdateCPUPerformancePane();
	VOID UpdateClockPane();
	VOID UpdateAllPanes();

	BOOL ShowPane(UINT nPaneID, BOOL bVisible = TRUE);
	BOOL IsPaneVisible(UINT nPaneID) CONST;
	BOOL IsPaneAvailable(UINT nPaneID) CONST;

	BOOL SetProgressIndicator(LPCTSTR pszMessage);
	BOOL ShowProgress(INT nPercent);
	BOOL IsShowingProgress() CONST;

private:
	VOID DrawPanes();
	VOID DrawNetworkStatus(CDC *pDC);
	VOID DrawTelemetryStatus(CDC *pDC);
	VOID DrawTelecommandStatus(CDC *pDC);
	VOID DrawArchivingStatus(CDC *pDC);
	VOID DrawCPUPerformanceStatus(CDC *pDC);
	VOID DrawClockTime(CDC *pDC);

	CString FormatNetworkStatus() CONST;
	CString FormatTelemetryStatus() CONST;
	CString FormatTelecommandStatus() CONST;
	CString FormatArchivingStatus() CONST;
	CString FormatCPUPerformanceStatus() CONST;
	CString FormatClockDate() CONST;
	CString FormatClockTime() CONST;

	INT CalcNetworkPaneWidth();
	INT CalcTelemetryPaneWidth();
	INT CalcTelecommandPaneWidth();
	INT CalcArchivingPaneWidth();
	INT CalcCPUPerformancePaneWidth();
	INT CalcClockPaneWidth();

	INT TranslateTMDeviceStatus(UINT nStatus) CONST;
	INT TranslateTCDeviceStatus(UINT nStatus) CONST;
	INT TranslateArchivingStatus(UINT nStatus) CONST;

	VOID RecalcPanes();

private:
	BOOL LoadSymbols();
	VOID FreeSymbols();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainStatusBar)
public:
	virtual BOOL SetPaneText(int nIndex, LPCTSTR lpszNewText, BOOL bUpdate = TRUE);
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
	//{{AFX_MSG(CMainStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainWnd frame

class CMainWnd : public CLocaleMDIFrameWnd
{
	DECLARE_DYNCREATE(CMainWnd)

	// Construction
public:
	CMainWnd();
	~CMainWnd();

	// Attributes
private:
	CMainRibbonBar  m_wndRibbonBar;
	CMainStatusBar  m_wndStatusBar;
private:
	CDisplayFrame  *m_pDisplayFrame;
	CDisplayArea  *m_pDisplayArea;
	CCLCWToolWnd  *m_pCLCWToolWnd;
	CEventBoxWnd  *m_pReportWnd;
	CLogoWnd  *m_pLogoWnd;
private:
	CAboutDialog  m_dlgAbout;
	CSettingsDialog  m_dlgSettings;
	CAccountsDialog  m_dlgUserAccounts;
	CAccountChangeDialog  m_dlgAccountChange;
	CPrivilegesDialog  m_dlgUserPrivileges;
	CSystemAlertsDialog  m_dlgSystemAlerts;
	CPrintPageSetupDialog  m_dlgPrintPageSetup;
	CPrintPagePrepareDialog  m_dlgPrintPagePrepare;
	CUserAddressBookDialog  m_dlgUserAddressBook;
	CServerAddressBookDialog  m_dlgServerAddressBook;
	CToolsDownloadsDialog  m_dlgToolsDownloads;
	CToolsOptionsDialog  m_dlgToolsOptions;
private:
	CANDImportDialog  m_dlgANDImport;
	CANDExportDialog  m_dlgANDExport;
	CGRDImportDialog  m_dlgGRDImport;
	CGRDExportDialog  m_dlgGRDExport;
	CPODImportDialog  m_dlgPODImport;
	CPODExportDialog  m_dlgPODExport;
private:
	CPFLPServiceDialog  m_dlgPFLPService;
	CPFLPClientsDialog  m_dlgPFLPClients;
private:
	CTPEPServiceDialog  m_dlgTPEPService;
	CTPEPClientsDialog  m_dlgTPEPClients;
	CTPEPConnectDialog  m_dlgTPEPConnect;
private:
	CAutomationServiceDialog  m_dlgAutomationService;
private:
	CMemoryDumpsServiceDialog  m_dlgMemoryDumpsService;
	CMemoryDumpsImportDialog  m_dlgMemoryDumpsImport;
	CMemoryDumpsExportDialog  m_dlgMemoryDumpsExport;
private:
	CTelemetryServiceDialog  m_dlgTelemetryService;
private:
	CTelemetryEventsDialog  m_dlgTelemetryEvents;
	CTelemetryEventsImportDialog  m_dlgTelemetryEventsImport;
	CTelemetryEventsExportDialog  m_dlgTelemetryEventsExport;
private:
	CTelemetryReportsDialog  m_dlgTelemetryReports;
	CTelemetryReportsImportDialog  m_dlgTelemetryReportsImport;
	CTelemetryReportsExportDialog  m_dlgTelemetryReportsExport;
	CTelemetryReportsHistoricalDialog  m_dlgTelemetryReportsRetrievals;
private:
	CTelemetryParametersDialog  m_dlgTelemetryParameters;
private:
	CTelemetryArchivesDialog  m_dlgTelemetryArchives;
	CTelemetryArchivesExtractionsImportDialog  m_dlgTelemetryArchivesExtractionsImport;
	CTelemetryArchivesExtractionsExportDialog  m_dlgTelemetryArchivesExtractionsExport;
private:
	CTelecommandServiceDialog  m_dlgTelecommandService;
	CTelecommandOptionsDialog  m_dlgTelecommandOptions;
private:
	CTelecommandParametersDialog  m_dlgTelecommandParameters;
private:
	BOOL  m_bBattery;
private:
	UINT  m_nExitID;

	// Operations
public:
	BOOL Create();

	VOID SaveLayout(UINT nCode);
	BOOL LoadLayout();
	VOID SaveDisplays(UINT nCode);
	BOOL LoadDisplays();
	BOOL CheckDisplays() CONST;
	VOID SaveUser(UINT nCode);
	BOOL LoadUser();

	VOID StartDisplays();
	VOID StopDisplays();

	BOOL StartAssistant();
	VOID StopAssistant();

	VOID UpdateTitle();
	VOID UpdateLayout();
	VOID UpdateStatusBar();
	VOID UpdateDisplays();
	VOID UpdateMenus();

	VOID UpdateNetworkStatus();
	VOID UpdateNetworkStatus(LPCTSTR pszServer, RASCONNSTATE nState);
	VOID UpdateTelemetryStatus();
	VOID UpdateTelemetryStatus(CONST CTMProviderDevice *pDevice);
	VOID UpdateTelecommandStatus();
	VOID UpdateTelecommandStatus(CONST CTCUplinkDevice *pDevice);
	VOID UpdateArchivingStatus();
	VOID UpdateArchivingStatus(LPCTSTR pszArchiveFile, UINT nArchiveFreeSpace, BOOL bArchiveStatus, LPCTSTR pszBackupDirectory, UINT nBackupFreeSpace, BOOL bBackupStatus);

	BOOL ShowProgress(INT nProgress = 0);

	BOOL ShowMessage(INT nMessageID);
	BOOL ShowMessage(LPCTSTR pszMessage);
	BOOL ReportMessage(INT nMessageID);

	BOOL ReportEvent(UINT nFlags, LPCTSTR pszEvent, BOOL bAudition = TRUE);
	BOOL ReportEvent(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition = TRUE);
	BOOL ReportEvent(CEventObject *pEvent);

	BOOL SetReportDisplay(CEventBoxWnd *pEventBoxWnd = NULL);
	CEventBoxWnd *GetReportDisplay() CONST;

public:
	CDisplayArea *GetDisplayArea() CONST;
	CDisplayFrame *GetDisplayFrame() CONST;
	CDisplayWnd *GetGlobalDisplay(INT nType = DISPLAY_TYPE_EVENTBOX) CONST;
	CDisplayWnd *GetActiveDisplay() CONST;
	CCLCWToolWnd *GetCLCWToolWnd() CONST;

private:
	BOOL CreateLogo();
	BOOL CreateRibbonBar();
	BOOL CreateStatusBar();

	BOOL StartCLCWPanel();
	BOOL StopCLCWPanel();

	BOOL ConstructSubMenu(CMenu *pMenu, CMFCRibbonButton *pButton, CImageList &cImages, CImageList &cSpecialImages, CUIntArray &nImageIDs);
	UINT GetSubMenuState(CMenu *pMenu) CONST;

	VOID PrintServerAddressBook(PRINTDLG *pPrintInfo);
	VOID PrintUserAddressBook(PRINTDLG *pPrintInfo);

	BOOL DrawServerAddressBookPrintDocContents(CDC &cDC, CONST CServerProfiles &pServers, CONST CRect &rPage, INT nTotalHeight, INT nPageOffset) CONST;
	BOOL DrawUserAddressBookPrintDocContents(CDC &cDC, CONST CUserProfiles &pUsers, CONST CRect &rPage, INT nTotalHeight, INT nPageOffset) CONST;

	BOOL DrawAddressBookPrintDocPageFrame(CDC &cDC, LPCTSTR pszTitle, LPCTSTR pszSubTitle, LPCTSTR pszNotice, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage, CRect &rPage, BOOL bCalc = FALSE) CONST;
	BOOL DrawAddressBookPrintDocPageTitle(CDC &cDC, LPCTSTR pszTitle, CRect &rPage, BOOL bCalc = FALSE) CONST;
	BOOL DrawAddressBookPrintDocPageSubTitle(CDC &cDC, LPCTSTR pszSubTitle, CRect &rPage, BOOL bCalc = FALSE) CONST;
	BOOL DrawAddressBookPrintDocPageNotice(CDC &cDC, LPCTSTR pszNotice, CRect &rPage, BOOL bCalc = FALSE) CONST;
	BOOL DrawAddressBookPrintDocPageFooter(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage, CRect &rPage, BOOL bCalc = FALSE) CONST;

	BOOL CalcAddressBookPrintDocTitleFont(CDC &cDC, INT nWidth, CFont &cFont) CONST;
	BOOL CalcAddressBookPrintDocSubTitleFont(CDC &cDC, INT nWidth, CFont &cFont) CONST;
	BOOL CalcAddressBookPrintDocFooterFont(CDC &cDC, INT nWidth, CFont &cFont) CONST;
	BOOL CalcAddressBookPrintDocNoticeFonts(CDC &cDC, INT nWidth, CFont &cFont, CFont &cLogoFont) CONST;
	CRect CalcAddressBookPrintDocPageExtent(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST;
	INT CalcAddressBookPrintDocTitleHeight(CDC &cDC, CFont *pTitleFont) CONST;

	INT CalcServerAddressBookPrintDocExtent(CDC &cDC, CONST CServerProfiles &pServers, CONST RECT &rPage, CUIntArray &nPaging) CONST;
	INT CalcUserAddressBookPrintDocExtent(CDC &cDC, CONST CUserProfiles &pUsers, CONST RECT &rPage, CUIntArray &nPaging) CONST;
	BOOL CalcServerAddressBookPrintDocContentFonts(CDC &cDC, CONST CServerProfiles &pServers, INT nWidth, CFont &cTitleFont, CFont &cItemsFont, CFont &cDetailsFont) CONST;
	BOOL CalcUserAddressBookPrintDocContentFonts(CDC &cDC, CONST CUserProfiles &pUsers, INT nWidth, CFont &cTitleFont, CFont &cParagraphFont, CFont &cItemsFont) CONST;
	BOOL CalcServerAddressBookPrintDocColumnWidths(CDC &cDC, CONST CServerProfiles &pServers, CFont *pTitleFont, CFont *pItemsFont, CFont *pDetailsFont, CUIntArray &nWidths, INT &nMargin) CONST;
	BOOL CalcUserAddressBookPrintDocColumnWidths(CDC &cDC, CONST CUserProfiles &pUsers, CFont *pTitleFont, CFont *pParagraphFont, CFont *pItemsFont, CUIntArray &nWidths, INT &nMargin) CONST;

	INT CalcUserAddressBookNameInfo(CONST CUserProfileInfo *pUserInfo, CString &szName, CStringArray &szDetails) CONST;
	INT CalcUserAddressBookOfficeInfo(CONST CUserProfileInfo *pUserInfo, CString &szTitle, CStringArray &szAddress, CStringArray &szNumbers) CONST;
	INT CalcUserAddressBookHomeInfo(CONST CUserProfileInfo *pUserInfo, CString &szTitle, CStringArray &szAddress, CStringArray &szNumbers) CONST;
	INT CalcUserAddressBookMissionInfo(CONST CUserProfileInfo *pUserInfo, CString &szTitle, CStringArray &szAddress, CStringArray &szNumbers) CONST;
	INT CalcUserAddressBookHolidayInfo(CONST CUserProfileInfo *pUserInfo, CString &szTitle, CStringArray &szAddress, CStringArray &szNumbers) CONST;

	INT ExtractUserAddressBookInfo(LPCTSTR pszInfo, CStringArray &szDetails) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainWnd)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT pcs, CCreateContext *pContext);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnEnterIdle(UINT nType, CWnd *pWnd);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnSystemSettingsChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetMessageString(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBatteryCondition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCheckSystemHealth(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnQueryEndSession();
	afx_msg void OnSettings();
	afx_msg void OnAccounts();
	afx_msg void OnAccountPrivileges();
	afx_msg void OnAccountChange();
	afx_msg void OnTelemetrySettings();
	afx_msg void OnTelecommandSettings();
	afx_msg void OnSimulatorsSettings();
	afx_msg void OnSCOEsSettings();
	afx_msg void OnSystemAlerts();
	afx_msg void OnAutomationService();
	afx_msg void OnMemoryDumpSettings();
	afx_msg void OnMemoryDumpImport();
	afx_msg void OnMemoryDumpExport();
	afx_msg void OnTelemetryEventsSettings();
	afx_msg void OnTelemetryEventsImport();
	afx_msg void OnTelemetryEventsExport();
	afx_msg void OnTelemetryReportsSettings();
	afx_msg void OnTelemetryReportsRetrievals();
	afx_msg void OnTelemetryReportsImport();
	afx_msg void OnTelemetryReportsExport();
	afx_msg void OnTelemetryParameters();
	afx_msg void OnTelemetryArchivesSettings();
	afx_msg void OnTelemetryArchivesExtractionsImport();
	afx_msg void OnTelemetryArchivesExtractionsExport();
	afx_msg void OnAND();
	afx_msg void OnGRD();
	afx_msg void OnHEX();
	afx_msg void OnMMD();
	afx_msg void OnOOL();
	afx_msg void OnPOD();
	afx_msg void OnSatelliteTrackingTool();
	afx_msg void OnEventBox();
	afx_msg void OnMailBox();
	afx_msg void OnLogBook();
	afx_msg void OnANDImport();
	afx_msg void OnGRDImport();
	afx_msg void OnPODImport();
	afx_msg void OnANDExport();
	afx_msg void OnGRDExport();
	afx_msg void OnPODExport();
	afx_msg void OnTCManualStack();
	afx_msg void OnTCAutomaticStack();
	afx_msg void OnTCProceduresMonitor();
	afx_msg void OnTCDiagnosticsOversamplingDump();
	afx_msg void OnTCOnBoardBufferQueues();
	afx_msg void OnTCOnBoardMemoryImages();
	afx_msg void OnTCHistory();
	afx_msg void OnTelecommandParameters();
	afx_msg void OnTelecommandOptions();
	afx_msg void OnPFLPService();
	afx_msg void OnPFLPClients();
	afx_msg void OnTPEPService();
	afx_msg void OnTPEPConnect();
	afx_msg void OnTPEPClients();
	afx_msg void OnTPEPView();
	afx_msg void OnServerAddressBook();
	afx_msg void OnUserAddressBook();
	afx_msg void OnToolsDownloads();
	afx_msg void OnToolsOptions();
	afx_msg void OnPrintSetup();
	afx_msg void OnPrint();
	afx_msg void OnPrintServerAddressBook();
	afx_msg void OnPrintUserAddressBook();
	afx_msg void OnDisplayReduceFonts();
	afx_msg void OnDisplayRestoreFonts();
	afx_msg void OnWindows();
	afx_msg void OnNextWindow();
	afx_msg void OnPreviousWindow();
	afx_msg void OnCloseWindow();
	afx_msg void OnCloseAllWindows();
	afx_msg void OnLock();
	afx_msg void OnAssistantSupportDateConversions();
	afx_msg void OnAssistantListen();
	afx_msg void OnStatusBarTelemetryStatus();
	afx_msg void OnStatusBarTelecommandStatus();
	afx_msg void OnStatusBarArchivingStatus();
	afx_msg void OnStatusBarCPUPerformanceStatus();
	afx_msg void OnStatusBarClock();
	afx_msg void OnStatusBarHelp();
	afx_msg void OnMenuID(UINT nID);
	afx_msg void OnAbout();
	afx_msg void OnHelp();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAccounts(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAccountPrivileges(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAccountChange(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryEquipment(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetrySettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelecommandEquipment(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelecommandSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSimulatorsEquipment(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSimulatorsSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSCOEsEquipment(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSCOEsSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSystemAlerts(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAutomationService(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMemoryDumpSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMemoryDumpImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMemoryDumpExport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryEventsSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryEventsImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryEventsExport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryReportsSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryReportsRetrievals(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryReportsImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryReportsExport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryParameters(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryArchivesSettings(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryArchivesExtractionsImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelemetryArchivesExtractionsExport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAND(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGRD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHEX(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMMD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOOL(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePOD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSatelliteTrackingTool(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEventBox(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMailBox(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLogBook(CCmdUI *pCmdUI);
	afx_msg void OnUpdateANDImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGRDImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePODImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateANDExport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGRDExport(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePODExport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCManualStack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCAutomaticStack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCProceduresMonitor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCDiagnosticsOversamplingDump(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCOnBoardBufferQueues(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCOnBoardMemoryImages(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCHistory(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelecommandParameters(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTelecommandOptions(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePFLPService(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePFLPClients(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTPEPService(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTPEPConnect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTPEPClients(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTPEPView(CCmdUI *pCmdUI);
	afx_msg void OnUpdateServerAddressBook(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUserAddressBook(CCmdUI *pCmdUI);
	afx_msg void OnUpdateToolsDownloads(CCmdUI *pCmdUI);
	afx_msg void OnUpdateToolsOptions(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrintSetup(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrintServerAddressBook(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrintUserAddressBook(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDisplayReduceFonts(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDisplayRestoreFonts(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWindows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNextWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePreviousWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCloseWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCascadeWindows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTileHorzWindows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTileVertWindows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateArrangeWindows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCloseAllWindows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLock(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDisplayPages(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDisplayWindows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDisplayWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAssistantSupportDateConversions(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAssistantListen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarTelemetryStatus(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarTelecommandStatus(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarArchivingStatus(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarCPUPerformanceStatus(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarClock(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarHelp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuID(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAbout(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHelp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExit(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDesktopAppCommandLineInfo

class CDesktopAppCommandLineInfo : public CCommandLineInfo
{
	// Constructors
public:
	CDesktopAppCommandLineInfo();

	// Attributes
private:
	CAccountToken  m_cAccountToken;
	BOOL  m_bSpacecraft;
	BOOL  m_bDatabase;
	BOOL  m_bPassword;
	BOOL  m_bUser;

	// Operations
public:
	CString GetSpacecraft() CONST;
	CString GetDatabase() CONST;
	CString GetPassword() CONST;
	CString GetUser() CONST;

	BOOL IsValid() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesktopAppCommandLineInfo)
	virtual void ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast);
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDesktopApp application

class CDesktopApp : public CAccountsApp, public CThread
{
	DECLARE_DYNAMIC(CDesktopApp)

	// Construction
public:
	CDesktopApp();
	~CDesktopApp();

	// Attributes
private:
	CDatabaseEngine  *m_pDatabase;
private:
	CANDLayouts  m_pTemporaryANDs;
	CGRDLayouts  m_pTemporaryGRDs;
	CPODLayouts  m_pTemporaryPODs;
private:
	CTMService  *m_pTMService;
	CTCService  *m_pTCService;
	CRASService  *m_pRASService;
	CPFLPService  *m_pPFLPService;
	CTPEPService  *m_pTPEPService;
	CAutomationService  *m_pAutomationService;
	CMemoryDumpsService  *m_pMemoryDumpsService;
	CTelemetryReportsService  *m_pTelemetryReportsService;
	CNotificationService  *m_pNotificationService;
	CToolsDatabaseService  *m_pToolsDatabaseService;
	CToolsDownloadService  *m_pToolsDownloadService;
	CNetworkBrowseService  *m_pNetworkBrowseService;
private:
	CPFLPServiceEngine  *m_pPFLPServiceEngine;
	CTPEPServiceEngine  *m_pTPEPServiceEngine;
	CMemoryDumpsServiceEngine  *m_pMemoryDumpsServiceEngine;
private:
	CEMailSystem  *m_pEMailSystem;
private:
	CSystemAlerts  *m_pSystemAlerts;
	CTelemetryEvents  *m_pTelemetryEvents;
	CTelemetryReports  *m_pTelemetryReports;
	CTelemetryHistoricalReports  *m_pTelemetryHistoricalReports;
private:
	CPrintProfiles  *m_pPrintProfiles;
	CAuditionProfiles  *m_pAuditionProfiles;
	CNotificationProfiles  *m_pNotificationProfiles;
	CArchivesExtractionProfiles  *m_pArchivesExtractionProfiles;
	CToolsDownloadProfiles  *m_pToolsDownloadProfiles;
private:
	CJScriptCodeExecutor  m_cScriptsExecutor;
	CDefaultPrinter  m_cDefaultPrinter;
	CEventLog  m_cEventLog;
private:
	CAccountToken  m_cAccountToken;
private:
	CAccountToken  *m_pLoginAccount;
	CLoginOptions  *m_pLoginOptions;
	CServerProfileInfo  *m_pLoginServerInfo;
	CLoginInfo  *m_pLoginInfo;
	HANDLE  m_hLoginMutex;
private:
	CString  m_szOperatingMode;
	BOOL  m_bOperatingMode;
	BOOL  m_bTMService;
	BOOL  m_bTCService;
	CEvent  m_bLogo;
private:
	UINT_PTR  m_nTimerID[3];
	UINT_PTR  m_nWaitID;
	UINT  m_nExitID;

	// Enumerators
public:
	enum {
		ChangeArea = 1,
		ChangeDatabase,
		ReloadDatabase,
		ChangeUser,
		Reset,
		Exit
	};

	// Operations
public:
	BOOL StartAccount();
	BOOL StartAccount(CONST CDesktopAppCommandLineInfo &cStartupInfo);
	BOOL StartAccount(CAccountToken *pAccountToken);
	BOOL StopAccount(CAccountToken *pAccountToken = NULL);
	BOOL ReloadAccount(UINT nCode = ReloadDatabase);
	VOID ResetAccount(CONST EVENT_DESCRIPTOR sEvent);

	VOID SaveConfigurationData();
	VOID LoadConfigurationData();
	VOID SetLoginData(HANDLE hMutex = NULL);
	HANDLE GetLoginData() CONST;
	BOOL SetLoginOptions(CONST CLoginOptions &pOptions);
	BOOL GetLoginOptions(CLoginOptions &pOptions) CONST;
	BOOL UpdateLoginOptions();
	BOOL SetPrintProfiles(CONST CPrintProfiles &pProfiles);
	BOOL GetPrintProfiles(CPrintProfiles &pProfiles) CONST;
	BOOL EnumPrintProfiles(CStringArray &szProfiles) CONST;
	BOOL UpdatePrintProfiles();
	BOOL SetAuditionProfiles(CONST CAuditionProfiles &pProfiles);
	BOOL GetAuditionProfiles(CAuditionProfiles &pProfiles) CONST;
	BOOL EnumAuditionProfiles(CStringArray &szProfiles) CONST;
	BOOL UpdateAuditionProfiles();
	BOOL SetNotificationProfiles(CONST CNotificationProfiles &pProfiles);
	BOOL GetNotificationProfiles(CNotificationProfiles &pProfiles) CONST;
	BOOL EnumNotificationProfiles(CStringArray &szProfiles) CONST;
	BOOL UpdateNotificationProfiles();
	BOOL DoNotification(LPCTSTR pszProfile, LPCTSTR pszMessage);
	BOOL DoNotification(LPCTSTR pszProfile, LPCTSTR pszMessage, INT nAlertType, CONST CStringArray &szRecipients);
	BOOL SetSystemAlerts(CONST CSystemAlerts &pAlerts);
	BOOL GetSystemAlerts(CSystemAlerts &pAlerts) CONST;
	BOOL UpdateSystemAlerts();
	BOOL SetTelemetryEvents(CONST CTelemetryEvents &pEvents);
	BOOL GetTelemetryEvents(CTelemetryEvents &pEvents) CONST;
	BOOL UpdateTelemetryEvents();
	BOOL SetTelemetryReports(CONST CTelemetryReports &pReports);
	BOOL GetTelemetryReports(CTelemetryReports &pReports) CONST;
	BOOL UpdateTelemetryReports();
	BOOL SetTelemetryHistoricalReports(CONST CTelemetryHistoricalReports &pHistoricalReports);
	BOOL GetTelemetryHistoricalReports(CTelemetryHistoricalReports &pHistoricalReports) CONST;
	BOOL UpdateTelemetryHistoricalReports();
	BOOL DoUpdateReport(CONST CTelemetryReportInfo *pReportInfo);
	BOOL DoUpdateReport(CONST CTelemetryReportInfo *pReportInfo, CONST CSystemAlertInfo *pAlertInfo);
	BOOL DoUpdateReport(CONST CTelemetryReportInfo *pReportInfo, CONST CTelemetryEventInfo *pEventInfo);
	BOOL SetToolsDownloadProfiles(CONST CToolsDownloadProfiles &pProfiles);
	BOOL GetToolsDownloadProfiles(CToolsDownloadProfiles &pProfiles) CONST;
	BOOL EnumToolsDownloadProfiles(CStringArray &szProfiles) CONST;
	BOOL UpdateToolsDownloadProfiles();

	BOOL SaveTemporaryDisplays();
	BOOL LoadTemporaryDisplays();
	BOOL AddTemporaryAND(LPCTSTR pszName, CONST CANDLayout &cLayout);
	BOOL AddTemporaryGRD(LPCTSTR pszName, CONST CGRDLayout &cLayout);
	BOOL AddTemporaryPOD(LPCTSTR pszName, CONST CPODLayout &cLayout);
	BOOL LoadTemporaryAND(LPCTSTR pszName, CANDLayout &cLayout) CONST;
	BOOL LoadTemporaryGRD(LPCTSTR pszName, CGRDLayout &cLayout) CONST;
	BOOL LoadTemporaryPOD(LPCTSTR pszName, CPODLayout &cLayout) CONST;
	INT EnumTemporaryANDs(CANDLayouts &pLayouts) CONST;
	INT EnumTemporaryGRDs(CGRDLayouts &pLayouts) CONST;
	INT EnumTemporaryPODs(CPODLayouts &pLayouts) CONST;
	BOOL RemoveTemporaryAND(LPCTSTR pszName);
	BOOL RemoveTemporaryGRD(LPCTSTR pszName);
	BOOL RemoveTemporaryPOD(LPCTSTR pszName);

	BOOL InitializeTMUnit(CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	BOOL InitializeTMUnit(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData = FALSE);
	BOOL InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData = FALSE);
	BOOL InitializeTMData(COolParameters &pOolParameters, BOOL bBadData = FALSE);
	BOOL InitializeTMDump(CMemoryDump &pDump, BOOL bBadData = FALSE);

	BOOL UpdateTMParameters(CONST CTMParameters &pTMParameters);

	VOID UpdateNetworkStatus();
	VOID UpdateNetworkStatus(LPCTSTR pszServer, RASCONNSTATE nState);
	VOID UpdateTelemetryStatus();
	VOID UpdateTelemetryStatus(CONST CTMProviderDevice *pDevice);
	VOID UpdateTelecommandStatus();
	VOID UpdateTelecommandStatus(CONST CTCUplinkDevice *pDevice);
	VOID UpdateArchivingStatus();
	VOID UpdateArchivingStatus(LPCTSTR pszArchiveFile, UINT nArchiveFreeSpace, BOOL bArchiveStatus, LPCTSTR pszBackupDirectory, UINT nBackupFreeSpace, BOOL bBackupStatus);

	BOOL InitializeDefaultPrinter();
	BOOL IsDefaultPrinterAvailable() CONST;
	BOOL SetDefaultPrinterInfo(CONST PAGESETUPDLG *pPrinterInfo);
	BOOL GetDefaultPrinterInfo(PAGESETUPDLG *pPrinterInfo) CONST;
	BOOL CreatePrinterDC(CDC &cDC);
	BOOL CreatePrinterDC(LPCTSTR pszProfile, CDC &cDC);
	BOOL CreatePrinterDC(CONST CPrintProfileInfo *pProfileInfo, CDC &cDC);
	BOOL CreatePrinterDC(HANDLE hDevNames, HANDLE hDevMode, CDC &cDC);

	VOID LoginTMService();
	VOID LoginTMService(CONST CServerProfileInfo *pServerInfo);
	BOOL IsLogginginTMService() CONST;
	VOID LogoutTMService();

	BOOL StartRASScheduler();
	BOOL ScheduleRASService(RASCONNSTATE nState);
	BOOL StopRASScheduler();

	BOOL SwitchOperatingMode(LPCTSTR pszMode, BOOL bReport = TRUE);
	BOOL SaveRegistryData(CONST CStringArray &szSubSystems);
	BOOL LoadRegistryData(CONST CStringArray &szSubSystems);
	BOOL CheckSystemHealth() CONST;

	BOOL ShowMessage(INT nMessageID);
	BOOL ShowMessage(LPCTSTR pszMessage);
	BOOL ReportMessage(INT nMessageID);

	BOOL ReportEvent(CONST CSystemAlertInfo *pAlertInfo);
	BOOL ReportEvent(CONST CTelemetryEventInfo *pEventInfo);
	BOOL ReportEvent(UINT nFlags, LPCTSTR pszEvent, BOOL bAudition = TRUE);
	BOOL ReportEvent(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition = TRUE);
	BOOL ReportEvent(CEventObject *pEvent);

	BOOL ShowProgress(INT nProgress = 0);

	BOOL ShowHelp(LPCTSTR pszTopic = NULL);
	BOOL IsHelpAvailable() CONST;

	HANDLE GetLogo() CONST;

public:
	CDatabaseEngine *GetDatabase() CONST;

	CTMService *GetTMService() CONST;
	CTCService *GetTCService() CONST;
	CRASService *GetRASService() CONST;
	CPFLPService *GetPFLPService() CONST;
	CTPEPService *GetTPEPService() CONST;
	CAutomationService *GetAutomationService() CONST;
	CMemoryDumpsService *GetMemoryDumpsService() CONST;
	CNotificationService *GetNotificationService() CONST;
	CTelemetryReportsService *GetTelemetryReportsService() CONST;
	CToolsDatabaseService *GetToolsDatabaseService() CONST;
	CToolsDownloadService *GetToolsDownloadService() CONST;
	CNetworkBrowseService *GetNetworkBrowseService() CONST;
	CPFLPServiceEngine *GetPFLPServiceSupport() CONST;
	CTPEPServiceEngine *GetTPEPServiceSupport() CONST;
	CMemoryDumpsServiceEngine *GetMemoryDumpsServiceSupport() CONST;
	CEMailSystem *GetEMailSystem() CONST;

	CDisplayFrame *GetDisplayFrame() CONST;
	CDisplayArea *GetDisplayArea() CONST;

	CMainWnd *GetMainWnd() CONST;

public:
	void *operator new(size_t cbObject);
	void operator delete(void *pObject);

private:
	INT RegisterApp();
	BOOL UnregisterApp();

	BOOL EvaluateAccount(CONST CDesktopAppCommandLineInfo &cStartupInfo, CAccountToken *pAccountToken);

	BOOL ActivateAccount();
	BOOL ActivateAccount(CAccountToken *pAccountToken);
	BOOL IsAccountActivated() CONST;

	VOID ShowAccountStatus();
	BOOL TestAccountStatus(EVENT_DESCRIPTOR &sEvent);

	BOOL CompareAccount(CAccountToken *pAccountToken) CONST;
	BOOL CompareAccountSpacecraft(CAccountToken *pAccountToken) CONST;
	BOOL CompareAccountUser(CAccountToken *pAccountToken) CONST;
	BOOL CompareAccountMode(CAccountToken *pAccountToken) CONST;
	BOOL CompareAccountDatabase(CAccountToken *pAccountToken) CONST;
	BOOL CompareAccountServer(CAccountToken *pAccountToken) CONST;

	BOOL LoadSpacecraftLibrary();
	VOID FreeSpacecraftLibrary(UINT nCode = Exit);
	BOOL LoadLayout();
	VOID FreeLayout(UINT nCode = Exit);
	BOOL LoadDatabase();
	VOID FreeDatabase(UINT nCode = Exit);
	BOOL LoadDisplays();
	VOID FreeDisplays(UINT nCode = Exit);
	BOOL LoadUser();
	VOID FreeUser(UINT nCode = Exit);

	BOOL SaveLoginOptions();
	BOOL LoadLoginOptions();
	BOOL SavePrintProfiles();
	BOOL LoadPrintProfiles();
	BOOL SaveAuditionProfiles();
	BOOL LoadAuditionProfiles();
	BOOL SaveNotificationProfiles();
	BOOL LoadNotificationProfiles();
	BOOL SaveToolsDownloadProfiles();
	BOOL LoadToolsDownloadProfiles();
	BOOL SaveSystemAlerts();
	BOOL LoadSystemAlerts();
	BOOL SaveTelemetryEvents();
	BOOL LoadTelemetryEvents();
	BOOL SaveTelemetryReports();
	BOOL LoadTelemetryReports();
	BOOL SaveTelemetryHistoricalReports();
	BOOL LoadTelemetryHistoricalReports();
	BOOL SaveToolsEMailSettings();
	BOOL LoadToolsEMailSettings();

	BOOL SaveTemporaryANDs(CByteArray &nANDs);
	BOOL SaveTemporaryGRDs(CByteArray &nGRDs);
	BOOL SaveTemporaryPODs(CByteArray &nPODs);
	BOOL LoadTemporaryANDs(CONST CByteArray &nANDs);
	BOOL LoadTemporaryGRDs(CONST CByteArray &nGRDs);
	BOOL LoadTemporaryPODs(CONST CByteArray &nPODs);

	VOID StartServices();
	VOID StopServices();
	VOID StartTMService();
	VOID UpdateTMService();
	VOID StopTMService();
	VOID StartTCService();
	VOID UpdateTCService();
	VOID StopTCService();
	VOID StartDisplays();
	VOID StopDisplays();
	VOID StartAssistant();
	VOID StopAssistant();

#ifndef SATELLITETRACKING
	BOOL InitializeSpeech();
	BOOL UninitializeSpeech();
#endif

public:
	VOID ShowWaitCursor();
	BOOL IsShowingWaitCursor() CONST;
	VOID StopWaitCursor();

public:
	static BOOL ValidateAccounts();

public:
	static VOID CALLBACK Login(HWND hWnd, UINT uMsg, UINT_PTR nEventID, DWORD dwTime);

	static BOOL CALLBACK LoginScheduler();
	static VOID CALLBACK LoginScheduler(HWND hWnd, UINT uMsg, UINT_PTR nEventID, DWORD dwTime);
	static VOID CALLBACK LoginState(HWND hWnd, UINT uMsg, UINT_PTR nEventID, DWORD dwTime);

	static BOOL CALLBACK EnumTopLevelWindows(HWND hWnd, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesktopApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL SaveState(LPCTSTR lpszSectionName = (LPCTSTR)NULL, CFrameImpl *pFrameImpl = (CFrameImpl *)NULL);
	virtual BOOL LoadState(LPCTSTR lpszSectionName = (LPCTSTR)NULL, CFrameImpl *pFrameImpl = (CFrameImpl *)NULL);
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDesktopApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline CDesktopApp *GetDesktopApp()
{
	return((CDesktopApp *)AfxGetApp());
}
inline BOOL StartAccount()
{
	return(GetDesktopApp()->StartAccount());
}
inline BOOL StartAccount(CONST CDesktopAppCommandLineInfo &cStartupInfo)
{
	return(GetDesktopApp()->StartAccount(cStartupInfo));
}
inline BOOL StartAccount(CAccountToken *pAccountToken)
{
	return(GetDesktopApp()->StartAccount(pAccountToken));
}
inline BOOL StopAccount(CAccountToken *pAccountToken = NULL)
{
	return(GetDesktopApp()->StopAccount(pAccountToken));
}
inline BOOL ReloadAccount(UINT nCode)
{
	return(GetDesktopApp()->ReloadAccount(nCode));
}
inline VOID ResetAccount(CONST EVENT_DESCRIPTOR sEvent)
{
	return(GetDesktopApp()->ResetAccount(sEvent));
}
inline VOID SaveConfigurationData()
{
	return(GetDesktopApp()->SaveConfigurationData());
}
inline VOID LoadConfigurationData()
{
	return(GetDesktopApp()->LoadConfigurationData());
}
inline VOID SetLoginData(HANDLE hMutex = NULL)
{
	return(GetDesktopApp()->SetLoginData(hMutex));
}
inline HANDLE GetLoginData()
{
	return(GetDesktopApp()->GetLoginData());
}
inline BOOL SetLoginOptions(CONST CLoginOptions &pOptions)
{
	return(GetDesktopApp()->SetLoginOptions(pOptions));
}
inline BOOL GetLoginOptions(CLoginOptions &pOptions)
{
	return(GetDesktopApp()->GetLoginOptions(pOptions));
}
inline BOOL UpdateLoginOptions()
{
	return(GetDesktopApp()->UpdateLoginOptions());
}
inline BOOL SetPrintProfiles(CONST CPrintProfiles &pProfiles)
{
	return(GetDesktopApp()->SetPrintProfiles(pProfiles));
}
inline BOOL GetPrintProfiles(CPrintProfiles &pProfiles)
{
	return(GetDesktopApp()->GetPrintProfiles(pProfiles));
}
inline BOOL EnumPrintProfiles(CStringArray &szProfiles)
{
	return(GetDesktopApp()->EnumPrintProfiles(szProfiles));
}
inline BOOL UpdatePrintProfiles()
{
	return(GetDesktopApp()->UpdatePrintProfiles());
}
inline BOOL SetAuditionProfiles(CONST CAuditionProfiles &pProfiles)
{
	return(GetDesktopApp()->SetAuditionProfiles(pProfiles));
}
inline BOOL GetAuditionProfiles(CAuditionProfiles &pProfiles)
{
	return(GetDesktopApp()->GetAuditionProfiles(pProfiles));
}
inline BOOL EnumAuditionProfiles(CStringArray &szProfiles)
{
	return(GetDesktopApp()->EnumAuditionProfiles(szProfiles));
}
inline BOOL UpdateAuditionProfiles()
{
	return(GetDesktopApp()->UpdateAuditionProfiles());
}
inline BOOL SetNotificationProfiles(CONST CNotificationProfiles &pProfiles)
{
	return(GetDesktopApp()->SetNotificationProfiles(pProfiles));
}
inline BOOL GetNotificationProfiles(CNotificationProfiles &pProfiles)
{
	return(GetDesktopApp()->GetNotificationProfiles(pProfiles));
}
inline BOOL EnumNotificationProfiles(CStringArray &szProfiles)
{
	return(GetDesktopApp()->EnumNotificationProfiles(szProfiles));
}
inline BOOL UpdateNotificationProfiles()
{
	return(GetDesktopApp()->UpdateNotificationProfiles());
}
inline BOOL DoNotification(LPCTSTR pszProfile, LPCTSTR pszMessage)
{
	return(GetDesktopApp()->DoNotification(pszProfile, pszMessage));
}
inline BOOL DoNotification(LPCTSTR pszProfile, LPCTSTR pszMessage, INT nAlertType, CONST CStringArray &szRecipients)
{
	return(GetDesktopApp()->DoNotification(pszProfile, pszMessage, nAlertType, szRecipients));
}
inline BOOL SetToolsDownloadProfiles(CONST CToolsDownloadProfiles &pProfiles)
{
	return(GetDesktopApp()->SetToolsDownloadProfiles(pProfiles));
}
inline BOOL GetToolsDownloadProfiles(CToolsDownloadProfiles &pProfiles)
{
	return(GetDesktopApp()->GetToolsDownloadProfiles(pProfiles));
}
inline BOOL EnumToolsDownloadProfiles(CStringArray &szProfiles)
{
	return(GetDesktopApp()->EnumToolsDownloadProfiles(szProfiles));
}
inline BOOL UpdateToolsDownloadProfiles()
{
	return(GetDesktopApp()->UpdateToolsDownloadProfiles());
}
inline BOOL SetSystemAlerts(CONST CSystemAlerts &pAlerts)
{
	return(GetDesktopApp()->SetSystemAlerts(pAlerts));
}
inline BOOL GetSystemAlerts(CSystemAlerts &pAlerts)
{
	return(GetDesktopApp()->GetSystemAlerts(pAlerts));
}
inline BOOL UpdateSystemAlerts()
{
	return(GetDesktopApp()->UpdateSystemAlerts());
}
inline BOOL SetTelemetryEvents(CONST CTelemetryEvents &pEvents)
{
	return(GetDesktopApp()->SetTelemetryEvents(pEvents));
}
inline BOOL GetTelemetryEvents(CTelemetryEvents &pEvents)
{
	return(GetDesktopApp()->GetTelemetryEvents(pEvents));
}
inline BOOL UpdateTelemetryEvents()
{
	return(GetDesktopApp()->UpdateTelemetryEvents());
}
inline BOOL SetTelemetryReports(CONST CTelemetryReports &pReports)
{
	return(GetDesktopApp()->SetTelemetryReports(pReports));
}
inline BOOL GetTelemetryReports(CTelemetryReports &pReports)
{
	return(GetDesktopApp()->GetTelemetryReports(pReports));
}
inline BOOL UpdateTelemetryReports()
{
	return(GetDesktopApp()->UpdateTelemetryReports());
}
inline BOOL SetTelemetryHistoricalReports(CONST CTelemetryHistoricalReports &pHistoricalReports)
{
	return(GetDesktopApp()->SetTelemetryHistoricalReports(pHistoricalReports));
}
inline BOOL GetTelemetryHistoricalReports(CTelemetryHistoricalReports &pHistoricalReports)
{
	return(GetDesktopApp()->GetTelemetryHistoricalReports(pHistoricalReports));
}
inline BOOL UpdateTelemetryHistoricalReports()
{
	return(GetDesktopApp()->UpdateTelemetryHistoricalReports());
}
inline BOOL DoUpdateReport(CONST CTelemetryReportInfo *pReportInfo)
{
	return(GetDesktopApp()->DoUpdateReport(pReportInfo));
}
inline BOOL DoUpdateReport(CONST CTelemetryReportInfo *pReportInfo, CONST CSystemAlertInfo *pAlertInfo)
{
	return(GetDesktopApp()->DoUpdateReport(pReportInfo, pAlertInfo));
}
inline BOOL DoUpdateReport(CONST CTelemetryReportInfo *pReportInfo, CONST CTelemetryEventInfo *pEventInfo)
{
	return(GetDesktopApp()->DoUpdateReport(pReportInfo, pEventInfo));
}
inline BOOL SaveTemporaryDisplays()
{
	return(GetDesktopApp()->SaveTemporaryDisplays());
}
inline BOOL LoadTemporaryDisplays()
{
	return(GetDesktopApp()->LoadTemporaryDisplays());
}
inline BOOL AddTemporaryAND(LPCTSTR pszName, CONST CANDLayout &cLayout)
{
	return(GetDesktopApp()->AddTemporaryAND(pszName, cLayout));
}
inline BOOL AddTemporaryGRD(LPCTSTR pszName, CONST CGRDLayout &cLayout)
{
	return(GetDesktopApp()->AddTemporaryGRD(pszName, cLayout));
}
inline BOOL AddTemporaryPOD(LPCTSTR pszName, CONST CPODLayout &cLayout)
{
	return(GetDesktopApp()->AddTemporaryPOD(pszName, cLayout));
}
inline BOOL LoadTemporaryAND(LPCTSTR pszName, CANDLayout &cLayout)
{
	return(GetDesktopApp()->LoadTemporaryAND(pszName, cLayout));
}
inline BOOL LoadTemporaryGRD(LPCTSTR pszName, CGRDLayout &cLayout)
{
	return(GetDesktopApp()->LoadTemporaryGRD(pszName, cLayout));
}
inline BOOL LoadTemporaryPOD(LPCTSTR pszName, CPODLayout &cLayout)
{
	return(GetDesktopApp()->LoadTemporaryPOD(pszName, cLayout));
}
inline INT EnumTemporaryANDs(CANDLayouts &pLayouts)
{
	return(GetDesktopApp()->EnumTemporaryANDs(pLayouts));
}
inline INT EnumTemporaryGRDs(CGRDLayouts &pLayouts)
{
	return(GetDesktopApp()->EnumTemporaryGRDs(pLayouts));
}
inline INT EnumTemporaryPODs(CPODLayouts &pLayouts)
{
	return(GetDesktopApp()->EnumTemporaryPODs(pLayouts));
}
inline BOOL RemoveTemporaryAND(LPCTSTR pszName)
{
	return(GetDesktopApp()->RemoveTemporaryAND(pszName));
}
inline BOOL RemoveTemporaryGRD(LPCTSTR pszName)
{
	return(GetDesktopApp()->RemoveTemporaryGRD(pszName));
}
inline BOOL RemoveTemporaryPOD(LPCTSTR pszName)
{
	return(GetDesktopApp()->RemoveTemporaryPOD(pszName));
}
inline BOOL InitializeTMUnit(CTMUnit &cTMUnit, BOOL bBadData = FALSE)
{
	return(GetDesktopApp()->InitializeTMUnit(cTMUnit, bBadData));
}
inline BOOL InitializeTMUnit(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData = FALSE)
{
	return(GetDesktopApp()->InitializeTMUnit(pszTag, cTMUnit, bBadData));
}
inline BOOL InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData = FALSE)
{
	return(GetDesktopApp()->InitializeTMData(pTMParameters, bBadData));
}
inline BOOL InitializeTMData(COolParameters &pOolParameters, BOOL bBadData = FALSE)
{
	return(GetDesktopApp()->InitializeTMData(pOolParameters, bBadData));
}
inline BOOL InitializeTMDump(CMemoryDump &pDump, BOOL bBadData = FALSE)
{
	return(GetDesktopApp()->InitializeTMDump(pDump, bBadData));
}
inline BOOL UpdateTMParameters(CONST CTMParameters &pTMParameters)
{
	return(GetDesktopApp()->UpdateTMParameters(pTMParameters));
}
inline VOID UpdateNetworkStatus()
{
	return(GetDesktopApp()->UpdateNetworkStatus());
}
inline VOID UpdateNetworkStatus(LPCTSTR pszServer, RASCONNSTATE nState)
{
	return(GetDesktopApp()->UpdateNetworkStatus(pszServer, nState));
}
inline VOID UpdateTelemetryStatus()
{
	return(GetDesktopApp()->UpdateTelemetryStatus());
}
inline VOID UpdateTelemetryStatus(CONST CTMProviderDevice *pDevice)
{
	return(GetDesktopApp()->UpdateTelemetryStatus(pDevice));
}
inline VOID UpdateTelecommandStatus()
{
	return(GetDesktopApp()->UpdateTelecommandStatus());
}
inline VOID UpdateTelecommandStatus(CONST CTCUplinkDevice *pDevice)
{
	return(GetDesktopApp()->UpdateTelecommandStatus(pDevice));
}
inline VOID UpdateArchivingStatus()
{
	return(GetDesktopApp()->UpdateArchivingStatus());
}
inline VOID UpdateArchivingStatus(LPCTSTR pszArchiveFile, UINT nArchiveFreeSpace, BOOL bArchiveStatus, LPCTSTR pszBackupDirectory, UINT nBackupFreeSpace, BOOL bBackupStatus)
{
	return(GetDesktopApp()->UpdateArchivingStatus(pszArchiveFile, nArchiveFreeSpace, bArchiveStatus, pszBackupDirectory, nBackupFreeSpace, bBackupStatus));
}
inline BOOL InitializeDefaultPrinter()
{
	return(GetDesktopApp()->InitializeDefaultPrinter());
}
inline BOOL IsDefaultPrinterAvailable()
{
	return(GetDesktopApp()->IsDefaultPrinterAvailable());
}
inline BOOL SetDefaultPrinterInfo(CONST PAGESETUPDLG *pPrinterInfo)
{
	return(GetDesktopApp()->SetDefaultPrinterInfo(pPrinterInfo));
}
inline BOOL GetDefaultPrinterInfo(PAGESETUPDLG *pPrinterInfo)
{
	return(GetDesktopApp()->GetDefaultPrinterInfo(pPrinterInfo));
}
inline BOOL CreatePrinterDC(CDC &cDC)
{
	return(GetDesktopApp()->CreatePrinterDC(cDC));
}
inline BOOL CreatePrinterDC(LPCTSTR pszProfile, CDC &cDC)
{
	return(GetDesktopApp()->CreatePrinterDC(pszProfile, cDC));
}
inline BOOL CreatePrinterDC(CPrintProfileInfo *pProfileInfo, CDC &cDC)
{
	return(GetDesktopApp()->CreatePrinterDC(pProfileInfo, cDC));
}
inline BOOL CreatePrinterDC(HANDLE hDevNames, HANDLE hDevMode, CDC &cDC)
{
	return(GetDesktopApp()->CreatePrinterDC(hDevNames, hDevMode, cDC));
}
inline VOID LoginTMService()
{
	return(GetDesktopApp()->LoginTMService());
}
inline VOID LoginTMService(CONST CServerProfileInfo *pServerInfo)
{
	return(GetDesktopApp()->LoginTMService(pServerInfo));
}
inline BOOL IsLogginginTMService()
{
	return(GetDesktopApp()->IsLogginginTMService());
}
inline VOID LogoutTMService()
{
	return(GetDesktopApp()->LogoutTMService());
}
inline BOOL StartRASScheduler()
{
	return(GetDesktopApp()->StartRASScheduler());
}
inline BOOL ScheduleRASService(RASCONNSTATE nState)
{
	return(GetDesktopApp()->ScheduleRASService(nState));
}
inline BOOL StopRASScheduler()
{
	return(GetDesktopApp()->StopRASScheduler());
}
inline BOOL SwitchOperatingMode(LPCTSTR pszMode, BOOL bReport = TRUE)
{
	return(GetDesktopApp()->SwitchOperatingMode(pszMode, bReport));
}
inline BOOL SaveRegistryData(CONST CStringArray &szSubSystems)
{
	return(GetDesktopApp()->SaveRegistryData(szSubSystems));
}
inline BOOL LoadRegistryData(CONST CStringArray &szSubSystems)
{
	return(GetDesktopApp()->LoadRegistryData(szSubSystems));
}
inline BOOL CheckSystemHealth()
{
	return(GetDesktopApp()->CheckSystemHealth());
}
inline BOOL ShowMessage(INT nMessageID)
{
	return(GetDesktopApp()->ShowMessage(nMessageID));
}
inline BOOL ShowMessage(LPCTSTR pszMessage)
{
	return(GetDesktopApp()->ShowMessage(pszMessage));
}
inline BOOL ReportMessage(INT nMessageID)
{
	return(GetDesktopApp()->ReportMessage(nMessageID));
}
inline BOOL ReportEvent(CONST CSystemAlertInfo *pAlertInfo)
{
	return(GetDesktopApp()->ReportEvent(pAlertInfo));
}
inline BOOL ReportEvent(CONST CTelemetryEventInfo *pEventInfo)
{
	return(GetDesktopApp()->ReportEvent(pEventInfo));
}
inline BOOL ReportEvent(UINT nFlags, LPCTSTR pszEvent, BOOL bAudition = TRUE)
{
	return(GetDesktopApp()->ReportEvent(nFlags, pszEvent, bAudition));
}
inline BOOL ReportEvent(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition = TRUE)
{
	return(GetDesktopApp()->ReportEvent(sEvent, bAudition));
}
inline BOOL ReportEvent(CEventObject *pEvent)
{
	return(GetDesktopApp()->ReportEvent(pEvent));
}
inline BOOL ShowProgress(INT nProgress = 0)
{
	return(GetDesktopApp()->ShowProgress(nProgress));
}
inline BOOL ShowHelp(LPCTSTR pszTopic = NULL)
{
	return(GetDesktopApp()->ShowHelp(pszTopic));
}
inline BOOL IsHelpAvailable()
{
	return(GetDesktopApp()->IsHelpAvailable());
}
inline HANDLE GetLogo()
{
	return(GetDesktopApp()->GetLogo());
}
inline VOID ShowWaitCursor()
{
	return(GetDesktopApp()->ShowWaitCursor());
}
inline BOOL IsShowingWaitCursor()
{
	return(GetDesktopApp()->IsShowingWaitCursor());
}
inline VOID StopWaitCursor()
{
	return(GetDesktopApp()->StopWaitCursor());
}
inline CDatabaseEngine *GetDatabase()
{
	return(GetDesktopApp()->GetDatabase());
}
inline CTMService *GetTMService()
{
	return(GetDesktopApp()->GetTMService());
}
inline CTCService *GetTCService()
{
	return(GetDesktopApp()->GetTCService());
}
inline CRASService *GetRASService()
{
	return(GetDesktopApp()->GetRASService());
}
inline CPFLPService *GetPFLPService()
{
	return(GetDesktopApp()->GetPFLPService());
}
inline CTPEPService *GetTPEPService()
{
	return(GetDesktopApp()->GetTPEPService());
}
inline CAutomationService *GetAutomationService()
{
	return(GetDesktopApp()->GetAutomationService());
}
inline CMemoryDumpsService *GetMemoryDumpsService()
{
	return(GetDesktopApp()->GetMemoryDumpsService());
}
inline CNotificationService *GetNotificationService()
{
	return(GetDesktopApp()->GetNotificationService());
}
inline CTelemetryReportsService *GetTelemetryReportsService()
{
	return(GetDesktopApp()->GetTelemetryReportsService());
}
inline CToolsDatabaseService *GetToolsDatabaseService()
{
	return(GetDesktopApp()->GetToolsDatabaseService());
}
inline CToolsDownloadService *GetToolsDownloadService()
{
	return(GetDesktopApp()->GetToolsDownloadService());
}
inline CNetworkBrowseService *GetNetworkBrowseService()
{
	return(GetDesktopApp()->GetNetworkBrowseService());
}
inline CPFLPServiceEngine *GetPFLPServiceSupport()
{
	return(GetDesktopApp()->GetPFLPServiceSupport());
}
inline CTPEPServiceEngine *GetTPEPServiceSupport()
{
	return(GetDesktopApp()->GetTPEPServiceSupport());
}
inline CMemoryDumpsServiceEngine *GetMemoryDumpsServiceSupport()
{
	return(GetDesktopApp()->GetMemoryDumpsServiceSupport());
}
inline CEMailSystem *GetEMailSystem()
{
	return(GetDesktopApp()->GetEMailSystem());
}
inline CDisplayFrame *GetDisplayFrame()
{
	return(GetDesktopApp()->GetDisplayFrame());
}
inline CDisplayArea *GetDisplayArea()
{
	return(GetDesktopApp()->GetDisplayArea());
}
inline CMainWnd *GetMainWnd()
{
	return(GetDesktopApp()->GetMainWnd());
}

/////////////////////////////////////////////////////////////////////////////


#endif // __SATVIEW_H__
