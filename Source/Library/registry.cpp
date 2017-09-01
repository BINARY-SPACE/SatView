// REGISTRY.CPP : Registry Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the registry related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1994/05/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CRegistry

CRegistry::CRegistry() : CComputerToken()
{
	return;
}
CRegistry::CRegistry(LPCTSTR pszComputerName) : CComputerToken(pszComputerName)
{
	return;
}

INT CRegistry::EnumClassesSubKeys(LPCTSTR pszSubKey, CStringArray &szSubKeys) CONST
{
	return EnumSubKeys(HKEY_CLASSES_ROOT, pszSubKey, szSubKeys);
}

INT CRegistry::EnumClassesSubKeyValueNames(LPCTSTR pszSubKey, CStringArray &szValueNames) CONST
{
	return EnumValueNames(HKEY_CLASSES_ROOT, pszSubKey, szValueNames);
}

INT CRegistry::EnumMachineSubKeys(LPCTSTR pszSubKey, CStringArray &szSubKeys) CONST
{
	return EnumSubKeys(HKEY_LOCAL_MACHINE, pszSubKey, szSubKeys);
}

INT CRegistry::EnumMachineSubKeyValueNames(LPCTSTR pszSubKey, CStringArray &szValueNames) CONST
{
	return EnumValueNames(HKEY_LOCAL_MACHINE, pszSubKey, szValueNames);
}

INT CRegistry::EnumUsersSubKeys(LPCTSTR pszSubKey, CStringArray &szSubKeys) CONST
{
	return EnumSubKeys(HKEY_USERS, pszSubKey, szSubKeys);
}

INT CRegistry::EnumUsersSubKeyValueNames(LPCTSTR pszSubKey, CStringArray &szValueNames) CONST
{
	return EnumValueNames(HKEY_USERS, pszSubKey, szValueNames);
}

INT CRegistry::EnumUserSubKeys(LPCTSTR pszSubKey, CStringArray &szSubKeys) CONST
{
	return EnumSubKeys(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), szSubKeys);
}

INT CRegistry::EnumUserSubKeyValueNames(LPCTSTR pszSubKey, CStringArray &szValueNames) CONST
{
	return EnumValueNames(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), szValueNames);
}

BOOL CRegistry::SetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName)
{
	return SetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName);
}

BOOL CRegistry::SetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwInfo)
{
	return SetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, REG_DWORD, (CONST BYTE *) &dwInfo, sizeof(dwInfo));
}

BOOL CRegistry::SetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszInfo)
{
	return SetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, REG_SZ, (CONST BYTE *) pszInfo, (lstrlen(pszInfo) + 1) * sizeof(TCHAR));
}

BOOL CRegistry::SetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CONST CStringArray &szInfo)
{
	INT  nString;
	INT  nStrings;
	INT  cbStrings;
	LPTSTR  pszStrings;
	CString  szStrings;

	for (nString = 0, nStrings = (INT)szInfo.GetSize(), cbStrings = 0; nString < nStrings; nString++)
	{
		if ((pszStrings = szStrings.GetBufferSetLength(cbStrings + szInfo.GetAt(nString).GetLength() + 1)))
		{
			_tcscpy_s(&pszStrings[cbStrings], szInfo.GetAt(nString).GetLength() + 1, szInfo.GetAt(nString));
			cbStrings += szInfo.GetAt(nString).GetLength() + 1;
			szStrings.ReleaseBuffer();
			continue;
		}
		break;
	}
	return((nString == nStrings) ? SetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, REG_MULTI_SZ, (CONST BYTE *) (LPCTSTR) szStrings, (cbStrings + 1) * sizeof(TCHAR)) : FALSE);
}

BOOL CRegistry::SetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwType, CONST BYTE *pInfo, INT cbInfo)
{
	return SetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, dwType, pInfo, cbInfo);
}

BOOL CRegistry::GetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD &dwInfo) CONST
{
	DWORD  dwType;

	return((GetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, &dwType) > 0 && dwType == REG_DWORD  &&  GetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, &dwType, (BYTE *)&dwInfo, sizeof(DWORD)) == sizeof(DWORD)) ? TRUE : FALSE);
}

