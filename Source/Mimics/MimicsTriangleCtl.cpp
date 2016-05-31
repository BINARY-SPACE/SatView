// MIMICSTRIANGLECTL.CPP : Mimics Triangle Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics triangle
// control related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/06/05 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleCtrlDispatchDriver properties

VOID CMimicsTriangleCtrlDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsTriangleCtrlDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsTriangleCtrlDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsTriangleCtrlDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsTriangleCtrlDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsTriangleCtrlDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsTriangleCtrlDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTriangleCtrlDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsTriangleCtrlDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTriangleCtrlDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleCtrlDispatchDriver operations

VOID CMimicsTriangleCtrlDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsTriangleCtrlDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}

VOID CMimicsTriangleCtrlDispatchDriver::SetEdges(double x1, double y1, double x2, double y2, double x3, double y3)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETEDGES));
	static BYTE  pParameters[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, x1, y1, x2, y2, x3, y3);
}

VOID CMimicsTriangleCtrlDispatchDriver::GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETEDGES));
	static BYTE  pParameters[] = VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &x1, &y1, &x2, &y2, &x3, &y3);
}


IMPLEMENT_DYNCREATE(CMimicsTriangleCtrl, CMimicsCtrl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsTriangleCtrl, CMimicsCtrl)
	//{{AFX_MSG_MAP(CMimicsTriangleCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMimicsTriangleCtrl, CMimicsCtrl)
	//{{AFX_DISPATCH_MAP(CMimicsTriangleCtrl)
	DISP_PROPERTY_EX(CMimicsTriangleCtrl, "Style", GetStyle, SetStyle, VT_I4)
	DISP_PROPERTY_EX(CMimicsTriangleCtrl, "BorderSize", GetBorderSize, SetBorderSize, VT_I4)
	DISP_PROPERTY_EX(CMimicsTriangleCtrl, "BorderStyle", GetBorderStyle, SetBorderStyle, VT_I4)
	DISP_PROPERTY_EX(CMimicsTriangleCtrl, "BorderColor", GetBorderColor, SetBorderColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsTriangleCtrl, "InteriorColor", GetInteriorColor, SetInteriorColor, VT_COLOR)
	DISP_FUNCTION(CMimicsTriangleCtrl, "SetInteriorHatch", SetInteriorHatch, VT_EMPTY, VTS_I4 VTS_COLOR)
	DISP_FUNCTION(CMimicsTriangleCtrl, "GetInteriorHatch", GetInteriorHatch, VT_BOOL, VTS_PI4 VTS_PCOLOR)
	DISP_FUNCTION(CMimicsTriangleCtrl, "SetEdges", SetEdges, VT_EMPTY, VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8)
	DISP_FUNCTION(CMimicsTriangleCtrl, "GetEdges", GetEdges, VT_EMPTY, VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMimicsTriangleCtrl, CMimicsCtrl)
	//{{AFX_EVENT_MAP(CMimicsTriangleCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMimicsTriangleCtrl, 2)
	PROPPAGEID(CMimicsTriangleGeneralPage::guid)
	PROPPAGEID(CMimicsTriangleOutlinePage::guid)
END_PROPPAGEIDS(CMimicsTriangleCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsTriangleCtrl, "MIMICS.MimicsTriangleCtrl.1", 0xd9b0da04, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMimicsTriangleCtrl, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor)

/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMimicsTriangle = { 0xd9b0da02,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };
const IID BASED_CODE IID_DMimicsTriangleEvents = { 0xd9b0da03,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };

/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE  dwMimicsTriangleOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMimicsTriangleCtrl, IDS_MIMICSTRIANGLECTRL_DESCRIPTIVENAME, dwMimicsTriangleOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleCtrl::CMimicsTriangleCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsTriangleCtrl

BOOL CMimicsTriangleCtrl::CMimicsTriangleCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterControlClass(AfxGetInstanceHandle(), m_clsid, m_lpszProgID, IDS_MIMICSTRIANGLECTRL_DESCRIPTIVENAME, IDB_MIMICSTRIANGLECTRL, afxRegApartmentThreading, dwMimicsTriangleOleMisc, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor) : AfxOleUnregisterClass(m_clsid, m_lpszProgID));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleCtrl

CMimicsTriangleCtrl::CMimicsTriangleCtrl() : CMimicsCtrl()
{
	m_szType = STRING(IDS_MIMICSTRIANGLECTRL_TYPE);
	InitializeIIDs(&IID_DMimicsTriangle, &IID_DMimicsTriangleEvents);
	InitializeProps();
}

