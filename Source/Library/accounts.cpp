// ACCOUNTS.CPP : Accounts Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the accounts related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1996/09/26 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CAccountToken

CAccountToken::CAccountToken() : CToken()
{
	SetMode(ACCOUNT_MODE_OFFLINE);
	SetOwner(GetAccountComputerName(), GetAccountSpacecraftName(), GetAccountUserName());
	EnablePrivileges();
	SetUnique(FALSE);
}
CAccountToken::CAccountToken(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName) : CToken(pszComputerName, pszSpacecraftName, pszUserName)
{
	SetMode(ACCOUNT_MODE_OFFLINE);
	SetOwner(pszComputerName, pszSpacecraftName, pszUserName);
	EnablePrivileges();
	SetUnique(FALSE);
}
CAccountToken::CAccountToken(CAccountToken *pAccountToken)
{
	Copy(pAccountToken);
	EnablePrivileges();
	SetUnique(FALSE);
}

BOOL CAccountToken::SetOwner(CONST CAccountToken *pAccountToken)
{
	if (CToken::SetOwner(pAccountToken))
	{
		SetDefaultPrivileges();
		return TRUE;
	}
	return FALSE;
}
BOOL CAccountToken::SetOwner(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName)
{
	if (CToken::SetOwner(pszComputerName, pszSpacecraftName, pszUserName))
	{
		SetDefaultPrivileges();
		return TRUE;
	}
	return FALSE;
}

BOOL CAccountToken::GetOwner(CString &szComputerName, CString &szSpacecraftName, CString &szUserName) CONST
{
	return CToken::GetOwner(szComputerName, szSpacecraftName, szUserName);
}

BOOL CAccountToken::SetComputerName(LPCTSTR pszComputerName)
{
	if (CToken::SetComputerName(pszComputerName))
	{
		SetDefaultPrivileges();
		return TRUE;
	}
	return FALSE;
}

CString CAccountToken::GetComputerName() CONST
{
	return CToken::GetComputerName();
}

BOOL CAccountToken::SetSpacecraftName(LPCTSTR pszSpacecraftName)
{
	if (CToken::SetSpacecraftName(pszSpacecraftName))
	{
		SetDefaultPrivileges();
		return TRUE;
	}
	return FALSE;
}

CString CAccountToken::GetSpacecraftName() CONST
{
	return CToken::GetSpacecraftName();
}

BOOL CAccountToken::SetUserName(LPCTSTR pszUserName)
{
	if (CToken::SetUserName(pszUserName))
	{
		SetDefaultPrivileges();
		return TRUE;
	}
	return FALSE;
}

CString CAccountToken::GetUserName() CONST
{
	return CToken::GetUserName();
}

BOOL CAccountToken::SetMode(UINT nMode)
{
	if (((nMode == ACCOUNT_MODE_ONLINE  &&  CheckPrivilege(PRIVILEGE_ONLINE_OPERATE)) || (nMode == ACCOUNT_MODE_OFFLINE  &&  CheckPrivilege(PRIVILEGE_OFFLINE_OPERATE))) || !HasPrivilegesEnabled())
	{
		m_nMode = nMode;
		return TRUE;
	}
	return FALSE;
}

UINT CAccountToken::GetMode() CONST
{
	return m_nMode;
}

BOOL CAccountToken::SetDatabase(LPCTSTR pszDatabase)
{
	if (!CheckAccountOwner() || CheckAccountPrivilege(PRIVILEGE_ONLINE_OPERATE) || CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE) || !HasPrivilegesEnabled())
	{
		m_szDatabase = pszDatabase;
		return TRUE;
	}
	return FALSE;
}

CString CAccountToken::GetDatabase() CONST
{
	return m_szDatabase;
}

BOOL CAccountToken::SetPassword(LPCTSTR pszPassword)
{
	if ((!CheckAccountOwner() || CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_CHANGE) || (CheckAccountOwner(this) && CheckAccountPrivilege(PRIVILEGE_ACCOUNTPASSWORD_CHANGE))) || !HasPrivilegesEnabled())
	{
		m_szPassword = pszPassword;
		return TRUE;
	}
	return FALSE;
}

CString CAccountToken::GetPassword() CONST
{
	return m_szPassword;
}

BOOL CAccountToken::SetValidity(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	if ((!CheckAccountOwner() || CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_CHANGE) || (CheckAccountOwner(this) && CheckAccountPrivilege(PRIVILEGE_ACCOUNTVALIDITY_CHANGE))) || !HasPrivilegesEnabled())
	{
		if (tStartTime <= tStopTime)
		{
			m_tValidity[0] = tStartTime;
			m_tValidity[1] = tStopTime;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CAccountToken::GetValidity(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CTimeKey  tTime;

	tStartTime = m_tValidity[0];
	tStopTime = m_tValidity[1];
	return(((!tStartTime.GetTime() && !tStopTime.GetTime()) || (tStartTime < tStopTime  &&  tTime >= tStartTime  &&  tTime <= tStopTime)) ? TRUE : FALSE);
}

BOOL CAccountToken::SetPrivileges(CONST CUIntArray &nPrivileges)
{
	if ((!CheckAccountOwner() || CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_CHANGE) || (CheckAccountOwner(this) && CheckAccountPrivilege(PRIVILEGE_ACCOUNTRIGHTS_CHANGE))) || !HasPrivilegesEnabled())
	{
		m_nPrivileges.Copy(nPrivileges);
		return TRUE;
	}
	return FALSE;
}

INT CAccountToken::GetPrivileges(CUIntArray &nPrivileges) CONST
{
	nPrivileges.Copy(m_nPrivileges);
	return((INT)nPrivileges.GetSize());
}

BOOL CAccountToken::SetRASServer(LPCTSTR pszServer)
{
	if (!CheckAccountOwner() || CheckAccountPrivilege(PRIVILEGE_NETWORK_LOGIN) || !HasPrivilegesEnabled())
	{
		m_szRASServer = pszServer;
		return TRUE;
	}
	return FALSE;
}

CString CAccountToken::GetRASServer() CONST
{
	return m_szRASServer;
}

BOOL CAccountToken::SetRASUserName(LPCTSTR pszUserName)
{
	if (!CheckAccountOwner() || CheckAccountPrivilege(PRIVILEGE_NETWORK_LOGIN) || !HasPrivilegesEnabled())
	{
		m_szRASUserName = pszUserName;
		return TRUE;
	}
	return FALSE;
}

CString CAccountToken::GetRASUserName() CONST
{
	return m_szRASUserName;
}

BOOL CAccountToken::SetRASPassword(LPCTSTR pszPassword)
{
	if (!CheckAccountOwner() || CheckAccountPrivilege(PRIVILEGE_NETWORK_LOGIN) || !HasPrivilegesEnabled())
	{
		m_szRASPassword = pszPassword;
		return TRUE;
	}
	return FALSE;
}

CString CAccountToken::GetRASPassword() CONST
{
	return m_szRASPassword;
}

BOOL CAccountToken::SetAllPrivileges()
{
	return((!CheckAccountOwner() || CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_CHANGE) || (CheckAccountOwner(this) && CheckAccountPrivilege(PRIVILEGE_ACCOUNTRIGHTS_CHANGE))) ? SetDefaultPrivileges(PRIVILEGE_PROFILE_ADMINISTRATORS) : FALSE);
}

BOOL CAccountToken::SetUnique(BOOL bEnable)
{
	BOOL  bEnabled;

	bEnabled = m_bUnique;
	m_bUnique = bEnable;
	return bEnabled;
}

BOOL CAccountToken::IsUnique() CONST
{
	return m_bUnique;
}

INT CAccountToken::GetAllPrivileges(CUIntArray &nPrivileges) CONST
{
	INT  nRight;
	INT  nRights;

	for (nRight = 0, nRights = LASTPRIVILEGE - FIRSTPRIVILEGE + 1, nPrivileges.RemoveAll(); nRight < nRights; nRight++)
	{
		nPrivileges.Add(FIRSTPRIVILEGE + nRight);
		continue;
	}
	return((INT)nPrivileges.GetSize());
}

INT CAccountToken::LookupAllPrivileges(CStringArray &szPrivileges) CONST
{
	INT  nRight;
	INT  nRights;
	CUIntArray  nPrivileges;

	for (nRight = 0, nRights = GetAllPrivileges(nPrivileges), szPrivileges.RemoveAll(); nRight < nRights; nRight++)
	{
		szPrivileges.Add(STRING(MINPRIVILEGE + nPrivileges.GetAt(nRight) - FIRSTPRIVILEGE));
		continue;
	}
	return((INT)szPrivileges.GetSize());
}

BOOL CAccountToken::SetDefaultPrivileges(UINT nProfile)
{
	BOOL  bEnabled;
	CUIntArray  nPrivileges;

	for (bEnabled = EnablePrivileges(FALSE); GetDefaultPrivileges(nProfile, nPrivileges) && SetPrivileges(nPrivileges); )
	{
		if (nProfile == PRIVILEGE_PROFILE_DEFAULT)
		{
			SetMode(ACCOUNT_MODE_OFFLINE);
			SetDatabase(EMPTYSTRING);
			SetPassword(CString(CR));
			SetValidity(CTimeKey(0), CTimeKey(0));
			SetRASServer(EMPTYSTRING);
			SetRASUserName(EMPTYSTRING);
			SetRASPassword(EMPTYSTRING);
		}
		EnablePrivileges(bEnabled);
		return TRUE;
	}
	EnablePrivileges(bEnabled);
	return FALSE;
}