BOOL CRegistry::GetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CString &szInfo) CONST
{
	INT  cbString;
	DWORD  dwType;

	if ((cbString = GetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, &dwType)) > 0 && (dwType == REG_SZ || dwType == REG_EXPAND_SZ))
	{
		if (GetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, &dwType, (BYTE *)szInfo.GetBufferSetLength(cbString / sizeof(TCHAR)), cbString) == cbString)
		{
			szInfo.ReleaseBuffer();
			return TRUE;
		}
		szInfo.ReleaseBuffer();
	}
	return FALSE;
}

INT CRegistry::GetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CStringArray &szInfo) CONST
{
	INT  nString;
	INT  nStrings;
	INT  cbStrings;
	DWORD  dwType;
	LPTSTR  pszStrings;
	CString  szStrings;

	for (szInfo.RemoveAll(); (cbStrings = GetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, &dwType)) > 0 && dwType == REG_MULTI_SZ; )
	{
		if (GetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, &dwType, (BYTE *)(pszStrings = szStrings.GetBufferSetLength(cbStrings / sizeof(TCHAR) - 1)), cbStrings) == cbStrings)
		{
			for (nString = nStrings = 0; nStrings < cbStrings / (INT) sizeof(TCHAR) - 1; nStrings += lstrlen(&pszStrings[nStrings]) + 1)
			{
				szInfo.Add(&pszStrings[nStrings]);
				continue;
			}
		}
		szStrings.ReleaseBuffer();
		break;
	}
	return((INT)szInfo.GetSize());
}

INT CRegistry::GetClassesInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPDWORD pdwType, BYTE *pInfo, INT cbInfo) CONST
{
	return GetInfo(HKEY_CLASSES_ROOT, pszSubKey, pszValueName, pdwType, pInfo, cbInfo);
}

BOOL CRegistry::SetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName)
{
	return SetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName);
}

BOOL CRegistry::SetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwInfo)
{
	return SetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, REG_DWORD, (CONST BYTE *) &dwInfo, sizeof(dwInfo));
}

BOOL CRegistry::SetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszInfo)
{
	return SetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, REG_SZ, (CONST BYTE *) pszInfo, (lstrlen(pszInfo) + 1) * sizeof(TCHAR));
}

BOOL CRegistry::SetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CONST CStringArray &szInfo)
{
	INT  nString;
	INT  nStrings;
	INT  cbStrings;
	LPTSTR  pszStrings;
	CString  szStrings;

	for (nString = 0, nStrings = (INT)szInfo.GetSize(), cbStrings = 0; nString < nStrings; nString++)
	{
		if ((pszStrings = szStrings.GetBufferSetLength(cbStrings + szInfo.GetAt(nString).GetLength() + 1)))
		{
			_tcscpy_s(&pszStrings[cbStrings], szInfo.GetAt(nString).GetLength() + 1, szInfo.GetAt(nString));
			cbStrings += szInfo.GetAt(nString).GetLength() + 1;
			szStrings.ReleaseBuffer();
			continue;
		}
		break;
	}
	return((nString == nStrings) ? SetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, REG_MULTI_SZ, (CONST BYTE *) (LPCTSTR) szStrings, (cbStrings + 1) * sizeof(TCHAR)) : FALSE);
}

BOOL CRegistry::SetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwType, CONST BYTE *pInfo, INT cbInfo)
{
	return SetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, dwType, pInfo, cbInfo);
}

BOOL CRegistry::GetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD &dwInfo) CONST
{
	DWORD  dwType;

	return((GetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, &dwType) > 0 && dwType == REG_DWORD  &&  GetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, &dwType, (BYTE *)&dwInfo, sizeof(DWORD)) == sizeof(DWORD)) ? TRUE : FALSE);
}