VOID CMimicsTriangleCtrl::InitializeProps()
{
	m_nStyle = MIMICSTRIANGLECTRL_TYPE_NORMAL;
	m_nBorderSize = 1;
	m_nBorderStyle = PS_SOLID;
	m_nBorderColor = TranslateColor(VGA_COLOR_BLACK);
	m_nHatchColor = TranslateColor(VGA_COLOR_BLACK);
	m_nInteriorColor = TranslateColor(VGA_COLOR_WHITE);
	m_nInteriorHatch = -1;
	m_ptEdges[0][0] = 0.0;
	m_ptEdges[0][1] = 1.0;
	m_ptEdges[1][0] = 1.0;
	m_ptEdges[1][1] = 1.0;
	m_ptEdges[2][0] = 0.5;
	m_ptEdges[2][1] = 0.0;
}

void CMimicsTriangleCtrl::SetStyle(LONG nStyle)
{
	if (nStyle != m_nStyle)
	{
		m_nStyle = nStyle;
		Refresh();
	}
}

LONG CMimicsTriangleCtrl::GetStyle() CONST
{
	return m_nStyle;
}

void CMimicsTriangleCtrl::SetBorderSize(LONG nSize)
{
	if (nSize != m_nBorderSize)
	{
		m_nBorderSize = nSize;
		Refresh();
	}
}

LONG CMimicsTriangleCtrl::GetBorderSize() CONST
{
	return m_nBorderSize;
}

void CMimicsTriangleCtrl::SetBorderStyle(LONG nStyle)
{
	if (nStyle != m_nBorderStyle)
	{
		m_nBorderStyle = nStyle;
		Refresh();
	}
}

LONG CMimicsTriangleCtrl::GetBorderStyle() CONST
{
	return m_nBorderStyle;
}

