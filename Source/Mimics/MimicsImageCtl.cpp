// MIMICSIMAGECTL.CPP : Mimics Image Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics image
// control related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2005/09/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////////////////////////////////////////////////////////////
// CMimicsImageCtrlDispatchDriver properties

VOID CMimicsImageCtrlDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsImageCtrlDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsImageCtrlDispatchDriver::SetFileName(LPCTSTR pszFileName)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FILENAME));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszFileName);
}

CString CMimicsImageCtrlDispatchDriver::GetFileName() CONST
{
	CString  szFileName;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FILENAME));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szFileName);
	return szFileName;
}

VOID CMimicsImageCtrlDispatchDriver::SetImageTransparency(BYTE nFactor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_IMAGETRANSPARENCY));

	SetProperty(GetDispatchID(szDispatch), VT_UI1, nFactor);
}

BYTE CMimicsImageCtrlDispatchDriver::GetImageTransparency() CONST
{
	BYTE  nFactor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_IMAGETRANSPARENCY));

	GetProperty(GetDispatchID(szDispatch), VT_UI1, &nFactor);
	return nFactor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageCtrlDispatchDriver operations

VOID CMimicsImageCtrlDispatchDriver::SetImageOrigin(CONST POINT &pt)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETIMAGEORIGIN));
	static BYTE  pParameters[] = VTS_XPOS_PIXELS VTS_YPOS_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, pt.x, pt.y);
}

CPoint CMimicsImageCtrlDispatchDriver::GetImageOrigin() CONST
{
	OLE_XPOS_PIXELS  nXPos;
	OLE_YPOS_PIXELS  nYPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETIMAGEORIGIN));
	static BYTE  pParameters[] = VTS_PXPOS_PIXELS VTS_PYPOS_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &nXPos, &nYPos);
	return CPoint(nXPos, nYPos);
}

VOID CMimicsImageCtrlDispatchDriver::SetImageSize(CONST SIZE &size)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETIMAGESIZE));
	static BYTE  pParameters[] = VTS_XSIZE_PIXELS VTS_YSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, size.cx, size.cy);
}

CSize CMimicsImageCtrlDispatchDriver::GetImageSize() CONST
{
	OLE_XSIZE_PIXELS  cx;
	OLE_YSIZE_PIXELS  cy;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETIMAGESIZE));
	static BYTE  pParameters[] = VTS_PXSIZE_PIXELS VTS_PYSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &cx, &cy);
	return CSize(cx, cy);
}


IMPLEMENT_DYNCREATE(CMimicsImageCtrl, CMimicsCtrl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsImageCtrl, CMimicsCtrl)
	//{{AFX_MSG_MAP(CMimicsImageCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMimicsImageCtrl, CMimicsCtrl)
	//{{AFX_DISPATCH_MAP(CMimicsImageCtrl)
	DISP_PROPERTY_EX(CMimicsImageCtrl, "Style", GetStyle, SetStyle, VT_I4)
	DISP_PROPERTY_EX(CMimicsImageCtrl, "FileName", GetFileName, SetFileName, VT_BSTR)
	DISP_PROPERTY_EX(CMimicsImageCtrl, "ImageTransparency", GetImageTransparency, SetImageTransparency, VT_UI1)
	DISP_FUNCTION(CMimicsImageCtrl, "SetImageOrigin", SetImageOrigin, VT_EMPTY, VTS_XPOS_PIXELS VTS_YPOS_PIXELS)
	DISP_FUNCTION(CMimicsImageCtrl, "GetImageOrigin", GetImageOrigin, VT_EMPTY, VTS_PXPOS_PIXELS VTS_PYPOS_PIXELS)
	DISP_FUNCTION(CMimicsImageCtrl, "SetImageSize", SetImageSize, VT_EMPTY, VTS_XSIZE_PIXELS VTS_YSIZE_PIXELS)
	DISP_FUNCTION(CMimicsImageCtrl, "GetImageSize", GetImageSize, VT_EMPTY, VTS_PXSIZE_PIXELS VTS_PYSIZE_PIXELS)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMimicsImageCtrl, CMimicsCtrl)
	//{{AFX_EVENT_MAP(CMimicsImageCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMimicsImageCtrl, 2)
	PROPPAGEID(CMimicsImageGeneralPage::guid)
	PROPPAGEID(CMimicsImageOutlinePage::guid)