BOOL CRegistry::GetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CString &szInfo) CONST
{
	INT  cbString;
	DWORD  dwType;

	if ((cbString = GetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, &dwType)) > 0 && (dwType == REG_SZ || dwType == REG_EXPAND_SZ))
	{
		if (GetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, &dwType, (BYTE *)szInfo.GetBufferSetLength(cbString / sizeof(TCHAR)), cbString) == cbString)
		{
			szInfo.ReleaseBuffer();
			return TRUE;
		}
		szInfo.ReleaseBuffer();
	}
	return FALSE;
}

INT CRegistry::GetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CStringArray &szInfo) CONST
{
	INT  nString;
	INT  nStrings;
	INT  cbStrings;
	DWORD  dwType;
	LPTSTR  pszStrings;
	CString  szStrings;

	for (szInfo.RemoveAll(); (cbStrings = GetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, &dwType)) > 0 && dwType == REG_MULTI_SZ; )
	{
		if (GetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, &dwType, (BYTE *)(pszStrings = szStrings.GetBufferSetLength(cbStrings / sizeof(TCHAR) - 1)), cbStrings) == cbStrings)
		{
			for (nString = nStrings = 0; nStrings < cbStrings / (INT) sizeof(TCHAR) - 1; nStrings += lstrlen(&pszStrings[nStrings]) + 1)
			{
				szInfo.Add(&pszStrings[nStrings]);
				continue;
			}
		}
		szStrings.ReleaseBuffer();
		break;
	}
	return((INT)szInfo.GetSize());
}

INT CRegistry::GetMachineInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPDWORD pdwType, BYTE *pInfo, INT cbInfo) CONST
{
	return GetInfo(HKEY_LOCAL_MACHINE, pszSubKey, pszValueName, pdwType, pInfo, cbInfo);
}

BOOL CRegistry::SetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName)
{
	return SetInfo(HKEY_USERS, pszSubKey, pszValueName);
}

BOOL CRegistry::SetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwInfo)
{
	return SetInfo(HKEY_USERS, pszSubKey, pszValueName, REG_DWORD, (CONST BYTE *) &dwInfo, sizeof(dwInfo));
}

BOOL CRegistry::SetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszInfo)
{
	return SetInfo(HKEY_USERS, pszSubKey, pszValueName, REG_SZ, (CONST BYTE *) pszInfo, (lstrlen(pszInfo) + 1) * sizeof(TCHAR));
}

BOOL CRegistry::SetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CONST CStringArray &szInfo)
{
	INT  nString;
	INT  nStrings;
	INT  cbStrings;
	LPTSTR  pszStrings;
	CString  szStrings;

	for (nString = 0, nStrings = (INT)szInfo.GetSize(), cbStrings = 0; nString < nStrings; nString++)
	{
		if ((pszStrings = szStrings.GetBufferSetLength(cbStrings + szInfo.GetAt(nString).GetLength() + 1)))
		{
			_tcscpy_s(&pszStrings[cbStrings], szInfo.GetAt(nString).GetLength() + 1, szInfo.GetAt(nString));
			cbStrings += szInfo.GetAt(nString).GetLength() + 1;
			szStrings.ReleaseBuffer();
			continue;
		}
		break;
	}
	return((nString == nStrings) ? SetInfo(HKEY_USERS, pszSubKey, pszValueName, REG_MULTI_SZ, (CONST BYTE *) (LPCTSTR) szStrings, (cbStrings + 1) * sizeof(TCHAR)) : FALSE);
}

BOOL CRegistry::SetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwType, CONST BYTE *pInfo, INT cbInfo)
{
	return SetInfo(HKEY_USERS, pszSubKey, pszValueName, dwType, pInfo, cbInfo);
}

BOOL CRegistry::GetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD &dwInfo) CONST
{
	DWORD  dwType;

	return((GetInfo(HKEY_USERS, pszSubKey, pszValueName, &dwType) > 0 && dwType == REG_DWORD  &&  GetInfo(HKEY_USERS, pszSubKey, pszValueName, &dwType, (BYTE *)&dwInfo, sizeof(DWORD)) == sizeof(DWORD)) ? TRUE : FALSE);
}

