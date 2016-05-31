// SECURITY.CPP : Security Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the security related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1997/12/11 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CSecurityDescriptor

BOOL CSecurityDescriptor::SetRightsOfSystem(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_LOCAL_SYSTEM_RID);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfSystem(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_LOCAL_SYSTEM_RID);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfService(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_SERVICE_RID);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfService(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_SERVICE_RID);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfLocalService(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_LOCAL_SERVICE_RID);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfLocalService(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_LOCAL_SERVICE_RID);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfNetworkService(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_NETWORK_SERVICE_RID);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfNetworkService(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_NETWORK_SERVICE_RID);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfOwner(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_CREATOR_SID_AUTHORITY;

	nSubAuthorities.Add(SECURITY_CREATOR_OWNER_RID);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfOwner(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_CREATOR_SID_AUTHORITY;

	nSubAuthorities.Add(SECURITY_CREATOR_OWNER_RID);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfDomainAdministrators(DWORD dwAccessMask, BYTE nFlags)
{
	HANDLE  hToken;
	DWORD  cbToken;
	DWORD  dwTokenGroup;
	DWORD  dwTokenSubAuth;
	DWORD  dwTokenSubAuths;
	DWORD  dwTokenSubAuthID;
	DWORD  dwTokenFoundSubAuths;
	PTOKEN_GROUPS  pTokenGroups;
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		if (GetTokenInformation(hToken, TokenGroups, (LPVOID)NULL, 0, &cbToken))
		{
			if ((pTokenGroups = (PTOKEN_GROUPS)GlobalAlloc(GPTR, cbToken)))
			{
				if (GetTokenInformation(hToken, TokenGroups, pTokenGroups, cbToken, &cbToken))
				{
					for (dwTokenGroup = 0; dwTokenGroup < pTokenGroups->GroupCount; dwTokenGroup++)
					{
						for (dwTokenSubAuth = 0, CopyMemory(&dwTokenSubAuths, GetSidSubAuthorityCount(pTokenGroups->Groups[dwTokenGroup].Sid), sizeof(UCHAR)), dwTokenSubAuths = LOBYTE(LOWORD(dwTokenSubAuths)), dwTokenFoundSubAuths = 0, nSubAuthorities.RemoveAll(); dwTokenSubAuth < dwTokenSubAuths; dwTokenSubAuth++)
						{
							CopyMemory(&dwTokenSubAuthID, GetSidSubAuthority(pTokenGroups->Groups[dwTokenGroup].Sid, dwTokenSubAuth), sizeof(DWORD));
							dwTokenFoundSubAuths = (dwTokenSubAuthID == SECURITY_NT_NON_UNIQUE || dwTokenSubAuthID == DOMAIN_GROUP_RID_ADMINS) ? (dwTokenFoundSubAuths + 1) : dwTokenFoundSubAuths;
							nSubAuthorities.Add(dwTokenSubAuthID);
						}
						if (dwTokenFoundSubAuths >= 2) break;
					}
					if (dwTokenGroup < pTokenGroups->GroupCount)
					{
						if (SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags))
						{
							GlobalFree(pTokenGroups);
							CloseHandle(hToken);
							return TRUE;
						}
					}
				}
				GlobalFree(pTokenGroups);
			}
		}
		CloseHandle(hToken);
	}
	return FALSE;
}

