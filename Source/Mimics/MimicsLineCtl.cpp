// MIMICSLINECTL.CPP : Mimics Line Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics line
// control related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/03 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////////////////////////////////////////////////////////////
// CMimicsLineCtrlDispatchDriver properties

VOID CMimicsLineCtrlDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsLineCtrlDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsLineCtrlDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsLineCtrlDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsLineCtrlDispatchDriver::SetThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsLineCtrlDispatchDriver::GetThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineCtrlDispatchDriver operations

VOID CMimicsLineCtrlDispatchDriver::Arrow(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ARROW));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

VOID CMimicsLineCtrlDispatchDriver::DoubleArrow(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DOUBLEARROW));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

VOID CMimicsLineCtrlDispatchDriver::Cross(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_CROSS));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsLineCtrlDispatchDriver::SetCrossPt(double fPt)
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETCROSSPT));
	static BYTE  pParameters[] = VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, fPt);
	return bResult;
}

BOOL CMimicsLineCtrlDispatchDriver::GetCrossPt(double *fPt) CONST
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETCROSSPT));
	static BYTE  pParameters[] = VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, fPt);
	return bResult;
}

BOOL CMimicsLineCtrlDispatchDriver::IsArrow() CONST
{
	BOOL  bArrow;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISARROW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bArrow, (const BYTE *)NULL);
	return bArrow;
}

BOOL CMimicsLineCtrlDispatchDriver::IsDoubleArrow() CONST
{
	BOOL  bDoubleArrow;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDOUBLEARROW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDoubleArrow, (const BYTE *)NULL);
	return bDoubleArrow;
}

BOOL CMimicsLineCtrlDispatchDriver::IsCross() CONST
{
	BOOL  bCross;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCROSS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bCross, (const BYTE *)NULL);
	return bCross;
}

VOID CMimicsLineCtrlDispatchDriver::Solid()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SOLID));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineCtrlDispatchDriver::Dash()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASH));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineCtrlDispatchDriver::Dot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineCtrlDispatchDriver::DashDot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASHDOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineCtrlDispatchDriver::DashDotDot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASHDOTDOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsLineCtrlDispatchDriver::IsSolid() CONST
{
	BOOL  bSolid;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISSOLID));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bSolid, (const BYTE *)NULL);
	return bSolid;
}

BOOL CMimicsLineCtrlDispatchDriver::IsDashed() CONST
{
	BOOL  bDashed;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashed, (const BYTE *)NULL);
	return bDashed;
}

BOOL CMimicsLineCtrlDispatchDriver::IsDotted() CONST
{
	BOOL  bDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDotted, (const BYTE *)NULL);
	return bDotted;
}

BOOL CMimicsLineCtrlDispatchDriver::IsDashDotted() CONST
{
	BOOL  bDashDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashDotted, (const BYTE *)NULL);
	return bDashDotted;
}

BOOL CMimicsLineCtrlDispatchDriver::IsDashDotDotted() CONST
{
	BOOL  bDashDotDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHDOTDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashDotDotted, (const BYTE *)NULL);
	return bDashDotDotted;
}


IMPLEMENT_DYNCREATE(CMimicsLineCtrl, CMimicsCtrl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsLineCtrl, CMimicsCtrl)
	//{{AFX_MSG_MAP(CMimicsLineCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMimicsLineCtrl, CMimicsCtrl)
	//{{AFX_DISPATCH_MAP(CMimicsLineCtrl)
	DISP_PROPERTY_EX(CMimicsLineCtrl, "Style", GetStyle, SetStyle, VT_I4)
	DISP_PROPERTY_EX(CMimicsLineCtrl, "Color", GetColor, SetColor, VT_COLOR)
	DISP_PROPERTY_EX(CMimicsLineCtrl, "Thickness", GetThickness, SetThickness, VT_I4)
	DISP_FUNCTION(CMimicsLineCtrl, "Arrow", Arrow, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CMimicsLineCtrl, "DoubleArrow", DoubleArrow, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CMimicsLineCtrl, "Cross", Cross, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CMimicsLineCtrl, "SetCrossPt", SetCrossPt, VT_BOOL, VTS_R8)
	DISP_FUNCTION(CMimicsLineCtrl, "GetCrossPt", GetCrossPt, VT_BOOL, VTS_PR8)
	DISP_FUNCTION(CMimicsLineCtrl, "IsArrow", IsArrow, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "IsDoubleArrow", IsDoubleArrow, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "IsCross", IsCross, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "Solid", Solid, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "Dash", Dash, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "Dot", Dot, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "DashDot", DashDot, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "DashDotDot", DashDotDot, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "IsSolid", IsSolid, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "IsDashed", IsDashed, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "IsDotted", IsDotted, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "IsDashDotted", IsDashDotted, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsLineCtrl, "IsDashDotDotted", IsDashDotDotted, VT_BOOL, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMimicsLineCtrl, CMimicsCtrl)
	//{{AFX_EVENT_MAP(CMimicsLineCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMimicsLineCtrl, 2)
	PROPPAGEID(CMimicsLineGeneralPage::guid)
	PROPPAGEID(CMimicsLineOutlinePage::guid)
