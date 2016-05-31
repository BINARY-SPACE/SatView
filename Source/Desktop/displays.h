// DISPLAYS.H : Displays Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the displays related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/04/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DISPLAYS_H__
#define __DISPLAYS_H__


/////////////////////////////////////////////////////////////////////////////
// CDisplayDialog dialog

class CDisplayDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDisplayDialog)

	// Construction
public:
	CDisplayDialog();   // standard constructor

	// Attributes
private:
	BOOL  m_bModal;

	// Dialog Data
	//{{AFX_DATA(CDisplayDialog)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, UINT nID, BOOL bModal = TRUE);

	class CDisplayWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayPropertySheetDialog

class CDisplayPropertySheetDialog : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CDisplayPropertySheetDialog)

	// Construction
public:
	CDisplayPropertySheetDialog();
	CDisplayPropertySheetDialog(LPCTSTR pszTitle);

	// Attributes
private:
	BOOL  m_bModal;

	// Operations
public:
	INT Create(CWnd *pParentWnd, BOOL bModal = TRUE);

	class CDisplayWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayPropertySheetDialog)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayPropertySheetDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayLockDialog dialog

#define IDC_DISPLAY_LOCK_DETAILS   1001
#define IDC_DISPLAY_LOCK_PASSWORD_STATIC   1002
#define IDC_DISPLAY_LOCK_PASSWORD   1003
#define IDC_DISPLAY_LOCK_CONFIRMATION_STATIC   1004
#define IDC_DISPLAY_LOCK_CONFIRMATION   1005
#define IDC_DISPLAY_LOCK_OWNER   1006
#define IDC_DISPLAY_LOCK_OWNER_NAME_STATIC   1007
#define IDC_DISPLAY_LOCK_OWNER_NAME   1008
#define IDC_DISPLAY_LOCK_OWNER_CONTACT_STATIC   1009
#define IDC_DISPLAY_LOCK_OWNER_CONTACT   1010
#define IDC_DISPLAY_LOCK_OWNER_REASON_STATIC   1011
#define IDC_DISPLAY_LOCK_OWNER_REASON   1012
#define IDC_DISPLAY_LOCK_HELP   1013

class CDisplayLockDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CDisplayLockDialog)

	// Construction
public:
	CDisplayLockDialog();   // standard constructor

	// Attributes
private:
	CString  m_szOwner[2];
	CString  m_szPassword;
	CString  m_szReason;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	// Dialog Data
	//{{AFX_DATA(CDisplayLockDialog)
	enum { IDD = IDD_DISPLAY_LOCK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayLockDialog)
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
	//{{AFX_MSG(CDisplayLockDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeOwner();
	afx_msg void OnEditchangeReason();
	afx_msg void OnEditchangeContact();
	afx_msg void OnEditchangePassword();
	afx_msg void OnEditchangeConfirmation();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnlockDialog dialog

#define IDC_DISPLAY_UNLOCK_DETAILS   1001
#define IDC_DISPLAY_UNLOCK_PASSWORD_STATIC   1002
#define IDC_DISPLAY_UNLOCK_PASSWORD   1003
#define IDC_DISPLAY_UNLOCK_OWNER   1004
#define IDC_DISPLAY_UNLOCK_OWNER_NAME_STATIC   1005
#define IDC_DISPLAY_UNLOCK_OWNER_NAME   1006
#define IDC_DISPLAY_UNLOCK_OWNER_CONTACT_STATIC   1007
#define IDC_DISPLAY_UNLOCK_OWNER_CONTACT   1008
#define IDC_DISPLAY_UNLOCK_OWNER_REASON_STATIC   1009
#define IDC_DISPLAY_UNLOCK_OWNER_REASON   1010
#define IDC_DISPLAY_UNLOCK_HELP   1011

class CDisplayUnlockDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CDisplayUnlockDialog)

	// Construction
public:
	CDisplayUnlockDialog();   // standard constructor

	// Attributes
