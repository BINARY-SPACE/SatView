// CONTROLS.CPP : Custom Control Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the custom control
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/07/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMimicsControls

BOOL CMimicsControls::RegisterMimicsControls()
{
	CHAR  szName[64];
	HMODULE  hModule;
	HRESULT(STDAPICALLTYPE * RegisterMimicsControlsProc)();

	if ((hModule = AfxLoadLibrary(STRING(IDS_FILENAME_MIMICSMODULE))))
	{
#ifndef UNICODE
		strcpy_s(szName, sizeof(szName) / sizeof(CHAR), STRING(IDS_EXPORTINTERFACE_REGISTERMIMICSCONTROLS));
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_REGISTERMIMICSCONTROLS), -1, szName, sizeof(szName) / sizeof(CHAR), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
		if ((RegisterMimicsControlsProc = (HRESULT(STDAPICALLTYPE*)()) GetProcAddress(hModule, szName)))
		{
			if (RegisterMimicsControlsProc() == NOERROR)
			{
				AfxFreeLibrary(hModule);
				return TRUE;
			}
		}
		AfxFreeLibrary(hModule);
	}
	return FALSE;
}

BOOL CMimicsControls::UnregisterMimicsControls()
{
	CHAR  szName[64];
	HMODULE  hModule;
	HRESULT(STDAPICALLTYPE * UnregisterMimicsControlsProc)();

	if ((hModule = AfxLoadLibrary(STRING(IDS_FILENAME_MIMICSMODULE))))
	{
#ifndef UNICODE
		strcpy_s(szName, sizeof(szName) / sizeof(CHAR), STRING(IDS_EXPORTINTERFACE_UNREGISTERMIMICSCONTROLS));
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_UNREGISTERMIMICSCONTROLS), -1, szName, sizeof(szName) / sizeof(CHAR), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
		if ((UnregisterMimicsControlsProc = (HRESULT(STDAPICALLTYPE*)()) GetProcAddress(hModule, szName)))
		{
			if (UnregisterMimicsControlsProc() == NOERROR)
			{
				AfxFreeLibrary(hModule);
				return TRUE;
			}
		}
		AfxFreeLibrary(hModule);
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CCustomControls

BOOL CCustomControls::RegisterCustomControls()
{
	BOOL  bSuccess;

	bSuccess = CSimpleEdit::RegisterClass();
	bSuccess &= CNumberEdit::RegisterClass();
	bSuccess &= CTextEdit::RegisterClass();
	bSuccess &= CDPLCodeEdit::RegisterClass();
	bSuccess &= CMDLCodeEdit::RegisterClass();
	bSuccess &= CTPLCodeEdit::RegisterClass();
	bSuccess &= CScriptCodeEdit::RegisterClass();
	bSuccess &= CANDXmlEdit::RegisterClass();
	bSuccess &= CGRDXmlEdit::RegisterClass();
	bSuccess &= CPODXmlEdit::RegisterClass();
	bSuccess &= CSimpleListBox::RegisterClass();
	bSuccess &= CColorsComboBox::RegisterClass();
	bSuccess &= CLineStylesComboBox::RegisterClass();
	bSuccess &= CLineSymbolsComboBox::RegisterClass();
	bSuccess &= CHatchesComboBox::RegisterClass();
	bSuccess &= CFontsComboBox::RegisterClass();
	bSuccess &= CAlignmentComboBox::RegisterClass();
	bSuccess &= CSpinBox::RegisterClass();
	bSuccess &= CTimeSpinBox::RegisterClass();
	return bSuccess;
}

BOOL CCustomControls::UnregisterCustomControls()
{
	BOOL  bSuccess;

	bSuccess = CSimpleEdit::UnregisterClass();
	bSuccess &= CNumberEdit::UnregisterClass();
	bSuccess &= CTextEdit::UnregisterClass();
	bSuccess &= CDPLCodeEdit::UnregisterClass();
	bSuccess &= CMDLCodeEdit::UnregisterClass();
	bSuccess &= CTPLCodeEdit::UnregisterClass();
	bSuccess &= CScriptCodeEdit::UnregisterClass();
	bSuccess &= CANDXmlEdit::UnregisterClass();
	bSuccess &= CGRDXmlEdit::UnregisterClass();
	bSuccess &= CPODXmlEdit::UnregisterClass();
	bSuccess &= CSimpleListBox::UnregisterClass();
	bSuccess &= CColorsComboBox::UnregisterClass();
	bSuccess &= CLineStylesComboBox::UnregisterClass();
	bSuccess &= CLineSymbolsComboBox::UnregisterClass();
	bSuccess &= CHatchesComboBox::UnregisterClass();
	bSuccess &= CFontsComboBox::UnregisterClass();
	bSuccess &= CAlignmentComboBox::UnregisterClass();
	bSuccess &= CSpinBox::UnregisterClass();
	bSuccess &= CTimeSpinBox::UnregisterClass();
	return bSuccess;
}

CRuntimeClass* CCustomControls::GetCustomControlBaseClass(CRuntimeClass* pClass)
{
	return((AfxIsValidAddress(pClass, sizeof(CRuntimeClass), FALSE)) ? pClass->m_pfnGetBaseClass() : (CRuntimeClass*)NULL);
}

CFont* CCustomControls::GetCustomControlFont(CONST CWnd* pControl)
{
	CFont* pFont[2];
	CFontTools  cFontTools;

	if (IsWindow(pControl->GetSafeHwnd()))
	{
		if ((pFont[0] = pControl->GetFont())) return pFont[0];
		if ((pFont[0] = pControl->GetParent()->GetFont())) return pFont[0];
		if ((pFont[0] = new CFont) != (CFont*)NULL)
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
// CSimpleEdit

IMPLEMENT_DYNCREATE(CSimpleEdit, CEdit)

CSimpleEdit::CSimpleEdit()
{
	m_dwStyle = 0;
}

BOOL CSimpleEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CEdit::Create((MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (ES_MULTILINE | ES_LEFT | ES_CENTER | ES_RIGHT | ES_LOWERCASE | ES_UPPERCASE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_OEMCONVERT)) & ~(ES_NOHIDESEL | ES_PASSWORD | ES_WANTRETURN))), HIWORD(dwStyle)) | WS_CHILD) & ~WS_TABSTOP, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CSimpleEdit::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CSimpleEdit  cSimpleEdit;

	if ((pClass = cSimpleEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName && GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceSimpleEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceSimpleEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceSimpleEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CSimpleEdit::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CSimpleEdit  cSimpleEdit;

	if ((pClass = cSimpleEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

BEGIN_MESSAGE_MAP(CSimpleEdit, CEdit)
	//{{AFX_MSG_MAP(CSimpleEdit)
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
// CSimpleEdit message handlers

BOOL CSimpleEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	for (m_szContents = lpCreateStruct->lpszName; !IsThemeActive(); )
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | ((lpCreateStruct->style & WS_BORDER) ? WS_EX_CLIENTEDGE : 0));
		SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~(lpCreateStruct->style & WS_BORDER));
		break;
	}
	return CEdit::OnNcCreate(lpCreateStruct);
}

BOOL CSimpleEdit::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
	GetParent()->SendMessage(WM_SETCURSOR, (WPARAM)GetParent()->GetSafeHwnd(), MAKELPARAM(nHitTest, message));
	return TRUE;
}

void CSimpleEdit::OnSetFocus(CWnd* pOldWnd)
{
	return;
}

void CSimpleEdit::OnEnable(BOOL bEnable)
{
	CString  szContents;

	SetWindowText((bEnable) ? (LPCTSTR)(szContents = m_szContents) : EMPTYSTRING);
	m_szContents = szContents;
	CEdit::OnEnable(bEnable);
}

void CSimpleEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	return;
}

void CSimpleEdit::OnMButtonDown(UINT nFlags, CPoint point)
{
	return;
}

void CSimpleEdit::OnRButtonDown(UINT nFlags, CPoint point)
{
	return;
}

LRESULT CSimpleEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	m_szContents = (LPCTSTR)lParam;
	return Default();
}


/////////////////////////////////////////////////////////////////////////////
// CResourceSimpleEdit

IMPLEMENT_DYNCREATE(CResourceSimpleEdit, CSimpleEdit)

WNDPROC CResourceSimpleEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceSimpleEdit::CResourceSimpleEdit(HWND hWnd) : CSimpleEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceSimpleEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceSimpleEdit* pResourceSimpleEdit;

	if ((pResourceSimpleEdit = new CResourceSimpleEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceSimpleEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceSimpleEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceSimpleEdit, CSimpleEdit)
	//{{AFX_MSG_MAP(CResourceSimpleEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceSimpleEdit message handlers

BOOL CResourceSimpleEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (ES_MULTILINE | ES_LEFT | ES_CENTER | ES_RIGHT | ES_LOWERCASE | ES_UPPERCASE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_OEMCONVERT)) & ~(ES_NOHIDESEL | ES_PASSWORD | ES_WANTRETURN))), HIWORD(lpCreateStruct->style)) | WS_CHILD) & ~WS_TABSTOP));
	return CSimpleEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CNumberEdit

IMPLEMENT_DYNCREATE(CNumberEdit, CEdit)

CNumberEdit::CNumberEdit() : CEdit()
{
	m_nBase = 10;
	m_nDigits = 0;
	m_dwStyle = 0;
	m_nMin = m_nMax = 0;
	m_bMinusZero = FALSE;
	m_bAutoCompletion = TRUE;
}

BOOL CNumberEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle, BOOL bMinusZero)
{
	if (CEdit::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LOWERCASE | ES_UPPERCASE | ES_NUMBER | ES_PASSWORD | ES_READONLY | ES_WANTRETURN)) | ES_MULTILINE), HIWORD(dwStyle)) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		m_bMinusZero = bMinusZero;
		return TRUE;
	}
	return FALSE;
}

BOOL CNumberEdit::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CNumberEdit  cNumberEdit;

	if ((pClass = cNumberEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName && GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceNumberEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceNumberEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceNumberEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CNumberEdit::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CNumberEdit  cNumberEdit;

	if ((pClass = cNumberEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

VOID CNumberEdit::EnableMinusZero(BOOL bEnable)
{
	m_bMinusZero = bEnable;
}

BOOL CNumberEdit::IsMinusZeroEnabled() CONST
{
	return m_bMinusZero;
}

BOOL CNumberEdit::IsMinusZero() CONST
{
	CString  szNumber;

	GetWindowText(szNumber);
	return CheckMinusZero(szNumber);
}

VOID CNumberEdit::EnableAutoCompletion(BOOL bEnable)
{
	m_bAutoCompletion = bEnable;
}

BOOL CNumberEdit::IsAutoCompletionEnabled() CONST
{
	return m_bAutoCompletion;
}

VOID CNumberEdit::Format()
{
	CWnd* pWnd;
	CRect  rNumberEdit;
	CRect  rFormatArea;

	for (; (pWnd = GetParent()) && (pWnd->IsKindOf(RUNTIME_CLASS(CSpinBox)) || pWnd->IsKindOf(RUNTIME_CLASS(CTimeSpinBox))); )
	{
		SetMargins(0, 0);
		break;
	}
	GetRect(rFormatArea);
	GetClientRect(rNumberEdit);
	rFormatArea.SetRect(rFormatArea.left, (rNumberEdit.Height() - rFormatArea.Height()) / 2, rFormatArea.right, (rNumberEdit.Height() - rFormatArea.Height()) / 2 + rFormatArea.Height());
	SetRect(rFormatArea);
}

BOOL CNumberEdit::CheckMinusZero(LPCTSTR pszNumber) CONST
{
	return((!ConstructMinusZero(m_nDigits + 1).Compare(pszNumber)) ? m_bMinusZero : FALSE);
}

CString CNumberEdit::ConstructMinusZero(UINT nDigits) CONST
{
	CStringTools  cStringTools;

	return((nDigits > 0) ? (cStringTools.ConvertIntToString(-1).GetAt(0) + cStringTools.ConvertIntToPaddedString(0, nDigits - 1)) : (cStringTools.ConvertIntToString(-1).GetAt(0) + cStringTools.ConvertIntToString(0)));
}

BEGIN_MESSAGE_MAP(CNumberEdit, CEdit)
	//{{AFX_MSG_MAP(CNumberEdit)
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
// CNumberEdit message handlers

BOOL CNumberEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!IsThemeActive())
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | ((lpCreateStruct->style & WS_BORDER) ? WS_EX_CLIENTEDGE : 0));
		SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~(lpCreateStruct->style & WS_BORDER));
	}
	return CEdit::OnNcCreate(lpCreateStruct);
}

void CNumberEdit::OnSize(UINT nType, int cx, int cy)
{
	Default();
	Format();
}

void CNumberEdit::OnEnable(BOOL bEnable)
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

UINT CNumberEdit::OnGetDlgCode()
{
	return CEdit::OnGetDlgCode() | DLGC_WANTARROWS | DLGC_WANTALLKEYS | DLGC_WANTCHARS;
}

void CNumberEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	CSpinBox* pSpinBox;
	CTimeSpinBox* pTimeSpinBox;

	if ((pSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CSpinBox))) ? (CSpinBox*)GetParent() : (CSpinBox*)NULL)) pSpinBox->UpdateUI();
	if ((pTimeSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CTimeSpinBox))) ? (CTimeSpinBox*)GetParent() : (CTimeSpinBox*)NULL)) pTimeSpinBox->UpdateUI();
	CEdit::OnMouseMove(nFlags, point);
}

void CNumberEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd* pWnd[2];
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
	default:
	{ nPos = 0;
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
		if ((GetParent()->GetStyle() & WS_TABSTOP) && LOWORD(GetSel()) == HIWORD(GetSel()) && ((nChar == VK_LEFT && !LOWORD(GetSel())) || (nChar == VK_RIGHT && LOWORD(GetSel()) == GetWindowTextLength())))
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
			for (pWnd[0] = this; !pWnd[0]->IsKindOf(RUNTIME_CLASS(CDialogEx)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CMFCPropertySheet)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CMFCPropertyPage)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CView)); )
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

void CNumberEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString  szSign;
	CString  szDigit[3];
	CStringTools  cStringTools;

	for (szSign = cStringTools.ConvertIntToString(-1), szDigit[0] = cStringTools.ConvertIntToString(0), szDigit[1] = cStringTools.ConvertIntToString(1), szDigit[2] = cStringTools.ConvertIntToString(7); (nChar == (UINT)szSign[0] && (m_nBase == 2 || m_nMin >= 0 || (m_nMin < 0 && GetWindowTextLength() > 0 && (LOWORD(GetSel()) || HIWORD(GetSel()) < GetWindowTextLength())))) || (nChar != (UINT)szSign[0] && ((m_nBase == 2 && (nChar < (UINT)__toascii(szDigit[0].GetAt(0)) || nChar >(UINT) __toascii(szDigit[1].GetAt(0)))) || (m_nBase == 8 && (nChar < (UINT)__toascii(szDigit[0].GetAt(0)) || nChar >(UINT) __toascii(szDigit[2].GetAt(0)))) || (m_nBase == 10 && !_istdigit(nChar)) || (m_nBase == 16 && !_istxdigit(nChar))) && nChar >= VK_SPACE); )
	{
		CAudioDevice::AlertBySound();
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

void CNumberEdit::OnKillFocus(CWnd* pNewWnd)
{
	if (IsAutoCompletionEnabled() && !Check()) SetPos(GetPos(FALSE), TRUE);
	CEdit::OnKillFocus(pNewWnd);
}

LRESULT CNumberEdit::OnFont(WPARAM wParam, LPARAM lParam)
{
	Default();
	Format();
	return 0;
}

LRESULT CNumberEdit::OnNumber(WPARAM wParam, LPARAM lParam)
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

LRESULT CNumberEdit::OnSetBase(WPARAM wParam, LPARAM lParam)
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

LRESULT CNumberEdit::OnGetBase(WPARAM wParam, LPARAM lParam)
{
	*((UINT*)wParam) = m_nBase;
	*((UINT*)lParam) = m_nDigits;
	return((m_nBase == 2 || m_nBase == 8 || m_nBase == 10 || m_nBase == 16) ? TRUE : FALSE);
}

LRESULT CNumberEdit::OnSetRange(WPARAM wParam, LPARAM lParam)
{
	LONGLONG  nMin = (*(LONGLONG*)wParam);
	LONGLONG  nMax = (*(LONGLONG*)lParam);

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

LRESULT CNumberEdit::OnGetRange(WPARAM wParam, LPARAM lParam)
{
	*((LONGLONG*)wParam) = m_nMin;
	*((LONGLONG*)lParam) = m_nMax;
	return((m_nMin <= m_nMax) ? TRUE : FALSE);
}

LRESULT CNumberEdit::OnSetPos(WPARAM wParam, LPARAM lParam)
{
	CString  szPos;
	CString  szText;
	BOOL  bMinusZero;
	CStringTools  cStringTools;
	LONGLONG  nPos = (*(LONGLONG*)lParam);

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

LRESULT CNumberEdit::OnGetPos(WPARAM wParam, LPARAM lParam)
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
			nPos += ((LONGLONG)__toascii(szChar) - (LONGLONG)__toascii(szDigit[0].GetAt(0))) * nBase;
			nBase *= m_nBase;
			continue;
		}
		if (_istxdigit(szChar))
		{
			nPos += ((LONGLONG)__toascii(szChar) - (LONGLONG)__toascii(szDigit[1].GetAt(0)) + 10) * nBase;
			nBase *= 16;
			continue;
		}
		nPos = -nPos;
		break;
	}
	*((LONGLONG*)lParam) = nPos = (wParam) ? min(max(nPos, m_nMin), m_nMax) : nPos;
	return 0;
}

LRESULT CNumberEdit::OnSetSel(WPARAM wParam, LPARAM lParam)
{
	SendMessage(EM_SETSEL, wParam, lParam);
	return TRUE;
}

LRESULT CNumberEdit::OnGetSel(WPARAM wParam, LPARAM lParam)
{
	DWORD  dwSel[2];

	SendMessage(EM_GETSEL, (WPARAM)& dwSel[0], (LPARAM)& dwSel[1]);
	*((INT*)wParam) = (INT)dwSel[0];
	*((INT*)lParam) = (INT)dwSel[1];
	return((dwSel[0] < dwSel[1]) ? TRUE : FALSE);
}

LRESULT CNumberEdit::OnCheck(WPARAM wParam, LPARAM lParam)
{
	LONGLONG  nPos;
	CString  szSign;
	CString  szNumber;
	CStringTools  cStringTools;

	nPos = GetPos(FALSE);
	GetWindowText(szNumber);
	szSign = cStringTools.ConvertIntToString(-1);
	return(!szNumber.IsEmpty() && szNumber != szSign.GetAt(0) && (!m_nDigits || ((szNumber.GetAt(0) == szSign.GetAt(0) && szNumber.GetLength() > (INT)m_nDigits) || (szNumber.GetAt(0) != szSign.GetAt(0) && szNumber.GetLength() == m_nDigits))) && nPos >= m_nMin && nPos <= m_nMax);
}

// Numberedit helpers
BOOL Numberedit_SetBase(CWnd* pCtrl, UINT nBase, UINT nDigits)
{
	return((BOOL)pCtrl->SendMessage(NEM_SETBASE, (WPARAM)nBase, (LPARAM)nDigits));
}

BOOL Numberedit_GetBase(CWnd* pCtrl, UINT& nBase, UINT& nDigits)
{
	return((BOOL)pCtrl->SendMessage(NEM_GETBASE, (WPARAM)& nBase, (LPARAM)& nDigits));
}

BOOL Numberedit_SetRange(CWnd* pCtrl, LONGLONG nMin, LONGLONG nMax)
{
	return((BOOL)pCtrl->SendMessage(NEM_SETRANGE, (WPARAM)& nMin, (LPARAM)& nMax));
}

BOOL Numberedit_GetRange(CWnd* pCtrl, LONGLONG& nMin, LONGLONG& nMax)
{
	return((BOOL)pCtrl->SendMessage(NEM_GETRANGE, (WPARAM)& nMin, (LPARAM)& nMax));
}

BOOL Numberedit_SetPos(CWnd* pCtrl, LONGLONG nPos, BOOL bNotify)
{
	return((BOOL)pCtrl->SendMessage(NEM_SETPOS, bNotify, (LPARAM)& nPos));
}

LONGLONG Numberedit_GetPos(CWnd* pCtrl, BOOL bLimits)
{
	LONGLONG  nPos;

	pCtrl->SendMessage(NEM_GETPOS, bLimits, (LPARAM)& nPos);
	return nPos;
}

BOOL Numberedit_SetSel(CWnd* pCtrl, INT nStartPos, INT nStopPos)
{
	return((BOOL)pCtrl->SendMessage(NEM_SETSEL, nStartPos, nStopPos));
}

BOOL Numberedit_GetSel(CWnd* pCtrl, INT& nStartPos, INT& nStopPos)
{
	return((BOOL)pCtrl->SendMessage(NEM_GETSEL, (WPARAM)& nStartPos, (LPARAM)& nStopPos));
}
DWORD Numberedit_GetSel(CWnd* pCtrl)
{
	return((DWORD)pCtrl->SendMessage(EM_GETSEL));
}

BOOL Numberedit_Check(CWnd* pCtrl)
{
	return((BOOL)pCtrl->SendMessage(NEM_CHECK));
}


/////////////////////////////////////////////////////////////////////////////
// CResourceNumberEdit

IMPLEMENT_DYNCREATE(CResourceNumberEdit, CNumberEdit)

WNDPROC CResourceNumberEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceNumberEdit::CResourceNumberEdit(HWND hWnd) : CNumberEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceNumberEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceNumberEdit* pResourceNumberEdit;

	if ((pResourceNumberEdit = new CResourceNumberEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceNumberEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceNumberEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceNumberEdit, CNumberEdit)
	//{{AFX_MSG_MAP(CResourceNumberEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceNumberEdit message handlers

BOOL CResourceNumberEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LOWERCASE | ES_UPPERCASE | ES_NUMBER | ES_PASSWORD | ES_READONLY | ES_WANTRETURN)) | ES_MULTILINE), HIWORD(lpCreateStruct->style)) | WS_CHILD));
	return CNumberEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CTextEdit

IMPLEMENT_DYNCREATE(CTextEdit, CEdit)

CTextEdit::CTextEdit() : CEdit()
{
	m_dwStyle = 0;
	m_bAutoCompletion = TRUE;
}

BOOL CTextEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CEdit::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NUMBER | ES_LOWERCASE | ES_UPPERCASE | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_PASSWORD | ES_READONLY | ES_WANTRETURN)) | ES_MULTILINE), HIWORD(dwStyle)) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CTextEdit::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CTextEdit  cTextEdit;

	if ((pClass = cTextEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName && GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceTextEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceTextEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceTextEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CTextEdit::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CTextEdit  cTextEdit;

	if ((pClass = cTextEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

VOID CTextEdit::EnableAutoCompletion(BOOL bEnable)
{
	m_bAutoCompletion = bEnable;
}

BOOL CTextEdit::IsAutoCompletionEnabled() CONST
{
	return m_bAutoCompletion;
}

VOID CTextEdit::Format()
{
	CWnd* pWnd;
	CRect  rTextEdit;
	CRect  rFormatArea;

	for (; (pWnd = GetParent()) && (pWnd->IsKindOf(RUNTIME_CLASS(CSpinBox)) || pWnd->IsKindOf(RUNTIME_CLASS(CTimeSpinBox))); )
	{
		SetMargins(0, 0);
		return;
	}
	GetRect(rFormatArea);
	GetClientRect(rTextEdit);
	rFormatArea.SetRect(rFormatArea.left, (rTextEdit.Height() - rFormatArea.Height()) / 2 + 1, rFormatArea.right, (rTextEdit.Height() - rFormatArea.Height()) / 2 + rFormatArea.Height() + 1);
	SetRect(rFormatArea);
}

BEGIN_MESSAGE_MAP(CTextEdit, CEdit)
	//{{AFX_MSG_MAP(CTextEdit)
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
// CTextEdit message handlers

BOOL CTextEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!IsThemeActive())
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | ((lpCreateStruct->style & WS_BORDER) ? WS_EX_CLIENTEDGE : 0));
		SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~(lpCreateStruct->style & WS_BORDER));
	}
	return CEdit::OnNcCreate(lpCreateStruct);
}

void CTextEdit::OnSize(UINT nType, int cx, int cy)
{
	Default();
	Format();
}

void CTextEdit::OnEnable(BOOL bEnable)
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

UINT CTextEdit::OnGetDlgCode()
{
	return CEdit::OnGetDlgCode() | DLGC_WANTARROWS | DLGC_WANTALLKEYS | DLGC_WANTCHARS;
}

void CTextEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	CSpinBox* pSpinBox;
	CTimeSpinBox* pTimeSpinBox;

	if ((pSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CSpinBox))) ? (CSpinBox*)GetParent() : (CSpinBox*)NULL)) pSpinBox->UpdateUI();
	if ((pTimeSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CTimeSpinBox))) ? (CTimeSpinBox*)GetParent() : (CTimeSpinBox*)NULL)) pTimeSpinBox->UpdateUI();
	CEdit::OnMouseMove(nFlags, point);
}

void CTextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nPos;
	CWnd* pWnd[2];

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
	default:
	{ nPos = 0;
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
		if ((GetParent()->GetStyle() & WS_TABSTOP) && LOWORD(GetSel()) == HIWORD(GetSel()) && ((nChar == VK_LEFT && !LOWORD(GetSel())) || (nChar == VK_RIGHT && LOWORD(GetSel()) == GetWindowTextLength())))
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
			for (pWnd[0] = this; !pWnd[0]->IsKindOf(RUNTIME_CLASS(CDialogEx)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CMFCPropertySheet)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CMFCPropertyPage)) && !pWnd[0]->IsKindOf(RUNTIME_CLASS(CView)); )
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

void CTextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
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

void CTextEdit::OnKillFocus(CWnd* pNewWnd)
{
	if (IsAutoCompletionEnabled() && !Check()) SetPos(GetPos(), TRUE);
	CEdit::OnKillFocus(pNewWnd);
}

LRESULT CTextEdit::OnFont(WPARAM wParam, LPARAM lParam)
{
	Default();
	Format();
	return 0;
}

LRESULT CTextEdit::OnText(WPARAM wParam, LPARAM lParam)
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

LRESULT CTextEdit::OnAddText(WPARAM wParam, LPARAM lParam)
{
	return m_szNames.Add((LPCTSTR)lParam);
}

LRESULT CTextEdit::OnInsertText(WPARAM wParam, LPARAM lParam)
{
	m_szNames.InsertAt(wParam, (LPCTSTR)lParam, 1);
	return 0;
}

LRESULT CTextEdit::OnFindText(WPARAM wParam, LPARAM lParam)
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

LRESULT CTextEdit::OnSelectText(WPARAM wParam, LPARAM lParam)
{
	INT  nPos;

	if ((nPos = FindText((INT)wParam, (LPCTSTR)lParam)) >= 0)
	{
		SetPos(nPos, TRUE);
		return TRUE;
	}
	return FALSE;
}

LRESULT CTextEdit::OnDeleteText(WPARAM wParam, LPARAM lParam)
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

LRESULT CTextEdit::OnResetText(WPARAM wParam, LPARAM lParam)
{
	m_szNames.RemoveAll();
	SetWindowText(EMPTYSTRING);
	return 0;
}

LRESULT CTextEdit::OnSetPos(WPARAM wParam, LPARAM lParam)
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

LRESULT CTextEdit::OnGetPos(WPARAM wParam, LPARAM lParam)
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

LRESULT CTextEdit::OnSetSel(WPARAM wParam, LPARAM lParam)
{
	SendMessage(EM_SETSEL, wParam, lParam);
	return TRUE;
}

LRESULT CTextEdit::OnGetSel(WPARAM wParam, LPARAM lParam)
{
	INT* nSel[2];
	DWORD  dwSel[2];

	SendMessage(EM_GETSEL, (WPARAM)& dwSel[0], (LPARAM)& dwSel[1]);
	*(nSel[0] = (LPINT)wParam) = (INT)dwSel[0];
	*(nSel[1] = (LPINT)lParam) = (INT)dwSel[1];
	return 0;
}

LRESULT CTextEdit::OnCheck(WPARAM wParam, LPARAM lParam)
{
	CString  szText;

	GetWindowText(szText);
	return((FindText(0, szText) >= 0) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CResourceTextEdit

IMPLEMENT_DYNCREATE(CResourceTextEdit, CTextEdit)

WNDPROC CResourceTextEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceTextEdit::CResourceTextEdit(HWND hWnd) : CTextEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceTextEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceTextEdit* pResourceTextEdit;

	if ((pResourceTextEdit = new CResourceTextEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceTextEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceTextEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceTextEdit, CTextEdit)
	//{{AFX_MSG_MAP(CResourceTextEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceTextEdit message handlers

BOOL CResourceTextEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NUMBER | ES_LOWERCASE | ES_UPPERCASE | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_PASSWORD | ES_READONLY | ES_WANTRETURN)) | ES_MULTILINE), HIWORD(lpCreateStruct->style)) | WS_CHILD));
	return CTextEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CDPLCodeEdit

