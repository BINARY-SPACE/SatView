// LOGO.CPP : Logo Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the logo related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/04/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CLogoWnd

IMPLEMENT_DYNCREATE(CLogoWnd, CWnd)

CLogoWnd::CLogoWnd() : CWnd()
{
	m_hLogo = (HANDLE)NULL;
}

BOOL CLogoWnd::Create(CWnd *pParentWnd, HANDLE hLogo)
{
	for (m_hLogo = hLogo; CreateEx(WS_EX_TOPMOST, AfxRegisterWndClass(CS_NOCLOSE | CS_DROPSHADOW), (LPCTSTR)NULL, WS_POPUP, 0, 0, 0, 0, pParentWnd->GetSafeHwnd(), 0, (LPVOID)NULL); )
	{
		ShowWindow(SW_SHOW);
		UpdateWindow();
		return TRUE;
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CLogoWnd, CWnd)
	//{{AFX_MSG_MAP(CLogoWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogoWnd message handlers

int CLogoWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	BITMAP  sLogo;

	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		if (SetTimer(LOGO_TIMERID, LOGO_TIMEOUT, NULL))
		{
			if (m_bmLogo.LoadBitmap(IDB_MAINFRAMELOGO) && m_bmLogo.GetObject(sizeof(sLogo), (LPVOID)&sLogo))
			{
				MoveWindow((GetSystemMetrics(SM_CXSCREEN) - sLogo.bmWidth) / 2, (GetSystemMetrics(SM_CYSCREEN) - sLogo.bmHeight) / 2, sLogo.bmWidth, sLogo.bmHeight);
				BeginWaitCursor();
				SetCapture();
				return 0;
			}
		}
	}
	return -1;
}

void CLogoWnd::OnTimer(UINT_PTR nEventID)
{
	DestroyWindow();
	SetEvent(m_hLogo);
	CWnd::OnTimer(nEventID);
}

void CLogoWnd::OnPaint()
{
	CDC  cCompatibleDC;
	BITMAP  sLogoBitmap;
	CPaintDC  cDC(this);

	if (!(GetExStyle() & WS_EX_TRANSPARENT))
	{
		if (cCompatibleDC.CreateCompatibleDC(&cDC))
		{
			if (m_bmLogo.GetObject(sizeof(sLogoBitmap), &sLogoBitmap))
			{
				cCompatibleDC.SelectObject(&m_bmLogo);
				cDC.BitBlt(0, 0, sLogoBitmap.bmWidth, sLogoBitmap.bmHeight, &cCompatibleDC, 0, 0, SRCCOPY);
			}
			cCompatibleDC.DeleteDC();
		}
	}
}

void CLogoWnd::OnDestroy()
{
	SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
	m_bmLogo.DeleteObject();
	ReleaseCapture();
	EndWaitCursor();
}
