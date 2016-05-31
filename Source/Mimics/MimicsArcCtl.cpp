// MIMICSARCCTL.CPP : Mimics Arc Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics arc control
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/10/15 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////////////////////////////////////////////////////////////
// CMimicsArcCtrlDispatchDriver properties

VOID CMimicsArcCtrlDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsArcCtrlDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsArcCtrlDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsArcCtrlDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsArcCtrlDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsArcCtrlDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsArcCtrlDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsArcCtrlDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsArcCtrlDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsArcCtrlDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcCtrlDispatchDriver operations

VOID CMimicsArcCtrlDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsArcCtrlDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}

VOID CMimicsArcCtrlDispatchDriver::SetRadials(double fRadial1, double fRadial2)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETRADIALS));
	static BYTE  pParameters[] = VTS_R8 VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, fRadial1, fRadial2);
}

VOID CMimicsArcCtrlDispatchDriver::GetRadials(double &fRadial1, double &fRadial2) CONST
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETRADIALS));
	static BYTE  pParameters[] = VTS_PR8 VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &fRadial1, &fRadial2);
}


IMPLEMENT_DYNCREATE(CMimicsArcCtrl, CMimicsCtrl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsArcCtrl, CMimicsCtrl)
	//{{AFX_MSG_MAP(CMimicsArcCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMimicsArcCtrl, CMimicsCtrl)
	//{{AFX_DISPATCH_MAP(CMimicsArcCtrl)
	DISP_PROPERTY_EX(CMimicsArcCtrl, "Style", GetStyle, SetStyle, VT_I4)
	DISP_PROPERTY_EX(CMimicsArcCtrl, "BorderSize", GetBorderSize, SetBorderSize, VT_I4)
	DISP_PROPERTY_EX(CMimicsArcCtrl, "BorderStyle", GetBorderStyle, SetBorderStyle, VT_I4)
	DISP_PROPERTY_EX(CMimicsArcCtrl, "BorderColor", GetBorderColor, SetBorderColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsArcCtrl, "InteriorColor", GetInteriorColor, SetInteriorColor, VT_COLOR)
	DISP_FUNCTION(CMimicsArcCtrl, "SetInteriorHatch", SetInteriorHatch, VT_EMPTY, VTS_I4 VTS_COLOR)
	DISP_FUNCTION(CMimicsArcCtrl, "GetInteriorHatch", GetInteriorHatch, VT_BOOL, VTS_PI4 VTS_PCOLOR)
	DISP_FUNCTION(CMimicsArcCtrl, "SetRadials", SetRadials, VT_EMPTY, VTS_R8 VTS_R8)
	DISP_FUNCTION(CMimicsArcCtrl, "GetRadials", GetRadials, VT_EMPTY, VTS_PR8 VTS_PR8)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMimicsArcCtrl, CMimicsCtrl)
	//{{AFX_EVENT_MAP(CMimicsArcCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMimicsArcCtrl, 2)
	PROPPAGEID(CMimicsArcGeneralPage::guid)
	PROPPAGEID(CMimicsArcOutlinePage::guid)
END_PROPPAGEIDS(CMimicsArcCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsArcCtrl, "MIMICS.MimicsArcCtrl.1", 0xd9b0d9f5, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMimicsArcCtrl, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor)

/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMimicsArc = { 0xd9b0d9f3,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };
const IID BASED_CODE IID_DMimicsArcEvents = { 0xd9b0d9f4,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };

/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE  dwMimicsArcOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMimicsArcCtrl, IDS_MIMICSARCCTRL_DESCRIPTIVENAME, dwMimicsArcOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMimicsArcCtrl::CMimicsArcCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsArcCtrl

BOOL CMimicsArcCtrl::CMimicsArcCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterControlClass(AfxGetInstanceHandle(), m_clsid, m_lpszProgID, IDS_MIMICSARCCTRL_DESCRIPTIVENAME, IDB_MIMICSARCCTRL, afxRegApartmentThreading, dwMimicsArcOleMisc, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor) : AfxOleUnregisterClass(m_clsid, m_lpszProgID));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsArcCtrl

CMimicsArcCtrl::CMimicsArcCtrl() : CMimicsCtrl()
{
	m_szType = STRING(IDS_MIMICSARCCTRL_TYPE);
	InitializeIIDs(&IID_DMimicsArc, &IID_DMimicsArcEvents);
	InitializeProps();
}

VOID CMimicsArcCtrl::InitializeProps()
{
	m_nStyle = MIMICSARCCTRL_TYPE_ARC;
	m_nBorderSize = 1;
	m_nBorderStyle = PS_SOLID;
	m_nBorderColor = TranslateColor(VGA_COLOR_BLACK);
	m_nHatchColor = TranslateColor(VGA_COLOR_BLACK);
	m_nInteriorColor = TranslateColor(VGA_COLOR_WHITE);
	m_nInteriorHatch = -1;
	m_ptRadial[0] = 2.0*M_PI - M_PI / 4.0;
	m_ptRadial[1] = M_PI / 4.0;
}

void CMimicsArcCtrl::SetStyle(LONG nStyle)
{
	if (nStyle != m_nStyle)
	{
		m_nStyle = nStyle;
		Refresh();
	}
}

LONG CMimicsArcCtrl::GetStyle() CONST
{
	return m_nStyle;
}

void CMimicsArcCtrl::SetBorderSize(LONG nSize)
{
	if (nSize != m_nBorderSize)
	{
		m_nBorderSize = nSize;
		Refresh();
	}
}

LONG CMimicsArcCtrl::GetBorderSize() CONST
{
	return m_nBorderSize;
}