IMPLEMENT_DYNCREATE(CDPLCodeEdit, CRichEditCtrl)

CDPLCodeEdit::CDPLCodeEdit() : CRichEditCtrl()
{
	m_nType = DPLCODEEDIT_TYPE_DEFAULT;
	m_dwStyle = 0;
	m_bSelection = TRUE;
}

BOOL CDPLCodeEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CRichEditCtrl::Create((m_dwStyle = dwStyle) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CDPLCodeEdit::RegisterClass()
{
	CString  szClass[2];
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CDPLCodeEdit  cDPLCodeEdit;

	if ((pClass = cDPLCodeEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass[0] = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass[0].GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass[0].ReleaseBuffer();
#endif
		if (GetClassInfo((HINSTANCE)NULL, RICHEDIT_CLASS, &sWndClass))
		{
			CResourceDPLCodeEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass[1] = szClass[0].Mid(1)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass[1];
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceDPLCodeEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceDPLCodeEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CDPLCodeEdit::UnregisterClass()
{
	CString  szClass;
	CRuntimeClass* pClass;
	CDPLCodeEdit  cDPLCodeEdit;

	if ((pClass = cDPLCodeEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass.ReleaseBuffer();
#endif
		return ::UnregisterClass(szClass.Mid(1), GetModuleHandle((LPCTSTR)NULL));
	}
	return FALSE;
}

VOID CDPLCodeEdit::SetRenderType(UINT nType)
{
	if (m_nType != nType)
	{
		m_nType = nType;
		RenderCode();
	}
}

UINT CDPLCodeEdit::GetRenderType() CONST
{
	return m_nType;
}

VOID CDPLCodeEdit::RenderCode()
{
	RenderCode(this, CCustomControls::GetCustomControlFont(this), m_nType, m_bSelection);
}
VOID CDPLCodeEdit::RenderCode(CRichEditCtrl* pEdit, CFont* pFont, UINT nType, BOOL bSelection)
{
	INT  nPos;
	INT  nCount;
	INT  nLength;
	INT  nKeyword;
	LONG  lFreezeCount;
	LONG  nSelPos[2];
	LPTSTR  pszPos;
	LPTSTR  pszName;
	LPTSTR  pszQuote;
	LPTSTR  pszKeyword;
	LPTSTR  pszComment[3];
	LPTSTR  pszCodeBuffer;
	IRichEditOle* pIRichEditOle;
	ITextDocument* pITextDocument;
	CHARFORMAT2  cFormat[5];
	PARAFORMAT2  cParagraph;
	CFontTools  cFontTools;
	LOGFONT  lfFont;

	if ((pIRichEditOle = (IsWindow(pEdit->GetSafeHwnd())) ? pEdit->GetIRichEditOle() : (IRichEditOle*)NULL))
	{
		if (SUCCEEDED(pIRichEditOle->QueryInterface(IID_IDPLCodeDocument, (LPVOID*)& pITextDocument)))
		{
			pFont->GetLogFont(&lfFont);
			pEdit->GetSel(nSelPos[0], nSelPos[1]);
			pITextDocument->Freeze(&lFreezeCount);
			pITextDocument->Undo(tomSuspend, (long*)NULL);
			pITextDocument->Redo(tomSuspend, (long*)NULL);
			cFormat[0].cbSize = sizeof(cFormat[0]);
			cFormat[1].cbSize = sizeof(cFormat[1]);
			cFormat[2].cbSize = sizeof(cFormat[2]);
			cFormat[3].cbSize = sizeof(cFormat[3]);
			cFormat[4].cbSize = sizeof(cFormat[4]);
			cFormat[0].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[1].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[2].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[3].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[4].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			_tcscpy_s(cFormat[0].szFaceName, sizeof(cFormat[0].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[1].szFaceName, sizeof(cFormat[1].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[2].szFaceName, sizeof(cFormat[2].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[3].szFaceName, sizeof(cFormat[3].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[4].szFaceName, sizeof(cFormat[4].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			cFormat[0].dwEffects = CFE_AUTOCOLOR;
			cFormat[1].dwEffects = CFE_BOLD;
			cFormat[2].dwEffects = 0;
			cFormat[3].dwEffects = 0;
			cFormat[4].dwEffects = 0;
			cFormat[0].crTextColor = RGB(0, 0, 0);
			cFormat[1].crTextColor = RGB(0, 0, 128);
			cFormat[2].crTextColor = RGB(255, 0, 0);
			cFormat[3].crTextColor = RGB(0, 0, 255);
			cFormat[4].crTextColor = RGB(0, 128, 0);
			cFormat[0].yHeight = cFormat[1].yHeight = cFormat[2].yHeight = cFormat[3].yHeight = cFormat[4].yHeight = 20 * cFontTools.QueryPoints(&lfFont);
			cFormat[0].yOffset = 0;
			cFormat[1].yOffset = 0;
			cFormat[2].yOffset = 0;
			cFormat[3].yOffset = 0;
			cFormat[4].yOffset = 0;
			if ((pszCodeBuffer = (LPTSTR)GlobalAlloc(GPTR, ((SIZE_T)pEdit->GetWindowTextLength() + 1) * sizeof(TCHAR))))
			{
				for (cParagraph.cbSize = sizeof(cParagraph), cParagraph.dwMask = PFM_SPACEBEFORE | PFM_SPACEAFTER, cParagraph.dySpaceBefore = cParagraph.dySpaceAfter = 0, RenderCode(pEdit, 0, -1, &cFormat[0], &cParagraph), pEdit->GetWindowText(pszCodeBuffer, pEdit->GetWindowTextLength() + 1); (pszPos = _tcsstr(pszCodeBuffer, CString(CR))); )
				{
					for (nCount = 1; (pszPos[0] = pszPos[nCount]) != (TCHAR)EOS; )
					{
						nCount = ((++pszPos)[nCount] == CR) ? (nCount + 1) : nCount;
						continue;
					}
					break;
				}
				if (nType == DPLCODEEDIT_TYPE_DEFAULT)
				{
					for (nKeyword = MINDERIVEDPARAMETERLANGUAGEKEYWORD; nKeyword <= MAXDERIVEDPARAMETERLANGUAGEKEYWORD; nKeyword++)
					{
						for (nPos = 0, nLength = lstrlen(pszCodeBuffer); nPos < nLength; )
						{
							if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], STRING(nKeyword))))
							{
								for (; (lstrlen(pszKeyword) == nLength || (!_istalnum(pszKeyword[-1]) && pszKeyword[-1] != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SUBSTITUTE))) && !_istalnum(pszKeyword[lstrlen(STRING(nKeyword))]) && pszKeyword[lstrlen(STRING(nKeyword))] != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SUBSTITUTE); )
								{
									RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + lstrlen(STRING(nKeyword))), &cFormat[1]);
									break;
								}
								for (nPos = (INT)((pszKeyword - pszCodeBuffer) + lstrlen(STRING(nKeyword))); nKeyword == IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE; )
								{
									for (pszName = pszKeyword + lstrlen(STRING(nKeyword)); _istspace(pszName[0]) || pszName[0] == TAB; )
									{
										pszName++;
										continue;
									}
									for (nCount = 0; nCount < lstrlen(pszName); nCount++)
									{
										if (_istspace(pszName[nCount]) || pszName[nCount] == TAB || pszName[nCount] == EOL) break;
										continue;
									}
									RenderCode(pEdit, (INT)(pszName - pszCodeBuffer), (INT)((pszName - pszCodeBuffer) + nCount), &cFormat[2]);
									break;
								}
								continue;
							}
							break;
						}
					}
				}
				if (nType == DPLCODEEDIT_TYPE_DEFAULT || nType == DPLCODEEDIT_TYPE_PLAIN)
				{
					for (nKeyword = MINDERIVEDPARAMETERLANGUAGEEXTENDEDKEYWORD, nLength = lstrlen(pszCodeBuffer); nKeyword <= MAXDERIVEDPARAMETERLANGUAGEEXTENDEDKEYWORD; nKeyword++)
					{
						for (nPos = 0; nPos < nLength; )
						{
							if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], STRING(nKeyword))))
							{
								for (; (lstrlen(pszKeyword) == nLength || (!_istalnum(pszKeyword[-1]) && pszKeyword[-1] != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SUBSTITUTE))) && !_istalnum(pszKeyword[lstrlen(STRING(nKeyword))]) && pszKeyword[lstrlen(STRING(nKeyword))] != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SUBSTITUTE); )
								{
									RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + lstrlen(STRING(nKeyword))), &cFormat[3]);
									break;
								}
								nPos = (INT)((pszKeyword - pszCodeBuffer) + lstrlen(STRING(nKeyword)));
								continue;
							}
							break;
						}
					}
					for (nPos = 0; nPos < nLength; )
					{
						if ((pszQuote = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_STRINGQUOTE))))
						{
							for (nCount = lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_STRINGQUOTE)); (pszQuote - pszCodeBuffer) + nCount < nLength; nCount++)
							{
								if (pszQuote[nCount] == STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_STRINGQUOTE))
								{
									nCount++;
									break;
								}
								if (pszQuote[nCount] == EOL) break;
							}
							RenderCode(pEdit, (INT)(pszQuote - pszCodeBuffer), (INT)(pszQuote - pszCodeBuffer + nCount), &cFormat[0]);
							nPos = (INT)((pszQuote - pszCodeBuffer) + nCount);
							continue;
						}
						break;
					}
					for (nPos = 0; nPos < nLength; )
					{
						if ((pszComment[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_LINECOMMENTS))))
						{
							for (nCount = lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_LINECOMMENTS)); (pszComment[0] - pszCodeBuffer) + nCount < nLength; nCount++)
							{
								if (pszComment[0][nCount] == EOL) break;
								continue;
							}
							RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), (INT)(pszComment[0] - pszCodeBuffer + nCount), &cFormat[4]);
							nPos = (INT)((pszComment[0] - pszCodeBuffer) + nCount);
							continue;
						}
						break;
					}
					for (nPos = 0, pszComment[0] = pszComment[1] = (LPTSTR)NULL; nPos < nLength; )
					{
						if ((pszComment[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_BEGINCOMMENTS))))
						{
							for (pszComment[2] = _tcsstr(&pszCodeBuffer[(!pszComment[1]) ? ((pszComment[0] - pszCodeBuffer) + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_BEGINCOMMENTS))) : (pszComment[1] - pszCodeBuffer)], STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_ENDCOMMENTS)); !pszComment[2]; )
							{
								RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), -1, &cFormat[4]);
								nPos = nLength;
								break;
							}
							if (nPos < nLength)
							{
								RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), (INT)((pszComment[2] - pszCodeBuffer) + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_ENDCOMMENTS))), &cFormat[4]);
								nPos = (INT)((pszComment[0] - pszCodeBuffer) + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_BEGINCOMMENTS)));
								pszComment[1] = pszComment[2] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_ENDCOMMENTS));
								continue;
							}
						}
						break;
					}
				}
				if (nType == DPLCODEEDIT_TYPE_OL)
				{
					for (nKeyword = MINDERIVEDPARAMETEROLEXTENDEDKEYWORD, nLength = lstrlen(pszCodeBuffer); nKeyword <= MAXDERIVEDPARAMETEROLEXTENDEDKEYWORD; nKeyword++)
					{
						for (nPos = 0; nPos < nLength; )
						{
							if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], STRING(nKeyword))))
							{
								for (; (lstrlen(pszKeyword) == nLength || (!_istalnum(pszKeyword[-1]) && pszKeyword[-1] != STRINGCHAR(IDS_DERIVEDPARAMETER_OL_SYMBOL_SUBSTITUTE))) && !_istalnum(pszKeyword[lstrlen(STRING(nKeyword))]) && pszKeyword[lstrlen(STRING(nKeyword))] != STRINGCHAR(IDS_DERIVEDPARAMETER_OL_SYMBOL_SUBSTITUTE); )
								{
									RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + lstrlen(STRING(nKeyword))), &cFormat[3]);
									break;
								}
								nPos = (INT)((pszKeyword - pszCodeBuffer) + lstrlen(STRING(nKeyword)));
								continue;
							}
							break;
						}
					}
					for (nPos = 0; nPos < nLength; )
					{
						if ((pszQuote = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_DERIVEDPARAMETER_OL_SYMBOL_STRINGQUOTE))))
						{
							for (nCount = lstrlen(STRING(IDS_DERIVEDPARAMETER_OL_SYMBOL_STRINGQUOTE)); (pszQuote - pszCodeBuffer) + nCount < nLength; nCount++)
							{
								if (pszQuote[nCount] == STRINGCHAR(IDS_DERIVEDPARAMETER_OL_SYMBOL_STRINGQUOTE))
								{
									nCount++;
									break;
								}
								if (pszQuote[nCount] == EOL) break;
							}
							RenderCode(pEdit, (INT)(pszQuote - pszCodeBuffer), (INT)(pszQuote - pszCodeBuffer + nCount), &cFormat[0]);
							nPos = (INT)((pszQuote - pszCodeBuffer) + nCount);
							continue;
						}
						break;
					}
					for (nPos = 0; nPos < nLength; )
					{
						if ((pszComment[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_DERIVEDPARAMETER_OL_SYMBOL_LINECOMMENTS))))
						{
							for (nCount = lstrlen(STRING(IDS_DERIVEDPARAMETER_OL_SYMBOL_LINECOMMENTS)); (pszComment[0] - pszCodeBuffer) + nCount < nLength; nCount++)
							{
								if (pszComment[0][nCount] == EOL) break;
								continue;
							}
							RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), (INT)(pszComment[0] - pszCodeBuffer + nCount), &cFormat[4]);
							nPos = (INT)((pszComment[0] - pszCodeBuffer) + nCount);
							continue;
						}
						break;
					}
				}
				GlobalFree(pszCodeBuffer);
			}
			for (; bSelection; )
			{
				pEdit->SendMessage(EM_SETSEL, nSelPos[0], nSelPos[1]);
				break;
			}
			pITextDocument->Undo(tomResume, (long*)NULL);
			pITextDocument->Redo(tomResume, (long*)NULL);
			pITextDocument->Unfreeze(&lFreezeCount);
			pITextDocument->Release();
		}
		pIRichEditOle->Release();
	}
}
VOID CDPLCodeEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}
VOID CDPLCodeEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETPARAFORMAT, (WPARAM)NULL, (LPARAM)pParagraph);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}

BEGIN_MESSAGE_MAP(CDPLCodeEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CDPLCodeEdit)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_CONTROL_REFLECT_EX(EN_CHANGE, OnEditchange)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDPLCodeEdit message handlers

int CDPLCodeEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) != -1)
	{
		SetEventMask(GetEventMask() | ENM_CHANGE | ENM_REQUESTRESIZE);
		RequestResize();
		return 0;
	}
	return -1;
}

LRESULT CDPLCodeEdit::OnNcHitTest(CPoint point)
{
	CRect  rEdit;
	SCROLLINFO  sScrollInfo[2];

	for (GetWindowRect(rEdit); GetScrollInfo(SB_HORZ, &sScrollInfo[0]) && GetScrollInfo(SB_VERT, &sScrollInfo[1]); )
	{
		if (sScrollInfo[0].nPage > 0 && CRect(rEdit.left, rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL), (sScrollInfo[1].nPage > 0) ? (rEdit.right - GetSystemMetrics(SM_CXVSCROLL)) : rEdit.right, rEdit.bottom).PtInRect(point)) return HTHSCROLL;
		if (sScrollInfo[1].nPage > 0 && CRect(rEdit.right - GetSystemMetrics(SM_CXVSCROLL), rEdit.top, rEdit.right, (sScrollInfo[0].nPage > 0) ? (rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL)) : rEdit.bottom).PtInRect(point)) return HTVSCROLL;
		break;
	}
	return CRichEditCtrl::OnNcHitTest(point);
}

BOOL CDPLCodeEdit::OnEditchange()
{
	RenderCode();
	return FALSE;
}

LRESULT CDPLCodeEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	for (m_bSelection = FALSE, lResult = Default(); TRUE; )
	{
		RenderCode();
		break;
	}
	m_bSelection = TRUE;
	return lResult;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceDPLCodeEdit

IMPLEMENT_DYNCREATE(CResourceDPLCodeEdit, CDPLCodeEdit)

WNDPROC CResourceDPLCodeEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceDPLCodeEdit::CResourceDPLCodeEdit(HWND hWnd) : CDPLCodeEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceDPLCodeEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceDPLCodeEdit* pResourceDPLCodeEdit;

	if ((pResourceDPLCodeEdit = new CResourceDPLCodeEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceDPLCodeEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceDPLCodeEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceDPLCodeEdit, CDPLCodeEdit)
	//{{AFX_MSG_MAP(CResourceDPLCodeEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceDPLCodeEdit message handlers

BOOL CResourceDPLCodeEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (m_dwStyle = lpCreateStruct->style) | WS_CHILD));
	return CDPLCodeEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CMDLCodeEdit

IMPLEMENT_DYNCREATE(CMDLCodeEdit, CRichEditCtrl)

CMDLCodeEdit::CMDLCodeEdit() : CRichEditCtrl()
{
	m_dwStyle = 0;
	m_bSelection = TRUE;
}

BOOL CMDLCodeEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CRichEditCtrl::Create((m_dwStyle = dwStyle) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CMDLCodeEdit::RegisterClass()
{
	CString  szClass[2];
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CMDLCodeEdit  cMDLCodeEdit;

	if ((pClass = cMDLCodeEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass[0] = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass[0].GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass[0].ReleaseBuffer();
#endif
		if (GetClassInfo((HINSTANCE)NULL, RICHEDIT_CLASS, &sWndClass))
		{
			CResourceMDLCodeEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass[1] = szClass[0].Mid(1)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass[1];
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceMDLCodeEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceMDLCodeEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CMDLCodeEdit::UnregisterClass()
{
	CString  szClass;
	CRuntimeClass* pClass;
	CMDLCodeEdit  cMDLCodeEdit;

	if ((pClass = cMDLCodeEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass.ReleaseBuffer();
#endif
		return ::UnregisterClass(szClass.Mid(1), GetModuleHandle((LPCTSTR)NULL));
	}
	return FALSE;
}

VOID CMDLCodeEdit::RenderCode()
{
	RenderCode(this, CCustomControls::GetCustomControlFont(this), m_bSelection);
}
VOID CMDLCodeEdit::RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection)
{
	INT  nPos;
	INT  nCount;
	INT  nLength;
	INT  nKeyword;
	LONG  lFreezeCount;
	LONG  nSelPos[2];
	LPTSTR  pszPos;
	LPTSTR  pszName;
	LPTSTR  pszQuote;
	LPTSTR  pszKeyword;
	LPTSTR  pszComment[3];
	LPTSTR  pszCodeBuffer;
	IRichEditOle* pIRichEditOle;
	ITextDocument* pITextDocument;
	CHARFORMAT2  cFormat[5];
	PARAFORMAT2  cParagraph;
	CFontTools  cFontTools;
	LOGFONT  lfFont;

	if ((pIRichEditOle = (IsWindow(pEdit->GetSafeHwnd())) ? pEdit->GetIRichEditOle() : (IRichEditOle*)NULL))
	{
		if (SUCCEEDED(pIRichEditOle->QueryInterface(IID_IMDLCodeDocument, (LPVOID*)& pITextDocument)))
		{
			pFont->GetLogFont(&lfFont);
			pEdit->GetSel(nSelPos[0], nSelPos[1]);
			pITextDocument->Freeze(&lFreezeCount);
			pITextDocument->Undo(tomSuspend, (long*)NULL);
			pITextDocument->Redo(tomSuspend, (long*)NULL);
			cFormat[0].cbSize = sizeof(cFormat[0]);
			cFormat[1].cbSize = sizeof(cFormat[1]);
			cFormat[2].cbSize = sizeof(cFormat[2]);
			cFormat[3].cbSize = sizeof(cFormat[3]);
			cFormat[4].cbSize = sizeof(cFormat[4]);
			cFormat[0].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[1].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[2].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[3].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[4].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			_tcscpy_s(cFormat[0].szFaceName, sizeof(cFormat[0].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[1].szFaceName, sizeof(cFormat[1].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[2].szFaceName, sizeof(cFormat[2].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[3].szFaceName, sizeof(cFormat[3].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[4].szFaceName, sizeof(cFormat[4].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			cFormat[0].dwEffects = CFE_AUTOCOLOR;
			cFormat[1].dwEffects = CFE_BOLD;
			cFormat[2].dwEffects = 0;
			cFormat[3].dwEffects = 0;
			cFormat[4].dwEffects = 0;
			cFormat[0].crTextColor = RGB(0, 0, 0);
			cFormat[1].crTextColor = RGB(0, 0, 128);
			cFormat[2].crTextColor = RGB(255, 0, 0);
			cFormat[3].crTextColor = RGB(0, 0, 255);
			cFormat[4].crTextColor = RGB(0, 128, 0);
			cFormat[0].yHeight = cFormat[1].yHeight = cFormat[2].yHeight = cFormat[3].yHeight = cFormat[4].yHeight = 20 * cFontTools.QueryPoints(&lfFont);
			cFormat[0].yOffset = 0;
			cFormat[1].yOffset = 0;
			cFormat[2].yOffset = 0;
			cFormat[3].yOffset = 0;
			cFormat[4].yOffset = 0;
			if ((pszCodeBuffer = (LPTSTR)GlobalAlloc(GPTR, ((SIZE_T)pEdit->GetWindowTextLength() + 1) * sizeof(TCHAR))))
			{
				for (cParagraph.cbSize = sizeof(cParagraph), cParagraph.dwMask = PFM_SPACEBEFORE | PFM_SPACEAFTER, cParagraph.dySpaceBefore = cParagraph.dySpaceAfter = 0, RenderCode(pEdit, 0, -1, &cFormat[0], &cParagraph), pEdit->GetWindowText(pszCodeBuffer, pEdit->GetWindowTextLength() + 1); (pszPos = _tcsstr(pszCodeBuffer, CString(CR))); )
				{
					for (nCount = 1; (pszPos[0] = pszPos[nCount]) != (TCHAR)EOS; )
					{
						nCount = ((++pszPos)[nCount] == CR) ? (nCount + 1) : nCount;
						continue;
					}
					break;
				}
				for (nKeyword = MINMIMICSDESCRIPTIONLANGUAGEKEYWORD; nKeyword <= MAXMIMICSDESCRIPTIONLANGUAGEKEYWORD; nKeyword++)
				{
					for (nPos = 0, nLength = lstrlen(pszCodeBuffer); nPos < nLength; )
					{
						if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], STRING(nKeyword))))
						{
							for (; (lstrlen(pszKeyword) == nLength || (!_istalnum(pszKeyword[-1]) && pszKeyword[-1] != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SUBSTITUTE))) && !_istalnum(pszKeyword[lstrlen(STRING(nKeyword))]) && pszKeyword[lstrlen(STRING(nKeyword))] != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SUBSTITUTE); )
							{
								RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + lstrlen(STRING(nKeyword))), &cFormat[1]);
								break;
							}
							for (nPos = (INT)((pszKeyword - pszCodeBuffer) + lstrlen(STRING(nKeyword))); nKeyword == IDS_MIMICSDESCRIPTIONLANGUAGE_KEYWORD_PROCEDURE; )
							{
								for (pszName = pszKeyword + lstrlen(STRING(nKeyword)); _istspace(pszName[0]) || pszName[0] == TAB; )
								{
									pszName++;
									continue;
								}
								if (pszName[0] == STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER) && lstrlen(pszName) > lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER)) && _tcscspn(pszName + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER)), STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER)) < (size_t)lstrlen(pszName) - 1)
								{
									RenderCode(pEdit, (INT)(pszName - pszCodeBuffer), (INT)((pszName - pszCodeBuffer) + _tcscspn(pszName + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER)), STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER)) + 2 * (size_t)lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_DELIMITER))), &cFormat[2]);
									break;
								}
								break;
							}
							continue;
						}
						break;
					}
				}
				for (nKeyword = MINMIMICSDESCRIPTIONLANGUAGEEXTENDEDKEYWORD, nLength = lstrlen(pszCodeBuffer); nKeyword <= MAXMIMICSDESCRIPTIONLANGUAGEEXTENDEDKEYWORD; nKeyword++)
				{
					for (nPos = 0; nPos < nLength; )
					{
						if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], STRING(nKeyword))))
						{
							for (; (lstrlen(pszKeyword) == nLength || (!_istalnum(pszKeyword[-1]) && pszKeyword[-1] != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SUBSTITUTE))) && !_istalnum(pszKeyword[lstrlen(STRING(nKeyword))]) && pszKeyword[lstrlen(STRING(nKeyword))] != STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_SUBSTITUTE); )
							{
								RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + lstrlen(STRING(nKeyword))), &cFormat[3]);
								break;
							}
							nPos = (INT)((pszKeyword - pszCodeBuffer) + lstrlen(STRING(nKeyword)));
							continue;
						}
						break;
					}
				}
				for (nPos = 0; nPos < nLength; )
				{
					if ((pszQuote = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_STRINGQUOTE))))
					{
						for (nCount = lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_STRINGQUOTE)); (pszQuote - pszCodeBuffer) + nCount < nLength; nCount++)
						{
							if (pszQuote[nCount] == STRINGCHAR(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_STRINGQUOTE))
							{
								nCount++;
								break;
							}
							if (pszQuote[nCount] == EOL) break;
						}
						RenderCode(pEdit, (INT)(pszQuote - pszCodeBuffer), (INT)(pszQuote - pszCodeBuffer + nCount), &cFormat[0]);
						nPos = (INT)((pszQuote - pszCodeBuffer) + nCount);
						continue;
					}
					break;
				}
				for (nPos = 0; nPos < nLength; )
				{
					if ((pszComment[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_LINECOMMENTS))))
					{
						for (nCount = lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_LINECOMMENTS)); (pszComment[0] - pszCodeBuffer) + nCount < nLength; nCount++)
						{
							if (pszComment[0][nCount] == EOL) break;
							continue;
						}
						RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), (INT)(pszComment[0] - pszCodeBuffer + nCount), &cFormat[4]);
						nPos = (INT)((pszComment[0] - pszCodeBuffer) + nCount);
						continue;
					}
					break;
				}
				for (nPos = 0, pszComment[0] = pszComment[1] = (LPTSTR)NULL; nPos < nLength; )
				{
					if ((pszComment[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_BEGINCOMMENTS))))
					{
						for (pszComment[2] = _tcsstr(&pszCodeBuffer[(!pszComment[1]) ? ((pszComment[0] - pszCodeBuffer) + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_BEGINCOMMENTS))) : (pszComment[1] - pszCodeBuffer)], STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_ENDCOMMENTS)); !pszComment[2]; )
						{
							RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), -1, &cFormat[4]);
							nPos = nLength;
							break;
						}
						if (nPos < nLength)
						{
							RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), (INT)((pszComment[2] - pszCodeBuffer) + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_ENDCOMMENTS))), &cFormat[4]);
							nPos = (INT)((pszComment[0] - pszCodeBuffer) + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_BEGINCOMMENTS)));
							pszComment[1] = pszComment[2] + lstrlen(STRING(IDS_MIMICSDESCRIPTIONLANGUAGE_SYMBOL_ENDCOMMENTS));
							continue;
						}
					}
					break;
				}
				GlobalFree(pszCodeBuffer);
			}
			for (; bSelection; )
			{
				pEdit->SendMessage(EM_SETSEL, nSelPos[0], nSelPos[1]);
				break;
			}
			pITextDocument->Undo(tomResume, (long*)NULL);
			pITextDocument->Redo(tomResume, (long*)NULL);
			pITextDocument->Unfreeze(&lFreezeCount);
			pITextDocument->Release();
		}
		pIRichEditOle->Release();
	}
}
VOID CMDLCodeEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}
VOID CMDLCodeEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETPARAFORMAT, (WPARAM)NULL, (LPARAM)pParagraph);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}

BEGIN_MESSAGE_MAP(CMDLCodeEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CMDLCodeEdit)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_CONTROL_REFLECT_EX(EN_CHANGE, OnEditchange)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDLCodeEdit message handlers

int CMDLCodeEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) != -1)
	{
		SetEventMask(GetEventMask() | ENM_CHANGE | ENM_REQUESTRESIZE);
		RequestResize();
		return 0;
	}
	return -1;
}

