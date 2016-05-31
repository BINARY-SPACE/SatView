// MIMICSCONTROLS.CPP : Mimics Custom Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics custom
// control related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/22 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMimicsCustomControls

BOOL CMimicsCustomControls::RegisterCustomControls()
{
	BOOL  bSuccess;

	bSuccess = CMimicsSimpleEdit::RegisterClass();
	bSuccess &= CMimicsNumberEdit::RegisterClass();
	bSuccess &= CMimicsTextEdit::RegisterClass();
	bSuccess &= CMimicsSimpleListBox::RegisterClass();
	bSuccess &= CMimicsColorsComboBox::RegisterClass();
	bSuccess &= CMimicsLineStylesComboBox::RegisterClass();
	bSuccess &= CMimicsLineSymbolsComboBox::RegisterClass();
	bSuccess &= CMimicsHatchesComboBox::RegisterClass();
	bSuccess &= CMimicsFontsComboBox::RegisterClass();
	bSuccess &= CMimicsAlignmentComboBox::RegisterClass();
	bSuccess &= CMimicsSpinBox::RegisterClass();
	bSuccess &= CMimicsTimeSpinBox::RegisterClass();
	return bSuccess;
}

BOOL CMimicsCustomControls::UnregisterCustomControls()
{
	BOOL  bSuccess;

	bSuccess = CMimicsSimpleEdit::UnregisterClass();
	bSuccess &= CMimicsNumberEdit::UnregisterClass();
	bSuccess &= CMimicsTextEdit::UnregisterClass();
	bSuccess &= CMimicsSimpleListBox::UnregisterClass();
	bSuccess &= CMimicsColorsComboBox::UnregisterClass();
	bSuccess &= CMimicsLineStylesComboBox::UnregisterClass();
	bSuccess &= CMimicsLineSymbolsComboBox::UnregisterClass();
	bSuccess &= CMimicsHatchesComboBox::UnregisterClass();
	bSuccess &= CMimicsFontsComboBox::UnregisterClass();
	bSuccess &= CMimicsAlignmentComboBox::UnregisterClass();
	bSuccess &= CMimicsSpinBox::UnregisterClass();
	bSuccess &= CMimicsTimeSpinBox::UnregisterClass();
	return bSuccess;
}

CRuntimeClass *CMimicsCustomControls::GetCustomControlBaseClass(CRuntimeClass *pClass)
{
	return((AfxIsValidAddress(pClass, sizeof(CRuntimeClass), FALSE)) ? pClass->m_pfnGetBaseClass() : (CRuntimeClass *)NULL);
}

CFont *CMimicsCustomControls::GetCustomControlFont(CONST CWnd *pControl)
{
	CFont  *pFont[2];
	CFontTools  cFontTools;

	if (IsWindow(pControl->GetSafeHwnd()))
	{
		if ((pFont[0] = pControl->GetFont())) return pFont[0];
		if ((pFont[0] = pControl->GetParent()->GetFont())) return pFont[0];
		if ((pFont[0] = new CFont) != (CFont *)NULL)
		{
			if (cFontTools.QueryDefaultFont(pFont[0]))
			{
				if ((pFont[1] = CFont::FromHandle((HFONT)pFont[0]->Detach())))
				{
					delete pFont[0];
					return pFont[1];
				}
			}
			delete pFont[0];
		}
	}
	return CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsSimpleEdit

IMPLEMENT_DYNCREATE(CMimicsSimpleEdit, CEdit)

BOOL CMimicsSimpleEdit::Create(CWnd *pParentWnd, CONST RECT &rect, INT nID, DWORD dwStyle)
{
	if (CEdit::Create((MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (ES_MULTILINE | ES_LEFT | ES_CENTER | ES_RIGHT | ES_LOWERCASE | ES_UPPERCASE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_OEMCONVERT)) & ~(ES_NOHIDESEL | ES_PASSWORD | ES_WANTRETURN))), HIWORD(dwStyle)) | WS_CHILD) & ~WS_TABSTOP, rect, pParentWnd, nID))
	{
		SetFont(CMimicsCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsSimpleEdit::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsSimpleEdit  CMimicsSimpleEdit;

	if ((pClass = CMimicsSimpleEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName  &&  GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceMimicsSimpleEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMimicsSimpleEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMimicsSimpleEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMimicsSimpleEdit::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsSimpleEdit  CMimicsSimpleEdit;

	if ((pClass = CMimicsSimpleEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CMimicsSimpleEdit, CEdit)
	//{{AFX_MSG_MAP(CMimicsSimpleEdit)
	ON_WM_NCCREATE()
	ON_WM_SETCURSOR()
	ON_WM_SETFOCUS()
	ON_WM_ENABLE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsSimpleEdit message handlers

BOOL CMimicsSimpleEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	for (m_szContents = lpCreateStruct->lpszName; !IsThemeActive(); )
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | ((lpCreateStruct->style & WS_BORDER) ? WS_EX_CLIENTEDGE : 0));
		SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~(lpCreateStruct->style & WS_BORDER));
		break;
	}
	return CEdit::OnNcCreate(lpCreateStruct);
}

BOOL CMimicsSimpleEdit::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
	GetParent()->SendMessage(WM_SETCURSOR, (WPARAM)GetParent()->GetSafeHwnd(), MAKELPARAM(nHitTest, message));
	return TRUE;
}

void CMimicsSimpleEdit::OnSetFocus(CWnd *pOldWnd)
{
	return;
}

void CMimicsSimpleEdit::OnEnable(BOOL bEnable)
{
	CString  szContents;

	SetWindowText((bEnable) ? (LPCTSTR)(szContents = m_szContents) : EMPTYSTRING);
	m_szContents = szContents;
	CEdit::OnEnable(bEnable);
}

void CMimicsSimpleEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	return;
}

void CMimicsSimpleEdit::OnMButtonDown(UINT nFlags, CPoint point)
{
	return;
}

void CMimicsSimpleEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	return;
}

LRESULT CMimicsSimpleEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	m_szContents = (LPCTSTR)lParam;
	return Default();
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsSimpleEdit

IMPLEMENT_DYNCREATE(CResourceMimicsSimpleEdit, CMimicsSimpleEdit)

WNDPROC CResourceMimicsSimpleEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMimicsSimpleEdit::CResourceMimicsSimpleEdit(HWND hWnd) : CMimicsSimpleEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsSimpleEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsSimpleEdit  *pResourceSimpleEdit;

	if ((pResourceSimpleEdit = new CResourceMimicsSimpleEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC *CResourceMimicsSimpleEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMimicsSimpleEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsSimpleEdit, CMimicsSimpleEdit)
	//{{AFX_MSG_MAP(CResourceMimicsSimpleEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsSimpleEdit message handlers

BOOL CResourceMimicsSimpleEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (ES_MULTILINE | ES_LEFT | ES_CENTER | ES_RIGHT | ES_LOWERCASE | ES_UPPERCASE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_OEMCONVERT)) & ~(ES_NOHIDESEL | ES_PASSWORD | ES_WANTRETURN))), HIWORD(lpCreateStruct->style)) | WS_CHILD) & ~WS_TABSTOP));
	return CMimicsSimpleEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsNumberEdit

IMPLEMENT_DYNCREATE(CMimicsNumberEdit, CEdit)

CMimicsNumberEdit::CMimicsNumberEdit() : CEdit()
{
	m_nBase = 10;
	m_nDigits = 0;
	m_nMin = m_nMax = 0;
	m_bMinusZero = FALSE;
	m_bAutoCompletion = TRUE;
}

BOOL CMimicsNumberEdit::Create(CWnd *pParentWnd, CONST RECT &rect, INT nID, DWORD dwStyle, BOOL bMinusZero)
{
	if (CEdit::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LOWERCASE | ES_UPPERCASE | ES_NUMBER | ES_PASSWORD | ES_READONLY | ES_WANTRETURN)) | ES_MULTILINE), HIWORD(dwStyle)) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CMimicsCustomControls::GetCustomControlFont(this));
		m_bMinusZero = bMinusZero;
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsNumberEdit::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsNumberEdit  cNumberEdit;

	if ((pClass = cNumberEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName  &&  GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceMimicsNumberEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMimicsNumberEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMimicsNumberEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMimicsNumberEdit::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsNumberEdit  cNumberEdit;

	if ((pClass = cNumberEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

VOID CMimicsNumberEdit::EnableMinusZero(BOOL bEnable)
{
	m_bMinusZero = bEnable;
}

BOOL CMimicsNumberEdit::IsMinusZeroEnabled() CONST
{
	return m_bMinusZero;
}

BOOL CMimicsNumberEdit::IsMinusZero() CONST
{
	CString  szNumber;

	GetWindowText(szNumber);
	return CheckMinusZero(szNumber);
}

VOID CMimicsNumberEdit::EnableAutoCompletion(BOOL bEnable)
{
	m_bAutoCompletion = bEnable;
}

BOOL CMimicsNumberEdit::IsAutoCompletionEnabled() CONST
{
	return m_bAutoCompletion;
}

VOID CMimicsNumberEdit::Format()
{
	CWnd  *pWnd;
	CRect  rNumberEdit;
	CRect  rFormatArea;

	for (; (pWnd = GetParent()) && (pWnd->IsKindOf(RUNTIME_CLASS(CMimicsSpinBox)) || pWnd->IsKindOf(RUNTIME_CLASS(CMimicsTimeSpinBox))); )
	{
		SetMargins(0, 0);
		break;
	}
	GetRect(rFormatArea);
	GetClientRect(rNumberEdit);
	rFormatArea.SetRect(rFormatArea.left, (rNumberEdit.Height() - rFormatArea.Height()) / 2, rFormatArea.right, (rNumberEdit.Height() - rFormatArea.Height()) / 2 + rFormatArea.Height());
	SetRect(rFormatArea);
}

BOOL CMimicsNumberEdit::CheckMinusZero(LPCTSTR pszNumber) CONST
{
	return((!ConstructMinusZero(m_nDigits + 1).Compare(pszNumber)) ? m_bMinusZero : FALSE);
}

CString CMimicsNumberEdit::ConstructMinusZero(UINT nDigits) CONST
{
	CStringTools  cStringTools;

	return((nDigits > 0) ? (cStringTools.ConvertIntToString(-1).GetAt(0) + cStringTools.ConvertIntToPaddedString(0, nDigits - 1)) : (cStringTools.ConvertIntToString(-1).GetAt(0) + cStringTools.ConvertIntToString(0)));
}

BEGIN_MESSAGE_MAP(CMimicsNumberEdit, CEdit)
	//{{AFX_MSG_MAP(CMimicsNumberEdit)
	ON_WM_NCCREATE()
	ON_WM_SIZE()
	ON_WM_ENABLE()
	ON_WM_GETDLGCODE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_MESSAGE(WM_SETFONT, OnFont)
	ON_MESSAGE(WM_SETTEXT, OnNumber)
	ON_MESSAGE(NEM_SETBASE, OnSetBase)
	ON_MESSAGE(NEM_GETBASE, OnGetBase)
	ON_MESSAGE(NEM_SETRANGE, OnSetRange)
	ON_MESSAGE(NEM_GETRANGE, OnGetRange)
	ON_MESSAGE(NEM_SETPOS, OnSetPos)
	ON_MESSAGE(NEM_GETPOS, OnGetPos)
	ON_MESSAGE(NEM_SETSEL, OnSetSel)
	ON_MESSAGE(NEM_GETSEL, OnGetSel)
	ON_MESSAGE(NEM_CHECK, OnCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsNumberEdit message handlers

BOOL CMimicsNumberEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!IsThemeActive())
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | ((lpCreateStruct->style & WS_BORDER) ? WS_EX_CLIENTEDGE : 0));
		SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~(lpCreateStruct->style & WS_BORDER));
	}
	return CEdit::OnNcCreate(lpCreateStruct);
}

void CMimicsNumberEdit::OnSize(UINT nType, int cx, int cy)
{
	Default();
	Format();
}

void CMimicsNumberEdit::OnEnable(BOOL bEnable)
{
	for (; bEnable; )
	{
		SetPos(GetPos());
		break;
	}
	for (; !bEnable; )
	{
		SetWindowText(EMPTYSTRING);
		break;
	}
	CEdit::OnEnable(bEnable);
}

UINT CMimicsNumberEdit::OnGetDlgCode()
{
	return CEdit::OnGetDlgCode() | DLGC_WANTARROWS | DLGC_WANTALLKEYS | DLGC_WANTCHARS;
}

void CMimicsNumberEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	CMimicsSpinBox  *pSpinBox;
	CMimicsTimeSpinBox  *pTimeSpinBox;

	if ((pSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CMimicsSpinBox))) ? (CMimicsSpinBox *)GetParent() : (CMimicsSpinBox *)NULL)) pSpinBox->UpdateUI();
	if ((pTimeSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CMimicsTimeSpinBox))) ? (CMimicsTimeSpinBox *)GetParent() : (CMimicsTimeSpinBox *)NULL)) pTimeSpinBox->UpdateUI();
	CEdit::OnMouseMove(nFlags, point);
}

void CMimicsNumberEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd  *pWnd[2];
	LONGLONG  nPos;

	switch (nChar)
	{
	case VK_PRIOR:
	{ nPos = GetPos() + m_nBase;
	break;
	}
	case VK_NEXT:
	{ nPos = GetPos() - m_nBase;
	break;
	}
	case VK_UP:
	{ nPos = GetPos() + 1;
	break;
	}
	case VK_DOWN:
	{ nPos = GetPos() - 1;
	break;
	}
	case VK_HOME:
	{ nPos = m_nMin;
	break;
	}
	case VK_END:
	{ nPos = m_nMax;
	break;
	}
	}
	if (nChar == VK_NEXT || nChar == VK_PRIOR || nChar == VK_UP || nChar == VK_DOWN || nChar == VK_HOME || nChar == VK_END)
	{
		SetPos(nPos, TRUE);
		SetFocus();
		return;
	}
	if (nChar == VK_LEFT || nChar == VK_RIGHT)
	{
		if ((GetParent()->GetStyle() & WS_TABSTOP) && LOWORD(GetSel()) == HIWORD(GetSel()) && ((nChar == VK_LEFT  &&  !LOWORD(GetSel())) || (nChar == VK_RIGHT  &&  LOWORD(GetSel()) == GetWindowTextLength())))
		{
			if ((pWnd[0] = GetParent()->GetDlgItem((nChar == VK_RIGHT) ? (GetDlgCtrlID() + 1) : (GetDlgCtrlID() - 1))) && pWnd[0]->IsKindOf(RUNTIME_CLASS(CEdit)))
			{
				pWnd[0]->SendMessage(EM_SETSEL, (nChar == VK_LEFT) ? pWnd[0]->GetWindowTextLength() : 0, (nChar == VK_LEFT) ? pWnd[0]->GetWindowTextLength() : 0);
				pWnd[0]->SetFocus();
				return;
			}
		}
	}
	if (nChar == VK_TAB)
	{
		if ((GetStyle() & (WS_CHILD | WS_TABSTOP)) == (WS_CHILD | WS_TABSTOP))
		{
			for (pWnd[0] = this; !pWnd[0]->IsKindOf(RUNTIME_CLASS(CDialogEx)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CMFCPropertySheet)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(COlePropertyPage)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CView)); )
			{
				if ((pWnd[0] = (pWnd[1] = pWnd[0])->GetParent())) continue;
				break;
			}
			if (IsWindow(pWnd[0]->GetSafeHwnd()))
			{
				if (pWnd[0]->IsKindOf(RUNTIME_CLASS(CView)))
				{
					pWnd[1]->SendMessage(WM_CHAR, GetCurrentMessage()->wParam, GetCurrentMessage()->lParam);
					return;
				}
				if ((pWnd[1] = pWnd[0]->GetNextDlgTabItem(pWnd[1], (HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE)))
				{
					pWnd[1]->SetFocus();
					return;
				}
			}
		}
	}
	if (nChar == VK_ESCAPE)
	{
		for (pWnd[0] = this; !pWnd[0]->IsKindOf(RUNTIME_CLASS(CDialogEx)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CMFCPropertySheet)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CView)); )
		{
			if ((pWnd[0] = pWnd[0]->GetParent())) continue;
			break;
		}
		if (IsWindow(pWnd[0]->GetSafeHwnd()))
		{
			if (pWnd[0]->IsKindOf(RUNTIME_CLASS(CMFCPropertySheet)))
			{
				pWnd[0]->PostMessage(WM_CLOSE);
				return;
			}
		}
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMimicsNumberEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString  szSign;
	CString  szDigit[3];
	CStringTools  cStringTools;

	for (szSign = cStringTools.ConvertIntToString(-1), szDigit[0] = cStringTools.ConvertIntToString(0), szDigit[1] = cStringTools.ConvertIntToString(1), szDigit[2] = cStringTools.ConvertIntToString(7); (nChar == (UINT)szSign[0] && (m_nBase == 2 || m_nMin >= 0 || (m_nMin < 0 && GetWindowTextLength() > 0 && (LOWORD(GetSel()) || HIWORD(GetSel()) < GetWindowTextLength())))) || (nChar != (UINT)szSign[0] && ((m_nBase == 2 && (nChar < (UINT)__toascii(szDigit[0].GetAt(0)) || nChar >(UINT) __toascii(szDigit[1].GetAt(0)))) || (m_nBase == 8 && (nChar < (UINT)__toascii(szDigit[0].GetAt(0)) || nChar >(UINT) __toascii(szDigit[2].GetAt(0)))) || (m_nBase == 10 && !_istdigit(nChar)) || (m_nBase == 16 && !_istxdigit(nChar))) && nChar >= VK_SPACE); )
	{
		PlaySound((LPCTSTR)SND_ALIAS_SYSTEMDEFAULT, (HMODULE)NULL, SND_ALIAS_ID);
		return;
	}
	for (; nChar != VK_TAB; )
	{
		CEdit::Default();
		break;
	}
	for (; CWnd::GetFocus() != this && !Check(); )
	{
		SetPos(GetPos(FALSE), TRUE);
		break;
	}
}

void CMimicsNumberEdit::OnKillFocus(CWnd *pNewWnd)
{
	if (IsAutoCompletionEnabled() && !Check()) SetPos(GetPos(FALSE), TRUE);
	CEdit::OnKillFocus(pNewWnd);
}

LRESULT CMimicsNumberEdit::OnFont(WPARAM wParam, LPARAM lParam)
{
	Default();
	Format();
	return 0;
}

LRESULT CMimicsNumberEdit::OnNumber(WPARAM wParam, LPARAM lParam)
{
	INT  nSel[2];
	CString  szNumber[2];
	LRESULT  lResult;

	for (szNumber[0] = (LPCTSTR)lParam; szNumber[0].Find(TAB) < szNumber[0].GetLength() - 1 && wParam != TRUE; )
	{
		for (GetSel(nSel[0], nSel[1]), GetWindowText(szNumber[1]); szNumber[0] != szNumber[1]; )
		{
			for (lResult = CEdit::Default(); !IsMinusZero(); )
			{
				SetPos(GetPos());
				break;
			}
			SetSel((szNumber[0].GetLength() != szNumber[1].GetLength()) ? ((szNumber[0].GetLength() >= szNumber[1].GetLength()) ? (nSel[0] + 1) : max(nSel[0] - 1, 0)) : nSel[0], (szNumber[0].GetLength() != szNumber[1].GetLength()) ? ((szNumber[0].GetLength() >= szNumber[1].GetLength()) ? (nSel[1] + 1) : max(nSel[1] - 1, 0)) : nSel[1]);
			return lResult;
		}
		return TRUE;
	}
	return CEdit::Default();
}

LRESULT CMimicsNumberEdit::OnSetBase(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 2 || wParam == 8 || wParam == 10 || wParam == 16)
	{
		if (m_nBase != (UINT)wParam || m_nDigits != (UINT)lParam)
		{
			m_nBase = (UINT)wParam;
			m_nDigits = (UINT)lParam;
			SetPos(GetPos());
		}
		return TRUE;
	}
	return FALSE;
}

LRESULT CMimicsNumberEdit::OnGetBase(WPARAM wParam, LPARAM lParam)
{
	*((UINT *)wParam) = m_nBase;
	*((UINT *)lParam) = m_nDigits;
	return((m_nBase == 2 || m_nBase == 8 || m_nBase == 10 || m_nBase == 16) ? TRUE : FALSE);
}

LRESULT CMimicsNumberEdit::OnSetRange(WPARAM wParam, LPARAM lParam)
{
	LONGLONG  nMin = (*(LONGLONG *)wParam);
	LONGLONG  nMax = (*(LONGLONG *)lParam);

	if ((m_nBase == 10 || nMin >= 0) && nMin <= nMax)
	{
		for (m_nMin = nMin, m_nMax = nMax; GetPos() < nMin; )
		{
			SetPos(nMin);
			break;
		}
		if (GetPos() > nMax) SetPos(nMax);
		return TRUE;
	}
	return FALSE;
}

LRESULT CMimicsNumberEdit::OnGetRange(WPARAM wParam, LPARAM lParam)
{
	*((LONGLONG *)wParam) = m_nMin;
	*((LONGLONG *)lParam) = m_nMax;
	return((m_nMin <= m_nMax) ? TRUE : FALSE);
}

LRESULT CMimicsNumberEdit::OnSetPos(WPARAM wParam, LPARAM lParam)
{
	CString  szPos;
	CString  szText;
	BOOL  bMinusZero;
	CStringTools  cStringTools;
	LONGLONG  nPos = (*(LONGLONG *)lParam);

	for (GetWindowText(szText), nPos = (!(bMinusZero = (((szText == cStringTools.ConvertLongIntToPaddedString(0, m_nDigits, m_nBase) && nPos == -1) || (szText == cStringTools.ConvertLongIntToPaddedString(-1, m_nDigits + 1, m_nBase) && nPos == 0)) && m_bMinusZero))) ? nPos : 0; m_nMin <= nPos && m_nMax >= nPos; )
	{
		if ((szPos = (!bMinusZero) ? ((!CheckMinusZero(szText) || nPos != 1) ? cStringTools.ConvertLongIntToPaddedString(nPos, (m_nDigits > 0 && nPos < 0) ? (m_nDigits + 1) : m_nDigits, m_nBase) : cStringTools.ConvertLongIntToPaddedString(0, m_nDigits, m_nBase)) : ConstructMinusZero(m_nDigits + 1)) != szText)
		{
			for (szPos.MakeUpper(), SetWindowText(szPos); wParam; )
			{
				SetSel(0, -1);
				break;
			}
			if (wParam) GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE), (LPARAM)GetSafeHwnd());
		}
		return TRUE;
	}
	if ((szPos = cStringTools.ConvertLongIntToPaddedString((m_nMin >= nPos) ? m_nMin : m_nMax, m_nDigits, m_nBase)) != szText)
	{
		for (szPos.MakeUpper(), SetWindowText(szPos); wParam; )
		{
			SetSel(0, -1);
			break;
		}
		if (wParam) GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE), (LPARAM)GetSafeHwnd());
	}
	return FALSE;
}

LRESULT CMimicsNumberEdit::OnGetPos(WPARAM wParam, LPARAM lParam)
{
	TCHAR  szChar;
	CString  szPos;
	CString  szDigit[2];
	LONGLONG  nPos;
	LONGLONG  nBase;
	CStringTools  cStringTools;

	for (nPos = 0, nBase = 1, GetWindowText(szPos), szPos.MakeUpper(), szDigit[0] = cStringTools.ConvertIntToString(0), szDigit[1] = cStringTools.ConvertIntToString(10, 16); !szPos.IsEmpty(); szPos = szPos.Left(szPos.GetLength() - 1))
	{
		if (_istdigit((szChar = szPos[szPos.GetLength() - 1])))
		{
			nPos += (__toascii(szChar) - __toascii(szDigit[0].GetAt(0)))*nBase;
			nBase *= m_nBase;
			continue;
		}
		if (_istxdigit(szChar))
		{
			nPos += (__toascii(szChar) - __toascii(szDigit[1].GetAt(0)) + 10)*nBase;
			nBase *= 16;
			continue;
		}
		nPos = -nPos;
		break;
	}
	*((LONGLONG *)lParam) = nPos = (wParam) ? min(max(nPos, m_nMin), m_nMax) : nPos;
	return 0;
}

LRESULT CMimicsNumberEdit::OnSetSel(WPARAM wParam, LPARAM lParam)
{
	SendMessage(EM_SETSEL, wParam, lParam);
	return TRUE;
}

LRESULT CMimicsNumberEdit::OnGetSel(WPARAM wParam, LPARAM lParam)
{
	DWORD  dwSel[2];

	SendMessage(EM_GETSEL, (WPARAM)&dwSel[0], (LPARAM)&dwSel[1]);
	*((INT *)wParam) = (INT)dwSel[0];
	*((INT *)lParam) = (INT)dwSel[1];
	return((dwSel[0] < dwSel[1]) ? TRUE : FALSE);
}

