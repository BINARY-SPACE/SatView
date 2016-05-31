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
* 1995/04/18 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CProfile

BOOL CProfile::SetState(UINT nShow)
{
	return((nShow != (UINT)-1) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_STATE), nShow) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_STATE)));
}

BOOL CProfile::GetState(UINT &nShow) CONST
{
	DWORD  dwShow;

	if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_STATE), dwShow))
	{
		nShow = dwShow;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetPosition(LPCRECT pPosition)
{
	return SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_POSITION), REG_BINARY, (CONST BYTE *) pPosition, sizeof(RECT));
}

BOOL CProfile::GetPosition(LPRECT pPosition) CONST
{
	RECT  rRect;
	DWORD  dwType;

	if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_POSITION), &dwType, (LPBYTE)&rRect, sizeof(RECT)) == sizeof(RECT))
	{
		CopyRect(pPosition, &rRect);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetStatusBarState(CONST CUIntArray &nPaneIDs)
{
	struct {
		INT  cbSize;
		INT  cbPaneIDs;
	} sInfo;
	CByteArray  nInfo;

	sInfo.cbPaneIDs = (INT)(nPaneIDs.GetSize()*sizeof(UINT));
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbPaneIDs));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nPaneIDs.GetData(), sInfo.cbPaneIDs);
	return((nPaneIDs.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_STATUSBARSTATE), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_STATUSBARSTATE)));
}

BOOL CProfile::GetStatusBarState(CUIntArray &nPaneIDs) CONST
{
	struct {
		INT  cbSize;
		INT  cbPaneIDs;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_STATUSBARSTATE)), nInfo.SetSize(max(nSize, 0)), nPaneIDs.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_STATUSBARSTATE), &dwType, nInfo.GetData(), nSize) == nSize  &&  nSize >= sizeof(sInfo))
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), sizeof(sInfo)); sInfo.cbSize == (INT)(sizeof(sInfo) + sInfo.cbPaneIDs) && sInfo.cbPaneIDs >= 0; )
			{
				for (nPaneIDs.SetSize(sInfo.cbPaneIDs / sizeof(UINT)); nPaneIDs.GetSize() > 0; )
				{
					CopyMemory(nPaneIDs.GetData(), nInfo.GetData() + sizeof(sInfo), sInfo.cbPaneIDs);
					break;
				}
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayAreaType(UINT nType)
{
	return((nType != (UINT)-1) ? SetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATYPE), nType) : SetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATYPE)));
}

BOOL CProfile::GetDisplayAreaType(UINT &nType) CONST
{
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATYPE), dwType))
	{
		nType = dwType;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayAreaPageCount(INT nPages)
{
	return((nPages >= 0) ? SetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREAPAGECOUNT), nPages) : SetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREAPAGECOUNT)));
}

BOOL CProfile::GetDisplayAreaPageCount(INT &nPages) CONST
{
	DWORD  dwPages;

	if (GetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREAPAGECOUNT), dwPages))
	{
		nPages = dwPages;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayAreaActivePage(INT nPage)
{
	return((nPage >= 0) ? SetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREAACTIVEPAGE), nPage) : SetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREAACTIVEPAGE)));
}

BOOL CProfile::GetDisplayAreaActivePage(INT &nPage) CONST
{
	DWORD  dwPage;

	if (GetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREAACTIVEPAGE), dwPage))
	{
		nPage = dwPage;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayAreaTemporaryANDs(CONST CByteArray &nANDs)
{
	return((nANDs.GetSize() > 0) ? SetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYANDS), REG_BINARY, nANDs.GetData(), (INT)nANDs.GetSize()) : SetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYANDS)));
}

BOOL CProfile::GetDisplayAreaTemporaryANDs(CByteArray &nANDs) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYANDS)), nANDs.SetSize(max(nSize, 0)); nSize > 0 && nANDs.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYANDS), &dwType, nANDs.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetDisplayAreaTemporaryGRDs(CONST CByteArray &nGRDs)
{
	return((nGRDs.GetSize() > 0) ? SetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYGRDS), REG_BINARY, nGRDs.GetData(), (INT)nGRDs.GetSize()) : SetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYGRDS)));
}

BOOL CProfile::GetDisplayAreaTemporaryGRDs(CByteArray &nGRDs) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYGRDS)), nGRDs.SetSize(max(nSize, 0)); nSize > 0 && nGRDs.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYGRDS), &dwType, nGRDs.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetDisplayAreaTemporaryPODs(CONST CByteArray &nPODs)
{
	return((nPODs.GetSize() > 0) ? SetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYPODS), REG_BINARY, nPODs.GetData(), (INT)nPODs.GetSize()) : SetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYPODS)));
}

BOOL CProfile::GetDisplayAreaTemporaryPODs(CByteArray &nPODs) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYPODS)), nPODs.SetSize(max(nSize, 0)); nSize > 0 && nPODs.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTemporaryDisplaysSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYAREATEMPORARYPODS), &dwType, nPODs.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetDisplayPageTitle(INT nPage, LPCTSTR pszTitle)
{
	return SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGETITLE), pszTitle);
}

BOOL CProfile::GetDisplayPageTitle(INT nPage, CString &szTitle) CONST
{
	return GetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGETITLE), szTitle);
}

BOOL CProfile::SetDisplayPageWindowCount(INT nPage, INT nCount)
{
	return((nCount >= 0) ? SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEWINDOWCOUNT), nCount) : SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEWINDOWCOUNT)));
}

BOOL CProfile::GetDisplayPageWindowCount(INT nPage, INT &nCount) CONST
{
	DWORD  dwCount;

	if (GetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEWINDOWCOUNT), dwCount))
	{
		nCount = dwCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayPageScrollInfo(INT nPage, CONST SCROLLINFO *pHorzInfo, CONST SCROLLINFO *pVertInfo)
{
	SCROLLINFO  sInfo[2];

	CopyMemory(&sInfo[0], pHorzInfo, (AfxIsValidAddress(pHorzInfo, sizeof(SCROLLINFO), FALSE)) ? sizeof(SCROLLINFO) : 0);
	CopyMemory(&sInfo[1], pVertInfo, (AfxIsValidAddress(pVertInfo, sizeof(SCROLLINFO), FALSE)) ? sizeof(SCROLLINFO) : 0);
	return((AfxIsValidAddress(pHorzInfo, sizeof(SCROLLINFO), FALSE) && AfxIsValidAddress(pVertInfo, sizeof(SCROLLINFO), FALSE)) ? SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGESCROLLINFO), REG_BINARY, (CONST BYTE *) sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGESCROLLINFO)));
}

BOOL CProfile::GetDisplayPageScrollInfo(INT nPage, LPSCROLLINFO pHorzInfo, LPSCROLLINFO pVertInfo) CONST
{
	DWORD  dwType;
	SCROLLINFO  sInfo[2];

	if (GetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGESCROLLINFO), &dwType, (LPBYTE)sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(pHorzInfo, &sInfo[0], sizeof(SCROLLINFO));
		CopyMemory(pVertInfo, &sInfo[1], sizeof(SCROLLINFO));
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayPagePassword(INT nPage, LPCTSTR pszPassword)
{
	CByteArray  nPassword;
	CCryptographyTools  cCryptographyTools;

	return((AfxIsValidString(pszPassword)) ? ((cCryptographyTools.EncryptText(pszPassword, nPassword) > 0) ? SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEPASSWORD), REG_BINARY, nPassword.GetData(), (INT)nPassword.GetSize()) : FALSE) : SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEPASSWORD)));
}

BOOL CProfile::GetDisplayPagePassword(INT nPage, CString &szPassword) CONST
{
	INT  nSize;
	DWORD  dwType;
	CByteArray  nPassword;
	CCryptographyTools  cCryptographyTools;

	for (nSize = GetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEPASSWORD)), nPassword.SetSize(max(nSize, 0)); nSize > 0 && nPassword.GetSize() == nSize; ) break;
	return((nSize > 0 && GetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEPASSWORD), &dwType, nPassword.GetData(), nSize) == nSize) ? cCryptographyTools.DecryptText(nPassword, szPassword) : FALSE);
}

BOOL CProfile::SetDisplayPageUsers(INT nPage, CONST CStringArray &szUsers)
{
	return((szUsers.GetSize() > 0) ? SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEUSERS), szUsers) : SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEUSERS)));
}

BOOL CProfile::GetDisplayPageUsers(INT nPage, CStringArray &szUsers) CONST
{
	return((GetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEUSERS), szUsers) >= 0) ? TRUE : FALSE);
}

BOOL CProfile::SetDisplayPageFlags(INT nPage, UINT nFlags)
{
	DWORD  dwInfo;

	return(((dwInfo = (DWORD)nFlags) != (DWORD)-1) ? SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEFLAGS), dwInfo) : SetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEFLAGS)));
}

BOOL CProfile::GetDisplayPageFlags(INT nPage, UINT &nFlags) CONST
{
	DWORD  dwInfo;

	if (GetUserInfo(QueryDisplayPageSubKey(nPage), STRING(IDS_REG_SUBKEYVALUE_DISPLAYPAGEFLAGS), dwInfo))
	{
		nFlags = (UINT)dwInfo;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayWindowTitle(INT nPage, INT nDisplay, LPCTSTR pszTitle)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWTITLE), pszTitle);
}

BOOL CProfile::GetDisplayWindowTitle(INT nPage, INT nDisplay, CString &szTitle) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWTITLE), szTitle);
}

BOOL CProfile::SetDisplayWindowType(INT nPage, INT nDisplay, INT nType)
{
	return((nType != -1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWTYPE), nType) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWTYPE)));
}

BOOL CProfile::GetDisplayWindowType(INT nPage, INT nDisplay, INT &nType) CONST
{
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWTYPE), dwType))
	{
		nType = dwType;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayWindowScope(INT nPage, INT nDisplay, INT nScope)
{
	return((nScope != -1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWSCOPE), nScope) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWSCOPE)));
}

BOOL CProfile::GetDisplayWindowScope(INT nPage, INT nDisplay, INT &nScope) CONST
{
	DWORD  dwScope;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWSCOPE), dwScope))
	{
		nScope = dwScope;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayWindowMode(INT nPage, INT nDisplay, UINT nMode)
{
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWMODE), nMode) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWMODE)));
}

BOOL CProfile::GetDisplayWindowMode(INT nPage, INT nDisplay, UINT &nMode) CONST
{
	DWORD  dwMode;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWMODE), dwMode))
	{
		nMode = dwMode;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayWindowData(INT nPage, INT nDisplay, LPVOID pData)
{
	return((pData != (LPVOID)NULL  &&  GlobalSize(pData) > 1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWDATA), REG_BINARY, (CONST BYTE *) pData, (INT)GlobalSize(pData)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWDATA)));
}

BOOL CProfile::GetDisplayWindowData(INT nPage, INT nDisplay, LPVOID *pData) CONST
{
	INT  nSize;
	DWORD  dwType;
	LPVOID  pBlock;

	for (*pData = (LPVOID)NULL; (pBlock = ((nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWDATA))) > 0) ? (LPVOID)GlobalAlloc(GPTR, nSize) : (LPVOID)NULL); )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWDATA), &dwType, (LPBYTE)pBlock, nSize) == nSize)
		{
			CopyMemory(pData, &pBlock, sizeof(LPVOID));
			return TRUE;
		}
		GlobalFree(pBlock);
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetDisplayWindowLink(INT nPage, INT nDisplay, LPCTSTR pszLink)
{
	return((SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWLINK), pszLink)) ? TRUE : FALSE);
}

BOOL CProfile::GetDisplayWindowLink(INT nPage, INT nDisplay, CString &szLink) CONST
{
	return((GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWLINK), szLink) >= 0) ? TRUE : FALSE);
}

BOOL CProfile::SetDisplayWindowPlacement(INT nPage, INT nDisplay, LPCRECT pPosition, CONST POINT *pPoint, INT nNumber, UINT nShow, BOOL bVisible)
{
	struct {
		RECT  rPosition;
		POINT  ptPosition;
		INT  nNumber;
		UINT  nShow;
		BOOL  bVisible;
	} sInfo;

	sInfo.nShow = nShow;
	sInfo.nNumber = nNumber;
	sInfo.bVisible = bVisible;
	CopyMemory(&sInfo.rPosition, pPosition, (AfxIsValidAddress(pPosition, sizeof(RECT), FALSE)) ? sizeof(RECT) : 0);
	CopyMemory(&sInfo.ptPosition, pPoint, (AfxIsValidAddress(pPoint, sizeof(POINT), FALSE)) ? sizeof(POINT) : 0);
	return((AfxIsValidAddress(pPosition, sizeof(RECT), FALSE) && AfxIsValidAddress(pPoint, sizeof(POINT), FALSE) && nNumber >= 0 && nShow != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWPLACEMENT), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWPLACEMENT)));
}

BOOL CProfile::GetDisplayWindowPlacement(INT nPage, INT nDisplay, LPRECT pPosition, LPPOINT pPoint, INT &nNumber, UINT &nShow, BOOL &bVisible) CONST
{
	struct {
		RECT  rPosition;
		POINT  ptPosition;
		INT  nNumber;
		UINT  nShow;
		BOOL  bVisible;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWPLACEMENT), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(pPosition, &sInfo.rPosition, sizeof(RECT));
		CopyMemory(pPoint, &sInfo.ptPosition, sizeof(POINT));
		bVisible = sInfo.bVisible;
		nNumber = sInfo.nNumber;
		nShow = sInfo.nShow;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayWindowLockInformation(INT nPage, INT nDisplay, LPCTSTR pszOwner, LPCTSTR pszContact, LPCTSTR pszPassword, LPCTSTR pszReason)
{
	struct {
		INT  cbSize;
		INT  cbOwner;
		INT  cbContact;
		INT  cbPassword;
		INT  cbReason;
	} sInfo;
	CByteArray  nInfo;

	sInfo.cbOwner = (AfxIsValidString(pszOwner)) ? (lstrlen(pszOwner) + 1)*sizeof(TCHAR) : 0;
	sInfo.cbContact = (AfxIsValidString(pszContact)) ? (lstrlen(pszContact) + 1)*sizeof(TCHAR) : 0;
	sInfo.cbPassword = (AfxIsValidString(pszPassword)) ? (lstrlen(pszPassword) + 1)*sizeof(TCHAR) : 0;
	sInfo.cbReason = (AfxIsValidString(pszReason)) ? (lstrlen(pszReason) + 1)*sizeof(TCHAR) : 0;
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbOwner + sInfo.cbContact + sInfo.cbPassword + sInfo.cbReason));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), pszOwner, sInfo.cbOwner);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbOwner, pszContact, sInfo.cbContact);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbOwner + sInfo.cbContact, pszPassword, sInfo.cbPassword);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbOwner + sInfo.cbContact + sInfo.cbPassword, pszReason, sInfo.cbReason);
	return((AfxIsValidString(pszOwner) && AfxIsValidString(pszContact) && AfxIsValidString(pszPassword) && AfxIsValidString(pszReason)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWLOCKINFORMATION), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWLOCKINFORMATION)));
}

BOOL CProfile::GetDisplayWindowLockInformation(INT nPage, INT nDisplay, CString &szOwner, CString &szContact, CString &szPassword, CString &szReason) CONST
{
	struct {
		INT  cbSize;
		INT  cbOwner;
		INT  cbContact;
		INT  cbPassword;
		INT  cbReason;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWLOCKINFORMATION)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWLOCKINFORMATION), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), (nSize > sizeof(sInfo)) ? sizeof(sInfo) : 0); nSize > sizeof(sInfo) && nSize == sInfo.cbSize && sInfo.cbSize == sizeof(sInfo) + sInfo.cbOwner + sInfo.cbContact + sInfo.cbPassword + sInfo.cbReason && sInfo.cbOwner > 0 && sInfo.cbContact > 0 && sInfo.cbPassword > 0 && sInfo.cbReason > 0; )
			{
				CopyMemory(szOwner.GetBufferSetLength(STRINGCHARS(sInfo.cbOwner)), nInfo.GetData() + sizeof(sInfo), STRINGBYTES(sInfo.cbOwner));
				CopyMemory(szContact.GetBufferSetLength(STRINGCHARS(sInfo.cbContact)), nInfo.GetData() + sizeof(sInfo) + sInfo.cbOwner, STRINGBYTES(sInfo.cbContact));
				CopyMemory(szPassword.GetBufferSetLength(STRINGCHARS(sInfo.cbPassword)), nInfo.GetData() + sizeof(sInfo) + sInfo.cbOwner + sInfo.cbContact, STRINGBYTES(sInfo.cbPassword));
				CopyMemory(szReason.GetBufferSetLength(STRINGCHARS(sInfo.cbReason)), nInfo.GetData() + sizeof(sInfo) + sInfo.cbOwner + sInfo.cbContact + sInfo.cbPassword, STRINGBYTES(sInfo.cbReason));
				szOwner.ReleaseBuffer();
				szContact.ReleaseBuffer();
				szPassword.ReleaseBuffer();
				szReason.ReleaseBuffer();
				return TRUE;
			}
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetLoginOptions(CONST CByteArray &nOptionsInfo)
{
	return((nOptionsInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_LOGINOPTIONS), REG_BINARY, nOptionsInfo.GetData(), (INT)nOptionsInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_LOGINOPTIONS)));
}

BOOL CProfile::GetLoginOptions(CByteArray &nOptionsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_LOGINOPTIONS)), nOptionsInfo.SetSize(max(nSize, 0)); nSize > 0 && nOptionsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_LOGINOPTIONS), &dwType, nOptionsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetPrintProfilesInfo(CONST CByteArray &nProfilesInfo)
{
	return((nProfilesInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_PRINTPROFILESINFO), REG_BINARY, nProfilesInfo.GetData(), (INT)nProfilesInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_PRINTPROFILESINFO)));
}

BOOL CProfile::GetPrintProfilesInfo(CByteArray &nProfilesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_PRINTPROFILESINFO)), nProfilesInfo.SetSize(max(nSize, 0)); nSize > 0 && nProfilesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_PRINTPROFILESINFO), &dwType, nProfilesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetAuditionProfilesInfo(CONST CByteArray &nProfilesInfo)
{
	return((nProfilesInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_AUDITIONPROFILESINFO), REG_BINARY, nProfilesInfo.GetData(), (INT)nProfilesInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_AUDITIONPROFILESINFO)));
}

BOOL CProfile::GetAuditionProfilesInfo(CByteArray &nProfilesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_AUDITIONPROFILESINFO)), nProfilesInfo.SetSize(max(nSize, 0)); nSize > 0 && nProfilesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_AUDITIONPROFILESINFO), &dwType, nProfilesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetNotificationProfilesInfo(CONST CByteArray &nProfilesInfo)
{
	return((nProfilesInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_NOTIFICATIONPROFILESINFO), REG_BINARY, nProfilesInfo.GetData(), (INT)nProfilesInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_NOTIFICATIONPROFILESINFO)));
}

BOOL CProfile::GetNotificationProfilesInfo(CByteArray &nProfilesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_NOTIFICATIONPROFILESINFO)), nProfilesInfo.SetSize(max(nSize, 0)); nSize > 0 && nProfilesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_NOTIFICATIONPROFILESINFO), &dwType, nProfilesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetNotificationJobsInfo(CONST CByteArray &nJobsInfo)
{
	return((nJobsInfo.GetSize() > 0) ? SetUserInfo(QueryNotificationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_NOTIFICATIONJOBSINFO), REG_BINARY, nJobsInfo.GetData(), (INT)nJobsInfo.GetSize()) : SetUserInfo(QueryNotificationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_NOTIFICATIONJOBSINFO)));
}

BOOL CProfile::GetNotificationJobsInfo(CByteArray &nJobsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryNotificationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_NOTIFICATIONJOBSINFO)), nJobsInfo.SetSize(max(nSize, 0)); nSize > 0 && nJobsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryNotificationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_NOTIFICATIONJOBSINFO), &dwType, nJobsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetSystemAlertsInfo(CONST CByteArray &nAlertsInfo)
{
	return((nAlertsInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_SYSTEMALERTSINFO), REG_BINARY, nAlertsInfo.GetData(), (INT)nAlertsInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_SYSTEMALERTSINFO)));
}

BOOL CProfile::GetSystemAlertsInfo(CByteArray &nAlertsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_SYSTEMALERTSINFO)), nAlertsInfo.SetSize(max(nSize, 0)); nSize > 0 && nAlertsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_SYSTEMALERTSINFO), &dwType, nAlertsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryServiceInfo(CONST CByteArray &nServiceInfo)
{
	return((nServiceInfo.GetSize() > 0) ? SetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYSERVICEINFO), REG_BINARY, nServiceInfo.GetData(), (INT)nServiceInfo.GetSize()) : SetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYSERVICEINFO)));
}

BOOL CProfile::GetTelemetryServiceInfo(CByteArray &nServiceInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYSERVICEINFO)), nServiceInfo.SetSize(max(nSize, 0)); nSize > 0 && nServiceInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYSERVICEINFO), &dwType, nServiceInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryServiceConfigurationInfo(CONST CByteArray &nConfigurationInfo)
{
	return((nConfigurationInfo.GetSize() > 0) ? SetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYSERVICECONFIGURATIONINFO), REG_BINARY, nConfigurationInfo.GetData(), (INT)nConfigurationInfo.GetSize()) : SetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYSERVICECONFIGURATIONINFO)));
}

BOOL CProfile::GetTelemetryServiceConfigurationInfo(CByteArray &nConfigurationInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYSERVICECONFIGURATIONINFO)), nConfigurationInfo.SetSize(max(nSize, 0)); nSize > 0 && nConfigurationInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYSERVICECONFIGURATIONINFO), &dwType, nConfigurationInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryEventsInfo(CONST CByteArray &nEventsInfo)
{
	return((nEventsInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYEVENTSINFO), REG_BINARY, nEventsInfo.GetData(), (INT)nEventsInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYEVENTSINFO)));
}

BOOL CProfile::GetTelemetryEventsInfo(CByteArray &nEventsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYEVENTSINFO)), nEventsInfo.SetSize(max(nSize, 0)); nSize > 0 && nEventsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYEVENTSINFO), &dwType, nEventsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryReportsInfo(CONST CByteArray &nReportsInfo)
{
	return((nReportsInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYREPORTSINFO), REG_BINARY, nReportsInfo.GetData(), (INT)nReportsInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYREPORTSINFO)));
}

BOOL CProfile::GetTelemetryReportsInfo(CByteArray &nReportsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYREPORTSINFO)), nReportsInfo.SetSize(max(nSize, 0)); nSize > 0 && nReportsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYREPORTSINFO), &dwType, nReportsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryHistoricalReportsInfo(CONST CByteArray &nHistoricalReportsInfo)
{
	return((nHistoricalReportsInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYHISTORICALREPORTSINFO), REG_BINARY, nHistoricalReportsInfo.GetData(), (INT)nHistoricalReportsInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYHISTORICALREPORTSINFO)));
}

BOOL CProfile::GetTelemetryHistoricalReportsInfo(CByteArray &nHistoricalReportsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYHISTORICALREPORTSINFO)), nHistoricalReportsInfo.SetSize(max(nSize, 0)); nSize > 0 && nHistoricalReportsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYHISTORICALREPORTSINFO), &dwType, nHistoricalReportsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryReportJobsInfo(CONST CByteArray &nReportJobsInfo, CONST CByteArray &nHistoricalReportJobsInfo)
{
	struct {
		INT  cbSize;
		INT  cbJobs[2];
	} sInfo;
	CByteArray  nInfo;

	for (nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + (sInfo.cbJobs[0] = (INT)nReportJobsInfo.GetSize()) + (sInfo.cbJobs[1] = (INT)nHistoricalReportJobsInfo.GetSize()))); nInfo.GetSize() == sInfo.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
		CopyMemory(nInfo.GetData() + sizeof(sInfo), nReportJobsInfo.GetData(), sInfo.cbJobs[0]);
		CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbJobs[0], nHistoricalReportJobsInfo.GetData(), sInfo.cbJobs[1]);
		break;
	}
	return((nReportJobsInfo.GetSize() > 0 || nHistoricalReportJobsInfo.GetSize() > 0) ? SetUserInfo(QueryTelemetryReportsServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYREPORTJOBSINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryTelemetryReportsServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYREPORTJOBSINFO)));
}

BOOL CProfile::GetTelemetryReportJobsInfo(CByteArray &nReportJobsInfo, CByteArray &nHistoricalReportJobsInfo) CONST
{
	struct {
		INT  cbSize;
		INT  cbJobs[2];
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryTelemetryReportsServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYREPORTJOBSINFO)), nInfo.SetSize(max(nSize, 0)), nReportJobsInfo.RemoveAll(), nHistoricalReportJobsInfo.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryTelemetryReportsServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYREPORTJOBSINFO), &dwType, nInfo.GetData(), nSize) == nSize  &&  nSize >= sizeof(sInfo))
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), sizeof(sInfo)); sInfo.cbSize == (INT)(sizeof(sInfo) + sInfo.cbJobs[0] + sInfo.cbJobs[1]) && sInfo.cbJobs[0] >= 0 && sInfo.cbJobs[1] >= 0; )
			{
				for (nReportJobsInfo.SetSize(sInfo.cbJobs[0]), nHistoricalReportJobsInfo.SetSize(sInfo.cbJobs[1]); nReportJobsInfo.GetSize() == sInfo.cbJobs[0] && nHistoricalReportJobsInfo.GetSize() == sInfo.cbJobs[1]; )
				{
					CopyMemory(nReportJobsInfo.GetData(), nInfo.GetData() + sizeof(sInfo), sInfo.cbJobs[0]);
					CopyMemory(nHistoricalReportJobsInfo.GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbJobs[0], sInfo.cbJobs[1]);
					return TRUE;
				}
				nReportJobsInfo.RemoveAll();
				nHistoricalReportJobsInfo.RemoveAll();
				break;
			}
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryArchivesSettingsInfo(CONST CByteArray &nArchivesInfo)
{
	return((nArchivesInfo.GetSize() > 0) ? SetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESSETTINGSINFO), REG_BINARY, nArchivesInfo.GetData(), (INT)nArchivesInfo.GetSize()) : SetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESSETTINGSINFO)));
}

BOOL CProfile::GetTelemetryArchivesSettingsInfo(CByteArray &nArchivesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESSETTINGSINFO)), nArchivesInfo.SetSize(max(nSize, 0)); nSize > 0 && nArchivesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESSETTINGSINFO), &dwType, nArchivesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryArchivesBackupInfo(CONST CByteArray &nArchivesInfo)
{
	return((nArchivesInfo.GetSize() > 0) ? SetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESBACKUPINFO), REG_BINARY, nArchivesInfo.GetData(), (INT)nArchivesInfo.GetSize()) : SetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESBACKUPINFO)));
}

BOOL CProfile::GetTelemetryArchivesBackupInfo(CByteArray &nArchivesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESBACKUPINFO)), nArchivesInfo.SetSize(max(nSize, 0)); nSize > 0 && nArchivesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESBACKUPINFO), &dwType, nArchivesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryArchivesExtractionInfo(CONST CByteArray &nArchivesInfo)
{
	return((nArchivesInfo.GetSize() > 0) ? SetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESEXTRACTIONINFO), REG_BINARY, nArchivesInfo.GetData(), (INT)nArchivesInfo.GetSize()) : SetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESEXTRACTIONINFO)));
}

BOOL CProfile::GetTelemetryArchivesExtractionInfo(CByteArray &nArchivesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESEXTRACTIONINFO)), nArchivesInfo.SetSize(max(nSize, 0)); nSize > 0 && nArchivesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESEXTRACTIONINFO), &dwType, nArchivesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryArchivesExtractionJobsInfo(CONST CByteArray &nJobsInfo)
{
	return((nJobsInfo.GetSize() > 0) ? SetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESEXTRACTIONJOBSINFO), REG_BINARY, nJobsInfo.GetData(), (INT)nJobsInfo.GetSize()) : SetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESEXTRACTIONJOBSINFO)));
}

BOOL CProfile::GetTelemetryArchivesExtractionJobsInfo(CByteArray &nJobsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESEXTRACTIONJOBSINFO)), nJobsInfo.SetSize(max(nSize, 0)); nSize > 0 && nJobsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYARCHIVESEXTRACTIONJOBSINFO), &dwType, nJobsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryHistoryFileExtractionInfo(CONST CByteArray &nFileInfo)
{
	return((nFileInfo.GetSize() > 0) ? SetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYHISTORYFILEEXTRACTIONINFO), REG_BINARY, nFileInfo.GetData(), (INT)nFileInfo.GetSize()) : SetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYHISTORYFILEEXTRACTIONINFO)));
}

BOOL CProfile::GetTelemetryHistoryFileExtractionInfo(CByteArray &nFileInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYHISTORYFILEEXTRACTIONINFO)), nFileInfo.SetSize(max(nSize, 0)); nSize > 0 && nFileInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelemetryArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYHISTORYFILEEXTRACTIONINFO), &dwType, nFileInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelemetryParameterSetsInfo(CONST CByteArray &nSetsInfo)
{
	return((nSetsInfo.GetSize() > 0) ? SetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYPARAMETERSETSINFO), REG_BINARY, nSetsInfo.GetData(), (INT)nSetsInfo.GetSize()) : SetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYPARAMETERSETSINFO)));
}

