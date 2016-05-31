// PROFILE.CPP : Profile Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the profile related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Simulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CProfile

BOOL CProfile::SetIODevicesData(CONST CByteArray &nData)
{
	return((nData.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_DEVICESDATA), REG_BINARY, nData.GetData(), (INT)nData.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_DEVICESDATA)));
}

BOOL CProfile::GetIODevicesData(CByteArray &nData) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_DEVICESDATA)), nData.SetSize(max(nSize, 0)); nSize > 0 && nData.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_DEVICESDATA), &dwType, nData.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::DeleteAllInfo()
{
	CString  szSubKey;
	CStringArray  szSubKeys;
	CStringArray  szValueNames;
	CVersionInfo  cVersionInfo;

	DeleteSubKey(QuerySubKey());
	if (!EnumUserSubKeys((szSubKey = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName()), szSubKeys) && !EnumUserSubKeyValueNames(szSubKey, szValueNames)) return DeleteSubKey(szSubKey);
	return TRUE;
}

CString CProfile::QuerySubKey() CONST
{
	CString  szSubKey;
	CVersionInfo  cVersionInfo;

	szSubKey = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName();
	szSubKey += STRING(IDS_REG_SUBKEYPART_DELIMITER) + GetAppTitle();
	return szSubKey;
}

BOOL CProfile::DeleteSubKey(LPCTSTR pszSubKey)
{
	INT  nSubKey;
	INT  nSubKeys;
	CStringArray  szSubKeys;

	for (nSubKey = 0, nSubKeys = EnumUserSubKeys(pszSubKey, szSubKeys); nSubKey < nSubKeys; nSubKey++)
	{
		if (!DeleteSubKey(CString(pszSubKey) + STRING(IDS_REG_SUBKEYPART_DELIMITER) + szSubKeys.GetAt(nSubKey))) break;
		continue;
	}
	return((nSubKey == nSubKeys  &&  SetUserInfo(pszSubKey)) ? TRUE : FALSE);
}