LRESULT CMimicsNumberEdit::OnCheck(WPARAM wParam, LPARAM lParam)
{
	LONGLONG  nPos;
	CString  szSign;
	CString  szNumber;
	CStringTools  cStringTools;

	nPos = GetPos(FALSE);
	GetWindowText(szNumber);
	szSign = cStringTools.ConvertIntToString(-1);
	return(!szNumber.IsEmpty() && szNumber != szSign.GetAt(0) && (!m_nDigits || ((szNumber.GetAt(0) == szSign.GetAt(0) && szNumber.GetLength() > (INT) m_nDigits) || (szNumber.GetAt(0) != szSign.GetAt(0) && szNumber.GetLength() == m_nDigits))) && nPos >= m_nMin  &&  nPos <= m_nMax);
}

// MimicsNumberedit helpers
BOOL MimicsNumberedit_SetBase(CWnd *pCtrl, UINT nBase, UINT nDigits)
{
	return((BOOL)pCtrl->SendMessage(NEM_SETBASE, (WPARAM)nBase, (LPARAM)nDigits));
}

BOOL MimicsNumberedit_GetBase(CWnd *pCtrl, UINT &nBase, UINT &nDigits)
{
	return((BOOL)pCtrl->SendMessage(NEM_GETBASE, (WPARAM)&nBase, (LPARAM)&nDigits));
}

BOOL MimicsNumberedit_SetRange(CWnd *pCtrl, LONGLONG nMin, LONGLONG nMax)
{
	return((BOOL)pCtrl->SendMessage(NEM_SETRANGE, (WPARAM)&nMin, (LPARAM)&nMax));
}

BOOL MimicsNumberedit_GetRange(CWnd *pCtrl, LONGLONG &nMin, LONGLONG &nMax)
{
	return((BOOL)pCtrl->SendMessage(NEM_GETRANGE, (WPARAM)&nMin, (LPARAM)&nMax));
}

BOOL MimicsNumberedit_SetPos(CWnd *pCtrl, LONGLONG nPos, BOOL bNotify)
{
	return((BOOL)pCtrl->SendMessage(NEM_SETPOS, bNotify, (LPARAM)&nPos));
}

LONGLONG MimicsNumberedit_GetPos(CWnd *pCtrl, BOOL bLimits)
{
	LONGLONG  nPos;

	pCtrl->SendMessage(NEM_GETPOS, bLimits, (LPARAM)&nPos);
	return nPos;
}

BOOL MimicsNumberedit_SetSel(CWnd *pCtrl, INT nStartPos, INT nStopPos)
{
	return((BOOL)pCtrl->SendMessage(NEM_SETSEL, nStartPos, nStopPos));
}

BOOL MimicsNumberedit_GetSel(CWnd *pCtrl, INT &nStartPos, INT &nStopPos)
{
	return((BOOL)pCtrl->SendMessage(NEM_GETSEL, (WPARAM)&nStartPos, (LPARAM)&nStopPos));
}
DWORD MimicsNumberedit_GetSel(CWnd *pCtrl)
{
	return((DWORD)pCtrl->SendMessage(EM_GETSEL));
}

BOOL MimicsNumberedit_Check(CWnd *pCtrl)
{
	return((BOOL)pCtrl->SendMessage(NEM_CHECK));
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsNumberEdit

IMPLEMENT_DYNCREATE(CResourceMimicsNumberEdit, CMimicsNumberEdit)

WNDPROC CResourceMimicsNumberEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMimicsNumberEdit::CResourceMimicsNumberEdit(HWND hWnd) : CMimicsNumberEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsNumberEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsNumberEdit  *pResourceNumberEdit;

	if ((pResourceNumberEdit = new CResourceMimicsNumberEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC *CResourceMimicsNumberEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMimicsNumberEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsNumberEdit, CMimicsNumberEdit)
	//{{AFX_MSG_MAP(CResourceMimicsNumberEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsNumberEdit message handlers

BOOL CResourceMimicsNumberEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LOWERCASE | ES_UPPERCASE | ES_NUMBER | ES_PASSWORD | ES_READONLY | ES_WANTRETURN)) | ES_MULTILINE), HIWORD(lpCreateStruct->style)) | WS_CHILD));
	return CMimicsNumberEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextEdit

IMPLEMENT_DYNCREATE(CMimicsTextEdit, CEdit)

CMimicsTextEdit::CMimicsTextEdit() : CEdit()
{
	m_bAutoCompletion = TRUE;
}

BOOL CMimicsTextEdit::Create(CWnd *pParentWnd, CONST RECT &rect, INT nID, DWORD dwStyle)
{
	if (CEdit::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NUMBER | ES_LOWERCASE | ES_UPPERCASE | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_PASSWORD | ES_READONLY | ES_WANTRETURN)) | ES_MULTILINE), HIWORD(dwStyle)) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CMimicsCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsTextEdit::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsTextEdit  cTextEdit;

	if ((pClass = cTextEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName  &&  GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceMimicsTextEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMimicsTextEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMimicsTextEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMimicsTextEdit::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsTextEdit  cTextEdit;

	if ((pClass = cTextEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

VOID CMimicsTextEdit::EnableAutoCompletion(BOOL bEnable)
{
	m_bAutoCompletion = bEnable;
}

BOOL CMimicsTextEdit::IsAutoCompletionEnabled() CONST
{
	return m_bAutoCompletion;
}

VOID CMimicsTextEdit::Format()
{
	CWnd  *pWnd;
	CRect  rTextEdit;
	CRect  rFormatArea;

	for (; (pWnd = GetParent()) && (pWnd->IsKindOf(RUNTIME_CLASS(CMimicsSpinBox)) || pWnd->IsKindOf(RUNTIME_CLASS(CMimicsTimeSpinBox))); )
	{
		SetMargins(0, 0);
		break;
	}
	GetRect(rFormatArea);
	GetClientRect(rTextEdit);
	rFormatArea.SetRect(rFormatArea.left, (rTextEdit.Height() - rFormatArea.Height()) / 2, rFormatArea.right, (rTextEdit.Height() - rFormatArea.Height()) / 2 + rFormatArea.Height());
	SetRect(rFormatArea);
}

BEGIN_MESSAGE_MAP(CMimicsTextEdit, CEdit)
	//{{AFX_MSG_MAP(CMimicsTextEdit)
	ON_WM_NCCREATE()
	ON_WM_SIZE()
	ON_WM_ENABLE()
	ON_WM_GETDLGCODE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_MESSAGE(WM_SETFONT, OnFont)
	ON_MESSAGE(WM_SETTEXT, OnText)
	ON_MESSAGE(TEM_ADDTEXT, OnAddText)
	ON_MESSAGE(TEM_INSERTTEXT, OnInsertText)
	ON_MESSAGE(TEM_FINDTEXT, OnFindText)
	ON_MESSAGE(TEM_SELECTTEXT, OnSelectText)
	ON_MESSAGE(TEM_DELETETEXT, OnDeleteText)
	ON_MESSAGE(TEM_RESETTEXT, OnResetText)
	ON_MESSAGE(TEM_SETPOS, OnSetPos)
	ON_MESSAGE(TEM_GETPOS, OnGetPos)
	ON_MESSAGE(TEM_SETSEL, OnSetSel)
	ON_MESSAGE(TEM_GETSEL, OnGetSel)
	ON_MESSAGE(TEM_CHECK, OnCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextEdit message handlers

BOOL CMimicsTextEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!IsThemeActive())
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | ((lpCreateStruct->style & WS_BORDER) ? WS_EX_CLIENTEDGE : 0));
		SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~(lpCreateStruct->style & WS_BORDER));
	}
	return CEdit::OnNcCreate(lpCreateStruct);
}

void CMimicsTextEdit::OnSize(UINT nType, int cx, int cy)
{
	Default();
	Format();
}

void CMimicsTextEdit::OnEnable(BOOL bEnable)
{
	for (; bEnable; )
	{
		SetPos(GetPos());
		break;
	}
	for (; !bEnable; )
	{
		SetWindowText(EMPTYSTRING);
		break;
	}
	CEdit::OnEnable(bEnable);
}

UINT CMimicsTextEdit::OnGetDlgCode()
{
	return CEdit::OnGetDlgCode() | DLGC_WANTARROWS | DLGC_WANTALLKEYS | DLGC_WANTCHARS;
}

void CMimicsTextEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	CMimicsSpinBox  *pSpinBox;
	CMimicsTimeSpinBox  *pTimeSpinBox;

	if ((pSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CMimicsSpinBox))) ? (CMimicsSpinBox *)GetParent() : (CMimicsSpinBox *)NULL)) pSpinBox->UpdateUI();
	if ((pTimeSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CMimicsTimeSpinBox))) ? (CMimicsTimeSpinBox *)GetParent() : (CMimicsTimeSpinBox *)NULL)) pTimeSpinBox->UpdateUI();
	CEdit::OnMouseMove(nFlags, point);
}

void CMimicsTextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nPos;
	CWnd  *pWnd[2];

	switch (nChar)
	{
	case VK_UP:
	case VK_PRIOR:
	{ nPos = min(GetPos() + 1, (INT)m_szNames.GetSize() - 1);
	break;
	}
	case VK_DOWN:
	case VK_NEXT:
	{ nPos = max(GetPos() - 1, 0);
	break;
	}
	case VK_HOME:
	{ nPos = 0;
	break;
	}
	case VK_END:
	{ nPos = (INT)m_szNames.GetSize() - 1;
	break;
	}
	}
	if (nChar == VK_NEXT || nChar == VK_PRIOR || nChar == VK_UP || nChar == VK_DOWN || nChar == VK_HOME || nChar == VK_END)
	{
		SetPos(nPos, TRUE);
		SetFocus();
		return;
	}
	if (nChar == VK_LEFT || nChar == VK_RIGHT)
	{
		if ((GetParent()->GetStyle() & WS_TABSTOP) && LOWORD(GetSel()) == HIWORD(GetSel()) && ((nChar == VK_LEFT  &&  !LOWORD(GetSel())) || (nChar == VK_RIGHT  &&  LOWORD(GetSel()) == GetWindowTextLength())))
		{
			if ((pWnd[0] = GetParent()->GetDlgItem((nChar == VK_RIGHT) ? (GetDlgCtrlID() + 1) : (GetDlgCtrlID() - 1))) && pWnd[0]->IsKindOf(RUNTIME_CLASS(CEdit)))
			{
				pWnd[0]->SendMessage(EM_SETSEL, (nChar == VK_LEFT) ? pWnd[0]->GetWindowTextLength() : 0, (nChar == VK_LEFT) ? pWnd[0]->GetWindowTextLength() : 0);
				pWnd[0]->SetFocus();
				return;
			}
		}
	}
	if (nChar == VK_TAB)
	{
		if ((GetStyle() & (WS_CHILD | WS_TABSTOP)) == (WS_CHILD | WS_TABSTOP))
		{
			for (pWnd[0] = this; !pWnd[0]->IsKindOf(RUNTIME_CLASS(CDialogEx)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CMFCPropertySheet)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(COlePropertyPage)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CView)); )
			{
				if ((pWnd[0] = (pWnd[1] = pWnd[0])->GetParent())) continue;
				break;
			}
			if (IsWindow(pWnd[0]->GetSafeHwnd()))
			{
				if (pWnd[0]->IsKindOf(RUNTIME_CLASS(CView)))
				{
					pWnd[1]->SendMessage(WM_CHAR, GetCurrentMessage()->wParam, GetCurrentMessage()->lParam);
					return;
				}
				if ((pWnd[1] = pWnd[0]->GetNextDlgTabItem(pWnd[1], (HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE)))
				{
					pWnd[1]->SetFocus();
					return;
				}
			}
		}
	}
	if (nChar == VK_ESCAPE)
	{
		for (pWnd[0] = this; !pWnd[0]->IsKindOf(RUNTIME_CLASS(CDialogEx)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CMFCPropertySheet)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CView)); )
		{
			if ((pWnd[0] = pWnd[0]->GetParent())) continue;
			break;
		}
		if (IsWindow(pWnd[0]->GetSafeHwnd()))
		{
			if (pWnd[0]->IsKindOf(RUNTIME_CLASS(CMFCPropertySheet)))
			{
				pWnd[0]->PostMessage(WM_CLOSE);
				return;
			}
		}
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMimicsTextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nName;
	INT  nNames;
	CString  szText;

	for (; nChar != VK_TAB; )
	{
		CEdit::Default();
		break;
	}
	for (nName = 0, nNames = (INT)m_szNames.GetSize(), GetWindowText(szText); nName < nNames; nName++)
	{
		if (!m_szNames.GetAt(nName).Find(szText)) break;
		continue;
	}
	if (nName == nNames)
	{
		SetPos(0, TRUE);
		SetFocus();
	}
}

void CMimicsTextEdit::OnKillFocus(CWnd *pNewWnd)
{
	if (IsAutoCompletionEnabled() && !Check()) SetPos(GetPos(), TRUE);
	CEdit::OnKillFocus(pNewWnd);
}

LRESULT CMimicsTextEdit::OnFont(WPARAM wParam, LPARAM lParam)
{
	Default();
	Format();
	return 0;
}

LRESULT CMimicsTextEdit::OnText(WPARAM wParam, LPARAM lParam)
{
	CString  szText;
	LRESULT  lResult;

	for (GetWindowText(szText); szText != (LPCTSTR)lParam; )
	{
		for (lResult = CWnd::Default(); wParam != TRUE; )
		{
			SetPos(GetPos());
			break;
		}
		return lResult;
	}
	return TRUE;
}

LRESULT CMimicsTextEdit::OnAddText(WPARAM wParam, LPARAM lParam)
{
	return m_szNames.Add((LPCTSTR)lParam);
}

LRESULT CMimicsTextEdit::OnInsertText(WPARAM wParam, LPARAM lParam)
{
	m_szNames.InsertAt(wParam, (LPCTSTR)lParam, 1);
	return 0;
}

LRESULT CMimicsTextEdit::OnFindText(WPARAM wParam, LPARAM lParam)
{
	INT  nName;
	INT  nNames;

	for (nName = max((INT)wParam, 0), nNames = (INT)m_szNames.GetSize(); nName < nNames; nName++)
	{
		if (m_szNames.GetAt(nName) == (LPCTSTR)lParam) break;
		continue;
	}
	return((nName < nNames) ? nName : -1);
}

LRESULT CMimicsTextEdit::OnSelectText(WPARAM wParam, LPARAM lParam)
{
	INT  nPos;

	if ((nPos = FindText((INT)wParam, (LPCTSTR)lParam)) >= 0)
	{
		SetPos(nPos, TRUE);
		return TRUE;
	}
	return FALSE;
}

LRESULT CMimicsTextEdit::OnDeleteText(WPARAM wParam, LPARAM lParam)
{
	INT  nPos[2];

	for (nPos[0] = GetPos(); (nPos[1] = FindText(0, (LPCTSTR)lParam)) >= 0; )
	{
		for (m_szNames.RemoveAt(nPos[1]); nPos[0] == nPos[1]; )
		{
			SetPos(0, TRUE);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

LRESULT CMimicsTextEdit::OnResetText(WPARAM wParam, LPARAM lParam)
{
	m_szNames.RemoveAll();
	SetWindowText(EMPTYSTRING);
	return 0;
}

LRESULT CMimicsTextEdit::OnSetPos(WPARAM wParam, LPARAM lParam)
{
	CString  szPos;
	CString  szText;

	for (GetWindowText(szText); (INT)wParam >= 0 && m_szNames.GetSize() > (INT)wParam; )
	{
		if ((szPos = m_szNames.GetAt(wParam)) != szText)
		{
			for (SetWindowText(szPos); lParam; )
			{
				SetSel(0, -1);
				break;
			}
			if (lParam) GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE), (LPARAM)GetSafeHwnd());
		}
		return TRUE;
	}
	if ((szPos = (m_szNames.GetSize() > 0 && wParam != (WPARAM)-1) ? (LPCTSTR)m_szNames.GetAt(max(min(m_szNames.GetSize() - 1, (INT)wParam), 0)) : szText) != szText)
	{
		for (SetWindowText(szPos); lParam; )
		{
			SetSel(0, -1);
			break;
		}
		if (lParam) GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), EN_CHANGE), (LPARAM)GetSafeHwnd());
	}
	return FALSE;
}

LRESULT CMimicsTextEdit::OnGetPos(WPARAM wParam, LPARAM lParam)
{
	INT  nName;
	INT  nNames;
	INT  nIndex;
	CString  szText;

	for (GetWindowText(szText); szText.GetLength() > 0; )
	{
		for (nName = 0, nNames = ((nIndex = FindText(0, szText)) < 0) ? (INT)m_szNames.GetSize() : -1; nName < nNames; nName++)
		{
			if (!m_szNames.GetAt(nName).Find(szText)) break;
			continue;
		}
		return((nName != nNames) ? max(nIndex, nName) : -1);
	}
	return -1;
}

LRESULT CMimicsTextEdit::OnSetSel(WPARAM wParam, LPARAM lParam)
{
	SendMessage(EM_SETSEL, wParam, lParam);
	return TRUE;
}

LRESULT CMimicsTextEdit::OnGetSel(WPARAM wParam, LPARAM lParam)
{
	INT  *nSel[2];
	DWORD  dwSel[2];

	SendMessage(EM_GETSEL, (WPARAM)&dwSel[0], (LPARAM)&dwSel[1]);
	*(nSel[0] = (LPINT)wParam) = (INT)dwSel[0];
	*(nSel[1] = (LPINT)lParam) = (INT)dwSel[1];
	return 0;
}

LRESULT CMimicsTextEdit::OnCheck(WPARAM wParam, LPARAM lParam)
{
	CString  szText;

	GetWindowText(szText);
	return((FindText(0, szText) >= 0) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsTextEdit

IMPLEMENT_DYNCREATE(CResourceMimicsTextEdit, CMimicsTextEdit)

WNDPROC CResourceMimicsTextEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMimicsTextEdit::CResourceMimicsTextEdit(HWND hWnd) : CMimicsTextEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsTextEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsTextEdit  *pResourceTextEdit;

	if ((pResourceTextEdit = new CResourceMimicsTextEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC *CResourceMimicsTextEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMimicsTextEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsTextEdit, CMimicsTextEdit)
	//{{AFX_MSG_MAP(CResourceMimicsTextEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsTextEdit message handlers

BOOL CResourceMimicsTextEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NUMBER | ES_LOWERCASE | ES_UPPERCASE | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_PASSWORD | ES_READONLY | ES_WANTRETURN)) | ES_MULTILINE), HIWORD(lpCreateStruct->style)) | WS_CHILD));
	return CMimicsTextEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsSimpleListBox

IMPLEMENT_DYNCREATE(CMimicsSimpleListBox, CListBox)

BOOL CMimicsSimpleListBox::Create(CWnd *pParentWnd, CONST RECT &rect, INT nID, DWORD dwStyle)
{
	if (CListBox::Create((MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_MULTICOLUMN | LBS_NOINTEGRALHEIGHT | LBS_NOREDRAW | LBS_NOTIFY | LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE | LBS_SORT | LBS_USETABSTOPS)) & ~(LBS_EXTENDEDSEL | LBS_MULTIPLESEL | LBS_WANTKEYBOARDINPUT)) | LBS_NOSEL), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL) & ~WS_TABSTOP, rect, pParentWnd, nID))
	{
		SetFont(CMimicsCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsSimpleListBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsSimpleListBox  CMimicsSimpleListBox;

	if ((pClass = CMimicsSimpleListBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName  &&  GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceMimicsSimpleListBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMimicsSimpleListBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMimicsSimpleListBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMimicsSimpleListBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsSimpleListBox  CMimicsSimpleListBox;

	if ((pClass = CMimicsSimpleListBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

BEGIN_MESSAGE_MAP(CMimicsSimpleListBox, CListBox)
	//{{AFX_MSG_MAP(CMimicsSimpleListBox)
	ON_WM_NCCREATE()
	ON_WM_SETFOCUS()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsSimpleListBox message handlers

BOOL CMimicsSimpleListBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!IsThemeActive())
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | ((lpCreateStruct->style & WS_BORDER) ? WS_EX_CLIENTEDGE : 0));
		SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~(lpCreateStruct->style & WS_BORDER));
	}
	return CListBox::OnNcCreate(lpCreateStruct);
}

void CMimicsSimpleListBox::OnSetFocus(CWnd *pOldWnd)
{
	return;
}

void CMimicsSimpleListBox::OnEnable(BOOL bEnable)
{
	INT  nItem;
	INT  nItems;
	CString  szItem;

	if (bEnable)
	{
		for (nItem = 0, nItems = (INT)m_szItems.GetSize(); nItem < nItems; nItem++) AddString(m_szItems.GetAt(nItem));
		CListBox::OnEnable(bEnable);
		return;
	}
	for (nItem = 0, nItems = GetCount(), m_szItems.RemoveAll(); nItem < nItems; nItem++)
	{
		GetText(nItem, szItem);
		m_szItems.Add(szItem);
	}
	ResetContent();
	CListBox::OnEnable(bEnable);
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsSimpleListBox

IMPLEMENT_DYNCREATE(CResourceMimicsSimpleListBox, CMimicsSimpleListBox)

WNDPROC CResourceMimicsSimpleListBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMimicsSimpleListBox::CResourceMimicsSimpleListBox(HWND hWnd) : CMimicsSimpleListBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsSimpleListBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsSimpleListBox  *pResourceSimpleListBox;

	if ((pResourceSimpleListBox = new CResourceMimicsSimpleListBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC *CResourceMimicsSimpleListBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMimicsSimpleListBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsSimpleListBox, CMimicsSimpleListBox)
	//{{AFX_MSG_MAP(CResourceMimicsSimpleListBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsSimpleListBox message handlers

BOOL CResourceMimicsSimpleListBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_MULTICOLUMN | LBS_NOINTEGRALHEIGHT | LBS_NOREDRAW | LBS_NOTIFY | LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE | LBS_SORT | LBS_USETABSTOPS)) & ~(LBS_EXTENDEDSEL | LBS_MULTIPLESEL | LBS_WANTKEYBOARDINPUT)) | LBS_NOSEL), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL) & ~WS_TABSTOP));
	return CMimicsSimpleListBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsColorsComboBox

IMPLEMENT_DYNCREATE(CMimicsColorsComboBox, CComboBox)

BOOL CMimicsColorsComboBox::Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle)
{
	return CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (CCBS_STANDARD | CCBS_CUSTOM | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID);
}

BOOL CMimicsColorsComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsColorsComboBox  CMimicsColorsComboBox;

	if ((pClass = CMimicsColorsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName  &&  GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceMimicsColorsComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMimicsColorsComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMimicsColorsComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMimicsColorsComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsColorsComboBox  CMimicsColorsComboBox;

	if ((pClass = CMimicsColorsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

void CMimicsColorsComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC  *pDC;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CMimicsCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CMimicsColorsComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  cDC;
	INT  nBkMode;
	CFont  *pOldFont;
	CRect  rItemArea;
	CBrush  cBkBrush;
	CBrush  cItemBrush;
	COLORREF  nOldColor;
	TEXTMETRIC  tmFont;

	if (cDC.Attach(lpDrawItemStruct->hDC))
	{
		if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) || (lpDrawItemStruct->itemAction & ODA_SELECT))
		{
			if (cBkBrush.CreateSolidBrush((lpDrawItemStruct->itemState & ODS_SELECTED) ? (COLORREF)GetSysColor(COLOR_HIGHLIGHT) : (COLORREF)cDC.GetBkColor()))
			{
				cDC.FillRect(&lpDrawItemStruct->rcItem, &cBkBrush);
				if ((lpDrawItemStruct->itemState & ODS_SELECTED) && lpDrawItemStruct->rcItem.left > 0) cDC.DrawFocusRect(&lpDrawItemStruct->rcItem);
			}
			if (!(lpDrawItemStruct->itemState & ODS_DISABLED))
			{
				if (lpDrawItemStruct->itemID != (UINT)-1)
				{
					rItemArea = lpDrawItemStruct->rcItem;
					rItemArea.DeflateRect(2 * GetSystemMetrics(SM_CXBORDER), 2 * GetSystemMetrics(SM_CYBORDER));
					if ((GetStyle() & CCBS_CUSTOM) && lpDrawItemStruct->itemID == (UINT)GetCount() - 1)
					{
						if ((pOldFont = (CFont *)cDC.SelectObject(CMimicsCustomControls::GetCustomControlFont(this))))
						{
							if (cDC.GetTextMetrics(&tmFont))
							{
								nBkMode = cDC.SetBkMode(TRANSPARENT);
								nOldColor = cDC.SetTextColor((lpDrawItemStruct->itemState & ODS_SELECTED) ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_WINDOWTEXT));
								cDC.TextOut(rItemArea.left, rItemArea.top + (rItemArea.Height() - tmFont.tmHeight) / 2, STRING(IDS_MIMICSCONTROLS_COLORSCOMBOBOX_CUSTOM));
								cDC.SetTextColor(nOldColor);
								cDC.SelectObject(pOldFont);
								cDC.SetBkMode(nBkMode);
							}
						}
					}
					else
					{
						if (cItemBrush.CreateSolidBrush((COLORREF)lpDrawItemStruct->itemData))
						{
							cDC.FillRect(rItemArea, &cItemBrush);
							cItemBrush.DeleteObject();
						}
					}
				}
			}
		}
		cDC.Detach();
	}
}

int CMimicsColorsComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return((lpCompareItemStruct->itemData1 != lpCompareItemStruct->itemData2) ? ((lpCompareItemStruct->itemData1 < lpCompareItemStruct->itemData2) ? -1 : 1) : 0);
}