BOOL CProfile::GetTelemetryParameterSetsInfo(CByteArray &nSetsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYPARAMETERSETSINFO)), nSetsInfo.SetSize(max(nSize, 0)); nSize > 0 && nSetsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelemetryServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELEMETRYPARAMETERSETSINFO), &dwType, nSetsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelecommandServiceInfo(CONST CByteArray &nServiceInfo)
{
	return((nServiceInfo.GetSize() > 0) ? SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICEINFO), REG_BINARY, nServiceInfo.GetData(), (INT)nServiceInfo.GetSize()) : SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICEINFO)));
}

BOOL CProfile::GetTelecommandServiceInfo(CByteArray &nServiceInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICEINFO)), nServiceInfo.SetSize(max(nSize, 0)); nSize > 0 && nServiceInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICEINFO), &dwType, nServiceInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelecommandServiceConfigurationInfo(CONST CByteArray &nConfigurationInfo)
{
	return((nConfigurationInfo.GetSize() > 0) ? SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICECONFIGURATIONINFO), REG_BINARY, nConfigurationInfo.GetData(), (INT)nConfigurationInfo.GetSize()) : SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICECONFIGURATIONINFO)));
}

BOOL CProfile::GetTelecommandServiceConfigurationInfo(CByteArray &nConfigurationInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICECONFIGURATIONINFO)), nConfigurationInfo.SetSize(max(nSize, 0)); nSize > 0 && nConfigurationInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICECONFIGURATIONINFO), &dwType, nConfigurationInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelecommandServiceContentsInfo(CONST CByteArray &nContentsInfo)
{
	return((nContentsInfo.GetSize() > 0) ? SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICECONTENTSINFO), REG_BINARY, nContentsInfo.GetData(), (INT)nContentsInfo.GetSize()) : SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICECONTENTSINFO)));
}

BOOL CProfile::GetTelecommandServiceContentsInfo(CByteArray &nContentsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICECONTENTSINFO)), nContentsInfo.SetSize(max(nSize, 0)); nSize > 0 && nContentsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICECONTENTSINFO), &dwType, nContentsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelecommandServiceLoggingInfo(UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent)
{
	struct {
		INT  cbSize;
		INT  cbArchivalFileName;
		INT  cbRetrievalFileName;
		UINT  nArchivalPolicy;
		UINT  nRetrievalReloadCount;
		DWORDLONG  dwArchivalRetention;
		TIMEKEY  tArchivalRetention;
		BOOL  bShowAsEvent;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bShowAsEvent = bShowAsEvent;
	sInfo.nArchivalPolicy = nArchivalPolicy;
	sInfo.dwArchivalRetention = dwArchivalRetention;
	sInfo.nRetrievalReloadCount = nRetrievalReloadCount;
	sInfo.tArchivalRetention = tArchivalRetention.GetTotalSeconds();
	sInfo.cbArchivalFileName = (AfxIsValidString(pszArchivalFileName)) ? ((lstrlen(pszArchivalFileName) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbRetrievalFileName = (AfxIsValidString(pszRetrievalFileName)) ? ((lstrlen(pszRetrievalFileName) + 1)*sizeof(TCHAR)) : 0;
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbArchivalFileName + sInfo.cbRetrievalFileName));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), pszArchivalFileName, sInfo.cbArchivalFileName);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbArchivalFileName, pszRetrievalFileName, sInfo.cbRetrievalFileName);
	return((AfxIsValidString(pszArchivalFileName) && AfxIsValidString(pszRetrievalFileName)) ? SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICELOGGINGINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICELOGGINGINFO)));
}

BOOL CProfile::GetTelecommandServiceLoggingInfo(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST
{
	struct {
		INT  cbSize;
		INT  cbArchivalFileName;
		INT  cbRetrievalFileName;
		UINT  nArchivalPolicy;
		UINT  nRetrievalReloadCount;
		DWORDLONG  dwArchivalRetention;
		TIMEKEY  tArchivalRetention;
		BOOL  bShowAsEvent;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICELOGGINGINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICELOGGINGINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbArchivalFileName + sInfo.cbRetrievalFileName)
				{
					CopyMemory(szArchivalFileName.GetBufferSetLength(STRINGCHARS(sInfo.cbArchivalFileName)), nInfo.GetData() + sizeof(sInfo), STRINGBYTES(sInfo.cbArchivalFileName));
					CopyMemory(szRetrievalFileName.GetBufferSetLength(STRINGCHARS(sInfo.cbRetrievalFileName)), nInfo.GetData() + sizeof(sInfo) + sInfo.cbArchivalFileName, STRINGBYTES(sInfo.cbRetrievalFileName));
					nRetrievalReloadCount = sInfo.nRetrievalReloadCount;
					dwArchivalRetention = sInfo.dwArchivalRetention;
					tArchivalRetention = sInfo.tArchivalRetention;
					nArchivalPolicy = sInfo.nArchivalPolicy;
					bShowAsEvent = sInfo.bShowAsEvent;
					szArchivalFileName.ReleaseBuffer();
					szRetrievalFileName.ReleaseBuffer();
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTelecommandServiceProcessInfo(CONST CByteArray &nProcessInfo)
{
	return((nProcessInfo.GetSize() > 0) ? SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICEPROCESSINFO), REG_BINARY, nProcessInfo.GetData(), (INT)nProcessInfo.GetSize()) : SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICEPROCESSINFO)));
}

BOOL CProfile::GetTelecommandServiceProcessInfo(CByteArray &nProcessInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICEPROCESSINFO)), nProcessInfo.SetSize(max(nSize, 0)); nSize > 0 && nProcessInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDSERVICEPROCESSINFO), &dwType, nProcessInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelecommandDiagnosticsOversamplingDumpsInfo(CONST CByteArray &nDumpsInfo)
{
	return((nDumpsInfo.GetSize() > 0) ? SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDDIAGNOSTICSOVERSAMPLINGDUMPSINFO), REG_BINARY, nDumpsInfo.GetData(), (INT)nDumpsInfo.GetSize()) : SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDDIAGNOSTICSOVERSAMPLINGDUMPSINFO)));
}

BOOL CProfile::GetTelecommandDiagnosticsOversamplingDumpsInfo(CByteArray &nDumpsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDDIAGNOSTICSOVERSAMPLINGDUMPSINFO)), nDumpsInfo.SetSize(max(nSize, 0)); nSize > 0 && nDumpsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDDIAGNOSTICSOVERSAMPLINGDUMPSINFO), &dwType, nDumpsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelecommandArchivesSettingsInfo(CONST CByteArray &nArchivesInfo)
{
	return((nArchivesInfo.GetSize() > 0) ? SetUserInfo(QueryTelecommandArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDARCHIVESSETTINGSINFO), REG_BINARY, nArchivesInfo.GetData(), (INT)nArchivesInfo.GetSize()) : SetUserInfo(QueryTelecommandArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDARCHIVESSETTINGSINFO)));
}

BOOL CProfile::GetTelecommandArchivesSettingsInfo(CByteArray &nArchivesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelecommandArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDARCHIVESSETTINGSINFO)), nArchivesInfo.SetSize(max(nSize, 0)); nSize > 0 && nArchivesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelecommandArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDARCHIVESSETTINGSINFO), &dwType, nArchivesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelecommandArchivesBackupInfo(CONST CByteArray &nArchivesInfo)
{
	return((nArchivesInfo.GetSize() > 0) ? SetUserInfo(QueryTelecommandArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDARCHIVESBACKUPINFO), REG_BINARY, nArchivesInfo.GetData(), (INT)nArchivesInfo.GetSize()) : SetUserInfo(QueryTelecommandArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDARCHIVESBACKUPINFO)));
}

BOOL CProfile::GetTelecommandArchivesBackupInfo(CByteArray &nArchivesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelecommandArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDARCHIVESBACKUPINFO)), nArchivesInfo.SetSize(max(nSize, 0)); nSize > 0 && nArchivesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelecommandArchivesSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDARCHIVESBACKUPINFO), &dwType, nArchivesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTelecommandParameterSetsInfo(CONST CByteArray &nSetsInfo)
{
	return((nSetsInfo.GetSize() > 0) ? SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDPARAMETERSETSINFO), REG_BINARY, nSetsInfo.GetData(), (INT)nSetsInfo.GetSize()) : SetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDPARAMETERSETSINFO)));
}

BOOL CProfile::GetTelecommandParameterSetsInfo(CByteArray &nSetsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDPARAMETERSETSINFO)), nSetsInfo.SetSize(max(nSize, 0)); nSize > 0 && nSetsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryTelecommandServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TELECOMMANDPARAMETERSETSINFO), &dwType, nSetsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetMemoryDumpsServiceSettingsInfo(UINT nCharset)
{
	return((nCharset != (UINT)-1) ? SetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICESETTINGSINFO), nCharset) : SetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICESETTINGSINFO)));
}

BOOL CProfile::GetMemoryDumpsServiceSettingsInfo(UINT &nCharset) CONST
{
	DWORD  dwCharset;

	for (; GetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICESETTINGSINFO), dwCharset); )
	{
		nCharset = dwCharset;
		break;
	}
	return TRUE;
}

BOOL CProfile::SetMemoryDumpsServiceAvailabilityInfo(UINT nCode, CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	struct {
		UINT  nCode;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nCode = nCode;
	sInfo.tStartTime = tStartTime.GetTotalSeconds();
	sInfo.tStopTime = tStopTime.GetTotalSeconds();
	return((nCode != (UINT)-1) ? SetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEAVAILABILITYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEAVAILABILITYINFO)));
}

BOOL CProfile::GetMemoryDumpsServiceAvailabilityInfo(UINT &nCode, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	struct {
		UINT  nCode;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	INT  cbInfo;
	DWORD  dwType;

	if ((cbInfo = GetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEAVAILABILITYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo))) == sizeof(sInfo))
	{
		nCode = sInfo.nCode;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return((cbInfo < 0) ? TRUE : FALSE);
}

BOOL CProfile::SetMemoryDumpsServiceDumpInfo(CONST CByteArray &nDumpInfo)
{
	return((nDumpInfo.GetSize() > 0) ? SetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEDUMPINFO), REG_BINARY, nDumpInfo.GetData(), (INT)nDumpInfo.GetSize()) : SetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEDUMPINFO)));
}

BOOL CProfile::GetMemoryDumpsServiceDumpInfo(CByteArray &nDumpInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEDUMPINFO)), nDumpInfo.SetSize(max(nSize, 0)); nSize > 0 && nDumpInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEDUMPINFO), &dwType, nDumpInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetMemoryDumpsServiceFTPQueueInfo(CONST CByteArray &nQueueInfo)
{
	return((nQueueInfo.GetSize() > 0) ? SetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEFTPQUEUEINFO), REG_BINARY, nQueueInfo.GetData(), (INT)nQueueInfo.GetSize()) : SetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEFTPQUEUEINFO)));
}

BOOL CProfile::GetMemoryDumpsServiceFTPQueueInfo(CByteArray &nQueueInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEFTPQUEUEINFO)), nQueueInfo.SetSize(max(nSize, 0)); nSize > 0 && nQueueInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryMemoryDumpServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_MEMORYDUMPSSERVICEFTPQUEUEINFO), &dwType, nQueueInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetANDLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDLAYOUTNAME), pszName);
}

BOOL CProfile::GetANDLayoutName(INT nPage, INT nDisplay, CString &szName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDLAYOUTNAME), szName);
}

BOOL CProfile::SetANDLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST CUIntArray &nColors, BOOL bInvalidData, BOOL bBadData, BOOL bToolTips)
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
		UINT  nColors;
		BOOL  bInvalidData;
		BOOL  bBadData;
		BOOL  bToolTips;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bBadData = bBadData;
	sInfo.bInvalidData = bInvalidData;
	sInfo.bToolTips = bToolTips;
	sInfo.nColumns = (UINT)nColumns.GetSize();
	sInfo.nWidths = (UINT)nWidths.GetSize();
	sInfo.nColors = (UINT)nColors.GetSize();
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + (nColumns.GetSize() + nWidths.GetSize() + nColors.GetSize())*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nColumns.GetData(), nColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nColumns.GetSize()*sizeof(UINT), nWidths.GetData(), nWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nColumns.GetSize()*sizeof(UINT) + nWidths.GetSize()*sizeof(UINT), nColors.GetData(), nColors.GetSize()*sizeof(UINT));
	return((nColumns.GetSize() > 0 && nWidths.GetSize() > 0 && nColors.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDLAYOUTINFO)));
}

BOOL CProfile::GetANDLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nColumns, CUIntArray &nWidths, CUIntArray &nColors, BOOL &bInvalidData, BOOL &bBadData, BOOL &bToolTips) CONST
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
		UINT  nColors;
		BOOL  bInvalidData;
		BOOL  bBadData;
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + (sInfo.nColumns + sInfo.nWidths + sInfo.nColors)*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nColumns.SetSize(sInfo.nColumns);
					CopyMemory(nColumns.GetData(), nInfo.GetData(), nColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColumns*sizeof(UINT));
					nWidths.SetSize(sInfo.nWidths);
					CopyMemory(nWidths.GetData(), nInfo.GetData(), nWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nWidths*sizeof(UINT));
					nColors.SetSize(sInfo.nColors);
					CopyMemory(nColors.GetData(), nInfo.GetData(), nColors.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColors*sizeof(UINT));
					bInvalidData = sInfo.bInvalidData;
					bBadData = sInfo.bBadData;
					bToolTips = sInfo.bToolTips;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetANDFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont, CONST LOGFONT *pDefaultTitleFont, CONST LOGFONT *pLabelsFont, CONST LOGFONT *pDefaultLabelsFont, CONST LOGFONT *pItemsFont, CONST LOGFONT *pDefaultItemsFont, CONST LOGFONT *pValuesFont, CONST LOGFONT *pDefaultValuesFont)
{
	LOGFONT  sFontsInfo[2][4];

	CopyMemory(&sFontsInfo[0][0], pTitleFont, (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[0][1], pLabelsFont, (AfxIsValidAddress(pLabelsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[0][2], pItemsFont, (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[0][3], pValuesFont, (AfxIsValidAddress(pValuesFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][0], pDefaultTitleFont, (AfxIsValidAddress(pDefaultTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][1], pDefaultLabelsFont, (AfxIsValidAddress(pDefaultLabelsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][2], pDefaultItemsFont, (AfxIsValidAddress(pDefaultItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][3], pDefaultValuesFont, (AfxIsValidAddress(pDefaultValuesFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pLabelsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pValuesFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDefaultTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDefaultLabelsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDefaultItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDefaultValuesFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDFONTSINFO)));
}

BOOL CProfile::GetANDFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pDefaultTitleFont, LOGFONT *pLabelsFont, LOGFONT *pDefaultLabelsFont, LOGFONT *pItemsFont, LOGFONT *pDefaultItemsFont, LOGFONT *pValuesFont, LOGFONT *pDefaultValuesFont) CONST
{
	INT  cbInfo;
	DWORD  dwType;
	LOGFONT  sFontsInfo[2][4];

	if ((cbInfo = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo))) >= sizeof(sFontsInfo[0]))
	{
		CopyMemory(pTitleFont, &sFontsInfo[0][0], (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pLabelsFont, &sFontsInfo[0][1], (AfxIsValidAddress(pLabelsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pItemsFont, &sFontsInfo[0][2], (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pValuesFont, &sFontsInfo[0][3], (AfxIsValidAddress(pValuesFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDefaultTitleFont, (cbInfo == sizeof(sFontsInfo)) ? &sFontsInfo[1][0] : &sFontsInfo[0][0], (AfxIsValidAddress(pDefaultTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDefaultLabelsFont, (cbInfo == sizeof(sFontsInfo)) ? &sFontsInfo[1][1] : &sFontsInfo[0][1], (AfxIsValidAddress(pDefaultLabelsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDefaultItemsFont, (cbInfo == sizeof(sFontsInfo)) ? &sFontsInfo[1][2] : &sFontsInfo[0][2], (AfxIsValidAddress(pDefaultItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDefaultValuesFont, (cbInfo == sizeof(sFontsInfo)) ? &sFontsInfo[1][3] : &sFontsInfo[0][3], (AfxIsValidAddress(pDefaultValuesFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetANDModeInfo(INT nPage, INT nDisplay, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nMode = nMode;
	sInfo.nSpeed = nSpeed;
	sInfo.tInterval = tInterval.GetTotalSeconds();
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDMODEINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDMODEINFO)));
}

BOOL CProfile::GetANDModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDMODEINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		nMode = sInfo.nMode;
		nSpeed = sInfo.nSpeed;
		tInterval = sInfo.tInterval;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetANDPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDPRINTINFO)));
}

BOOL CProfile::GetANDPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetANDRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDRETRIEVEFILENAME), pszFileName);
}

BOOL CProfile::GetANDRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDRETRIEVEFILENAME), szFileName);
}

BOOL CProfile::SetGRDLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDLAYOUTNAME), pszName);
}

BOOL CProfile::GetGRDLayoutName(INT nPage, INT nDisplay, CString &szName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDLAYOUTNAME), szName);
}

BOOL CProfile::SetGRDLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST CUIntArray &nColors, CONST CByteArray &nMarkerData, CONST CByteArray &nScalingData, BOOL bInvalidData, BOOL bBadData, BOOL bToolTips)
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
		UINT  nColors;
		UINT  cbMarkerData;
		UINT  cbScalingData;
		BOOL  bInvalidData;
		BOOL  bBadData;
		BOOL  bToolTips;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bBadData = bBadData;
	sInfo.bInvalidData = bInvalidData;
	sInfo.bToolTips = bToolTips;
	sInfo.nColumns = (UINT)nColumns.GetSize();
	sInfo.nWidths = (UINT)nWidths.GetSize();
	sInfo.nColors = (UINT)nColors.GetSize();
	sInfo.cbMarkerData = (UINT)(nMarkerData.GetSize()*sizeof(BYTE));
	sInfo.cbScalingData = (UINT)(nScalingData.GetSize()*sizeof(BYTE));
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + (nColumns.GetSize() + nWidths.GetSize() + nColors.GetSize())*sizeof(UINT) + sInfo.cbMarkerData + sInfo.cbScalingData)));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nColumns.GetData(), nColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nColumns.GetSize()*sizeof(UINT), nWidths.GetData(), nWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nColumns.GetSize()*sizeof(UINT) + nWidths.GetSize()*sizeof(UINT), nColors.GetData(), nColors.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nColumns.GetSize()*sizeof(UINT) + nWidths.GetSize()*sizeof(UINT) + nColors.GetSize()*sizeof(UINT), nMarkerData.GetData(), sInfo.cbMarkerData);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nColumns.GetSize()*sizeof(UINT) + nWidths.GetSize()*sizeof(UINT) + nColors.GetSize()*sizeof(UINT) + sInfo.cbMarkerData, nScalingData.GetData(), sInfo.cbScalingData);
	return((nColumns.GetSize() > 0 && nWidths.GetSize() > 0 && nColors.GetSize() > 0 && nScalingData.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDLAYOUTINFO)));
}

BOOL CProfile::GetGRDLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nColumns, CUIntArray &nWidths, CUIntArray &nColors, CByteArray &nMarkerData, CByteArray &nScalingData, BOOL &bInvalidData, BOOL &bBadData, BOOL &bToolTips) CONST
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
		UINT  nColors;
		UINT  cbMarkerData;
		UINT  cbScalingData;
		BOOL  bInvalidData;
		BOOL  bBadData;
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + (sInfo.nColumns + sInfo.nWidths + sInfo.nColors)*sizeof(UINT) + sInfo.cbMarkerData + sInfo.cbScalingData &&  sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nColumns.SetSize(sInfo.nColumns);
					CopyMemory(nColumns.GetData(), nInfo.GetData(), nColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColumns*sizeof(UINT));
					nWidths.SetSize(sInfo.nWidths);
					CopyMemory(nWidths.GetData(), nInfo.GetData(), nWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nWidths*sizeof(UINT));
					nColors.SetSize(sInfo.nColors);
					CopyMemory(nColors.GetData(), nInfo.GetData(), nColors.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColors*sizeof(UINT));
					nMarkerData.SetSize(sInfo.cbMarkerData / sizeof(BYTE));
					CopyMemory(nMarkerData.GetData(), nInfo.GetData(), sInfo.cbMarkerData);
					nInfo.RemoveAt(0, sInfo.cbMarkerData);
					nScalingData.SetSize(sInfo.cbScalingData / sizeof(BYTE));
					CopyMemory(nScalingData.GetData(), nInfo.GetData(), sInfo.cbScalingData);
					nInfo.RemoveAt(0, sInfo.cbScalingData);
					bInvalidData = sInfo.bInvalidData;
					bBadData = sInfo.bBadData;
					bToolTips = sInfo.bToolTips;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetGRDFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont, CONST LOGFONT *pDefaultTitleFont, CONST LOGFONT *pItemsFont, CONST LOGFONT *pDefaultItemsFont, CONST LOGFONT *pValuesFont, CONST LOGFONT *pDefaultValuesFont, CONST LOGFONT *pAxesFont, CONST LOGFONT *pDefaultAxesFont)
{
	LOGFONT  sFontsInfo[2][4];

	CopyMemory(&sFontsInfo[0][0], pTitleFont, (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[0][1], pItemsFont, (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[0][2], pValuesFont, (AfxIsValidAddress(pValuesFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[0][3], pAxesFont, (AfxIsValidAddress(pAxesFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][0], pDefaultTitleFont, (AfxIsValidAddress(pDefaultTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][1], pDefaultItemsFont, (AfxIsValidAddress(pDefaultItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][2], pDefaultValuesFont, (AfxIsValidAddress(pDefaultValuesFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][3], pDefaultAxesFont, (AfxIsValidAddress(pDefaultAxesFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pValuesFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pAxesFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDefaultTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDefaultItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDefaultValuesFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDefaultAxesFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDFONTSINFO)));
}

BOOL CProfile::GetGRDFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pDefaultTitleFont, LOGFONT *pItemsFont, LOGFONT *pDefaultItemsFont, LOGFONT *pValuesFont, LOGFONT *pDefaultValuesFont, LOGFONT *pAxesFont, LOGFONT *pDefaultAxesFont) CONST
{
	INT  cbInfo;
	DWORD  dwType;
	LOGFONT  sFontsInfo[2][4];

	if ((cbInfo = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo))) >= sizeof(sFontsInfo[0]))
	{
		CopyMemory(pTitleFont, &sFontsInfo[0][0], (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pItemsFont, &sFontsInfo[0][1], (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pValuesFont, &sFontsInfo[0][2], (AfxIsValidAddress(pValuesFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pAxesFont, &sFontsInfo[0][3], (AfxIsValidAddress(pAxesFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDefaultTitleFont, (cbInfo == sizeof(sFontsInfo)) ? &sFontsInfo[1][0] : &sFontsInfo[0][0], (AfxIsValidAddress(pDefaultTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDefaultItemsFont, (cbInfo == sizeof(sFontsInfo)) ? &sFontsInfo[1][1] : &sFontsInfo[0][1], (AfxIsValidAddress(pDefaultItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDefaultValuesFont, (cbInfo == sizeof(sFontsInfo)) ? &sFontsInfo[1][2] : &sFontsInfo[0][2], (AfxIsValidAddress(pDefaultValuesFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDefaultAxesFont, (cbInfo == sizeof(sFontsInfo)) ? &sFontsInfo[1][3] : &sFontsInfo[0][3], (AfxIsValidAddress(pDefaultAxesFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetGRDModeInfo(INT nPage, INT nDisplay, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nMode = nMode;
	sInfo.nSpeed = nSpeed;
	sInfo.tInterval = tInterval.GetTotalSeconds();
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDMODEINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDMODEINFO)));
}

BOOL CProfile::GetGRDModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDMODEINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		nMode = sInfo.nMode;
		nSpeed = sInfo.nSpeed;
		tInterval = sInfo.tInterval;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetGRDPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDPRINTINFO)));
}

BOOL CProfile::GetGRDPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetGRDRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDRETRIEVEFILENAME), pszFileName);
}

BOOL CProfile::GetGRDRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDRETRIEVEFILENAME), szFileName);
}

BOOL CProfile::SetHEXLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXLAYOUTNAME), pszName);
}

BOOL CProfile::GetHEXLayoutName(INT nPage, INT nDisplay, CString &szName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXLAYOUTNAME), szName);
}

BOOL CProfile::SetHEXLayoutInfo(INT nPage, INT nDisplay, CONST SIZE &sizeData, CONST SIZE &sizeSpy, UINT nHorzEnum, UINT nVertEnum, UINT nLineLength, CONST CUIntArray &nColors, BOOL bBadData)
{
	struct {
		UINT  nSize;
		UINT  nColors;
		UINT  nDataWidth;
		UINT  nDataHeight;
		UINT  nSpyWidth;
		UINT  nSpyHeight;
		UINT  nHorzEnum;
		UINT  nVertEnum;
		UINT  nLineLength;
		BOOL  bBadData;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bBadData = bBadData;
	sInfo.nHorzEnum = nHorzEnum;
	sInfo.nVertEnum = nVertEnum;
	sInfo.nLineLength = nLineLength;
	sInfo.nDataWidth = sizeData.cx;
	sInfo.nDataHeight = sizeData.cy;
	sInfo.nSpyWidth = sizeSpy.cx;
	sInfo.nSpyHeight = sizeSpy.cy;
	sInfo.nColors = (UINT)nColors.GetSize();
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + nColors.GetSize()*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nColors.GetData(), nColors.GetSize()*sizeof(UINT));
	return((nHorzEnum != (UINT)-1 && nVertEnum != (UINT)-1 && nLineLength != (UINT)-1 && nColors.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXLAYOUTINFO)));
}

BOOL CProfile::GetHEXLayoutInfo(INT nPage, INT nDisplay, CSize &sizeData, CSize &sizeSpy, UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors, BOOL &bBadData) CONST
{
	struct {
		UINT  nSize;
		UINT  nColors;
		UINT  nDataWidth;
		UINT  nDataHeight;
		UINT  nSpyWidth;
		UINT  nSpyHeight;
		UINT  nHorzEnum;
		UINT  nVertEnum;
		UINT  nLineLength;
		BOOL  bBadData;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + sInfo.nColors*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nColors.SetSize(sInfo.nColors);
					CopyMemory(nColors.GetData(), nInfo.GetData(), nColors.GetSize()*sizeof(UINT));
					bBadData = sInfo.bBadData;
					nHorzEnum = sInfo.nHorzEnum;
					nVertEnum = sInfo.nVertEnum;
					nLineLength = sInfo.nLineLength;
					sizeData.cx = sInfo.nDataWidth;
					sizeData.cy = sInfo.nDataHeight;
					sizeSpy.cx = sInfo.nSpyWidth;
					sizeSpy.cy = sInfo.nSpyHeight;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetHEXLayoutContents(INT nPage, INT nDisplay, CONST CByteArray &nContentsInfo)
{
	return((nContentsInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXLAYOUTCONTENTS), REG_BINARY, nContentsInfo.GetData(), (INT)nContentsInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXLAYOUTCONTENTS)));
}

BOOL CProfile::GetHEXLayoutContents(INT nPage, INT nDisplay, CByteArray &nContentsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXLAYOUTCONTENTS)), nContentsInfo.SetSize(max(nSize, 0)); nSize > 0 && nContentsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXLAYOUTCONTENTS), &dwType, nContentsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetHEXFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont, CONST LOGFONT *pDataFont, CONST LOGFONT *pSpyHeaderFont, CONST LOGFONT *pSpyLocationsFont)
{
	LOGFONT  sFontsInfo[4];

	CopyMemory(&sFontsInfo[0], pTitleFont, (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pDataFont, (AfxIsValidAddress(pDataFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[2], pSpyHeaderFont, (AfxIsValidAddress(pSpyHeaderFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[3], pSpyLocationsFont, (AfxIsValidAddress(pSpyLocationsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDataFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pSpyHeaderFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pSpyLocationsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXFONTSINFO)));
}

BOOL CProfile::GetHEXFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pDataFont, LOGFONT *pSpyHeaderFont, LOGFONT *pSpyLocationsFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[4];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDataFont, &sFontsInfo[1], (AfxIsValidAddress(pDataFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pSpyHeaderFont, &sFontsInfo[2], (AfxIsValidAddress(pSpyHeaderFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pSpyLocationsFont, &sFontsInfo[3], (AfxIsValidAddress(pSpyLocationsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetHEXModeInfo(INT nPage, INT nDisplay, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nMode = nMode;
	sInfo.nSpeed = nSpeed;
	sInfo.tInterval = tInterval.GetTotalSeconds();
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXMODEINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXMODEINFO)));
}

BOOL CProfile::GetHEXModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXMODEINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		nMode = sInfo.nMode;
		nSpeed = sInfo.nSpeed;
		tInterval = sInfo.tInterval;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetHEXPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXPRINTINFO)));
}

BOOL CProfile::GetHEXPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetHEXRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXRETRIEVEFILENAME), pszFileName);
}

BOOL CProfile::GetHEXRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_HEXRETRIEVEFILENAME), szFileName);
}

BOOL CProfile::SetOOLLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLLAYOUTNAME), pszName);
}

BOOL CProfile::GetOOLLayoutName(INT nPage, INT nDisplay, CString &szName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLLAYOUTNAME), szName);
}

BOOL CProfile::SetOOLLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, BOOL bBadData, BOOL bToolTips)
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
		BOOL  bToolTips;
		BOOL  bBadData;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bBadData = bBadData;
	sInfo.bToolTips = bToolTips;
	sInfo.nColumns = (UINT)nColumns.GetSize();
	sInfo.nWidths = (UINT)nWidths.GetSize();
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + (nColumns.GetSize() + nWidths.GetSize())*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nColumns.GetData(), nColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nColumns.GetSize()*sizeof(UINT), nWidths.GetData(), nWidths.GetSize()*sizeof(UINT));
	return((nColumns.GetSize() > 0 && nWidths.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLLAYOUTINFO)));
}

