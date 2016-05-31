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
* 1998/02/18 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



//////////////////////////////////////////////////////////////////////////////
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

BOOL CProfile::SetPosition(LPCRECT pRect)
{
	return SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_POSITION), REG_BINARY, (CONST BYTE *) pRect, sizeof(RECT));
}

BOOL CProfile::GetPosition(LPRECT pRect) CONST
{
	RECT  rRect;
	DWORD  dwType;

	if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_POSITION), &dwType, (LPBYTE)&rRect, sizeof(RECT)) == sizeof(RECT))
	{
		CopyRect(pRect, &rRect);
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayWindowCount(INT nCount)
{
	return((nCount >= 0) ? SetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWCOUNT), nCount) : SetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWCOUNT)));
}

BOOL CProfile::GetDisplayWindowCount(INT &nCount) CONST
{
	DWORD  dwCount;

	if (GetUserInfo(QueryDisplayAreaSubKey(), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWCOUNT), dwCount))
	{
		nCount = dwCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayWindowType(INT nDisplay, UINT nType)
{
	return((nType != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWTYPE), nType) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWTYPE)));
}

BOOL CProfile::GetDisplayWindowType(INT nDisplay, UINT &nType) CONST
{
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWTYPE), dwType))
	{
		nType = dwType;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetDisplayWindowName(INT nDisplay, LPCTSTR pszName)
{
	return SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWNAME), pszName);
}

BOOL CProfile::GetDisplayWindowName(INT nDisplay, CString &szName) CONST
{
	return GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWNAME), szName);
}

BOOL CProfile::SetDisplayWindowPlacement(INT nDisplay, LPCRECT pRect, CONST POINT *pPoint, UINT nShow)
{
	struct {
		RECT  rPosition;
		POINT  ptPosition;
		UINT  nShow;
	} sInfo;

	sInfo.nShow = nShow;
	CopyMemory(&sInfo.rPosition, pRect, (AfxIsValidAddress(pRect, sizeof(RECT), FALSE)) ? sizeof(RECT) : 0);
	CopyMemory(&sInfo.ptPosition, pPoint, (AfxIsValidAddress(pPoint, sizeof(POINT), FALSE)) ? sizeof(POINT) : 0);
	return((AfxIsValidAddress(pRect, sizeof(RECT), FALSE) && AfxIsValidAddress(pPoint, sizeof(POINT), FALSE) && nShow != (UINT)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWPLACEMENT), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWPLACEMENT)));
}

BOOL CProfile::GetDisplayWindowPlacement(INT nDisplay, LPRECT pRect, LPPOINT pPoint, UINT &nShow) CONST
{
	struct {
		RECT  rPosition;
		POINT  ptPosition;
		UINT  nShow;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_DISPLAYWINDOWPLACEMENT), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(pRect, &sInfo.rPosition, sizeof(RECT));
		CopyMemory(pPoint, &sInfo.ptPosition, sizeof(POINT));
		nShow = sInfo.nShow;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTMPacketsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;

	sInfo.nColor[0] = nTitleColor;
	sInfo.nColor[1] = nItemsColor;
	sInfo.nColor[2] = nTitleBackground;
	sInfo.nColor[3] = nKeysBackground;
	CopyMemory(&sInfo.lfTable[0], plfTitle, (AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sInfo.lfTable[1], plfItems, (AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE) && nTitleColor != (COLORREF)-1 && nItemsColor != (COLORREF)-1 && nTitleBackground != (COLORREF)-1 && nKeysBackground != (COLORREF)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TMPACKETSFORMPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TMPACKETSFORMPROPERTYINFO)));
}

BOOL CProfile::GetTMPacketsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TMPACKETSFORMPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(plfTitle, &sInfo.lfTable[0], sizeof(LOGFONT));
		CopyMemory(plfItems, &sInfo.lfTable[1], sizeof(LOGFONT));
		nKeysBackground = sInfo.nColor[3];
		nTitleBackground = sInfo.nColor[2];
		nItemsColor = sInfo.nColor[1];
		nTitleColor = sInfo.nColor[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCFunctionsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;

	sInfo.nColor[0] = nTitleColor;
	sInfo.nColor[1] = nItemsColor;
	sInfo.nColor[2] = nTitleBackground;
	sInfo.nColor[3] = nKeysBackground;
	CopyMemory(&sInfo.lfTable[0], plfTitle, (AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sInfo.lfTable[1], plfItems, (AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE) && nTitleColor != (COLORREF)-1 && nItemsColor != (COLORREF)-1 && nTitleBackground != (COLORREF)-1 && nKeysBackground != (COLORREF)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCFUNCTIONSFORMPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCFUNCTIONSFORMPROPERTYINFO)));
}