BEGIN_MESSAGE_MAP(CMimicsColorsComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMimicsColorsComboBox)
	ON_WM_CREATE()
	ON_CONTROL_REFLECT_EX(CBN_SELCHANGE, OnColor)
	ON_MESSAGE(CCB_ADDCOLOR, OnAddColor)
	ON_MESSAGE(CCB_INSERTCOLOR, OnInsertColor)
	ON_MESSAGE(CCB_GETCOLOR, OnGetColor)
	ON_MESSAGE(CCB_FINDCOLOR, OnFindColor)
	ON_MESSAGE(CCB_SELECTCOLOR, OnSelectColor)
	ON_MESSAGE(CCB_DELETECOLOR, OnDeleteColor)
	ON_MESSAGE(CCB_RESETCOLORS, OnResetColors)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsColorsComboBox message handlers

int CMimicsColorsComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	COLORREF  nColor;
	MEASUREITEMSTRUCT  sItem;

	if (CComboBox::OnCreate(lpCreateStruct) != -1)
	{
		InsertColor(GetCount(), VGA_COLOR_BLACK);
		InsertColor(GetCount(), VGA_COLOR_GRAY);
		InsertColor(GetCount(), VGA_COLOR_LTGRAY);
		InsertColor(GetCount(), VGA_COLOR_YELLOW);
		InsertColor(GetCount(), VGA_COLOR_LTYELLOW);
		InsertColor(GetCount(), VGA_COLOR_RED);
		InsertColor(GetCount(), VGA_COLOR_LTRED);
		InsertColor(GetCount(), VGA_COLOR_MAGENTA);
		InsertColor(GetCount(), VGA_COLOR_LTMAGENTA);
		InsertColor(GetCount(), VGA_COLOR_BLUE);
		InsertColor(GetCount(), VGA_COLOR_LTBLUE);
		InsertColor(GetCount(), VGA_COLOR_CYAN);
		InsertColor(GetCount(), VGA_COLOR_LTCYAN);
		InsertColor(GetCount(), VGA_COLOR_GREEN);
		InsertColor(GetCount(), VGA_COLOR_LTGREEN);
		for (MeasureItem(&sItem), SetItemHeight(-1, sItem.itemHeight); GetStyle() & CCBS_CUSTOM; )
		{
			nColor = GetSysColor(COLOR_WINDOW);
			AddColor(nColor);
			break;
		}
		return 0;
	}
	return -1;
}

BOOL CMimicsColorsComboBox::OnColor()
{
	INT  nIndex;
	COLORREF  nColor;
	CColorDialog  cColorDialog(VGA_COLOR_LTGRAY, 0, this);

	if ((GetStyle() & CCBS_CUSTOM) && GetCurSel() == GetCount() - 1)
	{
		if (cColorDialog.DoModal() == IDOK)
		{
			nColor = cColorDialog.GetColor();
			if ((nIndex = FindColor(-1, nColor)) >= 0)
			{
				SetCurSel(nIndex);
				return FALSE;
			}
			InsertColor((nIndex = GetCount() - 1), nColor);
			SetCurSel(nIndex);
		}
	}
	return FALSE;
}

LRESULT CMimicsColorsComboBox::OnAddColor(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_ADDSTRING, wParam, lParam);
}

LRESULT CMimicsColorsComboBox::OnInsertColor(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_INSERTSTRING, wParam, lParam);
}

LRESULT CMimicsColorsComboBox::OnGetColor(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_GETITEMDATA, wParam);
}

LRESULT CMimicsColorsComboBox::OnFindColor(WPARAM wParam, LPARAM lParam)
{
	INT  nIndex;
	INT  nCount;
	COLORREF  nColor;
	CClientDC  cDC(this);

	for (nIndex = (wParam != (WPARAM)-1) ? (INT)wParam : 0, nCount = (GetStyle() & CCBS_CUSTOM) ? (GetCount() - 1) : GetCount(), nColor = cDC.GetNearestColor((COLORREF)lParam); nIndex < nCount; nIndex++)
	{
		if (cDC.GetNearestColor((COLORREF)SendMessage(CB_GETITEMDATA, nIndex)) == nColor) break;
		continue;
	}
	return((nIndex < nCount) ? nIndex : -1);
}

LRESULT CMimicsColorsComboBox::OnSelectColor(WPARAM wParam, LPARAM lParam)
{
	INT  nIndex;

	if (GetStyle() & CCBS_CUSTOM)
	{
		if (((nIndex = (INT)SendMessage(CCB_FINDCOLOR, (WPARAM)-1, lParam)) < 0 || nIndex == GetCount() - 1) && lParam != (UINT)-1)
		{
			SendMessage(CB_INSERTSTRING, (nIndex = GetCount() - 1), lParam);
			SendMessage(CB_SETCURSEL, nIndex);
			return nIndex;
		}
		if (nIndex < 0)
		{
			SendMessage(CB_SETCURSEL, (WPARAM)-1);
			return nIndex;
		}
		return SendMessage(CB_SETCURSEL, nIndex);
	}
	if ((nIndex = (INT)SendMessage(CB_SELECTSTRING, wParam, lParam)) == CB_ERR) SendMessage(CB_SETCURSEL, (WPARAM)-1);
	return nIndex;
}

LRESULT CMimicsColorsComboBox::OnDeleteColor(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)SendMessage(CCB_FINDCOLOR, wParam, lParam));
}

LRESULT CMimicsColorsComboBox::OnResetColors(WPARAM wParam, LPARAM lParam)
{
	SendMessage(CB_RESETCONTENT);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsColorsComboBox

IMPLEMENT_DYNCREATE(CResourceMimicsColorsComboBox, CMimicsColorsComboBox)

WNDPROC CResourceMimicsColorsComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMimicsColorsComboBox::CResourceMimicsColorsComboBox(HWND hWnd) : CMimicsColorsComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsColorsComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsColorsComboBox  *pResourceColorsComboBox;

	if ((pResourceColorsComboBox = new CResourceMimicsColorsComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC *CResourceMimicsColorsComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMimicsColorsComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsColorsComboBox, CMimicsColorsComboBox)
	//{{AFX_MSG_MAP(CResourceMimicsColorsComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsColorsComboBox message handlers

BOOL CResourceMimicsColorsComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (CCBS_STANDARD | CCBS_CUSTOM | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CMimicsColorsComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineStylesComboBox

IMPLEMENT_DYNCREATE(CMimicsLineStylesComboBox, CComboBox)

BOOL CMimicsLineStylesComboBox::Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle)
{
	return CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID);
}

BOOL CMimicsLineStylesComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsLineStylesComboBox  CMimicsLineStylesComboBox;

	if ((pClass = CMimicsLineStylesComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName  &&  GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceMimicsLineStylesComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMimicsLineStylesComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMimicsLineStylesComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMimicsLineStylesComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsLineStylesComboBox  CMimicsLineStylesComboBox;

	if ((pClass = CMimicsLineStylesComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

void CMimicsLineStylesComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC  *pDC;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CMimicsCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CMimicsLineStylesComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  cDC;
	HPEN  hPen;
	HPEN  hOldPen;
	CRect  rItemArea;
	CBrush  cBkBrush;
	LOGBRUSH  sPenBrush;

	if (cDC.Attach(lpDrawItemStruct->hDC))
	{
		if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) || (lpDrawItemStruct->itemAction & ODA_SELECT))
		{
			if (cBkBrush.CreateSolidBrush((lpDrawItemStruct->itemState & ODS_SELECTED) ? (COLORREF)GetSysColor(COLOR_HIGHLIGHT) : (COLORREF)cDC.GetBkColor()))
			{
				cDC.FillRect(&lpDrawItemStruct->rcItem, &cBkBrush);
				if ((lpDrawItemStruct->itemState & ODS_SELECTED) && lpDrawItemStruct->rcItem.left > 0) cDC.DrawFocusRect(&lpDrawItemStruct->rcItem);
			}
			if (!(lpDrawItemStruct->itemState & ODS_DISABLED))
			{
				if (lpDrawItemStruct->itemID != (UINT)-1)
				{
					rItemArea = lpDrawItemStruct->rcItem;
					rItemArea.DeflateRect(2 * GetSystemMetrics(SM_CXBORDER), 0);
					rItemArea.DeflateRect(0, 2 * GetSystemMetrics(SM_CYBORDER));
					sPenBrush.lbStyle = BS_SOLID;
					sPenBrush.lbHatch = (ULONG_PTR)NULL;
					sPenBrush.lbColor = (lpDrawItemStruct->itemState & ODS_SELECTED) ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_WINDOWTEXT);
					if ((hPen = ExtCreatePen((DWORD)(PS_GEOMETRIC | PS_ENDCAP_FLAT | lpDrawItemStruct->itemData), 2, &sPenBrush, 0, (CONST DWORD *) NULL)))
					{
						if ((hOldPen = (HPEN)SelectObject(lpDrawItemStruct->hDC, hPen)) != (HPEN)NULL)
						{
							MoveToEx(lpDrawItemStruct->hDC, rItemArea.left, rItemArea.CenterPoint().y, (LPPOINT)NULL);
							LineTo(lpDrawItemStruct->hDC, rItemArea.right, rItemArea.CenterPoint().y);
							SelectObject(lpDrawItemStruct->hDC, hOldPen);
						}
						DeleteObject(hPen);
					}
				}
			}
		}
		cDC.Detach();
	}
}

int CMimicsLineStylesComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return((lpCompareItemStruct->itemData1 != lpCompareItemStruct->itemData2) ? ((lpCompareItemStruct->itemData1 < lpCompareItemStruct->itemData2) ? -1 : 1) : 0);
}

BEGIN_MESSAGE_MAP(CMimicsLineStylesComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMimicsLineStylesComboBox)
	ON_WM_CREATE()
	ON_MESSAGE(LSCB_ADDLINESTYLE, OnAddLineStyle)
	ON_MESSAGE(LSCB_INSERTLINESTYLE, OnInsertLineStyle)
	ON_MESSAGE(LSCB_GETLINESTYLE, OnGetLineStyle)
	ON_MESSAGE(LSCB_FINDLINESTYLE, OnFindLineStyle)
	ON_MESSAGE(LSCB_SELECTLINESTYLE, OnSelectLineStyle)
	ON_MESSAGE(LSCB_DELETELINESTYLE, OnDeleteLineStyle)
	ON_MESSAGE(LSCB_RESETLINESTYLES, OnResetLineStyles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineStylesComboBox message handlers

int CMimicsLineStylesComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	MEASUREITEMSTRUCT  sItem;

	if (CComboBox::OnCreate(lpCreateStruct) != -1)
	{
		InsertLineStyle(GetCount(), LS_SOLID);
		InsertLineStyle(GetCount(), LS_DASH);
		InsertLineStyle(GetCount(), LS_DOT);
		InsertLineStyle(GetCount(), LS_DASHDOT);
		InsertLineStyle(GetCount(), LS_DASHDOTDOT);
		MeasureItem(&sItem);
		SetItemHeight(-1, sItem.itemHeight);
		return 0;
	}
	return -1;
}

LRESULT CMimicsLineStylesComboBox::OnAddLineStyle(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_ADDSTRING, wParam, lParam);
}

LRESULT CMimicsLineStylesComboBox::OnInsertLineStyle(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_INSERTSTRING, wParam, lParam);
}

LRESULT CMimicsLineStylesComboBox::OnGetLineStyle(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_GETITEMDATA, wParam);
}

LRESULT CMimicsLineStylesComboBox::OnFindLineStyle(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_FINDSTRINGEXACT, wParam, lParam);
}

LRESULT CMimicsLineStylesComboBox::OnSelectLineStyle(WPARAM wParam, LPARAM lParam)
{
	INT  nIndex;

	return(((nIndex = (INT)SendMessage(CB_SELECTSTRING, wParam, lParam)) == CB_ERR) ? SendMessage(CB_SETCURSEL, (WPARAM)-1) : nIndex);
}

LRESULT CMimicsLineStylesComboBox::OnDeleteLineStyle(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)SendMessage(CB_FINDSTRINGEXACT, wParam, lParam));
}

LRESULT CMimicsLineStylesComboBox::OnResetLineStyles(WPARAM wParam, LPARAM lParam)
{
	SendMessage(CB_RESETCONTENT);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsLineStylesComboBox

IMPLEMENT_DYNCREATE(CResourceMimicsLineStylesComboBox, CMimicsLineStylesComboBox)

WNDPROC CResourceMimicsLineStylesComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMimicsLineStylesComboBox::CResourceMimicsLineStylesComboBox(HWND hWnd) : CMimicsLineStylesComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsLineStylesComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsLineStylesComboBox  *pResourceLineStylesComboBox;

	if ((pResourceLineStylesComboBox = new CResourceMimicsLineStylesComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC *CResourceMimicsLineStylesComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMimicsLineStylesComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsLineStylesComboBox, CMimicsLineStylesComboBox)
	//{{AFX_MSG_MAP(CResourceMimicsLineStylesComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsLineStylesComboBox message handlers

BOOL CResourceMimicsLineStylesComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CMimicsLineStylesComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineSymbolsComboBox

IMPLEMENT_DYNCREATE(CMimicsLineSymbolsComboBox, CComboBox)

BOOL CMimicsLineSymbolsComboBox::Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle)
{
	return CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID);
}

BOOL CMimicsLineSymbolsComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsLineSymbolsComboBox  CMimicsLineSymbolsComboBox;

	if ((pClass = CMimicsLineSymbolsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName  &&  GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceMimicsLineSymbolsComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMimicsLineSymbolsComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMimicsLineSymbolsComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMimicsLineSymbolsComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsLineSymbolsComboBox  CMimicsLineSymbolsComboBox;

	if ((pClass = CMimicsLineSymbolsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

void CMimicsLineSymbolsComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC  *pDC;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CMimicsCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CMimicsLineSymbolsComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  cDC;
	INT  nWidth;
	HPEN  hPen;
	HPEN  hSymPen;
	HPEN  hOldPen;
	CRect  rItemArea;
	CBrush  cBkBrush;
	HBRUSH  hSymBrush;
	HBRUSH  hOldBrush;
	LOGBRUSH  sPenBrush;

	if (cDC.Attach(lpDrawItemStruct->hDC))
	{
		if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) || (lpDrawItemStruct->itemAction & ODA_SELECT))
		{
			if (cBkBrush.CreateSolidBrush((lpDrawItemStruct->itemState & ODS_SELECTED) ? (COLORREF)GetSysColor(COLOR_HIGHLIGHT) : (COLORREF)cDC.GetBkColor()))
			{
				cDC.FillRect(&lpDrawItemStruct->rcItem, &cBkBrush);
				if ((lpDrawItemStruct->itemState & ODS_SELECTED) && lpDrawItemStruct->rcItem.left > 0) cDC.DrawFocusRect(&lpDrawItemStruct->rcItem);
			}
			if (!(lpDrawItemStruct->itemState & ODS_DISABLED))
			{
				if (lpDrawItemStruct->itemID != (UINT)-1)
				{
					rItemArea = lpDrawItemStruct->rcItem;
					rItemArea.DeflateRect(2 * GetSystemMetrics(SM_CXBORDER), 0);
					rItemArea.DeflateRect(0, 2 * GetSystemMetrics(SM_CYBORDER));
					sPenBrush.lbStyle = BS_SOLID;
					sPenBrush.lbHatch = (ULONG_PTR)NULL;
					sPenBrush.lbColor = (lpDrawItemStruct->itemState & ODS_SELECTED) ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_WINDOWTEXT);
					if ((hPen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, (nWidth = 2), &sPenBrush, 0, (CONST DWORD *) NULL)))
					{
						if ((hOldPen = (HPEN)SelectObject(lpDrawItemStruct->hDC, hPen)) != (HPEN)NULL)
						{
							MoveToEx(lpDrawItemStruct->hDC, rItemArea.left, rItemArea.CenterPoint().y, (LPPOINT)NULL);
							LineTo(lpDrawItemStruct->hDC, rItemArea.right, rItemArea.CenterPoint().y);
							if ((hSymPen = CreatePen(PS_SOLID, 1, sPenBrush.lbColor)) != (HPEN)NULL)
							{
								if ((hOldPen = (HPEN)SelectObject(lpDrawItemStruct->hDC, hSymPen)))
								{
									if (lpDrawItemStruct->itemData == LS_STROKE)
									{
										MoveToEx(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x, rItemArea.CenterPoint().y - 2 * nWidth, (LPPOINT)NULL);
										LineTo(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x, rItemArea.CenterPoint().y + 2 * nWidth + nWidth % 2);
									}
									if (lpDrawItemStruct->itemData == LS_CROSS)
									{
										MoveToEx(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x - 2 * nWidth, rItemArea.CenterPoint().y - 2 * nWidth - (nWidth + 1) % 2, (LPPOINT)NULL);
										LineTo(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x, rItemArea.CenterPoint().y - (nWidth + 1) % 2);
										MoveToEx(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x + 2 * nWidth, rItemArea.CenterPoint().y - 2 * nWidth - (nWidth + 1) % 2, (LPPOINT)NULL);
										LineTo(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x, rItemArea.CenterPoint().y - (nWidth + 1) % 2);
										MoveToEx(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x - 2 * nWidth, rItemArea.CenterPoint().y + 2 * nWidth, (LPPOINT)NULL);
										LineTo(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x, rItemArea.CenterPoint().y);
										MoveToEx(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x + 2 * nWidth, rItemArea.CenterPoint().y + 2 * nWidth, (LPPOINT)NULL);
										LineTo(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x, rItemArea.CenterPoint().y);
									}
									if (lpDrawItemStruct->itemData == LS_POINT || lpDrawItemStruct->itemData == LS_SQUARE)
									{
										if ((hSymBrush = CreateSolidBrush(sPenBrush.lbColor)) != (HBRUSH)NULL)
										{
											if ((hOldBrush = (HBRUSH)SelectObject(lpDrawItemStruct->hDC, hSymBrush)))
											{
												if (lpDrawItemStruct->itemData == LS_POINT) Ellipse(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x - 2 * nWidth, rItemArea.CenterPoint().y - 2 * nWidth, rItemArea.CenterPoint().x + 2 * nWidth + 1, rItemArea.CenterPoint().y + 2 * nWidth + nWidth % 2);
												if (lpDrawItemStruct->itemData == LS_SQUARE) Rectangle(lpDrawItemStruct->hDC, rItemArea.CenterPoint().x - 2 * nWidth, rItemArea.CenterPoint().y - 2 * nWidth, rItemArea.CenterPoint().x + 2 * nWidth + 1, rItemArea.CenterPoint().y + 2 * nWidth + nWidth % 2);
												SelectObject(lpDrawItemStruct->hDC, hOldBrush);
											}
											DeleteObject(hSymBrush);
										}
									}
									SelectObject(lpDrawItemStruct->hDC, hOldPen);
								}
								DeleteObject(hSymPen);
							}
							SelectObject(lpDrawItemStruct->hDC, hPen);
						}
						DeleteObject(hPen);
					}
				}
			}
		}
		cDC.Detach();
	}
}

int CMimicsLineSymbolsComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return((lpCompareItemStruct->itemData1 != lpCompareItemStruct->itemData2) ? ((lpCompareItemStruct->itemData1 < lpCompareItemStruct->itemData2) ? -1 : 1) : 0);
}

BEGIN_MESSAGE_MAP(CMimicsLineSymbolsComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMimicsLineSymbolsComboBox)
	ON_WM_CREATE()
	ON_MESSAGE(LSCB_ADDLINESYMBOL, OnAddLineSymbol)
	ON_MESSAGE(LSCB_INSERTLINESYMBOL, OnInsertLineSymbol)
	ON_MESSAGE(LSCB_GETLINESYMBOL, OnGetLineSymbol)
	ON_MESSAGE(LSCB_FINDLINESYMBOL, OnFindLineSymbol)
	ON_MESSAGE(LSCB_SELECTLINESYMBOL, OnSelectLineSymbol)
	ON_MESSAGE(LSCB_DELETELINESYMBOL, OnDeleteLineSymbol)
	ON_MESSAGE(LSCB_RESETLINESYMBOLS, OnResetLineSymbols)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineSymbolsComboBox message handlers

int CMimicsLineSymbolsComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	MEASUREITEMSTRUCT  sItem;

	if (CComboBox::OnCreate(lpCreateStruct) != -1)
	{
		InsertLineSymbol(GetCount(), LS_NONE);
		InsertLineSymbol(GetCount(), LS_POINT);
		InsertLineSymbol(GetCount(), LS_STROKE);
		InsertLineSymbol(GetCount(), LS_CROSS);
		InsertLineSymbol(GetCount(), LS_SQUARE);
		MeasureItem(&sItem);
		SetItemHeight(-1, sItem.itemHeight);
		return 0;
	}
	return -1;
}

LRESULT CMimicsLineSymbolsComboBox::OnAddLineSymbol(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_ADDSTRING, wParam, lParam);
}

LRESULT CMimicsLineSymbolsComboBox::OnInsertLineSymbol(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_INSERTSTRING, wParam, lParam);
}

LRESULT CMimicsLineSymbolsComboBox::OnGetLineSymbol(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_GETITEMDATA, wParam);
}

LRESULT CMimicsLineSymbolsComboBox::OnFindLineSymbol(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_FINDSTRINGEXACT, wParam, lParam);
}

LRESULT CMimicsLineSymbolsComboBox::OnSelectLineSymbol(WPARAM wParam, LPARAM lParam)
{
	INT  nIndex;

	return(((nIndex = (INT)SendMessage(CB_SELECTSTRING, wParam, lParam)) == CB_ERR) ? SendMessage(CB_SETCURSEL, (WPARAM)-1) : nIndex);
}

LRESULT CMimicsLineSymbolsComboBox::OnDeleteLineSymbol(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)SendMessage(CB_FINDSTRINGEXACT, wParam, lParam));
}

LRESULT CMimicsLineSymbolsComboBox::OnResetLineSymbols(WPARAM wParam, LPARAM lParam)
{
	SendMessage(CB_RESETCONTENT);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsLineSymbolsComboBox

IMPLEMENT_DYNCREATE(CResourceMimicsLineSymbolsComboBox, CMimicsLineSymbolsComboBox)

WNDPROC CResourceMimicsLineSymbolsComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMimicsLineSymbolsComboBox::CResourceMimicsLineSymbolsComboBox(HWND hWnd) : CMimicsLineSymbolsComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsLineSymbolsComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsLineSymbolsComboBox  *pResourceLineSymbolsComboBox;

	if ((pResourceLineSymbolsComboBox = new CResourceMimicsLineSymbolsComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC *CResourceMimicsLineSymbolsComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMimicsLineSymbolsComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsLineSymbolsComboBox, CMimicsLineSymbolsComboBox)
	//{{AFX_MSG_MAP(CResourceMimicsLineSymbolsComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsLineSymbolsComboBox message handlers

BOOL CResourceMimicsLineSymbolsComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CMimicsLineSymbolsComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsHatchesComboBox

IMPLEMENT_DYNCREATE(CMimicsHatchesComboBox, CComboBox)

BOOL CMimicsHatchesComboBox::Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle)
{
	return CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID);
}

