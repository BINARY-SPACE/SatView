// ACCOUNTS.H : Accounts Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the accounts related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1996/09/26 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __ACCOUNTS_H__
#define __ACCOUNTS_H__

#include "token.h"
#include "timekey.h"
#include "language.h"
#include "registry.h"


/////////////////////////////////////////////////////////////////////////////
// CAccountToken

// Definition of the account modes
#define ACCOUNT_MODE_ONLINE   1
#define ACCOUNT_MODE_OFFLINE   2
// Definition of the account privilege profiles
#define PRIVILEGE_PROFILE_DEFAULT   0
#define PRIVILEGE_PROFILE_ADMINISTRATORS   1
#define PRIVILEGE_PROFILE_OPERATORS   2
#define PRIVILEGE_PROFILE_USERS   3
#define PRIVILEGE_PROFILE_GUESTS   4
// Definition of the account privileges
#define FIRSTPRIVILEGE   1
#define PRIVILEGE_ACCOUNTS_BROWSE   FIRSTPRIVILEGE
#define PRIVILEGE_ACCOUNTS_CHANGE   (FIRSTPRIVILEGE+1)
#define PRIVILEGE_ACCOUNTS_REMOTEBROWSE   (FIRSTPRIVILEGE+2)
#define PRIVILEGE_ACCOUNTS_REMOTECHANGE   (FIRSTPRIVILEGE+3)
#define PRIVILEGE_ACCOUNTDATABASES_CHANGE   (FIRSTPRIVILEGE+4)
#define PRIVILEGE_ACCOUNTRIGHTS_CHANGE   (FIRSTPRIVILEGE+5)
#define PRIVILEGE_ACCOUNTPASSWORD_CHANGE   (FIRSTPRIVILEGE+6)
#define PRIVILEGE_ACCOUNTVALIDITY_CHANGE   (FIRSTPRIVILEGE+7)
#define PRIVILEGE_DATABASE_CREATE   (FIRSTPRIVILEGE+8)
#define PRIVILEGE_DATABASE_DELETE   (FIRSTPRIVILEGE+9)
#define PRIVILEGE_DATABASE_REMOTECREATE   (FIRSTPRIVILEGE+10)
#define PRIVILEGE_DATABASE_REMOTEDELETE   (FIRSTPRIVILEGE+11)
#define PRIVILEGE_DISPLAYAREA_BROWSE   (FIRSTPRIVILEGE+12)
#define PRIVILEGE_DISPLAYAREA_CHANGE   (FIRSTPRIVILEGE+13)
#define PRIVILEGE_EVENTLOGS_BROWSE   (FIRSTPRIVILEGE+14)
#define PRIVILEGE_EVENTLOGS_CHANGE   (FIRSTPRIVILEGE+15)
#define PRIVILEGE_EVENTLOGS_REMOTEBROWSE   (FIRSTPRIVILEGE+16)
#define PRIVILEGE_EVENTLOGS_REMOTECHANGE   (FIRSTPRIVILEGE+17)
#define PRIVILEGE_EVENTLOGNAME_CHANGE   (FIRSTPRIVILEGE+18)
#define PRIVILEGE_EVENTLOGPOLICY_CHANGE   (FIRSTPRIVILEGE+19)
#define PRIVILEGE_EVENTLOGSIZE_CHANGE   (FIRSTPRIVILEGE+20)
#define PRIVILEGE_PRINTPROFILES_BROWSE   (FIRSTPRIVILEGE+21)
#define PRIVILEGE_PRINTPROFILES_CHANGE   (FIRSTPRIVILEGE+22)
#define PRIVILEGE_AUDITIONPROFILES_BROWSE   (FIRSTPRIVILEGE+23)
#define PRIVILEGE_AUDITIONPROFILES_CHANGE   (FIRSTPRIVILEGE+24)
#define PRIVILEGE_NOTIFICATIONPROFILES_BROWSE  (FIRSTPRIVILEGE+25)
#define PRIVILEGE_NOTIFICATIONPROFILES_CHANGE  (FIRSTPRIVILEGE+26)
#define PRIVILEGE_MISCELLANEOUS_BROWSE   (FIRSTPRIVILEGE+27)
#define PRIVILEGE_MISCELLANEOUS_CHANGE   (FIRSTPRIVILEGE+28)
#define PRIVILEGE_ONLINE_OPERATE   (FIRSTPRIVILEGE+29)
#define PRIVILEGE_OFFLINE_OPERATE   (FIRSTPRIVILEGE+30)
#define PRIVILEGE_NETWORK_LOGIN   (FIRSTPRIVILEGE+31)
#define PRIVILEGE_PRINTER_CHANGE   (FIRSTPRIVILEGE+32)
#define PRIVILEGE_COMPUTERLOGS_VIEW   (FIRSTPRIVILEGE+33)
#define PRIVILEGE_SPACECRAFTLOGS_VIEW   (FIRSTPRIVILEGE+34)
#define PRIVILEGE_USERLOGS_VIEW   (FIRSTPRIVILEGE+35)
#define PRIVILEGE_SYSTEMALERTS_BROWSE   (FIRSTPRIVILEGE+36)
#define PRIVILEGE_SYSTEMALERTS_CHANGE   (FIRSTPRIVILEGE+37)
#define PRIVILEGE_AUTOMATIONSERVICE_BROWSE   (FIRSTPRIVILEGE+38)
#define PRIVILEGE_AUTOMATIONSERVICE_CHANGE   (FIRSTPRIVILEGE+39)
#define PRIVILEGE_TELEMETRYSERVICE_BROWSE   (FIRSTPRIVILEGE+40)
#define PRIVILEGE_TELEMETRYSERVICE_CHANGE   (FIRSTPRIVILEGE+41)
#define PRIVILEGE_TELEMETRYEVENTS_BROWSE   (FIRSTPRIVILEGE+42)
#define PRIVILEGE_TELEMETRYEVENTS_CHANGE   (FIRSTPRIVILEGE+43)
#define PRIVILEGE_TELEMETRYEVENTS_IMPORT   (FIRSTPRIVILEGE+44)
#define PRIVILEGE_TELEMETRYEVENTS_EXPORT   (FIRSTPRIVILEGE+45)
#define PRIVILEGE_TELEMETRYREPORTS_BROWSE   (FIRSTPRIVILEGE+46)
#define PRIVILEGE_TELEMETRYREPORTS_CHANGE   (FIRSTPRIVILEGE+47)
#define PRIVILEGE_TELEMETRYREPORTS_IMPORT   (FIRSTPRIVILEGE+48)
#define PRIVILEGE_TELEMETRYREPORTS_EXPORT   (FIRSTPRIVILEGE+49)
#define PRIVILEGE_TELEMETRYARCHIVESARCHIVALS_BROWSE   (FIRSTPRIVILEGE+50)
#define PRIVILEGE_TELEMETRYARCHIVESARCHIVALS_CHANGE   (FIRSTPRIVILEGE+51)
#define PRIVILEGE_TELEMETRYARCHIVESRETRIEVALS_BROWSE   (FIRSTPRIVILEGE+52)
#define PRIVILEGE_TELEMETRYARCHIVESRETRIEVALS_CHANGE   (FIRSTPRIVILEGE+53)
#define PRIVILEGE_TELEMETRYARCHIVESBACKUPS_BROWSE   (FIRSTPRIVILEGE+54)
#define PRIVILEGE_TELEMETRYARCHIVESBACKUPS_CHANGE   (FIRSTPRIVILEGE+55)
#define PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_BROWSE   (FIRSTPRIVILEGE+56)
#define PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_CHANGE   (FIRSTPRIVILEGE+57)
#define PRIVILEGE_TELEMETRYARCHIVESTOOLS_BROWSE   (FIRSTPRIVILEGE+58)
#define PRIVILEGE_TELEMETRYARCHIVESTOOLS_CHANGE   (FIRSTPRIVILEGE+59)
#define PRIVILEGE_TELEMETRYPARAMETERS_BROWSE   (FIRSTPRIVILEGE+60)
#define PRIVILEGE_TELEMETRYPARAMETERS_CHANGE   (FIRSTPRIVILEGE+61)
#define PRIVILEGE_MEMORYDUMPS_SETUPVIEW   (FIRSTPRIVILEGE+62)
#define PRIVILEGE_MEMORYDUMPS_SETUPCHANGE   (FIRSTPRIVILEGE+63)
#define PRIVILEGE_MEMORYDUMPS_IMPORT   (FIRSTPRIVILEGE+64)
#define PRIVILEGE_MEMORYDUMPS_EXPORT   (FIRSTPRIVILEGE+65)
#define PRIVILEGE_AND_USE   (FIRSTPRIVILEGE+66)
#define PRIVILEGE_AND_TEMPORARYUSE   (FIRSTPRIVILEGE+67)
#define PRIVILEGE_AND_IMPORT   (FIRSTPRIVILEGE+68)
#define PRIVILEGE_AND_EXPORT   (FIRSTPRIVILEGE+69)
#define PRIVILEGE_GRD_USE   (FIRSTPRIVILEGE+70)
#define PRIVILEGE_GRD_TEMPORARYUSE   (FIRSTPRIVILEGE+71)
#define PRIVILEGE_GRD_IMPORT   (FIRSTPRIVILEGE+72)
#define PRIVILEGE_GRD_EXPORT   (FIRSTPRIVILEGE+73)
#define PRIVILEGE_HEX_USE   (FIRSTPRIVILEGE+74)
#define PRIVILEGE_OOL_USE   (FIRSTPRIVILEGE+75)
#define PRIVILEGE_MMD_USE   (FIRSTPRIVILEGE+76)
#define PRIVILEGE_POD_USE   (FIRSTPRIVILEGE+77)
#define PRIVILEGE_POD_TEMPORARYUSE   (FIRSTPRIVILEGE+78)
#define PRIVILEGE_POD_IMPORT   (FIRSTPRIVILEGE+79)
#define PRIVILEGE_POD_EXPORT   (FIRSTPRIVILEGE+80)
#define PRIVILEGE_SATELLITETRACKINGTOOL_USE   (FIRSTPRIVILEGE+81)
#define PRIVILEGE_EVENTBOX_USE   (FIRSTPRIVILEGE+82)
#define PRIVILEGE_EVENTBOX_SETUPVIEW   (FIRSTPRIVILEGE+83)
#define PRIVILEGE_EVENTBOX_SETUPCHANGE   (FIRSTPRIVILEGE+84)
#define PRIVILEGE_EVENTBOX_SCHEDULE   (FIRSTPRIVILEGE+85)
#define PRIVILEGE_EVENTBOX_WATCH   (FIRSTPRIVILEGE+86)
#define PRIVILEGE_EVENTBOX_LOOK   (FIRSTPRIVILEGE+87)
#define PRIVILEGE_EVENTBOX_ACKNOWLEDGE   (FIRSTPRIVILEGE+88)
#define PRIVILEGE_EVENTBOX_RESET   (FIRSTPRIVILEGE+89)
#define PRIVILEGE_MAILBOX_USE   (FIRSTPRIVILEGE+90)
#define PRIVILEGE_LOGBOOK_USE   (FIRSTPRIVILEGE+91)
#define PRIVILEGE_TELECOMMANDSERVICE_BROWSE   (FIRSTPRIVILEGE+92)
#define PRIVILEGE_TELECOMMANDSERVICE_CHANGE   (FIRSTPRIVILEGE+93)
#define PRIVILEGE_TELECOMMANDOPTIONS_BROWSE   (FIRSTPRIVILEGE+94)
#define PRIVILEGE_TELECOMMANDOPTIONS_CHANGE   (FIRSTPRIVILEGE+95)
#define PRIVILEGE_TELECOMMANDPARAMETERS_BROWSE   (FIRSTPRIVILEGE+96)
#define PRIVILEGE_TELECOMMANDPARAMETERS_CHANGE   (FIRSTPRIVILEGE+97)
#define PRIVILEGE_TCMANUALSTACK_BROWSE   (FIRSTPRIVILEGE+98)
#define PRIVILEGE_TCMANUALSTACK_CHANGE   (FIRSTPRIVILEGE+99)
#define PRIVILEGE_TCMANUALSTACK_CRITICALCHANGE   (FIRSTPRIVILEGE+100)
#define PRIVILEGE_TCAUTOMATICSTACK_BROWSE   (FIRSTPRIVILEGE+101)
#define PRIVILEGE_TCAUTOMATICSTACK_CHANGE   (FIRSTPRIVILEGE+102)
#define PRIVILEGE_TCAUTOMATICSTACK_CRITICALCHANGE   (FIRSTPRIVILEGE+103)
#define PRIVILEGE_TCPROCEDURESMONITOR_BROWSE   (FIRSTPRIVILEGE+104)
#define PRIVILEGE_TCPROCEDURESMONITOR_CHANGE   (FIRSTPRIVILEGE+105)
#define PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE   (FIRSTPRIVILEGE+106)
#define PRIVILEGE_TCDIAGNOSTICSERVICES_BROWSE   (FIRSTPRIVILEGE+107)
#define PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE   (FIRSTPRIVILEGE+108)
#define PRIVILEGE_TCONBOARDSOFTWARESERVICES_BROWSE   (FIRSTPRIVILEGE+109)
#define PRIVILEGE_TCONBOARDSOFTWARESERVICES_CHANGE   (FIRSTPRIVILEGE+110)
#define PRIVILEGE_TCHISTORY_BROWSE   (FIRSTPRIVILEGE+111)
#define PRIVILEGE_TCHISTORY_CHANGE   (FIRSTPRIVILEGE+112)
#define PRIVILEGE_PFLP_SETUPVIEW   (FIRSTPRIVILEGE+113)
#define PRIVILEGE_PFLP_SETUPCHANGE   (FIRSTPRIVILEGE+114)
#define PRIVILEGE_PFLP_CLIENTSVIEW   (FIRSTPRIVILEGE+115)
#define PRIVILEGE_PFLP_CLIENTSCHANGE   (FIRSTPRIVILEGE+116)
#define PRIVILEGE_TPEP_SETUPVIEW   (FIRSTPRIVILEGE+117)
#define PRIVILEGE_TPEP_SETUPCHANGE   (FIRSTPRIVILEGE+118)
#define PRIVILEGE_TPEP_CLIENTSVIEW   (FIRSTPRIVILEGE+119)
#define PRIVILEGE_TPEP_CLIENTSCHANGE   (FIRSTPRIVILEGE+120)
#define PRIVILEGE_TPEP_CONNECT   (FIRSTPRIVILEGE+121)
#define PRIVILEGE_TPEP_VIEW   (FIRSTPRIVILEGE+122)
#define PRIVILEGE_SERVERADDRESSBOOK_BROWSE   (FIRSTPRIVILEGE+123)
#define PRIVILEGE_SERVERADDRESSBOOK_CHANGE   (FIRSTPRIVILEGE+124)
#define PRIVILEGE_SERVERADDRESSBOOK_REMOTEBROWSE   (FIRSTPRIVILEGE+125)
#define PRIVILEGE_SERVERADDRESSBOOK_REMOTECHANGE   (FIRSTPRIVILEGE+126)
#define PRIVILEGE_USERADDRESSBOOK_BROWSE   (FIRSTPRIVILEGE+127)
#define PRIVILEGE_USERADDRESSBOOK_CHANGE   (FIRSTPRIVILEGE+128)
#define PRIVILEGE_USERADDRESSBOOK_REMOTEBROWSE   (FIRSTPRIVILEGE+129)
#define PRIVILEGE_USERADDRESSBOOK_REMOTECHANGE   (FIRSTPRIVILEGE+130)
#define PRIVILEGE_TOOLSDOWNLOADPROFILES_BROWSE   (FIRSTPRIVILEGE+131)
#define PRIVILEGE_TOOLSDOWNLOADPROFILES_CHANGE   (FIRSTPRIVILEGE+132)
#define PRIVILEGE_TOOLSDATABASEOPTIONS_BROWSE   (FIRSTPRIVILEGE+133)
#define PRIVILEGE_TOOLSDATABASEOPTIONS_CHANGE   (FIRSTPRIVILEGE+134)
#define PRIVILEGE_TOOLSSATELLITETRACKINGOPTIONS_BROWSE   (FIRSTPRIVILEGE+135)
#define PRIVILEGE_TOOLSSATELLITETRACKINGOPTIONS_CHANGE   (FIRSTPRIVILEGE+136)
#define PRIVILEGE_TOOLSEMAILOPTIONS_BROWSE   (FIRSTPRIVILEGE+137)
#define PRIVILEGE_TOOLSEMAILOPTIONS_CHANGE   (FIRSTPRIVILEGE+138)
#define PRIVILEGE_EXIT   (FIRSTPRIVILEGE+139)   
#define LASTPRIVILEGE   (FIRSTPRIVILEGE+139)

