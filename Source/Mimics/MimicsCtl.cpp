// MIMICSCTL.CPP : Mimics Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics control
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/01 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////////////////////////////////////////////////////////////
// CMimicsCtrlDispatchDriver properties

VOID CMimicsCtrlDispatchDriver::SetName(LPCTSTR pszName)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_NAME));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszName);
}

CString CMimicsCtrlDispatchDriver::GetName() CONST
{
	CString  szName;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_NAME));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szName);
	return szName;
}

VOID CMimicsCtrlDispatchDriver::SetType(LPCTSTR pszType)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TYPE));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszType);
}

CString CMimicsCtrlDispatchDriver::GetType() CONST
{
	CString  szType;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TYPE));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szType);
	return szType;
}

VOID CMimicsCtrlDispatchDriver::SetToolTipText(LPCTSTR pszText)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TOOLTIPTEXT));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszText);
}

CString CMimicsCtrlDispatchDriver::GetToolTipText() CONST
{
	CString  szText;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TOOLTIPTEXT));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szText);
	return szText;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsCtrlDispatchDriver operations

VOID CMimicsCtrlDispatchDriver::SetInitialSize(CONST SIZE &size)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINITIALSIZE));
	static BYTE  pParameters[] = VTS_XSIZE_PIXELS VTS_YSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, size.cx, size.cy);
}

CSize CMimicsCtrlDispatchDriver::GetInitialSize() CONST
{
	OLE_XSIZE_PIXELS  cx;
	OLE_YSIZE_PIXELS  cy;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINITIALSIZE));
	static BYTE  pParameters[] = VTS_PXSIZE_PIXELS VTS_PYSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &cx, &cy);
	return CSize(cx, cy);
}

COleDispatchDriver *CMimicsCtrlDispatchDriver::GetDispatchDriver() CONST
{
	return((COleDispatchDriver *) this);
}