BOOL CMimicsHatchesComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsHatchesComboBox  CMimicsHatchesComboBox;

	if ((pClass = CMimicsHatchesComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName  &&  GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceMimicsHatchesComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMimicsHatchesComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMimicsHatchesComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMimicsHatchesComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsHatchesComboBox  CMimicsHatchesComboBox;

	if ((pClass = CMimicsHatchesComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

void CMimicsHatchesComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC  *pDC;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CMimicsCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CMimicsHatchesComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  cDC;
	HPEN  hPen;
	HPEN  hOldPen;
	CRect  rItemArea;
	CBrush  cBkBrush;
	HBRUSH  hHtBrush;
	HBRUSH  hOldBrush;
	HBITMAP  hHtBitmap;
	COLORREF  nOldColor[2];

	if (cDC.Attach(lpDrawItemStruct->hDC))
	{
		if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) || (lpDrawItemStruct->itemAction & ODA_SELECT))
		{
			if (cBkBrush.CreateSolidBrush((lpDrawItemStruct->itemState & ODS_SELECTED) ? (COLORREF)GetSysColor(COLOR_HIGHLIGHT) : (COLORREF)cDC.GetBkColor()))
			{
				cDC.FillRect(&lpDrawItemStruct->rcItem, &cBkBrush);
				if ((lpDrawItemStruct->itemState & ODS_SELECTED) && lpDrawItemStruct->rcItem.left > 0) cDC.DrawFocusRect(&lpDrawItemStruct->rcItem);
			}
			if (!(lpDrawItemStruct->itemState & ODS_DISABLED))
			{
				if (lpDrawItemStruct->itemID != (UINT)-1)
				{
					rItemArea = lpDrawItemStruct->rcItem;
					rItemArea.DeflateRect(2 * GetSystemMetrics(SM_CXBORDER), 0);
					rItemArea.DeflateRect(0, 2 * GetSystemMetrics(SM_CYBORDER));
					nOldColor[0] = cDC.SetBkColor(GetSysColor(COLOR_WINDOW));
					nOldColor[1] = cDC.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
					if ((hPen = CreatePen(PS_NULL, 1, GetSysColor(COLOR_WINDOWTEXT))))
					{
						if ((hOldPen = (HPEN)SelectObject(lpDrawItemStruct->hDC, hPen)))
						{
							if ((hHtBitmap = LoadBitmap(GetModuleInstance(), (lpDrawItemStruct->itemData == HT_SOLID) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNSOLID) : ((lpDrawItemStruct->itemData == HT_HORIZONTAL) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNHORIZONTAL) : ((lpDrawItemStruct->itemData == HT_VERTICAL) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNVERTICAL) : ((lpDrawItemStruct->itemData == HT_BDIAGONAL) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNDIAGONALDOWN) : ((lpDrawItemStruct->itemData == HT_FDIAGONAL) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNDIAGONALUP) : ((lpDrawItemStruct->itemData == HT_CROSS) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNCROSS) : ((lpDrawItemStruct->itemData == HT_DIAGCROSS) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNCROSSDIAGONAL) : ((lpDrawItemStruct->itemData == HT_LPOINTS) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNPOINTSLOW) : ((lpDrawItemStruct->itemData == HT_MPOINTS) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNPOINTSMEDIUM) : MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNPOINTSHIGH))))))))))))
							{
								if ((hOldBrush = (HBRUSH)SelectObject(lpDrawItemStruct->hDC, (HBRUSH)(hHtBrush = CreatePatternBrush(hHtBitmap)))))
								{
									Rectangle(lpDrawItemStruct->hDC, rItemArea.left, rItemArea.top, rItemArea.right, rItemArea.bottom);
									SelectObject(lpDrawItemStruct->hDC, hOldBrush);
									DeleteObject(hHtBrush);
								}
								DeleteObject(hHtBitmap);
							}
							SelectObject(lpDrawItemStruct->hDC, hOldPen);
						}
						DeleteObject(hPen);
					}
					cDC.SetTextColor(nOldColor[1]);
					cDC.SetBkColor(nOldColor[0]);
				}
			}
		}
		cDC.Detach();
	}
}

int CMimicsHatchesComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return((lpCompareItemStruct->itemData1 != lpCompareItemStruct->itemData2) ? ((lpCompareItemStruct->itemData1 < lpCompareItemStruct->itemData2) ? -1 : 1) : 0);
}

BEGIN_MESSAGE_MAP(CMimicsHatchesComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMimicsHatchesComboBox)
	ON_WM_CREATE()
	ON_MESSAGE(HCB_ADDHATCH, OnAddHatch)
	ON_MESSAGE(HCB_INSERTHATCH, OnInsertHatch)
	ON_MESSAGE(HCB_GETHATCH, OnGetHatch)
	ON_MESSAGE(HCB_FINDHATCH, OnFindHatch)
	ON_MESSAGE(HCB_SELECTHATCH, OnSelectHatch)
	ON_MESSAGE(HCB_DELETEHATCH, OnDeleteHatch)
	ON_MESSAGE(HCB_RESETHATCHES, OnResetHatches)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsHatchesComboBox message handlers

int CMimicsHatchesComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	MEASUREITEMSTRUCT  sItem;

	if (CComboBox::OnCreate(lpCreateStruct) != -1)
	{
		InsertHatch(GetCount(), HT_SOLID);
		InsertHatch(GetCount(), HT_HORIZONTAL);
		InsertHatch(GetCount(), HT_VERTICAL);
		InsertHatch(GetCount(), HT_BDIAGONAL);
		InsertHatch(GetCount(), HT_FDIAGONAL);
		InsertHatch(GetCount(), HT_CROSS);
		InsertHatch(GetCount(), HT_DIAGCROSS);
		InsertHatch(GetCount(), HT_LPOINTS);
		InsertHatch(GetCount(), HT_MPOINTS);
		InsertHatch(GetCount(), HT_HPOINTS);
		MeasureItem(&sItem);
		SetItemHeight(-1, sItem.itemHeight);
		return 0;
	}
	return -1;
}

LRESULT CMimicsHatchesComboBox::OnAddHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_ADDSTRING, wParam, lParam);
}

LRESULT CMimicsHatchesComboBox::OnInsertHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_INSERTSTRING, wParam, lParam);
}

LRESULT CMimicsHatchesComboBox::OnGetHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_GETITEMDATA, wParam);
}

LRESULT CMimicsHatchesComboBox::OnFindHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_FINDSTRINGEXACT, wParam, lParam);
}

LRESULT CMimicsHatchesComboBox::OnSelectHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_SELECTSTRING, wParam, lParam);
}

LRESULT CMimicsHatchesComboBox::OnDeleteHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)SendMessage(CB_FINDSTRINGEXACT, wParam, lParam));
}

LRESULT CMimicsHatchesComboBox::OnResetHatches(WPARAM wParam, LPARAM lParam)
{
	SendMessage(CB_RESETCONTENT);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsHatchesComboBox

IMPLEMENT_DYNCREATE(CResourceMimicsHatchesComboBox, CMimicsHatchesComboBox)

WNDPROC CResourceMimicsHatchesComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMimicsHatchesComboBox::CResourceMimicsHatchesComboBox(HWND hWnd) : CMimicsHatchesComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsHatchesComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsHatchesComboBox  *pResourceHatchesComboBox;

	if ((pResourceHatchesComboBox = new CResourceMimicsHatchesComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC *CResourceMimicsHatchesComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMimicsHatchesComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsHatchesComboBox, CMimicsHatchesComboBox)
	//{{AFX_MSG_MAP(CResourceMimicsHatchesComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsHatchesComboBox message handlers

BOOL CResourceMimicsHatchesComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CMimicsHatchesComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsFontsComboBox

IMPLEMENT_DYNCREATE(CMimicsFontsComboBox, CComboBox)

CMimicsFontsComboBox::CMimicsFontsComboBox() : CComboBox()
{
	m_hPrinterFontBitmap = (HBITMAP)NULL;
	m_hTrueTypeFontBitmap = (HBITMAP)NULL;
}

BOOL CMimicsFontsComboBox::Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle)
{
	if (CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT | CBS_OEMCONVERT)) & ~(CBS_OWNERDRAWFIXED | CBS_UPPERCASE | CBS_LOWERCASE)) | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID))
	{
		SetFont(CMimicsCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsFontsComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsFontsComboBox  CMimicsFontsComboBox;

	if ((pClass = CMimicsFontsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName  &&  GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceMimicsFontsComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMimicsFontsComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMimicsFontsComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMimicsFontsComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsFontsComboBox  CMimicsFontsComboBox;

	if ((pClass = CMimicsFontsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

void CMimicsFontsComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC  *pDC;
	CFont  *pOldFont;
	BITMAP  sFont[2];
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CMimicsCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont) && GetObject(m_hTrueTypeFontBitmap, sizeof(BITMAP), &sFont[0]) && GetObject(m_hPrinterFontBitmap, sizeof(BITMAP), &sFont[1])) ? (max(max(sFont[0].bmHeight, sFont[1].bmHeight), tmFont.tmHeight) + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CMimicsFontsComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  cDC;
	CDC  cBitmapDC;
	INT  nOldColor;
	INT  nOldBkMode;
	CFont  *pOldFont;
	CBrush  cBkBrush;
	BITMAP  sFont[2];
	CBitmap  *pOldBitmap;
	PFONTINFO  pFontInfo = (PFONTINFO)lpDrawItemStruct->itemData;

	if (cDC.Attach(lpDrawItemStruct->hDC))
	{
		if (GetObject(m_hTrueTypeFontBitmap, sizeof(BITMAP), &sFont[0]) && GetObject(m_hPrinterFontBitmap, sizeof(BITMAP), &sFont[1]))
		{
			if (!(lpDrawItemStruct->itemState & ODS_DISABLED) && ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) || (lpDrawItemStruct->itemAction & ODA_SELECT)))
			{
				if (cBkBrush.CreateSolidBrush((lpDrawItemStruct->itemState & ODS_SELECTED) ? (COLORREF)GetSysColor(COLOR_HIGHLIGHT) : (COLORREF)cDC.GetBkColor()))
				{
					cDC.FillRect(CRect((!(GetStyle() & CBS_DROPDOWNLIST) || !lpDrawItemStruct->rcItem.left) ? (lpDrawItemStruct->rcItem.left + 4 * GetSystemMetrics(SM_CXBORDER) + max(sFont[0].bmWidth, sFont[1].bmWidth)) : lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom), &cBkBrush);
					if ((GetStyle() & CBS_DROPDOWNLIST) && (lpDrawItemStruct->itemState & ODS_SELECTED) && lpDrawItemStruct->rcItem.left > 0) cDC.DrawFocusRect(&lpDrawItemStruct->rcItem);
				}
				if (AfxIsValidAddress(pFontInfo, sizeof(FONTINFO), FALSE) && lpDrawItemStruct->itemID != (UINT)-1)
				{
					if (!(GetStyle() & CBS_DROPDOWNLIST) || !lpDrawItemStruct->rcItem.left)
					{
						if ((cBitmapDC.CreateCompatibleDC(&cDC)))
						{
							if (pFontInfo->dwType & TRUETYPE_FONTTYPE)
							{
								if ((pOldBitmap = cBitmapDC.SelectObject(CBitmap::FromHandle(m_hTrueTypeFontBitmap))))
								{
									cDC.BitBlt(lpDrawItemStruct->rcItem.left + 2 * GetSystemMetrics(SM_CXBORDER), lpDrawItemStruct->rcItem.top + (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top - sFont[0].bmHeight) / 2, sFont[0].bmWidth, sFont[0].bmHeight, &cBitmapDC, 0, 0, SRCCOPY);
									cBitmapDC.SelectObject(pOldBitmap);
								}
							}
							if (pFontInfo->dwType & DEVICE_FONTTYPE)
							{
								if ((pOldBitmap = cBitmapDC.SelectObject(CBitmap::FromHandle(m_hPrinterFontBitmap))))
								{
									cDC.BitBlt(lpDrawItemStruct->rcItem.left + 2 * GetSystemMetrics(SM_CXBORDER), lpDrawItemStruct->rcItem.top + (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top - sFont[1].bmHeight) / 2, sFont[1].bmWidth, sFont[1].bmHeight, &cBitmapDC, 0, 0, SRCCOPY);
									cBitmapDC.SelectObject(pOldBitmap);
								}
							}
							cBitmapDC.DeleteDC();
						}
					}
					if ((pOldFont = cDC.SelectObject(CMimicsCustomControls::GetCustomControlFont(this))))
					{
						if ((nOldBkMode = cDC.SetBkMode(TRANSPARENT)) == OPAQUE || nOldBkMode == TRANSPARENT)
						{
							nOldColor = cDC.SetTextColor((lpDrawItemStruct->itemState & ODS_SELECTED) ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_WINDOWTEXT));
							cDC.DrawText(pFontInfo->logFont.lfFaceName, lstrlen(pFontInfo->logFont.lfFaceName), CRect((!(GetStyle() & CBS_DROPDOWNLIST) || !lpDrawItemStruct->rcItem.left) ? (lpDrawItemStruct->rcItem.left + 6 * GetSystemMetrics(SM_CXBORDER) + max(sFont[0].bmWidth, sFont[1].bmWidth)) : (lpDrawItemStruct->rcItem.left + 2 * GetSystemMetrics(SM_CXBORDER)), lpDrawItemStruct->rcItem.top, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom), DT_LEFT | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX | DT_EXTERNALLEADING);
							cDC.SetTextColor(nOldColor);
							cDC.SetBkMode(nOldBkMode);
						}
						cDC.SelectObject(pOldFont);
					}
				}
			}
		}
		cDC.Detach();
	}
}

int CMimicsFontsComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	PFONTINFO  pFontInfo[2] = { (PFONTINFO)lpCompareItemStruct->itemData1,(PFONTINFO)lpCompareItemStruct->itemData2 };

	return lstrcmp(pFontInfo[0]->logFont.lfFaceName, pFontInfo[1]->logFont.lfFaceName);
}

void CMimicsFontsComboBox::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
{
	PFONTINFO  pFontInfo = (PFONTINFO)lpDeleteItemStruct->itemData;

	GlobalFree(pFontInfo);
}

INT CALLBACK CMimicsFontsComboBox::EnumFontsProc(CONST LOGFONT *pLogFont, CONST TEXTMETRIC *pTextMetric, DWORD dwFontType, LPARAM pData)
{
	INT  nIndex;
	CWnd  *pWnd;
	PFONTINFO  pFontInfo;
	PFONTENUMINFO  pFontEnumInfo = (PFONTENUMINFO)pData;

	if ((!(pFontEnumInfo->dwTypes & CF_TTONLY) || ((pFontEnumInfo->dwTypes & CF_TTONLY) && (dwFontType & TRUETYPE_FONTTYPE))) && (!(pFontEnumInfo->dwTypes & CF_ANSIONLY) || ((pFontEnumInfo->dwTypes & CF_ANSIONLY) && pLogFont->lfCharSet == ANSI_CHARSET)) && (!(pFontEnumInfo->dwTypes & CF_SCALABLEONLY) || ((pFontEnumInfo->dwTypes & CF_SCALABLEONLY) && (pLogFont->lfPitchAndFamily & VARIABLE_PITCH))) && (!(pFontEnumInfo->dwTypes & CF_FIXEDPITCHONLY) || ((pFontEnumInfo->dwTypes & CF_FIXEDPITCHONLY) && (pLogFont->lfPitchAndFamily & FIXED_PITCH))) && (!(pFontEnumInfo->dwTypes & CF_PRINTERFONTS) || ((pFontEnumInfo->dwTypes & CF_PRINTERFONTS) && (dwFontType & DEVICE_FONTTYPE))) && (!(pFontEnumInfo->dwTypes & CF_SCREENFONTS) || ((pFontEnumInfo->dwTypes & CF_SCREENFONTS) && !(dwFontType & DEVICE_FONTTYPE))))
	{
		if ((pFontEnumInfo->dwTypes & 0x80000000) || pLogFont->lfCharSet != SYMBOL_CHARSET)
		{
			if ((pFontInfo = (PFONTINFO)GlobalAlloc(GPTR, sizeof(FONTINFO))) != (PFONTINFO)NULL)
			{
				for (CopyMemory(&pFontInfo->logFont, pLogFont, sizeof(LOGFONT)), pFontInfo->dwType = dwFontType; (nIndex = ((pWnd = CWnd::FromHandle(pFontEnumInfo->hWnd))) ? (INT)pWnd->SendMessage(CB_ADDSTRING, (WPARAM)NULL, (LPARAM)pFontInfo->logFont.lfFaceName) : -1) >= 0; )
				{
					if (pWnd->SendMessage(CB_SETITEMDATA, nIndex, (LPARAM)pFontInfo) == CB_ERR)
					{
						pWnd->SendMessage(CB_DELETESTRING, nIndex);
						nIndex = -1;
					}
					break;
				}
				if (nIndex < 0)
				{
					GlobalFree(pFontInfo);
					return FALSE;
				}
				return TRUE;
			}
			return FALSE;
		}
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMimicsFontsComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMimicsFontsComboBox)
	ON_WM_CREATE()
	ON_WM_ENABLE()
	ON_WM_DESTROY()
	ON_MESSAGE(FCB_DIR, OnDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsFontsComboBox message handlers

int CMimicsFontsComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	MEASUREITEMSTRUCT  sItem;

	if (CComboBox::OnCreate(lpCreateStruct) != -1)
	{
		if ((m_hTrueTypeFontBitmap = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_FONTSCOMBOBOXFONTTRUETYPE))))
		{
			if ((m_hPrinterFontBitmap = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_FONTSCOMBOBOXFONTPRINTER))))
			{
				MeasureItem(&sItem);
				SetItemHeight(-1, sItem.itemHeight);
				return 0;
			}
		}
	}
	return -1;
}

void CMimicsFontsComboBox::OnEnable(BOOL bEnable)
{
	INT  nItem;
	PFONTINFO  pFontInfo;

	for (nItem = 0; bEnable && m_pItems.GetCount(); nItem++)
	{
		if ((pFontInfo = (PFONTINFO)m_pItems.RemoveHead()))
		{
			InsertString(nItem, pFontInfo->logFont.lfFaceName);
			SetItemDataPtr(nItem, pFontInfo);
		}
	}
	for (m_nItem = (bEnable && GetCount()) ? SetCurSel(m_nItem) : GetCurSel(); !bEnable && GetCount() > 0; DeleteString(0)) m_pItems.AddTail((CObject *)GetItemDataPtr(0));
	CComboBox::OnEnable(bEnable);
}

LRESULT CMimicsFontsComboBox::OnDir(WPARAM wParam, LPARAM lParam)
{
	FONTENUMINFO  sFontEnumInfo = { (HDC)lParam,GetSafeHwnd(),(DWORD)wParam };

	ResetContent();
	if ((sFontEnumInfo.hDC = (!(sFontEnumInfo.dwTypes & CF_PRINTERFONTS)) ? ::GetDC(sFontEnumInfo.hWnd) : sFontEnumInfo.hDC))
	{
		EnumFontFamilies(sFontEnumInfo.hDC, (LPCTSTR)NULL, EnumFontsProc, (LPARAM)&sFontEnumInfo);
		if (!(sFontEnumInfo.dwTypes & CF_PRINTERFONTS)) ::ReleaseDC(sFontEnumInfo.hWnd, sFontEnumInfo.hDC);
		return GetCount();
	}
	return 0;
}

void CMimicsFontsComboBox::OnDestroy()
{
	DeleteObject(m_hPrinterFontBitmap);
	DeleteObject(m_hTrueTypeFontBitmap);
	m_hPrinterFontBitmap = (HBITMAP)NULL;
	m_hTrueTypeFontBitmap = (HBITMAP)NULL;
	CComboBox::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsFontsComboBox

IMPLEMENT_DYNCREATE(CResourceMimicsFontsComboBox, CMimicsFontsComboBox)

WNDPROC CResourceMimicsFontsComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMimicsFontsComboBox::CResourceMimicsFontsComboBox(HWND hWnd) : CMimicsFontsComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsFontsComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsFontsComboBox  *pResourceFontsComboBox;

	if ((pResourceFontsComboBox = new CResourceMimicsFontsComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC *CResourceMimicsFontsComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMimicsFontsComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsFontsComboBox, CMimicsFontsComboBox)
	//{{AFX_MSG_MAP(CResourceMimicsFontsComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsFontsComboBox message handlers

BOOL CResourceMimicsFontsComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT | CBS_OEMCONVERT)) & ~(CBS_OWNERDRAWFIXED | CBS_UPPERCASE | CBS_LOWERCASE)) | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CMimicsFontsComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsAlignmentComboBox

IMPLEMENT_DYNCREATE(CMimicsAlignmentComboBox, CComboBox)

CMimicsAlignmentComboBox::CMimicsAlignmentComboBox() : CComboBox()
{
	m_hImageBitmap[AL_HLEFTVTOP] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HLEFTVCENTER] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HLEFTVBOTTOM] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HCENTERVTOP] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HCENTERVCENTER] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HCENTERVBOTTOM] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HRIGHTVTOP] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HRIGHTVCENTER] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HRIGHTVBOTTOM] = (HBITMAP)NULL;
}

BOOL CMimicsAlignmentComboBox::Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle)
{
	return CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (ALCBS_LEFT | ALCBS_CENTER | ALCBS_RIGHT | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID);
}

BOOL CMimicsAlignmentComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsAlignmentComboBox  CMimicsAlignmentComboBox;

	if ((pClass = CMimicsAlignmentComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName  &&  GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceMimicsAlignmentComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMimicsAlignmentComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMimicsAlignmentComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMimicsAlignmentComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsAlignmentComboBox  CMimicsAlignmentComboBox;

	if ((pClass = CMimicsAlignmentComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

void CMimicsAlignmentComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC  *pDC;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;
	BITMAP  sImage;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CMimicsCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont) && GetObject(m_hImageBitmap[0], sizeof(BITMAP), &sImage)) ? (max(sImage.bmHeight, tmFont.tmHeight) + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CMimicsAlignmentComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  cDC;
	CDC  cMemDC;
	CRect  rImage;
	CBrush  cBkBrush;
	CBitmap  *pOldBitmap;
	BITMAP  sImage;

	if (cDC.Attach(lpDrawItemStruct->hDC))
	{
		if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) || (lpDrawItemStruct->itemAction & ODA_SELECT))
		{
			if (cBkBrush.CreateSolidBrush((lpDrawItemStruct->itemState & ODS_SELECTED) ? (COLORREF)GetSysColor(COLOR_HIGHLIGHT) : (COLORREF)cDC.GetBkColor()))
			{
				cDC.FillRect(&lpDrawItemStruct->rcItem, &cBkBrush);
				if ((lpDrawItemStruct->itemState & ODS_SELECTED) && lpDrawItemStruct->rcItem.left > 0) cDC.DrawFocusRect(&lpDrawItemStruct->rcItem);
			}
			if (!(lpDrawItemStruct->itemState & ODS_DISABLED))
			{
				if (lpDrawItemStruct->itemID >= (UINT)AL_HLEFTVTOP  &&  lpDrawItemStruct->itemID <= (UINT)AL_HRIGHTVBOTTOM)
				{
					if (cMemDC.CreateCompatibleDC(&cDC))
					{
						if ((pOldBitmap = cMemDC.SelectObject(CBitmap::FromHandle(m_hImageBitmap[lpDrawItemStruct->itemID]))))
						{
							if (GetObject(m_hImageBitmap[lpDrawItemStruct->itemID], sizeof(BITMAP), &sImage))
							{
								rImage.left = lpDrawItemStruct->rcItem.left + GetSystemMetrics(SM_CXEDGE);
								rImage.left = (m_dwStyle & ALCBS_CENTER) ? max(lpDrawItemStruct->rcItem.left + (lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left - sImage.bmWidth) / 2, lpDrawItemStruct->rcItem.left) : rImage.left;
								rImage.left = (m_dwStyle & ALCBS_RIGHT) ? (lpDrawItemStruct->rcItem.right - GetSystemMetrics(SM_CXEDGE) - sImage.bmWidth) : rImage.left;
								rImage.top = max(lpDrawItemStruct->rcItem.top + (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top - sImage.bmHeight) / 2, lpDrawItemStruct->rcItem.top);
								rImage.right = lpDrawItemStruct->rcItem.left + GetSystemMetrics(SM_CXEDGE) + sImage.bmWidth;
								rImage.right = (m_dwStyle & ALCBS_CENTER) ? min(lpDrawItemStruct->rcItem.left + (lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left - sImage.bmWidth) / 2 + sImage.bmWidth, lpDrawItemStruct->rcItem.right) : rImage.right;
								rImage.right = (m_dwStyle & ALCBS_RIGHT) ? (lpDrawItemStruct->rcItem.right - GetSystemMetrics(SM_CXEDGE)) : rImage.right;
								rImage.bottom = min(lpDrawItemStruct->rcItem.top + (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top - sImage.bmHeight) / 2 + sImage.bmHeight, lpDrawItemStruct->rcItem.bottom);
								cDC.BitBlt(rImage.left, rImage.top, rImage.Width(), rImage.Height(), &cMemDC, 0, 0, SRCCOPY);
							}
							cMemDC.SelectObject(pOldBitmap);
						}
						cMemDC.DeleteDC();
					}
				}
			}
		}
		cDC.Detach();
	}
}

int CMimicsAlignmentComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	if (lpCompareItemStruct->itemData1 > lpCompareItemStruct->itemData2) return 1;
	if (lpCompareItemStruct->itemData1 < lpCompareItemStruct->itemData2) return -1;
	return 0;
}

BEGIN_MESSAGE_MAP(CMimicsAlignmentComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMimicsAlignmentComboBox)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_MESSAGE(ALCB_ADDALIGNMENT, OnAddAlignment)
	ON_MESSAGE(ALCB_INSERTALIGNMENT, OnInsertAlignment)
	ON_MESSAGE(ALCB_GETALIGNMENT, OnGetAlignment)
	ON_MESSAGE(ALCB_FINDALIGNMENT, OnFindAlignment)
	ON_MESSAGE(ALCB_SELECTALIGNMENT, OnSelectAlignment)
	ON_MESSAGE(ALCB_DELETEALIGNMENT, OnDeleteAlignment)
	ON_MESSAGE(ALCB_RESETALIGNMENTS, OnResetAlignments)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsAlignmentComboBox message handlers

int CMimicsAlignmentComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	MEASUREITEMSTRUCT  sItem;

	if (CComboBox::OnCreate(lpCreateStruct) != -1)
	{
		if ((m_hImageBitmap[AL_HLEFTVTOP] = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLLEFTTOP))))
		{
			if ((m_hImageBitmap[AL_HLEFTVCENTER] = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLLEFTMIDDLE))))
			{
				if ((m_hImageBitmap[AL_HLEFTVBOTTOM] = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLLEFTBOTTOM))))
				{
					if ((m_hImageBitmap[AL_HCENTERVTOP] = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLCENTERTOP))))
					{
						if ((m_hImageBitmap[AL_HCENTERVCENTER] = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLCENTERMIDDLE))))
						{
							if ((m_hImageBitmap[AL_HCENTERVBOTTOM] = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLCENTERBOTTOM))))
							{
								if ((m_hImageBitmap[AL_HRIGHTVTOP] = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLRIGHTTOP))))
								{
									if ((m_hImageBitmap[AL_HRIGHTVCENTER] = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLRIGHTMIDDLE))))
									{
										if ((m_hImageBitmap[AL_HRIGHTVBOTTOM] = LoadBitmap(GetModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLRIGHTBOTTOM))))
										{
											AddAlignment(AL_HLEFTVTOP);
											AddAlignment(AL_HLEFTVCENTER);
											AddAlignment(AL_HLEFTVBOTTOM);
											AddAlignment(AL_HCENTERVTOP);
											AddAlignment(AL_HCENTERVCENTER);
											AddAlignment(AL_HCENTERVBOTTOM);
											AddAlignment(AL_HRIGHTVTOP);
											AddAlignment(AL_HRIGHTVCENTER);
											AddAlignment(AL_HRIGHTVBOTTOM);
											MeasureItem(&sItem);
											SetItemHeight(-1, sItem.itemHeight);
											return 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return -1;
}

LRESULT CMimicsAlignmentComboBox::OnAddAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_ADDSTRING, wParam, lParam);
}

LRESULT CMimicsAlignmentComboBox::OnInsertAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_INSERTSTRING, wParam, lParam);
}

LRESULT CMimicsAlignmentComboBox::OnGetAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_GETITEMDATA, wParam);
}

LRESULT CMimicsAlignmentComboBox::OnFindAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_FINDSTRINGEXACT, wParam, lParam);
}

LRESULT CMimicsAlignmentComboBox::OnSelectAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_SELECTSTRING, wParam, lParam);
}

LRESULT CMimicsAlignmentComboBox::OnDeleteAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)SendMessage(CB_FINDSTRINGEXACT, wParam, lParam));
}

LRESULT CMimicsAlignmentComboBox::OnResetAlignments(WPARAM wParam, LPARAM lParam)
{
	SendMessage(CB_RESETCONTENT);
	return 0;
}

void CMimicsAlignmentComboBox::OnDestroy()
{
	DeleteObject(m_hImageBitmap[AL_HLEFTVTOP]);
	DeleteObject(m_hImageBitmap[AL_HLEFTVCENTER]);
	DeleteObject(m_hImageBitmap[AL_HLEFTVBOTTOM]);
	DeleteObject(m_hImageBitmap[AL_HCENTERVTOP]);
	DeleteObject(m_hImageBitmap[AL_HCENTERVCENTER]);
	DeleteObject(m_hImageBitmap[AL_HCENTERVBOTTOM]);
	DeleteObject(m_hImageBitmap[AL_HRIGHTVTOP]);
	DeleteObject(m_hImageBitmap[AL_HRIGHTVCENTER]);
	DeleteObject(m_hImageBitmap[AL_HRIGHTVBOTTOM]);
	m_hImageBitmap[AL_HLEFTVTOP] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HLEFTVCENTER] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HLEFTVBOTTOM] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HCENTERVTOP] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HCENTERVCENTER] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HCENTERVBOTTOM] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HRIGHTVTOP] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HRIGHTVCENTER] = (HBITMAP)NULL;
	m_hImageBitmap[AL_HRIGHTVBOTTOM] = (HBITMAP)NULL;
	CComboBox::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsAlignmentComboBox

IMPLEMENT_DYNCREATE(CResourceMimicsAlignmentComboBox, CMimicsAlignmentComboBox)

WNDPROC CResourceMimicsAlignmentComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMimicsAlignmentComboBox::CResourceMimicsAlignmentComboBox(HWND hWnd) : CMimicsAlignmentComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsAlignmentComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsAlignmentComboBox  *pResourceAlignmentComboBox;

	if ((pResourceAlignmentComboBox = new CResourceMimicsAlignmentComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC *CResourceMimicsAlignmentComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMimicsAlignmentComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsAlignmentComboBox, CMimicsAlignmentComboBox)
	//{{AFX_MSG_MAP(CResourceMimicsAlignmentComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsAlignmentComboBox message handlers

BOOL CResourceMimicsAlignmentComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (ALCBS_LEFT | ALCBS_CENTER | ALCBS_RIGHT | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CMimicsAlignmentComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsSpinButtons

IMPLEMENT_DYNCREATE(CMimicsSpinButtons, CSpinButtonCtrl)

CMimicsSpinButtons::CMimicsSpinButtons() : CSpinButtonCtrl()
{
	return;
}

BEGIN_MESSAGE_MAP(CMimicsSpinButtons, CSpinButtonCtrl)
	//{{AFX_MSG_MAP(CMimicsSpinButtons)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsSpinButtons message handlers

void CMimicsSpinButtons::OnMouseMove(UINT nFlags, CPoint point)
{
	CMimicsSpinBox  *pSpinBox;
	CMimicsTimeSpinBox  *pTimeSpinBox;

	if ((pSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CMimicsSpinBox))) ? (CMimicsSpinBox *)GetParent() : (CMimicsSpinBox *)NULL)) pSpinBox->UpdateUI();
	if ((pTimeSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CMimicsTimeSpinBox))) ? (CMimicsTimeSpinBox *)GetParent() : (CMimicsTimeSpinBox *)NULL)) pTimeSpinBox->UpdateUI();
	CSpinButtonCtrl::OnMouseMove(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsSpinBox

IMPLEMENT_DYNCREATE(CMimicsSpinBox, CWnd)

CMimicsSpinBox::CMimicsSpinBox() : CWnd()
{
	m_bState[0] = FALSE;
	m_bState[1] = FALSE;
}

BOOL CMimicsSpinBox::Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle)
{
	return CWnd::Create((LPCTSTR)NULL, EMPTYSTRING, MAKELONG((((m_dwStyle = ((LOWORD(dwStyle) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LOWERCASE | ES_UPPERCASE | ES_NUMBER | ES_PASSWORD | ES_READONLY | ES_WANTRETURN)))) ? NULL : NULL), HIWORD(dwStyle)) | WS_CHILD, rect, pParentWnd, nID);
}

BOOL CMimicsSpinBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsSpinBox  CMimicsSpinBox;

	if ((pClass = CMimicsSpinBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (szClass.Mid(cPos, 1) != szBaseClass.Mid(cPos, 1)) break;
			continue;
		}
		if (cPos < cbClassName  &&  !GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
		{
			sWndClass.lpszClassName = (LPCTSTR)szClass;
			sWndClass.lpfnWndProc = CResourceMimicsSpinBox::WndProcHook;
			sWndClass.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
			sWndClass.cbClsExtra = 0;
			sWndClass.cbWndExtra = 0;
			sWndClass.hIcon = (HICON)NULL;
			sWndClass.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
			sWndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			sWndClass.lpszMenuName = (LPCTSTR)NULL;
			return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
		}
	}
	return TRUE;
}

BOOL CMimicsSpinBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsSpinBox  CMimicsSpinBox;

	if ((pClass = CMimicsSpinBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (szClass.Mid(cPos, 1) != szBaseClass.Mid(cPos, 1)) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

void CMimicsSpinBox::UpdateUI()
{
	if (IsThemeActive())
	{
		if (!m_bState[1])
		{
			SetTimer(SPINBOX_UI_TIMERID, SPINBOX_UI_TIMEOUT, NULL);
			m_bState[1] = TRUE;
			RedrawWindow();
		}
	}
}
void CMimicsSpinBox::UpdateUI(CONST POINT &point)
{
	CRect  rSpinBox;
	BOOL  bState;

	if (IsThemeActive())
	{
		for (bState = m_bState[1], GetClientRect(rSpinBox); rSpinBox.PtInRect(point); )
		{
			if (!m_bState[1]) SetTimer(SPINBOX_UI_TIMERID, SPINBOX_UI_TIMEOUT, NULL);
			m_bState[1] = TRUE;
			break;
		}
		if (!rSpinBox.PtInRect(point))
		{
			if (m_bState[1]) KillTimer(SPINBOX_UI_TIMERID);
			m_bState[1] = FALSE;
		}
		if (m_bState[1] != bState) RedrawWindow();
	}
}

INT CMimicsSpinBox::CalcIndent()
{
	CDC  *pDC;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			pDC->GetTextMetrics(&tmFont);
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return tmFont.tmAveCharWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CMimicsSpinBox, CWnd)
	//{{AFX_MSG_MAP(CMimicsSpinBox)
	ON_WM_CREATE()
	ON_WM_NCCREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_MESSAGE(SBXM_SETPOS, OnSetPos)
	ON_MESSAGE(SBXM_GETPOS, OnGetPos)
	ON_MESSAGE(SBXM_SETBASE, OnSetBase)
	ON_MESSAGE(SBXM_GETBASE, OnGetBase)
	ON_MESSAGE(SBXM_SETRANGE, OnSetRange)
	ON_MESSAGE(SBXM_GETRANGE, OnGetRange)
	ON_MESSAGE(SBXM_SETACCEL, OnSetAccel)
	ON_MESSAGE(SBXM_GETACCEL, OnGetAccel)
	ON_MESSAGE(SBXM_SETSEL, OnSetSel)
	ON_MESSAGE(SBXM_GETSEL, OnGetSel)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_MESSAGE(WM_GETFONT, OnGetFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsSpinBox message handlers

int CMimicsSpinBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect  rSpinCtrl;

	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		if (m_wndSpinCtrl.Create(UDS_NOTHOUSANDS | ((IsWindowEnabled()) ? (WS_CHILD | WS_VISIBLE) : (WS_CHILD | WS_DISABLED | WS_VISIBLE)), CRect(0, 0, 0, 0), this, 0) && m_wndEditCtrl.Create(this, CRect(0, 0, 0, 0), m_wndSpinCtrl.GetDlgCtrlID() + 1, m_dwStyle | ((IsWindowEnabled()) ? (WS_CHILD | WS_VISIBLE) : WS_CHILD) | (lpCreateStruct->style & WS_TABSTOP)))
		{
			for (SetWindowPos(&m_wndEditCtrl, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE), SetFont(CMimicsCustomControls::GetCustomControlFont(this)), rSpinCtrl.SetRect(lpCreateStruct->cx - 3 * lpCreateStruct->cy / 4 + (3 * lpCreateStruct->cy / 4) % 2, 0, lpCreateStruct->cx, lpCreateStruct->cy); (GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_CLIENTEDGE) != WS_EX_CLIENTEDGE; )
			{
				rSpinCtrl.DeflateRect(0, GetSystemMetrics(SM_CYBORDER));
				rSpinCtrl.OffsetRect(-GetSystemMetrics(SM_CXBORDER), 0);
				break;
			}
			m_wndEditCtrl.MoveWindow(CalcIndent(), rSpinCtrl.top, lpCreateStruct->cx - CalcIndent() - rSpinCtrl.Width(), rSpinCtrl.Height());
			m_wndSpinCtrl.MoveWindow(rSpinCtrl);
			return 0;
		}
	}
	return -1;
}

BOOL CMimicsSpinBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	for (SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~WS_BORDER); !IsThemeActive(); )
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_CLIENTEDGE);
		break;
	}
	return CWnd::OnNcCreate(lpCreateStruct);
}

void CMimicsSpinBox::OnSize(UINT nType, int cx, int cy)
{
	CRect  rSpinCtrl;

	if (IsWindow(m_wndSpinCtrl.GetSafeHwnd()) && IsWindow(m_wndEditCtrl.GetSafeHwnd()))
	{
		for (m_wndSpinCtrl.GetWindowRect(rSpinCtrl), rSpinCtrl.SetRect(cx - rSpinCtrl.Width(), 0, cx, cy); (GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_CLIENTEDGE) != WS_EX_CLIENTEDGE; )
		{
			rSpinCtrl.DeflateRect(0, GetSystemMetrics(SM_CYBORDER));
			rSpinCtrl.OffsetRect(-GetSystemMetrics(SM_CXBORDER), 0);
			break;
		}
		m_wndEditCtrl.MoveWindow(CalcIndent(), rSpinCtrl.top, cx - CalcIndent() - rSpinCtrl.Width(), rSpinCtrl.Height());
		m_wndSpinCtrl.MoveWindow(rSpinCtrl);
	}
	CWnd::OnSize(nType, cx, cy);
}

BOOL CMimicsSpinBox::OnEraseBkgnd(CDC *pDC)
{
	HTHEME  hTheme;
	CBrush  cBkgndBrush;
	CRect  rSpinBox;

	for (GetClientRect(rSpinBox); (hTheme = (IsThemeActive()) ? OpenThemeData(GetSafeHwnd(), VSCLASS_EDIT) : (HTHEME)NULL); )
	{
		DrawThemeBackground(hTheme, pDC->GetSafeHdc(), EP_EDITBORDER_NOSCROLL, (IsWindowEnabled()) ? ((m_bState[0]) ? EPSN_FOCUSED : ((m_bState[1]) ? EPSN_HOT : EPSN_NORMAL)) : EPSN_DISABLED, rSpinBox, (LPCRECT)NULL);
		CloseThemeData(hTheme);
		return TRUE;
	}
	if (cBkgndBrush.Attach((HBRUSH)SendMessage((IsWindowEnabled()) ? WM_CTLCOLOREDIT : WM_CTLCOLORSTATIC, (WPARAM)pDC->GetSafeHdc(), (LPARAM)GetSafeHwnd())))
	{
		pDC->FillRect(rSpinBox, &cBkgndBrush);
		cBkgndBrush.Detach();
		return TRUE;
	}
	return CWnd::OnEraseBkgnd(pDC);
}

void CMimicsSpinBox::OnEnable(BOOL bEnable)
{
	Invalidate(TRUE);
	m_wndEditCtrl.ShowWindow((bEnable) ? SW_SHOWNA : SW_HIDE);
	m_wndSpinCtrl.EnableWindow(bEnable);
	CWnd::OnEnable(bEnable);
}

void CMimicsSpinBox::OnMouseMove(UINT nFlags, CPoint point)
{
	UpdateUI(point);
	CWnd::OnMouseMove(nFlags, point);
}

void CMimicsSpinBox::OnSetFocus(CWnd *pOldWnd)
{
	m_wndEditCtrl.SetSel(0, -1);
	m_wndEditCtrl.SetFocus();
}

void CMimicsSpinBox::OnTimer(UINT_PTR nTimerID)
{
	POINT  ptCursor;

	if (nTimerID == SPINBOX_UI_TIMERID)
	{
		GetCursorPos(&ptCursor);
		ScreenToClient(&ptCursor);
		UpdateUI(ptCursor);
	}
	CWnd::OnTimer(nTimerID);
}

BOOL CMimicsSpinBox::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == EN_SETFOCUS)
	{
		for (GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), SBXN_SETFOCUS), (LPARAM)GetSafeHwnd()), m_bState[0] = TRUE; IsThemeActive(); )
		{
			RedrawWindow();
			break;
		}
		return TRUE;
	}
	if (HIWORD(wParam) == EN_KILLFOCUS)
	{
		for (GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), SBXN_KILLFOCUS), (LPARAM)GetSafeHwnd()), m_bState[0] = FALSE; IsThemeActive(); )
		{
			RedrawWindow();
			break;
		}
		return TRUE;
	}
	if (HIWORD(wParam) == EN_CHANGE)
	{
		GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), SBXN_CHANGE), (LPARAM)GetSafeHwnd());
		return TRUE;
	}
	if (HIWORD(wParam) == EN_UPDATE)
	{
		GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), SBXN_UPDATE), (LPARAM)GetSafeHwnd());
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsSpinBox::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMUPDOWN  *pNotifyInfo = (NMUPDOWN *)lParam;

	if (pNotifyInfo->hdr.code == UDN_DELTAPOS)
	{
		m_wndEditCtrl.SetPos(m_wndEditCtrl.GetPos() - pNotifyInfo->iDelta, TRUE);
		m_wndEditCtrl.SetSel(0, -1);
		m_wndEditCtrl.SetFocus();
		return TRUE;
	}
	return FALSE;
}

LRESULT CMimicsSpinBox::OnSetPos(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_SETPOS, wParam, lParam) : FALSE);
}

LRESULT CMimicsSpinBox::OnGetPos(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_GETPOS, wParam, lParam) : FALSE);
}

LRESULT CMimicsSpinBox::OnSetBase(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_SETBASE, wParam, lParam) : FALSE);
}

LRESULT CMimicsSpinBox::OnGetBase(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_GETBASE, wParam, lParam) : FALSE);
}

LRESULT CMimicsSpinBox::OnSetRange(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_SETRANGE, wParam, lParam) : FALSE);
}

LRESULT CMimicsSpinBox::OnGetRange(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_GETRANGE, wParam, lParam) : FALSE);
}

LRESULT CMimicsSpinBox::OnSetAccel(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndSpinCtrl.GetSafeHwnd())) ? m_wndSpinCtrl.SendMessage(UDM_SETACCEL, wParam, lParam) : FALSE);
}

LRESULT CMimicsSpinBox::OnGetAccel(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndSpinCtrl.GetSafeHwnd())) ? m_wndSpinCtrl.SendMessage(UDM_GETACCEL, wParam, lParam) : FALSE);
}

LRESULT CMimicsSpinBox::OnSetSel(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_SETSEL, wParam, lParam) : FALSE);
}

LRESULT CMimicsSpinBox::OnGetSel(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_GETSEL, wParam, lParam) : FALSE);
}

LRESULT CMimicsSpinBox::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	LOGFONT  lfFont;

	for (m_cFont.DeleteObject(); GetObject((HGDIOBJ)wParam, sizeof(LOGFONT), &lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		m_wndEditCtrl.SetFont(&m_cFont, LOWORD(lParam));
		Invalidate(FALSE);
		UpdateWindow();
		break;
	}
	return FALSE;
}

LRESULT CMimicsSpinBox::OnGetFont(WPARAM wParam, LPARAM lParam)
{
	return((LRESULT)m_cFont.GetSafeHandle());
}

void CMimicsSpinBox::OnClose()
{
	GetParent()->SendMessage(WM_CLOSE);
}

void CMimicsSpinBox::OnDestroy()
{
	m_cFont.DeleteObject();
	CWnd::OnDestroy();
}

// MimicsSpinBox helpers
BOOL MimicsSpinbox_SetPos(CWnd *pCtrl, LONGLONG nPos)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETPOS, (WPARAM)NULL, (LPARAM)&nPos));
}

LONGLONG MimicsSpinbox_GetPos(CWnd *pCtrl)
{
	LONGLONG nPos;

	pCtrl->SendMessage(SBXM_GETPOS, TRUE, (LPARAM)&nPos);
	return nPos;
}

BOOL MimicsSpinbox_SetBase(CWnd *pCtrl, UINT nBase, UINT nDigits)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETBASE, nBase, nDigits));
}

BOOL MimicsSpinbox_GetBase(CWnd *pCtrl, UINT &nBase, UINT &nDigits)
{
	return((BOOL)pCtrl->SendMessage(SBXM_GETBASE, (WPARAM)&nBase, (LPARAM)&nDigits));
}

BOOL MimicsSpinbox_SetRange(CWnd *pCtrl, LONGLONG nMin, LONGLONG nMax)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETRANGE, (WPARAM)&nMin, (LPARAM)&nMax));
}

BOOL MimicsSpinbox_GetRange(CWnd *pCtrl, LONGLONG &nMin, LONGLONG &nMax)
{
	return((BOOL)pCtrl->SendMessage(SBXM_GETRANGE, (WPARAM)&nMin, (LPARAM)&nMax));
}

BOOL MimicsSpinbox_SetAccel(CWnd *pCtrl, INT nAccel, CONST UDACCEL *pAccel)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETACCEL, nAccel, (LPARAM)pAccel));
}

UINT MimicsSpinbox_GetAccel(CWnd *pCtrl, INT nAccel, UDACCEL *pAccel)
{
	return((UINT)pCtrl->SendMessage(SBXM_GETACCEL, nAccel, (LPARAM)pAccel));
}

BOOL MimicsSpinbox_SetSel(CWnd *pCtrl, INT nStartPos, INT nStopPos)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETSEL, nStartPos, nStopPos));
}

BOOL MimicsSpinbox_GetSel(CWnd *pCtrl, INT &nStartPos, INT &nStopPos)
{
	return((BOOL)pCtrl->SendMessage(SBXM_GETSEL, (WPARAM)&nStartPos, (LPARAM)&nStopPos));
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsSpinBox

IMPLEMENT_DYNCREATE(CResourceMimicsSpinBox, CMimicsSpinBox)

CResourceMimicsSpinBox::CResourceMimicsSpinBox(HWND hWnd) : CMimicsSpinBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsSpinBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsSpinBox  *pResourceSpinBox;

	if ((pResourceSpinBox = new CResourceMimicsSpinBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

void CResourceMimicsSpinBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsSpinBox, CMimicsSpinBox)
	//{{AFX_MSG_MAP(CResourceMimicsSpinBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsSpinBox message handlers

BOOL CResourceMimicsSpinBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG(((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LOWERCASE | ES_UPPERCASE | ES_NUMBER | ES_PASSWORD | ES_READONLY | ES_WANTRETURN))) ? NULL : NULL), HIWORD(lpCreateStruct->style)) | WS_CHILD));
	return CMimicsSpinBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsTimeSpinBox

IMPLEMENT_DYNCREATE(CMimicsTimeSpinBox, CWnd)

CMimicsTimeSpinBox::CMimicsTimeSpinBox() : CWnd()
{
	m_tTime = 1000000 * CTime::GetCurrentTime().GetTime();
	m_tStartTime = 0;
	m_tStopTime = 0;
	m_bState[0] = FALSE;
	m_bState[1] = FALSE;
	m_bVisible = TRUE;
}

BOOL CMimicsTimeSpinBox::Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle, LPCTSTR pszFormat, CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime)
{
	for (m_tStartTime = tStartTime, m_tStopTime = tStopTime; CWnd::Create((LPCTSTR)NULL, (AfxIsValidString(pszFormat)) ? pszFormat : EMPTYSTRING, MAKELONG((((m_dwStyle = LOWORD(dwStyle) & (TSBXS_ANY_TIME | TSBXS_PAST_TIME | TSBXS_FUTURE_TIME | TSBXS_UTC_TIME | TSBXS_SPAN_TIME | TSBXS_HIDE_TIME))) ? NULL : NULL), HIWORD(dwStyle)) | WS_CHILD, rect, pParentWnd, nID); ) return TRUE;
	return FALSE;
}

BOOL CMimicsTimeSpinBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass  *pClass;
	CMimicsTimeSpinBox  cTimeSpinBox;

	if ((pClass = cTimeSpinBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (szClass.Mid(cPos, 1) != szBaseClass.Mid(cPos, 1)) break;
			continue;
		}
		if (cPos < cbClassName  &&  !GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
		{
			sWndClass.lpszClassName = (LPCTSTR)szClass;
			sWndClass.lpfnWndProc = CResourceMimicsTimeSpinBox::WndProcHook;
			sWndClass.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
			sWndClass.cbClsExtra = 0;
			sWndClass.cbWndExtra = 0;
			sWndClass.hIcon = (HICON)NULL;
			sWndClass.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
			sWndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			sWndClass.lpszMenuName = (LPCTSTR)NULL;
			return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
		}
	}
	return TRUE;
}

BOOL CMimicsTimeSpinBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass  *pClass;
	CMimicsTimeSpinBox  cTimeSpinBox;

	if ((pClass = cTimeSpinBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CMimicsCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (szClass.Mid(cPos, 1) != szBaseClass.Mid(cPos, 1)) break;
			continue;
		}
		return((cPos < cbClassName) ? ::UnregisterClass(szClass.Mid(cPos), GetModuleHandle((LPCTSTR)NULL)) : FALSE);
	}
	return FALSE;
}

VOID CMimicsTimeSpinBox::EnableAutoCompletion(BOOL bEnable)
{
	INT  nCtrl;
	INT  nCtrls;
	CMimicsTextEdit  *pTextEditCtrl;
	CMimicsNumberEdit  *pNumberEditCtrl;

	for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pNumberEditCtrl = (IsSubFormatNumericalEditCtrl(m_nCtrlFormat.GetAt(nCtrl))) ? (CMimicsNumberEdit *)m_pwndEditCtrls.GetAt(nCtrl) : (CMimicsNumberEdit *)NULL))
		{
			pNumberEditCtrl->EnableAutoCompletion(bEnable);
			continue;
		}
		if ((pTextEditCtrl = (!IsSubFormatNumericalEditCtrl(m_nCtrlFormat.GetAt(nCtrl))) ? (CMimicsTextEdit *)m_pwndEditCtrls.GetAt(nCtrl) : (CMimicsTextEdit *)NULL))
		{
			pTextEditCtrl->EnableAutoCompletion(bEnable);
			continue;
		}
	}
}