BOOL CProfile::GetOOLLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nColumns, CUIntArray &nWidths, BOOL &bBadData, BOOL &bToolTips) CONST
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
		BOOL  bToolTips;
		BOOL  bBadData;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + (sInfo.nColumns + sInfo.nWidths)*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nColumns.SetSize(sInfo.nColumns);
					CopyMemory(nColumns.GetData(), nInfo.GetData(), nColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nColumns.GetSize()*sizeof(UINT));
					nWidths.SetSize(sInfo.nWidths);
					CopyMemory(nWidths.GetData(), nInfo.GetData(), nWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nWidths.GetSize()*sizeof(UINT));
					bToolTips = sInfo.bToolTips;
					bBadData = sInfo.bBadData;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetOOLFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont)
{
	LOGFONT  sFontsInfo[2];

	CopyMemory(&sFontsInfo[0], pTitleFont, (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pItemsFont, (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLFONTSINFO)));
}

BOOL CProfile::GetOOLFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[2];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pItemsFont, &sFontsInfo[1], (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetOOLFilterInfo(INT nPage, INT nDisplay, CONST CByteArray &nFilterInfo)
{
	return((nFilterInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLFILTERINFO), REG_BINARY, nFilterInfo.GetData(), (INT)nFilterInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLFILTERINFO)));
}

BOOL CProfile::GetOOLFilterInfo(INT nPage, INT nDisplay, CByteArray &nFilterInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLFILTERINFO)), nFilterInfo.SetSize(max(nSize, 0)); nSize > 0 && nFilterInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLFILTERINFO), &dwType, nFilterInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetOOLModeInfo(INT nPage, INT nDisplay, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nMode = nMode;
	sInfo.nSpeed = nSpeed;
	sInfo.tInterval = tInterval.GetTotalSeconds();
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLMODEINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLMODEINFO)));
}

BOOL CProfile::GetOOLModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLMODEINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		nMode = sInfo.nMode;
		nSpeed = sInfo.nSpeed;
		tInterval = sInfo.tInterval;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetOOLPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLPRINTINFO)));
}

BOOL CProfile::GetOOLPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetOOLRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLRETRIEVEFILENAME), pszFileName);
}

BOOL CProfile::GetOOLRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_OOLRETRIEVEFILENAME), szFileName);
}

BOOL CProfile::SetMMDLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDLAYOUTNAME), pszName);
}

BOOL CProfile::GetMMDLayoutName(INT nPage, INT nDisplay, CString &szName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDLAYOUTNAME), szName);
}

BOOL CProfile::SetMMDLayoutInfo(INT nPage, INT nDisplay, CONST SIZE &sizeImage, INT nMarginLeft, INT nMarginTop, INT nMarginRight, INT nMarginBottom, COLORREF nImageBkgnd, CONST SIZE &sizeGrid, COLORREF nImageGrid, BOOL bUseGrid, BOOL bInvalidData, BOOL bBadData, BOOL bToolTips)
{
	struct {
		INT  nSize;
		INT  nImageWidth;
		INT  nImageHeight;
		INT  nImageMargin[4];
		INT  nGridWidth;
		INT  nGridHeight;
		COLORREF  nImageBkgnd;
		COLORREF  nImageGrid;
		BOOL  bUseGrid;
		BOOL  bToolTips;
		BOOL  bBadData;
		BOOL  bInvalidData;
	} sInfo;

	sInfo.nSize = sizeof(sInfo);
	sInfo.nImageWidth = sizeImage.cx;
	sInfo.nImageHeight = sizeImage.cy;
	sInfo.nImageMargin[0] = nMarginLeft;
	sInfo.nImageMargin[1] = nMarginTop;
	sInfo.nImageMargin[2] = nMarginRight;
	sInfo.nImageMargin[3] = nMarginBottom;
	sInfo.nGridWidth = sizeGrid.cx;
	sInfo.nGridHeight = sizeGrid.cy;
	sInfo.nImageBkgnd = nImageBkgnd;
	sInfo.nImageGrid = nImageGrid;
	sInfo.bUseGrid = bUseGrid;
	sInfo.bToolTips = bToolTips;
	sInfo.bBadData = bBadData;
	sInfo.bInvalidData = bInvalidData;
	return((sizeImage.cx >= 0 && sizeImage.cy >= 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDLAYOUTINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDLAYOUTINFO)));
}

BOOL CProfile::GetMMDLayoutInfo(INT nPage, INT nDisplay, CSize &sizeImage, INT &nMarginLeft, INT &nMarginTop, INT &nMarginRight, INT &nMarginBottom, COLORREF &nImageBkgnd, CSize &sizeGrid, COLORREF &nImageGrid, BOOL &bUseGrid, BOOL &bInvalidData, BOOL &bBadData, BOOL &bToolTips) CONST
{
	struct {
		INT  nSize;
		INT  nImageWidth;
		INT  nImageHeight;
		INT  nImageMargin[4];
		INT  nGridWidth;
		INT  nGridHeight;
		COLORREF  nImageBkgnd;
		COLORREF  nImageGrid;
		BOOL  bUseGrid;
		BOOL  bToolTips;
		BOOL  bBadData;
		BOOL  bInvalidData;
	} sInfo;
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDLAYOUTINFO)); nSize == sizeof(sInfo); )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDLAYOUTINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo) && sInfo.nSize == sizeof(sInfo))
		{
			sizeImage.cx = sInfo.nImageWidth;
			sizeImage.cy = sInfo.nImageHeight;
			nMarginLeft = sInfo.nImageMargin[0];
			nMarginTop = sInfo.nImageMargin[1];
			nMarginRight = sInfo.nImageMargin[2];
			nMarginBottom = sInfo.nImageMargin[3];
			sizeGrid.cx = sInfo.nGridWidth;
			sizeGrid.cy = sInfo.nGridHeight;
			nImageBkgnd = sInfo.nImageBkgnd;
			nImageGrid = sInfo.nImageGrid;
			bUseGrid = sInfo.bUseGrid;
			bToolTips = sInfo.bToolTips;
			bBadData = sInfo.bBadData;
			bInvalidData = sInfo.bInvalidData;
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetMMDModeInfo(INT nPage, INT nDisplay, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nMode = nMode;
	sInfo.nSpeed = nSpeed;
	sInfo.tInterval = tInterval.GetTotalSeconds();
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDMODEINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDMODEINFO)));
}

BOOL CProfile::GetMMDModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDMODEINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		nMode = sInfo.nMode;
		nSpeed = sInfo.nSpeed;
		tInterval = sInfo.tInterval;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetMMDPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDPRINTINFO)));
}

BOOL CProfile::GetMMDPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetMMDRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDRETRIEVEFILENAME), pszFileName);
}

BOOL CProfile::GetMMDRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDRETRIEVEFILENAME), szFileName);
}

BOOL CProfile::SetPODLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODLAYOUTNAME), pszName);
}

BOOL CProfile::GetPODLayoutName(INT nPage, INT nDisplay, CString &szName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODLAYOUTNAME), szName);
}

BOOL CProfile::SetPODLayoutInfo(INT nPage, INT nDisplay, CONST SIZE &sizeData, CONST CUIntArray &nDataWidths, CONST SIZE &sizeParameters, CONST CUIntArray &nParametersWidths, CONST SIZE &sizeFunctions, CONST CUIntArray &nFunctionsWidths, BOOL bToolTips)
{
	struct {
		UINT  nSize;
		UINT  nDataSize;
		UINT  nParametersSize;
		UINT  nFunctionsSize;
		UINT  nDataWidth;
		UINT  nDataHeight;
		UINT  nParametersWidth;
		UINT  nParametersHeight;
		UINT  nFunctionsWidth;
		UINT  nFunctionsHeight;
		BOOL  bToolTips;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bToolTips = bToolTips;
	sInfo.nDataWidth = sizeData.cx;
	sInfo.nDataHeight = sizeData.cy;
	sInfo.nParametersWidth = sizeParameters.cx;
	sInfo.nParametersHeight = sizeParameters.cy;
	sInfo.nFunctionsWidth = sizeFunctions.cx;
	sInfo.nFunctionsHeight = sizeFunctions.cy;
	sInfo.nDataSize = (UINT)nDataWidths.GetSize();
	sInfo.nParametersSize = (UINT)nParametersWidths.GetSize();
	sInfo.nFunctionsSize = (UINT)nFunctionsWidths.GetSize();
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + (nDataWidths.GetSize() + nParametersWidths.GetSize() + nFunctionsWidths.GetSize())*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nDataWidths.GetData(), nDataWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nDataWidths.GetSize()*sizeof(UINT), nParametersWidths.GetData(), nParametersWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nDataWidths.GetSize()*sizeof(UINT) + nParametersWidths.GetSize()*sizeof(UINT), nFunctionsWidths.GetData(), nFunctionsWidths.GetSize()*sizeof(UINT));
	return((sizeData.cx != 0 || sizeData.cy != 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODLAYOUTINFO)));
}

BOOL CProfile::GetPODLayoutInfo(INT nPage, INT nDisplay, CSize &sizeData, CUIntArray &nDataWidths, CSize &sizeParameters, CUIntArray &nParametersWidths, CSize &sizeFunctions, CUIntArray &nFunctionsWidths, BOOL &bToolTips) CONST
{
	struct {
		UINT  nSize;
		UINT  nDataSize;
		UINT  nParametersSize;
		UINT  nFunctionsSize;
		UINT  nDataWidth;
		UINT  nDataHeight;
		UINT  nParametersWidth;
		UINT  nParametersHeight;
		UINT  nFunctionsWidth;
		UINT  nFunctionsHeight;
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + (sInfo.nDataSize + sInfo.nParametersSize + sInfo.nFunctionsSize)*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nDataWidths.SetSize(sInfo.nDataSize);
					CopyMemory(nDataWidths.GetData(), nInfo.GetData(), nDataWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nDataWidths.GetSize()*sizeof(UINT));
					nParametersWidths.SetSize(sInfo.nParametersSize);
					CopyMemory(nParametersWidths.GetData(), nInfo.GetData(), nParametersWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nParametersWidths.GetSize()*sizeof(UINT));
					nFunctionsWidths.SetSize(sInfo.nFunctionsSize);
					CopyMemory(nFunctionsWidths.GetData(), nInfo.GetData(), nFunctionsWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nFunctionsWidths.GetSize()*sizeof(UINT));
					sizeData.cx = sInfo.nDataWidth;
					sizeData.cy = sInfo.nDataHeight;
					sizeParameters.cx = sInfo.nParametersWidth;
					sizeParameters.cy = sInfo.nParametersHeight;
					sizeFunctions.cx = sInfo.nFunctionsWidth;
					sizeFunctions.cy = sInfo.nFunctionsHeight;
					bToolTips = sInfo.bToolTips;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetPODFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pDataTitleFont, CONST LOGFONT *pDataItemsFont, CONST LOGFONT *pParametersTitleFont, CONST LOGFONT *pParametersItemsFont, CONST LOGFONT *pFunctionsTitleFont, CONST LOGFONT *pFunctionsItemsFont)
{
	LOGFONT  sFontsInfo[6];

	CopyMemory(&sFontsInfo[0], pDataTitleFont, (AfxIsValidAddress(pDataTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pDataItemsFont, (AfxIsValidAddress(pDataItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[2], pParametersTitleFont, (AfxIsValidAddress(pParametersTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[3], pParametersItemsFont, (AfxIsValidAddress(pParametersItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[4], pFunctionsTitleFont, (AfxIsValidAddress(pFunctionsTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[5], pFunctionsItemsFont, (AfxIsValidAddress(pFunctionsItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pDataTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDataItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pParametersTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pParametersItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pFunctionsTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pFunctionsItemsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODFONTSINFO)));
}

BOOL CProfile::GetPODFontsInfo(INT nPage, INT nDisplay, LOGFONT *pDataTitleFont, LOGFONT *pDataItemsFont, LOGFONT *pParametersTitleFont, LOGFONT *pParametersItemsFont, LOGFONT *pFunctionsTitleFont, LOGFONT *pFunctionsItemsFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[6];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pDataTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pDataTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDataItemsFont, &sFontsInfo[1], (AfxIsValidAddress(pDataItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pParametersTitleFont, &sFontsInfo[2], (AfxIsValidAddress(pParametersTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pParametersItemsFont, &sFontsInfo[3], (AfxIsValidAddress(pParametersItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pFunctionsTitleFont, &sFontsInfo[4], (AfxIsValidAddress(pFunctionsTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pFunctionsItemsFont, &sFontsInfo[5], (AfxIsValidAddress(pFunctionsItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetPODModeInfo(INT nPage, INT nDisplay, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nMode = nMode;
	sInfo.nSpeed = nSpeed;
	sInfo.tInterval = tInterval.GetTotalSeconds();
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODMODEINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODMODEINFO)));
}

BOOL CProfile::GetPODModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODMODEINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		nMode = sInfo.nMode;
		nSpeed = sInfo.nSpeed;
		tInterval = sInfo.tInterval;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetPODFilterInfo(INT nPage, INT nDisplay, UINT nMode, UINT nLimit, UINT nDigits, UINT nStatus, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTimeSpan &tDailyStartTime, CONST CTimeSpan &tDailyStopTime, CONST CTimeKey &tPeriodicalStartTime, CONST CTimeSpan &tPeriodicalInterval, CONST CTimeKey &tPeriodicalStopTime, CONST CUIntArray &nColors)
{
	struct {
		UINT  nSize;
		UINT  nColors;
		UINT  nMode;
		UINT  nLimit;
		UINT  nDigits;
		UINT  nStatus;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
		TIMEKEY  tDailyStartTime;
		TIMEKEY  tDailyStopTime;
		TIMEKEY  tPeriodicalStartTime;
		TIMEKEY  tPeriodicalStopTime;
		TIMEKEY  tPeriodicalInterval;
	} sInfo;
	CByteArray  nInfo;

	sInfo.nMode = nMode;
	sInfo.nLimit = nLimit;
	sInfo.nDigits = nDigits;
	sInfo.nStatus = nStatus;
	sInfo.nColors = (UINT)nColors.GetSize();
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	sInfo.tDailyStartTime = tDailyStartTime.GetTotalSeconds();
	sInfo.tDailyStopTime = tDailyStopTime.GetTotalSeconds();
	sInfo.tPeriodicalStartTime = tPeriodicalStartTime.GetTime();
	sInfo.tPeriodicalStopTime = tPeriodicalStopTime.GetTime();
	sInfo.tPeriodicalInterval = tPeriodicalInterval.GetTotalSeconds();
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + nColors.GetSize()*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nColors.GetData(), nColors.GetSize()*sizeof(UINT));
	return((nMode != (UINT)-1 && nLimit != (UINT)-1 && nDigits != (UINT)-1 && nStatus != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODFILTERINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODFILTERINFO)));
}

BOOL CProfile::GetPODFilterInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nLimit, UINT &nDigits, UINT &nStatus, CTimeKey &tStartTime, CTimeKey &tStopTime, CTimeSpan &tDailyStartTime, CTimeSpan &tDailyStopTime, CTimeKey &tPeriodicalStartTime, CTimeSpan &tPeriodicalInterval, CTimeKey &tPeriodicalStopTime, CUIntArray &nColors) CONST
{
	struct {
		UINT  nSize;
		UINT  nColors;
		UINT  nMode;
		UINT  nLimit;
		UINT  nDigits;
		UINT  nStatus;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
		TIMEKEY  tDailyStartTime;
		TIMEKEY  tDailyStopTime;
		TIMEKEY  tPeriodicalStartTime;
		TIMEKEY  tPeriodicalStopTime;
		TIMEKEY  tPeriodicalInterval;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODFILTERINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODFILTERINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + sInfo.nColors*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nColors.SetSize(sInfo.nColors);
					CopyMemory(nColors.GetData(), nInfo.GetData(), nColors.GetSize()*sizeof(UINT));
					nMode = sInfo.nMode;
					nLimit = sInfo.nLimit;
					nDigits = sInfo.nDigits;
					nStatus = sInfo.nStatus;
					tStartTime = sInfo.tStartTime;
					tStopTime = sInfo.tStopTime;
					tDailyStartTime = sInfo.tDailyStartTime;
					tDailyStopTime = sInfo.tDailyStopTime;
					tPeriodicalStartTime = sInfo.tPeriodicalStartTime;
					tPeriodicalStopTime = sInfo.tPeriodicalStopTime;
					tPeriodicalInterval = sInfo.tPeriodicalInterval;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetPODPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODPRINTINFO)));
}

BOOL CProfile::GetPODPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetPODRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODRETRIEVEFILENAME), pszFileName);
}

BOOL CProfile::GetPODRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODRETRIEVEFILENAME), szFileName);
}

BOOL CProfile::SetTPEPConnectionInfo(INT nPage, INT nDisplay, LPCTSTR pszComputer, CONST CByteArray &nConnectionInfo, BOOL bConnection)
{
	CByteArray  nInfo;

	nInfo.Add(bConnection);
	nInfo.Append(nConnectionInfo);
	return((AfxIsValidString(pszComputer) && lstrlen(pszComputer) > 0 && nConnectionInfo.GetSize() > 0) ? (SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPCONNECTIONSERVER), pszComputer) && SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPCONNECTIONINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize())) : (SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPCONNECTIONSERVER)) && SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPCONNECTIONINFO))));
}

BOOL CProfile::GetTPEPConnectionInfo(INT nPage, INT nDisplay, CString &szComputer, CByteArray &nConnectionInfo, BOOL &bConnection) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPCONNECTIONINFO)), nConnectionInfo.SetSize(max(nSize, 0)); nSize > 0 && nConnectionInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPCONNECTIONSERVER), szComputer) && GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPCONNECTIONINFO), &dwType, nConnectionInfo.GetData(), nSize) == nSize  &&  nSize > 1)
		{
			bConnection = nConnectionInfo.GetAt(0);
			nConnectionInfo.RemoveAt(0);
			return TRUE;
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTPEPLayoutInfo(INT nPage, INT nDisplay, UINT nType, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, BOOL bToolTips)
{
	struct {
		UINT  nSize;
		UINT  nType;
		UINT  nColumns;
		UINT  nWidths;
		BOOL  bToolTips;
	} sInfo;
	CByteArray  nInfo;

	sInfo.nType = nType;
	sInfo.bToolTips = bToolTips;
	sInfo.nColumns = (UINT)nColumns.GetSize();
	sInfo.nWidths = (UINT)nWidths.GetSize();
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + (nColumns.GetSize() + nWidths.GetSize())*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nColumns.GetData(), nColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nColumns.GetSize()*sizeof(UINT), nWidths.GetData(), nWidths.GetSize()*sizeof(UINT));
	return((nColumns.GetSize() > 0 && nWidths.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPLAYOUTINFO)));
}

BOOL CProfile::GetTPEPLayoutInfo(INT nPage, INT nDisplay, UINT &nType, CUIntArray &nColumns, CUIntArray &nWidths, BOOL &bToolTips) CONST
{
	struct {
		UINT  nSize;
		UINT  nType;
		UINT  nColumns;
		UINT  nWidths;
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + (sInfo.nColumns + sInfo.nWidths)*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nColumns.SetSize(sInfo.nColumns);
					CopyMemory(nColumns.GetData(), nInfo.GetData(), nColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColumns*sizeof(UINT));
					nWidths.SetSize(sInfo.nWidths);
					CopyMemory(nWidths.GetData(), nInfo.GetData(), nWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nWidths*sizeof(UINT));
					bToolTips = sInfo.bToolTips;
					nType = sInfo.nType;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTPEPFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont, CONST LOGFONT *pMessagesFont)
{
	LOGFONT  sFontsInfo[2];

	CopyMemory(&sFontsInfo[0], pTitleFont, (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pMessagesFont, (AfxIsValidAddress(pMessagesFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pMessagesFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPFONTSINFO)));
}

BOOL CProfile::GetTPEPFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pMessagesFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[2];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pMessagesFont, &sFontsInfo[1], (AfxIsValidAddress(pMessagesFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTPEPFilterInfo(INT nPage, INT nDisplay, UINT nMode, UINT nLimit, UINT nDigits, UINT nStatus, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTimeSpan &tDailyStartTime, CONST CTimeSpan &tDailyStopTime, CONST CTimeKey &tPeriodicalStartTime, CONST CTimeSpan &tPeriodicalInterval, CONST CTimeKey &tPeriodicalStopTime, COLORREF nColor, CONST CUIntArray &nOOLColors)
{
	struct {
		UINT  nSize;
		UINT  nMode;
		UINT  nLimit;
		UINT  nDigits;
		UINT  nStatus;
		UINT  nOOLColors;
		COLORREF  nColor;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
		TIMEKEY  tDailyStartTime;
		TIMEKEY  tDailyStopTime;
		TIMEKEY  tPeriodicalStartTime;
		TIMEKEY  tPeriodicalStopTime;
		TIMEKEY  tPeriodicalInterval;
	} sInfo;
	CByteArray  nInfo;

	sInfo.nMode = nMode;
	sInfo.nLimit = nLimit;
	sInfo.nColor = nColor;
	sInfo.nDigits = nDigits;
	sInfo.nStatus = nStatus;
	sInfo.nOOLColors = (UINT)nOOLColors.GetSize();
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	sInfo.tDailyStartTime = tDailyStartTime.GetTotalSeconds();
	sInfo.tDailyStopTime = tDailyStopTime.GetTotalSeconds();
	sInfo.tPeriodicalStartTime = tPeriodicalStartTime.GetTime();
	sInfo.tPeriodicalStopTime = tPeriodicalStopTime.GetTime();
	sInfo.tPeriodicalInterval = tPeriodicalInterval.GetTotalSeconds();
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + nOOLColors.GetSize()*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nOOLColors.GetData(), nOOLColors.GetSize()*sizeof(UINT));
	return((nMode != (UINT)-1 && nLimit != (UINT)-1 && nDigits != (UINT)-1 && nStatus != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPFILTERINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPFILTERINFO)));
}

BOOL CProfile::GetTPEPFilterInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nLimit, UINT &nDigits, UINT &nStatus, CTimeKey &tStartTime, CTimeKey &tStopTime, CTimeSpan &tDailyStartTime, CTimeSpan &tDailyStopTime, CTimeKey &tPeriodicalStartTime, CTimeSpan &tPeriodicalInterval, CTimeKey &tPeriodicalStopTime, COLORREF &nColor, CUIntArray &nOOLColors) CONST
{
	struct {
		UINT  nSize;
		UINT  nMode;
		UINT  nLimit;
		UINT  nDigits;
		UINT  nStatus;
		UINT  nOOLColors;
		COLORREF  nColor;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
		TIMEKEY  tDailyStartTime;
		TIMEKEY  tDailyStopTime;
		TIMEKEY  tPeriodicalStartTime;
		TIMEKEY  tPeriodicalStopTime;
		TIMEKEY  tPeriodicalInterval;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPFILTERINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPFILTERINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + sInfo.nOOLColors*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nOOLColors.SetSize(sInfo.nOOLColors);
					CopyMemory(nOOLColors.GetData(), nInfo.GetData(), nOOLColors.GetSize()*sizeof(UINT));
					nMode = sInfo.nMode;
					nLimit = sInfo.nLimit;
					nColor = sInfo.nColor;
					nDigits = sInfo.nDigits;
					nStatus = sInfo.nStatus;
					tStartTime = sInfo.tStartTime;
					tStopTime = sInfo.tStopTime;
					tDailyStartTime = sInfo.tDailyStartTime;
					tDailyStopTime = sInfo.tDailyStopTime;
					tPeriodicalStartTime = sInfo.tPeriodicalStartTime;
					tPeriodicalStopTime = sInfo.tPeriodicalStopTime;
					tPeriodicalInterval = sInfo.tPeriodicalInterval;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTPEPAlertsInfo(INT nPage, INT nDisplay, CONST CByteArray &nAlertsInfo)
{
	return((nAlertsInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPALERTSINFO), REG_BINARY, nAlertsInfo.GetData(), (INT)nAlertsInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPALERTSINFO)));
}

BOOL CProfile::GetTPEPAlertsInfo(INT nPage, INT nDisplay, CByteArray &nAlertsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPALERTSINFO)), nAlertsInfo.SetSize(max(nSize, 0)); nSize > 0 && nAlertsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPALERTSINFO), &dwType, nAlertsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTPEPPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPPRINTINFO)));
}

BOOL CProfile::GetTPEPPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TPEPPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetEventBoxDefaultLayoutInfo(UINT nColumns)
{
	return((nColumns > 0) ? SetUserInfo(QueryEventBoxDefaultSubKey(), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXDEFAULTTITLEITEMSINFO), nColumns) : SetUserInfo(QueryEventBoxDefaultSubKey(), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXDEFAULTTITLEITEMSINFO)));
}

BOOL CProfile::GetEventBoxDefaultLayoutInfo(UINT &nColumns) CONST
{
	DWORD  dwColumns;

	if (GetUserInfo(QueryEventBoxDefaultSubKey(), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXDEFAULTTITLEITEMSINFO), dwColumns))
	{
		nColumns = (UINT)dwColumns;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetEventBoxDefaultFontsInfo(CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont)
{
	LOGFONT  sFontsInfo[2];

	CopyMemory(&sFontsInfo[0], pTitleFont, (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pItemsFont, (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryEventBoxDefaultSubKey(), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXDEFAULTFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryEventBoxDefaultSubKey(), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXDEFAULTFONTSINFO)));
}

BOOL CProfile::GetEventBoxDefaultFontsInfo(LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[2];

	if (GetUserInfo(QueryEventBoxDefaultSubKey(), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXDEFAULTFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pItemsFont, &sFontsInfo[1], (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetEventBoxLayoutInfo(INT nPage, INT nDisplay, UINT nColumns, CONST CUIntArray &nWidths)
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
	} sInfo;
	CByteArray  nInfo;

	sInfo.nColumns = nColumns;
	sInfo.nWidths = (UINT)nWidths.GetSize();
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + nWidths.GetSize()*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nWidths.GetData(), nWidths.GetSize()*sizeof(UINT));
	return((nColumns != 0 && nWidths.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXTITLEITEMSINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXTITLEITEMSINFO)));
}

BOOL CProfile::GetEventBoxLayoutInfo(INT nPage, INT nDisplay, UINT &nColumns, CUIntArray &nWidths) CONST
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXTITLEITEMSINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXTITLEITEMSINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + sInfo.nWidths*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nWidths.SetSize(sInfo.nWidths);
					CopyMemory(nWidths.GetData(), nInfo.GetData(), nWidths.GetSize()*sizeof(UINT));
					nColumns = sInfo.nColumns;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetEventBoxFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont)
{
	LOGFONT  sFontsInfo[2];

	CopyMemory(&sFontsInfo[0], pTitleFont, (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pItemsFont, (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXFONTSINFO)));
}

BOOL CProfile::GetEventBoxFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[2];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pItemsFont, &sFontsInfo[1], (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetEventBoxLogName(INT nPage, INT nDisplay, LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal)
{
	CStringArray  szLogName;

	szLogName.Add((AfxIsValidString(pszComputerName)) ? pszComputerName : EMPTYSTRING);
	szLogName.Add((AfxIsValidString(pszSpacecraftName)) ? pszSpacecraftName : EMPTYSTRING);
	szLogName.Add((AfxIsValidString(pszUserName)) ? pszUserName : EMPTYSTRING);
	szLogName.Add((szLogName.GetSize() == EVENT_CATEGORIES  &&  !bLocal) ? STRING(IDS_EVENTCATEGORY_GLOBALSPACECRAFT) : STRING(IDS_EVENTCATEGORY_SPACECRAFT));
	return((AfxIsValidString(pszComputerName) && AfxIsValidString(pszSpacecraftName) && AfxIsValidString(pszUserName)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXLOGNAME), szLogName) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXLOGNAME)));
}

BOOL CProfile::GetEventBoxLogName(INT nPage, INT nDisplay, CString &szComputerName, CString &szSpacecraftName, CString &szUserName, BOOL &bLocal) CONST
{
	INT  nIndex;
	CStringArray  szLogName;

	for (nIndex = 0; GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXLOGNAME), szLogName) == EVENT_CATEGORIES + 1; )
	{
		for (szComputerName = szLogName.GetAt(nIndex), szSpacecraftName = szLogName.GetAt(++nIndex), szUserName = szLogName.GetAt(++nIndex), bLocal = FALSE; szLogName.GetAt(++nIndex) != STRING(IDS_EVENTCATEGORY_GLOBALSPACECRAFT); )
		{
			bLocal = TRUE;
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetEventBoxModeInfo(INT nPage, INT nDisplay, UINT nMode, UINT nLimit, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	struct {
		UINT  nMode;
		UINT  nLimit;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nMode = nMode;
	sInfo.nLimit = nLimit;
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXMODEINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXMODEINFO)));
}

