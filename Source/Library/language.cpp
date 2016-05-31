// LANGUAGE.CPP : Language Localization Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the language
// localization related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1994/07/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CLocaleDialog dialog

IMPLEMENT_DYNCREATE(CLocaleDialog, CDialogEx)

CLocaleDialog::CLocaleDialog() : CDialogEx()
{
	m_hCtrlWnd = (HWND)NULL;
	m_hChildWnd = (HWND)NULL;
	m_hChildSheet = (HWND)NULL;
}
CLocaleDialog::CLocaleDialog(UINT nDialogID, CWnd *pParentWnd) : CDialogEx()
{
	LPVOID  pDialogTemplate;

	for (m_hCtrlWnd = (HWND)NULL, m_hChildWnd = (HWND)NULL, m_hChildSheet = (HWND)NULL, m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(nDialogID))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}
CLocaleDialog::CLocaleDialog(LPCTSTR pszDialogName, CWnd *pParentWnd) : CDialogEx()
{
	LPVOID  pDialogTemplate;

	for (m_hCtrlWnd = (HWND)NULL, m_hChildWnd = (HWND)NULL, m_hChildSheet = (HWND)NULL, m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(pszDialogName)); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

BOOL CLocaleDialog::Create(UINT nDialogID, CWnd *pParentWnd)
{
	LPVOID  pDialogTemplate;

	return(((pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(nDialogID)))) ? CreateIndirect(pDialogTemplate, (m_pParentWnd = (IsWindow(pParentWnd->GetSafeHwnd())) ? pParentWnd : m_pParentWnd)) : FALSE);
}
BOOL CLocaleDialog::Create(LPCTSTR pszDialogName, CWnd *pParentWnd)
{
	LPVOID  pDialogTemplate;

	return(((pDialogTemplate = LoadLocaleDialogTemplate(pszDialogName))) ? CreateIndirect(pDialogTemplate, (m_pParentWnd = (IsWindow(pParentWnd->GetSafeHwnd())) ? pParentWnd : m_pParentWnd)) : FALSE);
}

BOOL CLocaleDialog::Initialize()
{
	return TRUE;
}

CWnd *CLocaleDialog::GetParent() CONST
{
	return m_pParentWnd;
}

BOOL CLocaleDialog::AccessControl(UINT nCtrlID, BOOL bAccess, BOOL bVisible, BOOL bSelections)
{
	INT  nCtrl;
	INT  nCtrls;
	RECT  rControl;
	CWnd  *pCtrl[2];
	CRect  rCtrl[2];
	CComboBox  *pComboBox;
	SCROLLINFO  sScrollInfo[2];
	COMBOBOXINFO  sComboBox;

	for (nCtrl = 0, nCtrls = (INT)m_nCtrlIDs[0].GetSize(), GetDlgItem(nCtrlID)->ShowWindow((bVisible) ? SW_SHOW : SW_HIDE), GetDlgItem(nCtrlID)->GetWindowRect(rCtrl[0]), ScreenToClient(rCtrl[0]), sComboBox.cbSize = sizeof(sComboBox); nCtrl < nCtrls; nCtrl++)
	{
		if (m_nCtrlIDs[0].GetAt(nCtrl) == nCtrlID) break;
		continue;
	}
	if (nCtrl < nCtrls)
	{
		if ((pCtrl[0] = (CWnd *)m_pCtrls[0].GetAt(nCtrl)))
		{
			if (IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CEdit)) || IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CRichEditCtrl)))
			{
				for (ZeroMemory(&sScrollInfo[0], sizeof(SCROLLINFO)), GetDlgItem(nCtrlID)->GetScrollInfo(SB_HORZ, &sScrollInfo[0]), GetDlgItem(nCtrlID)->GetWindowRect(rCtrl[0]), ScreenToClient(rCtrl[0]); sScrollInfo[0].nPage > 0; )
				{
					rCtrl[0].bottom -= GetSystemMetrics(SM_CYHSCROLL);
					break;
				}
				for (ZeroMemory(&sScrollInfo[1], sizeof(SCROLLINFO)), GetDlgItem(nCtrlID)->GetScrollInfo(SB_VERT, &sScrollInfo[1]); sScrollInfo[1].nPage > 0; )
				{
					rCtrl[0].right -= GetSystemMetrics(SM_CXVSCROLL);
					break;
				}
			}
			pCtrl[0]->ShowWindow((!bAccess  &&  bVisible) ? SW_SHOW : SW_HIDE);
			pCtrl[0]->SetWindowPos((!bAccess  &&  bVisible) ? &wndTop : &wndBottom, (!bAccess  &&  bVisible) ? rCtrl[0].left : 0, (!bAccess  &&  bVisible) ? rCtrl[0].top : 0, (!bAccess  &&  bVisible) ? rCtrl[0].Width() : 0, (!bAccess  &&  bVisible) ? rCtrl[0].Height() : 0, (!bAccess  &&  bVisible) ? (SWP_NOACTIVATE | SWP_SHOWWINDOW) : SWP_NOACTIVATE);
			return TRUE;
		}
		return FALSE;
	}
	if (!bAccess)
	{
		if (!IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CListBox)))
		{
			if (IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CComboBox)))
			{
				if ((GetDlgItem(nCtrlID)->GetStyle() & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST)) == CBS_SIMPLE  &&  bSelections)
				{
					if (SendDlgItemMessage(nCtrlID, CB_GETCOMBOBOXINFO, (WPARAM)NULL, (LPARAM)&sComboBox))
					{
						if ((pCtrl[0] = CWnd::FromHandle(sComboBox.hwndItem)))
						{
							if ((pCtrl[1] = CWnd::FromHandle(sComboBox.hwndList)))
							{
								pCtrl[1]->GetWindowRect(rCtrl[1]);
								pCtrl[1]->GetParent()->ScreenToClient(rCtrl[1]);
								pCtrl[1]->SetWindowPos((CWnd *)NULL, rCtrl[1].left, 0, rCtrl[1].Width(), rCtrl[1].top + rCtrl[1].Height(), SWP_NOACTIVATE | SWP_NOZORDER);
								pCtrl[0]->ShowWindow(SW_HIDE);
								m_nCtrlPositions.Add(rCtrl[1].top);
								m_nCtrlIDs[1].Add(nCtrlID);
								return TRUE;
							}
						}
					}
					return FALSE;
				}
				if (((pCtrl[0] = GetDlgItem(nCtrlID))->GetStyle() & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST)) == CBS_DROPDOWN  &&  bSelections)
				{
					for (; pCtrl[0]->SendMessage(CB_GETDROPPEDCONTROLRECT, (WPARAM)NULL, (LPARAM)&rControl); )
					{
						ScreenToClient(&rControl);
						break;
					}
					if ((pComboBox = new CComboBox))
					{
						if (pComboBox->Create((pCtrl[0]->GetStyle() & ~CBS_DROPDOWN) | CBS_DROPDOWNLIST, rControl, this, nCtrlID))
						{
							pComboBox->SetWindowPos(pCtrl[0], 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
							UpdateControlContents(pCtrl[0], pComboBox);
							pCtrl[0]->SetDlgCtrlID(-(INT)nCtrlID);
							pCtrl[0]->ShowWindow(SW_HIDE);
							pCtrl[0]->EnableWindow(FALSE);
							m_pCtrls[1].Add(pComboBox);
							m_nCtrlIDs[1].Add(nCtrlID);
							m_nCtrlPositions.Add(-1);
							return TRUE;
						}
						delete pComboBox;
					}
					return FALSE;
				}
				for (nCtrl = 0, nCtrls = (m_nCtrlIDs[1].GetSize() == m_nCtrlPositions.GetSize()) ? (INT)m_nCtrlIDs[1].GetSize() : 0; nCtrl < nCtrls; nCtrl++)
				{
					if (m_nCtrlIDs[1].GetAt(nCtrl) == nCtrlID)
					{
						return TRUE;
						break;
					}
				}
			}
			if ((pCtrl[0] = new CWnd))
			{
				if (pCtrl[0]->Create(AfxRegisterWndClass(CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), (LPCTSTR)NULL, (bVisible) ? (WS_CHILD | WS_VISIBLE) : WS_CHILD, CRect(0, 0, 0, 0), this, 0))
				{
					if (IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CEdit)) || IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CRichEditCtrl)))
					{
						for (ZeroMemory(&sScrollInfo[0], sizeof(SCROLLINFO)), GetDlgItem(nCtrlID)->GetScrollInfo(SB_HORZ, &sScrollInfo[0]); sScrollInfo[0].nPage > 0; )
						{
							rCtrl[0].bottom -= GetSystemMetrics(SM_CYHSCROLL);
							break;
						}
						for (ZeroMemory(&sScrollInfo[1], sizeof(SCROLLINFO)), GetDlgItem(nCtrlID)->GetScrollInfo(SB_VERT, &sScrollInfo[1]); sScrollInfo[1].nPage > 0; )
						{
							rCtrl[0].right -= GetSystemMetrics(SM_CXVSCROLL);
							break;
						}
					}
					pCtrl[0]->SetWindowPos((bVisible) ? &wndTop : (CWnd *)NULL, rCtrl[0].left, rCtrl[0].top, rCtrl[0].Width(), rCtrl[0].Height(), (bVisible) ? (SWP_NOACTIVATE | SWP_SHOWWINDOW) : (SWP_NOACTIVATE | SWP_NOZORDER));
					m_nCtrlIDs[0].Add(nCtrlID);
					m_pCtrls[0].Add(pCtrl[0]);
					return TRUE;
				}
				delete pCtrl[0];
			}
			return FALSE;
		}
		return TRUE;
	}
	if (bAccess)
	{
		for (nCtrl = 0, nCtrls = (m_nCtrlIDs[1].GetSize() == m_nCtrlPositions.GetSize()) ? (INT)m_nCtrlIDs[1].GetSize() : 0; nCtrl < nCtrls; nCtrl++)
		{
			if (m_nCtrlIDs[1].GetAt(nCtrl) == nCtrlID) break;
			continue;
		}
		if (nCtrl < nCtrls)
		{
			if ((GetDlgItem(nCtrlID)->GetStyle() & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST)) == CBS_SIMPLE)
			{
				if (SendDlgItemMessage(nCtrlID, CB_GETCOMBOBOXINFO, (WPARAM)NULL, (LPARAM)&sComboBox))
				{
					if ((pCtrl[0] = CWnd::FromHandle(sComboBox.hwndItem)))
					{
						if ((pCtrl[1] = CWnd::FromHandle(sComboBox.hwndList)))
						{
							pCtrl[1]->GetWindowRect(rCtrl[1]);
							pCtrl[1]->GetParent()->ScreenToClient(rCtrl[1]);
							pCtrl[1]->SetWindowPos((CWnd *)NULL, rCtrl[1].left, m_nCtrlPositions.GetAt(nCtrl), rCtrl[1].Width(), rCtrl[1].Height() - m_nCtrlPositions.GetAt(nCtrl), SWP_NOACTIVATE | SWP_NOZORDER);
							pCtrl[0]->ShowWindow(SW_SHOW);
							return TRUE;
						}
					}
				}
				return FALSE;
			}
			if (((pCtrl[0] = GetDlgItem(nCtrlID))->GetStyle() & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST)) == CBS_DROPDOWNLIST)
			{
				if ((pComboBox = (CComboBox *)GetDlgItem(-(INT)nCtrlID)))
				{
					UpdateControlContents(pCtrl[0], pComboBox);
					pCtrl[0]->SetDlgCtrlID(-(INT)nCtrlID);
					pCtrl[0]->ShowWindow(SW_HIDE);
					pCtrl[0]->EnableWindow(FALSE);
					pComboBox->SetDlgCtrlID(nCtrlID);
					pComboBox->ShowWindow(SW_SHOW);
					pComboBox->EnableWindow();
					return TRUE;
				}
				return FALSE;
			}
		}
	}
	return TRUE;
}