BOOL CMimicsTimeSpinBox::IsAutoCompletionEnabled() CONST
{
	INT  nCtrl;
	INT  nCtrls;
	CMimicsTextEdit  *pTextEditCtrl;
	CMimicsNumberEdit  *pNumberEditCtrl;

	for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pNumberEditCtrl = (IsSubFormatNumericalEditCtrl(m_nCtrlFormat.GetAt(nCtrl))) ? (CMimicsNumberEdit *)m_pwndEditCtrls.GetAt(nCtrl) : (CMimicsNumberEdit *)NULL))
		{
			if (pNumberEditCtrl->IsAutoCompletionEnabled()) break;
			continue;
		}
		if ((pTextEditCtrl = (!IsSubFormatNumericalEditCtrl(m_nCtrlFormat.GetAt(nCtrl))) ? (CMimicsTextEdit *)m_pwndEditCtrls.GetAt(nCtrl) : (CMimicsTextEdit *)NULL))
		{
			if (pTextEditCtrl->IsAutoCompletionEnabled()) break;
			continue;
		}
	}
	return(nCtrl < nCtrls);
}

INT CMimicsTimeSpinBox::TranslateSubFormat(LPCTSTR pszFormat) CONST
{
	INT  nSubFormatID;
	CString  szFormat(pszFormat);

	for (nSubFormatID = MINTIMETAGSUBFORMAT; nSubFormatID <= MAXTIMETAGSUBFORMAT; nSubFormatID++)
	{
		if (!szFormat.Find(STRING(nSubFormatID))) break;
		continue;
	}
	return((nSubFormatID <= MAXTIMETAGSUBFORMAT) ? nSubFormatID : -1);
}

BOOL CMimicsTimeSpinBox::TranslateSubFormatDelimiter(LPCTSTR pszFormat, CString &szDelimiter) CONST
{
	CString  szFormat(pszFormat);

	for (szDelimiter.Empty(); !szFormat.IsEmpty() && TranslateSubFormat(szFormat) < 0; szFormat = szFormat.Mid(1))
	{
		szDelimiter += szFormat.Left(1);
		continue;
	}
	return !szDelimiter.IsEmpty();
}

BOOL CMimicsTimeSpinBox::TranslateSubFormatPosition(LPCTSTR pszFormat, CONST RECT &rect, CRect &rSubFormat)
{
	CDC  *pDC;
	INT  nWidth;
	INT  nSubFormat;
	INT  nSubFormats;
	INT  nSubFormatID;
	CFont  *pOldFont;
	CRect  rTimeSpinBox;
	CSize  sizeSubFormat[2];
	CStringArray  szSubFormats;
	CStringTools  cStringTools;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			for (; IsSubFormatDelimiterCtrl((nSubFormatID = TranslateSubFormat(pszFormat))); )
			{
				sizeSubFormat[0] = pDC->GetTextExtent(pszFormat);
				break;
			}
			if (IsSubFormatNumericalEditCtrl(nSubFormatID))
			{
				sizeSubFormat[0] = pDC->GetTextExtent(cStringTools.ConvertIntToString(TIMESPINBOXLOWLIMIT(EnumSubFormatLimits(nSubFormatID))));
				sizeSubFormat[1] = pDC->GetTextExtent(cStringTools.ConvertIntToString(TIMESPINBOXHIGHLIMIT(EnumSubFormatLimits(nSubFormatID))));
				sizeSubFormat[0].cx = max(sizeSubFormat[0].cx, sizeSubFormat[1].cx);
				sizeSubFormat[0].cy = max(sizeSubFormat[0].cy, sizeSubFormat[1].cy);
			}
			for (nSubFormat = 0, nSubFormats = (IsSubFormatEditCtrl(nSubFormatID)) ? EnumSubFormatLimits(nSubFormatID, szSubFormats) : 0, nWidth = 0; nSubFormat < nSubFormats; nSubFormat++, sizeSubFormat[0].cx = nWidth = max(sizeSubFormat[0].cx, nWidth))
			{
				sizeSubFormat[0] = pDC->GetTextExtent(szSubFormats.GetAt(nSubFormat));
				continue;
			}
			GetClientRect(rTimeSpinBox);
			sizeSubFormat[0].cx += GetSystemMetrics(SM_CXBORDER);
			sizeSubFormat[0].cy += GetSystemMetrics(SM_CYBORDER);
			rSubFormat.SetRect(0, (rTimeSpinBox.Height() - sizeSubFormat[0].cy) / 2, sizeSubFormat[0].cx, (rTimeSpinBox.Height() - sizeSubFormat[0].cy) / 2 + sizeSubFormat[0].cy);
			rSubFormat.OffsetRect(rect.right, 0);
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return TRUE;
		}
		ReleaseDC(pDC);
	}
	return FALSE;
}

LONGLONG CMimicsTimeSpinBox::EnumSubFormatLimits(INT nSubFormatID) CONST
{
	INT  nLimits[3];
	BOOL  bSubFormatIDs[6];

	if (m_dwStyle & TSBXS_SPAN_TIME)
	{
		if (IsTimespanSubFormatID(nSubFormatID))
		{
			for (nLimits[0] = m_tTime.EnumSubFormatLimits(nSubFormatID, (m_dwStyle & TSBXS_UTC_TIME) ? TRUE : FALSE), bSubFormatIDs[0] = IsExistingSubFormatID(IDS_TIMEKEY_SUBFORMAT_DAYS), bSubFormatIDs[1] = IsExistingSubFormatID(IDS_TIMEKEY_SUBFORMAT_HOUR), bSubFormatIDs[2] = IsExistingSubFormatID(IDS_TIMEKEY_SUBFORMAT_MINUTE), bSubFormatIDs[3] = IsExistingSubFormatID(IDS_TIMEKEY_SUBFORMAT_SECOND), bSubFormatIDs[4] = IsExistingSubFormatID(IDS_TIMEKEY_SUBFORMAT_MILLISECOND), bSubFormatIDs[5] = IsExistingSubFormatID(IDS_TIMEKEY_SUBFORMAT_MICROSECOND); nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYS; )
			{
				nLimits[1] = (INT)((m_tStartTime.GetTime() / 1000000) / SECONDSPERDAY);
				nLimits[2] = (INT)((m_tStopTime.GetTime() / 1000000) / SECONDSPERDAY);
				break;
			}
			if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_HOUR)
			{
				nLimits[1] = (!bSubFormatIDs[0] && m_tStartTime < 0) ? min((INT)max((m_tStartTime.GetTime() / (1000000 * (TIMETAG)SECONDSPERHOUR)), -(TIMETAG)HIWORD(nLimits[0])), (INT)HIWORD(nLimits[0])) : (INT)LOWORD(nLimits[0]);
				nLimits[2] = (!bSubFormatIDs[0] && m_tStartTime < 0) ? max((INT)min((m_tStopTime.GetTime() / (1000000 * (TIMETAG)SECONDSPERHOUR)), (TIMETAG)HIWORD(nLimits[0])), -(INT)HIWORD(nLimits[0])) : (INT)HIWORD(nLimits[0]);
			}
			if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MINUTE)
			{
				nLimits[1] = (!bSubFormatIDs[0] && !bSubFormatIDs[1] && m_tStartTime < 0) ? min((INT)max((m_tStartTime.GetTime() / (1000000 * (TIMETAG)SECONDSPERMINUTE)), -(TIMETAG)HIWORD(nLimits[0])), (INT)HIWORD(nLimits[0])) : (INT)LOWORD(nLimits[0]);
				nLimits[2] = (!bSubFormatIDs[0] && !bSubFormatIDs[1] && m_tStartTime < 0) ? max((INT)min((m_tStopTime.GetTime() / (1000000 * (TIMETAG)SECONDSPERMINUTE)), (TIMETAG)HIWORD(nLimits[0])), -(INT)HIWORD(nLimits[0])) : (INT)HIWORD(nLimits[0]);
			}
			if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_SECOND)
			{
				nLimits[1] = (!bSubFormatIDs[0] && !bSubFormatIDs[1] && !bSubFormatIDs[2] && m_tStartTime < 0) ? min((INT)max((m_tStartTime.GetTime() / 1000000), -(TIMETAG)HIWORD(nLimits[0])), (INT)HIWORD(nLimits[0])) : (INT)LOWORD(nLimits[0]);
				nLimits[2] = (!bSubFormatIDs[0] && !bSubFormatIDs[1] && !bSubFormatIDs[2] && m_tStartTime < 0) ? max((INT)min((m_tStopTime.GetTime() / 1000000), (TIMETAG)HIWORD(nLimits[0])), -(INT)HIWORD(nLimits[0])) : (INT)HIWORD(nLimits[0]);
			}
			if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MILLISECOND)
			{
				nLimits[1] = (!bSubFormatIDs[0] && !bSubFormatIDs[1] && !bSubFormatIDs[2] && !bSubFormatIDs[3] && m_tStartTime < 0) ? min((INT)max((m_tStartTime.GetTime() / 1000), -(TIMETAG)HIWORD(nLimits[0])), (INT)HIWORD(nLimits[0])) : (INT)LOWORD(nLimits[0]);
				nLimits[2] = (!bSubFormatIDs[0] && !bSubFormatIDs[1] && !bSubFormatIDs[2] && !bSubFormatIDs[3] && m_tStartTime < 0) ? max((INT)min((m_tStopTime.GetTime() / 1000), (TIMETAG)HIWORD(nLimits[0])), -(INT)HIWORD(nLimits[0])) : (INT)HIWORD(nLimits[0]);
			}
			if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MICROSECOND)
			{
				nLimits[1] = (!bSubFormatIDs[0] && !bSubFormatIDs[1] && !bSubFormatIDs[2] && !bSubFormatIDs[3] && !bSubFormatIDs[4] && m_tStartTime < 0) ? min((INT)max(m_tStartTime.GetTime(), -(TIMETAG)HIWORD(nLimits[0])), (INT)HIWORD(nLimits[0])) : (INT)LOWORD(nLimits[0]);
				nLimits[2] = (!bSubFormatIDs[0] && !bSubFormatIDs[1] && !bSubFormatIDs[2] && !bSubFormatIDs[3] && !bSubFormatIDs[4] && m_tStartTime < 0) ? max((INT)min(m_tStopTime.GetTime(), (TIMETAG)HIWORD(nLimits[0])), -(INT)HIWORD(nLimits[0])) : (INT)HIWORD(nLimits[0]);
			}
			return MAKETIMESPINBOXLIMITS(nLimits[1], nLimits[2]);
		}
	}
	return MAKETIMESPINBOXLIMITS(LOWORD(m_tTime.EnumSubFormatLimits(nSubFormatID, (m_dwStyle & TSBXS_UTC_TIME) ? TRUE : FALSE)), HIWORD(m_tTime.EnumSubFormatLimits(nSubFormatID, (m_dwStyle & TSBXS_UTC_TIME) ? TRUE : FALSE)));
}
INT CMimicsTimeSpinBox::EnumSubFormatLimits(INT nSubFormatID, CStringArray &szNames) CONST
{
	return m_tTime.EnumSubFormatLimits(nSubFormatID, szNames, (m_dwStyle & TSBXS_UTC_TIME) ? TRUE : FALSE);
}

BOOL CMimicsTimeSpinBox::ShowSubControls(BOOL bShow)
{
	INT  nCtrl[2];
	INT  nCtrls[2];
	CWnd  *pCtrl[2];

	if (m_dwStyle & TSBXS_HIDE_TIME)
	{
		for (nCtrl[0] = 0, nCtrls[0] = (m_bVisible != bShow) ? (INT)m_pwndEditCtrls.GetSize() : 0; nCtrl[0] < nCtrls[0]; nCtrl[0]++)
		{
			if ((pCtrl[0] = (CWnd *)m_pwndEditCtrls.GetAt(nCtrl[0])))
			{
				pCtrl[0]->ShowWindow((bShow) ? SW_SHOWNA : SW_HIDE);
				continue;
			}
			break;
		}
		for (nCtrl[1] = 0, nCtrls[1] = (m_bVisible != bShow) ? (INT)m_pwndStaticCtrls.GetSize() : 0; nCtrl[1] < nCtrls[1]; nCtrl[1]++)
		{
			if ((pCtrl[1] = (CWnd *)m_pwndStaticCtrls.GetAt(nCtrl[1])))
			{
				pCtrl[1]->ShowWindow((bShow) ? SW_SHOWNA : SW_HIDE);
				continue;
			}
			break;
		}
		if (nCtrl[0] == nCtrls[0] && nCtrl[1] == nCtrls[1] && nCtrls[0] > 0 && nCtrls[1] > 0)
		{
			for (m_bVisible = bShow; bShow; )
			{
				SetTime(m_tTime);
				break;
			}
			GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), TSBXN_CHANGE), (LPARAM)GetSafeHwnd());
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMimicsTimeSpinBox::IsSubFormatNumericalEditCtrl(INT nSubFormatID) CONST
{
	return((!IsSubFormatDelimiterCtrl(nSubFormatID) && !IsSubFormatEditCtrl(nSubFormatID)) ? TRUE : FALSE);
}

BOOL CMimicsTimeSpinBox::IsSubFormatEditCtrl(INT nSubFormatID) CONST
{
	CStringArray  szSubFormats;

	return((!IsSubFormatDelimiterCtrl(nSubFormatID) && EnumSubFormatLimits(nSubFormatID, szSubFormats)) ? TRUE : FALSE);
}

BOOL CMimicsTimeSpinBox::IsSubFormatDelimiterCtrl(INT nSubFormatID) CONST
{
	return((nSubFormatID < 0) ? TRUE : FALSE);
}

BOOL CMimicsTimeSpinBox::IsTimespanSubFormatID(INT nSubFormatID, BOOL bRightAligned) CONST
{
	return((nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYS || ((nSubFormatID == IDS_TIMEKEY_SUBFORMAT_HOUR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MINUTE || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_SECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MILLISECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MICROSECOND) && !bRightAligned)) ? TRUE : FALSE);
}

BOOL CMimicsTimeSpinBox::IsExistingSubFormatID(INT nSubFormatID) CONST
{
	INT  nID;
	INT  nIDs;

	for (nID = 0, nIDs = (INT)m_nCtrlFormat.GetSize(); nID < nIDs; nID++)
	{
		if (m_nCtrlFormat.GetAt(nID) == nSubFormatID) break;
		continue;
	}
	return((nID < nIDs) ? TRUE : FALSE);
}

void CMimicsTimeSpinBox::UpdateUI()
{
	if (IsThemeActive())
	{
		if (!m_bState[1])
		{
			SetTimer(TIMESPINBOX_UI_TIMERID, TIMESPINBOX_UI_TIMEOUT, NULL);
			m_bState[1] = TRUE;
			RedrawWindow();
		}
	}
}
void CMimicsTimeSpinBox::UpdateUI(CONST POINT &point)
{
	BOOL  bState;
	CRect  rSpinBox;

	if (IsThemeActive())
	{
		for (bState = m_bState[1], GetClientRect(rSpinBox); rSpinBox.PtInRect(point); )
		{
			if (!m_bState[1]) SetTimer(TIMESPINBOX_UI_TIMERID, TIMESPINBOX_UI_TIMEOUT, NULL);
			m_bState[1] = TRUE;
			break;
		}
		if (!rSpinBox.PtInRect(point))
		{
			if (m_bState[1]) KillTimer(TIMESPINBOX_UI_TIMERID);
			m_bState[1] = FALSE;
		}
		if (m_bState[1] != bState) RedrawWindow();
	}
}

INT CMimicsTimeSpinBox::CalcIndent()
{
	CDC  *pDC;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			pDC->GetTextMetrics(&tmFont);
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return tmFont.tmAveCharWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CMimicsTimeSpinBox, CWnd)
	//{{AFX_MSG_MAP(CMimicsTimeSpinBox)
	ON_WM_CREATE()
	ON_WM_NCCREATE()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_MESSAGE(TSBXM_SETTIME, OnSetTime)
	ON_MESSAGE(TSBXM_GETTIME, OnGetTime)
	ON_MESSAGE(TSBXM_SETRANGE, OnSetRange)
	ON_MESSAGE(TSBXM_GETRANGE, OnGetRange)
	ON_MESSAGE(TSBXM_SETSEL, OnSetSel)
	ON_MESSAGE(TSBXM_GETSEL, OnGetSel)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_MESSAGE(WM_GETFONT, OnGetFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsTimeSpinBox message handlers

int CMimicsTimeSpinBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT  nCtrlID;
	INT  nSubFormatID;
	BOOL  bFirstCtrl;
	CRect  rSubCtrl;
	CRect  rEditCtrl;
	CRect  rSpinCtrl;
	CRect  rStaticCtrl;
	CEdit  *pEditCtrl;
	CString  szDelimiter;
	CString  szTimeFormat;
	CStatic  *pStaticCtrl;
	CMimicsTextEdit  *pTextEditCtrl;
	CMimicsNumberEdit  *pNumberEditCtrl;

	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		if (m_tStartTime == 0 && m_tStopTime == 0)
		{
			m_tStartTime = (m_dwStyle & TSBXS_SPAN_TIME) ? -MIN_TIMETAG : MIN_TIMETAG;
			m_tStopTime = (m_dwStyle & TSBXS_SPAN_TIME) ? MIN_TIMETAG : MAX_TIMETAG;
		}
		if (m_wndSpinCtrl.Create(UDS_NOTHOUSANDS | ((IsWindowEnabled()) ? (WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) : (WS_CHILD | WS_CLIPSIBLINGS | WS_DISABLED | WS_VISIBLE)), CRect(0, 0, 0, 0), this, 0))
		{
			for (GetWindowText(szTimeFormat), SetWindowText((szTimeFormat = (szTimeFormat.IsEmpty()) ? STRING(IDS_TIMEKEY_FORMAT) : (LPCTSTR)szTimeFormat)), SetFont(CMimicsCustomControls::GetCustomControlFont(this)), rSubCtrl.SetRect(CalcIndent(), 0, CalcIndent(), 0), nCtrlID = m_wndSpinCtrl.GetDlgCtrlID() + 1, bFirstCtrl = TRUE; !szTimeFormat.IsEmpty(); )
			{
				if ((nSubFormatID = TranslateSubFormat(szTimeFormat)) >= 0 && TranslateSubFormatPosition(STRING(nSubFormatID), rSubCtrl, rEditCtrl))
				{
					if (IsSubFormatNumericalEditCtrl(nSubFormatID))
					{
						if ((pNumberEditCtrl = new CMimicsNumberEdit))
						{
							if (pNumberEditCtrl->Create(this, rEditCtrl, nCtrlID, ((!IsTimespanSubFormatID(nSubFormatID, TRUE)) ? ES_LEFT : ES_RIGHT) | ((IsWindowEnabled()) ? (WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) : (WS_CHILD | WS_CLIPSIBLINGS)) | (lpCreateStruct->style & WS_TABSTOP), (m_tStartTime < 0) ? bFirstCtrl : FALSE))
							{
								szTimeFormat = szTimeFormat.Mid(lstrlen(STRING(nSubFormatID)));
								pNumberEditCtrl->SetFont(GetFont());
								m_pwndEditCtrls.Add(pNumberEditCtrl);
								m_nCtrlFormat.Add(nSubFormatID);
								rSubCtrl = rEditCtrl;
								bFirstCtrl = FALSE;
								nCtrlID++;
								continue;
							}
							delete pNumberEditCtrl;
						}
						break;
					}
					if (IsSubFormatEditCtrl(nSubFormatID))
					{
						if ((pTextEditCtrl = new CMimicsTextEdit))
						{
							if (pTextEditCtrl->Create(this, rEditCtrl, nCtrlID, ES_LEFT | ((IsWindowEnabled()) ? (WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) : (WS_CHILD | WS_CLIPSIBLINGS)) | (lpCreateStruct->style & WS_TABSTOP)))
							{
								szTimeFormat = szTimeFormat.Mid(lstrlen(STRING(nSubFormatID)));
								pTextEditCtrl->SetFont(GetFont());
								m_pwndEditCtrls.Add(pTextEditCtrl);
								m_nCtrlFormat.Add(nSubFormatID);
								rSubCtrl = rEditCtrl;
								nCtrlID++;
								continue;
							}
							delete pTextEditCtrl;
						}
					}
					break;
				}
				if ((pStaticCtrl = (TranslateSubFormatDelimiter(szTimeFormat, szDelimiter) && TranslateSubFormatPosition(szDelimiter, rSubCtrl, rStaticCtrl)) ? new CStatic : (CStatic *)NULL))
				{
					if (pStaticCtrl->Create(szDelimiter, SS_SIMPLE | ((IsWindowEnabled()) ? (WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) : (WS_CHILD | WS_CLIPSIBLINGS)), rStaticCtrl, this))
					{
						szTimeFormat = szTimeFormat.Mid(szDelimiter.GetLength());
						pStaticCtrl->SetFont(GetFont());
						m_pwndStaticCtrls.Add(pStaticCtrl);
						rSubCtrl = rStaticCtrl;
						continue;
					}
					delete pStaticCtrl;
				}
				break;
			}
			if (szTimeFormat.IsEmpty())
			{
				for (rSpinCtrl.SetRect(lpCreateStruct->cx - 3 * lpCreateStruct->cy / 4 + (3 * lpCreateStruct->cy / 4) % 2, 0, lpCreateStruct->cx, lpCreateStruct->cy); (GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_CLIENTEDGE) != WS_EX_CLIENTEDGE; )
				{
					rSpinCtrl.DeflateRect(0, GetSystemMetrics(SM_CYBORDER));
					rSpinCtrl.OffsetRect(-GetSystemMetrics(SM_CXBORDER), 0);
					break;
				}
				m_wndSpinCtrl.MoveWindow(rSpinCtrl);
				SetTime();
				return 0;
			}
			for (; m_pwndEditCtrls.GetSize() > 0; m_pwndEditCtrls.RemoveAt(0))
			{
				if ((pEditCtrl = (CEdit *)m_pwndEditCtrls.GetAt(0)))
				{
					pEditCtrl->DestroyWindow();
					delete pEditCtrl;
				}
			}
			for (; m_pwndStaticCtrls.GetSize() > 0; m_pwndStaticCtrls.RemoveAt(0))
			{
				if ((pStaticCtrl = (CStatic *)m_pwndStaticCtrls.GetAt(0)))
				{
					pStaticCtrl->DestroyWindow();
					delete pStaticCtrl;
				}
			}
			m_wndSpinCtrl.DestroyWindow();
		}
	}
	return -1;
}

BOOL CMimicsTimeSpinBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	for (SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~WS_BORDER); !IsThemeActive(); )
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_CLIENTEDGE);
		break;
	}
	return CWnd::OnNcCreate(lpCreateStruct);
}

void CMimicsTimeSpinBox::OnSize(UINT nType, int cx, int cy)
{
	INT  nCtrl;
	INT  nCtrls;
	CRect  rEditCtrl;
	CRect  rSpinCtrl;
	CRect  rStaticCtrl;
	CEdit  *pEditCtrl;
	CStatic  *pStaticCtrl;

	if (IsWindow(m_wndSpinCtrl.GetSafeHwnd()))
	{
		for (m_wndSpinCtrl.GetWindowRect(rSpinCtrl), rSpinCtrl.SetRect(cx - rSpinCtrl.Width(), 0, cx, cy); (GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_CLIENTEDGE) != WS_EX_CLIENTEDGE; )
		{
			rSpinCtrl.DeflateRect(0, GetSystemMetrics(SM_CYBORDER));
			rSpinCtrl.OffsetRect(-GetSystemMetrics(SM_CXBORDER), 0);
			break;
		}
		m_wndSpinCtrl.MoveWindow(rSpinCtrl);
	}
	for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pEditCtrl = (CEdit *)m_pwndEditCtrls.GetAt(nCtrl)))
		{
			pEditCtrl->GetWindowRect(rEditCtrl);
			ScreenToClient(rEditCtrl);
			rEditCtrl.SetRect(rEditCtrl.left, (cy - rEditCtrl.Height()) / 2, rEditCtrl.right, (cy - rEditCtrl.Height()) / 2 + rEditCtrl.Height());
			pEditCtrl->MoveWindow(rEditCtrl);
		}
	}
	for (nCtrl = 0, nCtrls = (INT)m_pwndStaticCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pStaticCtrl = (CStatic *)m_pwndStaticCtrls.GetAt(nCtrl)))
		{
			pStaticCtrl->GetWindowRect(rStaticCtrl);
			ScreenToClient(rStaticCtrl);
			rStaticCtrl.SetRect(rStaticCtrl.left, (cy - rStaticCtrl.Height()) / 2, rStaticCtrl.right, (cy - rStaticCtrl.Height()) / 2 + rStaticCtrl.Height());
			pStaticCtrl->MoveWindow(rStaticCtrl);
		}
	}
	CWnd::OnSize(nType, cx, cy);
}

HBRUSH CMimicsTimeSpinBox::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	return((IsWindowEnabled() && nCtlColor == CTLCOLOR_STATIC) ? (HBRUSH)GetParent()->SendMessage(WM_CTLCOLOREDIT, (WPARAM)pDC->GetSafeHdc(), (LPARAM)pWnd->GetSafeHwnd()) : CWnd::OnCtlColor(pDC, pWnd, nCtlColor));
}