void CMimicsArcCtrl::SetBorderStyle(LONG nStyle)
{
	if (nStyle != m_nBorderStyle)
	{
		m_nBorderStyle = nStyle;
		Refresh();
	}
}

LONG CMimicsArcCtrl::GetBorderStyle() CONST
{
	return m_nBorderStyle;
}

void CMimicsArcCtrl::SetBorderColor(OLE_COLOR nColor)
{
	if (nColor != m_nBorderColor)
	{
		m_nBorderColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsArcCtrl::GetBorderColor() CONST
{
	return m_nBorderColor;
}

void CMimicsArcCtrl::SetInteriorColor(OLE_COLOR nColor)
{
	if (nColor != m_nInteriorColor)
	{
		m_nInteriorColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsArcCtrl::GetInteriorColor() CONST
{
	return m_nInteriorColor;
}

void CMimicsArcCtrl::SetInteriorHatch(LONG nHatch, OLE_COLOR nColor)
{
	if (nHatch != m_nInteriorHatch || nColor != m_nHatchColor)
	{
		m_nInteriorHatch = nHatch;
		m_nHatchColor = nColor;
		Refresh();
	}
}

BOOL CMimicsArcCtrl::GetInteriorHatch(LONG *pHatch, OLE_COLOR *pColor) CONST
{
	CopyMemory(pHatch, &m_nInteriorHatch, sizeof(LONG));
	CopyMemory(pColor, &m_nHatchColor, sizeof(COLORREF));
	return((m_nInteriorHatch >= 0) ? TRUE : FALSE);
}

void CMimicsArcCtrl::SetRadials(double fRadial1, double fRadial2)
{
	if (fRadial1 != m_ptRadial[0] || fRadial2 != m_ptRadial[1])
	{
		m_ptRadial[0] = fRadial1;
		m_ptRadial[1] = fRadial2;
		Refresh();
	}
}

void CMimicsArcCtrl::GetRadials(double *fRadial1, double *fRadial2) CONST
{
	CopyMemory(fRadial1, &m_ptRadial[0], sizeof(double));
	CopyMemory(fRadial2, &m_ptRadial[1], sizeof(double));
}

VOID CMimicsArcCtrl::DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape)
{
	INT  nPt;
	INT  nPts;
	INT  nMode;
	HPEN  hOldPen;
	HPEN  hBorderPen;
	POINT  ptRadial[2];
	double  fxRadial;
	double  fyRadial;
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
						for (nPt = 0, nPts = sizeof(ptRadial) / sizeof(POINT); nPt < nPts; nPt++)
						{
							fxRadial = (INT)((double)(pRect->left + pRect->right) / 2.0 + ((double)(pRect->right - pRect->left + pRect->bottom - pRect->top) / 2.0)*cos(2.0*M_PI - m_ptRadial[nPt]));
							fyRadial = (INT)((double)(pRect->top + pRect->bottom) / 2.0 + ((double)(pRect->right - pRect->left + pRect->bottom - pRect->top) / 2.0)*sin(2.0*M_PI - m_ptRadial[nPt]));
							ptRadial[nPt].x = (fxRadial >= 0.0) ? (INT)(fxRadial + 0.5) : (INT)(fxRadial - 0.5);
							ptRadial[nPt].y = (fyRadial >= 0.0) ? (INT)(fyRadial + 0.5) : (INT)(fyRadial - 0.5);
						}
						for (nMode = SetBkMode(hDC, OPAQUE), nOldColor[0] = SetBkColor(hDC, GetNearestColor(hDC, (!bShape) ? m_nInteriorColor : VGA_COLOR_WHITE)), nOldColor[1] = SetTextColor(hDC, GetNearestColor(hDC, (!bShape) ? m_nHatchColor : VGA_COLOR_WHITE)); m_nStyle & MIMICSARCCTRL_TYPE_ARC; )
						{
							Arc(hDC, pRect->left + m_nBorderSize / 2, pRect->top + m_nBorderSize / 2, pRect->right - m_nBorderSize / 2 - m_nBorderSize % 2, pRect->bottom - m_nBorderSize / 2 - m_nBorderSize % 2, ptRadial[0].x, ptRadial[0].y, ptRadial[1].x, ptRadial[1].y);
							break;
						}
						for (; m_nStyle & MIMICSARCCTRL_TYPE_PIE; )
						{
							Pie(hDC, pRect->left + m_nBorderSize / 2, pRect->top + m_nBorderSize / 2, pRect->right - m_nBorderSize / 2 - m_nBorderSize % 2, pRect->bottom - m_nBorderSize / 2 - m_nBorderSize % 2, ptRadial[0].x, ptRadial[0].y, ptRadial[1].x, ptRadial[1].y);
							break;
						}
						for (; m_nStyle & MIMICSARCCTRL_TYPE_CHORD; )
						{
							Chord(hDC, pRect->left + m_nBorderSize / 2, pRect->top + m_nBorderSize / 2, pRect->right - m_nBorderSize / 2 - m_nBorderSize % 2, pRect->bottom - m_nBorderSize / 2 - m_nBorderSize % 2, ptRadial[0].x, ptRadial[0].y, ptRadial[1].x, ptRadial[1].y);
							break;
						}
						SetBkMode(hDC, nMode);
						SetBkColor(hDC, nOldColor[0]);
						SetTextColor(hDC, nOldColor[1]);
						SelectObject(hDC, hOldBrush);
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

void CMimicsArcCtrl::DoPropExchange(CPropExchange *pPX)
{
	ExchangeVersion(pPX, MAKELONG(CMimicsApp::wAppVerMinor, CMimicsApp::wAppVerMajor));
	CMimicsCtrl::DoPropExchange(pPX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcCtrl message handlers
