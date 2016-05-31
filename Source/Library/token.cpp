// TOKEN.CPP : Token Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the token related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1996/10/21 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CModuleToken

CModuleToken::CModuleToken() : CObject()
{
	SetModuleName();
}
CModuleToken::CModuleToken(LPCTSTR pszModuleName) : CObject()
{
	SetModuleName(pszModuleName);
}

BOOL CModuleToken::SetModuleName(LPCTSTR pszModuleName)
{
	return(((m_szModuleName = (!AfxIsValidString(pszModuleName) || !lstrlen(pszModuleName)) ? (LPCTSTR)QueryDefaultModuleName() : pszModuleName).GetLength() > 0) ? TRUE : FALSE);
}

CString CModuleToken::GetModuleName() CONST
{
	return m_szModuleName;
}

CString CModuleToken::GetModuleFileRoot() CONST
{
	CFileFindEx  cFileFind;

	return((cFileFind.FindFile(m_szModuleName) && !cFileFind.FindNextFile()) ? (LPCTSTR)cFileFind.GetRoot() : EMPTYSTRING);
}

CString CModuleToken::GetModuleFileName() CONST
{
	CFileFindEx  cFileFind;

	return((cFileFind.FindFile(m_szModuleName) && !cFileFind.FindNextFile()) ? (LPCTSTR)cFileFind.GetFileName() : EMPTYSTRING);
}

CString CModuleToken::GetModuleFileTitle() CONST
{
	CFileFindEx  cFileFind;

	return((cFileFind.FindFile(m_szModuleName) && !cFileFind.FindNextFile()) ? (LPCTSTR)cFileFind.GetFileTitle() : EMPTYSTRING);
}

CModuleToken &CModuleToken::operator=(CONST CString &szModuleName)
{
	SetModuleName(szModuleName);
	return *this;
}
CModuleToken &CModuleToken::operator=(LPCTSTR pszModuleName)
{
	SetModuleName(pszModuleName);
	return *this;
}

BOOL CModuleToken::operator==(CONST CString &szModuleName) CONST
{
	return((!GetModuleName().CompareNoCase(szModuleName)) ? TRUE : FALSE);
}
BOOL CModuleToken::operator==(LPCTSTR pszModuleName) CONST
{
	return((!GetModuleName().CompareNoCase(pszModuleName)) ? TRUE : FALSE);
}

BOOL CModuleToken::operator!=(CONST CString &szModuleName) CONST
{
	return((GetModuleName().CompareNoCase(szModuleName) != 0) ? TRUE : FALSE);
}
BOOL CModuleToken::operator!=(LPCTSTR pszModuleName) CONST
{
	return((GetModuleName().CompareNoCase(pszModuleName) != 0) ? TRUE : FALSE);
}

CModuleToken::operator LPCTSTR() CONST
{
	return((LPCTSTR)m_szModuleName);
}

CString CModuleToken::QueryDefaultModuleName() CONST
{
	TCHAR  szName[MAX_PATH];

	return((::GetModuleFileName((HMODULE)NULL, szName, sizeof(szName) / sizeof(TCHAR))) ? szName : EMPTYSTRING);
}


/////////////////////////////////////////////////////////////////////////////
// CComputerToken

CComputerToken::CComputerToken() : CObject()
{
	SetComputerName();
}
CComputerToken::CComputerToken(LPCTSTR pszComputerName) : CObject()
{
	SetComputerName(pszComputerName);
}

BOOL CComputerToken::SetComputerName(LPCTSTR pszComputerName)
{
	return(((m_szComputerName = (!AfxIsValidString(pszComputerName) || !lstrlen(pszComputerName)) ? (LPCTSTR)QueryDefaultComputerName() : pszComputerName).GetLength() > 0) ? TRUE : FALSE);
}

CString CComputerToken::GetComputerName() CONST
{
	return m_szComputerName;
}

CString CComputerToken::GetComputerUNCName() CONST
{
	return STRING(IDS_LOCALNET_DELIMITER) + GetComputerName();
}

BOOL CComputerToken::IsHost() CONST
{
	return((!GetComputerName().CompareNoCase(QueryDefaultComputerName())) ? TRUE : FALSE);
}

CComputerToken &CComputerToken::operator=(CONST CString &szComputerName)
{
	SetComputerName(szComputerName);
	return *this;
}
CComputerToken &CComputerToken::operator=(LPCTSTR pszComputerName)
{
	SetComputerName(pszComputerName);
	return *this;
}

BOOL CComputerToken::operator==(CONST CString &szComputerName) CONST
{
	return((!GetComputerName().CompareNoCase(szComputerName)) ? TRUE : FALSE);
}
BOOL CComputerToken::operator==(LPCTSTR pszComputerName) CONST
{
	return((!GetComputerName().CompareNoCase(pszComputerName)) ? TRUE : FALSE);
}