LRESULT CMDLCodeEdit::OnNcHitTest(CPoint point)
{
	CRect  rEdit;
	SCROLLINFO  sScrollInfo[2];

	for (GetWindowRect(rEdit); GetScrollInfo(SB_HORZ, &sScrollInfo[0]) && GetScrollInfo(SB_VERT, &sScrollInfo[1]); )
	{
		if (sScrollInfo[0].nPage > 0 && CRect(rEdit.left, rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL), (sScrollInfo[1].nPage > 0) ? (rEdit.right - GetSystemMetrics(SM_CXVSCROLL)) : rEdit.right, rEdit.bottom).PtInRect(point)) return HTHSCROLL;
		if (sScrollInfo[1].nPage > 0 && CRect(rEdit.right - GetSystemMetrics(SM_CXVSCROLL), rEdit.top, rEdit.right, (sScrollInfo[0].nPage > 0) ? (rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL)) : rEdit.bottom).PtInRect(point)) return HTVSCROLL;
		break;
	}
	return CRichEditCtrl::OnNcHitTest(point);
}

BOOL CMDLCodeEdit::OnEditchange()
{
	RenderCode();
	return FALSE;
}

LRESULT CMDLCodeEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	for (m_bSelection = FALSE, lResult = Default(); TRUE; )
	{
		RenderCode();
		break;
	}
	m_bSelection = TRUE;
	return lResult;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceMDLCodeEdit

IMPLEMENT_DYNCREATE(CResourceMDLCodeEdit, CMDLCodeEdit)

WNDPROC CResourceMDLCodeEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceMDLCodeEdit::CResourceMDLCodeEdit(HWND hWnd) : CMDLCodeEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceMDLCodeEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceMDLCodeEdit* pResourceMDLCodeEdit;

	if ((pResourceMDLCodeEdit = new CResourceMDLCodeEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceMDLCodeEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceMDLCodeEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceMDLCodeEdit, CMDLCodeEdit)
	//{{AFX_MSG_MAP(CResourceMDLCodeEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceMDLCodeEdit message handlers

BOOL CResourceMDLCodeEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (m_dwStyle = lpCreateStruct->style) | WS_CHILD));
	return CMDLCodeEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CTPLCodeEdit

IMPLEMENT_DYNCREATE(CTPLCodeEdit, CRichEditCtrl)

CTPLCodeEdit::CTPLCodeEdit() : CRichEditCtrl()
{
	m_dwStyle = 0;
	m_bSelection = TRUE;
}

BOOL CTPLCodeEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CRichEditCtrl::Create((m_dwStyle = dwStyle) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CTPLCodeEdit::RegisterClass()
{
	CString  szClass[2];
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CTPLCodeEdit  cTPLCodeEdit;

	if ((pClass = cTPLCodeEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass[0] = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass[0].GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass[0].ReleaseBuffer();
#endif
		if (GetClassInfo((HINSTANCE)NULL, RICHEDIT_CLASS, &sWndClass))
		{
			CResourceTPLCodeEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass[1] = szClass[0].Mid(1)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass[1];
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceTPLCodeEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceTPLCodeEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CTPLCodeEdit::UnregisterClass()
{
	CString  szClass;
	CRuntimeClass* pClass;
	CTPLCodeEdit  cTPLCodeEdit;

	if ((pClass = cTPLCodeEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass.ReleaseBuffer();
#endif
		return ::UnregisterClass(szClass.Mid(1), GetModuleHandle((LPCTSTR)NULL));
	}
	return FALSE;
}

VOID CTPLCodeEdit::RenderCode()
{
	RenderCode(this, CCustomControls::GetCustomControlFont(this), m_bSelection);
}
VOID CTPLCodeEdit::RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection)
{
	INT  nPos;
	INT  nCount;
	INT  nLength;
	INT  nKeyword;
	LONG  lFreezeCount;
	LONG  nSelPos[2];
	LPTSTR  pszPos;
	LPTSTR  pszName;
	LPTSTR  pszQuote;
	LPTSTR  pszKeyword;
	LPTSTR  pszComment[3];
	LPTSTR  pszCodeBuffer;
	IRichEditOle* pIRichEditOle;
	ITextDocument* pITextDocument;
	CHARFORMAT2  cFormat[5];
	PARAFORMAT2  cParagraph;
	CFontTools  cFontTools;
	LOGFONT  lfFont;

	if ((pIRichEditOle = (IsWindow(pEdit->GetSafeHwnd())) ? pEdit->GetIRichEditOle() : (IRichEditOle*)NULL))
	{
		if (SUCCEEDED(pIRichEditOle->QueryInterface(IID_ITPLCodeDocument, (LPVOID*)& pITextDocument)))
		{
			pFont->GetLogFont(&lfFont);
			pEdit->GetSel(nSelPos[0], nSelPos[1]);
			pITextDocument->Freeze(&lFreezeCount);
			pITextDocument->Undo(tomSuspend, (long*)NULL);
			pITextDocument->Redo(tomSuspend, (long*)NULL);
			cFormat[0].cbSize = sizeof(cFormat[0]);
			cFormat[1].cbSize = sizeof(cFormat[1]);
			cFormat[2].cbSize = sizeof(cFormat[2]);
			cFormat[3].cbSize = sizeof(cFormat[3]);
			cFormat[4].cbSize = sizeof(cFormat[4]);
			cFormat[0].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[1].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[2].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[3].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[4].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			_tcscpy_s(cFormat[0].szFaceName, sizeof(cFormat[0].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[1].szFaceName, sizeof(cFormat[1].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[2].szFaceName, sizeof(cFormat[2].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[3].szFaceName, sizeof(cFormat[3].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[4].szFaceName, sizeof(cFormat[4].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			cFormat[0].dwEffects = CFE_AUTOCOLOR;
			cFormat[1].dwEffects = CFE_BOLD;
			cFormat[2].dwEffects = 0;
			cFormat[3].dwEffects = 0;
			cFormat[4].dwEffects = 0;
			cFormat[0].crTextColor = RGB(0, 0, 0);
			cFormat[1].crTextColor = RGB(0, 0, 128);
			cFormat[2].crTextColor = RGB(255, 0, 0);
			cFormat[3].crTextColor = RGB(0, 0, 255);
			cFormat[4].crTextColor = RGB(0, 128, 0);
			cFormat[0].yHeight = cFormat[1].yHeight = cFormat[2].yHeight = cFormat[3].yHeight = cFormat[4].yHeight = 20 * cFontTools.QueryPoints(&lfFont);
			cFormat[0].yOffset = 0;
			cFormat[1].yOffset = 0;
			cFormat[2].yOffset = 0;
			cFormat[3].yOffset = 0;
			cFormat[4].yOffset = 0;
			if ((pszCodeBuffer = (LPTSTR)GlobalAlloc(GPTR, ((SIZE_T)pEdit->GetWindowTextLength() + 1) * sizeof(TCHAR))))
			{
				for (cParagraph.cbSize = sizeof(cParagraph), cParagraph.dwMask = PFM_SPACEBEFORE | PFM_SPACEAFTER, cParagraph.dySpaceBefore = cParagraph.dySpaceAfter = 0, RenderCode(pEdit, 0, -1, &cFormat[0], &cParagraph), pEdit->GetWindowText(pszCodeBuffer, pEdit->GetWindowTextLength() + 1); (pszPos = _tcsstr(pszCodeBuffer, CString(CR))); )
				{
					for (nCount = 1; (pszPos[0] = pszPos[nCount]) != (TCHAR)EOS; )
					{
						nCount = ((++pszPos)[nCount] == CR) ? (nCount + 1) : nCount;
						continue;
					}
					break;
				}
				for (nKeyword = (pEdit->GetStyle() & TPLS_EXPRESSION) ? (MAXTELECOMMANDPROCEDURELANGUAGEKEYWORD + 1) : MINTELECOMMANDPROCEDURELANGUAGEKEYWORD; nKeyword <= MAXTELECOMMANDPROCEDURELANGUAGEKEYWORD; nKeyword++)
				{
					for (nPos = 0, nLength = lstrlen(pszCodeBuffer); nPos < nLength; )
					{
						if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], STRING(nKeyword))))
						{
							for (; (lstrlen(pszKeyword) == nLength || (!_istalnum(pszKeyword[-1]) && pszKeyword[-1] != STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_SUBSTITUTE))) && !_istalnum(pszKeyword[lstrlen(STRING(nKeyword))]) && pszKeyword[lstrlen(STRING(nKeyword))] != STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_SUBSTITUTE); )
							{
								RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + lstrlen(STRING(nKeyword))), &cFormat[1]);
								break;
							}
							for (nPos = (INT)((pszKeyword - pszCodeBuffer) + lstrlen(STRING(nKeyword))); nKeyword == IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_PROCEDURE || nKeyword == IDS_TELECOMMANDPROCEDURELANGUAGE_KEYWORD_THREAD; )
							{
								for (pszName = pszKeyword + lstrlen(STRING(nKeyword)); _istspace(pszName[0]) || pszName[0] == TAB; )
								{
									pszName++;
									continue;
								}
								if (pszName[0] == STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_DELIMITER) && lstrlen(pszName) > lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_DELIMITER)) && _tcscspn(pszName + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_DELIMITER)), STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_DELIMITER)) < (size_t)lstrlen(pszName) - 1)
								{
									RenderCode(pEdit, (INT)(pszName - pszCodeBuffer), (INT)((pszName - pszCodeBuffer) + _tcscspn(pszName + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_DELIMITER)), STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_DELIMITER)) + 2 * (size_t)lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_DELIMITER))), &cFormat[2]);
									break;
								}
								break;
							}
							continue;
						}
						break;
					}
				}
				for (nKeyword = MINTELECOMMANDPROCEDURELANGUAGEEXTENDEDKEYWORD, nLength = lstrlen(pszCodeBuffer); nKeyword <= MAXTELECOMMANDPROCEDURELANGUAGEEXTENDEDKEYWORD; nKeyword++)
				{
					for (nPos = 0; nPos < nLength; )
					{
						if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], STRING(nKeyword))))
						{
							for (; (lstrlen(pszKeyword) == nLength || (!_istalnum(pszKeyword[-1]) && pszKeyword[-1] != STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_SUBSTITUTE))) && !_istalnum(pszKeyword[lstrlen(STRING(nKeyword))]) && pszKeyword[lstrlen(STRING(nKeyword))] != STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_SUBSTITUTE); )
							{
								RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + lstrlen(STRING(nKeyword))), &cFormat[3]);
								break;
							}
							nPos = (INT)((pszKeyword - pszCodeBuffer) + lstrlen(STRING(nKeyword)));
							continue;
						}
						break;
					}
				}
				for (nPos = 0; nPos < nLength; )
				{
					if ((pszQuote = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_STRINGQUOTE))))
					{
						for (nCount = lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_STRINGQUOTE)); (pszQuote - pszCodeBuffer) + nCount < nLength; nCount++)
						{
							if (pszQuote[nCount] == STRINGCHAR(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_STRINGQUOTE))
							{
								nCount++;
								break;
							}
							if (pszQuote[nCount] == EOL) break;
						}
						RenderCode(pEdit, (INT)(pszQuote - pszCodeBuffer), (INT)(pszQuote - pszCodeBuffer + nCount), &cFormat[0]);
						nPos = (INT)((pszQuote - pszCodeBuffer) + nCount);
						continue;
					}
					break;
				}
				for (nPos = 0; nPos < nLength; )
				{
					if ((pszComment[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_LINECOMMENTS))))
					{
						for (nCount = lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_LINECOMMENTS)); (pszComment[0] - pszCodeBuffer) + nCount < nLength; nCount++)
						{
							if (pszComment[0][nCount] == EOL) break;
							continue;
						}
						RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), (INT)(pszComment[0] - pszCodeBuffer + nCount), &cFormat[4]);
						nPos = (INT)((pszComment[0] - pszCodeBuffer) + nCount);
						continue;
					}
					break;
				}
				for (nPos = 0, pszComment[0] = pszComment[1] = (LPTSTR)NULL; nPos < nLength; )
				{
					if ((pszComment[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_BEGINCOMMENTS))))
					{
						for (pszComment[2] = _tcsstr(&pszCodeBuffer[(!pszComment[1]) ? ((pszComment[0] - pszCodeBuffer) + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_BEGINCOMMENTS))) : (pszComment[1] - pszCodeBuffer)], STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_ENDCOMMENTS)); !pszComment[2]; )
						{
							RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), -1, &cFormat[4]);
							nPos = nLength;
							break;
						}
						if (nPos < nLength)
						{
							RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), (INT)((pszComment[2] - pszCodeBuffer) + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_ENDCOMMENTS))), &cFormat[4]);
							nPos = (INT)((pszComment[0] - pszCodeBuffer) + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_BEGINCOMMENTS)));
							pszComment[1] = pszComment[2] + lstrlen(STRING(IDS_TELECOMMANDPROCEDURELANGUAGE_SYMBOL_ENDCOMMENTS));
							continue;
						}
					}
					break;
				}
				GlobalFree(pszCodeBuffer);
			}
			for (; bSelection; )
			{
				pEdit->SendMessage(EM_SETSEL, nSelPos[0], nSelPos[1]);
				break;
			}
			pITextDocument->Undo(tomResume, (long*)NULL);
			pITextDocument->Redo(tomResume, (long*)NULL);
			pITextDocument->Unfreeze(&lFreezeCount);
			pITextDocument->Release();
		}
		pIRichEditOle->Release();
	}
}
VOID CTPLCodeEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}
VOID CTPLCodeEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETPARAFORMAT, (WPARAM)NULL, (LPARAM)pParagraph);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}

BEGIN_MESSAGE_MAP(CTPLCodeEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CTPLCodeEdit)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_CONTROL_REFLECT_EX(EN_CHANGE, OnEditchange)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPLCodeEdit message handlers

int CTPLCodeEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) != -1)
	{
		SetEventMask(GetEventMask() | ENM_CHANGE | ENM_REQUESTRESIZE);
		RequestResize();
		return 0;
	}
	return -1;
}

LRESULT CTPLCodeEdit::OnNcHitTest(CPoint point)
{
	CRect  rEdit;
	SCROLLINFO  sScrollInfo[2];

	for (GetWindowRect(rEdit); GetScrollInfo(SB_HORZ, &sScrollInfo[0]) && GetScrollInfo(SB_VERT, &sScrollInfo[1]); )
	{
		if (sScrollInfo[0].nPage > 0 && CRect(rEdit.left, rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL), (sScrollInfo[1].nPage > 0) ? (rEdit.right - GetSystemMetrics(SM_CXVSCROLL)) : rEdit.right, rEdit.bottom).PtInRect(point)) return HTHSCROLL;
		if (sScrollInfo[1].nPage > 0 && CRect(rEdit.right - GetSystemMetrics(SM_CXVSCROLL), rEdit.top, rEdit.right, (sScrollInfo[0].nPage > 0) ? (rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL)) : rEdit.bottom).PtInRect(point)) return HTVSCROLL;
		break;
	}
	return CRichEditCtrl::OnNcHitTest(point);
}

BOOL CTPLCodeEdit::OnEditchange()
{
	RenderCode();
	return FALSE;
}

LRESULT CTPLCodeEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	for (m_bSelection = FALSE, lResult = Default(); TRUE; )
	{
		RenderCode();
		break;
	}
	m_bSelection = TRUE;
	return lResult;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceTPLCodeEdit

IMPLEMENT_DYNCREATE(CResourceTPLCodeEdit, CTPLCodeEdit)

WNDPROC CResourceTPLCodeEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceTPLCodeEdit::CResourceTPLCodeEdit(HWND hWnd) : CTPLCodeEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceTPLCodeEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceTPLCodeEdit* pResourceTPLCodeEdit;

	if ((pResourceTPLCodeEdit = new CResourceTPLCodeEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceTPLCodeEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceTPLCodeEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceTPLCodeEdit, CTPLCodeEdit)
	//{{AFX_MSG_MAP(CResourceTPLCodeEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceTPLCodeEdit message handlers

BOOL CResourceTPLCodeEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (m_dwStyle = lpCreateStruct->style) | WS_CHILD));
	return CTPLCodeEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptCodeEdit

IMPLEMENT_DYNCREATE(CScriptCodeEdit, CRichEditCtrl)

CScriptCodeEdit::CScriptCodeEdit() : CRichEditCtrl()
{
	m_dwStyle = 0;
	m_bSelection = TRUE;
}

BOOL CScriptCodeEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CRichEditCtrl::Create((m_dwStyle = dwStyle) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CScriptCodeEdit::RegisterClass()
{
	CString  szClass[2];
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CScriptCodeEdit  cScriptCodeEdit;

	if ((pClass = cScriptCodeEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass[0] = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass[0].GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass[0].ReleaseBuffer();
#endif
		if (GetClassInfo((HINSTANCE)NULL, RICHEDIT_CLASS, &sWndClass))
		{
			CResourceScriptCodeEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass[1] = szClass[0].Mid(1)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass[1];
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceScriptCodeEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceScriptCodeEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CScriptCodeEdit::UnregisterClass()
{
	CString  szClass;
	CRuntimeClass* pClass;
	CScriptCodeEdit  cScriptCodeEdit;

	if ((pClass = cScriptCodeEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass.ReleaseBuffer();
#endif
		return ::UnregisterClass(szClass.Mid(1), GetModuleHandle((LPCTSTR)NULL));
	}
	return FALSE;
}

VOID CScriptCodeEdit::RenderCode()
{
	RenderCode(this, CCustomControls::GetCustomControlFont(this), m_bSelection);
}
VOID CScriptCodeEdit::RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection)
{
	INT  nPos;
	INT  nCount;
	INT  nLength;
	INT  nKeyword;
	LONG  lFreezeCount;
	LONG  nSelPos[2];
	LPTSTR  pszPos;
	LPTSTR  pszQuote;
	LPTSTR  pszKeyword;
	LPTSTR  pszComment[3];
	LPTSTR  pszCodeBuffer;
	IRichEditOle* pIRichEditOle;
	ITextDocument* pITextDocument;
	CHARFORMAT2  cFormat[3];
	PARAFORMAT2  cParagraph;
	CFontTools  cFontTools;
	LOGFONT  lfFont;

	if ((pIRichEditOle = (IsWindow(pEdit->GetSafeHwnd())) ? pEdit->GetIRichEditOle() : (IRichEditOle*)NULL))
	{
		if (SUCCEEDED(pIRichEditOle->QueryInterface(IID_IScriptCodeDocument, (LPVOID*)& pITextDocument)))
		{
			pFont->GetLogFont(&lfFont);
			pEdit->GetSel(nSelPos[0], nSelPos[1]);
			pITextDocument->Freeze(&lFreezeCount);
			pITextDocument->Undo(tomSuspend, (long*)NULL);
			pITextDocument->Redo(tomSuspend, (long*)NULL);
			cFormat[0].cbSize = sizeof(cFormat[0]);
			cFormat[1].cbSize = sizeof(cFormat[1]);
			cFormat[2].cbSize = sizeof(cFormat[2]);
			cFormat[0].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[1].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[2].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			_tcscpy_s(cFormat[0].szFaceName, sizeof(cFormat[0].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[1].szFaceName, sizeof(cFormat[1].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[2].szFaceName, sizeof(cFormat[2].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			cFormat[0].dwEffects = CFE_AUTOCOLOR;
			cFormat[1].dwEffects = CFE_BOLD;
			cFormat[2].dwEffects = 0;
			cFormat[0].crTextColor = RGB(0, 0, 0);
			cFormat[1].crTextColor = RGB(0, 0, 128);
			cFormat[2].crTextColor = RGB(0, 128, 0);
			cFormat[0].yHeight = cFormat[1].yHeight = cFormat[2].yHeight = 20 * cFontTools.QueryPoints(&lfFont);
			cFormat[0].yOffset = 0;
			cFormat[1].yOffset = 0;
			cFormat[2].yOffset = 0;
			if ((pszCodeBuffer = (LPTSTR)GlobalAlloc(GPTR, ((SIZE_T)pEdit->GetWindowTextLength() + 1) * sizeof(TCHAR))))
			{
				for (cParagraph.cbSize = sizeof(cParagraph), cParagraph.dwMask = PFM_SPACEBEFORE | PFM_SPACEAFTER, cParagraph.dySpaceBefore = cParagraph.dySpaceAfter = 0, RenderCode(pEdit, 0, -1, &cFormat[0], &cParagraph), pEdit->GetWindowText(pszCodeBuffer, pEdit->GetWindowTextLength() + 1); (pszPos = _tcsstr(pszCodeBuffer, CString(CR))); )
				{
					for (nCount = 1; (pszPos[0] = pszPos[nCount]) != (TCHAR)EOS; )
					{
						nCount = ((++pszPos)[nCount] == CR) ? (nCount + 1) : nCount;
						continue;
					}
					break;
				}
				for (nKeyword = MINSCRIPTLANGUAGEKEYWORD, nLength = lstrlen(pszCodeBuffer); nKeyword <= MAXSCRIPTLANGUAGEKEYWORD; nKeyword++)
				{
					for (nPos = 0; nPos < nLength; )
					{
						if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], STRING(nKeyword))))
						{
							for (; (lstrlen(pszKeyword) == nLength || (!_istalnum(pszKeyword[-1]) && pszKeyword[-1] != STRINGCHAR(IDS_SCRIPTLANGUAGE_SYMBOL_SUBSTITUTE))) && !_istalnum(pszKeyword[lstrlen(STRING(nKeyword))]) && pszKeyword[lstrlen(STRING(nKeyword))] != STRINGCHAR(IDS_SCRIPTLANGUAGE_SYMBOL_SUBSTITUTE); )
							{
								RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + lstrlen(STRING(nKeyword))), &cFormat[1]);
								break;
							}
							nPos = (INT)((pszKeyword - pszCodeBuffer) + lstrlen(STRING(nKeyword)));
							continue;
						}
						break;
					}
				}
				for (nPos = 0; nPos < nLength; )
				{
					if ((pszQuote = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_SCRIPTLANGUAGE_SYMBOL_STRINGQUOTE))))
					{
						for (nCount = lstrlen(STRING(IDS_SCRIPTLANGUAGE_SYMBOL_STRINGQUOTE)); (pszQuote - pszCodeBuffer) + nCount < nLength; nCount++)
						{
							if (pszQuote[nCount] == STRINGCHAR(IDS_SCRIPTLANGUAGE_SYMBOL_STRINGQUOTE))
							{
								nCount++;
								break;
							}
							if (pszQuote[nCount] == EOL) break;
						}
						RenderCode(pEdit, (INT)(pszQuote - pszCodeBuffer), (INT)(pszQuote - pszCodeBuffer + nCount), &cFormat[0]);
						nPos = (INT)((pszQuote - pszCodeBuffer) + nCount);
						continue;
					}
					break;
				}
				for (nPos = 0; nPos < nLength; )
				{
					if ((pszComment[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_SCRIPTLANGUAGE_SYMBOL_LINECOMMENTS))))
					{
						for (nCount = lstrlen(STRING(IDS_SCRIPTLANGUAGE_SYMBOL_LINECOMMENTS)); (pszComment[0] - pszCodeBuffer) + nCount < nLength; nCount++)
						{
							if (pszComment[0][nCount] == EOL) break;
							continue;
						}
						RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), (INT)(pszComment[0] - pszCodeBuffer + nCount), &cFormat[2]);
						nPos = (INT)((pszComment[0] - pszCodeBuffer) + nCount);
						continue;
					}
					break;
				}
				for (nPos = 0, pszComment[0] = pszComment[1] = (LPTSTR)NULL; nPos < nLength; )
				{
					if ((pszComment[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_SCRIPTLANGUAGE_SYMBOL_BEGINCOMMENTS))))
					{
						for (pszComment[2] = _tcsstr(&pszCodeBuffer[(!pszComment[1]) ? ((pszComment[0] - pszCodeBuffer) + lstrlen(STRING(IDS_SCRIPTLANGUAGE_SYMBOL_BEGINCOMMENTS))) : (pszComment[1] - pszCodeBuffer)], STRING(IDS_SCRIPTLANGUAGE_SYMBOL_ENDCOMMENTS)); !pszComment[2]; )
						{
							RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), -1, &cFormat[2]);
							nPos = nLength;
							break;
						}
						if (nPos < nLength)
						{
							RenderCode(pEdit, (INT)(pszComment[0] - pszCodeBuffer), (INT)((pszComment[2] - pszCodeBuffer) + lstrlen(STRING(IDS_SCRIPTLANGUAGE_SYMBOL_ENDCOMMENTS))), &cFormat[2]);
							nPos = (INT)((pszComment[0] - pszCodeBuffer) + lstrlen(STRING(IDS_SCRIPTLANGUAGE_SYMBOL_BEGINCOMMENTS)));
							pszComment[1] = pszComment[2] + lstrlen(STRING(IDS_SCRIPTLANGUAGE_SYMBOL_ENDCOMMENTS));
							continue;
						}
					}
					break;
				}
				GlobalFree(pszCodeBuffer);
			}
			for (; bSelection; )
			{
				pEdit->SendMessage(EM_SETSEL, nSelPos[0], nSelPos[1]);
				break;
			}
			pITextDocument->Undo(tomResume, (long*)NULL);
			pITextDocument->Redo(tomResume, (long*)NULL);
			pITextDocument->Unfreeze(&lFreezeCount);
			pITextDocument->Release();
		}
		pIRichEditOle->Release();
	}
}
VOID CScriptCodeEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}
VOID CScriptCodeEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETPARAFORMAT, (WPARAM)NULL, (LPARAM)pParagraph);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}

BEGIN_MESSAGE_MAP(CScriptCodeEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CScriptCodeEdit)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_CONTROL_REFLECT_EX(EN_CHANGE, OnEditchange)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptCodeEdit message handlers

int CScriptCodeEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) != -1)
	{
		SetEventMask(GetEventMask() | ENM_CHANGE);
		return 0;
	}
	return -1;
}

LRESULT CScriptCodeEdit::OnNcHitTest(CPoint point)
{
	CRect  rEdit;
	SCROLLINFO  sScrollInfo[2];

	for (GetWindowRect(rEdit); GetScrollInfo(SB_HORZ, &sScrollInfo[0]) && GetScrollInfo(SB_VERT, &sScrollInfo[1]); )
	{
		if (sScrollInfo[0].nPage > 0 && CRect(rEdit.left, rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL), (sScrollInfo[1].nPage > 0) ? (rEdit.right - GetSystemMetrics(SM_CXVSCROLL)) : rEdit.right, rEdit.bottom).PtInRect(point)) return HTHSCROLL;
		if (sScrollInfo[1].nPage > 0 && CRect(rEdit.right - GetSystemMetrics(SM_CXVSCROLL), rEdit.top, rEdit.right, (sScrollInfo[0].nPage > 0) ? (rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL)) : rEdit.bottom).PtInRect(point)) return HTVSCROLL;
		break;
	}
	return CRichEditCtrl::OnNcHitTest(point);
}

BOOL CScriptCodeEdit::OnEditchange()
{
	RenderCode();
	return FALSE;
}

LRESULT CScriptCodeEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	for (m_bSelection = FALSE, lResult = Default(); TRUE; )
	{
		RenderCode();
		break;
	}
	m_bSelection = TRUE;
	return lResult;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceScriptCodeEdit

IMPLEMENT_DYNCREATE(CResourceScriptCodeEdit, CScriptCodeEdit)

WNDPROC CResourceScriptCodeEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceScriptCodeEdit::CResourceScriptCodeEdit(HWND hWnd) : CScriptCodeEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceScriptCodeEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceScriptCodeEdit* pResourceScriptCodeEdit;

	if ((pResourceScriptCodeEdit = new CResourceScriptCodeEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceScriptCodeEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceScriptCodeEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceScriptCodeEdit, CScriptCodeEdit)
	//{{AFX_MSG_MAP(CResourceScriptCodeEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceScriptCodeEdit message handlers

BOOL CResourceScriptCodeEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (m_dwStyle = lpCreateStruct->style) | WS_CHILD));
	return CScriptCodeEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceXmlEdit

IMPLEMENT_DYNCREATE(CTCSequenceXmlEdit, CRichEditCtrl)

CTCSequenceXmlEdit::CTCSequenceXmlEdit() : CRichEditCtrl()
{
	m_dwStyle = 0;
	m_bSelection = TRUE;
}

