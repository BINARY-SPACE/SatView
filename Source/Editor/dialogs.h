// DIALOGS.H : Dialogs Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the dialogs related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/02/18 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DIALOGS_H__
#define __DIALOGS_H__


/////////////////////////////////////////////////////////////////////////////
// CWelcomeDialog dialog

#define IDC_WELCOME_SETUP   1001
#define IDC_WELCOME_ICON   1002
#define IDC_WELCOME_TEXT   1003
#define IDC_WELCOME_COMMENT   1004
#define IDC_WELCOME_USERNAME_STATIC   1005
#define IDC_WELCOME_USERNAME   1006
#define IDC_WELCOME_SPACECRAFTNAME_STATIC   1007
#define IDC_WELCOME_SPACECRAFTNAME   1008
#define IDC_WELCOME_PASSWORD_STATIC   1009
#define IDC_WELCOME_PASSWORD   1010
#define IDC_WELCOME_HELP   1011

class CWelcomeDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CWelcomeDialog)

	// Construction
public:
	CWelcomeDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CWelcomeDialog)
	enum { IDD = IDD_WELCOME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcomeDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWelcomeDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeSpacecraftName();
	afx_msg void OnEditchangePassword();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog

#define IDC_LOGIN_DETAILS   1001
#define IDC_LOGIN_SERVERNAME_STATIC   1002
#define IDC_LOGIN_SERVERNAME   1003
#define IDC_LOGIN_SPACECRAFTNAME_STATIC   1004
#define IDC_LOGIN_SPACECRAFTNAME   1005
#define IDC_LOGIN_SPACECRAFTSUPPORT   1006
#define IDC_LOGIN_USERNAME_STATIC   1007
#define IDC_LOGIN_USERNAME   1008
#define IDC_LOGIN_DATABASE   1009
#define IDC_LOGIN_DATABASE_NAME_STATIC  1010
#define IDC_LOGIN_DATABASE_NAME         1011
#define IDC_LOGIN_DATABASE_PASSWORD_STATIC   1012
#define IDC_LOGIN_DATABASE_PASSWORD   1013
#define IDC_LOGIN_HELP   1014

class CLoginDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CLoginDialog)

	// Construction
public:
	CLoginDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseProfiles  m_pDatabases;

	// Dialog Data
	//{{AFX_DATA(CLoginDialog)
	enum { IDD = IDD_LOGIN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumServers();
	BOOL EnumSpacecrafts();
	BOOL EnumDatabases();
	BOOL EnumUsers();

	VOID ShowDatabaseInfo();

	CDatabaseProfileInfo *FindDatabaseInfo() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDialog)
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
	//{{AFX_MSG(CLoginDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSpacecraftSupport();
	afx_msg void OnSelchangeServerName();
	afx_msg void OnSelchangeSpacecraftName();
	afx_msg void OnSelchangeUserName();
	afx_msg void OnSelchangeDatabaseName();
	afx_msg void OnEditchangeDatabasePassword();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CFileBrowseDialog dialog

class CFileBrowseDialog : public CFileDialog
{
	DECLARE_DYNCREATE(CFileBrowseDialog)

	// Construction
public:
	CFileBrowseDialog(CWnd *pParentWnd = NULL, LPCTSTR pszFileName = NULL, LPCTSTR pszDefaultExtension = NULL, LPCTSTR pszFilter = NULL, DWORD dwFlags = OFN_EXPLORER | OFN_HIDEREADONLY);
	CFileBrowseDialog(CWnd *pParentWnd, UINT nCtrlID, LPCTSTR pszDefaultExtension = NULL, LPCTSTR pszFilter = NULL, DWORD dwFlags = OFN_EXPLORER | OFN_HIDEREADONLY);

	// Attributes
private:
	TCHAR  m_szDirectory[MAX_PATH];

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileBrowseDialog)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CFileBrowseDialog)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDefaultPrinter dialog

class CDefaultPrinter : public CPrintDialog
{
	DECLARE_DYNCREATE(CDefaultPrinter)

	// Construction
public:
	CDefaultPrinter();
	~CDefaultPrinter();

	// Attributes
public:

	// Operations
public:
	BOOL Initialize();

	BOOL IsAvailable() CONST;

private:
	VOID Reset();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDefaultPrinter)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CDefaultPrinter)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPrintPageSetupDialog dialog

class CPrintPageSetupDialog : public CPageSetupDialog
{
	DECLARE_DYNCREATE(CPrintPageSetupDialog)

	// Construction
public:
	CPrintPageSetupDialog(CWnd *pParentWnd = NULL, DWORD dwFlags = PSD_MARGINS | PSD_INWININIINTLMEASURE | PSD_NOWARNING);
	~CPrintPageSetupDialog();

	// Operations
private:
	VOID Reset();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintPageSetupDialog)
public:
	virtual INT_PTR DoModal();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPrintPageSetupDialog)
	virtual void OnOK();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPrintPagePrepareDialog dialog

class CPrintPagePrepareDialog : public CPrintDialog
{
	DECLARE_DYNCREATE(CPrintPagePrepareDialog)

	// Construction
public:
	CPrintPagePrepareDialog(CWnd *pParentWnd = NULL, DWORD dwFlags = PD_ALLPAGES | PD_NOSELECTION | PD_USEDEVMODECOPIESANDCOLLATE | PD_HIDEPRINTTOFILE | PD_NOWARNING);
	~CPrintPagePrepareDialog();

	// Attributes
public:

	// Operations
private:
	VOID Reset();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintPagePrepareDialog)
public:
	virtual INT_PTR DoModal();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPrintPagePrepareDialog)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDetailsDialog dialog

#define IDC_DATABASE_DBMS_DETAILS   1001
#define IDC_DATABASE_DBMS_NAME_STATIC   1002
#define IDC_DATABASE_DBMS_NAME   1003
#define IDC_DATABASE_DBMS_PROPERTIES   1004
#define IDC_DATABASE_DBMS_PROPERTIES_FILETYPE   1005
#define IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA   1006
#define IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS   1007
#define IDC_DATABASE_DBMS_PROPERTIES_TABLES   1008
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS   1009
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_FILENAME_STATIC   1010
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_FILENAME   1011
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION_STATIC   1012
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION   1013
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION_BROWSE   1014
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE_STATIC   1015
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE   1016
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE_MB   1017
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_STATIC   1018
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE   1019
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_MB   1020
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED_STATIC   1021
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED   1022
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_STATIC   1023
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE   1024
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_MB   1025
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE_STATIC   1027
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE   1028
#define IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_READONLY   1029
#define IDC_DATABASE_DBMS_HELP   1030

// Specify the database details dialog related settings
#define DETAILSDATABASEDIALOG_MINIMUMINITDATASIZE   8
#define DETAILSDATABASEDIALOG_MAXIMUMINITDATASIZE   256
#define DETAILSDATABASEDIALOG_DEFAULTINITDATASIZE   8
#define DETAILSDATABASEDIALOG_MINIMUMMAXDATASIZE   8
#define DETAILSDATABASEDIALOG_MAXIMUMMAXDATASIZE   1024
#define DETAILSDATABASEDIALOG_DEFAULTMAXDATASIZE   16
#define DETAILSDATABASEDIALOG_MINIMUMGROWDATASIZE   1
#define DETAILSDATABASEDIALOG_MAXIMUMGROWDATASIZE   16
#define DETAILSDATABASEDIALOG_DEFAULTGROWDATASIZE   1
#define DETAILSDATABASEDIALOG_MINIMUMINITLOGSSIZE   1
#define DETAILSDATABASEDIALOG_MAXIMUMINITLOGSSIZE   16
#define DETAILSDATABASEDIALOG_DEFAULTINITLOGSSIZE   2
#define DETAILSDATABASEDIALOG_MINIMUMMAXLOGSSIZE   1
#define DETAILSDATABASEDIALOG_MAXIMUMMAXLOGSSIZE   256
#define DETAILSDATABASEDIALOG_DEFAULTMAXLOGSSIZE   16
#define DETAILSDATABASEDIALOG_MINIMUMGROWLOGSSIZE   1
#define DETAILSDATABASEDIALOG_MAXIMUMGROWLOGSSIZE   4
#define DETAILSDATABASEDIALOG_DEFAULTGROWLOGSSIZE   1

class CDatabaseDetailsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDatabaseDetailsDialog)

	// Construction
public:
	CDatabaseDetailsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szServer;
	CString  m_szDatabase;
	CString  m_szStandard;
	CString  m_szSpacecraft;
	CString  m_szDataFileName[2][2];
	CString  m_szLogsFileName[2][2];
	UINT  m_nDataFileSize[3][2];
	UINT  m_nLogsFileSize[3][2];
	BOOL  m_bReadOnly[2];

	// Dialog Data
	//{{AFX_DATA(CDatabaseDetailsDialog)
	enum { IDD = IDD_DATABASE_DETAILS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID ShowDatabaseInfo();

	CString ConstructDataFileName(LPCTSTR pszDatabase) CONST;
	CString ConstructLogsFileName(LPCTSTR pszDatabase) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseDetailsDialog)
public:
	virtual INT_PTR DoModal(LPCTSTR pszServer, LPCTSTR pszSpacecraft, LPCTSTR pszDatabase, LPCTSTR pszStandard, CString &szDataFileName, CString &szDataFilePath, UINT &nDataFileSize, UINT &nDataFileMaxSize, UINT &nDataFileGrowSize, CString &szLogsFileName, CString &szLogsFilePath, UINT &nLogsFileSize, UINT &nLogsFileMaxSize, UINT &nLogsFileGrowSize, BOOL &bReadOnly);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatabaseDetailsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDataType();
	afx_msg void OnLogsType();
	afx_msg void OnTables();
	afx_msg void OnBrowseLocation();
	afx_msg void OnUnlimitedSize();
	afx_msg void OnFixedSize();
	afx_msg void OnReadOnly();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeLocation();
	afx_msg void OnSpinchangeInitialSize();
	afx_msg void OnSpinchangeMaximalSize();
	afx_msg void OnSpinchangeGrowSize();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesDialog dialog