private:
	CString  m_szPassword;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	// Dialog Data
	//{{AFX_DATA(CDisplayUnlockDialog)
	enum { IDD = IDD_DISPLAY_UNLOCK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayUnlockDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDisplayUnlockDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangePassword();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayLockable

class CDisplayLockable
{
	// Construction
public:
	CDisplayLockable();
	~CDisplayLockable();

	// Attributes
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	CCriticalSection *GetLock() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayLockable)
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayToolBar window

class CDisplayToolBar : public CMFCToolBar, public CDisplayLockable
{
	DECLARE_DYNCREATE(CDisplayToolBar)

	// Construction
public:
	CDisplayToolBar();

	// Attributes
protected:
	CUIntArray  m_nButtonsID;
	CByteArray  m_bButtonsState[4];
protected:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetButtons(CONST UINT *pButtonsID, INT nCount);

	INT CommandToIndex(UINT nButtonID) CONST;

	BOOL EnableButton(INT nButtonID, BOOL bEnable);
	BOOL IsButtonEnabled(INT nButtonID) CONST;
	BOOL CheckButton(INT nButtonID, BOOL bCheck);
	BOOL IsButtonChecked(INT nButtonID) CONST;
	BOOL PressButton(INT nButtonID, BOOL bPress);
	BOOL IsButtonPressed(INT nButtonID) CONST;
	BOOL HideButton(INT nButtonID, BOOL bHide);
	BOOL IsButtonHidden(INT nButtonID) CONST;

	class CDisplayWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayToolBar)
public:
	virtual BOOL LoadToolBar(UINT uiResID, UINT uiColdResID = 0, UINT uiMenuResID = 0, BOOL bLocked = FALSE, UINT uiDisabledResID = 0, UINT uiMenuDisabledResID = 0, UINT uiHotResID = 0);
	virtual BOOL FloatPane(CRect rectFloat, AFX_DOCK_METHOD dockMethod = DM_UNKNOWN, bool bShow = TRUE);
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayToolBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayStatusBar window

class CDisplayStatusBar : public CMFCStatusBar, public CDisplayLockable
{
	DECLARE_DYNCREATE(CDisplayStatusBar)

	// Construction
public:
	CDisplayStatusBar();

	// Attributes
protected:
	CPtrArray  m_prPanes;
	CUIntArray  m_nPanesID;
	CUIntArray  m_nPanesStyle;
	CByteArray  m_bPanesAlertFlag;
	CStringArray  m_szPanesText;
	CFont  m_cPanesFont;
	BOOL  m_bPanesColor;
protected:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pPanesID, INT nCount);

	INT CommandToIndex(UINT nPaneID) CONST;

	BOOL SetPaneText(UINT nPaneID, LPCTSTR pszText, BOOL bAlerted = FALSE);
	BOOL GetPaneText(UINT nPaneID, CString &szText) CONST;
	CString GetPaneText(UINT nPaneID) CONST;

	BOOL EnablePaneColors(BOOL bEnable = TRUE);

	class CDisplayWnd *GetParent() CONST;

protected:
	BOOL DrawPaneText(INT nPane, LPCTSTR pszText);

	INT CalcPaneWidth(LPCTSTR pszText) CONST;
	CRect CalcPaneTextRect(INT nPane) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayStatusBar)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayToolTip window

class CDisplayToolTip : public CWnd, public CDisplayLockable
{
	DECLARE_DYNCREATE(CDisplayToolTip)

	// Construction
public:
	CDisplayToolTip();

	// Attributes
protected:
	CFont  m_cFont[2];
	CPoint  m_ptPosition;
	CString  m_szText;
	CString  m_szTitle;
	CUIntArray  m_nTabs;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST POINT &point, LPCTSTR pszTitle, LPCTSTR pszText);
	BOOL Destroy();

	BOOL SetTitleFont(CFont *pFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL SetTextFont(CFont *pFont);
	BOOL GetTextFont(CFont *pFont) CONST;

	BOOL SetTabstops(CONST CUIntArray &nTabs);
	INT GetTabstops(CUIntArray &nTabs) CONST;

	BOOL SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	BOOL SetText(LPCTSTR pszText);
	CString GetText() CONST;

	VOID Update();
	VOID Update(LPCTSTR pszTitle, LPCTSTR pszText, BOOL bForced = FALSE);

	BOOL IsVisibleAtPoint(CPoint &pt) CONST;

protected:
	VOID CalcTabstops(LPCTSTR pszTitle, LPCTSTR pszText);
	CSize CalcExtent(LPCTSTR pszTitle, LPCTSTR pszText, CPoint &ptTitle, CPoint &ptText);
	CSize CalcMargin();

	VOID DrawContent(CDC *pDC);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayToolTip)

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayToolTip)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd frame