BOOL CProfile::GetEventBoxModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nLimit, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	struct {
		UINT  nMode;
		UINT  nLimit;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXMODEINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		nMode = sInfo.nMode;
		nLimit = sInfo.nLimit;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetEventBoxFilterInfo(INT nPage, INT nDisplay, UINT nMode, UINT nLimit, UINT nAutoCount, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CStringArray &szTypes, CONST CStringArray &szSubtypes, CONST CUIntArray &nColors)
{
	struct {
		UINT  nSize;
		UINT  nMode;
		UINT  nLimit;
		UINT  nAutoCount;
		UINT  nColors;
		UINT  cbTypes;
		UINT  cbSubtypes;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	INT  nType;
	INT  nTypes;
	INT  nSubtype;
	INT  nSubtypes;
	CByteArray  nInfo;
	CByteArray  nTypesInfo;
	CByteArray  nSubtypesInfo;

	sInfo.nMode = nMode;
	sInfo.nLimit = nLimit;
	sInfo.nAutoCount = nAutoCount;
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	sInfo.nColors = (UINT)nColors.GetSize();
	for (nType = 0, nTypes = (INT)szTypes.GetSize(), sInfo.cbTypes = 0; nType < nTypes; nType++)
	{
		nTypesInfo.SetSize(sInfo.cbTypes + (szTypes.GetAt(nType).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nTypesInfo.GetData() + sInfo.cbTypes, (LPCTSTR)szTypes.GetAt(nType), nTypesInfo.GetSize() - sInfo.cbTypes);
		sInfo.cbTypes = (UINT)nTypesInfo.GetSize();
	}
	for (nSubtype = 0, nSubtypes = (INT)szSubtypes.GetSize(), sInfo.cbSubtypes = 0; nSubtype < nSubtypes; nSubtype++)
	{
		nSubtypesInfo.SetSize(sInfo.cbSubtypes + (szSubtypes.GetAt(nSubtype).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nSubtypesInfo.GetData() + sInfo.cbSubtypes, (LPCTSTR)szSubtypes.GetAt(nSubtype), nSubtypesInfo.GetSize() - sInfo.cbSubtypes);
		sInfo.cbSubtypes = (UINT)nSubtypesInfo.GetSize();
	}
	sInfo.nSize = sizeof(sInfo);
	sInfo.nSize += sInfo.cbTypes;
	sInfo.nSize += sInfo.cbSubtypes;
	sInfo.nSize += sInfo.nColors*sizeof(UINT);
	nInfo.SetSize(sInfo.nSize);
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nTypesInfo.GetData(), nTypesInfo.GetSize());
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nTypesInfo.GetSize(), nSubtypesInfo.GetData(), nSubtypesInfo.GetSize());
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nTypesInfo.GetSize() + nSubtypesInfo.GetSize(), nColors.GetData(), nColors.GetSize()*sizeof(UINT));
	return((nMode != (UINT)-1 && nLimit != (UINT)-1 && nAutoCount != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXFILTERINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXFILTERINFO)));
}

BOOL CProfile::GetEventBoxFilterInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nLimit, UINT &nAutoCount, CTimeKey &tStartTime, CTimeKey &tStopTime, CStringArray &szTypes, CStringArray &szSubtypes, CUIntArray &nColors) CONST
{
	struct {
		UINT  nSize;
		UINT  nMode;
		UINT  nLimit;
		UINT  nAutoCount;
		UINT  nColors;
		UINT  cbTypes;
		UINT  cbSubtypes;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;
	CByteArray  nTypesInfo;
	CByteArray  nSubtypesInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXFILTERINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXFILTERINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize  &&  nSize > sizeof(sInfo))
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), sizeof(sInfo)); sInfo.nSize == sizeof(sInfo) + sInfo.cbTypes + sInfo.cbSubtypes + sInfo.nColors*sizeof(UINT) && sInfo.nSize == nInfo.GetSize(); )
			{
				nInfo.RemoveAt(0, sizeof(sInfo));
				nTypesInfo.Copy(nInfo);
				nTypesInfo.SetSize(sInfo.cbTypes);
				nInfo.RemoveAt(0, sInfo.cbTypes);
				nSubtypesInfo.Copy(nInfo);
				nSubtypesInfo.SetSize(sInfo.cbSubtypes);
				nInfo.RemoveAt(0, sInfo.cbSubtypes);
				nColors.SetSize(sInfo.nColors);
				nMode = sInfo.nMode;
				nLimit = sInfo.nLimit;
				nAutoCount = sInfo.nAutoCount;
				tStartTime = sInfo.tStartTime;
				tStopTime = sInfo.tStopTime;
				for (szTypes.RemoveAll(); nTypesInfo.GetSize() > 0; )
				{
					szTypes.Add((LPCTSTR)nTypesInfo.GetData());
					nTypesInfo.RemoveAt(0, (szTypes.GetAt(szTypes.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR));
				}
				for (szSubtypes.RemoveAll(); nSubtypesInfo.GetSize() > 0; )
				{
					szSubtypes.Add((LPCTSTR)nSubtypesInfo.GetData());
					nSubtypesInfo.RemoveAt(0, (szSubtypes.GetAt(szSubtypes.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR));
				}
				CopyMemory(nColors.GetData(), nInfo.GetData(), nColors.GetSize()*sizeof(UINT));
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetEventBoxPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXPRINTINFO)));
}

BOOL CProfile::GetEventBoxPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetEventBoxScheduleInfo(INT nPage, INT nDisplay, CONST CByteArray &nScheduleInfo)
{
	return((nScheduleInfo.GetSize() > 0) ? SetUserInfo(QueryEventBoxDefaultSubKey(), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXSCHEDULEINFO), REG_BINARY, nScheduleInfo.GetData(), (INT)nScheduleInfo.GetSize()) : SetUserInfo(QueryEventBoxDefaultSubKey(), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXSCHEDULEINFO)));
}

BOOL CProfile::GetEventBoxScheduleInfo(INT nPage, INT nDisplay, CByteArray &nScheduleInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryEventBoxDefaultSubKey(), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXSCHEDULEINFO)), nScheduleInfo.SetSize(max(nSize, 0)); nSize > 0 && nScheduleInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryEventBoxDefaultSubKey(), STRING(IDS_REG_SUBKEYVALUE_EVENTBOXSCHEDULEINFO), &dwType, nScheduleInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCManualStackLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, COLORREF nGridBackgroundColor, BOOL bToolTips)
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
		COLORREF  nColor;
		BOOL  bToolTips;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bToolTips = bToolTips;
	sInfo.nColumns = (UINT)nColumns.GetSize();
	sInfo.nWidths = (UINT)nWidths.GetSize();
	sInfo.nColor = nGridBackgroundColor;
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + (nColumns.GetSize() + nWidths.GetSize())*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nColumns.GetData(), nColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nColumns.GetSize()*sizeof(UINT), nWidths.GetData(), nWidths.GetSize()*sizeof(UINT));
	return((nColumns.GetSize() > 0 && nWidths.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKLAYOUTINFO)));
}

BOOL CProfile::GetTCManualStackLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nColumns, CUIntArray &nWidths, COLORREF &nGridBackgroundColor, BOOL &bToolTips) CONST
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
		COLORREF  nColor;
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + (sInfo.nColumns + sInfo.nWidths)*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nColumns.SetSize(sInfo.nColumns);
					CopyMemory(nColumns.GetData(), nInfo.GetData(), nColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColumns*sizeof(UINT));
					nWidths.SetSize(sInfo.nWidths);
					CopyMemory(nWidths.GetData(), nInfo.GetData(), nWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nWidths*sizeof(UINT));
					nGridBackgroundColor = sInfo.nColor;
					bToolTips = sInfo.bToolTips;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCManualStackFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont)
{
	LOGFONT  sFontsInfo[2];

	CopyMemory(&sFontsInfo[0], pTitleFont, (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pItemsFont, (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKFONTSINFO)));
}

BOOL CProfile::GetTCManualStackFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[2];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pItemsFont, &sFontsInfo[1], (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCManualStackOperationsInfo(INT nPage, INT nDisplay, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingChecks, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, INT nUpdateCheckCount, INT nArgumentCount, BOOL bAllArguments, UINT nMiscellaneousOptions, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CTimeSpan &tDispatchTimeWindow)
{
	struct {
		INT  cbSize;
		INT  nArgumentCount;
		INT  nUpdateCheckCount;
		UINT  nTelecommandingMode;
		UINT  nTelecommandingState;
		UINT  nTelecommandingChecks;
		UINT  nMiscellaneousOptions;
		TIMEKEY  tDefaultReleaseTimeWindow;
		TIMEKEY  tDispatchTimeWindow;
		BOOL  bTelecommandingAutoRejectionMode;
		BOOL  bTelecommandingReleaseWaitMode;
		BOOL  bTelecommandingInterlockMode;
		BOOL  bAllArguments;
	} sInfo;

	sInfo.cbSize = sizeof(sInfo);
	sInfo.bAllArguments = bAllArguments;
	sInfo.nArgumentCount = nArgumentCount;
	sInfo.nUpdateCheckCount = nUpdateCheckCount;
	sInfo.nTelecommandingMode = nTelecommandingMode;
	sInfo.nTelecommandingState = nTelecommandingState;
	sInfo.nTelecommandingChecks = nTelecommandingChecks;
	sInfo.nMiscellaneousOptions = nMiscellaneousOptions;
	sInfo.bTelecommandingInterlockMode = bTelecommandingInterlockMode;
	sInfo.bTelecommandingReleaseWaitMode = bTelecommandingReleaseWaitMode;
	sInfo.bTelecommandingAutoRejectionMode = bTelecommandingAutoRejectionMode;
	sInfo.tDefaultReleaseTimeWindow = tDefaultReleaseTimeWindow.GetTotalSeconds();
	sInfo.tDispatchTimeWindow = tDispatchTimeWindow.GetTotalSeconds();
	return((nTelecommandingMode != (UINT)-1 && nTelecommandingState != (UINT)-1 && nTelecommandingChecks != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKOPERATIONSINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKOPERATIONSINFO)));
}

BOOL CProfile::GetTCManualStackOperationsInfo(INT nPage, INT nDisplay, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingChecks, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, INT &nUpdateCheckCount, INT &nArgumentCount, BOOL &bAllArguments, UINT &nMiscellaneousOptions, CTimeSpan &tDefaultReleaseTimeWindow, CTimeSpan &tDispatchTimeWindow) CONST
{
	struct {
		INT  cbSize;
		INT  nArgumentCount;
		INT  nUpdateCheckCount;
		UINT  nTelecommandingMode;
		UINT  nTelecommandingState;
		UINT  nTelecommandingChecks;
		UINT  nMiscellaneousOptions;
		TIMEKEY  tDefaultReleaseTimeWindow;
		TIMEKEY  tDispatchTimeWindow;
		BOOL  bTelecommandingAutoRejectionMode;
		BOOL  bTelecommandingReleaseWaitMode;
		BOOL  bTelecommandingInterlockMode;
		BOOL  bAllArguments;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKOPERATIONSINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKOPERATIONSINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize == (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) / sizeof(BYTE))
				{
					nTelecommandingMode = sInfo.nTelecommandingMode;
					nTelecommandingState = sInfo.nTelecommandingState;
					nTelecommandingChecks = sInfo.nTelecommandingChecks;
					nMiscellaneousOptions = sInfo.nMiscellaneousOptions;
					bTelecommandingInterlockMode = sInfo.bTelecommandingInterlockMode;
					bTelecommandingReleaseWaitMode = sInfo.bTelecommandingReleaseWaitMode;
					bTelecommandingAutoRejectionMode = sInfo.bTelecommandingAutoRejectionMode;
					tDefaultReleaseTimeWindow = sInfo.tDefaultReleaseTimeWindow;
					tDispatchTimeWindow = sInfo.tDispatchTimeWindow;
					nUpdateCheckCount = sInfo.nUpdateCheckCount;
					nArgumentCount = sInfo.nArgumentCount;
					bAllArguments = sInfo.bAllArguments;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCManualStackContentsInfo(INT nPage, INT nDisplay, CONST CByteArray &nContentsInfo)
{
	return((nContentsInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKCONTENTSINFO), REG_BINARY, nContentsInfo.GetData(), (INT)nContentsInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKCONTENTSINFO)));
}

BOOL CProfile::GetTCManualStackContentsInfo(INT nPage, INT nDisplay, CByteArray &nContentsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKCONTENTSINFO)), nContentsInfo.SetSize(max(nSize, 0)); nSize > 0 && nContentsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKCONTENTSINFO), &dwType, nContentsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCManualStackSearchInfo(INT nPage, INT nDisplay, CONST CByteArray &nGroupsInfo, CONST CByteArray &nFiltersInfo)
{
	struct {
		INT  cbSize;
		INT  cbGroups;
		INT  cbFilters;
	} sInfo;
	CByteArray  nInfo;

	sInfo.cbGroups = (INT)(nGroupsInfo.GetSize()*sizeof(BYTE));
	sInfo.cbFilters = (INT)(nFiltersInfo.GetSize()*sizeof(BYTE));
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbGroups + sInfo.cbFilters));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nGroupsInfo.GetData(), sInfo.cbGroups);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbGroups, nFiltersInfo.GetData(), sInfo.cbFilters);
	return((nGroupsInfo.GetSize() > 0 || nFiltersInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKSEARCHINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKSEARCHINFO)));
}

BOOL CProfile::GetTCManualStackSearchInfo(INT nPage, INT nDisplay, CByteArray &nGroupsInfo, CByteArray &nFiltersInfo) CONST
{
	struct {
		INT  cbSize;
		INT  cbGroups;
		INT  cbFilters;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKSEARCHINFO)), nInfo.SetSize(max(nSize, 0)), nGroupsInfo.RemoveAll(), nFiltersInfo.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKSEARCHINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbGroups + sInfo.cbFilters  &&  sInfo.cbSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nGroupsInfo.SetSize(sInfo.cbGroups);
					CopyMemory(nGroupsInfo.GetData(), nInfo.GetData(), sInfo.cbGroups);
					nInfo.RemoveAt(0, sInfo.cbGroups);
					nFiltersInfo.SetSize(sInfo.cbFilters);
					CopyMemory(nFiltersInfo.GetData(), nInfo.GetData(), sInfo.cbFilters);
					nInfo.RemoveAt(0, sInfo.cbFilters);
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCManualStackTemplatesInfo(INT nPage, INT nDisplay, CONST CByteArray &nItemTemplatesInfo, CONST CByteArray &nComposedItemTemplatesInfo)
{
	struct {
		INT  cbSize;
		INT  cbTemplates[2];
	} sInfo;
	CByteArray  nInfo;

	sInfo.cbTemplates[0] = (INT)(nItemTemplatesInfo.GetSize()*sizeof(BYTE));
	sInfo.cbTemplates[1] = (INT)(nComposedItemTemplatesInfo.GetSize()*sizeof(BYTE));
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbTemplates[0] + sInfo.cbTemplates[1]));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nItemTemplatesInfo.GetData(), sInfo.cbTemplates[0]);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTemplates[0], nComposedItemTemplatesInfo.GetData(), sInfo.cbTemplates[1]);
	return((nItemTemplatesInfo.GetSize() > 0 || nComposedItemTemplatesInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKTEMPLATESINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKTEMPLATESINFO)));
}

BOOL CProfile::GetTCManualStackTemplatesInfo(INT nPage, INT nDisplay, CByteArray &nItemTemplatesInfo, CByteArray &nComposedItemTemplatesInfo) CONST
{
	struct {
		INT  cbSize;
		INT  cbTemplates[2];
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKTEMPLATESINFO)), nInfo.SetSize(max(nSize, 0)), nItemTemplatesInfo.RemoveAll(), nComposedItemTemplatesInfo.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKTEMPLATESINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbTemplates[0] + sInfo.cbTemplates[1] && sInfo.cbSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nItemTemplatesInfo.SetSize(sInfo.cbTemplates[0]);
					CopyMemory(nItemTemplatesInfo.GetData(), nInfo.GetData(), sInfo.cbTemplates[0]);
					nInfo.RemoveAt(0, sInfo.cbTemplates[0]);
					nComposedItemTemplatesInfo.SetSize(sInfo.cbTemplates[1]);
					CopyMemory(nComposedItemTemplatesInfo.GetData(), nInfo.GetData(), sInfo.cbTemplates[1]);
					nInfo.RemoveAt(0, sInfo.cbTemplates[1]);
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCManualStackLoggingInfo(INT nPage, INT nDisplay, UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent)
{
	struct {
		INT  cbSize;
		INT  cbArchivalFileName;
		INT  cbRetrievalFileName;
		UINT  nArchivalPolicy;
		UINT  nRetrievalReloadCount;
		DWORDLONG  dwArchivalRetention;
		TIMEKEY  tArchivalRetention;
		BOOL  bShowAsEvent;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bShowAsEvent = bShowAsEvent;
	sInfo.nArchivalPolicy = nArchivalPolicy;
	sInfo.dwArchivalRetention = dwArchivalRetention;
	sInfo.nRetrievalReloadCount = nRetrievalReloadCount;
	sInfo.tArchivalRetention = tArchivalRetention.GetTotalSeconds();
	sInfo.cbArchivalFileName = (AfxIsValidString(pszArchivalFileName)) ? ((lstrlen(pszArchivalFileName) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbRetrievalFileName = (AfxIsValidString(pszRetrievalFileName)) ? ((lstrlen(pszRetrievalFileName) + 1)*sizeof(TCHAR)) : 0;
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbArchivalFileName + sInfo.cbRetrievalFileName));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), pszArchivalFileName, sInfo.cbArchivalFileName);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbArchivalFileName, pszRetrievalFileName, sInfo.cbRetrievalFileName);
	return((AfxIsValidString(pszArchivalFileName) && AfxIsValidString(pszRetrievalFileName)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKLOGGINGINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKLOGGINGINFO)));
}

BOOL CProfile::GetTCManualStackLoggingInfo(INT nPage, INT nDisplay, UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST
{
	struct {
		INT  cbSize;
		INT  cbArchivalFileName;
		INT  cbRetrievalFileName;
		UINT  nArchivalPolicy;
		UINT  nRetrievalReloadCount;
		DWORDLONG  dwArchivalRetention;
		TIMEKEY  tArchivalRetention;
		BOOL  bShowAsEvent;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKLOGGINGINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKLOGGINGINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbArchivalFileName + sInfo.cbRetrievalFileName)
				{
					CopyMemory(szArchivalFileName.GetBufferSetLength(STRINGCHARS(sInfo.cbArchivalFileName)), nInfo.GetData() + sizeof(sInfo), STRINGBYTES(sInfo.cbArchivalFileName));
					CopyMemory(szRetrievalFileName.GetBufferSetLength(STRINGCHARS(sInfo.cbRetrievalFileName)), nInfo.GetData() + sizeof(sInfo) + sInfo.cbArchivalFileName, STRINGBYTES(sInfo.cbRetrievalFileName));
					nRetrievalReloadCount = sInfo.nRetrievalReloadCount;
					dwArchivalRetention = sInfo.dwArchivalRetention;
					tArchivalRetention = sInfo.tArchivalRetention;
					nArchivalPolicy = sInfo.nArchivalPolicy;
					bShowAsEvent = sInfo.bShowAsEvent;
					szArchivalFileName.ReleaseBuffer();
					szRetrievalFileName.ReleaseBuffer();
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCManualStackAlertInfo(INT nPage, INT nDisplay, CONST CUIntArray &nTypes, CONST CStringArray &szAuditions, CONST CStringArray &szNotifications, CONST CDWordArray &nAcknowledgeColors, CONST CByteArray &bAcknowledgments)
{
	struct {
		INT  cbSize;
		INT  cbTypes;
		INT  cbAuditions;
		INT  cbNotifications;
		INT  cbAcknowledgeColors;
		INT  cbAcknowledgments;
	} sInfo;
	INT  nAudition;
	INT  nAuditions;
	INT  nNotification;
	INT  nNotifications;
	CByteArray  nInfo;
	CByteArray  nInfoData[2];

	sInfo.cbTypes = (INT)(nTypes.GetSize()*sizeof(UINT));
	sInfo.cbAcknowledgeColors = (INT)(nAcknowledgeColors.GetSize()*sizeof(DWORD));
	sInfo.cbAcknowledgments = (INT)(bAcknowledgments.GetSize()*sizeof(BYTE));
	for (nAudition = 0, nAuditions = (INT)szAuditions.GetSize(), sInfo.cbAuditions = 0; nAudition < nAuditions; nAudition++)
	{
		nInfoData[0].SetSize(sInfo.cbAuditions + (szAuditions.GetAt(nAudition).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nInfoData[0].GetData() + sInfo.cbAuditions, (LPCTSTR)szAuditions.GetAt(nAudition), (szAuditions.GetAt(nAudition).GetLength() + 1)*sizeof(TCHAR));
		sInfo.cbAuditions += (szAuditions.GetAt(nAudition).GetLength() + 1)*sizeof(TCHAR);
	}
	for (nNotification = 0, nNotifications = (INT)szNotifications.GetSize(), sInfo.cbNotifications = 0; nNotification < nNotifications; nNotification++)
	{
		nInfoData[1].SetSize(sInfo.cbNotifications + (szNotifications.GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nInfoData[1].GetData() + sInfo.cbNotifications, (LPCTSTR)szNotifications.GetAt(nNotification), (szNotifications.GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR));
		sInfo.cbNotifications += (szNotifications.GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR);
	}
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors + sInfo.cbAcknowledgments));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nTypes.GetData(), sInfo.cbTypes);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes, nInfoData[0].GetData(), sInfo.cbAuditions);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions, nInfoData[1].GetData(), sInfo.cbNotifications);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications, nAcknowledgeColors.GetData(), sInfo.cbAcknowledgeColors);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors, bAcknowledgments.GetData(), sInfo.cbAcknowledgments);
	return((nTypes.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKALERTSINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKALERTSINFO)));
}

BOOL CProfile::GetTCManualStackAlertInfo(INT nPage, INT nDisplay, CUIntArray &nTypes, CStringArray &szAuditions, CStringArray &szNotifications, CDWordArray &nAcknowledgeColors, CByteArray &bAcknowledgments) CONST
{
	struct {
		INT  cbSize;
		INT  cbTypes;
		INT  cbAuditions;
		INT  cbNotifications;
		INT  cbAcknowledgeColors;
		INT  cbAcknowledgments;
	} sInfo;
	INT  nSize;
	INT  cbAudition;
	INT  cbAuditions;
	INT  cbNotification;
	INT  cbNotifications;
	DWORD  dwType;
	CByteArray  nInfo;
	CByteArray  nInfoData[2];

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKALERTSINFO)), nInfo.SetSize(max(nSize, 0)), nTypes.RemoveAll(), szAuditions.RemoveAll(), szNotifications.RemoveAll(), nAcknowledgeColors.RemoveAll(), bAcknowledgments.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKALERTSINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors + sInfo.cbAcknowledgments)
				{
					nTypes.SetSize(sInfo.cbTypes / sizeof(UINT));
					nInfoData[0].SetSize(sInfo.cbAuditions);
					nInfoData[1].SetSize(sInfo.cbNotifications);
					nAcknowledgeColors.SetSize(sInfo.cbAcknowledgeColors / sizeof(DWORD));
					bAcknowledgments.SetSize(sInfo.cbAcknowledgments / sizeof(BYTE));
					CopyMemory(nTypes.GetData(), nInfo.GetData() + sizeof(sInfo), sInfo.cbTypes);
					CopyMemory(nInfoData[0].GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes, sInfo.cbAuditions);
					CopyMemory(nInfoData[1].GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions, sInfo.cbNotifications);
					CopyMemory(nAcknowledgeColors.GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications, sInfo.cbAcknowledgeColors);
					CopyMemory(bAcknowledgments.GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors, sInfo.cbAcknowledgments);
					for (cbAuditions = 0; cbAuditions < sInfo.cbAuditions; cbAuditions += cbAudition)
					{
						szAuditions.Add((LPCTSTR)(nInfoData[0].GetData() + cbAuditions));
						cbAudition = (szAuditions.GetAt(szAuditions.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
					}
					for (cbNotifications = 0; cbNotifications < sInfo.cbNotifications; cbNotifications += cbNotification)
					{
						szNotifications.Add((LPCTSTR)(nInfoData[1].GetData() + cbNotifications));
						cbNotification = (szNotifications.GetAt(szNotifications.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
					}
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCManualStackPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKPRINTINFO)));
}

BOOL CProfile::GetTCManualStackPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCMANUALSTACKPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCAutomaticStackLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nNormalStackScheduledColumns, CONST CUIntArray &nNormalStackScheduledWidths, CONST SIZE &sizeNormalStackScheduledList, COLORREF nNormalStackScheduledGridBackgroundColor, CONST CUIntArray &nNormalStackHistoricalColumns, CONST CUIntArray &nNormalStackHistoricalWidths, CONST SIZE &sizeNormalStackHistoricalList, COLORREF nNormalStackHistoricalGridBackgroundColor, CONST CUIntArray &nTimeTaggedStackScheduledColumns, CONST CUIntArray &nTimeTaggedStackScheduledWidths, CONST SIZE &sizeTimeTaggedStackScheduledList, COLORREF nTimeTaggedStackScheduledGridBackgroundColor, CONST CUIntArray &nTimeTaggedStackHistoricalColumns, CONST CUIntArray &nTimeTaggedStackHistoricalWidths, CONST SIZE &sizeTimeTaggedStackHistoricalList, COLORREF nTimeTaggedStackHistoricalGridBackgroundColor, BOOL bToolTips)
{
	struct {
		UINT  nSize;
		UINT  nColumns[2][2];
		UINT  nWidths[2][2];
		SIZE  size[2][2];
		COLORREF  nColor[2][2];
		BOOL  bToolTips;
	} sInfo;
	INT  cbData;
	CByteArray  nInfo;

	sInfo.bToolTips = bToolTips;
	sInfo.nColumns[0][0] = (UINT)nNormalStackScheduledColumns.GetSize();
	sInfo.nColumns[0][1] = (UINT)nNormalStackHistoricalColumns.GetSize();
	sInfo.nColumns[1][0] = (UINT)nTimeTaggedStackScheduledColumns.GetSize();
	sInfo.nColumns[1][1] = (UINT)nTimeTaggedStackHistoricalColumns.GetSize();
	sInfo.nWidths[0][0] = (UINT)nNormalStackScheduledWidths.GetSize();
	sInfo.nWidths[0][1] = (UINT)nNormalStackHistoricalWidths.GetSize();
	sInfo.nWidths[1][0] = (UINT)nTimeTaggedStackScheduledWidths.GetSize();
	sInfo.nWidths[1][1] = (UINT)nTimeTaggedStackHistoricalWidths.GetSize();
	sInfo.size[0][0].cx = sizeNormalStackScheduledList.cx;
	sInfo.size[0][0].cy = sizeNormalStackScheduledList.cy;
	sInfo.size[0][1].cx = sizeNormalStackHistoricalList.cx;
	sInfo.size[0][1].cy = sizeNormalStackHistoricalList.cy;
	sInfo.size[1][0].cx = sizeTimeTaggedStackScheduledList.cx;
	sInfo.size[1][0].cy = sizeTimeTaggedStackScheduledList.cy;
	sInfo.size[1][1].cx = sizeTimeTaggedStackHistoricalList.cx;
	sInfo.size[1][1].cy = sizeTimeTaggedStackHistoricalList.cy;
	sInfo.nColor[0][0] = nNormalStackScheduledGridBackgroundColor;
	sInfo.nColor[0][1] = nNormalStackHistoricalGridBackgroundColor;
	sInfo.nColor[1][0] = nTimeTaggedStackScheduledGridBackgroundColor;
	sInfo.nColor[1][1] = nTimeTaggedStackHistoricalGridBackgroundColor;
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + (nNormalStackScheduledColumns.GetSize() + nNormalStackHistoricalColumns.GetSize() + nTimeTaggedStackScheduledColumns.GetSize() + nTimeTaggedStackHistoricalColumns.GetSize() + nNormalStackScheduledWidths.GetSize() + nNormalStackHistoricalWidths.GetSize() + nTimeTaggedStackScheduledWidths.GetSize() + nTimeTaggedStackHistoricalWidths.GetSize())*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + (cbData = sizeof(sInfo)), nNormalStackScheduledColumns.GetData(), nNormalStackScheduledColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + (cbData = cbData + (INT)(nNormalStackScheduledColumns.GetSize()*sizeof(UINT))), nNormalStackHistoricalColumns.GetData(), nNormalStackHistoricalColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + (cbData = cbData + (INT)(nNormalStackHistoricalColumns.GetSize()*sizeof(UINT))), nTimeTaggedStackScheduledColumns.GetData(), nTimeTaggedStackScheduledColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + (cbData = cbData + (INT)(nTimeTaggedStackScheduledColumns.GetSize()*sizeof(UINT))), nTimeTaggedStackHistoricalColumns.GetData(), nTimeTaggedStackHistoricalColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + (cbData = cbData + (INT)(nTimeTaggedStackHistoricalColumns.GetSize()*sizeof(UINT))), nNormalStackScheduledWidths.GetData(), nNormalStackScheduledWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + (cbData = cbData + (INT)(nNormalStackScheduledWidths.GetSize()*sizeof(UINT))), nNormalStackHistoricalWidths.GetData(), nNormalStackHistoricalWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + (cbData = cbData + (INT)(nNormalStackHistoricalWidths.GetSize()*sizeof(UINT))), nTimeTaggedStackScheduledWidths.GetData(), nTimeTaggedStackScheduledWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + (cbData = cbData + (INT)(nTimeTaggedStackScheduledWidths.GetSize()*sizeof(UINT))), nTimeTaggedStackHistoricalWidths.GetData(), nTimeTaggedStackHistoricalWidths.GetSize()*sizeof(UINT));
	return((nNormalStackScheduledColumns.GetSize() > 0 && nNormalStackHistoricalColumns.GetSize() > 0 && nTimeTaggedStackScheduledColumns.GetSize() > 0 && nTimeTaggedStackHistoricalColumns.GetSize() > 0 && nNormalStackScheduledWidths.GetSize() > 0 && nNormalStackHistoricalWidths.GetSize() > 0 && nTimeTaggedStackScheduledWidths.GetSize() > 0 && nTimeTaggedStackHistoricalWidths.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKLAYOUTINFO)));
}