BOOL CProfile::GetTCFunctionsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCFUNCTIONSFORMPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(plfTitle, &sInfo.lfTable[0], sizeof(LOGFONT));
		CopyMemory(plfItems, &sInfo.lfTable[1], sizeof(LOGFONT));
		nKeysBackground = sInfo.nColor[3];
		nTitleBackground = sInfo.nColor[2];
		nItemsColor = sInfo.nColor[1];
		nTitleColor = sInfo.nColor[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCSequencesFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;

	sInfo.nColor[0] = nTitleColor;
	sInfo.nColor[1] = nItemsColor;
	sInfo.nColor[2] = nTitleBackground;
	sInfo.nColor[3] = nKeysBackground;
	CopyMemory(&sInfo.lfTable[0], plfTitle, (AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sInfo.lfTable[1], plfItems, (AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE) && nTitleColor != (COLORREF)-1 && nItemsColor != (COLORREF)-1 && nTitleBackground != (COLORREF)-1 && nKeysBackground != (COLORREF)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCSEQUENCESFORMPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCSEQUENCESFORMPROPERTYINFO)));
}

BOOL CProfile::GetTCSequencesFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCSEQUENCESFORMPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(plfTitle, &sInfo.lfTable[0], sizeof(LOGFONT));
		CopyMemory(plfItems, &sInfo.lfTable[1], sizeof(LOGFONT));
		nKeysBackground = sInfo.nColor[3];
		nTitleBackground = sInfo.nColor[2];
		nItemsColor = sInfo.nColor[1];
		nTitleColor = sInfo.nColor[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCProcedureWindowPropertyInfo(INT nDisplay, INT nFlowchartPaneWidth, INT nPropertiesPaneWidth, CONST LOGFONT *plfStepsLabel, COLORREF nStepsLabelColor, COLORREF nBackgroundColor)
{
	struct {
		INT  nPaneWidth[2];
		LOGFONT  lfStepsLabel;
		COLORREF  nStepsLabelColor;
		COLORREF  nBackgroundColor;
	} sInfo;

	sInfo.nPaneWidth[0] = nFlowchartPaneWidth;
	sInfo.nPaneWidth[1] = nPropertiesPaneWidth;
	sInfo.nStepsLabelColor = nStepsLabelColor;
	sInfo.nBackgroundColor = nBackgroundColor;
	CopyMemory(&sInfo.lfStepsLabel, plfStepsLabel, (AfxIsValidAddress(plfStepsLabel, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(plfStepsLabel, sizeof(LOGFONT), FALSE) && nFlowchartPaneWidth != -1 && nPropertiesPaneWidth != -1 && nStepsLabelColor != (COLORREF)-1 && nBackgroundColor != (COLORREF)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDUREWINDOWPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDUREWINDOWPROPERTYINFO)));
}

BOOL CProfile::GetTCProcedureWindowPropertyInfo(INT nDisplay, INT &nFlowchartPaneWidth, INT &nPropertiesPaneWidth, LOGFONT *plfStepsLabel, COLORREF &nStepsLabelColor, COLORREF &nBackgroundColor) CONST
{
	struct {
		INT  nPaneWidth[2];
		LOGFONT  lfStepsLabel;
		COLORREF  nStepsLabelColor;
		COLORREF  nBackgroundColor;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPROCEDUREWINDOWPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(plfStepsLabel, &sInfo.lfStepsLabel, sizeof(LOGFONT));
		nStepsLabelColor = sInfo.nStepsLabelColor;
		nBackgroundColor = sInfo.nBackgroundColor;
		nPropertiesPaneWidth = sInfo.nPaneWidth[1];
		nFlowchartPaneWidth = sInfo.nPaneWidth[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTMParametersFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;

	sInfo.nColor[0] = nTitleColor;
	sInfo.nColor[1] = nItemsColor;
	sInfo.nColor[2] = nTitleBackground;
	sInfo.nColor[3] = nKeysBackground;
	CopyMemory(&sInfo.lfTable[0], plfTitle, (AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sInfo.lfTable[1], plfItems, (AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE) && nTitleColor != (COLORREF)-1 && nItemsColor != (COLORREF)-1 && nTitleBackground != (COLORREF)-1 && nKeysBackground != (COLORREF)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TMPARAMETERSFORMPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TMPARAMETERSFORMPROPERTYINFO)));
}

BOOL CProfile::GetTMParametersFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TMPARAMETERSFORMPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(plfTitle, &sInfo.lfTable[0], sizeof(LOGFONT));
		CopyMemory(plfItems, &sInfo.lfTable[1], sizeof(LOGFONT));
		nKeysBackground = sInfo.nColor[3];
		nTitleBackground = sInfo.nColor[2];
		nItemsColor = sInfo.nColor[1];
		nTitleColor = sInfo.nColor[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCParametersFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;

	sInfo.nColor[0] = nTitleColor;
	sInfo.nColor[1] = nItemsColor;
	sInfo.nColor[2] = nTitleBackground;
	sInfo.nColor[3] = nKeysBackground;
	CopyMemory(&sInfo.lfTable[0], plfTitle, (AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sInfo.lfTable[1], plfItems, (AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE) && nTitleColor != (COLORREF)-1 && nItemsColor != (COLORREF)-1 && nTitleBackground != (COLORREF)-1 && nKeysBackground != (COLORREF)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPARAMETERSFORMPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPARAMETERSFORMPROPERTYINFO)));
}

BOOL CProfile::GetTCParametersFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_TCPARAMETERSFORMPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(plfTitle, &sInfo.lfTable[0], sizeof(LOGFONT));
		CopyMemory(plfItems, &sInfo.lfTable[1], sizeof(LOGFONT));
		nKeysBackground = sInfo.nColor[3];
		nTitleBackground = sInfo.nColor[2];
		nItemsColor = sInfo.nColor[1];
		nTitleColor = sInfo.nColor[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetOBProcessorsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;

	sInfo.nColor[0] = nTitleColor;
	sInfo.nColor[1] = nItemsColor;
	sInfo.nColor[2] = nTitleBackground;
	sInfo.nColor[3] = nKeysBackground;
	CopyMemory(&sInfo.lfTable[0], plfTitle, (AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sInfo.lfTable[1], plfItems, (AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE) && nTitleColor != (COLORREF)-1 && nItemsColor != (COLORREF)-1 && nTitleBackground != (COLORREF)-1 && nKeysBackground != (COLORREF)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_OBPROCESSORSFORMPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_OBPROCESSORSFORMPROPERTYINFO)));
}