END_PROPPAGEIDS(CMimicsImageCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMimicsImageCtrl, "MIMICS.MimicsImageCtrl.1", 0xd9b0da19, 0xc96c, 0x11d3, 0xb5, 0xe7, 0, 0x60, 0x8, 0x2d, 0x53, 0x89)

/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMimicsImageCtrl, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor)

/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMimicsImage = { 0xd9b0da17,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };
const IID BASED_CODE IID_DMimicsImageEvents = { 0xd9b0da18,0xc96c,0x11d3,{ 0xb5,0xe7,0,0x60,0x8,0x2d,0x53,0x89 } };

/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE  dwMimicsImageOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMimicsImageCtrl, IDS_MIMICSIMAGECTRL_DESCRIPTIVENAME, dwMimicsImageOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMimicsImageCtrl::CMimicsImageCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMimicsImageCtrl

BOOL CMimicsImageCtrl::CMimicsImageCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	return((bRegister) ? AfxOleRegisterControlClass(AfxGetInstanceHandle(), m_clsid, m_lpszProgID, IDS_MIMICSIMAGECTRL_DESCRIPTIVENAME, IDB_MIMICSIMAGECTRL, afxRegApartmentThreading, dwMimicsImageOleMisc, CMimicsApp::guidApp, CMimicsApp::wAppVerMajor, CMimicsApp::wAppVerMinor) : AfxOleUnregisterClass(m_clsid, m_lpszProgID));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsImageCtrl

CMimicsImageCtrl::CMimicsImageCtrl() : CMimicsCtrl()
{
	m_szType = STRING(IDS_MIMICSIMAGECTRL_TYPE);
	InitializeIIDs(&IID_DMimicsImage, &IID_DMimicsImageEvents);
	InitializeProps();
}

CMimicsImageCtrl::~CMimicsImageCtrl()
{
	m_cImage.Destroy();
}

VOID CMimicsImageCtrl::InitializeProps()
{
	m_nStyle = MIMICSIMAGECTRL_TYPE_NORMAL;
	m_szFileName.Empty();
	m_ptImage.x = 0;
	m_ptImage.y = 0;
	m_sizeImage.cx = 100;
	m_sizeImage.cy = 100;
	m_nImageTransparency = 0xFF;
}

void CMimicsImageCtrl::SetStyle(LONG nStyle)
{
	if (nStyle != m_nStyle)
	{
		m_nStyle = nStyle;
		Refresh();
	}
}

LONG CMimicsImageCtrl::GetStyle() CONST
{
	return m_nStyle;
}

void CMimicsImageCtrl::SetFileName(LPCTSTR pszFileName)
{
	if (m_szFileName.CompareNoCase(pszFileName))
	{
		for (; !m_cImage.IsNull(); )
		{
			m_cImage.Destroy();
			break;
		}
		m_cImage.Load((m_szFileName = pszFileName));
		Refresh();
	}
}

BSTR CMimicsImageCtrl::GetFileName() CONST
{
	return m_szFileName.AllocSysString();
}

void CMimicsImageCtrl::SetImageOrigin(OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y)
{
	if (x != m_ptImage.x || y != m_ptImage.y)
	{
		m_ptImage.x = x;
		m_ptImage.y = y;
		Refresh();
	}
}

void CMimicsImageCtrl::GetImageOrigin(OLE_XPOS_PIXELS *x, OLE_YPOS_PIXELS *y) CONST
{
	OLE_XPOS_PIXELS  nXPos = m_ptImage.x;
	OLE_YPOS_PIXELS  nYPos = m_ptImage.y;

	CopyMemory(x, &nXPos, sizeof(OLE_XPOS_PIXELS));
	CopyMemory(y, &nYPos, sizeof(OLE_YPOS_PIXELS));
}

void CMimicsImageCtrl::SetImageSize(OLE_XSIZE_PIXELS cx, OLE_YSIZE_PIXELS cy)
{
	if (cx != m_sizeImage.cx || cy != m_sizeImage.cy)
	{
		m_sizeImage.cx = cx;
		m_sizeImage.cy = cy;
		Refresh();
	}
}

void CMimicsImageCtrl::GetImageSize(OLE_XSIZE_PIXELS *cx, OLE_YSIZE_PIXELS *cy) CONST
{
	OLE_XSIZE_PIXELS  dx = m_sizeImage.cx;
	OLE_YSIZE_PIXELS  dy = m_sizeImage.cy;

	CopyMemory(cx, &dx, sizeof(OLE_XSIZE_PIXELS));
	CopyMemory(cy, &dy, sizeof(OLE_YSIZE_PIXELS));
}