INT CAccountToken::GetDefaultPrivileges(UINT nProfile, CUIntArray &nPrivileges) CONST
{
	for (nPrivileges.RemoveAll(); nProfile == PRIVILEGE_PROFILE_GUESTS; )
	{
		nPrivileges.Add(PRIVILEGE_ACCOUNTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_ACCOUNTS_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_DISPLAYAREA_BROWSE);
		nPrivileges.Add(PRIVILEGE_DISPLAYAREA_CHANGE);
		nPrivileges.Add(PRIVILEGE_EVENTLOGS_BROWSE);
		nPrivileges.Add(PRIVILEGE_EVENTLOGS_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_PRINTPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_AUDITIONPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_NOTIFICATIONPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_MISCELLANEOUS_BROWSE);
		nPrivileges.Add(PRIVILEGE_ONLINE_OPERATE);
		nPrivileges.Add(PRIVILEGE_OFFLINE_OPERATE);
		nPrivileges.Add(PRIVILEGE_SYSTEMALERTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_AUTOMATIONSERVICE_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYSERVICE_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYEVENTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYREPORTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESARCHIVALS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESRETRIEVALS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESRETRIEVALS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESBACKUPS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESTOOLS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYPARAMETERS_BROWSE);
		nPrivileges.Add(PRIVILEGE_MEMORYDUMPS_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_AND_USE);
		nPrivileges.Add(PRIVILEGE_GRD_USE);
		nPrivileges.Add(PRIVILEGE_HEX_USE);
		nPrivileges.Add(PRIVILEGE_OOL_USE);
		nPrivileges.Add(PRIVILEGE_MMD_USE);
		nPrivileges.Add(PRIVILEGE_POD_USE);
		nPrivileges.Add(PRIVILEGE_SATELLITETRACKINGTOOL_USE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_USE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_SETUPCHANGE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_LOOK);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_ACKNOWLEDGE);
		nPrivileges.Add(PRIVILEGE_PFLP_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_PFLP_CLIENTSVIEW);
		nPrivileges.Add(PRIVILEGE_TPEP_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_TPEP_CLIENTSVIEW);
		nPrivileges.Add(PRIVILEGE_SERVERADDRESSBOOK_BROWSE);
		nPrivileges.Add(PRIVILEGE_SERVERADDRESSBOOK_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_USERADDRESSBOOK_BROWSE);
		nPrivileges.Add(PRIVILEGE_USERADDRESSBOOK_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSDOWNLOADPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSDATABASEOPTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSSATELLITETRACKINGOPTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSEMAILOPTIONS_BROWSE);
		return((INT)nPrivileges.GetSize());
	}
	if ((nProfile == PRIVILEGE_PROFILE_DEFAULT  &&  !IsAdministrator()) || nProfile == PRIVILEGE_PROFILE_USERS)
	{
		nPrivileges.Add(PRIVILEGE_ACCOUNTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_ACCOUNTS_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_ACCOUNTPASSWORD_CHANGE);
		nPrivileges.Add(PRIVILEGE_DISPLAYAREA_BROWSE);
		nPrivileges.Add(PRIVILEGE_DISPLAYAREA_CHANGE);
		nPrivileges.Add(PRIVILEGE_EVENTLOGS_BROWSE);
		nPrivileges.Add(PRIVILEGE_EVENTLOGS_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_PRINTPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_AUDITIONPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_NOTIFICATIONPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_MISCELLANEOUS_BROWSE);
		nPrivileges.Add(PRIVILEGE_ONLINE_OPERATE);
		nPrivileges.Add(PRIVILEGE_OFFLINE_OPERATE);
		nPrivileges.Add(PRIVILEGE_NETWORK_LOGIN);
		nPrivileges.Add(PRIVILEGE_PRINTER_CHANGE);
		nPrivileges.Add(PRIVILEGE_SYSTEMALERTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_AUTOMATIONSERVICE_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYSERVICE_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYEVENTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYREPORTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESARCHIVALS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESRETRIEVALS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESRETRIEVALS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESBACKUPS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESTOOLS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESTOOLS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYPARAMETERS_BROWSE);
		nPrivileges.Add(PRIVILEGE_MEMORYDUMPS_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_AND_USE);
		nPrivileges.Add(PRIVILEGE_AND_TEMPORARYUSE);
		nPrivileges.Add(PRIVILEGE_GRD_USE);
		nPrivileges.Add(PRIVILEGE_GRD_TEMPORARYUSE);
		nPrivileges.Add(PRIVILEGE_HEX_USE);
		nPrivileges.Add(PRIVILEGE_OOL_USE);
		nPrivileges.Add(PRIVILEGE_MMD_USE);
		nPrivileges.Add(PRIVILEGE_POD_USE);
		nPrivileges.Add(PRIVILEGE_POD_TEMPORARYUSE);
		nPrivileges.Add(PRIVILEGE_SATELLITETRACKINGTOOL_USE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_USE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_SETUPCHANGE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_WATCH);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_LOOK);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_ACKNOWLEDGE);
		nPrivileges.Add(PRIVILEGE_MAILBOX_USE);
		nPrivileges.Add(PRIVILEGE_LOGBOOK_USE);
		nPrivileges.Add(PRIVILEGE_TELECOMMANDSERVICE_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELECOMMANDOPTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELECOMMANDPARAMETERS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCMANUALSTACK_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCAUTOMATICSTACK_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCPROCEDURESMONITOR_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCDIAGNOSTICSERVICES_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCONBOARDSOFTWARESERVICES_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCHISTORY_BROWSE);
		nPrivileges.Add(PRIVILEGE_PFLP_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_PFLP_CLIENTSVIEW);
		nPrivileges.Add(PRIVILEGE_TPEP_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_TPEP_CLIENTSVIEW);
		nPrivileges.Add(PRIVILEGE_TPEP_CONNECT);
		nPrivileges.Add(PRIVILEGE_TPEP_VIEW);
		nPrivileges.Add(PRIVILEGE_SERVERADDRESSBOOK_BROWSE);
		nPrivileges.Add(PRIVILEGE_SERVERADDRESSBOOK_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_USERADDRESSBOOK_BROWSE);
		nPrivileges.Add(PRIVILEGE_USERADDRESSBOOK_CHANGE);
		nPrivileges.Add(PRIVILEGE_USERADDRESSBOOK_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSDOWNLOADPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSDATABASEOPTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSSATELLITETRACKINGOPTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSEMAILOPTIONS_BROWSE);
		return((INT)nPrivileges.GetSize());
	}
	if (nProfile == PRIVILEGE_PROFILE_OPERATORS)
	{
		nPrivileges.Add(PRIVILEGE_ACCOUNTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_ACCOUNTS_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_ACCOUNTPASSWORD_CHANGE);
		nPrivileges.Add(PRIVILEGE_DISPLAYAREA_BROWSE);
		nPrivileges.Add(PRIVILEGE_DISPLAYAREA_CHANGE);
		nPrivileges.Add(PRIVILEGE_EVENTLOGS_BROWSE);
		nPrivileges.Add(PRIVILEGE_EVENTLOGS_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_EVENTLOGNAME_CHANGE);
		nPrivileges.Add(PRIVILEGE_EVENTLOGPOLICY_CHANGE);
		nPrivileges.Add(PRIVILEGE_EVENTLOGSIZE_CHANGE);
		nPrivileges.Add(PRIVILEGE_PRINTPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_PRINTPROFILES_CHANGE);
		nPrivileges.Add(PRIVILEGE_AUDITIONPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_AUDITIONPROFILES_CHANGE);
		nPrivileges.Add(PRIVILEGE_NOTIFICATIONPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_NOTIFICATIONPROFILES_CHANGE);
		nPrivileges.Add(PRIVILEGE_MISCELLANEOUS_BROWSE);
		nPrivileges.Add(PRIVILEGE_MISCELLANEOUS_CHANGE);
		nPrivileges.Add(PRIVILEGE_ONLINE_OPERATE);
		nPrivileges.Add(PRIVILEGE_OFFLINE_OPERATE);
		nPrivileges.Add(PRIVILEGE_NETWORK_LOGIN);
		nPrivileges.Add(PRIVILEGE_PRINTER_CHANGE);
		nPrivileges.Add(PRIVILEGE_COMPUTERLOGS_VIEW);
		nPrivileges.Add(PRIVILEGE_SPACECRAFTLOGS_VIEW);
		nPrivileges.Add(PRIVILEGE_USERLOGS_VIEW);
		nPrivileges.Add(PRIVILEGE_SYSTEMALERTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_SYSTEMALERTS_CHANGE);
		nPrivileges.Add(PRIVILEGE_AUTOMATIONSERVICE_BROWSE);
		nPrivileges.Add(PRIVILEGE_AUTOMATIONSERVICE_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYSERVICE_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYSERVICE_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYEVENTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYEVENTS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYEVENTS_IMPORT);
		nPrivileges.Add(PRIVILEGE_TELEMETRYEVENTS_EXPORT);
		nPrivileges.Add(PRIVILEGE_TELEMETRYREPORTS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYREPORTS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYREPORTS_IMPORT);
		nPrivileges.Add(PRIVILEGE_TELEMETRYREPORTS_EXPORT);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESARCHIVALS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESRETRIEVALS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESRETRIEVALS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESBACKUPS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESEXTRACTIONS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESTOOLS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYARCHIVESTOOLS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYPARAMETERS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELEMETRYPARAMETERS_CHANGE);
		nPrivileges.Add(PRIVILEGE_MEMORYDUMPS_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_MEMORYDUMPS_SETUPCHANGE);
		nPrivileges.Add(PRIVILEGE_MEMORYDUMPS_IMPORT);
		nPrivileges.Add(PRIVILEGE_MEMORYDUMPS_EXPORT);
		nPrivileges.Add(PRIVILEGE_AND_USE);
		nPrivileges.Add(PRIVILEGE_AND_TEMPORARYUSE);
		nPrivileges.Add(PRIVILEGE_AND_IMPORT);
		nPrivileges.Add(PRIVILEGE_AND_EXPORT);
		nPrivileges.Add(PRIVILEGE_GRD_USE);
		nPrivileges.Add(PRIVILEGE_GRD_TEMPORARYUSE);
		nPrivileges.Add(PRIVILEGE_GRD_IMPORT);
		nPrivileges.Add(PRIVILEGE_GRD_EXPORT);
		nPrivileges.Add(PRIVILEGE_HEX_USE);
		nPrivileges.Add(PRIVILEGE_OOL_USE);
		nPrivileges.Add(PRIVILEGE_MMD_USE);
		nPrivileges.Add(PRIVILEGE_POD_USE);
		nPrivileges.Add(PRIVILEGE_POD_TEMPORARYUSE);
		nPrivileges.Add(PRIVILEGE_POD_IMPORT);
		nPrivileges.Add(PRIVILEGE_POD_EXPORT);
		nPrivileges.Add(PRIVILEGE_SATELLITETRACKINGTOOL_USE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_USE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_SETUPCHANGE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_SCHEDULE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_WATCH);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_LOOK);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_ACKNOWLEDGE);
		nPrivileges.Add(PRIVILEGE_EVENTBOX_RESET);
		nPrivileges.Add(PRIVILEGE_MAILBOX_USE);
		nPrivileges.Add(PRIVILEGE_LOGBOOK_USE);
		nPrivileges.Add(PRIVILEGE_TELECOMMANDSERVICE_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELECOMMANDSERVICE_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELECOMMANDOPTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELECOMMANDOPTIONS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TELECOMMANDPARAMETERS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TELECOMMANDPARAMETERS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TCMANUALSTACK_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCMANUALSTACK_CHANGE);
		nPrivileges.Add(PRIVILEGE_TCMANUALSTACK_CRITICALCHANGE);
		nPrivileges.Add(PRIVILEGE_TCAUTOMATICSTACK_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCAUTOMATICSTACK_CHANGE);
		nPrivileges.Add(PRIVILEGE_TCAUTOMATICSTACK_CRITICALCHANGE);
		nPrivileges.Add(PRIVILEGE_TCPROCEDURESMONITOR_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCPROCEDURESMONITOR_CHANGE);
		nPrivileges.Add(PRIVILEGE_TCPROCEDURESMONITOR_CRITICALCHANGE);
		nPrivileges.Add(PRIVILEGE_TCDIAGNOSTICSERVICES_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCDIAGNOSTICSERVICES_CHANGE);
		nPrivileges.Add(PRIVILEGE_TCONBOARDSOFTWARESERVICES_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCONBOARDSOFTWARESERVICES_CHANGE);
		nPrivileges.Add(PRIVILEGE_TCHISTORY_BROWSE);
		nPrivileges.Add(PRIVILEGE_TCHISTORY_CHANGE);
		nPrivileges.Add(PRIVILEGE_PFLP_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_PFLP_SETUPCHANGE);
		nPrivileges.Add(PRIVILEGE_PFLP_CLIENTSVIEW);
		nPrivileges.Add(PRIVILEGE_PFLP_CLIENTSCHANGE);
		nPrivileges.Add(PRIVILEGE_TPEP_SETUPVIEW);
		nPrivileges.Add(PRIVILEGE_TPEP_SETUPCHANGE);
		nPrivileges.Add(PRIVILEGE_TPEP_CLIENTSVIEW);
		nPrivileges.Add(PRIVILEGE_TPEP_CLIENTSCHANGE);
		nPrivileges.Add(PRIVILEGE_TPEP_CONNECT);
		nPrivileges.Add(PRIVILEGE_TPEP_VIEW);
		nPrivileges.Add(PRIVILEGE_SERVERADDRESSBOOK_BROWSE);
		nPrivileges.Add(PRIVILEGE_SERVERADDRESSBOOK_CHANGE);
		nPrivileges.Add(PRIVILEGE_SERVERADDRESSBOOK_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_SERVERADDRESSBOOK_REMOTECHANGE);
		nPrivileges.Add(PRIVILEGE_USERADDRESSBOOK_BROWSE);
		nPrivileges.Add(PRIVILEGE_USERADDRESSBOOK_CHANGE);
		nPrivileges.Add(PRIVILEGE_USERADDRESSBOOK_REMOTEBROWSE);
		nPrivileges.Add(PRIVILEGE_USERADDRESSBOOK_REMOTECHANGE);
		nPrivileges.Add(PRIVILEGE_TOOLSDOWNLOADPROFILES_BROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSDOWNLOADPROFILES_CHANGE);
		nPrivileges.Add(PRIVILEGE_TOOLSDATABASEOPTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSDATABASEOPTIONS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TOOLSSATELLITETRACKINGOPTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSSATELLITETRACKINGOPTIONS_CHANGE);
		nPrivileges.Add(PRIVILEGE_TOOLSEMAILOPTIONS_BROWSE);
		nPrivileges.Add(PRIVILEGE_TOOLSEMAILOPTIONS_CHANGE);
		nPrivileges.Add(PRIVILEGE_EXIT);
		return((INT)nPrivileges.GetSize());
	}
	return GetAllPrivileges(nPrivileges);
}

