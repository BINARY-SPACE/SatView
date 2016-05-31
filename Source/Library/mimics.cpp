// MIMICS.CPP : Mimics Objects Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics objects
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/07/07 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMimicsClientItem

IMPLEMENT_DYNCREATE(CMimicsClientItem, COleClientItem)

CMimicsClientItem::CMimicsClientItem(COleDocument *pContainerDoc) : COleClientItem(pContainerDoc)
{
	return;
}

VOID CMimicsClientItem::SetPosition(CONST RECT &rect)
{
	return;
}

CRect CMimicsClientItem::GetPosition() CONST
{
	return CRect(0, 0, 0, 0);
}

VOID CMimicsClientItem::FlipHorizontal()
{
	return;
}

VOID CMimicsClientItem::FlipVertical()
{
	return;
}

VOID CMimicsClientItem::Rotate(double fAngle)
{
	return;
}

LPOLEOBJECT CMimicsClientItem::GetOleObject() CONST
{
	return m_lpObject;
}

LPDISPATCH CMimicsClientItem::GetDispatch() CONST
{
	LPUNKNOWN  pIUnknown;
	LPDISPATCH  pIDispatch;

	return(((pIUnknown = GetOleObject()) && pIUnknown->QueryInterface(IID_IDispatch, (LPVOID *)&pIDispatch) == NOERROR) ? pIDispatch : (LPDISPATCH)NULL);
}

BEGIN_MESSAGE_MAP(CMimicsClientItem, COleClientItem)
	//{{AFX_MSG_MAP(CMimicsClientItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsClientItem commands


////////////////////////////////////////////////////////////////////////////
// CMimicsObjectDispatchDriver

CMimicsObjectDispatchDriver::CMimicsObjectDispatchDriver() : COleDispatchDriver()
{
	m_pItem = (CMimicsClientItem *)NULL;
	m_pCriticalSection = new CCriticalSection;
}

CMimicsObjectDispatchDriver::~CMimicsObjectDispatchDriver()
{
	delete m_pCriticalSection;
}

////////////////////////////////////////////////////////////////////////////
// CMimicsObjectDispatchDriver properties

/////////////////////////////////////////////////////////////////////////////
// CMimicsObjectDispatchDriver operations

VOID CMimicsObjectDispatchDriver::SetPosition(CONST RECT &rect)
{
	CMimicsClientItem  *pItem;

	if ((pItem = GetDispatchItem()))
	{
		pItem->SetPosition(rect);
		return;
	}
}

CRect CMimicsObjectDispatchDriver::GetPosition() CONST
{
	CMimicsClientItem  *pItem;

	return(((pItem = GetDispatchItem())) ? pItem->GetPosition() : CRect(0, 0, 0, 0));
}

VOID CMimicsObjectDispatchDriver::FlipHorizontal()
{
	CMimicsClientItem  *pItem;

	if ((pItem = GetDispatchItem()))
	{
		pItem->FlipHorizontal();
		return;
	}
}

VOID CMimicsObjectDispatchDriver::FlipVertical()
{
	CMimicsClientItem  *pItem;

	if ((pItem = GetDispatchItem()))
	{
		pItem->FlipVertical();
		return;
	}
}

VOID CMimicsObjectDispatchDriver::Rotate(double fAngle)
{
	CMimicsClientItem  *pItem;

	if ((pItem = GetDispatchItem()))
	{
		pItem->Rotate(fAngle);
		return;
	}
}

VOID CMimicsObjectDispatchDriver::Show()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SHOW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsObjectDispatchDriver::Hide()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_HIDE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsObjectDispatchDriver::IsVisible() CONST
{
	BOOL  bVisible;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISVISIBLE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bVisible, (const BYTE *)NULL);
	return bVisible;
}

BOOL CMimicsObjectDispatchDriver::Blink(INT nInterval)
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_BLINK));
	static BYTE  pParameters[] = VTS_I4;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, nInterval);
	return bResult;
}

BOOL CMimicsObjectDispatchDriver::Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData)
{
	return FALSE;
}

VOID CMimicsObjectDispatchDriver::AttachDispatch(CMimicsClientItem *pItem, BOOL bAutoRelease)
{
	m_pCriticalSection->Lock();
	COleDispatchDriver::AttachDispatch((m_pItem = pItem)->GetDispatch(), bAutoRelease);
}

VOID CMimicsObjectDispatchDriver::ReleaseDispatch()
{
	COleDispatchDriver::ReleaseDispatch();
	m_pItem = (CMimicsClientItem *)NULL;
	m_pCriticalSection->Unlock();
}