// Specify the display window types
#define DISPLAY_TYPE_NONE   0
#define FIRSTDISPLAYTYPE   1
#define DISPLAY_TYPE_AND   1
#define DISPLAY_TYPE_GRD   2
#define DISPLAY_TYPE_HEX   3
#define DISPLAY_TYPE_MMD   4
#define DISPLAY_TYPE_OOL   5
#define DISPLAY_TYPE_POD   6
#define DISPLAY_TYPE_TPEP   7
#define DISPLAY_TYPE_SATELLITETRACKINGTOOL   8
#define DISPLAY_TYPE_EVENTBOX   9
#define DISPLAY_TYPE_MAILBOX   10
#define DISPLAY_TYPE_LOGBOOK   11
#define DISPLAY_TYPE_TCMANUALSTACK   12
#define DISPLAY_TYPE_TCAUTOMATICSTACK   13
#define DISPLAY_TYPE_TCPROCEDURESMONITOR   14
#define DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP   15
#define DISPLAY_TYPE_TCONBOARDBUFFERQUEUES   16
#define DISPLAY_TYPE_TCONBOARDMEMORYIMAGES   17
#define DISPLAY_TYPE_TCHISTORY   18
#define LASTDISPLAYTYPE   18
// Specify the display window scope
#define DISPLAY_SCOPE_NONE   0
#define DISPLAY_SCOPE_GLOBAL   1
#define DISPLAY_SCOPE_LOCAL   2
// Specify the display window modes
#define DISPLAY_MODE_NONE   0
#define DISPLAY_MODE_REALTIME   1
#define DISPLAY_MODE_HISTORY   2
// Specify the display default sizes
#define DISPLAY_DEFAULT_CX   900
#define DISPLAY_DEFAULT_CY   500

class CDisplayWnd : public CLocaleMDIChildWnd, public CDisplayLockable
{
	DECLARE_DYNAMIC(CDisplayWnd)

	// Construction
public:
	CDisplayWnd();

	// Attributes
protected:
	INT  m_nType;
	INT  m_nScope;
	UINT  m_nMode;
	UINT  m_nShow;
	BOOL  m_bFlag;
	BOOL  m_bRedraw;
protected:
	CString  m_szLink;
	CPtrArray  m_pLinks;
	CDisplayWnd  *m_pLink;
protected:
	CString  m_szOwner[2];
	CString  m_szPassword;
	CString  m_szReason;
protected:
	CDisplayLockDialog  m_dlgLock;
	CDisplayUnlockDialog  m_dlgUnlock;
protected:
	CMDIFrameWnd  *m_pParentWnd;
public:
	typedef struct tagDISPLAYINFO {
		HWND  hWnd;
		RECT  rWnd;
		POINT  ptWnd;
		INT  nNumber;
		INT  nOrder;
		INT  nScope;
		UINT  nMode;
		UINT  nShow;
		BOOL  bShow;
		LPVOID  pData;
	} DISPLAYINFO, *PDISPLAYINFO, *LPDISPLAYINFO;
private:
	typedef struct tagDISPLAYTITLEINFO {
		HWND  hWnd[3];
		LPCTSTR  pszTitle;
		INT  nNumber;
		INT  nCount;
	} DISPLAYTITLEINFO, *PDISPLAYTITLEINFO, *LPDISPLAYTITLEINFO;

	// Operations
public:
	BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, CONST RECT &rect, UINT nResourceID, UINT nStyle = WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW, INT nBkgndColor = COLOR_WINDOW);

	BOOL SetType(INT nType = DISPLAY_TYPE_NONE);
	INT GetType() CONST;
	BOOL SetScope(INT nScope = DISPLAY_SCOPE_NONE);
	INT GetScope() CONST;
	BOOL SetMode(UINT nMode = DISPLAY_MODE_NONE);
	UINT GetMode() CONST;
	BOOL SetState(UINT nShow = SW_SHOWNORMAL);
	UINT GetState() CONST;

	VOID SetLinks(CONST CPtrArray &pLinks);
	INT GetLinks(CPtrArray &pLinks) CONST;
	VOID AddLink(CDisplayWnd *pDisplayWnd);
	BOOL RemoveLink(CDisplayWnd *pDisplayWnd);
	VOID SetLink(CDisplayWnd *pDisplayWnd = NULL);
	CDisplayWnd *GetLink() CONST;
	VOID SetLinkByName(LPCTSTR pszName = NULL);
	CString GetLinkByName() CONST;

	VOID SetLockInformation();
	VOID SetLockInformation(LPCTSTR pszOwner, LPCTSTR pszContact, LPCTSTR pszPassword, LPCTSTR pszReason);
	BOOL GetLockInformation(CString &szOwner, CString &szContact, CString &szPassword, CString &szReason) CONST;

	class CMainWnd *GetParent() CONST;