BOOL CTCSequenceXmlEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CRichEditCtrl::Create((m_dwStyle = dwStyle) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCSequenceXmlEdit::RegisterClass()
{
	CString  szClass[2];
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CTCSequenceXmlEdit  cTCSequenceXmlEdit;

	if ((pClass = cTCSequenceXmlEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass[0] = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass[0].GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass[0].ReleaseBuffer();
#endif
		if (GetClassInfo((HINSTANCE)NULL, RICHEDIT_CLASS, &sWndClass))
		{
			CResourceTCSequenceXmlEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass[1] = szClass[0].Mid(1)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass[1];
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceTCSequenceXmlEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceTCSequenceXmlEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CTCSequenceXmlEdit::UnregisterClass()
{
	CString  szClass;
	CRuntimeClass* pClass;
	CTCSequenceXmlEdit  cTCSequenceXmlEdit;

	if ((pClass = cTCSequenceXmlEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass.ReleaseBuffer();
#endif
		return ::UnregisterClass(szClass.Mid(1), GetModuleHandle((LPCTSTR)NULL));
	}
	return FALSE;
}

VOID CTCSequenceXmlEdit::RenderCode()
{
	RenderCode(this, CCustomControls::GetCustomControlFont(this), m_bSelection);
}
VOID CTCSequenceXmlEdit::RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection)
{
	INT  nPos;
	INT  nCount;
	INT  nLength;
	INT  nOffset;
	INT  nKeyword;
	INT  nAttribute;
	INT  nAttributes;
	BOOL  bQuotes;
	BOOL  bAttribute;
	LONG  lFreezeCount;
	LONG  nSelPos[2];
	LPTSTR  pszPos[2];
	LPTSTR  pszKeyword;
	LPTSTR  pszQuote[2];
	LPTSTR  pszAttribute;
	LPTSTR  pszCodeBuffer;
	CString  szKeyword[3];
	IRichEditOle* pIRichEditOle;
	ITextDocument* pITextDocument;
	CHARFORMAT2  cFormat[4];
	PARAFORMAT2  cParagraph;
	CFontTools  cFontTools;
	LOGFONT  lfFont;

	if ((pIRichEditOle = (IsWindow(pEdit->GetSafeHwnd())) ? pEdit->GetIRichEditOle() : (IRichEditOle*)NULL))
	{
		if (SUCCEEDED(pIRichEditOle->QueryInterface(IID_ITCProcedureXmlDocument, (LPVOID*)& pITextDocument)))
		{
			pFont->GetLogFont(&lfFont);
			pEdit->GetSel(nSelPos[0], nSelPos[1]);
			pITextDocument->Freeze(&lFreezeCount);
			pITextDocument->Undo(tomSuspend, (long*)NULL);
			pITextDocument->Redo(tomSuspend, (long*)NULL);
			cFormat[0].cbSize = sizeof(cFormat[0]);
			cFormat[1].cbSize = sizeof(cFormat[1]);
			cFormat[2].cbSize = sizeof(cFormat[2]);
			cFormat[3].cbSize = sizeof(cFormat[3]);
			cFormat[0].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[1].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[2].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[3].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			_tcscpy_s(cFormat[0].szFaceName, sizeof(cFormat[0].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[1].szFaceName, sizeof(cFormat[1].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[2].szFaceName, sizeof(cFormat[2].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[3].szFaceName, sizeof(cFormat[3].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			cFormat[0].dwEffects = CFE_AUTOCOLOR;
			cFormat[1].dwEffects = CFE_BOLD;
			cFormat[2].dwEffects = 0;
			cFormat[3].dwEffects = CFE_BOLD;
			cFormat[0].crTextColor = RGB(0, 0, 0);
			cFormat[1].crTextColor = RGB(0, 0, 255);
			cFormat[2].crTextColor = RGB(255, 0, 0);
			cFormat[3].crTextColor = RGB(0, 0, 0);
			cFormat[0].yHeight = cFormat[1].yHeight = cFormat[2].yHeight = cFormat[3].yHeight = 20 * cFontTools.QueryPoints(&lfFont);
			cFormat[0].yOffset = 0;
			cFormat[1].yOffset = 0;
			cFormat[2].yOffset = 0;
			cFormat[3].yOffset = 0;
			if ((pszCodeBuffer = (LPTSTR)GlobalAlloc(GPTR, ((SIZE_T)pEdit->GetWindowTextLength() + 1) * sizeof(TCHAR))))
			{
				for (cParagraph.cbSize = sizeof(cParagraph), cParagraph.dwMask = PFM_SPACEBEFORE | PFM_SPACEAFTER, cParagraph.dySpaceBefore = cParagraph.dySpaceAfter = 0, RenderCode(pEdit, 0, -1, &cFormat[0], &cParagraph), pEdit->GetWindowText(pszCodeBuffer, pEdit->GetWindowTextLength() + 1); (pszPos[0] = _tcsstr(pszCodeBuffer, CString(CR))); )
				{
					for (nCount = 1; (pszPos[0][0] = pszPos[0][nCount]) != (TCHAR)EOS; )
					{
						nCount = ((++pszPos[0])[nCount] == CR) ? (nCount + 1) : nCount;
						continue;
					}
					break;
				}
				for (nKeyword = MINTCSEQUENCEXMLKEYWORDID; nKeyword <= MAXTCSEQUENCEXMLKEYWORDID; nKeyword++)
				{
					for (nPos = 0, nLength = lstrlen(pszCodeBuffer), szKeyword[0] = STRING(nKeyword), szKeyword[1] = STRING(nKeyword - MINTCSEQUENCEXMLKEYWORDID + MINTCSEQUENCEXMLKEYENDID); nPos < nLength; )
					{
						if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], szKeyword[0])))
						{
							for (RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + szKeyword[0].GetLength()), &cFormat[1]), nPos = (INT)((pszKeyword - pszCodeBuffer) + szKeyword[0].GetLength()); ((pszPos[0] = _tcsstr(&pszCodeBuffer[nPos], szKeyword[1])) || szKeyword[1] == STRING(IDS_TCSEQUENCE_XMLKEYEND_CSFDEFINITION) || szKeyword[1] == STRING(IDS_TCSEQUENCE_XMLKEYEND_CSSDEFINITION) || szKeyword[1] == STRING(IDS_TCSEQUENCE_XMLKEYEND_SDFDEFINITION) || szKeyword[1] == STRING(IDS_TCSEQUENCE_XMLKEYEND_CSPDEFINITION)) && (pszPos[1] = _tcsstr(&pszCodeBuffer[nPos], (szKeyword[2] = (szKeyword[1] == STRING(IDS_TCSEQUENCE_XMLKEYEND_CSFDEFINITION) || szKeyword[1] == STRING(IDS_TCSEQUENCE_XMLKEYEND_CSSDEFINITION) || szKeyword[1] == STRING(IDS_TCSEQUENCE_XMLKEYEND_SDFDEFINITION) || szKeyword[1] == STRING(IDS_TCSEQUENCE_XMLKEYEND_CSPDEFINITION)) ? szKeyword[1].Right(1) : szKeyword[1]))) && (pszPos[0] >= pszPos[1] || !pszPos[0]); )
							{
								do
								{
									for (szKeyword[1] = (!pszPos[0]) ? szKeyword[2] : szKeyword[1], pszPos[0] = (!pszPos[0]) ? pszPos[1] : pszPos[0], pszQuote[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_XMLSYMBOL_QUOTE)), pszQuote[1] = (pszQuote[0]) ? _tcsstr(pszQuote[0] + lstrlen(STRING(IDS_XMLSYMBOL_QUOTE)), STRING(IDS_XMLSYMBOL_QUOTE)) : (LPTSTR)NULL, bQuotes = FALSE; pszPos[1] > pszQuote[1] && pszQuote[0] != (LPTSTR)NULL && pszQuote[1] != (LPTSTR)NULL && !_tcsncmp(&pszCodeBuffer[(nPos = (INT)(pszQuote[0] - pszCodeBuffer))], STRING(IDS_XMLSYMBOL_QUOTE), lstrlen(STRING(IDS_XMLSYMBOL_QUOTE))); bQuotes = FALSE)
									{
										RenderCode(pEdit, nPos, nPos + (nOffset = (INT)(pszQuote[1] - pszQuote[0]) + lstrlen(STRING(IDS_XMLSYMBOL_QUOTE))), &cFormat[2]);
										nPos += nOffset + 1;
										bQuotes = TRUE;
										break;
									}
								} while (bQuotes);
								for (nAttribute = MINTCSEQUENCEXMLATTRIBUTEID, nAttributes = (pszPos[0] >= pszPos[1]) ? MAXTCSEQUENCEXMLATTRIBUTEID : 0; nAttribute <= nAttributes; nAttribute++)
								{
									for (nPos = (INT)((pszKeyword - pszCodeBuffer) + szKeyword[0].GetLength()); (!_tcscmp(STRING(nKeyword), STRING(IDS_TCSEQUENCE_XMLKEYWORD_CSFDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_NAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_DESCRIPTION))) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_DETAILS)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_TIMETAGFLAG)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_NUMBEROFPARAMETERS)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_NUMBEROFELEMENTS)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_CRITICALITYFLAG)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_PLANNINGFLAG)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_LOADINGFLAG)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_SUBSYSTEMID)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_CREATIONTIME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_DOCUMENTNAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_DOCUMENTISSUE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_DOCUMENTDATE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_DEFAULTVALUESET)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_PARAMETERVALUESET)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSF_SUBSCHEDULEID))) || (!_tcscmp(STRING(nKeyword), STRING(IDS_TCSEQUENCE_XMLKEYWORD_CSSDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_SEQUENCENAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_TYPE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_COMMENT)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_ENTRYNUMBER)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_ELEMENTID)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_NUMBEROFPARAMETERS)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_DISPATCHFLAG)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_RELEASETIMEDELTAFLAG)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_RELEASETIME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_EXECUTIONTIMEFLAG)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_EXECUTIONTIME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_GROUPFLAG)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_BLOCKFLAG)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_INTERLOCKSCOPE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_INTERLOCKSTAGE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_PTVCHECKS)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_PEVCHECKS)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSS_CEVCHECKS)))) || (!_tcscmp(STRING(nKeyword), STRING(IDS_TCSEQUENCE_XMLKEYWORD_SDFDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_SDF_SEQUENCENAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_SDF_NAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_SDF_TYPE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_SDF_ENTRYNUMBER)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_SDF_ELEMENTID)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_SDF_POSITION)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_SDF_REPEATEDPOSITION)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_SDF_VALUETYPE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_SDF_VALUE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_SDF_VALUESET)))) || (!_tcscmp(STRING(nKeyword), STRING(IDS_TCSEQUENCE_XMLKEYWORD_CSPDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_SEQUENCENAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_NAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_TYPE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_DESCRIPTION)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_ENTRYNUMBER)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_TYPECODE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_FORMATCODE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_DISPLAYFORMAT)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_VALUETYPE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_VALUERADIX)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_DEFAULTVALUE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_VALUERANGESET)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_CALIBRATIONCATEGORY)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_NUMERICALCALIBRATIONCURVE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_TEXTUALCALIBRATIONCURVE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_TCSEQUENCE_XMLATTRIBUTE_CSP_VALUEUNIT)))); )
									{
										do
										{
											for (pszAttribute = _tcsstr(&pszCodeBuffer[nPos], STRING(nAttribute)), bAttribute = FALSE; pszPos[1] > pszAttribute && pszAttribute != (LPTSTR)NULL; bAttribute = FALSE)
											{
												RenderCode(pEdit, nPos, (nPos = (INT)(pszAttribute - pszCodeBuffer)) + lstrlen(STRING(nAttribute)), &cFormat[3]);
												nPos += lstrlen(STRING(nAttribute));
												bAttribute = TRUE;
												break;
											}
										} while (bAttribute);
										break;
									}
								}
								for (RenderCode(pEdit, (INT)(pszPos[0] - pszCodeBuffer), (nPos = (INT)(pszPos[0] - pszCodeBuffer) + szKeyword[1].GetLength()), &cFormat[1]); pszPos[0] != pszPos[1]; )
								{
									RenderCode(pEdit, (INT)(pszPos[1] - pszCodeBuffer), (nPos = (INT)(pszPos[1] - pszCodeBuffer) + szKeyword[2].GetLength()), &cFormat[1]);
									break;
								}
								break;
							}
							continue;
						}
						break;
					}
				}
				GlobalFree(pszCodeBuffer);
			}
			for (; bSelection; )
			{
				pEdit->SendMessage(EM_SETSEL, nSelPos[0], nSelPos[1]);
				break;
			}
			pITextDocument->Undo(tomResume, (long*)NULL);
			pITextDocument->Redo(tomResume, (long*)NULL);
			pITextDocument->Unfreeze(&lFreezeCount);
			pITextDocument->Release();
		}
		pIRichEditOle->Release();
	}
}
VOID CTCSequenceXmlEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}
VOID CTCSequenceXmlEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETPARAFORMAT, (WPARAM)NULL, (LPARAM)pParagraph);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}

BEGIN_MESSAGE_MAP(CTCSequenceXmlEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CTCSequenceXmlEdit)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_CONTROL_REFLECT_EX(EN_CHANGE, OnEditchange)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceXmlEdit message handlers

int CTCSequenceXmlEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) != -1)
	{
		SetEventMask(GetEventMask() | ENM_CHANGE | ENM_REQUESTRESIZE);
		RequestResize();
		return 0;
	}
	return -1;
}

LRESULT CTCSequenceXmlEdit::OnNcHitTest(CPoint point)
{
	CRect  rEdit;
	SCROLLINFO  sScrollInfo[2];

	for (GetWindowRect(rEdit); GetScrollInfo(SB_HORZ, &sScrollInfo[0]) && GetScrollInfo(SB_VERT, &sScrollInfo[1]); )
	{
		if (sScrollInfo[0].nPage > 0 && CRect(rEdit.left, rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL), (sScrollInfo[1].nPage > 0) ? (rEdit.right - GetSystemMetrics(SM_CXVSCROLL)) : rEdit.right, rEdit.bottom).PtInRect(point)) return HTHSCROLL;
		if (sScrollInfo[1].nPage > 0 && CRect(rEdit.right - GetSystemMetrics(SM_CXVSCROLL), rEdit.top, rEdit.right, (sScrollInfo[0].nPage > 0) ? (rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL)) : rEdit.bottom).PtInRect(point)) return HTVSCROLL;
		break;
	}
	return CRichEditCtrl::OnNcHitTest(point);
}

BOOL CTCSequenceXmlEdit::OnEditchange()
{
	RenderCode();
	return FALSE;
}

LRESULT CTCSequenceXmlEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	for (m_bSelection = FALSE, lResult = Default(); TRUE; )
	{
		RenderCode();
		break;
	}
	m_bSelection = TRUE;
	return lResult;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceTCSequenceXmlEdit

IMPLEMENT_DYNCREATE(CResourceTCSequenceXmlEdit, CTCSequenceXmlEdit)

WNDPROC CResourceTCSequenceXmlEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceTCSequenceXmlEdit::CResourceTCSequenceXmlEdit(HWND hWnd) : CTCSequenceXmlEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceTCSequenceXmlEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceTCSequenceXmlEdit* pResourceTCSequenceXmlEdit;

	if ((pResourceTCSequenceXmlEdit = new CResourceTCSequenceXmlEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceTCSequenceXmlEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceTCSequenceXmlEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceTCSequenceXmlEdit, CTCSequenceXmlEdit)
	//{{AFX_MSG_MAP(CResourceTCSequenceXmlEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceTCSequenceXmlEdit message handlers

BOOL CResourceTCSequenceXmlEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (m_dwStyle = lpCreateStruct->style) | WS_CHILD));
	return CTCSequenceXmlEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CANDXmlEdit

IMPLEMENT_DYNCREATE(CANDXmlEdit, CRichEditCtrl)

CANDXmlEdit::CANDXmlEdit() : CRichEditCtrl()
{
	m_dwStyle = 0;
	m_bSelection = TRUE;
}

BOOL CANDXmlEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CRichEditCtrl::Create((m_dwStyle = dwStyle) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CANDXmlEdit::RegisterClass()
{
	CString  szClass[2];
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CANDXmlEdit  cANDXmlEdit;

	if ((pClass = cANDXmlEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass[0] = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass[0].GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass[0].ReleaseBuffer();
#endif
		if (GetClassInfo((HINSTANCE)NULL, RICHEDIT_CLASS, &sWndClass))
		{
			CResourceANDXmlEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass[1] = szClass[0].Mid(1)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass[1];
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceANDXmlEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceANDXmlEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CANDXmlEdit::UnregisterClass()
{
	CString  szClass;
	CRuntimeClass* pClass;
	CANDXmlEdit  cANDXmlEdit;

	if ((pClass = cANDXmlEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass.ReleaseBuffer();
#endif
		return ::UnregisterClass(szClass.Mid(1), GetModuleHandle((LPCTSTR)NULL));
	}
	return FALSE;
}

VOID CANDXmlEdit::RenderCode()
{
	RenderCode(this, CCustomControls::GetCustomControlFont(this), m_bSelection);
}
VOID CANDXmlEdit::RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection)
{
	INT  nPos;
	INT  nCount;
	INT  nLength;
	INT  nOffset;
	INT  nKeyword;
	INT  nAttribute;
	INT  nAttributes;
	BOOL  bQuotes;
	BOOL  bAttribute;
	LONG  lFreezeCount;
	LONG  nSelPos[2];
	LPTSTR  pszPos[2];
	LPTSTR  pszKeyword;
	LPTSTR  pszQuote[2];
	LPTSTR  pszAttribute;
	LPTSTR  pszCodeBuffer;
	CString  szKeyword[3];
	IRichEditOle* pIRichEditOle;
	ITextDocument* pITextDocument;
	CHARFORMAT2  cFormat[4];
	PARAFORMAT2  cParagraph;
	CFontTools  cFontTools;
	LOGFONT  lfFont;

	if ((pIRichEditOle = (IsWindow(pEdit->GetSafeHwnd())) ? pEdit->GetIRichEditOle() : (IRichEditOle*)NULL))
	{
		if (SUCCEEDED(pIRichEditOle->QueryInterface(IID_IANDXmlDocument, (LPVOID*)& pITextDocument)))
		{
			pFont->GetLogFont(&lfFont);
			pEdit->GetSel(nSelPos[0], nSelPos[1]);
			pITextDocument->Freeze(&lFreezeCount);
			pITextDocument->Undo(tomSuspend, (long*)NULL);
			pITextDocument->Redo(tomSuspend, (long*)NULL);
			cFormat[0].cbSize = sizeof(cFormat[0]);
			cFormat[1].cbSize = sizeof(cFormat[1]);
			cFormat[2].cbSize = sizeof(cFormat[2]);
			cFormat[3].cbSize = sizeof(cFormat[3]);
			cFormat[0].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[1].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[2].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[3].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			_tcscpy_s(cFormat[0].szFaceName, sizeof(cFormat[0].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[1].szFaceName, sizeof(cFormat[1].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[2].szFaceName, sizeof(cFormat[2].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[3].szFaceName, sizeof(cFormat[3].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			cFormat[0].dwEffects = CFE_AUTOCOLOR;
			cFormat[1].dwEffects = CFE_BOLD;
			cFormat[2].dwEffects = 0;
			cFormat[3].dwEffects = CFE_BOLD;
			cFormat[0].crTextColor = RGB(0, 0, 0);
			cFormat[1].crTextColor = RGB(0, 0, 255);
			cFormat[2].crTextColor = RGB(255, 0, 0);
			cFormat[3].crTextColor = RGB(0, 0, 0);
			cFormat[0].yHeight = cFormat[1].yHeight = cFormat[2].yHeight = cFormat[3].yHeight = 20 * cFontTools.QueryPoints(&lfFont);
			cFormat[0].yOffset = 0;
			cFormat[1].yOffset = 0;
			cFormat[2].yOffset = 0;
			cFormat[3].yOffset = 0;
			if ((pszCodeBuffer = (LPTSTR)GlobalAlloc(GPTR, ((SIZE_T)pEdit->GetWindowTextLength() + 1) * sizeof(TCHAR))))
			{
				for (cParagraph.cbSize = sizeof(cParagraph), cParagraph.dwMask = PFM_SPACEBEFORE | PFM_SPACEAFTER, cParagraph.dySpaceBefore = cParagraph.dySpaceAfter = 0, RenderCode(pEdit, 0, -1, &cFormat[0], &cParagraph), pEdit->GetWindowText(pszCodeBuffer, pEdit->GetWindowTextLength() + 1); (pszPos[0] = _tcsstr(pszCodeBuffer, CString(CR))); )
				{
					for (nCount = 1; (pszPos[0][0] = pszPos[0][nCount]) != (TCHAR)EOS; )
					{
						nCount = ((++pszPos[0])[nCount] == CR) ? (nCount + 1) : nCount;
						continue;
					}
					break;
				}
				for (nKeyword = MINANDXMLKEYWORDID; nKeyword <= MAXANDXMLKEYWORDID; nKeyword++)
				{
					for (nPos = 0, nLength = lstrlen(pszCodeBuffer), szKeyword[0] = STRING(nKeyword), szKeyword[1] = STRING(nKeyword - MINANDXMLKEYWORDID + MINANDXMLKEYENDID); nPos < nLength; )
					{
						if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], szKeyword[0])))
						{
							for (RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + szKeyword[0].GetLength()), &cFormat[1]), nPos = (INT)((pszKeyword - pszCodeBuffer) + szKeyword[0].GetLength()); ((pszPos[0] = _tcsstr(&pszCodeBuffer[nPos], szKeyword[1])) || szKeyword[1] == STRING(IDS_AND_XMLKEYEND_DISPLAYDEFINITION)) && (pszPos[1] = _tcsstr(&pszCodeBuffer[nPos], (szKeyword[2] = (szKeyword[1] == STRING(IDS_AND_XMLKEYEND_DISPLAYDEFINITION)) ? szKeyword[1].Right(1) : szKeyword[1]))) && (pszPos[0] >= pszPos[1] || !pszPos[0]); )
							{
								do
								{
									for (szKeyword[1] = (!pszPos[0]) ? szKeyword[2] : szKeyword[1], pszPos[0] = (!pszPos[0]) ? pszPos[1] : pszPos[0], pszQuote[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_XMLSYMBOL_QUOTE)), pszQuote[1] = (pszQuote[0]) ? _tcsstr(pszQuote[0] + lstrlen(STRING(IDS_XMLSYMBOL_QUOTE)), STRING(IDS_XMLSYMBOL_QUOTE)) : (LPTSTR)NULL, bQuotes = FALSE; pszPos[1] > pszQuote[1] && pszQuote[0] != (LPTSTR)NULL && pszQuote[1] != (LPTSTR)NULL && !_tcsncmp(&pszCodeBuffer[(nPos = (INT)(pszQuote[0] - pszCodeBuffer))], STRING(IDS_XMLSYMBOL_QUOTE), lstrlen(STRING(IDS_XMLSYMBOL_QUOTE))); bQuotes = FALSE)
									{
										RenderCode(pEdit, nPos, nPos + (nOffset = (INT)(pszQuote[1] - pszQuote[0]) + lstrlen(STRING(IDS_XMLSYMBOL_QUOTE))), &cFormat[2]);
										nPos += nOffset + 1;
										bQuotes = TRUE;
										break;
									}
								} while (bQuotes);
								for (nAttribute = MINANDXMLATTRIBUTEID, nAttributes = (pszPos[0] >= pszPos[1]) ? MAXANDXMLATTRIBUTEID : 0; nAttribute <= nAttributes; nAttribute++)
								{
									for (nPos = (INT)((pszKeyword - pszCodeBuffer) + szKeyword[0].GetLength()); (!_tcscmp(STRING(nKeyword), STRING(IDS_AND_XMLKEYWORD_DISPLAYDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_NAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_DESCRIPTION)))) || (!_tcscmp(STRING(nKeyword), STRING(IDS_AND_XMLKEYWORD_DISPLAYPARAMETERDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_NAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_DOMAIN)) || !_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_ORDERINDISPLAY)) || !_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_REPRESENTATION)) || !_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_COMMUTATION)) || !_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_FORMAT)) || !_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_DISPLAYIFINVALID)))) || (!_tcscmp(STRING(nKeyword), STRING(IDS_AND_XMLKEYWORD_DISPLAYCOMMENTDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_COMMENT)) || !_tcscmp(STRING(nAttribute), STRING(IDS_AND_XMLATTRIBUTE_ORDERINDISPLAY)))); )
									{
										do
										{
											for (pszAttribute = _tcsstr(&pszCodeBuffer[nPos], STRING(nAttribute)), bAttribute = FALSE; pszPos[1] > pszAttribute && pszAttribute != (LPTSTR)NULL; bAttribute = FALSE)
											{
												RenderCode(pEdit, nPos, (nPos = (INT)(pszAttribute - pszCodeBuffer)) + lstrlen(STRING(nAttribute)), &cFormat[3]);
												nPos += lstrlen(STRING(nAttribute));
												bAttribute = TRUE;
												break;
											}
										} while (bAttribute);
										break;
									}
								}
								for (RenderCode(pEdit, (INT)(pszPos[0] - pszCodeBuffer), (nPos = (INT)(pszPos[0] - pszCodeBuffer) + szKeyword[1].GetLength()), &cFormat[1]); pszPos[0] != pszPos[1]; )
								{
									RenderCode(pEdit, (INT)(pszPos[1] - pszCodeBuffer), (nPos = (INT)(pszPos[1] - pszCodeBuffer) + szKeyword[2].GetLength()), &cFormat[1]);
									break;
								}
								break;
							}
							continue;
						}
						break;
					}
				}
				GlobalFree(pszCodeBuffer);
			}
			for (; bSelection; )
			{
				pEdit->SendMessage(EM_SETSEL, nSelPos[0], nSelPos[1]);
				break;
			}
			pITextDocument->Undo(tomResume, (long*)NULL);
			pITextDocument->Redo(tomResume, (long*)NULL);
			pITextDocument->Unfreeze(&lFreezeCount);
			pITextDocument->Release();
		}
		pIRichEditOle->Release();
	}
}
VOID CANDXmlEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}
VOID CANDXmlEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETPARAFORMAT, (WPARAM)NULL, (LPARAM)pParagraph);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}

BEGIN_MESSAGE_MAP(CANDXmlEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CANDXmlEdit)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_CONTROL_REFLECT_EX(EN_CHANGE, OnEditchange)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDXmlEdit message handlers

int CANDXmlEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) != -1)
	{
		SetEventMask(GetEventMask() | ENM_CHANGE | ENM_REQUESTRESIZE);
		RequestResize();
		return 0;
	}
	return -1;
}

LRESULT CANDXmlEdit::OnNcHitTest(CPoint point)
{
	CRect  rEdit;
	SCROLLINFO  sScrollInfo[2];

	for (GetWindowRect(rEdit); GetScrollInfo(SB_HORZ, &sScrollInfo[0]) && GetScrollInfo(SB_VERT, &sScrollInfo[1]); )
	{
		if (sScrollInfo[0].nPage > 0 && CRect(rEdit.left, rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL), (sScrollInfo[1].nPage > 0) ? (rEdit.right - GetSystemMetrics(SM_CXVSCROLL)) : rEdit.right, rEdit.bottom).PtInRect(point)) return HTHSCROLL;
		if (sScrollInfo[1].nPage > 0 && CRect(rEdit.right - GetSystemMetrics(SM_CXVSCROLL), rEdit.top, rEdit.right, (sScrollInfo[0].nPage > 0) ? (rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL)) : rEdit.bottom).PtInRect(point)) return HTVSCROLL;
		break;
	}
	return CRichEditCtrl::OnNcHitTest(point);
}

BOOL CANDXmlEdit::OnEditchange()
{
	RenderCode();
	return FALSE;
}

LRESULT CANDXmlEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	for (m_bSelection = FALSE, lResult = Default(); TRUE; )
	{
		RenderCode();
		break;
	}
	m_bSelection = TRUE;
	return lResult;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceANDXmlEdit

IMPLEMENT_DYNCREATE(CResourceANDXmlEdit, CANDXmlEdit)

WNDPROC CResourceANDXmlEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceANDXmlEdit::CResourceANDXmlEdit(HWND hWnd) : CANDXmlEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceANDXmlEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceANDXmlEdit* pResourceANDXmlEdit;

	if ((pResourceANDXmlEdit = new CResourceANDXmlEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceANDXmlEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceANDXmlEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceANDXmlEdit, CANDXmlEdit)
	//{{AFX_MSG_MAP(CResourceANDXmlEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceANDXmlEdit message handlers

BOOL CResourceANDXmlEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (m_dwStyle = lpCreateStruct->style) | WS_CHILD));
	return CANDXmlEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDXmlEdit

IMPLEMENT_DYNCREATE(CGRDXmlEdit, CRichEditCtrl)

CGRDXmlEdit::CGRDXmlEdit() : CRichEditCtrl()
{
	m_dwStyle = 0;
	m_bSelection = TRUE;
}