INT CAccountToken::LookupDefaultPrivileges(UINT nProfile, CStringArray &szPrivileges) CONST
{
	INT  nRight;
	INT  nRights;
	CUIntArray  nPrivileges;

	for (nRight = 0, nRights = GetDefaultPrivileges(nProfile, nPrivileges), szPrivileges.RemoveAll(); nRight < nRights; nRight++)
	{
		szPrivileges.Add(STRING(MINPRIVILEGE + nPrivileges.GetAt(nRight) - FIRSTPRIVILEGE));
		continue;
	}
	return((INT)szPrivileges.GetSize());
}

INT CAccountToken::LookupPrivileges(CStringArray &szPrivileges) CONST
{
	INT  nRight;
	INT  nRights;
	CString  szPrivilege;

	for (nRight = 0, nRights = (INT)m_nPrivileges.GetSize(), szPrivileges.RemoveAll(); nRight < nRights; nRight++)
	{
		if (LookupPrivilege(m_nPrivileges.GetAt(nRight), szPrivilege))
		{
			szPrivileges.Add(szPrivilege);
			continue;
		}
	}
	return((INT)szPrivileges.GetSize());
}

BOOL CAccountToken::EnablePrivileges(BOOL bEnable)
{
	BOOL  bEnabled;

	bEnabled = m_bEnabled;
	m_bEnabled = bEnable;
	return bEnabled;
}

BOOL CAccountToken::HasPrivilegesEnabled() CONST
{
	return m_bEnabled;
}