BOOL CProfile::GetOBProcessorsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_OBPROCESSORSFORMPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(plfTitle, &sInfo.lfTable[0], sizeof(LOGFONT));
		CopyMemory(plfItems, &sInfo.lfTable[1], sizeof(LOGFONT));
		nKeysBackground = sInfo.nColor[3];
		nTitleBackground = sInfo.nColor[2];
		nItemsColor = sInfo.nColor[1];
		nTitleColor = sInfo.nColor[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetANDsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;

	sInfo.nColor[0] = nTitleColor;
	sInfo.nColor[1] = nItemsColor;
	sInfo.nColor[2] = nTitleBackground;
	sInfo.nColor[3] = nKeysBackground;
	CopyMemory(&sInfo.lfTable[0], plfTitle, (AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sInfo.lfTable[1], plfItems, (AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE) && nTitleColor != (COLORREF)-1 && nItemsColor != (COLORREF)-1 && nTitleBackground != (COLORREF)-1 && nKeysBackground != (COLORREF)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDSFORMPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDSFORMPROPERTYINFO)));
}

BOOL CProfile::GetANDsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_ANDSFORMPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(plfTitle, &sInfo.lfTable[0], sizeof(LOGFONT));
		CopyMemory(plfItems, &sInfo.lfTable[1], sizeof(LOGFONT));
		nKeysBackground = sInfo.nColor[3];
		nTitleBackground = sInfo.nColor[2];
		nItemsColor = sInfo.nColor[1];
		nTitleColor = sInfo.nColor[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetGRDsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;

	sInfo.nColor[0] = nTitleColor;
	sInfo.nColor[1] = nItemsColor;
	sInfo.nColor[2] = nTitleBackground;
	sInfo.nColor[3] = nKeysBackground;
	CopyMemory(&sInfo.lfTable[0], plfTitle, (AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sInfo.lfTable[1], plfItems, (AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE) && nTitleColor != (COLORREF)-1 && nItemsColor != (COLORREF)-1 && nTitleBackground != (COLORREF)-1 && nKeysBackground != (COLORREF)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDSFORMPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDSFORMPROPERTYINFO)));
}