CMimicsClientItem *CMimicsObjectDispatchDriver::GetDispatchItem() CONST
{
	return((CMimicsClientItem *)m_pItem);
}

COleDispatchDriver *CMimicsObjectDispatchDriver::GetDispatchDriver() CONST
{
	return((COleDispatchDriver *) this);
}

DISPID CMimicsObjectDispatchDriver::GetDispatchID(OLECHAR FAR *pszMethod) CONST
{
	DISPID  nDispID;

	return((m_lpDispatch != (LPDISPATCH)NULL  &&  m_lpDispatch->GetIDsOfNames(IID_NULL, &pszMethod, 1, GetLanguageID(), &nDispID) == S_OK) ? nDispID : 0);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsLineDispatchDriver properties

VOID CMimicsLineDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsLineDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsLineDispatchDriver::SetThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsLineDispatchDriver::GetThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineDispatchDriver operations

VOID CMimicsLineDispatchDriver::Arrow(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ARROW));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

VOID CMimicsLineDispatchDriver::DoubleArrow(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DOUBLEARROW));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

VOID CMimicsLineDispatchDriver::Cross(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_CROSS));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsLineDispatchDriver::SetCrossPt(double fPt)
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETCROSSPT));
	static BYTE  pParameters[] = VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, fPt);
	return bResult;
}

BOOL CMimicsLineDispatchDriver::GetCrossPt(double *fPt) CONST
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETCROSSPT));
	static BYTE  pParameters[] = VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, fPt);
	return bResult;
}

BOOL CMimicsLineDispatchDriver::IsArrow() CONST
{
	BOOL  bArrow;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISARROW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bArrow, (const BYTE *)NULL);
	return bArrow;
}

BOOL CMimicsLineDispatchDriver::IsDoubleArrow() CONST
{
	BOOL  bDoubleArrow;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDOUBLEARROW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDoubleArrow, (const BYTE *)NULL);
	return bDoubleArrow;
}

BOOL CMimicsLineDispatchDriver::IsCross() CONST
{
	BOOL  bCross;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCROSS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bCross, (const BYTE *)NULL);
	return bCross;
}

VOID CMimicsLineDispatchDriver::Solid()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SOLID));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineDispatchDriver::Dash()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASH));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineDispatchDriver::Dot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineDispatchDriver::DashDot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASHDOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineDispatchDriver::DashDotDot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASHDOTDOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsLineDispatchDriver::IsSolid() CONST
{
	BOOL  bSolid;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISSOLID));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bSolid, (const BYTE *)NULL);
	return bSolid;
}

BOOL CMimicsLineDispatchDriver::IsDashed() CONST
{
	BOOL  bDashed;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashed, (const BYTE *)NULL);
	return bDashed;
}

BOOL CMimicsLineDispatchDriver::IsDotted() CONST
{
	BOOL  bDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDotted, (const BYTE *)NULL);
	return bDotted;
}

BOOL CMimicsLineDispatchDriver::IsDashDotted() CONST
{
	BOOL  bDashDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashDotted, (const BYTE *)NULL);
	return bDashDotted;
}

BOOL CMimicsLineDispatchDriver::IsDashDotDotted() CONST
{
	BOOL  bDashDotDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHDOTDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashDotDotted, (const BYTE *)NULL);
	return bDashDotDotted;
}

BOOL CMimicsLineDispatchDriver::Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData)
{
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleDispatchDriver properties

VOID CMimicsRectangleDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsRectangleDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsRectangleDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsRectangleDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsRectangleDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsRectangleDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsRectangleDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsRectangleDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleDispatchDriver operations

VOID CMimicsRectangleDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsRectangleDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}

BOOL CMimicsRectangleDispatchDriver::Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData)
{
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseDispatchDriver properties

VOID CMimicsEllipseDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsEllipseDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsEllipseDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsEllipseDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsEllipseDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsEllipseDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsEllipseDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsEllipseDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseDispatchDriver operations

VOID CMimicsEllipseDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsEllipseDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}

BOOL CMimicsEllipseDispatchDriver::Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData)
{
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsArcDispatchDriver properties

VOID CMimicsArcDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsArcDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsArcDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsArcDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsArcDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsArcDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsArcDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsArcDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcDispatchDriver operations

VOID CMimicsArcDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsArcDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}

VOID CMimicsArcDispatchDriver::SetRadials(double fRadial1, double fRadial2)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETRADIALS));
	static BYTE  pParameters[] = VTS_R8 VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, fRadial1, fRadial2);
}