private:
	CRect CalcMenuItemAlignment(CONST RECT &rMenu, CONST RECT &rItem) CONST;
	BOOL IsLeftToRightMenuItemAlignment() CONST;
	BOOL IsRightToLeftMenuItemAlignment() CONST;

	VOID RedrawLayout(BOOL bRedraw = TRUE);
	BOOL IsRequiringRedraw() CONST;

private:
	static BOOL CALLBACK EnumDisplayWindows(HWND hWnd, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDisplayInfo, BOOL bDefault = TRUE) = 0;
	virtual void RecalcLayout(CDisplayToolBar *pToolBar);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual void ActivateFrame(int nCmdShow = -1);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Initialize(BOOL bFlag);
	virtual BOOL Initialize(CTMEnvironment *pTMEnvironment);
	virtual BOOL Initialize(CString &szTag, CTimeTag &tTag);
	virtual BOOL IsInitialized() CONST;
	virtual BOOL InitializeTMData(UINT nMode);
	virtual BOOL InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData = FALSE);
	virtual BOOL Check() CONST;
	virtual VOID Update();
	virtual BOOL Update(LPVOID pData);
	virtual BOOL Update(LPCTSTR pszMesssage);
	virtual BOOL Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags = 0);
	virtual BOOL Update(CONST CTimeKey &tTimeKey, CTCEnvironment *pTCEnvironment, UINT nFlags = 0);
	virtual VOID Reset(CTMEnvironment *pTMEnvironment = NULL);
	virtual VOID Reset(CTCEnvironment *pTCEnvironment = NULL);
	virtual BOOL Stop();
public:
	virtual BOOL SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo);
	virtual BOOL LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo);
	virtual BOOL DeleteInfo(INT nPage, INT nDisplay);
	virtual BOOL SetLayoutInfo(LPCVOID pData);
	virtual INT GetLayoutInfo(LPVOID *pData = NULL) CONST;
	virtual BOOL QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST = 0;
	virtual BOOL QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST = 0;
	virtual VOID ReduceFonts(BOOL bRestore = FALSE);
	virtual BOOL CanReduceFonts(BOOL bRestore = FALSE) CONST;
	virtual VOID UpdateSysMenu(CMenu *pMenu);
	virtual VOID UpdateBars();
public:
	virtual BOOL Print(PRINTDLG *pPrintInfo = NULL);
	virtual BOOL CanPrint() CONST;
	virtual BOOL IsLinkable() CONST;
	virtual BOOL IsAlerted() CONST;
	virtual VOID DoProtect();
	virtual BOOL CanProtect() CONST;
	virtual BOOL IsProtected() CONST;
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnWindowPosChanging(WINDOWPOS *lpwndpos);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnEnterSizeMove();
	afx_msg void OnExitSizeMove();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated type definitions
typedef CDisplayWnd::DISPLAYINFO  DISPLAYINFO;
typedef CDisplayWnd::DISPLAYINFO  *PDISPLAYINFO;
typedef CDisplayWnd::DISPLAYINFO  *LPDISPLAYINFO;

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayPage window

class CDisplayPage : public CWnd, public CDisplayLockable
{
	DECLARE_DYNCREATE(CDisplayPage)

	// Construction
public:
	CDisplayPage();

	// Attributes
private:
	CPtrList  m_pDisplays;
	CPtrArray  m_pwndDisplays;
	SCROLLINFO  m_sScrollInfo[2];
	CStringArray  m_szUsers;
	CString  m_szPassword;
	UINT  m_nFlags;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	BOOL Initialize();

	BOOL Activate(BOOL bPage = TRUE);
	BOOL Deactivate(BOOL bPage = TRUE);

