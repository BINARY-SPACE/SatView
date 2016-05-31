// SECURITY.H : Security Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the security related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1997/12/11 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SECURITY_H__
#define __SECURITY_H__


/////////////////////////////////////////////////////////////////////////////
// CSecurityDescriptor

class AFX_EXT_CLASS CSecurityDescriptor : public CSecurityDesc
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL SetRightsOfSystem(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfSystem(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfService(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfService(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfLocalService(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfLocalService(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfNetworkService(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfNetworkService(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfOwner(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfOwner(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfDomainAdministrators(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfDomainAdministrators(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfDomainUsers(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfDomainUsers(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfDomainGuests(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfDomainGuests(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfAdministrators(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfAdministrators(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfPowerUsers(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfPowerUsers(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfUsers(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfUsers(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfGuests(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfGuests(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfEveryone(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfEveryone(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfAuthenticatedUsers(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfAuthenticatedUsers(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfInteractiveUsers(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfInteractiveUsers(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfNetworkUsers(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfNetworkUsers(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfSystemOperators(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfSystemOperators(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfAccountOperators(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfAccountOperators(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfBackupOperators(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfBackupOperators(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfPrintOperators(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfPrintOperators(DWORD &dwAccessMask) CONST;
	BOOL SetRightsOfReplicators(DWORD dwAccessMask, BYTE nFlags = 0);
	BOOL GetRightsOfReplicators(DWORD &dwAccessMask) CONST;

	BOOL Copy(CONST PSECURITY_DESCRIPTOR pSecurityDescriptor);

	SECURITY_INFORMATION QueryInformation() CONST;

private:
	BOOL SetRights(LPCTSTR pszName, DWORD dwAccessMask, BYTE nFlags);
	BOOL GetRights(LPCTSTR pszName, DWORD &dwAccessMask) CONST;

	INT Enum(CStringArray &szNames, CDWordArray &dwAccessMasks, BOOL bAllowed = TRUE) CONST;
	BOOL Allow(LPCTSTR pszName, DWORD dwAccessMask, BYTE nFlags);
	BOOL Deny(LPCTSTR pszName, DWORD dwAccessMask, BYTE nFlags);
	BOOL Revoke(LPCTSTR pszName);

	INT EnumAce(CONST CDacl &cDacl, BOOL bAllowed, CStringArray &szNames, CDWordArray &dwAccessMasks) CONST;
	BOOL AddAccessAce(LPCTSTR pszName, DWORD dwAccessMask, BYTE nFlags, BOOL bAllowed, CDacl &cDacl);
	BOOL RemoveAccessAce(LPCTSTR pszName, CDacl &cDacl);

	CString GetName(PSID_IDENTIFIER_AUTHORITY pSidAuth, CDWordArray &nSubAuthorities) CONST;
	BOOL GetNameSid(LPCTSTR pszName, CSid &cSid) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSecurity

class AFX_EXT_CLASS CSecurity : public CObject
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	static BOOL SecureDirectory(LPCTSTR pszPath, CONST CSecurityDescriptor &cSecurityDescriptor);
	static BOOL SecureFile(LPCTSTR pszFileName, CONST CSecurityDescriptor &cSecurityDescriptor);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __SECURITY_H__