BOOL CSecurityDescriptor::GetRightsOfDomainAdministrators(DWORD &dwAccessMask) CONST
{
	HANDLE  hToken;
	DWORD  cbToken;
	DWORD  dwTokenGroup;
	DWORD  dwTokenSubAuth;
	DWORD  dwTokenSubAuths;
	DWORD  dwTokenSubAuthID;
	DWORD  dwTokenFoundSubAuths;
	PTOKEN_GROUPS  pTokenGroups;
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		if (GetTokenInformation(hToken, TokenGroups, (LPVOID)NULL, 0, &cbToken))
		{
			if ((pTokenGroups = (PTOKEN_GROUPS)GlobalAlloc(GPTR, cbToken)))
			{
				if (GetTokenInformation(hToken, TokenGroups, pTokenGroups, cbToken, &cbToken))
				{
					for (dwTokenGroup = 0; dwTokenGroup < pTokenGroups->GroupCount; dwTokenGroup++)
					{
						for (dwTokenSubAuth = 0, CopyMemory(&dwTokenSubAuths, GetSidSubAuthorityCount(pTokenGroups->Groups[dwTokenGroup].Sid), sizeof(UCHAR)), dwTokenSubAuths = LOBYTE(LOWORD(dwTokenSubAuths)), dwTokenFoundSubAuths = 0, nSubAuthorities.RemoveAll(); dwTokenSubAuth < dwTokenSubAuths; dwTokenSubAuth++)
						{
							CopyMemory(&dwTokenSubAuthID, GetSidSubAuthority(pTokenGroups->Groups[dwTokenGroup].Sid, dwTokenSubAuth), sizeof(DWORD));
							dwTokenFoundSubAuths = (dwTokenSubAuthID == SECURITY_NT_NON_UNIQUE || dwTokenSubAuthID == DOMAIN_GROUP_RID_ADMINS) ? (dwTokenFoundSubAuths + 1) : dwTokenFoundSubAuths;
							nSubAuthorities.Add(dwTokenSubAuthID);
						}
						if (dwTokenFoundSubAuths >= 2) break;
					}
					if (dwTokenGroup < pTokenGroups->GroupCount)
					{
						if (GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask))
						{
							GlobalFree(pTokenGroups);
							CloseHandle(hToken);
							return TRUE;
						}
					}
				}
				GlobalFree(pTokenGroups);
			}
		}
		CloseHandle(hToken);
	}
	return FALSE;
}

BOOL CSecurityDescriptor::SetRightsOfDomainUsers(DWORD dwAccessMask, BYTE nFlags)
{
	HANDLE  hToken;
	DWORD  cbToken;
	DWORD  dwTokenGroup;
	DWORD  dwTokenSubAuth;
	DWORD  dwTokenSubAuths;
	DWORD  dwTokenSubAuthID;
	DWORD  dwTokenFoundSubAuths;
	PTOKEN_GROUPS  pTokenGroups;
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		if (GetTokenInformation(hToken, TokenGroups, (LPVOID)NULL, 0, &cbToken))
		{
			if ((pTokenGroups = (PTOKEN_GROUPS)GlobalAlloc(GPTR, cbToken)))
			{
				if (GetTokenInformation(hToken, TokenGroups, pTokenGroups, cbToken, &cbToken))
				{
					for (dwTokenGroup = 0; dwTokenGroup < pTokenGroups->GroupCount; dwTokenGroup++)
					{
						for (dwTokenSubAuth = 0, CopyMemory(&dwTokenSubAuths, GetSidSubAuthorityCount(pTokenGroups->Groups[dwTokenGroup].Sid), sizeof(UCHAR)), dwTokenSubAuths = LOBYTE(LOWORD(dwTokenSubAuths)), dwTokenFoundSubAuths = 0, nSubAuthorities.RemoveAll(); dwTokenSubAuth < dwTokenSubAuths; dwTokenSubAuth++)
						{
							CopyMemory(&dwTokenSubAuthID, GetSidSubAuthority(pTokenGroups->Groups[dwTokenGroup].Sid, dwTokenSubAuth), sizeof(DWORD));
							dwTokenFoundSubAuths = (dwTokenSubAuthID == SECURITY_NT_NON_UNIQUE || dwTokenSubAuthID == DOMAIN_GROUP_RID_USERS) ? (dwTokenFoundSubAuths + 1) : dwTokenFoundSubAuths;
							nSubAuthorities.Add(dwTokenSubAuthID);
						}
						if (dwTokenFoundSubAuths >= 2) break;
					}
					if (dwTokenGroup < pTokenGroups->GroupCount)
					{
						if (SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags))
						{
							GlobalFree(pTokenGroups);
							CloseHandle(hToken);
							return TRUE;
						}
					}
				}
				GlobalFree(pTokenGroups);
			}
		}
		CloseHandle(hToken);
	}
	return FALSE;
}