	BOOL AddDisplay(CDisplayWnd *pDisplayWnd, LPCTSTR pszTitle = NULL, PDISPLAYINFO pDefaultInfo = NULL, BOOL bDefault = TRUE);
	BOOL RemoveDisplay(CDisplayWnd *pDisplayWnd);
	BOOL ActivateDisplay(CDisplayWnd *pDisplayWnd);
	BOOL ActivateDisplay(BOOL bNext = TRUE);
	BOOL ActivateDisplay(UINT nID);
	BOOL IsActiveDisplay(UINT nID) CONST;
	CDisplayWnd *GetActiveDisplay() CONST;
	CDisplayWnd *FindDisplay(INT nType) CONST;
	BOOL CloseDisplay();

	BOOL SaveDisplays(BOOL bAll, INT nPage = -1, INT nMinProgress = 0, INT nMaxProgress = 100);
	BOOL LoadDisplays(BOOL bAll, INT nPage = -1, INT nMinProgress = 0, INT nMaxProgress = 100);
	BOOL StartDisplays(BOOL bAll);
	BOOL StopDisplays(BOOL bAll);
	BOOL CheckDisplays(BOOL bAll) CONST;
	UINT QueryDisplays() CONST;
	VOID UpdateDisplays();
	VOID CloseDisplays(BOOL bAll = FALSE);
	VOID DestroyDisplays(UINT nCode, BOOL bAll);

	BOOL InitializeDisplays(CTMEnvironment *pTMEnvironment, BOOL bReset = FALSE);
	BOOL UpdateDisplays(CTMEnvironment *pTMEnvironment);

	INT EnumDisplays(CPtrArray &pDisplays, BOOL bOrder = FALSE) CONST;

	BOOL SetPassword(LPCTSTR pszPassword);
	BOOL GetPassword(CString &szPassword) CONST;
	BOOL SetUsers(CONST CStringArray &szUsers);
	INT GetUsers(CStringArray &szUsers) CONST;
	BOOL SetBehavior(UINT nFlags);
	BOOL GetBehavior(UINT &nFlags) CONST;

	INT IsAlerted() CONST;

private:
	CDisplayWnd *FindDefaultDisplay(UINT nType) CONST;
	BOOL QueryDefaultDisplayInfo(PDISPLAYINFO pDisplayInfo) CONST;
	BOOL QueryDefaultDisplayInfo(CDisplayWnd *pDisplayWnd, PDISPLAYINFO pDisplayInfo) CONST;

	BOOL IsActivated() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayPage)
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayPage)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayFolderAlertThread thread

// Specify the display folder alert time interval
#define DISPLAYFOLDER_ALERT_INTERVAL   500

class CDisplayFolderAlertThread : public CThread
{
	DECLARE_DYNCREATE(CDisplayFolderAlertThread)

	// Construction
public:
	BOOL Start(class CDisplayFolder *pFolder);
	BOOL Stop();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayFolderAlertThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDisplayFolderAlertThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayFolder window

class CDisplayFolder : public CTabCtrl, public CDisplayLockable
{
	DECLARE_DYNCREATE(CDisplayFolder)

	// Construction
public:
	CDisplayFolder();

	// Attributes
private:
	INT  m_nPage;
	CFont  m_cTabFont;
	CImage  m_cLamps[3];
	CPtrArray  m_prLamps;
	CPtrArray  m_pwndPages;
	CImageList  m_pPageLamps;
	CUIntArray  m_nPageMode;
	CStringArray  m_szPages;
private:
	CBasePane  *m_pPanesBar;
private:
	CDisplayFolderAlertThread  m_cAlertThread;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CBasePane *pBar);

	BOOL AddPage(LPCTSTR pszTitle, INT nPage);
	BOOL ModifyPage(LPCTSTR pszTitle, INT nPage);
	BOOL ActivatePage(INT nPage, BOOL bQuery = TRUE);
	BOOL RemovePage(INT nPage);
	BOOL SetActivePage(INT nPage);
	INT GetActivePage() CONST;
	INT GetPageCount() CONST;

	INT EnumPages(CPtrArray &pwndPages) CONST;
	INT EnumPages(CStringArray &szPages) CONST;