class AFX_EXT_CLASS CAccountToken : public CToken
{
	// Construction
public:
	CAccountToken();
	CAccountToken(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName);
	CAccountToken(CAccountToken *pAccountToken);

	// Attributes
private:
	UINT  m_nMode;
	CString  m_szDatabase;
	CString  m_szPassword;
	CString  m_szRASServer;
	CString  m_szRASUserName;
	CString  m_szRASPassword;
	CTimeKey  m_tValidity[2];
	CUIntArray  m_nPrivileges;
	BOOL  m_bEnabled;
	BOOL  m_bUnique;

	// Operations
public:
	BOOL SetOwner(CONST CAccountToken *pAccountToken);
	BOOL SetOwner(LPCTSTR pszComputerName = NULL, LPCTSTR pszSpacecraftName = NULL, LPCTSTR pszUserName = NULL);
	BOOL GetOwner(CString &szComputerName, CString &szSpacecraftName, CString &szUserName) CONST;

	BOOL SetComputerName(LPCTSTR pszComputerName = NULL);
	CString GetComputerName() CONST;
	BOOL SetSpacecraftName(LPCTSTR pszSpacecraftName = NULL);
	CString GetSpacecraftName() CONST;
	BOOL SetUserName(LPCTSTR pszUserName = NULL);
	CString GetUserName() CONST;