DISPID CMimicsCtrlDispatchDriver::GetDispatchID(OLECHAR FAR *pszMethod) CONST
{
	DISPID  nDispID;

	return((m_lpDispatch != (LPDISPATCH)NULL  &&  m_lpDispatch->GetIDsOfNames(IID_NULL, &pszMethod, 1, GetLanguageID(), &nDispID) == S_OK) ? nDispID : 0);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsBlinkThread

IMPLEMENT_DYNCREATE(CMimicsBlinkThread, CWinThread)

CMimicsBlinkThread::CMimicsBlinkThread() : CWinThread()
{
	m_nInterval = 0;
	m_bAutoDelete = FALSE;
}

CMimicsBlinkThread::~CMimicsBlinkThread()
{
	StopBlinking(TRUE);
}

BOOL CMimicsBlinkThread::InitInstance()
{
	return TRUE;
}

BOOL CMimicsBlinkThread::StartBlinking(class CMimicsCtrl *pCtrl, INT nInterval)
{
	if (m_hThread != (HANDLE)NULL)
	{
		CloseHandle(m_hThread);
		CommonConstruct();
		m_bAutoDelete = 0;
	}
	if (CreateThread(CREATE_SUSPENDED))
	{
		SetThreadPriority(THREAD_PRIORITY_NORMAL);
		m_pThreadParams = pCtrl;
		m_nInterval = nInterval;
		m_cEvent.ResetEvent();
		ResumeThread();
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsBlinkThread::StopBlinking(BOOL bWait)
{
	return((IsBlinking() && SetEvent(m_cEvent) && (!bWait || WaitForSingleObject(m_hThread, INFINITE) == WAIT_OBJECT_0)) ? TRUE : FALSE);
}

BOOL CMimicsBlinkThread::IsBlinking() CONST
{
	DWORD  dwExitCode;

	return((GetExitCodeThread(m_hThread, &dwExitCode) && dwExitCode == STILL_ACTIVE) ? TRUE : FALSE);
}

int CMimicsBlinkThread::Run()
{
	CMimicsCtrl  *pCtrl;

	for (pCtrl = (CMimicsCtrl *)m_pThreadParams; WaitForSingleObject(m_cEvent, m_nInterval) == WAIT_TIMEOUT; )
	{
		if (!pCtrl->IsVisible())
		{
			pCtrl->Show();
			continue;
		}
		pCtrl->Hide();
	}
	pCtrl->Show();
	return 0;
}

BEGIN_MESSAGE_MAP(CMimicsBlinkThread, CWinThread)
	//{{AFX_MSG_MAP(CMimicsBlinkThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsBlinkThread message handlers


IMPLEMENT_DYNCREATE(CMimicsCtrl, COleControl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMimicsCtrl, COleControl)
	//{{AFX_MSG_MAP(CMimicsCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMimicsCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CMimicsCtrl)
	DISP_PROPERTY_EX(CMimicsCtrl, "Name", GetName, SetName, VT_BSTR)
	DISP_PROPERTY_EX(CMimicsCtrl, "Type", GetType, SetType, VT_BSTR)
	DISP_PROPERTY_EX(CMimicsCtrl, "ToolTipText", GetToolTipText, SetToolTipText, VT_BSTR)
	DISP_FUNCTION(CMimicsCtrl, "SetInitialSize", SetInitialSize, VT_EMPTY, VTS_XSIZE_PIXELS VTS_YSIZE_PIXELS)
	DISP_FUNCTION(CMimicsCtrl, "GetInitialSize", GetInitialSize, VT_EMPTY, VTS_PXSIZE_PIXELS VTS_PYSIZE_PIXELS)
	DISP_FUNCTION(CMimicsCtrl, "Show", Show, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsCtrl, "Hide", Hide, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CMimicsCtrl, "IsVisible", IsVisible, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CMimicsCtrl, "Blink", Blink, VT_BOOL, VTS_I4)
	DISP_FUNCTION(CMimicsCtrl, "Draw", Draw, VT_EMPTY, VTS_HANDLE VTS_PVARIANT VTS_PVARIANT VTS_BOOL)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMimicsCtrl, COleControl)
	//{{AFX_EVENT_MAP(CMimicsCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMimicsCtrl

CMimicsCtrl::CMimicsCtrl() : COleControl()
{
	m_szName.Empty();
	m_szType.Empty();
	m_szToolTipText.Empty();
	m_bVisible = TRUE;
	SetInitialSize(MIMICSCTRL_DEFAULT_CX, MIMICSCTRL_DEFAULT_CY);
}

CMimicsCtrl::~CMimicsCtrl()
{
	m_cBlinkThread.StopBlinking(TRUE);
}

void CMimicsCtrl::InitializeProps()
{
	return;
}

void CMimicsCtrl::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

BSTR CMimicsCtrl::GetName() CONST
{
	return m_szName.AllocSysString();
}

void CMimicsCtrl::SetType(LPCTSTR pszType)
{
	m_szType = pszType;
}

BSTR CMimicsCtrl::GetType() CONST
{
	return m_szType.AllocSysString();
}

void CMimicsCtrl::SetToolTipText(LPCTSTR pszText)
{
	m_szToolTipText = pszText;
}

BSTR CMimicsCtrl::GetToolTipText() CONST
{
	return m_szToolTipText.AllocSysString();
}

void CMimicsCtrl::SetInitialSize(OLE_XSIZE_PIXELS cx, OLE_YSIZE_PIXELS cy)
{
	m_sizeCtrl.cx = cx;
	m_sizeCtrl.cy = cy;
	COleControl::SetInitialSize(cx, cy);
}

void CMimicsCtrl::GetInitialSize(OLE_XSIZE_PIXELS *cx, OLE_YSIZE_PIXELS *cy) CONST
{
	OLE_XSIZE_PIXELS  dx = m_sizeCtrl.cx;
	OLE_YSIZE_PIXELS  dy = m_sizeCtrl.cy;

	CopyMemory(cx, &dx, sizeof(OLE_XSIZE_PIXELS));
	CopyMemory(cy, &dy, sizeof(OLE_YSIZE_PIXELS));
}

void CMimicsCtrl::Show()
{
	if (!m_bVisible)
	{
		InterlockedExchange(&m_bVisible, TRUE);
		Refresh();
	}
}

void CMimicsCtrl::Hide()
{
	if (m_bVisible)
	{
		InterlockedExchange(&m_bVisible, FALSE);
		Refresh();
	}
}

BOOL CMimicsCtrl::IsVisible() CONST
{
	return m_bVisible;
}

BOOL CMimicsCtrl::Blink(LONG nInterval)
{
	return(((!nInterval  &&  m_cBlinkThread.IsBlinking() && m_cBlinkThread.StopBlinking()) || (nInterval > 0 && !m_cBlinkThread.IsBlinking() && m_cBlinkThread.StartBlinking(this, nInterval))) ? TRUE : FALSE);
}

void CMimicsCtrl::Draw(OLE_HANDLE hDC, VARIANT *pRect, VARIANT *pxForm, BOOL bShape)
{
	DrawCtrl((HDC)(DWORD_PTR)hDC, (CONST RECT *) pRect, (CONST XFORM *) pxForm, bShape);
}

void CMimicsCtrl::OnDraw(CDC *pDC, const CRect &rcBounds, const CRect &rcInvalid)
{
	XFORM  xForm;
	CRect  rItem(rcBounds);

	xForm.eM11 = xForm.eM22 = 1.0;
	xForm.eM12 = xForm.eM21 = 0.0;
	xForm.eDx = xForm.eDy = 0.0;
	DrawCtrl(pDC->GetSafeHdc(), rItem, &xForm);
}

VOID CMimicsCtrl::DrawCtrl(HDC hDC, CONST RECT *pRect, BOOL bShape)
{
	return;
}
VOID CMimicsCtrl::DrawCtrl(HDC hDC, CONST RECT *pRect, CONST XFORM *pxForm, BOOL bShape)
{
	INT  nMode;
	XFORM  xForm[2];

	nMode = SetGraphicsMode(hDC, GM_ADVANCED);
	xForm[0].eM11 = xForm[1].eM11 = pxForm->eM11;
	xForm[0].eM12 = xForm[1].eM12 = pxForm->eM12;
	xForm[0].eM21 = xForm[1].eM21 = pxForm->eM21;
	xForm[0].eM22 = xForm[1].eM22 = pxForm->eM22;
	xForm[0].eDx = xForm[1].eDx = pxForm->eDx;
	xForm[0].eDy = xForm[1].eDy = pxForm->eDy;
	xForm[0].eDx -= xForm[1].eDx*xForm[1].eM11 + xForm[1].eDy*xForm[1].eM21;
	xForm[0].eDy -= xForm[1].eDx*xForm[1].eM12 + xForm[1].eDy*xForm[1].eM22;
	if (GetWorldTransform(hDC, &xForm[1]) && SetWorldTransform(hDC, &xForm[0]))
	{
		DrawCtrl(hDC, pRect, bShape);
		SetWorldTransform(hDC, &xForm[1]);
	}
	SetGraphicsMode(hDC, nMode);
}

HPEN CMimicsCtrl::CreatePen(DWORD dwStyle, DWORD dwWidth, COLORREF nColor)
{
	return CreatePen(dwStyle, dwWidth, nColor, BS_SOLID, 0);
}
HPEN CMimicsCtrl::CreatePen(DWORD dwStyle, DWORD dwWidth, COLORREF nColor, UINT lbStyle, LONG lbHatch)
{
	LOGBRUSH  sPenBrush;

	sPenBrush.lbColor = nColor;
	sPenBrush.lbStyle = lbStyle;
	sPenBrush.lbHatch = lbHatch;
	return ExtCreatePen(dwStyle, dwWidth, &sPenBrush, 0, (CONST DWORD *) NULL);
}

VOID CMimicsCtrl::DeletePen(HPEN hPen)
{
	DeleteObject(hPen);
}

HRESULT CMimicsCtrl::GetClassID(LPCLSID pclsid)
{
	return FALSE;
}

UINT CMimicsCtrl::GetUserTypeNameID()
{
	return 0;
}

DWORD CMimicsCtrl::GetControlFlags()
{
	return COleControl::GetControlFlags() | windowlessActivate | canOptimizeDraw;
}

DWORD CMimicsCtrl::GetMiscStatus()
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsCtrl message handlers

void CMimicsCtrl::OnResetState()
{
	COleControl::OnResetState();
}