#define IDC_DATABASE_DBMS_TABLES_DETAILS   1001
#define IDC_DATABASE_DBMS_TABLES_NAME_STATIC   1002
#define IDC_DATABASE_DBMS_TABLES_NAME   1003
#define IDC_DATABASE_DBMS_TABLES_COMPONENT_STATIC   1004
#define IDC_DATABASE_DBMS_TABLES_COMPONENT   1005
#define IDC_DATABASE_DBMS_TABLES_PROPERTIES   1006
#define IDC_DATABASE_DBMS_TABLES_CONTENT   1007
#define IDC_DATABASE_DBMS_TABLES_HELP   1008

class CDatabaseTablesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDatabaseTablesDialog)

	// Construction
public:
	CDatabaseTablesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szDatabase;
	CString  m_szStandard;
	CString  m_szSpacecraft;
	CStringArray  m_szTables;
	CDatabaseEngine  m_cDatabase;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CDatabaseTablesDialog)
	enum { IDD = IDD_DATABASE_TABLES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumTables();

	VOID ShowTableContent();
	VOID ShowTableContent(INT nIndex);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseTablesDialog)
public:
	virtual INT_PTR DoModal(LPCTSTR pszDatabase, LPCTSTR pszStandard, LPCTSTR pszSpacecraft);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatabaseTablesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeTable();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseUsersDialog dialog

#define IDC_DATABASE_USERS_DETAILS   1001
#define IDC_DATABASE_USERS_NAME_STATIC   1002
#define IDC_DATABASE_USERS_NAME   1003
#define IDC_DATABASE_USERS_NAMES_STATIC   1004
#define IDC_DATABASE_USERS_NAMES   1005
#define IDC_DATABASE_USERS_ADD   1006
#define IDC_DATABASE_USERS_VIEW   1007
#define IDC_DATABASE_USERS_CHANGE   1008
#define IDC_DATABASE_USERS_REMOVE   1009
#define IDC_DATABASE_USERS_PERMISSIONS_STATIC   1010
#define IDC_DATABASE_USERS_PERMISSIONS   1011
#define IDC_DATABASE_USERS_HELP   1012

class CDatabaseUsersDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDatabaseUsersDialog)

	// Construction
public:
	CDatabaseUsersDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CStringArray  m_szUsers[2];
	CStringArray  m_szPasswords[2];
	CUIntArray  m_nPrivileges[2];
	BOOL  m_bDatabaseUsers;

	// Dialog Data
	//{{AFX_DATA(CDatabaseUsersDialog)
	enum { IDD = IDD_DATABASE_USERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

private:
	VOID EnumUsers();

	VOID ShowUserInfo();
	VOID ShowUserInfo(LPCTSTR pszUser);

	UINT ConvertToPermission(INT nRight) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseUsersDialog)
public:
	virtual INT_PTR DoModal();
	virtual INT_PTR DoModal(LPCTSTR pszDatabaseName, CStringArray &szUsers, CStringArray &szPasswords, CUIntArray &nPrivileges);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatabaseUsersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAddUser();
	afx_msg void OnViewUser();
	afx_msg void OnChangeUser();
	afx_msg void OnRemoveUser();
	afx_msg void OnSelchangeUser();
	afx_msg void OnEditchangeUser();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabasePrivilegesDialog dialog

#define IDC_DATABASE_PRIVILEGES_DETAILS   1001
#define IDC_DATABASE_PRIVILEGES_USER_STATIC   1002
#define IDC_DATABASE_PRIVILEGES_USER   1003
#define IDC_DATABASE_PRIVILEGES_PASSWORD   1004
#define IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT_STATIC   1005
#define IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT   1006
#define IDC_DATABASE_PRIVILEGES_PASSWORD_TEXTCONFIRMATION_STATIC   1007
#define IDC_DATABASE_PRIVILEGES_PASSWORD_TEXTCONFIRMATION   1008
#define IDC_DATABASE_PRIVILEGES_PERMISSIONS   1009
#define IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST_STATIC   1010
#define IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST   1011
#define IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED_STATIC   1012
#define IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED   1013
#define IDC_DATABASE_PRIVILEGES_PERMISSIONS_ALLOW   1014
#define IDC_DATABASE_PRIVILEGES_PERMISSIONS_DENY   1015
#define IDC_DATABASE_PRIVILEGES_HELP   1016

class CDatabasePrivilegesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDatabasePrivilegesDialog)

	// Construction
public:
	CDatabasePrivilegesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szUserName;
	CString  m_szPassword[2];
	UINT  m_nPrivileges[2];
	BOOL  m_bModify;

	// Dialog Data
	//{{AFX_DATA(CDatabasePrivilegesDialog)
	enum { IDD = IDD_DATABASE_PRIVILEGES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumPrivileges();

	VOID ShowPrivilegeInfo();

	UINT TranslatePermission() CONST;
	UINT TranslatePermission(LPCTSTR pszPermission) CONST;
	CString TranslatePermission(UINT nPermission) CONST;

	UINT ConvertToPermission(INT nRight) CONST;
	INT ConvertToRight(UINT nPermission) CONST;

	BOOL CheckPrivilege(UINT nPrivilege) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabasePrivilegesDialog)
public:
	virtual INT_PTR DoModal();
	virtual INT_PTR DoModal(LPCTSTR pszUserName, CString &szPassword, UINT &nPrivileges, BOOL bAllowModifications = TRUE);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatabasePrivilegesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAllowPermission();
	afx_msg void OnDenyPermission();
	afx_msg void OnSelchangePermission();
	afx_msg void OnSelchangeGrantedPermission();
	afx_msg void OnEditchangePassword();
	afx_msg void OnEditchangePasswordConfirmation();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseValidityDialog dialog

#define IDC_DATABASE_VALIDITY_DETAILS   1001
#define IDC_DATABASE_VALIDITY_NAME_STATIC   1002
#define IDC_DATABASE_VALIDITY_NAME   1003
#define IDC_DATABASE_VALIDITY_NOTE   1004
#define IDC_DATABASE_VALIDITY_NOTE_TEXT   1005
#define IDC_DATABASE_VALIDITY_NOTE_COMMENTS   1006
#define IDC_DATABASE_VALIDITY_INTERVAL   1007
#define IDC_DATABASE_VALIDITY_INTERVAL_UNLIMITED   1008
#define IDC_DATABASE_VALIDITY_INTERVAL_LIMITED   1009
#define IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME   1010
#define IDC_DATABASE_VALIDITY_INTERVAL_LIMITED_STATIC   1011
#define IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME   1012
#define IDC_DATABASE_VALIDITY_HELP   1013

class CDatabaseValidityDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDatabaseValidityDialog)

	// Construction
public:
	CDatabaseValidityDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTimeKey  m_tDatabaseValidity[2][2];
	BOOL  m_bDatabaseValidity;

	// Dialog Data
	//{{AFX_DATA(CDatabaseValidityDialog)
	enum { IDD = IDD_DATABASE_VALIDITY_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID ShowValidityInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseValidityDialog)
public:
	virtual INT_PTR DoModal();
	virtual INT_PTR DoModal(LPCTSTR pszDatabaseName, CTimeKey &tValidityStartTime, CTimeKey &tValidityStopTime);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatabaseValidityDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnUnlimitedValidity();
	afx_msg void OnLimitedValidity();
	afx_msg void OnSpinchangeValidityStartTime();
	afx_msg void OnSpinchangeValidityStopTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CNewDialog dialog

#define IDC_NEW_DOCUMENT_DETAILS   1001
#define IDC_NEW_DOCUMENT_TYPE_STATIC   1002
#define IDC_NEW_DOCUMENT_TYPE   1003
#define IDC_NEW_DOCUMENT_PROPERTIES   1004
#define IDC_NEW_DOCUMENT_PROPERTIES_NAME_STATIC   1005
#define IDC_NEW_DOCUMENT_PROPERTIES_NAME   1006
#define IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT_STATIC   1007
#define IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT   1008
#define IDC_NEW_DOCUMENT_PROPERTIES_SERVER_STATIC   1009
#define IDC_NEW_DOCUMENT_PROPERTIES_SERVER   1010
#define IDC_NEW_DOCUMENT_PROPERTIES_DETAILS   1011
#define IDC_NEW_DOCUMENT_PROPERTIES_USERS   1012
#define IDC_NEW_DOCUMENT_PROPERTIES_VALIDITY   1013
#define IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS   1014
#define IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_SCOPE   1015
#define IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL   1016
#define IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL   1017
#define IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_COMPATIBILITY   1018
#define IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD_STATIC   1019
#define IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD   1020
#define IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_STATIC   1021
#define IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION   1022
#define IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_FLOATINGPOINT   1023
#define IDC_NEW_DOCUMENT_PROPERTIES_FILES   1024
#define IDC_NEW_DOCUMENT_PROPERTIES_FILENAME_STATIC   1025
#define IDC_NEW_DOCUMENT_PROPERTIES_FILENAME   1026
#define IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION_STATIC   1027
#define IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION   1028
#define IDC_NEW_DOCUMENT_PROPERTIES_FILEBROWSE   1029
#define IDC_NEW_DOCUMENT_HELP   1030

class CNewDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CNewDialog)

	// Construction