BOOL CSecurityDescriptor::GetRightsOfDomainUsers(DWORD &dwAccessMask) CONST
{
	HANDLE  hToken;
	DWORD  cbToken;
	DWORD  dwTokenGroup;
	DWORD  dwTokenSubAuth;
	DWORD  dwTokenSubAuths;
	DWORD  dwTokenSubAuthID;
	DWORD  dwTokenFoundSubAuths;
	PTOKEN_GROUPS  pTokenGroups;
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		if (GetTokenInformation(hToken, TokenGroups, (LPVOID)NULL, 0, &cbToken))
		{
			if ((pTokenGroups = (PTOKEN_GROUPS)GlobalAlloc(GPTR, cbToken)))
			{
				if (GetTokenInformation(hToken, TokenGroups, pTokenGroups, cbToken, &cbToken))
				{
					for (dwTokenGroup = 0; dwTokenGroup < pTokenGroups->GroupCount; dwTokenGroup++)
					{
						for (dwTokenSubAuth = 0, CopyMemory(&dwTokenSubAuths, GetSidSubAuthorityCount(pTokenGroups->Groups[dwTokenGroup].Sid), sizeof(UCHAR)), dwTokenSubAuths = LOBYTE(LOWORD(dwTokenSubAuths)), dwTokenFoundSubAuths = 0, nSubAuthorities.RemoveAll(); dwTokenSubAuth < dwTokenSubAuths; dwTokenSubAuth++)
						{
							CopyMemory(&dwTokenSubAuthID, GetSidSubAuthority(pTokenGroups->Groups[dwTokenGroup].Sid, dwTokenSubAuth), sizeof(DWORD));
							dwTokenFoundSubAuths = (dwTokenSubAuthID == SECURITY_NT_NON_UNIQUE || dwTokenSubAuthID == DOMAIN_GROUP_RID_USERS) ? (dwTokenFoundSubAuths + 1) : dwTokenFoundSubAuths;
							nSubAuthorities.Add(dwTokenSubAuthID);
						}
						if (dwTokenFoundSubAuths >= 2) break;
					}
					if (dwTokenGroup < pTokenGroups->GroupCount)
					{
						if (GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask))
						{
							GlobalFree(pTokenGroups);
							CloseHandle(hToken);
							return TRUE;
						}
					}
				}
				GlobalFree(pTokenGroups);
			}
		}
		CloseHandle(hToken);
	}
	return FALSE;
}

BOOL CSecurityDescriptor::SetRightsOfDomainGuests(DWORD dwAccessMask, BYTE nFlags)
{
	HANDLE  hToken;
	DWORD  cbToken;
	DWORD  dwTokenGroup;
	DWORD  dwTokenSubAuth;
	DWORD  dwTokenSubAuths;
	DWORD  dwTokenSubAuthID;
	DWORD  dwTokenFoundSubAuths;
	PTOKEN_GROUPS  pTokenGroups;
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		if (GetTokenInformation(hToken, TokenGroups, (LPVOID)NULL, 0, &cbToken))
		{
			if ((pTokenGroups = (PTOKEN_GROUPS)GlobalAlloc(GPTR, cbToken)))
			{
				if (GetTokenInformation(hToken, TokenGroups, pTokenGroups, cbToken, &cbToken))
				{
					for (dwTokenGroup = 0; dwTokenGroup < pTokenGroups->GroupCount; dwTokenGroup++)
					{
						for (dwTokenSubAuth = 0, CopyMemory(&dwTokenSubAuths, GetSidSubAuthorityCount(pTokenGroups->Groups[dwTokenGroup].Sid), sizeof(UCHAR)), dwTokenSubAuths = LOBYTE(LOWORD(dwTokenSubAuths)), dwTokenFoundSubAuths = 0, nSubAuthorities.RemoveAll(); dwTokenSubAuth < dwTokenSubAuths; dwTokenSubAuth++)
						{
							CopyMemory(&dwTokenSubAuthID, GetSidSubAuthority(pTokenGroups->Groups[dwTokenGroup].Sid, dwTokenSubAuth), sizeof(DWORD));
							dwTokenFoundSubAuths = (dwTokenSubAuthID == SECURITY_NT_NON_UNIQUE || dwTokenSubAuthID == DOMAIN_GROUP_RID_GUESTS) ? (dwTokenFoundSubAuths + 1) : dwTokenFoundSubAuths;
							nSubAuthorities.Add(dwTokenSubAuthID);
						}
						if (dwTokenFoundSubAuths >= 2) break;
					}
					if (dwTokenGroup < pTokenGroups->GroupCount)
					{
						if (SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags))
						{
							GlobalFree(pTokenGroups);
							CloseHandle(hToken);
							return TRUE;
						}
					}
				}
				GlobalFree(pTokenGroups);
			}
		}
		CloseHandle(hToken);
	}
	return FALSE;
}