HGLOBAL CLocaleDialog::LoadLocaleDialogTemplate(UINT nDialogID) CONST
{
	return LoadLocaleDialogTemplate(MAKEINTRESOURCE(nDialogID));
}
HGLOBAL CLocaleDialog::LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST
{
	HMODULE  hModule;
	HRSRC  hDialogTemplate;

	return(((hDialogTemplate = FindResourceEx((hModule = GetModuleHandle((LPCTSTR)NULL)), RT_DIALOG, pszDialogName, GetLanguageID())) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hDialogTemplate) : (LPVOID)NULL);
}

BOOL CLocaleDialog::SetChildSheet(CMFCPropertySheet *pSheet, CWnd *pItem)
{
	if (IsChild(pSheet))
	{
		pSheet->SetWindowPos(pItem, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
		m_hChildSheet = pSheet->GetSafeHwnd();
		return TRUE;
	}
	return FALSE;
}

CMFCPropertySheet *CLocaleDialog::GetChildSheet() CONST
{
	return((CMFCPropertySheet *)CWnd::FromHandle(m_hChildSheet));
}

BOOL CLocaleDialog::IsControlOfType(CWnd *pCtrl, CRuntimeClass *pClass) CONST
{
	TCHAR  szClassName[2][256];

	if (!pCtrl->IsKindOf(pClass))
	{
		if (GetClassName(pCtrl->GetSafeHwnd(), szClassName[0], sizeof(szClassName[0]) / sizeof(TCHAR)))
		{
#ifndef UNICODE
			return((CString(pClass->m_lpszClassName).Find(szClassName[0]) == 1) ? TRUE : FALSE);
#else
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClassName[1], sizeof(szClassName[0]) / sizeof(TCHAR));
			return((CString(szClassName[1]).Find(szClassName[0]) == 1) ? TRUE : FALSE);
#endif
		}
		return FALSE;
	}
	return TRUE;
}

VOID CLocaleDialog::UpdateControlContents(CWnd *pCtrl, CComboBox *pComboBox)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CString  szItem;

	for (nItem = 0, nItems = (INT)pCtrl->SendMessage(CB_GETCOUNT), nIndex = (INT)pCtrl->SendMessage(CB_GETCURSEL), pComboBox->SetFont(GetFont()), pComboBox->ResetContent(); nItem < nItems; nItem++)
	{
		szItem = Combobox_GetText(pCtrl, nItem);
		pComboBox->InsertString(-1, szItem);
	}
	pComboBox->SetCurSel(nIndex);
}

LRESULT CLocaleDialog::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl[2];
	INT  nCtrls[2];
	CRect  rCtrl[2];
	CWnd  *pCtrl[4];
	SCROLLINFO  sScrollInfo[2];

	if (message == WM_COMMAND)
	{
		if (HIWORD(wParam) == BN_SETFOCUS || HIWORD(wParam) == EN_SETFOCUS || HIWORD(wParam) == CBN_SETFOCUS || HIWORD(wParam) == SBXN_SETFOCUS || HIWORD(wParam) == TSBXN_SETFOCUS)
		{
			for (nCtrl[0] = 0, nCtrls[0] = ((pCtrl[0] = CWnd::FromHandle((HWND)lParam)) && m_pCtrls[0].GetSize() == m_nCtrlIDs[0].GetSize()) ? (INT)m_nCtrlIDs[0].GetSize() : 0; nCtrl[0] < nCtrls[0]; nCtrl[0]++)
			{
				if (GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0])) == pCtrl[0] || GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0]))->IsChild(pCtrl[0]))
				{
					if ((pCtrl[1] = (CWnd *)m_pCtrls[0].GetAt(nCtrl[0])))
					{
						pCtrl[1]->GetClientRect(rCtrl[0]);
						if (!rCtrl[0].IsRectEmpty())
						{
							for (pCtrl[2] = GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0])); IsWindow(pCtrl[2]->GetSafeHwnd()); pCtrl[2] = pCtrl[3])
							{
								if ((pCtrl[3] = GetNextDlgTabItem(pCtrl[2], (HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE)))
								{
									for (nCtrl[1] = 0, nCtrls[1] = nCtrls[0]; nCtrl[1] < nCtrls[1]; nCtrl[1]++)
									{
										if (pCtrl[3]->GetDlgCtrlID() == (INT)m_nCtrlIDs[0].GetAt(nCtrl[1])) break;
										continue;
									}
									if (nCtrl[1] == nCtrls[1])
									{
										pCtrl[3]->SetFocus();
										break;
									}
								}
								if (!IsWindow(pCtrl[3]->GetSafeHwnd()) || pCtrl[3]->GetDlgCtrlID() == (INT)m_nCtrlIDs[0].GetAt(nCtrl[0])) break;
							}
							return 0;
						}
					}
					break;
				}
			}
			if (!IsWindow(m_hCtrlWnd))
			{
				if ((pCtrl[0] = (HIWORD(wParam) == EN_SETFOCUS || HIWORD(wParam) == SBXN_SETFOCUS || HIWORD(wParam) == TSBXN_SETFOCUS) ? FromHandle((HWND)lParam) : (CWnd *)NULL))
				{
					if (!pCtrl[0]->IsKindOf(RUNTIME_CLASS(CRichEditCtrl)))
					{
						pCtrl[0]->SendMessage(EM_SETSEL, 0, -1);
						m_hCtrlWnd = pCtrl[0]->GetSafeHwnd();
					}
				}
				if ((pCtrl[0] = (HIWORD(wParam) == CBN_SETFOCUS) ? FromHandle((HWND)lParam) : (CWnd *)NULL))
				{
					pCtrl[0]->SendMessage(CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
					m_hCtrlWnd = pCtrl[0]->GetSafeHwnd();
				}
			}
			else
			{
				for (; (pCtrl[0] = (HIWORD(wParam) == EN_KILLFOCUS || HIWORD(wParam) == SBXN_KILLFOCUS || HIWORD(wParam) == TSBXN_KILLFOCUS) ? FromHandle((HWND)lParam) : (CWnd *)NULL); )
				{
					m_hCtrlWnd = (pCtrl[0]->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) ? m_hCtrlWnd : (HWND)NULL;
					break;
				}
				for (; HIWORD(wParam) == CBN_KILLFOCUS; )
				{
					m_hCtrlWnd = (HWND)NULL;
					break;
				}
			}
		}
		if (HIWORD(wParam) == EN_CHANGE)
		{
			for (nCtrl[0] = 0, nCtrls[0] = ((pCtrl[0] = CWnd::FromHandle((HWND)lParam)) && m_pCtrls[0].GetSize() == m_nCtrlIDs[0].GetSize()) ? (INT)m_nCtrlIDs[0].GetSize() : 0; nCtrl[0] < nCtrls[0]; nCtrl[0]++)
			{
				if (GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0])) == pCtrl[0] || GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0]))->IsChild(pCtrl[0]))
				{
					for (ZeroMemory(&sScrollInfo[0], sizeof(SCROLLINFO)), pCtrl[0]->GetScrollInfo(SB_HORZ, &sScrollInfo[0]), pCtrl[0]->GetWindowRect(rCtrl[0]), ScreenToClient(rCtrl[0]); sScrollInfo[0].nPage > 0; )
					{
						rCtrl[0].bottom -= GetSystemMetrics(SM_CYHSCROLL);
						break;
					}
					for (ZeroMemory(&sScrollInfo[1], sizeof(SCROLLINFO)), pCtrl[0]->GetScrollInfo(SB_VERT, &sScrollInfo[1]); sScrollInfo[1].nPage > 0; )
					{
						rCtrl[0].right -= GetSystemMetrics(SM_CXVSCROLL);
						break;
					}
					if ((pCtrl[1] = (CWnd *)m_pCtrls[0].GetAt(nCtrl[0])))
					{
						for (pCtrl[1]->GetWindowRect(rCtrl[1]); !rCtrl[1].IsRectEmpty(); )
						{
							pCtrl[1]->SetWindowPos(&wndTop, rCtrl[0].left, rCtrl[0].top, rCtrl[0].Width(), rCtrl[0].Height(), SWP_NOACTIVATE | SWP_SHOWWINDOW);
							break;
						}
					}
					break;
				}
			}
		}
		for (; HIWORD(wParam) == EN_UPDATE || HIWORD(wParam) == EN_CHANGE; )
		{
			if ((pCtrl[0] = CWnd::FromHandle((HWND)lParam)) && !pCtrl[0]->IsKindOf(RUNTIME_CLASS(CRichEditCtrl)) && !IsWindow(m_hCtrlWnd)) return 0;
			break;
		}
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}

BOOL CLocaleDialog::IsModified() CONST
{
	return FALSE;
}

BOOL CLocaleDialog::Check(BOOL bModified) CONST
{
	return((bModified) ? IsModified() : TRUE);
}

void CLocaleDialog::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocaleDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CLocaleDialog::PostNcDestroy()
{
	INT  nCtrl;
	INT  nCtrls;
	CWnd  *pCtrl;

	for (nCtrl = 0, nCtrls = (INT)m_pCtrls[0].GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pCtrl = (CWnd *)m_pCtrls[0].GetAt(nCtrl)))
		{
			delete pCtrl;
			continue;
		}
	}
	for (nCtrl = 0, nCtrls = (INT)m_pCtrls[1].GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pCtrl = (CWnd *)m_pCtrls[1].GetAt(nCtrl)))
		{
			delete pCtrl;
			continue;
		}
	}
	m_pCtrls[0].RemoveAll();
	m_pCtrls[1].RemoveAll();
	m_nCtrlIDs[0].RemoveAll();
	m_nCtrlIDs[1].RemoveAll();
	m_nCtrlPositions.RemoveAll();
	CDialogEx::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CLocaleDialog, CDialogEx)
	//{{AFX_MSG_MAP(CLocaleDialog)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocaleDialog message handlers

int CLocaleDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDialogEx::OnCreate(lpCreateStruct) != -1 && Initialize()) ? 0 : -1);
}

void CLocaleDialog::OnActivate(UINT nState, CWnd *pWndOther, BOOL bMinimized)
{
	CWnd  *pChildWnd;

	if (IsWindow(m_hChildSheet) && nState == WA_INACTIVE)
	{
		m_hChildWnd = (IsChild((pChildWnd = GetFocus()))) ? pChildWnd->GetSafeHwnd() : (HWND)NULL;
		return;
	}
	if (IsWindow(m_hChildSheet) && nState != WA_INACTIVE)
	{
		for (Default(); IsWindow(m_hChildWnd) == TRUE; )
		{
			CWnd::FromHandle(m_hChildWnd)->SetFocus();
			break;
		}
		return;
	}
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
}


/////////////////////////////////////////////////////////////////////////////
// CLocalePropertySheetDialog dialog

IMPLEMENT_DYNCREATE(CLocalePropertySheetDialog, CMFCPropertySheet)

CLocalePropertySheetDialog::CLocalePropertySheetDialog() : CMFCPropertySheet()
{
	m_pParentWnd = (CWnd *)NULL;
}
CLocalePropertySheetDialog::CLocalePropertySheetDialog(LPCTSTR pszTitle, CWnd *pParentWnd) : CMFCPropertySheet(pszTitle, pParentWnd)
{
	m_pParentWnd = pParentWnd;
}

BOOL CLocalePropertySheetDialog::Create(CWnd *pParentWnd, DWORD dwStyle, DWORD dwExStyle)
{
	return CMFCPropertySheet::Create((m_pParentWnd = (IsWindow(pParentWnd->GetSafeHwnd())) ? pParentWnd : m_pParentWnd), dwStyle, dwExStyle);
}

BOOL CLocalePropertySheetDialog::Initialize()
{
	return TRUE;
}

CWnd *CLocalePropertySheetDialog::GetParent() CONST
{
	return m_pParentWnd;
}

VOID CLocalePropertySheetDialog::RepositionButtons()
{
	CRect  rDialog;
	CRect  rButton[3];

	for (GetWindowRect(rDialog), GetDlgItem(IDOK)->GetWindowRect(rButton[0]), GetDlgItem(IDCANCEL)->GetWindowRect(rButton[1]), GetDlgItem(IDHELP)->GetWindowRect(rButton[2]), ScreenToClient(rButton[0]), ScreenToClient(rButton[1]), ScreenToClient(rButton[2]), GetDlgItem(IDOK)->SetDlgCtrlID(-IDOK), GetDlgItem(IDCANCEL)->SetDlgCtrlID(-IDCANCEL), GetDlgItem(ID_APPLY_NOW)->DestroyWindow(); m_wndButton[0].Create(STRING(IDS_DIALOG_IDOK), (GetStyle() & WS_POPUP) ? (BS_DEFPUSHBUTTON | WS_CHILD | WS_DISABLED | WS_TABSTOP | WS_VISIBLE) : (BS_DEFPUSHBUTTON | WS_CHILD | WS_DISABLED | WS_TABSTOP), CRect(rDialog.Width() / 10, rButton[0].top, rDialog.Width() / 10 + rDialog.Width() / 5, rButton[0].top + rButton[0].Height()), this, IDOK) && m_wndButton[1].Create(STRING(IDS_DIALOG_IDCANCEL), (GetStyle() & WS_POPUP) ? (WS_CHILD | WS_TABSTOP | WS_VISIBLE) : (WS_CHILD | WS_TABSTOP), CRect(rDialog.Width() / 2 - rDialog.Width() / 10, rButton[1].top, rDialog.Width() / 2 - rDialog.Width() / 10 + rDialog.Width() / 5, rButton[1].top + rButton[1].Height()), this, IDCANCEL) && m_wndButton[2].Create(STRING(IDS_DIALOG_IDHELP), (GetStyle() & WS_POPUP) ? (WS_CHILD | WS_TABSTOP | WS_VISIBLE) : (WS_CHILD | WS_TABSTOP), CRect((9 * rDialog.Width()) / 10 - rDialog.Width() / 5, rButton[2].top, (9 * rDialog.Width()) / 10, rButton[2].top + rButton[2].Height()), this, IDHELP); )
	{
		GetDlgItem(-IDOK)->DestroyWindow();
		GetDlgItem(-IDCANCEL)->DestroyWindow();
		return;
	}
	for (; IsWindow(m_wndButton[0].GetSafeHwnd()); )
	{
		m_wndButton[0].DestroyWindow();
		break;
	}
	for (GetDlgItem(-IDOK)->SetDlgCtrlID(IDOK); IsWindow(m_wndButton[1].GetSafeHwnd()); )
	{
		m_wndButton[1].DestroyWindow();
		break;
	}
	for (GetDlgItem(-IDCANCEL)->SetDlgCtrlID(IDCANCEL); IsWindow(m_wndButton[2].GetSafeHwnd()); )
	{
		m_wndButton[2].DestroyWindow();
		break;
	}
}

BOOL CLocalePropertySheetDialog::IsModified() CONST
{
	CWnd  *pWnd;
	CLocalePropertyPage  *pPage;

	for (pWnd = GetWindow(GW_CHILD); IsWindow(pWnd->GetSafeHwnd()); pWnd = pWnd->GetWindow(GW_CHILD))
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CLocalePropertyPage))) break;
		continue;
	}
	for (; IsWindow(pWnd->GetSafeHwnd()); pWnd = pWnd->GetNextWindow())
	{
		if ((pPage = (pWnd->IsKindOf(RUNTIME_CLASS(CLocalePropertyPage))) ? (CLocalePropertyPage *)pWnd : (CLocalePropertyPage *)NULL))
		{
			if (pPage->IsModified(FALSE)) return TRUE;
			continue;
		}
	}
	return FALSE;
}

BOOL CLocalePropertySheetDialog::Check(BOOL bModified) CONST
{
	CWnd  *pWnd;
	CLocalePropertyPage  *pPage;

	for (pWnd = GetWindow(GW_CHILD); IsWindow(pWnd->GetSafeHwnd()); pWnd = pWnd->GetWindow(GW_CHILD))
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CLocalePropertyPage))) break;
		continue;
	}
	for (; IsWindow(pWnd->GetSafeHwnd()); pWnd = pWnd->GetNextWindow())
	{
		if ((pPage = (pWnd->IsKindOf(RUNTIME_CLASS(CLocalePropertyPage))) ? (CLocalePropertyPage *)pWnd : (CLocalePropertyPage *)NULL))
		{
			if (!pPage->Check(FALSE)) return FALSE;
			continue;
		}
	}
	return((bModified) ? IsModified() : TRUE);
}

BEGIN_MESSAGE_MAP(CLocalePropertySheetDialog, CMFCPropertySheet)
	//{{AFX_MSG_MAP(CLocalePropertySheetDialog)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalePropertySheetDialog message handlers

int CLocalePropertySheetDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CMFCPropertySheet::OnCreate(lpCreateStruct) != -1 && Initialize()) ? 0 : -1);
}

BOOL CLocalePropertySheetDialog::OnInitDialog()
{
	CMFCPropertySheet::OnInitDialog();
	RepositionButtons();
	return TRUE;
}

void CLocalePropertySheetDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE)
	{
		OnCancel();
		return;
	}
	CMFCPropertySheet::OnSysCommand(nID, lParam);
}

void CLocalePropertySheetDialog::OnOK()
{
	CHourglassCursor  cCursor;

	EndDialog(IDOK);
}

void CLocalePropertySheetDialog::OnCancel()
{
	CWnd  *pWnd;
	CHourglassCursor  cCursor;

	if ((pWnd = GetParent()))
	{
		while (IsWindow(pWnd->GetSafeHwnd()) && pWnd->IsKindOf(RUNTIME_CLASS(CMFCPropertyPage)))
		{
			pWnd = pWnd->GetParent();
			continue;
		}
		if (pWnd->IsKindOf(RUNTIME_CLASS(CMFCPropertySheet)) || pWnd->IsKindOf(RUNTIME_CLASS(CDialogEx)))
		{
			pWnd->SendMessage(WM_SYSCOMMAND, SC_CLOSE);
			return;
		}
	}
	EndDialog(IDCANCEL);
}

