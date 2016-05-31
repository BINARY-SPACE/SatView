// MIMICSELLIPSECTL.CPP : Mimics Ellipse Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics ellipse
// control related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseCtrlDispatchDriver properties

VOID CMimicsEllipseCtrlDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsEllipseCtrlDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsEllipseCtrlDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsEllipseCtrlDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsEllipseCtrlDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsEllipseCtrlDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsEllipseCtrlDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsEllipseCtrlDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsEllipseCtrlDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsEllipseCtrlDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseCtrlDispatchDriver operations

VOID CMimicsEllipseCtrlDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsEllipseCtrlDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}


IMPLEMENT_DYNCREATE(CMimicsEllipseCtrl, CMimicsCtrl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsEllipseCtrl, CMimicsCtrl)
	//{{AFX_MSG_MAP(CMimicsEllipseCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMimicsEllipseCtrl, CMimicsCtrl)
	//{{AFX_DISPATCH_MAP(CMimicsEllipseCtrl)
	DISP_PROPERTY_EX(CMimicsEllipseCtrl, "Style", GetStyle, SetStyle, VT_I4)
	DISP_PROPERTY_EX(CMimicsEllipseCtrl, "BorderSize", GetBorderSize, SetBorderSize, VT_I4)
	DISP_PROPERTY_EX(CMimicsEllipseCtrl, "BorderStyle", GetBorderStyle, SetBorderStyle, VT_I4)
	DISP_PROPERTY_EX(CMimicsEllipseCtrl, "BorderColor", GetBorderColor, SetBorderColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsEllipseCtrl, "InteriorColor", GetInteriorColor, SetInteriorColor, VT_COLOR)
	DISP_FUNCTION(CMimicsEllipseCtrl, "SetInteriorHatch", SetInteriorHatch, VT_EMPTY, VTS_I4 VTS_COLOR)
	DISP_FUNCTION(CMimicsEllipseCtrl, "GetInteriorHatch", GetInteriorHatch, VT_BOOL, VTS_PI4 VTS_PCOLOR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMimicsEllipseCtrl, CMimicsCtrl)
	//{{AFX_EVENT_MAP(CMimicsEllipseCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMimicsEllipseCtrl, 2)
	PROPPAGEID(CMimicsEllipseGeneralPage::guid)
	PROPPAGEID(CMimicsEllipseOutlinePage::guid)
END_PROPPAGEIDS(CMimicsEllipseCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsEllipseCtrl, "MIMICS.MimicsEllipseCtrl.1", 0xd9b0d9fa, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMimicsEllipseCtrl, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor)

/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMimicsEllipse = { 0xd9b0d9f8,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };
const IID BASED_CODE IID_DMimicsEllipseEvents = { 0xd9b0d9f9,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };

/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE  dwMimicsEllipseOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMimicsEllipseCtrl, IDS_MIMICSELLIPSECTRL_DESCRIPTIVENAME, dwMimicsEllipseOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseCtrl::CMimicsEllipseCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsEllipseCtrl

BOOL CMimicsEllipseCtrl::CMimicsEllipseCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterControlClass(AfxGetInstanceHandle(), m_clsid, m_lpszProgID, IDS_MIMICSELLIPSECTRL_DESCRIPTIVENAME, IDB_MIMICSELLIPSECTRL, afxRegApartmentThreading, dwMimicsEllipseOleMisc, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor) : AfxOleUnregisterClass(m_clsid, m_lpszProgID));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseCtrl

CMimicsEllipseCtrl::CMimicsEllipseCtrl() : CMimicsCtrl()
{
	m_szType = STRING(IDS_MIMICSELLIPSECTRL_TYPE);
	InitializeIIDs(&IID_DMimicsEllipse, &IID_DMimicsEllipseEvents);
	InitializeProps();
}

VOID CMimicsEllipseCtrl::InitializeProps()
{
	m_nStyle = MIMICSELLIPSECTRL_TYPE_NORMAL;
	m_nBorderSize = 1;
	m_nBorderStyle = PS_SOLID;
	m_nBorderColor = TranslateColor(VGA_COLOR_BLACK);
	m_nHatchColor = TranslateColor(VGA_COLOR_BLACK);
	m_nInteriorColor = TranslateColor(VGA_COLOR_WHITE);
	m_nInteriorHatch = -1;
}

void CMimicsEllipseCtrl::SetStyle(LONG nStyle)
{
	if (nStyle != m_nStyle)
	{
		m_nStyle = nStyle;
		Refresh();
	}
}

LONG CMimicsEllipseCtrl::GetStyle() CONST
{
	return m_nStyle;
}

void CMimicsEllipseCtrl::SetBorderSize(LONG nSize)
{
	if (nSize != m_nBorderSize)
	{
		m_nBorderSize = nSize;
		Refresh();
	}
}

LONG CMimicsEllipseCtrl::GetBorderSize() CONST
{
	return m_nBorderSize;
}

void CMimicsEllipseCtrl::SetBorderStyle(LONG nStyle)
{
	if (nStyle != m_nBorderStyle)
	{
		m_nBorderStyle = nStyle;
		Refresh();
	}
}

LONG CMimicsEllipseCtrl::GetBorderStyle() CONST
{
	return m_nBorderStyle;
}

