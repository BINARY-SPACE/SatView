// MIMICSTEXTCTL.CPP : Mimics Text Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics text
// control related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////////////////////////////////////////////////////////////
// CMimicsTextCtrlDispatchDriver properties

VOID CMimicsTextCtrlDispatchDriver::SetText(LPCTSTR pszText)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TEXT));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszText);
}

CString CMimicsTextCtrlDispatchDriver::GetText() CONST
{
	CString  szText;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TEXT));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szText);
	return szText;
}

VOID CMimicsTextCtrlDispatchDriver::SetMode(INT nMode)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_MODE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nMode);
}

INT CMimicsTextCtrlDispatchDriver::GetMode() CONST
{
	INT  nMode;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_MODE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nMode);
	return nMode;
}

VOID CMimicsTextCtrlDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTextCtrlDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsTextCtrlDispatchDriver::SetBackgroundColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BACKGROUNDCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTextCtrlDispatchDriver::GetBackgroundColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BACKGROUNDCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextCtrlDispatchDriver operations

BOOL CMimicsTextCtrlDispatchDriver::SetFont(CONST LOGFONT *pFont)
{
	BOOL  bFont;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETFONT));
	static BYTE  pParameters[] = VTS_PVARIANT;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bFont, pParameters, pFont);
	return bFont;
}

BOOL CMimicsTextCtrlDispatchDriver::GetFont(LOGFONT *pFont) CONST
{
	BOOL  bFont;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETFONT));
	static BYTE  pParameters[] = VTS_PVARIANT;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bFont, pParameters, pFont);
	return bFont;
}

VOID CMimicsTextCtrlDispatchDriver::AlignLeft()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNLEFT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextCtrlDispatchDriver::AlignCenter()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNCENTER));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextCtrlDispatchDriver::AlignRight()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNRIGHT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextCtrlDispatchDriver::AlignVertical(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNVERTICAL));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextCtrlDispatchDriver::IsLeftAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISLEFTALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextCtrlDispatchDriver::IsCenterAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCENTERALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextCtrlDispatchDriver::IsRightAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISRIGHTALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextCtrlDispatchDriver::IsVerticalAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISVERTICALALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

VOID CMimicsTextCtrlDispatchDriver::LeftToRightReading()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_LEFTTORIGHTREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextCtrlDispatchDriver::TopToBottomReading()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_TOPTOBOTTOMREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsTextCtrlDispatchDriver::IsLeftToRightReading() CONST
{
	BOOL  bReading;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISLEFTTORIGHTREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bReading, (const BYTE *)NULL);
	return bReading;
}

BOOL CMimicsTextCtrlDispatchDriver::IsTopToBottomReading() CONST
{
	BOOL  bReading;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISTOPTOBOTTOMREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bReading, (const BYTE *)NULL);
	return bReading;
}

VOID CMimicsTextCtrlDispatchDriver::SetTabChars(INT nChars)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETTABCHARS));
	static BYTE  pParameters[] = VTS_I4;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nChars);
}

INT CMimicsTextCtrlDispatchDriver::GetTabChars() CONST
{
	INT  nChars;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETTABCHARS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nChars, (const BYTE *)NULL);
	return nChars;
}

VOID CMimicsTextCtrlDispatchDriver::WrapWords(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_WRAPWORDS));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextCtrlDispatchDriver::IsWrappingWords() CONST
{
	BOOL  bEnable;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISWRAPPINGWORDS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bEnable, (const BYTE *)NULL);
	return bEnable;
}

VOID CMimicsTextCtrlDispatchDriver::SingleLine(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SINGLELINE));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextCtrlDispatchDriver::IsSingleLine() CONST
{
	BOOL  bEnable;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISSINGLELINE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bEnable, (const BYTE *)NULL);
	return bEnable;
}