BOOL CRegistry::GetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CString &szInfo) CONST
{
	INT  cbString;
	DWORD  dwType;

	if ((cbString = GetInfo(HKEY_USERS, pszSubKey, pszValueName, &dwType)) > 0 && (dwType == REG_SZ || dwType == REG_EXPAND_SZ))
	{
		if (GetInfo(HKEY_USERS, pszSubKey, pszValueName, &dwType, (BYTE *)szInfo.GetBufferSetLength(cbString / sizeof(TCHAR)), cbString) == cbString)
		{
			szInfo.ReleaseBuffer();
			return TRUE;
		}
		szInfo.ReleaseBuffer();
	}
	return FALSE;
}

INT CRegistry::GetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CStringArray &szInfo) CONST
{
	INT  nString;
	INT  nStrings;
	INT  cbStrings;
	DWORD  dwType;
	LPTSTR  pszStrings;
	CString  szStrings;

	for (szInfo.RemoveAll(); (cbStrings = GetInfo(HKEY_USERS, pszSubKey, pszValueName, &dwType)) > 0 && dwType == REG_MULTI_SZ; )
	{
		if (GetInfo(HKEY_USERS, pszSubKey, pszValueName, &dwType, (BYTE *)(pszStrings = szStrings.GetBufferSetLength(cbStrings / sizeof(TCHAR) - 1)), cbStrings) == cbStrings)
		{
			for (nString = nStrings = 0; nStrings < cbStrings / (INT) sizeof(TCHAR) - 1; nStrings += lstrlen(&pszStrings[nStrings]) + 1)
			{
				szInfo.Add(&pszStrings[nStrings]);
				continue;
			}
		}
		szStrings.ReleaseBuffer();
		break;
	}
	return((INT)szInfo.GetSize());
}

INT CRegistry::GetUsersInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPDWORD pdwType, BYTE *pInfo, INT cbInfo) CONST
{
	return GetInfo(HKEY_USERS, pszSubKey, pszValueName, pdwType, pInfo, cbInfo);
}

BOOL CRegistry::SetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName)
{
	return SetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName);
}

BOOL CRegistry::SetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwInfo)
{
	return SetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, REG_DWORD, (CONST BYTE *) &dwInfo, sizeof(dwInfo));
}

BOOL CRegistry::SetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPCTSTR pszInfo)
{
	return SetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, REG_SZ, (CONST BYTE *) pszInfo, (lstrlen(pszInfo) + 1) * sizeof(TCHAR));
}

BOOL CRegistry::SetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CONST CStringArray &szInfo)
{
	INT  nString;
	INT  nStrings;
	INT  cbStrings;
	LPTSTR  pszStrings;
	CString  szStrings;

	for (nString = 0, nStrings = (INT)szInfo.GetSize(), cbStrings = 0; nString < nStrings; nString++)
	{
		if ((pszStrings = szStrings.GetBufferSetLength(cbStrings + szInfo.GetAt(nString).GetLength() + 1)))
		{
			_tcscpy_s(&pszStrings[cbStrings], szInfo.GetAt(nString).GetLength() + 1, szInfo.GetAt(nString));
			cbStrings += szInfo.GetAt(nString).GetLength() + 1;
			szStrings.ReleaseBuffer();
			continue;
		}
		break;
	}
	return((nString == nStrings) ? SetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, REG_MULTI_SZ, (CONST BYTE *) (LPCTSTR) szStrings, (cbStrings + 1) * sizeof(TCHAR)) : FALSE);
}

BOOL CRegistry::SetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwType, CONST BYTE *pInfo, INT cbInfo)
{
	return SetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, dwType, pInfo, cbInfo);
}

BOOL CRegistry::GetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD &dwInfo) CONST
{
	DWORD  dwType;

	return((GetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, &dwType) > 0 && dwType == REG_DWORD  &&  GetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, &dwType, (BYTE *)&dwInfo, sizeof(DWORD)) == sizeof(DWORD)) ? TRUE : FALSE);
}