BOOL CComputerToken::operator!=(CONST CString &szComputerName) CONST
{
	return((GetComputerName().CompareNoCase(szComputerName) != 0) ? TRUE : FALSE);
}
BOOL CComputerToken::operator!=(LPCTSTR pszComputerName) CONST
{
	return((GetComputerName().CompareNoCase(pszComputerName) != 0) ? TRUE : FALSE);
}

CComputerToken::operator LPCTSTR() CONST
{
	return((LPCTSTR)m_szComputerName);
}

CString CComputerToken::QueryDefaultComputerName() CONST
{
	DWORD  cbName;
	TCHAR  szName[MAX_COMPUTERNAME_LENGTH + 1];

	return((::GetComputerName(szName, &(cbName = sizeof(szName) / sizeof(TCHAR)))) ? szName : EMPTYSTRING);
}


/////////////////////////////////////////////////////////////////////////////
// CSpacecraftToken

CSpacecraftToken::CSpacecraftToken() : CObject()
{
	SetSpacecraftName();
}
CSpacecraftToken::CSpacecraftToken(LPCTSTR pszSpacecraftName) : CObject()
{
	SetSpacecraftName(pszSpacecraftName);
}

BOOL CSpacecraftToken::SetSpacecraftName(LPCTSTR pszSpacecraftName)
{
	return(((m_szSpacecraftName = (!AfxIsValidString(pszSpacecraftName) || !lstrlen(pszSpacecraftName)) ? (LPCTSTR)QueryDefaultSpacecraftName() : pszSpacecraftName).GetLength() > 0) ? TRUE : FALSE);
}

CString CSpacecraftToken::GetSpacecraftName() CONST
{
	return m_szSpacecraftName;
}

CSpacecraftToken &CSpacecraftToken::operator=(CONST CString &szSpacecraftName)
{
	SetSpacecraftName(szSpacecraftName);
	return *this;
}
CSpacecraftToken &CSpacecraftToken::operator=(LPCTSTR pszSpacecraftName)
{
	SetSpacecraftName(pszSpacecraftName);
	return *this;
}

BOOL CSpacecraftToken::operator==(CONST CString &szSpacecraftName) CONST
{
	return((!GetSpacecraftName().Compare(szSpacecraftName)) ? TRUE : FALSE);
}
BOOL CSpacecraftToken::operator==(LPCTSTR pszSpacecraftName) CONST
{
	return((!GetSpacecraftName().Compare(pszSpacecraftName)) ? TRUE : FALSE);
}

BOOL CSpacecraftToken::operator!=(CONST CString &szSpacecraftName) CONST
{
	return((GetSpacecraftName().Compare(szSpacecraftName) != 0) ? TRUE : FALSE);
}
BOOL CSpacecraftToken::operator!=(LPCTSTR pszSpacecraftName) CONST
{
	return((GetSpacecraftName().Compare(pszSpacecraftName) != 0) ? TRUE : FALSE);
}

CSpacecraftToken::operator LPCTSTR() CONST
{
	return((LPCTSTR)m_szSpacecraftName);
}

CString CSpacecraftToken::QueryDefaultSpacecraftName() CONST
{
	return EMPTYSTRING;
}


/////////////////////////////////////////////////////////////////////////////
// CUserToken

CUserToken::CUserToken() : CObject()
{
	SetUserName();
}
CUserToken::CUserToken(LPCTSTR pszUserName) : CObject()
{
	SetUserName(pszUserName);
}

BOOL CUserToken::SetUserName(LPCTSTR pszUserName)
{
	return(((m_szUserName = (!AfxIsValidString(pszUserName) || !lstrlen(pszUserName)) ? (LPCTSTR)QueryDefaultUserName() : pszUserName).GetLength() > 0) ? TRUE : FALSE);
}

CString CUserToken::GetUserName() CONST
{
	return m_szUserName;
}