void CMimicsTriangleCtrl::SetBorderColor(OLE_COLOR nColor)
{
	if (nColor != m_nBorderColor)
	{
		m_nBorderColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsTriangleCtrl::GetBorderColor() CONST
{
	return m_nBorderColor;
}

void CMimicsTriangleCtrl::SetInteriorColor(OLE_COLOR nColor)
{
	if (nColor != m_nInteriorColor)
	{
		m_nInteriorColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsTriangleCtrl::GetInteriorColor() CONST
{
	return m_nInteriorColor;
}

void CMimicsTriangleCtrl::SetInteriorHatch(LONG nHatch, OLE_COLOR nColor)
{
	if (nHatch != m_nInteriorHatch || nColor != m_nHatchColor)
	{
		m_nInteriorHatch = nHatch;
		m_nHatchColor = nColor;
		Refresh();
	}
}

BOOL CMimicsTriangleCtrl::GetInteriorHatch(LONG *pHatch, OLE_COLOR *pColor) CONST
{
	CopyMemory(pHatch, &m_nInteriorHatch, sizeof(LONG));
	CopyMemory(pColor, &m_nHatchColor, sizeof(COLORREF));
	return((m_nInteriorHatch >= 0) ? TRUE : FALSE);
}

void CMimicsTriangleCtrl::SetEdges(double x1, double y1, double x2, double y2, double x3, double y3)
{
	if ((m_ptEdges[0][0] != x1 || m_ptEdges[0][1] != y1 || m_ptEdges[1][0] != x2 || m_ptEdges[1][1] != y2 || m_ptEdges[2][0] != x3 || m_ptEdges[2][1] != y3) && x1 >= 0.0  &&  x1 <= 1.0  &&  y1 >= 0.0  &&  y1 <= 1.0  &&  x2 >= 0.0  &&  x2 <= 1.0  &&  y2 >= 0.0  &&  y2 <= 1.0  &&  x3 >= 0.0  &&  x3 <= 1.0  &&  y3 >= 0.0  &&  y3 <= 1.0)
	{
		m_ptEdges[0][0] = x1;
		m_ptEdges[0][1] = y1;
		m_ptEdges[1][0] = x2;
		m_ptEdges[1][1] = y2;
		m_ptEdges[2][0] = x3;
		m_ptEdges[2][1] = y3;
		Refresh();
	}
}

void CMimicsTriangleCtrl::GetEdges(double *x1, double *y1, double *x2, double *y2, double *x3, double *y3) CONST
{
	CopyMemory(x1, &m_ptEdges[0][0], sizeof(double));
	CopyMemory(y1, &m_ptEdges[0][1], sizeof(double));
	CopyMemory(x2, &m_ptEdges[1][0], sizeof(double));
	CopyMemory(y2, &m_ptEdges[1][1], sizeof(double));
	CopyMemory(x3, &m_ptEdges[2][0], sizeof(double));
	CopyMemory(y3, &m_ptEdges[2][1], sizeof(double));
}

VOID CMimicsTriangleCtrl::DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape)
{
	INT  nMode;
	INT  nRgn;
	HRGN  hRgn;
	HRGN  hOldRgn;
	HPEN  hOldPen;
	HPEN  hBorderPen;
	float  fMiter[2];
	POINT  ptClip[4];
	POINT  ptEdge[3];
	HBRUSH  hOldBrush;
	HBRUSH  hInteriorBrush;
	HBITMAP  hInteriorBitmap;
	LOGBRUSH  sInteriorBrush;
	COLORREF  nOldColor[2];

	if ((hBorderPen = CreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_JOIN_MITER | m_nBorderStyle, (m_nBorderSize > 1) ? (2 * m_nBorderSize) : m_nBorderSize, GetNearestColor(hDC, (!bShape) ? m_nBorderColor : VGA_COLOR_WHITE))))
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
						SetMiterLimit(hDC, (fMiter[0] = (float)max(pRect->right - pRect->left, pRect->bottom - pRect->top)), &fMiter[1]);
						ptEdge[0].x = (INT)(pRect->left + m_ptEdges[0][0] * (pRect->right - pRect->left));
						ptEdge[0].y = (INT)(pRect->top + m_ptEdges[0][1] * (pRect->bottom - pRect->top));
						ptEdge[1].x = (INT)(pRect->left + m_ptEdges[1][0] * (pRect->right - pRect->left));
						ptEdge[1].y = (INT)(pRect->top + m_ptEdges[1][1] * (pRect->bottom - pRect->top));
						ptEdge[2].x = (INT)(pRect->left + m_ptEdges[2][0] * (pRect->right - pRect->left));
						ptEdge[2].y = (INT)(pRect->top + m_ptEdges[2][1] * (pRect->bottom - pRect->top));
						ptEdge[0].x = (m_nBorderSize == 1) ? (ptEdge[0].x + 1) : ptEdge[0].x;
						ptEdge[1].x = (m_nBorderSize == 1) ? (ptEdge[1].x - 1) : ptEdge[1].x;
						ptEdge[0].y = (m_nBorderSize == 1) ? ((ptEdge[0].y >= ptEdge[2].y) ? (ptEdge[0].y - 1) : (ptEdge[0].y + 1)) : ptEdge[0].y;
						ptEdge[1].y = (m_nBorderSize == 1) ? ((ptEdge[1].y >= ptEdge[2].y) ? (ptEdge[1].y - 1) : (ptEdge[1].y + 1)) : ptEdge[1].y;
						ptEdge[2].y = (m_nBorderSize == 1) ? ((ptEdge[0].y >= ptEdge[2].y) ? (ptEdge[2].y + 1) : (ptEdge[2].y - 1)) : ptEdge[2].y;
						ptClip[0].x = (m_nBorderSize == 1) ? (pRect->left - 1) : ptEdge[0].x;
						ptClip[0].y = (m_nBorderSize == 1) ? (pRect->top - 1) : ptEdge[0].y;
						ptClip[1].x = (m_nBorderSize == 1) ? (pRect->right + 1) : ptEdge[1].x;
						ptClip[1].y = (m_nBorderSize == 1) ? (pRect->top - 1) : ptEdge[1].y;
						ptClip[2].x = (m_nBorderSize == 1) ? (pRect->right + 1) : ptEdge[2].x;
						ptClip[2].y = (m_nBorderSize == 1) ? (pRect->bottom + 1) : ptEdge[2].y;
						ptClip[3].x = (m_nBorderSize == 1) ? (pRect->left - 1) : 0;
						ptClip[3].y = (m_nBorderSize == 1) ? (pRect->bottom + 1) : 0;
						LPtoDP(hDC, ptClip, sizeof(ptClip) / sizeof(POINT));
						if ((hRgn = CreatePolygonRgn(ptClip, (m_nBorderSize > 1) ? (sizeof(ptClip) / sizeof(POINT) - 1) : (sizeof(ptClip) / sizeof(POINT)), WINDING)))
						{
							if ((hOldRgn = CreateRectRgn(0, 0, 0, 0)))
							{
								if ((nRgn = GetClipRgn(hDC, hOldRgn)) >= 0)
								{
									if (ExtSelectClipRgn(hDC, hRgn, RGN_AND) != ERROR)
									{
										Polygon(hDC, ptEdge, sizeof(ptEdge) / sizeof(ptEdge[0]));
										SelectClipRgn(hDC, (nRgn > 0) ? hOldRgn : (HRGN)NULL);
									}
								}
								DeleteObject(hOldRgn);
							}
							DeleteObject(hRgn);
						}
						SetBkMode(hDC, nMode);
						SetBkColor(hDC, nOldColor[0]);
						SetTextColor(hDC, nOldColor[1]);
						SetMiterLimit(hDC, fMiter[1], (float *)NULL);
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

void CMimicsTriangleCtrl::DoPropExchange(CPropExchange *pPX)
{
	ExchangeVersion(pPX, MAKELONG(CMimicsApp::wAppVerMinor, CMimicsApp::wAppVerMajor));
	CMimicsCtrl::DoPropExchange(pPX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleCtrl message handlers