BOOL CSecurityDescriptor::GetRightsOfDomainGuests(DWORD &dwAccessMask) CONST
{
	HANDLE  hToken;
	DWORD  cbToken;
	DWORD  dwTokenGroup;
	DWORD  dwTokenSubAuth;
	DWORD  dwTokenSubAuths;
	DWORD  dwTokenSubAuthID;
	DWORD  dwTokenFoundSubAuths;
	PTOKEN_GROUPS  pTokenGroups;
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		if (GetTokenInformation(hToken, TokenGroups, (LPVOID)NULL, 0, &cbToken))
		{
			if ((pTokenGroups = (PTOKEN_GROUPS)GlobalAlloc(GPTR, cbToken)))
			{
				if (GetTokenInformation(hToken, TokenGroups, pTokenGroups, cbToken, &cbToken))
				{
					for (dwTokenGroup = 0; dwTokenGroup < pTokenGroups->GroupCount; dwTokenGroup++)
					{
						for (dwTokenSubAuth = 0, CopyMemory(&dwTokenSubAuths, GetSidSubAuthorityCount(pTokenGroups->Groups[dwTokenGroup].Sid), sizeof(UCHAR)), dwTokenSubAuths = LOBYTE(LOWORD(dwTokenSubAuths)), dwTokenFoundSubAuths = 0, nSubAuthorities.RemoveAll(); dwTokenSubAuth < dwTokenSubAuths; dwTokenSubAuth++)
						{
							CopyMemory(&dwTokenSubAuthID, GetSidSubAuthority(pTokenGroups->Groups[dwTokenGroup].Sid, dwTokenSubAuth), sizeof(DWORD));
							dwTokenFoundSubAuths = (dwTokenSubAuthID == SECURITY_NT_NON_UNIQUE || dwTokenSubAuthID == DOMAIN_GROUP_RID_GUESTS) ? (dwTokenFoundSubAuths + 1) : dwTokenFoundSubAuths;
							nSubAuthorities.Add(dwTokenSubAuthID);
						}
						if (dwTokenFoundSubAuths >= 2) break;
					}
					if (dwTokenGroup < pTokenGroups->GroupCount)
					{
						if (GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask))
						{
							GlobalFree(pTokenGroups);
							CloseHandle(hToken);
							return TRUE;
						}
					}
				}
				GlobalFree(pTokenGroups);
			}
		}
		CloseHandle(hToken);
	}
	return FALSE;
}