void CMimicsEllipseCtrl::SetBorderColor(OLE_COLOR nColor)
{
	if (nColor != m_nBorderColor)
	{
		m_nBorderColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsEllipseCtrl::GetBorderColor() CONST
{
	return m_nBorderColor;
}

void CMimicsEllipseCtrl::SetInteriorColor(OLE_COLOR nColor)
{
	if (nColor != m_nInteriorColor)
	{
		m_nInteriorColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsEllipseCtrl::GetInteriorColor() CONST
{
	return m_nInteriorColor;
}

void CMimicsEllipseCtrl::SetInteriorHatch(LONG nHatch, OLE_COLOR nColor)
{
	if (nHatch != m_nInteriorHatch || nColor != m_nHatchColor)
	{
		m_nInteriorHatch = nHatch;
		m_nHatchColor = nColor;
		Refresh();
	}
}

BOOL CMimicsEllipseCtrl::GetInteriorHatch(LONG *pHatch, OLE_COLOR *pColor) CONST
{
	CopyMemory(pHatch, &m_nInteriorHatch, sizeof(LONG));
	CopyMemory(pColor, &m_nHatchColor, sizeof(COLORREF));
	return((m_nInteriorHatch >= 0) ? TRUE : FALSE);
}

VOID CMimicsEllipseCtrl::DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape)
{
	INT  nMode;
	HPEN  hOldPen;
	HPEN  hBorderPen;
	HBRUSH  hOldBrush;
	HBRUSH  hInteriorBrush;
	HBITMAP  hInteriorBitmap;
	LOGBRUSH  sInteriorBrush;
	COLORREF  nOldColor[2];

	if ((hBorderPen = CreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_JOIN_MITER | m_nBorderStyle, m_nBorderSize, GetNearestColor(hDC, (!bShape) ? m_nBorderColor : VGA_COLOR_WHITE))))
	{
		if ((hInteriorBitmap = LoadBitmap(GetModuleInstance(), (m_nInteriorHatch == HT_SOLID || m_nInteriorHatch < 0) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHSOLID) : ((m_nInteriorHatch == HT_HORIZONTAL) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHHORIZONTAL) : ((m_nInteriorHatch == HT_VERTICAL) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHVERTICAL) : ((m_nInteriorHatch == HT_BDIAGONAL) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHDIAGONALDOWN) : ((m_nInteriorHatch == HT_FDIAGONAL) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHDIAGONALUP) : ((m_nInteriorHatch == HT_CROSS) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHCROSS) : ((m_nInteriorHatch == HT_DIAGCROSS) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHCROSSDIAGONAL) : ((m_nInteriorHatch == HT_LPOINTS) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHPOINTSLOW) : ((m_nInteriorHatch == HT_MPOINTS) ? MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHPOINTSMEDIUM) : MAKEINTRESOURCE(IDB_MIMICSOBJECTCTLHATCHPOINTSHIGH))))))))))))
		{
			sInteriorBrush.lbStyle = (m_nInteriorColor != (COLORREF)-1) ? ((m_nInteriorHatch > 0) ? BS_PATTERN : BS_SOLID) : BS_HOLLOW;
			sInteriorBrush.lbColor = (sInteriorBrush.lbStyle == BS_SOLID) ? GetNearestColor(hDC, (!bShape) ? m_nInteriorColor : VGA_COLOR_WHITE) : 0;
			sInteriorBrush.lbHatch = (sInteriorBrush.lbStyle == BS_PATTERN) ? (ULONG_PTR)hInteriorBitmap : (ULONG_PTR)NULL;
			if ((hInteriorBrush = CreateBrushIndirect(&sInteriorBrush)) != (HBRUSH)NULL)
			{
				if ((hOldPen = (HPEN)SelectObject(hDC, hBorderPen)) != (HPEN)NULL)
				{
					if ((hOldBrush = (HBRUSH)SelectObject(hDC, hInteriorBrush)))
					{
						nMode = SetBkMode(hDC, OPAQUE);
						nOldColor[0] = SetBkColor(hDC, GetNearestColor(hDC, (!bShape) ? m_nInteriorColor : VGA_COLOR_WHITE));
						nOldColor[1] = SetTextColor(hDC, GetNearestColor(hDC, (!bShape) ? m_nHatchColor : VGA_COLOR_WHITE));
						Ellipse(hDC, pRect->left + m_nBorderSize / 2, pRect->top + m_nBorderSize / 2, pRect->right - m_nBorderSize / 2 - m_nBorderSize % 2, pRect->bottom - m_nBorderSize / 2 - m_nBorderSize % 2);
						SetTextColor(hDC, nOldColor[1]);
						SetBkColor(hDC, nOldColor[0]);
						SelectObject(hDC, hOldBrush);
						SetBkMode(hDC, nMode);
					}
					SelectObject(hDC, hOldPen);
				}
				DeleteObject(hInteriorBrush);
			}
			DeleteObject(hInteriorBitmap);
		}
		DeletePen(hBorderPen);
	}
}

void CMimicsEllipseCtrl::DoPropExchange(CPropExchange *pPX)
{
	ExchangeVersion(pPX, MAKELONG(CMimicsApp::wAppVerMinor, CMimicsApp::wAppVerMajor));
	CMimicsCtrl::DoPropExchange(pPX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseCtrl message handlers
