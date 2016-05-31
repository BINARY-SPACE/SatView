// MIMICSPPG.CPP : Mimics Control Dialog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics control
// dialog related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Mimics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



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

BOOL CLocalePropertySheetDialog::Attach(HWND hDlg)
{
	if (SubclassWindow(hDlg))
	{
		RepositionButtons();
		return Initialize();
	}
	return FALSE;
}

HWND CLocalePropertySheetDialog::Detach()
{
	return CMFCPropertySheet::Detach();
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
	ON_WM_SYSCOMMAND()
	ON_WM_HELPINFO()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, OnOK)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	ON_BN_CLICKED(IDHELP, OnHelp)
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
	CWnd  *pWnd;
	CLocalePropertyPage  *pPage;
	CHourglassCursor  cCursor;

	for (pWnd = GetWindow(GW_CHILD); IsWindow(pWnd->GetSafeHwnd()); pWnd = pWnd->GetWindow(GW_CHILD))
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CLocalePropertyPage))) break;
		continue;
	}
	for (; IsWindow(pWnd->GetSafeHwnd()); pWnd = pWnd->GetNextWindow())
	{
		if ((pPage = (pWnd->IsKindOf(RUNTIME_CLASS(CLocalePropertyPage))) ? (CLocalePropertyPage *)pWnd : (CLocalePropertyPage *)NULL))
		{
			pPage->Update();
			continue;
		}
	}
	EndDialog(IDOK);
}

void CLocalePropertySheetDialog::OnCancel()
{
	CWnd  *pWnd;
	CHourglassCursor  cCursor;

	if ((pWnd = GetParent()))
	{
		while (IsWindow(pWnd->GetSafeHwnd()) && pWnd->IsKindOf(RUNTIME_CLASS(COlePropertyPage)))
		{
			pWnd = pWnd->GetParent();
			continue;
		}
		if (pWnd->IsKindOf(RUNTIME_CLASS(CMFCPropertySheet)) || pWnd->IsKindOf(RUNTIME_CLASS(CDialog)))
		{
			pWnd->SendMessage(WM_SYSCOMMAND, SC_CLOSE);
			return;
		}
	}
	EndDialog(IDCANCEL);
}

void CLocalePropertySheetDialog::OnHelp()
{
	INT  nCtrl;
	INT  nCtrls;
	CString  szCtrl;

	for (nCtrl = MINMIMICSOBJECTCTRLDIALOGTITLE, nCtrls = MAXMIMICSOBJECTCTRLDIALOGTITLE, GetWindowText(szCtrl); nCtrl <= nCtrls; nCtrl++)
	{
		if (szCtrl == STRING(nCtrl)) break;
		continue;
	}
	if (nCtrl <= nCtrls)
	{
		GetTopLevelParent()->SendMessage(WM_HELP, (WPARAM)-1, (LPARAM)STRING(nCtrl + MINMIMICSOBJECTCTRLTYPE - MINMIMICSOBJECTCTRLDIALOGTITLE));
		return;
	}
}