void CLocalePropertySheetDialog::OnDestroy()
{
	if (IsWindow(m_wndButton[0].GetSafeHwnd())) m_wndButton[0].DestroyWindow();
	if (IsWindow(m_wndButton[1].GetSafeHwnd())) m_wndButton[1].DestroyWindow();
	if (IsWindow(m_wndButton[2].GetSafeHwnd())) m_wndButton[2].DestroyWindow();
	if (m_psh.ppsp != (LPCPROPSHEETPAGE)NULL) free((void *)m_psh.ppsp);
	m_psh.ppsp = (LPCPROPSHEETPAGE)NULL;
	CMFCPropertySheet::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CLocalePropertyPage dialog

IMPLEMENT_DYNCREATE(CLocalePropertyPage, CMFCPropertyPage)

CLocalePropertyPage::CLocalePropertyPage() : CMFCPropertyPage()
{
	m_nCaptionID = 0;
	m_hCtrlWnd = (HWND)NULL;
	m_hChildWnd = (HWND)NULL;
	m_hChildSheet = (HWND)NULL;
}
CLocalePropertyPage::CLocalePropertyPage(UINT nTemplateID, UINT nCaptionID) : CMFCPropertyPage()
{
	m_nCaptionID = 0;
	m_hCtrlWnd = (HWND)NULL;
	m_hChildWnd = (HWND)NULL;
	m_hChildSheet = (HWND)NULL;
	Construct(nTemplateID, nCaptionID);
}
CLocalePropertyPage::CLocalePropertyPage(LPCTSTR pszTemplateName, UINT nCaptionID) : CMFCPropertyPage()
{
	m_nCaptionID = 0;
	m_hCtrlWnd = (HWND)NULL;
	m_hChildWnd = (HWND)NULL;
	m_hChildSheet = (HWND)NULL;
	Construct(pszTemplateName, nCaptionID);
}

BOOL CLocalePropertyPage::Initialize()
{
	return TRUE;
}

void CLocalePropertyPage::Construct(UINT nTemplateID, UINT nCaptionID)
{
	Construct(MAKEINTRESOURCE(nTemplateID), nCaptionID);
}
void CLocalePropertyPage::Construct(LPCTSTR pszTemplateName, UINT nCaptionID)
{
	for (m_psp.pResource = (LPCDLGTEMPLATE)LoadLocalePropertyPageTemplate(pszTemplateName), m_psp.dwFlags |= PSP_DLGINDIRECT; m_nCaptionID != 0 || nCaptionID != 0; )
	{
		m_psp.pszTitle = STRING((m_nCaptionID = (nCaptionID != 0) ? nCaptionID : m_nCaptionID));
		m_psp.dwFlags |= PSP_USETITLE;
		break;
	}
}

CWnd *CLocalePropertyPage::GetDlgItem(UINT nCtrlID) CONST
{
	CWnd  *pWnd;
	CWnd  *pCtrl[2];

	for (pWnd = (nCtrlID == IDOK || nCtrlID == ID_APPLY_NOW || nCtrlID == IDCANCEL || nCtrlID == IDHELP) ? GetParent() : (CWnd *)NULL, pCtrl[0] = (CWnd *)NULL; IsWindow(pWnd->GetSafeHwnd()); pWnd = pWnd->GetParent())
	{
		if ((pCtrl[1] = pWnd->GetDlgItem(nCtrlID)) != (CWnd *)NULL)
		{
			if (pCtrl[1]->IsWindowVisible()) return pCtrl[1];
			pCtrl[0] = pCtrl[1];
		}
	}
	return((nCtrlID != IDOK  &&  nCtrlID != ID_APPLY_NOW  &&  nCtrlID != IDCANCEL  &&  nCtrlID != IDHELP) ? CMFCPropertyPage::GetDlgItem(nCtrlID) : pCtrl[0]);
}

CLocalePropertySheetDialog *CLocalePropertyPage::GetParent() CONST
{
	return((CLocalePropertySheetDialog *)m_pParentWnd);
}

BOOL CLocalePropertyPage::AccessControl(UINT nCtrlID, BOOL bAccess, BOOL bVisible, BOOL bSelections)
{
	INT  nCtrl;
	INT  nCtrls;
	RECT  rControl;
	CWnd  *pCtrl[2];
	CRect  rCtrl[2];
	CComboBox  *pComboBox;
	SCROLLINFO  sScrollInfo[2];
	COMBOBOXINFO  sComboBox;

	for (nCtrl = 0, nCtrls = (INT)m_nCtrlIDs[0].GetSize(), GetDlgItem(nCtrlID)->ShowWindow((bVisible) ? SW_SHOW : SW_HIDE), GetDlgItem(nCtrlID)->GetWindowRect(rCtrl[0]), ScreenToClient(rCtrl[0]), sComboBox.cbSize = sizeof(sComboBox); nCtrl < nCtrls; nCtrl++)
	{
		if (m_nCtrlIDs[0].GetAt(nCtrl) == nCtrlID) break;
		continue;
	}
	if (nCtrl < nCtrls)
	{
		if ((pCtrl[0] = (CWnd *)m_pCtrls[0].GetAt(nCtrl)))
		{
			if (IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CEdit)) || IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CRichEditCtrl)))
			{
				for (ZeroMemory(&sScrollInfo[0], sizeof(SCROLLINFO)), GetDlgItem(nCtrlID)->GetScrollInfo(SB_HORZ, &sScrollInfo[0]), GetDlgItem(nCtrlID)->GetWindowRect(rCtrl[0]), ScreenToClient(rCtrl[0]); sScrollInfo[0].nPage > 0; )
				{
					rCtrl[0].bottom -= GetSystemMetrics(SM_CYHSCROLL);
					break;
				}
				for (ZeroMemory(&sScrollInfo[1], sizeof(SCROLLINFO)), GetDlgItem(nCtrlID)->GetScrollInfo(SB_VERT, &sScrollInfo[1]); sScrollInfo[1].nPage > 0; )
				{
					rCtrl[0].right -= GetSystemMetrics(SM_CXVSCROLL);
					break;
				}
			}
			pCtrl[0]->ShowWindow((!bAccess  &&  bVisible) ? SW_SHOW : SW_HIDE);
			pCtrl[0]->SetWindowPos((!bAccess  &&  bVisible) ? &wndTop : &wndBottom, (!bAccess  &&  bVisible) ? rCtrl[0].left : 0, (!bAccess  &&  bVisible) ? rCtrl[0].top : 0, (!bAccess  &&  bVisible) ? rCtrl[0].Width() : 0, (!bAccess  &&  bVisible) ? rCtrl[0].Height() : 0, (!bAccess  &&  bVisible) ? (SWP_NOACTIVATE | SWP_SHOWWINDOW) : SWP_NOACTIVATE);
			return TRUE;
		}
		return FALSE;
	}
	if (!bAccess)
	{
		if (!IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CListBox)))
		{
			if (IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CComboBox)))
			{
				if ((GetDlgItem(nCtrlID)->GetStyle() & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST)) == CBS_SIMPLE  &&  bSelections)
				{
					if (SendDlgItemMessage(nCtrlID, CB_GETCOMBOBOXINFO, (WPARAM)NULL, (LPARAM)&sComboBox))
					{
						if ((pCtrl[0] = CWnd::FromHandle(sComboBox.hwndItem)))
						{
							if ((pCtrl[1] = CWnd::FromHandle(sComboBox.hwndList)))
							{
								pCtrl[1]->GetWindowRect(rCtrl[1]);
								pCtrl[1]->GetParent()->ScreenToClient(rCtrl[1]);
								pCtrl[1]->SetWindowPos((CWnd *)NULL, rCtrl[1].left, 0, rCtrl[1].Width(), rCtrl[1].top + rCtrl[1].Height(), SWP_NOACTIVATE | SWP_NOZORDER);
								pCtrl[0]->ShowWindow(SW_HIDE);
								m_nCtrlPositions.Add(rCtrl[1].top);
								m_nCtrlIDs[1].Add(nCtrlID);
								return TRUE;
							}
						}
					}
					return FALSE;
				}
				if (((pCtrl[0] = GetDlgItem(nCtrlID))->GetStyle() & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST)) == CBS_DROPDOWN  &&  bSelections)
				{
					for (; pCtrl[0]->SendMessage(CB_GETDROPPEDCONTROLRECT, (WPARAM)NULL, (LPARAM)&rControl); )
					{
						ScreenToClient(&rControl);
						break;
					}
					if ((pComboBox = new CComboBox))
					{
						if (pComboBox->Create((pCtrl[0]->GetStyle() & ~CBS_DROPDOWN) | CBS_DROPDOWNLIST, rControl, this, nCtrlID))
						{
							pComboBox->SetWindowPos(pCtrl[0], 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
							UpdateControlContents(pCtrl[0], pComboBox);
							pCtrl[0]->SetDlgCtrlID(-(INT)nCtrlID);
							pCtrl[0]->ShowWindow(SW_HIDE);
							pCtrl[0]->EnableWindow(FALSE);
							m_pCtrls[1].Add(pComboBox);
							m_nCtrlIDs[1].Add(nCtrlID);
							m_nCtrlPositions.Add(-1);
							return TRUE;
						}
						delete pComboBox;
					}
					return FALSE;
				}
				for (nCtrl = 0, nCtrls = (m_nCtrlIDs[1].GetSize() == m_nCtrlPositions.GetSize()) ? (INT)m_nCtrlIDs[1].GetSize() : 0; nCtrl < nCtrls; nCtrl++)
				{
					if (m_nCtrlIDs[1].GetAt(nCtrl) == nCtrlID)
					{
						return TRUE;
						break;
					}
				}
			}
			if ((pCtrl[0] = new CWnd))
			{
				if (pCtrl[0]->Create(AfxRegisterWndClass(CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW)), (LPCTSTR)NULL, (bVisible) ? (WS_CHILD | WS_VISIBLE) : WS_CHILD, CRect(0, 0, 0, 0), this, 0))
				{
					if (IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CEdit)) || IsControlOfType(GetDlgItem(nCtrlID), RUNTIME_CLASS(CRichEditCtrl)))
					{
						for (ZeroMemory(&sScrollInfo[0], sizeof(SCROLLINFO)), GetDlgItem(nCtrlID)->GetScrollInfo(SB_HORZ, &sScrollInfo[0]); sScrollInfo[0].nPage > 0; )
						{
							rCtrl[0].bottom -= GetSystemMetrics(SM_CYHSCROLL);
							break;
						}
						for (ZeroMemory(&sScrollInfo[1], sizeof(SCROLLINFO)), GetDlgItem(nCtrlID)->GetScrollInfo(SB_VERT, &sScrollInfo[1]); sScrollInfo[1].nPage > 0; )
						{
							rCtrl[0].right -= GetSystemMetrics(SM_CXVSCROLL);
							break;
						}
					}
					pCtrl[0]->SetWindowPos((bVisible) ? &wndTop : (CWnd *)NULL, rCtrl[0].left, rCtrl[0].top, rCtrl[0].Width(), rCtrl[0].Height(), (bVisible) ? (SWP_NOACTIVATE | SWP_SHOWWINDOW) : (SWP_NOACTIVATE | SWP_NOZORDER));
					m_nCtrlIDs[0].Add(nCtrlID);
					m_pCtrls[0].Add(pCtrl[0]);
					return TRUE;
				}
				delete pCtrl[0];
			}
			return FALSE;
		}
		return TRUE;
	}
	if (bAccess)
	{
		for (nCtrl = 0, nCtrls = (m_nCtrlIDs[1].GetSize() == m_nCtrlPositions.GetSize()) ? (INT)m_nCtrlIDs[1].GetSize() : 0; nCtrl < nCtrls; nCtrl++)
		{
			if (m_nCtrlIDs[1].GetAt(nCtrl) == nCtrlID) break;
			continue;
		}
		if (nCtrl < nCtrls)
		{
			if ((GetDlgItem(nCtrlID)->GetStyle() & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST)) == CBS_SIMPLE)
			{
				if (SendDlgItemMessage(nCtrlID, CB_GETCOMBOBOXINFO, (WPARAM)NULL, (LPARAM)&sComboBox))
				{
					if ((pCtrl[0] = CWnd::FromHandle(sComboBox.hwndItem)))
					{
						if ((pCtrl[1] = CWnd::FromHandle(sComboBox.hwndList)))
						{
							pCtrl[1]->GetWindowRect(rCtrl[1]);
							pCtrl[1]->GetParent()->ScreenToClient(rCtrl[1]);
							pCtrl[1]->SetWindowPos((CWnd *)NULL, rCtrl[1].left, m_nCtrlPositions.GetAt(nCtrl), rCtrl[1].Width(), rCtrl[1].Height() - m_nCtrlPositions.GetAt(nCtrl), SWP_NOACTIVATE | SWP_NOZORDER);
							pCtrl[0]->ShowWindow(SW_SHOW);
							return TRUE;
						}
					}
				}
				return FALSE;
			}
			if (((pCtrl[0] = GetDlgItem(nCtrlID))->GetStyle() & (CBS_SIMPLE | CBS_DROPDOWN | CBS_DROPDOWNLIST)) == CBS_DROPDOWNLIST)
			{
				if ((pComboBox = (CComboBox *)GetDlgItem(-(INT)nCtrlID)))
				{
					UpdateControlContents(pCtrl[0], pComboBox);
					pCtrl[0]->SetDlgCtrlID(-(INT)nCtrlID);
					pCtrl[0]->ShowWindow(SW_HIDE);
					pCtrl[0]->EnableWindow(FALSE);
					pComboBox->SetDlgCtrlID(nCtrlID);
					pComboBox->ShowWindow(SW_SHOW);
					pComboBox->EnableWindow();
					return TRUE;
				}
				return FALSE;
			}
		}
	}
	return TRUE;
}