IMPLEMENT_DYNCREATE(CMimicsTextCtrl, CMimicsCtrl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsTextCtrl, CMimicsCtrl)
	//{{AFX_MSG_MAP(CMimicsTextCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMimicsTextCtrl, CMimicsCtrl)
	//{{AFX_DISPATCH_MAP(CMimicsTextCtrl)
	DISP_PROPERTY_EX(CMimicsTextCtrl, "Text", GetText, SetText, VT_BSTR)
	DISP_PROPERTY_EX(CMimicsTextCtrl, "Mode", GetMode, SetMode, VT_I4)
	DISP_PROPERTY_EX(CMimicsTextCtrl, "Color", GetColor, SetColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsTextCtrl, "BackgroundColor", GetBackgroundColor, SetBackgroundColor, VT_COLOR)
	DISP_FUNCTION(CMimicsTextCtrl, "SetFont", SetFont, VT_BOOL, VTS_PVARIANT)
	DISP_FUNCTION(CMimicsTextCtrl, "GetFont", GetFont, VT_BOOL, VTS_PVARIANT)
	DISP_FUNCTION(CMimicsTextCtrl, "AlignLeft", AlignLeft, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "AlignCenter", AlignCenter, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "AlignRight", AlignRight, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "AlignVertical", AlignVertical, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CMimicsTextCtrl, "IsLeftAligned", IsLeftAligned, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "IsCenterAligned", IsCenterAligned, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "IsRightAligned", IsRightAligned, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "IsVerticalAligned", IsVerticalAligned, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "LeftToRightReading", LeftToRightReading, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "TopToBottomReading", TopToBottomReading, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "IsLeftToRightReading", IsLeftToRightReading, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "IsTopToBottomReading", IsTopToBottomReading, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "SetTabChars", SetTabChars, VT_EMPTY, VTS_I4)
	DISP_FUNCTION(CMimicsTextCtrl, "GetTabChars", GetTabChars, VT_I4, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "WrapWords", WrapWords, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CMimicsTextCtrl, "IsWrappingWords", IsWrappingWords, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsTextCtrl, "SingleLine", SingleLine, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CMimicsTextCtrl, "IsSingleLine", IsSingleLine, VT_BOOL, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMimicsTextCtrl, CMimicsCtrl)
	//{{AFX_EVENT_MAP(CMimicsTextCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMimicsTextCtrl, 3)
	PROPPAGEID(CMimicsTextGeneralPage::guid)
	PROPPAGEID(CMimicsTextFontPage::guid)
	PROPPAGEID(CMimicsTextOutlinePage::guid)
END_PROPPAGEIDS(CMimicsTextCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsTextCtrl, "MIMICS.MimicsTextCtrl.1", 0xd9b0da0e, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMimicsTextCtrl, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor)

/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMimicsText = { 0xd9b0da0c,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };
const IID BASED_CODE IID_DMimicsTextEvents = { 0xd9b0da0d,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };

/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE  dwMimicsTextOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMimicsTextCtrl, IDS_MIMICSTEXTCTRL_DESCRIPTIVENAME, dwMimicsTextOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextCtrl::CMimicsTextCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsTextCtrl

BOOL CMimicsTextCtrl::CMimicsTextCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterControlClass(AfxGetInstanceHandle(), m_clsid, m_lpszProgID, IDS_MIMICSTEXTCTRL_DESCRIPTIVENAME, IDB_MIMICSTEXTCTRL, afxRegApartmentThreading, dwMimicsTextOleMisc, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor) : AfxOleUnregisterClass(m_clsid, m_lpszProgID));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextCtrl

CMimicsTextCtrl::CMimicsTextCtrl() : CMimicsCtrl()
{
	m_szType = STRING(IDS_MIMICSTEXTCTRL_TYPE);
	InitializeIIDs(&IID_DMimicsText, &IID_DMimicsTextEvents);
	InitializeProps();
}

CMimicsTextCtrl::~CMimicsTextCtrl()
{
	DeleteObject(m_hFont);
}