BOOL CProfile::GetTCAutomaticStackLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nNormalStackScheduledColumns, CUIntArray &nNormalStackScheduledWidths, CSize &sizeNormalStackScheduledList, COLORREF &nNormalStackScheduledGridBackgroundColor, CUIntArray &nNormalStackHistoricalColumns, CUIntArray &nNormalStackHistoricalWidths, CSize &sizeNormalStackHistoricalList, COLORREF &nNormalStackHistoricalGridBackgroundColor, CUIntArray &nTimeTaggedStackScheduledColumns, CUIntArray &nTimeTaggedStackScheduledWidths, CSize &sizeTimeTaggedStackScheduledList, COLORREF &nTimeTaggedStackScheduledGridBackgroundColor, CUIntArray &nTimeTaggedStackHistoricalColumns, CUIntArray &nTimeTaggedStackHistoricalWidths, CSize &sizeTimeTaggedStackHistoricalList, COLORREF &nTimeTaggedStackHistoricalGridBackgroundColor, BOOL &bToolTips) CONST
{
	struct {
		UINT  nSize;
		UINT  nColumns[2][2];
		UINT  nWidths[2][2];
		SIZE  size[2][2];
		COLORREF  nColor[2][2];
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + (sInfo.nColumns[0][0] + sInfo.nColumns[0][1] + sInfo.nColumns[1][0] + sInfo.nColumns[1][1] + sInfo.nWidths[0][0] + sInfo.nWidths[0][1] + sInfo.nWidths[1][0] + sInfo.nWidths[1][1])*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nNormalStackScheduledColumns.SetSize(sInfo.nColumns[0][0]);
					CopyMemory(nNormalStackScheduledColumns.GetData(), nInfo.GetData(), nNormalStackScheduledColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColumns[0][0] * sizeof(UINT));
					nNormalStackHistoricalColumns.SetSize(sInfo.nColumns[0][1]);
					CopyMemory(nNormalStackHistoricalColumns.GetData(), nInfo.GetData(), nNormalStackHistoricalColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColumns[0][1] * sizeof(UINT));
					nTimeTaggedStackScheduledColumns.SetSize(sInfo.nColumns[1][0]);
					CopyMemory(nTimeTaggedStackScheduledColumns.GetData(), nInfo.GetData(), nTimeTaggedStackScheduledColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColumns[1][0] * sizeof(UINT));
					nTimeTaggedStackHistoricalColumns.SetSize(sInfo.nColumns[1][1]);
					CopyMemory(nTimeTaggedStackHistoricalColumns.GetData(), nInfo.GetData(), nTimeTaggedStackHistoricalColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColumns[1][1] * sizeof(UINT));
					nNormalStackScheduledWidths.SetSize(sInfo.nWidths[0][0]);
					CopyMemory(nNormalStackScheduledWidths.GetData(), nInfo.GetData(), nNormalStackScheduledWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nWidths[0][0] * sizeof(UINT));
					nNormalStackHistoricalWidths.SetSize(sInfo.nWidths[0][1]);
					CopyMemory(nNormalStackHistoricalWidths.GetData(), nInfo.GetData(), nNormalStackHistoricalWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nWidths[0][1] * sizeof(UINT));
					nTimeTaggedStackScheduledWidths.SetSize(sInfo.nWidths[1][0]);
					CopyMemory(nTimeTaggedStackScheduledWidths.GetData(), nInfo.GetData(), nTimeTaggedStackScheduledWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nWidths[1][0] * sizeof(UINT));
					nTimeTaggedStackHistoricalWidths.SetSize(sInfo.nWidths[1][1]);
					CopyMemory(nTimeTaggedStackHistoricalWidths.GetData(), nInfo.GetData(), nTimeTaggedStackHistoricalWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nWidths[1][1] * sizeof(UINT));
					sizeNormalStackScheduledList.cx = sInfo.size[0][0].cx;
					sizeNormalStackScheduledList.cy = sInfo.size[0][0].cy;
					sizeNormalStackHistoricalList.cx = sInfo.size[0][1].cx;
					sizeNormalStackHistoricalList.cy = sInfo.size[0][1].cy;
					sizeTimeTaggedStackScheduledList.cx = sInfo.size[1][0].cx;
					sizeTimeTaggedStackScheduledList.cy = sInfo.size[1][0].cy;
					sizeTimeTaggedStackHistoricalList.cx = sInfo.size[1][1].cx;
					sizeTimeTaggedStackHistoricalList.cy = sInfo.size[1][1].cy;
					nNormalStackScheduledGridBackgroundColor = sInfo.nColor[0][0];
					nNormalStackHistoricalGridBackgroundColor = sInfo.nColor[0][1];
					nTimeTaggedStackScheduledGridBackgroundColor = sInfo.nColor[1][0];
					nTimeTaggedStackHistoricalGridBackgroundColor = sInfo.nColor[1][1];
					bToolTips = sInfo.bToolTips;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCAutomaticStackFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pNormalStackScheduledTitleFont, CONST LOGFONT *pNormalStackScheduledItemsFont, CONST LOGFONT *pNormalStackHistoricalTitleFont, CONST LOGFONT *pNormalStackHistoricalItemsFont, CONST LOGFONT *pTimeTaggedStackScheduledTitleFont, CONST LOGFONT *pTimeTaggedStackScheduledItemsFont, CONST LOGFONT *pTimeTaggedStackHistoricalTitleFont, CONST LOGFONT *pTimeTaggedStackHistoricalItemsFont)
{
	LOGFONT  sFontsInfo[2][2][2];

	CopyMemory(&sFontsInfo[0][0][0], pNormalStackScheduledTitleFont, (AfxIsValidAddress(pNormalStackScheduledTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[0][0][1], pNormalStackScheduledItemsFont, (AfxIsValidAddress(pNormalStackScheduledItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[0][1][0], pNormalStackHistoricalTitleFont, (AfxIsValidAddress(pNormalStackHistoricalTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[0][1][1], pNormalStackHistoricalItemsFont, (AfxIsValidAddress(pNormalStackHistoricalItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][0][0], pTimeTaggedStackScheduledTitleFont, (AfxIsValidAddress(pTimeTaggedStackScheduledTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][0][1], pTimeTaggedStackScheduledItemsFont, (AfxIsValidAddress(pTimeTaggedStackScheduledItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][1][0], pTimeTaggedStackHistoricalTitleFont, (AfxIsValidAddress(pTimeTaggedStackHistoricalTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1][1][1], pTimeTaggedStackHistoricalItemsFont, (AfxIsValidAddress(pTimeTaggedStackHistoricalItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pNormalStackScheduledTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pNormalStackScheduledItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pNormalStackHistoricalTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pNormalStackHistoricalItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pTimeTaggedStackScheduledTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pTimeTaggedStackScheduledItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pTimeTaggedStackHistoricalTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pTimeTaggedStackHistoricalItemsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKFONTSINFO)));
}

BOOL CProfile::GetTCAutomaticStackFontsInfo(INT nPage, INT nDisplay, LOGFONT *pNormalStackScheduledTitleFont, LOGFONT *pNormalStackScheduledItemsFont, LOGFONT *pNormalStackHistoricalTitleFont, LOGFONT *pNormalStackHistoricalItemsFont, LOGFONT *pTimeTaggedStackScheduledTitleFont, LOGFONT *pTimeTaggedStackScheduledItemsFont, LOGFONT *pTimeTaggedStackHistoricalTitleFont, LOGFONT *pTimeTaggedStackHistoricalItemsFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[2][2][2];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pNormalStackScheduledTitleFont, &sFontsInfo[0][0][0], (AfxIsValidAddress(pNormalStackScheduledTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pNormalStackScheduledItemsFont, &sFontsInfo[0][0][1], (AfxIsValidAddress(pNormalStackScheduledItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pNormalStackHistoricalTitleFont, &sFontsInfo[0][1][0], (AfxIsValidAddress(pNormalStackHistoricalTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pNormalStackHistoricalItemsFont, &sFontsInfo[0][1][1], (AfxIsValidAddress(pNormalStackHistoricalItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pTimeTaggedStackScheduledTitleFont, &sFontsInfo[1][0][0], (AfxIsValidAddress(pTimeTaggedStackScheduledTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pTimeTaggedStackScheduledItemsFont, &sFontsInfo[1][0][1], (AfxIsValidAddress(pTimeTaggedStackScheduledItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pTimeTaggedStackHistoricalTitleFont, &sFontsInfo[1][1][0], (AfxIsValidAddress(pTimeTaggedStackHistoricalTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pTimeTaggedStackHistoricalItemsFont, &sFontsInfo[1][1][1], (AfxIsValidAddress(pTimeTaggedStackHistoricalItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCAutomaticStackOperationsInfo(INT nPage, INT nDisplay, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingChecks, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, INT nUpdateCheckCount, INT nArgumentCount, BOOL bAllArguments, UINT nMiscellaneousOptions, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CTimeSpan &tDispatchTimeWindow, UINT nUserPermissions)
{
	struct {
		INT  cbSize;
		INT  nArgumentCount;
		INT  nUpdateCheckCount;
		UINT  nTelecommandingMode;
		UINT  nTelecommandingState;
		UINT  nTelecommandingChecks;
		UINT  nMiscellaneousOptions;
		UINT  nUserPermissions;
		TIMEKEY  tDispatchTimeWindow;
		TIMEKEY  tDefaultReleaseTimeWindow;
		BOOL  bTelecommandingAutoRejectionMode;
		BOOL  bTelecommandingReleaseWaitMode;
		BOOL  bTelecommandingInterlockMode;
		BOOL  bAllArguments;
	} sInfo;

	sInfo.cbSize = sizeof(sInfo);
	sInfo.bAllArguments = bAllArguments;
	sInfo.nArgumentCount = nArgumentCount;
	sInfo.nUserPermissions = nUserPermissions;
	sInfo.nUpdateCheckCount = nUpdateCheckCount;
	sInfo.nTelecommandingMode = nTelecommandingMode;
	sInfo.nTelecommandingState = nTelecommandingState;
	sInfo.nTelecommandingChecks = nTelecommandingChecks;
	sInfo.nMiscellaneousOptions = nMiscellaneousOptions;
	sInfo.bTelecommandingInterlockMode = bTelecommandingInterlockMode;
	sInfo.bTelecommandingReleaseWaitMode = bTelecommandingReleaseWaitMode;
	sInfo.bTelecommandingAutoRejectionMode = bTelecommandingAutoRejectionMode;
	sInfo.tDefaultReleaseTimeWindow = tDefaultReleaseTimeWindow.GetTotalSeconds();
	sInfo.tDispatchTimeWindow = tDispatchTimeWindow.GetTotalSeconds();
	return((nTelecommandingMode != (UINT)-1 && nTelecommandingState != (UINT)-1 && nTelecommandingChecks != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKOPERATIONSINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKOPERATIONSINFO)));
}

BOOL CProfile::GetTCAutomaticStackOperationsInfo(INT nPage, INT nDisplay, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingChecks, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, INT &nUpdateCheckCount, INT &nArgumentCount, BOOL &bAllArguments, UINT &nMiscellaneousOptions, CTimeSpan &tDefaultReleaseTimeWindow, CTimeSpan &tDispatchTimeWindow, UINT &nUserPermissions) CONST
{
	struct {
		INT  cbSize;
		INT  nArgumentCount;
		INT  nUpdateCheckCount;
		UINT  nTelecommandingMode;
		UINT  nTelecommandingState;
		UINT  nTelecommandingChecks;
		UINT  nMiscellaneousOptions;
		UINT  nUserPermissions;
		TIMEKEY  tDispatchTimeWindow;
		TIMEKEY  tDefaultReleaseTimeWindow;
		BOOL  bTelecommandingAutoRejectionMode;
		BOOL  bTelecommandingReleaseWaitMode;
		BOOL  bTelecommandingInterlockMode;
		BOOL  bAllArguments;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKOPERATIONSINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKOPERATIONSINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize == (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) / sizeof(BYTE))
				{
					nTelecommandingMode = sInfo.nTelecommandingMode;
					nTelecommandingState = sInfo.nTelecommandingState;
					nTelecommandingChecks = sInfo.nTelecommandingChecks;
					nMiscellaneousOptions = sInfo.nMiscellaneousOptions;
					bTelecommandingInterlockMode = sInfo.bTelecommandingInterlockMode;
					bTelecommandingReleaseWaitMode = sInfo.bTelecommandingReleaseWaitMode;
					bTelecommandingAutoRejectionMode = sInfo.bTelecommandingAutoRejectionMode;
					tDefaultReleaseTimeWindow = sInfo.tDefaultReleaseTimeWindow;
					tDispatchTimeWindow = sInfo.tDispatchTimeWindow;
					nUpdateCheckCount = sInfo.nUpdateCheckCount;
					nUserPermissions = sInfo.nUserPermissions;
					nArgumentCount = sInfo.nArgumentCount;
					bAllArguments = sInfo.bAllArguments;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCAutomaticStackContentsInfo(INT nPage, INT nDisplay, CONST CByteArray &nContentsInfo)
{
	return((nContentsInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKCONTENTSINFO), REG_BINARY, nContentsInfo.GetData(), (INT)nContentsInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKCONTENTSINFO)));
}

BOOL CProfile::GetTCAutomaticStackContentsInfo(INT nPage, INT nDisplay, CByteArray &nContentsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKCONTENTSINFO)), nContentsInfo.SetSize(max(nSize, 0)); nSize > 0 && nContentsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKCONTENTSINFO), &dwType, nContentsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCAutomaticStackFilterInfo(INT nPage, INT nDisplay, UINT nMode, LPCTSTR pszName, LPCTSTR pszSequence, CONST CUIntArray &nSubSystemIDs, UINT nLimitation, UINT nSortMode)
{
	struct {
		INT  cbSize;
		INT  cbTelecommand[2];
		INT  cbSubSystemIDs;
		UINT  nMode[2];
		UINT  nLimitation;
	} sInfo;
	CByteArray  nInfo;

	sInfo.nMode[0] = nMode;
	sInfo.nMode[1] = nSortMode;
	sInfo.nLimitation = nLimitation;
	sInfo.cbSubSystemIDs = (INT)(nSubSystemIDs.GetSize()*sizeof(UINT));
	sInfo.cbTelecommand[0] = (AfxIsValidString(pszName)) ? ((lstrlen(pszName) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbTelecommand[1] = (AfxIsValidString(pszSequence)) ? ((lstrlen(pszSequence) + 1)*sizeof(TCHAR)) : 0;
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbTelecommand[0] + sInfo.cbTelecommand[1] + sInfo.cbSubSystemIDs));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), pszName, sInfo.cbTelecommand[0]);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTelecommand[0], pszSequence, sInfo.cbTelecommand[1]);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTelecommand[0] + sInfo.cbTelecommand[1], nSubSystemIDs.GetData(), sInfo.cbSubSystemIDs);
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKFILTERINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKFILTERINFO)));
}

BOOL CProfile::GetTCAutomaticStackFilterInfo(INT nPage, INT nDisplay, UINT &nMode, CString &szName, CString &szSequence, CUIntArray &nSubSystemIDs, UINT &nLimitation, UINT &nSortMode) CONST
{
	struct {
		INT  cbSize;
		INT  cbTelecommand[2];
		INT  cbSubSystemIDs;
		UINT  nMode[2];
		UINT  nLimitation;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKFILTERINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKFILTERINFO), &dwType, (BYTE *)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbTelecommand[0] + sInfo.cbTelecommand[1] + sInfo.cbSubSystemIDs)
				{
					for (nSubSystemIDs.SetSize(sInfo.cbSubSystemIDs / sizeof(UINT)), CopyMemory(szName.GetBufferSetLength(STRINGCHARS(sInfo.cbTelecommand[0])), nInfo.GetData() + sizeof(sInfo), STRINGBYTES(sInfo.cbTelecommand[0])), CopyMemory(szSequence.GetBufferSetLength(STRINGCHARS(sInfo.cbTelecommand[1])), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTelecommand[0], STRINGBYTES(sInfo.cbTelecommand[1])); nSubSystemIDs.GetSize() == sInfo.cbSubSystemIDs / sizeof(UINT); )
					{
						CopyMemory(nSubSystemIDs.GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTelecommand[0] + sInfo.cbTelecommand[1], sInfo.cbSubSystemIDs);
						break;
					}
					nMode = sInfo.nMode[0];
					nSortMode = sInfo.nMode[1];
					nLimitation = sInfo.nLimitation;
					szSequence.ReleaseBuffer();
					szName.ReleaseBuffer();
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCAutomaticStackSearchInfo(INT nPage, INT nDisplay, CONST CByteArray &nFiltersInfo)
{
	struct {
		INT  cbSize;
		INT  cbFilters;
	} sInfo;
	CByteArray  nInfo;

	sInfo.cbFilters = (INT)(nFiltersInfo.GetSize()*sizeof(BYTE));
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbFilters));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nFiltersInfo.GetData(), sInfo.cbFilters);
	return((nFiltersInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKSEARCHINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKSEARCHINFO)));
}

BOOL CProfile::GetTCAutomaticStackSearchInfo(INT nPage, INT nDisplay, CByteArray &nFiltersInfo) CONST
{
	struct {
		INT  cbSize;
		INT  cbFilters;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKSEARCHINFO)), nInfo.SetSize(max(nSize, 0)), nFiltersInfo.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKSEARCHINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbFilters  &&  sInfo.cbSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nFiltersInfo.SetSize(sInfo.cbFilters);
					CopyMemory(nFiltersInfo.GetData(), nInfo.GetData(), sInfo.cbFilters);
					nInfo.RemoveAt(0, sInfo.cbFilters);
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCAutomaticStackTemplatesInfo(INT nPage, INT nDisplay, CONST CByteArray &nItemTemplatesInfo, CONST CByteArray &nComposedItemTemplatesInfo)
{
	struct {
		INT  cbSize;
		INT  cbTemplates[2];
	} sInfo;
	CByteArray  nInfo;

	sInfo.cbTemplates[0] = (INT)(nItemTemplatesInfo.GetSize()*sizeof(BYTE));
	sInfo.cbTemplates[1] = (INT)(nComposedItemTemplatesInfo.GetSize()*sizeof(BYTE));
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbTemplates[0] + sInfo.cbTemplates[1]));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nItemTemplatesInfo.GetData(), sInfo.cbTemplates[0]);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTemplates[0], nComposedItemTemplatesInfo.GetData(), sInfo.cbTemplates[1]);
	return((nItemTemplatesInfo.GetSize() > 0 || nComposedItemTemplatesInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKTEMPLATESINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKTEMPLATESINFO)));
}

BOOL CProfile::GetTCAutomaticStackTemplatesInfo(INT nPage, INT nDisplay, CByteArray &nItemTemplatesInfo, CByteArray &nComposedItemTemplatesInfo) CONST
{
	struct {
		INT  cbSize;
		INT  cbTemplates[2];
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKTEMPLATESINFO)), nInfo.SetSize(max(nSize, 0)), nItemTemplatesInfo.RemoveAll(), nComposedItemTemplatesInfo.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKTEMPLATESINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbTemplates[0] + sInfo.cbTemplates[1] && sInfo.cbSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nItemTemplatesInfo.SetSize(sInfo.cbTemplates[0]);
					CopyMemory(nItemTemplatesInfo.GetData(), nInfo.GetData(), sInfo.cbTemplates[0]);
					nInfo.RemoveAt(0, sInfo.cbTemplates[0]);
					nComposedItemTemplatesInfo.SetSize(sInfo.cbTemplates[1]);
					CopyMemory(nComposedItemTemplatesInfo.GetData(), nInfo.GetData(), sInfo.cbTemplates[1]);
					nInfo.RemoveAt(0, sInfo.cbTemplates[1]);
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCAutomaticStackSubSystemsInfo(INT nPage, INT nDisplay, CONST CUIntArray &nSubSystemIDs, CONST CStringArray &szEnablingEvents, CONST CStringArray &szDisablingEvents, CONST CUIntArray &nStatus)
{
	struct {
		INT  cbSize;
		INT  cbSubSystemIDs;
		INT  cbEvents[2];
		INT  cbStatus;
	} sInfo;
	INT  nSubSystem;
	INT  nSubSystems;
	CByteArray  nInfo;
	CByteArray  nEventsData[2];

	for (nSubSystem = 0, nSubSystems = (INT)nSubSystemIDs.GetSize(), sInfo.cbEvents[0] = sInfo.cbEvents[1] = 0; nSubSystem < nSubSystems; nSubSystem++)
	{
		nEventsData[0].SetSize(sInfo.cbEvents[0] + (szEnablingEvents.GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR));
		nEventsData[1].SetSize(sInfo.cbEvents[1] + (szDisablingEvents.GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nEventsData[0].GetData() + sInfo.cbEvents[0], (LPCTSTR)szEnablingEvents.GetAt(nSubSystem), (szEnablingEvents.GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nEventsData[1].GetData() + sInfo.cbEvents[1], (LPCTSTR)szDisablingEvents.GetAt(nSubSystem), (szDisablingEvents.GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR));
		sInfo.cbEvents[0] += (szEnablingEvents.GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR);
		sInfo.cbEvents[1] += (szDisablingEvents.GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR);
	}
	sInfo.cbStatus = (INT)(nStatus.GetSize()*sizeof(UINT));
	sInfo.cbSubSystemIDs = (INT)(nSubSystemIDs.GetSize()*sizeof(UINT));
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbSubSystemIDs + sInfo.cbEvents[0] + sInfo.cbEvents[1] + sInfo.cbStatus));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nSubSystemIDs.GetData(), sInfo.cbSubSystemIDs);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbSubSystemIDs, nEventsData[0].GetData(), sInfo.cbEvents[0]);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbSubSystemIDs + sInfo.cbEvents[0], nEventsData[1].GetData(), sInfo.cbEvents[1]);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbSubSystemIDs + sInfo.cbEvents[0] + sInfo.cbEvents[1], nStatus.GetData(), sInfo.cbStatus);
	return((nSubSystemIDs.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKSUBSYSTEMSINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKSUBSYSTEMSINFO)));
}

BOOL CProfile::GetTCAutomaticStackSubSystemsInfo(INT nPage, INT nDisplay, CUIntArray &nSubSystemIDs, CStringArray &szEnablingEvents, CStringArray &szDisablingEvents, CUIntArray &nStatus) CONST
{
	struct {
		INT  cbSize;
		INT  cbSubSystemIDs;
		INT  cbEvents[2];
		INT  cbStatus;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;
	CByteArray  nEventsData[2];

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKSUBSYSTEMSINFO)), nInfo.SetSize(max(nSize, 0)), nSubSystemIDs.RemoveAll(), szEnablingEvents.RemoveAll(), szDisablingEvents.RemoveAll(), nStatus.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKSUBSYSTEMSINFO), &dwType, (BYTE *)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbSubSystemIDs + sInfo.cbEvents[0] + sInfo.cbEvents[1] + sInfo.cbStatus  &&  sInfo.cbSize == nInfo.GetSize())
				{
					for (nSubSystemIDs.SetSize(sInfo.cbSubSystemIDs / sizeof(UINT)), nEventsData[0].SetSize(sInfo.cbEvents[0]), nEventsData[1].SetSize(sInfo.cbEvents[1]), nStatus.SetSize(sInfo.cbStatus / sizeof(UINT)), CopyMemory(nSubSystemIDs.GetData(), nInfo.GetData() + sizeof(sInfo), sInfo.cbSubSystemIDs), CopyMemory(nEventsData[0].GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbSubSystemIDs, sInfo.cbEvents[0]), CopyMemory(nEventsData[1].GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbSubSystemIDs + sInfo.cbEvents[0], sInfo.cbEvents[1]), CopyMemory(nStatus.GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbSubSystemIDs + sInfo.cbEvents[0] + sInfo.cbEvents[1], sInfo.cbStatus), szEnablingEvents.RemoveAll(); nEventsData[0].GetSize() > 0; nEventsData[0].RemoveAt(0, (szEnablingEvents.GetAt(szEnablingEvents.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
					{
						szEnablingEvents.Add((LPCTSTR)nEventsData[0].GetData());
						continue;
					}
					for (szDisablingEvents.RemoveAll(); nEventsData[1].GetSize() > 0; nEventsData[1].RemoveAt(0, (szDisablingEvents.GetAt(szDisablingEvents.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
					{
						szDisablingEvents.Add((LPCTSTR)nEventsData[1].GetData());
						continue;
					}
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCAutomaticStackPlanningInfo(INT nPage, INT nDisplay, LPCTSTR pszMissionPlanningComputer, LPCTSTR pszMissionPlanningBackupComputer, UINT nMissionPlanningOptions, CONST CTimeSpan &tMissionPlanningPeriod, LPCTSTR pszMissionPlanningAudition, LPCTSTR pszMissionPlanningNotification, LPCTSTR pszFlightDynamicsComputer, LPCTSTR pszFlightDynamicsBackupComputer, UINT nFlightDynamicsOptions)
{
	struct {
		INT  cbSize;
		INT  cbMissionPlanningComputer[2];
		INT  cbMissionPlanningAudition;
		INT  cbMissionPlanningNotification;
		INT  cbFlightDynamicsComputer[2];
		UINT  nMissionPlanningOptions;
		UINT  nFlightDynamicsOptions;
		TIMEKEY  tMissionPlanningPeriod;
	} sInfo;
	CByteArray  nInfo;

	sInfo.nMissionPlanningOptions = nMissionPlanningOptions;
	sInfo.nFlightDynamicsOptions = nFlightDynamicsOptions;
	sInfo.tMissionPlanningPeriod = tMissionPlanningPeriod.GetTotalSeconds();
	sInfo.cbMissionPlanningComputer[0] = (AfxIsValidString(pszMissionPlanningComputer)) ? ((lstrlen(pszMissionPlanningComputer) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbMissionPlanningComputer[1] = (AfxIsValidString(pszMissionPlanningBackupComputer)) ? ((lstrlen(pszMissionPlanningBackupComputer) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbFlightDynamicsComputer[0] = (AfxIsValidString(pszFlightDynamicsComputer)) ? ((lstrlen(pszFlightDynamicsComputer) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbFlightDynamicsComputer[1] = (AfxIsValidString(pszFlightDynamicsBackupComputer)) ? ((lstrlen(pszFlightDynamicsBackupComputer) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbMissionPlanningAudition = (AfxIsValidString(pszMissionPlanningAudition)) ? ((lstrlen(pszMissionPlanningAudition) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbMissionPlanningNotification = (AfxIsValidString(pszMissionPlanningNotification)) ? ((lstrlen(pszMissionPlanningNotification) + 1)*sizeof(TCHAR)) : 0;
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0] + sInfo.cbMissionPlanningComputer[1] + sInfo.cbMissionPlanningAudition + sInfo.cbMissionPlanningNotification + sInfo.cbFlightDynamicsComputer[0] + sInfo.cbFlightDynamicsComputer[1]));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), pszMissionPlanningComputer, sInfo.cbMissionPlanningComputer[0]);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0], pszMissionPlanningBackupComputer, sInfo.cbMissionPlanningComputer[1]);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0] + sInfo.cbMissionPlanningComputer[1], pszMissionPlanningAudition, sInfo.cbMissionPlanningAudition);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0] + sInfo.cbMissionPlanningComputer[1] + sInfo.cbMissionPlanningAudition, pszMissionPlanningNotification, sInfo.cbMissionPlanningNotification);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0] + sInfo.cbMissionPlanningComputer[1] + sInfo.cbMissionPlanningAudition + sInfo.cbMissionPlanningNotification, pszFlightDynamicsComputer, sInfo.cbFlightDynamicsComputer[0]);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0] + sInfo.cbMissionPlanningComputer[1] + sInfo.cbMissionPlanningAudition + sInfo.cbMissionPlanningNotification + sInfo.cbFlightDynamicsComputer[0], pszFlightDynamicsBackupComputer, sInfo.cbFlightDynamicsComputer[1]);
	return((AfxIsValidString(pszMissionPlanningComputer) && AfxIsValidString(pszMissionPlanningBackupComputer) && nMissionPlanningOptions != (UINT)-1 && AfxIsValidString(pszMissionPlanningAudition) && AfxIsValidString(pszMissionPlanningNotification) && AfxIsValidString(pszFlightDynamicsComputer) && AfxIsValidString(pszFlightDynamicsBackupComputer) && nFlightDynamicsOptions != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKPLANNINGINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKPLANNINGINFO)));
}

BOOL CProfile::GetTCAutomaticStackPlanningInfo(INT nPage, INT nDisplay, CString &szMissionPlanningComputer, CString &szMissionPlanningBackupComputer, UINT &nMissionPlanningOptions, CTimeSpan &tMissionPlanningPeriod, CString &szMissionPlanningAudition, CString &szMissionPlanningNotification, CString &szFlightDynamicsComputer, CString &szFlightDynamicsBackupComputer, UINT &nFlightDynamicsOptions) CONST
{
	struct {
		INT  cbSize;
		INT  cbMissionPlanningComputer[2];
		INT  cbMissionPlanningAudition;
		INT  cbMissionPlanningNotification;
		INT  cbFlightDynamicsComputer[2];
		UINT  nMissionPlanningOptions;
		UINT  nFlightDynamicsOptions;
		TIMEKEY  tMissionPlanningPeriod;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKPLANNINGINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKPLANNINGINFO), &dwType, (BYTE *)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0] + sInfo.cbMissionPlanningComputer[1] + sInfo.cbMissionPlanningAudition + sInfo.cbMissionPlanningNotification + sInfo.cbFlightDynamicsComputer[0] + sInfo.cbFlightDynamicsComputer[1])
				{
					CopyMemory(szMissionPlanningComputer.GetBufferSetLength(STRINGCHARS(sInfo.cbMissionPlanningComputer[0])), nInfo.GetData() + sizeof(sInfo), STRINGBYTES(sInfo.cbMissionPlanningComputer[0]));
					CopyMemory(szMissionPlanningBackupComputer.GetBufferSetLength(STRINGCHARS(sInfo.cbMissionPlanningComputer[1])), nInfo.GetData() + sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0], STRINGBYTES(sInfo.cbMissionPlanningComputer[1]));
					CopyMemory(szMissionPlanningAudition.GetBufferSetLength(STRINGCHARS(sInfo.cbMissionPlanningAudition)), nInfo.GetData() + sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0] + sInfo.cbMissionPlanningComputer[1], STRINGBYTES(sInfo.cbMissionPlanningAudition));
					CopyMemory(szMissionPlanningNotification.GetBufferSetLength(STRINGCHARS(sInfo.cbMissionPlanningNotification)), nInfo.GetData() + sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0] + sInfo.cbMissionPlanningComputer[1] + sInfo.cbMissionPlanningAudition, STRINGBYTES(sInfo.cbMissionPlanningNotification));
					CopyMemory(szFlightDynamicsComputer.GetBufferSetLength(STRINGCHARS(sInfo.cbFlightDynamicsComputer[0])), nInfo.GetData() + sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0] + sInfo.cbMissionPlanningComputer[1] + sInfo.cbMissionPlanningAudition + sInfo.cbMissionPlanningNotification, STRINGBYTES(sInfo.cbFlightDynamicsComputer[0]));
					CopyMemory(szFlightDynamicsBackupComputer.GetBufferSetLength(STRINGCHARS(sInfo.cbFlightDynamicsComputer[1])), nInfo.GetData() + sizeof(sInfo) + sInfo.cbMissionPlanningComputer[0] + sInfo.cbMissionPlanningComputer[1] + sInfo.cbMissionPlanningAudition + sInfo.cbMissionPlanningNotification + sInfo.cbFlightDynamicsComputer[0], STRINGBYTES(sInfo.cbFlightDynamicsComputer[1]));
					nMissionPlanningOptions = sInfo.nMissionPlanningOptions;
					tMissionPlanningPeriod = sInfo.tMissionPlanningPeriod;
					nFlightDynamicsOptions = sInfo.nFlightDynamicsOptions;
					szMissionPlanningComputer.ReleaseBuffer();
					szMissionPlanningBackupComputer.ReleaseBuffer();
					szMissionPlanningAudition.ReleaseBuffer();
					szMissionPlanningNotification.ReleaseBuffer();
					szFlightDynamicsComputer.ReleaseBuffer();
					szFlightDynamicsBackupComputer.ReleaseBuffer();
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCAutomaticStackLoggingInfo(INT nPage, INT nDisplay, UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent)
{
	struct {
		INT  cbSize;
		INT  cbArchivalFileName;
		INT  cbRetrievalFileName;
		UINT  nArchivalPolicy;
		UINT  nRetrievalReloadCount;
		DWORDLONG  dwArchivalRetention;
		TIMEKEY  tArchivalRetention;
		BOOL  bShowAsEvent;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bShowAsEvent = bShowAsEvent;
	sInfo.nArchivalPolicy = nArchivalPolicy;
	sInfo.dwArchivalRetention = dwArchivalRetention;
	sInfo.nRetrievalReloadCount = nRetrievalReloadCount;
	sInfo.tArchivalRetention = tArchivalRetention.GetTotalSeconds();
	sInfo.cbArchivalFileName = (AfxIsValidString(pszArchivalFileName)) ? ((lstrlen(pszArchivalFileName) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbRetrievalFileName = (AfxIsValidString(pszRetrievalFileName)) ? ((lstrlen(pszRetrievalFileName) + 1)*sizeof(TCHAR)) : 0;
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbArchivalFileName + sInfo.cbRetrievalFileName));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), pszArchivalFileName, sInfo.cbArchivalFileName);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbArchivalFileName, pszRetrievalFileName, sInfo.cbRetrievalFileName);
	return((AfxIsValidString(pszArchivalFileName) && AfxIsValidString(pszRetrievalFileName)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKLOGGINGINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKLOGGINGINFO)));
}