BOOL CLocalePropertySheetDialog::OnHelpInfo(HELPINFO *lpHelpInfo)
{
	INT  nCtrl;
	INT  nCtrls;
	CString  szCtrl;

	for (nCtrl = MINMIMICSOBJECTCTRLDIALOGTITLE, nCtrls = MAXMIMICSOBJECTCTRLDIALOGTITLE, GetWindowText(szCtrl); nCtrl <= nCtrls; nCtrl++)
	{
		if (szCtrl == STRING(nCtrl)) break;
		continue;
	}
	return((nCtrl <= nCtrls) ? (BOOL)GetTopLevelParent()->SendMessage(WM_HELP, (WPARAM)-1, (LPARAM)STRING(nCtrl + MINMIMICSOBJECTCTRLTYPE - MINMIMICSOBJECTCTRLDIALOGTITLE)) : FALSE);
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

IMPLEMENT_DYNCREATE(CLocalePropertyPage, COlePropertyPage)

CLocalePropertyPage::CLocalePropertyPage(LPCTSTR pszTitle, UINT nTemplateID, UINT nCaptionID) : COlePropertyPage(nTemplateID, nCaptionID)
{
	for (m_nTemplateID = nTemplateID, m_nCaptionID = nCaptionID, m_pDialog = (CLocalePropertySheetDialog *)NULL, m_pDispatch = (LPDISPATCH *)NULL, m_hCtrlWnd = (HWND)NULL, m_hChildWnd = (HWND)NULL, m_hChildSheet = (HWND)NULL, m_bDialog = FALSE; AfxIsValidString(pszTitle); )
	{
		m_szTitle = pszTitle;
		break;
	}
}

VOID CLocalePropertyPage::SetName(LPCTSTR pszName)
{
	CMimicsCtrlDispatchDriver  cMimicsCtrl(GetOleControl());

	cMimicsCtrl.SetName(pszName);
}

CString CLocalePropertyPage::GetName() CONST
{
	CMimicsCtrlDispatchDriver  cMimicsCtrl(GetOleControl());

	return cMimicsCtrl.GetName();
}

BOOL CLocalePropertyPage::Initialize()
{
	return TRUE;
}

COleControl *CLocalePropertyPage::GetOleControl() CONST
{
	return (COleControl *)CCmdTarget::FromIDispatch(m_pDispatch[0]);
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
	return((nCtrlID != IDOK  &&  nCtrlID != ID_APPLY_NOW  &&  nCtrlID != IDCANCEL  &&  nCtrlID != IDHELP) ? COlePropertyPage::GetDlgItem(nCtrlID) : pCtrl[0]);
}

CLocalePropertySheetDialog *CLocalePropertyPage::GetParent() CONST
{
	return m_pDialog;
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
	DWORD  cbTemplate;
	LPVOID  pTemplate[2];
	HGLOBAL  hTemplate[2];
	HRSRC  hPropertyPageTemplate;

	if ((hTemplate[0] = ((hPropertyPageTemplate = FindResourceEx(GetModuleInstance(), RT_DIALOG, pszPropertyPageName, GetLanguageID())) || (hPropertyPageTemplate = FindResourceEx(GetModuleInstance(), RT_DIALOG, pszPropertyPageName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hPropertyPageTemplate = FindResourceEx(GetModuleInstance(), RT_DIALOG, pszPropertyPageName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(GetModuleInstance(), hPropertyPageTemplate) : (HGLOBAL)NULL))
	{
		if ((hTemplate[1] = GlobalAlloc(GHND, (SIZE_T)(cbTemplate = SizeofResource(GetModuleInstance(), hPropertyPageTemplate)))))
		{
			if ((pTemplate[0] = LockResource(hTemplate[0])))
			{
				if ((pTemplate[1] = GlobalLock(hTemplate[1])))
				{
					CopyMemory(pTemplate[1], pTemplate[0], cbTemplate);
					GlobalUnlock(hTemplate[1]);
					return hTemplate[1];
				}
			}
			GlobalFree(hTemplate[1]);
		}
	}
	return((HGLOBAL)NULL);
}

BOOL CLocalePropertyPage::SetChildSheet(CPropertySheet *pSheet, CWnd *pItem)
{
	if (IsChild(pSheet))
	{
		pSheet->SetWindowPos(pItem, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
		m_hChildSheet = pSheet->GetSafeHwnd();
		return TRUE;
	}
	return FALSE;
}

CPropertySheet *CLocalePropertyPage::GetChildSheet() CONST
{
	return((CPropertySheet *)CWnd::FromHandle(m_hChildSheet));
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
					if ((pWnd = GetParent()->GetParent()) && pWnd->IsKindOf(RUNTIME_CLASS(CDialog)))
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
	return COlePropertyPage::PreTranslateMessage(pMsg);
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
	return COlePropertyPage::WindowProc(message, wParam, lParam);
}

BOOL CLocalePropertyPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->IsModified() : FALSE);
}

BOOL CLocalePropertyPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && bAll) ? GetParent()->Check() : TRUE);
}

VOID CLocalePropertyPage::Update()
{
	return;
}

void CLocalePropertyPage::DoDataExchange(CDataExchange *pDX)
{
	COlePropertyPage::DoDataExchange(pDX);
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
	for (m_pCtrls[0].RemoveAll(), m_pCtrls[1].RemoveAll(), m_nCtrlIDs[0].RemoveAll(), m_nCtrlIDs[1].RemoveAll(), m_nCtrlPositions.RemoveAll(); !m_bDialog; )
	{
		delete m_pDialog;
		break;
	}
	COlePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CLocalePropertyPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CLocalePropertyPage)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLocalePropertyPage message handlers

int CLocalePropertyPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	HWND  hDlg;
	ULONG  nCount;

	if (COlePropertyPage::OnCreate(lpCreateStruct) != -1)
	{
		for (m_pDispatch = GetObjectArray(&nCount); (m_pDialog = (FromHandlePermanent((hDlg = CWnd::FromHandle(lpCreateStruct->hwndParent)->GetParent()->GetSafeHwnd()))) ? (CLocalePropertySheetDialog *)CWnd::FromHandle(hDlg) : new CLocalePropertySheetDialog); )
		{
			for (m_bDialog = IsWindow(m_pDialog->GetSafeHwnd()); !m_bDialog && m_pDialog->Attach(hDlg); )
			{
				m_pDialog->SetWindowText(m_szTitle);
				return((Initialize()) ? 0 : -1);
			}
			return((m_bDialog  &&  Initialize()) ? 0 : -1);
		}
	}
	return -1;
}

void CLocalePropertyPage::OnSetPageSite()
{
	HGLOBAL  hTemplate;

	if ((hTemplate = LoadLocalePropertyPageTemplate(MAKEINTRESOURCE(m_nTemplateID))))
	{
		for (SetDialogResource(hTemplate); m_nCaptionID != 0; )
		{
			SetPageName(STRING(m_nCaptionID));
			break;
		}
		GlobalFree(hTemplate);
		return;
	}
	COlePropertyPage::OnSetPageSite();
}

BOOL CLocalePropertyPage::OnInitDialog()
{
	CRect  rWnd;
	CRect  rDlg;

	COlePropertyPage::OnInitDialog();
	m_pDialog->GetWindowRect(rDlg);
	GetTopLevelParent()->GetWindowRect(rWnd);
	m_pDialog->MoveWindow(rWnd.left + (rWnd.Width() - rDlg.Width()) / 2, rWnd.top + (rWnd.Height() - rDlg.Height()) / 2, rDlg.Width(), rDlg.Height());
	return TRUE;
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
	COlePropertyPage::OnActivate(nState, pWndOther, bMinimized);
}