HGLOBAL CLocalePropertyPage::LoadLocalePropertyPageTemplate(UINT nPropertyPageID) CONST
{
	return LoadLocalePropertyPageTemplate(MAKEINTRESOURCE(nPropertyPageID));
}
HGLOBAL CLocalePropertyPage::LoadLocalePropertyPageTemplate(LPCTSTR pszPropertyPageName) CONST
{
	HMODULE  hModule;
	HRSRC  hPropertyPageTemplate;

	return(((hPropertyPageTemplate = FindResourceEx((hModule = GetModuleHandle((LPCTSTR)NULL)), RT_DIALOG, pszPropertyPageName, GetLanguageID())) || (hPropertyPageTemplate = FindResourceEx(hModule, RT_DIALOG, pszPropertyPageName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hPropertyPageTemplate = FindResourceEx(hModule, RT_DIALOG, pszPropertyPageName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hPropertyPageTemplate) : (LPVOID)NULL);
}

BOOL CLocalePropertyPage::SetChildSheet(CMFCPropertySheet *pSheet, CWnd *pItem)
{
	if (IsChild(pSheet))
	{
		pSheet->SetWindowPos(pItem, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
		m_hChildSheet = pSheet->GetSafeHwnd();
		return TRUE;
	}
	return FALSE;
}

CMFCPropertySheet *CLocalePropertyPage::GetChildSheet() CONST
{
	return((CMFCPropertySheet *)CWnd::FromHandle(m_hChildSheet));
}

BOOL CLocalePropertyPage::IsControlOfType(CWnd *pCtrl, CRuntimeClass *pClass) CONST
{
	TCHAR  szClassName[2][256];

	if (!pCtrl->IsKindOf(pClass))
	{
		if (GetClassName(pCtrl->GetSafeHwnd(), szClassName[0], sizeof(szClassName[0]) / sizeof(TCHAR)))
		{
#ifndef UNICODE
			return((CString(pClass->m_lpszClassName).Find(szClassName[0]) == 1) ? TRUE : FALSE);
#else
			MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, pClass->m_lpszClassName, -1, szClassName[1], sizeof(szClassName[0]) / sizeof(TCHAR));
			return((CString(szClassName[1]).Find(szClassName[0]) == 1) ? TRUE : FALSE);
#endif
		}
		return FALSE;
	}
	return TRUE;
}

VOID CLocalePropertyPage::UpdateControlContents(CWnd *pCtrl, CComboBox *pComboBox)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CString  szItem;

	for (nItem = 0, nItems = (INT)pCtrl->SendMessage(CB_GETCOUNT), nIndex = (INT)pCtrl->SendMessage(CB_GETCURSEL), pComboBox->SetFont(GetFont()), pComboBox->ResetContent(); nItem < nItems; nItem++)
	{
		szItem = Combobox_GetText(pCtrl, nItem);
		pComboBox->InsertString(-1, szItem);
	}
	pComboBox->SetCurSel(nIndex);
}

BOOL CLocalePropertyPage::PreTranslateMessage(MSG *pMsg)
{
	CWnd  *pWnd;
	BOOL  bPrevious;

	if (IsWindow(pMsg->hwnd))
	{
		if (IsChild(FromHandle(pMsg->hwnd)))
		{
			if (pMsg->message == WM_KEYDOWN)
			{
				if (pMsg->wParam == VK_TAB)
				{
					if ((pWnd = GetParent()->GetParent()) && pWnd->IsKindOf(RUNTIME_CLASS(CDialogEx)))
					{
						for (bPrevious = (HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE; (!bPrevious && GetNextDlgTabItem(GetFocus())->GetSafeHwnd() == GetNextDlgTabItem((CWnd *)NULL)->GetSafeHwnd()) || (bPrevious && GetFocus()->GetSafeHwnd() == GetNextDlgTabItem((CWnd *)NULL)->GetSafeHwnd()); )
						{
							GetParent()->SetFocus();
							return TRUE;
						}
					}
				}
			}
		}
	}
	return CMFCPropertyPage::PreTranslateMessage(pMsg);
}

LRESULT CLocalePropertyPage::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	INT  nCtrl[2];
	INT  nCtrls[2];
	CRect  rCtrl[2];
	CWnd  *pCtrl[4];
	SCROLLINFO  sScrollInfo[2];

	if (message == WM_COMMAND)
	{
		if (HIWORD(wParam) == BN_SETFOCUS || HIWORD(wParam) == EN_SETFOCUS || HIWORD(wParam) == CBN_SETFOCUS || HIWORD(wParam) == SBXN_SETFOCUS || HIWORD(wParam) == TSBXN_SETFOCUS)
		{
			for (nCtrl[0] = 0, nCtrls[0] = ((pCtrl[0] = CWnd::FromHandle((HWND)lParam)) && m_pCtrls[0].GetSize() == m_nCtrlIDs[0].GetSize()) ? (INT)m_nCtrlIDs[0].GetSize() : 0; nCtrl[0] < nCtrls[0]; nCtrl[0]++)
			{
				if (GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0])) == pCtrl[0] || GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0]))->IsChild(pCtrl[0]))
				{
					if ((pCtrl[1] = (CWnd *)m_pCtrls[0].GetAt(nCtrl[0])))
					{
						pCtrl[1]->GetClientRect(rCtrl[0]);
						if (!rCtrl[0].IsRectEmpty())
						{
							if (!HIBYTE(GetKeyState(VK_SHIFT)))
							{
								if ((pCtrl[2] = GetNextDlgTabItem(GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0])))) == GetNextDlgTabItem(GetWindow(GW_CHILD)))
								{
									GetParent()->GetNextDlgTabItem(this)->SetFocus();
									return 0;
								}
							}
							for (pCtrl[2] = GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0])); IsWindow(pCtrl[2]->GetSafeHwnd()); pCtrl[2] = pCtrl[3])
							{
								if ((pCtrl[3] = GetNextDlgTabItem(pCtrl[2], (HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE)))
								{
									for (nCtrl[1] = 0, nCtrls[1] = nCtrls[0]; nCtrl[1] < nCtrls[1]; nCtrl[1]++)
									{
										if (pCtrl[3]->GetDlgCtrlID() == (INT)m_nCtrlIDs[0].GetAt(nCtrl[1])) break;
										continue;
									}
									if (nCtrl[1] == nCtrls[1])
									{
										pCtrl[3]->SetFocus();
										break;
									}
								}
								if (!IsWindow(pCtrl[3]->GetSafeHwnd()) || pCtrl[3]->GetDlgCtrlID() == (INT)m_nCtrlIDs[0].GetAt(nCtrl[0]))
								{
									pCtrl[2] = (CWnd *)NULL;
									break;
								}
							}
							for (; !IsWindow(pCtrl[2]->GetSafeHwnd()); )
							{
								GetParent()->GetNextDlgTabItem(this, (HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE)->SetFocus();
								break;
							}
							return 0;
						}
					}
					break;
				}
			}
			if (!IsWindow(m_hCtrlWnd))
			{
				if ((pCtrl[0] = (HIWORD(wParam) == EN_SETFOCUS || HIWORD(wParam) == SBXN_SETFOCUS || HIWORD(wParam) == TSBXN_SETFOCUS) ? FromHandle((HWND)lParam) : (CWnd *)NULL))
				{
					if (!pCtrl[0]->IsKindOf(RUNTIME_CLASS(CRichEditCtrl)))
					{
						pCtrl[0]->SendMessage(EM_SETSEL, 0, -1);
						m_hCtrlWnd = pCtrl[0]->GetSafeHwnd();
					}
				}
				if ((pCtrl[0] = (HIWORD(wParam) == CBN_SETFOCUS) ? FromHandle((HWND)lParam) : (CWnd *)NULL))
				{
					pCtrl[0]->SendMessage(CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
					m_hCtrlWnd = pCtrl[0]->GetSafeHwnd();
				}
			}
			else
			{
				for (; (pCtrl[0] = (HIWORD(wParam) == EN_KILLFOCUS || HIWORD(wParam) == SBXN_KILLFOCUS || HIWORD(wParam) == TSBXN_KILLFOCUS) ? FromHandle((HWND)lParam) : (CWnd *)NULL); )
				{
					m_hCtrlWnd = (pCtrl[0]->IsKindOf(RUNTIME_CLASS(CRichEditCtrl))) ? m_hCtrlWnd : (HWND)NULL;
					break;
				}
				for (; HIWORD(wParam) == CBN_KILLFOCUS; )
				{
					m_hCtrlWnd = (HWND)NULL;
					break;
				}
			}
		}
		if (HIWORD(wParam) == EN_CHANGE)
		{
			for (nCtrl[0] = 0, nCtrls[0] = ((pCtrl[0] = CWnd::FromHandle((HWND)lParam)) && m_pCtrls[0].GetSize() == m_nCtrlIDs[0].GetSize()) ? (INT)m_nCtrlIDs[0].GetSize() : 0; nCtrl[0] < nCtrls[0]; nCtrl[0]++)
			{
				if (GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0])) == pCtrl[0] || GetDlgItem(m_nCtrlIDs[0].GetAt(nCtrl[0]))->IsChild(pCtrl[0]))
				{
					for (ZeroMemory(&sScrollInfo[0], sizeof(SCROLLINFO)), pCtrl[0]->GetScrollInfo(SB_HORZ, &sScrollInfo[0]), pCtrl[0]->GetWindowRect(rCtrl[0]), ScreenToClient(rCtrl[0]); sScrollInfo[0].nPage > 0; )
					{
						rCtrl[0].bottom -= GetSystemMetrics(SM_CYHSCROLL);
						break;
					}
					for (ZeroMemory(&sScrollInfo[1], sizeof(SCROLLINFO)), pCtrl[0]->GetScrollInfo(SB_VERT, &sScrollInfo[1]); sScrollInfo[1].nPage > 0; )
					{
						rCtrl[0].right -= GetSystemMetrics(SM_CXVSCROLL);
						break;
					}
					if ((pCtrl[1] = (CWnd *)m_pCtrls[0].GetAt(nCtrl[0])))
					{
						for (pCtrl[1]->GetWindowRect(rCtrl[1]); !rCtrl[1].IsRectEmpty(); )
						{
							pCtrl[1]->SetWindowPos(&wndTop, rCtrl[0].left, rCtrl[0].top, rCtrl[0].Width(), rCtrl[0].Height(), SWP_NOACTIVATE | SWP_SHOWWINDOW);
							break;
						}
					}
					break;
				}
			}
		}
		for (; HIWORD(wParam) == EN_UPDATE || HIWORD(wParam) == EN_CHANGE; )
		{
			if ((pCtrl[0] = CWnd::FromHandle((HWND)lParam)) && !pCtrl[0]->IsKindOf(RUNTIME_CLASS(CRichEditCtrl)) && !IsWindow(m_hCtrlWnd)) return 0;
			break;
		}
	}
	return CMFCPropertyPage::WindowProc(message, wParam, lParam);
}