BOOL CProfile::GetTCAutomaticStackLoggingInfo(INT nPage, INT nDisplay, UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST
{
	struct {
		INT  cbSize;
		INT  cbArchivalFileName;
		INT  cbRetrievalFileName;
		UINT  nArchivalPolicy;
		UINT  nRetrievalReloadCount;
		DWORDLONG  dwArchivalRetention;
		TIMEKEY  tArchivalRetention;
		BOOL  bShowAsEvent;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKLOGGINGINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKLOGGINGINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbArchivalFileName + sInfo.cbRetrievalFileName)
				{
					CopyMemory(szArchivalFileName.GetBufferSetLength(STRINGCHARS(sInfo.cbArchivalFileName)), nInfo.GetData() + sizeof(sInfo), STRINGBYTES(sInfo.cbArchivalFileName));
					CopyMemory(szRetrievalFileName.GetBufferSetLength(STRINGCHARS(sInfo.cbRetrievalFileName)), nInfo.GetData() + sizeof(sInfo) + sInfo.cbArchivalFileName, STRINGBYTES(sInfo.cbRetrievalFileName));
					nRetrievalReloadCount = sInfo.nRetrievalReloadCount;
					dwArchivalRetention = sInfo.dwArchivalRetention;
					tArchivalRetention = sInfo.tArchivalRetention;
					nArchivalPolicy = sInfo.nArchivalPolicy;
					bShowAsEvent = sInfo.bShowAsEvent;
					szArchivalFileName.ReleaseBuffer();
					szRetrievalFileName.ReleaseBuffer();
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCAutomaticStackAlertInfo(INT nPage, INT nDisplay, CONST CUIntArray &nTypes, CONST CStringArray &szAuditions, CONST CStringArray &szNotifications, CONST CDWordArray &nAcknowledgeColors, CONST CByteArray &bAcknowledgments)
{
	struct {
		INT  cbSize;
		INT  cbTypes;
		INT  cbAuditions;
		INT  cbNotifications;
		INT  cbAcknowledgeColors;
		INT  cbAcknowledgments;
	} sInfo;
	INT  nAudition;
	INT  nAuditions;
	INT  nNotification;
	INT  nNotifications;
	CByteArray  nInfo;
	CByteArray  nInfoData[2];

	sInfo.cbTypes = (INT)(nTypes.GetSize()*sizeof(UINT));
	sInfo.cbAcknowledgeColors = (INT)(nAcknowledgeColors.GetSize()*sizeof(DWORD));
	sInfo.cbAcknowledgments = (INT)(bAcknowledgments.GetSize()*sizeof(BYTE));
	for (nAudition = 0, nAuditions = (INT)szAuditions.GetSize(), sInfo.cbAuditions = 0; nAudition < nAuditions; nAudition++)
	{
		nInfoData[0].SetSize(sInfo.cbAuditions + (szAuditions.GetAt(nAudition).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nInfoData[0].GetData() + sInfo.cbAuditions, (LPCTSTR)szAuditions.GetAt(nAudition), (szAuditions.GetAt(nAudition).GetLength() + 1)*sizeof(TCHAR));
		sInfo.cbAuditions += (szAuditions.GetAt(nAudition).GetLength() + 1)*sizeof(TCHAR);
	}
	for (nNotification = 0, nNotifications = (INT)szNotifications.GetSize(), sInfo.cbNotifications = 0; nNotification < nNotifications; nNotification++)
	{
		nInfoData[1].SetSize(sInfo.cbNotifications + (szNotifications.GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nInfoData[1].GetData() + sInfo.cbNotifications, (LPCTSTR)szNotifications.GetAt(nNotification), (szNotifications.GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR));
		sInfo.cbNotifications += (szNotifications.GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR);
	}
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors + sInfo.cbAcknowledgments));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nTypes.GetData(), sInfo.cbTypes);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes, nInfoData[0].GetData(), sInfo.cbAuditions);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions, nInfoData[1].GetData(), sInfo.cbNotifications);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications, nAcknowledgeColors.GetData(), sInfo.cbAcknowledgeColors);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors, bAcknowledgments.GetData(), sInfo.cbAcknowledgments);
	return((nTypes.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKALERTSINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKALERTSINFO)));
}

BOOL CProfile::GetTCAutomaticStackAlertInfo(INT nPage, INT nDisplay, CUIntArray &nTypes, CStringArray &szAuditions, CStringArray &szNotifications, CDWordArray &nAcknowledgeColors, CByteArray &bAcknowledgments) CONST
{
	struct {
		INT  cbSize;
		INT  cbTypes;
		INT  cbAuditions;
		INT  cbNotifications;
		INT  cbAcknowledgeColors;
		INT  cbAcknowledgments;
	} sInfo;
	INT  nSize;
	INT  cbAudition;
	INT  cbAuditions;
	INT  cbNotification;
	INT  cbNotifications;
	DWORD  dwType;
	CByteArray  nInfo;
	CByteArray  nInfoData[2];

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKALERTSINFO)), nInfo.SetSize(max(nSize, 0)), nTypes.RemoveAll(), szAuditions.RemoveAll(), szNotifications.RemoveAll(), nAcknowledgeColors.RemoveAll(), bAcknowledgments.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKALERTSINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors + sInfo.cbAcknowledgments)
				{
					nTypes.SetSize(sInfo.cbTypes / sizeof(UINT));
					nInfoData[0].SetSize(sInfo.cbAuditions);
					nInfoData[1].SetSize(sInfo.cbNotifications);
					nAcknowledgeColors.SetSize(sInfo.cbAcknowledgeColors / sizeof(DWORD));
					bAcknowledgments.SetSize(sInfo.cbAcknowledgments / sizeof(BYTE));
					CopyMemory(nTypes.GetData(), nInfo.GetData() + sizeof(sInfo), sInfo.cbTypes);
					CopyMemory(nInfoData[0].GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes, sInfo.cbAuditions);
					CopyMemory(nInfoData[1].GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions, sInfo.cbNotifications);
					CopyMemory(nAcknowledgeColors.GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications, sInfo.cbAcknowledgeColors);
					CopyMemory(bAcknowledgments.GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors, sInfo.cbAcknowledgments);
					for (cbAuditions = 0; cbAuditions < sInfo.cbAuditions; cbAuditions += cbAudition)
					{
						szAuditions.Add((LPCTSTR)(nInfoData[0].GetData() + cbAuditions));
						cbAudition = (szAuditions.GetAt(szAuditions.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
					}
					for (cbNotifications = 0; cbNotifications < sInfo.cbNotifications; cbNotifications += cbNotification)
					{
						szNotifications.Add((LPCTSTR)(nInfoData[1].GetData() + cbNotifications));
						cbNotification = (szNotifications.GetAt(szNotifications.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
					}
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCAutomaticStackPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKPRINTINFO)));
}

BOOL CProfile::GetTCAutomaticStackPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCAUTOMATICSTACKPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCProceduresMonitorLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nListColumns, CONST CUIntArray &nListWidths, CONST SIZE &sizeList, CONST SIZE &sizeFlowchart, CONST SIZE &sizeCode, COLORREF nBackgroundColor, COLORREF nLabelsColor, BOOL bToolTips)
{
	struct {
		UINT  nSize;
		UINT  nListColumns;
		UINT  nListWidths;
		SIZE  sizeList;
		SIZE  sizeFlowchart;
		SIZE  sizeCode;
		COLORREF  nFlowchartColor[2];
		BOOL  bToolTips;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bToolTips = bToolTips;
	sInfo.sizeList = sizeList;
	sInfo.sizeCode = sizeCode;
	sInfo.sizeFlowchart = sizeFlowchart;
	sInfo.nListColumns = (UINT)nListColumns.GetSize();
	sInfo.nListWidths = (UINT)nListWidths.GetSize();
	sInfo.nFlowchartColor[0] = nBackgroundColor;
	sInfo.nFlowchartColor[1] = nLabelsColor;
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + (nListColumns.GetSize() + nListWidths.GetSize())*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nListColumns.GetData(), nListColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nListColumns.GetSize()*sizeof(UINT), nListWidths.GetData(), nListWidths.GetSize()*sizeof(UINT));
	return((nListColumns.GetSize() > 0 && nListWidths.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORLAYOUTINFO)));
}