BOOL CMimicsTimeSpinBox::OnEraseBkgnd(CDC *pDC)
{
	HTHEME  hTheme;
	CBrush  cBkgndBrush;
	CRect  rTimeSpinBox;

	for (GetClientRect(rTimeSpinBox); (hTheme = (IsThemeActive()) ? OpenThemeData(GetSafeHwnd(), VSCLASS_EDIT) : (HTHEME)NULL); )
	{
		DrawThemeBackground(hTheme, pDC->GetSafeHdc(), EP_EDITBORDER_NOSCROLL, (IsWindowEnabled()) ? ((m_bState[0]) ? EPSN_FOCUSED : ((m_bState[1]) ? EPSN_HOT : EPSN_NORMAL)) : EPSN_DISABLED, rTimeSpinBox, (LPCRECT)NULL);
		CloseThemeData(hTheme);
		return TRUE;
	}
	if (cBkgndBrush.Attach((HBRUSH)SendMessage(WM_CTLCOLORSTATIC, (WPARAM)pDC->GetSafeHdc(), (LPARAM)GetSafeHwnd())))
	{
		pDC->FillRect(rTimeSpinBox, &cBkgndBrush);
		cBkgndBrush.Detach();
		return TRUE;
	}
	return CWnd::OnEraseBkgnd(pDC);
}

void CMimicsTimeSpinBox::OnEnable(BOOL bEnable)
{
	INT  nCtrl;
	INT  nCtrls;
	CEdit  *pEditCtrl;
	CStatic  *pStaticCtrl;

	for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(), Invalidate(TRUE); nCtrl < nCtrls; nCtrl++)
	{
		if ((pEditCtrl = (CEdit *)m_pwndEditCtrls.GetAt(nCtrl)))
		{
			pEditCtrl->ShowWindow((bEnable) ? SW_SHOWNA : SW_HIDE);
			continue;
		}
	}
	for (nCtrl = 0, nCtrls = (INT)m_pwndStaticCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pStaticCtrl = (CStatic *)m_pwndStaticCtrls.GetAt(nCtrl)))
		{
			pStaticCtrl->ShowWindow((bEnable) ? SW_SHOWNA : SW_HIDE);
			continue;
		}
	}
	m_wndSpinCtrl.EnableWindow(bEnable);
	CWnd::OnEnable(bEnable);
}

void CMimicsTimeSpinBox::OnMouseMove(UINT nFlags, CPoint point)
{
	UpdateUI(point);
	CWnd::OnMouseMove(nFlags, point);
}

void CMimicsTimeSpinBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_bVisible) SetFocus();
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CMimicsTimeSpinBox::OnSetFocus(CWnd *pOldWnd)
{
	CEdit  *pEditCtrl;

	for (ShowSubControls(); (pEditCtrl = (m_pwndEditCtrls.GetSize() > 0) ? (CEdit *)m_pwndEditCtrls.GetAt(0) : (CEdit *)NULL); )
	{
		pEditCtrl->SetSel(0, -1);
		pEditCtrl->SetFocus();
		break;
	}
}

void CMimicsTimeSpinBox::OnTimer(UINT_PTR nTimerID)
{
	POINT  ptCursor;

	if (nTimerID == TIMESPINBOX_UI_TIMERID)
	{
		GetCursorPos(&ptCursor);
		ScreenToClient(&ptCursor);
		UpdateUI(ptCursor);
	}
	CWnd::OnTimer(nTimerID);
}

BOOL CMimicsTimeSpinBox::OnCommand(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	CWnd  *pCtrl;
	CTimeTag  tTime;

	if (HIWORD(wParam) == EN_SETFOCUS)
	{
		for (GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), TSBXN_SETFOCUS), (LPARAM)GetSafeHwnd()), m_bState[0] = TRUE; IsThemeActive(); )
		{
			RedrawWindow();
			break;
		}
		return TRUE;
	}
	if (HIWORD(wParam) == EN_KILLFOCUS)
	{
		if (CWnd::GetFocus() != this  &&  !IsChild(CWnd::GetFocus()))
		{
			for (GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), TSBXN_KILLFOCUS), (LPARAM)GetSafeHwnd()), m_bState[0] = FALSE; IsThemeActive(); )
			{
				RedrawWindow();
				break;
			}
			for (nCtrl = 0, nCtrls = ((m_dwStyle & TSBXS_HIDE_TIME) && m_bVisible) ? (INT)m_pwndEditCtrls.GetSize() : 0; nCtrl < nCtrls; nCtrl++)
			{
				if ((pCtrl = (CWnd *)m_pwndEditCtrls.GetAt(nCtrl)))
				{
					if (!pCtrl->GetWindowTextLength())
					{
						ShowSubControls(FALSE);
						break;
					}
				}
			}
			return TRUE;
		}
		if (!GetTime(tTime)) SetTime(m_tTime);
		return TRUE;
	}
	if (HIWORD(wParam) == EN_CHANGE)
	{
		GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), TSBXN_CHANGE), (LPARAM)GetSafeHwnd());
		return TRUE;
	}
	if (HIWORD(wParam) == EN_UPDATE)
	{
		GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), TSBXN_UPDATE), (LPARAM)GetSafeHwnd());
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsTimeSpinBox::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nCtrl;
	INT  nCtrls;
	INT  nFormat;
	CEdit  *pEditCtrl;
	CMimicsTextEdit  *pTextEditCtrl;
	CMimicsNumberEdit  *pNumberEditCtrl;
	NMUPDOWN  *pNotifyInfo = (NMUPDOWN *)lParam;

	if (pNotifyInfo->hdr.code == UDN_DELTAPOS)
	{
		for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(), ShowSubControls(); nCtrl < nCtrls; nCtrl++)
		{
			if (!CWnd::GetFocus() || !IsChild(CWnd::GetFocus()))
			{
				if ((pEditCtrl = (CEdit *)m_pwndEditCtrls.GetAt(0)))
				{
					pEditCtrl->SetSel(0, -1);
					pEditCtrl->SetFocus();
				}
			}
			if (IsSubFormatNumericalEditCtrl((nFormat = m_nCtrlFormat.GetAt(nCtrl))))
			{
				if ((pNumberEditCtrl = (CMimicsNumberEdit *)m_pwndEditCtrls.GetAt(nCtrl)) && CWnd::GetFocus() == (CWnd *)pNumberEditCtrl)
				{
					pNumberEditCtrl->SetPos(pNumberEditCtrl->GetPos() - pNotifyInfo->iDelta, TRUE);
					pNumberEditCtrl->SetSel(0, -1);
					pNumberEditCtrl->SetFocus();
					break;
				}
				continue;
			}
			if ((pTextEditCtrl = (CMimicsTextEdit *)m_pwndEditCtrls.GetAt(nCtrl)) && CWnd::GetFocus() == (CWnd *)pTextEditCtrl)
			{
				pTextEditCtrl->SetPos(pTextEditCtrl->GetPos() - pNotifyInfo->iDelta, TRUE);
				pTextEditCtrl->SetSel(0, -1);
				pTextEditCtrl->SetFocus();
				break;
			}
		}
		return TRUE;
	}
	return FALSE;
}

LRESULT CMimicsTimeSpinBox::OnSetTime(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	INT  nLimits[2];
	INT  nSubFormatID;
	BOOL  bFirstSubFormat;
	CString  szNumber;
	TIMETAG  tTime[2];
	CTimeTag  tTimeTag;
	CMimicsTextEdit  *pTextEditCtrl;
	CMimicsNumberEdit  *pNumberEditCtrl;
	CStringArray  szCtrlFormatNames;
	CStringTools  cStringTools;

	for (CopyMemory(&tTime[0], (LPCVOID)lParam, sizeof(tTime[0])), ShowSubControls(((m_dwStyle & TSBXS_SPAN_TIME) || tTime[0] > 0) ? TRUE : FALSE), tTime[0] = ((m_dwStyle & TSBXS_SPAN_TIME) == 0) ? abs(tTime[0]) : ((!wParam) ? tTime[0] : 0), tTime[1] = tTimeTag.GetTime(), tTime[0] = ((m_dwStyle & TSBXS_SPAN_TIME) == 0 && !tTime[0]) ? tTime[1] : tTime[0]; m_dwStyle & TSBXS_PAST_TIME; )
	{
		tTime[0] = (tTime[0] > 0) ? ((tTime[0] > tTime[1]) ? tTime[1] : tTime[0]) : tTime[0];
		break;
	}
	for (; m_dwStyle & TSBXS_FUTURE_TIME; )
	{
		tTime[0] = (tTime[0] > 0) ? ((tTime[0] < tTime[1]) ? tTime[1] : tTime[0]) : tTime[0];
		break;
	}
	if (m_tStartTime < m_tStopTime)
	{
		tTime[0] = (tTime[0] < m_tStartTime.GetTime()) ? m_tStartTime.GetTime() : tTime[0];
		tTime[0] = (tTime[0] > m_tStopTime.GetTime()) ? m_tStopTime.GetTime() : tTime[0];
	}
	for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(), m_tTime = tTime[0], bFirstSubFormat = TRUE; nCtrl < nCtrls; nCtrl++)
	{
		if (IsSubFormatNumericalEditCtrl((nSubFormatID = m_nCtrlFormat.GetAt(nCtrl))))
		{
			if ((pNumberEditCtrl = (CMimicsNumberEdit *)m_pwndEditCtrls.GetAt(nCtrl)))
			{
				nLimits[0] = TIMESPINBOXLOWLIMIT(EnumSubFormatLimits(nSubFormatID));
				nLimits[1] = TIMESPINBOXHIGHLIMIT(EnumSubFormatLimits(nSubFormatID));
				szNumber = (m_dwStyle & (TSBXS_UTC_TIME | TSBXS_SPAN_TIME)) ? CTimeTag((!bFirstSubFormat) ? abs(tTime[0]) : tTime[0]).FormatGmt(nSubFormatID) : CTimeTag((!bFirstSubFormat) ? abs(tTime[0]) : tTime[0]).Format(nSubFormatID);
				pNumberEditCtrl->SetBase(10, (!IsTimespanSubFormatID(nSubFormatID, TRUE)) ? max(cStringTools.ConvertIntToString(nLimits[0]).GetLength(), cStringTools.ConvertIntToString(nLimits[1]).GetLength()) : 0);
				pNumberEditCtrl->SetRange(nLimits[0], nLimits[1]);
				pNumberEditCtrl->SetWindowText(szNumber);
				bFirstSubFormat = FALSE;
				continue;
			}
		}
		if ((pTextEditCtrl = (CMimicsTextEdit *)m_pwndEditCtrls.GetAt(nCtrl)))
		{
			for (EnumSubFormatLimits(nSubFormatID, szCtrlFormatNames), pTextEditCtrl->ResetText(); szCtrlFormatNames.GetSize() > 0; szCtrlFormatNames.RemoveAt(0))
			{
				pTextEditCtrl->AddText(szCtrlFormatNames.GetAt(0));
				continue;
			}
			pTextEditCtrl->SetWindowText((m_dwStyle & TSBXS_UTC_TIME) ? m_tTime.FormatGmt(nSubFormatID) : m_tTime.Format(nSubFormatID));
			pTextEditCtrl->SetSel(0, -1);
		}
	}
	return 0;
}

LRESULT CMimicsTimeSpinBox::OnGetTime(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	INT  nDays;
	INT  nHour;
	INT  nMinute;
	INT  nSecond;
	INT  nSubFormatID;
	INT  nMilliseconds;
	INT  nMicroseconds;
	WORD  wMicroseconds;
	BOOL  bCorrection;
	BOOL  bMinusZero;
	TIMETAG  tTime[2];
	SYSTEMTIME  tFlagTime;
	SYSTEMTIME  tActualTime;
	CMimicsNumberEdit  *pNumberEditCtrl;
	CMimicsTextEdit  *pTextEditCtrl;

	for (nSubFormatID = (!m_bVisible) ? (MAXTIMETAGSUBFORMAT + 1) : MINTIMETAGSUBFORMAT, tActualTime.wYear = m_tTime.GetYear(), tActualTime.wMonth = m_tTime.GetMonth(), tActualTime.wDayOfWeek = m_tTime.GetDayOfWeek() - 1, tActualTime.wDay = m_tTime.GetDay(), tActualTime.wHour = m_tTime.GetHour(), tActualTime.wMinute = m_tTime.GetMinute(), tActualTime.wSecond = m_tTime.GetSecond(), tActualTime.wMilliseconds = m_tTime.GetMilliSeconds(), tFlagTime.wYear = (WORD)-1, tFlagTime.wMonth = (WORD)-1, tFlagTime.wDayOfWeek = (WORD)-1, tFlagTime.wDay = (WORD)-1, tFlagTime.wHour = (WORD)-1, tFlagTime.wMinute = (WORD)-1, tFlagTime.wSecond = (WORD)-1, tFlagTime.wMilliseconds = (WORD)-1, wMicroseconds = (WORD)-1, nDays = nHour = nMinute = nSecond = nMilliseconds = nMicroseconds = 0, bCorrection = bMinusZero = FALSE; nSubFormatID <= MAXTIMETAGSUBFORMAT; nSubFormatID++)
	{
		for (nCtrl = 0, nCtrls = (INT)m_nCtrlFormat.GetSize(); nCtrl < nCtrls; nCtrl++)
		{
			if (nSubFormatID == (INT)m_nCtrlFormat.GetAt(nCtrl)) break;
			continue;
		}
		if (nCtrl < nCtrls  &&  IsSubFormatNumericalEditCtrl(nSubFormatID))
		{
			if ((pNumberEditCtrl = (CMimicsNumberEdit *)m_pwndEditCtrls.GetAt(nCtrl)) && pNumberEditCtrl->Check())
			{
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAR)
				{
					if (CWnd::GetFocus() == (CWnd *)pNumberEditCtrl || tFlagTime.wYear == (WORD)-1) tActualTime.wYear = tFlagTime.wYear = (WORD)pNumberEditCtrl->GetPos();
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAROFCENTURY)
				{
					if (CWnd::GetFocus() == (CWnd *)pNumberEditCtrl || tFlagTime.wYear == (WORD)-1) tActualTime.wYear = tFlagTime.wYear = (WORD)pNumberEditCtrl->GetPos() + 100 * (tActualTime.wYear / 100);
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTH)
				{
					if (CWnd::GetFocus() == (CWnd *)pNumberEditCtrl || tFlagTime.wMonth == (WORD)-1) tActualTime.wMonth = tFlagTime.wMonth = (WORD)pNumberEditCtrl->GetPos();
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR)
				{
					CTimeTag  tTimeConversion(CTimeTag(tActualTime).GetTime() + (pNumberEditCtrl->GetPos() - _ttoi64(CTimeTag(tActualTime).Format(nSubFormatID))) * 1000000 * (TIMETAG)SECONDSPERWEEK);
					if (CWnd::GetFocus() == (CWnd *)pNumberEditCtrl || (tFlagTime.wMonth == (WORD)-1 && tFlagTime.wDay == (WORD)-1) || (tActualTime.wMonth == (WORD)tTimeConversion.GetMonth() && tFlagTime.wDay == (WORD)-1))
					{
						tActualTime.wMonth = tFlagTime.wMonth = tTimeConversion.GetMonth();
						tActualTime.wDay = tFlagTime.wDay = tTimeConversion.GetDay();
					}
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR)
				{
					CTimeTag  tTimeConversion(tActualTime.wYear, (INT)pNumberEditCtrl->GetPos(), 0, 0, 0, 0, 0);
					if (CWnd::GetFocus() == (CWnd *)pNumberEditCtrl || (tFlagTime.wMonth == (WORD)-1 && tFlagTime.wDay == (WORD)-1) || (tActualTime.wMonth == (WORD)tTimeConversion.GetMonth() && tFlagTime.wDay == (WORD)-1))
					{
						tActualTime.wMonth = tFlagTime.wMonth = tTimeConversion.GetMonth();
						tActualTime.wDay = tFlagTime.wDay = tTimeConversion.GetDay();
					}
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFMONTH)
				{
					if (CWnd::GetFocus() == (CWnd *)pNumberEditCtrl || tFlagTime.wDay == (WORD)-1) tActualTime.wDay = tFlagTime.wDay = (WORD)pNumberEditCtrl->GetPos();
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK)
				{
					CTimeTag  tTimeConversion(CTimeTag(tActualTime).GetTime() + (pNumberEditCtrl->GetPos() - CTimeTag(tActualTime).GetDayOfWeek()) * 1000000 * (TIMETAG)SECONDSPERDAY);
					if (CWnd::GetFocus() == (CWnd *)pNumberEditCtrl || (tFlagTime.wMonth == (WORD)-1 && tFlagTime.wDay == (WORD)-1) || (tActualTime.wMonth == (WORD)tTimeConversion.GetMonth() && tFlagTime.wDay == (WORD)-1))
					{
						tActualTime.wDayOfWeek = tFlagTime.wDayOfWeek = tTimeConversion.GetDayOfWeek() - 1;
						tActualTime.wMonth = tFlagTime.wMonth = tTimeConversion.GetMonth();
						tActualTime.wDay = tFlagTime.wDay = tTimeConversion.GetDay();
					}
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYS)
				{
					nDays = (INT)pNumberEditCtrl->GetPos();
					bMinusZero |= pNumberEditCtrl->IsMinusZero();
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_HOUR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR)
				{
					tActualTime.wHour = tFlagTime.wHour = (WORD)(nHour = (INT)pNumberEditCtrl->GetPos());
					bMinusZero |= pNumberEditCtrl->IsMinusZero();
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MINUTE)
				{
					tActualTime.wMinute = tFlagTime.wMinute = (WORD)(nMinute = (INT)pNumberEditCtrl->GetPos());
					bMinusZero |= pNumberEditCtrl->IsMinusZero();
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_SECOND)
				{
					tActualTime.wSecond = tFlagTime.wSecond = (WORD)(nSecond = (INT)pNumberEditCtrl->GetPos());
					bMinusZero |= pNumberEditCtrl->IsMinusZero();
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MILLISECOND)
				{
					tActualTime.wMilliseconds = tFlagTime.wMilliseconds = (WORD)(nMilliseconds = (INT)pNumberEditCtrl->GetPos());
					bMinusZero |= pNumberEditCtrl->IsMinusZero();
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MICROSECOND)
				{
					wMicroseconds = (WORD)(nMicroseconds = (INT)pNumberEditCtrl->GetPos());
					bMinusZero |= pNumberEditCtrl->IsMinusZero();
					continue;
				}
			}
			break;
		}
		if (nCtrl < nCtrls)
		{
			if ((pTextEditCtrl = (CMimicsTextEdit *)m_pwndEditCtrls.GetAt(nCtrl)) && pTextEditCtrl->Check())
			{
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHMNEMONIC)
				{
					if (CWnd::GetFocus() == (CWnd *)pTextEditCtrl || tFlagTime.wMonth == (WORD)-1) tActualTime.wMonth = tFlagTime.wMonth = pTextEditCtrl->GetPos() + 1;
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC)
				{
					CTimeTag  tTimeConversion(CTimeTag(tActualTime).GetTime() + (pTextEditCtrl->GetPos() % DAYSPERWEEK - (CTimeTag(tActualTime).GetDayOfWeek() + Thursday) % DAYSPERWEEK) * 1000000 * (TIMETAG)SECONDSPERDAY);
					if (CWnd::GetFocus() == (CWnd *)pTextEditCtrl || (tFlagTime.wMonth == (WORD)-1 && tFlagTime.wDay == (WORD)-1) || (tActualTime.wMonth == tTimeConversion.GetMonth() && tFlagTime.wDay == (WORD)-1))
					{
						tActualTime.wDayOfWeek = tFlagTime.wDayOfWeek = tTimeConversion.GetDayOfWeek() - 1;
						tActualTime.wMonth = tFlagTime.wMonth = tTimeConversion.GetMonth();
						tActualTime.wDay = tFlagTime.wDay = tTimeConversion.GetDay();
					}
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANINDICATOR)
				{
					if (CWnd::GetFocus() == (CWnd *)pTextEditCtrl) tActualTime.wHour = tFlagTime.wHour = (pTextEditCtrl->GetPos() > 0) ? ((tActualTime.wHour < TIMESPINBOXHIGHLIMIT(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR))) ? (tActualTime.wHour + TIMESPINBOXHIGHLIMIT(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR))) : tActualTime.wHour) : ((tActualTime.wHour == TIMESPINBOXHIGHLIMIT(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR))) ? (tActualTime.wHour - TIMESPINBOXHIGHLIMIT(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR))) : tActualTime.wHour);
					continue;
				}
			}
			break;
		}
		continue;
	}
	for (tTime[0] = 0; nSubFormatID > MAXTIMETAGSUBFORMAT; )
	{
		if (m_tTime == 0 && tFlagTime.wYear == (WORD)-1)
		{
			tActualTime.wYear = CTimeTag(MIN_TIMETAG).GetYear();
			bCorrection = TRUE;
		}
		if (m_dwStyle & TSBXS_SPAN_TIME)
		{
			CopyMemory((LPVOID)lParam, &(tTime[0] = (nDays >= 0 && nHour >= 0 && nMinute >= 0 && nSecond >= 0 && nMilliseconds >= 0 && nMicroseconds >= 0 && !bMinusZero) ? (1000000 * (nDays*(TIMETAG)SECONDSPERDAY + nHour*(TIMETAG)SECONDSPERHOUR + nMinute*(TIMETAG)SECONDSPERMINUTE + nSecond) + 1000 * nMilliseconds + nMicroseconds) : (-1000000 * (abs(nDays)*(TIMETAG)SECONDSPERDAY + abs(nHour)*(TIMETAG)SECONDSPERHOUR + abs(nMinute)*(TIMETAG)SECONDSPERMINUTE + abs(nSecond)) - 1000 * abs(nMilliseconds) - abs(nMicroseconds))), sizeof(TIMETAG));
			return TRUE;
		}
		for (tTime[1] = (m_dwStyle & TSBXS_UTC_TIME) ? (CTimeTag(tActualTime).GetTime() - CTimeTag(tActualTime).GetBias()) : CTimeTag(tActualTime).GetTime(), tTime[1] += (wMicroseconds != (WORD)-1) ? wMicroseconds : 0, tTime[1] = (!m_bVisible) ? -m_tTime.GetTime() : tTime[1]; !m_bVisible || tTime[1] > 0; )
		{
			CopyMemory((LPVOID)lParam, &(tTime[0] = (bCorrection) ? (tTime[1] - CTimeTag(MIN_TIMETAG).GetTime()) : tTime[1]), sizeof(TIMETAG));
			break;
		}
		return TRUE;
	}
	CopyMemory((LPVOID)lParam, &tTime[0], sizeof(TIMETAG));
	return FALSE;
}