BOOL CLocalePropertyPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->IsModified() : FALSE);
}

BOOL CLocalePropertyPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->Check() : TRUE);
}

void CLocalePropertyPage::DoDataExchange(CDataExchange *pDX)
{
	CMFCPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLocalePropertyPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CLocalePropertyPage::PostNcDestroy()
{
	INT  nCtrl;
	INT  nCtrls;
	CWnd  *pCtrl;

	for (nCtrl = 0, nCtrls = (INT)m_pCtrls[0].GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pCtrl = (CWnd *)m_pCtrls[0].GetAt(nCtrl)))
		{
			delete pCtrl;
			continue;
		}
	}
	for (nCtrl = 0, nCtrls = (INT)m_pCtrls[1].GetSize(); nCtrl < nCtrls; nCtrl++)
	{
		if ((pCtrl = (CWnd *)m_pCtrls[1].GetAt(nCtrl)))
		{
			delete pCtrl;
			continue;
		}
	}
	m_pCtrls[0].RemoveAll();
	m_pCtrls[1].RemoveAll();
	m_nCtrlIDs[0].RemoveAll();
	m_nCtrlIDs[1].RemoveAll();
	m_nCtrlPositions.RemoveAll();
	CMFCPropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CLocalePropertyPage, CMFCPropertyPage)
	//{{AFX_MSG_MAP(CLocalePropertyPage)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalePropertyPage message handlers

int CLocalePropertyPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCPropertyPage::OnCreate(lpCreateStruct) != -1)
	{
		m_pParentWnd = CMFCPropertyPage::GetParent();
		return((Initialize()) ? 0 : -1);
	}
	return -1;
}

void CLocalePropertyPage::OnActivate(UINT nState, CWnd *pWndOther, BOOL bMinimized)
{
	CWnd  *pChildWnd;

	if (IsWindow(m_hChildSheet) && nState == WA_INACTIVE)
	{
		m_hChildWnd = (IsChild((pChildWnd = GetFocus()))) ? pChildWnd->GetSafeHwnd() : (HWND)NULL;
		return;
	}
	if (IsWindow(m_hChildSheet) && nState != WA_INACTIVE)
	{
		for (Default(); IsWindow(m_hChildWnd) == TRUE; )
		{
			CWnd::FromHandle(m_hChildWnd)->SetFocus();
			break;
		}
		return;
	}
	CMFCPropertyPage::OnActivate(nState, pWndOther, bMinimized);
}


/////////////////////////////////////////////////////////////////////////////
// CLocaleMenu

BOOL CLocaleMenu::LoadMenu(UINT nMenuID)
{
	return LoadMenu(MAKEINTRESOURCE(nMenuID));
}
BOOL CLocaleMenu::LoadMenu(LPCTSTR pszMenuName)
{
	return Attach(LoadLocaleMenu(pszMenuName));
}