BOOL CProfile::GetTCProceduresMonitorLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nListColumns, CUIntArray &nListWidths, CSize &sizeList, CSize &sizeFlowchart, CSize &sizeCode, COLORREF &nBackgroundColor, COLORREF &nLabelsColor, BOOL &bToolTips) CONST
{
	struct {
		UINT  nSize;
		UINT  nListColumns;
		UINT  nListWidths;
		SIZE  sizeList;
		SIZE  sizeFlowchart;
		SIZE  sizeCode;
		COLORREF  nFlowchartColor[2];
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + (sInfo.nListColumns + sInfo.nListWidths)*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nListColumns.SetSize(sInfo.nListColumns);
					CopyMemory(nListColumns.GetData(), nInfo.GetData(), nListColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nListColumns.GetSize()*sizeof(UINT));
					nListWidths.SetSize(sInfo.nListWidths);
					CopyMemory(nListWidths.GetData(), nInfo.GetData(), nListWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nListWidths.GetSize()*sizeof(UINT));
					sizeList = sInfo.sizeList;
					sizeCode = sInfo.sizeCode;
					sizeFlowchart = sInfo.sizeFlowchart;
					nBackgroundColor = sInfo.nFlowchartColor[0];
					nLabelsColor = sInfo.nFlowchartColor[1];
					bToolTips = sInfo.bToolTips;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCProceduresMonitorFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pListTitleFont, CONST LOGFONT *pListItemsFont, CONST LOGFONT *pFlowchartTitleFont, CONST LOGFONT *pFlowchartLabelsFont, CONST LOGFONT *pSourceCodeFont)
{
	LOGFONT  sFontsInfo[5];

	CopyMemory(&sFontsInfo[0], pListTitleFont, (AfxIsValidAddress(pListTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pListItemsFont, (AfxIsValidAddress(pListItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[2], pFlowchartTitleFont, (AfxIsValidAddress(pFlowchartTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[3], pFlowchartLabelsFont, (AfxIsValidAddress(pFlowchartLabelsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[4], pSourceCodeFont, (AfxIsValidAddress(pSourceCodeFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pListTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pListItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pFlowchartTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pFlowchartLabelsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pSourceCodeFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORFONTSINFO)));
}

BOOL CProfile::GetTCProceduresMonitorFontsInfo(INT nPage, INT nDisplay, LOGFONT *pListTitleFont, LOGFONT *pListItemsFont, LOGFONT *pFlowchartTitleFont, LOGFONT *pFlowchartLabelsFont, LOGFONT *pSourceCodeFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[5];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pListTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pListTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pListItemsFont, &sFontsInfo[1], (AfxIsValidAddress(pListItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pFlowchartTitleFont, &sFontsInfo[2], (AfxIsValidAddress(pFlowchartTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pFlowchartLabelsFont, &sFontsInfo[3], (AfxIsValidAddress(pFlowchartLabelsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pSourceCodeFont, &sFontsInfo[4], (AfxIsValidAddress(pSourceCodeFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCProceduresMonitorContentsInfo(INT nPage, INT nDisplay, CONST CByteArray &nContentsInfo, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingChecks, BOOL bTelecommandingReleaseWaitMode)
{
	struct {
		INT  cbSize;
		INT  cbContents;
		UINT  nTelecommandingMode;
		UINT  nTelecommandingState;
		UINT  nTelecommandingChecks;
		BOOL  bTelecommandingReleaseWaitMode;
	} sInfo;
	CByteArray  nInfo;

	sInfo.nTelecommandingMode = nTelecommandingMode;
	sInfo.nTelecommandingState = nTelecommandingState;
	sInfo.nTelecommandingChecks = nTelecommandingChecks;
	sInfo.bTelecommandingReleaseWaitMode = bTelecommandingReleaseWaitMode;
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + (sInfo.cbContents = (INT)nContentsInfo.GetSize())));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nContentsInfo.GetData(), sInfo.cbContents);
	return((nTelecommandingMode != (UINT)-1 && nTelecommandingState != (UINT)-1 && nTelecommandingChecks != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORCONTENTSINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORCONTENTSINFO)));
}

BOOL CProfile::GetTCProceduresMonitorContentsInfo(INT nPage, INT nDisplay, CByteArray &nContentsInfo, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingChecks, BOOL &bTelecommandingReleaseWaitMode) CONST
{
	struct {
		INT  cbSize;
		INT  cbContents;
		UINT  nTelecommandingMode;
		UINT  nTelecommandingState;
		UINT  nTelecommandingChecks;
		BOOL  bTelecommandingReleaseWaitMode;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORCONTENTSINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORCONTENTSINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbContents  &&  sInfo.cbSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nContentsInfo.SetSize(sInfo.cbContents);
					CopyMemory(nContentsInfo.GetData(), nInfo.GetData(), sInfo.cbContents);
					nInfo.RemoveAt(0, sInfo.cbContents);
					nTelecommandingMode = sInfo.nTelecommandingMode;
					nTelecommandingState = sInfo.nTelecommandingState;
					nTelecommandingChecks = sInfo.nTelecommandingChecks;
					bTelecommandingReleaseWaitMode = sInfo.bTelecommandingReleaseWaitMode;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCProceduresMonitorLoggingInfo(INT nPage, INT nDisplay, UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent)
{
	struct {
		INT  cbSize;
		INT  cbArchivalFileName;
		INT  cbRetrievalFileName;
		UINT  nArchivalPolicy;
		UINT  nRetrievalReloadCount;
		DWORDLONG  dwArchivalRetention;
		TIMEKEY  tArchivalRetention;
		BOOL  bShowAsEvent;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bShowAsEvent = bShowAsEvent;
	sInfo.nArchivalPolicy = nArchivalPolicy;
	sInfo.dwArchivalRetention = dwArchivalRetention;
	sInfo.nRetrievalReloadCount = nRetrievalReloadCount;
	sInfo.tArchivalRetention = tArchivalRetention.GetTotalSeconds();
	sInfo.cbArchivalFileName = (AfxIsValidString(pszArchivalFileName)) ? ((lstrlen(pszArchivalFileName) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbRetrievalFileName = (AfxIsValidString(pszRetrievalFileName)) ? ((lstrlen(pszRetrievalFileName) + 1)*sizeof(TCHAR)) : 0;
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbArchivalFileName + sInfo.cbRetrievalFileName));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), pszArchivalFileName, sInfo.cbArchivalFileName);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbArchivalFileName, pszRetrievalFileName, sInfo.cbRetrievalFileName);
	return((AfxIsValidString(pszArchivalFileName) && AfxIsValidString(pszRetrievalFileName)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORLOGGINGINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORLOGGINGINFO)));
}

BOOL CProfile::GetTCProceduresMonitorLoggingInfo(INT nPage, INT nDisplay, UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST
{
	struct {
		INT  cbSize;
		INT  cbArchivalFileName;
		INT  cbRetrievalFileName;
		UINT  nArchivalPolicy;
		UINT  nRetrievalReloadCount;
		DWORDLONG  dwArchivalRetention;
		TIMEKEY  tArchivalRetention;
		BOOL  bShowAsEvent;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORLOGGINGINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORLOGGINGINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbArchivalFileName + sInfo.cbRetrievalFileName)
				{
					CopyMemory(szArchivalFileName.GetBufferSetLength(STRINGCHARS(sInfo.cbArchivalFileName)), nInfo.GetData() + sizeof(sInfo), STRINGBYTES(sInfo.cbArchivalFileName));
					CopyMemory(szRetrievalFileName.GetBufferSetLength(STRINGCHARS(sInfo.cbRetrievalFileName)), nInfo.GetData() + sizeof(sInfo) + sInfo.cbArchivalFileName, STRINGBYTES(sInfo.cbRetrievalFileName));
					nRetrievalReloadCount = sInfo.nRetrievalReloadCount;
					dwArchivalRetention = sInfo.dwArchivalRetention;
					tArchivalRetention = sInfo.tArchivalRetention;
					nArchivalPolicy = sInfo.nArchivalPolicy;
					bShowAsEvent = sInfo.bShowAsEvent;
					szArchivalFileName.ReleaseBuffer();
					szRetrievalFileName.ReleaseBuffer();
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCProceduresMonitorPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORPRINTINFO)));
}

BOOL CProfile::GetTCProceduresMonitorPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDURESMONITORPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCOnBoardBufferQueuesLayoutInfo(INT nPage, INT nDisplay, CONST CStringArray &szBuffers, CONST CUIntArray &nSummaryColumns, CONST CUIntArray &nSummaryWidths, CONST SIZE &sizeSummaryList, CONST CUIntArray &nDetailsColumns, CONST CUIntArray &nDetailsWidths, CONST SIZE &sizeDetailsList, CONST CDWordArray &dwDetailsGridBackgroundColors, BOOL bToolTips)
{
	struct {
		INT  cbSize;
		INT  cbBuffers;
		UINT  nSummaryColumns;
		UINT  nSummaryWidths;
		UINT  nDetailsColumns;
		UINT  nDetailsWidths;
		UINT  nDetailsColors;
		SIZE  sizeSummaryList;
		SIZE  sizeDetailsList;
		BOOL  bToolTips;
	} sInfo;
	INT  nBuffer;
	INT  nBuffers;
	CByteArray  nInfo;
	CByteArray  nBuffersData;

	sInfo.bToolTips = bToolTips;
	sInfo.sizeSummaryList = sizeSummaryList;
	sInfo.sizeDetailsList = sizeDetailsList;
	sInfo.nSummaryColumns = (UINT)nSummaryColumns.GetSize();
	sInfo.nSummaryWidths = (UINT)nSummaryWidths.GetSize();
	sInfo.nDetailsColumns = (UINT)nDetailsColumns.GetSize();
	sInfo.nDetailsWidths = (UINT)nDetailsWidths.GetSize();
	sInfo.nDetailsColors = (UINT)dwDetailsGridBackgroundColors.GetSize();
	for (nBuffer = 0, nBuffers = (INT)szBuffers.GetSize(), sInfo.cbBuffers = 0; nBuffer < nBuffers; nBuffer++)
	{
		nBuffersData.SetSize(sInfo.cbBuffers + (szBuffers.GetAt(nBuffer).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nBuffersData.GetData() + sInfo.cbBuffers, (LPCTSTR)szBuffers.GetAt(nBuffer), (szBuffers.GetAt(nBuffer).GetLength() + 1)*sizeof(TCHAR));
		sInfo.cbBuffers += (szBuffers.GetAt(nBuffer).GetLength() + 1)*sizeof(TCHAR);
	}
	nInfo.SetSize((sInfo.cbSize = (INT)(sizeof(sInfo) + sInfo.cbBuffers + (nSummaryColumns.GetSize() + nSummaryWidths.GetSize() + nDetailsColumns.GetSize() + nDetailsWidths.GetSize())*sizeof(UINT) + dwDetailsGridBackgroundColors.GetSize()*sizeof(DWORD))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nBuffersData.GetData(), sInfo.cbBuffers);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbBuffers, nSummaryColumns.GetData(), nSummaryColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbBuffers + nSummaryColumns.GetSize()*sizeof(UINT), nSummaryWidths.GetData(), nSummaryWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbBuffers + (nSummaryColumns.GetSize() + nSummaryWidths.GetSize())*sizeof(UINT), nDetailsColumns.GetData(), nDetailsColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbBuffers + (nSummaryColumns.GetSize() + nSummaryWidths.GetSize() + nDetailsColumns.GetSize())*sizeof(UINT), nDetailsWidths.GetData(), nDetailsWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbBuffers + (nSummaryColumns.GetSize() + nSummaryWidths.GetSize() + nDetailsColumns.GetSize() + nDetailsWidths.GetSize())*sizeof(UINT), dwDetailsGridBackgroundColors.GetData(), dwDetailsGridBackgroundColors.GetSize()*sizeof(DWORD));
	return((nSummaryColumns.GetSize() > 0 && nSummaryWidths.GetSize() > 0 && nDetailsColumns.GetSize() > 0 && nDetailsWidths.GetSize() > 0 && dwDetailsGridBackgroundColors.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESLAYOUTINFO)));
}

BOOL CProfile::GetTCOnBoardBufferQueuesLayoutInfo(INT nPage, INT nDisplay, CStringArray &szBuffers, CUIntArray &nSummaryColumns, CUIntArray &nSummaryWidths, CSize &sizeSummaryList, CUIntArray &nDetailsColumns, CUIntArray &nDetailsWidths, CSize &sizeDetailsList, CDWordArray &dwDetailsGridBackgroundColors, BOOL &bToolTips) CONST
{
	struct {
		INT  cbSize;
		INT  cbBuffers;
		UINT  nSummaryColumns;
		UINT  nSummaryWidths;
		UINT  nDetailsColumns;
		UINT  nDetailsWidths;
		UINT  nDetailsColors;
		SIZE  sizeSummaryList;
		SIZE  sizeDetailsList;
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	INT  cbBuffer;
	INT  cbBuffers;
	DWORD  dwType;
	CByteArray  nInfo;
	CByteArray  nBuffersData;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbBuffers + (sInfo.nSummaryColumns + sInfo.nSummaryWidths + sInfo.nDetailsColumns + sInfo.nDetailsWidths)*sizeof(UINT) + sInfo.nDetailsColors*sizeof(DWORD) && sInfo.cbSize == nInfo.GetSize())
				{
					for (nInfo.RemoveAt(0, sizeof(sInfo)), nBuffersData.SetSize(sInfo.cbBuffers), CopyMemory(nBuffersData.GetData(), nInfo.GetData(), nBuffersData.GetSize()), nInfo.RemoveAt(0, nBuffersData.GetSize()), szBuffers.RemoveAll(), cbBuffers = 0; cbBuffers < nBuffersData.GetSize(); cbBuffers += cbBuffer)
					{
						szBuffers.Add((LPCTSTR)(nBuffersData.GetData() + cbBuffers));
						cbBuffer = (szBuffers.GetAt(szBuffers.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
					}
					nSummaryColumns.SetSize(sInfo.nSummaryColumns);
					CopyMemory(nSummaryColumns.GetData(), nInfo.GetData(), nSummaryColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nSummaryColumns.GetSize()*sizeof(UINT));
					nSummaryWidths.SetSize(sInfo.nSummaryWidths);
					CopyMemory(nSummaryWidths.GetData(), nInfo.GetData(), nSummaryWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nSummaryWidths.GetSize()*sizeof(UINT));
					nDetailsColumns.SetSize(sInfo.nDetailsColumns);
					CopyMemory(nDetailsColumns.GetData(), nInfo.GetData(), nDetailsColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nDetailsColumns.GetSize()*sizeof(UINT));
					nDetailsWidths.SetSize(sInfo.nDetailsWidths);
					CopyMemory(nDetailsWidths.GetData(), nInfo.GetData(), nDetailsWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nDetailsWidths.GetSize()*sizeof(UINT));
					dwDetailsGridBackgroundColors.SetSize(sInfo.nDetailsColors);
					CopyMemory(dwDetailsGridBackgroundColors.GetData(), nInfo.GetData(), dwDetailsGridBackgroundColors.GetSize()*sizeof(DWORD));
					nInfo.RemoveAt(0, dwDetailsGridBackgroundColors.GetSize()*sizeof(DWORD));
					sizeSummaryList = sInfo.sizeSummaryList;
					sizeDetailsList = sInfo.sizeDetailsList;
					bToolTips = sInfo.bToolTips;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCOnBoardBufferQueuesFontsInfo(INT nPage, INT nDisplay, CONST CByteArray &nFontsInfo)
{
	return((nFontsInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESFONTSINFO), REG_BINARY, nFontsInfo.GetData(), (INT)nFontsInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESFONTSINFO)));
}

BOOL CProfile::GetTCOnBoardBufferQueuesFontsInfo(INT nPage, INT nDisplay, CByteArray &nFontsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESFONTSINFO)), nFontsInfo.SetSize(max(nSize, 0)); nSize > 0 && nFontsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESFONTSINFO), &dwType, nFontsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCOnBoardBufferQueuesPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESPRINTINFO)));
}

BOOL CProfile::GetTCOnBoardBufferQueuesPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDBUFFERQUEUESPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCOnBoardMemoryImagesLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nSummaryColumns, CONST CUIntArray &nSummaryWidths, CONST SIZE &sizeSummaryList, CONST CUIntArray &nDetailsColumns, CONST CUIntArray &nDetailsWidths, CONST SIZE &sizeDetailsList, BOOL bToolTips)
{
	struct {
		INT  cbSize;
		UINT  nSummaryColumns;
		UINT  nSummaryWidths;
		UINT  nDetailsColumns;
		UINT  nDetailsWidths;
		SIZE  sizeSummaryList;
		SIZE  sizeDetailsList;
		BOOL  bToolTips;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bToolTips = bToolTips;
	sInfo.sizeSummaryList = sizeSummaryList;
	sInfo.sizeDetailsList = sizeDetailsList;
	sInfo.nSummaryColumns = (UINT)nSummaryColumns.GetSize();
	sInfo.nSummaryWidths = (UINT)nSummaryWidths.GetSize();
	sInfo.nDetailsColumns = (UINT)nDetailsColumns.GetSize();
	sInfo.nDetailsWidths = (UINT)nDetailsWidths.GetSize();
	nInfo.SetSize((sInfo.cbSize = (INT)(sizeof(sInfo) + (nSummaryColumns.GetSize() + nSummaryWidths.GetSize() + nDetailsColumns.GetSize() + nDetailsWidths.GetSize())*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nSummaryColumns.GetData(), nSummaryColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nSummaryColumns.GetSize()*sizeof(UINT), nSummaryWidths.GetData(), nSummaryWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + (nSummaryColumns.GetSize() + nSummaryWidths.GetSize())*sizeof(UINT), nDetailsColumns.GetData(), nDetailsColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + (nSummaryColumns.GetSize() + nSummaryWidths.GetSize() + nDetailsColumns.GetSize())*sizeof(UINT), nDetailsWidths.GetData(), nDetailsWidths.GetSize()*sizeof(UINT));
	return((nSummaryColumns.GetSize() > 0 && nSummaryWidths.GetSize() > 0 && nDetailsColumns.GetSize() >= 0 && nDetailsWidths.GetSize() >= 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESLAYOUTINFO)));
}

BOOL CProfile::GetTCOnBoardMemoryImagesLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nSummaryColumns, CUIntArray &nSummaryWidths, CSize &sizeSummaryList, CUIntArray &nDetailsColumns, CUIntArray &nDetailsWidths, CSize &sizeDetailsList, BOOL &bToolTips) CONST
{
	struct {
		INT  cbSize;
		UINT  nSummaryColumns;
		UINT  nSummaryWidths;
		UINT  nDetailsColumns;
		UINT  nDetailsWidths;
		SIZE  sizeSummaryList;
		SIZE  sizeDetailsList;
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + (sInfo.nSummaryColumns + sInfo.nSummaryWidths + sInfo.nDetailsColumns + sInfo.nDetailsWidths)*sizeof(UINT) && sInfo.cbSize == nInfo.GetSize())
				{
					nSummaryColumns.SetSize(sInfo.nSummaryColumns);
					CopyMemory(nSummaryColumns.GetData(), nInfo.GetData(), nSummaryColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nSummaryColumns.GetSize()*sizeof(UINT));
					nSummaryWidths.SetSize(sInfo.nSummaryWidths);
					CopyMemory(nSummaryWidths.GetData(), nInfo.GetData(), nSummaryWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nSummaryWidths.GetSize()*sizeof(UINT));
					nDetailsColumns.SetSize(sInfo.nDetailsColumns);
					CopyMemory(nDetailsColumns.GetData(), nInfo.GetData(), nDetailsColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nDetailsColumns.GetSize()*sizeof(UINT));
					nDetailsWidths.SetSize(sInfo.nDetailsWidths);
					CopyMemory(nDetailsWidths.GetData(), nInfo.GetData(), nDetailsWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nDetailsWidths.GetSize()*sizeof(UINT));
					sizeSummaryList = sInfo.sizeSummaryList;
					sizeDetailsList = sInfo.sizeDetailsList;
					bToolTips = sInfo.bToolTips;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCOnBoardMemoryImagesFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pSummaryTitleFont, CONST LOGFONT *pSummaryItemsFont, CONST LOGFONT *pDetailsTitleFont, CONST LOGFONT *pDetailsItemsFont)
{
	LOGFONT  sFontsInfo[4];

	CopyMemory(&sFontsInfo[0], pSummaryTitleFont, (AfxIsValidAddress(pSummaryTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pSummaryItemsFont, (AfxIsValidAddress(pSummaryItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[2], pDetailsTitleFont, (AfxIsValidAddress(pDetailsTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[3], pDetailsItemsFont, (AfxIsValidAddress(pDetailsItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pSummaryTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pSummaryItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDetailsTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pDetailsItemsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESFONTSINFO)));
}

BOOL CProfile::GetTCOnBoardMemoryImagesFontsInfo(INT nPage, INT nDisplay, LOGFONT *pSummaryTitleFont, LOGFONT *pSummaryItemsFont, LOGFONT *pDetailsTitleFont, LOGFONT *pDetailsItemsFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[4];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pSummaryTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pSummaryTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pSummaryItemsFont, &sFontsInfo[1], (AfxIsValidAddress(pSummaryItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDetailsTitleFont, &sFontsInfo[2], (AfxIsValidAddress(pDetailsTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pDetailsItemsFont, &sFontsInfo[3], (AfxIsValidAddress(pDetailsItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCOnBoardMemoryImagesTablesInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, COLORREF nTitleFontColor, COLORREF nItemsFontColor, COLORREF nTitleBackgroundColor, COLORREF nItemsBackgroundColor)
{
	struct {
		LOGFONT  sTitleFont;
		LOGFONT  sItemsFont;
		COLORREF  nFontColors[2];
		COLORREF  nBackgroundColors[2];
	} sInfo;

	sInfo.nFontColors[0] = nTitleFontColor;
	sInfo.nFontColors[1] = nItemsFontColor;
	sInfo.nBackgroundColors[0] = nTitleBackgroundColor;
	sInfo.nBackgroundColors[1] = nItemsBackgroundColor;
	CopyMemory(&sInfo.sTitleFont, pTitleFont, (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sInfo.sItemsFont, pItemsFont, (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESTABLESINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESTABLESINFO)));
}

BOOL CProfile::GetTCOnBoardMemoryImagesTablesInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pItemsFont, COLORREF &nTitleFontColor, COLORREF &nItemsFontColor, COLORREF &nTitleBackgroundColor, COLORREF &nItemsBackgroundColor) CONST
{
	struct {
		LOGFONT  sTitleFont;
		LOGFONT  sItemsFont;
		COLORREF  nFontColors[2];
		COLORREF  nBackgroundColors[2];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESTABLESINFO), &dwType, (BYTE *)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(pTitleFont, &sInfo.sTitleFont, sizeof(LOGFONT));
		CopyMemory(pItemsFont, &sInfo.sItemsFont, sizeof(LOGFONT));
		nTitleBackgroundColor = sInfo.nBackgroundColors[0];
		nItemsBackgroundColor = sInfo.nBackgroundColors[1];
		nTitleFontColor = sInfo.nFontColors[0];
		nItemsFontColor = sInfo.nFontColors[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCOnBoardMemoryImagesContentsInfo(INT nPage, INT nDisplay, CONST CByteArray &nContentsInfo, CONST CTimeSpan tDBMSDelay, BOOL bDBMSFlush, BOOL bDBMSFile)
{
	struct {
		INT  cbSize;
		INT  cbContents;
		TIMEKEY  tDBMSDelay;
		BOOL  bDBMSFlush[2];
	} sInfo;
	CByteArray  nInfo;

	sInfo.bDBMSFlush[0] = bDBMSFlush;
	sInfo.bDBMSFlush[1] = bDBMSFile;
	sInfo.tDBMSDelay = tDBMSDelay.GetTotalSeconds();
	sInfo.cbContents = (INT)(nContentsInfo.GetSize()*sizeof(BYTE));
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbContents));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nContentsInfo.GetData(), sInfo.cbContents);
	return((nContentsInfo.GetSize() > 0 || tDBMSDelay > 0 || bDBMSFlush || bDBMSFile) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESCONTENTSINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESCONTENTSINFO)));
}

BOOL CProfile::GetTCOnBoardMemoryImagesContentsInfo(INT nPage, INT nDisplay, CByteArray &nContentsInfo, CTimeSpan &tDBMSDelay, BOOL &bDBMSFlush, BOOL &bDBMSFile) CONST
{
	struct {
		INT  cbSize;
		INT  cbContents;
		TIMEKEY  tDBMSDelay;
		BOOL  bDBMSFlush[2];
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESCONTENTSINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESCONTENTSINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbContents)
				{
					nContentsInfo.SetSize(sInfo.cbContents);
					CopyMemory(nContentsInfo.GetData(), nInfo.GetData() + sizeof(sInfo), sInfo.cbContents);
					bDBMSFlush = sInfo.bDBMSFlush[0];
					bDBMSFile = sInfo.bDBMSFlush[1];
					tDBMSDelay = sInfo.tDBMSDelay;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCOnBoardMemoryImagesLoggingInfo(INT nPage, INT nDisplay, UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent)
{
	struct {
		INT  cbSize;
		INT  cbArchivalFileName;
		INT  cbRetrievalFileName;
		UINT  nArchivalPolicy;
		UINT  nRetrievalReloadCount;
		DWORDLONG  dwArchivalRetention;
		TIMEKEY  tArchivalRetention;
		BOOL  bShowAsEvent;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bShowAsEvent = bShowAsEvent;
	sInfo.nArchivalPolicy = nArchivalPolicy;
	sInfo.dwArchivalRetention = dwArchivalRetention;
	sInfo.nRetrievalReloadCount = nRetrievalReloadCount;
	sInfo.tArchivalRetention = tArchivalRetention.GetTotalSeconds();
	sInfo.cbArchivalFileName = (AfxIsValidString(pszArchivalFileName)) ? ((lstrlen(pszArchivalFileName) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbRetrievalFileName = (AfxIsValidString(pszRetrievalFileName)) ? ((lstrlen(pszRetrievalFileName) + 1)*sizeof(TCHAR)) : 0;
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbArchivalFileName + sInfo.cbRetrievalFileName));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), pszArchivalFileName, sInfo.cbArchivalFileName);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbArchivalFileName, pszRetrievalFileName, sInfo.cbRetrievalFileName);
	return((AfxIsValidString(pszArchivalFileName) && AfxIsValidString(pszRetrievalFileName)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESLOGGINGINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESLOGGINGINFO)));
}

BOOL CProfile::GetTCOnBoardMemoryImagesLoggingInfo(INT nPage, INT nDisplay, UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST
{
	struct {
		INT  cbSize;
		INT  cbArchivalFileName;
		INT  cbRetrievalFileName;
		UINT  nArchivalPolicy;
		UINT  nRetrievalReloadCount;
		DWORDLONG  dwArchivalRetention;
		TIMEKEY  tArchivalRetention;
		BOOL  bShowAsEvent;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESLOGGINGINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESLOGGINGINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbArchivalFileName + sInfo.cbRetrievalFileName)
				{
					CopyMemory(szArchivalFileName.GetBufferSetLength(STRINGCHARS(sInfo.cbArchivalFileName)), nInfo.GetData() + sizeof(sInfo), STRINGBYTES(sInfo.cbArchivalFileName));
					CopyMemory(szRetrievalFileName.GetBufferSetLength(STRINGCHARS(sInfo.cbRetrievalFileName)), nInfo.GetData() + sizeof(sInfo) + sInfo.cbArchivalFileName, STRINGBYTES(sInfo.cbRetrievalFileName));
					nRetrievalReloadCount = sInfo.nRetrievalReloadCount;
					dwArchivalRetention = sInfo.dwArchivalRetention;
					tArchivalRetention = sInfo.tArchivalRetention;
					nArchivalPolicy = sInfo.nArchivalPolicy;
					bShowAsEvent = sInfo.bShowAsEvent;
					szArchivalFileName.ReleaseBuffer();
					szRetrievalFileName.ReleaseBuffer();
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCOnBoardMemoryImagesPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESPRINTINFO)));
}

BOOL CProfile::GetTCOnBoardMemoryImagesPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCONBOARDMEMORYIMAGESPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCDiagnosticsOversamplingDumpLayoutInfo(INT nPage, INT nDisplay, CONST CByteArray &nLayoutData, CONST CUIntArray &nParametersColumns, CONST CUIntArray &nParametersWidths, CONST SIZE &sizeParameters, CONST CUIntArray &nRawDataColumns, CONST CUIntArray &nRawDataWidths, CONST SIZE &sizeRawData, COLORREF nNumbersBackgroundColor, COLORREF nValuesBackgroundColor, UINT nSampleLimit, BOOL bInvalidData, BOOL bBadData, BOOL bToolTips)
{
	struct {
		UINT  nSize;
		UINT  nLayoutData;
		UINT  nParametersColumns;
		UINT  nParametersWidths;
		UINT  nRawDataColumns;
		UINT  nRawDataWidths;
		UINT  nValueSampleLimit;
		SIZE  sizeParameters;
		SIZE  sizeRawData;
		COLORREF  nBackgroundColor[2];
		BOOL  bInvalidData;
		BOOL  bBadData;
		BOOL  bToolTips;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bBadData = bBadData;
	sInfo.bToolTips = bToolTips;
	sInfo.bInvalidData = bInvalidData;
	sInfo.nValueSampleLimit = nSampleLimit;
	sInfo.sizeRawData = sizeRawData;
	sInfo.sizeParameters = sizeParameters;
	sInfo.nLayoutData = (UINT)nLayoutData.GetSize();
	sInfo.nParametersColumns = (UINT)nParametersColumns.GetSize();
	sInfo.nParametersWidths = (UINT)nParametersWidths.GetSize();
	sInfo.nRawDataColumns = (UINT)nRawDataColumns.GetSize();
	sInfo.nRawDataWidths = (UINT)nRawDataWidths.GetSize();
	sInfo.nBackgroundColor[0] = nNumbersBackgroundColor;
	sInfo.nBackgroundColor[1] = nValuesBackgroundColor;
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + nLayoutData.GetSize()*sizeof(BYTE) + (nParametersColumns.GetSize() + nParametersWidths.GetSize() + nRawDataColumns.GetSize() + nRawDataWidths.GetSize())*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nLayoutData.GetData(), nLayoutData.GetSize()*sizeof(BYTE));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nLayoutData.GetSize()*sizeof(BYTE), nParametersColumns.GetData(), nParametersColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nLayoutData.GetSize()*sizeof(BYTE) + nParametersColumns.GetSize()*sizeof(UINT), nParametersWidths.GetData(), nParametersWidths.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nLayoutData.GetSize()*sizeof(BYTE) + (nParametersColumns.GetSize() + nParametersWidths.GetSize())*sizeof(UINT), nRawDataColumns.GetData(), nRawDataColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nLayoutData.GetSize()*sizeof(BYTE) + (nParametersColumns.GetSize() + nParametersWidths.GetSize() + nRawDataColumns.GetSize())*sizeof(UINT), nRawDataWidths.GetData(), nRawDataWidths.GetSize()*sizeof(UINT));
	return((nLayoutData.GetSize() > 0 && nParametersColumns.GetSize() > 0 && nParametersWidths.GetSize() > 0 && nRawDataColumns.GetSize() > 0 && nRawDataWidths.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUTINFO)));
}

BOOL CProfile::GetTCDiagnosticsOversamplingDumpLayoutInfo(INT nPage, INT nDisplay, CByteArray &nLayoutData, CUIntArray &nParametersColumns, CUIntArray &nParametersWidths, CSize &sizeParameters, CUIntArray &nRawDataColumns, CUIntArray &nRawDataWidths, CSize &sizeRawData, COLORREF &nNumbersBackgroundColor, COLORREF &nValuesBackgroundColor, UINT &nSampleLimit, BOOL &bInvalidData, BOOL &bBadData, BOOL &bToolTips) CONST
{
	struct {
		UINT  nSize;
		UINT  nLayoutData;
		UINT  nParametersColumns;
		UINT  nParametersWidths;
		UINT  nRawDataColumns;
		UINT  nRawDataWidths;
		UINT  nValueSampleLimit;
		SIZE  sizeParameters;
		SIZE  sizeRawData;
		COLORREF  nBackgroundColor[2];
		BOOL  bInvalidData;
		BOOL  bBadData;
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + sInfo.nLayoutData*sizeof(BYTE) + (sInfo.nParametersColumns + sInfo.nParametersWidths + sInfo.nRawDataColumns + sInfo.nRawDataWidths)*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nLayoutData.SetSize(sInfo.nLayoutData*sizeof(BYTE));
					CopyMemory(nLayoutData.GetData(), nInfo.GetData(), nLayoutData.GetSize()*sizeof(BYTE));
					nInfo.RemoveAt(0, nLayoutData.GetSize()*sizeof(BYTE));
					nParametersColumns.SetSize(sInfo.nParametersColumns);
					CopyMemory(nParametersColumns.GetData(), nInfo.GetData(), nParametersColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nParametersColumns.GetSize()*sizeof(UINT));
					nParametersWidths.SetSize(sInfo.nParametersWidths);
					CopyMemory(nParametersWidths.GetData(), nInfo.GetData(), nParametersWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nParametersWidths.GetSize()*sizeof(UINT));
					nRawDataColumns.SetSize(sInfo.nRawDataColumns);
					CopyMemory(nRawDataColumns.GetData(), nInfo.GetData(), nRawDataColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nRawDataColumns.GetSize()*sizeof(UINT));
					nRawDataWidths.SetSize(sInfo.nRawDataWidths);
					CopyMemory(nRawDataWidths.GetData(), nInfo.GetData(), nRawDataWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, nRawDataWidths.GetSize()*sizeof(UINT));
					sizeParameters = sInfo.sizeParameters;
					sizeRawData = sInfo.sizeRawData;
					nNumbersBackgroundColor = sInfo.nBackgroundColor[0];
					nValuesBackgroundColor = sInfo.nBackgroundColor[1];
					nSampleLimit = sInfo.nValueSampleLimit;
					bInvalidData = sInfo.bInvalidData;
					bBadData = sInfo.bBadData;
					bToolTips = sInfo.bToolTips;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCDiagnosticsOversamplingDumpFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pParametersTitleFont, CONST LOGFONT *pParametersItemsFont, CONST LOGFONT *pParametersValuesFont, CONST LOGFONT *pRawDataTitleFont, CONST LOGFONT *pRawDataItemsFont)
{
	LOGFONT  sFontsInfo[5];

	CopyMemory(&sFontsInfo[0], pParametersTitleFont, (AfxIsValidAddress(pParametersTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pParametersItemsFont, (AfxIsValidAddress(pParametersItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[2], pParametersValuesFont, (AfxIsValidAddress(pParametersValuesFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[3], pRawDataTitleFont, (AfxIsValidAddress(pRawDataTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[4], pRawDataItemsFont, (AfxIsValidAddress(pRawDataItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pParametersTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pParametersItemsFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pParametersValuesFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pRawDataTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pRawDataItemsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPFONTSINFO)));
}

BOOL CProfile::GetTCDiagnosticsOversamplingDumpFontsInfo(INT nPage, INT nDisplay, LOGFONT *pParametersTitleFont, LOGFONT *pParametersItemsFont, LOGFONT *pParametersValuesFont, LOGFONT *pRawDataTitleFont, LOGFONT *pRawDataItemsFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[5];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pParametersTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pParametersTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pParametersItemsFont, &sFontsInfo[1], (AfxIsValidAddress(pParametersItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pParametersValuesFont, &sFontsInfo[2], (AfxIsValidAddress(pParametersValuesFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pRawDataTitleFont, &sFontsInfo[3], (AfxIsValidAddress(pRawDataTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pRawDataItemsFont, &sFontsInfo[4], (AfxIsValidAddress(pRawDataItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCDiagnosticsOversamplingDumpModeInfo(INT nPage, INT nDisplay, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nMode = nMode;
	sInfo.nSpeed = nSpeed;
	sInfo.tInterval = tInterval.GetTotalSeconds();
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPMODEINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPMODEINFO)));
}

BOOL CProfile::GetTCDiagnosticsOversamplingDumpModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tInterval;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPMODEINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		nMode = sInfo.nMode;
		nSpeed = sInfo.nSpeed;
		tInterval = sInfo.tInterval;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCDiagnosticsOversamplingDumpPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPPRINTINFO)));
}

BOOL CProfile::GetTCDiagnosticsOversamplingDumpPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCDiagnosticsOversamplingDumpRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEFILENAME), pszFileName);
}

BOOL CProfile::GetTCDiagnosticsOversamplingDumpRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCDIAGNOSTICSOVERSAMPLINGDUMPRETRIEVEFILENAME), szFileName);
}

BOOL CProfile::SetTCHistoryLayoutName(INT nPage, INT nDisplay, LPCTSTR pszName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYLAYOUTNAME), pszName);
}

BOOL CProfile::GetTCHistoryLayoutName(INT nPage, INT nDisplay, CString &szName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYLAYOUTNAME), szName);
}

BOOL CProfile::SetTCHistoryLayoutInfo(INT nPage, INT nDisplay, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, COLORREF nGridBackgroundColor, BOOL bToolTips)
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
		COLORREF  nColor;
		BOOL  bToolTips;
	} sInfo;
	CByteArray  nInfo;

	sInfo.bToolTips = bToolTips;
	sInfo.nColumns = (UINT)nColumns.GetSize();
	sInfo.nWidths = (UINT)nWidths.GetSize();
	sInfo.nColor = nGridBackgroundColor;
	nInfo.SetSize((sInfo.nSize = (UINT)(sizeof(sInfo) + (nColumns.GetSize() + nWidths.GetSize())*sizeof(UINT))));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nColumns.GetData(), nColumns.GetSize()*sizeof(UINT));
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + nColumns.GetSize()*sizeof(UINT), nWidths.GetData(), nWidths.GetSize()*sizeof(UINT));
	return((nColumns.GetSize() > 0 && nWidths.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYLAYOUTINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYLAYOUTINFO)));
}

BOOL CProfile::GetTCHistoryLayoutInfo(INT nPage, INT nDisplay, CUIntArray &nColumns, CUIntArray &nWidths, COLORREF &nGridBackgroundColor, BOOL &bToolTips) CONST
{
	struct {
		UINT  nSize;
		UINT  nColumns;
		UINT  nWidths;
		COLORREF  nColor;
		BOOL  bToolTips;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYLAYOUTINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYLAYOUTINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.nSize == sizeof(sInfo) + (sInfo.nColumns + sInfo.nWidths)*sizeof(UINT) && sInfo.nSize == nInfo.GetSize())
				{
					nInfo.RemoveAt(0, sizeof(sInfo));
					nColumns.SetSize(sInfo.nColumns);
					CopyMemory(nColumns.GetData(), nInfo.GetData(), nColumns.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nColumns*sizeof(UINT));
					nWidths.SetSize(sInfo.nWidths);
					CopyMemory(nWidths.GetData(), nInfo.GetData(), nWidths.GetSize()*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nWidths*sizeof(UINT));
					nGridBackgroundColor = sInfo.nColor;
					bToolTips = sInfo.bToolTips;
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCHistoryFontsInfo(INT nPage, INT nDisplay, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont)
{
	LOGFONT  sFontsInfo[2];

	CopyMemory(&sFontsInfo[0], pTitleFont, (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sFontsInfo[1], pItemsFont, (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(pTitleFont, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(pItemsFont, sizeof(LOGFONT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYFONTSINFO), REG_BINARY, (CONST BYTE *) sFontsInfo, sizeof(sFontsInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYFONTSINFO)));
}

BOOL CProfile::GetTCHistoryFontsInfo(INT nPage, INT nDisplay, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST
{
	DWORD  dwType;
	LOGFONT  sFontsInfo[2];

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYFONTSINFO), &dwType, (BYTE *)sFontsInfo, sizeof(sFontsInfo)) == sizeof(sFontsInfo))
	{
		CopyMemory(pTitleFont, &sFontsInfo[0], (AfxIsValidAddress(pTitleFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		CopyMemory(pItemsFont, &sFontsInfo[1], (AfxIsValidAddress(pItemsFont, sizeof(LOGFONT))) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCHistoryFilterInfo(INT nPage, INT nDisplay, UINT nMode, LPCTSTR pszComputer, LPCTSTR pszName, LPCTSTR pszSequence, UINT nLimitation, UINT nAutoload, UINT nSortMode)
{
	struct {
		INT  cbSize;
		INT  cbComputer;
		INT  cbTelecommand[2];
		UINT  nMode[2];
		UINT  nLimitation;
		UINT  nAutoload;
	} sInfo;
	CByteArray  nInfo;

	sInfo.nMode[0] = nMode;
	sInfo.nMode[1] = nSortMode;
	sInfo.nAutoload = nAutoload;
	sInfo.nLimitation = nLimitation;
	sInfo.cbComputer = (AfxIsValidString(pszComputer)) ? ((lstrlen(pszComputer) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbTelecommand[0] = (AfxIsValidString(pszName)) ? ((lstrlen(pszName) + 1)*sizeof(TCHAR)) : 0;
	sInfo.cbTelecommand[1] = (AfxIsValidString(pszSequence)) ? ((lstrlen(pszSequence) + 1)*sizeof(TCHAR)) : 0;
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbComputer + sInfo.cbTelecommand[0] + sInfo.cbTelecommand[1]));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), pszComputer, sInfo.cbComputer);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbComputer, pszName, sInfo.cbTelecommand[0]);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbComputer + sInfo.cbTelecommand[0], pszSequence, sInfo.cbTelecommand[1]);
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYFILTERINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYFILTERINFO)));
}

BOOL CProfile::GetTCHistoryFilterInfo(INT nPage, INT nDisplay, UINT &nMode, CString &szComputer, CString &szName, CString &szSequence, UINT &nLimitation, UINT &nAutoload, UINT &nSortMode) CONST
{
	struct {
		INT  cbSize;
		INT  cbComputer;
		INT  cbTelecommand[2];
		UINT  nMode[2];
		UINT  nLimitation;
		UINT  nAutoload;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nInfo;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYFILTERINFO)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYFILTERINFO), &dwType, (BYTE *)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbComputer + sInfo.cbTelecommand[0] + sInfo.cbTelecommand[1])
				{
					CopyMemory(szComputer.GetBufferSetLength(STRINGCHARS(sInfo.cbComputer)), nInfo.GetData() + sizeof(sInfo), STRINGBYTES(sInfo.cbComputer));
					CopyMemory(szName.GetBufferSetLength(STRINGCHARS(sInfo.cbTelecommand[0])), nInfo.GetData() + sizeof(sInfo) + sInfo.cbComputer, STRINGBYTES(sInfo.cbTelecommand[0]));
					CopyMemory(szSequence.GetBufferSetLength(STRINGCHARS(sInfo.cbTelecommand[1])), nInfo.GetData() + sizeof(sInfo) + sInfo.cbComputer + sInfo.cbTelecommand[0], STRINGBYTES(sInfo.cbTelecommand[1]));
					nLimitation = sInfo.nLimitation;
					nAutoload = sInfo.nAutoload;
					nSortMode = sInfo.nMode[1];
					nMode = sInfo.nMode[0];
					szComputer.ReleaseBuffer();
					szSequence.ReleaseBuffer();
					szName.ReleaseBuffer();
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetTCHistoryModeInfo(INT nPage, INT nDisplay, UINT nMode, UINT nSpeed, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nMode = nMode;
	sInfo.nSpeed = nSpeed;
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tStopTime = tStopTime.GetTime();
	return((nMode != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYMODEINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYMODEINFO)));
}

BOOL CProfile::GetTCHistoryModeInfo(INT nPage, INT nDisplay, UINT &nMode, UINT &nSpeed, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	struct {
		UINT  nMode;
		UINT  nSpeed;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYMODEINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		nMode = sInfo.nMode;
		nSpeed = sInfo.nSpeed;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCHistoryAlertInfo(INT nPage, INT nDisplay, CONST CUIntArray &nTypes, CONST CStringArray &szAuditions, CONST CStringArray &szNotifications, CONST CDWordArray &nAcknowledgeColors, CONST CByteArray &bAcknowledgments)
{
	struct {
		INT  cbSize;
		INT  cbTypes;
		INT  cbAuditions;
		INT  cbNotifications;
		INT  cbAcknowledgeColors;
		INT  cbAcknowledgments;
	} sInfo;
	INT  nAudition;
	INT  nAuditions;
	INT  nNotification;
	INT  nNotifications;
	CByteArray  nInfo;
	CByteArray  nInfoData[2];

	sInfo.cbTypes = (INT)(nTypes.GetSize()*sizeof(UINT));
	sInfo.cbAcknowledgeColors = (INT)(nAcknowledgeColors.GetSize()*sizeof(DWORD));
	sInfo.cbAcknowledgments = (INT)(bAcknowledgments.GetSize()*sizeof(BYTE));
	for (nAudition = 0, nAuditions = (INT)szAuditions.GetSize(), sInfo.cbAuditions = 0; nAudition < nAuditions; nAudition++)
	{
		nInfoData[0].SetSize(sInfo.cbAuditions + (szAuditions.GetAt(nAudition).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nInfoData[0].GetData() + sInfo.cbAuditions, (LPCTSTR)szAuditions.GetAt(nAudition), (szAuditions.GetAt(nAudition).GetLength() + 1)*sizeof(TCHAR));
		sInfo.cbAuditions += (szAuditions.GetAt(nAudition).GetLength() + 1)*sizeof(TCHAR);
	}
	for (nNotification = 0, nNotifications = (INT)szNotifications.GetSize(), sInfo.cbNotifications = 0; nNotification < nNotifications; nNotification++)
	{
		nInfoData[1].SetSize(sInfo.cbNotifications + (szNotifications.GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nInfoData[1].GetData() + sInfo.cbNotifications, (LPCTSTR)szNotifications.GetAt(nNotification), (szNotifications.GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR));
		sInfo.cbNotifications += (szNotifications.GetAt(nNotification).GetLength() + 1)*sizeof(TCHAR);
	}
	nInfo.SetSize((sInfo.cbSize = sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors + sInfo.cbAcknowledgments));
	CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nInfo.GetData() + sizeof(sInfo), nTypes.GetData(), sInfo.cbTypes);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes, nInfoData[0].GetData(), sInfo.cbAuditions);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions, nInfoData[1].GetData(), sInfo.cbNotifications);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications, nAcknowledgeColors.GetData(), sInfo.cbAcknowledgeColors);
	CopyMemory(nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors, bAcknowledgments.GetData(), sInfo.cbAcknowledgments);
	return((nTypes.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYALERTSINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYALERTSINFO)));
}

BOOL CProfile::GetTCHistoryAlertInfo(INT nPage, INT nDisplay, CUIntArray &nTypes, CStringArray &szAuditions, CStringArray &szNotifications, CDWordArray &nAcknowledgeColors, CByteArray &bAcknowledgments) CONST
{
	struct {
		INT  cbSize;
		INT  cbTypes;
		INT  cbAuditions;
		INT  cbNotifications;
		INT  cbAcknowledgeColors;
		INT  cbAcknowledgments;
	} sInfo;
	INT  nSize;
	INT  cbAudition;
	INT  cbAuditions;
	INT  cbNotification;
	INT  cbNotifications;
	DWORD  dwType;
	CByteArray  nInfo;
	CByteArray  nInfoData[2];

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYALERTSINFO)), nInfo.SetSize(max(nSize, 0)), nTypes.RemoveAll(), szAuditions.RemoveAll(), szNotifications.RemoveAll(), nAcknowledgeColors.RemoveAll(), bAcknowledgments.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYALERTSINFO), &dwType, (LPBYTE)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				if (sInfo.cbSize == sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors + sInfo.cbAcknowledgments)
				{
					nTypes.SetSize(sInfo.cbTypes / sizeof(UINT));
					nInfoData[0].SetSize(sInfo.cbAuditions);
					nInfoData[1].SetSize(sInfo.cbNotifications);
					nAcknowledgeColors.SetSize(sInfo.cbAcknowledgeColors / sizeof(DWORD));
					bAcknowledgments.SetSize(sInfo.cbAcknowledgments / sizeof(BYTE));
					CopyMemory(nTypes.GetData(), nInfo.GetData() + sizeof(sInfo), sInfo.cbTypes);
					CopyMemory(nInfoData[0].GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes, sInfo.cbAuditions);
					CopyMemory(nInfoData[1].GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions, sInfo.cbNotifications);
					CopyMemory(nAcknowledgeColors.GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications, sInfo.cbAcknowledgeColors);
					CopyMemory(bAcknowledgments.GetData(), nInfo.GetData() + sizeof(sInfo) + sInfo.cbTypes + sInfo.cbAuditions + sInfo.cbNotifications + sInfo.cbAcknowledgeColors, sInfo.cbAcknowledgments);
					for (cbAuditions = 0; cbAuditions < sInfo.cbAuditions; cbAuditions += cbAudition)
					{
						szAuditions.Add((LPCTSTR)(nInfoData[0].GetData() + cbAuditions));
						cbAudition = (szAuditions.GetAt(szAuditions.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
					}
					for (cbNotifications = 0; cbNotifications < sInfo.cbNotifications; cbNotifications += cbNotification)
					{
						szNotifications.Add((LPCTSTR)(nInfoData[1].GetData() + cbNotifications));
						cbNotification = (szNotifications.GetAt(szNotifications.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
					}
					return TRUE;
				}
				break;
			}
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCHistoryPrintInfo(INT nPage, INT nDisplay, CONST CByteArray &nPrintInfo)
{
	return((nPrintInfo.GetSize() > 0) ? SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYPRINTINFO), REG_BINARY, nPrintInfo.GetData(), (INT)nPrintInfo.GetSize()) : SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYPRINTINFO)));
}

BOOL CProfile::GetTCHistoryPrintInfo(INT nPage, INT nDisplay, CByteArray &nPrintInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYPRINTINFO)), nPrintInfo.SetSize(max(nSize, 0)); nSize > 0 && nPrintInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYPRINTINFO), &dwType, nPrintInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTCHistoryRetrieveFileName(INT nPage, INT nDisplay, LPCTSTR pszFileName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYRETRIEVEFILENAME), pszFileName);
}

BOOL CProfile::GetTCHistoryRetrieveFileName(INT nPage, INT nDisplay, CString &szFileName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nPage, nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCHISTORYRETRIEVEFILENAME), szFileName);
}

