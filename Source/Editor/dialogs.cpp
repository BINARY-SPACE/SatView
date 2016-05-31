// DIALOGS.CPP : Dialogs Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the dialogs related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/02/18 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CWelcomeDialog dialog

IMPLEMENT_DYNCREATE(CWelcomeDialog, CLocaleDialog)

CWelcomeDialog::CWelcomeDialog(CWnd *pParentWnd) : CLocaleDialog(CWelcomeDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CWelcomeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CWelcomeDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_WELCOME_SPACECRAFTNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_WELCOME_PASSWORD)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CWelcomeDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWelcomeDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CWelcomeDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_WELCOME_HELP, OnHelp)
	ON_EN_CHANGE(IDC_WELCOME_SPACECRAFTNAME, OnEditchangeSpacecraftName)
	ON_EN_CHANGE(IDC_WELCOME_PASSWORD, OnEditchangePassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcomeDialog message handlers

BOOL CWelcomeDialog::OnInitDialog()
{
	CString  szText;
	CString  szTitle;
	CString  szFormat[2];
	CVersionInfo  cVersionInfo;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	for (SetForegroundWindow(), GetWindowText(szFormat[0]), GetDlgItem(IDC_WELCOME_TEXT)->GetWindowText(szFormat[1]); !szFormat[0].IsEmpty() && !szFormat[1].IsEmpty(); )
	{
		szTitle.Format(szFormat[0], (LPCTSTR)cVersionInfo.QueryProductName());
		szText.Format(szFormat[1], (LPCTSTR)cVersionInfo.QueryProductName());
		GetDlgItem(IDC_WELCOME_TEXT)->SetWindowText(szText);
		SetWindowText(szTitle);
		break;
	}
	GetDlgItem(IDC_WELCOME_SETUP)->EnableWindow();
	GetDlgItem(IDC_WELCOME_TEXT)->EnableWindow();
	GetDlgItem(IDC_WELCOME_COMMENT)->EnableWindow();
	GetDlgItem(IDC_WELCOME_USERNAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_WELCOME_USERNAME)->EnableWindow();
	GetDlgItem(IDC_WELCOME_SPACECRAFTNAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_WELCOME_SPACECRAFTNAME)->EnableWindow();
	GetDlgItem(IDC_WELCOME_PASSWORD_STATIC)->EnableWindow();
	GetDlgItem(IDC_WELCOME_PASSWORD)->EnableWindow();
	return TRUE;
}

void CWelcomeDialog::OnEditchangeSpacecraftName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CWelcomeDialog::OnEditchangePassword()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CWelcomeDialog::OnOK()
{
	HANDLE  hAccount;
	CString  szUserName;
	CString  szPassword;
	CString  szSpacecraft;
	CUserAccounts  cUserAccounts;
	CAccountToken  cAccountToken;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_WELCOME_USERNAME)->GetWindowText(szUserName);
	GetDlgItem(IDC_WELCOME_PASSWORD)->GetWindowText(szPassword);
	GetDlgItem(IDC_WELCOME_SPACECRAFTNAME)->GetWindowText(szSpacecraft);
	if (!LogonUser(szUserName, (LPCTSTR)NULL, szPassword, LOGON32_LOGON_NEW_CREDENTIALS, LOGON32_PROVIDER_WINNT50, &hAccount))
	{
		GetDlgItem(IDC_WELCOME_PASSWORD)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_WELCOME_PASSWORD)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow(Check());
		CAudioDevice::AlertBySound();
		return;
	}
	for (RevertToSelf(), CloseHandle(hAccount); cAccountToken.SetSpacecraftName(szSpacecraft) && cAccountToken.SetUserName(szUserName) && cAccountToken.SetPassword(szPassword); )
	{
		if (cUserAccounts.WriteAccount(&cAccountToken) && cUserAccounts.SetActiveAccount(&cAccountToken))
		{
			EndDialog(IDOK);
			return;
		}
		break;
	}
	GetDlgItem(IDC_WELCOME_PASSWORD)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_WELCOME_PASSWORD)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
	CAudioDevice::AlertBySound();
}

BOOL CWelcomeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_WELCOMEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CWelcomeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_WELCOMEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CLoginDialog dialog

IMPLEMENT_DYNCREATE(CLoginDialog, CLocaleDialog)

CLoginDialog::CLoginDialog(CWnd *pParentWnd) : CLocaleDialog(CLoginDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CLoginDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CLoginDialog::Initialize()
{
	CDatabases  cDatabases;

	cDatabases.GetDatabases(m_pDatabases, TRUE);
	return TRUE;
}

BOOL CLoginDialog::EnumServers()
{
	INT  nServer;
	INT  nServers;
	CString  szServer;
	CComputerToken  cComputerToken;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_RESETCONTENT);
	for (nServer = 0, nServers = (INT)m_pDatabases.GetSize(); nServer < nServers; nServer++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nServer)) != (CDatabaseProfileInfo *)NULL)
		{
			if (SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szServer = pDatabaseProfileInfo->GetServer())) == CB_ERR)
			{
				SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szServer);
				continue;
			}
		}
	}
	for (; SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cComputerToken.GetComputerName()) < 0; )
	{
		SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)cComputerToken.GetComputerName());
		break;
	}
	SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cComputerToken.GetComputerName()), 0));
	GetDlgItem(IDC_LOGIN_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_LOGIN_SERVERNAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_LOGIN_SERVERNAME)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CLoginDialog::EnumSpacecrafts()
{
	INT  nSpacecraft;
	INT  nSpacecrafts;
	CString  szServer;
	CString  szSpacecraft;
	CUserAccounts  cUserAccounts;
	CAccountToken  cAccountToken;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_LOGIN_SERVERNAME)->GetWindowText(szServer);
	SendDlgItemMessage(IDC_LOGIN_SPACECRAFTNAME, CB_RESETCONTENT);
	for (nSpacecraft = 0, nSpacecrafts = (!IsDlgButtonChecked(IDC_LOGIN_SPACECRAFTSUPPORT)) ? (INT)m_pDatabases.GetSize() : 0; ((!nSpacecraft && !nSpacecrafts) || nSpacecraft < nSpacecrafts) && !szServer.IsEmpty(); nSpacecraft++)
	{
		if ((pDatabaseProfileInfo = (nSpacecrafts > 0) ? m_pDatabases.GetAt(nSpacecraft) : (CDatabaseProfileInfo *)NULL) && pDatabaseProfileInfo->GetServer() == szServer)
		{
			if (SendDlgItemMessage(IDC_LOGIN_SPACECRAFTNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szSpacecraft = pDatabaseProfileInfo->GetSpacecraft())) == CB_ERR)
			{
				SendDlgItemMessage(IDC_LOGIN_SPACECRAFTNAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szSpacecraft);
				continue;
			}
		}
		if (!nSpacecrafts)
		{
			if (!IsDlgButtonChecked(IDC_LOGIN_SPACECRAFTSUPPORT))
			{
				if (cUserAccounts.GetActiveAccount(&cAccountToken))
				{
					SendDlgItemMessage(IDC_LOGIN_SPACECRAFTNAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)cAccountToken.GetSpacecraftName());
					break;
				}
			}
		}
	}
	SendDlgItemMessage(IDC_LOGIN_SPACECRAFTNAME, CB_SETCURSEL);
	CheckDlgButton(IDC_LOGIN_SPACECRAFTSUPPORT, (SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_GETCOUNT) > 0 && !SendDlgItemMessage(IDC_LOGIN_SPACECRAFTNAME, CB_GETCOUNT)) ? TRUE : FALSE);
	GetDlgItem(IDC_LOGIN_SPACECRAFTSUPPORT)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_LOGIN_SPACECRAFTNAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_SPACECRAFTNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_LOGIN_SPACECRAFTNAME)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_SPACECRAFTNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CLoginDialog::EnumDatabases()
{
	INT  nUser;
	INT  nUsers;
	INT  nDatabase;
	INT  nDatabases;
	CString  szUser;
	CString  szServer;
	CString  szDatabase;
	CString  szSpacecraft;
	CStringArray  szUsers;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_LOGIN_SERVERNAME)->GetWindowText(szServer);
	GetDlgItem(IDC_LOGIN_SPACECRAFTNAME)->GetWindowText(szSpacecraft);
	GetDlgItem(IDC_LOGIN_USERNAME)->GetWindowText(szUser);
	GetDlgItem(IDC_LOGIN_DATABASE_NAME)->GetWindowText(szDatabase);
	SendDlgItemMessage(IDC_LOGIN_DATABASE_NAME, CB_RESETCONTENT);
	for (nDatabase = 0, nDatabases = (!IsDlgButtonChecked(IDC_LOGIN_SPACECRAFTSUPPORT)) ? (INT)m_pDatabases.GetSize() : 0; nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetUsers(szUsers) > 0 && pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft  &&  pDatabaseProfileInfo->GetServer() == szServer)
		{
			for (nUser = 0, nUsers = (INT)szUsers.GetSize(); nUser < nUsers; nUser++)
			{
				if (!szUser.CompareNoCase(szUsers.GetAt(nUser)) || szUser.IsEmpty())
				{
					if (SendDlgItemMessage(IDC_LOGIN_DATABASE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pDatabaseProfileInfo->GetName()) == CB_ERR) SendDlgItemMessage(IDC_LOGIN_DATABASE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pDatabaseProfileInfo->GetName());
					break;
				}
			}
		}
	}
	SendDlgItemMessage(IDC_LOGIN_DATABASE_NAME, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_LOGIN_DATABASE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDatabase), 0));
	GetDlgItem(IDC_LOGIN_DATABASE)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_DATABASE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_LOGIN_DATABASE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_DATABASE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_LOGIN_DATABASE_NAME)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_DATABASE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_LOGIN_SERVERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CLoginDialog::EnumUsers()
{
	INT  nUser[2];
	INT  nUsers[2];
	CString  szUser[2];
	CString  szServer;
	CString  szDatabase;
	CString  szSpacecraft;
	CAccounts  cAccounts;
	CUserToken  cUserToken;
	CStringArray  szUsers;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_LOGIN_SERVERNAME)->GetWindowText(szServer);
	GetDlgItem(IDC_LOGIN_SPACECRAFTNAME)->GetWindowText(szSpacecraft);
	GetDlgItem(IDC_LOGIN_USERNAME)->GetWindowText(szUser[0]);
	GetDlgItem(IDC_LOGIN_DATABASE_NAME)->GetWindowText(szDatabase);
	SendDlgItemMessage(IDC_LOGIN_USERNAME, CB_RESETCONTENT);
	for (nUser[0] = 0, nUsers[0] = (!IsDlgButtonChecked(IDC_LOGIN_SPACECRAFTSUPPORT)) ? (INT)m_pDatabases.GetSize() : 0; ((!nUser[0] && !nUsers[0]) || nUser[0] < nUsers[0]) && !szServer.IsEmpty(); nUser[0]++)
	{
		if ((pDatabaseProfileInfo = (nUsers[0] > 0) ? m_pDatabases.GetAt(nUser[0]) : (CDatabaseProfileInfo *)NULL) && pDatabaseProfileInfo->GetUsers(szUsers) > 0 && pDatabaseProfileInfo->GetServer() == szServer  &&  pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft  &&  pDatabaseProfileInfo->GetName() == szDatabase)
		{
			for (nUser[1] = 0, nUsers[1] = (INT)szUsers.GetSize(); nUser[1] < nUsers[1]; nUser[1] = nUser[1] + 1)
			{
				if (SendDlgItemMessage(IDC_LOGIN_USERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szUser[1] = szUsers.GetAt(nUser[1]))) == CB_ERR)
				{
					SendDlgItemMessage(IDC_LOGIN_USERNAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szUser[1]);
					continue;
				}
			}
		}
		if (!nUsers[0])
		{
			for (nUser[1] = 0, nUsers[1] = cAccounts.EnumUsers(szUsers, TRUE); nUser[1] < nUsers[1]; nUser[1]++)
			{
				if (cUserToken.SetUserName(szUsers.GetAt(nUser[1])) && cUserToken.IsAdministrator(TRUE))
				{
					SendDlgItemMessage(IDC_LOGIN_USERNAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szUsers.GetAt(nUser[1]));
					continue;
				}
			}
			break;
		}
	}
	SendDlgItemMessage(IDC_LOGIN_USERNAME, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_LOGIN_USERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser[0]), 0));
	GetDlgItem(IDC_LOGIN_USERNAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_USERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_LOGIN_USERNAME)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_USERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_LOGIN_USERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CLoginDialog::ShowDatabaseInfo()
{
	INT  nUser;
	INT  nUsers;
	CString  szUser;
	CStringArray  szUsers;
	CStringArray  szPasswords;
	CUIntArray  nPrivileges;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	if ((pDatabaseProfileInfo = FindDatabaseInfo()))
	{
		GetDlgItem(IDC_LOGIN_USERNAME)->GetWindowText(szUser);
		for (nUser = 0, nUsers = (pDatabaseProfileInfo->GetUsers(szUsers, szPasswords, nPrivileges) > 0) ? (INT)szUsers.GetSize() : 0; nUser < nUsers; nUser++)
		{
			if (szUsers.GetAt(nUser) == szUser) break;
			continue;
		}
		if (nUser < nUsers)
		{
			if (szPasswords.GetAt(nUser).IsEmpty())
			{
				GetDlgItem(IDC_LOGIN_DATABASE)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_DATABASE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
				GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->EnableWindow(FALSE);
				GetDlgItem(IDOK)->EnableWindow();
				GetDlgItem(IDOK)->SetFocus();
				return;
			}
			SendDlgItemMessage(IDC_LOGIN_DATABASE_PASSWORD, EM_SETSEL, 0, -1);
			GetDlgItem(IDC_LOGIN_DATABASE)->EnableWindow();
			GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD_STATIC)->EnableWindow();
			GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->EnableWindow();
			GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->SetFocus();
			return;
		}
	}
	if (SendDlgItemMessage(IDC_LOGIN_USERNAME, CB_GETCURSEL) >= 0)
	{
		SendDlgItemMessage(IDC_LOGIN_DATABASE_PASSWORD, EM_SETSEL, 0, -1);
		GetDlgItem(IDC_LOGIN_DATABASE)->EnableWindow();
		GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD_STATIC)->EnableWindow();
		GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->EnableWindow();
		GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->SetFocus();
		return;
	}
	GetDlgItem(IDC_LOGIN_DATABASE)->EnableWindow((SendDlgItemMessage(IDC_LOGIN_DATABASE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDCANCEL)->SetFocus();
}

CDatabaseProfileInfo *CLoginDialog::FindDatabaseInfo() CONST
{
	INT  nDatabase;
	INT  nDatabases;
	CString  szName;
	CString  szServer;
	CString  szSpacecraft;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_LOGIN_SERVERNAME)->GetWindowText(szServer);
	GetDlgItem(IDC_LOGIN_DATABASE_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_LOGIN_SPACECRAFTNAME)->GetWindowText(szSpacecraft);
	for (nDatabase = 0, nDatabases = (INT)m_pDatabases.GetSize(); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetName() == szName  &&  pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft  &&  pDatabaseProfileInfo->GetServer() == szServer) break;
		continue;
	}
	return((nDatabase < nDatabases) ? m_pDatabases.GetAt(nDatabase) : (CDatabaseProfileInfo *)NULL);
}

BOOL CLoginDialog::Check(BOOL bModified) CONST
{
	CString  szPassword;

	GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->GetWindowText(szPassword);
	return !szPassword.IsEmpty();
}

void CLoginDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CLoginDialog::PostNcDestroy()
{
	m_pDatabases.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CLoginDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CLoginDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_LOGIN_SPACECRAFTSUPPORT, OnSpacecraftSupport)
	ON_BN_CLICKED(IDC_LOGIN_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_LOGIN_SERVERNAME, OnSelchangeServerName)
	ON_CBN_SELCHANGE(IDC_LOGIN_SPACECRAFTNAME, OnSelchangeSpacecraftName)
	ON_CBN_SELCHANGE(IDC_LOGIN_USERNAME, OnSelchangeUserName)
	ON_CBN_SELCHANGE(IDC_LOGIN_DATABASE_NAME, OnSelchangeDatabaseName)
	ON_EN_CHANGE(IDC_LOGIN_DATABASE_PASSWORD, OnEditchangeDatabasePassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDialog message handlers

BOOL CLoginDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	for (SetForegroundWindow(); EnumServers() && EnumSpacecrafts() && EnumDatabases() && EnumUsers(); )
	{
		ShowDatabaseInfo();
		return FALSE;
	}
	return TRUE;
}

void CLoginDialog::OnSpacecraftSupport()
{
	EnumSpacecrafts();
	EnumDatabases();
	EnumUsers();
	ShowDatabaseInfo();
}

void CLoginDialog::OnSelchangeServerName()
{
	EnumSpacecrafts();
	EnumDatabases();
	EnumUsers();
	ShowDatabaseInfo();
}

void CLoginDialog::OnSelchangeSpacecraftName()
{
	EnumDatabases();
	EnumUsers();
	ShowDatabaseInfo();
}

void CLoginDialog::OnSelchangeUserName()
{
	EnumDatabases();
	ShowDatabaseInfo();
}

void CLoginDialog::OnSelchangeDatabaseName()
{
	EnumUsers();
	ShowDatabaseInfo();
}

void CLoginDialog::OnEditchangeDatabasePassword()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CLoginDialog::OnOK()
{
	INT  nUser;
	INT  nUsers;
	HANDLE  hLogin;
	CString  szUser;
	CString  szServer;
	CString  szDatabase;
	CString  szPassword;
	CString  szSpacecraft;
	CUIntArray  nPrivileges;
	CStringArray  szUsers;
	CStringArray  szPasswords;
	CUserAccounts  cUserAccounts;
	CAccountToken  cAccountToken;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CHourglassCursor  cCursor;

	if ((pDatabaseProfileInfo = FindDatabaseInfo()))
	{
		GetDlgItem(IDC_LOGIN_SERVERNAME)->GetWindowText(szServer);
		GetDlgItem(IDC_LOGIN_SPACECRAFTNAME)->GetWindowText(szSpacecraft);
		GetDlgItem(IDC_LOGIN_USERNAME)->GetWindowText(szUser);
		GetDlgItem(IDC_LOGIN_DATABASE_NAME)->GetWindowText(szDatabase);
		GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->GetWindowText(szPassword);
		for (nUser = 0, nUsers = (pDatabaseProfileInfo->GetUsers(szUsers, szPasswords, nPrivileges) > 0) ? (INT)szUsers.GetSize() : 0; nUser < nUsers; nUser++)
		{
			if (szUsers.GetAt(nUser) == szUser  &&  szPasswords.GetAt(nUser) == szPassword) break;
			continue;
		}
		if (nUser == nUsers)
		{
			GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->SetWindowText(EMPTYSTRING);
			GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->SetFocus();
			GetDlgItem(IDOK)->EnableWindow(FALSE);
			CAudioDevice::AlertBySound();
			return;
		}
		if (cAccountToken.SetSpacecraftName(szSpacecraft) && cAccountToken.SetUserName(szUser))
		{
			if ((!cUserAccounts.FindAccount(&cAccountToken) || cUserAccounts.ReadAccount(&cAccountToken)) && cAccountToken.SetDatabase(szDatabase) && cAccountToken.SetPassword(szPassword))
			{
				for (SetAccount(&cAccountToken); SetDatabase(szServer, szSpacecraft, szDatabase) >= 0; )
				{
					EndDialog(IDOK);
					return;
				}
			}
		}
		GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_LOGIN_DATABASE_NAME)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow(FALSE);
		CAudioDevice::AlertBySound();
		return;
	}
	GetDlgItem(IDC_LOGIN_USERNAME)->GetWindowText(szUser);
	GetDlgItem(IDC_LOGIN_DATABASE_NAME)->GetWindowText(szDatabase);
	GetDlgItem(IDC_LOGIN_SPACECRAFTNAME)->GetWindowText(szSpacecraft);
	GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->GetWindowText(szPassword);
	if (!LogonUser(szUser, (LPCTSTR)NULL, szPassword, LOGON32_LOGON_NEW_CREDENTIALS, LOGON32_PROVIDER_WINNT50, &hLogin))
	{
		GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
	if ((cAccountToken.SetSpacecraftName(szSpacecraft) || IsDlgButtonChecked(IDC_LOGIN_SPACECRAFTSUPPORT)) && cAccountToken.SetUserName(szUser) && (!cUserAccounts.FindAccount(&cAccountToken) || cUserAccounts.ReadAccount(&cAccountToken)) && (cAccountToken.SetDatabase(szDatabase) || IsDlgButtonChecked(IDC_LOGIN_SPACECRAFTSUPPORT)) && cAccountToken.SetPassword(szPassword))
	{
		SetAccount(&cAccountToken);
		CloseHandle(hLogin);
		EndDialog(IDOK);
		return;
	}
	GetDlgItem(IDC_LOGIN_DATABASE_PASSWORD)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_LOGIN_DATABASE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	CAudioDevice::AlertBySound();
	CloseHandle(hLogin);
}

void CLoginDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CLoginDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_LOGINDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CLoginDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_LOGINDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CFileBrowseDialog

IMPLEMENT_DYNCREATE(CFileBrowseDialog, CFileDialog)

CFileBrowseDialog::CFileBrowseDialog(CWnd *pParentWnd, LPCTSTR pszFileName, LPCTSTR pszDefaultExtension, LPCTSTR pszFilter, DWORD dwFlags) : CFileDialog(TRUE, pszDefaultExtension, pszFileName, dwFlags, pszFilter, pParentWnd)
{
	m_ofn.lpstrTitle = STRING(IDS_FILEBROWSEDIALOG_TITLE);
	GetCurrentDirectory(sizeof(m_szDirectory) / sizeof(TCHAR), m_szDirectory);
}
CFileBrowseDialog::CFileBrowseDialog(CWnd *pParentWnd, UINT nCtrlID, LPCTSTR pszDefaultExtension, LPCTSTR pszFilter, DWORD dwFlags) : CFileDialog(TRUE, pszDefaultExtension, (LPCTSTR)NULL, dwFlags, pszFilter, pParentWnd)
{
	CWnd  *pWnd;
	CString  szFileName;

	for (m_ofn.lpstrTitle = STRING(IDS_FILEBROWSEDIALOG_TITLE), GetCurrentDirectory(sizeof(m_szDirectory) / sizeof(TCHAR), m_szDirectory); (pWnd = (IsWindow(pParentWnd->GetSafeHwnd())) ? pParentWnd->GetDlgItem(nCtrlID) : (CWnd *)NULL); )
	{
		for (pWnd->GetWindowText(szFileName); !szFileName.IsEmpty(); )
		{
			_tcscpy_s(m_szFileName, sizeof(m_szFileName) / sizeof(TCHAR), szFileName);
			break;
		}
		break;
	}
}

void CFileBrowseDialog::PostNcDestroy()
{
	SetCurrentDirectory(m_szDirectory);
	CFileDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CFileBrowseDialog, CFileDialog)
	//{{AFX_MSG_MAP(CFileBrowseDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileBrowseDialog message handlers


/////////////////////////////////////////////////////////////////////////////
// CDefaultPrinter

IMPLEMENT_DYNCREATE(CDefaultPrinter, CPrintDialog)

CDefaultPrinter::CDefaultPrinter() : CPrintDialog(TRUE)
{
	return;
}

CDefaultPrinter::~CDefaultPrinter()
{
	Reset();
}

BOOL CDefaultPrinter::Initialize()
{
	Reset();
	return GetDefaults();
}

BOOL CDefaultPrinter::IsAvailable() CONST
{
	return !GetDeviceName().IsEmpty();
}

VOID CDefaultPrinter::Reset()
{
	if (m_pd.hDevNames)
	{
		GlobalFree(m_pd.hDevNames);
		m_pd.hDevNames = (HANDLE)NULL;
	}
	if (m_pd.hDevMode)
	{
		GlobalFree(m_pd.hDevMode);
		m_pd.hDevMode = (HANDLE)NULL;
	}
}

BEGIN_MESSAGE_MAP(CDefaultPrinter, CPrintDialog)
	//{{AFX_MSG_MAP(CDefaultPrinter)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDefaultPrinter message handlers


/////////////////////////////////////////////////////////////////////////////
// CPrintPageSetupDialog

IMPLEMENT_DYNCREATE(CPrintPageSetupDialog, CPageSetupDialog)

CPrintPageSetupDialog::CPrintPageSetupDialog(CWnd *pParentWnd, DWORD dwFlags) : CPageSetupDialog(dwFlags, pParentWnd)
{
	return;
}

CPrintPageSetupDialog::~CPrintPageSetupDialog()
{
	Reset();
}

INT_PTR CPrintPageSetupDialog::DoModal()
{
	Reset();
	GetDefaultPrinterInfo(&m_psd);
	return CPageSetupDialog::DoModal();
}

VOID CPrintPageSetupDialog::Reset()
{
	if (m_psd.hDevNames)
	{
		GlobalFree(m_psd.hDevNames);
		m_psd.hDevNames = (HANDLE)NULL;
	}
	if (m_psd.hDevMode)
	{
		GlobalFree(m_psd.hDevMode);
		m_psd.hDevMode = (HANDLE)NULL;
	}
}

BEGIN_MESSAGE_MAP(CPrintPageSetupDialog, CPageSetupDialog)
	//{{AFX_MSG_MAP(CPrintPageSetupDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintPageSetupDialog message handlers

void CPrintPageSetupDialog::OnOK()
{
	CHourglassCursor  cCursor;

	SetDefaultPrinterInfo(&m_psd);
	CPageSetupDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CPrintPagePrepareDialog

IMPLEMENT_DYNCREATE(CPrintPagePrepareDialog, CPrintDialog)

CPrintPagePrepareDialog::CPrintPagePrepareDialog(CWnd *pParentWnd, DWORD dwFlags) : CPrintDialog(FALSE, dwFlags, pParentWnd)
{
	return;
}

CPrintPagePrepareDialog::~CPrintPagePrepareDialog()
{
	Reset();
}

INT_PTR CPrintPagePrepareDialog::DoModal()
{
	INT_PTR  nResult;
	PAGESETUPDLG  sPageSetup;

	for (Reset(), GetDefaultPrinterInfo(&sPageSetup), m_pd.Flags = (m_pd.Flags & ~(PD_PAGENUMS | PD_SELECTION)) | PD_ALLPAGES | PD_NOSELECTION | PD_USEDEVMODECOPIESANDCOLLATE | PD_HIDEPRINTTOFILE | PD_NOWARNING, m_pd.nFromPage = m_pd.nToPage = m_pd.nMinPage = 1, m_pd.nMaxPage = -m_pd.nMinPage, m_pd.hDevNames = sPageSetup.hDevNames, m_pd.hDevMode = sPageSetup.hDevMode; (nResult = CPrintDialog::DoModal()) == IDOK; )
	{
		sPageSetup.hDevNames = m_pd.hDevNames;
		sPageSetup.hDevMode = m_pd.hDevMode;
		SetDefaultPrinterInfo(&sPageSetup);
		break;
	}
	return nResult;
}

VOID CPrintPagePrepareDialog::Reset()
{
	if (m_pd.hDevNames)
	{
		GlobalFree(m_pd.hDevNames);
		m_pd.hDevNames = (HANDLE)NULL;
	}
	if (m_pd.hDevMode)
	{
		GlobalFree(m_pd.hDevMode);
		m_pd.hDevMode = (HANDLE)NULL;
	}
}

BEGIN_MESSAGE_MAP(CPrintPagePrepareDialog, CPrintDialog)
	//{{AFX_MSG_MAP(CPrintPagePrepareDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintPagePrepareDialog message handlers


/////////////////////////////////////////////////////////////////////////////
// CDatabaseDetailsDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseDetailsDialog, CLocaleDialog)

CDatabaseDetailsDialog::CDatabaseDetailsDialog(CWnd *pParentWnd) : CLocaleDialog(CDatabaseDetailsDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDatabaseDetailsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CDatabaseDetailsDialog::DoModal(LPCTSTR pszServer, LPCTSTR pszSpacecraft, LPCTSTR pszDatabase, LPCTSTR pszStandard, CString &szDataFileName, CString &szDataFilePath, UINT &nDataFileSize, UINT &nDataFileMaxSize, UINT &nDataFileGrowSize, CString &szLogsFileName, CString &szLogsFilePath, UINT &nLogsFileSize, UINT &nLogsFileMaxSize, UINT &nLogsFileGrowSize, BOOL &bReadOnly)
{
	INT_PTR  nResult;

	if (szDataFileName.IsEmpty() || szLogsFileName.IsEmpty())
	{
		for (m_szServer = pszServer, m_szSpacecraft = pszSpacecraft, m_szDatabase = pszDatabase, m_szStandard = pszStandard, m_szDataFileName[0][0] = ConstructDataFileName(pszDatabase), m_szDataFileName[0][1].Empty(), m_szLogsFileName[0][0] = ConstructLogsFileName(pszDatabase), m_szLogsFileName[0][1].Empty(), m_szDataFileName[1][0] = m_szDataFileName[1][1] = m_szLogsFileName[1][0] = m_szLogsFileName[1][1] = EMPTYSTRING, m_nDataFileSize[0][0] = m_nDataFileSize[0][1] = DETAILSDATABASEDIALOG_DEFAULTINITDATASIZE, m_nLogsFileSize[0][0] = m_nLogsFileSize[0][1] = DETAILSDATABASEDIALOG_DEFAULTINITLOGSSIZE, m_nDataFileSize[1][0] = m_nDataFileSize[1][1] = DETAILSDATABASEDIALOG_DEFAULTMAXDATASIZE, m_nLogsFileSize[1][0] = m_nLogsFileSize[1][1] = DETAILSDATABASEDIALOG_DEFAULTMAXLOGSSIZE, m_nDataFileSize[2][0] = m_nDataFileSize[2][1] = DETAILSDATABASEDIALOG_DEFAULTGROWDATASIZE, m_nLogsFileSize[2][0] = m_nLogsFileSize[2][1] = DETAILSDATABASEDIALOG_DEFAULTGROWLOGSSIZE, m_bReadOnly[0] = m_bReadOnly[1] = FALSE; (nResult = CLocaleDialog::DoModal()) == IDOK; )
		{
			szDataFileName = m_szDataFileName[0][0];
			szDataFilePath = m_szDataFileName[1][0];
			szLogsFileName = m_szLogsFileName[0][0];
			szLogsFilePath = m_szLogsFileName[1][0];
			nDataFileSize = m_nDataFileSize[0][0];
			nLogsFileSize = m_nLogsFileSize[0][0];
			nDataFileMaxSize = m_nDataFileSize[1][0];
			nLogsFileMaxSize = m_nLogsFileSize[1][0];
			nDataFileGrowSize = m_nDataFileSize[2][0];
			nLogsFileGrowSize = m_nLogsFileSize[2][0];
			bReadOnly = m_bReadOnly[0];
			break;
		}
		return nResult;
	}
	for (m_szServer = pszServer, m_szSpacecraft = pszSpacecraft, m_szDatabase = pszDatabase, m_szStandard = pszStandard, m_szDataFileName[0][0] = m_szDataFileName[0][1] = szDataFileName, m_szLogsFileName[0][0] = m_szLogsFileName[0][1] = szLogsFileName, m_szDataFileName[1][0] = m_szDataFileName[1][1] = szDataFilePath, m_szLogsFileName[1][0] = m_szLogsFileName[1][1] = szLogsFilePath, m_nDataFileSize[0][0] = m_nDataFileSize[0][1] = nDataFileSize, m_nLogsFileSize[0][0] = m_nLogsFileSize[0][1] = nLogsFileSize, m_nDataFileSize[1][0] = m_nDataFileSize[1][1] = nDataFileMaxSize, m_nLogsFileSize[1][0] = m_nLogsFileSize[1][1] = nLogsFileMaxSize, m_nDataFileSize[2][0] = m_nDataFileSize[2][1] = nDataFileGrowSize, m_nLogsFileSize[2][0] = m_nLogsFileSize[2][1] = nLogsFileGrowSize, m_bReadOnly[0] = m_bReadOnly[1] = bReadOnly; (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		szDataFileName = m_szDataFileName[0][0];
		szDataFilePath = m_szDataFileName[1][0];
		szLogsFileName = m_szLogsFileName[0][0];
		szLogsFilePath = m_szLogsFileName[1][0];
		nDataFileSize = m_nDataFileSize[0][0];
		nLogsFileSize = m_nLogsFileSize[0][0];
		nDataFileMaxSize = m_nDataFileSize[1][0];
		nLogsFileMaxSize = m_nLogsFileSize[1][0];
		nDataFileGrowSize = m_nDataFileSize[2][0];
		nLogsFileGrowSize = m_nLogsFileSize[2][0];
		bReadOnly = m_bReadOnly[0];
		break;
	}
	return nResult;
}

VOID CDatabaseDetailsDialog::ShowDatabaseInfo()
{
	CheckDlgButton(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_READONLY, (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_bReadOnly[0] : FALSE);
	CheckDlgButton(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED, (((IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA) || (!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA) && !IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS))) && m_nDataFileSize[1][0] == (UINT)-1) || (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS) && m_nLogsFileSize[1][0] == (UINT)-1)) ? TRUE : FALSE);
	CheckDlgButton(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE, (((IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA) || (!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA) && !IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS))) && !m_nDataFileSize[2][0] && !m_bReadOnly[0]) || (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS) && !m_nLogsFileSize[2][0])) ? TRUE : FALSE);
	CheckRadioButton(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA, IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS, ((!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA) && !IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) || IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA : IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS);
	Spinbox_SetRange(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? DETAILSDATABASEDIALOG_MINIMUMINITDATASIZE : DETAILSDATABASEDIALOG_MINIMUMINITLOGSSIZE, (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? DETAILSDATABASEDIALOG_MAXIMUMINITDATASIZE : DETAILSDATABASEDIALOG_MAXIMUMINITLOGSSIZE);
	Spinbox_SetRange(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? DETAILSDATABASEDIALOG_MINIMUMMAXDATASIZE : DETAILSDATABASEDIALOG_MINIMUMMAXLOGSSIZE, (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? DETAILSDATABASEDIALOG_MAXIMUMMAXDATASIZE : DETAILSDATABASEDIALOG_MAXIMUMMAXLOGSSIZE);
	Spinbox_SetRange(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? DETAILSDATABASEDIALOG_MINIMUMGROWDATASIZE : DETAILSDATABASEDIALOG_MINIMUMGROWLOGSSIZE, (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? DETAILSDATABASEDIALOG_MAXIMUMGROWDATASIZE : DETAILSDATABASEDIALOG_MAXIMUMGROWLOGSSIZE);
	Spinbox_SetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[0][0] : m_nLogsFileSize[0][0]);
	Spinbox_SetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[1][0] : m_nLogsFileSize[1][0]);
	Spinbox_SetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[2][0] : m_nLogsFileSize[2][0]);
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_FILENAME)->SetWindowText((IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_szDataFileName[0][0] : m_szLogsFileName[0][0]);
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION)->SetWindowText((IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_szDataFileName[1][0] : m_szLogsFileName[1][0]);
	GetDlgItem(IDC_DATABASE_DBMS_NAME)->SetWindowText(m_szDatabase);
	GetDlgItem(IDC_DATABASE_DBMS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_NAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_TABLES)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_FILENAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION_BROWSE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE_MB)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED));
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_MB)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED));
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE));
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE) && !IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_READONLY));
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_MB)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE) && !IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_READONLY));
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED) && !IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_READONLY));
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_READONLY)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA));
	SendDlgItemMessage(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_FILENAME, EM_SETSEL, 0, (LPARAM)-1);
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

CString CDatabaseDetailsDialog::ConstructDataFileName(LPCTSTR pszDatabase) CONST
{
	CString  szFileName;

	szFileName.Format(STRING(IDS_ODBC_DATABASE_DATAFILE_NAME), pszDatabase);
	return szFileName;
}

CString CDatabaseDetailsDialog::ConstructLogsFileName(LPCTSTR pszDatabase) CONST
{
	CString  szFileName;

	szFileName.Format(STRING(IDS_ODBC_DATABASE_LOGSFILE_NAME), pszDatabase);
	return szFileName;
}

BOOL CDatabaseDetailsDialog::IsModified() CONST
{
	return((m_szDataFileName[0][0].CompareNoCase(m_szDataFileName[0][1]) || m_szDataFileName[1][0].CompareNoCase(m_szDataFileName[1][1]) || m_szLogsFileName[0][0].CompareNoCase(m_szLogsFileName[0][1]) || m_szLogsFileName[1][0].CompareNoCase(m_szLogsFileName[1][1]) || m_nDataFileSize[0][0] != m_nDataFileSize[0][1] || m_nDataFileSize[1][0] != m_nDataFileSize[1][1] || m_nDataFileSize[2][0] != m_nDataFileSize[2][1] || m_nLogsFileSize[0][0] != m_nLogsFileSize[0][1] || m_nLogsFileSize[1][0] != m_nLogsFileSize[1][1] || m_nLogsFileSize[2][0] != m_nLogsFileSize[2][1] || m_bReadOnly[0] != m_bReadOnly[1]) ? TRUE : FALSE);
}

BOOL CDatabaseDetailsDialog::Check(BOOL bModified) CONST
{
	return(((m_nDataFileSize[0][0] <= m_nDataFileSize[1][0] || !m_nDataFileSize[1][0]) && (m_nLogsFileSize[0][0] <= m_nLogsFileSize[1][0] || !m_nLogsFileSize[1][0]) && (m_nDataFileSize[2][0] <= m_nDataFileSize[1][0] || !m_nDataFileSize[1][0]) && (m_nLogsFileSize[2][0] <= m_nLogsFileSize[1][0] || !m_nLogsFileSize[1][0]) && m_szDataFileName[0][0].CompareNoCase(m_szLogsFileName[0][0]) && !m_szDataFileName[0][0].IsEmpty() && !m_szLogsFileName[0][0].IsEmpty()) ? (!bModified || IsModified()) : FALSE);
}

void CDatabaseDetailsDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseDetailsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseDetailsDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabaseDetailsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA, OnDataType)
	ON_BN_CLICKED(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS, OnLogsType)
	ON_BN_CLICKED(IDC_DATABASE_DBMS_PROPERTIES_TABLES, OnTables)
	ON_BN_CLICKED(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION_BROWSE, OnBrowseLocation)
	ON_BN_CLICKED(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED, OnUnlimitedSize)
	ON_BN_CLICKED(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE, OnFixedSize)
	ON_BN_CLICKED(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_READONLY, OnReadOnly)
	ON_BN_CLICKED(IDC_DATABASE_DBMS_HELP, OnHelp)
	ON_EN_CHANGE(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION, OnEditchangeLocation)
	ON_CONTROL(SBXN_CHANGE, IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE, OnSpinchangeInitialSize)
	ON_CONTROL(SBXN_CHANGE, IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE, OnSpinchangeMaximalSize)
	ON_CONTROL(SBXN_CHANGE, IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE, OnSpinchangeGrowSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDetailsDialog message handlers

BOOL CDatabaseDetailsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	ShowDatabaseInfo();
	return FALSE;
}

void CDatabaseDetailsDialog::OnDataType()
{
	ShowDatabaseInfo();
}

void CDatabaseDetailsDialog::OnLogsType()
{
	ShowDatabaseInfo();
}

void CDatabaseDetailsDialog::OnTables()
{
	CDatabaseTablesDialog  cDatabaseTablesDialog;

	cDatabaseTablesDialog.DoModal(m_szDatabase, m_szStandard, m_szSpacecraft);
}

void CDatabaseDetailsDialog::OnBrowseLocation()
{
	CString  szName;
	LPMALLOC  pIMalloc;
	LPITEMIDLIST  pItemIDList;
	TCHAR  szItemBuffer[MAX_PATH];
	TCHAR  szDisplayName[MAX_PATH];
	BROWSEINFO  sBrowseInfo = { 0 };

	if (SHGetMalloc(&pIMalloc) == NOERROR)
	{
		sBrowseInfo.hwndOwner = GetSafeHwnd();
		sBrowseInfo.pszDisplayName = szDisplayName;
		sBrowseInfo.lpszTitle = STRING(IDS_DIRECTORYBROWSEDIALOG_TITLE);
		if ((pItemIDList = SHBrowseForFolder(&sBrowseInfo)))
		{
			if (SHGetPathFromIDList(pItemIDList, szItemBuffer))
			{
				GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_FILENAME)->GetWindowText(szName);
				GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION)->SetWindowText(szItemBuffer);
				m_szDataFileName[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? szItemBuffer : m_szDataFileName[1][0];
				m_szLogsFileName[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? szItemBuffer : m_szLogsFileName[1][0];
			}
			pIMalloc->Free(pItemIDList);
		}
		pIMalloc->Release();
	}
	SendDlgItemMessage(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDetailsDialog::OnUnlimitedSize()
{
	if (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED))
	{
		for (m_nDataFileSize[1][0] = (!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[1][0] : (UINT)-1, m_nLogsFileSize[1][0] = (!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? m_nLogsFileSize[1][0] : (UINT)-1; IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE); )
		{
			m_nDataFileSize[2][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? (UINT)min(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTGROWDATASIZE) : m_nDataFileSize[2][0];
			m_nLogsFileSize[2][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? (UINT)min(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTGROWLOGSSIZE) : m_nLogsFileSize[2][0];
			Spinbox_SetRange(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? DETAILSDATABASEDIALOG_MINIMUMGROWDATASIZE : DETAILSDATABASEDIALOG_MINIMUMGROWLOGSSIZE, (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? DETAILSDATABASEDIALOG_MAXIMUMGROWDATASIZE : DETAILSDATABASEDIALOG_MAXIMUMGROWLOGSSIZE);
			Spinbox_SetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[2][0] : m_nLogsFileSize[2][0]);
			CheckDlgButton(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE, FALSE);
			GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_MB)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE)->SetFocus();
			break;
		}
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_MB)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE)->EnableWindow(FALSE);
	}
	else
	{
		m_nDataFileSize[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? (UINT)max(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTMAXDATASIZE) : m_nDataFileSize[1][0];
		m_nLogsFileSize[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? (UINT)max(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTMAXLOGSSIZE) : m_nLogsFileSize[1][0];
		Spinbox_SetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[1][0] : m_nLogsFileSize[1][0]);
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE)->EnableWindow();
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE)->EnableWindow();
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_MB)->EnableWindow();
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDetailsDialog::OnFixedSize()
{
	if (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE))
	{
		for (m_nDataFileSize[2][0] = (!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[2][0] : 0, m_nLogsFileSize[2][0] = (!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? m_nLogsFileSize[2][0] : 0; IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED); )
		{
			m_nDataFileSize[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? (UINT)max(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTMAXDATASIZE) : m_nDataFileSize[1][0];
			m_nLogsFileSize[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? (UINT)max(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTMAXLOGSSIZE) : m_nLogsFileSize[1][0];
			Spinbox_SetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[1][0] : m_nLogsFileSize[1][0]);
			CheckDlgButton(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED, FALSE);
			GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_MB)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE)->SetFocus();
			break;
		}
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_MB)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED)->EnableWindow(FALSE);
	}
	else
	{
		m_bReadOnly[0] = (!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_bReadOnly[0] : FALSE;
		m_nDataFileSize[2][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? (UINT)min(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTGROWDATASIZE) : m_nDataFileSize[2][0];
		m_nLogsFileSize[2][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? (UINT)min(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTGROWLOGSSIZE) : m_nLogsFileSize[2][0];
		Spinbox_SetRange(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? DETAILSDATABASEDIALOG_MINIMUMGROWDATASIZE : DETAILSDATABASEDIALOG_MINIMUMGROWLOGSSIZE, (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? DETAILSDATABASEDIALOG_MAXIMUMGROWDATASIZE : DETAILSDATABASEDIALOG_MAXIMUMGROWLOGSSIZE);
		Spinbox_SetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[2][0] : m_nLogsFileSize[2][0]);
		CheckDlgButton(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_READONLY, FALSE);
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED)->EnableWindow();
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE)->EnableWindow();
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_MB)->EnableWindow();
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDetailsDialog::OnReadOnly()
{
	if ((m_bReadOnly[0] = IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_READONLY)))
	{
		for (m_nDataFileSize[2][0] = (!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[2][0] : 0, m_nLogsFileSize[2][0] = (!IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? m_nLogsFileSize[2][0] : 0; IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED); )
		{
			m_nDataFileSize[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? (UINT)max(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTMAXDATASIZE) : m_nDataFileSize[1][0];
			m_nLogsFileSize[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? (UINT)max(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTMAXLOGSSIZE) : m_nLogsFileSize[1][0];
			Spinbox_SetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE), (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? m_nDataFileSize[1][0] : m_nLogsFileSize[1][0]);
			CheckDlgButton(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED, FALSE);
			GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_MB)->EnableWindow();
			break;
		}
		CheckDlgButton(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE, FALSE);
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_MB)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED)->EnableWindow(FALSE);
	}
	else
	{
		Spinbox_SetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE), (m_nDataFileSize[2][0] = (UINT)min(Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE)), DETAILSDATABASEDIALOG_DEFAULTGROWDATASIZE)));
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE)->EnableWindow();
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_MB)->EnableWindow();
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE_FIXEDSIZE)->EnableWindow();
		GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE_UNLIMITED)->EnableWindow();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDetailsDialog::OnEditchangeFileName()
{
	CString  szFileName;

	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_FILENAME)->GetWindowText(szFileName);
	m_szDataFileName[0][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? szFileName : m_szDataFileName[0][0];
	m_szLogsFileName[0][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? szFileName : m_szLogsFileName[0][0];
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDetailsDialog::OnEditchangeLocation()
{
	CString  szFileLocation;

	GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_LOCATION)->GetWindowText(szFileLocation);
	m_szDataFileName[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? szFileLocation : m_szDataFileName[1][0];
	m_szLogsFileName[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? szFileLocation : m_szLogsFileName[1][0];
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDetailsDialog::OnSpinchangeInitialSize()
{
	INT  nSize;

	nSize = (INT)Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_INITIALSIZE));
	m_nDataFileSize[0][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? nSize : m_nDataFileSize[0][0];
	m_nLogsFileSize[0][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? nSize : m_nLogsFileSize[0][0];
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDetailsDialog::OnSpinchangeMaximalSize()
{
	INT  nSize;

	nSize = (INT)Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_MAXIMALSIZE));
	m_nDataFileSize[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? nSize : m_nDataFileSize[1][0];
	m_nLogsFileSize[1][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? nSize : m_nLogsFileSize[1][0];
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDetailsDialog::OnSpinchangeGrowSize()
{
	INT  nSize;

	nSize = (INT)Spinbox_GetPos(GetDlgItem(IDC_DATABASE_DBMS_PROPERTIES_CHARACTERISTICS_GROWSIZE));
	m_nDataFileSize[2][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_DATA)) ? nSize : m_nDataFileSize[2][0];
	m_nLogsFileSize[2][0] = (IsDlgButtonChecked(IDC_DATABASE_DBMS_PROPERTIES_FILETYPE_LOGS)) ? nSize : m_nLogsFileSize[2][0];
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDetailsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	EndDialog(IDOK);
}

void CDatabaseDetailsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabaseDetailsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEDBMSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseDetailsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEDBMSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseTablesDialog, CLocaleDialog)

CDatabaseTablesDialog::CDatabaseTablesDialog(CWnd *pParentWnd) : CLocaleDialog(CDatabaseTablesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDatabaseTablesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CDatabaseTablesDialog::DoModal(LPCTSTR pszDatabase, LPCTSTR pszStandard, LPCTSTR pszSpacecraft)
{
	m_szDatabase = pszDatabase;
	m_szStandard = pszStandard;
	m_szSpacecraft = pszSpacecraft;
	return CLocaleDialog::DoModal();
}

BOOL CDatabaseTablesDialog::EnumTables()
{
	INT  nTable;
	INT  nTables;
	CString  szTable;
	CStringArray  szDescriptions;
	CDatabaseProfileInfo  cDatabaseProfileInfo;

	for (cDatabaseProfileInfo.SetType(CDatabaseProfileInfo::TranslateImplementationStandard(m_szStandard)), cDatabaseProfileInfo.SetSpacecraft(m_szSpacecraft), nTables = 0; m_cDatabase.Open(&cDatabaseProfileInfo, FALSE); )
	{
		for (nTable = 0, nTables = m_cDatabase.EnumDBMSTables(m_szTables, szDescriptions); nTable < nTables; nTable = nTable + 1)
		{
			szTable.Format(STRING(IDS_DATABASETABLESDIALOG_COMPONENTFORMAT), (LPCTSTR)m_szTables.GetAt(nTable), (LPCTSTR)szDescriptions.GetAt(nTable));
			SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_COMPONENT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
		}
		break;
	}
	SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_COMPONENT, CB_SETCURSEL);
	GetDlgItem(IDC_DATABASE_DBMS_TABLES_COMPONENT_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_COMPONENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_DBMS_TABLES_COMPONENT)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_COMPONENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((nTables > 0) ? TRUE : FALSE);
}

VOID CDatabaseTablesDialog::ShowTableContent()
{
	GetDlgItem(IDC_DATABASE_DBMS_TABLES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_TABLES_NAME)->SetWindowText(m_szDatabase);
	GetDlgItem(IDC_DATABASE_DBMS_TABLES_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_TABLES_NAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_DBMS_TABLES_PROPERTIES)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_COMPONENT, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	ShowTableContent((INT)SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_COMPONENT, CB_GETCURSEL));
}
VOID CDatabaseTablesDialog::ShowTableContent(INT nIndex)
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CStringArray  szColumns;
	CStringArray  szDataTypes;
	CStringArray  szDefaults;
	CByteArray  bAllowNulls;

	for (nItem = 0, nItems = (nIndex >= 0 && nIndex < m_szTables.GetSize() && m_cDatabase.GetDBMSTableCharacteristics(m_szTables.GetAt(nIndex), szColumns, szDataTypes, szDefaults, bAllowNulls)) ? (INT)szColumns.GetSize() : 0; nItem < nItems; nItem++)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESDIALOG_TITLEITEM_COLUMN); )
			{
				szItem = szColumns.GetAt(nItem);
				break;
			}
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESDIALOG_TITLEITEM_FORMAT)) szItem = szDataTypes.GetAt(nItem);
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESDIALOG_TITLEITEM_DEFAULT))  szItem = szDefaults.GetAt(nItem);
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESDIALOG_TITLEITEM_ALLOWNULLS)) szItem = (bAllowNulls.GetAt(nItem)) ? STRING(IDS_DATABASETABLESDIALOG_NULLFLAG_YES) : STRING(IDS_DATABASETABLESDIALOG_NULLFLAG_NO);
			if (!nColumn  &&  nItem >= SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_CONTENT, LVM_GETITEMCOUNT))
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_DBMS_TABLES_CONTENT), nItem, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_DBMS_TABLES_CONTENT), nItem, nColumn, szItem);
		}
	}
	for (Listview_SetCurText(GetDlgItem(IDC_DATABASE_DBMS_TABLES_CONTENT), 0); nItems < SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_CONTENT, LVM_GETITEMCOUNT); )
	{
		Listview_DeleteText(GetDlgItem(IDC_DATABASE_DBMS_TABLES_CONTENT), nItems);
		continue;
	}
	GetDlgItem(IDC_DATABASE_DBMS_TABLES_CONTENT)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_CONTENT, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow();
}

void CDatabaseTablesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseTablesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseTablesDialog::PostNcDestroy()
{
	m_cDatabase.Close();
	m_szTables.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseTablesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabaseTablesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_DBMS_TABLES_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_DATABASE_DBMS_TABLES_COMPONENT, OnSelchangeTable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesDialog message handlers

BOOL CDatabaseTablesDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	m_szColumns.Add(STRING(IDS_DATABASETABLESDIALOG_TITLEITEM_COLUMN));
	m_szColumns.Add(STRING(IDS_DATABASETABLESDIALOG_TITLEITEM_FORMAT));
	m_szColumns.Add(STRING(IDS_DATABASETABLESDIALOG_TITLEITEM_DEFAULT));
	m_szColumns.Add(STRING(IDS_DATABASETABLESDIALOG_TITLEITEM_ALLOWNULLS));
	GetDlgItem(IDC_DATABASE_DBMS_TABLES_CONTENT)->GetClientRect(rColumns);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_CONTENT, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_DATABASE_DBMS_TABLES_CONTENT), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESDIALOG_TITLEITEM_COLUMN)) ? (rColumns.Width() - rColumns.Width() / 4 - rColumns.Width() / 3 - GetSystemMetrics(SM_CXVSCROLL)) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESDIALOG_TITLEITEM_FORMAT)) ? (rColumns.Width() / 4) : (rColumns.Width() / 6)));
		continue;
	}
	EnumTables();
	ShowTableContent();
	return TRUE;
}

void CDatabaseTablesDialog::OnSelchangeTable()
{
	ShowTableContent((INT)SendDlgItemMessage(IDC_DATABASE_DBMS_TABLES_COMPONENT, CB_GETCURSEL));
}

void CDatabaseTablesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	EndDialog(IDOK);
}

void CDatabaseTablesDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabaseTablesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEDBMSTABLESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseTablesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEDBMSTABLESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseUsersDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseUsersDialog, CLocaleDialog)

CDatabaseUsersDialog::CDatabaseUsersDialog(CWnd *pParentWnd) : CLocaleDialog(CDatabaseUsersDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDatabaseUsersDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CDatabaseUsersDialog::DoModal()
{
	INT  nUser;
	INT  nUsers;
	INT  nDatabase;
	INT  nDatabases;
	BOOL  bAdministrator;
	CStringArray  szUsers;
	CStringArray  szPasswords;
	CUIntArray  nPrivileges;
	CDatabases  cDatabases;
	CDatabaseProfiles  pDatabases;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	for (nDatabase = 0, nDatabases = (cDatabases.GetDatabases(pDatabases, TRUE)) ? (INT)pDatabases.GetSize() : 0; nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetName() == GetAccountDatabase() && pDatabaseProfileInfo->GetSpacecraft() == GetAccountSpacecraftName() && !pDatabaseProfileInfo->GetServer().CompareNoCase(GetAccountComputerName()))
		{
			if (pDatabaseProfileInfo->GetUsers(szUsers, szPasswords, nPrivileges) >= 0)
			{
				for (nUser = 0, nUsers = (INT)szUsers.GetSize(); nUser < nUsers; nUser++)
				{
					if ((bAdministrator = CUserToken(szUsers.GetAt(nUser)).IsAdministrator()) && nUser > 0)
					{
						szUsers.InsertAt(0, (LPCTSTR)szUsers.GetAt(nUser));
						szPasswords.InsertAt(0, (LPCTSTR)szPasswords.GetAt(nUser));
						nPrivileges.InsertAt(0, nPrivileges.GetAt(nUser));
						szUsers.RemoveAt(nUser + 1);
						szPasswords.RemoveAt(nUser + 1);
						nPrivileges.RemoveAt(nUser + 1);
					}
					if (bAdministrator) break;
				}
				m_szUsers[0].Copy(szUsers);
				m_szUsers[1].Copy(szUsers);
				m_szPasswords[0].Copy(szPasswords);
				m_szPasswords[1].Copy(szPasswords);
				m_nPrivileges[0].Copy(nPrivileges);
				m_nPrivileges[1].Copy(nPrivileges);
				m_bDatabaseUsers = TRUE;
				return CLocaleDialog::DoModal();
			}
		}
	}
	return IDCANCEL;
}
INT_PTR CDatabaseUsersDialog::DoModal(LPCTSTR pszDatabaseName, CStringArray &szUsers, CStringArray &szPasswords, CUIntArray &nPrivileges)
{
	INT  nUser;
	INT  nUsers;
	BOOL  bAdministrator;
	INT_PTR  nResult;

	for (nUser = 0, nUsers = (INT)szUsers.GetSize(); nUser < nUsers; nUser++)
	{
		if ((bAdministrator = CUserToken(szUsers.GetAt(nUser)).IsAdministrator()) && nUser > 0)
		{
			szUsers.InsertAt(0, (LPCTSTR)szUsers.GetAt(nUser));
			szPasswords.InsertAt(0, (LPCTSTR)szPasswords.GetAt(nUser));
			nPrivileges.InsertAt(0, nPrivileges.GetAt(nUser));
			szUsers.RemoveAt(nUser + 1);
			szPasswords.RemoveAt(nUser + 1);
			nPrivileges.RemoveAt(nUser + 1);
		}
		if (bAdministrator) break;
	}
	for (m_szUsers[0].Copy(szUsers), m_szUsers[1].Copy(szUsers), m_szPasswords[0].Copy(szPasswords), m_szPasswords[1].Copy(szPasswords), m_nPrivileges[0].Copy(nPrivileges), m_nPrivileges[1].Copy(nPrivileges), m_bDatabaseUsers = FALSE; (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		nPrivileges.Copy(m_nPrivileges[0]);
		szPasswords.Copy(m_szPasswords[0]);
		szUsers.Copy(m_szUsers[0]);
		break;
	}
	return nResult;
}

VOID CDatabaseUsersDialog::EnumUsers()
{
	INT  nUser;
	INT  nUsers;

	for (nUser = 0, nUsers = (INT)m_szUsers[0].GetSize(), SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_RESETCONTENT); nUser < nUsers; nUser++)
	{
		SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szUsers[0].GetAt(nUser));
		continue;
	}
	SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountUserName()), 0));
	GetDlgItem(IDC_DATABASE_USERS_NAMES_STATIC)->EnableWindow(CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) || !CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE));
	GetDlgItem(IDC_DATABASE_USERS_NAMES)->EnableWindow();
	GetDlgItem(IDC_DATABASE_USERS_NAMES)->SetFocus();
}

VOID CDatabaseUsersDialog::ShowUserInfo()
{
	CString  szUser;

	GetDlgItem(IDC_DATABASE_USERS_NAME)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_DATABASE_USERS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_USERS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_USERS_NAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_USERS_NAMES)->GetWindowText(szUser);
	ShowUserInfo(szUser);
}
VOID CDatabaseUsersDialog::ShowUserInfo(LPCTSTR pszUser)
{
	INT  nUser;
	INT  nUsers;
	INT  nRight;
	INT  nRights;

	for (nUser = 0, nUsers = (INT)m_szUsers[0].GetSize(), SendDlgItemMessage(IDC_DATABASE_USERS_PERMISSIONS, LB_RESETCONTENT); nUser < nUsers; nUser++)
	{
		if (m_szUsers[0].GetAt(nUser) == pszUser) break;
		continue;
	}
	for (nRight = 0, nRights = (nUser < nUsers) ? (MAXDATABASEPRIVILEGE - MINDATABASEPRIVILEGE + 1) : 0; nRight < nRights; nRight++)
	{
		if (ConvertToPermission(nRight) & m_nPrivileges[0].GetAt(nUser)) SendDlgItemMessage(IDC_DATABASE_USERS_PERMISSIONS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(MINDATABASEPRIVILEGE + nRight));
		continue;
	}
	GetDlgItem(IDC_DATABASE_USERS_ADD)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)pszUser) == CB_ERR) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
	GetDlgItem(IDC_DATABASE_USERS_VIEW)->EnableWindow(((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)pszUser) > 0 && !CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE)) || !SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)pszUser)) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_USERS_VIEW)->ShowWindow(((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)pszUser) > 0 && !CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE)) || SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)pszUser) <= 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_DATABASE_USERS_CHANGE)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)pszUser) > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
	GetDlgItem(IDC_DATABASE_USERS_CHANGE)->ShowWindow((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)pszUser) > 0 && CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE)) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_DATABASE_USERS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)pszUser) > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
	GetDlgItem(IDC_DATABASE_USERS_PERMISSIONS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_USERS_PERMISSIONS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_USERS_PERMISSIONS)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_USERS_PERMISSIONS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

UINT CDatabaseUsersDialog::ConvertToPermission(INT nRight) CONST
{
	return 1 << nRight;
}

BOOL CDatabaseUsersDialog::IsModified() CONST
{
	INT  nUser[2];
	INT  nUsers[2];
	CString  szUser;

	GetDlgItem(IDC_DATABASE_USERS_NAMES)->GetWindowText(szUser);
	for (nUser[0] = 0, nUsers[0] = (m_szUsers[0].GetSize() == m_szUsers[1].GetSize()) ? (INT)m_szUsers[0].GetSize() : -1; nUser[0] < nUsers[0]; nUser[0]++)
	{
		for (nUser[1] = 0, nUsers[1] = (INT)m_szUsers[1].GetSize(); nUser[1] < nUsers[1]; nUser[1]++)
		{
			if (m_szUsers[0].GetAt(nUser[0]) == m_szUsers[1].GetAt(nUser[1]))
			{
				if (m_szPasswords[0].GetAt(nUser[0]) != m_szPasswords[1].GetAt(nUser[1])) break;
				if (m_nPrivileges[0].GetAt(nUser[0]) != m_nPrivileges[1].GetAt(nUser[1])) break;
			}
		}
		if (nUser[1] < nUsers[1]) break;
	}
	return((nUser[0] < nUsers[0] || nUsers[0] < 0) ? TRUE : FALSE);
}

BOOL CDatabaseUsersDialog::Check(BOOL bModified) CONST
{
	CString  szUser;

	GetDlgItem(IDC_DATABASE_USERS_NAMES)->GetWindowText(szUser);
	return((GetDlgItem(IDC_DATABASE_USERS_NAMES)->SendMessage(CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser) >= 0) ? (!bModified || IsModified()) : FALSE);
}

VOID CDatabaseUsersDialog::AdjustToPrivileges()
{
	AccessControl(IDC_DATABASE_USERS_NAMES, CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE));
}

void CDatabaseUsersDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseUsersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseUsersDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabaseUsersDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_USERS_ADD, OnAddUser)
	ON_BN_CLICKED(IDC_DATABASE_USERS_VIEW, OnViewUser)
	ON_BN_CLICKED(IDC_DATABASE_USERS_CHANGE, OnChangeUser)
	ON_BN_CLICKED(IDC_DATABASE_USERS_REMOVE, OnRemoveUser)
	ON_BN_CLICKED(IDC_DATABASE_USERS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_DATABASE_USERS_NAMES, OnSelchangeUser)
	ON_CBN_EDITCHANGE(IDC_DATABASE_USERS_NAMES, OnEditchangeUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseUsersDialog message handlers

BOOL CDatabaseUsersDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	EnumUsers();
	ShowUserInfo();
	AdjustToPrivileges();
	return FALSE;
}

void CDatabaseUsersDialog::OnAddUser()
{
	INT  nIndex;
	UINT  nPrivileges;
	CString  szUser;
	CString  szPassword;
	CDatabasePrivilegesDialog  cDatabasePrivilegesDialog(this);

	GetDlgItem(IDC_DATABASE_USERS_NAMES)->GetWindowText(szUser);
	if (cDatabasePrivilegesDialog.DoModal(szUser, szPassword, (nPrivileges = DATABASE_PRIVILEGES_ALL)) == IDOK)
	{
		if ((nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szUser)) >= 0)
		{
			SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_SETCURSEL, nIndex);
			m_nPrivileges[0].Add(nPrivileges);
			m_szPasswords[0].Add(szPassword);
			m_szUsers[0].Add(szUser);
			ShowUserInfo(szUser);
		}
	}
	GetDlgItem(IDC_DATABASE_USERS_NAMES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseUsersDialog::OnViewUser()
{
	INT  nUser;
	INT  nUsers;
	UINT  nPrivileges;
	CString  szUser;
	CString  szPassword;
	CDatabasePrivilegesDialog  cDatabasePrivilegesDialog(this);

	GetDlgItem(IDC_DATABASE_USERS_NAMES)->GetWindowText(szUser);
	for (nUser = 0, nUsers = (INT)m_szUsers[0].GetSize(); nUser < nUsers; nUser++)
	{
		if (m_szUsers[0].GetAt(nUser) == szUser)
		{
			szPassword = m_szPasswords[0].GetAt(nUser);
			nPrivileges = m_nPrivileges[0].GetAt(nUser);
			break;
		}
	}
	cDatabasePrivilegesDialog.DoModal(szUser, szPassword, nPrivileges, FALSE);
	GetDlgItem(IDC_DATABASE_USERS_NAMES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseUsersDialog::OnChangeUser()
{
	INT  nUser;
	INT  nUsers;
	INT  nIndex;
	UINT  nPrivileges;
	CString  szUser;
	CString  szPassword;
	CDatabasePrivilegesDialog  cDatabasePrivilegesDialog(this);

	GetDlgItem(IDC_DATABASE_USERS_NAMES)->GetWindowText(szUser);
	for (nUser = 0, nUsers = (INT)m_szUsers[0].GetSize(); nUser < nUsers; nUser++)
	{
		if (m_szUsers[0].GetAt(nUser) == szUser)
		{
			szPassword = m_szPasswords[0].GetAt(nUser);
			nPrivileges = m_nPrivileges[0].GetAt(nUser);
			break;
		}
	}
	if (cDatabasePrivilegesDialog.DoModal(szUser, szPassword, nPrivileges) == IDOK)
	{
		if ((nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser)) >= 0)
		{
			SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_SETCURSEL, nIndex);
			m_nPrivileges[0].SetAt(nIndex, nPrivileges);
			m_szPasswords[0].SetAt(nIndex, szPassword);
			m_szUsers[0].SetAt(nIndex, szUser);
			ShowUserInfo(szUser);
		}
	}
	GetDlgItem(IDC_DATABASE_USERS_NAMES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseUsersDialog::OnRemoveUser()
{
	INT  nIndex;
	CString  szUser;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_DATABASE_USERS_NAMES)->GetWindowText(szUser);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser)) >= 0)
	{
		SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_DELETESTRING, nIndex);
		SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_SETCURSEL);
		m_nPrivileges[0].RemoveAt(nIndex);
		m_szPasswords[0].RemoveAt(nIndex);
		m_szUsers[0].RemoveAt(nIndex);
		ShowUserInfo();
	}
	GetDlgItem(IDC_DATABASE_USERS_NAMES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseUsersDialog::OnSelchangeUser()
{
	INT  nIndex;
	CString  szUser[2];

	GetDlgItem(IDC_DATABASE_USERS_NAMES)->GetWindowText(szUser[0]);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_GETCURSEL)) >= 0)
	{
		if ((szUser[1] = Combobox_GetText(GetDlgItem(IDC_DATABASE_USERS_NAMES), nIndex)) != szUser[0])
		{
			ShowUserInfo(szUser[1]);
			return;
		}
	}
}

void CDatabaseUsersDialog::OnEditchangeUser()
{
	CString  szUser;

	GetDlgItem(IDC_DATABASE_USERS_NAMES)->GetWindowText(szUser);
	GetDlgItem(IDC_DATABASE_USERS_ADD)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser) == CB_ERR  &&  szUser.GetLength() > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
	GetDlgItem(IDC_DATABASE_USERS_VIEW)->EnableWindow(((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser) > 0 && !CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE)) || !SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser)) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_USERS_VIEW)->ShowWindow(((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser) > 0 && !CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE)) || SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser) <= 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_DATABASE_USERS_CHANGE)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser) > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
	GetDlgItem(IDC_DATABASE_USERS_CHANGE)->ShowWindow((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser) > 0 && CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE)) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_DATABASE_USERS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_USERS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser) > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
}

void CDatabaseUsersDialog::OnOK()
{
	INT  nUser;
	INT  nUsers;
	INT  nDatabase;
	INT  nDatabases;
	BOOL  bDatabase;
	CString  szDatabase;
	CDatabases  cDatabases;
	CDatabaseProfiles  pDatabases;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CHourglassCursor  cCursor;

	for (nDatabase = 0, nDatabases = (CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) && m_bDatabaseUsers) ? ((cDatabases.GetDatabases(pDatabases, TRUE)) ? (INT)pDatabases.GetSize() : -1) : 0, bDatabase = FALSE; nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetName() == GetAccountDatabase() && pDatabaseProfileInfo->GetSpacecraft() == GetAccountSpacecraftName() && !pDatabaseProfileInfo->GetServer().CompareNoCase(GetAccountComputerName()))
		{
			if ((szDatabase = pDatabaseProfileInfo->GetName()) == GetAccountDatabase())
			{
				GetDatabase()->SetUsers(m_szUsers[0], m_szPasswords[0], m_nPrivileges[0]);
				bDatabase = TRUE;
			}
			pDatabaseProfileInfo->SetUsers(m_szUsers[0], m_szPasswords[0], m_nPrivileges[0]);
			nDatabases = (cDatabases.SetDatabases(pDatabases)) ? nDatabases : -1;
			break;
		}
	}
	for (nUser = 0, nUsers = (nDatabase < nDatabases) ? (INT)m_szUsers[0].GetSize() : 0; nUser < nUsers; nUser++)
	{
		if (m_szUsers[0].GetAt(nUser) == GetAccountUserName()) break;
		continue;
	}
	for (; nUser == nUsers && nDatabase < nDatabases && bDatabase; )
	{
		SetDatabase(GetAccountSpacecraftName(), EMPTYSTRING);
		break;
	}
	ShowMessage(((nDatabase == nDatabases  &&  nDatabases > 0) || nDatabases < 0) ? SYSTEM_WARNING_DATABASE_UPDATE_FAILURE : SYSTEM_NOERROR);
	EndDialog(IDOK);
}

void CDatabaseUsersDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabaseUsersDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ACCOUNTSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseUsersDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ACCOUNTSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabasePrivilegesDialog dialog

IMPLEMENT_DYNCREATE(CDatabasePrivilegesDialog, CLocaleDialog)

CDatabasePrivilegesDialog::CDatabasePrivilegesDialog(CWnd *pParentWnd) : CLocaleDialog(CDatabasePrivilegesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDatabasePrivilegesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CDatabasePrivilegesDialog::DoModal()
{
	INT  nUser;
	INT  nUsers;
	CStringArray  szUsers;
	CStringArray  szPasswords;
	CUIntArray  nPrivileges;

	for (nUser = 0, nUsers = (GetDatabase()->GetUsers(szUsers, szPasswords, nPrivileges) > 0) ? (INT)szUsers.GetSize() : 0, m_bModify = TRUE; nUser < nUsers; nUser++)
	{
		if (szUsers.GetAt(nUser) == GetAccountUserName())
		{
			m_szUserName = szUsers.GetAt(nUser);
			m_szPassword[0] = szPasswords.GetAt(nUser);
			m_szPassword[1] = szPasswords.GetAt(nUser);
			m_nPrivileges[0] = nPrivileges.GetAt(nUser);
			m_nPrivileges[1] = nPrivileges.GetAt(nUser);
			return CLocaleDialog::DoModal();
		}
	}
	return IDCANCEL;
}
INT_PTR CDatabasePrivilegesDialog::DoModal(LPCTSTR pszUserName, CString &szPassword, UINT &nPrivileges, BOOL bAllowModifications)
{
	INT_PTR  nResult;

	for (m_szUserName = pszUserName, m_szPassword[0] = m_szPassword[1] = szPassword, m_nPrivileges[0] = m_nPrivileges[1] = nPrivileges, m_bModify = bAllowModifications; (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		nPrivileges = m_nPrivileges[0];
		szPassword = m_szPassword[0];
		break;
	}
	return nResult;
}

VOID CDatabasePrivilegesDialog::EnumPrivileges()
{
	INT  nRight;
	INT  nRights;

	for (nRight = 0, nRights = MAXDATABASEPRIVILEGE - MINDATABASEPRIVILEGE + 1; nRight < nRights; nRight++)
	{
		SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)TranslatePermission(ConvertToPermission(nRight)));
		continue;
	}
	SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST, CB_SETCURSEL);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CDatabasePrivilegesDialog::ShowPrivilegeInfo()
{
	INT  nRight;
	INT  nRights;

	SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_RESETCONTENT);
	for (nRight = 0, nRights = MAXDATABASEPRIVILEGE - MINDATABASEPRIVILEGE + 1; nRight < nRights; nRight++)
	{
		if (ConvertToPermission(nRight) & m_nPrivileges[0]) SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)TranslatePermission(ConvertToPermission(nRight)));
		continue;
	}
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT)->SetWindowText(m_szPassword[0]);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXTCONFIRMATION)->SetWindowText(m_szPassword[0]);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD)->EnableWindow();
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT)->EnableWindow();
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXTCONFIRMATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXTCONFIRMATION)->EnableWindow();
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_ALLOW)->EnableWindow((!(TranslatePermission() & m_nPrivileges[0])) ? CheckPrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_DENY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_GETCURSEL) >= 0) ? CheckPrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
	SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT)->SetFocus();
}

UINT CDatabasePrivilegesDialog::TranslatePermission() CONST
{
	CString  szPermission;

	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST)->GetWindowText(szPermission);
	return TranslatePermission(szPermission);
}
UINT CDatabasePrivilegesDialog::TranslatePermission(LPCTSTR pszPermission) CONST
{
	INT  nRight;
	INT  nRights;

	for (nRight = 0, nRights = MAXDATABASEPRIVILEGE - MINDATABASEPRIVILEGE + 1; nRight < nRights; nRight++)
	{
		if (!_tcscmp(STRING(MINDATABASEPRIVILEGE + nRight), pszPermission)) break;
		continue;
	}
	return((nRight < nRights) ? ConvertToPermission(nRight) : 0);
}

CString CDatabasePrivilegesDialog::TranslatePermission(UINT nPermission) CONST
{
	return((ConvertToRight(nPermission) >= 0) ? STRING(MINDATABASEPRIVILEGE + ConvertToRight(nPermission)) : EMPTYSTRING);
}

UINT CDatabasePrivilegesDialog::ConvertToPermission(INT nRight) CONST
{
	return 1 << nRight;
}

INT CDatabasePrivilegesDialog::ConvertToRight(UINT nPermission) CONST
{
	INT  nRight;
	INT  nRights;

	for (nRight = 0, nRights = MAXDATABASEPRIVILEGE - MINDATABASEPRIVILEGE + 1; nRight < nRights; nRight++)
	{
		if (nPermission == ConvertToPermission(nRight)) break;
		continue;
	}
	return((nRight < nRights) ? nRight : -1);
}

BOOL CDatabasePrivilegesDialog::CheckPrivilege(UINT nPrivilege) CONST
{
	return((CheckDatabasePrivilege(nPrivilege)) ? m_bModify : FALSE);
}

BOOL CDatabasePrivilegesDialog::IsModified() CONST
{
	CString  szPassword[2];

	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT)->GetWindowText(szPassword[0]);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXTCONFIRMATION)->GetWindowText(szPassword[1]);
	return((m_szPassword[0] != m_szPassword[1] || m_nPrivileges[0] != m_nPrivileges[1]) ? TRUE : FALSE);
}

BOOL CDatabasePrivilegesDialog::Check(BOOL bModified) CONST
{
	CString  szPassword[2];

	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT)->GetWindowText(szPassword[0]);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXTCONFIRMATION)->GetWindowText(szPassword[1]);
	return((!szPassword[0].IsEmpty() && !szPassword[1].IsEmpty() && szPassword[0] == szPassword[1]) ? (!bModified || IsModified()) : FALSE);
}

VOID CDatabasePrivilegesDialog::AdjustToPrivileges()
{
	AccessControl(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT, (m_bModify) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
	AccessControl(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXTCONFIRMATION, (m_bModify) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
}

void CDatabasePrivilegesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabasePrivilegesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabasePrivilegesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabasePrivilegesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_PRIVILEGES_PERMISSIONS_ALLOW, OnAllowPermission)
	ON_BN_CLICKED(IDC_DATABASE_PRIVILEGES_PERMISSIONS_DENY, OnDenyPermission)
	ON_BN_CLICKED(IDC_DATABASE_PRIVILEGES_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST, OnSelchangePermission)
	ON_LBN_SELCHANGE(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, OnSelchangeGrantedPermission)
	ON_EN_CHANGE(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT, OnEditchangePassword)
	ON_EN_CHANGE(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXTCONFIRMATION, OnEditchangePasswordConfirmation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabasePrivilegesDialog message handlers

BOOL CDatabasePrivilegesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	AccessControl(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT, CheckPrivilege(DATABASE_PRIVILEGE_USERS_CHANGE));
	AccessControl(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXTCONFIRMATION, CheckPrivilege(DATABASE_PRIVILEGE_USERS_CHANGE));
	GetDlgItem(IDC_DATABASE_PRIVILEGES_USER)->SetWindowText(m_szUserName);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_PRIVILEGES_USER_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_PRIVILEGES_USER)->EnableWindow();
	EnumPrivileges();
	ShowPrivilegeInfo();
	AdjustToPrivileges();
	return FALSE;
}

void CDatabasePrivilegesDialog::OnAllowPermission()
{
	INT  nIndex;
	CString  szPermission;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST)->GetWindowText(szPermission);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szPermission)) >= 0)
	{
		GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_SETCURSEL, nIndex);
		GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_ALLOW)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_DENY)->EnableWindow(CheckPrivilege(DATABASE_PRIVILEGE_USERS_CHANGE));
		GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST)->SetFocus();
		m_nPrivileges[0] |= TranslatePermission(szPermission);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabasePrivilegesDialog::OnDenyPermission()
{
	INT  nIndex;
	CString  szPermission;
	CHourglassCursor  cCursor;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_GETCURSEL)) >= 0)
	{
		for (szPermission = Listbox_GetText(GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED), nIndex); SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_DELETESTRING, nIndex) >= 0; )
		{
			SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_SETCURSEL, (WPARAM)-1);
			GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_ALLOW)->EnableWindow((TranslatePermission(szPermission) == TranslatePermission() || !(TranslatePermission() & m_nPrivileges[0])) ? CheckPrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
			GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_DENY)->EnableWindow(FALSE);
			GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_LIST)->SetFocus();
			m_nPrivileges[0] &= ~TranslatePermission(szPermission);
			break;
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabasePrivilegesDialog::OnSelchangePermission()
{
	SendDlgItemMessage(IDC_DATABASE_PRIVILEGES_PERMISSIONS_GRANTED, LB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_ALLOW)->EnableWindow((!(TranslatePermission() & m_nPrivileges[0])) ? CheckPrivilege(DATABASE_PRIVILEGE_USERS_CHANGE) : FALSE);
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_DENY)->EnableWindow(FALSE);
}

void CDatabasePrivilegesDialog::OnSelchangeGrantedPermission()
{
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PERMISSIONS_DENY)->EnableWindow(CheckPrivilege(DATABASE_PRIVILEGE_USERS_CHANGE));
}

void CDatabasePrivilegesDialog::OnEditchangePassword()
{
	GetDlgItem(IDC_DATABASE_PRIVILEGES_PASSWORD_TEXT)->GetWindowText(m_szPassword[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabasePrivilegesDialog::OnEditchangePasswordConfirmation()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabasePrivilegesDialog::OnOK()
{
	INT  nUser;
	INT  nUsers;
	INT  nDatabase;
	INT  nDatabases;
	CStringArray  szUsers;
	CStringArray  szPasswords;
	CUIntArray  nPrivileges;
	CDatabases  cDatabases;
	CDatabaseProfiles  pDatabases;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CHourglassCursor  cCursor;

	for (nUser = 0, nUsers = (GetDatabase()->GetUsers(szUsers, szPasswords, nPrivileges) >= 0) ? (INT)szUsers.GetSize() : -1; nUser < nUsers; nUser++)
	{
		if (szUsers.GetAt(nUser) == GetAccountUserName())
		{
			szPasswords.SetAt(nUser, m_szPassword[0]);
			nPrivileges.SetAt(nUser, m_nPrivileges[0]);
			break;
		}
	}
	for (nDatabase = 0, nDatabases = (nUser < nUsers) ? ((cDatabases.GetDatabases(pDatabases, TRUE)) ? (INT)pDatabases.GetSize() : -1) : -1; nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetName() == GetAccountDatabase() && pDatabaseProfileInfo->GetSpacecraft() == GetAccountSpacecraftName() && !pDatabaseProfileInfo->GetServer().CompareNoCase(GetAccountComputerName()))
		{
			pDatabaseProfileInfo->SetUsers(szUsers, szPasswords, nPrivileges);
			GetDatabase()->SetUsers(szUsers, szPasswords, nPrivileges);
			if (cDatabases.SetDatabases(pDatabases)) break;
		}
	}
	ShowMessage(((nDatabase == nDatabases  &&  nDatabases > 0) || nDatabases < 0) ? SYSTEM_WARNING_DATABASE_UPDATE_FAILURE : SYSTEM_NOERROR);
	EndDialog(IDOK);
}

void CDatabasePrivilegesDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabasePrivilegesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_PRIVILEGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabasePrivilegesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_PRIVILEGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseValidityDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseValidityDialog, CLocaleDialog)

CDatabaseValidityDialog::CDatabaseValidityDialog(CWnd *pParentWnd) : CLocaleDialog(CDatabaseValidityDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDatabaseValidityDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CDatabaseValidityDialog::DoModal()
{
	INT  nDatabase;
	INT  nDatabases;
	CDatabases  cDatabases;
	CDatabaseProfiles  pDatabases;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	for (nDatabase = 0, nDatabases = (cDatabases.GetDatabases(pDatabases, TRUE)) ? (INT)pDatabases.GetSize() : 0; nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetName() == GetAccountDatabase() && pDatabaseProfileInfo->GetSpacecraft() == GetAccountSpacecraftName() && !pDatabaseProfileInfo->GetServer().CompareNoCase(GetAccountComputerName()))
		{
			pDatabaseProfileInfo->GetValidity(m_tDatabaseValidity[0][0], m_tDatabaseValidity[0][1]);
			m_tDatabaseValidity[1][0] = m_tDatabaseValidity[0][0];
			m_tDatabaseValidity[1][1] = m_tDatabaseValidity[0][1];
			m_bDatabaseValidity = TRUE;
			return CLocaleDialog::DoModal();
		}
	}
	return IDCANCEL;
}
INT_PTR CDatabaseValidityDialog::DoModal(LPCTSTR pszDatabaseName, CTimeKey &tValidityStartTime, CTimeKey &tValidityStopTime)
{
	INT_PTR  nResult;

	for (m_tDatabaseValidity[0][0] = m_tDatabaseValidity[1][0] = tValidityStartTime, m_tDatabaseValidity[0][1] = m_tDatabaseValidity[1][1] = tValidityStopTime, m_bDatabaseValidity = FALSE; (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		tValidityStartTime = m_tDatabaseValidity[0][0];
		tValidityStopTime = m_tDatabaseValidity[0][1];
		break;
	}
	return nResult;
}

VOID CDatabaseValidityDialog::ShowValidityInfo()
{
	Timespinbox_SetTime(GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME), (m_tDatabaseValidity[0][0] > 0) ? m_tDatabaseValidity[0][0] : CTime::GetCurrentTime().GetTime());
	Timespinbox_SetTime(GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME), (m_tDatabaseValidity[0][1] > 0) ? m_tDatabaseValidity[0][1] : CTime::GetCurrentTime().GetTime());
	CheckRadioButton(IDC_DATABASE_VALIDITY_INTERVAL_UNLIMITED, IDC_DATABASE_VALIDITY_INTERVAL_LIMITED, (m_tDatabaseValidity[0][0] > 0 && m_tDatabaseValidity[0][1] > 0 && m_tDatabaseValidity[0][0] <= m_tDatabaseValidity[0][1]) ? IDC_DATABASE_VALIDITY_INTERVAL_LIMITED : IDC_DATABASE_VALIDITY_INTERVAL_UNLIMITED);
	GetDlgItem(IDC_DATABASE_VALIDITY_NAME)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_DATABASE_VALIDITY_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_NAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_NOTE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_NOTE_TEXT)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_NOTE_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_UNLIMITED)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED));
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED));
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED));
}

VOID CDatabaseValidityDialog::AdjustToPrivileges()
{
	AccessControl(IDC_DATABASE_VALIDITY_INTERVAL_UNLIMITED, CheckDatabasePrivilege(DATABASE_PRIVILEGE_VALIDITY_CHANGE));
	AccessControl(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED, CheckDatabasePrivilege(DATABASE_PRIVILEGE_VALIDITY_CHANGE));
	AccessControl(IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_VALIDITY_CHANGE));
	AccessControl(IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_VALIDITY_CHANGE));
}

BOOL CDatabaseValidityDialog::IsModified() CONST
{
	return((m_tDatabaseValidity[0][0] != m_tDatabaseValidity[1][0] || m_tDatabaseValidity[0][1] != m_tDatabaseValidity[1][1]) ? TRUE : FALSE);
}

void CDatabaseValidityDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseValidityDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseValidityDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabaseValidityDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_VALIDITY_INTERVAL_UNLIMITED, OnUnlimitedValidity)
	ON_BN_CLICKED(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED, OnLimitedValidity)
	ON_BN_CLICKED(IDC_DATABASE_VALIDITY_HELP, OnHelp)
	ON_CONTROL(TSBXN_CHANGE, IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME, OnSpinchangeValidityStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME, OnSpinchangeValidityStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseValidityDialog message handlers

BOOL CDatabaseValidityDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	ShowValidityInfo();
	AdjustToPrivileges();
	return TRUE;
}

void CDatabaseValidityDialog::OnUnlimitedValidity()
{
	m_tDatabaseValidity[0][0] = 0;
	m_tDatabaseValidity[0][1] = 0;
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseValidityDialog::OnLimitedValidity()
{
	CTimeKey  tStartTime;
	CTimeKey  tStopTime(tStartTime.GetYear() + 1, tStartTime.GetDayOfYear(), tStartTime.GetHour(), tStartTime.GetMinute(), tStartTime.GetSecond());

	Timespinbox_SetTime(GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME), (m_tDatabaseValidity[0][0] = tStartTime));
	Timespinbox_SetTime(GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME), (m_tDatabaseValidity[0][1] = tStopTime));
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseValidityDialog::OnSpinchangeValidityStartTime()
{
	CTimeKey  tValidity[2];

	tValidity[0] = Timespinbox_GetTime(GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME));
	tValidity[1] = Timespinbox_GetTime(GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME));
	Timespinbox_SetTime(GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME), (tValidity[1] = (tValidity[0] >= tValidity[1]) ? min(tValidity[0].GetTime() + 1, MAX_TIMEKEY) : tValidity[1]));
	m_tDatabaseValidity[0][0] = (IsDlgButtonChecked(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED)) ? tValidity[0] : m_tDatabaseValidity[0][0].GetTime();
	m_tDatabaseValidity[0][1] = (IsDlgButtonChecked(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED)) ? tValidity[1] : m_tDatabaseValidity[0][1].GetTime();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseValidityDialog::OnSpinchangeValidityStopTime()
{
	CTimeKey  tValidity[2];

	tValidity[0] = Timespinbox_GetTime(GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME));
	tValidity[1] = Timespinbox_GetTime(GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STOPTIME));
	Timespinbox_SetTime(GetDlgItem(IDC_DATABASE_VALIDITY_INTERVAL_STARTTIME), (tValidity[0] = (tValidity[0] >= tValidity[1]) ? max(tValidity[1].GetTime() - 1, 0) : tValidity[0]));
	m_tDatabaseValidity[0][0] = (IsDlgButtonChecked(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED)) ? tValidity[0] : m_tDatabaseValidity[0][0].GetTime();
	m_tDatabaseValidity[0][1] = (IsDlgButtonChecked(IDC_DATABASE_VALIDITY_INTERVAL_LIMITED)) ? tValidity[1] : m_tDatabaseValidity[0][1].GetTime();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseValidityDialog::OnOK()
{
	INT  nDatabase;
	INT  nDatabases;
	CDatabases  cDatabases;
	CDatabaseProfiles  pDatabases;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CHourglassCursor  cCursor;

	for (nDatabase = 0, nDatabases = (m_bDatabaseValidity && cDatabases.GetDatabases(pDatabases, TRUE)) ? (INT)pDatabases.GetSize() : 0; nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetName() == GetAccountDatabase() && pDatabaseProfileInfo->GetSpacecraft() == GetAccountSpacecraftName() && !pDatabaseProfileInfo->GetServer().CompareNoCase(GetAccountComputerName()))
		{
			pDatabaseProfileInfo->SetValidity(m_tDatabaseValidity[0][0], m_tDatabaseValidity[0][1]);
			cDatabases.SetDatabases(pDatabases);
			break;
		}
	}
	EndDialog(IDOK);
}

void CDatabaseValidityDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabaseValidityDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEVALIDITYDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseValidityDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEVALIDITYDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CNewDialog dialog

IMPLEMENT_DYNCREATE(CNewDialog, CLocaleDialog)

CNewDialog::CNewDialog(CWnd *pParentWnd) : CLocaleDialog(CNewDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CNewDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CNewDialog::Initialize()
{
	m_szDatabaseDataFile[0].Empty();
	m_szDatabaseDataFile[1].Empty();
	m_szDatabaseLogsFile[0].Empty();
	m_szDatabaseLogsFile[1].Empty();
	m_tDatabaseValidity[0] = m_tDatabaseValidity[1] = 0;
	m_nDatabaseDataSize[0] = m_nDatabaseDataSize[1] = m_nDatabaseDataSize[2] = 0;
	m_nDatabaseLogsSize[0] = m_nDatabaseLogsSize[1] = m_nDatabaseLogsSize[2] = 0;
	m_szDatabaseUsers.Add(GetAccountUserName());
	m_szDatabasePasswords.Add(GetAccountPassword());
	m_nDatabasePrivileges.Add(DATABASE_PRIVILEGES_ALL);
	m_bDatabaseReadOnly = FALSE;
	return((LoadDatabases() >= 0) ? TRUE : FALSE);
}

INT_PTR CNewDialog::DoModal()
{
	CStringArray  szDocuments;

	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TMPACKET));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TCFUNCTION));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TCSEQUENCE));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TCPROCEDURE));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TMPARAMETER));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_TCPARAMETER));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_OBPROCESSOR));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_ALPHANUMERICDISPLAY));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_GRAPHICDISPLAY));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_MIMICSDISPLAY));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_PARAMETEROBSERVATIONDISPLAY));
	szDocuments.Add(STRING(IDS_NEWDIALOG_DATABASETYPE_AUTOMATIONSCRIPT));
	return DoModal(szDocuments);
}
INT_PTR CNewDialog::DoModal(CONST CStringArray &szDocuments)
{
	m_szDatabaseDocuments.Copy(szDocuments);
	return CLocaleDialog::DoModal();
}

BOOL CNewDialog::EnumDatabaseTypes()
{
	INT  nIndex;
	INT  nDocument;
	INT  nDocuments;
	CStringArray  szComputers;

	for (nDocument = 0, nDocuments = (INT)m_szDatabaseDocuments.GetSize(), GetNetworkBrowseService()->EnumNetworkComputers(szComputers); nDocument < nDocuments; nDocument++)
	{
		if ((m_szDatabaseDocuments.GetAt(nDocument) == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && ((CheckAccountPrivilege(PRIVILEGE_DATABASE_CREATE) && szComputers.GetSize() >= 1) || (CheckAccountPrivilege(PRIVILEGE_DATABASE_REMOTECREATE) && szComputers.GetSize() > 1))) || (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && m_pDatabases.Find(GetAccountDatabase()) >= 0 && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_TMPACKET) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_TCFUNCTION) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_TCSEQUENCE) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_TCPROCEDURE) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPROCEDURE_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_TMPARAMETER) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_TCPARAMETER) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_OBPROCESSOR) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_ALPHANUMERICDISPLAY) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_GRAPHICDISPLAY) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_MIMICSDISPLAY) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_PARAMETEROBSERVATIONDISPLAY) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_POD_CHANGE)) && (m_szDatabaseDocuments.GetAt(nDocument) != STRING(IDS_NEWDIALOG_DATABASETYPE_AUTOMATIONSCRIPT) || CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE))))
		{
			SendDlgItemMessage(IDC_NEW_DOCUMENT_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szDatabaseDocuments.GetAt(nDocument));
			continue;
		}
	}
	SendDlgItemMessage(IDC_NEW_DOCUMENT_TYPE, CB_SETCURSEL, ((nIndex = (INT)SendDlgItemMessage(IDC_NEW_DOCUMENT_TYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE))) >= 0) ? ((!CheckAccountPrivilege(PRIVILEGE_DATABASE_CREATE)) ? ((!nIndex) ? (nIndex + 1) : 0) : nIndex) : 0);
	GetDlgItem(IDC_NEW_DOCUMENT_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_NEW_DOCUMENT_TYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_TYPE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_NEW_DOCUMENT_TYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_TYPE)->EnableWindow((SendDlgItemMessage(IDC_NEW_DOCUMENT_TYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_NEW_DOCUMENT_TYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CNewDialog::EnumDatabaseStandard()
{
	INT  nStandard;

	for (nStandard = MINDATABASESTANDARD; nStandard <= MAXDATABASESTANDARD; nStandard++)
	{
		SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(nStandard));
		continue;
	}
	return((SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CNewDialog::EnumDatabaseImplementation()
{
	INT  nImplementation;

	for (nImplementation = MINDATABASEIMPLEMENTATION; nImplementation <= MAXDATABASEIMPLEMENTATION; nImplementation++)
	{
		SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(nImplementation));
		continue;
	}
	return((SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CNewDialog::EnumDatabaseImplementationFloatingPoint()
{
	INT  nImplementation;

	for (nImplementation = MINDATABASEIMPLEMENTATIONFLOATINGPOINT; nImplementation <= MAXDATABASEIMPLEMENTATIONFLOATINGPOINT; nImplementation++)
	{
		SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_FLOATINGPOINT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(nImplementation));
		continue;
	}
	return((SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_FLOATINGPOINT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CNewDialog::EnumSpacecrafts()
{
	INT  nSpacecraft;
	INT  nSpacecrafts;
	CString  szSpacecraft;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_RESETCONTENT);
	for (nSpacecraft = 0, nSpacecrafts = (INT)m_pDatabases.GetSize(); nSpacecraft < nSpacecrafts; nSpacecraft++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nSpacecraft)) != (CDatabaseProfileInfo *)NULL)
		{
			if (SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szSpacecraft = pDatabaseProfileInfo->GetSpacecraft())) == CB_ERR)
			{
				SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szSpacecraft);
				continue;
			}
		}
	}
	SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountSpacecraftName()), 0));
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT_STATIC)->EnableWindow();
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->EnableWindow();
	return TRUE;
}

BOOL CNewDialog::EnumServers()
{
	INT  nServer;
	INT  nServers;
	CString  szServer;
	CStringArray  szServers;
	CComputerToken  cComputerToken;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_RESETCONTENT);
	for (nServer = 0, nServers = (INT)m_pDatabases.GetSize(); nServer < nServers; nServer++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nServer)) != (CDatabaseProfileInfo *)NULL)
		{
			if (SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szServer = pDatabaseProfileInfo->GetServer())) == CB_ERR)
			{
				SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szServer);
				continue;
			}
		}
	}
	for (nServer = 0, nServers = GetNetworkBrowseService()->EnumNetworkComputers(szServers), szServer = cComputerToken.GetComputerName(); nServer < nServers; nServer++)
	{
		if (SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szServers.GetAt(nServer)) == CB_ERR)
		{
			SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szServers.GetAt(nServer));
			continue;
		}
	}
	SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szServer), 0));
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES)->EnableWindow((SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER_STATIC)->EnableWindow((SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->EnableWindow((SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CNewDialog::ShowDatabaseInfo()
{
	UINT  nType;
	INT  nDatabase;
	INT  nDatabases;
	CString  szType;
	CString  szDatabase;
	CString  szFileName;
	CString  szServer[2];
	CString  szSpacecraft;
	CString  szFileLocation;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_NEW_DOCUMENT_TYPE)->GetWindowText(szType);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer[0]);
	for (nDatabase = 0, nDatabases = (szType != STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? (INT)m_pDatabases.GetSize() : -1; nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetName() == GetAccountDatabase() && pDatabaseProfileInfo->GetSpacecraft() == GetAccountSpacecraftName() && pDatabaseProfileInfo->GetServer() == szServer[0])
		{
			nType = pDatabaseProfileInfo->GetType();
			szDatabase = pDatabaseProfileInfo->GetName();
			szServer[1] = pDatabaseProfileInfo->GetServer();
			szFileName = pDatabaseProfileInfo->GetFileName();
			szSpacecraft = pDatabaseProfileInfo->GetSpacecraft();
			szFileLocation = ConstructDatabaseFileLocation(szFileName);
			szFileName = ConstructDatabaseFileName(szFileName);
			break;
		}
	}
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->SetWindowText((nDatabase < nDatabases) ? (LPCTSTR)szDatabase : EMPTYSTRING);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILENAME)->SetWindowText((nDatabase < nDatabases) ? (LPCTSTR)szFileName : EMPTYSTRING);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION)->SetWindowText((nDatabase < nDatabases) ? (LPCTSTR)szFileLocation : EMPTYSTRING);
	SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_SETCURSEL, (nDatabase < nDatabases) ? (WPARAM)SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szServer[0]) : ((nDatabases < 0) ? (WPARAM)SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, CB_GETCURSEL) : (WPARAM)-1));
	SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_SETCURSEL, (nDatabase < nDatabases) ? (WPARAM)SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szSpacecraft) : ((nDatabases < 0) ? (WPARAM)max(SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountSpacecraftName()), 0) : (WPARAM)-1));
	SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD, CB_SETCURSEL, (nDatabase < nDatabases) ? (WPARAM)SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD, CB_FINDSTRINGEXACT, (WPARAM)-1, (nType & DATABASE_TYPE_STANDARD_PCM) ? (LPARAM)STRING(IDS_DATABASE_STANDARD_PCM) : ((nType & DATABASE_TYPE_STANDARD_CCSDS) ? (LPARAM)STRING(IDS_DATABASE_STANDARD_CCSDS) : (LPARAM)EMPTYSTRING)) : ((nDatabases < 0) ? (WPARAM)max(SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_DATABASE_STANDARD_CCSDS)), 0) : (WPARAM)-1));
	SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION, CB_SETCURSEL, (nDatabase < nDatabases) ? (WPARAM)SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION, CB_FINDSTRINGEXACT, (WPARAM)-1, (nType & DATABASE_TYPE_IMPLEMENTATION_SCOS) ? (LPARAM)STRING(IDS_DATABASE_IMPLEMENTATION_SCOS) : ((nType & DATABASE_TYPE_IMPLEMENTATION_ALTEL) ? (LPARAM)STRING(IDS_DATABASE_IMPLEMENTATION_ALTEL) : (LPARAM)EMPTYSTRING)) : ((nDatabases < 0) ? (WPARAM)max(SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_DATABASE_IMPLEMENTATION_ALTEL)), 0) : (WPARAM)-1));
	SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_FLOATINGPOINT, CB_SETCURSEL, (nDatabase < nDatabases) ? (WPARAM)SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_FLOATINGPOINT, CB_FINDSTRINGEXACT, (WPARAM)-1, (nType & DATABASE_TYPE_FLOATINGPOINTFORMAT_IEEE) ? (LPARAM)STRING(IDS_DATABASE_IMPLEMENTATIONFLOATINGPOINT_IEEE) : ((nType & DATABASE_TYPE_FLOATINGPOINTFORMAT_USAF) ? (LPARAM)STRING(IDS_DATABASE_IMPLEMENTATIONFLOATINGPOINT_USAF) : (LPARAM)EMPTYSTRING)) : ((nDatabases < 0) ? (WPARAM)max(SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_FLOATINGPOINT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_DATABASE_IMPLEMENTATIONFLOATINGPOINT_IEEE)), 0) : (WPARAM)-1));
	CheckDlgButton(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL, (nDatabase < nDatabases) ? ((nType & DATABASE_TYPE_GLOBAL) ? TRUE : FALSE) : ((nDatabases < 0) ? CheckDatabases() : FALSE));
	CheckDlgButton(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL, (nDatabase < nDatabases) ? ((nType & DATABASE_TYPE_LOCAL) ? TRUE : FALSE) : ((nDatabases < 0) ? !CheckDatabases() : FALSE));
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME_STATIC)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT_STATIC)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER_STATIC)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_SCOPE)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? ((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? CheckDatabases() : TRUE) : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_COMPATIBILITY)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD_STATIC)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_STATIC)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_FLOATINGPOINT)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILES)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILENAME_STATIC)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILENAME)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION_STATIC)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILEBROWSE)->EnableWindow((nDatabase < nDatabases || nDatabases < 0) ? ((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE) : FALSE);
	AccessControl(IDC_NEW_DOCUMENT_PROPERTIES_NAME, (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE);
	AccessControl(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE);
	AccessControl(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE, TRUE, FALSE);
	AccessControl(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL, (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE);
	AccessControl(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL, (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE);
	AccessControl(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD, (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE);
	AccessControl(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION, (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE);
	AccessControl(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_FLOATINGPOINT, (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE);
	AccessControl(IDC_NEW_DOCUMENT_PROPERTIES_FILENAME, (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE);
	AccessControl(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION, (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE)) ? TRUE : FALSE);
}

BOOL CNewDialog::SaveDatabases()
{
	CDatabases  cDatabases;

	return cDatabases.SetDatabases(m_pDatabases);
}

BOOL CNewDialog::LoadDatabases()
{
	CDatabases  cDatabases;

	return cDatabases.GetDatabases(m_pDatabases, TRUE);
}

BOOL CNewDialog::CheckDatabases() CONST
{
	CString  szSpacecraft;

	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
	return CheckDatabases(szSpacecraft);
}
BOOL CNewDialog::CheckDatabases(LPCTSTR pszSpacecraft) CONST
{
	INT  nDatabase;
	INT  nDatabases;
	CDatabases  cDatabases;
	CDatabaseProfiles  pDatabases;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	for (nDatabase = 0, nDatabases = (cDatabases.GetDatabases(pDatabases)) ? (INT)pDatabases.GetSize() : 0; nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetSpacecraft() == pszSpacecraft)
		{
			if (pDatabaseProfileInfo->GetType() & DATABASE_TYPE_GLOBAL) break;
			continue;
		}
	}
	return((nDatabase == nDatabases) ? TRUE : FALSE);
}

BOOL CNewDialog::UpdateDatabase(CONST CDatabaseProfileInfo *pDatabaseProfileInfo)
{
	CBinaryDatabase  cBinaryDatabase;

	return cBinaryDatabase.Update(pDatabaseProfileInfo);
}

BOOL CNewDialog::FindDatabase() CONST
{
	CString  szDatabase;
	CDatabaseProfileInfo  cDatabaseProfileInfo;

	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->GetWindowText(szDatabase);
	return FindDatabase(szDatabase, &cDatabaseProfileInfo);
}
BOOL CNewDialog::FindDatabase(LPCTSTR pszDatabase, CDatabaseProfileInfo *pDatabaseProfileInfo) CONST
{
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szSpacecraft;
	CDatabases  cDatabases;
	CDatabaseProfiles  pDatabases;

	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
	for (nDatabase = 0, nDatabases = ((!szServer.CompareNoCase(cDatabases.GetComputerName()) || cDatabases.SetComputerName(szServer)) && cDatabases.GetDatabases(pDatabases, TRUE)) ? (INT)pDatabases.GetSize() : 0; nDatabase < nDatabases; nDatabase++)
	{
		if (pDatabases.GetAt(nDatabase)->GetSpacecraft() == szSpacecraft  &&  !pDatabases.GetAt(nDatabase)->GetName().CompareNoCase(pszDatabase))
		{
			pDatabaseProfileInfo->Copy(pDatabases.GetAt(nDatabase));
			break;
		}
	}
	return((nDatabase < nDatabases) ? TRUE : FALSE);
}

CString CNewDialog::GetDatabaseFileName() CONST
{
	INT  nPos;
	CString  szFileName[4];
	CString  szFileLocation;
	CLogicalDrives  cDrives;

	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILENAME)->GetWindowText(szFileName[0]);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION)->GetWindowText(szFileLocation);
	for (nPos = lstrlen((szFileName[1] = STRING(IDS_DATABASE_BINARY_UPDATENAME))) - 1, szFileName[2] = (!szFileLocation.IsEmpty()) ? ((szFileLocation.GetLength() > 1 && szFileLocation[szFileLocation.GetLength() - 1] != cDrives.GetDriveDelimiter() && szFileLocation[szFileLocation.GetLength() - 1] != cDrives.GetPathDelimiter()) ? CString(szFileLocation + cDrives.GetPathDelimiter() + szFileName[0]) : (szFileLocation + szFileName[0])) : szFileName[0], szFileName[3].Format(STRING(IDS_DATABASE_BINARY_FILENAME), (LPCTSTR)szFileName[2]); nPos >= 0; nPos--)
	{
		if (!_istalpha(szFileName[1].GetAt(nPos))) break;
		continue;
	}
	if (nPos >= 0)
	{
		if (!szFileName[2].Right(szFileName[1].Mid(nPos).GetLength()).CompareNoCase(szFileName[1].Mid(nPos)))
		{
			szFileName[3].Format(STRING(IDS_DATABASE_BINARY_FILENAME), (LPCTSTR)szFileName[2].Left(szFileName[2].GetLength() - szFileName[1].Mid(nPos).GetLength()));
			szFileName[2] = szFileName[3];
		}
	}
	return((szFileName[2] = (nPos >= 0 && szFileName[2].Find(szFileName[1].GetAt(nPos)) < 0) ? szFileName[3] : szFileName[2]));
}

CString CNewDialog::GetDatabaseUpdateFileName() CONST
{
	INT  nPos[2];
	CString  szFileName[4];

	if (!GetFileTitle((szFileName[0] = szFileName[1] = GetDatabaseFileName()), szFileName[2].GetBufferSetLength(GetDatabaseFileName().GetLength()), GetDatabaseFileName().GetLength() + 1))
	{
		for (szFileName[2].ReleaseBuffer(), szFileName[0].MakeReverse(), szFileName[2].MakeReverse(), szFileName[0].MakeUpper(), szFileName[2].MakeUpper(); (nPos[0] = szFileName[0].Find(szFileName[2])) >= 0; )
		{
			for (nPos[1] = lstrlen((szFileName[3] = STRING(IDS_DATABASE_BINARY_UPDATENAME))) - 1, szFileName[2].MakeReverse(); nPos[1] >= 0; nPos[1]--)
			{
				if (!_istalpha(szFileName[3].GetAt(nPos[1]))) break;
				continue;
			}
			szFileName[1] = szFileName[1].Left(szFileName[1].GetLength() - lstrlen(szFileName[2]) - nPos[0]);
			szFileName[2] = ((nPos[1] = (nPos[1] >= 0) ? szFileName[2].ReverseFind(szFileName[3].GetAt(nPos[1])) : -1) >= 0) ? szFileName[2].Left(nPos[1]) : szFileName[2];
			szFileName[3].Format(STRING(IDS_DATABASE_BINARY_UPDATENAME), (LPCTSTR)(szFileName[1] + szFileName[2]));
			return szFileName[3];
		}
		return EMPTYSTRING;
	}
	szFileName[2].ReleaseBuffer();
	return szFileName[3];
}

CString CNewDialog::GetDatabaseLibraryFileName() CONST
{
	INT  nPos;
	CString  szDatabase;
	CString  szFileName[4];
	CString  szFileLocation;
	CLogicalDrives  cDrives;

	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->GetWindowText(szDatabase);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION)->GetWindowText(szFileLocation);
	for (nPos = lstrlen((szFileName[1] = STRING(IDS_DATABASE_LIBRARY_UPDATENAME))) - 1, szFileName[0].Format(STRING(IDS_DATABASE_BINARY_FILENAME), (LPCTSTR)szDatabase), szFileName[2] = (!szFileLocation.IsEmpty()) ? ((szFileLocation.GetLength() > 1 && szFileLocation[szFileLocation.GetLength() - 1] != cDrives.GetDriveDelimiter() && szFileLocation[szFileLocation.GetLength() - 1] != cDrives.GetPathDelimiter()) ? CString(szFileLocation + cDrives.GetPathDelimiter() + szFileName[0]) : (szFileLocation + szFileName[0])) : szFileName[0]; nPos >= 0; nPos--)
	{
		if (!_istalpha(szFileName[1].GetAt(nPos))) break;
		continue;
	}
	szFileName[3].Format(STRING(IDS_DATABASE_LIBRARY_FILENAME), (nPos >= 0 && szFileName[2].ReverseFind(szFileName[1].GetAt(nPos)) >= 0) ? (LPCTSTR)szFileName[2].Left(szFileName[2].ReverseFind(szFileName[1].GetAt(nPos))) : (LPCTSTR)szFileName[2]);
	return szFileName[3];
}

CString CNewDialog::GetDatabaseLibraryUpdateFileName() CONST
{
	INT  nPos[2];
	CString  szFileName[4];

	if (!GetFileTitle((szFileName[0] = szFileName[1] = GetDatabaseLibraryFileName()), szFileName[2].GetBufferSetLength(GetDatabaseLibraryFileName().GetLength()), GetDatabaseLibraryFileName().GetLength() + 1))
	{
		for (szFileName[2].ReleaseBuffer(), szFileName[0].MakeReverse(), szFileName[2].MakeReverse(), szFileName[0].MakeUpper(), szFileName[2].MakeUpper(); (nPos[0] = szFileName[0].Find(szFileName[2])) >= 0; )
		{
			for (nPos[1] = lstrlen((szFileName[3] = STRING(IDS_DATABASE_LIBRARY_UPDATENAME))) - 1, szFileName[2].MakeReverse(); nPos[1] >= 0; nPos[1]--)
			{
				if (!_istalpha(szFileName[3].GetAt(nPos[1]))) break;
				continue;
			}
			szFileName[1] = szFileName[1].Left(szFileName[1].GetLength() - lstrlen(szFileName[2]) - nPos[0]);
			szFileName[2] = ((nPos[1] = (nPos[1] >= 0) ? szFileName[2].ReverseFind(szFileName[3].GetAt(nPos[1])) : -1) >= 0) ? szFileName[2].Left(nPos[1]) : szFileName[2];
			szFileName[3].Format(STRING(IDS_DATABASE_LIBRARY_UPDATENAME), (LPCTSTR)(szFileName[1] + szFileName[2]));
			return szFileName[3];
		}
		return EMPTYSTRING;
	}
	szFileName[2].ReleaseBuffer();
	return szFileName[3];
}

CString CNewDialog::GetDatabaseLogFileName() CONST
{
	INT  nPos[2];
	CString  szFileName[4];

	if (!GetFileTitle((szFileName[0] = szFileName[1] = GetDatabaseFileName()), szFileName[2].GetBufferSetLength(GetDatabaseFileName().GetLength()), GetDatabaseFileName().GetLength() + 1))
	{
		for (szFileName[2].ReleaseBuffer(), szFileName[0].MakeReverse(), szFileName[2].MakeReverse(), szFileName[0].MakeUpper(), szFileName[2].MakeUpper(); (nPos[0] = szFileName[0].Find(szFileName[2])) >= 0; )
		{
			for (nPos[1] = lstrlen((szFileName[3] = STRING(IDS_DATABASE_LOGGING_FILENAME))) - 1, szFileName[2].MakeReverse(); nPos[1] >= 0; nPos[1]--)
			{
				if (!_istalpha(szFileName[3].GetAt(nPos[1]))) break;
				continue;
			}
			szFileName[1] = szFileName[1].Left(szFileName[1].GetLength() - lstrlen(szFileName[2]) - nPos[0]);
			szFileName[2] = ((nPos[1] = (nPos[1] >= 0) ? szFileName[2].ReverseFind(szFileName[3].GetAt(nPos[1])) : -1) >= 0) ? szFileName[2].Left(nPos[1]) : szFileName[2];
			szFileName[3].Format(STRING(IDS_DATABASE_LOGGING_FILENAME), (LPCTSTR)(szFileName[1] + szFileName[2]));
			return szFileName[3];
		}
		return EMPTYSTRING;
	}
	szFileName[2].ReleaseBuffer();
	return szFileName[3];
}

CString CNewDialog::ConstructDatabaseFileName(LPCTSTR pszPathName) CONST
{
	INT  nPos;
	CString  szFileTitle;

	if (!GetFileTitle(pszPathName, szFileTitle.GetBufferSetLength(max(GetFileTitle(pszPathName, (LPTSTR)NULL, 0) - 1, 0)), GetFileTitle(pszPathName, (LPTSTR)NULL, 0)))
	{
		for (nPos = lstrlen(pszPathName) - lstrlen(szFileTitle), szFileTitle.ReleaseBuffer(); nPos >= 0; nPos--)
		{
			if (!_tcsnicmp(&pszPathName[nPos], szFileTitle, lstrlen(szFileTitle))) break;
			continue;
		}
		return((nPos >= 0) ? (LPCTSTR)CString(pszPathName).Mid(nPos) : EMPTYSTRING);
	}
	szFileTitle.ReleaseBuffer();
	szFileTitle.Empty();
	return szFileTitle;
}

CString CNewDialog::ConstructDatabaseFileLocation(LPCTSTR pszPathName) CONST
{
	INT  nPos;
	CString  szDrive;
	CString  szFilePath;
	CString  szFileTitle;
	CLogicalDrives  cDrives;

	for (nPos = lstrlen(pszPathName), szDrive = cDrives.ExtractDrive(pszPathName), GetFileTitle(pszPathName, szFileTitle.GetBufferSetLength(max(GetFileTitle(pszPathName, (LPTSTR)NULL, 0) - 1, 0)), ::GetFileTitle(pszPathName, (LPTSTR)NULL, 0)), szFileTitle.ReleaseBuffer(), nPos -= szFileTitle.GetLength(), szFilePath = (nPos > 0) ? pszPathName : EMPTYSTRING; nPos >= 0; nPos--)
	{
		if (!_tcsnicmp(&pszPathName[nPos], szFileTitle, szFileTitle.GetLength())) break;
		continue;
	}
	if (nPos >= 0)
	{
		szFilePath = (nPos > 0 && cDrives.GetPathDelimiter() == pszPathName[nPos - 1]) ? CString(pszPathName).Left(nPos - 1) : CString(pszPathName).Left(nPos);
		return szFilePath;
	}
	return EMPTYSTRING;
}

BOOL CNewDialog::CreateTMPacketsForm()
{
	CTMPacketWnd  *pTMPacketWnd;

	return(((pTMPacketWnd = new CTMPacketWnd)) ? pTMPacketWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreateTCFunctionsForm()
{
	CTCFunctionWnd  *pTCFunctionWnd;

	return(((pTCFunctionWnd = new CTCFunctionWnd)) ? pTCFunctionWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreateTCSequencesForm()
{
	CTCSequenceWnd  *pTCSequenceWnd;

	return(((pTCSequenceWnd = new CTCSequenceWnd)) ? pTCSequenceWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreateTCProceduresForm()
{
	CTCProcedureWnd  *pTCProcedureWnd;

	return(((pTCProcedureWnd = new CTCProcedureWnd)) ? pTCProcedureWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreateTMParametersForm()
{
	CTMParameterWnd  *pTMParameterWnd;

	return(((pTMParameterWnd = new CTMParameterWnd)) ? pTMParameterWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreateTCParametersForm()
{
	CTCParameterWnd  *pTCParameterWnd;

	return(((pTCParameterWnd = new CTCParameterWnd)) ? pTCParameterWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreateOBProcessorsForm()
{
	COBProcessorWnd  *pOBProcessorWnd;

	return(((pOBProcessorWnd = new COBProcessorWnd)) ? pOBProcessorWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreateAND()
{
	CANDWnd  *pANDWnd;

	return(((pANDWnd = new CANDWnd)) ? pANDWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreateGRD()
{
	CGRDWnd  *pGRDWnd;

	return(((pGRDWnd = new CGRDWnd)) ? pGRDWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreateMMD()
{
	CMMDWnd  *pMMDWnd;

	return(((pMMDWnd = new CMMDWnd)) ? pMMDWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreatePOD()
{
	CPODWnd  *pPODWnd;

	return(((pPODWnd = new CPODWnd)) ? pPODWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::CreateScript()
{
	CScriptWnd  *pScriptWnd;

	return(((pScriptWnd = new CScriptWnd)) ? pScriptWnd->Create(GetMainWnd()) : FALSE);
}

BOOL CNewDialog::IsModified() CONST
{
	return(Combobox_GetText(GetDlgItem(IDC_NEW_DOCUMENT_TYPE), (INT)GetDlgItem(IDC_NEW_DOCUMENT_TYPE)->SendMessage(CB_GETCURSEL)) != STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) || (!m_szDatabaseDataFile[0].IsEmpty() && !m_szDatabaseLogsFile[0].IsEmpty() && m_nDatabaseDataSize[0] > 0 && m_nDatabaseDataSize[1] > 0 && m_nDatabaseLogsSize[0] > 0 && m_nDatabaseLogsSize[1] > 0 && !FindDatabase()));
}

BOOL CNewDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowTextLength() > 0 && GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowTextLength() > 0 && (IsDlgButtonChecked(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL) || IsDlgButtonChecked(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL)) && GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_FLOATINGPOINT)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILENAME)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void CNewDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CNewDialog::PostNcDestroy()
{
	m_pDatabases.RemoveAll();
	m_szDatabaseUsers.RemoveAll();
	m_szDatabasePasswords.RemoveAll();
	m_szDatabaseDocuments.RemoveAll();
	m_nDatabasePrivileges.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CNewDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CNewDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_NEW_DOCUMENT_PROPERTIES_DETAILS, OnDatabaseDetails)
	ON_BN_CLICKED(IDC_NEW_DOCUMENT_PROPERTIES_USERS, OnDatabaseUsers)
	ON_BN_CLICKED(IDC_NEW_DOCUMENT_PROPERTIES_VALIDITY, OnDatabaseValidity)
	ON_BN_CLICKED(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL, OnGlobalDatabaseType)
	ON_BN_CLICKED(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL, OnLocalDatabaseType)
	ON_BN_CLICKED(IDC_NEW_DOCUMENT_PROPERTIES_FILEBROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_NEW_DOCUMENT_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, OnEditchangeSpacecraft)
	ON_CBN_SELCHANGE(IDC_NEW_DOCUMENT_TYPE, OnSelchangeType)
	ON_CBN_SELCHANGE(IDC_NEW_DOCUMENT_PROPERTIES_SERVER, OnSelchangeServer)
	ON_CBN_SELCHANGE(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, OnSelchangeSpacecraft)
	ON_EN_CHANGE(IDC_NEW_DOCUMENT_PROPERTIES_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_NEW_DOCUMENT_PROPERTIES_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION, OnEditchangeFileLocation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewDialog message handlers

BOOL CNewDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	if (EnumDatabaseTypes() && EnumServers() && EnumSpacecrafts() && EnumDatabaseStandard() && EnumDatabaseImplementation() && EnumDatabaseImplementationFloatingPoint())
	{
		ShowDatabaseInfo();
		return FALSE;
	}
	return TRUE;
}

void CNewDialog::OnDatabaseDetails()
{
	CString  szServer;
	CString  szDatabase;
	CString  szStandard;
	CString  szSpacecraft;
	CDatabaseDetailsDialog  cDatabaseDetailsDialog(this);

	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->GetWindowText(szDatabase);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION)->GetWindowText(szStandard);
	cDatabaseDetailsDialog.DoModal(szServer, szSpacecraft, szDatabase, szStandard, m_szDatabaseDataFile[0], m_szDatabaseDataFile[1], m_nDatabaseDataSize[0], m_nDatabaseDataSize[1], m_nDatabaseDataSize[2], m_szDatabaseLogsFile[0], m_szDatabaseLogsFile[1], m_nDatabaseLogsSize[0], m_nDatabaseLogsSize[1], m_nDatabaseLogsSize[2], m_bDatabaseReadOnly);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnDatabaseUsers()
{
	CString  szDatabase;
	CDatabaseUsersDialog  cDatabaseUsersDialog(this);

	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->GetWindowText(szDatabase);
	cDatabaseUsersDialog.DoModal(szDatabase, m_szDatabaseUsers, m_szDatabasePasswords, m_nDatabasePrivileges);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnDatabaseValidity()
{
	CString  szDatabase;
	CDatabaseValidityDialog  cDatabaseValidityDialog(this);

	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->GetWindowText(szDatabase);
	cDatabaseValidityDialog.DoModal(szDatabase, m_tDatabaseValidity[0], m_tDatabaseValidity[1]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnGlobalDatabaseType()
{
	CheckDlgButton(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL, TRUE);
	CheckDlgButton(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL, FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnLocalDatabaseType()
{
	CheckDlgButton(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL, FALSE);
	CheckDlgButton(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL, TRUE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnBrowse()
{
	LPMALLOC  pIMalloc;
	LPITEMIDLIST  pItemIDList;
	TCHAR  szItemBuffer[MAX_PATH];
	TCHAR  szDisplayName[MAX_PATH];
	BROWSEINFO  sBrowseInfo = { 0 };

	if (SHGetMalloc(&pIMalloc) == NOERROR)
	{
		sBrowseInfo.hwndOwner = GetSafeHwnd();
		sBrowseInfo.pszDisplayName = szDisplayName;
		sBrowseInfo.lpszTitle = STRING(IDS_DIRECTORYBROWSEDIALOG_TITLE);
		if ((pItemIDList = SHBrowseForFolder(&sBrowseInfo)) != (LPITEMIDLIST)NULL)
		{
			if (SHGetPathFromIDList(pItemIDList, szItemBuffer)) GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION)->SetWindowText(szItemBuffer);
			pIMalloc->Free(pItemIDList);
		}
		pIMalloc->Release();
	}
	SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnSelchangeType()
{
	CString  szType;

	for (ShowDatabaseInfo(), GetDlgItem(IDC_NEW_DOCUMENT_TYPE)->GetWindowText(szType); szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE); )
	{
		SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_NAME, EM_SETSEL, 0, -1);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->SetFocus();
		break;
	}
	if (szType != STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && Check())
	{
		GetDlgItem(IDOK)->EnableWindow();
		GetDlgItem(IDOK)->SetFocus();
		return;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnSelchangeServer()
{
	INT  nType;
	INT  nTypes;
	CString  szServer;
	CString  szType[2];
	CComputerToken  cComputerToken;

	GetDlgItem(IDC_NEW_DOCUMENT_TYPE)->GetWindowText(szType[0]);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
	if (szType[0] == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && ((!szServer.CompareNoCase(cComputerToken.GetComputerName()) && !CheckAccountPrivilege(PRIVILEGE_DATABASE_CREATE)) || (szServer.CompareNoCase(cComputerToken.GetComputerName()) && !CheckAccountPrivilege(PRIVILEGE_DATABASE_REMOTECREATE))))
	{
		for (nType = 0, nTypes = (INT)SendDlgItemMessage(IDC_NEW_DOCUMENT_TYPE, CB_GETCOUNT); nType < nTypes; nType++)
		{
			if ((szType[1] = Combobox_GetText(GetDlgItem(IDC_NEW_DOCUMENT_TYPE), nType)) != szType[0]) break;
			continue;
		}
		SendDlgItemMessage(IDC_NEW_DOCUMENT_TYPE, CB_SETCURSEL, (nType < nTypes) ? nType : -1);
	}
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnSelchangeSpacecraft()
{
	CString  szType;
	CString  szDatabase;
	CString  szSpacecraft;
	CDatabaseProfileInfo  cDatabaseProfileInfo;

	for (szSpacecraft = Combobox_GetText(GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT), (INT)SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_GETCURSEL)); SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_GETCURSEL) >= 0 && !CheckDatabases(szSpacecraft); )
	{
		CheckDlgButton(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL, FALSE);
		CheckDlgButton(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL, TRUE);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL)->EnableWindow(FALSE);
		break;
	}
	for (; SendDlgItemMessage(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT, CB_GETCURSEL) < 0 || CheckDatabases(szSpacecraft); )
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL)->EnableWindow();
		break;
	}
	GetDlgItem(IDC_NEW_DOCUMENT_TYPE)->GetWindowText(szType);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->GetWindowText(szDatabase);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_DETAILS)->EnableWindow((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && !szDatabase.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_USERS)->EnableWindow((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && !szDatabase.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_VALIDITY)->EnableWindow((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && !szDatabase.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnEditchangeName()
{
	CString  szType;
	CString  szDatabase;
	CString  szFileName;
	CDatabaseProfileInfo  cDatabaseProfileInfo;

	GetDlgItem(IDC_NEW_DOCUMENT_TYPE)->GetWindowText(szType);
	for (GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->GetWindowText(szDatabase), szFileName.Empty(); !szDatabase.IsEmpty(); )
	{
		szFileName = STRING(IDS_DATABASE_BINARYFILEEXTENSION_FORMAT);
		szFileName = szDatabase + szFileName.Mid(1);
		break;
	}
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILENAME)->SetWindowText(szFileName);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_DETAILS)->EnableWindow((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && !szDatabase.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_USERS)->EnableWindow((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && !szDatabase.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_VALIDITY)->EnableWindow((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && !szDatabase.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnEditchangeSpacecraft()
{
	CString  szType;
	CString  szDatabase;
	CString  szSpacecraft;
	CDatabaseProfileInfo  cDatabaseProfileInfo;

	if (!CheckDatabases())
	{
		CheckDlgButton(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL, FALSE);
		CheckDlgButton(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL, TRUE);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_GLOBAL)->EnableWindow();
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL)->EnableWindow();
	}
	GetDlgItem(IDC_NEW_DOCUMENT_TYPE)->GetWindowText(szType);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->GetWindowText(szDatabase);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_DETAILS)->EnableWindow((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && !szDatabase.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_USERS)->EnableWindow((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && !szDatabase.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_VALIDITY)->EnableWindow((szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE) && !szDatabase.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnEditchangeFileLocation()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CNewDialog::OnOK()
{
	INT  nIndex;
	INT  nResult;
	UINT  nType;
	CDBMS  cDBMS;
	CString  szType;
	CString  szServer;
	CString  szMessage;
	CString  szStandard;
	CString  szDatabase;
	CString  szSpacecraft;
	CString  szFileLocation;
	CString  szDatabaseType[2];
	CTimeKey  tDatabaseTime;
	CFileFind  cFileFind;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_NEW_DOCUMENT_TYPE)->GetWindowText(szType);
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_DATABASE))
	{
		if ((pDatabaseProfileInfo = new CDatabaseProfileInfo))
		{
			GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
			GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_NAME)->GetWindowText(szDatabase);
			GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
			GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_STANDARD)->GetWindowText(szStandard);
			GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION)->GetWindowText(szDatabaseType[0]);
			GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_IMPLEMENTATION_FLOATINGPOINT)->GetWindowText(szDatabaseType[1]);
			for (GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_FILELOCATION)->GetWindowText(szFileLocation); cFileFind.FindFile(szFileLocation) || CreateDirectory(szFileLocation, (LPSECURITY_ATTRIBUTES)NULL); )
			{
				CDatabaseEngine::SecureDirectoryOrFile(szFileLocation);
				break;
			}
			for (pDatabaseProfileInfo->SetName(szDatabase), pDatabaseProfileInfo->SetType((nType = DATABASE_TYPE_GLOBAL | DATABASE_TYPE_SUPPORT_DBMS | DATABASE_TYPE_STANDARD_CCSDS | DATABASE_TYPE_IMPLEMENTATION_SCOS | DATABASE_TYPE_FLOATINGPOINTFORMAT_IEEE)); IsDlgButtonChecked(IDC_NEW_DOCUMENT_PROPERTIES_CHARACTERISTICS_LOCAL); )
			{
				nType = (nType & ~DATABASE_TYPE_GLOBAL) | DATABASE_TYPE_LOCAL;
				pDatabaseProfileInfo->SetType(nType);
				break;
			}
			if (szStandard == STRING(IDS_DATABASE_STANDARD_PCM))
			{
				nType = (nType & ~DATABASE_TYPE_STANDARD_CCSDS) | DATABASE_TYPE_STANDARD_PCM;
				pDatabaseProfileInfo->SetType(nType);
			}
			if (szDatabaseType[0] == STRING(IDS_DATABASE_IMPLEMENTATION_ALTEL))
			{
				nType = (nType & ~DATABASE_TYPE_IMPLEMENTATION_SCOS) | DATABASE_TYPE_IMPLEMENTATION_ALTEL;
				pDatabaseProfileInfo->SetType(nType);
			}
			if (szDatabaseType[1] == STRING(IDS_DATABASE_IMPLEMENTATIONFLOATINGPOINT_USAF))
			{
				nType = (nType & ~DATABASE_TYPE_FLOATINGPOINTFORMAT_IEEE) | DATABASE_TYPE_FLOATINGPOINTFORMAT_USAF;
				pDatabaseProfileInfo->SetType(nType);
			}
			for (pDatabaseProfileInfo->SetServer(szServer), pDatabaseProfileInfo->SetSpacecraft(szSpacecraft), pDatabaseProfileInfo->SetFileName(GetDatabaseFileName()), pDatabaseProfileInfo->SetUpdateFileName(GetDatabaseUpdateFileName()), pDatabaseProfileInfo->SetLibraryFileName(GetDatabaseLibraryFileName()), pDatabaseProfileInfo->SetLibraryUpdateFileName(GetDatabaseLibraryUpdateFileName()), pDatabaseProfileInfo->SetLoggingFileName(GetDatabaseLogFileName()), pDatabaseProfileInfo->SetUsers(m_szDatabaseUsers, m_szDatabasePasswords, m_nDatabasePrivileges), pDatabaseProfileInfo->SetValidity(m_tDatabaseValidity[0], m_tDatabaseValidity[1]), pDatabaseProfileInfo->SetCreationTime((tDatabaseTime = CTime::GetCurrentTime().GetTime())), pDatabaseProfileInfo->SetLastUpdateTime(tDatabaseTime); (nIndex = m_pDatabases.Add(pDatabaseProfileInfo)) >= 0; )
			{
				if ((nResult = cDBMS.CreateDatabase(pDatabaseProfileInfo, m_szDatabaseDataFile[0], m_szDatabaseDataFile[1], m_nDatabaseDataSize[0], m_nDatabaseDataSize[1], m_nDatabaseDataSize[2], m_szDatabaseLogsFile[0], m_szDatabaseLogsFile[1], m_nDatabaseLogsSize[0], m_nDatabaseLogsSize[1], m_nDatabaseLogsSize[2], m_bDatabaseReadOnly)) == 0)
				{
					szMessage.Format(STRING(IDS_DATABASE_MESSAGE_CREATION_ERROR), (LPCTSTR)szDatabase);
					m_pDatabases.RemoveAt(nIndex);
					delete pDatabaseProfileInfo;
					ShowMessage(szMessage);
					EndDialog(IDCANCEL);
					return;
				}
				for (SaveDatabases(), UpdateDatabase(pDatabaseProfileInfo), szMessage.Format((nResult > 0) ? STRING(IDS_DATABASE_MESSAGE_CREATION_SUCCESSFUL) : STRING(IDS_DATABASE_MESSAGE_CREATION_WARNING), (LPCTSTR)szDatabase), ShowMessage(szMessage, nResult < 0); GetAccountDatabase().IsEmpty(); )
				{
					SetDatabase(szServer, szSpacecraft, szDatabase, (nResult < 0) ? TRUE : FALSE);
					EndDialog(IDOK);
					return;
				}
				EndDialog(IDOK);
				return;
			}
			delete pDatabaseProfileInfo;
		}
		szMessage.Format(STRING(IDS_DATABASE_MESSAGE_CREATION_ERROR), (LPCTSTR)szDatabase);
		ShowMessage(szMessage);
		EndDialog(IDCANCEL);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_TMPACKET))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateTMPacketsForm()) ? SYSTEM_WARNING_TMPACKET_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_TCFUNCTION))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateTCFunctionsForm()) ? SYSTEM_WARNING_TCFUNCTION_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_TCSEQUENCE))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateTCSequencesForm()) ? SYSTEM_WARNING_TCSEQUENCE_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_TCPROCEDURE))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateTCProceduresForm()) ? SYSTEM_WARNING_TCPROCEDURE_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_TMPARAMETER))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateTMParametersForm()) ? SYSTEM_WARNING_TMPARAMETER_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_TCPARAMETER))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateTCParametersForm()) ? SYSTEM_WARNING_TCPARAMETER_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_OBPROCESSOR))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateOBProcessorsForm()) ? SYSTEM_WARNING_OBPROCESSOR_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_ALPHANUMERICDISPLAY))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateAND()) ? SYSTEM_WARNING_AND_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_GRAPHICDISPLAY))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateGRD()) ? SYSTEM_WARNING_GRD_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_MIMICSDISPLAY))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateMMD()) ? SYSTEM_WARNING_MMD_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_PARAMETEROBSERVATIONDISPLAY))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreatePOD()) ? SYSTEM_WARNING_POD_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	if (szType == STRING(IDS_NEWDIALOG_DATABASETYPE_AUTOMATIONSCRIPT))
	{
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SERVER)->GetWindowText(szServer);
		GetDlgItem(IDC_NEW_DOCUMENT_PROPERTIES_SPACECRAFT)->GetWindowText(szSpacecraft);
		ShowMessage((!CreateScript()) ? SYSTEM_WARNING_AUTOMATIONSCRIPT_OPEN_FAILURE : SYSTEM_NOERROR);
		EndDialog(IDOK);
		return;
	}
	EndDialog(IDCANCEL);
}

void CNewDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CNewDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_NEWDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CNewDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_NEWDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COpenDialog dialog

IMPLEMENT_DYNCREATE(COpenDialog, CLocaleDialog)

COpenDialog::COpenDialog(CWnd *pParentWnd) : CLocaleDialog(COpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(COpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR COpenDialog::DoModal()
{
	CStringArray  szDocuments;

	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_TMPACKET));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_TCFUNCTION));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_TCSEQUENCE));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_TCPROCEDURE));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_TMPARAMETER));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_TCPARAMETER));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_OBPROCESSOR));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_ALPHANUMERICDISPLAY));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_GRAPHICDISPLAY));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_MIMICSDISPLAY));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_PARAMETEROBSERVATIONDISPLAY));
	szDocuments.Add(STRING(IDS_OPENDIALOG_DATABASETYPE_AUTOMATIONSCRIPT));
	return DoModal(szDocuments);
}
INT_PTR COpenDialog::DoModal(CONST CStringArray &szDocuments)
{
	m_szDatabaseDocuments.Copy(szDocuments);
	return CLocaleDialog::DoModal();
}

BOOL COpenDialog::EnumDatabaseTypes()
{
	INT  nDocument;
	INT  nDocuments;

	for (nDocument = 0, nDocuments = (GetDatabase()->IsInitialized()) ? (INT)m_szDatabaseDocuments.GetSize() : 0; nDocument < nDocuments; nDocument++)
	{
		SendDlgItemMessage(IDC_OPEN_DOCUMENT_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szDatabaseDocuments.GetAt(nDocument));
		continue;
	}
	SendDlgItemMessage(IDC_OPEN_DOCUMENT_TYPE, CB_SETCURSEL);
	GetDlgItem(IDC_OPEN_DOCUMENT_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_OPEN_DOCUMENT_TYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OPEN_DOCUMENT_TYPE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OPEN_DOCUMENT_TYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OPEN_DOCUMENT_TYPE)->EnableWindow((SendDlgItemMessage(IDC_OPEN_DOCUMENT_TYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_OPEN_DOCUMENT_TYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL COpenDialog::EnumDatabaseDirectory()
{
	CString  szDocument;

	for (BeginWaitCursor(), GetDlgItem(IDC_OPEN_DOCUMENT_TYPE)->GetWindowText(szDocument); szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TMPACKET); )
	{
		EnumTMPackets();
		break;
	}
	if (szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TCFUNCTION)) EnumTCFunctions();
	if (szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TCSEQUENCE)) EnumTCSequences();
	if (szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TCPROCEDURE)) EnumTCProcedures();
	if (szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TMPARAMETER)) EnumTMParameters();
	if (szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TCPARAMETER)) EnumTCParameters();
	if (szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_OBPROCESSOR)) EnumOBProcessors();
	if (szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_ALPHANUMERICDISPLAY)) EnumANDs();
	if (szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_GRAPHICDISPLAY)) EnumGRDs();
	if (szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_MIMICSDISPLAY)) EnumMMDs();
	if (szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_PARAMETEROBSERVATIONDISPLAY)) EnumPODs();
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_AUTOMATIONSCRIPT); )
	{
		EnumScripts();
		break;
	}
	EndWaitCursor();
	GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow((SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_GETITEMCOUNT) < 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

VOID COpenDialog::EnumTMPackets()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	for (nItem = 0, nItems = (m_pDatabaseTMPackets.Copy(GetDatabase()->GetTMPackets())) ? (INT)m_pDatabaseTMPackets.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
	{
		if ((pDatabaseTMPacket = m_pDatabaseTMPackets.GetAt(nItem)) != (CDatabaseTMPacket *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = pDatabaseTMPacket->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTMPacket->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumTCFunctions()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCFunction  *pDatabaseTCFunction;

	for (nItem = 0, nItems = (m_pDatabaseTCFunctions.Copy(GetDatabase()->GetTCFunctions())) ? (INT)m_pDatabaseTCFunctions.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
	{
		if ((pDatabaseTCFunction = m_pDatabaseTCFunctions.GetAt(nItem)) != (CDatabaseTCFunction *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = pDatabaseTCFunction->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCFunction->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumTCSequences()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	for (nItem = 0, nItems = (m_pDatabaseTCSequences.Copy(GetDatabase()->GetTCSequences())) ? (INT)m_pDatabaseTCSequences.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
	{
		if ((pDatabaseTCSequence = m_pDatabaseTCSequences.GetAt(nItem)) != (CDatabaseTCSequence *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = pDatabaseTCSequence->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCSequence->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumTCProcedures()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCProcedure  *pDatabaseTCProcedure;

	for (nItem = 0, nItems = (m_pDatabaseTCProcedures.Copy(GetDatabase()->GetTCProcedures())) ? (INT)m_pDatabaseTCProcedures.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
	{
		if ((pDatabaseTCProcedure = m_pDatabaseTCProcedures.GetAt(nItem)) != (CDatabaseTCProcedure *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = pDatabaseTCProcedure->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCProcedure->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumTMParameters()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nItem = 0, nItems = (m_pDatabaseTMParameters.Copy(GetDatabase()->GetTMParameters())) ? (INT)m_pDatabaseTMParameters.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
	{
		if ((pDatabaseTMParameter = m_pDatabaseTMParameters.GetAt(nItem)) != (CDatabaseTMParameter *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = pDatabaseTMParameter->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTMParameter->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumTCParameters()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCParameter  *pDatabaseTCParameter;

	for (nItem = 0, nItems = (m_pDatabaseTCParameters.Copy(GetDatabase()->GetTCParameters())) ? (INT)m_pDatabaseTCParameters.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
	{
		if ((pDatabaseTCParameter = m_pDatabaseTCParameters.GetAt(nItem)) != (CDatabaseTCParameter *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = pDatabaseTCParameter->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCParameter->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumOBProcessors()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	for (nItem = 0, nItems = (m_pDatabaseOBProcessors.Copy(GetDatabase()->GetOBProcessors())) ? (INT)m_pDatabaseOBProcessors.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
	{
		if ((pDatabaseOBProcessor = m_pDatabaseOBProcessors.GetAt(nItem)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = pDatabaseOBProcessor->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? pDatabaseOBProcessor->GetDescription() : pDatabaseOBProcessor->GetDetails();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumANDs()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CANDLayout  *pANDLayout;

	for (nItem = 0, nItems = (m_pANDs.Copy(GetDatabase()->GetANDs())) ? (INT)m_pANDs.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
	{
		if ((pANDLayout = m_pANDs.GetAt(nItem)) != (CANDLayout *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = pANDLayout->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pANDLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumGRDs()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CGRDLayout  *pGRDLayout;

	for (nItem = 0, nItems = (m_pGRDs.Copy(GetDatabase()->GetGRDs())) ? (INT)m_pGRDs.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
	{
		if ((pGRDLayout = m_pGRDs.GetAt(nItem)) != (CGRDLayout *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = pGRDLayout->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pGRDLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumMMDs()
{
	INT  nItem;
	INT  nItems;
	INT  nDigits;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CStringTools  cStringTools;
	CMMDLayout  *pMMDLayout;

	for (nItem = 0, nItems = (m_pMMDs.Copy(GetDatabase()->GetMMDs())) ? (INT)m_pMMDs.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS), nDigits = 0; nItem < nItems; nItem++)
	{
		nDigits = ((pMMDLayout = m_pMMDs.GetAt(nItem))) ? max(pMMDLayout->GetName().GetLength(), nDigits) : nDigits;
		continue;
	}
	for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pMMDLayout = m_pMMDs.GetAt(nItem)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = cStringTools.ConvertUIntToPaddedString(_ttoi(pMMDLayout->GetName()), nDigits);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pMMDLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumPODs()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CPODLayout  *pPODLayout;

	for (nItem = 0, nItems = (m_pPODs.Copy(GetDatabase()->GetPODs())) ? (INT)m_pPODs.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
	{
		if ((pPODLayout = m_pPODs.GetAt(nItem)) != (CPODLayout *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = pPODLayout->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pPODLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::EnumScripts()
{
	INT  nItem;
	INT  nItems;
	INT  nDigits;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CStringTools  cStringTools;
	CAutomationScript  *pScript;

	for (nItem = 0, nItems = (m_pScripts.Copy(GetDatabase()->GetScripts())) ? (INT)m_pScripts.GetSize() : 0, SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_DELETEALLITEMS), nDigits = 0; nItem < nItems; nItem++)
	{
		nDigits = ((pScript = m_pScripts.GetAt(nItem))) ? max(pScript->GetName().GetLength(), nDigits) : nDigits;
		continue;
	}
	for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pScript = m_pScripts.GetAt(nItem)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID); )
				{
					szItem = cStringTools.ConvertUIntToPaddedString(_ttoi(pScript->GetName()), nDigits);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pScript->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nItem, nColumn, szItem);
			}
		}
	}
}

VOID COpenDialog::OpenTMPacket()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTMPacketWnd  *pTMPacketWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET)
		{
			if ((pTMPacketWnd = (CTMPacketWnd *)pDisplayWnd)->GetName() == m_pDatabaseTMPackets.GetAt(nIndex)->GetTag())
			{
				pTMPacketWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pTMPacketWnd = new CTMPacketWnd(m_pDatabaseTMPackets.GetAt(nIndex)->GetTag())); )
		{
			if (pTMPacketWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_TMPACKET_FAILURE_LOAD), (LPCTSTR)m_pDatabaseTMPackets.GetAt(nIndex)->GetTag());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenTCFunction()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCFunctionWnd  *pTCFunctionWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION)
		{
			if ((pTCFunctionWnd = (CTCFunctionWnd *)pDisplayWnd)->GetName() == m_pDatabaseTCFunctions.GetAt(nIndex)->GetName())
			{
				pTCFunctionWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pTCFunctionWnd = new CTCFunctionWnd(m_pDatabaseTCFunctions.GetAt(nIndex)->GetName())); )
		{
			if (pTCFunctionWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_TCFUNCTION_FAILURE_LOAD), (LPCTSTR)m_pDatabaseTCFunctions.GetAt(nIndex)->GetName());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenTCSequence()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCSequenceWnd  *pTCSequenceWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE)
		{
			if ((pTCSequenceWnd = (CTCSequenceWnd *)pDisplayWnd)->GetName() == m_pDatabaseTCSequences.GetAt(nIndex)->GetName())
			{
				pTCSequenceWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pTCSequenceWnd = new CTCSequenceWnd(m_pDatabaseTCSequences.GetAt(nIndex)->GetName())); )
		{
			if (pTCSequenceWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_LOAD), (LPCTSTR)m_pDatabaseTCSequences.GetAt(nIndex)->GetName());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenTCProcedure()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCProcedureWnd  *pTCProcedureWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPROCEDURE)
		{
			if ((pTCProcedureWnd = (CTCProcedureWnd *)pDisplayWnd)->GetName() == m_pDatabaseTCProcedures.GetAt(nIndex)->GetName())
			{
				pTCProcedureWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pTCProcedureWnd = new CTCProcedureWnd(m_pDatabaseTCProcedures.GetAt(nIndex)->GetName())); )
		{
			if (pTCProcedureWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_TCPROCEDURE_FAILURE_LOAD), (LPCTSTR)m_pDatabaseTCProcedures.GetAt(nIndex)->GetName());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenTMParameter()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTMParameterWnd  *pTMParameterWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER)
		{
			if ((pTMParameterWnd = (CTMParameterWnd *)pDisplayWnd)->GetName() == m_pDatabaseTMParameters.GetAt(nIndex)->GetTag())
			{
				pTMParameterWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pTMParameterWnd = new CTMParameterWnd(m_pDatabaseTMParameters.GetAt(nIndex)->GetTag())); )
		{
			if (pTMParameterWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_TMPARAMETER_FAILURE_LOAD), (LPCTSTR)m_pDatabaseTMParameters.GetAt(nIndex)->GetTag());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenTCParameter()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCParameterWnd  *pTCParameterWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER)
		{
			if ((pTCParameterWnd = (CTCParameterWnd *)pDisplayWnd)->GetName() == m_pDatabaseTCParameters.GetAt(nIndex)->GetTag())
			{
				pTCParameterWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pTCParameterWnd = new CTCParameterWnd(m_pDatabaseTCParameters.GetAt(nIndex)->GetTag())); )
		{
			if (pTCParameterWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_TCPARAMETER_FAILURE_LOAD), (LPCTSTR)m_pDatabaseTCParameters.GetAt(nIndex)->GetTag());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenOBProcessor()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	COBProcessorWnd  *pOBProcessorWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR)
		{
			if ((pOBProcessorWnd = (COBProcessorWnd *)pDisplayWnd)->GetName() == m_pDatabaseOBProcessors.GetAt(nIndex)->GetName())
			{
				pOBProcessorWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pOBProcessorWnd = new COBProcessorWnd(m_pDatabaseOBProcessors.GetAt(nIndex)->GetName())); )
		{
			if (pOBProcessorWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_OBPROCESSOR_FAILURE_LOAD), (LPCTSTR)m_pDatabaseOBProcessors.GetAt(nIndex)->GetName());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenAND()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CANDWnd  *pANDWnd;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_AND)
		{
			if ((pANDWnd = (CANDWnd *)pDisplayWnd)->GetName() == m_pANDs.GetAt(nIndex)->GetName())
			{
				pANDWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pANDWnd = new CANDWnd(m_pANDs.GetAt(nIndex)->GetName())); )
		{
			if (pANDWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_AND_FAILURE_LOAD), (LPCTSTR)m_pANDs.GetAt(nIndex)->GetName());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenGRD()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CGRDWnd  *pGRDWnd;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_GRD)
		{
			if ((pGRDWnd = (CGRDWnd *)pDisplayWnd)->GetName() == m_pGRDs.GetAt(nIndex)->GetName())
			{
				pGRDWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pGRDWnd = new CGRDWnd(m_pGRDs.GetAt(nIndex)->GetName())); )
		{
			if (pGRDWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_GRD_FAILURE_LOAD), (LPCTSTR)m_pGRDs.GetAt(nIndex)->GetName());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenMMD()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CMMDWnd  *pMMDWnd;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD)
		{
			if (_ttoi((pMMDWnd = (CMMDWnd *)pDisplayWnd)->GetName()) == _ttoi(m_pMMDs.GetAt(nIndex)->GetName()))
			{
				pMMDWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pMMDWnd = new CMMDWnd(m_pMMDs.GetAt(nIndex)->GetName())); )
		{
			if (pMMDWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_MMD_FAILURE_LOAD), (LPCTSTR)m_pMMDs.GetAt(nIndex)->GetName());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenPOD()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CPODWnd  *pPODWnd;
	CString  szMessage;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_POD)
		{
			if ((pPODWnd = (CPODWnd *)pDisplayWnd)->GetName() == m_pPODs.GetAt(nIndex)->GetName())
			{
				pPODWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pPODWnd = new CPODWnd(m_pPODs.GetAt(nIndex)->GetName())); )
		{
			if (pPODWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_POD_FAILURE_LOAD), (LPCTSTR)m_pPODs.GetAt(nIndex)->GetName());
		ShowMessage(szMessage);
	}
}

VOID COpenDialog::OpenScript()
{
	INT  nIndex;
	INT  nDisplay;
	INT  nDisplays;
	CString  szMessage;
	CPtrArray  pDisplays;
	CScriptWnd  *pScriptWnd;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays), nIndex = Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT)
		{
			if (_ttoi((pScriptWnd = (CScriptWnd *)pDisplayWnd)->GetName()) == _ttoi(m_pScripts.GetAt(nIndex)->GetName()))
			{
				pScriptWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		for (; (pScriptWnd = new CScriptWnd(m_pScripts.GetAt(nIndex)->GetName())); )
		{
			if (pScriptWnd->Create(GetMainWnd())) return;
			break;
		}
		szMessage.Format(STRING(IDS_SCRIPT_FAILURE_LOAD), (LPCTSTR)m_pScripts.GetAt(nIndex)->GetName());
		ShowMessage(szMessage);
	}
}

BOOL COpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void COpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COpenDialog::PostNcDestroy()
{
	m_pANDs.RemoveAll();
	m_pGRDs.RemoveAll();
	m_pMMDs.RemoveAll();
	m_pPODs.RemoveAll();
	m_pScripts.RemoveAll();
	m_szColumns.RemoveAll();
	m_pDatabaseTMPackets.RemoveAll();
	m_pDatabaseTCFunctions.RemoveAll();
	m_pDatabaseTCSequences.RemoveAll();
	m_pDatabaseTCProcedures.RemoveAll();
	m_pDatabaseTMParameters.RemoveAll();
	m_pDatabaseTCParameters.RemoveAll();
	m_pDatabaseOBProcessors.RemoveAll();
	m_szDatabaseDocuments.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(COpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OPEN_DOCUMENT_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_OPEN_DOCUMENT_TYPE, OnSelchangeType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenDialog message handlers

BOOL COpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_ID));
	m_szColumns.Add(STRING(IDS_OPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_OPEN_DOCUMENT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 4; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL) - nWidth) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_OPEN_DOCUMENT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumDatabaseTypes();
	EnumDatabaseDirectory();
	return TRUE;
}

BOOL COpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_OPEN_DOCUMENT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED) GetDlgItem(IDOK)->EnableWindow(Check());
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			OnOK();
			return TRUE;
		}
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void COpenDialog::OnSelchangeType()
{
	EnumDatabaseDirectory();
}

void COpenDialog::OnOK()
{
	CString  szDocument;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_OPEN_DOCUMENT_TYPE)->GetWindowText(szDocument); szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TMPACKET); )
	{
		OpenTMPacket();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TCFUNCTION); )
	{
		OpenTCFunction();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TCSEQUENCE); )
	{
		OpenTCSequence();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TCPROCEDURE); )
	{
		OpenTCProcedure();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TMPARAMETER); )
	{
		OpenTMParameter();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_TCPARAMETER); )
	{
		OpenTCParameter();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_OBPROCESSOR); )
	{
		OpenOBProcessor();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_ALPHANUMERICDISPLAY); )
	{
		OpenAND();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_GRAPHICDISPLAY); )
	{
		OpenGRD();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_MIMICSDISPLAY); )
	{
		OpenMMD();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_PARAMETEROBSERVATIONDISPLAY); )
	{
		OpenPOD();
		break;
	}
	for (; szDocument == STRING(IDS_OPENDIALOG_DATABASETYPE_AUTOMATIONSCRIPT); )
	{
		OpenScript();
		break;
	}
	EndDialog(IDOK);
}

void COpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL COpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_OPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_OPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseOpenDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseOpenDialog, CLocaleDialog)

CDatabaseOpenDialog::CDatabaseOpenDialog(CWnd *pParentWnd) : CLocaleDialog(CDatabaseOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDatabaseOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CDatabaseOpenDialog::EnumServers()
{
	INT  nServer;
	INT  nServers;
	CString  szServer;
	CDatabases  cDatabases;
	CStringArray  szServers;
	CStringArray  szDatabases;

	SendDlgItemMessage(IDC_DATABASE_OPEN_SERVER, CB_RESETCONTENT);
	for (nServer = 0, nServers = GetNetworkBrowseService()->EnumNetworkComputers(szServers); nServer < nServers; nServer++)
	{
		for (cDatabases.SetComputerName(szServers.GetAt(nServer)); cDatabases.IsHost() || cDatabases.EnumDatabases(szDatabases, TRUE) > 0; )
		{
			if (SendDlgItemMessage(IDC_DATABASE_OPEN_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szServer = szServers.GetAt(nServer))) == CB_ERR) SendDlgItemMessage(IDC_DATABASE_OPEN_SERVER, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szServer);
			break;
		}
	}
	SendDlgItemMessage(IDC_DATABASE_OPEN_SERVER, CB_SETCURSEL, max(SendDlgItemMessage(IDC_DATABASE_OPEN_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountComputerName()), 0));
	GetDlgItem(IDC_DATABASE_OPEN_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OPEN_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_OPEN_SERVER_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OPEN_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_OPEN_SERVER)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OPEN_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_OPEN_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseOpenDialog::EnumSpacecrafts()
{
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szSpacecraft;
	CDatabases  cDatabases;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	SendDlgItemMessage(IDC_DATABASE_OPEN_SPACECRAFT, CB_RESETCONTENT);
	GetDlgItem(IDC_DATABASE_OPEN_SERVER)->GetWindowText(szServer);
	for (nDatabase = 0, nDatabases = (cDatabases.SetComputerName(szServer) && cDatabases.GetDatabases(m_pDatabases, TRUE)) ? (INT)m_pDatabases.GetSize() : 0; (!nDatabase && !nDatabases && !GetAccountSpacecraftName().IsEmpty()) || nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase)) != (CDatabaseProfileInfo *)NULL  &&  !pDatabaseProfileInfo->GetServer().Compare(szServer))
		{
			if (SendDlgItemMessage(IDC_DATABASE_OPEN_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szSpacecraft = pDatabaseProfileInfo->GetSpacecraft())) == CB_ERR)
			{
				SendDlgItemMessage(IDC_DATABASE_OPEN_SPACECRAFT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szSpacecraft);
				continue;
			}
		}
		if (!nDatabases)
		{
			SendDlgItemMessage(IDC_DATABASE_OPEN_SPACECRAFT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)GetAccountSpacecraftName());
			break;
		}
	}
	SendDlgItemMessage(IDC_DATABASE_OPEN_SPACECRAFT, CB_SETCURSEL, max(SendDlgItemMessage(IDC_DATABASE_OPEN_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountSpacecraftName()), 0));
	GetDlgItem(IDC_DATABASE_OPEN_SPACECRAFT_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OPEN_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_OPEN_SPACECRAFT)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OPEN_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_OPEN_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseOpenDialog::EnumDatabases()
{
	INT  nUser;
	INT  nUsers;
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	INT  nDatabase[2];
	INT  nDatabases[2];
	CString  szServer;
	CString  szDatabase;
	CString  szSpacecraft;
	CString  szVersion[4];
	CStringArray  szUsers;
	CStringArray  szPasswords;
	CUIntArray  nPrivileges;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_DATABASE_OPEN_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_DATABASE_OPEN_SPACECRAFT)->GetWindowText(szSpacecraft);
	for (nDatabase[0] = 0, nDatabases[0] = (INT)m_pDatabases.GetSize(), SendDlgItemMessage(IDC_DATABASE_OPEN_DATABASES_LIST, LVM_DELETEALLITEMS), nIndex = -1; nDatabase[0] < nDatabases[0]; nDatabase[0]++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase[0])) && pDatabaseProfileInfo->GetUsers(szUsers, szPasswords, nPrivileges) > 0 && pDatabaseProfileInfo->GetServer() == szServer  &&  pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft)
		{
			for (nUser = 0, nUsers = (INT)szUsers.GetSize(); nUser < nUsers; nUser++)
			{
				if (szUsers.GetAt(nUser) == GetAccountUserName()) break;
				continue;
			}
			for (nDatabase[1] = 0, nDatabases[1] = (nUser < nUsers) ? (INT)SendDlgItemMessage(IDC_DATABASE_OPEN_DATABASES_LIST, LVM_GETITEMCOUNT) : -1; nDatabase[1] < nDatabases[1]; nDatabase[1]++)
			{
				if (Listview_GetText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST), nDatabase[1], FindColumnIndex(STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_NAME))) == pDatabaseProfileInfo->GetName()) break;
				continue;
			}
			for (nColumn = 0, nColumns = (nDatabase[1] == nDatabases[1]) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
			{
				for (szDatabase.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_NAME); )
				{
					for (szDatabase = pDatabaseProfileInfo->GetName(); szDatabase == GetAccountDatabase(); )
					{
						nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_OPEN_DATABASES_LIST, LVM_GETITEMCOUNT);
						nIndex = (nColumn > 0) ? (nIndex - 1) : nIndex;
						break;
					}
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_VERSION); )
				{
					szDatabase = (pDatabaseProfileInfo->GetVersion(szVersion[0], szVersion[1], szVersion[2], szVersion[3])) ? szVersion[0] : STRING(IDS_DATABASEOPENDIALOG_SYMBOL_NOVERSION);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_RELEASE); )
				{
					szDatabase = (pDatabaseProfileInfo->GetVersion(szVersion[0], szVersion[1], szVersion[2], szVersion[3]) && !szVersion[1].IsEmpty()) ? szVersion[1] : STRING(IDS_DATABASEOPENDIALOG_SYMBOL_NORELEASE);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_ISSUE); )
				{
					szDatabase = (pDatabaseProfileInfo->GetVersion(szVersion[0], szVersion[1], szVersion[2], szVersion[3]) && !szVersion[2].IsEmpty()) ? szVersion[2] : STRING(IDS_DATABASEOPENDIALOG_SYMBOL_NOISSUE);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_COMMENT); )
				{
					szDatabase = (pDatabaseProfileInfo->GetVersion(szVersion[0], szVersion[1], szVersion[2], szVersion[3]) && !szVersion[3].IsEmpty()) ? szVersion[3] : STRING(IDS_DATABASEOPENDIALOG_SYMBOL_NOCOMMENT);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST), (INT)SendDlgItemMessage(IDC_DATABASE_OPEN_DATABASES_LIST, LVM_GETITEMCOUNT), szDatabase);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST), (INT)SendDlgItemMessage(IDC_DATABASE_OPEN_DATABASES_LIST, LVM_GETITEMCOUNT) - 1, nColumn, szDatabase);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST), max(nIndex, 0));
	GetDlgItem(IDC_DATABASE_OPEN_DATABASES)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OPEN_DATABASES_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OPEN_DATABASES_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

VOID CDatabaseOpenDialog::ShowDatabaseInfo()
{
	UINT  nType;
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szTime[2];
	CString  szDatabase;
	CString  szSpacecraft;
	CTimeKey  tTime[3];
	CStringArray  szUsers;
	CStringArray  szPasswords;
	CUIntArray  nPrivileges;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_DATABASE_OPEN_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_DATABASE_OPEN_SPACECRAFT)->GetWindowText(szSpacecraft);
	for (nDatabase = 0, nDatabases = (INT)m_pDatabases.GetSize(), szDatabase = Listview_GetText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST), Listview_GetCurText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST)), FindColumnIndex(STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_NAME))); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetUsers(szUsers, szPasswords, nPrivileges) >= 0 && pDatabaseProfileInfo->GetValidity(tTime[1], tTime[2]) >= 0 && pDatabaseProfileInfo->GetServer() == szServer  &&  pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft  &&  pDatabaseProfileInfo->GetName() == szDatabase)
		{
			szTime[0] = (tTime[0] = pDatabaseProfileInfo->GetCreationTime()).FormatGmt(STRING(IDS_DATABASEOPENDIALOG_CREATIONTIMEFORMAT));
			szTime[1] = tTime[1].FormatGmt(CString(STRING(IDS_DATABASEOPENDIALOG_VALIDITYTIMEFORMAT)).Left(lstrlen(STRING(IDS_DATABASEOPENDIALOG_VALIDITYTIMEFORMAT)) / 2));
			szTime[1] += tTime[2].FormatGmt(CString(STRING(IDS_DATABASEOPENDIALOG_VALIDITYTIMEFORMAT)).Mid(lstrlen(STRING(IDS_DATABASEOPENDIALOG_VALIDITYTIMEFORMAT)) / 2));
			szTime[1] = (tTime[1] > 0 && tTime[2] > 0 && tTime[1] <= tTime[2]) ? (LPCTSTR)szTime[1] : STRING(IDS_DATABASEOPENDIALOG_UNLIMITEDVALIDITY);
			CheckDlgButton(IDC_DATABASE_OPEN_CHARACTERISTICS_GLOBAL, ((nType = pDatabaseProfileInfo->GetType()) & DATABASE_TYPE_GLOBAL) ? TRUE : FALSE);
			CheckDlgButton(IDC_DATABASE_OPEN_CHARACTERISTICS_LOCAL, (nType & DATABASE_TYPE_LOCAL) ? TRUE : FALSE);
			GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_STANDARD)->SetWindowText((nType & DATABASE_TYPE_STANDARD_PCM) ? STRING(IDS_DATABASE_STANDARD_PCM) : ((nType & DATABASE_TYPE_STANDARD_CCSDS) ? STRING(IDS_DATABASE_STANDARD_CCSDS) : (LPCTSTR)m_szStandard));
			GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION)->SetWindowText((nType & DATABASE_TYPE_IMPLEMENTATION_SCOS) ? STRING(IDS_DATABASE_IMPLEMENTATION_SCOS) : ((nType & DATABASE_TYPE_IMPLEMENTATION_ALTEL) ? STRING(IDS_DATABASE_IMPLEMENTATION_ALTEL) : (LPCTSTR)m_szImplementation));
			GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_OWNER)->SetWindowText(szUsers.GetAt(0));
			GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_TIME)->SetWindowText(szTime[0]);
			GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_VALIDITY)->SetWindowText(szTime[1]);
			break;
		}
	}
	if (nDatabase == nDatabases)
	{
		CheckDlgButton(IDC_DATABASE_OPEN_CHARACTERISTICS_GLOBAL, FALSE);
		CheckDlgButton(IDC_DATABASE_OPEN_CHARACTERISTICS_LOCAL, FALSE);
		GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_STANDARD)->SetWindowText(m_szStandard);
		GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION)->SetWindowText(m_szImplementation);
		GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_OWNER)->SetWindowText(m_szOwner);
		GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_TIME)->SetWindowText(m_szTime);
		GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_VALIDITY)->SetWindowText(m_szValidity);
	}
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_SCOPE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_GLOBAL)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_LOCAL)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_STANDARD_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_STANDARD)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_OWNER_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_OWNER)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_TIME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_VALIDITY_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_VALIDITY)->EnableWindow();
}

INT CDatabaseOpenDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

BOOL CDatabaseOpenDialog::IsModified() CONST
{
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	return(((pDatabaseProfileInfo = m_pDatabases.GetAt(m_pDatabases.Find(Combobox_GetText(GetDlgItem(IDC_DATABASE_OPEN_SERVER), (INT)GetDlgItem(IDC_DATABASE_OPEN_SERVER)->SendMessage(CB_GETCURSEL)), Listview_GetText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST), Listview_GetCurText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST)), FindColumnIndex(STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_NAME)))))) && !GetDatabase()->CDatabaseProfileInfo::Compare(pDatabaseProfileInfo)) ? TRUE : FALSE);
}

BOOL CDatabaseOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST)) >= 0) ? (!bModified || IsModified()) : FALSE);
}

void CDatabaseOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseOpenDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabases.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabaseOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_OPEN_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_DATABASE_OPEN_SERVER, OnSelchangeServer)
	ON_CBN_SELCHANGE(IDC_DATABASE_OPEN_SPACECRAFT, OnSelchangeSpacecraft)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOpenDialog message handlers

BOOL CDatabaseOpenDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	m_szColumns.Add(STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_VERSION));
	m_szColumns.Add(STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_RELEASE));
	m_szColumns.Add(STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_ISSUE));
	m_szColumns.Add(STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_COMMENT));
	GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST)->GetClientRect(rColumns);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_DATABASE_OPEN_DATABASES_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_NAME)) ? (rColumns.Width() / 3) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_VERSION)) ? (rColumns.Width() / 4) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_RELEASE) || m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_ISSUE)) ? (rColumns.Width() / 7) : (rColumns.Width() / 2))));
		continue;
	}
	for (GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_STANDARD)->GetWindowText(m_szStandard), GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION)->GetWindowText(m_szImplementation), GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_OWNER)->GetWindowText(m_szOwner), GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_TIME)->GetWindowText(m_szTime), GetDlgItem(IDC_DATABASE_OPEN_CHARACTERISTICS_VALIDITY)->GetWindowText(m_szValidity); EnumServers() && EnumSpacecrafts() && EnumDatabases(); )
	{
		ShowDatabaseInfo();
		break;
	}
	AccessControl(IDC_DATABASE_OPEN_CHARACTERISTICS_GLOBAL, FALSE);
	AccessControl(IDC_DATABASE_OPEN_CHARACTERISTICS_LOCAL, FALSE);
	return TRUE;
}

BOOL CDatabaseOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_DATABASE_OPEN_DATABASES_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (pNotifyListView->uNewState != 0) ShowDatabaseInfo();
			GetDlgItem(IDOK)->EnableWindow(Check());
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			OnOK();
			return TRUE;
		}
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void CDatabaseOpenDialog::OnSelchangeServer()
{
	EnumSpacecrafts();
	EnumDatabases();
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseOpenDialog::OnSelchangeSpacecraft()
{
	EnumDatabases();
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseOpenDialog::OnOK()
{
	CString  szServer;
	CString  szSpacecraft;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_DATABASE_OPEN_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_DATABASE_OPEN_SPACECRAFT)->GetWindowText(szSpacecraft);
	EndDialog((SetDatabase(szServer, szSpacecraft, Listview_GetText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST), Listview_GetCurText(GetDlgItem(IDC_DATABASE_OPEN_DATABASES_LIST)), FindColumnIndex(STRING(IDS_DATABASEOPENDIALOG_LISTTITLEITEM_NAME))))) ? IDOK : IDCANCEL);
}

void CDatabaseOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabaseOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseImportDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseImportDialog, CLocaleDialog)

CDatabaseImportDialog::CDatabaseImportDialog(CWnd *pParentWnd) : CLocaleDialog(CDatabaseImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDatabaseImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CDatabaseImportDialog::Initialize()
{
	m_szDatabaseDataFile[0].Empty();
	m_szDatabaseDataFile[1].Empty();
	m_szDatabaseLogsFile[0].Empty();
	m_szDatabaseLogsFile[1].Empty();
	m_nDatabaseDataSize[0] = m_nDatabaseDataSize[1] = m_nDatabaseDataSize[2] = 0;
	m_nDatabaseLogsSize[0] = m_nDatabaseLogsSize[1] = m_nDatabaseLogsSize[2] = 0;
	m_tDatabaseValidity[0] = m_tDatabaseValidity[1] = 0;
	m_szDatabaseUsers[0].Add(GetAccountUserName());
	m_szDatabaseUsers[1].Add(GetAccountPassword());
	m_nDatabasePrivileges.Add(DATABASE_PRIVILEGES_ALL);
	m_bDatabaseReadOnly = FALSE;
	return((LoadDatabases() >= 0) ? TRUE : FALSE);
}

BOOL CDatabaseImportDialog::EnumServers()
{
	INT  nServer;
	INT  nServers;
	CString  szServer;
	CDatabases  cDatabases;
	CStringArray  szServers;
	CStringArray  szDatabases;

	SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_RESETCONTENT);
	for (nServer = 0, nServers = GetNetworkBrowseService()->EnumNetworkComputers(szServers); nServer < nServers; nServer++)
	{
		for (cDatabases.SetComputerName((szServer = szServers.GetAt(nServer))); SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szServer) == CB_ERR && (cDatabases.IsHost() || cDatabases.EnumDatabases(szDatabases, TRUE) > 0); )
		{
			SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szServers.GetAt(nServer));
			break;
		}
	}
	SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_SETCURSEL, max(SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountComputerName()), 0));
	GetDlgItem(IDC_DATABASE_IMPORT_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_IMPORT_SERVER_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_IMPORT_SERVER)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_IMPORT_DATAONLY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseImportDialog::EnumSpacecrafts()
{
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szSpacecraft;
	CDatabases  cDatabases;
	CComputerToken  cComputerToken;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	SendDlgItemMessage(IDC_DATABASE_IMPORT_SPACECRAFT, CB_RESETCONTENT);
	for (GetDlgItem(IDC_DATABASE_IMPORT_SERVER)->GetWindowText(szServer); IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES); )
	{
		szServer = cComputerToken.GetComputerName();
		break;
	}
	for (nDatabase = 0, nDatabases = (cDatabases.SetComputerName(szServer) && cDatabases.GetDatabases(m_pDatabases[1], TRUE)) ? (INT)m_pDatabases[1].GetSize() : 0; (!nDatabase && !nDatabases && !GetAccountSpacecraftName().IsEmpty()) || nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases[1].GetAt(nDatabase)) != (CDatabaseProfileInfo *)NULL  &&  !pDatabaseProfileInfo->GetServer().Compare(szServer))
		{
			if (SendDlgItemMessage(IDC_DATABASE_IMPORT_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szSpacecraft = pDatabaseProfileInfo->GetSpacecraft())) == CB_ERR)
			{
				SendDlgItemMessage(IDC_DATABASE_IMPORT_SPACECRAFT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szSpacecraft);
				continue;
			}
		}
		if (!nDatabases)
		{
			SendDlgItemMessage(IDC_DATABASE_IMPORT_SPACECRAFT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)GetAccountSpacecraftName());
			break;
		}
	}
	SendDlgItemMessage(IDC_DATABASE_IMPORT_SPACECRAFT, CB_SETCURSEL, max(SendDlgItemMessage(IDC_DATABASE_IMPORT_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountSpacecraftName()), 0));
	GetDlgItem(IDC_DATABASE_IMPORT_SPACECRAFT_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_IMPORT_SPACECRAFT)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_IMPORT_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseImportDialog::EnumDatabases()
{
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szDatabase;
	CString  szSpacecraft;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_RESETCONTENT);
	SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_RESETCONTENT);
	GetDlgItem(IDC_DATABASE_IMPORT_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_DATABASE_IMPORT_SPACECRAFT)->GetWindowText(szSpacecraft);
	for (nDatabase = 0, nDatabases = (INT)m_pDatabases[1].GetSize(); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases[1].GetAt(nDatabase)) && pDatabaseProfileInfo->GetServer() == szServer  &&  pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft)
		{
			if (SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szDatabase = pDatabaseProfileInfo->GetName())) == CB_ERR)
			{
				SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDatabase);
				continue;
			}
		}
	}
	SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_SETCURSEL);
	GetDlgItem(IDC_DATABASE_IMPORT_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_IMPORT_NAME)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CDatabaseImportDialog::EnumStringDelimiters()
{
	INT  nDelimiter;
	INT  nDelimiters;

	for (nDelimiter = 0, nDelimiters = MAXDATABASEIMPORTSTRINGDELIMITER - MINDATABASEIMPORTSTRINGDELIMITER; nDelimiter <= nDelimiters; nDelimiter++)
	{
		SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINDATABASEIMPORTSTRINGDELIMITER + nDelimiter));
		continue;
	}
}

VOID CDatabaseImportDialog::EnumFieldDelimiters()
{
	INT  nDelimiter;
	INT  nDelimiters;

	for (nDelimiter = 0, nDelimiters = MAXDATABASEIMPORTFIELDDELIMITER - MINDATABASEIMPORTFIELDDELIMITER; nDelimiter <= nDelimiters; nDelimiter++)
	{
		SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINDATABASEIMPORTFIELDDELIMITER + nDelimiter));
		continue;
	}
}

VOID CDatabaseImportDialog::EnumRowDelimiters()
{
	INT  nDelimiter;
	INT  nDelimiters;

	for (nDelimiter = 0, nDelimiters = MAXDATABASEIMPORTROWDELIMITER - MINDATABASEIMPORTROWDELIMITER; nDelimiter <= nDelimiters; nDelimiter++)
	{
		SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINDATABASEIMPORTROWDELIMITER + nDelimiter));
		continue;
	}
}

VOID CDatabaseImportDialog::ShowDatabaseInfo()
{
	INT  nIndex;
	INT  nDatabase;
	INT  nDatabases;
	CString  szTime[2];
	CString  szDatabase;
	CString  szSpacecraft;
	CTimeKey  tValidity[2];
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	for (GetDlgItem(IDC_DATABASE_IMPORT_SPACECRAFT)->GetWindowText(szSpacecraft); IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY); )
	{
		if (!SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_GETCOUNT))
		{
			for (nDatabase = 0, nDatabases = (INT)m_pDatabases[0].GetSize(); nDatabase < nDatabases; nDatabase++)
			{
				if ((pDatabaseProfileInfo = m_pDatabases[1].GetAt(nDatabase)) && pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft)
				{
					if (SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szDatabase = pDatabaseProfileInfo->GetName())) == CB_ERR)
					{
						SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDatabase);
						continue;
					}
				}
			}
			SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_SETCURSEL, ((nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_GETCURSEL)) < 0) ? (WPARAM)SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountDatabase()) : nIndex);
		}
		for (nDatabase = 0, nDatabases = (INT)m_pDatabases[0].GetSize(), GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->GetWindowText(szDatabase), m_szDatabaseUsers[0].RemoveAll(), m_szDatabaseUsers[1].RemoveAll(), m_nDatabasePrivileges.RemoveAll(); nDatabase < nDatabases; nDatabase++)
		{
			if ((pDatabaseProfileInfo = m_pDatabases[0].GetAt(nDatabase)) && pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft  &&  pDatabaseProfileInfo->GetName() == szDatabase  &&  pDatabaseProfileInfo->GetUsers(m_szDatabaseUsers[0], m_szDatabaseUsers[1], m_nDatabasePrivileges) > 0 && pDatabaseProfileInfo->GetValidity(tValidity[0], tValidity[1]))
			{
				CheckRadioButton(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL, IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL, (pDatabaseProfileInfo->GetType() & DATABASE_TYPE_GLOBAL) ? IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL : IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL);
				szTime[0] = tValidity[0].FormatGmt(CString(STRING(IDS_DATABASEIMPORTDIALOG_VALIDITYTIMEFORMAT)).Left(lstrlen(STRING(IDS_DATABASEIMPORTDIALOG_VALIDITYTIMEFORMAT)) / 2));
				szTime[1] = tValidity[1].FormatGmt(CString(STRING(IDS_DATABASEIMPORTDIALOG_VALIDITYTIMEFORMAT)).Mid(lstrlen(STRING(IDS_DATABASEIMPORTDIALOG_VALIDITYTIMEFORMAT)) / 2));
				GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION)->SetWindowText(ConstructDatabaseFileLocation(pDatabaseProfileInfo->GetFileName()));
				GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_OWNER)->SetWindowText(m_szDatabaseUsers[0].GetAt(m_szDatabaseUsers[0].GetCount() - m_szDatabaseUsers[0].GetUpperBound() - 1));
				GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_TIME)->SetWindowText(pDatabaseProfileInfo->GetCreationTime().Format(STRING(IDS_DATABASEIMPORTDIALOG_CREATIONTIMEFORMAT)));
				GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_VALIDITY)->SetWindowText((tValidity[0] > 0 && tValidity[1] > 0 && tValidity[0] <= tValidity[1]) ? (szTime[0] + szTime[1]) : STRING(IDS_DATABASEIMPORTDIALOG_UNLIMITEDVALIDITY));
				break;
			}
		}
		if (nDatabase == nDatabases)
		{
			GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION)->SetWindowText(EMPTYSTRING);
			m_szDatabaseUsers[0].Add(GetAccountUserName());
			m_szDatabaseUsers[1].Add(GetAccountPassword());
			m_nDatabasePrivileges.Add(DATABASE_PRIVILEGES_ALL);
		}
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION_BROWSE)->EnableWindow(FALSE);
		AccessControl(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL, FALSE);
		AccessControl(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL, FALSE);
		AccessControl(IDC_DATABASE_IMPORT_DESTINATION_LOCATION, FALSE);
		break;
	}
	if (!IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY))
	{
		if (SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_GETCOUNT) > 0)
		{
			SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_RESETCONTENT);
			GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION)->SetWindowText(EMPTYSTRING);
			m_szDatabaseUsers[0].RemoveAll();
			m_szDatabaseUsers[1].RemoveAll();
			m_nDatabasePrivileges.RemoveAll();
			m_szDatabaseUsers[0].Add(GetAccountUserName());
			m_szDatabaseUsers[1].Add(GetAccountPassword());
			m_nDatabasePrivileges.Add(DATABASE_PRIVILEGES_ALL);
		}
		for (szTime[0].Empty(), szTime[1].Empty(); m_tDatabaseValidity[0] > 0 && m_tDatabaseValidity[1] > 0 && m_tDatabaseValidity[0] <= m_tDatabaseValidity[1]; )
		{
			szTime[0] = m_tDatabaseValidity[0].FormatGmt(CString(STRING(IDS_DATABASEIMPORTDIALOG_VALIDITYTIMEFORMAT)).Left(lstrlen(STRING(IDS_DATABASEIMPORTDIALOG_VALIDITYTIMEFORMAT)) / 2));
			szTime[1] = m_tDatabaseValidity[1].FormatGmt(CString(STRING(IDS_DATABASEIMPORTDIALOG_VALIDITYTIMEFORMAT)).Mid(lstrlen(STRING(IDS_DATABASEIMPORTDIALOG_VALIDITYTIMEFORMAT)) / 2));
			break;
		}
		for (nDatabase = 0, nDatabases = (INT)m_pDatabases[0].GetSize(); nDatabase < nDatabases; nDatabase++)
		{
			if ((pDatabaseProfileInfo = m_pDatabases[0].GetAt(nDatabase)) && pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft && (pDatabaseProfileInfo->GetType() & DATABASE_TYPE_GLOBAL)) break;
			continue;
		}
		CheckRadioButton(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL, IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL, (nDatabase == nDatabases) ? IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL : IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL);
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_VALIDITY)->SetWindowText((!szTime[0].IsEmpty() && !szTime[1].IsEmpty()) ? (szTime[0] + szTime[1]) : STRING(IDS_DATABASEIMPORTDIALOG_UNLIMITEDVALIDITY));
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_TIME)->SetWindowText(STRING(IDS_DATABASEIMPORTDIALOG_CREATIONTIMENOW));
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_OWNER)->SetWindowText(GetAccountUserName());
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL));
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION_BROWSE)->EnableWindow();
		AccessControl(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL, TRUE);
		AccessControl(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL, TRUE);
		AccessControl(IDC_DATABASE_IMPORT_DESTINATION_LOCATION, TRUE);
	}
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->GetWindowText(szDatabase);
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION)->EnableWindow();
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DETAILS)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY) && !szDatabase.IsEmpty());
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_USERS)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY) && !szDatabase.IsEmpty());
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_VALIDITY)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY) && !szDatabase.IsEmpty());
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_OWNER_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_OWNER)->EnableWindow();
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_TIME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_VALIDITY_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_INFO_VALIDITY)->EnableWindow();
}

BOOL CDatabaseImportDialog::SaveDatabases()
{
	CDatabases  cDatabases;

	return cDatabases.SetDatabases(m_pDatabases[0]);
}

BOOL CDatabaseImportDialog::LoadDatabases()
{
	CDatabases  cDatabases;

	return cDatabases.GetDatabases(m_pDatabases[0], TRUE);
}

CString CDatabaseImportDialog::GetDatabaseFileName() CONST
{
	INT  nPos;
	CString  szFileName[4];
	CString  szFileLocation;
	CLogicalDrives  cDrives;

	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->GetWindowText(szFileName[0]);
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION)->GetWindowText(szFileLocation);
	for (nPos = lstrlen((szFileName[1] = STRING(IDS_DATABASE_BINARY_UPDATENAME))) - 1, szFileName[2] = (!szFileLocation.IsEmpty()) ? ((szFileLocation.GetLength() > 1 && szFileLocation[szFileLocation.GetLength() - 1] != cDrives.GetDriveDelimiter() && szFileLocation[szFileLocation.GetLength() - 1] != cDrives.GetPathDelimiter()) ? CString(szFileLocation + cDrives.GetPathDelimiter() + szFileName[0]) : (szFileLocation + szFileName[0])) : szFileName[0], szFileName[3].Format(STRING(IDS_DATABASE_BINARY_FILENAME), (LPCTSTR)szFileName[2]); nPos >= 0; nPos--)
	{
		if (!_istalpha(szFileName[1].GetAt(nPos))) break;
		continue;
	}
	if (nPos >= 0)
	{
		if (!szFileName[2].Right(szFileName[1].Mid(nPos).GetLength()).CompareNoCase(szFileName[1].Mid(nPos)))
		{
			szFileName[3].Format(STRING(IDS_DATABASE_BINARY_FILENAME), (LPCTSTR)szFileName[2].Left(szFileName[2].GetLength() - szFileName[1].Mid(nPos).GetLength()));
			szFileName[2] = szFileName[3];
		}
	}
	return((szFileName[2] = (nPos >= 0 && szFileName[2].Find(szFileName[1].GetAt(nPos)) < 0) ? szFileName[3] : szFileName[2]));
}

CString CDatabaseImportDialog::GetDatabaseUpdateFileName() CONST
{
	INT  nPos[2];
	CString  szFileName[4];

	if (!GetFileTitle((szFileName[0] = szFileName[1] = GetDatabaseFileName()), szFileName[2].GetBufferSetLength(GetDatabaseFileName().GetLength()), GetDatabaseFileName().GetLength() + 1))
	{
		for (szFileName[2].ReleaseBuffer(), szFileName[0].MakeReverse(), szFileName[2].MakeReverse(), szFileName[0].MakeUpper(), szFileName[2].MakeUpper(); (nPos[0] = szFileName[0].Find(szFileName[2])) >= 0; )
		{
			for (nPos[1] = lstrlen((szFileName[3] = STRING(IDS_DATABASE_BINARY_UPDATENAME))) - 1, szFileName[2].MakeReverse(); nPos[1] >= 0; nPos[1]--)
			{
				if (!_istalpha(szFileName[3].GetAt(nPos[1]))) break;
				continue;
			}
			szFileName[1] = szFileName[1].Left(szFileName[1].GetLength() - lstrlen(szFileName[2]) - nPos[0]);
			szFileName[2] = ((nPos[1] = (nPos[1] >= 0) ? szFileName[2].ReverseFind(szFileName[3].GetAt(nPos[1])) : -1) >= 0) ? szFileName[2].Left(nPos[1]) : szFileName[2];
			szFileName[3].Format(STRING(IDS_DATABASE_BINARY_UPDATENAME), (LPCTSTR)(szFileName[1] + szFileName[2]));
			return szFileName[3];
		}
		return EMPTYSTRING;
	}
	szFileName[2].ReleaseBuffer();
	return szFileName[3];
}

CString CDatabaseImportDialog::GetDatabaseLibraryFileName() CONST
{
	INT  nPos;
	CString  szDatabase;
	CString  szFileName[4];
	CString  szFileLocation;
	CLogicalDrives  cDrives;

	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->GetWindowText(szDatabase);
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION)->GetWindowText(szFileLocation);
	for (nPos = lstrlen((szFileName[1] = STRING(IDS_DATABASE_LIBRARY_UPDATENAME))) - 1, szFileName[0].Format(STRING(IDS_DATABASE_BINARY_FILENAME), (LPCTSTR)szDatabase), szFileName[2] = (!szFileLocation.IsEmpty()) ? ((szFileLocation.GetLength() > 1 && szFileLocation[szFileLocation.GetLength() - 1] != cDrives.GetDriveDelimiter() && szFileLocation[szFileLocation.GetLength() - 1] != cDrives.GetPathDelimiter()) ? CString(szFileLocation + cDrives.GetPathDelimiter() + szFileName[0]) : (szFileLocation + szFileName[0])) : szFileName[0]; nPos >= 0; nPos--)
	{
		if (!_istalpha(szFileName[1].GetAt(nPos))) break;
		continue;
	}
	szFileName[3].Format(STRING(IDS_DATABASE_LIBRARY_FILENAME), (nPos >= 0 && szFileName[2].ReverseFind(szFileName[1].GetAt(nPos)) >= 0) ? (LPCTSTR)szFileName[2].Left(szFileName[2].ReverseFind(szFileName[1].GetAt(nPos))) : (LPCTSTR)szFileName[2]);
	return szFileName[3];
}

CString CDatabaseImportDialog::GetDatabaseLibraryUpdateFileName() CONST
{
	INT  nPos[2];
	CString  szFileName[4];

	if (!GetFileTitle((szFileName[0] = szFileName[1] = GetDatabaseLibraryFileName()), szFileName[2].GetBufferSetLength(GetDatabaseLibraryFileName().GetLength()), GetDatabaseLibraryFileName().GetLength() + 1))
	{
		for (szFileName[2].ReleaseBuffer(), szFileName[0].MakeReverse(), szFileName[2].MakeReverse(), szFileName[0].MakeUpper(), szFileName[2].MakeUpper(); (nPos[0] = szFileName[0].Find(szFileName[2])) >= 0; )
		{
			for (nPos[1] = lstrlen((szFileName[3] = STRING(IDS_DATABASE_LIBRARY_UPDATENAME))) - 1, szFileName[2].MakeReverse(); nPos[1] >= 0; nPos[1]--)
			{
				if (!_istalpha(szFileName[3].GetAt(nPos[1]))) break;
				continue;
			}
			szFileName[1] = szFileName[1].Left(szFileName[1].GetLength() - lstrlen(szFileName[2]) - nPos[0]);
			szFileName[2] = ((nPos[1] = (nPos[1] >= 0) ? szFileName[2].ReverseFind(szFileName[3].GetAt(nPos[1])) : -1) >= 0) ? szFileName[2].Left(nPos[1]) : szFileName[2];
			szFileName[3].Format(STRING(IDS_DATABASE_LIBRARY_UPDATENAME), (LPCTSTR)(szFileName[1] + szFileName[2]));
			return szFileName[3];
		}
		return EMPTYSTRING;
	}
	szFileName[2].ReleaseBuffer();
	return szFileName[3];
}

CString CDatabaseImportDialog::GetDatabaseLogFileName() CONST
{
	INT  nPos[2];
	CString  szFileName[4];

	if (!GetFileTitle((szFileName[0] = szFileName[1] = GetDatabaseFileName()), szFileName[2].GetBufferSetLength(GetDatabaseFileName().GetLength()), GetDatabaseFileName().GetLength() + 1))
	{
		for (szFileName[2].ReleaseBuffer(), szFileName[0].MakeReverse(), szFileName[2].MakeReverse(), szFileName[0].MakeUpper(), szFileName[2].MakeUpper(); (nPos[0] = szFileName[0].Find(szFileName[2])) >= 0; )
		{
			for (nPos[1] = lstrlen((szFileName[3] = STRING(IDS_DATABASE_LOGGING_FILENAME))) - 1, szFileName[2].MakeReverse(); nPos[1] >= 0; nPos[1]--)
			{
				if (!_istalpha(szFileName[3].GetAt(nPos[1]))) break;
				continue;
			}
			szFileName[1] = szFileName[1].Left(szFileName[1].GetLength() - lstrlen(szFileName[2]) - nPos[0]);
			szFileName[2] = ((nPos[1] = (nPos[1] >= 0) ? szFileName[2].ReverseFind(szFileName[3].GetAt(nPos[1])) : -1) >= 0) ? szFileName[2].Left(nPos[1]) : szFileName[2];
			szFileName[3].Format(STRING(IDS_DATABASE_LOGGING_FILENAME), (LPCTSTR)(szFileName[1] + szFileName[2]));
			return szFileName[3];
		}
		return EMPTYSTRING;
	}
	szFileName[2].ReleaseBuffer();
	return szFileName[3];
}

CString CDatabaseImportDialog::ConstructDatabaseFileName(LPCTSTR pszPathName) CONST
{
	INT  nPos;
	CString  szFileTitle;

	if (!GetFileTitle(pszPathName, szFileTitle.GetBufferSetLength(max(GetFileTitle(pszPathName, (LPTSTR)NULL, 0) - 1, 0)), GetFileTitle(pszPathName, (LPTSTR)NULL, 0)))
	{
		for (nPos = lstrlen(pszPathName) - lstrlen(szFileTitle), szFileTitle.ReleaseBuffer(); nPos >= 0; nPos--)
		{
			if (!_tcsnicmp(&pszPathName[nPos], szFileTitle, lstrlen(szFileTitle))) break;
			continue;
		}
		return((nPos >= 0) ? (LPCTSTR)CString(pszPathName).Mid(nPos) : EMPTYSTRING);
	}
	szFileTitle.ReleaseBuffer();
	szFileTitle.Empty();
	return szFileTitle;
}

CString CDatabaseImportDialog::ConstructDatabaseFileLocation(LPCTSTR pszPathName) CONST
{
	INT  nPos;
	CString  szDrive;
	CString  szFilePath;
	CString  szFileTitle;
	CLogicalDrives  cDrives;

	for (nPos = lstrlen(pszPathName), szDrive = cDrives.ExtractDrive(pszPathName), GetFileTitle(pszPathName, szFileTitle.GetBufferSetLength(max(GetFileTitle(pszPathName, (LPTSTR)NULL, 0) - 1, 0)), ::GetFileTitle(pszPathName, (LPTSTR)NULL, 0)), szFileTitle.ReleaseBuffer(), nPos -= szFileTitle.GetLength(), szFilePath = (nPos > 0) ? pszPathName : EMPTYSTRING; nPos >= 0; nPos--)
	{
		if (!_tcsnicmp(&pszPathName[nPos], szFileTitle, szFileTitle.GetLength())) break;
		continue;
	}
	if (nPos >= 0)
	{
		szFilePath = (nPos > 0 && cDrives.GetPathDelimiter() == pszPathName[nPos - 1]) ? CString(pszPathName).Left(nPos - 1) : CString(pszPathName).Left(nPos);
		return szFilePath;
	}
	return EMPTYSTRING;
}

BOOL CDatabaseImportDialog::IsModified() CONST
{
	return((!m_szDatabaseDataFile[0].IsEmpty() && !m_szDatabaseLogsFile[0].IsEmpty() && m_nDatabaseDataSize[0] > 0 && m_nDatabaseDataSize[1] > 0 && m_nDatabaseLogsSize[0] > 0 && m_nDatabaseLogsSize[1] > 0) || IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY));
}

BOOL CDatabaseImportDialog::Check(BOOL bModified) CONST
{
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szSpacecraft;
	CString  szDatabase[2];
	CComputerToken  cComputerToken;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_DATABASE_IMPORT_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_DATABASE_IMPORT_SPACECRAFT)->GetWindowText(szSpacecraft);
	GetDlgItem(IDC_DATABASE_IMPORT_NAME)->GetWindowText(szDatabase[0]);
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->GetWindowText(szDatabase[1]);
	for (nDatabase = 0, nDatabases = (INT)m_pDatabases[0].GetSize(); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases[0].GetAt(nDatabase)) && pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft  &&  !pDatabaseProfileInfo->GetName().CompareNoCase(szDatabase[1])) break;
		continue;
	}
	return(((!IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY) || !IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES)) ? ((GetDlgItem(IDC_DATABASE_IMPORT_SERVER)->SendMessage(CB_GETCURSEL) >= 0 || IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES)) && GetDlgItem(IDC_DATABASE_IMPORT_SPACECRAFT)->SendMessage(CB_GETCURSEL) >= 0 && (GetDlgItem(IDC_DATABASE_IMPORT_NAME)->SendMessage(CB_GETCURSEL) >= 0 || IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES)) && (IsDlgButtonChecked(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL) || IsDlgButtonChecked(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL)) && (szServer.CompareNoCase(cComputerToken.GetComputerName()) || szDatabase[0].CompareNoCase(szDatabase[1])) && ((IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY) && nDatabase < nDatabases) || (!IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY) && nDatabase == nDatabases)) && !szDatabase[1].IsEmpty() && GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION)->GetWindowTextLength() > 0) : (GetDlgItem(IDC_DATABASE_IMPORT_SPACECRAFT)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_DATABASE_IMPORT_LOCATION)->GetWindowTextLength() > 0 && GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER)->SendMessage(CB_GETCURSEL) >= 0 && (IsDlgButtonChecked(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL) || IsDlgButtonChecked(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_LOCAL)) && nDatabase < nDatabases  &&  !szDatabase[1].IsEmpty())) ? (!bModified || IsModified()) : FALSE);
}

void CDatabaseImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseImportDialog::PostNcDestroy()
{
	m_pDatabases[0].RemoveAll();
	m_pDatabases[1].RemoveAll();
	m_szDatabaseUsers[0].RemoveAll();
	m_szDatabaseUsers[1].RemoveAll();
	m_nDatabasePrivileges.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabaseImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_IMPORT_DATAONLY, OnImportDataOnly)
	ON_BN_CLICKED(IDC_DATABASE_IMPORT_DATAFILES, OnImportDataFiles)
	ON_BN_CLICKED(IDC_DATABASE_IMPORT_LOCATION_BROWSE, OnDataFilesBrowse)
	ON_BN_CLICKED(IDC_DATABASE_IMPORT_DESTINATION_DETAILS, OnDatabaseDetails)
	ON_BN_CLICKED(IDC_DATABASE_IMPORT_DESTINATION_USERS, OnDatabaseUsers)
	ON_BN_CLICKED(IDC_DATABASE_IMPORT_DESTINATION_VALIDITY, OnDatabaseValidity)
	ON_BN_CLICKED(IDC_DATABASE_IMPORT_DESTINATION_LOCATION_BROWSE, OnLocationBrowse)
	ON_BN_CLICKED(IDC_DATABASE_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_DATABASE_IMPORT_LOCATION, OnEditchangeDataFilesLocation)
	ON_EN_CHANGE(IDC_DATABASE_IMPORT_DESTINATION_LOCATION, OnEditchangeDestinationDatabaseLocation)
	ON_CBN_EDITCHANGE(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, OnEditchangeDestinationDatabase)
	ON_CBN_SELCHANGE(IDC_DATABASE_IMPORT_SERVER, OnSelchangeServer)
	ON_CBN_SELCHANGE(IDC_DATABASE_IMPORT_SPACECRAFT, OnSelchangeSpacecraft)
	ON_CBN_SELCHANGE(IDC_DATABASE_IMPORT_NAME, OnSelchangeDatabase)
	ON_CBN_SELCHANGE(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER, OnSelchangeDataFilesStringDelimiter)
	ON_CBN_SELCHANGE(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER, OnSelchangeDataFilesFieldDelimiter)
	ON_CBN_SELCHANGE(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER, OnSelchangeDataFilesRowDelimiter)
	ON_CBN_SELCHANGE(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, OnSelchangeDestinationDatabase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseImportDialog message handlers

BOOL CDatabaseImportDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	if (EnumServers() && EnumSpacecrafts() && EnumDatabases())
	{
		EnumStringDelimiters();
		EnumFieldDelimiters();
		EnumRowDelimiters();
	}
	ShowDatabaseInfo();
	return FALSE;
}

void CDatabaseImportDialog::OnSelchangeServer()
{
	EnumSpacecrafts();
	EnumDatabases();
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnSelchangeSpacecraft()
{
	EnumDatabases();
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnSelchangeDatabase()
{
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnImportDataOnly()
{
	INT  nIndex;

	for (ShowDatabaseInfo(), CheckDlgButton(IDC_DATABASE_IMPORT_DATAFILES, FALSE); !IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY); )
	{
		if ((nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountComputerName())) != SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_GETCURSEL))
		{
			SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_SETCURSEL, nIndex);
			EnumSpacecrafts();
			EnumDatabases();
			ShowDatabaseInfo();
		}
		SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER, CB_SETCURSEL, (WPARAM)-1);
		SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER, CB_SETCURSEL, (WPARAM)-1);
		SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER, CB_SETCURSEL, (WPARAM)-1);
		GetDlgItem(IDC_DATABASE_IMPORT_LOCATION)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_DATABASE_IMPORT_FILEPREFIX)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_DATABASE_IMPORT_FILEEXTENSION)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_DATABASE_IMPORT_SERVER_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_SERVER)->EnableWindow();
		GetDlgItem(IDC_DATABASE_IMPORT_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_NAME)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_LOCATION_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_LOCATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_LOCATION_BROWSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FILEPREFIX_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FILEPREFIX)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FILEEXTENSION_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FILEEXTENSION)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FORMAT)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER)->EnableWindow(FALSE);
		break;
	}
	GetDlgItem(IDC_DATABASE_IMPORT_DATAFILES)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY));
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnImportDataFiles()
{
	INT  nIndex;

	for (ShowDatabaseInfo(); (nIndex = (!IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES)) ? (INT)SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountComputerName()) : (INT)SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_GETCURSEL)) != SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_GETCURSEL); )
	{
		SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_SETCURSEL, nIndex);
		EnumSpacecrafts();
		EnumDatabases();
		ShowDatabaseInfo();
		break;
	}
	for (GetDlgItem(IDC_DATABASE_IMPORT_LOCATION)->SetWindowText(EMPTYSTRING), GetDlgItem(IDC_DATABASE_IMPORT_FILEPREFIX)->SetWindowText(EMPTYSTRING), GetDlgItem(IDC_DATABASE_IMPORT_FILEEXTENSION)->SetWindowText(EMPTYSTRING); IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES); )
	{
		SendDlgItemMessage(IDC_DATABASE_IMPORT_SERVER, CB_SETCURSEL, (WPARAM)-1);
		SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_SETCURSEL, (WPARAM)-1);
		break;
	}
	GetDlgItem(IDC_DATABASE_IMPORT_SERVER_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_SERVER)->EnableWindow(!IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_GETCOUNT) > 0 && !IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES)) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_IMPORT_NAME)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_IMPORT_NAME, CB_GETCOUNT) > 0 && !IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES)) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_IMPORT_LOCATION_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_LOCATION)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_LOCATION_BROWSE)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FILEPREFIX_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FILEPREFIX)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FILEEXTENSION_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FILEEXTENSION)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FORMAT)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES));
	SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER, CB_SETCURSEL, (IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES)) ? (WPARAM)SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_DATABASEIMPORTDIALOG_STRINGDELIMITER_DOUBLEQUOTE)) : -1);
	SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER, CB_SETCURSEL, (IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES)) ? (WPARAM)SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_DATABASEIMPORTDIALOG_FIELDDELIMITER_COMMA)) : -1);
	SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER, CB_SETCURSEL, (IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES)) ? (WPARAM)SendDlgItemMessage(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_DATABASEIMPORTDIALOG_ROWDELIMITER_CREOL)) : -1);
	GetDlgItem(IDC_DATABASE_IMPORT_LOCATION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnDataFilesBrowse()
{
	LPMALLOC  pIMalloc;
	LPITEMIDLIST  pItemIDList;
	TCHAR  szItemBuffer[MAX_PATH];
	TCHAR  szDisplayName[MAX_PATH];
	BROWSEINFO  sBrowseInfo = { 0 };

	if (SHGetMalloc(&pIMalloc) == NOERROR)
	{
		sBrowseInfo.hwndOwner = GetSafeHwnd();
		sBrowseInfo.pszDisplayName = szDisplayName;
		sBrowseInfo.lpszTitle = STRING(IDS_DIRECTORYBROWSEDIALOG_TITLE);
		if ((pItemIDList = SHBrowseForFolder(&sBrowseInfo)) != (LPITEMIDLIST)NULL)
		{
			if (SHGetPathFromIDList(pItemIDList, szItemBuffer)) GetDlgItem(IDC_DATABASE_IMPORT_LOCATION)->SetWindowText(szItemBuffer);
			pIMalloc->Free(pItemIDList);
		}
		pIMalloc->Release();
	}
	SendDlgItemMessage(IDC_DATABASE_IMPORT_LOCATION, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_IMPORT_LOCATION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnDatabaseDetails()
{
	CString  szDatabase;
	CString  szStandard;
	CString  szSpacecraft;
	CComputerToken  cComputerToken;
	CDatabaseDetailsDialog  cDatabaseDetailsDialog(this);

	GetDlgItem(IDC_DATABASE_IMPORT_SPACECRAFT)->GetWindowText(szSpacecraft);
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->GetWindowText(szDatabase);
	cDatabaseDetailsDialog.DoModal(cComputerToken.GetComputerName(), szSpacecraft, szDatabase, szStandard, m_szDatabaseDataFile[0], m_szDatabaseDataFile[1], m_nDatabaseDataSize[0], m_nDatabaseDataSize[1], m_nDatabaseDataSize[2], m_szDatabaseLogsFile[0], m_szDatabaseLogsFile[1], m_nDatabaseLogsSize[0], m_nDatabaseLogsSize[1], m_nDatabaseLogsSize[2], m_bDatabaseReadOnly);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnDatabaseUsers()
{
	CString  szDatabase;
	CDatabaseUsersDialog  cDatabaseUsersDialog(this);

	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->GetWindowText(szDatabase);
	cDatabaseUsersDialog.DoModal(szDatabase, m_szDatabaseUsers[0], m_szDatabaseUsers[1], m_nDatabasePrivileges);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnDatabaseValidity()
{
	CString  szDatabase;
	CDatabaseValidityDialog  cDatabaseValidityDialog(this);

	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->GetWindowText(szDatabase);
	cDatabaseValidityDialog.DoModal(szDatabase, m_tDatabaseValidity[0], m_tDatabaseValidity[1]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnLocationBrowse()
{
	LPMALLOC  pIMalloc;
	LPITEMIDLIST  pItemIDList;
	TCHAR  szItemBuffer[MAX_PATH];
	TCHAR  szDisplayName[MAX_PATH];
	BROWSEINFO  sBrowseInfo = { 0 };

	if (SHGetMalloc(&pIMalloc) == NOERROR)
	{
		sBrowseInfo.hwndOwner = GetSafeHwnd();
		sBrowseInfo.pszDisplayName = szDisplayName;
		sBrowseInfo.lpszTitle = STRING(IDS_DIRECTORYBROWSEDIALOG_TITLE);
		if ((pItemIDList = SHBrowseForFolder(&sBrowseInfo)) != (LPITEMIDLIST)NULL)
		{
			if (SHGetPathFromIDList(pItemIDList, szItemBuffer)) GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION)->SetWindowText(szItemBuffer);
			pIMalloc->Free(pItemIDList);
		}
		pIMalloc->Release();
	}
	SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_LOCATION, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_LOCATION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnEditchangeDataFilesLocation()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnEditchangeDestinationDatabase()
{
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnEditchangeDestinationDatabaseLocation()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnSelchangeDataFilesStringDelimiter()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnSelchangeDataFilesFieldDelimiter()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnSelchangeDataFilesRowDelimiter()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnSelchangeDestinationDatabase()
{
	if (SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_IMPORT_DESTINATION_DATABASE, CB_GETCURSEL)) >= 0) ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseImportDialog::OnOK()
{
	INT  nFile;
	INT  nFiles;
	INT  nIndex;
	INT  nResult;
	INT  nDatabase[2];
	INT  nDatabases[2];
	CDBMS  cDBMS;
	CString  szFile;
	CString  szServer;
	CString  szMessage;
	CString  szLocation;
	CString  szFiles[2];
	CString  szFileList;
	CString  szSpacecraft;
	CString  szDatabase[2];
	CString  szDelimiter[3];
	CTimeKey  tDatabaseTime;
	CStringArray  szFailures;
	CComputerToken  cComputerToken;
	CDatabaseProfileInfo  *pDatabaseProfileInfo[2];
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_DATABASE_IMPORT_SERVER)->GetWindowText(szServer), GetDlgItem(IDC_DATABASE_IMPORT_SPACECRAFT)->GetWindowText(szSpacecraft), GetDlgItem(IDC_DATABASE_IMPORT_NAME)->GetWindowText(szDatabase[0]), GetDlgItem(IDC_DATABASE_IMPORT_DESTINATION_DATABASE)->GetWindowText(szDatabase[1]); !IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAONLY); )
	{
		for (nDatabase[0] = 0, nDatabases[0] = (INT)m_pDatabases[1].GetSize(); nDatabase[0] < nDatabases[0]; nDatabase[0]++)
		{
			if ((pDatabaseProfileInfo[0] = m_pDatabases[1].GetAt(nDatabase[0])) != (CDatabaseProfileInfo *)NULL)
			{
				if (!pDatabaseProfileInfo[0]->GetServer().CompareNoCase(szServer) && pDatabaseProfileInfo[0]->GetSpacecraft() == szSpacecraft  &&  pDatabaseProfileInfo[0]->GetName() == szDatabase[0])
				{
					if ((pDatabaseProfileInfo[1] = new CDatabaseProfileInfo))
					{
						pDatabaseProfileInfo[1]->Copy(pDatabaseProfileInfo[0]);
						pDatabaseProfileInfo[1]->SetName(szDatabase[1]);
						pDatabaseProfileInfo[1]->SetServer(cComputerToken.GetComputerName());
						pDatabaseProfileInfo[1]->SetType((IsDlgButtonChecked(IDC_DATABASE_IMPORT_DESTINATION_SCOPE_GLOBAL)) ? ((pDatabaseProfileInfo[1]->GetType() & ~DATABASE_TYPE_LOCAL) | DATABASE_TYPE_GLOBAL) : ((pDatabaseProfileInfo[1]->GetType() & ~DATABASE_TYPE_GLOBAL) | DATABASE_TYPE_LOCAL));
						for (pDatabaseProfileInfo[1]->SetFileName(GetDatabaseFileName()), pDatabaseProfileInfo[1]->SetUpdateFileName(GetDatabaseUpdateFileName()), pDatabaseProfileInfo[1]->SetLibraryFileName(GetDatabaseLibraryFileName()), pDatabaseProfileInfo[1]->SetLibraryUpdateFileName(GetDatabaseLibraryUpdateFileName()), pDatabaseProfileInfo[1]->SetLoggingFileName(GetDatabaseLogFileName()), pDatabaseProfileInfo[1]->SetUsers(m_szDatabaseUsers[0], m_szDatabaseUsers[1], m_nDatabasePrivileges), pDatabaseProfileInfo[1]->SetValidity(m_tDatabaseValidity[0], m_tDatabaseValidity[1]), pDatabaseProfileInfo[1]->SetCreationTime((tDatabaseTime = CTime::GetCurrentTime().GetTime())), pDatabaseProfileInfo[1]->SetLastUpdateTime(tDatabaseTime); (nIndex = m_pDatabases[0].Add(pDatabaseProfileInfo[1])) >= 0; )
						{
							for (szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORT_ERROR), (LPCTSTR)szDatabase[0]); (nResult = cDBMS.ImportDatabase(pDatabaseProfileInfo[0], pDatabaseProfileInfo[1], m_szDatabaseDataFile[0], m_szDatabaseDataFile[1], m_nDatabaseDataSize[0], m_nDatabaseDataSize[1], m_nDatabaseDataSize[2], m_szDatabaseLogsFile[0], m_szDatabaseLogsFile[1], m_nDatabaseLogsSize[0], m_nDatabaseLogsSize[1], m_nDatabaseLogsSize[2], m_bDatabaseReadOnly)) < 0; )
							{
								for (SaveDatabases(), szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORT_WARNING), (LPCTSTR)szDatabase[0]), ShowMessage(szMessage); GetAccountDatabase().IsEmpty(); )
								{
									SetDatabase(szSpacecraft, szDatabase[1]);
									break;
								}
								EndDialog(IDOK);
								return;
							}
							if (!nResult)
							{
								ShowMessage(szMessage);
								m_pDatabases[0].RemoveAt(nIndex);
								delete pDatabaseProfileInfo[1];
								EndDialog(IDCANCEL);
								return;
							}
							for (SaveDatabases(), szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORT_SUCCESSFUL), (LPCTSTR)szDatabase[0]), ShowMessage(szMessage, FALSE); GetAccountDatabase().IsEmpty(); )
							{
								SetDatabase(szSpacecraft, szDatabase[1]);
								break;
							}
							EndDialog(IDOK);
							return;
						}
						delete pDatabaseProfileInfo[1];
					}
					break;
				}
			}
		}
		szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORT_ERROR), (LPCTSTR)szDatabase[0]);
		ShowMessage(szMessage);
		EndDialog(IDCANCEL);
		return;
	}
	if (!IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES))
	{
		for (nDatabase[0] = 0, nDatabases[0] = (INT)m_pDatabases[1].GetSize(); nDatabase[0] < nDatabases[0]; nDatabase[0]++)
		{
			if ((pDatabaseProfileInfo[0] = m_pDatabases[1].GetAt(nDatabase[0])) && !pDatabaseProfileInfo[0]->GetServer().CompareNoCase(szServer) && pDatabaseProfileInfo[0]->GetSpacecraft() == szSpacecraft  &&  pDatabaseProfileInfo[0]->GetName() == szDatabase[0])
			{
				for (nDatabase[1] = 0, nDatabases[1] = (INT)m_pDatabases[0].GetSize(); nDatabase[1] < nDatabases[1]; nDatabase[1]++)
				{
					if ((pDatabaseProfileInfo[1] = m_pDatabases[0].GetAt(nDatabase[1])))
					{
						if (pDatabaseProfileInfo[1]->GetSpacecraft() == szSpacecraft)
						{
							if (!pDatabaseProfileInfo[1]->GetName().CompareNoCase(szDatabase[1]))
							{
								if (cDBMS.ImportDatabase(pDatabaseProfileInfo[0], pDatabaseProfileInfo[1], FALSE))
								{
									for (szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORTDATA_SUCCESSFUL), (LPCTSTR)szDatabase[1]), ShowMessage(szMessage, FALSE); GetAccountSpacecraftName() == szSpacecraft && !GetAccountDatabase().CompareNoCase(szDatabase[1]); )
									{
										SetDatabase();
										break;
									}
									EndDialog(IDOK);
									return;
								}
								break;
							}
						}
					}
				}
				break;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_IMPORT_DATAFILES))
	{
		for (nDatabase[0] = 0, nDatabases[0] = (INT)m_pDatabases[0].GetSize(); nDatabase[0] < nDatabases[0]; nDatabase[0]++)
		{
			if ((pDatabaseProfileInfo[0] = m_pDatabases[0].GetAt(nDatabase[0])) && pDatabaseProfileInfo[0]->GetSpacecraft() == szSpacecraft  &&  !pDatabaseProfileInfo[0]->GetName().CompareNoCase(szDatabase[1]))
			{
				for (GetDlgItem(IDC_DATABASE_IMPORT_LOCATION)->GetWindowText(szLocation), GetDlgItem(IDC_DATABASE_IMPORT_FILEPREFIX)->GetWindowText(szFiles[0]), GetDlgItem(IDC_DATABASE_IMPORT_FILEEXTENSION)->GetWindowText(szFiles[1]), GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_STRINGDELIMITER)->GetWindowText(szDelimiter[0]), GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_FIELDDELIMITER)->GetWindowText(szDelimiter[1]), GetDlgItem(IDC_DATABASE_IMPORT_FORMAT_ROWDELIMITER)->GetWindowText(szDelimiter[2]); szDelimiter[0] == STRING(IDS_DATABASEIMPORTDIALOG_STRINGDELIMITER_NONE); )
				{
					szDelimiter[0].Empty();
					break;
				}
				for (szDelimiter[1] = (szDelimiter[1] == STRING(IDS_DATABASEIMPORTDIALOG_FIELDDELIMITER_TAB)) ? TAB : szDelimiter[1], szDelimiter[2] = (szDelimiter[2] == STRING(IDS_DATABASEIMPORTDIALOG_ROWDELIMITER_CR)) ? CR : ((szDelimiter[2] == STRING(IDS_DATABASEIMPORTDIALOG_ROWDELIMITER_EOL)) ? EOL : (CString(CR) + CString(EOL))); cDBMS.ImportDatabase(pDatabaseProfileInfo[0], szLocation, szFiles[0], szFiles[1], szDelimiter[0], szDelimiter[1], szDelimiter[2], szFailures) && !szFailures.GetSize(); )
				{
					for (szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORTDATA_SUCCESSFUL), (LPCTSTR)szDatabase[1]), ShowMessage(szMessage, FALSE); GetAccountSpacecraftName() == szSpacecraft && !GetAccountDatabase().CompareNoCase(szDatabase[1]); )
					{
						SetDatabase();
						break;
					}
					EndDialog(IDOK);
					return;
				}
				if (szFailures.GetSize() > 0)
				{
					for (nFile = 0, nFiles = (INT)szFailures.GetSize(), szFileList.Empty(); nFile < nFiles; nFile++)
					{
						szFile.Format(STRING(IDS_DATABASE_MESSAGE_IMPORTFILE_NAME), (LPCTSTR)szFailures.GetAt(nFile));
						szFileList += (nFile > 0) ? (STRING(IDS_DATABASE_MESSAGE_IMPORTFILE_SEPARATOR) + szFile) : szFile;
					}
					for (szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORTFILES_ERROR), (LPCTSTR)szDatabase[1], (LPCTSTR)szFileList), ShowMessage(szMessage); GetAccountSpacecraftName() == szSpacecraft && !GetAccountDatabase().CompareNoCase(szDatabase[1]); )
					{
						SetDatabase();
						break;
					}
					EndDialog(IDOK);
					return;
				}
				break;
			}
		}
	}
	szMessage.Format(STRING(IDS_DATABASE_MESSAGE_IMPORTDATA_ERROR), (LPCTSTR)szDatabase[1]);
	ShowMessage(szMessage);
	EndDialog(IDCANCEL);
}

void CDatabaseImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabaseImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseExportDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseExportDialog, CLocaleDialog)

CDatabaseExportDialog::CDatabaseExportDialog(CWnd *pParentWnd) : CLocaleDialog(CDatabaseExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDatabaseExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CDatabaseExportDialog::EnumServers()
{
	INT  nServer;
	INT  nServers;
	CString  szServer;
	CDatabases  cDatabases;
	CStringArray  szServers;
	CStringArray  szDatabases;

	SendDlgItemMessage(IDC_DATABASE_EXPORT_SERVER, CB_RESETCONTENT);
	for (nServer = 0, nServers = GetNetworkBrowseService()->EnumNetworkComputers(szServers); nServer < nServers; nServer++)
	{
		for (cDatabases.SetComputerName((szServer = szServers.GetAt(nServer))); SendDlgItemMessage(IDC_DATABASE_EXPORT_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szServer) == CB_ERR && (cDatabases.IsHost() || cDatabases.EnumDatabases(szDatabases, TRUE) > 0); )
		{
			SendDlgItemMessage(IDC_DATABASE_EXPORT_SERVER, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szServers.GetAt(nServer));
			break;
		}
	}
	SendDlgItemMessage(IDC_DATABASE_EXPORT_SERVER, CB_SETCURSEL, max(SendDlgItemMessage(IDC_DATABASE_EXPORT_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountComputerName()), 0));
	GetDlgItem(IDC_DATABASE_EXPORT_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_SERVER_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_SERVER)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_EXPORT_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseExportDialog::EnumSpacecrafts()
{
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szSpacecraft;
	CDatabases  cDatabases;
	CComputerToken  cComputerToken;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	SendDlgItemMessage(IDC_DATABASE_EXPORT_SPACECRAFT, CB_RESETCONTENT);
	GetDlgItem(IDC_DATABASE_EXPORT_SERVER)->GetWindowText(szServer);
	for (nDatabase = 0, nDatabases = (cDatabases.SetComputerName(szServer) && cDatabases.GetDatabases(m_pDatabases, TRUE)) ? (INT)m_pDatabases.GetSize() : 0; (!nDatabase && !nDatabases && !GetAccountSpacecraftName().IsEmpty()) || nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase)) != (CDatabaseProfileInfo *)NULL  &&  !pDatabaseProfileInfo->GetServer().Compare(szServer))
		{
			if (SendDlgItemMessage(IDC_DATABASE_EXPORT_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szSpacecraft = pDatabaseProfileInfo->GetSpacecraft())) == CB_ERR)
			{
				SendDlgItemMessage(IDC_DATABASE_EXPORT_SPACECRAFT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szSpacecraft);
				continue;
			}
		}
		if (!nDatabases)
		{
			SendDlgItemMessage(IDC_DATABASE_EXPORT_SPACECRAFT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)GetAccountSpacecraftName());
			break;
		}
	}
	SendDlgItemMessage(IDC_DATABASE_EXPORT_SPACECRAFT, CB_SETCURSEL, max(SendDlgItemMessage(IDC_DATABASE_EXPORT_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountSpacecraftName()), 0));
	GetDlgItem(IDC_DATABASE_EXPORT_SPACECRAFT_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_SPACECRAFT)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_EXPORT_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseExportDialog::EnumDatabases()
{
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szDatabase;
	CString  szSpacecraft;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	SendDlgItemMessage(IDC_DATABASE_EXPORT_NAME, CB_RESETCONTENT);
	GetDlgItem(IDC_DATABASE_EXPORT_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_DATABASE_EXPORT_SPACECRAFT)->GetWindowText(szSpacecraft);
	for (nDatabase = 0, nDatabases = (INT)m_pDatabases.GetSize(); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetServer() == szServer  &&  pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft)
		{
			if (SendDlgItemMessage(IDC_DATABASE_EXPORT_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szDatabase = pDatabaseProfileInfo->GetName())) == CB_ERR)
			{
				SendDlgItemMessage(IDC_DATABASE_EXPORT_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDatabase);
				continue;
			}
		}
	}
	SendDlgItemMessage(IDC_DATABASE_EXPORT_NAME, CB_SETCURSEL);
	GetDlgItem(IDC_DATABASE_EXPORT_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_NAME)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_EXPORT_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseExportDialog::EnumStringDelimiters()
{
	INT  nDelimiter;
	INT  nDelimiters;

	for (nDelimiter = 0, nDelimiters = MAXDATABASEEXPORTSTRINGDELIMITER - MINDATABASEEXPORTSTRINGDELIMITER; nDelimiter <= nDelimiters; nDelimiter++)
	{
		SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINDATABASEEXPORTSTRINGDELIMITER + nDelimiter));
		continue;
	}
	SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_DATABASEEXPORTDIALOG_STRINGDELIMITER_DOUBLEQUOTE)));
	GetDlgItem(IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

BOOL CDatabaseExportDialog::EnumFieldDelimiters()
{
	INT  nDelimiter;
	INT  nDelimiters;

	for (nDelimiter = 0, nDelimiters = MAXDATABASEEXPORTFIELDDELIMITER - MINDATABASEEXPORTFIELDDELIMITER; nDelimiter <= nDelimiters; nDelimiter++)
	{
		SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINDATABASEEXPORTFIELDDELIMITER + nDelimiter));
		continue;
	}
	SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_DATABASEEXPORTDIALOG_FIELDDELIMITER_COMMA)));
	GetDlgItem(IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

BOOL CDatabaseExportDialog::EnumRowDelimiters()
{
	INT  nDelimiter;
	INT  nDelimiters;

	for (nDelimiter = 0, nDelimiters = MAXDATABASEEXPORTROWDELIMITER - MINDATABASEEXPORTROWDELIMITER; nDelimiter <= nDelimiters; nDelimiter++)
	{
		SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINDATABASEEXPORTROWDELIMITER + nDelimiter));
		continue;
	}
	SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_DATABASEEXPORTDIALOG_ROWDELIMITER_CREOL)));
	GetDlgItem(IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

VOID CDatabaseExportDialog::ShowDatabaseInfo()
{
	INT  nTable;
	INT  nTables;
	CDBMS  cDBMS;
	CString  szServer;
	CString  szDatabase;
	CString  szSpacecraft;
	CStringArray  szTables;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_DATABASE_EXPORT_NAME)->GetWindowText(szDatabase);
	GetDlgItem(IDC_DATABASE_EXPORT_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_DATABASE_EXPORT_SPACECRAFT)->GetWindowText(szSpacecraft);
	for (SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_RESETCONTENT), SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_RESETCONTENT); (pDatabaseProfileInfo = (IsDlgButtonChecked(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTS)) ? new CDatabaseProfileInfo : (CDatabaseProfileInfo *)NULL); )
	{
		for (nTable = 0, pDatabaseProfileInfo->SetServer(szServer), pDatabaseProfileInfo->SetSpacecraft(szSpacecraft), pDatabaseProfileInfo->SetName(szDatabase), nTables = cDBMS.EnumDatabaseTables(pDatabaseProfileInfo, szTables); nTable < nTables; nTable++)
		{
			SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szTables.GetAt(nTable));
			continue;
		}
		SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_SETCURSEL);
		delete pDatabaseProfileInfo;
		break;
	}
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_ADD)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVEALL)->EnableWindow(FALSE);
}

BOOL CDatabaseExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_DATABASE_EXPORT_SERVER)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_DATABASE_EXPORT_SPACECRAFT)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_DATABASE_EXPORT_NAME)->SendMessage(CB_GETCURSEL) >= 0 && (IsDlgButtonChecked(IDC_DATABASE_EXPORT_DIRECTIVES_COMPLETE) || GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST)->SendMessage(LB_GETCOUNT) > 0) && GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_LOCATION)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CDatabaseExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseExportDialog::PostNcDestroy()
{
	m_pDatabases.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabaseExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_EXPORT_DIRECTIVES_COMPLETE, OnExportComplete)
	ON_BN_CLICKED(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTS, OnExportComponents)
	ON_BN_CLICKED(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_ADD, OnAddComponent)
	ON_BN_CLICKED(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVE, OnRemoveComponent)
	ON_BN_CLICKED(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVEALL, OnRemoveAllComponents)
	ON_BN_CLICKED(IDC_DATABASE_EXPORT_DESTINATION_LOCATION_BROWSE, OnLocationBrowse)
	ON_BN_CLICKED(IDC_DATABASE_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_DATABASE_EXPORT_DESTINATION_LOCATION, OnEditchangeDataFilesLocation)
	ON_CBN_SELCHANGE(IDC_DATABASE_EXPORT_SERVER, OnSelchangeServer)
	ON_CBN_SELCHANGE(IDC_DATABASE_EXPORT_SPACECRAFT, OnSelchangeSpacecraft)
	ON_CBN_SELCHANGE(IDC_DATABASE_EXPORT_NAME, OnSelchangeDatabase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseExportDialog message handlers

BOOL CDatabaseExportDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	if (EnumServers() && EnumSpacecrafts() && EnumDatabases())
	{
		CheckDlgButton(IDC_DATABASE_EXPORT_DIRECTIVES_COMPLETE, TRUE);
		GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPLETE)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_LOCATION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_LOCATION)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_LOCATION_BROWSE)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_FILEPREFIX_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_FILEPREFIX)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_FILEEXTENSION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_FILEEXTENSION)->EnableWindow();
		GetDlgItem(IDC_DATABASE_EXPORT_FORMAT_UNICODE)->EnableWindow();
		EnumStringDelimiters();
		EnumFieldDelimiters();
		EnumRowDelimiters();
	}
	return FALSE;
}

void CDatabaseExportDialog::OnExportComplete()
{
	CHourglassCursor  cCursor;

	ShowDatabaseInfo();
}

void CDatabaseExportDialog::OnExportComponents()
{
	CHourglassCursor  cCursor;

	ShowDatabaseInfo();
}

void CDatabaseExportDialog::OnAddComponent()
{
	INT  nIndex;
	CString  szItem;
	CHourglassCursor  cCursor;

	for (szItem = Listbox_GetText(GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL), (nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCURSEL))); SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_DELETESTRING, nIndex) >= 0; )
	{
		SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szItem));
		SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_SETCURSEL);
		break;
	}
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_ADD)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	if (!SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCOUNT)) GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseExportDialog::OnRemoveComponent()
{
	INT  nIndex;
	CString  szItem;
	CHourglassCursor  cCursor;

	for (szItem = Listbox_GetText(GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST), (nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCURSEL))); SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_DELETESTRING, nIndex) >= 0; )
	{
		SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szItem));
		SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_SETCURSEL);
		break;
	}
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_ADD)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	if (!SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCOUNT)) GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseExportDialog::OnRemoveAllComponents()
{
	INT  nIndex;
	INT  nCount;
	CStringArray  szItems;
	CHourglassCursor  cCursor;

	for (nIndex = 0, nCount = (INT)SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCOUNT); nIndex < nCount; nIndex++)
	{
		szItems.Add(Listbox_GetText(GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST), nIndex));
		continue;
	}
	for (nIndex = 0, SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_RESETCONTENT); nIndex < nCount; nIndex++)
	{
		SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_ADDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szItems.GetAt(nIndex));
		continue;
	}
	SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_SETCURSEL, ((nIndex = (INT)SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCURSEL)) >= 0) ? nIndex : 0);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_ADD)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENT_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLISTALL)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseExportDialog::OnLocationBrowse()
{
	LPMALLOC  pIMalloc;
	LPITEMIDLIST  pItemIDList;
	TCHAR  szItemBuffer[MAX_PATH];
	TCHAR  szDisplayName[MAX_PATH];
	BROWSEINFO  sBrowseInfo = { 0 };

	if (SHGetMalloc(&pIMalloc) == NOERROR)
	{
		sBrowseInfo.hwndOwner = GetSafeHwnd();
		sBrowseInfo.pszDisplayName = szDisplayName;
		sBrowseInfo.lpszTitle = STRING(IDS_DIRECTORYBROWSEDIALOG_TITLE);
		if ((pItemIDList = SHBrowseForFolder(&sBrowseInfo)) != (LPITEMIDLIST)NULL)
		{
			if (SHGetPathFromIDList(pItemIDList, szItemBuffer)) GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_LOCATION)->SetWindowText(szItemBuffer);
			pIMalloc->Free(pItemIDList);
		}
		pIMalloc->Release();
	}
	SendDlgItemMessage(IDC_DATABASE_EXPORT_DESTINATION_LOCATION, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_LOCATION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseExportDialog::OnEditchangeDataFilesLocation()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseExportDialog::OnSelchangeServer()
{
	EnumSpacecrafts();
	EnumDatabases();
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseExportDialog::OnSelchangeSpacecraft()
{
	EnumDatabases();
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseExportDialog::OnSelchangeDatabase()
{
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseExportDialog::OnOK()
{
	INT  nFile;
	INT  nFiles;
	INT  nTable;
	INT  nTables;
	CDBMS  cDBMS;
	CString  szFile;
	CString  szServer;
	CString  szMessage;
	CString  szDatabase;
	CString  szLocation;
	CString  szFileList;
	CString  szFiles[2];
	CString  szSpacecraft;
	CString  szDelimiter[3];
	CStringArray  szTables;
	CStringArray  szFailures;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_DATABASE_EXPORT_SERVER)->GetWindowText(szServer), GetDlgItem(IDC_DATABASE_EXPORT_SPACECRAFT)->GetWindowText(szSpacecraft), GetDlgItem(IDC_DATABASE_EXPORT_NAME)->GetWindowText(szDatabase), GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_LOCATION)->GetWindowText(szLocation), GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_FILEPREFIX)->GetWindowText(szFiles[0]), GetDlgItem(IDC_DATABASE_EXPORT_DESTINATION_FILEEXTENSION)->GetWindowText(szFiles[1]); (pDatabaseProfileInfo = new CDatabaseProfileInfo); )
	{
		for (pDatabaseProfileInfo->SetServer(szServer), pDatabaseProfileInfo->SetSpacecraft(szSpacecraft), pDatabaseProfileInfo->SetName(szDatabase); IsDlgButtonChecked(IDC_DATABASE_EXPORT_DIRECTIVES_COMPLETE); )
		{
			cDBMS.EnumDatabaseTables(pDatabaseProfileInfo, szTables);
			break;
		}
		for (nTable = 0, nTables = (IsDlgButtonChecked(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTS)) ? (INT)SendDlgItemMessage(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST, LB_GETCOUNT) : 0; nTable < nTables; nTable++)
		{
			szTables.Add(Listbox_GetText(GetDlgItem(IDC_DATABASE_EXPORT_DIRECTIVES_COMPONENTSLIST), nTable));
			continue;
		}
		for (GetDlgItem(IDC_DATABASE_EXPORT_FORMAT_STRINGDELIMITER)->GetWindowText(szDelimiter[0]), GetDlgItem(IDC_DATABASE_EXPORT_FORMAT_FIELDDELIMITER)->GetWindowText(szDelimiter[1]), GetDlgItem(IDC_DATABASE_EXPORT_FORMAT_ROWDELIMITER)->GetWindowText(szDelimiter[2]), szDelimiter[1] = (szDelimiter[1] == STRING(IDS_DATABASEEXPORTDIALOG_FIELDDELIMITER_TAB)) ? TAB : szDelimiter[1], szDelimiter[2] = (szDelimiter[2] == STRING(IDS_DATABASEEXPORTDIALOG_ROWDELIMITER_CR)) ? CR : ((szDelimiter[2] == STRING(IDS_DATABASEEXPORTDIALOG_ROWDELIMITER_EOL)) ? EOL : (CString(CR) + CString(EOL))); szDelimiter[0] == STRING(IDS_DATABASEEXPORTDIALOG_STRINGDELIMITER_NONE); )
		{
			szDelimiter[0].Empty();
			break;
		}
		if (cDBMS.ExportDatabase(pDatabaseProfileInfo, szTables, szLocation, szFiles[0], szFiles[1], szDelimiter[0], szDelimiter[1], szDelimiter[2], IsDlgButtonChecked(IDC_DATABASE_EXPORT_FORMAT_UNICODE), szFailures))
		{
			szMessage.Format(STRING(IDS_DATABASE_MESSAGE_EXPORTDATA_SUCCESSFUL), (LPCTSTR)szDatabase);
			ShowMessage(szMessage, FALSE);
			delete pDatabaseProfileInfo;
			EndDialog(IDOK);
			return;
		}
		if (!szFailures.GetSize())
		{
			szMessage.Format(STRING(IDS_DATABASE_MESSAGE_EXPORTDATA_ERROR), (LPCTSTR)szDatabase);
			ShowMessage(szMessage, TRUE);
			delete pDatabaseProfileInfo;
			EndDialog(IDCANCEL);
			return;
		}
		for (nFile = 0, nFiles = (INT)szFailures.GetSize(), szFileList.Empty(); nFile < nFiles; nFile++)
		{
			szFile.Format(STRING(IDS_DATABASE_MESSAGE_EXPORTFILE_NAME), (LPCTSTR)szFailures.GetAt(nFile));
			szFileList += (nFile > 0) ? (STRING(IDS_DATABASE_MESSAGE_EXPORTFILE_SEPARATOR) + szFile) : szFile;
		}
		szMessage.Format(STRING(IDS_DATABASE_MESSAGE_EXPORTFILES_ERROR), (LPCTSTR)szDatabase[1], (LPCTSTR)szFileList);
		ShowMessage(szMessage, TRUE);
		delete pDatabaseProfileInfo;
		EndDialog(IDOK);
		return;
	}
	szMessage.Format(STRING(IDS_DATABASE_MESSAGE_EXPORTDATA_ERROR), (LPCTSTR)szDatabase);
	ShowMessage(szMessage);
	EndDialog(IDCANCEL);
}

void CDatabaseExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabaseExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseDeleteDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseDeleteDialog, CLocaleDialog)

CDatabaseDeleteDialog::CDatabaseDeleteDialog(CWnd *pParentWnd) : CLocaleDialog(CDatabaseDeleteDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDatabaseDeleteDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CDatabaseDeleteDialog::EnumServers()
{
	INT  nServer;
	INT  nServers;
	CString  szServer;
	CDatabases  cDatabases;
	CStringArray  szServers;
	CStringArray  szDatabases;
	CComputerToken  cComputerToken;

	SendDlgItemMessage(IDC_DATABASE_DELETE_SERVER, CB_RESETCONTENT);
	for (nServer = 0, nServers = GetNetworkBrowseService()->EnumNetworkComputers(szServers); nServer < nServers; nServer++)
	{
		if ((!szServers.GetAt(nServer).CompareNoCase(cComputerToken.GetComputerName()) && CheckAccountPrivilege(PRIVILEGE_DATABASE_DELETE)) || (szServers.GetAt(nServer).CompareNoCase(cComputerToken.GetComputerName()) && CheckAccountPrivilege(PRIVILEGE_DATABASE_REMOTEDELETE)))
		{
			for (cDatabases.SetComputerName((szServer = szServers.GetAt(nServer))); SendDlgItemMessage(IDC_DATABASE_DELETE_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szServer) == CB_ERR && (cDatabases.IsHost() || cDatabases.EnumDatabases(szDatabases, TRUE) > 0); )
			{
				SendDlgItemMessage(IDC_DATABASE_DELETE_SERVER, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szServers.GetAt(nServer));
				break;
			}
		}
	}
	SendDlgItemMessage(IDC_DATABASE_DELETE_SERVER, CB_SETCURSEL, max(SendDlgItemMessage(IDC_DATABASE_DELETE_SERVER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountComputerName()), 0));
	GetDlgItem(IDC_DATABASE_DELETE_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DELETE_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_DELETE_SERVER_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DELETE_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_DELETE_SERVER)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DELETE_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_DELETE_SERVER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseDeleteDialog::EnumSpacecrafts()
{
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szSpacecraft;
	CDatabases  cDatabases;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_DATABASE_DELETE_SERVER)->GetWindowText(szServer);
	SendDlgItemMessage(IDC_DATABASE_DELETE_SPACECRAFT, CB_RESETCONTENT);
	for (nDatabase = 0, nDatabases = (cDatabases.SetComputerName(szServer) && cDatabases.GetDatabases(m_pDatabases, TRUE)) ? (INT)m_pDatabases.GetSize() : 0; (!nDatabase && !nDatabases && !GetAccountSpacecraftName().IsEmpty()) || nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase)) != (CDatabaseProfileInfo *)NULL  &&  !pDatabaseProfileInfo->GetServer().Compare(szServer))
		{
			if (SendDlgItemMessage(IDC_DATABASE_DELETE_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szSpacecraft = pDatabaseProfileInfo->GetSpacecraft())) == CB_ERR)
			{
				SendDlgItemMessage(IDC_DATABASE_DELETE_SPACECRAFT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szSpacecraft);
				continue;
			}
		}
		if (!nDatabases)
		{
			SendDlgItemMessage(IDC_DATABASE_DELETE_SPACECRAFT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)GetAccountSpacecraftName());
			break;
		}
	}
	SendDlgItemMessage(IDC_DATABASE_DELETE_SPACECRAFT, CB_SETCURSEL, max(SendDlgItemMessage(IDC_DATABASE_DELETE_SPACECRAFT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountSpacecraftName()), 0));
	GetDlgItem(IDC_DATABASE_DELETE_SPACECRAFT_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DELETE_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_DELETE_SPACECRAFT)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DELETE_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_DELETE_SPACECRAFT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseDeleteDialog::EnumDatabases()
{
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szDatabase;
	CString  szSpacecraft;
	CComputerToken  cComputerToken;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	SendDlgItemMessage(IDC_DATABASE_DELETE_DATABASES, CB_RESETCONTENT);
	GetDlgItem(IDC_DATABASE_DELETE_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_DATABASE_DELETE_SPACECRAFT)->GetWindowText(szSpacecraft);
	for (nDatabase = 0, nDatabases = (INT)m_pDatabases.GetSize(); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetServer() == szServer  &&  pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft)
		{
			if (SendDlgItemMessage(IDC_DATABASE_DELETE_DATABASES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szDatabase = pDatabaseProfileInfo->GetName())) == LB_ERR)
			{
				SendDlgItemMessage(IDC_DATABASE_DELETE_DATABASES, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDatabase);
				continue;
			}
		}
	}
	SendDlgItemMessage(IDC_DATABASE_DELETE_DATABASES, CB_SETCURSEL);
	GetDlgItem(IDC_DATABASE_DELETE_DATABASES_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DELETE_DATABASES, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_DELETE_DATABASES)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_DELETE_DATABASES, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_DELETE_DATABASES, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CDatabaseDeleteDialog::ShowDatabaseInfo()
{
	UINT  nType;
	INT  nDatabase;
	INT  nDatabases;
	CString  szServer;
	CString  szTime[2];
	CString  szDatabase;
	CString  szSpacecraft;
	CTimeKey  tTime[3];
	CUIntArray  nPrivileges;
	CStringArray  szUsers;
	CStringArray  szPasswords;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;

	GetDlgItem(IDC_DATABASE_DELETE_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_DATABASE_DELETE_DATABASES)->GetWindowText(szDatabase);
	GetDlgItem(IDC_DATABASE_DELETE_SPACECRAFT)->GetWindowText(szSpacecraft);
	for (nDatabase = 0, nDatabases = (INT)m_pDatabases.GetSize(); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = m_pDatabases.GetAt(nDatabase)) && pDatabaseProfileInfo->GetServer() == szServer  &&  pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft  &&  pDatabaseProfileInfo->GetName() == szDatabase  &&  pDatabaseProfileInfo->GetUsers(szUsers, szPasswords, nPrivileges) > 0 && pDatabaseProfileInfo->GetValidity(tTime[1], tTime[2]) >= 0)
		{
			szTime[0] = (tTime[0] = pDatabaseProfileInfo->GetCreationTime()).FormatGmt(STRING(IDS_DATABASEDELETEDIALOG_CREATIONTIMEFORMAT));
			szTime[1] = (m_tDatabaseValidity[0] = tTime[1]).FormatGmt(CString(STRING(IDS_DATABASEDELETEDIALOG_VALIDITYTIMEFORMAT)).Left(lstrlen(STRING(IDS_DATABASEDELETEDIALOG_VALIDITYTIMEFORMAT)) / 2));
			szTime[1] += (m_tDatabaseValidity[1] = tTime[2]).FormatGmt(CString(STRING(IDS_DATABASEDELETEDIALOG_VALIDITYTIMEFORMAT)).Mid(lstrlen(STRING(IDS_DATABASEDELETEDIALOG_VALIDITYTIMEFORMAT)) / 2));
			szTime[1] = (tTime[1] > 0 && tTime[2] > 0 && tTime[1] <= tTime[2]) ? (LPCTSTR)szTime[1] : STRING(IDS_DATABASEDELETEDIALOG_UNLIMITEDVALIDITY);
			CheckDlgButton(IDC_DATABASE_DELETE_CHARACTERISTICS_GLOBAL, ((nType = pDatabaseProfileInfo->GetType()) & DATABASE_TYPE_GLOBAL) ? TRUE : FALSE);
			CheckDlgButton(IDC_DATABASE_DELETE_CHARACTERISTICS_LOCAL, (nType & DATABASE_TYPE_LOCAL) ? TRUE : FALSE);
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_STANDARD)->SetWindowText((nType & DATABASE_TYPE_STANDARD_PCM) ? STRING(IDS_DATABASE_STANDARD_PCM) : ((nType & DATABASE_TYPE_STANDARD_CCSDS) ? STRING(IDS_DATABASE_STANDARD_CCSDS) : (LPCTSTR)m_szStandard));
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION)->SetWindowText((nType & DATABASE_TYPE_IMPLEMENTATION_SCOS) ? STRING(IDS_DATABASE_IMPLEMENTATION_SCOS) : ((nType & DATABASE_TYPE_IMPLEMENTATION_ALTEL) ? STRING(IDS_DATABASE_IMPLEMENTATION_ALTEL) : (LPCTSTR)m_szImplementation));
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_OWNER)->SetWindowText(szUsers.GetAt(0));
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_TIME)->SetWindowText(szTime[0]);
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_VALIDITY)->SetWindowText(szTime[1]);
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_SCOPE)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_GLOBAL)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_LOCAL)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_STANDARD_STATIC)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_STANDARD)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION_STATIC)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_OWNER_STATIC)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_OWNER)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_TIME_STATIC)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_TIME)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_VALIDITY_STATIC)->EnableWindow();
			GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_VALIDITY)->EnableWindow();
			break;
		}
	}
	if (nDatabase == nDatabases)
	{
		CheckDlgButton(IDC_DATABASE_DELETE_CHARACTERISTICS_GLOBAL, FALSE);
		CheckDlgButton(IDC_DATABASE_DELETE_CHARACTERISTICS_LOCAL, FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_STANDARD)->SetWindowText(m_szStandard);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION)->SetWindowText(m_szImplementation);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_OWNER)->SetWindowText(m_szOwner);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_TIME)->SetWindowText(m_szTime);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_VALIDITY)->SetWindowText(m_szValidity);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_SCOPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_GLOBAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_LOCAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_STANDARD_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_STANDARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_OWNER_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_OWNER)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_TIME_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_VALIDITY_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_VALIDITY)->EnableWindow(FALSE);
	}
}

BOOL CDatabaseDeleteDialog::IsModified() CONST
{
	return TRUE;
}

BOOL CDatabaseDeleteDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_DATABASE_DELETE_SERVER)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_DATABASE_DELETE_SPACECRAFT)->SendMessage(CB_GETCURSEL) >= 0 && GetDlgItem(IDC_DATABASE_DELETE_DATABASES)->SendMessage(CB_GETCURSEL) >= 0) ? (!bModified || IsModified()) : FALSE);
}

void CDatabaseDeleteDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseDeleteDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseDeleteDialog::PostNcDestroy()
{
	m_pDatabases.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseDeleteDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabaseDeleteDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_DELETE_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_DATABASE_DELETE_SERVER, OnSelchangeServer)
	ON_CBN_SELCHANGE(IDC_DATABASE_DELETE_SPACECRAFT, OnSelchangeSpacecraft)
	ON_LBN_SELCHANGE(IDC_DATABASE_DELETE_DATABASES, OnSelchangeDatabase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDeleteDialog message handlers

BOOL CDatabaseDeleteDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	if (EnumServers() && EnumSpacecrafts() && EnumDatabases())
	{
		AccessControl(IDC_DATABASE_DELETE_CHARACTERISTICS_GLOBAL, FALSE);
		AccessControl(IDC_DATABASE_DELETE_CHARACTERISTICS_LOCAL, FALSE);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_STANDARD)->GetWindowText(m_szStandard);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_COMPATIBILITY_IMPLEMENTATION)->GetWindowText(m_szImplementation);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_OWNER)->GetWindowText(m_szOwner);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_TIME)->GetWindowText(m_szTime);
		GetDlgItem(IDC_DATABASE_DELETE_CHARACTERISTICS_VALIDITY)->GetWindowText(m_szValidity);
	}
	ShowDatabaseInfo();
	GetDlgItem(IDC_DATABASE_DELETE_SERVER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return FALSE;
}

void CDatabaseDeleteDialog::OnSelchangeServer()
{
	EnumSpacecrafts();
	EnumDatabases();
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDeleteDialog::OnSelchangeSpacecraft()
{
	EnumDatabases();
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDeleteDialog::OnSelchangeDatabase()
{
	ShowDatabaseInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseDeleteDialog::OnOK()
{
	INT  nDatabase;
	INT  nDatabases;
	BOOL  bSuccess;
	CDBMS  cDBMS;
	CString  szServer;
	CString  szMessage;
	CString  szDatabase;
	CString  szSpacecraft;
	CProfile  cProfile;
	CFileFind  cFileFind;
	CDatabases  cDatabases;
	CBinaryDatabase  *pDatabase;
	CDatabaseProfiles  pDatabaseProfiles;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_DATABASE_DELETE_SERVER)->GetWindowText(szServer);
	GetDlgItem(IDC_DATABASE_DELETE_DATABASES)->GetWindowText(szDatabase);
	GetDlgItem(IDC_DATABASE_DELETE_SPACECRAFT)->GetWindowText(szSpacecraft);
	for (nDatabase = 0, nDatabases = (cDatabases.SetComputerName(szServer) && cDatabases.GetDatabases(pDatabaseProfiles, TRUE)) ? (INT)pDatabaseProfiles.GetSize() : 0; nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = pDatabaseProfiles.GetAt(nDatabase)) && pDatabaseProfileInfo->GetServer() == szServer  &&  pDatabaseProfileInfo->GetSpacecraft() == szSpacecraft  &&  pDatabaseProfileInfo->GetName() == szDatabase)
		{
			if ((pDatabase = new CBinaryDatabase(pDatabaseProfileInfo)) != (CBinaryDatabase *)NULL)
			{
				for (bSuccess = pDatabase->Delete(); pDatabaseProfileInfo->GetType() & DATABASE_TYPE_SUPPORT_DBMS; )
				{
					bSuccess &= cDBMS.DeleteDatabase(pDatabaseProfileInfo);
					break;
				}
				for (cProfile.DeleteDatabaseInfo(szDatabase); cFileFind.FindFile(pDatabaseProfileInfo->GetLoggingFileName()) && !cFileFind.FindNextFile(); )
				{
					CFileEx::SetAttributes(cFileFind.GetFilePath(), CFileEx::GetAttributes(cFileFind.GetFilePath()) & ~FILE_ATTRIBUTE_READONLY);
					CFileEx::Remove(cFileFind.GetFilePath());
					cFileFind.Close();
					break;
				}
				for (GetMainWnd()->RemoveMRUMenuItem(pDatabaseProfileInfo), pDatabaseProfiles.RemoveAt(nDatabase); !cDatabases.SetDatabases(pDatabaseProfiles); )
				{
					bSuccess = FALSE;
					break;
				}
				for (; !GetAccountComputerName().CompareNoCase(szServer) && GetAccountSpacecraftName() == szSpacecraft && GetAccountDatabase() == szDatabase; )
				{
					SetDatabase(szServer, szSpacecraft, EMPTYSTRING, FALSE);
					break;
				}
				for (szMessage.Format((bSuccess) ? STRING(IDS_DATABASE_MESSAGE_DELETION_SUCCESSFUL) : STRING(IDS_DATABASE_MESSAGE_DELETION_ERROR), (LPCTSTR)szDatabase), ShowMessage(szMessage, !bSuccess); bSuccess; )
				{
					delete pDatabaseProfileInfo;
					delete pDatabase;
					EndDialog(IDOK);
					return;
				}
				delete pDatabaseProfileInfo;
				delete pDatabase;
				EndDialog(IDCANCEL);
				return;
			}
			szMessage.Format(STRING(IDS_DATABASE_MESSAGE_DELETION_ERROR), (LPCTSTR)szDatabase);
			ShowMessage(szMessage);
			EndDialog(IDCANCEL);
			return;
		}
	}
	szMessage.Format(STRING(IDS_DATABASE_MESSAGE_DELETION_WARNING), (LPCTSTR)szDatabase);
	ShowMessage(szMessage);
	EndDialog(IDCANCEL);
}

void CDatabaseDeleteDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabaseDeleteDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEDELETEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseDeleteDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEDELETEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseVersioningDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseVersioningDialog, CLocaleDialog)

CDatabaseVersioningDialog::CDatabaseVersioningDialog(CWnd *pParentWnd) : CLocaleDialog(CDatabaseVersioningDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDatabaseVersioningDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CDatabaseVersioningDialog::Initialize()
{
	CDatabaseEngine  *pDatabaseEngine;

	if ((pDatabaseEngine = GetDatabase()->GetDatabaseEngine()))
	{
		m_pDatabaseVersions[0].Copy(pDatabaseEngine);
		m_pDatabaseVersions[1].Copy(pDatabaseEngine);
	}
	return TRUE;
}

VOID CDatabaseVersioningDialog::EnumVersionHistory(INT nIndex)
{
	INT  nColumn;
	INT  nColumns;
	INT  nVersion;
	INT  nVersions;
	CString  szItem;
	CDatabaseVersion  *pDatabaseVersion;

	for (nVersion = 0, nVersions = (INT)m_pDatabaseVersions[0].GetSize(); nVersion < nVersions; nVersion++)
	{
		if ((pDatabaseVersion = m_pDatabaseVersions[0].GetAt(nVersion)) != (CDatabaseVersion *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_NAME); )
				{
					szItem = pDatabaseVersion->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_RELEASE); )
				{
					szItem = (!pDatabaseVersion->GetRelease().IsEmpty()) ? pDatabaseVersion->GetRelease() : STRING(IDS_DATABASEVERSIONINGDIALOG_SYMBOL_NORELEASE);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_ISSUE); )
				{
					szItem = (!pDatabaseVersion->GetIssue().IsEmpty()) ? pDatabaseVersion->GetIssue() : STRING(IDS_DATABASEVERSIONINGDIALOG_SYMBOL_NOISSUE);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_COMMENT); )
				{
					szItem = (!pDatabaseVersion->GetComment().IsEmpty()) ? pDatabaseVersion->GetComment() : STRING(IDS_DATABASEVERSIONINGDIALOG_SYMBOL_NOCOMMENT);
					break;
				}
				if (!nColumn  &&  nVersion >= SendDlgItemMessage(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY, LVM_GETITEMCOUNT))
				{
					Listview_InsertText(GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY), nVersion, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY), nVersion, nColumn, szItem);
			}
		}
	}
	while (nVersions < SendDlgItemMessage(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY, LVM_GETITEMCOUNT))
	{
		if (!Listview_DeleteText(GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY), nVersions)) break;
		continue;
	}
	Listview_SetCurText(GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY), nIndex);
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

VOID CDatabaseVersioningDialog::ShowVersionInfo()
{
	CDatabaseVersion  *pDatabaseVersion;

	if ((pDatabaseVersion = m_pDatabaseVersions[0].GetAt(Listview_GetCurText(GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY)))))
	{
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_NAME)->SetWindowText(pDatabaseVersion->GetName());
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_RELEASE)->SetWindowText(pDatabaseVersion->GetRelease());
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ISSUE)->SetWindowText(pDatabaseVersion->GetIssue());
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_COMMENT)->SetWindowText(pDatabaseVersion->GetComment());
		return;
	}
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_RELEASE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ISSUE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_COMMENT)->SetWindowText(EMPTYSTRING);
}

BOOL CDatabaseVersioningDialog::CanAddVersion() CONST
{
	CString  szVersion[4];

	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_NAME)->GetWindowText(szVersion[0]);
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_RELEASE)->GetWindowText(szVersion[1]);
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ISSUE)->GetWindowText(szVersion[2]);
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_COMMENT)->GetWindowText(szVersion[3]);
	return((GetDatabase()->CheckVersionName(szVersion[0]) && GetDatabase()->CheckVersionDomain(GetDatabase()->GetName()) && GetDatabase()->CheckVersionRelease(szVersion[1]) && GetDatabase()->CheckVersionIssue(szVersion[2]) && GetDatabase()->CheckVersionComment(szVersion[3]) && m_pDatabaseVersions[0].Find(szVersion[0], GetDatabase()->GetName(), szVersion[1], szVersion[2]) < 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_VERSION_CHANGE) : FALSE);
}

BOOL CDatabaseVersioningDialog::CanModifyVersion() CONST
{
	CString  szVersion[4];
	CDatabaseVersion  *pDatabaseVersion;

	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_NAME)->GetWindowText(szVersion[0]);
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_RELEASE)->GetWindowText(szVersion[1]);
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ISSUE)->GetWindowText(szVersion[2]);
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_COMMENT)->GetWindowText(szVersion[3]);
	return(((pDatabaseVersion = m_pDatabaseVersions[0].GetAt(m_pDatabaseVersions[0].Find(szVersion[0], GetDatabase()->GetName(), szVersion[1], szVersion[2]))) && GetDatabase()->CheckVersionName(szVersion[0]) && GetDatabase()->CheckVersionDomain(GetDatabase()->GetName()) && GetDatabase()->CheckVersionRelease(szVersion[1]) && GetDatabase()->CheckVersionIssue(szVersion[2]) && GetDatabase()->CheckVersionComment(szVersion[3]) && (szVersion[0].CompareNoCase(pDatabaseVersion->GetName()) || szVersion[1].CompareNoCase(pDatabaseVersion->GetRelease()) || szVersion[2].CompareNoCase(pDatabaseVersion->GetIssue()) || szVersion[3].CompareNoCase(pDatabaseVersion->GetComment()))) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_VERSION_CHANGE) : FALSE);
}

BOOL CDatabaseVersioningDialog::CanRemoveVersion() CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY)) >= 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_VERSION_CHANGE) : FALSE);
}

VOID CDatabaseVersioningDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_DATABASE_VERSIONING_HISTORY_NAME, (bCheck = CheckDatabasePrivilege(DATABASE_PRIVILEGE_VERSION_CHANGE)));
	AccessControl(IDC_DATABASE_VERSIONING_HISTORY_RELEASE, bCheck);
	AccessControl(IDC_DATABASE_VERSIONING_HISTORY_ISSUE, bCheck);
	AccessControl(IDC_DATABASE_VERSIONING_HISTORY_COMMENT, bCheck);
}

BOOL CDatabaseVersioningDialog::IsModified() CONST
{
	return !m_pDatabaseVersions[0].Compare(&m_pDatabaseVersions[1]);
}

BOOL CDatabaseVersioningDialog::Check(BOOL bModified) CONST
{
	return(!bModified || IsModified());
}

void CDatabaseVersioningDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseVersioningDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseVersioningDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseVersions[0].RemoveAll();
	m_pDatabaseVersions[1].RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseVersioningDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabaseVersioningDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_VERSIONING_HISTORY_ADD, OnAddVersion)
	ON_BN_CLICKED(IDC_DATABASE_VERSIONING_HISTORY_MODIFY, OnModifyVersion)
	ON_BN_CLICKED(IDC_DATABASE_VERSIONING_HISTORY_REMOVE, OnRemoveVersion)
	ON_BN_CLICKED(IDC_DATABASE_VERSIONING_HELP, OnHelp)
	ON_EN_CHANGE(IDC_DATABASE_VERSIONING_HISTORY_NAME, OnEditchangeVersion)
	ON_EN_CHANGE(IDC_DATABASE_VERSIONING_HISTORY_RELEASE, OnEditchangeRelease)
	ON_EN_CHANGE(IDC_DATABASE_VERSIONING_HISTORY_ISSUE, OnEditchangeIssue)
	ON_EN_CHANGE(IDC_DATABASE_VERSIONING_HISTORY_COMMENT, OnEditchangeComment)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseVersioningDialog message handlers

BOOL CDatabaseVersioningDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	m_szColumns.Add(STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_RELEASE));
	m_szColumns.Add(STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_ISSUE));
	m_szColumns.Add(STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_COMMENT));
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY)->GetClientRect(rColumns);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_NAME)) ? (rColumns.Width() / 3) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_RELEASE) || m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEVERSIONINGDIALOG_HISTORYTITLEITEM_ISSUE)) ? (rColumns.Width() / 7) : (rColumns.Width() / 2)));
		continue;
	}
	GetDlgItem(IDC_DATABASE_VERSIONING_SERVER)->SetWindowText(GetAccountComputerName());
	GetDlgItem(IDC_DATABASE_VERSIONING_SPACECRAFT)->SetWindowText(GetAccountSpacecraftName());
	GetDlgItem(IDC_DATABASE_VERSIONING_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_DATABASE_VERSIONING_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_SERVER_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_SERVER)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_SPACECRAFT_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_SPACECRAFT)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_DATABASE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_NAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_RELEASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_RELEASE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ISSUE_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ISSUE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_COMMENT_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_COMMENT)->EnableWindow();
	EnumVersionHistory();
	AdjustToPrivileges();
	return FALSE;
}

BOOL CDatabaseVersioningDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_DATABASE_VERSIONING_HISTORY_SUMMARY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (pNotifyListView->uNewState != 0) ShowVersionInfo();
			GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ADD)->EnableWindow(CanAddVersion());
			GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_MODIFY)->EnableWindow(CanModifyVersion());
			GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_REMOVE)->EnableWindow(CanRemoveVersion());
		}
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void CDatabaseVersioningDialog::OnAddVersion()
{
	INT  nIndex;
	CString  szVersion[4];
	CDatabaseVersion  *pDatabaseVersion;
	CHourglassCursor  cCursor;

	if ((pDatabaseVersion = new CDatabaseVersion))
	{
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_NAME)->GetWindowText(szVersion[0]);
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_RELEASE)->GetWindowText(szVersion[1]);
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ISSUE)->GetWindowText(szVersion[2]);
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_COMMENT)->GetWindowText(szVersion[3]);
		for (pDatabaseVersion->SetName(szVersion[0]), pDatabaseVersion->SetDomain(GetDatabase()->GetName()), pDatabaseVersion->SetRelease(szVersion[1]), pDatabaseVersion->SetIssue(szVersion[2]), pDatabaseVersion->SetComment(szVersion[3]); (nIndex = m_pDatabaseVersions[0].Add(pDatabaseVersion)) >= 0; )
		{
			EnumVersionHistory(nIndex);
			break;
		}
		if (nIndex < 0) delete pDatabaseVersion;
	}
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ADD)->EnableWindow(CanAddVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_MODIFY)->EnableWindow(CanModifyVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_REMOVE)->EnableWindow(CanRemoveVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseVersioningDialog::OnModifyVersion()
{
	INT  nIndex;
	CString  szVersion[4];
	CDatabaseVersion  *pDatabaseVersion;
	CHourglassCursor  cCursor;

	if ((pDatabaseVersion = m_pDatabaseVersions[0].GetAt((nIndex = Listview_GetCurText(GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY))))))
	{
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_NAME)->GetWindowText(szVersion[0]);
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_RELEASE)->GetWindowText(szVersion[1]);
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ISSUE)->GetWindowText(szVersion[2]);
		GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_COMMENT)->GetWindowText(szVersion[3]);
		pDatabaseVersion->SetName(szVersion[0]);
		pDatabaseVersion->SetRelease(szVersion[1]);
		pDatabaseVersion->SetIssue(szVersion[2]);
		pDatabaseVersion->SetComment(szVersion[3]);
		EnumVersionHistory(nIndex);
	}
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ADD)->EnableWindow(CanAddVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_MODIFY)->EnableWindow(CanModifyVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_REMOVE)->EnableWindow(CanRemoveVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseVersioningDialog::OnRemoveVersion()
{
	INT  nIndex;
	INT  nCount;
	CDatabaseVersion  *pDatabaseVersion;
	CHourglassCursor  cCursor;

	if ((pDatabaseVersion = m_pDatabaseVersions[0].GetAt((nIndex = Listview_GetCurText(GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_SUMMARY))))))
	{
		for (m_pDatabaseVersions[0].RemoveAt(nIndex); (nCount = (INT)m_pDatabaseVersions[0].GetSize()) >= 0; )
		{
			EnumVersionHistory((nCount > 0) ? 0 : -1);
			ShowVersionInfo();
			break;
		}
		delete pDatabaseVersion;
	}
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ADD)->EnableWindow(CanAddVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_MODIFY)->EnableWindow(CanModifyVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_REMOVE)->EnableWindow(CanRemoveVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseVersioningDialog::OnEditchangeVersion()
{
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ADD)->EnableWindow(CanAddVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_MODIFY)->EnableWindow(CanModifyVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_REMOVE)->EnableWindow(CanRemoveVersion());
}

void CDatabaseVersioningDialog::OnEditchangeRelease()
{
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ADD)->EnableWindow(CanAddVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_MODIFY)->EnableWindow(CanModifyVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_REMOVE)->EnableWindow(CanRemoveVersion());
}

void CDatabaseVersioningDialog::OnEditchangeIssue()
{
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ADD)->EnableWindow(CanAddVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_MODIFY)->EnableWindow(CanModifyVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_REMOVE)->EnableWindow(CanRemoveVersion());
}

void CDatabaseVersioningDialog::OnEditchangeComment()
{
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_ADD)->EnableWindow(CanAddVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_MODIFY)->EnableWindow(CanModifyVersion());
	GetDlgItem(IDC_DATABASE_VERSIONING_HISTORY_REMOVE)->EnableWindow(CanRemoveVersion());
}

void CDatabaseVersioningDialog::OnOK()
{
	INT  nDatabase;
	INT  nDatabases;
	BOOL  bSuccess;
	CString  szMessage;
	CDatabases  cDatabases;
	CDatabaseProfiles  pDatabases;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CHourglassCursor  cCursor;

	for (nDatabase = 0, nDatabases = (cDatabases.SetComputerName(GetAccountComputerName()) && cDatabases.GetDatabases(pDatabases, TRUE)) ? (INT)pDatabases.GetSize() : 0; nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseProfileInfo = pDatabases.GetAt(nDatabase)) && !pDatabaseProfileInfo->GetServer().CompareNoCase(GetAccountComputerName()) && pDatabaseProfileInfo->GetSpacecraft() == GetAccountSpacecraftName() && pDatabaseProfileInfo->GetName() == GetAccountDatabase())
		{
			if (pDatabaseProfileInfo->CDatabaseVersions::Copy(&m_pDatabaseVersions[0])) break;
			continue;
		}
	}
	for (bSuccess = cDatabases.SetDatabases(pDatabases); (bSuccess = bSuccess && GetDatabase()->Flush(&m_pDatabaseVersions[1], TRUE) && GetDatabase()->Flush(&m_pDatabaseVersions[0])); )
	{
		bSuccess &= GetDatabase()->Save(DATABASE_PROPERTY_VERSION);
		break;
	}
	szMessage.Format((bSuccess) ? STRING(IDS_DATABASE_MESSAGE_VERSIONING_SUCCESSFUL) : STRING(IDS_DATABASE_MESSAGE_VERSIONING_ERROR), (LPCTSTR)GetDatabase()->GetName());
	ShowMessage(szMessage, !bSuccess);
	EndDialog(IDOK);
}

BOOL CDatabaseVersioningDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEVERSIONINGDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseVersioningDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEVERSIONINGDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTMPacketsPage property page

IMPLEMENT_DYNCREATE(CDatabaseFindTMPacketsPage, CLocalePropertyPage)

CDatabaseFindTMPacketsPage::CDatabaseFindTMPacketsPage() : CLocalePropertyPage(CDatabaseFindTMPacketsPage::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseFindTMPacketsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CDatabaseFindTMPacketsPage::Search()
{
	INT  nID;
	INT  nIDs;
	INT  nPos;
	INT  nType;
	INT  nTypes;
	INT  nPacket;
	INT  nPackets;
	CString  szAPID;
	CString  szPane;
	CString  szFormat;
	CString  szTMType;
	CString  szPacket;
	CString  szMessage;
	CString  szParameter;
	CString  szDescription;
	CUIntArray  nAPIDs;
	CUIntArray  nTMTypes;
	CStringArray  szAPIDs;
	CStringArray  szTMTypes;
	CDatabaseTMPacket  *pDatabaseTMPacket;
	CDatabaseTMPackets  pDatabaseTMPackets;
	CRecentDocumentInfo  cDocumentInfo;

	pDatabaseTMPackets.Copy(GetDatabase()->GetTMPackets());
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_APID_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_APID)->GetWindowText(szAPID);
		for (nID = 0, nIDs = GetDatabase()->EnumTMPacketAPIDs(szAPIDs, nAPIDs); nID < nIDs; nID++)
		{
			for (nPacket = 0, nPackets = (szAPIDs.GetAt(nID) == szAPID) ? (INT)pDatabaseTMPackets.GetSize() : 0; nPacket < nPackets; nPacket++)
			{
				if ((pDatabaseTMPacket = pDatabaseTMPackets.GetAt(nPacket)) && pDatabaseTMPacket->GetAPID() != nAPIDs.GetAt(nID))
				{
					pDatabaseTMPackets.RemoveAt(nPacket);
					delete pDatabaseTMPacket;
					nPackets--;
					nPacket--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY)->GetWindowText(szTMType);
		for (nType = 0, nTypes = GetDatabase()->EnumTMPacketTMTypes(szTMTypes, nTMTypes); nType < nTypes; nType++)
		{
			for (nPacket = 0, nPackets = (szTMTypes.GetAt(nType) == szTMType) ? (INT)pDatabaseTMPackets.GetSize() : 0; nPacket < nPackets; nPacket++)
			{
				if ((pDatabaseTMPacket = pDatabaseTMPackets.GetAt(nPacket)) && pDatabaseTMPacket->GetTMType() != nTMTypes.GetAt(nType))
				{
					pDatabaseTMPackets.RemoveAt(nPacket);
					delete pDatabaseTMPacket;
					nPackets--;
					nPacket--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION)->GetWindowText(szDescription);
		for (nPacket = 0, nPackets = (INT)pDatabaseTMPackets.GetSize(); nPacket < nPackets; nPacket++)
		{
			if ((pDatabaseTMPacket = pDatabaseTMPackets.GetAt(nPacket)) && pDatabaseTMPacket->GetDescription().Find(szDescription) < 0)
			{
				pDatabaseTMPackets.RemoveAt(nPacket);
				delete pDatabaseTMPacket;
				nPackets--;
				nPacket--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nPacket = 0, nPackets = (INT)pDatabaseTMPackets.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nPacket < nPackets; nPacket++)
		{
			if ((pDatabaseTMPacket = pDatabaseTMPackets.GetAt(nPacket)) && pDatabaseTMPacket->Find(szParameter) < 0)
			{
				pDatabaseTMPackets.RemoveAt(nPacket);
				delete pDatabaseTMPacket;
				nPackets--;
				nPacket--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nPacket = 0, nPackets = (INT)pDatabaseTMPackets.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nPacket < nPackets; nPacket++)
		{
			if ((pDatabaseTMPacket = pDatabaseTMPackets.GetAt(nPacket)) && pDatabaseTMPacket->Find(szParameter) < 0)
			{
				pDatabaseTMPackets.RemoveAt(nPacket);
				delete pDatabaseTMPacket;
				nPackets--;
				nPacket--;
			}
		}
	}
	for (nPacket = 0, nPackets = (INT)pDatabaseTMPackets.GetSize(), ResetConsoleContent((szPane = (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_RESULTS_PANE1)) ? STRING(IDS_OUTPUTWINDOW_FIND1TAB) : STRING(IDS_OUTPUTWINDOW_FIND2TAB))), szMessage.Format(STRING(IDS_DATABASE_STARTSEARCHING), (LPCTSTR)GetDatabase()->GetName()), ShowConsoleText(szPane, szMessage, FALSE, FALSE); nPacket < nPackets && !HIBYTE(GetAsyncKeyState(VK_ESCAPE)); nPacket++)
	{
		if ((pDatabaseTMPacket = (CDatabaseTMPacket *)pDatabaseTMPackets.GetAt(nPacket)) != (CDatabaseTMPacket *)NULL)
		{
			szPacket.Format(STRING(IDS_DATABASEFINDDIALOG_RESULTFORMAT), (LPCTSTR)pDatabaseTMPacket->GetTag(), (LPCTSTR)pDatabaseTMPacket->GetDescription());
			cDocumentInfo.SetDocument(pDatabaseTMPacket->GetTag(), pDatabaseTMPacket->GetDescription(), DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE);
			SetConsoleContext(szPane, &cDocumentInfo);
			ShowConsoleText(szPane, szPacket, FALSE, FALSE);
		}
	}
	cDocumentInfo.Reset();
	szMessage.Format((nPacket == nPackets) ? STRING(IDS_DATABASE_STOPSEARCHING) : STRING(IDS_DATABASE_ABORTSEARCHING), nPackets);
	SetConsoleContext(szPane, &cDocumentInfo);
	ShowConsoleText(szPane, szMessage, FALSE);
}

BOOL CDatabaseFindTMPacketsPage::EnumAPIDs()
{
	INT  nID;
	INT  nIDs;
	CUIntArray  nAPIDs;
	CStringArray  szAPIDs;

	for (nID = 0, nIDs = GetDatabase()->EnumTMPacketAPIDs(szAPIDs, nAPIDs); nID < nIDs; nID++)
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_TMPACKETSPAGE_APID, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szAPIDs.GetAt(nID));
		continue;
	}
	return((nID == nIDs) ? TRUE : FALSE);
}

BOOL CDatabaseFindTMPacketsPage::EnumTMTYs()
{
	INT  nType;
	INT  nTypes;
	CUIntArray  nTMTypes;
	CStringArray  szTMTypes;

	for (nType = 0, nTypes = GetDatabase()->EnumTMPacketTMTypes(szTMTypes, nTMTypes); nType < nTypes; nType++)
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTMTypes.GetAt(nType));
		continue;
	}
	return((nType == nTypes) ? TRUE : FALSE);
}

BOOL CDatabaseFindTMPacketsPage::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;

	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		szParameter.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), (LPCTSTR)GetDatabase()->GetTMParameters()->GetAt(nParameter)->GetTag(), (LPCTSTR)GetDatabase()->GetTMParameters()->GetAt(nParameter)->GetDescription());
		SendDlgItemMessage(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
		SendDlgItemMessage(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CDatabaseFindTMPacketsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_APID_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2_STATIC)) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_APID_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_APID)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2)->GetWindowTextLength() > 0)) : CLocalePropertyPage::Check()) : TRUE);
}

void CDatabaseFindTMPacketsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseFindTMPacketsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseFindTMPacketsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CDatabaseFindTMPacketsPage)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPACKETSPAGE_APID_STATIC, OnAPID)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY_STATIC, OnTMTY)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION_STATIC, OnDescription)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1_STATIC, OnParameter1)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2_STATIC, OnParameter2)
	ON_EN_CHANGE(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION, OnEditchangeDescription)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1, OnEditchangeParameter1)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2, OnEditchangeParameter2)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TMPACKETSPAGE_APID, OnSelchangeAPID)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY, OnSelchangeTMTY)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1, OnSelchangeParameter1)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2, OnSelchangeParameter2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTMPacketsPage message handlers

BOOL CDatabaseFindTMPacketsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	if (EnumAPIDs() && EnumTMTYs() && EnumParameters())
	{
		CheckDlgButton(IDC_DATABASE_FIND_TMPACKETSPAGE_RESULTS_PANE1, TRUE);
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_APID_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_RESULTS_PANE1)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_RESULTS_PANE2)->EnableWindow();
	}
	return TRUE;
}

BOOL CDatabaseFindTMPacketsPage::OnSetActive()
{
	BOOL  bResult;

	bResult = CLocalePropertyPage::OnSetActive();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return bResult;
}

void CDatabaseFindTMPacketsPage::OnAPID()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TMPACKETSPAGE_APID, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_APID)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_APID_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_APID)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnTMTY()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_TMTY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnDescription()
{
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_DESCRIPTION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnParameter1()
{
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnParameter2()
{
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnSelchangeAPID()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnSelchangeTMTY()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnSelchangeParameter1()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER1, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnSelchangeParameter2()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_TMPACKETSPAGE_PARAMETER2, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnEditchangeParameter1()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMPacketsPage::OnEditchangeParameter2()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTCFunctionsPage property page

IMPLEMENT_DYNCREATE(CDatabaseFindTCFunctionsPage, CLocalePropertyPage)

CDatabaseFindTCFunctionsPage::CDatabaseFindTCFunctionsPage() : CLocalePropertyPage(CDatabaseFindTCFunctionsPage::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseFindTCFunctionsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CDatabaseFindTCFunctionsPage::Search()
{
	INT  nPos;
	INT  nSet;
	INT  nSets;
	INT  nType;
	INT  nTypes;
	INT  nFunction;
	INT  nFunctions;
	INT  nParameter;
	INT  nParameters;
	CString  szPane;
	CString  szFormat;
	CString  szTCType;
	CString  szPacket;
	CString  szMessage;
	CString  szFunction;
	CString  szParameter;
	CString  szDescription;
	CStringArray  szParameterSets;
	CStringArray  szTCTypes;
	CLongUIntArray  nTCTypes;
	CDatabaseTCFunction  *pDatabaseTCFunction;
	CDatabaseTCFunctions  pDatabaseTCFunctions;
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;
	CDatabaseTCFunctionElement  *pDatabaseTCFunctionElement;
	CRecentDocumentInfo  cDocumentInfo;

	pDatabaseTCFunctions.Copy(GetDatabase()->GetTCFunctions());
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE)->GetWindowText(szTCType);
		for (nType = 0, nTypes = GetDatabase()->EnumTCFunctionTypes(szTCTypes, nTCTypes); nType < nTypes; nType++)
		{
			for (nFunction = 0, nFunctions = (szTCTypes.GetAt(nType) == szTCType) ? (INT)pDatabaseTCFunctions.GetSize() : 0; nFunction < nFunctions; nFunction++)
			{
				if ((pDatabaseTCFunction = pDatabaseTCFunctions.GetAt(nFunction)) && (pDatabaseTCFunction->GetAttributes() & nTCTypes.GetAt(nType)) != nTCTypes.GetAt(nType))
				{
					pDatabaseTCFunctions.RemoveAt(nFunction);
					delete pDatabaseTCFunction;
					nFunctions--;
					nFunction--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION)->GetWindowText(szDescription);
		for (nFunction = 0, nFunctions = (INT)pDatabaseTCFunctions.GetSize(); nFunction < nFunctions; nFunction++)
		{
			if ((pDatabaseTCFunction = pDatabaseTCFunctions.GetAt(nFunction)) && pDatabaseTCFunction->GetDescription().Find(szDescription) < 0)
			{
				pDatabaseTCFunctions.RemoveAt(nFunction);
				delete pDatabaseTCFunction;
				nFunctions--;
				nFunction--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET)->GetWindowText(szPacket);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PACKETFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nFunction = 0, nFunctions = (INT)pDatabaseTCFunctions.GetSize(), nPos = szPacket.Find(szFormat), szPacket = (lstrlen(szFormat) > 0 && nPos >= 0) ? szPacket.Left(nPos) : szPacket; nFunction < nFunctions; nFunction++)
		{
			if ((pDatabaseTCFunction = pDatabaseTCFunctions.GetAt(nFunction)) && pDatabaseTCFunction->GetTCPacket().CompareNoCase(szPacket))
			{
				pDatabaseTCFunctions.RemoveAt(nFunction);
				delete pDatabaseTCFunction;
				nFunctions--;
				nFunction--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nFunction = 0, nFunctions = (INT)pDatabaseTCFunctions.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nFunction < nFunctions; nFunction++)
		{
			if ((pDatabaseTCFunction = pDatabaseTCFunctions.GetAt(nFunction)) && pDatabaseTCFunction->Find(szParameter) < 0)
			{
				for (nSet = 0, nSets = pDatabaseTCFunction->GetParameterSets(szParameterSets); nSet < nSets; nSet++)
				{
					if ((pDatabaseTCParameterSet = GetDatabase()->GetTCParameterSets()->GetAt(GetDatabase()->GetTCParameterSets()->Find(szParameterSets.GetAt(nSet)))))
					{
						for (nParameter = 0, nParameters = (INT)pDatabaseTCParameterSet->GetSize(); nParameter < nParameters; nParameter++)
						{
							if ((pDatabaseTCFunctionElement = pDatabaseTCParameterSet->GetAt(nParameter)))
							{
								if (pDatabaseTCFunctionElement->GetName() == szParameter) break;
								continue;
							}
						}
						if (nParameter < nParameters) break;
					}
				}
				if (nSet == nSets)
				{
					pDatabaseTCFunctions.RemoveAt(nFunction);
					delete pDatabaseTCFunction;
					nFunctions--;
					nFunction--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nFunction = 0, nFunctions = (INT)pDatabaseTCFunctions.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nFunction < nFunctions; nFunction++)
		{
			if ((pDatabaseTCFunction = pDatabaseTCFunctions.GetAt(nFunction)) && pDatabaseTCFunction->Find(szParameter) < 0)
			{
				for (nSet = 0, nSets = pDatabaseTCFunction->GetParameterSets(szParameterSets); nSet < nSets; nSet++)
				{
					if ((pDatabaseTCParameterSet = GetDatabase()->GetTCParameterSets()->GetAt(GetDatabase()->GetTCParameterSets()->Find(szParameterSets.GetAt(nSet)))))
					{
						for (nParameter = 0, nParameters = (INT)pDatabaseTCParameterSet->GetSize(); nParameter < nParameters; nParameter++)
						{
							if ((pDatabaseTCFunctionElement = pDatabaseTCParameterSet->GetAt(nParameter)))
							{
								if (pDatabaseTCFunctionElement->GetName() == szParameter) break;
								continue;
							}
						}
						if (nParameter < nParameters) break;
					}
				}
				if (nSet == nSets)
				{
					pDatabaseTCFunctions.RemoveAt(nFunction);
					delete pDatabaseTCFunction;
					nFunctions--;
					nFunction--;
				}
			}
		}
	}
	for (nFunction = 0, nFunctions = (INT)pDatabaseTCFunctions.GetSize(), ResetConsoleContent((szPane = (IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_RESULTS_PANE1)) ? STRING(IDS_OUTPUTWINDOW_FIND1TAB) : STRING(IDS_OUTPUTWINDOW_FIND2TAB))), szMessage.Format(STRING(IDS_DATABASE_STARTSEARCHING), (LPCTSTR)GetDatabase()->GetName()), ShowConsoleText(szPane, szMessage, FALSE, FALSE); nFunction < nFunctions && !HIBYTE(GetAsyncKeyState(VK_ESCAPE)); nFunction++)
	{
		if ((pDatabaseTCFunction = (CDatabaseTCFunction *)pDatabaseTCFunctions.GetAt(nFunction)) != (CDatabaseTCFunction *)NULL)
		{
			szFunction.Format(STRING(IDS_DATABASEFINDDIALOG_RESULTFORMAT), (LPCTSTR)pDatabaseTCFunction->GetName(), (LPCTSTR)pDatabaseTCFunction->GetDescription());
			cDocumentInfo.SetDocument(pDatabaseTCFunction->GetName(), pDatabaseTCFunction->GetDescription(), DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE);
			SetConsoleContext(szPane, &cDocumentInfo);
			ShowConsoleText(szPane, szFunction, FALSE, FALSE);
		}
	}
	cDocumentInfo.Reset();
	szMessage.Format((nFunction == nFunctions) ? STRING(IDS_DATABASE_STOPSEARCHING) : STRING(IDS_DATABASE_ABORTSEARCHING), nFunctions);
	SetConsoleContext(szPane, &cDocumentInfo);
	ShowConsoleText(szPane, szMessage, FALSE);
}

BOOL CDatabaseFindTCFunctionsPage::EnumTypes()
{
	INT  nType;
	INT  nTypes;
	CStringArray  szTCTypes;
	CLongUIntArray  nTCTypes;

	for (nType = 0, nTypes = GetDatabase()->EnumTCFunctionTypes(szTCTypes, nTCTypes); nType < nTypes; nType++)
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTCTypes.GetAt(nType));
		continue;
	}
	return((nType == nTypes) ? TRUE : FALSE);
}

BOOL CDatabaseFindTCFunctionsPage::EnumPackets()
{
	INT  nPacket;
	INT  nPackets;
	CString  szPacket;

	for (nPacket = 0, nPackets = (INT)GetDatabase()->GetTCPackets()->GetSize(); nPacket < nPackets; nPacket++)
	{
		szPacket.Format(STRING(IDS_DATABASEFINDDIALOG_PACKETFORMAT), (LPCTSTR)GetDatabase()->GetTCPackets()->GetAt(nPacket)->GetTag(), (LPCTSTR)GetDatabase()->GetTCPackets()->GetAt(nPacket)->GetDescription());
		SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szPacket);
	}
	return((nPacket == nPackets) ? TRUE : FALSE);
}

BOOL CDatabaseFindTCFunctionsPage::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;

	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTCParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		szParameter.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), (LPCTSTR)GetDatabase()->GetTCParameters()->GetAt(nParameter)->GetTag(), (LPCTSTR)GetDatabase()->GetTCParameters()->GetAt(nParameter)->GetDescription());
		SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
		SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CDatabaseFindTCFunctionsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2_STATIC)) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2)->GetWindowTextLength() > 0)) : CLocalePropertyPage::Check()) : TRUE);
}

void CDatabaseFindTCFunctionsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseFindTCFunctionsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseFindTCFunctionsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CDatabaseFindTCFunctionsPage)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE_STATIC, OnType)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION_STATIC, OnDescription)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET_STATIC, OnPacket)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1_STATIC, OnParameter1)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2_STATIC, OnParameter2)
	ON_EN_CHANGE(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION, OnEditchangeDescription)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE, OnSelchangeType)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET, OnSelchangePacket)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1, OnSelchangeParameter1)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2, OnSelchangeParameter2)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET, OnEditchangePacket)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1, OnEditchangeParameter1)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2, OnEditchangeParameter2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTCFunctionsPage message handlers

BOOL CDatabaseFindTCFunctionsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	if (EnumTypes() && EnumPackets() && EnumParameters())
	{
		CheckDlgButton(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_RESULTS_PANE1, TRUE);
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_RESULTS_PANE1)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_RESULTS_PANE2)->EnableWindow();
	}
	return TRUE;
}

BOOL CDatabaseFindTCFunctionsPage::OnSetActive()
{
	BOOL  bResult;

	bResult = CLocalePropertyPage::OnSetActive();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return bResult;
}

void CDatabaseFindTCFunctionsPage::OnType()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_TYPE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnDescription()
{
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_DESCRIPTION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnPacket()
{
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnParameter1()
{
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnParameter2()
{
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnSelchangeType()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnSelchangePacket()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PACKET, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnSelchangeParameter1()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER1, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnSelchangeParameter2()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_TCFUNCTIONSPAGE_PARAMETER2, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnEditchangePacket()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnEditchangeParameter1()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCFunctionsPage::OnEditchangeParameter2()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTMParametersPage property page

IMPLEMENT_DYNCREATE(CDatabaseFindTMParametersPage, CLocalePropertyPage)

CDatabaseFindTMParametersPage::CDatabaseFindTMParametersPage() : CLocalePropertyPage(CDatabaseFindTMParametersPage::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseFindTMParametersPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CDatabaseFindTMParametersPage::Search()
{
	INT  nPos;
	INT  nType;
	INT  nTypes;
	INT  nWidth;
	INT  nTable;
	INT  nTables;
	INT  nCoding;
	INT  nCodings;
	INT  nCategory;
	INT  nCategories;
	INT  nParameter;
	INT  nParameters;
	CString  szPane;
	CString  szType;
	CString  szTable;
	CString  szCoding;
	CString  szFormat;
	CString  szMessage;
	CString  szParameter;
	CString  szCalibration;
	CStringArray  szTypes;
	CStringArray  szCodings;
	CStringArray  szCategories;
	CStringArray  szCalTables[2];
	CStringArray  szOolTables[2];
	CLongUIntArray  nTypeIDs;
	CLongUIntArray  nCodingIDs;
	CLongUIntArray  nCategoryIDs;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMParameters  pDatabaseTMParameters;
	CRecentDocumentInfo  cDocumentInfo;

	pDatabaseTMParameters.Copy(GetDatabase()->GetTMParameters());
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE)->GetWindowText(szType);
		for (nType = 0, nTypes = GetDatabase()->EnumTMParameterTypes(szTypes, nTypeIDs); nType < nTypes; nType++)
		{
			for (nParameter = 0, nParameters = (szTypes.GetAt(nType) == szType) ? (INT)pDatabaseTMParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
			{
				if ((pDatabaseTMParameter = pDatabaseTMParameters.GetAt(nParameter)) && (pDatabaseTMParameter->GetAttributes() & nTypeIDs.GetAt(nType)) != nTypeIDs.GetAt(nType))
				{
					pDatabaseTMParameters.RemoveAt(nParameter);
					delete pDatabaseTMParameter;
					nParameters--;
					nParameter--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING)->GetWindowText(szCoding);
		for (nCoding = 0, nCodings = GetDatabase()->EnumTMParameterCodings(szCodings, nCodingIDs); nCoding < nCodings; nCoding++)
		{
			for (nParameter = 0, nParameters = (szCodings.GetAt(nCoding) == szCoding) ? (INT)pDatabaseTMParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
			{
				if ((pDatabaseTMParameter = pDatabaseTMParameters.GetAt(nParameter)) && (pDatabaseTMParameter->GetAttributes() & nCodingIDs.GetAt(nCoding)) != nCodingIDs.GetAt(nCoding))
				{
					pDatabaseTMParameters.RemoveAt(nParameter);
					delete pDatabaseTMParameter;
					nParameters--;
					nParameter--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH_STATIC))
	{
		for (nParameter = 0, nParameters = (INT)pDatabaseTMParameters.GetSize(), nWidth = (INT)Spinbox_GetPos(GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH)); nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTMParameter = pDatabaseTMParameters.GetAt(nParameter)) && pDatabaseTMParameter->GetWidth() != nWidth)
			{
				pDatabaseTMParameters.RemoveAt(nParameter);
				delete pDatabaseTMParameter;
				nParameters--;
				nParameter--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION)->GetWindowText(szCalibration);
		for (nCategory = 0, nCategories = GetDatabase()->EnumTMParameterCategories(szCategories, nCategoryIDs); nCategory < nCategories; nCategory++)
		{
			for (nParameter = 0, nParameters = (szCategories.GetAt(nCategory) == szCalibration) ? (INT)pDatabaseTMParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
			{
				if ((pDatabaseTMParameter = pDatabaseTMParameters.GetAt(nParameter)) && (pDatabaseTMParameter->GetAttributes() & nCategoryIDs.GetAt(nCategory)) != nCategoryIDs.GetAt(nCategory))
				{
					pDatabaseTMParameters.RemoveAt(nParameter);
					delete pDatabaseTMParameter;
					nParameters--;
					nParameter--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE)->GetWindowText(szTable);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_CALTABLEFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nParameter = 0, nParameters = (INT)pDatabaseTMParameters.GetSize(), nPos = szTable.Find(szFormat), szTable = (lstrlen(szFormat) > 0 && nPos >= 0) ? szTable.Left(nPos) : szTable; nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTMParameter = pDatabaseTMParameters.GetAt(nParameter)) && pDatabaseTMParameter->GetCalTables(szCalTables[0], szCalTables[1]) > 0)
			{
				for (nTable = 0, nTables = (INT)szCalTables[0].GetSize(); nTable < nTables; nTable++)
				{
					if (szCalTables[0].GetAt(nTable) == szTable) break;
					continue;
				}
				if (nTable < nTables) continue;
			}
			pDatabaseTMParameters.RemoveAt(nParameter);
			delete pDatabaseTMParameter;
			nParameters--;
			nParameter--;
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE)->GetWindowText(szTable);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_OOLTABLEFORMAT), EMPTYSTRING);
		for (nParameter = 0, nParameters = (INT)pDatabaseTMParameters.GetSize(), nPos = szTable.Find(szFormat), szTable = (lstrlen(szFormat) > 0 && nPos >= 0) ? szTable.Left(nPos) : szTable; nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTMParameter = pDatabaseTMParameters.GetAt(nParameter)) && pDatabaseTMParameter->GetOolTables(szOolTables[0], szOolTables[1]) > 0)
			{
				for (nTable = 0, nTables = (INT)szOolTables[0].GetSize(); nTable < nTables; nTable++)
				{
					if (szOolTables[0].GetAt(nTable) == szTable) break;
					continue;
				}
				if (nTable < nTables) continue;
			}
			pDatabaseTMParameters.RemoveAt(nParameter);
			delete pDatabaseTMParameter;
			nParameters--;
			nParameter--;
		}
	}
	for (nParameter = 0, nParameters = (INT)pDatabaseTMParameters.GetSize(), ResetConsoleContent((szPane = (IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_RESULTS_PANE1)) ? STRING(IDS_OUTPUTWINDOW_FIND1TAB) : STRING(IDS_OUTPUTWINDOW_FIND2TAB))), szMessage.Format(STRING(IDS_DATABASE_STARTSEARCHING), (LPCTSTR)GetDatabase()->GetName()), ShowConsoleText(szPane, szMessage, FALSE, FALSE); nParameter < nParameters && !HIBYTE(GetAsyncKeyState(VK_ESCAPE)); nParameter++)
	{
		if ((pDatabaseTMParameter = (CDatabaseTMParameter *)pDatabaseTMParameters.GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
		{
			szParameter.Format(STRING(IDS_DATABASEFINDDIALOG_RESULTFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			cDocumentInfo.SetDocument(pDatabaseTMParameter->GetTag(), pDatabaseTMParameter->GetDescription(), DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE);
			SetConsoleContext(szPane, &cDocumentInfo);
			ShowConsoleText(szPane, szParameter, FALSE, FALSE);
		}
	}
	cDocumentInfo.Reset();
	szMessage.Format((nParameter == nParameters) ? STRING(IDS_DATABASE_STOPSEARCHING) : STRING(IDS_DATABASE_ABORTSEARCHING), nParameters);
	SetConsoleContext(szPane, &cDocumentInfo);
	ShowConsoleText(szPane, szMessage, FALSE);
}

BOOL CDatabaseFindTMParametersPage::EnumTypes()
{
	INT  nType;
	INT  nTypes;
	CStringArray  szTypes;
	CLongUIntArray  nTypeIDs;

	for (nType = 0, nTypes = GetDatabase()->EnumTMParameterTypes(szTypes, nTypeIDs); nType < nTypes; nType++)
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTypes.GetAt(nType));
		continue;
	}
	return((nType == nTypes) ? TRUE : FALSE);
}

BOOL CDatabaseFindTMParametersPage::EnumCodings()
{
	INT  nCoding;
	INT  nCodings;
	CStringArray  szCodings;
	CLongUIntArray  nCodingIDs;

	for (nCoding = 0, nCodings = GetDatabase()->EnumTMParameterCodings(szCodings, nCodingIDs); nCoding < nCodings; nCoding++)
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szCodings.GetAt(nCoding));
		continue;
	}
	return((nCoding == nCodings) ? TRUE : FALSE);
}

BOOL CDatabaseFindTMParametersPage::EnumCalibrations()
{
	INT  nCategory;
	INT  nCategories;
	CStringArray  szCategories;
	CLongUIntArray  nCategoryIDs;

	for (nCategory = 0, nCategories = GetDatabase()->EnumTMParameterCategories(szCategories, nCategoryIDs); nCategory < nCategories; nCategory++)
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szCategories.GetAt(nCategory));
		continue;
	}
	return((nCategory == nCategories) ? TRUE : FALSE);
}

BOOL CDatabaseFindTMParametersPage::EnumCalTables()
{
	INT  nTable;
	INT  nTables;
	INT  nCategory;
	INT  nCategories;
	CString  szTable;
	CString  szCategory;
	CStringArray  szCategories;
	CLongUIntArray  nCategoryIDs;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE, CB_RESETCONTENT);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION)->GetWindowText(szCategory);
	for (nCategory = 0, nCategories = GetDatabase()->EnumTMParameterCategories(szCategories, nCategoryIDs); nCategory < nCategories; nCategory++)
	{
		if (szCategories.GetAt(nCategory) == szCategory  &&  nCategoryIDs.GetAt(nCategory) == TMPARAMETER_CALIBRATION_NUMERICAL)
		{
			for (nTable = 0, nTables = (INT)GetDatabase()->GetTMNumCalTables()->GetSize(); nTable < nTables; nTable = nTable + 1)
			{
				if ((pDatabaseTMNumCalTable = GetDatabase()->GetTMNumCalTables()->GetAt(nTable)) != (CDatabaseTMNumCalTable *)NULL)
				{
					szTable.Format(STRING(IDS_DATABASEFINDDIALOG_CALTABLEFORMAT), (LPCTSTR)pDatabaseTMNumCalTable->GetName(), (LPCTSTR)pDatabaseTMNumCalTable->GetDescription());
					SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
				}
			}
			GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE_STATIC)->EnableWindow();
			return TRUE;
		}
		if (szCategories.GetAt(nCategory) == szCategory  &&  nCategoryIDs.GetAt(nCategory) == TMPARAMETER_CALIBRATION_STATUS)
		{
			for (nTable = 0, nTables = (INT)GetDatabase()->GetTMTxtCalTables()->GetSize(); nTable < nTables; nTable = nTable + 1)
			{
				if ((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(nTable)) != (CDatabaseTMTxtCalTable *)NULL)
				{
					szTable.Format(STRING(IDS_DATABASEFINDDIALOG_CALTABLEFORMAT), (LPCTSTR)pDatabaseTMTxtCalTable->GetName(), (LPCTSTR)pDatabaseTMTxtCalTable->GetDescription());
					SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
				}
			}
			GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE_STATIC)->EnableWindow();
			return TRUE;
		}
	}
	CheckDlgButton(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE_STATIC, FALSE);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE)->EnableWindow(FALSE);
	return TRUE;
}

BOOL CDatabaseFindTMParametersPage::EnumOolTables()
{
	INT  nTable;
	INT  nTables;
	INT  nCategory;
	INT  nCategories;
	CString  szTable;
	CString  szCategory;
	CStringArray  szCategories;
	CLongUIntArray  nCategoryIDs;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE, CB_RESETCONTENT);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION)->GetWindowText(szCategory);
	for (nCategory = 0, nCategories = GetDatabase()->EnumTMParameterCategories(szCategories, nCategoryIDs); nCategory < nCategories; nCategory++)
	{
		if (szCategories.GetAt(nCategory) == szCategory && (nCategoryIDs.GetAt(nCategory) == TMPARAMETER_CALIBRATION_NONE || nCategoryIDs.GetAt(nCategory) == TMPARAMETER_CALIBRATION_NUMERICAL))
		{
			for (nTable = 0, nTables = (INT)GetDatabase()->GetTMNumOolTables()->GetSize(); nTable < nTables; nTable = nTable + 1)
			{
				if ((pDatabaseTMNumOolTable = GetDatabase()->GetTMNumOolTables()->GetAt(nTable)) != (CDatabaseTMNumOolTable *)NULL)
				{
					szTable.Format(STRING(IDS_DATABASEFINDDIALOG_OOLTABLEFORMAT), (LPCTSTR)pDatabaseTMNumOolTable->GetName());
					SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
				}
			}
			GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE_STATIC)->EnableWindow();
			return TRUE;
		}
		if (szCategories.GetAt(nCategory) == szCategory  &&  nCategoryIDs.GetAt(nCategory) == TMPARAMETER_CALIBRATION_STATUS)
		{
			for (nTable = 0, nTables = (INT)GetDatabase()->GetTMTxtOolTables()->GetSize(); nTable < nTables; nTable = nTable + 1)
			{
				if ((pDatabaseTMTxtOolTable = GetDatabase()->GetTMTxtOolTables()->GetAt(nTable)) != (CDatabaseTMTxtOolTable *)NULL)
				{
					szTable.Format(STRING(IDS_DATABASEFINDDIALOG_OOLTABLEFORMAT), (LPCTSTR)pDatabaseTMTxtOolTable->GetName());
					SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
				}
			}
			GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE_STATIC)->EnableWindow();
			return TRUE;
		}
	}
	CheckDlgButton(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE_STATIC, FALSE);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE)->EnableWindow(FALSE);
	return TRUE;
}

BOOL CDatabaseFindTMParametersPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE_STATIC)) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE)->GetWindowTextLength() > 0)) : CLocalePropertyPage::Check()) : TRUE);
}

void CDatabaseFindTMParametersPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseFindTMParametersPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseFindTMParametersPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CDatabaseFindTMParametersPage)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE_STATIC, OnType)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING_STATIC, OnCoding)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH_STATIC, OnWidth)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION_STATIC, OnCalibration)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE_STATIC, OnCalTable)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE_STATIC, OnOolTable)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE, OnSelchangeType)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING, OnSelchangeCoding)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION, OnSelchangeCalibration)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE, OnSelchangeCalTable)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE, OnSelchangeOolTable)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE, OnEditchangeCalTable)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE, OnEditchangeOolTable)
	ON_CONTROL(SBXN_CHANGE, IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH, OnSpinchangeWidth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTMParametersPage message handlers

BOOL CDatabaseFindTMParametersPage::OnInitDialog()
{
	INT  nRange[2];
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	for (GetDatabase()->GetTMParameterBitWidthRange(nRange[0], nRange[1]); EnumTypes() && EnumCodings() && EnumCalibrations() && EnumCalTables() && EnumOolTables(); )
	{
		Spinbox_SetRange(GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH), nRange[0], nRange[1]);
		CheckDlgButton(IDC_DATABASE_FIND_TMPARAMETERSPAGE_RESULTS_PANE1, TRUE);
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_RESULTS_PANE1)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_RESULTS_PANE2)->EnableWindow();
		break;
	}
	return TRUE;
}

BOOL CDatabaseFindTMParametersPage::OnSetActive()
{
	BOOL  bResult;

	bResult = CLocalePropertyPage::OnSetActive();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return bResult;
}

void CDatabaseFindTMParametersPage::OnType()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_TYPE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnCoding()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CODING)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnWidth()
{
	Spinbox_SetPos(GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH), 0);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_WIDTH)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnCalibration()
{
	for (SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION, CB_SETCURSEL, (WPARAM)-1); TRUE; )
	{
		EnumCalTables();
		EnumOolTables();
		break;
	}
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALIBRATION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnCalTable()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnOolTable()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnSelchangeType()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnSelchangeCoding()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnSelchangeCalibration()
{
	EnumCalTables();
	EnumOolTables();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnSelchangeCalTable()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_CALTABLE, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnSelchangeOolTable()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_TMPARAMETERSPAGE_OOLTABLE, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnSpinchangeWidth()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnEditchangeCalTable()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTMParametersPage::OnEditchangeOolTable()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTCParametersPage property page

IMPLEMENT_DYNCREATE(CDatabaseFindTCParametersPage, CLocalePropertyPage)

CDatabaseFindTCParametersPage::CDatabaseFindTCParametersPage() : CLocalePropertyPage(CDatabaseFindTCParametersPage::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseFindTCParametersPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CDatabaseFindTCParametersPage::Search()
{
	INT  nPos;
	INT  nWidth;
	INT  nCoding;
	INT  nCodings;
	INT  nCategory;
	INT  nCategories;
	INT  nParameter;
	INT  nParameters;
	CString  szPane;
	CString  szTable;
	CString  szCoding;
	CString  szFormat;
	CString  szMessage;
	CString  szParameter;
	CString  szCalibration;
	CString  szDescription;
	CStringArray  szCodings;
	CStringArray  szCategories;
	CLongUIntArray  nCodingIDs;
	CLongUIntArray  nCategoryIDs;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CDatabaseTCParameters  pDatabaseTCParameters;
	CRecentDocumentInfo  cDocumentInfo;

	pDatabaseTCParameters.Copy(GetDatabase()->GetTCParameters());
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION)->GetWindowText(szDescription);
		for (nParameter = 0, nParameters = (INT)pDatabaseTCParameters.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTCParameter = pDatabaseTCParameters.GetAt(nParameter)) && pDatabaseTCParameter->GetDescription().Find(szDescription) < 0)
			{
				pDatabaseTCParameters.RemoveAt(nParameter);
				delete pDatabaseTCParameter;
				nParameters--;
				nParameter--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING)->GetWindowText(szCoding);
		for (nCoding = 0, nCodings = GetDatabase()->EnumTCParameterCodings(szCodings, nCodingIDs); nCoding < nCodings; nCoding++)
		{
			for (nParameter = 0, nParameters = (szCodings.GetAt(nCoding) == szCoding) ? (INT)pDatabaseTCParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
			{
				if ((pDatabaseTCParameter = pDatabaseTCParameters.GetAt(nParameter)) && (pDatabaseTCParameter->GetAttributes() & nCodingIDs.GetAt(nCoding)) != nCodingIDs.GetAt(nCoding))
				{
					pDatabaseTCParameters.RemoveAt(nParameter);
					delete pDatabaseTCParameter;
					nParameters--;
					nParameter--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH_STATIC))
	{
		for (nParameter = 0, nParameters = (INT)pDatabaseTCParameters.GetSize(), nWidth = (INT)Spinbox_GetPos(GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH)); nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTCParameter = pDatabaseTCParameters.GetAt(nParameter)) && pDatabaseTCParameter->GetWidth() != nWidth)
			{
				pDatabaseTCParameters.RemoveAt(nParameter);
				delete pDatabaseTCParameter;
				nParameters--;
				nParameter--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION)->GetWindowText(szCalibration);
		for (nCategory = 0, nCategories = GetDatabase()->EnumTCParameterCategories(szCategories, nCategoryIDs); nCategory < nCategories; nCategory++)
		{
			for (nParameter = 0, nParameters = (szCategories.GetAt(nCategory) == szCalibration) ? (INT)pDatabaseTCParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
			{
				if ((pDatabaseTCParameter = pDatabaseTCParameters.GetAt(nParameter)) && (pDatabaseTCParameter->GetAttributes() & nCategoryIDs.GetAt(nCategory)) != nCategoryIDs.GetAt(nCategory))
				{
					pDatabaseTCParameters.RemoveAt(nParameter);
					delete pDatabaseTCParameter;
					nParameters--;
					nParameter--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE)->GetWindowText(szTable);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_CALTABLEFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nParameter = 0, nParameters = (INT)pDatabaseTCParameters.GetSize(), nPos = szTable.Find(szFormat), szTable = (lstrlen(szFormat) > 0 && nPos >= 0) ? szTable.Left(nPos) : szTable; nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTCParameter = pDatabaseTCParameters.GetAt(nParameter)) && pDatabaseTCParameter->GetCalTable() != szTable)
			{
				pDatabaseTCParameters.RemoveAt(nParameter);
				delete pDatabaseTCParameter;
				nParameters--;
				nParameter--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE)->GetWindowText(szTable);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_OOLTABLEFORMAT), EMPTYSTRING);
		for (nParameter = 0, nParameters = (INT)pDatabaseTCParameters.GetSize(), nPos = szTable.Find(szFormat), szTable = (lstrlen(szFormat) > 0 && nPos >= 0) ? szTable.Left(nPos) : szTable; nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTCParameter = pDatabaseTCParameters.GetAt(nParameter)) && pDatabaseTCParameter->GetOolTable() != szTable)
			{
				pDatabaseTCParameters.RemoveAt(nParameter);
				delete pDatabaseTCParameter;
				nParameters--;
				nParameter--;
			}
		}
	}
	for (nParameter = 0, nParameters = (INT)pDatabaseTCParameters.GetSize(), ResetConsoleContent((szPane = (IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_RESULTS_PANE1)) ? STRING(IDS_OUTPUTWINDOW_FIND1TAB) : STRING(IDS_OUTPUTWINDOW_FIND2TAB))), szMessage.Format(STRING(IDS_DATABASE_STARTSEARCHING), (LPCTSTR)GetDatabase()->GetName()), ShowConsoleText(szPane, szMessage, FALSE, FALSE); nParameter < nParameters && !HIBYTE(GetAsyncKeyState(VK_ESCAPE)); nParameter++)
	{
		if ((pDatabaseTCParameter = (CDatabaseTCParameter *)pDatabaseTCParameters.GetAt(nParameter)) != (CDatabaseTCParameter *)NULL)
		{
			szParameter.Format(STRING(IDS_DATABASEFINDDIALOG_RESULTFORMAT), (LPCTSTR)pDatabaseTCParameter->GetTag(), (LPCTSTR)pDatabaseTCParameter->GetDescription());
			cDocumentInfo.SetDocument(pDatabaseTCParameter->GetTag(), pDatabaseTCParameter->GetDescription(), DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE);
			SetConsoleContext(szPane, &cDocumentInfo);
			ShowConsoleText(szPane, szParameter, FALSE, FALSE);
		}
	}
	cDocumentInfo.Reset();
	szMessage.Format((nParameter == nParameters) ? STRING(IDS_DATABASE_STOPSEARCHING) : STRING(IDS_DATABASE_ABORTSEARCHING), nParameters);
	SetConsoleContext(szPane, &cDocumentInfo);
	ShowConsoleText(szPane, szMessage, FALSE);
}

BOOL CDatabaseFindTCParametersPage::EnumCodings()
{
	INT  nCoding;
	INT  nCodings;
	CStringArray  szCodings;
	CLongUIntArray  nCodingIDs;

	for (nCoding = 0, nCodings = GetDatabase()->EnumTCParameterCodings(szCodings, nCodingIDs); nCoding < nCodings; nCoding++)
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szCodings.GetAt(nCoding));
		continue;
	}
	return((nCoding == nCodings) ? TRUE : FALSE);
}

BOOL CDatabaseFindTCParametersPage::EnumCalibrations()
{
	INT  nCategory;
	INT  nCategories;
	CStringArray  szCategories;
	CLongUIntArray  nCategoryIDs;

	for (nCategory = 0, nCategories = GetDatabase()->EnumTCParameterCategories(szCategories, nCategoryIDs); nCategory < nCategories; nCategory++)
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szCategories.GetAt(nCategory));
		continue;
	}
	return((nCategory == nCategories) ? TRUE : FALSE);
}

BOOL CDatabaseFindTCParametersPage::EnumCalTables()
{
	INT  nTable;
	INT  nTables;
	INT  nCategory;
	INT  nCategories;
	CString  szTable;
	CString  szCategory;
	CStringArray  szCategories;
	CLongUIntArray  nCategoryIDs;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE, CB_RESETCONTENT);
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION)->GetWindowText(szCategory);
	for (nCategory = 0, nCategories = GetDatabase()->EnumTCParameterCategories(szCategories, nCategoryIDs); nCategory < nCategories; nCategory++)
	{
		if (szCategories.GetAt(nCategory) == szCategory  &&  nCategoryIDs.GetAt(nCategory) == TCPARAMETER_CALIBRATION_NUMERICAL)
		{
			for (nTable = 0, nTables = (INT)GetDatabase()->GetTCNumCalTables()->GetSize(); nTable < nTables; nTable = nTable + 1)
			{
				if ((pDatabaseTCNumCalTable = GetDatabase()->GetTCNumCalTables()->GetAt(nTable)) != (CDatabaseTCNumCalTable *)NULL)
				{
					szTable.Format(STRING(IDS_DATABASEFINDDIALOG_CALTABLEFORMAT), (LPCTSTR)pDatabaseTCNumCalTable->GetName(), (LPCTSTR)pDatabaseTCNumCalTable->GetDescription());
					SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
				}
			}
			GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE_STATIC)->EnableWindow();
			return TRUE;
		}
		if (szCategories.GetAt(nCategory) == szCategory  &&  nCategoryIDs.GetAt(nCategory) == TCPARAMETER_CALIBRATION_STATUS)
		{
			for (nTable = 0, nTables = (INT)GetDatabase()->GetTCTxtCalTables()->GetSize(); nTable < nTables; nTable = nTable + 1)
			{
				if ((pDatabaseTCTxtCalTable = GetDatabase()->GetTCTxtCalTables()->GetAt(nTable)) != (CDatabaseTCTxtCalTable *)NULL)
				{
					szTable.Format(STRING(IDS_DATABASEFINDDIALOG_CALTABLEFORMAT), (LPCTSTR)pDatabaseTCTxtCalTable->GetName(), (LPCTSTR)pDatabaseTCTxtCalTable->GetDescription());
					SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
				}
			}
			GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE_STATIC)->EnableWindow();
			return TRUE;
		}
	}
	CheckDlgButton(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE_STATIC, FALSE);
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE)->EnableWindow(FALSE);
	return TRUE;
}

BOOL CDatabaseFindTCParametersPage::EnumOolTables()
{
	INT  nTable;
	INT  nTables;
	INT  nCategory;
	INT  nCategories;
	CString  szTable;
	CString  szCategory;
	CStringArray  szCategories;
	CLongUIntArray  nCategoryIDs;
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;

	SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE, CB_RESETCONTENT);
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION)->GetWindowText(szCategory);
	for (nCategory = 0, nCategories = GetDatabase()->EnumTCParameterCategories(szCategories, nCategoryIDs); nCategory < nCategories; nCategory++)
	{
		if (szCategories.GetAt(nCategory) == szCategory && (nCategoryIDs.GetAt(nCategory) == TCPARAMETER_CALIBRATION_NONE || nCategoryIDs.GetAt(nCategory) == TCPARAMETER_CALIBRATION_NUMERICAL))
		{
			for (nTable = 0, nTables = (INT)GetDatabase()->GetTCNumOolTables()->GetSize(); nTable < nTables; nTable = nTable + 1)
			{
				if ((pDatabaseTCNumOolTable = GetDatabase()->GetTCNumOolTables()->GetAt(nTable)) != (CDatabaseTCNumOolTable *)NULL)
				{
					szTable.Format(STRING(IDS_DATABASEFINDDIALOG_OOLTABLEFORMAT), (LPCTSTR)pDatabaseTCNumOolTable->GetName());
					SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
				}
			}
			GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE_STATIC)->EnableWindow();
			return TRUE;
		}
		if (szCategories.GetAt(nCategory) == szCategory  &&  nCategoryIDs.GetAt(nCategory) == TCPARAMETER_CALIBRATION_STATUS)
		{
			for (nTable = 0, nTables = (INT)GetDatabase()->GetTCTxtOolTables()->GetSize(); nTable < nTables; nTable = nTable + 1)
			{
				if ((pDatabaseTCTxtOolTable = GetDatabase()->GetTCTxtOolTables()->GetAt(nTable)) != (CDatabaseTCTxtOolTable *)NULL)
				{
					szTable.Format(STRING(IDS_DATABASEFINDDIALOG_OOLTABLEFORMAT), (LPCTSTR)pDatabaseTCTxtOolTable->GetName());
					SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
				}
			}
			GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE_STATIC)->EnableWindow();
			return TRUE;
		}
	}
	CheckDlgButton(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE_STATIC, FALSE);
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE)->EnableWindow(FALSE);
	return TRUE;
}

BOOL CDatabaseFindTCParametersPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE_STATIC)) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE_STATIC) || GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE)->GetWindowTextLength() > 0)) : CLocalePropertyPage::Check()) : TRUE);
}

void CDatabaseFindTCParametersPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseFindTCParametersPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseFindTCParametersPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CDatabaseFindTCParametersPage)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION_STATIC, OnDescription)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING_STATIC, OnCoding)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH_STATIC, OnWidth)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION_STATIC, OnCalibration)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE_STATIC, OnCalTable)
	ON_BN_CLICKED(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE_STATIC, OnOolTable)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING, OnSelchangeCoding)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION, OnSelchangeCalibration)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE, OnSelchangeCalTable)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE, OnSelchangeOolTable)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE, OnEditchangeCalTable)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE, OnEditchangeOolTable)
	ON_EN_CHANGE(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION, OnEditchangeDescription)
	ON_CONTROL(SBXN_CHANGE, IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH, OnSpinchangeWidth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTCParametersPage message handlers

BOOL CDatabaseFindTCParametersPage::OnInitDialog()
{
	INT  nRange[2];
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	for (GetDatabase()->GetTCParameterBitWidthRange(nRange[0], nRange[1]); EnumCodings() && EnumCalibrations() && EnumCalTables() && EnumOolTables(); )
	{
		Spinbox_SetRange(GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH), nRange[0], nRange[1]);
		CheckDlgButton(IDC_DATABASE_FIND_TCPARAMETERSPAGE_RESULTS_PANE1, TRUE);
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_RESULTS_PANE1)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_RESULTS_PANE2)->EnableWindow();
		break;
	}
	return TRUE;
}

BOOL CDatabaseFindTCParametersPage::OnSetActive()
{
	BOOL  bResult;

	bResult = CLocalePropertyPage::OnSetActive();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return bResult;
}

void CDatabaseFindTCParametersPage::OnDescription()
{
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_DESCRIPTION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnCoding()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CODING)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnWidth()
{
	Spinbox_SetPos(GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH), 0);
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_WIDTH)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnCalibration()
{
	for (SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION, CB_SETCURSEL, (WPARAM)-1); TRUE; )
	{
		EnumCalTables();
		EnumOolTables();
		break;
	}
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALIBRATION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnCalTable()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnOolTable()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnSelchangeCoding()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnSelchangeCalibration()
{
	EnumCalTables();
	EnumOolTables();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnSelchangeCalTable()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_CALTABLE, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnSelchangeOolTable()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_TCPARAMETERSPAGE_OOLTABLE, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnSpinchangeWidth()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnEditchangeCalTable()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindTCParametersPage::OnEditchangeOolTable()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindOBProcessorsPage property page

IMPLEMENT_DYNCREATE(CDatabaseFindOBProcessorsPage, CLocalePropertyPage)

CDatabaseFindOBProcessorsPage::CDatabaseFindOBProcessorsPage() : CLocalePropertyPage(CDatabaseFindOBProcessorsPage::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseFindOBProcessorsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CDatabaseFindOBProcessorsPage::Search()
{
	INT  nPos;
	INT  nProcessor;
	INT  nProcessors;
	UINT  nRange[2][2];
	UINT  nAddress[3][2];
	CString  szPane;
	CString  szImage;
	CString  szFormat;
	CString  szPacket;
	CString  szCommand;
	CString  szMessage;
	CString  szProcessor;
	CString  szAddress[2];
	CStringTools  cStringTools;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;
	CDatabaseOBProcessors  pDatabaseOBProcessors;
	CRecentDocumentInfo  cDocumentInfo;

	pDatabaseOBProcessors.Copy(GetDatabase()->GetOBProcessors());
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND))
	{
		for (szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_COMMANDFORMAT), EMPTYSTRING, EMPTYSTRING), GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND_NAME)->GetWindowText(szCommand); (nPos = szCommand.Find(szFormat.GetAt(0))) >= 0; )
		{
			szCommand = szCommand.Left(nPos);
			break;
		}
		for (nProcessor = 0, nProcessors = (INT)pDatabaseOBProcessors.GetSize(); nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor = pDatabaseOBProcessors.GetAt(nProcessor)) && pDatabaseOBProcessor->GetPatchCommand().Compare(szCommand))
			{
				pDatabaseOBProcessors.RemoveAt(nProcessor);
				delete pDatabaseOBProcessor;
				nProcessors--;
				nProcessor--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND))
	{
		for (szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_COMMANDFORMAT), EMPTYSTRING, EMPTYSTRING), GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND_NAME)->GetWindowText(szCommand); (nPos = szCommand.Find(szFormat.GetAt(0))) >= 0; )
		{
			szCommand = szCommand.Left(nPos);
			break;
		}
		for (nProcessor = 0, nProcessors = (INT)pDatabaseOBProcessors.GetSize(); nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor = pDatabaseOBProcessors.GetAt(nProcessor)) && pDatabaseOBProcessor->GetDumpCommand().Compare(szCommand))
			{
				pDatabaseOBProcessors.RemoveAt(nProcessor);
				delete pDatabaseOBProcessor;
				nProcessors--;
				nProcessor--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET))
	{
		for (szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PACKETFORMAT), EMPTYSTRING, EMPTYSTRING), GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET_TAG)->GetWindowText(szPacket); (nPos = szPacket.Find(szFormat.GetAt(0))) >= 0; )
		{
			szPacket = szPacket.Left(nPos);
			break;
		}
		for (nProcessor = 0, nProcessors = (INT)pDatabaseOBProcessors.GetSize(); nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor = pDatabaseOBProcessors.GetAt(nProcessor)) && pDatabaseOBProcessor->GetDumpPacket().Compare(szPacket))
			{
				pDatabaseOBProcessors.RemoveAt(nProcessor);
				delete pDatabaseOBProcessor;
				nProcessors--;
				nProcessor--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE))
	{
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE_NAME)->GetWindowText(szImage);
		for (nProcessor = 0, nProcessors = (INT)pDatabaseOBProcessors.GetSize(); nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor = pDatabaseOBProcessors.GetAt(nProcessor)) && pDatabaseOBProcessor->GetMasterImage().Compare(szImage))
			{
				pDatabaseOBProcessors.RemoveAt(nProcessor);
				delete pDatabaseOBProcessor;
				nProcessors--;
				nProcessor--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS))
	{
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE)->GetWindowText(szAddress[0]);
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET)->GetWindowText(szAddress[1]);
		for (nProcessor = 0, nProcessors = (INT)pDatabaseOBProcessors.GetSize(), GetDatabase()->GetOBProcessorAddressRange(nRange[0][0], nRange[0][1], nRange[1][0], nRange[1][1]), nAddress[0][0] = (UINT)GetDatabase()->ParseValue(szAddress[0], 16), nAddress[0][1] = (!szAddress[1].IsEmpty()) ? (UINT)GetDatabase()->ParseValue(szAddress[1], 16) : nAddress[0][0]; nProcessor < nProcessors; nProcessor++)
		{
			if ((pDatabaseOBProcessor = pDatabaseOBProcessors.GetAt(nProcessor)) && pDatabaseOBProcessor->GetAddressRange(nAddress[1][0], nAddress[2][0], nAddress[1][1], nAddress[2][1]) && (((ULONGLONG)nAddress[0][0] * (ULONGLONG)(nRange[1][1] - nRange[1][0] + 1) + (ULONGLONG)nAddress[0][1] < (ULONGLONG)nAddress[1][0] * (ULONGLONG)(nRange[1][1] - nRange[1][0] + 1) + (ULONGLONG)nAddress[2][0] || (ULONGLONG)nAddress[0][0] * (ULONGLONG)(nRange[1][1] - nRange[1][0] + 1) + (ULONGLONG)nAddress[0][1] > (ULONGLONG) nAddress[1][1] * (ULONGLONG)(nRange[1][1] - nRange[1][0] + 1) + (ULONGLONG)nAddress[2][1])))
			{
				pDatabaseOBProcessors.RemoveAt(nProcessor);
				delete pDatabaseOBProcessor;
				nProcessors--;
				nProcessor--;
			}
		}
	}
	for (nProcessor = 0, nProcessors = (INT)pDatabaseOBProcessors.GetSize(), ResetConsoleContent((szPane = (IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_RESULTS_PANE1)) ? STRING(IDS_OUTPUTWINDOW_FIND1TAB) : STRING(IDS_OUTPUTWINDOW_FIND2TAB))), szMessage.Format(STRING(IDS_DATABASE_STARTSEARCHING), (LPCTSTR)GetDatabase()->GetName()), ShowConsoleText(szPane, szMessage, FALSE, FALSE); nProcessor < nProcessors && !HIBYTE(GetAsyncKeyState(VK_ESCAPE)); nProcessor++)
	{
		if ((pDatabaseOBProcessor = (CDatabaseOBProcessor *)pDatabaseOBProcessors.GetAt(nProcessor)) != (CDatabaseOBProcessor *)NULL)
		{
			szProcessor.Format(STRING(IDS_DATABASEFINDDIALOG_RESULTFORMAT), (LPCTSTR)pDatabaseOBProcessor->GetName(), (LPCTSTR)pDatabaseOBProcessor->GetDetails());
			cDocumentInfo.SetDocument(pDatabaseOBProcessor->GetName(), pDatabaseOBProcessor->GetDetails(), DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE);
			SetConsoleContext(szPane, &cDocumentInfo);
			ShowConsoleText(szPane, szProcessor, FALSE, FALSE);
		}
	}
	cDocumentInfo.Reset();
	szMessage.Format((nProcessor == nProcessors) ? STRING(IDS_DATABASE_STOPSEARCHING) : STRING(IDS_DATABASE_ABORTSEARCHING), nProcessors);
	SetConsoleContext(szPane, &cDocumentInfo);
	ShowConsoleText(szPane, szMessage, FALSE);
}

BOOL CDatabaseFindOBProcessorsPage::EnumPatchCommands()
{
	INT  nCommand;
	INT  nCommands;
	CString  szCommand;
	CDatabaseTCFunction  *pDatabaseTCFunction;

	for (nCommand = 0, nCommands = (INT)GetDatabase()->GetTCFunctions()->GetSize(); nCommand < nCommands; nCommand++)
	{
		if ((pDatabaseTCFunction = GetDatabase()->GetTCFunctions()->GetAt(nCommand)) != (CDatabaseTCFunction *)NULL)
		{
			szCommand.Format(STRING(IDS_DATABASEFINDDIALOG_COMMANDFORMAT), (LPCTSTR)pDatabaseTCFunction->GetName(), (LPCTSTR)pDatabaseTCFunction->GetDescription());
			SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szCommand);
		}
	}
	return((nCommand == nCommands) ? TRUE : FALSE);
}

BOOL CDatabaseFindOBProcessorsPage::EnumDumpCommands()
{
	INT  nCommand;
	INT  nCommands;
	CString  szCommand;
	CDatabaseTCFunction  *pDatabaseTCFunction;

	for (nCommand = 0, nCommands = (INT)GetDatabase()->GetTCFunctions()->GetSize(); nCommand < nCommands; nCommand++)
	{
		if ((pDatabaseTCFunction = GetDatabase()->GetTCFunctions()->GetAt(nCommand)) != (CDatabaseTCFunction *)NULL)
		{
			szCommand.Format(STRING(IDS_DATABASEFINDDIALOG_COMMANDFORMAT), (LPCTSTR)pDatabaseTCFunction->GetName(), (LPCTSTR)pDatabaseTCFunction->GetDescription());
			SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szCommand);
		}
	}
	return((nCommand == nCommands) ? TRUE : FALSE);
}

BOOL CDatabaseFindOBProcessorsPage::EnumDumpPackets()
{
	INT  nPacket;
	INT  nPackets;
	CString  szPacket;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	for (nPacket = 0, nPackets = (INT)GetDatabase()->GetTMPackets()->GetSize(); nPacket < nPackets; nPacket++)
	{
		if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(nPacket)) != (CDatabaseTMPacket *)NULL)
		{
			szPacket.Format(STRING(IDS_DATABASEFINDDIALOG_PACKETFORMAT), (LPCTSTR)pDatabaseTMPacket->GetTag(), (LPCTSTR)pDatabaseTMPacket->GetDescription());
			SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET_TAG, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szPacket);
		}
	}
	return((nPacket == nPackets) ? TRUE : FALSE);
}

BOOL CDatabaseFindOBProcessorsPage::EnumMasterImages()
{
	INT  nImage;
	INT  nImages;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;

	for (nImage = 0, nImages = (INT)GetDatabase()->GetOBProcessorMemoryImages()->GetSize(); nImage < nImages; nImage++)
	{
		if ((pDatabaseOBProcessorMemoryImage = GetDatabase()->GetOBProcessorMemoryImages()->GetAt(nImage)) != (CDatabaseOBProcessorMemoryImage *)NULL)
		{
			SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pDatabaseOBProcessorMemoryImage->GetName());
			continue;
		}
	}
	return((nImage == nImages) ? TRUE : FALSE);
}

BOOL CDatabaseFindOBProcessorsPage::Check(BOOL bAll) CONST
{
	CString  szAddress[2];

	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE)->GetWindowText(szAddress[0]);
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET)->GetWindowText(szAddress[1]);
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND) || IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND) || IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET) || IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE) || IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS)) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND) || GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND_NAME)->SendMessage(CB_GETCURSEL) >= 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND) || GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND_NAME)->SendMessage(CB_GETCURSEL) >= 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET) || GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET_TAG)->SendMessage(CB_GETCURSEL) >= 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE) || GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE_NAME)->SendMessage(CB_GETCURSEL) >= 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS) || (GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET)->GetWindowTextLength() > 0))) : CLocalePropertyPage::Check()) : TRUE);
}

void CDatabaseFindOBProcessorsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseFindOBProcessorsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseFindOBProcessorsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CDatabaseFindOBProcessorsPage)
	ON_BN_CLICKED(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND, OnPatchCommand)
	ON_BN_CLICKED(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND, OnDumpCommand)
	ON_BN_CLICKED(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET, OnDumpPacket)
	ON_BN_CLICKED(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE, OnMasterImage)
	ON_BN_CLICKED(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS, OnAddress)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND_NAME, OnSelchangePatchCommand)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND_NAME, OnSelchangeDumpCommand)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET_TAG, OnSelchangeDumpPacket)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE_NAME, OnSelchangeMasterImage)
	ON_EN_CHANGE(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE, OnEditchangeAddressPage)
	ON_EN_CHANGE(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET, OnEditchangeAddressOffset)
	ON_EN_UPDATE(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE, OnEditupdateAddressPage)
	ON_EN_UPDATE(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET, OnEditupdateAddressOffset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindOBProcessorsPage message handlers

BOOL CDatabaseFindOBProcessorsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	if (EnumPatchCommands() && EnumDumpCommands() && EnumDumpPackets() && EnumMasterImages())
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE, EM_LIMITTEXT, 2 * sizeof(UINT));
		SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET, EM_LIMITTEXT, 2 * sizeof(UINT));
		CheckDlgButton(IDC_DATABASE_FIND_OBPROCESSORSPAGE_RESULTS_PANE1, TRUE);
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET_TAG, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_RESULTS_PANE1)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_RESULTS_PANE2)->EnableWindow();
	}
	return TRUE;
}

BOOL CDatabaseFindOBProcessorsPage::OnSetActive()
{
	BOOL  bResult;

	bResult = CLocalePropertyPage::OnSetActive();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return bResult;
}

void CDatabaseFindOBProcessorsPage::OnPatchCommand()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND_NAME, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND_NAME)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND));
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_PATCHCOMMAND_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnDumpCommand()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND_NAME, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND_NAME)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND));
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPCOMMAND_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnDumpPacket()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET_TAG, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET_TAG)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET));
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_DUMPPACKET_TAG)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnMasterImage()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE_NAME, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE_NAME)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE));
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_MASTERIMAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnAddress()
{
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS));
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_SYMBOL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS));
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS));
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_RADIX_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS));
	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnSelchangePatchCommand()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnSelchangeDumpCommand()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnSelchangeDumpPacket()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnSelchangeMasterImage()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnEditchangeAddressPage()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnEditchangeAddressOffset()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindOBProcessorsPage::OnEditupdateAddressPage()
{
	INT  nPos;
	INT  nLength;
	CString  szAddress;

	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE)->GetWindowText(szAddress);
	for (nPos = 0, nLength = szAddress.GetLength(); nPos < nLength; nPos++)
	{
		if (!_istxdigit(szAddress.GetAt(nPos))) break;
		continue;
	}
	if (nPos < nLength)
	{
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE)->SetWindowText(szAddress.Left(nPos) + szAddress.Mid(nPos + 1));
		SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE, EM_SETSEL, 0, -1);
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_PAGE)->SetFocus();
		CAudioDevice::AlertBySound();
	}
}

void CDatabaseFindOBProcessorsPage::OnEditupdateAddressOffset()
{
	INT  nPos;
	INT  nLength;
	CString  szAddress;

	GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET)->GetWindowText(szAddress);
	for (nPos = 0, nLength = szAddress.GetLength(); nPos < nLength; nPos++)
	{
		if (!_istxdigit(szAddress.GetAt(nPos))) break;
		continue;
	}
	if (nPos < nLength)
	{
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET)->SetWindowText(szAddress.Left(nPos) + szAddress.Mid(nPos + 1));
		SendDlgItemMessage(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET, EM_SETSEL, 0, -1);
		GetDlgItem(IDC_DATABASE_FIND_OBPROCESSORSPAGE_ADDRESS_OFFSET)->SetFocus();
		CAudioDevice::AlertBySound();
	}
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindANDsPage property page

IMPLEMENT_DYNCREATE(CDatabaseFindANDsPage, CLocalePropertyPage)

CDatabaseFindANDsPage::CDatabaseFindANDsPage() : CLocalePropertyPage(CDatabaseFindANDsPage::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseFindANDsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CDatabaseFindANDsPage::Search()
{
	INT  nPos;
	INT  nLayout;
	INT  nLayouts;
	CString  szPane;
	CString  szFormat;
	CString  szLayout;
	CString  szMessage;
	CString  szParameter;
	CString  szDescription;
	CANDLayout  *pLayout;
	CANDLayouts  pLayouts;
	CRecentDocumentInfo  cDocumentInfo;

	pLayouts.Copy(GetDatabase()->GetANDs());
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION)->GetWindowText(szDescription);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(); nLayout < nLayouts; nLayout++)
		{
			if ((pLayout = pLayouts.GetAt(nLayout)) && pLayout->GetTitle().Find(szDescription) < 0)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout = pLayouts.GetAt(nLayout)) && pLayout->Find(szParameter) < 0)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout = pLayouts.GetAt(nLayout)) && pLayout->Find(szParameter) < 0)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout = pLayouts.GetAt(nLayout)) && pLayout->Find(szParameter) < 0)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout = pLayouts.GetAt(nLayout)) && pLayout->Find(szParameter) < 0)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), ResetConsoleContent((szPane = (IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_RESULTS_PANE1)) ? STRING(IDS_OUTPUTWINDOW_FIND1TAB) : STRING(IDS_OUTPUTWINDOW_FIND2TAB))), szMessage.Format(STRING(IDS_DATABASE_STARTSEARCHING), (LPCTSTR)GetDatabase()->GetName()), ShowConsoleText(szPane, szMessage, FALSE, FALSE); nLayout < nLayouts && !HIBYTE(GetAsyncKeyState(VK_ESCAPE)); nLayout++)
	{
		if ((pLayout = (CANDLayout *)pLayouts.GetAt(nLayout)) != (CANDLayout *)NULL)
		{
			szLayout.Format(STRING(IDS_DATABASEFINDDIALOG_RESULTFORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
			cDocumentInfo.SetDocument(pLayout->GetName(), pLayout->GetTitle(), DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE);
			SetConsoleContext(szPane, &cDocumentInfo);
			ShowConsoleText(szPane, szLayout, FALSE, FALSE);
		}
	}
	cDocumentInfo.Reset();
	szMessage.Format((nLayout == nLayouts) ? STRING(IDS_DATABASE_STOPSEARCHING) : STRING(IDS_DATABASE_ABORTSEARCHING), nLayouts);
	SetConsoleContext(szPane, &cDocumentInfo);
	ShowConsoleText(szPane, szMessage, FALSE);
}

BOOL CDatabaseFindANDsPage::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
		{
			szParameter.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
			SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
			SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
			SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CDatabaseFindANDsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4_STATIC)) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION_STATIC) || GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1_STATIC) || GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2_STATIC) || GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3_STATIC) || GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4_STATIC) || GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4)->GetWindowTextLength() > 0)) : CLocalePropertyPage::Check()) : TRUE);
}

void CDatabaseFindANDsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseFindANDsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseFindANDsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CDatabaseFindANDsPage)
	ON_BN_CLICKED(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION_STATIC, OnDescription)
	ON_BN_CLICKED(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1_STATIC, OnParameter1)
	ON_BN_CLICKED(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2_STATIC, OnParameter2)
	ON_BN_CLICKED(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3_STATIC, OnParameter3)
	ON_BN_CLICKED(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4_STATIC, OnParameter4)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1, OnEditchangeParameter1)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2, OnEditchangeParameter2)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3, OnEditchangeParameter3)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4, OnEditchangeParameter4)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1, OnSelchangeParameter1)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2, OnSelchangeParameter2)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3, OnSelchangeParameter3)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4, OnSelchangeParameter4)
	ON_EN_CHANGE(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindANDsPage message handlers

BOOL CDatabaseFindANDsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(); EnumParameters(); )
	{
		CheckDlgButton(IDC_DATABASE_FIND_ANDSPAGE_RESULTS_PANE1, TRUE);
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_RESULTS_PANE1)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_RESULTS_PANE2)->EnableWindow();
		break;
	}
	return TRUE;
}

BOOL CDatabaseFindANDsPage::OnSetActive()
{
	BOOL  bResult;

	bResult = CLocalePropertyPage::OnSetActive();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return bResult;
}

void CDatabaseFindANDsPage::OnDescription()
{
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_DESCRIPTION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnParameter1()
{
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnParameter2()
{
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnParameter3()
{
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnParameter4()
{
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnSelchangeParameter1()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER1, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnSelchangeParameter2()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER2, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnSelchangeParameter3()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER3, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnSelchangeParameter4()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_ANDSPAGE_PARAMETER4, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnEditchangeParameter1()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnEditchangeParameter2()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnEditchangeParameter3()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindANDsPage::OnEditchangeParameter4()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindGRDsPage property page

IMPLEMENT_DYNCREATE(CDatabaseFindGRDsPage, CLocalePropertyPage)

CDatabaseFindGRDsPage::CDatabaseFindGRDsPage() : CLocalePropertyPage(CDatabaseFindGRDsPage::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseFindGRDsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CDatabaseFindGRDsPage::Search()
{
	INT  nPos;
	INT  nType;
	INT  nTypes;
	INT  nMode;
	INT  nModes;
	INT  nLayout;
	INT  nLayouts;
	CString  szPane;
	CString  szType;
	CString  szMode;
	CString  szFormat;
	CString  szLayout;
	CString  szMessage;
	CString  szParameter;
	CString  szDescription;
	CUIntArray  nTypeIDs;
	CUIntArray  nModeIDs;
	CStringArray  szTypes;
	CStringArray  szModes;
	CGRDLayout  *pLayout;
	CGRDLayouts  pLayouts;
	CRecentDocumentInfo  cDocumentInfo;

	pLayouts.Copy(GetDatabase()->GetGRDs());
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_TYPE_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_TYPE)->GetWindowText(szType);
		for (nType = 0, nTypes = GetDatabase()->EnumGRDTypes(szTypes, nTypeIDs); nType < nTypes; nType++)
		{
			for (nLayout = 0, nLayouts = (szTypes.GetAt(nType) == szType) ? (INT)pLayouts.GetSize() : 0; nLayout < nLayouts; nLayout++)
			{
				if ((pLayout = pLayouts.GetAt(nLayout)) && pLayout->GetType() != nTypeIDs.GetAt(nType))
				{
					pLayouts.RemoveAt(nLayout);
					delete pLayout;
					nLayouts--;
					nLayout--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE)->GetWindowText(szMode);
		for (nMode = 0, nModes = GetDatabase()->EnumGRDPlotModes(szModes, nModeIDs); nMode < nModes; nMode++)
		{
			for (nLayout = 0, nLayouts = (szModes.GetAt(nMode) == szMode) ? (INT)pLayouts.GetSize() : 0; nLayout < nLayouts; nLayout++)
			{
				if ((pLayout = pLayouts.GetAt(nLayout)) && (pLayout->GetMode() & nModeIDs.GetAt(nMode)) != nModeIDs.GetAt(nMode))
				{
					pLayouts.RemoveAt(nLayout);
					delete pLayout;
					nLayouts--;
					nLayout--;
				}
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION)->GetWindowText(szDescription);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(); nLayout < nLayouts; nLayout++)
		{
			if ((pLayout = pLayouts.GetAt(nLayout)) && pLayout->GetTitle().Find(szDescription) < 0)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout = pLayouts.GetAt(nLayout)) && pLayout->Find(szParameter) < 0)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout = pLayouts.GetAt(nLayout)) && pLayout->Find(szParameter) < 0)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), ResetConsoleContent((szPane = (IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_RESULTS_PANE1)) ? STRING(IDS_OUTPUTWINDOW_FIND1TAB) : STRING(IDS_OUTPUTWINDOW_FIND2TAB))), szMessage.Format(STRING(IDS_DATABASE_STARTSEARCHING), (LPCTSTR)GetDatabase()->GetName()), ShowConsoleText(szPane, szMessage, FALSE, FALSE); nLayout < nLayouts && !HIBYTE(GetAsyncKeyState(VK_ESCAPE)); nLayout++)
	{
		if ((pLayout = (CGRDLayout *)pLayouts.GetAt(nLayout)) != (CGRDLayout *)NULL)
		{
			szLayout.Format(STRING(IDS_DATABASEFINDDIALOG_RESULTFORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
			cDocumentInfo.SetDocument(pLayout->GetName(), pLayout->GetTitle(), DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE);
			SetConsoleContext(szPane, &cDocumentInfo);
			ShowConsoleText(szPane, szLayout, FALSE, FALSE);
		}
	}
	cDocumentInfo.Reset();
	szMessage.Format((nLayout == nLayouts) ? STRING(IDS_DATABASE_STOPSEARCHING) : STRING(IDS_DATABASE_ABORTSEARCHING), nLayouts);
	SetConsoleContext(szPane, &cDocumentInfo);
	ShowConsoleText(szPane, szMessage, FALSE);
}

BOOL CDatabaseFindGRDsPage::EnumTypes()
{
	INT  nType;
	INT  nTypes;
	CUIntArray  nTypeIDs;
	CStringArray  szTypes;

	for (nType = 0, nTypes = GetDatabase()->EnumGRDTypes(szTypes, nTypeIDs); nType < nTypes; nType++)
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_GRDSPAGE_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTypes.GetAt(nType));
		continue;
	}
	return((nType == nTypes) ? TRUE : FALSE);
}

BOOL CDatabaseFindGRDsPage::EnumPlottingModes()
{
	INT  nMode;
	INT  nModes;
	CUIntArray  nModeIDs;
	CStringArray  szModes;

	for (nMode = 0, nModes = GetDatabase()->EnumGRDPlotModes(szModes, nModeIDs); nMode < nModes; nMode++)
	{
		SendDlgItemMessage(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szModes.GetAt(nMode));
		continue;
	}
	return((nMode == nModes) ? TRUE : FALSE);
}

BOOL CDatabaseFindGRDsPage::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
		{
			szParameter.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
			SendDlgItemMessage(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CDatabaseFindGRDsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_TYPE_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2_STATIC)) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_TYPE_STATIC) || GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_TYPE)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE_STATIC) || GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION_STATIC) || GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1_STATIC) || GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2_STATIC) || GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2)->GetWindowTextLength() > 0)) : CLocalePropertyPage::Check()) : TRUE);
}

void CDatabaseFindGRDsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseFindGRDsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseFindGRDsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CDatabaseFindGRDsPage)
	ON_BN_CLICKED(IDC_DATABASE_FIND_GRDSPAGE_TYPE_STATIC, OnType)
	ON_BN_CLICKED(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE_STATIC, OnPlottingMode)
	ON_BN_CLICKED(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION_STATIC, OnDescription)
	ON_BN_CLICKED(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1_STATIC, OnParameter1)
	ON_BN_CLICKED(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2_STATIC, OnParameter2)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1, OnEditchangeParameter1)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2, OnEditchangeParameter2)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_GRDSPAGE_TYPE, OnSelchangeType)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE, OnSelchangePlottingMode)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1, OnSelchangeParameter1)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2, OnSelchangeParameter2)
	ON_EN_CHANGE(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindGRDsPage message handlers

BOOL CDatabaseFindGRDsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	if (EnumTypes() && EnumPlottingModes() && EnumParameters())
	{
		CheckDlgButton(IDC_DATABASE_FIND_GRDSPAGE_RESULTS_PANE1, TRUE);
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_RESULTS_PANE1)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_RESULTS_PANE2)->EnableWindow();
	}
	return TRUE;
}

BOOL CDatabaseFindGRDsPage::OnSetActive()
{
	BOOL  bResult;

	bResult = CLocalePropertyPage::OnSetActive();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return bResult;
}

void CDatabaseFindGRDsPage::OnType()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_GRDSPAGE_TYPE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_TYPE)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_TYPE_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_TYPE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnPlottingMode()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PLOTTINGMODE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnDescription()
{
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_DESCRIPTION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnParameter1()
{
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnParameter2()
{
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnSelchangeType()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnSelchangePlottingMode()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnSelchangeParameter1()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER1, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnSelchangeParameter2()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_GRDSPAGE_PARAMETER2, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnEditchangeParameter1()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindGRDsPage::OnEditchangeParameter2()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindPODsPage property page

IMPLEMENT_DYNCREATE(CDatabaseFindPODsPage, CLocalePropertyPage)

CDatabaseFindPODsPage::CDatabaseFindPODsPage() : CLocalePropertyPage(CDatabaseFindPODsPage::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseFindPODsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CDatabaseFindPODsPage::Search()
{
	INT  nPos;
	INT  nLayout;
	INT  nLayouts;
	INT  nElement;
	INT  nElements;
	INT  nParameter;
	INT  nParameters;
	CString  szPane;
	CString  szFormat;
	CString  szLayout;
	CString  szMessage;
	CString  szParameter;
	CString  szDescription;
	CPODLayout  *pLayout;
	CPODLayouts  pLayouts;
	CStringArray  szParameters;
	CPODLayoutExpression  *pElement;
	CRecentDocumentInfo  cDocumentInfo;

	pLayouts.Copy(GetDatabase()->GetPODs());
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION)->GetWindowText(szDescription);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(); nLayout < nLayouts; nLayout++)
		{
			if ((pLayout = pLayouts.GetAt(nLayout)) && pLayout->GetTitle().Find(szDescription) < 0)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nLayout < nLayouts; nLayout++)
		{
			for (nElement = 0, nElements = ((pLayout = pLayouts.GetAt(nLayout))) ? (INT)pLayout->GetSize() : 0; nElement < nElements; nElement++)
			{
				if ((pElement = pLayout->GetAt(nElement)) && pElement->IsParameter() && pElement->GetParameter() == szParameter) break;
				continue;
			}
			if (nElement == nElements)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nLayout < nLayouts; nLayout++)
		{
			for (nElement = 0, nElements = ((pLayout = pLayouts.GetAt(nLayout))) ? (INT)pLayout->GetSize() : 0; nElement < nElements; nElement++)
			{
				if ((pElement = pLayout->GetAt(nElement)) && pElement->IsParameter() && pElement->GetParameter() == szParameter) break;
				continue;
			}
			if (nElement == nElements)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	if (IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER_STATIC))
	{
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER)->GetWindowText(szParameter);
		szFormat.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), EMPTYSTRING, EMPTYSTRING);
		for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), nPos = szParameter.Find(szFormat), szParameter = (lstrlen(szFormat) > 0 && nPos >= 0) ? szParameter.Left(nPos) : szParameter; nLayout < nLayouts; nLayout++)
		{
			for (nParameter = 0, nParameters = ((pLayout = pLayouts.GetAt(nLayout))) ? pLayout->GetParameters(szParameters) : 0; nParameter < nParameters; nParameter++)
			{
				if (szParameters.GetAt(nParameter) == szParameter) break;
				continue;
			}
			if (nParameter == nParameters)
			{
				pLayouts.RemoveAt(nLayout);
				delete pLayout;
				nLayouts--;
				nLayout--;
			}
		}
	}
	for (nLayout = 0, nLayouts = (INT)pLayouts.GetSize(), ResetConsoleContent((szPane = (IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_RESULTS_PANE1)) ? STRING(IDS_OUTPUTWINDOW_FIND1TAB) : STRING(IDS_OUTPUTWINDOW_FIND2TAB))), szMessage.Format(STRING(IDS_DATABASE_STARTSEARCHING), (LPCTSTR)GetDatabase()->GetName()), ShowConsoleText(szPane, szMessage, FALSE, FALSE); nLayout < nLayouts && !HIBYTE(GetAsyncKeyState(VK_ESCAPE)); nLayout++)
	{
		if ((pLayout = (CPODLayout *)pLayouts.GetAt(nLayout)) != (CPODLayout *)NULL)
		{
			szLayout.Format(STRING(IDS_DATABASEFINDDIALOG_RESULTFORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
			cDocumentInfo.SetDocument(pLayout->GetName(), pLayout->GetTitle(), DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE);
			SetConsoleContext(szPane, &cDocumentInfo);
			ShowConsoleText(szPane, szLayout, FALSE, FALSE);
		}
	}
	cDocumentInfo.Reset();
	szMessage.Format((nLayout == nLayouts) ? STRING(IDS_DATABASE_STOPSEARCHING) : STRING(IDS_DATABASE_ABORTSEARCHING), nLayouts);
	SetConsoleContext(szPane, &cDocumentInfo);
	ShowConsoleText(szPane, szMessage, FALSE);
}

BOOL CDatabaseFindPODsPage::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
		{
			szParameter.Format(STRING(IDS_DATABASEFINDDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
			SendDlgItemMessage(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
			SendDlgItemMessage(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CDatabaseFindPODsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2_STATIC) || IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER_STATIC)) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION_STATIC) || GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1_STATIC) || GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2_STATIC) || GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2)->GetWindowTextLength() > 0) && (!IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER_STATIC) || GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER)->GetWindowTextLength() > 0)) : CLocalePropertyPage::Check()) : TRUE);
}

void CDatabaseFindPODsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseFindPODsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseFindPODsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CDatabaseFindPODsPage)
	ON_BN_CLICKED(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION_STATIC, OnDescription)
	ON_BN_CLICKED(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1_STATIC, OnStackParameter1)
	ON_BN_CLICKED(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2_STATIC, OnStackParameter2)
	ON_BN_CLICKED(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER_STATIC, OnAssociatedParameter)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1, OnSelchangeStackParameter1)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2, OnSelchangeStackParameter2)
	ON_CBN_SELCHANGE(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER, OnSelchangeAssociatedParameter)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1, OnEditchangeStackParameter1)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2, OnEditchangeStackParameter2)
	ON_CBN_EDITCHANGE(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER, OnEditchangeAssociatedParameter)
	ON_EN_CHANGE(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindPODsPage message handlers

BOOL CDatabaseFindPODsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(); EnumParameters(); )
	{
		CheckDlgButton(IDC_DATABASE_FIND_PODSPAGE_RESULTS_PANE1, TRUE);
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACK_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATED_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_RESULTS_PANE1)->EnableWindow();
		GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_RESULTS_PANE2)->EnableWindow();
		break;
	}
	return TRUE;
}

BOOL CDatabaseFindPODsPage::OnSetActive()
{
	BOOL  bResult;

	bResult = CLocalePropertyPage::OnSetActive();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return bResult;
}

void CDatabaseFindPODsPage::OnDescription()
{
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_DESCRIPTION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindPODsPage::OnStackParameter1()
{
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindPODsPage::OnStackParameter2()
{
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindPODsPage::OnAssociatedParameter()
{
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER)->EnableWindow(IsDlgButtonChecked(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER_STATIC));
	GetDlgItem(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindPODsPage::OnSelchangeStackParameter1()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER1, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindPODsPage::OnSelchangeStackParameter2()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_PODSPAGE_STACKPARAMETER2, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindPODsPage::OnSelchangeAssociatedParameter()
{
	SendDlgItemMessage(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_FIND_PODSPAGE_ASSOCIATEDPARAMETER, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindPODsPage::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindPODsPage::OnEditchangeStackParameter1()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindPODsPage::OnEditchangeStackParameter2()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseFindPODsPage::OnEditchangeAssociatedParameter()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindDBMSPage property page

IMPLEMENT_DYNCREATE(CDatabaseFindDBMSPage, CLocalePropertyPage)

CDatabaseFindDBMSPage::CDatabaseFindDBMSPage() : CLocalePropertyPage(CDatabaseFindDBMSPage::IDD)
{
	//{{AFX_DATA_INIT(CDatabaseFindDBMSPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CDatabaseFindDBMSPage::Search()
{
	INT  nCount;
	INT  nField;
	INT  nFields;
	INT  nPos[2];
	INT  nLength;
	INT  nResult;
	INT  nResults;
	CString  szPane;
	CString  szQuery;
	CString  szField;
	CString  szFields;
	CString  szResult;
	CString  szMessage;
	CStringArray  szResults;
	CODBCFieldInfo  cFieldInfo;
	CRecentDocumentInfo  cDocumentInfo;

	for (GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_QUERY)->GetWindowText(szQuery); GetDatabase()->OpenDBMS(CDatabase::noOdbcDialog); )
	{
		ResetConsoleContent((szPane = (IsDlgButtonChecked(IDC_DATABASE_FIND_DBMSPAGE_RESULTS_PANE1)) ? STRING(IDS_OUTPUTWINDOW_FIND1TAB) : STRING(IDS_OUTPUTWINDOW_FIND2TAB)));
		szMessage.Format(STRING(IDS_DATABASE_STARTSEARCHING), (LPCTSTR)GetDatabase()->GetName());
		ShowConsoleText(szPane, szMessage, FALSE, FALSE);
		try
		{
			CRecordset  cRecordset(GetDatabase()->GetDBMS());
			if (cRecordset.Open(CRecordset::forwardOnly, szQuery))
			{
				for (nField = 0, nFields = cRecordset.GetODBCFieldCount(), szFields.Empty(); nField < nFields; nField++)
				{
					cRecordset.GetODBCFieldInfo(nField, cFieldInfo);
					szFields += (nField > 0) ? CString(TAB) : EMPTYSTRING;
					szFields += (LPCTSTR)cFieldInfo.m_strName;
				}
				for (nCount = 0; !cRecordset.IsEOF() && !HIBYTE(GetAsyncKeyState(VK_ESCAPE)); nCount++)
				{
					for (nField = 0, szResult.Empty(); nField < nFields; nField++)
					{
						cRecordset.GetFieldValue(nField, szField);
						szResult += (nField > 0) ? CString(TAB) : EMPTYSTRING;
						szResult += (LPCTSTR)szField;
					}
					szResults.Add(szResult);
					cRecordset.MoveNext();
				}
				for (nField = 0, nPos[0] = 0, szResults.InsertAt(0, szFields); nField < nFields; nField++)
				{
					for (nResult = 0, nResults = (INT)szResults.GetSize(), nLength = 0; nResult < nResults; nResult++)
					{
						if ((nPos[1] = szResults.GetAt(nResult).Mid(nPos[0]).Find(TAB)) >= 0)
						{
							nLength = max(nPos[1], nLength);
							continue;
						}
						nLength = max(szResults.GetAt(nResult).Mid(nPos[0]).GetLength(), nLength);
					}
					for (nResult = 0; nResult < nResults; nResult++)
					{
						if ((nPos[1] = szResults.GetAt(nResult).Mid(nPos[0]).Find(TAB)) >= 0)
						{
							szResults.SetAt(nResult, szResults.GetAt(nResult).Left(nPos[0] + nPos[1]) + CString(SPACE[0], nLength - nPos[1] + 1) + szResults.GetAt(nResult).Mid(nPos[0] + nPos[1] + 1));
							continue;
						}
						szResults.SetAt(nResult, szResults.GetAt(nResult) + CString(SPACE[0], nLength - szResults.GetAt(nResult).Mid(nPos[0]).GetLength() + 1));
					}
					nPos[0] += nLength;
				}
				if (!szFields.IsEmpty())
				{
					ShowConsoleText(szPane, SPACE, FALSE, FALSE);
					szResults.InsertAt(1, CString(STRING(IDS_DATABASEFINDDIALOG_UNDERLINEFORMAT)[0], nPos[0]));
				}
				for (nResult = 0, nResults = (INT)szResults.GetSize(); nResult < nResults && !HIBYTE(GetAsyncKeyState(VK_ESCAPE)); nResult++)
				{
					ShowConsoleText(szPane, szResults.GetAt(nResult), FALSE, FALSE);
					continue;
				}
				for (cDocumentInfo.SetDocument(STRING(IDS_OUTPUTWINDOW_QUERY1TAB), szQuery, (ULONGLONG)-1); IsDlgButtonChecked(IDC_DATABASE_FIND_DBMSPAGE_QUERYTEXT_PANE1); )
				{
					SetConsoleContext(STRING(IDS_OUTPUTWINDOW_QUERY1TAB), &cDocumentInfo);
					ShowConsoleText(STRING(IDS_OUTPUTWINDOW_QUERY1TAB), szQuery, FALSE, FALSE);
					break;
				}
				for (cDocumentInfo.SetDocument(STRING(IDS_OUTPUTWINDOW_QUERY2TAB), szQuery, (ULONGLONG)-1); IsDlgButtonChecked(IDC_DATABASE_FIND_DBMSPAGE_QUERYTEXT_PANE2); )
				{
					SetConsoleContext(STRING(IDS_OUTPUTWINDOW_QUERY2TAB), &cDocumentInfo);
					ShowConsoleText(STRING(IDS_OUTPUTWINDOW_QUERY2TAB), szQuery, FALSE, FALSE);
					break;
				}
				szMessage.Format((nResult == nResults  &&  cRecordset.IsEOF()) ? STRING(IDS_DATABASE_STOPSEARCHING) : STRING(IDS_DATABASE_ABORTSEARCHING), nCount);
				ShowConsoleText(szPane, szMessage, FALSE);
				cRecordset.Close();
			}
		}
		catch (CDBException *e)
		{
			ShowConsoleText(szPane, e->m_strError, FALSE, FALSE);
			ShowConsoleText(szPane, STRING(IDS_DATABASE_ABORTSEARCHING), FALSE);
			GetDatabase()->CloseDBMS();
			e->Delete();
			return;
		}
		catch (CMemoryException *e)
		{
			ShowConsoleText(szPane, STRING(IDS_DATABASE_ABORTSEARCHING), FALSE);
			GetDatabase()->CloseDBMS();
			e->Delete();
			return;
		}
		GetDatabase()->CloseDBMS();
		return;
	}
	szMessage.Format(STRING(IDS_DATABASE_OPEN_FAILURE), (LPCTSTR)GetDatabase()->GetName());
	ShowMessage(szMessage);
}

VOID CDatabaseFindDBMSPage::SetQuery(LPCTSTR pszQuery)
{
	m_szQuery = pszQuery;
}

CString CDatabaseFindDBMSPage::GetQuery() CONST
{
	return m_szQuery;
}

BOOL CDatabaseFindDBMSPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_QUERY)->GetWindowTextLength() > 0) : CLocalePropertyPage::Check()) : TRUE);
}

void CDatabaseFindDBMSPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseFindDBMSPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseFindDBMSPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CDatabaseFindDBMSPage)
	ON_EN_CHANGE(IDC_DATABASE_FIND_DBMSPAGE_QUERY, OnEditchangeQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindDBMSPage message handlers

BOOL CDatabaseFindDBMSPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	CheckDlgButton(IDC_DATABASE_FIND_DBMSPAGE_RESULTS_PANE1, TRUE);
	CheckDlgButton(IDC_DATABASE_FIND_DBMSPAGE_QUERYTEXT_PANE1, TRUE);
	GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_QUERY)->SetWindowText(m_szQuery);
	GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_QUERY_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_QUERY)->EnableWindow();
	GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_RESULTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_RESULTS_PANE1)->EnableWindow();
	GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_RESULTS_PANE2)->EnableWindow();
	GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_QUERYTEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_QUERYTEXT_PANE1)->EnableWindow();
	GetDlgItem(IDC_DATABASE_FIND_DBMSPAGE_QUERYTEXT_PANE2)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return TRUE;
}

BOOL CDatabaseFindDBMSPage::OnSetActive()
{
	BOOL  bResult;

	bResult = CLocalePropertyPage::OnSetActive();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return bResult;
}

void CDatabaseFindDBMSPage::OnEditchangeQuery()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTabCtrl

IMPLEMENT_DYNCREATE(CDatabaseFindTabCtrl, CTabCtrl)

CDatabaseFindDialog *CDatabaseFindTabCtrl::GetParent() CONST
{
	return((CDatabaseFindDialog *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CDatabaseFindTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CDatabaseFindTabCtrl)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindTabCtrl message handlers

void CDatabaseFindTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nTab;

	if ((nChar == VK_LEFT  &&  GetCurSel() > 0) || (nChar == VK_RIGHT  &&  GetCurSel() < GetItemCount() - 1))
	{
		if ((nTab = (nChar == VK_LEFT) ? (GetCurSel() - 1) : (GetCurSel() + 1)) >= 0)
		{
			GetParent()->SetActivePage(nTab);
			return;
		}
	}
	CTabCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDatabaseFindTabCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	CTabCtrl::OnLButtonDown(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindDialog

IMPLEMENT_DYNCREATE(CDatabaseFindDialog, CLocalePropertySheetDialog)

CDatabaseFindDialog::CDatabaseFindDialog(CWnd *pParentWnd) : CLocalePropertySheetDialog(STRING(IDS_DATABASEFINDDIALOG_TITLE), pParentWnd)
{
	AddPage(&m_pageTMPackets);
	AddPage(&m_pageTCFunctions);
	AddPage(&m_pageTMParameters);
	AddPage(&m_pageTCParameters);
	AddPage(&m_pageOBProcessors);
	AddPage(&m_pageANDs);
	AddPage(&m_pageGRDs);
	AddPage(&m_pagePODs);
	AddPage(&m_pageDBMS);
}

INT_PTR CDatabaseFindDialog::DoModal()
{
	return CLocalePropertySheetDialog::DoModal();
}
INT_PTR CDatabaseFindDialog::DoModal(LPCTSTR pszQuery)
{
	m_pageDBMS.SetQuery(pszQuery);
	return DoModal();
}

BOOL CDatabaseFindDialog::Check(BOOL bModified) CONST
{
	CWnd  *pWnd;
	CLocalePropertyPage  *pPage;

	for (pWnd = GetWindow(GW_CHILD); IsWindow(pWnd->GetSafeHwnd()); pWnd = pWnd->GetNextWindow())
	{
		if ((pPage = (pWnd->IsKindOf(RUNTIME_CLASS(CLocalePropertyPage))) ? (CLocalePropertyPage *)pWnd : (CLocalePropertyPage *)NULL))
		{
			if (pPage == (CPropertyPage *)GetActivePage() && pPage->Check(FALSE)) return TRUE;
			continue;
		}
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CDatabaseFindDialog, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CDatabaseFindDialog)
	ON_WM_CREATE()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseFindDialog message handlers

int CDatabaseFindDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	EnableStackedTabs(FALSE);
	return CLocalePropertySheetDialog::OnCreate(lpCreateStruct);
}

BOOL CDatabaseFindDialog::OnInitDialog()
{
	CTabCtrl  *pTabCtrl;
	CHourglassCursor  cCursor;

	CLocalePropertySheetDialog::OnInitDialog();
	if ((pTabCtrl = GetTabControl()) && IsWindow(pTabCtrl->GetSafeHwnd()))
	{
		for (; m_pageDBMS.GetQuery().GetLength() > 0; )
		{
			SetActivePage(&m_pageDBMS);
			break;
		}
		m_wndTabCtrl.SubclassWindow(pTabCtrl->GetSafeHwnd());
		m_wndTabCtrl.SetFocus();
		return FALSE;
	}
	return TRUE;
}

void CDatabaseFindDialog::OnOK()
{
	CHourglassCursor  cCursor;

	for (; TRUE; )
	{
		if (GetActivePage()->GetSafeHwnd() == m_pageTMPackets.GetSafeHwnd())
		{
			m_pageTMPackets.Search();
			break;
		}
		if (GetActivePage()->GetSafeHwnd() == m_pageTCFunctions.GetSafeHwnd())
		{
			m_pageTCFunctions.Search();
			break;
		}
		if (GetActivePage()->GetSafeHwnd() == m_pageTMParameters.GetSafeHwnd())
		{
			m_pageTMParameters.Search();
			break;
		}
		if (GetActivePage()->GetSafeHwnd() == m_pageTCParameters.GetSafeHwnd())
		{
			m_pageTCParameters.Search();
			break;
		}
		if (GetActivePage()->GetSafeHwnd() == m_pageOBProcessors.GetSafeHwnd())
		{
			m_pageOBProcessors.Search();
			break;
		}
		if (GetActivePage()->GetSafeHwnd() == m_pageANDs.GetSafeHwnd())
		{
			m_pageANDs.Search();
			break;
		}
		if (GetActivePage()->GetSafeHwnd() == m_pageGRDs.GetSafeHwnd())
		{
			m_pageGRDs.Search();
			break;
		}
		if (GetActivePage()->GetSafeHwnd() == m_pagePODs.GetSafeHwnd())
		{
			m_pagePODs.Search();
			break;
		}
		if (GetActivePage()->GetSafeHwnd() == m_pageDBMS.GetSafeHwnd())
		{
			m_pageDBMS.Search();
			break;
		}
		break;
	}
	CLocalePropertySheetDialog::OnOK();
}

BOOL CDatabaseFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASEFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CCompileBatchInfo

CCompileBatchInfo::CCompileBatchInfo() : CObject()
{
	m_nAction = 0;
	m_nComponents = 0;
	m_nScheduleOptions = 0;
	m_tExecutionTime[0] = 0;
	m_tExecutionTime[1] = 0;
	m_tDailyTime = 0;
	m_bModified = FALSE;
}

VOID CCompileBatchInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CCompileBatchInfo::GetName() CONST
{
	return m_szName;
}

VOID CCompileBatchInfo::SetAction(UINT nAction)
{
	m_nAction = nAction;
}

UINT CCompileBatchInfo::GetAction() CONST
{
	return m_nAction;
}

VOID CCompileBatchInfo::SetComponents(ULONGLONG nComponents)
{
	m_nComponents = nComponents;
}

ULONGLONG CCompileBatchInfo::GetComponents() CONST
{
	return m_nComponents;
}

VOID CCompileBatchInfo::SetScheduleOptions(UINT nOptions)
{
	m_nScheduleOptions = nOptions;
}

UINT CCompileBatchInfo::GetScheduleOptions() CONST
{
	return m_nScheduleOptions;
}

VOID CCompileBatchInfo::SetExecutionTime(CONST CTimeKey &tTime)
{
	m_tExecutionTime[0] = tTime;
}

CTimeKey CCompileBatchInfo::GetExecutionTime() CONST
{
	return m_tExecutionTime[0];
}

VOID CCompileBatchInfo::SetDailyExecutionTime(CONST CTimeSpan &tTime)
{
	m_tDailyTime = tTime;
}

CTimeSpan CCompileBatchInfo::GetDailyExecutionTime() CONST
{
	return m_tDailyTime;
}

VOID CCompileBatchInfo::SetLastExecutionTime(CONST CTimeKey &tTime)
{
	m_tExecutionTime[1] = tTime;
}

CTimeKey CCompileBatchInfo::GetLastExecutionTime() CONST
{
	return m_tExecutionTime[1];
}

VOID CCompileBatchInfo::SetModified(BOOL bModified)
{
	m_bModified = bModified;
}

BOOL CCompileBatchInfo::IsModified() CONST
{
	return m_bModified;
}

VOID CCompileBatchInfo::Copy(CONST CCompileBatchInfo *pBatchInfo)
{
	m_szName = pBatchInfo->m_szName;
	m_nAction = pBatchInfo->m_nAction;
	m_nComponents = pBatchInfo->m_nComponents;
	m_nScheduleOptions = pBatchInfo->m_nScheduleOptions;
	m_tExecutionTime[0] = pBatchInfo->m_tExecutionTime[0];
	m_tExecutionTime[1] = pBatchInfo->m_tExecutionTime[1];
	m_tDailyTime = pBatchInfo->m_tDailyTime;
	m_bModified = pBatchInfo->m_bModified;
}

BOOL CCompileBatchInfo::Compare(CONST CCompileBatchInfo *pBatchInfo) CONST
{
	return((pBatchInfo->m_szName == m_szName  &&  pBatchInfo->m_nAction == m_nAction  &&  pBatchInfo->m_nComponents == m_nComponents  &&  pBatchInfo->m_nScheduleOptions == m_nScheduleOptions  &&  pBatchInfo->m_tExecutionTime[0] == m_tExecutionTime[0] && pBatchInfo->m_tExecutionTime[1] == m_tExecutionTime[1] && pBatchInfo->m_tDailyTime == m_tDailyTime  &&  pBatchInfo->m_bModified == m_bModified) ? TRUE : FALSE);
}

BOOL CCompileBatchInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName)), sData.nComponents = m_nComponents, sData.nAction = m_nAction, sData.nScheduleOptions = m_nScheduleOptions, sData.tExecutionTime = m_tExecutionTime[0].GetTime(), sData.tDailyTime = m_tDailyTime.GetTotalSeconds(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + sizeof(DATA), (LPCTSTR)m_szName, sData.cbName);
		return TRUE;
	}
	return FALSE;
}

BOOL CCompileBatchInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName && sData.cbName > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + sizeof(DATA), STRINGBYTES(sData.cbName));
		m_nComponents = sData.nComponents;
		m_nAction = sData.nAction;
		m_nScheduleOptions = sData.nScheduleOptions;
		m_tExecutionTime[0] = sData.tExecutionTime;
		m_tDailyTime = sData.tDailyTime;
		m_szName.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CCompileBatches

CCompileBatches::CCompileBatches() : CPtrArray()
{
	return;
}

CCompileBatches::~CCompileBatches()
{
	RemoveAll();
}

INT CCompileBatches::Add(CCompileBatchInfo *pBatchInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pBatchInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pBatchInfo, 1);
	return nIndex;
}

INT CCompileBatches::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

INT CCompileBatches::Enum(CStringArray &szNames) CONST
{
	INT  nBatch;
	INT  nBatches;
	CCompileBatchInfo  *pBatchInfo;

	for (nBatch = 0, nBatches = (INT)GetSize(), szNames.RemoveAll(); nBatch < nBatches; nBatch++)
	{
		if ((pBatchInfo = GetAt(nBatch)) != (CCompileBatchInfo *)NULL)
		{
			szNames.Add(pBatchInfo->GetName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CCompileBatchInfo *CCompileBatches::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CCompileBatchInfo *)CPtrArray::GetAt(nIndex) : (CCompileBatchInfo *)NULL);
}

CCompileBatchInfo *CCompileBatches::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CCompileBatchInfo *)CPtrArray::GetAt(nIndex) : (CCompileBatchInfo *)NULL);
}

VOID CCompileBatches::RemoveAll()
{
	INT  nBatch;
	INT  nBatches;

	for (nBatch = 0, nBatches = (INT)GetSize(); nBatch < nBatches; nBatch++)
	{
		delete GetAt(nBatch);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CCompileBatches::Copy(CONST CCompileBatches *pBatches)
{
	INT  nBatch;
	INT  nBatches;
	CCompileBatchInfo  *pBatchInfo;

	for (nBatch = 0, nBatches = (INT)pBatches->GetSize(), RemoveAll(); nBatch < nBatches; nBatch++)
	{
		if ((pBatchInfo = new CCompileBatchInfo) != (CCompileBatchInfo *)NULL)
		{
			pBatchInfo->Copy(pBatches->GetAt(nBatch));
			InsertAt(nBatch, pBatchInfo, 1);
			continue;
		}
		break;
	}
	return((nBatch == nBatches) ? TRUE : FALSE);
}

BOOL CCompileBatches::Compare(CONST CCompileBatches *pBatches) CONST
{
	INT  nBatch;
	INT  nBatches;

	for (nBatch = 0, nBatches = (pBatches->GetSize() == GetSize()) ? (INT)GetSize() : -1; nBatch < nBatches; nBatch++)
	{
		if (!pBatches->GetAt(nBatch)->Compare(GetAt(nBatch))) break;
		continue;
	}
	return((nBatch == nBatches) ? TRUE : FALSE);
}

BOOL CCompileBatches::Map(CByteArray &nInfo) CONST
{
	INT  nBatch;
	INT  nBatches;
	CByteArray  nBatchData;
	CCompileBatchInfo  *pBatchInfo;

	for (nBatch = 0, nBatches = (INT)GetSize(), nInfo.RemoveAll(); nBatch < nBatches; nBatch++)
	{
		if ((pBatchInfo = GetAt(nBatch)) && pBatchInfo->Map(nBatchData) && nInfo.Append(nBatchData) >= 0) continue;
		break;
	}
	return((nBatch == nBatches) ? TRUE : FALSE);
}

BOOL CCompileBatches::Unmap(CONST CByteArray &nInfo)
{
	INT  cbBatch;
	INT  cbBatches;
	CTimeKey  tBatchTime;
	CByteArray  nBatchData;
	CCompileBatchInfo  *pBatchInfo;

	for (cbBatches = 0, RemoveAll(); cbBatches < nInfo.GetSize(); cbBatches += cbBatch)
	{
		for (CopyMemory(&cbBatch, nInfo.GetData() + cbBatches, sizeof(cbBatch)), nBatchData.SetSize(max(min(cbBatch, nInfo.GetSize() - cbBatches), 0)); nBatchData.GetSize() >= 0; )
		{
			CopyMemory(nBatchData.GetData(), nInfo.GetData() + cbBatches, nBatchData.GetSize());
			break;
		}
		if ((pBatchInfo = new CCompileBatchInfo))
		{
			if (pBatchInfo->Unmap(nBatchData))
			{
				for (; pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_IMMEDIATELY || (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_ATTIME && pBatchInfo->GetExecutionTime() <= tBatchTime) || pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_DAILY; )
				{
					pBatchInfo->SetLastExecutionTime(tBatchTime);
					break;
				}
				if (Add(pBatchInfo) >= 0) continue;
			}
			delete pBatchInfo;
		}
		break;
	}
	if ((pBatchInfo = (!nInfo.GetSize()) ? new CCompileBatchInfo : (CCompileBatchInfo *)NULL))
	{
		for (pBatchInfo->SetName(STRING(IDS_COMPILEBATCHES_PROFILE_DEFAULT)), pBatchInfo->SetComponents(COMPILEBATCH_COMPONENT_TMPACKETS | COMPILEBATCH_COMPONENT_TCFUNCTIONS | COMPILEBATCH_COMPONENT_TMPARAMETERS | COMPILEBATCH_COMPONENT_TCPARAMETERS | COMPILEBATCH_COMPONENT_OBPROCESSORS | COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS | COMPILEBATCH_COMPONENT_ANDS | COMPILEBATCH_COMPONENT_GRDS | COMPILEBATCH_COMPONENT_PODS), pBatchInfo->SetAction(COMPILEBATCH_ACTION_COMPILATION), pBatchInfo->SetScheduleOptions(COMPILEBATCH_SCHEDULE_IMMEDIATELY), pBatchInfo->SetLastExecutionTime(tBatchTime); Add(pBatchInfo) >= 0; ) return TRUE;
		delete pBatchInfo;
		return FALSE;
	}
	return((cbBatches == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CCompileBatches::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CCompileBatchInfo  *pBatchInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pBatchInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pBatchInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pBatchInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pBatchInfo->GetName() == pszName) || (bInsert && (((pBatchInfo = GetAt(max(nIndex[0] - 1, 0))) && pBatchInfo->GetName() != pszName && (pBatchInfo = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pBatchInfo->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CCompileBatchesDialog dialog

IMPLEMENT_DYNCREATE(CCompileBatchesDialog, CLocaleDialog)

CCompileBatchesDialog::CCompileBatchesDialog(CWnd *pParentWnd) : CLocaleDialog(CCompileBatchesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CCompileBatchesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CCompileBatchesDialog::Initialize()
{
	INT  nBatch;
	INT  nBatches;
	CTimeKey  tExecutionTime;
	CCompileBatchInfo  *pBatchInfo;

	for (nBatch = 0, nBatches = (GetCompileBatchProfiles(m_pBatches[0])) ? (INT)m_pBatches[0].GetSize() : -1; nBatch < nBatches; nBatch++)
	{
		if ((pBatchInfo = m_pBatches[0].GetAt(nBatch)) != (CCompileBatchInfo *)NULL)
		{
			if (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_IMMEDIATELY)
			{
				pBatchInfo->SetScheduleOptions(0);
				pBatchInfo->SetLastExecutionTime(0);
				pBatchInfo->SetModified(FALSE);
				continue;
			}
			if (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_ATTIME  &&  pBatchInfo->GetExecutionTime() < tExecutionTime)
			{
				pBatchInfo->SetScheduleOptions(0);
				pBatchInfo->SetLastExecutionTime(0);
				pBatchInfo->SetModified(FALSE);
				continue;
			}
			pBatchInfo->SetModified(FALSE);
		}
	}
	return m_pBatches[1].Copy(&m_pBatches[0]);
}

VOID CCompileBatchesDialog::EnumBatches()
{
	INT  nBatch;
	INT  nBatches;
	CCompileBatchInfo  *pBatchInfo;

	for (nBatch = 0, nBatches = (INT)m_pBatches[0].GetSize(); nBatch < nBatches; nBatch++)
	{
		if ((pBatchInfo = (CCompileBatchInfo *)m_pBatches[0].GetAt(nBatch)) != (CCompileBatchInfo *)NULL)
		{
			SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pBatchInfo->GetName());
			continue;
		}
	}
	SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_COMPILEBATCHES_PROFILE_DEFAULT)));
	GetDlgItem(IDC_COMPILE_BATCHES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_STATIC)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_GETCOUNT) > 1) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_ACTION)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_STATIC)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_STATIC)->EnableWindow();
	ShowBatchProperties();
}

VOID CCompileBatchesDialog::ShowBatchProperties()
{
	CString  szBatch;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_TMPACKETS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_TCFUNCTIONS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPROCEDURES, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_TCPROCEDURES) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_TMPARAMETERS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_TCPARAMETERS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_OBPROCESSORS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_OBPROCESSORS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_ANDS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_ANDS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_GRDS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_GRDS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_MMDS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_MMDS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_PODS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_PODS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_SCRIPTS, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_SCRIPTS) && (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) != COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, ((pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENTS_ALL) == COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_COMPILATION, (pBatchInfo->GetAction() == COMPILEBATCH_ACTION_COMPILATION) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_SYNTAXCHECK, (pBatchInfo->GetAction() == COMPILEBATCH_ACTION_SYNTAXCHECK) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY, (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_IMMEDIATELY) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME, (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_ATTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY, (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_DAILY) ? TRUE : FALSE);
		Timespinbox_SetTime(GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER), (pBatchInfo->GetExecutionTime() > 0) ? pBatchInfo->GetExecutionTime() : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER), CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + pBatchInfo->GetDailyExecutionTime().GetTotalSeconds()));
		GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVE)->EnableWindow((pBatchInfo->GetName().Compare(STRING(IDS_COMPILEBATCHES_PROFILE_DEFAULT))) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
		GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_GETCOUNT) > 1) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
		GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow(FALSE);
	}
	else
	{
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS, (COMPILEBATCH_COMPONENT_TMPACKETS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS, (COMPILEBATCH_COMPONENT_TCFUNCTIONS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPROCEDURES, (COMPILEBATCH_COMPONENT_TCPROCEDURES & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS, (COMPILEBATCH_COMPONENT_TMPARAMETERS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS, (COMPILEBATCH_COMPONENT_TCPARAMETERS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_OBPROCESSORS, (COMPILEBATCH_COMPONENT_OBPROCESSORS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS, (COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_ANDS, (COMPILEBATCH_COMPONENT_ANDS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_GRDS, (COMPILEBATCH_COMPONENT_GRDS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_MMDS, (COMPILEBATCH_COMPONENT_MMDS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_PODS, (COMPILEBATCH_COMPONENT_PODS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_SCRIPTS, (COMPILEBATCH_COMPONENT_SCRIPTS & COMPILEBATCH_COMPONENTS_DEFAULT) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, ((COMPILEBATCH_COMPONENTS_ALL & COMPILEBATCH_COMPONENTS_DEFAULT) == COMPILEBATCH_COMPONENTS_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_COMPILATION, TRUE);
		CheckDlgButton(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_SYNTAXCHECK, FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY, FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME, FALSE);
		CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY, FALSE);
		GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatch);
		GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow(Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE));
		GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_GETCOUNT) > 1) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
		GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVE)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPROCEDURES)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_OBPROCESSORS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_ANDS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_GRDS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_MMDS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_PODS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_SCRIPTS)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_COMPILATION)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_SYNTAXCHECK)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME));
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY)->EnableWindow();
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY));
}

CCompileBatchInfo *CCompileBatchesDialog::FindBatch() CONST
{
	CString  szBatch;

	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatch);
	return m_pBatches[0].GetAt(m_pBatches[0].Find(szBatch));
}

VOID CCompileBatchesDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_COMPILE_BATCHES_PROFILE, (bCheck = CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)));
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPROCEDURES, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_OBPROCESSORS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_ANDS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_GRDS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_MMDS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_PODS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_SCRIPTS, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_COMPILATION, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_SYNTAXCHECK, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY, bCheck);
	AccessControl(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER, bCheck);
}

BOOL CCompileBatchesDialog::IsModified() CONST
{
	return !m_pBatches[0].Compare(&m_pBatches[1]);
}

BOOL CCompileBatchesDialog::Check(BOOL bModified) CONST
{
	INT  nIndex;
	CString  szBatch;

	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatch);
	return(((((nIndex = (INT)GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->SendMessage(CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatch)) >= 0 && bModified) || !bModified) && (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPROCEDURES) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_OBPROCESSORS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_ANDS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_GRDS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_MMDS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_PODS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_SCRIPTS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE))) ? (!bModified || IsModified()) : FALSE);
}

void CCompileBatchesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompileBatchesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCompileBatchesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CCompileBatchesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROFILE_ADD, OnAddBatch)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROFILE_REMOVE, OnRemoveBatch)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROFILE_REMOVEALL, OnRemoveAllBatches)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS, OnComponentTMPackets)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS, OnComponentTCFunctions)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPROCEDURES, OnComponentTCProcedures)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS, OnComponentTMParameters)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS, OnComponentTCParameters)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_OBPROCESSORS, OnComponentOBProcessors)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS, OnComponentDerivedParameters)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_ANDS, OnComponentANDs)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_GRDS, OnComponentGRDs)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_MMDS, OnComponentMMDs)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_PODS, OnComponentPODs)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_SCRIPTS, OnComponentScripts)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, OnComponentAll)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_COMPILATION, OnActionCompilation)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_SYNTAXCHECK, OnActionSyntaxCheck)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY, OnScheduleImmediately)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME, OnScheduleAtTime)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY, OnScheduleDaily)
	ON_BN_CLICKED(IDC_COMPILE_BATCHES_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_COMPILE_BATCHES_PROFILE, OnSelchangeBatch)
	ON_CBN_EDITCHANGE(IDC_COMPILE_BATCHES_PROFILE, OnEditchangeBatch)
	ON_CONTROL(TSBXN_CHANGE, IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER, OnSpinchangeExecutionTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER, OnSpinchangeDailyTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompileBatchesDialog message handlers

BOOL CCompileBatchesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	EnumBatches();
	AdjustToPrivileges();
	return TRUE;
}

void CCompileBatchesDialog::OnAddBatch()
{
	UINT  nAction;
	UINT  nOptions;
	CString  szBatchName;
	CTimeKey  tDailyTime;
	CTimeKey  tExecutionTime;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;
	CHourglassCursor  cCursor;

	if ((pBatchInfo = new CCompileBatchInfo))
	{
		GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
		SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szBatchName);
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS)) ? COMPILEBATCH_COMPONENT_TMPACKETS : 0;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS)) ? COMPILEBATCH_COMPONENT_TCFUNCTIONS : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPROCEDURES)) ? COMPILEBATCH_COMPONENT_TCPROCEDURES : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS)) ? COMPILEBATCH_COMPONENT_TMPARAMETERS : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS)) ? COMPILEBATCH_COMPONENT_TCPARAMETERS : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_OBPROCESSORS)) ? COMPILEBATCH_COMPONENT_OBPROCESSORS : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS)) ? COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_ANDS)) ? COMPILEBATCH_COMPONENT_ANDS : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_GRDS)) ? COMPILEBATCH_COMPONENT_GRDS : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_MMDS)) ? COMPILEBATCH_COMPONENT_MMDS : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_PODS)) ? COMPILEBATCH_COMPONENT_PODS : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_SCRIPTS)) ? COMPILEBATCH_COMPONENT_SCRIPTS : nComponents;
		nComponents |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE)) ? COMPILEBATCH_COMPONENTS_ALL : nComponents;
		nAction = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_COMPILATION)) ? COMPILEBATCH_ACTION_COMPILATION : 0;
		nAction = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_ACTION_DIRECTIVE_SYNTAXCHECK)) ? COMPILEBATCH_ACTION_SYNTAXCHECK : nAction;
		nOptions = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY)) ? COMPILEBATCH_SCHEDULE_IMMEDIATELY : 0;
		nOptions |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME)) ? COMPILEBATCH_SCHEDULE_ATTIME : nOptions;
		nOptions |= (IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY)) ? COMPILEBATCH_SCHEDULE_DAILY : nOptions;
		tExecutionTime = Timespinbox_GetTime(GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER));
		tDailyTime = Timespinbox_GetTime(GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER));
		for (pBatchInfo->SetName(szBatchName), pBatchInfo->SetAction(nAction), pBatchInfo->SetComponents(nComponents), pBatchInfo->SetScheduleOptions(nOptions); nOptions & COMPILEBATCH_SCHEDULE_ATTIME; )
		{
			pBatchInfo->SetExecutionTime(tExecutionTime);
			break;
		}
		for (; nOptions & COMPILEBATCH_SCHEDULE_DAILY; )
		{
			pBatchInfo->SetDailyExecutionTime(tDailyTime.GetTime() % SECONDSPERDAY);
			break;
		}
		for (; m_pBatches[0].Add(pBatchInfo) < 0; )
		{
			delete pBatchInfo;
			break;
		}
	}
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) >= 0 && szBatchName.Compare(STRING(IDS_COMPILEBATCHES_PROFILE_DEFAULT))) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_GETCOUNT) > 1) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnRemoveBatch()
{
	INT  nIndex;
	CString  szBatchName;
	CCompileBatchInfo  *pBatchInfo;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName), SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName)); (nIndex = m_pBatches[0].Find(szBatchName)) >= 0; )
	{
		if ((pBatchInfo = m_pBatches[0].GetAt(nIndex)))
		{
			m_pBatches[0].RemoveAt(nIndex);
			delete pBatchInfo;
		}
		break;
	}
	for (; SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_COMPILEBATCHES_PROFILE_DEFAULT))) >= 0; )
	{
		ShowBatchProperties();
		break;
	}
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) >= 0 && szBatchName.Compare(STRING(IDS_COMPILEBATCHES_PROFILE_DEFAULT))) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_GETCOUNT) > 1) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnRemoveAllBatches()
{
	INT  nBatch;
	INT  nBatches;
	CString  szBatchName;
	CCompileBatchInfo  *pBatchInfo;
	CHourglassCursor  cCursor;

	for (nBatch = 0, nBatches = (INT)m_pBatches[0].GetSize(); nBatch < nBatches; nBatch++)
	{
		if ((pBatchInfo = m_pBatches[0].GetAt(nBatch)) && pBatchInfo->GetName() != STRING(IDS_COMPILEBATCHES_PROFILE_DEFAULT))
		{
			SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pBatchInfo->GetName()));
			m_pBatches[0].RemoveAt(nBatch);
			delete pBatchInfo;
			nBatches--;
			nBatch--;
		}
	}
	for (; SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_COMPILEBATCHES_PROFILE_DEFAULT))) >= 0; )
	{
		ShowBatchProperties();
		break;
	}
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) >= 0 && szBatchName.Compare(STRING(IDS_COMPILEBATCHES_PROFILE_DEFAULT))) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_GETCOUNT) > 1) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentTMPackets()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_TMPACKETS | COMPILEBATCH_COMPONENT_TMPARAMETERS | COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS) : (pBatchInfo->GetComponents() & ~COMPILEBATCH_COMPONENT_TMPACKETS);
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS, IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS));
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS, IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS));
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentTCFunctions()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_TCFUNCTIONS | COMPILEBATCH_COMPONENT_TCPARAMETERS) : (pBatchInfo->GetComponents() & ~COMPILEBATCH_COMPONENT_TCFUNCTIONS);
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS, IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS));
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentTCProcedures()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPROCEDURES)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_TCPROCEDURES) : (pBatchInfo->GetComponents() & ~COMPILEBATCH_COMPONENT_TCPROCEDURES);
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentTMParameters()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_TMPARAMETERS | COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS) : (pBatchInfo->GetComponents() & ~(COMPILEBATCH_COMPONENT_TMPARAMETERS | COMPILEBATCH_COMPONENT_TMPACKETS));
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS, IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS) && IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS));
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS, IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS) || IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS));
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentTCParameters()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_TCPARAMETERS) : (pBatchInfo->GetComponents() & ~(COMPILEBATCH_COMPONENT_TCPARAMETERS | COMPILEBATCH_COMPONENT_TCFUNCTIONS));
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS, IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS) && IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS));
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentOBProcessors()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_OBPROCESSORS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_OBPROCESSORS) : (pBatchInfo->GetComponents() & ~COMPILEBATCH_COMPONENT_OBPROCESSORS);
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentDerivedParameters()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS) : (pBatchInfo->GetComponents() & ~(COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS | COMPILEBATCH_COMPONENT_TMPACKETS | COMPILEBATCH_COMPONENT_TMPARAMETERS));
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS, IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS) && IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS) && IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS));
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS, IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS) && IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS));
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentANDs()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_ANDS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_ANDS) : (pBatchInfo->GetComponents() & ~COMPILEBATCH_COMPONENT_ANDS);
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentGRDs()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_GRDS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_GRDS) : (pBatchInfo->GetComponents() & ~COMPILEBATCH_COMPONENT_GRDS);
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentMMDs()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_MMDS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_MMDS) : (pBatchInfo->GetComponents() & ~COMPILEBATCH_COMPONENT_MMDS);
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentPODs()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_PODS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_PODS) : (pBatchInfo->GetComponents() & ~COMPILEBATCH_COMPONENT_PODS);
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentScripts()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_SCRIPTS)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENT_SCRIPTS) : (pBatchInfo->GetComponents() & ~COMPILEBATCH_COMPONENT_SCRIPTS);
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnComponentAll()
{
	CString  szBatchName;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nComponents = (IsDlgButtonChecked(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_COMPLETEDATABASE)) ? (pBatchInfo->GetComponents() | COMPILEBATCH_COMPONENTS_ALL) : (pBatchInfo->GetComponents() & ~COMPILEBATCH_COMPONENTS_ALL);
		pBatchInfo->SetComponents(nComponents);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPACKETS, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCFUNCTIONS, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPROCEDURES, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TMPARAMETERS, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_TCPARAMETERS, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_OBPROCESSORS, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_DERIVEDPARAMETERS, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_ANDS, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_GRDS, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_MMDS, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_PODS, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_PROPERTIES_COMPONENTS_SCRIPTS, FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatchName);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatchName) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnActionCompilation()
{
	UINT  nAction;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nAction = COMPILEBATCH_ACTION_COMPILATION;
		pBatchInfo->SetAction(nAction);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnActionSyntaxCheck()
{
	UINT  nAction;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		nAction = COMPILEBATCH_ACTION_SYNTAXCHECK;
		pBatchInfo->SetAction(nAction);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnScheduleImmediately()
{
	CTimeKey  tExecutionTime;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		pBatchInfo->SetScheduleOptions((!IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY)) ? COMPILEBATCH_SCHEDULE_IMMEDIATELY : 0);
		pBatchInfo->SetLastExecutionTime(min(pBatchInfo->GetLastExecutionTime(), tExecutionTime));
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY, !IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY));
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnScheduleAtTime()
{
	CTimeKey  tExecutionTime;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		pBatchInfo->SetScheduleOptions((!IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME)) ? COMPILEBATCH_SCHEDULE_ATTIME : 0);
		pBatchInfo->SetLastExecutionTime(min(pBatchInfo->GetLastExecutionTime(), tExecutionTime));
		pBatchInfo->SetExecutionTime(tExecutionTime.GetTime() + COMPILEBATCHES_DEFAULT_DELAY);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME, !IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME));
	Timespinbox_SetTime(GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER), CTimeKey(tExecutionTime.GetTime() + COMPILEBATCHES_DEFAULT_DELAY));
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME));
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnScheduleDaily()
{
	CTimeKey  tExecutionTime;
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		pBatchInfo->SetScheduleOptions((!IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY)) ? COMPILEBATCH_SCHEDULE_DAILY : 0);
		pBatchInfo->SetLastExecutionTime(min(pBatchInfo->GetLastExecutionTime(), tExecutionTime));
		pBatchInfo->SetDailyExecutionTime(tExecutionTime.GetTime() % SECONDSPERDAY);
	}
	CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_IMMEDIATELY, FALSE);
	CheckDlgButton(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY, !IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY));
	Timespinbox_SetTime(GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER), tExecutionTime);
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY));
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnSelchangeBatch()
{
	SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_GETCURSEL));
	ShowBatchProperties();
}

void CCompileBatchesDialog::OnEditchangeBatch()
{
	CString  szBatch;

	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE)->GetWindowText(szBatch);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_ADD)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatch) < 0) ? (Check(FALSE) && CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE)) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szBatch) >= 0 && szBatch.Compare(STRING(IDS_COMPILEBATCHES_PROFILE_DEFAULT))) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
	GetDlgItem(IDC_COMPILE_BATCHES_PROFILE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_BATCHES_PROFILE, CB_GETCOUNT) > 1) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEBATCHES_CHANGE) : FALSE);
}

void CCompileBatchesDialog::OnSpinchangeExecutionTime()
{
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		pBatchInfo->SetLastExecutionTime(min(pBatchInfo->GetLastExecutionTime(), CTime::GetCurrentTime().GetTime()));
		pBatchInfo->SetExecutionTime(Timespinbox_GetTime(GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_ATTIME_NUMBER)));
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnSpinchangeDailyTime()
{
	CCompileBatchInfo  *pBatchInfo;

	if ((pBatchInfo = FindBatch()))
	{
		pBatchInfo->SetLastExecutionTime(min(pBatchInfo->GetLastExecutionTime(), CTime::GetCurrentTime().GetTime()));
		pBatchInfo->SetDailyExecutionTime(Timespinbox_GetTime(GetDlgItem(IDC_COMPILE_BATCHES_SCHEDULE_EXECUTE_DAILY_NUMBER)).GetTime() % SECONDSPERDAY);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileBatchesDialog::OnOK()
{
	INT  nBatch;
	INT  nBatches;
	CCompileBatchInfo  *pBatchInfo[2];
	CHourglassCursor  cCursor;

	for (nBatch = 0, nBatches = (INT)m_pBatches[0].GetSize(); nBatch < nBatches; nBatch++)
	{
		if ((pBatchInfo[0] = m_pBatches[0].GetAt(nBatch)) != (CCompileBatchInfo *)NULL)
		{
			if ((pBatchInfo[1] = m_pBatches[1].GetAt(m_pBatches[1].Find(pBatchInfo[0]->GetName()))))
			{
				pBatchInfo[0]->SetModified(!pBatchInfo[0]->Compare(pBatchInfo[1]));
				continue;
			}
			pBatchInfo[0]->SetModified();
		}
	}
	SetCompileBatchProfiles(m_pBatches[0]);
	CLocaleDialog::OnOK();
}

BOOL CCompileBatchesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_COMPILEBATCHESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CCompileBatchesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_COMPILEBATCHESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CCompileDirectiveInfo

CCompileDirectivesInfo::CCompileDirectivesInfo() : CObject()
{
	m_nFlags = 0;
}

CCompileDirectivesInfo::~CCompileDirectivesInfo()
{
	RemoveAll();
}

VOID CCompileDirectivesInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CCompileDirectivesInfo::GetName() CONST
{
	return m_szName;
}

VOID CCompileDirectivesInfo::SetFlags(UINT nFlags)
{
	m_nFlags = nFlags;
}

UINT CCompileDirectivesInfo::GetFlags() CONST
{
	return m_nFlags;
}

VOID CCompileDirectivesInfo::SetMessages(CONST CStringArray &szMessages)
{
	m_szMessages.Copy(szMessages);
}

INT CCompileDirectivesInfo::GetMessages(CStringArray &szMessages) CONST
{
	szMessages.Copy(m_szMessages);
	return((INT)szMessages.GetSize());
}

INT CCompileDirectivesInfo::Add(LPCTSTR pszMessage)
{
	INT  nIndex;

	if ((nIndex = Find(pszMessage)) < 0)
	{
		m_szMessages.Add(pszMessage);
		return((INT)m_szMessages.GetUpperBound());
	}
	return nIndex;
}

INT CCompileDirectivesInfo::Find(LPCTSTR pszMessage, INT nIndex) CONST
{
	INT  nMessage;
	INT  nMessages;

	for (nMessage = max(nIndex, 0), nMessages = (INT)m_szMessages.GetSize(); nMessage < nMessages; nMessage++)
	{
		if (m_szMessages.GetAt(nMessage) == pszMessage) break;
		continue;
	}
	return((nMessage < nMessages) ? nMessage : -1);
}

CString CCompileDirectivesInfo::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < m_szMessages.GetSize()) ? m_szMessages.GetAt(nIndex) : EMPTYSTRING);
}

CString CCompileDirectivesInfo::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < m_szMessages.GetSize()) ? m_szMessages.GetAt(nIndex) : EMPTYSTRING);
}

VOID CCompileDirectivesInfo::RemoveAll()
{
	m_szMessages.RemoveAll();
}

VOID CCompileDirectivesInfo::Copy(CONST CCompileDirectivesInfo *pDirectivesInfo)
{
	m_szName = pDirectivesInfo->m_szName;
	m_nFlags = pDirectivesInfo->m_nFlags;
	m_szMessages.Copy(pDirectivesInfo->m_szMessages);
}

BOOL CCompileDirectivesInfo::Compare(CONST CCompileDirectivesInfo *pDirectivesInfo) CONST
{
	INT  nMessage;
	INT  nMessages;

	for (nMessage = 0, nMessages = (pDirectivesInfo->m_szName == m_szName && pDirectivesInfo->m_nFlags == m_nFlags && pDirectivesInfo->m_szMessages.GetSize() == m_szMessages.GetSize()) ? (INT)m_szMessages.GetSize() : -1; nMessage < nMessages; nMessage++)
	{
		if (pDirectivesInfo->Find(m_szMessages.GetAt(nMessage)) < 0) break;
		continue;
	}
	return((nMessage == nMessages) ? TRUE : FALSE);
}

BOOL CCompileDirectivesInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nMessage;
	INT  nMessages;
	CByteArray  nMessageData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	for (nMessage = 0, nMessages = (INT)m_szMessages.GetSize(), sData.cbMessages = 0; nMessage < nMessages; nMessage++, sData.cbMessages += cbData)
	{
		nMessageData.SetSize(sData.cbMessages + (cbData = (m_szMessages.GetAt(nMessage).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nMessageData.GetData() + sData.cbMessages, (LPCTSTR)m_szMessages.GetAt(nMessage), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbMessages)), sData.nFlags = m_nFlags; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), nMessageData.GetData(), sData.cbMessages);
		return TRUE;
	}
	return FALSE;
}

BOOL CCompileDirectivesInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbMessage;
	INT  cbMessages;
	CByteArray  nMessageData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbMessages && sData.cbName > 0 && sData.cbMessages >= 0; )
	{
		for (CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName)), nMessageData.SetSize(sData.cbMessages), CopyMemory(nMessageData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbName), sData.cbMessages), m_nFlags = sData.nFlags, m_szName.ReleaseBuffer(), m_szMessages.RemoveAll(), cbMessage = cbMessages = 0; cbMessages < sData.cbMessages; cbMessages += (cbMessage = (m_szMessages.GetAt(m_szMessages.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szMessages.Add((LPCTSTR)(nMessageData.GetData() + cbMessages));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CCompileDirectives

CCompileDirectives::CCompileDirectives() : CPtrArray()
{
	return;
}

CCompileDirectives::~CCompileDirectives()
{
	RemoveAll();
}

BOOL CCompileDirectives::SetActiveDirectives(LPCTSTR pszName)
{
	INT  nItem;
	INT  nItems;
	CCompileDirectivesInfo  *pDirectivesInfo;

	for (nItem = 0, nItems = (INT)GetSize(); nItem < nItems; nItem++)
	{
		if ((pDirectivesInfo = GetAt(nItem)) != (CCompileDirectivesInfo *)NULL)
		{
			pDirectivesInfo->SetFlags((pDirectivesInfo->GetName() == pszName) ? (pDirectivesInfo->GetFlags() | COMPILEDIRECTIVES_FLAGS_ACTIVE) : (pDirectivesInfo->GetFlags() & ~COMPILEDIRECTIVES_FLAGS_ACTIVE));
			continue;
		}
	}
	return((Find(pszName) >= 0) ? TRUE : FALSE);
}

CString CCompileDirectives::GetActiveDirectives() CONST
{
	INT  nItem;
	INT  nItems;
	CString  szItem;
	CCompileDirectivesInfo  *pDirectivesInfo;

	for (nItem = 0, nItems = (INT)GetSize(); nItem < nItems; nItem++)
	{
		if ((pDirectivesInfo = GetAt(nItem)) != (CCompileDirectivesInfo *)NULL)
		{
			if (pDirectivesInfo->GetFlags() & COMPILEDIRECTIVES_FLAGS_ACTIVE)
			{
				szItem = pDirectivesInfo->GetName();
				break;
			}
		}
	}
	return((nItem < nItems) ? szItem : STRING(IDS_COMPILEDIRECTIVES_PROFILE_DEFAULT));
}

INT CCompileDirectives::Add(CCompileDirectivesInfo *pDirectivesInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pDirectivesInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pDirectivesInfo, 1);
	return nIndex;
}

INT CCompileDirectives::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CCompileDirectivesInfo *CCompileDirectives::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CCompileDirectivesInfo *)CPtrArray::GetAt(nIndex) : (CCompileDirectivesInfo *)NULL);
}

CCompileDirectivesInfo *CCompileDirectives::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CCompileDirectivesInfo *)CPtrArray::GetAt(nIndex) : (CCompileDirectivesInfo *)NULL);
}

VOID CCompileDirectives::RemoveAll()
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (INT)GetSize(); nItem < nItems; nItem++)
	{
		delete GetAt(nItem);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CCompileDirectives::Copy(CONST CCompileDirectives *pDirectives)
{
	INT  nItem;
	INT  nItems;
	CCompileDirectivesInfo  *pDirectivesInfo;

	for (nItem = 0, nItems = (INT)pDirectives->GetSize(), RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pDirectivesInfo = new CCompileDirectivesInfo) != (CCompileDirectivesInfo *)NULL)
		{
			pDirectivesInfo->Copy(pDirectives->GetAt(nItem));
			InsertAt(nItem, pDirectivesInfo, 1);
			continue;
		}
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CCompileDirectives::Compare(CONST CCompileDirectives *pDirectives) CONST
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (pDirectives->GetSize() == GetSize()) ? (INT)GetSize() : -1; nItem < nItems; nItem++)
	{
		if (!pDirectives->GetAt(nItem)->Compare(GetAt(nItem))) break;
		continue;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CCompileDirectives::Map(CByteArray &nInfo) CONST
{
	INT  nItem;
	INT  nItems;
	CByteArray  nDirectivesData;
	CCompileDirectivesInfo  *pDirectivesInfo;

	for (nItem = 0, nItems = (INT)GetSize(), nInfo.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pDirectivesInfo = GetAt(nItem)) && pDirectivesInfo->Map(nDirectivesData) && nInfo.Append(nDirectivesData) >= 0) continue;
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CCompileDirectives::Unmap(CONST CByteArray &nInfo)
{
	INT  cbItem;
	INT  cbItems;
	CByteArray  nDirectivesData;
	CCompileDirectivesInfo  *pDirectivesInfo;

	for (cbItems = 0, RemoveAll(); cbItems < nInfo.GetSize(); cbItems += cbItem)
	{
		for (CopyMemory(&cbItem, nInfo.GetData() + cbItems, sizeof(cbItem)), nDirectivesData.SetSize(max(min(cbItem, nInfo.GetSize() - cbItems), 0)); nDirectivesData.GetSize() >= 0; )
		{
			CopyMemory(nDirectivesData.GetData(), nInfo.GetData() + cbItems, nDirectivesData.GetSize());
			break;
		}
		if ((pDirectivesInfo = new CCompileDirectivesInfo))
		{
			if (pDirectivesInfo->Unmap(nDirectivesData) && Add(pDirectivesInfo) >= 0) continue;
			delete pDirectivesInfo;
		}
		break;
	}
	if ((pDirectivesInfo = (!nInfo.GetSize()) ? new CCompileDirectivesInfo : (CCompileDirectivesInfo *)NULL))
	{
		for (pDirectivesInfo->SetName(STRING(IDS_COMPILEDIRECTIVES_PROFILE_DEFAULT)), pDirectivesInfo->SetFlags(COMPILEDIRECTIVES_FLAGS_ACTIVE); Add(pDirectivesInfo) >= 0; ) return TRUE;
		delete pDirectivesInfo;
		return FALSE;
	}
	return((cbItems == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CCompileDirectives::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CCompileDirectivesInfo  *pDirectivesInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pDirectivesInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pDirectivesInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pDirectivesInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pDirectivesInfo->GetName() == pszName) || (bInsert && (((pDirectivesInfo = GetAt(max(nIndex[0] - 1, 0))) && pDirectivesInfo->GetName() != pszName && (pDirectivesInfo = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pDirectivesInfo->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CCompileDirectivesDialog dialog

IMPLEMENT_DYNCREATE(CCompileDirectivesDialog, CLocaleDialog)

CCompileDirectivesDialog::CCompileDirectivesDialog(CWnd *pParentWnd) : CLocaleDialog(CCompileDirectivesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CCompileDirectivesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CCompileDirectivesDialog::Initialize()
{
	CByteArray  nInfo;
	CProfile  cProfile;

	cProfile.GetCompileDirectivesInfo(nInfo);
	return((m_pDirectives[0].Unmap(nInfo)) ? m_pDirectives[1].Copy(&m_pDirectives[0]) : FALSE);
}

BOOL CCompileDirectivesDialog::EnumProfiles()
{
	INT  nDirective;
	INT  nDirectives;
	CCompileDirectivesInfo  *pDirectivesInfo;

	for (nDirective = 0, nDirectives = (INT)m_pDirectives[0].GetSize(); nDirective < nDirectives; nDirective++)
	{
		if ((pDirectivesInfo = m_pDirectives[0].GetAt(nDirective)) && (pDirectivesInfo->GetFlags() & COMPILEDIRECTIVES_FLAGS_ACTIVE))
		{
			SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pDirectivesInfo->GetName());
			SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_SETCURSEL, nDirective);
			continue;
		}
		if ((pDirectivesInfo = m_pDirectives[0].GetAt(nDirective)))
		{
			SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pDirectivesInfo->GetName());
			continue;
		}
	}
	for (; SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_GETCURSEL) < 0; )
	{
		SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_COMPILEDIRECTIVES_PROFILE_DEFAULT)));
		break;
	}
	return((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

BOOL CCompileDirectivesDialog::EnumMessages()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	INT  nMessage;
	INT  nMessages;
	CString  szItem;
	CStringArray  szMessages;

	SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_DELETEALLITEMS);
	for (nItem = 0, nItems = (ReadConsoleText(STRING(IDS_OUTPUTWINDOW_BUILDTAB), m_szMessages, FALSE, FALSE)) ? (INT)m_szMessages.GetSize() : 0; nItem < nItems; nItem++)
	{
		for (nMessage = 0, nMessages = (INT)szMessages.GetSize(); nMessage < nMessages; nMessage++)
		{
			if (m_szMessages.GetAt(nItem) == szMessages.GetAt(nMessage)) break;
			continue;
		}
		if ((!m_szMessages.GetAt(nItem).Find(STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX)) || !m_szMessages.GetAt(nItem).Find(STRING(IDS_COMPILER_MESSAGE_WARNING_PREFIX))) && nMessage == nMessages)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns[0].GetSize(); nColumn < nColumns; nColumn = nColumn + 1)
			{
				for (; m_szColumns[0].GetAt(nColumn) == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TYPE); )
				{
					szItem = (!m_szMessages.GetAt(nItem).Find(STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX))) ? STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGETYPE_ERROR) : STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGETYPE_WARNING);
					break;
				}
				for (; m_szColumns[0].GetAt(nColumn) == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TEXT); )
				{
					if (!m_szMessages.GetAt(nItem).Find(STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX)))
					{
						szItem = m_szMessages.GetAt(nItem).Mid(lstrlen(STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX)));
						break;
					}
					if (!m_szMessages.GetAt(nItem).Find(STRING(IDS_COMPILER_MESSAGE_WARNING_PREFIX)))
					{
						szItem = m_szMessages.GetAt(nItem).Mid(lstrlen(STRING(IDS_COMPILER_MESSAGE_WARNING_PREFIX)));
						break;
					}
					szItem = m_szMessages.GetAt(nItem);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), (INT)szMessages.GetSize(), szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), (INT)szMessages.GetSize(), nColumn, szItem);
			}
			szMessages.Add(m_szMessages.GetAt(nItem));
			continue;
		}
		m_szMessages.RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	Listview_SetCurText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), 0);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES_STATIC)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

VOID CCompileDirectivesDialog::ShowDirectives()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CString  szProfile;
	CStringArray  szMessages;
	CCompileDirectivesInfo  *pDirectivesInfo;

	SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->GetWindowText(szProfile);
	if ((pDirectivesInfo = FindDirectives()) != (CCompileDirectivesInfo *)NULL)
	{
		for (nItem = 0, nItems = pDirectivesInfo->GetMessages(szMessages); nItem < nItems; nItem++)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns[1].GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns[1].GetAt(nColumn) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TYPE); )
				{
					szItem = (!szMessages.GetAt(nItem).Find(STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX))) ? STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGETYPE_ERROR) : STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGETYPE_WARNING);
					break;
				}
				for (; m_szColumns[1].GetAt(nColumn) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TEXT); )
				{
					if (!szMessages.GetAt(nItem).Find(STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX)))
					{
						szItem = szMessages.GetAt(nItem).Mid(lstrlen(STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX)));
						break;
					}
					if (!szMessages.GetAt(nItem).Find(STRING(IDS_COMPILER_MESSAGE_WARNING_PREFIX)))
					{
						szItem = szMessages.GetAt(nItem).Mid(lstrlen(STRING(IDS_COMPILER_MESSAGE_WARNING_PREFIX)));
						break;
					}
					szItem = szMessages.GetAt(nItem);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem, nColumn, szItem);
			}
		}
		Listview_SetCurText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), 0);
		CheckDlgButton(IDC_COMPILE_DIRECTIVES_NOWARNINGS, (pDirectivesInfo->GetFlags() & COMPILEDIRECTIVES_FLAGS_NOWARNINGS) ? TRUE : FALSE);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_ADD)->EnableWindow((szProfile.GetLength() < 0) ? TRUE : FALSE);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVE)->EnableWindow((szProfile != STRING(IDS_COMPILEDIRECTIVES_PROFILE_DEFAULT)) ? TRUE : FALSE);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_GETCOUNT) > 1) ? TRUE : FALSE);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED_STATIC)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	}
	else
	{
		CheckDlgButton(IDC_COMPILE_DIRECTIVES_NOWARNINGS, FALSE);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_ADD)->EnableWindow(!szProfile.IsEmpty());
		GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVE)->EnableWindow((szProfile.GetLength() < 0) ? TRUE : FALSE);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_GETCOUNT) > 1) ? TRUE : FALSE);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED_STATIC)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	}
	UpdateDirectives();
}

VOID CCompileDirectivesDialog::UpdateDirectives()
{
	INT  nItem[2];
	INT  nItems[2];
	INT  nColumn[2];
	INT  nColumns[2];
	CString  szItem[2][2];

	for (nItem[0] = 0, nItems[0] = (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_GETITEMCOUNT); nItem[0] < nItems[0]; nItem[0]++)
	{
		for (nColumn[0] = 0, nColumns[0] = (Listview_IsSelText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nItem[0])) ? (INT)m_szColumns[0].GetSize() : 0; nColumn[0] < nColumns[0]; nColumn[0]++)
		{
			for (; m_szColumns[0].GetAt(nColumn[0]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TYPE); )
			{
				szItem[0][0] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nItem[0], nColumn[0]);
				break;
			}
			for (; m_szColumns[0].GetAt(nColumn[0]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TEXT); )
			{
				szItem[0][1] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nItem[0], nColumn[0]);
				break;
			}
		}
		for (nItem[1] = 0, nItems[1] = (nColumns[0] > 0) ? (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) : 0; nItem[1] < nItems[1]; nItem[1]++)
		{
			for (nColumn[1] = 0, nColumns[1] = (INT)m_szColumns[1].GetSize(); nColumn[1] < nColumns[1]; nColumn[1]++)
			{
				for (; m_szColumns[1].GetAt(nColumn[1]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TYPE); )
				{
					szItem[1][0] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem[1], nColumn[1]);
					break;
				}
				for (; m_szColumns[1].GetAt(nColumn[1]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TEXT); )
				{
					szItem[1][1] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem[1], nColumn[1]);
					break;
				}
			}
			if (szItem[0][0] == szItem[1][0] && szItem[0][1] == szItem[1][1]) break;
		}
		if (nItem[1] == nItems[1] && nColumns[0] > 0) break;
	}
	GetDlgItem(IDC_COMPILE_DIRECTIVES_ENABLE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED)) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_DELETE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED)) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLE)->EnableWindow((nItem[0] < nItems[0]) ? TRUE : FALSE);
}

CCompileDirectivesInfo *CCompileDirectivesDialog::FindDirectives() CONST
{
	CString  szProfile;

	GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->GetWindowText(szProfile);
	return m_pDirectives[0].GetAt(m_pDirectives[0].Find(szProfile));
}

BOOL CCompileDirectivesDialog::IsModified() CONST
{
	CString  szProfile;

	GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->GetWindowText(szProfile);
	return(((m_pDirectives[0].GetActiveDirectives() != szProfile  &&  m_pDirectives[0].Find(szProfile) >= 0) || !m_pDirectives[0].Compare(&m_pDirectives[1])) ? TRUE : FALSE);
}

void CCompileDirectivesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompileDirectivesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CCompileDirectivesDialog::PostNcDestroy()
{
	m_szMessages.RemoveAll();
	m_szColumns[0].RemoveAll();
	m_szColumns[1].RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CCompileDirectivesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CCompileDirectivesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_COMPILE_DIRECTIVES_ADD, OnAdd)
	ON_BN_CLICKED(IDC_COMPILE_DIRECTIVES_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_COMPILE_DIRECTIVES_REMOVEALL, OnRemoveAll)
	ON_BN_CLICKED(IDC_COMPILE_DIRECTIVES_NOWARNINGS, OnNoWarnings)
	ON_BN_CLICKED(IDC_COMPILE_DIRECTIVES_ENABLE, OnEnable)
	ON_BN_CLICKED(IDC_COMPILE_DIRECTIVES_DISABLE, OnDisable)
	ON_BN_CLICKED(IDC_COMPILE_DIRECTIVES_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_COMPILE_DIRECTIVES_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_COMPILE_DIRECTIVES_PROFILE, OnSelchangeProfile)
	ON_CBN_EDITCHANGE(IDC_COMPILE_DIRECTIVES_PROFILE, OnEditchangeProfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompileDirectivesDialog message handlers

BOOL CCompileDirectivesDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED)->GetClientRect(rColumns[1]);
	m_szColumns[0].Add(STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TYPE));
	m_szColumns[0].Add(STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TEXT));
	m_szColumns[1].Add(STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TYPE));
	m_szColumns[1].Add(STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TEXT));
	SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns[0].GetSize(), nWidth = rColumns[0].Width() / 6; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - GetSystemMetrics(SM_CXVSCROLL) - nWidth) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nColumn, m_szColumns[0].GetAt(nColumn), nWidth);
		continue;
	}
	for (nColumn = 0, nColumns = (INT)m_szColumns[1].GetSize(), nWidth = rColumns[1].Width() / 6; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[1].Width() - GetSystemMetrics(SM_CXVSCROLL) - nWidth) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nColumn, m_szColumns[1].GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumProfiles() && EnumMessages())
	{
		GetDlgItem(IDC_COMPILE_DIRECTIVES_DETAILS)->EnableWindow();
		GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->EnableWindow();
		GetDlgItem(IDC_COMPILE_DIRECTIVES_NOWARNINGS)->EnableWindow();
		ShowDirectives();
	}
	return TRUE;
}

BOOL CCompileDirectivesDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	for (; pNotifyListView->hdr.idFrom == IDC_COMPILE_DIRECTIVES_MESSAGES; )
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			UpdateDirectives();
			break;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK) OnDisable();
		break;
	}
	for (; pNotifyListView->hdr.idFrom == IDC_COMPILE_DIRECTIVES_DISABLED; )
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			UpdateDirectives();
			break;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK) OnEnable();
		break;
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void CCompileDirectivesDialog::OnAdd()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CString  szProfile;
	CString  szMessage;
	CStringArray  szMessages;
	CCompileDirectivesInfo  *pDirectivesInfo;
	CHourglassCursor  cCursor;

	if ((pDirectivesInfo = new CCompileDirectivesInfo))
	{
		for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns[1].GetSize(); nColumn < nColumns; nColumn++)
			{
				if (m_szColumns[1].GetAt(nColumn) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TYPE))
				{
					szItem = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem, nColumn);
					szMessage = (szItem == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGETYPE_ERROR)) ? STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX) : STRING(IDS_COMPILER_MESSAGE_WARNING_PREFIX);
				}
				if (m_szColumns[1].GetAt(nColumn) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TEXT))
				{
					szItem = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem, nColumn);
					szMessage += szItem;
				}
			}
			szMessages.Add(szMessage);
		}
		for (GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->GetWindowText(szProfile); (nIndex = (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfile)) >= 0; )
		{
			SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_SETCURSEL, nIndex);
			break;
		}
		pDirectivesInfo->SetName(szProfile);
		pDirectivesInfo->SetMessages(szMessages);
		m_pDirectives[0].Add(pDirectivesInfo);
	}
	GetDlgItem(IDC_COMPILE_DIRECTIVES_ADD)->EnableWindow((GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->GetWindowTextLength() > 0 && !FindDirectives()) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVE)->EnableWindow((GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->GetWindowTextLength() > 0 && FindDirectives()) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_GETCOUNT) > 1) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileDirectivesDialog::OnRemove()
{
	INT  nIndex;
	CString  szProfile;
	CCompileDirectivesInfo  *pDirectivesInfo;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->GetWindowText(szProfile);
	if ((pDirectivesInfo = (szProfile != STRING(IDS_COMPILEDIRECTIVES_PROFILE_DEFAULT)) ? m_pDirectives[0].GetAt((nIndex = m_pDirectives[0].Find(szProfile))) : (CCompileDirectivesInfo *)NULL))
	{
		SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile));
		m_pDirectives[0].RemoveAt(nIndex);
		delete pDirectivesInfo;
	}
	for (; SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_COMPILEDIRECTIVES_PROFILE_DEFAULT))) >= 0; )
	{
		ShowDirectives();
		break;
	}
	GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_GETCOUNT) > 1) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileDirectivesDialog::OnRemoveAll()
{
	INT  nIndex;
	INT  nProfile;
	INT  nProfiles;
	CString  szProfile;
	CCompileDirectivesInfo  *pDirectivesInfo;
	CHourglassCursor  cCursor;

	for (nProfile = 0, nProfiles = (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_GETCOUNT); nProfile < nProfiles; nProfile++)
	{
		if ((pDirectivesInfo = ((szProfile = Combobox_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE), nProfile)) != STRING(IDS_COMPILEDIRECTIVES_PROFILE_DEFAULT)) ? m_pDirectives[0].GetAt((nIndex = m_pDirectives[0].Find(szProfile))) : (CCompileDirectivesInfo *)NULL))
		{
			SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_DELETESTRING, nProfile);
			m_pDirectives[0].RemoveAt(nIndex);
			delete pDirectivesInfo;
			nProfiles--;
			nProfile--;
		}
	}
	for (; SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_COMPILEDIRECTIVES_PROFILE_DEFAULT))) >= 0; )
	{
		ShowDirectives();
		break;
	}
	GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileDirectivesDialog::OnEnable()
{
	INT  nItem[2];
	INT  nItems[2];
	INT  nColumn[2];
	INT  nColumns[2];
	CString  szItem[2][2];
	CStringArray  szMessages;
	CCompileDirectivesInfo  *pDirectivesInfo;
	CHourglassCursor  cCursor;

	for (nItem[0] = 0, nItems[0] = (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT); nItem[0] < nItems[0]; nItem[0]++)
	{
		for (nColumn[1] = 0, nColumns[1] = (Listview_IsSelText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem[0])) ? (INT)m_szColumns[1].GetSize() : 0; nColumn[1] < nColumns[1]; nColumn[1]++)
		{
			for (; m_szColumns[1].GetAt(nColumn[1]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TYPE); )
			{
				szItem[0][0] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem[0], nColumn[1]);
				break;
			}
			for (; m_szColumns[1].GetAt(nColumn[1]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TEXT); )
			{
				szItem[0][1] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem[0], nColumn[1]);
				break;
			}
		}
		for (nItem[1] = 0, nItems[1] = (nColumns[1] > 0) ? (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_GETITEMCOUNT) : 0; nItem[1] < nItems[1]; nItem[1]++)
		{
			for (nColumn[0] = 0, nColumns[0] = (INT)m_szColumns[0].GetSize(); nColumn[0] < nColumns[0]; nColumn[0]++)
			{
				for (; m_szColumns[0].GetAt(nColumn[0]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TYPE); )
				{
					szItem[1][0] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nItem[1], nColumn[0]);
					break;
				}
				for (; m_szColumns[0].GetAt(nColumn[0]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TEXT); )
				{
					szItem[1][1] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nItem[1], nColumn[0]);
					break;
				}
			}
			if (szItem[0][0] == szItem[1][0] && szItem[0][1] == szItem[1][1]) break;
		}
		if (nColumns[1] > 0)
		{
			if (nItem[1] == nItems[1])
			{
				for (nColumn[0] = 0, nColumns[0] = (INT)m_szColumns[0].GetSize(); nColumn[0] < nColumns[0]; nColumn[0]++)
				{
					for (; m_szColumns[0].GetAt(nColumn[0]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TYPE); )
					{
						szItem[1][0] = szItem[0][0];
						break;
					}
					for (; m_szColumns[0].GetAt(nColumn[0]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TEXT); )
					{
						szItem[1][1] = szItem[0][1];
						break;
					}
					if (!nColumn[0])
					{
						Listview_InsertText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nItem[1], szItem[1][0]);
						continue;
					}
					Listview_SetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nItem[1], nColumn[0], szItem[1][1]);
				}
			}
			if (Listview_DeleteText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem[0]))
			{
				if ((pDirectivesInfo = FindDirectives()) && nItem[0] < pDirectivesInfo->GetMessages(szMessages))
				{
					for (; nItem[1] == nItems[1]; )
					{
						m_szMessages.InsertAt(nItem[1], szMessages.GetAt(nItem[0]));
						break;
					}
					szMessages.RemoveAt(nItem[0]);
					nItems[0]--;
					nItem[0]--;
				}
				pDirectivesInfo->SetMessages(szMessages);
			}
		}
	}
	for (; Listview_GetCurText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES)) < 0; )
	{
		Listview_SetCurText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), 0);
		break;
	}
	UpdateDirectives();
	GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES_STATIC)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED_STATIC)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileDirectivesDialog::OnNoWarnings()
{
	CCompileDirectivesInfo  *pDirectivesInfo;

	for (; (pDirectivesInfo = FindDirectives()); )
	{
		pDirectivesInfo->SetFlags((IsDlgButtonChecked(IDC_COMPILE_DIRECTIVES_NOWARNINGS)) ? (pDirectivesInfo->GetFlags() | COMPILEDIRECTIVES_FLAGS_NOWARNINGS) : (pDirectivesInfo->GetFlags() & ~COMPILEDIRECTIVES_FLAGS_NOWARNINGS));
		break;
	}
	UpdateDirectives();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileDirectivesDialog::OnDisable()
{
	INT  nItem[2];
	INT  nItems[2];
	INT  nColumn[2];
	INT  nColumns[2];
	CString  szItem[2][2];
	CStringArray  szMessages;
	CCompileDirectivesInfo  *pDirectivesInfo;
	CHourglassCursor  cCursor;

	for (nItem[0] = 0, nItems[0] = (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_GETITEMCOUNT); nItem[0] < nItems[0]; nItem[0]++)
	{
		for (nColumn[0] = 0, nColumns[0] = (Listview_IsSelText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nItem[0])) ? (INT)m_szColumns[0].GetSize() : 0; nColumn[0] < nColumns[0]; nColumn[0]++)
		{
			for (; m_szColumns[0].GetAt(nColumn[0]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TYPE); )
			{
				szItem[0][0] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nItem[0], nColumn[0]);
				break;
			}
			for (; m_szColumns[0].GetAt(nColumn[0]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_MESSAGESTITLEITEM_TEXT); )
			{
				szItem[0][1] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES), nItem[0], nColumn[0]);
				break;
			}
		}
		for (nItem[1] = 0, nItems[1] = (nColumns[0] > 0) ? (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) : 0; nItem[1] < nItems[1]; nItem[1]++)
		{
			for (nColumn[1] = 0, nColumns[1] = (INT)m_szColumns[1].GetSize(); nColumn[1] < nColumns[1]; nColumn[1]++)
			{
				for (; m_szColumns[1].GetAt(nColumn[1]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TYPE); )
				{
					szItem[1][0] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem[1], nColumn[1]);
					break;
				}
				for (; m_szColumns[1].GetAt(nColumn[1]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TEXT); )
				{
					szItem[1][1] = Listview_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem[1], nColumn[1]);
					break;
				}
			}
			if (szItem[0][0] == szItem[1][0] && szItem[0][1] == szItem[1][1]) break;
		}
		if (nItem[1] == nItems[1] && nColumns[0] > 0)
		{
			if ((pDirectivesInfo = FindDirectives()) && pDirectivesInfo->GetMessages(szMessages) >= 0)
			{
				for (nColumn[1] = 0, nColumns[1] = (INT)m_szColumns[1].GetSize(), szMessages.InsertAt(nItem[1], m_szMessages.GetAt(nItem[0])), pDirectivesInfo->SetMessages(szMessages); nColumn[1] < nColumns[1]; nColumn[1]++)
				{
					for (; m_szColumns[1].GetAt(nColumn[1]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TYPE); )
					{
						szItem[1][0] = szItem[0][0];
						break;
					}
					for (; m_szColumns[1].GetAt(nColumn[1]) == STRING(IDS_COMPILEDIRECTIVESDIALOG_DISABLEDTITLEITEM_TEXT); )
					{
						szItem[1][0] = szItem[0][1];
						break;
					}
					if (!nColumn[1])
					{
						Listview_InsertText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem[1], szItem[1][0]);
						continue;
					}
					Listview_SetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem[1], nColumn[1], szItem[1][0]);
				}
			}
		}
	}
	for (; Listview_GetCurText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED)) < 0; )
	{
		Listview_SetCurText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), 0);
		break;
	}
	UpdateDirectives();
	GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES_STATIC)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_MESSAGES)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_MESSAGES, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED_STATIC)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileDirectivesDialog::OnDelete()
{
	INT  nItem;
	INT  nItems;
	CStringArray  szMessages;
	CCompileDirectivesInfo  *pDirectivesInfo;
	CHourglassCursor  cCursor;

	if ((pDirectivesInfo = FindDirectives()))
	{
		for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT), pDirectivesInfo->GetMessages(szMessages); nItem < nItems; nItem++)
		{
			if (Listview_IsSelText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem) && nItem < szMessages.GetSize())
			{
				if (Listview_DeleteText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), nItem))
				{
					szMessages.RemoveAt(nItem);
					nItems--;
					nItem--;
				}
			}
		}
		pDirectivesInfo->SetMessages(szMessages);
		Listview_SetCurText(GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED), 0);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED_STATIC)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_COMPILE_DIRECTIVES_DISABLED)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_DISABLED, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		UpdateDirectives();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileDirectivesDialog::OnSelchangeProfile()
{
	if (SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_GETCURSEL)) >= 0) ShowDirectives();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileDirectivesDialog::OnEditchangeProfile()
{
	CString  szProfile;

	for (GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->GetWindowText(szProfile); m_pDirectives[0].Find(szProfile) >= 0; )
	{
		ShowDirectives();
		break;
	}
	GetDlgItem(IDC_COMPILE_DIRECTIVES_ADD)->EnableWindow((GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->GetWindowTextLength() > 0 && !FindDirectives()) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVE)->EnableWindow((GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE)->GetWindowTextLength() > 0 && FindDirectives()) ? TRUE : FALSE);
	GetDlgItem(IDC_COMPILE_DIRECTIVES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_GETCOUNT) > 1) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileDirectivesDialog::OnOK()
{
	CString  szProfile;
	CProfile  cProfile;
	CByteArray  nInfo;
	CHourglassCursor  cCursor;

	for (m_pDirectives[0].SetActiveDirectives((m_pDirectives[0].Find((szProfile = Combobox_GetText(GetDlgItem(IDC_COMPILE_DIRECTIVES_PROFILE), (INT)SendDlgItemMessage(IDC_COMPILE_DIRECTIVES_PROFILE, CB_GETCURSEL)))) >= 0) ? szProfile : STRING(IDS_COMPILEDIRECTIVES_PROFILE_DEFAULT)); m_pDirectives[0].Map(nInfo); )
	{
		cProfile.SetCompileDirectivesInfo(nInfo);
		break;
	}
	CLocaleDialog::OnOK();
}

BOOL CCompileDirectivesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_COMPILEDIRECTIVESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CCompileDirectivesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_COMPILEDIRECTIVESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CCompileOptionsDialog dialog

IMPLEMENT_DYNCREATE(CCompileOptionsDialog, CLocaleDialog)

CCompileOptionsDialog::CCompileOptionsDialog(CWnd *pParentWnd) : CLocaleDialog(CCompileOptionsDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CCompileOptionsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CCompileOptionsDialog::DoModal()
{
	INT  nID[3][2];
	INT  nIDs[3][2];
	CProfile  cProfile;

	for (nID[0][0] = MINCOMPILEROPTIONOPTIMIZATIONTYPE, nIDs[0][0] = MAXCOMPILEROPTIONOPTIMIZATIONTYPE, cProfile.GetCompileOptions(m_szFileName[0][0], m_szFileName[1][0], m_szPlatForm[0], m_szDirectory[0][0], m_szDirectory[1][0], m_szOptions[0][0], m_szOptions[1][0], m_szOptions[2][0]), m_szPlatForm[0] = (m_szPlatForm[0].IsEmpty()) ? ((sizeof(UINT_PTR) > sizeof(UINT)) ? STRING(IDS_COMPILER_PLATFORM_64BIT) : STRING(IDS_COMPILER_PLATFORM_32BIT)) : m_szPlatForm[0]; nID[0][0] <= nIDs[0][0]; nID[0][0]++)
	{
		if (m_szOptions[0][0].Find(STRING(nID[0][0])) >= 0) break;
		continue;
	}
	for (nID[0][1] = MINCOMPILEROPTIONWARNING, nIDs[0][1] = MAXCOMPILEROPTIONWARNING; nID[0][1] <= nIDs[0][1]; nID[0][1]++)
	{
		if (m_szOptions[0][0].Find(STRING(nID[0][1])) >= 0 && nID[0][1] != IDS_COMPILER_OPTION_TREATWARNING) break;
		continue;
	}
	for (nID[1][0] = MINCOMPILEROPTIONOPTIMIZATIONTYPE, nIDs[1][0] = MAXCOMPILEROPTIONOPTIMIZATIONTYPE; nID[1][0] <= nIDs[1][0]; nID[1][0]++)
	{
		if (m_szOptions[1][0].Find(STRING(nID[1][0])) >= 0) break;
		continue;
	}
	for (nID[1][1] = MINCOMPILEROPTIONWARNING, nIDs[1][1] = MAXCOMPILEROPTIONWARNING; nID[1][1] <= nIDs[1][1]; nID[1][1]++)
	{
		if (m_szOptions[1][0].Find(STRING(nID[1][1])) >= 0 && nID[1][1] != IDS_COMPILER_OPTION_TREATWARNING) break;
		continue;
	}
	for (nID[2][0] = MINCOMPILEROPTIONOPTIMIZATIONTYPE, nIDs[2][0] = MAXCOMPILEROPTIONOPTIMIZATIONTYPE; nID[2][0] <= nIDs[2][0]; nID[2][0]++)
	{
		if (m_szOptions[2][0].Find(STRING(nID[2][0])) >= 0) break;
		continue;
	}
	for (nID[2][1] = MINCOMPILEROPTIONWARNING, nIDs[2][1] = MAXCOMPILEROPTIONWARNING; nID[2][1] <= nIDs[2][1]; nID[2][1]++)
	{
		if (m_szOptions[2][0].Find(STRING(nID[2][1])) >= 0 && nID[2][1] != IDS_COMPILER_OPTION_TREATWARNING) break;
		continue;
	}
	m_szOptions[0][0] = (nID[0][0] > MAXCOMPILEROPTIONOPTIMIZATIONTYPE) ? (m_szOptions[0][0] + SPACE + STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) : m_szOptions[0][0];
	m_szOptions[1][0] = (nID[1][0] > MAXCOMPILEROPTIONOPTIMIZATIONTYPE) ? (m_szOptions[1][0] + SPACE + STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) : m_szOptions[1][0];
	m_szOptions[2][0] = (nID[2][0] > MAXCOMPILEROPTIONOPTIMIZATIONTYPE) ? (m_szOptions[2][0] + SPACE + STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) : m_szOptions[2][0];
	m_szOptions[0][0] = (nID[0][1] > MAXCOMPILEROPTIONWARNING) ? (m_szOptions[0][0] + SPACE + STRING(IDS_COMPILER_OPTION_WARNING3)) : m_szOptions[0][0];
	m_szOptions[1][0] = (nID[1][1] > MAXCOMPILEROPTIONWARNING) ? (m_szOptions[1][0] + SPACE + STRING(IDS_COMPILER_OPTION_WARNING3)) : m_szOptions[1][0];
	m_szOptions[2][0] = (nID[2][1] > MAXCOMPILEROPTIONWARNING) ? (m_szOptions[2][0] + SPACE + STRING(IDS_COMPILER_OPTION_WARNING3)) : m_szOptions[2][0];
	m_szFileName[0][1] = m_szFileName[0][0];
	m_szFileName[1][1] = m_szFileName[1][0];
	m_szDirectory[0][1] = m_szDirectory[0][0];
	m_szDirectory[1][1] = m_szDirectory[1][0];
	m_szOptions[0][1] = m_szOptions[0][0];
	m_szOptions[1][1] = m_szOptions[1][0];
	m_szOptions[2][1] = m_szOptions[2][0];
	m_szPlatForm[1] = m_szPlatForm[0];
	return CLocaleDialog::DoModal();
}
INT_PTR CCompileOptionsDialog::DoModal(CString &szFileName)
{
	INT_PTR  nResult;
	CFileFindEx  cFileFind;

	m_szFileName[0][0].Empty();
	m_szFileName[1][0].Empty();
	m_szDirectory[0][0].Empty();
	m_szDirectory[1][0].Empty();
	if (cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile())
	{
		m_szFileName[0][0] = cFileFind.GetFilePath();
		m_szFileName[1][0] = cFileFind.GetFilePath().Left(cFileFind.GetFilePath().GetLength() - cFileFind.GetFileName().GetLength()) + STRING(IDS_DERIVEDPARAMETERLANGUAGE_LINKER_FILENAME);
	}
	for (m_szOptions[0][0] = CString(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) + SPACE + CString(STRING(IDS_COMPILER_OPTION_WARNING3)), m_szOptions[1][0] = CString(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) + SPACE + CString(STRING(IDS_COMPILER_OPTION_WARNING3)), m_szOptions[2][0] = CString(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) + SPACE + CString(STRING(IDS_COMPILER_OPTION_WARNING3)), m_szFileName[0][1] = m_szFileName[0][0], m_szFileName[1][1] = m_szFileName[1][0], m_szDirectory[0][1] = m_szDirectory[0][0], m_szDirectory[1][1] = m_szDirectory[1][0], m_szOptions[0][1] = m_szOptions[0][0], m_szOptions[1][1] = m_szOptions[1][0], m_szOptions[2][1] = m_szOptions[2][0], m_szPlatForm[0] = m_szPlatForm[1] = (sizeof(UINT_PTR) > sizeof(UINT)) ? STRING(IDS_COMPILER_PLATFORM_64BIT) : STRING(IDS_COMPILER_PLATFORM_32BIT); (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		szFileName = m_szFileName[0][0];
		break;
	}
	return nResult;
}

BOOL CCompileOptionsDialog::EnumCompilationUnits()
{
	INT  nID;
	INT  nIDs;

	for (nID = MINCOMPILEOPTIONSCOMPILATIONUNIT, nIDs = MAXCOMPILEOPTIONSCOMPILATIONUNIT; nID <= nIDs; nID++)
	{
		SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(nID));
		continue;
	}
	SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT, CB_SETCURSEL);
	return((SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CCompileOptionsDialog::EnumOptimizationsOptions()
{
	INT  nID;
	INT  nIDs;
	CString  szCompilationUnit;

	GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT)->GetWindowText(szCompilationUnit);
	for (nID = MINCOMPILEOPTIONSOPTIMIZATIONTYPE, nIDs = MAXCOMPILEOPTIONSOPTIMIZATIONTYPE; nID <= nIDs; nID++)
	{
		if (SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(nID)) >= 0)
		{
			SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_SETCURSEL, ((szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_DERIVEDPARAMETERS) && ((nID == IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_NONE  &&  m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_NONE)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_DEFAULT  &&  m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_SPEED  &&  m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_SPEED)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_SIZE  &&  m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_SIZE)) >= 0))) || (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_MIMICSDESCRIPTIONFILES) && ((nID == IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_NONE  &&  m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_NONE)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_DEFAULT  &&  m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_SPEED  &&  m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_SPEED)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_SIZE  &&  m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_SIZE)) >= 0)))) ? (WPARAM)(SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_GETCOUNT) - 1) : (WPARAM)SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_GETCURSEL));
			continue;
		}
	}
	return((SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CCompileOptionsDialog::EnumWarningsOptions()
{
	INT  nID;
	INT  nIDs;
	CString  szCompilationUnit;

	GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT)->GetWindowText(szCompilationUnit);
	for (nID = MINCOMPILEOPTIONSWARNING, nIDs = MAXCOMPILEOPTIONSWARNING; nID <= nIDs; nID++)
	{
		if (SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(nID)) >= 0)
		{
			SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_SETCURSEL, ((szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_DERIVEDPARAMETERS) && ((nID == IDS_COMPILEOPTIONSDIALOG_WARNING0  &&  m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_WARNING0)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_WARNING1  &&  m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_WARNING1)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_WARNING2  &&  m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_WARNING2)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_WARNING3  &&  m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_WARNING3)) >= 0))) || (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_MIMICSDESCRIPTIONFILES) && ((nID == IDS_COMPILEOPTIONSDIALOG_WARNING0  &&  m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_WARNING0)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_WARNING1  &&  m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_WARNING1)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_WARNING2  &&  m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_WARNING2)) >= 0) || (nID == IDS_COMPILEOPTIONSDIALOG_WARNING3  &&  m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_WARNING3)) >= 0)))) ? (WPARAM)(SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_GETCOUNT) - 1) : (WPARAM)SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_GETCURSEL));
			continue;
		}
	}
	CheckDlgButton(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS, ((szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_DERIVEDPARAMETERS) && m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_TREATWARNING)) >= 0) || (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_MIMICSDESCRIPTIONFILES) && m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_TREATWARNING)) >= 0)) ? ((SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_GETCOUNT) > 0) ? TRUE : FALSE) : FALSE);
	return((SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CCompileOptionsDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_COMPILE_OPTIONS_COMPILER_FILENAME, (bCheck = CheckDatabasePrivilege(DATABASE_PRIVILEGE_COMPILEOPTIONS_CHANGE)));
	AccessControl(IDC_COMPILE_OPTIONS_LINKER_FILENAME, bCheck);
	AccessControl(IDC_COMPILE_OPTIONS_PLATFORM, bCheck);
	AccessControl(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY, bCheck);
	AccessControl(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY, bCheck);
	AccessControl(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, bCheck);
	AccessControl(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, bCheck);
	AccessControl(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS, bCheck);
	GetDlgItem(IDC_COMPILE_OPTIONS_COMPILER_FILENAME_BROWSE)->EnableWindow(bCheck);
	GetDlgItem(IDC_COMPILE_OPTIONS_LINKER_FILENAME_BROWSE)->EnableWindow(bCheck);
	GetDlgItem(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY_BROWSE)->EnableWindow(bCheck);
	GetDlgItem(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY_BROWSE)->EnableWindow(bCheck);
}

BOOL CCompileOptionsDialog::IsModified() CONST
{
	INT  nID[3][2];
	INT  nIDs[3][2];

	if (!m_szFileName[0][0].CompareNoCase(m_szFileName[0][1]) && !m_szFileName[1][0].CompareNoCase(m_szFileName[1][1]) && m_szPlatForm[0] == m_szPlatForm[1] && !m_szDirectory[0][0].CompareNoCase(m_szDirectory[0][1]) && !m_szDirectory[1][0].CompareNoCase(m_szDirectory[1][1]))
	{
		for (nID[0][0] = MINCOMPILEROPTIONOPTIMIZATIONTYPE, nIDs[0][0] = MAXCOMPILEROPTIONOPTIMIZATIONTYPE; nID[0][0] <= nIDs[0][0]; nID[0][0]++)
		{
			if (m_szOptions[0][0].Find(STRING(nID[0][0])) >= 0 && m_szOptions[0][1].Find(STRING(nID[0][0])) >= 0) continue;
			if (m_szOptions[0][0].Find(STRING(nID[0][0])) < 0 && m_szOptions[0][1].Find(STRING(nID[0][0])) < 0) continue;
			break;
		}
		for (nID[0][1] = MINCOMPILEROPTIONWARNING, nIDs[0][1] = MAXCOMPILEROPTIONWARNING; nID[0][1] <= nIDs[0][1]; nID[0][1]++)
		{
			if (m_szOptions[0][0].Find(STRING(nID[0][1])) >= 0 && m_szOptions[0][1].Find(STRING(nID[0][1])) >= 0) continue;
			if (m_szOptions[0][0].Find(STRING(nID[0][1])) < 0 && m_szOptions[0][1].Find(STRING(nID[0][1])) < 0) continue;
			break;
		}
		for (nID[1][0] = MINCOMPILEROPTIONOPTIMIZATIONTYPE, nIDs[1][0] = MAXCOMPILEROPTIONOPTIMIZATIONTYPE; nID[1][0] <= nIDs[1][0]; nID[1][0]++)
		{
			if (m_szOptions[1][0].Find(STRING(nID[1][0])) >= 0 && m_szOptions[1][1].Find(STRING(nID[1][0])) >= 0) continue;
			if (m_szOptions[1][0].Find(STRING(nID[1][0])) < 0 && m_szOptions[1][1].Find(STRING(nID[1][0])) < 0) continue;
			break;
		}
		for (nID[1][1] = MINCOMPILEROPTIONWARNING, nIDs[1][1] = MAXCOMPILEROPTIONWARNING; nID[1][1] <= nIDs[1][1]; nID[1][1]++)
		{
			if (m_szOptions[1][0].Find(STRING(nID[1][1])) >= 0 && m_szOptions[1][1].Find(STRING(nID[1][1])) >= 0) continue;
			if (m_szOptions[1][0].Find(STRING(nID[1][1])) < 0 && m_szOptions[1][1].Find(STRING(nID[1][1])) < 0) continue;
			break;
		}
		for (nID[2][0] = MINCOMPILEROPTIONOPTIMIZATIONTYPE, nIDs[2][0] = MAXCOMPILEROPTIONOPTIMIZATIONTYPE; nID[2][0] <= nIDs[2][0]; nID[2][0]++)
		{
			if (m_szOptions[2][0].Find(STRING(nID[2][0])) >= 0 && m_szOptions[2][1].Find(STRING(nID[2][0])) >= 0) continue;
			if (m_szOptions[2][0].Find(STRING(nID[2][0])) < 0 && m_szOptions[2][1].Find(STRING(nID[2][0])) < 0) continue;
			break;
		}
		for (nID[2][1] = MINCOMPILEROPTIONWARNING, nIDs[2][1] = MAXCOMPILEROPTIONWARNING; nID[2][1] <= nIDs[2][1]; nID[2][1]++)
		{
			if (m_szOptions[2][0].Find(STRING(nID[2][1])) >= 0 && m_szOptions[2][1].Find(STRING(nID[2][1])) >= 0) continue;
			if (m_szOptions[2][0].Find(STRING(nID[2][1])) < 0 && m_szOptions[2][1].Find(STRING(nID[2][1])) < 0) continue;
			break;
		}
		return((nID[0][0] <= nIDs[0][0] || nID[0][1] <= nIDs[0][1] || nID[1][0] <= nIDs[1][0] || nID[1][1] <= nIDs[1][1] || nID[2][0] <= nIDs[2][0] || nID[2][1] <= nIDs[2][1]) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CCompileOptionsDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_COMPILE_OPTIONS_COMPILER_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_COMPILE_OPTIONS_LINKER_FILENAME)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void CCompileOptionsDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompileOptionsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCompileOptionsDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CCompileOptionsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_COMPILE_OPTIONS_PLATFORM, OnPlatForm)
	ON_BN_CLICKED(IDC_COMPILE_OPTIONS_COMPILER_FILENAME_BROWSE, OnBrowseCompilerFiles)
	ON_BN_CLICKED(IDC_COMPILE_OPTIONS_LINKER_FILENAME_BROWSE, OnBrowseLinkerFiles)
	ON_BN_CLICKED(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY_BROWSE, OnBrowseIncludeDirectory)
	ON_BN_CLICKED(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY_BROWSE, OnBrowseLibraryDirectory)
	ON_BN_CLICKED(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS, OnTreatWarningsAsError)
	ON_BN_CLICKED(IDC_COMPILE_OPTIONS_HELP, OnHelp)
	ON_EN_CHANGE(IDC_COMPILE_OPTIONS_COMPILER_FILENAME, OnEditchangeCompilerFileName)
	ON_EN_CHANGE(IDC_COMPILE_OPTIONS_LINKER_FILENAME, OnEditchangeLinkerFileName)
	ON_EN_CHANGE(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY, OnEditchangeIncludeDirectory)
	ON_EN_CHANGE(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY, OnEditchangeLibraryDirectory)
	ON_CBN_SELCHANGE(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT, OnSelchangeCompilationUnit)
	ON_CBN_SELCHANGE(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, OnSelchangeOptimization)
	ON_CBN_SELCHANGE(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, OnSelchangeWarningLevel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompileOptionsDialog message handlers

BOOL CCompileOptionsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	if (EnumCompilationUnits() && EnumOptimizationsOptions() && EnumWarningsOptions())
	{
		CheckDlgButton(IDC_COMPILE_OPTIONS_PLATFORM, (m_szPlatForm[0] == STRING(IDS_COMPILER_PLATFORM_32BIT)) ? TRUE : FALSE);
		GetDlgItem(IDC_COMPILE_OPTIONS_COMPILER_FILENAME)->SetWindowText(m_szFileName[0][0]);
		GetDlgItem(IDC_COMPILE_OPTIONS_LINKER_FILENAME)->SetWindowText(m_szFileName[1][0]);
		GetDlgItem(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY)->SetWindowText(m_szDirectory[0][0]);
		GetDlgItem(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY)->SetWindowText(m_szDirectory[1][0]);
		GetDlgItem(IDC_COMPILE_OPTIONS_DETAILS)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_COMPILER_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_COMPILER_FILENAME)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_LINKER_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_LINKER_FILENAME)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_PLATFORM_STATIC)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_PLATFORM)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY_STATIC)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY_STATIC)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT_STATIC)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS_STATIC)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL_STATIC)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL)->EnableWindow();
		GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS)->EnableWindow();
	}
	AdjustToPrivileges();
	return TRUE;
}

void CCompileOptionsDialog::OnPlatForm()
{
	m_szPlatForm[0] = (!IsDlgButtonChecked(IDC_COMPILE_OPTIONS_PLATFORM)) ? STRING(IDS_COMPILER_PLATFORM_64BIT) : STRING(IDS_COMPILER_PLATFORM_32BIT);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnBrowseCompilerFiles()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_COMPILE_OPTIONS_COMPILER_FILENAME, STRING(IDS_FILEBROWSEDIALOG_EXECUTABLEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_EXECUTABLEFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_COMPILE_OPTIONS_COMPILER_FILENAME)->SetWindowText((m_szFileName[0][0] = cFileBrowseDialog.GetPathName()));
	SendDlgItemMessage(IDC_COMPILE_OPTIONS_COMPILER_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_COMPILE_OPTIONS_COMPILER_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnBrowseLinkerFiles()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_COMPILE_OPTIONS_LINKER_FILENAME, STRING(IDS_FILEBROWSEDIALOG_EXECUTABLEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_EXECUTABLEFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_COMPILE_OPTIONS_LINKER_FILENAME)->SetWindowText((m_szFileName[1][0] = cFileBrowseDialog.GetPathName()));
	SendDlgItemMessage(IDC_COMPILE_OPTIONS_LINKER_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_COMPILE_OPTIONS_LINKER_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnBrowseIncludeDirectory()
{
	LPMALLOC  pIMalloc;
	LPITEMIDLIST  pItemIDList;
	TCHAR  szItemBuffer[MAX_PATH];
	TCHAR  szDisplayName[MAX_PATH];
	BROWSEINFO  sBrowseInfo = { 0 };

	if (SHGetMalloc(&pIMalloc) == NOERROR)
	{
		sBrowseInfo.hwndOwner = GetSafeHwnd();
		sBrowseInfo.pszDisplayName = szDisplayName;
		sBrowseInfo.lpszTitle = STRING(IDS_DIRECTORYBROWSEDIALOG_TITLE);
		if ((pItemIDList = SHBrowseForFolder(&sBrowseInfo)))
		{
			if (SHGetPathFromIDList(pItemIDList, szItemBuffer))
			{
				m_szDirectory[0][0] = szItemBuffer;
				GetDlgItem(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY)->SetWindowText(szItemBuffer);
			}
			pIMalloc->Free(pItemIDList);
		}
		pIMalloc->Release();
	}
	SendDlgItemMessage(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnBrowseLibraryDirectory()
{
	LPMALLOC  pIMalloc;
	LPITEMIDLIST  pItemIDList;
	TCHAR  szItemBuffer[MAX_PATH];
	TCHAR  szDisplayName[MAX_PATH];
	BROWSEINFO  sBrowseInfo = { 0 };

	if (SHGetMalloc(&pIMalloc) == NOERROR)
	{
		sBrowseInfo.hwndOwner = GetSafeHwnd();
		sBrowseInfo.pszDisplayName = szDisplayName;
		sBrowseInfo.lpszTitle = STRING(IDS_DIRECTORYBROWSEDIALOG_TITLE);
		if ((pItemIDList = SHBrowseForFolder(&sBrowseInfo)))
		{
			if (SHGetPathFromIDList(pItemIDList, szItemBuffer))
			{
				m_szDirectory[1][0] = szItemBuffer;
				GetDlgItem(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY)->SetWindowText(szItemBuffer);
			}
			pIMalloc->Free(pItemIDList);
		}
		pIMalloc->Release();
	}
	SendDlgItemMessage(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnTreatWarningsAsError()
{
	INT  nPos;
	CString  szCompilationUnit;

	GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT)->GetWindowText(szCompilationUnit);
	if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_DERIVEDPARAMETERS))
	{
		if ((nPos = m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_TREATWARNING))) >= 0) m_szOptions[0][0] = (!IsDlgButtonChecked(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS)) ? (m_szOptions[0][0].Left(nPos) + m_szOptions[0][0].Mid(nPos + lstrlen(STRING(IDS_COMPILER_OPTION_TREATWARNING)))) : m_szOptions[0][0];
		else  m_szOptions[0][0] = (IsDlgButtonChecked(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS)) ? (m_szOptions[0][0] + STRING(IDS_COMPILER_OPTION_TREATWARNING)) : m_szOptions[0][0];
	}
	if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_MIMICSDESCRIPTIONFILES))
	{
		if ((nPos = m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_TREATWARNING))) >= 0) m_szOptions[1][0] = (!IsDlgButtonChecked(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS)) ? (m_szOptions[1][0].Left(nPos) + m_szOptions[1][0].Mid(nPos + lstrlen(STRING(IDS_COMPILER_OPTION_TREATWARNING)))) : m_szOptions[1][0];
		else  m_szOptions[1][0] = (IsDlgButtonChecked(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS)) ? (m_szOptions[1][0] + STRING(IDS_COMPILER_OPTION_TREATWARNING)) : m_szOptions[1][0];
	}
	if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_TELECOMMANDPROCEDURES))
	{
		if ((nPos = m_szOptions[2][0].Find(STRING(IDS_COMPILER_OPTION_TREATWARNING))) >= 0) m_szOptions[2][0] = (!IsDlgButtonChecked(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS)) ? (m_szOptions[2][0].Left(nPos) + m_szOptions[2][0].Mid(nPos + lstrlen(STRING(IDS_COMPILER_OPTION_TREATWARNING)))) : m_szOptions[2][0];
		else  m_szOptions[2][0] = (IsDlgButtonChecked(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS)) ? (m_szOptions[2][0] + STRING(IDS_COMPILER_OPTION_TREATWARNING)) : m_szOptions[2][0];
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnEditchangeCompilerFileName()
{
	GetDlgItem(IDC_COMPILE_OPTIONS_COMPILER_FILENAME)->GetWindowText(m_szFileName[0][0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnEditchangeLinkerFileName()
{
	GetDlgItem(IDC_COMPILE_OPTIONS_LINKER_FILENAME)->GetWindowText(m_szFileName[1][0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnEditchangeIncludeDirectory()
{
	GetDlgItem(IDC_COMPILE_OPTIONS_INCLUDE_DIRECTORY)->GetWindowText(m_szDirectory[0][0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnEditchangeLibraryDirectory()
{
	GetDlgItem(IDC_COMPILE_OPTIONS_LIBRARY_DIRECTORY)->GetWindowText(m_szDirectory[1][0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnSelchangeCompilationUnit()
{
	CString  szCompilationUnit;

	GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT)->GetWindowText(szCompilationUnit);
	if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_DERIVEDPARAMETERS))
	{
		SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_FINDSTRINGEXACT, (WPARAM)-1, (m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_NONE)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_NONE) : ((m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_DEFAULT) : ((m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_SPEED)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_SPEED) : ((m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_SIZE)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_SIZE) : (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_DEFAULT))))));
		SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_FINDSTRINGEXACT, (WPARAM)-1, (m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_WARNING0)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING0) : ((m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_WARNING1)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING1) : ((m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_WARNING2)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING2) : (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING3)))));
		CheckDlgButton(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS, (m_szOptions[0][0].Find(STRING(IDS_COMPILER_OPTION_TREATWARNING)) >= 0) ? TRUE : FALSE);
	}
	if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_MIMICSDESCRIPTIONFILES))
	{
		SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_FINDSTRINGEXACT, (WPARAM)-1, (m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_NONE)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_NONE) : ((m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_DEFAULT) : ((m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_SPEED)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_SPEED) : ((m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_SIZE)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_SIZE) : (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_DEFAULT))))));
		SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_FINDSTRINGEXACT, (WPARAM)-1, (m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_WARNING0)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING0) : ((m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_WARNING1)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING1) : ((m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_WARNING2)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING2) : (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING3)))));
		CheckDlgButton(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS, (m_szOptions[1][0].Find(STRING(IDS_COMPILER_OPTION_TREATWARNING)) >= 0) ? TRUE : FALSE);
	}
	if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_TELECOMMANDPROCEDURES))
	{
		SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS, CB_FINDSTRINGEXACT, (WPARAM)-1, (m_szOptions[2][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_NONE)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_NONE) : ((m_szOptions[2][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_DEFAULT) : ((m_szOptions[2][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_SPEED)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_SPEED) : ((m_szOptions[2][0].Find(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_SIZE)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_SIZE) : (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_OPTIMIZATION_DEFAULT))))));
		SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL, CB_FINDSTRINGEXACT, (WPARAM)-1, (m_szOptions[2][0].Find(STRING(IDS_COMPILER_OPTION_WARNING0)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING0) : ((m_szOptions[2][0].Find(STRING(IDS_COMPILER_OPTION_WARNING1)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING1) : ((m_szOptions[2][0].Find(STRING(IDS_COMPILER_OPTION_WARNING2)) >= 0) ? (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING2) : (LPARAM)STRING(IDS_COMPILEOPTIONSDIALOG_WARNING3)))));
		CheckDlgButton(IDC_COMPILE_OPTIONS_DIRECTIVES_TREATWARNINGS, (m_szOptions[2][0].Find(STRING(IDS_COMPILER_OPTION_TREATWARNING)) >= 0) ? TRUE : FALSE);
	}
}

void CCompileOptionsDialog::OnSelchangeOptimization()
{
	INT  nID;
	INT  nIDs;
	INT  nPos;
	CString  szOption[2];
	CString  szCompilationUnit;

	GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_OPTIMIZATIONS)->GetWindowText(szOption[0]);
	GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT)->GetWindowText(szCompilationUnit);
	for (nID = MINCOMPILEOPTIONSOPTIMIZATIONTYPE, nIDs = MAXCOMPILEOPTIONSOPTIMIZATIONTYPE; nID <= nIDs && szOption[1].IsEmpty(); nID++)
	{
		szOption[1] = (szOption[0] == STRING(nID)) ? STRING(MINCOMPILEROPTIONOPTIMIZATIONTYPE + nID - MINCOMPILEOPTIONSOPTIMIZATIONTYPE) : (LPCTSTR)szOption[1];
		continue;
	}
	for (nID = MINCOMPILEROPTIONOPTIMIZATIONTYPE, nIDs = MAXCOMPILEROPTIONOPTIMIZATIONTYPE; nID <= nIDs; nID++)
	{
		if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_DERIVEDPARAMETERS))
		{
			if ((nPos = m_szOptions[0][0].Find(STRING(nID))) >= 0)
			{
				m_szOptions[0][0] = m_szOptions[0][0].Left(nPos) + szOption[1] + m_szOptions[0][0].Mid(nPos + lstrlen(STRING(nID)));
				break;
			}
		}
		if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_MIMICSDESCRIPTIONFILES))
		{
			if ((nPos = m_szOptions[1][0].Find(STRING(nID))) >= 0)
			{
				m_szOptions[1][0] = m_szOptions[1][0].Left(nPos) + szOption[1] + m_szOptions[1][0].Mid(nPos + lstrlen(STRING(nID)));
				break;
			}
		}
		if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_TELECOMMANDPROCEDURES))
		{
			if ((nPos = m_szOptions[2][0].Find(STRING(nID))) >= 0)
			{
				m_szOptions[2][0] = m_szOptions[2][0].Left(nPos) + szOption[1] + m_szOptions[2][0].Mid(nPos + lstrlen(STRING(nID)));
				break;
			}
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnSelchangeWarningLevel()
{
	INT  nID;
	INT  nIDs;
	INT  nPos;
	CString  szOption[2];
	CString  szCompilationUnit;

	GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_WARNINGLEVEL)->GetWindowText(szOption[0]);
	GetDlgItem(IDC_COMPILE_OPTIONS_DIRECTIVES_COMPILATIONUNIT)->GetWindowText(szCompilationUnit);
	for (nID = MINCOMPILEOPTIONSWARNING, nIDs = MAXCOMPILEOPTIONSWARNING; nID <= nIDs; nID++)
	{
		szOption[1] = (szOption[0] == STRING(nID)) ? STRING(MINCOMPILEROPTIONWARNING + nID - MINCOMPILEOPTIONSWARNING) : (LPCTSTR)szOption[1];
		continue;
	}
	for (nID = MINCOMPILEROPTIONWARNING, nIDs = MAXCOMPILEROPTIONWARNING; nID <= nIDs; nID++)
	{
		if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_DERIVEDPARAMETERS))
		{
			if ((nPos = m_szOptions[0][0].Find(STRING(nID))) >= 0 && nID != IDS_COMPILER_OPTION_TREATWARNING)
			{
				m_szOptions[0][0] = m_szOptions[0][0].Left(nPos) + szOption[1] + m_szOptions[0][0].Mid(nPos + lstrlen(STRING(nID)));
				break;
			}
		}
		if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_MIMICSDESCRIPTIONFILES))
		{
			if ((nPos = m_szOptions[1][0].Find(STRING(nID))) >= 0 && nID != IDS_COMPILER_OPTION_TREATWARNING)
			{
				m_szOptions[1][0] = m_szOptions[1][0].Left(nPos) + szOption[1] + m_szOptions[1][0].Mid(nPos + lstrlen(STRING(nID)));
				break;
			}
		}
		if (szCompilationUnit == STRING(IDS_COMPILEOPTIONSDIALOG_COMPILATIONUNIT_TELECOMMANDPROCEDURES))
		{
			if ((nPos = m_szOptions[2][0].Find(STRING(nID))) >= 0 && nID != IDS_COMPILER_OPTION_TREATWARNING)
			{
				m_szOptions[2][0] = m_szOptions[2][0].Left(nPos) + szOption[1] + m_szOptions[2][0].Mid(nPos + lstrlen(STRING(nID)));
				break;
			}
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CCompileOptionsDialog::OnOK()
{
	CProfile  cProfile;
	CHourglassCursor  cCursor;

	cProfile.SetCompileOptions(m_szFileName[0][0], m_szFileName[1][0], m_szPlatForm[0], m_szDirectory[0][0], m_szDirectory[1][0], m_szOptions[0][0], m_szOptions[1][0], m_szOptions[2][0]);
	CLocaleDialog::OnOK();
}

BOOL CCompileOptionsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_COMPILEOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CCompileOptionsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_COMPILEOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsLoggingPage property page

IMPLEMENT_DYNCREATE(CToolsOptionsLoggingPage, CLocalePropertyPage)

CToolsOptionsLoggingPage::CToolsOptionsLoggingPage() : CLocalePropertyPage(CToolsOptionsLoggingPage::IDD)
{
	//{{AFX_DATA_INIT(CToolsOptionsLoggingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CToolsOptionsLoggingPage::Initialize()
{
	m_cDatabaseInfo[0].SetName(GetDatabase()->GetName());
	m_cDatabaseInfo[0].SetLoggingMode(GetDatabase()->GetLoggingMode());
	m_cDatabaseInfo[0].SetLoggingPolicy(GetDatabase()->GetLoggingPolicy());
	m_cDatabaseInfo[0].SetLoggingRetentionBySize(GetDatabase()->GetLoggingRetentionBySize());
	m_cDatabaseInfo[0].SetLoggingRetentionByTime(GetDatabase()->GetLoggingRetentionByTime());
	m_cDatabaseInfo[0].SetLoggingFileName(GetDatabase()->GetLoggingFileName());
	m_cDatabaseInfo[1].Copy(&m_cDatabaseInfo[0]);
	return TRUE;
}

VOID CToolsOptionsLoggingPage::SetLoggingInformation(CONST CDatabaseProfileInfo *pDatabaseInfo)
{
	m_cDatabaseInfo[0].Copy(pDatabaseInfo);
	ShowLoggingInformation();
}

VOID CToolsOptionsLoggingPage::GetLoggingInformation(CDatabaseProfileInfo *pDatabaseInfo) CONST
{
	pDatabaseInfo->SetLoggingMode(m_cDatabaseInfo[0].GetLoggingMode());
	pDatabaseInfo->SetLoggingPolicy(m_cDatabaseInfo[0].GetLoggingPolicy());
	pDatabaseInfo->SetLoggingFileName(m_cDatabaseInfo[0].GetLoggingFileName());
	pDatabaseInfo->SetLoggingRetentionBySize(m_cDatabaseInfo[0].GetLoggingRetentionBySize());
	pDatabaseInfo->SetLoggingRetentionByTime(m_cDatabaseInfo[0].GetLoggingRetentionByTime());
}

VOID CToolsOptionsLoggingPage::ShowLoggingInformation()
{
	Spinbox_SetPos(GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS), m_cDatabaseInfo[0].GetLoggingRetentionByTime().GetTotalSeconds() / SECONDSPERDAY);
	Spinbox_SetPos(GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM), m_cDatabaseInfo[0].GetLoggingRetentionBySize() / 1024);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OVERWRITE, ((m_cDatabaseInfo[0].GetLoggingMode() & LOGFILE_POLICY_CYCLICMODE) && (m_cDatabaseInfo[0].GetLoggingPolicy() & LOGFILE_POLICY_RETENTIONBYTIME) != LOGFILE_POLICY_RETENTIONBYTIME) ? TRUE : FALSE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OLDOVERWRITE, ((m_cDatabaseInfo[0].GetLoggingMode() & LOGFILE_POLICY_CYCLICMODE) && (m_cDatabaseInfo[0].GetLoggingPolicy() & LOGFILE_POLICY_RETENTIONBYTIME)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_NOOVERWRITE, (m_cDatabaseInfo[0].GetLoggingMode() & LOGFILE_POLICY_NONCYCLICMODE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_UNLIMITED, ((m_cDatabaseInfo[0].GetLoggingPolicy() & LOGFILE_POLICY_RETENTIONBYSIZE) != LOGFILE_POLICY_RETENTIONBYSIZE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_LIMITED, (m_cDatabaseInfo[0].GetLoggingPolicy() & LOGFILE_POLICY_RETENTIONBYSIZE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_DISABLED, (m_cDatabaseInfo[0].GetLoggingPolicy() & LOGFILE_POLICY_DISABLED) ? TRUE : FALSE);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_DATABASE)->SetWindowText(m_cDatabaseInfo[0].GetName());
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME)->SetWindowText(m_cDatabaseInfo[0].GetLoggingFileName());
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OLDOVERWRITE));
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS)->EnableWindow(IsDlgButtonChecked(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OLDOVERWRITE));
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_LIMITED));
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM)->EnableWindow(IsDlgButtonChecked(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_LIMITED));
}

VOID CToolsOptionsLoggingPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_BROWSE)->EnableWindow((bCheck = CheckDatabasePrivilege(DATABASE_PRIVILEGE_LOGFILES_CHANGE)));
	AccessControl(IDC_TOOLSOPTIONS_LOGGINGPAGE_DISABLED, bCheck);
	AccessControl(IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME, bCheck);
	AccessControl(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OVERWRITE, bCheck);
	AccessControl(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OLDOVERWRITE, bCheck);
	AccessControl(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS, bCheck);
	AccessControl(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_NOOVERWRITE, bCheck);
	AccessControl(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_UNLIMITED, bCheck);
	AccessControl(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_LIMITED, bCheck);
	AccessControl(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM, bCheck);
	AccessControl(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_RESET, bCheck);
}

BOOL CToolsOptionsLoggingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_cDatabaseInfo[0].Compare(&m_cDatabaseInfo[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CToolsOptionsLoggingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME)->GetWindowTextLength() > 0) : CLocalePropertyPage::Check()) : TRUE);
}

void CToolsOptionsLoggingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolsOptionsLoggingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CToolsOptionsLoggingPage::PostNcDestroy()
{
	CDatabaseProfileInfo  cDatabaseInfo;

	m_cDatabaseInfo[0].Copy(&cDatabaseInfo);
	m_cDatabaseInfo[1].Copy(&cDatabaseInfo);
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CToolsOptionsLoggingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CToolsOptionsLoggingPage)
	ON_BN_CLICKED(IDC_TOOLSOPTIONS_LOGGINGPAGE_BROWSE, OnBrowseFilename)
	ON_BN_CLICKED(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OVERWRITE, OnOverwriteLogs)
	ON_BN_CLICKED(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OLDOVERWRITE, OnOverwriteOldLogs)
	ON_BN_CLICKED(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_NOOVERWRITE, OnOverwriteNoLogs)
	ON_BN_CLICKED(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_UNLIMITED, OnUnlimitedSize)
	ON_BN_CLICKED(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_LIMITED, OnLimitedSize)
	ON_BN_CLICKED(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_RESET, OnResetSize)
	ON_BN_CLICKED(IDC_TOOLSOPTIONS_LOGGINGPAGE_DISABLED, OnDisabled)
	ON_CONTROL(SBXN_CHANGE, IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS, OnSpinchangeDays)
	ON_CONTROL(SBXN_CHANGE, IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM, OnSpinchangeSize)
	ON_EN_CHANGE(IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME, OnEditchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsLoggingPage message handlers

BOOL CToolsOptionsLoggingPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS), TOOLSOPTIONSLOGGING_MINIMUMDAYS, TOOLSOPTIONSLOGGING_MAXIMUMDAYS);
	Spinbox_SetRange(GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM), TOOLSOPTIONSLOGGING_MINIMUMSIZE, TOOLSOPTIONSLOGGING_MAXIMUMSIZE);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_DATABASE)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_DISABLED)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_BROWSE)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OVERWRITE)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OLDOVERWRITE)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_NOOVERWRITE)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_UNLIMITED)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_LIMITED)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_RESET)->EnableWindow();
	ShowLoggingInformation();
	AdjustToPrivileges();
	return TRUE;
}

void CToolsOptionsLoggingPage::OnBrowseFilename()
{
	CFileBrowseDialog  cFileBrowseDialog(this, m_cDatabaseInfo[0].GetLoggingFileName(), STRING(IDS_FILEBROWSEDIALOG_LOGFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_LOGFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		m_cDatabaseInfo[0].SetLoggingFileName(cFileBrowseDialog.GetPathName());
		GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	}
	SendDlgItemMessage(IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CToolsOptionsLoggingPage::OnOverwriteLogs()
{
	m_cDatabaseInfo[0].SetLoggingPolicy((m_cDatabaseInfo[0].GetLoggingPolicy() & LOGFILE_POLICY_RETENTIONBYSIZE) | LOGFILE_POLICY_CYCLICMODE);
	m_cDatabaseInfo[0].SetLoggingRetentionByTime(CTimeSpan(0));
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OVERWRITE, TRUE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OLDOVERWRITE, FALSE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_NOOVERWRITE, FALSE);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CToolsOptionsLoggingPage::OnOverwriteOldLogs()
{
	m_cDatabaseInfo[0].SetLoggingPolicy((m_cDatabaseInfo[0].GetLoggingPolicy() & LOGFILE_POLICY_RETENTIONBYSIZE) | LOGFILE_POLICY_CYCLICMODE | LOGFILE_POLICY_RETENTIONBYTIME);
	m_cDatabaseInfo[0].SetLoggingRetentionByTime(CTimeSpan(SECONDSPERDAY*TOOLSOPTIONSLOGGING_DEFAULTDAYS));
	Spinbox_SetPos(GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS), TOOLSOPTIONSLOGGING_DEFAULTDAYS);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OVERWRITE, FALSE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OLDOVERWRITE, TRUE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_NOOVERWRITE, FALSE);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CToolsOptionsLoggingPage::OnOverwriteNoLogs()
{
	m_cDatabaseInfo[0].SetLoggingPolicy((m_cDatabaseInfo[0].GetLoggingPolicy() & LOGFILE_POLICY_RETENTIONBYSIZE) | LOGFILE_POLICY_NONCYCLICMODE);
	m_cDatabaseInfo[0].SetLoggingRetentionByTime(CTimeSpan(0));
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OVERWRITE, FALSE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_OLDOVERWRITE, FALSE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_NOOVERWRITE, TRUE);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CToolsOptionsLoggingPage::OnUnlimitedSize()
{
	m_cDatabaseInfo[0].SetLoggingPolicy(m_cDatabaseInfo[0].GetLoggingPolicy() & ~LOGFILE_POLICY_RETENTIONBYSIZE);
	m_cDatabaseInfo[0].SetLoggingRetentionBySize((DWORDLONG)0);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_UNLIMITED, TRUE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_LIMITED, FALSE);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CToolsOptionsLoggingPage::OnLimitedSize()
{
	m_cDatabaseInfo[0].SetLoggingPolicy(m_cDatabaseInfo[0].GetLoggingPolicy() | LOGFILE_POLICY_RETENTIONBYSIZE);
	m_cDatabaseInfo[0].SetLoggingRetentionBySize((DWORDLONG)(1024 * TOOLSOPTIONSLOGGING_DEFAULTSIZE));
	Spinbox_SetPos(GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM), TOOLSOPTIONSLOGGING_DEFAULTSIZE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_UNLIMITED, FALSE);
	CheckDlgButton(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_LIMITED, TRUE);
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM_STATIC)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM)->EnableWindow();
	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CToolsOptionsLoggingPage::OnResetSize()
{
	m_cDatabaseInfo[0].SetLoggingPolicy((IsDlgButtonChecked(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_RESET)) ? (m_cDatabaseInfo[0].GetLoggingPolicy() | LOGFILE_POLICY_RESET) : (m_cDatabaseInfo[0].GetLoggingPolicy() & ~LOGFILE_POLICY_RESET));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CToolsOptionsLoggingPage::OnDisabled()
{
	m_cDatabaseInfo[0].SetLoggingPolicy((IsDlgButtonChecked(IDC_TOOLSOPTIONS_LOGGINGPAGE_DISABLED)) ? (m_cDatabaseInfo[0].GetLoggingPolicy() | LOGFILE_POLICY_DISABLED) : (m_cDatabaseInfo[0].GetLoggingPolicy() & ~LOGFILE_POLICY_DISABLED));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CToolsOptionsLoggingPage::OnSpinchangeDays()
{
	m_cDatabaseInfo[0].SetLoggingRetentionByTime(SECONDSPERDAY*Spinbox_GetPos(GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_POLICY_DAYS)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CToolsOptionsLoggingPage::OnSpinchangeSize()
{
	m_cDatabaseInfo[0].SetLoggingRetentionBySize(1024 * Spinbox_GetPos(GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_SIZE_MAXIMUM)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CToolsOptionsLoggingPage::OnEditchangeFileName()
{
	CString  szFileName;

	GetDlgItem(IDC_TOOLSOPTIONS_LOGGINGPAGE_FILENAME)->GetWindowText(szFileName);
	m_cDatabaseInfo[0].SetLoggingFileName(szFileName);
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsTabCtrl

IMPLEMENT_DYNCREATE(CToolsOptionsTabCtrl, CTabCtrl)

CToolsOptionsDialog *CToolsOptionsTabCtrl::GetParent() CONST
{
	return((CToolsOptionsDialog *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CToolsOptionsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CToolsOptionsTabCtrl)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsTabCtrl message handlers

void CToolsOptionsTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nTab;

	if ((nChar == VK_LEFT  &&  GetCurSel() > 0) || (nChar == VK_RIGHT  &&  GetCurSel() < GetItemCount() - 1))
	{
		if ((nTab = (nChar == VK_LEFT) ? (GetCurSel() - 1) : (GetCurSel() + 1)) >= 0)
		{
			GetParent()->SetActivePage(nTab);
			return;
		}
	}
	CTabCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CToolsOptionsTabCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	CTabCtrl::OnLButtonDown(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsDialog

IMPLEMENT_DYNCREATE(CToolsOptionsDialog, CLocalePropertySheetDialog)

CToolsOptionsDialog::CToolsOptionsDialog(CWnd *pParentWnd) : CLocalePropertySheetDialog(STRING(IDS_TOOLSOPTIONSDIALOG_TITLE), pParentWnd)
{
	AddPage(&m_pageLogging);
}

BEGIN_MESSAGE_MAP(CToolsOptionsDialog, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CToolsOptionsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolsOptionsDialog message handlers

BOOL CToolsOptionsDialog::OnInitDialog()
{
	CTabCtrl  *pTabCtrl;
	CHourglassCursor  cCursor;

	CLocalePropertySheetDialog::OnInitDialog();
	if ((pTabCtrl = GetTabControl()) && IsWindow(pTabCtrl->GetSafeHwnd()))
	{
		m_wndTabCtrl.SubclassWindow(pTabCtrl->GetSafeHwnd());
		m_wndTabCtrl.SetFocus();
		return FALSE;
	}
	return TRUE;
}

void CToolsOptionsDialog::OnOK()
{
	INT  nDatabase;
	INT  nDatabases;
	CLogFile  cLogFile;
	CDatabases  cDatabases;
	CDatabaseProfiles  pDatabases;
	CDatabaseProfileInfo  cDatabaseInfo;
	CDatabaseProfileInfo  *pDatabaseInfo;
	CHourglassCursor  cCursor;

	for (cDatabases.SetComputerName(GetDatabase()->GetServer()), m_pageLogging.GetLoggingInformation(&cDatabaseInfo); cDatabaseInfo.GetLoggingPolicy() & LOGFILE_POLICY_RESET; )
	{
		for (cDatabaseInfo.SetLoggingPolicy(cDatabaseInfo.GetLoggingPolicy() & ~LOGFILE_POLICY_RESET); GetDatabase()->ResetLog(); )
		{
			GetMainWnd()->GetWorkspaceWindow()->UpdateDatabaseLogs();
			break;
		}
		break;
	}
	for (nDatabase = 0, nDatabases = cDatabases.GetDatabases(pDatabases), GetDatabase()->SetLoggingMode(cDatabaseInfo.GetLoggingMode()), GetDatabase()->SetLoggingPolicy(cDatabaseInfo.GetLoggingPolicy()), GetDatabase()->SetLoggingRetentionBySize(cDatabaseInfo.GetLoggingRetentionBySize()), GetDatabase()->SetLoggingRetentionByTime(cDatabaseInfo.GetLoggingRetentionByTime()), GetDatabase()->SetLoggingFileName(cDatabaseInfo.GetLoggingFileName()), GetDatabase()->UpdateLog(); nDatabase < nDatabases; nDatabase++)
	{
		if ((pDatabaseInfo = pDatabases.GetAt(nDatabase)) && !pDatabaseInfo->GetServer().CompareNoCase(GetDatabase()->GetServer()) && pDatabaseInfo->GetName() == GetDatabase()->GetName() && pDatabaseInfo->GetSpacecraft() == GetDatabase()->GetSpacecraft())
		{
			pDatabaseInfo->SetLoggingMode(cDatabaseInfo.GetLoggingMode());
			pDatabaseInfo->SetLoggingPolicy(cDatabaseInfo.GetLoggingPolicy());
			pDatabaseInfo->SetLoggingRetentionBySize(cDatabaseInfo.GetLoggingRetentionBySize());
			pDatabaseInfo->SetLoggingRetentionByTime(cDatabaseInfo.GetLoggingRetentionByTime());
			pDatabaseInfo->SetLoggingFileName(cDatabaseInfo.GetLoggingFileName());
			cDatabases.SetDatabases(pDatabases);
			break;
		}
	}
	CLocalePropertySheetDialog::OnOK();
}

BOOL CToolsOptionsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TOOLSOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CToolsOptionsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TOOLSOPTIONSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayWindowsDialog dialog

IMPLEMENT_DYNCREATE(CDisplayWindowsDialog, CLocaleDialog)

CDisplayWindowsDialog::CDisplayWindowsDialog(CWnd *pParentWnd) : CLocaleDialog(CDisplayWindowsDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CDisplayWindowsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDisplayWindowsDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayWindowsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDisplayWindowsDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDisplayWindowsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DISPLAYWINDOWS_HELP, OnHelp)
	ON_LBN_DBLCLK(IDC_DISPLAYWINDOWS_LIST, OnSelectDisplayWindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayWindowsDialog message handlers

BOOL CDisplayWindowsDialog::OnInitDialog()
{
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CString  szDisplayTitle;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)))
		{
			for (pDisplayWnd->GetWindowText(szDisplayTitle); TRUE; )
			{
				SendDlgItemMessage(IDC_DISPLAYWINDOWS_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDisplayTitle);
				break;
			}
		}
	}
	if (SendDlgItemMessage(IDC_DISPLAYWINDOWS_LIST, LB_GETCOUNT) == nDisplays)
	{
		SendDlgItemMessage(IDC_DISPLAYWINDOWS_LIST, LB_SETCURSEL);
		GetDlgItem(IDC_DISPLAYWINDOWS_LIST_STATIC)->EnableWindow();
		GetDlgItem(IDC_DISPLAYWINDOWS_LIST)->EnableWindow();
		GetDlgItem(IDC_DISPLAYWINDOWS_LIST)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow();
		return FALSE;
	}
	SendDlgItemMessage(IDC_DISPLAYWINDOWS_LIST, LB_RESETCONTENT);
	return TRUE;
}

void CDisplayWindowsDialog::OnSelectDisplayWindow()
{
	INT  nIndex;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = ((nIndex = (INT)SendDlgItemMessage(IDC_DISPLAYWINDOWS_LIST, LB_GETCURSEL)) >= 0 && nIndex < EnumDisplayWindows(pDisplays)) ? (CDisplayWnd *)pDisplays.GetAt(nIndex) : (CDisplayWnd *)NULL))
	{
		ActivateDisplayWindow(pDisplayWnd);
		EndDialog(IDOK);
		return;
	}
	EndDialog(IDCANCEL);
}

void CDisplayWindowsDialog::OnOK()
{
	INT  nIndex;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = ((nIndex = (INT)SendDlgItemMessage(IDC_DISPLAYWINDOWS_LIST, LB_GETCURSEL)) >= 0 && nIndex < EnumDisplayWindows(pDisplays)) ? (CDisplayWnd *)pDisplays.GetAt(nIndex) : (CDisplayWnd *)NULL))
	{
		ActivateDisplayWindow(pDisplayWnd);
		EndDialog(IDOK);
		return;
	}
	EndDialog(IDCANCEL);
}

BOOL CDisplayWindowsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DISPLAYWINDOWSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDisplayWindowsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DISPLAYWINDOWSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CUserInterfaceRibbonBarPage

IMPLEMENT_DYNCREATE(CUserInterfaceRibbonBarPage, CLocalePropertyPage)

CUserInterfaceRibbonBarPage::CUserInterfaceRibbonBarPage(CMFCRibbonBar *pRibbonBar) : CLocalePropertyPage(CUserInterfaceRibbonBarPage::IDD), m_wndCommandsList(pRibbonBar), m_wndQATList(pRibbonBar, TRUE, TRUE)
{
	m_pRibbonBar = pRibbonBar;
	m_bQAToolbarOnBottom = m_bQAToolbarBelow = !m_pRibbonBar->IsQuickAccessToolbarOnTop();

	//{{AFX_DATA_INIT(CUserInterfaceRibbonBarPage)
	m_nCategory = -1;
	//}}AFX_DATA_INIT
}

BOOL CUserInterfaceRibbonBarPage::IsModified(BOOL bAll) CONST
{
	INT  nCommand;
	INT  nCommands;
	CMFCRibbonBaseElement  *pCommand;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nCommand = 0, nCommands = m_wndQATList.GetCount(); nCommand < nCommands; nCommand++)
		{
			if ((pCommand = (CMFCRibbonBaseElement *)m_wndQATList.GetItemData(nCommand)) != (CMFCRibbonBaseElement *)NULL)
			{
				if (nCommand >= m_nQATCommandIDs.GetSize() || pCommand->GetID() != m_nQATCommandIDs.GetAt(nCommand)) break;
				continue;
			}
		}
		return((m_wndQATList.GetCount() != m_nQATCommandIDs.GetSize() || nCommand < nCommands || m_bQAToolbarOnBottom != m_bQAToolbarBelow) ? TRUE : FALSE);
	}
	return((bAll) ? CLocalePropertyPage::IsModified() : FALSE);
}

BOOL CUserInterfaceRibbonBarPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

VOID CUserInterfaceRibbonBarPage::Update()
{
	INT  nCommand;
	INT  nCommands;
	CList<UINT, UINT>  lstQACommands;
	CFrameWnd  *pParentFrame;

	if (IsWindow(GetSafeHwnd()))
	{
		for (nCommand = 0, nCommands = m_wndQATList.GetCount(), UpdateData(); nCommand < nCommands; nCommand++)
		{
			lstQACommands.AddTail(m_wndQATList.GetCommand(nCommand)->GetID());
			continue;
		}
		for (m_pRibbonBar->SetQuickAccessCommands(lstQACommands), m_pRibbonBar->SetQuickAccessToolbarOnTop(!m_bQAToolbarOnBottom); pParentFrame = m_pRibbonBar->GetParentFrame(); )
		{
			pParentFrame->RecalcLayout();
			pParentFrame->RedrawWindow();
			break;
		}
	}
}

VOID CUserInterfaceRibbonBarPage::EnumCommands()
{
	INT  nCommand;
	INT  nCommands;
	CString  szCommand;
	CMFCRibbonCategory  *pCategory;
	CMFCRibbonBaseElement  *pCommand;

	for (UpdateData(); (pCategory = (CMFCRibbonCategory *)m_wndCategoryCombo.GetItemData(m_nCategory)); )
	{
		m_wndCommandsList.FillFromCategory(pCategory);
		break;
	}
	for (nCommand = 0, nCommands = m_wndCommandsList.GetCount(); nCommand < nCommands; nCommand++)
	{
		for (m_wndCommandsList.GetText(nCommand, szCommand); nCommand > 0 && _istdigit(szCommand.GetAt(0)); )
		{
			m_wndCommandsList.DeleteString(nCommand);
			nCommands--;
			nCommand--;
			break;
		}
	}
	for (; (pCommand = (!m_nCategory) ? m_pRibbonBar->FindByID(ID_APP_EXIT) : (CMFCRibbonBaseElement *)NULL); )
	{
		pCommand->AddToListBox(&m_wndCommandsList, FALSE);
		break;
	}
	m_wndAdd.EnableWindow(((pCommand = m_wndCommandsList.GetSelected()) && m_wndQATList.GetCommandIndex(pCommand->GetID()) < 0) ? TRUE : FALSE);
}

void CUserInterfaceRibbonBarPage::MoveCommand(BOOL bUp)
{
	INT  nIndex[2];
	CString  szCommand;
	DWORD_PTR  dwCommandData;

	for (nIndex[0] = m_wndQATList.GetCurSel(); nIndex[0] >= 0; )
	{
		for (m_wndQATList.GetText(nIndex[0], szCommand), dwCommandData = m_wndQATList.GetItemData(nIndex[0]); m_wndQATList.DeleteString(nIndex[0]) >= 0; )
		{
			if ((nIndex[1] = m_wndQATList.InsertString((bUp) ? (nIndex[0] - 1) : (nIndex[0] + 1), szCommand)) >= 0)
			{
				m_wndQATList.SetItemData(nIndex[1], dwCommandData);
				m_wndQATList.SetCurSel(nIndex[1]);
			}
			break;
		}
		break;
	}
	m_wndUp.EnableWindow(m_wndQATList.GetCurSel() > 0);
	m_wndDown.EnableWindow(m_wndQATList.GetCurSel() < m_wndQATList.GetCount() - 1);
	m_wndRemove.EnableWindow(m_wndQATList.GetCurSel() >= 0);
}

void CUserInterfaceRibbonBarPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserInterfaceRibbonBarPage)
	DDX_Control(pDX, IDC_USERINTERFACE_RIBBONBARPAGE_CATEGORY, m_wndCategoryCombo);
	DDX_Control(pDX, IDC_USERINTERFACE_RIBBONBARPAGE_COMMANDS, m_wndCommandsList);
	DDX_Control(pDX, IDC_USERINTERFACE_RIBBONBARPAGE_COMMAND_ADD, m_wndAdd);
	DDX_Control(pDX, IDC_USERINTERFACE_RIBBONBARPAGE_COMMAND_REMOVE, m_wndRemove);
	DDX_Control(pDX, IDC_USERINTERFACE_RIBBONBARPAGE_QAT_LIST, m_wndQATList);
	DDX_Control(pDX, IDC_USERINTERFACE_RIBBONBARPAGE_QAT_MOVEUP, m_wndUp);
	DDX_Control(pDX, IDC_USERINTERFACE_RIBBONBARPAGE_QAT_MOVEDOWN, m_wndDown);
	DDX_CBIndex(pDX, IDC_USERINTERFACE_RIBBONBARPAGE_CATEGORY, m_nCategory);
	//}}AFX_DATA_MAP
}

void CUserInterfaceRibbonBarPage::PostNcDestroy()
{
	m_nQATCommandIDs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CUserInterfaceRibbonBarPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CUserInterfaceRibbonBarPage)
	ON_BN_CLICKED(IDC_USERINTERFACE_RIBBONBARPAGE_COMMAND_ADD, OnAddCommand)
	ON_BN_CLICKED(IDC_USERINTERFACE_RIBBONBARPAGE_COMMAND_REMOVE, OnRemoveCommand)
	ON_BN_CLICKED(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_MOVEUP, OnQATCommandUp)
	ON_BN_CLICKED(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_MOVEDOWN, OnQATCommandDown)
	ON_BN_CLICKED(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_RESET, OnQATReset)
	ON_BN_CLICKED(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_BELOW, OnQAToolbarBelow)
	ON_CBN_SELENDOK(IDC_USERINTERFACE_RIBBONBARPAGE_CATEGORY, OnSelendokCategory)
	ON_LBN_SELCHANGE(IDC_USERINTERFACE_RIBBONBARPAGE_COMMANDS, OnSelchangeCommands)
	ON_LBN_SELCHANGE(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_LIST, OnSelchangeQATList)
	ON_LBN_DBLCLK(IDC_USERINTERFACE_RIBBONBARPAGE_COMMANDS, OnAddCommand)
	ON_LBN_DBLCLK(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_LIST, OnRemoveCommand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserInterfaceRibbonBarPage message handlers

BOOL CUserInterfaceRibbonBarPage::OnInitDialog()
{
	INT  nIndex;
	INT  nCategory;
	INT  nCategories;
	POSITION  lPosition;
	CList<UINT, UINT>  lstQACommands;
	CMFCRibbonCategory  *pCategory;

	CLocalePropertyPage::OnInitDialog();
	for (nCategory = 0, nCategories = m_pRibbonBar->GetCategoryCount(), m_wndUp.SetStdImage(CMenuImages::IdArrowUpLarge), m_wndDown.SetStdImage(CMenuImages::IdArrowDownLarge), CheckDlgButton(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_BELOW, m_bQAToolbarOnBottom); nCategory < nCategories; nCategory++)
	{
		if ((pCategory = m_pRibbonBar->GetCategory(nCategory)))
		{
			nIndex = m_wndCategoryCombo.AddString(pCategory->GetName());
			m_wndCategoryCombo.SetItemData(nIndex, (DWORD_PTR)pCategory);
		}
	}
	if (m_wndCategoryCombo.GetCount() > 0)
	{
		m_nCategory = 0;
		UpdateData(FALSE);
		EnumCommands();
	}
	for (m_pRibbonBar->GetQuickAccessCommands(lstQACommands); lstQACommands.GetCount() > 0; )
	{
		for (lPosition = lstQACommands.GetHeadPosition(), m_wndQATList.FillFromIDs(lstQACommands, FALSE); lPosition; )
		{
			m_nQATCommandIDs.Add(lstQACommands.GetNext(lPosition));
			continue;
		}
		m_wndUp.EnableWindow(m_wndQATList.GetCurSel() > 0);
		m_wndDown.EnableWindow(m_wndQATList.GetCurSel() < m_wndQATList.GetCount() - 1);
		m_wndRemove.EnableWindow(m_wndQATList.GetCurSel() >= 0);
		break;
	}
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_CATEGORY_STATIC)->EnableWindow(m_wndCategoryCombo.GetCount() > 0);
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_CATEGORY)->EnableWindow(m_wndCategoryCombo.GetCount() > 0);
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_COMMANDS_STATIC)->EnableWindow(m_wndCommandsList.GetCount() > 0);
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_COMMANDS)->EnableWindow(m_wndCommandsList.GetCount() > 0);
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_COMMAND_ADD)->EnableWindow(m_wndCommandsList.GetCount() > 0 && m_wndCommandsList.GetCurSel() >= 0);
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_COMMAND_REMOVE)->EnableWindow(m_wndQATList.GetCount() > 0 && m_wndQATList.GetCurSel() >= 0);
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_LIST)->EnableWindow(m_wndQATList.GetCount() > 0);
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_MOVEUP)->EnableWindow(m_wndQATList.GetCount() > 0 && m_wndQATList.GetCurSel() > 0);
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_MOVEDOWN)->EnableWindow(m_wndQATList.GetCount() > 0 && m_wndQATList.GetCurSel() < m_wndQATList.GetCount() - 1);
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_RESET)->EnableWindow(m_wndQATList.GetCount() > 0);
	GetDlgItem(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_BELOW)->EnableWindow();
	return TRUE;
}

void CUserInterfaceRibbonBarPage::OnAddCommand()
{
	INT  nIndex;
	CMFCRibbonBaseElement  *pCommand;
	CHourglassCursor  cCursor;

	if ((pCommand = m_wndCommandsList.GetSelected()))
	{
		if (m_wndQATList.AddCommand(pCommand, TRUE, FALSE))
		{
			if ((nIndex = m_wndCommandsList.GetCurSel()) < m_wndCommandsList.GetCount() - 1) m_wndCommandsList.SetCurSel(nIndex + 1);
			EnumCommands();
		}
	}
	m_wndUp.EnableWindow(m_wndQATList.GetCurSel() > 0);
	m_wndDown.EnableWindow(m_wndQATList.GetCurSel() < m_wndQATList.GetCount() - 1);
	m_wndRemove.EnableWindow(m_wndQATList.GetCurSel() >= 0);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CUserInterfaceRibbonBarPage::OnRemoveCommand()
{
	INT  nIndex;
	CMFCRibbonBaseElement  *pCommand;

	if ((nIndex = m_wndQATList.GetCurSel()) >= 0)
	{
		for (m_wndQATList.DeleteString(nIndex); (nIndex = min(nIndex, m_wndQATList.GetCount() - 1)) >= 0; )
		{
			m_wndQATList.SetCurSel(nIndex);
			break;
		}
	}
	m_wndUp.EnableWindow(m_wndQATList.GetCurSel() > 0);
	m_wndDown.EnableWindow(m_wndQATList.GetCurSel() < m_wndQATList.GetCount() - 1);
	m_wndAdd.EnableWindow(((pCommand = m_wndCommandsList.GetSelected()) && m_wndQATList.GetCommandIndex(pCommand->GetID()) < 0) ? TRUE : FALSE);
	m_wndRemove.EnableWindow(m_wndQATList.GetCurSel() >= 0);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CUserInterfaceRibbonBarPage::OnQATCommandUp()
{
	MoveCommand(TRUE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CUserInterfaceRibbonBarPage::OnQATCommandDown()
{
	MoveCommand(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CUserInterfaceRibbonBarPage::OnQATReset()
{
	CList<UINT, UINT>  lstCmds;

	m_wndQATList.FillFromIDs(lstCmds, FALSE);
	m_wndQATList.EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CUserInterfaceRibbonBarPage::OnQAToolbarBelow()
{
	m_bQAToolbarOnBottom = IsDlgButtonChecked(IDC_USERINTERFACE_RIBBONBARPAGE_QAT_BELOW);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CUserInterfaceRibbonBarPage::OnSelendokCategory()
{
	EnumCommands();
}

void CUserInterfaceRibbonBarPage::OnSelchangeCommands()
{
	CMFCRibbonBaseElement  *pCommand;

	m_wndAdd.EnableWindow(((pCommand = m_wndCommandsList.GetSelected()) && m_wndQATList.GetCommandIndex(pCommand->GetID()) < 0) ? TRUE : FALSE);
}

void CUserInterfaceRibbonBarPage::OnSelchangeQATList()
{
	m_wndUp.EnableWindow(m_wndQATList.GetCurSel() > 0);
	m_wndDown.EnableWindow(m_wndQATList.GetCurSel() < m_wndQATList.GetCount() - 1);
	m_wndRemove.EnableWindow(m_wndQATList.GetCurSel() >= 0);
}


/////////////////////////////////////////////////////////////////////////////
// CUserInterfaceKeyboardPage

IMPLEMENT_DYNCREATE(CUserInterfaceKeyboardPage, CLocalePropertyPage)

CUserInterfaceKeyboardPage::CUserInterfaceKeyboardPage(CMFCRibbonBar *pRibbonBar) : CLocalePropertyPage(CUserInterfaceKeyboardPage::IDD), m_wndCommandsList(pRibbonBar, FALSE)
{
	m_pRibbonBar = pRibbonBar;
	m_pParentFrame = m_pRibbonBar->GetTopLevelFrame();
	m_pButton = (CMFCRibbonBaseElement *)NULL;
	m_hAccelTable = (HACCEL)NULL;
	m_pAccel[0] = (LPACCEL)NULL;
	m_pAccel[1] = (LPACCEL)NULL;
	m_pAccel[2] = (LPACCEL)NULL;
	m_nAccelSize[0] = 0;
	m_nAccelSize[1] = 0;

	//{{AFX_DATA_INIT(CUserInterfaceKeyboardPage)
	//}}AFX_DATA_INIT
}

CUserInterfaceKeyboardPage::~CUserInterfaceKeyboardPage()
{
	if (m_pAccel[0] != NULL) delete[] m_pAccel[0];
	if (m_pAccel[1] != NULL) delete[] m_pAccel[1];
}

BOOL CUserInterfaceKeyboardPage::IsModified(BOOL bAll) CONST
{
	INT  nIndex[2];
	INT  nCount[2];

	for (nIndex[0] = 0, nCount[0] = (IsWindow(GetSafeHwnd())) ? ((m_nAccelSize[0] == m_nAccelSize[1]) ? m_nAccelSize[0] : -1) : 0; nIndex[0] < nCount[0]; nIndex[0]++)
	{
		for (nIndex[1] = 0, nCount[1] = m_nAccelSize[1]; nIndex[1] < nCount[1]; nIndex[1]++)
		{
			if (m_pAccel[0][nIndex[0]].cmd == m_pAccel[1][nIndex[1]].cmd) break;
			continue;
		}
		if (nIndex[1] == nCount[1] || m_pAccel[0][nIndex[0]].key != m_pAccel[1][nIndex[1]].key || (m_pAccel[0][nIndex[0]].fVirt & (FCONTROL | FALT | FSHIFT | FVIRTKEY)) != (m_pAccel[1][nIndex[1]].fVirt & (FCONTROL | FALT | FSHIFT | FVIRTKEY))) break;
	}
	return((nIndex[0] != nCount[0]) ? TRUE : FALSE);
}

BOOL CUserInterfaceKeyboardPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

VOID CUserInterfaceKeyboardPage::Update()
{
	return;
}

VOID CUserInterfaceKeyboardPage::EnumCommands()
{
	INT  nIndex;
	INT  nCommand;
	INT  nCommands;
	CString  szCommand;
	CMFCRibbonCategory  *pCategory;

	for (UpdateData(); (pCategory = ((nIndex = m_wndCategoryList.GetCurSel()) >= 0) ? m_pRibbonBar->GetCategory(nIndex) : (CMFCRibbonCategory *)NULL); )
	{
		m_wndCommandsList.FillFromCategory(pCategory);
		break;
	}
	for (nCommand = 0, nCommands = m_wndCommandsList.GetCount(); nCommand < nCommands; nCommand++)
	{
		for (m_wndCommandsList.GetText(nCommand, szCommand); _istdigit(szCommand.GetAt(0)); )
		{
			m_wndCommandsList.DeleteString(nCommand);
			nCommands--;
			nCommand--;
			break;
		}
	}
	if (m_wndCommandsList.GetCount() > 0)
	{
		m_wndCommandsList.SetCurSel(0);
		EnumAccelerators();
	}
}

VOID CUserInterfaceKeyboardPage::EnumAccelerators()
{
	INT  nIndex;
	LPACCEL  pAccel;

	for (m_hAccelTable = NULL; m_pAccel[0] != (LPACCEL)NULL; )
	{
		delete[] m_pAccel[0];
		m_pAccel[0] = NULL;
		break;
	}
	if ((nIndex = m_wndViewTypeList.GetCurSel()) == CB_ERR)
	{
		m_wndViewIcon.SetIcon((HICON)NULL);
		return;
	}
	for (m_wndViewIcon.SetIcon((HICON)(LONG_PTR)GetClassLongPtr(m_pParentFrame->GetSafeHwnd(), GCLP_HICON)), m_nAccelSize[0] = CopyAcceleratorTable((m_hAccelTable = m_pParentFrame->m_hAccelTable), (LPACCEL)NULL, 0); (m_pAccel[0] = new ACCEL[m_nAccelSize[0]]); )
	{
		for (CopyAcceleratorTable(m_hAccelTable, m_pAccel[0], m_nAccelSize[0]); (pAccel = (!m_pAccel[1]) ? new ACCEL[(m_nAccelSize[1] = m_nAccelSize[0])] : (LPACCEL)NULL); )
		{
			CopyAcceleratorTable(m_hAccelTable, (m_pAccel[1] = pAccel), m_nAccelSize[1]);
			break;
		}
		break;
	}
	ShowAccelerator();
}

VOID CUserInterfaceKeyboardPage::ShowAccelerator()
{
	INT  nIndex;
	INT  nCount;

	for (m_szCommand.Empty(), m_wndCurrentKeysList.ResetContent(), m_wndRemoveButton.EnableWindow(FALSE), m_pAccel[2] = NULL; (nIndex = m_wndCommandsList.GetCurSel()) == LB_ERR; )
	{
		m_wndNewKey.EnableWindow(FALSE);
		UpdateData(FALSE);
		m_pButton = NULL;
		return;
	}
	for (; (m_pButton = (CMFCRibbonBaseElement*)m_wndCommandsList.GetItemData(nIndex)); )
	{
		m_pParentFrame->GetMessageString(m_pButton->GetID(), m_szCommand);
		break;
	}
	for (nIndex = 0, nCount = (m_pAccel[0] != (LPACCEL)NULL) ? m_nAccelSize[0] : 0; nIndex < nCount; nIndex++)
	{
		if (m_pButton->GetID() == m_pAccel[0][nIndex].cmd)
		{
			AddKeyEntry(&m_pAccel[0][nIndex]);
			continue;
		}
	}
	UpdateData(FALSE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION_STATIC)->ShowWindow((GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION)->ShowWindow((GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION_STATIC)->EnableWindow((GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION)->EnableWindow((GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS)->EnableWindow((SendDlgItemMessage(IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_NEWKEY_STATIC)->EnableWindow(!m_szCommand.IsEmpty());
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_NEWKEY)->EnableWindow(!m_szCommand.IsEmpty());
}

VOID CUserInterfaceKeyboardPage::ShowShortcutKey()
{
	INT  nIndex;
	INT  nCount;
	BYTE  nFlags;
	BOOL  bDefined;
	LPACCEL  pAccel;
	CString  szText;
	CMFCRibbonBaseElement  *pCommand;

	if ((pAccel = (LPACCEL)m_wndNewKey.GetAccel()))
	{
		for (m_wndAssociation.ShowWindow((m_wndNewKey.IsKeyDefined()) ? SW_SHOW : SW_HIDE), m_wndAssignButton.EnableWindow(FALSE), m_szAssociation.Empty(); m_wndNewKey.IsKeyDefined(); )
		{
			for (nIndex = 0, nCount = m_nAccelSize[0], nFlags = FCONTROL | FALT | FSHIFT | FVIRTKEY, bDefined = FALSE; nIndex < nCount; nIndex++)
			{
				if (pAccel->key == m_pAccel[0][nIndex].key && (pAccel->fVirt & nFlags) == (m_pAccel[0][nIndex].fVirt & nFlags))
				{
					if ((pCommand = m_pRibbonBar->FindByID(m_pAccel[0][nIndex].cmd, FALSE)) != (CMFCRibbonBaseElement *)NULL)
					{
						for (m_szAssociation = pCommand->GetText(); m_szAssociation.IsEmpty(); )
						{
							pCommand->UpdateTooltipInfo();
							m_szAssociation = pCommand->GetToolTipText();
							break;
						}
					}
					else
					{
						for (m_szAssociation = STRING(IDS_USERINTERFACEDIALOG_KEYBOARDPAGE_ASSOCIATIONUNKNOWN); szText.LoadString(m_pAccel[0][nIndex].cmd) && !szText.IsEmpty(); )
						{
							AfxExtractSubString(m_szAssociation, szText, 1, EOL);
							break;
						}
					}
					bDefined = TRUE;
				}
			}
			if (!bDefined)
			{
				m_szAssociation = STRING(IDS_USERINTERFACEDIALOG_KEYBOARDPAGE_ASSOCIATIONNONE);
				m_wndAssignButton.EnableWindow();
			}
			break;
		}
		UpdateData(FALSE);
		GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDASSOCIATION_STATIC)->EnableWindow(m_wndNewKey.IsKeyDefined());
		GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDASSOCIATION)->EnableWindow(m_wndNewKey.IsKeyDefined());
	}
}

VOID CUserInterfaceKeyboardPage::AddKeyEntry(LPACCEL pEntry)
{
	INT  nIndex;
	CString  szKey;
	CMFCAcceleratorKey  cKey(pEntry);

	for (cKey.Format(szKey); (nIndex = m_wndCurrentKeysList.AddString(szKey)) >= 0; )
	{
		m_wndCurrentKeysList.SetItemData(nIndex, (DWORD_PTR)pEntry);
		break;
	}
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS)->EnableWindow((SendDlgItemMessage(IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

void CUserInterfaceKeyboardPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserInterfaceKeyboardPage)
	DDX_Control(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_CATEGORY, m_wndCategoryList);
	DDX_Control(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDS, m_wndCommandsList);
	DDX_Control(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE, m_wndViewTypeList);
	DDX_Control(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE_SYMBOL, m_wndViewIcon);
	DDX_Control(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS, m_wndCurrentKeysList);
	DDX_Control(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_NEWKEY, m_wndNewKey);
	DDX_Control(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDASSOCIATION_STATIC, m_wndAssociation);
	DDX_Control(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_ACCELERATOR_ASSIGN, m_wndAssignButton);
	DDX_Control(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_ACCELERATOR_REMOVE, m_wndRemoveButton);
	DDX_Text(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDDESCRIPTION, m_szCommand);
	DDX_Text(pDX, IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDASSOCIATION, m_szAssociation);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUserInterfaceKeyboardPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CUserInterfaceKeyboardPage)
	ON_BN_CLICKED(IDC_USERINTERFACE_KEYBOARDPAGE_ACCELERATOR_ASSIGN, OnAssignAccelerator)
	ON_BN_CLICKED(IDC_USERINTERFACE_KEYBOARDPAGE_ACCELERATOR_REMOVE, OnRemoveAccelerator)
	ON_BN_CLICKED(IDC_USERINTERFACE_KEYBOARDPAGE_ACCELERATORS_RESET, OnResetAllAccelerators)
	ON_EN_CHANGE(IDC_USERINTERFACE_KEYBOARDPAGE_NEWKEY, OnEditchangeNewKey)
	ON_CBN_SELCHANGE(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE, OnSelchangeViewType)
	ON_LBN_SELCHANGE(IDC_USERINTERFACE_KEYBOARDPAGE_CATEGORY, OnSelchangeCategory)
	ON_LBN_SELCHANGE(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDS, OnSelchangeCommandsList)
	ON_LBN_SELCHANGE(IDC_USERINTERFACE_KEYBOARDPAGE_CURRENTKEYS, OnSelchangeCurrentKeysList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserInterfaceKeyboardPage message handlers

BOOL CUserInterfaceKeyboardPage::OnInitDialog()
{
	INT  nIndex;
	INT  nCategory;
	INT  nCategories;
	CMFCRibbonCategory  *pCategory;

	CLocalePropertyPage::OnInitDialog();
	for (nCategory = 0, nCategories = m_pRibbonBar->GetCategoryCount(); nCategory < nCategories; nCategory++)
	{
		if ((pCategory = m_pRibbonBar->GetCategory(nCategory)))
		{
			m_wndCategoryList.AddString(pCategory->GetName());
			continue;
		}
	}
	if (m_wndCategoryList.GetCount() > 0)
	{
		m_wndCategoryList.SetCurSel(0);
		EnumCommands();
	}
	if ((nIndex = m_wndViewTypeList.AddString(STRING(IDS_USERINTERFACEDIALOG_KEYBOARDPAGE_DEFAULTCOMMANDVIEW))) >= 0)
	{
		m_wndViewTypeList.SetItemData(nIndex, (DWORD_PTR)NULL);
		m_wndViewTypeList.SetCurSel(nIndex);
		EnumAccelerators();
	}
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_CATEGORY_STATIC)->EnableWindow(m_wndCategoryList.GetCount() > 0);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_CATEGORY)->EnableWindow(m_wndCategoryList.GetCount() > 0);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDS_STATIC)->EnableWindow(m_wndCommandsList.GetCount() > 0);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDS)->EnableWindow(m_wndCommandsList.GetCount() > 0);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE)->EnableWindow((SendDlgItemMessage(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE_SYMBOL)->EnableWindow((SendDlgItemMessage(IDC_USERINTERFACE_KEYBOARDPAGE_COMMANDVIEWTYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_ACCELERATORS_RESET)->EnableWindow();
	return TRUE;
}

void CUserInterfaceKeyboardPage::OnAssignAccelerator()
{
	INT  nIndex[2];
	INT  nCount[2];
	LPACCEL  pAccel[2];

	if ((pAccel[0] = (LPACCEL)m_wndNewKey.GetAccel()))
	{
		for (pAccel[0]->cmd = (USHORT)m_pButton->GetID(), pAccel[1] = m_pAccel[0]; (m_pAccel[0] = new ACCEL[m_nAccelSize[0] + 1]); )
		{
			for (nIndex[0] = 0, nCount[0] = m_nAccelSize[0], memcpy(m_pAccel[0], pAccel[1], m_nAccelSize[0] * sizeof(ACCEL)); nIndex[0] < nCount[0]; nIndex[0]++)
			{
				for (nIndex[1] = 0, nCount[1] = m_wndCurrentKeysList.GetCount(); nIndex[1] < nCount[1]; nIndex[1]++)
				{
					if (m_wndCurrentKeysList.GetItemData(nIndex[1]) == (DWORD_PTR)(pAccel[1] + nIndex[0]))
					{
						m_wndCurrentKeysList.SetItemData(nIndex[1], (DWORD_PTR)(m_pAccel[0] + nIndex[0]));
						break;
					}
				}
			}
			for (m_pAccel[0][m_nAccelSize[0]++] = *pAccel[0], GetEditorApp()->GetKeyboardManager()->UpdateAccelTable((CMultiDocTemplate *)NULL, m_pAccel[0], m_nAccelSize[0]), AddKeyEntry(&m_pAccel[0][m_nAccelSize[0] - 1]), m_wndNewKey.ResetKey(); pAccel[1] != (LPACCEL)NULL; )
			{
				delete[] pAccel[1];
				break;
			}
			ShowShortcutKey();
			m_wndNewKey.SetFocus();
			break;
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CUserInterfaceKeyboardPage::OnRemoveAccelerator()
{
	INT  nIndex[3];
	INT  nCount[3];
	LPACCEL  pAccel;

	for (pAccel = m_pAccel[0]; (m_pAccel[0] = new ACCEL[m_nAccelSize[0] - 1]); )
	{
		for (nIndex[0] = 0, nCount[0] = m_nAccelSize[0], nIndex[1] = 0; nIndex[0] < nCount[0]; nIndex[0]++)
		{
			if (m_pAccel[2] != (pAccel + nIndex[0]))
			{
				m_pAccel[0][nIndex[1]++] = pAccel[nIndex[0]];
				for (nIndex[2] = 0, nCount[2] = m_wndCurrentKeysList.GetCount(); nIndex[2] < nCount[2]; nIndex[2]++)
				{
					if (m_wndCurrentKeysList.GetItemData(nIndex[2]) == (DWORD_PTR)(pAccel + nIndex[0]))
					{
						m_wndCurrentKeysList.SetItemData(nIndex[2], (DWORD_PTR)(m_pAccel[0] + nIndex[1] - 1));
						break;
					}
				}
			}
		}
		for (GetEditorApp()->GetKeyboardManager()->UpdateAccelTable((CMultiDocTemplate *)NULL, m_pAccel[0], --m_nAccelSize[0]); pAccel != (LPACCEL)NULL; )
		{
			delete[] pAccel;
			break;
		}
		ShowAccelerator();
		m_wndNewKey.SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CUserInterfaceKeyboardPage::OnResetAllAccelerators()
{
	for (GetEditorApp()->GetKeyboardManager()->ResetAll(), GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_NEWKEY)->SetWindowText(EMPTYSTRING), m_wndAssignButton.EnableWindow(FALSE); m_pParentFrame != NULL; )
	{
		m_pParentFrame->SendMessage(AFX_WM_RESETKEYBOARD);
		break;
	}
	EnumAccelerators();
	ShowAccelerator();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CUserInterfaceKeyboardPage::OnEditchangeNewKey()
{
	ShowShortcutKey();
	SendDlgItemMessage(IDC_USERINTERFACE_KEYBOARDPAGE_NEWKEY, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_USERINTERFACE_KEYBOARDPAGE_NEWKEY)->SetFocus();
}

void CUserInterfaceKeyboardPage::OnSelchangeCategory()
{
	EnumCommands();
}

void CUserInterfaceKeyboardPage::OnSelchangeCommandsList()
{
	ShowAccelerator();
}

void CUserInterfaceKeyboardPage::OnSelchangeCurrentKeysList()
{
	INT  nIndex;

	if ((nIndex = m_wndCurrentKeysList.GetCurSel()) >= 0)
	{
		m_pAccel[2] = (LPACCEL)m_wndCurrentKeysList.GetItemData(nIndex);
		m_wndRemoveButton.EnableWindow();
		return;
	}
	m_pAccel[2] = (LPACCEL)NULL;
	m_wndRemoveButton.EnableWindow(FALSE);
}

void CUserInterfaceKeyboardPage::OnSelchangeViewType()
{
	EnumAccelerators();
}


/////////////////////////////////////////////////////////////////////////////
// CUserInterfaceDialog

IMPLEMENT_DYNAMIC(CUserInterfaceDialog, CLocalePropertySheetDialog)

CUserInterfaceDialog::CUserInterfaceDialog(CWnd *pParentWnd, CMFCRibbonBar *pRibbonBar) : CLocalePropertySheetDialog(STRING(IDS_USERINTERFACEDIALOG_TITLE), pParentWnd)
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	m_pRibbonBarPage = new CUserInterfaceRibbonBarPage(pRibbonBar);
	m_pKeyboardPage = new CUserInterfaceKeyboardPage(pRibbonBar);
	AddPage(m_pRibbonBarPage);
	AddPage(m_pKeyboardPage);
}

CUserInterfaceDialog::~CUserInterfaceDialog()
{
	delete m_pRibbonBarPage;
	delete m_pKeyboardPage;
}

BEGIN_MESSAGE_MAP(CUserInterfaceDialog, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CUserInterfaceDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserInterfaceDialog message handlers

void CUserInterfaceDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_pRibbonBarPage->Update();
	m_pKeyboardPage->Update();
	CLocalePropertySheetDialog::OnOK();
}

BOOL CUserInterfaceDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_USERINTERFACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CUserInterfaceDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_USERINTERFACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDialog dialog

IMPLEMENT_DYNCREATE(CAboutDialog, CLocaleDialog)

CAboutDialog::CAboutDialog(CWnd *pParentWnd) : CLocaleDialog(CAboutDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CAboutDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CAboutDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CAboutDialog)
	// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDialog message handlers

BOOL CAboutDialog::OnInitDialog()
{
	CString  szTitle[2];
	CString  szVersion[2];
	CString  szCopyright[2];
	CTimeKey  tCopyrightTime;
	CVersionInfo  cVersionInfo;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	for (GetWindowText(szTitle[0]), GetDlgItem(IDC_ABOUT_VERSION)->GetWindowText(szVersion[0]), GetDlgItem(IDC_ABOUT_COPYRIGHT)->GetWindowText(szCopyright[0]), szTitle[1].Format(szTitle[0], (LPCTSTR)GetAppTitle()), szVersion[1].Format(szVersion[0], (LPCTSTR)cVersionInfo.QueryProductVersion()), szCopyright[1].Format(szCopyright[0], tCopyrightTime.GetYear(), (LPCTSTR)cVersionInfo.QueryCompanyName()); szTitle[0] != szTitle[1]; )
	{
		SetWindowText(szTitle[1]);
		break;
	}
	GetDlgItem(IDC_ABOUT_NAME)->SetWindowText(GetAppTitle());
	GetDlgItem(IDC_ABOUT_VERSION)->SetWindowText(szVersion[1]);
	GetDlgItem(IDC_ABOUT_COPYRIGHT)->SetWindowText(szCopyright[1]);
	GetDlgItem(IDC_ABOUT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_ABOUT_NAME)->EnableWindow();
	GetDlgItem(IDC_ABOUT_VERSION)->EnableWindow();
	GetDlgItem(IDC_ABOUT_COPYRIGHT)->EnableWindow();
	GetDlgItem(IDC_ABOUT_COPYRIGHTNOTICE_TITLE)->EnableWindow();
	GetDlgItem(IDC_ABOUT_COPYRIGHTNOTICE_STATEMENT)->EnableWindow();
	GetDlgItem(IDC_ABOUT_COPYRIGHTNOTICE_CONSEQUENCE)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow();
	return TRUE;
}

void CAboutDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnOK();
}