BOOL CSecurityDescriptor::SetRightsOfAdministrators(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_ADMINS);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfAdministrators(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_ADMINS);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfPowerUsers(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_POWER_USERS);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfPowerUsers(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_POWER_USERS);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfUsers(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_USERS);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfUsers(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_USERS);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfGuests(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_GUESTS);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfGuests(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_GUESTS);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfEveryone(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_WORLD_SID_AUTHORITY;

	nSubAuthorities.Add(SECURITY_WORLD_RID);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfEveryone(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_WORLD_SID_AUTHORITY;

	nSubAuthorities.Add(SECURITY_WORLD_RID);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfAuthenticatedUsers(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_NETWORK_RID | SECURITY_SERVER_LOGON_RID);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfAuthenticatedUsers(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_NETWORK_RID | SECURITY_SERVER_LOGON_RID);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfInteractiveUsers(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_INTERACTIVE_RID);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfInteractiveUsers(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_INTERACTIVE_RID);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfNetworkUsers(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_NETWORK_RID);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfNetworkUsers(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_NETWORK_RID);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfSystemOperators(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_SYSTEM_OPS);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfSystemOperators(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_SYSTEM_OPS);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfAccountOperators(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_ACCOUNT_OPS);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfAccountOperators(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_ACCOUNT_OPS);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfBackupOperators(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_BACKUP_OPS);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfBackupOperators(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_BACKUP_OPS);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfPrintOperators(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_PRINT_OPS);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfPrintOperators(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_PRINT_OPS);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::SetRightsOfReplicators(DWORD dwAccessMask, BYTE nFlags)
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_REPLICATOR);
	return SetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask, nFlags);
}

BOOL CSecurityDescriptor::GetRightsOfReplicators(DWORD &dwAccessMask) CONST
{
	CDWordArray  nSubAuthorities;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	nSubAuthorities.Add(SECURITY_BUILTIN_DOMAIN_RID);
	nSubAuthorities.Add(DOMAIN_ALIAS_RID_REPLICATOR);
	return GetRights(GetName(&sSidAuth, nSubAuthorities), dwAccessMask);
}

BOOL CSecurityDescriptor::Copy(CONST PSECURITY_DESCRIPTOR pSecurityDescriptor)
{
	DWORD  dwLength;
	DWORD  dwRevision;
	SECURITY_DESCRIPTOR_CONTROL  sdc;

	for (Clear(); (m_pSecurityDescriptor = static_cast<SECURITY_DESCRIPTOR *>(malloc((dwLength = GetSecurityDescriptorLength(pSecurityDescriptor)))));)
	{
		if (GetSecurityDescriptorControl(pSecurityDescriptor, &sdc, &dwRevision))
		{
			if (sdc & SE_SELF_RELATIVE)
			{
				Checked::memcpy_s(m_pSecurityDescriptor, dwLength, pSecurityDescriptor, dwLength);
				return TRUE;
			}
			else
			{
				if (!MakeSelfRelativeSD(pSecurityDescriptor, m_pSecurityDescriptor, &dwLength))
				{
					free(m_pSecurityDescriptor);
					m_pSecurityDescriptor = NULL;
					break;
				}
				return TRUE;
			}
		}
		else
		{
			free(m_pSecurityDescriptor);
			m_pSecurityDescriptor = NULL;
		}
		break;
	}
	return FALSE;

}

SECURITY_INFORMATION CSecurityDescriptor::QueryInformation() CONST
{
	CDacl  cDacl;
	CSacl  cSacl;
	bool  bPresent;

	return(((GetDacl(&cDacl, &bPresent) && bPresent) ? DACL_SECURITY_INFORMATION : 0) | ((GetSacl(&cSacl, &bPresent) && bPresent) ? SACL_SECURITY_INFORMATION : 0));
}

BOOL CSecurityDescriptor::SetRights(LPCTSTR pszName, DWORD dwAccessMask, BYTE nFlags)
{
	DWORD  dwMask;

	return(((!GetRights(pszName, dwMask) || Revoke(pszName)) && Allow(pszName, dwAccessMask, nFlags)) ? TRUE : FALSE);
}

BOOL CSecurityDescriptor::GetRights(LPCTSTR pszName, DWORD &dwAccessMask) CONST
{
	INT  nName;
	INT  nNames;
	CStringArray  szNames;
	CDWordArray  dwMasks;

	for (nName = 0, nNames = Enum(szNames, dwMasks); nName < nNames; nName++)
	{
		if (szNames.GetAt(nName) == pszName)
		{
			dwAccessMask = dwMasks.GetAt(nName);
			break;
		}
	}
	return((nName < nNames) ? TRUE : FALSE);
}