public:
	CNewDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseProfiles  m_pDatabases;
	CStringArray  m_szDatabaseUsers;
	CStringArray  m_szDatabaseDocuments;
	CStringArray  m_szDatabasePasswords;
	CUIntArray  m_nDatabasePrivileges;
	CTimeKey  m_tDatabaseValidity[2];
	CString  m_szDatabaseDataFile[2];
	CString  m_szDatabaseLogsFile[2];
	UINT  m_nDatabaseDataSize[3];
	UINT  m_nDatabaseLogsSize[3];
	BOOL  m_bDatabaseReadOnly;

	// Dialog Data
	//{{AFX_DATA(CNewDialog)
	enum { IDD = IDD_NEW_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumDatabaseTypes();
	BOOL EnumDatabaseStandard();
	BOOL EnumDatabaseImplementation();
	BOOL EnumDatabaseImplementationFloatingPoint();
	BOOL EnumSpacecrafts();
	BOOL EnumServers();

	VOID ShowDatabaseInfo();

	BOOL SaveDatabases();
	BOOL LoadDatabases();
	BOOL CheckDatabases() CONST;
	BOOL CheckDatabases(LPCTSTR pszSpacecraft) CONST;

	BOOL FindDatabase() CONST;
	BOOL FindDatabase(LPCTSTR pszDatabase, CDatabaseProfileInfo *pDatabaseProfileInfo) CONST;
	BOOL UpdateDatabase(CONST CDatabaseProfileInfo *pDatabaseProfileInfo);

	CString GetDatabaseFileName() CONST;
	CString GetDatabaseUpdateFileName() CONST;
	CString GetDatabaseLibraryFileName() CONST;
	CString GetDatabaseLibraryUpdateFileName() CONST;
	CString GetDatabaseLogFileName() CONST;
	CString ConstructDatabaseFileName(LPCTSTR pszPathName) CONST;
	CString ConstructDatabaseFileLocation(LPCTSTR pszPathName) CONST;

	BOOL CreateTMPacketsForm();
	BOOL CreateTCFunctionsForm();
	BOOL CreateTCSequencesForm();
	BOOL CreateTCProceduresForm();
	BOOL CreateTMParametersForm();
	BOOL CreateTCParametersForm();
	BOOL CreateOBProcessorsForm();
	BOOL CreateAND();
	BOOL CreateGRD();
	BOOL CreateMMD();
	BOOL CreatePOD();
	BOOL CreateScript();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewDialog)
public:
	virtual INT_PTR DoModal();
	virtual INT_PTR DoModal(CONST CStringArray &szDocuments);
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
	//{{AFX_MSG(CNewDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDatabaseDetails();
	afx_msg void OnDatabaseUsers();
	afx_msg void OnDatabaseValidity();
	afx_msg void OnGlobalDatabaseType();
	afx_msg void OnLocalDatabaseType();
	afx_msg void OnBrowse();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeServer();
	afx_msg void OnSelchangeSpacecraft();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeSpacecraft();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeFileLocation();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COpenDialog dialog

#define IDC_OPEN_DOCUMENT_DETAILS   1001
#define IDC_OPEN_DOCUMENT_TYPE_STATIC   1002
#define IDC_OPEN_DOCUMENT_TYPE   1003
#define IDC_OPEN_DOCUMENT_DIRECTORY_STATIC   1004
#define IDC_OPEN_DOCUMENT_DIRECTORY   1005
#define IDC_OPEN_DOCUMENT_HELP   1006

class COpenDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(COpenDialog)

	// Construction
public:
	COpenDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseTMPackets  m_pDatabaseTMPackets;
	CDatabaseTCFunctions  m_pDatabaseTCFunctions;
	CDatabaseTCSequences  m_pDatabaseTCSequences;
	CDatabaseTCProcedures  m_pDatabaseTCProcedures;
	CDatabaseTMParameters  m_pDatabaseTMParameters;
	CDatabaseTCParameters  m_pDatabaseTCParameters;
	CDatabaseOBProcessors  m_pDatabaseOBProcessors;
private:
	CANDLayouts  m_pANDs;
	CGRDLayouts  m_pGRDs;
	CMMDLayouts  m_pMMDs;
	CPODLayouts  m_pPODs;
	CAutomationScripts  m_pScripts;
private:
	CStringArray  m_szDatabaseDocuments;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(COpenDialog)
	enum { IDD = IDD_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumDatabaseTypes();
	BOOL EnumDatabaseDirectory();

	VOID EnumTMPackets();
	VOID EnumTCFunctions();
	VOID EnumTCSequences();
	VOID EnumTCProcedures();
	VOID EnumTMParameters();
	VOID EnumTCParameters();
	VOID EnumOBProcessors();
	VOID EnumANDs();
	VOID EnumGRDs();
	VOID EnumMMDs();
	VOID EnumPODs();
	VOID EnumScripts();

	VOID OpenTMPacket();
	VOID OpenTCFunction();
	VOID OpenTCSequence();
	VOID OpenTCProcedure();
	VOID OpenTMParameter();
	VOID OpenTCParameter();
	VOID OpenOBProcessor();
	VOID OpenAND();
	VOID OpenGRD();
	VOID OpenMMD();
	VOID OpenPOD();
	VOID OpenScript();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenDialog)
public:
	virtual INT_PTR DoModal();
	virtual INT_PTR DoModal(CONST CStringArray &szDocuments);
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeType();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOpenDialog dialog

#define IDC_DATABASE_OPEN_DETAILS   1001
#define IDC_DATABASE_OPEN_SERVER_STATIC   1002
#define IDC_DATABASE_OPEN_SERVER   1003
#define IDC_DATABASE_OPEN_SPACECRAFT_STATIC   1004
#define IDC_DATABASE_OPEN_SPACECRAFT   1005
#define IDC_DATABASE_OPEN_DATABASES   1006
#define IDC_DATABASE_OPEN_DATABASES_LIST   1007
#define IDC_DATABASE_OPEN_CHARACTERISTICS   1008
#define IDC_DATABASE_OPEN_CHARACTERISTICS_SCOPE   1009
#define IDC_DATABASE_OPEN_CHARACTERISTICS_GLOBAL   1010
#define IDC_DATABASE_OPEN_CHARACTERISTICS_LOCAL   1011
#define IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY   1012
#define IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_STANDARD_STATIC   1013
#define IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_STANDARD   1014
#define IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION_STATIC   1015
#define IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION   1016
#define IDC_DATABASE_OPEN_CHARACTERISTICS_OWNER_STATIC   1017
#define IDC_DATABASE_OPEN_CHARACTERISTICS_OWNER   1018
#define IDC_DATABASE_OPEN_CHARACTERISTICS_SERVER_STATIC   1019
#define IDC_DATABASE_OPEN_CHARACTERISTICS_SERVER   1020
#define IDC_DATABASE_OPEN_CHARACTERISTICS_TIME_STATIC   1021
#define IDC_DATABASE_OPEN_CHARACTERISTICS_TIME   1022
#define IDC_DATABASE_OPEN_CHARACTERISTICS_VALIDITY_STATIC   1023
#define IDC_DATABASE_OPEN_CHARACTERISTICS_VALIDITY   1024
#define IDC_DATABASE_OPEN_HELP   1025

class CDatabaseOpenDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDatabaseOpenDialog)

	// Construction
public:
	CDatabaseOpenDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szTime;
	CString  m_szOwner;
	CString  m_szValidity;
	CString  m_szStandard;
	CString  m_szImplementation;
	CDatabaseProfiles  m_pDatabases;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CDatabaseOpenDialog)
	enum { IDD = IDD_DATABASE_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumServers();
	BOOL EnumSpacecrafts();
	BOOL EnumDatabases();

	VOID ShowDatabaseInfo();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseOpenDialog)
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
	//{{AFX_MSG(CDatabaseOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeServer();
	afx_msg void OnSelchangeSpacecraft();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseImportDialog dialog

#define IDC_DATABASE_IMPORT_DETAILS   1001
#define IDC_DATABASE_IMPORT_SERVER_STATIC   1002
#define IDC_DATABASE_IMPORT_SERVER   1003
#define IDC_DATABASE_IMPORT_SPACECRAFT_STATIC   1004
#define IDC_DATABASE_IMPORT_SPACECRAFT   1005
#define IDC_DATABASE_IMPORT_NAME_STATIC   1006
#define IDC_DATABASE_IMPORT_NAME   1007
#define IDC_DATABASE_IMPORT_DATAONLY   1008
#define IDC_DATABASE_IMPORT_DATAFILES   1009
#define IDC_DATABASE_IMPORT_LOCATION_STATIC   1010
#define IDC_DATABASE_IMPORT_LOCATION   1011
#define IDC_DATABASE_IMPORT_LOCATION_BROWSE   1012
#define IDC_DATABASE_IMPORT_FILEPREFIX_STATIC   1013
#define IDC_DATABASE_IMPORT_FILEPREFIX   1014
#define IDC_DATABASE_IMPORT_FILEEXTENSION_STATIC   1015
#define IDC_DATABASE_IMPORT_FILEEXTENSION   1016
#define IDC_DATABASE_IMPORT_FORMAT   1017
#define IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER_STATIC   1018
#define IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER   1019
#define IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER_STATIC   1020
#define IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER   1021
#define IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER_STATIC   1022
#define IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER   1023
#define IDC_DATABASE_IMPORT_DESTINATION   1024
#define IDC_DATABASE_IMPORT_DESTINATION_SCOPE_STATIC   1025
#define IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL   1026
#define IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL   1027
#define IDC_DATABASE_IMPORT_DESTINATION_DATABASE_STATIC   1028
#define IDC_DATABASE_IMPORT_DESTINATION_DATABASE   1029
#define IDC_DATABASE_IMPORT_DESTINATION_DETAILS   1030
#define IDC_DATABASE_IMPORT_DESTINATION_USERS   1031
#define IDC_DATABASE_IMPORT_DESTINATION_VALIDITY   1032
#define IDC_DATABASE_IMPORT_DESTINATION_LOCATION_STATIC   1033
#define IDC_DATABASE_IMPORT_DESTINATION_LOCATION   1034
#define IDC_DATABASE_IMPORT_DESTINATION_LOCATION_BROWSE   1035
#define IDC_DATABASE_IMPORT_DESTINATION_INFO_OWNER_STATIC   1036
#define IDC_DATABASE_IMPORT_DESTINATION_INFO_OWNER   1037
#define IDC_DATABASE_IMPORT_DESTINATION_INFO_TIME_STATIC   1038
#define IDC_DATABASE_IMPORT_DESTINATION_INFO_TIME   1039
#define IDC_DATABASE_IMPORT_DESTINATION_INFO_VALIDITY_STATIC   1040
#define IDC_DATABASE_IMPORT_DESTINATION_INFO_VALIDITY   1041
#define IDC_DATABASE_IMPORT_HELP   1042

class CDatabaseImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDatabaseImportDialog)

	// Construction
