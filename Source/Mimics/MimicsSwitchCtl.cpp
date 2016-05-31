// MIMICSSWITCHCTL.CPP : Mimics Switch Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics switch
// control related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/06/28 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchCtrlDispatchDriver properties

VOID CMimicsSwitchCtrlDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsSwitchCtrlDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchCtrlDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetFrameColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMECOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchCtrlDispatchDriver::GetFrameColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMECOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetInteriorFrameColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORFRAMECOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchCtrlDispatchDriver::GetInteriorFrameColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORFRAMECOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetCenterColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchCtrlDispatchDriver::GetCenterColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetInteriorCenterColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCENTERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchCtrlDispatchDriver::GetInteriorCenterColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCENTERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetBarColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchCtrlDispatchDriver::GetBarColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetStubsColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchCtrlDispatchDriver::GetStubsColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchCtrlDispatchDriver::GetThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetFrameThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMETHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchCtrlDispatchDriver::GetFrameThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMETHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetCenterThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchCtrlDispatchDriver::GetCenterThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetBarThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchCtrlDispatchDriver::GetBarThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchCtrlDispatchDriver::SetStubsThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchCtrlDispatchDriver::GetStubsThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchCtrlDispatchDriver operations

VOID CMimicsSwitchCtrlDispatchDriver::Open()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_OPEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchCtrlDispatchDriver::IsOpen() CONST
{
	BOOL  bOpen;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISOPEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bOpen, (const BYTE *)NULL);
	return bOpen;
}

BOOL CMimicsSwitchCtrlDispatchDriver::IsClosed() CONST
{
	BOOL  bClosed;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCLOSED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bClosed, (const BYTE *)NULL);
	return bClosed;
}

VOID CMimicsSwitchCtrlDispatchDriver::Close()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_CLOSE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsSwitchCtrlDispatchDriver::Pos1()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS1));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchCtrlDispatchDriver::IsPos1() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS1));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 0) ? TRUE : FALSE);
}

VOID CMimicsSwitchCtrlDispatchDriver::Pos2()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS2));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchCtrlDispatchDriver::IsPos2() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS2));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 1) ? TRUE : FALSE);
}

VOID CMimicsSwitchCtrlDispatchDriver::Pos3()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS3));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchCtrlDispatchDriver::IsPos3() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS3));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 2) ? TRUE : FALSE);
}

VOID CMimicsSwitchCtrlDispatchDriver::Broken()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_BROKEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchCtrlDispatchDriver::IsBroken() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISBROKEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == -1) ? TRUE : FALSE);
}


IMPLEMENT_DYNCREATE(CMimicsSwitchCtrl, CMimicsCtrl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsSwitchCtrl, CMimicsCtrl)
	//{{AFX_MSG_MAP(CMimicsSwitchCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMimicsSwitchCtrl, CMimicsCtrl)
	//{{AFX_DISPATCH_MAP(CMimicsSwitchCtrl)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "Style", GetStyle, SetStyle, VT_I4)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "Color", GetColor, SetColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "FrameColor", GetFrameColor, SetFrameColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "InteriorFrameColor", GetInteriorFrameColor, SetInteriorFrameColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "CenterColor", GetCenterColor, SetCenterColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "InteriorCenterColor", GetInteriorCenterColor, SetInteriorCenterColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "BarColor", GetBarColor, SetBarColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "StubsColor", GetStubsColor, SetStubsColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "Thickness", GetThickness, SetThickness, VT_I4)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "FrameThickness", GetFrameThickness, SetFrameThickness, VT_I4)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "CenterThickness", GetCenterThickness, SetCenterThickness, VT_I4)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "BarThickness", GetBarThickness, SetBarThickness, VT_I4)
	DISP_PROPERTY_EX(CMimicsSwitchCtrl, "StubsThickness", GetStubsThickness, SetStubsThickness, VT_I4)
	DISP_FUNCTION(CMimicsSwitchCtrl, "Open", Open, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "IsOpen", IsOpen, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "IsClosed", IsClosed, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "Close", Close, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "Pos1", Pos1, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "IsPos1", IsPos1, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "Pos2", Pos2, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "IsPos2", IsPos2, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "Pos3", Pos3, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "IsPos3", IsPos3, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "Broken", Broken, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsSwitchCtrl, "IsBroken", IsBroken, VT_BOOL, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMimicsSwitchCtrl, CMimicsCtrl)
	//{{AFX_EVENT_MAP(CMimicsSwitchCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMimicsSwitchCtrl, 2)
	PROPPAGEID(CMimicsSwitchGeneralPage::guid)
	PROPPAGEID(CMimicsSwitchOutlinePage::guid)
END_PROPPAGEIDS(CMimicsSwitchCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsSwitchCtrl, "MIMICS.MimicsSwitchCtrl.1", 0xd9b0da09, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMimicsSwitchCtrl, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor)

/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMimicsSwitch = { 0xd9b0da07,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };
const IID BASED_CODE IID_DMimicsSwitchEvents = { 0xd9b0da08,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };

/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE  dwMimicsSwitchOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMimicsSwitchCtrl, IDS_MIMICSSWITCHCTRL_DESCRIPTIVENAME, dwMimicsSwitchOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchCtrl::CMimicsSwitchCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsSwitchCtrl

BOOL CMimicsSwitchCtrl::CMimicsSwitchCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterControlClass(AfxGetInstanceHandle(), m_clsid, m_lpszProgID, IDS_MIMICSSWITCHCTRL_DESCRIPTIVENAME, IDB_MIMICSSWITCHCTRL, afxRegApartmentThreading, dwMimicsSwitchOleMisc, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor) : AfxOleUnregisterClass(m_clsid, m_lpszProgID));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchCtrl

CMimicsSwitchCtrl::CMimicsSwitchCtrl() : CMimicsCtrl()
{
	m_szType = STRING(IDS_MIMICSSWITCHCTRL_TYPE);
	SetInitialSize((m_sizeCtrl.cx = MIMICSSWITCHCTRL_DEFAULT_CX), (m_sizeCtrl.cy = MIMICSSWITCHCTRL_DEFAULT_CY));
	InitializeIIDs(&IID_DMimicsSwitch, &IID_DMimicsSwitchEvents);
	InitializeProps();
}