BOOL CProfile::GetGRDsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_GRDSFORMPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(plfTitle, &sInfo.lfTable[0], sizeof(LOGFONT));
		CopyMemory(plfItems, &sInfo.lfTable[1], sizeof(LOGFONT));
		nKeysBackground = sInfo.nColor[3];
		nTitleBackground = sInfo.nColor[2];
		nItemsColor = sInfo.nColor[1];
		nTitleColor = sInfo.nColor[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetMMDWindowPropertyInfo(INT nDisplay, INT nImagePaneHeight, INT nImagePaneMinHeight, INT nCodePaneHeight, INT nCodePaneMinHeight, LPCRECT pHotSpot)
{
	struct {
		INT  nImagePaneHeight[2];
		INT  nCodePaneHeight[2];
		RECT  rHotSpot;
	} sInfo;

	sInfo.nImagePaneHeight[0] = nImagePaneHeight;
	sInfo.nImagePaneHeight[1] = nImagePaneMinHeight;
	sInfo.nCodePaneHeight[0] = nCodePaneHeight;
	sInfo.nCodePaneHeight[1] = nCodePaneMinHeight;
	CopyMemory(&sInfo.rHotSpot, pHotSpot, (AfxIsValidAddress(pHotSpot, sizeof(RECT), FALSE)) ? sizeof(RECT) : 0);
	return((nImagePaneHeight != -1 && nImagePaneMinHeight != -1 && nCodePaneHeight != -1 && nCodePaneMinHeight != -1 && AfxIsValidAddress(pHotSpot, sizeof(RECT), FALSE)) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDWINDOWPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDWINDOWPROPERTYINFO)));
}