INT CSecurityDescriptor::Enum(CStringArray &szNames, CDWordArray &dwAccessMasks, BOOL bAllowed) CONST
{
	CDacl  cDacl;
	bool  bPresent;

	for (szNames.RemoveAll(), dwAccessMasks.RemoveAll(); GetDacl(&cDacl, &bPresent) && bPresent;)
	{
		if (EnumAce(cDacl, bAllowed, szNames, dwAccessMasks) > 0) break;
		return 0;
	}
	return((INT)szNames.GetSize());
}

BOOL CSecurityDescriptor::Allow(LPCTSTR pszName, DWORD dwAccessMask, BYTE nFlags)
{
	CDacl  cDacl;

	GetDacl(&cDacl);
	return((lstrlen(pszName) > 0) ? AddAccessAce(pszName, dwAccessMask, nFlags, TRUE, cDacl) : FALSE);
}

BOOL CSecurityDescriptor::Deny(LPCTSTR pszName, DWORD dwAccessMask, BYTE nFlags)
{
	CDacl  cDacl;

	GetDacl(&cDacl);
	return((lstrlen(pszName) > 0) ? AddAccessAce(pszName, dwAccessMask, nFlags, FALSE, cDacl) : FALSE);
}

BOOL CSecurityDescriptor::Revoke(LPCTSTR pszName)
{
	CDacl  cDacl;
	bool  bPresent;

	return((lstrlen(pszName) > 0 && GetDacl(&cDacl, &bPresent) && bPresent) ? RemoveAccessAce(pszName, cDacl) : FALSE);
}

INT CSecurityDescriptor::EnumAce(CONST CDacl &cDacl, BOOL bAllowed, CStringArray &szNames, CDWordArray &dwAccessMasks) CONST
{
	INT  i, j;
	INT  nIndex;
	INT  nCount;
	CString szName;
	CSid::CSidArray  cSids;
	CAcl::CAccessMaskArray  cAccessMasks;
	CAcl::CAceTypeArray  cAceTypes;

	for (szNames.RemoveAll(), dwAccessMasks.RemoveAll(); (nCount = cDacl.GetAceCount()) > 0;)
	{
		for (nIndex = 0, cDacl.GetAclEntries(&cSids, &cAccessMasks, &cAceTypes); nIndex < nCount; nIndex++)
		{
			if ((bAllowed && cAceTypes.GetAt(nIndex) == ACCESS_ALLOWED_ACE_TYPE) || (!bAllowed && cAceTypes.GetAt(nIndex) == ACCESS_DENIED_ACE_TYPE))
			{
				for (i = 0, j = (INT)szNames.GetSize(), szName = cSids.GetAt(nIndex).AccountName(); i < j; i++)
				{
					if (szNames.GetAt(i).CompareNoCase(szName)) continue;
					if (dwAccessMasks.GetAt(i) == cAccessMasks.GetAt(nIndex)) break;
				}
				if (i == j)
				{
					szNames.Add(szName);
					dwAccessMasks.Add(cAccessMasks.GetAt(nIndex));
				}
			}
		}
		break;
	}
	return((INT)szNames.GetSize());
}