BOOL CGRDXmlEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CRichEditCtrl::Create((m_dwStyle = dwStyle) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDXmlEdit::RegisterClass()
{
	CString  szClass[2];
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CGRDXmlEdit  cGRDXmlEdit;

	if ((pClass = cGRDXmlEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass[0] = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass[0].GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass[0].ReleaseBuffer();
#endif
		if (GetClassInfo((HINSTANCE)NULL, RICHEDIT_CLASS, &sWndClass))
		{
			CResourceGRDXmlEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass[1] = szClass[0].Mid(1)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass[1];
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceGRDXmlEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceGRDXmlEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CGRDXmlEdit::UnregisterClass()
{
	CString  szClass;
	CRuntimeClass* pClass;
	CGRDXmlEdit  cGRDXmlEdit;

	if ((pClass = cGRDXmlEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass.ReleaseBuffer();
#endif
		return ::UnregisterClass(szClass.Mid(1), GetModuleHandle((LPCTSTR)NULL));
	}
	return FALSE;
}

VOID CGRDXmlEdit::RenderCode()
{
	RenderCode(this, CCustomControls::GetCustomControlFont(this), m_bSelection);
}
VOID CGRDXmlEdit::RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection)
{
	INT  nPos;
	INT  nCount;
	INT  nLength;
	INT  nOffset;
	INT  nKeyword;
	INT  nAttribute;
	INT  nAttributes;
	BOOL  bQuotes;
	BOOL  bAttribute;
	LONG  lFreezeCount;
	LONG  nSelPos[2];
	LPTSTR  pszPos[2];
	LPTSTR  pszKeyword;
	LPTSTR  pszQuote[2];
	LPTSTR  pszAttribute;
	LPTSTR  pszCodeBuffer;
	CString  szKeyword[3];
	IRichEditOle* pIRichEditOle;
	ITextDocument* pITextDocument;
	CHARFORMAT2  cFormat[4];
	PARAFORMAT2  cParagraph;
	CFontTools  cFontTools;
	LOGFONT  lfFont;

	if ((pIRichEditOle = (IsWindow(pEdit->GetSafeHwnd())) ? pEdit->GetIRichEditOle() : (IRichEditOle*)NULL))
	{
		if (SUCCEEDED(pIRichEditOle->QueryInterface(IID_IGRDXmlDocument, (LPVOID*)& pITextDocument)))
		{
			pFont->GetLogFont(&lfFont);
			pEdit->GetSel(nSelPos[0], nSelPos[1]);
			pITextDocument->Freeze(&lFreezeCount);
			pITextDocument->Undo(tomSuspend, (long*)NULL);
			pITextDocument->Redo(tomSuspend, (long*)NULL);
			cFormat[0].cbSize = sizeof(cFormat[0]);
			cFormat[1].cbSize = sizeof(cFormat[1]);
			cFormat[2].cbSize = sizeof(cFormat[2]);
			cFormat[3].cbSize = sizeof(cFormat[3]);
			cFormat[0].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[1].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[2].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[3].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			_tcscpy_s(cFormat[0].szFaceName, sizeof(cFormat[0].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[1].szFaceName, sizeof(cFormat[1].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[2].szFaceName, sizeof(cFormat[2].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[3].szFaceName, sizeof(cFormat[3].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			cFormat[0].dwEffects = CFE_AUTOCOLOR;
			cFormat[1].dwEffects = CFE_BOLD;
			cFormat[2].dwEffects = 0;
			cFormat[3].dwEffects = CFE_BOLD;
			cFormat[0].crTextColor = RGB(0, 0, 0);
			cFormat[1].crTextColor = RGB(0, 0, 255);
			cFormat[2].crTextColor = RGB(255, 0, 0);
			cFormat[3].crTextColor = RGB(0, 0, 0);
			cFormat[0].yHeight = cFormat[1].yHeight = cFormat[2].yHeight = cFormat[3].yHeight = 20 * cFontTools.QueryPoints(&lfFont);
			cFormat[0].yOffset = 0;
			cFormat[1].yOffset = 0;
			cFormat[2].yOffset = 0;
			cFormat[3].yOffset = 0;
			if ((pszCodeBuffer = (LPTSTR)GlobalAlloc(GPTR, ((SIZE_T)pEdit->GetWindowTextLength() + 1) * sizeof(TCHAR))))
			{
				for (cParagraph.cbSize = sizeof(cParagraph), cParagraph.dwMask = PFM_SPACEBEFORE | PFM_SPACEAFTER, cParagraph.dySpaceBefore = cParagraph.dySpaceAfter = 0, RenderCode(pEdit, 0, -1, &cFormat[0], &cParagraph), pEdit->GetWindowText(pszCodeBuffer, pEdit->GetWindowTextLength() + 1); (pszPos[0] = _tcsstr(pszCodeBuffer, CString(CR))); )
				{
					for (nCount = 1; (pszPos[0][0] = pszPos[0][nCount]) != (TCHAR)EOS; )
					{
						nCount = ((++pszPos[0])[nCount] == CR) ? (nCount + 1) : nCount;
						continue;
					}
					break;
				}
				for (nKeyword = MINGRDXMLKEYWORDID; nKeyword <= MAXGRDXMLKEYWORDID; nKeyword++)
				{
					for (nPos = 0, nLength = lstrlen(pszCodeBuffer), szKeyword[0] = STRING(nKeyword), szKeyword[1] = STRING(nKeyword - MINGRDXMLKEYWORDID + MINGRDXMLKEYENDID); nPos < nLength; )
					{
						if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], szKeyword[0])))
						{
							for (RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + szKeyword[0].GetLength()), &cFormat[1]), nPos = (INT)((pszKeyword - pszCodeBuffer) + szKeyword[0].GetLength()); ((pszPos[0] = _tcsstr(&pszCodeBuffer[nPos], szKeyword[1])) || szKeyword[1] == STRING(IDS_GRD_XMLKEYEND_DISPLAYDEFINITION)) && (pszPos[1] = _tcsstr(&pszCodeBuffer[nPos], (szKeyword[2] = (szKeyword[1] == STRING(IDS_GRD_XMLKEYEND_DISPLAYDEFINITION)) ? szKeyword[1].Right(1) : szKeyword[1]))) && (pszPos[0] >= pszPos[1] || !pszPos[0]); )
							{
								do
								{
									for (szKeyword[1] = (!pszPos[0]) ? szKeyword[2] : szKeyword[1], pszPos[0] = (!pszPos[0]) ? pszPos[1] : pszPos[0], pszQuote[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_XMLSYMBOL_QUOTE)), pszQuote[1] = (pszQuote[0]) ? _tcsstr(pszQuote[0] + lstrlen(STRING(IDS_XMLSYMBOL_QUOTE)), STRING(IDS_XMLSYMBOL_QUOTE)) : (LPTSTR)NULL, bQuotes = FALSE; pszPos[1] > pszQuote[1] && pszQuote[0] != (LPTSTR)NULL && pszQuote[1] != (LPTSTR)NULL && !_tcsncmp(&pszCodeBuffer[(nPos = (INT)(pszQuote[0] - pszCodeBuffer))], STRING(IDS_XMLSYMBOL_QUOTE), lstrlen(STRING(IDS_XMLSYMBOL_QUOTE))); bQuotes = FALSE)
									{
										RenderCode(pEdit, nPos, nPos + (nOffset = (INT)(pszQuote[1] - pszQuote[0]) + lstrlen(STRING(IDS_XMLSYMBOL_QUOTE))), &cFormat[2]);
										nPos += nOffset + 1;
										bQuotes = TRUE;
										break;
									}
								} while (bQuotes);
								for (nAttribute = MINGRDXMLATTRIBUTEID, nAttributes = (pszPos[0] >= pszPos[1]) ? MAXGRDXMLATTRIBUTEID : 0; nAttribute <= nAttributes; nAttribute++)
								{
									for (nPos = (INT)((pszKeyword - pszCodeBuffer) + szKeyword[0].GetLength()); (!_tcscmp(STRING(nKeyword), STRING(IDS_GRD_XMLKEYWORD_DISPLAYDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_NAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_DESCRIPTION)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_PLOTTYPE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_SCROLLING)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_DURATION)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_COLOR)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_XAXISPOINTS)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_YAXISPOINTS)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_XGRIDLINES)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_YGRIDLINES)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_AUTOHARDCOPY)))) || (!_tcscmp(STRING(nKeyword), STRING(IDS_GRD_XMLKEYWORD_DISPLAYPARAMETERDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_NAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_DOMAIN)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_ORDERINDISPLAY)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_REPRESENTATION)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_INITWITHSOURCEVIEW)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_ISXAXISPARAMETER)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_PLOTAREA)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_MINVALUE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_MAXVALUE)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_COLOR)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_MARKER)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_LINESTYLE)))) || (!_tcscmp(STRING(nKeyword), STRING(IDS_GRD_XMLKEYWORD_DISPLAYCOMMENTDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_COMMENT)) || !_tcscmp(STRING(nAttribute), STRING(IDS_GRD_XMLATTRIBUTE_ORDERINDISPLAY)))); )
									{
										do
										{
											for (pszAttribute = _tcsstr(&pszCodeBuffer[nPos], STRING(nAttribute)), bAttribute = FALSE; pszPos[1] > pszAttribute && pszAttribute != (LPTSTR)NULL; bAttribute = FALSE)
											{
												RenderCode(pEdit, nPos, (nPos = (INT)(pszAttribute - pszCodeBuffer)) + lstrlen(STRING(nAttribute)), &cFormat[3]);
												nPos += lstrlen(STRING(nAttribute));
												bAttribute = TRUE;
												break;
											}
										} while (bAttribute);
										break;
									}
								}
								for (RenderCode(pEdit, (INT)(pszPos[0] - pszCodeBuffer), (nPos = (INT)(pszPos[0] - pszCodeBuffer) + szKeyword[1].GetLength()), &cFormat[1]); pszPos[0] != pszPos[1]; )
								{
									RenderCode(pEdit, (INT)(pszPos[1] - pszCodeBuffer), (nPos = (INT)(pszPos[1] - pszCodeBuffer) + szKeyword[2].GetLength()), &cFormat[1]);
									break;
								}
								break;
							}
							continue;
						}
						break;
					}
				}
				GlobalFree(pszCodeBuffer);
			}
			for (; bSelection; )
			{
				pEdit->SendMessage(EM_SETSEL, nSelPos[0], nSelPos[1]);
				break;
			}
			pITextDocument->Undo(tomResume, (long*)NULL);
			pITextDocument->Redo(tomResume, (long*)NULL);
			pITextDocument->Unfreeze(&lFreezeCount);
			pITextDocument->Release();
		}
		pIRichEditOle->Release();
	}
}
VOID CGRDXmlEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}
VOID CGRDXmlEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETPARAFORMAT, (WPARAM)NULL, (LPARAM)pParagraph);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}

BEGIN_MESSAGE_MAP(CGRDXmlEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CGRDXmlEdit)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_CONTROL_REFLECT_EX(EN_CHANGE, OnEditchange)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDXmlEdit message handlers

int CGRDXmlEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) != -1)
	{
		SetEventMask(GetEventMask() | ENM_CHANGE | ENM_REQUESTRESIZE);
		RequestResize();
		return 0;
	}
	return -1;
}

LRESULT CGRDXmlEdit::OnNcHitTest(CPoint point)
{
	CRect  rEdit;
	SCROLLINFO  sScrollInfo[2];

	for (GetWindowRect(rEdit); GetScrollInfo(SB_HORZ, &sScrollInfo[0]) && GetScrollInfo(SB_VERT, &sScrollInfo[1]); )
	{
		if (sScrollInfo[0].nPage > 0 && CRect(rEdit.left, rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL), (sScrollInfo[1].nPage > 0) ? (rEdit.right - GetSystemMetrics(SM_CXVSCROLL)) : rEdit.right, rEdit.bottom).PtInRect(point)) return HTHSCROLL;
		if (sScrollInfo[1].nPage > 0 && CRect(rEdit.right - GetSystemMetrics(SM_CXVSCROLL), rEdit.top, rEdit.right, (sScrollInfo[0].nPage > 0) ? (rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL)) : rEdit.bottom).PtInRect(point)) return HTVSCROLL;
		break;
	}
	return CRichEditCtrl::OnNcHitTest(point);
}

BOOL CGRDXmlEdit::OnEditchange()
{
	RenderCode();
	return FALSE;
}

LRESULT CGRDXmlEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	for (m_bSelection = FALSE, lResult = Default(); TRUE; )
	{
		RenderCode();
		break;
	}
	m_bSelection = TRUE;
	return lResult;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceGRDXmlEdit

IMPLEMENT_DYNCREATE(CResourceGRDXmlEdit, CGRDXmlEdit)

WNDPROC CResourceGRDXmlEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceGRDXmlEdit::CResourceGRDXmlEdit(HWND hWnd) : CGRDXmlEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceGRDXmlEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceGRDXmlEdit* pResourceGRDXmlEdit;

	if ((pResourceGRDXmlEdit = new CResourceGRDXmlEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceGRDXmlEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceGRDXmlEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceGRDXmlEdit, CGRDXmlEdit)
	//{{AFX_MSG_MAP(CResourceGRDXmlEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceGRDXmlEdit message handlers

BOOL CResourceGRDXmlEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (m_dwStyle = lpCreateStruct->style) | WS_CHILD));
	return CGRDXmlEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CPODXmlEdit

IMPLEMENT_DYNCREATE(CPODXmlEdit, CRichEditCtrl)

CPODXmlEdit::CPODXmlEdit() : CRichEditCtrl()
{
	m_dwStyle = 0;
	m_bSelection = TRUE;
}

BOOL CPODXmlEdit::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CRichEditCtrl::Create((m_dwStyle = dwStyle) | WS_CHILD, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CPODXmlEdit::RegisterClass()
{
	CString  szClass[2];
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CPODXmlEdit  cPODXmlEdit;

	if ((pClass = cPODXmlEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass[0] = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass[0].GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass[0].ReleaseBuffer();
#endif
		if (GetClassInfo((HINSTANCE)NULL, RICHEDIT_CLASS, &sWndClass))
		{
			CResourcePODXmlEdit::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass[1] = szClass[0].Mid(1)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass[1];
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourcePODXmlEdit::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourcePODXmlEdit::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CPODXmlEdit::UnregisterClass()
{
	CString  szClass;
	CRuntimeClass* pClass;
	CPODXmlEdit  cPODXmlEdit;

	if ((pClass = cPODXmlEdit.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		szClass.ReleaseBuffer();
#endif
		return ::UnregisterClass(szClass.Mid(1), GetModuleHandle((LPCTSTR)NULL));
	}
	return FALSE;
}

VOID CPODXmlEdit::RenderCode()
{
	RenderCode(this, CCustomControls::GetCustomControlFont(this), m_bSelection);
}
VOID CPODXmlEdit::RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection)
{
	INT  nPos;
	INT  nCount;
	INT  nLength;
	INT  nOffset;
	INT  nKeyword;
	INT  nAttribute;
	INT  nAttributes;
	BOOL  bQuotes;
	BOOL  bAttribute;
	LONG  lFreezeCount;
	LONG  nSelPos[2];
	LPTSTR  pszPos[2];
	LPTSTR  pszKeyword;
	LPTSTR  pszQuote[2];
	LPTSTR  pszAttribute;
	LPTSTR  pszCodeBuffer;
	CString  szKeyword[3];
	IRichEditOle* pIRichEditOle;
	ITextDocument* pITextDocument;
	CHARFORMAT2  cFormat[4];
	PARAFORMAT2  cParagraph;
	CFontTools  cFontTools;
	LOGFONT  lfFont;

	if ((pIRichEditOle = (IsWindow(pEdit->GetSafeHwnd())) ? pEdit->GetIRichEditOle() : (IRichEditOle*)NULL))
	{
		if (SUCCEEDED(pIRichEditOle->QueryInterface(IID_IPODXmlDocument, (LPVOID*)& pITextDocument)))
		{
			pFont->GetLogFont(&lfFont);
			pEdit->GetSel(nSelPos[0], nSelPos[1]);
			pITextDocument->Freeze(&lFreezeCount);
			pITextDocument->Undo(tomSuspend, (long*)NULL);
			pITextDocument->Redo(tomSuspend, (long*)NULL);
			cFormat[0].cbSize = sizeof(cFormat[0]);
			cFormat[1].cbSize = sizeof(cFormat[1]);
			cFormat[2].cbSize = sizeof(cFormat[2]);
			cFormat[3].cbSize = sizeof(cFormat[3]);
			cFormat[0].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[1].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[2].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			cFormat[3].dwMask = CFM_FACE | CFM_SIZE | CFM_OFFSET | CFM_BOLD | CFM_ITALIC | CFM_STRIKEOUT | CFM_UNDERLINE | CFM_COLOR;
			_tcscpy_s(cFormat[0].szFaceName, sizeof(cFormat[0].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[1].szFaceName, sizeof(cFormat[1].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[2].szFaceName, sizeof(cFormat[2].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			_tcscpy_s(cFormat[3].szFaceName, sizeof(cFormat[3].szFaceName) / sizeof(TCHAR), lfFont.lfFaceName);
			cFormat[0].dwEffects = CFE_AUTOCOLOR;
			cFormat[1].dwEffects = CFE_BOLD;
			cFormat[2].dwEffects = 0;
			cFormat[3].dwEffects = CFE_BOLD;
			cFormat[0].crTextColor = RGB(0, 0, 0);
			cFormat[1].crTextColor = RGB(0, 0, 255);
			cFormat[2].crTextColor = RGB(255, 0, 0);
			cFormat[3].crTextColor = RGB(0, 0, 0);
			cFormat[0].yHeight = cFormat[1].yHeight = cFormat[2].yHeight = cFormat[3].yHeight = 20 * cFontTools.QueryPoints(&lfFont);
			cFormat[0].yOffset = 0;
			cFormat[1].yOffset = 0;
			cFormat[2].yOffset = 0;
			cFormat[3].yOffset = 0;
			if ((pszCodeBuffer = (LPTSTR)GlobalAlloc(GPTR, ((SIZE_T)pEdit->GetWindowTextLength() + 1) * sizeof(TCHAR))))
			{
				for (cParagraph.cbSize = sizeof(cParagraph), cParagraph.dwMask = PFM_SPACEBEFORE | PFM_SPACEAFTER, cParagraph.dySpaceBefore = cParagraph.dySpaceAfter = 0, RenderCode(pEdit, 0, -1, &cFormat[0], &cParagraph), pEdit->GetWindowText(pszCodeBuffer, pEdit->GetWindowTextLength() + 1); (pszPos[0] = _tcsstr(pszCodeBuffer, CString(CR))); )
				{
					for (nCount = 1; (pszPos[0][0] = pszPos[0][nCount]) != (TCHAR)EOS; )
					{
						nCount = ((++pszPos[0])[nCount] == CR) ? (nCount + 1) : nCount;
						continue;
					}
					break;
				}
				for (nKeyword = MINPODXMLKEYWORDID; nKeyword <= MAXPODXMLKEYWORDID; nKeyword++)
				{
					for (nPos = 0, nLength = lstrlen(pszCodeBuffer), szKeyword[0] = STRING(nKeyword), szKeyword[1] = STRING(nKeyword - MINPODXMLKEYWORDID + MINPODXMLKEYENDID); nPos < nLength; )
					{
						if ((pszKeyword = _tcsstr(&pszCodeBuffer[nPos], szKeyword[0])))
						{
							for (RenderCode(pEdit, (INT)(pszKeyword - pszCodeBuffer), (INT)(pszKeyword - pszCodeBuffer + szKeyword[0].GetLength()), &cFormat[1]), nPos = (INT)((pszKeyword - pszCodeBuffer) + szKeyword[0].GetLength()); ((pszPos[0] = _tcsstr(&pszCodeBuffer[nPos], szKeyword[1])) || szKeyword[1] == STRING(IDS_POD_XMLKEYEND_DISPLAYDEFINITION)) && (pszPos[1] = _tcsstr(&pszCodeBuffer[nPos], (szKeyword[2] = (szKeyword[1] == STRING(IDS_POD_XMLKEYEND_DISPLAYDEFINITION)) ? szKeyword[1].Right(1) : szKeyword[1]))) && (pszPos[0] >= pszPos[1] || !pszPos[0]); )
							{
								do
								{
									for (szKeyword[1] = (!pszPos[0]) ? szKeyword[2] : szKeyword[1], pszPos[0] = (!pszPos[0]) ? pszPos[1] : pszPos[0], pszQuote[0] = _tcsstr(&pszCodeBuffer[nPos], STRING(IDS_XMLSYMBOL_QUOTE)), pszQuote[1] = (pszQuote[0]) ? _tcsstr(pszQuote[0] + lstrlen(STRING(IDS_XMLSYMBOL_QUOTE)), STRING(IDS_XMLSYMBOL_QUOTE)) : (LPTSTR)NULL, bQuotes = FALSE; pszPos[1] > pszQuote[1] && pszQuote[0] != (LPTSTR)NULL && pszQuote[1] != (LPTSTR)NULL && !_tcsncmp(&pszCodeBuffer[(nPos = (INT)(pszQuote[0] - pszCodeBuffer))], STRING(IDS_XMLSYMBOL_QUOTE), lstrlen(STRING(IDS_XMLSYMBOL_QUOTE))); bQuotes = FALSE)
									{
										RenderCode(pEdit, nPos, nPos + (nOffset = (INT)(pszQuote[1] - pszQuote[0]) + lstrlen(STRING(IDS_XMLSYMBOL_QUOTE))), &cFormat[2]);
										nPos += nOffset + 1;
										bQuotes = TRUE;
										break;
									}
								} while (bQuotes);
								for (nAttribute = MINPODXMLATTRIBUTEID, nAttributes = (pszPos[0] >= pszPos[1]) ? MAXPODXMLATTRIBUTEID : 0; nAttribute <= nAttributes; nAttribute++)
								{
									for (nPos = (INT)((pszKeyword - pszCodeBuffer) + szKeyword[0].GetLength()); (!_tcscmp(STRING(nKeyword), STRING(IDS_POD_XMLKEYWORD_DISPLAYDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_NAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_DESCRIPTION)))) || (!_tcscmp(STRING(nKeyword), STRING(IDS_POD_XMLKEYWORD_DISPLAYPARAMETERDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_NAME)) || !_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_DOMAIN)) || !_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_ORDERINDISPLAY)) || !_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_REPRESENTATION)) || !_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_FORMAT)) || !_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_BGCOLOR)) || !_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_FGCOLOR)) || !_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_UPDATEWHENSCROLL)) || !_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_DISPLAYIFINVALID)))) || (!_tcscmp(STRING(nKeyword), STRING(IDS_POD_XMLKEYWORD_DISPLAYCOMMENTDEFINITION)) && (!_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_COMMENT)) || !_tcscmp(STRING(nAttribute), STRING(IDS_POD_XMLATTRIBUTE_ORDERINDISPLAY)))); )
									{
										do
										{
											for (pszAttribute = _tcsstr(&pszCodeBuffer[nPos], STRING(nAttribute)), bAttribute = FALSE; pszPos[1] > pszAttribute && pszAttribute != (LPTSTR)NULL; bAttribute = FALSE)
											{
												RenderCode(pEdit, nPos, (nPos = (INT)(pszAttribute - pszCodeBuffer)) + lstrlen(STRING(nAttribute)), &cFormat[3]);
												nPos += lstrlen(STRING(nAttribute));
												bAttribute = TRUE;
												break;
											}
										} while (bAttribute);
										break;
									}
								}
								for (RenderCode(pEdit, (INT)(pszPos[0] - pszCodeBuffer), (nPos = (INT)(pszPos[0] - pszCodeBuffer) + szKeyword[1].GetLength()), &cFormat[1]); pszPos[0] != pszPos[1]; )
								{
									RenderCode(pEdit, (INT)(pszPos[1] - pszCodeBuffer), (nPos = (INT)(pszPos[1] - pszCodeBuffer) + szKeyword[2].GetLength()), &cFormat[1]);
									break;
								}
								break;
							}
							continue;
						}
						break;
					}
				}
				GlobalFree(pszCodeBuffer);
			}
			for (; bSelection; )
			{
				pEdit->SendMessage(EM_SETSEL, nSelPos[0], nSelPos[1]);
				break;
			}
			pITextDocument->Undo(tomResume, (long*)NULL);
			pITextDocument->Redo(tomResume, (long*)NULL);
			pITextDocument->Unfreeze(&lFreezeCount);
			pITextDocument->Release();
		}
		pIRichEditOle->Release();
	}
}
VOID CPODXmlEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}
VOID CPODXmlEdit::RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph)
{
	pEdit->SendMessage(EM_SETSEL, nStartPos, nStopPos);
	pEdit->SendMessage(EM_SETPARAFORMAT, (WPARAM)NULL, (LPARAM)pParagraph);
	pEdit->SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)pFormat);
}

BEGIN_MESSAGE_MAP(CPODXmlEdit, CRichEditCtrl)
	//{{AFX_MSG_MAP(CPODXmlEdit)
	ON_WM_CREATE()
	ON_WM_NCHITTEST()
	ON_CONTROL_REFLECT_EX(EN_CHANGE, OnEditchange)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODXmlEdit message handlers

int CPODXmlEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) != -1)
	{
		SetEventMask(GetEventMask() | ENM_CHANGE | ENM_REQUESTRESIZE);
		RequestResize();
		return 0;
	}
	return -1;
}

LRESULT CPODXmlEdit::OnNcHitTest(CPoint point)
{
	CRect  rEdit;
	SCROLLINFO  sScrollInfo[2];

	for (GetWindowRect(rEdit); GetScrollInfo(SB_HORZ, &sScrollInfo[0]) && GetScrollInfo(SB_VERT, &sScrollInfo[1]); )
	{
		if (sScrollInfo[0].nPage > 0 && CRect(rEdit.left, rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL), (sScrollInfo[1].nPage > 0) ? (rEdit.right - GetSystemMetrics(SM_CXVSCROLL)) : rEdit.right, rEdit.bottom).PtInRect(point)) return HTHSCROLL;
		if (sScrollInfo[1].nPage > 0 && CRect(rEdit.right - GetSystemMetrics(SM_CXVSCROLL), rEdit.top, rEdit.right, (sScrollInfo[0].nPage > 0) ? (rEdit.bottom - GetSystemMetrics(SM_CYHSCROLL)) : rEdit.bottom).PtInRect(point)) return HTVSCROLL;
		break;
	}
	return CRichEditCtrl::OnNcHitTest(point);
}

BOOL CPODXmlEdit::OnEditchange()
{
	RenderCode();
	return FALSE;
}

LRESULT CPODXmlEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	for (m_bSelection = FALSE, lResult = Default(); TRUE; )
	{
		RenderCode();
		break;
	}
	m_bSelection = TRUE;
	return lResult;
}


/////////////////////////////////////////////////////////////////////////////
// CResourcePODXmlEdit

IMPLEMENT_DYNCREATE(CResourcePODXmlEdit, CPODXmlEdit)

WNDPROC CResourcePODXmlEdit::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourcePODXmlEdit::CResourcePODXmlEdit(HWND hWnd) : CPODXmlEdit()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourcePODXmlEdit::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourcePODXmlEdit* pResourcePODXmlEdit;

	if ((pResourcePODXmlEdit = new CResourcePODXmlEdit(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourcePODXmlEdit::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourcePODXmlEdit::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourcePODXmlEdit, CPODXmlEdit)
	//{{AFX_MSG_MAP(CResourcePODXmlEdit)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourcePODXmlEdit message handlers

BOOL CResourcePODXmlEdit::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (m_dwStyle = lpCreateStruct->style) | WS_CHILD));
	return CPODXmlEdit::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CSimpleListBox

IMPLEMENT_DYNCREATE(CSimpleListBox, CListBox)

CSimpleListBox::CSimpleListBox()
{
	m_dwStyle = 0;
}

BOOL CSimpleListBox::Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle)
{
	if (CListBox::Create((MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_MULTICOLUMN | LBS_NOINTEGRALHEIGHT | LBS_NOREDRAW | LBS_NOTIFY | LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE | LBS_SORT | LBS_USETABSTOPS)) & ~(LBS_EXTENDEDSEL | LBS_MULTIPLESEL | LBS_WANTKEYBOARDINPUT)) | LBS_NOSEL), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL) & ~WS_TABSTOP, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CSimpleListBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CSimpleListBox  cSimpleListBox;

	if ((pClass = cSimpleListBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName && GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceSimpleListBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceSimpleListBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceSimpleListBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CSimpleListBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CSimpleListBox  cSimpleListBox;

	if ((pClass = cSimpleListBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

BEGIN_MESSAGE_MAP(CSimpleListBox, CListBox)
	//{{AFX_MSG_MAP(CSimpleListBox)
	ON_WM_NCCREATE()
	ON_WM_SETFOCUS()
	ON_WM_ENABLE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleListBox message handlers

BOOL CSimpleListBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!IsThemeActive())
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | ((lpCreateStruct->style & WS_BORDER) ? WS_EX_CLIENTEDGE : 0));
		SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~(lpCreateStruct->style & WS_BORDER));
	}
	return CListBox::OnNcCreate(lpCreateStruct);
}