BOOL CRegistry::GetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CString &szInfo) CONST
{
	INT  cbString;
	DWORD  dwType;

	if ((cbString = GetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, &dwType)) > 0 && (dwType == REG_SZ || dwType == REG_EXPAND_SZ))
	{
		if (GetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, &dwType, (BYTE *)szInfo.GetBufferSetLength(cbString / sizeof(TCHAR)), cbString) == cbString)
		{
			szInfo.ReleaseBuffer();
			return TRUE;
		}
		szInfo.ReleaseBuffer();
	}
	return FALSE;
}

INT CRegistry::GetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, CStringArray &szInfo) CONST
{
	INT  nString;
	INT  nStrings;
	INT  cbStrings;
	DWORD  dwType;
	LPTSTR  pszStrings;
	CString  szStrings;

	for (szInfo.RemoveAll(); (cbStrings = GetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, &dwType)) > 0 && dwType == REG_MULTI_SZ; )
	{
		if (GetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, &dwType, (BYTE *)(pszStrings = szStrings.GetBufferSetLength(cbStrings / sizeof(TCHAR) - 1)), cbStrings) == cbStrings)
		{
			for (nString = nStrings = 0; nStrings < cbStrings / (INT) sizeof(TCHAR) - 1; nStrings += lstrlen(&pszStrings[nStrings]) + 1)
			{
				szInfo.Add(&pszStrings[nStrings]);
				continue;
			}
		}
		szStrings.ReleaseBuffer();
		break;
	}
	return((INT)szInfo.GetSize());
}

INT CRegistry::GetUserInfo(LPCTSTR pszSubKey, LPCTSTR pszValueName, LPDWORD pdwType, BYTE *pInfo, INT cbInfo) CONST
{
	return GetInfo(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), pszValueName, pdwType, pInfo, cbInfo);
}

BOOL CRegistry::SetClassesSecurity(LPCTSTR pszSubKey, CONST CSecurityDescriptor &cSecurityDescriptor)
{
	return SetSecurity(HKEY_CLASSES_ROOT, pszSubKey, cSecurityDescriptor);
}

BOOL CRegistry::GetClassesSecurity(LPCTSTR pszSubKey, CSecurityDescriptor &cSecurityDescriptor) CONST
{
	return GetSecurity(HKEY_CLASSES_ROOT, pszSubKey, cSecurityDescriptor);
}

BOOL CRegistry::SetMachineSecurity(LPCTSTR pszSubKey, CONST CSecurityDescriptor &cSecurityDescriptor)
{
	return SetSecurity(HKEY_LOCAL_MACHINE, pszSubKey, cSecurityDescriptor);
}

BOOL CRegistry::GetMachineSecurity(LPCTSTR pszSubKey, CSecurityDescriptor &cSecurityDescriptor) CONST
{
	return GetSecurity(HKEY_LOCAL_MACHINE, pszSubKey, cSecurityDescriptor);
}

BOOL CRegistry::SetUsersSecurity(LPCTSTR pszSubKey, CONST CSecurityDescriptor &cSecurityDescriptor)
{
	return SetSecurity(HKEY_USERS, pszSubKey, cSecurityDescriptor);
}

BOOL CRegistry::GetUsersSecurity(LPCTSTR pszSubKey, CSecurityDescriptor &cSecurityDescriptor) CONST
{
	return GetSecurity(HKEY_USERS, pszSubKey, cSecurityDescriptor);
}

BOOL CRegistry::SetUserSecurity(LPCTSTR pszSubKey, CONST CSecurityDescriptor &cSecurityDescriptor)
{
	return SetSecurity(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), cSecurityDescriptor);
}

BOOL CRegistry::GetUserSecurity(LPCTSTR pszSubKey, CSecurityDescriptor &cSecurityDescriptor) CONST
{
	return GetSecurity(HKEY_USERS, ConstructQualifiedSubKey(pszSubKey), cSecurityDescriptor);
}

