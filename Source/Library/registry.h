// REGISTRY.H : Registry Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the registry related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1994/05/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __REGISTRY_H__
#define __REGISTRY_H__

#include "token.h"
#include "security.h"


/////////////////////////////////////////////////////////////////////////////
// CRegistry

class AFX_EXT_CLASS CRegistry : public CComputerToken
{
	// Construction
public:
	CRegistry();
	CRegistry(LPCTSTR pszComputerName);

	// Attributes
public:

	// Operations
public:
	INT EnumClassesSubKeys(LPCTSTR pszSubKey, CStringArray &szSubKeys) CONST;
	INT EnumClassesSubKeyValueNames(LPCTSTR pszSubKey, CStringArray &szValueNames) CONST;
	INT EnumMachineSubKeys(LPCTSTR pszSubKey, CStringArray &szSubKeys) CONST;
	INT EnumMachineSubKeyValueNames(LPCTSTR pszSubKey, CStringArray &szValueNames) CONST;
	INT EnumUsersSubKeys(LPCTSTR pszSubKey, CStringArray &szSubKeys) CONST;
	INT EnumUsersSubKeyValueNames(LPCTSTR pszSubKey, CStringArray &szValueNames) CONST;
	INT EnumUserSubKeys(LPCTSTR pszSubKey, CStringArray &szSubKeys) CONST;
	INT EnumUserSubKeyValueNames(LPCTSTR pszSubKey, CStringArray &szValueNames) CONST;

	BOOL SetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName = NULL);
	BOOL SetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwInfo);
	BOOL SetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszInfo);
	BOOL SetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CONST CStringArray &szInfo);
	BOOL SetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwType, CONST BYTE *pInfo, INT cbInfo);
	BOOL GetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD &dwInfo) CONST;
	BOOL GetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CString &szInfo) CONST;
	INT GetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CStringArray &szInfo) CONST;
	INT GetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPDWORD pdwType = NULL, BYTE *pInfo = NULL, INT cbInfo = 0) CONST;
	BOOL SetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName = NULL);
	BOOL SetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwInfo);
	BOOL SetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszInfo);
	BOOL SetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CONST CStringArray &szInfo);
	BOOL SetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwType, CONST BYTE *pInfo, INT cbInfo);
	BOOL GetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD &dwInfo) CONST;
	BOOL GetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CString &szInfo) CONST;
	INT GetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CStringArray &szInfo) CONST;
	INT GetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPDWORD pdwType = NULL, BYTE *pInfo = NULL, INT cbInfo = 0) CONST;
	BOOL SetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName = NULL);
	BOOL SetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwInfo);
	BOOL SetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszInfo);
	BOOL SetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CONST CStringArray &szInfo);
	BOOL SetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwType, CONST BYTE *pInfo, INT cbInfo);
	BOOL GetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD &dwInfo) CONST;
	BOOL GetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CString &szInfo) CONST;
	INT GetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CStringArray &szInfo) CONST;
	INT GetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPDWORD pdwType = NULL, BYTE *pInfo = NULL, INT cbInfo = 0) CONST;
	BOOL SetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName = NULL);
	BOOL SetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwInfo);
	BOOL SetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszInfo);
	BOOL SetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CONST CStringArray &szInfo);
	BOOL SetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwType, CONST BYTE *pInfo, INT cbInfo);
	BOOL GetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD &dwInfo) CONST;
	BOOL GetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CString &szInfo) CONST;
	INT GetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CStringArray &szInfo) CONST;
	INT GetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPDWORD pdwType = NULL, BYTE *pInfo = NULL, INT cbInfo = 0) CONST;

	BOOL SetClassesSecurity(LPCTSTR pszSubKey, CONST CSecurityDescriptor &cSecurityDescriptor);
	BOOL GetClassesSecurity(LPCTSTR pszSubKey, CSecurityDescriptor &cSecurityDescriptor) CONST;
	BOOL SetMachineSecurity(LPCTSTR pszSubKey, CONST CSecurityDescriptor &cSecurityDescriptor);
	BOOL GetMachineSecurity(LPCTSTR pszSubKey, CSecurityDescriptor &cSecurityDescriptor) CONST;
	BOOL SetUsersSecurity(LPCTSTR pszSubKey, CONST CSecurityDescriptor &cSecurityDescriptor);
	BOOL GetUsersSecurity(LPCTSTR pszSubKey, CSecurityDescriptor &cSecurityDescriptor) CONST;
	BOOL SetUserSecurity(LPCTSTR pszSubKey, CONST CSecurityDescriptor &cSecurityDescriptor);
	BOOL GetUserSecurity(LPCTSTR pszSubKey, CSecurityDescriptor &cSecurityDescriptor) CONST;

private:
	INT EnumSubKeys(HKEY hKey, LPCTSTR pszSubKey, CStringArray &szSubKeys) CONST;
	INT EnumValueNames(HKEY hKey, LPCTSTR pszSubKey, CStringArray &szValueNames) CONST;

	BOOL SetInfo(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName = NULL, DWORD dwType = REG_NONE, CONST BYTE *pInfo = NULL, INT cbInfo = 0);
	INT GetInfo(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, LPDWORD pdwType = NULL, BYTE *pInfo = NULL, INT cbInfo = 0) CONST;

	BOOL SetSecurity(HKEY hKey, LPCTSTR pszSubKey, CONST CSecurityDescriptor &cSecurityDescriptor);
	BOOL GetSecurity(HKEY hKey, LPCTSTR pszSubKey, CSecurityDescriptor &cSecurityDescriptor) CONST;

	CString ConstructQualifiedSubKey(LPCTSTR pszSubKey) CONST;

	REGSAM CheckSAM(REGSAM regSAM) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __REGISTRY_H__