public:
	CDatabaseImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseProfiles  m_pDatabases[2];
	CStringArray  m_szDatabaseUsers[2];
	CUIntArray  m_nDatabasePrivileges;
	CTimeKey  m_tDatabaseValidity[2];
	CString  m_szDatabaseDataFile[2];
	CString  m_szDatabaseLogsFile[2];
	UINT  m_nDatabaseDataSize[3];
	UINT  m_nDatabaseLogsSize[3];
	BOOL  m_bDatabaseReadOnly;

	// Dialog Data
	//{{AFX_DATA(CDatabaseImportDialog)
	enum { IDD = IDD_DATABASE_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumServers();
	BOOL EnumSpacecrafts();
	BOOL EnumDatabases();
	VOID EnumStringDelimiters();
	VOID EnumFieldDelimiters();
	VOID EnumRowDelimiters();

	VOID ShowDatabaseInfo();

	BOOL SaveDatabases();
	BOOL LoadDatabases();

	CString GetDatabaseFileName() CONST;
	CString GetDatabaseUpdateFileName() CONST;
	CString GetDatabaseLibraryFileName() CONST;
	CString GetDatabaseLibraryUpdateFileName() CONST;
	CString GetDatabaseLogFileName() CONST;
	CString ConstructDatabaseFileName(LPCTSTR pszPathName) CONST;
	CString ConstructDatabaseFileLocation(LPCTSTR pszPathName) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseImportDialog)
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
	//{{AFX_MSG(CDatabaseImportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnImportDataOnly();
	afx_msg void OnImportDataFiles();
	afx_msg void OnDataFilesBrowse();
	afx_msg void OnDatabaseDetails();
	afx_msg void OnDatabaseUsers();
	afx_msg void OnDatabaseValidity();
	afx_msg void OnLocationBrowse();
	afx_msg void OnEditchangeDataFilesLocation();
	afx_msg void OnEditchangeDestinationDatabase();
	afx_msg void OnEditchangeDestinationDatabaseLocation();
	afx_msg void OnSelchangeServer();
	afx_msg void OnSelchangeSpacecraft();
	afx_msg void OnSelchangeDatabase();
	afx_msg void OnSelchangeDataFilesStringDelimiter();
	afx_msg void OnSelchangeDataFilesFieldDelimiter();
	afx_msg void OnSelchangeDataFilesRowDelimiter();
	afx_msg void OnSelchangeDestinationDatabase();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseExportDialog dialog

#define IDC_DATABASE_EXPORT_DETAILS   1001
#define IDC_DATABASE_EXPORT_SERVER_STATIC   1002
#define IDC_DATABASE_EXPORT_SERVER   1003
#define IDC_DATABASE_EXPORT_SPACECRAFT_STATIC   1004
#define IDC_DATABASE_EXPORT_SPACECRAFT   1005
#define IDC_DATABASE_EXPORT_NAME_STATIC   1006
#define IDC_DATABASE_EXPORT_NAME   1007
#define IDC_DATABASE_EXPORT_DIRECTIVES_STATIC   1008
#define IDC_DATABASE_EXPORT_DIRECTIVES_COMPLETE   1009
#define IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTS   1010
#define IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST   1011
#define IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_ADD   1012
#define IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVE   1013
#define IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVEALL   1014
#define IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL   1015
#define IDC_DATABASE_EXPORT_DESTINATION   1016
#define IDC_DATABASE_EXPORT_DESTINATION_LOCATION_STATIC   1017
#define IDC_DATABASE_EXPORT_DESTINATION_LOCATION   1018
#define IDC_DATABASE_EXPORT_DESTINATION_LOCATION_BROWSE   1019
#define IDC_DATABASE_EXPORT_DESTINATION_FILEPREFIX_STATIC   1020
#define IDC_DATABASE_EXPORT_DESTINATION_FILEPREFIX   1021
#define IDC_DATABASE_EXPORT_DESTINATION_FILEEXTENSION_STATIC   1022
#define IDC_DATABASE_EXPORT_DESTINATION_FILEEXTENSION   1023
#define IDC_DATABASE_EXPORT_FORMAT   1024
#define IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER_STATIC   1025
#define IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER   1026
#define IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER_STATIC   1027
#define IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER   1028
#define IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER_STATIC   1029
#define IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER   1030
#define IDC_DATABASE_EXPORT_FORMAT_UNICODE   1031
#define IDC_DATABASE_EXPORT_HELP   1032

class CDatabaseExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDatabaseExportDialog)

	// Construction
public:
	CDatabaseExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseProfiles  m_pDatabases;

	// Dialog Data
	//{{AFX_DATA(CDatabaseExportDialog)
	enum { IDD = IDD_DATABASE_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumServers();
	BOOL EnumSpacecrafts();
	BOOL EnumDatabases();
	BOOL EnumStringDelimiters();
	BOOL EnumFieldDelimiters();
	BOOL EnumRowDelimiters();

	VOID ShowDatabaseInfo();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseExportDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatabaseExportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnExportComplete();
	afx_msg void OnExportComponents();
	afx_msg void OnAddComponent();
	afx_msg void OnRemoveComponent();
	afx_msg void OnRemoveAllComponents();
	afx_msg void OnLocationBrowse();
	afx_msg void OnEditchangeDataFilesLocation();
	afx_msg void OnSelchangeServer();
	afx_msg void OnSelchangeSpacecraft();
	afx_msg void OnSelchangeDatabase();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDeleteDialog dialog

#define IDC_DATABASE_DELETE_DETAILS   1001
#define IDC_DATABASE_DELETE_SERVER_STATIC   1002
#define IDC_DATABASE_DELETE_SERVER   1003
#define IDC_DATABASE_DELETE_SPACECRAFT_STATIC   1004
#define IDC_DATABASE_DELETE_SPACECRAFT   1005
#define IDC_DATABASE_DELETE_DATABASES_STATIC   1006
#define IDC_DATABASE_DELETE_DATABASES   1007
#define IDC_DATABASE_DELETE_CHARACTERISTICS   1008
#define IDC_DATABASE_DELETE_CHARACTERISTICS_SCOPE   1009
#define IDC_DATABASE_DELETE_CHARACTERISTICS_GLOBAL   1010
#define IDC_DATABASE_DELETE_CHARACTERISTICS_LOCAL   1011
#define IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY   1012
#define IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_STANDARD_STATIC   1013
#define IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_STANDARD   1014
#define IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION_STATIC   1015
#define IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION   1016
#define IDC_DATABASE_DELETE_CHARACTERISTICS_OWNER_STATIC   1017
#define IDC_DATABASE_DELETE_CHARACTERISTICS_OWNER   1018
#define IDC_DATABASE_DELETE_CHARACTERISTICS_SERVER_STATIC   1019
#define IDC_DATABASE_DELETE_CHARACTERISTICS_SERVER   1020
#define IDC_DATABASE_DELETE_CHARACTERISTICS_TIME_STATIC   1021
#define IDC_DATABASE_DELETE_CHARACTERISTICS_TIME   1022
#define IDC_DATABASE_DELETE_CHARACTERISTICS_VALIDITY_STATIC   1023
#define IDC_DATABASE_DELETE_CHARACTERISTICS_VALIDITY   1024
#define IDC_DATABASE_DELETE_HELP   1025

class CDatabaseDeleteDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDatabaseDeleteDialog)

	// Construction
public:
	CDatabaseDeleteDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szTime;
	CString  m_szOwner;
	CString  m_szValidity;
	CString  m_szStandard;
	CString  m_szImplementation;
	CTimeKey  m_tDatabaseValidity[2];
	CDatabaseProfiles  m_pDatabases;

	// Dialog Data
	//{{AFX_DATA(CDatabaseDeleteDialog)
	enum { IDD = IDD_DATABASE_DELETE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumServers();
	BOOL EnumSpacecrafts();
	BOOL EnumDatabases();

	VOID ShowDatabaseInfo();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseDeleteDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatabaseDeleteDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeServer();
	afx_msg void OnSelchangeSpacecraft();
	afx_msg void OnSelchangeDatabase();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseVersioningDialog dialog

#define IDC_DATABASE_VERSIONING_DETAILS   1001
#define IDC_DATABASE_VERSIONING_SERVER_STATIC   1002
#define IDC_DATABASE_VERSIONING_SERVER   1003
#define IDC_DATABASE_VERSIONING_SPACECRAFT_STATIC   1004
#define IDC_DATABASE_VERSIONING_SPACECRAFT   1005
#define IDC_DATABASE_VERSIONING_DATABASE_STATIC   1006
#define IDC_DATABASE_VERSIONING_DATABASE   1007
#define IDC_DATABASE_VERSIONING_HISTORY   1008
#define IDC_DATABASE_VERSIONING_HISTORY_SUMMARY   1009
#define IDC_DATABASE_VERSIONING_HISTORY_NAME_STATIC   1010
#define IDC_DATABASE_VERSIONING_HISTORY_NAME   1011
#define IDC_DATABASE_VERSIONING_HISTORY_RELEASE_STATIC   1012
#define IDC_DATABASE_VERSIONING_HISTORY_RELEASE   1013
#define IDC_DATABASE_VERSIONING_HISTORY_ISSUE_STATIC   1014
#define IDC_DATABASE_VERSIONING_HISTORY_ISSUE   1015
#define IDC_DATABASE_VERSIONING_HISTORY_COMMENT_STATIC   1016
#define IDC_DATABASE_VERSIONING_HISTORY_COMMENT   1017
#define IDC_DATABASE_VERSIONING_HISTORY_ADD   1018
#define IDC_DATABASE_VERSIONING_HISTORY_MODIFY   1019
#define IDC_DATABASE_VERSIONING_HISTORY_REMOVE   1020
#define IDC_DATABASE_VERSIONING_HELP   1021

class CDatabaseVersioningDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDatabaseVersioningDialog)

	// Construction
