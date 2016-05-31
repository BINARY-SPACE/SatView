// VERSION.CPP : Version Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the version related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1992/10/26 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CVersionInfo

CVersionInfo::CVersionInfo() : CModuleToken()
{
	return;
}
CVersionInfo::CVersionInfo(LPCTSTR pszModuleName) : CModuleToken(pszModuleName)
{
	return;
}

CString CVersionInfo::QueryApplicationTitle() CONST
{
	INT  nPos;
	CString  szName;

	for (szName = QueryFileDescription(); (nPos = szName.Find(QueryProductName().Left(QueryProductName().GetLength() - 1))) >= 0; )
	{
		szName = szName.Left(nPos) + QueryProductName() + szName.Mid(nPos + QueryProductName().GetLength() - 1);
		break;
	}
	return szName;
}

CString CVersionInfo::QueryProductName() CONST
{
	CString  szInfo;

	return((QueryVersionInfo(IDS_VERSIONINFO_PRODUCTNAME, szInfo)) ? (LPCTSTR)szInfo : EMPTYSTRING);
}

CString CVersionInfo::QueryProductVersion() CONST
{
	CString  szInfo;

	return((QueryVersionInfo(IDS_VERSIONINFO_PRODUCTVERSION, szInfo)) ? (LPCTSTR)szInfo : EMPTYSTRING);
}

CString CVersionInfo::QueryFileDescription() CONST
{
	CString  szInfo;

	return((QueryVersionInfo(IDS_VERSIONINFO_FILEDESCRIPTION, szInfo)) ? (LPCTSTR)szInfo : EMPTYSTRING);
}

CString CVersionInfo::QueryFileVersion() CONST
{
	CString  szInfo;

	return((QueryVersionInfo(IDS_VERSIONINFO_FILEVERSION, szInfo)) ? (LPCTSTR)szInfo : EMPTYSTRING);
}

CString CVersionInfo::QueryOriginalFileName() CONST
{
	CString  szInfo;

	return((QueryVersionInfo(IDS_VERSIONINFO_ORIGINALFILENAME, szInfo)) ? (LPCTSTR)szInfo : EMPTYSTRING);
}

CString CVersionInfo::QueryCompanyName() CONST
{
	CString  szInfo;

	return((QueryVersionInfo(IDS_VERSIONINFO_COMPANYNAME, szInfo)) ? (LPCTSTR)szInfo : EMPTYSTRING);
}

CString CVersionInfo::QueryInternalName() CONST
{
	CString  szInfo;

	return((QueryVersionInfo(IDS_VERSIONINFO_INTERNALNAME, szInfo)) ? (LPCTSTR)szInfo : EMPTYSTRING);
}

CString CVersionInfo::QueryLegalCopyright() CONST
{
	CString  szInfo;

	return((QueryVersionInfo(IDS_VERSIONINFO_LEGALCOPYRIGHT, szInfo)) ? (LPCTSTR)szInfo : EMPTYSTRING);
}

CString CVersionInfo::QueryLegalTrademark() CONST
{
	CString  szInfo;

	return((QueryVersionInfo(IDS_VERSIONINFO_LEGALTRADEMARK, szInfo)) ? (LPCTSTR)szInfo : EMPTYSTRING);
}

CString CVersionInfo::QueryComments() CONST
{
	CString  szInfo;

	return((QueryVersionInfo(IDS_VERSIONINFO_COMMENTS, szInfo)) ? (LPCTSTR)szInfo : EMPTYSTRING);
}

BOOL CVersionInfo::QueryVersionInfo(UINT nInfoType, CString &szInfo) CONST
{
	UINT  cbVersionValue;
	DWORD  dwVersionInfoSize;
	DWORD  dwVersionInfoHandle;
	LPVOID  pVersionInfo;
	LPTSTR  pszVersionValue;
	CString  szVersionBlock;
	CString  szModuleName;

	if ((pVersionInfo = (LPVOID)GlobalAlloc(GPTR, (dwVersionInfoSize = GetFileVersionInfoSize((LPTSTR)(LPCTSTR)(szModuleName = GetModuleName()), &dwVersionInfoHandle)))) != (LPVOID)NULL)
	{
		if (GetFileVersionInfo((LPTSTR)(LPCTSTR)szModuleName, dwVersionInfoHandle, dwVersionInfoSize, pVersionInfo))
		{
			if (QueryVersionLanguageBlock(pVersionInfo, nInfoType, szVersionBlock))
			{
				if (VerQueryValue(pVersionInfo, (LPTSTR)(LPCTSTR)szVersionBlock, (LPVOID *)&pszVersionValue, &cbVersionValue))
				{
					szInfo = pszVersionValue;
					GlobalFree(pVersionInfo);
					return TRUE;
				}
			}
		}
		GlobalFree(pVersionInfo);
	}
	return FALSE;
}

BOOL CVersionInfo::QueryVersionLanguageBlock(CONST LPVOID pVersionInfo, UINT nInfoType, CString &szBlock) CONST
{
	UINT  nLanguageIndex;
	UINT  cbVersionValue;
	LPWSTR  pszLanguageID;
	LPTSTR  pszVersionValue;
	CString  szVersionInfo;
	CString  szVersionBlock;
	CStringTools  cStringTools;

	if (VerQueryValue(pVersionInfo, (LPTSTR)(LPCTSTR)(szVersionInfo = STRING(IDS_VERSIONINFO_TRANSLATIONDATA)), (LPVOID *)&pszVersionValue, &cbVersionValue))
	{
		for (nLanguageIndex = 0, pszLanguageID = (LPWSTR)pszVersionValue; nLanguageIndex < cbVersionValue / sizeof(DWORD); nLanguageIndex++)
		{
			if (pszLanguageID[2 * nLanguageIndex] == GetLanguageID() || nLanguageIndex == cbVersionValue / sizeof(DWORD) - 1)
			{
				szVersionBlock = cStringTools.ConvertUIntToPaddedString((UINT)pszLanguageID[2 * nLanguageIndex], 4, 16);
				szVersionBlock = cStringTools.AddUIntToPaddedString((UINT)pszLanguageID[2 * nLanguageIndex + 1], szVersionBlock, 4, (LPCTSTR)NULL, (LPCTSTR)NULL, 16);
				szBlock = STRING(IDS_VERSIONINFO_STRINGFILEDATA) + szVersionBlock;
				szBlock += STRING(nInfoType);
				return TRUE;
			}
		}
	}
	return FALSE;
}