BOOL CProfile::GetMMDWindowPropertyInfo(INT nDisplay, INT &nImagePaneHeight, INT &nImagePaneMinHeight, INT &nCodePaneHeight, INT &nCodePaneMinHeight, LPRECT pHotSpot) CONST
{
	struct {
		INT  nImagePaneHeight[2];
		INT  nCodePaneHeight[2];
		RECT  rHotSpot;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_MMDWINDOWPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(pHotSpot, &sInfo.rHotSpot, sizeof(RECT));
		nImagePaneHeight = sInfo.nImagePaneHeight[0];
		nImagePaneMinHeight = sInfo.nImagePaneHeight[1];
		nCodePaneHeight = sInfo.nCodePaneHeight[0];
		nCodePaneMinHeight = sInfo.nCodePaneHeight[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetPODsFormPropertyInfo(INT nDisplay, CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;

	sInfo.nColor[0] = nTitleColor;
	sInfo.nColor[1] = nItemsColor;
	sInfo.nColor[2] = nTitleBackground;
	sInfo.nColor[3] = nKeysBackground;
	CopyMemory(&sInfo.lfTable[0], plfTitle, (AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	CopyMemory(&sInfo.lfTable[1], plfItems, (AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE)) ? sizeof(LOGFONT) : 0);
	return((AfxIsValidAddress(plfTitle, sizeof(LOGFONT), FALSE) && AfxIsValidAddress(plfItems, sizeof(LOGFONT), FALSE) && nTitleColor != (COLORREF)-1 && nItemsColor != (COLORREF)-1 && nTitleBackground != (COLORREF)-1 && nKeysBackground != (COLORREF)-1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODSFORMPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODSFORMPROPERTYINFO)));
}

BOOL CProfile::GetPODsFormPropertyInfo(INT nDisplay, LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	struct {
		LOGFONT  lfTable[2];
		COLORREF  nColor[4];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_PODSFORMPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(plfTitle, &sInfo.lfTable[0], sizeof(LOGFONT));
		CopyMemory(plfItems, &sInfo.lfTable[1], sizeof(LOGFONT));
		nKeysBackground = sInfo.nColor[3];
		nTitleBackground = sInfo.nColor[2];
		nItemsColor = sInfo.nColor[1];
		nTitleColor = sInfo.nColor[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetScriptWindowPropertyInfo(INT nDisplay, INT nCodePaneHeight, INT nCodePaneMinHeight, INT nImagePaneHeight, INT nImagePaneMinHeight)
{
	struct {
		INT  nCodePaneHeight[2];
		INT  nImagePaneHeight[2];
	} sInfo;

	sInfo.nCodePaneHeight[0] = nCodePaneHeight;
	sInfo.nCodePaneHeight[1] = nCodePaneMinHeight;
	sInfo.nImagePaneHeight[0] = nImagePaneHeight;
	sInfo.nImagePaneHeight[1] = nImagePaneMinHeight;
	return((nCodePaneHeight != -1 && nCodePaneMinHeight != -1 && nImagePaneHeight != -1 && nImagePaneMinHeight != -1) ? SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_SCRIPTWINDOWPROPERTYINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_SCRIPTWINDOWPROPERTYINFO)));
}

BOOL CProfile::GetScriptWindowPropertyInfo(INT nDisplay, INT &nCodePaneHeight, INT &nCodePaneMinHeight, INT &nImagePaneHeight, INT &nImagePaneMinHeight) CONST
{
	struct {
		INT  nCodePaneHeight[2];
		INT  nImagePaneHeight[2];
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QueryDisplayWindowSubKey(nDisplay), STRING(IDS_REG_SUBKEYVALUE_SCRIPTWINDOWPROPERTYINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		nCodePaneHeight = sInfo.nCodePaneHeight[0];
		nCodePaneMinHeight = sInfo.nCodePaneHeight[1];
		nImagePaneHeight = sInfo.nImagePaneHeight[0];
		nImagePaneMinHeight = sInfo.nImagePaneHeight[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetWorkspaceWindowInfo(UINT nState, LPCRECT pRect, CONST CByteArray &nInfo)
{
	struct {
		UINT  nState;
		RECT  rPosition;
	} sInfo;
	CByteArray  nData;

	sInfo.nState = nState;
	CopyRect(&sInfo.rPosition, pRect);
	nData.SetSize(sizeof(sInfo) + nInfo.GetSize());
	if (nData.GetSize() == sizeof(sInfo) + nInfo.GetSize())
	{
		CopyMemory(nData.GetData(), &sInfo, sizeof(sInfo));
		CopyMemory(nData.GetData() + sizeof(sInfo), nInfo.GetData(), nInfo.GetSize());
		return((AfxIsValidAddress(pRect, sizeof(RECT), FALSE)) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_WORKSPACEWINDOWINFO), REG_BINARY, nData.GetData(), (INT)nData.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_WORKSPACEWINDOWINFO)));
	}
	return FALSE;
}

BOOL CProfile::GetWorkspaceWindowInfo(UINT &nState, LPRECT pRect, CByteArray &nInfo) CONST
{
	struct {
		UINT  nState;
		RECT  rPosition;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nData;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_WORKSPACEWINDOWINFO)), nData.SetSize(max(nSize, 0)); nSize > 0 && nData.GetSize() == nSize; )
	{
		if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_WORKSPACEWINDOWINFO), &dwType, nData.GetData(), nSize) == nSize  &&  nData.GetSize() >= sizeof(sInfo))
		{
			for (nInfo.SetSize(nData.GetSize() - sizeof(sInfo)); nInfo.GetSize() == nData.GetSize() - (INT) sizeof(sInfo); )
			{
				CopyMemory(&sInfo, nData.GetData(), sizeof(sInfo));
				CopyMemory(nInfo.GetData(), nData.GetData() + sizeof(sInfo), nInfo.GetSize());
				CopyMemory(pRect, &sInfo.rPosition, sizeof(RECT));
				nState = sInfo.nState;
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetOutputWindowInfo(UINT nState, LPCRECT pRect, CONST CByteArray &nInfo)
{
	struct {
		UINT  nState;
		RECT  rPosition;
	} sInfo;
	CByteArray  nData;

	sInfo.nState = nState;
	CopyRect(&sInfo.rPosition, pRect);
	nData.SetSize(sizeof(sInfo) + nInfo.GetSize());
	if (nData.GetSize() == sizeof(sInfo) + nInfo.GetSize())
	{
		CopyMemory(nData.GetData(), &sInfo, sizeof(sInfo));
		CopyMemory(nData.GetData() + sizeof(sInfo), nInfo.GetData(), nInfo.GetSize());
		return((AfxIsValidAddress(pRect, sizeof(RECT), FALSE)) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_OUTPUTWINDOWINFO), REG_BINARY, nData.GetData(), (INT)nData.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_OUTPUTWINDOWINFO)));
	}
	return FALSE;
}

BOOL CProfile::GetOutputWindowInfo(UINT &nState, LPRECT pRect, CByteArray &nInfo) CONST
{
	struct {
		UINT  nState;
		RECT  rPosition;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nData;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_OUTPUTWINDOWINFO)), nData.SetSize(max(nSize, 0)); nSize > 0 && nData.GetSize() == nSize; )
	{
		if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_OUTPUTWINDOWINFO), &dwType, nData.GetData(), nSize) == nSize  &&  nData.GetSize() >= sizeof(sInfo))
		{
			for (nInfo.SetSize(nData.GetSize() - sizeof(sInfo)); nInfo.GetSize() == nData.GetSize() - (INT) sizeof(sInfo); )
			{
				CopyMemory(&sInfo, nData.GetData(), sizeof(sInfo));
				CopyMemory(nInfo.GetData(), nData.GetData() + sizeof(sInfo), nInfo.GetSize());
				CopyMemory(pRect, &sInfo.rPosition, sizeof(RECT));
				nState = sInfo.nState;
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

BOOL CProfile::SetZoomWindowInfo(UINT nState, LPCRECT pRect)
{
	struct {
		UINT  nState;
		RECT  rPosition;
	} sInfo;

	sInfo.nState = nState;
	CopyMemory(&sInfo.rPosition, pRect, (AfxIsValidAddress(pRect, sizeof(RECT))) ? sizeof(RECT) : 0);
	return((nState != (UINT)-1 && AfxIsValidAddress(pRect, sizeof(RECT), FALSE)) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_ZOOMWINDOWINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_ZOOMWINDOWINFO)));
}