public:
	CDatabaseVersioningDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseVersions  m_pDatabaseVersions[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CDatabaseVersioningDialog)
	enum { IDD = IDD_DATABASE_VERSIONING_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumVersionHistory(INT nIndex = -1);

	VOID ShowVersionInfo();

	BOOL CanAddVersion() CONST;
	BOOL CanModifyVersion() CONST;
	BOOL CanRemoveVersion() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseVersioningDialog)
public:
	virtual BOOL Initialize();
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
	//{{AFX_MSG(CDatabaseVersioningDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddVersion();
	afx_msg void OnModifyVersion();
	afx_msg void OnRemoveVersion();
	afx_msg void OnEditchangeVersion();
	afx_msg void OnEditchangeRelease();
	afx_msg void OnEditchangeIssue();
	afx_msg void OnEditchangeComment();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTMPacketsPage dialog

#define IDC_DATABASE_FIND_TMPACKETSPAGE_DETAILS   1001
#define IDC_DATABASE_FIND_TMPACKETSPAGE_APID_STATIC   1002
#define IDC_DATABASE_FIND_TMPACKETSPAGE_APID   1003
#define IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY_STATIC   1004
#define IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY   1005
#define IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION_STATIC   1006
#define IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION   1007
#define IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1_STATIC   1008
#define IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1   1009
#define IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2_STATIC   1010
#define IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2   1011
#define IDC_DATABASE_FIND_TMPACKETSPAGE_RESULTS_STATIC   1012
#define IDC_DATABASE_FIND_TMPACKETSPAGE_RESULTS_PANE1   1013
#define IDC_DATABASE_FIND_TMPACKETSPAGE_RESULTS_PANE2   1014

class CDatabaseFindTMPacketsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CDatabaseFindTMPacketsPage)

	// Construction
public:
	CDatabaseFindTMPacketsPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CDatabaseFindTMPacketsPage)
	enum { IDD = IDD_DATABASE_FIND_TMPACKETSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID Search();

private:
	BOOL EnumAPIDs();
	BOOL EnumTMTYs();
	BOOL EnumParameters();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindTMPacketsPage)
public:
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatabaseFindTMPacketsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAPID();
	afx_msg void OnTMTY();
	afx_msg void OnDescription();
	afx_msg void OnParameter1();
	afx_msg void OnParameter2();
	afx_msg void OnSelchangeAPID();
	afx_msg void OnSelchangeTMTY();
	afx_msg void OnSelchangeParameter1();
	afx_msg void OnSelchangeParameter2();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeParameter1();
	afx_msg void OnEditchangeParameter2();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTCFunctionsPage dialog

#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DETAILS   1001
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE_STATIC   1002
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE   1003
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION_STATIC   1004
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION   1005
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET_STATIC   1006
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET   1007
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1_STATIC   1008
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1   1009
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2_STATIC   1010
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2   1011
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_RESULTS_STATIC   1012
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_RESULTS_PANE1   1013
#define IDC_DATABASE_FIND_TCFUNCTIONSPAGE_RESULTS_PANE2   1014

class CDatabaseFindTCFunctionsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CDatabaseFindTCFunctionsPage)

	// Construction
public:
	CDatabaseFindTCFunctionsPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CDatabaseFindTCFunctionsPage)
	enum { IDD = IDD_DATABASE_FIND_TCFUNCTIONSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID Search();

private:
	BOOL EnumTypes();
	BOOL EnumPackets();
	BOOL EnumParameters();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindTCFunctionsPage)
public:
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatabaseFindTCFunctionsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnType();
	afx_msg void OnDescription();
	afx_msg void OnPacket();
	afx_msg void OnParameter1();
	afx_msg void OnParameter2();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangePacket();
	afx_msg void OnSelchangeParameter1();
	afx_msg void OnSelchangeParameter2();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangePacket();
	afx_msg void OnEditchangeParameter1();
	afx_msg void OnEditchangeParameter2();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTMParametersPage dialog

#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_DETAILS   1001
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE_STATIC   1002
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE   1003
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING_STATIC   1004
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING   1005
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH_STATIC   1006
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH   1007
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION_STATIC   1008
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION   1009
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE_STATIC   1010
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE   1011
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE_STATIC   1012
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE   1013
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_RESULTS_STATIC   1014
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_RESULTS_PANE1   1015
#define IDC_DATABASE_FIND_TMPARAMETERSPAGE_RESULTS_PANE2   1016

class CDatabaseFindTMParametersPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CDatabaseFindTMParametersPage)

	// Construction
public:
	CDatabaseFindTMParametersPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CDatabaseFindTMParametersPage)
	enum { IDD = IDD_DATABASE_FIND_TMPARAMETERSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID Search();

private:
	BOOL EnumTypes();
	BOOL EnumCodings();
	BOOL EnumCalibrations();
	BOOL EnumCalTables();
	BOOL EnumOolTables();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindTMParametersPage)
public:
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatabaseFindTMParametersPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnType();
	afx_msg void OnCoding();
	afx_msg void OnWidth();
	afx_msg void OnCalibration();
	afx_msg void OnCalTable();
	afx_msg void OnOolTable();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeCoding();
	afx_msg void OnSelchangeCalibration();
	afx_msg void OnSelchangeCalTable();
	afx_msg void OnSelchangeOolTable();
	afx_msg void OnSpinchangeWidth();
	afx_msg void OnEditchangeCalTable();
	afx_msg void OnEditchangeOolTable();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTCParametersPage dialog

#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_DETAILS   1001
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION_STATIC   1002
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION   1003
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING_STATIC   1004
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING   1005
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH_STATIC   1006
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH   1007
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION_STATIC   1008
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION   1009
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE_STATIC   1010
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE   1011
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE_STATIC   1012
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE   1013
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_RESULTS_STATIC   1014
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_RESULTS_PANE1   1015
#define IDC_DATABASE_FIND_TCPARAMETERSPAGE_RESULTS_PANE2   1016

class CDatabaseFindTCParametersPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CDatabaseFindTCParametersPage)

	// Construction
public:
	CDatabaseFindTCParametersPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CDatabaseFindTCParametersPage)
	enum { IDD = IDD_DATABASE_FIND_TCPARAMETERSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID Search();

private:
	BOOL EnumCodings();
	BOOL EnumCalibrations();
	BOOL EnumCalTables();
	BOOL EnumOolTables();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindTCParametersPage)
public:
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatabaseFindTCParametersPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDescription();
	afx_msg void OnCoding();
	afx_msg void OnWidth();
	afx_msg void OnCalibration();
	afx_msg void OnCalTable();
	afx_msg void OnOolTable();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnSelchangeCoding();
	afx_msg void OnSelchangeCalibration();
	afx_msg void OnSelchangeCalTable();
	afx_msg void OnSelchangeOolTable();
	afx_msg void OnSpinchangeWidth();
	afx_msg void OnEditchangeCalTable();
	afx_msg void OnEditchangeOolTable();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindOBProcessorsPage dialog

#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_DETAILS   1001
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND   1002
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND_NAME   1003
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND   1004
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND_NAME   1005
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET   1006
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET_TAG   1007
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE   1008
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE_NAME   1009
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS   1010
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE   1011
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_SYMBOL_STATIC   1012
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET   1013
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_RADIX_STATIC   1014
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_RESULTS_STATIC   1015
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_RESULTS_PANE1   1016
#define IDC_DATABASE_FIND_OBPROCESSORSPAGE_RESULTS_PANE2   1017

class CDatabaseFindOBProcessorsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CDatabaseFindOBProcessorsPage)

	// Construction
public:
	CDatabaseFindOBProcessorsPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CDatabaseFindOBProcessorsPage)
	enum { IDD = IDD_DATABASE_FIND_OBPROCESSORSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID Search();

private:
	BOOL EnumPatchCommands();
	BOOL EnumDumpCommands();
	BOOL EnumDumpPackets();
	BOOL EnumMasterImages();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindOBProcessorsPage)
public:
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatabaseFindOBProcessorsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPatchCommand();
	afx_msg void OnDumpCommand();
	afx_msg void OnDumpPacket();
	afx_msg void OnMasterImage();
	afx_msg void OnAddress();
	afx_msg void OnSelchangePatchCommand();
	afx_msg void OnSelchangeDumpCommand();
	afx_msg void OnSelchangeDumpPacket();
	afx_msg void OnSelchangeMasterImage();
	afx_msg void OnEditchangeAddressPage();
	afx_msg void OnEditchangeAddressOffset();
	afx_msg void OnEditupdateAddressPage();
	afx_msg void OnEditupdateAddressOffset();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindANDsPage dialog

#define IDC_DATABASE_FIND_ANDSPAGE_DETAILS   1001
#define IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION_STATIC   1002
#define IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION   1003
#define IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1_STATIC   1004
#define IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1   1005
#define IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2_STATIC   1006
#define IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2   1007
#define IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3_STATIC   1008
#define IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3   1009
#define IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4_STATIC   1010
#define IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4   1011
#define IDC_DATABASE_FIND_ANDSPAGE_RESULTS_STATIC   1012
#define IDC_DATABASE_FIND_ANDSPAGE_RESULTS_PANE1   1013
#define IDC_DATABASE_FIND_ANDSPAGE_RESULTS_PANE2   1014

class CDatabaseFindANDsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CDatabaseFindANDsPage)

	// Construction
public:
	CDatabaseFindANDsPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CDatabaseFindANDsPage)
	enum { IDD = IDD_DATABASE_FIND_ANDSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID Search();

private:
	BOOL EnumParameters();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindANDsPage)
public:
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatabaseFindANDsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDescription();
	afx_msg void OnParameter1();
	afx_msg void OnParameter2();
	afx_msg void OnParameter3();
	afx_msg void OnParameter4();
	afx_msg void OnSelchangeParameter1();
	afx_msg void OnSelchangeParameter2();
	afx_msg void OnSelchangeParameter3();
	afx_msg void OnSelchangeParameter4();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeParameter1();
	afx_msg void OnEditchangeParameter2();
	afx_msg void OnEditchangeParameter3();
	afx_msg void OnEditchangeParameter4();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindGRDsPage dialog