INT CRegistry::EnumSubKeys(HKEY hKey, LPCTSTR pszSubKey, CStringArray &szSubKeys) CONST
{
	HKEY  hRegKey;
	HKEY  hRegSubKey;
	LONG  lRegResult;
	DWORD  cbRegData;
	DWORD  cbSubKey;
	DWORD  dwSubKey;
	DWORD  dwSubKeys;
	FILETIME  tSubKey;
	CString  szSubKey;

	if (RegConnectRegistry(GetComputerUNCName(), hKey, &hRegKey) == ERROR_SUCCESS)
	{
		if (RegOpenKeyEx(hRegKey, pszSubKey, 0, CheckSAM(KEY_READ), &hRegSubKey) == ERROR_SUCCESS)
		{
			if (RegQueryInfoKey(hRegSubKey, (LPTSTR)NULL, (LPDWORD)NULL, (LPDWORD)NULL, &dwSubKeys, &cbSubKey, (LPDWORD)NULL, (LPDWORD)NULL, (LPDWORD)NULL, (LPDWORD)NULL, (LPDWORD)NULL, (PFILETIME)NULL) == ERROR_SUCCESS)
			{
				for (dwSubKey = 0; (lRegResult = RegEnumKeyEx(hRegSubKey, dwSubKey, szSubKey.GetBufferSetLength(cbSubKey), &(cbRegData = cbSubKey + 1), (LPDWORD)NULL, (LPTSTR)NULL, (LPDWORD)NULL, &tSubKey)) == ERROR_SUCCESS; dwSubKey++)
				{
					szSubKey.ReleaseBuffer();
					szSubKeys.Add(szSubKey);
					continue;
				}
				if (lRegResult == ERROR_NO_MORE_ITEMS)
				{
					RegCloseKey(hRegSubKey);
					RegCloseKey(hRegKey);
					return dwSubKeys;
				}
				for (szSubKey.ReleaseBuffer(); dwSubKey > 0 && szSubKeys.GetSize(); dwSubKey--)
				{
					szSubKeys.RemoveAt(szSubKeys.GetSize() - 1);
					continue;
				}
			}
			RegCloseKey(hRegSubKey);
		}
		RegCloseKey(hRegKey);
	}
	return -1;
}

INT CRegistry::EnumValueNames(HKEY hKey, LPCTSTR pszSubKey, CStringArray &szValueNames) CONST
{
	HKEY  hRegKey;
	HKEY  hRegSubKey;
	LONG  lRegResult;
	DWORD  cbRegData;
	DWORD  cbValueName;
	DWORD  dwValueName;
	DWORD  dwValueNames;
	CString  szValueName;

	if (RegConnectRegistry(GetComputerUNCName(), hKey, &hRegKey) == ERROR_SUCCESS)
	{
		if (RegOpenKeyEx(hRegKey, pszSubKey, 0, CheckSAM(KEY_READ), &hRegSubKey) == ERROR_SUCCESS)
		{
			if (RegQueryInfoKey(hRegSubKey, (LPTSTR)NULL, (LPDWORD)NULL, (LPDWORD)NULL, (LPDWORD)NULL, (LPDWORD)NULL, (LPDWORD)NULL, &dwValueNames, &cbValueName, (LPDWORD)NULL, (LPDWORD)NULL, (PFILETIME)NULL) == ERROR_SUCCESS)
			{
				for (dwValueName = 0; (lRegResult = RegEnumValue(hRegSubKey, dwValueName, szValueName.GetBufferSetLength(cbValueName), &(cbRegData = cbValueName + 1), (LPDWORD)NULL, (LPDWORD)NULL, (LPBYTE)NULL, (LPDWORD)NULL)) == ERROR_SUCCESS; dwValueName++)
				{
					szValueName.ReleaseBuffer();
					szValueNames.Add(szValueName);
					continue;
				}
				if (lRegResult == ERROR_NO_MORE_ITEMS)
				{
					RegCloseKey(hRegSubKey);
					RegCloseKey(hRegKey);
					return dwValueNames;
				}
				for (szValueName.ReleaseBuffer(); dwValueName > 0 && szValueNames.GetSize(); dwValueName--)
				{
					szValueNames.RemoveAt(szValueNames.GetSize() - 1);
					continue;
				}
			}
			RegCloseKey(hRegSubKey);
		}
		RegCloseKey(hRegKey);
	}
	return -1;
}