BOOL CProfile::GetZoomWindowInfo(UINT &nState, LPRECT pRect) CONST
{
	struct {
		UINT  nState;
		RECT  rPosition;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_ZOOMWINDOWINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(pRect, &sInfo.rPosition, sizeof(RECT));
		nState = sInfo.nState;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetMimicsObjectsToolBarInfo(LPCRECT pRect, BOOL bShow)
{
	struct {
		RECT  rPosition;
		BOOL  bShow;
	} sInfo;

	sInfo.bShow = bShow;
	CopyMemory(&sInfo.rPosition, pRect, (AfxIsValidAddress(pRect, sizeof(RECT))) ? sizeof(RECT) : 0);
	return((AfxIsValidAddress(pRect, sizeof(RECT), FALSE)) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSOBJECTSTOOLBARINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSOBJECTSTOOLBARINFO)));
}

BOOL CProfile::GetMimicsObjectsToolBarInfo(LPRECT pRect, BOOL &bShow) CONST
{
	struct {
		RECT  rPosition;
		BOOL  bShow;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSOBJECTSTOOLBARINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(pRect, &sInfo.rPosition, sizeof(RECT));
		bShow = sInfo.bShow;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetTCStepsToolBarInfo(LPCRECT pRect, BOOL bShow)
{
	struct {
		RECT  rPosition;
		BOOL  bShow;
	} sInfo;

	sInfo.bShow = bShow;
	CopyMemory(&sInfo.rPosition, pRect, (AfxIsValidAddress(pRect, sizeof(RECT))) ? sizeof(RECT) : 0);
	return((AfxIsValidAddress(pRect, sizeof(RECT), FALSE)) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TCSTEPSTOOLBARINFO), REG_BINARY, (CONST BYTE *) &sInfo, sizeof(sInfo)) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TCSTEPSTOOLBARINFO)));
}

BOOL CProfile::GetTCStepsToolBarInfo(LPRECT pRect, BOOL &bShow) CONST
{
	struct {
		RECT  rPosition;
		BOOL  bShow;
	} sInfo;
	DWORD  dwType;

	if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_TCSTEPSTOOLBARINFO), &dwType, (LPBYTE)&sInfo, sizeof(sInfo)) == sizeof(sInfo))
	{
		CopyMemory(pRect, &sInfo.rPosition, sizeof(RECT));
		bShow = sInfo.bShow;
		return TRUE;
	}
	return FALSE;
}

BOOL CProfile::SetMimicsGroupsInfo(CONST CByteArray &nGroupsInfo)
{
	return((nGroupsInfo.GetSize() > 0) ? SetUserInfo(QueryMimicsGroupsSubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSGROUPSINFO), REG_BINARY, nGroupsInfo.GetData(), (INT)nGroupsInfo.GetSize()) : SetUserInfo(QueryMimicsGroupsSubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSGROUPSINFO)));
}

BOOL CProfile::GetMimicsGroupsInfo(CByteArray &nGroupsInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryMimicsGroupsSubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSGROUPSINFO)), nGroupsInfo.SetSize(max(nSize, 0)); nSize > 0 && nGroupsInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryMimicsGroupsSubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSGROUPSINFO), &dwType, nGroupsInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetMimicsTestInfo(CONST CByteArray &nTestInfo)
{
	return((nTestInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSTESTINFO), REG_BINARY, nTestInfo.GetData(), (INT)nTestInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSTESTINFO)));
}

BOOL CProfile::GetMimicsTestInfo(CByteArray &nTestInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSTESTINFO)), nTestInfo.SetSize(max(nSize, 0)); nSize > 0 && nTestInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_MIMICSTESTINFO), &dwType, nTestInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetPrintProfileInfo(CONST CByteArray &nProfileInfo)
{
	return((nProfileInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_PRINTPROFILEINFO), REG_BINARY, nProfileInfo.GetData(), (INT)nProfileInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_PRINTPROFILEINFO)));
}