END_PROPPAGEIDS(CMimicsLineCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsLineCtrl, "MIMICS.MimicsLineCtrl.1", 0xd9b0d9f0, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMimicsLineCtrl, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor)

/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMimicsLine = { 0xd9b0d9ee,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };
const IID BASED_CODE IID_DMimicsLineEvents = { 0xd9b0d9ef,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };

/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE  dwMimicsLineOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMimicsLineCtrl, IDS_MIMICSLINECTRL_DESCRIPTIVENAME, dwMimicsLineOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineCtrl::CMimicsLineCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsLineCtrl

BOOL CMimicsLineCtrl::CMimicsLineCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterControlClass(AfxGetInstanceHandle(), m_clsid, m_lpszProgID, IDS_MIMICSLINECTRL_DESCRIPTIVENAME, IDB_MIMICSLINECTRL, afxRegApartmentThreading, dwMimicsLineOleMisc, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor) : AfxOleUnregisterClass(m_clsid, m_lpszProgID));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineCtrl

CMimicsLineCtrl::CMimicsLineCtrl() : CMimicsCtrl()
{
	m_szType = STRING(IDS_MIMICSLINECTRL_TYPE);
	SetInitialSize((m_sizeCtrl.cx = MIMICSLINECTRL_DEFAULT_CX), (m_sizeCtrl.cy = MIMICSLINECTRL_DEFAULT_CY));
	InitializeIIDs(&IID_DMimicsLine, &IID_DMimicsLineEvents);
	InitializeProps();
}

void CMimicsLineCtrl::InitializeProps()
{
	m_nStyle = MIMICSLINECTRL_STYLE_SOLID;
	m_nColor = TranslateColor(VGA_COLOR_BLACK);
	m_fPtCross = 0.0;
	m_nWidth = 1;
}

void CMimicsLineCtrl::SetStyle(LONG nStyle)
{
	if (nStyle != m_nStyle)
	{
		m_nStyle = nStyle;
		Refresh();
	}
}

LONG CMimicsLineCtrl::GetStyle() CONST
{
	return m_nStyle;
}

void CMimicsLineCtrl::Arrow(BOOL bEnable)
{
	if (((m_nStyle & MIMICSLINECTRL_STYLE_ARROW) && !bEnable) || ((m_nStyle & MIMICSLINECTRL_STYLE_ARROW) != MIMICSLINECTRL_STYLE_ARROW  &&  bEnable))
	{
		m_nStyle = (bEnable) ? (m_nStyle | MIMICSLINECTRL_STYLE_ARROW) : (m_nStyle & ~MIMICSLINECTRL_STYLE_ARROW);
		Refresh();
	}
}

void CMimicsLineCtrl::DoubleArrow(BOOL bEnable)
{
	if (((m_nStyle & MIMICSLINECTRL_STYLE_DOUBLEARROW) && !bEnable) || ((m_nStyle & MIMICSLINECTRL_STYLE_DOUBLEARROW) != MIMICSLINECTRL_STYLE_DOUBLEARROW  &&  bEnable))
	{
		m_nStyle = (bEnable) ? (m_nStyle | MIMICSLINECTRL_STYLE_DOUBLEARROW) : (m_nStyle & ~MIMICSLINECTRL_STYLE_DOUBLEARROW);
		Refresh();
	}
}