BOOL CAccountToken::AddPrivilege(UINT nPrivilege)
{
	if (!CheckAccountOwner() || CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_CHANGE) || (CheckAccountOwner(this) && CheckAccountPrivilege(PRIVILEGE_ACCOUNTRIGHTS_CHANGE)))
	{
		if (nPrivilege >= FIRSTPRIVILEGE  &&  nPrivilege <= LASTPRIVILEGE)
		{
			if (FindPrivilege(nPrivilege) < 0) m_nPrivileges.Add(nPrivilege);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CAccountToken::RemovePrivilege(UINT nPrivilege)
{
	INT  nIndex;

	if (!CheckAccountOwner() || CheckAccountPrivilege(PRIVILEGE_ACCOUNTS_CHANGE) || (CheckAccountOwner(this) && CheckAccountPrivilege(PRIVILEGE_ACCOUNTRIGHTS_CHANGE)))
	{
		if ((nIndex = FindPrivilege(nPrivilege)) >= 0)
		{
			m_nPrivileges.RemoveAt(nIndex);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CAccountToken::CheckPrivilege(UINT nPrivilege) CONST
{
	return((FindPrivilege(nPrivilege) >= 0) ? TRUE : FALSE);
}

BOOL CAccountToken::LookupPrivilege(UINT nPrivilege, CString &szPrivilege) CONST
{
	if (nPrivilege >= FIRSTPRIVILEGE  &&  nPrivilege <= LASTPRIVILEGE)
	{
		szPrivilege = STRING(MINPRIVILEGE + nPrivilege - FIRSTPRIVILEGE);
		return TRUE;
	}
	return FALSE;
}

VOID CAccountToken::Copy(CONST CAccountToken *pAccountToken)
{
	SetOwner(pAccountToken);
	m_nMode = pAccountToken->m_nMode;
	m_szDatabase = pAccountToken->m_szDatabase;
	m_szPassword = pAccountToken->m_szPassword;
	m_tValidity[0] = pAccountToken->m_tValidity[0];
	m_tValidity[1] = pAccountToken->m_tValidity[1];
	m_nPrivileges.Copy(pAccountToken->m_nPrivileges);
	m_szRASServer = pAccountToken->m_szRASServer;
	m_szRASUserName = pAccountToken->m_szRASUserName;
	m_szRASPassword = pAccountToken->m_szRASPassword;
	m_bEnabled = pAccountToken->m_bEnabled;
	m_bUnique = pAccountToken->m_bUnique;
}

BOOL CAccountToken::Compare(CONST CAccountToken *pAccountToken) CONST
{
	INT  nRight[2];
	INT  nRights[2];

	for (nRight[0] = 0, nRights[0] = (HasSameOwner(pAccountToken) && pAccountToken->m_nMode == m_nMode && pAccountToken->m_szDatabase == m_szDatabase && pAccountToken->m_szPassword == m_szPassword && pAccountToken->m_tValidity[0] == m_tValidity[0] && pAccountToken->m_tValidity[1] == m_tValidity[1] && pAccountToken->m_nPrivileges.GetSize() == m_nPrivileges.GetSize() && pAccountToken->m_szRASServer == m_szRASServer && pAccountToken->m_szRASUserName == m_szRASUserName && pAccountToken->m_szRASPassword == m_szRASPassword && pAccountToken->m_bEnabled == m_bEnabled && pAccountToken->m_bUnique == m_bUnique) ? (INT)pAccountToken->m_nPrivileges.GetSize() : -1; nRight[0] < nRights[0]; nRight[0]++)
	{
		if (CheckPrivilege(pAccountToken->m_nPrivileges.GetAt(nRight[0]))) continue;
		break;
	}
	for (nRight[1] = 0, nRights[1] = (nRight[0] == nRights[0]) ? (INT)m_nPrivileges.GetSize() : -1; nRight[1] < nRights[1]; nRight[1]++)
	{
		if (pAccountToken->CheckPrivilege(m_nPrivileges.GetAt(nRight[1]))) continue;
		break;
	}
	return((nRight[0] == nRights[0] && nRight[1] == nRights[1]) ? TRUE : FALSE);
}

INT CAccountToken::FindPrivilege(UINT nPrivilege) CONST
{
	INT  nRight;
	INT  nRights;

	for (nRight = 0, nRights = (INT)m_nPrivileges.GetSize(); nRight < nRights; nRight++)
	{
		if (m_nPrivileges.GetAt(nRight) == nPrivilege) break;
		continue;
	}
	return((nRight < nRights) ? nRight : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CAccountTokens

CAccountTokens::CAccountTokens() : CPtrArray()
{
	return;
}

CAccountTokens::~CAccountTokens()
{
	RemoveAll();
}

INT CAccountTokens::Add(CAccountToken *pAccountToken)
{
	return((INT)CPtrArray::Add(pAccountToken));
}

INT CAccountTokens::Find(CAccountToken *pAccountToken) CONST
{
	CString  szAccount[3];

	return((pAccountToken->GetOwner(szAccount[0], szAccount[1], szAccount[2]) >= 0) ? Find(szAccount[0], szAccount[1], szAccount[2]) : -1);
}
INT CAccountTokens::Find(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName) CONST
{
	INT  nAccount;
	INT  nAccounts;
	CAccountToken  *pAccountToken;

	for (nAccount = 0, nAccounts = (INT)GetSize(); nAccount < nAccounts; nAccount++)
	{
		if ((pAccountToken = GetAt(nAccount)) && pAccountToken->HasSameOwner(pszComputerName, pszSpacecraftName, pszUserName)) break;
		continue;
	}
	return((nAccount < nAccounts) ? nAccount : -1);
}

CAccountToken *CAccountTokens::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CAccountToken *)CPtrArray::GetAt(nIndex) : (CAccountToken *)NULL);
}

CAccountToken *CAccountTokens::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CAccountToken *)CPtrArray::GetAt(nIndex) : (CAccountToken *)NULL);
}

VOID CAccountTokens::RemoveAll()
{
	INT  nAccount;
	INT  nAccounts;

	for (nAccount = 0, nAccounts = (INT)GetSize(); nAccount < nAccounts; nAccount++)
	{
		delete GetAt(nAccount);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CAccountTokens::Copy(CONST CAccountTokens *pAccountTokens)
{
	INT  nAccount;
	INT  nAccounts;
	CAccountToken  *pAccountToken;

	for (nAccount = 0, nAccounts = (INT)pAccountTokens->GetSize(), RemoveAll(); nAccount < nAccounts; nAccount++)
	{
		if ((pAccountToken = new CAccountToken) != (CAccountToken *)NULL)
		{
			pAccountToken->Copy(pAccountTokens->GetAt(nAccount));
			InsertAt(nAccount, pAccountToken, 1);
			continue;
		}
		RemoveAll();
		break;
	}
	return((nAccount == nAccounts) ? TRUE : FALSE);
}

BOOL CAccountTokens::Compare(CONST CAccountTokens *pAccountTokens) CONST
{
	INT  nAccount[2];
	INT  nAccounts[2];

	for (nAccount[0] = 0, nAccounts[0] = (INT)GetSize(), nAccounts[1] = (INT)pAccountTokens->GetSize(); nAccount[0] < nAccounts[0] && nAccounts[0] == nAccounts[1]; nAccount[0]++)
	{
		for (nAccount[1] = 0; nAccount[1] < nAccounts[1]; nAccount[1] = nAccount[1] + 1)
		{
			if (pAccountTokens->GetAt(nAccount[0])->Compare(GetAt(nAccount[1]))) break;
			continue;
		}
		if (nAccount[1] == nAccounts[1]) break;
	}
	return((nAccount[0] == nAccounts[0] && nAccounts[0] == nAccounts[1]) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CAccounts

CAccounts::CAccounts() : CComputerToken()
{
	return;
}
CAccounts::CAccounts(LPCTSTR pszComputerName) : CComputerToken(pszComputerName)
{
	return;
}

INT CAccounts::EnumUsers(CStringArray &szUsers, BOOL bAll) CONST
{
	DWORD  dwUser;
	DWORD  dwUsers;
	LPTSTR  pszUserName;
	LPWSTR  pszServerName;
	CString  szDCName;
	CString  szServerName;
	CStringArray  szUserNames;
	PUSER_INFO_20  pUserInfo;

	if ((pszServerName = (LPWSTR)GlobalAlloc(GPTR, ((szServerName = GetComputerUNCName()).GetLength() + 1)*sizeof(WCHAR))))
	{
#ifdef UNICODE
		wcscpy_s(pszServerName, szServerName.GetLength() + 1, szServerName);
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szServerName, -1, pszServerName, szServerName.GetLength() + 1);
#endif
		if (NetUserEnum(pszServerName, 20, FILTER_NORMAL_ACCOUNT, (LPBYTE *)&pUserInfo, (DWORD)-1, &dwUsers, &dwUser, (LPDWORD)NULL) == NERR_Success)
		{
			for (dwUser = 0; dwUser < dwUsers; dwUser++)
			{
				if ((pUserInfo[dwUser].usri20_flags & UF_NORMAL_ACCOUNT) && (bAll || (pUserInfo[dwUser].usri20_flags & UF_ACCOUNTDISABLE) != UF_ACCOUNTDISABLE))
				{
					if ((pszUserName = (LPTSTR)GlobalAlloc(GPTR, (wcslen(pUserInfo[dwUser].usri20_name) + 1)*sizeof(TCHAR))))
					{
#ifdef UNICODE
						wcscpy_s(pszUserName, wcslen(pUserInfo[dwUser].usri20_name) + 1, pUserInfo[dwUser].usri20_name);
#else
						WideCharToMultiByte(CP_ACP, 0, pUserInfo[dwUser].usri20_name, -1, pszUserName, (INT)wcslen(pUserInfo[dwUser].usri20_name) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#endif
						szUserNames.Add(pszUserName);
						GlobalFree(pszUserName);
						continue;
					}
					break;
				}
			}
			if (dwUser == dwUsers)
			{
				szUsers.Copy(szUserNames);
				GlobalFree(pszServerName);
				NetApiBufferFree(pUserInfo);
				return((INT)szUserNames.GetSize());
			}
			NetApiBufferFree(pUserInfo);
		}
		GlobalFree(pszServerName);
	}
	return 0;
}

INT CAccounts::EnumGroups(CStringArray &szGroups) CONST
{
	DWORD  dwGroup;
	DWORD  dwGroups;
	LPTSTR  pszGroupName;
	LPWSTR  pszServerName;
	CString  szDCName;
	CString  szServerName;
	CStringArray  szGroupNames;
	PLOCALGROUP_INFO_0  pGroupInfo;

	if ((pszServerName = (LPWSTR)GlobalAlloc(GPTR, ((szServerName = GetComputerUNCName()).GetLength() + 1)*sizeof(WCHAR))))
	{
#ifdef UNICODE
		wcscpy_s(pszServerName, szServerName.GetLength() + 1, szServerName);
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szServerName, -1, pszServerName, szServerName.GetLength() + 1);
#endif
		if (NetLocalGroupEnum(pszServerName, 0, (LPBYTE *)&pGroupInfo, (DWORD)-1, &dwGroups, &dwGroup, (PDWORD_PTR)NULL) == NERR_Success)
		{
			for (dwGroup = 0; dwGroup < dwGroups; dwGroup++)
			{
				if ((pszGroupName = (LPTSTR)GlobalAlloc(GPTR, (wcslen(pGroupInfo[dwGroup].lgrpi0_name) + 1)*sizeof(TCHAR))))
				{
#ifdef UNICODE
					wcscpy_s(pszGroupName, wcslen(pGroupInfo[dwGroup].lgrpi0_name) + 1, pGroupInfo[dwGroup].lgrpi0_name);
#else
					WideCharToMultiByte(CP_ACP, 0, pGroupInfo[dwGroup].lgrpi0_name, -1, pszGroupName, (INT)wcslen(pGroupInfo[dwGroup].lgrpi0_name) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#endif
					szGroupNames.Add(pszGroupName);
					GlobalFree(pszGroupName);
					continue;
				}
				break;
			}
			if (dwGroup == dwGroups)
			{
				szGroups.Copy(szGroupNames);
				GlobalFree(pszServerName);
				NetApiBufferFree(pGroupInfo);
				return((INT)szGroupNames.GetSize());
			}
			NetApiBufferFree(pGroupInfo);
		}
		GlobalFree(pszServerName);
	}
	return 0;
}

INT CAccounts::EnumGroupMemberShips(LPCTSTR pszUserName, CStringArray &szGroups) CONST
{
	DWORD  dwGroup;
	DWORD  dwGroups;
	LPTSTR  pszGroupName;
	LPWSTR  pszAccountName;
	LPWSTR  pszServerName;
	CString  szDCName;
	CString  szServerName;
	CStringArray  szGroupNames;
	PLOCALGROUP_USERS_INFO_0  pGroupInfo;

	if ((pszServerName = (LPWSTR)GlobalAlloc(GPTR, ((szServerName = GetComputerUNCName()).GetLength() + 1)*sizeof(WCHAR))))
	{
#ifdef UNICODE
		wcscpy_s(pszServerName, szServerName.GetLength() + 1, szServerName);
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szServerName, -1, pszServerName, szServerName.GetLength() + 1);
#endif
		if ((pszAccountName = (LPWSTR)GlobalAlloc(GPTR, (lstrlen(pszUserName) + 1)*sizeof(WCHAR))))
		{
#ifdef UNICODE
			wcscpy_s(pszAccountName, lstrlen(pszUserName) + 1, pszUserName);
#else
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszUserName, -1, pszAccountName, lstrlen(pszUserName) + 1);
#endif
			if (NetUserGetLocalGroups(pszServerName, pszAccountName, 0, LG_INCLUDE_INDIRECT, (LPBYTE *)&pGroupInfo, (DWORD)-1, &dwGroups, &dwGroup) == NERR_Success)
			{
				for (dwGroup = 0; dwGroup < dwGroups; dwGroup++)
				{
					if ((pszGroupName = (LPTSTR)GlobalAlloc(GPTR, (wcslen(pGroupInfo[dwGroup].lgrui0_name) + 1)*sizeof(TCHAR))))
					{
#ifdef UNICODE
						wcscpy_s(pszGroupName, wcslen(pGroupInfo[dwGroup].lgrui0_name) + 1, pGroupInfo[dwGroup].lgrui0_name);
#else
						WideCharToMultiByte(CP_ACP, 0, pGroupInfo[dwGroup].lgrui0_name, -1, pszGroupName, (INT)wcslen(pGroupInfo[dwGroup].lgrui0_name) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#endif
						szGroupNames.Add(pszGroupName);
						GlobalFree(pszGroupName);
						continue;
					}
					break;
				}
				if (dwGroup == dwGroups)
				{
					szGroups.Copy(szGroupNames);
					GlobalFree(pszAccountName);
					GlobalFree(pszServerName);
					NetApiBufferFree(pGroupInfo);
					return((INT)szGroupNames.GetSize());
				}
				NetApiBufferFree(pGroupInfo);
			}
			GlobalFree(pszAccountName);
		}
		GlobalFree(pszServerName);
	}
	return 0;
}

INT CAccounts::EnumGroupMembers(LPCTSTR pszGroupName, CStringArray &szUsers) CONST
{
	DWORD  dwUser;
	DWORD  dwUsers;
	LPTSTR  pszUserName;
	LPWSTR  pszAccountName;
	LPWSTR  pszServerName;
	CString  szDCName;
	CString  szServerName;
	CStringArray  szUserNames;
	PLOCALGROUP_MEMBERS_INFO_1  pUserInfo;

	if ((pszServerName = (LPWSTR)GlobalAlloc(GPTR, ((szServerName = GetComputerUNCName()).GetLength() + 1)*sizeof(WCHAR))))
	{
#ifdef UNICODE
		wcscpy_s(pszServerName, szServerName.GetLength() + 1, szServerName);
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szServerName, -1, pszServerName, szServerName.GetLength() + 1);
#endif
		if ((pszAccountName = (LPWSTR)GlobalAlloc(GPTR, (lstrlen(pszGroupName) + 1)*sizeof(WCHAR))))
		{
#ifdef UNICODE
			wcscpy_s(pszAccountName, lstrlen(pszGroupName) + 1, pszGroupName);
#else
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pszGroupName, -1, pszAccountName, lstrlen(pszGroupName) + 1);
#endif
			if (NetLocalGroupGetMembers(pszServerName, pszAccountName, 1, (LPBYTE *)&pUserInfo, (DWORD)-1, &dwUsers, &dwUser, (PDWORD_PTR)NULL) == NERR_Success)
			{
				for (dwUser = 0; dwUser < dwUsers; dwUser++)
				{
					if ((pszUserName = (LPTSTR)GlobalAlloc(GPTR, (wcslen(pUserInfo[dwUser].lgrmi1_name) + 1)*sizeof(TCHAR))))
					{
#ifdef UNICODE
						wcscpy_s(pszUserName, wcslen(pUserInfo[dwUser].lgrmi1_name) + 1, pUserInfo[dwUser].lgrmi1_name);
#else
						WideCharToMultiByte(CP_ACP, 0, pUserInfo[dwUser].lgrmi1_name, -1, pszUserName, (INT)wcslen(pUserInfo[dwUser].lgrmi1_name) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#endif
						szUserNames.Add(pszUserName);
						GlobalFree(pszUserName);
						continue;
					}
					break;
				}
				if (dwUser == dwUsers)
				{
					szUsers.Copy(szUserNames);
					GlobalFree(pszAccountName);
					GlobalFree(pszServerName);
					NetApiBufferFree(pUserInfo);
					return((INT)szUserNames.GetSize());
				}
				NetApiBufferFree(pUserInfo);
			}
			GlobalFree(pszAccountName);
		}
		GlobalFree(pszServerName);
	}
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CUserAccounts

BOOL CUserAccounts::WriteAccount(CONST CAccountToken *pAccountToken)
{
	CString  szSubKey;
	CString  szAccount[3];
	CTimeKey  tValidity[2];
	CByteArray  nPassword[2];
	CUIntArray  nPrivileges;
	CCryptographyTools  cCryptographyTools;

	return((pAccountToken->GetOwner(szAccount[0], szAccount[1], szAccount[2]) && cCryptographyTools.EncryptText(pAccountToken->GetPassword(), nPassword[0]) > 0 && cCryptographyTools.EncryptText(pAccountToken->GetRASPassword(), nPassword[1]) > 0 && SetComputerName(szAccount[0]) && SecureSubKey(QueryAccountsSubKey()) && pAccountToken->GetPrivileges(nPrivileges) >= 0 && pAccountToken->GetValidity(tValidity[0], tValidity[1]) >= 0 && AddAccount(szAccount[0], szAccount[1], szAccount[2], FALSE) && WriteAccountMode((szSubKey = QueryUserAccountSubKey(szAccount[1], szAccount[2])), pAccountToken->GetMode()) && WriteAccountDatabase(szSubKey, pAccountToken->GetDatabase()) && WriteAccountPassword(szSubKey, nPassword[0]) && WriteAccountValidity(szSubKey, tValidity[0], tValidity[1]) && WriteAccountPrivileges(szSubKey, nPrivileges) && WriteAccountUniqueFlag(szSubKey, pAccountToken->IsUnique()) && WriteAccountRASServer(szSubKey, pAccountToken->GetRASServer()) && WriteAccountRASUserName(szSubKey, pAccountToken->GetRASUserName()) && WriteAccountRASPassword(szSubKey, nPassword[1])) ? TRUE : FALSE);
}

BOOL CUserAccounts::ReadAccount(CAccountToken *pAccountToken)
{
	UINT  nMode;
	BOOL  bUnique;
	BOOL  bEnabled;
	CString  szSubKey;
	CString  szDatabase;
	CString  szPassword;
	CString  szRASServer;
	CString  szRASUserName;
	CString  szRASPassword;
	CString  szAccount[3];
	CTimeKey  tValidity[2];
	CByteArray  nPassword[2];
	CUIntArray  nPrivileges;
	CCryptographyTools  cCryptographyTools;

	for (bEnabled = pAccountToken->EnablePrivileges(FALSE); pAccountToken->GetOwner(szAccount[0], szAccount[1], szAccount[2]); )
	{
		if (SetComputerName(szAccount[0]) && ReadAccountMode((szSubKey = QueryUserAccountSubKey(szAccount[1], szAccount[2])), nMode) && ReadAccountDatabase(szSubKey, szDatabase) && ReadAccountPassword(szSubKey, nPassword[0]) && ReadAccountValidity(szSubKey, tValidity[0], tValidity[1]) && ReadAccountPrivileges(szSubKey, nPrivileges) && ReadAccountUniqueFlag(szSubKey, bUnique) && ReadAccountRASServer(szSubKey, szRASServer) && ReadAccountRASUserName(szSubKey, szRASUserName) && ReadAccountRASPassword(szSubKey, nPassword[1]) && (!nPassword[0].GetSize() || cCryptographyTools.DecryptText(nPassword[0], szPassword)) && (!nPassword[1].GetSize() || cCryptographyTools.DecryptText(nPassword[1], szRASPassword)) && pAccountToken->SetMode(nMode) && pAccountToken->SetDatabase(szDatabase) && pAccountToken->SetPassword(szPassword) && pAccountToken->SetValidity(tValidity[0], tValidity[1]) && pAccountToken->SetPrivileges(nPrivileges) && pAccountToken->SetRASServer(szRASServer) && pAccountToken->SetRASUserName(szRASUserName) && pAccountToken->SetRASPassword(szRASPassword))
		{
			pAccountToken->SetUnique(bUnique);
			pAccountToken->EnablePrivileges(bEnabled);
			return TRUE;
		}
		break;
	}
	pAccountToken->SetUnique(FALSE);
	pAccountToken->EnablePrivileges(bEnabled);
	return FALSE;
}

BOOL CUserAccounts::FindAccount(CONST CAccountToken *pAccountToken)
{
	UINT  nMode;
	CString  szSubKey;
	CString  szAccount[3];
	CTimeKey  tValidity[2];
	CByteArray  nPassword;
	CUIntArray  nPrivileges;

	return((pAccountToken->GetOwner(szAccount[0], szAccount[1], szAccount[2]) && SetComputerName(szAccount[0]) && ReadAccountMode((szSubKey = QueryUserAccountSubKey(szAccount[1], szAccount[2])), nMode) && ReadAccountPassword(szSubKey, nPassword) && ReadAccountValidity(szSubKey, tValidity[0], tValidity[1]) && ReadAccountPrivileges(szSubKey, nPrivileges)) ? TRUE : FALSE);
}

BOOL CUserAccounts::RemoveAccount(CONST CAccountToken *pAccountToken)
{
	CString  szAccount[3];

	return((pAccountToken->GetOwner(szAccount[0], szAccount[1], szAccount[2]) && RemoveAccount(szAccount[0], szAccount[1], szAccount[2])) ? TRUE : FALSE);
}

BOOL CUserAccounts::SetActiveAccount(CONST CAccountToken *pAccountToken)
{
	CString  szAccount[3];

	return((pAccountToken->GetOwner(szAccount[0], szAccount[1], szAccount[2]) && AddAccount(szAccount[0], szAccount[1], szAccount[2])) ? TRUE : FALSE);
}

BOOL CUserAccounts::GetActiveAccount(CAccountToken *pAccountToken) CONST
{
	CStringArray  szAccounts[2];

	return((GetMachineInfo(QueryUserAccountsDirectorySubKey(), STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTACCOUNTS), szAccounts[0]) > 0 && GetMachineInfo(QueryUserAccountsSubKey(szAccounts[0].GetAt(0)), STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTS), szAccounts[1]) > 0 && pAccountToken->SetOwner(GetComputerName(), szAccounts[0].GetAt(0), szAccounts[1].GetAt(0))) ? TRUE : FALSE);
}

INT CUserAccounts::EnumAccounts(BOOL bExpired)
{
	CAccountTokens  pAccountTokens;

	return EnumAccounts(pAccountTokens, bExpired);
}
INT CUserAccounts::EnumAccounts(CAccountTokens &pAccountTokens, BOOL bExpired)
{
	INT  nAccount[2];
	INT  nAccounts[2];
	CTimeKey  tValidity[2];
	CStringArray  szAccounts[2];
	CAccountToken  *pAccountToken;

	for (nAccount[0] = 0, nAccounts[0] = GetMachineInfo(QueryUserAccountsDirectorySubKey(), STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTACCOUNTS), szAccounts[0]); nAccount[0] < nAccounts[0]; nAccount[0]++, szAccounts[1].RemoveAll())
	{
		for (nAccount[1] = 0, nAccounts[1] = GetMachineInfo(QueryUserAccountsSubKey(szAccounts[0].GetAt(nAccount[0])), STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTS), szAccounts[1]); nAccount[1] < nAccounts[1]; nAccount[1]++)
		{
			if ((pAccountToken = new CAccountToken) != (CAccountToken *)NULL  &&  pAccountToken->SetOwner(GetComputerName(), szAccounts[0].GetAt(nAccount[0]), szAccounts[1].GetAt(nAccount[1])))
			{
				if ((!bExpired  &&  ReadAccount(pAccountToken) && pAccountToken->GetValidity(tValidity[0], tValidity[1])) || (bExpired && (!ReadAccount(pAccountToken) || !pAccountToken->GetValidity(tValidity[0], tValidity[1]))))
				{
					pAccountTokens.Add(pAccountToken);
					continue;
				}
			}
			delete pAccountToken;
		}
	}
	return((INT)pAccountTokens.GetSize());
}