#define IDC_DATABASE_FIND_GRDSPAGE_DETAILS   1001
#define IDC_DATABASE_FIND_GRDSPAGE_TYPE_STATIC   1002
#define IDC_DATABASE_FIND_GRDSPAGE_TYPE   1003
#define IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE_STATIC   1004
#define IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE   1005
#define IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION_STATIC   1006
#define IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION   1007
#define IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1_STATIC   1008
#define IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1   1009
#define IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2_STATIC   1010
#define IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2   1011
#define IDC_DATABASE_FIND_GRDSPAGE_RESULTS_STATIC   1012
#define IDC_DATABASE_FIND_GRDSPAGE_RESULTS_PANE1   1013
#define IDC_DATABASE_FIND_GRDSPAGE_RESULTS_PANE2   1014

class CDatabaseFindGRDsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CDatabaseFindGRDsPage)

	// Construction
public:
	CDatabaseFindGRDsPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CDatabaseFindGRDsPage)
	enum { IDD = IDD_DATABASE_FIND_GRDSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID Search();

private:
	BOOL EnumTypes();
	BOOL EnumPlottingModes();
	BOOL EnumParameters();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindGRDsPage)
public:
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatabaseFindGRDsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnType();
	afx_msg void OnPlottingMode();
	afx_msg void OnDescription();
	afx_msg void OnParameter1();
	afx_msg void OnParameter2();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangePlottingMode();
	afx_msg void OnSelchangeParameter1();
	afx_msg void OnSelchangeParameter2();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeParameter1();
	afx_msg void OnEditchangeParameter2();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindPODsPage dialog

#define IDC_DATABASE_FIND_PODSPAGE_DETAILS   1001
#define IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION_STATIC   1002
#define IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION   1003
#define IDC_DATABASE_FIND_PODSPAGE_STACK_STATIC   1004
#define IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1_STATIC   1005
#define IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1   1006
#define IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2_STATIC   1007
#define IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2   1008
#define IDC_DATABASE_FIND_PODSPAGE_ASSOCIATED_STATIC   1009
#define IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER_STATIC   1010
#define IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER   1011
#define IDC_DATABASE_FIND_PODSPAGE_RESULTS_STATIC   1014
#define IDC_DATABASE_FIND_PODSPAGE_RESULTS_PANE1   1015
#define IDC_DATABASE_FIND_PODSPAGE_RESULTS_PANE2   1016

class CDatabaseFindPODsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CDatabaseFindPODsPage)

	// Construction
public:
	CDatabaseFindPODsPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CDatabaseFindPODsPage)
	enum { IDD = IDD_DATABASE_FIND_PODSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID Search();

private:
	BOOL EnumParameters();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindPODsPage)
public:
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatabaseFindPODsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDescription();
	afx_msg void OnStackParameter1();
	afx_msg void OnStackParameter2();
	afx_msg void OnAssociatedParameter();
	afx_msg void OnSelchangeStackParameter1();
	afx_msg void OnSelchangeStackParameter2();
	afx_msg void OnSelchangeAssociatedParameter();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeStackParameter1();
	afx_msg void OnEditchangeStackParameter2();
	afx_msg void OnEditchangeAssociatedParameter();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindDBMSPage dialog

#define IDC_DATABASE_FIND_DBMSPAGE_DETAILS   1001
#define IDC_DATABASE_FIND_DBMSPAGE_QUERY_STATIC   1002
#define IDC_DATABASE_FIND_DBMSPAGE_QUERY   1003
#define IDC_DATABASE_FIND_DBMSPAGE_RESULTS_STATIC   1004
#define IDC_DATABASE_FIND_DBMSPAGE_RESULTS_PANE1   1005
#define IDC_DATABASE_FIND_DBMSPAGE_RESULTS_PANE2   1006
#define IDC_DATABASE_FIND_DBMSPAGE_QUERYTEXT_STATIC   1007
#define IDC_DATABASE_FIND_DBMSPAGE_QUERYTEXT_PANE1   1008
#define IDC_DATABASE_FIND_DBMSPAGE_QUERYTEXT_PANE2   1009

class CDatabaseFindDBMSPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CDatabaseFindDBMSPage)

	// Construction
public:
	CDatabaseFindDBMSPage();

	// Attributes
private:
	CString  m_szQuery;

	// Dialog Data
	//{{AFX_DATA(CDatabaseFindDBMSPage)
	enum { IDD = IDD_DATABASE_FIND_DBMSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID Search();

	VOID SetQuery(LPCTSTR pszQuery);
	CString GetQuery() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindDBMSPage)
public:
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatabaseFindDBMSPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeQuery();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTabCtrl window

class CDatabaseFindTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CDatabaseFindTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CDatabaseFindDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDatabaseFindTabCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindDialog

class CDatabaseFindDialog : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CDatabaseFindDialog)

	// Construction
public:
	CDatabaseFindDialog(CWnd *pParentWnd = NULL);

	// Attributes
public:
	CDatabaseFindTabCtrl  m_wndTabCtrl;
	CDatabaseFindTMPacketsPage  m_pageTMPackets;
	CDatabaseFindTCFunctionsPage  m_pageTCFunctions;
	CDatabaseFindTMParametersPage  m_pageTMParameters;
	CDatabaseFindTCParametersPage  m_pageTCParameters;
	CDatabaseFindOBProcessorsPage  m_pageOBProcessors;
	CDatabaseFindANDsPage  m_pageANDs;
	CDatabaseFindGRDsPage  m_pageGRDs;
	CDatabaseFindPODsPage  m_pagePODs;
	CDatabaseFindDBMSPage  m_pageDBMS;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseFindDialog)
public:
	virtual INT_PTR DoModal();
	virtual INT_PTR DoModal(LPCTSTR pszQuery);
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDatabaseFindDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCompileBatchInfo

// Specify the compile batch database components
#define COMPILEBATCH_COMPONENT_TMPACKETS   (1<<0)
#define COMPILEBATCH_COMPONENT_TCFUNCTIONS   (1<<1)
#define COMPILEBATCH_COMPONENT_TCPROCEDURES   (1<<2)
#define COMPILEBATCH_COMPONENT_TMPARAMETERS   (1<<3)
#define COMPILEBATCH_COMPONENT_TCPARAMETERS   (1<<4)
#define COMPILEBATCH_COMPONENT_OBPROCESSORS   (1<<5)
#define COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS   (1<<6)
#define COMPILEBATCH_COMPONENT_ANDS   (1<<7)
#define COMPILEBATCH_COMPONENT_GRDS   (1<<8)
#define COMPILEBATCH_COMPONENT_MMDS   (1<<9)
#define COMPILEBATCH_COMPONENT_PODS   (1<<10)
#define COMPILEBATCH_COMPONENT_SCRIPTS   (1<<11)
#ifndef RC_INVOKED
#define COMPILEBATCH_COMPONENTS_DEFAULT   (COMPILEBATCH_COMPONENT_TMPACKETS | COMPILEBATCH_COMPONENT_TCFUNCTIONS | COMPILEBATCH_COMPONENT_TMPARAMETERS | COMPILEBATCH_COMPONENT_TCPARAMETERS | COMPILEBATCH_COMPONENT_OBPROCESSORS | COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS | COMPILEBATCH_COMPONENT_ANDS | COMPILEBATCH_COMPONENT_GRDS | COMPILEBATCH_COMPONENT_PODS)
#define COMPILEBATCH_COMPONENTS_ALL   (COMPILEBATCH_COMPONENT_TMPACKETS | COMPILEBATCH_COMPONENT_TCFUNCTIONS | COMPILEBATCH_COMPONENT_TCPROCEDURES | COMPILEBATCH_COMPONENT_TMPARAMETERS | COMPILEBATCH_COMPONENT_TCPARAMETERS | COMPILEBATCH_COMPONENT_OBPROCESSORS | COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS | COMPILEBATCH_COMPONENT_ANDS | COMPILEBATCH_COMPONENT_GRDS | COMPILEBATCH_COMPONENT_MMDS | COMPILEBATCH_COMPONENT_PODS | COMPILEBATCH_COMPONENT_SCRIPTS)
#endif
// Specify the compile batch action options
#define COMPILEBATCH_ACTION_COMPILATION   1
#define COMPILEBATCH_ACTION_SYNTAXCHECK   2
#define COMPILEBATCH_ACTION_NOTHING   3
// Specify the compile batch schedule options
#define COMPILEBATCH_SCHEDULE_IMMEDIATELY   1
#define COMPILEBATCH_SCHEDULE_ATTIME   2
#define COMPILEBATCH_SCHEDULE_DAILY   3

class CCompileBatchInfo : public CObject
{
	// Construction
public:
	CCompileBatchInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		UINT  nAction;
		UINT  nScheduleOptions;
		ULONGLONG  nComponents;
		TIMEKEY  tExecutionTime;
		TIMEKEY  tDailyTime;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CTimeKey  m_tExecutionTime[2];
	CTimeSpan  m_tDailyTime;
	ULONGLONG  m_nComponents;
	UINT  m_nScheduleOptions;
	UINT  m_nAction;
private:
	BOOL  m_bModified;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetAction(UINT nAction);
	UINT GetAction() CONST;
	VOID SetComponents(ULONGLONG nComponents);
	ULONGLONG GetComponents() CONST;
	VOID SetScheduleOptions(UINT nOptions);
	UINT GetScheduleOptions() CONST;
	VOID SetExecutionTime(CONST CTimeKey &tTime);
	CTimeKey GetExecutionTime() CONST;
	VOID SetDailyExecutionTime(CONST CTimeSpan &tTime);
	CTimeSpan GetDailyExecutionTime() CONST;
	VOID SetLastExecutionTime(CONST CTimeKey &tTime);
	CTimeKey GetLastExecutionTime() CONST;
	VOID SetModified(BOOL bModified = TRUE);
	BOOL IsModified() CONST;