void CSimpleListBox::OnSetFocus(CWnd* pOldWnd)
{
	return;
}

void CSimpleListBox::OnEnable(BOOL bEnable)
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
// CResourceSimpleListBox

IMPLEMENT_DYNCREATE(CResourceSimpleListBox, CSimpleListBox)

WNDPROC CResourceSimpleListBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceSimpleListBox::CResourceSimpleListBox(HWND hWnd) : CSimpleListBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceSimpleListBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceSimpleListBox* pResourceSimpleListBox;

	if ((pResourceSimpleListBox = new CResourceSimpleListBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceSimpleListBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceSimpleListBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceSimpleListBox, CSimpleListBox)
	//{{AFX_MSG_MAP(CResourceSimpleListBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceSimpleListBox message handlers

BOOL CResourceSimpleListBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = (MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (LBS_DISABLENOSCROLL | LBS_HASSTRINGS | LBS_MULTICOLUMN | LBS_NOINTEGRALHEIGHT | LBS_NOREDRAW | LBS_NOTIFY | LBS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE | LBS_SORT | LBS_USETABSTOPS)) & ~(LBS_EXTENDEDSEL | LBS_MULTIPLESEL | LBS_WANTKEYBOARDINPUT)) | LBS_NOSEL), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL) & ~WS_TABSTOP));
	return CSimpleListBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CColorsComboBox

IMPLEMENT_DYNCREATE(CColorsComboBox, CComboBox)

CColorsComboBox::CColorsComboBox()
{
	m_dwStyle = 0;
}

BOOL CColorsComboBox::Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle)
{
	return CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (CCBS_STANDARD | CCBS_CUSTOM | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID);
}

BOOL CColorsComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CColorsComboBox  cColorsComboBox;

	if ((pClass = cColorsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName && GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceColorsComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceColorsComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceColorsComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CColorsComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CColorsComboBox  cColorsComboBox;

	if ((pClass = cColorsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

void CColorsComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC* pDC;
	CFont* pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CColorsComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  cDC;
	INT  nBkMode;
	CFont* pOldFont;
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
						if ((pOldFont = (CFont*)cDC.SelectObject(CCustomControls::GetCustomControlFont(this))))
						{
							if (cDC.GetTextMetrics(&tmFont))
							{
								nBkMode = cDC.SetBkMode(TRANSPARENT);
								nOldColor = cDC.SetTextColor((lpDrawItemStruct->itemState & ODS_SELECTED) ? GetSysColor(COLOR_HIGHLIGHTTEXT) : GetSysColor(COLOR_WINDOWTEXT));
								cDC.TextOut(rItemArea.left, rItemArea.top + (rItemArea.Height() - tmFont.tmHeight) / 2, STRING(IDS_COLORSCOMBOBOX_CUSTOM));
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

int CColorsComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return((lpCompareItemStruct->itemData1 != lpCompareItemStruct->itemData2) ? ((lpCompareItemStruct->itemData1 < lpCompareItemStruct->itemData2) ? -1 : 1) : 0);
}

BEGIN_MESSAGE_MAP(CColorsComboBox, CComboBox)
	//{{AFX_MSG_MAP(CColorsComboBox)
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
// CColorsComboBox message handlers

int CColorsComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

BOOL CColorsComboBox::OnColor()
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

LRESULT CColorsComboBox::OnAddColor(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_ADDSTRING, wParam, lParam);
}

LRESULT CColorsComboBox::OnInsertColor(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_INSERTSTRING, wParam, lParam);
}

LRESULT CColorsComboBox::OnGetColor(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_GETITEMDATA, wParam);
}

LRESULT CColorsComboBox::OnFindColor(WPARAM wParam, LPARAM lParam)
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

LRESULT CColorsComboBox::OnSelectColor(WPARAM wParam, LPARAM lParam)
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

LRESULT CColorsComboBox::OnDeleteColor(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)SendMessage(CCB_FINDCOLOR, wParam, lParam));
}

LRESULT CColorsComboBox::OnResetColors(WPARAM wParam, LPARAM lParam)
{
	SendMessage(CB_RESETCONTENT);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceColorsComboBox

IMPLEMENT_DYNCREATE(CResourceColorsComboBox, CColorsComboBox)

WNDPROC CResourceColorsComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceColorsComboBox::CResourceColorsComboBox(HWND hWnd) : CColorsComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceColorsComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceColorsComboBox* pResourceColorsComboBox;

	if ((pResourceColorsComboBox = new CResourceColorsComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceColorsComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceColorsComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceColorsComboBox, CColorsComboBox)
	//{{AFX_MSG_MAP(CResourceColorsComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceColorsComboBox message handlers

BOOL CResourceColorsComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (CCBS_STANDARD | CCBS_CUSTOM | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CColorsComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CLineStylesComboBox

IMPLEMENT_DYNCREATE(CLineStylesComboBox, CComboBox)

CLineStylesComboBox::CLineStylesComboBox()
{
	m_dwStyle = 0;
}

BOOL CLineStylesComboBox::Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle)
{
	return CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID);
}

BOOL CLineStylesComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CLineStylesComboBox  cLineStylesComboBox;

	if ((pClass = cLineStylesComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName && GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceLineStylesComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceLineStylesComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceLineStylesComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CLineStylesComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CLineStylesComboBox  cLineStylesComboBox;

	if ((pClass = cLineStylesComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

void CLineStylesComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC* pDC;
	CFont* pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CLineStylesComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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
					if ((hPen = ExtCreatePen((DWORD)(PS_GEOMETRIC | PS_ENDCAP_FLAT | lpDrawItemStruct->itemData), 2, &sPenBrush, 0, (CONST DWORD*) NULL)))
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

int CLineStylesComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return((lpCompareItemStruct->itemData1 != lpCompareItemStruct->itemData2) ? ((lpCompareItemStruct->itemData1 < lpCompareItemStruct->itemData2) ? -1 : 1) : 0);
}

BEGIN_MESSAGE_MAP(CLineStylesComboBox, CComboBox)
	//{{AFX_MSG_MAP(CLineStylesComboBox)
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
// CLineStylesComboBox message handlers

int CLineStylesComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

LRESULT CLineStylesComboBox::OnAddLineStyle(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_ADDSTRING, wParam, lParam);
}

LRESULT CLineStylesComboBox::OnInsertLineStyle(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_INSERTSTRING, wParam, lParam);
}

LRESULT CLineStylesComboBox::OnGetLineStyle(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_GETITEMDATA, wParam);
}

LRESULT CLineStylesComboBox::OnFindLineStyle(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_FINDSTRINGEXACT, wParam, lParam);
}

LRESULT CLineStylesComboBox::OnSelectLineStyle(WPARAM wParam, LPARAM lParam)
{
	INT  nIndex;

	return(((nIndex = (INT)SendMessage(CB_SELECTSTRING, wParam, lParam)) == CB_ERR) ? SendMessage(CB_SETCURSEL, (WPARAM)-1) : nIndex);
}

LRESULT CLineStylesComboBox::OnDeleteLineStyle(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)SendMessage(CB_FINDSTRINGEXACT, wParam, lParam));
}

LRESULT CLineStylesComboBox::OnResetLineStyles(WPARAM wParam, LPARAM lParam)
{
	SendMessage(CB_RESETCONTENT);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceLineStylesComboBox

IMPLEMENT_DYNCREATE(CResourceLineStylesComboBox, CLineStylesComboBox)

WNDPROC CResourceLineStylesComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceLineStylesComboBox::CResourceLineStylesComboBox(HWND hWnd) : CLineStylesComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceLineStylesComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceLineStylesComboBox* pResourceLineStylesComboBox;

	if ((pResourceLineStylesComboBox = new CResourceLineStylesComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceLineStylesComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceLineStylesComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceLineStylesComboBox, CLineStylesComboBox)
	//{{AFX_MSG_MAP(CResourceLineStylesComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceLineStylesComboBox message handlers

BOOL CResourceLineStylesComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CLineStylesComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CLineSymbolsComboBox

IMPLEMENT_DYNCREATE(CLineSymbolsComboBox, CComboBox)

CLineSymbolsComboBox::CLineSymbolsComboBox()
{
	m_dwStyle = 0;
}

BOOL CLineSymbolsComboBox::Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle)
{
	return CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID);
}

BOOL CLineSymbolsComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CLineSymbolsComboBox  cLineSymbolsComboBox;

	if ((pClass = cLineSymbolsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName && GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceLineSymbolsComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceLineSymbolsComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceLineSymbolsComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CLineSymbolsComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CLineSymbolsComboBox  cLineSymbolsComboBox;

	if ((pClass = cLineSymbolsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

void CLineSymbolsComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC* pDC;
	CFont* pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CLineSymbolsComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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
					if ((hPen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, (nWidth = 2), &sPenBrush, 0, (CONST DWORD*) NULL)))
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

int CLineSymbolsComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return((lpCompareItemStruct->itemData1 != lpCompareItemStruct->itemData2) ? ((lpCompareItemStruct->itemData1 < lpCompareItemStruct->itemData2) ? -1 : 1) : 0);
}

BEGIN_MESSAGE_MAP(CLineSymbolsComboBox, CComboBox)
	//{{AFX_MSG_MAP(CLineSymbolsComboBox)
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
// CLineSymbolsComboBox message handlers

int CLineSymbolsComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

LRESULT CLineSymbolsComboBox::OnAddLineSymbol(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_ADDSTRING, wParam, lParam);
}

LRESULT CLineSymbolsComboBox::OnInsertLineSymbol(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_INSERTSTRING, wParam, lParam);
}

LRESULT CLineSymbolsComboBox::OnGetLineSymbol(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_GETITEMDATA, wParam);
}

LRESULT CLineSymbolsComboBox::OnFindLineSymbol(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_FINDSTRINGEXACT, wParam, lParam);
}

LRESULT CLineSymbolsComboBox::OnSelectLineSymbol(WPARAM wParam, LPARAM lParam)
{
	INT  nIndex;

	return(((nIndex = (INT)SendMessage(CB_SELECTSTRING, wParam, lParam)) == CB_ERR) ? SendMessage(CB_SETCURSEL, (WPARAM)-1) : nIndex);
}

LRESULT CLineSymbolsComboBox::OnDeleteLineSymbol(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)SendMessage(CB_FINDSTRINGEXACT, wParam, lParam));
}

LRESULT CLineSymbolsComboBox::OnResetLineSymbols(WPARAM wParam, LPARAM lParam)
{
	SendMessage(CB_RESETCONTENT);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceLineSymbolsComboBox

IMPLEMENT_DYNCREATE(CResourceLineSymbolsComboBox, CLineSymbolsComboBox)

WNDPROC CResourceLineSymbolsComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceLineSymbolsComboBox::CResourceLineSymbolsComboBox(HWND hWnd) : CLineSymbolsComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceLineSymbolsComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceLineSymbolsComboBox* pResourceLineSymbolsComboBox;

	if ((pResourceLineSymbolsComboBox = new CResourceLineSymbolsComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceLineSymbolsComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceLineSymbolsComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceLineSymbolsComboBox, CLineSymbolsComboBox)
	//{{AFX_MSG_MAP(CResourceLineSymbolsComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceLineSymbolsComboBox message handlers

BOOL CResourceLineSymbolsComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CLineSymbolsComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CHatchesComboBox

IMPLEMENT_DYNCREATE(CHatchesComboBox, CComboBox)

CHatchesComboBox::CHatchesComboBox()
{
	m_dwStyle = 0;
}

BOOL CHatchesComboBox::Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle)
{
	return CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID);
}

BOOL CHatchesComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CHatchesComboBox  cHatchesComboBox;

	if ((pClass = cHatchesComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName && GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceHatchesComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceHatchesComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceHatchesComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CHatchesComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CHatchesComboBox  cHatchesComboBox;

	if ((pClass = cHatchesComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

void CHatchesComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC* pDC;
	CFont* pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont)) ? (tmFont.tmHeight + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CHatchesComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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
							if ((hHtBitmap = LoadBitmap(GetLibraryModuleInstance(), (lpDrawItemStruct->itemData == HT_SOLID) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNSOLID) : ((lpDrawItemStruct->itemData == HT_HORIZONTAL) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNHORIZONTAL) : ((lpDrawItemStruct->itemData == HT_VERTICAL) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNVERTICAL) : ((lpDrawItemStruct->itemData == HT_BDIAGONAL) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNDIAGONALDOWN) : ((lpDrawItemStruct->itemData == HT_FDIAGONAL) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNDIAGONALUP) : ((lpDrawItemStruct->itemData == HT_CROSS) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNCROSS) : ((lpDrawItemStruct->itemData == HT_DIAGCROSS) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNCROSSDIAGONAL) : ((lpDrawItemStruct->itemData == HT_LPOINTS) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNPOINTSLOW) : ((lpDrawItemStruct->itemData == HT_MPOINTS) ? MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNPOINTSMEDIUM) : MAKEINTRESOURCE(IDB_HATCHESCOMBOBOXPATTERNPOINTSHIGH))))))))))))
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

int CHatchesComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return((lpCompareItemStruct->itemData1 != lpCompareItemStruct->itemData2) ? ((lpCompareItemStruct->itemData1 < lpCompareItemStruct->itemData2) ? -1 : 1) : 0);
}

BEGIN_MESSAGE_MAP(CHatchesComboBox, CComboBox)
	//{{AFX_MSG_MAP(CHatchesComboBox)
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
// CHatchesComboBox message handlers

int CHatchesComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

LRESULT CHatchesComboBox::OnAddHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_ADDSTRING, wParam, lParam);
}

LRESULT CHatchesComboBox::OnInsertHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_INSERTSTRING, wParam, lParam);
}

LRESULT CHatchesComboBox::OnGetHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_GETITEMDATA, wParam);
}

LRESULT CHatchesComboBox::OnFindHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_FINDSTRINGEXACT, wParam, lParam);
}

LRESULT CHatchesComboBox::OnSelectHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_SELECTSTRING, wParam, lParam);
}

LRESULT CHatchesComboBox::OnDeleteHatch(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)SendMessage(CB_FINDSTRINGEXACT, wParam, lParam));
}

LRESULT CHatchesComboBox::OnResetHatches(WPARAM wParam, LPARAM lParam)
{
	SendMessage(CB_RESETCONTENT);
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CResourceHatchesComboBox

IMPLEMENT_DYNCREATE(CResourceHatchesComboBox, CHatchesComboBox)

WNDPROC CResourceHatchesComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceHatchesComboBox::CResourceHatchesComboBox(HWND hWnd) : CHatchesComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceHatchesComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceHatchesComboBox* pResourceHatchesComboBox;

	if ((pResourceHatchesComboBox = new CResourceHatchesComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceHatchesComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceHatchesComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceHatchesComboBox, CHatchesComboBox)
	//{{AFX_MSG_MAP(CResourceHatchesComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceHatchesComboBox message handlers

BOOL CResourceHatchesComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CHatchesComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CFontsComboBox

IMPLEMENT_DYNCREATE(CFontsComboBox, CComboBox)

CFontsComboBox::CFontsComboBox() : CComboBox()
{
	m_dwStyle = 0;
	m_nItem = 0;
	m_hPrinterFontBitmap = (HBITMAP)NULL;
	m_hTrueTypeFontBitmap = (HBITMAP)NULL;
}

BOOL CFontsComboBox::Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle)
{
	if (CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT | CBS_OEMCONVERT)) & ~(CBS_OWNERDRAWFIXED | CBS_UPPERCASE | CBS_LOWERCASE)) | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID))
	{
		SetFont(CCustomControls::GetCustomControlFont(this));
		return TRUE;
	}
	return FALSE;
}

BOOL CFontsComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CFontsComboBox  cFontsComboBox;

	if ((pClass = cFontsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName && GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceFontsComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceFontsComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceFontsComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CFontsComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CFontsComboBox  cFontsComboBox;

	if ((pClass = cFontsComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

void CFontsComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC* pDC;
	CFont* pOldFont;
	BITMAP  sFont[2];
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont) && GetObject(m_hTrueTypeFontBitmap, sizeof(BITMAP), &sFont[0]) && GetObject(m_hPrinterFontBitmap, sizeof(BITMAP), &sFont[1])) ? (max(max(sFont[0].bmHeight, sFont[1].bmHeight), tmFont.tmHeight) + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CFontsComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  cDC;
	CDC  cBitmapDC;
	INT  nOldColor;
	INT  nOldBkMode;
	CFont* pOldFont;
	CBrush  cBkBrush;
	BITMAP  sFont[2];
	CBitmap* pOldBitmap;
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
					if ((pOldFont = cDC.SelectObject(CCustomControls::GetCustomControlFont(this))))
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

int CFontsComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	PFONTINFO  pFontInfo[2] = { (PFONTINFO)lpCompareItemStruct->itemData1,(PFONTINFO)lpCompareItemStruct->itemData2 };

	return lstrcmp(pFontInfo[0]->logFont.lfFaceName, pFontInfo[1]->logFont.lfFaceName);
}

void CFontsComboBox::DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct)
{
	PFONTINFO  pFontInfo = (PFONTINFO)lpDeleteItemStruct->itemData;

	GlobalFree(pFontInfo);
}

INT CALLBACK CFontsComboBox::EnumFontsProc(CONST LOGFONT* pLogFont, CONST TEXTMETRIC* pTextMetric, DWORD dwFontType, LPARAM pData)
{
	INT  nIndex;
	CWnd* pWnd;
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

BEGIN_MESSAGE_MAP(CFontsComboBox, CComboBox)
	//{{AFX_MSG_MAP(CFontsComboBox)
	ON_WM_CREATE()
	ON_WM_ENABLE()
	ON_WM_DESTROY()
	ON_MESSAGE(FCB_DIR, OnDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFontsComboBox message handlers

int CFontsComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	MEASUREITEMSTRUCT  sItem;

	if (CComboBox::OnCreate(lpCreateStruct) != -1)
	{
		if ((m_hTrueTypeFontBitmap = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_FONTSCOMBOBOXFONTTRUETYPE))))
		{
			if ((m_hPrinterFontBitmap = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_FONTSCOMBOBOXFONTPRINTER))))
			{
				MeasureItem(&sItem);
				SetItemHeight(-1, sItem.itemHeight);
				return 0;
			}
		}
	}
	return -1;
}

void CFontsComboBox::OnEnable(BOOL bEnable)
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
	for (m_nItem = (bEnable && GetCount()) ? SetCurSel(m_nItem) : GetCurSel(); !bEnable && GetCount() > 0; DeleteString(0)) m_pItems.AddTail((CObject*)GetItemDataPtr(0));
	CComboBox::OnEnable(bEnable);
}

LRESULT CFontsComboBox::OnDir(WPARAM wParam, LPARAM lParam)
{
	FONTENUMINFO  sFontEnumInfo = { (HDC)lParam,GetSafeHwnd(),(DWORD)wParam };

	ResetContent();
	if ((sFontEnumInfo.hDC = (!(sFontEnumInfo.dwTypes & CF_PRINTERFONTS)) ? ::GetDC(sFontEnumInfo.hWnd) : sFontEnumInfo.hDC))
	{
		EnumFontFamilies(sFontEnumInfo.hDC, (LPCTSTR)NULL, EnumFontsProc, (LPARAM)& sFontEnumInfo);
		if (!(sFontEnumInfo.dwTypes & CF_PRINTERFONTS)) ::ReleaseDC(sFontEnumInfo.hWnd, sFontEnumInfo.hDC);
		return GetCount();
	}
	return 0;
}

void CFontsComboBox::OnDestroy()
{
	DeleteObject(m_hPrinterFontBitmap);
	DeleteObject(m_hTrueTypeFontBitmap);
	m_hPrinterFontBitmap = (HBITMAP)NULL;
	m_hTrueTypeFontBitmap = (HBITMAP)NULL;
	CComboBox::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CResourceFontsComboBox

IMPLEMENT_DYNCREATE(CResourceFontsComboBox, CFontsComboBox)

WNDPROC CResourceFontsComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceFontsComboBox::CResourceFontsComboBox(HWND hWnd) : CFontsComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceFontsComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceFontsComboBox* pResourceFontsComboBox;

	if ((pResourceFontsComboBox = new CResourceFontsComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceFontsComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceFontsComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceFontsComboBox, CFontsComboBox)
	//{{AFX_MSG_MAP(CResourceFontsComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceFontsComboBox message handlers

BOOL CResourceFontsComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT | CBS_OEMCONVERT)) & ~(CBS_OWNERDRAWFIXED | CBS_UPPERCASE | CBS_LOWERCASE)) | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CFontsComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CAlignmentComboBox

IMPLEMENT_DYNCREATE(CAlignmentComboBox, CComboBox)

CAlignmentComboBox::CAlignmentComboBox() : CComboBox()
{
	m_dwStyle = 0;
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

BOOL CAlignmentComboBox::Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle)
{
	return CComboBox::Create(MAKELONG((m_dwStyle = ((LOWORD(dwStyle) & (ALCBS_LEFT | ALCBS_CENTER | ALCBS_RIGHT | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(dwStyle)) | WS_CHILD | WS_VSCROLL, rect, pParentWnd, nID);
}

BOOL CAlignmentComboBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CAlignmentComboBox  cAlignmentComboBox;

	if ((pClass = cAlignmentComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (_tcsstr(szClass, szBaseClass.Mid(cPos))) break;
			continue;
		}
		if (cPos < cbClassName && GetClassInfo((HINSTANCE)NULL, szBaseClass.Mid(cPos), &sWndClass))
		{
			CResourceAlignmentComboBox::m_lpfnSuperWndProc = (WNDPROC)sWndClass.lpfnWndProc;
			if (!GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
			{
				sWndClass.lpszClassName = (LPCTSTR)szClass;
				sWndClass.style = sWndClass.style | CS_GLOBALCLASS;
				sWndClass.lpfnWndProc = CResourceAlignmentComboBox::WndProcHook;
				return((::RegisterClass(&sWndClass)) ? TRUE : FALSE);
			}
			return((CResourceAlignmentComboBox::m_lpfnSuperWndProc == sWndClass.lpfnWndProc) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

BOOL CAlignmentComboBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CAlignmentComboBox  cAlignmentComboBox;

	if ((pClass = cAlignmentComboBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

void CAlignmentComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC* pDC;
	CFont* pOldFont;
	TEXTMETRIC  tmFont;
	BITMAP  sImage;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(CCustomControls::GetCustomControlFont(this))))
		{
			lpMeasureItemStruct->itemHeight = (pDC->GetTextMetrics(&tmFont) && GetObject(m_hImageBitmap[0], sizeof(BITMAP), &sImage)) ? (max(sImage.bmHeight, tmFont.tmHeight) + 2 * GetSystemMetrics(SM_CYBORDER)) : lpMeasureItemStruct->itemHeight;
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

void CAlignmentComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC  cDC;
	CDC  cMemDC;
	CRect  rImage;
	CBrush  cBkBrush;
	CBitmap* pOldBitmap;
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
				if (lpDrawItemStruct->itemID >= (UINT)AL_HLEFTVTOP && lpDrawItemStruct->itemID <= (UINT)AL_HRIGHTVBOTTOM)
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

int CAlignmentComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	if (lpCompareItemStruct->itemData1 > lpCompareItemStruct->itemData2) return 1;
	if (lpCompareItemStruct->itemData1 < lpCompareItemStruct->itemData2) return -1;
	return 0;
}

BEGIN_MESSAGE_MAP(CAlignmentComboBox, CComboBox)
	//{{AFX_MSG_MAP(CAlignmentComboBox)
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
// CAlignmentComboBox message handlers

int CAlignmentComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	MEASUREITEMSTRUCT  sItem;

	if (CComboBox::OnCreate(lpCreateStruct) != -1)
	{
		if ((m_hImageBitmap[AL_HLEFTVTOP] = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLLEFTTOP))))
		{
			if ((m_hImageBitmap[AL_HLEFTVCENTER] = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLLEFTMIDDLE))))
			{
				if ((m_hImageBitmap[AL_HLEFTVBOTTOM] = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLLEFTBOTTOM))))
				{
					if ((m_hImageBitmap[AL_HCENTERVTOP] = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLCENTERTOP))))
					{
						if ((m_hImageBitmap[AL_HCENTERVCENTER] = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLCENTERMIDDLE))))
						{
							if ((m_hImageBitmap[AL_HCENTERVBOTTOM] = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLCENTERBOTTOM))))
							{
								if ((m_hImageBitmap[AL_HRIGHTVTOP] = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLRIGHTTOP))))
								{
									if ((m_hImageBitmap[AL_HRIGHTVCENTER] = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLRIGHTMIDDLE))))
									{
										if ((m_hImageBitmap[AL_HRIGHTVBOTTOM] = LoadBitmap(GetLibraryModuleInstance(), MAKEINTRESOURCE(IDB_ALIGNMENTCOMBOBOXSYMBOLRIGHTBOTTOM))))
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

LRESULT CAlignmentComboBox::OnAddAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_ADDSTRING, wParam, lParam);
}

LRESULT CAlignmentComboBox::OnInsertAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_INSERTSTRING, wParam, lParam);
}

LRESULT CAlignmentComboBox::OnGetAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_GETITEMDATA, wParam);
}

LRESULT CAlignmentComboBox::OnFindAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_FINDSTRINGEXACT, wParam, lParam);
}

LRESULT CAlignmentComboBox::OnSelectAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_SELECTSTRING, wParam, lParam);
}

LRESULT CAlignmentComboBox::OnDeleteAlignment(WPARAM wParam, LPARAM lParam)
{
	return SendMessage(CB_DELETESTRING, (WPARAM)SendMessage(CB_FINDSTRINGEXACT, wParam, lParam));
}

LRESULT CAlignmentComboBox::OnResetAlignments(WPARAM wParam, LPARAM lParam)
{
	SendMessage(CB_RESETCONTENT);
	return 0;
}

void CAlignmentComboBox::OnDestroy()
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
// CResourceAlignmentComboBox

IMPLEMENT_DYNCREATE(CResourceAlignmentComboBox, CAlignmentComboBox)

WNDPROC CResourceAlignmentComboBox::m_lpfnSuperWndProc = (WNDPROC)NULL;

CResourceAlignmentComboBox::CResourceAlignmentComboBox(HWND hWnd) : CAlignmentComboBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceAlignmentComboBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceAlignmentComboBox* pResourceAlignmentComboBox;

	if ((pResourceAlignmentComboBox = new CResourceAlignmentComboBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

WNDPROC* CResourceAlignmentComboBox::GetSuperWndProcAddr()
{
	return &m_lpfnSuperWndProc;
}

void CResourceAlignmentComboBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceAlignmentComboBox, CAlignmentComboBox)
	//{{AFX_MSG_MAP(CResourceAlignmentComboBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceAlignmentComboBox message handlers

BOOL CResourceAlignmentComboBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (ALCBS_LEFT | ALCBS_CENTER | ALCBS_RIGHT | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT)) & ~(CBS_SIMPLE | CBS_DROPDOWN | CBS_OWNERDRAWFIXED | CBS_AUTOHSCROLL | CBS_HASSTRINGS | CBS_LOWERCASE | CBS_UPPERCASE | CBS_OEMCONVERT)) | CBS_DROPDOWNLIST | CBS_OWNERDRAWVARIABLE), HIWORD(lpCreateStruct->style)) | WS_CHILD | WS_VSCROLL));
	return CAlignmentComboBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CSpinButtons

IMPLEMENT_DYNCREATE(CSpinButtons, CSpinButtonCtrl)

CSpinButtons::CSpinButtons() : CSpinButtonCtrl()
{
	return;
}

BEGIN_MESSAGE_MAP(CSpinButtons, CSpinButtonCtrl)
	//{{AFX_MSG_MAP(CSpinButtons)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpinButtons message handlers

void CSpinButtons::OnMouseMove(UINT nFlags, CPoint point)
{
	CSpinBox* pSpinBox;
	CTimeSpinBox* pTimeSpinBox;

	if ((pSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CSpinBox))) ? (CSpinBox*)GetParent() : (CSpinBox*)NULL)) pSpinBox->UpdateUI();
	if ((pTimeSpinBox = (GetParent()->IsKindOf(RUNTIME_CLASS(CTimeSpinBox))) ? (CTimeSpinBox*)GetParent() : (CTimeSpinBox*)NULL)) pTimeSpinBox->UpdateUI();
	CSpinButtonCtrl::OnMouseMove(nFlags, point);
}