VOID CMimicsArcDispatchDriver::GetRadials(double &fRadial1, double &fRadial2) CONST
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETRADIALS));
	static BYTE  pParameters[] = VTS_PR8 VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &fRadial1, &fRadial2);
}

BOOL CMimicsArcDispatchDriver::Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData)
{
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleDispatchDriver properties

VOID CMimicsTriangleDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsTriangleDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsTriangleDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsTriangleDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsTriangleDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTriangleDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsTriangleDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTriangleDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleDispatchDriver operations

VOID CMimicsTriangleDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsTriangleDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}

VOID CMimicsTriangleDispatchDriver::SetEdges(double x1, double y1, double x2, double y2, double x3, double y3)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETEDGES));
	static BYTE  pParameters[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, x1, y1, x2, y2, x3, y3);
}

VOID CMimicsTriangleDispatchDriver::GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETEDGES));
	static BYTE  pParameters[] = VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &x1, &y1, &x2, &y2, &x3, &y3);
}

BOOL CMimicsTriangleDispatchDriver::Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData)
{
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchDispatchDriver properties

VOID CMimicsSwitchDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchDispatchDriver::SetFrameColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMECOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchDispatchDriver::GetFrameColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMECOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchDispatchDriver::SetInteriorFrameColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORFRAMECOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchDispatchDriver::GetInteriorFrameColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORFRAMECOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchDispatchDriver::SetCenterColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchDispatchDriver::GetCenterColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchDispatchDriver::SetInteriorCenterColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCENTERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchDispatchDriver::GetInteriorCenterColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCENTERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchDispatchDriver::SetBarColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchDispatchDriver::GetBarColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchDispatchDriver::SetStubsColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchDispatchDriver::GetStubsColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchDispatchDriver::SetThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchDispatchDriver::GetThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchDispatchDriver::SetFrameThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMETHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchDispatchDriver::GetFrameThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMETHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchDispatchDriver::SetCenterThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchDispatchDriver::GetCenterThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchDispatchDriver::SetBarThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchDispatchDriver::GetBarThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchDispatchDriver::SetStubsThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchDispatchDriver::GetStubsThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchDispatchDriver operations

VOID CMimicsSwitchDispatchDriver::Open()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_OPEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchDispatchDriver::IsOpen() CONST
{
	BOOL  bOpen;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISOPEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bOpen, (const BYTE *)NULL);
	return bOpen;
}

BOOL CMimicsSwitchDispatchDriver::IsClosed() CONST
{
	BOOL  bClosed;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCLOSED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bClosed, (const BYTE *)NULL);
	return bClosed;
}

VOID CMimicsSwitchDispatchDriver::Close()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_CLOSE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsSwitchDispatchDriver::Pos1()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS1));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchDispatchDriver::IsPos1() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS1));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 0) ? TRUE : FALSE);
}

VOID CMimicsSwitchDispatchDriver::Pos2()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS2));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchDispatchDriver::IsPos2() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS2));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 1) ? TRUE : FALSE);
}

VOID CMimicsSwitchDispatchDriver::Pos3()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS3));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchDispatchDriver::IsPos3() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS3));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 2) ? TRUE : FALSE);
}

VOID CMimicsSwitchDispatchDriver::Broken()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_BROKEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchDispatchDriver::IsBroken() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISBROKEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == -1) ? TRUE : FALSE);
}

BOOL CMimicsSwitchDispatchDriver::Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData)
{
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsTextDispatchDriver properties

VOID CMimicsTextDispatchDriver::SetText(LPCTSTR pszText)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TEXT));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszText);
}

CString CMimicsTextDispatchDriver::GetText() CONST
{
	CString  szText;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TEXT));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szText);
	return szText;
}

VOID CMimicsTextDispatchDriver::SetMode(INT nMode)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_MODE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nMode);
}

INT CMimicsTextDispatchDriver::GetMode() CONST
{
	INT  nMode;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_MODE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nMode);
	return nMode;
}

VOID CMimicsTextDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTextDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsTextDispatchDriver::SetBackgroundColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BACKGROUNDCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTextDispatchDriver::GetBackgroundColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BACKGROUNDCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextDispatchDriver operations

BOOL CMimicsTextDispatchDriver::SetFont(CONST LOGFONT *pFont)
{
	BOOL  bFont;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETFONT));
	static BYTE  pParameters[] = VTS_PVARIANT;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bFont, pParameters, pFont);
	return bFont;
}

BOOL CMimicsTextDispatchDriver::GetFont(LOGFONT *pFont) CONST
{
	BOOL  bFont;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETFONT));
	static BYTE  pParameters[] = VTS_PVARIANT;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bFont, pParameters, pFont);
	return bFont;
}