VOID CMimicsTextCtrl::InitializeProps()
{
	SIZE  size;
	HFONT  hOldFont;
	LOGFONT  lfFont;
	TEXTMETRIC  tmFont;
	CFontTools  cFontTools;
	CClientDC  cDC(NULL);

	for (m_szText = STRING(IDS_MIMICSTEXTCTRL_TYPE); (m_hFont = (cFontTools.QueryDefaultFont(&lfFont)) ? CreateFontIndirect(&lfFont) : (HFONT)NULL); )
	{
		if ((hOldFont = (HFONT)SelectObject(cDC.GetSafeHdc(), m_hFont)))
		{
			if (GetTextMetrics(cDC.GetSafeHdc(), &tmFont))
			{
				GetTextExtentPoint(cDC.GetSafeHdc(), m_szText, m_szText.GetLength(), &size);
				SetInitialSize(size.cx + tmFont.tmMaxCharWidth, size.cy + tmFont.tmDescent);
			}
			SelectObject(cDC.GetSafeHdc(), hOldFont);
		}
		break;
	}
	m_nMode = TRANSPARENT;
	m_nColor = GetSysColor(COLOR_WINDOWTEXT);
	m_nBkColor = GetSysColor(COLOR_WINDOW);
	m_nFormat = DT_LEFT | DT_NOPREFIX;
	m_bReading = FALSE;
	m_nTabs = -1;
}

void CMimicsTextCtrl::SetText(LPCTSTR pszText)
{
	if (m_szText != pszText)
	{
		m_szText = pszText;
		Refresh();
	}
}

BSTR CMimicsTextCtrl::GetText() CONST
{
	return m_szText.AllocSysString();
}

void CMimicsTextCtrl::SetMode(LONG nMode)
{
	if (nMode != m_nMode)
	{
		m_nMode = nMode;
		Refresh();
	}
}

LONG CMimicsTextCtrl::GetMode() CONST
{
	return m_nMode;
}