BOOL CUserAccounts::DeleteAccounts()
{
	return DeleteSubKey(QueryAccountsSubKey());
}

BOOL CUserAccounts::AddAccount(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bActive)
{
	INT  nAccount[2];
	INT  nAccounts[2];
	CStringArray  szAccounts[3];

	if (SetComputerName(pszComputerName))
	{
		for (nAccount[0] = 0, nAccounts[0] = GetMachineInfo(QueryUserAccountsDirectorySubKey(), STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTACCOUNTS), szAccounts[0]); nAccount[0] < nAccounts[0]; nAccount[0]++)
		{
			if (!szAccounts[0].GetAt(nAccount[0]).Compare(pszSpacecraftName))
			{
				for (szAccounts[2].Add(szAccounts[0].GetAt(nAccount[0])); bActive; )
				{
					szAccounts[0].RemoveAt(nAccount[0]);
					szAccounts[2].Append(szAccounts[0]);
					szAccounts[0].Copy(szAccounts[2]);
					break;
				}
				szAccounts[2].RemoveAll();
				break;
			}
		}
		for (nAccount[1] = 0, nAccounts[1] = GetMachineInfo(QueryUserAccountsSubKey(pszSpacecraftName), STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTS), szAccounts[1]); nAccount[1] < nAccounts[1]; nAccount[1]++)
		{
			if (!szAccounts[1].GetAt(nAccount[1]).Compare(pszUserName))
			{
				for (szAccounts[2].Add(szAccounts[1].GetAt(nAccount[1])); bActive; )
				{
					szAccounts[1].RemoveAt(nAccount[1]);
					szAccounts[2].Append(szAccounts[1]);
					szAccounts[1].Copy(szAccounts[2]);
					break;
				}
				szAccounts[2].RemoveAll();
				break;
			}
		}
		if (nAccounts[0] <= 0 || nAccount[0] == nAccounts[0])
		{
			for (szAccounts[2].Add(pszSpacecraftName); bActive; )
			{
				szAccounts[2].Append(szAccounts[0]);
				szAccounts[0].Copy(szAccounts[2]);
				break;
			}
			for (szAccounts[2].RemoveAll(); !bActive; )
			{
				szAccounts[0].Add(pszSpacecraftName);
				break;
			}
		}
		if (nAccounts[1] <= 0 || nAccount[1] == nAccounts[1])
		{
			for (szAccounts[2].Add(pszUserName); bActive; )
			{
				szAccounts[2].Append(szAccounts[1]);
				szAccounts[1].Copy(szAccounts[2]);
				break;
			}
			for (szAccounts[2].RemoveAll(); !bActive; )
			{
				szAccounts[1].Add(pszUserName);
				break;
			}
		}
		return SetMachineInfo(QueryUserAccountsDirectorySubKey(), STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTACCOUNTS), szAccounts[0]) && SetMachineInfo(QueryUserAccountsSubKey(pszSpacecraftName), STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTS), szAccounts[1]);
	}
	return FALSE;
}