VOID CMimicsTextDispatchDriver::AlignLeft()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNLEFT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextDispatchDriver::AlignCenter()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNCENTER));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextDispatchDriver::AlignRight()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNRIGHT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextDispatchDriver::AlignVertical(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNVERTICAL));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextDispatchDriver::IsLeftAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISLEFTALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextDispatchDriver::IsCenterAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCENTERALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextDispatchDriver::IsRightAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISRIGHTALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextDispatchDriver::IsVerticalAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISVERTICALALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

VOID CMimicsTextDispatchDriver::LeftToRightReading()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_LEFTTORIGHTREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextDispatchDriver::TopToBottomReading()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_TOPTOBOTTOMREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsTextDispatchDriver::IsLeftToRightReading() CONST
{
	BOOL  bReading;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISLEFTTORIGHTREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bReading, (const BYTE *)NULL);
	return bReading;
}

BOOL CMimicsTextDispatchDriver::IsTopToBottomReading() CONST
{
	BOOL  bReading;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISTOPTOBOTTOMREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bReading, (const BYTE *)NULL);
	return bReading;
}

VOID CMimicsTextDispatchDriver::SetTabChars(INT nChars)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETTABCHARS));
	static BYTE  pParameters[] = VTS_I4;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nChars);
}

INT CMimicsTextDispatchDriver::GetTabChars() CONST
{
	INT  nChars;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETTABCHARS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nChars, (const BYTE *)NULL);
	return nChars;
}

VOID CMimicsTextDispatchDriver::WrapWords(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_WRAPWORDS));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextDispatchDriver::IsWrappingWords() CONST
{
	BOOL  bEnable;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISWRAPPINGWORDS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bEnable, (const BYTE *)NULL);
	return bEnable;
}

VOID CMimicsTextDispatchDriver::SingleLine(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SINGLELINE));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextDispatchDriver::IsSingleLine() CONST
{
	BOOL  bEnable;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISSINGLELINE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bEnable, (const BYTE *)NULL);
	return bEnable;
}

BOOL CMimicsTextDispatchDriver::Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData)
{
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsImageDispatchDriver properties

VOID CMimicsImageDispatchDriver::SetFileName(LPCTSTR pszFileName)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FILENAME));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszFileName);
}

CString CMimicsImageDispatchDriver::GetFileName() CONST
{
	CString  szFileName;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FILENAME));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szFileName);
	return szFileName;
}

VOID CMimicsImageDispatchDriver::SetImageTransparency(BYTE nFactor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_IMAGETRANSPARENCY));

	SetProperty(GetDispatchID(szDispatch), VT_UI1, nFactor);
}

BYTE CMimicsImageDispatchDriver::GetImageTransparency() CONST
{
	BYTE  nFactor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_IMAGETRANSPARENCY));

	GetProperty(GetDispatchID(szDispatch), VT_UI1, &nFactor);
	return nFactor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageDispatchDriver operations

VOID CMimicsImageDispatchDriver::SetImageOrigin(CONST POINT &pt)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETIMAGEORIGIN));
	static BYTE  pParameters[] = VTS_XPOS_PIXELS VTS_YPOS_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, pt.x, pt.y);
}

CPoint CMimicsImageDispatchDriver::GetImageOrigin() CONST
{
	OLE_XPOS_PIXELS  nXPos;
	OLE_YPOS_PIXELS  nYPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETIMAGEORIGIN));
	static BYTE  pParameters[] = VTS_PXPOS_PIXELS VTS_PYPOS_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &nXPos, &nYPos);
	return CPoint(nXPos, nYPos);
}

VOID CMimicsImageDispatchDriver::SetImageSize(CONST SIZE &size)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETIMAGESIZE));
	static BYTE  pParameters[] = VTS_XSIZE_PIXELS VTS_YSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, size.cx, size.cy);
}

CSize CMimicsImageDispatchDriver::GetImageSize() CONST
{
	OLE_XSIZE_PIXELS  cx;
	OLE_YSIZE_PIXELS  cy;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETIMAGESIZE));
	static BYTE  pParameters[] = VTS_PXSIZE_PIXELS VTS_PYSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &cx, &cy);
	return CSize(cx, cy);
}

BOOL CMimicsImageDispatchDriver::Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData)
{
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsGroupDispatchDriver properties

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupDispatchDriver operations

BOOL CMimicsGroupDispatchDriver::Update(CONST CDatabaseEngine *pDatabase, CONST CTMEnvironment *pTMEnvironment, BOOL bInvalidData)
{
	return FALSE;
}