	BOOL AddDisplay(CDisplayWnd *pDisplayWnd, LPCTSTR pszTitle = NULL, PDISPLAYINFO pDefaultInfo = NULL, BOOL bDefault = TRUE);
	BOOL AddDisplay(INT nPage, CDisplayWnd *pDisplayWnd, LPCTSTR pszTitle = NULL, PDISPLAYINFO pDefaultInfo = NULL, BOOL bDefault = TRUE);
	BOOL RemoveDisplay(CDisplayWnd *pDisplayWnd);
	BOOL RemoveDisplay(INT nPage, CDisplayWnd *pDisplayWnd);
	BOOL ActivateDisplay(CDisplayWnd *pDisplayWnd);
	BOOL ActivateDisplay(BOOL bNext = TRUE);
	BOOL ActivateDisplay(UINT nID);
	BOOL IsActiveDisplay(UINT nID) CONST;
	CDisplayWnd *GetActiveDisplay() CONST;
	CDisplayWnd *FindDisplay(INT nType) CONST;
	BOOL CloseDisplay();

	BOOL SaveDisplays(BOOL bAll);
	BOOL LoadDisplays(BOOL bAll);
	BOOL StartDisplays(BOOL bAll);
	BOOL StopDisplays(BOOL bAll);
	BOOL CheckDisplays(BOOL bAll) CONST;
	UINT QueryDisplays() CONST;
	VOID UpdateDisplays();
	VOID CloseDisplays();
	VOID DestroyDisplays(UINT nCode, BOOL bAll);

	BOOL InitializeDisplays(CTMEnvironment *pTMEnvironment, BOOL bReset = FALSE);
	BOOL UpdateDisplays(CTMEnvironment *pTMEnvironment);

	INT EnumDisplays(CPtrArray &pDisplays, BOOL bOrder = FALSE) CONST;
	INT EnumDisplays(INT nPage, CPtrArray &pDisplays, BOOL bOrder = FALSE) CONST;

	BOOL SetPassword(LPCTSTR pszPassword);
	BOOL SetPassword(INT nPage, LPCTSTR pszPassword);
	BOOL GetPassword(CString &szPassword) CONST;
	BOOL GetPassword(INT nPage, CString &szPassword) CONST;
	BOOL SetUsers(CONST CStringArray &szUsers);
	BOOL SetUsers(INT nPage, CONST CStringArray &szUsers);
	INT GetUsers(CStringArray &szUsers) CONST;
	INT GetUsers(INT nPage, CStringArray &szUsers) CONST;
	BOOL SetBehavior(UINT nFlags);
	BOOL SetBehavior(INT nPage, UINT nFlags);
	BOOL GetBehavior(UINT &nFlags) CONST;
	BOOL GetBehavior(INT nPage, UINT &nFlags) CONST;

	VOID UpdateLamps(BOOL bStatus = TRUE);

	VOID RecalcLayout(LPRECT lpRect);

private:
	CDisplayPage *GetPage(INT nPage) CONST;

	INT AccessPage(INT nPage);
	BOOL CheckPage(INT nPage) CONST;

	VOID DrawLamps(CDC *pDC);
	VOID DrawLamp(CDC *pDC, INT nPage);

	VOID RepositionLamps();
	CPoint RecalcLamps();

	BOOL LoadLamps();
	VOID FreeLamps();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayFolder)
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
	//{{AFX_MSG(CDisplayFolder)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayArea window

// Specify the display area types
#define DISPLAYAREA_TYPE_STANDARD   1
#define DISPLAYAREA_TYPE_FOLDER   2

class CDisplayArea : public CWnd, public CDisplayLockable
{
	DECLARE_DYNCREATE(CDisplayArea)

	// Construction
public:
	CDisplayArea();