BOOL CUserAccounts::RemoveAccount(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName)
{
	INT  nAccount[2];
	INT  nAccounts[2];
	CStringArray  szAccounts[2];

	if (SetComputerName(pszComputerName))
	{
		for (nAccount[1] = 0, nAccounts[1] = GetMachineInfo(QueryUserAccountsSubKey(pszSpacecraftName), STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTS), szAccounts[1]); nAccount[1] < nAccounts[1]; nAccount[1]++)
		{
			if (szAccounts[1].GetAt(nAccount[1]) == pszUserName)
			{
				szAccounts[1].RemoveAt(nAccount[1]);
				break;
			}
		}
		for (nAccount[0] = 0, nAccounts[0] = GetMachineInfo(QueryUserAccountsDirectorySubKey(), STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTACCOUNTS), szAccounts[0]); nAccount[0] < nAccounts[0]; nAccount[0]++)
		{
			if (szAccounts[0].GetAt(nAccount[0]) == pszSpacecraftName)
			{
				if (!szAccounts[1].GetSize()) szAccounts[0].RemoveAt(nAccount[0]);
				break;
			}
		}
		return((nAccount[0] < nAccounts[0] && nAccount[1] < nAccounts[1] && ((szAccounts[0].GetSize() && SetMachineInfo(QueryUserAccountsDirectorySubKey(), STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTACCOUNTS), szAccounts[0])) || (!szAccounts[0].GetSize() && SetMachineInfo(QueryUserAccountsDirectorySubKey(), STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTACCOUNTS)))) && ((szAccounts[1].GetSize() && SetMachineInfo(QueryUserAccountsSubKey(pszSpacecraftName), STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTS), szAccounts[1])) || (!szAccounts[1].GetSize() && SetMachineInfo(QueryUserAccountsSubKey(pszSpacecraftName), STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTS)))) && ((szAccounts[1].GetSize() && DeleteSubKey(QueryUserAccountSubKey(pszSpacecraftName, pszUserName))) || DeleteSubKey(QueryUserAccountsSubKey(pszSpacecraftName)))) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CUserAccounts::WriteAccountMode(LPCTSTR pszSubKey, UINT nMode)
{
	return SetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTMODE), nMode);
}