/////////////////////////////////////////////////////////////////////////////
// CSpinBox

IMPLEMENT_DYNCREATE(CSpinBox, CWnd)

CSpinBox::CSpinBox() : CWnd()
{
	m_dwStyle = 0;
	m_bState[0] = FALSE;
	m_bState[1] = FALSE;
}

BOOL CSpinBox::Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle)
{
	return CWnd::Create((LPCTSTR)NULL, EMPTYSTRING, MAKELONG((((m_dwStyle = ((LOWORD(dwStyle) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LOWERCASE | ES_UPPERCASE | ES_NUMBER | ES_PASSWORD | ES_READONLY | ES_WANTRETURN)))) ? NULL : NULL), HIWORD(dwStyle)) | WS_CHILD, rect, pParentWnd, nID);
}

BOOL CSpinBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CSpinBox  cSpinBox;

	if ((pClass = cSpinBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (szClass.Mid(cPos, 1) != szBaseClass.Mid(cPos, 1)) break;
			continue;
		}
		if (cPos < cbClassName && !GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
		{
			sWndClass.lpszClassName = (LPCTSTR)szClass;
			sWndClass.lpfnWndProc = CResourceSpinBox::WndProcHook;
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

BOOL CSpinBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CSpinBox  cSpinBox;

	if ((pClass = cSpinBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

void CSpinBox::UpdateUI()
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
void CSpinBox::UpdateUI(CONST POINT& point)
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

VOID CSpinBox::RecalcLayout(INT cx, INT cy)
{
	CDC* pDC;
	CRect  rEditCtrl;
	CRect  rSpinCtrl;
	CFont* pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			for (pDC->GetTextMetrics(&tmFont), rEditCtrl.SetRect(tmFont.tmAveCharWidth, (cy - tmFont.tmHeight) / 2, cx - 2 * tmFont.tmAveCharWidth, (cy - tmFont.tmHeight) / 2 + tmFont.tmHeight), rSpinCtrl.SetRect(cx - 3 * cy / 4 + (3 * cy / 4) % 2, 0, cx, cy); (GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_CLIENTEDGE) != WS_EX_CLIENTEDGE; )
			{
				rSpinCtrl.DeflateRect(0, GetSystemMetrics(SM_CYBORDER));
				rSpinCtrl.OffsetRect(-GetSystemMetrics(SM_CXBORDER), 0);
				break;
			}
			if (IsWindow(m_wndEditCtrl.GetSafeHwnd()))
			{
				m_wndEditCtrl.MoveWindow(rEditCtrl.left, rEditCtrl.top, rSpinCtrl.left - rEditCtrl.left, rEditCtrl.Height());
			}
			if (IsWindow(m_wndSpinCtrl.GetSafeHwnd()))
			{
				m_wndSpinCtrl.MoveWindow(rSpinCtrl);
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

BEGIN_MESSAGE_MAP(CSpinBox, CWnd)
	//{{AFX_MSG_MAP(CSpinBox)
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
// CSpinBox message handlers

int CSpinBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		if (m_wndSpinCtrl.Create(UDS_NOTHOUSANDS | ((IsWindowEnabled()) ? (WS_CHILD | WS_VISIBLE) : (WS_CHILD | WS_DISABLED | WS_VISIBLE)), CRect(0, 0, 0, 0), this, 0) && m_wndEditCtrl.Create(this, CRect(0, 0, 0, 0), m_wndSpinCtrl.GetDlgCtrlID() + 1, m_dwStyle | ((IsWindowEnabled()) ? (WS_CHILD | WS_VISIBLE) : WS_CHILD) | (lpCreateStruct->style & WS_TABSTOP)))
		{
			SetWindowPos(&m_wndEditCtrl, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			SetFont(CCustomControls::GetCustomControlFont(this));
			RecalcLayout(lpCreateStruct->cx, lpCreateStruct->cy);
			return 0;
		}
	}
	return -1;
}

BOOL CSpinBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	for (SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~WS_BORDER); !IsThemeActive(); )
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_CLIENTEDGE);
		break;
	}
	return CWnd::OnNcCreate(lpCreateStruct);
}

void CSpinBox::OnSize(UINT nType, int cx, int cy)
{
	RecalcLayout(cx, cy);
	CWnd::OnSize(nType, cx, cy);
}

BOOL CSpinBox::OnEraseBkgnd(CDC* pDC)
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

void CSpinBox::OnEnable(BOOL bEnable)
{
	Invalidate(TRUE);
	m_wndEditCtrl.ShowWindow((bEnable) ? SW_SHOWNA : SW_HIDE);
	m_wndSpinCtrl.EnableWindow(bEnable);
	CWnd::OnEnable(bEnable);
}

void CSpinBox::OnMouseMove(UINT nFlags, CPoint point)
{
	UpdateUI(point);
	CWnd::OnMouseMove(nFlags, point);
}

void CSpinBox::OnSetFocus(CWnd* pOldWnd)
{
	m_wndEditCtrl.SetSel(0, -1);
	m_wndEditCtrl.SetFocus();
}

void CSpinBox::OnTimer(UINT_PTR nTimerID)
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

BOOL CSpinBox::OnCommand(WPARAM wParam, LPARAM lParam)
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

BOOL CSpinBox::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	NMUPDOWN* pNotifyInfo = (NMUPDOWN*)lParam;

	if (pNotifyInfo->hdr.code == UDN_DELTAPOS)
	{
		m_wndEditCtrl.SetPos(m_wndEditCtrl.GetPos() - (LONGLONG)pNotifyInfo->iDelta, TRUE);
		m_wndEditCtrl.SetSel(0, -1);
		m_wndEditCtrl.SetFocus();
		return TRUE;
	}
	return FALSE;
}

LRESULT CSpinBox::OnSetPos(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_SETPOS, wParam, lParam) : FALSE);
}

LRESULT CSpinBox::OnGetPos(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_GETPOS, wParam, lParam) : FALSE);
}

LRESULT CSpinBox::OnSetBase(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_SETBASE, wParam, lParam) : FALSE);
}

LRESULT CSpinBox::OnGetBase(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_GETBASE, wParam, lParam) : FALSE);
}

LRESULT CSpinBox::OnSetRange(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_SETRANGE, wParam, lParam) : FALSE);
}

LRESULT CSpinBox::OnGetRange(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_GETRANGE, wParam, lParam) : FALSE);
}

LRESULT CSpinBox::OnSetAccel(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndSpinCtrl.GetSafeHwnd())) ? m_wndSpinCtrl.SendMessage(UDM_SETACCEL, wParam, lParam) : FALSE);
}

LRESULT CSpinBox::OnGetAccel(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndSpinCtrl.GetSafeHwnd())) ? m_wndSpinCtrl.SendMessage(UDM_GETACCEL, wParam, lParam) : FALSE);
}

LRESULT CSpinBox::OnSetSel(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_SETSEL, wParam, lParam) : FALSE);
}

LRESULT CSpinBox::OnGetSel(WPARAM wParam, LPARAM lParam)
{
	return((IsWindow(m_wndEditCtrl.GetSafeHwnd())) ? m_wndEditCtrl.SendMessage(NEM_GETSEL, wParam, lParam) : FALSE);
}

LRESULT CSpinBox::OnSetFont(WPARAM wParam, LPARAM lParam)
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

LRESULT CSpinBox::OnGetFont(WPARAM wParam, LPARAM lParam)
{
	return((LRESULT)m_cFont.GetSafeHandle());
}

void CSpinBox::OnClose()
{
	GetParent()->SendMessage(WM_CLOSE);
}

void CSpinBox::OnDestroy()
{
	m_cFont.DeleteObject();
	CWnd::OnDestroy();
}

// SpinBox helpers
BOOL Spinbox_SetPos(CWnd* pCtrl, LONGLONG nPos)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETPOS, (WPARAM)NULL, (LPARAM)& nPos));
}

LONGLONG Spinbox_GetPos(CWnd* pCtrl)
{
	LONGLONG nPos;

	pCtrl->SendMessage(SBXM_GETPOS, TRUE, (LPARAM)& nPos);
	return nPos;
}

BOOL Spinbox_SetBase(CWnd* pCtrl, UINT nBase, UINT nDigits)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETBASE, nBase, nDigits));
}

BOOL Spinbox_GetBase(CWnd* pCtrl, UINT& nBase, UINT& nDigits)
{
	return((BOOL)pCtrl->SendMessage(SBXM_GETBASE, (WPARAM)& nBase, (LPARAM)& nDigits));
}

BOOL Spinbox_SetRange(CWnd* pCtrl, LONGLONG nMin, LONGLONG nMax)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETRANGE, (WPARAM)& nMin, (LPARAM)& nMax));
}

BOOL Spinbox_GetRange(CWnd* pCtrl, LONGLONG& nMin, LONGLONG& nMax)
{
	return((BOOL)pCtrl->SendMessage(SBXM_GETRANGE, (WPARAM)& nMin, (LPARAM)& nMax));
}

BOOL Spinbox_SetAccel(CWnd* pCtrl, INT nAccel, CONST UDACCEL* pAccel)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETACCEL, nAccel, (LPARAM)pAccel));
}

UINT Spinbox_GetAccel(CWnd* pCtrl, INT nAccel, UDACCEL* pAccel)
{
	return((UINT)pCtrl->SendMessage(SBXM_GETACCEL, nAccel, (LPARAM)pAccel));
}

BOOL Spinbox_SetSel(CWnd* pCtrl, INT nStartPos, INT nStopPos)
{
	return((BOOL)pCtrl->SendMessage(SBXM_SETSEL, nStartPos, nStopPos));
}

BOOL Spinbox_GetSel(CWnd* pCtrl, INT& nStartPos, INT& nStopPos)
{
	return((BOOL)pCtrl->SendMessage(SBXM_GETSEL, (WPARAM)& nStartPos, (LPARAM)& nStopPos));
}


/////////////////////////////////////////////////////////////////////////////
// CResourceSpinBox

IMPLEMENT_DYNCREATE(CResourceSpinBox, CSpinBox)

CResourceSpinBox::CResourceSpinBox(HWND hWnd) : CSpinBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceSpinBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceSpinBox* pResourceSpinBox;

	if ((pResourceSpinBox = new CResourceSpinBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

void CResourceSpinBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceSpinBox, CSpinBox)
	//{{AFX_MSG_MAP(CResourceSpinBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceSpinBox message handlers

BOOL CResourceSpinBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG(((m_dwStyle = ((LOWORD(lpCreateStruct->style) & (ES_LEFT | ES_CENTER | ES_RIGHT | ES_NOHIDESEL | ES_OEMCONVERT)) & ~(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_LOWERCASE | ES_UPPERCASE | ES_NUMBER | ES_PASSWORD | ES_READONLY | ES_WANTRETURN))) ? NULL : NULL), HIWORD(lpCreateStruct->style)) | WS_CHILD));
	return CSpinBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// CTimeSpinBox

IMPLEMENT_DYNCREATE(CTimeSpinBox, CWnd)

CTimeSpinBox::CTimeSpinBox() : CWnd()
{
	m_dwStyle = 0;
	m_tStartTime = m_tStopTime = 0;
	m_tTime = 1000000 * CTime::GetCurrentTime().GetTime();
	m_bState[0] = m_bState[1] = FALSE;
	m_bVisible = TRUE;
}

BOOL CTimeSpinBox::Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle, LPCTSTR pszFormat, CONST CTimeTag& tStartTime, CONST CTimeTag& tStopTime)
{
	for (m_tStartTime = tStartTime, m_tStopTime = tStopTime; CWnd::Create((LPCTSTR)NULL, (AfxIsValidString(pszFormat)) ? pszFormat : EMPTYSTRING, MAKELONG((((m_dwStyle = LOWORD(dwStyle) & (TSBXS_ANY_TIME | TSBXS_PAST_TIME | TSBXS_FUTURE_TIME | TSBXS_UTC_TIME | TSBXS_SPAN_TIME | TSBXS_HIDE_TIME))) ? NULL : NULL), HIWORD(dwStyle)) | WS_CHILD, rect, pParentWnd, nID); ) return TRUE;
	return FALSE;
}

BOOL CTimeSpinBox::RegisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	WNDCLASS  sWndClass;
	CRuntimeClass* pClass;
	CTimeSpinBox  cTimeSpinBox;

	if ((pClass = cTimeSpinBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
		szBaseClass.ReleaseBuffer();
		szClass.ReleaseBuffer();
#endif
		for (cPos = 0, cbClassName = lstrlen(szBaseClass); cPos < cbClassName; cPos++)
		{
			if (szClass.Mid(cPos, 1) != szBaseClass.Mid(cPos, 1)) break;
			continue;
		}
		if (cPos < cbClassName && !GetClassInfo((sWndClass.hInstance = GetModuleHandle((LPCTSTR)NULL)), (szClass = szClass.Mid(cPos)), &sWndClass))
		{
			sWndClass.lpszClassName = (LPCTSTR)szClass;
			sWndClass.lpfnWndProc = CResourceTimeSpinBox::WndProcHook;
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

BOOL CTimeSpinBox::UnregisterClass()
{
	INT  cPos;
	INT  cbClassName;
	CString  szClass;
	CString  szBaseClass;
	CRuntimeClass* pClass;
	CTimeSpinBox  cTimeSpinBox;

	if ((pClass = cTimeSpinBox.GetRuntimeClass()))
	{
#ifndef UNICODE
		szClass = pClass->m_lpszClassName;
		szBaseClass = CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName;
#else
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClass.GetBufferSetLength((INT)strlen(pClass->m_lpszClassName)), (INT)strlen(pClass->m_lpszClassName) + 1);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName, -1, szBaseClass.GetBufferSetLength((INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName)), (INT)strlen(CCustomControls::GetCustomControlBaseClass(pClass)->m_lpszClassName) + 1);
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

VOID CTimeSpinBox::EnableAutoCompletion(BOOL bEnable)
{
	INT  nCtrl;
	INT  nCtrls;
	CTextEdit* pTextEditCtrl;
	CNumberEdit* pNumberEditCtrl;

	for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pNumberEditCtrl = (IsSubFormatNumericalEditCtrl(m_nCtrlFormat.GetAt(nCtrl))) ? (CNumberEdit*)m_pwndEditCtrls.GetAt(nCtrl) : (CNumberEdit*)NULL))
		{
			pNumberEditCtrl->EnableAutoCompletion(bEnable);
			continue;
		}
		if ((pTextEditCtrl = (!IsSubFormatNumericalEditCtrl(m_nCtrlFormat.GetAt(nCtrl))) ? (CTextEdit*)m_pwndEditCtrls.GetAt(nCtrl) : (CTextEdit*)NULL))
		{
			pTextEditCtrl->EnableAutoCompletion(bEnable);
			continue;
		}
	}
}

BOOL CTimeSpinBox::IsAutoCompletionEnabled() CONST
{
	INT  nCtrl;
	INT  nCtrls;
	CTextEdit* pTextEditCtrl;
	CNumberEdit* pNumberEditCtrl;

	for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pNumberEditCtrl = (IsSubFormatNumericalEditCtrl(m_nCtrlFormat.GetAt(nCtrl))) ? (CNumberEdit*)m_pwndEditCtrls.GetAt(nCtrl) : (CNumberEdit*)NULL))
		{
			if (pNumberEditCtrl->IsAutoCompletionEnabled()) break;
			continue;
		}
		if ((pTextEditCtrl = (!IsSubFormatNumericalEditCtrl(m_nCtrlFormat.GetAt(nCtrl))) ? (CTextEdit*)m_pwndEditCtrls.GetAt(nCtrl) : (CTextEdit*)NULL))
		{
			if (pTextEditCtrl->IsAutoCompletionEnabled()) break;
			continue;
		}
	}
	return(nCtrl < nCtrls);
}

INT CTimeSpinBox::TranslateSubFormat(LPCTSTR pszFormat) CONST
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

BOOL CTimeSpinBox::TranslateSubFormatDelimiter(LPCTSTR pszFormat, CString& szDelimiter) CONST
{
	CString  szFormat(pszFormat);

	for (szDelimiter.Empty(); !szFormat.IsEmpty() && TranslateSubFormat(szFormat) < 0; szFormat = szFormat.Mid(1))
	{
		szDelimiter += szFormat.Left(1);
		continue;
	}
	return !szDelimiter.IsEmpty();
}

BOOL CTimeSpinBox::TranslateSubFormatPosition(LPCTSTR pszFormat, CONST RECT& rect, CRect& rSubFormat)
{
	CDC* pDC;
	INT  nWidth;
	INT  nSubFormat;
	INT  nSubFormats;
	INT  nSubFormatID;
	CFont* pOldFont;
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

LONGLONG CTimeSpinBox::EnumSubFormatLimits(INT nSubFormatID) CONST
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
INT CTimeSpinBox::EnumSubFormatLimits(INT nSubFormatID, CStringArray& szNames) CONST
{
	return m_tTime.EnumSubFormatLimits(nSubFormatID, szNames, (m_dwStyle & TSBXS_UTC_TIME) ? TRUE : FALSE);
}

BOOL CTimeSpinBox::ShowSubControls(BOOL bShow)
{
	INT  nCtrl[2];
	INT  nCtrls[2];
	CWnd* pCtrl[2];

	if (m_dwStyle & TSBXS_HIDE_TIME)
	{
		for (nCtrl[0] = 0, nCtrls[0] = (m_bVisible != bShow) ? (INT)m_pwndEditCtrls.GetSize() : 0; nCtrl[0] < nCtrls[0]; nCtrl[0]++)
		{
			if ((pCtrl[0] = (CWnd*)m_pwndEditCtrls.GetAt(nCtrl[0])))
			{
				pCtrl[0]->ShowWindow((bShow) ? SW_SHOWNA : SW_HIDE);
				continue;
			}
			break;
		}
		for (nCtrl[1] = 0, nCtrls[1] = (m_bVisible != bShow) ? (INT)m_pwndStaticCtrls.GetSize() : 0; nCtrl[1] < nCtrls[1]; nCtrl[1]++)
		{
			if ((pCtrl[1] = (CWnd*)m_pwndStaticCtrls.GetAt(nCtrl[1])))
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

BOOL CTimeSpinBox::IsSubFormatNumericalEditCtrl(INT nSubFormatID) CONST
{
	return((!IsSubFormatDelimiterCtrl(nSubFormatID) && !IsSubFormatEditCtrl(nSubFormatID)) ? TRUE : FALSE);
}

BOOL CTimeSpinBox::IsSubFormatEditCtrl(INT nSubFormatID) CONST
{
	CStringArray  szSubFormats;

	return((!IsSubFormatDelimiterCtrl(nSubFormatID) && EnumSubFormatLimits(nSubFormatID, szSubFormats)) ? TRUE : FALSE);
}

BOOL CTimeSpinBox::IsSubFormatDelimiterCtrl(INT nSubFormatID) CONST
{
	return((nSubFormatID < 0) ? TRUE : FALSE);
}

BOOL CTimeSpinBox::IsTimespanSubFormatID(INT nSubFormatID, BOOL bRightAligned) CONST
{
	return((nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYS || ((nSubFormatID == IDS_TIMEKEY_SUBFORMAT_HOUR || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MINUTE || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_SECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MILLISECOND || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MICROSECOND) && !bRightAligned)) ? TRUE : FALSE);
}

BOOL CTimeSpinBox::IsExistingSubFormatID(INT nSubFormatID) CONST
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

void CTimeSpinBox::UpdateUI()
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
void CTimeSpinBox::UpdateUI(CONST POINT& point)
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

INT CTimeSpinBox::CalcIndent()
{
	CDC* pDC;
	CFont* pOldFont;
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

BEGIN_MESSAGE_MAP(CTimeSpinBox, CWnd)
	//{{AFX_MSG_MAP(CTimeSpinBox)
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
// CTimeSpinBox message handlers

int CTimeSpinBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	INT  nCtrlID;
	INT  nSubFormatID;
	BOOL  bFirstCtrl;
	CRect  rSubCtrl;
	CRect  rEditCtrl;
	CRect  rSpinCtrl;
	CRect  rStaticCtrl;
	CEdit* pEditCtrl;
	CString  szDelimiter;
	CString  szTimeFormat;
	CStatic* pStaticCtrl;
	CTextEdit* pTextEditCtrl;
	CNumberEdit* pNumberEditCtrl;

	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		if (m_tStartTime == 0 && m_tStopTime == 0)
		{
			m_tStartTime = (m_dwStyle & TSBXS_SPAN_TIME) ? -MIN_TIMETAG : MIN_TIMETAG;
			m_tStopTime = (m_dwStyle & TSBXS_SPAN_TIME) ? MIN_TIMETAG : MAX_TIMETAG;
		}
		if (m_wndSpinCtrl.Create(UDS_NOTHOUSANDS | ((IsWindowEnabled()) ? (WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) : (WS_CHILD | WS_CLIPSIBLINGS | WS_DISABLED | WS_VISIBLE)), CRect(0, 0, 0, 0), this, 0))
		{
			for (GetWindowText(szTimeFormat), SetWindowText((szTimeFormat = (szTimeFormat.IsEmpty()) ? STRING(IDS_TIMEKEY_FORMAT) : (LPCTSTR)szTimeFormat)), SetFont(CCustomControls::GetCustomControlFont(this)), rSubCtrl.SetRect(CalcIndent(), 0, CalcIndent(), 0), nCtrlID = m_wndSpinCtrl.GetDlgCtrlID() + 1, bFirstCtrl = TRUE; !szTimeFormat.IsEmpty(); )
			{
				if ((nSubFormatID = TranslateSubFormat(szTimeFormat)) >= 0 && TranslateSubFormatPosition(STRING(nSubFormatID), rSubCtrl, rEditCtrl))
				{
					if (IsSubFormatNumericalEditCtrl(nSubFormatID))
					{
						if ((pNumberEditCtrl = new CNumberEdit))
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
						if ((pTextEditCtrl = new CTextEdit))
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
				if ((pStaticCtrl = (TranslateSubFormatDelimiter(szTimeFormat, szDelimiter) && TranslateSubFormatPosition(szDelimiter, rSubCtrl, rStaticCtrl)) ? new CStatic : (CStatic*)NULL))
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
				if ((pEditCtrl = (CEdit*)m_pwndEditCtrls.GetAt(0)))
				{
					pEditCtrl->DestroyWindow();
					delete pEditCtrl;
				}
			}
			for (; m_pwndStaticCtrls.GetSize() > 0; m_pwndStaticCtrls.RemoveAt(0))
			{
				if ((pStaticCtrl = (CStatic*)m_pwndStaticCtrls.GetAt(0)))
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

BOOL CTimeSpinBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	for (SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_STYLE) & ~WS_BORDER); !IsThemeActive(); )
	{
		SetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE, GetWindowLongPtr(GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_CLIENTEDGE);
		break;
	}
	return CWnd::OnNcCreate(lpCreateStruct);
}

void CTimeSpinBox::OnSize(UINT nType, int cx, int cy)
{
	INT  nCtrl;
	INT  nCtrls;
	CRect  rEditCtrl;
	CRect  rSpinCtrl;
	CRect  rStaticCtrl;
	CEdit* pEditCtrl;
	CStatic* pStaticCtrl;

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
		if ((pEditCtrl = (CEdit*)m_pwndEditCtrls.GetAt(nCtrl)))
		{
			pEditCtrl->GetWindowRect(rEditCtrl);
			ScreenToClient(rEditCtrl);
			rEditCtrl.SetRect(rEditCtrl.left, (cy - rEditCtrl.Height()) / 2, rEditCtrl.right, (cy - rEditCtrl.Height()) / 2 + rEditCtrl.Height());
			pEditCtrl->MoveWindow(rEditCtrl);
		}
	}
	for (nCtrl = 0, nCtrls = (INT)m_pwndStaticCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pStaticCtrl = (CStatic*)m_pwndStaticCtrls.GetAt(nCtrl)))
		{
			pStaticCtrl->GetWindowRect(rStaticCtrl);
			ScreenToClient(rStaticCtrl);
			rStaticCtrl.SetRect(rStaticCtrl.left, (cy - rStaticCtrl.Height()) / 2, rStaticCtrl.right, (cy - rStaticCtrl.Height()) / 2 + rStaticCtrl.Height());
			pStaticCtrl->MoveWindow(rStaticCtrl);
		}
	}
	CWnd::OnSize(nType, cx, cy);
}

HBRUSH CTimeSpinBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return((IsWindowEnabled() && nCtlColor == CTLCOLOR_STATIC) ? (HBRUSH)GetParent()->SendMessage(WM_CTLCOLOREDIT, (WPARAM)pDC->GetSafeHdc(), (LPARAM)pWnd->GetSafeHwnd()) : CWnd::OnCtlColor(pDC, pWnd, nCtlColor));
}

BOOL CTimeSpinBox::OnEraseBkgnd(CDC* pDC)
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

void CTimeSpinBox::OnEnable(BOOL bEnable)
{
	INT  nCtrl;
	INT  nCtrls;
	CEdit* pEditCtrl;
	CStatic* pStaticCtrl;

	for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(), Invalidate(TRUE); nCtrl < nCtrls; nCtrl++)
	{
		if ((pEditCtrl = (CEdit*)m_pwndEditCtrls.GetAt(nCtrl)))
		{
			pEditCtrl->ShowWindow((bEnable) ? SW_SHOWNA : SW_HIDE);
			continue;
		}
	}
	for (nCtrl = 0, nCtrls = (INT)m_pwndStaticCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pStaticCtrl = (CStatic*)m_pwndStaticCtrls.GetAt(nCtrl)))
		{
			pStaticCtrl->ShowWindow((bEnable) ? SW_SHOWNA : SW_HIDE);
			continue;
		}
	}
	m_wndSpinCtrl.EnableWindow(bEnable);
	CWnd::OnEnable(bEnable);
}

void CTimeSpinBox::OnMouseMove(UINT nFlags, CPoint point)
{
	UpdateUI(point);
	CWnd::OnMouseMove(nFlags, point);
}

void CTimeSpinBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_bVisible) SetFocus();
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CTimeSpinBox::OnSetFocus(CWnd* pOldWnd)
{
	CEdit* pEditCtrl;

	for (ShowSubControls(); (pEditCtrl = (m_pwndEditCtrls.GetSize() > 0) ? (CEdit*)m_pwndEditCtrls.GetAt(0) : (CEdit*)NULL); )
	{
		pEditCtrl->SetSel(0, -1);
		pEditCtrl->SetFocus();
		break;
	}
}

void CTimeSpinBox::OnTimer(UINT_PTR nTimerID)
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