BOOL CRegistry::SetInfo(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, DWORD dwType, CONST BYTE *pInfo, INT cbInfo)
{
	HKEY  hRegKey;
	HKEY  hRegSubKey;
	LONG  lRegKeyCode;
	DWORD  dwKeyStatus;

	if (RegConnectRegistry(GetComputerUNCName(), hKey, &hRegKey) == ERROR_SUCCESS)
	{
		if ((AfxIsValidString(pszValueName) && RegCreateKeyEx(hRegKey, pszSubKey, 0, (LPTSTR)NULL, REG_OPTION_NON_VOLATILE, CheckSAM(KEY_WRITE), (LPSECURITY_ATTRIBUTES)NULL, &hRegSubKey, &dwKeyStatus) == ERROR_SUCCESS) || (!AfxIsValidString(pszValueName) && ((lRegKeyCode = RegDeleteKey(hRegKey, pszSubKey)) == ERROR_SUCCESS || lRegKeyCode == ERROR_FILE_NOT_FOUND)))
		{
			if ((AfxIsValidString(pszValueName) && ((AfxIsValidAddress(pInfo, cbInfo, FALSE) && RegSetValueEx(hRegSubKey, pszValueName, 0, dwType, pInfo, cbInfo) == ERROR_SUCCESS) || (!AfxIsValidAddress(pInfo, cbInfo, FALSE) && (GetInfo(hKey, pszSubKey, pszValueName) < 0 || (lRegKeyCode = RegDeleteValue(hRegSubKey, pszValueName)) == ERROR_SUCCESS || lRegKeyCode == ERROR_FILE_NOT_FOUND)))) || !AfxIsValidString(pszValueName))
			{
				if (AfxIsValidString(pszValueName)) RegCloseKey(hRegSubKey);
				RegCloseKey(hRegKey);
				return TRUE;
			}
			if (AfxIsValidString(pszValueName)) RegCloseKey(hRegSubKey);
		}
		RegCloseKey(hRegKey);
	}
	return FALSE;
}

INT CRegistry::GetInfo(HKEY hKey, LPCTSTR pszSubKey, LPCTSTR pszValueName, LPDWORD pdwType, BYTE *pInfo, INT cbInfo) CONST
{
	HKEY  hRegKey;
	HKEY  hRegSubKey;
	DWORD  cbValueData;

	if (RegConnectRegistry(GetComputerUNCName(), hKey, &hRegKey) == ERROR_SUCCESS)
	{
		if (RegOpenKeyEx(hRegKey, pszSubKey, 0, CheckSAM(KEY_READ), &hRegSubKey) == ERROR_SUCCESS)
		{
			if (RegQueryValueEx(hRegSubKey, pszValueName, (LPDWORD)NULL, pdwType, pInfo, &(cbValueData = cbInfo)) == ERROR_SUCCESS)
			{
				RegCloseKey(hRegSubKey);
				RegCloseKey(hRegKey);
				return cbValueData;
			}
			RegCloseKey(hRegSubKey);
			RegCloseKey(hRegKey);
			return 0;
		}
		RegCloseKey(hRegKey);
	}
	return -1;
}

BOOL CRegistry::SetSecurity(HKEY hKey, LPCTSTR pszSubKey, CONST CSecurityDescriptor &cSecurityDescriptor)
{
	HKEY  hRegKey;
	HKEY  hRegSubKey;

	if (RegConnectRegistry(GetComputerUNCName(), hKey, &hRegKey) == ERROR_SUCCESS)
	{
		if (RegOpenKeyEx(hRegKey, pszSubKey, 0, CheckSAM(KEY_ALL_ACCESS), &hRegSubKey) == ERROR_SUCCESS)
		{
			if (RegSetKeySecurity(hRegSubKey, cSecurityDescriptor.QueryInformation(), (PSECURITY_DESCRIPTOR)cSecurityDescriptor.GetPSECURITY_DESCRIPTOR()) == ERROR_SUCCESS)
			{
				RegCloseKey(hRegSubKey);
				RegCloseKey(hRegKey);
				return TRUE;
			}
			RegCloseKey(hRegSubKey);
		}
		RegCloseKey(hRegKey);
	}
	return FALSE;
}