HMENU CLocaleMenu::LoadLocaleMenu(LPCTSTR pszMenuName) CONST
{
	HRSRC  hTemplate;
	HMODULE  hModule;
	HGLOBAL  hMenuTemplateMemory;
	LPWSTR  pszMenuTemplate;

	return(((pszMenuTemplate = ((hMenuTemplateMemory = ((hTemplate = FindResourceEx((hModule = GetModuleHandle((LPCTSTR)NULL)), RT_MENU, pszMenuName, GetLanguageID())) || (hTemplate = FindResourceEx(hModule, RT_MENU, pszMenuName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hTemplate = FindResourceEx(hModule, RT_MENU, pszMenuName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hTemplate) : (HGLOBAL)NULL)) ? (LPWSTR)LockResource(hMenuTemplateMemory) : (LPWSTR)NULL)) ? ::LoadMenuIndirect((CONST MENUTEMPLATE *) pszMenuTemplate) : (HMENU)NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CLocaleFrameWnd

IMPLEMENT_DYNCREATE(CLocaleFrameWnd, CFrameWndEx)

CLocaleFrameWnd::CLocaleFrameWnd() : CFrameWndEx()
{
	m_nUITimerID = 0;
}

BOOL CLocaleFrameWnd::LoadFrame(UINT nResourceID, DWORD dwDefaultStyle, CWnd *pParentWnd, CCreateContext *pContext)
{
	if (CFrameWndEx::LoadFrame(nResourceID, dwDefaultStyle, pParentWnd, pContext))
	{
		SetWindowText(GetAppTitle());
		LoadAccelTable(nResourceID);
		return TRUE;
	}
	return FALSE;
}

BOOL CLocaleFrameWnd::LoadAccelTable(UINT nAccelID)
{
	return((!m_hAccelTable || DestroyAcceleratorTable(m_hAccelTable)) ? ((m_hAccelTable = LoadLocaleAccelTable(MAKEINTRESOURCE(nAccelID))) ? TRUE : FALSE) : FALSE);
}
BOOL CLocaleFrameWnd::LoadAccelTable(LPCTSTR pszAccelName)
{
	return((!m_hAccelTable || DestroyAcceleratorTable(m_hAccelTable)) ? ((m_hAccelTable = LoadLocaleAccelTable(pszAccelName)) ? TRUE : FALSE) : FALSE);
}

HACCEL CLocaleFrameWnd::LoadLocaleAccelTable(LPCTSTR pszAccelName) CONST
{
	INT  nIndex;
	INT  nCount;
	DWORD  cbEntry;
	DWORD  cbTemplate;
	HRSRC  hTemplate;
	LPSTR  pszTemplate;
	HACCEL  hAccelTable;
	LPACCEL  pAccelTable;
	HGLOBAL  hTemplateMemory;
	HMODULE  hModule;

	if ((hTemplate = FindResourceEx((hModule = GetModuleHandle((LPCTSTR)NULL)), RT_ACCELERATOR, pszAccelName, GetLanguageID())) || (hTemplate = FindResourceEx(hModule, RT_ACCELERATOR, pszAccelName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hTemplate = FindResourceEx(hModule, RT_ACCELERATOR, pszAccelName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))))
	{
		if ((cbTemplate = SizeofResource(hModule, hTemplate)) > 0)
		{
			if ((hTemplateMemory = LoadResource(hModule, hTemplate)))
			{
				if ((pszTemplate = (LPSTR)LockResource(hTemplateMemory)))
				{
					for (cbEntry = sizeof(ACCEL), nCount = (INT)(cbTemplate / cbEntry); !pszTemplate[cbEntry] && cbEntry < cbTemplate; )
					{
						nCount = (INT)(cbTemplate / (cbEntry + 1));
						cbEntry++;
					}
					if ((pAccelTable = (LPACCEL)GlobalAlloc(GPTR, nCount*cbEntry)))
					{
						for (nIndex = 0; nIndex < nCount; nIndex = nIndex + 1)
						{
							CopyMemory(&pAccelTable[nIndex], &pszTemplate[nIndex*cbEntry], cbEntry);
							continue;
						}
						if ((hAccelTable = CreateAcceleratorTable(pAccelTable, nCount)))
						{
							GlobalFree(pAccelTable);
							return hAccelTable;
						}
						GlobalFree(pAccelTable);
					}
				}
			}
		}
	}
	return((HACCEL)NULL);
}

VOID CLocaleFrameWnd::DoUpdateUI()
{
	m_nUITimerID = SetTimer((UINT_PTR)-1, 0, NULL);
}

BOOL CLocaleFrameWnd::CanUpdateUI() CONST
{
	return TRUE;
}

BEGIN_MESSAGE_MAP(CLocaleFrameWnd, CFrameWndEx)
	//{{AFX_MSG_MAP(CLocaleFrameWnd)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocaleFrameWnd message handlers

void CLocaleFrameWnd::OnTimer(UINT_PTR nEventID)
{
	if (nEventID == (UINT)-1)
	{
		if (CanUpdateUI())
		{
			PostMessage(WM_IDLEUPDATECMDUI, TRUE);
			KillTimer(m_nUITimerID);
			m_nUITimerID = 0;
		}
		return;
	}
	CFrameWndEx::OnTimer(nEventID);
}

void CLocaleFrameWnd::OnDestroy()
{
	if (m_nUITimerID != 0)
	{
		KillTimer(m_nUITimerID);
		m_nUITimerID = 0;
	}
	CFrameWndEx::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CLocaleMDIFrameWnd

IMPLEMENT_DYNCREATE(CLocaleMDIFrameWnd, CMDIFrameWndEx)

CLocaleMDIFrameWnd::CLocaleMDIFrameWnd() : CMDIFrameWndEx()
{
	m_nUITimerID = 0;
}

BOOL CLocaleMDIFrameWnd::LoadFrame(UINT nResourceID, DWORD dwDefaultStyle, CWnd *pParentWnd, CCreateContext *pContext)
{
	if (CMDIFrameWndEx::LoadFrame(nResourceID, dwDefaultStyle, pParentWnd, pContext))
	{
		SetWindowText(GetAppTitle());
		LoadAccelTable(nResourceID);
		return TRUE;
	}
	return FALSE;
}

BOOL CLocaleMDIFrameWnd::LoadAccelTable(UINT nAccelID)
{
	return((!m_hAccelTable || DestroyAcceleratorTable(m_hAccelTable)) ? ((m_hAccelTable = LoadLocaleAccelTable(MAKEINTRESOURCE(nAccelID))) ? TRUE : FALSE) : FALSE);
}
BOOL CLocaleMDIFrameWnd::LoadAccelTable(LPCTSTR pszAccelName)
{
	return((!m_hAccelTable || DestroyAcceleratorTable(m_hAccelTable)) ? ((m_hAccelTable = LoadLocaleAccelTable(pszAccelName)) ? TRUE : FALSE) : FALSE);
}

HACCEL CLocaleMDIFrameWnd::LoadLocaleAccelTable(LPCTSTR pszAccelName) CONST
{
	INT  nIndex;
	INT  nCount;
	DWORD  cbEntry;
	DWORD  cbTemplate;
	HRSRC  hTemplate;
	LPSTR  pszTemplate;
	HACCEL  hAccelTable;
	LPACCEL  pAccelTable;
	HGLOBAL  hTemplateMemory;
	HMODULE  hModule;

	if ((hTemplate = FindResourceEx((hModule = GetModuleHandle((LPCTSTR)NULL)), RT_ACCELERATOR, pszAccelName, GetLanguageID())) || (hTemplate = FindResourceEx(hModule, RT_ACCELERATOR, pszAccelName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hTemplate = FindResourceEx(hModule, RT_ACCELERATOR, pszAccelName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))))
	{
		if ((cbTemplate = SizeofResource(hModule, hTemplate)) > 0)
		{
			if ((hTemplateMemory = LoadResource(hModule, hTemplate)))
			{
				if ((pszTemplate = (LPSTR)LockResource(hTemplateMemory)))
				{
					for (cbEntry = sizeof(ACCEL), nCount = (INT)(cbTemplate / cbEntry); !pszTemplate[cbEntry] && cbEntry < cbTemplate; )
					{
						nCount = (INT)(cbTemplate / (cbEntry + 1));
						cbEntry++;
					}
					if ((pAccelTable = (LPACCEL)GlobalAlloc(GPTR, nCount*cbEntry)))
					{
						for (nIndex = 0; nIndex < nCount; nIndex = nIndex + 1)
						{
							CopyMemory(&pAccelTable[nIndex], &pszTemplate[nIndex*cbEntry], cbEntry);
							continue;
						}
						if ((hAccelTable = CreateAcceleratorTable(pAccelTable, nCount)))
						{
							GlobalFree(pAccelTable);
							return hAccelTable;
						}
						GlobalFree(pAccelTable);
					}
				}
			}
		}
	}
	return((HACCEL)NULL);
}

VOID CLocaleMDIFrameWnd::DoUpdateUI()
{
	m_nUITimerID = SetTimer((UINT_PTR)-1, 0, NULL);
}

BOOL CLocaleMDIFrameWnd::CanUpdateUI() CONST
{
	return TRUE;
}

BEGIN_MESSAGE_MAP(CLocaleMDIFrameWnd, CMDIFrameWndEx)
	//{{AFX_MSG_MAP(CLocaleMDIFrameWnd)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocaleMDIFrameWnd message handlers

void CLocaleMDIFrameWnd::OnTimer(UINT_PTR nEventID)
{
	if (nEventID == (UINT)-1)
	{
		if (CanUpdateUI())
		{
			PostMessage(WM_IDLEUPDATECMDUI, TRUE);
			KillTimer(m_nUITimerID);
			m_nUITimerID = 0;
		}
		return;
	}
	CMDIFrameWndEx::OnTimer(nEventID);
}

void CLocaleMDIFrameWnd::OnDestroy()
{
	if (m_nUITimerID != 0)
	{
		KillTimer(m_nUITimerID);
		m_nUITimerID = 0;
	}
	CMDIFrameWndEx::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CLocaleMDIChildWnd

IMPLEMENT_DYNCREATE(CLocaleMDIChildWnd, CMDIChildWndEx)

BOOL CLocaleMDIChildWnd::LoadFrame(LPCTSTR pszTitle, UINT nResourceID, DWORD dwDefaultStyle, CWnd *pParentWnd, CCreateContext *pContext)
{
	if (CMDIChildWndEx::LoadFrame(nResourceID, dwDefaultStyle, pParentWnd, pContext))
	{
		LoadAccelTable(nResourceID);
		SetWindowText(pszTitle);
		return TRUE;
	}
	return FALSE;
}

BOOL CLocaleMDIChildWnd::LoadAccelTable(UINT nAccelID)
{
	return((!m_hAccelTable || DestroyAcceleratorTable(m_hAccelTable)) ? ((m_hAccelTable = LoadLocaleAccelTable(MAKEINTRESOURCE(nAccelID))) ? TRUE : FALSE) : FALSE);
}
BOOL CLocaleMDIChildWnd::LoadAccelTable(LPCTSTR pszAccelName)
{
	return((!m_hAccelTable || DestroyAcceleratorTable(m_hAccelTable)) ? ((m_hAccelTable = LoadLocaleAccelTable(pszAccelName)) ? TRUE : FALSE) : FALSE);
}

HACCEL CLocaleMDIChildWnd::LoadLocaleAccelTable(LPCTSTR pszAccelName) CONST
{
	INT  nIndex;
	INT  nCount;
	DWORD  cbEntry;
	DWORD  cbTemplate;
	HRSRC  hTemplate;
	LPSTR  pszTemplate;
	HACCEL  hAccelTable;
	LPACCEL  pAccelTable;
	HGLOBAL  hTemplateMemory;
	HMODULE  hModule;

	if ((hTemplate = FindResourceEx((hModule = GetModuleHandle((LPCTSTR)NULL)), RT_ACCELERATOR, pszAccelName, GetLanguageID())) || (hTemplate = FindResourceEx(hModule, RT_ACCELERATOR, pszAccelName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hTemplate = FindResourceEx(hModule, RT_ACCELERATOR, pszAccelName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))))
	{
		if ((cbTemplate = SizeofResource(hModule, hTemplate)) > 0)
		{
			if ((hTemplateMemory = LoadResource(hModule, hTemplate)))
			{
				if ((pszTemplate = (LPSTR)LockResource(hTemplateMemory)))
				{
					for (cbEntry = sizeof(ACCEL), nCount = (INT)(cbTemplate / cbEntry); !pszTemplate[cbEntry] && cbEntry < cbTemplate; )
					{
						nCount = (INT)(cbTemplate / (cbEntry + 1));
						cbEntry++;
					}
					if ((pAccelTable = (LPACCEL)GlobalAlloc(GPTR, nCount*cbEntry)))
					{
						for (nIndex = 0; nIndex < nCount; nIndex = nIndex + 1)
						{
							CopyMemory(&pAccelTable[nIndex], &pszTemplate[nIndex*cbEntry], cbEntry);
							continue;
						}
						if ((hAccelTable = CreateAcceleratorTable(pAccelTable, nCount)))
						{
							GlobalFree(pAccelTable);
							return hAccelTable;
						}
						GlobalFree(pAccelTable);
					}
				}
			}
		}
	}
	return((HACCEL)NULL);
}

BEGIN_MESSAGE_MAP(CLocaleMDIChildWnd, CMDIChildWndEx)
	//{{AFX_MSG_MAP(CLocaleMDIChildWnd)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocaleMDIChildWnd message handlers


/////////////////////////////////////////////////////////////////////////////
// CLocaleApp

IMPLEMENT_DYNAMIC(CLocaleApp, CWinAppEx)

CLocaleApp::CLocaleApp() : CWinAppEx()
{
	m_pStringTable = (LPTSTR *)NULL;
	m_pStringIDTable = (LPINT)NULL;
	m_nAppStringCount = m_nStringCount = 0;
	m_nAppStringOffset = m_nStringOffset = 0;
	m_nLanguageID = (LANGID)0;
}

BOOL CLocaleApp::InitInstance()
{
	if (CWinAppEx::InitInstance() && LoadStrings())
	{
		SetAppID(GetAppRegID());
		SetRegistryKey(GetAppRegKey());
		return TRUE;
	}
	return FALSE;
}

int CLocaleApp::ExitInstance()
{
	FreeStrings();
	return CWinAppEx::ExitInstance();
}

CString CLocaleApp::GetAppTitle() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryApplicationTitle();
}

CString CLocaleApp::GetAppRegID() CONST
{
	CString  szID;
	CVersionInfo  cVersionInfo;

	szID.Format(STRING(IDS_REG_APPID), (LPCTSTR)cVersionInfo.QueryCompanyName(), (LPCTSTR)cVersionInfo.QueryFileDescription());
	return szID;
}

CString CLocaleApp::GetAppRegKey() CONST
{
	CString  szKey;
	CVersionInfo  cVersionInfo;

	szKey.Format(STRING(IDS_REG_APPKEY), (LPCTSTR)cVersionInfo.QueryCompanyName());
	return szKey;
}

LANGID CLocaleApp::GetLanguageID() CONST
{
	return m_nLanguageID;
}

BOOL CLocaleApp::GetPrinterDeviceDefaults(PRINTDLG *pPrinterInfo)
{
	DEVMODE  *pDevMode[2];
	DEVNAMES  *pDevNames[2];
	PRINTDLG  sPrinterInfo;

	for (sPrinterInfo.lStructSize = sizeof(PRINTDLG); CWinAppEx::GetPrinterDeviceDefaults(&sPrinterInfo); )
	{
		if ((pPrinterInfo->hDevNames = GlobalAlloc(GHND, GlobalSize(sPrinterInfo.hDevNames))))
		{
			if ((pPrinterInfo->hDevMode = GlobalAlloc(GHND, GlobalSize(sPrinterInfo.hDevMode))))
			{
				if ((pDevNames[0] = (DEVNAMES *)GlobalLock(pPrinterInfo->hDevNames)))
				{
					if ((pDevMode[0] = (DEVMODE *)GlobalLock(pPrinterInfo->hDevMode)))
					{
						if ((pDevNames[1] = (DEVNAMES *)GlobalLock(sPrinterInfo.hDevNames)))
						{
							if ((pDevMode[1] = (DEVMODE *)GlobalLock(sPrinterInfo.hDevMode)))
							{
								CopyMemory(pDevNames[0], pDevNames[1], GlobalSize(sPrinterInfo.hDevNames));
								CopyMemory(pDevMode[0], pDevMode[1], GlobalSize(sPrinterInfo.hDevMode));
								GlobalUnlock(pPrinterInfo->hDevNames);
								GlobalUnlock(sPrinterInfo.hDevNames);
								GlobalUnlock(pPrinterInfo->hDevMode);
								GlobalUnlock(sPrinterInfo.hDevMode);
								return TRUE;
							}
							GlobalUnlock(sPrinterInfo.hDevNames);
						}
						GlobalUnlock(pPrinterInfo->hDevMode);
					}
					GlobalUnlock(pPrinterInfo->hDevNames);
				}
				GlobalFree(pPrinterInfo->hDevMode);
				pPrinterInfo->hDevMode = (HGLOBAL)NULL;
			}
			GlobalFree(pPrinterInfo->hDevNames);
			pPrinterInfo->hDevNames = (HGLOBAL)NULL;
		}
		break;
	}
	return FALSE;
}

CString CLocaleApp::GetHelpFileName() CONST
{
	return m_szHelpFileName;
}

LPCTSTR CLocaleApp::GetLibraryModuleName() CONST
{
	return GetLibraryName();
}

HINSTANCE CLocaleApp::GetLibraryModuleInstance() CONST
{
	return GetLibraryInstance();
}

LPCTSTR CLocaleApp::String(INT nID) CONST
{
	INT  nIndex;

	return(((nIndex = SearchString(nID)) != -1) ? m_pStringTable[nIndex] : EMPTYSTRING);
}

TCHAR CLocaleApp::StringChar(INT nID) CONST
{
	return String(nID)[0];
}

INT CLocaleApp::GetStringOffset(BOOL bLibrary) CONST
{
	return((!bLibrary) ? m_nAppStringOffset : m_nStringOffset);
}

BOOL CLocaleApp::LoadStrings()
{
	INT  nPos;
	INT  cbLanguage;
	LPTSTR  pszLanguage;
	LPTSTR  pszFileName;
	CString  szFileName;
	CString  szFileExtension;
	CString  szHelpFileName;
	TCHAR  szPathName[MAX_PATH];
	HINSTANCE  hLibrary;

	if ((m_nLanguageID = GetUserDefaultLangID()))
	{
		if ((hLibrary = AfxLoadLibrary(GetLibraryModuleName())))
		{
			if ((EnumResourceNames(hLibrary, RT_STRING, (ENUMRESNAMEPROC)EnumStrings, (LONG_PTR) this) || GetLastError() == ERROR_RESOURCE_TYPE_NOT_FOUND) && (EnumResourceNames(GetModuleHandle((LPCTSTR)NULL), RT_STRING, (ENUMRESNAMEPROC)EnumStrings, (LONG_PTR) this) || GetLastError() == ERROR_RESOURCE_TYPE_NOT_FOUND))
			{
				if ((cbLanguage = GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_SABBREVLANGNAME, (LPTSTR)NULL, 0)))
				{
					if ((pszLanguage = (LPTSTR)GlobalAlloc(GPTR, cbLanguage*sizeof(TCHAR))) != (LPTSTR)NULL)
					{
						if (GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_SABBREVLANGNAME, pszLanguage, cbLanguage))
						{
							for (szFileExtension.Format(STRING(IDS_ONLINEHELP_FILENAME), EMPTYSTRING); GetModuleFileName((HMODULE)NULL, szPathName, sizeof(szPathName) / sizeof(TCHAR)) > 0; )
							{
								for (m_szHelpFileName = szFileName.Left(((nPos = (szFileName = szPathName).ReverseFind(szFileExtension[0])) < 0) ? szFileName.GetLength() : nPos) + szFileExtension; m_pszHelpFilePath != (LPCTSTR)NULL; )
								{
									free((void *)m_pszHelpFilePath);
									break;
								}
								for (m_pszHelpFilePath = (LPCTSTR)NULL; (pszFileName = (LPTSTR)malloc((m_szHelpFileName.GetLength() + 1)*sizeof(TCHAR))); )
								{
									_tcscpy_s(pszFileName, m_szHelpFileName.GetLength() + 1, m_szHelpFileName);
									m_pszHelpFilePath = pszFileName;
									break;
								}
								break;
							}
							_tsetlocale(LC_ALL, pszLanguage);
							AfxFreeLibrary(hLibrary);
							GlobalFree(pszLanguage);
							return TRUE;
						}
						GlobalFree(pszLanguage);
					}
				}
			}
			AfxFreeLibrary(hLibrary);
			FreeStrings();
		}
	}
	return FALSE;
}

VOID CLocaleApp::FreeStrings()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = m_nAppStringCount + m_nStringCount; nIndex < nCount; nIndex++)
	{
		GlobalFree(m_pStringTable[nIndex]);
		continue;
	}
	if (nCount > 0)
	{
		GlobalFree(m_pStringTable);
		GlobalFree(m_pStringIDTable);
	}
	free((void *)m_pszHelpFilePath);
	m_pStringTable = (LPTSTR *)NULL;
	m_pStringIDTable = (LPINT)NULL;
	m_pszHelpFilePath = (LPCTSTR)NULL;
	m_nAppStringCount = m_nStringCount = 0;
}

INT CLocaleApp::SearchString(INT nID) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;
	INT  nStringID;

	if ((nMaxIndex = m_nAppStringCount + m_nStringCount) > 0)
	{
		if (nID >= 0 && (nID >= nMaxIndex || nID != m_pStringIDTable[nID]))
		{
			for (nMinIndex = 0, nMaxIndex = nMaxIndex - 1, nIndex = nMaxIndex / 2; nMaxIndex > nMinIndex; nIndex = (nMaxIndex + nMinIndex) / 2)
			{
				if ((nStringID = m_pStringIDTable[nIndex]) == nID) break;
				if (nStringID < nID)
				{
					nMinIndex = nIndex + 1;
					continue;
				}
				nMaxIndex = nIndex;
			}
			return((nID == m_pStringIDTable[nIndex]) ? nIndex : -1);
		}
		return((nID >= 0) ? nID : -1);
	}
	return -1;
}

INT CLocaleApp::GetLocaleData(UINT nDataID, LPVOID pData, INT cbMax) CONST
{
	return GetLocaleData(MAKEINTRESOURCE(nDataID), pData, cbMax);
}
INT CLocaleApp::GetLocaleData(LPCTSTR pszDataName, LPVOID pData, INT cbMax) CONST
{
	HMODULE  hModule;
	INT  cbDataTemplate;
	HRSRC  hDataTemplate;
	LPVOID  pDataTemplate;
	HGLOBAL  hDataTemplateMemory;

	if ((hDataTemplate = FindResourceEx((hModule = GetModuleHandle((LPCTSTR)NULL)), RT_RCDATA, pszDataName, m_nLanguageID)) || (hDataTemplate = FindResourceEx(hModule, RT_RCDATA, pszDataName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hDataTemplate = FindResourceEx(hModule, RT_RCDATA, pszDataName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))))
	{
		if ((cbDataTemplate = SizeofResource(hModule, hDataTemplate)) <= cbMax  &&  AfxIsValidAddress(pData, cbMax))
		{
			if ((hDataTemplateMemory = LoadResource(hModule, hDataTemplate)))
			{
				if ((pDataTemplate = LockResource(hDataTemplateMemory)))
				{
					CopyMemory(pData, pDataTemplate, cbDataTemplate);
					return cbDataTemplate;
				}
			}
			return 0;
		}
		return((!cbMax) ? cbDataTemplate : 0);
	}
	return 0;
}

BOOL CALLBACK CLocaleApp::EnumStrings(HINSTANCE hModule, LPCTSTR pszType, LPTSTR pszName, CLocaleApp *pLocaleApp)
{
	return EnumResourceLanguages(hModule, pszType, pszName, (ENUMRESLANGPROC)EnumLocaleStrings, (LONG_PTR)pLocaleApp);
}

BOOL CALLBACK CLocaleApp::EnumLocaleStrings(HINSTANCE hModule, LPCTSTR pszType, LPCTSTR pszName, WORD wLanguageID, CLocaleApp *pLocaleApp)
{
	INT  cPos;
	INT  cbStrings;
	INT  nStringID;
	INT  nStringLength;
	BOOL  bStringLibrary;
	HRSRC  hStringBlock;
	DWORD  cbStringBlock;
	LPINT  pStringIDTable;
	LPTSTR  *pStringTable;
	LPWSTR  pszStringBlock;
	LPTSTR  pszBlockExtraction;
	HGLOBAL  hStringBlockMemory;

	if ((hStringBlock = FindResourceEx(hModule, pszType, pszName, pLocaleApp->m_nLanguageID)) || (hStringBlock = FindResourceEx(hModule, pszType, pszName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hStringBlock = FindResourceEx(hModule, pszType, pszName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US))))
	{
		if ((cbStringBlock = SizeofResource(hModule, hStringBlock)))
		{
			if ((hStringBlockMemory = LoadResource(hModule, hStringBlock)))
			{
				if ((pszStringBlock = (LPWSTR)LockResource(hStringBlockMemory)))
				{
					for (cPos = 0, cbStrings = 0, nStringID = (INT)(16 * ((INT_PTR)pszName - 1)), bStringLibrary = (hModule == GetLibraryInstance()) ? TRUE : FALSE; cbStrings < (INT)cbStringBlock; cPos += nStringLength + 1, cbStrings = cPos*sizeof(WCHAR), nStringID++)
					{
						if ((!bStringLibrary  &&  !pLocaleApp->m_nAppStringCount) || (bStringLibrary  &&  !pLocaleApp->m_nStringCount))
						{
							if (!bStringLibrary) pLocaleApp->m_nAppStringOffset = pLocaleApp->m_nStringCount - nStringID;
							else  pLocaleApp->m_nStringOffset = -nStringID;
						}
						if ((nStringLength = (INT)pszStringBlock[cPos]))
						{
							if ((pStringTable = (!pLocaleApp->m_pStringTable) ? (LPTSTR *)GlobalAlloc(GPTR, sizeof(LPTSTR)) : (LPTSTR *)GlobalReAlloc(pLocaleApp->m_pStringTable, (pLocaleApp->m_nAppStringCount + pLocaleApp->m_nStringCount + 1)*sizeof(LPTSTR), GMEM_MOVEABLE | GMEM_ZEROINIT)))
							{
								if ((pStringIDTable = (!pLocaleApp->m_pStringIDTable) ? (LPINT)GlobalAlloc(GPTR, sizeof(INT)) : (LPINT)GlobalReAlloc(pLocaleApp->m_pStringIDTable, (pLocaleApp->m_nAppStringCount + pLocaleApp->m_nStringCount + 1)*sizeof(INT), GMEM_MOVEABLE | GMEM_ZEROINIT)))
								{
									if ((pszBlockExtraction = (LPTSTR)GlobalAlloc(GPTR, (nStringLength + 1)*sizeof(TCHAR))))
									{
#ifndef UNICODE
										if (!WideCharToMultiByte(CP_ACP, (DWORD)NULL, &pszStringBlock[cPos + 1], nStringLength, pszBlockExtraction, nStringLength + 1, (LPSTR)NULL, (LPBOOL)NULL))
										{
											pLocaleApp->m_pStringIDTable = pStringIDTable;
											pLocaleApp->m_pStringTable = pStringTable;
											GlobalFree(pszBlockExtraction);
											break;
										}
#else
										wcsncpy_s(pszBlockExtraction, nStringLength + 1, &pszStringBlock[cPos + 1], nStringLength);
#endif
										pLocaleApp->m_pStringTable = pStringTable;
										pLocaleApp->m_pStringIDTable = pStringIDTable;
										pLocaleApp->m_pStringTable[pLocaleApp->m_nAppStringCount + pLocaleApp->m_nStringCount] = pszBlockExtraction;
										pLocaleApp->m_pStringIDTable[pLocaleApp->m_nAppStringCount + pLocaleApp->m_nStringCount] = ((!bStringLibrary) ? pLocaleApp->m_nAppStringOffset : 0) + nStringID;
										if (!bStringLibrary) pLocaleApp->m_nAppStringCount++;
										else  pLocaleApp->m_nStringCount++;
										continue;
									}
									pLocaleApp->m_pStringIDTable = pStringIDTable;
								}
								pLocaleApp->m_pStringTable = pStringTable;
							}
							break;
						}
					}
					return((cbStrings >= (INT)cbStringBlock) ? TRUE : FALSE);
				}
			}
		}
	}
	return FALSE;
}

BOOL CLocaleApp::IsIdleMessage(MSG *pMsg)
{
	return((CWinAppEx::IsIdleMessage(pMsg) && pMsg->message != WM_TIMER) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CLocaleApp, CWinAppEx)
	//{{AFX_MSG_MAP(CLocaleApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocaleApp message handlers