BOOL CSecurityDescriptor::AddAccessAce(LPCTSTR pszName, DWORD dwAccessMask, BYTE nFlags, BOOL bAllowed, CDacl &cDacl)
{
	CSid  cSid;

	if (GetNameSid(pszName, cSid))
	{
		if ((bAllowed && cDacl.AddAllowedAce(cSid, dwAccessMask, nFlags)) || (!bAllowed && cDacl.AddDeniedAce(cSid, dwAccessMask, nFlags)))
		{
			SetDacl(cDacl);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CSecurityDescriptor::RemoveAccessAce(LPCTSTR pszName, CDacl &cDacl)
{
	CSid  cSid;

	if (GetNameSid(pszName, cSid))
	{
		cDacl.RemoveAllAces();
		SetDacl(cDacl);
		return TRUE;
	}
	return FALSE;
}

CString CSecurityDescriptor::GetName(PSID_IDENTIFIER_AUTHORITY pSidAuth, CDWordArray &nSubAuthorities) CONST
{
	PSID  pSid;
	DWORD  cbName;
	DWORD  cbDomain;
	LPTSTR  pszName;
	LPTSTR  pszDomain;
	SID_NAME_USE  sSidUse;
	CString  szName;

	if (AllocateAndInitializeSid(pSidAuth, (BYTE)nSubAuthorities.GetSize(), (nSubAuthorities.GetSize() > 0) ? nSubAuthorities.GetAt(0) : 0, (nSubAuthorities.GetSize() > 1) ? nSubAuthorities.GetAt(1) : 0, (nSubAuthorities.GetSize() > 2) ? nSubAuthorities.GetAt(2) : 0, (nSubAuthorities.GetSize() > 3) ? nSubAuthorities.GetAt(3) : 0, (nSubAuthorities.GetSize() > 4) ? nSubAuthorities.GetAt(4) : 0, (nSubAuthorities.GetSize() > 5) ? nSubAuthorities.GetAt(5) : 0, (nSubAuthorities.GetSize() > 6) ? nSubAuthorities.GetAt(6) : 0, (nSubAuthorities.GetSize() > 7) ? nSubAuthorities.GetAt(7) : 0, &pSid))
	{
		if (LookupAccountSid((LPCTSTR)NULL, pSid, (LPTSTR)NULL, &(cbName = 0), (LPTSTR)NULL, &(cbDomain = 0), &sSidUse) >= 0)
		{
			if ((pszDomain = (LPTSTR)GlobalAlloc(GPTR, (cbDomain + 1) * sizeof(TCHAR))) != (LPTSTR)NULL)
			{
				if ((pszName = (LPTSTR)GlobalAlloc(GPTR, (cbName + 1) * sizeof(TCHAR))) != (LPTSTR)NULL)
				{
					szName = (LookupAccountSid((LPCTSTR)NULL, pSid, pszName, &cbName, pszDomain, &cbDomain, &sSidUse)) ? pszName : EMPTYSTRING;
					GlobalFree(pszName);
				}
				GlobalFree(pszDomain);
			}
		}
		FreeSid(pSid);
	}
	return szName;
}

BOOL CSecurityDescriptor::GetNameSid(LPCTSTR pszName, CSid &cSid) CONST
{
	return cSid.LoadAccount(pszName);
}


/////////////////////////////////////////////////////////////////////////////
// CSecurity

BOOL CSecurity::SecureDirectory(LPCTSTR pszPath, CONST CSecurityDescriptor &cSecurityDescriptor)
{
	CDacl  cDacl;
	CSacl  cSacl;
	bool  bPresent;

	return(SetNamedSecurityInfo((LPTSTR)pszPath, SE_FILE_OBJECT, cSecurityDescriptor.QueryInformation(), (PSID)NULL, (PSID)NULL, (cSecurityDescriptor.GetDacl(&cDacl, &bPresent) && bPresent) ? (PACL)cDacl.GetPACL() : (PACL)NULL, (cSecurityDescriptor.GetSacl(&cSacl, &bPresent) && bPresent) ? (PACL)cSacl.GetPACL() : (PACL)NULL) == ERROR_SUCCESS);
}

BOOL CSecurity::SecureFile(LPCTSTR pszFileName, CONST CSecurityDescriptor &cSecurityDescriptor)
{
	CDacl  cDacl;
	CSacl  cSacl;
	bool  bPresent;

	return(SetNamedSecurityInfo((LPTSTR)pszFileName, SE_FILE_OBJECT, cSecurityDescriptor.QueryInformation(), (PSID)NULL, (PSID)NULL, (cSecurityDescriptor.GetDacl(&cDacl, &bPresent) && bPresent) ? (PACL)cDacl.GetPACL() : (PACL)NULL, (cSecurityDescriptor.GetSacl(&cSacl, &bPresent) && bPresent) ? (PACL)cSacl.GetPACL() : (PACL)NULL) == ERROR_SUCCESS);
}