BOOL CRegistry::GetSecurity(HKEY hKey, LPCTSTR pszSubKey, CSecurityDescriptor &cSecurityDescriptor) CONST
{
	HKEY  hRegKey;
	HKEY  hRegSubKey;
	DWORD  cbSecurityDescriptor;
	PSECURITY_DESCRIPTOR  pSecurityDescriptor;

	if (RegConnectRegistry(GetComputerUNCName(), hKey, &hRegKey) == ERROR_SUCCESS)
	{
		if (RegOpenKeyEx(hRegKey, pszSubKey, 0, CheckSAM(KEY_ALL_ACCESS), &hRegSubKey) == ERROR_SUCCESS)
		{
			if (RegGetKeySecurity(hRegSubKey, OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION, (PSECURITY_DESCRIPTOR)NULL, &(cbSecurityDescriptor = 0)) == ERROR_INSUFFICIENT_BUFFER)
			{
				if ((pSecurityDescriptor = (PSECURITY_DESCRIPTOR)GlobalAlloc(GPTR, cbSecurityDescriptor)) != (PSECURITY_DESCRIPTOR)NULL)
				{
					if (RegGetKeySecurity(hRegSubKey, OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION, pSecurityDescriptor, &cbSecurityDescriptor) == ERROR_SUCCESS)
					{
						if (cSecurityDescriptor.Copy(pSecurityDescriptor))
						{
							GlobalFree(pSecurityDescriptor);
							RegCloseKey(hRegSubKey);
							RegCloseKey(hRegKey);
							return TRUE;
						}
					}
					GlobalFree(pSecurityDescriptor);
				}
			}
			RegCloseKey(hRegSubKey);
		}
		RegCloseKey(hRegKey);
	}
	return FALSE;
}

CString CRegistry::ConstructQualifiedSubKey(LPCTSTR pszSubKey) CONST
{
	PSID  pSid;
	DWORD  cbSid;
	DWORD  cbDomain;
	DWORD  cbUserName;
	LPTSTR  pszDomain;
	LPTSTR  pszSid;
	CString  szSid;
	SID_NAME_USE  sSidUse;
	TCHAR  szUserName[UNLEN + 1];

	if (GetUserName(szUserName, &(cbUserName = sizeof(szUserName) / sizeof(TCHAR))))
	{
		for (LookupAccountName((LPCTSTR)NULL, szUserName, (pSid = NULL), &(cbSid = 0), (pszDomain = NULL), &(cbDomain = 0), &sSidUse); (pSid = (PSID)GlobalAlloc(GPTR, cbSid)); )
		{
			if ((pszDomain = (LPTSTR)GlobalAlloc(GPTR, (cbDomain + 1) * sizeof(TCHAR))) != (LPTSTR)NULL)
			{
				if (LookupAccountName((LPCTSTR)NULL, szUserName, pSid, &cbSid, pszDomain, &cbDomain, &sSidUse))
				{
					if (ConvertSidToStringSid(pSid, &pszSid))
					{
						szSid = pszSid;
						LocalFree(pszSid);
						GlobalFree(pszDomain);
						GlobalFree(pSid);
						return(szSid + STRING(IDS_REG_SUBKEYPART_DELIMITER) + pszSubKey);
					}
				}
				GlobalFree(pszDomain);
			}
			GlobalFree(pSid);
			break;
		}
	}
	return pszSubKey;
}

REGSAM CRegistry::CheckSAM(REGSAM regSAM) CONST
{
	SYSTEM_INFO  sSystemInfo;

	GetNativeSystemInfo(&sSystemInfo);
	return((sSystemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) ? (KEY_WOW64_32KEY | regSAM) : (KEY_WOW64_64KEY | regSAM));
}