LRESULT CMimicsTimeSpinBox::OnSetRange(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	INT  nOffset;
	BOOL  bFirstCtrl;
	CWnd  *pCtrl[2];
	CRect  rCtrl[2];
	TIMETAG  tTime[2];
	CTimeTag  tTimeTag[2];
	CMimicsNumberEdit  *pNumberEditCtrl;

	for (CopyMemory(&tTime[0], (LPCVOID)wParam, sizeof(tTime[0])), CopyMemory(&tTime[1], (LPCVOID)lParam, sizeof(tTime[1])), GetTime(tTimeTag[0]); (m_dwStyle & TSBXS_PAST_TIME) && (m_dwStyle & TSBXS_SPAN_TIME) == 0; )
	{
		if (tTimeTag[1].GetTime() >= tTime[1] && tTime[0] < tTime[1])
		{
			if (tTimeTag[0].GetTime() < tTime[0]) SetTime(CTimeTag(tTime[0]));
			if (tTimeTag[0].GetTime() > tTime[1]) SetTime(CTimeTag(tTime[1]));
			m_tStartTime = tTime[0];
			m_tStopTime = tTime[1];
			return TRUE;
		}
		break;
	}
	if ((m_dwStyle & TSBXS_FUTURE_TIME) && (m_dwStyle & TSBXS_SPAN_TIME) == 0)
	{
		if (tTimeTag[1].GetTime() <= tTime[0] && tTime[0] < tTime[1])
		{
			if (tTimeTag[0].GetTime() < tTime[0]) SetTime(CTimeTag(tTime[0]));
			if (tTimeTag[0].GetTime() > tTime[1]) SetTime(CTimeTag(tTime[1]));
			m_tStartTime = tTime[0];
			m_tStopTime = tTime[1];
			return TRUE;
		}
	}
	if (tTime[0] <= tTime[1])
	{
		if (tTimeTag[0].GetTime() < tTime[0]) SetTime(CTimeTag(tTime[0]));
		if (tTimeTag[0].GetTime() > tTime[1]) SetTime(CTimeTag(tTime[1]));
		for (nCtrl = 0, nCtrls = (INT)m_nCtrlFormat.GetSize(), m_tStartTime = tTime[0], m_tStopTime = tTime[1]; nCtrl < nCtrls; nCtrl++)
		{
			if ((pCtrl[0] = pCtrl[1] = (m_nCtrlFormat.GetAt(nCtrl) == IDS_TIMEKEY_SUBFORMAT_DAYS) ? GetDlgItem(m_wndSpinCtrl.GetDlgCtrlID() + nCtrl + 1) : (CWnd *)NULL))
			{
				for (pCtrl[0]->GetWindowRect(rCtrl[0]); TranslateSubFormatPosition(STRING(m_nCtrlFormat.GetAt(nCtrl)), CRect(0, 0, 0, 0), rCtrl[1]) && (nOffset = rCtrl[1].Width() - rCtrl[0].Width()) != 0; )
				{
					for (rCtrl[0].SetRect(rCtrl[0].left, rCtrl[0].top, rCtrl[0].right + nOffset, rCtrl[0].bottom), ScreenToClient(rCtrl[0]), pCtrl[0]->MoveWindow(rCtrl[0]); (pCtrl[1] = pCtrl[1]->GetNextWindow()); )
					{
						pCtrl[1]->GetWindowRect(rCtrl[1]);
						rCtrl[1].OffsetRect(nOffset, 0);
						ScreenToClient(rCtrl[1]);
						pCtrl[1]->MoveWindow(rCtrl[1]);
					}
					break;
				}
			}
		}
		for (nCtrl = 0, bFirstCtrl = TRUE; nCtrl < nCtrls; nCtrl++)
		{
			if ((pNumberEditCtrl = (IsSubFormatNumericalEditCtrl(m_nCtrlFormat.GetAt(nCtrl))) ? (CMimicsNumberEdit *)GetDlgItem(m_wndSpinCtrl.GetDlgCtrlID() + nCtrl + 1) : (CMimicsNumberEdit *)NULL))
			{
				pNumberEditCtrl->EnableMinusZero((m_tStartTime < 0) ? bFirstCtrl : FALSE);
				bFirstCtrl = FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

LRESULT CMimicsTimeSpinBox::OnGetRange(WPARAM wParam, LPARAM lParam)
{
	TIMETAG  tTime[2];

	if (m_tStartTime != m_tStopTime)
	{
		CopyMemory((LPVOID)wParam, &(tTime[0] = m_tStartTime.GetTime()), sizeof(tTime[0]));
		CopyMemory((LPVOID)lParam, &(tTime[1] = m_tStopTime.GetTime()), sizeof(tTime[1]));
		return TRUE;
	}
	return FALSE;
}

LRESULT CMimicsTimeSpinBox::OnSetSel(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	CEdit  *pEditCtrl;

	for (nCtrl = HIWORD(wParam), nCtrls = (INT)m_pwndEditCtrls.GetSize(); (pEditCtrl = (nCtrl >= 0 && nCtrl < nCtrls) ? (CEdit *)m_pwndEditCtrls.GetAt(nCtrl) : (CEdit *)NULL); )
	{
		pEditCtrl->SetSel(LOWORD(wParam), LOWORD(lParam));
		pEditCtrl->SetFocus();
		return TRUE;
	}
	return FALSE;
}

LRESULT CMimicsTimeSpinBox::OnGetSel(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	INT  *nSel[2];
	CEdit  *pEditCtrl;

	for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pEditCtrl = (CEdit *)m_pwndEditCtrls.GetAt(nCtrl)) && CWnd::GetFocus() == (CWnd *)pEditCtrl)
		{
			*(nSel[0] = (LPINT)wParam) = MAKELONG(LOWORD(pEditCtrl->GetSel()), nCtrl);
			*(nSel[1] = (LPINT)lParam) = MAKELONG(HIWORD(pEditCtrl->GetSel()), nCtrl);
			return TRUE;
		}
	}
	*(nSel[0] = (LPINT)wParam) = MAKELONG(-1, -1);
	*(nSel[1] = (LPINT)lParam) = MAKELONG(-1, -1);
	return FALSE;
}

LRESULT CMimicsTimeSpinBox::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrlID;
	INT  nFormat;
	INT  nStaticCtrl;
	CRect  rSubCtrl;
	CRect  rEditCtrl;
	CRect  rStaticCtrl;
	LOGFONT  lfFont;
	CString  szDelimiter;
	CString  szTimeFormat;
	CStatic  *pStaticCtrl;
	CMimicsTextEdit  *pTextEditCtrl;
	CMimicsNumberEdit  *pNumberEditCtrl;

	for (m_cFont.DeleteObject(); GetObject((HGDIOBJ)wParam, sizeof(LOGFONT), &lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		for (GetWindowText(szTimeFormat), rSubCtrl.SetRect(CalcIndent(), 0, CalcIndent(), 0), nCtrlID = m_wndSpinCtrl.GetDlgCtrlID() + 1, nStaticCtrl = 0; !szTimeFormat.IsEmpty(); )
		{
			if ((nFormat = TranslateSubFormat(szTimeFormat)) >= 0 && TranslateSubFormatPosition(STRING(nFormat), rSubCtrl, rEditCtrl))
			{
				if (IsSubFormatNumericalEditCtrl(nFormat))
				{
					if ((pNumberEditCtrl = (CMimicsNumberEdit *)GetDlgItem(nCtrlID)))
					{
						szTimeFormat = szTimeFormat.Mid(lstrlen(STRING(nFormat)));
						pNumberEditCtrl->MoveWindow(rEditCtrl, LOWORD(lParam));
						pNumberEditCtrl->SetFont(&m_cFont, LOWORD(lParam));
						rSubCtrl = rEditCtrl;
						nCtrlID++;
						continue;
					}
					break;
				}
				if (IsSubFormatEditCtrl(nFormat))
				{
					if ((pTextEditCtrl = (CMimicsTextEdit *)GetDlgItem(nCtrlID)))
					{
						szTimeFormat = szTimeFormat.Mid(lstrlen(STRING(nFormat)));
						pTextEditCtrl->MoveWindow(rEditCtrl, LOWORD(lParam));
						pTextEditCtrl->SetFont(&m_cFont, LOWORD(lParam));
						rSubCtrl = rEditCtrl;
						nCtrlID++;
						continue;
					}
				}
				break;
			}
			if ((pStaticCtrl = (TranslateSubFormatDelimiter(szTimeFormat, szDelimiter) && TranslateSubFormatPosition(szDelimiter, rSubCtrl, rStaticCtrl) && nStaticCtrl < m_pwndStaticCtrls.GetSize()) ? (CStatic *)m_pwndStaticCtrls.GetAt(nStaticCtrl) : (CStatic *)NULL))
			{
				szTimeFormat = szTimeFormat.Mid(szDelimiter.GetLength());
				pStaticCtrl->MoveWindow(rStaticCtrl, LOWORD(lParam));
				pStaticCtrl->SetFont(&m_cFont, LOWORD(lParam));
				rSubCtrl = rStaticCtrl;
				nStaticCtrl++;
				continue;
			}
			break;
		}
		Invalidate(FALSE);
		UpdateWindow();
		break;
	}
	return FALSE;
}

LRESULT CMimicsTimeSpinBox::OnGetFont(WPARAM wParam, LPARAM lParam)
{
	return((LRESULT)m_cFont.GetSafeHandle());
}

void CMimicsTimeSpinBox::OnClose()
{
	GetParent()->SendMessage(WM_CLOSE);
}

void CMimicsTimeSpinBox::OnDestroy()
{
	CEdit  *pEditCtrl;
	CStatic  *pStaticCtrl;

	for (; m_pwndEditCtrls.GetSize() > 0; m_pwndEditCtrls.RemoveAt(0), m_nCtrlFormat.RemoveAt(0))
	{
		if ((pEditCtrl = (CEdit *)m_pwndEditCtrls.GetAt(0)))
		{
			pEditCtrl->DestroyWindow();
			delete pEditCtrl;
		}
	}
	for (; m_pwndStaticCtrls.GetSize() > 0; m_pwndStaticCtrls.RemoveAt(0))
	{
		if ((pStaticCtrl = (CStatic *)m_pwndStaticCtrls.GetAt(0)))
		{
			pStaticCtrl->DestroyWindow();
			delete pStaticCtrl;
		}
	}
	m_cFont.DeleteObject();
	CWnd::OnDestroy();
}

// MimicsTimeSpinBox helpers
VOID MimicsTimespinbox_SetTime(CWnd *pCtrl)
{
	TIMETAG  t = CTimeTag().GetTime();

	pCtrl->SendMessage(TSBXM_SETTIME, TRUE, (LPARAM)&t);
}
VOID MimicsTimespinbox_SetTime(CWnd *pCtrl, CONST CTimeTag &tTime)
{
	TIMETAG  t = tTime.GetTime();

	pCtrl->SendMessage(TSBXM_SETTIME, (WPARAM)NULL, (LPARAM)&t);
}
VOID MimicsTimespinbox_SetTime(CWnd *pCtrl, CONST CTimeKey &tTime)
{
	TIMETAG  t = 1000000 * tTime.GetTime();

	pCtrl->SendMessage(TSBXM_SETTIME, (WPARAM)NULL, (LPARAM)&t);
}

CTimeKey MimicsTimespinbox_GetTime(CWnd *pCtrl)
{
	TIMETAG  t;

	return((pCtrl->SendMessage(TSBXM_GETTIME, (WPARAM)NULL, (LPARAM)&t)) ? (t / 1000000) : 0);
}
BOOL MimicsTimespinbox_GetTime(CWnd *pCtrl, CTimeTag &tTime)
{
	TIMETAG  t;

	if (pCtrl->SendMessage(TSBXM_GETTIME, (WPARAM)NULL, (LPARAM)&t))
	{
		tTime = t;
		return TRUE;
	}
	return FALSE;
}
BOOL MimicsTimespinbox_GetTime(CWnd *pCtrl, CTimeKey &tTime)
{
	TIMETAG  t;

	if (pCtrl->SendMessage(TSBXM_GETTIME, (WPARAM)NULL, (LPARAM)&t))
	{
		tTime = t / 1000000;
		return TRUE;
	}
	return FALSE;
}

BOOL MimicsTimespinbox_SetRange(CWnd *pCtrl, CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime)
{
	TIMETAG  t[2] = { tStartTime.GetTime(),tStopTime.GetTime() };

	return((BOOL)pCtrl->SendMessage(TSBXM_SETRANGE, (WPARAM)&t[0], (LPARAM)&t[1]));
}
BOOL MimicsTimespinbox_SetRange(CWnd *pCtrl, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	TIMETAG  t[2] = { 1000000 * tStartTime.GetTime(),1000000 * tStopTime.GetTime() };

	return((BOOL)pCtrl->SendMessage(TSBXM_SETRANGE, (WPARAM)&t[0], (LPARAM)&t[1]));
}

BOOL MimicsTimespinbox_GetRange(CWnd *pCtrl, CTimeTag &tStartTime, CTimeTag &tStopTime)
{
	TIMETAG  t[2];

	if (pCtrl->SendMessage(TSBXM_GETRANGE, (WPARAM)&t[0], (LPARAM)&t[1]))
	{
		tStartTime = t[0];
		tStopTime = t[1];
		return TRUE;
	}
	return FALSE;
}
BOOL MimicsTimespinbox_GetRange(CWnd *pCtrl, CTimeKey &tStartTime, CTimeKey &tStopTime)
{
	TIMETAG  t[2];

	if (pCtrl->SendMessage(TSBXM_GETRANGE, (WPARAM)&t[0], (LPARAM)&t[1]))
	{
		tStartTime = t[0] / 1000000;
		tStopTime = t[1] / 1000000;
		return TRUE;
	}
	return FALSE;
}

BOOL MimicsTimespinbox_SetSel(CWnd *pCtrl, INT nStartPos, INT nStopPos)
{
	return((BOOL)pCtrl->SendMessage(TSBXM_SETSEL, nStartPos, nStopPos));
}

BOOL MimicsTimespinbox_GetSel(CWnd *pCtrl, INT &nStartPos, INT &nStopPos)
{
	return((BOOL)pCtrl->SendMessage(TSBXM_GETSEL, (WPARAM)&nStartPos, (LPARAM)&nStopPos));
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsTimeSpinBox

IMPLEMENT_DYNCREATE(CResourceMimicsTimeSpinBox, CMimicsTimeSpinBox)

CResourceMimicsTimeSpinBox::CResourceMimicsTimeSpinBox(HWND hWnd) : CMimicsTimeSpinBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMimicsTimeSpinBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMimicsTimeSpinBox  *pResourceTimeSpinBox;

	if ((pResourceTimeSpinBox = new CResourceMimicsTimeSpinBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

void CResourceMimicsTimeSpinBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMimicsTimeSpinBox, CMimicsTimeSpinBox)
	//{{AFX_MSG_MAP(CResourceMimicsTimeSpinBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsTimeSpinBox message handlers

BOOL CResourceMimicsTimeSpinBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG(((m_dwStyle = LOWORD(lpCreateStruct->style) & (TSBXS_ANY_TIME | TSBXS_PAST_TIME | TSBXS_FUTURE_TIME | TSBXS_UTC_TIME | TSBXS_SPAN_TIME | TSBXS_HIDE_TIME)) ? NULL : NULL), HIWORD(lpCreateStruct->style)) | WS_CHILD));
	return CMimicsTimeSpinBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// ListBox helpers

BOOL Listbox_SetText(CWnd *pCtrl, INT nItem, LPCTSTR pszText)
{
	INT  nIndex;

	if (nItem >= 0 && nItem < pCtrl->SendMessage(LB_GETCOUNT))
	{
		if (Listbox_GetText(pCtrl, nItem).Compare(pszText) != 0)
		{
			if (((pCtrl->GetStyle() & (LBS_OWNERDRAWVARIABLE) | LBS_OWNERDRAWFIXED)) == 0 || (pCtrl->GetStyle() & LBS_HASSTRINGS))
			{
				for (nIndex = (INT)pCtrl->SendMessage(LB_GETCURSEL); pCtrl->SendMessage(LB_DELETESTRING, nItem) != LB_ERR && pCtrl->SendMessage(LB_INSERTSTRING, nItem, (LPARAM)pszText) != LB_ERR; )
				{
					pCtrl->SendMessage(LB_SETCURSEL, nIndex);
					return TRUE;
				}
				return FALSE;
			}
			return((pCtrl->SendMessage(LB_SETITEMDATA, nItem, (LPARAM)_ttoi(pszText)) != LB_ERR) ? TRUE : FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

CString Listbox_GetText(CWnd *pCtrl, INT nItem)
{
	INT  nLength;
	CString  szText;
	DWORD_PTR  dwData;
	CStringTools  cStringTools;

	if (nItem >= 0 && nItem < pCtrl->SendMessage(LB_GETCOUNT))
	{
		if (((pCtrl->GetStyle() & LBS_OWNERDRAWVARIABLE) || (pCtrl->GetStyle() & LBS_OWNERDRAWFIXED)) && (pCtrl->GetStyle() & LBS_HASSTRINGS) != LBS_HASSTRINGS)
		{
			dwData = pCtrl->SendMessage(LB_GETITEMDATA, nItem);
			return cStringTools.ConvertLongUIntToString(dwData);
		}
		if ((nLength = (INT)pCtrl->SendMessage(LB_GETTEXTLEN, nItem)) >= 0)
		{
			for (szText.GetBufferSetLength(nLength); pCtrl->SendMessage(LB_GETTEXT, nItem, (LPARAM)(LPTSTR)(LPCTSTR)szText) != LB_ERR; )
			{
				szText.ReleaseBuffer();
				return szText;
			}
			szText.ReleaseBuffer();
			szText.Empty();
		}
	}
	return szText;
}


/////////////////////////////////////////////////////////////////////////////
// ComboBox helpers

BOOL Combobox_SetText(CWnd *pCtrl, INT nItem, LPCTSTR pszText)
{
	INT  nIndex;

	if (nItem >= 0 && nItem < pCtrl->SendMessage(CB_GETCOUNT))
	{
		if (Combobox_GetText(pCtrl, nItem).Compare(pszText) != 0)
		{
			if (((pCtrl->GetStyle() & (CBS_OWNERDRAWVARIABLE) | CBS_OWNERDRAWFIXED)) == 0 || (pCtrl->GetStyle() & CBS_HASSTRINGS))
			{
				for (nIndex = (INT)pCtrl->SendMessage(CB_GETCURSEL); pCtrl->SendMessage(CB_DELETESTRING, nItem) != CB_ERR && pCtrl->SendMessage(CB_INSERTSTRING, nItem, (LPARAM)pszText) != CB_ERR; )
				{
					pCtrl->SendMessage(CB_SETCURSEL, nIndex);
					return TRUE;
				}
				return FALSE;
			}
			return((pCtrl->SendMessage(CB_SETITEMDATA, nItem, (LPARAM)_ttoi(pszText)) != CB_ERR) ? TRUE : FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

CString Combobox_GetText(CWnd *pCtrl, INT nItem)
{
	INT  nLength;
	CString  szText;
	DWORD_PTR  dwData;
	CStringTools  cStringTools;

	if (nItem >= 0 && nItem < pCtrl->SendMessage(CB_GETCOUNT))
	{
		if (((pCtrl->GetStyle() & CBS_OWNERDRAWVARIABLE) || (pCtrl->GetStyle() & CBS_OWNERDRAWFIXED)) && (pCtrl->GetStyle() & CBS_HASSTRINGS) != CBS_HASSTRINGS)
		{
			dwData = pCtrl->SendMessage(CB_GETITEMDATA, nItem);
			return cStringTools.ConvertLongUIntToString(dwData);
		}
		if ((nLength = (INT)pCtrl->SendMessage(CB_GETLBTEXTLEN, nItem)) >= 0)
		{
			for (szText.GetBufferSetLength(nLength); pCtrl->SendMessage(CB_GETLBTEXT, nItem, (LPARAM)(LPTSTR)(LPCTSTR)szText) != CB_ERR; )
			{
				szText.ReleaseBuffer();
				return szText;
			}
			szText.ReleaseBuffer();
			szText.Empty();
		}
	}
	return szText;
}


/////////////////////////////////////////////////////////////////////////////
// ListView helpers

BOOL Listview_InsertColumn(CWnd *pCtrl, INT nColumn, LPCTSTR pszColumn, INT nWidth)
{
	LVCOLUMN  sColumn;

	sColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	sColumn.fmt = LVCFMT_LEFT;
	sColumn.cx = nWidth;
	sColumn.pszText = (LPTSTR)pszColumn;
	sColumn.cchTextMax = lstrlen(pszColumn) + 1;
	return((pCtrl->SendMessage(LVM_INSERTCOLUMN, nColumn, (LPARAM)&sColumn) >= 0) ? TRUE : FALSE);
}

BOOL Listview_SetColumn(CWnd *pCtrl, INT nColumn, LPCTSTR pszColumn, INT nWidth)
{
	LVCOLUMN  sColumn;

	sColumn.mask = (nWidth >= 0) ? (LVCF_TEXT | LVCF_WIDTH) : LVCF_TEXT;
	sColumn.cx = (nWidth >= 0) ? nWidth : 0;
	sColumn.pszText = (LPTSTR)pszColumn;
	sColumn.cchTextMax = lstrlen(pszColumn) + 1;
	return((pCtrl->SendMessage(LVM_SETCOLUMN, nColumn, (LPARAM)&sColumn)) ? TRUE : FALSE);
}

BOOL Listview_GetColumn(CWnd *pCtrl, INT nColumn, CString &szColumn, INT &nWidth)
{
	LVCOLUMN  sColumn;
	TCHAR  szText[1024];

	sColumn.mask = LVCF_TEXT | LVCF_WIDTH;
	sColumn.pszText = (LPTSTR)szText;
	sColumn.cchTextMax = sizeof(szText) / sizeof(TCHAR) - 1;
	if (pCtrl->SendMessage(LVM_GETCOLUMN, nColumn, (LPARAM)&sColumn))
	{
		szColumn = sColumn.pszText;
		nWidth = sColumn.cx;
		return TRUE;
	}
	return FALSE;
}

BOOL Listview_DeleteColumn(CWnd *pCtrl, INT nColumn)
{
	return((pCtrl->SendMessage(LVM_DELETECOLUMN, nColumn)) ? TRUE : FALSE);
}

BOOL Listview_InsertText(CWnd *pCtrl, INT nItem, LPCTSTR pszText)
{
	LVITEM  sItem;

	sItem.iItem = nItem;
	sItem.iSubItem = 0;
	sItem.mask = LVIF_TEXT;
	sItem.pszText = (LPTSTR)pszText;
	sItem.cchTextMax = lstrlen(pszText) + 1;
	return((pCtrl->SendMessage(LVM_INSERTITEM, (WPARAM)NULL, (LPARAM)&sItem) >= 0) ? TRUE : FALSE);
}

BOOL Listview_SetText(CWnd *pCtrl, INT nItem, INT nSubItem, LPCTSTR pszText)
{
	LVITEM  sItem;

	sItem.iItem = nItem;
	sItem.iSubItem = nSubItem;
	sItem.mask = LVIF_TEXT;
	sItem.pszText = (LPTSTR)pszText;
	sItem.cchTextMax = lstrlen(pszText) + 1;
	return((pCtrl->SendMessage(LVM_SETITEM, (WPARAM)NULL, (LPARAM)&sItem)) ? TRUE : FALSE);
}

CString Listview_GetText(CWnd *pCtrl, INT nItem, INT nSubItem)
{
	LVITEM  sItem;
	TCHAR  szText[1024];

	sItem.iItem = nItem;
	sItem.iSubItem = nSubItem;
	sItem.mask = LVIF_TEXT;
	sItem.pszText = szText;
	sItem.cchTextMax = sizeof(szText) / sizeof(TCHAR) - 1;
	return((pCtrl->SendMessage(LVM_GETITEM, (WPARAM)NULL, (LPARAM)&sItem)) ? sItem.pszText : EMPTYSTRING);
}

BOOL Listview_SetCurText(CWnd *pCtrl, INT nItem)
{
	INT  nIndex;
	INT  nCount;
	LVITEM  sItem;

	for (nIndex = 0, nCount = (INT)pCtrl->SendMessage(LVM_GETITEMCOUNT); nIndex < nCount; nIndex++)
	{
		sItem.iItem = nIndex;
		sItem.iSubItem = 0;
		sItem.mask = LVIF_STATE;
		sItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
		sItem.state = (nIndex == nItem) ? (LVIS_SELECTED | LVIS_FOCUSED) : 0;
		if (!pCtrl->SendMessage(LVM_SETITEM, (WPARAM)NULL, (LPARAM)&sItem)) break;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

INT Listview_GetCurText(CWnd *pCtrl)
{
	INT  nIndex;
	INT  nCount;
	LVITEM  sItem;

	for (nIndex = 0, nCount = (INT)pCtrl->SendMessage(LVM_GETITEMCOUNT); nIndex < nCount; nIndex++)
	{
		sItem.iItem = nIndex;
		sItem.iSubItem = 0;
		sItem.mask = LVIF_STATE;
		sItem.stateMask = LVIS_SELECTED;
		if (pCtrl->SendMessage(LVM_GETITEM, (WPARAM)NULL, (LPARAM)&sItem) && sItem.state == LVIS_SELECTED) break;
	}
	return((nIndex < nCount) ? nIndex : -1);
}

BOOL Listview_SetSelText(CWnd *pCtrl, CONST CUIntArray &nItems)
{
	INT  nIndex[2];
	INT  nCount[2];
	LVITEM  sItem;

	for (nIndex[0] = 0, nCount[0] = (INT)pCtrl->SendMessage(LVM_GETITEMCOUNT); nIndex[0] < nCount[0]; nIndex[0]++)
	{
		for (nIndex[1] = 0, nCount[1] = (INT)nItems.GetCount(); nIndex[1] < nCount[1]; nIndex[1]++)
		{
			if (nItems.GetAt(nIndex[1]) == nIndex[0]) break;
			continue;
		}
		sItem.iItem = nIndex[0];
		sItem.iSubItem = 0;
		sItem.mask = LVIF_STATE;
		sItem.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
		sItem.state = (nIndex[1] < nCount[1]) ? (LVIS_SELECTED | LVIS_FOCUSED) : 0;
		if (!pCtrl->SendMessage(LVM_SETITEM, (WPARAM)NULL, (LPARAM)&sItem)) break;
	}
	return((nIndex[0] == nCount[0]) ? TRUE : FALSE);
}

BOOL Listview_IsSelText(CWnd *pCtrl, INT nItem)
{
	LVITEM  sItem;

	sItem.iItem = nItem;
	sItem.iSubItem = 0;
	sItem.mask = LVIF_STATE;
	sItem.stateMask = LVIS_SELECTED;
	return((pCtrl->SendMessage(LVM_GETITEM, (WPARAM)NULL, (LPARAM)&sItem) && sItem.state == LVIS_SELECTED) ? TRUE : FALSE);
}

INT Listview_GetSelText(CWnd *pCtrl, CUIntArray &nItems)
{
	INT  nIndex;
	INT  nCount;
	LVITEM  sItem;

	for (nIndex = 0, nCount = (INT)pCtrl->SendMessage(LVM_GETITEMCOUNT), nItems.RemoveAll(); nIndex < nCount; nIndex++)
	{
		for (sItem.iItem = nIndex, sItem.iSubItem = 0, sItem.mask = LVIF_STATE, sItem.stateMask = LVIS_SELECTED; pCtrl->SendMessage(LVM_GETITEM, (WPARAM)NULL, (LPARAM)&sItem) && sItem.state == LVIS_SELECTED; )
		{
			nItems.Add(nIndex);
			break;
		}
	}
	return((INT)nItems.GetSize());
}

BOOL Listview_DeleteText(CWnd *pCtrl, INT nItem)
{
	return((pCtrl->SendMessage(LVM_DELETEITEM, nItem)) ? TRUE : FALSE);
}