	VOID Copy(CONST CCompileBatchInfo *pBatchInfo);
	BOOL Compare(CONST CCompileBatchInfo *pBatchInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCompileBatches

class CCompileBatches : public CPtrArray
{
	// Construction
public:
	CCompileBatches();
	~CCompileBatches();

	// Attributes
public:

	// Operations
public:
	INT Add(CCompileBatchInfo *pBatchInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CCompileBatchInfo *GetAt(INT nIndex) CONST;
	CCompileBatchInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CCompileBatches *pBatches);
	BOOL Compare(CONST CCompileBatches *pBatches) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCompileBatchesDialog dialog

#define IDC_COMPILE_BATCHES_DETAILS   1001
#define IDC_COMPILE_BATCHES_PROFILE_STATIC   1002
#define IDC_COMPILE_BATCHES_PROFILE   1003
#define IDC_COMPILE_BATCHES_PROFILE_ADD   1004
#define IDC_COMPILE_BATCHES_PROFILE_REMOVE   1005
#define IDC_COMPILE_BATCHES_PROFILE_REMOVEALL   1006
#define IDC_COMPILE_BATCHES_PROPERTIES   1007
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_STATIC   1008
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS   1009
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS   1010
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPROCEDURES   1011
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS   1012
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS   1013
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_OBPROCESSORS   1014
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS   1015
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_ANDS   1016
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_GRDS   1017
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_MMDS   1018
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_PODS   1019
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_SCRIPTS   1020
#define IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE   1021
#define IDC_COMPILE_BATCHES_ACTION   1022
#define IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_STATIC   1023
#define IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_COMPILATION   1024
#define IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_SYNTAXCHECK   1025
#define IDC_COMPILE_BATCHES_SCHEDULE   1026
#define IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_STATIC   1027
#define IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY   1028
#define IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME   1029
#define IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER   1030
#define IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY   1031
#define IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER   1032
#define IDC_COMPILE_BATCHES_HELP   1033

// Specify the compile batches dialog related settings
#define COMPILEBATCHES_DEFAULT_DELAY   SECONDSPERDAY

class CCompileBatchesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CCompileBatchesDialog)

	// Construction
public:
	CCompileBatchesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CCompileBatches  m_pBatches[2];

	// Dialog Data
	//{{AFX_DATA(CCompileBatchesDialog)
	enum { IDD = IDD_COMPILE_BATCHES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumBatches();

	VOID ShowBatchProperties();

	CCompileBatchInfo *FindBatch() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompileBatchesDialog)
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
	//{{AFX_MSG(CCompileBatchesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddBatch();
	afx_msg void OnRemoveBatch();
	afx_msg void OnRemoveAllBatches();
	afx_msg void OnComponentTMPackets();
	afx_msg void OnComponentTCFunctions();
	afx_msg void OnComponentTCProcedures();
	afx_msg void OnComponentTMParameters();
	afx_msg void OnComponentTCParameters();
	afx_msg void OnComponentOBProcessors();
	afx_msg void OnComponentDerivedParameters();
	afx_msg void OnComponentANDs();
	afx_msg void OnComponentGRDs();
	afx_msg void OnComponentMMDs();
	afx_msg void OnComponentPODs();
	afx_msg void OnComponentScripts();
	afx_msg void OnComponentAll();
	afx_msg void OnActionCompilation();
	afx_msg void OnActionSyntaxCheck();
	afx_msg void OnScheduleImmediately();
	afx_msg void OnScheduleAtTime();
	afx_msg void OnScheduleDaily();
	afx_msg void OnSelchangeBatch();
	afx_msg void OnEditchangeBatch();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg void OnSpinchangeDailyTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCompileDirectiveInfo

// Specify the compile directives flags
#define COMPILEDIRECTIVES_FLAGS_ACTIVE   (1<<0)
#define COMPILEDIRECTIVES_FLAGS_NOWARNINGS   (1<<1)

class CCompileDirectivesInfo : public CObject
{
	// Construction
public:
	CCompileDirectivesInfo();
	~CCompileDirectivesInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbMessages;
		UINT  nFlags;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CStringArray  m_szMessages;
	UINT  m_nFlags;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetFlags(UINT nFlags);
	UINT GetFlags() CONST;
	VOID SetMessages(CONST CStringArray &szMessages);
	INT GetMessages(CStringArray &szMessages) CONST;

	INT Add(LPCTSTR pszMessage);

	INT Find(LPCTSTR pszMessage, INT nIndex = -1) CONST;

	CString GetAt(INT nIndex) CONST;
	CString operator[](INT nIndex) CONST;

	VOID RemoveAll();

	VOID Copy(CONST CCompileDirectivesInfo *pDirectivesInfo);
	BOOL Compare(CONST CCompileDirectivesInfo *pDirectivesInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCompileDirectives

class CCompileDirectives : public CPtrArray
{
	// Construction
public:
	CCompileDirectives();
	~CCompileDirectives();

	// Attributes
public:

	// Operations
public:
	BOOL SetActiveDirectives(LPCTSTR pszName);
	CString GetActiveDirectives() CONST;

	INT Add(CCompileDirectivesInfo *pDirectivesInfo);

	INT Find(LPCTSTR pszName) CONST;

	CCompileDirectivesInfo *GetAt(INT nIndex) CONST;
	CCompileDirectivesInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CCompileDirectives *pDirectives);
	BOOL Compare(CONST CCompileDirectives *pDirectives) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCompileDirectivesDialog dialog

#define IDC_COMPILE_DIRECTIVES_DETAILS   1001
#define IDC_COMPILE_DIRECTIVES_PROFILE_STATIC   1002
#define IDC_COMPILE_DIRECTIVES_PROFILE   1003
#define IDC_COMPILE_DIRECTIVES_ADD   1004
#define IDC_COMPILE_DIRECTIVES_REMOVE   1005
#define IDC_COMPILE_DIRECTIVES_REMOVEALL   1006
#define IDC_COMPILE_DIRECTIVES_MESSAGES_STATIC   1007
#define IDC_COMPILE_DIRECTIVES_MESSAGES   1008
#define IDC_COMPILE_DIRECTIVES_NOWARNINGS   1009
#define IDC_COMPILE_DIRECTIVES_DISABLE   1010
#define IDC_COMPILE_DIRECTIVES_DISABLED_STATIC   1011
#define IDC_COMPILE_DIRECTIVES_DISABLED   1012
#define IDC_COMPILE_DIRECTIVES_ENABLE   1013
#define IDC_COMPILE_DIRECTIVES_DELETE   1014
#define IDC_COMPILE_DIRECTIVES_HELP   1015

class CCompileDirectivesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CCompileDirectivesDialog)

	// Construction
public:
	CCompileDirectivesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CCompileDirectives  m_pDirectives[2];
	CStringArray  m_szMessages;
private:
	CStringArray  m_szColumns[2];

	// Dialog Data
	//{{AFX_DATA(CCompileDirectivesDialog)
	enum { IDD = IDD_COMPILE_DIRECTIVES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumProfiles();
	BOOL EnumMessages();

	VOID ShowDirectives();
	VOID UpdateDirectives();

	CCompileDirectivesInfo *FindDirectives() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompileDirectivesDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCompileDirectivesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnNoWarnings();
	afx_msg void OnEnable();
	afx_msg void OnDisable();
	afx_msg void OnDelete();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnEditchangeProfile();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCompileOptionsDialog dialog

#define IDC_COMPILE_OPTIONS_DETAILS   1001
#define IDC_COMPILE_OPTIONS_COMPILER_FILENAME_STATIC   1002
#define IDC_COMPILE_OPTIONS_COMPILER_FILENAME   1003
#define IDC_COMPILE_OPTIONS_COMPILER_FILENAME_BROWSE   1004
#define IDC_COMPILE_OPTIONS_LINKER_FILENAME_STATIC   1005
#define IDC_COMPILE_OPTIONS_LINKER_FILENAME   1006
#define IDC_COMPILE_OPTIONS_LINKER_FILENAME_BROWSE   1007
#define IDC_COMPILE_OPTIONS_PLATFORM_STATIC   1008
#define IDC_COMPILE_OPTIONS_PLATFORM   1009
#define IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY_STATIC   1010
#define IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY   1011
#define IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY_BROWSE   1012
#define IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY_STATIC   1013
#define IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY   1014
#define IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY_BROWSE   1015
#define IDC_COMPILE_OPTIONS_DIRECTIVES   1016
#define IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT_STATIC   1017
#define IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT   1018
#define IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS_STATIC   1019
#define IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS   1020
#define IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL_STATIC   1021
#define IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL   1022
#define IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS   1023
#define IDC_COMPILE_OPTIONS_HELP   1024

class CCompileOptionsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CCompileOptionsDialog)

	// Construction
public:
	CCompileOptionsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szPlatForm[2];
	CString  m_szFileName[2][2];
	CString  m_szDirectory[2][2];
	CString  m_szOptions[3][2];

	// Dialog Data
	//{{AFX_DATA(CCompileOptionsDialog)
	enum { IDD = IDD_COMPILE_OPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumCompilationUnits();
	BOOL EnumOptimizationsOptions();
	BOOL EnumWarningsOptions();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompileOptionsDialog)
public:
	virtual INT_PTR DoModal();
	virtual INT_PTR DoModal(CString &szFileName);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCompileOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPlatForm();
	afx_msg void OnBrowseCompilerFiles();
	afx_msg void OnBrowseLinkerFiles();
	afx_msg void OnBrowseIncludeDirectory();
	afx_msg void OnBrowseLibraryDirectory();
	afx_msg void OnTreatWarningsAsError();
	afx_msg void OnEditchangeCompilerFileName();
	afx_msg void OnEditchangeLinkerFileName();
	afx_msg void OnEditchangeIncludeDirectory();
	afx_msg void OnEditchangeLibraryDirectory();
	afx_msg void OnSelchangeCompilationUnit();
	afx_msg void OnSelchangeOptimization();
	afx_msg void OnSelchangeWarningLevel();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsLoggingPage dialog

#define IDC_TOOLSOPTIONS_LOGGINGPAGE_DETAILS   1001
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_DATABASE_STATIC   1002
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_DATABASE   1003
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_DISABLED   1004
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME_STATIC   1005
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME   1006
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_BROWSE   1007
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY   1008
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OVERWRITE   1009
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OLDOVERWRITE   1010
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS_STATIC   1011
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS   1012
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_NOOVERWRITE   1013
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE   1014
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_UNLIMITED   1015
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_LIMITED   1016
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM_STATIC   1017
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM   1018
#define IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_RESET   1019

// Specify the tools options logging page related settings
#define TOOLSOPTIONSLOGGING_MINIMUMDAYS   1
#define TOOLSOPTIONSLOGGING_MAXIMUMDAYS   10000
#define TOOLSOPTIONSLOGGING_DEFAULTDAYS   DAYSPERWEEK
#define TOOLSOPTIONSLOGGING_MINIMUMSIZE   4
#define TOOLSOPTIONSLOGGING_MAXIMUMSIZE   4096
#define TOOLSOPTIONSLOGGING_DEFAULTSIZE   (LOGFILE_DEFAULT_SIZE/(16*1024))

class CToolsOptionsLoggingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CToolsOptionsLoggingPage)

	// Construction
public:
	CToolsOptionsLoggingPage();

	// Attributes
private:
	CDatabaseProfileInfo  m_cDatabaseInfo[2];

	// Dialog Data
	//{{AFX_DATA(CToolsOptionsLoggingPage)
	enum { IDD = IDD_TOOLSOPTIONS_LOGGINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetLoggingInformation(CONST CDatabaseProfileInfo *pDatabaseInfo);
	VOID GetLoggingInformation(CDatabaseProfileInfo *pDatabaseInfo) CONST;

	VOID ShowLoggingInformation();

private:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CToolsOptionsLoggingPage)
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
	//{{AFX_MSG(CToolsOptionsLoggingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseFilename();
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
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsTabCtrl window

class CToolsOptionsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CToolsOptionsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CToolsOptionsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolsOptionsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolsOptionsTabCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsDialog

class CToolsOptionsDialog : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CToolsOptionsDialog)

