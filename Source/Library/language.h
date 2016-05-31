// LANGUAGE.H : Language Localization Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the language localization related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1994/07/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__


/////////////////////////////////////////////////////////////////////////////
// CLocaleDialog dialog

class AFX_EXT_CLASS CLocaleDialog : public CDialogEx
{
	DECLARE_DYNCREATE(CLocaleDialog)

	// Construction
public:
	CLocaleDialog();
	CLocaleDialog(UINT nDialogID, CWnd *pParentWnd = NULL);
	CLocaleDialog(LPCTSTR pszDialogName, CWnd *pParentWnd = NULL);

	// Attributes
private:
	CPtrArray  m_pCtrls[2];
	CUIntArray  m_nCtrlIDs[2];
	CUIntArray  m_nCtrlPositions;
private:
	HWND  m_hChildSheet;
	HWND  m_hChildWnd;
	HWND  m_hCtrlWnd;

	// Operations
public:
	BOOL Create(UINT nDialogID, CWnd *pParentWnd = NULL);
	BOOL Create(LPCTSTR pszDialogName, CWnd *pParentWnd = NULL);

	CWnd *GetParent() CONST;

protected:
	BOOL AccessControl(UINT nCtrlID, BOOL bAccess, BOOL bVisible = TRUE, BOOL bSelections = TRUE);

	HGLOBAL LoadLocaleDialogTemplate(UINT nDialogID) CONST;
	HGLOBAL LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST;

	BOOL SetChildSheet(CMFCPropertySheet *pSheet, CWnd *pItem);
	CMFCPropertySheet *GetChildSheet() CONST;

private:
	BOOL IsControlOfType(CWnd *pCtrl, CRuntimeClass *pClass) CONST;

	VOID UpdateControlContents(CWnd *pCtrl, CComboBox *pComboBox);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocaleDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLocaleDialog)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd *pWndOther, BOOL bMinimized);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLocalePropertySheetDialog dialog

class AFX_EXT_CLASS CLocalePropertySheetDialog : public CMFCPropertySheet
{
	DECLARE_DYNCREATE(CLocalePropertySheetDialog)

	// Construction
public:
	CLocalePropertySheetDialog();
	CLocalePropertySheetDialog(LPCTSTR pszTitle, CWnd *pParentWnd = NULL);

	// Attributes
private:
	CMFCButton  m_wndButton[3];

	// Operations
public:
	BOOL Create(CWnd *pParentWnd = NULL, DWORD dwStyle = (DWORD)-1, DWORD dwExStyle = 0);

	CWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalePropertySheetDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual VOID RepositionButtons();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CLocalePropertySheetDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLocalePropertyPage dialog

class AFX_EXT_CLASS CLocalePropertyPage : public CMFCPropertyPage
{
	DECLARE_DYNCREATE(CLocalePropertyPage)

	// Construction
public:
	CLocalePropertyPage();
	CLocalePropertyPage(UINT nTemplateID, UINT nCaptionID = 0);
	CLocalePropertyPage(LPCTSTR pszTemplateName, UINT nCaptionID = 0);

	// Attributes
private:
	UINT  m_nCaptionID;
	CPtrArray  m_pCtrls[2];
	CUIntArray  m_nCtrlIDs[2];
	CUIntArray  m_nCtrlPositions;
private:
	HWND  m_hChildSheet;
	HWND  m_hChildWnd;
	HWND  m_hCtrlWnd;

	// Operations
public:
	void Construct(UINT nTemplateID = 0, UINT nCaptionID = 0);
	void Construct(LPCTSTR pszTemplateName, UINT nCaptionID = 0);

	CWnd *GetDlgItem(UINT nCtrlID) CONST;

	CLocalePropertySheetDialog *GetParent() CONST;

protected:
	BOOL AccessControl(UINT nCtrlID, BOOL bAccess, BOOL bVisible = TRUE, BOOL bSelections = TRUE);

	HGLOBAL LoadLocalePropertyPageTemplate(UINT nPropertyPageID) CONST;
	HGLOBAL LoadLocalePropertyPageTemplate(LPCTSTR pszPropertyPageName) CONST;

	BOOL SetChildSheet(CMFCPropertySheet *pSheet, CWnd *pItem);
	CMFCPropertySheet *GetChildSheet() CONST;

private:
	BOOL IsControlOfType(CWnd *pCtrl, CRuntimeClass *pClass) CONST;

	VOID UpdateControlContents(CWnd *pCtrl, CComboBox *pComboBox);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLocalePropertyPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLocalePropertyPage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd *pWndOther, BOOL bMinimized);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLocaleMenu

class AFX_EXT_CLASS CLocaleMenu : public CMenu
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL LoadMenu(UINT nMenuID);
	BOOL LoadMenu(LPCTSTR pszMenuName);

protected:
	HMENU LoadLocaleMenu(LPCTSTR pszMenuName) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLocaleFrameWnd frame

class AFX_EXT_CLASS CLocaleFrameWnd : public CFrameWndEx
{
	DECLARE_DYNCREATE(CLocaleFrameWnd)

	// Construction
public:
	CLocaleFrameWnd();

	// Attributes
protected:
	UINT_PTR  m_nUITimerID;