BOOL CUserAccounts::ReadAccountMode(LPCTSTR pszSubKey, UINT &nMode) CONST
{
	DWORD  dwMode;

	if (GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTMODE), dwMode))
	{
		nMode = dwMode;
		return TRUE;
	}
	return FALSE;
}

BOOL CUserAccounts::WriteAccountDatabase(LPCTSTR pszSubKey, LPCTSTR pszDatabase)
{
	return((lstrlen(pszDatabase)) ? SetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTDATABASE), pszDatabase) : TRUE);
}

BOOL CUserAccounts::ReadAccountDatabase(LPCTSTR pszSubKey, CString &szDatabase) CONST
{
	if (!GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTDATABASE), szDatabase)) szDatabase.Empty();
	return TRUE;
}

BOOL CUserAccounts::WriteAccountPassword(LPCTSTR pszSubKey, CONST CByteArray &nPassword)
{
	return SetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTPASSWORD), REG_BINARY, nPassword.GetData(), (INT)nPassword.GetSize());
}

BOOL CUserAccounts::ReadAccountPassword(LPCTSTR pszSubKey, CByteArray &nPassword) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTPASSWORD)), nPassword.SetSize(max(nSize, 0)); nSize > 0 && nPassword.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTPASSWORD), &dwType, nPassword.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CUserAccounts::WriteAccountValidity(LPCTSTR pszSubKey, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	CStringArray  szValidity;
	CStringTools  cStringTools;

	szValidity.Add(cStringTools.ConvertLongIntToString(tStartTime.GetTime()));
	szValidity.Add(cStringTools.ConvertLongIntToString(tStopTime.GetTime()));
	return SetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTVALIDITY), szValidity);
}

BOOL CUserAccounts::ReadAccountValidity(LPCTSTR pszSubKey, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CStringArray  szValidity;

	if (GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTVALIDITY), szValidity) - 1 == 1)
	{
		tStartTime = _ttoi64(szValidity.GetAt(0));
		tStopTime = _ttoi64(szValidity.GetAt(1));
		return TRUE;
	}
	return FALSE;
}

BOOL CUserAccounts::WriteAccountPrivileges(LPCTSTR pszSubKey, CONST CUIntArray &nPrivileges)
{
	return SetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTPRIVILEGES), REG_BINARY, (nPrivileges.GetSize()) ? (CONST BYTE *) nPrivileges.GetData() : (CONST BYTE *) EMPTYSTRING, (INT)nPrivileges.GetSize()*sizeof(UINT));
}

BOOL CUserAccounts::ReadAccountPrivileges(LPCTSTR pszSubKey, CUIntArray &nPrivileges) CONST
{
	INT  cbPrivileges;
	DWORD  dwPrivileges;

	if ((cbPrivileges = GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTPRIVILEGES))) >= 0)
	{
		nPrivileges.SetSize(cbPrivileges / sizeof(UINT));
		return((nPrivileges.GetSize() == cbPrivileges / sizeof(UINT) && GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTPRIVILEGES), &dwPrivileges, (LPBYTE)nPrivileges.GetData(), cbPrivileges) == cbPrivileges) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CUserAccounts::WriteAccountUniqueFlag(LPCTSTR pszSubKey, BOOL bUnique)
{
	return SetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTUNIQUEFLAG), bUnique);
}

BOOL CUserAccounts::ReadAccountUniqueFlag(LPCTSTR pszSubKey, BOOL &bUnique) CONST
{
	DWORD  dwFlag;

	for (bUnique = FALSE; GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTUNIQUEFLAG), dwFlag); )
	{
		bUnique = (BOOL)dwFlag;
		break;
	}
	return TRUE;
}

BOOL CUserAccounts::WriteAccountRASServer(LPCTSTR pszSubKey, LPCTSTR pszServer)
{
	return((lstrlen(pszServer)) ? SetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTRASSERVER), pszServer) : TRUE);
}

BOOL CUserAccounts::ReadAccountRASServer(LPCTSTR pszSubKey, CString &szServer) CONST
{
	if (!GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTRASSERVER), szServer)) szServer.Empty();
	return TRUE;
}

BOOL CUserAccounts::WriteAccountRASUserName(LPCTSTR pszSubKey, LPCTSTR pszUserName)
{
	return((lstrlen(pszUserName)) ? SetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTRASUSERNAME), pszUserName) : TRUE);
}

BOOL CUserAccounts::ReadAccountRASUserName(LPCTSTR pszSubKey, CString &szUserName) CONST
{
	if (!GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTRASUSERNAME), szUserName)) szUserName.Empty();
	return TRUE;
}

BOOL CUserAccounts::WriteAccountRASPassword(LPCTSTR pszSubKey, CONST CByteArray &nPassword)
{
	return SetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTRASPASSWORD), REG_BINARY, nPassword.GetData(), (INT)nPassword.GetSize());
}