void CMimicsTextCtrl::SetColor(OLE_COLOR nColor)
{
	if (nColor != m_nColor)
	{
		m_nColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsTextCtrl::GetColor() CONST
{
	return m_nColor;
}

void CMimicsTextCtrl::SetBackgroundColor(OLE_COLOR nColor)
{
	if (nColor != m_nBkColor)
	{
		m_nBkColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsTextCtrl::GetBackgroundColor() CONST
{
	return m_nBkColor;
}

BOOL CMimicsTextCtrl::SetFont(VARIANT *pFont)
{
	HFONT  hFont;
	LOGFONT  lfFont;

	if (GetObject(m_hFont, sizeof(LOGFONT), &lfFont))
	{
		if (memcmp(pFont, &lfFont, sizeof(LOGFONT)) != 0)
		{
			if ((hFont = CreateFontIndirect((CONST LOGFONT *) pFont)))
			{
				DeleteObject(m_hFont);
				m_hFont = hFont;
				Refresh();
				return TRUE;
			}
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsTextCtrl::GetFont(VARIANT *pFont) CONST
{
	LOGFONT  lfFont;

	if (GetObject(m_hFont, sizeof(LOGFONT), &lfFont))
	{
		CopyMemory(pFont, &lfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

void CMimicsTextCtrl::AlignLeft()
{
	if (m_nFormat & (DT_CENTER | DT_RIGHT))
	{
		m_nFormat &= ~(DT_CENTER | DT_RIGHT);
		m_nFormat |= DT_LEFT;
		Refresh();
	}
}

void CMimicsTextCtrl::AlignCenter()
{
	if (!(m_nFormat & DT_CENTER))
	{
		m_nFormat &= ~(DT_LEFT | DT_RIGHT);
		m_nFormat |= DT_CENTER;
		Refresh();
	}
}

void CMimicsTextCtrl::AlignRight()
{
	if (!(m_nFormat & DT_RIGHT))
	{
		m_nFormat &= ~(DT_LEFT | DT_CENTER);
		m_nFormat |= DT_RIGHT;
		Refresh();
	}
}

void CMimicsTextCtrl::AlignVertical(BOOL bEnable)
{
	if ((!bEnable && (m_nFormat & DT_VCENTER)) || (bEnable  &&  !(m_nFormat & DT_VCENTER)))
	{
		m_nFormat = (!bEnable) ? (m_nFormat & ~DT_VCENTER) : (m_nFormat | DT_VCENTER);
		Refresh();
	}
}

BOOL CMimicsTextCtrl::IsLeftAligned() CONST
{
	return((m_nFormat & (DT_CENTER | DT_RIGHT)) ? !TRUE : !FALSE);
}

BOOL CMimicsTextCtrl::IsCenterAligned() CONST
{
	return((m_nFormat & DT_CENTER) ? TRUE : FALSE);
}

BOOL CMimicsTextCtrl::IsRightAligned() CONST
{
	return((m_nFormat & DT_RIGHT) ? TRUE : FALSE);
}

BOOL CMimicsTextCtrl::IsVerticalAligned() CONST
{
	return((m_nFormat & DT_VCENTER) ? TRUE : FALSE);
}

void CMimicsTextCtrl::LeftToRightReading()
{
	if (m_bReading)
	{
		m_bReading = FALSE;
		Refresh();
	}
}

void CMimicsTextCtrl::TopToBottomReading()
{
	if (!m_bReading)
	{
		m_bReading = TRUE;
		Refresh();
	}
}

BOOL CMimicsTextCtrl::IsLeftToRightReading() CONST
{
	return !m_bReading;
}

BOOL CMimicsTextCtrl::IsTopToBottomReading() CONST
{
	return m_bReading;
}

void CMimicsTextCtrl::SetTabChars(LONG nChars)
{
	if (nChars != m_nTabs)
	{
		m_nTabs = nChars;
		Refresh();
	}
}

LONG CMimicsTextCtrl::GetTabChars() CONST
{
	return m_nTabs;
}

void CMimicsTextCtrl::WrapWords(BOOL bEnable)
{
	if ((bEnable  &&  !(m_nFormat & DT_WORDBREAK)) || (!bEnable && (m_nFormat & DT_WORDBREAK)))
	{
		m_nFormat = (bEnable) ? (m_nFormat | DT_WORDBREAK) : (m_nFormat & ~DT_WORDBREAK);
		Refresh();
	}
}

BOOL CMimicsTextCtrl::IsWrappingWords() CONST
{
	return((m_nFormat & DT_WORDBREAK) ? TRUE : FALSE);
}

void CMimicsTextCtrl::SingleLine(BOOL bEnable)
{
	if ((bEnable  &&  !(m_nFormat & DT_SINGLELINE)) || (!bEnable && (m_nFormat & DT_SINGLELINE)))
	{
		m_nFormat = (bEnable) ? (m_nFormat | DT_SINGLELINE) : (m_nFormat & ~DT_SINGLELINE);
		Refresh();
	}
}

BOOL CMimicsTextCtrl::IsSingleLine() CONST
{
	return((m_nFormat & DT_SINGLELINE) ? TRUE : FALSE);
}

VOID CMimicsTextCtrl::DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape)
{
	INT  nPos;
	INT  nMode;
	CRect  rText;
	HFONT  hOldFont;
	COLORREF  nColor;
	COLORREF  nBkColor;
	TEXTMETRIC  tmFont;

	nMode = SetBkMode(hDC, m_nMode);
	nColor = SetTextColor(hDC, GetNearestColor(hDC, m_nColor));
	nBkColor = SetBkColor(hDC, GetNearestColor(hDC, m_nBkColor));
	if ((hOldFont = (HFONT)SelectObject(hDC, m_hFont)) != (HFONT)NULL)
	{
		for (nPos = (GetTextMetrics(hDC, &tmFont)) ? 0 : -1; (!nPos || m_bReading) && nPos < m_szText.GetLength() && nPos >= 0; nPos++)
		{
			DrawText(hDC, (!m_bReading) ? m_szText : m_szText.Mid(nPos, 1), -1, (rText = CRect(pRect->left, pRect->top + nPos*tmFont.tmHeight, pRect->right, pRect->bottom)), ((m_nTabs > 0) ? ((m_nFormat & 0xFFFF00FF) | ((m_nTabs & 0xFF) << 8) | DT_TABSTOP | DT_EXPANDTABS) : m_nFormat) | ((bShape) ? DT_CALCRECT : 0));
			FillRect(hDC, (bShape) ? rText : CRect(0, 0, 0, 0), (HBRUSH)GetStockObject(WHITE_BRUSH));
			if ((m_nFormat & DT_SINGLELINE) || !m_bReading) break;
		}
		SelectObject(hDC, hOldFont);
	}
	SetTextColor(hDC, nColor);
	SetBkColor(hDC, nBkColor);
	SetBkMode(hDC, nMode);
}

void CMimicsTextCtrl::DoPropExchange(CPropExchange *pPX)
{
	ExchangeVersion(pPX, MAKELONG(CMimicsApp::wAppVerMinor, CMimicsApp::wAppVerMajor));
	CMimicsCtrl::DoPropExchange(pPX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextCtrl message handlers