	// Operations
public:
	BOOL LoadAccelTable(UINT nAccelID);
	BOOL LoadAccelTable(LPCTSTR pszAccelName);

protected:
	HACCEL LoadLocaleAccelTable(LPCTSTR pszAccelName) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocaleFrameWnd)
public:
	virtual BOOL LoadFrame(UINT nResourceID, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd *pParentWnd = NULL, CCreateContext *pContext = NULL);
public:
	virtual VOID DoUpdateUI();
	virtual BOOL CanUpdateUI() CONST;
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLocaleFrameWnd)
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLocaleMDIFrameWnd frame

class AFX_EXT_CLASS CLocaleMDIFrameWnd : public CMDIFrameWndEx
{
	DECLARE_DYNCREATE(CLocaleMDIFrameWnd)

	// Construction
public:
	CLocaleMDIFrameWnd();

	// Attributes
protected:
	UINT_PTR  m_nUITimerID;

	// Operations
public:
	BOOL LoadAccelTable(UINT nAccelID);
	BOOL LoadAccelTable(LPCTSTR pszAccelName);

protected:
	HACCEL LoadLocaleAccelTable(LPCTSTR pszAccelName) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocaleMDIFrameWnd)
public:
	virtual BOOL LoadFrame(UINT nResourceID, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd *pParentWnd = NULL, CCreateContext *pContext = NULL);
public:
	virtual VOID DoUpdateUI();
	virtual BOOL CanUpdateUI() CONST;
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLocaleMDIFrameWnd)
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLocaleMDIChildWnd frame

class AFX_EXT_CLASS CLocaleMDIChildWnd : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CLocaleMDIChildWnd)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL LoadAccelTable(UINT nAccelID);
	BOOL LoadAccelTable(LPCTSTR pszAccelName);

protected:
	HACCEL LoadLocaleAccelTable(LPCTSTR pszAccelName) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocaleMDIChildWnd)
public:
	virtual BOOL LoadFrame(LPCTSTR pszTitle, UINT nResourceID, DWORD dwDefaultStyle, CWnd *pParentWnd, CCreateContext *pContext = NULL);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLocaleMDIChildWnd)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLocaleApp application

class AFX_EXT_CLASS CLocaleApp : public CWinAppEx
{
	DECLARE_DYNAMIC(CLocaleApp)

	// Construction
public:
	CLocaleApp();

	// Attributes
private:
	LANGID  m_nLanguageID;
	LPTSTR  *m_pStringTable;
	LPINT  m_pStringIDTable;
	INT  m_nAppStringOffset;
	INT  m_nAppStringCount;
	INT  m_nStringOffset;
	INT  m_nStringCount;
private:
	CString  m_szHelpFileName;

	// Operations
public:
	CString GetAppTitle() CONST;
	CString GetAppRegID() CONST;
	CString GetAppRegKey() CONST;

	LANGID GetLanguageID() CONST;

	BOOL GetPrinterDeviceDefaults(PRINTDLG *pPrinterInfo);

	CString GetHelpFileName() CONST;

	LPCTSTR GetLibraryModuleName() CONST;
	HINSTANCE GetLibraryModuleInstance() CONST;

public:
	LPCTSTR String(INT nID) CONST;
	TCHAR StringChar(INT nID) CONST;

	INT GetStringOffset(BOOL bLibrary) CONST;

protected:
	BOOL LoadStrings();
	VOID FreeStrings();

	INT SearchString(INT nID) CONST;

	INT GetLocaleData(UINT nDataID, LPVOID pData = NULL, INT cbMax = 0) CONST;
	INT GetLocaleData(LPCTSTR pszDataName, LPVOID pData = NULL, INT cbMax = 0) CONST;

	static BOOL CALLBACK EnumStrings(HINSTANCE hModule, LPCTSTR pszType, LPTSTR pszName, CLocaleApp *pLocaleApp);
	static BOOL CALLBACK EnumLocaleStrings(HINSTANCE hModule, LPCTSTR pszType, LPCTSTR pszName, WORD wLanguageID, CLocaleApp *pLocaleApp);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocaleApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
public:
	virtual BOOL IsIdleMessage(MSG *pMsg);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLocaleApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline CLocaleApp *GetLocaleApp()
{
	return((CLocaleApp *)AfxGetApp());
}
inline CString GetAppTitle()
{
	return(GetLocaleApp()->GetAppTitle());
}
inline CString GetAppRegID()
{
	return(GetLocaleApp()->GetAppRegID());
}
inline CString GetAppRegKey()
{
	return(GetLocaleApp()->GetAppRegKey());
}
inline LANGID GetLanguageID()
{
	return(GetLocaleApp()->GetLanguageID());
}
inline BOOL GetPrinterDeviceDefaults(PRINTDLG *pPrinterInfo)
{
	return(GetLocaleApp()->GetPrinterDeviceDefaults(pPrinterInfo));
}
inline LPCTSTR GetLibraryModuleName()
{
	return(GetLocaleApp()->GetLibraryModuleName());
}
inline HINSTANCE GetLibraryModuleInstance()
{
	return(GetLocaleApp()->GetLibraryModuleInstance());
}
#ifndef LIBRARYENVIRONMENT
#ifndef SPACEENGINEENVIRONMENT
inline LPCTSTR STRING(INT nID)
{
	return(GetLocaleApp()->String(nID));
}
inline TCHAR STRINGCHAR(INT nID)
{
	return(GetLocaleApp()->StringChar(nID));
}
#endif
#endif

/////////////////////////////////////////////////////////////////////////////


#endif // __LANGUAGE_H__
