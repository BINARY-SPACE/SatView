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
* 1995/11/26 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DIALOGS_H__
#define __DIALOGS_H__

#include "email.h"


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

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CWelcomeDialog)
	enum { IDD = IDD_WELCOME_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumSpacecrafts();

	INT EnumAccounts(LPCTSTR pszPath, CStringArray &szAccounts);
	BOOL TestAccount(LPCTSTR pszAccount, CString &szName);

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
	afx_msg void OnEditchangePassword();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLoginInfo

class CLoginInfo : public CObject
{
	// Construction
public:
	CLoginInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbUser;
		INT  cbServer;
		INT  cbPassword;
		TIMEKEY  tTime[2];
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szUser;
	CString  m_szServer;
	CString  m_szPassword;
	CTimeKey  m_tTime[2];

	// Operations
public:
	VOID SetServer(LPCTSTR pszServer);
	CString GetServer() CONST;
	VOID SetUser(LPCTSTR pszUser);
	CString GetUser() CONST;
	VOID SetPassword(LPCTSTR pszPassword);
	CString GetPassword() CONST;
	VOID SetTimeRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetTimeRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;

	VOID Copy(CONST CLoginInfo *pInfo);
	BOOL Compare(CONST CLoginInfo *pInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLoginOptions

#define LOGIN_OPTION_RECONNECT   (1<<0)
#define LOGIN_OPTION_RECONNECTBYINTERVAL   (1<<1)
#define LOGIN_OPTION_RECONNECTBYCOUNT   (1<<2)

class CLoginOptions : public CMutexArray
{
	// Construction
public:
	CLoginOptions();
	~CLoginOptions();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbItems;
		UINT  nOptions;
		UINT  nRetryCount[2];
		TIMEKEY  tRetryInterval;
	} DATA, *PDATA, *LPDATA;
private:
	UINT  m_nOptions;
	UINT  m_nRetryCount[2];
	CTimeSpan  m_tRetryInterval;

	// Operations
public:
	INT Add(CLoginInfo *pInfo);

	INT Find(CONST CLoginInfo *pInfo) CONST;

	CLoginInfo *GetAt(INT nIndex) CONST;
	CLoginInfo *operator[](INT nIndex) CONST;

	VOID SetOptions(UINT nOptions);
	UINT GetOptions();
	BOOL SetRetention(CONST CTimeSpan &tInterval, UINT nCount);
	BOOL GetRetention(CTimeSpan &tInterval, UINT &nCount) CONST;
	BOOL SetRetentionRetries(UINT nCount);
	UINT GetRetentionRetries() CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CLoginOptions *pOptions);
	BOOL Compare(CONST CLoginOptions *pOptions) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(CONST CLoginInfo *pInfo, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog

#define IDC_LOGIN_DETAILS   1001
#define IDC_LOGIN_COMPUTERNAME_STATIC   1002
#define IDC_LOGIN_COMPUTERNAME   1003
#define IDC_LOGIN_SPACECRAFTNAME_STATIC   1004
#define IDC_LOGIN_SPACECRAFTNAME   1005
#define IDC_LOGIN_USERNAME_STATIC   1006
#define IDC_LOGIN_USERNAME   1007
#define IDC_LOGIN_DATABASE_STATIC  1008
#define IDC_LOGIN_DATABASE   1009
#define IDC_LOGIN_MODE   1010
#define IDC_LOGIN_MODE_ONLINE   1011
#define IDC_LOGIN_MODE_OFFLINE   1012
#define IDC_LOGIN_PASSWORD_STATIC   1013
#define IDC_LOGIN_PASSWORD   1014
#define IDC_LOGIN_REMOTENETWORK   1015
#define IDC_LOGIN_REMOTENETWORK_SERVER_STATIC   1016
#define IDC_LOGIN_REMOTENETWORK_SERVER   1017
#define IDC_LOGIN_REMOTENETWORK_USER_STATIC   1018
#define IDC_LOGIN_REMOTENETWORK_USER   1019
#define IDC_LOGIN_REMOTENETWORK_PASSWORD_STATIC   1020
#define IDC_LOGIN_REMOTENETWORK_PASSWORD   1021
#define IDC_LOGIN_REMOTENETWORK_DIALUP   1022
#define IDC_LOGIN_REMOTENETWORK_OPTIONS   1023
#define IDC_LOGIN_HELP   1024

class CLoginDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CLoginDialog)

	// Construction
public:
	CLoginDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CAccountTokens  m_pAccounts;
	CServerProfiles  m_pServers;
	CDatabaseProfiles  m_pDatabases[2];
	CLoginOptions  m_pLoginOptions[2];

	// Dialog Data
	//{{AFX_DATA(CLoginDialog)
	enum { IDD = IDD_LOGIN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumComputers();
	BOOL EnumSpacecrafts();
	BOOL EnumUsers();
	BOOL EnumDatabases();
	BOOL EnumServers();
	BOOL EnumLogins();

	BOOL ShowLoginInfo(BOOL bReset = FALSE);

	INT EnumAccounts(LPCTSTR pszPath, CStringArray &szAccounts);
	BOOL TestAccount(LPCTSTR pszAccount, CString &szName);

	INT FindAccount() CONST;
	INT FindAccount(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDialog)
public:
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
	afx_msg void OnSelchangeSpacecraftName();
	afx_msg void OnSelchangeUserName();
	afx_msg void OnSelchangeDatabase();
	afx_msg void OnSelchangeNetworkServer();
	afx_msg void OnEditchangePassword();
	afx_msg void OnEditchangeNetworkServer();
	afx_msg void OnEditchangeNetworkUser();
	afx_msg void OnEditchangeNetworkPassword();
	afx_msg void OnOnlineMode();
	afx_msg void OnOfflineMode();
	afx_msg void OnDialup();
	afx_msg void OnOptions();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLoginOptionsDialog dialog

#define IDC_LOGIN_OPTIONS_DETAILS   1001
#define IDC_LOGIN_OPTIONS_LIST_STATIC   1002
#define IDC_LOGIN_OPTIONS_LIST   1003
#define IDC_LOGIN_OPTIONS_LIST_ADD   1004
#define IDC_LOGIN_OPTIONS_LIST_REMOVE   1005
#define IDC_LOGIN_OPTIONS_LIST_REMOVEALL   1006
#define IDC_LOGIN_OPTIONS_RECONNECTION   1007
#define IDC_LOGIN_OPTIONS_RECONNECTION_INTERVAL   1008
#define IDC_LOGIN_OPTIONS_RECONNECTION_INTERVAL_STATIC   1009
#define IDC_LOGIN_OPTIONS_RECONNECTION_INTERVAL_MINUTES   1010
#define IDC_LOGIN_OPTIONS_RECONNECTION_COUNT   1011
#define IDC_LOGIN_OPTIONS_RECONNECTION_COUNT_STATIC   1012
#define IDC_LOGIN_OPTIONS_RECONNECTION_COUNT_NUMBER   1013
#define IDC_LOGIN_OPTIONS_HELP   1014

// Specify the login options related settings
#define LOGINOPTIONS_INTERVAL_MINIMUM   1
#define LOGINOPTIONS_INTERVAL_MAXIMUM   MINUTESPERDAY
#define LOGINOPTIONS_INTERVAL_DEFAULT   1
#define LOGINOPTIONS_COUNT_MINIMUM   1
#define LOGINOPTIONS_COUNT_MAXIMUM   100
#define LOGINOPTIONS_COUNT_DEFAULT   5

class CLoginOptionsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CLoginOptionsDialog)

	// Construction
public:
	CLoginOptionsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CLoginInfo  m_cDefaultOption;
	CLoginOptions  m_pOptions[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CLoginOptionsDialog)
	enum { IDD = IDD_LOGIN_OPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumScheduledLogins();

	VOID ShowLoginOptions();

	INT CalcColumnWidth(LPCTSTR pszColumn);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginOptionsDialog)
public:
	virtual INT DoModal(CLoginOptions &pOptions);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnListAdd();
	afx_msg void OnListRemove();
	afx_msg void OnListRemoveAll();
	afx_msg void OnReconnect();
	afx_msg void OnReconnectInterval();
	afx_msg void OnReconnectCount();
	afx_msg void OnSpinchangeReconnectInterval();
	afx_msg void OnSpinchangeReconnectCount();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLoginScheduleDialog dialog

#define IDC_LOGIN_SCHEDULE_DETAILS   1001
#define IDC_LOGIN_SCHEDULE_STARTTIME_STATIC   1002
#define IDC_LOGIN_SCHEDULE_STARTTIME   1003
#define IDC_LOGIN_SCHEDULE_STOPTIME_STATIC   1004
#define IDC_LOGIN_SCHEDULE_STOPTIME   1005
#define IDC_LOGIN_SCHEDULE_PROPERTIES   1006
#define IDC_LOGIN_SCHEDULE_PROPERTIES_SERVER_STATIC   1007
#define IDC_LOGIN_SCHEDULE_PROPERTIES_SERVER   1008
#define IDC_LOGIN_SCHEDULE_PROPERTIES_USER_STATIC   1009
#define IDC_LOGIN_SCHEDULE_PROPERTIES_USER   1010
#define IDC_LOGIN_SCHEDULE_PROPERTIES_PASSWORD_STATIC   1011
#define IDC_LOGIN_SCHEDULE_PROPERTIES_PASSWORD   1012
#define IDC_LOGIN_SCHEDULE_HELP   1013

// Specify the login schedule related settings
#define LOGINSCHEDULE_TIMERANGE_DEFAULT   SECONDSPERHOUR

class CLoginScheduleDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CLoginScheduleDialog)

	// Construction
public:
	CLoginScheduleDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CLoginInfo  m_cLoginInfo;

	// Dialog Data
	//{{AFX_DATA(CLoginScheduleDialog)
	enum { IDD = IDD_LOGIN_SCHEDULE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumServers();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginScheduleDialog)
public:
	virtual INT DoModal(CLoginInfo *pInfo);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginScheduleDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeServer();
	afx_msg void OnEditchangeUser();
	afx_msg void OnEditchangePassword();
	afx_msg void OnSelchangeServer();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsDisplayAreaPage dialog

#define IDC_SETTINGS_DISPLAYAREAPAGE_DETAILS   1001
#define IDC_SETTINGS_DISPLAYAREAPAGE_TYPE_STATIC   1002
#define IDC_SETTINGS_DISPLAYAREAPAGE_TYPE_STANDARD   1003
#define IDC_SETTINGS_DISPLAYAREAPAGE_TYPE_FOLDER   1004
#define IDC_SETTINGS_DISPLAYAREAPAGE_CONTENTS   1005
#define IDC_SETTINGS_DISPLAYAREAPAGE_TABS   1006
#define IDC_SETTINGS_DISPLAYAREAPAGE_TABSCOMMENT   1007
#define IDC_SETTINGS_DISPLAYAREAPAGE_TITLE_STATIC   1008
#define IDC_SETTINGS_DISPLAYAREAPAGE_TITLE   1009
#define IDC_SETTINGS_DISPLAYAREAPAGE_INSERTBEFORE   1010
#define IDC_SETTINGS_DISPLAYAREAPAGE_INSERTAFTER   1011
#define IDC_SETTINGS_DISPLAYAREAPAGE_MODIFY   1012
#define IDC_SETTINGS_DISPLAYAREAPAGE_DELETE   1013
#define IDC_SETTINGS_DISPLAYAREAPAGE_BEHAVIOR   1014
#define IDC_SETTINGS_DISPLAYAREAPAGE_ACCESS   1015
#define IDC_SETTINGS_DISPLAYAREAPAGE_ALLUSERS   1016
#define IDC_SETTINGS_DISPLAYAREAPAGE_LIMITEDUSERS   1017
#define IDC_SETTINGS_DISPLAYAREAPAGE_USERS   1018
#define IDC_SETTINGS_DISPLAYAREAPAGE_ADDUSER   1019
#define IDC_SETTINGS_DISPLAYAREAPAGE_REMOVEUSER   1020
#define IDC_SETTINGS_DISPLAYAREAPAGE_PASSWORD   1021
#define IDC_SETTINGS_DISPLAYAREAPAGE_PASSWORD_NONE   1022
#define IDC_SETTINGS_DISPLAYAREAPAGE_PASSWORD_USER   1023
#define IDC_SETTINGS_DISPLAYAREAPAGE_PASSWORD_SPECIAL   1024
#define IDC_SETTINGS_DISPLAYAREAPAGE_PASSWORD_CONTENTS   1025
#define IDC_SETTINGS_DISPLAYAREAPAGE_PASSWORD_CONFIRMATION_STATIC   1026
#define IDC_SETTINGS_DISPLAYAREAPAGE_PASSWORD_CONFIRMATION   1027

class CSettingsDisplayAreaPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CSettingsDisplayAreaPage)

	// Construction
public:
	CSettingsDisplayAreaPage();

	// Attributes
private:
	CString  m_szList;
	CPtrArray  m_pUsers;
	CUIntArray  m_nTabs;
	CStringArray  m_szTabs[2];
	CStringArray  m_szPasswords;
	CUIntArray  m_nBehaviorFlags;

	// Dialog Data
	//{{AFX_DATA(CSettingsDisplayAreaPage)
	enum { IDD = IDD_SETTINGS_DISPLAYAREAPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
private:
	VOID EnumUsers(INT nIndex);
	VOID EnumPasswords(INT nIndex);

	BOOL InsertTab(LPCTSTR pszTitle, INT nIndex);
	BOOL ModifyTab(LPCTSTR pszTitle, INT nIndex);
	BOOL DeleteTab(INT nIndex);

	VOID ShowDisplayPageInfo();
	VOID SaveDisplayPageInfo();

	VOID AdjustToPrivileges();

public:
	class CSettingsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDisplayAreaPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
	virtual VOID Update();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSettingsDisplayAreaPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnStandardType();
	afx_msg void OnFolderType();
	afx_msg void OnEditchangeTitle();
	afx_msg void OnInsertBefore();
	afx_msg void OnInsertAfter();
	afx_msg void OnModify();
	afx_msg void OnDelete();
	afx_msg void OnBehavior();
	afx_msg void OnAllUsers();
	afx_msg void OnLimitedUsers();
	afx_msg void OnSelchangeUsers();
	afx_msg void OnAddUser();
	afx_msg void OnRemoveUser();
	afx_msg void OnPasswordNone();
	afx_msg void OnPasswordUser();
	afx_msg void OnPasswordSpecial();
	afx_msg void OnEditchangePasswordContents();
	afx_msg void OnEditchangePasswordConfirmation();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsEventLogsPage dialog

#define IDC_SETTINGS_EVENTLOGSPAGE_DETAILS   1001
#define IDC_SETTINGS_EVENTLOGSPAGE_COMPUTERNAME_STATIC   1002
#define IDC_SETTINGS_EVENTLOGSPAGE_COMPUTERNAME   1003
#define IDC_SETTINGS_EVENTLOGSPAGE_CONNECT   1004
#define IDC_SETTINGS_EVENTLOGSPAGE_SPACECRAFTNAME_STATIC   1005
#define IDC_SETTINGS_EVENTLOGSPAGE_SPACECRAFTNAME   1006
#define IDC_SETTINGS_EVENTLOGSPAGE_USERNAME_STATIC   1007
#define IDC_SETTINGS_EVENTLOGSPAGE_USERNAME   1008
#define IDC_SETTINGS_EVENTLOGSPAGE_DEFAULTS   1009
#define IDC_SETTINGS_EVENTLOGSPAGE_CATEGORYDETAILS   1010
#define IDC_SETTINGS_EVENTLOGSPAGE_CATEGORY_STATIC   1011
#define IDC_SETTINGS_EVENTLOGSPAGE_CATEGORY   1012
#define IDC_SETTINGS_EVENTLOGSPAGE_FILENAME_STATIC   1013
#define IDC_SETTINGS_EVENTLOGSPAGE_FILENAME   1014
#define IDC_SETTINGS_EVENTLOGSPAGE_BROWSE   1015
#define IDC_SETTINGS_EVENTLOGSPAGE_FREESPACE_STATIC   1016
#define IDC_SETTINGS_EVENTLOGSPAGE_FREESPACE   1017
#define IDC_SETTINGS_EVENTLOGSPAGE_FREESPACE_KB   1018
#define IDC_SETTINGS_EVENTLOGSPAGE_POLICY   1019
#define IDC_SETTINGS_EVENTLOGSPAGE_POLICY_OVERWRITE   1020
#define IDC_SETTINGS_EVENTLOGSPAGE_POLICY_OLDOVERWRITE   1021
#define IDC_SETTINGS_EVENTLOGSPAGE_POLICY_DAYS_STATIC   1022
#define IDC_SETTINGS_EVENTLOGSPAGE_POLICY_DAYS   1023
#define IDC_SETTINGS_EVENTLOGSPAGE_POLICY_NOOVERWRITE   1024
#define IDC_SETTINGS_EVENTLOGSPAGE_SIZE   1025
#define IDC_SETTINGS_EVENTLOGSPAGE_SIZE_UNLIMITED   1026
#define IDC_SETTINGS_EVENTLOGSPAGE_SIZE_LIMITED   1027
#define IDC_SETTINGS_EVENTLOGSPAGE_SIZE_MAXIMUM_STATIC   1028
#define IDC_SETTINGS_EVENTLOGSPAGE_SIZE_MAXIMUM   1029
#define IDC_SETTINGS_EVENTLOGSPAGE_SIZE_COMPRESSION   1030
#define IDC_SETTINGS_EVENTLOGSPAGE_SIZE_RESET   1031

// Specify the settings eventlogs page categories
#define EVENTLOGS_CATEGORY_SYSTEM   0
#define EVENTLOGS_CATEGORY_GLOBALSPACECRAFT   1
#define EVENTLOGS_CATEGORY_SPACECRAFT   2
#define EVENTLOGS_CATEGORY_USER   3
#define EVENTLOGS_CATEGORIES   4
// Specify the settings eventlogs page related settings
#define EVENTLOGS_MINIMUMDAYS   1
#define EVENTLOGS_MAXIMUMDAYS   10000
#define EVENTLOGS_DEFAULTDAYS   DAYSPERWEEK
#define EVENTLOGS_MINIMUMSIZE   32
#define EVENTLOGS_MAXIMUMSIZE   2147483647
#define EVENTLOGS_DEFAULTSIZE   (LOGFILE_DEFAULT_SIZE/1024)

class CSettingsEventLogsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CSettingsEventLogsPage)

	// Construction
public:
	CSettingsEventLogsPage();

	// Attributes
private:
	CStringArray  m_szComputerName[2];
	CStringArray  m_szSpacecraftName[2];
	CStringArray  m_szUserName[2];
	CStringArray  m_szFileName[2][EVENTLOGS_CATEGORIES];
	CUIntArray  m_nPolicy[2][EVENTLOGS_CATEGORIES];
	CUIntArray  m_fRetention[2][EVENTLOGS_CATEGORIES];
	CUIntArray  m_tRetention[2][EVENTLOGS_CATEGORIES];
	CByteArray  m_bCompression[2][EVENTLOGS_CATEGORIES];
	CByteArray  m_bReset[2][EVENTLOGS_CATEGORIES];

	// Dialog Data
	//{{AFX_DATA(CSettingsEventLogsPage)
	enum { IDD = IDD_SETTINGS_EVENTLOGSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumComputers();
	BOOL EnumSpacecrafts();
	BOOL EnumUsers();
	BOOL EnumCategories();

	BOOL SaveEventLogInfo();
	BOOL LoadEventLogInfo();
	BOOL DefaultEventLogInfo();
	BOOL CheckEventLogInfo() CONST;
	INT FindEventLogInfo() CONST;

	VOID ShowEventLogCategoryInfo();
	VOID LoadEventLogCategoryInfo();
	VOID SaveCommonEventLogCategoryInfo();
	VOID LoadCommonEventLogCategoryInfo();
	BOOL CheckEventLogCategoryFileName() CONST;
	BOOL CheckEventLogCategoryPolicy() CONST;
	BOOL CheckEventLogCategorySize() CONST;
	BOOL CheckEventLogCategoryCompression() CONST;
	INT QueryEventLogCategory() CONST;

	CString GetFreeEventLogDiskSpace(LPCTSTR pszFileName) CONST;

	BOOL CheckPrivileges(UINT nPrivilege) CONST;
	VOID AdjustToPrivileges();

public:
	class CSettingsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSettingsEventLogsPage)
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
	//{{AFX_MSG(CSettingsEventLogsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComputerName();
	afx_msg void OnSelchangeSpacecraftName();
	afx_msg void OnSelchangeUserName();
	afx_msg void OnDropdownComputerName();
	afx_msg void OnDropdownSpacecraftName();
	afx_msg void OnDropdownUserName();
	afx_msg void OnEditchangeComputerName();
	afx_msg void OnConnectComputer();
	afx_msg void OnDefaults();
	afx_msg void OnSelchangeCategory();
	afx_msg void OnDropdownCategory();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSpinchangeDays();
	afx_msg void OnSpinchangeSize();
	afx_msg void OnBrowseFilename();
	afx_msg void OnOverwriteEvents();
	afx_msg void OnOverwriteOldEvents();
	afx_msg void OnOverwriteNoEvents();
	afx_msg void OnUnlimitedSize();
	afx_msg void OnLimitedSize();
	afx_msg void OnResetSize();
	afx_msg void OnCompression();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsPrintingPage dialog

#define IDC_SETTINGS_PRINTINGPAGE_DETAILS   1001
#define IDC_SETTINGS_PRINTINGPAGE_PROFILES_STATIC   1002
#define IDC_SETTINGS_PRINTINGPAGE_PROFILES   1003
#define IDC_SETTINGS_PRINTINGPAGE_ADDPROFILE   1004
#define IDC_SETTINGS_PRINTINGPAGE_REMOVEPROFILE   1005
#define IDC_SETTINGS_PRINTINGPAGE_REMOVEALLPROFILES   1006
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES   1007
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PRINTER_STATIC   1008
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PRINTER   1009
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_CHANGE   1010
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_SETUP   1011
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPER   1012
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERSIZE_STATIC   1013
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERSIZE   1014
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERSOURCE_STATIC   1015
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERSOURCE   1016
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERCOPIES_STATIC   1017
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERCOPIES   1018
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERRESOLUTION_STATIC   1019
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERRESOLUTION   1020
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERMARGINS   1021
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERLEFTMARGIN_STATIC   1022
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERLEFTMARGIN   1023
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERRIGHTMARGIN_STATIC   1024
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERRIGHTMARGIN   1025
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERTOPMARGIN_STATIC   1026
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERTOPMARGIN   1027
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERBOTTOMMARGIN_STATIC   1028
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERBOTTOMMARGIN   1029
#define IDC_SETTINGS_PRINTINGPAGE_PROPERTIES_PAPERORIENTATION   1030

class CSettingsPrintingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CSettingsPrintingPage)

	// Construction
public:
	CSettingsPrintingPage();

	// Attributes
private:
	CPrintProfiles  m_pProfiles[2];

	// Dialog Data
	//{{AFX_DATA(CSettingsPrintingPage)
	enum { IDD = IDD_SETTINGS_PRINTINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
private:
	VOID ShowProfileInfo();
	CPrintProfileInfo *FindProfileInfo() CONST;

	VOID GetPaperMargins(CONST CPrintProfileInfo *pProfileInfo, CString &szLeft, CString &szTop, CString &szRight, CString &szBottom) CONST;
	CString GetPaperSize(CONST CPrintProfileInfo *pProfileInfo) CONST;
	CString GetPaperSource(CONST CPrintProfileInfo *pProfileInfo) CONST;
	CString GetResolution(CONST CPrintProfileInfo *pProfileInfo) CONST;
	CString GetCopies(CONST CPrintProfileInfo *pProfileInfo) CONST;

	VOID ShowPaperPicture();
	VOID ShowPaperPicture(CDC *pDC);

	VOID AdjustToPrivileges();

public:
	class CSettingsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSettingsPrintingPage)
public:
	virtual BOOL Initialize();
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
	//{{AFX_MSG(CSettingsPrintingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnEditchangeProfile();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnAddProfile();
	afx_msg void OnRemoveProfile();
	afx_msg void OnRemoveAllProfiles();
	afx_msg void OnChangePrinter();
	afx_msg void OnChangePrinterSetup();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsAuditionsPage dialog

#define IDC_SETTINGS_AUDITIONSPAGE_DETAILS   1001
#define IDC_SETTINGS_AUDITIONSPAGE_PROFILES_STATIC   1002
#define IDC_SETTINGS_AUDITIONSPAGE_PROFILES   1003
#define IDC_SETTINGS_AUDITIONSPAGE_ADDPROFILE   1004
#define IDC_SETTINGS_AUDITIONSPAGE_REMOVEPROFILE   1005
#define IDC_SETTINGS_AUDITIONSPAGE_REMOVEALLPROFILES   1006
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES   1007
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SOUND   1008
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SOUND_NONE   1009
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SOUND_SPEAKER   1010
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SOUND_BEEP   1011
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SOUND_BEEPFREQUENCY_STATIC   1012
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SOUND_BEEPFREQUENCY   1013
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SOUND_WAVE   1014
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SOUND_VOICE   1015
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS   1016
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_ADAPTER_STATIC   1017
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_ADAPTER   1018
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOLUME   1019
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOLUME_LEFT_STATIC   1020
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOLUME_LEFT   1021
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOLUME_RIGHT_STATIC   1022
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOLUME_RIGHT   1023
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_PLAYBACKRATE_STATIC   1024
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_PLAYBACKRATE   1025
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_PITCH_STATIC   1026
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_PITCH   1027
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_WAVE   1028
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_WAVE_FILENAME_STATIC   1029
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_WAVE_FILENAME   1030
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_WAVE_BROWSE   1031
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOICE   1032
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOICE_GENDER_STATIC   1033
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOICE_GENDER   1034
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOICE_AGE_STATIC   1035
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOICE_AGE  1036
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOICE_SPEAKER_STATIC   1037
#define IDC_SETTINGS_AUDITIONSPAGE_PROPERTIES_SETTINGS_VOICE_SPEAKER  1038

class CSettingsAuditionsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CSettingsAuditionsPage)

	// Construction
public:
	CSettingsAuditionsPage();

	// Attributes
private:
	CAuditionProfiles  m_pProfiles[2];

	// Dialog Data
	//{{AFX_DATA(CSettingsAuditionsPage)
	enum { IDD = IDD_SETTINGS_AUDITIONSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
private:
	VOID ShowProfileInfo();
	VOID SaveProfileInfo();
	CAuditionProfileInfo *FindProfileInfo() CONST;

	BOOL EnumVoiceSpeakers(WORD wGender, WORD wAge);

	BOOL FindDefaultSoundPath(LPCTSTR pszDirectory, CString &szPath) CONST;

	VOID AdjustToPrivileges();

public:
	class CSettingsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSettingsAuditionsPage)
public:
	virtual BOOL Initialize();
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
	//{{AFX_MSG(CSettingsAuditionsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnEditchangeProfile();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnAddProfile();
	afx_msg void OnRemoveProfile();
	afx_msg void OnRemoveAllProfiles();
	afx_msg void OnNoSound();
	afx_msg void OnSpeakerSound();
	afx_msg void OnBeepSound();
	afx_msg void OnWaveSound();
	afx_msg void OnVoiceSound();
	afx_msg void OnSelchangeAdapter();
	afx_msg void OnSpinchangeFrequency();
	afx_msg void OnEditchangeWave();
	afx_msg void OnBrowseWave();
	afx_msg void OnSelchangeVoiceGender();
	afx_msg void OnSelchangeVoiceAge();
	afx_msg void OnSelchangeVoiceSpeaker();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsNotificationsEMailDialog dialog

#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_DETAILS   1001
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_ATTACHMENT_STATIC   1002
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_ATTACHMENT   1003
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_ATTACHMENT_BROWSE   1004
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_ATTACHMENT_LIST   1005
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_ATTACHMENT_ADD   1006
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_ATTACHMENT_REMOVE   1007
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_PRIORITY_STATIC   1008
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_PRIORITY   1009
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_BEHAVIOR   1010
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_BEHAVIOR_RETRY   1011
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_BEHAVIOR_RETRY_STATIC   1012
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_BEHAVIOR_RETRY_NUMBER   1013
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_BEHAVIOR_RETRY_MINUTES_STATIC   1014
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_BEHAVIOR_RETRY_MINUTES_NUMBER   1015
#define IDC_SETTINGS_NOTIFICATIONSPAGE_EMAIL_HELP   1016

// Specify the e-mail notifications dialog related settings
#define NOTIFICATIONS_EMAIL_MINIMUMRETRIES   1
#define NOTIFICATIONS_EMAIL_MAXIMUMRETRIES   100
#define NOTIFICATIONS_EMAIL_DEFAULTRETRIES   2
#define NOTIFICATIONS_EMAIL_MINIMUMRETRYINTERVAL   1
#define NOTIFICATIONS_EMAIL_MAXIMUMRETRYINTERVAL   MINUTESPERDAY
#define NOTIFICATIONS_EMAIL_DEFAULTRETRYINTERVAL   5

class CSettingsNotificationsEMailDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CSettingsNotificationsEMailDialog)

	// Construction
public:
	CSettingsNotificationsEMailDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CNotificationProfileInfo  m_cProfileInfo[2];

	// Operations
public:
	VOID SetDetails(CONST CNotificationProfileInfo *pProfileInfo);
	VOID GetDetails(CNotificationProfileInfo *pProfileInfo) CONST;

private:
	BOOL EnumMailAttachments();
	BOOL EnumMailPriorities();

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CSettingsNotificationsEMailDialog)
	enum { IDD = IDD_SETTINGS_NOTIFICATIONSPAGE_EMAIL_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsNotificationsEMailDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsNotificationsEMailDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddAttachment();
	afx_msg void OnRemoveAttachment();
	afx_msg void OnBrowseAttachment();
	afx_msg void OnRetryNotification();
	afx_msg void OnEditchangeAttachment();
	afx_msg void OnSelchangePriority();
	afx_msg void OnSpinchangeRetryCount();
	afx_msg void OnSpinchangeRetryInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsNotificationsFAXDialog dialog

#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_DETAILS   1001
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTAREA_PROLOG_STATIC   1002
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTAREA   1003
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTAREA_EPILOG_STATIC   1004
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTNAME_STATIC   1005
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTNAME   1006
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTSTYLE_STATIC   1007
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTSTYLE   1008
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTSIZE_STATIC   1009
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTSIZE   1010
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTCOLOR_STATIC   1011
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTCOLOR   1012
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTSAMPLE   1013
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_FONTSAMPLE_AREA   1014
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_BEHAVIOR   1015
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_BEHAVIOR_RETRY   1016
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_BEHAVIOR_RETRY_STATIC   1017
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_BEHAVIOR_RETRY_NUMBER   1018
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_BEHAVIOR_RETRY_MINUTES_STATIC   1019
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_BEHAVIOR_RETRY_MINUTES_NUMBER   1020
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FAX_HELP   1021

// Specify the FAX notifications dialog related settings
#define NOTIFICATIONS_FAX_MINIMUMRETRIES   1
#define NOTIFICATIONS_FAX_MAXIMUMRETRIES   100
#define NOTIFICATIONS_FAX_DEFAULTRETRIES   2
#define NOTIFICATIONS_FAX_MINIMUMRETRYINTERVAL   1
#define NOTIFICATIONS_FAX_MAXIMUMRETRYINTERVAL   MINUTESPERDAY
#define NOTIFICATIONS_FAX_DEFAULTRETRYINTERVAL   5

class CSettingsNotificationsFAXDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CSettingsNotificationsFAXDialog)

	// Construction
public:
	CSettingsNotificationsFAXDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	LOGFONT  m_lfFonts[3];
	CString  m_szFontSampleText;
	COLORREF  m_nFontColors[3];
	CNotificationProfileInfo  m_cProfileInfo[2];

	// Operations
public:
	VOID SetDetails(CONST CNotificationProfileInfo *pProfileInfo);
	VOID GetDetails(CNotificationProfileInfo *pProfileInfo) CONST;

private:
	BOOL EnumFontAreaLocations();

	VOID ShowFontDetails();
	VOID ShowFontSample();

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CSettingsNotificationsFAXDialog)
	enum { IDD = IDD_SETTINGS_NOTIFICATIONSPAGE_FAX_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsNotificationsFAXDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsNotificationsFAXDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnRetryNotification();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeFontArea();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeFontColor();
	afx_msg void OnSpinchangeRetryCount();
	afx_msg void OnSpinchangeRetryInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsNotificationsPhoneCallDialog dialog

#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_DETAILS   1001
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_MODEM_STATIC   1002
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_MODEM   1003
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_CONVERSATION   1004
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_VOICE   1005
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_VOICE_GENDER_STATIC   1006
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_VOICE_GENDER   1007
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_VOICE_AGE_STATIC   1008
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_VOICE_AGE   1009
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_VOICE_SPEAKER_STATIC   1010
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_VOICE_SPEAKER   1011
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_BEHAVIOR   1012
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_BEHAVIOR_RETRY   1013
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_BEHAVIOR_RETRY_STATIC   1014
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_BEHAVIOR_RETRY_NUMBER   1015
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_BEHAVIOR_RETRY_MINUTES_STATIC   1016
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_BEHAVIOR_RETRY_MINUTES_NUMBER   1017
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_HELP   1018

// Specify the phone call notifications dialog related settings
#define NOTIFICATIONS_PHONECALL_MINIMUMRETRIES   1
#define NOTIFICATIONS_PHONECALL_MAXIMUMRETRIES   100
#define NOTIFICATIONS_PHONECALL_DEFAULTRETRIES   2
#define NOTIFICATIONS_PHONECALL_MINIMUMRETRYINTERVAL   1
#define NOTIFICATIONS_PHONECALL_MAXIMUMRETRYINTERVAL   MINUTESPERDAY
#define NOTIFICATIONS_PHONECALL_DEFAULTRETRYINTERVAL   5

class CSettingsNotificationsPhoneCallDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CSettingsNotificationsPhoneCallDialog)

	// Construction
public:
	CSettingsNotificationsPhoneCallDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CNotificationProfileInfo  m_cProfileInfo[2];

	// Operations
public:
	VOID SetDetails(CONST CNotificationProfileInfo *pProfileInfo);
	VOID GetDetails(CNotificationProfileInfo *pProfileInfo) CONST;

private:
	BOOL EnumModems();

	BOOL EnumVoiceGenders();
	BOOL EnumVoiceAges();
	BOOL EnumVoiceSpeakers(WORD wGender, WORD wAge);

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CSettingsNotificationsPhoneCallDialog)
	enum { IDD = IDD_SETTINGS_NOTIFICATIONSPAGE_PHONECALL_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsNotificationsPhoneCallDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsNotificationsPhoneCallDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnConversation();
	afx_msg void OnRetryNotification();
	afx_msg void OnSelchangeModem();
	afx_msg void OnSelchangeVoiceGender();
	afx_msg void OnSelchangeVoiceAge();
	afx_msg void OnSelchangeVoiceSpeaker();
	afx_msg void OnSpinchangeRetryCount();
	afx_msg void OnSpinchangeRetryInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsNotificationsPagerCallDialog dialog

#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_DETAILS   1001
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_MODEM_STATIC   1002
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_MODEM   1003
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_BEHAVIOR   1004
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_BEHAVIOR_ABORT_STATIC   1005
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_BEHAVIOR_ABORT_SECONDS_STATIC   1006
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_BEHAVIOR_ABORT_SECONDS   1007
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_BEHAVIOR_RETRY   1008
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_BEHAVIOR_RETRY_STATIC   1009
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_BEHAVIOR_RETRY_NUMBER   1010
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_BEHAVIOR_RETRY_MINUTES_STATIC   1011
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_BEHAVIOR_RETRY_MINUTES_NUMBER   1012
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_HELP   1013

// Specify the pager notifications dialog related settings
#define NOTIFICATIONS_PAGER_MINIMUMDISCONNECTTIME   1
#define NOTIFICATIONS_PAGER_MAXIMUMDISCONNECTTIME   SECONDSPERMINUTE
#define NOTIFICATIONS_PAGER_DEFAULTDISCONNECTTIME   15
#define NOTIFICATIONS_PAGER_MINIMUMRETRIES   1
#define NOTIFICATIONS_PAGER_MAXIMUMRETRIES   100
#define NOTIFICATIONS_PAGER_DEFAULTRETRIES   2
#define NOTIFICATIONS_PAGER_MINIMUMRETRYINTERVAL   1
#define NOTIFICATIONS_PAGER_MAXIMUMRETRYINTERVAL   MINUTESPERDAY
#define NOTIFICATIONS_PAGER_DEFAULTRETRYINTERVAL   5

class CSettingsNotificationsPagerCallDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CSettingsNotificationsPagerCallDialog)

	// Construction
public:
	CSettingsNotificationsPagerCallDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CNotificationProfileInfo  m_cProfileInfo[2];

	// Operations
public:
	VOID SetDetails(CONST CNotificationProfileInfo *pProfileInfo);
	VOID GetDetails(CNotificationProfileInfo *pProfileInfo) CONST;

private:
	BOOL EnumAllAvailableModems();

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CSettingsNotificationsPagerCallDialog)
	enum { IDD = IDD_SETTINGS_NOTIFICATIONSPAGE_PAGERCALL_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsNotificationsPagerCallDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsNotificationsPagerCallDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRetryNotification();
	afx_msg void OnSelchangeModem();
	afx_msg void OnSpinchangeDisconnectTime();
	afx_msg void OnSpinchangeRetryCount();
	afx_msg void OnSpinchangeRetryInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsNotificationsFTPMessageDialog dialog

#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_DETAILS   1001
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_LOCATION_STATIC   1002
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_LOCATION   1003
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_USERNAME_STATIC   1004
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_USERNAME   1005
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_LOGINNAME_STATIC   1006
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_LOGINNAME   1007
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_PASSWORD_STATIC   1008
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_PASSWORD   1009
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_PORT   1010
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_PORT_NUMBER   1011
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_BEHAVIOR   1012
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_BEHAVIOR_RETRY   1013
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_BEHAVIOR_RETRY_STATIC   1014
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_BEHAVIOR_RETRY_NUMBER   1015
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_BEHAVIOR_RETRY_MINUTES_STATIC   1016
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_BEHAVIOR_RETRY_MINUTES_NUMBER   1017
#define IDC_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_HELP   1018

// Specify the FTP message notifications dialog related settings
#define NOTIFICATIONS_FTPMESSAGE_FIRSTPORT   1
#define NOTIFICATIONS_FTPMESSAGE_LASTPORT   65535
#define NOTIFICATIONS_FTPMESSAGE_DEFAULTPORT   1024
#define NOTIFICATIONS_FTPMESSAGE_MINIMUMRETRIES   1
#define NOTIFICATIONS_FTPMESSAGE_MAXIMUMRETRIES   100
#define NOTIFICATIONS_FTPMESSAGE_DEFAULTRETRIES   2
#define NOTIFICATIONS_FTPMESSAGE_MINIMUMRETRYINTERVAL   1
#define NOTIFICATIONS_FTPMESSAGE_MAXIMUMRETRYINTERVAL   MINUTESPERDAY
#define NOTIFICATIONS_FTPMESSAGE_DEFAULTRETRYINTERVAL   5

class CSettingsNotificationsFTPMessageDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CSettingsNotificationsFTPMessageDialog)

	// Construction
public:
	CSettingsNotificationsFTPMessageDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CNotificationProfileInfo  m_cProfileInfo[2];

	// Operations
public:
	VOID SetDetails(CONST CNotificationProfileInfo *pProfileInfo);
	VOID GetDetails(CNotificationProfileInfo *pProfileInfo) CONST;

private:
	BOOL CheckURL(LPCTSTR pszLocation) CONST;

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CSettingsNotificationsFTPMessageDialog)
	enum { IDD = IDD_SETTINGS_NOTIFICATIONSPAGE_FTPMESSAGE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsNotificationsFTPMessageDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsNotificationsFTPMessageDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnUseFTPPort();
	afx_msg void OnRetryNotification();
	afx_msg void OnEditchangeFTPLoginName();
	afx_msg void OnEditchangeFTPLocation();
	afx_msg void OnEditchangeFTPPassword();
	afx_msg void OnSelchangeFTPUserName();
	afx_msg void OnSpinchangeFTPPort();
	afx_msg void OnSpinchangeRetryCount();
	afx_msg void OnSpinchangeRetryInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsNotificationsPrinterMessageDialog dialog

#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_DETAILS   1001
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTAREA_PROLOG_STATIC   1002
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTAREA   1003
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTAREA_EPILOG_STATIC   1004
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTNAME_STATIC   1005
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTNAME   1006
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTSTYLE_STATIC   1007
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTSTYLE   1008
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTSIZE_STATIC   1009
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTSIZE   1010
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTCOLOR_STATIC   1011
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTCOLOR   1012
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTSAMPLE   1013
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_FONTSAMPLE_AREA   1014
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_BEHAVIOR   1015
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_BEHAVIOR_RETRY   1016
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_BEHAVIOR_RETRY_STATIC   1017
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_BEHAVIOR_RETRY_NUMBER   1018
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_BEHAVIOR_RETRY_MINUTES_STATIC   1019
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_BEHAVIOR_RETRY_MINUTES_NUMBER   1020
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_HELP   1021

// Specify the printer message notifications dialog related settings
#define NOTIFICATIONS_PRINTERMESSAGE_MINIMUMRETRIES   1
#define NOTIFICATIONS_PRINTERMESSAGE_MAXIMUMRETRIES   100
#define NOTIFICATIONS_PRINTERMESSAGE_DEFAULTRETRIES   2
#define NOTIFICATIONS_PRINTERMESSAGE_MINIMUMRETRYINTERVAL   1
#define NOTIFICATIONS_PRINTERMESSAGE_MAXIMUMRETRYINTERVAL   MINUTESPERDAY
#define NOTIFICATIONS_PRINTERMESSAGE_DEFAULTRETRYINTERVAL   5

class CSettingsNotificationsPrinterMessageDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CSettingsNotificationsPrinterMessageDialog)

	// Construction
public:
	CSettingsNotificationsPrinterMessageDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	LOGFONT  m_lfFonts[3];
	CString  m_szFontSampleText;
	COLORREF  m_nFontColors[3];
	CNotificationProfileInfo  m_cProfileInfo[2];

	// Operations
public:
	VOID SetDetails(CONST CNotificationProfileInfo *pProfileInfo);
	VOID GetDetails(CNotificationProfileInfo *pProfileInfo) CONST;

private:
	BOOL EnumFontAreaLocations();

	VOID ShowFontDetails();
	VOID ShowFontSample();

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CSettingsNotificationsPrinterMessageDialog)
	enum { IDD = IDD_SETTINGS_NOTIFICATIONSPAGE_PRINTERMESSAGE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsNotificationsPrinterMessageDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingsNotificationsPrinterMessageDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnRetryNotification();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeFontArea();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeFontColor();
	afx_msg void OnSpinchangeRetryCount();
	afx_msg void OnSpinchangeRetryInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsNotificationsAbortDialog dialog

#define IDC_SETTINGS_NOTIFICATIONSPAGE_ABORT_DETAILS  1001
#define IDC_SETTINGS_NOTIFICATIONSPAGE_ABORT_LIST_STATIC  1002
#define IDC_SETTINGS_NOTIFICATIONSPAGE_ABORT_LIST   1003
#define IDC_SETTINGS_NOTIFICATIONSPAGE_ABORT_HELP   1004

class CSettingsNotificationsAbortDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CSettingsNotificationsAbortDialog)

	// Construction
public:
	CSettingsNotificationsAbortDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CNotificationProfiles  m_pProfiles;
private:
	CStringArray  m_szColumns;

	// Operations
private:
	BOOL EnumJobs();

	INT CalcColumnWidth(LPCTSTR pszColumn);

	// Dialog Data
	//{{AFX_DATA(CSettingsNotificationsAbortDialog)
	enum { IDD = IDD_SETTINGS_NOTIFICATIONSPAGE_ABORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsNotificationsAbortDialog)
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
	//{{AFX_MSG(CSettingsNotificationsAbortDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsNotificationsPage dialog

#define IDC_SETTINGS_NOTIFICATIONSPAGE_DETAILS   1001
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROFILES_STATIC   1002
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROFILES   1003
#define IDC_SETTINGS_NOTIFICATIONSPAGE_ADDPROFILE   1004
#define IDC_SETTINGS_NOTIFICATIONSPAGE_REMOVEPROFILE   1005
#define IDC_SETTINGS_NOTIFICATIONSPAGE_REMOVEALLPROFILES   1006
#define IDC_SETTINGS_NOTIFICATIONSPAGE_ABORTPROFILE   1007
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES   1008
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_ALERT   1009
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_ALERT_NONE   1010
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_ALERT_EMAIL   1011
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_ALERT_FAX   1012
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_ALERT_PHONECALL   1013
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_ALERT_PAGERCALL   1014
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_ALERT_VOIPCALL   1015
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_ALERT_FTPMESSAGE   1016
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_ALERT_PRINTERMESSAGE   1017
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_AUDIT_STATIC   1018
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_AUDIT_NOTHING   1019
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_AUDIT_EVERYTHING   1020
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_AUDIT_FAILURES   1021
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_DETAILS   1022
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_MESSAGE   1023
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_MESSAGE_PROLOG_STATIC   1024
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_MESSAGE_PROLOG   1025
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_MESSAGE_EPILOG_STATIC   1026
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_MESSAGE_EPILOG   1027
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_RECIPIENTS   1028
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_RECIPIENTS_LIST   1029
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_RECIPIENTS_ADD   1030
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_RECIPIENTS_REMOVE   1031
#define IDC_SETTINGS_NOTIFICATIONSPAGE_PROPERTIES_RECIPIENTS_REMOVEALL   1032

class CSettingsNotificationsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CSettingsNotificationsPage)

	// Construction
public:
	CSettingsNotificationsPage();

	// Attributes
private:
	CUserProfiles  m_pUsers[2];
	CNotificationProfiles  m_pProfiles[2];
	CNotificationProfileInfo  m_cProfileInfo[6];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CSettingsNotificationsPage)
	enum { IDD = IDD_SETTINGS_NOTIFICATIONSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
private:
	VOID ShowProfileInfo();
	VOID SaveProfileInfo();
	CNotificationProfileInfo *FindProfileInfo() CONST;

	VOID GetDefaultEMailProperties(CNotificationProfileInfo *pProfileInfo) CONST;
	VOID GetDefaultFAXProperties(CNotificationProfileInfo *pProfileInfo) CONST;
	VOID GetDefaultPhoneCallProperties(CNotificationProfileInfo *pProfileInfo) CONST;
	VOID GetDefaultPagerCallProperties(CNotificationProfileInfo *pProfileInfo) CONST;
	VOID GetDefaultFTPMessageProperties(CNotificationProfileInfo *pProfileInfo) CONST;
	VOID GetDefaultPrinterMessageProperties(CNotificationProfileInfo *pProfileInfo) CONST;
	CString GetDefaultModemName() CONST;

	BOOL CheckRecipients(CONST CNotificationProfileInfo *pProfileInfo) CONST;
	BOOL CheckRecipients() CONST;

	VOID AdjustToPrivileges();

public:
	class CSettingsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSettingsNotificationsPage)
public:
	virtual BOOL Initialize();
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
	//{{AFX_MSG(CSettingsNotificationsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeProfile();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnAddProfile();
	afx_msg void OnRemoveProfile();
	afx_msg void OnRemoveAllProfiles();
	afx_msg void OnAbortProfile();
	afx_msg void OnNone();
	afx_msg void OnEMail();
	afx_msg void OnFAX();
	afx_msg void OnPhoneCall();
	afx_msg void OnPagerCall();
	afx_msg void OnFTPMessage();
	afx_msg void OnPrinterMessage();
	afx_msg void OnAuditNothing();
	afx_msg void OnAuditEverything();
	afx_msg void OnAuditFailures();
	afx_msg void OnDetails();
	afx_msg void OnAddRecipient();
	afx_msg void OnRemoveRecipient();
	afx_msg void OnRemoveAllRecipients();
	afx_msg void OnEditchangeProlog();
	afx_msg void OnEditchangeEpilog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsMiscellaneousPage dialog

#define IDC_SETTINGS_MISCELLANEOUSPAGE_DETAILS   1001
#define IDC_SETTINGS_MISCELLANEOUSPAGE_SERVICES   1002
#define IDC_SETTINGS_MISCELLANEOUSPAGE_SERVICES_TELEMETRY   1003
#define IDC_SETTINGS_MISCELLANEOUSPAGE_SERVICES_TELECOMMAND   1004
#define IDC_SETTINGS_MISCELLANEOUSPAGE_SERVICES_MEMORYDUMPS   1005
#define IDC_SETTINGS_MISCELLANEOUSPAGE_SERVICES_TPEP   1006
#define IDC_SETTINGS_MISCELLANEOUSPAGE_SERVICES_PFLP   1007
#define IDC_SETTINGS_MISCELLANEOUSPAGE_SERVICES_AUTOMATION   1008
#define IDC_SETTINGS_MISCELLANEOUSPAGE_ALERTS   1009
#define IDC_SETTINGS_MISCELLANEOUSPAGE_ALERTS_SYSTEM   1010
#define IDC_SETTINGS_MISCELLANEOUSPAGE_EVENTS   1011
#define IDC_SETTINGS_MISCELLANEOUSPAGE_EVENTS_TELEMETRY   1012
#define IDC_SETTINGS_MISCELLANEOUSPAGE_REPORTS   1013
#define IDC_SETTINGS_MISCELLANEOUSPAGE_REPORTS_TELEMETRY   1014
#define IDC_SETTINGS_MISCELLANEOUSPAGE_PROFILES   1015
#define IDC_SETTINGS_MISCELLANEOUSPAGE_PROFILES_PRINTING   1016
#define IDC_SETTINGS_MISCELLANEOUSPAGE_PROFILES_AUDITIONS   1017
#define IDC_SETTINGS_MISCELLANEOUSPAGE_PROFILES_NOTIFICATIONS   1018
#define IDC_SETTINGS_MISCELLANEOUSPAGE_PROFILES_DOWNLOADS   1019
#define IDC_SETTINGS_MISCELLANEOUSPAGE_SCHEDULES   1020
#define IDC_SETTINGS_MISCELLANEOUSPAGE_SCHEDULES_LOGIN   1021
#define IDC_SETTINGS_MISCELLANEOUSPAGE_DOUPDATE   1022
#define IDC_SETTINGS_MISCELLANEOUSPAGE_IMPORT   1023
#define IDC_SETTINGS_MISCELLANEOUSPAGE_IMPORT_FILENAME   1024
#define IDC_SETTINGS_MISCELLANEOUSPAGE_IMPORT_BROWSE   1025
#define IDC_SETTINGS_MISCELLANEOUSPAGE_EXPORT   1026
#define IDC_SETTINGS_MISCELLANEOUSPAGE_EXPORT_FILENAME   1027
#define IDC_SETTINGS_MISCELLANEOUSPAGE_EXPORT_BROWSE   1028
#define IDC_SETTINGS_MISCELLANEOUSPAGE_DOIMPORT   1029
#define IDC_SETTINGS_MISCELLANEOUSPAGE_DOEXPORT   1030
#define IDC_SETTINGS_MISCELLANEOUSPAGE_RESULTS_STATIC   1031
#define IDC_SETTINGS_MISCELLANEOUSPAGE_RESULTS   1032

class CSettingsMiscellaneousPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CSettingsMiscellaneousPage)

	// Construction
public:
	CSettingsMiscellaneousPage();

	// Attributes
private:
	typedef struct tagAPPLICATIONDATA {
		INT  cbSize;
		INT  cbLoginSchedule;
		INT  cbTelemetryService;
		INT  cbTelecommandService;
		INT  cbMemoryDumpsService;
		INT  cbTPEPService;
		INT  cbPFLPService;
		INT  cbAutomationService;
		INT  cbSystemAlerts;
		INT  cbTelemetryEvents;
		INT  cbTelemetryReports;
		INT  cbPrintProfiles;
		INT  cbAuditionProfiles;
		INT  cbDownloadProfiles;
		INT  cbNotificationProfiles;
		INT  cbTelemetryReportProfiles;
	} APPLICATIONDATA, *PAPPLICATIONDATA, *LPAPPLICATIONDATA;

	// Dialog Data
	//{{AFX_DATA(CSettingsMiscellaneousPage)
	enum { IDD = IDD_SETTINGS_MISCELLANEOUSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
private:
	BOOL WriteExportFile(LPCTSTR pszFileName, CONST CByteArray &nLoginSchedule, CONST CByteArray &nTelemetryService, CONST CByteArray &nTelecommandService, CONST CByteArray &nMemoryDumpsService, CONST CByteArray &nTPEPService, CONST CByteArray &nPFLPService, CONST CByteArray &nAutomationService, CONST CByteArray &nSystemAlerts, CONST CByteArray &nTelemetryEvents, CONST CByteArray &nTelemetryReports, CONST CByteArray &nTelemetryReportProfiles, CONST CByteArray &nPrintProfiles, CONST CByteArray &nAuditionProfiles, CONST CByteArray &nNotificationProfiles, CONST CByteArray &nDownloadProfiles);
	BOOL ReadImportFile(LPCTSTR pszFileName, CByteArray &nLoginSchedule, CByteArray &nTelemetryService, CByteArray &nTelecommandService, CByteArray &nMemoryDumpsService, CByteArray &nTPEPService, CByteArray &nPFLPService, CByteArray &nAutomationService, CByteArray &nSystemAlerts, CByteArray &nTelemetryEvents, CByteArray &nTelemetryReports, CByteArray &nTelemetryReportProfiles, CByteArray &nPrintProfiles, CByteArray &nAuditionProfiles, CByteArray &nNotificationProfiles, CByteArray &nDownloadProfiles) CONST;

	BOOL CanUpdate() CONST;
	BOOL CanImport() CONST;
	BOOL CanExport() CONST;

public:
	class CSettingsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSettingsMiscellaneousPage)
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
	//{{AFX_MSG(CSettingsMiscellaneousPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTelemetryService();
	afx_msg void OnTelecommandService();
	afx_msg void OnMemoryDumpsService();
	afx_msg void OnTPEPService();
	afx_msg void OnPFLPService();
	afx_msg void OnAutomationService();
	afx_msg void OnSystemAlerts();
	afx_msg void OnTelemetryEvents();
	afx_msg void OnTelemetryReports();
	afx_msg void OnPrintProfiles();
	afx_msg void OnAuditionProfiles();
	afx_msg void OnNotificationProfiles();
	afx_msg void OnDownloadProfiles();
	afx_msg void OnLoginSchedule();
	afx_msg void OnImport();
	afx_msg void OnExport();
	afx_msg void OnImportBrowse();
	afx_msg void OnExportBrowse();
	afx_msg void OnDoImport();
	afx_msg void OnDoExport();
	afx_msg void OnDoUpdate();
	afx_msg void OnEditchangeImportFileName();
	afx_msg void OnEditchangeExportFileName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsTabCtrl window

class CSettingsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CSettingsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CSettingsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSettingsTabCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSettingsDialog

class CSettingsDialog : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CSettingsDialog)

	// Construction
public:
	CSettingsDialog(CWnd *pParentWnd = NULL);

	// Attributes
public:
	CSettingsTabCtrl  m_wndTabCtrl;
	CSettingsDisplayAreaPage  m_pageDisplayArea;
	CSettingsEventLogsPage  m_pageEventLogs;
	CSettingsPrintingPage  m_pagePrinting;
	CSettingsAuditionsPage  m_pageAudition;
	CSettingsNotificationsPage  m_pageNotifications;
	CSettingsMiscellaneousPage  m_pageMiscellaneous;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDialog)
public:
	virtual BOOL CheckPageAccessibility(INT nIndex) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSettingsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAccountsDialog dialog

#define IDC_ACCOUNTS_DETAILS   1001
#define IDC_ACCOUNTS_COMPUTERNAME_STATIC   1002
#define IDC_ACCOUNTS_COMPUTERNAME   1003
#define IDC_ACCOUNTS_CONNECT   1004
#define IDC_ACCOUNTS_SPACECRAFTNAME_STATIC   1005
#define IDC_ACCOUNTS_SPACECRAFTNAME   1006
#define IDC_ACCOUNTS_USERNAME_STATIC   1007
#define IDC_ACCOUNTS_USERNAME   1008
#define IDC_ACCOUNTS_CREATE   1009
#define IDC_ACCOUNTS_DELETE   1010
#define IDC_ACCOUNTS_PRIVILEGES   1011
#define IDC_ACCOUNTS_GROUPMEMBER_STATIC   1012
#define IDC_ACCOUNTS_GROUPMEMBER   1013
#define IDC_ACCOUNTS_DATABASES   1014
#define IDC_ACCOUNTS_PROFILES   1015
#define IDC_ACCOUNTS_PROFILES_ADMINISTRATORS   1016
#define IDC_ACCOUNTS_PROFILES_OPERATORS   1017
#define IDC_ACCOUNTS_PROFILES_USERS   1018
#define IDC_ACCOUNTS_PROFILES_GUESTS   1019
#define IDC_ACCOUNTS_PROFILES_CUSTOM   1020
#define IDC_ACCOUNTS_UNIQUE_USER   1021
#define IDC_ACCOUNTS_RIGHTS_STATIC   1022
#define IDC_ACCOUNTS_RIGHTS    1023
#define IDC_ACCOUNTS_RIGHTS_CHANGE   1024
#define IDC_ACCOUNTS_PASSWORD   1025
#define IDC_ACCOUNTS_PASSWORD_NONE   1026
#define IDC_ACCOUNTS_PASSWORD_USE   1027
#define IDC_ACCOUNTS_PASSWORD_CONTENTS   1028
#define IDC_ACCOUNTS_PASSWORD_CONFIRMATION_STATIC   1029
#define IDC_ACCOUNTS_PASSWORD_CONFIRMATION   1030
#define IDC_ACCOUNTS_VALIDITY   1031
#define IDC_ACCOUNTS_VALIDITY_UNLIMITED   1032
#define IDC_ACCOUNTS_VALIDITY_LIMITED   1033
#define IDC_ACCOUNTS_VALIDITY_DAYS    1034
#define IDC_ACCOUNTS_VALIDITY_DAYS_STATIC   1035
#define IDC_ACCOUNTS_VALIDITY_DATE_STATIC   1036
#define IDC_ACCOUNTS_VALIDITY_DATE_NONE   1037
#define IDC_ACCOUNTS_VALIDITY_DATE   1038
#define IDC_ACCOUNTS_HELP   1039

// Specify the accounts dialog related flags
#define ACCOUNTS_TYPE_NEW   0
#define ACCOUNTS_TYPE_OLD   1
#define ACCOUNTS_TYPE_ANY   2
// Specify the accounts dialog related settings
#define ACCOUNTS_MINIMUMVALIDITY   1
#define ACCOUNTS_MAXIMUMVALIDITY   (4*365+1)
#define ACCOUNTS_DEFAULTVALIDITY   30

class CAccountsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CAccountsDialog)

	// Construction
public:
	CAccountsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CPtrArray  m_pDatabases[2];
	CStringArray  m_szDatabases;
	CAccountTokens  m_pAccounts[2];
	CUIntArray  m_nPrivileges;

	// Dialog Data
	//{{AFX_DATA(CAccountsDialog)
	enum { IDD = IDD_ACCOUNTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumComputers();
	BOOL EnumSpacecrafts();
	BOOL EnumUsers();
	BOOL EnumGroups();
	BOOL EnumRights();
	BOOL EnumRights(UINT nRights);
	BOOL EnumRights(CONST CUIntArray &nRights);
	BOOL EnumDatabases();

	INT EnumAccounts(LPCTSTR pszPath, CStringArray &szAccounts);
	BOOL TestAccount(LPCTSTR pszAccount, CString &szName);

	BOOL SaveAccountInfo(BOOL bUpdate = FALSE);
	BOOL UpdateAccountInfo();
	VOID ShowAccountInfo();
	BOOL CheckAccountInfo() CONST;
	BOOL DeleteAccountInfo();

	CAccountToken *FindAccount(UINT nType = ACCOUNTS_TYPE_NEW) CONST;
	CDatabaseProfiles *FindDatabases(UINT nType = ACCOUNTS_TYPE_NEW) CONST;

	BOOL CheckPrivilegeProfile(UINT nProfile, CONST CUIntArray &nPrivileges) CONST;
	BOOL CheckPrivileges(UINT nPrivilege = 0) CONST;
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountsDialog)
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
	//{{AFX_MSG(CAccountsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComputerName();
	afx_msg void OnSelchangeSpacecraftName();
	afx_msg void OnSelchangeUserName();
	afx_msg void OnEditchangeComputerName();
	afx_msg void OnEditchangeUserName();
	afx_msg void OnConnectComputer();
	afx_msg void OnCreateAccount();
	afx_msg void OnDeleteAccount();
	afx_msg void OnAdministratorsProfile();
	afx_msg void OnOperatorsProfile();
	afx_msg void OnUsersProfile();
	afx_msg void OnGuestsProfile();
	afx_msg void OnAccountDatabases();
	afx_msg void OnAccountRights();
	afx_msg void OnAccountUniqueUser();
	afx_msg void OnAccountPasswordNone();
	afx_msg void OnAccountPasswordUse();
	afx_msg void OnAccountValidity();
	afx_msg void OnEditchangeAccountPassword();
	afx_msg void OnSpinchangeAccountDays();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAccountDatabaseDialog dialog

#define IDC_ACCOUNTDATABASE_DETAILS   1001
#define IDC_ACCOUNTDATABASE_SERVER_STATIC   1002
#define IDC_ACCOUNTDATABASE_SERVER   1003
#define IDC_ACCOUNTDATABASE_CONNECT   1004
#define IDC_ACCOUNTDATABASE_USER_STATIC   1005
#define IDC_ACCOUNTDATABASE_USER   1006
#define IDC_ACCOUNTDATABASE_NAME_STATIC   1007
#define IDC_ACCOUNTDATABASE_NAME   1008
#define IDC_ACCOUNTDATABASE_ALLOWEDLIST_STATIC   1009
#define IDC_ACCOUNTDATABASE_ALLOWEDLIST   1010
#define IDC_ACCOUNTDATABASE_ADD   1011
#define IDC_ACCOUNTDATABASE_REMOVE   1012
#define IDC_ACCOUNTDATABASE_REMOVEALL   1013
#define IDC_ACCOUNTDATABASE_HELP   1014

class CAccountDatabaseDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CAccountDatabaseDialog)

	// Construction
public:
	CAccountDatabaseDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CAccountToken  m_cAccountToken;
	CDatabaseProfiles  m_pDatabases[3];

	// Dialog Data
	//{{AFX_DATA(CAccountDatabaseDialog)
	enum { IDD = IDD_ACCOUNTDATABASE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumServers();
	BOOL EnumDatabases();
	BOOL EnumUserDatabases();
	BOOL EnumUser();

	VOID ShowDatabaseInfo();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountDatabaseDialog)
public:
	virtual INT DoModal(CAccountToken *pAccountToken, CDatabaseProfiles *pDatabases);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAccountDatabaseDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnConnect();
	afx_msg void OnAddDatabase();
	afx_msg void OnRemoveDatabase();
	afx_msg void OnRemoveAllDatabases();
	afx_msg void OnEditchangeServer();
	afx_msg void OnSelchangeServer();
	afx_msg void OnSelchangeDatabase();
	afx_msg void OnSelchangeUserDatabase();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAccountChangeDialog dialog

#define IDC_ACCOUNTCHANGE_DETAILS   1001
#define IDC_ACCOUNTCHANGE_COMPUTERNAME_STATIC   1002
#define IDC_ACCOUNTCHANGE_COMPUTERNAME   1003
#define IDC_ACCOUNTCHANGE_SPACECRAFTNAME_STATIC   1004
#define IDC_ACCOUNTCHANGE_SPACECRAFTNAME   1005
#define IDC_ACCOUNTCHANGE_USERNAME_STATIC   1006
#define IDC_ACCOUNTCHANGE_USERNAME   1007
#define IDC_ACCOUNTCHANGE_DATABASE_STATIC  1008
#define IDC_ACCOUNTCHANGE_DATABASE   1009
#define IDC_ACCOUNTCHANGE_MODE   1010
#define IDC_ACCOUNTCHANGE_MODE_ONLINE   1011
#define IDC_ACCOUNTCHANGE_MODE_OFFLINE   1012
#define IDC_ACCOUNTCHANGE_PASSWORD_STATIC   1013
#define IDC_ACCOUNTCHANGE_PASSWORD   1014
#define IDC_ACCOUNTCHANGE_VALIDITY_LIFETIME   1015
#define IDC_ACCOUNTCHANGE_VALIDITY_UNLIMITED   1016
#define IDC_ACCOUNTCHANGE_VALIDITY_LIMITED   1017
#define IDC_ACCOUNTCHANGE_VALIDITY_EXPIRATION   1018
#define IDC_ACCOUNTCHANGE_REMOTENETWORK   1019
#define IDC_ACCOUNTCHANGE_REMOTENETWORK_SERVER_STATIC   1020
#define IDC_ACCOUNTCHANGE_REMOTENETWORK_SERVER   1021
#define IDC_ACCOUNTCHANGE_REMOTENETWORK_USER_STATIC   1022
#define IDC_ACCOUNTCHANGE_REMOTENETWORK_USER   1023
#define IDC_ACCOUNTCHANGE_REMOTENETWORK_PASSWORD_STATIC   1024
#define IDC_ACCOUNTCHANGE_REMOTENETWORK_PASSWORD   1025
#define IDC_ACCOUNTCHANGE_REMOTENETWORK_DIALUP   1026
#define IDC_ACCOUNTCHANGE_REMOTENETWORK_OPTIONS   1027
#define IDC_ACCOUNTCHANGE_HELP   1028

class CAccountChangeDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CAccountChangeDialog)

	// Construction
public:
	CAccountChangeDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CAccountTokens  m_pAccounts;
	CServerProfiles  m_pServers;
	CDatabaseProfiles  m_pDatabases[2];
	CLoginOptions  m_pLoginOptions[2];

	// Dialog Data
	//{{AFX_DATA(CAccountChangeDialog)
	enum { IDD = IDD_ACCOUNTCHANGE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumComputers();
	BOOL EnumSpacecrafts();
	BOOL EnumUsers();
	BOOL EnumDatabases();
	BOOL EnumServers();
	BOOL EnumLogins();

	BOOL ShowAccountInfo();

	INT FindAccount() CONST;
	INT FindAccount(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName) CONST;
	CAccountToken *GetAccount(INT nIndex = 0) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountChangeDialog)
public:
	virtual INT DoModal(CAccountToken *pAccountToken);
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
	//{{AFX_MSG(CAccountChangeDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeSpacecraftName();
	afx_msg void OnSelchangeUserName();
	afx_msg void OnSelchangeDatabase();
	afx_msg void OnSelchangeNetworkServer();
	afx_msg void OnEditchangePassword();
	afx_msg void OnEditchangeNetworkServer();
	afx_msg void OnEditchangeNetworkUser();
	afx_msg void OnEditchangeNetworkPassword();
	afx_msg void OnOnlineMode();
	afx_msg void OnOfflineMode();
	afx_msg void OnOptions();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAccountDirectoryDialog dialog

#define IDC_ACCOUNTDIRECTORY_DETAILS   1001
#define IDC_ACCOUNTDIRECTORY_COMPUTERNAME_STATIC   1002
#define IDC_ACCOUNTDIRECTORY_COMPUTERNAME   1003
#define IDC_ACCOUNTDIRECTORY_SPACECRAFTNAME_STATIC   1004
#define IDC_ACCOUNTDIRECTORY_SPACECRAFTNAME   1005
#define IDC_ACCOUNTDIRECTORY_USERS_STATIC   1006
#define IDC_ACCOUNTDIRECTORY_USERS   1007
#define IDC_ACCOUNTDIRECTORY_HELP   1008

class CAccountDirectoryDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CAccountDirectoryDialog)

	// Construction
public:
	CAccountDirectoryDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CStringArray  m_szUsers;

	// Dialog Data
	//{{AFX_DATA(CAccountDirectoryDialog)
	enum { IDD = IDD_ACCOUNTDIRECTORY_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountDirectoryDialog)
public:
	virtual INT DoModal(CStringArray &szUsers);
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAccountDirectoryDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeUsers();
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
// CPasswordDialog dialog

#define IDC_PASSWORD_DETAILS   1001
#define IDC_PASSWORD_COMMENT   1002
#define IDC_PASSWORD_TIP   1003
#define IDC_PASSWORD_CONTENTS_STATIC   1004
#define IDC_PASSWORD_CONTENTS   1005
#define IDC_PASSWORD_HELP   1006

class CPasswordDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CPasswordDialog)

	// Construction
public:
	CPasswordDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szFacility;
	CString  m_szPassword;

	// Dialog Data
	//{{AFX_DATA(CPasswordDialog)
	enum { IDD = IDD_PASSWORD_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPasswordDialog)
public:
	virtual INT DoModal(LPCTSTR pszFacility, LPCTSTR pszPassword);
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPasswordDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangePassword();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPrivilegesDialog dialog

#define IDC_PRIVILEGES_DETAILS   1001
#define IDC_PRIVILEGES_NAME_STATIC   1002
#define IDC_PRIVILEGES_NAME   1003
#define IDC_PRIVILEGES_POLICY   1004
#define IDC_PRIVILEGES_RIGHTS_STATIC   1005
#define IDC_PRIVILEGES_RIGHTS   1006
#define IDC_PRIVILEGES_RIGHTSGRANTED_STATIC   1007
#define IDC_PRIVILEGES_RIGHTSGRANTED   1008
#define IDC_PRIVILEGES_RIGHTSALLOW   1009
#define IDC_PRIVILEGES_RIGHTSDENY   1010
#define IDC_PRIVILEGES_HELP   1011

class CPrivilegesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CPrivilegesDialog)

	// Construction
public:
	CPrivilegesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CAccountTokens  m_pAccounts;

	// Dialog Data
	//{{AFX_DATA(CPrivilegesDialog)
	enum { IDD = IDD_PRIVILEGES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	UINT QueryRights() CONST;
	UINT QueryGrantedRights() CONST;

	CAccountToken *GetAccount(BOOL bBackup = FALSE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrivilegesDialog)
public:
	virtual INT DoModal(CAccountToken *pAccountToken);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrivilegesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeRights();
	afx_msg void OnSelchangeRightsGranted();
	afx_msg void OnRightsAllow();
	afx_msg void OnRightsDeny();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
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
// CSystemAlertsDialog

#define IDC_SYSTEMALERTS_DETAILS   1001
#define IDC_SYSTEMALERTS_EVENT_STATIC   1002
#define IDC_SYSTEMALERTS_EVENT   1003
#define IDC_SYSTEMALERTS_DESCRIPTION_STATIC   1004
#define IDC_SYSTEMALERTS_DESCRIPTION   1005
#define IDC_SYSTEMALERTS_BEHAVIOR   1006
#define IDC_SYSTEMALERTS_BEHAVIOR_AUDITION_STATIC   1007
#define IDC_SYSTEMALERTS_BEHAVIOR_AUDITION   1008
#define IDC_SYSTEMALERTS_BEHAVIOR_NOTIFICATIONS_STATIC   1009
#define IDC_SYSTEMALERTS_BEHAVIOR_NOTIFICATIONS_LIST   1010
#define IDC_SYSTEMALERTS_BEHAVIOR_NOTIFICATIONS   1011
#define IDC_SYSTEMALERTS_BEHAVIOR_NOTIFICATION_ADD   1012
#define IDC_SYSTEMALERTS_BEHAVIOR_NOTIFICATION_REMOVE   1013
#define IDC_SYSTEMALERTS_BEHAVIOR_MESSAGE_STATIC   1014
#define IDC_SYSTEMALERTS_BEHAVIOR_MESSAGE   1015
#define IDC_SYSTEMALERTS_HELP   1016

class CSystemAlertsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CSystemAlertsDialog)

	// Construction
public:
	CSystemAlertsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CSystemAlerts  m_pAlerts[2];

	// Dialog Data
	//{{AFX_DATA(CSystemAlertsDialog)
	enum { IDD = IDD_SYSTEMALERTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumAlerts();
	BOOL EnumAuditions();
	BOOL EnumNotifications();

	VOID ShowAlertInfo();

	CSystemAlertInfo *FindAlertInfo() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemAlertsDialog)
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

	//{{AFX_MSG(CSystemAlertsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddNotification();
	afx_msg void OnRemoveNotification();
	afx_msg void OnEditchangeMessage();
	afx_msg void OnSelchangeEvent();
	afx_msg void OnSelchangeAudition();
	afx_msg void OnSelchangeNotification();
	afx_msg void OnSelchangeNotificationList();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAutomationServiceDialog

#define IDC_AUTOMATIONSERVICE_DETAILS   1001
#define IDC_AUTOMATIONSERVICE_PORT_STATIC   1002
#define IDC_AUTOMATIONSERVICE_PORT   1003
#define IDC_AUTOMATIONSERVICE_TIMEOUT_STATIC   1004
#define IDC_AUTOMATIONSERVICE_TIMEOUT   1005
#define IDC_AUTOMATIONSERVICE_TIMEOUT_SECONDS   1006
#define IDC_AUTOMATIONSERVICE_BUFFER_STATIC   1007
#define IDC_AUTOMATIONSERVICE_BUFFER   1008
#define IDC_AUTOMATIONSERVICE_BUFFER_KB   1009
#define IDC_AUTOMATIONSERVICE_DISABLED   1010
#define IDC_AUTOMATIONSERVICE_CLIENTS   1011
#define IDC_AUTOMATIONSERVICE_CLIENT_USERNAME_STATIC   1012
#define IDC_AUTOMATIONSERVICE_CLIENT_USERNAME   1013
#define IDC_AUTOMATIONSERVICE_CLIENT_PASSWORD_STATIC   1014
#define IDC_AUTOMATIONSERVICE_CLIENT_PASSWORD   1015
#define IDC_AUTOMATIONSERVICE_CLIENT_PASSWORD_CONFIRMATION_STATIC   1016
#define IDC_AUTOMATIONSERVICE_CLIENT_PASSWORD_CONFIRMATION   1017
#define IDC_AUTOMATIONSERVICE_CLIENT_ENCRYPT   1018
#define IDC_AUTOMATIONSERVICE_CLIENT_BAN   1019
#define IDC_AUTOMATIONSERVICE_CLIENT_LIST   1020
#define IDC_AUTOMATIONSERVICE_CLIENT_ADD   1021
#define IDC_AUTOMATIONSERVICE_CLIENT_MODIFY   1022
#define IDC_AUTOMATIONSERVICE_CLIENT_REMOVE   1023
#define IDC_AUTOMATIONSERVICE_CLIENT_REMOVEALL   1024
#define IDC_AUTOMATIONSERVICE_CLIENT_PERMISSIONS   1025
#define IDC_AUTOMATIONSERVICE_CLIENT_PERMISSIONS_ALL   1026
#define IDC_AUTOMATIONSERVICE_CLIENT_PERMISSIONS_GRANTED_STATIC   1027
#define IDC_AUTOMATIONSERVICE_CLIENT_PERMISSIONS_GRANTED   1028
#define IDC_AUTOMATIONSERVICE_CLIENT_PERMISSION_ALLOW   1029
#define IDC_AUTOMATIONSERVICE_CLIENT_PERMISSION_REVOKE   1030
#define IDC_AUTOMATIONSERVICE_CLIENT_PERMISSION_REVOKEALL   1031
#define IDC_AUTOMATIONSERVICE_HELP   1032

class CAutomationServiceDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CAutomationServiceDialog)

	// Construction
public:
	CAutomationServiceDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	UINT  m_nPort[2];
	UINT  m_nBufferSize[2];
	CTimeSpan  m_tTimeout[2];
	CAutomationClients  m_pClients[2];
	BOOL  m_bEnabled[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CAutomationServiceDialog)
	enum { IDD = IDD_AUTOMATIONSERVICE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumClients(INT nIndex = -1);
	VOID EnumPermissions();

	VOID ShowServiceDetails();
	VOID ShowClientDetails();

	VOID CheckClientDetails() CONST;
	BOOL GetClientDetails(CAutomationClientInfo *pClientInfo) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutomationServiceDialog)
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

	//{{AFX_MSG(CAutomationServiceDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddClient();
	afx_msg void OnModifyClient();
	afx_msg void OnRemoveClient();
	afx_msg void OnRemoveAllClients();
	afx_msg void OnEncryption();
	afx_msg void OnBanClient();
	afx_msg void OnAllowPermission();
	afx_msg void OnRevokePermission();
	afx_msg void OnRevokeAllPermissions();
	afx_msg void OnDisabled();
	afx_msg void OnSelchangePermission();
	afx_msg void OnSelchangeGrantedPermission();
	afx_msg void OnEditchangeUserName();
	afx_msg void OnEditchangePassword();
	afx_msg void OnEditchangePasswordConfirmatation();
	afx_msg void OnSpinchangePort();
	afx_msg void OnSpinchangeTimeout();
	afx_msg void OnSpinchangeBufferSize();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryServiceDialog dialog

#define IDC_TELEMETRYSERVICE_DETAILS   1001
#define IDC_TELEMETRYSERVICE_PRODUCT_STATIC   1002
#define IDC_TELEMETRYSERVICE_PRODUCT   1003
#define IDC_TELEMETRYSERVICE_DEVICE_STATIC   1004
#define IDC_TELEMETRYSERVICE_DEVICE   1005
#define IDC_TELEMETRYSERVICE_DEVICE_CHANGE   1006
#define IDC_TELEMETRYSERVICE_DEVICE_ADD   1007
#define IDC_TELEMETRYSERVICE_DEVICE_REMOVE   1008
#define IDC_TELEMETRYSERVICE_SCHEDULE   1009
#define IDC_TELEMETRYSERVICE_SCHEDULE_USE   1010
#define IDC_TELEMETRYSERVICE_SCHEDULE_ALWAYS   1011
#define IDC_TELEMETRYSERVICE_SCHEDULE_DAILY   1012
#define IDC_TELEMETRYSERVICE_SCHEDULE_DAILY_STARTTIME   1013
#define IDC_TELEMETRYSERVICE_SCHEDULE_DAILY_STATIC   1014
#define IDC_TELEMETRYSERVICE_SCHEDULE_DAILY_STOPTIME   1015
#define IDC_TELEMETRYSERVICE_SCHEDULE_INTERVAL   1016
#define IDC_TELEMETRYSERVICE_SCHEDULE_INTERVAL_STARTTIME   1017
#define IDC_TELEMETRYSERVICE_SCHEDULE_INTERVAL_STATIC   1018
#define IDC_TELEMETRYSERVICE_SCHEDULE_INTERVAL_STOPTIME   1019
#define IDC_TELEMETRYSERVICE_SCHEDULE_PERIODIC   1020
#define IDC_TELEMETRYSERVICE_SCHEDULE_PERIODIC_TIME   1021
#define IDC_TELEMETRYSERVICE_SCHEDULE_PERIODIC_STATIC   1022
#define IDC_TELEMETRYSERVICE_SCHEDULE_PERIODIC_TIMESPAN   1023
#define IDC_TELEMETRYSERVICE_SCHEDULE_PERIODIC_TIMESPAN_STATIC   1024
#define IDC_TELEMETRYSERVICE_SCHEDULE_PERIODIC_INTERVAL_STATIC   1025
#define IDC_TELEMETRYSERVICE_SCHEDULE_PERIODIC_INTERVAL   1026
#define IDC_TELEMETRYSERVICE_SCHEDULE_PERIODIC_INTERVAL_SECONDS   1027
#define IDC_TELEMETRYSERVICE_SCHEDULE_DISABLED   1028
#define IDC_TELEMETRYSERVICE_SCHEDULE_AUDIT   1029
#define IDC_TELEMETRYSERVICE_BACKUP   1030
#define IDC_TELEMETRYSERVICE_BACKUP_RETRY   1031
#define IDC_TELEMETRYSERVICE_BACKUP_RETRY_CONTINOUSLY   1032
#define IDC_TELEMETRYSERVICE_BACKUP_RETRY_COUNT   1033
#define IDC_TELEMETRYSERVICE_BACKUP_RETRY_COUNT_STATIC   1034
#define IDC_TELEMETRYSERVICE_BACKUP_RETRY_COUNT_NUMBER   1035
#define IDC_TELEMETRYSERVICE_BACKUP_RETRY_DEVICE   1036
#define IDC_TELEMETRYSERVICE_BACKUP_RETRY_DEVICE_NAME   1037
#define IDC_TELEMETRYSERVICE_BACKUP_RETRY_ANYDEVICE   1038
#define IDC_TELEMETRYSERVICE_BACKUP_TIMEOUT   1039
#define IDC_TELEMETRYSERVICE_BACKUP_TIMEOUT_PERIOD   1040
#define IDC_TELEMETRYSERVICE_BACKUP_TIMEOUT_STATIC   1041
#define IDC_TELEMETRYSERVICE_BACKUP_AUDITFAILURES   1042
#define IDC_TELEMETRYSERVICE_HELP   1043

// Specify the telemetry service dialog related settings
#define TELEMETRYSERVICE_MINIMUMINTERVAL   SECONDSPERMINUTE
#define TELEMETRYSERVICE_MAXIMUMINTERVAL   (365*SECONDSPERDAY)
#define TELEMETRYSERVICE_DEFAULTINTERVAL   SECONDSPERHOUR
#define TELEMETRYSERVICE_MINIMUMTIMESPAN   SECONDSPERMINUTE
#define TELEMETRYSERVICE_MAXIMUMTIMESPAN   SECONDSPERWEEK
#define TELEMETRYSERVICE_DEFAULTTIMESPAN   (SECONDSPERHOUR/2)
#define TELEMETRYSERVICE_MINIMUMTIMEOUT   (SECONDSPERMINUTE/4)
#define TELEMETRYSERVICE_MAXIMUMTIMEOUT   SECONDSPERDAY
#define TELEMETRYSERVICE_DEFAULTTIMEOUT   SECONDSPERMINUTE
#define TELEMETRYSERVICE_MINIMUMRETRIES   1
#define TELEMETRYSERVICE_MAXIMUMRETRIES   100
#define TELEMETRYSERVICE_DEFAULTRETRIES   5
#define TELEMETRYSERVICE_DAILYSTARTTIME   HOURS(8)
#define TELEMETRYSERVICE_DAILYSTOPTIME   HOURS(17)
#define TELEMETRYSERVICE_INTERVALTIME   SECONDSPERHOUR

class CTelemetryServiceDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryServiceDialog)

	// Construction
public:
	CTelemetryServiceDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTMProviderDevices  m_pDevices[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryServiceDialog)
	enum { IDD = IDD_TELEMETRYSERVICE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumProducts();
	BOOL EnumProductDevices();
	VOID EnumBackupDevices();

	VOID ShowDeviceDetails();
	VOID ShowDeviceDetails(CONST CTMProviderDevice *pDevice);

	CTMProviderDevice *FindDevice() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryServiceDialog)
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
	//{{AFX_MSG(CTelemetryServiceDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddDevice();
	afx_msg void OnChangeDevice();
	afx_msg void OnRemoveDevice();
	afx_msg void OnScheduleAlways();
	afx_msg void OnScheduleDaily();
	afx_msg void OnScheduleInterval();
	afx_msg void OnSchedulePeriodic();
	afx_msg void OnScheduleDisabled();
	afx_msg void OnScheduleAudit();
	afx_msg void OnBackupContinously();
	afx_msg void OnBackupRetries();
	afx_msg void OnBackupUseDevice();
	afx_msg void OnBackupUseAnyDevice();
	afx_msg void OnBackupTimeout();
	afx_msg void OnBackupAudit();
	afx_msg void OnSelchangeProduct();
	afx_msg void OnSelchangeDevice();
	afx_msg void OnSelchangeDeviceName();
	afx_msg void OnSpinchangeDailyStartTime();
	afx_msg void OnSpinchangeDailyStopTime();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnSpinchangePeriodicTime();
	afx_msg void OnSpinchangePeriodicTimeSpan();
	afx_msg void OnSpinchangePeriodicInterval();
	afx_msg void OnSpinchangeBackupRetryCount();
	afx_msg void OnSpinchangeBackupTimeout();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryEventsDialog

#define IDC_TELEMETRYEVENTS_DETAILS   1001
#define IDC_TELEMETRYEVENTS_NAME_STATIC   1002
#define IDC_TELEMETRYEVENTS_NAME   1003
#define IDC_TELEMETRYEVENTS_ADD   1004
#define IDC_TELEMETRYEVENTS_REMOVE   1005
#define IDC_TELEMETRYEVENTS_REMOVEALL   1006
#define IDC_TELEMETRYEVENTS_PROPERTIES   1007
#define IDC_TELEMETRYEVENTS_PROPERTIES_STACK_STATIC   1008
#define IDC_TELEMETRYEVENTS_PROPERTIES_STACK   1009
#define IDC_TELEMETRYEVENTS_PROPERTIES_RESULT_STATIC   1010
#define IDC_TELEMETRYEVENTS_PROPERTIES_RESULT   1011
#define IDC_TELEMETRYEVENTS_PROPERTIES_STACK_ADD   1012
#define IDC_TELEMETRYEVENTS_PROPERTIES_STACK_REMOVE   1013
#define IDC_TELEMETRYEVENTS_PROPERTIES_STACK_REMOVEALL   1014
#define IDC_TELEMETRYEVENTS_PROPERTIES_PARAMETER_STATIC   1015
#define IDC_TELEMETRYEVENTS_PROPERTIES_PARAMETER   1016
#define IDC_TELEMETRYEVENTS_PROPERTIES_SAMPLE_STATIC   1017
#define IDC_TELEMETRYEVENTS_PROPERTIES_SAMPLE   1018
#define IDC_TELEMETRYEVENTS_PROPERTIES_SAMPLE_CALIBRATED   1019
#define IDC_TELEMETRYEVENTS_PROPERTIES_SAMPLE_CODED   1020
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_7   1021
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_8   1022
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_9   1023
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_4   1024
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_5   1025
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_6   1026
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_1   1027
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_2   1028
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_3   1029
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_0   1030
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_DIV   1031
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_MUL   1032
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_SUB   1033
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_ADD   1034
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_SIGN   1035
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_POINT   1036
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_SIN   1037
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_COS   1038
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_TAN   1039
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_ASIN   1040
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_ACOS   1041
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_ATAN   1042
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_ABS   1043
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_INT   1044
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_SQRT   1045
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_X2   1046
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_XY   1047
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_LN   1048
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_LOG   1049
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_EXP   1050
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_PI   1051
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_E   1052
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_AND   1053
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_OR   1054
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_NOT   1055
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_XOR   1056
#define IDC_TELEMETRYEVENTS_PROPERTIES_KEY_ENTER   1057
#define IDC_TELEMETRYEVENTS_PROPERTIES_DATA   1058
#define IDC_TELEMETRYEVENTS_PROPERTIES_DATA_INVALID   1059
#define IDC_TELEMETRYEVENTS_PROPERTIES_DATA_BAD   1060
#define IDC_TELEMETRYEVENTS_PROPERTIES_DATA_DISABLED   1061
#define IDC_TELEMETRYEVENTS_PROPERTIES_AUDITION_STATIC   1062
#define IDC_TELEMETRYEVENTS_PROPERTIES_AUDITION   1063
#define IDC_TELEMETRYEVENTS_PROPERTIES_NOTIFICATION_STATIC   1064
#define IDC_TELEMETRYEVENTS_PROPERTIES_NOTIFICATION   1065
#define IDC_TELEMETRYEVENTS_PROPERTIES_TEXT_STATIC   1066
#define IDC_TELEMETRYEVENTS_PROPERTIES_TEXT   1067
#define IDC_TELEMETRYEVENTS_HELP   1068

// Specify the telemetry events dialog related identifiers
#define TELEMETRYEVENTSDIALOG_STACKPOSINDICATOR_WIDTH   3
// Specify the telemetry events dialog related limits
#define TELEMETRYEVENTSDIALOG_MINIMUMSAMPLE   -100
#define TELEMETRYEVENTSDIALOG_MAXIMUMSAMPLE   100
#define TELEMETRYEVENTSDIALOG_DEFAULTSAMPLE   0

class CTelemetryEventsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryEventsDialog)

	// Construction
public:
	CTelemetryEventsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryEvents  m_pEvents[2];
	CTelemetryEventInfo  *m_pEventInfo;
private:
	INT  m_nStackPos[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryEventsDialog)
	enum { IDD = IDD_TELEMETRYEVENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumEvents();
	BOOL EnumResults();
	BOOL EnumParameters();
	BOOL EnumAuditions();
	BOOL EnumNotifications();
	VOID EnumExpressions();

	VOID ShowEventInfo();
	BOOL CheckEventInfo() CONST;
	BOOL CheckEventInfo(CONST CTelemetryEventInfo *pEventInfo) CONST;
	CTelemetryEventInfo *FindEventInfo(BOOL bAny = TRUE) CONST;

	VOID Key(INT nDigit);
	VOID Key(LPCTSTR pszKey);

	UINT CheckStackOperands() CONST;
	UINT CheckStackOperands(CONST CTelemetryEventInfo *pEventInfo) CONST;
	BOOL CheckStackContents(LPCTSTR pszKey) CONST;
	VOID UpdateStackContents();

	BOOL TranslateNumber(CTelemetryEventExpression *pExpression, INT nDigit, double &fNumber);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryEventsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	//{{AFX_MSG(CTelemetryEventsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDrawItem(int nCtlID, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnAddEvent();
	afx_msg void OnRemoveEvent();
	afx_msg void OnRemoveAllEvents();
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
	afx_msg void OnKeyAND();
	afx_msg void OnKeyOR();
	afx_msg void OnKeyNOT();
	afx_msg void OnKeyXOR();
	afx_msg void OnKeyPoint();
	afx_msg void OnKeyEnter();
	afx_msg void OnInvalidData();
	afx_msg void OnBadData();
	afx_msg void OnDisabledData();
	afx_msg void OnEditchangeEvent();
	afx_msg void OnEditchangeText();
	afx_msg void OnSelchangeEvent();
	afx_msg void OnSelchangeResult();
	afx_msg void OnSelchangeAudition();
	afx_msg void OnSelchangeNotification();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryEventsImportDialog dialog

#define IDC_TELEMETRYEVENTS_IMPORT_DETAILS   1001
#define IDC_TELEMETRYEVENTS_IMPORT_FILENAME_STATIC   1002
#define IDC_TELEMETRYEVENTS_IMPORT_FILENAME   1003
#define IDC_TELEMETRYEVENTS_IMPORT_BROWSE   1004
#define IDC_TELEMETRYEVENTS_IMPORT_INSPECT   1005
#define IDC_TELEMETRYEVENTS_IMPORT_DIRECTORY_STATIC   1006
#define IDC_TELEMETRYEVENTS_IMPORT_DIRECTORY   1007
#define IDC_TELEMETRYEVENTS_IMPORT_ADD   1008
#define IDC_TELEMETRYEVENTS_IMPORT_ADDALL   1009
#define IDC_TELEMETRYEVENTS_IMPORT_ATTENTION   1010
#define IDC_TELEMETRYEVENTS_IMPORT_ATTENTION_TEXT   1011
#define IDC_TELEMETRYEVENTS_IMPORT_LIST_STATIC   1012
#define IDC_TELEMETRYEVENTS_IMPORT_LIST   1013
#define IDC_TELEMETRYEVENTS_IMPORT_REMOVE   1014
#define IDC_TELEMETRYEVENTS_IMPORT_REMOVEALL   1015
#define IDC_TELEMETRYEVENTS_IMPORT_HELP   1016

class CTelemetryEventsImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryEventsImportDialog)

	// Construction
public:
	CTelemetryEventsImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryEvents  m_pEvents[3];

	// Operations
private:
	VOID EnumEvents();

	// Dialog Data
	//{{AFX_DATA(CTelemetryEventsImportDialog)
	enum { IDD = IDD_TELEMETRYEVENTS_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryEventsImportDialog)
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
	//{{AFX_MSG(CTelemetryEventsImportDialog)
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
// CTelemetryEventsExportDialog dialog

#define IDC_TELEMETRYEVENTS_EXPORT_DETAILS   1001
#define IDC_TELEMETRYEVENTS_EXPORT_DIRECTORY_STATIC   1002
#define IDC_TELEMETRYEVENTS_EXPORT_DIRECTORY   1003
#define IDC_TELEMETRYEVENTS_EXPORT_ADD   1004
#define IDC_TELEMETRYEVENTS_EXPORT_ADDALL   1005
#define IDC_TELEMETRYEVENTS_EXPORT_LIST_STATIC   1006
#define IDC_TELEMETRYEVENTS_EXPORT_LIST   1007
#define IDC_TELEMETRYEVENTS_EXPORT_REMOVE   1008
#define IDC_TELEMETRYEVENTS_EXPORT_REMOVEALL   1009
#define IDC_TELEMETRYEVENTS_EXPORT_FILENAME_STATIC   1010
#define IDC_TELEMETRYEVENTS_EXPORT_FILENAME   1011
#define IDC_TELEMETRYEVENTS_EXPORT_BROWSE   1012
#define IDC_TELEMETRYEVENTS_EXPORT_HELP   1013

class CTelemetryEventsExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryEventsExportDialog)

	// Construction
public:
	CTelemetryEventsExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryEvents  m_pEvents[2];

	// Operations
private:
	BOOL EnumEvents();

	// Dialog Data
	//{{AFX_DATA(CTelemetryEventsExportDialog)
	enum { IDD = IDD_TELEMETRYEVENTS_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryEventsExportDialog)
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
	//{{AFX_MSG(CTelemetryEventsExportDialog)
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
// CTelemetryReportsDialog

#define IDC_TELEMETRYREPORTS_DETAILS   1001
#define IDC_TELEMETRYREPORTS_NAME_STATIC   1002
#define IDC_TELEMETRYREPORTS_NAME   1003
#define IDC_TELEMETRYREPORTS_ADD   1004
#define IDC_TELEMETRYREPORTS_REMOVE   1005
#define IDC_TELEMETRYREPORTS_REMOVEALL   1006
#define IDC_TELEMETRYREPORTS_ABORT   1007
#define IDC_TELEMETRYREPORTS_DISABLED   1008
#define IDC_TELEMETRYREPORTS_PROPERTIES   1009
#define IDC_TELEMETRYREPORTS_PROPERTIES_TRACK_STATIC   1010
#define IDC_TELEMETRYREPORTS_PROPERTIES_TELEMETRYEVENTS   1011
#define IDC_TELEMETRYREPORTS_PROPERTIES_TELEMETRYEVENTS_LIST   1012
#define IDC_TELEMETRYREPORTS_PROPERTIES_TELEMETRYEVENTS_ADD   1013
#define IDC_TELEMETRYREPORTS_PROPERTIES_TELEMETRYEVENTS_ACTIVELIST   1014
#define IDC_TELEMETRYREPORTS_PROPERTIES_TELEMETRYEVENTS_REMOVE   1015
#define IDC_TELEMETRYREPORTS_PROPERTIES_TELEMETRYEVENTS_REMOVEALL   1016
#define IDC_TELEMETRYREPORTS_PROPERTIES_SYSTEMALERTS   1017
#define IDC_TELEMETRYREPORTS_PROPERTIES_SYSTEMALERTS_LIST   1018
#define IDC_TELEMETRYREPORTS_PROPERTIES_SYSTEMALERTS_ADD   1019
#define IDC_TELEMETRYREPORTS_PROPERTIES_SYSTEMALERTS_ACTIVELIST   1020
#define IDC_TELEMETRYREPORTS_PROPERTIES_SYSTEMALERTS_REMOVE   1021
#define IDC_TELEMETRYREPORTS_PROPERTIES_SYSTEMALERTS_REMOVEALL   1022
#define IDC_TELEMETRYREPORTS_PROPERTIES_FILETRIGGERS   1023
#define IDC_TELEMETRYREPORTS_PROPERTIES_SCHEDULE   1024
#define IDC_TELEMETRYREPORTS_PROPERTIES_SCRIPT_STATIC   1025
#define IDC_TELEMETRYREPORTS_PROPERTIES_SCRIPT   1026
#define IDC_TELEMETRYREPORTS_PROPERTIES_KEEPALLFILES   1027
#define IDC_TELEMETRYREPORTS_PROPERTIES_INPUTFILENAME_STATIC   1028
#define IDC_TELEMETRYREPORTS_PROPERTIES_INPUTFILENAME   1029
#define IDC_TELEMETRYREPORTS_PROPERTIES_INPUTFILENAME_BROWSE   1030
#define IDC_TELEMETRYREPORTS_PROPERTIES_OUTPUTFILENAME_STATIC   1031
#define IDC_TELEMETRYREPORTS_PROPERTIES_OUTPUTFILENAME   1032
#define IDC_TELEMETRYREPORTS_PROPERTIES_OUTPUTFILENAME_BROWSE   1033
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAILLIST_STATIC   1034
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAILLIST   1035
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAILLIST_FTP   1036
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAILLIST_ADD   1037
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAILLIST_REMOVE   1038
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAIL_DAILY   1039
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAIL_DAILY_INTERVAL   1040
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAIL_DAILY_STATIC   1041
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAIL_DAILY_TIME   1042
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAIL_WEEKLY   1043
#define IDC_TELEMETRYREPORTS_PROPERTIES_MAIL_WEEKLY_TIME   1044
#define IDC_TELEMETRYREPORTS_HELP   1045

// Specify the telemetry reports dialog related limits
#define TELEMETRYREPORTSDIALOG_MINIMUMDAYS   1
#define TELEMETRYREPORTSDIALOG_MAXIMUMDAYS   365
#define TELEMETRYREPORTSDIALOG_DEFAULTDAYS   1

class CTelemetryReportsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryReportsDialog)

	// Construction
public:
	CTelemetryReportsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CSystemAlerts  m_pAlerts;
	CTelemetryEvents  m_pEvents;
	CTelemetryReports  m_pReports[2];
	CTelemetryReportInfo  *m_pReportInfo;
	CAutomationScripts  m_pScripts;

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsDialog)
	enum { IDD = IDD_TELEMETRYREPORTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumReports();
	BOOL EnumScripts();
	BOOL EnumSystemAlerts();
	BOOL EnumTelemetryEvents();

	VOID ShowReportInfo();
	BOOL CheckReportInfo() CONST;
	BOOL CheckReportInfo(CONST CTelemetryReportInfo *pReportInfo) CONST;
	CTelemetryReportInfo *FindReportInfo(BOOL bAny = TRUE) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsDialog)
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

	//{{AFX_MSG(CTelemetryReportsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAddReport();
	afx_msg void OnRemoveReport();
	afx_msg void OnRemoveAllReports();
	afx_msg void OnAbortReports();
	afx_msg void OnDisableReport();
	afx_msg void OnTelemetryEvents();
	afx_msg void OnAddTelemetryEvent();
	afx_msg void OnRemoveTelemetryEvent();
	afx_msg void OnRemoveAllTelemetryEvents();
	afx_msg void OnSystemAlerts();
	afx_msg void OnAddSystemAlert();
	afx_msg void OnRemoveSystemAlert();
	afx_msg void OnRemoveAllSystemAlerts();
	afx_msg void OnTriggerReportByFiles();
	afx_msg void OnScheduleReport();
	afx_msg void OnKeepAllFiles();
	afx_msg void OnBrowseInputFileName();
	afx_msg void OnBrowseOutputFileName();
	afx_msg void OnAddFTPRecipient();
	afx_msg void OnAddMailRecipient();
	afx_msg void OnRemoveRecipient();
	afx_msg void OnMailDaily();
	afx_msg void OnMailWeekly();
	afx_msg void OnEditchangeReport();
	afx_msg void OnEditchangeInputFileName();
	afx_msg void OnEditchangeOutputFileName();
	afx_msg void OnSelchangeReport();
	afx_msg void OnSelchangeTelemetryEvent();
	afx_msg void OnSelchangeActiveTelemetryEvent();
	afx_msg void OnSelchangeSystemAlert();
	afx_msg void OnSelchangeActiveSystemAlert();
	afx_msg void OnSelchangeScript();
	afx_msg void OnSelchangeMailRecipient();
	afx_msg void OnSpinchangeDailyInterval();
	afx_msg void OnSpinchangeDailyTime();
	afx_msg void OnSpinchangeWeeklyTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsImportDialog dialog

#define IDC_TELEMETRYREPORTS_IMPORT_DETAILS   1001
#define IDC_TELEMETRYREPORTS_IMPORT_FILENAME_STATIC   1002
#define IDC_TELEMETRYREPORTS_IMPORT_FILENAME   1003
#define IDC_TELEMETRYREPORTS_IMPORT_BROWSE   1004
#define IDC_TELEMETRYREPORTS_IMPORT_INSPECT   1005
#define IDC_TELEMETRYREPORTS_IMPORT_DIRECTORY_STATIC   1006
#define IDC_TELEMETRYREPORTS_IMPORT_DIRECTORY   1007
#define IDC_TELEMETRYREPORTS_IMPORT_HISTORICAL   1008
#define IDC_TELEMETRYREPORTS_IMPORT_ADD   1009
#define IDC_TELEMETRYREPORTS_IMPORT_ADDALL   1010
#define IDC_TELEMETRYREPORTS_IMPORT_ATTENTION   1011
#define IDC_TELEMETRYREPORTS_IMPORT_ATTENTION_TEXT   1012
#define IDC_TELEMETRYREPORTS_IMPORT_LIST_STATIC   1013
#define IDC_TELEMETRYREPORTS_IMPORT_LIST   1014
#define IDC_TELEMETRYREPORTS_IMPORT_REMOVE   1015
#define IDC_TELEMETRYREPORTS_IMPORT_REMOVEALL   1016
#define IDC_TELEMETRYREPORTS_IMPORT_HELP   1017

class CTelemetryReportsImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryReportsImportDialog)

	// Construction
public:
	CTelemetryReportsImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryReports  m_pReports[3];
	CTelemetryHistoricalReports  m_pHistoricalReports[3];

	// Operations
private:
	VOID EnumReports();

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsImportDialog)
	enum { IDD = IDD_TELEMETRYREPORTS_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsImportDialog)
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
	//{{AFX_MSG(CTelemetryReportsImportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowse();
	afx_msg void OnInspect();
	afx_msg void OnAdd();
	afx_msg void OnAddAll();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnHistorical();
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
// CTelemetryReportsExportDialog dialog

#define IDC_TELEMETRYREPORTS_EXPORT_DETAILS   1001
#define IDC_TELEMETRYREPORTS_EXPORT_DIRECTORY_STATIC   1002
#define IDC_TELEMETRYREPORTS_EXPORT_DIRECTORY   1003
#define IDC_TELEMETRYREPORTS_EXPORT_HISTORICAL   1004
#define IDC_TELEMETRYREPORTS_EXPORT_ADD   1005
#define IDC_TELEMETRYREPORTS_EXPORT_ADDALL   1006
#define IDC_TELEMETRYREPORTS_EXPORT_LIST_STATIC   1007
#define IDC_TELEMETRYREPORTS_EXPORT_LIST   1008
#define IDC_TELEMETRYREPORTS_EXPORT_REMOVE   1009
#define IDC_TELEMETRYREPORTS_EXPORT_REMOVEALL   1010
#define IDC_TELEMETRYREPORTS_EXPORT_FILENAME_STATIC   1011
#define IDC_TELEMETRYREPORTS_EXPORT_FILENAME   1012
#define IDC_TELEMETRYREPORTS_EXPORT_BROWSE   1013
#define IDC_TELEMETRYREPORTS_EXPORT_HELP   1014

class CTelemetryReportsExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryReportsExportDialog)

	// Construction
public:
	CTelemetryReportsExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryReports  m_pReports[2];
	CTelemetryHistoricalReports  m_pHistoricalReports[2];

	// Operations
private:
	BOOL EnumReports();

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsExportDialog)
	enum { IDD = IDD_TELEMETRYREPORTS_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsExportDialog)
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
	//{{AFX_MSG(CTelemetryReportsExportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnAddAll();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnHistorical();
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
// CTelemetryReportsHistoricalRangePage dialog

#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_DETAILS   1001
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_EXTRACT_STATIC   1002
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_TIMEPERIOD   1003
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_TIMEPERIOD_STARTTIME   1004
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_TIMEPERIOD_STATIC   1005
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_TIMEPERIOD_STOPTIME   1006
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_DAILYPERIOD   1007
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_DAILYPERIOD_STARTTIME   1008
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_DAILYPERIOD_STATIC   1009
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_DAILYPERIOD_STOPTIME   1010
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_PERIOD_ALL   1011
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_PERIOD_ALL_STATIC   1012
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_PERIOD_PART   1013
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_PERIOD_PART_STATIC   1014
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_PERIOD_PART_MINUTES_STATIC   1015
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_PERIOD_PART_MINUTES   1016
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_TRIGGER   1017
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_TRIGGER_STATIC   1018
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_TRIGGER_MINUTES_PREFIX_STATIC   1019
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_TRIGGER_MINUTES   1020
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_TRIGGER_MINUTES_REFERENCE   1021
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_TRIGGER_MINUTES_SUFFIX_STATIC   1022
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_INTERVAL   1023
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_INTERVAL_STATIC   1024
#define IDC_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE_INTERVAL_MINUTES   1025

// Specify the historical telemetry reports range related settings
#define TELEMETRYREPORTSRANGE_MINIMUMINTERVAL   0
#define TELEMETRYREPORTSRANGE_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define TELEMETRYREPORTSRANGE_DEFAULTINTERVAL   MINUTESPERHOUR
#define TELEMETRYREPORTSRANGE_DAILYSTARTTIME   HOURS(8)
#define TELEMETRYREPORTSRANGE_DAILYSTOPTIME   HOURS(17)

class CTelemetryReportsHistoricalRangePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryReportsHistoricalRangePage)

	// Construction
public:
	CTelemetryReportsHistoricalRangePage();

	// Attributes
private:
	CTelemetryHistoricalReportInfo  m_cInfo[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsHistoricalRangePage)
	enum { IDD = IDD_TELEMETRYREPORTS_HISTORICAL_RANGEPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CONST CTelemetryHistoricalReportInfo *pBackupHistoricalReportInfo = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CTelemetryHistoricalReportInfo *pHistoricalReportInfo) CONST;

	class CTelemetryReportsHistoricalPageFolder *GetParent() CONST;

private:
	VOID ShowRangeInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsHistoricalRangePage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryReportsHistoricalRangePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimeRange();
	afx_msg void OnDailyTimeRange();
	afx_msg void OnPeriodicalRange();
	afx_msg void OnPeriodicalPartialRange();
	afx_msg void OnTriggeredRange();
	afx_msg void OnRangeInterval();
	afx_msg void OnSelchangeTriggerReference();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnSpinchangeDailyStartTime();
	afx_msg void OnSpinchangeDailyStopTime();
	afx_msg void OnSpinchangePeriodicalInterval();
	afx_msg void OnSpinchangeTriggeredInterval();
	afx_msg void OnSpinchangeRangeInterval();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsHistoricalExecutionPage dialog

#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_DETAILS   1001
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_STATIC   1002
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_IMMEDIATELY   1003
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_ONCE   1004
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_ONCE_TIME   1005
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_DAILY   1006
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_DAILY_TIME   1007
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_PERIODICALLY   1008
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_PERIODICALLY_STARTTIME   1009
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_PERIODICALLY_INTERVAL_STATIC   1010
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_PERIODICALLY_INTERVAL   1011
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_PERIODICALLY_INTERVAL_MINUTES_STATIC   1012
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_PERIODICALLY_STOPTIME_STATIC   1013
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_PERIODICALLY_STOPTIME   1014
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_EVENT   1015
#define IDC_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE_RUN_EVENT_NAME   1016

// Specify the historical telemetry reports execution related settings
#define TELEMETRYREPORTSEXECUTION_MINIMUMINTERVAL   1
#define TELEMETRYREPORTSEXECUTION_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define TELEMETRYREPORTSEXECUTION_DEFAULTINTERVAL   MINUTESPERHOUR

class CTelemetryReportsHistoricalExecutionPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryReportsHistoricalExecutionPage)

	// Construction
public:
	CTelemetryReportsHistoricalExecutionPage();

	// Attributes
private:
	CTelemetryHistoricalReportInfo  m_cInfo[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsHistoricalExecutionPage)
	enum { IDD = IDD_TELEMETRYREPORTS_HISTORICAL_EXECUTIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CONST CTelemetryHistoricalReportInfo *pBackupHistoricalReportInfo = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CTelemetryHistoricalReportInfo *pHistoricalReportInfo) CONST;

	class CTelemetryReportsHistoricalPageFolder *GetParent() CONST;

private:
	BOOL EnumEvents();

	VOID ShowExecutionInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsHistoricalExecutionPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryReportsHistoricalExecutionPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnExecutionNow();
	afx_msg void OnExecutionAtTime();
	afx_msg void OnExecutionAtDailyTime();
	afx_msg void OnExecutionAtPeriodicalTime();
	afx_msg void OnExecutionAtEvent();
	afx_msg void OnSelchangeExecutionEvent();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg void OnSpinchangeExecutionDailyTime();
	afx_msg void OnSpinchangeExecutionPeriodicalStartTime();
	afx_msg void OnSpinchangeExecutionPeriodicalStopTime();
	afx_msg void OnSpinchangeExecutionPeriodicalInterval();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsHistoricalInputPage dialog

#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_DETAILS   1001
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FILES_STATIC   1002
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FILES   1003
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FILES_BROWSE   1004
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_DIRECTORY_STATIC   1005
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_DIRECTORY   1006
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_DIRECTORY_BROWSE   1007
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_KEEPFILES   1008
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FTP   1009
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FTP_LOCATION   1010
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FTP_USERNAME_STATIC   1011
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FTP_USERNAME   1012
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FTP_PASSWORD_STATIC   1013
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FTP_PASSWORD   1014
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FTP_PORT   1015
#define IDC_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE_FTP_PORT_NUMBER   1016

// Specify the historical telemetry reports input related settings
#define TELEMETRYREPORTSINPUT_FIRSTPORT   1024
#define TELEMETRYREPORTSINPUT_LASTPORT   65535
#define TELEMETRYREPORTSINPUT_DEFAULTPORT   1024

class CTelemetryReportsHistoricalInputPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryReportsHistoricalInputPage)

	// Construction
public:
	CTelemetryReportsHistoricalInputPage();

	// Attributes
private:
	CTelemetryHistoricalReportInfo  m_cInfo[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsHistoricalInputPage)
	enum { IDD = IDD_TELEMETRYREPORTS_HISTORICAL_INPUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CONST CTelemetryHistoricalReportInfo *pBackupHistoricalReportInfo = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CTelemetryHistoricalReportInfo *pHistoricalReportInfo) CONST;

	class CTelemetryReportsHistoricalPageFolder *GetParent() CONST;

private:
	VOID ShowInputInfo();

	BOOL CheckFTPLocation() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsHistoricalInputPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryReportsHistoricalInputPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseFiles();
	afx_msg void OnBrowseDirectory();
	afx_msg void OnKeepFiles();
	afx_msg void OnUseFTP();
	afx_msg void OnUseFTPPort();
	afx_msg void OnEditchangeFiles();
	afx_msg void OnEditchangeDirectory();
	afx_msg void OnEditchangeFTPLocation();
	afx_msg void OnEditchangeFTPUserName();
	afx_msg void OnEditchangeFTPPassword();
	afx_msg void OnSpinchangeFTPPort();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsHistoricalOutputPage dialog

#define IDC_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE_DETAILS   1001
#define IDC_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE_FILENAME_STATIC   1002
#define IDC_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE_FILENAME   1003
#define IDC_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE_FILENAME_BROWSE   1004
#define IDC_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE_KEEPFILE   1005
#define IDC_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE_MAILLIST_STATIC   1006
#define IDC_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE_MAILLIST   1007
#define IDC_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE_MAILLIST_FTP   1008
#define IDC_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE_MAILLIST_ADD   1009
#define IDC_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE_MAILLIST_REMOVE   1010

class CTelemetryReportsHistoricalOutputPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryReportsHistoricalOutputPage)

	// Construction
public:
	CTelemetryReportsHistoricalOutputPage();

	// Attributes
private:
	CTelemetryHistoricalReportInfo  m_cInfo[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsHistoricalOutputPage)
	enum { IDD = IDD_TELEMETRYREPORTS_HISTORICAL_OUTPUTPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CONST CTelemetryHistoricalReportInfo *pBackupHistoricalReportInfo = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CTelemetryHistoricalReportInfo *pHistoricalReportInfo) CONST;

	class CTelemetryReportsHistoricalPageFolder *GetParent() CONST;

private:
	VOID ShowOutputInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsHistoricalOutputPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryReportsHistoricalOutputPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseFile();
	afx_msg void OnKeepFile();
	afx_msg void OnAddFTPRecipient();
	afx_msg void OnAddMailRecipient();
	afx_msg void OnRemoveRecipient();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnSelchangeMailRecipient();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsHistoricalPageTabCtrl window

class CTelemetryReportsHistoricalPageTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTelemetryReportsHistoricalPageTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTelemetryReportsHistoricalPageFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsHistoricalPageTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelemetryReportsHistoricalPageTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsHistoricalPageFolder

class CTelemetryReportsHistoricalPageFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNAMIC(CTelemetryReportsHistoricalPageFolder)

	// Construction
public:
	CTelemetryReportsHistoricalPageFolder();

	// Attributes
private:
	CTelemetryReportsHistoricalPageTabCtrl  m_wndTabCtrl;
	CTelemetryReportsHistoricalRangePage  m_pageRange;
	CTelemetryReportsHistoricalExecutionPage  m_pageExecution;
	CTelemetryReportsHistoricalInputPage  m_pageInput;
	CTelemetryReportsHistoricalOutputPage  m_pageOutput;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID SetInfo(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, BOOL bUpdate = TRUE);
	VOID SetInfo(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, CONST CTelemetryHistoricalReportInfo *pBackupHistoricalReportInfo);
	VOID GetInfo(CTelemetryHistoricalReportInfo *pHistoricalReportInfo) CONST;

	class CTelemetryReportsHistoricalDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsHistoricalPageFolder)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	virtual BOOL Check(BOOL bModified, BOOL bChecked) CONST;
protected:
	virtual VOID RepositionButtons();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelemetryReportsHistoricalPageFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsHistoricalDialog

#define IDC_TELEMETRYREPORTS_HISTORICAL_DETAILS   1001
#define IDC_TELEMETRYREPORTS_HISTORICAL_NAME_STATIC  1002
#define IDC_TELEMETRYREPORTS_HISTORICAL_NAME   1003
#define IDC_TELEMETRYREPORTS_HISTORICAL_SAVE   1004
#define IDC_TELEMETRYREPORTS_HISTORICAL_DELETE   1005
#define IDC_TELEMETRYREPORTS_HISTORICAL_DELETEALL   1006
#define IDC_TELEMETRYREPORTS_HISTORICAL_SUBMIT   1007
#define IDC_TELEMETRYREPORTS_HISTORICAL_ABORT   1008
#define IDC_TELEMETRYREPORTS_HISTORICAL_PROPERTIES   1009
#define IDC_TELEMETRYREPORTS_HISTORICAL_PROPERTIES_REPORT_STATIC   1010
#define IDC_TELEMETRYREPORTS_HISTORICAL_PROPERTIES_REPORT   1011
#define IDC_TELEMETRYREPORTS_HISTORICAL_PROPERTIES_SOURCE_STATIC   1012
#define IDC_TELEMETRYREPORTS_HISTORICAL_PROPERTIES_SOURCE   1013
#define IDC_TELEMETRYREPORTS_HISTORICAL_PROPERTIES_SOURCE_BROWSE   1014
#define IDC_TELEMETRYREPORTS_HISTORICAL_FOLDER   1015
#define IDC_TELEMETRYREPORTS_HISTORICAL_HELP   1016

class CTelemetryReportsHistoricalDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryReportsHistoricalDialog)

	// Construction
public:
	CTelemetryReportsHistoricalDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryReports  m_pReports;
	CTelemetryHistoricalReports  m_pHistoricalReports[3];
private:
	CTelemetryReportsHistoricalPageFolder  *m_pwndFolderCtrl;
private:
	UINT  m_nLocked;

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsHistoricalDialog)
	enum { IDD = IDD_TELEMETRYREPORTS_HISTORICAL_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetHistoricalReports(CONST CTelemetryHistoricalReports &pHistoricalReports);
	BOOL GetHistoricalReports(CTelemetryHistoricalReports &pHistoricalReports) CONST;

private:
	BOOL EnumReports();
	BOOL EnumHistoricalReports();
	BOOL EnumReportSourceFiles();

	BOOL CheckHistoricalReports() CONST;

	VOID SetHistoricalReportInfo(BOOL bInitialize = FALSE);
	VOID UpdateHistoricalReportInfo(CONST CTelemetryHistoricalReportInfo *pHistoricalReportInfo, BOOL bInitialize);
	BOOL GetHistoricalReportInfo(CTelemetryHistoricalReportInfo *pHistoricalReportInfo) CONST;
	CTelemetryHistoricalReportInfo *FindHistoricalReportInfo() CONST;

	CRect CalcFolderSize() CONST;

	VOID AdjustToPrivileges();

	VOID Lock();
	BOOL IsLocked() CONST;
	VOID Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsHistoricalDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	virtual BOOL Check(BOOL bModified, BOOL bChecked) CONST;
	virtual VOID Update(BOOL bModified, BOOL bChecked) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	//{{AFX_MSG(CTelemetryReportsHistoricalDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSave();
	afx_msg void OnDelete();
	afx_msg void OnDeleteAll();
	afx_msg void OnSubmit();
	afx_msg void OnAbort();
	afx_msg void OnBrowseSource();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeSource();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeReport();
	afx_msg void OnSelchangeSource();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsFTPDialog

#define IDC_TELEMETRYREPORTS_FTP_DETAILS   1001
#define IDC_TELENETRYREPORTS_FTP_LOCATION_STATIC  1002
#define IDC_TELEMETRYREPORTS_FTP_LOCATION   1003
#define IDC_TELEMETRYREPORTS_FTP_USERNAME_STATIC   1004
#define IDC_TELEMETRYREPORTS_FTP_USERNAME   1005
#define IDC_TELEMETRYREPORTS_FTP_PASSWORD_STATIC   1006
#define IDC_TELEMETRYREPORTS_FTP_PASSWORD   1007
#define IDC_TELEMETRYREPORTS_FTP_PORT   1008
#define IDC_TELEMETRYREPORTS_FTP_PORT_NUMBER   1009
#define IDC_TELEMETRYREPORTS_FTP_TRANSFERS   1010
#define IDC_TELEMETRYREPORTS_FTP_BEHAVIOR   1011
#define IDC_TELEMETRYREPORTS_FTP_BEHAVIOR_STATIC   1012
#define IDC_TELEMETRYREPORTS_FTP_RETRY_NEVER   1013
#define IDC_TELEMETRYREPORTS_FTP_RETRY_CONTINUOUSLY   1014
#define IDC_TELEMETRYREPORTS_FTP_RETRY_COUNT   1015
#define IDC_TELEMETRYREPORTS_FTP_RETRY_COUNT_STATIC   1016
#define IDC_TELEMETRYREPORTS_FTP_RETRY_COUNT_NUMBER   1017
#define IDC_TELEMETRYREPORTS_FTP_RETRY_INTERVAL_STATIC   1018
#define IDC_TELEMETRYREPORTS_FTP_RETRY_INTERVAL   1019
#define IDC_TELEMETRYREPORTS_FTP_RETRY_INTERVAL_MINUTES_STATIC   1020
#define IDC_TELEMETRYREPORTS_FTP_AUDITION   1021
#define IDC_TELEMETRYREPORTS_FTP_AUDITION_STATIC   1022
#define IDC_TELEMETRYREPORTS_FTP_AUDITION_NOTHING   1023
#define IDC_TELEMETRYREPORTS_FTP_AUDITION_EVERYTHING   1024
#define IDC_TELEMETRYREPORTS_FTP_AUDITION_FAILURES   1025
#define IDC_TELEMETRYREPORTS_FTP_HELP   1026

// Specify the telemetry reports FTP dialog related settings
#define TELEMETRYREPORTSFTPTRANSFERS_FIRSTPORT   1024
#define TELEMETRYREPORTSFTPTRANSFERS_LASTPORT   65535
#define TELEMETRYREPORTSFTPTRANSFERS_DEFAULTPORT   1024
#define TELEMETRYREPORTSFTPTRANSFERS_MINIMUMRETRIES   1
#define TELEMETRYREPORTSFTPTRANSFERS_MAXIMUMRETRIES   100
#define TELEMETRYREPORTSFTPTRANSFERS_DEFAULTRETRIES   5
#define TELEMETRYREPORTSFTPTRANSFERS_MINIMUMRETRYINTERVAL   1
#define TELEMETRYREPORTSFTPTRANSFERS_MAXIMUMRETRYINTERVAL   MINUTESPERHOUR
#define TELEMETRYREPORTSFTPTRANSFERS_DEFAULTRETRYINTERVAL   5

class CTelemetryReportsFTPDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryReportsFTPDialog)

	// Construction
public:
	CTelemetryReportsFTPDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryReportFTPRecipientInfo  m_cRecipientInfo;

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsFTPDialog)
	enum { IDD = IDD_TELEMETRYREPORTS_FTP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL CheckURL(LPCTSTR pszLocation) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsFTPDialog)
public:
	virtual INT DoModal(CTelemetryReportFTPRecipientInfo *pRecipientInfo);
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	//{{AFX_MSG(CTelemetryReportsFTPDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnUsePort();
	afx_msg void OnTransfers();
	afx_msg void OnRetryNever();
	afx_msg void OnRetryContinuously();
	afx_msg void OnRetryLimited();
	afx_msg void OnAuditNothing();
	afx_msg void OnAuditEverything();
	afx_msg void OnAuditFailures();
	afx_msg void OnEditchangeLocation();
	afx_msg void OnEditchangeUserName();
	afx_msg void OnEditchangePassword();
	afx_msg void OnSpinchangePort();
	afx_msg void OnSpinchangeRetries();
	afx_msg void OnSpinchangeRetryInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsFileTriggersDialog dialog

#define IDC_TELEMETRYREPORTS_FILETRIGGERS_DETAILS   1001
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_DIRECTORIES_STATIC  1002
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_DIRECTORIES   1003
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BROWSEDIRECTORIES   1004
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_ADDDIRECTORY   1005
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_REMOVEDIRECTORY   1006
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_DISABLED   1007
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR   1008
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_STATIC   1009
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_NEWFILES   1010
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_UPDATEDFILES   1011
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_DELETEDFILES   1012
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_FILTER_STATIC   1013
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_FILTER_ALLFILES   1014
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_FILTER_SELECTEDFILES   1015
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_FILTER_SELECTEDFILESLIST   1016
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_FILTER_BROWSEFILE   1017
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_FILTER_ADDFILE   1018
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_BEHAVIOR_TRACK_FILTER_REMOVEFILE   1019
#define IDC_TELEMETRYREPORTS_FILETRIGGERS_HELP   1020

class CTelemetryReportsFileTriggersDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryReportsFileTriggersDialog)

	// Construction
public:
	CTelemetryReportsFileTriggersDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	INT  m_nIndex;
	CTelemetryReportFileTriggers  m_pTriggers[2];

	// Operations
private:
	BOOL EnumTriggerDirectories();

	VOID ShowTriggerInfo(INT nIndex = -1);
	VOID ShowFileTriggerInfo();
	VOID ShowFileTriggerInfo(CONST CTelemetryReportFileTriggerInfo *pTriggerInfo);
	CTelemetryReportFileTriggerInfo *FindTriggerInfo(INT nIndex = -1) CONST;

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsFileTriggersDialog)
	enum { IDD = IDD_TELEMETRYREPORTS_FILETRIGGERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsFileTriggersDialog)
public:
	virtual INT DoModal(CTelemetryReportInfo *pReportInfo);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelemetryReportsFileTriggersDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseDirectories();
	afx_msg void OnAddDirectory();
	afx_msg void OnRemoveDirectory();
	afx_msg void OnDisabled();
	afx_msg void OnTrackNewFiles();
	afx_msg void OnTrackUpdatedFiles();
	afx_msg void OnTrackDeletedFiles();
	afx_msg void OnFilterAllFiles();
	afx_msg void OnFilterSelectedFiles();
	afx_msg void OnBrowseFilteredFiles();
	afx_msg void OnAddFilteredFile();
	afx_msg void OnRemoveFilteredFile();
	afx_msg void OnSelchangeDirectory();
	afx_msg void OnSelchangeFilteredFiles();
	afx_msg void OnEditchangeDirectory();
	afx_msg void OnEditchangeFilteredFiles();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsScheduleDialog dialog

#define IDC_TELEMETRYREPORTS_SCHEDULE_DETAILS   1001
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_STATIC  1002
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_ONCE   1003
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_ONCE_TIME   1004
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_DAILY   1005
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_DAILY_TIME   1006
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_PERIODICAL   1007
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_PERIODICAL_STARTTIME   1008
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_PERIODICAL_INTERVAL_STATIC   1009
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_PERIODICAL_INTERVAL_TIME   1010
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_PERIODICAL_INTERVAL_TIME_STATIC   1011
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_PERIODICAL_STOP   1012
#define IDC_TELEMETRYREPORTS_SCHEDULE_EXECUTION_PERIODICAL_STOPTIME   1013
#define IDC_TELEMETRYREPORTS_SCHEDULE_HELP   1014

// Specify the telemetry reports schedule related settings
#define TELEMETRYREPORTSSCHEDULE_MINIMUMINTERVAL   1
#define TELEMETRYREPORTSSCHEDULE_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define TELEMETRYREPORTSSCHEDULE_DEFAULTINTERVAL   MINUTESPERHOUR

class CTelemetryReportsScheduleDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryReportsScheduleDialog)

	// Construction
public:
	CTelemetryReportsScheduleDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryReportInfo  m_cReportInfo[2];

	// Operations
private:
	VOID ShowScheduleInfo();

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsScheduleDialog)
	enum { IDD = IDD_TELEMETRYREPORTS_SCHEDULE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsScheduleDialog)
public:
	virtual INT DoModal(CTelemetryReportInfo *pReportInfo);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelemetryReportsScheduleDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnExecuteOnce();
	afx_msg void OnExecuteDaily();
	afx_msg void OnExecutePeriodically();
	afx_msg void OnExecuteStop();
	afx_msg void OnSpinchangeTime();
	afx_msg void OnSpinchangeDailyTime();
	afx_msg void OnSpinchangePeriodicalStartTime();
	afx_msg void OnSpinchangePeriodicalStopTime();
	afx_msg void OnSpinchangePeriodicalInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryReportsAbortDialog dialog

#define IDC_TELEMETRYREPORTS_ABORT_DETAILS   1001
#define IDC_TELEMETRYREPORTS_ABORT_LIST_STATIC   1002
#define IDC_TELEMETRYREPORTS_ABORT_LIST   1003
#define IDC_TELEMETRYREPORTS_ABORT_TRIGGEREDLIST_STATIC   1004
#define IDC_TELEMETRYREPORTS_ABORT_TRIGGEREDLIST   1005
#define IDC_TELEMETRYREPORTS_ABORT_HELP   1006

class CTelemetryReportsAbortDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryReportsAbortDialog)

	// Construction
public:
	CTelemetryReportsAbortDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryReports  m_pReports;
private:
	CStringArray  m_szColumns[2];

	// Operations
private:
	BOOL EnumJobs();

	INT CalcColumnWidth(LPCTSTR pszColumn);

	// Dialog Data
	//{{AFX_DATA(CTelemetryReportsAbortDialog)
	enum { IDD = IDD_TELEMETRYREPORTS_ABORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryReportsAbortDialog)
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
	//{{AFX_MSG(CTelemetryReportsAbortDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesArchivalsPage dialog

#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_FILES_STATIC   1002
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_FILES   1003
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_FREESPACE   1004
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_FREESPACE_STATIC   1005
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_FILES_BROWSE   1006
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_FILES_OPTIONS   1007
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_FILES_ADD   1008
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_FILES_REMOVE   1009
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_FILES_REMOVEALL   1010
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_FILES_DELETE   1011
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR   1012
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_ARCHIVING   1013
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_ALWAYS   1014
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_DAILY   1015
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_DAILY_STARTTIME   1016
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_DAILY_STATIC   1017
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_DAILY_STOPTIME   1018
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_LIMITED   1019
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_LIMITED_STARTTIME   1020
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_LIMITED_STATIC   1021
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_LIMITED_STOPTIME   1022
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_SECONDARY   1023
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_SECONDARY_FILENAME   1024
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_SECONDARY_FILENAME_STATIC   1025
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_AUDITFAILURES   1026
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_BEHAVIOR_SHOWSTATUS   1027
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES   1028
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_POLICY   1029
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_POLICY_CYCLIC   1030
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_POLICY_NONCYCLIC   1031
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_POLICY_UPDATES   1032
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_POLICY_UPDATES_STATIC   1033
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_POLICY_UPDATES_INTERVAL   1034
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_SIZE   1035
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_SIZE_UNLIMITED   1036
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_SIZE_LIMITED   1037
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_SIZE_LIMITED_SIZE_STATIC   1038
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_SIZE_LIMITED_SIZE   1039
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_PROPERTIES_SIZE_COMPRESSION   1040

// Specify the telemetry archives archivals page related settings
#define TELEMETRYARCHIVESARCHIVALSPAGE_MINIMUMSIZE   1
#define TELEMETRYARCHIVESARCHIVALSPAGE_MAXIMUMSIZE   2147483647
#define TELEMETRYARCHIVESARCHIVALSPAGE_DEFAULTSIZE   1024
#define TELEMETRYARCHIVESARCHIVALSPAGE_MINIMUMUPDATEINTERVAL   100
#define TELEMETRYARCHIVESARCHIVALSPAGE_MAXIMUMUPDATEINTERVAL   10000
#define TELEMETRYARCHIVESARCHIVALSPAGE_DEFAULTUPDATEINTERVAL   1000
#define TELEMETRYARCHIVESARCHIVALSPAGE_DAILYSTARTTIME   HOURS(8)
#define TELEMETRYARCHIVESARCHIVALSPAGE_DAILYSTOPTIME   HOURS(17)
#define TELEMETRYARCHIVESARCHIVALSPAGE_LIMITEDINTERVAL   SECONDSPERDAY

class CTelemetryArchivesArchivalsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryArchivesArchivalsPage)

	// Construction
public:
	CTelemetryArchivesArchivalsPage();

	// Attributes
private:
	CHistoryStoreFiles  m_pFiles[2];
	CHistoryStoreOptions  m_pOptions[2];
	CStringArray  m_szDeleteFiles;

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesArchivalsPage)
	enum { IDD = IDD_TELEMETRYARCHIVES_ARCHIVALSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetArchiveFiles(CONST CHistoryStoreFiles &pFiles, BOOL bInitialize = FALSE);
	BOOL GetArchiveFiles(CHistoryStoreFiles &pFiles) CONST;
	VOID SetArchiveOptions(CONST CHistoryStoreOptions &pOptions, BOOL bInitialize = FALSE);
	BOOL GetArchiveOptions(CHistoryStoreOptions &pOptions) CONST;

	BOOL EnumArchiveFilesToDelete(CStringArray &szFiles) CONST;

	class CTelemetryArchivesDialog *GetParent() CONST;

private:
	BOOL EnumArchiveFiles();

	VOID SetArchiveFileInfo();
	VOID SetArchiveFileInfo(CONST CHistoryStoreFile *pFile);
	BOOL GetArchiveFileInfo(CHistoryStoreFile *pFile) CONST;
	CHistoryStoreFile *FindArchiveFileInfo() CONST;

	INT FindFileToDelete(LPCTSTR pszFileName) CONST;

	CString GetFreeArchiveDiskSpace(LPCTSTR pszFileName) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesArchivalsPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesArchivalsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseFiles();
	afx_msg void OnOptions();
	afx_msg void OnAddFile();
	afx_msg void OnRemoveFile();
	afx_msg void OnRemoveFiles();
	afx_msg void OnDeleteFile();
	afx_msg void OnSelchangeFile();
	afx_msg void OnPerformArchiving();
	afx_msg void OnArchiveAlways();
	afx_msg void OnArchiveDaily();
	afx_msg void OnArchiveLimited();
	afx_msg void OnUseSecondary();
	afx_msg void OnUseUpdates();
	afx_msg void OnUseCompression();
	afx_msg void OnAuditFailures();
	afx_msg void OnShowStatus();
	afx_msg void OnCyclicMode();
	afx_msg void OnNonCyclicMode();
	afx_msg void OnUnlimitedSize();
	afx_msg void OnLimitedSize();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeSecondaryFileName();
	afx_msg void OnSpinchangeDailyStartTime();
	afx_msg void OnSpinchangeDailyStopTime();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnSpinchangeUpdates();
	afx_msg void OnSpinchangeSize();
	afx_msg void OnUpdateStorageMediaFreeSpace();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesArchivalsOptionsDialog dialog

#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPACKET_STATIC   1002
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPACKET   1003
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPACKET_RETENTION   1004
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPACKET_RETENTION_DAYS   1005
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPACKET_RETENTION_STATIC   1006
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPACKET_NORETENTION   1007
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPARAMETER_STATIC   1008
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPARAMETER   1009
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPARAMETER_RETENTION   1010
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPARAMETER_RETENTION_DAYS   1011
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPARAMETER_RETENTION_STATIC   1012
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_TMPARAMETER_NORETENTION   1013
#define IDC_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_HELP   1014

// Specify the telemetry archives archivals options dialog related settings
#define TELEMETRYARCHIVESARCHIVALSOPTIONS_MINIMUMRETENTION   0
#define TELEMETRYARCHIVESARCHIVALSOPTIONS_MAXIMUMRETENTION   1000
#define TELEMETRYARCHIVESARCHIVALSOPTIONS_DEFAULTRETENTION   7

class CTelemetryArchivesArchivalsOptionsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryArchivesArchivalsOptionsDialog)

	// Construction
public:
	CTelemetryArchivesArchivalsOptionsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CHistoryStoreOptions  m_pOptions[2];

	// Operations
private:
	BOOL EnumPackets();
	BOOL EnumParameters();

	VOID ShowOptionsInfo();

	BOOL AddOptionInfo(CHistoryStoreOptionInfo *pOptionInfo);
	BOOL RemoveOptionInfo(CHistoryStoreOptionInfo *pOptionInfo);
	CHistoryStoreOptionInfo *FindOptionInfo(UINT nType, BOOL bAll = FALSE) CONST;

	CString ExtractTag(UINT nType, LPCTSTR pszDetails) CONST;

	class CTelemetryArchivesArchivalsPage *GetParent() CONST;

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesArchivalsOptionsDialog)
	enum { IDD = IDD_TELEMETRYARCHIVES_ARCHIVALSPAGE_OPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesArchivalsOptionsDialog)
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
	//{{AFX_MSG(CTelemetryArchivesArchivalsOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPacketRetention();
	afx_msg void OnPacketNoRetention();
	afx_msg void OnParameterRetention();
	afx_msg void OnParameterNoRetention();
	afx_msg void OnSelchangePacket();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSpinchangePacketRetention();
	afx_msg void OnSpinchangeParameterRetention();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesRetrievalsPage dialog

#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_FILES_STATIC   1002
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_FILES   1003
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_FREESPACE   1004
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_FREESPACE_STATIC   1005
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_FILES_BROWSE   1006
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_FILES_INSPECT   1007
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_FILES_DEFAULT   1008
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_FILES_ADD   1009
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_FILES_REMOVE   1010
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_FILES_REMOVEALL   1011
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_AUTOBROWSE   1012
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_AUTOBROWSE_LIST   1013
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_AUTOBROWSE_ANYFILE   1014
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_AUTOBROWSE_DIRECTORY   1015
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_AUTOBROWSE_ANYFILE_DIRECTORY   1016
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_AUTOBROWSE_TIMETAGGEDFILES   1017
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_AUTOBROWSE_TIMETAGGEDFILES_DIRECTORY   1018
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_AUTOBROWSE_ENUMERATEDFILES   1019
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_AUTOBROWSE_ENUMERATEDFILES_DIRECTORY   1020
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO   1021
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_COMMENTS   1022
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_PRODUCT_STATIC   1023
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_PRODUCT   1024
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_COMPANY_STATIC   1025
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_COMPANY   1026
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_SPACECRAFT_STATIC   1027
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_SPACECRAFT   1028
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_TYPE_STATIC   1029
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_TYPE   1030
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_TIMERANGE_STATIC   1031
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_TIMERANGE_STARTTIME   1032
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_TIMERANGE_TO   1033
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_TIMERANGE_STOPTIME   1034
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_CREATIONTIME_STATIC   1035
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_CREATIONTIME   1036
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_SIZE_STATIC   1037
#define IDC_TELEMETRYARCHIVES_RETRIEVALSPAGE_SOURCEINFO_SIZE   1038

class CTelemetryArchivesRetrievalsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryArchivesRetrievalsPage)

	// Construction
public:
	CTelemetryArchivesRetrievalsPage();

	// Attributes
private:
	CString  m_szDefaultFile[2];
	CUIntArray  m_nBrowseOptions[2];
	CStringArray  m_szBrowseDirectories[2];
	CHistoryStoreFiles  m_pFiles[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesRetrievalsPage)
	enum { IDD = IDD_TELEMETRYARCHIVES_RETRIEVALSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetRetrieveFiles(CONST CHistoryStoreFiles &pFiles, BOOL bInitialize = FALSE);
	BOOL GetRetrieveFiles(CHistoryStoreFiles &pFiles) CONST;
	VOID SetDefaultRetrieveFile(CONST CHistoryStoreFile &cFile, BOOL bInitialize = FALSE);
	VOID GetDefaultRetrieveFile(CHistoryStoreFile &cFile) CONST;

	VOID SetBrowseOptions(CONST CUIntArray &nOptions, CONST CStringArray &szDirectories, BOOL bInitialize = FALSE);
	BOOL GetBrowseOptions(CUIntArray &nOptions, CStringArray &szDirectories) CONST;

	class CTelemetryArchivesDialog *GetParent() CONST;

private:
	BOOL EnumRetrieveFiles();

	VOID SetRetrieveFileInfo();
	VOID SetRetrieveFileInfo(CONST CHistoryStoreFile *pFile);
	BOOL GetRetrieveFileInfo(CHistoryStoreFile *pFile) CONST;
	CHistoryStoreFile *FindRetrieveFileInfo() CONST;

	VOID ShowDataSourceInfo(LPCTSTR pszFileName = NULL);

	BOOL CheckRetrieveFile(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST;

	CString GetFreeRetrieveDiskSpace(LPCTSTR pszFileName) CONST;

	CString FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST;

	VOID AddBrowseOption(UINT nOption, LPCTSTR pszDirectory);
	VOID RemoveBrowseOption(UINT nOption);
	BOOL CheckBrowseOption(UINT nOption) CONST;
	INT FindBrowseOption(UINT nOption) CONST;
	CString GetBrowseDirectory(UINT nOption) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesRetrievalsPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesRetrievalsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseFiles();
	afx_msg void OnInspectFile();
	afx_msg void OnAddFile();
	afx_msg void OnRemoveFile();
	afx_msg void OnRemoveFiles();
	afx_msg void OnDefaultFile();
	afx_msg void OnSelchangeFile();
	afx_msg void OnBrowseAnyFiles();
	afx_msg void OnBrowseTimeTaggedFiles();
	afx_msg void OnBrowseEnumeratedFiles();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeAnyFileDirectory();
	afx_msg void OnEditchangeTimeTaggedFileDirectory();
	afx_msg void OnEditchangeEnumeratedFileDirectory();
	afx_msg void OnUpdateStorageMediaFreeSpace();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesBackupsPage dialog

#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_FILES_STATIC   1002
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_FILES   1003
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS   1004
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_TYPE   1005
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_TYPE_SIMPLE   1006
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_TYPE_TIMETAGGED   1007
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_TYPE_ENUMERATED   1008
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_DIRECTORY_STATIC   1009
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_DIRECTORY   1010
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_TRIGGER   1011
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_TRIGGER_AUTO   1012
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_TRIGGER_SIZE   1013
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_TRIGGER_SIZE_MB   1014
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_CHARACTERISTICS_TRIGGER_SIZE_MB_STATIC   1015
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR   1016
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_BACKUPS   1017
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_RESTRICTIONS   1018
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_RESTRICTION_DAILY   1019
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_RESTRICTION_DAILY_STARTTIME   1020
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_RESTRICTION_DAILY_STATIC   1021
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_RESTRICTION_DAILY_STOPTIME   1022
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_RESTRICTION_TIME   1023
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_RESTRICTION_TIME_STATIC   1024
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_RESTRICTION_TIME_PERIOD   1025
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_RESTRICTION_PROTECTION   1026
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_RESTRICTION_DISK   1027
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_FAILURES   1028
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_FAILURES_STATIC   1029
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_FAILURES_RETRY_COUNT   1030
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_FAILURES_RETRY_INTERVAL_STATIC   1031
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_FAILURES_RETRY_INTERVAL   1032
#define IDC_TELEMETRYARCHIVES_BACKUPSPAGE_BEHAVIOR_AUDITFAILURES   1033

// Specify the telemetry archives backups page related settings
#define TELEMETRYARCHIVESBACKUPSPAGE_MINIMUMSIZE   1
#define TELEMETRYARCHIVESBACKUPSPAGE_MAXIMUMSIZE   2147483647
#define TELEMETRYARCHIVESBACKUPSPAGE_DEFAULTSIZE   1024
#define TELEMETRYARCHIVESBACKUPSPAGE_MINIMUMPERIOD   1
#define TELEMETRYARCHIVESBACKUPSPAGE_MAXIMUMPERIOD   MINUTESPERWEEK
#define TELEMETRYARCHIVESBACKUPSPAGE_DEFAULTPERIOD   MINUTESPERHOUR
#define TELEMETRYARCHIVESBACKUPSPAGE_MINIMUMRETRIES   1
#define TELEMETRYARCHIVESBACKUPSPAGE_MAXIMUMRETRIES   100
#define TELEMETRYARCHIVESBACKUPSPAGE_DEFAULTRETRIES   5
#define TELEMETRYARCHIVESBACKUPSPAGE_MINIMUMRETRYINTERVAL   1
#define TELEMETRYARCHIVESBACKUPSPAGE_MAXIMUMRETRYINTERVAL   MINUTESPERWEEK
#define TELEMETRYARCHIVESBACKUPSPAGE_DEFAULTRETRYINTERVAL   5
#define TELEMETRYARCHIVESBACKUPSPAGE_DAILYSTARTTIME   HOURS(8)
#define TELEMETRYARCHIVESBACKUPSPAGE_DAILYSTOPTIME   HOURS(17)

class CTelemetryArchivesBackupsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryArchivesBackupsPage)

	// Construction
public:
	CTelemetryArchivesBackupsPage();

	// Attributes
private:
	CHistoryStoreFiles  m_pFiles[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesBackupsPage)
	enum { IDD = IDD_TELEMETRYARCHIVES_BACKUPSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetArchiveFiles(CONST CHistoryStoreFiles &pFiles, BOOL bInitialize = FALSE);
	BOOL GetArchiveFiles(CHistoryStoreFiles &pFiles) CONST;

	class CTelemetryArchivesDialog *GetParent() CONST;

private:
	BOOL EnumArchiveFiles();

	VOID ShowArchiveFileInfo();
	VOID ShowArchiveFileInfo(CONST CHistoryStoreFile *pFile);
	CHistoryStoreFile *FindArchiveFileInfo() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesBackupsPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesBackupsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeFile();
	afx_msg void OnTypeSimple();
	afx_msg void OnTypeTimeTagged();
	afx_msg void OnTypeEnumerated();
	afx_msg void OnEditchangeDirectory();
	afx_msg void OnBackups();
	afx_msg void OnBackupByDefault();
	afx_msg void OnBackupBySize();
	afx_msg void OnBackupDaily();
	afx_msg void OnBackupTime();
	afx_msg void OnBackupProtectedDisk();
	afx_msg void OnBackupEmptyDisk();
	afx_msg void OnBackupFailures();
	afx_msg void OnBackupAuditFailures();
	afx_msg void OnSpinchangeBackupBySize();
	afx_msg void OnSpinchangeBackupDailyStartTime();
	afx_msg void OnSpinchangeBackupDailyStopTime();
	afx_msg void OnSpinchangeBackupTime();
	afx_msg void OnSpinchangeBackupRetries();
	afx_msg void OnSpinchangeBackupInterval();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesExtractionsContentsPage dialog

#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_PARAMETER_STATIC   1002
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_PARAMETER   1003
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_MEMBERS_STATIC   1004
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_MEMBERS   1005
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_CODING_STATIC   1006
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_CODING_DEFAULT   1007
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_CODING_CODED   1008
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_CODING_RAW   1009
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_CODING_RAW_DECIMAL   1010
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_CODING_RAW_BINARY   1011
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_CODING_RAW_OCTAL   1012
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_CODING_RAW_HEXADECIMAL   1013
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_CODING_RAW_INVERSE   1014
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_CODING_STATUS   1015
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_TRIGGER_STATIC   1016
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_TRIGGER_CHANGES   1017
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_ADD   1018
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_REMOVE   1019
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE_REMOVEALL   1020

class CTelemetryArchivesExtractionsContentsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryArchivesExtractionsContentsPage)

	// Construction
public:
	CTelemetryArchivesExtractionsContentsPage();

	// Attributes
private:
	CArchivesExtractionProfileInfo  m_cInfo[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesExtractionsContentsPage)
	enum { IDD = IDD_TELEMETRYARCHIVES_EXTRACTIONS_CONTENTSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CArchivesExtractionProfileInfo *pProfileInfo, CONST CArchivesExtractionProfileInfo *pBackupProfileInfo = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CArchivesExtractionProfileInfo *pProfileInfo) CONST;

	class CTelemetryArchivesExtractionsPageFolder *GetParent() CONST;

private:
	VOID EnumParameters();
	VOID EnumParameterMembers();

	VOID ShowParameterInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsContentsPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesExtractionsContentsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnCodingDefault();
	afx_msg void OnCodingCoded();
	afx_msg void OnCodingRaw();
	afx_msg void OnCodingDecimal();
	afx_msg void OnCodingBinary();
	afx_msg void OnCodingOctal();
	afx_msg void OnCodingHexadecimal();
	afx_msg void OnCodingInverse();
	afx_msg void OnCodingStatus();
	afx_msg void OnTriggerChanges();
	afx_msg void OnAddParameter();
	afx_msg void OnRemoveParameter();
	afx_msg void OnRemoveAllParameters();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeMember();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesExtractionsRangePage dialog

#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_EXTRACT_STATIC   1002
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_TIMEPERIOD   1003
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_TIMEPERIOD_STARTTIME   1004
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_TIMEPERIOD_STATIC   1005
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_TIMEPERIOD_STOPTIME   1006
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_DAILYPERIOD   1007
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_DAILYPERIOD_STARTTIME   1008
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_DAILYPERIOD_STATIC   1009
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_DAILYPERIOD_STOPTIME   1010
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_PERIOD_ALL   1011
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_PERIOD_ALL_STATIC   1012
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_PERIOD_PART   1013
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_PERIOD_PART_STATIC   1014
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_PERIOD_PART_MINUTES_STATIC   1015
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_PERIOD_PART_MINUTES   1016
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_TRIGGER   1017
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_TRIGGER_STATIC   1018
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_TRIGGER_MINUTES_PREFIX_STATIC   1019
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_TRIGGER_MINUTES   1020
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_TRIGGER_MINUTES_REFERENCE   1021
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_TRIGGER_MINUTES_SUFFIX_STATIC   1022
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_INTERVAL   1023
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_INTERVAL_STATIC   1024
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE_INTERVAL_MINUTES   1025

// Specify the telemetry archives extractions range related settings
#define TELEMETRYARCHIVESEXTRACTIONSRANGE_MINIMUMINTERVAL   0
#define TELEMETRYARCHIVESEXTRACTIONSRANGE_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define TELEMETRYARCHIVESEXTRACTIONSRANGE_DEFAULTINTERVAL   MINUTESPERHOUR
#define TELEMETRYARCHIVESEXTRACTIONSRANGE_DAILYSTARTTIME   HOURS(8)
#define TELEMETRYARCHIVESEXTRACTIONSRANGE_DAILYSTOPTIME   HOURS(17)

class CTelemetryArchivesExtractionsRangePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryArchivesExtractionsRangePage)

	// Construction
public:
	CTelemetryArchivesExtractionsRangePage();

	// Attributes
private:
	CArchivesExtractionProfileInfo  m_cInfo[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesExtractionsRangePage)
	enum { IDD = IDD_TELEMETRYARCHIVES_EXTRACTIONS_RANGEPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CArchivesExtractionProfileInfo *pProfileInfo, CONST CArchivesExtractionProfileInfo *pBackupProfileInfo = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CArchivesExtractionProfileInfo *pProfileInfo) CONST;

	class CTelemetryArchivesExtractionsPageFolder *GetParent() CONST;

private:
	VOID ShowRangeInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsRangePage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesExtractionsRangePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimeRange();
	afx_msg void OnDailyTimeRange();
	afx_msg void OnPeriodicalRange();
	afx_msg void OnPeriodicalPartialRange();
	afx_msg void OnTriggeredRange();
	afx_msg void OnRangeInterval();
	afx_msg void OnSelchangeTriggerReference();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnSpinchangeDailyStartTime();
	afx_msg void OnSpinchangeDailyStopTime();
	afx_msg void OnSpinchangePeriodicalInterval();
	afx_msg void OnSpinchangeTriggeredInterval();
	afx_msg void OnSpinchangeRangeInterval();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesExtractionsExecutionPage dialog

#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_STATIC   1002
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_IMMEDIATELY   1003
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_ONCE   1004
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_ONCE_TIME   1005
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_DAILY   1006
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_DAILY_TIME   1007
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_PERIODICALLY   1008
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_PERIODICALLY_STARTTIME   1009
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_PERIODICALLY_INTERVAL_STATIC   1010
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_PERIODICALLY_INTERVAL   1011
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_PERIODICALLY_INTERVAL_MINUTES_STATIC   1012
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_PERIODICALLY_STOPTIME_STATIC   1013
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_PERIODICALLY_STOPTIME   1014
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_EVENT   1015
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE_RUN_EVENT_NAME   1016

// Specify the telemetry archives extractions execution related settings
#define TELEMETRYARCHIVESEXTRACTIONSEXECUTION_MINIMUMINTERVAL   1
#define TELEMETRYARCHIVESEXTRACTIONSEXECUTION_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define TELEMETRYARCHIVESEXTRACTIONSEXECUTION_DEFAULTINTERVAL   MINUTESPERHOUR

class CTelemetryArchivesExtractionsExecutionPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryArchivesExtractionsExecutionPage)

	// Construction
public:
	CTelemetryArchivesExtractionsExecutionPage();

	// Attributes
private:
	CArchivesExtractionProfileInfo  m_cInfo[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesExtractionsExecutionPage)
	enum { IDD = IDD_TELEMETRYARCHIVES_EXTRACTIONS_EXECUTIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CArchivesExtractionProfileInfo *pProfileInfo, CONST CArchivesExtractionProfileInfo *pBackupProfileInfo = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CArchivesExtractionProfileInfo *pProfileInfo) CONST;

	class CTelemetryArchivesExtractionsPageFolder *GetParent() CONST;

private:
	BOOL EnumEvents();

	VOID ShowExecutionInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsExecutionPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesExtractionsExecutionPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnExecutionNow();
	afx_msg void OnExecutionAtTime();
	afx_msg void OnExecutionAtDailyTime();
	afx_msg void OnExecutionAtPeriodicalTime();
	afx_msg void OnExecutionAtEvent();
	afx_msg void OnSelchangeExecutionEvent();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg void OnSpinchangeExecutionDailyTime();
	afx_msg void OnSpinchangeExecutionPeriodicalStartTime();
	afx_msg void OnSpinchangeExecutionPeriodicalStopTime();
	afx_msg void OnSpinchangeExecutionPeriodicalInterval();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesExtractionsFTPTransfersPage dialog

#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_LOCATION_STATIC   1002
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_LOCATION   1003
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_USERNAME_STATIC   1004
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_USERNAME   1005
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_PASSWORD_STATIC   1006
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_PASSWORD   1007
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_PORT   1008
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_PORT_NUMBER   1009
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_FTPTRANSFERS   1010
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_BEHAVIOR   1011
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_BEHAVIOR_STATIC   1012
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_RETRY_NEVER   1013
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_RETRY_CONTINUOUSLY   1014
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_RETRY_COUNT   1015
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_RETRY_COUNT_STATIC   1016
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_RETRY_COUNT_NUMBER   1017
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_RETRY_INTERVAL_STATIC   1018
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_RETRY_INTERVAL   1019
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_RETRY_INTERVAL_MINUTES_STATIC   1020
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_AUDITION   1021
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_AUDITION_STATIC   1022
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_AUDITION_NOTHING   1023
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_AUDITION_EVERYTHING   1024
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE_AUDITION_FAILURES   1025

// Specify the telemetry archives extractions FTP transfers related settings
#define TELEMETRYARCHIVESEXTRACTIONSFTPTRANSFERS_FIRSTPORT   1024
#define TELEMETRYARCHIVESEXTRACTIONSFTPTRANSFERS_LASTPORT   65535
#define TELEMETRYARCHIVESEXTRACTIONSFTPTRANSFERS_DEFAULTPORT   1024
#define TELEMETRYARCHIVESEXTRACTIONSFTPTRANSFERS_MINIMUMRETRIES   1
#define TELEMETRYARCHIVESEXTRACTIONSFTPTRANSFERS_MAXIMUMRETRIES   100
#define TELEMETRYARCHIVESEXTRACTIONSFTPTRANSFERS_DEFAULTRETRIES   5
#define TELEMETRYARCHIVESEXTRACTIONSFTPTRANSFERS_MINIMUMRETRYINTERVAL   1
#define TELEMETRYARCHIVESEXTRACTIONSFTPTRANSFERS_MAXIMUMRETRYINTERVAL   MINUTESPERHOUR
#define TELEMETRYARCHIVESEXTRACTIONSFTPTRANSFERS_DEFAULTRETRYINTERVAL   5

class CTelemetryArchivesExtractionsFTPTransfersPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryArchivesExtractionsFTPTransfersPage)

	// Construction
public:
	CTelemetryArchivesExtractionsFTPTransfersPage();

	// Attributes
private:
	CArchivesExtractionProfileInfo  m_cInfo[2];

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesExtractionsFTPTransfersPage)
	enum { IDD = IDD_TELEMETRYARCHIVES_EXTRACTIONS_FTPTRANSFERSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CArchivesExtractionProfileInfo *pProfileInfo, CONST CArchivesExtractionProfileInfo *pBackupProfileInfo = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CArchivesExtractionProfileInfo *pProfileInfo) CONST;

	class CTelemetryArchivesExtractionsPageFolder *GetParent() CONST;

private:
	VOID ShowFTPTransfersInfo();

	BOOL CheckURL(LPCTSTR pszLocation) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsFTPTransfersPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesExtractionsFTPTransfersPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEnable();
	afx_msg void OnUsePort();
	afx_msg void OnRetryNever();
	afx_msg void OnRetryContinuously();
	afx_msg void OnRetryLimited();
	afx_msg void OnAuditNothing();
	afx_msg void OnAuditEverything();
	afx_msg void OnAuditFailures();
	afx_msg void OnEditchangeLocation();
	afx_msg void OnEditchangeUserName();
	afx_msg void OnEditchangePassword();
	afx_msg void OnSpinchangePort();
	afx_msg void OnSpinchangeRetries();
	afx_msg void OnSpinchangeRetryInterval();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesExtractionsAutomationPage dialog

#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE_NAME_STATIC   1002
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE_NAME   1003
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE_TYPE_STATIC   1004
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE_TYPE   1005
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE_CODE_STATIC   1006
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE_CODE   1007
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE_OPTIONS_STATIC   1008
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE_OPTIONS_FTPTRANSFER   1009
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE_OPTIONS_DISABLED   1010

class CTelemetryArchivesExtractionsAutomationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryArchivesExtractionsAutomationPage)

	// Construction
public:
	CTelemetryArchivesExtractionsAutomationPage();

	// Attributes
private:
	CAutomationScripts  m_pScripts;
	CArchivesExtractionProfileInfo  m_cInfo[2];
private:
	CFont  m_cCodeFont;

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesExtractionsAutomationPage)
	enum { IDD = IDD_TELEMETRYARCHIVES_EXTRACTIONS_AUTOMATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CArchivesExtractionProfileInfo *pProfileInfo, CONST CArchivesExtractionProfileInfo *pBackupProfileInfo = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CArchivesExtractionProfileInfo *pProfileInfo) CONST;

	class CTelemetryArchivesExtractionsPageFolder *GetParent() CONST;

private:
	BOOL EnumAutomationScripts();

	VOID ShowAutomationScriptInfo();
	VOID ShowAutomationScriptInfo(CONST CAutomationScript *pScript);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsAutomationPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesExtractionsAutomationPage)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFTPTransferScript();
	afx_msg void OnDisabledScript();
	afx_msg void OnSelchangeScript();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesExtractionsPageTabCtrl window

class CTelemetryArchivesExtractionsPageTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTelemetryArchivesExtractionsPageTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTelemetryArchivesExtractionsPageFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsPageTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelemetryArchivesExtractionsPageTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesExtractionsPageFolder

class CTelemetryArchivesExtractionsPageFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNAMIC(CTelemetryArchivesExtractionsPageFolder)

	// Construction
public:
	CTelemetryArchivesExtractionsPageFolder();

	// Attributes
private:
	CTelemetryArchivesExtractionsRangePage  m_pageRange;
	CTelemetryArchivesExtractionsContentsPage  m_pageContents;
	CTelemetryArchivesExtractionsExecutionPage  m_pageExecution;
	CTelemetryArchivesExtractionsAutomationPage  m_pageAutomation;
	CTelemetryArchivesExtractionsFTPTransfersPage  m_pageFTPTransfers;
	CTelemetryArchivesExtractionsPageTabCtrl  m_wndTabCtrl;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID SetInfo(CONST CArchivesExtractionProfileInfo *pProfileInfo, BOOL bUpdate = TRUE);
	VOID SetInfo(CONST CArchivesExtractionProfileInfo *pProfileInfo, CONST CArchivesExtractionProfileInfo *pBackupProfileInfo);
	VOID GetInfo(CArchivesExtractionProfileInfo *pProfileInfo) CONST;

	class CTelemetryArchivesExtractionsPage *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsPageFolder)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	virtual BOOL Check(BOOL bModified, BOOL bChecked) CONST;
protected:
	virtual VOID RepositionButtons();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelemetryArchivesExtractionsPageFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesExtractionsPage dialog

#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_PROFILE_STATIC   1002
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_PROFILE   1003
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_SAVE   1004
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_DELETE   1005
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_DELETEALL   1006
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_SUBMIT   1007
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_ABORT   1008
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_SOURCE_STATIC   1009
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_DESTINATION_STATIC   1010
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_SOURCE   1011
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_BROWSE   1012
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT   1013
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_DELIMITERS_STATIC   1014
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_DELIMITERS_COLUMN_STATIC   1015
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_DELIMITERS_COLUMN   1016
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_DELIMITERS_ROW_STATIC   1017
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_DELIMITERS_ROW   1018
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_DELIMITERS_TEXT_STATIC   1019
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_DELIMITERS_TEXT   1020
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_TIME_STATIC   1021
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_TIME   1022
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_CHARSET_STATIC   1023
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_CHARSET_ASCII   1024
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_CHARSET_UNICODE   1025
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FORMAT_TITLEOPTION   1026
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_FOLDER   1027

class CTelemetryArchivesExtractionsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryArchivesExtractionsPage)

	// Construction
public:
	CTelemetryArchivesExtractionsPage();

	// Attributes
private:
	CHistoryStoreFiles  m_pFiles;
	CArchivesExtractionProfiles  m_pProfiles[3];
private:
	CTelemetryArchivesExtractionsPageFolder  *m_pwndFolderCtrl;
private:
	CString  m_szSourceFile;
	CString  m_szDestinationDirectory;
private:
	UINT  m_nLocked;

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesExtractionsPage)
	enum { IDD = IDD_TELEMETRYARCHIVES_EXTRACTIONSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetExtractionProfiles(CONST CArchivesExtractionProfiles &pProfiles, BOOL bInitialize = FALSE);
	BOOL GetExtractionProfiles(CArchivesExtractionProfiles &pProfiles) CONST;
	VOID SetRetrieveFiles(CONST CHistoryStoreFiles &pFiles);
	BOOL GetRetrieveFiles(CHistoryStoreFiles &pFiles) CONST;

	class CTelemetryArchivesDialog *GetParent() CONST;

private:
	BOOL EnumExtractionProfiles();

	BOOL CheckExtractionProfiles() CONST;

	VOID SetExtractionProfileInfo(BOOL bInitialize = FALSE);
	VOID UpdateExtractionProfileInfo(CONST CArchivesExtractionProfileInfo *pProfileInfo, BOOL bInitialize);
	BOOL GetExtractionProfileInfo(CArchivesExtractionProfileInfo *pProfileInfo) CONST;
	CArchivesExtractionProfileInfo *FindExtractionProfileInfo() CONST;

	BOOL EnumExtractionSources();
	BOOL EnumExtractionDelimiters();
	BOOL EnumExtractionTimeFormats();

	CString ConvertSymbolToDelimiter(LPCTSTR pszSymbol) CONST;
	CString ConvertDelimiterToSymbol(LPCTSTR pszDelimiter) CONST;

	CRect CalcFolderSize() CONST;

	VOID AdjustToPrivileges();

	VOID Lock();
	BOOL IsLocked() CONST;
	VOID Unlock();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bModified, BOOL bChecked) CONST;
	virtual VOID Update(BOOL bModified, BOOL bChecked) CONST;
public:
	virtual BOOL OnSetActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesExtractionsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSave();
	afx_msg void OnDelete();
	afx_msg void OnDeleteAll();
	afx_msg void OnSubmit();
	afx_msg void OnAbort();
	afx_msg void OnBrowse();
	afx_msg void OnCharsetASCII();
	afx_msg void OnCharsetUnicode();
	afx_msg void OnTitleOption();
	afx_msg void OnEditchangeProfile();
	afx_msg void OnEditchangeSource();
	afx_msg void OnSelchangeProfile();
	afx_msg void OnSelchangeSource();
	afx_msg void OnSelchangeColumnDelimiter();
	afx_msg void OnSelchangeRowDelimiter();
	afx_msg void OnSelchangeTextDelimiter();
	afx_msg void OnSelchangeTimeFormat();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesExtractionsAbortDialog dialog

#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_ABORT_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_ABORT_LIST_STATIC   1002
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_ABORT_LIST   1003
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_ABORT_TRIGGEREDLIST_STATIC   1004
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_ABORT_TRIGGEREDLIST   1005
#define IDC_TELEMETRYARCHIVES_EXTRACTIONSPAGE_ABORT_HELP   1006

class CTelemetryArchivesExtractionsAbortDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryArchivesExtractionsAbortDialog)

	// Construction
public:
	CTelemetryArchivesExtractionsAbortDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CArchivesExtractionProfiles  m_pProfiles[2];
private:
	CStringArray  m_szColumns[2];

	// Operations
private:
	BOOL EnumExtractionJobs();

	INT CalcColumnWidth(LPCTSTR pszColumn);

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesExtractionsAbortDialog)
	enum { IDD = IDD_TELEMETRYARCHIVES_EXTRACTIONSPAGE_ABORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsAbortDialog)
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
	//{{AFX_MSG(CTelemetryArchivesExtractionsAbortDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesExtractionsImportDialog dialog

#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_FILENAME_STATIC   1002
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_FILENAME   1003
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_BROWSE   1004
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_INSPECT   1005
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_DIRECTORY_STATIC   1006
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_DIRECTORY   1007
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_ADD   1008
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_ADDALL   1009
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_ATTENTION   1010
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_ATTENTION_TEXT   1011
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_LIST_STATIC   1012
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_LIST   1013
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_REMOVE   1014
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_REMOVEALL   1015
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_HELP   1016

class CTelemetryArchivesExtractionsImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryArchivesExtractionsImportDialog)

	// Construction
public:
	CTelemetryArchivesExtractionsImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CArchivesExtractionProfiles  m_pProfiles[3];

	// Operations
private:
	VOID EnumProfiles();

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesExtractionsImportDialog)
	enum { IDD = IDD_TELEMETRYARCHIVES_EXTRACTIONS_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsImportDialog)
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
	//{{AFX_MSG(CTelemetryArchivesExtractionsImportDialog)
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
// CTelemetryArchivesExtractionsExportDialog dialog

#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_DIRECTORY_STATIC   1002
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_DIRECTORY   1003
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_ADD   1004
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_ADDALL   1005
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_LIST_STATIC   1006
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_LIST   1007
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_REMOVE   1008
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_REMOVEALL   1009
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_FILENAME_STATIC   1010
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_FILENAME   1011
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_BROWSE   1012
#define IDC_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_HELP   1013

class CTelemetryArchivesExtractionsExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryArchivesExtractionsExportDialog)

	// Construction
public:
	CTelemetryArchivesExtractionsExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CArchivesExtractionProfiles  m_pProfiles[2];

	// Operations
private:
	BOOL EnumProfiles();

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesExtractionsExportDialog)
	enum { IDD = IDD_TELEMETRYARCHIVES_EXTRACTIONS_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesExtractionsExportDialog)
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
	//{{AFX_MSG(CTelemetryArchivesExtractionsExportDialog)
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
// CTelemetryArchivesToolsPage dialog

#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_FILENAME_STATIC   1002
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_FILENAME   1003
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_FILENAME_BROWSE   1004
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_SOURCES_STATIC   1005
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_SOURCES   1006
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_SOURCES_BROWSE   1007
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_SOURCES_ADD   1008
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_SOURCES_REMOVE   1009
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES   1010
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_FORMAT_STATIC   1011
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_FORMAT_STANDARD   1012
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_FORMAT_RAW   1013
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_FORMAT_OPTIONS   1014
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_GAPS_STATIC   1015
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_GAPS   1016
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_GAPS_SECONDS_STATIC   1017
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_UPDATES   1018
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_UPDATES_UNITS_STATIC   1019
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_UPDATES_INTERVAL   1020
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS   1021
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_START_STATIC   1022
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_START_FROM   1023
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_START_FROMTIME   1024
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_START_FILEBEGIN   1025
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_STOP_STATIC   1026
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_STOP_AT   1027
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_STOP_ATTIME   1028
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_STOP_AFTER   1029
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_STOP_AFTER_STATIC   1030
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_STOP_AFTERSIZE   1031
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_STOP_DISKFULL   1032
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_FILTERING   1033
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_FILTERING_LIST_STATIC   1034
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_FILTERING_LIST    1035
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_FILTERING_REMOVE   1036
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_RESTRICTIONS_FILTERING_ADDALL   1037
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_EXECUTION   1038
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_EXECUTION_RANGE   1039
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_EXECUTION_RANGE_STARTTIME   1040
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_EXECUTION_RANGE_STATIC   1041
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_EXECUTION_RANGE_STOPTIME   1042
#define IDC_TELEMETRYARCHIVES_TOOLSPAGE_PROPERTIES_EXECUTION_ABORT   1043

// Specify the telemetry archives tools page related settings
#define TELEMETRYARCHIVESTOOLSPAGE_MINIMUMGAPINTERVAL   1
#define TELEMETRYARCHIVESTOOLSPAGE_MAXIMUMGAPINTERVAL   SECONDSPERHOUR
#define TELEMETRYARCHIVESTOOLSPAGE_DEFAULTGAPINTERVAL   1
#define TELEMETRYARCHIVESTOOLSPAGE_MINIMUMUPDATEINTERVAL   100
#define TELEMETRYARCHIVESTOOLSPAGE_MAXIMUMUPDATEINTERVAL   10000
#define TELEMETRYARCHIVESTOOLSPAGE_DEFAULTUPDATEINTERVAL   1000
#define TELEMETRYARCHIVESTOOLSPAGE_MINIMUMSIZE   1
#define TELEMETRYARCHIVESTOOLSPAGE_MAXIMUMSIZE   2147483647
#define TELEMETRYARCHIVESTOOLSPAGE_DEFAULTSIZE   1024
#define TELEMETRYARCHIVESTOOLSPAGE_DAILYSTARTTIME   HOURS(8)
#define TELEMETRYARCHIVESTOOLSPAGE_DAILYSTOPTIME   HOURS(17)
#define TELEMETRYARCHIVESTOOLSPAGE_INTERVALTIME   SECONDSPERHOUR

class CTelemetryArchivesToolsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryArchivesToolsPage)

	// Construction
public:
	CTelemetryArchivesToolsPage();

	// Attributes
private:
	CHistoryFileExtractionProfiles  m_pProfiles[2];
private:
	BOOL  m_bExecuting;

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesToolsPage)
	enum { IDD = IDD_TELEMETRYARCHIVES_TOOLSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetExtractionProfiles(CONST CHistoryFileExtractionProfiles &pProfiles, BOOL bInitialize = FALSE);
	BOOL GetExtractionProfiles(CHistoryFileExtractionProfiles &pProfiles) CONST;

	class CTelemetryArchivesDialog *GetParent() CONST;

private:
	VOID ShowExtractionProfileInfo();

	VOID EnumExtractionSources(CONST CHistoryFileExtractionProfileInfo *pProfileInfo);
	VOID EnumExtractionFilters(CONST CHistoryFileExtractionProfileInfo *pProfileInfo);

	CHistoryFileExtractionProfileInfo *FindExtractionProfileInfo() CONST;

	BOOL IsExtractionExecuting() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesToolsPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesToolsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnFilenameBrowse();
	afx_msg void OnSourceBrowse();
	afx_msg void OnAddSource();
	afx_msg void OnRemoveSource();
	afx_msg void OnUpdateInterval();
	afx_msg void OnFormatStandard();
	afx_msg void OnFormatRaw();
	afx_msg void OnFormatOptions();
	afx_msg void OnRestrictionStartTime();
	afx_msg void OnRestrictionStopTime();
	afx_msg void OnRestrictionStartFile();
	afx_msg void OnRestrictionStopSize();
	afx_msg void OnRestrictionStopDisk();
	afx_msg void OnFilteringRemoveItem();
	afx_msg void OnFilteringAllItems();
	afx_msg void OnExecutionTimeRange();
	afx_msg void OnAbort();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeSource();
	afx_msg void OnSpinchangeGapsInterval();
	afx_msg void OnSpinchangeUpdateInterval();
	afx_msg void OnSpinchangeRestrictionStartTime();
	afx_msg void OnSpinchangeRestrictionStopTime();
	afx_msg void OnSpinchangeRestrictionStopSize();
	afx_msg void OnSpinchangeExecutionStartTime();
	afx_msg void OnSpinchangeExecutionStopTime();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesToolsOptionsDialog dialog

#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_DETAILS   1001
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_ENCODING_STATIC   1002
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_ENCODING_ASCII   1003
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_ENCODING_BINARY   1004
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT   1005
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_RADIX_STATIC   1006
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_RADIX_HEXADECIMAL   1007
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_RADIX_DECIMAL   1008
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_RADIX_OCTAL   1009
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_RADIX_BINARY   1010
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_BLOCKS_STATIC   1011
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_BLOCKS_8BITS   1012
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_BLOCKS_16BITS   1013
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_BLOCKS_32BITS   1014
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_BLOCKS_64BITS   1015
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FORMAT_CHARSET_UNICODE   1016
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_SEPARATOR_STATIC   1017
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_SEPARATOR_NONE   1018
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_SEPARATOR_CR   1019
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_SEPARATOR_EOL   1020
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_SEPARATOR_CREOL   1021
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_USESEPARATEFILES   1022
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_USEFILEPREFIX   1023
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FILEPREFIX   1024
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_USEFILEEXTENSION   1025
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_FILEEXTENSION   1026
#define IDC_TELEMETRYARCHIVES_TOOLS_OPTIONS_HELP   1027

class CTelemetryArchivesToolsOptionsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryArchivesToolsOptionsDialog)

	// Construction
public:
	CTelemetryArchivesToolsOptionsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CHistoryFileExtractionProfileInfo  m_cProfileInfo[2];

	// Operations
private:
	VOID ShowFormatOptions();

	VOID AdjustToPrivileges();

	// Dialog Data
	//{{AFX_DATA(CTelemetryArchivesToolsOptionsDialog)
	enum { IDD = IDD_TELEMETRYARCHIVES_TOOLSPAGE_OPTIONS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesToolsOptionsDialog)
public:
	virtual INT DoModal(CHistoryFileExtractionProfileInfo *pProfileInfo);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelemetryArchivesToolsOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEncodingASCII();
	afx_msg void OnEncodingBinary();
	afx_msg void OnRadixHexadecimal();
	afx_msg void OnRadixDecimal();
	afx_msg void OnRadixOctal();
	afx_msg void OnRadixBinary();
	afx_msg void On8BitsBlock();
	afx_msg void On16BitsBlock();
	afx_msg void On32BitsBlock();
	afx_msg void On64BitsBlock();
	afx_msg void OnUnicode();
	afx_msg void OnNoSeparator();
	afx_msg void OnCRSeparator();
	afx_msg void OnEOLSeparator();
	afx_msg void OnCREOLSeparator();
	afx_msg void OnUseSeparateFiles();
	afx_msg void OnUseFilePrefix();
	afx_msg void OnUseFileExtension();
	afx_msg void OnEditchangeFilePrefix();
	afx_msg void OnEditchangeFileExtension();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesTabCtrl window

class CTelemetryArchivesTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTelemetryArchivesTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTelemetryArchivesDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelemetryArchivesTabCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryArchivesDialog

class CTelemetryArchivesDialog : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTelemetryArchivesDialog)

	// Construction
public:
	CTelemetryArchivesDialog(CWnd *pParentWnd = NULL);

	// Attributes
public:
	CTelemetryArchivesTabCtrl  m_wndTabCtrl;
	CTelemetryArchivesArchivalsPage  m_pageArchivals;
	CTelemetryArchivesRetrievalsPage  m_pageRetrievals;
	CTelemetryArchivesExtractionsPage  m_pageExtractions;
	CTelemetryArchivesBackupsPage  m_pageBackups;
	CTelemetryArchivesToolsPage  m_pageTools;

	// Operations
public:
	VOID SetArchiveFiles(CONST CHistoryStoreFiles &pFiles);
	VOID GetArchiveFiles(CHistoryStoreFiles &pFiles) CONST;
	VOID SetArchiveOptions(CONST CHistoryStoreOptions &pOptions);
	VOID GetArchiveOptions(CHistoryStoreOptions &pOptions) CONST;
	VOID EnumArchiveFilesToDelete(CStringArray &szFiles) CONST;
	VOID SetRetrieveFiles(CONST CHistoryStoreFiles &pFiles);
	VOID GetRetrieveFiles(CHistoryStoreFiles &pFiles) CONST;
	VOID SetDefaultRetrieveFile(CONST CHistoryStoreFile &cFile);
	VOID GetDefaultRetrieveFile(CHistoryStoreFile &cFile) CONST;
	VOID SetBrowseOptions(CONST CUIntArray &nOptions, CONST CStringArray &szDirectories);
	VOID GetBrowseOptions(CUIntArray &nOptions, CStringArray &szDirectories) CONST;
	VOID SetHistoryFileExtractionProfiles(CONST CArchivesExtractionProfiles &pProfiles);
	VOID SetHistoryFileExtractionProfiles(CONST CHistoryFileExtractionProfiles &pProfiles);
	VOID GetHistoryFileExtractionProfiles(CArchivesExtractionProfiles &pProfiles) CONST;
	VOID GetHistoryFileExtractionProfiles(CHistoryFileExtractionProfiles &pProfiles) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryArchivesDialog)
public:
	virtual BOOL Initialize();
public:
	virtual BOOL CheckPageAccessibility(INT nIndex) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelemetryArchivesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParameterSet

class CTelemetryParameterSet : public CTMParameters
{
	// Construction
public:
	CTelemetryParameterSet();
	~CTelemetryParameterSet();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbParameters;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;

	BOOL Copy(CONST CTelemetryParameterSet *pTMParameterSet);
	BOOL Compare(CONST CTelemetryParameterSet *pTMParameterSet) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParameterSets

class CTelemetryParameterSets : public CPtrArray
{
	// Construction
public:
	CTelemetryParameterSets();
	~CTelemetryParameterSets();

	// Attributes
public:

	// Operations
public:
	INT Add(CTelemetryParameterSet *pTMParameterSet);

	INT Find(LPCTSTR pszName) CONST;

	CTelemetryParameterSet *GetAt(INT nIndex) CONST;
	CTelemetryParameterSet *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTelemetryParameterSets *pTMParameterSets);
	BOOL Compare(CONST CTelemetryParameterSets *pTMParameterSets) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParametersCharacteristicsPage dialog

#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_TYPE_STATIC   1001
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_TYPE_RAW   1002
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_TYPE_NUMERICAL   1003
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_TYPE_STATUS   1004
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_SUBTTYPE_STATIC   1005
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_SUBTTYPE   1006
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_WIDTH_STATIC   1007
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_WIDTH   1008
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_WIDTH_BITS   1009
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_WIDTH_BIT   1010
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_UNITS_STATIC   1011
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_UNITS   1012
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_NATURE_STATIC   1013
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_NATURE_NORMAL   1014
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_NATURE_DERIVED   1015
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_NATURE_CONSTANT   1016
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_CODING_STATIC   1017
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_CODING_BITPATTERN   1018
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_CODING_SIGNEDINTEGER   1019
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_CODING_UNSIGNEDINTEGER   1020
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_CODING_COMPLEMENTCOMPLEX   1021
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_CODING_FLOATINGPOINT   1022
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_RADIX_STATIC   1023
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_RADIX_BINARY   1024
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_RADIX_OCTAL   1025
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_RADIX_DECIMAL   1026
#define IDC_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE_RADIX_HEXADECIMAL   1027

class CTelemetryParametersCharacteristicsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryParametersCharacteristicsPage)

	// Construction
public:
	CTelemetryParametersCharacteristicsPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTelemetryParametersCharacteristicsPage)
	enum { IDD = IDD_TELEMETRYPARAMETERS_CHARACTERISTICSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTMParameter *pDatabaseTMParameter);

	class CTelemetryParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryParametersCharacteristicsPage)
public:
	virtual BOOL HasParameterInfo() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryParametersCharacteristicsPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParametersCalibrationPage dialog

#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_TABLE_STATIC   1001
#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_TABLE   1002
#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_INTERPRETATION_STATIC   1007
#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_INTERPRETATION   1008
#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_STATUS_STATIC   1009
#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_STATUS   1010
#define IDC_TELEMETRYPARAMETERS_CALIBRATIONPAGE_POINTS   1011

class CTelemetryParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryParametersCalibrationPage)

	// Construction
public:
	CTelemetryParametersCalibrationPage();

	// Attributes
private:
	INT  m_nCalTableID;
	ULONGLONG  m_nCalTableType;
	CUIntArray  m_nCalTableRefs;
	CUIntArray  m_nCalValidityRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelemetryParametersCalibrationPage)
	enum { IDD = IDD_TELEMETRYPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTMParameter *pDatabaseTMParameter, CONST CTMParameter *pTMParameter);
	VOID ShowCalibrationInfo();

	class CTelemetryParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryParametersCalibrationPage)
public:
	virtual BOOL HasParameterInfo() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTable();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParametersLimitsPage dialog

#define IDC_TELEMETRYPARAMETERS_LIMITSPAGE_TABLE_STATIC   1001
#define IDC_TELEMETRYPARAMETERS_LIMITSPAGE_TABLE   1002
#define IDC_TELEMETRYPARAMETERS_LIMITSPAGE_ID_STATIC   1003
#define IDC_TELEMETRYPARAMETERS_LIMITSPAGE_ID   1004
#define IDC_TELEMETRYPARAMETERS_LIMITSPAGE_TYPE_STATIC   1005
#define IDC_TELEMETRYPARAMETERS_LIMITSPAGE_TYPE   1006
#define IDC_TELEMETRYPARAMETERS_LIMITSPAGE_STATUS_STATIC   1007
#define IDC_TELEMETRYPARAMETERS_LIMITSPAGE_STATUS   1008
#define IDC_TELEMETRYPARAMETERS_LIMITSPAGE_POINTS   1009

class CTelemetryParametersLimitsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryParametersLimitsPage)

	// Construction
public:
	CTelemetryParametersLimitsPage();

	// Attributes
private:
	INT  m_nOolTableID;
	WORD  m_wOolLimitID;
	ULONGLONG  m_nOolTableType;
	CUIntArray  m_nOolTableRefs;
	CUIntArray  m_nOolValidityRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelemetryParametersLimitsPage)
	enum { IDD = IDD_TELEMETRYPARAMETERS_LIMITSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTMParameter *pDatabaseTMParameter, CONST CTMParameter *pTMParameter);

	VOID ShowLimitsInfo();

	class CTelemetryParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryParametersLimitsPage)
public:
	virtual BOOL HasParameterInfo() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryParametersLimitsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTable();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParametersDerivationPage dialog

#define IDC_TELEMETRYPARAMETERS_DERIVATIONPAGE_CODE   1001

class CTelemetryParametersDerivationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryParametersDerivationPage)

	// Construction
public:
	CTelemetryParametersDerivationPage();

	// Attributes
private:
	CFont  m_cCodeFont;

	// Dialog Data
	//{{AFX_DATA(CTelemetryParametersDerivationPage)
	enum { IDD = IDD_TELEMETRYPARAMETERS_DERIVATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTMParameter *pDatabaseTMParameter);

	class CTelemetryParametersFolder *GetParent() CONST;

private:
	CString LoadParameterDerivationCode(CONST CDatabaseTMParameter *pDatabaseTMParameter) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryParametersDerivationPage)
public:
	virtual BOOL HasParameterInfo() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryParametersDerivationPage)
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParametersAllocationsPage dialog

#define IDC_TELEMETRYPARAMETERS_ALLOCATIONSPAGE_TYPE_STATIC   1001
#define IDC_TELEMETRYPARAMETERS_ALLOCATIONSPAGE_TYPE   1002
#define IDC_TELEMETRYPARAMETERS_ALLOCATIONSPAGE_COMMENT   1003
#define IDC_TELEMETRYPARAMETERS_ALLOCATIONSPAGE_LOCATIONS   1004

class CTelemetryParametersAllocationsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelemetryParametersAllocationsPage)

	// Construction
public:
	CTelemetryParametersAllocationsPage();

	// Attributes
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelemetryParametersAllocationsPage)
	enum { IDD = IDD_TELEMETRYPARAMETERS_ALLOCATIONSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTMParameter *pDatabaseTMParameter);

	class CTelemetryParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryParametersAllocationsPage)
public:
	virtual BOOL HasParameterInfo() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelemetryParametersAllocationsPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParametersFolderTabCtrl window

class CTelemetryParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTelemetryParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTelemetryParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelemetryParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParametersFolder

class CTelemetryParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTelemetryParametersFolder)

	// Construction
public:
	CTelemetryParametersFolder();

	// Attributes
private:
	CTelemetryParametersCharacteristicsPage  m_pageCharacteristics;
	CTelemetryParametersCalibrationPage  m_pageCalibration;
	CTelemetryParametersLimitsPage  m_pageLimits;
	CTelemetryParametersDerivationPage  m_pageDerivation;
	CTelemetryParametersAllocationsPage  m_pageAllocations;
	CTelemetryParametersFolderTabCtrl  m_wndTabCtrl;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTMParameter *pDatabaseTMParameter);

	class CTelemetryParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryParametersFolder)
public:
	virtual BOOL CheckPageAccessibility(INT nIndex) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelemetryParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParametersDialog dialog

#define IDC_TELEMETRYPARAMETERS_DETAILS   1001
#define IDC_TELEMETRYPARAMETERS_NAME_STATIC   1002
#define IDC_TELEMETRYPARAMETERS_NAME   1003
#define IDC_TELEMETRYPARAMETERS_RESETALL   1004
#define IDC_TELEMETRYPARAMETERS_FOLDER   1005
#define IDC_TELEMETRYPARAMETERS_SETS   1006
#define IDC_TELEMETRYPARAMETERS_SETS_MEMBERS   1007
#define IDC_TELEMETRYPARAMETERS_SETS_MEMBER_COMMENT   1008
#define IDC_TELEMETRYPARAMETERS_SETS_MEMBER_ADD   1009
#define IDC_TELEMETRYPARAMETERS_SETS_MEMBER_REMOVE   1010
#define IDC_TELEMETRYPARAMETERS_SETS_MEMBER_REMOVEALL   1011
#define IDC_TELEMETRYPARAMETERS_SETS_MEMBER_VALUE_STATIC   1012
#define IDC_TELEMETRYPARAMETERS_SETS_MEMBER_VALUE   1013
#define IDC_TELEMETRYPARAMETERS_SETS_MEMBER_VALUEINTERPRETATION_STATIC   1014
#define IDC_TELEMETRYPARAMETERS_SETS_MEMBER_VALUEINTERPRETATION   1015
#define IDC_TELEMETRYPARAMETERS_SETS_MEMBER_VALUE_SET   1016
#define IDC_TELEMETRYPARAMETERS_SETS_NAME_STATIC   1017
#define IDC_TELEMETRYPARAMETERS_SETS_NAME   1018
#define IDC_TELEMETRYPARAMETERS_SETS_SAVE   1019
#define IDC_TELEMETRYPARAMETERS_SETS_DELETE   1020
#define IDC_TELEMETRYPARAMETERS_SETS_IMPORT   1021
#define IDC_TELEMETRYPARAMETERS_SETS_EXPORT   1022
#define IDC_TELEMETRYPARAMETERS_HELP   1023

class CTelemetryParametersDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryParametersDialog)

	// Construction
public:
	CTelemetryParametersDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryParameterSet  m_cTMParameterSet;
	CTelemetryParameterSets  m_pTMParameterSets[2];
	CDatabaseTMParameter  m_cDatabaseTMParameter;
private:
	CTelemetryParametersFolder  m_wndFolderCtrl;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelemetryParametersDialog)
	enum { IDD = IDD_TELEMETRYPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumParameters();
	BOOL EnumParameterSets();
	BOOL EnumParameterValues();

	VOID ShowParameterSetMembers();
	VOID ShowParameterInfo();

	CDatabaseTMParameter *FindParameter() CONST;

	UINT CheckTMParameterOolStatus(CONST CTMParameter *pTMParameter) CONST;
	UINT CheckTMParameterOolStatus(CONST CTMParameter *pTMParameter, LPCTSTR pszTable, ULONGLONG nValue) CONST;
	UINT CheckTMParameterValidity(CONST CTMParameter *pTMParameter) CONST;
	CString CheckTMParameterCalTable(CONST CTMParameter *pTMParameter) CONST;
	CString CheckTMParameterOolTable(CONST CTMParameter *pTMParameter) CONST;
	INT FindTMParameterCalTable(CONST CDatabaseTMParameter *pDatabaseTMParameter) CONST;
	INT FindTMParameterOolTable(CONST CDatabaseTMParameter *pDatabaseTMParameter) CONST;

	CRect CalcFolderSize() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryParametersDialog)
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
	//{{AFX_MSG(CTelemetryParametersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddSetMember();
	afx_msg void OnRemoveSetMember();
	afx_msg void OnRemoveAllSetMembers();
	afx_msg void OnSetMemberValueInitialization();
	afx_msg void OnSaveSet();
	afx_msg void OnDeleteSet();
	afx_msg void OnImportSets();
	afx_msg void OnExportSets();
	afx_msg void OnResetAllParameters();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeSetMemberValue();
	afx_msg void OnSelchangeSetMemberValueInterpretation();
	afx_msg void OnSelchangeSetName();
	afx_msg void OnEditchangeSetMemberValue();
	afx_msg void OnEditchangeSetName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParametersImportSetsDialog dialog

#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_DETAILS   1001
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_FILENAME_STATIC   1002
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_FILENAME   1003
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_FILENAME_BROWSE   1004
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_FILENAME_INSPECT   1005
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_COMMENT   1006
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_LIST_STATIC   1007
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_LIST   1008
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_LIST_REMOVE   1009
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_LIST_REMOVEALL   1010
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_PROPERTIES   1011
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_PROPERTIES_MEMBERS   1012
#define IDC_TELEMETRYPARAMETERS_IMPORTSETS_HELP   1013

class CTelemetryParametersImportSetsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryParametersImportSetsDialog)

	// Construction
public:
	CTelemetryParametersImportSetsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryParameterSets  m_pSets[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelemetryParametersImportSetsDialog)
	enum { IDD = IDD_TELEMETRYPARAMETERS_IMPORTSETS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumParameterSets();

	VOID ShowParameterSetMembers();
	VOID ExamineParameterSets();

	CTelemetryParameterSet *FindParameterSet() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryParametersImportSetsDialog)
public:
	virtual INT DoModal(CTelemetryParameterSets &pSets);
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelemetryParametersImportSetsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnFilenameBrowse();
	afx_msg void OnInspectParameterSet();
	afx_msg void OnRemoveParameterSet();
	afx_msg void OnRemoveAllParameterSets();
	afx_msg void OnSelchangeParameterSet();
	afx_msg void OnEditchangeFilename();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelemetryParametersExportSetsDialog dialog

#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_DETAILS   1001
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_NAME_STATIC   1002
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_NAME   1003
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_PROPERTIES   1004
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_PROPERTIES_MEMBERS   1005
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_LIST_STATIC   1006
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_LIST   1007
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_LIST_ADD   1008
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_LIST_REMOVE   1009
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_LIST_REMOVEALL  1010
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_FILENAME_STATIC   1011
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_FILENAME   1012
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_FILENAME_BROWSE   1013
#define IDC_TELEMETRYPARAMETERS_EXPORTSETS_HELP   1014

class CTelemetryParametersExportSetsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelemetryParametersExportSetsDialog)

	// Construction
public:
	CTelemetryParametersExportSetsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelemetryParameterSets  m_pSets;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelemetryParametersExportSetsDialog)
	enum { IDD = IDD_TELEMETRYPARAMETERS_EXPORTSETS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumParameterSets();

	VOID ShowParameterSetMembers();

	CTelemetryParameterSet *FindParameterSet() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelemetryParametersExportSetsDialog)
public:
	virtual INT DoModal(CONST CTelemetryParameterSets &pSets);
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelemetryParametersExportSetsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddParameterSet();
	afx_msg void OnRemoveParameterSet();
	afx_msg void OnRemoveAllParameterSets();
	afx_msg void OnFilenameBrowse();
	afx_msg void OnSelchangeParameterSet();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsArchivingPage dialog

#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_FILENAME_STATIC   1001
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_FILENAME   1002
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_FORMATS   1003
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_FORMATS_NORMAL   1004
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_FORMATS_DESCRIPTIVE   1005
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_FORMATS_DELIMITED   1006
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_FORMATS_EXTENSIONS   1007
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_FORMATS_NORMAL_EXTENSION   1008
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_FORMATS_DESCRIPTIVE_EXTENSION   1009
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_FORMATS_DELIMITED_EXTENSION   1010
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_RETENTIONS   1011
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_RETENTIONS_STATUS   1012
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_RETENTIONS_STOPBYCOUNT   1013
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_RETENTIONS_STOPCOUNT   1014
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_RETENTIONS_STOPBYCOUNT_STATIC   1015
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_RETENTIONS_STOPBYTIME   1016
#define IDC_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE_RETENTIONS_STOPTIME   1017

// Specify the memory dumps archiving page related settings
#define MEMORYDUMPSSERVICE_ARCHIVING_MINIMUMDUMPS   1
#define MEMORYDUMPSSERVICE_ARCHIVING_MAXIMUMDUMPS   999
#define MEMORYDUMPSSERVICE_ARCHIVING_DEFAULTDUMPS   10
#define MEMORYDUMPSSERVICE_ARCHIVING_DEFAULTINTERVAL   SECONDSPERDAY

class CMemoryDumpsArchivingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMemoryDumpsArchivingPage)

	// Construction
public:
	CMemoryDumpsArchivingPage();

	// Attributes
private:
	CMemoryDump  m_cDump[2];

	// Dialog Data
	//{{AFX_DATA(CMemoryDumpsArchivingPage)
	enum { IDD = IDD_MEMORYDUMPS_SERVICE_ARCHIVINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CMemoryDump *pDump, CONST CMemoryDump *pBackupDump = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CMemoryDump *pDump) CONST;

	class CMemoryDumpsFolder *GetParent() CONST;

private:
	VOID ShowArchivingInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMemoryDumpsArchivingPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMemoryDumpsArchivingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnFileFormatNormal();
	afx_msg void OnFileFormatDescriptive();
	afx_msg void OnFileFormatDelimited();
	afx_msg void OnRetentionStatus();
	afx_msg void OnRetentionStopByCount();
	afx_msg void OnRetentionStopByTime();
	afx_msg void OnSpinchangeRetentionCount();
	afx_msg void OnSpinchangeRetentionTime();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeFileExtensionNormal();
	afx_msg void OnEditchangeFileExtensionDescriptive();
	afx_msg void OnEditchangeFileExtensionDelimited();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsNotificationsPage dialog

#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_LOCATION_STATIC   1001
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_LOCATION   1002
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_USERNAME_STATIC   1003
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_USERNAME   1004
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_PASSWORD_STATIC   1005
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_PASSWORD   1006
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_PORT   1007
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_PORTNUMBER   1008
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_FORMATS   1009
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_FORMATS_NORMAL   1010
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_FORMATS_DESCRIPTIVE   1011
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_FORMATS_DELIMITED   1012
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_RETENTIONS   1013
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_RETENTIONS_STATUS   1014
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_RETENTIONS_STOPBYCOUNT   1015
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_RETENTIONS_STOPCOUNT   1016
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_RETENTIONS_STOPBYCOUNT_STATIC   1017
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_RETENTIONS_STOPBYTIME   1018
#define IDC_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE_RETENTIONS_STOPTIME   1019

// Specify the memory dumps notifications page related settings
#define MEMORYDUMPSSERVICE_NOTIFICATIONS_FIRSTPORT   1024
#define MEMORYDUMPSSERVICE_NOTIFICATIONS_LASTPORT   65535
#define MEMORYDUMPSSERVICE_NOTIFICATIONS_DEFAULTPORT   1024
#define MEMORYDUMPSSERVICE_NOTIFICATIONS_MINIMUMDUMPS   1
#define MEMORYDUMPSSERVICE_NOTIFICATIONS_MAXIMUMDUMPS   999
#define MEMORYDUMPSSERVICE_NOTIFICATIONS_DEFAULTDUMPS   10
#define MEMORYDUMPSSERVICE_NOTIFICATIONS_DEFAULTINTERVAL   SECONDSPERDAY

class CMemoryDumpsNotificationsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMemoryDumpsNotificationsPage)

	// Construction
public:
	CMemoryDumpsNotificationsPage();

	// Attributes
private:
	CMemoryDump  m_cDump[2];

	// Dialog Data
	//{{AFX_DATA(CMemoryDumpsNotificationsPage)
	enum { IDD = IDD_MEMORYDUMPS_SERVICE_NOTIFICATIONSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CMemoryDump *pDump, CONST CMemoryDump *pBackupDump = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CMemoryDump *pDump) CONST;

	class CMemoryDumpsFolder *GetParent() CONST;

private:
	VOID ShowNotificationsInfo();

	BOOL ParseURL(LPCTSTR pszLocation, CString &szServer, CString &szDirectory, UINT &nPort) CONST;
	CString ConstructURL(LPCTSTR pszServer, LPCTSTR pszDirectory) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMemoryDumpsNotificationsPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMemoryDumpsNotificationsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnFileFormatNormal();
	afx_msg void OnFileFormatDescriptive();
	afx_msg void OnFileFormatDelimited();
	afx_msg void OnPort();
	afx_msg void OnRetentionStatus();
	afx_msg void OnRetentionStopByCount();
	afx_msg void OnRetentionStopByTime();
	afx_msg void OnSpinchangeRetentionCount();
	afx_msg void OnSpinchangeRetentionTime();
	afx_msg void OnEditchangeLocation();
	afx_msg void OnEditchangeUserName();
	afx_msg void OnEditchangePassword();
	afx_msg void OnSpinchangePort();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsFTPTransfersPage dialog

#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_BEHAVIOR   1001
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_BEHAVIOR_STATIC   1002
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_RETRY_NEVER   1003
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_RETRY_CONTINOUSLY   1004
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_RETRY_LIMITED   1005
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_RETRY_LIMITED_STATIC   1006
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_RETRY_LIMITED_COUNT   1007
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_RETRY_INTERVAL_STATIC   1008
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_RETRY_INTERVAL_PERIOD   1009
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_RETRY_INTERVAL_PERIOD_STATIC   1010
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_RESETQUEUE   1011
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_SAVEONEXIT   1012
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_AUDITION   1013
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_AUDITION_STATIC   1014
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_AUDITION_NONE   1015
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_AUDITION_ALL   1016
#define IDC_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE_AUDITION_FAILURES   1017

// Specify the memory dumps ftp transfers page related settings
#define MEMORYDUMPSSERVICE_FTPTRANSFERS_MINIMUMRETRIES   1
#define MEMORYDUMPSSERVICE_FTPTRANSFERS_MAXIMUMRETRIES   100
#define MEMORYDUMPSSERVICE_FTPTRANSFERS_DEFAULTRETRIES   5
#define MEMORYDUMPSSERVICE_FTPTRANSFERS_MINIMUMRETRYINTERVAL   1
#define MEMORYDUMPSSERVICE_FTPTRANSFERS_MAXIMUMRETRYINTERVAL   MINUTESPERWEEK
#define MEMORYDUMPSSERVICE_FTPTRANSFERS_DEFAULTRETRYINTERVAL   5

class CMemoryDumpsFTPTransfersPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CMemoryDumpsFTPTransfersPage)

	// Construction
public:
	CMemoryDumpsFTPTransfersPage();

	// Attributes
private:
	CMemoryDump  m_cDump[2];

	// Dialog Data
	//{{AFX_DATA(CMemoryDumpsFTPTransfersPage)
	enum { IDD = IDD_MEMORYDUMPS_SERVICE_FTPTRANSFERSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CMemoryDump *pDump, CONST CMemoryDump *pBackupDump = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CMemoryDump *pDump) CONST;

	BOOL EmptyDumpsQueue() CONST;

	class CMemoryDumpsFolder *GetParent() CONST;

private:
	VOID ShowFTPTransfersInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMemoryDumpsFTPTransfersPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMemoryDumpsFTPTransfersPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnRetryNone();
	afx_msg void OnRetryContinously();
	afx_msg void OnRetryLimited();
	afx_msg void OnResetQueue();
	afx_msg void OnSaveOnExit();
	afx_msg void OnAuditionNone();
	afx_msg void OnAuditionAll();
	afx_msg void OnAuditionFailures();
	afx_msg void OnSpinchangeRetries();
	afx_msg void OnSpinchangeRetryInterval();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsFolderTabCtrl window

class CMemoryDumpsFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CMemoryDumpsFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CMemoryDumpsFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryDumpsFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMemoryDumpsFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsFolder

class CMemoryDumpsFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CMemoryDumpsFolder)

	// Construction
public:
	CMemoryDumpsFolder();

	// Attributes
private:
	CMemoryDumpsFolderTabCtrl  m_wndTabCtrl;
	CMemoryDumpsArchivingPage  m_pageArchiving;
	CMemoryDumpsNotificationsPage  m_pageNotifications;
	CMemoryDumpsFTPTransfersPage  m_pageFTPTransfers;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID SetInfo(CONST CMemoryDump *pDump, BOOL bUpdate = TRUE);
	VOID SetInfo(CONST CMemoryDump *pDump, CONST CMemoryDump *pBackupDump);
	VOID GetInfo(CMemoryDump *pDump) CONST;

	BOOL EmptyDumpsQueue() CONST;

	class CMemoryDumpsServiceDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryDumpsFolder)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	virtual BOOL Check(BOOL bModified, BOOL bChecked) CONST;
protected:
	virtual VOID RepositionButtons();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMemoryDumpsFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsServiceDialog dialog

#define IDC_MEMORYDUMPS_SERVICE_DETAILS   1001
#define IDC_MEMORYDUMPS_SERVICE_STATUS_STATIC   1002
#define IDC_MEMORYDUMPS_SERVICE_STATUS   1003
#define IDC_MEMORYDUMPS_SERVICE_CHARSET   1004
#define IDC_MEMORYDUMPS_SERVICE_CHARSET_ASCII   1005
#define IDC_MEMORYDUMPS_SERVICE_CHARSET_UNICODE   1006
#define IDC_MEMORYDUMPS_SERVICE_AVAILABILITY   1007
#define IDC_MEMORYDUMPS_SERVICE_AVAILABILITY_UNLIMITED   1008
#define IDC_MEMORYDUMPS_SERVICE_AVAILABILITY_DAILY   1009
#define IDC_MEMORYDUMPS_SERVICE_AVAILABILITY_STARTTIME   1010
#define IDC_MEMORYDUMPS_SERVICE_AVAILABILITY_DAILY_STATIC   1011
#define IDC_MEMORYDUMPS_SERVICE_AVAILABILITY_STOPTIME   1012
#define IDC_MEMORYDUMPS_SERVICE_AVAILABILITY_WORKINGDAYS   1013
#define IDC_MEMORYDUMPS_SERVICE_AVAILABILITY_AUDIT   1014
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES   1015
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_NAME_STATIC   1016
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_NAME   1017
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_SOURCE_STATIC   1018
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_SOURCE   1019
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_ADDRESS_STATIC   1020
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_REGISTER_STATIC   1021
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_LOWADDRESS   1022
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_ADDRESS_TO_STATIC   1023
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_ADDRESS_COMMENTS   1024
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_HIGHADDRESS   1025
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_AUDIT   1026
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_FORMATTYPE_STATIC   1027
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_FORMATTYPE   1028
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_ADD   1029
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_MODIFY   1030
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_REMOVE   1031
#define IDC_MEMORYDUMPS_SERVICE_PROPERTIES_FOLDER   1032
#define IDC_MEMORYDUMPS_SERVICE_HELP   1033

// Specify the memory dumps service dialog related settings
#define MEMORYDUMPSSERVICE_DEFAULTSTARTTIME   HOURS(8)
#define MEMORYDUMPSSERVICE_DEFAULTSTOPTIME   HOURS(17)

class CMemoryDumpsServiceDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CMemoryDumpsServiceDialog)

	// Construction
public:
	CMemoryDumpsServiceDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	UINT  m_nCode;
	UINT  m_nCharset;
	CTimeSpan  m_tStartTime;
	CTimeSpan  m_tStopTime;
	CMemoryDumps  m_pDumps[3];
private:
	CMemoryDumpsFolder  *m_pwndFolderCtrl;
private:
	UINT  m_nLocked;

	// Dialog Data
	//{{AFX_DATA(CMemoryDumpsServiceDialog)
	enum { IDD = IDD_MEMORYDUMPS_SERVICE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetDumps(CONST CMemoryDumps &pDumps);
	BOOL GetDumps(CMemoryDumps &pDumps) CONST;

private:
	BOOL EnumDumps();
	BOOL EnumDumpSources();
	BOOL EnumDumpFormatTypes();

	VOID ShowServiceInfo();

	VOID SetDumpInfo(BOOL bInitialize = FALSE);
	VOID UpdateDumpInfo(CONST CMemoryDump *pDump, BOOL bInitialize);
	BOOL GetDumpInfo(CMemoryDump *pDump) CONST;
	CMemoryDump *FindDumpInfo() CONST;

	BOOL TranslateDumpAddressRange(LPCTSTR pszStartAddress, LPCTSTR pszEndAddress, UINT &nStartPage, UINT &nStartAddress, UINT &nEndPage, UINT &nEndAddress) CONST;
	BOOL TranslateDumpAddressRange(UINT nStartPage, UINT nStartAddress, UINT nEndPage, UINT nEndAddress, CString &szStartAddress, CString &szEndAddress) CONST;

	BOOL EmptyDumpsQueue() CONST;

	CRect CalcFolderSize() CONST;

	VOID AdjustToPrivileges();

	VOID Lock();
	BOOL IsLocked() CONST;
	VOID Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryDumpsServiceDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	virtual BOOL Check(BOOL bModified, BOOL bChecked) CONST;
	virtual VOID Update(BOOL bModified, BOOL bChecked) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMemoryDumpsServiceDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnServiceStatus();
	afx_msg void OnCharsetASCII();
	afx_msg void OnCharsetUnicode();
	afx_msg void OnUnlimitedAvailability();
	afx_msg void OnDailyAvailability();
	afx_msg void OnWorkingDaysAvailability();
	afx_msg void OnAuditAvailability();
	afx_msg void OnMemoryDumpAudit();
	afx_msg void OnAddMemoryDump();
	afx_msg void OnModifyMemoryDump();
	afx_msg void OnRemoveMemoryDump();
	afx_msg void OnSpinchangeDailyStartTime();
	afx_msg void OnSpinchangeDailyStopTime();
	afx_msg void OnEditchangeMemoryName();
	afx_msg void OnEditchangeLowAddress();
	afx_msg void OnEditchangeHighAddress();
	afx_msg void OnEditupdateLowAddress();
	afx_msg void OnEditupdateHighAddress();
	afx_msg void OnSelchangeMemoryName();
	afx_msg void OnSelchangeMemorySource();
	afx_msg void OnSelchangeMemoryFormatType();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMemoryDumpsImportDialog dialog

#define IDC_MEMORYDUMPS_IMPORT_DETAILS   1001
#define IDC_MEMORYDUMPS_IMPORT_FILENAME_STATIC   1002
#define IDC_MEMORYDUMPS_IMPORT_FILENAME   1003
#define IDC_MEMORYDUMPS_IMPORT_BROWSE   1004
#define IDC_MEMORYDUMPS_IMPORT_INSPECT   1005
#define IDC_MEMORYDUMPS_IMPORT_DIRECTORY_STATIC   1006
#define IDC_MEMORYDUMPS_IMPORT_DIRECTORY   1007
#define IDC_MEMORYDUMPS_IMPORT_ADD   1008
#define IDC_MEMORYDUMPS_IMPORT_ADDALL   1009
#define IDC_MEMORYDUMPS_IMPORT_ATTENTION   1010
#define IDC_MEMORYDUMPS_IMPORT_ATTENTION_TEXT   1011
#define IDC_MEMORYDUMPS_IMPORT_LIST_STATIC   1012
#define IDC_MEMORYDUMPS_IMPORT_LIST   1013
#define IDC_MEMORYDUMPS_IMPORT_REMOVE   1014
#define IDC_MEMORYDUMPS_IMPORT_REMOVEALL   1015
#define IDC_MEMORYDUMPS_IMPORT_HELP   1016

class CMemoryDumpsImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CMemoryDumpsImportDialog)

	// Construction
public:
	CMemoryDumpsImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CMemoryDumps  m_pDumps[3];

	// Operations
private:
	VOID EnumDumps();

	// Dialog Data
	//{{AFX_DATA(CMemoryDumpsImportDialog)
	enum { IDD = IDD_MEMORYDUMPS_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryDumpsImportDialog)
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
	//{{AFX_MSG(CMemoryDumpsImportDialog)
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
// CMemoryDumpsExportDialog dialog

#define IDC_MEMORYDUMPS_EXPORT_DETAILS   1001
#define IDC_MEMORYDUMPS_EXPORT_DIRECTORY_STATIC   1002
#define IDC_MEMORYDUMPS_EXPORT_DIRECTORY   1003
#define IDC_MEMORYDUMPS_EXPORT_ADD   1004
#define IDC_MEMORYDUMPS_EXPORT_ADDALL   1005
#define IDC_MEMORYDUMPS_EXPORT_LIST_STATIC   1006
#define IDC_MEMORYDUMPS_EXPORT_LIST   1007
#define IDC_MEMORYDUMPS_EXPORT_REMOVE   1008
#define IDC_MEMORYDUMPS_EXPORT_REMOVEALL   1009
#define IDC_MEMORYDUMPS_EXPORT_FILENAME_STATIC   1010
#define IDC_MEMORYDUMPS_EXPORT_FILENAME   1011
#define IDC_MEMORYDUMPS_EXPORT_BROWSE   1012
#define IDC_MEMORYDUMPS_EXPORT_HELP   1013

class CMemoryDumpsExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CMemoryDumpsExportDialog)

	// Construction
public:
	CMemoryDumpsExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CMemoryDumps  m_pDumps[2];

	// Operations
private:
	BOOL EnumDumps();

	// Dialog Data
	//{{AFX_DATA(CMemoryDumpsExportDialog)
	enum { IDD = IDD_MEMORYDUMPS_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemoryDumpsExportDialog)
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
	//{{AFX_MSG(CMemoryDumpsExportDialog)
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
// CTelecommandServiceDialog dialog

#define IDC_TELECOMMANDSERVICE_DETAILS   1001
#define IDC_TELECOMMANDSERVICE_PRODUCT_STATIC   1002
#define IDC_TELECOMMANDSERVICE_PRODUCT   1003
#define IDC_TELECOMMANDSERVICE_DEVICE_STATIC   1004
#define IDC_TELECOMMANDSERVICE_DEVICE   1005
#define IDC_TELECOMMANDSERVICE_DEVICE_CHANGE   1006
#define IDC_TELECOMMANDSERVICE_DEVICE_ADD   1007
#define IDC_TELECOMMANDSERVICE_DEVICE_REMOVE   1008
#define IDC_TELECOMMANDSERVICE_SCHEDULE   1009
#define IDC_TELECOMMANDSERVICE_SCHEDULE_USE   1010
#define IDC_TELECOMMANDSERVICE_SCHEDULE_ALWAYS   1011
#define IDC_TELECOMMANDSERVICE_SCHEDULE_DAILY   1012
#define IDC_TELECOMMANDSERVICE_SCHEDULE_DAILY_STARTTIME   1013
#define IDC_TELECOMMANDSERVICE_SCHEDULE_DAILY_STATIC   1014
#define IDC_TELECOMMANDSERVICE_SCHEDULE_DAILY_STOPTIME   1015
#define IDC_TELECOMMANDSERVICE_SCHEDULE_INTERVAL   1016
#define IDC_TELECOMMANDSERVICE_SCHEDULE_INTERVAL_STARTTIME   1017
#define IDC_TELECOMMANDSERVICE_SCHEDULE_INTERVAL_STATIC   1018
#define IDC_TELECOMMANDSERVICE_SCHEDULE_INTERVAL_STOPTIME   1019
#define IDC_TELECOMMANDSERVICE_SCHEDULE_PERIODIC   1020
#define IDC_TELECOMMANDSERVICE_SCHEDULE_PERIODIC_TIME   1021
#define IDC_TELECOMMANDSERVICE_SCHEDULE_PERIODIC_STATIC   1022
#define IDC_TELECOMMANDSERVICE_SCHEDULE_PERIODIC_TIMESPAN   1023
#define IDC_TELECOMMANDSERVICE_SCHEDULE_PERIODIC_TIMESPAN_STATIC   1024
#define IDC_TELECOMMANDSERVICE_SCHEDULE_PERIODIC_INTERVAL_STATIC   1025
#define IDC_TELECOMMANDSERVICE_SCHEDULE_PERIODIC_INTERVAL   1026
#define IDC_TELECOMMANDSERVICE_SCHEDULE_PERIODIC_INTERVAL_SECONDS   1027
#define IDC_TELECOMMANDSERVICE_SCHEDULE_DISABLED   1028
#define IDC_TELECOMMANDSERVICE_SCHEDULE_AUDIT   1029
#define IDC_TELECOMMANDSERVICE_BACKUP   1030
#define IDC_TELECOMMANDSERVICE_BACKUP_RETRY   1031
#define IDC_TELECOMMANDSERVICE_BACKUP_RETRY_CONTINOUSLY   1032
#define IDC_TELECOMMANDSERVICE_BACKUP_RETRY_COUNT   1033
#define IDC_TELECOMMANDSERVICE_BACKUP_RETRY_COUNT_STATIC   1034
#define IDC_TELECOMMANDSERVICE_BACKUP_RETRY_COUNT_NUMBER   1035
#define IDC_TELECOMMANDSERVICE_BACKUP_RETRY_DEVICE   1036
#define IDC_TELECOMMANDSERVICE_BACKUP_RETRY_DEVICE_NAME   1037
#define IDC_TELECOMMANDSERVICE_BACKUP_RETRY_ANYDEVICE   1038
#define IDC_TELECOMMANDSERVICE_BACKUP_TIMEOUT   1039
#define IDC_TELECOMMANDSERVICE_BACKUP_TIMEOUT_PERIOD   1040
#define IDC_TELECOMMANDSERVICE_BACKUP_TIMEOUT_STATIC   1041
#define IDC_TELECOMMANDSERVICE_BACKUP_AUDITFAILURES   1042
#define IDC_TELECOMMANDSERVICE_HELP   1043

// Specify the telecommand service dialog related settings
#define TELECOMMANDSERVICE_MINIMUMINTERVAL   SECONDSPERMINUTE
#define TELECOMMANDSERVICE_MAXIMUMINTERVAL   (365*SECONDSPERDAY)
#define TELECOMMANDSERVICE_DEFAULTINTERVAL   SECONDSPERHOUR
#define TELECOMMANDSERVICE_MINIMUMTIMESPAN   SECONDSPERMINUTE
#define TELECOMMANDSERVICE_MAXIMUMTIMESPAN   SECONDSPERWEEK
#define TELECOMMANDSERVICE_DEFAULTTIMESPAN   (SECONDSPERHOUR/2)
#define TELECOMMANDSERVICE_MINIMUMTIMEOUT   (SECONDSPERMINUTE/4)
#define TELECOMMANDSERVICE_MAXIMUMTIMEOUT   SECONDSPERDAY
#define TELECOMMANDSERVICE_DEFAULTTIMEOUT   SECONDSPERMINUTE
#define TELECOMMANDSERVICE_MINIMUMRETRIES   1
#define TELECOMMANDSERVICE_MAXIMUMRETRIES   100
#define TELECOMMANDSERVICE_DEFAULTRETRIES   5
#define TELECOMMANDSERVICE_DAILYSTARTTIME   HOURS(8)
#define TELECOMMANDSERVICE_DAILYSTOPTIME   HOURS(17)
#define TELECOMMANDSERVICE_INTERVALTIME   SECONDSPERHOUR

class CTelecommandServiceDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandServiceDialog)

	// Construction
public:
	CTelecommandServiceDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTCUplinkDevices  m_pDevices[2];

	// Dialog Data
	//{{AFX_DATA(CTelecommandServiceDialog)
	enum { IDD = IDD_TELECOMMANDSERVICE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumProducts();
	BOOL EnumProductDevices();
	VOID EnumBackupDevices();

	VOID ShowDeviceDetails();
	VOID ShowDeviceDetails(CONST CTCUplinkDevice *pDevice);

	CTCUplinkDevice *FindDevice() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandServiceDialog)
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
	//{{AFX_MSG(CTelecommandServiceDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddDevice();
	afx_msg void OnChangeDevice();
	afx_msg void OnRemoveDevice();
	afx_msg void OnScheduleAlways();
	afx_msg void OnScheduleDaily();
	afx_msg void OnScheduleInterval();
	afx_msg void OnSchedulePeriodic();
	afx_msg void OnScheduleDisabled();
	afx_msg void OnScheduleAudit();
	afx_msg void OnBackupContinously();
	afx_msg void OnBackupRetries();
	afx_msg void OnBackupUseDevice();
	afx_msg void OnBackupUseAnyDevice();
	afx_msg void OnBackupTimeout();
	afx_msg void OnBackupAudit();
	afx_msg void OnSelchangeProduct();
	afx_msg void OnSelchangeDevice();
	afx_msg void OnSelchangeDeviceName();
	afx_msg void OnSpinchangeDailyStartTime();
	afx_msg void OnSpinchangeDailyStopTime();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	afx_msg void OnSpinchangePeriodicTime();
	afx_msg void OnSpinchangePeriodicTimeSpan();
	afx_msg void OnSpinchangePeriodicInterval();
	afx_msg void OnSpinchangeBackupRetryCount();
	afx_msg void OnSpinchangeBackupTimeout();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsConfigurationPage dialog

#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_COMMANDHANDLER_STATIC   1002
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_COMMANDHANDLER_PRIMARY   1003
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_COMMANDHANDLER_PRIMARY_NAME   1004
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_COMMANDHANDLER_SECONDARY   1005
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_COMMANDHANDLER_SECONDARY_NAME   1006
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_COMMANDHANDLER_ALLOWSELF   1007
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_COMMANDHANDLER_USEANY   1008
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_COMMANDHANDLER_ENSUREUNIQUE   1009
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_COMMANDHANDLER_ALWAYSALLOWEXIT   1010
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_COMMANDHANDLER_MORE   1011
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALMODES_STATIC   1012
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALMODES_MASTERMANUALMODE   1013
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALMODES_MASTERMANUALMODE_OWNER   1014
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALMODES_RELEASEWAITMODE   1015
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALMODES_AUTOMATICREJECTIONMODE   1016
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALSTATE_DISABLERELEASE   1017
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_STATIC   1018
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_OVERRIDEPTV   1019
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_DISABLEPTV   1020
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_OVERRIDEPEV   1021
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_DISABLEPEV   1022
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_OVERRIDECEV   1023
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_DISABLECEV   1024
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_VERIFICATIONUNCERTAINTYTIMEWINDOW_STATIC   1025
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_VERIFICATIONUNCERTAINTYTIMEWINDOW_INTERVAL   1026
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_VERIFICATIONUNCERTAINTYTIMEWINDOW_INTERVAL_STATIC   1027
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_GLOBALCHECKS_INTERLOCKS   1028
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_STATIC   1029
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_MAXIMUMEXECUTIONTIMEPERIOD_STATIC   1030
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_MAXIMUMEXECUTIONTIMEPERIOD_INTERVAL   1031
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_MAXIMUMEXECUTIONTIMEPERIOD_INTERVAL_STATIC   1032
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_MAXIMUMTIMECHECKPERIOD_STATIC   1033
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_MAXIMUMTIMECHECKPERIOD_INTERVAL   1034
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_MAXIMUMTIMECHECKPERIOD_INTERVAL_STATIC   1035
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_STATIC   1036
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_INTERVAL   1037
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_INTERVAL_STATIC   1038
#define IDC_TELECOMMANDOPTIONS_CONFIGURATIONPAGE_MISCELLANEOUS_SHOWCLCWPANEL   1039

// Specify the telecommand options configuration page related settings
#define TELECOMMANDOPTIONSCONFIGURATION_UNCERTAINTYTIMEWINDOW_MINIMUMINTERVAL   0
#define TELECOMMANDOPTIONSCONFIGURATION_UNCERTAINTYTIMEWINDOW_MAXIMUMINTERVAL   SECONDSPERHOUR
#define TELECOMMANDOPTIONSCONFIGURATION_UNCERTAINTYTIMEWINDOW_DEFAULTINTERVAL   SECONDSPERMINUTE
#define TELECOMMANDOPTIONSCONFIGURATION_MAXIMUMEXECUTIONTIMEPERIOD_MINIMUMINTERVAL   1
#define TELECOMMANDOPTIONSCONFIGURATION_MAXIMUMEXECUTIONTIMEPERIOD_MAXIMUMINTERVAL   (365*HOURSPERDAY)
#define TELECOMMANDOPTIONSCONFIGURATION_MAXIMUMEXECUTIONTIMEPERIOD_DEFAULTINTERVAL   HOURSPERDAY
#define TELECOMMANDOPTIONSCONFIGURATION_MAXIMUMCHETIMECKPERIOD_MINIMUMINTERVAL   1
#define TELECOMMANDOPTIONSCONFIGURATION_MAXIMUMCHETIMECKPERIOD_MAXIMUMINTERVAL   (365*HOURSPERDAY)
#define TELECOMMANDOPTIONSCONFIGURATION_MAXIMUMCHETIMECKPERIOD_DEFAULTINTERVAL   HOURSPERDAY
#define TELECOMMANDOPTIONSCONFIGURATION_DEFAULTRELEASETIMEWINDOW_MINIMUMINTERVAL   1
#define TELECOMMANDOPTIONSCONFIGURATION_DEFAULTRELEASETIMEWINDOW_MAXIMUMINTERVAL   SECONDSPERDAY
#define TELECOMMANDOPTIONSCONFIGURATION_DEFAULTRELEASETIMEWINDOW_DEFAULTINTERVAL   TCSERVICE_COMMANDHANDLERTIMEWINDOW_DEFAULTRELEASEINTERVAL

class CTelecommandOptionsConfigurationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelecommandOptionsConfigurationPage)

	// Construction
public:
	CTelecommandOptionsConfigurationPage();

	// Attributes
private:
	CString  m_szCommandHandler[2][2];
	CUIntArray  m_nCommandHandlerAccessCodes[2];
	CStringArray  m_szCommandHandlerClients[2];
	CTimeKeyArray  m_tCommandHandlerStartTimes[2];
	CTimeKeyArray  m_tCommandHandlerStopTimes[2];
	CTCProcessCommandSources  m_pCommandHandlerSources[2];
	CTimeSpan  m_tCommandHandlerMaximumTimeCheckPeriod[2];
	CTimeSpan  m_tCommandHandlerMaximumExecutionTimePeriod[2];
	CTimeSpan  m_tCommandHandlerDefaultReleaseTimeWindow[2];
	CTimeSpan  m_tCommandHandlerVerificationUncertaintyTimeWindow[2];
	CTimeSpan  m_tCommandHandlerTimeout[2];
	UINT  m_nCommandHandlerPort[2];
	UINT  m_nCommandHandlerOptions[2];
	UINT  m_nCommandHandlerBufferSize[2];
	UINT  m_nCommandHandlerTelecommandingMode[2];
	UINT  m_nCommandHandlerTelecommandingState[2];
	UINT  m_nCommandHandlerTelecommandingFlags[2];
	BOOL  m_bCommandHandlerTelecommandingInterlockMode[2];
	BOOL  m_bCommandHandlerTelecommandingReleaseWaitMode[2];
	BOOL  m_bCommandHandlerTelecommandingAutoRejectionMode[2];
	BOOL  m_bCommandHandler[2][3];
	BOOL  m_bCLCWToolWindow[2];
	BOOL  m_bUpdate;

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsConfigurationPage)
	enum { IDD = IDD_TELECOMMANDOPTIONS_CONFIGURATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetCommandHandlerConfiguration(LPCTSTR pszPreferredCommandHandler, LPCTSTR pszBackupCommandHandler, BOOL bSelfCommandHandler, BOOL bAnyCommandHandler, BOOL bExclusiveCommandHandler, UINT nCommandHandlerOptions, UINT nCommandHandlerPort, UINT nCommandHandlerBufferSize, CONST CTimeSpan &tCommandHandlerTimeout, CONST CStringArray &szCommandHandlerClients, CONST CUIntArray &nCommandHandlerAccessCodes, CONST CTimeKeyArray &tCommandHandlerStartTimes, CONST CTimeKeyArray &tCommandHandlerStopTimes, CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, BOOL bCLCWToolWindow, BOOL bAllowUpdates, BOOL bBackup = FALSE);
	BOOL GetCommandHandlerConfiguration(CString &szPreferredCommandHandler, CString &szBackupCommandHandler, BOOL &bSelfCommandHandler, BOOL &bAnyCommandHandler, BOOL &bExclusiveCommandHandler, UINT &nCommandHandlerOptions, UINT &nCommandHandlerPort, UINT &nCommandHandlerBufferSize, CTimeSpan &tCommandHandlerTimeout, CStringArray &szCommandHandlerClients, CUIntArray &nCommandHandlerAccessCodes, CTimeKeyArray &tCommandHandlerStartTimes, CTimeKeyArray &tCommandHandlerStopTimes, CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, BOOL &bCLCWToolWindow) CONST;

	BOOL SetMasterManualModeOwner(LPCTSTR pszOwner);
	CString GetMasterManualModeOwner() CONST;

	INT CollectLogEntries(CTCLogEntries &pEntries) CONST;

	class CTelecommandOptionsDialog *GetParent() CONST;

private:
	BOOL EnumComputers();
	BOOL EnumClients();

	VOID ShowConfiguration();

	BOOL CollectLogEntry(CTCLogEntries &pEntries, LPCTSTR pszName, LPCTSTR pszDescription, LPCTSTR pszActivity, CONST CTimeKey &tTime) CONST;
	BOOL CollectLogEntry(CTCLogEntries &pEntries, LPCTSTR pszName, LPCTSTR pszComputer, LPCTSTR pszDescription, LPCTSTR pszActivity, CONST CTimeKey &tTime) CONST;

	CString FindMasterManualModeOwner(CONST CTCProcessCommandSources &pCommandSources) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsConfigurationPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsConfigurationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrimaryCommandHandler();
	afx_msg void OnSecondaryCommandHandler();
	afx_msg void OnAllowSelfCommandHandler();
	afx_msg void OnUseAnyCommandHandler();
	afx_msg void OnEnsureUniqueCommandHandler();
	afx_msg void OnAlwaysAllowExit();
	afx_msg void OnMoreOptions();
	afx_msg void OnMasterManualMode();
	afx_msg void OnReleaseWaitMode();
	afx_msg void OnAutoRejectionMode();
	afx_msg void OnDisableRelease();
	afx_msg void OnOverridePTV();
	afx_msg void OnOverridePEV();
	afx_msg void OnOverrideCEV();
	afx_msg void OnDisablePTV();
	afx_msg void OnDisablePEV();
	afx_msg void OnDisableCEV();
	afx_msg void OnEnableInterlocks();
	afx_msg void OnShowCLCWPanel();
	afx_msg void OnEditchangePrimaryCommandHandler();
	afx_msg void OnEditchangeSecondaryCommandHandler();
	afx_msg void OnEditchangeMasterManualModeOwner();
	afx_msg void OnSelchangePrimaryCommandHandler();
	afx_msg void OnSelchangeSecondaryCommandHandler();
	afx_msg void OnSelchangeMasterManualModeOwner();
	afx_msg void OnSpinchangeVerificationUncertaintyTimeWindow();
	afx_msg void OnSpinchangeMaximumExecutionTimePeriod();
	afx_msg void OnSpinchangeMaximumTimeCheckPeriod();
	afx_msg void OnSpinchangeDefaultReleaseTimeWindow();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsCommandSourcesPage dialog

#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_COMPUTER_STATIC   1002
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_COMPUTER   1003
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_TYPE_STATIC   1004
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_TYPE_MANUALSTACK   1005
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_TYPE_AUTOMATICSTACK   1006
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_TYPE_PROCEDURESMONITOR   1007
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_STATE_STATIC   1008
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_STATE   1009
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION   1010
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MODES   1011
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MODES_MASTERMANUALMODE   1012
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MODES_RELEASEWAITMODE   1013
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MODES_AUTOMATICREJECTIONMODE   1014
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_STATE_DISABLED   1015
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_CHECKS   1016
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_CHECKS_OVERRIDEPTV   1017
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_CHECKS_DISABLEPTV   1018
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_CHECKS_OVERRIDEPEV   1019
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_CHECKS_DISABLEPEV   1020
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_CHECKS_OVERRIDECEV   1021
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_CHECKS_DISABLECEV   1022
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_CHECKS_INTERLOCKS   1023
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MISCELLANEOUS   1024
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_STATIC   1025
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_INTERVAL   1026
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MISCELLANEOUS_DEFAULTRELEASETIMEWINDOW_INTERVAL_STATIC   1027
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MISCELLANEOUS_DISPATCHTIMEWINDOW_STATIC   1028
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MISCELLANEOUS_DISPATCHTIMEWINDOW_INTERVAL   1029
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MISCELLANEOUS_DISPATCHTIMEWINDOW_INTERVAL_STATIC   1030
#define IDC_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE_CONFIGURATION_MISCELLANEOUS_SUBSYSTEMS   1031

// Specify the telecommand options command sources page related settings
#define TELECOMMANDOPTIONSCOMMANDSOURCES_DEFAULTRELEASETIMEWINDOW_MINIMUMINTERVAL   1
#define TELECOMMANDOPTIONSCOMMANDSOURCES_DEFAULTRELEASETIMEWINDOW_MAXIMUMINTERVAL   SECONDSPERDAY
#define TELECOMMANDOPTIONSCOMMANDSOURCES_DEFAULTRELEASETIMEWINDOW_DEFAULTINTERVAL   TCSERVICE_COMMANDHANDLERTIMEWINDOW_DEFAULTRELEASEINTERVAL
#define TELECOMMANDOPTIONSCOMMANDSOURCES_DISPATCHTIMEWINDOW_MINIMUMINTERVAL   1
#define TELECOMMANDOPTIONSCOMMANDSOURCES_DISPATCHTIMEWINDOW_MAXIMUMINTERVAL   (5*SECONDSPERMINUTE)
#define TELECOMMANDOPTIONSCOMMANDSOURCES_DISPATCHTIMEWINDOW_DEFAULTINTERVAL   TCSERVICE_COMMANDHANDLERTIMEWINDOW_DISPATCHINTERVAL

class CTelecommandOptionsCommandSourcesPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelecommandOptionsCommandSourcesPage)

	// Construction
public:
	CTelecommandOptionsCommandSourcesPage();

	// Attributes
private:
	CTCProcessCommandSources  m_pCommandHandlerSources[2];
	BOOL  m_bUpdate;

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsCommandSourcesPage)
	enum { IDD = IDD_TELECOMMANDOPTIONS_COMMANDSOURCESPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetCommandHandlerSources(CONST CTCProcessCommandSources &pCommandSources, BOOL bAllowUpdates, BOOL bBackup = FALSE);
	BOOL GetCommandHandlerSources(CTCProcessCommandSources &pCommandSources) CONST;

	BOOL SetMasterManualModeOwner(LPCTSTR pszOwner);
	CString GetMasterManualModeOwner() CONST;

	INT CollectLogEntries(CTCLogEntries &pEntries) CONST;

	class CTelecommandOptionsDialog *GetParent() CONST;

private:
	BOOL EnumCommandSources();

	VOID ShowCommandSource();
	CTCProcessCommandSourceInfo *FindCommandSource() CONST;

	CString GetCommandSourceState(CTCProcessCommandSourceInfo *pCommandSourceInfo) CONST;

	BOOL CollectLogEntry(CTCLogEntries &pEntries, LPCTSTR pszName, LPCTSTR pszDescription, LPCTSTR pszActivity, CONST CTimeKey &tTime) CONST;
	BOOL CollectLogEntry(CTCLogEntries &pEntries, LPCTSTR pszName, LPCTSTR pszComputer, LPCTSTR pszDescription, LPCTSTR pszActivity, CONST CTimeKey &tTime) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsCommandSourcesPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsCommandSourcesPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnManualStack();
	afx_msg void OnAutomaticStack();
	afx_msg void OnProceduresMonitor();
	afx_msg void OnMasterManualMode();
	afx_msg void OnReleaseWaitMode();
	afx_msg void OnAutoRejectionMode();
	afx_msg void OnDisableRelease();
	afx_msg void OnOverridePTV();
	afx_msg void OnOverridePEV();
	afx_msg void OnOverrideCEV();
	afx_msg void OnDisablePTV();
	afx_msg void OnDisablePEV();
	afx_msg void OnDisableCEV();
	afx_msg void OnEnableInterlocks();
	afx_msg void OnSubSystems();
	afx_msg void OnEditchangeComputer();
	afx_msg void OnSelchangeComputer();
	afx_msg void OnSpinchangeDefaultReleaseTimeWindow();
	afx_msg void OnSpinchangeDispatchTimeWindow();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsInterlocksPage dialog

#define IDC_TELECOMMANDOPTIONS_INTERLOCKSPAGE_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_INTERLOCKSPAGE_LIST   1002
#define IDC_TELECOMMANDOPTIONS_INTERLOCKSPAGE_EDIT   1003
#define IDC_TELECOMMANDOPTIONS_INTERLOCKSPAGE_RESET   1004

class CTelecommandOptionsInterlocksPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelecommandOptionsInterlocksPage)

	// Construction
public:
	CTelecommandOptionsInterlocksPage();

	// Attributes
private:
	CTCInterlocks  m_pInterlocks[2];
	BOOL  m_bUpdate;
	BOOL  m_bModified;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsInterlocksPage)
	enum { IDD = IDD_TELECOMMANDOPTIONS_INTERLOCKSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetCommandHandlerInterlocks(CONST CTCInterlocks &pInterlocks, BOOL bAllowUpdates);
	BOOL GetCommandHandlerInterlocks(CTCInterlocks &pInterlocks) CONST;

	class CTelecommandOptionsDialog *GetParent() CONST;

private:
	VOID EnumInterlocks();

	BOOL LogActivity(CONST CTCInterlock *pInterlock, LPCTSTR pszActivity, BOOL bSuccess = TRUE);
	BOOL LogActivity(CONST CTCInterlocks &pInterlocks);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsInterlocksPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Update(CONST CTCInterlocks &pInterlocks);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsInterlocksPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEdit();
	afx_msg void OnReset();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsQueuePage dialog

#define IDC_TELECOMMANDOPTIONS_QUEUEPAGE_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_QUEUEPAGE_LIST   1002
#define IDC_TELECOMMANDOPTIONS_QUEUEPAGE_TIME_STATIC   1003
#define IDC_TELECOMMANDOPTIONS_QUEUEPAGE_TIME   1004
#define IDC_TELECOMMANDOPTIONS_QUEUEPAGE_REMOVE   1005
#define IDC_TELECOMMANDOPTIONS_QUEUEPAGE_REMOVEALL   1006

// Specify the telecommand options queue page related timer identifiers
#define TELECOMMANDOPTIONSQUEUEPAGE_RELEASECLOCK_TIMERID   1000
#define TELECOMMANDOPTIONSQUEUEPAGE_RELEASECLOCK_TIMEOUT   500

class CTelecommandOptionsQueuePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelecommandOptionsQueuePage)

	// Construction
public:
	CTelecommandOptionsQueuePage();

	// Attributes
private:
	CTCItems  m_pItems[2];
	UINT_PTR  m_nTimerID;
	BOOL  m_bModified;
	BOOL  m_bUpdate;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsQueuePage)
	enum { IDD = IDD_TELECOMMANDOPTIONS_QUEUEPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetCommandHandlerTelecommands(CONST CTCItems &pItems, BOOL bAllowUpdates);
	BOOL GetCommandHandlerTelecommands(CTCItems &pItems) CONST;

	class CTelecommandOptionsDialog *GetParent() CONST;

private:
	VOID EnumTelecommands();

	BOOL LogActivity(CONST CTCItem *pItem, BOOL bSuccess = TRUE);
	BOOL LogActivity(CONST CTCItems &pItems, BOOL bSuccess = TRUE);

	INT CalcColumnWidth(LPCTSTR pszColumn);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsQueuePage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Update(CONST CTCItems &pItems);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsQueuePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsHistoryPage dialog

#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_ARCHIVEFILENAME_USE   1002
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_ARCHIVEFILENAME   1003
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_ARCHIVEFILENAME_BROWSE   1004
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_BACKUPFILENAME_USE   1005
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_BACKUPFILENAME   1006
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_BACKUPFILENAME_BROWSE   1007
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_DELETEFILE_STATIC   1008
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_DELETEARCHIVEFILE   1009
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_DELETEBACKUPFILE   1010   
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_FILESETTINGS   1011
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS   1012
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_FILES_STATIC   1013
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_FILES   1014
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_FREESPACE   1015
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_FREESPACE_STATIC   1016
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_FILES_BROWSE   1017
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_FILES_INSPECT   1018
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_FILES_DEFAULT   1019
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_FILES_ADD   1020
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_FILES_REMOVE   1021
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_FILES_REMOVEALL   1022
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO   1023
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_COMMENTS   1024
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_PRODUCT_STATIC   1025
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_PRODUCT   1026
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_COMPANY_STATIC   1027
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_COMPANY   1028
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_SPACECRAFT_STATIC   1029
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_SPACECRAFT   1030
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_TYPE_STATIC   1031
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_TYPE   1032
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_TIMERANGE_STATIC   1033
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_TIMERANGE_STARTTIME   1034
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_TIMERANGE_TO   1035
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_TIMERANGE_STOPTIME   1036
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_CREATIONTIME_STATIC   1037
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_CREATIONTIME   1038
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_SIZE_STATIC   1039
#define IDC_TELECOMMANDOPTIONS_HISTORYPAGE_RETRIEVALS_SOURCEINFO_SIZE   1040

class CTelecommandOptionsHistoryPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelecommandOptionsHistoryPage)

	// Construction
public:
	CTelecommandOptionsHistoryPage();

	// Attributes
private:
	CHistoryStoreFiles  m_pArchivalFiles[2];
	CHistoryStoreFiles  m_pRetrievalFiles[2];
	CString  m_szDefaultRetrievalFileName[2];
	BOOL  m_bUpdate;

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsHistoryPage)
	enum { IDD = IDD_TELECOMMANDOPTIONS_HISTORYPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetHistoryConfiguration(CONST CHistoryStoreFiles &pArchivalFiles, CONST CHistoryStoreFiles &pRetrievalFiles, LPCTSTR pszDefaultRetrievalFileName, BOOL bAllowUpdates, BOOL bBackup = FALSE);
	BOOL GetHistoryConfiguration(CHistoryStoreFiles &pArchivalFiles, CHistoryStoreFiles &pRetrievalFiles, CString &szDefaultRetrievalFileName) CONST;

	INT EnumHistoryFilesToDelete(CStringArray &szFiles) CONST;

	INT CollectLogEntries(CTCLogEntries &pEntries) CONST;

	class CTelecommandOptionsDialog *GetParent() CONST;

private:
	BOOL EnumArchivalFiles();
	BOOL EnumRetrievalFiles();

	VOID InitializeFile(CHistoryStoreFile *pFile);

	VOID ShowDataSourceInfo();
	VOID ShowDataSourceInfo(LPCTSTR pszFileName);

	BOOL CheckRetrieveFile(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST;
	CString GetFreeRetrieveDiskSpace(LPCTSTR pszFileName) CONST;

	CString FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST;

	BOOL CollectLogEntry(CTCLogEntries &pEntries, LPCTSTR pszName, LPCTSTR pszDescription, LPCTSTR pszActivity, CONST CTimeKey &tTime) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsHistoryPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsHistoryPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnHistoryFile();
	afx_msg void OnBackupFile();
	afx_msg void OnBrowseHistoryFile();
	afx_msg void OnBrowseBackupFile();
	afx_msg void OnDeleteHistoryFile();
	afx_msg void OnDeleteBackupFile();
	afx_msg void OnFileSettings();
	afx_msg void OnAddRetrievalFile();
	afx_msg void OnRemoveRetrievalFile();
	afx_msg void OnRemoveAllRetrievalFiles();
	afx_msg void OnBrowseRetrievalFile();
	afx_msg void OnInspectRetrievalFile();
	afx_msg void OnDefaultRetrievalFile();
	afx_msg void OnEditchangeHistoryFile();
	afx_msg void OnEditchangeBackupFile();
	afx_msg void OnEditchangeRetrievalFile();
	afx_msg void OnUpdateStorageMediaFreeSpace();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsLoggingPage dialog

#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_LIST   1002
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_SETTINGS   1003
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_MODE_STATIC   1004
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_REALTIME   1005
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_RELOAD   1006
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_RELOAD_COUNT   1007
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_RELOAD_COUNT_STATIC   1008
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_HISTORICAL   1009
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_HISTORICAL_STARTTIME_STATIC   1010
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_HISTORICAL_STARTTIME   1011
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_HISTORICAL_STOPATTIME   1012
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_HISTORICAL_STOPTIME   1013
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_HISTORICAL_STOPATLIMIT   1014
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_HISTORICAL_STOPLIMIT   1015
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_HISTORICAL_STOPLIMIT_STATIC   1016
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_HISTORICAL_NOLIMIT   1017
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_HISTORICAL_RETRIEVE   1018
#define IDC_TELECOMMANDOPTIONS_LOGGINGPAGE_SHOWASEVENT   1019

// Specify the telecommand options logging page related limits
#define TELECOMMANDOPTIONSLOGGINGPAGE_MINIMUMRELOADCOUNT   1
#define TELECOMMANDOPTIONSLOGGINGPAGE_MAXIMUMRELOADCOUNT   1000
#define TELECOMMANDOPTIONSLOGGINGPAGE_DEFAULTRELOADCOUNT   25
#define TELECOMMANDOPTIONSLOGGINGPAGE_MINIMUMRETRIEVALSTOPCOUNT   1
#define TELECOMMANDOPTIONSLOGGINGPAGE_MAXIMUMRETRIEVALSTOPCOUNT   10000
#define TELECOMMANDOPTIONSLOGGINGPAGE_DEFAULTRETRIEVALSTOPCOUNT   100
// Specify the telecommand options logging page related timer identifiers
#define TELECOMMANDOPTIONSLOGGINGPAGE_LOGUPDATE_TIMERID   1001
#define TELECOMMANDOPTIONSLOGGINGPAGE_LOGUPDATE_TIMEOUT   500

class CTelecommandOptionsLoggingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelecommandOptionsLoggingPage)

	// Construction
public:
	CTelecommandOptionsLoggingPage();

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
	//{{AFX_DATA(CTelecommandOptionsLoggingPage)
	enum { IDD = IDD_TELECOMMANDOPTIONS_LOGGINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetLoggingOptions(UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent, BOOL bBackup = FALSE);
	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	class CTelecommandOptionsDialog *GetParent() CONST;

private:
	BOOL ShowLoggingDetails();

	VOID ShowLogEntries(CONST CTCLogEntries &pEntries);
	VOID ShowLogEntry(CONST CTCLogEntry *pEntry, INT nIndex = -1);

	BOOL RetrieveLogEntries();
	BOOL RetrieveLogEntries(CTCLogEntries &pEntries);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsLoggingPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Update();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsLoggingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnRealtime();
	afx_msg void OnHistorical();
	afx_msg void OnReloadCount();
	afx_msg void OnStopAtTime();
	afx_msg void OnStopAtLimit();
	afx_msg void OnStopAtEnd();
	afx_msg void OnSettings();
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
// CTelecommandOptionsTabCtrl window

class CTelecommandOptionsTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTelecommandOptionsTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTelecommandOptionsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelecommandOptionsTabCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsDialog

// Specify the telecommand options dialog related timer identifiers
#define TELECOMMANDOPTIONS_UPDATEINTERVAL_TIMERID   1002
#define TELECOMMANDOPTIONS_UPDATEINTERVAL_TIMEOUT   500

class CTelecommandOptionsDialog : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTelecommandOptionsDialog)

	// Construction
public:
	CTelecommandOptionsDialog(CWnd *pParentWnd = NULL);

	// Attributes
public:
	CTelecommandOptionsTabCtrl  m_wndTabCtrl;
	CTelecommandOptionsConfigurationPage  m_pageConfiguration;
	CTelecommandOptionsCommandSourcesPage  m_pageCommandSources;
	CTelecommandOptionsInterlocksPage  m_pageInterlocks;
	CTelecommandOptionsHistoryPage  m_pageHistory;
	CTelecommandOptionsLoggingPage  m_pageLogging;
	CTelecommandOptionsQueuePage  m_pageQueue;
private:
	BOOL  m_bUpdate;

	// Operations
public:
	VOID SetCommandHandlerConfiguration(LPCTSTR pszPreferredCommandHandler, LPCTSTR pszBackupCommandHandler, BOOL bSelfCommandHandler, BOOL bAnyCommandHandler, BOOL bExclusiveCommandHandler, UINT nCommandHandlerOptions, UINT nCommandHandlerPort, UINT nCommandHandlerBufferSize, CONST CTimeSpan &tCommandHandlerTimeout, CONST CStringArray &szCommandHandlerClients, CONST CUIntArray &nCommandHandlerAccessCodes, CONST CTimeKeyArray &tCommandHandlerStartTimes, CONST CTimeKeyArray &tCommandHandlerStopTimes, CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, BOOL bCLCWToolWindow);
	BOOL GetCommandHandlerConfiguration(CString &szPreferredCommandHandler, CString &szBackupCommandHandler, BOOL &bSelfCommandHandler, BOOL &bAnyCommandHandler, BOOL &bExclusiveCommandHandler, UINT &nCommandHandlerOptions, UINT &nCommandHandlerPort, UINT &nCommandHandlerBufferSize, CTimeSpan &tCommandHandlerTimeout, CStringArray &szCommandHandlerClients, CUIntArray &nCommandHandlerAccessCodes, CTimeKeyArray &tCommandHandlerStartTimes, CTimeKeyArray &tCommandHandlerStopTimes, CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, BOOL &bCLCWToolWindow) CONST;
	VOID SetCommandHandlerSources(CONST CTCProcessCommandSources &pCommandSources);
	BOOL GetCommandHandlerSources(CTCProcessCommandSources &pCommandSources) CONST;
	VOID UpdateCommandHandlerSources(LPCTSTR pszMasterManualModeOwner);
	VOID SetCommandHandlerInterlocks(CONST CTCInterlocks &pInterlocks);
	BOOL GetCommandHandlerInterlocks(CTCInterlocks &pInterlocks) CONST;
	VOID SetCommandHandlerTelecommands(CONST CTCItems &pItems);
	BOOL GetCommandHandlerTelecommands(CTCItems &pItems) CONST;
	VOID SetHistoryConfiguration(CONST CHistoryStoreFiles &pArchivalFiles, CONST CHistoryStoreFiles &pRetrievalFiles, LPCTSTR pszDefaultRetrievalFileName);
	BOOL GetHistoryConfiguration(CHistoryStoreFiles &pArchivalFiles, CHistoryStoreFiles &pRetrievalFiles, CString &szDefaultRetrievalFileName) CONST;
	VOID SetLoggingOptions(UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent);
	BOOL GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST;

	INT EnumHistoryFilesToDelete(CStringArray &szFiles) CONST;

	BOOL LogActivity(CONST CTCLogEntry *pEntry);
	BOOL LogActivity(CONST CTCLogEntry *pEntry, LPCTSTR pszFileName, UINT nPolicy, BOOL bShow);
	BOOL LogDeleteHistoryFile(LPCTSTR pszFileName, BOOL bSuccess);

private:
	BOOL FilterCommandHandlerContents(CTCItems &pItems) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsDialog)
public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelecommandOptionsDialog)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsInterlocksDialog dialog

#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_NAME_STATIC   1002
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_NAME   1003
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_ADD   1004
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_REMOVE   1005
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_REMOVEALL   1006
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES   1007
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_STATIC   1008
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_GLOBAL   1009
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_LOCAL   1010
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM   1011
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_SUBSYSTEM_NAME   1012
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_TELECOMMANDS   1013
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_NOWAITSTATE   1014
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_COMPUTER_STATIC   1015
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_COMPUTER   1016
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_COMMANDSOURCE_STATIC   1017
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_COMMANDSOURCE_MANUALSTACK   1018
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_COMMANDSOURCE_AUTOMATICSTACK   1019
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_SCOPE_COMMANDSOURCE_PROCEDURESMONITOR   1020
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_STAGE_STATIC   1021
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_STAGE_RECEPTION   1022
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_STAGE_TRANSMISSION   1023
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_STAGE_ACCEPTANCE   1024
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_STAGE_START   1025
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_STAGE_PROGRESS   1026
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_PROPERTIES_STAGE_COMPLETION   1027
#define IDC_TELECOMMANDOPTIONS_INTERLOCKS_HELP   1028

class CTelecommandOptionsInterlocksDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandOptionsInterlocksDialog)

	// Construction
public:
	CTelecommandOptionsInterlocksDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CStringArray  m_szComputers;
	CTCInterlock  m_cInterlock;
	CTCInterlocks  m_pInterlocks[2];

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsInterlocksDialog)
	enum { IDD = IDD_TELECOMMANDOPTIONS_INTERLOCKS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumInterlocks();
	BOOL EnumSubSystems();
	BOOL EnumComputers();

	VOID ShowProperties();
	VOID ShowProperties(CONST CTCInterlock *pInterlock);

	CTCInterlock *FindInterlock(INT nIndex = -1) CONST;

	UINT TranslateToSubSystemID(LPCTSTR pszSubSystem) CONST;
	CString TranslateIDToSubSystem(UINT nSubSystemID) CONST;

	BOOL CanAddInterlock() CONST;
	BOOL CanRemoveInterlock() CONST;
	BOOL CanRemoveAllInterlocks() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsInterlocksDialog)
public:
	virtual INT DoModal(CONST CStringArray &szComputers, CTCInterlocks &pInterlocks);
	virtual INT DoModal(CONST CStringArray &szComputers, CONST CTCInterlock *pInterlock, CTCInterlocks &pInterlocks);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsInterlocksDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnScopeGlobal();
	afx_msg void OnScopeLocal();
	afx_msg void OnScopeSubSystem();
	afx_msg void OnScopeTeleommands();
	afx_msg void OnScopeNoWaitState();
	afx_msg void OnTypeManualStack();
	afx_msg void OnTypeAutomaticStack();
	afx_msg void OnTypeProceduresMonitor();
	afx_msg void OnStageReception();
	afx_msg void OnStageTransmission();
	afx_msg void OnStageAcceptance();
	afx_msg void OnStageStart();
	afx_msg void OnStageProgress();
	afx_msg void OnStageCompletion();
	afx_msg void OnEditchangeName();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeSubSystem();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsSubSystemsDialog dialog

#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_LIST_STATIC   1002
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_LIST   1003
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_BEHAVIOR   1004
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_BEHAVIOR_STATIC   1005
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_BEHAVIOR_ENABLED   1006
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_BEHAVIOR_ENABLEBYEVENT   1007
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_BEHAVIOR_ENABLEEVENTNAME   1008
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_BEHAVIOR_DISABLED   1009
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_BEHAVIOR_DISABLEBYEVENT   1010
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_BEHAVIOR_DISABLEEVENTNAME   1011
#define IDC_TELECOMMANDOPTIONS_SUBSYSTEMS_HELP   1012

class CTelecommandOptionsSubSystemsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandOptionsSubSystemsDialog)

	// Construction
public:
	CTelecommandOptionsSubSystemsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szComputer;
	CUIntArray  m_nSubSystemIDs[2];
	CUIntArray  m_nSubSystemStatus[2];
	CStringArray  m_szSubSystemEvents[2][2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsSubSystemsDialog)
	enum { IDD = IDD_TELECOMMANDOPTIONS_SUBSYSTEMS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumSubSystems();
	BOOL EnumEvents();

	VOID ShowDetails();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsSubSystemsDialog)
public:
	virtual INT DoModal(CTCProcessCommandSourceInfo *pCommandSourceInfo);
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
	//{{AFX_MSG(CTelecommandOptionsSubSystemsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEnableSubSystem();
	afx_msg void OnDisableSubSystem();
	afx_msg void OnUseEnableSubSystemEvent();
	afx_msg void OnUseDisableSubSystemEvent();
	afx_msg void OnSelchangeEnableSubSystemEvent();
	afx_msg void OnSelchangeDisableSubSystemEvent();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsCommandHandlerSettingsDialog dialog

#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_PORT_STATIC   1002
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_PORT   1003
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_BUFFERSIZE_STATIC   1004
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_BUFFERSIZE   1005
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_BUFFERSIZE_KB   1006
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_TIMEOUT_STATIC   1007
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_TIMEOUT   1008
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_TIMEOUT_SECONDS   1009
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_STANDARD_STATIC   1010
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY   1011
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_CLIENTS_STATIC   1012
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_CLIENTS   1013
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_ADDCLIENTS   1014
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_REMOVECLIENTS   1015
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_ANYCLIENT   1016
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_RESTRICTIONS_STATIC   1017
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_RESTRICTIONS_NONE   1018
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_RESTRICTIONS_FULL   1019
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_RESTRICTIONS_PARTIAL   1020
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_RESTRICTIONS_STARTTIME   1021
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_RESTRICTIONS_PARTIAL_STATIC   1022
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_RESTRICTIONS_STOPTIME   1023
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_SECURITY_RESTRICTIONS_AUDIT   1024
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_HELP   1025

// Specify the telecommand options command handler settings dialog related defaults
#define TELECOMMANDOPTIONSCOMMANDHANDLERSETTINGS_DEFAULTACCESSPERIOD   SECONDSPERHOUR

class CTelecommandOptionsCommandHandlerSettingsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandOptionsCommandHandlerSettingsDialog)

	// Construction
public:
	CTelecommandOptionsCommandHandlerSettingsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	UINT  m_nPort[2];
	UINT  m_nBufferSize[2];
	CTimeSpan  m_tTimeout[2];
	CUIntArray  m_nAccessCodes[2];
	CStringArray  m_szClients[2];
	CTimeKeyArray  m_tStartTimes[2];
	CTimeKeyArray  m_tStopTimes[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsCommandHandlerSettingsDialog)
	enum { IDD = IDD_TELECOMMANDOPTIONS_COMMANDHANDLERSETTINGS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID ShowCommandHandlerDetails();

	VOID ShowClientProperties(INT nIndex = 0);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsCommandHandlerSettingsDialog)
public:
	virtual INT DoModal(UINT &nPort, UINT &nBufferSize, CTimeSpan &tTimeout, CStringArray &szClients, CUIntArray &nAccessCodes, CTimeKeyArray &tStartTimes, CTimeKeyArray &tStopTimes);
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
	//{{AFX_MSG(CTelecommandOptionsCommandHandlerSettingsDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddClients();
	afx_msg void OnRemoveClients();
	afx_msg void OnAllowAnyClient();
	afx_msg void OnNoAccessRestrictions();
	afx_msg void OnFullAccessRestrictions();
	afx_msg void OnPartialAccessRestrictions();
	afx_msg void OnAuditRestrictions();
	afx_msg void OnSpinchangeProtocolPort();
	afx_msg void OnSpinchangeProtocolBufferSize();
	afx_msg void OnSpinchangeProtocolTimeout();
	afx_msg void OnSpinchangeAccessStartTime();
	afx_msg void OnSpinchangeAccessStopTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsCommandHandlerClientAddressesDialog dialog

#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_NAME_STATIC   1002
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_NAME   1003
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_ADDRESS_STATIC   1004
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_ADDRESS   1005
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_ADDRESSSYNTAX_STATIC   1006
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_ADDADDRESS   1007
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_REMOVEADDRESS   1008
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_ADDRESSLIST   1009
#define IDC_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_HELP   1010

class CTelecommandOptionsCommandHandlerClientAddressesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandOptionsCommandHandlerClientAddressesDialog)

	// Construction
public:
	CTelecommandOptionsCommandHandlerClientAddressesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CStringArray  m_szAddresses;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsCommandHandlerClientAddressesDialog)
	enum { IDD = IDD_TELECOMMANDOPTIONS_COMMANDHANDLERCLIENTADDRESSES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumComputers();

	BOOL CheckName(LPCTSTR pszName) CONST;
	BOOL CheckAddress(LPCTSTR pszAddress, BOOL bSyntax = FALSE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsCommandHandlerClientAddressesDialog)
public:
	virtual INT DoModal(CStringArray &szAddresses);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsCommandHandlerClientAddressesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeAddress();
	afx_msg void OnSelchangeName();
	afx_msg void OnAddAddress();
	afx_msg void OnRemoveAddress();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsHistoryArchivalSettingsDialog dialog

#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_FILENAME_STATIC   1002
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_FILENAME   1003
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_DISABLED   1004
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_SECONDARY   1005
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_SECONDARY_FILENAME   1006
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_SECONDARY_FILENAME_STATIC   1007
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_PROPERTIES   1008
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_PROPERTIES_POLICY   1009
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_PROPERTIES_POLICY_CYCLIC   1010
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_PROPERTIES_POLICY_NONCYCLIC   1011
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_PROPERTIES_SIZE   1012
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_PROPERTIES_SIZE_UNLIMITED   1013
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_PROPERTIES_SIZE_LIMITED   1014
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_PROPERTIES_SIZE_MAXIMUM   1015
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_PROPERTIES_SIZE_MAXIMUM_STATIC   1016
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_PROPERTIES_SIZE_COMPRESSION   1017
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP   1018
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_TYPE   1019
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_TYPE_SIMPLE   1020
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_TYPE_TIMETAGGED   1021
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_TYPE_ENUMERATED   1022
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_DIRECTORY_STATIC   1023
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_DIRECTORY   1024
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_TRIGGER   1025
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_TRIGGER_AUTO   1026
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_TRIGGER_SIZE   1027
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_TRIGGER_SIZE_MB   1028
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_TRIGGER_SIZE_MB_STATIC   1029
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_PERFORM   1030
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_RESTRICTIONS   1031
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_RESTRICTION_DAILY   1032
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_RESTRICTION_DAILY_STARTTIME   1033
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_RESTRICTION_DAILY_STATIC   1034
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_RESTRICTION_DAILY_STOPTIME   1035
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_RESTRICTION_DISK   1036
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_FAILURES   1037
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_FAILURES_STATIC   1038
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_FAILURES_RETRY_COUNT   1039
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_FAILURES_RETRY_INTERVAL_STATIC   1040
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_FAILURES_RETRY_INTERVAL   1041
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_BACKUP_BEHAVIOR_AUDITFAILURES   1042
#define IDC_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_HELP   1043

// Specify the telecommand options history archival settings dialog related settings
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_MINIMUMSIZE   1
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_MAXIMUMSIZE   2147483647
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_DEFAULTSIZE   1024
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_MINIMUMPERIOD   1
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_MAXIMUMPERIOD   MINUTESPERWEEK
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_DEFAULTPERIOD   MINUTESPERHOUR
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_MINIMUMRETRIES   1
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_MAXIMUMRETRIES   100
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_DEFAULTRETRIES   5
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_MINIMUMRETRYINTERVAL   1
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_MAXIMUMRETRYINTERVAL   MINUTESPERWEEK
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_DEFAULTRETRYINTERVAL   5
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_DAILYSTARTTIME   HOURS(8)
#define TELECOMMANDOPTIONSHISTORYARCHIVALSETTINGS_DAILYSTOPTIME   HOURS(17)

class CTelecommandOptionsHistoryArchivalSettingsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandOptionsHistoryArchivalSettingsDialog)

	// Construction
public:
	CTelecommandOptionsHistoryArchivalSettingsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CHistoryStoreFiles  m_pArchivalFiles[2];

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsHistoryArchivalSettingsDialog)
	enum { IDD = IDD_TELECOMMANDOPTIONS_HISTORYARCHIVALSETTINGS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumArchivingFiles();

	VOID ShowArchivingOptions();
	CHistoryStoreFile *FindArchivingFile() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsHistoryArchivalSettingsDialog)
public:
	virtual INT DoModal(CHistoryStoreFiles &pArchivalFiles);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsHistoryArchivalSettingsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDisabled();
	afx_msg void OnUseSecondary();
	afx_msg void OnCyclicMode();
	afx_msg void OnNonCyclicMode();
	afx_msg void OnUnlimitedSize();
	afx_msg void OnLimitedSize();
	afx_msg void OnUseCompression();
	afx_msg void OnTypeSimple();
	afx_msg void OnTypeTimeTagged();
	afx_msg void OnTypeEnumerated();
	afx_msg void OnBackups();
	afx_msg void OnBackupByDefault();
	afx_msg void OnBackupBySize();
	afx_msg void OnBackupDaily();
	afx_msg void OnBackupEmptyDisk();
	afx_msg void OnBackupFailures();
	afx_msg void OnBackupAuditFailures();
	afx_msg void OnEditchangeSecondaryFileName();
	afx_msg void OnEditchangeBackupDirectory();
	afx_msg void OnSelchangeFileName();
	afx_msg void OnSpinchangeSize();
	afx_msg void OnSpinchangeBackupBySize();
	afx_msg void OnSpinchangeBackupDailyStartTime();
	afx_msg void OnSpinchangeBackupDailyStopTime();
	afx_msg void OnSpinchangeBackupRetries();
	afx_msg void OnSpinchangeBackupInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandOptionsLoggingArchivalSettingsDialog dialog

#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_FILENAME_STATIC   1002
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_FILENAME   1003
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_BROWSE   1004
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_DISABLED   1005
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_RETRIEVALS   1006
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_POLICY   1007
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_POLICY_OVERWRITE   1008
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_POLICY_OLDOVERWRITE   1009
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_POLICY_DAYS_STATIC   1010
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_POLICY_DAYS   1011
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_POLICY_NOOVERWRITE   1012
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_SIZE   1013
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_SIZE_UNLIMITED   1014
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_SIZE_LIMITED   1015
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_SIZE_MAXIMUM_STATIC   1016
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_SIZE_MAXIMUM   1017
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_SIZE_RESET   1018
#define IDC_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_HELP   1019

// Specify the telecommand options logging archival settings dialog related settings
#define TELECOMMANDOPTIONSLOGGINGARCHIVALSETTINGS_MINIMUMDAYS   1
#define TELECOMMANDOPTIONSLOGGINGARCHIVALSETTINGS_MAXIMUMDAYS   10000
#define TELECOMMANDOPTIONSLOGGINGARCHIVALSETTINGS_DEFAULTDAYS   DAYSPERWEEK
#define TELECOMMANDOPTIONSLOGGINGARCHIVALSETTINGS_MINIMUMSIZE   8
#define TELECOMMANDOPTIONSLOGGINGARCHIVALSETTINGS_MAXIMUMSIZE   2147483647
#define TELECOMMANDOPTIONSLOGGINGARCHIVALSETTINGS_DEFAULTSIZE   (LOGFILE_DEFAULT_SIZE/1024)

class CTelecommandOptionsLoggingArchivalSettingsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandOptionsLoggingArchivalSettingsDialog)

	// Construction
public:
	CTelecommandOptionsLoggingArchivalSettingsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szArchivalFileName[2];
	CString  m_szRetrievalFileName[2];
	DWORDLONG  m_dwArchivalRetention[2];
	CTimeSpan  m_tArchivalRetention[2];
	UINT  m_nArchivalPolicy[2];

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsLoggingArchivalSettingsDialog)
	enum { IDD = IDD_TELECOMMANDOPTIONS_LOGGINGARCHIVALSETTINGS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID ShowLoggingOptions();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsLoggingArchivalSettingsDialog)
public:
	virtual INT DoModal(CString &szArchivalFileName, UINT &nArchivalPolicy, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsLoggingArchivalSettingsDialog)
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
// CTelecommandOptionsLoggingRetrievalSettingsDialog dialog

#define IDC_TELECOMMANDOPTIONS_LOGGINGRETRIEVALSETTINGS_DETAILS   1001
#define IDC_TELECOMMANDOPTIONS_LOGGINGRETRIEVALSETTINGS_FILENAME_STATIC   1002
#define IDC_TELECOMMANDOPTIONS_LOGGINGRETRIEVALSETTINGS_FILENAME   1003
#define IDC_TELECOMMANDOPTIONS_LOGGINGRETRIEVALSETTINGS_BROWSE   1004
#define IDC_TELECOMMANDOPTIONS_LOGGINGRETRIEVALSETTINGS_HELP   1005

class CTelecommandOptionsLoggingRetrievalSettingsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandOptionsLoggingRetrievalSettingsDialog)

	// Construction
public:
	CTelecommandOptionsLoggingRetrievalSettingsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szFileName[2];

	// Dialog Data
	//{{AFX_DATA(CTelecommandOptionsLoggingRetrievalSettingsDialog)
	enum { IDD = IDD_TELECOMMANDOPTIONS_LOGGINGRETRIEVALSETTINGS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandOptionsLoggingRetrievalSettingsDialog)
public:
	virtual INT DoModal(CString &szFileName);
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelecommandOptionsLoggingRetrievalSettingsDialog)
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
// CTelecommandParameterSet

class CTelecommandParameterSet : public CTCParameters
{
	// Construction
public:
	CTelecommandParameterSet();
	~CTelecommandParameterSet();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbParameters;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;

	BOOL Copy(CONST CTelecommandParameterSet *pTCParameterSet);
	BOOL Compare(CONST CTelecommandParameterSet *pTCParameterSet) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandParameterSets

class CTelecommandParameterSets : public CPtrArray
{
	// Construction
public:
	CTelecommandParameterSets();
	~CTelecommandParameterSets();

	// Attributes
public:

	// Operations
public:
	INT Add(CTelecommandParameterSet *pTCParameterSet);

	INT Find(LPCTSTR pszName) CONST;

	CTelecommandParameterSet *GetAt(INT nIndex) CONST;
	CTelecommandParameterSet *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTelecommandParameterSets *pTCParameterSets);
	BOOL Compare(CONST CTelecommandParameterSets *pTCParameterSets) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);

private:
	INT FindIndex(LPCTSTR pszName, BOOL bInsert = FALSE) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandParametersCharacteristicsPage dialog

#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_TYPE_STATIC   1001
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_TYPE_RAW   1002
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_TYPE_NUMERICAL   1003
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_TYPE_STATUS   1004
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_WIDTH_STATIC   1005
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_WIDTH   1006
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_WIDTH_BITS   1007
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_WIDTH_BIT   1008
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_UNITS_STATIC   1009
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_UNITS   1010
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_VALUE_STATIC   1011
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_VALUE_VARIABLE   1012
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_VALUE_FIXED   1013
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_VALUE_FORMAL   1014
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_CODING_STATIC   1015
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_CODING_BITPATTERN   1016
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_CODING_SIGNEDINTEGER   1017
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_CODING_UNSIGNEDINTEGER   1018
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_CODING_FLOATINGPOINT   1019
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_CODING_TIME   1020
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_RADIX_STATIC   1021
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_RADIX_BINARY   1022
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_RADIX_OCTAL   1023
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_RADIX_DECIMAL   1024
#define IDC_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE_RADIX_HEXADECIMAL   1025

class CTelecommandParametersCharacteristicsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelecommandParametersCharacteristicsPage)

	// Construction
public:
	CTelecommandParametersCharacteristicsPage();

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTelecommandParametersCharacteristicsPage)
	enum { IDD = IDD_TELECOMMANDPARAMETERS_CHARACTERISTICSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);

	class CTelecommandParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandParametersCharacteristicsPage)
public:
	virtual BOOL HasParameterInfo() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelecommandParametersCharacteristicsPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandParametersCalibrationPage dialog

#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_TABLE_STATIC   1001
#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_TABLE   1002
#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_INTERPRETATION_STATIC   1007
#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_INTERPRETATION   1008
#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_STATUS_STATIC   1009
#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_STATUS   1010
#define IDC_TELECOMMANDPARAMETERS_CALIBRATIONPAGE_POINTS   1011

class CTelecommandParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelecommandParametersCalibrationPage)

	// Construction
public:
	CTelecommandParametersCalibrationPage();

	// Attributes
private:
	ULONGLONG  m_nCalTableType;
	CUIntArray  m_nCalTableRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandParametersCalibrationPage)
	enum { IDD = IDD_TELECOMMANDPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);
	VOID ShowCalibrationInfo();

	class CTelecommandParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandParametersCalibrationPage)
public:
	virtual BOOL HasParameterInfo() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelecommandParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTable();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandParametersLimitsPage dialog

#define IDC_TELECOMMANDPARAMETERS_LIMITSPAGE_TABLE_STATIC   1001
#define IDC_TELECOMMANDPARAMETERS_LIMITSPAGE_TABLE   1002
#define IDC_TELECOMMANDPARAMETERS_LIMITSPAGE_ID_STATIC   1003
#define IDC_TELECOMMANDPARAMETERS_LIMITSPAGE_ID   1004
#define IDC_TELECOMMANDPARAMETERS_LIMITSPAGE_TYPE_STATIC   1005
#define IDC_TELECOMMANDPARAMETERS_LIMITSPAGE_TYPE   1006
#define IDC_TELECOMMANDPARAMETERS_LIMITSPAGE_STATUS_STATIC   1007
#define IDC_TELECOMMANDPARAMETERS_LIMITSPAGE_STATUS   1008
#define IDC_TELECOMMANDPARAMETERS_LIMITSPAGE_POINTS   1009

class CTelecommandParametersLimitsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelecommandParametersLimitsPage)

	// Construction
public:
	CTelecommandParametersLimitsPage();

	// Attributes
private:
	ULONGLONG  m_nOolTableType;
	CUIntArray  m_nOolTableRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandParametersLimitsPage)
	enum { IDD = IDD_TELECOMMANDPARAMETERS_LIMITSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);
	VOID ShowLimitsInfo();

	class CTelecommandParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandParametersLimitsPage)
public:
	virtual BOOL HasParameterInfo() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelecommandParametersLimitsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTable();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandParametersAllocationsPage dialog

#define IDC_TELECOMMANDPARAMETERS_ALLOCATIONSPAGE_TYPE_STATIC   1001
#define IDC_TELECOMMANDPARAMETERS_ALLOCATIONSPAGE_TYPE   1002
#define IDC_TELECOMMANDPARAMETERS_ALLOCATIONSPAGE_COMMENT1   1003
#define IDC_TELECOMMANDPARAMETERS_ALLOCATIONSPAGE_COMMENT2   1004
#define IDC_TELECOMMANDPARAMETERS_ALLOCATIONSPAGE_LOCATIONS   1005

class CTelecommandParametersAllocationsPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTelecommandParametersAllocationsPage)

	// Construction
public:
	CTelecommandParametersAllocationsPage();

	// Attributes
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandParametersAllocationsPage)
	enum { IDD = IDD_TELECOMMANDPARAMETERS_ALLOCATIONSPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);

	class CTelecommandParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandParametersAllocationsPage)
public:
	virtual BOOL HasParameterInfo() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTelecommandParametersAllocationsPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandParametersFolderTabCtrl window

class CTelecommandParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTelecommandParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTelecommandParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelecommandParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandParametersFolder

class CTelecommandParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTelecommandParametersFolder)

	// Construction
public:
	CTelecommandParametersFolder();

	// Attributes
private:
	CTelecommandParametersCharacteristicsPage  m_pageCharacteristics;
	CTelecommandParametersCalibrationPage  m_pageCalibration;
	CTelecommandParametersLimitsPage  m_pageLimits;
	CTelecommandParametersAllocationsPage  m_pageAllocations;
	CTelecommandParametersFolderTabCtrl  m_wndTabCtrl;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo();
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);

	class CTelecommandParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandParametersFolder)
public:
	virtual BOOL CheckPageAccessibility(INT nIndex) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTelecommandParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandParametersDialog dialog

#define IDC_TELECOMMANDPARAMETERS_DETAILS   1001
#define IDC_TELECOMMANDPARAMETERS_NAME_STATIC   1002
#define IDC_TELECOMMANDPARAMETERS_NAME   1003
#define IDC_TELECOMMANDPARAMETERS_RESETALL   1004
#define IDC_TELECOMMANDPARAMETERS_FOLDER   1005
#define IDC_TELECOMMANDPARAMETERS_SETS   1006
#define IDC_TELECOMMANDPARAMETERS_SETS_MEMBERS   1007
#define IDC_TELECOMMANDPARAMETERS_SETS_MEMBER_COMMENT   1008
#define IDC_TELECOMMANDPARAMETERS_SETS_MEMBER_ADD   1009
#define IDC_TELECOMMANDPARAMETERS_SETS_MEMBER_REMOVE   1010
#define IDC_TELECOMMANDPARAMETERS_SETS_MEMBER_REMOVEALL   1011
#define IDC_TELECOMMANDPARAMETERS_SETS_MEMBER_VALUE_STATIC   1012
#define IDC_TELECOMMANDPARAMETERS_SETS_MEMBER_VALUE   1013
#define IDC_TELECOMMANDPARAMETERS_SETS_MEMBER_VALUE_SET   1014
#define IDC_TELECOMMANDPARAMETERS_SETS_NAME_STATIC   1015
#define IDC_TELECOMMANDPARAMETERS_SETS_NAME   1016
#define IDC_TELECOMMANDPARAMETERS_SETS_SAVE   1017
#define IDC_TELECOMMANDPARAMETERS_SETS_DELETE   1018
#define IDC_TELECOMMANDPARAMETERS_SETS_IMPORT   1019
#define IDC_TELECOMMANDPARAMETERS_SETS_EXPORT   1020
#define IDC_TELECOMMANDPARAMETERS_HELP   1021

class CTelecommandParametersDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandParametersDialog)

	// Construction
public:
	CTelecommandParametersDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelecommandParameterSet  m_cTCParameterSet;
	CTelecommandParameterSets  m_pTCParameterSets[2];
	CDatabaseTCParameter  m_cDatabaseTCParameter;
private:
	CTelecommandParametersFolder  m_wndFolderCtrl;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandParametersDialog)
	enum { IDD = IDD_TELECOMMANDPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumParameters();
	BOOL EnumParameterSets();
	BOOL EnumParameterValues();

	VOID ShowParameterSetMembers();
	VOID ShowParameterInfo();

	CDatabaseTCParameter *FindParameter() CONST;

	UINT CheckTCParameterOolStatus(CONST CTCParameter *pTCParameter) CONST;

	CRect CalcFolderSize() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandParametersDialog)
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
	//{{AFX_MSG(CTelecommandParametersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddSetMember();
	afx_msg void OnRemoveSetMember();
	afx_msg void OnRemoveAllSetMembers();
	afx_msg void OnSetMemberValueInitialization();
	afx_msg void OnSaveSet();
	afx_msg void OnDeleteSet();
	afx_msg void OnImportSets();
	afx_msg void OnExportSets();
	afx_msg void OnResetAllParameters();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeSetMemberValue();
	afx_msg void OnSelchangeSetName();
	afx_msg void OnEditchangeSetMemberValue();
	afx_msg void OnEditchangeSetName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandParametersImportSetsDialog dialog

#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_DETAILS   1001
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_FILENAME_STATIC   1002
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_FILENAME   1003
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_FILENAME_BROWSE   1004
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_FILENAME_INSPECT   1005
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_COMMENT   1006
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_LIST_STATIC   1007
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_LIST   1008
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_LIST_REMOVE   1009
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_LIST_REMOVEALL   1010
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_PROPERTIES   1011
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_PROPERTIES_MEMBERS   1012
#define IDC_TELECOMMANDPARAMETERS_IMPORTSETS_HELP   1013

class CTelecommandParametersImportSetsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandParametersImportSetsDialog)

	// Construction
public:
	CTelecommandParametersImportSetsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelecommandParameterSets  m_pSets[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandParametersImportSetsDialog)
	enum { IDD = IDD_TELECOMMANDPARAMETERS_IMPORTSETS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumParameterSets();

	VOID ShowParameterSetMembers();
	VOID ExamineParameterSets();

	CTelecommandParameterSet *FindParameterSet() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandParametersImportSetsDialog)
public:
	virtual INT DoModal(CTelecommandParameterSets &pSets);
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelecommandParametersImportSetsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnFilenameBrowse();
	afx_msg void OnInspectParameterSet();
	afx_msg void OnRemoveParameterSet();
	afx_msg void OnRemoveAllParameterSets();
	afx_msg void OnSelchangeParameterSet();
	afx_msg void OnEditchangeFilename();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTelecommandParametersExportSetsDialog dialog

#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_DETAILS   1001
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_NAME_STATIC   1002
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_NAME   1003
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_PROPERTIES   1004
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_PROPERTIES_MEMBERS   1005
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_LIST_STATIC   1006
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_LIST   1007
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_LIST_ADD   1008
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_LIST_REMOVE   1009
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_LIST_REMOVEALL  1010
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_FILENAME_STATIC   1011
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_FILENAME   1012
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_FILENAME_BROWSE   1013
#define IDC_TELECOMMANDPARAMETERS_EXPORTSETS_HELP   1014

class CTelecommandParametersExportSetsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTelecommandParametersExportSetsDialog)

	// Construction
public:
	CTelecommandParametersExportSetsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTelecommandParameterSets  m_pSets;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTelecommandParametersExportSetsDialog)
	enum { IDD = IDD_TELECOMMANDPARAMETERS_EXPORTSETS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumParameterSets();

	VOID ShowParameterSetMembers();

	CTelecommandParameterSet *FindParameterSet() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTelecommandParametersExportSetsDialog)
public:
	virtual INT DoModal(CONST CTelecommandParameterSets &pSets);
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTelecommandParametersExportSetsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddParameterSet();
	afx_msg void OnRemoveParameterSet();
	afx_msg void OnRemoveAllParameterSets();
	afx_msg void OnFilenameBrowse();
	afx_msg void OnSelchangeParameterSet();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CServerAddressBookDialog dialog

#define IDC_SERVERADDRESSBOOK_DETAILS   1001
#define IDC_SERVERADDRESSBOOK_COMPUTER_STATIC   1002
#define IDC_SERVERADDRESSBOOK_COMPUTER   1003
#define IDC_SERVERADDRESSBOOK_CONNECT   1004
#define IDC_SERVERADDRESSBOOK_CONNECTION   1005
#define IDC_SERVERADDRESSBOOK_SERVER_STATIC   1006
#define IDC_SERVERADDRESSBOOK_SERVER   1007
#define IDC_SERVERADDRESSBOOK_ADDSERVER   1008
#define IDC_SERVERADDRESSBOOK_REMOVESERVER   1009
#define IDC_SERVERADDRESSBOOK_REMOVEALLSERVERS   1010
#define IDC_SERVERADDRESSBOOK_DEVICE_STATIC   1011
#define IDC_SERVERADDRESSBOOK_DEVICE   1012
#define IDC_SERVERADDRESSBOOK_DEVICETYPE_STATIC   1013
#define IDC_SERVERADDRESSBOOK_DEVICETYPE   1014
#define IDC_SERVERADDRESSBOOK_DEVICETYPEDEFAULT   1015
#define IDC_SERVERADDRESSBOOK_ACCESS   1016
#define IDC_SERVERADDRESSBOOK_ACCESS_VPN   1017
#define IDC_SERVERADDRESSBOOK_ACCESS_PHONE   1018
#define IDC_SERVERADDRESSBOOK_DIALUP   1019
#define IDC_SERVERADDRESSBOOK_DIALUP_NUMBERS_STATIC   1020
#define IDC_SERVERADDRESSBOOK_DIALUP_NUMBERS   1021
#define IDC_SERVERADDRESSBOOK_DIALUP_ADDNUMBER   1022
#define IDC_SERVERADDRESSBOOK_DIALUP_REMOVENUMBER   1023
#define IDC_SERVERADDRESSBOOK_DIALUP_BEHAVIOR   1024
#define IDC_SERVERADDRESSBOOK_DIALUP_BEHAVIOR_CALLBACK   1025
#define IDC_SERVERADDRESSBOOK_DIALUP_BEHAVIOR_CALLBACKNUMBER   1026
#define IDC_SERVERADDRESSBOOK_DIALUP_BEHAVIOR_TRYALLNUMBERS   1027
#define IDC_SERVERADDRESSBOOK_DIALUP_BEHAVIOR_MODEMSPEAKER   1028
#define IDC_SERVERADDRESSBOOK_DIALUP_BEHAVIOR_SOFTWARECOMPRESSION   1029
#define IDC_SERVERADDRESSBOOK_HELP   1030

class CServerAddressBookDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CServerAddressBookDialog)

	// Construction
public:
	CServerAddressBookDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szComputer;
	CStringArray  m_szComputers;
	CStringArray  m_szDeviceNames;
	CStringArray  m_szDeviceTypes;
	CServerProfiles  m_pAddressBook[2];
	CPtrArray  m_pAddressBooks[2];

	// Dialog Data
	//{{AFX_DATA(CServerAddressBookDialog)
	enum { IDD = IDD_SERVERADDRESSBOOK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumComputers();
	BOOL EnumServers();
	BOOL EnumDevices();

	VOID ShowServers();
	VOID ShowServerInfo();
	VOID ShowDeviceInfo();

	CServerProfileInfo *FindServerProfile() CONST;

	BOOL CanAddServer() CONST;
	BOOL CanRemoveServer() CONST;
	BOOL CanRemoveAllServers() CONST;
	BOOL CanAddServerNumber() CONST;
	BOOL CanRemoveServerNumber() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerAddressBookDialog)
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
	//{{AFX_MSG(CServerAddressBookDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComputer();
	afx_msg void OnSelchangeServer();
	afx_msg void OnEditchangeComputer();
	afx_msg void OnEditchangeServer();
	afx_msg void OnConnectComputer();
	afx_msg void OnAddServer();
	afx_msg void OnRemoveServer();
	afx_msg void OnRemoveAllServers();
	afx_msg void OnAccessByVPN();
	afx_msg void OnAccessByPhone();
	afx_msg void OnAddNumber();
	afx_msg void OnRemoveNumber();
	afx_msg void OnBehaviorCallback();
	afx_msg void OnBehaviorTryAllNumbers();
	afx_msg void OnBehaviorModemSpeaker();
	afx_msg void OnBehaviorSoftwareCompression();
	afx_msg void OnSelchangeDevice();
	afx_msg void OnSelchangeNumber();
	afx_msg void OnEditchangeNumber();
	afx_msg void OnEditchangeCallbackNumber();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookPersonalNotes window

class CUserAddressBookPersonalNotes : public CEdit
{
	DECLARE_DYNCREATE(CUserAddressBookPersonalNotes)

	// Construction
public:

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookPersonalNotes)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CUserAddressBookPersonalNotes)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookPersonalPage dialog

#define IDC_USERADDRESSBOOK_PERSONALPAGE_DETAILS   1001
#define IDC_USERADDRESSBOOK_PERSONALPAGE_NAME_STATIC   1002
#define IDC_USERADDRESSBOOK_PERSONALPAGE_NAME   1003
#define IDC_USERADDRESSBOOK_PERSONALPAGE_FIRSTNAME_STATIC   1004
#define IDC_USERADDRESSBOOK_PERSONALPAGE_FIRSTNAME   1005
#define IDC_USERADDRESSBOOK_PERSONALPAGE_ALIAS_STATIC   1006
#define IDC_USERADDRESSBOOK_PERSONALPAGE_ALIAS   1007
#define IDC_USERADDRESSBOOK_PERSONALPAGE_PROFESSION_STATIC   1008
#define IDC_USERADDRESSBOOK_PERSONALPAGE_PROFESSION   1009
#define IDC_USERADDRESSBOOK_PERSONALPAGE_NOTES_STATIC   1010
#define IDC_USERADDRESSBOOK_PERSONALPAGE_NOTES   1011

class CUserAddressBookPersonalPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CUserAddressBookPersonalPage)

	// Construction
public:
	CUserAddressBookPersonalPage();

	// Attributes
private:
	CUserProfileInfo  m_cProfileInfo[2];
private:
	CUserAddressBookPersonalNotes  m_wndNotes;

	// Dialog Data
	//{{AFX_DATA(CUserAddressBookPersonalPage)
	enum { IDD = IDD_USERADDRESSBOOK_PERSONALPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, BOOL bUpdate);
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, CONST CUserProfileInfo *pBackupProfileInfo, BOOL bAccess, BOOL bUpdate);
	VOID GetInfo(CUserProfileInfo *pProfileInfo) CONST;

	class CUserAddressBookFolder *GetParent() CONST;

private:
	VOID ShowUserInfo();

	CString GetUserName() CONST;
	CString GetUserFirstName() CONST;
	CString GetUserAlias() CONST;
	CString GetUserProfession() CONST;
	CString GetUserNotes() CONST;

	VOID AdjustToPrivileges(BOOL bAccess);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookPersonalPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUserAddressBookPersonalPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeUserName();
	afx_msg void OnEditchangeUserFirstName();
	afx_msg void OnEditchangeUserAlias();
	afx_msg void OnEditchangeUserProfession();
	afx_msg void OnEditchangeUserNotes();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookOfficePage dialog

#define IDC_USERADDRESSBOOK_OFFICEPAGE_DETAILS   1001
#define IDC_USERADDRESSBOOK_OFFICEPAGE_COMPANY_STATIC   1002
#define IDC_USERADDRESSBOOK_OFFICEPAGE_COMPANY   1003
#define IDC_USERADDRESSBOOK_OFFICEPAGE_STREET_STATIC   1004
#define IDC_USERADDRESSBOOK_OFFICEPAGE_STREET   1005
#define IDC_USERADDRESSBOOK_OFFICEPAGE_CITY_STATIC   1006
#define IDC_USERADDRESSBOOK_OFFICEPAGE_CITY   1007
#define IDC_USERADDRESSBOOK_OFFICEPAGE_ZIPCODE_STATIC   1008
#define IDC_USERADDRESSBOOK_OFFICEPAGE_ZIPCODE   1009
#define IDC_USERADDRESSBOOK_OFFICEPAGE_COUNTRY_STATIC   1010
#define IDC_USERADDRESSBOOK_OFFICEPAGE_COUNTRY  1011
#define IDC_USERADDRESSBOOK_OFFICEPAGE_DEPARTMENT_STATIC  1012
#define IDC_USERADDRESSBOOK_OFFICEPAGE_DEPARTMENT   1013
#define IDC_USERADDRESSBOOK_OFFICEPAGE_COMPUTER_STATIC   1014
#define IDC_USERADDRESSBOOK_OFFICEPAGE_COMPUTER   1015
#define IDC_USERADDRESSBOOK_OFFICEPAGE_PRINTPROFILE_STATIC   1016
#define IDC_USERADDRESSBOOK_OFFICEPAGE_PRINTPROFILE   1017
#define IDC_USERADDRESSBOOK_OFFICEPAGE_PHONE_STATIC   1018
#define IDC_USERADDRESSBOOK_OFFICEPAGE_PHONE   1019
#define IDC_USERADDRESSBOOK_OFFICEPAGE_PAGER_STATIC   1020
#define IDC_USERADDRESSBOOK_OFFICEPAGE_PAGER   1021
#define IDC_USERADDRESSBOOK_OFFICEPAGE_FAX_STATIC   1022
#define IDC_USERADDRESSBOOK_OFFICEPAGE_FAX   1023
#define IDC_USERADDRESSBOOK_OFFICEPAGE_EMAIL_STATIC   1024
#define IDC_USERADDRESSBOOK_OFFICEPAGE_EMAIL   1025

class CUserAddressBookOfficePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CUserAddressBookOfficePage)

	// Construction
public:
	CUserAddressBookOfficePage();

	// Attributes
private:
	CUserProfileInfo  m_cProfileInfo[2];

	// Dialog Data
	//{{AFX_DATA(CUserAddressBookOfficePage)
	enum { IDD = IDD_USERADDRESSBOOK_OFFICEPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, BOOL bUpdate);
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, CONST CUserProfileInfo *pBackupProfileInfo, BOOL bAccess, BOOL bUpdate);
	VOID GetInfo(CUserProfileInfo *pProfileInfo) CONST;

	class CUserAddressBookFolder *GetParent() CONST;

private:
	INT EnumComputers();
	INT EnumPrintProfiles();

	VOID ShowUserInfo();

	CString GetOfficeCompanyName() CONST;
	CString GetOfficeCompanyStreet() CONST;
	CString GetOfficeCompanyCity() CONST;
	CString GetOfficeCompanyZipCode() CONST;
	CString GetOfficeCompanyCountry() CONST;
	CString GetOfficeCompanyDepartment() CONST;
	CString GetOfficeComputer() CONST;
	CString GetOfficePrintProfile() CONST;
	CString GetOfficePhone() CONST;
	CString GetOfficePager() CONST;
	CString GetOfficeFAX() CONST;
	CString GetOfficeEMail() CONST;

	VOID AdjustToPrivileges(BOOL bAccess);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookOfficePage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUserAddressBookOfficePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeOfficeCompanyName();
	afx_msg void OnEditchangeOfficeCompanyStreet();
	afx_msg void OnEditchangeOfficeCompanyCity();
	afx_msg void OnEditchangeOfficeCompanyZipCode();
	afx_msg void OnEditchangeOfficeCompanyCountry();
	afx_msg void OnEditchangeOfficeCompanyDepartment();
	afx_msg void OnEditchangeOfficeComputer();
	afx_msg void OnEditchangeOfficePrintProfile();
	afx_msg void OnEditchangeOfficePhone();
	afx_msg void OnEditchangeOfficePager();
	afx_msg void OnEditchangeOfficeFAX();
	afx_msg void OnEditchangeOfficeEMail();
	afx_msg void OnSelchangeOfficeComputer();
	afx_msg void OnSelchangeOfficePrintProfile();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookMissionPage dialog

#define IDC_USERADDRESSBOOK_MISSIONPAGE_DETAILS   1001
#define IDC_USERADDRESSBOOK_MISSIONPAGE_COMPANY_STATIC   1002
#define IDC_USERADDRESSBOOK_MISSIONPAGE_COMPANY   1003
#define IDC_USERADDRESSBOOK_MISSIONPAGE_STREET_STATIC   1004
#define IDC_USERADDRESSBOOK_MISSIONPAGE_STREET   1005
#define IDC_USERADDRESSBOOK_MISSIONPAGE_CITY_STATIC   1006
#define IDC_USERADDRESSBOOK_MISSIONPAGE_CITY   1007
#define IDC_USERADDRESSBOOK_MISSIONPAGE_ZIPCODE_STATIC   1008
#define IDC_USERADDRESSBOOK_MISSIONPAGE_ZIPCODE   1009
#define IDC_USERADDRESSBOOK_MISSIONPAGE_COUNTRY_STATIC   1010
#define IDC_USERADDRESSBOOK_MISSIONPAGE_COUNTRY  1011
#define IDC_USERADDRESSBOOK_MISSIONPAGE_DEPARTMENT_STATIC  1012
#define IDC_USERADDRESSBOOK_MISSIONPAGE_DEPARTMENT   1013
#define IDC_USERADDRESSBOOK_MISSIONPAGE_COMPUTER_STATIC   1014
#define IDC_USERADDRESSBOOK_MISSIONPAGE_COMPUTER   1015
#define IDC_USERADDRESSBOOK_MISSIONPAGE_PRINTPROFILE_STATIC   1016
#define IDC_USERADDRESSBOOK_MISSIONPAGE_PRINTPROFILE   1017
#define IDC_USERADDRESSBOOK_MISSIONPAGE_PHONE_STATIC   1018
#define IDC_USERADDRESSBOOK_MISSIONPAGE_PHONE   1019
#define IDC_USERADDRESSBOOK_MISSIONPAGE_MOBILE_STATIC   1020
#define IDC_USERADDRESSBOOK_MISSIONPAGE_MOBILE   1021
#define IDC_USERADDRESSBOOK_MISSIONPAGE_FAX_STATIC   1022
#define IDC_USERADDRESSBOOK_MISSIONPAGE_FAX   1023
#define IDC_USERADDRESSBOOK_MISSIONPAGE_EMAIL_STATIC   1024
#define IDC_USERADDRESSBOOK_MISSIONPAGE_EMAIL   1025

class CUserAddressBookMissionPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CUserAddressBookMissionPage)

	// Construction
public:
	CUserAddressBookMissionPage();

	// Attributes
private:
	CUserProfileInfo  m_cProfileInfo[2];

	// Dialog Data
	//{{AFX_DATA(CUserAddressBookMissionPage)
	enum { IDD = IDD_USERADDRESSBOOK_MISSIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, BOOL bUpdate);
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, CONST CUserProfileInfo *pBackupProfileInfo, BOOL bAccess, BOOL bUpdate);
	VOID GetInfo(CUserProfileInfo *pProfileInfo) CONST;

	class CUserAddressBookFolder *GetParent() CONST;

private:
	INT EnumComputers();
	INT EnumPrintProfiles();

	VOID ShowUserInfo();

	CString GetMissionCompanyName() CONST;
	CString GetMissionCompanyStreet() CONST;
	CString GetMissionCompanyCity() CONST;
	CString GetMissionCompanyZipCode() CONST;
	CString GetMissionCompanyCountry() CONST;
	CString GetMissionCompanyDepartment() CONST;
	CString GetMissionComputer() CONST;
	CString GetMissionPrintProfile() CONST;
	CString GetMissionPhone() CONST;
	CString GetMissionMobile() CONST;
	CString GetMissionFAX() CONST;
	CString GetMissionEMail() CONST;

	VOID AdjustToPrivileges(BOOL bAccess);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookMissionPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUserAddressBookMissionPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeMissionCompanyName();
	afx_msg void OnEditchangeMissionCompanyStreet();
	afx_msg void OnEditchangeMissionCompanyCity();
	afx_msg void OnEditchangeMissionCompanyZipCode();
	afx_msg void OnEditchangeMissionCompanyCountry();
	afx_msg void OnEditchangeMissionCompanyDepartment();
	afx_msg void OnEditchangeMissionComputer();
	afx_msg void OnEditchangeMissionPrintProfile();
	afx_msg void OnEditchangeMissionPhone();
	afx_msg void OnEditchangeMissionMobile();
	afx_msg void OnEditchangeMissionFAX();
	afx_msg void OnEditchangeMissionEMail();
	afx_msg void OnSelchangeMissionComputer();
	afx_msg void OnSelchangeMissionPrintProfile();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookHomePage dialog

#define IDC_USERADDRESSBOOK_HOMEPAGE_DETAILS   1001
#define IDC_USERADDRESSBOOK_HOMEPAGE_FAMILYNAME_STATIC   1002
#define IDC_USERADDRESSBOOK_HOMEPAGE_FAMILYNAME   1003
#define IDC_USERADDRESSBOOK_HOMEPAGE_STREET_STATIC   1004
#define IDC_USERADDRESSBOOK_HOMEPAGE_STREET   1005
#define IDC_USERADDRESSBOOK_HOMEPAGE_CITY_STATIC   1006
#define IDC_USERADDRESSBOOK_HOMEPAGE_CITY   1007
#define IDC_USERADDRESSBOOK_HOMEPAGE_ZIPCODE_STATIC   1008
#define IDC_USERADDRESSBOOK_HOMEPAGE_ZIPCODE   1009
#define IDC_USERADDRESSBOOK_HOMEPAGE_COUNTRY_STATIC   1010
#define IDC_USERADDRESSBOOK_HOMEPAGE_COUNTRY  1011
#define IDC_USERADDRESSBOOK_HOMEPAGE_COMPUTER_STATIC   1012
#define IDC_USERADDRESSBOOK_HOMEPAGE_COMPUTER   1013
#define IDC_USERADDRESSBOOK_HOMEPAGE_PRINTPROFILE_STATIC   1014
#define IDC_USERADDRESSBOOK_HOMEPAGE_PRINTPROFILE   1015
#define IDC_USERADDRESSBOOK_HOMEPAGE_PHONE_STATIC   1016
#define IDC_USERADDRESSBOOK_HOMEPAGE_PHONE   1017
#define IDC_USERADDRESSBOOK_HOMEPAGE_FAX_STATIC   1018
#define IDC_USERADDRESSBOOK_HOMEPAGE_FAX   1019
#define IDC_USERADDRESSBOOK_HOMEPAGE_EMAIL_STATIC   1020
#define IDC_USERADDRESSBOOK_HOMEPAGE_EMAIL   1021

class CUserAddressBookHomePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CUserAddressBookHomePage)

	// Construction
public:
	CUserAddressBookHomePage();

	// Attributes
private:
	CUserProfileInfo  m_cProfileInfo[2];

	// Dialog Data
	//{{AFX_DATA(CUserAddressBookHomePage)
	enum { IDD = IDD_USERADDRESSBOOK_HOMEPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, BOOL bUpdate);
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, CONST CUserProfileInfo *pBackupProfileInfo, BOOL bAccess, BOOL bUpdate);
	VOID GetInfo(CUserProfileInfo *pProfileInfo) CONST;

	class CUserAddressBookFolder *GetParent() CONST;

private:
	INT EnumComputers();
	INT EnumPrintProfiles();

	VOID ShowUserInfo();

	CString GetHomeFamilyName() CONST;
	CString GetHomeStreet() CONST;
	CString GetHomeCity() CONST;
	CString GetHomeZipCode() CONST;
	CString GetHomeCountry() CONST;
	CString GetHomeComputer() CONST;
	CString GetHomePrintProfile() CONST;
	CString GetHomePhone() CONST;
	CString GetHomeFAX() CONST;
	CString GetHomeEMail() CONST;

	VOID AdjustToPrivileges(BOOL bAccess);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookHomePage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUserAddressBookHomePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeHomeFamilyName();
	afx_msg void OnEditchangeHomeStreet();
	afx_msg void OnEditchangeHomeCity();
	afx_msg void OnEditchangeHomeZipCode();
	afx_msg void OnEditchangeHomeCountry();
	afx_msg void OnEditchangeHomeComputer();
	afx_msg void OnEditchangeHomePrintProfile();
	afx_msg void OnEditchangeHomePhone();
	afx_msg void OnEditchangeHomeFAX();
	afx_msg void OnEditchangeHomeEMail();
	afx_msg void OnSelchangeHomeComputer();
	afx_msg void OnSelchangeHomePrintProfile();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookHolidayPage dialog

#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_DETAILS   1001
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_HOTEL_STATIC   1002
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_HOTEL   1003
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_STREET_STATIC   1004
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_STREET   1005
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_CITY_STATIC   1006
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_CITY   1007
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_ZIPCODE_STATIC   1008
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_ZIPCODE   1009
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_COUNTRY_STATIC   1010
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_COUNTRY  1011
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_APARTMENT_STATIC  1012
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_APARTMENT   1013
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_COMPUTER_STATIC   1014
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_COMPUTER   1015
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_PRINTPROFILE_STATIC   1016
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_PRINTPROFILE   1017
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_PHONE_STATIC   1018
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_PHONE   1019
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_FAX_STATIC   1020
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_FAX   1021
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_EMAIL_STATIC   1022
#define IDC_USERADDRESSBOOK_HOLIDAYPAGE_EMAIL   1023

class CUserAddressBookHolidayPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CUserAddressBookHolidayPage)

	// Construction
public:
	CUserAddressBookHolidayPage();

	// Attributes
private:
	CUserProfileInfo  m_cProfileInfo[2];

	// Dialog Data
	//{{AFX_DATA(CUserAddressBookHolidayPage)
	enum { IDD = IDD_USERADDRESSBOOK_HOLIDAYPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, BOOL bUpdate);
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, CONST CUserProfileInfo *pBackupProfileInfo, BOOL bAccess, BOOL bUpdate);
	VOID GetInfo(CUserProfileInfo *pProfileInfo) CONST;

	class CUserAddressBookFolder *GetParent() CONST;

private:
	INT EnumComputers();
	INT EnumPrintProfiles();

	VOID ShowUserInfo();

	CString GetHolidayHotelName() CONST;
	CString GetHolidayHotelStreet() CONST;
	CString GetHolidayHotelCity() CONST;
	CString GetHolidayHotelZipCode() CONST;
	CString GetHolidayHotelCountry() CONST;
	CString GetHolidayHotelApartment() CONST;
	CString GetHolidayComputer() CONST;
	CString GetHolidayPrintProfile() CONST;
	CString GetHolidayPhone() CONST;
	CString GetHolidayFAX() CONST;
	CString GetHolidayEMail() CONST;

	VOID AdjustToPrivileges(BOOL bAccess);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookHolidayPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUserAddressBookHolidayPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEditchangeHolidayHotelName();
	afx_msg void OnEditchangeHolidayHotelStreet();
	afx_msg void OnEditchangeHolidayHotelCity();
	afx_msg void OnEditchangeHolidayHotelZipCode();
	afx_msg void OnEditchangeHolidayHotelCountry();
	afx_msg void OnEditchangeHolidayHotelApartment();
	afx_msg void OnEditchangeHolidayComputer();
	afx_msg void OnEditchangeHolidayPrintProfile();
	afx_msg void OnEditchangeHolidayPhone();
	afx_msg void OnEditchangeHolidayFAX();
	afx_msg void OnEditchangeHolidayEMail();
	afx_msg void OnSelchangeHolidayComputer();
	afx_msg void OnSelchangeHolidayPrintProfile();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookPlannerPage dialog

#define IDC_USERADDRESSBOOK_PLANNERPAGE_DETAILS   1001
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS   1002
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_STARTTIME_STATIC   1003
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_STARTTIME   1004
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_STOPTIME_STATIC   1005
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_STOPTIME   1006
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_DAYS   1007
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_MONDAY   1008
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_TUESDAY   1009
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_WEDNESDAY   1010
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_THURSDAY   1011
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_FRIDAY   1012
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_SATURDAY   1013
#define IDC_USERADDRESSBOOK_PLANNERPAGE_OFFICEHOURS_SUNDAY   1014
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOMEHOURS   1015
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOMEHOURS_STARTTIME_STATIC   1016
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOMEHOURS_STARTTIME   1017
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOMEHOURS_STOPTIME_STATIC   1018
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOMEHOURS_STOPTIME   1019
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOMEHOURS_DAYS   1020
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOMEHOURS_WEEKDAYS   1021
#define IDC_USERADDRESSBOOK_PLANNERPAGE_MISSION   1022
#define IDC_USERADDRESSBOOK_PLANNERPAGE_MISSION_LEAVEDAY_STATIC  1023
#define IDC_USERADDRESSBOOK_PLANNERPAGE_MISSION_LEAVEDAY   1024
#define IDC_USERADDRESSBOOK_PLANNERPAGE_MISSION_RETURNDAY_STATIC   1025
#define IDC_USERADDRESSBOOK_PLANNERPAGE_MISSION_RETURNDAY   1026
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOLIDAY   1027
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOLIDAY_LEAVEDAY_STATIC   1028
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOLIDAY_LEAVEDAY   1029
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOLIDAY_RETURNDAY_STATIC   1030
#define IDC_USERADDRESSBOOK_PLANNERPAGE_HOLIDAY_RETURNDAY   1031

class CUserAddressBookPlannerPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CUserAddressBookPlannerPage)

	// Construction
public:
	CUserAddressBookPlannerPage();

	// Attributes
private:
	CUserProfileInfo  m_cProfileInfo[2];

	// Dialog Data
	//{{AFX_DATA(CUserAddressBookPlannerPage)
	enum { IDD = IDD_USERADDRESSBOOK_PLANNERPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, BOOL bUpdate);
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, CONST CUserProfileInfo *pBackupProfileInfo, BOOL bAccess, BOOL bUpdate);
	VOID GetInfo(CUserProfileInfo *pProfileInfo) CONST;

	class CUserAddressBookFolder *GetParent() CONST;

private:
	VOID ShowUserInfo();

	BOOL GetOfficeHours(UINT &nDays, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST;
	BOOL GetHomeHours(CTimeSpan &tStartTime, CTimeSpan &tStopTime, BOOL &bDays) CONST;
	BOOL GetMissionInfo(CTimeKey &tLeaveTime, CTimeKey &tReturnTime) CONST;
	BOOL GetHolidayInfo(CTimeKey &tLeaveTime, CTimeKey &tReturnTime) CONST;

	VOID AdjustToPrivileges(BOOL bAccess);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookPlannerPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUserAddressBookPlannerPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnHomeHours();
	afx_msg void OnMission();
	afx_msg void OnHoliday();
	afx_msg void OnChangeOfficeHoursInfo();
	afx_msg void OnChangeHomeHoursInfo();
	afx_msg void OnSpinchangeMissionLeaveDate();
	afx_msg void OnSpinchangeMissionReturnDate();
	afx_msg void OnSpinchangeHolidayLeaveDate();
	afx_msg void OnSpinchangeHolidayReturnDate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookFolderTabCtrl window

class CUserAddressBookFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CUserAddressBookFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CUserAddressBookFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CUserAddressBookFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookFolder

class CUserAddressBookFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CUserAddressBookFolder)

	// Construction
public:
	CUserAddressBookFolder();

	// Attributes
private:
	CUserAddressBookFolderTabCtrl  m_wndTabCtrl;
	CUserAddressBookPersonalPage  m_pagePersonal;
	CUserAddressBookMissionPage  m_pageMission;
	CUserAddressBookHolidayPage  m_pageHoliday;
	CUserAddressBookPlannerPage  m_pagePlanner;
	CUserAddressBookOfficePage  m_pageOffice;
	CUserAddressBookHomePage  m_pageHome;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, BOOL bUpdate = TRUE);
	VOID SetInfo(CONST CUserProfileInfo *pProfileInfo, CONST CUserProfileInfo *pBackupProfileInfo, BOOL bAccess, BOOL bUpdate = TRUE);
	VOID GetInfo(CUserProfileInfo *pProfileInfo) CONST;

	class CUserAddressBookDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookFolder)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	virtual BOOL Check(BOOL bModified, BOOL bChecked) CONST;
protected:
	virtual VOID RepositionButtons();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CUserAddressBookFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookDialog dialog

#define IDC_USERADDRESSBOOK_DETAILS   1001
#define IDC_USERADDRESSBOOK_COMPUTER_STATIC   1002
#define IDC_USERADDRESSBOOK_COMPUTER   1003
#define IDC_USERADDRESSBOOK_CONNECT   1004
#define IDC_USERADDRESSBOOK_CONTENTS   1005
#define IDC_USERADDRESSBOOK_USERS   1006
#define IDC_USERADDRESSBOOK_ADDUSER   1007
#define IDC_USERADDRESSBOOK_MODIFYUSER   1008
#define IDC_USERADDRESSBOOK_REMOVEUSER   1009
#define IDC_USERADDRESSBOOK_CLEARUSER   1010
#define IDC_USERADDRESSBOOK_IMPORTUSERS   1011
#define IDC_USERADDRESSBOOK_FOLDER   1012
#define IDC_USERADDRESSBOOK_HELP   1013

class CUserAddressBookDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CUserAddressBookDialog)

	// Construction
public:
	CUserAddressBookDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szComputer;
	CStringArray  m_szComputers;
	CUserProfiles  m_pAddressBook[3];
	CPtrArray  m_pAddressBooks[3];
private:
	CStringArray  m_szColumns;
private:
	CUserAddressBookFolder  *m_pwndFolderCtrl;
private:
	UINT  m_nLocked;

	// Dialog Data
	//{{AFX_DATA(CUserAddressBookDialog)
	enum { IDD = IDD_USERADDRESSBOOK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumComputers();
	BOOL EnumUsers();

	VOID ShowUsers();

	VOID SetUserInfo(BOOL bInitialize = FALSE);
	VOID UpdateUserInfo(CONST CUserProfileInfo *pProfileInfo, BOOL bInitialize);
	BOOL GetUserInfo(CUserProfileInfo *pProfileInfo) CONST;
	CUserProfileInfo *FindUserInfo() CONST;

	CRect CalcFolderSize() CONST;

	VOID AdjustToPrivileges();

	VOID Lock();
	BOOL IsLocked() CONST;
	VOID Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	virtual BOOL Check(BOOL bModified, BOOL bChecked) CONST;
	virtual VOID Update(BOOL bModified, BOOL bChecked) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserAddressBookDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComputer();
	afx_msg void OnEditchangeComputer();
	afx_msg void OnConnectComputer();
	afx_msg void OnAddUser();
	afx_msg void OnModifyUser();
	afx_msg void OnRemoveUser();
	afx_msg void OnClearUser();
	afx_msg void OnImportUsers();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressBookImportDialog dialog

#define IDC_USERADDRESSBOOKIMPORT_DETAILS   1001
#define IDC_USERADDRESSBOOKIMPORT_COMPUTER_STATIC   1002
#define IDC_USERADDRESSBOOKIMPORT_COMPUTER   1003
#define IDC_USERADDRESSBOOKIMPORT_CONNECT   1004
#define IDC_USERADDRESSBOOKIMPORT_CONTENTS_STATIC   1005
#define IDC_USERADDRESSBOOKIMPORT_CONTENTS   1006
#define IDC_USERADDRESSBOOKIMPORT_HELP   1007

class CUserAddressBookImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CUserAddressBookImportDialog)

	// Construction
public:
	CUserAddressBookImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CUserProfiles  m_pUsers;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CUserAddressBookImportDialog)
	enum { IDD = IDD_USERADDRESSBOOKIMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumComputers();
	VOID EnumUsers();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressBookImportDialog)
public:
	virtual INT DoModal(CUserProfiles &pUsers);
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
	//{{AFX_MSG(CUserAddressBookImportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnConnectComputer();
	afx_msg void OnSelchangeComputer();
	afx_msg void OnEditchangeComputer();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAddressesDialog dialog

#define IDC_USERADDRESSES_DETAILS   1001
#define IDC_USERADDRESSES_USERS_STATIC   1002
#define IDC_USERADDRESSES_USERS   1003
#define IDC_USERADDRESSES_HELP   1004

class CUserAddressesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CUserAddressesDialog)

	// Construction
public:
	CUserAddressesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CUserProfiles  m_pUserAddresses;
	CUserProfiles  m_pUsers;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CUserAddressesDialog)
	enum { IDD = IDD_USERADDRESSES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumUsers();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserAddressesDialog)
public:
	virtual INT DoModal(CUserProfiles &pUsers);
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
	//{{AFX_MSG(CUserAddressesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPServiceDialog dialog

#define IDC_PFLP_SERVICE_DETAILS   1001
#define IDC_PFLP_SERVICE_DEVICE_STATIC   1002
#define IDC_PFLP_SERVICE_DEVICE   1003
#define IDC_PFLP_SERVICE_DEVICE_CONFIGURATION   1004
#define IDC_PFLP_SERVICE_AVAILABILITY   1005
#define IDC_PFLP_SERVICE_AVAILABILITY_UNLIMITED   1006
#define IDC_PFLP_SERVICE_AVAILABILITY_DAILY   1007
#define IDC_PFLP_SERVICE_AVAILABILITY_STARTTIME   1008
#define IDC_PFLP_SERVICE_AVAILABILITY_DAILY_STATIC   1009
#define IDC_PFLP_SERVICE_AVAILABILITY_STOPTIME   1010
#define IDC_PFLP_SERVICE_AVAILABILITY_DISABLED   1011
#define IDC_PFLP_SERVICE_AVAILABILITY_WORKINGDAYS   1012
#define IDC_PFLP_SERVICE_AVAILABILITY_AUDIT   1013
#define IDC_PFLP_SERVICE_HELP   1014

// Specify the PFLP service dialog related settings
#define PFLPSERVICE_DEFAULTSTARTTIME   HOURS(8)
#define PFLPSERVICE_DEFAULTSTOPTIME   HOURS(17)
#define PFLPSERVICE_DEFAULTACCESSPERIOD   SECONDSPERHOUR

class CPFLPServiceDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CPFLPServiceDialog)

	// Construction
public:
	CPFLPServiceDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	UINT  m_nCode[2];
	CTimeSpan  m_tStartTime[2];
	CTimeSpan  m_tStopTime[2];
	CPFLPServiceDevices  m_pDevices[2];

	// Dialog Data
	//{{AFX_DATA(CPFLPServiceDialog)
	enum { IDD = IDD_PFLP_SERVICE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumServiceDevices();

	VOID ShowServiceDetails();

	CPFLPServiceDevice *FindActiveDevice() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPFLPServiceDialog)
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
	//{{AFX_MSG(CPFLPServiceDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDeviceConfiguration();
	afx_msg void OnUnlimitedAvailability();
	afx_msg void OnDailyAvailability();
	afx_msg void OnDisabledAvailability();
	afx_msg void OnWorkingDaysAvailability();
	afx_msg void OnAuditAvailability();
	afx_msg void OnSelchangeDevice();
	afx_msg void OnSpinchangeDailyStartTime();
	afx_msg void OnSpinchangeDailyStopTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPFLPClientsDialog dialog

#define IDC_PFLP_CLIENTS_DETAILS   1001
#define IDC_PFLP_CLIENTS_NAMES_STATIC   1002
#define IDC_PFLP_CLIENTS_NAMES   1003
#define IDC_PFLP_CLIENTS_CLOSE   1004
#define IDC_PFLP_CLIENTS_CLOSEALL   1005
#define IDC_PFLP_CLIENTS_HELP   1006

class CPFLPClientsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CPFLPClientsDialog)

	// Construction
public:
	CPFLPClientsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CStringArray  m_szClients;
	CPFLPConnections  m_pConnections;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CPFLPClientsDialog)
	enum { IDD = IDD_PFLP_CLIENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumConnections();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPFLPClientsDialog)
public:
	virtual BOOL Initialize();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPFLPClientsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnCloseAll();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPServiceDialog dialog

#define IDC_TPEP_SERVICE_DETAILS   1001
#define IDC_TPEP_SERVICE_PORT_STATIC   1002
#define IDC_TPEP_SERVICE_PORT   1003
#define IDC_TPEP_SERVICE_TIMEOUT_STATIC   1004
#define IDC_TPEP_SERVICE_TIMEOUT   1005
#define IDC_TPEP_SERVICE_TIMEOUT_SECONDS   1006
#define IDC_TPEP_SERVICE_BUFFERSIZE_STATIC   1007
#define IDC_TPEP_SERVICE_BUFFERSIZE   1008
#define IDC_TPEP_SERVICE_BUFFERSIZE_KB   1009
#define IDC_TPEP_SERVICE_CHARSET   1010
#define IDC_TPEP_SERVICE_CHARSET_ASCII   1011
#define IDC_TPEP_SERVICE_CHARSET_UNICODE   1012
#define IDC_TPEP_SERVICE_CHARSET_DEFAULT   1013
#define IDC_TPEP_SERVICE_AVAILABILITY   1014
#define IDC_TPEP_SERVICE_AVAILABILITY_UNLIMITED   1015
#define IDC_TPEP_SERVICE_AVAILABILITY_DAILY   1016
#define IDC_TPEP_SERVICE_AVAILABILITY_STARTTIME   1017
#define IDC_TPEP_SERVICE_AVAILABILITY_DAILY_STATIC   1018
#define IDC_TPEP_SERVICE_AVAILABILITY_STOPTIME   1019
#define IDC_TPEP_SERVICE_AVAILABILITY_DISABLED   1020
#define IDC_TPEP_SERVICE_AVAILABILITY_WORKINGDAYS   1021
#define IDC_TPEP_SERVICE_AVAILABILITY_AUDIT   1022
#define IDC_TPEP_SERVICE_SECURITY   1023
#define IDC_TPEP_SERVICE_SECURITY_CLIENTS_STATIC   1024
#define IDC_TPEP_SERVICE_SECURITY_CLIENTS   1025
#define IDC_TPEP_SERVICE_SECURITY_ADDCLIENTS   1026
#define IDC_TPEP_SERVICE_SECURITY_REMOVECLIENTS   1027
#define IDC_TPEP_SERVICE_SECURITY_RESTRICTIONS_STATIC   1028
#define IDC_TPEP_SERVICE_SECURITY_RESTRICTIONS_NONE   1029
#define IDC_TPEP_SERVICE_SECURITY_RESTRICTIONS_FULL   1030
#define IDC_TPEP_SERVICE_SECURITY_RESTRICTIONS_PARTIAL   1031
#define IDC_TPEP_SERVICE_SECURITY_RESTRICTIONS_STARTTIME   1032
#define IDC_TPEP_SERVICE_SECURITY_RESTRICTIONS_PARTIAL_STATIC   1033
#define IDC_TPEP_SERVICE_SECURITY_RESTRICTIONS_STOPTIME   1034
#define IDC_TPEP_SERVICE_SECURITY_RESTRICTIONS_AUDIT   1035
#define IDC_TPEP_SERVICE_HELP   1036

// Specify the TPEP service dialog related settings
#define TPEPSERVICE_DEFAULTSTARTTIME   HOURS(8)
#define TPEPSERVICE_DEFAULTSTOPTIME   HOURS(17)
#define TPEPSERVICE_DEFAULTACCESSPERIOD   SECONDSPERHOUR

class CTPEPServiceDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTPEPServiceDialog)

	// Construction
public:
	CTPEPServiceDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	UINT  m_nCode[2];
	UINT  m_nPort[2];
	UINT  m_nCharset[2];
	UINT  m_nBufferSize[2];
	CTimeSpan  m_tTimeout[2];
	CTimeSpan  m_tStartTime[2];
	CTimeSpan  m_tStopTime[2];
	CUIntArray  m_nAccessCodes[2];
	CStringArray  m_szClients[2];
	CTimeKeyArray  m_tStartTimes[2];
	CTimeKeyArray  m_tStopTimes[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTPEPServiceDialog)
	enum { IDD = IDD_TPEP_SERVICE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID ShowServiceDetails();
	VOID ShowClientProperties(INT nIndex = 0);

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPServiceDialog)
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
	//{{AFX_MSG(CTPEPServiceDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCharsetASCII();
	afx_msg void OnCharsetUnicode();
	afx_msg void OnCharsetDefault();
	afx_msg void OnUnlimitedAvailability();
	afx_msg void OnDailyAvailability();
	afx_msg void OnDisabledAvailability();
	afx_msg void OnWorkingDaysAvailability();
	afx_msg void OnAuditAvailability();
	afx_msg void OnAddClients();
	afx_msg void OnRemoveClients();
	afx_msg void OnNoAccessRestrictions();
	afx_msg void OnFullAccessRestrictions();
	afx_msg void OnPartialAccessRestrictions();
	afx_msg void OnAuditRestrictions();
	afx_msg void OnSpinchangeProtocolPort();
	afx_msg void OnSpinchangeProtocolBufferSize();
	afx_msg void OnSpinchangeProtocolTimeout();
	afx_msg void OnSpinchangeDailyStartTime();
	afx_msg void OnSpinchangeDailyStopTime();
	afx_msg void OnSpinchangeAccessStartTime();
	afx_msg void OnSpinchangeAccessStopTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPConnectDialog dialog

#define IDC_TPEP_CONNECT_DETAILS   1001
#define IDC_TPEP_CONNECT_SERVER_STATIC   1002
#define IDC_TPEP_CONNECT_SERVER   1003
#define IDC_TPEP_CONNECT_VIEW   1004
#define IDC_TPEP_CONNECT_PROPERTIES   1005
#define IDC_TPEP_CONNECT_PROPERTIES_CONTENTS_STATIC   1006
#define IDC_TPEP_CONNECT_PROPERTIES_CONTENTS_PACKETS   1007
#define IDC_TPEP_CONNECT_PROPERTIES_CONTENTS_PARAMETERS   1008
#define IDC_TPEP_CONNECT_PROPERTIES_CONTENTS   1009
#define IDC_TPEP_CONNECT_PROPERTIES_CONTENTS_ADD   1010
#define IDC_TPEP_CONNECT_PROPERTIES_CONTENTS_REMOVE   1011
#define IDC_TPEP_CONNECT_PROPERTIES_CONTENTS_REMOVEALL   1012
#define IDC_TPEP_CONNECT_PROPERTIES_LINKTYPE_STATIC   1013
#define IDC_TPEP_CONNECT_PROPERTIES_LINKTYPE_HOT   1014
#define IDC_TPEP_CONNECT_PROPERTIES_LINKTYPE_COLD   1015
#define IDC_TPEP_CONNECT_PROPERTIES_DATATYPE_STATIC   1016
#define IDC_TPEP_CONNECT_PROPERTIES_DATATYPE_RAW   1017
#define IDC_TPEP_CONNECT_PROPERTIES_DATATYPE_PIE   1018
#define IDC_TPEP_CONNECT_PROPERTIES_DATATYPE_PIE_NUMBER   1019
#define IDC_TPEP_CONNECT_PROPERTIES_TRIGGERMODE_STATIC   1020
#define IDC_TPEP_CONNECT_PROPERTIES_TRIGGERMODE_UPDATE   1021
#define IDC_TPEP_CONNECT_PROPERTIES_TRIGGERMODE_CHANGE   1022
#define IDC_TPEP_CONNECT_PROPERTIES_DATAMODE_STATIC   1023
#define IDC_TPEP_CONNECT_PROPERTIES_DATAMODE_REALTIME   1024
#define IDC_TPEP_CONNECT_PROPERTIES_DATAMODE_RANDOM   1025
#define IDC_TPEP_CONNECT_PROPERTIES_DATAMODE_HISTORICAL   1026
#define IDC_TPEP_CONNECT_PROPERTIES_DATAMODE_STARTTIME   1027
#define IDC_TPEP_CONNECT_PROPERTIES_DATAMODE_HISTORICAL_STATIC   1028
#define IDC_TPEP_CONNECT_PROPERTIES_DATAMODE_STOPTIME   1029
#define IDC_TPEP_CONNECT_PROPERTIES_DATAMODE_SPEED_STATIC   1030
#define IDC_TPEP_CONNECT_PROPERTIES_DATAMODE_SPEED   1031
#define IDC_TPEP_CONNECT_HELP   1032

// Specify the TPEP connect dialog related settings
#define TPEPCONNECT_MINIMUMSAMPLES   1
#define TPEPCONNECT_MAXIMUMSAMPLES   1000
#define TPEPCONNECT_DEFAULTSAMPLES   1
#define TPEPCONNECT_DEFAULTRETRIEVALPERIOD   SECONDSPERHOUR

class CTPEPConnectDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTPEPConnectDialog)

	// Construction
public:
	CTPEPConnectDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTPEPConnectDialog)
	enum { IDD = IDD_TPEP_CONNECT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumServers();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPConnectDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTPEPConnectDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPackets();
	afx_msg void OnParameters();
	afx_msg void OnAddContents();
	afx_msg void OnRemoveContents();
	afx_msg void OnRemoveAllContents();
	afx_msg void OnHotLinkType();
	afx_msg void OnColdLinkType();
	afx_msg void OnRawDataType();
	afx_msg void OnPIEDataType();
	afx_msg void OnUpdateTriggerMode();
	afx_msg void OnChangeTriggerMode();
	afx_msg void OnRealtimeDataMode();
	afx_msg void OnRandomDataMode();
	afx_msg void OnHistoricalDataMode();
	afx_msg void OnSpinchangeRetrieveStartTime();
	afx_msg void OnSpinchangeRetrieveStopTime();
	afx_msg void OnEditchangeServer();
	afx_msg void OnSelchangeServer();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPClientsDialog dialog

#define IDC_TPEP_CLIENTS_DETAILS   1001
#define IDC_TPEP_CLIENTS_NAMES_STATIC   1002
#define IDC_TPEP_CLIENTS_NAMES   1003
#define IDC_TPEP_CLIENTS_CLOSE   1004
#define IDC_TPEP_CLIENTS_CLOSEALL   1005
#define IDC_TPEP_CLIENTS_PROPERTIES   1006
#define IDC_TPEP_CLIENTS_PROPERTIES_CONTENTS_STATIC   1007
#define IDC_TPEP_CLIENTS_PROPERTIES_CONTENTS_PACKETS   1008
#define IDC_TPEP_CLIENTS_PROPERTIES_CONTENTS_PARAMETERS   1009
#define IDC_TPEP_CLIENTS_PROPERTIES_CONTENTS   1010
#define IDC_TPEP_CLIENTS_PROPERTIES_LINKTYPE_STATIC   1011
#define IDC_TPEP_CLIENTS_PROPERTIES_LINKTYPE_HOT   1012
#define IDC_TPEP_CLIENTS_PROPERTIES_LINKTYPE_COLD   1013
#define IDC_TPEP_CLIENTS_PROPERTIES_DATATYPE_STATIC   1014
#define IDC_TPEP_CLIENTS_PROPERTIES_DATATYPE_RAW   1015
#define IDC_TPEP_CLIENTS_PROPERTIES_DATATYPE_PIE   1016
#define IDC_TPEP_CLIENTS_PROPERTIES_DATATYPE_PIE_NUMBER   1017
#define IDC_TPEP_CLIENTS_PROPERTIES_TRIGGERMODE_STATIC   1018
#define IDC_TPEP_CLIENTS_PROPERTIES_TRIGGERMODE_UPDATE   1019
#define IDC_TPEP_CLIENTS_PROPERTIES_TRIGGERMODE_CHANGE   1020
#define IDC_TPEP_CLIENTS_PROPERTIES_DATAMODE_STATIC   1021
#define IDC_TPEP_CLIENTS_PROPERTIES_DATAMODE_REALTIME   1022
#define IDC_TPEP_CLIENTS_PROPERTIES_DATAMODE_RANDOM   1023
#define IDC_TPEP_CLIENTS_PROPERTIES_DATAMODE_HISTORICAL   1024
#define IDC_TPEP_CLIENTS_PROPERTIES_DATAMODE_STARTTIME_STATIC   1025
#define IDC_TPEP_CLIENTS_PROPERTIES_DATAMODE_STARTTIME   1026
#define IDC_TPEP_CLIENTS_PROPERTIES_DATAMODE_STOPTIME_STATIC   1027
#define IDC_TPEP_CLIENTS_PROPERTIES_DATAMODE_STOPTIME   1028
#define IDC_TPEP_CLIENTS_PROPERTIES_DATAMODE_SPEED_STATIC   1029
#define IDC_TPEP_CLIENTS_PROPERTIES_DATAMODE_SPEED   1030
#define IDC_TPEP_CLIENTS_HELP   1031

class CTPEPClientsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTPEPClientsDialog)

	// Construction
public:
	CTPEPClientsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CStringArray  m_szServers[2];
	CStringArray  m_szClients[2];
	CTPEPConnections  m_pConnections[2][2];
private:
	CStringArray  m_szColumns[2];

	// Dialog Data
	//{{AFX_DATA(CTPEPClientsDialog)
	enum { IDD = IDD_TPEP_CLIENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumConnections();

	VOID ShowConnectionInfo(INT nIndex = 0);

	INT CalcColumnExtent(LPCTSTR pszColumn);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPClientsDialog)
public:
	virtual BOOL Initialize();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTPEPClientsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnCloseAll();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPClientAddressesDialog dialog

#define IDC_TPEP_CLIENTADDRESSES_DETAILS   1001
#define IDC_TPEP_CLIENTADDRESSES_NAME_STATIC   1002
#define IDC_TPEP_CLIENTADDRESSES_NAME   1003
#define IDC_TPEP_CLIENTADDRESSES_ADDRESS_STATIC   1004
#define IDC_TPEP_CLIENTADDRESSES_ADDRESS   1005
#define IDC_TPEP_CLIENTADDRESSES_ADDRESSSYNTAX_STATIC   1006
#define IDC_TPEP_CLIENTADDRESSES_ADDADDRESS   1007
#define IDC_TPEP_CLIENTADDRESSES_REMOVEADDRESS   1008
#define IDC_TPEP_CLIENTADDRESSES_ADDRESSLIST   1009
#define IDC_TPEP_CLIENTADDRESSES_HELP   1010

class CTPEPClientAddressesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTPEPClientAddressesDialog)

	// Construction
public:
	CTPEPClientAddressesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CStringArray  m_szAddresses;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTPEPClientAddressesDialog)
	enum { IDD = IDD_TPEP_CLIENTADDRESSES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumComputers();

	BOOL CheckName(LPCTSTR pszName) CONST;
	BOOL CheckAddress(LPCTSTR pszAddress, BOOL bSyntax = FALSE) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPClientAddressesDialog)
public:
	virtual INT DoModal(CStringArray &szAddresses);
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
	//{{AFX_MSG(CTPEPClientAddressesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeAddress();
	afx_msg void OnSelchangeName();
	afx_msg void OnAddAddress();
	afx_msg void OnRemoveAddress();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPPacketsListDialog dialog

#define IDC_TPEP_PACKETSLIST_DETAILS   1001
#define IDC_TPEP_PACKETSLIST_NAME_STATIC   1002
#define IDC_TPEP_PACKETSLIST_NAME   1003
#define IDC_TPEP_PACKETSLIST_ADD   1004
#define IDC_TPEP_PACKETSLIST_REMOVE   1005
#define IDC_TPEP_PACKETSLIST_PROFILES   1006
#define IDC_TPEP_PACKETSLIST_PROFILES_NAME_STATIC   1007
#define IDC_TPEP_PACKETSLIST_PROFILES_NAME   1008
#define IDC_TPEP_PACKETSLIST_PROFILES_SAVE   1009
#define IDC_TPEP_PACKETSLIST_PROFILES_MODIFY   1010
#define IDC_TPEP_PACKETSLIST_PROFILES_DELETE   1011
#define IDC_TPEP_PACKETSLIST_MEMBERS   1012
#define IDC_TPEP_PACKETSLIST_HELP   1013

class CTPEPPacketsListDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTPEPPacketsListDialog)

	// Construction
public:
	CTPEPPacketsListDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CStringArray  m_szPacketIDs;
	CStringArray  m_szPacketDescriptions;
	CTPEPDataProfiles  m_pPacketProfiles[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTPEPPacketsListDialog)
	enum { IDD = IDD_TPEP_PACKETSLIST_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumPackets();
	BOOL EnumProfiles();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPPacketsListDialog)
public:
	virtual INT DoModal(CStringArray &szPacketIDs, CStringArray &szPacketDescriptions);
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
	//{{AFX_MSG(CTPEPPacketsListDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddPacket();
	afx_msg void OnRemovePacket();
	afx_msg void OnSaveProfile();
	afx_msg void OnModifyProfile();
	afx_msg void OnDeleteProfile();
	afx_msg void OnEditchangeProfile();
	afx_msg void OnSelchangePacket();
	afx_msg void OnSelchangeProfile();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersListDialog dialog

#define IDC_TPEP_PARAMETERSLIST_DETAILS   1001
#define IDC_TPEP_PARAMETERSLIST_NAME_STATIC   1002
#define IDC_TPEP_PARAMETERSLIST_NAME   1003
#define IDC_TPEP_PARAMETERSLIST_ADD   1004
#define IDC_TPEP_PARAMETERSLIST_REMOVE   1005
#define IDC_TPEP_PARAMETERSLIST_PROFILES   1006
#define IDC_TPEP_PARAMETERSLIST_PROFILES_NAME_STATIC   1007
#define IDC_TPEP_PARAMETERSLIST_PROFILES_NAME   1008
#define IDC_TPEP_PARAMETERSLIST_PROFILES_SAVE   1009
#define IDC_TPEP_PARAMETERSLIST_PROFILES_MODIFY   1010
#define IDC_TPEP_PARAMETERSLIST_PROFILES_DELETE   1011
#define IDC_TPEP_PARAMETERSLIST_MEMBERS   1012
#define IDC_TPEP_PARAMETERSLIST_HELP   1013

class CTPEPParametersListDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTPEPParametersListDialog)

	// Construction
public:
	CTPEPParametersListDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CStringArray  m_szParameterIDs;
	CStringArray  m_szParameterDescriptions;
	CTPEPDataProfiles  m_pParameterProfiles[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTPEPParametersListDialog)
	enum { IDD = IDD_TPEP_PARAMETERSLIST_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumParameters();
	BOOL EnumProfiles();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPEPParametersListDialog)
public:
	virtual INT DoModal(CStringArray &szParameterIDs, CStringArray &szParameterDescriptions);
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
	//{{AFX_MSG(CTPEPParametersListDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddParameter();
	afx_msg void OnRemoveParameter();
	afx_msg void OnSaveProfile();
	afx_msg void OnModifyProfile();
	afx_msg void OnDeleteProfile();
	afx_msg void OnEditchangeProfile();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeProfile();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadsFilesPage dialog

#define IDC_TOOLSDOWNLOADS_FILESPAGE_DETAILS   1001
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FILES_STATIC   1002
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FILES   1003
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FILES_BROWSE   1004
#define IDC_TOOLSDOWNLOADS_FILESPAGE_DIRECTORY_STATIC   1005
#define IDC_TOOLSDOWNLOADS_FILESPAGE_DIRECTORY   1006
#define IDC_TOOLSDOWNLOADS_FILESPAGE_DIRECTORY_BROWSE   1007
#define IDC_TOOLSDOWNLOADS_FILESPAGE_TRANSFER_STATIC   1008
#define IDC_TOOLSDOWNLOADS_FILESPAGE_TRANSFER_ASCII   1009
#define IDC_TOOLSDOWNLOADS_FILESPAGE_TRANSFER_BINARY   1010
#define IDC_TOOLSDOWNLOADS_FILESPAGE_DELETEFILES   1011
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FTP_LOCATION_STATIC   1012
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FTP_LOCATION   1013
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FTP_USERNAME_STATIC   1014
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FTP_USERNAME   1015
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FTP_PASSWORD_STATIC   1016
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FTP_PASSWORD   1017
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FTP_PORT   1018
#define IDC_TOOLSDOWNLOADS_FILESPAGE_FTP_PORT_NUMBER   1019

// Specify the tools downloads files related settings
#define TOOLSDOWNLOADSFILES_FIRSTPORT   1024
#define TOOLSDOWNLOADSFILES_LASTPORT   65535
#define TOOLSDOWNLOADSFILES_DEFAULTPORT   1024

class CToolsDownloadsFilesPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CToolsDownloadsFilesPage)

	// Construction
public:
	CToolsDownloadsFilesPage();

	// Attributes
private:
	CToolsDownloadProfileInfo  m_cInfo[2];

	// Dialog Data
	//{{AFX_DATA(CToolsDownloadsFilesPage)
	enum { IDD = IDD_TOOLSDOWNLOADS_FILESPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CToolsDownloadProfileInfo *pProfileInfo, CONST CToolsDownloadProfileInfo *pBackupProfileInfo = NULL, BOOL bUpdate = TRUE);
	VOID GetInfo(CToolsDownloadProfileInfo *pProfileInfo) CONST;

	class CToolsDownloadsPageFolder *GetParent() CONST;

private:
	VOID ShowFilesInfo();

	BOOL CheckFTPLocation() CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CToolsDownloadsFilesPage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CToolsDownloadsFilesPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseFiles();
	afx_msg void OnBrowseDirectory();
	afx_msg void OnTransferASCIIMode();
	afx_msg void OnTransferBinaryMode();
	afx_msg void OnDeleteFiles();
	afx_msg void OnUseFTPPort();
	afx_msg void OnEditchangeFiles();
	afx_msg void OnEditchangeDirectory();
	afx_msg void OnEditchangeFTPLocation();
	afx_msg void OnEditchangeFTPUserName();
	afx_msg void OnEditchangeFTPPassword();
	afx_msg void OnSpinchangeFTPPort();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadsSchedulePage dialog

#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_DETAILS   1001
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_STATIC   1002
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_IMMEDIATELY   1003
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_ONCE   1004
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_ONCE_TIME   1005
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_DAILY   1006
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_DAILY_TIME   1007
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_PERIODICALLY   1008
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_PERIODICALLY_STARTTIME   1009
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_PERIODICALLY_INTERVAL_STATIC   1010
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_PERIODICALLY_INTERVAL   1011
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_PERIODICALLY_INTERVAL_MINUTES_STATIC   1012
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_PERIODICALLY_STOPTIME_STATIC   1013
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_PERIODICALLY_STOPTIME   1014
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_EVENT   1015
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_EVENT_NAME   1016
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_EVENT_DELAY_STATIC   1017
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_EVENT_DELAY   1018
#define IDC_TOOLSDOWNLOADS_SCHEDULEPAGE_RUN_EVENT_DELAY_MINUTES_STATIC   1019

// Specify the tools downloads schedule related settings
#define TOOLSDOWNLOADSSCHEDULE_MINIMUMINTERVAL   1
#define TOOLSDOWNLOADSSCHEDULE_MAXIMUMINTERVAL   (365*MINUTESPERDAY)
#define TOOLSDOWNLOADSSCHEDULE_DEFAULTINTERVAL   MINUTESPERHOUR
#define TOOLSDOWNLOADSSCHEDULE_MINIMUMDELAY   0
#define TOOLSDOWNLOADSSCHEDULE_MAXIMUMDELAY   (365*MINUTESPERDAY)
#define TOOLSDOWNLOADSSCHEDULE_DEFAULTDELAY   0

class CToolsDownloadsSchedulePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CToolsDownloadsSchedulePage)

	// Construction
public:
	CToolsDownloadsSchedulePage();

	// Attributes
private:
	CToolsDownloadProfileInfo  m_cInfo[2];

	// Dialog Data
	//{{AFX_DATA(CToolsDownloadsSchedulePage)
	enum { IDD = IDD_TOOLSDOWNLOADS_SCHEDULEPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID SetInfo(CONST CToolsDownloadProfileInfo *pProfileInfo, CONST CToolsDownloadProfileInfo *pBackupProfileInfo, BOOL bUpdate = TRUE);
	VOID GetInfo(CToolsDownloadProfileInfo *pProfileInfo) CONST;

	class CToolsDownloadsPageFolder *GetParent() CONST;

private:
	BOOL EnumEvents();

	VOID ShowScheduleInfo();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CToolsDownloadsSchedulePage)
public:
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CToolsDownloadsSchedulePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnExecutionNow();
	afx_msg void OnExecutionAtTime();
	afx_msg void OnExecutionAtDailyTime();
	afx_msg void OnExecutionAtPeriodicalTime();
	afx_msg void OnExecutionAtEvent();
	afx_msg void OnSelchangeExecutionEvent();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg void OnSpinchangeExecutionDailyTime();
	afx_msg void OnSpinchangeExecutionPeriodicalStartTime();
	afx_msg void OnSpinchangeExecutionPeriodicalStopTime();
	afx_msg void OnSpinchangeExecutionPeriodicalInterval();
	afx_msg void OnSpinchangeExecutionDelay();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadsPageTabCtrl window

class CToolsDownloadsPageTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CToolsDownloadsPageTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CToolsDownloadsPageFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolsDownloadsPageTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolsDownloadsPageTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadsPageFolder

class CToolsDownloadsPageFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNAMIC(CToolsDownloadsPageFolder)

	// Construction
public:
	CToolsDownloadsPageFolder();

	// Attributes
private:
	CToolsDownloadsPageTabCtrl  m_wndTabCtrl;
	CToolsDownloadsFilesPage  m_pageFiles;
	CToolsDownloadsSchedulePage  m_pageSchedule;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID SetInfo(CONST CToolsDownloadProfileInfo *pProfileInfo, BOOL bUpdate = TRUE);
	VOID SetInfo(CONST CToolsDownloadProfileInfo *pProfileInfo, CONST CToolsDownloadProfileInfo *pBackupProfileInfo);
	VOID GetInfo(CToolsDownloadProfileInfo *pProfileInfo) CONST;

	class CToolsDownloadsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolsDownloadsPageFolder)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	virtual BOOL Check(BOOL bModified, BOOL bChecked) CONST;
protected:
	virtual VOID RepositionButtons();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolsDownloadsPageFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsDownloadsDialog

#define IDC_TOOLSDOWNLOADS_DETAILS   1001
#define IDC_TOOLSDOWNLOADS_PROFILE_STATIC  1002
#define IDC_TOOLSDOWNLOADS_PROFILE   1003
#define IDC_TOOLSDOWNLOADS_SAVE   1004
#define IDC_TOOLSDOWNLOADS_DELETE   1005
#define IDC_TOOLSDOWNLOADS_DELETEALL   1006
#define IDC_TOOLSDOWNLOADS_AUDITION   1007
#define IDC_TOOLSDOWNLOADS_DISABLED   1008
#define IDC_TOOLSDOWNLOADS_PROPERTIES   1009
#define IDC_TOOLSDOWNLOADS_FOLDER   1010
#define IDC_TOOLSDOWNLOADS_HELP   1011

class CToolsDownloadsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CToolsDownloadsDialog)

	// Construction
public:
	CToolsDownloadsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CToolsDownloadProfiles  m_pProfiles[3];
private:
	CToolsDownloadsPageFolder  *m_pwndFolderCtrl;
private:
	UINT  m_nLocked;

	// Dialog Data
	//{{AFX_DATA(CToolsDownloadsDialog)
	enum { IDD = IDD_TOOLSDOWNLOADS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetDownloadProfiles(CONST CToolsDownloadProfiles &pProfiles);
	BOOL GetDownloadProfiles(CToolsDownloadProfiles &pProfiles) CONST;

private:
	BOOL EnumDownloadProfiles();

	VOID SetDownloadProfileInfo(BOOL bInitialize = FALSE);
	VOID UpdateDownloadProfileInfo(CONST CToolsDownloadProfileInfo *pProfileInfo, BOOL bInitialize);
	BOOL GetDownloadProfileInfo(CToolsDownloadProfileInfo *pProfileInfo) CONST;
	CToolsDownloadProfileInfo *FindDownloadProfileInfo() CONST;

	CRect CalcFolderSize() CONST;

	VOID AdjustToPrivileges();

	VOID Lock();
	BOOL IsLocked() CONST;
	VOID Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolsDownloadsDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	virtual BOOL Check(BOOL bModified, BOOL bChecked) CONST;
	virtual VOID Update(BOOL bModified, BOOL bChecked) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	//{{AFX_MSG(CToolsDownloadsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSave();
	afx_msg void OnDelete();
	afx_msg void OnDeleteAll();
	afx_msg void OnDisabled();
	afx_msg void OnAudition();
	afx_msg void OnEditchangeProfile();
	afx_msg void OnSelchangeProfile();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsDatabasePage dialog

#define IDC_TOOLSOPTIONS_DATABASEPAGE_DETAILS   1001
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_STATIC   1002
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_DONOTHING   1003
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_INFORMBYEVENT   1004
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_UPDATEIMMEDIATELY   1005
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_UPDATEATTIME   1006
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_UPDATEATTIME_STARTTIME   1007
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_UPDATEATTIME_STARTTIME_STATIC   1008
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_UPDATEATTIME_STOPTIME   1009
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_UPDATEATTIME_STOPTIME_STATIC   1010
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_SEPARATOR   1011
#define IDC_TOOLSOPTIONS_DATABASEPAGE_ACTION_RELOADNOW   1012

// Specify the tools options datatabse related settings
#define TOOLOPTIONSDATABASE_UPDATE_STARTTIME   HOURS(17)
#define TOOLOPTIONSDATABASE_UPDATE_STOPTIME   HOURS(8)

class CToolsOptionsDatabasePage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CToolsOptionsDatabasePage)

	// Construction
public:
	CToolsOptionsDatabasePage();

	// Attributes
private:
	UINT  m_nOption;
	CTimeKey  m_tStartTime;
	CTimeKey  m_tStopTime;

	// Dialog Data
	//{{AFX_DATA(CToolsOptionsDatabasePage)
	enum { IDD = IDD_TOOLSOPTIONS_DATABASEPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	class CToolsOptionsDialog *GetParent() CONST;

private:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CToolsOptionsDatabasePage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
	virtual VOID Update();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CToolsOptionsDatabasePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDoNothing();
	afx_msg void OnInformByEvent();
	afx_msg void OnUpdateImmediately();
	afx_msg void OnUpdateAtTime();
	afx_msg void OnReloadNow();
	afx_msg void OnSpinchangeStartTime();
	afx_msg void OnSpinchangeStopTime();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsSatelliteTrackingPage dialog

#define IDC_TOOLSOPTIONS_SATELLITETRACKINGPAGE_DETAILS   1001
#define IDC_TOOLSOPTIONS_SATELLITETRACKINGPAGE_CONFIGURATIONFILENAME_STATIC   1002
#define IDC_TOOLSOPTIONS_SATELLITETRACKINGPAGE_CONFIGURATIONFILENAME   1003
#define IDC_TOOLSOPTIONS_SATELLITETRACKINGPAGE_CONFIGURATIONFILENAME_BROWSE   1004
#define IDC_TOOLSOPTIONS_SATELLITETRACKINGPAGE_HELPFILENAME_STATIC   1005
#define IDC_TOOLSOPTIONS_SATELLITETRACKINGPAGE_HELPFILENAME   1006
#define IDC_TOOLSOPTIONS_SATELLITETRACKINGPAGE_HELPFILENAME_BROWSE   1007
#define IDC_TOOLSOPTIONS_SATELLITETRACKINGPAGE_ENABLED   1008

class CToolsOptionsSatelliteTrackingPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CToolsOptionsSatelliteTrackingPage)

	// Construction
public:
	CToolsOptionsSatelliteTrackingPage();

	// Attributes
private:
	CString  m_szConfigurationFileName;
	CString  m_szHelpFileName;
	BOOL  m_bEnabled;

	// Dialog Data
	//{{AFX_DATA(CToolsOptionsSatelliteTrackingPage)
	enum { IDD = IDD_TOOLSOPTIONS_SATELLITETRACKINGPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	class CToolsOptionsDialog *GetParent() CONST;

private:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CToolsOptionsSatelliteTrackingPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
	virtual VOID Update();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CToolsOptionsSatelliteTrackingPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnEnable();
	afx_msg void OnBrowseConfigurationFileName();
	afx_msg void OnBrowseHelpFileName();
	afx_msg void OnEditchangeConfigurationFileName();
	afx_msg void OnEditchangeHelpFileName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsEMailPage dialog

#define IDC_TOOLSOPTIONS_EMAILPAGE_DETAILS   1001
#define IDC_TOOLSOPTIONS_EMAILPAGE_SERVER_STATIC   1002
#define IDC_TOOLSOPTIONS_EMAILPAGE_SERVER   1003
#define IDC_TOOLSOPTIONS_EMAILPAGE_TYPE_STATIC   1004
#define IDC_TOOLSOPTIONS_EMAILPAGE_TYPE_PLAINTEXT   1005
#define IDC_TOOLSOPTIONS_EMAILPAGE_TYPE_SSLTLS   1006
#define IDC_TOOLSOPTIONS_EMAILPAGE_TYPE_STARTTLS   1007
#define IDC_TOOLSOPTIONS_EMAILPAGE_TYPE_AUTOSTARTTLS   1008
#define IDC_TOOLSOPTIONS_EMAILPAGE_PORT_STATIC   1009
#define IDC_TOOLSOPTIONS_EMAILPAGE_PORT   1010
#define IDC_TOOLSOPTIONS_EMAILPAGE_ADVANCED   1011
#define IDC_TOOLSOPTIONS_EMAILPAGE_ACCOUNT   1012
#define IDC_TOOLSOPTIONS_EMAILPAGE_ACCOUNT_NAME_STATIC   1013
#define IDC_TOOLSOPTIONS_EMAILPAGE_ACCOUNT_NAME   1014
#define IDC_TOOLSOPTIONS_EMAILPAGE_ACCOUNT_ADDRESS_STATIC   1015
#define IDC_TOOLSOPTIONS_EMAILPAGE_ACCOUNT_ADDRESS   1016
#define IDC_TOOLSOPTIONS_EMAILPAGE_LOGINNAME_STATIC   1017
#define IDC_TOOLSOPTIONS_EMAILPAGE_LOGINNAME   1018
#define IDC_TOOLSOPTIONS_EMAILPAGE_LOGINPASSWORD_STATIC   1019
#define IDC_TOOLSOPTIONS_EMAILPAGE_LOGINPASSWORD   1020

// Specify the tools options e-mail related settings
#define TOOLOPTIONSEMAIL_MINIMUMPORT   EMAILCONFIGURATION_MINIMUMPORT
#define TOOLOPTIONSEMAIL_MAXIMUMPORT   EMAILCONFIGURATION_MAXIMUMPORT
#define TOOLOPTIONSEMAIL_DEFAULTPORT   EMAILCONFIGURATION_DEFAULTPORT

class CToolsOptionsEMailPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CToolsOptionsEMailPage)

	// Construction
public:
	CToolsOptionsEMailPage();

	// Attributes
private:
	CString  m_szServer;
	CString  m_szAccountName;
	CString  m_szAccountAddress;
	CString  m_szAccountLogin;
	CString  m_szAccountPassword;
	CString  m_szCharsetEncoding[2];
	CString  m_szConnectBoundIP[2];
	CSMTPConnection::ConnectionType  m_nType;
	CSMTPConnection::AuthenticationMethod  m_nAuthentication[2];
	CSMTPConnection::SSLProtocol  m_nSSLProtocol[2];
	CSMTPMessage::PRIORITY  m_nPriority[2];
	UINT  m_nOptions[2];
	UINT  m_nPort;

	// Dialog Data
	//{{AFX_DATA(CToolsOptionsEMailPage)
	enum { IDD = IDD_TOOLSOPTIONS_EMAILPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	class CToolsOptionsDialog *GetParent() CONST;

private:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CToolsOptionsEMailPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
	virtual VOID Update();
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CToolsOptionsEMailPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTypePlainText();
	afx_msg void OnTypeSSLTLS();
	afx_msg void OnTypeSTARTTLS();
	afx_msg void OnTypeAutoSTARTTLS();
	afx_msg void OnAdvancedSettings();
	afx_msg void OnEditchangeServer();
	afx_msg void OnEditchangeAccountName();
	afx_msg void OnEditchangeAccountAddress();
	afx_msg void OnEditchangeAccountLoginName();
	afx_msg void OnEditchangeAccountLoginPassword();
	afx_msg void OnSpinchangePort();
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
private:
	CToolsOptionsTabCtrl  m_wndTabCtrl;
	CToolsOptionsDatabasePage  m_pageDatabase;
	CToolsOptionsSatelliteTrackingPage  m_pageSatelliteTracking;
	CToolsOptionsEMailPage  m_pageEMail;

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolsOptionsDialog)
public:
	virtual BOOL CheckPageAccessibility(INT nIndex) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolsOptionsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayPagesDialog dialog

#define IDC_DISPLAYPAGES_LIST_STATIC   1001
#define IDC_DISPLAYPAGES_LIST   1002
#define IDC_DISPLAYPAGES_HELP   1003

class CDisplayPagesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CDisplayPagesDialog)

	// Construction
public:
	CDisplayPagesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
public:

	// Operations
public:

	// Dialog Data
	//{{AFX_DATA(CDisplayPagesDialog)
	enum { IDD = IDD_DISPLAYPAGES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayPagesDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDisplayPagesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelectDisplayPage();
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
private:
	INT  m_nIndex;

	// Operations
public:

	// Dialog Data
	//{{AFX_DATA(CDisplayWindowsDialog)
	enum { IDD = IDD_DISPLAYWINDOWS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayWindowsDialog)
public:
	virtual INT DoModal(INT nIndex);
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

	// Operations
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