void CMimicsSwitchCtrl::InitializeProps()
{
	m_nStyle = MIMICSSWITCHCTRL_STYLE_SIMPLE | MIMICSSWITCHCTRL_STYLE_STUBS | MIMICSSWITCHCTRL_STYLE_OPENCLOSE;
	m_nColor = m_nBarColor = m_nStubsColor = m_nFrameColor[0] = m_nCenterColor[0] = TranslateColor(VGA_COLOR_BLACK);
	m_nWidth = m_nBarWidth = m_nStubsWidth = m_nFrameWidth = m_nCenterWidth = 1;
	m_nCenterColor[1] = GetSysColor(COLOR_WINDOW);
	m_nFrameColor[1] = GetSysColor(COLOR_WINDOW);
	m_nBarWidth++;
	m_nStatus = 0;
}

void CMimicsSwitchCtrl::SetStyle(LONG nStyle)
{
	if (nStyle != m_nStyle)
	{
		m_nStyle = nStyle;
		Refresh();
	}
}

LONG CMimicsSwitchCtrl::GetStyle() CONST
{
	return m_nStyle;
}

void CMimicsSwitchCtrl::SetColor(OLE_COLOR nColor)
{
	if (nColor != m_nColor)
	{
		m_nColor = m_nBarColor = m_nStubsColor = m_nFrameColor[0] = m_nCenterColor[0] = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsSwitchCtrl::GetColor() CONST
{
	return m_nColor;
}

void CMimicsSwitchCtrl::SetFrameColor(OLE_COLOR nColor)
{
	if (nColor != m_nFrameColor[0])
	{
		m_nFrameColor[0] = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsSwitchCtrl::GetFrameColor() CONST
{
	return m_nFrameColor[0];
}

void CMimicsSwitchCtrl::SetInteriorFrameColor(OLE_COLOR nColor)
{
	if (nColor != m_nFrameColor[1])
	{
		m_nFrameColor[1] = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsSwitchCtrl::GetInteriorFrameColor() CONST
{
	return m_nFrameColor[1];
}

void CMimicsSwitchCtrl::SetCenterColor(OLE_COLOR nColor)
{
	if (nColor != m_nCenterColor[0])
	{
		m_nCenterColor[0] = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsSwitchCtrl::GetCenterColor() CONST
{
	return m_nCenterColor[0];
}

void CMimicsSwitchCtrl::SetInteriorCenterColor(OLE_COLOR nColor)
{
	if (nColor != m_nCenterColor[1])
	{
		m_nCenterColor[1] = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsSwitchCtrl::GetInteriorCenterColor() CONST
{
	return m_nCenterColor[1];
}

void CMimicsSwitchCtrl::SetBarColor(OLE_COLOR nColor)
{
	if (nColor != m_nBarColor)
	{
		m_nBarColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsSwitchCtrl::GetBarColor() CONST
{
	return m_nBarColor;
}

void CMimicsSwitchCtrl::SetStubsColor(OLE_COLOR nColor)
{
	if (nColor != m_nStubsColor)
	{
		m_nStubsColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsSwitchCtrl::GetStubsColor() CONST
{
	return m_nStubsColor;
}

void CMimicsSwitchCtrl::SetThickness(LONG nWidth)
{
	if (nWidth != m_nWidth)
	{
		m_nWidth = m_nBarWidth = m_nStubsWidth = m_nFrameWidth = m_nCenterWidth = nWidth;
		Refresh();
	}
}

LONG CMimicsSwitchCtrl::GetThickness() CONST
{
	return m_nWidth;
}

void CMimicsSwitchCtrl::SetFrameThickness(LONG nWidth)
{
	if (nWidth != m_nFrameWidth)
	{
		m_nFrameWidth = nWidth;
		Refresh();
	}
}

LONG CMimicsSwitchCtrl::GetFrameThickness() CONST
{
	return m_nFrameWidth;
}

void CMimicsSwitchCtrl::SetCenterThickness(LONG nWidth)
{
	if (nWidth != m_nCenterWidth)
	{
		m_nCenterWidth = nWidth;
		Refresh();
	}
}

LONG CMimicsSwitchCtrl::GetCenterThickness() CONST
{
	return m_nCenterWidth;
}

void CMimicsSwitchCtrl::SetBarThickness(LONG nWidth)
{
	if (nWidth != m_nBarWidth)
	{
		m_nBarWidth = nWidth;
		Refresh();
	}
}

LONG CMimicsSwitchCtrl::GetBarThickness() CONST
{
	return m_nBarWidth;
}

void CMimicsSwitchCtrl::SetStubsThickness(LONG nWidth)
{
	if (nWidth != m_nStubsWidth)
	{
		m_nStubsWidth = nWidth;
		Refresh();
	}
}

LONG CMimicsSwitchCtrl::GetStubsThickness() CONST
{
	return m_nStubsWidth;
}

void CMimicsSwitchCtrl::Open()
{
	if ((m_nStyle & MIMICSSWITCHCTRL_STYLE_OPENCLOSE) && m_nStatus != 0)
	{
		m_nStatus = 0;
		Refresh();
	}
}

BOOL CMimicsSwitchCtrl::IsOpen() CONST
{
	return((m_nStyle & MIMICSSWITCHCTRL_STYLE_OPENCLOSE) ? ((m_nStatus == 0) ? TRUE : FALSE) : FALSE);
}

BOOL CMimicsSwitchCtrl::IsClosed() CONST
{
	return((m_nStyle & MIMICSSWITCHCTRL_STYLE_OPENCLOSE) ? ((m_nStatus == 1) ? TRUE : FALSE) : FALSE);
}

void CMimicsSwitchCtrl::Close()
{
	if ((m_nStyle & MIMICSSWITCHCTRL_STYLE_OPENCLOSE) && m_nStatus != 1)
	{
		m_nStatus = 1;
		Refresh();
	}
}

void CMimicsSwitchCtrl::Pos1()
{
	if (((m_nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS) || (m_nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS)) && m_nStatus != 0)
	{
		m_nStatus = 0;
		Refresh();
	}
}

BOOL CMimicsSwitchCtrl::IsPos1() CONST
{
	return(((m_nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS) || (m_nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS)) ? ((m_nStatus == 0) ? TRUE : FALSE) : FALSE);
}

void CMimicsSwitchCtrl::Pos2()
{
	if (((m_nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS) || (m_nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS)) && m_nStatus != 1)
	{
		m_nStatus = 1;
		Refresh();
	}
}

BOOL CMimicsSwitchCtrl::IsPos2() CONST
{
	return(((m_nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS) || (m_nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS)) ? ((m_nStatus == 1) ? TRUE : FALSE) : FALSE);
}

void CMimicsSwitchCtrl::Pos3()
{
	if ((m_nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS) && m_nStatus != 2)
	{
		m_nStatus = 2;
		Refresh();
	}
}

BOOL CMimicsSwitchCtrl::IsPos3() CONST
{
	return((m_nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS) ? ((m_nStatus == 2) ? TRUE : FALSE) : FALSE);
}

void CMimicsSwitchCtrl::Broken()
{
	if (m_nStatus != -1)
	{
		m_nStatus = -1;
		Refresh();
	}
}

BOOL CMimicsSwitchCtrl::IsBroken() CONST
{
	return((m_nStatus == -1) ? TRUE : FALSE);
}

VOID CMimicsSwitchCtrl::DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape)
{
	INT  dx;
	INT  dy;
	INT  dc;
	INT  dr;
	HPEN  hPen;
	HPEN  hOldPen;
	CRect  rFrame;
	HBRUSH  hBrush;
	HBRUSH  hOldBrush;
	CPoint  ptStubs[4][2];

	if (m_nStyle & MIMICSSWITCHCTRL_STYLE_SIMPLE)
	{
		if (m_nStyle & MIMICSSWITCHCTRL_STYLE_FRAME)
		{
			dx = pRect->right - pRect->left;
			dy = pRect->bottom - pRect->top;
			dr = min(dx, dy);
			rFrame.left = pRect->left + (dx - dr) / 2;
			rFrame.top = pRect->top + (dy - dr) / 2;
			rFrame.right = rFrame.left + dr;
			rFrame.bottom = rFrame.top + dr;
			rFrame.DeflateRect(((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && dx == dr) ? (dx / 10) : 0, 0);
			rFrame.DeflateRect(0, ((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && dx == dr) ? (dx / 10) : 0);
			rFrame.DeflateRect(((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && ((m_nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS) || (m_nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS)) && dx != dr  &&  dy == dr) ? (dy / 10) : 0, 0);
			rFrame.DeflateRect(0, ((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && ((m_nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS) || (m_nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS)) && dx != dr  &&  dy == dr) ? (dy / 10) : 0);
			if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_INSIDEFRAME, m_nFrameWidth, GetNearestColor(hDC, (!bShape) ? m_nFrameColor[0] : VGA_COLOR_WHITE))))
			{
				if ((hBrush = CreateSolidBrush(GetNearestColor(hDC, (!bShape) ? m_nFrameColor[1] : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
					{
						if ((hOldBrush = (HBRUSH)SelectObject(hDC, hBrush)))
						{
							Ellipse(hDC, rFrame.left, rFrame.top, rFrame.right, rFrame.bottom);
							SelectObject(hDC, hOldBrush);
						}
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hBrush);
				}
				DeleteObject(hPen);
			}
			if (m_nStyle & MIMICSSWITCHCTRL_STYLE_OPENCLOSE)
			{
				if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nBarWidth, GetNearestColor(hDC, (!bShape) ? m_nBarColor : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)))
					{
						if (m_nStatus > 0)
						{
							MoveToEx(hDC, rFrame.left + 1, rFrame.CenterPoint().y + rFrame.Height() % 2, (LPPOINT)NULL);
							LineTo(hDC, rFrame.right, rFrame.CenterPoint().y + rFrame.Height() % 2);
						}
						if (!m_nStatus) Arc(hDC, rFrame.CenterPoint().x - rFrame.Width() + rFrame.Width() % 2, rFrame.CenterPoint().y - rFrame.Height() + rFrame.Height() % 2, rFrame.CenterPoint().x + rFrame.Width() % 2, rFrame.CenterPoint().y + rFrame.Height() % 2, rFrame.left + 1, rFrame.CenterPoint().y + rFrame.Height() % 2, rFrame.CenterPoint().x + rFrame.Width() % 2, rFrame.top + 1);
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hPen);
				}
				if (m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS)
				{
					if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nStubsWidth, GetNearestColor(hDC, (!bShape) ? m_nStubsColor : VGA_COLOR_WHITE))))
					{
						if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
						{
							MoveToEx(hDC, pRect->left, rFrame.CenterPoint().y + rFrame.Height() % 2, (LPPOINT)NULL);
							LineTo(hDC, rFrame.left + 1, rFrame.CenterPoint().y + rFrame.Height() % 2);
							MoveToEx(hDC, pRect->right, rFrame.CenterPoint().y + rFrame.Height() % 2, (LPPOINT)NULL);
							LineTo(hDC, rFrame.right - 1, rFrame.CenterPoint().y + rFrame.Height() % 2);
							SelectObject(hDC, hOldPen);
						}
						DeleteObject(hPen);
					}
				}
				return;
			}
			if (m_nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS)
			{
				if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nBarWidth, GetNearestColor(hDC, (!bShape) ? m_nBarColor : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
					{
						if (m_nStatus >= 0) Arc(hDC, rFrame.CenterPoint().x - rFrame.Width() + rFrame.Width() % 2, (!m_nStatus) ? (rFrame.CenterPoint().y - rFrame.Height() + rFrame.Height() % 2) : (rFrame.CenterPoint().y + rFrame.Height() % 2), rFrame.CenterPoint().x + rFrame.Width() % 2, (!m_nStatus) ? (rFrame.CenterPoint().y + rFrame.Height() % 2) : (rFrame.CenterPoint().y + rFrame.Height() + rFrame.Height() % 2), (!m_nStatus) ? (rFrame.left + 1) : (rFrame.CenterPoint().x + rFrame.Width() % 2), (!m_nStatus) ? (rFrame.CenterPoint().y + rFrame.Height() % 2) : (rFrame.bottom - 1), (!m_nStatus) ? (rFrame.CenterPoint().x + rFrame.Width() % 2) : (rFrame.left + 1), (!m_nStatus) ? (rFrame.top + 1) : (rFrame.CenterPoint().y + rFrame.Height() % 2));
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hPen);
				}
				if (m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS)
				{
					if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nStubsWidth, GetNearestColor(hDC, (!bShape) ? m_nStubsColor : VGA_COLOR_WHITE))))
					{
						if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
						{
							MoveToEx(hDC, pRect->left, rFrame.CenterPoint().y + rFrame.Height() % 2, (LPPOINT)NULL);
							LineTo(hDC, rFrame.left + 1, rFrame.CenterPoint().y + rFrame.Height() % 2);
							MoveToEx(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, pRect->top, (LPPOINT)NULL);
							LineTo(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, rFrame.top + 1);
							MoveToEx(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, pRect->bottom, (LPPOINT)NULL);
							LineTo(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, rFrame.bottom - 1);
							SelectObject(hDC, hOldPen);
						}
						DeleteObject(hPen);
					}
				}
				return;
			}
			if (m_nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS)
			{
				if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nBarWidth, GetNearestColor(hDC, (!bShape) ? m_nBarColor : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)))
					{
						if (m_nStatus == 1)
						{
							MoveToEx(hDC, rFrame.left + 1, rFrame.CenterPoint().y + rFrame.Height() % 2, (LPPOINT)NULL);
							LineTo(hDC, rFrame.right, rFrame.CenterPoint().y + rFrame.Height() % 2);
						}
						if (m_nStatus == 0 || m_nStatus == 2) Arc(hDC, rFrame.CenterPoint().x - rFrame.Width() + rFrame.Width() % 2, (!m_nStatus) ? (rFrame.CenterPoint().y - rFrame.Height() + rFrame.Height() % 2) : (rFrame.CenterPoint().y + rFrame.Height() % 2), rFrame.CenterPoint().x + rFrame.Width() % 2, (!m_nStatus) ? (rFrame.CenterPoint().y + rFrame.Height() % 2) : (rFrame.CenterPoint().y + rFrame.Height() + rFrame.Height() % 2), (!m_nStatus) ? (rFrame.left + 1) : (rFrame.CenterPoint().x + rFrame.Width() % 2), (!m_nStatus) ? (rFrame.CenterPoint().y + rFrame.Height() % 2) : (rFrame.bottom - 1), (!m_nStatus) ? (rFrame.CenterPoint().x + rFrame.Width() % 2) : (rFrame.left + 1), (!m_nStatus) ? (rFrame.top + 1) : (rFrame.CenterPoint().y + rFrame.Height() % 2));
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hPen);
				}
				if (m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS)
				{
					if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nStubsWidth, GetNearestColor(hDC, (!bShape) ? m_nStubsColor : VGA_COLOR_WHITE))))
					{
						if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
						{
							MoveToEx(hDC, pRect->left, rFrame.CenterPoint().y + rFrame.Height() % 2, (LPPOINT)NULL);
							LineTo(hDC, rFrame.left + 1, rFrame.CenterPoint().y + rFrame.Height() % 2);
							MoveToEx(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, pRect->top, (LPPOINT)NULL);
							LineTo(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, rFrame.top + 1);
							MoveToEx(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, pRect->bottom, (LPPOINT)NULL);
							LineTo(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, rFrame.bottom - 1);
							MoveToEx(hDC, pRect->right, rFrame.CenterPoint().y + rFrame.Height() % 2, (LPPOINT)NULL);
							LineTo(hDC, rFrame.right - 1, rFrame.CenterPoint().y + rFrame.Height() % 2);
							SelectObject(hDC, hOldPen);
						}
						DeleteObject(hPen);
					}
				}
			}
			return;
		}
		if (m_nStyle & MIMICSSWITCHCTRL_STYLE_OPENCLOSE)
		{
			dx = pRect->right - pRect->left;
			dy = pRect->bottom - pRect->top;
			dr = min((min(dx, dy) + 4) / 16 + 2, min(dx, dy));
			ptStubs[0][0].x = pRect->left;
			ptStubs[1][1].x = pRect->right;
			ptStubs[0][1].x = (3 * dr + sqrt(2.0)*(dy - dr) <= (double)dx) ? (INT)(pRect->left + (dx - sqrt(2.0)*(dy - dr) - dr) / 2.0) : (pRect->left + dr);
			ptStubs[1][0].x = (3 * dr + sqrt(2.0)*(dy - dr) <= (double)dx) ? (INT)(pRect->right - (dx - sqrt(2.0)*(dy - dr) - dr) / 2.0) : (pRect->right - dr);
			ptStubs[0][0].y = ptStubs[0][1].y = pRect->bottom - max(m_nStubsWidth / 2, dr) - 1;
			ptStubs[1][0].y = ptStubs[1][1].y = pRect->bottom - max(m_nStubsWidth / 2, dr) - 1;
			if ((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) == MIMICSSWITCHCTRL_STYLE_STUBS)
			{
				if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nStubsWidth, GetNearestColor(hDC, (!bShape) ? m_nStubsColor : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
					{
						MoveToEx(hDC, ptStubs[0][0].x, min(max(ptStubs[0][0].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom), (LPPOINT)NULL);
						LineTo(hDC, ptStubs[0][1].x + 1, min(max(ptStubs[0][1].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom));
						MoveToEx(hDC, ptStubs[1][0].x, min(max(ptStubs[1][0].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom), (LPPOINT)NULL);
						LineTo(hDC, ptStubs[1][1].x + 1, min(max(ptStubs[1][1].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom));
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hPen);
				}
			}
			if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nBarWidth, GetNearestColor(hDC, (!bShape) ? m_nBarColor : VGA_COLOR_WHITE))))
			{
				if ((hOldPen = (HPEN)SelectObject(hDC, hPen)))
				{
					if (m_nStatus >= 0)
					{
						MoveToEx(hDC, ptStubs[0][1].x + dr, ptStubs[0][1].y, (LPPOINT)NULL);
						LineTo(hDC, (!m_nStatus) ? (INT)(ptStubs[0][1].x + dr + (ptStubs[1][0].x - ptStubs[0][1].x - dr) / sqrt(2.0)) : ptStubs[1][0].x, (!m_nStatus) ? (INT)(ptStubs[0][1].y - (ptStubs[1][0].x - ptStubs[0][1].x - dr) / sqrt(2.0) + 1) : ptStubs[1][0].y);
					}
					SelectObject(hDC, hOldPen);
				}
				DeleteObject(hPen);
			}
			if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_INSIDEFRAME, m_nCenterWidth, GetNearestColor(hDC, (!bShape) ? m_nCenterColor[0] : VGA_COLOR_WHITE))))
			{
				if ((hBrush = CreateSolidBrush(GetNearestColor(hDC, (!bShape) ? m_nCenterColor[1] : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
					{
						if ((hOldBrush = (HBRUSH)SelectObject(hDC, hBrush)))
						{
							Ellipse(hDC, ptStubs[0][1].x, ptStubs[0][1].y - dr, ptStubs[0][1].x + 2 * dr + 1, ptStubs[0][1].y + dr + 1);
							SelectObject(hDC, hOldBrush);
						}
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hBrush);
				}
				DeleteObject(hPen);
			}
			return;
		}
		if (m_nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS)
		{
			dx = pRect->right - pRect->left;
			dy = pRect->bottom - pRect->top;
			dr = min((min(dx, dy) + 4) / 24 + 2, min(dx, dy));
			ptStubs[0][0].x = pRect->left;
			ptStubs[1][1].x = ptStubs[2][1].x = pRect->right;
			ptStubs[0][1].x = (3 * dr + sqrt(2.0)*(dy - dr) <= (double)dx) ? (INT)(pRect->left + (dx - sqrt(2.0)*(dy - dr) - dr) / 2.0) : (pRect->left + dr);
			ptStubs[1][0].x = ptStubs[2][0].x = (3 * dr + sqrt(2.0)*(dy - dr) <= (double)dx) ? (INT)(pRect->right - (dx - sqrt(2.0)*(dy - dr) - dr) / 2.0) : (pRect->right - dr);
			ptStubs[0][0].y = ptStubs[0][1].y = (pRect->top + pRect->bottom) / 2;
			ptStubs[1][0].y = ptStubs[1][1].y = pRect->top + max(m_nStubsWidth / 2, dr) + 1;
			ptStubs[2][0].y = ptStubs[2][1].y = pRect->bottom - max(m_nStubsWidth / 2, dr) - 1;
			if ((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) == MIMICSSWITCHCTRL_STYLE_STUBS)
			{
				if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nStubsWidth, GetNearestColor(hDC, (!bShape) ? m_nStubsColor : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
					{
						MoveToEx(hDC, ptStubs[0][0].x, min(max(ptStubs[0][0].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom), (LPPOINT)NULL);
						LineTo(hDC, ptStubs[0][1].x + 1, min(max(ptStubs[0][1].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom));
						MoveToEx(hDC, ptStubs[1][0].x, min(max(ptStubs[1][0].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom), (LPPOINT)NULL);
						LineTo(hDC, ptStubs[1][1].x + 1, min(max(ptStubs[1][1].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom));
						MoveToEx(hDC, ptStubs[2][0].x, min(max(ptStubs[2][0].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom), (LPPOINT)NULL);
						LineTo(hDC, ptStubs[2][1].x + 1, min(max(ptStubs[2][1].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom));
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hPen);
				}
			}
			if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nBarWidth, GetNearestColor(hDC, (!bShape) ? m_nBarColor : VGA_COLOR_WHITE))))
			{
				if ((hOldPen = (HPEN)SelectObject(hDC, hPen)))
				{
					if (m_nStatus >= 0)
					{
						MoveToEx(hDC, ptStubs[0][1].x + dr, ptStubs[0][1].y, (LPPOINT)NULL);
						LineTo(hDC, (!m_nStatus) ? ptStubs[1][0].x : ptStubs[2][0].x, (!m_nStatus) ? ptStubs[1][0].y : ptStubs[2][0].y);
					}
					SelectObject(hDC, hOldPen);
				}
				DeleteObject(hPen);
			}
			if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_INSIDEFRAME, m_nCenterWidth, GetNearestColor(hDC, (!bShape) ? m_nCenterColor[0] : VGA_COLOR_WHITE))))
			{
				if ((hBrush = CreateSolidBrush(GetNearestColor(hDC, (!bShape) ? m_nCenterColor[1] : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
					{
						if ((hOldBrush = (HBRUSH)SelectObject(hDC, hBrush)))
						{
							Ellipse(hDC, ptStubs[0][1].x, ptStubs[0][1].y - dr, ptStubs[0][1].x + 2 * dr + 1, ptStubs[0][1].y + dr + 1);
							SelectObject(hDC, hOldBrush);
						}
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hBrush);
				}
				DeleteObject(hPen);
			}
			return;
		}
		if (m_nStyle & MIMICSSWITCHCTRL_STYLE_THREEPOS)
		{
			dx = pRect->right - pRect->left;
			dy = pRect->bottom - pRect->top;
			dr = min((min(dx, dy) + 4) / 24 + 2, min(dx, dy));
			ptStubs[0][0].x = pRect->left;
			ptStubs[1][1].x = ptStubs[2][1].x = ptStubs[3][1].x = pRect->right;
			ptStubs[0][1].x = (3 * dr + sqrt(2.0)*(dy - dr) <= (double)dx) ? (INT)(pRect->left + (dx - sqrt(2.0)*(dy - dr) - dr) / 2.0) : (pRect->left + dr);
			ptStubs[1][0].x = ptStubs[2][0].x = ptStubs[3][0].x = (3 * dr + sqrt(2.0)*(dy - dr) <= (double)dx) ? (INT)(pRect->right - (dx - sqrt(2.0)*(dy - dr) - dr) / 2.0) : (pRect->right - dr);
			ptStubs[0][0].y = ptStubs[0][1].y = ptStubs[2][0].y = ptStubs[2][1].y = (pRect->top + pRect->bottom) / 2;
			ptStubs[1][0].y = ptStubs[1][1].y = pRect->top + max(m_nStubsWidth / 2, dr) + 1;
			ptStubs[3][0].y = ptStubs[3][1].y = pRect->bottom - max(m_nStubsWidth / 2, dr) - 1;
			if ((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) == MIMICSSWITCHCTRL_STYLE_STUBS)
			{
				if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nStubsWidth, GetNearestColor(hDC, (!bShape) ? m_nStubsColor : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
					{
						MoveToEx(hDC, ptStubs[0][0].x, min(max(ptStubs[0][0].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom), (LPPOINT)NULL);
						LineTo(hDC, ptStubs[0][1].x + 1, min(max(ptStubs[0][1].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom));
						MoveToEx(hDC, ptStubs[1][0].x, min(max(ptStubs[1][0].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom), (LPPOINT)NULL);
						LineTo(hDC, ptStubs[1][1].x + 1, min(max(ptStubs[1][1].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom));
						MoveToEx(hDC, ptStubs[2][0].x, min(max(ptStubs[2][0].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom), (LPPOINT)NULL);
						LineTo(hDC, ptStubs[2][1].x + 1, min(max(ptStubs[2][1].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom));
						MoveToEx(hDC, ptStubs[3][0].x, min(max(ptStubs[3][0].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom), (LPPOINT)NULL);
						LineTo(hDC, ptStubs[3][1].x + 1, min(max(ptStubs[3][1].y + (m_nStubsWidth + 1) % 2, pRect->top), pRect->bottom));
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hPen);
				}
			}
			if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nBarWidth, GetNearestColor(hDC, (!bShape) ? m_nBarColor : VGA_COLOR_WHITE))))
			{
				if ((hOldPen = (HPEN)SelectObject(hDC, hPen)))
				{
					if (m_nStatus >= 0)
					{
						MoveToEx(hDC, ptStubs[0][1].x + dr, ptStubs[0][1].y, (LPPOINT)NULL);
						LineTo(hDC, (m_nStatus == 0) ? ptStubs[1][0].x : ((m_nStatus == 1) ? ptStubs[2][0].x : ptStubs[3][0].x), (m_nStatus == 0) ? ptStubs[1][0].y : ((m_nStatus == 1) ? ptStubs[2][0].y : ptStubs[3][0].y));
					}
					SelectObject(hDC, hOldPen);
				}
				DeleteObject(hPen);
			}
			if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_INSIDEFRAME, m_nCenterWidth, GetNearestColor(hDC, (!bShape) ? m_nCenterColor[0] : VGA_COLOR_WHITE))))
			{
				if ((hBrush = CreateSolidBrush(GetNearestColor(hDC, (!bShape) ? m_nCenterColor[1] : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
					{
						if ((hOldBrush = (HBRUSH)SelectObject(hDC, hBrush)))
						{
							Ellipse(hDC, ptStubs[0][1].x, ptStubs[0][1].y - dr, ptStubs[0][1].x + 2 * dr + 1, ptStubs[0][1].y + dr + 1);
							SelectObject(hDC, hOldBrush);
						}
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hBrush);
				}
				DeleteObject(hPen);
			}
		}
		return;
	}
	if (m_nStyle & MIMICSSWITCHCTRL_STYLE_DOUBLE)
	{
		if (m_nStyle & MIMICSSWITCHCTRL_STYLE_FRAME)
		{
			dx = pRect->right - pRect->left;
			dy = pRect->bottom - pRect->top;
			dr = min(dx, dy);
			dc = min(max(m_nBarWidth, 4), max(dr / 2 - m_nBarWidth / 2, 0));
			rFrame.left = pRect->left + (dx - dr) / 2;
			rFrame.top = pRect->top + (dy - dr) / 2;
			rFrame.right = rFrame.left + dr;
			rFrame.bottom = rFrame.top + dr;
			rFrame.DeflateRect(((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && dx == dr) ? (dx / 10) : 0, 0);
			rFrame.DeflateRect(0, ((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && dx == dr) ? (dx / 10) : 0);
			rFrame.DeflateRect(((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && dx != dr  &&  dy == dr) ? (dy / 10) : 0, 0);
			rFrame.DeflateRect(0, ((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && dx != dr  &&  dy == dr) ? (dy / 10) : 0);
			if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_INSIDEFRAME, m_nFrameWidth, GetNearestColor(hDC, (!bShape) ? m_nFrameColor[0] : VGA_COLOR_WHITE))))
			{
				if ((hBrush = CreateSolidBrush(GetNearestColor(hDC, (!bShape) ? m_nFrameColor[1] : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
					{
						if ((hOldBrush = (HBRUSH)SelectObject(hDC, hBrush)))
						{
							Ellipse(hDC, rFrame.left, rFrame.top, rFrame.right, rFrame.bottom);
							SelectObject(hDC, hOldBrush);
						}
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hBrush);
				}
				DeleteObject(hPen);
			}
			if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nBarWidth, GetNearestColor(hDC, (!bShape) ? m_nBarColor : VGA_COLOR_WHITE))))
			{
				if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
				{
					if (m_nStatus == 0 || (((m_nStyle & MIMICSSWITCHCTRL_STYLE_OPENCLOSE) || (m_nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS)) && m_nStatus == 1) || m_nStatus == 2)
					{
						Arc(hDC, rFrame.CenterPoint().x - rFrame.Width() + rFrame.Width() % 2, (!m_nStatus) ? (rFrame.CenterPoint().y - rFrame.Height() + rFrame.Height() % 2) : (rFrame.CenterPoint().y + rFrame.Height() % 2), rFrame.CenterPoint().x + rFrame.Width() % 2, (!m_nStatus) ? (rFrame.CenterPoint().y + rFrame.Height() % 2) : (rFrame.CenterPoint().y + rFrame.Height() + rFrame.Height() % 2), (!m_nStatus) ? (rFrame.left + 1) : (rFrame.CenterPoint().x + rFrame.Width() % 2), (!m_nStatus) ? (rFrame.CenterPoint().y + rFrame.Height() % 2) : (rFrame.bottom - 1), (!m_nStatus) ? (rFrame.CenterPoint().x + rFrame.Width() % 2) : (rFrame.left + 1), (!m_nStatus) ? (rFrame.top + 1) : (rFrame.CenterPoint().y + rFrame.Height() % 2));
						Arc(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, (!m_nStatus) ? (rFrame.CenterPoint().y + rFrame.Height() % 2) : (rFrame.CenterPoint().y - rFrame.Height() + rFrame.Height() % 2), rFrame.CenterPoint().x + rFrame.Width() + rFrame.Width() % 2, (!m_nStatus) ? (rFrame.CenterPoint().y + rFrame.Height() + rFrame.Height() % 2) : (rFrame.CenterPoint().y + rFrame.Height() % 2), (!m_nStatus) ? (rFrame.right - 1) : (rFrame.CenterPoint().x + rFrame.Width() % 2), (!m_nStatus) ? (rFrame.CenterPoint().y + rFrame.Height() % 2) : (rFrame.top + 1), (!m_nStatus) ? (rFrame.CenterPoint().x + rFrame.Width() % 2) : (rFrame.right - 1), (!m_nStatus) ? (rFrame.bottom - 1) : (rFrame.CenterPoint().y + rFrame.Height() % 2));
					}
					else
					{
						if (m_nStatus >= 0)
						{
							MoveToEx(hDC, rFrame.left + 1, rFrame.CenterPoint().y + rFrame.Height() % 2, (LPPOINT)NULL);
							LineTo(hDC, rFrame.right, rFrame.CenterPoint().y + rFrame.Height() % 2);
							MoveToEx(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, rFrame.top + 1, (LPPOINT)NULL);
							LineTo(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, max(rFrame.CenterPoint().y - dc + rFrame.Height() % 2 - (m_nBarWidth + 1) % 2 + 1, rFrame.top + 1));
							MoveToEx(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, rFrame.bottom - 1, (LPPOINT)NULL);
							LineTo(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, min(rFrame.CenterPoint().y + dc + rFrame.Height() % 2, rFrame.bottom - 1));
							Arc(hDC, rFrame.CenterPoint().x - dc + rFrame.Width() % 2, rFrame.CenterPoint().y - dc + rFrame.Height() % 2 - (m_nBarWidth + 1) % 2, rFrame.CenterPoint().x + dc + rFrame.Width() % 2, rFrame.CenterPoint().y + dc + rFrame.Height() % 2, rFrame.CenterPoint().x + rFrame.Width() % 2, rFrame.CenterPoint().y + dc + rFrame.Height() % 2, rFrame.CenterPoint().x + rFrame.Width() % 2, rFrame.CenterPoint().y - dc + rFrame.Height() % 2 - (m_nBarWidth + 1) % 2);
						}
					}
					SelectObject(hDC, hOldPen);
				}
				DeleteObject(hPen);
			}
			if (m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS)
			{
				if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nStubsWidth, GetNearestColor(hDC, (!bShape) ? m_nStubsColor : VGA_COLOR_WHITE))))
				{
					if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
					{
						MoveToEx(hDC, pRect->left, rFrame.CenterPoint().y + rFrame.Height() % 2, (LPPOINT)NULL);
						LineTo(hDC, min(rFrame.left + 1, pRect->right), rFrame.CenterPoint().y + rFrame.Height() % 2);
						MoveToEx(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, pRect->top, (LPPOINT)NULL);
						LineTo(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, min(rFrame.top + 1, pRect->bottom));
						MoveToEx(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, pRect->bottom, (LPPOINT)NULL);
						LineTo(hDC, rFrame.CenterPoint().x + rFrame.Width() % 2, max(rFrame.bottom - 1, pRect->top));
						MoveToEx(hDC, pRect->right, rFrame.CenterPoint().y + rFrame.Height() % 2, (LPPOINT)NULL);
						LineTo(hDC, max(rFrame.right - 1, pRect->left), rFrame.CenterPoint().y + rFrame.Height() % 2);
						SelectObject(hDC, hOldPen);
					}
					DeleteObject(hPen);
				}
			}
			return;
		}
		dx = pRect->right - pRect->left;
		dy = pRect->bottom - pRect->top;
		dr = min(max(min(dx, dy) / 24 + 2, 2), min(dx, dy));
		dc = min(max(m_nBarWidth, 4), max(min(dx, dy) / 2 - m_nBarWidth / 2, 0));
		rFrame.left = pRect->left + (dx - min(dx, dy)) / 2;
		rFrame.top = pRect->top + (dy - min(dx, dy)) / 2;
		rFrame.right = rFrame.left + min(dx, dy);
		rFrame.bottom = rFrame.top + min(dx, dy);
		rFrame.DeflateRect(((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && dx == min(dx, dy)) ? (dx / 10) : 0, 0);
		rFrame.DeflateRect(0, ((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && dx == min(dx, dy)) ? (dx / 10) : 0);
		rFrame.DeflateRect(((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && dx != min(dx, dy) && dy == min(dx, dy)) ? (dy / 10) : 0, 0);
		rFrame.DeflateRect(0, ((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) && dx != min(dx, dy) && dy == min(dx, dy)) ? (dy / 10) : 0);
		if ((m_nStyle & MIMICSSWITCHCTRL_STYLE_STUBS) == MIMICSSWITCHCTRL_STYLE_STUBS)
		{
			if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nStubsWidth, GetNearestColor(hDC, (!bShape) ? m_nStubsColor : VGA_COLOR_WHITE))))
			{
				if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
				{
					MoveToEx(hDC, pRect->left, rFrame.CenterPoint().y + (m_nStubsWidth + 1) % 2, (LPPOINT)NULL);
					LineTo(hDC, min(rFrame.left + 1, pRect->right), rFrame.CenterPoint().y + (m_nStubsWidth + 1) % 2);
					MoveToEx(hDC, rFrame.CenterPoint().x + (m_nStubsWidth + 1) % 2, pRect->top, (LPPOINT)NULL);
					LineTo(hDC, rFrame.CenterPoint().x + (m_nStubsWidth + 1) % 2, min(rFrame.top + 1, pRect->bottom));
					MoveToEx(hDC, rFrame.CenterPoint().x + (m_nStubsWidth + 1) % 2, pRect->bottom, (LPPOINT)NULL);
					LineTo(hDC, rFrame.CenterPoint().x + (m_nStubsWidth + 1) % 2, max(rFrame.bottom - 1, pRect->top));
					MoveToEx(hDC, pRect->right, rFrame.CenterPoint().y + (m_nStubsWidth + 1) % 2, (LPPOINT)NULL);
					LineTo(hDC, max(rFrame.right - 1, pRect->left), rFrame.CenterPoint().y + (m_nStubsWidth + 1) % 2);
					SelectObject(hDC, hOldPen);
				}
				DeleteObject(hPen);
			}
		}
		if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT, m_nBarWidth, GetNearestColor(hDC, (!bShape) ? m_nBarColor : VGA_COLOR_WHITE))))
		{
			if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
			{
				if (m_nStatus == 0 || (((m_nStyle & MIMICSSWITCHCTRL_STYLE_OPENCLOSE) || (m_nStyle & MIMICSSWITCHCTRL_STYLE_TWOPOS)) && m_nStatus == 1) || m_nStatus == 2)
				{
					MoveToEx(hDC, rFrame.left + dr, rFrame.CenterPoint().y, (LPPOINT)NULL);
					LineTo(hDC, rFrame.CenterPoint().x, (m_nStatus == 0) ? (rFrame.top + dr) : (rFrame.bottom - dr - rFrame.Height() % 2));
					MoveToEx(hDC, rFrame.right - dr, rFrame.CenterPoint().y, (LPPOINT)NULL);
					LineTo(hDC, rFrame.CenterPoint().x, (m_nStatus == 0) ? (rFrame.bottom - dr) : (rFrame.top + dr - rFrame.Height() % 2));
				}
				else
				{
					if (m_nStatus >= 0)
					{
						MoveToEx(hDC, rFrame.left + dr, rFrame.CenterPoint().y + (m_nBarWidth + 1) % 2, (LPPOINT)NULL);
						LineTo(hDC, rFrame.right - dr, rFrame.CenterPoint().y + (m_nBarWidth + 1) % 2);
						MoveToEx(hDC, rFrame.CenterPoint().x + (m_nBarWidth + 1) % 2, rFrame.top + dr, (LPPOINT)NULL);
						LineTo(hDC, rFrame.CenterPoint().x + (m_nBarWidth + 1) % 2, max(rFrame.CenterPoint().y - dc, rFrame.top + dr));
						MoveToEx(hDC, rFrame.CenterPoint().x + (m_nBarWidth + 1) % 2, rFrame.bottom - dr, (LPPOINT)NULL);
						LineTo(hDC, rFrame.CenterPoint().x + (m_nBarWidth + 1) % 2, min(rFrame.CenterPoint().y + dc + (m_nBarWidth + 1) % 2, rFrame.bottom - dr));
						Arc(hDC, rFrame.CenterPoint().x - dc, rFrame.CenterPoint().y - dc, rFrame.CenterPoint().x + dc, rFrame.CenterPoint().y + dc + (m_nBarWidth + 1) % 2, rFrame.CenterPoint().x, rFrame.CenterPoint().y + dc + (m_nBarWidth + 1) % 2, rFrame.CenterPoint().x, rFrame.CenterPoint().y - dc);
					}
				}
				SelectObject(hDC, hOldPen);
			}
			DeleteObject(hPen);
		}
		if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_INSIDEFRAME, m_nCenterWidth, GetNearestColor(hDC, (!bShape) ? m_nCenterColor[0] : VGA_COLOR_WHITE))))
		{
			if ((hBrush = CreateSolidBrush(GetNearestColor(hDC, (!bShape) ? m_nCenterColor[1] : VGA_COLOR_WHITE))))
			{
				if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
				{
					if ((hOldBrush = (HBRUSH)SelectObject(hDC, hBrush)))
					{
						Ellipse(hDC, rFrame.left, rFrame.CenterPoint().y - dr, rFrame.left + 2 * dr + 1, rFrame.CenterPoint().y + dr + 1);
						Ellipse(hDC, rFrame.right - 2 * dr, rFrame.CenterPoint().y - dr, rFrame.right + 1, rFrame.CenterPoint().y + dr + 1);
						Ellipse(hDC, rFrame.CenterPoint().x - dr, rFrame.top - rFrame.Height() % 2, rFrame.CenterPoint().x + dr + 1, rFrame.top + 2 * dr - rFrame.Height() % 2 + 1);
						Ellipse(hDC, rFrame.CenterPoint().x - dr, rFrame.bottom - 2 * dr - rFrame.Height() % 2, rFrame.CenterPoint().x + dr + 1, rFrame.bottom - rFrame.Height() % 2 + 1);
						SelectObject(hDC, hOldBrush);
					}
					SelectObject(hDC, hOldPen);
				}
				DeleteObject(hBrush);
			}
			DeleteObject(hPen);
		}
		return;
	}
}

void CMimicsSwitchCtrl::DoPropExchange(CPropExchange *pPX)
{
	ExchangeVersion(pPX, MAKELONG(CMimicsApp::wAppVerMinor, CMimicsApp::wAppVerMajor));
	CMimicsCtrl::DoPropExchange(pPX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchCtrl message handlers

void CMimicsSwitchCtrl::OnResetState()
{
	m_nStatus = 0;
	CMimicsCtrl::OnResetState();
}