BOOL CUserAccounts::ReadAccountRASPassword(LPCTSTR pszSubKey, CByteArray &nPassword) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTRASPASSWORD)), nPassword.SetSize(max(nSize, 0)); nSize > 0 && nPassword.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetMachineInfo(pszSubKey, STRING(IDS_REG_SUBKEYVALUE_USERACCOUNTRASPASSWORD), &dwType, nPassword.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

CString CUserAccounts::QueryAccountsSubKey() CONST
{
	CString  szSubKey;
	CVersionInfo  cVersionInfo;

	szSubKey = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName();
	return szSubKey;
}

CString CUserAccounts::QueryUserAccountsDirectorySubKey() CONST
{
	CString  szSubKey;
	CVersionInfo  cVersionInfo;

	szSubKey = QueryAccountsSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + cVersionInfo.QueryProductName();
	return szSubKey;
}

CString CUserAccounts::QueryUserAccountsSubKey(LPCTSTR pszSpacecraftName) CONST
{
	CString  szSubKey;

	szSubKey = QueryUserAccountsDirectorySubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + pszSpacecraftName;
	return szSubKey;
}

CString CUserAccounts::QueryUserAccountSubKey(LPCTSTR pszSpacecraftName, LPCTSTR pszUserName) CONST
{
	CString  szSubKey;

	szSubKey = QueryUserAccountsSubKey(pszSpacecraftName) + STRING(IDS_REG_SUBKEYPART_DELIMITER) + pszUserName;
	return szSubKey;
}

BOOL CUserAccounts::SecureSubKey(LPCTSTR pszSubKey)
{
	CSecurityDescriptor  cSecurityDescriptor;

	return((cSecurityDescriptor.SetRightsOfSystem(KEY_ALL_ACCESS, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfOwner(KEY_ALL_ACCESS, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfAdministrators(KEY_ALL_ACCESS, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfEveryone(KEY_READ, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE)) ? ((SetMachineInfo(pszSubKey, EMPTYSTRING) && SetMachineSecurity(pszSubKey, cSecurityDescriptor)) ? TRUE : FALSE) : FALSE);
}

BOOL CUserAccounts::DeleteSubKey(LPCTSTR pszSubKey)
{
	INT  nSubKey;
	INT  nSubKeys;
	CStringArray  szSubKeys;

	for (nSubKey = 0, nSubKeys = EnumMachineSubKeys(pszSubKey, szSubKeys); nSubKey < nSubKeys; nSubKey++)
	{
		if (DeleteSubKey(CString(CString(pszSubKey) + STRING(IDS_REG_SUBKEYPART_DELIMITER)) + szSubKeys.GetAt(nSubKey))) continue;
		break;
	}
	return((nSubKey == nSubKeys  &&  SetMachineInfo(pszSubKey)) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CAccountsApp

IMPLEMENT_DYNAMIC(CAccountsApp, CLocaleApp)

CAccountsApp::CAccountsApp() : CLocaleApp()
{
	CToken  cToken;

	m_pCriticalSection = new CCriticalSection;
	m_pAccountToken = new CAccountToken(cToken.GetComputerName(), cToken.GetSpacecraftName(), cToken.GetUserName());
}

CAccountsApp::~CAccountsApp()
{
	if (m_pAccountToken != (CAccountToken *)NULL) delete m_pAccountToken;
	delete m_pCriticalSection;
}

BOOL CAccountsApp::InitInstance()
{
	INT  nUser;
	INT  nUsers;
	INT  nAccount;
	INT  nAccounts;
	DWORD  cbUser;
	TCHAR  szUser[UNLEN + 1];
	CString  szAccount[3];
	CString  szModuleName;
	CUserToken  cUserToken;
	CStringArray  szUsers;
	CStringArray  szSubKeys;
	CModuleToken  cModuleToken;
	CUserAccounts  cUserAccounts;
	CAccountToken  *pAccountToken;
	CAccountTokens  pAccountTokens;
	CComputerToken  cComputerToken;
	PROCESS_INFORMATION  sProcessInfo;
	STARTUPINFO  sStartupInfo;
	CRegistry  cRegistry;
	CAccounts  cUsers;
	HANDLE  hAccount;

	if (CLocaleApp::InitInstance())
	{
		if (GetUserName(szUser, &(cbUser = sizeof(szUser) / sizeof(TCHAR))) > 0)
		{
			for (cUserToken.SetUserName(szUser); !cUserToken.IsAdministrator(); )
			{
				for (nAccount = 0, nAccounts = cUserAccounts.EnumAccounts(pAccountTokens); nAccount < nAccounts; nAccount++)
				{
					for (nUser = 0, nUsers = ((pAccountToken = pAccountTokens.GetAt(nAccount)) && pAccountToken->IsAdministrator()) ? cUsers.EnumUsers(szUsers) : 0; nUser < nUsers; nUser++)
					{
						for (cUserToken.SetUserName(szUsers.GetAt(nUser)); cUserToken.IsAdministrator() && LogonUser(cUserToken.GetUserName(), (LPCTSTR)NULL, pAccountToken->GetPassword(), LOGON32_LOGON_NEW_CREDENTIALS, LOGON32_PROVIDER_WINNT50, &hAccount); )
						{
							if (cRegistry.EnumUserSubKeys(STRING(IDS_REG_SUBKEYPART_ROOTKEY) + GetAppRegKey(), szSubKeys) >= 0)
							{
								ZeroMemory(&sStartupInfo, sizeof(STARTUPINFO));
								sStartupInfo.cb = sizeof(sStartupInfo);
#ifndef UNICODE
								MultiByteToWideChar(CP_ACP, 0, szUsers.GetAt(nUser), -1, szAccount[0].GetBufferSetLength(szUsers.GetAt(nUser).GetLength()), szUsers.GetAt(nUser).GetLength() + 1);
								MultiByteToWideChar(CP_ACP, 0, pAccountToken->GetPassword(), -1, szAccount[1].GetBufferSetLength(pAccountToken->GetPassword().GetLength()), pAccountToken->GetPassword().GetLength() + 1);
								MultiByteToWideChar(CP_ACP, 0, cComputerToken.GetComputerName(), -1, szAccount[2].GetBufferSetLength(cComputerToken.GetComputerName().GetLength()), cComputerToken.GetComputerName().GetLength() + 1);
								MultiByteToWideChar(CP_ACP, 0, cModuleToken.GetModuleFileName(), -1, szModuleName.GetBufferSetLength(cModuleToken.GetModuleFileName().GetLength()), cModuleToken.GetModuleFileName().GetLength() + 1);
								szAccount[0].ReleaseBuffer();
								szAccount[1].ReleaseBuffer();
								szAccount[2].ReleaseBuffer();
								szModuleName.ReleaseBuffer();
#else
								szAccount[0] = szUsers.GetAt(nUser);
								szAccount[1] = pAccountToken->GetPassword();
								szAccount[2] = cComputerToken.GetComputerName();
								szModuleName = cModuleToken.GetModuleFileName();
#endif
								for (RevertToSelf(), CloseHandle(hAccount); CreateProcessWithLogonW(szAccount[0], szAccount[2], szAccount[1], LOGON_WITH_PROFILE, szModuleName, (LPWSTR)NULL, 0, (LPVOID)NULL, (LPCWSTR)NULL, &sStartupInfo, &sProcessInfo); ) return FALSE;
							}
							RevertToSelf();
							CloseHandle(hAccount);
							break;
						}
					}
				}
				return FALSE;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CAccountsApp::RegisterApp()
{
	INT  nPath;
	INT  nPaths;
	CString  szPath;
	CString  szSubKey;
	CStringArray  szAccessPaths;
	CVersionInfo  cVersionInfo;
	CRegistry  cRegistry;

	for (nPath = 0, nPaths = cRegistry.GetMachineInfo((szSubKey = STRING(IDS_REG_SUBKEY_ACCESSPATH)), STRING(IDS_REG_SUBKEYVALUE_ACCESSPATHTYPE), szAccessPaths), szPath = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + cVersionInfo.QueryProductName(); nPath < nPaths; nPath++)
	{
		if (szAccessPaths.GetAt(nPath) == szPath) break;
		continue;
	}
	if (nPath == nPaths) szAccessPaths.Add(szPath);
	return((nPaths < 0 || nPath < nPaths || (cRegistry.SetMachineInfo(STRING(IDS_REG_SUBKEY_UACPATH), STRING(IDS_REG_SUBKEYVALUE_UACTOKENPOLICY), 1) && cRegistry.SetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_ACCESSPATHTYPE), szAccessPaths))) ? TRUE : FALSE);
}

BOOL CAccountsApp::UnregisterApp(BOOL bAll)
{
	INT  nPath;
	INT  nPaths;
	CString  szPath;
	CString  szSubKey;
	CStringArray  szAccessPaths;
	CVersionInfo  cVersionInfo;
	CRegistry  cRegistry;

	for (nPath = 0, nPaths = cRegistry.GetMachineInfo((szSubKey = STRING(IDS_REG_SUBKEY_ACCESSPATH)), STRING(IDS_REG_SUBKEYVALUE_ACCESSPATHTYPE), szAccessPaths), szPath = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + cVersionInfo.QueryProductName(); nPath < nPaths; nPath++)
	{
		if (szAccessPaths.GetAt(nPath) == szPath) break;
		continue;
	}
	if (nPath < nPaths) szAccessPaths.RemoveAt(nPath);
	return((!bAll || nPaths < 0 || nPath == nPaths || (cRegistry.SetMachineInfo(STRING(IDS_REG_SUBKEY_UACPATH), STRING(IDS_REG_SUBKEYVALUE_UACTOKENPOLICY)) && cRegistry.SetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_ACCESSPATHTYPE), szAccessPaths))) ? TRUE : FALSE);
}

BOOL CAccountsApp::SaveAccount()
{
	CUserAccounts  cUserAccounts;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(cUserAccounts.WriteAccount(m_pAccountToken) && cUserAccounts.SetActiveAccount(m_pAccountToken));
}

BOOL CAccountsApp::TestAccount() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->HasOwner();
}

BOOL CAccountsApp::LoadAccount()
{
	CUserAccounts  cUserAccounts;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (!cUserAccounts.GetActiveAccount(m_pAccountToken) || !cUserAccounts.ReadAccount(m_pAccountToken) || !ValidateAccount(m_pAccountToken)) ValidateAccount(FALSE);
	return TRUE;
}
BOOL CAccountsApp::LoadAccount(CONST CAccountToken *pAccountToken)
{
	CUserAccounts  cUserAccounts;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (!m_pAccountToken->SetOwner(pAccountToken) || !cUserAccounts.ReadAccount(m_pAccountToken) || !ValidateAccount(m_pAccountToken))
	{
		ValidateAccount(FALSE);
		return FALSE;
	}
	return TRUE;
}

VOID CAccountsApp::SetAccount(CONST CAccountToken *pAccountToken)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_pAccountToken->Copy(pAccountToken);
}

VOID CAccountsApp::GetAccount(CAccountToken *pAccountToken) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	pAccountToken->Copy(m_pAccountToken);
}

BOOL CAccountsApp::ValidateAccount(CONST CAccountToken *pAccountToken)
{
	CTimeKey  tValidity[2];

	return((pAccountToken->HasOwner() && pAccountToken->GetValidity(tValidity[0], tValidity[1])) ? TRUE : FALSE);
}
BOOL CAccountsApp::ValidateAccount(BOOL bValidate)
{
	CAccountToken  cAccountToken(EMPTYSTRING, EMPTYSTRING, EMPTYSTRING);

	if (bValidate)
	{
		GetAccount(&cAccountToken);
		return ValidateAccount(&cAccountToken);
	}
	SetAccount(&cAccountToken);
	return TRUE;
}

CString CAccountsApp::GetAccountComputerName() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->GetComputerName();
}

CString CAccountsApp::GetAccountSpacecraftName() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->GetSpacecraftName();
}

CString CAccountsApp::GetAccountUserName() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->GetUserName();
}

CString CAccountsApp::GetAccountDatabase() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->GetDatabase();
}

CString CAccountsApp::GetAccountPassword() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->GetPassword();
}

CString CAccountsApp::GetAccountRASServer() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->GetRASServer();
}

CString CAccountsApp::GetAccountRASUserName() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->GetRASUserName();
}

CString CAccountsApp::GetAccountRASPassword() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->GetRASPassword();
}

INT CAccountsApp::GetAccountPrivileges(CUIntArray &nPrivileges) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->GetPrivileges(nPrivileges);
}

UINT CAccountsApp::GetAccountMode() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->GetMode();
}

BOOL CAccountsApp::IsAccountUnique() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->IsUnique();
}

BOOL CAccountsApp::CheckAccountOwner() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->HasOwner();
}
BOOL CAccountsApp::CheckAccountOwner(CONST CAccountToken *pAccountToken) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->HasSameOwner(pAccountToken);
}

BOOL CAccountsApp::CheckAccountPrivilege(UINT nPrivilege) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pAccountToken->CheckPrivilege(nPrivilege);
}

BOOL CAccountsApp::IsInitialized() CONST
{
	CUserAccounts  cUserAccounts;
	CAccountTokens  pAccountTokens;

	return((cUserAccounts.EnumAccounts(pAccountTokens) > 0) ? TRUE : FALSE);
}

BOOL CAccountsApp::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CAccountsApp::Unlock()
{
	return m_pCriticalSection->Unlock();
}

BEGIN_MESSAGE_MAP(CAccountsApp, CLocaleApp)
	//{{AFX_MSG_MAP(CAccountsApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountsApp message handlers