void CMimicsLineCtrl::Cross(BOOL bEnable)
{
	if (((m_nStyle & MIMICSLINECTRL_STYLE_CROSSING) && !bEnable) || ((m_nStyle & MIMICSLINECTRL_STYLE_CROSSING) != MIMICSLINECTRL_STYLE_CROSSING  &&  bEnable))
	{
		m_nStyle = (bEnable) ? (m_nStyle | MIMICSLINECTRL_STYLE_CROSSING) : (m_nStyle & ~MIMICSLINECTRL_STYLE_CROSSING);
		m_fPtCross = (bEnable) ? 0.5 : 0.0;
		Refresh();
	}
}

BOOL CMimicsLineCtrl::SetCrossPt(double fPt)
{
	if (m_nStyle & MIMICSLINECTRL_STYLE_CROSSING)
	{
		if (fPt >= 0.0  &&  fPt <= 1.0)
		{
			m_fPtCross = fPt;
			Refresh();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMimicsLineCtrl::GetCrossPt(double *fPt) CONST
{
	CopyMemory(fPt, &m_fPtCross, sizeof(double));
	return((m_nStyle & MIMICSLINECTRL_STYLE_CROSSING) ? TRUE : FALSE);
}

BOOL CMimicsLineCtrl::IsArrow() CONST
{
	return((m_nStyle & MIMICSLINECTRL_STYLE_ARROW) ? TRUE : FALSE);
}

BOOL CMimicsLineCtrl::IsDoubleArrow() CONST
{
	return((m_nStyle & MIMICSLINECTRL_STYLE_DOUBLEARROW) ? TRUE : FALSE);
}

BOOL CMimicsLineCtrl::IsCross() CONST
{
	return((m_nStyle & MIMICSLINECTRL_STYLE_CROSSING) ? TRUE : FALSE);
}

void CMimicsLineCtrl::SetColor(OLE_COLOR nColor)
{
	if (nColor != m_nColor)
	{
		m_nColor = nColor;
		Refresh();
	}
}

OLE_COLOR CMimicsLineCtrl::GetColor() CONST
{
	return m_nColor;
}

void CMimicsLineCtrl::SetThickness(LONG nWidth)
{
	if (nWidth != m_nWidth)
	{
		m_nWidth = nWidth;
		Refresh();
	}
}

LONG CMimicsLineCtrl::GetThickness() CONST
{
	return m_nWidth;
}

void CMimicsLineCtrl::Solid()
{
	if ((m_nStyle & MIMICSLINECTRL_STYLE_SOLID) != MIMICSLINECTRL_STYLE_SOLID)
	{
		m_nStyle &= ~(MIMICSLINECTRL_STYLE_SOLID | MIMICSLINECTRL_STYLE_DASH | MIMICSLINECTRL_STYLE_DOT | MIMICSLINECTRL_STYLE_DASHDOT | MIMICSLINECTRL_STYLE_DASHDOTDOT);
		m_nStyle |= MIMICSLINECTRL_STYLE_SOLID;
		Refresh();
	}
}

void CMimicsLineCtrl::Dash()
{
	if ((m_nStyle & MIMICSLINECTRL_STYLE_DASH) != MIMICSLINECTRL_STYLE_DASH)
	{
		m_nStyle &= ~(MIMICSLINECTRL_STYLE_SOLID | MIMICSLINECTRL_STYLE_DASH | MIMICSLINECTRL_STYLE_DOT | MIMICSLINECTRL_STYLE_DASHDOT | MIMICSLINECTRL_STYLE_DASHDOTDOT);
		m_nStyle |= MIMICSLINECTRL_STYLE_DASH;
		Refresh();
	}
}

void CMimicsLineCtrl::Dot()
{
	if ((m_nStyle & MIMICSLINECTRL_STYLE_DOT) != MIMICSLINECTRL_STYLE_DOT)
	{
		m_nStyle &= ~(MIMICSLINECTRL_STYLE_SOLID | MIMICSLINECTRL_STYLE_DASH | MIMICSLINECTRL_STYLE_DOT | MIMICSLINECTRL_STYLE_DASHDOT | MIMICSLINECTRL_STYLE_DASHDOTDOT);
		m_nStyle |= MIMICSLINECTRL_STYLE_DOT;
		Refresh();
	}
}

void CMimicsLineCtrl::DashDot()
{
	if ((m_nStyle & MIMICSLINECTRL_STYLE_DASHDOT) != MIMICSLINECTRL_STYLE_DASHDOT)
	{
		m_nStyle &= ~(MIMICSLINECTRL_STYLE_SOLID | MIMICSLINECTRL_STYLE_DASH | MIMICSLINECTRL_STYLE_DOT | MIMICSLINECTRL_STYLE_DASHDOT | MIMICSLINECTRL_STYLE_DASHDOTDOT);
		m_nStyle |= MIMICSLINECTRL_STYLE_DASHDOT;
		Refresh();
	}
}

void CMimicsLineCtrl::DashDotDot()
{
	if ((m_nStyle & MIMICSLINECTRL_STYLE_DASHDOTDOT) != MIMICSLINECTRL_STYLE_DASHDOTDOT)
	{
		m_nStyle &= ~(MIMICSLINECTRL_STYLE_SOLID | MIMICSLINECTRL_STYLE_DASH | MIMICSLINECTRL_STYLE_DOT | MIMICSLINECTRL_STYLE_DASHDOT | MIMICSLINECTRL_STYLE_DASHDOTDOT);
		m_nStyle |= MIMICSLINECTRL_STYLE_DASHDOTDOT;
		Refresh();
	}
}

BOOL CMimicsLineCtrl::IsSolid() CONST
{
	return((m_nStyle & MIMICSLINECTRL_STYLE_SOLID) ? TRUE : FALSE);
}

BOOL CMimicsLineCtrl::IsDashed() CONST
{
	return((m_nStyle & MIMICSLINECTRL_STYLE_DASH) ? TRUE : FALSE);
}

BOOL CMimicsLineCtrl::IsDotted() CONST
{
	return((m_nStyle & MIMICSLINECTRL_STYLE_DOT) ? TRUE : FALSE);
}

BOOL CMimicsLineCtrl::IsDashDotted() CONST
{
	return((m_nStyle & MIMICSLINECTRL_STYLE_DASHDOT) ? TRUE : FALSE);
}

BOOL CMimicsLineCtrl::IsDashDotDotted() CONST
{
	return((m_nStyle & MIMICSLINECTRL_STYLE_DASHDOTDOT) ? TRUE : FALSE);
}

VOID CMimicsLineCtrl::DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape)
{
	INT  dx;
	INT  dy;
	INT  dl;
	INT  dw;
	INT  dc;
	INT  nPt;
	INT  nPts;
	INT  x[2];
	INT  y[2];
	INT  nArc;
	RECT  rLine;
	HPEN  hPen;
	HPEN  hOldPen;
	POINT  ptLine[2];
	POINT  ptArrow[3];
	XFORM  xTransform;
	HBRUSH  hOldBrush;
	HBRUSH  hArrowBrush;
	double  fPtCross[2];
	double  fAngle;
	double  fx, fy;

	if ((hPen = CreatePen((m_nStyle & MIMICSLINECTRL_STYLE_SOLID) ? (PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_BEVEL) : ((m_nStyle & MIMICSLINECTRL_STYLE_DASH) ? (PS_GEOMETRIC | PS_DASH | PS_ENDCAP_FLAT | PS_JOIN_BEVEL) : ((m_nStyle & MIMICSLINECTRL_STYLE_DOT) ? (PS_GEOMETRIC | PS_DOT | PS_ENDCAP_FLAT | PS_JOIN_BEVEL) : ((m_nStyle & MIMICSLINECTRL_STYLE_DASHDOT) ? (PS_GEOMETRIC | PS_DASHDOT | PS_ENDCAP_FLAT | PS_JOIN_BEVEL) : ((m_nStyle & MIMICSLINECTRL_STYLE_DASHDOTDOT) ? (PS_GEOMETRIC | PS_DASHDOTDOT | PS_ENDCAP_FLAT | PS_JOIN_BEVEL) : (PS_GEOMETRIC | PS_NULL | PS_ENDCAP_FLAT | PS_JOIN_BEVEL))))), m_nWidth, GetNearestColor(hDC, (!bShape) ? m_nColor : VGA_COLOR_WHITE))))
	{
		if ((hOldPen = (HPEN)SelectObject(hDC, hPen)))
		{
			ptLine[0].x = pRect->right;
			ptLine[0].y = pRect->bottom;
			ptLine[1].x = pRect->left;
			ptLine[1].y = pRect->top;
			dx = pRect->right - pRect->left;
			dy = pRect->bottom - pRect->top;
			dl = 10 + 2 * m_nWidth;
			if (m_nStyle & MIMICSLINECTRL_STYLE_ARROW)
			{
				fx = (dx || dy) ? (double)(dl*dx) : 0.0;
				fy = (dx || dy) ? (double)(dl*dy) : 0.0;
				fx = (dx || dy) ? (fx / sqrt((double)(dx*dx + dy*dy))) : 0.0;
				fy = (dx || dy) ? (fy / sqrt((double)(dx*dx + dy*dy))) : 0.0;
				ptLine[0].x = (INT)(pRect->right - fx);
				ptLine[0].y = (INT)(pRect->bottom - fy);
			}
			if (m_nStyle & MIMICSLINECTRL_STYLE_DOUBLEARROW)
			{
				fx = (dx || dy) ? (double)(dl*dx) : 0.0;
				fy = (dx || dy) ? (double)(dl*dy) : 0.0;
				fx = (dx || dy) ? (fx / sqrt((double)(dx*dx + dy*dy))) : 0.0;
				fy = (dx || dy) ? (fy / sqrt((double)(dx*dx + dy*dy))) : 0.0;
				ptLine[0].x = (INT)(pRect->right - fx);
				ptLine[0].y = (INT)(pRect->bottom - fy);
				ptLine[1].x = (INT)(pRect->left + fx);
				ptLine[1].y = (INT)(pRect->top + fy);
			}
			if (m_nStyle & MIMICSLINECTRL_STYLE_CROSSING)
			{
				dx = abs(dx);
				dy = abs(dy);
				dc = 3 + m_nWidth;
				fPtCross[1] = (double) 0.0;
				if (dx >= dy  &&  dx > 0)
				{
					fPtCross[0] = fabs((double)(dc + m_nWidth / 2 + 1)) / (double)dx;
					fPtCross[1] = (m_fPtCross < fPtCross[0]) ? fPtCross[0] : m_fPtCross;
					fPtCross[1] = (m_fPtCross > 1.0 - fPtCross[0]) ? (1.0 - fPtCross[0]) : fPtCross[1];
				}
				if (dx < dy)
				{
					fPtCross[0] = fabs((double)(dc + m_nWidth / 2 + 1)) / (double)dy;
					fPtCross[1] = (m_fPtCross < fPtCross[0]) ? fPtCross[0] : m_fPtCross;
					fPtCross[1] = (m_fPtCross > 1.0 - fPtCross[0]) ? (1.0 - fPtCross[0]) : fPtCross[1];
				}
				x[0] = (INT)(pRect->left + (pRect->right - pRect->left)*fPtCross[1] - dc - 1);
				y[0] = (INT)(pRect->top + (pRect->bottom - pRect->top)*fPtCross[1] - dc - 1);
				x[1] = (INT)(pRect->left + (pRect->right - pRect->left)*fPtCross[1] + dc + 1);
				y[1] = (INT)(pRect->top + (pRect->bottom - pRect->top)*fPtCross[1] + dc + 1);
				nArc = SetArcDirection(hDC, AD_CLOCKWISE);
				MoveToEx(hDC, ptLine[1].x, ptLine[1].y, (LPPOINT)NULL);
				ArcTo(hDC, x[0], y[0], x[1], y[1], ptLine[1].x, ptLine[1].y, ptLine[0].x, ptLine[0].y);
				SetArcDirection(hDC, nArc);
				MoveToEx(hDC, ptLine[0].x, ptLine[0].y, (LPPOINT)NULL);
				ArcTo(hDC, x[0], y[0], x[1], y[1], ptLine[0].x, ptLine[0].y, ptLine[1].x, ptLine[1].y);
			}
			else
			{
				MoveToEx(hDC, ptLine[1].x, ptLine[1].y, (LPPOINT)NULL);
				LineTo(hDC, ptLine[0].x, ptLine[0].y);
			}
			SelectObject(hDC, hOldPen);
		}
		DeleteObject(hPen);
	}
	if ((m_nStyle & MIMICSLINECTRL_STYLE_ARROW) || (m_nStyle & MIMICSLINECTRL_STYLE_DOUBLEARROW))
	{
		if ((hPen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_JOIN_MITER, m_nWidth, GetNearestColor(hDC, (!bShape) ? m_nColor : VGA_COLOR_WHITE))))
		{
			if ((hArrowBrush = CreateSolidBrush(GetNearestColor(hDC, (!bShape) ? m_nColor : VGA_COLOR_WHITE))))
			{
				if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
				{
					if ((hOldBrush = (HBRUSH)SelectObject(hDC, hArrowBrush)))
					{
						dx = pRect->right - pRect->left;
						dy = pRect->bottom - pRect->top;
						dl = 10 + 2 * m_nWidth;
						dw = dl / 3;
						if (abs(dy) >= 0 && !dx)
						{
							ptArrow[0].x = pRect->right;
							ptArrow[1].x = pRect->right - dw;
							ptArrow[2].x = pRect->right + dw;
							ptArrow[0].y = (pRect->top <= pRect->bottom) ? (pRect->bottom - (m_nWidth*dl) / (2 * dw)) : (pRect->bottom + (m_nWidth*dl) / (2 * dw));
							ptArrow[1].y = (pRect->top <= pRect->bottom) ? (pRect->bottom - dl - (m_nWidth*dl) / (2 * dw)) : (pRect->bottom + dl + (m_nWidth*dl) / (2 * dw));
							ptArrow[2].y = (pRect->top <= pRect->bottom) ? (pRect->bottom - dl - (m_nWidth*dl) / (2 * dw)) : (pRect->bottom + dl + (m_nWidth*dl) / (2 * dw));
							Polygon(hDC, ptArrow, sizeof(ptArrow) / sizeof(POINT));
							if (m_nStyle & MIMICSLINECTRL_STYLE_DOUBLEARROW)
							{
								ptArrow[0].x = pRect->left;
								ptArrow[1].x = pRect->left - dw;
								ptArrow[2].x = pRect->left + dw;
								ptArrow[0].y = (pRect->top <= pRect->bottom) ? (pRect->top + (m_nWidth*dl) / (2 * dw)) : (pRect->top - (m_nWidth*dl) / (2 * dw));
								ptArrow[1].y = (pRect->top <= pRect->bottom) ? (pRect->top + dl + (m_nWidth*dl) / (2 * dw)) : (pRect->top - dl - (m_nWidth*dl) / (2 * dw));
								ptArrow[2].y = (pRect->top <= pRect->bottom) ? (pRect->top + dl + (m_nWidth*dl) / (2 * dw)) : (pRect->top - dl - (m_nWidth*dl) / (2 * dw));
								Polygon(hDC, ptArrow, sizeof(ptArrow) / sizeof(POINT));
							}
						}
						else
						{
							fAngle = atan((double)dy / (double)dx);
							xTransform.eM11 = (float)cos(fAngle);
							xTransform.eM12 = (float)sin(fAngle);
							xTransform.eM21 = (float)-sin(fAngle);
							xTransform.eM22 = (float)cos(fAngle);
							xTransform.eDx = (float)((pRect->left + pRect->right) / 2);
							xTransform.eDy = (float)((pRect->top + pRect->bottom) / 2);
							rLine.top = rLine.bottom = (pRect->top + pRect->bottom) / 2;
							rLine.left = (INT)((pRect->left + pRect->right) / 2 - sqrt((double)(dx*dx + dy*dy)) / 2.0 + 0.5);
							rLine.right = (INT)((pRect->left + pRect->right) / 2 + sqrt((double)(dx*dx + dy*dy)) / 2.0 + 0.5);
							ptArrow[0].x = (pRect->left <= pRect->right) ? (rLine.right - (m_nWidth*dl) / (2 * dw)) : (rLine.left + (m_nWidth*dl) / (2 * dw));
							ptArrow[1].x = (pRect->left <= pRect->right) ? (rLine.right - dl - (m_nWidth*dl) / (2 * dw)) : (rLine.left + dl + (m_nWidth*dl) / (2 * dw));
							ptArrow[2].x = (pRect->left <= pRect->right) ? (rLine.right - dl - (m_nWidth*dl) / (2 * dw)) : (rLine.left + dl + (m_nWidth*dl) / (2 * dw));
							ptArrow[0].y = (pRect->top + pRect->bottom) / 2;
							ptArrow[1].y = (pRect->top + pRect->bottom) / 2 - dw;
							ptArrow[2].y = (pRect->top + pRect->bottom) / 2 + dw;
							for (nPt = 0, nPts = sizeof(ptArrow) / sizeof(POINT); nPt < nPts; nPt++)
							{
								fx = (double)((ptArrow[nPt].x - xTransform.eDx)*xTransform.eM11 + (ptArrow[nPt].y - xTransform.eDy)*xTransform.eM21 + xTransform.eDx);
								fy = (double)((ptArrow[nPt].x - xTransform.eDx)*xTransform.eM12 + (ptArrow[nPt].y - xTransform.eDy)*xTransform.eM22 + xTransform.eDy);
								ptArrow[nPt].x = (fx >= 0.0) ? (INT)(fx + 0.5) : (INT)(fx - 0.5);
								ptArrow[nPt].y = (fy >= 0.0) ? (INT)(fy + 0.5) : (INT)(fy - 0.5);
							}
							Polygon(hDC, ptArrow, sizeof(ptArrow) / sizeof(POINT));
							if (m_nStyle & MIMICSLINECTRL_STYLE_DOUBLEARROW)
							{
								ptArrow[0].x = (pRect->left <= pRect->right) ? (rLine.left + (m_nWidth*dl) / (2 * dw)) : (rLine.right - (m_nWidth*dl) / (2 * dw));
								ptArrow[1].x = (pRect->left <= pRect->right) ? (rLine.left + dl + (m_nWidth*dl) / (2 * dw)) : (rLine.right - dl - (m_nWidth*dl) / (2 * dw));
								ptArrow[2].x = (pRect->left <= pRect->right) ? (rLine.left + dl + (m_nWidth*dl) / (2 * dw)) : (rLine.right - dl - (m_nWidth*dl) / (2 * dw));
								ptArrow[0].y = (pRect->top + pRect->bottom) / 2;
								ptArrow[1].y = (pRect->top + pRect->bottom) / 2 - dw;
								ptArrow[2].y = (pRect->top + pRect->bottom) / 2 + dw;
								for (nPt = 0, nPts = sizeof(ptArrow) / sizeof(POINT); nPt < nPts; nPt++)
								{
									fx = (double)((ptArrow[nPt].x - xTransform.eDx)*xTransform.eM11 + (ptArrow[nPt].y - xTransform.eDy)*xTransform.eM21 + xTransform.eDx);
									fy = (double)((ptArrow[nPt].x - xTransform.eDx)*xTransform.eM12 + (ptArrow[nPt].y - xTransform.eDy)*xTransform.eM22 + xTransform.eDy);
									ptArrow[nPt].x = (fx >= 0.0) ? (INT)(fx + 0.5) : (INT)(fx - 0.5);
									ptArrow[nPt].y = (fy >= 0.0) ? (INT)(fy + 0.5) : (INT)(fy - 0.5);
								}
								Polygon(hDC, ptArrow, sizeof(ptArrow) / sizeof(POINT));
							}
						}
						SelectObject(hDC, hOldBrush);
					}
					SelectObject(hDC, hOldPen);
				}
				DeleteObject(hArrowBrush);
			}
			DeleteObject(hPen);
		}
	}
}

void CMimicsLineCtrl::DoPropExchange(CPropExchange *pPX)
{
	ExchangeVersion(pPX, MAKELONG(CMimicsApp::wAppVerMinor, CMimicsApp::wAppVerMajor));
	CMimicsCtrl::DoPropExchange(pPX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineCtrl message handlers