void CMimicsImageCtrl::SetImageTransparency(BYTE nFactor)
{
	if (nFactor != m_nImageTransparency)
	{
		m_nImageTransparency = nFactor;
		Refresh();
	}
}

BYTE CMimicsImageCtrl::GetImageTransparency() CONST
{
	return m_nImageTransparency;
}

VOID CMimicsImageCtrl::DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape)
{
	INT  nClip;
	HPEN  hPen;
	HPEN  hOldPen;
	BOOL  bImage;
	RECT  rImage;
	CRgn  rgClip[2];
	POINT  ptImage[4];

	for (ptImage[0].x = pRect->left, ptImage[0].y = pRect->bottom, ptImage[1].x = pRect->left, ptImage[1].y = pRect->top, ptImage[2].x = pRect->right, ptImage[2].y = pRect->top, ptImage[3].x = pRect->right, ptImage[3].y = pRect->bottom; LPtoDP(hDC, ptImage, sizeof(ptImage) / sizeof(POINT)); )
	{
		if (rgClip[0].CreatePolygonRgn(ptImage, sizeof(ptImage) / sizeof(POINT), WINDING) && rgClip[1].CreateRectRgn(0, 0, 0, 0))
		{
			if ((nClip = GetClipRgn(hDC, (HRGN)rgClip[1].GetSafeHandle())) >= 0)
			{
				if (SelectClipRgn(hDC, (HRGN)rgClip[0].GetSafeHandle()) != ERROR)
				{
					if ((bImage = !m_cImage.IsNull()) && bShape)
					{
						SetRect(&rImage, pRect->left + m_ptImage.x, pRect->top + m_ptImage.y, pRect->left + m_ptImage.x + m_cImage.GetWidth(), pRect->top + m_ptImage.y + m_cImage.GetHeight());
						FillRect(hDC, &rImage, (HBRUSH)GetStockObject(WHITE_BRUSH));
					}
					for (; bImage && !bShape; )
					{
						m_cImage.AlphaBlend(hDC, pRect->left + m_ptImage.x, pRect->top + m_ptImage.y, (m_cImage.GetWidth()*m_sizeImage.cx) / 100, (m_cImage.GetHeight()*m_sizeImage.cy) / 100, 0, 0, m_cImage.GetWidth(), m_cImage.GetHeight(), m_nImageTransparency);
						break;
					}
				}
				SelectClipRgn(hDC, (nClip > 0) ? (HRGN)rgClip[1].GetSafeHandle() : (HRGN)NULL);
			}
			rgClip[0].DeleteObject();
			rgClip[1].DeleteObject();
		}
		break;
	}
	if (m_cImage.IsNull() && !bShape)
	{
		if ((hPen = CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWTEXT))))
		{
			if ((hOldPen = (HPEN)SelectObject(hDC, hPen)) != (HPEN)NULL)
			{
				MoveToEx(hDC, pRect->left, pRect->bottom, (LPPOINT)NULL);
				LineTo(hDC, pRect->left, pRect->top);
				LineTo(hDC, pRect->right - 1, pRect->top);
				LineTo(hDC, pRect->right - 1, pRect->bottom - 1);
				LineTo(hDC, pRect->left, pRect->bottom - 1);
				LineTo(hDC, pRect->right - 1, pRect->top);
				MoveToEx(hDC, pRect->right - 1, pRect->bottom - 1, (LPPOINT)NULL);
				LineTo(hDC, pRect->left, pRect->top);
				SelectObject(hDC, hOldPen);
			}
			DeletePen(hPen);
		}
	}
	if (m_cImage.IsNull() && bShape)
	{
		SetRect(&rImage, pRect->left, pRect->top, pRect->right, pRect->bottom);
		FillRect(hDC, &rImage, (HBRUSH)GetStockObject(WHITE_BRUSH));
	}
}

void CMimicsImageCtrl::DoPropExchange(CPropExchange *pPX)
{
	ExchangeVersion(pPX, MAKELONG(CMimicsApp::wAppVerMinor, CMimicsApp::wAppVerMajor));
	CMimicsCtrl::DoPropExchange(pPX);
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageCtrl message handlers