BOOL CProfile::GetPrintProfileInfo(CByteArray &nProfileInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_PRINTPROFILEINFO)), nProfileInfo.SetSize(max(nSize, 0)); nSize > 0 && nProfileInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_PRINTPROFILEINFO), &dwType, nProfileInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetCompileOptions(LPCTSTR pszCompilerPath, LPCTSTR pszLinkerPath, LPCTSTR pszPlatForm, LPCTSTR pszIncludeDirectory, LPCTSTR pszLibraryDirectory, LPCTSTR pszDPLOptions, LPCTSTR pszMDLOptions, LPCTSTR pszTPLOptions)
{
	return((SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILERFILENAME), pszCompilerPath) && SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_LINKERFILENAME), pszLinkerPath) && SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_PLATFORMTYPE), pszPlatForm) && SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_INCLUDEDIRECTORY), pszIncludeDirectory) && SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_LIBRARYDIRECTORY), pszLibraryDirectory) && SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEDPLOPTIONS), pszDPLOptions) && SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEMDLOPTIONS), pszMDLOptions) && SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILETPLOPTIONS), pszTPLOptions)) ? TRUE : FALSE);
}

BOOL CProfile::GetCompileOptions(CString &szCompilerPath, CString &szLinkerPath, CString &szPlatForm, CString &szIncludeDirectory, CString &szLibraryDirectory, CString &szDPLOptions, CString &szMDLOptions, CString &szTPLOptions) CONST
{
	return((GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILERFILENAME), szCompilerPath) && GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_LINKERFILENAME), szLinkerPath) && GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_PLATFORMTYPE), szPlatForm) && GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_INCLUDEDIRECTORY), szIncludeDirectory) && GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_LIBRARYDIRECTORY), szLibraryDirectory) && GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEDPLOPTIONS), szDPLOptions) && GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEMDLOPTIONS), szMDLOptions) && GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILETPLOPTIONS), szTPLOptions)) ? TRUE : FALSE);
}

BOOL CProfile::SetCompileDirectivesInfo(CONST CByteArray &nDirectivesInfo)
{
	return((nDirectivesInfo.GetSize() > 0) ? SetUserInfo(QueryDatabaseSubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEDIRECTIVESINFO), REG_BINARY, nDirectivesInfo.GetData(), (INT)nDirectivesInfo.GetSize()) : SetUserInfo(QueryDatabaseSubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEDIRECTIVESINFO)));
}

BOOL CProfile::GetCompileDirectivesInfo(CByteArray &nDirectivesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QueryDatabaseSubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEDIRECTIVESINFO)), nDirectivesInfo.SetSize(max(nSize, 0)); nSize > 0 && nDirectivesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QueryDatabaseSubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEDIRECTIVESINFO), &dwType, nDirectivesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetCompileBatchesInfo(CONST CByteArray &nBatchesInfo)
{
	return((nBatchesInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEBATCHESINFO), REG_BINARY, nBatchesInfo.GetData(), (INT)nBatchesInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEBATCHESINFO)));
}

BOOL CProfile::GetCompileBatchesInfo(CByteArray &nBatchesInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEBATCHESINFO)), nBatchesInfo.SetSize(max(nSize, 0)); nSize > 0 && nBatchesInfo.GetSize() == nSize; ) break;
	return((nSize <= 0 || GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_COMPILEBATCHESINFO), &dwType, nBatchesInfo.GetData(), nSize) == nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetAssistantCharacterInfo(LPCTSTR pszName, CONST POINT *pPosition, BOOL bVisible, BOOL bSpeak, LONG lSpeed, LONG lPitch, LONG lVolume, BOOL bWordBalloon, BOOL bSoundEffects)
{
	struct {
		POINT  pt;
		BOOL  bVisible;
		BOOL  bSpeak;
		LONG  lSpeed;
		LONG  lPitch;
		LONG  lVolume;
		BOOL  bWordBalloon;
		BOOL  bSoundEffects;
	} sInfo;
	CByteArray  nData;

	sInfo.bSpeak = bSpeak;
	sInfo.lSpeed = lSpeed;
	sInfo.lPitch = lPitch;
	sInfo.lVolume = lVolume;
	sInfo.bVisible = bVisible;
	sInfo.bWordBalloon = bWordBalloon;
	sInfo.bSoundEffects = bSoundEffects;
	sInfo.pt.x = pPosition->x;
	sInfo.pt.y = pPosition->y;
	nData.SetSize(sizeof(sInfo) + (lstrlen(pszName) + 1)*sizeof(TCHAR));
	CopyMemory(nData.GetData(), &sInfo, sizeof(sInfo));
	CopyMemory(nData.GetData() + sizeof(sInfo), pszName, (lstrlen(pszName) + 1)*sizeof(TCHAR));
	return((AfxIsValidString(pszName) && AfxIsValidAddress(pPosition, sizeof(POINT), FALSE)) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_ASSISTANTCHARACTERINFO), REG_BINARY, nData.GetData(), (INT)nData.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_ASSISTANTCHARACTERINFO)));
}