BOOL CUserToken::IsAdministrator(BOOL bUnique) CONST
{
	INT  nUser;
	INT  nUsers;
	PSID  pSid;
	DWORD  cbGroup;
	DWORD  cbDomain;
	LPTSTR  pszGroup;
	LPTSTR  pszDomain;
	CAccounts  cAccounts;
	CStringArray  szUsers;
	SID_NAME_USE  sSidUse;
	SID_IDENTIFIER_AUTHORITY  sSidAuth = SECURITY_NT_AUTHORITY;

	if (AllocateAndInitializeSid(&sSidAuth, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pSid))
	{
		for (LookupAccountSid((LPCTSTR)NULL, pSid, (LPTSTR)NULL, &(cbGroup = 0), (LPTSTR)NULL, &(cbDomain = 0), &sSidUse); (pszDomain = (LPTSTR)GlobalAlloc(GPTR, (cbDomain + 1)*sizeof(TCHAR))); )
		{
			if ((pszGroup = (LPTSTR)GlobalAlloc(GPTR, (cbGroup + 1)*sizeof(TCHAR))) != (LPTSTR)NULL)
			{
				if (LookupAccountSid((LPCTSTR)NULL, pSid, pszGroup, &cbGroup, pszDomain, &cbDomain, &sSidUse))
				{
					if (!_tcsncmp(pszGroup, GetUserName(), GetUserName().GetLength()))
					{
						GlobalFree(pszDomain);
						GlobalFree(pszGroup);
						LocalFree(pSid);
						return TRUE;
					}
					for (nUser = 0, nUsers = (!bUnique) ? cAccounts.EnumGroupMembers(pszGroup, szUsers) : 0; nUser < nUsers; nUser++)
					{
						if (!szUsers.GetAt(nUser).CompareNoCase(GetUserName())) break;
						continue;
					}
					if (nUser < nUsers)
					{
						GlobalFree(pszDomain);
						GlobalFree(pszGroup);
						FreeSid(pSid);
						return TRUE;
					}
				}
				GlobalFree(pszGroup);
			}
			GlobalFree(pszDomain);
			break;
		}
		FreeSid(pSid);
	}
	return FALSE;
}

CUserToken &CUserToken::operator=(CONST CString &szUserName)
{
	SetUserName(szUserName);
	return *this;
}
CUserToken &CUserToken::operator=(LPCTSTR pszUserName)
{
	SetUserName(pszUserName);
	return *this;
}

BOOL CUserToken::operator==(CONST CString &szUserName) CONST
{
	return((!GetUserName().Compare(szUserName)) ? TRUE : FALSE);
}
BOOL CUserToken::operator==(LPCTSTR pszUserName) CONST
{
	return((!GetUserName().Compare(pszUserName)) ? TRUE : FALSE);
}

BOOL CUserToken::operator!=(CONST CString &szUserName) CONST
{
	return((GetUserName().Compare(szUserName) != 0) ? TRUE : FALSE);
}
BOOL CUserToken::operator!=(LPCTSTR pszUserName) CONST
{
	return((GetUserName().Compare(pszUserName) != 0) ? TRUE : FALSE);
}

CUserToken::operator LPCTSTR() CONST
{
	return((LPCTSTR)m_szUserName);
}

CString CUserToken::QueryDefaultUserName() CONST
{
	return EMPTYSTRING;
}


/////////////////////////////////////////////////////////////////////////////
// CToken

CToken::CToken() : CComputerToken(), CSpacecraftToken(), CUserToken()
{
	return;
}
CToken::CToken(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName) : CComputerToken(pszComputerName), CSpacecraftToken(pszSpacecraftName), CUserToken(pszUserName)
{
	return;
}

BOOL CToken::SetOwner(CONST CToken *pToken)
{
	CString  szComputerName;
	CString  szSpacecraftName;
	CString  szUserName;

	pToken->GetOwner(szComputerName, szSpacecraftName, szUserName);
	return SetOwner(szComputerName, szSpacecraftName, szUserName);
}
BOOL CToken::SetOwner(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName)
{
	SetComputerName(pszComputerName);
	SetSpacecraftName(pszSpacecraftName);
	SetUserName(pszUserName);
	return HasOwner();
}

BOOL CToken::GetOwner(CString &szComputerName, CString &szSpacecraftName, CString &szUserName) CONST
{
	szComputerName = GetComputerName();
	szSpacecraftName = GetSpacecraftName();
	szUserName = GetUserName();
	return HasOwner();
}

BOOL CToken::HasOwner() CONST
{
	return((!GetComputerName().IsEmpty() && !GetSpacecraftName().IsEmpty() && !GetUserName().IsEmpty()) ? TRUE : FALSE);
}

BOOL CToken::HasSameOwner(CONST CToken *pToken) CONST
{
	return((pToken->GetComputerName() == GetComputerName() && pToken->GetSpacecraftName() == GetSpacecraftName() && pToken->GetUserName() == GetUserName()) ? TRUE : FALSE);
}
BOOL CToken::HasSameOwner(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName) CONST
{
	return((!GetComputerName().CompareNoCase(pszComputerName) && !GetSpacecraftName().Compare(pszSpacecraftName) && !GetUserName().Compare(pszUserName)) ? TRUE : FALSE);
}

CToken &CToken::operator=(CToken &cToken)
{
	SetOwner(&cToken);
	return *this;
}

BOOL CToken::operator==(CONST CToken &cToken) CONST
{
	return HasSameOwner(&cToken);
}

BOOL CToken::operator!=(CONST CToken &cToken) CONST
{
	return !HasSameOwner(&cToken);
}