	// Construction
public:
	CToolsOptionsDialog(CWnd *pParentWnd = NULL);

	// Attributes
public:
	CToolsOptionsTabCtrl  m_wndTabCtrl;
	CToolsOptionsLoggingPage  m_pageLogging;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolsOptionsDialog)
public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolsOptionsDialog)
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayWindowsDialog dialog

#define IDC_DISPLAYWINDOWS_LIST_STATIC   1001
#define IDC_DISPLAYWINDOWS_LIST   1002
#define IDC_DISPLAYWINDOWS_HELP   1003

class CDisplayWindowsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDisplayWindowsDialog)

	// Construction
public:
	CDisplayWindowsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CDisplayWindowsDialog)
	enum { IDD = IDD_DISPLAYWINDOWS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayWindowsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDisplayWindowsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelectDisplayWindow();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserInterfaceRibbonBarPage dialog

#define IDC_USERINTERFACE_RIBBONBARPAGE_DETAILS   1001
#define IDC_USERINTERFACE_RIBBONBARPAGE_CATEGORY_STATIC   1002
#define IDC_USERINTERFACE_RIBBONBARPAGE_CATEGORY   1003
#define IDC_USERINTERFACE_RIBBONBARPAGE_COMMANDS_STATIC   1004
#define IDC_USERINTERFACE_RIBBONBARPAGE_COMMANDS   1005
#define IDC_USERINTERFACE_RIBBONBARPAGE_COMMAND_ADD   1006
#define IDC_USERINTERFACE_RIBBONBARPAGE_COMMAND_REMOVE   1007
#define IDC_USERINTERFACE_RIBBONBARPAGE_QAT_LIST   1008
#define IDC_USERINTERFACE_RIBBONBARPAGE_QAT_MOVEUP   1009
#define IDC_USERINTERFACE_RIBBONBARPAGE_QAT_MOVEDOWN   1010
#define IDC_USERINTERFACE_RIBBONBARPAGE_QAT_RESET   1011
#define IDC_USERINTERFACE_RIBBONBARPAGE_QAT_BELOW   1012

class CUserInterfaceRibbonBarPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CUserInterfaceRibbonBarPage)

	// Construction
public:
	CUserInterfaceRibbonBarPage(CMFCRibbonBar *pRibbonBar = NULL);

	// Attributes
private:
	CMFCRibbonBar  *m_pRibbonBar;
private:
	CUIntArray  m_nQATCommandIDs;
	BOOL  m_bQAToolbarBelow;

	// Dialog Data
	//{{AFX_DATA(CUserInterfaceRibbonBarPage)
	enum { IDD = IDD_USERINTERFACE_RIBBONBARPAGE };

	int  m_nCategory;
	BOOL  m_bQAToolbarOnBottom;
	CMFCButton  m_wndAdd;
	CMFCButton  m_wndRemove;
	CMFCButton  m_wndUp;
	CMFCButton  m_wndDown;
	CComboBox  m_wndCategoryCombo;
	CMFCRibbonCommandsListBox  m_wndCommandsList;
	CMFCRibbonCommandsListBox  m_wndQATList;
	//}}AFX_DATA

	// Operations
private:
	VOID EnumCommands();

	VOID MoveCommand(BOOL bUp);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserInterfaceRibbonBarPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
	virtual VOID Update();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserInterfaceRibbonBarPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddCommand();
	afx_msg void OnRemoveCommand();
	afx_msg void OnQATCommandUp();
	afx_msg void OnQATCommandDown();
	afx_msg void OnQATReset();
	afx_msg void OnQAToolbarBelow();
	afx_msg void OnSelendokCategory();
	afx_msg void OnSelchangeCommands();
	afx_msg void OnSelchangeQATList();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserInterfaceKeyboardPage dialog

#define IDC_USERINTERFACE_KEYBOARDPAGE_DETAILS   1001
#define IDC_USERINTERFACE_KEYBOARDPAGE_CATEGORY_STATIC   1002
#define IDC_USERINTERFACE_KEYBOARDPAGE_CATEGORY   1003
#define IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDS_STATIC   1004
#define IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDS   1005
#define IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS_STATIC   1006
#define IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS   1007
#define IDC_USERINTERFACE_KEYBOARDPAGE_NEWKEY_STATIC   1008
#define IDC_USERINTERFACE_KEYBOARDPAGE_NEWKEY   1009
#define IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDASSOCIATION_STATIC   1010
#define IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDASSOCIATION   1011
#define IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE_STATIC   1012
#define IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE   1013
#define IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE_SYMBOL   1014
#define IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION_STATIC   1015
#define IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION   1016
#define IDC_USERINTERFACE_KEYBOARDPAGE_ACCELERATOR_ASSIGN   1017
#define IDC_USERINTERFACE_KEYBOARDPAGE_ACCELERATOR_REMOVE   1018
#define IDC_USERINTERFACE_KEYBOARDPAGE_ACCELERATORS_RESET   1019

class CUserInterfaceKeyboardPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CUserInterfaceKeyboardPage)

	// Construction
public:
	CUserInterfaceKeyboardPage(CMFCRibbonBar *pRibbonBar = NULL);
	virtual ~CUserInterfaceKeyboardPage();

	// Attributes
private:
	CMFCRibbonBar  *m_pRibbonBar;
	CFrameWnd  *m_pParentFrame;
private:
	INT  m_nAccelSize[2];
	HACCEL  m_hAccelTable;
	LPACCEL  m_pAccel[3];
	CMFCRibbonBaseElement  *m_pButton;

	// Dialog Data
	//{{AFX_DATA(CUserInterfaceKeyboardPage)
	enum { IDD = IDD_USERINTERFACE_KEYBOARDPAGE };

	CString  m_szCommand;
	CString  m_szAssociation;
	CStatic  m_wndAssociation;
	CStatic  m_wndViewIcon;
	CListBox  m_wndCategoryList;
	CListBox  m_wndCurrentKeysList;
	CComboBox  m_wndViewTypeList;
	CMFCButton  m_wndRemoveButton;
	CMFCButton  m_wndAssignButton;
	CMFCRibbonCommandsListBox  m_wndCommandsList;
	CMFCAcceleratorKeyAssignCtrl  m_wndNewKey;
	//}}AFX_DATA

	// Operations
private:
	VOID EnumCommands();
	VOID EnumAccelerators();

	VOID ShowAccelerator();
	VOID ShowShortcutKey();

	VOID AddKeyEntry(LPACCEL pEntry);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserInterfaceKeyboardPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
	virtual VOID Update();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserInterfaceKeyboardPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAssignAccelerator();
	afx_msg void OnRemoveAccelerator();
	afx_msg void OnResetAllAccelerators();
	afx_msg void OnEditchangeNewKey();
	afx_msg void OnSelchangeCategory();
	afx_msg void OnSelchangeCommandsList();
	afx_msg void OnSelchangeCurrentKeysList();
	afx_msg void OnSelchangeViewType();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserInterfaceDialog

class CUserInterfaceDialog : public CLocalePropertySheetDialog
{
	DECLARE_DYNAMIC(CUserInterfaceDialog)

	// Construction
public:
	CUserInterfaceDialog(CWnd *pParentWnd, CMFCRibbonBar *pRibbonBar);
	virtual ~CUserInterfaceDialog();

	// Attributes
private:
	CUserInterfaceRibbonBarPage  *m_pRibbonBarPage;
	CUserInterfaceKeyboardPage  *m_pKeyboardPage;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserInterfaceDialog)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CUserInterfaceDialog)
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog dialog

#define IDC_ABOUT_DETAILS   1001
#define IDC_ABOUT_ICON   1002
#define IDC_ABOUT_NAME   1003
#define IDC_ABOUT_VERSION   1004
#define IDC_ABOUT_COPYRIGHT   1005
#define IDC_ABOUT_SEPARATOR   1006
#define IDC_ABOUT_COPYRIGHTNOTICE_TITLE   1007
#define IDC_ABOUT_COPYRIGHTNOTICE_STATEMENT   1008
#define IDC_ABOUT_COPYRIGHTNOTICE_CONSEQUENCE   1009

class CAboutDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CAboutDialog)

	// Construction
public:
	CAboutDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CAboutDialog)
	enum { IDD = IDD_ABOUT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAboutDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DIALOGS_H__
