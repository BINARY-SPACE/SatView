// MMD.CPP : Mimics Display Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics display
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/01 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#include "MimicsIIDs.h"
#include "MimicsCtlEnum.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nStatusBarIndicators[] =
{
	ID_MMD_STATUSBAR_OBJECTPANE,
	ID_MMD_STATUSBAR_POSITIONPANE,
	ID_MMD_STATUSBAR_SIZEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CMMDDocument

IMPLEMENT_DYNCREATE(CMMDDocument, COleDocument)

CMMDDocument::CMMDDocument() : COleDocument()
{
	m_bAutoDelete = FALSE;
}

CMMDDocument::~CMMDDocument()
{
	DeleteContents();
}

INT CMMDDocument::EnumItems(CPtrArray &pItems) CONST
{
	pItems.RemoveAll();
	return((EnumItemsInList(this, pItems)) ? (INT)pItems.GetSize() : -1);
}

POSITION CMMDDocument::FindItem(CMimicsClientItem *pItem) CONST
{
	return FindItemInList(this, pItem);
}

CDocItem *CMMDDocument::GetNextItem(POSITION &lPosition) CONST
{
	CDocItem  *pItem;
	CONST CMMDDocument  *pDocument;

	return((!(pItem = (CDocItem *)m_docItemList.GetNext(lPosition))) ? (((pDocument = FindPositionInList(this, lPosition))) ? (CDocItem *)pDocument->m_docItemList.GetNext(lPosition) : (CDocItem *)NULL) : pItem);
}

CDocItem *CMMDDocument::GetPreviousItem(POSITION &lPosition) CONST
{
	CDocItem  *pItem;
	CONST CMMDDocument  *pDocument;

	return((!(pItem = (CDocItem *)m_docItemList.GetPrev(lPosition))) ? (((pDocument = FindPositionInList(this, lPosition))) ? (CDocItem *)pDocument->m_docItemList.GetPrev(lPosition) : (CDocItem *)NULL) : pItem);
}

UINT CMMDDocument::GetItemCount() CONST
{
	return((UINT)m_docItemList.GetCount());
}

POSITION CMMDDocument::GetStartPosition() CONST
{
	return m_docItemList.GetHeadPosition();
}

POSITION CMMDDocument::GetStopPosition() CONST
{
	return m_docItemList.GetTailPosition();
}

BOOL CMMDDocument::SaveModified()
{
	return TRUE;
}

BOOL CMMDDocument::OnNewDocument()
{
	return COleDocument::OnNewDocument();
}

void CMMDDocument::OnCloseDocument()
{
	DeleteContents();
}

BOOL CMMDDocument::CanCloseFrame(CFrameWnd *pFrame)
{
	return TRUE;
}

VOID CMMDDocument::DeleteContents()
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_docItemList.GetHeadPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_docItemList.GetNext(lPosition)))
		{
			pItem->Release();
			pItem->Delete();
		}
	}
	SetModifiedFlag(FALSE);
	COleDocument::DeleteContents();
}

BOOL CMMDDocument::Copy(CONST CMMDDocument *pDocument, BOOL bAll)
{
	POSITION  lPosition;
	CMimicsItem  *pItem[2];

	for (lPosition = pDocument->m_docItemList.GetHeadPosition(), DeleteContents(); lPosition; )
	{
		if ((pItem[0] = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition)))
		{
			if ((pItem[1] = CMimicsItem::AllocateFromItem(pItem[0])))
			{
				if (pItem[1]->Copy(pItem[0], bAll))
				{
					AddItem(pItem[1]);
					continue;
				}
				delete pItem[1];
			}
		}
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}

BOOL CMMDDocument::Compare(CONST CMMDDocument *pDocument, BOOL bAll) CONST
{
	POSITION  lPosition[2];
	CMimicsItem  *pItem;

	for (lPosition[0] = pDocument->m_docItemList.GetHeadPosition(), lPosition[1] = m_docItemList.GetHeadPosition(); pDocument->m_docItemList.GetCount() == m_docItemList.GetCount() && lPosition[0] && lPosition[1]; )
	{
		if ((pItem = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition[0])) && pItem->Compare((CMimicsItem *)m_docItemList.GetNext(lPosition[1]), bAll)) continue;
		lPosition[0] = pDocument->m_docItemList.GetHeadPosition();
		lPosition[1] = m_docItemList.GetHeadPosition();
		break;
	}
	return((pDocument->m_docItemList.GetCount() == m_docItemList.GetCount()) ? ((!lPosition[0] && !lPosition[1]) ? TRUE : FALSE) : FALSE);
}

BOOL CMMDDocument::Map(CMMDLayout &cLayout, CONST POINT &ptOrigin) CONST
{
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDLayoutItem  *pLayoutItem;

	for (lPosition = m_docItemList.GetHeadPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_docItemList.GetNext(lPosition)))
		{
			if ((pLayoutItem = new CMMDLayoutItem) && pItem->Map(pLayoutItem, ptOrigin) && cLayout.Add(pLayoutItem) >= 0) continue;
			delete pLayoutItem;
		}
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}

BOOL CMMDDocument::Unmap(CONST CMMDLayout &cLayout, CONST POINT &ptOrigin)
{
	INT  nItem;
	INT  nItems;
	CMimicsItem  *pItem;
	CMMDLayoutItem  *pLayoutItem;

	for (nItem = 0, nItems = (INT)cLayout.GetSize(), DeleteContents(); nItem < nItems; nItem++)
	{
		if ((pLayoutItem = cLayout.GetAt(nItem)) != (CMMDLayoutItem *)NULL)
		{
			if ((pItem = CMimicsItem::AllocateFromItem(pLayoutItem)))
			{
				if (pItem->Unmap(pLayoutItem, ptOrigin))
				{
					AddItem(pItem);
					continue;
				}
				delete pItem;
			}
		}
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CMMDDocument::EnumItemsInList(CONST CMMDDocument *pDocument, CPtrArray &pItems) CONST
{
	POSITION  lPosition;
	CMimicsItem  *pMimicsItem;
	CMimicsGroup  *pMimicsGroup;

	for (lPosition = pDocument->m_docItemList.GetHeadPosition(); lPosition; )
	{
		if ((pMimicsItem = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition)))
		{
			if (pMimicsItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup))) EnumItemsInList((pMimicsGroup = (CMimicsGroup *)pMimicsItem)->GetItemList(), pItems);
			pItems.Add(pMimicsItem);
			continue;
		}
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}

POSITION CMMDDocument::FindItemInList(CONST CMMDDocument *pDocument, CMimicsClientItem *pItem) CONST
{
	POSITION  lPosition[2];
	CMimicsItem  *pMimicsItem;
	CMimicsGroup  *pMimicsGroup;

	for (lPosition[0] = pDocument->m_docItemList.GetHeadPosition(), lPosition[1] = (POSITION)NULL; lPosition[0]; )
	{
		if ((pMimicsItem = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition[0])))
		{
			if (pMimicsItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)) && pMimicsItem != pItem)
			{
				if ((pMimicsGroup = (CMimicsGroup *)pMimicsItem) != (CMimicsGroup *)NULL)
				{
					if ((lPosition[1] = FindItemInList(pMimicsGroup->GetItemList(), pItem))) break;
					continue;
				}
			}
			if (pMimicsItem == pItem)
			{
				lPosition[1] = pDocument->m_docItemList.Find(pItem);
				break;
			}
			continue;
		}
		break;
	}
	return lPosition[1];
}

CONST CMMDDocument *CMMDDocument::FindPositionInList(CONST CMMDDocument *pDocument, POSITION lPosition) CONST
{
	POSITION  lItemPos;
	CMimicsItem  *pMimicsItem;
	CMimicsGroup  *pMimicsGroup;
	CONST CMMDDocument  *pItemList;

	for (lItemPos = pDocument->m_docItemList.GetHeadPosition(), pItemList = pDocument; lItemPos && lPosition && lItemPos != lPosition; )
	{
		if ((pMimicsItem = (CMimicsItem *)pDocument->m_docItemList.GetNext(lItemPos)))
		{
			if (pMimicsItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)) && lItemPos != lPosition)
			{
				if ((pMimicsGroup = (CMimicsGroup *)pMimicsItem) != (CMimicsGroup *)NULL)
				{
					if ((pItemList = FindPositionInList(pMimicsGroup->GetItemList(), lPosition)))
					{
						lItemPos = lPosition;
						break;
					}
					continue;
				}
			}
			if (lItemPos == lPosition)
			{
				pItemList = pDocument;
				break;
			}
			continue;
		}
		break;
	}
	return((lItemPos  &&  lItemPos == lPosition) ? pItemList : (CONST CMMDDocument *) NULL);
}

BEGIN_MESSAGE_MAP(CMMDDocument, COleDocument)
	//{{AFX_MSG_MAP(CMMDDocument)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDDocument serialization

void CMMDDocument::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMMDDocument commands


////////////////////////////////////////////////////////////////////////////
// CMimicsItemDispatchDriver properties

VOID CMimicsItemDispatchDriver::SetName(LPCTSTR pszName)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_NAME));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszName);
}

CString CMimicsItemDispatchDriver::GetName() CONST
{
	CString  szName;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_NAME));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szName);
	return szName;
}

VOID CMimicsItemDispatchDriver::SetType(LPCTSTR pszType)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TYPE));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszType);
}

CString CMimicsItemDispatchDriver::GetType() CONST
{
	CString  szType;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TYPE));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szType);
	return szType;
}

VOID CMimicsItemDispatchDriver::SetToolTipText(LPCTSTR pszText)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TOOLTIPTEXT));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszText);
}

CString CMimicsItemDispatchDriver::GetToolTipText() CONST
{
	CString  szText;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TOOLTIPTEXT));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szText);
	return szText;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsItemDispatchDriver operations

VOID CMimicsItemDispatchDriver::SetInitialSize(CONST SIZE &size)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINITIALSIZE));
	static BYTE  pParameters[] = VTS_XSIZE_PIXELS VTS_YSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, size.cx, size.cy);
}

CSize CMimicsItemDispatchDriver::GetInitialSize() CONST
{
	OLE_XSIZE_PIXELS  cx;
	OLE_YSIZE_PIXELS  cy;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINITIALSIZE));
	static BYTE  pParameters[] = VTS_PXSIZE_PIXELS VTS_PYSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &cx, &cy);
	return CSize(cx, cy);
}

VOID CMimicsItemDispatchDriver::Show()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SHOW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsItemDispatchDriver::Hide()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_HIDE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsItemDispatchDriver::IsVisible() CONST
{
	BOOL  bVisible;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISVISIBLE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bVisible, (const BYTE *)NULL);
	return bVisible;
}

BOOL CMimicsItemDispatchDriver::Blink(INT nInterval)
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_BLINK));
	static BYTE  pParameters[] = VTS_I4;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, nInterval);
	return bResult;
}

VOID CMimicsItemDispatchDriver::Draw(HDC hDC, CONST RECT *pRect, CONST XFORM *pxForm, BOOL bShape)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DRAW));
	static BYTE  pParameters[] = VTS_HANDLE VTS_PVARIANT VTS_PVARIANT VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, hDC, pRect, pxForm, bShape);
}

COleDispatchDriver *CMimicsItemDispatchDriver::GetDispatchDriver() CONST
{
	return((COleDispatchDriver *) this);
}

DISPID CMimicsItemDispatchDriver::GetDispatchID(OLECHAR FAR *pszMethod) CONST
{
	DISPID  nDispID;

	return((m_lpDispatch != (LPDISPATCH)NULL  &&  m_lpDispatch->GetIDsOfNames(IID_NULL, &pszMethod, 1, GetLanguageID(), &nDispID) == S_OK) ? nDispID : 0);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsLineItemDispatchDriver properties

VOID CMimicsLineItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsLineItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsLineItemDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsLineItemDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsLineItemDispatchDriver::SetThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsLineItemDispatchDriver::GetThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineItemDispatchDriver operations

VOID CMimicsLineItemDispatchDriver::Arrow(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ARROW));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

VOID CMimicsLineItemDispatchDriver::DoubleArrow(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DOUBLEARROW));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

VOID CMimicsLineItemDispatchDriver::Cross(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_CROSS));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsLineItemDispatchDriver::SetCrossPt(double fPt)
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETCROSSPT));
	static BYTE  pParameters[] = VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, fPt);
	return bResult;
}

BOOL CMimicsLineItemDispatchDriver::GetCrossPt(double *fPt) CONST
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETCROSSPT));
	static BYTE  pParameters[] = VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, fPt);
	return bResult;
}

BOOL CMimicsLineItemDispatchDriver::IsArrow() CONST
{
	BOOL  bArrow;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISARROW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bArrow, (const BYTE *)NULL);
	return bArrow;
}

BOOL CMimicsLineItemDispatchDriver::IsDoubleArrow() CONST
{
	BOOL  bDoubleArrow;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDOUBLEARROW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDoubleArrow, (const BYTE *)NULL);
	return bDoubleArrow;
}

BOOL CMimicsLineItemDispatchDriver::IsCross() CONST
{
	BOOL  bCross;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCROSS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bCross, (const BYTE *)NULL);
	return bCross;
}

VOID CMimicsLineItemDispatchDriver::Solid()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SOLID));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineItemDispatchDriver::Dash()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASH));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineItemDispatchDriver::Dot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineItemDispatchDriver::DashDot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASHDOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineItemDispatchDriver::DashDotDot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASHDOTDOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsLineItemDispatchDriver::IsSolid() CONST
{
	BOOL  bSolid;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISSOLID));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bSolid, (const BYTE *)NULL);
	return bSolid;
}

BOOL CMimicsLineItemDispatchDriver::IsDashed() CONST
{
	BOOL  bDashed;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashed, (const BYTE *)NULL);
	return bDashed;
}

BOOL CMimicsLineItemDispatchDriver::IsDotted() CONST
{
	BOOL  bDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDotted, (const BYTE *)NULL);
	return bDotted;
}

BOOL CMimicsLineItemDispatchDriver::IsDashDotted() CONST
{
	BOOL  bDashDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashDotted, (const BYTE *)NULL);
	return bDashDotted;
}

BOOL CMimicsLineItemDispatchDriver::IsDashDotDotted() CONST
{
	BOOL  bDashDotDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHDOTDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashDotDotted, (const BYTE *)NULL);
	return bDashDotDotted;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItemDispatchDriver properties

VOID CMimicsRectangleItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsRectangleItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsRectangleItemDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsRectangleItemDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsRectangleItemDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsRectangleItemDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsRectangleItemDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsRectangleItemDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsRectangleItemDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsRectangleItemDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItemDispatchDriver operations

VOID CMimicsRectangleItemDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsRectangleItemDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItemDispatchDriver properties

VOID CMimicsEllipseItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsEllipseItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsEllipseItemDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsEllipseItemDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsEllipseItemDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsEllipseItemDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsEllipseItemDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsEllipseItemDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsEllipseItemDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsEllipseItemDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItemDispatchDriver operations

VOID CMimicsEllipseItemDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsEllipseItemDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsArcItemDispatchDriver properties

VOID CMimicsArcItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsArcItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsArcItemDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsArcItemDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsArcItemDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsArcItemDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsArcItemDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsArcItemDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsArcItemDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsArcItemDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcItemDispatchDriver operations

VOID CMimicsArcItemDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsArcItemDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}

VOID CMimicsArcItemDispatchDriver::SetRadials(double fRadial1, double fRadial2)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETRADIALS));
	static BYTE  pParameters[] = VTS_R8 VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, fRadial1, fRadial2);
}

VOID CMimicsArcItemDispatchDriver::GetRadials(double &fRadial1, double &fRadial2) CONST
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETRADIALS));
	static BYTE  pParameters[] = VTS_PR8 VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &fRadial1, &fRadial2);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItemDispatchDriver properties

VOID CMimicsTriangleItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsTriangleItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsTriangleItemDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsTriangleItemDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsTriangleItemDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsTriangleItemDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsTriangleItemDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTriangleItemDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsTriangleItemDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTriangleItemDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItemDispatchDriver operations

VOID CMimicsTriangleItemDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsTriangleItemDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}

VOID CMimicsTriangleItemDispatchDriver::SetEdges(double x1, double y1, double x2, double y2, double x3, double y3)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETEDGES));
	static BYTE  pParameters[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, x1, y1, x2, y2, x3, y3);
}

VOID CMimicsTriangleItemDispatchDriver::GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETEDGES));
	static BYTE  pParameters[] = VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &x1, &y1, &x2, &y2, &x3, &y3);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItemDispatchDriver properties

VOID CMimicsSwitchItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsSwitchItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsSwitchItemDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetFrameColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMECOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetFrameColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMECOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetInteriorFrameColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORFRAMECOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetInteriorFrameColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORFRAMECOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetCenterColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetCenterColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetInteriorCenterColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCENTERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetInteriorCenterColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCENTERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetBarColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetBarColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetStubsColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetStubsColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchItemDispatchDriver::GetThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchItemDispatchDriver::SetFrameThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMETHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchItemDispatchDriver::GetFrameThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMETHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchItemDispatchDriver::SetCenterThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchItemDispatchDriver::GetCenterThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchItemDispatchDriver::SetBarThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchItemDispatchDriver::GetBarThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchItemDispatchDriver::SetStubsThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchItemDispatchDriver::GetStubsThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItemDispatchDriver operations

VOID CMimicsSwitchItemDispatchDriver::Open()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_OPEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchItemDispatchDriver::IsOpen() CONST
{
	BOOL  bOpen;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISOPEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bOpen, (const BYTE *)NULL);
	return bOpen;
}

BOOL CMimicsSwitchItemDispatchDriver::IsClosed() CONST
{
	BOOL  bClosed;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCLOSED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bClosed, (const BYTE *)NULL);
	return bClosed;
}

VOID CMimicsSwitchItemDispatchDriver::Close()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_CLOSE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsSwitchItemDispatchDriver::Pos1()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS1));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchItemDispatchDriver::IsPos1() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS1));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 0) ? TRUE : FALSE);
}

VOID CMimicsSwitchItemDispatchDriver::Pos2()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS2));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchItemDispatchDriver::IsPos2() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS2));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 1) ? TRUE : FALSE);
}

VOID CMimicsSwitchItemDispatchDriver::Pos3()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS3));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchItemDispatchDriver::IsPos3() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS3));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 2) ? TRUE : FALSE);
}

VOID CMimicsSwitchItemDispatchDriver::Broken()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_BROKEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchItemDispatchDriver::IsBroken() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISBROKEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == -1) ? TRUE : FALSE);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsTextItemDispatchDriver properties

VOID CMimicsTextItemDispatchDriver::SetText(LPCTSTR pszText)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TEXT));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszText);
}

CString CMimicsTextItemDispatchDriver::GetText() CONST
{
	CString  szText;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TEXT));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szText);
	return szText;
}

VOID CMimicsTextItemDispatchDriver::SetMode(INT nMode)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_MODE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nMode);
}

INT CMimicsTextItemDispatchDriver::GetMode() CONST
{
	INT  nMode;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_MODE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nMode);
	return nMode;
}

VOID CMimicsTextItemDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTextItemDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsTextItemDispatchDriver::SetBackgroundColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BACKGROUNDCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTextItemDispatchDriver::GetBackgroundColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BACKGROUNDCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextItemDispatchDriver operations

BOOL CMimicsTextItemDispatchDriver::SetFont(CONST LOGFONT *pFont)
{
	BOOL  bFont;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETFONT));
	static BYTE  pParameters[] = VTS_PVARIANT;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bFont, pParameters, pFont);
	return bFont;
}

BOOL CMimicsTextItemDispatchDriver::GetFont(LOGFONT *pFont) CONST
{
	BOOL  bFont;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETFONT));
	static BYTE  pParameters[] = VTS_PVARIANT;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bFont, pParameters, pFont);
	return bFont;
}

VOID CMimicsTextItemDispatchDriver::AlignLeft()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNLEFT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextItemDispatchDriver::AlignCenter()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNCENTER));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextItemDispatchDriver::AlignRight()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNRIGHT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextItemDispatchDriver::AlignVertical(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNVERTICAL));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextItemDispatchDriver::IsLeftAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISLEFTALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextItemDispatchDriver::IsCenterAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCENTERALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextItemDispatchDriver::IsRightAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISRIGHTALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextItemDispatchDriver::IsVerticalAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISVERTICALALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

VOID CMimicsTextItemDispatchDriver::LeftToRightReading()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_LEFTTORIGHTREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextItemDispatchDriver::TopToBottomReading()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_TOPTOBOTTOMREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsTextItemDispatchDriver::IsLeftToRightReading() CONST
{
	BOOL  bReading;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISLEFTTORIGHTREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bReading, (const BYTE *)NULL);
	return bReading;
}

BOOL CMimicsTextItemDispatchDriver::IsTopToBottomReading() CONST
{
	BOOL  bReading;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISTOPTOBOTTOMREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bReading, (const BYTE *)NULL);
	return bReading;
}

VOID CMimicsTextItemDispatchDriver::SetTabChars(INT nChars)
{
	static BYTE  pParameters[] = VTS_I4;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETTABCHARS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nChars);
}

INT CMimicsTextItemDispatchDriver::GetTabChars() CONST
{
	INT  nChars;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETTABCHARS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nChars, (const BYTE *)NULL);
	return nChars;
}

VOID CMimicsTextItemDispatchDriver::WrapWords(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_WRAPWORDS));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextItemDispatchDriver::IsWrappingWords() CONST
{
	BOOL  bEnable;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISWRAPPINGWORDS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bEnable, (const BYTE *)NULL);
	return bEnable;
}

VOID CMimicsTextItemDispatchDriver::SingleLine(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SINGLELINE));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextItemDispatchDriver::IsSingleLine() CONST
{
	BOOL  bEnable;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISSINGLELINE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bEnable, (const BYTE *)NULL);
	return bEnable;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsImageItemDispatchDriver properties

VOID CMimicsImageItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsImageItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsImageItemDispatchDriver::SetFileName(LPCTSTR pszFileName)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FILENAME));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszFileName);
}

CString CMimicsImageItemDispatchDriver::GetFileName() CONST
{
	CString  szFileName;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FILENAME));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szFileName);
	return szFileName;
}

VOID CMimicsImageItemDispatchDriver::SetImageTransparency(BYTE nFactor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_IMAGETRANSPARENCY));

	SetProperty(GetDispatchID(szDispatch), VT_UI1, nFactor);
}

BYTE CMimicsImageItemDispatchDriver::GetImageTransparency() CONST
{
	BYTE  nFactor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_IMAGETRANSPARENCY));

	GetProperty(GetDispatchID(szDispatch), VT_UI1, &nFactor);
	return nFactor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageItemDispatchDriver operations

VOID CMimicsImageItemDispatchDriver::SetImageOrigin(CONST POINT &pt)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETIMAGEORIGIN));
	static BYTE  pParameters[] = VTS_XPOS_PIXELS VTS_YPOS_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, pt.x, pt.y);
}

CPoint CMimicsImageItemDispatchDriver::GetImageOrigin() CONST
{
	OLE_XPOS_PIXELS  nXPos;
	OLE_YPOS_PIXELS  nYPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETIMAGEORIGIN));
	static BYTE  pParameters[] = VTS_PXPOS_PIXELS VTS_PYPOS_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &nXPos, &nYPos);
	return CPoint(nXPos, nYPos);
}

VOID CMimicsImageItemDispatchDriver::SetImageSize(CONST SIZE &size)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETIMAGESIZE));
	static BYTE  pParameters[] = VTS_XSIZE_PIXELS VTS_YSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, size.cx, size.cy);
}

CSize CMimicsImageItemDispatchDriver::GetImageSize() CONST
{
	OLE_XSIZE_PIXELS  cx;
	OLE_YSIZE_PIXELS  cy;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETIMAGESIZE));
	static BYTE  pParameters[] = VTS_PXSIZE_PIXELS VTS_PYSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &cx, &cy);
	return CSize(cx, cy);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsGroupItemDispatchDriver properties

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupItemDispatchDriver operations


/////////////////////////////////////////////////////////////////////////////
// CMimicsItem

IMPLEMENT_DYNCREATE(CMimicsItem, CMimicsClientItem)

CMimicsItem::CMimicsItem(CMMDDocument *pContainerDoc) : CMimicsClientItem(pContainerDoc)
{
	m_szName = STRING(IDS_MMD_STATUSBAR_OBJECTDEFAULTNAME);
	m_rPosition[0].SetRectEmpty();
	m_rPosition[1].SetRectEmpty();
	m_ptCenter.x = 0;
	m_ptCenter.y = 0;
	m_xForm.eM11 = 1.0;
	m_xForm.eM12 = 0.0;
	m_xForm.eM21 = 0.0;
	m_xForm.eM22 = 1.0;
	m_xForm.eDx = 0.0;
	m_xForm.eDy = 0.0;
	m_bOriginal = FALSE;
	m_pContainerItem = (CMimicsItem *)NULL;
	m_pOleInPlaceObjectWindowless = (LPOLEINPLACEOBJECTWINDOWLESS)NULL;
	m_pImageView = (CView *)NULL;
	m_pDC = (CDC *)NULL;
	m_bProperties = FALSE;
	m_bRotateFlag = FALSE;
	m_bActivated = FALSE;
	m_bSelected = FALSE;
	m_bVisible = TRUE;
	m_bLocked = FALSE;
}

CMimicsItem::~CMimicsItem()
{
	Release();
}

CMimicsItem *CMimicsItem::Create(CLSID &clsid, CView *pView, CMMDDocument *pDocument, CPoint point)
{
	CMimicsItem  *pMimicsItem;

	if (clsid == CLSID_CMimicsLineCtrl)
	{
		if ((pMimicsItem = new CMimicsLineItem(pDocument)))
		{
			if (pMimicsItem->CreateNewItem(clsid, pView))
			{
				pMimicsItem->SetItemPosition(CRect(point.x - pMimicsItem->GetItemSize().cx / 2, point.y - pMimicsItem->GetItemSize().cy / 2, point.x - pMimicsItem->GetItemSize().cx / 2 + pMimicsItem->GetItemSize().cx, point.y - pMimicsItem->GetItemSize().cy / 2 + pMimicsItem->GetItemSize().cy));
				pMimicsItem->SetItemCenterPoint();
				pMimicsItem->InitializeProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (clsid == CLSID_CMimicsRectangleCtrl)
	{
		if ((pMimicsItem = new CMimicsRectangleItem(pDocument)))
		{
			if (pMimicsItem->CreateNewItem(clsid, pView))
			{
				pMimicsItem->SetItemPosition(CRect(point.x - pMimicsItem->GetItemSize().cx / 2, point.y - pMimicsItem->GetItemSize().cy / 2, point.x - pMimicsItem->GetItemSize().cx / 2 + pMimicsItem->GetItemSize().cx, point.y - pMimicsItem->GetItemSize().cy / 2 + pMimicsItem->GetItemSize().cy));
				pMimicsItem->SetItemCenterPoint();
				pMimicsItem->InitializeProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (clsid == CLSID_CMimicsEllipseCtrl)
	{
		if ((pMimicsItem = new CMimicsEllipseItem(pDocument)))
		{
			if (pMimicsItem->CreateNewItem(clsid, pView))
			{
				pMimicsItem->SetItemPosition(CRect(point.x - pMimicsItem->GetItemSize().cx / 2, point.y - pMimicsItem->GetItemSize().cy / 2, point.x - pMimicsItem->GetItemSize().cx / 2 + pMimicsItem->GetItemSize().cx, point.y - pMimicsItem->GetItemSize().cy / 2 + pMimicsItem->GetItemSize().cy));
				pMimicsItem->SetItemCenterPoint();
				pMimicsItem->InitializeProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (clsid == CLSID_CMimicsArcCtrl)
	{
		if ((pMimicsItem = new CMimicsArcItem(pDocument)))
		{
			if (pMimicsItem->CreateNewItem(clsid, pView))
			{
				pMimicsItem->SetItemPosition(CRect(point.x - pMimicsItem->GetItemSize().cx / 2, point.y - pMimicsItem->GetItemSize().cy / 2, point.x - pMimicsItem->GetItemSize().cx / 2 + pMimicsItem->GetItemSize().cx, point.y - pMimicsItem->GetItemSize().cy / 2 + pMimicsItem->GetItemSize().cy));
				pMimicsItem->SetItemCenterPoint();
				pMimicsItem->InitializeProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (clsid == CLSID_CMimicsTriangleCtrl)
	{
		if ((pMimicsItem = new CMimicsTriangleItem(pDocument)))
		{
			if (pMimicsItem->CreateNewItem(clsid, pView))
			{
				pMimicsItem->SetItemPosition(CRect(point.x - pMimicsItem->GetItemSize().cx / 2, point.y - pMimicsItem->GetItemSize().cy / 2, point.x - pMimicsItem->GetItemSize().cx / 2 + pMimicsItem->GetItemSize().cx, point.y - pMimicsItem->GetItemSize().cy / 2 + pMimicsItem->GetItemSize().cy));
				pMimicsItem->SetItemCenterPoint();
				pMimicsItem->InitializeProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (clsid == CLSID_CMimicsSwitchCtrl)
	{
		if ((pMimicsItem = new CMimicsSwitchItem(pDocument)))
		{
			if (pMimicsItem->CreateNewItem(clsid, pView))
			{
				pMimicsItem->SetItemPosition(CRect(point.x - pMimicsItem->GetItemSize().cx / 2, point.y - pMimicsItem->GetItemSize().cy / 2, point.x - pMimicsItem->GetItemSize().cx / 2 + pMimicsItem->GetItemSize().cx, point.y - pMimicsItem->GetItemSize().cy / 2 + pMimicsItem->GetItemSize().cy));
				pMimicsItem->SetItemCenterPoint();
				pMimicsItem->InitializeProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (clsid == CLSID_CMimicsTextCtrl)
	{
		if ((pMimicsItem = new CMimicsTextItem(pDocument)))
		{
			if (pMimicsItem->CreateNewItem(clsid, pView))
			{
				pMimicsItem->SetItemPosition(CRect(point.x - pMimicsItem->GetItemSize().cx / 2, point.y - pMimicsItem->GetItemSize().cy / 2, point.x - pMimicsItem->GetItemSize().cx / 2 + pMimicsItem->GetItemSize().cx, point.y - pMimicsItem->GetItemSize().cy / 2 + pMimicsItem->GetItemSize().cy));
				pMimicsItem->SetItemCenterPoint();
				pMimicsItem->InitializeProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (clsid == CLSID_CMimicsImageCtrl)
	{
		if ((pMimicsItem = new CMimicsImageItem(pDocument)))
		{
			if (pMimicsItem->CreateNewItem(clsid, pView))
			{
				pMimicsItem->SetItemPosition(CRect(point.x - pMimicsItem->GetItemSize().cx / 2, point.y - pMimicsItem->GetItemSize().cy / 2, point.x - pMimicsItem->GetItemSize().cx / 2 + pMimicsItem->GetItemSize().cx, point.y - pMimicsItem->GetItemSize().cy / 2 + pMimicsItem->GetItemSize().cy));
				pMimicsItem->SetItemCenterPoint();
				pMimicsItem->InitializeProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	return((CMimicsItem *)NULL);
}
CMimicsItem *CMimicsItem::Create(CMimicsItem *pItem, CView *pView, CMMDDocument *pDocument)
{
	CMimicsItem  *pMimicsItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsLineItem)))
	{
		if ((pMimicsItem = new CMimicsLineItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsLineCtrl, pView))
			{
				pMimicsItem->UpdateProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsRectangleItem)))
	{
		if ((pMimicsItem = new CMimicsRectangleItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsRectangleCtrl, pView))
			{
				pMimicsItem->UpdateProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsEllipseItem)))
	{
		if ((pMimicsItem = new CMimicsEllipseItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsEllipseCtrl, pView))
			{
				pMimicsItem->UpdateProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsArcItem)))
	{
		if ((pMimicsItem = new CMimicsArcItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsArcCtrl, pView))
			{
				pMimicsItem->UpdateProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTriangleItem)))
	{
		if ((pMimicsItem = new CMimicsTriangleItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsTriangleCtrl, pView))
			{
				pMimicsItem->UpdateProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsSwitchItem)))
	{
		if ((pMimicsItem = new CMimicsSwitchItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsSwitchCtrl, pView))
			{
				pMimicsItem->UpdateProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTextItem)))
	{
		if ((pMimicsItem = new CMimicsTextItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsTextCtrl, pView))
			{
				pMimicsItem->UpdateProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsImageItem)))
	{
		if ((pMimicsItem = new CMimicsImageItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsImageCtrl, pView))
			{
				pMimicsItem->UpdateProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)))
	{
		if ((pMimicsItem = new CMimicsGroup(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsGroupCtrl, pView))
			{
				pMimicsItem->UpdateProperties();
				return pMimicsItem;
			}
			delete pMimicsItem;
		}
	}
	return((CMimicsItem *)NULL);
}

BOOL CMimicsItem::CreateNewItem(REFCLSID clsid, CView *pView, OLERENDER render, CLIPFORMAT cfFormat, LPFORMATETC lpFormatEtc)
{
	Lock();
	if (CMimicsClientItem::CreateNewItem(clsid, render, cfFormat, lpFormatEtc))
	{
		SetItemClassID(clsid);
		SetItemName();
		SetItemType();
		SetItemSize();
		SetItemCenterPoint();
		SetItemToolTipText();
		SetItemImage(pView);
		SetItemVisibility();
		m_bOriginal = TRUE;
		Unlock();
		return TRUE;
	}
	Unlock();
	return FALSE;
}

CMimicsItem *CMimicsItem::AllocateFromItem(CMimicsItem *pItem, CMMDDocument *pDocument)
{
	CMimicsItem  *pMimicsItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsLineItem)))
	{
		if ((pMimicsItem = new CMimicsLineItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsRectangleItem)))
	{
		if ((pMimicsItem = new CMimicsRectangleItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsEllipseItem)))
	{
		if ((pMimicsItem = new CMimicsEllipseItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsArcItem)))
	{
		if ((pMimicsItem = new CMimicsArcItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTriangleItem)))
	{
		if ((pMimicsItem = new CMimicsTriangleItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsSwitchItem)))
	{
		if ((pMimicsItem = new CMimicsSwitchItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTextItem)))
	{
		if ((pMimicsItem = new CMimicsTextItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsImageItem)))
	{
		if ((pMimicsItem = new CMimicsImageItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)))
	{
		if ((pMimicsItem = new CMimicsGroup))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	return((CMimicsItem *)NULL);
}
CMimicsItem *CMimicsItem::AllocateFromItem(CMMDLayoutItem *pItem, CMMDDocument *pDocument)
{
	CMimicsItem  *pMimicsItem;

	if (pItem->GetClassID() == CLSID_CMimicsLineCtrl)
	{
		if ((pMimicsItem = new CMimicsLineItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->GetClassID() == CLSID_CMimicsRectangleCtrl)
	{
		if ((pMimicsItem = new CMimicsRectangleItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->GetClassID() == CLSID_CMimicsEllipseCtrl)
	{
		if ((pMimicsItem = new CMimicsEllipseItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->GetClassID() == CLSID_CMimicsArcCtrl)
	{
		if ((pMimicsItem = new CMimicsArcItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->GetClassID() == CLSID_CMimicsTriangleCtrl)
	{
		if ((pMimicsItem = new CMimicsTriangleItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->GetClassID() == CLSID_CMimicsSwitchCtrl)
	{
		if ((pMimicsItem = new CMimicsSwitchItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->GetClassID() == CLSID_CMimicsTextCtrl)
	{
		if ((pMimicsItem = new CMimicsTextItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->GetClassID() == CLSID_CMimicsImageCtrl)
	{
		if ((pMimicsItem = new CMimicsImageItem))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	if (pItem->GetClassID() == CLSID_CMimicsGroupCtrl)
	{
		if ((pMimicsItem = new CMimicsGroup))
		{
			pMimicsItem->m_pDocument = pDocument;
			return pMimicsItem;
		}
	}
	return((CMimicsItem *)NULL);
}

CMimicsItem *CMimicsItem::AllocateFromData(CONST CByteArray &nData, CMMDDocument *pDocument)
{
	CMimicsItem  *pMimicsItem;
	CMMDLayoutItem  cLayoutItem;

	if (cLayoutItem.Unmap(nData))
	{
		if (cLayoutItem.GetClassID() == CLSID_CMimicsLineCtrl)
		{
			if ((pMimicsItem = new CMimicsLineItem))
			{
				pMimicsItem->m_pDocument = pDocument;
				return pMimicsItem;
			}
		}
		if (cLayoutItem.GetClassID() == CLSID_CMimicsRectangleCtrl)
		{
			if ((pMimicsItem = new CMimicsRectangleItem))
			{
				pMimicsItem->m_pDocument = pDocument;
				return pMimicsItem;
			}
		}
		if (cLayoutItem.GetClassID() == CLSID_CMimicsEllipseCtrl)
		{
			if ((pMimicsItem = new CMimicsEllipseItem))
			{
				pMimicsItem->m_pDocument = pDocument;
				return pMimicsItem;
			}
		}
		if (cLayoutItem.GetClassID() == CLSID_CMimicsArcCtrl)
		{
			if ((pMimicsItem = new CMimicsArcItem))
			{
				pMimicsItem->m_pDocument = pDocument;
				return pMimicsItem;
			}
		}
		if (cLayoutItem.GetClassID() == CLSID_CMimicsTriangleCtrl)
		{
			if ((pMimicsItem = new CMimicsTriangleItem))
			{
				pMimicsItem->m_pDocument = pDocument;
				return pMimicsItem;
			}
		}
		if (cLayoutItem.GetClassID() == CLSID_CMimicsSwitchCtrl)
		{
			if ((pMimicsItem = new CMimicsSwitchItem))
			{
				pMimicsItem->m_pDocument = pDocument;
				return pMimicsItem;
			}
		}
		if (cLayoutItem.GetClassID() == CLSID_CMimicsTextCtrl)
		{
			if ((pMimicsItem = new CMimicsTextItem))
			{
				pMimicsItem->m_pDocument = pDocument;
				return pMimicsItem;
			}
		}
		if (cLayoutItem.GetClassID() == CLSID_CMimicsImageCtrl)
		{
			if ((pMimicsItem = new CMimicsImageItem))
			{
				pMimicsItem->m_pDocument = pDocument;
				return pMimicsItem;
			}
		}
		if (cLayoutItem.GetClassID() == CLSID_CMimicsGroupCtrl)
		{
			if ((pMimicsItem = new CMimicsGroup))
			{
				pMimicsItem->m_pDocument = pDocument;
				return pMimicsItem;
			}
		}
	}
	return((CMimicsItem *)NULL);
}

VOID CMimicsItem::SetItemName(LPCTSTR pszName)
{
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMimicsGroup  *pGroup;
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	for (lPosition = ((pGroup = (IsKindOf(RUNTIME_CLASS(CMimicsGroup))) ? (CMimicsGroup *) this : (CMimicsGroup *)NULL) && !lstrcmp(pszName, STRING(IDS_MMD_STATUSBAR_OBJECTDEFAULTNAME))) ? pGroup->GetItemList()->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CMimicsItem *)pGroup->GetItemList()->GetNextItem(lPosition)))
		{
			pItem->SetItemName(pszName);
			continue;
		}
	}
	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (!AfxIsValidString(pszName))
		{
			cMimicsItem.SetName(m_szName);
			return;
		}
	}
	m_szName = pszName;
}

CString CMimicsItem::GetItemName() CONST
{
	CString  szName;
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		szName = cMimicsItem.GetName();
		return szName;
	}
	return m_szName;
}

VOID CMimicsItem::SetItemClassID(CLSID clsid)
{
	m_clsid = clsid;
}

CLSID CMimicsItem::GetItemClassID() CONST
{
	return m_clsid;
}

VOID CMimicsItem::SetItemType(LPCTSTR pszType)
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsItem.SetType((m_szType = (!AfxIsValidString(pszType)) ? cMimicsItem.GetType() : pszType));
		return;
	}
	m_szType = pszType;
}

CString CMimicsItem::GetItemType() CONST
{
	CString  szType;
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		szType = cMimicsItem.GetType();
		return szType;
	}
	return m_szType;
}

VOID CMimicsItem::SetItemLink(LPCTSTR pszName)
{
	m_szLink = pszName;
}

CString CMimicsItem::GetItemLink() CONST
{
	return m_szLink;
}

VOID CMimicsItem::SetItemSize(INT cx, INT cy)
{
	SIZE  sizeItem[2];
	CClientDC  cDC(NULL);

	if (GetOleObject() != (LPOLEOBJECT)NULL  &&  GetDocument())
	{
		for (sizeItem[0].cx = (!cx && !cy) ? abs(m_rPosition[0].Width()) : cx, sizeItem[0].cy = (!cx && !cy) ? abs(m_rPosition[0].Height()) : cy, GetCachedExtent(&sizeItem[1]), cDC.HIMETRICtoDP(&sizeItem[1]); (!cx && !cy) || sizeItem[0].cx != sizeItem[1].cx || sizeItem[0].cy != sizeItem[1].cy; )
		{
			cDC.DPtoHIMETRIC(&sizeItem[0]);
			SetExtent(sizeItem[0]);
			break;
		}
	}
}

CSize CMimicsItem::GetItemSize() CONST
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsItem.GetInitialSize() : CSize(0, 0));
}

VOID CMimicsItem::SetItemToolTipText(LPCTSTR pszText)
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsItem.SetToolTipText((!AfxIsValidString(pszText)) ? m_szText : pszText);
		return;
	}
	m_szText = pszText;
}

CString CMimicsItem::GetItemToolTipText() CONST
{
	CString  szText;
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		szText = cMimicsItem.GetToolTipText();
		return szText;
	}
	return m_szText;
}

VOID CMimicsItem::SetItemRotateMode(BOOL bFlag)
{
	m_bRotateFlag = bFlag;
}

BOOL CMimicsItem::GetItemRotateMode() CONST
{
	return m_bRotateFlag;
}

VOID CMimicsItem::ActivateItem(BOOL bActivate)
{
	for (; !bActivate && IsItemActivated(TRUE); )
	{
		Deactivate();
		break;
	}
	m_bActivated = bActivate;
}
VOID CMimicsItem::ActivateItem(LONG nVerb, CView *pView, LPMSG lpMsg)
{
	for (SelectItem(FALSE); nVerb == OLEIVERB_PROPERTIES; )
	{
		if ((m_bProperties = IsWindow(pView->GetSafeHwnd())))
		{
			DoVerb(OLEIVERB_PROPERTIES, pView, lpMsg);
			m_bProperties = FALSE;
			pView->SetFocus();
		}
		return;
	}
	CMimicsClientItem::Activate(nVerb, pView, lpMsg);
}

BOOL CMimicsItem::IsItemActivated(BOOL bInPlace) CONST
{
	return(((!bInPlace  &&  m_bActivated) || (bInPlace && (m_nItemState == activeState || m_nItemState == activeUIState))) ? TRUE : FALSE);
}

BOOL CMimicsItem::SelectItem(BOOL bSelect)
{
	if (!GetItemContainer())
	{
		m_bSelected = bSelect;
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsItem::IsItemSelected() CONST
{
	return m_bSelected;
}

VOID CMimicsItem::ShowItem()
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsItem.Show();
		return;
	}
	m_bVisible = TRUE;
}

VOID CMimicsItem::HideItem()
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsItem.Hide();
		return;
	}
	m_bVisible = FALSE;
}

BOOL CMimicsItem::IsItemVisible() CONST
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsItem.IsVisible() : m_bVisible);
}

VOID CMimicsItem::SetItemVisibility(UINT bVisible)
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (bVisible == (UINT)-1 && m_bVisible)
		{
			cMimicsItem.Show();
			return;
		}
		if (bVisible == (UINT)-1)
		{
			cMimicsItem.Hide();
			return;
		}
		if (bVisible)
		{
			cMimicsItem.Show();
			return;
		}
		cMimicsItem.Hide();
		return;
	}
	m_bVisible = (bVisible == (UINT)-1) ? m_bVisible : bVisible;
}

BOOL CMimicsItem::GetItemVisibility() CONST
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsItem.IsVisible() : m_bVisible);
}

VOID CMimicsItem::SetItemProperties(CONST CByteArray &nInfo)
{
	m_nInfo.Copy(nInfo);
}

BOOL CMimicsItem::GetItemProperties(CByteArray &nInfo) CONST
{
	nInfo.Copy(m_nInfo);
	return((nInfo.GetSize() > 0) ? TRUE : FALSE);
}

VOID CMimicsItem::SetItemContainer(CMimicsItem *pItem)
{
	m_pContainerItem = pItem;
	m_bSelected = FALSE;
}

CMimicsItem *CMimicsItem::GetItemContainer() CONST
{
	return m_pContainerItem;
}

VOID CMimicsItem::AdjustItemContainer()
{
	CMimicsItem  *pItem;

	if ((pItem = GetItemContainer()))
	{
		pItem->AdjustItemPosition();
		return;
	}
}

VOID CMimicsItem::SetItemImage(CView *pView)
{
	POSITION  lPosition;

	for (lPosition = (!pView) ? GetDocument()->CDocument::GetFirstViewPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pView = GetDocument()->CDocument::GetNextView(lPosition))) break;
		continue;
	}
	m_pImageView = pView;
}

CView *CMimicsItem::GetItemImage() CONST
{
	return m_pImageView;
}

VOID CMimicsItem::SetItemPosition(CONST RECT &rect)
{
	CRect  rPosition;

	rPosition = rect;
	rPosition.OffsetRect(GetPosition().CenterPoint() - GetItemPosition().CenterPoint());
	SetPosition(rPosition);
}

CRect CMimicsItem::GetItemPosition() CONST
{
	return m_rPosition[0];
}
VOID CMimicsItem::GetItemPosition(CPoint &point, CSize &size) CONST
{
	CRect  rItem;
	CPoint  ptItem[4];

	rItem = GetItemPosition();
	ptItem[0] = CalcTransform(CPoint(rItem.left, rItem.top));
	ptItem[2] = CalcTransform(CPoint(rItem.right, rItem.bottom));
	ptItem[1] = CalcTransform(CPoint(rItem.right, rItem.top));
	ptItem[3] = CalcTransform(CPoint(rItem.left, rItem.bottom));
	size.cx = max(max(max(ptItem[0].x, ptItem[1].x), ptItem[2].x), ptItem[3].x) - min(min(min(ptItem[0].x, ptItem[1].x), ptItem[2].x), ptItem[3].x);
	size.cy = max(max(max(ptItem[0].y, ptItem[1].y), ptItem[2].y), ptItem[3].y) - min(min(min(ptItem[0].y, ptItem[1].y), ptItem[2].y), ptItem[3].y);
	point.x = (ptItem[0].x + ptItem[2].x) / 2;
	point.y = (ptItem[0].y + ptItem[2].y) / 2;
}

VOID CMimicsItem::NormalizeItemPosition(BOOL bUndo)
{
	if (!bUndo)
	{
		DoTransformation(m_ptCenter, m_xForm, m_rPosition[0]);
		return;
	}
	DoInverseTransformation(m_ptCenter, m_xForm, m_rPosition[0]);
}

VOID CMimicsItem::AdjustItemPosition()
{
	return;
}
VOID CMimicsItem::AdjustItemPosition(CONST RECT &rect)
{
	m_ptCenter.x += (rect.left + rect.right) / 2 - m_rPosition[0].CenterPoint().x;
	m_ptCenter.y += (rect.top + rect.bottom) / 2 - m_rPosition[0].CenterPoint().y;
	m_rPosition[0] = rect;
}

VOID CMimicsItem::SetItemDefaultPosition(CONST RECT &rect)
{
	m_rPosition[1] = rect;
}

CRect CMimicsItem::GetItemDefaultPosition() CONST
{
	return m_rPosition[1];
}

VOID CMimicsItem::AdjustItemDefaultPosition()
{
	CRect  rItem;
	CRect  rGroup;
	CMimicsGroup  *pGroup;

	if ((pGroup = (CMimicsGroup *)GetItemContainer()))
	{
		rItem = GetItemPosition();
		rGroup = pGroup->GetItemPosition();
		rItem.OffsetRect(-rGroup.TopLeft());
		rItem.left = (rGroup.Width() > 0) ? ((rItem.left*GetSystemMetrics(SM_CXSCREEN)) / rGroup.Width()) : 0;
		rItem.top = (rGroup.Height() > 0) ? ((rItem.top*GetSystemMetrics(SM_CYSCREEN)) / rGroup.Height()) : 0;
		rItem.right = (rGroup.Width() > 0) ? ((rItem.right*GetSystemMetrics(SM_CXSCREEN)) / rGroup.Width()) : 0;
		rItem.bottom = (rGroup.Height() > 0) ? ((rItem.bottom*GetSystemMetrics(SM_CYSCREEN)) / rGroup.Height()) : 0;
		SetItemDefaultPosition(rItem);
	}
}

VOID CMimicsItem::SetItemCenterPoint()
{
	SetItemCenterPoint(m_rPosition[0].CenterPoint());
}
VOID CMimicsItem::SetItemCenterPoint(CONST POINT &ptCenter)
{
	m_ptCenter = ptCenter;
}

CPoint CMimicsItem::GetItemCenterPoint() CONST
{
	return m_ptCenter;
}

VOID CMimicsItem::AdjustItemCenterPoint()
{
	CRect  rPosition;
	CPoint  ptItem[2];

	rPosition = GetItemPosition();
	if (m_ptCenter != rPosition.CenterPoint())
	{
		ptItem[0] = DoTransformation(rPosition.TopLeft());
		ptItem[1] = DoTransformation(rPosition.BottomRight());
		m_ptCenter.x = (ptItem[0].x + ptItem[1].x) / 2;
		m_ptCenter.y = (ptItem[0].y + ptItem[1].y) / 2;
		rPosition.OffsetRect(m_ptCenter - rPosition.CenterPoint());
		m_rPosition[0] = rPosition;
	}
}

VOID CMimicsItem::HorzFlipItem()
{
	FlipHorizontal();
}

VOID CMimicsItem::VertFlipItem()
{
	FlipVertical();
}

VOID CMimicsItem::RotateItem(double fAngle)
{
	Rotate(fAngle);
}

BOOL CMimicsItem::IsItemFlippedOrRotated() CONST
{
	return((m_xForm.eM11 != 1.0 || m_xForm.eM12 != 0.0 || m_xForm.eM21 != 0.0 || m_xForm.eM22 != 1.0) ? TRUE : FALSE);
}

BOOL CMimicsItem::IsItemSizeable() CONST
{
	return TRUE;
}

VOID CMimicsItem::DragItem(UINT nCode, CONST POINT &ptNew, CONST POINT &ptOld)
{
	return;
}

BOOL CMimicsItem::DrawItemFrame(CDC *pDC, CONST RECT &rect)
{
	INT  x;
	INT  y;
	INT  nPt;
	INT  nPts;
	INT  nRgn;
	INT  nThumb;
	INT  nThumbs;
	CPen  cThumbPen;
	CPen  cFramePen;
	CPen  *pOldPen;
	CRgn  rgClip;
	CRgn  rgFrame;
	CRect  rFrame;
	POINT  *pPoints;
	CBrush  brThumb;
	CBrush  *pOldBrush;
	RECT  rThumbs[MIAC_THUMBS];

	if (IsItemActivated(TRUE))
	{
		if (GetItemRotateMode())
		{
			if (cThumbPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME)))
			{
				if (brThumb.CreateSolidBrush(GetSysColor(COLOR_3DFACE)))
				{
					if ((pOldPen = (CPen *)pDC->SelectObject(&cThumbPen)))
					{
						if ((pOldBrush = (CBrush *)pDC->SelectObject(&brThumb)))
						{
							for (nThumb = 0, nThumbs = CalcItemFrameTurnThumbPositions(rect, rThumbs, sizeof(rThumbs) / sizeof(rThumbs[0])); nThumb < nThumbs; nThumb++)
							{
								if (!IsRectEmpty(&rThumbs[nThumb])) pDC->Ellipse(&rThumbs[nThumb]);
								continue;
							}
							pDC->SelectObject(pOldBrush);
						}
						pDC->SelectObject(pOldPen);
					}
					brThumb.DeleteObject();
				}
				cThumbPen.DeleteObject();
			}
			return TRUE;
		}
		if (cThumbPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME)))
		{
			if (brThumb.CreateSolidBrush(GetSysColor(COLOR_3DFACE)))
			{
				if ((pOldPen = (CPen *)pDC->SelectObject(&cThumbPen)))
				{
					if ((pOldBrush = (CBrush *)pDC->SelectObject(&brThumb)))
					{
						for (nThumb = 0, nThumbs = CalcItemFrameThumbPositions(rect, rThumbs, sizeof(rThumbs) / sizeof(rThumbs[0])); nThumb < nThumbs; nThumb++)
						{
							if (!IsRectEmpty(&rThumbs[nThumb])) pDC->Rectangle(&rThumbs[nThumb]);
							continue;
						}
						pDC->SelectObject(pOldBrush);
					}
					pDC->SelectObject(pOldPen);
				}
				brThumb.DeleteObject();
			}
			cThumbPen.DeleteObject();
		}
		return TRUE;
	}
	if (IsItemSelected())
	{
		if ((nPts = CalcItemFrameOutlinePoints(rect)))
		{
			if ((pPoints = (LPPOINT)GlobalAlloc(GPTR, nPts*sizeof(POINT))))
			{
				for (nPt = 0, nPts = CalcItemFrameOutlinePoints(rect, pPoints, nPts), rFrame.SetRectEmpty(); nPt < nPts; nPt++)
				{
					rFrame.left = (nPt > 0) ? min(pPoints[nPt].x - 1, rFrame.left) : (pPoints[nPt].x - 1);
					rFrame.top = (nPt > 0) ? min(pPoints[nPt].y - 1, rFrame.top) : (pPoints[nPt].y - 1);
					rFrame.right = (nPt > 0) ? max(pPoints[nPt].x + 1, rFrame.right) : (pPoints[nPt].x + 1);
					rFrame.bottom = (nPt > 0) ? max(pPoints[nPt].y + 1, rFrame.bottom) : (pPoints[nPt].y + 1);
				}
				if (cFramePen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME)))
				{
					if (rgFrame.CreatePolygonRgn(pPoints, nPts, WINDING) && rgClip.CreateRectRgn(0, 0, 0, 0))
					{
						if ((nRgn = GetClipRgn(pDC->GetSafeHdc(), rgClip)) >= 0)
						{
							if (ExtSelectClipRgn(pDC->GetSafeHdc(), rgFrame, RGN_AND) != ERROR)
							{
								if ((pOldPen = pDC->SelectObject(&cFramePen)) != (CPen *)NULL)
								{
									for (x = rFrame.left, y = rFrame.top; y <= rFrame.top + rFrame.Height() + rFrame.Width(); y += MIMICSITEM_GRID_SIZE)
									{
										pDC->MoveTo(x, y);
										pDC->LineTo(x + y - rFrame.top, rFrame.top);
									}
									pDC->SelectObject(pOldPen);
								}
							}
							pDC->SelectClipRgn((nRgn > 0) ? (CRgn *)&rgClip : (CRgn *)NULL);
						}
						rgFrame.DeleteObject();
					}
					cFramePen.DeleteObject();
				}
				GlobalFree(pPoints);
			}
		}
	}
	return FALSE;
}

BOOL CMimicsItem::DrawItemDraggingFrame(CDC *pDC, CONST RECT &rect)
{
	INT  nMode;
	CPen  *pOldPen;
	CPen  cFramePen;
	CPoint  ptFrame[4];

	if (cFramePen.CreatePen(PS_DOT, 1, GetSysColor(COLOR_WINDOWFRAME)))
	{
		if ((pOldPen = (CPen *)pDC->SelectObject(&cFramePen)))
		{
			ptFrame[0] = DoTransformation(CPoint(rect.left - 1, rect.top - 1));
			ptFrame[1] = DoTransformation(CPoint(rect.right, rect.top - 1));
			ptFrame[2] = DoTransformation(CPoint(rect.right, rect.bottom));
			ptFrame[3] = DoTransformation(CPoint(rect.left - 1, rect.bottom));
			nMode = pDC->SetROP2(R2_MASKNOTPEN);
			pDC->MoveTo(ptFrame[0]);
			pDC->LineTo(ptFrame[1]);
			pDC->LineTo(ptFrame[2]);
			pDC->LineTo(ptFrame[3]);
			pDC->LineTo(ptFrame[0]);
			pDC->SetROP2(nMode);
			pDC->SelectObject(pOldPen);
			cFramePen.DeleteObject();
			return TRUE;
		}
		cFramePen.DeleteObject();
	}
	return FALSE;
}

CRect CMimicsItem::CalcItemFrameExtent() CONST
{
	return DoTransformation(GetItemPosition());
}

CRect CMimicsItem::CalcItemFramePosition() CONST
{
	CRect  rFrame;

	rFrame = DoTransformation(GetItemPosition());
	rFrame.InflateRect((GetItemRotateMode()) ? (MIMICSITEM_THUMB_SIZE / 2 + 1) : (MIMICSITEM_THUMB_SIZE / 2), (GetItemRotateMode()) ? (MIMICSITEM_THUMB_SIZE / 2 + 1) : (MIMICSITEM_THUMB_SIZE / 2));
	rFrame.InflateRect(0, 0, 1, 1);
	return rFrame;
}

CRect CMimicsItem::CalcItemFrameThumbPosition(UINT nCode, CONST RECT &rect) CONST
{
	CPoint  ptThumb;

	switch (nCode)
	{
	case MIAC_SWTHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.left, rect.bottom));
	break;
	}
	case MIAC_WTHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.left, (rect.top + rect.bottom) / 2));
	break;
	}
	case MIAC_NWTHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.left, rect.top));
	break;
	}
	case MIAC_NTHUMB:
	{ ptThumb = DoTransformation(CPoint((rect.left + rect.right) / 2, rect.top));
	break;
	}
	case MIAC_NETHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.right, rect.top));
	break;
	}
	case MIAC_ETHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.right, (rect.top + rect.bottom) / 2));
	break;
	}
	case MIAC_SETHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.right, rect.bottom));
	break;
	}
	case MIAC_STHUMB:
	{ ptThumb = DoTransformation(CPoint((rect.left + rect.right) / 2, rect.bottom));
	break;
	}
	}
	return((nCode == MIAC_SWTHUMB || nCode == MIAC_WTHUMB || nCode == MIAC_NWTHUMB || nCode == MIAC_NTHUMB || nCode == MIAC_NETHUMB || nCode == MIAC_ETHUMB || nCode == MIAC_SETHUMB || nCode == MIAC_STHUMB) ? CRect(ptThumb.x - MIMICSITEM_THUMB_SIZE / 2, ptThumb.y - MIMICSITEM_THUMB_SIZE / 2, ptThumb.x + MIMICSITEM_THUMB_SIZE / 2, ptThumb.y + MIMICSITEM_THUMB_SIZE / 2) : CRect(0, 0, 0, 0));
}

INT CMimicsItem::CalcItemFrameThumbPositions(CONST RECT &rect, LPRECT prThumbs, INT nThumbs) CONST
{
	CRect  rThumb;

	if (nThumbs >= MIAC_SWTHUMB) SetRect(&prThumbs[MIAC_SWTHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameThumbPosition(MIAC_SWTHUMB, rect)).bottom);
	if (nThumbs >= MIAC_WTHUMB) SetRect(&prThumbs[MIAC_WTHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameThumbPosition(MIAC_WTHUMB, rect)).bottom);
	if (nThumbs >= MIAC_NWTHUMB) SetRect(&prThumbs[MIAC_NWTHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameThumbPosition(MIAC_NWTHUMB, rect)).bottom);
	if (nThumbs >= MIAC_NTHUMB) SetRect(&prThumbs[MIAC_NTHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameThumbPosition(MIAC_NTHUMB, rect)).bottom);
	if (nThumbs >= MIAC_NETHUMB) SetRect(&prThumbs[MIAC_NETHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameThumbPosition(MIAC_NETHUMB, rect)).bottom);
	if (nThumbs >= MIAC_ETHUMB) SetRect(&prThumbs[MIAC_ETHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameThumbPosition(MIAC_ETHUMB, rect)).bottom);
	if (nThumbs >= MIAC_SETHUMB) SetRect(&prThumbs[MIAC_SETHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameThumbPosition(MIAC_SETHUMB, rect)).bottom);
	if (nThumbs >= MIAC_STHUMB) SetRect(&prThumbs[MIAC_STHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameThumbPosition(MIAC_STHUMB, rect)).bottom);
	return((nThumbs > 0) ? min(nThumbs, MIAC_THUMBS) : MIAC_THUMBS);
}

CRect CMimicsItem::CalcItemFrameTurnThumbPosition(UINT nCode, CONST RECT &rect) CONST
{
	CPoint  ptThumb;

	switch (nCode)
	{
	case MIAC_SWTHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.left, rect.bottom));
	break;
	}
	case MIAC_NWTHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.left, rect.top));
	break;
	}
	case MIAC_NETHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.right, rect.top));
	break;
	}
	case MIAC_SETHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.right, rect.bottom));
	break;
	}
	}
	return((nCode == MIAC_SWTHUMB || nCode == MIAC_NWTHUMB || nCode == MIAC_NETHUMB || nCode == MIAC_SETHUMB) ? CRect(ptThumb.x - MIMICSITEM_THUMB_SIZE / 2 - 1, ptThumb.y - MIMICSITEM_THUMB_SIZE / 2 - 1, ptThumb.x + MIMICSITEM_THUMB_SIZE / 2, ptThumb.y + MIMICSITEM_THUMB_SIZE / 2) : CRect(0, 0, 0, 0));
}

INT CMimicsItem::CalcItemFrameTurnThumbPositions(CONST RECT &rect, LPRECT prThumbs, INT nThumbs) CONST
{
	CRect  rThumb;

	if (nThumbs >= MIAC_SWTHUMB) SetRect(&prThumbs[MIAC_SWTHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameTurnThumbPosition(MIAC_SWTHUMB, rect)).bottom);
	if (nThumbs >= MIAC_WTHUMB) SetRect(&prThumbs[MIAC_WTHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameTurnThumbPosition(MIAC_WTHUMB, rect)).bottom);
	if (nThumbs >= MIAC_NWTHUMB) SetRect(&prThumbs[MIAC_NWTHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameTurnThumbPosition(MIAC_NWTHUMB, rect)).bottom);
	if (nThumbs >= MIAC_NTHUMB) SetRect(&prThumbs[MIAC_NTHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameTurnThumbPosition(MIAC_NTHUMB, rect)).bottom);
	if (nThumbs >= MIAC_NETHUMB) SetRect(&prThumbs[MIAC_NETHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameTurnThumbPosition(MIAC_NETHUMB, rect)).bottom);
	if (nThumbs >= MIAC_ETHUMB) SetRect(&prThumbs[MIAC_ETHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameTurnThumbPosition(MIAC_ETHUMB, rect)).bottom);
	if (nThumbs >= MIAC_SETHUMB) SetRect(&prThumbs[MIAC_SETHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameTurnThumbPosition(MIAC_SETHUMB, rect)).bottom);
	if (nThumbs >= MIAC_STHUMB) SetRect(&prThumbs[MIAC_STHUMB - 1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameTurnThumbPosition(MIAC_STHUMB, rect)).bottom);
	return((nThumbs > 0) ? min(nThumbs, MIAC_THUMBS) : MIAC_THUMBS);
}

INT CMimicsItem::CalcItemFrameOutlinePoints(CONST RECT &rect, LPPOINT pPoints, INT nPoints) CONST
{
	if (nPoints > 0) pPoints[0] = CalcItemFrameThumbPosition(MIAC_SWTHUMB, rect).CenterPoint();
	if (nPoints > 1) pPoints[1] = CalcItemFrameThumbPosition(MIAC_NWTHUMB, rect).CenterPoint();
	if (nPoints > 2) pPoints[2] = CalcItemFrameThumbPosition(MIAC_NETHUMB, rect).CenterPoint();
	if (nPoints > 3) pPoints[3] = CalcItemFrameThumbPosition(MIAC_SETHUMB, rect).CenterPoint();
	return((nPoints > 0) ? ((nPoints >= 4) ? min(nPoints, 4) : 0) : 4);
}

BOOL CMimicsItem::CalcItemShape(CBitmap *pBitmap)
{
	CDC  cDC;
	CRect  rItem;
	CBitmap  *pOldBitmap;

	if (cDC.CreateCompatibleDC(NULL))
	{
		if (pBitmap->CreateBitmap(rItem.right + 1, (rItem = DoTransformation(GetItemPosition())).bottom + 1, 1, 1, (LPCVOID)NULL))
		{
			if ((pOldBitmap = cDC.SelectObject(pBitmap)))
			{
				Draw(&cDC, TRUE);
				cDC.SelectObject(pOldBitmap);
				cDC.DeleteDC();
				return TRUE;
			}
			pBitmap->DeleteObject();
		}
		cDC.DeleteDC();
	}
	return FALSE;
}

UINT CMimicsItem::CheckPointOnItem(CONST POINT &ptPosition)
{
	CRect  rItem;

	if (IsItemActivated(TRUE))
	{
		if (GetItemRotateMode())
		{
			if (CalcItemFrameTurnThumbPosition(MIAC_SWTHUMB, (rItem = GetItemPosition())).PtInRect(ptPosition)) return MIAC_SWTHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_NWTHUMB, rItem).PtInRect(ptPosition)) return MIAC_NWTHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_NETHUMB, rItem).PtInRect(ptPosition)) return MIAC_NETHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_SETHUMB, rItem).PtInRect(ptPosition)) return MIAC_SETHUMB;
		}
		else
		{
			if (CalcItemFrameThumbPosition(MIAC_SWTHUMB, (rItem = GetItemPosition())).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_SWTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_WTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_WTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_NWTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NWTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_NTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_NETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NETHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_ETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_ETHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_SETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_SETHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_STHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_STHUMB : MIAC_NOWHERE);
		}
	}
	return((CheckPointInsideItem(ptPosition)) ? MIAC_INSIDE : MIAC_NOWHERE);
}

BOOL CMimicsItem::CheckPointInsideItem(CONST POINT &ptPosition)
{
	CDC  cDC;
	CRgn  rgItem;
	CRect  rItem;
	POINT  ptItem[4];
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;

	rItem = GetItemPosition();
	rItem.InflateRect((!rItem.Width()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0, 0);
	rItem.InflateRect(0, (!rItem.Height()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0);
	ptItem[0] = DoTransformation(CPoint(rItem.left, rItem.top));
	ptItem[1] = DoTransformation(CPoint(rItem.right, rItem.top));
	ptItem[2] = DoTransformation(CPoint(rItem.right, rItem.bottom));
	ptItem[3] = DoTransformation(CPoint(rItem.left, rItem.bottom));
	if (rgItem.CreatePolygonRgn(ptItem, sizeof(ptItem) / sizeof(POINT), WINDING))
	{
		if (!rgItem.PtInRegion(ptPosition))
		{
			rgItem.DeleteObject();
			return FALSE;
		}
		if (rItem.Width() == MIMICSITEM_THUMB_SIZE / 2 || rItem.Height() == MIMICSITEM_THUMB_SIZE / 2 || IsItemActivated(TRUE))
		{
			rgItem.DeleteObject();
			return TRUE;
		}
		if (CalcItemShape(&cBitmap))
		{
			if (cDC.CreateCompatibleDC(NULL))
			{
				if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
				{
					if (cDC.GetPixel(ptPosition))
					{
						cDC.SelectObject(pOldBitmap);
						cBitmap.DeleteObject();
						rgItem.DeleteObject();
						cDC.DeleteDC();
						return TRUE;
					}
					cDC.SelectObject(pOldBitmap);
				}
				cDC.DeleteDC();
			}
			cBitmap.DeleteObject();
		}
		rgItem.DeleteObject();
	}
	return FALSE;
}

BOOL CMimicsItem::CheckItemOnItem(CMimicsItem *pItem)
{
	INT  cx;
	INT  cy;
	INT  nCode;
	INT  nByte;
	INT  nBytes;
	CDC  cDC[3];
	CRgn  rgItem[3];
	CRect  rItem[2];
	BYTE  *pBitmapBits;
	POINT  ptItem[2][4];
	BITMAP  sBitmap[3];
	CBitmap  cBitmap[3];
	CBitmap  *pOldBitmap[3];

	rItem[0] = GetItemPosition();
	rItem[1] = pItem->GetItemPosition();
	rItem[0].InflateRect((!rItem[0].Width()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0, 0);
	rItem[0].InflateRect(0, (!rItem[0].Height()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0);
	rItem[1].InflateRect((!rItem[1].Width()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0, 0);
	rItem[1].InflateRect(0, (!rItem[1].Height()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0);
	ptItem[0][0] = DoTransformation(CPoint(rItem[0].left, rItem[0].top));
	ptItem[0][1] = DoTransformation(CPoint(rItem[0].right, rItem[0].top));
	ptItem[0][2] = DoTransformation(CPoint(rItem[0].right, rItem[0].bottom));
	ptItem[0][3] = DoTransformation(CPoint(rItem[0].left, rItem[0].bottom));
	ptItem[1][0] = pItem->DoTransformation(CPoint(rItem[1].left, rItem[1].top));
	ptItem[1][1] = pItem->DoTransformation(CPoint(rItem[1].right, rItem[1].top));
	ptItem[1][2] = pItem->DoTransformation(CPoint(rItem[1].right, rItem[1].bottom));
	ptItem[1][3] = pItem->DoTransformation(CPoint(rItem[1].left, rItem[1].bottom));
	if (rgItem[0].CreatePolygonRgn(ptItem[0], sizeof(ptItem[0]) / sizeof(POINT), WINDING) && rgItem[1].CreatePolygonRgn(ptItem[1], sizeof(ptItem[1]) / sizeof(POINT), WINDING) && rgItem[2].CreateRectRgn(0, 0, 0, 0))
	{
		if ((nCode = rgItem[2].CombineRgn(&rgItem[0], &rgItem[1], RGN_AND)) == NULLREGION || nCode == ERROR)
		{
			rgItem[0].DeleteObject();
			rgItem[1].DeleteObject();
			rgItem[2].DeleteObject();
			return FALSE;
		}
		if (CalcItemShape(&cBitmap[0]))
		{
			if (pItem->CalcItemShape(&cBitmap[1]))
			{
				if (cDC[0].CreateCompatibleDC(NULL))
				{
					if (cDC[1].CreateCompatibleDC(NULL))
					{
						if (cDC[2].CreateCompatibleDC(NULL))
						{
							if (cBitmap[0].GetObject(sizeof(BITMAP), &sBitmap[0]) > 0)
							{
								if (cBitmap[1].GetObject(sizeof(BITMAP), &sBitmap[1]) > 0)
								{
									if (cBitmap[2].CreateBitmap((cx = min(sBitmap[0].bmWidth, sBitmap[1].bmWidth)), (cy = min(sBitmap[0].bmHeight, sBitmap[1].bmHeight)), 1, 1, (LPCVOID)NULL))
									{
										if ((pOldBitmap[0] = cDC[0].SelectObject(&cBitmap[0])))
										{
											if ((pOldBitmap[1] = cDC[1].SelectObject(&cBitmap[1])))
											{
												if ((pOldBitmap[2] = cDC[2].SelectObject(&cBitmap[2])))
												{
													cDC[2].BitBlt(0, 0, cx, cy, (CDC *)NULL, 0, 0, WHITENESS);
													cDC[2].BitBlt(0, 0, cx, cy, &cDC[0], 0, 0, SRCAND);
													cDC[2].BitBlt(0, 0, cx, cy, &cDC[1], 0, 0, SRCAND);
													if (cBitmap[2].GetObject(sizeof(BITMAP), &sBitmap[2]) > 0)
													{
														if ((pBitmapBits = (LPBYTE)GlobalAlloc(GPTR, (nBytes = sBitmap[2].bmWidthBytes*sBitmap[2].bmHeight))))
														{
															for (nByte = 0, nBytes = cBitmap[2].GetBitmapBits(nBytes, pBitmapBits); nByte < nBytes; nByte++)
															{
																if (pBitmapBits[nByte]) break;
																continue;
															}
															if (nByte < nBytes)
															{
																GlobalFree(pBitmapBits);
																cDC[0].SelectObject(pOldBitmap[0]);
																cDC[1].SelectObject(pOldBitmap[1]);
																cDC[2].SelectObject(pOldBitmap[2]);
																cBitmap[0].DeleteObject();
																cBitmap[1].DeleteObject();
																cBitmap[2].DeleteObject();
																rgItem[0].DeleteObject();
																rgItem[1].DeleteObject();
																rgItem[2].DeleteObject();
																cDC[0].DeleteDC();
																cDC[1].DeleteDC();
																cDC[2].DeleteDC();
																return TRUE;
															}
															GlobalFree(pBitmapBits);
														}
													}
													cDC[2].SelectObject(pOldBitmap[2]);
												}
												cDC[1].SelectObject(pOldBitmap[1]);
											}
											cDC[0].SelectObject(pOldBitmap[0]);
										}
										cBitmap[2].DeleteObject();
									}
								}
							}
							cDC[2].DeleteDC();
						}
						cDC[1].DeleteDC();
					}
					cDC[0].DeleteDC();
				}
				cBitmap[1].DeleteObject();
			}
			cBitmap[0].DeleteObject();
		}
		rgItem[0].DeleteObject();
		rgItem[1].DeleteObject();
		rgItem[2].DeleteObject();
	}
	return FALSE;
}

CRect CMimicsItem::DoTransformation(CONST RECT &rect) CONST
{
	CPoint  ptRect[4];

	ptRect[0] = DoTransformation(CPoint(rect.left, rect.top));
	ptRect[1] = DoTransformation(CPoint(rect.right, rect.top));
	ptRect[2] = DoTransformation(CPoint(rect.right, rect.bottom));
	ptRect[3] = DoTransformation(CPoint(rect.left, rect.bottom));
	return CRect(min(min(min(ptRect[0].x, ptRect[1].x), ptRect[2].x), ptRect[3].x), min(min(min(ptRect[0].y, ptRect[1].y), ptRect[2].y), ptRect[3].y), max(max(max(ptRect[0].x, ptRect[1].x), ptRect[2].x), ptRect[3].x), max(max(max(ptRect[0].y, ptRect[1].y), ptRect[2].y), ptRect[3].y));
}
CPoint CMimicsItem::DoTransformation(CONST POINT &point) CONST
{
	CPoint  pt;
	CMimicsItem  *pGroup;

	pt = CalcTransform((pt = point));
	for (pGroup = GetItemContainer(); pGroup; pGroup = pGroup->GetItemContainer())
	{
		pt = pGroup->CalcTransform(pt);
		continue;
	}
	return pt;
}
VOID CMimicsItem::DoTransformation(XFORM &xForm, CRect &rPosition) CONST
{
	CPoint  ptCenter;

	DoTransformation(this, ptCenter, xForm, rPosition);
}
VOID CMimicsItem::DoTransformation(CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST
{
	DoTransformation(this, ptCenter, xForm, rPosition);
}
VOID CMimicsItem::DoTransformation(CONST CMimicsItem *pItem, CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST
{
	CSize  ptOffset;
	CMimicsItem  *pGroup;

	rPosition = pItem->GetItemPosition();
	ptCenter = pItem->GetItemCenterPoint();
	CopyMemory(&xForm, &pItem->m_xForm, sizeof(XFORM));
	for (pGroup = pItem->GetItemContainer(); pGroup && pGroup != this; pGroup = pGroup->GetItemContainer())
	{
		rPosition.OffsetRect((ptOffset = pGroup->CalcTransform(rPosition.CenterPoint()) - rPosition.CenterPoint()));
		ptCenter.x += ptOffset.cx;
		ptCenter.y += ptOffset.cy;
		CombineTransform(&xForm, &xForm, &pGroup->m_xForm);
	}
}

CPoint CMimicsItem::DoInverseTransformation(CONST POINT &point) CONST
{
	CPoint  pt;
	XFORM  xInvForm;
	CPtrArray  pGroups;
	CMimicsItem  *pGroup;

	for (pGroup = GetItemContainer(); pGroup; pGroup = pGroup->GetItemContainer())
	{
		pGroups.Add(pGroup);
		continue;
	}
	for (pt = point; pGroups.GetSize() > 0; )
	{
		if ((pGroup = (CMimicsItem *)pGroups.GetAt(pGroups.GetUpperBound())))
		{
			pGroup->BuildInverseTransform(xInvForm);
			pt = pGroup->CalcTransform(xInvForm, pt);
		}
		pGroups.RemoveAt(pGroups.GetUpperBound());
	}
	BuildInverseTransform(xInvForm);
	return CalcTransform(xInvForm, pt);
}
VOID CMimicsItem::DoInverseTransformation(XFORM &xForm, CRect &rPosition) CONST
{
	CPoint  ptCenter;

	DoInverseTransformation(this, ptCenter, xForm, rPosition);
}
VOID CMimicsItem::DoInverseTransformation(CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST
{
	DoInverseTransformation(this, ptCenter, xForm, rPosition);
}
VOID CMimicsItem::DoInverseTransformation(CONST CMimicsItem *pItem, CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST
{
	XFORM  xInvForm;
	CSize  ptOffset;
	CPtrArray  pGroups;
	CMimicsItem  *pGroup;

	rPosition = pItem->GetItemPosition();
	ptCenter = pItem->GetItemCenterPoint();
	CopyMemory(&xForm, &pItem->m_xForm, sizeof(XFORM));
	for (pGroup = GetItemContainer(); pGroup; pGroup = pGroup->GetItemContainer())
	{
		pGroups.Add(pGroup);
		continue;
	}
	while (pGroups.GetSize() > 0)
	{
		if ((pGroup = (CMimicsItem *)pGroups.GetAt(pGroups.GetUpperBound())) != this)
		{
			pGroup->BuildInverseTransform(xInvForm);
			CombineTransform(&xForm, &xForm, &xInvForm);
			rPosition.OffsetRect((ptOffset = pGroup->CalcTransform(xInvForm, rPosition.CenterPoint()) - rPosition.CenterPoint()));
			ptCenter.x += ptOffset.cx;
			ptCenter.y += ptOffset.cy;
			pGroups.RemoveAt(pGroups.GetUpperBound());
			continue;
		}
		break;
	}
}

CPoint CMimicsItem::CalcTransform(CONST POINT &point) CONST
{
	return CalcTransform(m_ptCenter, m_xForm, point);
}
CPoint CMimicsItem::CalcTransform(CONST XFORM &xForm, CONST POINT &point) CONST
{
	return CalcTransform(m_ptCenter, xForm, point);
}
CPoint CMimicsItem::CalcTransform(CONST POINT &ptCenter, CONST POINT &point) CONST
{
	return CalcTransform(ptCenter, m_xForm, point);
}
CPoint CMimicsItem::CalcTransform(CONST POINT &ptCenter, CONST XFORM &xForm, CONST POINT &point) CONST
{
	POINT  pt;
	XFORM  xTransform;
	static CClientDC  cDC(NULL);

	SetGraphicsMode(cDC.GetSafeHdc(), GM_ADVANCED);
	xTransform.eM11 = xForm.eM11;
	xTransform.eM12 = xForm.eM12;
	xTransform.eM21 = xForm.eM21;
	xTransform.eM22 = xForm.eM22;
	xTransform.eDx = (float)ptCenter.x - (float)ptCenter.x*xForm.eM11 - (float)ptCenter.y*xForm.eM21;
	xTransform.eDy = (float)ptCenter.y - (float)ptCenter.x*xForm.eM12 - (float)ptCenter.y*xForm.eM22;
	SetWorldTransform(cDC.GetSafeHdc(), &xTransform);
	pt.x = point.x;
	pt.y = point.y;
	cDC.LPtoDP(&pt, 1);
	return pt;
}
CRect CMimicsItem::CalcTransform(CONST RECT &rect) CONST
{
	return CalcTransform(m_ptCenter, m_xForm, rect);
}
CRect CMimicsItem::CalcTransform(CONST XFORM &xForm, CONST RECT &rect) CONST
{
	return CalcTransform(m_ptCenter, xForm, rect);
}
CRect CMimicsItem::CalcTransform(CONST POINT &ptCenter, CONST RECT &rect) CONST
{
	return CalcTransform(ptCenter, m_xForm, rect);
}
CRect CMimicsItem::CalcTransform(CONST POINT &ptCenter, CONST XFORM &xForm, CONST RECT &rect) CONST
{
	CPoint  ptRect[4];

	ptRect[0] = CalcTransform(ptCenter, xForm, CPoint(rect.left, rect.top));
	ptRect[1] = CalcTransform(ptCenter, xForm, CPoint(rect.right, rect.top));
	ptRect[2] = CalcTransform(ptCenter, xForm, CPoint(rect.right, rect.bottom));
	ptRect[3] = CalcTransform(ptCenter, xForm, CPoint(rect.left, rect.bottom));
	return CRect(min(min(min(ptRect[0].x, ptRect[1].x), ptRect[2].x), ptRect[3].x), min(min(min(ptRect[0].y, ptRect[1].y), ptRect[2].y), ptRect[3].y), max(max(max(ptRect[0].x, ptRect[1].x), ptRect[2].x), ptRect[3].x), max(max(max(ptRect[0].y, ptRect[1].y), ptRect[2].y), ptRect[3].y));
}

VOID CMimicsItem::BuildInverseTransform(XFORM &xForm) CONST
{
	float  f;

	f = (m_xForm.eM11*m_xForm.eM22 - m_xForm.eM12*m_xForm.eM21 >= 0.0) ? (float) 1.0 : (float)-1.0;
	xForm.eM11 = f*m_xForm.eM22;
	xForm.eM22 = f*m_xForm.eM11;
	xForm.eM12 = -f*m_xForm.eM12;
	xForm.eM21 = -f*m_xForm.eM21;
	xForm.eDx = -m_xForm.eDx;
	xForm.eDy = -m_xForm.eDy;
}

BOOL CMimicsItem::Draw(CDC *pDC, BOOL bShape)
{
	CRect  rItem;
	XFORM  xForm;
	CPoint  ptCenter;
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (cMimicsItem.IsVisible() || bShape)
		{
			DoTransformation(ptCenter, xForm, rItem);
			xForm.eDx = (float)ptCenter.x;
			xForm.eDy = (float)ptCenter.y;
			cMimicsItem.Draw(pDC->GetSafeHdc(), rItem, &xForm, bShape);
			return TRUE;
		}
	}
	return FALSE;
}

VOID CMimicsItem::DrawItem()
{
	DrawItem(CalcItemFramePosition());
}
VOID CMimicsItem::DrawItem(CONST RECT &rect)
{
	CMMDImageView  *pView;

	if ((pView = (!IsLocked()) ? (CMMDImageView *)GetItemImage() : (CMMDImageView *)NULL))
	{
		if (!IsRectEmpty(&rect) && IsItemVisible())
		{
			pView->DrawImage(rect);
			return;
		}
		if (IsItemVisible())
		{
			pView->UpdateAllItems();
			return;
		}
	}
}

VOID CMimicsItem::SetPosition(CONST RECT &rect)
{
	CRect  rItem;
	CRect  rPosition;
	CMimicsGroup  *pGroup;

	Lock();
	rItem = GetPosition();
	rPosition.SetRect(rect.left, rect.top, rect.right, rect.bottom);
	rPosition.OffsetRect(GetItemPosition().CenterPoint() - rItem.CenterPoint());
	if ((!IsItemSizeable() && (abs(rect.right - rect.left) != abs(rItem.Width()) || abs(rect.bottom - rect.top) != abs(rItem.Height()))) || rItem.EqualRect(&rect))
	{
		Unlock();
		return;
	}
	for (rItem.SetRectEmpty(); (pGroup = (CMimicsGroup *)GetItemContainer()); )
	{
		if (pGroup->Lock())
		{
			AdjustItemContainer();
			AdjustItemPosition(rPosition);
			AdjustItemContainer();
			if (IsItemActivated(TRUE))
			{
				rPosition = GetItemPosition();
				rPosition.NormalizeRect();
				SetItemRects(rPosition);
			}
			SetItemSize(abs(rect.right - rect.left), abs(rect.bottom - rect.top));
			pGroup->Unlock();
		}
		Unlock();
		break;
	}
	if (!pGroup)
	{
		for (AdjustItemPosition(rPosition); IsItemActivated(TRUE); )
		{
			rPosition = GetItemPosition();
			rPosition.NormalizeRect();
			SetItemRects(rPosition);
			break;
		}
		SetItemSize(abs(rect.right - rect.left), abs(rect.bottom - rect.top));
		Unlock();
	}
	DrawItem(rItem);
}

CRect CMimicsItem::GetPosition() CONST
{
	CRect  rItem;
	XFORM  xForm;

	DoTransformation(xForm, rItem);
	return rItem;
}

VOID CMimicsItem::FlipHorizontal()
{
	CRect  rItem;
	XFORM  xForm;
	CMimicsGroup  *pGroup;

	Lock();
	AdjustItemContainer();
	AdjustItemCenterPoint();
	for (rItem.SetRectEmpty(); (pGroup = (CMimicsGroup *)GetItemContainer()); )
	{
		if (pGroup->Lock())
		{
			xForm.eM11 = -1.0;
			xForm.eM21 = 0.0;
			xForm.eM12 = 0.0;
			xForm.eM22 = 1.0;
			xForm.eDx = 0.0;
			xForm.eDy = 0.0;
			CombineTransform(&m_xForm, &m_xForm, &xForm);
			pGroup->Unlock();
		}
		Unlock();
		break;
	}
	if (!pGroup)
	{
		xForm.eM11 = -1.0;
		xForm.eM21 = 0.0;
		xForm.eM12 = 0.0;
		xForm.eM22 = 1.0;
		xForm.eDx = 0.0;
		xForm.eDy = 0.0;
		CombineTransform(&m_xForm, &m_xForm, &xForm);
		Unlock();
	}
	DrawItem(rItem);
}

VOID CMimicsItem::FlipVertical()
{
	CRect  rItem;
	XFORM  xForm;
	CMimicsGroup  *pGroup;

	Lock();
	AdjustItemContainer();
	AdjustItemCenterPoint();
	for (rItem.SetRectEmpty(); (pGroup = (CMimicsGroup *)GetItemContainer()); )
	{
		if (pGroup->Lock())
		{
			xForm.eM11 = 1.0;
			xForm.eM21 = 0.0;
			xForm.eM12 = 0.0;
			xForm.eM22 = -1.0;
			xForm.eDx = 0.0;
			xForm.eDy = 0.0;
			CombineTransform(&m_xForm, &m_xForm, &xForm);
			pGroup->Unlock();
		}
		Unlock();
		break;
	}
	if (!pGroup)
	{
		xForm.eM11 = 1.0;
		xForm.eM21 = 0.0;
		xForm.eM12 = 0.0;
		xForm.eM22 = -1.0;
		xForm.eDx = 0.0;
		xForm.eDy = 0.0;
		CombineTransform(&m_xForm, &m_xForm, &xForm);
		Unlock();
	}
	DrawItem(rItem);
}

VOID CMimicsItem::Rotate(double fAngle)
{
	CRect  rItem;
	XFORM  xForm;
	CMimicsGroup  *pGroup;

	Lock();
	AdjustItemContainer();
	AdjustItemCenterPoint();
	for (rItem.SetRectEmpty(); (pGroup = (CMimicsGroup *)GetItemContainer()); )
	{
		if (pGroup->Lock())
		{
			fAngle = (fmod(fAngle, 360.0)*2.0*M_PI) / 360.0;
			xForm.eM11 = (float)cos(fAngle);
			xForm.eM21 = (float)sin(fAngle);
			xForm.eM12 = (float)-sin(fAngle);
			xForm.eM22 = (float)cos(fAngle);
			xForm.eDx = xForm.eDy = 0.0;
			CombineTransform(&m_xForm, &m_xForm, &xForm);
			pGroup->Unlock();
		}
		Unlock();
		break;
	}
	if (!pGroup)
	{
		fAngle = (fmod(fAngle, 360.0)*2.0*M_PI) / 360.0;
		xForm.eM11 = (float)cos(fAngle);
		xForm.eM21 = (float)sin(fAngle);
		xForm.eM12 = (float)-sin(fAngle);
		xForm.eM22 = (float)cos(fAngle);
		xForm.eDx = xForm.eDy = 0.0;
		CombineTransform(&m_xForm, &m_xForm, &xForm);
		Unlock();
	}
	DrawItem(rItem);
}

BOOL CMimicsItem::HasProperties() CONST
{
	return TRUE;
}

BOOL CMimicsItem::MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin)
{
	return TRUE;
}

BOOL CMimicsItem::UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin)
{
	return TRUE;
}

VOID CMimicsItem::InitializeProperties()
{
	return;
}

VOID CMimicsItem::UpdateProperties()
{
	SetItemVisibility(m_bVisible);
}

BOOL CMimicsItem::IsUpdatingProperties() CONST
{
	return m_bProperties;
}

VOID CMimicsItem::ResetState()
{
	return;
}

BOOL CMimicsItem::Copy(CONST CMimicsItem *pItem, BOOL bAll)
{
	m_clsid = pItem->GetItemClassID();
	m_szName = pItem->GetItemName();
	m_szType = pItem->GetItemType();
	m_szLink = pItem->GetItemLink();
	m_szText = pItem->GetItemToolTipText();
	m_bVisible = pItem->IsItemVisible();
	m_bSelected = (bAll) ? pItem->m_bSelected : m_bSelected;
	m_bActivated = (bAll) ? pItem->m_bActivated : m_bActivated;
	m_rPosition[0] = pItem->m_rPosition[0];
	m_rPosition[1] = pItem->m_rPosition[1];
	m_ptCenter = pItem->m_ptCenter;
	CopyMemory(&m_xForm, &pItem->m_xForm, sizeof(XFORM));
	m_nInfo.Copy(pItem->m_nInfo);
	return TRUE;
}

BOOL CMimicsItem::Compare(CONST CMimicsItem *pItem, BOOL bAll) CONST
{
	return((pItem->GetItemClassID() == GetItemClassID() && pItem->GetItemName() == GetItemName() && pItem->GetItemType() == GetItemType() && pItem->GetItemLink() == GetItemLink() && pItem->GetItemToolTipText() == GetItemToolTipText() && pItem->IsItemVisible() == IsItemVisible() && (!bAll || (pItem->m_bSelected == m_bSelected  &&  pItem->m_bActivated == m_bActivated)) && pItem->m_rPosition[0] == m_rPosition[0] && pItem->m_rPosition[1] == m_rPosition[1] && pItem->m_ptCenter == m_ptCenter  &&  !memcmp(&pItem->m_xForm, &m_xForm, sizeof(XFORM)) && pItem->m_nInfo.GetSize() == m_nInfo.GetSize() && !memcmp(pItem->m_nInfo.GetData(), m_nInfo.GetData(), m_nInfo.GetSize())) ? TRUE : FALSE);
}

BOOL CMimicsItem::Map(CMMDLayoutItem *pItem, CONST POINT &ptOrigin)
{
	CRect  rPosition;

	if (MapProperties(m_nInfo, ptOrigin))
	{
		rPosition = GetItemPosition();
		rPosition.OffsetRect(-ptOrigin.x, 0);
		rPosition.OffsetRect(0, -ptOrigin.y);
		pItem->SetClassID(GetItemClassID());
		pItem->SetName(GetItemName());
		pItem->SetType(GetItemType());
		pItem->SetLink(GetItemLink());
		pItem->SetPosition(rPosition);
		pItem->SetVisible(GetItemVisibility());
		pItem->SetToolTipText(GetItemToolTipText());
		pItem->SetTransformation(m_xForm);
		pItem->SetProperties(m_nInfo);
		return TRUE;
	}
	return FALSE;
}
BOOL CMimicsItem::Map(CByteArray &nData)
{
	CPoint  ptOrigin(0, 0);

	return Map(nData, ptOrigin);
}
BOOL CMimicsItem::Map(CByteArray &nData, CONST POINT &ptOrigin)
{
	CMMDLayoutItem  cLayoutItem;

	return((Map(&cLayoutItem, ptOrigin) && cLayoutItem.Map(nData)) ? TRUE : FALSE);
}

BOOL CMimicsItem::Unmap(CONST CMMDLayoutItem *pItem, CONST POINT &ptOrigin)
{
	CRect  rPosition;

	rPosition = pItem->GetPosition();
	rPosition.OffsetRect(ptOrigin);
	SetItemClassID(pItem->GetClassID());
	SetItemName(pItem->GetName());
	SetItemType(pItem->GetType());
	SetItemLink(pItem->GetLink());
	SetItemPosition(rPosition);
	SetItemVisibility(pItem->IsVisible());
	SetItemToolTipText(pItem->GetToolTipText());
	SetItemCenterPoint(rPosition.CenterPoint());
	pItem->GetTransformation(m_xForm);
	pItem->GetProperties(m_nInfo);
	return UnmapProperties(m_nInfo, ptOrigin);
}
BOOL CMimicsItem::Unmap(CONST CByteArray &nData)
{
	CPoint  ptOrigin(0, 0);

	return Unmap(nData, ptOrigin);
}
BOOL CMimicsItem::Unmap(CONST CByteArray &nData, CONST POINT &ptOrigin)
{
	CMMDLayoutItem  cLayoutItem;

	return((cLayoutItem.Unmap(nData) && Unmap(&cLayoutItem, ptOrigin)) ? TRUE : FALSE);
}

BOOL CMimicsItem::Lock()
{
	return((InterlockedIncrement(&m_bLocked) > 0) ? TRUE : FALSE);
}

BOOL CMimicsItem::IsLocked() CONST
{
	return((m_bLocked > 0) ? TRUE : FALSE);
}

BOOL CMimicsItem::Unlock()
{
	if (InterlockedDecrement(&m_bLocked) < 0)
	{
		InterlockedIncrement(&m_bLocked);
		return FALSE;
	}
	return TRUE;
}

void CMimicsItem::Release(OLECLOSE dwCloseOption)
{
	if (!m_bOriginal)
	{
		m_lpObject = (LPOLEOBJECT)NULL;
		m_lpViewObject = (LPVIEWOBJECT2)NULL;
	}
	CMimicsClientItem::Release(dwCloseOption);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::QueryInterface(REFIID iid, LPVOID *ppvObj)
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(ULONG) CMimicsItem::XOleInPlaceSiteWindowless::AddRef()
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CMimicsItem::XOleInPlaceSiteWindowless::Release()
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->ExternalRelease();
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::GetWindow(HWND *phWnd)
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.GetWindow(phWnd);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::ContextSensitiveHelp(BOOL bEnter)
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.ContextSensitiveHelp(bEnter);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::GetWindowContext(IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT prectPos, LPRECT prectClip, LPOLEINPLACEFRAMEINFO pFrameInfo)
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.GetWindowContext(ppFrame, ppDoc, prectPos, prectClip, pFrameInfo);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::CanWindowlessActivate()
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return S_OK;
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::CanInPlaceActivate()
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.CanInPlaceActivate();
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::RequestUIActivate()
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return S_OK;
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::DeactivateAndUndo()
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.DeactivateAndUndo();
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::DiscardUndoState()
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.DiscardUndoState();
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::Scroll(SIZE sizeExtent)
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.Scroll(sizeExtent);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::SetCapture(BOOL bCapture)
{
	CMMDImageView  *pView;
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return(((pView = (CMMDImageView *)pThis->GetActiveView())) ? ((bCapture) ? pView->SetCaptureOnItem(pThis) : pView->ReleaseCaptureFromItem(pThis)) : E_FAIL);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::GetCapture()
{
	CMMDImageView  *pView;
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return(((pView = (CMMDImageView *)pThis->GetActiveView())) ? ((pView->GetItemWithCapture() == pThis) ? S_OK : S_FALSE) : S_FALSE);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::SetFocus(BOOL bFocus)
{
	CMMDImageView  *pView;
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless);

	return(((pView = (CMMDImageView *)pThis->GetActiveView())) ? ((bFocus) ? pView->SetFocusOnItem(pThis) : pView->ReleaseFocusFromItem(pThis)) : E_FAIL);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::GetFocus()
{
	CMMDImageView  *pView;
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return(((pView = (CMMDImageView *)pThis->GetActiveView())) ? ((pView->GetItemWithFocus() == pThis) ? S_OK : S_FALSE) : S_FALSE);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::GetDC(LPCRECT prect, DWORD dwFlags, HDC *phDC)
{
	CRgn  rgItem;
	CRect  rItem;
	CView  *pView;
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		if ((pThis->m_pDC = ((pView = (!pThis->m_pDC) ? pThis->GetActiveView() : (CView *)NULL)) ? pView->GetDC() : (CDC *)NULL))
		{
			if (rgItem.CreateRectRgnIndirect((rItem = (prect) ? ((rItem.IntersectRect(pThis->GetItemPosition(), prect)) ? rItem : CRect(0, 0, 0, 0)) : pThis->GetItemPosition())))
			{
				if (pThis->m_pDC->SelectClipRgn(&rgItem, RGN_AND) != ERROR)
				{
					*phDC = pThis->m_pDC->GetSafeHdc();
					return S_OK;
				}
			}
			pView->ReleaseDC(pThis->m_pDC);
			pThis->m_pDC = (CDC *)NULL;
		}
	return E_FAIL;
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::ReleaseDC(HDC hDC)
{
	CView  *pView;
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		if ((pView = pThis->GetActiveView()))
		{
			if (pThis->m_pDC->GetSafeHdc() == hDC)
			{
				pView->ReleaseDC(pThis->m_pDC);
				pThis->m_pDC = (CDC *)NULL;
				return S_OK;
			}
		}
	return E_FAIL;
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::InvalidateRect(LPCRECT prect, BOOL bErase)
{
	CRect  rItem;
	CView  *pView;
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		if ((pView = pThis->GetActiveView()))
		{
			if (!AfxIsValidAddress(prect, sizeof(RECT), FALSE))
			{
				pView->InvalidateRect(prect, bErase);
				return S_OK;
			}
			rItem.SetRect(prect->left - pView->GetScrollPos(SB_HORZ), prect->top - pView->GetScrollPos(SB_VERT), prect->right - pView->GetScrollPos(SB_HORZ), prect->bottom - pView->GetScrollPos(SB_VERT));
			pView->InvalidateRect(rItem, bErase);
			return S_OK;
		}
	return E_FAIL;
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::InvalidateRgn(HRGN hRgn, BOOL bErase)
{
	CRgn  *rgItem;
	CView  *pView;
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		if ((pView = pThis->GetActiveView()))
		{
			if ((rgItem = CRgn::FromHandle(hRgn)))
			{
				rgItem->OffsetRgn(-pView->GetScrollPos(SB_HORZ), 0);
				rgItem->OffsetRgn(0, -pView->GetScrollPos(SB_VERT));
				pView->InvalidateRgn(rgItem, bErase);
				return S_OK;
			}
		}
	return E_FAIL;
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::AdjustRect(LPRECT prect)
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return E_NOTIMPL;
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::ScrollRect(int dx, int dy, LPCRECT prectScroll, LPCRECT prectClip)
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return E_NOTIMPL;
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::OnInPlaceActivate()
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.OnInPlaceActivate();
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::OnInPlaceDeactivate()
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.OnInPlaceDeactivate();
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::OnInPlaceActivateEx(BOOL *pbNoRedraw, DWORD dwFlags)
{
	BOOL  bNoRedraw;
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		if ((dwFlags & ACTIVATE_WINDOWLESS) != ACTIVATE_WINDOWLESS)
		{
			CopyMemory(pbNoRedraw, &(bNoRedraw = !pThis->GetActiveView()->GetUpdateRect((LPRECT)NULL)), (pbNoRedraw) ? sizeof(BOOL) : 0);
			return pThis->m_xOleIPSite.OnInPlaceActivate();
		}
	return((pThis->m_lpObject->QueryInterface(IID_IOleInPlaceObjectWindowless, (LPVOID *)&pThis->m_pOleInPlaceObjectWindowless) == S_OK) ? pThis->m_xOleIPSite.OnInPlaceActivate() : E_FAIL);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::OnInPlaceDeactivateEx(BOOL bNoRedraw)
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		pThis->OnDeactivate();
	return S_OK;
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::OnUIActivate()
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.OnUIActivate();
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::OnUIDeactivate(BOOL bUndoable)
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.OnUIDeactivate(bUndoable);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::OnPosRectChange(LPCRECT prectPos)
{
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return pThis->m_xOleIPSite.OnPosRectChange(prectPos);
}

STDMETHODIMP CMimicsItem::XOleInPlaceSiteWindowless::OnDefWindowMessage(UINT nMessage, WPARAM wParam, LPARAM lParam, LRESULT *plResult)
{
	CMMDImageView  *pView;
	METHOD_PROLOGUE(CMimicsItem, OleInPlaceSiteWindowless)

		return(((pView = (CMMDImageView *)pThis->GetActiveView())) ? pView->DefWindowMessageProc(nMessage, wParam, lParam, plResult) : E_FAIL);
}

BEGIN_INTERFACE_MAP(CMimicsItem, CMimicsClientItem)
	INTERFACE_PART(CMimicsItem, IID_IOleInPlaceSiteWindowless, OleInPlaceSiteWindowless)
END_INTERFACE_MAP()

BEGIN_MESSAGE_MAP(CMimicsItem, CMimicsClientItem)
	//{{AFX_MSG_MAP(CMimicsItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsItem commands

void CMimicsItem::OnGetClipRect(CRect &rClip)
{
	POINT  ptOrigin;
	CMMDImageView  *pView;

	if ((pView = (CMMDImageView *)GetActiveView()))
	{
		ptOrigin = pView->GetImageOrigin();
		pView->GetClientRect(rClip);
		rClip.left = ptOrigin.x + 1;
		rClip.top = ptOrigin.y + 1;
		return;
	}
	CMimicsClientItem::OnGetClipRect(rClip);
}

void CMimicsItem::OnGetItemPosition(CRect &rPosition)
{
	rPosition = GetItemPosition();
	CMimicsClientItem::OnGetItemPosition(rPosition);
}

void CMimicsItem::OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam)
{
	for (; wNotification == OLE_CHANGED; )
	{
		DrawItem();
		break;
	}
	CMimicsClientItem::OnChange(wNotification, dwParam);
}

void CMimicsItem::OnDeactivate()
{
	if (m_pOleInPlaceObjectWindowless != (LPOLEINPLACEOBJECTWINDOWLESS)NULL)
	{
		m_pOleInPlaceObjectWindowless->Release();
		AdjustItemCenterPoint();
	}
	CMimicsClientItem::OnDeactivate();
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsItems

CMimicsItems::CMimicsItems() : CPtrArray()
{
	return;
}

CMimicsItems::~CMimicsItems()
{
	RemoveAll();
}

INT CMimicsItems::Add(CMimicsItem *pMimicsItem)
{
	return((INT)CPtrArray::Add(pMimicsItem));
}

INT CMimicsItems::Find(LPCTSTR pszName) CONST
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (INT)GetSize(); nItem < nItems; nItem++)
	{
		if (GetAt(nItem)->GetItemName() == pszName) break;
		continue;
	}
	return((nItem < nItems) ? nItem : -1);
}

CMimicsItem *CMimicsItems::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMimicsItem *)CPtrArray::GetAt(nIndex) : (CMimicsItem *)NULL);
}

CMimicsItem *CMimicsItems::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMimicsItem *)CPtrArray::GetAt(nIndex) : (CMimicsItem *)NULL);
}

VOID CMimicsItems::RemoveAll()
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (INT)GetSize(); nItem < nItems; nItem++)
	{
		delete GetAt(nItem);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CMimicsItems::Copy(CONST CMimicsItems *pMimicsItems, BOOL bAll)
{
	INT  nItem;
	INT  nItems;
	CMimicsItem  *pItem;

	for (nItem = 0, nItems = (INT)pMimicsItems->GetSize(), RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = CMimicsItem::AllocateFromItem(pMimicsItems->GetAt(nItem))) != (CMimicsItem *)NULL)
		{
			if (pItem->Copy(pMimicsItems->GetAt(nItem), bAll) && Add(pItem) >= 0) continue;
			delete pItem;
		}
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CMimicsItems::Compare(CONST CMimicsItems *pMimicsItems, BOOL bAll) CONST
{
	INT  nItem;
	INT  nItems;
	CMimicsItem  *pItem;

	for (nItem = 0, nItems = (pMimicsItems->GetSize() == GetSize()) ? (INT)GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pItem = pMimicsItems->GetAt(nItem)) && pItem->Compare(GetAt(nItem), bAll)) continue;
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CMimicsItems::Map(CByteArray &nData) CONST
{
	INT  nItem;
	INT  nItems;
	CByteArray  nItemData;
	CMimicsItem  *pItem;

	for (nItem = 0, nItems = (INT)GetSize(), nData.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = GetAt(nItem)) && pItem->Map(nItemData) && nData.Append(nItemData) >= 0) continue;
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CMimicsItems::Unmap(CONST CByteArray &nData)
{
	INT  cbItem;
	INT  cbItems;
	CByteArray  nItemData;
	CMimicsItem  *pItem;

	for (cbItems = 0, RemoveAll(); cbItems < nData.GetSize(); cbItems += cbItem)
	{
		for (CopyMemory(&cbItem, nData.GetData() + cbItems, sizeof(cbItem)), nItemData.SetSize(max(min(cbItem, nData.GetSize() - cbItems), 0)); nItemData.GetSize() >= 0; )
		{
			CopyMemory(nItemData.GetData(), nData.GetData() + cbItems, nItemData.GetSize());
			break;
		}
		if ((pItem = CMimicsItem::AllocateFromData(nItemData)))
		{
			if (pItem->Unmap(nItemData) && Add(pItem) >= 0) continue;
			delete pItem;
		}
		break;
	}
	return((cbItems == nData.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineItem

IMPLEMENT_DYNCREATE(CMimicsLineItem, CMimicsItem)

CMimicsLineItem::CMimicsLineItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsLineCtrl);
	SetStyle();
	SetColor();
	SetThickness();
	Arrow();
	DoubleArrow();
	Cross();
	SetCrossPt();
}

VOID CMimicsLineItem::SetStyle(INT nStyle)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (nStyle == PS_SOLID) cMimicsLineItem.Solid();
		if (nStyle == PS_DASH) cMimicsLineItem.Dash();
		if (nStyle == PS_DOT) cMimicsLineItem.Dot();
		if (nStyle == PS_DASHDOT) cMimicsLineItem.DashDot();
		if (nStyle == PS_DASHDOTDOT) cMimicsLineItem.DashDotDot();
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsLineItem::GetStyle() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (cMimicsLineItem.IsSolid()) return PS_SOLID;
		if (cMimicsLineItem.IsDashed()) return PS_DASH;
		if (cMimicsLineItem.IsDotted()) return PS_DOT;
		if (cMimicsLineItem.IsDashDotted()) return PS_DASHDOT;
		if (cMimicsLineItem.IsDashDotDotted()) return PS_DASHDOTDOT;
	}
	return m_nStyle;
}

VOID CMimicsLineItem::Arrow(BOOL bEnable)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.Arrow(bEnable);
		return;
	}
	m_bArrow[0] = bEnable;
}

VOID CMimicsLineItem::DoubleArrow(BOOL bEnable)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.DoubleArrow(bEnable);
		return;
	}
	m_bArrow[1] = bEnable;
}

VOID CMimicsLineItem::Cross(BOOL bEnable)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.Cross(bEnable);
		return;
	}
	m_bCrossing = bEnable;
}

BOOL CMimicsLineItem::SetCrossPt(double fPt)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		m_fPtCross = fPt;
		return TRUE;
	}
	return cMimicsLineItem.SetCrossPt(fPt);
}

BOOL CMimicsLineItem::GetCrossPt(double *fPt) CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		CopyMemory(fPt, &m_fPtCross, sizeof(double));
		return IsCross();
	}
	return cMimicsLineItem.GetCrossPt(fPt);
}

BOOL CMimicsLineItem::IsArrow() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsArrow() : m_bArrow[0]);
}

BOOL CMimicsLineItem::IsDoubleArrow() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsDoubleArrow() : m_bArrow[1]);
}

BOOL CMimicsLineItem::IsCross() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsCross() : m_bCrossing);
}

VOID CMimicsLineItem::SetColor(COLORREF nColor)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.SetColor(nColor);
		return;
	}
	m_nColor = nColor;
}

COLORREF CMimicsLineItem::GetColor() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.GetColor() : m_nColor);
}

VOID CMimicsLineItem::SetThickness(INT nWidth)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.SetThickness(nWidth);
		return;
	}
	m_nWidth = nWidth;
}

INT CMimicsLineItem::GetThickness() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.GetThickness() : m_nWidth);
}

VOID CMimicsLineItem::Solid()
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.Solid();
		return;
	}
	m_nStyle = PS_SOLID;
}

VOID CMimicsLineItem::Dash()
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.Dash();
		return;
	}
	m_nStyle = PS_DASH;
}

VOID CMimicsLineItem::Dot()
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.Dot();
		return;
	}
	m_nStyle = PS_DOT;
}

VOID CMimicsLineItem::DashDot()
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.DashDot();
		return;
	}
	m_nStyle = PS_DASHDOT;
}

VOID CMimicsLineItem::DashDotDot()
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.DashDotDot();
		return;
	}
	m_nStyle = PS_DASHDOTDOT;
}

BOOL CMimicsLineItem::IsSolid() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsSolid() : ((m_nStyle == PS_SOLID) ? TRUE : FALSE));
}

BOOL CMimicsLineItem::IsDashed() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsDashed() : ((m_nStyle == PS_DASH) ? TRUE : FALSE));
}

BOOL CMimicsLineItem::IsDotted() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsDotted() : ((m_nStyle == PS_DOT) ? TRUE : FALSE));
}

BOOL CMimicsLineItem::IsDashDotted() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsDashDotted() : ((m_nStyle == PS_DASHDOT) ? TRUE : FALSE));
}

BOOL CMimicsLineItem::IsDashDotDotted() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsDashDotDotted() : ((m_nStyle == PS_DASHDOTDOT) ? TRUE : FALSE));
}

VOID CMimicsLineItem::SetItemPosition(CONST RECT &rect)
{
	CRect  rPosition;

	rPosition = rect;
	rPosition.OffsetRect(GetPosition().CenterPoint() - GetItemPosition().CenterPoint());
	SetPosition(rPosition);
}

CRect CMimicsLineItem::GetItemPosition() CONST
{
	return m_rPosition[0];
}
VOID CMimicsLineItem::GetItemPosition(CPoint &point, CSize &size) CONST
{
	CRect  rItem;
	CPoint  ptItem[2];

	rItem = GetItemPosition();
	ptItem[0] = CalcTransform(rItem.TopLeft());
	ptItem[1] = CalcTransform(rItem.BottomRight());
	size.cx = max(ptItem[0].x, ptItem[1].x) - min(ptItem[0].x, ptItem[1].x);
	size.cy = max(ptItem[0].y, ptItem[1].y) - min(ptItem[0].y, ptItem[1].y);
	point.x = (ptItem[0].x + ptItem[1].x) / 2;
	point.y = (ptItem[0].y + ptItem[1].y) / 2;
}

VOID CMimicsLineItem::DragItem(UINT nCode, CONST POINT &ptNew, CONST POINT &ptOld)
{
	CRect  rItem;
	CPoint  point;
	double  fPtCross[2];

	rItem = GetItemPosition();
	point = DoInverseTransformation(ptNew);
	if (abs(rItem.Width()) >= abs(rItem.Height()) && abs(rItem.Width()) != 0)
	{
		fPtCross[0] = fabs((double)MIMICSITEM_THUMB_SIZE) / fabs((double)rItem.Width());
		fPtCross[1] = fabs((double)(point.x - rItem.left)) / fabs((double)rItem.Width());
		fPtCross[1] = (fPtCross[1] < fPtCross[0]) ? fPtCross[0] : fPtCross[1];
		fPtCross[1] = (fPtCross[1] > 1.0 - fPtCross[0]) ? (1.0 - fPtCross[0]) : fPtCross[1];
		fPtCross[1] = ((point.x < rItem.left  &&  rItem.Width() > 0) || (point.x > rItem.left  &&  rItem.Width() < 0)) ? fPtCross[0] : fPtCross[1];
		SetCrossPt(fPtCross[1]);
		return;
	}
	if (abs(rItem.Height()) != 0)
	{
		fPtCross[0] = fabs((double)MIMICSITEM_THUMB_SIZE) / fabs((double)rItem.Height());
		fPtCross[1] = fabs((double)(point.y - rItem.top)) / fabs((double)rItem.Height());
		fPtCross[1] = (fPtCross[1] < fPtCross[0]) ? fPtCross[0] : fPtCross[1];
		fPtCross[1] = (fPtCross[1] > 1.0 - fPtCross[0]) ? (1.0 - fPtCross[0]) : fPtCross[1];
		fPtCross[1] = ((point.y < rItem.top  &&  rItem.Height() > 0) || (point.y > rItem.top  &&  rItem.Height() < 0)) ? fPtCross[0] : fPtCross[1];
		SetCrossPt(fPtCross[1]);
		return;
	}
}

BOOL CMimicsLineItem::DrawItemFrame(CDC *pDC, CONST RECT &rect)
{
	INT  nThumb;
	INT  nThumbs;
	CPen  *pOldPen;
	CPen  cThumbPen;
	CBrush  brThumb[2];
	CBrush  *pOldBrush[2];
	RECT  rThumbs[MIAC_THUMBS];

	if (IsItemActivated(TRUE))
	{
		if (GetItemRotateMode())
		{
			if (cThumbPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME)))
			{
				if (brThumb[0].CreateSolidBrush(GetSysColor(COLOR_3DFACE)))
				{
					if ((pOldPen = (CPen *)pDC->SelectObject(&cThumbPen)))
					{
						if ((pOldBrush[0] = (CBrush *)pDC->SelectObject(&brThumb[0])))
						{
							for (nThumb = 0, nThumbs = CalcItemFrameTurnThumbPositions(rect, rThumbs, sizeof(rThumbs) / sizeof(rThumbs[0])); nThumb < nThumbs; nThumb++)
							{
								if (!IsRectEmpty(&rThumbs[nThumb])) pDC->Ellipse(&rThumbs[nThumb]);
								continue;
							}
							pDC->SelectObject(pOldBrush[0]);
						}
						pDC->SelectObject(pOldPen);
					}
					brThumb[0].DeleteObject();
				}
				cThumbPen.DeleteObject();
			}
			return TRUE;
		}
		if (cThumbPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME)))
		{
			if (brThumb[0].CreateSolidBrush(GetSysColor(COLOR_3DFACE)))
			{
				if ((pOldPen = (CPen *)pDC->SelectObject(&cThumbPen)))
				{
					if ((pOldBrush[0] = (CBrush *)pDC->SelectObject(&brThumb[0])))
					{
						for (nThumb = 0, nThumbs = CalcItemFrameThumbPositions(rect, rThumbs, sizeof(rThumbs) / sizeof(rThumbs[0])); nThumb < nThumbs; nThumb++)
						{
							if (!IsRectEmpty(&rThumbs[nThumb])) pDC->Rectangle(&rThumbs[nThumb]);
							continue;
						}
						if (CalcItemFrameCrossThumbPosition(rect, &rThumbs[0]))
						{
							if (brThumb[1].CreateSolidBrush(VGA_COLOR_LTYELLOW))
							{
								if ((pOldBrush[1] = (CBrush *)pDC->SelectObject(&brThumb[1])))
								{
									pDC->Rectangle(&rThumbs[0]);
									pDC->SelectObject(pOldBrush[1]);
								}
								brThumb[1].DeleteObject();
							}
						}
						pDC->SelectObject(pOldBrush[0]);
					}
					pDC->SelectObject(pOldPen);
				}
				brThumb[0].DeleteObject();
			}
			cThumbPen.DeleteObject();
		}
		return TRUE;
	}
	return CMimicsItem::DrawItemFrame(pDC, rect);
}

BOOL CMimicsLineItem::DrawItemDraggingFrame(CDC *pDC, CONST RECT &rect)
{
	INT  nMode;
	CPen  *pOldPen;
	CPen  cFramePen;
	POINT  point[4];

	CalcItemFrameOutlinePoints(rect, point, sizeof(point) / sizeof(point[0]));
	if (cFramePen.CreatePen(PS_DOT, 1, GetSysColor(COLOR_WINDOWFRAME)))
	{
		if ((pOldPen = (CPen *)pDC->SelectObject(&cFramePen)))
		{
			nMode = pDC->SetROP2(R2_MASKNOTPEN);
			pDC->MoveTo(point[0]);
			pDC->LineTo(point[1]);
			pDC->LineTo(point[2]);
			pDC->LineTo(point[3]);
			pDC->LineTo(point[0]);
			pDC->SetROP2(nMode);
			pDC->SelectObject(pOldPen);
			cFramePen.DeleteObject();
			return TRUE;
		}
		cFramePen.DeleteObject();
	}
	return FALSE;
}

CRect CMimicsLineItem::CalcItemFrameExtent() CONST
{
	CPoint  ptItem[2];

	ptItem[0] = DoTransformation(GetItemPosition().TopLeft());
	ptItem[1] = DoTransformation(GetItemPosition().BottomRight());
	return CRect(min(ptItem[0].x, ptItem[1].x), min(ptItem[0].y, ptItem[1].y), max(ptItem[0].x, ptItem[1].x), max(ptItem[0].y, ptItem[1].y));
}

CRect CMimicsLineItem::CalcItemFramePosition() CONST
{
	CRect  rFrame;
	POINT  point[4];
	CPoint  ptFrame[2];

	ptFrame[0] = CalcTransform(GetItemPosition().TopLeft());
	ptFrame[1] = CalcTransform(GetItemPosition().BottomRight());
	CalcItemFrameOutlinePoints(GetItemPosition(), point, sizeof(point) / sizeof(point[0]));
	rFrame.left = min(min(min(min(min(ptFrame[0].x, ptFrame[1].x), point[0].x), point[1].x), point[2].x), point[3].x);
	rFrame.top = min(min(min(min(min(ptFrame[0].y, ptFrame[1].y), point[0].y), point[1].y), point[2].y), point[3].y);
	rFrame.right = max(max(max(max(max(ptFrame[0].x, ptFrame[1].x), point[0].x), point[1].x), point[2].x), point[3].x);
	rFrame.bottom = max(max(max(max(max(ptFrame[0].y, ptFrame[1].y), point[0].y), point[1].y), point[2].y), point[3].y);
	rFrame.InflateRect((GetItemRotateMode()) ? (MIMICSITEM_THUMB_SIZE / 2 + 1) : (MIMICSITEM_THUMB_SIZE / 2), (GetItemRotateMode()) ? (MIMICSITEM_THUMB_SIZE / 2 + 1) : (MIMICSITEM_THUMB_SIZE / 2));
	rFrame.InflateRect(0, 0, 1, 1);
	return rFrame;
}

CRect CMimicsLineItem::CalcItemFrameThumbPosition(UINT nCode, CONST RECT &rect) CONST
{
	CPoint  ptThumb;

	switch (nCode)
	{
	case MIAC_FIRSTTHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.left, rect.top));
	break;
	}
	case MIAC_LASTTHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.right, rect.bottom));
	break;
	}
	}
	return((nCode == MIAC_FIRSTTHUMB || nCode == MIAC_LASTTHUMB) ? CRect(ptThumb.x - MIMICSITEM_THUMB_SIZE / 2, ptThumb.y - MIMICSITEM_THUMB_SIZE / 2, ptThumb.x + MIMICSITEM_THUMB_SIZE / 2, ptThumb.y + MIMICSITEM_THUMB_SIZE / 2) : CRect(0, 0, 0, 0));
}

INT CMimicsLineItem::CalcItemFrameThumbPositions(CONST RECT &rect, LPRECT prThumbs, INT nThumbs) CONST
{
	CRect  rThumb;

	if (nThumbs > 0) SetRect(&prThumbs[0], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameThumbPosition(MIAC_FIRSTTHUMB, rect)).bottom);
	if (nThumbs > 1) SetRect(&prThumbs[1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameThumbPosition(MIAC_LASTTHUMB, rect)).bottom);
	return((nThumbs > 0) ? min(nThumbs, 2) : 2);
}

CRect CMimicsLineItem::CalcItemFrameTurnThumbPosition(UINT nCode, CONST RECT &rect) CONST
{
	CPoint  ptThumb;

	switch (nCode)
	{
	case MIAC_FIRSTTHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.left, rect.top));
	break;
	}
	case MIAC_LASTTHUMB:
	{ ptThumb = DoTransformation(CPoint(rect.right, rect.bottom));
	break;
	}
	}
	return((nCode == MIAC_FIRSTTHUMB || nCode == MIAC_LASTTHUMB) ? CRect(ptThumb.x - MIMICSITEM_THUMB_SIZE / 2 - 1, ptThumb.y - MIMICSITEM_THUMB_SIZE / 2 - 1, ptThumb.x + MIMICSITEM_THUMB_SIZE / 2, ptThumb.y + MIMICSITEM_THUMB_SIZE / 2) : CRect(0, 0, 0, 0));
}

INT CMimicsLineItem::CalcItemFrameTurnThumbPositions(CONST RECT &rect, LPRECT prThumbs, INT nThumbs) CONST
{
	CRect  rThumb;

	if (nThumbs > 0) SetRect(&prThumbs[0], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameTurnThumbPosition(MIAC_FIRSTTHUMB, rect)).bottom);
	if (nThumbs > 1) SetRect(&prThumbs[1], rThumb.left, rThumb.top, rThumb.right, (rThumb = CalcItemFrameTurnThumbPosition(MIAC_LASTTHUMB, rect)).bottom);
	return((nThumbs > 0) ? min(nThumbs, 2) : 2);
}

INT CMimicsLineItem::CalcItemFrameOutlinePoints(CONST RECT &rect, LPPOINT pPoints, INT nPoints) CONST
{
	INT  dx[2];
	INT  dy[2];
	INT  nWidth;
	CPoint  pt[2];
	CPoint  ptFrame[4];

	if (nPoints > 0)
	{
		pt[0] = DoTransformation(CPoint(rect.left, rect.top));
		pt[1] = DoTransformation(CPoint(rect.right, rect.bottom));
		nWidth = max(GetThickness() / 2 + 1 + 1, MIMICSITEM_THUMB_SIZE / 2);
		if ((dx[0] = pt[1].x - pt[0].x) == 0)
		{
			ptFrame[0].x = pt[0].x - nWidth;
			ptFrame[1].x = pt[0].x + nWidth;
			ptFrame[2].x = pt[1].x + nWidth;
			ptFrame[3].x = pt[1].x - nWidth;
			ptFrame[0].y = pt[0].y;
			ptFrame[1].y = pt[0].y;
			ptFrame[2].y = pt[1].y;
			ptFrame[3].y = pt[1].y;
		}
		if ((dy[0] = pt[1].y - pt[0].y) == 0)
		{
			ptFrame[0].x = (dx[0]) ? pt[0].x : ptFrame[0].x;
			ptFrame[1].x = (dx[0]) ? pt[1].x : ptFrame[1].x;
			ptFrame[2].x = (dx[0]) ? pt[1].x : ptFrame[2].x;
			ptFrame[3].x = (dx[0]) ? pt[0].x : ptFrame[3].x;
			ptFrame[0].y = pt[0].y - nWidth;
			ptFrame[1].y = pt[1].y - nWidth;
			ptFrame[2].y = pt[1].y + nWidth;
			ptFrame[3].y = pt[0].y + nWidth;
		}
		if (dx[0] != 0 && dy[0] != 0)
		{
			dx[1] = (INT)((double)(nWidth + 1) / sqrt(1.0 + ((double)dx[0] * (double)dx[0]) / ((double)dy[0] * (double)dy[0])));
			dy[1] = (INT)((-(double)dx[0] / (double)dy[0] * (double)(nWidth + 1)) / sqrt(1.0 + ((double)dx[0] * (double)dx[0]) / ((double)dy[0] * (double)dy[0])));
			ptFrame[0].x = pt[0].x - dx[1];
			ptFrame[1].x = pt[1].x - dx[1];
			ptFrame[2].x = pt[1].x + dx[1];
			ptFrame[3].x = pt[0].x + dx[1];
			ptFrame[0].y = pt[0].y - dy[1];
			ptFrame[1].y = pt[1].y - dy[1];
			ptFrame[2].y = pt[1].y + dy[1];
			ptFrame[3].y = pt[0].y + dy[1];
		}
		if (nPoints > 0) pPoints[0] = ptFrame[0];
		if (nPoints > 1) pPoints[1] = ptFrame[1];
		if (nPoints > 2) pPoints[2] = ptFrame[2];
		if (nPoints > 3) pPoints[3] = ptFrame[3];
	}
	return((nPoints > 0) ? ((nPoints >= 4) ? min(nPoints, 4) : 0) : 4);
}

BOOL CMimicsLineItem::CalcItemFrameCrossThumbPosition(CONST RECT &rect, LPRECT prThumb) CONST
{
	CPoint  point;
	double  fPtCross;

	if (GetCrossPt(&fPtCross))
	{
		point.x = (INT)(rect.left + (rect.right - rect.left)*fPtCross);
		point.y = (INT)(rect.top + (rect.bottom - rect.top)*fPtCross);
		point = DoTransformation(point);
		SetRect(prThumb, point.x - MIMICSITEM_THUMB_SIZE / 2, point.y - MIMICSITEM_THUMB_SIZE / 2, point.x + MIMICSITEM_THUMB_SIZE / 2, point.y + MIMICSITEM_THUMB_SIZE / 2);
		return TRUE;
	}
	return FALSE;
}

UINT CMimicsLineItem::CheckPointOnItem(CONST POINT &ptPosition)
{
	CRect  rItem;
	CRect  rThumb;

	if (IsItemActivated(TRUE))
	{
		if (GetItemRotateMode())
		{
			if (CalcItemFrameTurnThumbPosition(MIAC_FIRSTTHUMB, (rItem = GetItemPosition())).PtInRect(ptPosition)) return MIAC_FIRSTTHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_LASTTHUMB, rItem).PtInRect(ptPosition)) return MIAC_LASTTHUMB;
		}
		else
		{
			if (CalcItemFrameThumbPosition(MIAC_FIRSTTHUMB, (rItem = GetItemPosition())).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_FIRSTTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_LASTTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_LASTTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameCrossThumbPosition(GetItemPosition(), rThumb) && rThumb.PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_DRAGTHUMB : MIAC_NOWHERE);
		}
	}
	return((CheckPointInsideItem(ptPosition)) ? MIAC_INSIDE : MIAC_NOWHERE);
}

BOOL CMimicsLineItem::CheckPointInsideItem(CONST POINT &ptPosition)
{
	CRgn  rgItem;
	POINT  ptItem[4];

	if (CalcItemFrameOutlinePoints(GetItemPosition(), ptItem, sizeof(ptItem) / sizeof(POINT)) > 0)
	{
		if (rgItem.CreatePolygonRgn(ptItem, sizeof(ptItem) / sizeof(POINT), WINDING))
		{
			if (!rgItem.PtInRegion(ptPosition))
			{
				rgItem.DeleteObject();
				return FALSE;
			}
			rgItem.DeleteObject();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMimicsLineItem::MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.nColor = GetColor();
	sData.nWidth = GetThickness();
	sData.bCrossing = IsCross();
	sData.bArrow[0] = IsArrow();
	sData.bArrow[1] = IsDoubleArrow();
	GetCrossPt(&sData.fPtCross);
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsLineItem::UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_nStyle = sData.nStyle;
		m_nWidth = sData.nWidth;
		m_nColor = sData.nColor;
		m_bCrossing = sData.bCrossing;
		m_bArrow[0] = sData.bArrow[0];
		m_bArrow[1] = sData.bArrow[1];
		m_fPtCross = sData.fPtCross;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsLineItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetColor(m_nColor);
	SetThickness(m_nWidth);
	Cross(m_bCrossing);
	SetCrossPt(m_fPtCross);
	Arrow(m_bArrow[0]);
	DoubleArrow(m_bArrow[1]);
	SetItemVisibility(m_bVisible);
	Unlock();
}

BOOL CMimicsLineItem::Copy(CONST CMimicsItem *pItem, BOOL bAll)
{
	CMimicsLineItem  *pLineItem = (CMimicsLineItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsLineItem)))
	{
		m_nStyle = pLineItem->GetStyle();
		m_nColor = pLineItem->GetColor();
		m_nWidth = pLineItem->GetThickness();
		m_bCrossing = pLineItem->IsCross();
		m_bArrow[0] = pLineItem->IsArrow();
		m_bArrow[1] = pLineItem->IsDoubleArrow();
		pLineItem->GetCrossPt(&m_fPtCross);
		return CMimicsItem::Copy(pItem, bAll);
	}
	return FALSE;
}

BOOL CMimicsLineItem::Compare(CONST CMimicsItem *pItem, BOOL bAll) CONST
{
	double  fPtCross[2];
	CMimicsLineItem  *pLineItem = (CMimicsLineItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsLineItem))) ? ((pLineItem->GetStyle() == GetStyle() && pLineItem->GetColor() == GetColor() && pLineItem->GetThickness() == GetThickness() && pLineItem->IsCross() == IsCross() && pLineItem->IsArrow() == IsArrow() && pLineItem->IsDoubleArrow() == IsDoubleArrow() && pLineItem->GetCrossPt(&fPtCross[0]) == GetCrossPt(&fPtCross[1]) && fPtCross[0] == fPtCross[1]) ? CMimicsItem::Compare(pItem, bAll) : FALSE) : FALSE);
}

BEGIN_MESSAGE_MAP(CMimicsLineItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsLineItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItem

IMPLEMENT_DYNCREATE(CMimicsRectangleItem, CMimicsItem)

CMimicsRectangleItem::CMimicsRectangleItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsRectangleCtrl);
	SetStyle();
	SetBorderSize();
	SetBorderStyle();
	SetBorderColor();
	SetInteriorColor();
	SetInteriorHatch();
}

VOID CMimicsRectangleItem::SetStyle(INT nStyle)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsRectangleItem::GetStyle() CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsRectangleItem.GetStyle() : m_nStyle);
}

VOID CMimicsRectangleItem::SetBorderSize(INT nSize)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetBorderSize(nSize);
		return;
	}
	m_nBorderSize = nSize;
}

INT CMimicsRectangleItem::GetBorderSize() CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsRectangleItem.GetBorderSize() : m_nBorderSize);
}

VOID CMimicsRectangleItem::SetBorderStyle(INT nStyle)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetBorderStyle(nStyle);
		return;
	}
	m_nBorderStyle = nStyle;
}

INT CMimicsRectangleItem::GetBorderStyle() CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsRectangleItem.GetBorderStyle() : m_nBorderStyle);
}

VOID CMimicsRectangleItem::SetBorderColor(COLORREF nColor)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetBorderColor(nColor);
		return;
	}
	m_nBorderColor = nColor;
}

COLORREF CMimicsRectangleItem::GetBorderColor() CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsRectangleItem.GetBorderColor() : m_nBorderColor);
}

VOID CMimicsRectangleItem::SetInteriorColor(COLORREF nColor)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetInteriorColor(nColor);
		return;
	}
	m_nInteriorColor = nColor;
}

COLORREF CMimicsRectangleItem::GetInteriorColor() CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsRectangleItem.GetInteriorColor() : m_nInteriorColor);
}

VOID CMimicsRectangleItem::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetInteriorHatch(nHatch, nColor);
		return;
	}
	m_nInteriorHatch = nHatch;
	m_nHatchColor = nColor;
}

BOOL CMimicsRectangleItem::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		nHatch = m_nInteriorHatch;
		nColor = m_nHatchColor;
		return((nHatch >= 0) ? TRUE : FALSE);
	}
	return cMimicsRectangleItem.GetInteriorHatch(nHatch, nColor);
}

BOOL CMimicsRectangleItem::MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.nBorderSize = GetBorderSize();
	sData.nBorderStyle = GetBorderStyle();
	sData.nBorderColor = GetBorderColor();
	sData.nInteriorColor = GetInteriorColor();
	GetInteriorHatch(sData.nInteriorHatch, sData.nHatchColor);
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsRectangleItem::UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_nInteriorColor = sData.nInteriorColor;
		m_nInteriorHatch = sData.nInteriorHatch;
		m_nHatchColor = sData.nHatchColor;
		m_nBorderStyle = sData.nBorderStyle;
		m_nBorderColor = sData.nBorderColor;
		m_nBorderSize = sData.nBorderSize;
		m_nStyle = sData.nStyle;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsRectangleItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetBorderSize(m_nBorderSize);
	SetBorderStyle(m_nBorderStyle);
	SetBorderColor(m_nBorderColor);
	SetInteriorColor(m_nInteriorColor);
	SetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
	SetItemVisibility(m_bVisible);
	Unlock();
}

BOOL CMimicsRectangleItem::Copy(CONST CMimicsItem *pItem, BOOL bAll)
{
	CMimicsRectangleItem  *pRectangleItem = (CMimicsRectangleItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsRectangleItem)))
	{
		m_nStyle = pRectangleItem->GetStyle();
		m_nBorderSize = pRectangleItem->GetBorderSize();
		m_nBorderStyle = pRectangleItem->GetBorderStyle();
		m_nBorderColor = pRectangleItem->GetBorderColor();
		m_nInteriorColor = pRectangleItem->GetInteriorColor();
		pRectangleItem->GetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
		return CMimicsItem::Copy(pItem, bAll);
	}
	return FALSE;
}

BOOL CMimicsRectangleItem::Compare(CONST CMimicsItem *pItem, BOOL bAll) CONST
{
	INT  nHatch[2];
	COLORREF  nHatchColor[2];
	CMimicsRectangleItem  *pRectangleItem = (CMimicsRectangleItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsRectangleItem))) ? ((pRectangleItem->GetStyle() == GetStyle() && pRectangleItem->GetBorderSize() == GetBorderSize() && pRectangleItem->GetBorderStyle() == GetBorderStyle() && pRectangleItem->GetBorderColor() == GetBorderColor() && pRectangleItem->GetInteriorColor() == GetInteriorColor() && pRectangleItem->GetInteriorHatch(nHatch[0], nHatchColor[0]) == GetInteriorHatch(nHatch[1], nHatchColor[1]) && nHatch[0] == nHatch[1] && (nHatch[0] < 0 || nHatchColor[0] == nHatchColor[1])) ? CMimicsItem::Compare(pItem, bAll) : FALSE) : FALSE);
}

BEGIN_MESSAGE_MAP(CMimicsRectangleItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsRectangleItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItem

IMPLEMENT_DYNCREATE(CMimicsEllipseItem, CMimicsItem)

CMimicsEllipseItem::CMimicsEllipseItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsEllipseCtrl);
	SetStyle();
	SetBorderSize();
	SetBorderStyle();
	SetBorderColor();
	SetInteriorColor();
	SetInteriorHatch();
}

VOID CMimicsEllipseItem::SetStyle(INT nStyle)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsEllipseItem::GetStyle() CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsEllipseItem.GetStyle() : m_nStyle);
}

VOID CMimicsEllipseItem::SetBorderSize(INT nSize)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetBorderSize(nSize);
		return;
	}
	m_nBorderSize = nSize;
}

INT CMimicsEllipseItem::GetBorderSize() CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsEllipseItem.GetBorderSize() : m_nBorderSize);
}

VOID CMimicsEllipseItem::SetBorderStyle(INT nStyle)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetBorderStyle(nStyle);
		return;
	}
	m_nBorderStyle = nStyle;
}

INT CMimicsEllipseItem::GetBorderStyle() CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsEllipseItem.GetBorderStyle() : m_nBorderStyle);
}

VOID CMimicsEllipseItem::SetBorderColor(COLORREF nColor)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetBorderColor(nColor);
		return;
	}
	m_nBorderColor = nColor;
}

COLORREF CMimicsEllipseItem::GetBorderColor() CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsEllipseItem.GetBorderColor() : m_nBorderColor);
}

VOID CMimicsEllipseItem::SetInteriorColor(COLORREF nColor)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetInteriorColor(nColor);
		return;
	}
	m_nInteriorColor = nColor;
}

COLORREF CMimicsEllipseItem::GetInteriorColor() CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsEllipseItem.GetInteriorColor() : m_nInteriorColor);
}

VOID CMimicsEllipseItem::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetInteriorHatch(nHatch, nColor);
		return;
	}
	m_nInteriorHatch = nHatch;
	m_nHatchColor = nColor;
}

BOOL CMimicsEllipseItem::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		nHatch = m_nInteriorHatch;
		nColor = m_nHatchColor;
		return((nHatch >= 0) ? TRUE : FALSE);
	}
	return cMimicsEllipseItem.GetInteriorHatch(nHatch, nColor);
}

BOOL CMimicsEllipseItem::MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.nBorderSize = GetBorderSize();
	sData.nBorderStyle = GetBorderStyle();
	sData.nBorderColor = GetBorderColor();
	sData.nInteriorColor = GetInteriorColor();
	GetInteriorHatch(sData.nInteriorHatch, sData.nHatchColor);
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsEllipseItem::UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_nInteriorColor = sData.nInteriorColor;
		m_nInteriorHatch = sData.nInteriorHatch;
		m_nHatchColor = sData.nHatchColor;
		m_nBorderStyle = sData.nBorderStyle;
		m_nBorderColor = sData.nBorderColor;
		m_nBorderSize = sData.nBorderSize;
		m_nStyle = sData.nStyle;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsEllipseItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetBorderSize(m_nBorderSize);
	SetBorderStyle(m_nBorderStyle);
	SetBorderColor(m_nBorderColor);
	SetInteriorColor(m_nInteriorColor);
	SetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
	SetItemVisibility(m_bVisible);
	Unlock();
}

BOOL CMimicsEllipseItem::Copy(CONST CMimicsItem *pItem, BOOL bAll)
{
	CMimicsEllipseItem  *pEllipseItem = (CMimicsEllipseItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsEllipseItem)))
	{
		m_nStyle = pEllipseItem->GetStyle();
		m_nBorderSize = pEllipseItem->GetBorderSize();
		m_nBorderStyle = pEllipseItem->GetBorderStyle();
		m_nBorderColor = pEllipseItem->GetBorderColor();
		m_nInteriorColor = pEllipseItem->GetInteriorColor();
		pEllipseItem->GetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
		return CMimicsItem::Copy(pItem, bAll);
	}
	return FALSE;
}

BOOL CMimicsEllipseItem::Compare(CONST CMimicsItem *pItem, BOOL bAll) CONST
{
	INT  nHatch[2];
	COLORREF  nHatchColor[2];
	CMimicsEllipseItem  *pEllipseItem = (CMimicsEllipseItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsEllipseItem))) ? ((pEllipseItem->GetStyle() == GetStyle() && pEllipseItem->GetBorderSize() == GetBorderSize() && pEllipseItem->GetBorderStyle() == GetBorderStyle() && pEllipseItem->GetBorderColor() == GetBorderColor() && pEllipseItem->GetInteriorColor() == GetInteriorColor() && pEllipseItem->GetInteriorHatch(nHatch[0], nHatchColor[0]) == GetInteriorHatch(nHatch[1], nHatchColor[1]) && nHatch[0] == nHatch[1] && (nHatch[0] < 0 || nHatchColor[0] == nHatchColor[1])) ? CMimicsItem::Compare(pItem, bAll) : FALSE) : FALSE);
}

BEGIN_MESSAGE_MAP(CMimicsEllipseItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsEllipseItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsArcItem

IMPLEMENT_DYNCREATE(CMimicsArcItem, CMimicsItem)

CMimicsArcItem::CMimicsArcItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsArcCtrl);
	SetStyle();
	SetBorderSize();
	SetBorderStyle();
	SetBorderColor();
	SetInteriorColor();
	SetInteriorHatch();
	SetRadials();
}

VOID CMimicsArcItem::SetStyle(INT nStyle)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsArcItem::GetStyle() CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsArcItem.GetStyle() : m_nStyle);
}

VOID CMimicsArcItem::SetBorderSize(INT nSize)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetBorderSize(nSize);
		return;
	}
	m_nBorderSize = nSize;
}

INT CMimicsArcItem::GetBorderSize() CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsArcItem.GetBorderSize() : m_nBorderSize);
}

VOID CMimicsArcItem::SetBorderStyle(INT nStyle)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetBorderStyle(nStyle);
		return;
	}
	m_nBorderStyle = nStyle;
}

INT CMimicsArcItem::GetBorderStyle() CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsArcItem.GetBorderStyle() : m_nBorderStyle);
}

VOID CMimicsArcItem::SetBorderColor(COLORREF nColor)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetBorderColor(nColor);
		return;
	}
	m_nBorderColor = nColor;
}

COLORREF CMimicsArcItem::GetBorderColor() CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsArcItem.GetBorderColor() : m_nBorderColor);
}

VOID CMimicsArcItem::SetInteriorColor(COLORREF nColor)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetInteriorColor(nColor);
		return;
	}
	m_nInteriorColor = nColor;
}

COLORREF CMimicsArcItem::GetInteriorColor() CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsArcItem.GetInteriorColor() : m_nInteriorColor);
}

VOID CMimicsArcItem::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetInteriorHatch(nHatch, nColor);
		return;
	}
	m_nInteriorHatch = nHatch;
	m_nHatchColor = nColor;
}

BOOL CMimicsArcItem::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		nHatch = m_nInteriorHatch;
		nColor = m_nHatchColor;
		return((nHatch >= 0) ? TRUE : FALSE);
	}
	return cMimicsArcItem.GetInteriorHatch(nHatch, nColor);
}

VOID CMimicsArcItem::SetRadials(double fRadial1, double fRadial2)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL) cMimicsArcItem.SetRadials(fRadial1, fRadial2);
	m_ptRadial[0] = fRadial1;
	m_ptRadial[1] = fRadial2;
}

VOID CMimicsArcItem::GetRadials(double &fRadial1, double &fRadial2) CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.GetRadials(fRadial1, fRadial2);
		return;
	}
	fRadial1 = m_ptRadial[0];
	fRadial2 = m_ptRadial[1];
}

VOID CMimicsArcItem::DragItem(UINT nCode, CONST POINT &ptNew, CONST POINT &ptOld)
{
	CRect  rItem;
	CPoint  point;
	double  fAngle;

	rItem = GetItemPosition();
	point = DoInverseTransformation(ptNew);
	fAngle = (point.x == rItem.CenterPoint().x  &&  point.y == rItem.CenterPoint().y) ? 0.0 : 0.0;
	fAngle = (point.x == rItem.CenterPoint().x  &&  point.y < rItem.CenterPoint().y) ? (M_PI / 2.0) : fAngle;
	fAngle = (point.x == rItem.CenterPoint().x  &&  point.y > rItem.CenterPoint().y) ? ((3.0*M_PI) / 2.0) : fAngle;
	fAngle = (point.x > rItem.CenterPoint().x  &&  point.y == rItem.CenterPoint().y) ? 0.0 : fAngle;
	fAngle = (point.x < rItem.CenterPoint().x  &&  point.y == rItem.CenterPoint().y) ? M_PI : fAngle;
	fAngle = (point.x > rItem.CenterPoint().x  &&  point.y < rItem.CenterPoint().y) ? atan((double)(rItem.CenterPoint().y - point.y) / (double)(point.x - rItem.CenterPoint().x)) : fAngle;
	fAngle = (point.x < rItem.CenterPoint().x  &&  point.y < rItem.CenterPoint().y) ? (M_PI - atan((double)(rItem.CenterPoint().y - point.y) / (double)(rItem.CenterPoint().x - point.x))) : fAngle;
	fAngle = (point.x < rItem.CenterPoint().x  &&  point.y > rItem.CenterPoint().y) ? (M_PI + atan((double)(point.y - rItem.CenterPoint().y) / (double)(rItem.CenterPoint().x - point.x))) : fAngle;
	fAngle = (point.x > rItem.CenterPoint().x  &&  point.y > rItem.CenterPoint().y) ? (2.0*M_PI - atan((double)(point.y - rItem.CenterPoint().y) / (double)(point.x - rItem.CenterPoint().x))) : fAngle;
	SetRadials((nCode == MIAC_FIRSTRADIALTHUMB) ? fAngle : m_ptRadial[0], (nCode == MIAC_LASTRADIALTHUMB) ? fAngle : m_ptRadial[1]);
}

BOOL CMimicsArcItem::DrawItemFrame(CDC *pDC, CONST RECT &rect)
{
	INT  nRgn;
	INT  nMode;
	INT  nThumb;
	INT  nThumbs;
	INT  nRadius;
	CRgn  rgnClip;
	HRGN  hOldRgn;
	CPen  *pOldPen;
	CPen  cThumbPen;
	CPen  cRadialPen;
	RECT  rThumbs[2];
	XFORM  xTransform;
	CBrush  *pOldBrush;
	CBrush  brThumb;
	CPoint  ptCenter;
	CPoint  ptItem[4];
	CPoint  ptRadial[2];

	if (IsItemActivated(TRUE))
	{
		nRadius = max(rect.right - rect.left, rect.bottom - rect.top);
		ptItem[0] = DoTransformation(CPoint(rect.left, rect.top));
		ptItem[1] = DoTransformation(CPoint(rect.right, rect.top));
		ptItem[2] = DoTransformation(CPoint(rect.right, rect.bottom));
		ptItem[3] = DoTransformation(CPoint(rect.left, rect.bottom));
		ptCenter = CPoint((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2);
		if (rgnClip.CreatePolygonRgn(ptItem, sizeof(ptItem) / sizeof(CPoint), WINDING))
		{
			if ((hOldRgn = CreateRectRgn(0, 0, 0, 0)) && (nRgn = GetClipRgn(pDC->GetSafeHdc(), hOldRgn)) >= 0 && pDC->SelectClipRgn(&rgnClip, RGN_AND) != ERROR)
			{
				ptRadial[0].x = ptRadial[1].x = (rect.left + rect.right) / 2 + nRadius;
				ptRadial[0].y = ptRadial[1].y = (rect.top + rect.bottom) / 2;
				xTransform.eM11 = (float)cos(2.0*M_PI - m_ptRadial[0]);
				xTransform.eM12 = (float)sin(2.0*M_PI - m_ptRadial[0]);
				xTransform.eM21 = (float)-sin(2.0*M_PI - m_ptRadial[0]);
				xTransform.eM22 = (float)cos(2.0*M_PI - m_ptRadial[0]);
				xTransform.eDx = xTransform.eDy = (float) 0.0;
				ptRadial[0] = CalcTransform(ptCenter, xTransform, ptRadial[0]);
				ptRadial[0] = DoTransformation(ptRadial[0]);
				xTransform.eM11 = (float)cos(2.0*M_PI - m_ptRadial[1]);
				xTransform.eM12 = (float)sin(2.0*M_PI - m_ptRadial[1]);
				xTransform.eM21 = (float)-sin(2.0*M_PI - m_ptRadial[1]);
				xTransform.eM22 = (float)cos(2.0*M_PI - m_ptRadial[1]);
				ptRadial[1] = CalcTransform(ptCenter, xTransform, ptRadial[1]);
				ptRadial[1] = DoTransformation(ptRadial[1]);
				if (cRadialPen.CreatePen(PS_DOT, 1, GetSysColor(COLOR_WINDOWFRAME)))
				{
					if ((pOldPen = pDC->SelectObject(&cRadialPen)))
					{
						nMode = pDC->SetROP2(R2_MASKNOTPEN);
						pDC->MoveTo(DoTransformation(ptCenter));
						pDC->LineTo(ptRadial[0]);
						pDC->MoveTo(DoTransformation(ptCenter));
						pDC->LineTo(ptRadial[1]);
						pDC->SetROP2(nMode);
						pDC->SelectObject(pOldPen);
					}
					cRadialPen.DeleteObject();
				}
				if (cThumbPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME)))
				{
					if (brThumb.CreateSolidBrush(VGA_COLOR_LTYELLOW))
					{
						if ((pOldPen = (CPen *)pDC->SelectObject(&cThumbPen)))
						{
							if ((pOldBrush = (CBrush *)pDC->SelectObject(&brThumb)))
							{
								for (nThumb = 0, nThumbs = CalcItemFrameRadialThumbPositions(rect, rThumbs, sizeof(rThumbs) / sizeof(rThumbs[0])); nThumb < nThumbs; nThumb++)
								{
									pDC->Ellipse(&rThumbs[nThumb]);
									continue;
								}
								pDC->SelectObject(pOldBrush);
							}
							pDC->SelectObject(pOldPen);
						}
						brThumb.DeleteObject();
					}
					cThumbPen.DeleteObject();
				}
				SelectClipRgn(pDC->GetSafeHdc(), (nRgn > 0) ? hOldRgn : (HRGN)NULL);
			}
			rgnClip.DeleteObject();
			DeleteObject(hOldRgn);
		}
	}
	return CMimicsItem::DrawItemFrame(pDC, rect);
}

INT CMimicsArcItem::CalcItemFrameRadialThumbPositions(CONST RECT &rect, LPRECT prThumbs, INT nThumbs) CONST
{
	RECT  rThumbs[2];
	XFORM  xTransform;
	CPoint  ptCenter;
	CPoint  ptRadial[2];

	ptRadial[0].y = ptRadial[1].y = (rect.top + rect.bottom) / 2;
	ptRadial[0].x = ptRadial[1].x = (rect.left + rect.right) / 2 + min(rect.right - rect.left, rect.bottom - rect.top) / 3;
	ptCenter = CPoint((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2);
	xTransform.eM11 = (float)cos(2.0*M_PI - m_ptRadial[0]);
	xTransform.eM12 = (float)sin(2.0*M_PI - m_ptRadial[0]);
	xTransform.eM21 = (float)-sin(2.0*M_PI - m_ptRadial[0]);
	xTransform.eM22 = (float)cos(2.0*M_PI - m_ptRadial[0]);
	xTransform.eDx = xTransform.eDy = (float) 0.0;
	ptRadial[0] = CalcTransform(ptCenter, xTransform, ptRadial[0]);
	ptRadial[0] = DoTransformation(ptRadial[0]);
	xTransform.eM11 = (float)cos(2.0*M_PI - m_ptRadial[1]);
	xTransform.eM12 = (float)sin(2.0*M_PI - m_ptRadial[1]);
	xTransform.eM21 = (float)-sin(2.0*M_PI - m_ptRadial[1]);
	xTransform.eM22 = (float)cos(2.0*M_PI - m_ptRadial[1]);
	ptRadial[1] = CalcTransform(ptCenter, xTransform, ptRadial[1]);
	ptRadial[1] = DoTransformation(ptRadial[1]);
	SetRect(&rThumbs[0], ptRadial[0].x - MIMICSITEM_THUMB_SIZE / 2 - 1, ptRadial[0].y - MIMICSITEM_THUMB_SIZE / 2 - 1, ptRadial[0].x + MIMICSITEM_THUMB_SIZE / 2, ptRadial[0].y + MIMICSITEM_THUMB_SIZE / 2);
	SetRect(&rThumbs[1], ptRadial[1].x - MIMICSITEM_THUMB_SIZE / 2 - 1, ptRadial[1].y - MIMICSITEM_THUMB_SIZE / 2 - 1, ptRadial[1].x + MIMICSITEM_THUMB_SIZE / 2, ptRadial[1].y + MIMICSITEM_THUMB_SIZE / 2);
	CopyMemory(&prThumbs[0], &rThumbs[0], (nThumbs >= (INT)(sizeof(rThumbs) / sizeof(RECT))) ? sizeof(RECT) : 0);
	CopyMemory(&prThumbs[1], &rThumbs[1], (nThumbs >= (INT)(sizeof(rThumbs) / sizeof(RECT))) ? sizeof(RECT) : 0);
	return((!nThumbs || nThumbs >= (INT)(sizeof(rThumbs) / sizeof(RECT))) ? sizeof(rThumbs) / sizeof(RECT) : -1);
}

INT CMimicsArcItem::CalcItemFrameOutlinePoints(CONST RECT &rect, LPPOINT pPoints, INT nPoints) CONST
{
	INT  dx;
	INT  dy;
	INT  nPt;
	INT  nPts;
	double  fAngle;
	CPoint  ptCenter;
	CPoint  ptOutline;
	CPoint  ptIntersection[2];
	POINT  ptEdge[4];

	dx = rect.right - rect.left;
	dy = rect.bottom - rect.top;
	ptCenter.x = (rect.left + rect.right) / 2;
	ptCenter.y = (rect.top + rect.bottom) / 2;
	fAngle = (dx > 0) ? atan(fabs((double)dy) / fabs((double)dx)) : 0.0;
	for (nPt = 0, nPts = sizeof(ptIntersection) / sizeof(CPoint); nPt < nPts; nPt++)
	{
		if (fabs(m_ptRadial[nPt]) < FLT_EPSILON || fabs(2.0*M_PI - m_ptRadial[nPt]) < FLT_EPSILON)
		{
			ptIntersection[nPt].x = rect.right;
			ptIntersection[nPt].y = (rect.top + rect.bottom) / 2;
			continue;
		}
		if (fabs(m_ptRadial[nPt] - M_PI) < FLT_EPSILON)
		{
			ptIntersection[nPt].x = rect.left;
			ptIntersection[nPt].y = (rect.top + rect.bottom) / 2;
			continue;
		}
		if (fabs(m_ptRadial[nPt] - M_PI / 2.0) < FLT_EPSILON)
		{
			ptIntersection[nPt].x = (rect.left + rect.right) / 2;
			ptIntersection[nPt].y = rect.top;
			continue;
		}
		if (fabs(m_ptRadial[nPt] - (3.0*M_PI) / 2.0) < FLT_EPSILON)
		{
			ptIntersection[nPt].x = (rect.left + rect.right) / 2;
			ptIntersection[nPt].y = rect.bottom;
			continue;
		}
		if (m_ptRadial[nPt] < fAngle || m_ptRadial[nPt] >= 2.0*M_PI - fAngle)
		{
			ptIntersection[nPt].x = rect.right;
			ptIntersection[nPt].y = (INT)((double)(rect.top + rect.bottom) / 2.0 - tan(m_ptRadial[nPt])*(double)dx / 2.0);
			continue;
		}
		if (m_ptRadial[nPt] >= fAngle  &&  m_ptRadial[nPt] < M_PI - fAngle)
		{
			ptIntersection[nPt].x = (INT)((double)(rect.left + rect.right) / 2.0 + (double)dy / (2.0*tan(m_ptRadial[nPt])));
			ptIntersection[nPt].y = rect.top;
			continue;
		}
		if (m_ptRadial[nPt] >= M_PI - fAngle  &&  m_ptRadial[nPt] < M_PI + fAngle)
		{
			ptIntersection[nPt].x = rect.left;
			ptIntersection[nPt].y = (INT)((double)(rect.top + rect.bottom) / 2.0 + tan(m_ptRadial[nPt])*(double)dx / 2.0);
			continue;
		}
		if (m_ptRadial[nPt] >= M_PI + fAngle  &&  m_ptRadial[nPt] < 2.0*M_PI - fAngle)
		{
			ptIntersection[nPt].x = (INT)((double)(rect.left + rect.right) / 2.0 - (double)dy / (2.0*tan(m_ptRadial[nPt])));
			ptIntersection[nPt].y = rect.bottom;
			continue;
		}
	}
	for (nPts = (INT)(sizeof(ptIntersection) / sizeof(CPoint)), CopyMemory(&pPoints[0], &ptCenter, (nPoints >= nPts) ? sizeof(POINT) : 0), CopyMemory(&pPoints[1], &ptIntersection[0], (nPoints >= nPts) ? sizeof(POINT) : 0); TRUE; )
	{
		if (ptIntersection[0].x == rect.left)
		{
			ptEdge[0].x = rect.left;
			ptEdge[0].y = rect.bottom;
			if (ptIntersection[1].y == rect.bottom)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[1].x = rect.right;
			ptEdge[1].y = rect.bottom;
			if (ptIntersection[1].x == rect.right)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[2].x = rect.right;
			ptEdge[2].y = rect.top;
			if (ptIntersection[1].y == rect.top)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[2], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[3].x = rect.left;
			ptEdge[3].y = rect.top;
			if (ptIntersection[1].x == rect.left  &&  ptIntersection[0].y >= ptIntersection[1].y)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[2], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[3], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			if (ptIntersection[1].x == rect.left)
			{
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
		}
		if (ptIntersection[0].y == rect.bottom)
		{
			ptEdge[0].x = rect.right;
			ptEdge[0].y = rect.bottom;
			if (ptIntersection[1].x == rect.right)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[1].x = rect.right;
			ptEdge[1].y = rect.top;
			if (ptIntersection[1].y == rect.top)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[2].x = rect.left;
			ptEdge[2].y = rect.top;
			if (ptIntersection[1].x == rect.left)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[2], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[3].x = rect.left;
			ptEdge[3].y = rect.bottom;
			if (ptIntersection[1].y == rect.bottom  &&  ptIntersection[0].x >= ptIntersection[1].x)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[2], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[3], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			if (ptIntersection[1].y == rect.bottom)
			{
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
		}
		if (ptIntersection[0].x == rect.right)
		{
			ptEdge[0].x = rect.right;
			ptEdge[0].y = rect.top;
			if (ptIntersection[1].y == rect.top)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[1].x = rect.left;
			ptEdge[1].y = rect.top;
			if (ptIntersection[1].x == rect.left)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[2].x = rect.left;
			ptEdge[2].y = rect.bottom;
			if (ptIntersection[1].y == rect.bottom)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[2], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[3].x = rect.right;
			ptEdge[3].y = rect.bottom;
			if (ptIntersection[1].x == rect.right  &&  ptIntersection[0].y <= ptIntersection[1].y)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[2], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[3], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			if (ptIntersection[1].x == rect.right)
			{
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
		}
		if (ptIntersection[0].y == rect.top)
		{
			ptEdge[0].x = rect.left;
			ptEdge[0].y = rect.top;
			if (ptIntersection[1].x == rect.left)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[1].x = rect.left;
			ptEdge[1].y = rect.bottom;
			if (ptIntersection[1].y == rect.bottom)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[2].x = rect.right;
			ptEdge[2].y = rect.bottom;
			if (ptIntersection[1].x == rect.right)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[2], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			ptEdge[3].x = rect.right;
			ptEdge[3].y = rect.top;
			if (ptIntersection[1].y == rect.top  &&  ptIntersection[0].x <= ptIntersection[1].x)
			{
				CopyMemory(&pPoints[nPts - 1], &ptEdge[0], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[2], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptEdge[3], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
			if (ptIntersection[1].y == rect.top)
			{
				CopyMemory(&pPoints[nPts - 1], &ptIntersection[1], (nPoints >= ++nPts) ? sizeof(POINT) : 0);
				break;
			}
		}
		break;
	}
	for (nPt = 0; nPt < nPts && nPoints >= nPts; nPt++)
	{
		ptOutline = DoTransformation(pPoints[nPt]);
		pPoints[nPt].x = ptOutline.x;
		pPoints[nPt].y = ptOutline.y;
	}
	return((!nPoints || nPoints >= nPts) ? nPts : 0);
}

UINT CMimicsArcItem::CheckPointOnItem(CONST POINT &ptPosition)
{
	CRect  rItem;
	RECT  rThumbs[2];

	if (IsItemActivated(TRUE))
	{
		if (GetItemRotateMode())
		{
			if (CalcItemFrameTurnThumbPosition(MIAC_SWTHUMB, (rItem = GetItemPosition())).PtInRect(ptPosition)) return MIAC_SWTHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_NWTHUMB, rItem).PtInRect(ptPosition)) return MIAC_NWTHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_NETHUMB, rItem).PtInRect(ptPosition)) return MIAC_NETHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_SETHUMB, rItem).PtInRect(ptPosition)) return MIAC_SETHUMB;
		}
		else
		{
			if (CalcItemFrameThumbPosition(MIAC_SWTHUMB, (rItem = GetItemPosition())).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_SWTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_WTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_WTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_NWTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NWTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_NTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_NETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NETHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_ETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_ETHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_SETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_SETHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_STHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_STHUMB : MIAC_NOWHERE);
		}
		if (CalcItemFrameRadialThumbPositions(GetItemPosition(), rThumbs, sizeof(rThumbs) / sizeof(RECT)) > 0)
		{
			if (PtInRect(&rThumbs[0], ptPosition)) return MIAC_FIRSTRADIALTHUMB;
			if (PtInRect(&rThumbs[1], ptPosition)) return MIAC_LASTRADIALTHUMB;
		}
	}
	return((CheckPointInsideItem(ptPosition)) ? MIAC_INSIDE : MIAC_NOWHERE);
}

BOOL CMimicsArcItem::MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.nBorderSize = GetBorderSize();
	sData.nBorderStyle = GetBorderStyle();
	sData.nBorderColor = GetBorderColor();
	sData.nInteriorColor = GetInteriorColor();
	GetInteriorHatch(sData.nInteriorHatch, sData.nHatchColor);
	GetRadials(sData.ptRadial[0], sData.ptRadial[1]);
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsArcItem::UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_nInteriorColor = sData.nInteriorColor;
		m_nInteriorHatch = sData.nInteriorHatch;
		m_nHatchColor = sData.nHatchColor;
		m_nBorderStyle = sData.nBorderStyle;
		m_nBorderColor = sData.nBorderColor;
		m_nBorderSize = sData.nBorderSize;
		m_ptRadial[0] = sData.ptRadial[0];
		m_ptRadial[1] = sData.ptRadial[1];
		m_nStyle = sData.nStyle;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsArcItem::InitializeProperties()
{
	INT  dx;
	INT  dy;

	dx = m_rPosition[0].right - m_rPosition[0].left;
	dy = m_rPosition[0].bottom - m_rPosition[0].top;
	SetRadials((dx > 0) ? (2.0*M_PI - atan((double)dy / (double)dx)) : (M_PI / 2.0), (dx > 0) ? atan((double)dy / (double)dx) : (M_PI / 2.0));
}

VOID CMimicsArcItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetBorderSize(m_nBorderSize);
	SetBorderStyle(m_nBorderStyle);
	SetBorderColor(m_nBorderColor);
	SetInteriorColor(m_nInteriorColor);
	SetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
	SetRadials(m_ptRadial[0], m_ptRadial[1]);
	SetItemVisibility(m_bVisible);
	Unlock();
}

BOOL CMimicsArcItem::Copy(CONST CMimicsItem *pItem, BOOL bAll)
{
	CMimicsArcItem  *pArcItem = (CMimicsArcItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsArcItem)))
	{
		m_nStyle = pArcItem->GetStyle();
		m_nBorderSize = pArcItem->GetBorderSize();
		m_nBorderStyle = pArcItem->GetBorderStyle();
		m_nBorderColor = pArcItem->GetBorderColor();
		m_nInteriorColor = pArcItem->GetInteriorColor();
		pArcItem->GetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
		m_ptRadial[0] = pArcItem->m_ptRadial[0];
		m_ptRadial[1] = pArcItem->m_ptRadial[1];
		return CMimicsItem::Copy(pItem, bAll);
	}
	return FALSE;
}

BOOL CMimicsArcItem::Compare(CONST CMimicsItem *pItem, BOOL bAll) CONST
{
	INT  nHatch[2];
	COLORREF  nHatchColor[2];
	CMimicsArcItem  *pArcItem = (CMimicsArcItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsArcItem))) ? ((pArcItem->GetStyle() == GetStyle() && pArcItem->GetBorderSize() == GetBorderSize() && pArcItem->GetBorderStyle() == GetBorderStyle() && pArcItem->GetBorderColor() == GetBorderColor() && pArcItem->GetInteriorColor() == GetInteriorColor() && pArcItem->GetInteriorHatch(nHatch[0], nHatchColor[0]) == GetInteriorHatch(nHatch[1], nHatchColor[1]) && nHatch[0] == nHatch[1] && (nHatch[0] < 0 || nHatchColor[0] == nHatchColor[1]) && pArcItem->m_ptRadial[0] == m_ptRadial[0] && pArcItem->m_ptRadial[1] == m_ptRadial[1]) ? CMimicsItem::Compare(pItem, bAll) : FALSE) : FALSE);
}

BEGIN_MESSAGE_MAP(CMimicsArcItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsArcItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItem

IMPLEMENT_DYNCREATE(CMimicsTriangleItem, CMimicsItem)

CMimicsTriangleItem::CMimicsTriangleItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsTriangleCtrl);
	SetStyle();
	SetBorderSize();
	SetBorderStyle();
	SetBorderColor();
	SetInteriorColor();
	SetInteriorHatch();
	SetEdges();
}

VOID CMimicsTriangleItem::SetStyle(INT nStyle)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsTriangleItem::GetStyle() CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTriangleItem.GetStyle() : m_nStyle);
}

VOID CMimicsTriangleItem::SetBorderSize(INT nSize)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetBorderSize(nSize);
		return;
	}
	m_nBorderSize = nSize;
}

INT CMimicsTriangleItem::GetBorderSize() CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTriangleItem.GetBorderSize() : m_nBorderSize);
}

VOID CMimicsTriangleItem::SetBorderStyle(INT nStyle)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetBorderStyle(nStyle);
		return;
	}
	m_nBorderStyle = nStyle;
}

INT CMimicsTriangleItem::GetBorderStyle() CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTriangleItem.GetBorderStyle() : m_nBorderStyle);
}

VOID CMimicsTriangleItem::SetBorderColor(COLORREF nColor)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetBorderColor(nColor);
		return;
	}
	m_nBorderColor = nColor;
}

COLORREF CMimicsTriangleItem::GetBorderColor() CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTriangleItem.GetBorderColor() : m_nBorderColor);
}

VOID CMimicsTriangleItem::SetInteriorColor(COLORREF nColor)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetInteriorColor(nColor);
		return;
	}
	m_nInteriorColor = nColor;
}

COLORREF CMimicsTriangleItem::GetInteriorColor() CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTriangleItem.GetInteriorColor() : m_nInteriorColor);
}

VOID CMimicsTriangleItem::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetInteriorHatch(nHatch, nColor);
		return;
	}
	m_nInteriorHatch = nHatch;
	m_nHatchColor = nColor;
}

BOOL CMimicsTriangleItem::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		nHatch = m_nInteriorHatch;
		nColor = m_nHatchColor;
		return((nHatch >= 0) ? TRUE : FALSE);
	}
	return cMimicsTriangleItem.GetInteriorHatch(nHatch, nColor);
}

VOID CMimicsTriangleItem::SetEdges(double x1, double y1, double x2, double y2, double x3, double y3)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetEdges(x1, y1, x2, y2, x3, y3);
		return;
	}
	m_ptEdges[0][0] = x1;
	m_ptEdges[0][1] = y1;
	m_ptEdges[1][0] = x2;
	m_ptEdges[1][1] = y2;
	m_ptEdges[2][0] = x3;
	m_ptEdges[2][1] = y3;
}

VOID CMimicsTriangleItem::GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		x1 = m_ptEdges[0][0];
		y1 = m_ptEdges[0][1];
		x2 = m_ptEdges[1][0];
		y2 = m_ptEdges[1][1];
		x3 = m_ptEdges[2][0];
		y3 = m_ptEdges[2][1];
		return;
	}
	cMimicsTriangleItem.GetEdges(x1, y1, x2, y2, x3, y3);
}

VOID CMimicsTriangleItem::DragItem(UINT nCode, CONST POINT &ptNew, CONST POINT &ptOld)
{
	CRect  rItem[2];
	CPoint  ptDragEdge;
	double  ptEdges[2][3][2];

	rItem[0] = GetItemPosition();
	ptDragEdge = DoInverseTransformation(ptNew);
	GetEdges(ptEdges[0][0][0], ptEdges[0][0][1], ptEdges[0][1][0], ptEdges[0][1][1], ptEdges[0][2][0], ptEdges[0][2][1]);
	ptEdges[1][0][0] = ptEdges[0][0][0] * rItem[0].Width();
	ptEdges[1][1][0] = ptEdges[0][1][0] * rItem[0].Width();
	ptEdges[1][0][1] = ptEdges[0][0][1] * rItem[0].Height();
	ptEdges[1][1][1] = ptEdges[0][1][1] * rItem[0].Height();
	ptEdges[1][0][0] += rItem[0].left;
	ptEdges[1][1][0] += rItem[0].left;
	ptEdges[1][0][1] += rItem[0].top;
	ptEdges[1][1][1] += rItem[0].top;
	ptEdges[1][2][0] = ptDragEdge.x;
	ptEdges[1][2][1] = ptDragEdge.y;
	for (rItem[1].left = (INT)(min(min(ptEdges[1][0][0], ptEdges[1][1][0]), ptEdges[1][2][0]) + 0.5), rItem[1].top = (INT)(min(min(ptEdges[1][0][1], ptEdges[1][1][1]), ptEdges[1][2][1]) + 0.5), rItem[1].right = (INT)(max(max(ptEdges[1][0][0], ptEdges[1][1][0]), ptEdges[1][2][0]) + 0.5), rItem[1].bottom = (INT)(max(max(ptEdges[1][0][1], ptEdges[1][1][1]), ptEdges[1][2][1]) + 0.5), ptEdges[1][2][0] -= rItem[1].left; rItem[1].Width() > 0; )
	{
		ptEdges[1][2][0] /= rItem[1].Width();
		break;
	}
	for (ptEdges[1][2][1] -= rItem[1].top; rItem[1].Height() > 0; )
	{
		ptEdges[1][2][1] /= rItem[1].Height();
		break;
	}
	AdjustItemPosition(rItem[1]);
	SetEdges(ptEdges[0][0][0], ptEdges[0][0][1], ptEdges[0][1][0], ptEdges[0][1][1], ptEdges[1][2][0], ptEdges[1][2][1]);
	AdjustItemPosition(rItem[0]);
	SetItemPosition(rItem[1]);
}

BOOL CMimicsTriangleItem::DrawItemFrame(CDC *pDC, CONST RECT &rect)
{
	CPen  cPen;
	CPen  *pOldPen;
	CRect  rItem;
	CRect  rThumb;
	CPoint  ptThumb;
	CBrush  *pOldBrush;
	CBrush  cThumbBrush;
	double  ptEdges[3][2];

	if (!GetItemRotateMode())
	{
		rItem = GetItemPosition();
		if (CMimicsItem::DrawItemFrame(pDC, rect))
		{
			GetEdges(ptEdges[0][0], ptEdges[0][1], ptEdges[1][0], ptEdges[1][1], ptEdges[2][0], ptEdges[2][1]);
			ptEdges[2][0] *= rItem.Width();
			ptEdges[2][1] *= rItem.Height();
			ptEdges[2][0] += rItem.left;
			ptEdges[2][1] += rItem.top;
			ptThumb.x = (INT)ptEdges[2][0];
			ptThumb.y = (INT)ptEdges[2][1];
			ptThumb = DoTransformation(ptThumb);
			rThumb.SetRect(ptThumb.x - MIMICSITEM_THUMB_SIZE / 2, ptThumb.y - MIMICSITEM_THUMB_SIZE / 2, ptThumb.x + MIMICSITEM_THUMB_SIZE / 2, ptThumb.y + MIMICSITEM_THUMB_SIZE / 2);
			if (cPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME)))
			{
				if (cThumbBrush.CreateSolidBrush(VGA_COLOR_LTYELLOW))
				{
					if ((pOldBrush = pDC->SelectObject(&cThumbBrush)))
					{
						if ((pOldPen = pDC->SelectObject(&cPen)))
						{
							pDC->Rectangle(rThumb);
							pDC->SelectObject(pOldPen);
						}
						pDC->SelectObject(pOldBrush);
					}
					cThumbBrush.DeleteObject();
				}
				cPen.DeleteObject();
			}
			return TRUE;
		}
		return FALSE;
	}
	return CMimicsItem::DrawItemFrame(pDC, rect);
}

UINT CMimicsTriangleItem::CheckPointOnItem(CONST POINT &ptPosition)
{
	CRect  rItem;
	CRect  rThumb;
	CPoint  ptThumb;
	double  ptEdges[3][2];

	if (IsItemActivated(TRUE))
	{
		if (GetItemRotateMode())
		{
			if (CalcItemFrameTurnThumbPosition(MIAC_SWTHUMB, (rItem = GetItemPosition())).PtInRect(ptPosition)) return MIAC_SWTHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_NWTHUMB, rItem).PtInRect(ptPosition)) return MIAC_NWTHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_NETHUMB, rItem).PtInRect(ptPosition)) return MIAC_NETHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_SETHUMB, rItem).PtInRect(ptPosition)) return MIAC_SETHUMB;
		}
		else
		{
			for (rItem = GetItemPosition(), GetEdges(ptEdges[0][0], ptEdges[0][1], ptEdges[1][0], ptEdges[1][1], ptEdges[2][0], ptEdges[2][1]), ptEdges[2][0] *= rItem.Width(), ptEdges[2][1] *= rItem.Height(), ptEdges[2][0] += rItem.left, ptEdges[2][1] += rItem.top, ptThumb.x = (INT)ptEdges[2][0], ptThumb.y = (INT)ptEdges[2][1], ptThumb = DoTransformation(ptThumb), rThumb.SetRect(ptThumb.x - MIMICSITEM_THUMB_SIZE / 2, ptThumb.y - MIMICSITEM_THUMB_SIZE / 2, ptThumb.x + MIMICSITEM_THUMB_SIZE / 2, ptThumb.y + MIMICSITEM_THUMB_SIZE / 2); !rThumb.PtInRect(ptPosition); )
			{
				if (CalcItemFrameThumbPosition(MIAC_SWTHUMB, (rItem = GetItemPosition())).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_SWTHUMB : MIAC_NOWHERE);
				if (CalcItemFrameThumbPosition(MIAC_WTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_WTHUMB : MIAC_NOWHERE);
				if (CalcItemFrameThumbPosition(MIAC_NWTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NWTHUMB : MIAC_NOWHERE);
				if (CalcItemFrameThumbPosition(MIAC_NTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NTHUMB : MIAC_NOWHERE);
				if (CalcItemFrameThumbPosition(MIAC_NETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NETHUMB : MIAC_NOWHERE);
				if (CalcItemFrameThumbPosition(MIAC_ETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_ETHUMB : MIAC_NOWHERE);
				if (CalcItemFrameThumbPosition(MIAC_SETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_SETHUMB : MIAC_NOWHERE);
				if (CalcItemFrameThumbPosition(MIAC_STHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_STHUMB : MIAC_NOWHERE);
				break;
			}
			if (rThumb.PtInRect(ptPosition)) return MIAC_DRAGTHUMB;
		}
	}
	return((CheckPointInsideItem(ptPosition)) ? MIAC_INSIDE : MIAC_NOWHERE);
}

BOOL CMimicsTriangleItem::MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;
	double  ptEdges[3][2];

	sData.nStyle = GetStyle();
	sData.nBorderSize = GetBorderSize();
	sData.nBorderStyle = GetBorderStyle();
	sData.nBorderColor = GetBorderColor();
	sData.nInteriorColor = GetInteriorColor();
	GetInteriorHatch(sData.nInteriorHatch, sData.nHatchColor);
	GetEdges(ptEdges[0][0], ptEdges[0][1], ptEdges[1][0], ptEdges[1][1], ptEdges[2][0], ptEdges[2][1]);
	sData.ptEdges[0][0] = ptEdges[0][0];
	sData.ptEdges[0][1] = ptEdges[0][1];
	sData.ptEdges[1][0] = ptEdges[1][0];
	sData.ptEdges[1][1] = ptEdges[1][1];
	sData.ptEdges[2][0] = ptEdges[2][0];
	sData.ptEdges[2][1] = ptEdges[2][1];
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsTriangleItem::UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_ptEdges[0][0] = sData.ptEdges[0][0];
		m_ptEdges[0][1] = sData.ptEdges[0][1];
		m_ptEdges[1][0] = sData.ptEdges[1][0];
		m_ptEdges[1][1] = sData.ptEdges[1][1];
		m_ptEdges[2][0] = sData.ptEdges[2][0];
		m_ptEdges[2][1] = sData.ptEdges[2][1];
		m_nInteriorColor = sData.nInteriorColor;
		m_nInteriorHatch = sData.nInteriorHatch;
		m_nHatchColor = sData.nHatchColor;
		m_nBorderStyle = sData.nBorderStyle;
		m_nBorderColor = sData.nBorderColor;
		m_nBorderSize = sData.nBorderSize;
		m_nStyle = sData.nStyle;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsTriangleItem::InitializeProperties()
{
	double  ptEdges[3][2];

	ptEdges[0][0] = 0.0;
	ptEdges[0][1] = 1.0;
	ptEdges[1][0] = 1.0;
	ptEdges[1][1] = 1.0;
	ptEdges[2][0] = 0.5;
	ptEdges[2][1] = 0.0;
	SetEdges(ptEdges[0][0], ptEdges[0][1], ptEdges[1][0], ptEdges[1][1], ptEdges[2][0], ptEdges[2][1]);
}

VOID CMimicsTriangleItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetBorderSize(m_nBorderSize);
	SetBorderStyle(m_nBorderStyle);
	SetBorderColor(m_nBorderColor);
	SetInteriorColor(m_nInteriorColor);
	SetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
	SetEdges(m_ptEdges[0][0], m_ptEdges[0][1], m_ptEdges[1][0], m_ptEdges[1][1], m_ptEdges[2][0], m_ptEdges[2][1]);
	SetItemVisibility(m_bVisible);
	Unlock();
}

BOOL CMimicsTriangleItem::Copy(CONST CMimicsItem *pItem, BOOL bAll)
{
	CMimicsTriangleItem  *pTriangleItem = (CMimicsTriangleItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTriangleItem)))
	{
		m_nStyle = pTriangleItem->GetStyle();
		m_nBorderSize = pTriangleItem->GetBorderSize();
		m_nBorderStyle = pTriangleItem->GetBorderStyle();
		m_nBorderColor = pTriangleItem->GetBorderColor();
		m_nInteriorColor = pTriangleItem->GetInteriorColor();
		pTriangleItem->GetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
		pTriangleItem->GetEdges(m_ptEdges[0][0], m_ptEdges[0][1], m_ptEdges[1][0], m_ptEdges[1][1], m_ptEdges[2][0], m_ptEdges[2][1]);
		return CMimicsItem::Copy(pItem, bAll);
	}
	return FALSE;
}

BOOL CMimicsTriangleItem::Compare(CONST CMimicsItem *pItem, BOOL bAll) CONST
{
	INT  nHatch[2];
	double  ptEdges[2][3][2];
	COLORREF  nHatchColor[2];
	CMimicsTriangleItem  *pTriangleItem = (CMimicsTriangleItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTriangleItem)))
	{
		GetEdges(ptEdges[0][0][0], ptEdges[0][0][1], ptEdges[0][1][0], ptEdges[0][1][1], ptEdges[0][2][0], ptEdges[0][2][1]);
		pTriangleItem->GetEdges(ptEdges[1][0][0], ptEdges[1][0][1], ptEdges[1][1][0], ptEdges[1][1][1], ptEdges[1][2][0], ptEdges[1][2][1]);
		return((pTriangleItem->GetStyle() == GetStyle() && pTriangleItem->GetBorderSize() == GetBorderSize() && pTriangleItem->GetBorderStyle() == GetBorderStyle() && pTriangleItem->GetBorderColor() == GetBorderColor() && pTriangleItem->GetInteriorColor() == GetInteriorColor() && pTriangleItem->GetInteriorHatch(nHatch[0], nHatchColor[0]) == GetInteriorHatch(nHatch[1], nHatchColor[1]) && nHatch[0] == nHatch[1] && (nHatch[0] < 0 || nHatchColor[0] == nHatchColor[1]) && ptEdges[0][0][0] == ptEdges[1][0][0] && ptEdges[0][0][1] == ptEdges[1][0][1] && ptEdges[0][1][0] == ptEdges[1][1][0] && ptEdges[0][1][1] == ptEdges[1][1][1] && ptEdges[0][2][0] == ptEdges[1][2][0] && ptEdges[0][2][1] == ptEdges[1][2][1]) ? CMimicsItem::Compare(pItem, bAll) : FALSE);
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CMimicsTriangleItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsTriangleItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItem

IMPLEMENT_DYNCREATE(CMimicsSwitchItem, CMimicsItem)

CMimicsSwitchItem::CMimicsSwitchItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsSwitchCtrl);
	SetStyle();
	SetColor();
	SetBarColor();
	SetStubsColor();
	SetFrameColor();
	SetCenterColor();
	SetInteriorFrameColor();
	SetInteriorCenterColor();
	SetThickness();
	SetBarThickness();
	SetStubsThickness();
	SetFrameThickness();
	SetCenterThickness();
}

VOID CMimicsSwitchItem::SetStyle(INT nStyle)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsSwitchItem::GetStyle() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetStyle() : m_nStyle);
}

VOID CMimicsSwitchItem::SetColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetColor(nColor);
		return;
	}
	m_nColor = nColor;
}

COLORREF CMimicsSwitchItem::GetColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetColor() : m_nColor);
}

VOID CMimicsSwitchItem::SetFrameColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetFrameColor(nColor);
		return;
	}
	m_nFrameColor[0] = nColor;
}

COLORREF CMimicsSwitchItem::GetFrameColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetFrameColor() : m_nFrameColor[0]);
}

VOID CMimicsSwitchItem::SetInteriorFrameColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetInteriorFrameColor(nColor);
		return;
	}
	m_nFrameColor[1] = nColor;
}

COLORREF CMimicsSwitchItem::GetInteriorFrameColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetInteriorFrameColor() : m_nFrameColor[1]);
}

VOID CMimicsSwitchItem::SetCenterColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetCenterColor(nColor);
		return;
	}
	m_nCenterColor[0] = nColor;
}

COLORREF CMimicsSwitchItem::GetCenterColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetCenterColor() : m_nCenterColor[0]);
}

VOID CMimicsSwitchItem::SetInteriorCenterColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetInteriorCenterColor(nColor);
		return;
	}
	m_nCenterColor[1] = nColor;
}

COLORREF CMimicsSwitchItem::GetInteriorCenterColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetInteriorCenterColor() : m_nCenterColor[1]);
}

VOID CMimicsSwitchItem::SetBarColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetBarColor(nColor);
		return;
	}
	m_nBarColor = nColor;
}

COLORREF CMimicsSwitchItem::GetBarColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetBarColor() : m_nBarColor);
}

VOID CMimicsSwitchItem::SetStubsColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetStubsColor(nColor);
		return;
	}
	m_nStubsColor = nColor;
}

COLORREF CMimicsSwitchItem::GetStubsColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetStubsColor() : m_nStubsColor);
}

VOID CMimicsSwitchItem::SetThickness(INT nWidth)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetThickness(nWidth);
		return;
	}
	m_nWidth = nWidth;
}

INT CMimicsSwitchItem::GetThickness() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetThickness() : m_nWidth);
}

VOID CMimicsSwitchItem::SetFrameThickness(INT nWidth)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetFrameThickness(nWidth);
		return;
	}
	m_nFrameWidth = nWidth;
}

INT CMimicsSwitchItem::GetFrameThickness() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetFrameThickness() : m_nFrameWidth);
}

VOID CMimicsSwitchItem::SetCenterThickness(INT nWidth)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetCenterThickness(nWidth);
		return;
	}
	m_nCenterWidth = nWidth;
}

INT CMimicsSwitchItem::GetCenterThickness() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetCenterThickness() : m_nCenterWidth);
}

VOID CMimicsSwitchItem::SetBarThickness(INT nWidth)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetBarThickness(nWidth);
		return;
	}
	m_nBarWidth = nWidth;
}

INT CMimicsSwitchItem::GetBarThickness() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetBarThickness() : m_nBarWidth);
}

VOID CMimicsSwitchItem::SetStubsThickness(INT nWidth)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetStubsThickness(nWidth);
		return;
	}
	m_nStubsWidth = nWidth;
}

INT CMimicsSwitchItem::GetStubsThickness() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetStubsThickness() : m_nStubsWidth);
}

VOID CMimicsSwitchItem::Open()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Open();
		return;
	}
}

BOOL CMimicsSwitchItem::IsOpen() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsOpen() : FALSE);
}

BOOL CMimicsSwitchItem::IsClosed() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsClosed() : FALSE);
}

VOID CMimicsSwitchItem::Close()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Close();
		return;
	}
}

VOID CMimicsSwitchItem::Pos1()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Pos1();
		return;
	}
}

BOOL CMimicsSwitchItem::IsPos1() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsPos1() : FALSE);
}

VOID CMimicsSwitchItem::Pos2()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Pos2();
		return;
	}
}

BOOL CMimicsSwitchItem::IsPos2() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsPos2() : FALSE);
}

VOID CMimicsSwitchItem::Pos3()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Pos3();
		return;
	}
}

BOOL CMimicsSwitchItem::IsPos3() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsPos3() : FALSE);
}

VOID CMimicsSwitchItem::Broken()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Broken();
		return;
	}
}

BOOL CMimicsSwitchItem::IsBroken() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsBroken() : FALSE);
}

VOID CMimicsSwitchItem::ResetState()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	cMimicsSwitchItem.Open();
	cMimicsSwitchItem.Pos1();
}

BOOL CMimicsSwitchItem::MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.nColor = GetColor();
	sData.nWidth = GetThickness();
	sData.nBarColor = GetBarColor();
	sData.nBarWidth = GetBarThickness();
	sData.nStubsColor = GetStubsColor();
	sData.nStubsWidth = GetStubsThickness();
	sData.nFrameColor[0] = GetFrameColor();
	sData.nFrameColor[1] = GetInteriorFrameColor();
	sData.nFrameWidth = GetFrameThickness();
	sData.nCenterColor[0] = GetCenterColor();
	sData.nCenterColor[1] = GetInteriorCenterColor();
	sData.nCenterWidth = GetCenterThickness();
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsSwitchItem::UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_nCenterColor[0] = sData.nCenterColor[0];
		m_nCenterColor[1] = sData.nCenterColor[1];
		m_nCenterWidth = sData.nCenterWidth;
		m_nFrameColor[0] = sData.nFrameColor[0];
		m_nFrameColor[1] = sData.nFrameColor[1];
		m_nFrameWidth = sData.nFrameWidth;
		m_nStubsColor = sData.nStubsColor;
		m_nStubsWidth = sData.nStubsWidth;
		m_nBarColor = sData.nBarColor;
		m_nBarWidth = sData.nBarWidth;
		m_nColor = sData.nColor;
		m_nWidth = sData.nWidth;
		m_nStyle = sData.nStyle;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsSwitchItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetColor(m_nColor);
	SetBarColor(m_nBarColor);
	SetStubsColor(m_nStubsColor);
	SetFrameColor(m_nFrameColor[0]);
	SetCenterColor(m_nCenterColor[0]);
	SetInteriorFrameColor(m_nFrameColor[1]);
	SetInteriorCenterColor(m_nCenterColor[1]);
	SetThickness(m_nWidth);
	SetBarThickness(m_nBarWidth);
	SetStubsThickness(m_nStubsWidth);
	SetFrameThickness(m_nFrameWidth);
	SetCenterThickness(m_nCenterWidth);
	SetItemVisibility(m_bVisible);
	Unlock();
}

BOOL CMimicsSwitchItem::Copy(CONST CMimicsItem *pItem, BOOL bAll)
{
	CMimicsSwitchItem  *pSwitchItem = (CMimicsSwitchItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsSwitchItem)))
	{
		m_nStyle = pSwitchItem->GetStyle();
		m_nColor = pSwitchItem->GetColor();
		m_nBarColor = pSwitchItem->GetBarColor();
		m_nStubsColor = pSwitchItem->GetStubsColor();
		m_nFrameColor[0] = pSwitchItem->GetFrameColor();
		m_nCenterColor[0] = pSwitchItem->GetCenterColor();
		m_nFrameColor[1] = pSwitchItem->GetInteriorFrameColor();
		m_nCenterColor[1] = pSwitchItem->GetInteriorCenterColor();
		m_nWidth = pSwitchItem->GetThickness();
		m_nBarWidth = pSwitchItem->GetBarThickness();
		m_nStubsWidth = pSwitchItem->GetStubsThickness();
		m_nFrameWidth = pSwitchItem->GetFrameThickness();
		m_nCenterWidth = pSwitchItem->GetCenterThickness();
		return CMimicsItem::Copy(pItem, bAll);
	}
	return FALSE;
}

BOOL CMimicsSwitchItem::Compare(CONST CMimicsItem *pItem, BOOL bAll) CONST
{
	CMimicsSwitchItem  *pSwitchItem = (CMimicsSwitchItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsSwitchItem))) ? ((pSwitchItem->GetStyle() == GetStyle() && pSwitchItem->GetColor() == GetColor() && pSwitchItem->GetBarColor() == GetBarColor() && pSwitchItem->GetStubsColor() == GetStubsColor() && pSwitchItem->GetFrameColor() == GetFrameColor() && pSwitchItem->GetInteriorFrameColor() == GetInteriorFrameColor() && pSwitchItem->GetCenterColor() == GetCenterColor() && pSwitchItem->GetInteriorCenterColor() == GetInteriorCenterColor() && pSwitchItem->GetThickness() == GetThickness() && pSwitchItem->GetBarThickness() == GetBarThickness() && pSwitchItem->GetStubsThickness() == GetStubsThickness() && pSwitchItem->GetFrameThickness() == GetFrameThickness() && pSwitchItem->GetCenterThickness() == GetCenterThickness()) ? CMimicsItem::Compare(pItem, bAll) : FALSE) : FALSE);
}

BEGIN_MESSAGE_MAP(CMimicsSwitchItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsSwitchItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextItem

IMPLEMENT_DYNCREATE(CMimicsTextItem, CMimicsItem)

CMimicsTextItem::CMimicsTextItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsTextCtrl);
	SetMode();
	SetFont();
	SetColor();
	SetBackgroundColor();
	LeftToRightReading();
	AlignLeft();
	WrapWords();
	SetTabChars();
	SingleLine();
}

VOID CMimicsTextItem::SetText(LPCTSTR pszText)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SetText(pszText);
		return;
	}
	m_szText = pszText;
}

CString CMimicsTextItem::GetText() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.GetText() : m_szText);
}

VOID CMimicsTextItem::SetMode(INT nMode)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SetMode(nMode);
		return;
	}
	m_nMode = nMode;
}

INT CMimicsTextItem::GetMode() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.GetMode() : m_nMode);
}

VOID CMimicsTextItem::SetColor(COLORREF nColor)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SetColor(nColor);
		return;
	}
	m_nColor = nColor;
}

COLORREF CMimicsTextItem::GetColor() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.GetColor() : m_nColor);
}

VOID CMimicsTextItem::SetBackgroundColor(COLORREF nColor)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SetBackgroundColor(nColor);
		return;
	}
	m_nBkColor = nColor;
}

COLORREF CMimicsTextItem::GetBackgroundColor() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.GetBackgroundColor() : m_nBkColor);
}

BOOL CMimicsTextItem::SetFont(CONST LOGFONT *pFont)
{
	LOGFONT  lfFont;
	CFontTools  cFontTools;
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	for (cFontTools.QueryDefaultFont(&lfFont); !GetOleObject(); )
	{
		CopyMemory(&m_lfFont, (!pFont) ? &lfFont : pFont, sizeof(LOGFONT));
		return TRUE;
	}
	return cMimicsTextItem.SetFont((!pFont) ? &lfFont : pFont);
}

BOOL CMimicsTextItem::GetFont(LOGFONT *pFont) CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (!GetOleObject())
	{
		CopyMemory(pFont, &m_lfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return cMimicsTextItem.GetFont(pFont);
}

VOID CMimicsTextItem::AlignLeft()
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.AlignLeft();
		return;
	}
	m_nFormat &= ~(DT_CENTER | DT_RIGHT);
	m_nFormat |= DT_LEFT;
}

VOID CMimicsTextItem::AlignCenter()
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.AlignCenter();
		return;
	}
	m_nFormat &= ~(DT_LEFT | DT_RIGHT);
	m_nFormat |= DT_CENTER;
}

VOID CMimicsTextItem::AlignRight()
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.AlignRight();
		return;
	}
	m_nFormat &= ~(DT_LEFT | DT_CENTER);
	m_nFormat |= DT_RIGHT;
}

VOID CMimicsTextItem::AlignVertical(BOOL bEnable)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.AlignVertical(bEnable);
		return;
	}
	m_nFormat = (!bEnable) ? (m_nFormat & ~DT_VCENTER) : (m_nFormat | DT_VCENTER);
}

BOOL CMimicsTextItem::IsLeftAligned() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsLeftAligned() : ((m_nFormat & (DT_CENTER | DT_RIGHT)) ? !TRUE : !FALSE));
}

BOOL CMimicsTextItem::IsCenterAligned() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsCenterAligned() : ((m_nFormat & DT_CENTER) ? TRUE : FALSE));
}

BOOL CMimicsTextItem::IsRightAligned() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsRightAligned() : ((m_nFormat & DT_RIGHT) ? TRUE : FALSE));
}

BOOL CMimicsTextItem::IsVerticalAligned() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsVerticalAligned() : ((m_nFormat & DT_VCENTER) ? TRUE : FALSE));
}

VOID CMimicsTextItem::LeftToRightReading()
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.LeftToRightReading();
		return;
	}
	m_bReading = FALSE;
}

VOID CMimicsTextItem::TopToBottomReading()
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.TopToBottomReading();
		return;
	}
	m_bReading = TRUE;
}

BOOL CMimicsTextItem::IsLeftToRightReading() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsLeftToRightReading() : !m_bReading);
}

BOOL CMimicsTextItem::IsTopToBottomReading() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsTopToBottomReading() : m_bReading);
}

VOID CMimicsTextItem::SetTabChars(INT nChars)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SetTabChars(nChars);
		return;
	}
	m_nTabs = nChars;
}

INT CMimicsTextItem::GetTabChars() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.GetTabChars() : m_nTabs);
}

VOID CMimicsTextItem::WrapWords(BOOL bEnable)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.WrapWords(bEnable);
		return;
	}
	m_nFormat = (bEnable) ? (m_nFormat | DT_WORDBREAK) : (m_nFormat & ~DT_WORDBREAK);
}

BOOL CMimicsTextItem::IsWrappingWords() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsWrappingWords() : ((m_nFormat & DT_WORDBREAK) ? TRUE : FALSE));
}

VOID CMimicsTextItem::SingleLine(BOOL bEnable)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SingleLine(bEnable);
		return;
	}
	m_nFormat = (bEnable) ? (m_nFormat | DT_SINGLELINE) : (m_nFormat & ~DT_SINGLELINE);
}

BOOL CMimicsTextItem::IsSingleLine() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsSingleLine() : ((m_nFormat & DT_SINGLELINE) ? TRUE : FALSE));
}

BOOL CMimicsTextItem::CheckPointInsideItem(CONST POINT &ptPosition)
{
	CRgn  rgItem;
	CRect  rItem;
	CPoint  ptItem[4];

	if (GetText().IsEmpty())
	{
		rItem = GetItemPosition();
		rItem.InflateRect((!rItem.Width()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0, 0);
		rItem.InflateRect(0, (!rItem.Height()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0);
		ptItem[0] = DoTransformation(CPoint(rItem.left, rItem.top));
		ptItem[1] = DoTransformation(CPoint(rItem.right, rItem.top));
		ptItem[2] = DoTransformation(CPoint(rItem.right, rItem.bottom));
		ptItem[3] = DoTransformation(CPoint(rItem.left, rItem.bottom));
		if (rgItem.CreatePolygonRgn(ptItem, sizeof(ptItem) / sizeof(POINT), WINDING))
		{
			if (rgItem.PtInRegion(ptPosition))
			{
				rgItem.DeleteObject();
				return TRUE;
			}
			rgItem.DeleteObject();
		}
		return FALSE;
	}
	return CMimicsItem::CheckPointInsideItem(ptPosition);
}

BOOL CMimicsTextItem::MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	GetFont(&sData.lfFont);
	sData.nMode = GetMode();
	sData.nTabs = GetTabChars();
	sData.nColor = GetColor();
	sData.nBkColor = GetBackgroundColor();
	sData.bReading = IsTopToBottomReading();
	sData.nFormat = (IsLeftAligned()) ? DT_LEFT : 0;
	sData.nFormat |= (IsRightAligned()) ? DT_RIGHT : sData.nFormat;
	sData.nFormat |= (IsCenterAligned()) ? DT_CENTER : sData.nFormat;
	sData.nFormat |= (IsWrappingWords()) ? DT_WORDBREAK : sData.nFormat;
	sData.nFormat |= (IsSingleLine()) ? DT_SINGLELINE : sData.nFormat;
	sData.cbText = (GetText().GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbText)); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + sizeof(DATA), (LPCTSTR)GetText(), sData.cbText);
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsTextItem::UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbText && sData.cbText > 0; )
	{
		CopyMemory(m_szText.GetBufferSetLength(STRINGCHARS(sData.cbText)), nInfo.GetData() + sizeof(DATA), STRINGBYTES(sData.cbText));
		CopyMemory(&m_lfFont, &sData.lfFont, sizeof(LOGFONT));
		m_nMode = sData.nMode;
		m_nTabs = sData.nTabs;
		m_nColor = sData.nColor;
		m_nFormat = sData.nFormat;
		m_nBkColor = sData.nBkColor;
		m_bReading = sData.bReading;
		m_szText.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsTextItem::UpdateProperties()
{
	Lock();
	SetMode(m_nMode);
	SetText(m_szText);
	SetFont(&m_lfFont);
	SetColor(m_nColor);
	SetBackgroundColor(m_nBkColor);
	SetItemVisibility(m_bVisible);
	if (m_nFormat & ~(DT_CENTER | DT_RIGHT)) AlignLeft();
	if (m_nFormat & DT_CENTER) AlignCenter();
	if (m_nFormat & DT_RIGHT) AlignRight();
	if (m_bReading) TopToBottomReading();
	if (!m_bReading) LeftToRightReading();
	WrapWords((m_nFormat & DT_WORDBREAK) ? TRUE : FALSE);
	SingleLine((m_nFormat & DT_SINGLELINE) ? TRUE : FALSE);
	SetTabChars(m_nTabs);
	Unlock();
}

BOOL CMimicsTextItem::Copy(CONST CMimicsItem *pItem, BOOL bAll)
{
	CMimicsTextItem  *pTextItem = (CMimicsTextItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTextItem)))
	{
		m_nMode = pTextItem->GetMode();
		m_nTabs = pTextItem->GetTabChars();
		m_szText = pTextItem->GetText();
		m_nColor = pTextItem->GetColor();
		m_nBkColor = pTextItem->GetBackgroundColor();
		m_bReading = pTextItem->IsTopToBottomReading();
		m_nFormat = (pTextItem->IsLeftAligned()) ? DT_LEFT : 0;
		m_nFormat |= (pTextItem->IsRightAligned()) ? DT_RIGHT : m_nFormat;
		m_nFormat |= (pTextItem->IsCenterAligned()) ? DT_CENTER : m_nFormat;
		m_nFormat |= (pTextItem->IsWrappingWords()) ? DT_WORDBREAK : m_nFormat;
		m_nFormat |= (pTextItem->IsSingleLine()) ? DT_SINGLELINE : m_nFormat;
		pTextItem->GetFont(&m_lfFont);
		return CMimicsItem::Copy(pItem, bAll);
	}
	return FALSE;
}

BOOL CMimicsTextItem::Compare(CONST CMimicsItem *pItem, BOOL bAll) CONST
{
	LOGFONT  lfFont;
	CMimicsTextItem  *pTextItem = (CMimicsTextItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsTextItem))) ? ((pTextItem->GetMode() == GetMode() && pTextItem->GetTabChars() == GetTabChars() && pTextItem->GetText() == GetText() && pTextItem->GetColor() == GetColor() && pTextItem->GetBackgroundColor() == GetBackgroundColor() && pTextItem->IsLeftAligned() == IsLeftAligned() && pTextItem->IsCenterAligned() == IsCenterAligned() && pTextItem->IsRightAligned() == IsRightAligned() && pTextItem->IsLeftToRightReading() == IsLeftToRightReading() && pTextItem->IsTopToBottomReading() == IsTopToBottomReading() && pTextItem->IsWrappingWords() == IsWrappingWords() && pTextItem->IsSingleLine() == IsSingleLine() && pTextItem->GetFont(&lfFont) && !memcmp(&m_lfFont, &lfFont, sizeof(LOGFONT))) ? CMimicsItem::Compare(pItem, bAll) : FALSE) : FALSE);
}

BEGIN_MESSAGE_MAP(CMimicsTextItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsTextItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsImageItem

IMPLEMENT_DYNCREATE(CMimicsImageItem, CMimicsItem)

CMimicsImageItem::CMimicsImageItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsImageCtrl);
	SetStyle();
	SetFileName();
	SetImageOrigin();
	SetImageSize();
	SetImageTransparency();
}

VOID CMimicsImageItem::SetStyle(INT nStyle)
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsImageItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsImageItem::GetStyle() CONST
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsImageItem.GetStyle() : m_nStyle);
}

VOID CMimicsImageItem::SetFileName(LPCTSTR pszFileName)
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsImageItem.SetFileName(pszFileName);
		return;
	}
	m_szFileName = pszFileName;
}

CString CMimicsImageItem::GetFileName() CONST
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsImageItem.GetFileName() : m_szFileName);
}

VOID CMimicsImageItem::SetImageOrigin(CONST POINT &pt)
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsImageItem.SetImageOrigin(pt);
		return;
	}
	m_ptImage = pt;
}

CPoint CMimicsImageItem::GetImageOrigin() CONST
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsImageItem.GetImageOrigin() : m_ptImage);
}

VOID CMimicsImageItem::SetImageSize(CONST SIZE &size)
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsImageItem.SetImageSize(size);
		return;
	}
	m_sizeImage = size;
}

CSize CMimicsImageItem::GetImageSize() CONST
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsImageItem.GetImageSize() : m_sizeImage);
}

VOID CMimicsImageItem::SetImageTransparency(BYTE nFactor)
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsImageItem.SetImageTransparency(nFactor);
		return;
	}
	m_nImageTransparency = nFactor;
}

BYTE CMimicsImageItem::GetImageTransparency() CONST
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsImageItem.GetImageTransparency() : m_nImageTransparency);
}

BOOL CMimicsImageItem::MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.ptImage = GetImageOrigin();
	sData.sizeImage = GetImageSize();
	sData.nImageTransparency = GetImageTransparency();
	sData.cbFileName = (GetFileName().GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbFileName)); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + sizeof(DATA), (LPCTSTR)GetFileName(), sData.cbFileName);
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsImageItem::UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin)
{
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbFileName && sData.cbFileName > 0; )
	{
		CopyMemory(m_szFileName.GetBufferSetLength(STRINGCHARS(sData.cbFileName)), nInfo.GetData() + sizeof(DATA), STRINGBYTES(sData.cbFileName));
		m_nStyle = sData.nStyle;
		m_ptImage = sData.ptImage;
		m_sizeImage = sData.sizeImage;
		m_nImageTransparency = sData.nImageTransparency;
		m_szFileName.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsImageItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetFileName(m_szFileName);
	SetImageOrigin(m_ptImage);
	SetImageSize(m_sizeImage);
	SetImageTransparency(m_nImageTransparency);
	SetItemVisibility(m_bVisible);
	Unlock();
}

BOOL CMimicsImageItem::Copy(CONST CMimicsItem *pItem, BOOL bAll)
{
	CMimicsImageItem  *pImageItem = (CMimicsImageItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsImageItem)))
	{
		m_nStyle = pImageItem->GetStyle();
		m_szFileName = pImageItem->GetFileName();
		m_ptImage = pImageItem->GetImageOrigin();
		m_sizeImage = pImageItem->GetImageSize();
		m_nImageTransparency = pImageItem->GetImageTransparency();
		return CMimicsItem::Copy(pItem, bAll);
	}
	return FALSE;
}

BOOL CMimicsImageItem::Compare(CONST CMimicsItem *pItem, BOOL bAll) CONST
{
	CMimicsImageItem  *pImageItem = (CMimicsImageItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsImageItem))) ? ((pImageItem->GetStyle() == GetStyle() && !pImageItem->GetFileName().CompareNoCase(GetFileName()) && pImageItem->GetImageOrigin() == GetImageOrigin() && pImageItem->GetImageSize() == GetImageSize() && pImageItem->GetImageTransparency() == GetImageTransparency()) ? CMimicsItem::Compare(pItem, bAll) : FALSE) : FALSE);
}

BEGIN_MESSAGE_MAP(CMimicsImageItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsImageItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsGroup

IMPLEMENT_DYNCREATE(CMimicsGroup, CMimicsItem)

CMimicsGroup::CMimicsGroup(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsGroupCtrl);
	m_pItemList = new CMMDDocument;
}
CMimicsGroup::CMimicsGroup(LPCTSTR pszName, CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsGroupCtrl);
	m_pItemList = new CMMDDocument;
	m_szName = pszName;
}

CMimicsGroup::~CMimicsGroup()
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			delete pItem;
			continue;
		}
	}
	m_pItemList->SetModifiedFlag(FALSE);
	delete m_pItemList;
}

BOOL CMimicsGroup::CreateNewItem(REFCLSID clsid, CView *pView, OLERENDER render, CLIPFORMAT cfFormat, LPFORMATETC lpFormatEtc)
{
	INT  nCount;
	POSITION  lPosition;
	CMimicsItem  *pItem[2];

	Lock();
	if (CMimicsItem::CreateNewItem(clsid, pView, render, cfFormat, lpFormatEtc))
	{
		for (lPosition = m_pItemList->GetStartPosition(), nCount = (INT)m_pItemList->m_docItemList.GetCount(); lPosition && nCount > 0; nCount--)
		{
			if ((pItem[0] = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
			{
				if ((pItem[1] = CMimicsItem::Create(pItem[0], pView, m_pItemList)))
				{
					pItem[1]->SetItemContainer(this);
					pItem[1]->AdjustItemDefaultPosition();
					delete pItem[0];
					continue;
				}
			}
			break;
		}
		Unlock();
		return((!nCount) ? TRUE : FALSE);
	}
	Unlock();
	return FALSE;
}

VOID CMimicsGroup::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CMimicsGroup::GetName() CONST
{
	return m_szName;
}

VOID CMimicsGroup::SetItemPosition(CONST RECT &rect)
{
	CRect  rPosition;

	rPosition = rect;
	rPosition.OffsetRect(GetPosition().CenterPoint() - GetItemPosition().CenterPoint());
	SetPosition(rPosition);
}

CRect CMimicsGroup::GetItemPosition() CONST
{
	return m_rPosition[0];
}

VOID CMimicsGroup::NormalizeItemPosition(BOOL bUndo)
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	if (!bUndo)
	{
		for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
		{
			if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
			{
				pItem->NormalizeItemPosition(bUndo);
				continue;
			}
		}
		DoTransformation(m_ptCenter, m_xForm, m_rPosition[0]);
		return;
	}
	for (lPosition = m_pItemList->GetStartPosition(), DoInverseTransformation(m_ptCenter, m_xForm, m_rPosition[0]); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			pItem->NormalizeItemPosition(bUndo);
			continue;
		}
	}
}

VOID CMimicsGroup::AdjustItemPosition()
{
	CRect  rItem;
	CRect  rGroup;
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(), rGroup.SetRectEmpty(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			rItem = pItem->CalcItemFrameExtent();
			if (rGroup.IsRectNull())
			{
				rGroup.left = min(rItem.left, rItem.right);
				rGroup.top = min(rItem.top, rItem.bottom);
				rGroup.right = max(rItem.left, rItem.right);
				rGroup.bottom = max(rItem.top, rItem.bottom);
				continue;
			}
			rGroup.left = min(min(rItem.left, rItem.right), rGroup.left);
			rGroup.top = min(min(rItem.top, rItem.bottom), rGroup.top);
			rGroup.right = max(max(rItem.left, rItem.right), rGroup.right);
			rGroup.bottom = max(max(rItem.top, rItem.bottom), rGroup.bottom);
		}
	}
	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			pItem->NormalizeItemPosition();
			continue;
		}
	}
	if (!m_pItemList->GetStartPosition())
	{
		m_rPosition[0].DeflateRect(m_rPosition[0].Width(), m_rPosition[0].Height());
		SetItemSize(rGroup.Width(), rGroup.Height());
		SetItemCenterPoint();
		return;
	}
	m_rPosition[0] = rGroup;
	m_ptCenter = rGroup.CenterPoint();
	m_xForm.eM11 = m_xForm.eM22 = (float) 1.0;
	m_xForm.eM12 = m_xForm.eM21 = (float) 0.0;
	m_xForm.eDx = m_xForm.eDy = (float) 0.0;
	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			pItem->NormalizeItemPosition(TRUE);
			pItem->AdjustItemDefaultPosition();
		}
	}
	SetItemSize(rGroup.Width(), rGroup.Height());
	AdjustItemContainer();
}
VOID CMimicsGroup::AdjustItemPosition(CONST RECT &rect)
{
	CRect  rItem;
	CPoint  ptItem;
	POSITION  lPosition;
	CMimicsItem  *pItem;

	if (!m_rPosition[0].EqualRect(&rect))
	{
		if (m_rPosition[0].Width() == rect.right - rect.left &&  m_rPosition[0].Height() == rect.bottom - rect.top)
		{
			for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
			{
				if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
				{
					rItem = pItem->GetItemPosition();
					rItem.OffsetRect(rect.left - m_rPosition[0].left, 0);
					rItem.OffsetRect(0, rect.top - m_rPosition[0].top);
					pItem->AdjustItemPosition(rItem);
				}
			}
			m_ptCenter.x += (rect.left + rect.right) / 2 - m_rPosition[0].CenterPoint().x;
			m_ptCenter.y += (rect.top + rect.bottom) / 2 - m_rPosition[0].CenterPoint().y;
		}
		else
		{
			for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
			{
				if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
				{
					rItem = pItem->GetItemDefaultPosition();
					rItem.left = (rItem.left*(rect.right - rect.left)) / GetSystemMetrics(SM_CXSCREEN);
					rItem.top = (rItem.top*(rect.bottom - rect.top)) / GetSystemMetrics(SM_CYSCREEN);
					rItem.right = (rItem.right*(rect.right - rect.left)) / GetSystemMetrics(SM_CXSCREEN);
					rItem.bottom = (rItem.bottom*(rect.bottom - rect.top)) / GetSystemMetrics(SM_CYSCREEN);
					rItem.OffsetRect(rect.left, rect.top);
					pItem->SetItemCenterPoint(rItem.CenterPoint());
					pItem->AdjustItemPosition(rItem);
				}
			}
		}
		m_rPosition[0] = rect;
	}
}

VOID CMimicsGroup::AdjustItemCenterPoint()
{
	CRect  rItem;
	CRect  rPosition;
	CSize  ptOffset;
	CPoint  ptItem[2];
	POSITION  lPosition;
	CMimicsItem  *pItem;

	rPosition = GetItemPosition();
	if (m_ptCenter != rPosition.CenterPoint())
	{
		ptItem[0] = DoTransformation(rPosition.TopLeft());
		ptItem[1] = DoTransformation(rPosition.BottomRight());
		m_ptCenter.x = (ptItem[0].x + ptItem[1].x) / 2;
		m_ptCenter.y = (ptItem[0].y + ptItem[1].y) / 2;
		ptOffset = m_ptCenter - rPosition.CenterPoint();
		for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
		{
			if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
			{
				rItem = pItem->GetItemPosition();
				rItem.OffsetRect(ptOffset.cx, ptOffset.cy);
				pItem->AdjustItemPosition(rItem);
			}
		}
		rPosition.OffsetRect(ptOffset);
		m_rPosition[0] = rPosition;
	}
}

BOOL CMimicsGroup::IsItemSizeable() CONST
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			if (pItem->IsItemFlippedOrRotated() || !pItem->IsItemSizeable())
			{
				lPosition = (POSITION)-1;
				break;
			}
		}
	}
	return((!lPosition) ? TRUE : FALSE);
}

VOID CMimicsGroup::AddItem(CMimicsItem *pItem)
{
	m_pItemList->AddItem(pItem);
	pItem->NormalizeItemPosition();
	pItem->SetItemContainer(this);
	pItem->NormalizeItemPosition(TRUE);
	AdjustItemPosition();
}

VOID CMimicsGroup::RemoveItem(CMimicsItem *pItem)
{
	m_pItemList->RemoveItem(pItem);
	pItem->NormalizeItemPosition();
	pItem->SetItemContainer(NULL);
	pItem->NormalizeItemPosition(TRUE);
	AdjustItemPosition();
}

CMimicsItem *CMimicsGroup::GetAt(INT nIndex) CONST
{
	INT  nItem;
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(), nItem = 0; lPosition && nIndex >= 0 && nIndex < m_pItemList->m_docItemList.GetCount(); nItem++)
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)) && nItem == nIndex) break;
		continue;
	}
	return((nItem == nIndex) ? pItem : (CMimicsItem *)NULL);
}

CMimicsItem *CMimicsGroup::operator[](INT nIndex) CONST
{
	INT  nItem;
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(), nItem = 0; lPosition && nIndex >= 0 && nIndex < m_pItemList->m_docItemList.GetCount(); nItem++)
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)) && nItem == nIndex) break;
		continue;
	}
	return((nItem == nIndex) ? pItem : (CMimicsItem *)NULL);
}

CMMDDocument *CMimicsGroup::GetItemList() CONST
{
	return m_pItemList;
}

INT CMimicsGroup::GetItemCount() CONST
{
	return((INT)m_pItemList->m_docItemList.GetCount());
}

VOID CMimicsGroup::RemoveAllItems()
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			delete pItem;
			continue;
		}
	}
	m_pItemList->SetModifiedFlag(FALSE);
	AdjustItemPosition();
}

BOOL CMimicsGroup::Draw(CDC *pDC, BOOL bShape)
{
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMimicsGroupItemDispatchDriver  cMimicsGroupItem(GetDispatch());

	for (lPosition = (cMimicsGroupItem.IsVisible()) ? m_pItemList->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			pItem->Draw(pDC, bShape);
			continue;
		}
	}
	return TRUE;
}

UINT CMimicsGroup::CheckPointOnItem(CONST POINT &ptPosition)
{
	CRect  rItem;

	if (IsItemActivated(TRUE))
	{
		if (GetItemRotateMode())
		{
			if (CalcItemFrameTurnThumbPosition(MIAC_SWTHUMB, (rItem = GetItemPosition())).PtInRect(ptPosition)) return MIAC_SWTHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_NWTHUMB, rItem).PtInRect(ptPosition)) return MIAC_NWTHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_NETHUMB, rItem).PtInRect(ptPosition)) return MIAC_NETHUMB;
			if (CalcItemFrameTurnThumbPosition(MIAC_SETHUMB, rItem).PtInRect(ptPosition)) return MIAC_SETHUMB;
		}
		else
		{
			if (CalcItemFrameThumbPosition(MIAC_SWTHUMB, (rItem = GetItemPosition())).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_SWTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_WTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_WTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_NWTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NWTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_NTHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NTHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_NETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_NETHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_ETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_ETHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_SETHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_SETHUMB : MIAC_NOWHERE);
			if (CalcItemFrameThumbPosition(MIAC_STHUMB, rItem).PtInRect(ptPosition)) return((IsItemSizeable()) ? MIAC_STHUMB : MIAC_NOWHERE);
		}
	}
	return((CheckPointInsideItem(ptPosition)) ? MIAC_INSIDE : MIAC_NOWHERE);
}

BOOL CMimicsGroup::CheckPointInsideItem(CONST POINT &ptPosition)
{
	CRgn  rgItem;
	CRect  rItem;
	POINT  ptItem[4];
	POSITION  lPosition;
	CMimicsItem  *pItem;

	if (IsItemActivated(TRUE))
	{
		rItem = GetItemPosition();
		rItem.InflateRect((!rItem.Width()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0, 0);
		rItem.InflateRect(0, (!rItem.Height()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0);
		ptItem[0] = DoTransformation(CPoint(rItem.left, rItem.top));
		ptItem[1] = DoTransformation(CPoint(rItem.right, rItem.top));
		ptItem[2] = DoTransformation(CPoint(rItem.right, rItem.bottom));
		ptItem[3] = DoTransformation(CPoint(rItem.left, rItem.bottom));
		if (rgItem.CreatePolygonRgn(ptItem, sizeof(ptItem) / sizeof(POINT), WINDING))
		{
			if (rgItem.PtInRegion(ptPosition))
			{
				rgItem.DeleteObject();
				return TRUE;
			}
			rgItem.DeleteObject();
		}
		return FALSE;
	}
	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			if (pItem->CheckPointOnItem(ptPosition)) return TRUE;
			continue;
		}
	}
	return FALSE;
}

BOOL CMimicsGroup::MapProperties(CByteArray &nInfo, CONST POINT &ptOrigin)
{
	POSITION  lPosition;
	CByteArray  nItemData;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(), nInfo.RemoveAll(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)) && pItem->Map(nItemData) && nInfo.Append(nItemData) >= 0) continue;
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}

BOOL CMimicsGroup::UnmapProperties(CONST CByteArray &nInfo, CONST POINT &ptOrigin)
{
	INT  cbItem;
	INT  cbItems;
	POSITION  lPosition;
	CByteArray  nItemData;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			m_pItemList->RemoveItem(pItem);
			delete pItem;
		}
	}
	for (cbItems = 0; cbItems < nInfo.GetSize(); cbItems += cbItem)
	{
		for (CopyMemory(&cbItem, nInfo.GetData() + cbItems, sizeof(cbItem)), nItemData.SetSize(max(min(cbItem, nInfo.GetSize() - cbItems), 0)); nItemData.GetSize() >= 0; )
		{
			CopyMemory(nItemData.GetData(), nInfo.GetData() + cbItems, nItemData.GetSize());
			break;
		}
		if ((pItem = CMimicsItem::AllocateFromData(nItemData)))
		{
			if (pItem->Unmap(nItemData, ptOrigin))
			{
				pItem->SetItemContainer(this);
				m_pItemList->AddItem(pItem);
				continue;
			}
			delete pItem;
		}
		break;
	}
	return((cbItems == nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CMimicsGroup::Copy(CONST CMimicsItem *pItem, BOOL bAll)
{
	POSITION  lPosition[2];
	CMimicsItem  *pMimicsItem[2];
	CMimicsGroup  *pMimicsGroup;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)))
	{
		for (lPosition[0] = ((pMimicsGroup = (CMimicsGroup *)pItem)->GetItemName() == GetItemName() && pMimicsGroup->m_pItemList->GetItemCount() == m_pItemList->GetItemCount()) ? pMimicsGroup->m_pItemList->GetStartPosition() : (POSITION)-1, lPosition[1] = (lPosition[0] != (POSITION)-1) ? m_pItemList->GetStartPosition() : (POSITION)-1; lPosition[0] && lPosition[1] && lPosition[0] != (POSITION)-1 && lPosition[1] != (POSITION)-1; )
		{
			if ((pMimicsItem[0] = (CMimicsItem *)pMimicsGroup->m_pItemList->GetNextItem(lPosition[0])))
			{
				if ((pMimicsItem[1] = (CMimicsItem *)m_pItemList->GetNextItem(lPosition[1])))
				{
					if (pMimicsItem[0]->GetItemName() != pMimicsItem[1]->GetItemName())
					{
						lPosition[0] = lPosition[1] = (POSITION)-1;
						break;
					}
					if (pMimicsItem[0]->GetItemType() != pMimicsItem[1]->GetItemType())
					{
						lPosition[0] = lPosition[1] = (POSITION)-1;
						break;
					}
					continue;
				}
			}
			break;
		}
		if (!lPosition[0] && !lPosition[1])
		{
			for (lPosition[0] = pMimicsGroup->m_pItemList->GetStartPosition(), lPosition[1] = m_pItemList->GetStartPosition(); lPosition[0] && lPosition[1]; )
			{
				if ((pMimicsItem[0] = (CMimicsItem *)pMimicsGroup->m_pItemList->GetNextItem(lPosition[0])))
				{
					if ((pMimicsItem[1] = (CMimicsItem *)m_pItemList->GetNextItem(lPosition[1])))
					{
						pMimicsItem[1]->Copy(pMimicsItem[0], bAll);
						continue;
					}
				}
			}
			return CMimicsItem::Copy(pItem, bAll);
		}
		for (lPosition[0] = pMimicsGroup->m_pItemList->GetStartPosition(), RemoveAllItems(); lPosition[0] && lPosition[0] != (POSITION)-1; )
		{
			if ((pMimicsItem[0] = (CMimicsItem *)pMimicsGroup->m_pItemList->GetNextItem(lPosition[0])))
			{
				if ((pMimicsItem[1] = CMimicsItem::AllocateFromItem(pMimicsItem[0])))
				{
					if (pMimicsItem[1]->Copy(pMimicsItem[0], bAll))
					{
						pMimicsItem[1]->SetItemContainer(this);
						m_pItemList->AddItem(pMimicsItem[1]);
						continue;
					}
					delete pMimicsItem[1];
				}
			}
			lPosition[0] = (POSITION)-1;
			break;
		}
		return((!lPosition[0]) ? CMimicsItem::Copy(pItem, bAll) : FALSE);
	}
	return FALSE;
}

BOOL CMimicsGroup::Compare(CONST CMimicsItem *pItem, BOOL bAll) CONST
{
	POSITION  lPosition[2];
	CMimicsItem  *pMimicsItem[2];
	CMimicsGroup  *pMimicsGroup;

	for (lPosition[0] = (pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup))) ? (((pMimicsGroup = (CMimicsGroup *)pItem)->GetItemCount() == GetItemCount()) ? pMimicsGroup->m_pItemList->GetStartPosition() : (POSITION)-1) : (POSITION)-1, lPosition[1] = (lPosition[0] && lPosition[0] != (POSITION)-1) ? m_pItemList->GetStartPosition() : (POSITION)-1; lPosition[0] && lPosition[0] != (POSITION)-1 && lPosition[1] && lPosition[1] != (POSITION)-1; )
	{
		if ((pMimicsItem[0] = (CMimicsItem *)pMimicsGroup->m_pItemList->GetNextItem(lPosition[0])))
		{
			if ((pMimicsItem[1] = (CMimicsItem *)m_pItemList->GetNextItem(lPosition[1])))
			{
				if (!pMimicsItem[0]->Compare(pMimicsItem[1], bAll))
				{
					lPosition[0] = lPosition[1] = (POSITION)-1;
					break;
				}
				continue;
			}
		}
		lPosition[0] = lPosition[1] = (POSITION)-1;
		break;
	}
	return((!lPosition[0] && !lPosition[1]) ? CMimicsItem::Compare(pItem, bAll) : FALSE);
}

BOOL CMimicsGroup::SaveAsStandardFile(LPCTSTR pszFileName)
{
	DWORD  cbData;
	CFileEx  cFile;
	CByteArray  nFileData;

	if (Map(nFileData))
	{
		if (cFile.Open(pszFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
		{
			if (WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &cbData, (LPOVERLAPPED)NULL) && cbData == (DWORD)nFileData.GetSize())
			{
				cFile.Close();
				return TRUE;
			}
			cFile.Close();
			cFile.Remove(pszFileName);
		}
	}
	return FALSE;
}

BOOL CMimicsGroup::LoadAsStandardFile(LPCTSTR pszFileName)
{
	DWORD  cbData;
	CFileEx  cFile;
	CByteArray  nFileData;

	if (cFile.Open(pszFileName, CFile::modeRead | CFile::shareDenyNone))
	{
		for (nFileData.SetSize((cbData = GetFileSize(cFile.m_hFile, (LPDWORD)NULL))); nFileData.GetSize() == cbData && ReadFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &cbData, (LPOVERLAPPED)NULL) && cbData == (DWORD)nFileData.GetSize(); )
		{
			if (Unmap(nFileData))
			{
				cFile.Close();
				return TRUE;
			}
			break;
		}
		cFile.Close();
	}
	return FALSE;
}

BOOL CMimicsGroup::SaveAsMetafile(LPCTSTR pszFileName)
{
	CRect  rGroup;
	CClientDC  cDC(NULL);
	CMetaFileDC  cMetaDC[2];
	HENHMETAFILE  hMetaFile;
	ENHMETAHEADER  sMetaFile;

	if (cMetaDC[0].CreateEnhanced(&cDC, (LPCTSTR)NULL, (LPCRECT)NULL, (LPCTSTR)NULL) && cMetaDC[1].CreateEnhanced(&cDC, CFileEx::TranslateToUNCName(pszFileName), (LPCRECT)NULL, GetName()))
	{
		cMetaDC[0].SetAttribDC(cDC.GetSafeHdc());
		cMetaDC[1].SetAttribDC(cDC.GetSafeHdc());
		if ((hMetaFile = (Draw(&cMetaDC[0])) ? cMetaDC[0].CloseEnhanced() : (HENHMETAFILE)NULL))
		{
			if (GetEnhMetaFileHeader(hMetaFile, sizeof(sMetaFile), &sMetaFile))
			{
				rGroup.left = sMetaFile.rclBounds.left;
				rGroup.top = sMetaFile.rclBounds.top;
				rGroup.right = sMetaFile.rclBounds.right;
				rGroup.bottom = sMetaFile.rclBounds.bottom;
				rGroup.OffsetRect(-rGroup.TopLeft());
				if (cMetaDC[1].PlayMetaFile(hMetaFile, rGroup))
				{
					DeleteEnhMetaFile(cMetaDC[1].CloseEnhanced());
					DeleteEnhMetaFile(hMetaFile);
					return TRUE;
				}
				DeleteEnhMetaFile(cMetaDC[1].CloseEnhanced());
			}
			DeleteEnhMetaFile(hMetaFile);
			return FALSE;
		}
		DeleteEnhMetaFile(cMetaDC[0].CloseEnhanced());
	}
	return FALSE;
}

BOOL CMimicsGroup::SaveAsBitmap(LPCTSTR pszFileName)
{
	CDC  cMemDC;
	BYTE  *pBits;
	CRect  rGroup;
	DWORD  cbBytes;
	CFileEx  cFile;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CClientDC  cDC(NULL);
	CMetaFileDC  cMetaDC;
	BITMAPINFO  sBitmapInfo;
	BITMAPINFO  *pBitmapInfo;
	HENHMETAFILE  hMetaFile;
	ENHMETAHEADER  sMetaFile;
	BITMAPFILEHEADER  sBitmapHeader;

	if (cMemDC.CreateCompatibleDC(&cDC))
	{
		if (cMetaDC.CreateEnhanced(&cMemDC, (LPCTSTR)NULL, (LPCRECT)NULL, (LPCTSTR)NULL))
		{
			for (cMetaDC.SetAttribDC(cMemDC.GetSafeHdc()); TRUE; )
			{
				Draw(&cMetaDC);
				break;
			}
			if ((hMetaFile = cMetaDC.CloseEnhanced()))
			{
				if (GetEnhMetaFileHeader(hMetaFile, sizeof(sMetaFile), &sMetaFile))
				{
					rGroup.left = sMetaFile.rclBounds.left;
					rGroup.top = sMetaFile.rclBounds.top;
					rGroup.right = sMetaFile.rclBounds.right;
					rGroup.bottom = sMetaFile.rclBounds.bottom;
					rGroup.OffsetRect(-rGroup.TopLeft());
					if (cBitmap.CreateCompatibleBitmap(&cDC, rGroup.Width(), rGroup.Height()))
					{
						if ((pOldBitmap = (CBitmap *)cMemDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
						{
							cMemDC.FillRect(rGroup, CBrush::FromHandle(GetSysColorBrush(COLOR_WINDOW)));
							if (cMemDC.PlayMetaFile(hMetaFile, rGroup))
							{
								sBitmapInfo.bmiHeader.biBitCount = 0;
								sBitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
								if (GetDIBits(cMemDC.GetSafeHdc(), (HBITMAP)cBitmap.GetSafeHandle(), 0, rGroup.Height(), (LPVOID)NULL, &sBitmapInfo, DIB_RGB_COLORS))
								{
									if ((pBitmapInfo = (BITMAPINFO *)GlobalAlloc(GPTR, sizeof(BITMAPINFOHEADER) + max(sBitmapInfo.bmiHeader.biClrUsed, 256)*sizeof(RGBQUAD))))
									{
										CopyMemory(&pBitmapInfo->bmiHeader, &sBitmapInfo.bmiHeader, sizeof(BITMAPINFOHEADER));
										if ((pBits = (LPBYTE)GlobalAlloc(GPTR, sBitmapInfo.bmiHeader.biSizeImage)))
										{
											if (GetDIBits(cMemDC.GetSafeHdc(), (HBITMAP)cBitmap.GetSafeHandle(), 0, (UINT)pBitmapInfo->bmiHeader.biHeight, pBits, pBitmapInfo, DIB_RGB_COLORS))
											{
												sBitmapHeader.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) + pBitmapInfo->bmiHeader.biSize + sizeof(RGBQUAD) + pBitmapInfo->bmiHeader.biSizeImage);
												sBitmapHeader.bfOffBits = (DWORD)(sizeof(BITMAPFILEHEADER) + pBitmapInfo->bmiHeader.biSize + sizeof(RGBQUAD));
												sBitmapHeader.bfType = 0x4d42;
												sBitmapHeader.bfReserved1 = 0;
												sBitmapHeader.bfReserved2 = 0;
												if (cFile.Open(pszFileName, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone))
												{
													if (WriteFile(cFile.m_hFile, &sBitmapHeader, sizeof(BITMAPFILEHEADER), &cbBytes, (LPOVERLAPPED)NULL))
													{
														if (WriteFile(cFile.m_hFile, pBitmapInfo, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD), &cbBytes, (LPOVERLAPPED)NULL))
														{
															if (WriteFile(cFile.m_hFile, pBits, pBitmapInfo->bmiHeader.biSizeImage, &cbBytes, (LPOVERLAPPED)NULL))
															{
																cMemDC.SelectObject(pOldBitmap);
																DeleteEnhMetaFile(hMetaFile);
																GlobalFree(pBitmapInfo);
																GlobalFree(pBits);
																cBitmap.DeleteObject();
																cMemDC.DeleteDC();
																cFile.Close();
																return TRUE;
															}
														}
													}
													cFile.Close();
													cFile.Remove(pszFileName);
												}
											}
											GlobalFree(pBits);
										}
										GlobalFree(pBitmapInfo);
									}
								}
							}
							cMemDC.SelectObject(pOldBitmap);
						}
						cBitmap.DeleteObject();
					}
				}
				DeleteEnhMetaFile(hMetaFile);
			}
		}
		cMemDC.DeleteDC();
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CMimicsGroup, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsGroup)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroup commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsGroups

CMimicsGroups::CMimicsGroups() : CPtrArray()
{
	return;
}

CMimicsGroups::~CMimicsGroups()
{
	RemoveAll();
}

INT CMimicsGroups::Add(CMimicsGroup *pMimicsGroup)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pMimicsGroup->GetName(), TRUE)) >= 0) InsertAt(nIndex, pMimicsGroup, 1);
	return nIndex;
}

INT CMimicsGroups::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CMimicsGroup *CMimicsGroups::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMimicsGroup *)CPtrArray::GetAt(nIndex) : (CMimicsGroup *)NULL);
}

CMimicsGroup *CMimicsGroups::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMimicsGroup *)CPtrArray::GetAt(nIndex) : (CMimicsGroup *)NULL);
}

VOID CMimicsGroups::RemoveAll()
{
	INT  nGroup;
	INT  nGroups;

	for (nGroup = 0, nGroups = (INT)GetSize(); nGroup < nGroups; nGroup++)
	{
		delete GetAt(nGroup);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CMimicsGroups::Copy(CONST CMimicsGroups *pMimicsGroups, BOOL bAll)
{
	INT  nGroup;
	INT  nGroups;
	CMimicsGroup  *pGroup;

	for (nGroup = 0, nGroups = (INT)pMimicsGroups->GetSize(), RemoveAll(); nGroup < nGroups; nGroup++)
	{
		if ((pGroup = new CMimicsGroup) != (CMimicsGroup *)NULL)
		{
			if (pGroup->Copy(pMimicsGroups->GetAt(nGroup), bAll))
			{
				InsertAt(nGroup, pGroup, 1);
				continue;
			}
			delete pGroup;
		}
		break;
	}
	return((nGroup == nGroups) ? TRUE : FALSE);
}

BOOL CMimicsGroups::Compare(CONST CMimicsGroups *pMimicsGroups, BOOL bAll) CONST
{
	INT  nGroup;
	INT  nGroups;

	for (nGroup = 0, nGroups = (pMimicsGroups->GetSize() == GetSize()) ? (INT)GetSize() : -1; nGroup < nGroups; nGroup++)
	{
		if (!pMimicsGroups->GetAt(nGroup)->Compare(GetAt(nGroup), bAll)) break;
		continue;
	}
	return((nGroup == nGroups) ? TRUE : FALSE);
}

BOOL CMimicsGroups::Map(CByteArray &nData) CONST
{
	INT  nGroup;
	INT  nGroups;
	INT  cbGroup;
	CByteArray  nGroupData;
	CMimicsGroup  *pGroup;

	for (nGroup = 0, nGroups = (INT)GetSize(), nData.SetSize((nGroups + 1)*sizeof(INT)), CopyMemory(nData.GetData(), &nGroups, sizeof(nGroups)); nGroup < nGroups; nGroup++)
	{
		if ((pGroup = GetAt(nGroup)) != (CMimicsGroup *)NULL  &&  pGroup->Map(nGroupData) && nData.Append(nGroupData) >= 0)
		{
			CopyMemory(nData.GetData() + (nGroup + 1)*sizeof(INT), &(cbGroup = (INT)nGroupData.GetSize()), sizeof(cbGroup));
			continue;
		}
		break;
	}
	return((nGroup == nGroups) ? TRUE : FALSE);
}

BOOL CMimicsGroups::Unmap(CONST CByteArray &nData)
{
	INT  nGroup;
	INT  nGroups;
	INT  cbGroup;
	INT  cbGroups;
	CByteArray  nGroupData;
	CMimicsGroup  *pGroup;

	for (nGroup = 0, CopyMemory(&(nGroups = 0), nData.GetData(), (nData.GetSize() >= sizeof(INT)) ? sizeof(INT) : 0), RemoveAll(), cbGroups = (nGroups + 1)*sizeof(INT); nGroup < nGroups && cbGroups <= nData.GetSize(); nGroup++, cbGroups += cbGroup)
	{
		for (CopyMemory(&cbGroup, nData.GetData() + (nGroup + 1)*sizeof(INT), sizeof(cbGroup)), nGroupData.SetSize(max(min(cbGroup, nData.GetSize() - cbGroups), 0)); nGroupData.GetSize() >= 0; )
		{
			CopyMemory(nGroupData.GetData(), nData.GetData() + cbGroups, nGroupData.GetSize());
			break;
		}
		if ((pGroup = new CMimicsGroup))
		{
			if (pGroup->Unmap(nGroupData) && Add(pGroup) >= 0) continue;
			delete pGroup;
		}
		break;
	}
	return((nGroup == nGroups) ? TRUE : FALSE);
}

INT CMimicsGroups::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CMimicsGroup  *pGroup;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pGroup = GetAt(nIndex[0]))) ? ((nIndex[1] = (pGroup->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pGroup = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pGroup->GetName() == pszName) || (bInsert && (((pGroup = GetAt(max(nIndex[0] - 1, 0))) && pGroup->GetName() != pszName && (pGroup = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pGroup->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDUndoItem

CMMDUndoItem::CMMDUndoItem() : CObject()
{
	m_nIndex = -1;
	m_pDocument[0] = new CMMDDocument;
	m_pDocument[1] = new CMMDDocument;
}

CMMDUndoItem::~CMMDUndoItem()
{
	delete m_pDocument[0];
	delete m_pDocument[1];
}

BOOL CMMDUndoItem::SetInfo(CONST CMMDDocument *pDocument, CONST CMMDDocument *pOldDocument, INT nIndex)
{
	m_nIndex = nIndex;
	return((m_pDocument[0]->Copy(pDocument, TRUE) && m_pDocument[1]->Copy(pOldDocument, TRUE)) ? TRUE : FALSE);
}

INT CMMDUndoItem::GetInfo(CMMDDocument *pDocument, CMMDDocument *pOldDocument) CONST
{
	return((pDocument->Copy(m_pDocument[0], TRUE) && pOldDocument->Copy(m_pDocument[1], TRUE)) ? m_nIndex : -1);
}

BOOL CMMDUndoItem::Copy(CONST CMMDUndoItem *pItem)
{
	m_nIndex = pItem->m_nIndex;
	return((pItem->m_pDocument[0]->Copy(m_pDocument[0], TRUE) && pItem->m_pDocument[1]->Copy(m_pDocument[1], TRUE)) ? TRUE : FALSE);
}

BOOL CMMDUndoItem::Compare(CONST CMMDUndoItem *pItem) CONST
{
	return((pItem->m_nIndex == m_nIndex) ? (pItem->m_pDocument[0]->Compare(m_pDocument[0], TRUE) && pItem->m_pDocument[1]->Compare(m_pDocument[1], TRUE)) : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDUndoList

CMMDUndoList::CMMDUndoList() : CPtrArray()
{
	m_pDocument = new CMMDDocument;
	m_nIndex[0] = m_nIndex[1] = -1;
	m_bLocked = 0;
}

CMMDUndoList::~CMMDUndoList()
{
	Reset();
	delete m_pDocument;
}

BOOL CMMDUndoList::Update(CONST CMMDDocument *pDocument, BOOL bReset)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex[2];
	POSITION  lPosition[2];
	CMimicsItem  *pItem[2];
	CMMDUndoItem  *pUndoItem;
	CMMDDocument  *pUndoDocument[2];

	if (!IsLocked())
	{
		if (bReset)
		{
			Reset();
			return m_pDocument->Copy(pDocument, TRUE);
		}
		if (!m_pDocument->Compare(pDocument, TRUE))
		{
			for (nItem = m_nIndex[0] + 1, nItems = (INT)GetSize(); nItem < nItems; nItem++)
			{
				delete GetAt(nItem);
				RemoveAt(nItem);
				nItems--;
				nItem--;
			}
			if ((pUndoItem = new CMMDUndoItem))
			{
				for (lPosition[0] = m_pDocument->m_docItemList.GetHeadPosition(), lPosition[1] = pDocument->m_docItemList.GetHeadPosition(), nIndex[0] = 0; lPosition[0] && lPosition[1]; nIndex[0]++)
				{
					if ((pItem[0] = (CMimicsItem *)m_pDocument->m_docItemList.GetNext(lPosition[0])))
					{
						if ((pItem[1] = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition[1])))
						{
							if (!pItem[0]->Compare(pItem[1], TRUE)) break;
							continue;
						}
					}
					break;
				}
				for (lPosition[0] = m_pDocument->m_docItemList.GetTailPosition(), lPosition[1] = pDocument->m_docItemList.GetTailPosition(), nIndex[1] = 0; lPosition[0] && lPosition[1]; nIndex[1]++)
				{
					if ((pItem[0] = (CMimicsItem *)m_pDocument->m_docItemList.GetPrev(lPosition[0])))
					{
						if ((pItem[1] = (CMimicsItem *)pDocument->m_docItemList.GetPrev(lPosition[1])))
						{
							if (!pItem[0]->Compare(pItem[1], TRUE)) break;
							continue;
						}
					}
					break;
				}
				if ((pUndoDocument[0] = new CMMDDocument))
				{
					if ((pUndoDocument[1] = new CMMDDocument))
					{
						for (nItem = 0, nItems = (INT)pDocument->m_docItemList.GetCount() - nIndex[0] - nIndex[1], lPosition[0] = pDocument->m_docItemList.FindIndex(nIndex[0]); nItem < nItems && lPosition[0]; nItem++)
						{
							if ((pItem[0] = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition[0])) != (CMimicsItem *)NULL)
							{
								if ((pItem[1] = CMimicsItem::AllocateFromItem(pItem[0])) && pItem[1]->Copy(pItem[0], TRUE))
								{
									pUndoDocument[0]->AddItem(pItem[1]);
									continue;
								}
								delete pItem[1];
							}
							lPosition[0] = (POSITION)-1;
							break;
						}
						for (nItem = 0, nItems = (INT)m_pDocument->m_docItemList.GetCount() - nIndex[0] - nIndex[1], lPosition[0] = (lPosition[0] != (POSITION)-1) ? m_pDocument->m_docItemList.FindIndex(nIndex[0]) : lPosition[0]; nItem < nItems && lPosition[0]; nItem++)
						{
							if ((pItem[0] = (CMimicsItem *)m_pDocument->m_docItemList.GetNext(lPosition[0])) != (CMimicsItem *)NULL)
							{
								if ((pItem[1] = CMimicsItem::AllocateFromItem(pItem[0])) && pItem[1]->Copy(pItem[0], TRUE))
								{
									pUndoDocument[1]->AddItem(pItem[1]);
									continue;
								}
								delete pItem[1];
							}
							lPosition[0] = (POSITION)-1;
							break;
						}
						if (pUndoItem->SetInfo(pUndoDocument[0], pUndoDocument[1], nIndex[0]) && lPosition[0] != (POSITION)-1)
						{
							if (CPtrArray::Add(pUndoItem) >= 0)
							{
								m_pDocument->Copy(pDocument, TRUE);
								m_nIndex[1] = ++m_nIndex[0] + 1;
								delete pUndoDocument[1];
								delete pUndoDocument[0];
								return TRUE;
							}
						}
						delete pUndoDocument[1];
					}
					delete pUndoDocument[0];
				}
				delete pUndoItem;
			}
		}
	}
	return FALSE;
}

BOOL CMMDUndoList::Undo(CMMDDocument *pDocument)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	POSITION  lPosition[2];
	CMimicsItem  *pItem[2];
	CMMDUndoItem  *pUndoItem;
	CMMDDocument  *pUndoDocument[2];

	if ((pUndoItem = GetAt(m_nIndex[0])))
	{
		if ((pUndoDocument[0] = new CMMDDocument))
		{
			if ((pUndoDocument[1] = new CMMDDocument))
			{
				if ((nIndex = pUndoItem->GetInfo(pUndoDocument[0], pUndoDocument[1])) >= 0)
				{
					for (nItem = 0, nItems = pUndoDocument[0]->GetItemCount(), lPosition[0] = pDocument->m_docItemList.FindIndex(nIndex); nItem < nItems && lPosition[0]; nItem++)
					{
						if ((pItem[0] = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition[0])))
						{
							delete pItem[0];
							continue;
						}
					}
					for (lPosition[0] = pUndoDocument[1]->m_docItemList.GetHeadPosition(), nItem = 0; lPosition[0]; nItem++)
					{
						if ((pItem[0] = (CMimicsItem *)pUndoDocument[1]->m_docItemList.GetNext(lPosition[0])))
						{
							if ((pItem[1] = CMimicsItem::AllocateFromItem(pItem[0], pDocument)) && pItem[1]->Copy(pItem[0], TRUE))
							{
								if ((lPosition[1] = (nIndex + nItem > 0) ? pDocument->m_docItemList.FindIndex(nIndex + nItem) : (POSITION)NULL))
								{
									pDocument->m_docItemList.InsertBefore(lPosition[1], pItem[1]);
									continue;
								}
								if ((nIndex + nItem == 0 && pDocument->m_docItemList.AddHead(pItem[1])) || (nIndex + nItem > 0 && pDocument->m_docItemList.AddTail(pItem[1]))) continue;
							}
							delete pItem[1];
						}
						lPosition[0] = (POSITION)-1;
						break;
					}
					if (lPosition[0] != (POSITION)-1)
					{
						m_pDocument->Copy(pDocument, TRUE);
						delete pUndoDocument[1];
						delete pUndoDocument[0];
						m_nIndex[1] = m_nIndex[0];
						m_nIndex[0]--;
						return TRUE;
					}
				}
				delete pUndoDocument[1];
			}
			delete pUndoDocument[0];
		}
	}
	return FALSE;
}

BOOL CMMDUndoList::Redo(CMMDDocument *pDocument)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	POSITION  lPosition[2];
	CMimicsItem  *pItem[2];
	CMMDUndoItem  *pUndoItem;
	CMMDDocument  *pUndoDocument[2];

	if ((pUndoItem = GetAt(m_nIndex[1])))
	{
		if ((pUndoDocument[0] = new CMMDDocument))
		{
			if ((pUndoDocument[1] = new CMMDDocument))
			{
				if ((nIndex = pUndoItem->GetInfo(pUndoDocument[0], pUndoDocument[1])) >= 0)
				{
					for (nItem = 0, nItems = pUndoDocument[1]->GetItemCount(), lPosition[0] = pDocument->m_docItemList.FindIndex(nIndex); nItem < nItems && lPosition[0]; nItem++)
					{
						if ((pItem[0] = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition[0])))
						{
							delete pItem[0];
							continue;
						}
					}
					for (lPosition[0] = pUndoDocument[0]->m_docItemList.GetHeadPosition(), nItem = 0; lPosition[0]; nItem++)
					{
						if ((pItem[0] = (CMimicsItem *)pUndoDocument[0]->m_docItemList.GetNext(lPosition[0])))
						{
							if ((pItem[1] = CMimicsItem::AllocateFromItem(pItem[0], pDocument)) && pItem[1]->Copy(pItem[0], TRUE))
							{
								if ((lPosition[1] = (nIndex + nItem > 0) ? pDocument->m_docItemList.FindIndex(nIndex + nItem) : (POSITION)NULL))
								{
									pDocument->m_docItemList.InsertBefore(lPosition[1], pItem[1]);
									continue;
								}
								if ((nIndex + nItem == 0 && pDocument->m_docItemList.AddHead(pItem[1])) || (nIndex + nItem > 0 && pDocument->m_docItemList.AddTail(pItem[1]))) continue;
							}
							delete pItem[1];
						}
						lPosition[0] = (POSITION)-1;
						break;
					}
					if (lPosition[0] != (POSITION)-1)
					{
						m_pDocument->Copy(pDocument, TRUE);
						delete pUndoDocument[1];
						delete pUndoDocument[0];
						m_nIndex[0] = m_nIndex[1];
						m_nIndex[1]++;
						return TRUE;
					}
				}
				delete pUndoDocument[1];
			}
			delete pUndoDocument[0];
		}
	}
	return FALSE;
}

BOOL CMMDUndoList::CanUndo() CONST
{
	return((m_nIndex[0] >= 0) ? TRUE : FALSE);
}

BOOL CMMDUndoList::CanRedo() CONST
{
	return((m_nIndex[1] < GetSize() && GetSize() > 0) ? TRUE : FALSE);
}

CMMDUndoItem *CMMDUndoList::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMMDUndoItem *)CPtrArray::GetAt(nIndex) : (CMMDUndoItem *)NULL);
}

CMMDUndoItem *CMMDUndoList::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMMDUndoItem *)CPtrArray::GetAt(nIndex) : (CMMDUndoItem *)NULL);
}

VOID CMMDUndoList::Reset()
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (INT)GetSize(), m_nIndex[0] = m_nIndex[1] = -1; nItem < nItems; nItem++)
	{
		delete GetAt(nItem);
		RemoveAt(nItem);
		nItems--;
		nItem--;
	}
}

VOID CMMDUndoList::Lock()
{
	m_bLocked++;
}

BOOL CMMDUndoList::IsLocked() CONST
{
	return((m_bLocked > 0) ? TRUE : FALSE);
}

VOID CMMDUndoList::Unlock()
{
	m_bLocked--;
}


/////////////////////////////////////////////////////////////////////////////
// CMMDSaveDialog dialog

IMPLEMENT_DYNCREATE(CMMDSaveDialog, CDisplayDialog)

CMMDSaveDialog::CMMDSaveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDSaveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDSaveDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CMMDSaveDialog::IDD);
}

BOOL CMMDSaveDialog::Initialize()
{
	m_pLayouts.Copy(GetDatabase()->GetMMDs());
	return TRUE;
}

CMMDWnd *CMMDSaveDialog::GetParentDisplay() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CMMDSaveDialog::EnumMMDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	CString  szItem;
	CStringTools  cStringTools;
	CMMDLayout  *pMMDLayout;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(), nDigits = 0; nLayout < nLayouts; nLayout++)
	{
		nDigits = ((pMMDLayout = m_pLayouts.GetAt(nLayout))) ? max(pMMDLayout->GetName().GetLength(), nDigits) : nDigits;
		continue;
	}
	for (nLayout = 0; nLayout < nLayouts; nLayout++)
	{
		if ((pMMDLayout = m_pLayouts.GetAt(nLayout)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_MMDSAVEDIALOG_DIRECTORYTITLEITEM_NUMBER); )
				{
					szItem = cStringTools.ConvertUIntToPaddedString(_ttoi(pMMDLayout->GetName()), nDigits);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_MMDSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pMMDLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_MMD_SAVE_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_MMD_SAVE_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_MMD_SAVE_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_SAVE_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_SAVE_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_MMD_SAVE_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CMMDSaveDialog::FindMMD(LPCTSTR pszNumber) CONST
{
	INT  nLayout;
	INT  nLayouts;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(); nLayout < nLayouts; nLayout++)
	{
		if (_ttoi(m_pLayouts.GetAt(nLayout)->GetName()) == _ttoi(pszNumber)) break;
		continue;
	}
	return((nLayout < nLayouts) ? TRUE : FALSE);
}

BOOL CMMDSaveDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_MMD_SAVE_NUMBER)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMD_SAVE_TITLE)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CMMDSaveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDSaveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDSaveDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDSaveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDSaveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_SAVE_HELP, OnHelp)
	ON_EN_CHANGE(IDC_MMD_SAVE_TITLE, OnEditchangeTitle)
	ON_EN_CHANGE(IDC_MMD_SAVE_NUMBER, OnEditchangeNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDSaveDialog message handlers

BOOL CMMDSaveDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_MMD_SAVE_NUMBER)->GetWindowRect(rColumns[0]);
	GetDlgItem(IDC_MMD_SAVE_DIRECTORY)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_MMDSAVEDIALOG_DIRECTORYTITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_MMDSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[0].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[1].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_MMD_SAVE_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumMMDs();
	SendDlgItemMessage(IDC_MMD_SAVE_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_MMD_SAVE_NUMBER, EM_LIMITTEXT, cStringTools.ConvertUIntToString(-1).GetLength(), (LPARAM)NULL);
	SendDlgItemMessage(IDC_MMD_SAVE_TITLE, EM_SETSEL, 0, (LPARAM)-1);
	GetDlgItem(IDC_MMD_SAVE_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_MMD_SAVE_NUMBER)->SetWindowText(GetParentDisplay()->GetName());
	GetDlgItem(IDC_MMD_SAVE_TITLE)->SetWindowText(GetParentDisplay()->GetTitle());
	GetDlgItem(IDC_MMD_SAVE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMD_SAVE_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_SAVE_DATABASE)->EnableWindow();
	GetDlgItem(IDC_MMD_SAVE_TITLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_SAVE_TITLE)->EnableWindow();
	GetDlgItem(IDC_MMD_SAVE_NUMBER_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_SAVE_NUMBER)->EnableWindow();
	GetDlgItem(IDC_MMD_SAVE_TITLE)->SetFocus();
	return FALSE;
}

BOOL CMMDSaveDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nColumn;
	INT  nColumns;
	BOOL  bNumber;
	CString  szNumber;
	CStringTools  cStringTools;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_MMD_SAVE_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (pNotifyListView->uNewState & LVIS_SELECTED)
			{
				for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
				{
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDSAVEDIALOG_DIRECTORYTITLEITEM_NUMBER))
					{
						GetDlgItem(IDC_MMD_SAVE_NUMBER)->SetWindowText(cStringTools.ConvertIntToString(_ttoi(Listview_GetText(GetDlgItem(IDC_MMD_SAVE_DIRECTORY), pNotifyListView->iItem, nColumn))));
						continue;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
					{
						GetDlgItem(IDC_MMD_SAVE_TITLE)->SetWindowText(Listview_GetText(GetDlgItem(IDC_MMD_SAVE_DIRECTORY), pNotifyListView->iItem, nColumn));
						continue;
					}
				}
				GetDlgItem(IDC_MMD_SAVE_NUMBER)->GetWindowText(szNumber);
				GetDlgItem(IDC_MMD_SAVE_COMMENT_STATIC)->ShowWindow(((bNumber = FindMMD(szNumber) && GetParentDisplay()->GetName() != szNumber)) ? SW_SHOW : SW_HIDE);
				GetDlgItem(IDC_MMD_SAVE_COMMENT)->ShowWindow((bNumber) ? SW_SHOW : SW_HIDE);
				GetDlgItem(IDC_MMD_SAVE_COMMENT_STATIC)->EnableWindow(bNumber);
				GetDlgItem(IDC_MMD_SAVE_COMMENT)->EnableWindow(bNumber);
			}
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			if (!GetDlgItem(IDC_MMD_SAVE_COMMENT)->IsWindowVisible())
			{
				OnOK();
				return TRUE;
			}
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CMMDSaveDialog::OnEditchangeTitle()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSaveDialog::OnEditchangeNumber()
{
	BOOL  bNumber;
	CString  szNumber;

	GetDlgItem(IDC_MMD_SAVE_NUMBER)->GetWindowText(szNumber);
	GetDlgItem(IDC_MMD_SAVE_COMMENT_STATIC)->ShowWindow(((bNumber = FindMMD(szNumber) && GetParentDisplay()->GetName() != szNumber)) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_MMD_SAVE_COMMENT)->ShowWindow((bNumber) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_MMD_SAVE_COMMENT_STATIC)->EnableWindow(bNumber);
	GetDlgItem(IDC_MMD_SAVE_COMMENT)->EnableWindow(bNumber);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSaveDialog::OnOK()
{
	CString  szTitle;
	CString  szNumber;
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_SAVE_NUMBER)->GetWindowText(szNumber);
	GetDlgItem(IDC_MMD_SAVE_TITLE)->GetWindowText(szTitle);
	GetParentDisplay()->SetName(cStringTools.ConvertIntToString(_ttoi(szNumber)));
	GetParentDisplay()->SetTitle(szTitle);
	CDisplayDialog::OnOK();
}

BOOL CMMDSaveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDSAVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDSaveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDSAVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDOpenDialog dialog

IMPLEMENT_DYNCREATE(CMMDOpenDialog, CLocaleDialog)

CMMDOpenDialog::CMMDOpenDialog(CWnd *pParentWnd) : CLocaleDialog(CMMDOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CMMDOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMMDOpenDialog::Initialize()
{
	m_pLayouts.Copy(GetDatabase()->GetMMDs());
	return TRUE;
}

VOID CMMDOpenDialog::EnumMMDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	CString  szItem;
	CStringTools  cStringTools;
	CMMDLayout  *pMMDLayout;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(), nDigits = 0; nLayout < nLayouts; nLayout++)
	{
		nDigits = ((pMMDLayout = m_pLayouts.GetAt(nLayout))) ? max(pMMDLayout->GetName().GetLength(), nDigits) : nDigits;
		continue;
	}
	for (nLayout = 0; nLayout < nLayouts; nLayout++)
	{
		if ((pMMDLayout = m_pLayouts.GetAt(nLayout)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_MMDOPENDIALOG_DIRECTORYTITLEITEM_NUMBER); )
				{
					szItem = cStringTools.ConvertUIntToPaddedString(_ttoi(pMMDLayout->GetName()), nDigits);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_MMDOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pMMDLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_MMD_OPEN_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_MMD_OPEN_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_MMD_OPEN_DIRECTORY), 0);
	GetDlgItem(IDC_MMD_OPEN_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_OPEN_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_MMD_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CMMDOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_MMD_OPEN_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void CMMDOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDOpenDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CMMDOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDOpenDialog message handlers

BOOL CMMDOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_MMD_OPEN_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_MMDOPENDIALOG_DIRECTORYTITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_MMDOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_MMD_OPEN_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 7; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_MMD_OPEN_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumMMDs();
	GetDlgItem(IDC_MMD_OPEN_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_MMD_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMD_OPEN_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_OPEN_DATABASE)->EnableWindow();
	GetDlgItem(IDC_MMD_OPEN_DIRECTORY)->SetFocus();
	return FALSE;
}

BOOL CMMDOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_MMD_OPEN_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			OnOK();
			return TRUE;
		}
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void CMMDOpenDialog::OnOK()
{
	INT  nColumn;
	INT  nColumns;
	INT  nDisplay;
	INT  nDisplays;
	CString  szTitle;
	CString  szNumber;
	CString  szMessage;
	CMMDWnd  *pMMDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDOPENDIALOG_DIRECTORYTITLEITEM_NUMBER))
		{
			szNumber = Listview_GetText(GetDlgItem(IDC_MMD_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_MMD_OPEN_DIRECTORY)), nColumn);
			continue;
		}
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
		{
			szTitle = Listview_GetText(GetDlgItem(IDC_MMD_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_MMD_OPEN_DIRECTORY)), nColumn);
			continue;
		}
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_MMD)
		{
			if ((pMMDWnd = (CMMDWnd *)pDisplayWnd)->GetName() == szNumber)
			{
				pMMDWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		if ((pMMDWnd = new CMMDWnd(szNumber)))
		{
			if (pMMDWnd->Create(GetMainWnd()))
			{
				EndDialog(IDOK);
				return;
			}
		}
		szMessage.Format(STRING(IDS_MMD_FAILURE_LOAD), (LPCTSTR)szTitle);
		ShowMessage(szMessage);
	}
	EndDialog(IDOK);
}

void CMMDOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CMMDOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDImportDialog dialog

IMPLEMENT_DYNCREATE(CMMDImportDialog, CLocaleDialog)

CMMDImportDialog::CMMDImportDialog(CWnd *pParentWnd) : CLocaleDialog(CMMDImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CMMDImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CMMDImportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

VOID CMMDImportDialog::EnumMMDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szItem;
	CString  szFileName;
	CByteArray  cFileBuffer;
	CFileFindEx  cFileFind;
	CStringTools  cStringTools;
	CMMDLayout  *pMMDLayout;

	SendDlgItemMessage(IDC_MMD_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_MMD_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				for (nLayout = 0, nLayouts = (m_pLayouts.Unmap(cFileBuffer)) ? (INT)m_pLayouts.GetSize() : 0, nDigits = 0; nLayout < nLayouts; nLayout++)
				{
					nDigits = ((pMMDLayout = m_pLayouts.GetAt(nLayout))) ? max(pMMDLayout->GetName().GetLength(), nDigits) : nDigits;
					continue;
				}
				for (nLayout = 0; nLayout < nLayouts; nLayout++)
				{
					if ((pMMDLayout = m_pLayouts.GetAt(nLayout)))
					{
						for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_MMDIMPORTDIALOG_DIRECTORYTITLEITEM_NUMBER); )
							{
								szItem = cStringTools.ConvertUIntToPaddedString(_ttoi(pMMDLayout->GetName()), nDigits);
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_MMDIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
							{
								szItem = pMMDLayout->GetTitle();
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_MMD_IMPORT_DIRECTORY), nLayout, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_MMD_IMPORT_DIRECTORY), nLayout, nColumn, szItem);
						}
					}
				}
				break;
			}
			cFile.Close();
		}
		cFileFind.Close();
		break;
	}
	GetDlgItem(IDC_MMD_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_MMD_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CMMDImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_MMD_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMD_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_MMD_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_MMD_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CMMDImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDImportDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CMMDImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_MMD_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_MMD_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_MMD_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_MMD_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER, OnEditchangeNumber)
	ON_EN_CHANGE(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDImportDialog message handlers

BOOL CMMDImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_MMD_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_MMDIMPORTDIALOG_DIRECTORYTITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_MMDIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_MMD_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_MMD_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_MMD_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_MMD_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CMMDImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_MMD_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_MMD_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_MMD_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM)->EnableWindow();
			}
			else
			{
				CheckDlgButton(IDC_MMD_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_MMD_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER)->EnableWindow(FALSE);
				GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
			}
			GetDlgItem(IDOK)->EnableWindow(Check());
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			OnOK();
			return TRUE;
		}
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void CMMDImportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_MMD_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_MMD_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumMMDs();
	}
	SendDlgItemMessage(IDC_MMD_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_MMD_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDImportDialog::OnDefault()
{
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDImportDialog::OnCustom()
{
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDImportDialog::OnEditchangeFileName()
{
	EnumMMDs();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDImportDialog::OnEditchangeNumber()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDImportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDImportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nLayout;
	INT  nLayouts;
	CMMDWnd  cMMDWnd;
	CString  szTitle;
	CString  szNumber;
	CPtrArray  pLayoutIDs;
	CUIntArray  nLayoutIDs;
	CMMDLayout  *pLayout[2];
	CMMDLayouts  pLayouts;
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_MMD_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_MMD_IMPORT_DIRECTORY), nLayout))
		{
			delete m_pLayouts.GetAt(nLayout);
			m_pLayouts.SetAt(nLayout, NULL);
		}
	}
	for (nLayout = 0, nLayouts = (pLayouts.Copy(GetDatabase()->GetMMDs())) ? nLayouts : -1; nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pLayouts.GetAt(nLayout)))
		{
			if (IsDlgButtonChecked(IDC_MMD_IMPORT_TYPE_CUSTOM))
			{
				GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_NUMBER)->GetWindowText(szNumber);
				GetDlgItem(IDC_MMD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szTitle);
				pLayout[0]->SetName(szNumber);
				pLayout[0]->SetTitle(szTitle);
			}
			if ((pLayout[1] = pLayouts.GetAt((nIndex = pLayouts.Find(pLayout[0]->GetName())))))
			{
				if (pLayout[1]->Copy(pLayout[0]))
				{
					pLayoutIDs.Add(pLayout[1]);
					nLayoutIDs.Add(nIndex);
					continue;
				}
				break;
			}
			if ((pLayout[1] = new CMMDLayout))
			{
				if (pLayout[1]->Copy(pLayout[0]))
				{
					if ((nIndex = pLayouts.Add(pLayout[1])) >= 0)
					{
						pLayoutIDs.Add(pLayout[1]);
						nLayoutIDs.Add(-(nIndex + 1));
						continue;
					}
				}
				delete pLayout[1];
			}
			break;
		}
		m_pLayouts.RemoveAt(nLayout);
		nLayouts--;
		nLayout--;
	}
	for (; nLayout == nLayouts; )
	{
		if (GetDatabase()->GetMMDs()->Copy(&pLayouts) && GetDatabase()->Save(DATABASE_COMPONENT_MMD))
		{
			for (nItem = 0, nItems = (INT)pLayoutIDs.GetSize(); nItem < nItems; nItem++)
			{
				if ((pLayout[0] = (CMMDLayout *)pLayoutIDs.GetAt(nItem)))
				{
					cMMDWnd.SetName(pLayout[0]->GetName());
					cMMDWnd.SetTitle(pLayout[0]->GetTitle());
					UpdateDatabase(&cMMDWnd, (INT)nLayoutIDs.GetAt(nItem));
					continue;
				}
			}
			if (nItem == nItems) break;
		}
		nLayouts = -1;
		break;
	}
	for (; nLayout != nLayouts; )
	{
		ShowMessage((SendDlgItemMessage(IDC_MMD_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_MMDDIRECTORY_IMPORT_FAILURE : SYSTEM_WARNING_MMD_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CMMDImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CMMDImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDExportDialog dialog

IMPLEMENT_DYNCREATE(CMMDExportDialog, CLocaleDialog)

CMMDExportDialog::CMMDExportDialog(CWnd *pParentWnd) : CLocaleDialog(CMMDExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CMMDExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CMMDExportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

BOOL CMMDExportDialog::EnumMMDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	CString  szItem;
	CStringTools  cStringTools;
	CMMDLayout  *pMMDLayout;

	for (nLayout = 0, nLayouts = GetDatabase()->EnumMMDs(m_pLayouts, FALSE), nDigits = 0; nLayout < nLayouts; nLayout++)
	{
		nDigits = ((pMMDLayout = m_pLayouts.GetAt(nLayout))) ? max(pMMDLayout->GetName().GetLength(), nDigits) : nDigits;
		continue;
	}
	for (nLayout = 0; nLayout < nLayouts; nLayout++)
	{
		if ((pMMDLayout = m_pLayouts.GetAt(nLayout)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_MMDEXPORTDIALOG_DIRECTORYTITLEITEM_NUMBER); )
				{
					szItem = cStringTools.ConvertUIntToPaddedString(_ttoi(pMMDLayout->GetName()), nDigits);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_MMDEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pMMDLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_MMD_EXPORT_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_MMD_EXPORT_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_MMD_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_MMD_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_MMD_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CMMDExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_MMD_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMD_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_MMD_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_MMD_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0) || IsDlgButtonChecked(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE))) ? TRUE : FALSE);
}

void CMMDExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDExportDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CMMDExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_MMD_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_MMD_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE, OnSourceCode)
	ON_BN_CLICKED(IDC_MMD_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_MMD_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER, OnEditchangeNumber)
	ON_EN_CHANGE(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDExportDialog message handlers

BOOL CMMDExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_MMD_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_MMDEXPORTDIALOG_DIRECTORYTITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_MMDEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_MMD_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_MMD_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumMMDs())
	{
		CheckDlgButton(IDC_MMD_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_MMD_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_MMD_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_MMD_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_MMD_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_MMD_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM)->EnableWindow();
		GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE)->EnableWindow();
		GetDlgItem(IDC_MMD_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL CMMDExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_MMD_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_MMD_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) > 0)
			{
				if (SendDlgItemMessage(IDC_MMD_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
				{
					GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM)->EnableWindow();
					GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE)->EnableWindow();
				}
				else
				{
					CheckDlgButton(IDC_MMD_EXPORT_TYPE_DEFAULT, TRUE);
					CheckDlgButton(IDC_MMD_EXPORT_TYPE_CUSTOM, FALSE);
					CheckDlgButton(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE, FALSE);
					GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->SetWindowText(EMPTYSTRING);
					GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
					GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
					GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->EnableWindow(FALSE);
					GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow(FALSE);
					GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
					GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
					GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE)->EnableWindow(FALSE);
				}
			}
			GetDlgItem(IDOK)->EnableWindow(Check());
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			OnOK();
			return TRUE;
		}
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void CMMDExportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_MMD_EXPORT_FILENAME, (!IsDlgButtonChecked(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE)) ? STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION) : STRING(IDS_FILEBROWSEDIALOG_DOCUMENTFILEEXTENSION), (!IsDlgButtonChecked(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE)) ? STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER) : STRING(IDS_FILEBROWSEDIALOG_DOCUMENTFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_MMD_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_MMD_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_MMD_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDExportDialog::OnDefault()
{
	CheckDlgButton(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE, FALSE);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDExportDialog::OnCustom()
{
	CheckDlgButton(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE, FALSE);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->EnableWindow();
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDExportDialog::OnSourceCode()
{
	CheckDlgButton(IDC_MMD_EXPORT_TYPE_CUSTOM, FALSE);
	CheckDlgButton(IDC_MMD_EXPORT_TYPE_DEFAULT, FALSE);
	CheckDlgButton(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE, TRUE);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDExportDialog::OnEditchangeNumber()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDExportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDExportDialog::OnOK()
{
	INT  nLayout;
	INT  nLayouts;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szTitle;
	CString  szNumber;
	CString  szFileName;
	CString  szSourceCode;
	CMMDLayout  *pLayout;
	CByteArray  nLayoutsData;
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_MMD_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_MMD_EXPORT_DIRECTORY), nLayout))
		{
			delete m_pLayouts.GetAt(nLayout);
			m_pLayouts.SetAt(nLayout, NULL);
		}
	}
	for (nLayout = 0; nLayout < nLayouts; nLayout++)
	{
		if (!m_pLayouts.GetAt(nLayout))
		{
			m_pLayouts.RemoveAt(nLayout);
			nLayouts--;
			nLayout--;
		}
	}
	if ((pLayout = (IsDlgButtonChecked(IDC_MMD_EXPORT_TYPE_CUSTOM) || IsDlgButtonChecked(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE)) ? m_pLayouts.GetAt(nLayout - 1) : (CMMDLayout *)NULL))
	{
		for (GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szTitle), GetDlgItem(IDC_MMD_EXPORT_TYPE_CUSTOM_NUMBER)->GetWindowText(szNumber), szSourceCode = pLayout->GetSourceCode(); IsDlgButtonChecked(IDC_MMD_EXPORT_TYPE_CUSTOM); )
		{
			pLayout->SetName(szNumber);
			pLayout->SetTitle(szTitle);
			break;
		}
	}
	for (; nLayout == nLayouts; )
	{
		if (m_pLayouts.Map(nLayoutsData))
		{
			for (GetDlgItem(IDC_MMD_EXPORT_FILENAME)->GetWindowText(szFileName); IsDlgButtonChecked(IDC_MMD_EXPORT_TYPE_CUSTOM_SOURCECODE); )
			{
				nLayoutsData.SetSize(szSourceCode.GetLength());
#ifndef UNICODE
				CopyMemory(nLayoutsData.GetData(), (LPCTSTR)szSourceCode, nLayoutsData.GetSize());
#else
				WideCharToMultiByte(CP_ACP, 0, szSourceCode, -1, (LPSTR)nLayoutsData.GetData(), (INT)nLayoutsData.GetSize(), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
				break;
			}
			if (cFile.Open(szFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyWrite))
			{
				if (WriteFile(cFile.m_hFile, nLayoutsData.GetData(), (DWORD)nLayoutsData.GetSize(), &dwBytes, (LPOVERLAPPED)NULL))
				{
					cFile.Close();
					break;
				}
				cFile.Close();
			}
		}
		nLayouts = -1;
		break;
	}
	if (nLayout != nLayouts) ShowMessage((SendDlgItemMessage(IDC_MMD_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_MMDDIRECTORY_EXPORT_FAILURE : SYSTEM_WARNING_MMD_IMPORT_FAILURE);
	EndDialog(IDOK);
}

void CMMDExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CMMDExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CMMDPropertiesDialog, CDisplayDialog)

CMMDPropertiesDialog::CMMDPropertiesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDPropertiesDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CMMDPropertiesDialog::IDD);
}

BOOL CMMDPropertiesDialog::Initialize()
{
	GetParentDisplay()->GetImage(m_sizeImage[0], m_nImage[0][0], m_nImage[0][1], m_nImage[0][2], m_nImage[0][3], m_nImageBkgnd[0], m_sizeGrid[0], m_nImageGrid[0], m_bUseGrid[0]);
	m_nImageBkgnd[1] = m_nImageBkgnd[0];
	m_nImageGrid[1] = m_nImageGrid[0];
	m_sizeImage[1] = m_sizeImage[0];
	m_sizeGrid[1] = m_sizeGrid[0];
	m_bUseGrid[1] = m_bUseGrid[0];
	m_nImage[1][0] = m_nImage[0][0];
	m_nImage[1][1] = m_nImage[0][1];
	m_nImage[1][2] = m_nImage[0][2];
	m_nImage[1][3] = m_nImage[0][3];
	return TRUE;
}

CMMDWnd *CMMDPropertiesDialog::GetParentDisplay() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CMMDPropertiesDialog::ShowProperties()
{
	CheckDlgButton(IDC_MMD_PROPERTIES_GRID_SHOWALWAYS, m_bUseGrid[0]);
	CheckRadioButton(IDC_MMD_PROPERTIES_SIZE_DEFAULT, IDC_MMD_PROPERTIES_SIZE_FIXED, (m_sizeImage[0].cx <= 0 || m_sizeImage[0].cy <= 0) ? IDC_MMD_PROPERTIES_SIZE_DEFAULT : IDC_MMD_PROPERTIES_SIZE_FIXED);
	CheckRadioButton(IDC_MMD_PROPERTIES_GRID_POINTS, IDC_MMD_PROPERTIES_GRID_LINES, (m_sizeGrid[0].cx > 0 && m_sizeGrid[0].cy > 0) ? IDC_MMD_PROPERTIES_GRID_POINTS : ((m_sizeGrid[0].cx < 0 && m_sizeGrid[0].cy < 0) ? IDC_MMD_PROPERTIES_GRID_LINES : -1));
	SendDlgItemMessage(IDC_MMD_PROPERTIES_BACKGROUND, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nImageBkgnd[0]);
	SendDlgItemMessage(IDC_MMD_PROPERTIES_GRID_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nImageGrid[0]);
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_X), m_sizeImage[0].cx);
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_Y), m_sizeImage[0].cy);
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT), m_nImage[0][0]);
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_RIGHT), m_nImage[0][2]);
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP), m_nImage[0][1]);
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_BOTTOM), m_nImage[0][3]);
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL), abs(m_sizeGrid[0].cx));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL), abs(m_sizeGrid[0].cy));
	GetDlgItem(IDC_MMD_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_X)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_SIZE_FIXED));
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_SIZE_FIXED));
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_Y)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_SIZE_FIXED));
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_SIZE_FIXED));
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_SIZE_FIXED));
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_SIZE_FIXED));
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_SIZE_FIXED));
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_SIZE_FIXED));
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP_PIXELS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_SIZE_FIXED));
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_RIGHT_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_RIGHT)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_BOTTOM_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_BOTTOM)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_BOTTOM_PIXELS)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_BACKGROUND_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_BACKGROUND)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_POINTS)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_LINES)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_SHOWALWAYS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_COLOR_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_COLOR)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
}

BOOL CMMDPropertiesDialog::IsModified() CONST
{
	return((m_sizeImage[0] != m_sizeImage[1] || m_nImage[0][0] != m_nImage[1][0] || m_nImage[0][1] != m_nImage[1][1] || m_nImage[0][2] != m_nImage[1][2] || m_nImage[0][3] != m_nImage[1][3] || GetDlgItem(IDC_MMD_PROPERTIES_BACKGROUND)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nImageBkgnd[0]) != GetDlgItem(IDC_MMD_PROPERTIES_BACKGROUND)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nImageBkgnd[1]) || m_sizeGrid[0] != m_sizeGrid[1] || GetDlgItem(IDC_MMD_PROPERTIES_GRID_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nImageGrid[0]) != GetDlgItem(IDC_MMD_PROPERTIES_GRID_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nImageGrid[1]) || m_bUseGrid[0] != m_bUseGrid[1]) ? TRUE : FALSE);
}

void CMMDPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMMDPropertiesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDPropertiesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_PROPERTIES_SIZE_DEFAULT, OnDefaultSize)
	ON_BN_CLICKED(IDC_MMD_PROPERTIES_SIZE_FIXED, OnFixedSize)
	ON_BN_CLICKED(IDC_MMD_PROPERTIES_GRID_POINTS, OnGridPoints)
	ON_BN_CLICKED(IDC_MMD_PROPERTIES_GRID_LINES, OnGridLines)
	ON_BN_CLICKED(IDC_MMD_PROPERTIES_GRID_SHOWALWAYS, OnShowGrid)
	ON_BN_CLICKED(IDC_MMD_PROPERTIES_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_MMD_PROPERTIES_BACKGROUND, OnSelchangeBackgroundColor)
	ON_CBN_SELCHANGE(IDC_MMD_PROPERTIES_GRID_COLOR, OnSelchangeGridColor)
	ON_CONTROL(SBXN_CHANGE, IDC_MMD_PROPERTIES_SIZE_FIXED_X, OnSpinchangeHorizontalSize)
	ON_CONTROL(SBXN_CHANGE, IDC_MMD_PROPERTIES_SIZE_FIXED_Y, OnSpinchangeVerticalSize)
	ON_CONTROL(SBXN_CHANGE, IDC_MMD_PROPERTIES_MARGINS_LEFT, OnSpinchangeLeftMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_MMD_PROPERTIES_MARGINS_RIGHT, OnSpinchangeRightMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_MMD_PROPERTIES_MARGINS_TOP, OnSpinchangeTopMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_MMD_PROPERTIES_MARGINS_BOTTOM, OnSpinchangeBottomMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL, OnSpinchangeHorizontalGridInterval)
	ON_CONTROL(SBXN_CHANGE, IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL, OnSpinchangeVerticalGridInterval)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDPropertiesDialog message handlers

BOOL CMMDPropertiesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_X), 0, GetSystemMetrics(SM_CXSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_Y), 0, GetSystemMetrics(SM_CYSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT), 0, GetSystemMetrics(SM_CXSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP), 0, GetSystemMetrics(SM_CYSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_RIGHT), 0, GetSystemMetrics(SM_CXSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_BOTTOM), 0, GetSystemMetrics(SM_CYSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL), 2, GetSystemMetrics(SM_CXSCREEN) / 2);
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL), 2, GetSystemMetrics(SM_CYSCREEN) / 2);
	SendDlgItemMessage(IDC_MMD_PROPERTIES_BACKGROUND, CCB_INSERTCOLOR, 0, (LPARAM)GetSysColor(COLOR_WINDOW));
	SendDlgItemMessage(IDC_MMD_PROPERTIES_GRID_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)GetSysColor(COLOR_WINDOW));
	AccessControl(IDC_MMD_PROPERTIES_SIZE_DEFAULT, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_SIZE_FIXED, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_SIZE_FIXED_X, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_SIZE_FIXED_Y, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_MARGINS_LEFT, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_MARGINS_RIGHT, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_MARGINS_TOP, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_MARGINS_BOTTOM, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_BACKGROUND, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_GRID_POINTS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_GRID_LINES, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_GRID_SHOWALWAYS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	AccessControl(IDC_MMD_PROPERTIES_GRID_COLOR, CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE));
	ShowProperties();
	return TRUE;
}

void CMMDPropertiesDialog::OnDefaultSize()
{
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_X), (m_sizeImage[0].cx = 0));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_Y), (m_sizeImage[0].cy = 0));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT), (m_nImage[0][0] = 0));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP), (m_nImage[0][1] = 0));
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_UNITS)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP_PIXELS)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnFixedSize()
{
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_X), (m_sizeImage[0].cx = (!(m_nImage[0][0] = 0)) ? MMDPROPERTIESDIALOG_DEFAULT_IMAGEWIDTH : 0));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_Y), (m_sizeImage[0].cy = (!(m_nImage[0][1] = 0)) ? MMDPROPERTIESDIALOG_DEFAULT_IMAGEHEIGHT : 0));
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_X)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_Y)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_UNITS)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP_PIXELS)->EnableWindow();
	GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_X)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnGridPoints()
{
	CheckDlgButton(IDC_MMD_PROPERTIES_GRID_LINES, FALSE);
	CheckDlgButton(IDC_MMD_PROPERTIES_GRID_SHOWALWAYS, (m_bUseGrid[0] = FALSE));
	CheckDlgButton(IDC_MMD_PROPERTIES_GRID_POINTS, !IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL), (m_sizeGrid[0].cx = (IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS)) ? MMDPROPERTIESDIALOG_DEFAULT_GRIDINTERVAL : 0));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL), (m_sizeGrid[0].cy = (IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS)) ? MMDPROPERTIESDIALOG_DEFAULT_GRIDINTERVAL : 0));
	SendDlgItemMessage(IDC_MMD_PROPERTIES_GRID_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)(m_nImageGrid[0] = VGA_COLOR_LTGRAY));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_SHOWALWAYS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_COLOR_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_COLOR)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnGridLines()
{
	CheckDlgButton(IDC_MMD_PROPERTIES_GRID_POINTS, FALSE);
	CheckDlgButton(IDC_MMD_PROPERTIES_GRID_SHOWALWAYS, (m_bUseGrid[0] = FALSE));
	CheckDlgButton(IDC_MMD_PROPERTIES_GRID_LINES, !IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL), abs((m_sizeGrid[0].cx = (IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES)) ? -MMDPROPERTIESDIALOG_DEFAULT_GRIDINTERVAL : 0)));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL), abs((m_sizeGrid[0].cy = (IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES)) ? -MMDPROPERTIESDIALOG_DEFAULT_GRIDINTERVAL : 0)));
	SendDlgItemMessage(IDC_MMD_PROPERTIES_GRID_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)(m_nImageGrid[0] = VGA_COLOR_LTGRAY));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_SHOWALWAYS)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_COLOR_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_COLOR)->EnableWindow(IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES));
	GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnShowGrid()
{
	m_bUseGrid[0] = IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_SHOWALWAYS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnSelchangeBackgroundColor()
{
	m_nImageBkgnd[0] = (COLORREF)SendDlgItemMessage(IDC_MMD_PROPERTIES_BACKGROUND, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MMD_PROPERTIES_BACKGROUND, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnSelchangeGridColor()
{
	m_nImageGrid[0] = (COLORREF)SendDlgItemMessage(IDC_MMD_PROPERTIES_GRID_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MMD_PROPERTIES_GRID_COLOR, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnSpinchangeHorizontalSize()
{
	m_sizeImage[0].cx = (LONG)Spinbox_GetPos(GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_X));
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT), 0, m_sizeImage[0].cx);
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_RIGHT), 0, (!m_sizeImage[0].cx) ? GetSystemMetrics(SM_CXSCREEN) : m_sizeImage[0].cx);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnSpinchangeVerticalSize()
{
	m_sizeImage[0].cy = (LONG)Spinbox_GetPos(GetDlgItem(IDC_MMD_PROPERTIES_SIZE_FIXED_Y));
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP), 0, m_sizeImage[0].cy);
	Spinbox_SetRange(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_BOTTOM), 0, (!m_sizeImage[0].cy) ? GetSystemMetrics(SM_CYSCREEN) : m_sizeImage[0].cy);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnSpinchangeLeftMargin()
{
	m_nImage[0][0] = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_RIGHT), (m_nImage[0][2] = (m_sizeImage[0].cx > 0) ? ((m_sizeImage[0].cx - m_nImage[0][0] - m_nImage[0][2] < 0) ? (m_sizeImage[0].cx - m_nImage[0][0]) : m_nImage[0][2]) : m_nImage[0][2]));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnSpinchangeRightMargin()
{
	m_nImage[0][2] = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_RIGHT));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_LEFT), (m_nImage[0][0] = (m_sizeImage[0].cx > 0) ? ((m_sizeImage[0].cx - m_nImage[0][2] - m_nImage[0][0] < 0) ? (m_sizeImage[0].cx - m_nImage[0][2]) : m_nImage[0][0]) : m_nImage[0][0]));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnSpinchangeTopMargin()
{
	m_nImage[0][1] = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_BOTTOM), (m_nImage[0][3] = (m_sizeImage[0].cy > 0) ? ((m_sizeImage[0].cy - m_nImage[0][1] - m_nImage[0][3] < 0) ? (m_sizeImage[0].cy - m_nImage[0][1]) : m_nImage[0][3]) : m_nImage[0][3]));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnSpinchangeBottomMargin()
{
	m_nImage[0][3] = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_BOTTOM));
	Spinbox_SetPos(GetDlgItem(IDC_MMD_PROPERTIES_MARGINS_TOP), (m_nImage[0][1] = (m_sizeImage[0].cy > 0) ? ((m_sizeImage[0].cy - m_nImage[0][3] - m_nImage[0][1] < 0) ? (m_sizeImage[0].cy - m_nImage[0][3]) : m_nImage[0][1]) : m_nImage[0][1]));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnSpinchangeHorizontalGridInterval()
{
	INT  nInterval;

	if (IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES))
	{
		nInterval = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_PROPERTIES_GRID_HORIZONTALINTERVAL));
		m_sizeGrid[0].cx = (IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES)) ? -nInterval : nInterval;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnSpinchangeVerticalGridInterval()
{
	INT  nInterval;

	if (IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_POINTS) || IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES))
	{
		nInterval = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_PROPERTIES_GRID_VERTICALINTERVAL));
		m_sizeGrid[0].cy = (IsDlgButtonChecked(IDC_MMD_PROPERTIES_GRID_LINES)) ? -nInterval : nInterval;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParentDisplay()->SetImage(m_sizeImage[0], m_nImage[0][0], m_nImage[0][1], m_nImage[0][2], m_nImage[0][3], m_nImageBkgnd[0], m_sizeGrid[0], m_nImageGrid[0], m_bUseGrid[0]);
	CDisplayDialog::OnOK();
}

BOOL CMMDPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDLinkInformationDialog dialog

IMPLEMENT_DYNCREATE(CMMDLinkInformationDialog, CDisplayDialog)

CMMDLinkInformationDialog::CMMDLinkInformationDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDLinkInformationDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDLinkInformationDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CMMDLinkInformationDialog::IDD);
}

BOOL CMMDLinkInformationDialog::Initialize()
{
	m_pDisplays.Copy(GetDatabase()->GetMMDs());
	return TRUE;
}

CMMDWnd *CMMDLinkInformationDialog::GetParentDisplay() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParentDisplay());
}

INT CMMDLinkInformationDialog::EnumDisplays()
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(), SendDlgItemMessage(IDC_MMD_LINKINFORMATION_DISPLAY, CB_RESETCONTENT); nDisplay < nDisplays; nDisplay++)
	{
		if (GetParentDisplay()->GetName() == m_pDisplays.GetAt(nDisplay)->GetName())
		{
			delete m_pDisplays.GetAt(nDisplay);
			m_pDisplays.RemoveAt(nDisplay);
			nDisplays--;
			nDisplay--;
			continue;
		}
		szDisplay.Format(STRING(IDS_MMDLINKINFORMATIONDIALOG_DIRECTORYITEMFORMAT), (LPCTSTR)m_pDisplays.GetAt(nDisplay)->GetName(), (LPCTSTR)m_pDisplays.GetAt(nDisplay)->GetTitle());
		SendDlgItemMessage(IDC_MMD_LINKINFORMATION_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDisplay);
	}
	if ((nDisplays = (INT)SendDlgItemMessage(IDC_MMD_LINKINFORMATION_DISPLAY, CB_GETCOUNT)) > 0)
	{
		GetDlgItem(IDC_MMD_LINKINFORMATION_DISPLAY_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_LINKINFORMATION_DISPLAY)->EnableWindow();
		GetDlgItem(IDC_MMD_LINKINFORMATION_DISPLAY)->SetFocus();
		return nDisplays;
	}
	GetDlgItem(IDC_MMD_LINKINFORMATION_DISPLAY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_LINKINFORMATION_DISPLAY)->EnableWindow(FALSE);
	return 0;
}

INT CMMDLinkInformationDialog::FindDisplay(LPCTSTR pszName) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		szDisplay.Format(STRING(IDS_MMDLINKINFORMATIONDIALOG_DIRECTORYITEMFORMAT), (LPCTSTR)m_pDisplays.GetAt(nDisplay)->GetName(), (LPCTSTR)m_pDisplays.GetAt(nDisplay)->GetTitle());
		if (!szDisplay.CompareNoCase(pszName) || !m_pDisplays.GetAt(nDisplay)->GetName().CompareNoCase(pszName) || !m_pDisplays.GetAt(nDisplay)->GetTitle().CompareNoCase(pszName)) break;
	}
	return((nDisplay < nDisplays) ? nDisplay : -1);
}

BOOL CMMDLinkInformationDialog::Check(BOOL bModified) CONST
{
	INT  nIndex;
	CString  szDisplay;

	GetDlgItem(IDC_MMD_LINKINFORMATION_DISPLAY)->GetWindowText(szDisplay);
	return(((nIndex = FindDisplay(szDisplay)) >= 0 && m_nIndex != nIndex) || (m_nIndex >= 0 && szDisplay.IsEmpty()) ? TRUE : FALSE);
}

void CMMDLinkInformationDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDLinkInformationDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDLinkInformationDialog::PostNcDestroy()
{
	m_pDisplays.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDLinkInformationDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDLinkInformationDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_LINKINFORMATION_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_MMD_LINKINFORMATION_DISPLAY, OnEditchangeDisplay)
	ON_CBN_SELCHANGE(IDC_MMD_LINKINFORMATION_DISPLAY, OnSelchangeDisplay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDLinkInformationDialog message handlers

BOOL CMMDLinkInformationDialog::OnInitDialog()
{
	CMimicsItem  *pItem;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	if ((pItem = (EnumDisplays() >= 0) ? GetParentDisplay()->GetActivatedMimicsCtrl() : (CMimicsItem *)NULL))
	{
		SendDlgItemMessage(IDC_MMD_LINKINFORMATION_DISPLAY, CB_SETCURSEL, (m_nIndex = FindDisplay(pItem->GetItemLink())));
		GetDlgItem(IDC_MMD_LINKINFORMATION_NAME)->SetWindowText(pItem->GetItemName());
		GetDlgItem(IDC_MMD_LINKINFORMATION_DETAILS)->EnableWindow();
		GetDlgItem(IDC_MMD_LINKINFORMATION_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_LINKINFORMATION_NAME)->EnableWindow();
		return FALSE;
	}
	return TRUE;
}

void CMMDLinkInformationDialog::OnEditchangeDisplay()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDLinkInformationDialog::OnSelchangeDisplay()
{
	SendDlgItemMessage(IDC_MMD_LINKINFORMATION_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMD_LINKINFORMATION_DISPLAY, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDLinkInformationDialog::OnOK()
{
	INT  nIndex;
	CString  szDisplay;
	CMimicsItem  *pItem;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_LINKINFORMATION_DISPLAY)->GetWindowText(szDisplay);
	if ((nIndex = ((pItem = GetParentDisplay()->GetActivatedMimicsCtrl())) ? FindDisplay(szDisplay) : -1) >= 0)
	{
		pItem->SetItemLink(m_pDisplays.GetAt(nIndex)->GetName());
		CDisplayDialog::OnOK();
		return;
	}
	for (; (pItem = GetParentDisplay()->GetActivatedMimicsCtrl()); )
	{
		pItem->SetItemLink(EMPTYSTRING);
		break;
	}
	CDisplayDialog::OnOK();
}

BOOL CMMDLinkInformationDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDOBJECTLINKDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDLinkInformationDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDOBJECTLINKDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDCreateMimicsGroupDialog dialog

IMPLEMENT_DYNCREATE(CMMDCreateMimicsGroupDialog, CDisplayDialog)

CMMDCreateMimicsGroupDialog::CMMDCreateMimicsGroupDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDCreateMimicsGroupDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDCreateMimicsGroupDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CMMDCreateMimicsGroupDialog::IDD);
}

CMMDWnd *CMMDCreateMimicsGroupDialog::GetParentDisplay() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CMMDCreateMimicsGroupDialog::EnumMimicsGroups()
{
	INT  nGroup;
	INT  nGroups;
	CByteArray  nGroupsInfo;
	CProfile  cProfile;

	for (nGroup = 0, nGroups = (cProfile.GetMimicsGroupsInfo(nGroupsInfo) && m_pMimicsGroups.Unmap(nGroupsInfo)) ? (INT)m_pMimicsGroups.GetSize() : -1; nGroup < nGroups; nGroup++)
	{
		SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_pMimicsGroups.GetAt(nGroup)->GetName());
		continue;
	}
	if (nGroups < 0)
	{
		ShowMessage(SYSTEM_WARNING_MIMICSGROUPS_LOAD_FAILURE);
		return FALSE;
	}
	return TRUE;
}

BOOL CMMDCreateMimicsGroupDialog::EnumMimicsObjects()
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CSize  sizeItem;
	CPoint  ptItem;
	CString  szItem;
	CStringArray  szNames;
	CStringArray  szTypes;
	CStringArray  szPositions;
	CMimicsItem  *pItem;

	for (nItem = 0, nItems = (INT)m_pMimicsItems[1].GetSize(), m_pMimicsObjects.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = m_pMimicsItems[1].GetAt(nItem)))
		{
			pItem->GetItemPosition(ptItem, sizeItem);
			for (nColumn = 0, nColumns = (INT)m_szColumns[1].GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns[1].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSOBJECTSTITLEITEM_NAME); )
				{
					szItem = pItem->GetItemName();
					szNames.Add(szItem);
					break;
				}
				for (; m_szColumns[1].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSOBJECTSTITLEITEM_TYPE); )
				{
					szItem = pItem->GetItemType();
					szTypes.Add(szItem);
					break;
				}
				for (; m_szColumns[1].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSOBJECTSTITLEITEM_POSITION); )
				{
					szItem.Format(STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSOBJECTS_POSITIONFORMAT), ptItem.x - GetParentDisplay()->GetImageView()->GetImageOrigin().x, ptItem.y - GetParentDisplay()->GetImageView()->GetImageOrigin().y, sizeItem.cx, sizeItem.cy);
					szPositions.Add(szItem);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS), nItem, nColumn, szItem);
			}
			m_pMimicsObjects.InsertAt(nItem, pItem, 1);
		}
	}
	if (SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_GETITEMCOUNT) > 0)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns[1].GetSize(); nColumn < nColumns; nColumn++)
		{
			if (m_szColumns[1].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSOBJECTSTITLEITEM_NAME))
			{
				SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(m_szColumns[1].GetAt(nColumn), szNames)) > 0) ? MAKELPARAM(nWidth, 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
			if (m_szColumns[1].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSOBJECTSTITLEITEM_TYPE))
			{
				SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(m_szColumns[1].GetAt(nColumn), szTypes)) > 0) ? MAKELPARAM(nWidth, 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
			if (m_szColumns[1].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSOBJECTSTITLEITEM_POSITION))
			{
				SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(m_szColumns[1].GetAt(nColumn), szPositions)) > 0) ? MAKELPARAM(nWidth, 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
		}
		Listview_SetCurText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS), 0);
	}
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

VOID CMMDCreateMimicsGroupDialog::ShowMimicsGroupContents()
{
	CString  szGroup;

	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_NAME)->GetWindowText(szGroup);
	ShowMimicsGroupContents(szGroup);
}
VOID CMMDCreateMimicsGroupDialog::ShowMimicsGroupContents(LPCTSTR pszGroup)
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CSize  sizeItem;
	CPoint  ptItem;
	CString  szItem;
	CStringArray  szNames;
	CStringArray  szTypes;
	CStringArray  szPositions;
	CMimicsGroup  *pGroup;
	CMimicsItem  *pItem;

	SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_DELETEALLITEMS);
	for (nItem = 0, nItems = ((pGroup = m_pMimicsGroups.GetAt(m_pMimicsGroups.Find(pszGroup)))) ? pGroup->GetItemCount() : 0, m_pMimicsItems[0].RemoveAll(), m_pMimicsItems[2].RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = pGroup->GetAt(nItem)))
		{
			pItem->GetItemPosition(ptItem, sizeItem);
			if (BuildMimicsGroupMemberItem(pItem))
			{
				for (nColumn = 0, nColumns = (INT)m_szColumns[0].GetSize(); nColumn < nColumns; nColumn++)
				{
					for (; m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_NAME); )
					{
						szItem = pItem->GetItemName();
						szNames.Add(szItem);
						break;
					}
					for (; m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_TYPE); )
					{
						szItem = pItem->GetItemType();
						szTypes.Add(szItem);
						break;
					}
					for (; m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_POSITION); )
					{
						szItem.Format(STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTION_POSITIONFORMAT), ptItem.x - GetParentDisplay()->GetImageView()->GetImageOrigin().x, ptItem.y - GetParentDisplay()->GetImageView()->GetImageOrigin().y, sizeItem.cx, sizeItem.cy);
						szPositions.Add(szItem);
						break;
					}
					if (!nColumn)
					{
						Listview_InsertText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), nItem, szItem);
						continue;
					}
					Listview_SetText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), nItem, nColumn, szItem);
				}
			}
		}
	}
	if (SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns[0].GetSize(); nColumn < nColumns; nColumn++)
		{
			if (m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_NAME))
			{
				SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(m_szColumns[0].GetAt(nColumn), szNames)) > 0) ? MAKELPARAM(nWidth, 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
			if (m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_TYPE))
			{
				SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(m_szColumns[0].GetAt(nColumn), szTypes)) > 0) ? MAKELPARAM(nWidth, 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
			if (m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_POSITION))
			{
				SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(m_szColumns[0].GetAt(nColumn), szPositions)) > 0) ? MAKELPARAM(nWidth, 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
		}
		Listview_SetCurText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), 0);
	}
	DrawMimicsGroupPreviewPicture();
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_PREVIEW_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_PREVIEW)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

VOID CMMDCreateMimicsGroupDialog::DrawMimicsGroupPreviewPicture()
{
	CDC  *pDC;
	CWnd  *pWnd;

	if ((pDC = ((pWnd = GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_PREVIEW))) ? pWnd->GetDC() : (CDC *)NULL))
	{
		DrawMimicsGroupPreviewPicture(pDC);
		pWnd->ReleaseDC(pDC);
	}
}
VOID CMMDCreateMimicsGroupDialog::DrawMimicsGroupPreviewPicture(CDC *pDC)
{
	INT  nItem;
	INT  nItems;
	INT  cxImage;
	INT  cyImage;
	CRect  rImage;
	CRect  rPreview;
	CMimicsItem  *pItem;
	CMetaFileDC  cMetaDC;
	HENHMETAFILE  hMetaFile;
	ENHMETAHEADER  sMetaFile;

	if (cMetaDC.CreateEnhanced(pDC, (LPCTSTR)NULL, (LPCRECT)NULL, (LPCTSTR)NULL))
	{
		for (nItem = 0, nItems = (INT)m_pMimicsItems[0].GetSize(), cMetaDC.SetAttribDC(pDC->GetSafeHdc()), rPreview.SetRect(0, 0, (cxImage = CalcMimicsGroupPreviewSize().cx), (cyImage = CalcMimicsGroupPreviewSize().cy)), rPreview.DeflateRect(GetSystemMetrics(SM_CXFRAME), GetSystemMetrics(SM_CYFRAME)); nItem < nItems; nItem++)
		{
			if ((pItem = m_pMimicsItems[0].GetAt(nItem)))
			{
				pItem->Draw(&cMetaDC);
				continue;
			}
		}
		if ((hMetaFile = cMetaDC.CloseEnhanced()))
		{
			if (GetEnhMetaFileHeader(hMetaFile, sizeof(sMetaFile), &sMetaFile))
			{
				pDC->FillSolidRect(CRect(0, 0, cxImage, cyImage), GetSysColor(COLOR_WINDOW));
				rImage.SetRect(0, 0, ((double)(sMetaFile.rclBounds.right - sMetaFile.rclBounds.left) / (double)rPreview.Width() >= (double)(sMetaFile.rclBounds.bottom - sMetaFile.rclBounds.top) / (double)rPreview.Height()) ? (INT)((double)(sMetaFile.rclBounds.right - sMetaFile.rclBounds.left) / ((double)(sMetaFile.rclBounds.right - sMetaFile.rclBounds.left) / (double)rPreview.Width())) : (INT)((double)(sMetaFile.rclBounds.right - sMetaFile.rclBounds.left) / ((double)(sMetaFile.rclBounds.bottom - sMetaFile.rclBounds.top) / (double)rPreview.Height())), ((double)(sMetaFile.rclBounds.right - sMetaFile.rclBounds.left) / (double)rPreview.Width() >= (double)(sMetaFile.rclBounds.bottom - sMetaFile.rclBounds.top) / (double)rPreview.Height()) ? (INT)((double)(sMetaFile.rclBounds.bottom - sMetaFile.rclBounds.top) / ((double)(sMetaFile.rclBounds.right - sMetaFile.rclBounds.left) / (double)rPreview.Width())) : (INT)((double)(sMetaFile.rclBounds.bottom - sMetaFile.rclBounds.top) / ((double)(sMetaFile.rclBounds.bottom - sMetaFile.rclBounds.top) / (double)rPreview.Height())));
				rImage.OffsetRect(rPreview.left + (rPreview.Width() - rImage.Width()) / 2, rPreview.top + (rPreview.Height() - rImage.Height()) / 2);
				pDC->PlayMetaFile(hMetaFile, rImage);
			}
			DeleteEnhMetaFile(hMetaFile);
			return;
		}
	}
	pDC->FillSolidRect(CRect(0, 0, CalcMimicsGroupPreviewSize().cx, CalcMimicsGroupPreviewSize().cy), GetSysColor(COLOR_WINDOW));
}

BOOL CMMDCreateMimicsGroupDialog::BuildMimicsGroupMemberItem(CMimicsItem *pItem)
{
	CMimicsItem  *pMimicsItem[2];

	if ((pMimicsItem[0] = CMimicsItem::Create(pItem, (CView *)NULL, m_pMimicsDocument)))
	{
		if ((pMimicsItem[1] = CMimicsItem::AllocateFromItem(pMimicsItem[0])) && pMimicsItem[1]->Copy(pMimicsItem[0]))
		{
			if (m_pMimicsItems[0].Add(pMimicsItem[0]) < 0)
			{
				delete pMimicsItem[0];
				delete pMimicsItem[1];
				return FALSE;
			}
			if (m_pMimicsItems[2].Add(pMimicsItem[1]) < 0)
			{
				m_pMimicsItems[0].RemoveAt(m_pMimicsItems[0].GetUpperBound());
				delete pMimicsItem[0];
				delete pMimicsItem[1];
				return FALSE;
			}
			return TRUE;
		}
		delete pMimicsItem[0];
	}
	return FALSE;
}
CMimicsItem *CMMDCreateMimicsGroupDialog::DuplicateMimicsGroupMemberItem(CMimicsItem *pItem)
{
	return CMimicsItem::Create(pItem, (CView *)NULL, m_pMimicsDocument);
}

CSize CMMDCreateMimicsGroupDialog::CalcMimicsGroupPreviewSize() CONST
{
	CRect  rPreview;

	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_PREVIEW)->GetClientRect(rPreview);
	return CSize(rPreview.Width(), rPreview.Height());
}

INT CMMDCreateMimicsGroupDialog::CalcColumnWidth(LPCTSTR pszTitle, CONST CStringArray &szItems)
{
	CDC  *pDC;
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	CFont  *pOldFont;
	CSize  sizeItem[2];

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS)->GetFont())))
		{
			for (nItem = 0, nItems = (INT)szItems.GetSize(), sizeItem[0] = pDC->GetTextExtent(pszTitle); nItem < nItems; nItem++)
			{
				sizeItem[1] = pDC->GetTextExtent(szItems.GetAt(nItem));
				sizeItem[0] = (sizeItem[0].cx < sizeItem[1].cx) ? sizeItem[1] : sizeItem[0];
			}
			nWidth = 6 * GetSystemMetrics(SM_CXEDGE) + sizeItem[0].cx;
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return nWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

BOOL CMMDCreateMimicsGroupDialog::IsModified() CONST
{
	return !m_pMimicsItems[0].Compare(&m_pMimicsItems[1]);
}

BOOL CMMDCreateMimicsGroupDialog::Check(BOOL bModified) CONST
{
	CString  szGroup;

	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_NAME)->GetWindowText(szGroup);
	return((!szGroup.IsEmpty() && (m_pMimicsGroups.Find(szGroup) < 0 || (!bModified || IsModified())) && GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION)->SendMessage(LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

void CMMDCreateMimicsGroupDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDCreateMimicsGroupDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDCreateMimicsGroupDialog::PostNcDestroy()
{
	m_szColumns[0].RemoveAll();
	m_szColumns[1].RemoveAll();
	m_pMimicsGroups.RemoveAll();
	m_pMimicsObjects.RemoveAll();
	m_pMimicsItems[0].RemoveAll();
	m_pMimicsItems[1].RemoveAll();
	m_pMimicsItems[2].RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDCreateMimicsGroupDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDCreateMimicsGroupDialog)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_CREATEMIMICSGROUP_HELP, OnHelp)
	ON_COMMAND(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_ADD, OnAddMember)
	ON_COMMAND(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_REMOVE, OnRemoveMember)
	ON_COMMAND(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_REMOVEALL, OnRemoveAllMembers)
	ON_CBN_EDITCHANGE(IDC_MMD_CREATEMIMICSGROUP_NAME, OnEditchangeName)
	ON_CBN_SELCHANGE(IDC_MMD_CREATEMIMICSGROUP_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDCreateMimicsGroupDialog message handlers

int CMMDCreateMimicsGroupDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT  nItem;
	INT  nItems;
	CPtrArray  pItems;
	CMimicsItem  *pItem[2];

	if (CLocaleDialog::OnCreate(lpCreateStruct) != -1)
	{
		if ((m_pMimicsDocument = new CMMDDocument) != (CMMDDocument *)NULL)
		{
			for (nItem = 0, nItems = GetParentDisplay()->EnumMimicsCtrls(pItems); nItem < nItems; nItem++)
			{
				if ((pItem[0] = (CMimicsItem *)pItems.GetAt(nItem)) != (CMimicsItem *)NULL  &&  !pItem[0]->GetItemContainer())
				{
					if ((pItem[1] = CMimicsItem::AllocateFromItem(pItem[0])) != (CMimicsItem *)NULL)
					{
						if (!pItem[1]->Copy(pItem[0]) || m_pMimicsItems[1].Add(pItem[1]) < 0)
						{
							delete pItem[1];
							continue;
						}
					}
				}
			}
			return 0;
		}
	}
	return -1;
}

BOOL CMMDCreateMimicsGroupDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS)->GetWindowRect(rColumns[0]);
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION)->GetWindowRect(rColumns[1]);
	m_szColumns[0].Add(STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_NAME));
	m_szColumns[0].Add(STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_TYPE));
	m_szColumns[0].Add(STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_POSITION));
	m_szColumns[1].Add(STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSOBJECTSTITLEITEM_NAME));
	m_szColumns[1].Add(STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSOBJECTSTITLEITEM_TYPE));
	m_szColumns[1].Add(STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSOBJECTSTITLEITEM_POSITION));
	SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns[0].GetSize(), nWidth = (3 * rColumns[1].Width()) / 4; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[1].Width() / 3) : (rColumns[1].Width() / 2))
	{
		Listview_InsertColumn(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), nColumn, m_szColumns[0].GetAt(nColumn), nWidth);
		continue;
	}
	for (nColumn = 0, nColumns = (INT)m_szColumns[1].GetSize(), nWidth = (3 * rColumns[0].Width()) / 4; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() / 3) : (rColumns[0].Width() / 2))
	{
		Listview_InsertColumn(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS), nColumn, m_szColumns[1].GetAt(nColumn), nWidth);
		continue;
	}
	EnumMimicsGroups();
	EnumMimicsObjects();
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_NAME)->EnableWindow();
	return TRUE;
}

BOOL CMMDCreateMimicsGroupDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CMimicsItem  *pItem;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION || pNotifyListView->hdr.idFrom == IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_INSERTITEM || (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) || pNotifyListView->hdr.code == LVN_DELETEITEM || pNotifyListView->hdr.code == LVN_DELETEALLITEMS)
		{
			for (nItem = 0, nItems = ((pNotifyListView->hdr.code != LVN_DELETEITEM || m_pMimicsItems[0].GetSize() > 1) && pNotifyListView->hdr.code != LVN_DELETEALLITEMS) ? (((nIndex = Listview_GetCurText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS))) >= 0) ? (INT)m_pMimicsItems[0].GetSize() : -1) : 0; nItem < nItems; nItem++)
			{
				if ((pItem = m_pMimicsItems[0].GetAt(nItem)) && pItem->Compare((CMimicsItem *)m_pMimicsObjects.GetAt(nIndex))) break;
				continue;
			}
			GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_ADD)->EnableWindow((nItem == nItems) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION)) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

HBRUSH CMMDCreateMimicsGroupDialog::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	return((pWnd->GetDlgCtrlID() == IDC_MMD_CREATEMIMICSGROUP_PREVIEW) ? (HBRUSH)GetStockObject(NULL_BRUSH) : CDisplayDialog::OnCtlColor(pDC, pWnd, nCtlColor));
}

void CMMDCreateMimicsGroupDialog::OnPaint()
{
	CPaintDC  cDC(this);

	DrawMimicsGroupPreviewPicture();
}

void CMMDCreateMimicsGroupDialog::OnAddMember()
{
	INT  nWidth;
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	INT  nItem[3];
	INT  nItems[3];
	CSize  sizeItem;
	CPoint  ptItem;
	CString  szItem;
	CStringArray  szNames;
	CStringArray  szTypes;
	CStringArray  szPositions;
	CMimicsItem  *pItem[2];
	CHourglassCursor  cCursor;

	if ((pItem[1] = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS))) >= 0 && nIndex < m_pMimicsObjects.GetSize()) ? (CMimicsItem *)m_pMimicsObjects.GetAt(nIndex) : (CMimicsItem *)NULL))
	{
		for (nItem[0] = 0, nItems[0] = ((pItem[0] = DuplicateMimicsGroupMemberItem(pItem[1]))) ? (INT)m_pMimicsItems[1].GetSize() : -1; nItem[0] < nItems[0]; nItem[0]++)
		{
			if (pItem[1] == m_pMimicsItems[1].GetAt(nItem[0])) break;
			continue;
		}
		for (nItem[1] = 0, nItems[1] = (nItem[0] < nItems[0]) ? (INT)m_pMimicsItems[0].GetSize() : -1; nItem[1] < nItems[1]; nItem[1]++)
		{
			for (nItem[2] = 0, nItems[2] = (INT)m_pMimicsItems[1].GetSize(); nItem[2] < nItems[2]; nItem[2] = nItem[2] + 1)
			{
				if (m_pMimicsItems[0].GetAt(nItem[1])->Compare(m_pMimicsItems[1].GetAt(nItem[2])) && nItem[2] > nItem[0])
				{
					m_pMimicsItems[0].InsertAt(nItem[1], pItem[0], 1);
					break;
				}
			}
			if (nItem[2] < nItems[2]) break;
		}
		if ((nItem[1] == nItems[1] && m_pMimicsItems[0].Add(pItem[0]) >= 0) || nItem[1] < nItems[1])
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns[0].GetSize(), pItem[0]->GetItemPosition(ptItem, sizeItem); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_NAME); )
				{
					szItem = pItem[0]->GetItemName();
					break;
				}
				for (; m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_TYPE); )
				{
					szItem = pItem[0]->GetItemType();
					break;
				}
				for (; m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_POSITION); )
				{
					szItem.Format(STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTION_POSITIONFORMAT), ptItem.x - GetParentDisplay()->GetImageView()->GetImageOrigin().x, ptItem.y - GetParentDisplay()->GetImageView()->GetImageOrigin().y, sizeItem.cx, sizeItem.cy);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), nItem[1], szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), nItem[1], nColumn, szItem);
			}
			for (nItem[2] = 0, nItems[2] = (INT)SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT); nItem[2] < nItems[2]; nItem[2]++)
			{
				for (nColumn = 0, nColumns = (INT)m_szColumns[0].GetSize(); nColumn < nColumns; nColumn++)
				{
					if (m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_NAME))
					{
						szNames.Add(Listview_GetText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), nItem[2], nColumn));
						continue;
					}
					if (m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_TYPE))
					{
						szTypes.Add(Listview_GetText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), nItem[2], nColumn));
						continue;
					}
					if (m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_POSITION))
					{
						szPositions.Add(Listview_GetText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), nItem[2], nColumn));
						continue;
					}
				}
			}
			for (nColumn = 0, nColumns = (INT)m_szColumns[0].GetSize(); nColumn < nColumns; nColumn++)
			{
				if (m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_NAME))
				{
					SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(m_szColumns[0].GetAt(nColumn), szNames)) > 0) ? MAKELPARAM(nWidth, 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETCOLUMNWIDTH, nColumn), 0));
					continue;
				}
				if (m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_TYPE))
				{
					SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(m_szColumns[0].GetAt(nColumn), szTypes)) > 0) ? MAKELPARAM(nWidth, 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETCOLUMNWIDTH, nColumn), 0));
					continue;
				}
				if (m_szColumns[0].GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_MEMBERSCOLLECTIONTITLEITEM_POSITION))
				{
					SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(m_szColumns[0].GetAt(nColumn), szPositions)) > 0) ? MAKELPARAM(nWidth, 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETCOLUMNWIDTH, nColumn), 0));
					continue;
				}
			}
			DrawMimicsGroupPreviewPicture();
		}
		else  delete pItem[0];
	}
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_PREVIEW_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_PREVIEW)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDCreateMimicsGroupDialog::OnRemoveMember()
{
	INT  nIndex;
	CMimicsItem  *pItem;
	CHourglassCursor  cCursor;

	if (Listview_DeleteText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), (nIndex = Listview_GetCurText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION)))))
	{
		if ((pItem = m_pMimicsItems[0].GetAt(nIndex)))
		{
			m_pMimicsItems[0].RemoveAt(nIndex);
			delete pItem;
		}
		Listview_SetCurText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION), 0);
		GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_PREVIEW_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_PREVIEW)->EnableWindow((SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		DrawMimicsGroupPreviewPicture();
	}
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDCreateMimicsGroupDialog::OnRemoveAllMembers()
{
	CHourglassCursor  cCursor;

	for (m_pMimicsItems[0].RemoveAll(); SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION, LVM_DELETEALLITEMS); )
	{
		GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_COLLECTION)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_PREVIEW_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_PREVIEW)->EnableWindow(FALSE);
		DrawMimicsGroupPreviewPicture();
		break;
	}
	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_MEMBERS_OBJECTS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDCreateMimicsGroupDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDCreateMimicsGroupDialog::OnSelchangeName()
{
	INT  nItem;
	INT  nItems;
	CString  szGroup;
	CMimicsItem  *pItem;
	CMimicsGroup  *pGroup;

	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_NAME)->GetWindowText(szGroup);
	if ((pGroup = m_pMimicsGroups.GetAt(m_pMimicsGroups.Find(szGroup))))
	{
		for (nItem = 0, nItems = (pGroup->GetItemCount() == m_pMimicsItems[0].GetSize()) ? pGroup->GetItemCount() : 0; nItem < nItems; nItem++)
		{
			if (!pGroup->GetAt(nItem)->Compare(m_pMimicsItems[0].GetAt(nItem))) break;
			continue;
		}
		for (nItem = (nItem == nItems) ? (INT)m_pMimicsItems[0].GetSize() : 0, nItems = (INT)m_pMimicsItems[0].GetSize(); nItem < nItems; nItem++)
		{
			if ((pItem = CMimicsItem::AllocateFromItem(m_pMimicsItems[0].GetAt(nItem))) && pItem->Copy(m_pMimicsItems[0].GetAt(nItem)))
			{
				if (!nItem  &&  pGroup->GetItemCount() > 0) pGroup->RemoveAllItems();
				pGroup->AddItem(pItem);
				continue;
			}
			delete pItem;
			break;
		}
	}
	ShowMimicsGroupContents(Combobox_GetText(GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_NAME), (INT)SendDlgItemMessage(IDC_MMD_CREATEMIMICSGROUP_NAME, CB_GETCURSEL)));
}

void CMMDCreateMimicsGroupDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nGroup;
	CString  szGroup;
	CProfile  cProfile;
	CByteArray  nData;
	CMimicsItem  *pItem;
	CMimicsGroup  *pGroup[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_CREATEMIMICSGROUP_NAME)->GetWindowText(szGroup);
	if ((nGroup = m_pMimicsGroups.Find(szGroup)) < 0)
	{
		if ((pGroup[0] = new CMimicsGroup(szGroup)))
		{
			for (nItem = 0, nItems = (INT)m_pMimicsItems[0].GetSize(); nItem < nItems; nItem++)
			{
				if ((pItem = CMimicsItem::AllocateFromItem(m_pMimicsItems[0].GetAt(nItem))) && pItem->Copy(m_pMimicsItems[0].GetAt(nItem)))
				{
					pGroup[0]->AddItem(pItem);
					continue;
				}
				delete pItem;
				break;
			}
			if (nItem == nItems)
			{
				if ((pGroup[1] = (CMimicsGroup *)CMimicsItem::Create(pGroup[0], (CView *)NULL, m_pMimicsDocument)))
				{
					pGroup[0]->SetItemType(pGroup[1]->GetItemType());
					pGroup[0]->SetItemClassID(pGroup[1]->GetItemClassID());
					if (m_pMimicsGroups.Add(pGroup[0]) >= 0 && m_pMimicsGroups.Map(nData))
					{
						if (cProfile.SetMimicsGroupsInfo(nData))
						{
							m_pMimicsItems[0].RemoveAll();
							delete pGroup[1];
							EndDialog(IDOK);
							return;
						}
						ShowMessage(SYSTEM_WARNING_MIMICSGROUPS_SAVE_FAILURE);
						m_pMimicsItems[0].RemoveAll();
						delete pGroup[1];
						EndDialog(IDOK);
						return;
					}
					delete pGroup[1];
				}
			}
		}
		ShowMessage(SYSTEM_WARNING_MIMICSGROUPS_UPDATE_FAILURE);
		m_pMimicsItems[0].RemoveAll();
		EndDialog(IDOK);
		return;
	}
	if ((pGroup[0] = m_pMimicsGroups.GetAt(nGroup)))
	{
		for (nItem = 0, nItems = (INT)m_pMimicsItems[0].GetSize(), pGroup[0]->RemoveAllItems(); nItem < nItems; nItem++)
		{
			if ((pItem = CMimicsItem::AllocateFromItem(m_pMimicsItems[0].GetAt(nItem))) && pItem->Copy(m_pMimicsItems[0].GetAt(nItem)))
			{
				pGroup[0]->AddItem(pItem);
				continue;
			}
			delete pItem;
			break;
		}
		if (nItem == nItems)
		{
			if ((pGroup[1] = (CMimicsGroup *)CMimicsItem::Create(pGroup[0], (CView *)NULL, m_pMimicsDocument)))
			{
				pGroup[0]->SetItemType(pGroup[1]->GetItemType());
				pGroup[0]->SetItemClassID(pGroup[1]->GetItemClassID());
				if (m_pMimicsGroups.Map(nData))
				{
					if (cProfile.SetMimicsGroupsInfo(nData))
					{
						m_pMimicsItems[0].RemoveAll();
						delete pGroup[1];
						EndDialog(IDOK);
						return;
					}
					ShowMessage(SYSTEM_WARNING_MIMICSGROUPS_SAVE_FAILURE);
					m_pMimicsItems[0].RemoveAll();
					delete pGroup[1];
					EndDialog(IDOK);
					return;
				}
				delete pGroup[1];
			}
		}
	}
	ShowMessage(SYSTEM_WARNING_MIMICSGROUPS_UPDATE_FAILURE);
	m_pMimicsItems[0].RemoveAll();
	CDisplayDialog::OnOK();
}

void CMMDCreateMimicsGroupDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	m_pMimicsItems[0].RemoveAll();
	CDisplayDialog::OnCancel();
}

void CMMDCreateMimicsGroupDialog::OnDestroy()
{
	delete m_pMimicsDocument;
	CDisplayDialog::OnDestroy();
}

BOOL CMMDCreateMimicsGroupDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGROUPNEWDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDCreateMimicsGroupDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGROUPNEWDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDDeleteMimicsGroupDialog dialog

IMPLEMENT_DYNCREATE(CMMDDeleteMimicsGroupDialog, CDisplayDialog)

CMMDDeleteMimicsGroupDialog::CMMDDeleteMimicsGroupDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDDeleteMimicsGroupDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDDeleteMimicsGroupDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CMMDDeleteMimicsGroupDialog::IDD);
}

CMMDWnd *CMMDDeleteMimicsGroupDialog::GetParentDisplay() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CMMDDeleteMimicsGroupDialog::EnumMimicsGroups()
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CMimicsGroup  *pGroup;
	CStringArray  szNames;
	CStringArray  szCounts;
	CStringTools  cStringTools;
	CByteArray  nGroupsInfo;
	CProfile  cProfile;

	for (nItem = 0, nItems = (cProfile.GetMimicsGroupsInfo(nGroupsInfo) && m_pMimicsGroups.Unmap(nGroupsInfo)) ? (INT)m_pMimicsGroups.GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pGroup = (CMimicsGroup *)m_pMimicsGroups.GetAt(nItem)) != (CMimicsGroup *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME))
				{
					szItem = pGroup->GetName();
					szNames.Add(szItem);
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT))
				{
					szItem = cStringTools.ConvertIntToString(pGroup->GetItemCount());
					szCounts.Add(szItem);
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST), nItem, nColumn, szItem);
			}
		}
	}
	for (; nItems < 0; )
	{
		ShowMessage(SYSTEM_WARNING_MIMICSGROUPS_LOAD_FAILURE);
		break;
	}
	if (SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME))
			{
				SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(szNames)) > 0) ? MAKELPARAM(max((WORD)SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), nWidth), 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT))
			{
				SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(szCounts)) > 0) ? MAKELPARAM(max((WORD)SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), nWidth), 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
		}
		Listview_SetCurText(GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST), 0);
	}
	GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST)->EnableWindow((SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

INT CMMDDeleteMimicsGroupDialog::CalcColumnWidth(CONST CStringArray &szItems)
{
	CDC  *pDC;
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	CFont  *pOldFont;
	CSize  sizeItem[2];

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST)->GetFont())))
		{
			for (nItem = 0, nItems = (INT)szItems.GetSize(), sizeItem[0].cx = sizeItem[0].cy = 0; nItem < nItems; nItem++)
			{
				sizeItem[1] = pDC->GetTextExtent(szItems.GetAt(nItem));
				sizeItem[0] = (sizeItem[0].cx < sizeItem[1].cx) ? sizeItem[1] : sizeItem[0];
			}
			nWidth = 6 * GetSystemMetrics(SM_CXEDGE) + sizeItem[0].cx;
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return nWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

void CMMDDeleteMimicsGroupDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDDeleteMimicsGroupDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDDeleteMimicsGroupDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pMimicsGroups.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDDeleteMimicsGroupDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDDeleteMimicsGroupDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_DELETEMIMICSGROUP_DELETEGROUP, OnDeleteGroup)
	ON_BN_CLICKED(IDC_MMD_DELETEMIMICSGROUP_DELETEALLGROUPS, OnDeleteAllGroups)
	ON_BN_CLICKED(IDC_MMD_DELETEMIMICSGROUP_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDDeleteMimicsGroupDialog message handlers

BOOL CMMDDeleteMimicsGroupDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT));
	SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (4 * rColumns.Width()) / 5; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumMimicsGroups();
	GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_DETAILS)->EnableWindow();
	return TRUE;
}

BOOL CMMDDeleteMimicsGroupDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_MMD_DELETEMIMICSGROUP_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_INSERTITEM || pNotifyListView->hdr.code == LVN_DELETEITEM || pNotifyListView->hdr.code == LVN_DELETEALLITEMS)
		{
			GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_DELETEGROUP)->EnableWindow((pNotifyListView->hdr.code == LVN_INSERTITEM || (pNotifyListView->hdr.code == LVN_DELETEITEM  &&  m_pMimicsGroups.GetSize() > 1)) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_DELETEALLGROUPS)->EnableWindow((pNotifyListView->hdr.code == LVN_INSERTITEM || (pNotifyListView->hdr.code == LVN_DELETEITEM  &&  m_pMimicsGroups.GetSize() > 1)) ? TRUE : FALSE);
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CMMDDeleteMimicsGroupDialog::OnDeleteGroup()
{
	INT  nIndex;
	CHourglassCursor  cCursor;

	if (Listview_DeleteText(GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST), (nIndex = Listview_GetCurText(GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST)))))
	{
		for (delete m_pMimicsGroups.GetAt(nIndex), m_pMimicsGroups.RemoveAt(nIndex); SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0; )
		{
			Listview_SetCurText(GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST), 0);
			GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST)->SetFocus();
			GetDlgItem(IDOK)->EnableWindow();
			return;
		}
		GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow();
	GetDlgItem(IDOK)->SetFocus();
}

void CMMDDeleteMimicsGroupDialog::OnDeleteAllGroups()
{
	CHourglassCursor  cCursor;

	m_pMimicsGroups.RemoveAll();
	SendDlgItemMessage(IDC_MMD_DELETEMIMICSGROUP_LIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_DELETEMIMICSGROUP_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow();
	GetDlgItem(IDOK)->SetFocus();
}

void CMMDDeleteMimicsGroupDialog::OnOK()
{
	CProfile  cProfile;
	CByteArray  nGroupsInfo;
	CHourglassCursor  cCursor;

	ShowMessage((!m_pMimicsGroups.Map(nGroupsInfo) || !cProfile.SetMimicsGroupsInfo(nGroupsInfo)) ? SYSTEM_WARNING_MIMICSGROUPS_UPDATE_FAILURE : SYSTEM_NOERROR);
	CDisplayDialog::OnOK();
}

BOOL CMMDDeleteMimicsGroupDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGROUPDELETEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDDeleteMimicsGroupDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGROUPDELETEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDInsertMimicsGroupDialog dialog

IMPLEMENT_DYNCREATE(CMMDInsertMimicsGroupDialog, CDisplayDialog)

CMMDInsertMimicsGroupDialog::CMMDInsertMimicsGroupDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDInsertMimicsGroupDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDInsertMimicsGroupDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CMMDInsertMimicsGroupDialog::IDD);
}

CMMDWnd *CMMDInsertMimicsGroupDialog::GetParentDisplay() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CMMDInsertMimicsGroupDialog::EnumMimicsGroups()
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CMimicsGroup  *pGroup;
	CStringArray  szNames;
	CStringArray  szCounts;
	CStringTools  cStringTools;
	CByteArray  nGroupsInfo;
	CProfile  cProfile;

	for (nItem = 0, nItems = (cProfile.GetMimicsGroupsInfo(nGroupsInfo) && m_pMimicsGroups.Unmap(nGroupsInfo)) ? (INT)m_pMimicsGroups.GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pGroup = (CMimicsGroup *)m_pMimicsGroups.GetAt(nItem)) != (CMimicsGroup *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME))
				{
					szItem = pGroup->GetName();
					szNames.Add(szItem);
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT))
				{
					szItem = cStringTools.ConvertIntToString(pGroup->GetItemCount());
					szCounts.Add(szItem);
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_LIST), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_LIST), nItem, nColumn, szItem);
			}
		}
	}
	for (; nItems < 0; )
	{
		ShowMessage(SYSTEM_WARNING_MIMICSGROUPS_LOAD_FAILURE);
		break;
	}
	if (SendDlgItemMessage(IDC_MMD_INSERTMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME))
			{
				SendDlgItemMessage(IDC_MMD_INSERTMIMICSGROUP_LIST, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(szNames)) > 0) ? MAKELPARAM(max((WORD)SendDlgItemMessage(IDC_MMD_INSERTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), nWidth), 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_INSERTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT))
			{
				SendDlgItemMessage(IDC_MMD_INSERTMIMICSGROUP_LIST, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(szCounts)) > 0) ? MAKELPARAM(max((WORD)SendDlgItemMessage(IDC_MMD_INSERTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), nWidth), 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_INSERTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
		}
		Listview_SetCurText(GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_LIST), 0);
	}
	GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_INSERTMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_LIST)->EnableWindow((SendDlgItemMessage(IDC_MMD_INSERTMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

INT CMMDInsertMimicsGroupDialog::CalcColumnWidth(CONST CStringArray &szItems)
{
	CDC  *pDC;
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	CFont  *pOldFont;
	CSize  sizeItem[2];

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_LIST)->GetFont())))
		{
			for (nItem = 0, nItems = (INT)szItems.GetSize(), sizeItem[0].cx = sizeItem[0].cy = 0; nItem < nItems; nItem++)
			{
				sizeItem[1] = pDC->GetTextExtent(szItems.GetAt(nItem));
				sizeItem[0] = (sizeItem[0].cx < sizeItem[1].cx) ? sizeItem[1] : sizeItem[0];
			}
			nWidth = 6 * GetSystemMetrics(SM_CXEDGE) + sizeItem[0].cx;
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return nWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

BOOL CMMDInsertMimicsGroupDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_LIST)) >= 0) ? TRUE : FALSE);
}

void CMMDInsertMimicsGroupDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDInsertMimicsGroupDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDInsertMimicsGroupDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pMimicsGroups.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDInsertMimicsGroupDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDInsertMimicsGroupDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_INSERTMIMICSGROUP_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDInsertMimicsGroupDialog message handlers

BOOL CMMDInsertMimicsGroupDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT));
	SendDlgItemMessage(IDC_MMD_INSERTMIMICSGROUP_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (4 * rColumns.Width()) / 5; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_LIST), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumMimicsGroups();
	GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_DETAILS)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return TRUE;
}

BOOL CMMDInsertMimicsGroupDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_MMD_INSERTMIMICSGROUP_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			OnOK();
			return TRUE;
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CMMDInsertMimicsGroupDialog::OnOK()
{
	CRect  rGroup[2];
	CMimicsGroup  *pGroup;
	CHourglassCursor  cCursor;

	if ((pGroup = m_pMimicsGroups.GetAt(Listview_GetCurText(GetDlgItem(IDC_MMD_INSERTMIMICSGROUP_LIST)))))
	{
		rGroup[0] = pGroup->GetItemPosition();
		rGroup[1] = pGroup->CalcItemFramePosition();
		rGroup[0].OffsetRect(-rGroup[1].left, -rGroup[1].top);
		rGroup[0].OffsetRect(GetParentDisplay()->GetImageView()->GetScrollPos(SB_HORZ), 0);
		rGroup[0].OffsetRect(GetParentDisplay()->GetImageView()->GetImageOrigin().x + 1, 0);
		rGroup[0].OffsetRect(0, GetParentDisplay()->GetImageView()->GetScrollPos(SB_VERT));
		rGroup[0].OffsetRect(0, GetParentDisplay()->GetImageView()->GetImageOrigin().y + 1);
		for (pGroup->SetItemName(STRING(IDS_MMD_STATUSBAR_OBJECTDEFAULTNAME)), pGroup->SetItemPosition(rGroup[0]); GetParentDisplay()->AddMimicsCtrl(pGroup, TRUE); )
		{
			GetParentDisplay()->GetImageView()->SetFocus();
			EndDialog(IDOK);
			return;
		}
	}
	ShowMessage(SYSTEM_WARNING_MIMICSGROUPS_LOAD_FAILURE);
	CDisplayDialog::OnOK();
}

BOOL CMMDInsertMimicsGroupDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGROUPINSERTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDInsertMimicsGroupDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGROUPINSERTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDImportMimicsGroupDialog dialog

IMPLEMENT_DYNCREATE(CMMDImportMimicsGroupDialog, CLocaleDialog)

CMMDImportMimicsGroupDialog::CMMDImportMimicsGroupDialog(CWnd *pParentWnd) : CLocaleDialog(CMMDImportMimicsGroupDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CMMDImportMimicsGroupDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMMDImportMimicsGroupDialog::EnumMimicsGroups()
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CMimicsGroup  *pGroup;
	CStringArray  szNames;
	CStringArray  szCounts;
	CStringTools  cStringTools;
	CByteArray  nGroupsInfo;
	CProfile  cProfile;

	for (nItem = 0, nItems = (cProfile.GetMimicsGroupsInfo(nGroupsInfo) && m_pMimicsGroups.Unmap(nGroupsInfo)) ? (INT)m_pMimicsGroups.GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pGroup = (CMimicsGroup *)m_pMimicsGroups.GetAt(nItem)) != (CMimicsGroup *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME))
				{
					szItem = pGroup->GetName();
					szNames.Add(szItem);
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT))
				{
					szItem = cStringTools.ConvertIntToString(pGroup->GetItemCount());
					szCounts.Add(szItem);
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_LIST), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_LIST), nItem, nColumn, szItem);
			}
		}
	}
	for (; nItems < 0; )
	{
		ShowMessage(SYSTEM_WARNING_MIMICSGROUPS_LOAD_FAILURE);
		break;
	}
	if (SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME))
			{
				SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_LIST, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(szNames)) > 0) ? MAKELPARAM(max((WORD)SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), nWidth), 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT))
			{
				SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_LIST, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(szCounts)) > 0) ? MAKELPARAM(max((WORD)SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), nWidth), 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
		}
		Listview_SetCurText(GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_LIST), 0);
	}
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_LIST)->EnableWindow((SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

INT CMMDImportMimicsGroupDialog::CalcColumnWidth(CONST CStringArray &szItems)
{
	CDC  *pDC;
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	CFont  *pOldFont;
	CSize  sizeItem[2];

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_LIST)->GetFont())))
		{
			for (nItem = 0, nItems = (INT)szItems.GetSize(), sizeItem[0].cx = sizeItem[0].cy = 0; nItem < nItems; nItem++)
			{
				sizeItem[1] = pDC->GetTextExtent(szItems.GetAt(nItem));
				sizeItem[0] = (sizeItem[0].cx < sizeItem[1].cx) ? sizeItem[1] : sizeItem[0];
			}
			nWidth = 6 * GetSystemMetrics(SM_CXEDGE) + sizeItem[0].cx;
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return nWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

BOOL CMMDImportMimicsGroupDialog::Check(BOOL bModified) CONST
{
	CString  szName;
	CString  szFileName;

	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_FILENAME)->GetWindowText(szFileName);
	return((!szName.IsEmpty() && !szFileName.IsEmpty()) ? TRUE : FALSE);
}

void CMMDImportMimicsGroupDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDImportMimicsGroupDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDImportMimicsGroupDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pMimicsGroups.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDImportMimicsGroupDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CMMDImportMimicsGroupDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_IMPORTMIMICSGROUP_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_MMD_IMPORTMIMICSGROUP_HELP, OnHelp)
	ON_EN_CHANGE(IDC_MMD_IMPORTMIMICSGROUP_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_MMD_IMPORTMIMICSGROUP_FILENAME, OnEditchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDImportMimicsGroupDialog message handlers

BOOL CMMDImportMimicsGroupDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT));
	SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (4 * rColumns.Width()) / 5; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_LIST), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumMimicsGroups();
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_FILENAME)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_BROWSE)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_NAME)->EnableWindow();
	return TRUE;
}

BOOL CMMDImportMimicsGroupDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_MMD_IMPORTMIMICSGROUP_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			if (!GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_WARNING)->IsWindowVisible())
			{
				OnOK();
				return TRUE;
			}
		}
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void CMMDImportMimicsGroupDialog::OnBrowse()
{
	CString  szName;
	CString  szFileName;
	CFileDialog  *pFileDialog;

	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_FILENAME)->GetWindowText(szFileName);
	if ((pFileDialog = new CFileDialog(TRUE, STRING(IDS_MMDMIMICSGROUPDIALOG_FILEFORMAT_STANDARDEXTENSION), szFileName, OFN_HIDEREADONLY, STRING(IDS_MMDMIMICSGROUPDIALOG_FILEFORMAT_STANDARDBROWSEFILTER), this)))
	{
		if (pFileDialog->DoModal() == IDOK)
		{
			szFileName = pFileDialog->GetPathName();
			GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_FILENAME)->SetWindowText(szFileName);
		}
		SendDlgItemMessage(IDC_MMD_IMPORTMIMICSGROUP_FILENAME, EM_SETSEL, 0, -1);
		GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_FILENAME)->SetFocus();
		delete pFileDialog;
	}
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_WARNING)->ShowWindow((m_pMimicsGroups.Find(szName) >= 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_WARNING)->EnableWindow((m_pMimicsGroups.Find(szName) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDImportMimicsGroupDialog::OnEditchangeName()
{
	CString  szName;

	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_WARNING)->ShowWindow((m_pMimicsGroups.Find(szName) >= 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_WARNING)->EnableWindow((m_pMimicsGroups.Find(szName) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDImportMimicsGroupDialog::OnEditchangeFileName()
{
	CString  szName;

	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_WARNING)->ShowWindow((m_pMimicsGroups.Find(szName) >= 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_WARNING)->EnableWindow((m_pMimicsGroups.Find(szName) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDImportMimicsGroupDialog::OnOK()
{
	CString  szName;
	CString  szFileName;
	CProfile  cProfile;
	CByteArray  nGroupsInfo;
	CMimicsGroup  *pGroup;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_MMD_IMPORTMIMICSGROUP_FILENAME)->GetWindowText(szFileName);
	if ((pGroup = m_pMimicsGroups.GetAt(m_pMimicsGroups.Find(szName))))
	{
		if (pGroup->LoadAsStandardFile(szFileName))
		{
			pGroup->SetName(szName);
			if (m_pMimicsGroups.Map(nGroupsInfo))
			{
				if (cProfile.SetMimicsGroupsInfo(nGroupsInfo))
				{
					EndDialog(IDOK);
					return;
				}
			}
		}
		ShowMessage(SYSTEM_WARNING_MIMICSGROUP_IMPORT_FAILURE);
		EndDialog(IDOK);
		return;
	}
	if ((pGroup = new CMimicsGroup))
	{
		if (pGroup->LoadAsStandardFile(szFileName))
		{
			pGroup->SetName(szName);
			if (m_pMimicsGroups.Add(pGroup) >= 0)
			{
				if (m_pMimicsGroups.Map(nGroupsInfo))
				{
					if (cProfile.SetMimicsGroupsInfo(nGroupsInfo))
					{
						EndDialog(IDOK);
						return;
					}
				}
				ShowMessage(SYSTEM_WARNING_MIMICSGROUP_IMPORT_FAILURE);
				EndDialog(IDOK);
				return;
			}
		}
		delete pGroup;
	}
	ShowMessage(SYSTEM_WARNING_MIMICSGROUP_IMPORT_FAILURE);
	EndDialog(IDOK);
}

void CMMDImportMimicsGroupDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CMMDImportMimicsGroupDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGROUPIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDImportMimicsGroupDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGROUPIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDExportMimicsGroupDialog dialog

IMPLEMENT_DYNCREATE(CMMDExportMimicsGroupDialog, CLocaleDialog)

CMMDExportMimicsGroupDialog::CMMDExportMimicsGroupDialog(CWnd *pParentWnd) : CLocaleDialog(CMMDExportMimicsGroupDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CMMDExportMimicsGroupDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMMDExportMimicsGroupDialog::EnumMimicsGroups()
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CMimicsGroup  *pGroup;
	CStringArray  szNames;
	CStringArray  szCounts;
	CStringTools  cStringTools;
	CByteArray  nGroupsInfo;
	CProfile  cProfile;

	for (nItem = 0, nItems = (cProfile.GetMimicsGroupsInfo(nGroupsInfo) && m_pMimicsGroups.Unmap(nGroupsInfo)) ? (INT)m_pMimicsGroups.GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pGroup = (CMimicsGroup *)m_pMimicsGroups.GetAt(nItem)) != (CMimicsGroup *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME))
				{
					szItem = pGroup->GetName();
					szNames.Add(szItem);
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT))
				{
					szItem = cStringTools.ConvertIntToString(pGroup->GetItemCount());
					szCounts.Add(szItem);
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_LIST), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_LIST), nItem, nColumn, szItem);
			}
		}
	}
	for (; nItems < 0; )
	{
		ShowMessage(SYSTEM_WARNING_MIMICSGROUPS_LOAD_FAILURE);
		break;
	}
	if (SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME))
			{
				SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_LIST, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(szNames)) > 0) ? MAKELPARAM(max((WORD)SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), nWidth), 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT))
			{
				SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_LIST, LVM_SETCOLUMNWIDTH, nColumn, ((nWidth = CalcColumnWidth(szCounts)) > 0) ? MAKELPARAM(max((WORD)SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), nWidth), 0) : MAKELPARAM(SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_LIST, LVM_GETCOLUMNWIDTH, nColumn), 0));
				continue;
			}
		}
		Listview_SetCurText(GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_LIST), 0);
	}
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_LIST)->EnableWindow((SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

BOOL CMMDExportMimicsGroupDialog::EnumExportFormats()
{
	INT  nFormat;
	INT  nFormats;

	for (nFormat = 0, nFormats = MAXMIMICSGROUPFILEFORMAT - MINMIMICSGROUPFILEFORMAT + 1; nFormat < nFormats; nFormat++)
	{
		SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_FORMAT, CB_INSERTSTRING, nFormat, (LPARAM)STRING(MINMIMICSGROUPFILEFORMAT + nFormat));
		continue;
	}
	SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_FORMAT, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_FORMAT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MMDMIMICSGROUPDIALOG_FILEFORMAT_STANDARD)), 0));
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FORMAT_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_FORMAT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FORMAT)->EnableWindow((SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_FORMAT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_FORMAT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

INT CMMDExportMimicsGroupDialog::CalcColumnWidth(CONST CStringArray &szItems)
{
	CDC  *pDC;
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	CFont  *pOldFont;
	CSize  sizeItem[2];

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_LIST)->GetFont())))
		{
			for (nItem = 0, nItems = (INT)szItems.GetSize(), sizeItem[0].cx = sizeItem[0].cy = 0; nItem < nItems; nItem++)
			{
				sizeItem[1] = pDC->GetTextExtent(szItems.GetAt(nItem));
				sizeItem[0] = (sizeItem[0].cx < sizeItem[1].cx) ? sizeItem[1] : sizeItem[0];
			}
			nWidth = 6 * GetSystemMetrics(SM_CXEDGE) + sizeItem[0].cx;
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return nWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

BOOL CMMDExportMimicsGroupDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_LIST)) >= 0 && GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FILENAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CMMDExportMimicsGroupDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDExportMimicsGroupDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDExportMimicsGroupDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pMimicsGroups.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDExportMimicsGroupDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CMMDExportMimicsGroupDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_EXPORTMIMICSGROUP_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_MMD_EXPORTMIMICSGROUP_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_MMD_EXPORTMIMICSGROUP_FORMAT, OnSelchangeFormat)
	ON_EN_CHANGE(IDC_MMD_EXPORTMIMICSGROUP_FILENAME, OnEditchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDExportMimicsGroupDialog message handlers

BOOL CMMDExportMimicsGroupDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_MMDMIMICSGROUPDIALOG_LISTTITLEITEM_COUNT));
	SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (4 * rColumns.Width()) / 5; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_LIST), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumMimicsGroups();
	EnumExportFormats();
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FILENAME)->EnableWindow();
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_BROWSE)->EnableWindow();
	return TRUE;
}

BOOL CMMDExportMimicsGroupDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_MMD_EXPORTMIMICSGROUP_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			OnOK();
			return TRUE;
		}
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void CMMDExportMimicsGroupDialog::OnBrowse()
{
	INT  nFormat;
	INT  nFormats;
	CString  szFilter;
	CString  szFormat;
	CString  szFileName;
	CString  szExtension;
	CFileDialog  *pFileDialog;

	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FORMAT)->GetWindowText(szFormat);
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FILENAME)->GetWindowText(szFileName);
	for (nFormat = 0, nFormats = MAXMIMICSGROUPFILEFORMAT - MINMIMICSGROUPFILEFORMAT + 1; nFormat < nFormats; nFormat++)
	{
		if (szFormat == STRING(MINMIMICSGROUPFILEFORMAT + nFormat))
		{
			szFilter = STRING(MINMIMICSGROUPFILEFORMATBROWSEFILTER + nFormat);
			szExtension = STRING(MINMIMICSGROUPFILEFORMATEXTENSION + nFormat);
			break;
		}
	}
	if ((pFileDialog = new CFileDialog(FALSE, szExtension, szFileName, OFN_HIDEREADONLY, szFilter, this)))
	{
		if (pFileDialog->DoModal() == IDOK)
		{
			szFileName = pFileDialog->GetPathName();
			GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FILENAME)->SetWindowText(szFileName);
		}
		delete pFileDialog;
	}
	SendDlgItemMessage(IDC_MMD_EXPORTMIMICSGROUP_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDExportMimicsGroupDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDExportMimicsGroupDialog::OnSelchangeFormat()
{
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FILENAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDExportMimicsGroupDialog::OnOK()
{
	CString  szFormat;
	CString  szFileName;
	CMMDDocument  *pDocument;
	CMimicsGroup  *pGroup[2];
	CHourglassCursor  cCursor;

	if ((pGroup[0] = m_pMimicsGroups.GetAt(Listview_GetCurText(GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_LIST)))))
	{
		GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FORMAT)->GetWindowText(szFormat);
		GetDlgItem(IDC_MMD_EXPORTMIMICSGROUP_FILENAME)->GetWindowText(szFileName);
		if (szFormat == STRING(IDS_MMDMIMICSGROUPDIALOG_FILEFORMAT_STANDARD))
		{
			ShowMessage((!pGroup[0]->SaveAsStandardFile(szFileName)) ? SYSTEM_WARNING_MIMICSGROUP_EXPORT_FAILURE : SYSTEM_NOERROR);
			EndDialog(IDOK);
			return;
		}
		if (szFormat == STRING(IDS_MMDMIMICSGROUPDIALOG_FILEFORMAT_BITMAP))
		{
			if ((pDocument = new CMMDDocument) != (CMMDDocument *)NULL)
			{
				if ((pGroup[1] = (CMimicsGroup *)CMimicsItem::Create(pGroup[0], (CView *)NULL, pDocument)))
				{
					ShowMessage((!pGroup[1]->SaveAsBitmap(szFileName)) ? SYSTEM_WARNING_MIMICSGROUP_EXPORT_FAILURE : SYSTEM_NOERROR);
					pDocument->RemoveItem(pGroup[1]);
					pDocument->SetModifiedFlag(FALSE);
					delete pGroup[1];
					delete pDocument;
					EndDialog(IDOK);
					return;
				}
				pDocument->SetModifiedFlag(FALSE);
				delete pDocument;
			}
		}
		if (szFormat == STRING(IDS_MMDMIMICSGROUPDIALOG_FILEFORMAT_METAFILE))
		{
			if ((pDocument = new CMMDDocument) != (CMMDDocument *)NULL)
			{
				if ((pGroup[1] = (CMimicsGroup *)CMimicsItem::Create(pGroup[0], (CView *)NULL, pDocument)))
				{
					ShowMessage((!pGroup[1]->SaveAsMetafile(szFileName)) ? SYSTEM_WARNING_MIMICSGROUP_EXPORT_FAILURE : SYSTEM_NOERROR);
					pDocument->RemoveItem(pGroup[1]);
					pDocument->SetModifiedFlag(FALSE);
					delete pGroup[1];
					delete pDocument;
					EndDialog(IDOK);
					return;
				}
				pDocument->SetModifiedFlag(FALSE);
				delete pDocument;
			}
		}
	}
	ShowMessage(SYSTEM_WARNING_MIMICSGROUP_EXPORT_FAILURE);
	EndDialog(IDOK);
}

void CMMDExportMimicsGroupDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CMMDExportMimicsGroupDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGROUPEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDExportMimicsGroupDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGROUPEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDRotateMimicsObjectDialog dialog

IMPLEMENT_DYNCREATE(CMMDRotateMimicsObjectDialog, CDisplayDialog)

CMMDRotateMimicsObjectDialog::CMMDRotateMimicsObjectDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDRotateMimicsObjectDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDRotateMimicsObjectDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CMMDRotateMimicsObjectDialog::IDD);
}

CMMDWnd *CMMDRotateMimicsObjectDialog::GetParentDisplay() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParentDisplay());
}

void CMMDRotateMimicsObjectDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDRotateMimicsObjectDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMMDRotateMimicsObjectDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDRotateMimicsObjectDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE90, OnAngle90)
	ON_BN_CLICKED(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE180, OnAngle180)
	ON_BN_CLICKED(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE270, OnAngle270)
	ON_BN_CLICKED(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY, OnAngleAny)
	ON_BN_CLICKED(IDC_MMD_ROTATEMIMICSOBJECT_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDRotateMimicsObjectDialog message handlers

BOOL CMMDRotateMimicsObjectDialog::OnInitDialog()
{
	CMimicsItem  *pItem;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	if ((pItem = GetParentDisplay()->GetActivatedMimicsCtrl()))
	{
		GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_NAME)->SetWindowText(pItem->GetItemName());
		GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_TYPE)->SetWindowText(pItem->GetItemType());
	}
	CheckRadioButton(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE90, IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY, IDC_MMD_ROTATEMIMICSOBJECT_ANGLE90);
	Spinbox_SetRange(GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY_NUMBER), -360, 360);
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_NAME)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_TYPE)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE90)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE180)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE270)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow();
	return TRUE;
}

void CMMDRotateMimicsObjectDialog::OnAngle90()
{
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJCT_ANGLEANY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY_NUMBER)->EnableWindow(FALSE);
}

void CMMDRotateMimicsObjectDialog::OnAngle180()
{
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJCT_ANGLEANY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY_NUMBER)->EnableWindow(FALSE);
}

void CMMDRotateMimicsObjectDialog::OnAngle270()
{
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJCT_ANGLEANY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY_NUMBER)->EnableWindow(FALSE);
}

void CMMDRotateMimicsObjectDialog::OnAngleAny()
{
	Spinbox_SetPos(GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY_NUMBER), 90);
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJCT_ANGLEANY_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY_NUMBER)->EnableWindow();
	GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY_NUMBER)->SetFocus();
}

void CMMDRotateMimicsObjectDialog::OnOK()
{
	double  fAngle = 0.0;
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE90)) fAngle = 90.0;
	if (IsDlgButtonChecked(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE180)) fAngle = 180.0;
	if (IsDlgButtonChecked(IDC_MMD_ROTATEMIMICSOBJECT_ANGLE270)) fAngle = 270.0;
	if (IsDlgButtonChecked(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY)) fAngle = (double)Spinbox_GetPos(GetDlgItem(IDC_MMD_ROTATEMIMICSOBJECT_ANGLEANY_NUMBER));
	GetParentDisplay()->DoRotateMimicsCtrl(fAngle);
	CDisplayDialog::OnOK();
}

BOOL CMMDRotateMimicsObjectDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDOBJECTROTATEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDRotateMimicsObjectDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDOBJECTROTATEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDTestParameter

CMMDTestParameter::CMMDTestParameter() : CTMParameter()
{
	return;
}
CMMDTestParameter::CMMDTestParameter(LPCTSTR pszName) : CTMParameter()
{
	SetTag(pszName);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDTestProfile

CMMDTestProfile::CMMDTestProfile() : CPtrArray()
{
	return;
}
CMMDTestProfile::CMMDTestProfile(LPCTSTR pszName) : CPtrArray()
{
	m_szName = pszName;
}

CMMDTestProfile::~CMMDTestProfile()
{
	RemoveAll();
}

VOID CMMDTestProfile::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CMMDTestProfile::GetName() CONST
{
	return m_szName;
}

INT CMMDTestProfile::Add(CMMDTestParameter *pParameter)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pParameter->GetTag(), TRUE)) >= 0) InsertAt(nIndex, pParameter, 1);
	return nIndex;
}

INT CMMDTestProfile::Find(LPCTSTR pszTag) CONST
{
	return FindIndex(pszTag);
}

CMMDTestParameter *CMMDTestProfile::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMMDTestParameter *)CPtrArray::GetAt(nIndex) : (CMMDTestParameter *)NULL);
}

CMMDTestParameter *CMMDTestProfile::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMMDTestParameter *)CPtrArray::GetAt(nIndex) : (CMMDTestParameter *)NULL);
}

VOID CMMDTestProfile::RemoveAll()
{
	INT  nParameter;
	INT  nParameters;

	for (nParameter = 0, nParameters = (INT)GetSize(); nParameter < nParameters; nParameter++)
	{
		delete GetAt(nParameter);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CMMDTestProfile::Copy(CONST CMMDTestProfile *pProfile)
{
	INT  nParameter;
	INT  nParameters;
	CMMDTestParameter  *pParameter;

	for (nParameter = 0, nParameters = (INT)pProfile->GetSize(), m_szName = pProfile->m_szName, RemoveAll(); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = new CMMDTestParameter) != (CMMDTestParameter *)NULL)
		{
			pParameter->Copy(pProfile->GetAt(nParameter));
			InsertAt(nParameter, pParameter, 1);
			continue;
		}
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CMMDTestProfile::Compare(CONST CMMDTestProfile *pProfile) CONST
{
	INT  nParameter;
	INT  nParameters;
	CMMDTestParameter  *pParameter;

	for (nParameter = 0, nParameters = (pProfile->m_szName == m_szName && pProfile->GetSize() == GetSize()) ? (INT)GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if ((pParameter = pProfile->GetAt(nParameter)) && pParameter->Compare(GetAt(nParameter))) continue;
		break;
	}
	return((nParameter == nParameters) ? TRUE : FALSE);
}

BOOL CMMDTestProfile::Map(CByteArray &nData) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nParameter;
	INT  nParameters;
	CByteArray  nParameterData[2];
	CMMDTestParameter  *pParameter;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	for (nParameter = 0, nParameters = (INT)GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = GetAt(nParameter)) && pParameter->Map(nParameterData[1]) && nParameterData[0].Append(nParameterData[1]) >= 0) continue;
		break;
	}
	for (nData.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + (sData.cbParameters = (INT)(nParameterData[0].GetSize()*sizeof(BYTE))))); nData.GetSize() == sData.cbSize && nParameter == nParameters; )
	{
		CopyMemory(nData.GetData(), &sData, sizeof(DATA));
		CopyMemory(nData.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nData.GetData() + (cbData = cbData + sData.cbName), nParameterData[0].GetData(), sData.cbParameters);
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDTestProfile::Unmap(CONST CByteArray &nData)
{
	DATA  sData;
	INT  cbData;
	INT  cbParameter;
	INT  cbParameters;
	CByteArray  nParameterData[2];
	CMMDTestParameter  *pParameter;

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nData.GetSize() >= sizeof(DATA) && nData.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbParameters && sData.cbName > 0 && sData.cbParameters >= 0; )
	{
		for (CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nData.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName)), nParameterData[0].SetSize(sData.cbParameters), CopyMemory(nParameterData[0].GetData(), nData.GetData() + (cbData = cbData + sData.cbName), sData.cbParameters), m_szName.ReleaseBuffer(), RemoveAll(), cbParameter = cbParameters = 0; cbParameters < sData.cbParameters; cbParameters += cbParameter)
		{
			for (CopyMemory(&cbParameter, nParameterData[0].GetData() + cbParameters, sizeof(cbParameter)), nParameterData[1].SetSize(max(min(cbParameter, nParameterData[0].GetSize() - cbParameters), 0)); nParameterData[1].GetSize() >= 0; )
			{
				CopyMemory(nParameterData[1].GetData(), nParameterData[0].GetData() + cbParameters, nParameterData[1].GetSize());
				break;
			}
			if ((pParameter = new CMMDTestParameter))
			{
				if (pParameter->Unmap(nParameterData[1]) && Add(pParameter) >= 0) continue;
				delete pParameter;
			}
			break;
		}
		return((cbParameters == sData.cbParameters) ? TRUE : FALSE);
	}
	return FALSE;
}

INT CMMDTestProfile::FindIndex(LPCTSTR pszTag, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CMMDTestParameter  *pParameter;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pParameter = GetAt(nIndex[0]))) ? ((nIndex[1] = (pParameter->GetTag() <= pszTag)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pParameter = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pParameter->GetTag() == pszTag) || (bInsert && (((pParameter = GetAt(max(nIndex[0] - 1, 0))) && pParameter->GetTag() != pszTag && (pParameter = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pParameter->GetTag() != pszTag) || !GetSize()))) && lstrlen(pszTag) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDTestProfiles

CMMDTestProfiles::CMMDTestProfiles() : CPtrArray()
{
	return;
}

CMMDTestProfiles::~CMMDTestProfiles()
{
	RemoveAll();
}

INT CMMDTestProfiles::Add(CMMDTestProfile *pProfile)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pProfile->GetName(), TRUE)) >= 0) InsertAt(nIndex, pProfile, 1);
	return nIndex;
}

INT CMMDTestProfiles::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CMMDTestProfile *CMMDTestProfiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMMDTestProfile *)CPtrArray::GetAt(nIndex) : (CMMDTestProfile *)NULL);
}

CMMDTestProfile *CMMDTestProfiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMMDTestProfile *)CPtrArray::GetAt(nIndex) : (CMMDTestProfile *)NULL);
}

VOID CMMDTestProfiles::RemoveAll()
{
	INT  nProfile;
	INT  nProfiles;

	for (nProfile = 0, nProfiles = (INT)GetSize(); nProfile < nProfiles; nProfile++)
	{
		delete GetAt(nProfile);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CMMDTestProfiles::Copy(CONST CMMDTestProfiles *pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	CMMDTestProfile  *pProfile;

	for (nProfile = 0, nProfiles = (INT)pProfiles->GetSize(), RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfile = new CMMDTestProfile) != (CMMDTestProfile *)NULL)
		{
			pProfile->Copy(pProfiles->GetAt(nProfile));
			InsertAt(nProfile, pProfile, 1);
			continue;
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CMMDTestProfiles::Compare(CONST CMMDTestProfiles *pProfiles) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CMMDTestProfile  *pProfile;

	for (nProfile = 0, nProfiles = (pProfiles->GetSize() == GetSize()) ? (INT)GetSize() : -1; nProfile < nProfiles; nProfile++)
	{
		if ((pProfile = pProfiles->GetAt(nProfile)) && pProfile->Compare(GetAt(nProfile))) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CMMDTestProfiles::Map(CByteArray &nData) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CByteArray  nProfileData;
	CMMDTestProfile  *pProfile;

	for (nProfile = 0, nProfiles = (INT)GetSize(), nData.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfile = GetAt(nProfile)) && pProfile->Map(nProfileData) && nData.Append(nProfileData) >= 0) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CMMDTestProfiles::Unmap(CONST CByteArray &nData)
{
	INT  cbProfile;
	INT  cbProfiles;
	CByteArray  nProfileData;
	CMMDTestProfile  *pProfile;

	for (cbProfiles = 0, RemoveAll(); cbProfiles < nData.GetSize(); cbProfiles += cbProfile)
	{
		for (CopyMemory(&cbProfile, nData.GetData() + cbProfiles, sizeof(cbProfile)), nProfileData.SetSize(max(min(cbProfile, nData.GetSize() - cbProfiles), 0)); nProfileData.GetSize() >= 0; )
		{
			CopyMemory(nProfileData.GetData(), nData.GetData() + cbProfiles, nProfileData.GetSize());
			break;
		}
		if ((pProfile = new CMMDTestProfile))
		{
			if (pProfile->Unmap(nProfileData) && Add(pProfile) >= 0) continue;
			delete pProfile;
		}
		break;
	}
	return((cbProfiles == nData.GetSize()) ? TRUE : FALSE);
}

INT CMMDTestProfiles::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CMMDTestProfile  *pProfile;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pProfile = GetAt(nIndex[0]))) ? ((nIndex[1] = (pProfile->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pProfile = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pProfile->GetName() == pszName) || (bInsert && (((pProfile = GetAt(max(nIndex[0] - 1, 0))) && pProfile->GetName() != pszName && (pProfile = GetAt(min(nIndex[0], (INT)GetUpperBound()))) && pProfile->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDTestDialog dialog

IMPLEMENT_DYNCREATE(CMMDTestDialog, CDisplayDialog)

CMMDTestDialog::CMMDTestDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDTestDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDTestDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CMMDTestDialog::IDD);
}

CMMDWnd *CMMDTestDialog::GetParentDisplay() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CMMDTestDialog::EnumParameters()
{
	INT  nItem;
	INT  nItems;
	INT  nParameter;
	INT  nParameters;
	CString  szItem;
	CString  szProcedure;
	CString  szParameter;
	CPtrArray  pItems;
	CPtrArray  pItemsCode;
	CMimicsItem  *pItem;
	CStringArray  szItems;
	CStringArray  szParameters;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	BOOL(__cdecl *pInitialize)(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CONST CStringArray &szItems, CPtrArray &pItems, CStringArray &szParameters);

	for (nItem = 0, nItems = (LoadCode()) ? GetParentDisplay()->EnumMimicsCtrls(pItems) : -1; nItem < nItems; nItem++)
	{
		if ((pItem = (CMimicsItem *)pItems.GetAt(nItem)))
		{
			szItem = pItem->GetItemName();
			szItems.Add(szItem);
		}
	}
	if (nItems >= 0)
	{
		if ((m_pDocument = new CMMDDocument))
		{
			if (m_pDocument->Copy(GetParentDisplay()->GetImageView()->GetDocument()))
			{
#ifndef UNICODE
				szProcedure = STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAY);
#else
				WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAY), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAY))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAY)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				szProcedure.ReleaseBuffer();
#endif
				if ((pInitialize = (BOOL(__cdecl *)(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CONST CStringArray &szItems, CPtrArray &pItems, CStringArray &szParameters)) GetProcAddress(m_hImageCode, (LPCSTR)(LPCTSTR)szProcedure)))
				{
					if ((*pInitialize)(GetDatabase(), &m_cTMEnvironment, szItems, pItemsCode, szParameters))
					{
						for (nItem = 0, nItems = (pItems.GetSize() == pItemsCode.GetSize()) ? (INT)pItems.GetSize() : -1; nItem < nItems; nItem++)
						{
							if (!pItemsCode.GetAt(nItem))
							{
								pItemsCode.RemoveAt(nItem);
								pItems.RemoveAt(nItem);
								nItems--;
								nItem--;
							}
						}
						for (nParameter = 0, nParameters = (nItem == nItems) ? (INT)szParameters.GetSize() : -1; nParameter < nParameters; nParameter++)
						{
							if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameters.GetAt(nParameter)))))
							{
								szParameter.Format(STRING(IDS_MMDTESTDIALOG_PARAMETER_FORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
								SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
							}
						}
						if (nParameters == SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCOUNT) && nParameters > 0)
						{
							SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_SETCURSEL);
							m_szItemParameters.Copy(szParameters);
							m_pItemsCode.Copy(pItemsCode);
							m_pItems.Copy(pItems);
							return TRUE;
						}
						SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_RESETCONTENT);
					}
				}
			}
			delete m_pDocument;
		}
	}
	m_pDocument = (CMMDDocument *)NULL;
	return FALSE;
}

BOOL CMMDTestDialog::EnumParameterTables()
{
	INT  nTable;
	INT  nTables;
	CString  szTable;
	CStringArray  szTables[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_RESETCONTENT);
	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))))
	{
		for (nTable = 0, nTables = pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1]); nTable < nTables; nTable = nTable + 1)
		{
			if ((pDatabaseTMNumCalTable = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTMNumCalTables()->GetAt(GetDatabase()->GetTMNumCalTables()->Find(szTables[0].GetAt(nTable))) : (CDatabaseTMNumCalTable *)NULL))
			{
				szTable.Format(STRING(IDS_MMDTESTDIALOG_TABLE_FORMAT), (LPCTSTR)pDatabaseTMNumCalTable->GetName(), (LPCTSTR)pDatabaseTMNumCalTable->GetDescription());
				SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
				continue;
			}
			if ((pDatabaseTMTxtCalTable = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTMTxtCalTables()->GetAt(GetDatabase()->GetTMTxtCalTables()->Find(szTables[0].GetAt(nTable))) : (CDatabaseTMTxtCalTable *)NULL))
			{
				szTable.Format(STRING(IDS_MMDTESTDIALOG_TABLE_FORMAT), (LPCTSTR)pDatabaseTMTxtCalTable->GetName(), (LPCTSTR)pDatabaseTMTxtCalTable->GetDescription());
				SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
				continue;
			}
		}
	}
	SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_SETCURSEL);
	GetDlgItem(IDC_MMD_TEST_TABLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_TABLE)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CMMDTestDialog::EnumParameterTableValues()
{
	INT  nIndex;
	INT  nPoint;
	INT  nPoints;
	double  fX[2];
	CString  szValue;
	CString  szPoint;
	CString  szRange;
	CStringArray  szTables[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTMTxtCalPoint  *pDatabaseTMTxtCalPoint;

	SendDlgItemMessage(IDC_MMD_TEST_VALUE, CB_RESETCONTENT);
	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))))
	{
		for (nPoint = 0, nPoints = ((pDatabaseTMTxtCalTable = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) && (nIndex = (INT)SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_GETCURSEL)) >= 0 && nIndex < pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1])) ? GetDatabase()->GetTMTxtCalTables()->GetAt(GetDatabase()->GetTMTxtCalTables()->Find(szTables[0].GetAt(nIndex))) : (CDatabaseTMTxtCalTable *)NULL)) ? (INT)pDatabaseTMTxtCalTable->GetSize() : 0; nPoint < nPoints; nPoint++)
		{
			if ((pDatabaseTMTxtCalPoint = pDatabaseTMTxtCalTable->GetAt(nPoint)))
			{
				if (pDatabaseTMTxtCalPoint->GetPoint(fX[0], szValue))
				{
					szPoint.Format(STRING(IDS_MMDTESTDIALOG_POINTVALUE_FORMAT), (LPCTSTR)szValue, (LONGLONG)fX[0]);
					SendDlgItemMessage(IDC_MMD_TEST_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szPoint);
					continue;
				}
				if (pDatabaseTMTxtCalPoint->GetRange(fX[0], fX[1], szValue))
				{
					szPoint.Format(STRING(IDS_MMDTESTDIALOG_RANGEVALUE_FORMAT), (LPCTSTR)szValue, (LONGLONG)fX[0], (LONGLONG)fX[1]);
					SendDlgItemMessage(IDC_MMD_TEST_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szRange);
					continue;
				}
			}
		}
	}
	return((SendDlgItemMessage(IDC_MMD_TEST_VALUE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CMMDTestDialog::EnumParameterProfiles()
{
	INT  nProfile;
	INT  nProfiles;
	CMMDTestProfile  *pProfile;

	for (nProfile = 0, nProfiles = (LoadProfiles()) ? (INT)m_pProfiles[0].GetSize() : 0; nProfile < nProfiles; nProfile++)
	{
		if ((pProfile = (CMMDTestProfile *)m_pProfiles[0].GetAt(nProfile)) != (CMMDTestProfile *)NULL)
		{
			SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pProfile->GetName());
			continue;
		}
	}
	SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_SETCURSEL);
	GetDlgItem(IDC_MMD_TEST_PROFILES_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_PROFILES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_PROFILES_TEST)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_ADDPROFILE)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_GETCOUNT) > 0) ? EnumParameterProfileMembers() : FALSE);
}

BOOL CMMDTestDialog::EnumParameterProfileMembers()
{
	INT  nMember;
	INT  nSample;
	INT  nMembers;
	INT  nSamples;
	CString  szValue;
	CString  szMember;
	CString  szProfile;
	CString  szParameter;
	CMMDTestProfile  *pProfile;
	CMMDTestParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CTMParameter  *pTMParameter;

	SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_RESETCONTENT);
	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->GetWindowText(szProfile);
	for (nMember = 0, nMembers = ((pProfile = m_pProfiles[0].GetAt(m_pProfiles[0].Find(szProfile)))) ? (INT)pProfile->GetSize() : 0; nMember < nMembers; nMember++)
	{
		if ((pParameter = (CMMDTestParameter *)pProfile->GetAt(nMember)) != (CMMDTestParameter *)NULL)
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetTag()))))
			{
				for (nSample = 0, nSamples = pParameter->GetValueCount(); nSample < nSamples; nSample++)
				{
					if (pParameter->GetValueAsText(GetDatabase(), nSample, szValue)) break;
					continue;
				}
				szParameter.Format(STRING(IDS_MMDTESTDIALOG_PARAMETER_FORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
				szMember.Format(STRING(IDS_MMDTESTDIALOG_SCRIPT_PARAMETER_FORMAT), (LPCTSTR)szParameter, (LPCTSTR)szValue);
				SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szMember);
			}
		}
	}
	GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_ADD)->EnableWindow(((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))) && pTMParameter->GetValueCount() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_REMOVE)->EnableWindow(FALSE);
	return TRUE;
}

VOID CMMDTestDialog::ShowParameterDetails()
{
	INT  nTable;
	INT  nTables;
	UINT  nStatus;
	CString  szTable;
	CString  szValue;
	ULONGLONG  nValue;
	CStringArray  szTables[2];
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))))
	{
		if ((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(pDatabaseTMParameter->GetTag()))) && pTMParameter->GetRawValue(MMDTESTDIALOG_DEFAULTSAMPLE, nValue, nStatus, szTable))
		{
			for (nTable = 0, nTables = (!szTable.IsEmpty()) ? pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1]) : 0, EnumParameterTables(); nTable < nTables; nTable++)
			{
				if (szTables[0].GetAt(nTable) == szTable) break;
				continue;
			}
			Spinbox_SetPos(GetDlgItem(IDC_MMD_TEST_SAMPLE), MMDTESTDIALOG_DEFAULTSAMPLE);
			SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_SETCURSEL, (nTable < nTables) ? nTable : -1);
			CheckDlgButton(IDC_MMD_TEST_STATUS_NOLIMIT, (nStatus & TMPARAMETER_STATUS_NOLIMIT) ? TRUE : FALSE);
			CheckDlgButton(IDC_MMD_TEST_STATUS_HARDLIMIT, (nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? TRUE : FALSE);
			CheckDlgButton(IDC_MMD_TEST_STATUS_SOFTLIMIT, (nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? TRUE : FALSE);
			CheckDlgButton(IDC_MMD_TEST_STATUS_DELTALIMIT, (nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? TRUE : FALSE);
			CheckDlgButton(IDC_MMD_TEST_STATUS_CONSISTENCYLIMIT, (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? TRUE : FALSE);
			CheckDlgButton(IDC_MMD_TEST_QUALITY_BADDATA, (nStatus & TMPARAMETER_STATUS_BAD) ? TRUE : FALSE);
			CheckDlgButton(IDC_MMD_TEST_QUALITY_INVALIDDATA, (nStatus & TMPARAMETER_STATUS_INVALID) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_TEST_VALUE)->SetWindowText((pTMParameter->GetValueAsText(GetDatabase(), (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_TEST_SAMPLE)), szValue)) ? szValue : EMPTYSTRING);
			GetDlgItem(IDC_MMD_TEST_TABLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_TEST_TABLE)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			return;
		}
		EnumParameterTables();
		EnumParameterTableValues();
	}
	else
	{
		SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_RESETCONTENT);
		SendDlgItemMessage(IDC_MMD_TEST_VALUE, CB_RESETCONTENT);
	}
	Spinbox_SetPos(GetDlgItem(IDC_MMD_TEST_SAMPLE), MMDTESTDIALOG_DEFAULTSAMPLE);
	CheckDlgButton(IDC_MMD_TEST_STATUS_NOLIMIT, TRUE);
	CheckDlgButton(IDC_MMD_TEST_STATUS_HARDLIMIT, FALSE);
	CheckDlgButton(IDC_MMD_TEST_STATUS_SOFTLIMIT, FALSE);
	CheckDlgButton(IDC_MMD_TEST_STATUS_DELTALIMIT, FALSE);
	CheckDlgButton(IDC_MMD_TEST_STATUS_CONSISTENCYLIMIT, FALSE);
	CheckDlgButton(IDC_MMD_TEST_QUALITY_BADDATA, FALSE);
	CheckDlgButton(IDC_MMD_TEST_QUALITY_INVALIDDATA, FALSE);
	GetDlgItem(IDC_MMD_TEST_VALUE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_TEST_TABLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_TABLE)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CMMDTestDialog::Test()
{
	Test(&m_cTMEnvironment);
}
VOID CMMDTestDialog::Test(CONST CTMEnvironment *pTMEnvironment)
{
	INT  nItem;
	INT  nItems;
	CView  *pView;
	CTMUnit  cTMUnit;
	CMimicsItem  *pItem;
	CMimicsObjectDispatchDriver  *pItemDriver;

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = (CMimicsItem *)m_pItems.GetAt(nItem)) != (CMimicsItem *)NULL)
		{
			if ((pItemDriver = (CMimicsObjectDispatchDriver *)m_pItemsCode.GetAt(nItem)))
			{
				pItem->Lock();
				pItemDriver->AttachDispatch(pItem);
				pItemDriver->Update(GetDatabase(), pTMEnvironment);
				pItemDriver->ReleaseDispatch();
				pItem->Unlock();
			}
			if ((pView = (nItem == nItems - 1) ? pItem->GetItemImage() : (CView *)NULL))
			{
				pView->Invalidate(FALSE);
				pView->UpdateWindow();
			}
		}
	}
	ShowParameterDetails();
}

VOID CMMDTestDialog::Stop()
{
	INT  nItem;
	INT  nItems;
	CView  *pView;
	CMimicsItem  *pItem;
	CMimicsObjectDispatchDriver  *pItemDriver;

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = (CMimicsItem *)m_pItems.GetAt(nItem)) != (CMimicsItem *)NULL)
		{
			if ((pItemDriver = (CMimicsObjectDispatchDriver *)m_pItemsCode.GetAt(nItem)))
			{
				pItem->Lock();
				pItemDriver->AttachDispatch(pItem);
				pItemDriver->Blink(0);
				pItemDriver->ReleaseDispatch();
				pItem->Unlock();
			}
			if ((pView = (nItem == nItems - 1) ? pItem->GetItemImage() : (CView *)NULL))
			{
				pView->Invalidate(FALSE);
				pView->UpdateWindow();
			}
		}
	}
}

VOID CMMDTestDialog::Reset()
{
	POSITION  lPosition[2];
	CMimicsItem  *pItem[2];
	CMMDImageView  *pView;

	if ((pView = GetParentDisplay()->GetImageView()))
	{
		for (lPosition[0] = pView->GetDocument()->GetStartPosition(), lPosition[1] = (m_pDocument != (CMMDDocument *)NULL) ? m_pDocument->GetStartPosition() : (POSITION)NULL; lPosition[0] && lPosition[1]; )
		{
			if ((pItem[0] = (CMimicsItem *)pView->GetDocument()->GetNextItem(lPosition[0])))
			{
				if ((pItem[1] = (CMimicsItem *)m_pDocument->GetNextItem(lPosition[1])))
				{
					if (pItem[0]->GetItemType() == pItem[1]->GetItemType())
					{
						pItem[0]->Copy(pItem[1]);
						Reset(pItem[0]);
						continue;
					}
				}
			}
			break;
		}
		pView->Invalidate(FALSE);
		pView->UpdateWindow();
	}
}
VOID CMMDTestDialog::Reset(CMimicsItem *pItem)
{
	POSITION  lPosition;
	CMimicsItem  *pMimicsItem;
	CMimicsGroup  *pGroup;

	pItem->Lock();
	if (!pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)))
	{
		pItem->UpdateProperties();
		pItem->ResetState();
		pItem->Unlock();
		return;
	}
	for (lPosition = (pGroup = (CMimicsGroup *)pItem)->GetItemList()->GetStartPosition(); lPosition; )
	{
		if ((pMimicsItem = (CMimicsItem *)pGroup->GetItemList()->GetNextItem(lPosition)))
		{
			Reset(pMimicsItem);
			continue;
		}
	}
	pItem->Unlock();
}

BOOL CMMDTestDialog::UpdateParameter(CTMParameter *pTMParameter) CONST
{
	CString  szValue;

	GetDlgItem(IDC_MMD_TEST_VALUE)->GetWindowText(szValue);
	return UpdateParameter(pTMParameter, szValue);
}
BOOL CMMDTestDialog::UpdateParameter(CTMParameter *pTMParameter, LPCTSTR pszValue) CONST
{
	INT  nIndex;
	BYTE  nStatus;
	CString  szTable;
	CStringArray  szTables[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;

	szTable = ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag()))) && (nIndex = (INT)GetDlgItem(IDC_MMD_TEST_TABLE)->SendMessage(CB_GETCURSEL)) >= 0 && nIndex < pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1])) ? szTables[0].GetAt(nIndex) : EMPTYSTRING;
	nStatus = (IsDlgButtonChecked(IDC_MMD_TEST_STATUS_NOLIMIT)) ? TMPARAMETER_STATUS_NOLIMIT : TMPARAMETER_STATUS_NONE;
	nStatus = (IsDlgButtonChecked(IDC_MMD_TEST_STATUS_SOFTLIMIT)) ? TMPARAMETER_STATUS_SOFTLIMIT : nStatus;
	nStatus = (IsDlgButtonChecked(IDC_MMD_TEST_STATUS_HARDLIMIT)) ? TMPARAMETER_STATUS_HARDLIMIT : nStatus;
	nStatus = (IsDlgButtonChecked(IDC_MMD_TEST_STATUS_DELTALIMIT)) ? TMPARAMETER_STATUS_DELTALIMIT : nStatus;
	nStatus = (IsDlgButtonChecked(IDC_MMD_TEST_STATUS_CONSISTENCYLIMIT)) ? TMPARAMETER_STATUS_CONSISTENCYLIMIT : nStatus;
	nStatus |= (!IsDlgButtonChecked(IDC_MMD_TEST_QUALITY_INVALIDDATA)) ? TMPARAMETER_STATUS_VALID : TMPARAMETER_STATUS_INVALID;
	nStatus |= (!IsDlgButtonChecked(IDC_MMD_TEST_QUALITY_BADDATA)) ? TMPARAMETER_STATUS_GOOD : TMPARAMETER_STATUS_BAD;
	return UpdateParameter(pTMParameter, pszValue, (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_TEST_SAMPLE)), nStatus, szTable);
}
BOOL CMMDTestDialog::UpdateParameter(CTMParameter *pTMParameter, LPCTSTR pszValue, INT nSample, BYTE nStatus, LPCTSTR pszTable) CONST
{
	INT  nPoint;
	INT  nPoints;
	double  fX[2];
	double  fValue;
	double  fRawValue;
	CString  szValue;
	CString  szPoint;
	CString  szRange;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMNumCalPoint  *pDatabaseTMNumCalPoint[2];
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTMTxtCalPoint  *pDatabaseTMTxtCalPoint;

	if (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)
	{
		if ((pDatabaseTMNumCalTable = ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())))) ? GetDatabase()->GetTMNumCalTables()->GetAt(GetDatabase()->GetTMNumCalTables()->Find(pszTable)) : (CDatabaseTMNumCalTable *)NULL))
		{
			for (nPoint = 0, nPoints = (GetDatabase()->CheckTMParameterConstValue(pTMParameter->GetAttributes() | TMPARAMETER_NATURE_CONSTANT, pszValue)) ? (INT)(pDatabaseTMNumCalTable->GetSize() - 1) : -1, fValue = _tstof(pszValue); nPoint < nPoints; nPoint++)
			{
				if ((pDatabaseTMNumCalPoint[0] = pDatabaseTMNumCalTable->GetAt(nPoint)) != (CDatabaseTMNumCalPoint *)NULL)
				{
					if ((pDatabaseTMNumCalPoint[1] = pDatabaseTMNumCalTable->GetAt(nPoint + 1)) != (CDatabaseTMNumCalPoint *)NULL)
					{
						if ((fValue >= pDatabaseTMNumCalPoint[0]->GetY() && fValue <= pDatabaseTMNumCalPoint[1]->GetY()) || (fValue <= pDatabaseTMNumCalPoint[0]->GetY() && fValue >= pDatabaseTMNumCalPoint[1]->GetY()))
						{
							fRawValue = pDatabaseTMNumCalPoint[0]->GetX() + ((fValue - pDatabaseTMNumCalPoint[0]->GetY()) / (pDatabaseTMNumCalPoint[1]->GetY() - pDatabaseTMNumCalPoint[0]->GetY()))*(pDatabaseTMNumCalPoint[1]->GetX() - pDatabaseTMNumCalPoint[0]->GetX());
							break;
						}
					}
				}
			}
			if (nPoint < nPoints)
			{
				UpdateParameter(pTMParameter, (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), fRawValue, FALSE) : CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (ULONGLONG)fRawValue, FALSE), nSample, nStatus, pDatabaseTMNumCalTable->GetName());
				return TRUE;
			}
			if (nPoint == nPoints)
			{
				if ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_INTERPRETATION_FULL) != TMPARAMETER_INTERPRETATION_FULL)
				{
					if ((pDatabaseTMNumCalPoint[0] = pDatabaseTMNumCalTable->GetAt(0)))
					{
						if ((pDatabaseTMNumCalPoint[1] = pDatabaseTMNumCalTable->GetAt(1)))
						{
							if ((fRawValue = pDatabaseTMNumCalPoint[0]->GetX() + ((fValue - pDatabaseTMNumCalPoint[0]->GetY()) / (pDatabaseTMNumCalPoint[1]->GetY() - pDatabaseTMNumCalPoint[0]->GetY()))*(pDatabaseTMNumCalPoint[1]->GetX() - pDatabaseTMNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pDatabaseTMParameter->GetWidth()))
							{
								UpdateParameter(pTMParameter, (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), fRawValue, FALSE) : CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (UINT)fRawValue, FALSE), nSample, nStatus, pDatabaseTMNumCalTable->GetName());
								return TRUE;
							}
						}
					}
					if ((pDatabaseTMNumCalPoint[0] = pDatabaseTMNumCalTable->GetAt((INT)pDatabaseTMNumCalTable->GetUpperBound() - 1)))
					{
						if ((pDatabaseTMNumCalPoint[1] = pDatabaseTMNumCalTable->GetAt((INT)pDatabaseTMNumCalTable->GetUpperBound())))
						{
							if ((fRawValue = pDatabaseTMNumCalPoint[0]->GetX() + ((fValue - pDatabaseTMNumCalPoint[0]->GetY()) / (pDatabaseTMNumCalPoint[1]->GetY() - pDatabaseTMNumCalPoint[0]->GetY()))*(pDatabaseTMNumCalPoint[1]->GetX() - pDatabaseTMNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pDatabaseTMParameter->GetWidth()))
							{
								UpdateParameter(pTMParameter, (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), fRawValue, FALSE) : CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (UINT)fRawValue, FALSE), nSample, nStatus, pDatabaseTMNumCalTable->GetName());
								return TRUE;
							}
						}
					}
				}
			}
			return FALSE;
		}
	}
	if (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
	{
		if ((pDatabaseTMTxtCalTable = ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())))) ? GetDatabase()->GetTMTxtCalTables()->GetAt(GetDatabase()->GetTMTxtCalTables()->Find(pszTable)) : (CDatabaseTMTxtCalTable *)NULL))
		{
			for (nPoint = 0, nPoints = (INT)pDatabaseTMTxtCalTable->GetSize(); nPoint < nPoints; nPoint++)
			{
				if ((pDatabaseTMTxtCalPoint = pDatabaseTMTxtCalTable->GetAt(nPoint)))
				{
					if (pDatabaseTMTxtCalPoint->GetPoint(fX[0], szValue))
					{
						szPoint.Format(STRING(IDS_MMDTESTDIALOG_POINTVALUE_FORMAT), (LPCTSTR)szValue, (LONGLONG)fX[0]);
						if (szValue == pszValue || szPoint == pszValue) break;
					}
					if (pDatabaseTMTxtCalPoint->GetRange(fX[0], fX[1], szValue))
					{
						szRange.Format(STRING(IDS_MMDTESTDIALOG_RANGEVALUE_FORMAT), (LPCTSTR)szValue, (LONGLONG)fX[0], (LONGLONG)fX[1]);
						if (szValue == pszValue || szRange == pszValue) break;
					}
				}
			}
			if (nPoint < nPoints)
			{
				UpdateParameter(pTMParameter, (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), fX[0], FALSE) : CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (UINT)fX[0], FALSE), nSample, nStatus, pDatabaseTMTxtCalTable->GetName());
				return TRUE;
			}
			return FALSE;
		}
	}
	if (GetDatabase()->CheckTMParameterConstValue(pTMParameter->GetAttributes() | TMPARAMETER_NATURE_CONSTANT, pszValue))
	{
		for (fValue = _tstof(pszValue); (pDatabaseTMParameter = (pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())) : (CDatabaseTMParameter *)NULL); )
		{
			if (pTMParameter->GetAttributes() & TMPARAMETER_RADIX_BINARY) fValue = (double)CDatabaseEngine::ParseValue(pszValue, 2);
			if (pTMParameter->GetAttributes() & TMPARAMETER_RADIX_OCTAL) fValue = (double)CDatabaseEngine::ParseValue(pszValue, 8);
			if (pTMParameter->GetAttributes() & TMPARAMETER_RADIX_HEXADECIMAL) fValue = (double)CDatabaseEngine::ParseValue(pszValue, 16);
			UpdateParameter(pTMParameter, CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (UINT)fValue, FALSE), nSample, nStatus, EMPTYSTRING);
			return TRUE;
		}
		if ((pDatabaseTMParameter = (pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())) : (CDatabaseTMParameter *)NULL))
		{
			UpdateParameter(pTMParameter, CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (UINT)fValue, FALSE), nSample, nStatus, EMPTYSTRING);
			return TRUE;
		}
		if (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)
		{
			UpdateParameter(pTMParameter, CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), fValue, FALSE), nSample, nStatus, EMPTYSTRING);
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CMMDTestDialog::UpdateParameter(CTMParameter *pTMParameter, ULONGLONG nRawValue, INT nSample, BYTE nStatus, LPCTSTR pszTable) CONST
{
	CTMUnit  cTMUnit;
	CTimeTag  tTMUnit;

	cTMUnit.SetTag(STRING(IDS_TMUNIT_INTERACTIVE));
	cTMUnit.SetTimeTag((pTMParameter->GetLastUpdateTime() > 0) ? pTMParameter->GetLastUpdateTime() : tTMUnit.GetTime());
	return pTMParameter->SetRawValue(&cTMUnit, nSample, nRawValue, nStatus, pszTable);
}

BOOL CMMDTestDialog::CheckParameterValue() CONST
{
	CString  szValue;

	GetDlgItem(IDC_MMD_TEST_VALUE)->GetWindowText(szValue);
	return CheckParameterValue(szValue);
}
BOOL CMMDTestDialog::CheckParameterValue(LPCTSTR pszValue) CONST
{
	CTMParameter  *pTMParameter;

	return(((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(GetDlgItem(IDC_MMD_TEST_PARAMETER)->SendMessage(CB_GETCURSEL)))))) ? CheckParameterValue(pTMParameter, pszValue) : FALSE);
}
BOOL CMMDTestDialog::CheckParameterValue(CONST CTMParameter *pTMParameter, LPCTSTR pszValue) CONST
{
	CTMParameter  cTMParameter;

	cTMParameter.Copy(pTMParameter);
	return((UpdateParameter(&cTMParameter, pszValue)) ? !cTMParameter.Compare(pTMParameter) : FALSE);
}

BOOL CMMDTestDialog::LoadCode()
{
	CString  szCode[2];
	CString  szMessage;
	CString  szProcedure;
	HINSTANCE  hImageCode;
	CFileFindEx  cFileFind[2];
	CStringArray  szParameters;
	BOOL(__cdecl *pInitializeParameters)(CONST CDatabaseEngine *pDatabase, CStringArray &szErrors);

	if (m_cTMEnvironment.Create(GetDatabase()))
	{
		if ((cFileFind[0].FindFile(GetDatabase()->GetFileName()) || cFileFind[0].FindFile(GetDatabase()->GetUpdateFileName())) && !cFileFind[0].FindNextFile())
		{
			szCode[0].Format(STRING(IDS_MIMICSDISPLAYCODE_NORMAL_FILENAME), (LPCTSTR)GetParentDisplay()->GetName());
			szCode[1].Format(STRING(IDS_MIMICSDISPLAYCODE_UPDATE_FILENAME), (LPCTSTR)GetParentDisplay()->GetName());
			szCode[0] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[0];
			szCode[1] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[1];
			if (cFileFind[1].FindFile(szCode[1]) && !cFileFind[1].FindNextFile())
			{
				szCode[0] = szCode[1];
				cFileFind[1].Close();
			}
			if (cFileFind[1].FindFile(szCode[0]) && !cFileFind[1].FindNextFile())
			{
				if ((hImageCode = (!(hImageCode = AfxLoadLibrary(cFileFind[1].GetFileName()))) ? AfxLoadLibrary(szCode[0]) : hImageCode))
				{
#ifndef UNICODE
					szProcedure = STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAYPARAMETERS);
#else
					WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAYPARAMETERS), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAYPARAMETERS))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAYPARAMETERS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
					szProcedure.ReleaseBuffer();
#endif
					if ((pInitializeParameters = (BOOL(__cdecl *)(CONST CDatabaseEngine *pDatabase, CStringArray &szErrors)) GetProcAddress(hImageCode, (LPCSTR)(LPCTSTR)szProcedure)))
					{
						if ((*pInitializeParameters)(GetDatabase(), szParameters))
						{
							m_hImageCode = hImageCode;
							cFileFind[1].Close();
							cFileFind[0].Close();
							return TRUE;
						}
					}
					AfxFreeLibrary(hImageCode);
				}
				cFileFind[1].Close();
			}
			cFileFind[0].Close();
		}
		m_cTMEnvironment.Destroy();
	}
	szMessage.Format(STRING(IDS_MMD_FAILURE_TEST), (LPCTSTR)GetParentDisplay()->GetName());
	ShowMessage(szMessage);
	return FALSE;
}

VOID CMMDTestDialog::FreeCode()
{
	AfxFreeLibrary(m_hImageCode);
	m_hImageCode = (HINSTANCE)NULL;
}

BOOL CMMDTestDialog::SaveProfiles()
{
	CByteArray  nInfo;
	CProfile  cProfile;

	return((m_pProfiles[0].Map(nInfo) && cProfile.SetMimicsTestInfo(nInfo)) ? TRUE : FALSE);
}

BOOL CMMDTestDialog::LoadProfiles()
{
	INT  nProfile;
	INT  nProfiles;
	INT  nParameter;
	INT  nParameters;
	CByteArray  nInfo;
	CMMDTestProfile  *pProfile[2];
	CMMDTestParameter  *pParameter[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CProfile  cProfile;

	for (nProfile = 0, nProfiles = (cProfile.GetMimicsTestInfo(nInfo) && m_pProfiles[0].Unmap(nInfo)) ? (INT)m_pProfiles[0].GetSize() : -1; nProfile < nProfiles; nProfile++)
	{
		if ((pProfile[0] = m_pProfiles[0].GetAt(nProfile)) != (CMMDTestProfile *)NULL)
		{
			if ((pProfile[1] = new CMMDTestProfile) != (CMMDTestProfile *)NULL)
			{
				for (nParameter = 0, nParameters = (INT)pProfile[0]->GetSize(), pProfile[1]->SetName(pProfile[0]->GetName()); nParameter < nParameters; nParameter++)
				{
					if ((pParameter[0] = pProfile[0]->GetAt(nParameter)))
					{
						if ((pParameter[1] = new CMMDTestParameter))
						{
							if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter[0]->GetTag()))))
							{
								pParameter[0]->SetAttributes(pDatabaseTMParameter->GetAttributes());
								pParameter[1]->Copy(pParameter[0]);
								pProfile[1]->Add(pParameter[1]);
								continue;
							}
							delete pParameter[1];
						}
					}
					break;
				}
				if (nParameter < nParameters)
				{
					delete pProfile[1];
					break;
				}
				m_pProfiles[1].Add(pProfile[1]);
				continue;
			}
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CMMDTestDialog::IsModified() CONST
{
	return((!GetParentDisplay()->GetImageView()->GetDocument()->Compare(m_pDocument) || !m_pProfiles[0].Compare(&m_pProfiles[1])) ? TRUE : FALSE);
}

void CMMDTestDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDTestDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDTestDialog::PostNcDestroy()
{
	INT  nParameter;
	INT  nParameters;
	CMMDTestParameter  *pParameter;

	Stop();
	for (nParameter = 0, nParameters = (INT)m_pScriptParameters.GetSize(), m_pItems.RemoveAll(), m_pItemsCode.RemoveAll(), m_szItemParameters.RemoveAll(), m_pProfiles[0].RemoveAll(), m_pProfiles[1].RemoveAll(), m_cTMEnvironment.Destroy(); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = (CMMDTestParameter *)m_pScriptParameters.GetAt(nParameter)))
		{
			delete pParameter;
			continue;
		}
	}
	FreeCode();
	delete m_pDocument;
	m_pDocument = (CMMDDocument *)NULL;
	m_pScriptParameters.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDTestDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDTestDialog)
	ON_WM_TIMER()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_TEST_STATUS_NOLIMIT, OnParameterStatusNoLimit)
	ON_BN_CLICKED(IDC_MMD_TEST_STATUS_HARDLIMIT, OnParameterStatusHardLimit)
	ON_BN_CLICKED(IDC_MMD_TEST_STATUS_SOFTLIMIT, OnParameterStatusSoftLimit)
	ON_BN_CLICKED(IDC_MMD_TEST_STATUS_DELTALIMIT, OnParameterStatusDeltaLimit)
	ON_BN_CLICKED(IDC_MMD_TEST_STATUS_CONSISTENCYLIMIT, OnParameterStatusConsistencyLimit)
	ON_BN_CLICKED(IDC_MMD_TEST_QUALITY_INVALIDDATA, OnParameterStatusInvalid)
	ON_BN_CLICKED(IDC_MMD_TEST_QUALITY_BADDATA, OnParameterStatusBadData)
	ON_BN_CLICKED(IDC_MMD_TEST_SETVALUE, OnSetParameterValue)
	ON_BN_CLICKED(IDC_MMD_TEST_RUNVALUE, OnRunParameterValue)
	ON_BN_CLICKED(IDC_MMD_TEST_STOPVALUE, OnStopParameterValue)
	ON_BN_CLICKED(IDC_MMD_TEST_RESETVALUE, OnResetParameterValue)
	ON_BN_CLICKED(IDC_MMD_TEST_PROFILES_ADD, OnAddProfile)
	ON_BN_CLICKED(IDC_MMD_TEST_PROFILES_REMOVE, OnRemoveProfile)
	ON_BN_CLICKED(IDC_MMD_TEST_PROFILES_TEST, OnTestProfile)
	ON_BN_CLICKED(IDC_MMD_TEST_PROFILES_MEMBERS_ADD, OnAddProfileMember)
	ON_BN_CLICKED(IDC_MMD_TEST_PROFILES_MEMBERS_REMOVE, OnRemoveProfileMember)
	ON_BN_CLICKED(IDC_MMD_TEST_SCRIPT_ADDPROFILE, OnAddScriptProfile)
	ON_BN_CLICKED(IDC_MMD_TEST_SCRIPT_ADDPARAMETER, OnAddScriptParameter)
	ON_BN_CLICKED(IDC_MMD_TEST_SCRIPT_REMOVE, OnRemoveScriptCommand)
	ON_BN_CLICKED(IDC_MMD_TEST_SCRIPT_RUN, OnRunScript)
	ON_BN_CLICKED(IDC_MMD_TEST_SCRIPT_STOP, OnStopScript)
	ON_BN_CLICKED(IDC_MMD_TEST_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_MMD_TEST_PARAMETER, OnSelchangeParameter)
	ON_CBN_SELCHANGE(IDC_MMD_TEST_TABLE, OnSelchangeParameterTable)
	ON_CBN_SELCHANGE(IDC_MMD_TEST_VALUE, OnSelchangeParameterValue)
	ON_CBN_SELCHANGE(IDC_MMD_TEST_PROFILES_NAME, OnSelchangeProfileName)
	ON_LBN_SELCHANGE(IDC_MMD_TEST_PROFILES_MEMBERS, OnSelchangeProfileMember)
	ON_LBN_SELCHANGE(IDC_MMD_TEST_SCRIPT_CODE, OnSelchangeScriptCommand)
	ON_CBN_EDITCHANGE(IDC_MMD_TEST_VALUE, OnEditchangeParameterValue)
	ON_CBN_EDITCHANGE(IDC_MMD_TEST_PROFILES_NAME, OnEditchangeProfileName)
	ON_CONTROL(SBXN_CHANGE, IDC_MMD_TEST_SAMPLE, OnSpinchangeParameterSample)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDTestDialog message handlers

BOOL CMMDTestDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(); EnumParameters(); )
	{
		Spinbox_SetRange(GetDlgItem(IDC_MMD_TEST_SAMPLE), MMDTESTDIALOG_MINIMUMSAMPLE, MMDTESTDIALOG_MAXIMUMSAMPLE);
		Spinbox_SetRange(GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY), MMDTESTDIALOG_MINIMUMINTERVAL, MMDTESTDIALOG_MAXIMUMINTERVAL);
		Spinbox_SetPos(GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY), MMDTESTDIALOG_DEFAULTINTERVAL);
		GetDlgItem(IDC_MMD_TEST_DETAILS)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_PARAMETER_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_PARAMETER)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_VALUE)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_SAMPLE_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_SAMPLE)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_STATUS_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_STATUS_NOLIMIT)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_STATUS_HARDLIMIT)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_STATUS_SOFTLIMIT)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_STATUS_DELTALIMIT)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_STATUS_CONSISTENCYLIMIT)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_QUALITY_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_QUALITY_INVALIDDATA)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_QUALITY_BADDATA)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_PROFILES)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_PROFILES_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_SCRIPT)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_SCRIPT_CODE_STATIC)->EnableWindow();
		EnumParameterProfiles();
		ShowParameterDetails();
		break;
	}
	return TRUE;
}

void CMMDTestDialog::OnTimer(UINT_PTR nEventID)
{
	INT  nPos;
	INT  nDelay;
	INT  nProfile;
	INT  nProfiles;
	INT  nParameter;
	INT  nParameters;
	CString  szDelay;
	CString  szProfile;
	CString  szCommand;
	CMMDTestProfile  *pProfile;
	CMMDTestParameter  *pParameter;
	CTMParameter  *pTMParameter;

	if (nEventID == MMDTESTDIALOG_TIMERID)
	{
		for (szCommand = Listbox_GetText(GetDlgItem(IDC_MMD_TEST_SCRIPT_CODE), m_nCommand), szDelay = Listbox_GetText(GetDlgItem(IDC_MMD_TEST_SCRIPT_CODE), m_nCommand + 1), nPos = 0, nDelay = -1; nPos < szDelay.GetLength(); nPos++)
		{
			if (_istdigit(szDelay.GetAt(nPos)))
			{
				nDelay = _ttoi(szDelay.Mid(nPos));
				break;
			}
		}
		if (!szCommand.IsEmpty())
		{
			for (nProfile = 0, nProfiles = (INT)m_pProfiles[0].GetSize(), SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_SETCURSEL, m_nCommand); nProfile < nProfiles; nProfile++)
			{
				szProfile.Format(STRING(IDS_MMDTESTDIALOG_SCRIPT_PROFILE_FORMAT), (LPCTSTR)m_pProfiles[0].GetAt(nProfile)->GetName());
				if (szCommand == szProfile) break;
			}
			if (nProfile < nProfiles)
			{
				if ((pProfile = m_pProfiles[0].GetAt(nProfile)))
				{
					for (nParameter = 0, nParameters = (INT)pProfile->GetSize(); nParameter < nParameters; nParameter++)
					{
						if ((pParameter = (CMMDTestParameter *)pProfile->GetAt(nParameter)) != (CMMDTestParameter *)NULL)
						{
							if ((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(pParameter->GetTag()))))
							{
								pTMParameter->Copy(pParameter);
								continue;
							}
						}
					}
					Test();
				}
			}
			else
			{
				if ((pParameter = (m_nCommand < 2 * m_pScriptParameters.GetSize()) ? (CMMDTestParameter *)m_pScriptParameters.GetAt(m_nCommand / 2) : (CMMDTestParameter *)NULL))
				{
					if ((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(pParameter->GetTag()))))
					{
						pTMParameter->Copy(pParameter);
						Test();
					}
				}
			}
			if (nDelay >= 0)
			{
				SetTimer(MMDTESTDIALOG_TIMERID, nDelay, NULL);
				m_nCommand++;
				m_nCommand++;
			}
			else
			{
				SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_SETTOPINDEX);
				SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_SETCURSEL, (WPARAM)-1);
				GetDlgItem(IDC_MMD_TEST_SCRIPT_STOP)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_MMD_TEST_SCRIPT_STOP)->EnableWindow(FALSE);
				GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->EnableWindow();
				KillTimer(nEventID);
			}
		}
		else
		{
			SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_SETTOPINDEX);
			SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_SETCURSEL, (WPARAM)-1);
			GetDlgItem(IDC_MMD_TEST_SCRIPT_STOP)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_MMD_TEST_SCRIPT_STOP)->EnableWindow(FALSE);
			GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->EnableWindow();
			KillTimer(nEventID);
		}
	}
	if (nEventID == IDC_MMD_TEST_SAMPLE)
	{
		SendDlgItemMessage(IDC_MMD_TEST_VALUE, CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
		GetDlgItem(IDC_MMD_TEST_VALUE)->SetFocus();
		KillTimer(nEventID);
		return;
	}
	CDisplayDialog::OnTimer(nEventID);
}

void CMMDTestDialog::OnParameterStatusNoLimit()
{
	GetDlgItem(IDC_MMD_TEST_SETVALUE)->EnableWindow(CheckParameterValue());
}

void CMMDTestDialog::OnParameterStatusHardLimit()
{
	GetDlgItem(IDC_MMD_TEST_SETVALUE)->EnableWindow(CheckParameterValue());
}

void CMMDTestDialog::OnParameterStatusSoftLimit()
{
	GetDlgItem(IDC_MMD_TEST_SETVALUE)->EnableWindow(CheckParameterValue());
}

void CMMDTestDialog::OnParameterStatusDeltaLimit()
{
	GetDlgItem(IDC_MMD_TEST_SETVALUE)->EnableWindow(CheckParameterValue());
}

void CMMDTestDialog::OnParameterStatusConsistencyLimit()
{
	GetDlgItem(IDC_MMD_TEST_SETVALUE)->EnableWindow(CheckParameterValue());
}

void CMMDTestDialog::OnParameterStatusInvalid()
{
	GetDlgItem(IDC_MMD_TEST_SETVALUE)->EnableWindow(CheckParameterValue());
}

void CMMDTestDialog::OnParameterStatusBadData()
{
	GetDlgItem(IDC_MMD_TEST_SETVALUE)->EnableWindow(CheckParameterValue());
}

void CMMDTestDialog::OnSetParameterValue()
{
	CString  szValue;
	CString  szProfile;
	CTMParameter  *pTMParameter;
	CHourglassCursor  cCursor;

	for (; (pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))); )
	{
		UpdateParameter(pTMParameter);
		break;
	}
	GetDlgItem(IDC_MMD_TEST_VALUE)->SetWindowText(((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))) && pTMParameter->GetValueAsText(GetDatabase(), (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_TEST_SAMPLE)), szValue)) ? szValue : EMPTYSTRING);
	GetDlgItem(IDC_MMD_TEST_SETVALUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_RUNVALUE)->EnableWindow();
	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->GetWindowText(szProfile);
	GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_ADD)->EnableWindow((m_pProfiles[0].Find(szProfile) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_ADDPROFILE)->EnableWindow((m_pProfiles[0].Find(szProfile) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_ADDPARAMETER)->EnableWindow();
	GetDlgItem(IDC_MMD_TEST_RUNVALUE)->SetFocus();
}

void CMMDTestDialog::OnRunParameterValue()
{
	CHourglassCursor  cCursor;

	Test();
	GetDlgItem(IDC_MMD_TEST_RUNVALUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_STOPVALUE)->EnableWindow();
	GetDlgItem(IDC_MMD_TEST_RESETVALUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_STOPVALUE)->SetFocus();
}

void CMMDTestDialog::OnStopParameterValue()
{
	CHourglassCursor  cCursor;

	Stop();
	GetDlgItem(IDC_MMD_TEST_RUNVALUE)->EnableWindow();
	GetDlgItem(IDC_MMD_TEST_STOPVALUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_RESETVALUE)->EnableWindow();
	GetDlgItem(IDC_MMD_TEST_RUNVALUE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDTestDialog::OnResetParameterValue()
{
	CHourglassCursor  cCursor;

	Reset();
	GetDlgItem(IDC_MMD_TEST_RESETVALUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_RUNVALUE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDTestDialog::OnAddProfile()
{
	CString  szProfile;
	CMMDTestProfile  *pProfile;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->GetWindowText(szProfile);
	if (SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfile) >= 0)
	{
		if ((pProfile = new CMMDTestProfile(szProfile)))
		{
			if ((m_pProfiles[0].Add(pProfile)) >= 0)
			{
				SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile));
				GetDlgItem(IDC_MMD_TEST_PROFILES_ADD)->EnableWindow(FALSE);
				GetDlgItem(IDC_MMD_TEST_PROFILES_REMOVE)->EnableWindow();
				GetDlgItem(IDC_MMD_TEST_PROFILES_TEST)->EnableWindow();
				GetDlgItem(IDC_MMD_TEST_SCRIPT_ADDPROFILE)->EnableWindow();
				EnumParameterProfileMembers();
			}
			else
			{
				SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile));
				delete pProfile;
			}
		}
		else  SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile));
	}
	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDTestDialog::OnRemoveProfile()
{
	CString  szProfile;
	CMMDTestProfile  *pProfile;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->GetWindowText(szProfile);
	if (SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile)) >= 0)
	{
		if ((pProfile = m_pProfiles[0].GetAt(m_pProfiles[0].Find(szProfile))))
		{
			m_pProfiles[0].RemoveAt(m_pProfiles[0].Find(szProfile));
			delete pProfile;
		}
		SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_RESETCONTENT);
		GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_REMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_TEST_PROFILES_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_TEST_PROFILES_REMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_TEST_PROFILES_TEST)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_TEST_SCRIPT_ADDPROFILE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_TEST_SCRIPT_REMOVE)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDTestDialog::OnTestProfile()
{
	INT  nParameter;
	INT  nParameters;
	CString  szProfile;
	CMMDTestProfile  *pProfile;
	CMMDTestParameter  *pParameter;
	CTMParameter  *pTMParameter;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->GetWindowText(szProfile);
	if ((pProfile = m_pProfiles[0].GetAt(m_pProfiles[0].Find(szProfile))))
	{
		for (nParameter = 0, nParameters = (INT)pProfile->GetSize(), m_cTMEnvironment.GetTMParameters()->Reset(); nParameter < nParameters; nParameter++)
		{
			if ((pParameter = (CMMDTestParameter *)pProfile->GetAt(nParameter)) != (CMMDTestParameter *)NULL)
			{
				if ((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(pParameter->GetTag()))))
				{
					pTMParameter->Copy(pParameter);
					continue;
				}
			}
		}
		Test();
		GetDlgItem(IDC_MMD_TEST_RUNVALUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_TEST_STOPVALUE)->EnableWindow();
		GetDlgItem(IDC_MMD_TEST_RESETVALUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMD_TEST_STOPVALUE)->SetFocus();
	}
}

void CMMDTestDialog::OnAddProfileMember()
{
	INT  nSample;
	INT  nSamples;
	CString  szValue;
	CString  szMember;
	CString  szProfile;
	CString  szParameter;
	CMMDTestProfile  *pProfile;
	CMMDTestParameter  *pParameter;
	CTMParameter  *pTMParameter;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_TEST_PARAMETER)->GetWindowText(szParameter);
	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->GetWindowText(szProfile);
	if ((pProfile = m_pProfiles[0].GetAt(m_pProfiles[0].Find(szProfile))))
	{
		if ((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))))
		{
			for (nSample = 0, nSamples = pTMParameter->GetValueCount(); nSample < nSamples; nSample++)
			{
				if (pTMParameter->GetValueAsText(GetDatabase(), nSample, szValue)) break;
				continue;
			}
			szMember.Format(STRING(IDS_MMDTESTDIALOG_SCRIPT_PARAMETER_FORMAT), (LPCTSTR)szParameter, (LPCTSTR)szValue);
			if ((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szMember.Left(pTMParameter->GetTag().GetLength() + 1)) < 0 || SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szMember.Left(pTMParameter->GetTag().GetLength() + 1))) >= 0) && SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szMember) >= 0)
			{
				if ((pParameter = (pProfile->Find(pTMParameter->GetTag()) < 0) ? new CMMDTestParameter(pTMParameter->GetTag()) : pProfile->GetAt(pProfile->Find(pTMParameter->GetTag()))))
				{
					if (pParameter->Copy(pTMParameter) && (pProfile->Find(pTMParameter->GetTag()) >= 0 || pProfile->Add(pParameter) >= 0))
					{
						SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szMember));
						GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_STATIC)->EnableWindow();
						GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS)->EnableWindow();
						GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_REMOVE)->EnableWindow();
					}
					else
					{
						SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szMember));
						if (pProfile->Find(pTMParameter->GetTag()) < 0) delete pParameter;
					}
				}
				else  SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szMember));
			}
		}
	}
	GetDlgItem(IDC_MMD_TEST_PARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDTestDialog::OnRemoveProfileMember()
{
	INT  nParameter;
	INT  nParameters;
	CString  szProfile;
	CString  szParameter;
	CMMDTestProfile  *pProfile;
	CMMDTestParameter  *pParameter;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->GetWindowText(szProfile);
	if ((pProfile = m_pProfiles[0].GetAt(m_pProfiles[0].Find(szProfile))))
	{
		for (szParameter = Listbox_GetText(GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS), (INT)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_GETCURSEL)); SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_GETCURSEL)) >= 0; )
		{
			for (nParameter = 0, nParameters = (INT)pProfile->GetSize(); nParameter < nParameters; nParameter = nParameter + 1)
			{
				if ((pParameter = pProfile->GetAt(nParameter)) && !pParameter->GetTag().Compare(szParameter.Left(pParameter->GetTag().GetLength())))
				{
					pProfile->RemoveAt(nParameter);
					delete pParameter;
					break;
				}
			}
			if (nParameter < nParameters)
			{
				GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
				GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_MEMBERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
				GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_REMOVE)->EnableWindow(FALSE);
			}
			break;
		}
	}
	GetDlgItem(IDC_MMD_TEST_PARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDTestDialog::OnAddScriptProfile()
{
	CString  szDelay;
	CString  szProfile;
	CString  szCommand;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->GetWindowText(szProfile);
	szCommand.Format(STRING(IDS_MMDTESTDIALOG_SCRIPT_PROFILE_FORMAT), (LPCTSTR)szProfile);
	szDelay.Format(STRING(IDS_MMDTESTDIALOG_SCRIPT_DELAY_FORMAT), (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY)));
	if (!SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCOUNT) || SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szDelay) >= 0)
	{
		if (SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szCommand) >= 0)
		{
			GetDlgItem(IDC_MMD_TEST_SCRIPT_CODE)->EnableWindow();
			GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY_STATIC)->EnableWindow();
			GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY)->EnableWindow();
			GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY_MILLISECONDS)->EnableWindow();
			GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->EnableWindow();
			GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->SetFocus();
			m_pScriptParameters.Add(NULL);
			return;
		}
		SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCOUNT) - 1);
	}
}

void CMMDTestDialog::OnAddScriptParameter()
{
	INT  nSample;
	INT  nSamples;
	CString  szDelay;
	CString  szValue;
	CString  szCommand;
	CString  szParameter;
	CTMParameter  *pTMParameter;
	CMMDTestParameter  *pParameter;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_TEST_PARAMETER)->GetWindowText(szParameter);
	if ((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))))
	{
		for (nSample = 0, nSamples = pTMParameter->GetValueCount(); nSample < nSamples; nSample++)
		{
			if (pTMParameter->GetValueAsText(GetDatabase(), nSample, szValue)) break;
			continue;
		}
		szCommand.Format(STRING(IDS_MMDTESTDIALOG_SCRIPT_PARAMETER_FORMAT), (LPCTSTR)szParameter, (LPCTSTR)szValue);
		szDelay.Format(STRING(IDS_MMDTESTDIALOG_SCRIPT_DELAY_FORMAT), (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY)));
		if (!SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCOUNT) || SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szDelay) >= 0)
		{
			if (SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szCommand) >= 0)
			{
				if ((pParameter = new CMMDTestParameter) != (CMMDTestParameter *)NULL)
				{
					GetDlgItem(IDC_MMD_TEST_SCRIPT_CODE)->EnableWindow();
					GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY_STATIC)->EnableWindow();
					GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY)->EnableWindow();
					GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY_MILLISECONDS)->EnableWindow();
					GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->EnableWindow();
					GetDlgItem(IDC_MMD_TEST_PARAMETER)->SetFocus();
					pParameter->Copy(pTMParameter);
					m_pScriptParameters.Add(pParameter);
					return;
				}
			}
			SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCOUNT) - 1);
		}
	}
}

void CMMDTestDialog::OnRemoveScriptCommand()
{
	INT  nIndex;
	CMMDTestParameter  *pParameter;
	CHourglassCursor  cCursor;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCURSEL)) < 2 * (INT)m_pScriptParameters.GetSize())
	{
		if ((pParameter = (CMMDTestParameter *)m_pScriptParameters.GetAt(nIndex / 2))) delete pParameter;
		m_pScriptParameters.RemoveAt(nIndex / 2);
	}
	SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_DELETESTRING, max(nIndex - 1, 0));
	SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_DELETESTRING, max(nIndex - 1, 0));
	GetDlgItem(IDC_MMD_TEST_SCRIPT_CODE)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_DELAY_MILLISECONDS)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_PARAMETER)->SetFocus();
}

void CMMDTestDialog::OnRunScript()
{
	CHourglassCursor  cCursor;

	m_nCommand = 0;
	m_cTMEnvironment.GetTMParameters()->Reset();
	SetTimer(MMDTESTDIALOG_TIMERID, MMDTESTDIALOG_TIMEOUT, NULL);
	GetDlgItem(IDC_MMD_TEST_STOPVALUE)->EnableWindow(TRUE);
	GetDlgItem(IDC_MMD_TEST_RESETVALUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_STOP)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_STOP)->EnableWindow();
	GetDlgItem(IDC_MMD_TEST_SCRIPT_STOP)->SetFocus();
}

void CMMDTestDialog::OnStopScript()
{
	CHourglassCursor  cCursor;

	KillTimer(MMDTESTDIALOG_TIMERID);
	SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_SETTOPINDEX);
	SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->EnableWindow();
	GetDlgItem(IDC_MMD_TEST_SCRIPT_STOP)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_RUN)->SetFocus();
}

void CMMDTestDialog::OnSelchangeParameter()
{
	CString  szProfile;
	CTMParameter  *pTMParameter;

	ShowParameterDetails();
	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->GetWindowText(szProfile);
	GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_ADD)->EnableWindow(((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))) && pTMParameter->GetValueCount() > 0) ? ((m_pProfiles[0].Find(szProfile) >= 0) ? TRUE : FALSE) : FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_ADDPARAMETER)->EnableWindow(((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))) && pTMParameter->GetValueCount() > 0) ? TRUE : FALSE);
	SendDlgItemMessage(IDC_MMD_TEST_VALUE, CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
	GetDlgItem(IDC_MMD_TEST_VALUE)->SetFocus();
}

void CMMDTestDialog::OnSelchangeParameterTable()
{
	UINT  nStatus;
	CString  szValue;
	ULONGLONG  nValue;
	CStringArray  szTables[2];
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (EnumParameterTableValues(); (pDatabaseTMParameter = ((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL)))))) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())) : (CDatabaseTMParameter *)NULL) && SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_GETCURSEL) < pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1]) && pTMParameter->GetRawValue((INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_TEST_SAMPLE)), nValue, nStatus); )
	{
		UpdateParameter(pTMParameter, nValue, (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_TEST_SAMPLE)), nStatus, szTables[0].GetAt(SendDlgItemMessage(IDC_MMD_TEST_TABLE, CB_GETCURSEL)));
		break;
	}
	GetDlgItem(IDC_MMD_TEST_VALUE)->SetWindowText(((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))) && pTMParameter->GetValueAsText(GetDatabase(), (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_TEST_SAMPLE)), szValue)) ? szValue : EMPTYSTRING);
	SendDlgItemMessage(IDC_MMD_TEST_VALUE, CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
	GetDlgItem(IDC_MMD_TEST_VALUE)->SetFocus();
}

void CMMDTestDialog::OnSelchangeParameterValue()
{
	GetDlgItem(IDC_MMD_TEST_SETVALUE)->EnableWindow(CheckParameterValue(Combobox_GetText(GetDlgItem(IDC_MMD_TEST_VALUE), (INT)SendDlgItemMessage(IDC_MMD_TEST_VALUE, CB_GETCURSEL))));
}

void CMMDTestDialog::OnSelchangeProfileName()
{
	CString  szProfile;

	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->SetWindowText((szProfile = Combobox_GetText(GetDlgItem(IDC_MMD_TEST_PROFILES_NAME), (INT)SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_GETCURSEL))));
	GetDlgItem(IDC_MMD_TEST_PROFILES_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_TEST_PROFILES_REMOVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_MMD_TEST_PROFILES_TEST)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile) >= 0) ? TRUE : FALSE);
	EnumParameterProfileMembers();
}

void CMMDTestDialog::OnSelchangeProfileMember()
{
	GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_REMOVE)->EnableWindow();
}

void CMMDTestDialog::OnSelchangeScriptCommand()
{
	GetDlgItem(IDC_MMD_TEST_SCRIPT_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_SCRIPT_CODE, LB_GETCURSEL) % 2 == 0) ? TRUE : FALSE);
}

void CMMDTestDialog::OnSpinchangeParameterSample()
{
	CString  szValue;
	CTMParameter  *pTMParameter;

	SetTimer(IDC_MMD_TEST_SAMPLE, 0, NULL);
	GetDlgItem(IDC_MMD_TEST_VALUE)->SetWindowText(((pTMParameter = m_cTMEnvironment.GetTMParameters()->GetAt(m_cTMEnvironment.GetTMParameters()->Find(m_szItemParameters.GetAt(SendDlgItemMessage(IDC_MMD_TEST_PARAMETER, CB_GETCURSEL))))) && pTMParameter->GetValueAsText(GetDatabase(), (INT)Spinbox_GetPos(GetDlgItem(IDC_MMD_TEST_SAMPLE)), szValue)) ? szValue : EMPTYSTRING);
}

void CMMDTestDialog::OnEditchangeParameterValue()
{
	GetDlgItem(IDC_MMD_TEST_SETVALUE)->EnableWindow(CheckParameterValue());
}

void CMMDTestDialog::OnEditchangeProfileName()
{
	CString  szProfile;

	GetDlgItem(IDC_MMD_TEST_PROFILES_NAME)->GetWindowText(szProfile);
	GetDlgItem(IDC_MMD_TEST_PROFILES_ADD)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile) < 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_PROFILES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_PROFILES_MEMBERS_ADD)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_PROFILES_TEST)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_TEST_SCRIPT_ADDPROFILE)->EnableWindow((SendDlgItemMessage(IDC_MMD_TEST_PROFILES_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szProfile) >= 0) ? TRUE : FALSE);
}

void CMMDTestDialog::OnOK()
{
	CHourglassCursor  cCursor;

	SaveProfiles();
	m_cTMEnvironment.Destroy();
	CDisplayDialog::OnOK();
}

void CMMDTestDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	Reset();
	m_cTMEnvironment.Destroy();
	CDisplayDialog::OnCancel();
}

BOOL CMMDTestDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDTESTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDTestDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDTESTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDFindDialog dialog

IMPLEMENT_DYNCREATE(CMMDFindDialog, CDisplayDialog)

CMMDFindDialog::CMMDFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDFindDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMMDFindDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CMMDFindDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CMMDWnd *CMMDFindDialog::GetParent() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParent());
}

void CMMDFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDFindDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMMDFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_FIND_NEXT, OnFindText)
	ON_BN_CLICKED(IDC_MMD_FIND_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_MMD_FIND_TEXT, OnSelchangeText)
	ON_CBN_EDITCHANGE(IDC_MMD_FIND_TEXT, OnEditchangeText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDFindDialog message handlers

BOOL CMMDFindDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	BOOL  bFindDefaults[4];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szSearchItems.GetSize(), GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_MMD_FIND_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szSearchItems.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_MMD_FIND_DIRECTION_DOWN, bFindDefaults[0]);
	CheckDlgButton(IDC_MMD_FIND_DIRECTION_UP, !bFindDefaults[0]);
	CheckDlgButton(IDC_MMD_FIND_ALL, bFindDefaults[1]);
	CheckDlgButton(IDC_MMD_FIND_CASE, bFindDefaults[2]);
	CheckDlgButton(IDC_MMD_FIND_WORD, bFindDefaults[3]);
	GetDlgItem(IDC_MMD_FIND_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_FIND_TEXT)->EnableWindow();
	GetDlgItem(IDC_MMD_FIND_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_MMD_FIND_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_MMD_FIND_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_MMD_FIND_ALL)->EnableWindow();
	GetDlgItem(IDC_MMD_FIND_CASE)->EnableWindow();
	GetDlgItem(IDC_MMD_FIND_WORD)->EnableWindow();
	return TRUE;
}

void CMMDFindDialog::OnFindText()
{
	CString  szText;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_MMD_FIND_TEXT)->GetWindowText(szText); SendDlgItemMessage(IDC_MMD_FIND_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText) == CB_ERR; )
	{
		SendDlgItemMessage(IDC_MMD_FIND_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText);
		m_szSearchItems.Add(szText);
		break;
	}
	if (!GetParent()->SearchMimicsCtrlCode(szText, IsDlgButtonChecked(IDC_MMD_FIND_DIRECTION_DOWN), IsDlgButtonChecked(IDC_MMD_FIND_ALL), IsDlgButtonChecked(IDC_MMD_FIND_CASE), IsDlgButtonChecked(IDC_MMD_FIND_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_MMD_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
		return;
	}
	CheckDlgButton(IDC_MMD_FIND_ALL, FALSE);
}

void CMMDFindDialog::OnSelchangeText()
{
	GetDlgItem(IDC_MMD_FIND_NEXT)->EnableWindow((SendDlgItemMessage(IDC_MMD_FIND_TEXT, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CMMDFindDialog::OnEditchangeText()
{
	GetDlgItem(IDC_MMD_FIND_NEXT)->EnableWindow((GetDlgItem(IDC_MMD_FIND_TEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CMMDFindDialog::OnCancel()
{
	GetParent()->SetFocus();
	CDisplayDialog::OnCancel();
}

BOOL CMMDFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDReplaceDialog dialog

IMPLEMENT_DYNCREATE(CMMDReplaceDialog, CDisplayDialog)

CMMDReplaceDialog::CMMDReplaceDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDReplaceDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMMDReplaceDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CMMDReplaceDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CMMDWnd *CMMDReplaceDialog::GetParent() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParent());
}

void CMMDReplaceDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDReplaceDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMMDReplaceDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDReplaceDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_REPLACE_FINDNEXT, OnFindNextText)
	ON_BN_CLICKED(IDC_MMD_REPLACE_NEXT, OnReplaceText)
	ON_BN_CLICKED(IDC_MMD_REPLACE_ALLNEXT, OnReplaceAllText)
	ON_BN_CLICKED(IDC_MMD_REPLACE_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_MMD_REPLACE_FINDTEXT, OnSelchangeFindText)
	ON_CBN_EDITCHANGE(IDC_MMD_REPLACE_FINDTEXT, OnEditchangeFindText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDReplaceDialog message handlers

BOOL CMMDReplaceDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szItems[0].GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_MMD_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szItems[0].GetAt(nItem));
		continue;
	}
	for (nItem = 0, nItems = (INT)m_szItems[1].GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_MMD_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szItems[1].GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_MMD_REPLACE_ALL, TRUE);
	CheckDlgButton(IDC_MMD_REPLACE_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_MMD_REPLACE_FINDTEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_REPLACE_FINDTEXT)->EnableWindow();
	GetDlgItem(IDC_MMD_REPLACE_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_REPLACE_TEXT)->EnableWindow();
	GetDlgItem(IDC_MMD_REPLACE_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_MMD_REPLACE_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_MMD_REPLACE_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_MMD_REPLACE_ALL)->EnableWindow();
	GetDlgItem(IDC_MMD_REPLACE_CASE)->EnableWindow();
	GetDlgItem(IDC_MMD_REPLACE_WORD)->EnableWindow();
	return TRUE;
}

void CMMDReplaceDialog::OnFindNextText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_MMD_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_MMD_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_MMD_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_MMD_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_MMD_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->SearchMimicsCtrlCode(szText[0], IsDlgButtonChecked(IDC_MMD_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_MMD_REPLACE_ALL), IsDlgButtonChecked(IDC_MMD_REPLACE_CASE), IsDlgButtonChecked(IDC_MMD_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_MMD_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
		return;
	}
	CheckDlgButton(IDC_MMD_REPLACE_ALL, FALSE);
}

void CMMDReplaceDialog::OnReplaceText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_MMD_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_MMD_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_MMD_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_MMD_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_MMD_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->ReplaceMimicsCtrlCode(szText[0], szText[1], IsDlgButtonChecked(IDC_MMD_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_MMD_REPLACE_ALL), IsDlgButtonChecked(IDC_MMD_REPLACE_CASE), IsDlgButtonChecked(IDC_MMD_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_MMD_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
	}
}

void CMMDReplaceDialog::OnReplaceAllText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_MMD_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_MMD_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_MMD_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_MMD_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_MMD_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->ReplaceAllMimicsCtrlCode(szText[0], szText[1], IsDlgButtonChecked(IDC_MMD_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_MMD_REPLACE_ALL), IsDlgButtonChecked(IDC_MMD_REPLACE_CASE), IsDlgButtonChecked(IDC_MMD_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_MMD_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
	}
}

void CMMDReplaceDialog::OnSelchangeFindText()
{
	GetDlgItem(IDC_MMD_REPLACE_FINDNEXT)->EnableWindow((GetDlgItem(IDC_MMD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_REPLACE_NEXT)->EnableWindow((GetDlgItem(IDC_MMD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_REPLACE_ALLNEXT)->EnableWindow((GetDlgItem(IDC_MMD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CMMDReplaceDialog::OnEditchangeFindText()
{
	GetDlgItem(IDC_MMD_REPLACE_FINDNEXT)->EnableWindow((GetDlgItem(IDC_MMD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_REPLACE_NEXT)->EnableWindow((GetDlgItem(IDC_MMD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_REPLACE_ALLNEXT)->EnableWindow((GetDlgItem(IDC_MMD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CMMDReplaceDialog::OnCancel()
{
	GetParent()->SetFocus();
	CDisplayDialog::OnCancel();
}

BOOL CMMDReplaceDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDREPLACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDReplaceDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDREPLACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDGoToDialog dialog

IMPLEMENT_DYNCREATE(CMMDGoToDialog, CDisplayDialog)

CMMDGoToDialog::CMMDGoToDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDGoToDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMMDGoToDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CMMDGoToDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CMMDWnd *CMMDGoToDialog::GetParent() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParent());
}

BOOL CMMDGoToDialog::Check(BOOL bModified) CONST
{
	return(((IsDlgButtonChecked(IDC_MMD_GOTO_LINE) && GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->GetWindowTextLength() > 0) || IsDlgButtonChecked(IDC_MMD_GOTO_JUMPDOWN) || IsDlgButtonChecked(IDC_MMD_GOTO_JUMPUP)) ? TRUE : FALSE);
}

void CMMDGoToDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDGoToDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMMDGoToDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDGoToDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_GOTO_LINE, OnLineNumber)
	ON_BN_CLICKED(IDC_MMD_GOTO_JUMPDOWN, OnJumpLineDown)
	ON_BN_CLICKED(IDC_MMD_GOTO_JUMPUP, OnJumpLineUp)
	ON_BN_CLICKED(IDC_MMD_GOTO_JUMP, OnJump)
	ON_BN_CLICKED(IDC_MMD_GOTO_HELP, OnHelp)
	ON_EN_CHANGE(IDC_MMD_GOTO_LINENUMBER, OnEditchangeLineNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDGoToDialog message handlers

BOOL CMMDGoToDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_MMD_GOTO_LINE, TRUE);
	Spinbox_SetRange(GetDlgItem(IDC_MMD_GOTO_JUMPDOWNLINE), 1, INT_MAX);
	Spinbox_SetRange(GetDlgItem(IDC_MMD_GOTO_JUMPUPLINE), 1, INT_MAX);
	GetDlgItem(IDC_MMD_GOTO_LINE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_GOTO_LINE)->EnableWindow();
	GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->EnableWindow();
	GetDlgItem(IDC_MMD_GOTO_JUMPDOWN)->EnableWindow();
	GetDlgItem(IDC_MMD_GOTO_JUMPUP)->EnableWindow();
	GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->SetFocus();
	return FALSE;
}

void CMMDGoToDialog::OnLineNumber()
{
	CheckDlgButton(IDC_MMD_GOTO_LINE, TRUE);
	CheckDlgButton(IDC_MMD_GOTO_JUMPDOWN, FALSE);
	CheckDlgButton(IDC_MMD_GOTO_JUMPUP, FALSE);
	GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->EnableWindow();
	GetDlgItem(IDC_MMD_GOTO_JUMPDOWN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_JUMPDOWNLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_JUMPUP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_JUMPUPLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_JUMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDGoToDialog::OnJumpLineDown()
{
	CheckDlgButton(IDC_MMD_GOTO_LINE, FALSE);
	CheckDlgButton(IDC_MMD_GOTO_JUMPDOWN, TRUE);
	CheckDlgButton(IDC_MMD_GOTO_JUMPUP, FALSE);
	Spinbox_SetPos(GetDlgItem(IDC_MMD_GOTO_JUMPDOWNLINE), 10);
	GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_JUMPDOWN_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_GOTO_JUMPDOWNLINE)->EnableWindow();
	GetDlgItem(IDC_MMD_GOTO_JUMPUP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_JUMPUPLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_MMD_GOTO_JUMPDOWNLINE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDGoToDialog::OnJumpLineUp()
{
	CheckDlgButton(IDC_MMD_GOTO_LINE, FALSE);
	CheckDlgButton(IDC_MMD_GOTO_JUMPDOWN, FALSE);
	CheckDlgButton(IDC_MMD_GOTO_JUMPUP, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_MMD_GOTO_JUMPUPLINE), 10);
	GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_JUMPDOWN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_JUMPDOWNLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_GOTO_JUMPUP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_GOTO_JUMPUPLINE)->EnableWindow();
	GetDlgItem(IDC_MMD_GOTO_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_MMD_GOTO_JUMPUPLINE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDGoToDialog::OnJump()
{
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_MMD_GOTO_LINE)) ShowMessage((!GetParent()->GoToMimicsCtrlCode(GetDlgItemInt(IDC_MMD_GOTO_LINENUMBER, (LPBOOL)NULL, FALSE), FALSE, FALSE)) ? USER_INFORMATIONAL_MMD_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_MMD_GOTO_JUMPDOWN)) ShowMessage((!GetParent()->GoToMimicsCtrlCode((UINT)Spinbox_GetPos(GetDlgItem(IDC_MMD_GOTO_JUMPDOWNLINE)), TRUE, FALSE)) ? USER_INFORMATIONAL_MMD_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_MMD_GOTO_JUMPUP)) ShowMessage((!GetParent()->GoToMimicsCtrlCode((UINT)Spinbox_GetPos(GetDlgItem(IDC_MMD_GOTO_JUMPUPLINE)), FALSE, TRUE)) ? USER_INFORMATIONAL_MMD_GOTO_LINE_FAILURE : USER_NOERROR);
}

void CMMDGoToDialog::OnEditchangeLineNumber()
{
	GetDlgItem(IDC_MMD_GOTO_JUMP)->EnableWindow((GetDlgItem(IDC_MMD_GOTO_LINENUMBER)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDGoToDialog::OnOK()
{
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_MMD_GOTO_LINE)) ShowMessage((!GetParent()->GoToMimicsCtrlCode(GetDlgItemInt(IDC_MMD_GOTO_LINENUMBER, (LPBOOL)NULL, FALSE), FALSE, FALSE)) ? USER_INFORMATIONAL_MMD_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_MMD_GOTO_JUMPDOWN)) ShowMessage((!GetParent()->GoToMimicsCtrlCode((UINT)Spinbox_GetPos(GetDlgItem(IDC_MMD_GOTO_JUMPDOWNLINE)), TRUE, FALSE)) ? USER_INFORMATIONAL_MMD_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_MMD_GOTO_JUMPUP)) ShowMessage((!GetParent()->GoToMimicsCtrlCode((UINT)Spinbox_GetPos(GetDlgItem(IDC_MMD_GOTO_JUMPUPLINE)), FALSE, TRUE)) ? USER_INFORMATIONAL_MMD_GOTO_LINE_FAILURE : USER_NOERROR);
	GetParent()->SetFocus();
	CDisplayDialog::OnOK();
}

BOOL CMMDGoToDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGOTODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDGoToDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_MMDGOTODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDStatusBar

IMPLEMENT_DYNCREATE(CMMDStatusBar, CMFCStatusBar)

BOOL CMMDStatusBar::SetIndicators(CONST UINT *pIDs, INT nCount)
{
	INT  nIndex;
	CString  szText;
	CBitmap  cBitmap;

	for (Initialize(); CMFCStatusBar::SetIndicators(pIDs, nCount); )
	{
		if ((nIndex = CommandToIndex(ID_MMD_STATUSBAR_OBJECTPANE)) >= 0)
		{
			szText.Format(STRING(IDS_MMD_STATUSBAR_OBJECTS), (UINT)-1);
			SetPaneInfo(nIndex, ID_MMD_STATUSBAR_OBJECTPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(nIndex, szText));
		}
		if ((nIndex = CommandToIndex(ID_MMD_STATUSBAR_POSITIONPANE)) >= 0)
		{
			for (szText.Format(STRING(IDS_MMD_STATUSBAR_OBJECTPOSITION), -GetSystemMetrics(SM_CXVIRTUALSCREEN), -GetSystemMetrics(SM_CYVIRTUALSCREEN)), SetPaneInfo(nIndex, ID_MMD_STATUSBAR_POSITIONPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText)), SetTipText(nIndex, STRING(IDS_MMD_STATUSBAR_POSITIONPANE)); cBitmap.LoadBitmap(IDB_MIMICSITEMPOSITIONSYMBOL); )
			{
				SetPaneIcon(nIndex, (HBITMAP)cBitmap.GetSafeHandle(), VGA_COLOR_WHITE);
				cBitmap.DeleteObject();
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_MMD_STATUSBAR_SIZEPANE)) >= 0)
		{
			for (szText.Format(STRING(IDS_MMD_STATUSBAR_OBJECTSIZE), GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN)), SetPaneInfo(nIndex, ID_MMD_STATUSBAR_SIZEPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText)), SetTipText(nIndex, STRING(IDS_MMD_STATUSBAR_SIZEPANE)); cBitmap.LoadBitmap(IDB_MIMICSITEMSIZESYMBOL); )
			{
				SetPaneIcon(nIndex, (HBITMAP)cBitmap.GetSafeHandle(), VGA_COLOR_WHITE);
				cBitmap.DeleteObject();
				break;
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDStatusBar::SetPaneText(UINT nID, LPCTSTR pszText)
{
	INT  nIndex;
	INT  nWidth;
	UINT  nStyle;
	CRect  rPane;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		if (GetPaneText(nIndex).Compare(pszText))
		{
			for (GetItemRect(nIndex, rPane); rPane.Width() != CalcPaneWidth(nIndex, pszText); )
			{
				GetPaneInfo(nIndex, nID, nStyle, nWidth);
				SetPaneInfo(nIndex, nID, nStyle, CalcPaneWidth(nIndex, pszText));
				break;
			}
			return CMFCStatusBar::SetPaneText(nIndex, pszText);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDStatusBar::GetPaneText(UINT nID, CString &szText) CONST
{
	INT  nIndex;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		szText = CMFCStatusBar::GetPaneText(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString CMMDStatusBar::GetPaneText(UINT nID) CONST
{
	CString  szText;

	return((GetPaneText(nID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

INT CMMDStatusBar::CalcPaneWidth(INT nIndex) CONST
{
	return CalcPaneWidth(nIndex, CMFCStatusBar::GetPaneText(nIndex));
}
INT CMMDStatusBar::CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST
{
	INT  nWidth;
	CFont  *pOldFont;
	BITMAP  sBitmap;
	CBitmap  cBitmap;
	CClientDC  cDC(NULL);

	if ((pOldFont = cDC.SelectObject(GetFont())))
	{
		for (nWidth = cDC.GetTextExtent(SPACE + CString(pszText) + SPACE).cx; nIndex == CommandToIndex(ID_MMD_STATUSBAR_POSITIONPANE) || nIndex == CommandToIndex(ID_MMD_STATUSBAR_SIZEPANE); )
		{
			if (cBitmap.LoadBitmap((nIndex == CommandToIndex(ID_MMD_STATUSBAR_POSITIONPANE)) ? IDB_MIMICSITEMPOSITIONSYMBOL : IDB_MIMICSITEMSIZESYMBOL) && cBitmap.GetBitmap(&sBitmap))
			{
				nWidth += sBitmap.bmWidth + cDC.GetTextExtent(SPACE).cx;
				cBitmap.DeleteObject();
			}
			break;
		}
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

VOID CMMDStatusBar::Initialize()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = GetCount(); nIndex < nCount; nIndex++)
	{
		SetTipText(nIndex, (LPCTSTR)NULL);
		continue;
	}
}

BEGIN_MESSAGE_MAP(CMMDStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CMMDStatusBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDStatusBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CMMDImageView

IMPLEMENT_DYNCREATE(CMMDImageView, CScrollView)

CMMDImageView::CMMDImageView() : CScrollView()
{
	m_nItemID = -1;
	m_nImage[0] = 0;
	m_nImage[1] = 0;
	m_nImage[2] = 0;
	m_nImage[3] = 0;
	m_sizeGrid.cx = 0;
	m_sizeGrid.cy = 0;
	m_sizeImage.cx = 0;
	m_sizeImage.cy = 0;
	m_bUseGrid = FALSE;
	m_bModified = FALSE;
	m_nItemDragCode = 0;
	m_nRulerDragCode = 0;
	m_nClipboardFormat = 0;
	m_bSelectionCode[0] = FALSE;
	m_bSelectionCode[1] = FALSE;
	m_ptItemDragPosition.x = 0;
	m_ptItemDragPosition.y = 0;
	m_ptRulerDragPosition.x = 0;
	m_ptRulerDragPosition.y = 0;
	m_sizeItemSelectionArea.cx = 0;
	m_sizeItemSelectionArea.cy = 0;
	m_ptItemSelectionPosition.x = 0;
	m_ptItemSelectionPosition.y = 0;
	m_rItemSelectionArea.SetRectEmpty();
	m_rItemToggledArea.SetRectEmpty();
	m_rItemZoomHotSpot.SetRectEmpty();
	m_nImageGrid = VGA_COLOR_LTGRAY;
	m_nImageBkgnd = GetSysColor(COLOR_WINDOW);
	m_pIUnknown = (IUnknown *)NULL;
	m_pIClassFactory = (IClassFactory *)NULL;
	m_pIEnumMimicsCtrls = (IEnumMimicsCtrls *)NULL;
	m_pDocument[0] = (CMMDDocument *)NULL;
	m_pDocument[1] = (CMMDDocument *)NULL;
	m_hDefaultCursor = (HCURSOR)NULL;
	m_hPointCursor = (HCURSOR)NULL;
	m_hMoveCursor = (HCURSOR)NULL;
	m_hSelectCursor = (HCURSOR)NULL;
	m_hWESizeCursor = (HCURSOR)NULL;
	m_hNSSizeCursor = (HCURSOR)NULL;
	m_hWENSSizeCursor = (HCURSOR)NULL;
	m_hSWNESizeCursor = (HCURSOR)NULL;
	m_hNWSESizeCursor = (HCURSOR)NULL;
	m_hHorzSizeCursor = (HCURSOR)NULL;
	m_hVertSizeCursor = (HCURSOR)NULL;
	m_hRotateCursor = (HCURSOR)NULL;
}

VOID CMMDImageView::SetImage(LPCTSTR pszTitle)
{
	m_cLayout.SetTitle(pszTitle);
}
BOOL CMMDImageView::SetImage(CONST CMMDLayout &cLayout)
{
	INT  nItem;
	INT  nItems;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDLayoutItem  *pLayoutItem[2];
	CMMDDocument  *pDocument;

	if (!m_cLayout.Compare(&cLayout))
	{
		for (nItem = 0, nItems = (m_cLayout.GetName() == cLayout.GetName() && m_cLayout.GetSize() == cLayout.GetSize()) ? (INT)m_cLayout.GetSize() : -1, m_cUndoList.Reset(); nItem < nItems; nItem++)
		{
			if ((pLayoutItem[0] = m_cLayout.GetAt(nItem)))
			{
				if ((pLayoutItem[1] = cLayout.GetAt(nItem)))
				{
					if (!pLayoutItem[0]->Compare(pLayoutItem[1])) break;
					continue;
				}
			}
		}
		if (nItem == nItems)
		{
			cLayout.GetImage(m_sizeImage, m_nImage[0], m_nImage[1], m_nImage[2], m_nImage[3], m_nImageBkgnd, m_sizeGrid, m_nImageGrid, m_bUseGrid);
			SetImage(m_sizeImage, m_nImage[0], m_nImage[1], m_nImage[2], m_nImage[3], m_nImageBkgnd, m_sizeGrid, m_nImageGrid, m_bUseGrid);
			UpdateUndoList(TRUE);
			UpdateAllItems();
			return TRUE;
		}
		if ((pDocument = new CMMDDocument))
		{
			for (lPosition = (m_cLayout.Copy(&cLayout)) ? ((pDocument->Unmap(cLayout, GetImageOrigin())) ? pDocument->m_docItemList.GetHeadPosition() : (POSITION)NULL) : (POSITION)NULL, m_cLayout.GetImage(m_sizeImage, m_nImage[0], m_nImage[1], m_nImage[2], m_nImage[3], m_nImageBkgnd, m_sizeGrid, m_nImageGrid, m_bUseGrid), SetActivatedItem(), m_pDocument[0]->DeleteContents(), m_pDocument[1]->DeleteContents(); lPosition; )
			{
				if ((pItem = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition)) && CMimicsItem::Create(pItem, this, m_pDocument[0])) continue;
				lPosition = (POSITION)-1;
				break;
			}
			if (!lPosition)
			{
				if (m_pDocument[1]->Copy(m_pDocument[0]))
				{
					UpdateUndoList(TRUE);
					UpdateAllItems();
					delete pDocument;
					return TRUE;
				}
			}
			delete pDocument;
		}
		UpdateUndoList(TRUE);
		UpdateAllItems();
		return FALSE;
	}
	return TRUE;
}
VOID CMMDImageView::SetImage(CONST SIZE &sizeImage, INT nMarginLeft, INT nMarginTop, INT nMarginRight, INT nMarginBottom, COLORREF nImageBkgnd, CONST SIZE &sizeGrid, COLORREF nImageGrid, BOOL bUseGrid)
{
	m_sizeImage = sizeImage;
	m_nImage[0] = nMarginLeft;
	m_nImage[1] = nMarginTop;
	m_nImage[2] = nMarginRight;
	m_nImage[3] = nMarginBottom;
	m_nImageBkgnd = nImageBkgnd;
	m_nImageGrid = nImageGrid;
	m_sizeGrid = sizeGrid;
	m_bUseGrid = bUseGrid;
}

CString CMMDImageView::GetImage() CONST
{
	return m_cLayout.GetTitle();
}
BOOL CMMDImageView::GetImage(CMMDLayout &cLayout) CONST
{
	cLayout.SetImage(m_sizeImage, m_nImage[0], m_nImage[1], m_nImage[2], m_nImage[3], m_nImageBkgnd, m_sizeGrid, m_nImageGrid, m_bUseGrid);
	return m_pDocument[0]->Map(cLayout, GetImageOrigin());
}
VOID CMMDImageView::GetImage(SIZE &sizeImage, INT &nMarginLeft, INT &nMarginTop, INT &nMarginRight, INT &nMarginBottom, COLORREF &nImageBkgnd, SIZE &sizeGrid, COLORREF &nImageGrid, BOOL &bUseGrid) CONST
{
	sizeImage = m_sizeImage;
	nMarginLeft = m_nImage[0];
	nMarginTop = m_nImage[1];
	nMarginRight = m_nImage[2];
	nMarginBottom = m_nImage[3];
	nImageBkgnd = m_nImageBkgnd;
	nImageGrid = m_nImageGrid;
	sizeGrid = m_sizeGrid;
	bUseGrid = m_bUseGrid;
}

VOID CMMDImageView::SetImageSize(CONST SIZE &size)
{
	m_sizeImage = size;
}

CSize CMMDImageView::GetImageSize() CONST
{
	return((!m_sizeImage.cx  &&  !m_sizeImage.cy) ? CSize(max(GetTotalSize().cx - CalcVerticalRulerPosition().Width(), 0), max(GetTotalSize().cy - CalcHorizontalRulerPosition().Height(), 0)) : m_sizeImage);
}

VOID CMMDImageView::SetImageMargin(INT nLeft, INT nTop, INT nRight, INT nBottom)
{
	m_nImage[0] = nLeft;
	m_nImage[1] = nTop;
	m_nImage[2] = nRight;
	m_nImage[3] = nBottom;
}

VOID CMMDImageView::GetImageMargin(INT &nLeft, INT &nTop, INT &nRight, INT &nBottom) CONST
{
	nLeft = m_nImage[0];
	nTop = m_nImage[1];
	nRight = m_nImage[2];
	nBottom = m_nImage[3];
}

CPoint CMMDImageView::GetImageOrigin() CONST
{
	return CPoint(CalcVerticalRulerPosition().Width(), CalcHorizontalRulerPosition().Height());
}

VOID CMMDImageView::DrawImage(CONST RECT &rect)
{
	CDC  *pDC;

	if ((pDC = GetDC()))
	{
		pDC->SetWindowOrg(GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
		DrawImage(pDC, rect);
		ReleaseDC(pDC);
	}
	UpdateZoomWindow();
}

VOID CMMDImageView::SetSelectedItemID(UINT nItemID)
{
	m_nItemID = nItemID;
}

UINT CMMDImageView::GetSelectedItemID() CONST
{
	return m_nItemID;
}

CMimicsItem *CMMDImageView::AddItem(UINT nItemID, CONST POINT &point, BOOL bActivate)
{
	CLSID  clsidMimicsItem;
	CMimicsItem  *pMimicsItem;

	if ((pMimicsItem = (m_pIEnumMimicsCtrls->TranslateMimicsCtrlIDToCLSID(nItemID - IDM_FIRSTMIMICSOBJECT, &clsidMimicsItem)) ? CMimicsItem::Create(clsidMimicsItem, this, GetDocument(), point) : (CMimicsItem *)NULL))
	{
		for (SetSelectedItemID(); bActivate; )
		{
			SetActivatedItem(pMimicsItem);
			break;
		}
	}
	return pMimicsItem;
}
CMimicsItem *CMMDImageView::AddItem(CMimicsItem *pItem, BOOL bActivate)
{
	CMimicsItem  *pMimicsItem;

	if ((pMimicsItem = CMimicsItem::Create(pItem, this, GetDocument())))
	{
		for (SetSelectedItemID(); bActivate; )
		{
			SetActivatedItem(pMimicsItem);
			break;
		}
	}
	return pMimicsItem;
}

CMimicsItem *CMMDImageView::FindItem(LPCTSTR pszName) CONST
{
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
		{
			if (pItem->GetItemName() == pszName) return pItem;
			continue;
		}
	}
	return((CMimicsItem *)NULL);
}

VOID CMMDImageView::DeleteItem(CMimicsItem *pItem)
{
	CMimicsGroup  *pGroup;
	CMMDDocument  *pDocument;

	if ((pGroup = (CMimicsGroup *)pItem->GetItemContainer()))
	{
		for (pGroup->RemoveItem(pItem); (pDocument = GetDocument()); )
		{
			pDocument->AddItem(pItem);
			break;
		}
	}
	pItem->Delete();
}

BOOL CMMDImageView::SetActivatedItem(CMimicsItem *pItem)
{
	CRect  rItem;
	CRect  rView;
	POSITION  lPosition;
	CMimicsItem  *pMimicsItem;
	CMMDDocument  *pDocument;

	if (pItem)
	{
		for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, StopSelectingItems(); lPosition; )
		{
			if ((pMimicsItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
			{
				pMimicsItem->ActivateItem(pMimicsItem == pItem);
				continue;
			}
		}
		for (GetClientRect(rView), rItem = pItem->GetItemPosition(), rView.OffsetRect(GetScrollPos(SB_HORZ), 0), rView.OffsetRect(0, GetScrollPos(SB_VERT)), rView.DeflateRect(GetImageOrigin().x, GetImageOrigin().y, 0, 0); rView.left > rItem.left; )
		{
			SetScrollPos(SB_HORZ, GetScrollPos(SB_HORZ) + rItem.left - rView.left);
			break;
		}
		for (; rView.right < rItem.right; )
		{
			SetScrollPos(SB_HORZ, GetScrollPos(SB_HORZ) + rItem.right - rView.right);
			break;
		}
		for (; rView.top > rItem.top; )
		{
			SetScrollPos(SB_VERT, GetScrollPos(SB_VERT) + rItem.top - rView.top);
			break;
		}
		for (; rView.bottom < rItem.bottom; )
		{
			SetScrollPos(SB_VERT, GetScrollPos(SB_VERT) + rItem.bottom - rView.bottom);
			break;
		}
		pItem->ActivateItem(OLEIVERB_SHOW, this);
		UpdateAllItems();
		return TRUE;
	}
	if ((pMimicsItem = GetActivatedItem()))
	{
		for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, StopSelectingItems(), SetItemRotateMode(FALSE); lPosition; )
		{
			if ((pMimicsItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
			{
				pMimicsItem->ActivateItem(FALSE);
				pMimicsItem->SelectItem(FALSE);
			}
		}
		UpdateAllItems();
		return TRUE;
	}
	return FALSE;
}

CMimicsItem *CMMDImageView::GetActivatedItem() CONST
{
	POSITION  lPosition;
	CMimicsItem  *pMimicsItem;
	CMMDDocument  *pDocument;

	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pMimicsItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)) && pMimicsItem->IsItemActivated(TRUE)) return pMimicsItem;
		continue;
	}
	return((CMimicsItem *)NULL);
}

BOOL CMMDImageView::HasActivatedItem() CONST
{
	return((GetActivatedItem()) ? TRUE : FALSE);
}

BOOL CMMDImageView::SelectItem(CMimicsItem *pItem)
{
	CRect  rItem;
	POSITION  lPosition;
	CMimicsItem  *pMimicsItem;
	CMMDDocument  *pDocument;

	if (pItem)
	{
		if ((pMimicsItem = GetActivatedItem()) && !pMimicsItem->GetItemContainer() && !pMimicsItem->GetItemRotateMode() && pMimicsItem != pItem)
		{
			if (pItem->SelectItem(!pItem->IsItemSelected()))
			{
				rItem = pItem->CalcItemFramePosition();
				rItem.OffsetRect(-GetScrollPos(SB_HORZ), 0);
				rItem.OffsetRect(0, -GetScrollPos(SB_VERT));
				InvalidateRect(rItem, FALSE);
				UpdateWindow();
				return TRUE;
			}
		}
		return FALSE;
	}
	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pMimicsItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
		{
			pMimicsItem->SelectItem(FALSE);
			continue;
		}
	}
	return FALSE;
}

BOOL CMMDImageView::HasSelectedItems() CONST
{
	POSITION  lPosition;
	CMimicsItem  *pMimicsItem;
	CMMDDocument  *pDocument;

	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pMimicsItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)) && pMimicsItem->IsItemSelected()) return TRUE;
		continue;
	}
	return FALSE;
}

VOID CMMDImageView::DoUndo()
{
	POSITION  lPosition;
	CMimicsItem  *pItem[2];

	for (m_cUndoList.Lock(), lPosition = (m_cUndoList.Undo(m_pDocument[0])) ? m_pDocument[0]->GetStartPosition() : (POSITION)NULL, pItem[1] = (CMimicsItem *)NULL; lPosition; )
	{
		if ((pItem[0] = (CMimicsItem *)m_pDocument[0]->GetNextItem(lPosition)) && !pItem[0]->GetOleObject())
		{
			if (pItem[0]->CreateNewItem(pItem[0]->GetItemClassID(), this))
			{
				pItem[1] = (pItem[0]->IsItemActivated()) ? pItem[0] : pItem[1];
				pItem[0]->UpdateProperties();
			}
			continue;
		}
		pItem[1] = (pItem[0] && pItem[0]->IsItemActivated()) ? pItem[0] : pItem[1];
	}
	SetActivatedItem(pItem[1]);
	StopSelectingItems();
	m_cUndoList.Unlock();
	UpdateAllItems();
}

BOOL CMMDImageView::CanUndo() CONST
{
	return m_cUndoList.CanUndo();
}

VOID CMMDImageView::DoRedo()
{
	POSITION  lPosition;
	CMimicsItem  *pItem[2];

	for (m_cUndoList.Lock(), lPosition = (m_cUndoList.Redo(m_pDocument[0])) ? m_pDocument[0]->GetStartPosition() : (POSITION)NULL, pItem[1] = (CMimicsItem *)NULL; lPosition; )
	{
		if ((pItem[0] = (CMimicsItem *)m_pDocument[0]->GetNextItem(lPosition)) && !pItem[0]->GetOleObject())
		{
			if (pItem[0]->CreateNewItem(pItem[0]->GetItemClassID(), this))
			{
				pItem[1] = (pItem[0]->IsItemActivated()) ? pItem[0] : pItem[1];
				pItem[0]->UpdateProperties();
			}
			continue;
		}
		pItem[1] = (pItem[0] && pItem[0]->IsItemActivated()) ? pItem[0] : pItem[1];
	}
	SetActivatedItem(pItem[1]);
	StopSelectingItems();
	m_cUndoList.Unlock();
	UpdateAllItems();
}

BOOL CMMDImageView::CanRedo() CONST
{
	return m_cUndoList.CanRedo();
}

VOID CMMDImageView::DoCutItem()
{
	INT  nItem;
	INT  nItems;
	CMimicsItem  *pItem[2];
	CMimicsGroup  *pGroup;

	if ((pItem[0] = GetActivatedItem()) && CopyToClipboard(pItem[0]))
	{
		SetActivatedItem();
		DeleteItem(pItem[0]);
		UpdateUndoList();
		UpdateAllItems();
		return;
	}
	if ((pGroup = new CMimicsGroup))
	{
		for (nItem = 0, nItems = (INT)m_pSelectedItems.GetSize(), pGroup->SetItemType(EMPTYSTRING); nItem < nItems; nItem++)
		{
			if ((pItem[0] = (CMimicsItem *)m_pSelectedItems.GetAt(nItem)))
			{
				if ((pItem[1] = CMimicsItem::AllocateFromItem(pItem[0])))
				{
					if (pItem[1]->Copy(pItem[0]))
					{
						pGroup->AddItem(pItem[1]);
						continue;
					}
					delete pItem[1];
				}
			}
			break;
		}
		if (nItem == nItems)
		{
			if (CopyToClipboard(pGroup))
			{
				for (nItem = 0, nItems = (INT)m_pSelectedItems.GetSize(); nItem < nItems; nItem++)
				{
					if ((pItem[0] = (CMimicsItem *)m_pSelectedItems.GetAt(nItem)))
					{
						DeleteItem(pItem[0]);
						continue;
					}
				}
				StopSelectingItems();
				UpdateUndoList();
				UpdateAllItems();
			}
		}
		delete pGroup;
	}
}

BOOL CMMDImageView::CanCutItem() CONST
{
	return((HasActivatedItem() || GetSelectedItemsAreaCount() > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoCopyItem()
{
	INT  nItem;
	INT  nItems;
	CMimicsItem  *pItem[2];
	CMimicsGroup  *pGroup;

	if ((pItem[0] = GetActivatedItem()))
	{
		CopyToClipboard(pItem[0]);
		return;
	}
	if ((pGroup = new CMimicsGroup))
	{
		for (nItem = 0, nItems = (INT)m_pSelectedItems.GetSize(), pGroup->SetItemType(EMPTYSTRING); nItem < nItems; nItem++)
		{
			if ((pItem[0] = (CMimicsItem *)m_pSelectedItems.GetAt(nItem)))
			{
				if ((pItem[1] = CMimicsItem::AllocateFromItem(pItem[0])))
				{
					if (pItem[1]->Copy(pItem[0]))
					{
						pGroup->AddItem(pItem[1]);
						continue;
					}
					delete pItem[1];
				}
			}
			break;
		}
		for (; nItem == nItems; )
		{
			CopyToClipboard(pGroup);
			break;
		}
		delete pGroup;
	}
}

BOOL CMMDImageView::CanCopyItem() CONST
{
	return((HasActivatedItem() || GetSelectedItemsAreaCount() > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoPasteItem()
{
	CRect  rArea;
	CRect  rItem;
	POSITION  lPosition;
	CMimicsItem  *pItem[3];
	CMimicsGroup  *pGroup;
	COleDataObject  cOleDataObject;

	if (cOleDataObject.AttachClipboard() && cOleDataObject.IsDataAvailable(m_nClipboardFormat))
	{
		if ((pItem[0] = PasteFromClipboard()) != (CMimicsItem *)NULL)
		{
			if (pItem[0]->IsKindOf(RUNTIME_CLASS(CMimicsGroup)))
			{
				if (!lstrlen((pGroup = (CMimicsGroup *)pItem[0])->GetItemType()))
				{
					for (lPosition = pGroup->GetItemList()->GetStartPosition(), rArea.SetRectEmpty(); lPosition; )
					{
						if ((pItem[1] = (CMimicsItem *)pGroup->GetItemList()->GetNextItem(lPosition)))
						{
							rItem = pItem[1]->DoTransformation(pItem[1]->GetItemPosition());
							rItem.InflateRect(1, 1);
							if (rArea.IsRectEmpty())
							{
								rArea = rItem;
								continue;
							}
							rArea.left = min(rItem.left, rArea.left);
							rArea.top = min(rItem.top, rArea.top);
							rArea.right = max(rItem.right, rArea.right);
							rArea.bottom = max(rItem.bottom, rArea.bottom);
						}
					}
					for (lPosition = pGroup->GetItemList()->GetStartPosition(), m_pSelectedItems.RemoveAll(); lPosition; )
					{
						if ((pItem[1] = (CMimicsItem *)pGroup->GetItemList()->GetNextItem(lPosition)))
						{
							rItem = pItem[1]->GetItemPosition();
							rItem.OffsetRect(-rArea.left + 1, 0);
							rItem.OffsetRect(0, -rArea.top + 1);
							rItem.OffsetRect(GetImageOrigin());
							rItem.OffsetRect(GetScrollPos(SB_HORZ), 0);
							rItem.OffsetRect(0, GetScrollPos(SB_VERT));
							pItem[1]->AdjustItemPosition(rItem);
							if ((pItem[2] = AddItem(pItem[1])))
							{
								m_pSelectedItems.Add(pItem[2]);
								continue;
							}
						}
					}
					rArea.OffsetRect(-rArea.left + 1, 0);
					rArea.OffsetRect(0, -rArea.top + 1);
					rArea.OffsetRect(GetImageOrigin());
					rArea.OffsetRect(GetScrollPos(SB_HORZ), 0);
					rArea.OffsetRect(0, GetScrollPos(SB_VERT));
					m_rItemSelectionArea = rArea;
					m_ptItemSelectionPosition.x = 0;
					m_ptItemSelectionPosition.y = 0;
					m_sizeItemSelectionArea.cx = 0;
					m_sizeItemSelectionArea.cy = 0;
					UpdateUndoList();
					UpdateAllItems();
					delete pItem[0];
					return;
				}
			}
			if ((pItem[1] = AddItem(pItem[0], TRUE)))
			{
				UpdateUndoList();
				UpdateAllItems();
			}
		}
		delete pItem[0];
	}
}

BOOL CMMDImageView::CanPasteItem() CONST
{
	COleDataObject  cOleDataObject;

	return((cOleDataObject.AttachClipboard() && cOleDataObject.IsDataAvailable(m_nClipboardFormat)) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoDeleteItem()
{
	INT  nItem;
	INT  nItems;
	CMimicsItem  *pItem;

	if ((pItem = GetActivatedItem()))
	{
		SetActivatedItem();
		DeleteItem(pItem);
		UpdateUndoList();
		UpdateAllItems();
		return;
	}
	for (nItem = 0, nItems = (INT)m_pSelectedItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = (CMimicsItem *)m_pSelectedItems.GetAt(nItem)))
		{
			DeleteItem(pItem);
			continue;
		}
	}
	StopSelectingItems();
	UpdateUndoList();
	UpdateAllItems();
}

BOOL CMMDImageView::CanDeleteItem() CONST
{
	return((HasActivatedItem() || GetSelectedItemsAreaCount() > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoSelectAllItems()
{
	CRect  rArea;
	CRect  rItem;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, m_pSelectedItems.RemoveAll(), rArea.SetRectEmpty(), SetActivatedItem(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
		{
			rItem = pItem->DoTransformation(pItem->GetItemPosition());
			rItem.InflateRect(1, 1);
			if (rArea.IsRectEmpty())
			{
				m_pSelectedItems.Add(pItem);
				rArea = rItem;
				continue;
			}
			rArea.left = min(rItem.left, rArea.left);
			rArea.top = min(rItem.top, rArea.top);
			rArea.right = max(rItem.right, rArea.right);
			rArea.bottom = max(rItem.bottom, rArea.bottom);
			m_pSelectedItems.Add(pItem);
		}
	}
	m_rItemSelectionArea = rArea;
	UpdateAllItems();
}

VOID CMMDImageView::UnSelectAllItems()
{
	SetActivatedItem();
	StopSelectingItems();
}

BOOL CMMDImageView::CanSelectAllItems() CONST
{
	CRect  rArea;
	CRect  rItem;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, rArea.SetRectEmpty(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
		{
			rItem = pItem->DoTransformation(pItem->GetItemPosition());
			rItem.InflateRect(1, 1);
			if (rArea.IsRectEmpty())
			{
				rArea = rItem;
				continue;
			}
			rArea.left = min(rItem.left, rArea.left);
			rArea.top = min(rItem.top, rArea.top);
			rArea.right = max(rItem.right, rArea.right);
			rArea.bottom = max(rItem.bottom, rArea.bottom);
		}
	}
	return((GetItemCount() > 0 && (!HasSelectedItemsArea() || !GetSelectedItemsArea().EqualRect(rArea))) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::CollectMimicsGroup()
{
	INT  nItem;
	INT  nItems;
	CPtrArray  pItems;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMimicsGroup  *pGroup[2];
	CMMDDocument  *pDocument;

	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)) && ((pItem->IsItemActivated(TRUE) && !pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup))) || pItem->IsItemSelected()))
		{
			pItems.Add(pItem);
			continue;
		}
	}
	if ((pItem = (CMimicsItem *)GetActivatedItem()))
	{
		if (!pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)))
		{
			if ((pGroup[0] = new CMimicsGroup) != (CMimicsGroup *)NULL)
			{
				if ((pGroup[1] = (CMimicsGroup *)CMimicsItem::Create(pGroup[0], this, pDocument)))
				{
					for (nItem = 0, nItems = (INT)pItems.GetSize(), pGroup[1]->Lock(); nItem < nItems; nItem++)
					{
						if ((pItem = (CMimicsItem *)pItems.GetAt(nItem)))
						{
							pDocument->RemoveItem(pItem);
							pGroup[1]->AddItem(pItem);
						}
					}
					SetActivatedItem(pGroup[1]);
					pGroup[1]->Unlock();
					UpdateUndoList();
				}
				delete pGroup[0];
			}
			return;
		}
	}
	if ((pGroup[0] = (CMimicsGroup *)GetActivatedItem()))
	{
		for (nItem = 0, nItems = (INT)pItems.GetSize(), pGroup[0]->Lock(); nItem < nItems; nItem++)
		{
			if ((pItem = (CMimicsItem *)pItems.GetAt(nItem)))
			{
				pDocument->RemoveItem(pItem);
				pGroup[0]->AddItem(pItem);
			}
		}
		SetActivatedItem(pGroup[0]);
		pGroup[0]->Unlock();
		UpdateUndoList();
	}
}

BOOL CMMDImageView::CanCollectMimicsGroup() CONST
{
	return((HasActivatedItem() && HasSelectedItems()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DiscardMimicsGroup()
{
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMimicsGroup  *pGroup[2];
	CMMDDocument  *pDocument;

	if ((pGroup[0] = (CMimicsGroup *)GetActivatedItem()))
	{
		for (lPosition = ((pDocument = GetDocument())) ? pGroup[0]->GetItemList()->GetStartPosition() : (POSITION)NULL, pGroup[0]->Lock(); lPosition; )
		{
			if ((pItem = (CMimicsItem *)pGroup[0]->GetItemList()->GetNextItem(lPosition)))
			{
				if ((pGroup[1] = (CMimicsGroup *)pGroup[0]->GetItemContainer()))
				{
					pGroup[0]->RemoveItem(pItem);
					pGroup[1]->AddItem(pItem);
					continue;
				}
				pGroup[0]->RemoveItem(pItem);
				pDocument->AddItem(pItem);
			}
		}
		SetActivatedItem(pItem);
		pGroup[0]->Unlock();
		UpdateUndoList();
		delete pGroup[0];
	}
}

BOOL CMMDImageView::CanDiscardMimicsGroup() CONST
{
	CMimicsItem  *pItem;
	CMimicsGroup  *pGroup;

	return(((pItem = GetActivatedItem()) && pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup))) ? (((pGroup = (CMimicsGroup *)pItem)->GetItemCount() > 0 && !HasSelectedItems()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE) : FALSE);
}

VOID CMMDImageView::StepIntoMimicsGroup()
{
	CMimicsItem  *pItem;
	CMimicsGroup  *pGroup;

	if ((pGroup = (CMimicsGroup *)GetActivatedItem()))
	{
		if ((pItem = (CMimicsItem *)pGroup->GetItemList()->m_docItemList.GetAt(pGroup->GetItemList()->GetStartPosition())))
		{
			SetActivatedItem(pItem);
			UpdateUndoList();
		}
	}
}

BOOL CMMDImageView::CanStepIntoMimicsGroup() CONST
{
	CMimicsItem  *pItem;
	CMimicsGroup  *pGroup;

	return(((pItem = GetActivatedItem()) && pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup))) ? (((pGroup = (CMimicsGroup *)pItem)->GetItemCount() > 0 && !HasSelectedItems()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE) : FALSE);
}

VOID CMMDImageView::StepOutMimicsGroup()
{
	CMimicsItem  *pItem[2];

	if ((pItem[0] = GetActivatedItem()))
	{
		if ((pItem[1] = pItem[0]->GetItemContainer()))
		{
			SetActivatedItem(pItem[1]);
			UpdateUndoList();
		}
	}
}

BOOL CMMDImageView::CanStepOutMimicsGroup() CONST
{
	CMimicsItem  *pItem;

	return(((pItem = GetActivatedItem()) && pItem->GetItemContainer() && !HasSelectedItems()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoHorzAlignItems()
{
	CRect  rItem[2];
	POSITION  lPosition;
	CMimicsItem  *pItem[2];
	CMMDDocument  *pDocument;

	if ((pItem[0] = GetActivatedItem()))
	{
		for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, rItem[0] = GetActivatedItem()->GetItemPosition(); lPosition; )
		{
			if ((pItem[1] = (CMimicsItem *)pDocument->GetNextItem(lPosition)) && pItem[1]->IsItemSelected())
			{
				rItem[1] = pItem[1]->GetItemPosition();
				rItem[1].OffsetRect(0, rItem[0].CenterPoint().y - rItem[1].CenterPoint().y);
				pItem[1]->AdjustItemPosition(rItem[1]);
			}
		}
		UpdateUndoList();
		UpdateAllItems();
	}
}

BOOL CMMDImageView::CanHorzAlignItems() CONST
{
	return((HasActivatedItem() && HasSelectedItems()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoVertAlignItems()
{
	CRect  rItem[2];
	POSITION  lPosition;
	CMimicsItem  *pItem[2];
	CMMDDocument  *pDocument;

	if ((pItem[0] = GetActivatedItem()))
	{
		for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, rItem[0] = GetActivatedItem()->GetItemPosition(); lPosition; )
		{
			if ((pItem[1] = (CMimicsItem *)pDocument->GetNextItem(lPosition)) && pItem[1]->IsItemSelected())
			{
				rItem[1] = pItem[1]->GetItemPosition();
				rItem[1].OffsetRect(rItem[0].CenterPoint().x - rItem[1].CenterPoint().x, 0);
				pItem[1]->AdjustItemPosition(rItem[1]);
			}
		}
		UpdateUndoList();
		UpdateAllItems();
	}
}

BOOL CMMDImageView::CanVertAlignItems() CONST
{
	return((HasActivatedItem() && HasSelectedItems()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoMoveItemToTop()
{
	INT  nCount;
	INT  nPosition;

	if ((nCount = EnumOverlappingItems(nPosition)) > 0)
	{
		RepositionOverlappingItems(nCount);
		UpdateUndoList();
	}
}

BOOL CMMDImageView::CanMoveItemToTop() CONST
{
	INT  nCount;
	INT  nPosition;

	return(((nCount = EnumOverlappingItems(nPosition)) > 0 && nPosition < nCount) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoMoveItemToBottom()
{
	INT  nCount;
	INT  nPosition;

	if ((nCount = EnumOverlappingItems(nPosition)) > 0)
	{
		RepositionOverlappingItems(0);
		UpdateUndoList();
	}
}

BOOL CMMDImageView::CanMoveItemToBottom() CONST
{
	INT  nCount;
	INT  nPosition;

	return(((nCount = EnumOverlappingItems(nPosition)) > 0 && nPosition > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoMoveItemUp()
{
	INT  nCount;
	INT  nPosition;

	if ((nCount = EnumOverlappingItems(nPosition)) > 0)
	{
		RepositionOverlappingItems(nPosition + 1);
		UpdateUndoList();
	}
}

BOOL CMMDImageView::CanMoveItemUp() CONST
{
	INT  nCount;
	INT  nPosition;

	return(((nCount = EnumOverlappingItems(nPosition)) > 0 && nPosition < nCount) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoMoveItemDown()
{
	INT  nCount;
	INT  nPosition;

	if ((nCount = EnumOverlappingItems(nPosition)) > 0)
	{
		RepositionOverlappingItems(nPosition - 1);
		UpdateUndoList();
	}
}

BOOL CMMDImageView::CanMoveItemDown() CONST
{
	INT  nCount;
	INT  nPosition;

	return(((nCount = EnumOverlappingItems(nPosition)) > 0 && nPosition > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoShowHideItem()
{
	CMimicsItem  *pItem;

	if ((pItem = GetActivatedItem()))
	{
		if (!pItem->IsItemVisible())
		{
			pItem->ShowItem();
			UpdateUndoList();
			return;
		}
		pItem->HideItem();
		UpdateUndoList();
	}
}

BOOL CMMDImageView::CanShowHideItem() CONST
{
	return((HasActivatedItem()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoHorzFlipItem()
{
	CMimicsItem  *pItem;

	if ((pItem = GetActivatedItem()))
	{
		pItem->HorzFlipItem();
		UpdateUndoList();
	}
}

BOOL CMMDImageView::CanHorzFlipItem() CONST
{
	return((HasActivatedItem()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoVertFlipItem()
{
	CMimicsItem  *pItem;

	if ((pItem = GetActivatedItem()))
	{
		pItem->VertFlipItem();
		UpdateUndoList();
	}
}

BOOL CMMDImageView::CanVertFlipItem() CONST
{
	return((HasActivatedItem()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::DoRotateItem(double fAngle)
{
	CMimicsItem  *pItem;

	if ((pItem = GetActivatedItem()))
	{
		pItem->RotateItem(fAngle);
		UpdateUndoList();
	}
}

BOOL CMMDImageView::CanRotateItem() CONST
{
	return((HasActivatedItem()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDImageView::SetItemRotateMode(BOOL bFlag)
{
	CMimicsItem  *pItem;

	if ((pItem = GetActivatedItem()))
	{
		pItem->SetItemRotateMode(bFlag);
		UpdateAllItems();
	}
}

BOOL CMMDImageView::GetItemRotateMode() CONST
{
	CMimicsItem  *pItem;

	return(((pItem = GetActivatedItem())) ? pItem->GetItemRotateMode() : FALSE);
}

HRESULT CMMDImageView::SetCaptureOnItem(CMimicsItem *pItem)
{
	if (SetFocusOnItem(pItem) == S_OK)
	{
		if (IsWindow(pItem->GetInPlaceWindow()->GetSafeHwnd()))
		{
			pItem->GetInPlaceWindow()->SetCapture();
			return S_OK;
		}
		SetCapture();
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CMMDImageView::ReleaseCaptureFromItem(CMimicsItem *pItem)
{
	if (pItem == GetItemWithCapture())
	{
		ReleaseCapture();
		return S_OK;
	}
	return E_FAIL;
}

CMimicsItem *CMMDImageView::GetItemWithCapture() CONST
{
	CMimicsItem  *pItem;

	return(((pItem = GetItemWithFocus())) ? (((!IsWindow(pItem->GetInPlaceWindow()->GetSafeHwnd()) && CWnd::GetCapture() == (CWnd *) this) || (IsWindow(pItem->GetInPlaceWindow()->GetSafeHwnd()) && IsWindow(CWnd::GetCapture()->GetSafeHwnd()) && pItem->GetInPlaceWindow()->IsChild(CWnd::GetCapture()))) ? pItem : (CMimicsItem *)NULL) : (CMimicsItem *)NULL);
}

HRESULT CMMDImageView::SetFocusOnItem(CMimicsItem *pItem)
{
	CWnd  *pWnd;

	if (SetActivatedItem(pItem))
	{
		if ((pWnd = (IsWindow(pItem->GetInPlaceWindow()->GetSafeHwnd())) ? pItem->GetInPlaceWindow() : CWnd::FromHandle(GetSafeHwnd())))
		{
			pWnd->SetFocus();
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT CMMDImageView::ReleaseFocusFromItem(CMimicsItem *pItem)
{
	if (pItem == GetItemWithFocus())
	{
		SetActivatedItem();
		return S_OK;
	}
	return E_FAIL;
}

CMimicsItem *CMMDImageView::GetItemWithFocus() CONST
{
	CMimicsItem  *pItem;

	return(((pItem = GetActivatedItem())) ? (((!IsWindow(pItem->GetInPlaceWindow()->GetSafeHwnd()) && CWnd::GetFocus() == (CWnd *) this) || (IsWindow(pItem->GetInPlaceWindow()->GetSafeHwnd()) && IsWindow(CWnd::GetFocus()->GetSafeHwnd()) && pItem->GetInPlaceWindow()->IsChild(CWnd::GetFocus()))) ? pItem : (CMimicsItem *)NULL) : (CMimicsItem *)NULL);
}

INT CMMDImageView::EnumItems(CPtrArray &pItems) CONST
{
	CMMDDocument  *pDocument;

	return(((pDocument = GetDocument())) ? pDocument->EnumItems(pItems) : 0);
}
INT CMMDImageView::EnumItems(CStringArray &szItems) CONST
{
	INT  nItem;
	INT  nItems;
	BSTR  pszType;
	CLSID   clsidItem;

	for (nItem = 0, nItems = (m_pIEnumMimicsCtrls != (IEnumMimicsCtrls *)NULL) ? m_pIEnumMimicsCtrls->GetMimicsCtrlsCount() : 0, szItems.RemoveAll(); nItem < nItems; nItem++)
	{
		if (m_pIEnumMimicsCtrls->GetMimicsCtrlProperties(nItem, &pszType, &clsidItem) && clsidItem != CLSID_CMimicsGroupCtrl)
		{
			szItems.Add(pszType);
			SysFreeString(pszType);
		}
	}
	return((INT)szItems.GetSize());
}

INT CMMDImageView::GetItemCount() CONST
{
	CMMDDocument  *pDocument;

	return(((pDocument = GetDocument())) ? (INT)pDocument->m_docItemList.GetCount() : 0);
}

VOID CMMDImageView::UpdateAllItems(BOOL bUndo)
{
	CMimicsItem  *pMimicsItem;

	for (SetScrollSizes(MM_TEXT, CalcScrollSizes()), DrawImage(); bUndo; )
	{
		UpdateUndoList();
		break;
	}
	for (UpdateZoomWindow(); (pMimicsItem = GetActivatedItem()); )
	{
		GetParent()->GetParent()->UpdateBars(pMimicsItem);
		return;
	}
	GetParent()->GetParent()->UpdateBars();
}
BOOL CMMDImageView::UpdateAllItems(CMimicsItem *pItem)
{
	CString  szName;
	CString  szType;
	CString  szMessage;
	POSITION  lPosition;
	CMimicsItem  *pMimicsItem;
	CMMDDocument  *pDocument;

	if ((szName = pItem->GetItemName()) != STRING(IDS_MMD_STATUSBAR_OBJECTDEFAULTNAME))
	{
		for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, szType = pItem->GetItemType(); lPosition; )
		{
			if ((pMimicsItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)) && pMimicsItem != pItem)
			{
				if (pMimicsItem->GetItemName() == szName  &&  pMimicsItem->GetItemType() == szType)
				{
					lPosition = (POSITION)-1;
					break;
				}
			}
		}
		if (!lPosition)
		{
			pItem->SetItemName(szName);
			UpdateUndoList();
			UpdateAllItems();
			return TRUE;
		}
		szMessage.Format(STRING(IDS_MMD_FAILURE_IDENTICALITEMNAMES), (LPCTSTR)GetParent()->GetParent()->GetTitle(), (LPCTSTR)szName);
		MessageBox(szMessage, GetAppTitle(), MB_ICONINFORMATION | MB_OK);
		pItem->SetItemName();
		UpdateUndoList();
		UpdateAllItems();
		return FALSE;
	}
	UpdateUndoList();
	UpdateAllItems();
	return TRUE;
}

VOID CMMDImageView::SetHotSpot(CONST RECT &rect)
{
	m_rItemZoomHotSpot = rect;
}

CRect CMMDImageView::GetHotSpot() CONST
{
	return m_rItemZoomHotSpot;
}

VOID CMMDImageView::DrawHotSpot(CDC *pDC, CONST SIZE &size)
{
	CDC  cMemDC[2];
	CRect  rHotSpot;
	CBitmap  cBitmap[2];
	CBitmap  *pOldBitmap[2];
	CZoomWnd  *pZoomWnd;

	if ((rHotSpot = GetHotSpot()).IsRectEmpty())
	{
		if ((pZoomWnd = GetMainWnd()->GetZoomWindow()))
		{
			rHotSpot.left = rHotSpot.top = 0;
			rHotSpot.right = size.cx;
			rHotSpot.bottom = size.cy;
			GetParent()->GetParent()->SetHotSpot(rHotSpot);
			pZoomWnd->SetScrollPos(SB_VERT, 0);
		}
	}
	if (cMemDC[0].CreateCompatibleDC(pDC))
	{
		if (cMemDC[1].CreateCompatibleDC(pDC))
		{
			if (cBitmap[0].CreateCompatibleBitmap(pDC, rHotSpot.right, rHotSpot.bottom))
			{
				if (cBitmap[1].CreateCompatibleBitmap(pDC, size.cx, size.cy))
				{
					if ((pOldBitmap[0] = (CBitmap *)cMemDC[0].SelectObject(&cBitmap[0])))
					{
						if ((pOldBitmap[1] = (CBitmap *)cMemDC[1].SelectObject(&cBitmap[1])))
						{
							cMemDC[0].FillSolidRect(rHotSpot, GetSysColor(COLOR_WINDOW));
							cMemDC[0].ExcludeClipRect(0, 0, rHotSpot.right, GetScrollPos(SB_VERT));
							cMemDC[0].ExcludeClipRect(0, 0, GetScrollPos(SB_HORZ), rHotSpot.bottom);
							DrawImage(&cMemDC[0], CRect(rHotSpot.left, rHotSpot.top, rHotSpot.right, rHotSpot.bottom));
							cMemDC[1].FillSolidRect(0, 0, size.cx, size.cy, GetSysColor(COLOR_WINDOW));
							cMemDC[1].StretchBlt(0, 0, size.cx, size.cy, &cMemDC[0], rHotSpot.left, rHotSpot.top, rHotSpot.Width(), rHotSpot.Height(), SRCCOPY);
							pDC->BitBlt(0, 0, size.cx, size.cy, &cMemDC[1], 0, 0, SRCCOPY);
							cMemDC[1].SelectObject(pOldBitmap[1]);
						}
						cMemDC[0].SelectObject(pOldBitmap[0]);
					}
					cBitmap[1].DeleteObject();
				}
				cBitmap[0].DeleteObject();
			}
			cMemDC[1].DeleteDC();
		}
		cMemDC[0].DeleteDC();
	}
}

BOOL CMMDImageView::GetPrintProperties(CMetaFileDC &cMetaDC)
{
	CClientDC  cDC(NULL);

	if (cMetaDC.CreateEnhanced(&cDC, (LPCTSTR)NULL, (LPCRECT)NULL, (LPCTSTR)NULL))
	{
		cMetaDC.SetAttribDC(cDC.GetSafeHdc());
		DrawImage(&cMetaDC);
		return TRUE;
	}
	return FALSE;
}

VOID CMMDImageView::SetModified(BOOL bFlag)
{
	for (m_bModified = bFlag; !bFlag; )
	{
		m_cLayout.SetImage(m_sizeImage, m_nImage[0], m_nImage[1], m_nImage[2], m_nImage[3], m_nImageBkgnd, m_sizeGrid, m_nImageGrid, m_bUseGrid);
		m_pDocument[1]->Copy(m_pDocument[0]);
		break;
	}
}

BOOL CMMDImageView::IsModified() CONST
{
	INT  nImage[4];
	BOOL  bUseGrid;
	CSize  sizeGrid;
	CSize  sizeImage;
	COLORREF  nImageGrid;
	COLORREF  nImageBkgnd;

	m_cLayout.GetImage(sizeImage, nImage[0], nImage[1], nImage[2], nImage[3], nImageBkgnd, sizeGrid, nImageGrid, bUseGrid);
	return((m_sizeImage != sizeImage || m_nImage[0] != nImage[0] || m_nImage[1] != nImage[1] || m_nImage[2] != nImage[2] || m_nImage[3] != nImage[3] || m_nImageBkgnd != nImageBkgnd || m_sizeGrid != sizeGrid || m_nImageGrid != nImageGrid || m_bUseGrid != bUseGrid || !m_pDocument[0]->Compare(m_pDocument[1]) || m_bModified) ? TRUE : FALSE);
}

CMMDDocument *CMMDImageView::GetDocument() CONST
{
	return m_pDocument[0];
}

CMMDSplitterWnd *CMMDImageView::GetParent() CONST
{
	return((CMMDSplitterWnd *)CScrollView::GetParent());
}

BOOL CMMDImageView::InstallMimicsCtrlInterface()
{
	BSTR  pszFormat;

	if (SUCCEEDED(CoGetClassObject(CLSID_CEnumMimicsCtrls, CLSCTX_INPROC, NULL, IID_IClassFactory, (LPVOID *)&m_pIClassFactory)))
	{
		if (SUCCEEDED(m_pIClassFactory->CreateInstance(NULL, IID_IUnknown, (LPVOID *)&m_pIUnknown)))
		{
			if (SUCCEEDED(m_pIUnknown->QueryInterface(IID_IEnumMimicsCtrls, (LPVOID *)&m_pIEnumMimicsCtrls)))
			{
				if ((m_nClipboardFormat = RegisterClipboardFormat(CString((pszFormat = m_pIEnumMimicsCtrls->GetMimicsClipboardFormat())))) > 0)
				{
					SysFreeString(pszFormat);
					return TRUE;
				}
				SysFreeString(pszFormat);
				m_pIEnumMimicsCtrls->Release();
				m_pIEnumMimicsCtrls = (IEnumMimicsCtrls *)NULL;
			}
			m_pIUnknown->Release();
			m_pIUnknown = (IUnknown *)NULL;
		}
		m_pIClassFactory->Release();
		m_pIClassFactory = (IClassFactory *)NULL;
	}
	return FALSE;
}

VOID CMMDImageView::DestroyMimicsCtrlInterface()
{
	if (m_pIEnumMimicsCtrls != (IEnumMimicsCtrls *)NULL)
	{
		m_pIEnumMimicsCtrls->Release();
		m_pIEnumMimicsCtrls = (IEnumMimicsCtrls *)NULL;
	}
	if (m_pIUnknown != (IUnknown *)NULL)
	{
		m_pIUnknown->Release();
		m_pIUnknown = (IUnknown *)NULL;
	}
	if (m_pIClassFactory != (IClassFactory *)NULL)
	{
		m_pIClassFactory->Release();
		m_pIClassFactory = (IClassFactory *)NULL;
	}
}

VOID CMMDImageView::DrawImage()
{
	CDC  *pDC;

	if ((pDC = GetDC()))
	{
		pDC->SetViewportOrg(-GetScrollPosition());
		DrawImage(pDC);
		ReleaseDC(pDC);
	}
}
VOID CMMDImageView::DrawImage(CDC *pDC)
{
	DrawImage(pDC, CRect(0, 0, 0, 0));
}
VOID CMMDImageView::DrawImage(CDC *pDC, CONST RECT &rect)
{
	CDC  cDC;
	CRect  rView;
	CRect  rImage;
	CSize  sizeView;
	DWORD  dwDCType;
	CBitmap  bmpImage;
	CBitmap  *pOldBitmap;

	if ((dwDCType = GetObjectType(pDC->GetSafeHdc())) == OBJ_DC)
	{
		for (GetClientRect(rView), sizeView.cx = max(GetTotalSize().cx, rView.Width()) + 1, sizeView.cy = max(GetTotalSize().cy, rView.Height()) + 1, rImage.SetRect((IsRectEmpty(&rect)) ? GetScrollPos(SB_HORZ) : rect.left, (IsRectEmpty(&rect)) ? GetScrollPos(SB_VERT) : rect.top, (IsRectEmpty(&rect)) ? (GetScrollPos(SB_HORZ) + rView.Width()) : rect.right, (IsRectEmpty(&rect)) ? (GetScrollPos(SB_VERT) + rView.Height()) : rect.bottom); cDC.CreateCompatibleDC(pDC); )
		{
			if (bmpImage.CreateCompatibleBitmap(pDC, sizeView.cx, sizeView.cy))
			{
				if ((pOldBitmap = cDC.SelectObject(&bmpImage)))
				{
					DrawImage(&cDC, rect, FALSE);
					pDC->BitBlt(rImage.left, rImage.top, rImage.Width(), rImage.Height(), &cDC, rImage.left, rImage.top, SRCCOPY);
					cDC.SelectObject(pOldBitmap);
				}
				bmpImage.DeleteObject();
			}
			cDC.DeleteDC();
			break;
		}
		return;
	}
	DrawImage(pDC, rect, (dwDCType == OBJ_ENHMETADC) ? TRUE : FALSE);
}
VOID CMMDImageView::DrawImage(CDC *pDC, CONST RECT &rect, BOOL bPrinting)
{
	INT  nRgn;
	INT  nTop;
	INT  nLeft;
	INT  nMode;
	INT  nRight;
	INT  nBottom;
	CPen  cAreaPen;
	CPen  *pOldPen;
	CRgn  rgn[4];
	CRgn  rgClip;
	CRgn  rgView;
	CRect  rView;
	CRect  rItem;
	CRect  rImage;
	CSize  sizeView;
	CSize  sizeImage;
	CPoint  ptImageOrigin;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	for (GetClientRect(rView), sizeImage = GetImageSize(), ptImageOrigin = GetImageOrigin(), rImage.left = GetScrollPos(SB_HORZ) + rView.left, rImage.top = GetScrollPos(SB_VERT) + rView.top, rImage.right = GetScrollPos(SB_HORZ) + rView.right, rImage.bottom = GetScrollPos(SB_VERT) + rView.bottom, sizeView.cx = max(GetTotalSize().cx, rView.Width()) + 1, sizeView.cy = max(GetTotalSize().cy, rView.Height()) + 1, GetImageMargin(nLeft, nTop, nRight, nBottom); !bPrinting; )
	{
		DrawBackground(pDC, ptImageOrigin.x, ptImageOrigin.y, rect, sizeView, sizeImage);
		break;
	}
	if (((!bPrinting  &&  rgn[0].CreateRectRgn(max(ptImageOrigin.x + nLeft, ptImageOrigin.x + GetScrollPos(SB_HORZ)), max(ptImageOrigin.y + nTop, ptImageOrigin.y + GetScrollPos(SB_VERT)), min(ptImageOrigin.x + sizeImage.cx - nRight, ptImageOrigin.x + GetScrollPos(SB_HORZ) + sizeImage.cx), min(ptImageOrigin.y + sizeImage.cy - nBottom, ptImageOrigin.y + GetScrollPos(SB_VERT) + sizeImage.cy)) && rgn[1].CreateRectRgn(ptImageOrigin.x + sizeImage.cx, ptImageOrigin.y + GetScrollPos(SB_VERT), ptImageOrigin.x + GetScrollPos(SB_HORZ) + sizeView.cx, ptImageOrigin.y + GetScrollPos(SB_VERT) + sizeView.cy) && rgn[2].CreateRectRgn(ptImageOrigin.x + GetScrollPos(SB_HORZ), ptImageOrigin.y + sizeImage.cy, ptImageOrigin.x + GetScrollPos(SB_HORZ) + sizeImage.cx, ptImageOrigin.y + GetScrollPos(SB_VERT) + sizeView.cy) && rgn[3].CreateRectRgn(ptImageOrigin.x + GetScrollPos(SB_HORZ), ptImageOrigin.y + GetScrollPos(SB_VERT), ptImageOrigin.x + GetScrollPos(SB_HORZ) + rView.Width(), ptImageOrigin.y + GetScrollPos(SB_VERT) + rView.Height()) && rgClip.CreateRectRgn(0, 0, 0, 0) && rgClip.CombineRgn(&rgn[0], &rgn[1], RGN_OR) != ERROR  &&  rgClip.CombineRgn(&rgClip, &rgn[2], RGN_OR) != ERROR) || (bPrinting  &&  rgn[0].CreateRectRgn(ptImageOrigin.x, ptImageOrigin.y, ptImageOrigin.x + sizeImage.cx, ptImageOrigin.y + sizeImage.cy) && rgn[1].CreateRectRgn(0, 0, ptImageOrigin.x + sizeImage.cx, ptImageOrigin.y + sizeImage.cy) && rgClip.CreateRectRgn(ptImageOrigin.x + nLeft, ptImageOrigin.y + nTop, ptImageOrigin.x + sizeImage.cx - nRight, ptImageOrigin.y + sizeImage.cy - nBottom))) && rgView.CreateRectRgn(0, 0, 0, 0))
	{
		for (nRgn = GetClipRgn(pDC->GetSafeHdc(), (HRGN)rgView.GetSafeHandle()); bPrinting && pDC->SelectClipRgn(&rgn[0]) != ERROR; )
		{
			DrawBackground(pDC, ptImageOrigin.x, ptImageOrigin.y, rect, sizeView, sizeImage);
			break;
		}
		if (pDC->SelectClipRgn(&rgClip) != ERROR)
		{
			for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
			{
				if ((pItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
				{
					if (bPrinting  &&  IsRectEmpty(&rect))
					{
						pItem->Draw(pDC);
						continue;
					}
					if (!bPrinting  &&  IsRectEmpty(&rect))
					{
						if (rItem.IntersectRect(rImage, pItem->CalcItemFramePosition())) pItem->Draw(pDC);
						continue;
					}
					if (rItem.IntersectRect(&rect, pItem->CalcItemFramePosition()))
					{
						pItem->Draw(pDC);
						continue;
					}
				}
			}
			if ((!bPrinting  &&  pDC->SelectClipRgn(&rgn[3]) != ERROR) || bPrinting)
			{
				for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
				{
					if ((pItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)) && pItem != GetActivatedItem())
					{
						pItem->DrawItemFrame(pDC, pItem->GetItemPosition());
						continue;
					}
				}
				for (; (pItem = GetActivatedItem()) && IsDraggingItem() && IsDraggingItem() != MIAC_FIRSTRADIALTHUMB && IsDraggingItem() != MIAC_LASTRADIALTHUMB; )
				{
					pItem->DrawItemDraggingFrame(pDC, pItem->GetItemPosition());
					break;
				}
				for (; (pItem = GetActivatedItem()); )
				{
					pItem->DrawItemFrame(pDC, pItem->GetItemPosition());
					break;
				}
				if (HasSelectedItemsArea())
				{
					if (cAreaPen.CreatePen(PS_DOT, 1, GetSysColor(COLOR_WINDOWFRAME)))
					{
						if ((pOldPen = pDC->SelectObject(&cAreaPen)))
						{
							nMode = pDC->SetROP2(R2_MASKNOTPEN);
							pDC->MoveTo(GetSelectedItemsArea().left, GetSelectedItemsArea().top);
							pDC->LineTo(GetSelectedItemsArea().right, GetSelectedItemsArea().top);
							pDC->LineTo(GetSelectedItemsArea().right, GetSelectedItemsArea().bottom);
							pDC->LineTo(GetSelectedItemsArea().left, GetSelectedItemsArea().bottom);
							pDC->LineTo(GetSelectedItemsArea().left, GetSelectedItemsArea().top);
							pDC->SetROP2(nMode);
							pDC->SelectObject(pOldPen);
						}
						cAreaPen.DeleteObject();
					}
				}
			}
		}
		for (pDC->SelectClipRgn((nRgn > 0) ? &rgView : (CRgn *)NULL); bPrinting; )
		{
			if (pDC->SelectClipRgn(&rgn[1]) != ERROR) DrawRulers(pDC, CSize(rView.Width(), rView.Height()), sizeImage, CalcHorizontalRulerPosition(CRect(0, 0, sizeView.cx, sizeView.cy)), CalcVerticalRulerPosition(CRect(0, 0, sizeView.cx, sizeView.cy)));
			pDC->SelectClipRgn((nRgn > 0) ? &rgView : (CRgn *)NULL);
			break;
		}
		if (!bPrinting)
		{
			DrawRulers(pDC, CSize(rView.Width(), rView.Height()), sizeImage, CalcHorizontalRulerPosition(rImage), CalcVerticalRulerPosition(rImage));
			pDC->FillSolidRect(GetScrollPos(SB_HORZ) + rView.Width(), rView.top, sizeView.cx - (GetScrollPos(SB_HORZ) + rView.Width()), rView.Height(), GetSysColor(COLOR_WINDOW));
			pDC->FillSolidRect(rView.left, GetScrollPos(SB_VERT) + rView.Height(), rView.Width(), sizeView.cy - (GetScrollPos(SB_VERT) + rView.Height()), GetSysColor(COLOR_WINDOW));
			rgn[2].DeleteObject();
			rgn[3].DeleteObject();
		}
		rgn[0].DeleteObject();
		rgn[1].DeleteObject();
		rgView.DeleteObject();
		rgClip.DeleteObject();
	}
}

VOID CMMDImageView::DrawBackground(CDC *pDC, INT x, INT y, CONST RECT &rect, CONST SIZE &sizeView, CONST SIZE &sizeImage)
{
	INT  nGridX;
	INT  nGridY;
	INT  nBkMode;
	INT  nMargin[4];
	BOOL  bUseGrid;
	CPen  cGridPen;
	CPen  *pOldPen;
	CRect  rImage;
	CSize  sizeGrid;
	CSize  sizePicture;
	CBrush  brImageBkgnd;
	COLORREF  nGridColor;
	COLORREF  nImageBkgnd;

	for (GetImage(sizePicture, nMargin[0], nMargin[1], nMargin[2], nMargin[3], nImageBkgnd, sizeGrid, nGridColor, bUseGrid), rImage.IntersectRect((IsRectEmpty(&rect)) ? CRect(x, y, (!sizeImage.cx && !sizeImage.cy) ? (x + sizeView.cx) : (x + sizeImage.cx), (!sizeImage.cx && !sizeImage.cy) ? (y + sizeView.cy) : (y + sizeImage.cy)) : CRect(rect), CRect(x, y, (!sizeImage.cx && !sizeImage.cy) ? (x + sizeView.cx) : (x + sizeImage.cx), (!sizeImage.cx && !sizeImage.cy) ? (y + sizeView.cy) : (y + sizeImage.cy))), nGridX = (sizeGrid.cx > 0 && sizeGrid.cy > 0) ? ((rImage.left / sizeGrid.cx)*sizeGrid.cx) : (rImage.right + 1), pDC->FillSolidRect(rImage.left, rImage.top, rImage.Width(), rImage.Height(), nImageBkgnd); nGridX <= rImage.right; nGridX += sizeGrid.cx)
	{
		for (nGridY = (rImage.top / sizeGrid.cy)*sizeGrid.cy; nGridY <= rImage.bottom; nGridY += sizeGrid.cy)
		{
			if (rImage.PtInRect(CPoint(nGridX, nGridY)))
			{
				pDC->SetPixelV(nGridX, nGridY, nGridColor);
				continue;
			}
		}
	}
	if (sizeGrid.cx < 0 && sizeGrid.cy < 0)
	{
		if (cGridPen.CreatePen(PS_SOLID, 0, nGridColor))
		{
			if ((pOldPen = pDC->SelectObject(&cGridPen)))
			{
				for (nGridX = (rImage.left / sizeGrid.cx)*sizeGrid.cx; nGridX <= rImage.right; nGridX += abs(sizeGrid.cx))
				{
					if (nGridX >= rImage.left)
					{
						pDC->MoveTo(nGridX, rImage.top);
						pDC->LineTo(nGridX, rImage.bottom + 1);
					}
				}
				for (nGridY = (rImage.top / sizeGrid.cy)*sizeGrid.cy; nGridY <= rImage.bottom; nGridY += abs(sizeGrid.cy))
				{
					if (nGridY >= rImage.top)
					{
						pDC->MoveTo(rImage.left, nGridY);
						pDC->LineTo(rImage.right + 1, nGridY);
					}
				}
				pDC->SelectObject(pOldPen);
			}
			cGridPen.DeleteObject();
		}
	}
	for (nBkMode = pDC->SetBkMode(OPAQUE), nImageBkgnd = pDC->SetBkColor(GetSysColor(COLOR_WINDOW)); brImageBkgnd.CreateHatchBrush(HS_DIAGCROSS, VGA_COLOR_LTGRAY); )
	{
		pDC->FillRect(CRect(x + sizeImage.cx, y, sizeView.cx, sizeView.cy), &brImageBkgnd);
		pDC->FillRect(CRect(x, y + sizeImage.cy, sizeView.cx, sizeView.cy), &brImageBkgnd);
		brImageBkgnd.DeleteObject();
		break;
	}
	pDC->SetBkColor(nImageBkgnd);
	pDC->SetBkMode(nBkMode);
}

VOID CMMDImageView::DrawRulers(CDC *pDC, CONST SIZE &sizeView, CONST SIZE &sizeImage, CONST RECT &rHorzRuler, CONST RECT &rVertRuler)
{
	INT  x;
	INT  y;
	INT  nTop;
	INT  nLeft;
	INT  nRight;
	INT  nBottom;
	CPen  *pOldPen;
	CPen  cEdgePen;
	CPen  cGridsPen;
	CPen  cTicksPen;
	CPen  cDividerPen;
	POINT  ptThumbSymbol[6][3];
	LOGBRUSH  cPenBrush;

	for (GetImageMargin(nLeft, nTop, nRight, nBottom), cPenBrush.lbHatch = 0, cPenBrush.lbStyle = BS_SOLID, cPenBrush.lbColor = GetSysColor(COLOR_WINDOWTEXT), pDC->FillSolidRect(&rHorzRuler, GetSysColor(COLOR_3DFACE)), pDC->FillSolidRect(&rVertRuler, GetSysColor(COLOR_3DFACE)), pDC->FillSolidRect(rVertRuler.left, rHorzRuler.top, rVertRuler.right - rVertRuler.left, rHorzRuler.bottom - rHorzRuler.top, GetSysColor(COLOR_3DFACE)); cEdgePen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW)); )
	{
		if ((pOldPen = pDC->SelectObject(&cEdgePen)))
		{
			pDC->MoveTo(rHorzRuler.left, rHorzRuler.bottom);
			pDC->LineTo(rHorzRuler.right, rHorzRuler.bottom);
			pDC->MoveTo(rVertRuler.right, rVertRuler.top);
			pDC->LineTo(rVertRuler.right, rVertRuler.bottom);
			pDC->SelectObject(pOldPen);
		}
		cEdgePen.DeleteObject();
		break;
	}
	if (cGridsPen.CreatePen(PS_SOLID | PS_GEOMETRIC | PS_ENDCAP_FLAT, 2, &cPenBrush))
	{
		if ((pOldPen = pDC->SelectObject(&cGridsPen)) != (CPen *)NULL)
		{
			for (x = rVertRuler.right - rVertRuler.left + MMDIMAGEVIEW_RULER_GRIDSINTERVAL; x < rHorzRuler.right; )
			{
				if (x > rHorzRuler.left)
				{
					pDC->MoveTo(x, rHorzRuler.top + (rHorzRuler.bottom - rHorzRuler.top) / 5);
					pDC->LineTo(x, rHorzRuler.bottom - (rHorzRuler.bottom - rHorzRuler.top) / 5);
				}
				x += MMDIMAGEVIEW_RULER_GRIDSINTERVAL;
			}
			for (y = rHorzRuler.bottom - rHorzRuler.top + MMDIMAGEVIEW_RULER_GRIDSINTERVAL; y < rVertRuler.bottom; )
			{
				if (y > rVertRuler.top)
				{
					pDC->MoveTo(rVertRuler.left + (rVertRuler.right - rVertRuler.left) / 5, y);
					pDC->LineTo(rVertRuler.right - (rVertRuler.right - rVertRuler.left) / 5, y);
				}
				y += MMDIMAGEVIEW_RULER_GRIDSINTERVAL;
			}
			pDC->SelectObject(pOldPen);
		}
		cGridsPen.DeleteObject();
	}
	if (cTicksPen.CreatePen(PS_SOLID | PS_GEOMETRIC | PS_ENDCAP_FLAT, 1, &cPenBrush))
	{
		if ((pOldPen = pDC->SelectObject(&cTicksPen)) != (CPen *)NULL)
		{
			for (x = rVertRuler.right - rVertRuler.left; x < rHorzRuler.right; )
			{
				if (x >= rHorzRuler.left)
				{
					pDC->MoveTo(x, rHorzRuler.top + (rHorzRuler.bottom - rHorzRuler.top) / 3);
					pDC->LineTo(x, rHorzRuler.bottom - (rHorzRuler.bottom - rHorzRuler.top) / 3);
				}
				x += MMDIMAGEVIEW_RULER_TICKSINTERVAL;
			}
			for (y = rHorzRuler.bottom - rHorzRuler.top; y < rVertRuler.bottom; )
			{
				if (y >= rVertRuler.top)
				{
					pDC->MoveTo(rVertRuler.left + (rVertRuler.right - rVertRuler.left) / 3, y);
					pDC->LineTo(rVertRuler.right - (rVertRuler.right - rVertRuler.left) / 3, y);
				}
				y += MMDIMAGEVIEW_RULER_TICKSINTERVAL;
			}
			pDC->SelectObject(pOldPen);
		}
		cTicksPen.DeleteObject();
	}
	CalcHorizontalRulerOuterThumbPosition(rHorzRuler, ptThumbSymbol[0], sizeof(ptThumbSymbol[0]) / sizeof(POINT));
	CalcVerticalRulerOuterThumbPosition(rVertRuler, ptThumbSymbol[1], sizeof(ptThumbSymbol[1]) / sizeof(POINT));
	CalcHorizontalRulerInnerLeftThumbPosition(rHorzRuler, nLeft, ptThumbSymbol[2], sizeof(ptThumbSymbol[2]) / sizeof(POINT));
	CalcHorizontalRulerInnerRightThumbPosition(rHorzRuler, nRight, ptThumbSymbol[3], sizeof(ptThumbSymbol[3]) / sizeof(POINT));
	CalcVerticalRulerInnerTopThumbPosition(rVertRuler, nTop, ptThumbSymbol[4], sizeof(ptThumbSymbol[4]) / sizeof(POINT));
	CalcVerticalRulerInnerBottomThumbPosition(rVertRuler, nBottom, ptThumbSymbol[5], sizeof(ptThumbSymbol[5]) / sizeof(POINT));
	DrawRulerThumb(pDC, IDP_MMDOUTERHORIZONTALTHUMB, ptThumbSymbol[0][0].x, ptThumbSymbol[0][2].y - 1);
	DrawRulerThumb(pDC, IDP_MMDOUTERVERTICALTHUMB, ptThumbSymbol[1][1].x - 1, ptThumbSymbol[1][0].y);
	DrawRulerThumb(pDC, IDP_MMDINNERHORIZONTALLEFTTHUMB, ptThumbSymbol[2][2].x - 1, ptThumbSymbol[2][1].y);
	DrawRulerThumb(pDC, IDP_MMDINNERHORIZONTALRIGHTTHUMB, ptThumbSymbol[3][0].x, ptThumbSymbol[3][2].y);
	DrawRulerThumb(pDC, IDP_MMDINNERVERTICALTOPTHUMB, ptThumbSymbol[4][1].x, ptThumbSymbol[4][2].y - 1);
	DrawRulerThumb(pDC, IDP_MMDINNERVERTICALBOTTOMTHUMB, ptThumbSymbol[5][1].x, ptThumbSymbol[5][0].y);
	if (IsDraggingOnRuler() & MMDIMAGEVIEW_DRAG_HORIZONTAL)
	{
		if (IsDraggingOnRuler() & MMDIMAGEVIEW_DRAG_OUTERMARGIN)
		{
			if (cDividerPen.CreatePen(PS_SOLID, 0, VGA_COLOR_GREEN))
			{
				if ((pOldPen = pDC->SelectObject(&cDividerPen)))
				{
					pDC->MoveTo((x = GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width() + sizeImage.cx), (y = GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height()));
					pDC->LineTo(x, y + sizeView.cy);
					pDC->SelectObject(pOldPen);
				}
				cDividerPen.DeleteObject();
			}
		}
		if (IsDraggingOnRuler() & MMDIMAGEVIEW_DRAG_INNERMARGIN)
		{
			if (IsDraggingOnRuler() & MMDIMAGEVIEW_DRAG_LEFT)
			{
				if (cDividerPen.CreatePen(PS_SOLID, 0, VGA_COLOR_LTBLUE))
				{
					if ((pOldPen = pDC->SelectObject(&cDividerPen)))
					{
						pDC->MoveTo((x = GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width() + nLeft), (y = GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height()));
						pDC->LineTo(x, y + sizeImage.cy);
						pDC->SelectObject(pOldPen);
					}
					cDividerPen.DeleteObject();
				}
			}
			if (IsDraggingOnRuler() & MMDIMAGEVIEW_DRAG_RIGHT)
			{
				if (cDividerPen.CreatePen(PS_SOLID, 0, VGA_COLOR_LTBLUE))
				{
					if ((pOldPen = pDC->SelectObject(&cDividerPen)))
					{
						pDC->MoveTo((x = GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width() + sizeImage.cx - nRight), (y = GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height()));
						pDC->LineTo(x, y + sizeImage.cy);
						pDC->SelectObject(pOldPen);
					}
					cDividerPen.DeleteObject();
				}
			}
		}
	}
	if (IsDraggingOnRuler() & MMDIMAGEVIEW_DRAG_VERTICAL)
	{
		if (IsDraggingOnRuler() & MMDIMAGEVIEW_DRAG_OUTERMARGIN)
		{
			if (cDividerPen.CreatePen(PS_SOLID, 0, VGA_COLOR_GREEN))
			{
				if ((pOldPen = pDC->SelectObject(&cDividerPen)))
				{
					pDC->MoveTo((x = GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width()), (y = GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height() + sizeImage.cy));
					pDC->LineTo(x + sizeView.cx, y);
					pDC->SelectObject(pOldPen);
				}
				cDividerPen.DeleteObject();
			}
		}
		if (IsDraggingOnRuler() & MMDIMAGEVIEW_DRAG_INNERMARGIN)
		{
			if (IsDraggingOnRuler() & MMDIMAGEVIEW_DRAG_TOP)
			{
				if (cDividerPen.CreatePen(PS_SOLID, 0, VGA_COLOR_LTBLUE))
				{
					if ((pOldPen = pDC->SelectObject(&cDividerPen)))
					{
						pDC->MoveTo((x = GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width()), (y = GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height() + nTop));
						pDC->LineTo(x + sizeImage.cx, y);
						pDC->SelectObject(pOldPen);
					}
					cDividerPen.DeleteObject();
				}
			}
			if (IsDraggingOnRuler() & MMDIMAGEVIEW_DRAG_BOTTOM)
			{
				if (cDividerPen.CreatePen(PS_SOLID, 0, VGA_COLOR_LTBLUE))
				{
					if ((pOldPen = pDC->SelectObject(&cDividerPen)))
					{
						pDC->MoveTo((x = GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width()), (y = GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height() + sizeImage.cy - nBottom));
						pDC->LineTo(x + sizeImage.cx, y);
						pDC->SelectObject(pOldPen);
					}
					cDividerPen.DeleteObject();
				}
			}
		}
	}
}

VOID CMMDImageView::DrawRulerThumb(CDC *pDC, UINT nResourceID, INT x, INT y)
{
	CDC  cMemDC;
	ULONG  cbSymbol;
	HRSRC  hResource;
	CImage  cSymbol;
	LPVOID  pResource;
	HGLOBAL  hMemResource[2];
	HMODULE  hModule;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	LPSTREAM  pIStream;
	CClientDC  cDC(this);

	if (cMemDC.CreateCompatibleDC(&cDC))
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), MAKEINTRESOURCE(nResourceID), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)) && SUCCEEDED(cSymbol.Load(pIStream)))
							{
								if (cBitmap.CreateCompatibleBitmap(&cDC, cSymbol.GetWidth(), cSymbol.GetHeight()))
								{
									if ((pOldBitmap = cMemDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
									{
										cMemDC.FillSolidRect(0, 0, cSymbol.GetWidth(), cSymbol.GetHeight(), VGA_COLOR_WHITE);
										cSymbol.Draw(cMemDC.GetSafeHdc(), 0, 0);
										pDC->BitBlt(x, y, cSymbol.GetWidth(), cSymbol.GetHeight(), &cMemDC, 0, 0, SRCAND);
										cMemDC.SelectObject(pOldBitmap);
									}
									cBitmap.DeleteObject();
								}
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		cMemDC.DeleteDC();
	}
}

CRect CMMDImageView::CalcHorizontalRulerPosition() CONST
{
	CRect  rView;

	GetClientRect(rView);
	rView.OffsetRect(GetScrollPos(SB_HORZ), 0);
	rView.OffsetRect(0, GetScrollPos(SB_VERT));
	return CalcHorizontalRulerPosition(rView);
}
CRect CMMDImageView::CalcHorizontalRulerPosition(CONST RECT &rect) CONST
{
	return CRect(rect.left + GetSystemMetrics(SM_CXVSCROLL), rect.top, rect.right, rect.top + GetSystemMetrics(SM_CYHSCROLL));
}

CRect CMMDImageView::CalcVerticalRulerPosition() CONST
{
	CRect  rView;

	GetClientRect(rView);
	rView.OffsetRect(GetScrollPos(SB_HORZ), 0);
	rView.OffsetRect(0, GetScrollPos(SB_VERT));
	return CalcVerticalRulerPosition(rView);
}
CRect CMMDImageView::CalcVerticalRulerPosition(CONST RECT &rect) CONST
{
	return CRect(rect.left, rect.top + GetSystemMetrics(SM_CYHSCROLL), rect.left + GetSystemMetrics(SM_CXVSCROLL), rect.bottom);
}

BOOL CMMDImageView::CalcHorizontalRulerOuterThumbPosition(CONST RECT &rect, POINT *pPoints, INT nPoints)
{
	CRect  rRuler(rect);
	POINT  ptThumb[3] = { { 0,0 },{ 0,0 },{ 0,0 } };

	if (GetImageSize().cx > 0 && GetImageSize().cy > 0)
	{
		ptThumb[0].x = CalcVerticalRulerPosition().Width() + GetImageSize().cx;
		ptThumb[0].y = rRuler.bottom - rRuler.Height() / 2 - 1;
		ptThumb[1].x = ptThumb[0].x + rRuler.Height() / 3;
		ptThumb[1].y = ptThumb[0].y;
		ptThumb[2].x = ptThumb[0].x;
		ptThumb[2].y = rRuler.top;
	}
	if (nPoints == (INT)(sizeof(ptThumb) / sizeof(POINT)))
	{
		CopyMemory(pPoints, ptThumb, nPoints*sizeof(POINT));
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDImageView::CalcHorizontalRulerInnerLeftThumbPosition(CONST RECT &rect, INT nMargin, POINT *pPoints, INT nPoints)
{
	CRect  rRuler(rect);
	POINT  ptThumb[3] = { { 0,0 },{ 0,0 },{ 0,0 } };

	if (GetImageSize().cx > 0 && GetImageSize().cy > 0)
	{
		ptThumb[0].x = CalcVerticalRulerPosition().Width() + nMargin;
		ptThumb[0].y = rRuler.bottom - 1;
		ptThumb[1].x = ptThumb[0].x;
		ptThumb[1].y = rRuler.bottom - rRuler.Height() / 2;
		ptThumb[2].x = ptThumb[0].x - rRuler.Height() / 3;
		ptThumb[2].y = ptThumb[1].y;
	}
	if (nPoints == (INT)(sizeof(ptThumb) / sizeof(POINT)))
	{
		CopyMemory(pPoints, ptThumb, nPoints*sizeof(POINT));
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDImageView::CalcHorizontalRulerInnerRightThumbPosition(CONST RECT &rect, INT nMargin, POINT *pPoints, INT nPoints)
{
	CRect  rRuler(rect);
	POINT  ptThumb[3] = { { 0,0 },{ 0,0 },{ 0,0 } };

	if (GetImageSize().cx > 0 && GetImageSize().cy > 0)
	{
		ptThumb[0].x = CalcVerticalRulerPosition().Width() + GetImageSize().cx - nMargin;
		ptThumb[0].y = rRuler.bottom - 1;
		ptThumb[1].x = ptThumb[0].x;
		ptThumb[1].y = rRuler.bottom - rRuler.Height() / 2;
		ptThumb[2].x = ptThumb[0].x + rRuler.Height() / 3;
		ptThumb[2].y = ptThumb[1].y;
	}
	if (nPoints == (INT)(sizeof(ptThumb) / sizeof(POINT)))
	{
		CopyMemory(pPoints, ptThumb, nPoints*sizeof(POINT));
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDImageView::CalcVerticalRulerOuterThumbPosition(CONST RECT &rect, POINT *pPoints, INT nPoints)
{
	CRect  rRuler(rect);
	POINT  ptThumb[3] = { { 0,0 },{ 0,0 },{ 0,0 } };

	if (GetImageSize().cx > 0 && GetImageSize().cy > 0)
	{
		ptThumb[0].x = rRuler.right - rRuler.Width() / 2 - 1;
		ptThumb[0].y = CalcHorizontalRulerPosition().Height() + GetImageSize().cy;
		ptThumb[1].x = rRuler.left;
		ptThumb[1].y = ptThumb[0].y;
		ptThumb[2].x = ptThumb[0].x;
		ptThumb[2].y = ptThumb[0].y + rRuler.Width() / 3;
	}
	if (nPoints == (INT)(sizeof(ptThumb) / sizeof(POINT)))
	{
		CopyMemory(pPoints, ptThumb, nPoints*sizeof(POINT));
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDImageView::CalcVerticalRulerInnerTopThumbPosition(CONST RECT &rect, INT nMargin, POINT *pPoints, INT nPoints)
{
	CRect  rRuler(rect);
	POINT  ptThumb[3] = { { 0,0 },{ 0,0 },{ 0,0 } };

	if (GetImageSize().cx > 0 && GetImageSize().cy > 0)
	{
		ptThumb[0].x = rRuler.right - 1;
		ptThumb[0].y = CalcHorizontalRulerPosition().Height() + nMargin;
		ptThumb[1].x = rRuler.right - rRuler.Width() / 2;
		ptThumb[1].y = ptThumb[0].y;
		ptThumb[2].x = ptThumb[1].x;
		ptThumb[2].y = ptThumb[0].y - rRuler.Width() / 3;
	}
	if (nPoints == (INT)(sizeof(ptThumb) / sizeof(POINT)))
	{
		CopyMemory(pPoints, ptThumb, nPoints*sizeof(POINT));
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDImageView::CalcVerticalRulerInnerBottomThumbPosition(CONST RECT &rect, INT nMargin, POINT *pPoints, INT nPoints)
{
	CRect  rRuler(rect);
	POINT  ptThumb[3] = { { 0,0 },{ 0,0 },{ 0,0 } };

	if (GetImageSize().cx > 0 && GetImageSize().cy > 0)
	{
		ptThumb[0].x = rRuler.right - 1;
		ptThumb[0].y = CalcHorizontalRulerPosition().Height() + GetImageSize().cy - nMargin;
		ptThumb[1].x = rRuler.right - rRuler.Width() / 2;
		ptThumb[1].y = ptThumb[0].y;
		ptThumb[2].x = ptThumb[1].x;
		ptThumb[2].y = ptThumb[0].y + rRuler.Width() / 3;
	}
	if (nPoints == (INT)(sizeof(ptThumb) / sizeof(POINT)))
	{
		CopyMemory(pPoints, ptThumb, nPoints*sizeof(POINT));
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDImageView::IsPointOnRulerThumb(CONST POINT &point, CONST POINT *pPoints) CONST
{
	return(((point.x >= min(min(pPoints[0].x, pPoints[1].x), pPoints[2].x) && point.x <= max(max(pPoints[0].x, pPoints[1].x), pPoints[2].x) && point.y >= min(min(pPoints[0].y, pPoints[1].y), pPoints[2].y) && point.y <= max(max(pPoints[0].y, pPoints[1].y), pPoints[2].y)) && (pPoints[0].x > 0 || pPoints[0].y > 0 || pPoints[1].x > 0 || pPoints[1].y > 0 || pPoints[2].x > 0 || pPoints[2].y > 0)) ? TRUE : FALSE);
}

INT CMMDImageView::EnumOverlappingItems(INT &nPosition) CONST
{
	INT  nCount;
	POSITION  lPosition;
	CMimicsItem  *pItem[2];
	CMMDDocument  *pDocument;

	if ((pItem[0] = GetActivatedItem()))
	{
		for (lPosition = ((pDocument = (CMMDDocument *)pItem[0]->GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, nCount = 0, nPosition = -1; lPosition; )
		{
			if ((pItem[1] = (CMimicsItem *)pDocument->GetNextItem(lPosition)) != (CMimicsItem *)NULL  &&  pItem[0] != pItem[1])
			{
				if (pItem[0]->GetItemContainer() == pItem[1]->GetItemContainer() && pItem[0]->CheckItemOnItem(pItem[1]))
				{
					nCount++;
					continue;
				}
			}
			if (pItem[0] == pItem[1])
			{
				nPosition = nCount;
				continue;
			}
		}
		return nCount;
	}
	nPosition = -1;
	return 0;
}

BOOL CMMDImageView::RepositionOverlappingItems(INT nPosition)
{
	INT  nCount;
	CRect  rItem;
	POSITION  lPosition;
	CMimicsItem  *pItem[2];
	CMMDDocument  *pDocument;

	if ((pItem[0] = GetActivatedItem()))
	{
		for (lPosition = ((pDocument = (CMMDDocument *)pItem[0]->GetDocument())) ? pDocument->m_docItemList.GetHeadPosition() : (POSITION)NULL, rItem = pItem[0]->CalcItemFramePosition(), nCount = 0; lPosition; )
		{
			if ((pItem[1] = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition)) != (CMimicsItem *)NULL  &&  pItem[0] != pItem[1])
			{
				if (pItem[0]->GetItemContainer() == pItem[1]->GetItemContainer() && pItem[0]->CheckItemOnItem(pItem[1]))
				{
					if (nPosition == nCount  &&  RepositionOverlappingItems(pItem[0], pItem[1]))
					{
						lPosition = (POSITION)-1;
						break;
					}
					nCount++;
				}
			}
		}
		for (lPosition = (!lPosition) ? pDocument->m_docItemList.GetTailPosition() : (POSITION)NULL; lPosition; )
		{
			if ((pItem[1] = (CMimicsItem *)pDocument->m_docItemList.GetPrev(lPosition)) != (CMimicsItem *)NULL  &&  pItem[0] != pItem[1])
			{
				if (pItem[0]->GetItemContainer() == pItem[1]->GetItemContainer() && pItem[0]->CheckItemOnItem(pItem[1]))
				{
					if (RepositionOverlappingItems(pItem[0], pItem[1], FALSE)) break;
					continue;
				}
			}
		}
		rItem.OffsetRect(-GetScrollPos(SB_HORZ), -GetScrollPos(SB_VERT));
		InvalidateRect(rItem, FALSE);
		UpdateWindow();
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDImageView::RepositionOverlappingItems(CMimicsItem *pItem, CMimicsItem *pPositionItem, BOOL bBefore)
{
	POSITION  lPosition[2];
	COleDocument  *pDocument;

	if ((pDocument = pItem->GetDocument()) == pPositionItem->GetDocument())
	{
		if ((lPosition[0] = pDocument->m_docItemList.Find(pItem)) && (lPosition[1] = pDocument->m_docItemList.Find(pPositionItem)))
		{
			if ((bBefore  &&  pDocument->m_docItemList.InsertBefore(lPosition[1], pItem)) || (!bBefore  &&  pDocument->m_docItemList.InsertAfter(lPosition[1], pItem)))
			{
				pDocument->m_docItemList.RemoveAt(lPosition[0]);
				return TRUE;
			}
		}
	}
	return FALSE;
}

HCURSOR CMMDImageView::DetermineItemCursor(CMimicsItem *pItem, CPoint point)
{
	INT  dx;
	INT  dy;
	UINT  nCode;
	CRect  rItem;
	CRect  rThumb;
	double  fAngle;

	if ((nCode = (!IsDraggingItem()) ? pItem->CheckPointOnItem(point) : MIAC_NOWHERE) == MIAC_SWTHUMB || nCode == MIAC_WTHUMB || nCode == MIAC_NWTHUMB || nCode == MIAC_NTHUMB || nCode == MIAC_NETHUMB || nCode == MIAC_ETHUMB || nCode == MIAC_SETHUMB || nCode == MIAC_STHUMB || nCode == MIAC_DRAGTHUMB || nCode == MIAC_FIRSTTHUMB || nCode == MIAC_LASTTHUMB || nCode == MIAC_FIRSTRADIALTHUMB || nCode == MIAC_LASTRADIALTHUMB)
	{
		if (pItem->GetItemRotateMode() || nCode == MIAC_FIRSTRADIALTHUMB || nCode == MIAC_LASTRADIALTHUMB)
		{
			switch (nCode)
			{
			case MIAC_SWTHUMB:
			case MIAC_NWTHUMB:
			case MIAC_NETHUMB:
			case MIAC_SETHUMB:
			case MIAC_FIRSTTHUMB:
			case MIAC_LASTTHUMB:
			case MIAC_FIRSTRADIALTHUMB:
			case MIAC_LASTRADIALTHUMB:
			{ return m_hRotateCursor;
			break;
			}
			}
			return GetCursor();
		}
		if (nCode != MIAC_DRAGTHUMB  &&  nCode != MIAC_FIRSTTHUMB  &&  nCode != MIAC_LASTTHUMB)
		{
			if (nCode == MIAC_STHUMB || nCode == MIAC_WTHUMB || nCode == MIAC_NTHUMB || nCode == MIAC_ETHUMB)
			{
				for (rItem = pItem->DoTransformation(pItem->GetItemPosition()), rThumb.SetRect(rItem.CenterPoint().x - MIMICSITEM_THUMB_SIZE / 2, rItem.CenterPoint().y - MIMICSITEM_THUMB_SIZE / 2, rItem.CenterPoint().x + MIMICSITEM_THUMB_SIZE / 2 + 1, rItem.CenterPoint().y + MIMICSITEM_THUMB_SIZE / 2 + 1), dx = point.x - rItem.CenterPoint().x, dy = rItem.CenterPoint().y - point.y; !rThumb.PtInRect(point) && dx != 0 && dy != 0; )
				{
					if (((fAngle = atan((double)dx / (double)dy)) >= -M_PI / 8.0  &&  fAngle < M_PI / 8.0) || (fAngle >= 7.0*M_PI / 8.0  &&  fAngle <= M_PI) || (fAngle <= -7.0*M_PI / 8.0  &&  fAngle >= -M_PI)) return m_hNSSizeCursor;
					if ((fAngle >= M_PI / 8.0  &&  fAngle < 3.0*M_PI / 8.0) || (fAngle <= -5.0*M_PI / 8.0  &&  fAngle > -7.0*M_PI / 8.0)) return m_hSWNESizeCursor;
					return(((fAngle >= 3.0*M_PI / 8.0  &&  fAngle < 5.0*M_PI / 8.0) || (fAngle <= -3.0*M_PI / 8.0  &&  fAngle > -5.0*M_PI / 8.0)) ? m_hWESizeCursor : m_hNWSESizeCursor);
				}
				if (!rThumb.PtInRect(point))
				{
					if (!dx) return m_hNSSizeCursor;
					if (!dy) return m_hWESizeCursor;
				}
				if (rItem.Width() > rThumb.Width()) return m_hNSSizeCursor;
				if (rItem.Height() > rThumb.Height()) return m_hWESizeCursor;
				return m_hWENSSizeCursor;
			}
			if (nCode == MIAC_SWTHUMB || nCode == MIAC_NWTHUMB || nCode == MIAC_NETHUMB || nCode == MIAC_SETHUMB) return m_hWENSSizeCursor;
		}
	}
	return((!IsDraggingItem()) ? ((nCode == MIAC_INSIDE || nCode == MIAC_DRAGTHUMB || nCode == MIAC_FIRSTTHUMB || nCode == MIAC_LASTTHUMB) ? ((nCode == MIAC_DRAGTHUMB || nCode == MIAC_FIRSTTHUMB || nCode == MIAC_LASTTHUMB) ? m_hWENSSizeCursor : m_hMoveCursor) : (HCURSOR)NULL) : GetCursor());
}

VOID CMMDImageView::StartDraggingOnRuler(UINT nCode, CONST POINT &point)
{
	m_nRulerDragCode = nCode;
	m_ptRulerDragPosition.x = point.x;
	m_ptRulerDragPosition.y = point.y;
	SetImageSize(CSize(GetImageSize().cx, GetImageSize().cy));
	UpdateAllItems();
	SetCapture();
}

UINT CMMDImageView::IsDraggingOnRuler() CONST
{
	return m_nRulerDragCode;
}

VOID CMMDImageView::StopDraggingOnRuler()
{
	m_nRulerDragCode = 0;
	m_ptRulerDragPosition.x = 0;
	m_ptRulerDragPosition.y = 0;
	ReleaseCapture();
}

BOOL CMMDImageView::DoItemDragging(CMimicsItem *pItem, CPoint point)
{
	UINT  nCode;

	if (HasSelectedItemsArea())
	{
		if (GetSelectedItemsArea().PtInRect(point))
		{
			nCode = MIAC_NOWHERE;
			return FALSE;
		}
	}
	if (SetFocusOnItem(pItem) == S_OK)
	{
		if ((nCode = pItem->CheckPointOnItem(point)) && HIBYTE(GetAsyncKeyState(VK_LBUTTON))) SetTimer(MMDIMAGEVIEW_TIMERID, GetDoubleClickTime(), NULL);
		return TRUE;
	}
	return FALSE;
}

VOID CMMDImageView::StartDraggingItem(UINT nCode, CONST POINT &point)
{
	CMimicsItem  *pItem;

	if ((pItem = GetActivatedItem()))
	{
		for (; pItem->GetItemRotateMode() && nCode != MIAC_SWTHUMB && nCode != MIAC_NWTHUMB && nCode != MIAC_NETHUMB && nCode != MIAC_SETHUMB && nCode != MIAC_FIRSTTHUMB && nCode != MIAC_LASTTHUMB; )
		{
			SetItemRotateMode(FALSE);
			break;
		}
		m_ptItemDragPosition = point;
		m_nItemDragCode = nCode;
		SetCaptureOnItem(pItem);
	}
}

UINT CMMDImageView::IsDraggingItem() CONST
{
	return m_nItemDragCode;
}

VOID CMMDImageView::StopDraggingItem()
{
	CMimicsItem  *pItem;

	if ((pItem = GetActivatedItem()))
	{
		ReleaseCaptureFromItem(pItem);
		m_ptItemDragPosition.x = 0;
		m_ptItemDragPosition.y = 0;
		m_nItemDragCode = 0;
	}
}

VOID CMMDImageView::StartSelectingItems(CONST POINT &point)
{
	m_ptItemSelectionPosition.x = 0;
	m_ptItemSelectionPosition.y = 0;
	m_sizeItemSelectionArea.cx = 0;
	m_sizeItemSelectionArea.cy = 0;
	m_rItemSelectionArea.SetRect(point.x, point.y, point.x, point.y);
	m_pSelectedItems.RemoveAll();
	m_bSelectionCode[0] = TRUE;
	UpdateAllItems();
	SetCapture();
}

BOOL CMMDImageView::IsSelectingItems() CONST
{
	return m_bSelectionCode[0];
}

VOID CMMDImageView::StopSelectingItems()
{
	CRect  rItem;
	CRect  rResult;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	if (IsSelectingItems())
	{
		for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL, m_pSelectedItems.RemoveAll(); lPosition; )
		{
			if ((pItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
			{
				rItem = pItem->GetItemPosition();
				rItem.NormalizeRect();
				rItem.InflateRect((!rItem.Width()) ? 1 : 0, 0);
				rItem.InflateRect(0, (!rItem.Height()) ? 1 : 0);
				if (rResult.IntersectRect(GetSelectedItemsArea(), rItem))
				{
					m_pSelectedItems.Add(pItem);
					continue;
				}
			}
		}
		if (m_pSelectedItems.GetSize() > 0)
		{
			m_bSelectionCode[0] = FALSE;
			ReleaseCapture();
			return;
		}
		m_bSelectionCode[0] = FALSE;
		ReleaseCapture();
	}
	m_ptItemSelectionPosition.x = 0;
	m_ptItemSelectionPosition.y = 0;
	m_sizeItemSelectionArea.cx = 0;
	m_sizeItemSelectionArea.cy = 0;
	m_rItemSelectionArea.SetRectEmpty();
	m_pSelectedItems.RemoveAll();
	UpdateAllItems();
}

BOOL CMMDImageView::StartDraggingSelectedItems(CONST POINT &point)
{
	if (HasSelectedItemsArea())
	{
		if (!GetSelectedItemsArea().PtInRect(point))
		{
			StopSelectingItems();
			return FALSE;
		}
		m_sizeItemSelectionArea = GetImageSize();
		m_ptItemSelectionPosition = point;
		m_bSelectionCode[1] = TRUE;
		SetCapture();
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDImageView::IsDraggingSelectedItems() CONST
{
	return m_bSelectionCode[1];
}

VOID CMMDImageView::StopDraggingSelectedItems()
{
	if (IsDraggingSelectedItems())
	{
		m_bSelectionCode[1] = FALSE;
		ReleaseCapture();
	}
}

BOOL CMMDImageView::HasSelectedItemsArea() CONST
{
	return !m_rItemSelectionArea.IsRectNull();
}

CRect CMMDImageView::GetSelectedItemsArea() CONST
{
	return m_rItemSelectionArea;
}

INT CMMDImageView::GetSelectedItemsAreaCount() CONST
{
	return((HasSelectedItemsArea()) ? (INT)m_pSelectedItems.GetSize() : 0);
}

VOID CMMDImageView::UpdateUndoList(BOOL bInitialize)
{
	m_cUndoList.Update(m_pDocument[0], bInitialize);
}

BOOL CMMDImageView::CopyToClipboard(CMimicsItem *pItem)
{
	LPBYTE  pData;
	HGLOBAL  hData;
	CByteArray  nItemData;
	CMimicsItem  *pMimicsItem;

	if (OpenClipboard())
	{
		if (EmptyClipboard())
		{
			if ((pMimicsItem = CMimicsItem::AllocateFromItem(pItem)))
			{
				if (pMimicsItem->Copy(pItem) && pMimicsItem->Map(nItemData))
				{
					if ((hData = GlobalAlloc(GHND, nItemData.GetSize())) != (HGLOBAL)NULL)
					{
						if ((pData = (LPBYTE)GlobalLock(hData)) != (LPBYTE)NULL)
						{
							CopyMemory(pData, nItemData.GetData(), nItemData.GetSize());
							SetClipboardData(m_nClipboardFormat, hData);
							GlobalUnlock(hData);
							delete pMimicsItem;
							CloseClipboard();
							return TRUE;
						}
						GlobalFree(hData);
					}
				}
				delete pMimicsItem;
			}
		}
		CloseClipboard();
	}
	return FALSE;
}

CMimicsItem *CMMDImageView::PasteFromClipboard()
{
	LPBYTE  pData;
	HGLOBAL  hData;
	CRect  rItem[2];
	CByteArray  nItemData;
	CMimicsItem  *pMimicsItem;
	COleDataObject  cOleDataObject;

	if (cOleDataObject.AttachClipboard())
	{
		if ((hData = cOleDataObject.GetGlobalData(m_nClipboardFormat)))
		{
			if ((pData = (LPBYTE)GlobalLock(hData)))
			{
				nItemData.SetSize(GlobalSize(hData));
				if (nItemData.GetSize() == GlobalSize(hData))
				{
					CopyMemory(nItemData.GetData(), pData, nItemData.GetSize());
					if ((pMimicsItem = CMimicsItem::AllocateFromData(nItemData)) && pMimicsItem->Unmap(nItemData))
					{
						rItem[0] = pMimicsItem->GetItemPosition();
						rItem[1] = pMimicsItem->CalcItemFramePosition();
						rItem[0].OffsetRect(-rItem[1].left, -rItem[1].top);
						rItem[0].OffsetRect(GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width() + 1, GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height() + 1);
						pMimicsItem->SetItemName(STRING(IDS_MMD_STATUSBAR_OBJECTDEFAULTNAME));
						pMimicsItem->SetItemPosition(rItem[0]);
						GlobalUnlock(hData);
						return pMimicsItem;
					}
					delete pMimicsItem;
				}
				GlobalUnlock(hData);
			}
		}
	}
	return((CMimicsItem *)NULL);
}

CSize CMMDImageView::CalcScrollSizes() CONST
{
	INT  nTop;
	INT  nLeft;
	INT  nRight;
	INT  nBottom;
	CRect  rView;
	CRect  rPosition;
	CSize  sizeScroll;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	if ((pDocument = GetDocument()))
	{
		for (lPosition = pDocument->GetStartPosition(), rView.SetRectEmpty(); lPosition; )
		{
			if ((pItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
			{
				rPosition = pItem->CalcItemFrameExtent();
				rView.SetRect(min(rPosition.left, rView.left), min(rPosition.top, rView.top), max(rPosition.right + 1, rView.right), max(rPosition.bottom + 1, rView.bottom));
			}
		}
		GetImageMargin(nLeft, nTop, nRight, nBottom);
		sizeScroll.cx = max((rView.right + nRight < m_sizeImage.cx) ? (rView.right + nRight) : rView.right, 0);
		sizeScroll.cy = max((rView.bottom + nBottom < m_sizeImage.cy) ? (rView.bottom + nBottom) : rView.bottom, 0);
		return CSize(max(CalcVerticalRulerPosition().Width() + m_sizeImage.cx, sizeScroll.cx), max(CalcHorizontalRulerPosition().Height() + m_sizeImage.cy, sizeScroll.cy));
	}
	return CSize(0, 0);
}

VOID CMMDImageView::UpdateZoomWindow()
{
	CZoomWnd  *pZoomWnd;

	if ((pZoomWnd = GetMainWnd()->GetZoomWindow()))
	{
		if (CThread::IsSameThread(this) && GetMainWnd()->MDIGetActive() == (CMDIChildWnd *)GetParentFrame())
		{
			pZoomWnd->Invalidate(FALSE);
			pZoomWnd->UpdateWindow();
			return;
		}
		if (!CThread::IsSameThread(this))
		{
			pZoomWnd->Invalidate(FALSE);
			return;
		}
	}
}

HRESULT CMMDImageView::DefWindowMessageProc(UINT nMessage, WPARAM wParam, LPARAM lParam, LRESULT *plResult)
{
	CONST MSG  *pMsg;

	if ((pMsg = GetCurrentMessage()))
	{
		if (pMsg->message == nMessage  &&  pMsg->wParam == wParam  &&  pMsg->lParam == lParam)
		{
			*plResult = Default();
			return S_OK;
		}
	}
	return E_FAIL;
}

LRESULT CMMDImageView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SETCURSOR:
	{ if (message == WM_SETCURSOR)
	{
		if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE))
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
			return TRUE;
		}
		break;
	}
	}
	case WM_SETFOCUS:
	{ if (message == WM_SETFOCUS)
	{
		if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE))
		{
			GetParent()->GetCodeView()->UnSelectAllCode();
			return FALSE;
		}
		break;
	}
	}
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_KEYDOWN:
	case WM_KEYUP:
	{ if (CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) || (message == WM_KEYDOWN  &&  wParam == VK_DOWN  &&  HIBYTE(GetAsyncKeyState(VK_CONTROL)))) break;
	return FALSE;
	}
	default: break;
	}
	return CScrollView::WindowProc(message, wParam, lParam);
}

BEGIN_MESSAGE_MAP(CMMDImageView, CScrollView)
	//{{AFX_MSG_MAP(CMMDImageView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDImageView drawing

void CMMDImageView::OnDraw(CDC *pDC)
{
	DrawImage(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMMDImageView message handlers

int CMMDImageView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	HCURSOR  hCursor[12];

	if (CScrollView::OnCreate(lpCreateStruct) != -1 && InstallMimicsCtrlInterface())
	{
		if ((hCursor[0] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_SIZEHORIZONTAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
		{
			if ((hCursor[1] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_SIZEVERTICAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
			{
				if ((hCursor[2] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_MIMICSITEMDEFAULT), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
				{
					if ((hCursor[3] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_MIMICSITEMPOINT), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
					{
						if ((hCursor[4] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_MIMICSITEMMOVE), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
						{
							if ((hCursor[5] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_MIMICSITEMSELECT), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
							{
								if ((hCursor[6] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_MIMICSITEMSIZEHORIZONTAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
								{
									if ((hCursor[7] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_MIMICSITEMSIZEVERTICAL), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
									{
										if ((hCursor[8] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_MIMICSITEMSIZEALLDIRECTIONS), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
										{
											if ((hCursor[9] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_MIMICSITEMSIZEDIAGONALUP), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
											{
												if ((hCursor[10] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_MIMICSITEMSIZEDIAGONALDOWN), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
												{
													if ((hCursor[11] = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_MIMICSITEMTURN), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR | LR_DEFAULTSIZE)))
													{
														if ((m_pDocument[0] = new CMMDDocument))
														{
															if ((m_pDocument[1] = new CMMDDocument))
															{
																SetScrollSizes(MM_TEXT, CSize(0, 0));
																m_hHorzSizeCursor = hCursor[0];
																m_hVertSizeCursor = hCursor[1];
																m_hDefaultCursor = hCursor[2];
																m_hPointCursor = hCursor[3];
																m_hMoveCursor = hCursor[4];
																m_hSelectCursor = hCursor[5];
																m_hWESizeCursor = hCursor[6];
																m_hNSSizeCursor = hCursor[7];
																m_hWENSSizeCursor = hCursor[8];
																m_hSWNESizeCursor = hCursor[9];
																m_hNWSESizeCursor = hCursor[10];
																m_hRotateCursor = hCursor[11];
																return 0;
															}
															delete m_pDocument[0];
															m_pDocument[0] = (CMMDDocument *)NULL;
														}
														DestroyCursor(hCursor[11]);
													}
													DestroyCursor(hCursor[10]);
												}
												DestroyCursor(hCursor[9]);
											}
											DestroyCursor(hCursor[8]);
										}
										DestroyCursor(hCursor[7]);
									}
									DestroyCursor(hCursor[6]);
								}
								DestroyCursor(hCursor[5]);
							}
							DestroyCursor(hCursor[4]);
						}
						DestroyCursor(hCursor[3]);
					}
					DestroyCursor(hCursor[2]);
				}
				DestroyCursor(hCursor[1]);
			}
			DestroyCursor(hCursor[0]);
		}
	}
	return -1;
}

BOOL CMMDImageView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll)
{
	CRect  rHotSpot;
	CSize  sizeSpot;
	CMMDWnd  *pMMDWnd;
	SCROLLINFO  sScrollInfo[2];

	GetScrollInfo(SB_HORZ, &sScrollInfo[0]);
	GetScrollInfo(SB_VERT, &sScrollInfo[1]);
	if (((sizeScroll.cx > 0 && sScrollInfo[0].nPos <= (INT)(sScrollInfo[0].nMax - sScrollInfo[0].nPage)) || (sizeScroll.cx < 0 && sScrollInfo[0].nPos > 0) || !sizeScroll.cx) && ((sizeScroll.cy > 0 && sScrollInfo[1].nPos <= (INT)(sScrollInfo[1].nMax - sScrollInfo[1].nPage)) || (sizeScroll.cy < 0 && sScrollInfo[1].nPos > 0) || !sizeScroll.cy) && (sizeScroll.cx != 0 || sizeScroll.cy != 0))
	{
		if ((pMMDWnd = GetParent()->GetParent()))
		{
			rHotSpot = pMMDWnd->GetHotSpot();
			sizeSpot.cx = (sScrollInfo[0].nPos + sizeScroll.cx < 0) ? -sScrollInfo[0].nPos : sizeScroll.cx;
			sizeSpot.cy = (sScrollInfo[1].nPos + sizeScroll.cy < 0) ? -sScrollInfo[1].nPos : sizeScroll.cy;
			sizeSpot.cx = (sScrollInfo[0].nPos + sizeScroll.cx >(INT) (sScrollInfo[0].nMax - sScrollInfo[0].nPage)) ? (INT)(sScrollInfo[0].nMax - sScrollInfo[0].nPage - sScrollInfo[0].nPos + 1) : sizeSpot.cx;
			sizeSpot.cy = (sScrollInfo[1].nPos + sizeScroll.cy >(INT) (sScrollInfo[1].nMax - sScrollInfo[1].nPage)) ? (INT)(sScrollInfo[1].nMax - sScrollInfo[1].nPage - sScrollInfo[1].nPos + 1) : sizeSpot.cy;
			rHotSpot.OffsetRect((!rHotSpot.IsRectEmpty()) ? sizeSpot.cx : 0, 0);
			rHotSpot.OffsetRect(0, (!rHotSpot.IsRectEmpty()) ? sizeSpot.cy : 0);
			pMMDWnd->SetHotSpot(rHotSpot);
		}
		Invalidate(FALSE);
	}
	return CScrollView::OnScrollBy(sizeScroll, bDoScroll);
}

BOOL CMMDImageView::OnEraseBkgnd(CDC *pDC)
{
	UpdateWindow();
	return TRUE;
}

void CMMDImageView::OnPaint()
{
	UpdateZoomWindow();
	CScrollView::OnPaint();
}

void CMMDImageView::OnSetFocus(CWnd *pOldWnd)
{
	CWnd  *pWnd;
	CMimicsItem  *pItem;

	if ((pItem = GetActivatedItem()))
	{
		if (pItem->GetItemState() == COleClientItem::activeUIState)
		{
			if ((pWnd = pItem->GetInPlaceWindow()) != (CWnd *)NULL)
			{
				GetParent()->GetCodeView()->UnSelectAllCode();
				pWnd->SetFocus();
				return;
			}
		}
	}
	GetParent()->GetCodeView()->UnSelectAllCode();
	CScrollView::OnSetFocus(pOldWnd);
}

BOOL CMMDImageView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	INT  nTop;
	INT  nLeft;
	INT  nRight;
	INT  nBottom;
	CRect  rView;
	POINT  ptThumb[3];
	POINT  ptPosition;
	HCURSOR  hItemCursor;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	GetClientRect(rView);
	rView.OffsetRect(GetScrollPos(SB_HORZ), 0);
	rView.OffsetRect(0, GetScrollPos(SB_VERT));
	rView.DeflateRect(CalcVerticalRulerPosition().Width(), 0, 0, 0);
	rView.DeflateRect(0, CalcHorizontalRulerPosition().Height(), 0, 0);
	GetImageMargin(nLeft, nTop, nRight, nBottom);
	ptPosition.x = GetCurrentMessage()->pt.x;
	ptPosition.y = GetCurrentMessage()->pt.y;
	ptPosition.x += GetScrollPos(SB_HORZ);
	ptPosition.y += GetScrollPos(SB_VERT);
	ScreenToClient(&ptPosition);
	if (rView.PtInRect(ptPosition))
	{
		if (GetSelectedItemID() != (UINT)-1)
		{
			SetCursor(m_hPointCursor);
			return TRUE;
		}
		if (HasSelectedItemsArea())
		{
			if (GetSelectedItemsArea().PtInRect(ptPosition))
			{
				SetCursor(m_hSelectCursor);
				return TRUE;
			}
		}
		if ((pItem = GetActivatedItem()))
		{
			if ((hItemCursor = DetermineItemCursor(pItem, ptPosition)))
			{
				SetCursor(hItemCursor);
				return TRUE;
			}
		}
		for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStopPosition() : (POSITION)NULL; lPosition; )
		{
			if ((pItem = (CMimicsItem *)pDocument->GetPreviousItem(lPosition)) && !pItem->IsItemActivated(TRUE))
			{
				if ((hItemCursor = DetermineItemCursor(pItem, ptPosition)))
				{
					SetCursor(hItemCursor);
					return TRUE;
				}
			}
		}
	}
	if ((CalcHorizontalRulerOuterThumbPosition(CalcHorizontalRulerPosition(), ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb)) || (CalcHorizontalRulerInnerRightThumbPosition(CalcHorizontalRulerPosition(), nRight, ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb)) || (GetImageSize().cx > 0 && GetImageSize().cy > 0 && CalcHorizontalRulerInnerLeftThumbPosition(CalcHorizontalRulerPosition(), nLeft, ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb)))
	{
		SetCursor(m_hHorzSizeCursor);
		return TRUE;
	}
	if ((CalcVerticalRulerOuterThumbPosition(CalcVerticalRulerPosition(), ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb)) || (CalcVerticalRulerInnerBottomThumbPosition(CalcVerticalRulerPosition(), nBottom, ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb)) || (GetImageSize().cx > 0 && GetImageSize().cy > 0 && CalcVerticalRulerInnerTopThumbPosition(CalcVerticalRulerPosition(), nTop, ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb)))
	{
		SetCursor(m_hVertSizeCursor);
		return TRUE;
	}
	SetCursor(m_hDefaultCursor);
	return TRUE;
}

void CMMDImageView::OnMouseMove(UINT nFlags, CPoint point)
{
	INT  dx;
	INT  dy;
	INT  ix;
	INT  iy;
	INT  nTop;
	INT  nLeft;
	INT  nRight;
	INT  nBottom;
	INT  nItem;
	INT  nItems;
	CRect  rView;
	CRect  rArea;
	CRect  rItem[2];
	CSize  sizeView;
	CSize  sizeImage;
	double  fAngle[3];
	CPoint  ptItem[4];
	CPoint  ptPosition;
	HCURSOR  hItemCursor;
	CMimicsItem  *pItem;

	if ((pItem = GetActivatedItem()))
	{
		if (IsDraggingItem())
		{
			GetClientRect(rView);
			ptPosition = point;
			ptPosition.x += GetScrollPos(SB_HORZ);
			ptPosition.y += GetScrollPos(SB_VERT);
			rItem[0] = pItem->GetItemPosition();
			if (pItem->GetItemRotateMode())
			{
				fAngle[0] = (m_ptItemDragPosition.x == rItem[0].CenterPoint().x  &&  m_ptItemDragPosition.y == rItem[0].CenterPoint().y) ? 0.0 : 0.0;
				fAngle[0] = (m_ptItemDragPosition.x == rItem[0].CenterPoint().x  &&  m_ptItemDragPosition.y < rItem[0].CenterPoint().y) ? (M_PI / 2.0) : fAngle[0];
				fAngle[0] = (m_ptItemDragPosition.x == rItem[0].CenterPoint().x  &&  m_ptItemDragPosition.y > rItem[0].CenterPoint().y) ? ((3.0*M_PI) / 2.0) : fAngle[0];
				fAngle[0] = (m_ptItemDragPosition.x > rItem[0].CenterPoint().x  &&  m_ptItemDragPosition.y == rItem[0].CenterPoint().y) ? 0.0 : fAngle[0];
				fAngle[0] = (m_ptItemDragPosition.x < rItem[0].CenterPoint().x  &&  m_ptItemDragPosition.y == rItem[0].CenterPoint().y) ? M_PI : fAngle[0];
				fAngle[0] = (m_ptItemDragPosition.x > rItem[0].CenterPoint().x  &&  m_ptItemDragPosition.y < rItem[0].CenterPoint().y) ? atan((double)(rItem[0].CenterPoint().y - m_ptItemDragPosition.y) / (double)(m_ptItemDragPosition.x - rItem[0].CenterPoint().x)) : fAngle[0];
				fAngle[0] = (m_ptItemDragPosition.x < rItem[0].CenterPoint().x  &&  m_ptItemDragPosition.y < rItem[0].CenterPoint().y) ? (M_PI - atan((double)(rItem[0].CenterPoint().y - m_ptItemDragPosition.y) / (double)(rItem[0].CenterPoint().x - m_ptItemDragPosition.x))) : fAngle[0];
				fAngle[0] = (m_ptItemDragPosition.x < rItem[0].CenterPoint().x  &&  m_ptItemDragPosition.y > rItem[0].CenterPoint().y) ? (M_PI + atan((double)(m_ptItemDragPosition.y - rItem[0].CenterPoint().y) / (double)(rItem[0].CenterPoint().x - m_ptItemDragPosition.x))) : fAngle[0];
				fAngle[0] = (m_ptItemDragPosition.x > rItem[0].CenterPoint().x  &&  m_ptItemDragPosition.y > rItem[0].CenterPoint().y) ? (2.0*M_PI - atan((double)(m_ptItemDragPosition.y - rItem[0].CenterPoint().y) / (double)(m_ptItemDragPosition.x - rItem[0].CenterPoint().x))) : fAngle[0];
				fAngle[1] = (ptPosition.x == rItem[0].CenterPoint().x  &&  ptPosition.y == rItem[0].CenterPoint().y) ? 0.0 : 0.0;
				fAngle[1] = (ptPosition.x == rItem[0].CenterPoint().x  &&  ptPosition.y < rItem[0].CenterPoint().y) ? (M_PI / 2.0) : fAngle[1];
				fAngle[1] = (ptPosition.x == rItem[0].CenterPoint().x  &&  ptPosition.y > rItem[0].CenterPoint().y) ? ((3.0*M_PI) / 2.0) : fAngle[1];
				fAngle[1] = (ptPosition.x > rItem[0].CenterPoint().x  &&  ptPosition.y == rItem[0].CenterPoint().y) ? 0.0 : fAngle[1];
				fAngle[1] = (ptPosition.x < rItem[0].CenterPoint().x  &&  ptPosition.y == rItem[0].CenterPoint().y) ? M_PI : fAngle[1];
				fAngle[1] = (ptPosition.x > rItem[0].CenterPoint().x  &&  ptPosition.y < rItem[0].CenterPoint().y) ? atan((double)(rItem[0].CenterPoint().y - ptPosition.y) / (double)(ptPosition.x - rItem[0].CenterPoint().x)) : fAngle[1];
				fAngle[1] = (ptPosition.x < rItem[0].CenterPoint().x  &&  ptPosition.y < rItem[0].CenterPoint().y) ? (M_PI - atan((double)(rItem[0].CenterPoint().y - ptPosition.y) / (double)(rItem[0].CenterPoint().x - ptPosition.x))) : fAngle[1];
				fAngle[1] = (ptPosition.x < rItem[0].CenterPoint().x  &&  ptPosition.y > rItem[0].CenterPoint().y) ? (M_PI + atan((double)(ptPosition.y - rItem[0].CenterPoint().y) / (double)(rItem[0].CenterPoint().x - ptPosition.x))) : fAngle[1];
				fAngle[1] = (ptPosition.x > rItem[0].CenterPoint().x  &&  ptPosition.y > rItem[0].CenterPoint().y) ? (2.0*M_PI - atan((double)(ptPosition.y - rItem[0].CenterPoint().y) / (double)(ptPosition.x - rItem[0].CenterPoint().x))) : fAngle[1];
				fAngle[2] = (360.0*(fAngle[1] - fAngle[0])) / (2.0*M_PI);
				m_ptItemDragPosition = ptPosition;
				pItem->RotateItem(fAngle[2]);
			}
			else
			{
				for (ptItem[0] = pItem->CalcTransform(rItem[0].TopLeft()), ptItem[1] = pItem->CalcTransform(CPoint(rItem[0].right, rItem[0].top)), ptItem[2] = pItem->CalcTransform(rItem[0].BottomRight()), ptItem[3] = pItem->CalcTransform(CPoint(rItem[0].left, rItem[0].bottom)), dx = ptPosition.x - m_ptItemDragPosition.x, dy = ptPosition.y - m_ptItemDragPosition.y, ix = iy = 0; ptItem[0].x > ptItem[1].x;)
				{
					dx = -dx;
					ix = 1;
					break;
				}
				if (ptItem[0].y > ptItem[2].y)
				{
					dy = -dy;
					iy = 1;
				}
				if (IsDraggingItem() == MIAC_SWTHUMB)
				{
					pItem->SetItemPosition(CRect(min(rItem[0].left + (1 - ix)*dx, rItem[0].right), min(rItem[0].top - iy*dy, rItem[0].bottom), max(rItem[0].right - ix*dx, rItem[0].left), max(rItem[0].bottom + (1 - iy)*dy, rItem[0].top)));
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_WTHUMB)
				{
					pItem->SetItemPosition(CRect(min(rItem[0].left + (1 - ix)*dx, rItem[0].right), rItem[0].top, max(rItem[0].right - ix*dx, rItem[0].left), rItem[0].bottom));
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_NWTHUMB)
				{
					pItem->SetItemPosition(CRect(min(rItem[0].left + (1 - ix)*dx, rItem[0].right), min(rItem[0].top + (1 - iy)*dy, rItem[0].bottom), max(rItem[0].right - ix*dx, rItem[0].top), max(rItem[0].bottom - iy*dy, rItem[0].top)));
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_NTHUMB)
				{
					pItem->SetItemPosition(CRect(rItem[0].left, min(rItem[0].top + (1 - iy)*dy, rItem[0].bottom), rItem[0].right, max(rItem[0].bottom - iy*dy, rItem[0].top)));
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_NETHUMB)
				{
					pItem->SetItemPosition(CRect(min(rItem[0].left - ix*dx, rItem[0].right), min(rItem[0].top + (1 - iy)*dy, rItem[0].bottom), max(rItem[0].right + (1 - ix)*dx, rItem[0].left), max(rItem[0].bottom - iy*dy, rItem[0].top)));
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_ETHUMB)
				{
					pItem->SetItemPosition(CRect(min(rItem[0].left - ix*dx, rItem[0].right), rItem[0].top, max(rItem[0].right + (1 - ix)*dx, rItem[0].left), rItem[0].bottom));
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_SETHUMB)
				{
					pItem->SetItemPosition(CRect(min(rItem[0].left - ix*dx, rItem[0].right), min(rItem[0].top - iy*dy, rItem[0].bottom), max(rItem[0].right + (1 - ix)*dx, rItem[0].left), max(rItem[0].bottom + (1 - iy)*dy, rItem[0].top)));
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_STHUMB)
				{
					pItem->SetItemPosition(CRect(rItem[0].left, min(rItem[0].top - iy*dy, rItem[0].bottom), rItem[0].right, max(rItem[0].bottom + (1 - iy)*dy, rItem[0].top)));
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_INSIDE)
				{
					ptItem[1] = (pItem->CheckPointOnItem(ptItem[1]) != MIAC_NOWHERE) ? ptItem[1] : ptItem[2];
					ptItem[3] = (pItem->CheckPointOnItem(ptItem[3]) != MIAC_NOWHERE) ? ptItem[3] : ptItem[0];
					rItem[1].SetRect(rItem[0].left + ptPosition.x - m_ptItemDragPosition.x, rItem[0].top + ptPosition.y - m_ptItemDragPosition.y, rItem[0].right + ptPosition.x - m_ptItemDragPosition.x, rItem[0].bottom + ptPosition.y - m_ptItemDragPosition.y);
					rItem[1].OffsetRect((max(rItem[1].left, rItem[1].right) + max(max(max(ptItem[0].x, ptItem[1].x), ptItem[2].x), ptItem[3].x) - max(rItem[0].left, rItem[0].right) < GetImageOrigin().x) ? (GetImageOrigin().x - (max(rItem[1].left, rItem[1].right) + max(max(max(ptItem[0].x, ptItem[1].x), ptItem[2].x), ptItem[3].x) - max(rItem[0].left, rItem[0].right))) : 0, 0);
					rItem[1].OffsetRect(0, (max(rItem[1].top, rItem[1].bottom) + max(max(max(ptItem[0].y, ptItem[1].y), ptItem[2].y), ptItem[3].y) - max(rItem[0].top, rItem[0].bottom) < GetImageOrigin().y) ? (GetImageOrigin().y - (max(rItem[1].top, rItem[1].bottom) + max(max(max(ptItem[0].y, ptItem[1].y), ptItem[2].y), ptItem[3].y) - max(rItem[0].top, rItem[0].bottom))) : 0);
					m_ptItemDragPosition.x += rItem[1].CenterPoint().x - rItem[0].CenterPoint().x;
					m_ptItemDragPosition.y += rItem[1].CenterPoint().y - rItem[0].CenterPoint().y;
					pItem->SetItemPosition(rItem[1]);
				}
				if (IsDraggingItem() == MIAC_DRAGTHUMB)
				{
					pItem->DragItem(IsDraggingItem(), ptPosition, m_ptItemDragPosition);
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_FIRSTTHUMB)
				{
					pItem->SetItemPosition(CRect(rItem[0].left + (1 - ix)*dx, rItem[0].top, rItem[0].right, rItem[0].bottom));
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_LASTTHUMB)
				{
					pItem->SetItemPosition(CRect(rItem[0].left, rItem[0].top, rItem[0].right + (1 - ix)*dx, rItem[0].bottom));
					m_ptItemDragPosition = ptPosition;
				}
				if (IsDraggingItem() == MIAC_FIRSTRADIALTHUMB || IsDraggingItem() == MIAC_LASTRADIALTHUMB)
				{
					pItem->DragItem(IsDraggingItem(), ptPosition, m_ptItemDragPosition);
					m_ptItemDragPosition = ptPosition;
				}
			}
			SetCursor(((hItemCursor = DetermineItemCursor(pItem, ptPosition))) ? hItemCursor : GetCursor());
			UpdateAllItems();
		}
	}
	if (IsSelectingItems())
	{
		ptPosition.x = max(point.x + GetScrollPos(SB_HORZ), m_rItemSelectionArea.left);
		ptPosition.y = max(point.y + GetScrollPos(SB_VERT), m_rItemSelectionArea.top);
		m_rItemSelectionArea.right = ptPosition.x;
		m_rItemSelectionArea.bottom = ptPosition.y;
		SetCursor(m_hSelectCursor);
		UpdateAllItems();
	}
	if (IsDraggingSelectedItems())
	{
		GetClientRect(rView);
		ptPosition.x = point.x;
		ptPosition.y = point.y;
		ptPosition.x += GetScrollPos(SB_HORZ);
		ptPosition.y += GetScrollPos(SB_VERT);
		dx = ptPosition.x - m_ptItemSelectionPosition.x;
		dy = ptPosition.y - m_ptItemSelectionPosition.y;
		if (m_rItemSelectionArea.left + dx >= max(GetTotalSize().cx, rView.Width()) - 1) dx = max(GetTotalSize().cx, rView.Width()) - m_rItemSelectionArea.left - 1;
		if (m_rItemSelectionArea.top + dy >= max(GetTotalSize().cy, rView.Height()) - 1) dy = max(GetTotalSize().cy, rView.Height()) - m_rItemSelectionArea.top - 1;
		if (m_rItemSelectionArea.right + dx <= GetImageOrigin().x + 1) dx = GetImageOrigin().x - m_rItemSelectionArea.right + 1;
		if (m_rItemSelectionArea.bottom + dy <= GetImageOrigin().y + 1) dy = GetImageOrigin().y - m_rItemSelectionArea.bottom + 1;
		if (dx != 0) m_ptItemSelectionPosition.x += dx;
		if (dy != 0) m_ptItemSelectionPosition.y += dy;
		for (nItem = 0, nItems = (dx != 0 || dy != 0) ? (INT)m_pSelectedItems.GetSize() : 0; nItem < nItems; nItem++)
		{
			if ((pItem = (CMimicsItem *)m_pSelectedItems.GetAt(nItem)))
			{
				rItem[0] = pItem->GetItemPosition();
				rItem[0].OffsetRect(dx, dy);
				pItem->AdjustItemPosition(rItem[0]);
			}
		}
		m_rItemSelectionArea.OffsetRect(dx, dy);
		SetCursor(m_hSelectCursor);
		UpdateAllItems();
	}
	if (IsDraggingOnRuler())
	{
		GetClientRect(rView);
		sizeImage = GetImageSize();
		sizeView.cx = rView.Width();
		sizeView.cy = rView.Height();
		GetImageMargin(nLeft, nTop, nRight, nBottom);
		ptPosition.x = point.x + GetScrollPos(SB_HORZ);
		ptPosition.y = point.y + GetScrollPos(SB_VERT);
		dx = ptPosition.x - m_ptRulerDragPosition.x;
		dy = ptPosition.y - m_ptRulerDragPosition.y;
		switch (IsDraggingOnRuler())
		{
		case MMDIMAGEVIEW_DRAG_HORIZONTAL | MMDIMAGEVIEW_DRAG_OUTERMARGIN:
		{ m_ptRulerDragPosition.x = max(ptPosition.x, GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width() + nLeft + nRight + 1);
		sizeImage.cx = max(sizeImage.cx + dx, nLeft + nRight + 1);
		SetImageSize(sizeImage);
		SetCursor(m_hHorzSizeCursor);
		UpdateAllItems();
		break;
		}
		case MMDIMAGEVIEW_DRAG_HORIZONTAL | MMDIMAGEVIEW_DRAG_INNERMARGIN | MMDIMAGEVIEW_DRAG_LEFT:
		{ m_ptRulerDragPosition.x = max(ptPosition.x, GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width());
		m_ptRulerDragPosition.x = min(GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width() + sizeImage.cx - nRight - 1, m_ptRulerDragPosition.x);
		SetImageMargin(min(max(nLeft + dx, 0), sizeImage.cx - nRight - 1), nTop, nRight, nBottom);
		SetImageSize(sizeImage);
		SetCursor(m_hHorzSizeCursor);
		UpdateAllItems();
		break;
		}
		case MMDIMAGEVIEW_DRAG_HORIZONTAL | MMDIMAGEVIEW_DRAG_INNERMARGIN | MMDIMAGEVIEW_DRAG_RIGHT:
		{ m_ptRulerDragPosition.x = max(ptPosition.x, GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width() + nLeft + 1);
		m_ptRulerDragPosition.x = min(GetScrollPos(SB_HORZ) + CalcVerticalRulerPosition().Width() + sizeImage.cx, m_ptRulerDragPosition.x);
		SetImageMargin(nLeft, nTop, min(max(nRight - dx, 0), sizeImage.cx - nLeft - 1), nBottom);
		SetImageSize(sizeImage);
		SetCursor(m_hHorzSizeCursor);
		UpdateAllItems();
		break;
		}
		case MMDIMAGEVIEW_DRAG_VERTICAL | MMDIMAGEVIEW_DRAG_OUTERMARGIN:
		{ m_ptRulerDragPosition.y = max(ptPosition.y, GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height() + nTop + nBottom + 1);
		sizeImage.cy = max(sizeImage.cy + dy, nTop + nBottom + 1);
		SetImageSize(sizeImage);
		SetCursor(m_hVertSizeCursor);
		UpdateAllItems();
		break;
		}
		case MMDIMAGEVIEW_DRAG_VERTICAL | MMDIMAGEVIEW_DRAG_INNERMARGIN | MMDIMAGEVIEW_DRAG_TOP:
		{ m_ptRulerDragPosition.y = max(ptPosition.y, GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height());
		m_ptRulerDragPosition.y = min(GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height() + sizeImage.cy - nBottom - 1, m_ptRulerDragPosition.y);
		SetImageMargin(nLeft, min(max(nTop + dy, 0), sizeImage.cy - nBottom - 1), nRight, nBottom);
		SetImageSize(sizeImage);
		SetCursor(m_hVertSizeCursor);
		UpdateAllItems();
		break;
		}
		case MMDIMAGEVIEW_DRAG_VERTICAL | MMDIMAGEVIEW_DRAG_INNERMARGIN | MMDIMAGEVIEW_DRAG_BOTTOM:
		{ m_ptRulerDragPosition.y = max(ptPosition.y, GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height() + nTop + 1);
		m_ptRulerDragPosition.y = min(GetScrollPos(SB_VERT) + CalcHorizontalRulerPosition().Height() + sizeImage.cy, m_ptRulerDragPosition.y);
		SetImageMargin(nLeft, nTop, nRight, min(max(nBottom - dy, 0), sizeImage.cy - nTop - 1));
		SetImageSize(sizeImage);
		SetCursor(m_hVertSizeCursor);
		UpdateAllItems();
		break;
		}
		}
	}
	CScrollView::OnMouseMove(nFlags, point);
}

void CMMDImageView::OnLButtonDown(UINT nFlags, CPoint point)
{
	INT  nTop;
	INT  nLeft;
	INT  nRight;
	INT  nBottom;
	UINT  nCode;
	BOOL  bShift;
	CRect  rView;
	POINT  ptThumb[3];
	CPoint  ptPosition;
	POSITION  lPosition;
	CMimicsItem  *pItem[2];
	CMMDDocument  *pDocument;

	GetClientRect(rView), GetImageMargin(nLeft, nTop, nRight, nBottom);
	rView.OffsetRect(GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT));
	rView.DeflateRect(CalcVerticalRulerPosition().Width(), 0, 0, 0);
	rView.DeflateRect(0, CalcHorizontalRulerPosition().Height(), 0, 0);
	ptPosition.x = point.x + GetScrollPos(SB_HORZ);
	ptPosition.y = point.y + GetScrollPos(SB_VERT);
	if (rView.PtInRect(ptPosition) && GetSelectedItemID() == (UINT)-1)
	{
		for (nCode = MIAC_NOWHERE, bShift = (HIBYTE(GetAsyncKeyState(VK_SHIFT))) ? TRUE : FALSE; (pItem[0] = GetActivatedItem()) && !bShift; )
		{
			if ((nCode = pItem[0]->CheckPointOnItem(ptPosition)))
			{
				if (!DoItemDragging(pItem[0], ptPosition))
				{
					nCode = MIAC_NOWHERE;
					break;
				}
			}
			break;
		}
		for (lPosition = ((pDocument = GetDocument())) ? ((nCode == MIAC_NOWHERE) ? pDocument->GetStopPosition() : (POSITION)NULL) : (POSITION)NULL; lPosition; )
		{
			if ((pItem[0] = (CMimicsItem *)pDocument->GetPreviousItem(lPosition)))
			{
				if ((nCode = pItem[0]->CheckPointOnItem(ptPosition)))
				{
					if (bShift  &&  !SelectItem(pItem[0]))
					{
						nCode = MIAC_NOWHERE;
						break;
					}
					if (!bShift)
					{
						if (!DoItemDragging(pItem[0], ptPosition))
						{
							nCode = MIAC_NOWHERE;
							break;
						}
					}
					break;
				}
			}
		}
		if (nCode == MIAC_NOWHERE)
		{
			for (SetActivatedItem(); bShift; )
			{
				StartSelectingItems(ptPosition);
				break;
			}
			for (; !bShift; )
			{
				if (!StartDraggingSelectedItems(ptPosition)) StopSelectingItems();
				break;
			}
		}
	}
	if (rView.PtInRect(ptPosition))
	{
		if ((pItem[0] = AddItem(GetSelectedItemID(), ptPosition)))
		{
			DoItemDragging(pItem[0], ptPosition);
			UpdateAllItems();
		}
	}
	if (CalcHorizontalRulerOuterThumbPosition(CalcHorizontalRulerPosition(), ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb)) StartDraggingOnRuler(MMDIMAGEVIEW_DRAG_HORIZONTAL | MMDIMAGEVIEW_DRAG_OUTERMARGIN, ptPosition);
	if (CalcHorizontalRulerInnerRightThumbPosition(CalcHorizontalRulerPosition(), nRight, ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb)) StartDraggingOnRuler(MMDIMAGEVIEW_DRAG_HORIZONTAL | MMDIMAGEVIEW_DRAG_INNERMARGIN | MMDIMAGEVIEW_DRAG_RIGHT, ptPosition);
	if (CalcHorizontalRulerInnerLeftThumbPosition(CalcHorizontalRulerPosition(), nLeft, ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb) && GetImageSize().cx > 0 && GetImageSize().cy > 0) StartDraggingOnRuler(MMDIMAGEVIEW_DRAG_HORIZONTAL | MMDIMAGEVIEW_DRAG_INNERMARGIN | MMDIMAGEVIEW_DRAG_LEFT, ptPosition);
	if (CalcVerticalRulerOuterThumbPosition(CalcVerticalRulerPosition(), ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb)) StartDraggingOnRuler(MMDIMAGEVIEW_DRAG_VERTICAL | MMDIMAGEVIEW_DRAG_OUTERMARGIN, ptPosition);
	if (CalcVerticalRulerInnerBottomThumbPosition(CalcVerticalRulerPosition(), nBottom, ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb)) StartDraggingOnRuler(MMDIMAGEVIEW_DRAG_VERTICAL | MMDIMAGEVIEW_DRAG_INNERMARGIN | MMDIMAGEVIEW_DRAG_BOTTOM, ptPosition);
	if (CalcVerticalRulerInnerTopThumbPosition(CalcVerticalRulerPosition(), nTop, ptThumb, sizeof(ptThumb) / sizeof(POINT)) && IsPointOnRulerThumb(ptPosition, ptThumb) && GetImageSize().cx > 0 && GetImageSize().cy > 0) StartDraggingOnRuler(MMDIMAGEVIEW_DRAG_VERTICAL | MMDIMAGEVIEW_DRAG_INNERMARGIN | MMDIMAGEVIEW_DRAG_TOP, ptPosition);
	CScrollView::OnLButtonDown(nFlags, point);
}

void CMMDImageView::OnLButtonUp(UINT nFlags, CPoint point)
{
	for (; IsDraggingItem(); )
	{
		StopDraggingItem();
		break;
	}
	for (; IsSelectingItems(); )
	{
		StopSelectingItems();
		break;
	}
	for (; IsDraggingSelectedItems(); )
	{
		StopDraggingSelectedItems();
		break;
	}
	for (; IsDraggingOnRuler(); )
	{
		StopDraggingOnRuler();
		break;
	}
	UpdateUndoList();
	UpdateAllItems();
	CScrollView::OnLButtonUp(nFlags, point);
}

void CMMDImageView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CSize  sizeImage;
	CPoint  ptPosition;
	CMimicsItem  *pItem;

	for (ptPosition = point, ptPosition.x += GetScrollPos(SB_HORZ), ptPosition.y += GetScrollPos(SB_VERT); (pItem = GetActivatedItem()) && !IsDraggingItem() && pItem->CheckPointOnItem(ptPosition) == MIAC_INSIDE; )
	{
		pItem->ActivateItem(OLEIVERB_PROPERTIES, this);
		UpdateAllItems(pItem);
		break;
	}
	if ((sizeImage = GetImageSize()).cx > 0 && sizeImage.cy > 0)
	{
		if (CalcHorizontalRulerPosition().PtInRect(ptPosition))
		{
			SetImageSize(CSize(0, 0));
			SetImageMargin(0, 0, 0, 0);
			UpdateAllItems();
		}
		if (CalcVerticalRulerPosition().PtInRect(ptPosition))
		{
			SetImageSize(CSize(0, 0));
			SetImageMargin(0, 0, 0, 0);
			UpdateAllItems();
		}
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CMMDImageView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMenu  cMenu;
	CPoint  ptMenu;
	CPoint  ptPosition;
	POSITION  lPosition;
	CMimicsItem  *pItem[2];
	CMMDDocument  *pDocument;
	CMFCPopupMenu  *pFloatingMenu;

	for (pItem[0] = GetActivatedItem(), pItem[1] = (CMimicsItem *)NULL, ptPosition = point, ptPosition.Offset(GetScrollPos(SB_HORZ), GetScrollPos(SB_VERT)); pItem[0] != (CMimicsItem *)NULL; )
	{
		if (pItem[0]->CheckPointOnItem(ptPosition) != MIAC_NOWHERE) pItem[1] = pItem[0];
		break;
	}
	for (lPosition = ((pDocument = GetDocument()) && !pItem[1]) ? pDocument->GetStopPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem[0] = (CMimicsItem *)pDocument->GetPreviousItem(lPosition)))
		{
			if (pItem[0]->CheckPointOnItem(ptPosition) != MIAC_NOWHERE)
			{
				SetActivatedItem((pItem[1] = pItem[0]));
				break;
			}
		}
	}
	if (pItem[1] != (CMimicsItem *)NULL)
	{
		for (ClientToScreen(&(ptMenu = point)); (pFloatingMenu = (cMenu.CreatePopupMenu() && cMenu.AppendMenu(MF_STRING, IDM_VIEW_MIMICSOBJECTPROPERTIES, STRING(IDS_MMD_FLOATINGMENU_PROPERTIES)) && cMenu.AppendMenu(MF_STRING, IDM_VIEW_MIMICSOBJECTCODE, STRING(IDS_MMD_FLOATINGMENU_VIEWOBJECTCODE))) ? new CMFCPopupMenu : (CMFCPopupMenu *)NULL); )
		{
			pFloatingMenu->Create(GetParentFrame(), ptMenu.x, ptMenu.y, cMenu.Detach());
			break;
		}
	}
	CScrollView::OnRButtonDown(nFlags, point);
}

void CMMDImageView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nItem;
	INT  nItems;
	BOOL  bCaps;
	BOOL  bCtrl;
	BOOL  bShift;
	CRect  rView;
	CRect  rArea;
	CRect  rItem;
	POSITION  lPosition;
	CMimicsItem  *pItem[2];
	CMMDDocument  *pDocument;

	GetClientRect(rView);
	bCaps = (LOBYTE(GetKeyState(VK_CAPITAL))) ? TRUE : FALSE;
	bCtrl = (HIBYTE(GetAsyncKeyState(VK_CONTROL))) ? TRUE : FALSE;
	bShift = (HIBYTE(GetAsyncKeyState(VK_SHIFT))) ? TRUE : FALSE;
	if ((pItem[0] = GetActivatedItem()) && !IsDraggingItem())
	{
		if (nChar == VK_LEFT || nChar == VK_RIGHT || nChar == VK_UP || (nChar == VK_DOWN  &&  !bCtrl))
		{
			for (rItem = pItem[0]->GetItemPosition(); nChar == VK_LEFT; )
			{
				rItem.OffsetRect((rItem.right > GetImageOrigin().x + 1) ? -1 : 0, 0);
				pItem[0]->SetItemPosition(rItem);
				break;
			}
			if (nChar == VK_RIGHT)
			{
				rItem.OffsetRect((rItem.left < max(GetTotalSize().cx, rView.Width()) - 1) ? 1 : 0, 0);
				pItem[0]->SetItemPosition(rItem);
			}
			if (nChar == VK_UP)
			{
				rItem.OffsetRect(0, (rItem.bottom > GetImageOrigin().y + 1) ? -1 : 0);
				pItem[0]->SetItemPosition(rItem);
			}
			if (nChar == VK_DOWN)
			{
				rItem.OffsetRect(0, (rItem.top < max(GetTotalSize().cy, rView.Height()) - 1) ? 1 : 0);
				pItem[0]->SetItemPosition(rItem);
			}
			UpdateAllItems();
		}
	}
	if (GetSelectedItemsAreaCount())
	{
		rArea = GetSelectedItemsArea();
		if (nChar == VK_LEFT || nChar == VK_RIGHT || nChar == VK_UP || (nChar == VK_DOWN  &&  !bCtrl))
		{
			if (nChar == VK_LEFT) m_rItemSelectionArea.OffsetRect((rArea.right - 1 > GetImageOrigin().x + 1) ? -1 : 0, 0);
			if (nChar == VK_RIGHT) m_rItemSelectionArea.OffsetRect((rArea.left < max(GetTotalSize().cx, rView.Width()) - 1) ? 1 : 0, 0);
			if (nChar == VK_UP) m_rItemSelectionArea.OffsetRect(0, (rArea.bottom - 1 > GetImageOrigin().y + 1) ? -1 : 0);
			if (nChar == VK_DOWN) m_rItemSelectionArea.OffsetRect(0, (rArea.top < max(GetTotalSize().cy, rView.Height()) - 1) ? 1 : 0);
			for (nItem = 0, nItems = (!m_rItemSelectionArea.EqualRect(rArea)) ? (INT)m_pSelectedItems.GetSize() : 0; nItem < nItems; nItem++)
			{
				if ((pItem[0] = (CMimicsItem *)m_pSelectedItems.GetAt(nItem)))
				{
					rItem = pItem[0]->GetItemPosition();
					rItem.OffsetRect(m_rItemSelectionArea.left - rArea.left, 0);
					rItem.OffsetRect(0, m_rItemSelectionArea.top - rArea.top);
					pItem[0]->AdjustItemPosition(rItem);
				}
			}
			UpdateAllItems();
		}
	}
	if (nChar == VK_RETURN)
	{
		if (!GetActivatedItem())
		{
			if ((pDocument = GetDocument()) && pDocument->GetItemCount() > 0)
			{
				for (; (pItem[0] = (CMimicsItem *)pDocument->GetNextItem((lPosition = pDocument->GetStartPosition()))); )
				{
					SetActivatedItem(pItem[0]);
					break;
				}
			}
		}
	}
	if (nChar == VK_TAB)
	{
		if ((pItem[0] = GetActivatedItem()))
		{
			if ((lPosition = ((pDocument = GetDocument())) ? pDocument->FindItem(pItem[0]) : (POSITION)NULL))
			{
				if ((!bShift  &&  pDocument->GetNextItem(lPosition)) || (bShift  &&  pDocument->GetPreviousItem(lPosition)))
				{
					for (; !m_rItemToggledArea.IsRectEmpty() && !bCaps; )
					{
						m_rItemToggledArea.SetRectEmpty();
						break;
					}
					for (; m_rItemToggledArea.IsRectEmpty() && bCaps; )
					{
						m_rItemToggledArea = pItem[0]->GetItemPosition();
						break;
					}
					for (pItem[1] = (!lPosition) ? ((!bShift) ? (CMimicsItem *)pDocument->GetNextItem((lPosition = pDocument->GetStartPosition())) : (CMimicsItem *)pDocument->GetPreviousItem((lPosition = pDocument->GetStopPosition()))) : ((!bShift) ? (CMimicsItem *)pDocument->GetNextItem(lPosition) : (CMimicsItem *)pDocument->GetPreviousItem(lPosition)); pItem[0] != pItem[1] && bCaps; pItem[1] = (!lPosition) ? ((!bShift) ? (CMimicsItem *)pDocument->GetNextItem((lPosition = pDocument->GetStartPosition())) : (CMimicsItem *)pDocument->GetPreviousItem((lPosition = pDocument->GetStopPosition()))) : ((!bShift) ? (CMimicsItem *)pDocument->GetNextItem(lPosition) : (CMimicsItem *)pDocument->GetPreviousItem(lPosition)))
					{
						if (rItem.IntersectRect(pItem[1]->GetItemPosition(), m_rItemToggledArea)) break;
						continue;
					}
					for (; pItem[0] != pItem[1]; )
					{
						SetActivatedItem(pItem[1]);
						break;
					}
				}
			}
		}
	}
	if (nChar == VK_DOWN  &&  bCtrl)
	{
		GetParent()->ActivateNext();
		UpdateAllItems();
	}
	for (; nChar == VK_ESCAPE; )
	{
		SetActivatedItem();
		break;
	}
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMMDImageView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	POINT  ptPosition;
	HCURSOR  hItemCursor;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	GetCursorPos(&ptPosition);
	ScreenToClient(&ptPosition);
	ptPosition.x += GetScrollPos(SB_HORZ);
	ptPosition.y += GetScrollPos(SB_VERT);
	for (hItemCursor = (HCURSOR)NULL; GetSelectedItemID() != (UINT)-1; )
	{
		SetCursor((hItemCursor = m_hPointCursor));
		break;
	}
	for (; HasSelectedItemsArea() && !hItemCursor; )
	{
		if (GetSelectedItemsArea().PtInRect(ptPosition)) SetCursor((hItemCursor = m_hSelectCursor));
		break;
	}
	for (; (pItem = GetActivatedItem()) && !hItemCursor; )
	{
		if ((hItemCursor = DetermineItemCursor(pItem, ptPosition))) SetCursor(hItemCursor);
		break;
	}
	for (lPosition = ((pDocument = GetDocument())) ? ((!hItemCursor) ? pDocument->GetStopPosition() : (POSITION)NULL) : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CMimicsItem *)pDocument->GetPreviousItem(lPosition)))
		{
			if ((hItemCursor = DetermineItemCursor(pItem, ptPosition)))
			{
				SetCursor(hItemCursor);
				break;
			}
		}
	}
	for (UpdateUndoList(), UpdateAllItems(); !hItemCursor; )
	{
		SetCursor((HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR));
		break;
	}
	CScrollView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CMMDImageView::OnTimer(UINT_PTR nEventID)
{
	UINT  nCode;
	POINT  ptPosition;
	CMimicsItem  *pItem;

	if (nEventID == MMDIMAGEVIEW_TIMERID)
	{
		GetCursorPos(&ptPosition);
		ScreenToClient(&ptPosition);
		ptPosition.x += GetScrollPos(SB_HORZ);
		ptPosition.y += GetScrollPos(SB_VERT);
		if ((nCode = ((pItem = GetActivatedItem())) ? pItem->CheckPointOnItem(ptPosition) : MIAC_NOWHERE) != MIAC_NOWHERE  &&  !pItem->IsUpdatingProperties() && HIBYTE(GetAsyncKeyState(VK_LBUTTON)))
		{
			StartDraggingItem(nCode, ptPosition);
			UpdateAllItems();
		}
		KillTimer(nEventID);
	}
	CScrollView::OnTimer(nEventID);
}

void CMMDImageView::OnDestroy()
{
	delete m_pDocument[0];
	delete m_pDocument[1];
	DestroyMimicsCtrlInterface();
	DestroyCursor(m_hDefaultCursor);
	DestroyCursor(m_hPointCursor);
	DestroyCursor(m_hMoveCursor);
	DestroyCursor(m_hSelectCursor);
	DestroyCursor(m_hWESizeCursor);
	DestroyCursor(m_hNSSizeCursor);
	DestroyCursor(m_hWENSSizeCursor);
	DestroyCursor(m_hSWNESizeCursor);
	DestroyCursor(m_hNWSESizeCursor);
	DestroyCursor(m_hHorzSizeCursor);
	DestroyCursor(m_hVertSizeCursor);
	DestroyCursor(m_hRotateCursor);
	CScrollView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CMMDCodeView

IMPLEMENT_DYNCREATE(CMMDCodeView, CRichEditView)

CMMDCodeView::CMMDCodeView() : CRichEditView()
{
	m_nWordWrap = WrapNone;
	m_bModified = FALSE;
}

BOOL CMMDCodeView::SetCode(CONST CMMDLayout &cLayout)
{
	CString  szCode;
	CByteArray  nCode;

	for (GetWindowText(szCode); cLayout.GetSourceCode() != szCode; )
	{
		cLayout.GetSourceCode(nCode);
		return SetCode(nCode);
	}
	return TRUE;
}
BOOL CMMDCodeView::SetCode(CONST CByteArray &nCode)
{
	EDITSTREAM  sStream;

	for (sStream.dwCookie = (DWORD_PTR)&nCode, sStream.pfnCallback = SetCodeCallback, GetRichEditCtrl().StreamIn(SF_RTF, sStream); TRUE; )
	{
		GetWindowText(m_szCode);
		break;
	}
	return((!sStream.dwError) ? TRUE : FALSE);
}

BOOL CMMDCodeView::GetCode(CMMDLayout &cLayout) CONST
{
	CString  szCode;
	CByteArray  nCode;

	if (GetCode(nCode))
	{
		GetWindowText(szCode);
		cLayout.SetSourceCode(nCode);
		cLayout.SetSourceCode(szCode);
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDCodeView::GetCode(CByteArray &nCode) CONST
{
	EDITSTREAM  sStream;

	sStream.dwCookie = (DWORD_PTR)&nCode;
	sStream.pfnCallback = GetCodeCallback;
	GetRichEditCtrl().StreamOut(SF_RTF, sStream);
	return((!sStream.dwError) ? TRUE : FALSE);
}

INT CMMDCodeView::GetCodeSize() CONST
{
	return GetTextLength();
}

VOID CMMDCodeView::DoUndo()
{
	GetRichEditCtrl().Undo();
}

BOOL CMMDCodeView::CanUndo() CONST
{
	return((GetRichEditCtrl().CanUndo()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDCodeView::DoRedo()
{
	GetRichEditCtrl().Redo();
}

BOOL CMMDCodeView::CanRedo() CONST
{
	return((GetRichEditCtrl().CanRedo()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDCodeView::DoFindCode()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgFind.Create(GetParent()->GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CMMDCodeView::CanFindCode() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetCodeSize() > 0) ? TRUE : FALSE);
}

VOID CMMDCodeView::DoFindNextCode()
{
	LONG  nPos[2];
	CString  szText;

	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.GetDlgItem(IDC_MMD_FIND_TEXT)->GetWindowText(szText), GetRichEditCtrl().GetSel(nPos[0], nPos[1]), nPos[0] = nPos[1] = nPos[0] + szText.GetLength(), GetRichEditCtrl().SetSel(nPos[0], nPos[1]); !szText.IsEmpty(); )
		{
			ShowMessage((!SearchCode(szText, TRUE, FALSE, m_dlgFind.IsDlgButtonChecked(IDC_MMD_FIND_CASE), m_dlgFind.IsDlgButtonChecked(IDC_MMD_FIND_WORD))) ? USER_INFORMATIONAL_MMD_FIND_TEXT_NOTHING : USER_NOERROR);
			break;
		}
	}
}
VOID CMMDCodeView::DoFindNextCode(BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!SearchCode(GetRichEditCtrl().GetSelText(), TRUE, FALSE, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_MMD_FIND_TEXT_NOTHING : USER_NOERROR);
}
VOID CMMDCodeView::DoFindNextCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!SearchCode(pszText, TRUE, bSearchAll, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_MMD_FIND_TEXT_NOTHING : USER_NOERROR);
}

BOOL CMMDCodeView::CanFindNextCode() CONST
{
	return(((IsWindow(m_dlgFind.GetSafeHwnd()) || !GetRichEditCtrl().GetSelText().IsEmpty()) && GetCodeSize() > 0) ? TRUE : FALSE);
}

VOID CMMDCodeView::DoFindPreviousCode()
{
	CString  szText;

	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.GetDlgItem(IDC_MMD_FIND_TEXT)->GetWindowText(szText); !szText.IsEmpty(); )
		{
			ShowMessage((!SearchCode(szText, FALSE, FALSE, m_dlgFind.IsDlgButtonChecked(IDC_MMD_FIND_CASE), m_dlgFind.IsDlgButtonChecked(IDC_MMD_FIND_WORD))) ? USER_INFORMATIONAL_MMD_FIND_TEXT_NOTHING : USER_NOERROR);
			break;
		}
	}
}
VOID CMMDCodeView::DoFindPreviousCode(BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!SearchCode(GetRichEditCtrl().GetSelText(), FALSE, FALSE, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_MMD_FIND_TEXT_NOTHING : USER_NOERROR);
}
VOID CMMDCodeView::DoFindPreviousCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!SearchCode(pszText, FALSE, bSearchAll, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_MMD_FIND_TEXT_NOTHING : USER_NOERROR);
}

BOOL CMMDCodeView::CanFindPreviousCode() CONST
{
	return(((IsWindow(m_dlgFind.GetSafeHwnd()) || !GetRichEditCtrl().GetSelText().IsEmpty()) && GetCodeSize() > 0) ? TRUE : FALSE);
}

VOID CMMDCodeView::DoReplaceCode()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgReplace.Create(GetParent()->GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CMMDCodeView::CanReplaceCode() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetCodeSize() > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDCodeView::DoGoToCode()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgGoTo.Create(GetParent()->GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CMMDCodeView::CanGoToCode() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetCodeSize() > 0) ? TRUE : FALSE);
}

VOID CMMDCodeView::DoCutCode()
{
	GetRichEditCtrl().Cut();
}

BOOL CMMDCodeView::CanCutCode() CONST
{
	return((GetRichEditCtrl().GetSelectionType() != SEL_EMPTY) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDCodeView::DoCopyCode()
{
	GetRichEditCtrl().Copy();
}

BOOL CMMDCodeView::CanCopyCode() CONST
{
	return((GetRichEditCtrl().GetSelectionType() != SEL_EMPTY) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDCodeView::DoPasteCode()
{
	GetRichEditCtrl().Paste();
}

BOOL CMMDCodeView::CanPasteCode() CONST
{
	return((GetRichEditCtrl().CanPaste(CF_TEXT)) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDCodeView::DoDeleteCode()
{
	LONG  nSel[2];

	for (GetRichEditCtrl().GetSel(nSel[0], nSel[1]); GetRichEditCtrl().GetSelectionType() == SEL_EMPTY; )
	{
		GetRichEditCtrl().SetSel(nSel[0], nSel[0] + 1);
		break;
	}
	GetRichEditCtrl().Clear();
}

BOOL CMMDCodeView::CanDeleteCode() CONST
{
	LONG  nSel[2];

	GetRichEditCtrl().GetSel(nSel[0], nSel[1]);
	return((GetRichEditCtrl().GetSelectionType() != SEL_EMPTY || nSel[0] < GetRichEditCtrl().GetTextLengthEx(GTL_PRECISE | GTL_NUMCHARS)) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDCodeView::DoSelectAllCode()
{
	GetRichEditCtrl().SetSel(0, -1);
}

VOID CMMDCodeView::UnSelectAllCode()
{
	GetRichEditCtrl().SetSel(0, 0);
}

BOOL CMMDCodeView::CanSelectAllCode() CONST
{
	return((GetTextLength() > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

INT CMMDCodeView::FindCode(LPCTSTR pszName) CONST
{
	INT  nPos[3];
	CString  szName;
	CString  szCode;

	for (nPos[0] = nPos[1] = 0, szName = STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER) + CString(pszName) + STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER), GetRichEditCtrl().GetTextRange(0, GetRichEditCtrl().GetTextLength(), szCode); nPos[0] < szCode.GetLength(); )
	{
		if ((nPos[1] = szCode.Mid(nPos[0]).Find(szName)) < 0)
		{
			nPos[0] = szCode.GetLength();
			continue;
		}
		for (nPos[2] = nPos[1] - 1; nPos[2] >= 0; nPos[2]--)
		{
			if (!_istspace(szCode.GetAt(nPos[0] + nPos[2])) && szCode.GetAt(nPos[0] + nPos[2]) != TAB) break;
			continue;
		}
		if (nPos[2] >= lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)) - 1 && szCode.Mid((nPos[2] = nPos[0] + nPos[2] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)) + 1), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE))) == STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)) break;
		nPos[0] += nPos[1] + 1;
	}
	return((nPos[0] < szCode.GetLength()) ? nPos[2] : -1);
}
BOOL CMMDCodeView::FindCode(CString &szName) CONST
{
	INT  nLine;
	INT  nLength;
	LONG  nPos[3];
	CString  szLine;

	GetRichEditCtrl().GetSel(nPos[0], nPos[1]);
	if ((nLine = GetRichEditCtrl().LineFromChar(nPos[0])) == GetRichEditCtrl().LineFromChar(nPos[1]))
	{
		if (GetRichEditCtrl().GetLine(nLine, szLine.GetBufferSetLength(nLength), (nLength = GetRichEditCtrl().LineLength(nPos[0]) + 1)) > 0)
		{
			for (szLine.ReleaseBuffer(); (nPos[2] = szLine.Find(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE))) >= 0; )
			{
				for (nPos[2] += lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)); nPos[2] < lstrlen(szLine); nPos[2]++)
				{
					if (!_istspace(szLine.GetAt(nPos[2])) && szLine.GetAt(nPos[2]) != TAB) break;
					continue;
				}
				if (nPos[2] < lstrlen(szLine))
				{
					if (szLine.GetAt(nPos[2]) == STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER))
					{
						for (nPos[2] = nPos[2] + 1, szName.Empty(); nPos[2] < lstrlen(szLine); nPos[2]++)
						{
							if (szLine.GetAt(nPos[2]) != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER))
							{
								szName += szLine.GetAt(nPos[2]);
								continue;
							}
							break;
						}
						szName = (nPos[2] < lstrlen(szLine)) ? (LPCTSTR)szName : EMPTYSTRING;
						return !szName.IsEmpty();
					}
				}
			}
			return FALSE;
		}
		szLine.ReleaseBuffer();
	}
	return FALSE;
}

VOID CMMDCodeView::SelectCode(LPCTSTR pszName)
{
	INT  nPos;

	if ((nPos = FindCode(pszName)) >= 0)
	{
		GetRichEditCtrl().SetSel(nPos, nPos);
		return;
	}
}

BOOL CMMDCodeView::SearchCode(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	LONG  nPos[2];
	DWORD  dwFlags;
	FINDTEXTEX  sText;

	for (GetRichEditCtrl().GetSel(nPos[0], nPos[1]); nPos[0] < nPos[1]; )
	{
		nPos[0] = (bDown) ? min(nPos[0] + 1, GetRichEditCtrl().GetTextLength() - 1) : max(nPos[0] - 1, 0);
		break;
	}
	for (dwFlags = (bDown) ? FR_DOWN : 0, dwFlags |= (bCase) ? FR_MATCHCASE : 0, dwFlags |= (bWord) ? FR_WHOLEWORD : 0, sText.lpstrText = pszText, sText.chrg.cpMin = (bAll) ? ((!bDown) ? (GetRichEditCtrl().GetTextLength() - 1) : 0) : nPos[0], sText.chrg.cpMax = GetRichEditCtrl().GetTextLength(); GetRichEditCtrl().FindText(dwFlags, &sText) >= 0; )
	{
		GetRichEditCtrl().SetSel(sText.chrgText.cpMin, sText.chrgText.cpMax);
		SetFocus();
		return TRUE;
	}
	GetRichEditCtrl().SetSel(0, 0);
	return FALSE;
}

BOOL CMMDCodeView::ReplaceCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	LONG  nSel[2];
	CString  szText;

	for (GetRichEditCtrl().GetSel(nSel[0], nSel[1]); nSel[0] < nSel[1] && nSel[1] - nSel[0] == lstrlen(pszText); )
	{
		if (SendMessage(EM_GETSELTEXT, (WPARAM)NULL, (LPARAM)szText.GetBufferSetLength(nSel[1] - nSel[0])) == nSel[1] - nSel[0])
		{
			for (szText.ReleaseBuffer(); (bCase && !szText.Compare(pszText)) || (!bCase && !szText.CompareNoCase(pszText)); )
			{
				GetRichEditCtrl().ReplaceSel(pszReplaceText, TRUE);
				GetRichEditCtrl().GetSel(nSel[0], nSel[1]);
				GetRichEditCtrl().SetSel(nSel[1], nSel[1]);
				break;
			}
			break;
		}
		szText.ReleaseBuffer();
		break;
	}
	return SearchCode(pszText, bDown, bAll, bCase, bWord);
}

BOOL CMMDCodeView::ReplaceAllCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	LONG  nSel[2];

	for (GetRichEditCtrl().HideSelection(TRUE, TRUE), GetRichEditCtrl().GetSel(nSel[0], nSel[1]), GetRichEditCtrl().SetSel((bAll) ? ((!bDown) ? (GetRichEditCtrl().GetTextLength() - 1) : 0) : nSel[0], (bAll) ? ((!bDown) ? (GetRichEditCtrl().GetTextLength() - 1) : 0) : nSel[1]); TRUE; )
	{
		if (!ReplaceCode(pszText, pszReplaceText, bDown, FALSE, bCase, bWord)) break;
		continue;
	}
	GetRichEditCtrl().HideSelection(FALSE, TRUE);
	return TRUE;
}

BOOL CMMDCodeView::GoToCode(UINT nLine, BOOL bDown, BOOL bUp)
{
	INT  nPos;

	if (!bDown  &&  !bUp)
	{
		if ((nPos = GetRichEditCtrl().LineIndex(nLine - 1)) >= 0 && nLine > 0)
		{
			GetRichEditCtrl().SetSel(nPos, nPos + max(GetRichEditCtrl().LineLength(nPos), 1));
			return TRUE;
		}
		return FALSE;
	}
	return GoToCode((bDown) ? (GetRichEditCtrl().LineFromChar(-1) + nLine + 1) : (GetRichEditCtrl().LineFromChar(-1) - nLine + 1), FALSE, FALSE);
}
BOOL CMMDCodeView::GoToCode(LPCTSTR pszLine)
{
	INT  nPos[3];
	INT  nLength;
	CString  szKey;
	CString  szText;
	LPCTSTR  pPos[3];
	FINDTEXTEX  sTextPos;

	if ((pPos[0] = _tcsstr(pszLine, STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_GENERICSEARCHKEY))))
	{
		if ((pPos[1] = _tcsstr(pPos[0], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_SIMPLESEARCHKEY))))
		{
			for (nPos[0] = 0, pPos[2] = pPos[1] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_SIMPLESEARCHKEY)), szKey = CString(pszLine).Mid(lstrlen(pszLine) - lstrlen(pPos[0]) + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_GENERICSEARCHKEY)), (INT)(pPos[1] - pPos[0] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_GENERICSEARCHKEY)) - 1)), nLength = GetRichEditCtrl().GetTextLength(); nPos[0] < nLength; nPos[0]++)
			{
				sTextPos.lpstrText = (LPCTSTR)szKey;
				sTextPos.chrg.cpMin = nPos[0];
				sTextPos.chrg.cpMax = nLength;
				if ((nPos[1] = GetRichEditCtrl().FindText(FR_DOWN | FR_MATCHCASE, &sTextPos)) > 0)
				{
					for (nPos[2] = nPos[1] - 1; nPos[2] >= 0; nPos[2] = nPos[2] - 1)
					{
						GetRichEditCtrl().GetTextRange(nPos[2], nPos[1], szText);
						if (!_istspace(szText[0]) && szText[0] != TAB  &&  szText[0] != CR  &&  szText[0] != EOL)
						{
							nPos[2]++;
							break;
						}
					}
					if (nPos[2] >= lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)))
					{
						for (GetRichEditCtrl().GetTextRange(nPos[2] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)), nPos[2], szText); szText == STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE); )
						{
							for (sTextPos.chrg.cpMin = nPos[1], sTextPos.chrg.cpMax = nLength, sTextPos.lpstrText = STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN); (nPos[1] = GetRichEditCtrl().FindText(FR_DOWN | FR_MATCHCASE, &sTextPos)) >= 0; )
							{
								GetRichEditCtrl().SetSel(nPos[1], nPos[1]);
								return GoToCode(_ttoi(pPos[2]), TRUE);
							}
							break;
						}
					}
					nPos[0] = nPos[1];
					continue;
				}
				break;
			}
		}
		return FALSE;
	}
	return(((pPos[0] = _tcsstr(pszLine, STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_SIMPLESEARCHKEY)))) ? GoToCode(_ttoi(pPos[0] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_SIMPLESEARCHKEY)))) : FALSE);
}

VOID CMMDCodeView::ShowDialogs(BOOL bShow)
{
	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.ShowWindow((bShow) ? SW_SHOW : SW_HIDE); bShow; )
		{
			m_dlgFind.SetFocus();
			break;
		}
		return;
	}
	if (IsWindow(m_dlgReplace.GetSafeHwnd()))
	{
		for (m_dlgReplace.ShowWindow((bShow) ? SW_SHOW : SW_HIDE); bShow; )
		{
			m_dlgReplace.SetFocus();
			break;
		}
		return;
	}
	if (IsWindow(m_dlgGoTo.GetSafeHwnd()))
	{
		for (m_dlgGoTo.ShowWindow((bShow) ? SW_SHOW : SW_HIDE); bShow; )
		{
			m_dlgGoTo.SetFocus();
			break;
		}
		return;
	}
}

BOOL CMMDCodeView::HasDialogs() CONST
{
	return((IsWindow(m_dlgFind.GetSafeHwnd()) || IsWindow(m_dlgReplace.GetSafeHwnd()) || IsWindow(m_dlgGoTo.GetSafeHwnd())) ? TRUE : FALSE);
}

VOID CMMDCodeView::SetModified(BOOL bFlag)
{
	for (m_bModified = bFlag; !bFlag; )
	{
		GetWindowText(m_szCode);
		break;
	}
}

BOOL CMMDCodeView::IsModified() CONST
{
	CString  szCode;

	GetWindowText(szCode);
	return((m_szCode != szCode || m_bModified) ? TRUE : FALSE);
}

CMMDSplitterWnd *CMMDCodeView::GetParent() CONST
{
	return((CMMDSplitterWnd *)CRichEditView::GetParent());
}

DWORD CALLBACK CMMDCodeView::SetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	LONG  cbCode;
	CByteArray  *pCode = (CByteArray *)dwCookie;
	static LONG  nCode = 0;

	CopyMemory(pbBuff, pCode->GetData() + nCode, (cbCode = (LONG)max(min(pCode->GetSize() - nCode, cb), 0)));
	CopyMemory(pcb, &cbCode, sizeof(LONG));
	nCode = (nCode + cbCode < pCode->GetSize()) ? (nCode + cbCode) : 0;
	return 0;
}

DWORD CALLBACK CMMDCodeView::GetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	LONG  cbCode;
	CByteArray  *pCode = (CByteArray *)dwCookie;

	pCode->SetSize((cbCode = (LONG)pCode->GetSize()) + cb);
	CopyMemory(pCode->GetData() + cbCode, pbBuff, cb);
	CopyMemory(pcb, &cb, sizeof(LONG));
	return 0;
}

LRESULT CMMDCodeView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SETCURSOR:
	{ if (message == WM_SETCURSOR)
	{
		if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE))
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
			return TRUE;
		}
		break;
	}
	}
	case WM_SETFOCUS:
	{ if (message == WM_SETFOCUS)
	{
		if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE))
		{
			GetParent()->GetImageView()->UnSelectAllItems();
			return FALSE;
		}
		break;
	}
	}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	{ if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) && ((message != WM_KEYDOWN  &&  message != WM_KEYUP  &&  message != WM_CHAR) || (wParam != VK_HOME  &&  wParam != VK_END  &&  wParam != VK_UP  &&  wParam != VK_DOWN  &&  wParam != VK_PRIOR  &&  wParam != VK_NEXT  &&  wParam != VK_LEFT  &&  wParam != VK_RIGHT)))
	{
		UnSelectAllCode();
		return FALSE;
	}
	}
	default: break;
	}
	return CRichEditView::WindowProc(message, wParam, lParam);
}

BEGIN_MESSAGE_MAP(CMMDCodeView, CRichEditView)
	//{{AFX_MSG_MAP(CMMDCodeView)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_CONTROL_REFLECT(EN_CHANGE, OnEditchangeCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDCodeView drawing

void CMMDCodeView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CMMDCodeView message handlers

int CMMDCodeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFontTools  cFontTools(&m_cCodeFont);

	if (CRichEditView::OnCreate(lpCreateStruct) != -1)
	{
		GetRichEditCtrl().SetEventMask(GetRichEditCtrl().GetEventMask() | ENM_CHANGE | ENM_REQUESTRESIZE);
		GetRichEditCtrl().RequestResize();
		WrapChanged();
		return 0;
	}
	return -1;
}

void CMMDCodeView::OnSetFocus(CWnd *pOldWnd)
{
	GetParent()->GetImageView()->UnSelectAllItems();
	CRichEditView::OnSetFocus(pOldWnd);
}

void CMMDCodeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	INT  i;
	INT  nPos;
	INT  nLine;
	INT  nLength;
	LONG  nSel[2];
	CRect  rLines;
	CPoint  ptPos;

	for (nLine = GetRichEditCtrl().GetFirstVisibleLine(), GetRichEditCtrl().GetRect(rLines), GetRichEditCtrl().GetSel(nSel[0], nSel[1]); nLine < GetRichEditCtrl().GetLineCount() && !nSel[0] && !nSel[1]; nLine++)
	{
		if (rLines.PtInRect((ptPos = GetRichEditCtrl().GetCharPos((nPos = GetRichEditCtrl().LineIndex(nLine))))))
		{
			for (i = 0, nPos = (ptPos.y > point.y && nLine > 0) ? GetRichEditCtrl().LineIndex((nLine = nLine - 1)) : -1, nLength = GetRichEditCtrl().LineLength(nPos); i < nLength && nPos >= 0; i++)
			{
				if (GetRichEditCtrl().GetCharPos(nPos + i).x > point.x) break;
				continue;
			}
			if (nPos >= 0 && i < nLength)
			{
				GetRichEditCtrl().SetSel(max(nPos + i - 1, 0), max(nPos + i - 1, 0));
				break;
			}
			if (nPos >= 0 && i == nLength)
			{
				GetRichEditCtrl().SetSel(nPos + nLength, nPos + nLength);
				break;
			}
			continue;
		}
		if (ptPos.y > rLines.bottom) break;
	}
	CRichEditView::OnLButtonDown(nFlags, point);
}

void CMMDCodeView::OnRButtonDown(UINT nFlags, CPoint point)
{
	INT  i;
	INT  nPos;
	INT  nLine;
	INT  nLength;
	CMenu  cMenu;
	CRect  rLines;
	CPoint  ptPos;
	CPoint  ptMenu;
	CMFCPopupMenu  *pFloatingMenu;

	for (nLine = GetRichEditCtrl().GetFirstVisibleLine(), GetRichEditCtrl().GetRect(rLines); nLine < GetRichEditCtrl().GetLineCount(); nLine++)
	{
		if (rLines.PtInRect((ptPos = GetRichEditCtrl().GetCharPos((nPos = GetRichEditCtrl().LineIndex(nLine))))))
		{
			for (i = 0, nPos = (ptPos.y > point.y && nLine > 0) ? GetRichEditCtrl().LineIndex((nLine = nLine - 1)) : -1, nLength = GetRichEditCtrl().LineLength(nPos); i < nLength && nPos >= 0; i++)
			{
				if (GetRichEditCtrl().GetCharPos(nPos + i).x > point.x) break;
				continue;
			}
			if (nPos >= 0 && i < nLength)
			{
				GetRichEditCtrl().SetSel(max(nPos + i - 1, 0), max(nPos + i - 1, 0));
				break;
			}
			if (nPos >= 0 && i == nLength)
			{
				GetRichEditCtrl().SetSel(nPos + nLength, nPos + nLength);
				break;
			}
			continue;
		}
		if (ptPos.y > rLines.bottom) break;
	}
	for (ClientToScreen(&(ptMenu = point)); (pFloatingMenu = (cMenu.CreatePopupMenu() && cMenu.AppendMenu(MF_STRING, IDM_VIEW_MIMICSOBJECTPROPERTIES, STRING(IDS_MMD_FLOATINGMENU_PROPERTIES)) && cMenu.AppendMenu(MF_STRING, IDM_VIEW_MIMICSOBJECTITEM, STRING(IDS_MMD_FLOATINGMENU_VIEWOBJECTITEM))) ? new CMFCPopupMenu : (CMFCPopupMenu *)NULL); )
	{
		pFloatingMenu->Create(GetParentFrame(), ptMenu.x, ptMenu.y, cMenu.Detach());
		break;
	}
	CRichEditView::OnRButtonDown(nFlags, point);
}

void CMMDCodeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_F3)
	{
		if (CanFindNextCode() && !HIBYTE(GetKeyState(VK_SHIFT))) DoFindNextCode();
		if (CanFindPreviousCode() && HIBYTE(GetKeyState(VK_SHIFT))) DoFindPreviousCode();
	}
	if (nChar == VK_UP)
	{
		if (HIBYTE(GetAsyncKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNext(TRUE);
			return;
		}
	}
	for (; nChar == VK_INSERT; )
	{
		GetParent()->GetParent()->DoToggleKey();
		break;
	}
	CRichEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMMDCodeView::OnEditchangeCode()
{
	CMDLCodeEdit::RenderCode(&GetRichEditCtrl(), &m_cCodeFont);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDSplitterWnd

IMPLEMENT_DYNCREATE(CMMDSplitterWnd, CSplitterWndEx)

CMMDSplitterWnd::CMMDSplitterWnd() : CSplitterWndEx()
{
	m_pDocument = (CMMDDocument *)NULL;
}

BOOL CMMDSplitterWnd::Create(CMMDWnd *pParentWnd)
{
	CRect  rPanes;
	CCreateContext  cContext;

	if (CreateStatic(pParentWnd, 2, 1))
	{
		if ((m_pDocument = new CMMDDocument))
		{
			for (pParentWnd->GetClientRect(rPanes), cContext.m_pCurrentDoc = m_pDocument; CreateView(0, 0, RUNTIME_CLASS(CMMDImageView), CSize(rPanes.Width(), 3 * rPanes.Height() / 4), &cContext) && CreateView(1, 0, RUNTIME_CLASS(CMMDCodeView), CSize(rPanes.Width(), rPanes.Height() - 3 * rPanes.Height() / 4), &cContext); )
			{
				SetActivePane(0, 0, GetImageView());
				return TRUE;
			}
			delete m_pDocument;
			m_pDocument = (CMMDDocument *)NULL;
		}
	}
	return FALSE;
}

VOID CMMDSplitterWnd::DoUndo()
{
	CView  *pView;

	if ((pView = GetActivePane()))
	{
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)))
		{
			GetImageView()->DoUndo();
			return;
		}
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
		{
			GetCodeView()->DoUndo();
			return;
		}
	}
}

BOOL CMMDSplitterWnd::CanUndo() CONST
{
	CView  *pView;

	return(((pView = GetActivePane())) ? ((pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)) && GetImageView()->CanUndo()) || (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)) && GetCodeView()->CanUndo())) : FALSE);
}

VOID CMMDSplitterWnd::DoRedo()
{
	CView  *pView;

	if ((pView = GetActivePane()))
	{
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)))
		{
			GetImageView()->DoRedo();
			return;
		}
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
		{
			GetCodeView()->DoRedo();
			return;
		}
	}
}

BOOL CMMDSplitterWnd::CanRedo() CONST
{
	CView  *pView;

	return(((pView = GetActivePane())) ? ((pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)) && GetImageView()->CanRedo()) || (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)) && GetCodeView()->CanRedo())) : FALSE);
}

VOID CMMDSplitterWnd::DoFind()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
	{
		GetCodeView()->DoFindCode();
		return;
	}
}

BOOL CMMDSplitterWnd::CanFind() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView))) ? GetCodeView()->CanFindCode() : FALSE);
}

VOID CMMDSplitterWnd::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
	{
		GetCodeView()->DoFindNextCode(bMatchCase, bMatchWord);
		return;
	}
}
VOID CMMDSplitterWnd::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
	{
		GetCodeView()->DoFindNextCode(pszText, bSearchAll, bMatchCase, bMatchWord);
		return;
	}
}

BOOL CMMDSplitterWnd::CanFindNext() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView))) ? GetCodeView()->CanFindNextCode() : FALSE);
}

VOID CMMDSplitterWnd::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
	{
		GetCodeView()->DoFindPreviousCode(bMatchCase, bMatchWord);
		return;
	}
}
VOID CMMDSplitterWnd::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
	{
		GetCodeView()->DoFindPreviousCode(pszText, bSearchAll, bMatchCase, bMatchWord);
		return;
	}
}

BOOL CMMDSplitterWnd::CanFindPrevious() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView))) ? GetCodeView()->CanFindPreviousCode() : FALSE);
}

VOID CMMDSplitterWnd::DoReplace()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
	{
		GetCodeView()->DoReplaceCode();
		return;
	}
}

BOOL CMMDSplitterWnd::CanReplace() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView))) ? GetCodeView()->CanReplaceCode() : FALSE);
}

VOID CMMDSplitterWnd::DoGoTo()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
	{
		GetCodeView()->DoGoToCode();
		return;
	}
}

BOOL CMMDSplitterWnd::CanGoTo() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView))) ? GetCodeView()->CanGoToCode() : FALSE);
}

VOID CMMDSplitterWnd::DoCutSel()
{
	CView  *pView;

	if ((pView = GetActivePane()))
	{
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)))
		{
			GetImageView()->DoCutItem();
			return;
		}
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
		{
			GetCodeView()->DoCutCode();
			return;
		}
	}
}

BOOL CMMDSplitterWnd::CanCutSel() CONST
{
	CView  *pView;

	return(((pView = GetActivePane())) ? ((pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)) && GetImageView()->CanCutItem()) || (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)) && GetCodeView()->CanCutCode())) : FALSE);
}

VOID CMMDSplitterWnd::DoCopySel()
{
	CView  *pView;

	if ((pView = GetActivePane()))
	{
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)))
		{
			GetImageView()->DoCopyItem();
			return;
		}
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
		{
			GetCodeView()->DoCopyCode();
			return;
		}
	}
}

BOOL CMMDSplitterWnd::CanCopySel() CONST
{
	CView  *pView;

	return(((pView = GetActivePane())) ? ((pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)) && GetImageView()->CanCopyItem()) || (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)) && GetCodeView()->CanCopyCode())) : FALSE);
}

VOID CMMDSplitterWnd::DoPasteSel()
{
	CView  *pView;

	if ((pView = GetActivePane()))
	{
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)))
		{
			GetImageView()->DoPasteItem();
			return;
		}
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
		{
			GetCodeView()->DoPasteCode();
			return;
		}
	}
}

BOOL CMMDSplitterWnd::CanPasteSel() CONST
{
	CView  *pView;

	return(((pView = GetActivePane())) ? ((pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)) && GetImageView()->CanPasteItem()) || (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)) && GetCodeView()->CanPasteCode())) : FALSE);
}

VOID CMMDSplitterWnd::DoDeleteSel()
{
	CView  *pView;

	if ((pView = GetActivePane()))
	{
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)))
		{
			GetImageView()->DoDeleteItem();
			return;
		}
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
		{
			GetCodeView()->DoDeleteCode();
			return;
		}
	}
}

BOOL CMMDSplitterWnd::CanDeleteSel() CONST
{
	CView  *pView;

	return(((pView = GetActivePane())) ? ((pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)) && GetImageView()->CanDeleteItem()) || (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)) && GetCodeView()->CanDeleteCode())) : FALSE);
}

VOID CMMDSplitterWnd::DoSelectAll()
{
	CView  *pView;

	if ((pView = GetActivePane()))
	{
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)))
		{
			GetImageView()->DoSelectAllItems();
			return;
		}
		if (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)))
		{
			GetCodeView()->DoSelectAllCode();
			return;
		}
	}
}

VOID CMMDSplitterWnd::UnSelectAll()
{
	GetImageView()->UnSelectAllItems();
	GetCodeView()->UnSelectAllCode();
	GetParent()->UpdateBars();
}

BOOL CMMDSplitterWnd::CanSelectAll() CONST
{
	CView  *pView;

	return(((pView = GetActivePane())) ? ((pView->IsKindOf(RUNTIME_CLASS(CMMDImageView)) && GetImageView()->CanSelectAllItems()) || (pView->IsKindOf(RUNTIME_CLASS(CMMDCodeView)) && GetCodeView()->CanSelectAllCode())) : FALSE);
}

CView *CMMDSplitterWnd::GetActivePane() CONST
{
	CView  *pView;

	return(((pView = (GetParentFrame()->GetActiveView()) ? (CView *)GetParentFrame()->GetActiveView() : (CView *)GetFocus()) && (pView == GetImageView() || pView == GetCodeView())) ? pView : (CView *)NULL);
}

CMMDImageView *CMMDSplitterWnd::GetImageView() CONST
{
	return((IsWindow(GetDlgItem(IdFromRowCol(0, 0))->GetSafeHwnd())) ? (CMMDImageView *)GetPane(0, 0) : (CMMDImageView *)NULL);
}

CMMDCodeView *CMMDSplitterWnd::GetCodeView() CONST
{
	return((IsWindow(GetDlgItem(IdFromRowCol(1, 0))->GetSafeHwnd())) ? (CMMDCodeView *)GetPane(1, 0) : (CMMDCodeView *)NULL);
}

CMMDWnd *CMMDSplitterWnd::GetParent() CONST
{
	return((CMMDWnd *)CSplitterWndEx::GetParent());
}

BEGIN_MESSAGE_MAP(CMMDSplitterWnd, CSplitterWndEx)
	//{{AFX_MSG_MAP(CMMDSplitterWnd)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDSplitterWnd message handlers

void CMMDSplitterWnd::OnDestroy()
{
	delete m_pDocument;
	CSplitterWndEx::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CMMDCompileThread

IMPLEMENT_DYNAMIC(CMMDCompileThread, CThread)

CMMDCompileThread::CMMDCompileThread() : CThread()
{
	m_nErrors = 0;
	m_nWarnings = 0;
	m_bAbort = FALSE;
	m_bStop = FALSE;
}

BOOL CMMDCompileThread::StartCompiling(CBinaryDatabase *pDatabase, LPCTSTR pszName)
{
	for (SetAbortStatus(), SetCompileTarget(pszName, FALSE, FALSE), m_bCompilation[0].ResetEvent(), m_bCompilation[1].ResetEvent(); CreateThread((LPVOID)pDatabase, THREAD_PRIORITY_BELOW_NORMAL); )
	{
		WaitForSingleObject(m_bCompilation[0], INFINITE);
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDCompileThread::StartCompiling(CBinaryDatabase *pDatabase, LPCTSTR pszName, BOOL bSyntax, BOOL bBatch, INT &nErrors, INT &nWarnings, BOOL &bAbort)
{
	for (SetAbortStatus(), SetCompileTarget(pszName, bSyntax, bBatch), m_bCompilation[0].ResetEvent(), m_bCompilation[1].ResetEvent(), nErrors = nWarnings = 0; CreateThread((LPVOID)pDatabase, THREAD_PRIORITY_BELOW_NORMAL); )
	{
		for (WaitForSingleObject(m_bCompilation[0], INFINITE); bBatch; )
		{
			WaitForSingleObject(m_bCompilation[1], INFINITE);
			break;
		}
		nErrors = GetErrorCount();
		nWarnings = GetWarningCount();
		bAbort = GetAbortStatus();
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDCompileThread::IsCompiling() CONST
{
	return((IsThreadActive()) ? (!m_bStop  &&  !m_bAbort) : FALSE);
}

BOOL CMMDCompileThread::StopCompiling()
{
	if (IsCompiling())
	{
		ShowCompileMessage(STRING(IDS_COMPILER_MESSAGE_BREAKCOMPILING));
		SetAbortStatus(TRUE);
		DestroyThread();
		return TRUE;
	}
	return FALSE;
}

VOID CMMDCompileThread::SetCompileTarget(LPCTSTR pszName, BOOL bSyntax, BOOL bBatch)
{
	m_szName = pszName;
	m_bSyntax = bSyntax;
	m_bBatch = bBatch;
}

CString CMMDCompileThread::GetCompileTarget() CONST
{
	return m_szName;
}

BOOL CMMDCompileThread::IsSyntaxCompileTarget() CONST
{
	return m_bSyntax;
}

BOOL CMMDCompileThread::IsBatchCompileTarget() CONST
{
	return m_bBatch;
}

int CMMDCompileThread::Run()
{
	CBinaryDatabase  *pDatabase = (CBinaryDatabase *)GetThreadInfo();
	CUpdateUI  cUpdateUI;

	for (SetErrorCount(), SetWarningCount(), ShowStartCompileMessages(); OpenCompileTarget(pDatabase); )
	{
		CompileTarget(pDatabase);
		CloseCompileTarget();
		break;
	}
	ShowStopCompileMessages();
	return 0;
}

BOOL CMMDCompileThread::OpenCompileTarget(CBinaryDatabase *pDatabase)
{
	CString  szMessage;

	if (pDatabase->LoadMMD(GetCompileTarget(), m_cLayout))
	{
		m_bCompilation[0].SetEvent();
		return TRUE;
	}
	szMessage.Format(STRING(IDS_MMD_FAILURE_LOAD), (LPCTSTR)GetCompileTarget());
	ShowCompileMessage(szMessage, TRUE, TRUE);
	m_bCompilation[0].SetEvent();
	m_bCompilation[1].SetEvent();
	return FALSE;
}

VOID CMMDCompileThread::CompileTarget(CBinaryDatabase *pDatabase)
{
	INT  nSample;
	INT  nSamples;
	INT  nTrigger;
	INT  nTriggers;
	INT  nParameter;
	INT  nParameters;
	INT  nProcedure;
	INT  nProcedures;
	INT  nMimicsItem;
	INT  nMimicsItems;
	INT  nDataPos[9];
	INT  nStaticParameter;
	INT  nStaticParameters;
	CHAR  szOut[512];
	TCHAR  szDataPos;
	DWORD  dwBuf;
	DWORD  dwOut;
	DWORD  cbOut;
	CFileEx  cFile;
	HANDLE  hStdIn[3];
	HANDLE  hStdOut[3];
	HANDLE  hStdError;
	LPCTSTR  pDataPos;
	LPCTSTR  pKeyPos[2];
	CString  szCheck;
	CString  szError;
	CString  szErrors;
	CString  szData[1];
	CString  szName[2];
	CString  szType[1];
	CString  szMessage;
	CString  szWarning;
	CString  szOptions;
	CString  szVariable;
	CString  szArgument;
	CString  szProcedure;
	CString  szParameter;
	CString  szStatements;
	CString  szOutputName;
	CString  szDefinition;
	CString  szDeclaration;
	CString  szFileName[3];
	CFileFindEx  cFileFind;
	CByteArray  nFileData;
	CByteArray  bTriggerFlags;
	CUIntArray  nPastSamples[2];
	CStringArray  szParameters[4];
	CStringArray  szMimicsNames[2];
	CStringArray  szMimicsTypes[2];
	CStringArray  szPastProcedures;
	CStringArray  szPastParameters;
	CStringArray  szStaticParameters;
	CStringArray  szVolatileParameters;
	CStringArray  szTriggerProcedures;
	CStringArray  szImplementedProcedures;
	CStringArray  szPastProcedureParameters;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	SECURITY_ATTRIBUTES  sCompilerSecurityAttributes = { 0 };
	PROCESS_INFORMATION  sCompilerInformation = { 0 };
	STARTUPINFO  sCompilerStartupInformation = { 0 };

	if (!TranslateSourceCodeItems(szMimicsNames[0], szMimicsTypes[0]))
	{
		ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_GENERAL));
		return;
	}
	if (TranslateSourceCode(pDatabase, szMimicsNames[0], m_cLayout.GetSourceCode(), szData[0], szParameters[0], szParameters[1], szStaticParameters, szVolatileParameters, szPastProcedures, szPastProcedureParameters, szPastParameters, nPastSamples[0], szTriggerProcedures, bTriggerFlags))
	{
		if (cFile.Open(GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDESCRIPTIONFILE_COMPILENAME)), CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
		{
			for (nParameter = 0, nParameters = (INT)szParameters[0].GetSize(); (!nParameter && !nParameters) || nParameter < nParameters; nParameter++)
			{
				szParameter.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_VARIABLES), (nParameters > 0) ? (LPCTSTR)szParameters[0].GetAt(nParameter) : EMPTYSTRING);
				szParameter = (!nParameter) ? ((nParameters > 0) ? (LPCTSTR)(CString(STRING(IDS_MIMICSDESCRIPTIONFILE_INCLUDES)) + STRING(IDS_MIMICSDESCRIPTIONFILE_EXTERNALS) + szParameter) : CString(STRING(IDS_MIMICSDESCRIPTIONFILE_INCLUDES)) + STRING(IDS_MIMICSDESCRIPTIONFILE_EXTERNALS)) : szParameter;
				szParameter += (!nParameters || nParameter == nParameters - 1) ? (LPCTSTR)(CString(CR) + CString(EOL) + CString(CR) + CString(EOL)) : EMPTYSTRING;
				if (!ConvertSourceCodeLineToData(szParameter, nFileData))
				{
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_GENERAL));
					break;
				}
				if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
				{
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_OPERATEFILE));
					break;
				}
			}
			if (nParameter < nParameters)
			{
				CleanupMimicsDescriptionBuildOutput(pDatabase);
				return;
			}
			for (nMimicsItem = 0, nMimicsItems = (INT)szMimicsNames[0].GetSize(); nMimicsItem < nMimicsItems; nMimicsItem++)
			{
				for (nDataPos[0] = 0, szName[0] = szMimicsNames[0].GetAt(nMimicsItem), szType[0] = szMimicsTypes[0].GetAt(nMimicsItem); nDataPos[0] < szName[0].GetLength(); nDataPos[0]++)
				{
					if (!_istalnum(szName[0].GetAt(nDataPos[0]))) szName[0].SetAt(nDataPos[0], STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SUBSTITUTE));
					continue;
				}
				szMimicsNames[1].Add(szName[0]);
				szMimicsTypes[1].Add(szType[0]);
				szDefinition.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHDEFINITION), (LPCTSTR)szType[0], (LPCTSTR)szName[0], (LPCTSTR)szType[0]);
				szDeclaration.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHDECLARATION), (LPCTSTR)szType[0], (LPCTSTR)szName[0], (LPCTSTR)szType[0], (LPCTSTR)szName[0]);
				szStatements = (nMimicsItem == nMimicsItems - 1) ? (szDefinition + szDeclaration + CR + EOL) : (szDefinition + szDeclaration);
				if (!ConvertSourceCodeLineToData(szStatements, nFileData))
				{
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_GENERAL));
					szMimicsNames[1].RemoveAll();
					szMimicsTypes[1].RemoveAll();
					break;
				}
				if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
				{
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_OPERATEFILE));
					szMimicsNames[1].RemoveAll();
					szMimicsTypes[1].RemoveAll();
					break;
				}
			}
			if (nMimicsItem < nMimicsItems)
			{
				CleanupMimicsDescriptionBuildOutput(pDatabase);
				return;
			}
			for (nMimicsItem = 0, nMimicsItems = (INT)szMimicsNames[1].GetSize(); nMimicsItem < nMimicsItems || (!nMimicsItem && !nMimicsItems); nMimicsItem++)
			{
				szStatements.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHOBJECTPROCEDURESTATEMENT), (nMimicsItem < nMimicsItems) ? (LPCTSTR)szMimicsNames[1].GetAt(nMimicsItem) : EMPTYSTRING, (nMimicsItem < nMimicsItems) ? (LPCTSTR)szMimicsTypes[1].GetAt(nMimicsItem) : EMPTYSTRING, (nMimicsItem < nMimicsItems) ? (LPCTSTR)szMimicsNames[1].GetAt(nMimicsItem) : EMPTYSTRING);
				szStatements = (nMimicsItem < nMimicsItems) ? ((!nMimicsItem) ? (LPCTSTR)(STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHOBJECTPROCEDUREHEADER) + szStatements) : (LPCTSTR)szStatements) : STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHOBJECTPROCEDUREHEADER);
				szStatements = (nMimicsItem >= nMimicsItems - 1) ? (szStatements + STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHOBJECTPROCEDURETRAILER)) : szStatements;
				if (!ConvertSourceCodeLineToData(szStatements, nFileData))
				{
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_GENERAL));
					szMimicsNames[1].RemoveAll();
					szMimicsTypes[1].RemoveAll();
					break;
				}
				if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
				{
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_OPERATEFILE));
					szMimicsNames[1].RemoveAll();
					szMimicsTypes[1].RemoveAll();
					break;
				}
			}
			if (nMimicsItem < nMimicsItems)
			{
				CleanupMimicsDescriptionBuildOutput(pDatabase);
				return;
			}
			for (nParameter = 0, nParameters = (INT)szParameters[0].GetSize(), szStatements = STRING(IDS_MIMICSDESCRIPTIONFILE_CHECKLONGLONGPARAMETERPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_CHECKULONGLONGPARAMETERPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_CHECKFLOATINGPOINTPARAMETERPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_CHECKSTRINGPARAMETERPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_CHECKPARAMETERUPDATEPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_GETVALUEPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_GETRAWVALUEPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_GETVALUETIMEPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_GETPASTVALUEPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_GETPASTRAWVALUEPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_GETPASTVALUETIMEPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_CALCULATEAVERAGEVALUEPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_GETSTATUSPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_GETTMBANDWIDTHPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_CONVERSIONPARAMETERPROCEDURES), szStatements += STRING(IDS_MIMICSDESCRIPTIONFILE_INITIALIZEPARAMETERSPROCEDUREHEADER); (!nParameter && !nParameters) || nParameter < nParameters; nParameter++)
			{
				szParameter.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_INITIALIZEPARAMETERSPROCEDURESTATEMENT), (nParameters > 0) ? (LPCTSTR)szParameters[0].GetAt(nParameter) : EMPTYSTRING, (nParameters > 0) ? (LPCTSTR)szParameters[0].GetAt(nParameter) : EMPTYSTRING, (nParameters > 0) ? (LPCTSTR)szParameters[0].GetAt(nParameter) : EMPTYSTRING, (nParameters > 0) ? (LPCTSTR)szParameters[0].GetAt(nParameter) : EMPTYSTRING, (nParameters > 0) ? (LPCTSTR)szParameters[0].GetAt(nParameter) : EMPTYSTRING);
				szParameter = (nParameters > 0) ? ((nParameter == nParameters - 1) ? (LPCTSTR)(szParameter + STRING(IDS_MIMICSDESCRIPTIONFILE_INITIALIZEPARAMETERSPROCEDURETRAILER)) : (LPCTSTR)szParameter) : STRING(IDS_MIMICSDESCRIPTIONFILE_INITIALIZEPARAMETERSPROCEDURETRAILER);
				szParameter = (!nParameter) ? (szStatements + szParameter) : szParameter;
				if (!ConvertSourceCodeLineToData(szParameter, nFileData))
				{
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_GENERAL));
					break;
				}
				if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
				{
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_OPERATEFILE));
					break;
				}
			}
			if (nParameter < nParameters)
			{
				CleanupMimicsDescriptionBuildOutput(pDatabase);
				return;
			}
			for (nParameter = 0, nParameters = (INT)max(szParameters[0].GetSize(), szPastParameters.GetSize()), szStatements.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_INITIALIZATIONPROCEDUREHEADER), (LPCTSTR)STRING(IDS_MMD_STATUSBAR_OBJECTDEFAULTNAME)); (!nParameter && !nParameters) || nParameter < nParameters; nParameter++)
			{
				szParameter.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_INITIALIZATIONPROCEDUREPARAMETERSTATEMENT), (nParameter < szParameters[0].GetSize()) ? (LPCTSTR)szParameters[0].GetAt(nParameter) : EMPTYSTRING, (nParameter < szParameters[0].GetSize()) ? (LPCTSTR)szParameters[0].GetAt(nParameter) : EMPTYSTRING);
				szParameter = (nParameter < szParameters[0].GetSize()) ? (LPCTSTR)szParameter : EMPTYSTRING;
				szStatements = (!nParameter) ? (szStatements + szParameter) : szParameter;
				szParameter.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_INITIALIZATIONPROCEDUREPASTPARAMETERSTATEMENT), (nParameter < szPastParameters.GetSize()) ? (LPCTSTR)szPastParameters.GetAt(nParameter) : EMPTYSTRING, (nParameter < nPastSamples[0].GetSize()) ? nPastSamples[0].GetAt(nParameter) : 0);
				szParameter = (nParameter < szPastParameters.GetSize() && nParameter < nPastSamples[0].GetSize()) ? (LPCTSTR)szParameter : EMPTYSTRING;
				szStatements = (nParameters > 0) ? ((nParameter == nParameters - 1) ? (LPCTSTR)(szStatements + szParameter + STRING(IDS_MIMICSDESCRIPTIONFILE_INITIALIZATIONPROCEDURETRAILER)) : (LPCTSTR)(szStatements + szParameter)) : (LPCTSTR)(szStatements + STRING(IDS_MIMICSDESCRIPTIONFILE_INITIALIZATIONPROCEDURETRAILER));
				if (!ConvertSourceCodeLineToData(szStatements, nFileData))
				{
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_GENERAL));
					break;
				}
				if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
				{
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_OPERATEFILE));
					break;
				}
			}
			if (nParameter < nParameters)
			{
				CleanupMimicsDescriptionBuildOutput(pDatabase);
				return;
			}
			for (nDataPos[0] = nDataPos[1] = 0, szParameters[2].RemoveAll(), szParameters[3].RemoveAll(); (nDataPos[1] = ((pDataPos = FindMimicsDescriptionLangaugeSourceCodeKeyword((LPCTSTR)szData[0], nDataPos[0], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)))) ? (INT)(pDataPos - (LPCTSTR)szData[0]) : -1) >= 0; nDataPos[0] = nDataPos[1], szParameters[2].RemoveAll(), szParameters[3].RemoveAll())
			{
				for (nDataPos[1] = nDataPos[1] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)); nDataPos[1] < szData[0].GetLength() && ((szDataPos = szData[0].GetAt(nDataPos[1])) == SPACE[0] || szDataPos == TAB || szDataPos == CR || szDataPos == EOL); nDataPos[1]++);
				for (nDataPos[2] = nDataPos[1], szName[0].Empty(), szName[1].Empty(); nDataPos[2] < szData[0].GetLength(); nDataPos[2]++)
				{
					if ((szDataPos = szData[0].GetAt(nDataPos[2])) == STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER) || nDataPos[1] < nDataPos[2])
					{
						if (nDataPos[1] < nDataPos[2] && szDataPos != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER))
						{
							szName[0] += (_istalnum(szDataPos)) ? szDataPos : STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SUBSTITUTE);
							szName[1] += szDataPos;
						}
						if (nDataPos[1] == nDataPos[2] || szDataPos != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER)) continue;
					}
					break;
				}
				for (nMimicsItem = 0; nMimicsItem < nMimicsItems; nMimicsItem++)
				{
					if (szMimicsNames[1].GetAt(nMimicsItem) == szName[0]) break;
					continue;
				}
				if (nMimicsItem < nMimicsItems)
				{
					szProcedure.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDUREHEADER), (LPCTSTR)szMimicsTypes[0].GetAt(nMimicsItem), (LPCTSTR)szName[0], (LPCTSTR)szName[1]);
					for (nTrigger = 0, nTriggers = (INT)szTriggerProcedures.GetSize(), szImplementedProcedures.Add(szName[1]); nTrigger < nTriggers; nTrigger++)
					{
						if (szTriggerProcedures.GetAt(nTrigger) == szName[1]) break;
						continue;
					}
					if ((pKeyPos[0] = (LPTSTR)FindMimicsDescriptionLangaugeSourceCodeKeyword((LPCTSTR)szData[0], nDataPos[2], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN))) != (LPTSTR)NULL)
					{
						if ((pKeyPos[1] = (LPTSTR)FindMimicsDescriptionLangaugeSourceCodeKeyword((LPCTSTR)szData[0], nDataPos[2], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_END))) && pKeyPos[0] <= pKeyPos[1] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN)))
						{
							for (CopyMemory(szStatements.GetBufferSetLength((INT)(pKeyPos[1] - pKeyPos[0] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN)))), pKeyPos[0] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN)), (pKeyPos[1] - pKeyPos[0] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN)))*sizeof(TCHAR)); TRUE; )
							{
								szStatements.ReleaseBuffer();
								break;
							}
							if ((szStatements = (_tcsspn(szStatements, CString(SPACE) + TAB + CR + EOL) < (size_t)szStatements.GetLength()) ? (LPCTSTR)szStatements : EMPTYSTRING).GetLength() > 0 || (nTrigger < nTriggers  &&  bTriggerFlags.GetAt(nTrigger)))
							{
								for (nParameter = FindParameter(szParameters[1], szName[1]), nParameters = (INT)szParameters[1].GetSize(); nParameter >= 0 && nParameter < nParameters; nParameter++)
								{
									if (szParameters[1].GetAt(nParameter).Left(szName[1].GetLength() + 1) == szName[1] + EOL)
									{
										for (nDataPos[3] = 0, szArgument.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_PARAMETERARGUMENT), (LPCTSTR)szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)); nDataPos[3] < szStatements.GetLength(); nDataPos[3] += nDataPos[4] + 1)
										{
											if ((nDataPos[4] = szStatements.Mid(nDataPos[3]).Find(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1))) >= 0)
											{
												if (((nDataPos[3] + nDataPos[4] == 0 || !GetDatabase()->CheckTMParameterTag(szStatements.Mid(nDataPos[3] + nDataPos[4] - 1, szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1).GetLength()))) && (nDataPos[3] + nDataPos[4] + szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1).GetLength() == szStatements.GetLength() || !GetDatabase()->CheckTMParameterTag(szStatements.Mid(nDataPos[3] + nDataPos[4] + 1, szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1).GetLength())))) || (nDataPos[3] + nDataPos[4] - szArgument.Find(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) >= 0 && szStatements.Mid(nDataPos[3] + nDataPos[4] - szArgument.Find(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)), szArgument.GetLength()) == szArgument))
												{
													for (nDataPos[5] = nDataPos[3] + nDataPos[4] + szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1).GetLength(); nDataPos[5] < szStatements.GetLength(); nDataPos[5]++)
													{
														if ((szDataPos = szStatements.GetAt(nDataPos[5])) != SPACE[0] && szDataPos != TAB  &&  szDataPos != CR  &&  szDataPos != EOL)
														{
															if ((nDataPos[3] + nDataPos[4] > 0 && GetDatabase()->CheckTMParameterTag(szStatements.Mid(nDataPos[3] + nDataPos[4] - 1, szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1).GetLength()))) || (nDataPos[3] + nDataPos[4] + szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1).GetLength() < szStatements.GetLength() && GetDatabase()->CheckTMParameterTag(szStatements.Mid(nDataPos[3] + nDataPos[4] + 1, szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1).GetLength()))))
															{
																if ((nDataPos[7] = (nDataPos[6] = nDataPos[3] + nDataPos[4] - szArgument.Find(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1))) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTINTVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTINTVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTUINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTUINTVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTUINTVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTFLOATVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTFLOATVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTFLOATVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTSTRINGVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTSTRINGVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTSTRINGVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALINTVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALINTVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALUINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALUINTVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALUINTVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALFLOATVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALFLOATVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALFLOATVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWINTVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWINTVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWUINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWUINTVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWUINTVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWFLOATVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWFLOATVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWFLOATVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTVALUETIME))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTVALUETIME), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTVALUETIME))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEINTVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEINTVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEUINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEUINTVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEUINTVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
																if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEFLOATVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEFLOATVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEFLOATVALUE))))
																{
																	if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
																	break;
																}
															}
															if (!szParameters[2].GetSize() || szParameters[2].GetAt(szParameters[2].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) szParameters[2].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
															break;
														}
													}
												}
												continue;
											}
											break;
										}
										if ((!szParameters[2].GetSize() || szParameters[2].GetAt(szParameters[2].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)) && (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1)))
										{
											if (nTrigger < nTriggers  &&  bTriggerFlags.GetAt(nTrigger))
											{
												szParameters[2].Add(szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
												continue;
											}
											szWarning.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEWARNING_UNUSEDPARAMETER), (LPCTSTR)szName[1], (LPCTSTR)szParameters[1].GetAt(nParameter).Mid(szName[1].GetLength() + 1));
											ShowWarning(szWarning);
										}
										continue;
									}
									break;
								}
								for (nParameter = 0, nParameters = (INT)szParameters[2].GetSize(); nParameter < nParameters; nParameter++)
								{
									if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szParameters[2].GetAt(nParameter)))))
									{
										if ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)))
										{
											szVariable.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDUREFLOATVARIABLE), (LPCTSTR)szParameters[2].GetAt(nParameter));
											szProcedure += szVariable;
											continue;
										}
										if (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
										{
											szVariable.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDURESTRINGVARIABLE), (LPCTSTR)szParameters[2].GetAt(nParameter));
											szProcedure += szVariable;
											continue;
										}
										if ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
										{
											szVariable.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDUREINTVARIABLE), (LPCTSTR)szParameters[2].GetAt(nParameter));
											szProcedure += szVariable;
											continue;
										}
										szVariable.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDUREUINTVARIABLE), (LPCTSTR)szParameters[2].GetAt(nParameter));
										szProcedure += szVariable;
									}
								}
								if (szParameters[2].GetSize() + szParameters[3].GetSize() > 0)
								{
									szProcedure += STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDURESTATUSVARIABLE);
									szProcedure += CString(CR) + CString(EOL);
								}
								for (nParameter = 0, nParameters = (INT)szParameters[2].GetSize(); nParameter < nParameters; nParameter++)
								{
									if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szParameters[2].GetAt(nParameter)))))
									{
										szCheck.Format((FindParameter(szVolatileParameters, szName[1] + EOL + pDatabaseTMParameter->GetTag(), FALSE) < 0) ? STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDURECHECKSOURCEVARIABLE) : STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDURECHECKVOLATILESOURCEVARIABLE), (LPCTSTR)szParameters[2].GetAt(nParameter), (LPCTSTR)szParameters[2].GetAt(nParameter));
										szProcedure += szCheck;
									}
								}
								for (nParameter = 0, nParameters = (INT)szParameters[3].GetSize(); nParameter < nParameters; nParameter++)
								{
									if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szParameters[3].GetAt(nParameter)))))
									{
										for (nSample = 0, nSamples = GetParameterPastSamples(szName[1], szParameters[3].GetAt(nParameter), szPastProcedures, szPastProcedureParameters, nPastSamples[1]); nSample < nSamples; nSample++)
										{
											szCheck.Format((FindParameter(szVolatileParameters, szName[1] + EOL + pDatabaseTMParameter->GetTag(), FALSE) < 0) ? STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDURECHECKPASTSOURCEVARIABLE) : STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDURECHECKVOLATILEPASTSOURCEVARIABLE), (LPCTSTR)szParameters[3].GetAt(nParameter), nPastSamples[1].GetAt(nSample));
											szProcedure += szCheck;
										}
									}
								}
								for (nParameter = 0, nParameters = (nTrigger == nTriggers || bTriggerFlags.GetAt(nTrigger)) ? (INT)(szParameters[2].GetSize() + szParameters[3].GetSize()) : 0; nParameter < nParameters; nParameter++)
								{
									if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find((nParameter < szParameters[2].GetSize()) ? szParameters[2].GetAt(nParameter) : szParameters[3].GetAt(nParameter - szParameters[2].GetSize())))))
									{
										for (nStaticParameter = 0, nStaticParameters = (INT)szStaticParameters.GetSize(); nStaticParameter < nStaticParameters; nStaticParameter++)
										{
											if (szStaticParameters.GetAt(nStaticParameter) == szName[1] + EOL + pDatabaseTMParameter->GetTag()) break;
											continue;
										}
										if (nStaticParameter == nStaticParameters)
										{
											szCheck.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDURECHECKUPDATEVARIABLE), (nParameter < szParameters[2].GetSize()) ? (LPCTSTR)szParameters[2].GetAt(nParameter) : (LPCTSTR)szParameters[3].GetAt(nParameter - szParameters[2].GetSize()));
											szProcedure += szCheck;
										}
									}
								}
								for (szProcedure += (nParameters > 0) ? STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTPROCEDURECHECKRETURNVARIABLE) : EMPTYSTRING, nDataPos[3] = nDataPos[4] = 0; nDataPos[3] < szStatements.GetLength() && ((szDataPos = szStatements.GetAt(nDataPos[3])) == SPACE[0] || szDataPos == CR || szDataPos == EOL); nDataPos[3]++)
								{
									if (szDataPos == CR || szDataPos == EOL)
									{
										nDataPos[4] = nDataPos[3] + 1;
										continue;
									}
								}
								for (nDataPos[3] = nDataPos[5] = szStatements.GetLength() - 1; nDataPos[3] > nDataPos[4] && ((szDataPos = szStatements.GetAt(nDataPos[3])) == SPACE[0] || szDataPos == CR || szDataPos == EOL); nDataPos[3]--)
								{
									if (szDataPos == CR || szDataPos == EOL)
									{
										nDataPos[5] = nDataPos[3] - 1;
										continue;
									}
								}
								szProcedure += STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDURESTATEMENTSPROLOG) + szStatements.Mid(nDataPos[4], nDataPos[5] - nDataPos[4] + 1) + CString(CR) + CString(EOL) + STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDURESTATEMENTSEPILOG);
							}
							else
							{
								if (FindParameter(szParameters[1], szName[1]) >= 0)
								{
									szWarning.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEWARNING_EMPTYPROCEDURE), (LPCTSTR)szName[1]);
									ShowWarning(szWarning);
								}
							}
							if (ConvertSourceCodeLineToData((!szStatements.IsEmpty()) ? (szProcedure + STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDURETRAILER)) : (szProcedure + STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDUREEMPTYTRAILER)), nFileData))
							{
								if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
								{
									ShowError((szError = STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_OPERATEFILE)));
									break;
								}
								continue;
							}
						}
					}
					ShowError((szError = STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_GENERAL)));
					break;
				}
			}
			for (nMimicsItem = 0, nMimicsItems = (INT)szMimicsNames[0].GetSize(); nMimicsItem < nMimicsItems; nMimicsItem++)
			{
				for (nProcedure = 0, nProcedures = (INT)szImplementedProcedures.GetSize(); nProcedure < nProcedures; nProcedure++)
				{
					if (szMimicsNames[0].GetAt(nMimicsItem) == szImplementedProcedures.GetAt(nProcedure)) break;
					continue;
				}
				if (nProcedure == nProcedures)
				{
					szProcedure.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDUREDUMMY), (LPCTSTR)szMimicsTypes[0].GetAt(nMimicsItem), (LPCTSTR)szMimicsNames[1].GetAt(nMimicsItem), (LPCTSTR)szMimicsNames[0].GetAt(nMimicsItem));
					if (ConvertSourceCodeLineToData(szProcedure, nFileData))
					{
						if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
						{
							ShowError((szError = STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_OPERATEFILE)));
							break;
						}
					}
				}
			}
			cFile.Close();
		}
		else  ShowError((szError = STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_OPERATEFILE)));
	}
	else
	{
		CleanupMimicsDescriptionBuildOutput(pDatabase);
		return;
	}
	if (!szError.IsEmpty())
	{
		CleanupMimicsDescriptionBuildOutput(pDatabase);
		return;
	}
	sCompilerSecurityAttributes.bInheritHandle = TRUE;
	sCompilerSecurityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	if (CreatePipe(&hStdOut[0], &hStdOut[1], &sCompilerSecurityAttributes, 0))
	{
		if (CreatePipe(&hStdIn[0], &hStdIn[1], &sCompilerSecurityAttributes, 0))
		{
			if (DuplicateHandle(GetCurrentProcess(), hStdOut[1], GetCurrentProcess(), &hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS) && DuplicateHandle(GetCurrentProcess(), hStdOut[0], GetCurrentProcess(), &hStdOut[2], 0, FALSE, DUPLICATE_SAME_ACCESS) && DuplicateHandle(GetCurrentProcess(), hStdIn[1], GetCurrentProcess(), &hStdIn[2], 0, FALSE, DUPLICATE_SAME_ACCESS))
			{
				sCompilerStartupInformation.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
				sCompilerStartupInformation.cb = sizeof(STARTUPINFO);
				sCompilerStartupInformation.hStdOutput = hStdOut[1];
				sCompilerStartupInformation.hStdInput = hStdIn[0];
				sCompilerStartupInformation.hStdError = hStdError;
				sCompilerStartupInformation.wShowWindow = SW_HIDE;
				for (szFileName[0] = GetMimicsDescriptionCompilerFileName(), szOptions = GetMimicsDescriptionCompileOptions(pDatabase), CloseHandle(hStdOut[0]), CloseHandle(hStdIn[1]); CreateProcess(szFileName[0], (LPTSTR)(LPCTSTR)szOptions, (LPSECURITY_ATTRIBUTES)NULL, (LPSECURITY_ATTRIBUTES)NULL, TRUE, CREATE_NEW_CONSOLE | IDLE_PRIORITY_CLASS, (LPVOID)NULL, (LPCTSTR)NULL, &sCompilerStartupInformation, &sCompilerInformation); )
				{
					for (CloseHandle(hStdIn[0]), CloseHandle(hStdOut[1]), CloseHandle(hStdError), cbOut = 0; WaitForSingleObject(sCompilerInformation.hProcess, 0) == WAIT_TIMEOUT; )
					{
						if (ReadFile(hStdOut[2], szOut, sizeof(szOut), &dwOut, (LPOVERLAPPED)NULL) && dwOut > 0)
						{
							cbOut += dwOut;
#ifndef UNICODE
							CopyMemory(szError.GetBufferSetLength(dwOut), szOut, dwOut);
							szError.ReleaseBuffer();
#else
							MultiByteToWideChar(CP_ACP, 0, szOut, dwOut, szError.GetBufferSetLength(dwOut), dwOut + 1);
							szError.ReleaseBuffer();
#endif
							if (szErrors.IsEmpty())
							{
								if (cFileFind.FindFile(GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDESCRIPTIONFILE_COMPILENAME))) && !cFileFind.FindNextFile())
								{
									szMessage = szError;
									szMessage.MakeLower();
									szFileName[1] = cFileFind.GetFilePath();
									szFileName[2] = cFileFind.GetFileName();
									szFileName[1].MakeLower();
									szFileName[2].MakeLower();
									if ((nDataPos[8] = szMessage.Find(szFileName[2])) >= 0 && (szError.GetAt(nDataPos[8] + szFileName[2].GetLength()) == CR || szError.GetAt(nDataPos[8] + szFileName[2].GetLength()) == EOL))
									{
										for (szError = szError.Mid(nDataPos[8] + szFileName[2].GetLength()); szError.GetLength() > 0; )
										{
											if (szError.GetAt(0) == CR || szError.GetAt(0) == EOL)
											{
												szError = szError.Mid(1);
												continue;
											}
											break;
										}
										szErrors = szError;
										cFileFind.Close();
										continue;
									}
									if ((nDataPos[8] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILECOMMANDLINEPREFIX))) >= 0)
									{
										szErrors = szError.Mid(nDataPos[8]);
										cFileFind.Close();
										continue;
									}
									if ((nDataPos[8] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILEFATALERRORPREFIX))) >= 0)
									{
										szErrors = szError.Mid(nDataPos[8]);
										cFileFind.Close();
										continue;
									}
									if ((nDataPos[8] = szMessage.Find(szFileName[1])) >= 0)
									{
										szErrors = szError.Mid(nDataPos[8]);
										cFileFind.Close();
										continue;
									}
									for (; _tcsstr(szMessage, STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILEFATALERRORPREFIX)) || _tcsstr(szMessage, STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILEERRORPREFIX)) || _tcsstr(szMessage, STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILEWARNINGPREFIX)); )
									{
										szErrors = szError;
										break;
									}
									cFileFind.Close();
									continue;
								}
								szMessage = szError;
								szMessage.MakeLower();
								szErrors = (szErrors.IsEmpty()) ? (((nDataPos[8] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILECOMMANDLINEPREFIX))) >= 0) ? szError.Mid(nDataPos[8]) : szErrors) : szErrors;
								szErrors = (szErrors.IsEmpty()) ? (((nDataPos[8] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILEFATALERRORPREFIX))) >= 0) ? szError.Mid(nDataPos[8]) : szErrors) : szErrors;
								continue;
							}
							szErrors += szError;
						}
					}
					if (!cbOut)
					{
						szError = STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILERENVIRONMENT);
						ShowError(szError);
					}
					for (ShowMimicsDescriptionCompilerErrors(pDatabase, szErrors); !szErrors.IsEmpty() || !cbOut; )
					{
						CleanupMimicsDescriptionBuildOutput(pDatabase);
						CloseHandle(hStdOut[2]);
						CloseHandle(hStdIn[2]);
						return;
					}
					CloseHandle(hStdIn[2]);
					CloseHandle(hStdOut[2]);
					if (CreatePipe(&hStdOut[0], &hStdOut[1], &sCompilerSecurityAttributes, 0))
					{
						if (CreatePipe(&hStdIn[0], &hStdIn[1], &sCompilerSecurityAttributes, 0))
						{
							if (DuplicateHandle(GetCurrentProcess(), hStdOut[1], GetCurrentProcess(), &hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS) && DuplicateHandle(GetCurrentProcess(), hStdOut[0], GetCurrentProcess(), &hStdOut[2], 0, FALSE, DUPLICATE_SAME_ACCESS) && DuplicateHandle(GetCurrentProcess(), hStdIn[1], GetCurrentProcess(), &hStdIn[2], 0, FALSE, DUPLICATE_SAME_ACCESS))
							{
								sCompilerStartupInformation.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
								sCompilerStartupInformation.cb = sizeof(STARTUPINFO);
								sCompilerStartupInformation.hStdOutput = hStdOut[1];
								sCompilerStartupInformation.hStdInput = hStdIn[0];
								sCompilerStartupInformation.hStdError = hStdError;
								sCompilerStartupInformation.wShowWindow = SW_HIDE;
								for (szFileName[0] = GetMimicsDescriptionLinkerFileName(), szOptions = GetMimicsDescriptionLinkOptions(pDatabase), szOutputName = GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDISPLAYCODE_NORMAL_FILENAME), IsSyntaxCompileTarget()), CFileEx::SetAttributes(szOutputName, CFileEx::GetAttributes(szOutputName) & ~FILE_ATTRIBUTE_READONLY), CloseHandle(hStdOut[0]), CloseHandle(hStdIn[1]); CreateProcess(szFileName[0], (LPTSTR)(LPCTSTR)szOptions, (LPSECURITY_ATTRIBUTES)NULL, (LPSECURITY_ATTRIBUTES)NULL, TRUE, CREATE_NEW_CONSOLE | IDLE_PRIORITY_CLASS, (LPVOID)NULL, (LPCTSTR)NULL, &sCompilerStartupInformation, &sCompilerInformation); )
								{
									for (CloseHandle(hStdIn[0]), CloseHandle(hStdOut[1]), CloseHandle(hStdError), szErrors.Empty(), szError.Empty(), cbOut = 0; WaitForSingleObject(sCompilerInformation.hProcess, 0) == WAIT_TIMEOUT; )
									{
										if (ReadFile(hStdOut[2], szOut, sizeof(szOut) - 1, &dwOut, (LPOVERLAPPED)NULL) && dwOut > 0)
										{
											cbOut += dwOut;
#ifndef UNICODE
											CopyMemory(szError.GetBufferSetLength(dwOut), szOut, dwOut);
											szError.ReleaseBuffer();
#else
											MultiByteToWideChar(CP_ACP, 0, szOut, dwOut, szError.GetBufferSetLength(dwOut), dwOut + 1);
											szError.ReleaseBuffer();
#endif
											szOut[dwOut] = EOS;
											szErrors += szOut;
										}
									}
									if (!cbOut)
									{
										szError = STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_LINKERENVIRONMENT);
										ShowError(szError);
									}
									if (cFileFind.FindFile(GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTNAME))) && !cFileFind.FindNextFile())
									{
										szMessage = szErrors;
										szMessage.MakeLower();
										szFileName[1] = cFileFind.GetFileName();
										szFileName[1].MakeLower();
										szError = ((nDataPos[8] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_LINKFATALERRORPREFIX))) >= 0) ? (LPCTSTR)szErrors.Mid(nDataPos[8]) : EMPTYSTRING;
										szError = ((nDataPos[8] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_LINKERRORPREFIX))) >= 0) ? szErrors.Mid(nDataPos[8]) : szError;
										szError = ((nDataPos[8] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_LINKWARNINGPREFIX))) >= 0) ? szErrors.Mid(nDataPos[8]) : szError;
										szError = ((nDataPos[8] = szMessage.Find(szFileName[1])) >= 0) ? szErrors.Mid(nDataPos[8]) : szError;
										cFileFind.Close();
									}
									for (ShowMimicsDescriptionLinkerErrors(pDatabase, (szErrors = (cbOut > 0) ? (LPCTSTR)szError : EMPTYSTRING)); !IsSyntaxCompileTarget(); )
									{
										CFileEx::SetAttributes(szOutputName, CFileEx::GetAttributes(szOutputName) | FILE_ATTRIBUTE_READONLY);
										SecureMimicsDescriptionFile(szOutputName);
										break;
									}
									if (IsSyntaxCompileTarget()) CFileEx::Remove(szOutputName);
									CleanupMimicsDescriptionBuildOutput(pDatabase);
									CloseHandle(hStdOut[2]);
									CloseHandle(hStdIn[2]);
									return;
								}
								CloseHandle(hStdIn[0]);
								CloseHandle(hStdIn[2]);
								CloseHandle(hStdOut[1]);
								CloseHandle(hStdOut[2]);
								CloseHandle(hStdError);
								CleanupMimicsDescriptionBuildOutput(pDatabase);
								ShowError((!cFileFind.FindFile(szFileName[0])) ? STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_LINKERPATH) : STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_STDINOUT));
								return;
							}
							CloseHandle(hStdIn[0]);
							CloseHandle(hStdIn[1]);
						}
						CloseHandle(hStdOut[0]);
						CloseHandle(hStdOut[1]);
					}
					CleanupMimicsDescriptionBuildOutput(pDatabase);
					ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_STDINOUT));
					return;
				}
				CloseHandle(hStdIn[0]);
				CloseHandle(hStdIn[2]);
				CloseHandle(hStdOut[1]);
				CloseHandle(hStdOut[2]);
				CloseHandle(hStdError);
				CleanupMimicsDescriptionBuildOutput(pDatabase);
				ShowError((!cFileFind.FindFile(szFileName[0])) ? STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILERPATH) : STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_STDINOUT));
				return;
			}
			CloseHandle(hStdIn[0]);
			CloseHandle(hStdIn[1]);
		}
		CloseHandle(hStdOut[0]);
		CloseHandle(hStdOut[1]);
	}
	ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_STDINOUT));
	CleanupMimicsDescriptionBuildOutput(pDatabase);
}

VOID CMMDCompileThread::CloseCompileTarget()
{
	m_cLayout.RemoveAll();
	m_bCompilation[1].SetEvent();
}

BOOL CMMDCompileThread::TranslateSourceCode(CONST CBinaryDatabase *pDatabase, CONST CStringArray &szNames, LPCTSTR pszData, CString &szData, CStringArray &szGlobalParameters, CStringArray &szLocalParameters, CStringArray &szStaticParameters, CStringArray &szVolatileParameters, CStringArray &szPastProcedures, CStringArray &szPastProcedureParameters, CStringArray &szPastParameters, CUIntArray &nPastSamples, CStringArray &szTriggerProcedures, CByteArray &bTriggerFlags)
{
	INT  nItem;
	INT  nItems;
	INT  nPos[12];
	INT  nDiff[2];
	INT  nLevels;
	INT  nErrors;
	INT  nSamples;
	INT  nProcedure;
	INT  nProcedures;
	INT  nParameter;
	INT  nParameters;
	BOOL  bStatic;
	TCHAR  szChar;
	LPCTSTR  pPos;
	CString  szError;
	CString  szMacro;
	CString  szDigit[2];
	CString  szProcedure;
	CString  szParameter;
	CString  szSeparator;
	CString  szArgument[2];
	CStringTools  cStringTools;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CUIntArray  nSourceCodeLines;

	for (CalculateSourceCodeLines(pszData, nSourceCodeLines), szData = pszData, szGlobalParameters.RemoveAll(), szLocalParameters.RemoveAll(), szStaticParameters.RemoveAll(), szVolatileParameters.RemoveAll(), szPastProcedures.RemoveAll(), szPastProcedureParameters.RemoveAll(), szPastParameters.RemoveAll(), nPastSamples.RemoveAll(), szTriggerProcedures.RemoveAll(), bTriggerFlags.RemoveAll(), m_szLines.RemoveAll(), nPos[0] = nPos[1] = 0, nDiff[0] = nDiff[1] = 0, nLevels = 0, nErrors = 0; TRUE; )
	{
		nPos[2] = szData.Mid(nPos[1]).Find(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_BEGINCOMMENTS));
		nPos[3] = szData.Mid(nPos[1]).Find(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_ENDCOMMENTS));
		if (nPos[2] >= 0 && (nPos[2] < nPos[3] || nPos[3] < 0))
		{
			nPos[0] = (!nLevels) ? (nPos[1] + nPos[2]) : nPos[0];
			nPos[1] += nPos[2] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_BEGINCOMMENTS));
			nLevels++;
			continue;
		}
		if (nPos[3] >= 0 && nLevels > 0)
		{
			szData = (--nLevels == 0) ? (szData.Left(nPos[0]) + CString(SPACE[0], nPos[1] + nPos[3] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_ENDCOMMENTS)) - nPos[0]) + szData.Mid(nPos[1] + nPos[3] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_ENDCOMMENTS)))) : szData;
			nPos[1] += nPos[3] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_ENDCOMMENTS));
			continue;
		}
		if ((nPos[3] < 0 && nLevels > 0) || (nPos[3] >= 0 && !nLevels))
		{
			szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_MISMATCHINGCOMMENTSYMBOL), DetermineSourceCodeLine(nSourceCodeLines, (nPos[3] < 0 && nLevels > 0) ? (lstrlen(pszData) - 1) : nPos[3]), DetermineSourceCodeColumn(nSourceCodeLines, (nPos[3] < 0 && nLevels > 0) ? (lstrlen(pszData) - 1) : nPos[3]));
			ShowError(szError);
			nErrors++;
		}
		break;
	}
	for (nPos[0] = 0; TRUE; )
	{
		if ((nPos[1] = szData.Mid(nPos[0]).Find(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_LINECOMMENTS))) >= 0)
		{
			if ((nPos[2] = szData.Mid(nPos[0] + nPos[1]).Find(CString(CR) + CString(EOL))) >= 0)
			{
				szData = szData.Left(nPos[0] + nPos[1]) + CString(SPACE[0], nPos[2]) + szData.Mid(nPos[0] + nPos[1] + nPos[2]);
				nPos[0] += nPos[1] + nPos[2] + 2;
				continue;
			}
			if ((nPos[2] = szData.Mid(nPos[0] + nPos[1]).Find(CString(CR))) >= 0)
			{
				szData = szData.Left(nPos[0] + nPos[1]) + CString(SPACE[0], nPos[2]) + szData.Mid(nPos[0] + nPos[1] + nPos[2]);
				nPos[0] += nPos[1] + nPos[2] + 1;
				continue;
			}
			if ((nPos[2] = szData.Mid(nPos[0] + nPos[1]).Find(CString(EOL))) >= 0)
			{
				szData = szData.Left(nPos[0] + nPos[1]) + CString(SPACE[0], nPos[2]) + szData.Mid(nPos[0] + nPos[1] + nPos[2]);
				nPos[0] += nPos[1] + nPos[2] + 1;
				continue;
			}
			szData = szData.Left(nPos[0] + nPos[1]);
		}
		break;
	}
	for (nPos[0] = 0; (nPos[1] = ((pPos = FindMimicsDescriptionLangaugeSourceCodeKeyword((LPCTSTR)szData, nPos[0], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)))) ? (INT)(pPos - (LPCTSTR)szData - nPos[0]) : -1) >= 0; )
	{
		nPos[2] = ((pPos = FindMimicsDescriptionLangaugeSourceCodeKeyword((LPCTSTR)szData, nPos[0], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PARAMETERS)))) ? (INT)(pPos - (LPCTSTR)szData - nPos[0]) : -1;
		nPos[3] = ((pPos = FindMimicsDescriptionLangaugeSourceCodeKeyword((LPCTSTR)szData, nPos[0], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN)))) ? (INT)(pPos - (LPCTSTR)szData - nPos[0]) : -1;
		nPos[4] = ((pPos = FindMimicsDescriptionLangaugeSourceCodeKeyword((LPCTSTR)szData, nPos[0], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_END)))) ? (INT)(pPos - (LPCTSTR)szData - nPos[0]) : -1;
		nPos[5] = ((pPos = FindMimicsDescriptionLangaugeSourceCodeKeyword((LPCTSTR)szData, nPos[0] + nPos[1] + 1, STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)))) ? (INT)(pPos - (LPCTSTR)szData - nPos[0]) : -1;
		if (nPos[1] < nPos[2] || nPos[2] < 0)
		{
			if (nPos[1] < nPos[3] && (nPos[2] < 0 || nPos[2] > nPos[4] || nPos[2] < nPos[3]))
			{
				if (nPos[1] < nPos[4] && (nPos[2] < 0 || nPos[2] > nPos[4] || nPos[2] < nPos[4]) && nPos[3] < nPos[4] && (nPos[4] < nPos[5] || nPos[5] < 0))
				{
					for (nPos[5] = nPos[0] + nPos[1] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)), szProcedure.Empty(), szError.Empty(); (nPos[2] < 0 || nPos[5] < nPos[0] + nPos[2]) && nPos[5] < nPos[0] + nPos[3]; nPos[5]++)
					{
						if ((szChar = szData.GetAt(nPos[5])) == STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER))
						{
							if (szProcedure.IsEmpty())
							{
								szProcedure = szChar;
								continue;
							}
							break;
						}
						if (!szProcedure.IsEmpty() && szChar != TAB  &&  szChar != CR  &&  szChar != EOL)
						{
							szProcedure = (szProcedure != STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER)) ? (szProcedure + szData.GetAt(nPos[5])) : szData.GetAt(nPos[5]);
							continue;
						}
						if (szChar != SPACE[0])
						{
							szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_MISSINGDELIMITERSYMBOL), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
							ShowError(szError);
							nErrors++;
							break;
						}
					}
					if (szError.IsEmpty())
					{
						for (nItem = 0, nItems = (INT)szNames.GetSize(); nItem < nItems; nItem++)
						{
							if (szNames.GetAt(nItem) == szProcedure) break;
							continue;
						}
						if (szProcedure == STRING(IDS_MMD_STATUSBAR_OBJECTDEFAULTNAME) || nItem == nItems)
						{
							szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALPROCEDURENAME), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1] - szProcedure.GetLength()), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1] - szProcedure.GetLength()), (LPCTSTR)szProcedure);
							ShowError(szError);
							nErrors++;
						}
					}
					for (nPos[5] = nPos[0] + nPos[1] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)); (nPos[2] < 0 || nPos[5] < nPos[0] + nPos[2]) && nPos[5] < nPos[0] + nPos[3]; nPos[5]++)
					{
						if ((szChar = szData.GetAt(nPos[5])) == STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER))
						{
							nPos[5] += (szData.GetAt((nPos[5] = nPos[5] + szProcedure.GetLength() + 1)) == szChar) ? 1 : 0;
							continue;
						}
						if (szChar != SPACE[0] && szChar != TAB  &&  szChar != CR  &&  szChar != EOL) break;
					}
					for (; (nPos[2] < 0 || nPos[5] < nPos[0] + nPos[2]) && nPos[5] < nPos[0] + nPos[3]; nPos[5]++)
					{
						if ((szChar = szData.GetAt(nPos[5])) != SPACE[0] && szChar != TAB  &&  szChar != CR  &&  szChar != EOL) break;
						continue;
					}
					if (!_tcsncmp((LPCTSTR)szData + nPos[5], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PARAMETERS), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PARAMETERS))) || !_tcsncmp((LPCTSTR)szData + nPos[5], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN))))
					{
						for (nPos[5] = nPos[0] + nPos[2] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PARAMETERS)), szSeparator.Empty(); nPos[2] >= 0 && nPos[2] < nPos[3] && nPos[5] < nPos[0] + nPos[3]; )
						{
							while ((szChar = szData.GetAt(nPos[5])) == SPACE[0] || szChar == TAB || szChar == CR || szChar == EOL)
							{
								if (++nPos[5] >= nPos[0] + nPos[3]) break;
								continue;
							}
							if (szData.GetAt(nPos[5]) != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_TERMINATOR))
							{
								for (nPos[6] = nPos[5], szParameter.Empty(), bStatic = FALSE; nPos[6] < nPos[0] + nPos[3] && ((!bStatic && szParameter.GetLength() <= max(GetDatabase()->GetTMParameterTagLength(), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_STATIC)) + 1)) || (bStatic && szParameter.GetLength() <= GetDatabase()->GetTMParameterTagLength())); nPos[6]++)
								{
									if (szData.Mid(nPos[5], nPos[6] - nPos[5] + 1) == STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_STATIC) && !bStatic)
									{
										if ((szChar = szData.GetAt(++nPos[6])) == SPACE[0] || szChar == TAB || szChar == CR || szChar == EOL)
										{
											for (szParameter.Empty(), bStatic = TRUE; nPos[6] < nPos[0] + nPos[3]; nPos[6]++)
											{
												if ((szChar = szData.GetAt(++nPos[6])) == SPACE[0]) continue;
												if (szChar == TAB || szChar == CR || szChar == EOL) continue;
												break;
											}
										}
									}
									if (GetDatabase()->CheckTMParameterTag(szParameter + szData.GetAt(nPos[6])))
									{
										szParameter += szData.GetAt(nPos[6]);
										continue;
									}
									break;
								}
								if (pDatabase->GetTMParameters()->Find(szParameter) >= 0)
								{
									for (CollectParameter(szParameter, szGlobalParameters); !CollectParameter(szProcedure + EOL + szParameter, szLocalParameters); )
									{
										szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_DUPLICATEPARAMETER), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
										ShowError(szError);
										nErrors++;
										break;
									}
									for (nParameter = 0, nParameters = (INT)szStaticParameters.GetSize(); nParameter < nParameters; nParameter++)
									{
										if (szStaticParameters.GetAt(nParameter) == szProcedure + EOL + szParameter) break;
										continue;
									}
									if (nParameter == nParameters  &&  bStatic) szStaticParameters.Add(szProcedure + EOL + szParameter);
									if (nParameter < nParameters  &&  !bStatic) szStaticParameters.RemoveAt(nParameter);
								}
								else
								{
									szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALPARAMETER), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
									ShowError(szError);
									nErrors++;
								}
								for (nPos[5] = nPos[6]; (szChar = szData.GetAt(nPos[5])) == SPACE[0] || szChar == TAB || szChar == CR || szChar == EOL; )
								{
									if (++nPos[5] >= nPos[0] + nPos[3]) break;
									continue;
								}
								if (szChar != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SEPARATOR) && szChar != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_TERMINATOR))
								{
									szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_MISSINGSEPARATORSYMBOL), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
									ShowError(szError);
									nErrors++;
									break;
								}
								nPos[5] = (szChar == STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SEPARATOR)) ? (nPos[5] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SEPARATOR))) : nPos[5];
								szSeparator = (szChar == STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SEPARATOR)) ? STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SEPARATOR) : EMPTYSTRING;
								continue;
							}
							else
							{
								if (!szSeparator.IsEmpty())
								{
									szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALPARAMETER), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
									ShowError(szError);
									nErrors++;
								}
							}
							break;
						}
						for (nPos[5] = (szData.GetAt(nPos[5]) == STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_TERMINATOR)) ? (nPos[5] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_TERMINATOR))) : nPos[5]; nPos[2] >= 0 && nPos[2] < nPos[3] && nPos[5] < nPos[0] + nPos[3]; nPos[5]++)
						{
							if ((szChar = szData.GetAt(nPos[5])) != SPACE[0] && szChar != TAB  &&  szChar != CR  &&  szChar != EOL) break;
							continue;
						}
						if (!_tcsncmp((LPCTSTR)szData + nPos[5], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_VOLATILE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_VOLATILE))))
						{
							for (nPos[5] = nPos[5] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_VOLATILE)); nPos[2] >= 0 && nPos[2] < nPos[3] && nPos[5] < nPos[0] + nPos[3]; )
							{
								while ((szChar = szData.GetAt(nPos[5])) == SPACE[0] || szChar == TAB || szChar == CR || szChar == EOL)
								{
									if (++nPos[5] >= nPos[0] + nPos[3]) break;
									continue;
								}
								if (szData.GetAt(nPos[5]) != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_TERMINATOR))
								{
									for (nPos[6] = nPos[5], szParameter.Empty(); nPos[6] < nPos[0] + nPos[3] && nPos[6] - nPos[5] <= GetDatabase()->GetTMParameterTagLength(); nPos[6]++)
									{
										if (GetDatabase()->CheckTMParameterTag(szParameter + szData.GetAt(nPos[6])))
										{
											szParameter += szData.GetAt(nPos[6]);
											continue;
										}
										break;
									}
									if (pDatabase->GetTMParameters()->Find(szParameter) >= 0)
									{
										if (FindParameter(szLocalParameters, szProcedure + EOL + szParameter) >= 0)
										{
											if (!CollectParameter(szProcedure + EOL + szParameter, szVolatileParameters))
											{
												szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_DUPLICATEPARAMETER), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
												ShowError(szError);
												nErrors++;
											}
										}
										else
										{
											szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALPARAMETER), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
											ShowError(szError);
											nErrors++;
										}
									}
									else
									{
										szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALPARAMETER), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
										ShowError(szError);
										nErrors++;
									}
									for (nPos[5] = nPos[6]; (szChar = szData.GetAt(nPos[5])) == SPACE[0] || szChar == TAB || szChar == CR || szChar == EOL; )
									{
										if (++nPos[5] >= nPos[0] + nPos[3]) break;
										continue;
									}
									if (szChar != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SEPARATOR) && szChar != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_TERMINATOR))
									{
										szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_MISSINGSEPARATORSYMBOL), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
										ShowError(szError);
										nErrors++;
										break;
									}
									nPos[5] = (szChar == STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SEPARATOR)) ? (nPos[5] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SEPARATOR))) : nPos[5];
									continue;
								}
								break;
							}
						}
						if ((nPos[10] = szData.Mid(nPos[0] + nPos[2], max(nPos[3] - nPos[2] + 1, 0)).Find(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_NOAUTOTRIGGER))) >= 0)
						{
							for (nPos[11] = 0; nPos[11] < lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_NOAUTOTRIGGER)); nPos[11]++)
							{
								szData.SetAt(nPos[0] + nPos[2] + nPos[10] + nPos[11], SPACE[0]);
								continue;
							}
							szTriggerProcedures.Add(szProcedure);
							bTriggerFlags.Add(FALSE);
						}
						if ((nPos[11] = szData.Mid(nPos[0] + nPos[2], max(nPos[3] - nPos[2] + 1, 0)).Find(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_AUTOTRIGGER))) >= 0 && nPos[10] < 0)
						{
							szTriggerProcedures.Add(szProcedure);
							bTriggerFlags.Add(TRUE);
						}
						if (nPos[10] >= 0 && nPos[11] >= 0)
						{
							szError.Format((nPos[10] < nPos[11]) ? STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALAUTOTRIGGERKEYWORD) : STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALNOAUTOTRIGGERKEYWORD), DetermineSourceCodeLine(nSourceCodeLines, nPos[0] + nPos[2] + max(nPos[10], nPos[11]) + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[0] + nPos[2] + max(nPos[10], nPos[11]) + nDiff[1]));
							ShowError(szError);
							nErrors++;
						}
						for (nProcedure = 0, nProcedures = MAXMIMICSDESCRIPTIONLANGUAGEPROCEDURE - MINMIMICSDESCRIPTIONLANGUAGEPROCEDURE, szData.SetAt(nPos[0] + nPos[4], EOS); nProcedure <= nProcedures; nProcedure++)
						{
							for (nPos[6] = nPos[0] + nPos[3]; nPos[6] < nPos[0] + nPos[4]; nPos[6] = nPos[7] + lstrlen(STRING(MINMIMICSDESCRIPTIONLANGUAGEPROCEDURE + nProcedure)))
							{
								if ((nPos[7] = ((pPos = _tcsstr((LPCTSTR)szData + nPos[6], STRING(MINMIMICSDESCRIPTIONLANGUAGEPROCEDURE + nProcedure)))) ? (INT)(pPos - (LPCTSTR)szData) : -1) >= 0)
								{
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITTAG), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITTAG))))
									{
										szData = szData.Left(nPos[7]) + STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTMUNITTAG) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITTAG)));
										nDiff[0] = lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTMUNITTAG)) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITTAG));
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITTIME), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITTIME))))
									{
										szData = szData.Left(nPos[7]) + STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTMUNITTIME) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITTIME)));
										nDiff[0] = lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTMUNITTIME)) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITTIME));
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITID), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITID))))
									{
										szData = szData.Left(nPos[7]) + STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTMUNITID) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITID)));
										nDiff[0] = lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTMUNITID)) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITID));
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITDATA), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITDATA))))
									{
										szData = szData.Left(nPos[7]) + STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTMUNITDATA) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITDATA)));
										nDiff[0] = lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTMUNITDATA)) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITDATA));
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITQUALITY), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITQUALITY))))
									{
										szData = szData.Left(nPos[7]) + STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTMUNITQUALITY) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITQUALITY)));
										nDiff[0] = lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTMUNITQUALITY)) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTMUNITQUALITY));
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTOTALTMBANDWIDTH), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTOTALTMBANDWIDTH))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME))))
									{
										for (nDiff[0] = 0; !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTOTALTMBANDWIDTH), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTOTALTMBANDWIDTH))); )
										{
											szData = szData.Left(nPos[7]) + STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTOTALTMBANDWIDTH) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTOTALTMBANDWIDTH)));
											nDiff[0] = lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETTOTALTMBANDWIDTH)) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETTOTALTMBANDWIDTH));
											break;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH))))
										{
											szData = szData.Left(nPos[7]) + STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETAVAILABLETMBANDWIDTH) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH)));
											nDiff[0] = lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETAVAILABLETMBANDWIDTH)) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH));
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH))))
										{
											szData = szData.Left(nPos[7]) + STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH)));
											nDiff[0] = lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH)) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH));
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH))))
										{
											szData = szData.Left(nPos[7]) + STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH)));
											nDiff[0] = lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH)) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH));
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME))))
										{
											szData = szData.Left(nPos[7]) + STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME)));
											nDiff[0] = lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME)) - lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME));
										}
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									for (nPos[8] = nPos[7] + lstrlen(STRING(MINMIMICSDESCRIPTIONLANGUAGEPROCEDURE + nProcedure)); nPos[8] < nPos[0] + nPos[4]; nPos[8]++)
									{
										if ((szChar = szData.GetAt(nPos[8])) != SPACE[0] && szChar != TAB  &&  szChar != CR  &&  szChar != EOL) break;
										continue;
									}
									for (szMacro.Empty(), szArgument[0].Empty(); nPos[8] < nPos[0] + nPos[4] && szArgument[0].GetLength() < GetDatabase()->GetTMParameterTagLength(); nPos[8]++)
									{
										if (GetDatabase()->CheckTMParameterTag(szArgument[0] + szData.GetAt(nPos[8])))
										{
											szArgument[0] += szData.GetAt(nPos[8]);
											continue;
										}
										break;
									}
									if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szArgument[0]))) && FindParameter(szLocalParameters, szProcedure + EOL + szArgument[0]) >= 0)
									{
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETVALUE))))
										{
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS))) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETFLOATVALUE) : EMPTYSTRING;
											szMacro = (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETSTRINGVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETNUMERICALVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETNUMERICALVALUE))))
										{
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETNUMERICALFLOATVALUE) : EMPTYSTRING;
											szMacro = (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETNUMERICALINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETNUMERICALUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETRAWVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETRAWVALUE))))
										{
											szMacro = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETRAWFLOATVALUE) : EMPTYSTRING;
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETRAWINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETRAWUINTVALUE) : (LPCTSTR)szMacro;
										}
										for (; !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETVALUETIME), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETVALUETIME))); )
										{
											szMacro = STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETVALUETIME);
											break;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTVALUE))))
										{
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS))) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTFLOATVALUE) : EMPTYSTRING;
											szMacro = (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTSTRINGVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTNUMERICALVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTNUMERICALVALUE))))
										{
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALFLOATVALUE) : EMPTYSTRING;
											szMacro = (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTNUMERICALUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTRAWVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTRAWVALUE))))
										{
											szMacro = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWFLOATVALUE) : EMPTYSTRING;
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTRAWUINTVALUE) : (LPCTSTR)szMacro;
										}
										for (; !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTVALUETIME), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTVALUETIME))); )
										{
											szMacro = STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_GETPASTVALUETIME);
											break;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_CALCULATEVALUEAVERAGE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_CALCULATEVALUEAVERAGE))))
										{
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEFLOATVALUE) : EMPTYSTRING;
											szMacro = (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_CALCULATEAVERAGEUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!szMacro.IsEmpty())
										{
											if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTVALUE))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTNUMERICALVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTNUMERICALVALUE))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTRAWVALUE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTRAWVALUE))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTVALUETIME), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETPASTVALUETIME))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_CALCULATEVALUEAVERAGE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_CALCULATEVALUEAVERAGE))))
											{
												for (nPos[9] = nPos[8], szDigit[0] = cStringTools.ConvertUIntToString(0), szDigit[1] = cStringTools.ConvertUIntToString(10, 16); nPos[9] < nPos[0] + nPos[4] && !_istdigit(szData.GetAt(nPos[9])) && _tcsncmp((LPCTSTR)szData + nPos[9], STRING(IDS_CHARSET_HEXADECIMALNUMBERPREFIX), lstrlen(STRING(IDS_CHARSET_HEXADECIMALNUMBERPREFIX))); nPos[9]++);
												if (!_tcsncmp((LPCTSTR)szData + nPos[9], STRING(IDS_CHARSET_HEXADECIMALNUMBERPREFIX), lstrlen(STRING(IDS_CHARSET_HEXADECIMALNUMBERPREFIX))))
												{
													for (nPos[9] += lstrlen(STRING(IDS_CHARSET_HEXADECIMALNUMBERPREFIX)), nSamples = 0; nPos[9] < nPos[0] + nPos[4]; nPos[9]++)
													{
														if (_istdigit((szChar = szData.GetAt(nPos[9]))))
														{
															nSamples = 16 * nSamples + szChar - szDigit[0].GetAt(0);
															continue;
														}
														if (_istxdigit(szChar))
														{
															nSamples = 16 * nSamples + _totupper(szChar) - szDigit[1].GetAt(0) + 10;
															continue;
														}
														break;
													}
												}
												else
												{
													for (nSamples = 0; nPos[9] < nPos[0] + nPos[4]; nPos[9]++)
													{
														if (_istdigit((szChar = szData.GetAt(nPos[9]))))
														{
															nSamples = 10 * nSamples + szChar - szDigit[0].GetAt(0);
															continue;
														}
														break;
													}
												}
												if (!SetParameterPastSamples(szArgument[0], szPastParameters, nPastSamples, nSamples) || !SetParameterPastSamples(szProcedure, szArgument[0], szPastProcedures, szPastProcedureParameters, nSamples, (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_CALCULATEVALUEAVERAGE), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_CALCULATEVALUEAVERAGE)))) ? TRUE : FALSE))
												{
													ShowError(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_GENERAL));
													nErrors++;
												}
											}
											szArgument[1].Format(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_PARAMETERARGUMENT), (LPCTSTR)szArgument[0]);
											szData = szData.Left(nPos[7]) + szMacro + szArgument[1] + szData.Mid(nPos[8]);
											nDiff[0] = nPos[7] + szMacro.GetLength() + szArgument[1].GetLength() - nPos[8];
											nDiff[1] -= nDiff[0];
											nPos[4] += nDiff[0];
											nPos[5] += nDiff[0];
											continue;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETSTATUS), lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_MACRO_GETSTATUS))))
										{
											szArgument[1].Format(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_PARAMETERSTATUSARGUMENT), (LPCTSTR)szArgument[0]);
											szData = szData.Left(nPos[7] + lstrlen(STRING(MINMIMICSDESCRIPTIONLANGUAGEPROCEDURE + nProcedure))) + szArgument[1] + szData.Mid(nPos[8]);
										}
										else
										{
											szArgument[1].Format(STRING(IDS_MIMICSDESCRIPTIONFILE_MACRO_PARAMETERARGUMENT), (LPCTSTR)szArgument[0]);
											szData = szData.Left(nPos[7] + lstrlen(STRING(MINMIMICSDESCRIPTIONLANGUAGEPROCEDURE + nProcedure))) + szArgument[1] + szData.Mid(nPos[8]);
										}
										nDiff[0] = nPos[7] + lstrlen(STRING(MINMIMICSDESCRIPTIONLANGUAGEPROCEDURE + nProcedure)) + szArgument[1].GetLength() - nPos[8];
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALPARAMETER), DetermineSourceCodeLine(nSourceCodeLines, nPos[8] + nDiff[1] - szArgument[0].GetLength()), DetermineSourceCodeColumn(nSourceCodeLines, nPos[8] + nDiff[1] - szArgument[0].GetLength()));
									ShowError(szError);
									nErrors++;
									continue;
								}
								break;
							}
						}
						szData.SetAt(nPos[0] + nPos[4], STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_END));
					}
					else
					{
						if (!szProcedure.IsEmpty())
						{
							szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALBODYKEYWORD), DetermineSourceCodeLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
							ShowError(szError);
							nErrors++;
						}
					}
					nPos[0] += nPos[4] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_END));
					continue;
				}
				else
				{
					if (nPos[1] >= nPos[4] && nPos[4] >= 0)
					{
						szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALENDKEYWORD), DetermineSourceCodeLine(nSourceCodeLines, nPos[0] + nPos[4] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[0] + nPos[4] + nDiff[1]));
						nPos[0] += nPos[1];
					}
					if (nPos[1] < nPos[4] && nPos[3] >= nPos[4])
					{
						szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_MISSINGBEGINKEYWORD), DetermineSourceCodeLine(nSourceCodeLines, (nPos[2] < 0) ? (nPos[0] + nPos[1] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)) + nDiff[1] + 1) : (nPos[0] + nPos[2] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PARAMETERS)) + nDiff[1] + 1)), DetermineSourceCodeColumn(nSourceCodeLines, (nPos[2] < 0) ? (nPos[0] + nPos[1] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)) + nDiff[1] + 1) : (nPos[0] + nPos[2] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PARAMETERS)) + nDiff[1] + 1)));
						nPos[0] += nPos[4] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_END));
					}
					if (nPos[4] >= nPos[5] && nPos[5] >= 0)
					{
						szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_MISSINGENDKEYWORD), DetermineSourceCodeLine(nSourceCodeLines, nPos[0] + nPos[5] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[0] + nPos[5] + nDiff[1]));
						nPos[0] += nPos[5];
					}
					if (nPos[4] < 0)
					{
						szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_MISSINGENDKEYWORD), DetermineSourceCodeLine(nSourceCodeLines, nPos[0] + nPos[3] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN)) + nDiff[1] + 1), DetermineSourceCodeColumn(nSourceCodeLines, nPos[0] + nPos[3] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN)) + nDiff[1] + 1));
						nPos[0] += nPos[3] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_BEGIN));
					}
				}
			}
			else
			{
				if (nPos[1] >= nPos[3] && nPos[3] >= 0)
				{
					szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALBEGINKEYWORD), DetermineSourceCodeLine(nSourceCodeLines, nPos[0] + nPos[3] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[0] + nPos[3] + nDiff[1]));
					nPos[0] += nPos[1];
				}
				else
				{
					szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_MISSINGBEGINKEYWORD), DetermineSourceCodeLine(nSourceCodeLines, (nPos[2] < 0 || nPos[2] >= nPos[4]) ? (nPos[0] + nPos[1] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)) + nDiff[1] + 1) : (nPos[0] + nPos[2] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PARAMETERS)) + nDiff[1] + 1)), DetermineSourceCodeColumn(nSourceCodeLines, (nPos[2] < 0 || nPos[2] >= nPos[4]) ? (nPos[0] + nPos[1] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE)) + nDiff[1] + 1) : (nPos[0] + nPos[2] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PARAMETERS)) + nDiff[1] + 1)));
					nPos[0] += (nPos[2] < 0 || nPos[2] >= nPos[4]) ? (nPos[1] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE))) : (nPos[2] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PARAMETERS)));
					nPos[0] = (nPos[1] < nPos[4]) ? (nPos[0] + nPos[4] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_END))) : nPos[0];
				}
			}
		}
		else
		{
			szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_ILLEGALPARAMETERSKEYWORD), DetermineSourceCodeLine(nSourceCodeLines, nPos[0] + nPos[2] + nDiff[1]), DetermineSourceCodeColumn(nSourceCodeLines, nPos[0] + nPos[2] + nDiff[1]));
			nPos[0] += nPos[1];
		}
		ShowError(szError);
		nErrors++;
		continue;
	}
	return((!nErrors) ? TRUE : FALSE);
}

BOOL CMMDCompileThread::TranslateSourceCodeItems(CStringArray &szNames, CStringArray &szTypes) CONST
{
	INT  nItem[2];
	INT  nItems[2];
	CMimicsItem  *pItem;
	CMimicsItems  pItems;
	CMMDLayoutItem  *pLayoutItem;

	for (nItem[0] = 0, nItems[0] = (INT)m_cLayout.GetSize(), szNames.RemoveAll(), szTypes.RemoveAll(); nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pLayoutItem = m_cLayout.GetAt(nItem[0])) != (CMMDLayoutItem *)NULL)
		{
			if ((pItem = CMimicsItem::AllocateFromItem(pLayoutItem)))
			{
				if (pItem->Unmap(pLayoutItem, CPoint(0, 0)))
				{
					pItems.Add(pItem);
					continue;
				}
				delete pItem;
			}
		}
		break;
	}
	for (nItem[1] = 0, nItems[1] = (nItem[0] == nItems[0]) ? (INT)pItems.GetSize() : -1; nItem[1] < nItems[1]; nItem[1]++)
	{
		if ((pItem = (CMimicsItem *)pItems.GetAt(nItem[1])) != (CMimicsItem *)NULL)
		{
			if (pItem->GetItemName() != STRING(IDS_MMD_STATUSBAR_OBJECTDEFAULTNAME))
			{
				szNames.Add(pItem->GetItemName());
				szTypes.Add(pItem->GetItemType());
			}
			if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)))
			{
				TranslateSourceCodeItems(pItem, szNames, szTypes);
				continue;
			}
		}
	}
	return((nItem[1] == nItems[1]) ? TRUE : FALSE);
}
VOID CMMDCompileThread::TranslateSourceCodeItems(CMimicsItem *pItem, CStringArray &szNames, CStringArray &szTypes) CONST
{
	INT  nItem;
	INT  nItems;
	CPtrArray  pItems;
	CMimicsItem  *pMimicsItem;
	CMimicsGroup  *pGroup = (CMimicsGroup *)pItem;

	for (nItem = 0, nItems = pGroup->GetItemList()->EnumItems(pItems); nItem < nItems; nItem++)
	{
		if ((pMimicsItem = (CMimicsItem *)pItems.GetAt(nItem)) != (CMimicsItem *)NULL)
		{
			if (pMimicsItem->GetItemName() != STRING(IDS_MMD_STATUSBAR_OBJECTDEFAULTNAME))
			{
				szNames.Add(pMimicsItem->GetItemName());
				szTypes.Add(pMimicsItem->GetItemType());
			}
			delete pMimicsItem;
		}
	}
}

VOID CMMDCompileThread::CalculateSourceCodeLines(LPCTSTR pszData, CUIntArray &nLines) CONST
{
	INT  nPos;
	INT  cbData;
	UINT  nLine;
	LPCTSTR  pPos;

	for (nLine = 1, nLines.SetAtGrow(0, (nPos = 0)), nLines.SetSize(1), cbData = lstrlen(pszData); nPos < cbData; nLine++)
	{
		if ((pPos = _tcsstr(&pszData[nPos], CString(CR) + CString(EOL))))
		{
			nLines.InsertAt(nLine, (nPos = (INT)(pPos - pszData) + 2));
			continue;
		}
		if ((pPos = _tcsstr(&pszData[nPos], CString(CR))))
		{
			nLines.InsertAt(nLine, (nPos = (INT)(pPos - pszData) + 1));
			continue;
		}
		if ((pPos = _tcsstr(&pszData[nPos], CString(EOL))))
		{
			nLines.InsertAt(nLine, (nPos = (INT)(pPos - pszData) + 1));
			continue;
		}
		break;
	}
}

UINT CMMDCompileThread::DetermineSourceCodeLine(CONST CUIntArray &nLines, INT nPos) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)nLines.GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if (nLines.GetAt(nIndex) <= (UINT)nPos && (nIndex == nLines.GetUpperBound() || nLines.GetAt(nIndex + 1) > (UINT)nPos)) break;
		if (nLines.GetAt(nIndex) > (UINT)nPos)
		{
			nMaxIndex = nIndex;
			continue;
		}
		nMinIndex = nIndex + 1;
	}
	return((nIndex < nLines.GetSize() && nLines.GetAt(nIndex) <= (UINT)nPos && (nIndex == nLines.GetUpperBound() || nLines.GetAt(nIndex + 1) >(UINT) nPos)) ? (nIndex + 1) : -1);
}

UINT CMMDCompileThread::DetermineSourceCodeColumn(CONST CUIntArray &nLines, INT nPos) CONST
{
	UINT  nLine;
	UINT  nColumn;

	if ((nLine = DetermineSourceCodeLine(nLines, nPos)) > 0 && nLine <= (UINT)nLines.GetSize())
	{
		nColumn = nPos - nLines.GetAt(nLine - 1) + 1;
		return nColumn;
	}
	return -1;
}

BOOL CMMDCompileThread::ConvertSourceCodeLineToData(LPCTSTR pszText, CByteArray &nData) CONST
{
#ifndef UNICODE
	nData.SetSize(strlen(pszText));
	if (nData.GetSize() == strlen(pszText))
	{
		CopyMemory(nData.GetData(), pszText, strlen(pszText));
		return TRUE;
	}
#else
	nData.SetSize(lstrlen(pszText));
	if (nData.GetSize() == lstrlen(pszText))
	{
		WideCharToMultiByte(CP_ACP, 0, pszText, lstrlen(pszText), (LPSTR)nData.GetData(), (INT)nData.GetSize(), (LPCSTR)NULL, (LPBOOL)NULL);
		return TRUE;
	}
#endif
	return FALSE;
}

BOOL CMMDCompileThread::CollectParameter(LPCTSTR pszParameter, CStringArray &szParameters) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)szParameters.GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if (szParameters.GetAt(nIndex) < pszParameter)
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	if (nIndex <= szParameters.GetSize() && (!szParameters.GetSize() || (szParameters.GetAt(max(nIndex - 1, 0)) != pszParameter  &&  szParameters.GetAt(min(nIndex, szParameters.GetUpperBound())) != pszParameter  &&  lstrlen(pszParameter) > 0)))
	{
		szParameters.InsertAt(nIndex, pszParameter);
		return TRUE;
	}
	return FALSE;
}

INT CMMDCompileThread::FindParameter(CONST CStringArray &szParameters, LPCTSTR pszParameter, BOOL bScope) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;
	CString  szParameter;

	for (nMinIndex = 0, nMaxIndex = (INT)szParameters.GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2, szParameter = (!_tcsstr(pszParameter, CString(EOL)) && bScope) ? (pszParameter + CString(EOL)) : pszParameter; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if (szParameters.GetAt(nIndex).Left(szParameter.GetLength()) < szParameter)
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	return((nIndex < szParameters.GetSize() && szParameters.GetAt(nIndex).Left(szParameter.GetLength()) == szParameter) ? nIndex : -1);
}

BOOL CMMDCompileThread::SetParameterPastSamples(LPCTSTR pszProcedure, LPCTSTR pszParameter, CStringArray &szPastProcedures, CStringArray &szPastProcedureParameters, INT nSamples, BOOL bAll) CONST
{
	INT  nPos;
	INT  nIndex;
	INT  nSample;
	CString  szSample;
	CString  szSamples[2];
	CStringTools  cStringTools;

	if ((nIndex = FindParameterPastSamples(pszProcedure, szPastProcedures)) >= 0)
	{
		if ((nPos = (szSamples[0] = szPastProcedureParameters.GetAt(nIndex)).Find(pszParameter)) >= 0)
		{
			for (nPos += lstrlen(pszParameter), nSample = 1; nPos < szSamples[0].GetLength(); nPos++)
			{
				for (; szSamples[0].GetAt(nPos) == SPACE[0]; nPos++);
				if (!bAll && (nSamples < _ttoi(szSamples[0].Mid(nPos)) || szSamples[0].GetAt(nPos) == TAB))
				{
					szSample = cStringTools.ConvertIntToString(nSamples);
					szSamples[1] = szSamples[0].Left(nPos) + szSample;
					szSamples[1] += SPACE;
					szSamples[0] = szSamples[1] + szSamples[0].Mid(nPos);
					break;
				}
				if (bAll && (nSample < _ttoi(szSamples[0].Mid(nPos)) || szSamples[0].GetAt(nPos) == TAB))
				{
					szSample = cStringTools.ConvertIntToString(nSample);
					szSamples[1] = szSamples[0].Left(nPos) + szSample;
					szSamples[1] += SPACE;
					szSamples[0] = szSamples[1] + szSamples[0].Mid(nPos);
					if ((nSample = nSample + 1) <= nSamples)
					{
						nPos += szSample.GetLength();
						continue;
					}
					break;
				}
				for (; _istdigit(szSamples[0].GetAt(nPos)); nPos++);
				nSample = (bAll) ? (nSample + 1) : nSample;
			}
			szPastProcedureParameters.SetAt(nIndex, szSamples[0]);
			return TRUE;
		}
	}
	for (nSample = 1, szSamples[0] += pszParameter; bAll && nSample < nSamples; nSample++)
	{
		szSample = cStringTools.ConvertIntToString(nSample);
		szSamples[0] += SPACE;
		szSamples[0] += szSample;
	}
	szSample = cStringTools.ConvertIntToString(nSamples);
	szSamples[0] += SPACE + szSample;
	szSamples[0] += SPACE + CString(TAB);
	if ((nIndex = FindParameterPastSamples(pszProcedure, szPastProcedures)) < 0)
	{
		if ((nIndex = FindParameterPastSamples(pszProcedure, szPastProcedures, TRUE)) >= 0)
		{
			szPastProcedureParameters.InsertAt(nIndex, szSamples[0]);
			szPastProcedures.InsertAt(nIndex, pszProcedure);
			return TRUE;
		}
		return FALSE;
	}
	szPastProcedureParameters.SetAt(nIndex, szSamples[0]);
	return TRUE;
}
BOOL CMMDCompileThread::SetParameterPastSamples(LPCTSTR pszArgument, CStringArray &szPastParameters, CUIntArray &nPastSamples, INT nSamples) CONST
{
	INT  nIndex;

	if ((nIndex = FindParameterPastSamples(pszArgument, szPastParameters)) >= 0)
	{
		nPastSamples.SetAt(nIndex, max((INT)nPastSamples.GetAt(nIndex), nSamples));
		return TRUE;
	}
	if ((nIndex = FindParameterPastSamples(pszArgument, szPastParameters, TRUE)) >= 0)
	{
		szPastParameters.InsertAt(nIndex, pszArgument);
		nPastSamples.InsertAt(nIndex, nSamples);
		return TRUE;
	}
	return FALSE;
}

INT CMMDCompileThread::GetParameterPastSamples(LPCTSTR pszProcedure, LPCTSTR pszParameter, CONST CStringArray &szPastProcedures, CONST CStringArray &szPastProcedureParameters, CUIntArray &nPastSamples) CONST
{
	INT  nPos;
	INT  nIndex;
	CString  szSamples;

	if ((nIndex = FindParameterPastSamples(pszProcedure, szPastProcedures)) >= 0)
	{
		if ((nPos = (szSamples = szPastProcedureParameters.GetAt(nIndex)).Find(pszParameter)) >= 0)
		{
			for (nPos += lstrlen(pszParameter), nPastSamples.RemoveAll(); szSamples.GetAt(nPos) != TAB; nPos++)
			{
				for (; szSamples.GetAt(nPos) == SPACE[0]; nPos++);
				nPastSamples.Add(_ttoi(szSamples.Mid(nPos)));
				for (; _istdigit(szSamples.GetAt(nPos)); nPos++);
			}
			return((INT)nPastSamples.GetSize());
		}
	}
	return -1;
}
INT CMMDCompileThread::GetParameterPastSamples(LPCTSTR pszArgument, CONST CStringArray &szPastParameters, CONST CUIntArray &nPastSamples) CONST
{
	INT  nIndex;

	return(((nIndex = FindParameterPastSamples(pszArgument, szPastParameters)) >= 0) ? (INT)nPastSamples.GetAt(nIndex) : -1);
}

INT CMMDCompileThread::FindParameterPastSamples(LPCTSTR pszProcedureOrArgument, CONST CStringArray &szPastParameters, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)szPastParameters.GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if (szPastParameters.GetAt(nIndex) < pszProcedureOrArgument)
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	return(((!bInsert  &&  nIndex < szPastParameters.GetSize() && szPastParameters.GetAt(nIndex) == pszProcedureOrArgument) || (bInsert  &&  nIndex <= szPastParameters.GetSize() && (!szPastParameters.GetSize() || (szPastParameters.GetAt(max(nIndex - 1, 0)) != pszProcedureOrArgument  &&  szPastParameters.GetAt(min(nIndex, szPastParameters.GetUpperBound())) != pszProcedureOrArgument  &&  lstrlen(pszProcedureOrArgument) > 0)))) ? nIndex : -1);
}

CString CMMDCompileThread::GetMimicsDescriptionFileName(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFormat, BOOL bTemporary) CONST
{
	INT  nPos;
	INT  cbTitle;
	CString  szFileTitle;
	CString  szFileName[3];
	CFileFindEx  cFileFind;

	if (!GetFileTitle((szFileName[0] = pDatabase->GetFileName()), szFileTitle.GetBufferSetLength(cbTitle), (cbTitle = max(GetFileTitle((szFileName[0] = pDatabase->GetFileName()), (LPTSTR)NULL, 0), 0))))
	{
		for (nPos = szFileName[0].GetLength() - lstrlen(szFileTitle), szFileTitle.ReleaseBuffer(); nPos >= 0; nPos--)
		{
			if (!szFileName[0].Mid(nPos, lstrlen(szFileTitle)).CompareNoCase(szFileTitle)) break;
			continue;
		}
		if (nPos >= 0)
		{
			if (bTemporary)
			{
				szFileName[1].Format(STRING(IDS_MIMICSDISPLAYCODE_TEMPORARY_FILENAME), (LPCTSTR)GetCompileTarget());
				szFileName[2] = szFileName[0].Left(nPos) + szFileName[1];
				return szFileName[2];
			}
			szFileName[1].Format(pszFormat, (LPCTSTR)GetCompileTarget());
			szFileName[2] = szFileName[0].Left(nPos) + szFileName[1];
			if (!lstrcmp(pszFormat, STRING(IDS_MIMICSDISPLAYCODE_NORMAL_FILENAME)))
			{
				if (cFileFind.FindFile(szFileName[2]) && !cFileFind.FindNextFile())
				{
					szFileName[1].Format(STRING(IDS_MIMICSDISPLAYCODE_UPDATE_FILENAME), (LPCTSTR)GetCompileTarget());
					szFileName[2] = szFileName[0].Left(nPos) + szFileName[1];
					cFileFind.Close();
				}
			}
		}
		return szFileName[2];
	}
	szFileTitle.ReleaseBuffer();
	return EMPTYSTRING;
}

BOOL CMMDCompileThread::SecureMimicsDescriptionFile(LPCTSTR pszFileName) CONST
{
	CFileFindEx  cFileFind;
	CSecurityDescriptor  cSecurityDescriptor;

	if (cFileFind.FindFile(pszFileName) && !cFileFind.FindNextFile())
	{
		if (cSecurityDescriptor.SetRightsOfSystem(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfNetworkService(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfAdministrators(FILE_ALL_ACCESS) && (cSecurityDescriptor.SetRightsOfSystemOperators(FILE_GENERIC_READ | FILE_GENERIC_WRITE) || cSecurityDescriptor.SetRightsOfPowerUsers(FILE_GENERIC_READ | FILE_GENERIC_WRITE)) && cSecurityDescriptor.SetRightsOfAuthenticatedUsers(FILE_GENERIC_READ) && cSecurityDescriptor.SetRightsOfEveryone(FILE_GENERIC_READ) && CSecurity::SecureDirectory(cFileFind.GetRoot(), cSecurityDescriptor) && CSecurity::SecureFile(cFileFind.GetFilePath(), cSecurityDescriptor))
		{
			cFileFind.Close();
			return TRUE;
		}
		cFileFind.Close();
	}
	return FALSE;
}

CString CMMDCompileThread::GetMimicsDescriptionCompilerFileName() CONST
{
	INT  nDrive;
	INT  nDrives;
	CString  szPlatForm;
	CString  szFileName[2];
	CString  szDirectory[2];
	CString  szOptions[3];
	CProfile  cProfile;
	CStringArray  szDrives;
	CLogicalDrives  cDrives;
	CCompileOptionsDialog  cCompileOptionsDialog;

	if (!cProfile.GetCompileOptions(szFileName[0], szFileName[1], szPlatForm, szDirectory[0], szDirectory[1], szOptions[0], szOptions[1], szOptions[2]))
	{
		for (nDrive = 0, nDrives = cDrives.EnumDrives(szDrives); nDrive < nDrives; nDrive = nDrive + 1)
		{
			if (GetDriveType(szDrives.GetAt(nDrive)) == DRIVE_FIXED || GetDriveType(szDrives.GetAt(nDrive)) == DRIVE_REMOTE)
			{
				if ((szFileName[0] = GetMimicsDescriptionCompilerFileName(szDrives.GetAt(nDrive))).GetLength() > 0) break;
				continue;
			}
		}
		return((cCompileOptionsDialog.DoModal(szFileName[0]) == IDOK) ? (LPCTSTR)szFileName[0] : EMPTYSTRING);
	}
	return szFileName[0];
}
CString CMMDCompileThread::GetMimicsDescriptionCompilerFileName(LPCTSTR pszDirectory) CONST
{
	CString  szFileName;
	CFileFindEx  cFileFind[2];

	if (cFileFind[0].FindFile(CString(pszDirectory) + STRING(IDS_FILENAME_ALL)))
	{
		while (cFileFind[0].FindNextFile())
		{
			if (cFileFind[0].IsDirectory() && !cFileFind[0].IsDots())
			{
				if ((szFileName = GetMimicsDescriptionCompilerFileName(cFileFind[0].GetFilePath())).GetLength() > 0) break;
				continue;
			}
			if (!cFileFind[0].GetFileName().CompareNoCase(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILER_FILENAME)))
			{
				if (cFileFind[1].FindFile(cFileFind[0].GetRoot() + STRINGCHAR(IDS_FILENAME_ALL) + STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_LINKER_FILENAME)))
				{
					szFileName = cFileFind[0].GetFilePath();
					cFileFind[1].Close();
					break;
				}
			}
		}
		cFileFind[0].Close();
	}
	return szFileName;
}

CString CMMDCompileThread::GetMimicsDescriptionCompileOptions(CONST CBinaryDatabase *pDatabase) CONST
{
	INT  nPos[2];
	CString  szPlatForm;
	CString  szOptions[5];
	CString  szFileName[2];
	CString  szDirectory[2];
	CString  szIncludeDirectories;
	CProfile  cProfile;

	for (szOptions[0] = (!cProfile.GetCompileOptions(szFileName[0], szFileName[1], szPlatForm, szDirectory[0], szDirectory[1], szOptions[0], szOptions[1], szOptions[2])) ? (CString(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) + CString(SPACE) + CString(STRING(IDS_COMPILER_OPTION_WARNING3))) : szOptions[0], nPos[0] = 0; nPos[0] + (nPos[1] = (INT)_tcscspn(szDirectory[0].Mid(nPos[0]), STRING(IDS_COMPILER_OPTION_PATH_SEPARATORS))) < szDirectory[0].GetLength() || nPos[0] < szDirectory[0].GetLength(); nPos[0] += nPos[1] + 1)
	{
		for (szOptions[3].Format(STRING(IDS_COMPILER_OPTION_INCLUDEDIRECTORY), (LPCTSTR)szDirectory[0].Mid(nPos[0], nPos[1])); !szIncludeDirectories.IsEmpty(); )
		{
			szIncludeDirectories += SPACE;
			break;
		}
		szIncludeDirectories += szOptions[3];
	}
	szOptions[3] = (!szIncludeDirectories.IsEmpty()) ? (szOptions[0] + SPACE + szIncludeDirectories) : szOptions[0];
	szOptions[4].Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILER_OPTIONS), (LPCTSTR)szOptions[3], (LPCTSTR)GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTNAME)), (LPCTSTR)GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDESCRIPTIONFILE_COMPILENAME)));
	return szOptions[4];
}

CString CMMDCompileThread::GetMimicsDescriptionLinkerFileName() CONST
{
	CString  szPlatForm;
	CString  szFileName[2];
	CString  szDirectory[2];
	CString  szOptions[3];
	CProfile  cProfile;

	return((cProfile.GetCompileOptions(szFileName[0], szFileName[1], szPlatForm, szDirectory[0], szDirectory[1], szOptions[0], szOptions[1], szOptions[2])) ? (LPCTSTR)szFileName[1] : EMPTYSTRING);
}

CString CMMDCompileThread::GetMimicsDescriptionLinkOptions(CONST CBinaryDatabase *pDatabase) CONST
{
	INT  nPos[2];
	CString  szPlatForm;
	CString  szOptions[4];
	CString  szFileName[3];
	CString  szDirectory[2];
	CString  szLibraryFiles;
	CLogicalDrives  cDrives;
	CVersionInfo  cVersionInfo;
	CFileFindEx  cFileFind;
	CProfile  cProfile;

	if (cProfile.GetCompileOptions(szFileName[0], szFileName[1], szPlatForm, szDirectory[0], szDirectory[1], szOptions[0], szOptions[1], szOptions[2]))
	{
		for (nPos[0] = 0; nPos[0] + (nPos[1] = (INT)_tcscspn(szDirectory[1].Mid(nPos[0]), STRING(IDS_COMPILER_OPTION_PATH_SEPARATORS))) < szDirectory[1].GetLength() || nPos[0] < szDirectory[1].GetLength() || szDirectory[1].IsEmpty(); nPos[0] += nPos[1] + 1)
		{
			if (cFileFind.FindFile(szDirectory[1].Mid(nPos[0], nPos[1])))
			{
				for (cFileFind.FindNextFile(); !cFileFind.IsDirectory(); )
				{
					szFileName[2].Format(STRING(IDS_MIMICSDESCRIPTIONFILE_LIBRARYNAME), (LPCTSTR)szDirectory[1].Mid(nPos[0], nPos[1]));
					break;
				}
				for (; cFileFind.IsDirectory(); )
				{
					szFileName[2].Format(STRING(IDS_MIMICSDESCRIPTIONFILE_DEFAULTLIBRARYNAME), (LPCTSTR)(cFileFind.GetFilePath() + cDrives.GetPathDelimiter() + cVersionInfo.QueryInternalName()));
					break;
				}
				szLibraryFiles += (!szLibraryFiles.IsEmpty()) ? (SPACE + szFileName[2]) : szFileName[2];
				cFileFind.Close();
				continue;
			}
			if (szDirectory[1].IsEmpty())
			{
				szLibraryFiles.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_DEFAULTLIBRARYNAME), (LPCTSTR)cVersionInfo.QueryInternalName());
				break;
			}
		}
		szOptions[3].Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_LINKER_OPTIONS), (LPCTSTR)szPlatForm, (LPCTSTR)GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDISPLAYCODE_NORMAL_FILENAME), IsSyntaxCompileTarget()), (LPCTSTR)szLibraryFiles, (LPCTSTR)GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTNAME)));
		return szOptions[3];
	}
	return EMPTYSTRING;
}

LPCTSTR CMMDCompileThread::FindMimicsDescriptionLangaugeSourceCodeKeyword(LPCTSTR pszSourceCode, INT nPos, LPCTSTR pszKeyword) CONST
{
	LPCTSTR  pPos[2];

	for (pPos[0] = pszSourceCode + nPos; (pPos[1] = _tcsstr(pPos[0], pszKeyword)); pPos[0] = pPos[1] + lstrlen(pszKeyword))
	{
		if ((pPos[1] == pszSourceCode || (!_istalnum(pPos[1][-1]) && pPos[1][-1] != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SUBSTITUTE))) && (pPos[1] == pszSourceCode + lstrlen(pszSourceCode) - lstrlen(pszKeyword) || (!_istalnum(pPos[1][lstrlen(pszKeyword)]) && pPos[1][lstrlen(pszKeyword)] != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SUBSTITUTE)))) break;
		continue;
	}
	return pPos[1];
}

CString CMMDCompileThread::FormatMimicsDescriptionCompilerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszError, INT nLine)
{
	INT  nPos;
	INT  nLines;
	INT  nIndex;
	INT  nLength;
	INT  nOffset;
	DWORD  dwCode;
	LPSTR  pszCode;
	CFileEx  cFile;
	CString  szName;
	CString  szData;
	CString  szLine;
	CString  szError;
	LPCTSTR  pData[5];

	if (nLine > 0)
	{
		if (!m_szLines.GetSize())
		{
			if (cFile.Open(GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDESCRIPTIONFILE_COMPILENAME)), CFile::modeRead))
			{
				if ((pszCode = (LPSTR)GlobalAlloc(GPTR, (SIZE_T)cFile.GetLength() + 1)) != (LPSTR)NULL)
				{
					if (ReadFile(cFile.m_hFile, pszCode, (DWORD)cFile.GetLength(), &dwCode, (LPOVERLAPPED)NULL))
					{
#ifndef UNICODE
						szData = pszCode;
#else
						MultiByteToWideChar(CP_ACP, 0, pszCode, (INT)strlen(pszCode), szData.GetBufferSetLength((INT)strlen(pszCode)), (INT)strlen(pszCode));
						szData.ReleaseBuffer();
#endif
						for (nPos = 0, pData[0] = szData; nPos < szData.GetLength(); )
						{
							pData[1] = _tcsstr(pData[0] + nPos, CString(CR) + CString(EOL));
							pData[2] = _tcsstr(pData[0] + nPos, CString(CR));
							pData[3] = _tcsstr(pData[0] + nPos, CString(EOL));
							pData[4] = (pData[1]) ? ((pData[2]) ? ((pData[1] <= pData[2]) ? pData[1] : pData[2]) : pData[1]) : pData[2];
							pData[4] = (pData[4]) ? ((pData[3]) ? ((pData[4] <= pData[3]) ? pData[4] : pData[3]) : pData[4]) : pData[3];
							if (pData[4] && (pData[4] != pData[2] || pData[4] - pData[0] < szData.GetLength() - 1))
							{
								if (!_tcsncpy_s(szLine.GetBufferSetLength((INT)(pData[4] - pData[0] - nPos)), (INT)(pData[4] - pData[0] - nPos) + 1, pData[0] + nPos, pData[4] - pData[0] - nPos))
								{
									szLine.ReleaseBuffer();
									m_szLines.Add(szLine);
								}
								nPos += (pData[1] == pData[4]) ? (szLine.GetLength() + lstrlen(CString(CR) + CString(EOL))) : (szLine.GetLength() + max(lstrlen(CString(CR)), lstrlen(CString(EOL))));
								szLine.ReleaseBuffer();
								continue;
							}
							m_szLines.Add(pData[0] + nPos);
							break;
						}
						szData.Empty();
					}
					GlobalFree(pszCode);
				}
				cFile.Close();
			}
		}
		if (nLine < m_szLines.GetSize())
		{
			for (nIndex = nLine - 1, nOffset = 1; nIndex >= 0; nIndex--, nOffset = (nOffset > 0) ? (nOffset + 1) : nOffset)
			{
				for (nLines = (nOffset < 0) ? (INT)m_szLines.GetSize() : nIndex, szLine.Empty(); nLines < m_szLines.GetSize() && szLine.GetLength() < lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDURESTATEMENTSPROLOG)); nLines++)
				{
					szLine += m_szLines.GetAt(nLines) + CR + EOL;
					continue;
				}
				if (!szLine.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDURESTATEMENTSPROLOG)))
				{
					nOffset = -nOffset;
					continue;
				}
				if ((nPos = (szLine = m_szLines.GetAt(nIndex)).Find(STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDURENAME))) >= 0)
				{
					for (nPos += lstrlen(STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDURENAME)), szLine = m_szLines.GetAt(nIndex), nLength = szLine.GetLength(); nPos < nLength; nPos++)
					{
						if (szLine.Mid(nPos, lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_BEGINCOMMENTS))) == STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_BEGINCOMMENTS))
						{
							for (nPos += lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_BEGINCOMMENTS)), szName.Empty(); nPos < nLength; nPos++)
							{
								if (szLine.Mid(nPos, lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_ENDCOMMENTS))) != STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_ENDCOMMENTS))
								{
									szName += szLine.GetAt(nPos);
									continue;
								}
								if (nOffset < 0)
								{
									for (nPos = 0, nOffset = -nOffset, szLine = STRING(IDS_MIMICSDESCRIPTIONFILE_DISPATCHUPDATEPROCEDURESTATEMENTSPROLOG); nOffset > 1; nOffset--)
									{
										if ((nPos = szLine.Find(CString(CR) + CString(EOL))) < 0) break;
										szLine = szLine.Mid(nPos + 1);
									}
									szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_GENERICFORMAT), (LPCTSTR)szName, nOffset, pszError);
									break;
								}
								szError.Format(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_COMPILEERROR_SIMPLEFORMAT), (LPCTSTR)szName, pszError);
								break;
							}
							break;
						}
					}
					if (!szError.IsEmpty()) break;
				}
			}
		}
	}
	return((!szError.IsEmpty()) ? szError : pszError);
}

VOID CMMDCompileThread::ShowMimicsDescriptionCompilerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszErrors)
{
	INT  nLine;
	INT  nPos[3];
	TCHAR  szChar;
	CString  szDigit;
	CString  szError;
	CString  szErrors;
	CString  szPrefix;
	CString  szMessage;
	CString  szFileName;
	CFileFindEx  cFileFind;
	CStringTools  cStringTools;

	for (szErrors = szMessage = pszErrors, szMessage.MakeLower(), nLine = 0; szErrors.GetLength() > 0; szMessage = szErrors, szMessage.MakeLower(), nLine = 0)
	{
		nPos[0] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILEFATALERRORPREFIX));
		nPos[0] = nPos[1] = ((nPos[1] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_COMPILECOMMANDLINEPREFIX))) >= 0) ? ((nPos[0] >= 0) ? min(nPos[0], nPos[1]) : nPos[1]) : nPos[0];
		if (cFileFind.FindFile(GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDESCRIPTIONFILE_COMPILENAME))) && !cFileFind.FindNextFile() && (nPos[0] > szMessage.Find((!_tcslwr_s((szFileName = cFileFind.GetFileName()).GetBufferSetLength(cFileFind.GetFileName().GetLength()), cFileFind.GetFileName().GetLength() + 1)) ? szFileName : EMPTYSTRING) || nPos[0] < 0))
		{
			for (szFileName.ReleaseBuffer(), nPos[1] = ((nPos[0] = szMessage.Find(szFileName)) >= 0) ? (nPos[0] + szFileName.GetLength() + 1) : -1, szDigit = cStringTools.ConvertUIntToString(0); nPos[1] >= 0 && nPos[1] < szErrors.GetLength(); nPos[1]++)
			{
				if (_istdigit((szChar = szErrors.GetAt(nPos[1]))))
				{
					nLine = 10 * nLine + szChar - szDigit.GetAt(0);
					continue;
				}
				if (nLine > 0) break;
			}
		}
		if (nPos[1] >= 0)
		{
			for (szError.Empty(); nPos[1] < szErrors.GetLength() && nLine > 0; nPos[1]++)
			{
				if (_istalpha(szErrors.GetAt(nPos[1]))) break;
				continue;
			}
			while (nPos[1] < szErrors.GetLength())
			{
				if (szErrors.GetAt(nPos[1]) != CR  &&  szErrors.GetAt(nPos[1]) != EOL)
				{
					szError += szErrors.GetAt(nPos[1]);
					nPos[1]++;
					continue;
				}
				break;
			}
			if (!(szMessage = FormatMimicsDescriptionCompilerErrors(pDatabase, szError, nLine)).IsEmpty())
			{
				szMessage = szMessage.Left(szMessage.GetLength());
				ShowCompileMessage(szMessage);
			}
			for (; nPos[1] < szErrors.GetLength(); )
			{
				if (szErrors.GetAt(nPos[1]) == CR || szErrors.GetAt(nPos[1]) == EOL)
				{
					nPos[1]++;
					continue;
				}
				break;
			}
			for (nPos[2] = 0, szError.MakeUpper(), szPrefix = STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX), szPrefix.MakeUpper(); nPos[2] < szPrefix.GetLength(); nPos[2]++)
			{
				if (!_istalpha(szPrefix.GetAt(nPos[2])))
				{
					szPrefix = szPrefix.Left(nPos[2]);
					break;
				}
			}
			if (_tcsstr(szError, szPrefix))
			{
				SetErrorCount(GetErrorCount() + 1);
				szErrors = szErrors.Mid(nPos[1]);
				continue;
			}
			SetWarningCount((!szErrors.IsEmpty()) ? (GetWarningCount() + 1) : GetWarningCount());
			szFileName.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_COMPILENAME), (LPCTSTR)GetCompileTarget());
			if (!szErrors.Mid(nPos[1]).Left(szFileName.GetLength()).CompareNoCase(szFileName) && (szErrors.GetAt(nPos[1] + szFileName.GetLength()) == CR || szErrors.GetAt(nPos[1] + szFileName.GetLength()) == EOL))
			{
				for (nPos[1] = nPos[1] + szFileName.GetLength(); nPos[1] < szErrors.GetLength(); nPos[1]++)
				{
					if (szErrors.GetAt(nPos[1]) == CR || szErrors.GetAt(nPos[1]) == EOL) continue;
					break;
				}
			}
			szErrors = szErrors.Mid(nPos[1]);
			continue;
		}
		for (nPos[0] = 0, szError.Empty(); nPos[0] < szErrors.GetLength(); nPos[0]++)
		{
			if (szErrors.GetAt(nPos[0]) != CR  &&  szErrors.GetAt(nPos[0]) != EOL)
			{
				szError += szErrors.GetAt(nPos[0]);
				continue;
			}
			break;
		}
		if (!_istspace(szError.GetAt(0)))
		{
			ShowCompileMessage(szError);
			SetErrorCount(GetErrorCount() + 1);
		}
		else  ShowCompileMessage(szError, FALSE);
		while (nPos[0] < szErrors.GetLength())
		{
			if (szErrors.GetAt(nPos[0]) == CR || szErrors.GetAt(nPos[0]) == EOL)
			{
				nPos[0]++;
				continue;
			}
			break;
		}
		szFileName.Format(STRING(IDS_MIMICSDESCRIPTIONFILE_COMPILENAME), (LPCTSTR)GetCompileTarget());
		if (!szErrors.Mid(nPos[0]).Left(szFileName.GetLength()).CompareNoCase(szFileName) && (szErrors.GetAt(nPos[0] + szFileName.GetLength()) == CR || szErrors.GetAt(nPos[0] + szFileName.GetLength()) == EOL))
		{
			for (nPos[0] = nPos[0] + szFileName.GetLength(); nPos[0] < szErrors.GetLength(); nPos[0]++)
			{
				if (szErrors.GetAt(nPos[0]) == CR || szErrors.GetAt(nPos[0]) == EOL) continue;
				break;
			}
		}
		szErrors = szErrors.Mid(nPos[0]);
		continue;
	}
	cFileFind.Close();
}

VOID CMMDCompileThread::ShowMimicsDescriptionLinkerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszErrors)
{
	INT  nPos[3];
	CString  szError;
	CString  szErrors;
	CString  szPrefix;
	CString  szMessage;
	CString  szFileName;
	CFileFindEx  cFileFind;

	for (szErrors = szMessage = pszErrors, szMessage.MakeLower(); szErrors.GetLength() > 0; szMessage = szErrors, szMessage.MakeLower())
	{
		nPos[0] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_LINKFATALERRORPREFIX));
		nPos[1] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_LINKERRORPREFIX));
		nPos[2] = szMessage.Find(STRING(IDS_MIMICSDESCRIPTIONFILE_ERROR_LINKWARNINGPREFIX));
		nPos[0] = nPos[1] = (nPos[0] >= 0) ? ((nPos[1] >= 0) ? min(nPos[0], nPos[1]) : nPos[0]) : nPos[1];
		nPos[0] = nPos[1] = (nPos[0] >= 0) ? ((nPos[2] >= 0) ? min(nPos[0], nPos[2]) : nPos[0]) : nPos[2];
		if ((cFileFind.FindFile(GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDESCRIPTIONFILE_OBJECTNAME))) && !cFileFind.FindNextFile()) && nPos[0] < 0)
		{
			for (szFileName = cFileFind.GetFileName(), szFileName.MakeLower(), nPos[1] = ((nPos[0] = szMessage.Find(szFileName)) >= 0) ? (nPos[0] + szFileName.GetLength()) : -1; nPos[1] >= 0 && nPos[1] < szErrors.GetLength(); nPos[1]++)
			{
				if (_istalpha(szErrors.GetAt(nPos[1]))) break;
				continue;
			}
		}
		if (nPos[1] >= 0)
		{
			for (szError.Empty(); nPos[1] < szErrors.GetLength(); nPos[1]++)
			{
				if (szErrors.GetAt(nPos[1]) != CR  &&  szErrors.GetAt(nPos[1]) != EOL)
				{
					szError += szErrors.GetAt(nPos[1]);
					continue;
				}
				break;
			}
			for (ShowCompileMessage(szError); nPos[1] < szErrors.GetLength(); )
			{
				if (szErrors.GetAt(nPos[1]) == CR || szErrors.GetAt(nPos[1]) == EOL)
				{
					nPos[1]++;
					continue;
				}
				break;
			}
			for (nPos[2] = 0, szError.MakeUpper(), szPrefix = STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX), szPrefix.MakeUpper(); nPos[2] < szPrefix.GetLength(); nPos[2]++)
			{
				if (!_istalpha(szPrefix.GetAt(nPos[2])))
				{
					szPrefix = szPrefix.Left(nPos[2]);
					break;
				}
			}
			if (_tcsstr(szError, szPrefix))
			{
				SetErrorCount(GetErrorCount() + 1);
				szErrors = szErrors.Mid(nPos[1]);
				continue;
			}
			SetWarningCount((!szErrors.IsEmpty()) ? (GetWarningCount() + 1) : GetWarningCount());
			szErrors = szErrors.Mid(nPos[1]);
			continue;
		}
		for (nPos[0] = 0, szError.Empty(); nPos[0] < szErrors.GetLength(); nPos[0]++)
		{
			if (szErrors.GetAt(nPos[0]) != CR  &&  szErrors.GetAt(nPos[0]) != EOL)
			{
				szError += szErrors.GetAt(nPos[0]);
				continue;
			}
			break;
		}
		if (!_istspace(szError.GetAt(0)))
		{
			ShowCompileMessage(szError);
			SetErrorCount(GetErrorCount() + 1);
		}
		else  ShowCompileMessage(szError, FALSE);
		while (nPos[0] < szErrors.GetLength())
		{
			if (szErrors.GetAt(nPos[0]) == CR || szErrors.GetAt(nPos[0]) == EOL)
			{
				nPos[0]++;
				continue;
			}
			break;
		}
		szErrors = szErrors.Mid(nPos[0]);
		continue;
	}
	cFileFind.Close();
}

VOID CMMDCompileThread::CleanupMimicsDescriptionBuildOutput(CONST CBinaryDatabase *pDatabase)
{
	BOOL  bFound;
	CString  szFileName[3];
	CFileFindEx  cFileFind;

	for (szFileName[0].Format(STRING(IDS_MIMICSDISPLAYCODE_NORMAL_FILENAME), (LPCTSTR)GetCompileTarget()), szFileName[1].Format(STRING(IDS_MIMICSDISPLAYCODE_UPDATE_FILENAME), (LPCTSTR)GetCompileTarget()), szFileName[2] = GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDESCRIPTIONFILE_COMPILENAME)); cFileFind.FindFile(GetMimicsDescriptionFileName(pDatabase, STRING(IDS_MIMICSDISPLAYCODE_SEARCH_FILENAME))); )
	{
		while ((bFound = cFileFind.FindNextFile()) == TRUE || bFound == FALSE)
		{
			if (!cFileFind.GetFilePath().Right(szFileName[0].GetLength()).CompareNoCase(szFileName[0]))
			{
				if (!bFound) break;
				continue;
			}
			if (!cFileFind.GetFilePath().Right(szFileName[1].GetLength()).CompareNoCase(szFileName[1]))
			{
				if (!bFound) break;
				continue;
			}
			if (!cFileFind.GetFilePath().CompareNoCase(szFileName[2]))
			{
				if (!bFound) break;
				continue;
			}
			CFileEx::Remove(cFileFind.GetFilePath());
			if (!bFound) break;
		}
		break;
	}
}

VOID CMMDCompileThread::ShowStartCompileMessages()
{
	CString  szMessage[2];
	CRecentDocumentInfo  cDocument;
	CUpdateUI  cUpdateUI;

	for (SetConsoleContext(STRING(IDS_OUTPUTWINDOW_BUILDTAB), &cDocument), szMessage[0].Format(STRING(IDS_COMPILER_MESSAGE_FORMAT), (LPCTSTR)GetDatabase()->GetName()), szMessage[1].Format(STRING(IDS_COMPILER_MESSAGE_COMPILING_MIMICSDISPLAY), (LPCTSTR)GetCompileTarget()); !IsBatchCompileTarget(); )
	{
		ResetConsoleContent(STRING(IDS_OUTPUTWINDOW_BUILDTAB));
		ShowCompileMessage(szMessage[0]);
		break;
	}
	ShowCompileMessage(szMessage[1]);
	cDocument.SetDocument(GetCompileTarget(), EMPTYSTRING, DATABASE_COMPONENT_MMD);
	SetConsoleContext(STRING(IDS_OUTPUTWINDOW_BUILDTAB), &cDocument);
}

VOID CMMDCompileThread::ShowStopCompileMessages()
{
	CString  szMessage;
	CRecentDocumentInfo  cDocument;
	CUpdateUI  cUpdateUI;

	for (SetConsoleContext(STRING(IDS_OUTPUTWINDOW_BUILDTAB), &cDocument), szMessage.Format(STRING(IDS_COMPILER_MESSAGE_STOPCOMPILING), GetErrorCount(), GetWarningCount()), InterlockedExchange(&m_bStop, TRUE); !IsBatchCompileTarget(); )
	{
		ShowCompileMessage((!GetAbortStatus()) ? (LPCTSTR)szMessage : STRING(IDS_COMPILER_MESSAGE_ABORTCOMPILING), TRUE, TRUE);
		break;
	}
}

VOID CMMDCompileThread::ShowCompileMessage(LPCTSTR pszMessage, BOOL bTimestamp, BOOL bAudition)
{
	ShowConsoleText(STRING(IDS_OUTPUTWINDOW_BUILDTAB), pszMessage, bTimestamp, (!IsBatchCompileTarget()) ? bAudition : FALSE);
}

VOID CMMDCompileThread::ShowError(LPCTSTR pszError)
{
	ShowCompileMessage(CString(STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX)) + pszError);
	SetErrorCount(GetErrorCount() + 1);
}

VOID CMMDCompileThread::ShowWarning(LPCTSTR pszWarning)
{
	ShowCompileMessage(CString(STRING(IDS_COMPILER_MESSAGE_WARNING_PREFIX)) + pszWarning);
	SetWarningCount(GetWarningCount() + 1);
}

VOID CMMDCompileThread::SetErrorCount(UINT nCount)
{
	m_nErrors = nCount;
}

UINT CMMDCompileThread::GetErrorCount() CONST
{
	return m_nErrors;
}

VOID CMMDCompileThread::SetWarningCount(UINT nCount)
{
	m_nWarnings = nCount;
}

UINT CMMDCompileThread::GetWarningCount() CONST
{
	return m_nWarnings;
}

VOID CMMDCompileThread::SetAbortStatus(BOOL bAbort)
{
	InterlockedExchange(&m_bAbort, bAbort);
	InterlockedExchange(&m_bStop, (bAbort) ? m_bStop : FALSE);
}

BOOL CMMDCompileThread::GetAbortStatus() CONST
{
	return m_bAbort;
}

BEGIN_MESSAGE_MAP(CMMDCompileThread, CThread)
	//{{AFX_MSG_MAP(CMMDCompileThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDCompileThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CMMDWnd

IMPLEMENT_DYNCREATE(CMMDWnd, CDisplayWnd)

CMMDCompileThread  CMMDWnd::m_cCompileThread;

CMMDWnd::CMMDWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_MMD);
	SetTitle(STRING(IDS_WINDOW_UNTITLED));
}
CMMDWnd::CMMDWnd(LPCTSTR pszName) : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_MMD);
	SetTitle(STRING(IDS_WINDOW_UNTITLED));
	SetName(pszName);
}

BOOL CMMDWnd::Create(CMDIFrameWnd *pParentWnd, UINT nShow)
{
	CRect  rPosition[2];

	for (rPosition[0] = m_rPosition; CDisplayWnd::Create(pParentWnd, EMPTYSTRING, (nShow == (UINT)-1) ? CRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) : CRect(0, 0, 0, 0), IDR_MMDFRAME, (nShow != SW_SHOWMINIMIZED || nShow != SW_SHOWMAXIMIZED) ? (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE) : (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW)); )
	{
		for (GetWindowRect(rPosition[1]), GetParent()->ScreenToClient(rPosition[1]), MoveWindow(0, 0, 0, 0), MoveWindow((nShow != (UINT)-1) ? rPosition[0] : rPosition[1]), ShowWindow((nShow == SW_SHOWMAXIMIZED || nShow == SW_SHOWMINIMIZED || nShow == (UINT)-1) ? SW_SHOWNORMAL : nShow); nShow == SW_SHOWMAXIMIZED || nShow == SW_SHOWMINIMIZED; )
		{
			ShowWindow(nShow);
			break;
		}
		UpdateTitle();
		UpdateMenus();
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}

VOID CMMDWnd::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CMMDWnd::GetName() CONST
{
	return m_szName;
}

VOID CMMDWnd::SetTitle(LPCTSTR pszTitle)
{
	for (m_szTitle = pszTitle; IsWindow(GetSafeHwnd()); )
	{
		GetImageView()->SetImage(pszTitle);
		UpdateTitle();
		break;
	}
}

CString CMMDWnd::GetTitle() CONST
{
	return m_szTitle;
}

VOID CMMDWnd::SetImage(CONST SIZE &sizeImage, INT nMarginLeft, INT nMarginTop, INT nMarginRight, INT nMarginBottom, COLORREF nImageBkgnd, CONST SIZE &sizeGrid, COLORREF nImageGrid, BOOL bUseGrid)
{
	GetImageView()->SetImage(sizeImage, nMarginLeft, nMarginTop, nMarginRight, nMarginBottom, nImageBkgnd, sizeGrid, nImageGrid, bUseGrid);
}

VOID CMMDWnd::GetImage(SIZE &sizeImage, INT &nMarginLeft, INT &nMarginTop, INT &nMarginRight, INT &nMarginBottom, COLORREF &nImageBkgnd, SIZE &sizeGrid, COLORREF &nImageGrid, BOOL &bUseGrid) CONST
{
	GetImageView()->GetImage(sizeImage, nMarginLeft, nMarginTop, nMarginRight, nMarginBottom, nImageBkgnd, sizeGrid, nImageGrid, bUseGrid);
}

CMimicsItem *CMMDWnd::AddMimicsCtrl(UINT nCtrlID, CONST POINT &point, BOOL bActivate)
{
	CMimicsItem  *pMimicsItem;

	return(((pMimicsItem = GetImageView()->AddItem(nCtrlID, point, bActivate)) && GetImageView()->UpdateAllItems(pMimicsItem)) ? pMimicsItem : (CMimicsItem *)NULL);
}
CMimicsItem *CMMDWnd::AddMimicsCtrl(CMimicsItem *pItem, BOOL bActivate)
{
	CMimicsItem  *pMimicsItem;

	return(((pMimicsItem = GetImageView()->AddItem(pItem, bActivate)) && GetImageView()->UpdateAllItems(pMimicsItem)) ? pMimicsItem : (CMimicsItem *)NULL);
}

CMimicsItem *CMMDWnd::GetActivatedMimicsCtrl() CONST
{
	return GetImageView()->GetActivatedItem();
}

VOID CMMDWnd::DeleteMimicsCtrl(CMimicsItem *pItem)
{
	GetImageView()->DeleteItem(pItem);
	GetImageView()->UpdateAllItems(TRUE);
}

INT CMMDWnd::EnumMimicsCtrls(CPtrArray &pItems) CONST
{
	return GetImageView()->EnumItems(pItems);
}

INT CMMDWnd::GetMimicsCtrlCount() CONST
{
	return GetImageView()->GetItemCount();
}

VOID CMMDWnd::SetSelectedMimicsCtrlID(UINT nCtrlID)
{
	GetImageView()->SetSelectedItemID(nCtrlID);
}

UINT CMMDWnd::GetSelectedMimicsCtrlID() CONST
{
	return GetImageView()->GetSelectedItemID();
}

VOID CMMDWnd::CollectMimicsGroup()
{
	GetImageView()->CollectMimicsGroup();
}

BOOL CMMDWnd::CanCollectMimicsGroup() CONST
{
	return GetImageView()->CanCollectMimicsGroup();
}

VOID CMMDWnd::DiscardMimicsGroup()
{
	GetImageView()->DiscardMimicsGroup();
}

BOOL CMMDWnd::CanDiscardMimicsGroup() CONST
{
	return GetImageView()->CanDiscardMimicsGroup();
}

VOID CMMDWnd::StepIntoMimicsGroup()
{
	GetImageView()->StepIntoMimicsGroup();
}

BOOL CMMDWnd::CanStepIntoMimicsGroup() CONST
{
	return GetImageView()->CanStepIntoMimicsGroup();
}

VOID CMMDWnd::StepOutMimicsGroup()
{
	GetImageView()->StepOutMimicsGroup();
}

BOOL CMMDWnd::CanStepOutMimicsGroup() CONST
{
	return GetImageView()->CanStepOutMimicsGroup();
}

VOID CMMDWnd::DoHorzAlignMimicsCtrls()
{
	GetImageView()->DoHorzAlignItems();
}

BOOL CMMDWnd::CanHorzAlignMimicsCtrls() CONST
{
	return GetImageView()->CanHorzAlignItems();
}

VOID CMMDWnd::DoVertAlignMimicsCtrls()
{
	GetImageView()->DoVertAlignItems();
}

BOOL CMMDWnd::CanVertAlignMimicsCtrls() CONST
{
	return GetImageView()->CanVertAlignItems();
}

VOID CMMDWnd::DoMoveMimicsCtrlToTop()
{
	GetImageView()->DoMoveItemToTop();
}

BOOL CMMDWnd::CanMoveMimicsCtrlToTop() CONST
{
	return GetImageView()->CanMoveItemToTop();
}

VOID CMMDWnd::DoMoveMimicsCtrlToBottom()
{
	GetImageView()->DoMoveItemToBottom();
}

BOOL CMMDWnd::CanMoveMimicsCtrlToBottom() CONST
{
	return GetImageView()->CanMoveItemToBottom();
}

VOID CMMDWnd::DoMoveMimicsCtrlUp()
{
	GetImageView()->DoMoveItemUp();
}

BOOL CMMDWnd::CanMoveMimicsCtrlUp() CONST
{
	return GetImageView()->CanMoveItemUp();
}

VOID CMMDWnd::DoMoveMimicsCtrlDown()
{
	GetImageView()->DoMoveItemDown();
}

BOOL CMMDWnd::CanMoveMimicsCtrlDown() CONST
{
	return GetImageView()->CanMoveItemDown();
}

VOID CMMDWnd::DoShowHideMimicsCtrl()
{
	GetImageView()->DoShowHideItem();
}

BOOL CMMDWnd::CanShowHideMimicsCtrl() CONST
{
	return GetImageView()->CanShowHideItem();
}

VOID CMMDWnd::DoHorzFlipMimicsCtrl()
{
	GetImageView()->DoHorzFlipItem();
}

BOOL CMMDWnd::CanHorzFlipMimicsCtrl() CONST
{
	return GetImageView()->CanHorzFlipItem();
}

VOID CMMDWnd::DoVertFlipMimicsCtrl()
{
	GetImageView()->DoVertFlipItem();
}

BOOL CMMDWnd::CanVertFlipMimicsCtrl() CONST
{
	return GetImageView()->CanVertFlipItem();
}

VOID CMMDWnd::DoRotateMimicsCtrl(double fAngle)
{
	GetImageView()->DoRotateItem(fAngle);
}

BOOL CMMDWnd::CanRotateMimicsCtrl() CONST
{
	return GetImageView()->CanRotateItem();
}

VOID CMMDWnd::SetMimicsCtrlRotateMode(BOOL bFlag)
{
	GetImageView()->SetItemRotateMode(bFlag);
}

BOOL CMMDWnd::GetMimicsCtrlRotateMode() CONST
{
	return GetImageView()->GetItemRotateMode();
}

VOID CMMDWnd::ShowMimicsCtrlProperties()
{
	CMimicsItem  *pItem;

	if ((pItem = GetImageView()->GetActivatedItem()))
	{
		pItem->ActivateItem(OLEIVERB_PROPERTIES, GetImageView());
		GetImageView()->UpdateAllItems(pItem);
		UpdateBars(pItem);
		return;
	}
	for (ShowMimicsCtrlItem(); (pItem = GetImageView()->GetActivatedItem()); )
	{
		pItem->ActivateItem(OLEIVERB_PROPERTIES, GetImageView());
		GetImageView()->UpdateAllItems(pItem);
		UpdateBars(pItem);
		break;
	}
}

BOOL CMMDWnd::HasMimicsCtrlProperties()
{
	return CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE);
}

VOID CMMDWnd::ShowMimicsCtrlItem()
{
	CString  szName;
	CMimicsItem  *pItem;

	if ((pItem = (GetCodeView()->FindCode(szName)) ? GetImageView()->FindItem(szName) : (CMimicsItem *)NULL))
	{
		m_wndSplitter.SetActivePane(0, 0, GetImageView());
		GetImageView()->SetActivatedItem(pItem);
		GetImageView()->SetFocus();
	}
}

BOOL CMMDWnd::HasMimicsCtrlItem() CONST
{
	CString  szName;

	return((GetCodeView()->FindCode(szName) && GetImageView()->FindItem(szName)) ? TRUE : FALSE);
}

VOID CMMDWnd::ShowMimicsCtrlCode()
{
	CMimicsItem  *pItem;

	if ((pItem = GetImageView()->GetActivatedItem()))
	{
		m_wndSplitter.SetActivePane(0, 0, GetCodeView());
		GetCodeView()->SelectCode(pItem->GetItemName());
		GetCodeView()->SetFocus();
	}
}

BOOL CMMDWnd::HasMimicsCtrlCode() CONST
{
	CMimicsItem  *pItem;

	return(((pItem = GetImageView()->GetActivatedItem())) ? ((GetCodeView()->FindCode((LPCTSTR)pItem->GetItemName()) >= 0) ? TRUE : FALSE) : FALSE);
}

BOOL CMMDWnd::SearchMimicsCtrlCode(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return GetCodeView()->SearchCode(pszText, bDown, bAll, bCase, bWord);
}

BOOL CMMDWnd::ReplaceMimicsCtrlCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return GetCodeView()->ReplaceCode(pszText, pszReplaceText, bDown, bAll, bCase, bWord);
}

BOOL CMMDWnd::ReplaceAllMimicsCtrlCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return GetCodeView()->ReplaceAllCode(pszText, pszReplaceText, bDown, bAll, bCase, bWord);
}

BOOL CMMDWnd::GoToMimicsCtrlCode(UINT nLine, BOOL bDown, BOOL bUp)
{
	return GetCodeView()->GoToCode(nLine, bDown, bUp);
}
BOOL CMMDWnd::GoToMimicsCtrlCode(LPCTSTR pszLine)
{
	return GetCodeView()->GoToCode(pszLine);
}

VOID CMMDWnd::SetHotSpot(CONST RECT &rect)
{
	GetImageView()->SetHotSpot(rect);
}

CRect CMMDWnd::GetHotSpot() CONST
{
	return GetImageView()->GetHotSpot();
}

VOID CMMDWnd::DrawHotSpot(CDC *pDC, CONST SIZE &size)
{
	GetImageView()->DrawHotSpot(pDC, size);
}

BOOL CMMDWnd::IsNew() CONST
{
	return m_szName.IsEmpty();
}

BOOL CMMDWnd::IsModified() CONST
{
	return GetImageView()->IsModified() || GetCodeView()->IsModified();
}

BOOL CMMDWnd::Save(INT nPosition) CONST
{
	INT  nPane[2][2];
	UINT  nShowFlags;
	CRect  rHotSpot;
	CProfile  cProfile;

	rHotSpot = GetHotSpot();
	rHotSpot.OffsetRect(-GetImageView()->GetScrollPos(SB_HORZ), 0);
	rHotSpot.OffsetRect(0, -GetImageView()->GetScrollPos(SB_VERT));
	cProfile.DeleteDisplayWindowInfo(nPosition);
	m_wndSplitter.GetRowInfo(0, nPane[0][0], nPane[0][1]);
	m_wndSplitter.GetRowInfo(1, nPane[1][0], nPane[1][1]);
	return((cProfile.SetDisplayWindowType(nPosition, GetType()) && cProfile.SetDisplayWindowName(nPosition, GetName()) && cProfile.SetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, (nShowFlags = (!IsIconic()) ? ((!IsZoomed()) ? SW_SHOWNORMAL : SW_SHOWMAXIMIZED) : SW_SHOWMINIMIZED)) && cProfile.SetMMDWindowPropertyInfo(nPosition, nPane[0][0], nPane[0][1], nPane[1][0], nPane[1][1], rHotSpot)) ? TRUE : FALSE);
}

INT CMMDWnd::Load(INT nPosition)
{
	INT  nPane[2][2];
	UINT  nShowFlags;
	CRect  rHotSpot;
	CProfile  cProfile;

	if (cProfile.GetDisplayWindowName(nPosition, m_szName) && cProfile.GetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, nShowFlags) && cProfile.GetMMDWindowPropertyInfo(nPosition, nPane[0][0], nPane[0][1], nPane[1][0], nPane[1][1], rHotSpot))
	{
		if (CMMDWnd::Create(GetMainWnd(), nShowFlags))
		{
			GetImageView()->SetHotSpot(rHotSpot);
			m_wndSplitter.SetRowInfo(0, nPane[0][0], nPane[0][1]);
			m_wndSplitter.SetRowInfo(1, nPane[1][0], nPane[1][1]);
			m_wndSplitter.RecalcLayout();
			return TRUE;
		}
		return FALSE;
	}
	return -1;
}

BOOL CMMDWnd::UpdateProperties()
{
	CMimicsItem  *pItem;

	if ((pItem = GetImageView()->GetActivatedItem()))
	{
		pItem->ActivateItem(OLEIVERB_PROPERTIES, GetImageView());
		GetImageView()->UpdateAllItems(pItem);
		UpdateBars(pItem);
		return TRUE;
	}
	if (m_dlgProperties.Create(this) == IDOK)
	{
		GetImageView()->UpdateAllItems();
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::IsUpdatingProperties() CONST
{
	CMimicsItem  *pItem;

	return((((pItem = GetImageView()->GetActivatedItem()) && pItem->IsUpdatingProperties()) || IsWindow(m_dlgProperties.GetSafeHwnd())) ? TRUE : FALSE);
}

BOOL CMMDWnd::HasProperties() CONST
{
	CMimicsItem  *pItem;

	return(((pItem = GetImageView()->GetActivatedItem()) && pItem->HasProperties()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : TRUE);
}

BOOL CMMDWnd::UpdateLinkInformation()
{
	return((m_dlgLinkInformation.Create(this) == IDOK) ? TRUE : FALSE);
}

BOOL CMMDWnd::IsUpdatingLinkInformation() CONST
{
	return IsWindow(m_dlgLinkInformation.GetSafeHwnd());
}

BOOL CMMDWnd::HasLinkInformation() CONST
{
	return((GetImageView()->GetActivatedItem() != (CMimicsItem *)NULL) ? TRUE : FALSE);
}

BOOL CMMDWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
{
	CDC  cDC;
	BOOL  bMetrics;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	DEVMODE  *pDevMode;
	DEVNAMES  *pDevNames;
	CMetaFileDC  cMetaDC;
	CPrintProfileInfo  cPrintProfileInfo;

	if (GetPrintProperties(cMetaDC, nFlags))
	{
		if (GetPrintProfile(cPrintProfileInfo) && cPrintProfileInfo.GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetrics))
		{
			if (!AfxIsValidAddress(pPrintInfo, sizeof(PRINTDLG)))
			{
				if (CreatePrinterDC(&cPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, cPrintProfileInfo.GetPrinterName(), rtMargin[0], bMetrics, nFlags, cMetaDC))
					{
						cDC.DeleteDC();
						return TRUE;
					}
					cDC.DeleteDC();
				}
				DeleteEnhMetaFile(cMetaDC.CloseEnhanced());
				return FALSE;
			}
			if ((pDevNames = (DEVNAMES *)GlobalLock(pPrintInfo->hDevNames)))
			{
				if ((pDevMode = (DEVMODE *)GlobalLock(pPrintInfo->hDevMode)))
				{
					if (CreatePrinterDC(pPrintInfo->hDevNames, pPrintInfo->hDevMode, cDC))
					{
						if (PrintJob(cDC, (LPCTSTR)pDevMode->dmDeviceName, rtMargin[0], bMetrics, nFlags, cMetaDC, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : -1, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : -1))
						{
							GlobalUnlock(pPrintInfo->hDevNames);
							GlobalUnlock(pPrintInfo->hDevMode);
							cDC.DeleteDC();
							return TRUE;
						}
						cDC.DeleteDC();
					}
					GlobalUnlock(pPrintInfo->hDevMode);
				}
				GlobalUnlock(pPrintInfo->hDevNames);
			}
		}
		DeleteEnhMetaFile(cMetaDC.CloseEnhanced());
	}
	return FALSE;
}

VOID CMMDWnd::DoSave()
{
	INT  nPosition;
	CString  szMessage;

	if (CanSave())
	{
		if ((nPosition = SaveToDatabase()) >= 0)
		{
			GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_MMD);
			UpdateDatabase(this, nPosition);
			UpdateTitle();
			return;
		}
		szMessage.Format(STRING(IDS_MMD_FAILURE_SAVE), (LPCTSTR)GetTitle());
		ShowMessage(szMessage);
	}
}

BOOL CMMDWnd::CanSave() CONST
{
	return((IsModified() && !GetDatabase()->IsCompiling() && !IsCompilingMMD()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDWnd::DoSaveAs()
{
	INT  nIndex;
	INT  nResult;
	INT  nPosition;
	CString  szName;
	CString  szMessage;
	CMMDSaveDialog  cSaveDialog;

	if (CanSaveAs())
	{
		if ((nResult = ((szName = GetName()).GetLength() >= 0) ? cSaveDialog.Create(this) : IDCANCEL) == IDOK && (nPosition = ((nIndex = GetDatabase()->GetMMDs()->Find(GetName())) >= 0 || nIndex < 0) ? SaveToDatabase() : -1) >= 0)
		{
			GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_MMD);
			UpdateDatabase(this, (nIndex < 0) ? -(nPosition + 1) : nPosition);
			UpdateTitle();
			UpdateMenus();
			return;
		}
		if (nResult == IDOK)
		{
			szMessage.Format(STRING(IDS_MMD_FAILURE_SAVE), (LPCTSTR)GetTitle());
			ShowMessage(szMessage);
		}
	}
}

BOOL CMMDWnd::CanSaveAs() CONST
{
	return CanSave();
}

VOID CMMDWnd::DoDelete()
{
	INT  nPosition;
	CString  szMessage;

	if (!IsNew())
	{
		for (szMessage.Format(STRING(IDS_MMD_QUESTION_DELETE), (LPCTSTR)GetTitle()); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES; )
		{
			if ((nPosition = DeleteFromDatabase()) >= 0)
			{
				GetTopLevelFrame()->RemoveMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_MMD);
				UpdateDatabase(this, nPosition, TRUE);
				DestroyWindow();
				return;
			}
			szMessage.Format(STRING(IDS_MMD_FAILURE_DELETE), (LPCTSTR)GetTitle());
			ShowMessage(szMessage);
			break;
		}
	}
}

BOOL CMMDWnd::CanDelete() CONST
{
	return((!IsNew() && !GetDatabase()->IsCompiling() && !IsCompilingMMD()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

VOID CMMDWnd::DoUndo()
{
	m_wndSplitter.DoUndo();
}

BOOL CMMDWnd::CanUndo() CONST
{
	return m_wndSplitter.CanUndo();
}

VOID CMMDWnd::DoRedo()
{
	m_wndSplitter.DoRedo();
}

BOOL CMMDWnd::CanRedo() CONST
{
	return m_wndSplitter.CanRedo();
}

VOID CMMDWnd::DoFind()
{
	m_wndSplitter.DoFind();
}

BOOL CMMDWnd::CanFind() CONST
{
	return m_wndSplitter.CanFind();
}

VOID CMMDWnd::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	m_wndSplitter.DoFindNext(bMatchCase, bMatchWord);
}
VOID CMMDWnd::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	m_wndSplitter.DoFindNext(pszText, bSearchAll, bMatchCase, bMatchWord);
}

BOOL CMMDWnd::CanFindNext() CONST
{
	return m_wndSplitter.CanFindNext();
}

VOID CMMDWnd::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	m_wndSplitter.DoFindPrevious(bMatchCase, bMatchWord);
}
VOID CMMDWnd::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	m_wndSplitter.DoFindPrevious(pszText, bSearchAll, bMatchCase, bMatchWord);
}

BOOL CMMDWnd::CanFindPrevious() CONST
{
	return m_wndSplitter.CanFindPrevious();
}

VOID CMMDWnd::DoReplace()
{
	m_wndSplitter.DoReplace();
}

BOOL CMMDWnd::CanReplace() CONST
{
	return m_wndSplitter.CanReplace();
}

VOID CMMDWnd::DoGoTo()
{
	m_wndSplitter.DoGoTo();
}

BOOL CMMDWnd::CanGoTo() CONST
{
	return m_wndSplitter.CanGoTo();
}

VOID CMMDWnd::DoSelectAll()
{
	m_wndSplitter.DoSelectAll();
}

BOOL CMMDWnd::CanSelectAll() CONST
{
	return m_wndSplitter.CanSelectAll();
}

VOID CMMDWnd::DoCutSel()
{
	m_wndSplitter.DoCutSel();
}

BOOL CMMDWnd::CanCutSel() CONST
{
	return m_wndSplitter.CanCutSel();
}

VOID CMMDWnd::DoCopySel()
{
	m_wndSplitter.DoCopySel();
}

BOOL CMMDWnd::CanCopySel() CONST
{
	return m_wndSplitter.CanCopySel();
}

VOID CMMDWnd::DoPasteSel()
{
	m_wndSplitter.DoPasteSel();
}

BOOL CMMDWnd::CanPasteSel() CONST
{
	return m_wndSplitter.CanPasteSel();
}

VOID CMMDWnd::DoDeleteSel()
{
	m_wndSplitter.DoDeleteSel();
}

BOOL CMMDWnd::CanDeleteSel() CONST
{
	return m_wndSplitter.CanDeleteSel();
}

BOOL CMMDWnd::CanPrint(UINT nFlags) CONST
{
	return(((nFlags == DISPLAY_PRINTTYPE_IMAGE  &&  GetImageView()->GetItemCount() > 0) || (nFlags == DISPLAY_PRINTTYPE_CODE  &&  GetCodeView()->GetCodeSize() > 0)) ? TRUE : FALSE);
}

BOOL CMMDWnd::DoCompile()
{
	INT  nResult;
	INT  nPosition;
	CString  szName;
	CString  szMessage[3];
	CMMDSaveDialog  cSaveDialog;

	if (IsNew())
	{
		for (szMessage[0].Format(STRING(IDS_MMD_QUESTION_SAVE), (LPCTSTR)GetTitle()); MessageBox(szMessage[0], GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES; )
		{
			if ((nResult = cSaveDialog.Create(this)) == IDOK)
			{
				if ((nPosition = SaveToDatabase()) >= 0)
				{
					UpdateDatabase(this, -(nPosition + 1));
					UpdateTitle();
					UpdateMenus();
				}
			}
			if (nResult == IDOK  &&  nPosition < 0)
			{
				szMessage[1].Format(STRING(IDS_MMD_FAILURE_SAVE), (LPCTSTR)GetTitle());
				szMessage[2].Format(STRING(IDS_MMD_FAILURE_COMPILE), (LPCTSTR)GetTitle());
				ShowMessage(szMessage[1]);
				ShowMessage(szMessage[2]);
				return FALSE;
			}
			if (nResult == IDOK) return StartCompilingMMD(GetDatabase()->GetDatabaseEngine(), GetName());
			break;
		}
		szMessage[1].Format(STRING(IDS_MMD_FAILURE_COMPILE), (LPCTSTR)GetTitle());
		ShowMessage(szMessage[1]);
		return FALSE;
	}
	if (IsModified())
	{
		if (SaveToDatabase() < 0)
		{
			szMessage[1].Format(STRING(IDS_MMD_FAILURE_SAVE), (LPCTSTR)GetTitle());
			szMessage[2].Format(STRING(IDS_MMD_FAILURE_COMPILE), (LPCTSTR)GetTitle());
			ShowMessage(szMessage[1]);
			ShowMessage(szMessage[2]);
			return FALSE;
		}
		UpdateTitle();
	}
	return StartCompilingMMD(GetDatabase()->GetDatabaseEngine(), GetName());
}

BOOL CMMDWnd::IsCompiling() CONST
{
	return IsCompilingMMD();
}

BOOL CMMDWnd::CanCompile() CONST
{
	return((GetImageView()->GetItemCount() > 0 && GetCodeView()->GetCodeSize() > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) : FALSE);
}

BOOL CMMDWnd::StopCompiling()
{
	if (IsCompilingMMD())
	{
		StopCompilingMMD();
		return TRUE;
	}
	return FALSE;
}

VOID CMMDWnd::DoTest()
{
	CHourglassCursor  cCursor;

	m_dlgTest.Create(this);
}

BOOL CMMDWnd::IsTesting() CONST
{
	return IsWindow(m_dlgTest.GetSafeHwnd());
}

BOOL CMMDWnd::CanTest() CONST
{
	CString  szCode[2];
	CString  szFileName[2];
	CFileFindEx  cFileFind[2];

	for (szFileName[0] = GetDatabase()->GetFileName(), szFileName[1] = GetDatabase()->GetUpdateFileName(); (cFileFind[0].FindFile(szFileName[0]) || cFileFind[0].FindFile(szFileName[1])) && !cFileFind[0].FindNextFile(); )
	{
		szCode[0].Format(STRING(IDS_MIMICSDISPLAYCODE_NORMAL_FILENAME), (LPCTSTR)GetName());
		szCode[1].Format(STRING(IDS_MIMICSDISPLAYCODE_UPDATE_FILENAME), (LPCTSTR)GetName());
		szCode[0] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[0];
		szCode[1] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[1];
		if ((cFileFind[1].FindFile(szCode[0]) || cFileFind[1].FindFile(szCode[1])) && !cFileFind[1].FindNextFile())
		{
			cFileFind[1].Close();
			cFileFind[0].Close();
			return CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE);
		}
		cFileFind[0].Close();
		break;
	}
	return FALSE;
}

VOID CMMDWnd::DoClose()
{
	INT  nResult;
	INT  nPosition;
	CString  szName;
	CString  szMessage[2];
	CMMDSaveDialog  cSaveDialog;

	if (IsNew() || IsModified())
	{
		for (szMessage[0].Format(STRING(IDS_MMD_QUESTION_SAVEONCLOSE), (LPCTSTR)GetTitle()); CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE) && MessageBox(szMessage[0], GetAppTitle(), MB_ICONWARNING | MB_YESNO) == IDYES; )
		{
			if ((nResult = ((szName = GetName()).IsEmpty() || IsNew()) ? cSaveDialog.Create(this) : IDOK) == IDOK && (nPosition = SaveToDatabase()) >= 0)
			{
				GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
				UpdateDatabase(this, (szName != GetName()) ? -(nPosition + 1) : nPosition);
				UpdateTitle();
			}
			if (nResult == IDOK  &&  nPosition < 0)
			{
				szMessage[1].Format(STRING(IDS_MMD_FAILURE_SAVE), (LPCTSTR)GetTitle());
				ShowMessage(szMessage[1]);
			}
			break;
		}
	}
}

BOOL CMMDWnd::GetPrintProperties(CMetaFileDC &cMetaDC, UINT nFlags) CONST
{
	return(((nFlags == DISPLAY_PRINTTYPE_IMAGE  &&  GetImageView()->GetPrintProperties(cMetaDC)) || nFlags == DISPLAY_PRINTTYPE_CODE) ? TRUE : FALSE);
}

BOOL CMMDWnd::UpdateBars()
{
	INT  nItems;
	UINT  nPanes[2];
	CString  szSize;
	CString  szMessage;

	for (nPanes[0] = ID_MMD_STATUSBAR_OBJECTPANE, nPanes[1] = ID_MMD_STATUSBAR_SIZEPANE; m_wndStatusBar.SetIndicators(nPanes, sizeof(nPanes) / sizeof(UINT)); )
	{
		szMessage.Format((!(nItems = GetMimicsCtrlCount())) ? STRING(IDS_MMD_STATUSBAR_NOOBJECTS) : ((nItems == 1) ? STRING(IDS_MMD_STATUSBAR_OBJECT) : STRING(IDS_MMD_STATUSBAR_OBJECTS)), nItems);
		szSize.Format(STRING(IDS_MMD_STATUSBAR_OBJECTSIZE), GetImageView()->GetImageSize().cx, GetImageView()->GetImageSize().cy);
		m_wndStatusBar.SetPaneText(ID_MMD_STATUSBAR_OBJECTPANE, szMessage);
		m_wndStatusBar.SetPaneText(ID_MMD_STATUSBAR_SIZEPANE, szSize);
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDWnd::UpdateBars(CMimicsItem *pItem)
{
	CSize  size;
	CPoint  point;
	CString  szSize;
	CString  szPosition;
	CString  szMessage;

	for (pItem->GetItemPosition(point, size); m_wndStatusBar.SetIndicators(nStatusBarIndicators, sizeof(nStatusBarIndicators) / sizeof(nStatusBarIndicators[0])); )
	{
		szMessage.Format(STRING(IDS_MMD_STATUSBAR_ACTIVEOBJECT), (LPCTSTR)pItem->GetItemName(), (LPCTSTR)pItem->GetItemType());
		szPosition.Format(STRING(IDS_MMD_STATUSBAR_OBJECTPOSITION), point.x - GetImageView()->GetImageOrigin().x, point.y - GetImageView()->GetImageOrigin().y);
		szSize.Format(STRING(IDS_MMD_STATUSBAR_OBJECTSIZE), size.cx, size.cy);
		m_wndStatusBar.SetPaneText(ID_MMD_STATUSBAR_OBJECTPANE, szMessage);
		m_wndStatusBar.SetPaneText(ID_MMD_STATUSBAR_POSITIONPANE, szPosition);
		m_wndStatusBar.SetPaneText(ID_MMD_STATUSBAR_SIZEPANE, szSize);
		return TRUE;
	}
	return FALSE;
}

CMMDImageView *CMMDWnd::GetImageView() CONST
{
	return m_wndSplitter.GetImageView();
}

CMMDCodeView *CMMDWnd::GetCodeView() CONST
{
	return m_wndSplitter.GetCodeView();
}

VOID CMMDWnd::UpdateTitle()
{
	INT  nPos;
	CString  szName;
	CString  szTitle[2];

	for (szName = GetName(), szTitle[0] = STRING(IDS_DISPLAY_TITLE_MMD); szName.IsEmpty(); )
	{
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_WINDOW_UNTITLED), ((nPos = szTitle[0].ReverseFind(SPACE[0])) >= 0) ? (LPCTSTR)szTitle[0].Left(nPos) : (LPCTSTR)szTitle[0]);
		break;
	}
	for (szTitle[0] = GetTitle(); !szName.IsEmpty() && szTitle[0].IsEmpty(); )
	{
		szTitle[1].Format(STRING(IDS_DISPLAY_TITLE_MMD), (LPCTSTR)szName);
		szTitle[0].Empty();
		break;
	}
	if (!szName.IsEmpty() && !szTitle[0].IsEmpty())
	{
		szTitle[0].Format(STRING(IDS_DISPLAY_TITLE_MMD), (LPCTSTR)szName);
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), (LPCTSTR)GetTitle(), (LPCTSTR)szTitle[0]);
	}
	SetWindowText(szTitle[1]);
}

VOID CMMDWnd::UpdateMenus()
{
	GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
}

INT CMMDWnd::SaveToDatabase()
{
	INT  nResultCode;
	CMMDLayout  cLayout;

	for (cLayout.SetName(GetName()), cLayout.SetTitle(GetTitle()); GetImageView()->GetImage(cLayout) && GetCodeView()->GetCode(cLayout); )
	{
		if ((nResultCode = GetDatabase()->SaveMMD(cLayout)) >= 0)
		{
			GetImageView()->SetModified(FALSE);
			GetCodeView()->SetModified(FALSE);
		}
		return nResultCode;
	}
	return -1;
}

BOOL CMMDWnd::LoadFromDatabase()
{
	CMMDLayout  cLayout;

	if (GetDatabase()->LoadMMD(GetName(), cLayout))
	{
		if (GetImageView()->SetImage(cLayout) && GetCodeView()->SetCode(cLayout))
		{
			SetTitle(cLayout.GetTitle());
			SetName(cLayout.GetName());
			return TRUE;
		}
	}
	return FALSE;
}

INT CMMDWnd::DeleteFromDatabase()
{
	return Delete(GetName());
}

CMenu *CMMDWnd::FindMenu(CMenu *pMenu, CMenu &cMenu) CONST
{
	INT  nItem;
	INT  nItems;
	CMenu  *pSubMenu;
	CString  szItem[2];

	for (nItem = 0, nItems = pMenu->GetMenuItemCount(), pSubMenu = (CMenu *)NULL; nItem < nItems; nItem++)
	{
		if (pMenu->GetMenuString(nItem, szItem[0], MF_BYPOSITION) > 0 && cMenu.GetMenuString(0, szItem[1], MF_BYPOSITION) > 0)
		{
			if (szItem[0] == szItem[1])
			{
				pSubMenu = pMenu->GetSubMenu(nItem);
				break;
			}
		}
		if (pMenu->GetMenuItemID(nItem) == (UINT)-1)
		{
			if ((pSubMenu = FindMenu(pMenu->GetSubMenu(nItem), cMenu))) break;
			continue;
		}
	}
	return((nItem < nItems) ? pSubMenu : (CMenu *)NULL);
}

BOOL CMMDWnd::EnumMenu(CMenu &cMenu) CONST
{
	INT  nItem;
	INT  nItems;
	UINT  nItemID;
	CMenu  *pSubMenu;
	CString  szItem[1];
	CStringArray  szItems;

	for (nItem = 0, nItems = GetImageView()->EnumItems(szItems); nItem < nItems; nItem++)
	{
		cMenu.AppendMenu(MF_STRING, IDM_FIRSTMIMICSOBJECT + nItem, szItems.GetAt(nItem));
		continue;
	}
	if ((pSubMenu = cMenu.GetSubMenu(0)))
	{
		for (nItem = 0, nItems = pSubMenu->GetMenuItemCount(); nItem < nItems; nItem++)
		{
			if ((nItemID = pSubMenu->GetMenuItemID(nItem)) >= 0 && nItemID != IDM_FIRSTMIMICSOBJECT)
			{
				cMenu.GetMenuString(nItemID, szItem[0], MF_BYCOMMAND);
				cMenu.AppendMenu((nItemID > 0) ? MF_STRING : MF_SEPARATOR, nItemID, szItem[0]);
			}
		}
	}
	if (nItems > 0)
	{
		cMenu.DeleteMenu(0, MF_BYPOSITION);
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szJobTitle;

	for (sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, szJobTitle.Format(STRING(IDS_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetTitle()); szJobTitle.GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle;
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0 && cDC.StartPage() >= 0) ? TRUE : FALSE);
}

BOOL CMMDWnd::PrintJob(CDC &cDC, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, CMetaFileDC &cMetaDC, WORD wFromPage, WORD wToPage)
{
	INT  nPos;
	INT  nPage;
	INT  nOldMapMode;
	INT  nPrintLength;
	BOOL  bPrintOutput[2];
	CRect  rPrintArea[3];
	CSize  sizePrintImage[2];
	CFont  cFont[DISPLAY_PRINTFONTS];
	double  fPrintScale;
	CTimeKey  tPrintTime;
	CPtrArray  pFonts;
	HENHMETAFILE  hMetaFile;

	if (StartPrintJob(cDC))
	{
		if (nFlags == DISPLAY_PRINTTYPE_IMAGE)
		{
			if ((wFromPage < 1 || wToPage > 1) && wFromPage != (WORD)-1 && wToPage != (WORD)-1)
			{
				cDC.AbortDoc();
				return TRUE;
			}
			if (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rPrintArea[0]) != ERROR  &&  CalcPrintDocTitleFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_TITLE]) && CalcPrintDocNoticeFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_NOTICE], cFont[DISPLAY_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_FOOTER]))
			{
				for (pFonts.SetAtGrow(DISPLAY_PRINTFONT_TITLE, &cFont[DISPLAY_PRINTFONT_TITLE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_FOOTER, &cFont[DISPLAY_PRINTFONT_FOOTER]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_NOTICE, &cFont[DISPLAY_PRINTFONT_NOTICE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_LOGO, &cFont[DISPLAY_PRINTFONT_LOGO]); DrawPrintDocPage(cDC, tPrintTime, pszPrinterName, pFonts, (rPrintArea[1] = rPrintArea[0]), nFlags, -1, TRUE); )
				{
					for (fPrintScale = ((sizePrintImage[0] = GetImageView()->GetImageSize()).cx > 0 && sizePrintImage[0].cy > 0) ? (((double)rPrintArea[1].Width() / (double)sizePrintImage[0].cx <= (double)rPrintArea[1].Height() / (double)sizePrintImage[0].cy) ? ((double)rPrintArea[1].Width() / (double)sizePrintImage[0].cx) : ((double)rPrintArea[1].Height() / (double)sizePrintImage[0].cy)) : 0.0, sizePrintImage[1].cx = (INT)(fPrintScale*sizePrintImage[0].cx), sizePrintImage[1].cy = (INT)(fPrintScale*sizePrintImage[0].cy); DrawPrintDocPage(cDC, tPrintTime, pszPrinterName, pFonts, (rPrintArea[1] = rPrintArea[0]), nFlags); )
					{
						for (rPrintArea[2].SetRect(rPrintArea[1].left + (rPrintArea[1].Width() - sizePrintImage[1].cx) / 2, rPrintArea[1].top, rPrintArea[1].left + (rPrintArea[1].Width() - sizePrintImage[1].cx) / 2 + sizePrintImage[1].cx, rPrintArea[1].top + sizePrintImage[1].cy); (hMetaFile = cMetaDC.CloseEnhanced()); )
						{
							cDC.PlayMetaFile(hMetaFile, rPrintArea[2]);
							DeleteEnhMetaFile(hMetaFile);
							EndPrintJob(cDC);
							return TRUE;
						}
						break;
					}
					break;
				}
			}
		}
		if (nFlags == DISPLAY_PRINTTYPE_CODE)
		{
			if (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rPrintArea[0]) != ERROR  &&  CalcPrintDocTitleFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_TITLE]) && CalcPrintDocInfoTitleFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_INFOTITLE]) && CalcPrintDocNoticeFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_NOTICE], cFont[DISPLAY_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_FOOTER]))
			{
				for (nPos = 0, nPage = 1, nPrintLength = GetCodeView()->GetTextLengthEx(GTL_PRECISE | GTL_NUMCHARS), pFonts.SetAtGrow(DISPLAY_PRINTFONT_TITLE, &cFont[DISPLAY_PRINTFONT_TITLE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_INFOTITLE, &cFont[DISPLAY_PRINTFONT_INFOTITLE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_FOOTER, &cFont[DISPLAY_PRINTFONT_FOOTER]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_NOTICE, &cFont[DISPLAY_PRINTFONT_NOTICE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_LOGO, &cFont[DISPLAY_PRINTFONT_LOGO]), fPrintScale = (rPrintArea[0].Height() > 0) ? min((double)rPrintArea[0].Width() / (double)rPrintArea[0].Height(), 1.0) : 1.0, bPrintOutput[0] = bPrintOutput[1] = FALSE; nPos < nPrintLength && wFromPage <= wToPage; nPage++)
				{
					if (DrawPrintDocPage(cDC, tPrintTime, pszPrinterName, pFonts, (rPrintArea[1] = rPrintArea[0]), nFlags, nPage, !(bPrintOutput[0] = ((nPage >= (INT)wFromPage  &&  nPage <= (INT)wToPage) || wFromPage == (WORD)-1 || wToPage == (WORD)-1) ? TRUE : FALSE)))
					{
						for (nOldMapMode = cDC.SetMapMode(MM_ISOTROPIC), cDC.SetViewportExt((INT)(10000.0*fPrintScale), (INT)(10000.0*fPrintScale)), cDC.SetWindowExt(10000, 10000), rPrintArea[2].left = (INT)(1440.0*(double)rPrintArea[1].left / ((double)cDC.GetDeviceCaps(LOGPIXELSX)*fPrintScale)), rPrintArea[2].top = (INT)(1440.0*(double)rPrintArea[1].top / ((double)cDC.GetDeviceCaps(LOGPIXELSY)*fPrintScale)), rPrintArea[2].right = (INT)(1440.0*(double)rPrintArea[1].right / ((double)cDC.GetDeviceCaps(LOGPIXELSX)*fPrintScale)), rPrintArea[2].bottom = (INT)(1440.0*(double)rPrintArea[1].bottom / ((double)cDC.GetDeviceCaps(LOGPIXELSY)*fPrintScale)); (nPos = GetCodeView()->PrintInsideRect(&cDC, rPrintArea[2], nPos, -1, bPrintOutput[0])) >= 0; )
						{
							bPrintOutput[1] = bPrintOutput[1] | bPrintOutput[0];
							break;
						}
						if ((!bPrintOutput[0] || nPage == (INT)wToPage || nPos >= nPrintLength || cDC.EndPage() >= 0) && (nPos < nPrintLength && (((nPage + 1 <= (INT)wFromPage || nPage + 1 >(INT) wToPage) && wFromPage != (WORD)-1 && wToPage != (WORD)-1) || cDC.StartPage() >= 0)))
						{
							cDC.SetMapMode(nOldMapMode);
							cDC.SetViewportExt(1, 1);
							cDC.SetWindowExt(1, 1);
							continue;
						}
						cDC.SetMapMode(nOldMapMode);
						cDC.SetViewportExt(1, 1);
						cDC.SetWindowExt(1, 1);
					}
					break;
				}
				if (nPos >= nPrintLength  &&  bPrintOutput[1])
				{
					EndPrintJob(cDC);
					return TRUE;
				}
				if (!bPrintOutput[1])
				{
					cDC.AbortDoc();
					return TRUE;
				}
			}
		}
		cDC.AbortDoc();
	}
	return FALSE;
}

BOOL CMMDWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndPage() >= 0 && cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CMMDWnd::DrawPrintDocPage(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CPtrArray &pFonts, LPRECT prClip, UINT nFlags, INT nPage, BOOL bCalc)
{
	return((DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_TITLE), nFlags, bCalc) && (nFlags == DISPLAY_PRINTTYPE_IMAGE || DrawPrintDocInfoTitle(cDC, prClip, GetPrintDocInfoTitle(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_INFOTITLE), bCalc)) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_LOGO), bCalc) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPage), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_FOOTER), bCalc)) ? TRUE : FALSE);
}

BOOL CMMDWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nFlags, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += (nFlags == DISPLAY_PRINTTYPE_IMAGE) ? ((3 * rCalc.Height()) / 2) : rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

CString CMMDWnd::GetPrintDocTitle() CONST
{
	return GetTitle();
}

CString CMMDWnd::GetPrintDocInfoTitle() CONST
{
	return STRING(IDS_PRINTDOCUMENT_TITLE_SOURCECODE);
}

BOOL CMMDWnd::StartCompilingMMD(CBinaryDatabase *pDatabase, LPCTSTR pszName)
{
	if (m_cCompileThread.StartCompiling(pDatabase, pszName))
	{
		UpdateDatabase(DATABASE_COMPONENT_MMD, pszName);
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDWnd::StartCompilingMMD(CBinaryDatabase *pDatabase, LPCTSTR pszName, BOOL bSyntax, BOOL bBatch, INT &nErrors, INT &nWarnings, BOOL &bAbort)
{
	if (m_cCompileThread.StartCompiling(pDatabase, pszName, bSyntax, bBatch, nErrors, nWarnings, bAbort))
	{
		UpdateDatabase(DATABASE_COMPONENT_MMD, pszName);
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::IsCompilingMMD()
{
	return m_cCompileThread.IsCompiling();
}

VOID CMMDWnd::StopCompilingMMD()
{
	CString  szName;

	for (szName = m_cCompileThread.GetCompileTarget(); IsCompilingMMD(); )
	{
		UpdateDatabase(~DATABASE_COMPONENT_MMD, szName);
		break;
	}
	m_cCompileThread.StopCompiling();
}

INT CMMDWnd::Delete(LPCTSTR pszName)
{
	INT  nIndex;
	CString  szFilePath;
	CString  szFileName[3];
	CFileFindEx  cFileFind[2];

	for (szFileName[0] = GetDatabase()->GetFileName(), szFileName[1] = GetDatabase()->GetUpdateFileName(); (nIndex = GetDatabase()->DeleteMMD(pszName)) >= 0; )
	{
		if ((cFileFind[0].FindFile(szFileName[0]) || cFileFind[0].FindFile(szFileName[1])) && cFileFind[0].FindNextFile() >= 0)
		{
			szFilePath = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength());
			for (szFileName[2].Format(STRING(IDS_MIMICSDISPLAYCODE_SEARCH_FILENAME), pszName), szFileName[2] = szFilePath + szFileName[2]; cFileFind[1].FindFile(szFileName[2]); )
			{
				while (cFileFind[1].FindNextFile())
				{
					CFileEx::SetAttributes(cFileFind[1].GetFilePath(), CFileEx::GetAttributes(cFileFind[1].GetFilePath()) & ~FILE_ATTRIBUTE_READONLY);
					CFileEx::Remove(cFileFind[1].GetFilePath());
				}
				CFileEx::SetAttributes(cFileFind[1].GetFilePath(), CFileEx::GetAttributes(cFileFind[1].GetFilePath()) & ~FILE_ATTRIBUTE_READONLY);
				CFileEx::Remove(cFileFind[1].GetFilePath());
				cFileFind[1].Close();
				break;
			}
			cFileFind[0].Close();
		}
		return nIndex;
	}
	return -1;
}

VOID CMMDWnd::AdjustToPrivileges()
{
	if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_MMD_CHANGE))
	{
		m_wndSplitter.UnSelectAll();
		return;
	}
}

BEGIN_MESSAGE_MAP(CMMDWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CMMDWnd)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_MMD_STATUSBAR_OBJECTPANE, OnUpdateStatusBarObjectPane)
	ON_UPDATE_COMMAND_UI(ID_MMD_STATUSBAR_POSITIONPANE, OnUpdateStatusBarPositionPane)
	ON_UPDATE_COMMAND_UI(ID_MMD_STATUSBAR_SIZEPANE, OnUpdateStatusBarSizePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDWnd message handlers

int CMMDWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayWnd::OnCreate(lpCreateStruct) != -1 && LoadAccelTable(MAKEINTRESOURCE(IDR_MMDFRAME))) ? ((IsNew() || LoadFromDatabase()) ? 0 : -1) : -1);
}

BOOL CMMDWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	return(m_wndSplitter.Create(this) && m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1));
}

void CMMDWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	CWnd  *pWnd;
	CZoomWnd  *pZoomWnd;

	if ((pZoomWnd = GetMainWnd()->GetZoomWindow()) && bActivate)
	{
		pZoomWnd->AdjustZoomFactor(GetHotSpot());
		pZoomWnd->Invalidate(FALSE);
		pZoomWnd->UpdateWindow();
	}
	if (IsWindow(pZoomWnd->GetSafeHwnd()) && !bActivate)
	{
		pZoomWnd->Invalidate(FALSE);
		pZoomWnd->UpdateWindow();
	}
	for (pWnd = CWnd::GetFocus(); GetCodeView()->HasDialogs(); )
	{
		for (GetCodeView()->ShowDialogs(bActivate); !bActivate; )
		{
			pWnd->SetFocus();
			break;
		}
		break;
	}
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CMMDWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN)
	{
		SetActiveView(GetImageView());
		GetImageView()->SetFocus();
		return;
	}
	if (nChar == VK_UP)
	{
		SetActiveView(GetCodeView());
		GetCodeView()->SetFocus();
		return;
	}
	CDisplayWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMMDWnd::OnClose()
{
	CHourglassCursor  cCursor;

	DoClose();
	CDisplayWnd::OnClose();
}

void CMMDWnd::OnDestroy()
{
	m_wndSplitter.UnSelectAll();
	CDisplayWnd::OnDestroy();
}

void CMMDWnd::OnUpdateStatusBarObjectPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMMDWnd::OnUpdateStatusBarPositionPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMMDWnd::OnUpdateStatusBarSizePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