	BOOL SetMode(UINT nMode);
	UINT GetMode() CONST;
	BOOL SetDatabase(LPCTSTR pszDatabase);
	CString GetDatabase() CONST;
	BOOL SetPassword(LPCTSTR pszPassword);
	CString GetPassword() CONST;
	BOOL SetValidity(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetValidity(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetPrivileges(CONST CUIntArray &nPrivileges);
	INT GetPrivileges(CUIntArray &nPrivileges) CONST;
	BOOL SetRASServer(LPCTSTR pszServer);
	CString GetRASServer() CONST;
	BOOL SetRASUserName(LPCTSTR pszUserName);
	CString GetRASUserName() CONST;
	BOOL SetRASPassword(LPCTSTR pszPassword);
	CString GetRASPassword() CONST;
	BOOL SetUnique(BOOL bEnable = TRUE);
	BOOL IsUnique() CONST;

	BOOL SetAllPrivileges();
	INT GetAllPrivileges(CUIntArray &nPrivileges) CONST;
	INT LookupAllPrivileges(CStringArray &szPrivileges) CONST;
	BOOL SetDefaultPrivileges(UINT nProfile = PRIVILEGE_PROFILE_DEFAULT);
	INT GetDefaultPrivileges(UINT nProfile, CUIntArray &nPrivileges) CONST;
	INT LookupDefaultPrivileges(UINT nProfile, CStringArray &szPrivileges) CONST;
	INT LookupPrivileges(CStringArray &szPrivileges) CONST;
	BOOL EnablePrivileges(BOOL bEnable = TRUE);
	BOOL HasPrivilegesEnabled() CONST;
	BOOL AddPrivilege(UINT nPrivilege);
	BOOL RemovePrivilege(UINT nPrivilege);
	BOOL CheckPrivilege(UINT nPrivilege) CONST;
	BOOL LookupPrivilege(UINT nPrivilege, CString &szPrivilege) CONST;

	VOID Copy(CONST CAccountToken *pAccountToken);
	BOOL Compare(CONST CAccountToken *pAccountToken) CONST;

private:
	INT FindPrivilege(UINT nPrivilege) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAccountTokens

class AFX_EXT_CLASS CAccountTokens : public CPtrArray
{
	// Construction
public:
	CAccountTokens();
	~CAccountTokens();

	// Attributes
public:

	// Operations
public:
	INT Add(CAccountToken *pAccountToken);

	INT Find(CAccountToken *pAccountToken) CONST;
	INT Find(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName) CONST;

	CAccountToken *GetAt(INT nIndex) CONST;
	CAccountToken *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CAccountTokens *pAccountTokens);
	BOOL Compare(CONST CAccountTokens *pAccountTokens) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAccounts

class AFX_EXT_CLASS CAccounts : public CComputerToken
{
	// Construction
public:
	CAccounts();
	CAccounts(LPCTSTR pszComputerName);

	// Attributes
public:

	// Operations
public:
	INT EnumUsers(CStringArray &szUsers, BOOL bAll = FALSE) CONST;
	INT EnumGroups(CStringArray &szGroups) CONST;
	INT EnumGroupMemberShips(LPCTSTR pszUserName, CStringArray &szGroups) CONST;
	INT EnumGroupMembers(LPCTSTR pszGroupName, CStringArray &szUsers) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CUserAccounts

class AFX_EXT_CLASS CUserAccounts : public CRegistry
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL WriteAccount(CONST CAccountToken *pAccountToken);
	BOOL ReadAccount(CAccountToken *pAccountToken);
	BOOL FindAccount(CONST CAccountToken *pAccountToken);
	BOOL RemoveAccount(CONST CAccountToken *pAccountToken);
	BOOL SetActiveAccount(CONST CAccountToken *pAccountToken);
	BOOL GetActiveAccount(CAccountToken *pAccountToken) CONST;

	INT EnumAccounts(BOOL bExpired = FALSE);
	INT EnumAccounts(CAccountTokens &pAccountTokens, BOOL bExpired = FALSE);
	BOOL DeleteAccounts();

private:
	BOOL AddAccount(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bActive = TRUE);
	BOOL RemoveAccount(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName);

	BOOL WriteAccountMode(LPCTSTR pszSubKey, UINT nMode);
	BOOL ReadAccountMode(LPCTSTR pszSubKey, UINT &nMode) CONST;
	BOOL WriteAccountDatabase(LPCTSTR pszSubKey, LPCTSTR pszDatabase);
	BOOL ReadAccountDatabase(LPCTSTR pszSubKey, CString &szDatabase) CONST;
	BOOL WriteAccountPassword(LPCTSTR pszSubKey, CONST CByteArray &nPassword);
	BOOL ReadAccountPassword(LPCTSTR pszSubKey, CByteArray &nPassword) CONST;
	BOOL WriteAccountValidity(LPCTSTR pszSubKey, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL ReadAccountValidity(LPCTSTR pszSubKey, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL WriteAccountPrivileges(LPCTSTR pszSubKey, CONST CUIntArray &nPrivileges);
	BOOL ReadAccountPrivileges(LPCTSTR pszSubKey, CUIntArray &nPrivileges) CONST;
	BOOL WriteAccountUniqueFlag(LPCTSTR pszSubKey, BOOL bUnique);
	BOOL ReadAccountUniqueFlag(LPCTSTR pszSubKey, BOOL &bUnique) CONST;
	BOOL WriteAccountRASServer(LPCTSTR pszSubKey, LPCTSTR pszServer);
	BOOL ReadAccountRASServer(LPCTSTR pszSubKey, CString &szServer) CONST;
	BOOL WriteAccountRASUserName(LPCTSTR pszSubKey, LPCTSTR pszUserName);
	BOOL ReadAccountRASUserName(LPCTSTR pszSubKey, CString &szUserName) CONST;
	BOOL WriteAccountRASPassword(LPCTSTR pszSubKey, CONST CByteArray &nPassword);
	BOOL ReadAccountRASPassword(LPCTSTR pszSubKey, CByteArray &nPassword) CONST;

	CString QueryAccountsSubKey() CONST;
	CString QueryUserAccountsDirectorySubKey() CONST;
	CString QueryUserAccountsSubKey(LPCTSTR pszSpacecraftName) CONST;
	CString QueryUserAccountSubKey(LPCTSTR pszSpacecraftName, LPCTSTR pszUserName) CONST;

	BOOL SecureSubKey(LPCTSTR pszSubKey);
	BOOL DeleteSubKey(LPCTSTR pszSubKey);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAccountsApp application

class AFX_EXT_CLASS CAccountsApp : public CLocaleApp
{
	DECLARE_DYNAMIC(CAccountsApp)

	// Construction
public:
	CAccountsApp();
	~CAccountsApp();

	// Attributes
private:
	CString  m_szAccountName;
	CString  m_szAccountPassword;
	CAccountToken  *m_pAccountToken;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL RegisterApp();
	BOOL UnregisterApp(BOOL bAll = FALSE);

	BOOL SaveAccount();
	BOOL TestAccount() CONST;
	BOOL LoadAccount();
	BOOL LoadAccount(CONST CAccountToken *pAccountToken);
	VOID SetAccount(CONST CAccountToken *pAccountToken);
	VOID GetAccount(CAccountToken *pAccountToken) CONST;
	BOOL ValidateAccount(CONST CAccountToken *pAccountToken);
	BOOL ValidateAccount(BOOL bValidate = TRUE);

	CString GetAccountComputerName() CONST;
	CString GetAccountSpacecraftName() CONST;
	CString GetAccountUserName() CONST;
	UINT GetAccountMode() CONST;
	INT GetAccountPrivileges(CUIntArray &nPrivileges) CONST;
	BOOL IsAccountUnique() CONST;
	CString GetAccountDatabase() CONST;
	CString GetAccountPassword() CONST;
	CString GetAccountRASServer() CONST;
	CString GetAccountRASUserName() CONST;
	CString GetAccountRASPassword() CONST;

	BOOL CheckAccountOwner() CONST;
	BOOL CheckAccountOwner(CONST CAccountToken *pAccountToken) CONST;
	BOOL CheckAccountPrivilege(UINT nPrivilege) CONST;

protected:
	BOOL IsInitialized() CONST;

	BOOL Lock();
	BOOL Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountsApp)
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAccountsApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline CAccountsApp *GetAccountsApp()
{
	return((CAccountsApp *)AfxGetApp());
}
inline BOOL RegisterApp()
{
	return(GetAccountsApp()->RegisterApp());
}
inline BOOL UnregisterApp(BOOL bAll = FALSE)
{
	return(GetAccountsApp()->UnregisterApp(bAll));
}
inline BOOL SaveAccount()
{
	return(GetAccountsApp()->SaveAccount());
}
inline BOOL TestAccount()
{
	return(GetAccountsApp()->TestAccount());
}
inline BOOL LoadAccount()
{
	return(GetAccountsApp()->LoadAccount());
}
inline BOOL LoadAccount(CAccountToken *pAccountToken)
{
	return(GetAccountsApp()->LoadAccount(pAccountToken));
}
inline VOID SetAccount(CONST CAccountToken *pAccountToken)
{
	return(GetAccountsApp()->SetAccount(pAccountToken));
}
inline VOID GetAccount(CAccountToken *pAccountToken)
{
	return(GetAccountsApp()->GetAccount(pAccountToken));
}
inline BOOL ValidateAccount(CONST CAccountToken *pAccountToken)
{
	return(GetAccountsApp()->ValidateAccount(pAccountToken));
}
inline BOOL ValidateAccount(BOOL bValidate = TRUE)
{
	return(GetAccountsApp()->ValidateAccount(bValidate));
}
inline CString GetAccountComputerName()
{
	return(GetAccountsApp()->GetAccountComputerName());
}
inline CString GetAccountSpacecraftName()
{
	return(GetAccountsApp()->GetAccountSpacecraftName());
}
inline CString GetAccountUserName()
{
	return(GetAccountsApp()->GetAccountUserName());
}
inline UINT GetAccountMode()
{
	return(GetAccountsApp()->GetAccountMode());
}
inline INT GetAccountPrivileges(CUIntArray &nPrivileges)
{
	return(GetAccountsApp()->GetAccountPrivileges(nPrivileges));
}
inline BOOL IsAccountUnique()
{
	return(GetAccountsApp()->IsAccountUnique());
}
inline CString GetAccountDatabase()
{
	return(GetAccountsApp()->GetAccountDatabase());
}
inline CString GetAccountPassword()
{
	return(GetAccountsApp()->GetAccountPassword());
}
inline CString GetAccountRASServer()
{
	return(GetAccountsApp()->GetAccountRASServer());
}
inline CString GetAccountRASUserName()
{
	return(GetAccountsApp()->GetAccountRASUserName());
}
inline CString GetAccountRASPassword()
{
	return(GetAccountsApp()->GetAccountRASPassword());
}
inline BOOL CheckAccountOwner()
{
	return(GetAccountsApp()->CheckAccountOwner());
}
inline BOOL CheckAccountOwner(CONST CAccountToken *pAccountToken)
{
	return(GetAccountsApp()->CheckAccountOwner(pAccountToken));
}
inline BOOL CheckAccountPrivilege(UINT nPrivilege)
{
	return(GetAccountsApp()->CheckAccountPrivilege(nPrivilege));
}

/////////////////////////////////////////////////////////////////////////////


#endif // __ACCOUNTS_H__