BOOL CTimeSpinBox::OnCommand(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	CWnd* pCtrl;
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
		if (CWnd::GetFocus() != this && !IsChild(CWnd::GetFocus()))
		{
			for (GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), TSBXN_KILLFOCUS), (LPARAM)GetSafeHwnd()), m_bState[0] = FALSE; IsThemeActive(); )
			{
				RedrawWindow();
				break;
			}
			for (nCtrl = 0, nCtrls = ((m_dwStyle & TSBXS_HIDE_TIME) && m_bVisible) ? (INT)m_pwndEditCtrls.GetSize() : 0; nCtrl < nCtrls; nCtrl++)
			{
				if ((pCtrl = (CWnd*)m_pwndEditCtrls.GetAt(nCtrl)))
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

BOOL CTimeSpinBox::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	INT  nCtrl;
	INT  nCtrls;
	INT  nFormat;
	CEdit* pEditCtrl;
	CTextEdit* pTextEditCtrl;
	CNumberEdit* pNumberEditCtrl;
	NMUPDOWN* pNotifyInfo = (NMUPDOWN*)lParam;

	if (pNotifyInfo->hdr.code == UDN_DELTAPOS)
	{
		for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(), ShowSubControls(); nCtrl < nCtrls; nCtrl++)
		{
			if (!CWnd::GetFocus() || !IsChild(CWnd::GetFocus()))
			{
				if ((pEditCtrl = (CEdit*)m_pwndEditCtrls.GetAt(0)))
				{
					pEditCtrl->SetSel(0, -1);
					pEditCtrl->SetFocus();
				}
			}
			if (IsSubFormatNumericalEditCtrl((nFormat = m_nCtrlFormat.GetAt(nCtrl))))
			{
				if ((pNumberEditCtrl = (CNumberEdit*)m_pwndEditCtrls.GetAt(nCtrl)) && CWnd::GetFocus() == (CWnd*)pNumberEditCtrl)
				{
					pNumberEditCtrl->SetPos(pNumberEditCtrl->GetPos() - pNotifyInfo->iDelta, TRUE);
					pNumberEditCtrl->SetSel(0, -1);
					pNumberEditCtrl->SetFocus();
					break;
				}
				continue;
			}
			if ((pTextEditCtrl = (CTextEdit*)m_pwndEditCtrls.GetAt(nCtrl)) && CWnd::GetFocus() == (CWnd*)pTextEditCtrl)
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

LRESULT CTimeSpinBox::OnSetTime(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	INT  nLimits[2];
	INT  nSubFormatID;
	BOOL  bFirstSubFormat;
	CString  szNumber;
	TIMETAG  tTime[2];
	CTimeTag  tTimeTag;
	CTextEdit* pTextEditCtrl;
	CNumberEdit* pNumberEditCtrl;
	CStringArray  szCtrlFormatNames;
	CStringTools  cStringTools;

	for (CopyMemory(&tTime[0], (LPCVOID)lParam, sizeof(tTime[0])), ShowSubControls(((m_dwStyle& TSBXS_SPAN_TIME) || tTime[0] > 0) ? TRUE : FALSE), tTime[0] = ((m_dwStyle & TSBXS_SPAN_TIME) == 0) ? abs(tTime[0]) : ((!wParam) ? tTime[0] : 0), tTime[1] = tTimeTag.GetTime(), tTime[0] = ((m_dwStyle & TSBXS_SPAN_TIME) == 0 && !tTime[0]) ? tTime[1] : tTime[0]; m_dwStyle & TSBXS_PAST_TIME; )
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
			if ((pNumberEditCtrl = (CNumberEdit*)m_pwndEditCtrls.GetAt(nCtrl)))
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
		if ((pTextEditCtrl = (CTextEdit*)m_pwndEditCtrls.GetAt(nCtrl)))
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

LRESULT CTimeSpinBox::OnGetTime(WPARAM wParam, LPARAM lParam)
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
	CNumberEdit* pNumberEditCtrl;
	CTextEdit* pTextEditCtrl;

	for (nSubFormatID = (!m_bVisible) ? (MAXTIMETAGSUBFORMAT + 1) : MINTIMETAGSUBFORMAT, tActualTime.wYear = m_tTime.GetYear(), tActualTime.wMonth = m_tTime.GetMonth(), tActualTime.wDayOfWeek = m_tTime.GetDayOfWeek() - 1, tActualTime.wDay = m_tTime.GetDay(), tActualTime.wHour = m_tTime.GetHour(), tActualTime.wMinute = m_tTime.GetMinute(), tActualTime.wSecond = m_tTime.GetSecond(), tActualTime.wMilliseconds = m_tTime.GetMilliSeconds(), tFlagTime.wYear = (WORD)-1, tFlagTime.wMonth = (WORD)-1, tFlagTime.wDayOfWeek = (WORD)-1, tFlagTime.wDay = (WORD)-1, tFlagTime.wHour = (WORD)-1, tFlagTime.wMinute = (WORD)-1, tFlagTime.wSecond = (WORD)-1, tFlagTime.wMilliseconds = (WORD)-1, wMicroseconds = (WORD)-1, nDays = nHour = nMinute = nSecond = nMilliseconds = nMicroseconds = 0, bCorrection = bMinusZero = FALSE; nSubFormatID <= MAXTIMETAGSUBFORMAT; nSubFormatID++)
	{
		for (nCtrl = 0, nCtrls = (INT)m_nCtrlFormat.GetSize(); nCtrl < nCtrls; nCtrl++)
		{
			if (nSubFormatID == (INT)m_nCtrlFormat.GetAt(nCtrl)) break;
			continue;
		}
		if (nCtrl < nCtrls && IsSubFormatNumericalEditCtrl(nSubFormatID))
		{
			if ((pNumberEditCtrl = (CNumberEdit*)m_pwndEditCtrls.GetAt(nCtrl)) && pNumberEditCtrl->Check())
			{
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAR)
				{
					if (CWnd::GetFocus() == (CWnd*)pNumberEditCtrl || tFlagTime.wYear == (WORD)-1)
					{
						tActualTime.wYear = tFlagTime.wYear = (WORD)pNumberEditCtrl->GetPos();
					}
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_YEAROFCENTURY)
				{
					if (CWnd::GetFocus() == (CWnd*)pNumberEditCtrl || tFlagTime.wYear == (WORD)-1)
					{
						tActualTime.wYear = tFlagTime.wYear = (WORD)pNumberEditCtrl->GetPos() + 100 * (tActualTime.wYear / 100);
					}
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTH)
				{
					if (CWnd::GetFocus() == (CWnd*)pNumberEditCtrl || tFlagTime.wMonth == (WORD)-1)
					{
						tActualTime.wMonth = tFlagTime.wMonth = (WORD)pNumberEditCtrl->GetPos();
					}
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKOFYEAR)
				{
					CTimeTag  tTimeConversion(CTimeTag(tActualTime).GetTime() + (pNumberEditCtrl->GetPos() - _ttoi64(CTimeTag(tActualTime).Format(nSubFormatID))) * 1000000 * (TIMETAG)SECONDSPERWEEK);

					if (CWnd::GetFocus() == (CWnd*)pNumberEditCtrl || (tFlagTime.wMonth == (WORD)-1 && tFlagTime.wDay == (WORD)-1) || (tActualTime.wMonth == (WORD)tTimeConversion.GetMonth() && tFlagTime.wDay == (WORD)-1))
					{
						tActualTime.wMonth = tFlagTime.wMonth = tTimeConversion.GetMonth();
						tActualTime.wDay = tFlagTime.wDay = tTimeConversion.GetDay();
					}
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFYEAR)
				{
					CTimeTag  tTimeConversion(tActualTime.wYear, (INT)pNumberEditCtrl->GetPos(), 0, 0, 0, 0, 0);

					if (CWnd::GetFocus() == (CWnd*)pNumberEditCtrl || (tFlagTime.wMonth == (WORD)-1 && tFlagTime.wDay == (WORD)-1) || (tActualTime.wMonth == (WORD)tTimeConversion.GetMonth() && tFlagTime.wDay == (WORD)-1))
					{
						tActualTime.wMonth = tFlagTime.wMonth = tTimeConversion.GetMonth();
						tActualTime.wDay = tFlagTime.wDay = tTimeConversion.GetDay();
					}
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFMONTH)
				{
					if (CWnd::GetFocus() == (CWnd*)pNumberEditCtrl || tFlagTime.wDay == (WORD)-1) tActualTime.wDay = tFlagTime.wDay = (WORD)pNumberEditCtrl->GetPos();
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_DAYOFWEEK)
				{
					CTimeTag  tTimeConversion(CTimeTag(tActualTime).GetTime() + (pNumberEditCtrl->GetPos() - CTimeTag(tActualTime).GetDayOfWeek()) * 1000000 * (TIMETAG)SECONDSPERDAY);

					if (CWnd::GetFocus() == (CWnd*)pNumberEditCtrl || (tFlagTime.wMonth == (WORD)-1 && tFlagTime.wDay == (WORD)-1) || (tActualTime.wMonth == (WORD)tTimeConversion.GetMonth() && tFlagTime.wDay == (WORD)-1))
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
			if ((pTextEditCtrl = (CTextEdit*)m_pwndEditCtrls.GetAt(nCtrl)) && pTextEditCtrl->Check())
			{
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MONTHMNEMONIC)
				{
					if (CWnd::GetFocus() == (CWnd*)pTextEditCtrl || tFlagTime.wMonth == (WORD)-1) tActualTime.wMonth = tFlagTime.wMonth = pTextEditCtrl->GetPos() + 1;
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYNAME || nSubFormatID == IDS_TIMEKEY_SUBFORMAT_WEEKDAYMNEMONIC)
				{
					CTimeTag  tTimeConversion(CTimeTag(tActualTime).GetTime() + ((TIMETAG)pTextEditCtrl->GetPos() % DAYSPERWEEK - ((TIMETAG)CTimeTag(tActualTime).GetDayOfWeek() + Thursday) % DAYSPERWEEK) * 1000000 * (TIMETAG)SECONDSPERDAY);

					if (CWnd::GetFocus() == (CWnd*)pTextEditCtrl || (tFlagTime.wMonth == (WORD)-1 && tFlagTime.wDay == (WORD)-1) || (tActualTime.wMonth == tTimeConversion.GetMonth() && tFlagTime.wDay == (WORD)-1))
					{
						tActualTime.wDayOfWeek = tFlagTime.wDayOfWeek = tTimeConversion.GetDayOfWeek() - 1;
						tActualTime.wMonth = tFlagTime.wMonth = tTimeConversion.GetMonth();
						tActualTime.wDay = tFlagTime.wDay = tTimeConversion.GetDay();
					}
					continue;
				}
				if (nSubFormatID == IDS_TIMEKEY_SUBFORMAT_MERIDIANINDICATOR)
				{
					if (CWnd::GetFocus() == (CWnd*)pTextEditCtrl) tActualTime.wHour = tFlagTime.wHour = (pTextEditCtrl->GetPos() > 0) ? ((tActualTime.wHour < TIMESPINBOXHIGHLIMIT(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR))) ? (tActualTime.wHour + TIMESPINBOXHIGHLIMIT(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR))) : tActualTime.wHour) : ((tActualTime.wHour == TIMESPINBOXHIGHLIMIT(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR))) ? (tActualTime.wHour - TIMESPINBOXHIGHLIMIT(EnumSubFormatLimits(IDS_TIMEKEY_SUBFORMAT_MERIDIANHOUR))) : tActualTime.wHour);
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
			CopyMemory((LPVOID)lParam, &(tTime[0] = (nDays >= 0 && nHour >= 0 && nMinute >= 0 && nSecond >= 0 && nMilliseconds >= 0 && nMicroseconds >= 0 && !bMinusZero) ? (1000000 * ((TIMETAG)nDays * SECONDSPERDAY + (TIMETAG)nHour * SECONDSPERHOUR + (TIMETAG)nMinute * SECONDSPERMINUTE + (TIMETAG)nSecond) + 1000 * (TIMETAG)nMilliseconds + (TIMETAG)nMicroseconds) : (-1000000 * ((TIMETAG)abs(nDays) * SECONDSPERDAY + (TIMETAG)abs(nHour) * SECONDSPERHOUR + (TIMETAG)abs(nMinute) * SECONDSPERMINUTE + (TIMETAG)abs(nSecond)) - 1000 * (TIMETAG)abs(nMilliseconds) - (TIMETAG)abs(nMicroseconds))), sizeof(TIMETAG));
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

LRESULT CTimeSpinBox::OnSetRange(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	INT  nOffset;
	BOOL  bFirstCtrl;
	CWnd* pCtrl[2];
	CRect  rCtrl[2];
	TIMETAG  tTime[2];
	CTimeTag  tTimeTag[2];
	CNumberEdit* pNumberEditCtrl;

	for (CopyMemory(&tTime[0], (LPCVOID)wParam, sizeof(tTime[0])), CopyMemory(&tTime[1], (LPCVOID)lParam, sizeof(tTime[1])), GetTime(tTimeTag[0]); (m_dwStyle & TSBXS_PAST_TIME) && (m_dwStyle & TSBXS_SPAN_TIME) == 0; )
	{
		if (tTimeTag[1].GetTime() >= tTime[1] && tTime[0] < tTime[1])
		{
			if (tTimeTag[0].GetTime() < tTime[0])
			{
				SetTime(CTimeTag(tTime[0]));
			}
			if (tTimeTag[0].GetTime() > tTime[1])
			{
				SetTime(CTimeTag(tTime[1]));
			}
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
			if (tTimeTag[0].GetTime() < tTime[0])
			{
				SetTime(CTimeTag(tTime[0]));
			}
			if (tTimeTag[0].GetTime() > tTime[1])
			{
				SetTime(CTimeTag(tTime[1]));
			}
			m_tStartTime = tTime[0];
			m_tStopTime = tTime[1];
			return TRUE;
		}
	}
	if (tTime[0] <= tTime[1])
	{
		if (tTimeTag[0].GetTime() < tTime[0])
		{
			SetTime(CTimeTag(tTime[0]));
		}
		if (tTimeTag[0].GetTime() > tTime[1])
		{
			SetTime(CTimeTag(tTime[1]));
		}
		for (nCtrl = 0, nCtrls = (INT)m_nCtrlFormat.GetSize(), m_tStartTime = tTime[0], m_tStopTime = tTime[1]; nCtrl < nCtrls; nCtrl++)
		{
			if ((pCtrl[0] = pCtrl[1] = (m_nCtrlFormat.GetAt(nCtrl) == IDS_TIMEKEY_SUBFORMAT_DAYS) ? GetDlgItem(m_wndSpinCtrl.GetDlgCtrlID() + nCtrl + 1) : (CWnd*)NULL))
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
			if ((pNumberEditCtrl = (IsSubFormatNumericalEditCtrl(m_nCtrlFormat.GetAt(nCtrl))) ? (CNumberEdit*)GetDlgItem(m_wndSpinCtrl.GetDlgCtrlID() + nCtrl + 1) : (CNumberEdit*)NULL))
			{
				pNumberEditCtrl->EnableMinusZero((m_tStartTime < 0) ? bFirstCtrl : FALSE);
				bFirstCtrl = FALSE;
			}
		}
		return TRUE;
	}
	return FALSE;
}

LRESULT CTimeSpinBox::OnGetRange(WPARAM wParam, LPARAM lParam)
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

LRESULT CTimeSpinBox::OnSetSel(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	CEdit* pEditCtrl;

	for (nCtrl = HIWORD(wParam), nCtrls = (INT)m_pwndEditCtrls.GetSize(); (pEditCtrl = (nCtrl >= 0 && nCtrl < nCtrls) ? (CEdit*)m_pwndEditCtrls.GetAt(nCtrl) : (CEdit*)NULL); )
	{
		pEditCtrl->SetSel(LOWORD(wParam), LOWORD(lParam));
		pEditCtrl->SetFocus();
		return TRUE;
	}
	return FALSE;
}

LRESULT CTimeSpinBox::OnGetSel(WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl;
	INT  nCtrls;
	INT* nSel[2];
	CEdit* pEditCtrl;

	for (nCtrl = 0, nCtrls = (INT)m_pwndEditCtrls.GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pEditCtrl = (CEdit*)m_pwndEditCtrls.GetAt(nCtrl)) && CWnd::GetFocus() == (CWnd*)pEditCtrl)
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

LRESULT CTimeSpinBox::OnSetFont(WPARAM wParam, LPARAM lParam)
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
	CStatic* pStaticCtrl;
	CTextEdit* pTextEditCtrl;
	CNumberEdit* pNumberEditCtrl;

	for (m_cFont.DeleteObject(); GetObject((HGDIOBJ)wParam, sizeof(LOGFONT), &lfFont) > 0 && m_cFont.CreateFontIndirect(&lfFont); )
	{
		for (GetWindowText(szTimeFormat), rSubCtrl.SetRect(CalcIndent(), 0, CalcIndent(), 0), nCtrlID = m_wndSpinCtrl.GetDlgCtrlID() + 1, nStaticCtrl = 0; !szTimeFormat.IsEmpty(); )
		{
			if ((nFormat = TranslateSubFormat(szTimeFormat)) >= 0 && TranslateSubFormatPosition(STRING(nFormat), rSubCtrl, rEditCtrl))
			{
				if (IsSubFormatNumericalEditCtrl(nFormat))
				{
					if ((pNumberEditCtrl = (CNumberEdit*)GetDlgItem(nCtrlID)))
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
					if ((pTextEditCtrl = (CTextEdit*)GetDlgItem(nCtrlID)))
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
			if ((pStaticCtrl = (TranslateSubFormatDelimiter(szTimeFormat, szDelimiter) && TranslateSubFormatPosition(szDelimiter, rSubCtrl, rStaticCtrl) && nStaticCtrl < m_pwndStaticCtrls.GetSize()) ? (CStatic*)m_pwndStaticCtrls.GetAt(nStaticCtrl) : (CStatic*)NULL))
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

LRESULT CTimeSpinBox::OnGetFont(WPARAM wParam, LPARAM lParam)
{
	return((LRESULT)m_cFont.GetSafeHandle());
}

void CTimeSpinBox::OnClose()
{
	GetParent()->SendMessage(WM_CLOSE);
}

void CTimeSpinBox::OnDestroy()
{
	CEdit* pEditCtrl;
	CStatic* pStaticCtrl;

	for (; m_pwndEditCtrls.GetSize() > 0; m_pwndEditCtrls.RemoveAt(0), m_nCtrlFormat.RemoveAt(0))
	{
		if ((pEditCtrl = (CEdit*)m_pwndEditCtrls.GetAt(0)))
		{
			pEditCtrl->DestroyWindow();
			delete pEditCtrl;
		}
	}
	for (; m_pwndStaticCtrls.GetSize() > 0; m_pwndStaticCtrls.RemoveAt(0))
	{
		if ((pStaticCtrl = (CStatic*)m_pwndStaticCtrls.GetAt(0)))
		{
			pStaticCtrl->DestroyWindow();
			delete pStaticCtrl;
		}
	}
	m_cFont.DeleteObject();
	CWnd::OnDestroy();
}

// TimeSpinBox helpers
VOID Timespinbox_SetTime(CWnd* pCtrl)
{
	TIMETAG  t = CTimeTag().GetTime();

	pCtrl->SendMessage(TSBXM_SETTIME, TRUE, (LPARAM)& t);
}
VOID Timespinbox_SetTime(CWnd* pCtrl, CONST CTimeTag& tTime)
{
	TIMETAG  t = tTime.GetTime();

	pCtrl->SendMessage(TSBXM_SETTIME, (WPARAM)NULL, (LPARAM)& t);
}
VOID Timespinbox_SetTime(CWnd* pCtrl, CONST CTimeKey& tTime)
{
	TIMETAG  t = 1000000 * tTime.GetTime();

	pCtrl->SendMessage(TSBXM_SETTIME, (WPARAM)NULL, (LPARAM)& t);
}

CTimeKey Timespinbox_GetTime(CWnd* pCtrl)
{
	TIMETAG  t;

	return((pCtrl->SendMessage(TSBXM_GETTIME, (WPARAM)NULL, (LPARAM)& t)) ? (t / 1000000) : 0);
}
BOOL Timespinbox_GetTime(CWnd* pCtrl, CTimeTag& tTime)
{
	TIMETAG  t;

	if (pCtrl->SendMessage(TSBXM_GETTIME, (WPARAM)NULL, (LPARAM)& t))
	{
		tTime = t;
		return TRUE;
	}
	return FALSE;
}
BOOL Timespinbox_GetTime(CWnd* pCtrl, CTimeKey& tTime)
{
	TIMETAG  t;

	if (pCtrl->SendMessage(TSBXM_GETTIME, (WPARAM)NULL, (LPARAM)& t))
	{
		tTime = t / 1000000;
		return TRUE;
	}
	return FALSE;
}

BOOL Timespinbox_SetRange(CWnd* pCtrl, CONST CTimeTag& tStartTime, CONST CTimeTag& tStopTime)
{
	TIMETAG  t[2] = { tStartTime.GetTime(),tStopTime.GetTime() };

	return((BOOL)pCtrl->SendMessage(TSBXM_SETRANGE, (WPARAM)& t[0], (LPARAM)& t[1]));
}
BOOL Timespinbox_SetRange(CWnd* pCtrl, CONST CTimeKey& tStartTime, CONST CTimeKey& tStopTime)
{
	TIMETAG  t[2] = { 1000000 * tStartTime.GetTime(),1000000 * tStopTime.GetTime() };

	return((BOOL)pCtrl->SendMessage(TSBXM_SETRANGE, (WPARAM)& t[0], (LPARAM)& t[1]));
}

BOOL Timespinbox_GetRange(CWnd* pCtrl, CTimeTag& tStartTime, CTimeTag& tStopTime)
{
	TIMETAG  t[2];

	if (pCtrl->SendMessage(TSBXM_GETRANGE, (WPARAM)& t[0], (LPARAM)& t[1]))
	{
		tStartTime = t[0];
		tStopTime = t[1];
		return TRUE;
	}
	return FALSE;
}
BOOL Timespinbox_GetRange(CWnd* pCtrl, CTimeKey& tStartTime, CTimeKey& tStopTime)
{
	TIMETAG  t[2];

	if (pCtrl->SendMessage(TSBXM_GETRANGE, (WPARAM)& t[0], (LPARAM)& t[1]))
	{
		tStartTime = t[0] / 1000000;
		tStopTime = t[1] / 1000000;
		return TRUE;
	}
	return FALSE;
}

BOOL Timespinbox_SetSel(CWnd* pCtrl, INT nStartPos, INT nStopPos)
{
	return((BOOL)pCtrl->SendMessage(TSBXM_SETSEL, nStartPos, nStopPos));
}

BOOL Timespinbox_GetSel(CWnd* pCtrl, INT& nStartPos, INT& nStopPos)
{
	return((BOOL)pCtrl->SendMessage(TSBXM_GETSEL, (WPARAM)& nStartPos, (LPARAM)& nStopPos));
}


/////////////////////////////////////////////////////////////////////////////
// CResourceTimeSpinBox

IMPLEMENT_DYNCREATE(CResourceTimeSpinBox, CTimeSpinBox)

CResourceTimeSpinBox::CResourceTimeSpinBox(HWND hWnd) : CTimeSpinBox()
{
	Attach(hWnd);
}

LRESULT CALLBACK CResourceTimeSpinBox::WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CResourceTimeSpinBox* pResourceTimeSpinBox;

	if ((pResourceTimeSpinBox = new CResourceTimeSpinBox(hWnd)))
	{
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)AfxWndProc);
		return CallWindowProc(AfxWndProc, hWnd, message, wParam, lParam);
	}
	return ::DefWindowProc(hWnd, message, wParam, lParam);
}

void CResourceTimeSpinBox::PostNcDestroy()
{
	delete this;
}

BEGIN_MESSAGE_MAP(CResourceTimeSpinBox, CTimeSpinBox)
	//{{AFX_MSG_MAP(CResourceTimeSpinBox)
	ON_WM_NCCREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceTimeSpinBox message handlers

BOOL CResourceTimeSpinBox::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetWindowLongPtr(GetSafeHwnd(), GWL_STYLE, (lpCreateStruct->style = MAKELONG(((m_dwStyle = LOWORD(lpCreateStruct->style) & (TSBXS_ANY_TIME | TSBXS_PAST_TIME | TSBXS_FUTURE_TIME | TSBXS_UTC_TIME | TSBXS_SPAN_TIME | TSBXS_HIDE_TIME)) ? NULL : NULL), HIWORD(lpCreateStruct->style)) | WS_CHILD));
	return CTimeSpinBox::OnNcCreate(lpCreateStruct);
}


/////////////////////////////////////////////////////////////////////////////
// ListBox helpers

BOOL Listbox_SetText(CWnd* pCtrl, INT nItem, LPCTSTR pszText)
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

CString Listbox_GetText(CWnd* pCtrl, INT nItem)
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

BOOL Combobox_SetText(CWnd* pCtrl, INT nItem, LPCTSTR pszText)
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

CString Combobox_GetText(CWnd* pCtrl, INT nItem)
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

BOOL Listview_InsertColumn(CWnd* pCtrl, INT nColumn, LPCTSTR pszColumn, INT nWidth)
{
	LVCOLUMN  sColumn;

	sColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	sColumn.fmt = LVCFMT_LEFT;
	sColumn.cx = nWidth;
	sColumn.pszText = (LPTSTR)pszColumn;
	sColumn.cchTextMax = lstrlen(pszColumn) + 1;
	return((pCtrl->SendMessage(LVM_INSERTCOLUMN, nColumn, (LPARAM)& sColumn) >= 0) ? TRUE : FALSE);
}

BOOL Listview_SetColumn(CWnd* pCtrl, INT nColumn, LPCTSTR pszColumn, INT nWidth)
{
	LVCOLUMN  sColumn;

	sColumn.mask = (nWidth >= 0) ? (LVCF_TEXT | LVCF_WIDTH) : LVCF_TEXT;
	sColumn.cx = (nWidth >= 0) ? nWidth : 0;
	sColumn.pszText = (LPTSTR)pszColumn;
	sColumn.cchTextMax = lstrlen(pszColumn) + 1;
	return((pCtrl->SendMessage(LVM_SETCOLUMN, nColumn, (LPARAM)& sColumn)) ? TRUE : FALSE);
}

BOOL Listview_GetColumn(CWnd* pCtrl, INT nColumn, CString& szColumn, INT& nWidth)
{
	LVCOLUMN  sColumn;
	TCHAR  szText[1024];

	sColumn.mask = LVCF_TEXT | LVCF_WIDTH;
	sColumn.pszText = (LPTSTR)szText;
	sColumn.cchTextMax = sizeof(szText) / sizeof(TCHAR) - 1;
	if (pCtrl->SendMessage(LVM_GETCOLUMN, nColumn, (LPARAM)& sColumn))
	{
		szColumn = sColumn.pszText;
		nWidth = sColumn.cx;
		return TRUE;
	}
	return FALSE;
}

BOOL Listview_DeleteColumn(CWnd* pCtrl, INT nColumn)
{
	return((pCtrl->SendMessage(LVM_DELETECOLUMN, nColumn)) ? TRUE : FALSE);
}

BOOL Listview_InsertText(CWnd* pCtrl, INT nItem, LPCTSTR pszText)
{
	LVITEM  sItem;

	sItem.iItem = nItem;
	sItem.iSubItem = 0;
	sItem.mask = LVIF_TEXT;
	sItem.pszText = (LPTSTR)pszText;
	sItem.cchTextMax = lstrlen(pszText) + 1;
	return((pCtrl->SendMessage(LVM_INSERTITEM, (WPARAM)NULL, (LPARAM)& sItem) >= 0) ? TRUE : FALSE);
}

BOOL Listview_SetText(CWnd* pCtrl, INT nItem, INT nSubItem, LPCTSTR pszText)
{
	LVITEM  sItem;

	sItem.iItem = nItem;
	sItem.iSubItem = nSubItem;
	sItem.mask = LVIF_TEXT;
	sItem.pszText = (LPTSTR)pszText;
	sItem.cchTextMax = lstrlen(pszText) + 1;
	return((pCtrl->SendMessage(LVM_SETITEM, (WPARAM)NULL, (LPARAM)& sItem)) ? TRUE : FALSE);
}

CString Listview_GetText(CWnd* pCtrl, INT nItem, INT nSubItem)
{
	LVITEM  sItem;
	TCHAR  szText[1024];

	sItem.iItem = nItem;
	sItem.iSubItem = nSubItem;
	sItem.mask = LVIF_TEXT;
	sItem.pszText = szText;
	sItem.cchTextMax = sizeof(szText) / sizeof(TCHAR) - 1;
	return((pCtrl->SendMessage(LVM_GETITEM, (WPARAM)NULL, (LPARAM)& sItem)) ? sItem.pszText : EMPTYSTRING);
}

BOOL Listview_SetCurText(CWnd* pCtrl, INT nItem)
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
		if (!pCtrl->SendMessage(LVM_SETITEM, (WPARAM)NULL, (LPARAM)& sItem)) break;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

INT Listview_GetCurText(CWnd* pCtrl)
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
		if (pCtrl->SendMessage(LVM_GETITEM, (WPARAM)NULL, (LPARAM)& sItem) && sItem.state == LVIS_SELECTED) break;
	}
	return((nIndex < nCount) ? nIndex : -1);
}

BOOL Listview_SetSelText(CWnd* pCtrl, CONST CUIntArray& nItems)
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
		if (!pCtrl->SendMessage(LVM_SETITEM, (WPARAM)NULL, (LPARAM)& sItem)) break;
	}
	return((nIndex[0] == nCount[0]) ? TRUE : FALSE);
}

BOOL Listview_IsSelText(CWnd* pCtrl, INT nItem)
{
	LVITEM  sItem;

	sItem.iItem = nItem;
	sItem.iSubItem = 0;
	sItem.mask = LVIF_STATE;
	sItem.stateMask = LVIS_SELECTED;
	return((pCtrl->SendMessage(LVM_GETITEM, (WPARAM)NULL, (LPARAM)& sItem) && sItem.state == LVIS_SELECTED) ? TRUE : FALSE);
}

INT Listview_GetSelText(CWnd* pCtrl, CUIntArray& nItems)
{
	INT  nIndex;
	INT  nCount;
	LVITEM  sItem;

	for (nIndex = 0, nCount = (INT)pCtrl->SendMessage(LVM_GETITEMCOUNT), nItems.RemoveAll(); nIndex < nCount; nIndex++)
	{
		for (sItem.iItem = nIndex, sItem.iSubItem = 0, sItem.mask = LVIF_STATE, sItem.stateMask = LVIS_SELECTED; pCtrl->SendMessage(LVM_GETITEM, (WPARAM)NULL, (LPARAM)& sItem) && sItem.state == LVIS_SELECTED; )
		{
			nItems.Add(nIndex);
			break;
		}
	}
	return((INT)nItems.GetSize());
}

BOOL Listview_DeleteText(CWnd* pCtrl, INT nItem)
{
	return((pCtrl->SendMessage(LVM_DELETEITEM, nItem)) ? TRUE : FALSE);
}