	// Attributes
private:
	UINT  m_nType;
	BOOL  m_bFrame;
	CRect  m_rFrame;
	CDisplayPage  m_wndPage;
	CDisplayFolder  m_wndFolder;
private:
	CBasePane  *m_pPanesBar;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CBasePane *pBar);

	VOID SetType(UINT nType);
	UINT GetType() CONST;

	BOOL AddPage(LPCTSTR pszTitle, INT nPage);
	BOOL ModifyPage(LPCTSTR pszTitle, INT nPage);
	BOOL ActivatePage(INT nPage);
	BOOL RemovePage(INT nPage);
	INT GetActivePage() CONST;
	INT GetPageCount() CONST;

	INT EnumPages(CStringArray &szPages) CONST;

	BOOL AddDisplay(CDisplayWnd *pDisplayWnd, LPCTSTR pszTitle = NULL, PDISPLAYINFO pDefaultInfo = NULL, BOOL bDefault = TRUE);
	BOOL AddDisplay(INT nPage, CDisplayWnd *pDisplayWnd, LPCTSTR pszTitle = NULL, PDISPLAYINFO pDefaultInfo = NULL, BOOL bDefault = TRUE);
	BOOL RemoveDisplay(CDisplayWnd *pDisplayWnd);
	BOOL RemoveDisplay(INT nPage, CDisplayWnd *pDisplayWnd);
	BOOL ActivateDisplay(CDisplayWnd *pDisplayWnd);
	BOOL ActivateDisplay(BOOL bNext = TRUE);
	BOOL ActivateDisplay(UINT nID);
	BOOL IsActiveDisplay(UINT nID) CONST;
	CDisplayWnd *GetActiveDisplay() CONST;
	CDisplayWnd *FindDisplay(INT nType) CONST;
	BOOL CloseDisplay();

	BOOL SaveDisplays(BOOL bAll);
	BOOL LoadDisplays(BOOL bAll);
	BOOL StartDisplays(BOOL bAll);
	BOOL StopDisplays(BOOL bAll);
	BOOL CheckDisplays(BOOL bAll) CONST;
	UINT QueryDisplays() CONST;
	VOID UpdateDisplays();
	VOID CloseDisplays();
	VOID DestroyDisplays(UINT nCode, BOOL bAll);

	BOOL InitializeDisplays(CTMEnvironment *pTMEnvironment, BOOL bReset = FALSE);
	BOOL UpdateDisplays(CTMEnvironment *pTMEnvironment);

	INT EnumDisplays(CPtrArray &pDisplays, BOOL bOrder = FALSE) CONST;
	INT EnumDisplays(INT nPage, CPtrArray &pDisplays, BOOL bOrder = FALSE) CONST;

	BOOL SetPassword(LPCTSTR pszPassword);
	BOOL SetPassword(INT nPage, LPCTSTR pszPassword);
	BOOL GetPassword(CString &szPassword) CONST;
	BOOL GetPassword(INT nPage, CString &szPassword) CONST;
	BOOL SetUsers(CONST CStringArray &szUsers);
	BOOL SetUsers(INT nPage, CONST CStringArray &szUsers);
	INT GetUsers(CStringArray &szUsers) CONST;
	INT GetUsers(INT nPage, CStringArray &szUsers) CONST;
	BOOL SetBehavior(UINT nFlags);
	BOOL SetBehavior(INT nPage, UINT nFlags);
	BOOL GetBehavior(UINT &nFlags) CONST;
	BOOL GetBehavior(INT nPage, UINT &nFlags) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayArea)
public:
	virtual VOID RecalcLayout(LPRECT pRect = NULL);
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayArea)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnNcDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayFrame window

class CDisplayFrame : public CMDIClientAreaWnd
{
	DECLARE_DYNCREATE(CDisplayFrame)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL Create(class CMainWnd *pParentWnd);
	VOID Destroy(class CMainWnd *pParentWnd);

	BOOL BeginPage(BOOL bPage = TRUE);
	BOOL EndPage(BOOL bPage = TRUE);

	VOID RecalcBars();

	VOID Close();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayFrame)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayFrame)
	afx_msg void OnWindowPosChanging(LPWINDOWPOS lpwndpos);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayLock

class CDisplayLock
{
	// Construction
public:
	CDisplayLock(CONST CDisplayArea *pDisplayArea);
	CDisplayLock(CONST CDisplayFolder *pDisplayFolder);
	CDisplayLock(CONST CDisplayPage *pDisplayPage);
	CDisplayLock(CONST CDisplayWnd *pDisplayWnd);
	CDisplayLock(CONST CDisplayToolBar *pDisplayToolBar);
	CDisplayLock(CONST CDisplayStatusBar *pDisplayStatusBar);
	CDisplayLock(CONST CDisplayToolTip *pDisplayToolTip);
	CDisplayLock(CONST CDisplayLockable *pDisplayLockable);
	~CDisplayLock();

	// Attributes
private:
	CDisplayLockable  *m_pLockable;

	// Operations
public:
	BOOL Release();
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DISPLAYS_H__