BOOL CProfile::SetCLCWPanelLayoutInfo(LPCRECT pPosition, BOOL bVisible)
{
	struct {
		RECT  rPosition;
		BOOL  bVisible;
	} sInfo;

	sInfo.bVisible = bVisible;
	CopyMemory(&sInfo.rPosition, pPosition, (AfxIsValidAddress(pPosition, sizeof(RECT), FALSE)) ? sizeof(RECT) : 0);
	return((AfxIsValidAddress(pPosition, sizeof(RECT), FALSE)) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_CLCWPANELLAYOUTINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_CLCWPANELLAYOUTINFO)));
}

BOOL CProfile::GetCLCWPanelLayoutInfo(LPRECT pPosition, BOOL &bVisible) CONST
{
	struct {
		RECT  rPosition;
		BOOL  bVisible;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_CLCWPANELLAYOUTINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(pPosition, &sInfo.rPosition, sizeof(RECT));
		bVisible = sInfo.bVisible;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetPFLPServiceSettingsInfo(CONST CByteArray &nSettingsInfo)
{
	return((nSettingsInfo.GetSize() > 0) ? SetUserInfo(QueryPFLPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_PFLPSERVICESETTINGSINFO), REG_BINARY, nSettingsInfo.GetData(), (INT)nSettingsInfo.GetSize()) : SetUserInfo(QueryPFLPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_PFLPSERVICESETTINGSINFO)));
}

BOOL CProfile::GetPFLPServiceSettingsInfo(CByteArray &nSettingsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryPFLPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_PFLPSERVICESETTINGSINFO)), nSettingsInfo.SetSize(max(nSize, 0)); nSize > 0 && nSettingsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryPFLPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_PFLPSERVICESETTINGSINFO), &dwType, nSettingsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetTPEPServiceSettingsInfo(UINT nPort, UINT nBufferSize, UINT nCharset, CONST CTimeSpan &tTimeout)
{
	struct {
		UINT  nPort;
		UINT  nCharset;
		UINT  nBufferSize;
		TIMEKEY  tTimeout;
	} sInfo;

	sInfo.nPort = nPort;
	sInfo.nCharset = nCharset;
	sInfo.nBufferSize = nBufferSize;
	sInfo.tTimeout = tTimeout.GetTotalSeconds();
	return((nPort != (UINT)-1 && nBufferSize != (UINT)-1 && nCharset != (UINT)-1 && tTimeout > 0) ? SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICESETTINGSINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICESETTINGSINFO)));
}

BOOL CProfile::GetTPEPServiceSettingsInfo(UINT &nPort, UINT &nBufferSize, UINT &nCharset, CTimeSpan &tTimeout) CONST
{
	struct {
		UINT  nPort;
		UINT  nCharset;
		UINT  nBufferSize;
		TIMEKEY  tTimeout;
	} sInfo;
	INT  cbInfo;
	DWORD  dwType;

	if ((cbInfo = GetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICESETTINGSINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo))) == sizeof(sInfo))
	{
		nPort = sInfo.nPort;
		nCharset = sInfo.nCharset;
		nBufferSize = sInfo.nBufferSize;
		tTimeout = sInfo.tTimeout;
		return TRUE;
	}
	return((cbInfo < 0) ? TRUE : FALSE);
}

BOOL CProfile::SetTPEPServiceAvailabilityInfo(UINT nCode, CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	struct {
		UINT  nCode;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;

	sInfo.nCode = nCode;
	sInfo.tStartTime = tStartTime.GetTotalSeconds();
	sInfo.tStopTime = tStopTime.GetTotalSeconds();
	return((nCode != (UINT)-1) ? SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEAVAILABILITYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEAVAILABILITYINFO)));
}

BOOL CProfile::GetTPEPServiceAvailabilityInfo(UINT &nCode, CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	struct {
		UINT  nCode;
		TIMEKEY  tStartTime;
		TIMEKEY  tStopTime;
	} sInfo;
	INT  cbInfo;
	DWORD  dwType;

	if ((cbInfo = GetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEAVAILABILITYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo))) == sizeof(sInfo))
	{
		nCode = sInfo.nCode;
		tStartTime = sInfo.tStartTime;
		tStopTime = sInfo.tStopTime;
		return TRUE;
	}
	return((cbInfo < 0) ? TRUE : FALSE);
}

BOOL CProfile::SetTPEPServiceSecurityInfo(CONST CStringArray &szUsers, CONST CUIntArray &nCodes, CONST CTimeKeyArray &tStartTimes, CONST CTimeKeyArray &tStopTimes)
{
	struct {
		UINT  nSize;
		UINT  nCodes;
		UINT  nUsers;
		UINT  nStartTimes;
		UINT  nStopTimes;
	} sInfo;
	INT  nUser;
	INT  nUsers;
	INT  cbUser;
	INT  cbUsers;
	INT  nIndex;
	CByteArray  nInfo;
	CByteArray  nInfoData[2];

	sInfo.nCodes = (UINT)nCodes.GetSize();
	sInfo.nUsers = (UINT)szUsers.GetSize();
	sInfo.nStartTimes = (UINT)tStartTimes.Map(nInfoData[0]);
	sInfo.nStopTimes = (UINT)tStopTimes.Map(nInfoData[1]);
	for (nUser = 0, nUsers = (INT)szUsers.GetSize(), nInfo.SetSize((cbUsers = sizeof(sInfo))); nUser < nUsers; nUser++)
	{
		nInfo.SetSize((cbUsers + (cbUser = (szUsers.GetAt(nUser).GetLength() + 1)*sizeof(TCHAR))));
		if (nInfo.GetSize() == cbUsers + cbUser)
		{
			CopyMemory(nInfo.GetData() + cbUsers, (LPCTSTR)szUsers.GetAt(nUser), cbUser);
			cbUsers += cbUser;
			continue;
		}
		break;
	}
	if (nUser == nUsers)
	{
		if (nCodes.GetSize() > 0)
		{
			nInfo.InsertAt((nIndex = (INT)nInfo.GetSize()), 0, nCodes.GetSize()*sizeof(UINT));
			CopyMemory(nInfo.GetData() + nIndex, nCodes.GetData(), nCodes.GetSize()*sizeof(UINT));
		}
		if (nInfoData[0].GetSize() > 0)
		{
			nInfo.InsertAt((nIndex = (INT)nInfo.GetSize()), 0, nInfoData[0].GetSize());
			CopyMemory(nInfo.GetData() + nIndex, nInfoData[0].GetData(), nInfoData[0].GetSize());
		}
		if (nInfoData[1].GetSize() > 0)
		{
			nInfo.InsertAt((nIndex = (INT)nInfo.GetSize()), 0, nInfoData[1].GetSize());
			CopyMemory(nInfo.GetData() + nIndex, nInfoData[1].GetData(), nInfoData[1].GetSize());
		}
		sInfo.nSize = (UINT)nInfo.GetSize();
		CopyMemory(nInfo.GetData(), &sInfo, sizeof(sInfo));
		return((szUsers.GetSize() > 0 && szUsers.GetSize() == nCodes.GetSize() && szUsers.GetSize() == tStartTimes.GetSize() && tStartTimes.GetSize() == tStopTimes.GetSize()) ? SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICESECURITYINFO), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICESECURITYINFO)));
	}
	return FALSE;
}

BOOL CProfile::GetTPEPServiceSecurityInfo(CStringArray &szUsers, CUIntArray &nCodes, CTimeKeyArray &tStartTimes, CTimeKeyArray &tStopTimes) CONST
{
	struct {
		UINT  nSize;
		UINT  nCodes;
		UINT  nUsers;
		UINT  nStartTimes;
		UINT  nStopTimes;
	} sInfo;
	INT  nSize;
	INT  nUser;
	INT  nUsers;
	INT  cbUser;
	INT  cbUsers;
	DWORD  dwType;
	CByteArray  nInfo;
	CByteArray  nInfoData[2];

	for (nSize = GetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICESECURITYINFO)), nInfo.SetSize(max(nSize, 0)), szUsers.RemoveAll(), nCodes.RemoveAll(), tStartTimes.RemoveAll(), tStopTimes.RemoveAll(); nSize > 0 && nInfo.GetSize() == nSize; )
	{
		if (GetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICESECURITYINFO), &dwType, (BYTE *)nInfo.GetData(), nSize) == nSize)
		{
			for (CopyMemory(&sInfo, nInfo.GetData(), min(sizeof(sInfo), nInfo.GetSize())); nSize >= (INT)(sizeof(sInfo) / sizeof(BYTE)); )
			{
				for (nUser = 0, nUsers = (sInfo.nSize == nInfo.GetSize()) ? sInfo.nUsers : -1, cbUsers = sizeof(sInfo); nUser < nUsers; nUser++)
				{
					szUsers.Add((LPCTSTR)((LPSTR)nInfo.GetData() + cbUsers));
					cbUser = (szUsers.GetAt(nUser).GetLength() + 1)*sizeof(TCHAR);
					if ((cbUsers = cbUsers + cbUser) >= nInfo.GetSize()) break;
				}
				if (nUser == nUsers)
				{
					nInfo.RemoveAt(0, cbUsers);
					if (sInfo.nCodes*sizeof(UINT) >(UINT) nInfo.GetSize()) break;
					nCodes.SetSize(sInfo.nCodes);
					CopyMemory(nCodes.GetData(), nInfo.GetData(), sInfo.nCodes*sizeof(UINT));
					nInfo.RemoveAt(0, sInfo.nCodes*sizeof(UINT));
					if (sInfo.nStartTimes > (UINT)nInfo.GetSize()) break;
					nInfoData[0].SetSize(sInfo.nStartTimes);
					CopyMemory(nInfoData[0].GetData(), nInfo.GetData(), sInfo.nStartTimes);
					nInfo.RemoveAt(0, sInfo.nStartTimes);
					tStartTimes.Unmap(nInfoData[0]);
					if (sInfo.nStopTimes > (UINT)nInfo.GetSize()) break;
					nInfoData[1].SetSize(sInfo.nStopTimes);
					CopyMemory(nInfoData[1].GetData(), nInfo.GetData(), sInfo.nStopTimes);
					nInfo.RemoveAt(0, sInfo.nStopTimes);
					tStopTimes.Unmap(nInfoData[1]);
				}
				break;
			}
		}
		break;
	}
	return((nSize <= 0 || (szUsers.GetSize() > 0 && szUsers.GetSize() == nCodes.GetSize() && szUsers.GetSize() == tStartTimes.GetSize() && tStartTimes.GetSize() == tStopTimes.GetSize())) ? TRUE : FALSE);
}

BOOL CProfile::SetTPEPServiceProfileInfo(CONST CByteArray &nPacketProfilesInfo, CONST CByteArray &nParameterProfilesInfo)
{
	return((nPacketProfilesInfo.GetSize() > 0 && nParameterProfilesInfo.GetSize() > 0) ? (SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPACKETPROFILEINFO), REG_BINARY, nPacketProfilesInfo.GetData(), (INT)nPacketProfilesInfo.GetSize()) && SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPARAMETERPROFILEINFO), REG_BINARY, nParameterProfilesInfo.GetData(), (INT)nParameterProfilesInfo.GetSize())) : ((nPacketProfilesInfo.GetSize() > 0 && !nParameterProfilesInfo.GetSize()) ? (SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPACKETPROFILEINFO), REG_BINARY, nPacketProfilesInfo.GetData(), (INT)nPacketProfilesInfo.GetSize()) && SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPARAMETERPROFILEINFO))) : ((!nPacketProfilesInfo.GetSize() && nParameterProfilesInfo.GetSize() > 0) ? (SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPACKETPROFILEINFO)) && SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPARAMETERPROFILEINFO), REG_BINARY, nParameterProfilesInfo.GetData(), (INT)nParameterProfilesInfo.GetSize())) : (SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPACKETPROFILEINFO)) && SetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPARAMETERPROFILEINFO))))));
}

BOOL CProfile::GetTPEPServiceProfileInfo(CByteArray &nPacketProfilesInfo, CByteArray &nParameterProfilesInfo) CONST
{
	INT  nSize[2];
	DWORD  dwType;

	for (nSize[0] = GetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPACKETPROFILEINFO)), nPacketProfilesInfo.SetSize(max(nSize[0], 0)); nSize[0] > 0 && nPacketProfilesInfo.GetSize() == nSize[0]; ) break;
	for (nSize[1] = GetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPARAMETERPROFILEINFO)), nParameterProfilesInfo.SetSize(max(nSize[1], 0)); nSize[1] > 0 && nParameterProfilesInfo.GetSize() == nSize[1]; ) break;
	return(((nSize[0] <= 0 || GetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPACKETPROFILEINFO), &dwType, nPacketProfilesInfo.GetData(), nSize[0]) == nSize[0]) && (nSize[1] <= 0 || GetUserInfo(QueryTPEPServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_TPEPSERVICEPARAMETERPROFILEINFO), &dwType, nParameterProfilesInfo.GetData(), nSize[1]) == nSize[1])) ? TRUE : FALSE);
}

BOOL CProfile::SetAutomationServiceSettingsInfo(UINT nPort, UINT nBufferSize, CONST CTimeSpan &tTimeout, BOOL bEnabled)
{
	struct {
		UINT  nPort;
		UINT  nBufferSize;
		TIMEKEY  tTimeout;
		BOOL  bEnabled;
	} sInfo;

	sInfo.nPort = nPort;
	sInfo.bEnabled = bEnabled;
	sInfo.nBufferSize = nBufferSize;
	sInfo.tTimeout = tTimeout.GetTotalSeconds();
	return((nPort != (UINT)-1 && nBufferSize != (UINT)-1 && tTimeout > 0) ? SetUserInfo(QueryAutomationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_AUTOMATIONSERVICESETTINGSINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryAutomationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_AUTOMATIONSERVICESETTINGSINFO)));
}

BOOL CProfile::GetAutomationServiceSettingsInfo(UINT &nPort, UINT &nBufferSize, CTimeSpan &tTimeout, BOOL &bEnabled) CONST
{
	struct {
		UINT  nPort;
		UINT  nBufferSize;
		TIMEKEY  tTimeout;
		BOOL  bEnabled;
	} sInfo;
	INT  cbInfo;
	DWORD  dwType;

	if ((cbInfo = GetUserInfo(QueryAutomationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_AUTOMATIONSERVICESETTINGSINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo))) == sizeof(sInfo))
	{
		nPort = sInfo.nPort;
		bEnabled = sInfo.bEnabled;
		nBufferSize = sInfo.nBufferSize;
		tTimeout = sInfo.tTimeout;
		return TRUE;
	}
	return((cbInfo < 0) ? TRUE : FALSE);
}

BOOL CProfile::SetAutomationServiceClientsInfo(CONST CByteArray &nClientsInfo)
{
	return((nClientsInfo.GetSize() > 0) ? SetUserInfo(QueryAutomationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_AUTOMATIONSERVICECLIENTSINFO), REG_BINARY, nClientsInfo.GetData(), (INT)nClientsInfo.GetSize()) : SetUserInfo(QueryAutomationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_AUTOMATIONSERVICECLIENTSINFO)));
}

BOOL CProfile::GetAutomationServiceClientsInfo(CByteArray &nClientsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryAutomationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_AUTOMATIONSERVICECLIENTSINFO)), nClientsInfo.SetSize(max(nSize, 0)); nSize > 0 && nClientsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryAutomationServiceSubKey(), STRING(IDS_REG_SUBKEYVALUE_AUTOMATIONSERVICECLIENTSINFO), &dwType, nClientsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetToolsDownloadProfilesInfo(CONST CByteArray &nProfilesInfo)
{
	return((nProfilesInfo.GetSize() > 0) ? SetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSDOWNLOADPROFILESINFO), REG_BINARY, nProfilesInfo.GetData(), (INT)nProfilesInfo.GetSize()) : SetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSDOWNLOADPROFILESINFO)));
}

BOOL CProfile::GetToolsDownloadProfilesInfo(CByteArray &nProfilesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSDOWNLOADPROFILESINFO)), nProfilesInfo.SetSize(max(nSize, 0)); nSize > 0 && nProfilesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSDOWNLOADPROFILESINFO), &dwType, nProfilesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetToolsDatabaseOptionsInfo(UINT nOption, CONST CTimeKey &tStartTime, CONST CTimeKey &tEndTime)
{
	struct {
		UINT  nOption;
		TIMEKEY  tStartTime;
		TIMEKEY  tEndTime;
	} sInfo;

	sInfo.nOption = nOption;
	sInfo.tStartTime = tStartTime.GetTime();
	sInfo.tEndTime = tEndTime.GetTime();
	return((nOption != (UINT)-1 && tStartTime > 0 && tEndTime > 0) ? SetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSDATABASEOPTIONSINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSDATABASEOPTIONSINFO)));
}

BOOL CProfile::GetToolsDatabaseOptionsInfo(UINT &nOption, CTimeKey &tStartTime, CTimeKey &tEndTime) CONST
{
	struct {
		UINT  nOption;
		TIMEKEY  tStartTime;
		TIMEKEY  tEndTime;
	} sInfo;
	INT  cbInfo;
	DWORD  dwType;

	if ((cbInfo = GetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSDATABASEOPTIONSINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo))) == sizeof(sInfo))
	{
		nOption = sInfo.nOption;
		tStartTime = sInfo.tStartTime;
		tEndTime = sInfo.tEndTime;
		return TRUE;
	}
	return((cbInfo < 0) ? TRUE : FALSE);
}

BOOL CProfile::SetToolsSatelliteTrackingOptionsInfo(LPCTSTR pszConfigurationFileName, LPCTSTR pszHelpFileName, BOOL bEnabled)
{
	CStringTools  cStringTools;

	return((AfxIsValidString(pszConfigurationFileName) && AfxIsValidString(pszHelpFileName)) ? (SetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSSATELLITETRACKINGOPTIONSINFO), CString(pszConfigurationFileName) + TAB + CString(pszHelpFileName) + TAB + cStringTools.ConvertUIntToString(bEnabled))) : SetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSSATELLITETRACKINGOPTIONSINFO)));
}

BOOL CProfile::GetToolsSatelliteTrackingOptionsInfo(CString &szConfigurationFileName, CString &szHelpFileName, BOOL &bEnabled) CONST
{
	INT  nPos[2];
	CString  szInfo;
	BOOL  bInfo;

	for (szConfigurationFileName.Empty(), szHelpFileName.Empty(), bEnabled = TRUE; (nPos[0] = ((bInfo = GetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSSATELLITETRACKINGOPTIONSINFO), szInfo))) ? szInfo.Find(TAB) : -1) >= 0 && (nPos[1] = szInfo.Mid(nPos[0] + 1).Find(TAB)) >= 0; )
	{
		szConfigurationFileName = szInfo.Left(nPos[0]);
		szHelpFileName = szInfo.Mid(nPos[0] + 1).Left(nPos[1]);
		bEnabled = (_ttoi(szInfo.Mid(nPos[0] + 1 + nPos[1] + 1)) > 0);
		return TRUE;
	}
	return !bInfo;
}

BOOL CProfile::SetToolsEMailSettingsInfo(CONST CByteArray &nSettingsInfo)
{
	return((nSettingsInfo.GetSize() > 0) ? SetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSEMAILSETTINGSINFO), REG_BINARY, nSettingsInfo.GetData(), (INT)nSettingsInfo.GetSize()) : SetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSEMAILSETTINGSINFO)));
}

BOOL CProfile::GetToolsEMailSettingsInfo(CByteArray &nSettingsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSEMAILSETTINGSINFO)), nSettingsInfo.SetSize(max(nSize, 0)); nSize > 0 && nSettingsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryToolsSubKey(), STRING(IDS_REG_SUBKEYVALUE_TOOLSEMAILSETTINGSINFO), &dwType, nSettingsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::DeleteAllInfo()
{
	CString  szSubKey;
	CStringArray  szSubKeys;
	CStringArray  szValueNames;
	CVersionInfo  cVersionInfo;

	DeleteSubKey(STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + GetAppTitle());
	if (!EnumUserSubKeys((szSubKey = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName()), szSubKeys) && !EnumUserSubKeyValueNames(szSubKey, szValueNames)) return DeleteSubKey(szSubKey);
	return TRUE;
}

BOOL CProfile::DeleteDisplayAreaInfo()
{
	return DeleteSubKey(QueryDisplayAreaSubKey());
}

BOOL CProfile::DeleteDisplayPageInfo(INT nPage)
{
	return((nPage >= 0) ? DeleteSubKey(QueryDisplayPageSubKey(nPage)) : FALSE);
}

BOOL CProfile::DeleteDisplayWindowInfo(INT nPage, INT nDisplay)
{
	return DeleteSubKey(QueryDisplayWindowSubKey(nPage, nDisplay));
}

BOOL CProfile::DeleteTemporaryDisplaysInfo()
{
	return DeleteSubKey(QueryTemporaryDisplaysSubKey());
}

BOOL CProfile::DeleteEventBoxDefaultInfo()
{
	return DeleteSubKey(QueryEventBoxDefaultSubKey());
}

BOOL CProfile::DeleteTelemetryServiceInfo()
{
	return DeleteSubKey(QueryTelemetryServiceSubKey());
}

BOOL CProfile::DeleteTelemetryArchivesInfo()
{
	return DeleteSubKey(QueryTelemetryArchivesSubKey());
}

BOOL CProfile::DeleteTelemetryReportsServiceInfo()
{
	return DeleteSubKey(QueryTelemetryReportsServiceSubKey());
}

BOOL CProfile::DeleteTelecommandServiceInfo()
{
	return DeleteSubKey(QueryTelecommandServiceSubKey());
}

BOOL CProfile::DeleteTelecommandArchivesInfo()
{
	return DeleteSubKey(QueryTelecommandArchivesSubKey());
}

BOOL CProfile::DeleteMemoryDumpServiceInfo()
{
	return DeleteSubKey(QueryMemoryDumpServiceSubKey());
}

BOOL CProfile::DeleteNotificationServiceInfo()
{
	return DeleteSubKey(QueryNotificationServiceSubKey());
}

BOOL CProfile::DeletePFLPServiceInfo()
{
	return DeleteSubKey(QueryPFLPServiceSubKey());
}

BOOL CProfile::DeleteTPEPServiceInfo()
{
	return DeleteSubKey(QueryTPEPServiceSubKey());
}

BOOL CProfile::DeleteAutomationServiceInfo()
{
	return DeleteSubKey(QueryAutomationServiceSubKey());
}

BOOL CProfile::DeleteToolsInfo()
{
	return DeleteSubKey(QueryToolsSubKey());
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

CString CProfile::QuerySubKey() CONST
{
	CString  szSubKey;
	CVersionInfo  cVersionInfo;

	szSubKey = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName();
	szSubKey += STRING(IDS_REG_SUBKEYPART_DELIMITER) + GetAppTitle();
	szSubKey += STRING(IDS_REG_SUBKEYPART_DELIMITER) + GetAccountUserName();
	return szSubKey;
}

CString CProfile::QuerySpacecraftSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += GetAccountSpacecraftName();
	return szSubKey;
}

CString CProfile::QueryDisplayAreaSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += GetAccountDatabase() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + STRING(IDS_REG_SUBKEYPART_DISPLAYAREA);
	return szSubKey;
}

CString CProfile::QueryDisplayPageSubKey(INT nPage) CONST
{
	CString  szSubKey[2];
	CStringTools  cStringTools;

	szSubKey[0] = QueryDisplayAreaSubKey();
	szSubKey[1] = szSubKey[0] + STRING(IDS_REG_SUBKEYPART_DELIMITER) + STRING(IDS_REG_SUBKEYPART_DISPLAYPAGE) + cStringTools.ConvertIntToString(nPage);
	return((nPage >= 0) ? szSubKey[1] : szSubKey[0]);
}

CString CProfile::QueryDisplayWindowSubKey(INT nPage, INT nDisplay) CONST
{
	CString  szSubKey;
	CStringTools  cStringTools;

	szSubKey = QueryDisplayPageSubKey(nPage) + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_DISPLAYWINDOW);
	szSubKey += cStringTools.ConvertIntToString(nDisplay);
	return szSubKey;
}

CString CProfile::QueryTemporaryDisplaysSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QueryDisplayAreaSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_TEMPORARYDISPLAYS);
	return szSubKey;
}

CString CProfile::QueryEventBoxDefaultSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_EVENTBOX);
	return szSubKey;
}

CString CProfile::QueryTelemetryServiceSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_TELEMETRYSERVICE);
	return szSubKey;
}

CString CProfile::QueryTelemetryArchivesSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_TELEMETRYARCHIVES);
	return szSubKey;
}

CString CProfile::QueryTelemetryReportsServiceSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_TELEMETRYREPORTSSERVICE);
	return szSubKey;
}

CString CProfile::QueryTelecommandServiceSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_TELECOMMANDSERVICE);
	return szSubKey;
}

CString CProfile::QueryTelecommandArchivesSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_TELECOMMANDARCHIVES);
	return szSubKey;
}

CString CProfile::QueryMemoryDumpServiceSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_MEMORYDUMPSSERVICE);
	return szSubKey;
}

CString CProfile::QueryNotificationServiceSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_NOTIFICATIONSERVICE);
	return szSubKey;
}

CString CProfile::QueryPFLPServiceSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_PFLPSERVICE);
	return szSubKey;
}

CString CProfile::QueryTPEPServiceSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_TPEPSERVICE);
	return szSubKey;
}

CString CProfile::QueryAutomationServiceSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySpacecraftSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_AUTOMATIONSERVICE);
	return szSubKey;
}

CString CProfile::QueryToolsSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_TOOLS);
	return szSubKey;
}