BOOL CProfile::GetAssistantCharacterInfo(CString &szName, POINT *pPosition, BOOL &bVisible, BOOL &bSpeak, LONG &lSpeed, LONG &lPitch, LONG &lVolume, BOOL &bWordBalloon, BOOL &bSoundEffects) CONST
{
	struct {
		POINT  pt;
		BOOL  bVisible;
		BOOL  bSpeak;
		LONG  lSpeed;
		LONG  lPitch;
		LONG  lVolume;
		BOOL  bWordBalloon;
		BOOL  bSoundEffects;
	} sInfo;
	INT  nSize;
	DWORD  dwType;
	CByteArray  nData;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_ASSISTANTCHARACTERINFO)), nData.SetSize(max(nSize, 0)); nSize > 0 && nData.GetSize() == nSize; )
	{
		if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_ASSISTANTCHARACTERINFO), &dwType, nData.GetData(), nSize) == nSize  &&  nSize > sizeof(sInfo))
		{
			CopyMemory(&sInfo, nData.GetData(), sizeof(sInfo));
			CopyMemory(pPosition, &sInfo.pt, sizeof(POINT));
			szName = (LPCTSTR)(nData.GetData() + sizeof(sInfo));
			bSoundEffects = sInfo.bSoundEffects;
			bWordBalloon = sInfo.bWordBalloon;
			bVisible = sInfo.bVisible;
			lVolume = sInfo.lVolume;
			lPitch = sInfo.lPitch;
			lSpeed = sInfo.lSpeed;
			bSpeak = sInfo.bSpeak;
			return TRUE;
		}
		break;
	}
	return((!nSize) ? TRUE : FALSE);
}

BOOL CProfile::SetRecentDocuments(CONST CByteArray &nInfo)
{
	return((nInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_RECENTDOCUMENTS), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_RECENTDOCUMENTS)));
}

BOOL CProfile::GetRecentDocuments(CByteArray &nInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_RECENTDOCUMENTS)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; nSize = -1)
	{
		if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_RECENTDOCUMENTS), &dwType, nInfo.GetData(), nSize) == nSize) break;
		continue;
	}
	return((nSize >= 0) ? TRUE : FALSE);
}

BOOL CProfile::SetRecentDatabases(CONST CByteArray &nInfo)
{
	return((nInfo.GetSize() > 0) ? SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_RECENTDATABASES), REG_BINARY, nInfo.GetData(), (INT)nInfo.GetSize()) : SetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_RECENTDATABASES)));
}

BOOL CProfile::GetRecentDatabases(CByteArray &nInfo) CONST
{
	INT  nSize;
	DWORD  dwType;

	for (nSize = GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_RECENTDATABASES)), nInfo.SetSize(max(nSize, 0)); nSize > 0 && nInfo.GetSize() == nSize; nSize = -1)
	{
		if (GetUserInfo(QuerySubKey(), STRING(IDS_REG_SUBKEYVALUE_RECENTDATABASES), &dwType, nInfo.GetData(), nSize) == nSize) break;
		continue;
	}
	return((nSize >= 0) ? TRUE : FALSE);
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

BOOL CProfile::DeleteDisplayWindowInfo(INT nDisplay)
{
	return DeleteSubKey(QueryDisplayWindowSubKey(nDisplay));
}

BOOL CProfile::DeleteDatabaseInfo(LPCTSTR pszDatabase)
{
	return DeleteSubKey(QueryDatabaseSubKey(pszDatabase));
}

BOOL CProfile::DeleteMimicsGroupsInfo()
{
	return DeleteSubKey(QueryMimicsGroupsSubKey());
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

CString CProfile::QueryDisplayAreaSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QueryDatabaseSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_DISPLAYAREA);
	return szSubKey;
}

CString CProfile::QueryDisplayWindowSubKey(INT nDisplay) CONST
{
	CString  szSubKey[2];

	szSubKey[0].Format(STRING(IDS_REG_SUBKEYPART_DISPLAYFOLDER), nDisplay);
	szSubKey[1] = QueryDisplayAreaSubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + szSubKey[0];
	return szSubKey[1];
}

CString CProfile::QueryDatabaseSubKey(LPCTSTR pszDatabase) CONST
{
	CString  szSubKey;

	szSubKey = QuerySubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER) + GetAccountSpacecraftName() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += (!AfxIsValidString(pszDatabase)) ? (LPCTSTR)GetAccountDatabase() : pszDatabase;
	return szSubKey;
}

CString CProfile::QueryMimicsGroupsSubKey() CONST
{
	CString  szSubKey;

	szSubKey = QuerySubKey() + STRING(IDS_REG_SUBKEYPART_DELIMITER);
	szSubKey += STRING(IDS_REG_SUBKEYPART_MIMICSGROUPS);
	return szSubKey;
}
