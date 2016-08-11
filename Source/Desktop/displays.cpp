// DISPLAYS.CPP : Displays Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the displays related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/04/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDisplayDialog dialog

IMPLEMENT_DYNCREATE(CDisplayDialog, CLocaleDialog)

CDisplayDialog::CDisplayDialog() : CLocaleDialog()
{
	//{{AFX_DATA_INIT(CDisplayDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CDisplayDialog::Create(CWnd *pParentWnd, UINT nID, BOOL bModal)
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd, m_bModal = bModal; (pDialogTemplate = (!m_hDialogTemplate) ? LoadLocaleDialogTemplate(MAKEINTRESOURCE(nID)) : (LPVOID)NULL); )
	{
		if (!bModal) return((INT)CreateIndirect(pDialogTemplate, pParentWnd));
		InitModalIndirect(pDialogTemplate);
		break;
	}
	return((INT)DoModal());
}

CDisplayWnd *CDisplayDialog::GetParentDisplay() CONST
{
	CWnd  *pWnd;
	CDisplayWnd  *pDisplayWnd;
	CDisplayDialog  *pDisplayDialog;
	CDisplayPropertySheetDialog  *pDisplayPropertySheetDialog;

	for (pWnd = GetParent(), pDisplayWnd = (CDisplayWnd *)NULL; IsWindow(pWnd->GetSafeHwnd()); )
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CDisplayDialog)))
		{
			if ((pDisplayDialog = (CDisplayDialog *)pWnd))
			{
				pWnd = pDisplayDialog->GetParent();
				continue;
			}
			break;
		}
		if (pWnd->IsKindOf(RUNTIME_CLASS(CDisplayPropertySheetDialog)))
		{
			if ((pDisplayPropertySheetDialog = (CDisplayPropertySheetDialog *)pWnd))
			{
				pWnd = pDisplayPropertySheetDialog->GetParent();
				continue;
			}
			break;
		}
		if (!pWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
		{
			pWnd = pWnd->GetParent();
			continue;
		}
		pDisplayWnd = (CDisplayWnd *)pWnd;
		break;
	}
	return pDisplayWnd;
}

void CDisplayDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDisplayDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDisplayDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayDialog message handlers

BOOL CDisplayDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); (pDisplayWnd = GetParentDisplay())->GetSafeHwnd() == GetParent()->GetSafeHwnd() || rDialog[0].Width() <= rDialog[1].Width() || rDialog[0].Height() <= rDialog[1].Height(); )
	{
		MoveWindow(rDialog[0].left + 5 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	return TRUE;
}

void CDisplayDialog::OnOK()
{
	CHourglassCursor  cCursor;

	if (!m_bModal)
	{
		DestroyWindow();
		return;
	}
	EndDialog(IDOK);
}

void CDisplayDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!m_bModal)
	{
		DestroyWindow();
		return;
	}
	EndDialog(IDCANCEL);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayPropertySheetDialog

IMPLEMENT_DYNCREATE(CDisplayPropertySheetDialog, CLocalePropertySheetDialog)

CDisplayPropertySheetDialog::CDisplayPropertySheetDialog() : CLocalePropertySheetDialog()
{
	//{{AFX_DATA_INIT(CDisplayPropertySheetDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CDisplayPropertySheetDialog::CDisplayPropertySheetDialog(LPCTSTR pszTitle) : CLocalePropertySheetDialog(pszTitle)
{
	//{{AFX_DATA_INIT(CDisplayPropertySheetDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CDisplayPropertySheetDialog::Create(CWnd *pParentWnd, BOOL bModal)
{
	Construct(EMPTYSTRING, pParentWnd);
	return(((m_bModal = bModal)) ? (INT)DoModal() : (INT)CLocalePropertySheetDialog::Create(pParentWnd));
}

CDisplayWnd *CDisplayPropertySheetDialog::GetParentDisplay() CONST
{
	CWnd  *pWnd;
	CDisplayWnd  *pDisplayWnd;
	CDisplayDialog  *pDisplayDialog;
	CDisplayPropertySheetDialog  *pDisplayPropertySheetDialog;

	for (pWnd = GetParent(), pDisplayWnd = (CDisplayWnd *)NULL; IsWindow(pWnd->GetSafeHwnd()); )
	{
		if (pWnd->IsKindOf(RUNTIME_CLASS(CDisplayDialog)))
		{
			if ((pDisplayDialog = (CDisplayDialog *)pWnd))
			{
				pWnd = pDisplayDialog->GetParent();
				continue;
			}
			break;
		}
		if (pWnd->IsKindOf(RUNTIME_CLASS(CDisplayPropertySheetDialog)))
		{
			if ((pDisplayPropertySheetDialog = (CDisplayPropertySheetDialog *)pWnd))
			{
				pWnd = pDisplayPropertySheetDialog->GetParent();
				continue;
			}
			break;
		}
		if (!pWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
		{
			pWnd = pWnd->GetParent();
			continue;
		}
		pDisplayWnd = (CDisplayWnd *)pWnd;
		break;
	}
	return pDisplayWnd;
}

BEGIN_MESSAGE_MAP(CDisplayPropertySheetDialog, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CDisplayPropertySheetDialog)
	ON_COMMAND(IDOK, OnOK)
	ON_COMMAND(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayPropertySheetDialog message handlers

BOOL CDisplayPropertySheetDialog::OnInitDialog()
{
	CRect  rDialog[2];
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	CLocalePropertySheetDialog::OnInitDialog();
	for (GetParent()->GetWindowRect(rDialog[0]), GetWindowRect(rDialog[1]); (pDisplayWnd = GetParentDisplay())->GetSafeHwnd() == GetParent()->GetSafeHwnd() || rDialog[0].Width() <= rDialog[1].Width() || rDialog[0].Height() <= rDialog[1].Height(); )
	{
		MoveWindow(rDialog[0].left + 5 * GetSystemMetrics(SM_CXFRAME), rDialog[0].top + GetSystemMetrics(SM_CYCAPTION) + 5 * GetSystemMetrics(SM_CYFRAME), rDialog[1].Width(), rDialog[1].Height(), FALSE);
		break;
	}
	return TRUE;
}

void CDisplayPropertySheetDialog::OnOK()
{
	CHourglassCursor  cCursor;

	if (!m_bModal)
	{
		DestroyWindow();
		return;
	}
	EndDialog(IDOK);
}

void CDisplayPropertySheetDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!m_bModal)
	{
		DestroyWindow();
		return;
	}
	EndDialog(IDCANCEL);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayLockDialog dialog

IMPLEMENT_DYNCREATE(CDisplayLockDialog, CDisplayDialog)

CDisplayLockDialog::CDisplayLockDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CDisplayLockDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CDisplayLockDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CDisplayLockDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

BOOL CDisplayLockDialog::Initialize()
{
	GetParentDisplay()->GetLockInformation(m_szOwner[0], m_szOwner[1], m_szPassword, m_szReason);
	return TRUE;
}

BOOL CDisplayLockDialog::IsModified() CONST
{
	CString  szReason;
	CString  szOwner[2];
	CString  szPassword[2];

	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_NAME)->GetWindowText(szOwner[0]);
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_CONTACT)->GetWindowText(szOwner[1]);
	GetDlgItem(IDC_DISPLAY_LOCK_PASSWORD)->GetWindowText(szPassword[0]);
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_REASON)->GetWindowText(szReason);
	return((m_szOwner[0] != szOwner[0] || m_szOwner[1] != szOwner[1] || m_szPassword != szPassword[0] || m_szReason != szReason) ? TRUE : FALSE);
}

BOOL CDisplayLockDialog::Check(BOOL bModified) CONST
{
	CString  szPassword[2];

	GetDlgItem(IDC_DISPLAY_LOCK_PASSWORD)->GetWindowText(szPassword[0]);
	GetDlgItem(IDC_DISPLAY_LOCK_CONFIRMATION)->GetWindowText(szPassword[1]);
	return((szPassword[0] == szPassword[1]) ? (!bModified || IsModified()) : FALSE);
}

void CDisplayLockDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayLockDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDisplayLockDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CDisplayLockDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DISPLAY_LOCK_HELP, OnHelp)
	ON_EN_CHANGE(IDC_DISPLAY_LOCK_OWNER_NAME, OnEditchangeOwner)
	ON_EN_CHANGE(IDC_DISPLAY_LOCK_OWNER_REASON, OnEditchangeReason)
	ON_EN_CHANGE(IDC_DISPLAY_LOCK_OWNER_CONTACT, OnEditchangeContact)
	ON_EN_CHANGE(IDC_DISPLAY_LOCK_PASSWORD, OnEditchangePassword)
	ON_EN_CHANGE(IDC_DISPLAY_LOCK_CONFIRMATION, OnEditchangeConfirmation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayLockDialog message handlers

BOOL CDisplayLockDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_NAME)->SetWindowText(m_szOwner[0]);
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_CONTACT)->SetWindowText(m_szOwner[1]);
	GetDlgItem(IDC_DISPLAY_LOCK_PASSWORD)->SetWindowText(m_szPassword);
	GetDlgItem(IDC_DISPLAY_LOCK_CONFIRMATION)->SetWindowText(m_szPassword);
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_REASON)->SetWindowText(m_szReason);
	GetDlgItem(IDC_DISPLAY_LOCK_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_PASSWORD_STATIC)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_PASSWORD)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_CONFIRMATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_CONFIRMATION)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_NAME)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_CONTACT_STATIC)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_CONTACT)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_REASON_STATIC)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_REASON)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_LOCK_PASSWORD)->SetFocus();
	return FALSE;
}

void CDisplayLockDialog::OnEditchangeOwner()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDisplayLockDialog::OnEditchangeReason()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDisplayLockDialog::OnEditchangeContact()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDisplayLockDialog::OnEditchangePassword()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDisplayLockDialog::OnEditchangeConfirmation()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDisplayLockDialog::OnOK()
{
	CString  szReason;
	CString  szOwner[2];
	CString  szPassword;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_NAME)->GetWindowText(szOwner[0]);
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_CONTACT)->GetWindowText(szOwner[1]);
	GetDlgItem(IDC_DISPLAY_LOCK_OWNER_REASON)->GetWindowText(szReason);
	GetDlgItem(IDC_DISPLAY_LOCK_PASSWORD)->GetWindowText(szPassword);
	GetParentDisplay()->SetLockInformation(szOwner[0], szOwner[1], szPassword, szReason);
	EndDialog(IDOK);
}

BOOL CDisplayLockDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_DISPLAYLOCKDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDisplayLockDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_DISPLAYLOCKDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayUnlockDialog dialog

IMPLEMENT_DYNCREATE(CDisplayUnlockDialog, CDisplayDialog)

CDisplayUnlockDialog::CDisplayUnlockDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CDisplayUnlockDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CDisplayUnlockDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CDisplayUnlockDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

BOOL CDisplayUnlockDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_DISPLAY_UNLOCK_PASSWORD)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CDisplayUnlockDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayUnlockDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDisplayUnlockDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CDisplayUnlockDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DISPLAY_UNLOCK_HELP, OnHelp)
	ON_EN_CHANGE(IDC_DISPLAY_UNLOCK_PASSWORD, OnEditchangePassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayUnlockDialog message handlers

BOOL CDisplayUnlockDialog::OnInitDialog()
{
	CString  szReason;
	CString  szOwner[2];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (GetParentDisplay()->GetLockInformation(szOwner[0], szOwner[1], m_szPassword, szReason); !szOwner[0].IsEmpty(); )
	{
		GetDlgItem(IDC_DISPLAY_UNLOCK_OWNER_NAME)->SetWindowText(szOwner[0]);
		break;
	}
	for (; !szOwner[1].IsEmpty(); )
	{
		GetDlgItem(IDC_DISPLAY_UNLOCK_OWNER_CONTACT)->SetWindowText(szOwner[1]);
		break;
	}
	for (; !szReason.IsEmpty(); )
	{
		GetDlgItem(IDC_DISPLAY_UNLOCK_OWNER_REASON)->SetWindowText(szReason);
		break;
	}
	GetDlgItem(IDC_DISPLAY_UNLOCK_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_UNLOCK_PASSWORD_STATIC)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_UNLOCK_PASSWORD)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_UNLOCK_OWNER)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_UNLOCK_OWNER_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_UNLOCK_OWNER_NAME)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_UNLOCK_OWNER_CONTACT_STATIC)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_UNLOCK_OWNER_CONTACT)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_UNLOCK_OWNER_REASON_STATIC)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_UNLOCK_OWNER_REASON)->EnableWindow();
	GetDlgItem(IDC_DISPLAY_UNLOCK_PASSWORD)->SetFocus();
	return FALSE;
}

void CDisplayUnlockDialog::OnEditchangePassword()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDisplayUnlockDialog::OnOK()
{
	CString  szPassword;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_DISPLAY_UNLOCK_PASSWORD)->GetWindowText(szPassword); m_szPassword == szPassword; )
	{
		GetParentDisplay()->SetLockInformation();
		break;
	}
	EndDialog(IDOK);
}

BOOL CDisplayUnlockDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_DISPLAYUNLOCKDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDisplayUnlockDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_DISPLAYUNLOCKDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayLockable

CDisplayLockable::CDisplayLockable()
{
	m_pCriticalSection = new CCriticalSection;
}

CDisplayLockable::~CDisplayLockable()
{
	delete m_pCriticalSection;
}

CCriticalSection *CDisplayLockable::GetLock() CONST
{
	return m_pCriticalSection;
}

BOOL CDisplayLockable::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CDisplayLockable::Unlock()
{
	return m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayToolBar

IMPLEMENT_DYNCREATE(CDisplayToolBar, CMFCToolBar)

CDisplayToolBar::CDisplayToolBar() : CMFCToolBar(), CDisplayLockable()
{
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CDisplayToolBar::SetButtons(CONST UINT *pButtonsID, INT nCount)
{
	INT  nIndex;
	CDisplayLock  cLock(this);

	if (CMFCToolBar::SetButtons(pButtonsID, nCount))
	{
		for (nIndex = 0, m_nButtonsID.RemoveAll(), m_bButtonsState[0].RemoveAll(), m_bButtonsState[1].RemoveAll(), m_bButtonsState[2].RemoveAll(), m_bButtonsState[3].RemoveAll(); nIndex < nCount; nIndex++)
		{
			m_nButtonsID.SetAtGrow(nIndex, pButtonsID[nIndex]);
			m_bButtonsState[0].SetAtGrow(nIndex, FALSE);
			m_bButtonsState[1].SetAtGrow(nIndex, FALSE);
			m_bButtonsState[2].SetAtGrow(nIndex, FALSE);
			m_bButtonsState[3].SetAtGrow(nIndex, FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

INT CDisplayToolBar::CommandToIndex(UINT nButtonID) CONST
{
	INT  nIndex;
	INT  nCount;
	CDisplayLock  cLock(this);

	for (nIndex = 0, nCount = (INT)m_nButtonsID.GetSize(); nIndex < nCount; nIndex++)
	{
		if (nButtonID == m_nButtonsID.GetAt(nIndex)) break;
		continue;
	}
	return((nIndex < nCount) ? nIndex : -1);
}

BOOL CDisplayToolBar::EnableButton(INT nButtonID, BOOL bEnable)
{
	CDisplayLock  cLock(this);

	return((CommandToIndex(nButtonID) >= 0) ? (BOOL)PostMessage(TB_ENABLEBUTTON, nButtonID, MAKELPARAM(bEnable, 0)) : FALSE);
}

BOOL CDisplayToolBar::IsButtonEnabled(INT nButtonID) CONST
{
	INT  nIndex;
	CDisplayLock  cLock(this);

	return(((nIndex = CommandToIndex(nButtonID)) >= 0) ? m_bButtonsState[0].GetAt(nIndex) : FALSE);
}

BOOL CDisplayToolBar::CheckButton(INT nButtonID, BOOL bCheck)
{
	CDisplayLock  cLock(this);

	return((CommandToIndex(nButtonID) >= 0) ? (BOOL)PostMessage(TB_CHECKBUTTON, nButtonID, MAKELPARAM(bCheck, 0)) : FALSE);
}

BOOL CDisplayToolBar::IsButtonChecked(INT nButtonID) CONST
{
	INT  nIndex;
	CDisplayLock  cLock(this);

	return(((nIndex = CommandToIndex(nButtonID)) >= 0) ? m_bButtonsState[1].GetAt(nIndex) : FALSE);
}

BOOL CDisplayToolBar::PressButton(INT nButtonID, BOOL bPress)
{
	CDisplayLock  cLock(this);

	return((CommandToIndex(nButtonID) >= 0) ? (BOOL)PostMessage(TB_PRESSBUTTON, nButtonID, MAKELPARAM(bPress, 0)) : FALSE);
}

BOOL CDisplayToolBar::IsButtonPressed(INT nButtonID) CONST
{
	INT  nIndex;
	CDisplayLock  cLock(this);

	return(((nIndex = CommandToIndex(nButtonID)) >= 0) ? m_bButtonsState[2].GetAt(nIndex) : FALSE);
}

BOOL CDisplayToolBar::HideButton(INT nButtonID, BOOL bHide)
{
	CDisplayLock  cLock(this);

	return((CommandToIndex(nButtonID) >= 0) ? (BOOL)PostMessage(TB_HIDEBUTTON, nButtonID, MAKELPARAM(bHide, 0)) : FALSE);
}

BOOL CDisplayToolBar::IsButtonHidden(INT nButtonID) CONST
{
	INT  nIndex;
	CDisplayLock  cLock(this);

	return(((nIndex = CommandToIndex(nButtonID)) >= 0) ? m_bButtonsState[3].GetAt(nIndex) : FALSE);
}

BOOL CDisplayToolBar::LoadToolBar(UINT uiResID, UINT uiColdResID, UINT uiMenuResID, BOOL bLocked, UINT uiDisabledResID, UINT uiMenuDisabledResID, UINT uiHotResID)
{
	INT  nIndex;
	INT  nCount;
	BITMAP  sBitmap;
	CBitmap  cBitmap;
	CDisplayLock  cLock(this);

	if (cBitmap.LoadBitmap(uiMenuResID) && cBitmap.GetBitmap(&sBitmap) > 0)
	{
		for (SetMenuSizes(CSize(2 * (GetSystemMetrics(SM_CXEDGE) + GetSystemMetrics(SM_CXBORDER)) + sBitmap.bmHeight, 2 * (GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER)) + sBitmap.bmHeight), CSize(sBitmap.bmHeight, sBitmap.bmHeight)); CMFCToolBar::LoadToolBar(uiResID, uiColdResID, 0, bLocked, uiDisabledResID, 0, uiHotResID); )
		{
			for (nIndex = 0, nCount = GetCount(), m_nButtonsID.RemoveAll(), m_bButtonsState[0].RemoveAll(), m_bButtonsState[1].RemoveAll(), m_bButtonsState[2].RemoveAll(), m_bButtonsState[3].RemoveAll(); nIndex < nCount; nIndex++)
			{
				m_nButtonsID.SetAtGrow(nIndex, GetItemID(nIndex));
				m_bButtonsState[0].SetAtGrow(nIndex, FALSE);
				m_bButtonsState[1].SetAtGrow(nIndex, FALSE);
				m_bButtonsState[2].SetAtGrow(nIndex, FALSE);
				m_bButtonsState[3].SetAtGrow(nIndex, FALSE);
			}
			cBitmap.DeleteObject();
			return TRUE;
		}
		cBitmap.DeleteObject();
	}
	return FALSE;
}

BOOL CDisplayToolBar::FloatPane(CRect rectFloat, AFX_DOCK_METHOD dockMethod, bool bShow)
{
	return FALSE;
}

CDisplayWnd *CDisplayToolBar::GetParent() CONST
{
	return((CDisplayWnd *)m_pParentWnd);
}

void CDisplayToolBar::PostNcDestroy()
{
	CDisplayLock  cLock(this);

	m_nButtonsID.RemoveAll();
	m_bButtonsState[0].RemoveAll();
	m_bButtonsState[1].RemoveAll();
	m_bButtonsState[2].RemoveAll();
	m_bButtonsState[3].RemoveAll();
	CMFCToolBar::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDisplayToolBar, CMFCToolBar)
	//{{AFX_MSG_MAP(CDisplayToolBar)
	ON_WM_CREATE()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayToolBar message handlers

int CDisplayToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CDisplayLock  cLock(this);

	if (CMFCToolBar::OnCreate(lpCreateStruct) != -1)
	{
		m_pParentWnd = FromHandle(lpCreateStruct->hwndParent);
		return 0;
	}
	return -1;
}

void CDisplayToolBar::OnMove(int x, int y)
{
	GetParent()->RecalcLayout(this);
	CMFCToolBar::OnMove(x, y);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayStatusBar

IMPLEMENT_DYNCREATE(CDisplayStatusBar, CMFCStatusBar)

CDisplayStatusBar::CDisplayStatusBar() : CMFCStatusBar(), CDisplayLockable()
{
	m_bPanesColor = FALSE;
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CDisplayStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nPane;
	INT  nPanes;
	INT  nWidth;
	UINT  nPaneID;
	UINT  nPaneStyle;
	LPRECT  prPane;
	CDisplayLock  cLock(this);

	if (CMFCStatusBar::SetIndicators(pPanesID, nCount))
	{
		for (nPane = 0, nPanes = (INT)m_prPanes.GetSize(); nPane < nPanes; nPane++)
		{
			if ((prPane = (LPRECT)m_prPanes.GetAt(nPane))) GlobalFree(prPane);
			continue;
		}
		for (nPane = 0, nPanes = nCount, m_nPanesID.RemoveAll(), m_nPanesStyle.RemoveAll(), m_szPanesText.RemoveAll(), m_prPanes.RemoveAll(); nPane < nPanes; nPane++)
		{
			if ((prPane = (LPRECT)GlobalAlloc(GPTR, sizeof(RECT))))
			{
				GetPaneInfo(nPane, nPaneID, nPaneStyle, nWidth);
				GetItemRect(nPane, (LPRECT)prPane);
				m_nPanesID.InsertAt(nPane, pPanesID[nPane]);
				m_nPanesStyle.InsertAt(nPane, nPaneStyle);
				m_szPanesText.InsertAt(nPane, EMPTYSTRING);
				m_bPanesAlertFlag.InsertAt(nPane, FALSE, 1);
				m_prPanes.InsertAt(nPane, prPane, 1);
				continue;
			}
			break;
		}
		return((nPane == nPanes) ? TRUE : FALSE);
	}
	return FALSE;
}

INT CDisplayStatusBar::CommandToIndex(UINT nPaneID) CONST
{
	INT  nPane;
	INT  nPanes;
	CDisplayLock  cLock(this);

	for (nPane = 0, nPanes = (INT)m_nPanesID.GetSize(); nPane < nPanes; nPane++)
	{
		if (nPaneID == m_nPanesID.GetAt(nPane)) break;
		continue;
	}
	return((nPane < nPanes) ? nPane : -1);
}

BOOL CDisplayStatusBar::SetPaneText(UINT nPaneID, LPCTSTR pszText, BOOL bAlerted)
{
	INT  nIndex;
	LPRECT  prPane;
	CDisplayLock  cLock(this);

	if ((nIndex = CommandToIndex(nPaneID)) >= 0)
	{
		if (pszText != m_szPanesText.GetAt(nIndex))
		{
			for (m_szPanesText.SetAt(nIndex, pszText), m_bPanesAlertFlag.SetAt(nIndex, bAlerted), DrawPaneText(nIndex, pszText); (prPane = ((m_nPanesStyle.GetAt(nIndex) & SBPS_STRETCH) != SBPS_STRETCH) ? (LPRECT)m_prPanes.GetAt(nIndex) : (LPRECT)NULL) && prPane->right - prPane->left != CalcPaneWidth(pszText); )
			{
				InvalidateRect(prPane, FALSE);
				break;
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayStatusBar::GetPaneText(UINT nPaneID, CString &szText) CONST
{
	INT  nIndex;
	CDisplayLock  cLock(this);

	if ((nIndex = CommandToIndex(nPaneID)) >= 0)
	{
		szText = m_szPanesText.GetAt(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString CDisplayStatusBar::GetPaneText(UINT nPaneID) CONST
{
	CString  szText;

	return((GetPaneText(nPaneID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

BOOL CDisplayStatusBar::EnablePaneColors(BOOL bEnable)
{
	m_bPanesColor = bEnable;
	return TRUE;
}

CDisplayWnd *CDisplayStatusBar::GetParent() CONST
{
	return((CDisplayWnd *)m_pParentWnd);
}

BOOL CDisplayStatusBar::DrawPaneText(INT nPane, LPCTSTR pszText)
{
	CDC  *pDC;
	INT  nBkColor;
	INT  nOldColor;
	CRect  rText[2];
	CFont  *pOldFont;
	CBrush  cBkBrush;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cPanesFont)))
		{
			if (cBkBrush.CreateSysColorBrush(COLOR_3DFACE))
			{
				nBkColor = pDC->SetBkColor(GetSysColor(COLOR_3DFACE));
				nOldColor = pDC->SetTextColor((nPane > 0 && m_bPanesColor) ? ((!m_bPanesAlertFlag.GetAt(nPane)) ? VGA_COLOR_GREEN : VGA_COLOR_LTRED) : GetSysColor(COLOR_WINDOWTEXT));
				pDC->DrawText(pszText, (rText[0] = rText[1] = CalcPaneTextRect(nPane)), DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_CALCRECT);
				pDC->DrawText(pszText, rText[1], DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
				pDC->ExcludeClipRect(rText[0]);
				pDC->FillRect(rText[1], &cBkBrush);
				pDC->SelectObject(pOldFont);
				pDC->SetTextColor(nOldColor);
				pDC->SetBkColor(nBkColor);
				cBkBrush.DeleteObject();
				ReleaseDC(pDC);
				return TRUE;
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
	return FALSE;
}

INT CDisplayStatusBar::CalcPaneWidth(LPCTSTR pszText) CONST
{
	INT  nWidth;
	CFont  *pOldFont;
	CClientDC  cDC(NULL);

	if ((pOldFont = cDC.SelectObject((CFont *)&m_cPanesFont)))
	{
		nWidth = 2 * GetSystemMetrics(SM_CXEDGE) + cDC.GetTextExtent(pszText).cx;
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

CRect CDisplayStatusBar::CalcPaneTextRect(INT nPane) CONST
{
	CRect  rBar;
	CRect  rText;
	CFont  *pOldFont;
	LPRECT  prPane;
	TEXTMETRIC  tmFont;
	CClientDC  cDC(NULL);

	if ((pOldFont = cDC.SelectObject((CFont *)&m_cPanesFont)))
	{
		for (GetClientRect(rBar); (prPane = (LPRECT)m_prPanes.GetAt(nPane)) && cDC.GetTextMetrics(&tmFont); )
		{
			rText.SetRect(GetSystemMetrics(SM_CXEDGE) + prPane->left, prPane->top + (prPane->bottom - prPane->top - tmFont.tmHeight) / 2, max(min((!GetParent()->IsZoomed()) ? (rBar.right - rBar.Height()) : rBar.right, prPane->right - GetSystemMetrics(SM_CXEDGE)), GetSystemMetrics(SM_CXEDGE) + prPane->left), prPane->top + (prPane->bottom - prPane->top - tmFont.tmHeight) / 2 + tmFont.tmHeight);
			cDC.SelectObject(pOldFont);
			return rText;
		}
		cDC.SelectObject(pOldFont);
	}
	return CRect(0, 0, 0, 0);
}

void CDisplayStatusBar::PostNcDestroy()
{
	INT  nPane;
	INT  nPanes;
	LPRECT  prPane;
	CDisplayLock  cLock(this);

	for (nPane = 0, nPanes = (INT)m_nPanesID.GetSize(); nPane < nPanes; nPane++)
	{
		if ((prPane = (LPRECT)m_prPanes.GetAt(nPane))) GlobalFree(prPane);
		m_prPanes.RemoveAt(nPane);
		nPanes--;
		nPane--;
	}
	m_nPanesID.RemoveAll();
	m_nPanesStyle.RemoveAll();
	m_szPanesText.RemoveAll();
	m_bPanesAlertFlag.RemoveAll();
	CMFCStatusBar::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDisplayStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CDisplayStatusBar)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayStatusBar message handlers

int CDisplayStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFont  *pFont;
	LOGFONT  lfFont;
	CDisplayLock  cLock(this);

	if (CMFCStatusBar::OnCreate(lpCreateStruct) != -1)
	{
		if ((pFont = GetFont()) && pFont->GetLogFont(&lfFont) > 0 && m_cPanesFont.CreateFontIndirect(&lfFont))
		{
			m_pParentWnd = FromHandle(lpCreateStruct->hwndParent);
			return 0;
		}
	}
	return -1;
}

BOOL CDisplayStatusBar::OnEraseBkgnd(CDC *pDC)
{
	INT  nPane;
	INT  nPanes;
	INT  nWidth;
	UINT  nPaneID;
	UINT  nPaneStyle;
	CRect  rBar[2];
	LPRECT  prPane;
	CDisplayLock  cLock(this);

	for (nPane = 0, nPanes = (INT)m_nPanesID.GetSize(); nPane < nPanes; nPane++)
	{
		for (GetClientRect(rBar[0]), GetItemRect(nPane, rBar[1]), GetPaneInfo(nPane, nPaneID, nPaneStyle, nWidth), m_nPanesID.SetAt(nPane, nPaneID), m_nPanesStyle.SetAt(nPane, nPaneStyle), nWidth = CalcPaneWidth(m_szPanesText.GetAt(nPane)); (prPane = ((nPaneStyle & SBPS_STRETCH) != SBPS_STRETCH && rBar[0].IntersectRect(rBar[0], rBar[1])) ? (LPRECT)m_prPanes.GetAt(nPane) : (LPRECT)NULL) && prPane->right - prPane->left != nWidth; )
		{
			SetPaneWidth(nPane, nWidth);
			break;
		}
	}
	for (nPane = 0; nPane < nPanes; nPane++)
	{
		GetItemRect(nPane, (LPRECT)m_prPanes.GetAt(nPane));
		continue;
	}
	for (nPane = 0; nPane < nPanes; nPane++)
	{
		pDC->ExcludeClipRect(CalcPaneTextRect(nPane));
		continue;
	}
	return CMFCStatusBar::OnEraseBkgnd(pDC);
}

void CDisplayStatusBar::OnPaint()
{
	INT  nPane;
	INT  nPanes;
	INT  nWidth;
	UINT  nPaneID;
	UINT  nPaneStyle;
	CRect  rBar[2];
	LPRECT  prPane;
	CDisplayLock  cLock(this);

	for (nPane = 0, nPanes = (INT)m_nPanesID.GetSize(); nPane < nPanes; nPane++)
	{
		for (GetClientRect(rBar[0]), GetItemRect(nPane, rBar[1]), GetPaneInfo(nPane, nPaneID, nPaneStyle, nWidth), m_nPanesID.SetAt(nPane, nPaneID), m_nPanesStyle.SetAt(nPane, nPaneStyle), nWidth = CalcPaneWidth(m_szPanesText.GetAt(nPane)); (prPane = ((nPaneStyle & SBPS_STRETCH) != SBPS_STRETCH && rBar[0].IntersectRect(rBar[0], rBar[1])) ? (LPRECT)m_prPanes.GetAt(nPane) : (LPRECT)NULL) && prPane->right - prPane->left != nWidth; )
		{
			SetPaneWidth(nPane, nWidth);
			break;
		}
	}
	for (nPane = 0; nPane < nPanes; nPane++)
	{
		GetItemRect(nPane, (LPRECT)m_prPanes.GetAt(nPane));
		continue;
	}
	for (nPane = 0; nPane < nPanes; nPane++)
	{
		DrawPaneText(nPane, m_szPanesText.GetAt(nPane));
		ValidateRect(CalcPaneTextRect(nPane));
	}
	CMFCStatusBar::OnPaint();
}

LRESULT CDisplayStatusBar::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	CFont  cFont;
	LOGFONT  lfFont;
	LRESULT  lResult;
	CDisplayLock  cLock(this);

	for (lResult = Default(); m_cPanesFont.GetSafeHandle() != (HANDLE)wParam && wParam != (WPARAM)NULL; )
	{
		if (GetObject((HGDIOBJ)wParam, sizeof(LOGFONT), &lfFont) > 0 && cFont.CreateFontIndirect(&lfFont))
		{
			m_cPanesFont.DeleteObject();
			m_cPanesFont.Attach(cFont.Detach());
		}
		break;
	}
	return lResult;
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayToolTip

IMPLEMENT_DYNCREATE(CDisplayToolTip, CWnd)

CDisplayToolTip::CDisplayToolTip() : CWnd(), CDisplayLockable()
{
	m_ptPosition.x = 0;
	m_ptPosition.y = 0;
}

BOOL CDisplayToolTip::Create(CWnd *pParentWnd, CONST POINT &point, LPCTSTR pszTitle, LPCTSTR pszText)
{
	CPoint  ptPosition;

	for (SetTitle(pszTitle), SetText(pszText), m_ptPosition = ptPosition = point, pParentWnd->ClientToScreen(&ptPosition), Destroy(); CWnd::CreateEx(WS_EX_TOPMOST, AfxRegisterWndClass(CS_SAVEBITS | CS_DROPSHADOW | CS_NOCLOSE, (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR)), EMPTYSTRING, WS_POPUP | WS_BORDER, ptPosition.x, ptPosition.y, 0, 0, pParentWnd->GetSafeHwnd(), (HMENU)NULL); )
	{
		pParentWnd->SetCapture();
		ShowWindow(SW_SHOWNA);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayToolTip::Destroy()
{
	CDisplayLock  cLock(this);

	if (IsWindow(GetSafeHwnd()))
	{
		ReleaseCapture();
		DestroyWindow();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayToolTip::SetTitleFont(CFont *pFont)
{
	LOGFONT  lfFont;
	CDisplayLock  cLock(this);

	if (pFont->GetLogFont(&lfFont) && ((!m_cFont[0].GetSafeHandle() || m_cFont[0].DeleteObject()) && m_cFont[0].CreateFontIndirect(&lfFont)))
	{
		Update();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayToolTip::GetTitleFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;
	CDisplayLock  cLock(this);

	return((m_cFont[0].GetObject(sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

BOOL CDisplayToolTip::SetTextFont(CFont *pFont)
{
	LOGFONT  lfFont;
	CDisplayLock  cLock(this);

	if (pFont->GetLogFont(&lfFont) && ((!m_cFont[1].GetSafeHandle() || m_cFont[1].DeleteObject()) && m_cFont[1].CreateFontIndirect(&lfFont)))
	{
		Update();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayToolTip::GetTextFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;
	CDisplayLock  cLock(this);

	return((m_cFont[1].GetObject(sizeof(LOGFONT), &lfFont) > 0) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}

BOOL CDisplayToolTip::SetTabstops(CONST CUIntArray &nTabs)
{
	CDisplayLock  cLock(this);

	m_nTabs.Copy(nTabs);
	return TRUE;
}

INT CDisplayToolTip::GetTabstops(CUIntArray &nTabs) CONST
{
	CDisplayLock  cLock(this);

	nTabs.Copy(m_nTabs);
	return((INT)nTabs.GetSize());
}

BOOL CDisplayToolTip::SetTitle(LPCTSTR pszTitle)
{
	CDisplayLock  cLock(this);

	m_szTitle = pszTitle;
	return TRUE;
}

CString CDisplayToolTip::GetTitle() CONST
{
	CDisplayLock  cLock(this);

	return m_szTitle;
}

BOOL CDisplayToolTip::SetText(LPCTSTR pszText)
{
	CDisplayLock  cLock(this);

	m_szText = pszText;
	return TRUE;
}

CString CDisplayToolTip::GetText() CONST
{
	CDisplayLock  cLock(this);

	return m_szText;
}

VOID CDisplayToolTip::Update()
{
	CDisplayLock  cLock(this);

	Update(m_szTitle, m_szText, TRUE);
}
VOID CDisplayToolTip::Update(LPCTSTR pszTitle, LPCTSTR pszText, BOOL bForced)
{
	CRect  rToolTip;
	CDisplayLock  cLock(this);

	if (IsWindow(GetSafeHwnd()) && (GetTitle() != pszTitle || GetText() != pszText || bForced))
	{
		for (CalcTabstops((m_szTitle = pszTitle), (m_szText = pszText)), GetWindowRect(rToolTip); rToolTip.IsRectEmpty(); )
		{
			rToolTip.InflateRect(0, 0, 1, 1);
			MoveWindow(rToolTip);
			break;
		}
		Invalidate(FALSE);
	}
}

BOOL CDisplayToolTip::IsVisibleAtPoint(CPoint &pt) CONST
{
	CDisplayLock  cLock(this);

	pt = m_ptPosition;
	return IsWindow(GetSafeHwnd());
}

VOID CDisplayToolTip::CalcTabstops(LPCTSTR pszTitle, LPCTSTR pszText)
{
	CDC  *pDC;
	INT  nPos;
	CSize  sizeTab;
	CFont  *pOldFont;
	CString  szText;
	CString  szLine;
	CUIntArray  nTabs;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(&m_cFont[1])))
		{
			for (szText = pszText, sizeTab.cx = (pDC->GetTextMetrics(&tmFont)) ? tmFont.tmMaxCharWidth : 0, sizeTab.cy = 0; (nPos = szText.Find(EOL)) >= 0; szText = szText.Mid(nPos + 1))
			{
				for (szLine = szText.Left(nPos); szLine.Find(TAB) >= 0; )
				{
					sizeTab.cx = max(CalcMargin().cx + pDC->GetTextExtent(szLine.Left(szLine.Find(TAB))).cx + 1, sizeTab.cx);
					break;
				}
			}
			for (szLine = szText; szLine.Find(TAB) >= 0; )
			{
				sizeTab.cx = max(CalcMargin().cx + pDC->GetTextExtent(szLine.Left(szLine.Find(TAB))).cx + 1, sizeTab.cx);
				break;
			}
			if (!GetTabstops(nTabs))
			{
				nTabs.SetAtGrow(0, sizeTab.cx);
				SetTabstops(nTabs);
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

CSize CDisplayToolTip::CalcExtent(LPCTSTR pszTitle, LPCTSTR pszText, CPoint &ptTitle, CPoint &ptText)
{
	CDC  *pDC;
	INT  nPos;
	CRect  rText;
	CRect  rTitle;
	CSize  sizeText;
	CFont  *pOldFont;
	CString  szTitle;
	CString  szText;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		rText.SetRectEmpty();
		rTitle.SetRectEmpty();
		if (lstrlen(pszTitle) > 0 || lstrlen(pszText) > 0)
		{
			if ((pOldFont = pDC->SelectObject(&m_cFont[0])))
			{
				if (pDC->GetTextMetrics((LPTEXTMETRIC)&tmFont))
				{
					for (szTitle = pszTitle; !szTitle.IsEmpty(); )
					{
						if ((nPos = szTitle.Find(EOL)) >= 0)
						{
							sizeText = pDC->GetTabbedTextExtent(szTitle.Left(nPos), (INT)m_nTabs.GetSize(), (LPINT)m_nTabs.GetData());
							rTitle.right = max(sizeText.cx, rTitle.right);
							rTitle.bottom += tmFont.tmHeight;
							szTitle = szTitle.Mid(nPos + 1);
							continue;
						}
						sizeText = pDC->GetTabbedTextExtent(szTitle, (INT)m_nTabs.GetSize(), (LPINT)m_nTabs.GetData());
						rTitle.right = max(sizeText.cx, rTitle.right);
						rTitle.bottom += tmFont.tmHeight;
						break;
					}
				}
				pDC->SelectObject(pOldFont);
			}
			if ((pOldFont = pDC->SelectObject(&m_cFont[1])))
			{
				if (pDC->GetTextMetrics((LPTEXTMETRIC)&tmFont))
				{
					for (szText = pszText; !szText.IsEmpty(); )
					{
						if ((nPos = szText.Find(EOL)) >= 0)
						{
							sizeText = pDC->GetTabbedTextExtent(szText.Left(nPos), (INT)m_nTabs.GetSize(), (LPINT)m_nTabs.GetData());
							rText.right = max(sizeText.cx, rText.right);
							rText.bottom += tmFont.tmHeight;
							szText = szText.Mid(nPos + 1);
							continue;
						}
						sizeText = pDC->GetTabbedTextExtent(szText, (INT)m_nTabs.GetSize(), (LPINT)m_nTabs.GetData());
						rText.right = max(sizeText.cx, rText.right);
						rText.bottom += tmFont.tmHeight;
						break;
					}
				}
				pDC->SelectObject(pOldFont);
			}
			ReleaseDC(pDC);
			ptTitle = ptText = CalcMargin();
			ptText.y = ptText.y + rTitle.Height();
			return CSize(max(rTitle.Width(), rText.Width()) + 2 * (ptTitle.x + 1), rTitle.Height() + rText.Height() + 2 * (ptTitle.y + 1));
		}
		ReleaseDC(pDC);
	}
	return CSize(0, 0);
}

CSize CDisplayToolTip::CalcMargin()
{
	CDC  *pDC;
	CFont  *pOldFont;
	CSize  sizeMargin;
	TEXTMETRIC  tmFont;

	for (sizeMargin.cx = sizeMargin.cy = 0; (pDC = GetDC()); )
	{
		if ((pOldFont = pDC->SelectObject(&m_cFont[0])))
		{
			if (pDC->GetTextMetrics(&tmFont))
			{
				sizeMargin.cx = tmFont.tmAveCharWidth / 2;
				sizeMargin.cy = tmFont.tmHeight / 6;
			}
			pDC->SelectObject(pOldFont);
		}
		if ((pOldFont = pDC->SelectObject(&m_cFont[1])))
		{
			if (pDC->GetTextMetrics(&tmFont))
			{
				sizeMargin.cx = max(tmFont.tmAveCharWidth / 2, sizeMargin.cx);
				sizeMargin.cy = max(tmFont.tmHeight / 6, sizeMargin.cy);
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
		break;
	}
	return sizeMargin;
}

VOID CDisplayToolTip::DrawContent(CDC *pDC)
{
	INT  nPos;
	INT  nBkgndMode;
	CRect  rToolTip;
	CSize  sizeToolTip;
	CSize  sizeToolText;
	CFont  *pOldFont;
	CPoint  ptText;
	CPoint  ptTitle;
	CBrush  cBkgndBrush;
	CString  szText;
	CString  szTitle;
	COLORREF  nOldColor;
	TEXTMETRIC  tmFont;

	GetWindowRect(rToolTip);
	sizeToolTip = CalcExtent(GetTitle(), GetText(), ptTitle, ptText);
	rToolTip.left = min(rToolTip.left, GetSystemMetrics(SM_CXVIRTUALSCREEN) - GetSystemMetrics(SM_CXFRAME) - sizeToolTip.cx);
	rToolTip.top = (rToolTip.top < GetSystemMetrics(SM_CYVIRTUALSCREEN) - GetSystemMetrics(SM_CYFRAME) - sizeToolTip.cy) ? rToolTip.top : (rToolTip.top - sizeToolTip.cy - 1);
	rToolTip.right = rToolTip.left + sizeToolTip.cx;
	rToolTip.bottom = rToolTip.top + sizeToolTip.cy;
	MoveWindow(rToolTip.left, rToolTip.top, rToolTip.Width(), rToolTip.Height());
	if (cBkgndBrush.CreateSysColorBrush(COLOR_INFOBK))
	{
		nBkgndMode = pDC->SetBkMode(TRANSPARENT);
		nOldColor = pDC->SetTextColor(GetSysColor(COLOR_INFOTEXT));
		if ((pOldFont = pDC->SelectObject(&m_cFont[0])))
		{
			for (szTitle = GetTitle(); !szTitle.IsEmpty(); )
			{
				if ((nPos = szTitle.Find(EOL)) >= 0)
				{
					if (pDC->GetTextMetrics(&tmFont))
					{
						sizeToolText = pDC->GetTextExtent(szTitle.Left(nPos));
						pDC->FillRect(CRect(ptTitle.x, ptTitle.y, rToolTip.Width(), ptTitle.y + sizeToolText.cy), &cBkgndBrush);
						pDC->TabbedTextOut(ptTitle.x, ptTitle.y, szTitle.Left(nPos), (INT)m_nTabs.GetSize(), (LPINT)m_nTabs.GetData(), 0);
						szTitle = szTitle.Mid(nPos + 1);
						ptTitle.y += tmFont.tmHeight;
					}
					continue;
				}
				sizeToolText = pDC->GetTextExtent(szTitle);
				pDC->FillRect(CRect(ptTitle.x, ptTitle.y, rToolTip.Width(), ptTitle.y + sizeToolText.cy), &cBkgndBrush);
				pDC->TabbedTextOut(ptTitle.x, ptTitle.y, szTitle, (INT)m_nTabs.GetSize(), (LPINT)m_nTabs.GetData(), 0);
				break;
			}
			pDC->SelectObject(pOldFont);
		}
		if ((pOldFont = pDC->SelectObject(&m_cFont[1])))
		{
			for (szText = GetText(); !szText.IsEmpty(); )
			{
				if ((nPos = szText.Find(EOL)) >= 0)
				{
					if (pDC->GetTextMetrics(&tmFont))
					{
						sizeToolText = pDC->GetTextExtent(szText.Left(nPos));
						pDC->FillRect(CRect(ptText.x, ptText.y, rToolTip.Width(), ptText.y + sizeToolText.cy), &cBkgndBrush);
						pDC->TabbedTextOut(ptText.x, ptText.y, szText.Left(nPos), (INT)m_nTabs.GetSize(), (LPINT)m_nTabs.GetData(), 0);
						szText = szText.Mid(nPos + 1);
						ptText.y += tmFont.tmHeight;
					}
					continue;
				}
				sizeToolText = pDC->GetTextExtent(szText);
				pDC->FillRect(CRect(ptText.x, ptText.y, rToolTip.Width(), ptText.y + sizeToolText.cy), &cBkgndBrush);
				pDC->TabbedTextOut(ptText.x, ptText.y, szText, (INT)m_nTabs.GetSize(), (LPINT)m_nTabs.GetData(), 0);
				break;
			}
			pDC->SelectObject(pOldFont);
		}
		pDC->SetTextColor(nOldColor);
		pDC->SetBkMode(nBkgndMode);
	}
}

BEGIN_MESSAGE_MAP(CDisplayToolTip, CWnd)
	//{{AFX_MSG_MAP(CDisplayToolTip)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayToolTip message handlers

int CDisplayToolTip::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect  rToolTip;
	CSize  sizeToolTip;
	CPoint  ptToolTip[2];
	LOGFONT  lfFont[2];
	CFontTools  cFontTools[2] = { &lfFont[0],&lfFont[1] };
	CDisplayLock  cLock(this);

	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (lfFont[0].lfWeight = FW_BOLD; (m_cFont[0].GetSafeHandle() || m_cFont[0].CreateFontIndirect(&lfFont[0])) && (m_cFont[1].GetSafeHandle() || m_cFont[1].CreateFontIndirect(&lfFont[1])); )
		{
			for (CalcTabstops(GetTitle(), GetText()), sizeToolTip = CalcExtent(GetTitle(), GetText(), ptToolTip[0], ptToolTip[1]); sizeToolTip.cx > 0 && sizeToolTip.cy > 0; )
			{
				rToolTip.left = min(lpCreateStruct->x, GetSystemMetrics(SM_CXVIRTUALSCREEN) - GetSystemMetrics(SM_CXFRAME) - sizeToolTip.cx);
				rToolTip.top = (lpCreateStruct->y + GetSystemMetrics(SM_CYCURSOR) < GetSystemMetrics(SM_CYVIRTUALSCREEN) - GetSystemMetrics(SM_CYFRAME) - sizeToolTip.cy) ? (lpCreateStruct->y + GetSystemMetrics(SM_CYCURSOR)) : (lpCreateStruct->y - sizeToolTip.cy - 1);
				rToolTip.right = rToolTip.left + sizeToolTip.cx;
				rToolTip.bottom = rToolTip.top + sizeToolTip.cy;
				MoveWindow(rToolTip);
				return 0;
			}
			break;
		}
	}
	return -1;
}

BOOL CDisplayToolTip::OnEraseBkgnd(CDC *pDC)
{
	CRect  rToolTip;
	CBrush  cBkgndBrush;
	CDisplayLock  cLock(this);

	for (GetClientRect(rToolTip); cBkgndBrush.CreateSysColorBrush(COLOR_INFOBK); )
	{
		pDC->FillRect(rToolTip, &cBkgndBrush);
		cBkgndBrush.DeleteObject();
		return TRUE;
	}
	return CWnd::OnEraseBkgnd(pDC);
}

void CDisplayToolTip::OnPaint()
{
	CPaintDC  cDC(this);
	CDisplayLock  cLock(this);

	DrawContent(&cDC);
}

void CDisplayToolTip::OnDestroy()
{
	CDisplayLock  cLock(this);

	m_szText.Empty();
	m_szTitle.Empty();
	m_ptPosition.x = 0;
	m_ptPosition.y = 0;
	m_nTabs.RemoveAll();
	m_cFont[0].DeleteObject();
	m_cFont[1].DeleteObject();
	CWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd

IMPLEMENT_DYNAMIC(CDisplayWnd, CLocaleMDIChildWnd)

CDisplayWnd::CDisplayWnd() : CLocaleMDIChildWnd(), CDisplayLockable()
{
	m_nType = DISPLAY_TYPE_NONE;
	m_nMode = DISPLAY_MODE_NONE;
	m_nScope = DISPLAY_SCOPE_NONE;
	m_nShow = SW_SHOWNORMAL;
	m_bFlag = FALSE;
	m_bRedraw = FALSE;
	m_pLink = (CDisplayWnd *)NULL;
	m_pParentWnd = (CMDIFrameWnd *)NULL;
	Initialize(FALSE);
}

BOOL CDisplayWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, CONST RECT &rect, UINT nResourceID, UINT nStyle, INT nBkgndColor)
{
	if (CLocaleMDIChildWnd::Create(AfxRegisterWndClass(0, LoadCursor((HINSTANCE)NULL, IDC_ARROW), GetSysColorBrush(nBkgndColor), LoadIcon(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(nResourceID))), pszTitle, nStyle, rect, (m_pParentWnd = pParentWnd)))
	{
		ModifyStyleEx(0, WS_EX_CLIENTEDGE);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayWnd::SetType(INT nType)
{
	switch (LOWORD(nType))
	{
	case DISPLAY_TYPE_NONE:
	case DISPLAY_TYPE_AND:
	case DISPLAY_TYPE_GRD:
	case DISPLAY_TYPE_HEX:
	case DISPLAY_TYPE_OOL:
	case DISPLAY_TYPE_MMD:
	case DISPLAY_TYPE_POD:
	case DISPLAY_TYPE_TPEP:
	case DISPLAY_TYPE_SATELLITETRACKINGTOOL:
	case DISPLAY_TYPE_EVENTBOX:
	case DISPLAY_TYPE_MAILBOX:
	case DISPLAY_TYPE_LOGBOOK:
	case DISPLAY_TYPE_TCMANUALSTACK:
	case DISPLAY_TYPE_TCAUTOMATICSTACK:
	case DISPLAY_TYPE_TCPROCEDURESMONITOR:
	case DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP:
	case DISPLAY_TYPE_TCONBOARDBUFFERQUEUES:
	case DISPLAY_TYPE_TCONBOARDMEMORYIMAGES:
	case DISPLAY_TYPE_TCHISTORY:
	{ m_nType = nType;
	return TRUE;
	}
	}
	return FALSE;
}

INT CDisplayWnd::GetType() CONST
{
	return m_nType;
}

BOOL CDisplayWnd::SetScope(INT nScope)
{
	switch (nScope)
	{
	case DISPLAY_SCOPE_NONE:
	case DISPLAY_SCOPE_GLOBAL:
	case DISPLAY_SCOPE_LOCAL:
	{ m_nScope = nScope;
	return TRUE;
	}
	}
	return FALSE;
}

INT CDisplayWnd::GetScope() CONST
{
	return m_nScope;
}

BOOL CDisplayWnd::SetMode(UINT nMode)
{
	switch (nMode)
	{
	case DISPLAY_MODE_NONE:
	case DISPLAY_MODE_REALTIME:
	case DISPLAY_MODE_HISTORY:
	{ m_nMode = nMode;
	return TRUE;
	}
	}
	return FALSE;
}

UINT CDisplayWnd::GetMode() CONST
{
	return m_nMode;
}

BOOL CDisplayWnd::SetState(UINT nShow)
{
	switch (nShow)
	{
	case SW_SHOWNORMAL:
	case SW_SHOWMINIMIZED:
	case SW_SHOWMAXIMIZED:
	{ m_nShow = nShow;
	return TRUE;
	}
	}
	return FALSE;
}

UINT CDisplayWnd::GetState() CONST
{
	return MAKELONG((!IsZoomed()) ? ((!IsIconic()) ? SW_SHOWNORMAL : SW_SHOWMINIMIZED) : SW_SHOWMAXIMIZED, LOWORD(m_nShow));
}

VOID CDisplayWnd::SetLinks(CONST CPtrArray &pLinks)
{
	CDisplayLock  cLock(this);

	m_pLinks.Copy(pLinks);
}

INT CDisplayWnd::GetLinks(CPtrArray &pLinks) CONST
{
	CDisplayLock  cLock(this);

	pLinks.Copy(m_pLinks);
	return((INT)pLinks.GetSize());
}

VOID CDisplayWnd::AddLink(CDisplayWnd *pDisplayWnd)
{
	INT  nLink;
	INT  nLinks;
	CDisplayLock  cLock(this);

	for (nLink = 0, nLinks = (INT)m_pLinks.GetSize(); nLink < nLinks; nLink++)
	{
		if (m_pLinks.GetAt(nLink) == (LPVOID)pDisplayWnd) break;
		continue;
	}
	for (; nLink == nLinks; )
	{
		m_pLinks.Add(pDisplayWnd);
		break;
	}
}

BOOL CDisplayWnd::RemoveLink(CDisplayWnd *pDisplayWnd)
{
	INT  nLink;
	INT  nLinks;
	CDisplayLock  cLock(this);

	for (nLink = 0, nLinks = (INT)m_pLinks.GetSize(); nLink < nLinks; nLink++)
	{
		if (m_pLinks.GetAt(nLink) == (LPVOID)pDisplayWnd) break;
		continue;
	}
	if (nLink < nLinks)
	{
		m_pLinks.RemoveAt(nLink);
		return TRUE;
	}
	return FALSE;
}

VOID CDisplayWnd::SetLink(CDisplayWnd *pDisplayWnd)
{
	CDisplayLock  cLock(this);

	m_pLink = pDisplayWnd;
}

CDisplayWnd *CDisplayWnd::GetLink() CONST
{
	CDisplayLock  cLock(this);

	return m_pLink;
}

VOID CDisplayWnd::SetLinkByName(LPCTSTR pszName)
{
	CDisplayLock  cLock(this);

	m_szLink = (AfxIsValidString(pszName)) ? pszName : EMPTYSTRING;
}

CString CDisplayWnd::GetLinkByName() CONST
{
	CDisplayLock  cLock(this);

	return m_szLink;
}

VOID CDisplayWnd::SetLockInformation()
{
	return SetLockInformation(EMPTYSTRING, EMPTYSTRING, EMPTYSTRING, EMPTYSTRING);
}
VOID CDisplayWnd::SetLockInformation(LPCTSTR pszOwner, LPCTSTR pszContact, LPCTSTR pszPassword, LPCTSTR pszReason)
{
	CDisplayLock  cLock(this);

	m_szOwner[0] = pszOwner;
	m_szOwner[1] = pszContact;
	m_szPassword = pszPassword;
	m_szReason = pszReason;
}

BOOL CDisplayWnd::GetLockInformation(CString &szOwner, CString &szContact, CString &szPassword, CString &szReason) CONST
{
	CDisplayLock  cLock(this);

	szOwner = m_szOwner[0];
	szContact = m_szOwner[1];
	szPassword = m_szPassword;
	szReason = m_szReason;
	return !szPassword.IsEmpty();
}

BOOL CDisplayWnd::Start()
{
	return Initialize(TRUE);
}

BOOL CDisplayWnd::Prepare(BOOL bDialog)
{
	return !bDialog;
}

BOOL CDisplayWnd::Initialize(BOOL bFlag)
{
	m_bFlag = bFlag;
	return TRUE;
}
BOOL CDisplayWnd::Initialize(CTMEnvironment *pTMEnvironment)
{
	return TRUE;
}
BOOL CDisplayWnd::Initialize(CString &szTag, CTimeTag &tTag)
{
	return TRUE;
}

BOOL CDisplayWnd::IsInitialized() CONST
{
	return m_bFlag;
}

BOOL CDisplayWnd::InitializeTMData(UINT nMode)
{
	return FALSE;
}
BOOL CDisplayWnd::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	return FALSE;
}

BOOL CDisplayWnd::Check() CONST
{
	return TRUE;
}

VOID CDisplayWnd::Update()
{
	RedrawLayout();
}
BOOL CDisplayWnd::Update(LPVOID pData)
{
	return FALSE;
}
BOOL CDisplayWnd::Update(LPCTSTR pszMessage)
{
	return FALSE;
}
BOOL CDisplayWnd::Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags)
{
	return FALSE;
}
BOOL CDisplayWnd::Update(CONST CTimeKey &tTimeKey, CTCEnvironment *pTCEnvironment, UINT nFlags)
{
	return FALSE;
}

VOID CDisplayWnd::Reset(CTMEnvironment *pTMEnvironment)
{
	return;
}
VOID CDisplayWnd::Reset(CTCEnvironment *pTCEnvironment)
{
	return;
}

BOOL CDisplayWnd::Stop()
{
	return Initialize(FALSE);
}

BOOL CDisplayWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	CProfile  cProfile;

	DeleteInfo(nPage, nDisplay);
	return cProfile.SetDisplayWindowTitle(nPage, nDisplay, pszTitle) && cProfile.SetDisplayWindowType(nPage, nDisplay, GetType()) && cProfile.SetDisplayWindowScope(nPage, nDisplay, GetScope()) && cProfile.SetDisplayWindowMode(nPage, nDisplay, GetMode()) && cProfile.SetDisplayWindowData(nPage, nDisplay, pDisplayInfo->pData) && cProfile.SetDisplayWindowLink(nPage, nDisplay, GetLinkByName()) && cProfile.SetDisplayWindowPlacement(nPage, nDisplay, &pDisplayInfo->rWnd, &pDisplayInfo->ptWnd, pDisplayInfo->nNumber, pDisplayInfo->nShow, pDisplayInfo->bShow) && cProfile.SetDisplayWindowLockInformation(nPage, nDisplay, m_szOwner[0], m_szOwner[1], m_szPassword, m_szReason);
}

BOOL CDisplayWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	CProfile  cProfile;

	return cProfile.GetDisplayWindowTitle(nPage, nDisplay, szTitle) && cProfile.GetDisplayWindowScope(nPage, nDisplay, pDisplayInfo->nScope) && cProfile.GetDisplayWindowMode(nPage, nDisplay, pDisplayInfo->nMode) && cProfile.GetDisplayWindowData(nPage, nDisplay, &pDisplayInfo->pData) && cProfile.GetDisplayWindowLink(nPage, nDisplay, m_szLink) && cProfile.GetDisplayWindowPlacement(nPage, nDisplay, &pDisplayInfo->rWnd, &pDisplayInfo->ptWnd, pDisplayInfo->nNumber, pDisplayInfo->nShow, pDisplayInfo->bShow) && cProfile.GetDisplayWindowLockInformation(nPage, nDisplay, m_szOwner[0], m_szOwner[1], m_szPassword, m_szReason);
}

BOOL CDisplayWnd::DeleteInfo(INT nPage, INT nDisplay)
{
	CProfile  cProfile;

	return cProfile.DeleteDisplayWindowInfo(nPage, nDisplay);
}

BOOL CDisplayWnd::SetLayoutInfo(LPCVOID pData)
{
	return TRUE;
}

INT CDisplayWnd::GetLayoutInfo(LPVOID *pData) CONST
{
	return 0;
}

VOID CDisplayWnd::ReduceFonts(BOOL bRestore)
{
	return;
}

BOOL CDisplayWnd::CanReduceFonts(BOOL bRestore) CONST
{
	return FALSE;
}

VOID CDisplayWnd::UpdateSysMenu(CMenu *pMenu)
{
	return;
}

VOID CDisplayWnd::UpdateBars()
{
	return;
}

BOOL CDisplayWnd::Print(PRINTDLG *pPrintInfo)
{
	return FALSE;
}

BOOL CDisplayWnd::CanPrint() CONST
{
	return FALSE;
}

BOOL CDisplayWnd::IsLinkable() CONST
{
	return((GetType() != DISPLAY_TYPE_EVENTBOX  &&  GetScope() != DISPLAY_SCOPE_GLOBAL  &&  !GetLink()) ? TRUE : FALSE);
}

BOOL CDisplayWnd::IsAlerted() CONST
{
	return FALSE;
}

VOID CDisplayWnd::DoProtect()
{
	BOOL  bProtected;

	ReportEvent((((bProtected = IsProtected()) && !m_dlgUnlock.Create(this)) || (!bProtected  &&  !m_dlgLock.Create(this))) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CDisplayWnd::CanProtect() CONST
{
	return((GetScope() == DISPLAY_SCOPE_LOCAL) ? TRUE : FALSE);
}

BOOL CDisplayWnd::IsProtected() CONST
{
	CString  szOwner;
	CString  szReason;
	CString  szContact;
	CString  szPassword;

	return GetLockInformation(szOwner, szContact, szPassword, szReason);
}

void CDisplayWnd::ActivateFrame(int nCmdShow)
{
	if (GetScope() == DISPLAY_SCOPE_GLOBAL  &&  nCmdShow == SW_HIDE)
	{
		for (SetState(LOWORD(GetState())); IsZoomed(); )
		{
			GetParent()->LockWindowUpdate();
			CLocaleMDIChildWnd::ActivateFrame(SW_RESTORE);
			CLocaleMDIChildWnd::ActivateFrame(SW_HIDE);
			GetParent()->UnlockWindowUpdate();
			return;
		}
	}
	CLocaleMDIChildWnd::ActivateFrame(nCmdShow);
}

BOOL CALLBACK CDisplayWnd::EnumDisplayWindows(HWND hWnd, LPARAM lParam)
{
	INT  nPage;
	INT  nPages;
	INT  nCount;
	BOOL  bPage;
	CWnd  *pWnd;
	CString  szDisplayTitle;
	CPtrArray  pPageDisplays;
	CDisplayWnd  *pDisplayWnd[2];
	PDISPLAYTITLEINFO  pDisplayTitleInfo = (PDISPLAYTITLEINFO)lParam;

	if ((pWnd = CWnd::FromHandle(hWnd)) && pWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
	{
		if ((pDisplayWnd[0] = (CDisplayWnd *)pWnd) && pDisplayTitleInfo->hWnd[0] != hWnd)
		{
			for (nPage = 0, nPages = (pDisplayWnd[0]->GetScope() == DISPLAY_SCOPE_LOCAL) ? GetDisplayArea()->GetPageCount() : 0, bPage = FALSE; nPage < nPages; nPage++)
			{
				for (GetDisplayArea()->EnumDisplays(nPage, pPageDisplays), nCount = 0; pPageDisplays.GetSize() > 0 && nCount <= 1; pPageDisplays.RemoveAt(0))
				{
					if ((pDisplayWnd[1] = (CDisplayWnd *)pPageDisplays.GetAt(0)) == pDisplayWnd[0])
					{
						nCount++;
						continue;
					}
					if (pDisplayWnd[1]->GetSafeHwnd() == pDisplayTitleInfo->hWnd[0])
					{
						bPage = TRUE;
						nCount++;
						continue;
					}
				}
				if (nCount > 1) break;
			}
			if (!nPages || nCount > 1)
			{
				for (pDisplayWnd[0]->GetWindowText(szDisplayTitle); szDisplayTitle == pDisplayTitleInfo->pszTitle; )
				{
					pDisplayTitleInfo->nNumber = ++pDisplayTitleInfo->nCount + 1;
					pDisplayTitleInfo->hWnd[1] = hWnd;
					return TRUE;
				}
			}
			if ((pDisplayWnd[0]->IsWindowVisible() && !bPage) || !nPages || nCount > 1)
			{
				for (pDisplayWnd[0]->GetWindowText(szDisplayTitle); szDisplayTitle.Left(lstrlen(pDisplayTitleInfo->pszTitle)) == pDisplayTitleInfo->pszTitle && szDisplayTitle.Mid(lstrlen(pDisplayTitleInfo->pszTitle), 1) == CString(STRING(IDS_WINDOW_EXTENDEDTITLE)).Mid(lstrlen(STRING(IDS_WINDOW_TITLE)), 1); )
				{
					pDisplayTitleInfo->nNumber = max(_ttoi(szDisplayTitle.Mid(lstrlen(pDisplayTitleInfo->pszTitle) + 1)) + 1, max(pDisplayTitleInfo->nNumber, pDisplayTitleInfo->nCount + 1));
					pDisplayTitleInfo->nCount = pDisplayTitleInfo->nCount + 1;
					pDisplayTitleInfo->hWnd[2] = hWnd;
					break;
				}
			}
		}
	}
	return TRUE;
}

CRect CDisplayWnd::CalcMenuItemAlignment(CONST RECT &rMenu, CONST RECT &rItem) CONST
{
	CRect  rPosition(rItem);

	if (IsRightToLeftMenuItemAlignment())
	{
		rPosition.left = rMenu.left + rMenu.right - rItem.right;
		rPosition.right = rMenu.left + rMenu.right - rItem.left;
	}
	return rPosition;
}

BOOL CDisplayWnd::IsLeftToRightMenuItemAlignment() CONST
{
	BOOL  bAligned;

	return((!SystemParametersInfo(SPI_GETMENUDROPALIGNMENT, (UINT)NULL, &bAligned, 0) || !bAligned) ? TRUE : FALSE);
}

BOOL CDisplayWnd::IsRightToLeftMenuItemAlignment() CONST
{
	return !IsLeftToRightMenuItemAlignment();
}

VOID CDisplayWnd::RedrawLayout(BOOL bRedraw)
{
	if (bRedraw)
	{
		RedrawWindow((LPCRECT)NULL, (CRgn *)NULL, RDW_FRAME | RDW_ALLCHILDREN | RDW_INVALIDATE);
		return;
	}
}

BOOL CDisplayWnd::IsRequiringRedraw() CONST
{
	CRect  rDisplayWnd[2];
	CDisplayWnd  *pDisplayWnd;
	CDisplayArea  *pDisplayArea;

	if ((pDisplayArea = (GetType() != DISPLAY_TYPE_SATELLITETRACKINGTOOL) ? GetDisplayArea() : (CDisplayArea *)NULL))
	{
		for (GetWindowRect(rDisplayWnd[0]); (pDisplayWnd = pDisplayArea->FindDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL)) && pDisplayWnd->IsWindowVisible(); )
		{
			pDisplayWnd->GetWindowRect(rDisplayWnd[1]);
			return CRect().IntersectRect(rDisplayWnd[0], rDisplayWnd[1]);
		}
	}
	return FALSE;
}

void CDisplayWnd::RecalcLayout(CDisplayToolBar *pToolBar)
{
	return;
}
void CDisplayWnd::RecalcLayout(BOOL bNotify)
{
	CLocaleMDIChildWnd::RecalcLayout(bNotify);
}

CMainWnd *CDisplayWnd::GetParent() CONST
{
	return((CMainWnd *)m_pParentWnd);
}

BOOL CDisplayWnd::Lock()
{
	return GetLock()->Lock();
}

BOOL CDisplayWnd::Unlock()
{
	return GetLock()->Unlock();
}

BEGIN_MESSAGE_MAP(CDisplayWnd, CLocaleMDIChildWnd)
	//{{AFX_MSG_MAP(CDisplayWnd)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_MDIACTIVATE()
	ON_WM_SYSCOMMAND()
	ON_WM_MOVING()
	ON_WM_MOVE()
	ON_WM_ENTERSIZEMOVE()
	ON_WM_EXITSIZEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd message handlers

int CDisplayWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CLocaleMDIChildWnd::OnCreate(lpCreateStruct) != -1)
	{
		SetWindowText(lpCreateStruct->lpszName);
		return 0;
	}
	return -1;
}

void CDisplayWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDisplayFrame  *pDisplayFrame;

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		if ((pDisplayFrame = GetDisplayFrame()))
		{
			if (LOWORD(GetState()) != HIWORD(GetState()) && bShow)
			{
				ActivateFrame(HIWORD(GetState()));
				pDisplayFrame->RecalcBars();
				return;
			}
			pDisplayFrame->RecalcBars();
		}
	}
	CLocaleMDIChildWnd::OnShowWindow(bShow, nStatus);
}

void CDisplayWnd::OnWindowPosChanging(WINDOWPOS *lpwndpos)
{
	CSatelliteTrackingToolWnd  *pSatelliteTrackingToolWnd;

	if ((pSatelliteTrackingToolWnd = (CSatelliteTrackingToolWnd *)GetParent()->GetGlobalDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL)))
	{
		pSatelliteTrackingToolWnd->ShowSideBars(GetMDIFrame()->MDIGetActive() == pSatelliteTrackingToolWnd);
	}
	CLocaleMDIChildWnd::OnWindowPosChanging(lpwndpos);
}

void CDisplayWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	if (GetDisplayFrame()->IsWindowVisible())
	{
		GetMainWnd()->UpdateMenus();
	}
	CLocaleMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CDisplayWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_MAXIMIZE)
	{
		GetParent()->ShowScrollBar(SB_HORZ, FALSE);
		GetParent()->ShowScrollBar(SB_VERT, FALSE);
	}
	if (nID == SC_NEXTWINDOW)
	{
		GetDisplayArea()->ActivateDisplay(TRUE);
		return;
	}
	if (nID == SC_PREVWINDOW)
	{
		GetDisplayArea()->ActivateDisplay(FALSE);
		return;
	}
	if (nID == SC_CLOSE)
	{
		if (GetScope() == DISPLAY_SCOPE_GLOBAL)
		{
			ActivateFrame(SW_HIDE);
			return;
		}
		for (; IsProtected(); )
		{
			for (ReportEvent((!m_dlgUnlock.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR); IsProtected(); ) return;
			break;
		}
	}
	CLocaleMDIChildWnd::OnSysCommand(nID, lParam);
}

void CDisplayWnd::OnMoving(UINT nSide, LPRECT lpRect)
{
	BOOL  bDrag;

	RedrawLayout((!SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &bDrag, 0) || bDrag) ? IsRequiringRedraw() : FALSE);
	CLocaleMDIChildWnd::OnMoving(nSide, lpRect);
}

void CDisplayWnd::OnMove(int x, int y)
{
	BOOL  bDrag;

	RedrawLayout((!SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &bDrag, 0) || bDrag) ? IsRequiringRedraw() : FALSE);
	CLocaleMDIChildWnd::OnMove(x, y);
}

void CDisplayWnd::OnEnterSizeMove()
{
	BOOL  bDrag;

	m_bRedraw = (!SystemParametersInfo(SPI_GETDRAGFULLWINDOWS, 0, &bDrag, 0) || !bDrag) ? IsRequiringRedraw() : FALSE;
}

void CDisplayWnd::OnExitSizeMove()
{
	if (m_bRedraw)
	{
		RedrawLayout();
		m_bRedraw = FALSE;
	}
	CLocaleMDIChildWnd::OnExitSizeMove();
}

void CDisplayWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CDisplayArea  *pDisplayArea;

	if ((pDisplayArea = GetDisplayArea()) && pDisplayArea->GetType() == DISPLAYAREA_TYPE_FOLDER  &&  nChar == VK_TAB  &&  HIBYTE(GetKeyState(VK_SHIFT)))
	{
		pDisplayArea->SetFocus();
		return;
	}
	CLocaleMDIChildWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

LRESULT CDisplayWnd::OnSetText(WPARAM wParam, LPARAM lParam)
{
	INT  nLink;
	INT  nLinks;
	CWnd  *pWnd;
	CString  szDisplayTitle;
	CPtrArray  pDisplayLinks;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYTITLEINFO  sDisplayTitleInfo = { { GetSafeHwnd() },(LPCTSTR)lParam };

	if (!_tcsstr(sDisplayTitleInfo.pszTitle, CString(STRING(IDS_WINDOW_EXTENDEDTITLE)).Mid(lstrlen(STRING(IDS_WINDOW_TITLE)), 1)))
	{
		if (EnumChildWindows(GetParent()->GetSafeHwnd(), EnumDisplayWindows, (LPARAM)&sDisplayTitleInfo) && sDisplayTitleInfo.nCount > 0)
		{
			if (sDisplayTitleInfo.nCount == 1 && IsWindow(sDisplayTitleInfo.hWnd[1]))
			{
				if ((pWnd = CWnd::FromHandle(sDisplayTitleInfo.hWnd[1])) != (CWnd *)NULL)
				{
					szDisplayTitle.Format(STRING(IDS_WINDOW_EXTENDEDTITLE), sDisplayTitleInfo.pszTitle, 1);
					pWnd->SetWindowText(szDisplayTitle);
				}
			}
			for (nLink = 0, nLinks = GetLinks(pDisplayLinks), szDisplayTitle.Format(STRING(IDS_WINDOW_EXTENDEDTITLE), sDisplayTitleInfo.pszTitle, sDisplayTitleInfo.nNumber), SetWindowText(szDisplayTitle); nLink < nLinks; nLink++)
			{
				if ((pDisplayWnd = (CDisplayWnd *)pDisplayLinks.GetAt(nLink)))
				{
					pDisplayWnd->SetLinkByName(szDisplayTitle);
					continue;
				}
			}
			return TRUE;
		}
	}
	for (nLink = 0, nLinks = GetLinks(pDisplayLinks); nLink < nLinks; nLink++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplayLinks.GetAt(nLink)))
		{
			pDisplayWnd->SetLinkByName(sDisplayTitleInfo.pszTitle);
			continue;
		}
	}
	return Default();
}

void CDisplayWnd::OnDestroy()
{
	INT  nLink;
	INT  nLinks;
	CWnd  *pWnd;
	LPCTSTR  pPos[2];
	CString  szDisplayTitle;
	CPtrArray  pDisplayLinks;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYTITLEINFO  sDisplayTitleInfo;
	CHourglassCursor  cCursor;

	if (Lock())
	{
		if ((pDisplayWnd = GetLink()))
		{
			if (pDisplayWnd->Lock())
			{
				pDisplayWnd->RemoveLink(this);
				pDisplayWnd->Unlock();
			}
		}
		for (nLink = 0, nLinks = GetLinks(pDisplayLinks); nLink < nLinks; nLink++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pDisplayLinks.GetAt(nLink)))
			{
				if (pDisplayWnd->Lock())
				{
					pDisplayWnd->SetLink();
					pDisplayWnd->SetLinkByName();
					pDisplayWnd->UpdateBars();
					pDisplayWnd->Unlock();
				}
			}
		}
		Unlock();
	}
	for (GetWindowText(szDisplayTitle), GetDisplayArea()->RemoveDisplay(this); LOWORD(GetType()) == DISPLAY_TYPE_EVENTBOX && GetScope() == DISPLAY_SCOPE_GLOBAL; )
	{
		GetMainWnd()->SetReportDisplay();
		break;
	}
	if ((pPos[0] = pPos[1] = _tcsstr(szDisplayTitle, CString(STRING(IDS_WINDOW_EXTENDEDTITLE)).Mid(lstrlen(STRING(IDS_WINDOW_TITLE)), 1))))
	{
		for (sDisplayTitleInfo.hWnd[0] = GetSafeHwnd(), sDisplayTitleInfo.nCount = sDisplayTitleInfo.nNumber = 0; lstrlen(++pPos[1]) > 0; )
		{
			if (!_istdigit(pPos[1][0])) break;
			continue;
		}
		for (pWnd = GetParent(), Default(), sDisplayTitleInfo.pszTitle = szDisplayTitle = (!lstrlen(pPos[1])) ? szDisplayTitle.Left(szDisplayTitle.GetLength() - (INT)(pPos[1] - pPos[0])) : szDisplayTitle; EnumChildWindows(pWnd->GetSafeHwnd(), EnumDisplayWindows, (LPARAM)&sDisplayTitleInfo) && sDisplayTitleInfo.nCount > 0; )
		{
			if ((pWnd = (sDisplayTitleInfo.nCount == 1 && IsWindow(sDisplayTitleInfo.hWnd[2])) ? CWnd::FromHandle(sDisplayTitleInfo.hWnd[2]) : (CWnd *)NULL))
			{
				szDisplayTitle = sDisplayTitleInfo.pszTitle;
				pWnd->SetWindowText(szDisplayTitle);
			}
			break;
		}
	}
	GetMainWnd()->UpdateMenus();
	CLocaleMDIChildWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayPage

IMPLEMENT_DYNCREATE(CDisplayPage, CWnd)

CDisplayPage::CDisplayPage() : CWnd(), CDisplayLockable()
{
	m_nFlags = 0;
	m_sScrollInfo[0].fMask = m_sScrollInfo[1].fMask = SIF_ALL;
	m_sScrollInfo[0].cbSize = m_sScrollInfo[1].cbSize = sizeof(SCROLLINFO);
	m_sScrollInfo[0].nMin = m_sScrollInfo[1].nMin = 0;
	m_sScrollInfo[0].nMax = m_sScrollInfo[1].nMax = 0;
	m_sScrollInfo[0].nPos = m_sScrollInfo[1].nPos = 0;
	m_sScrollInfo[0].nPage = m_sScrollInfo[1].nPage = 0;
	m_sScrollInfo[0].nTrackPos = m_sScrollInfo[1].nTrackPos = 0;
}

BOOL CDisplayPage::Create(CWnd *pParentWnd)
{
	return CWnd::Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW), GetSysColorBrush(COLOR_APPWORKSPACE)), (LPCTSTR)NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(0, 0, 0, 0), pParentWnd, 0);
}

BOOL CDisplayPage::Initialize()
{
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  sDisplayInfo;

	return(((pDisplayWnd = GetMainWnd()->GetGlobalDisplay(DISPLAY_TYPE_EVENTBOX)) && (QueryDefaultDisplayInfo(pDisplayWnd, &sDisplayInfo) || QueryDefaultDisplayInfo(&sDisplayInfo)) && AddDisplay(pDisplayWnd, STRING(IDS_DISPLAY_TITLE_GLOBALEVENTBOX), &sDisplayInfo, FALSE) && (pDisplayWnd = GetMainWnd()->GetGlobalDisplay(DISPLAY_TYPE_OOL)) && (QueryDefaultDisplayInfo(pDisplayWnd, &sDisplayInfo) || QueryDefaultDisplayInfo(&sDisplayInfo)) && AddDisplay(pDisplayWnd, STRING(IDS_DISPLAY_TITLE_GLOBALOOL), &sDisplayInfo, FALSE) && (pDisplayWnd = GetMainWnd()->GetGlobalDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL)) && (QueryDefaultDisplayInfo(pDisplayWnd, &sDisplayInfo) || QueryDefaultDisplayInfo(&sDisplayInfo)) && AddDisplay(pDisplayWnd, STRING(IDS_DISPLAY_TITLE_SATELLITETRACKINGTOOL), &sDisplayInfo, FALSE) && (pDisplayWnd = GetMainWnd()->GetGlobalDisplay(DISPLAY_TYPE_TCMANUALSTACK)) && (QueryDefaultDisplayInfo(pDisplayWnd, &sDisplayInfo) || QueryDefaultDisplayInfo(&sDisplayInfo)) && AddDisplay(pDisplayWnd, STRING(IDS_DISPLAY_TITLE_TCMANUALSTACK), &sDisplayInfo, FALSE) && (pDisplayWnd = GetMainWnd()->GetGlobalDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK)) && (QueryDefaultDisplayInfo(pDisplayWnd, &sDisplayInfo) || QueryDefaultDisplayInfo(&sDisplayInfo)) && AddDisplay(pDisplayWnd, STRING(IDS_DISPLAY_TITLE_TCAUTOMATICSTACK), &sDisplayInfo, FALSE) && (pDisplayWnd = GetMainWnd()->GetGlobalDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR)) && (QueryDefaultDisplayInfo(pDisplayWnd, &sDisplayInfo) || QueryDefaultDisplayInfo(&sDisplayInfo)) && AddDisplay(pDisplayWnd, STRING(IDS_DISPLAY_TITLE_TCPROCEDURESMONITOR), &sDisplayInfo, FALSE) && (pDisplayWnd = GetMainWnd()->GetGlobalDisplay(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP)) && (QueryDefaultDisplayInfo(pDisplayWnd, &sDisplayInfo) || QueryDefaultDisplayInfo(&sDisplayInfo)) && AddDisplay(pDisplayWnd, STRING(IDS_DISPLAY_TITLE_GLOBALTCDIAGNOSTICSOVERSAMPLINGDUMP), &sDisplayInfo, FALSE) && (pDisplayWnd = GetMainWnd()->GetGlobalDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES)) && (QueryDefaultDisplayInfo(pDisplayWnd, &sDisplayInfo) || QueryDefaultDisplayInfo(&sDisplayInfo)) && AddDisplay(pDisplayWnd, STRING(IDS_DISPLAY_TITLE_TCONBOARDBUFFERQUEUES), &sDisplayInfo, FALSE) && (pDisplayWnd = GetMainWnd()->GetGlobalDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES)) && (QueryDefaultDisplayInfo(pDisplayWnd, &sDisplayInfo) || QueryDefaultDisplayInfo(&sDisplayInfo)) && AddDisplay(pDisplayWnd, STRING(IDS_DISPLAY_TITLE_TCONBOARDMEMORYIMAGES), &sDisplayInfo, FALSE) && (pDisplayWnd = GetMainWnd()->GetGlobalDisplay(DISPLAY_TYPE_TCHISTORY)) && (QueryDefaultDisplayInfo(pDisplayWnd, &sDisplayInfo) || QueryDefaultDisplayInfo(&sDisplayInfo)) && AddDisplay(pDisplayWnd, STRING(IDS_DISPLAY_TITLE_GLOBALTCHISTORY), &sDisplayInfo, FALSE)) ? TRUE : FALSE);
}

BOOL CDisplayPage::Activate(BOOL bPage)
{
	INT  nPosition[3];
	POSITION  lPosition;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  *pDisplayInfo;
	CDisplayFrame  *pDisplayFrame;
	WINDOWPLACEMENT  sDisplayPlacement;

	if ((pDisplayFrame = GetMainWnd()->GetDisplayFrame()))
	{
		for (pDisplayInfo = ((lPosition = m_pDisplays.GetHeadPosition())) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL, nPosition[0] = (INT)m_pDisplays.GetSize(), nPosition[1] = 0, nPosition[2] = (pDisplayInfo && pDisplayInfo->bShow) ? pDisplayInfo->nOrder : -1; pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
		{
			nPosition[2] = (pDisplayInfo->bShow) ? min(pDisplayInfo->nOrder, nPosition[2]) : nPosition[2];
			continue;
		}
		for (; nPosition[0] >= nPosition[1]; nPosition[0]--)
		{
			for (pDisplayInfo = ((lPosition = m_pDisplays.GetHeadPosition())) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL, sDisplayPlacement.length = sizeof(WINDOWPLACEMENT); pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
			{
				if ((pDisplayWnd = (CDisplayWnd *)CWnd::FromHandle(pDisplayInfo->hWnd)) && pDisplayInfo->nOrder == nPosition[0])
				{
					CopyMemory(&sDisplayPlacement.rcNormalPosition, &pDisplayInfo->rWnd, sizeof(sDisplayPlacement.rcNormalPosition));
					sDisplayPlacement.ptMinPosition.x = (pDisplayInfo->nShow == SW_SHOWMINIMIZED) ? pDisplayInfo->ptWnd.x : 0;
					sDisplayPlacement.ptMinPosition.y = (pDisplayInfo->nShow == SW_SHOWMINIMIZED) ? pDisplayInfo->ptWnd.y : 0;
					sDisplayPlacement.ptMaxPosition.x = sDisplayPlacement.ptMaxPosition.y = 0;
					sDisplayPlacement.flags = (pDisplayInfo->nShow == SW_SHOWMINIMIZED) ? WPF_SETMINPOSITION : 0;
					sDisplayPlacement.showCmd = (pDisplayInfo->bShow  &&  pDisplayWnd->Check()) ? pDisplayInfo->nShow : SW_HIDE;
					for (pDisplayWnd->SetWindowPlacement(&sDisplayPlacement), pDisplayWnd->SetLayoutInfo(pDisplayInfo->pData), pDisplayWnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | ((!pDisplayInfo->bShow) ? SWP_NOZORDER : FALSE)); nPosition[0] == nPosition[2]; )
					{
						pDisplayWnd->MDIActivate();
						break;
					}
				}
			}
		}
		pDisplayFrame->SetScrollInfo(SB_HORZ, &m_sScrollInfo[0]);
		pDisplayFrame->SetScrollInfo(SB_VERT, &m_sScrollInfo[1]);
		pDisplayFrame->EndPage(bPage);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayPage::Deactivate(BOOL bPage)
{
	INT  nMin[2];
	INT  nMax[2];
	INT  nPosition;
	POSITION  lPosition;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  *pDisplayInfo;
	CDisplayFrame  *pDisplayFrame;
	WINDOWPLACEMENT  sDisplayPlacement;

	if ((pDisplayFrame = GetMainWnd()->GetDisplayFrame()))
	{
		for (pDisplayWnd = (CDisplayWnd *)pDisplayFrame->GetWindow(GW_CHILD), nPosition = 0; pDisplayWnd; pDisplayWnd = (CDisplayWnd *)pDisplayWnd->GetNextWindow())
		{
			for (pDisplayInfo = ((lPosition = m_pDisplays.GetHeadPosition())) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL, sDisplayPlacement.length = sizeof(WINDOWPLACEMENT); pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
			{
				if (pDisplayInfo->hWnd == pDisplayWnd->GetSafeHwnd() && pDisplayWnd->GetWindowPlacement(&sDisplayPlacement))
				{
					CopyMemory(&pDisplayInfo->rWnd, &sDisplayPlacement.rcNormalPosition, sizeof(pDisplayInfo->rWnd));
					if ((pDisplayInfo->nShow = LOWORD(pDisplayWnd->GetState())) == SW_SHOWMINIMIZED)
					{
						pDisplayInfo->ptWnd.x = sDisplayPlacement.ptMinPosition.x;
						pDisplayInfo->ptWnd.y = sDisplayPlacement.ptMinPosition.y;
					}
					pDisplayWnd->GetLayoutInfo(&pDisplayInfo->pData);
					pDisplayInfo->bShow = (pDisplayWnd->GetStyle() & WS_VISIBLE) ? TRUE : FALSE;
					pDisplayInfo->nOrder = nPosition++;
					break;
				}
			}
		}
		pDisplayFrame->BeginPage(bPage);
		pDisplayFrame->GetScrollRange(SB_HORZ, &nMin[0], &nMax[0]);
		pDisplayFrame->GetScrollRange(SB_VERT, &nMin[1], &nMax[1]);
		for (pDisplayWnd = (CDisplayWnd *)pDisplayFrame->GetWindow(GW_CHILD); IsWindow(pDisplayWnd->GetSafeHwnd()) && bPage; pDisplayWnd = (CDisplayWnd *)pDisplayWnd->GetNextWindow())
		{
			if (pDisplayWnd->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
			{
				for (; pDisplayWnd->IsZoomed(); )
				{
					pDisplayWnd->ShowWindow(SW_RESTORE);
					break;
				}
				pDisplayWnd->ShowWindow(SW_HIDE);
			}
		}
		if (!nMin[0] && !nMax[0])
		{
			m_sScrollInfo[0].nMin = 0;
			m_sScrollInfo[0].nMax = 0;
			m_sScrollInfo[0].nPos = 0;
			m_sScrollInfo[0].nPage = 0;
			m_sScrollInfo[0].nTrackPos = 0;
		}
		if (!nMin[1] && !nMax[1])
		{
			m_sScrollInfo[1].nMin = 0;
			m_sScrollInfo[1].nMax = 0;
			m_sScrollInfo[1].nPos = 0;
			m_sScrollInfo[1].nPage = 0;
			m_sScrollInfo[1].nTrackPos = 0;
		}
		pDisplayFrame->GetScrollInfo(SB_HORZ, &m_sScrollInfo[0]);
		pDisplayFrame->GetScrollInfo(SB_VERT, &m_sScrollInfo[1]);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayPage::AddDisplay(CDisplayWnd *pDisplayWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	INT  nDisplay;
	INT  nDisplays;
	CRect  rPosition;
	CString  szTitle;
	POSITION  lPosition;
	DISPLAYINFO  sDefaultInfo;
	DISPLAYINFO  *pDisplayInfo[2];

	if (Lock())
	{
		if ((!IsWindow(pDisplayWnd->GetSafeHwnd()) && pDisplayWnd->QueryDefaultInfo(&sDefaultInfo)) || IsWindow(pDisplayWnd->GetSafeHwnd()))
		{
			if (IsWindow(pDisplayWnd->GetSafeHwnd()) || pDisplayWnd->Create(GetMainWnd(), pszTitle, (!AfxIsValidAddress(pDefaultInfo, sizeof(DISPLAYINFO), FALSE)) ? &sDefaultInfo : pDefaultInfo, (AfxIsValidAddress(pDefaultInfo, sizeof(DISPLAYINFO), FALSE)) ? bDefault : TRUE))
			{
				for (pDisplayWnd->GetWindowRect(rPosition), pDisplayWnd->GetParent()->ScreenToClient(rPosition), rPosition.right = rPosition.left + DISPLAY_DEFAULT_CX, rPosition.bottom = rPosition.top + DISPLAY_DEFAULT_CY; !AfxIsValidAddress(pDefaultInfo, sizeof(DISPLAYINFO), FALSE); )
				{
					pDisplayWnd->MoveWindow(rPosition);
					break;
				}
				for (lPosition = m_pDisplays.GetHeadPosition(), pDisplayInfo[0] = (PDISPLAYINFO)NULL; lPosition; m_pDisplays.GetNext(lPosition), pDisplayInfo[0] = (PDISPLAYINFO)NULL)
				{
					if ((pDisplayInfo[0] = (PDISPLAYINFO)m_pDisplays.GetAt(lPosition)) && pDisplayInfo[0]->hWnd == pDisplayWnd->GetSafeHwnd())
					{
						m_pDisplays.RemoveAt(lPosition);
						break;
					}
				}
				for (nDisplay = 0, nDisplays = (INT)m_pwndDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
				{
					if (m_pwndDisplays.GetAt(nDisplay) == (LPVOID)pDisplayWnd)
					{
						m_pwndDisplays.RemoveAt(nDisplay);
						break;
					}
				}
				if ((pDisplayInfo[0] = (!pDisplayInfo[0]) ? (PDISPLAYINFO)GlobalAlloc(GPTR, sizeof(DISPLAYINFO)) : pDisplayInfo[0]))
				{
					for (CopyMemory(pDisplayInfo[0], (!AfxIsValidAddress(pDefaultInfo, sizeof(DISPLAYINFO), FALSE)) ? &sDefaultInfo : pDefaultInfo, sizeof(DISPLAYINFO)); (pDisplayInfo[0]->pData = (!pDisplayInfo[0]->pData) ? (LPVOID)GlobalAlloc(GPTR, pDisplayWnd->GetLayoutInfo()) : pDisplayInfo[0]->pData); )
					{
						for (lPosition = (pDisplayInfo[0]->nNumber >= 0) ? m_pDisplays.GetHeadPosition() : (POSITION)NULL, pDisplayInfo[0]->hWnd = pDisplayWnd->GetSafeHwnd(), pDisplayInfo[0]->nNumber = (pDisplayInfo[0]->nNumber >= 0) ? pDisplayInfo[0]->nNumber : (INT)m_pDisplays.GetCount(), m_pDisplays.AddTail(pDisplayInfo[0]), m_pwndDisplays.Add(pDisplayWnd), pDisplayWnd->SetMode(pDisplayInfo[0]->nMode), pDisplayWnd->SetScope(pDisplayInfo[0]->nScope); lPosition; m_pDisplays.GetNext(lPosition))
						{
							if ((pDisplayInfo[1] = (PDISPLAYINFO)m_pDisplays.GetAt(lPosition)) && pDisplayInfo[1]->nNumber > pDisplayInfo[0]->nNumber)
							{
								m_pDisplays.InsertBefore(lPosition, m_pDisplays.RemoveTail());
								break;
							}
						}
						if (m_pDisplays.GetCount() == m_pwndDisplays.GetSize())
						{
							for (pDisplayWnd->GetWindowText(szTitle), pDisplayWnd->SetWindowText(szTitle); IsActivated() || pDisplayWnd->GetScope() == DISPLAY_SCOPE_LOCAL; )
							{
								pDisplayWnd->ActivateFrame((pDisplayWnd->GetParent()->IsWindowVisible() && IsActivated() && pDisplayInfo[0]->bShow) ? pDisplayInfo[0]->nShow : ((IsActivated()) ? SW_SHOW : SW_HIDE));
								break;
							}
							Unlock();
							return pDisplayWnd->Prepare(bDefault);
						}
						for (lPosition = m_pDisplays.GetHeadPosition(); lPosition; m_pDisplays.GetNext(lPosition))
						{
							if (pDisplayInfo[0] == (DISPLAYINFO *)m_pDisplays.GetAt(lPosition))
							{
								m_pDisplays.RemoveAt(lPosition);
								break;
							}
						}
						for (nDisplay = 0, nDisplays = (INT)m_pwndDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
						{
							if (m_pwndDisplays.GetAt(nDisplay) == (LPVOID)pDisplayWnd)
							{
								m_pwndDisplays.RemoveAt(nDisplay);
								break;
							}
						}
						GlobalFree(pDisplayInfo[0]->pData);
						break;
					}
					GlobalFree(pDisplayInfo[0]);
				}
				pDisplayWnd->DestroyWindow();
			}
			Unlock();
			return FALSE;
		}
		delete pDisplayWnd;
		Unlock();
	}
	return FALSE;
}

BOOL CDisplayPage::RemoveDisplay(CDisplayWnd *pDisplayWnd)
{
	INT  nPosition;
	POSITION  lPosition;
	PDISPLAYINFO  pDisplayInfo;

	if (Lock())
	{
		for (lPosition = m_pDisplays.GetHeadPosition(); lPosition; m_pDisplays.GetNext(lPosition))
		{
			if ((pDisplayInfo = (PDISPLAYINFO)m_pDisplays.GetAt(lPosition)) && pDisplayInfo->hWnd == pDisplayWnd->GetSafeHwnd())
			{
				m_pDisplays.RemoveAt(lPosition);
				GlobalFree(pDisplayInfo->pData);
				GlobalFree(pDisplayInfo);
				break;
			}
		}
		for (nPosition = (!lPosition) ? (INT)m_pwndDisplays.GetSize() : 0; nPosition < m_pwndDisplays.GetSize(); nPosition++)
		{
			if (pDisplayWnd == (CDisplayWnd *)m_pwndDisplays.GetAt(nPosition))
			{
				m_pwndDisplays.RemoveAt(nPosition);
				break;
			}
		}
		if (m_pDisplays.GetCount() == m_pwndDisplays.GetSize() && lPosition)
		{
			Unlock();
			return TRUE;
		}
		Unlock();
	}
	return FALSE;
}

BOOL CDisplayPage::ActivateDisplay(CDisplayWnd *pDisplayWnd)
{
	POSITION  lPosition;
	PDISPLAYINFO  pDisplayInfo;

	for (lPosition = m_pDisplays.GetHeadPosition(); lPosition; m_pDisplays.GetNext(lPosition))
	{
		if ((pDisplayInfo = (PDISPLAYINFO)m_pDisplays.GetAt(lPosition)) && pDisplayInfo->hWnd == pDisplayWnd->GetSafeHwnd())
		{
			pDisplayWnd->ActivateFrame((!pDisplayWnd->IsZoomed()) ? SW_SHOWNORMAL : SW_SHOW);
			break;
		}
	}
	return((lPosition) ? TRUE : FALSE);
}
BOOL CDisplayPage::ActivateDisplay(BOOL bNext)
{
	INT  nDisplay;
	INT  nDisplays;
	CWnd  *pDisplay;
	CDisplayWnd  *pDisplayWnd;

	for (pDisplay = (CWnd *)GetActiveDisplay(), pDisplayWnd = GetActiveDisplay(); IsWindow(pDisplay->GetSafeHwnd()); )
	{
		if ((pDisplay = (pDisplay->GetNextWindow((bNext) ? GW_HWNDNEXT : GW_HWNDPREV)) ? pDisplay->GetNextWindow((bNext) ? GW_HWNDNEXT : GW_HWNDPREV) : pDisplay->GetWindow((bNext) ? GW_HWNDFIRST : GW_HWNDLAST)))
		{
			for (nDisplay = 0, nDisplays = (INT)m_pwndDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
			{
				if (pDisplay == (CWnd *)m_pwndDisplays.GetAt(nDisplay))
				{
					if (pDisplay->IsWindowVisible()) break;
					continue;
				}
			}
			if (nDisplay < nDisplays) break;
		}
	}
	if (IsWindow(pDisplay->GetSafeHwnd()))
	{
		if (pDisplay != (CWnd *)pDisplayWnd)
		{
			pDisplayWnd->ActivateFrame(SW_SHOWNORMAL);
			return ActivateDisplay((CDisplayWnd *)pDisplay);
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CDisplayPage::ActivateDisplay(UINT nID)
{
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (nID < (UINT)EnumDisplays(pDisplays, TRUE)) ? (CDisplayWnd *)pDisplays.GetAt(nID) : (CDisplayWnd *)NULL))
	{
		pDisplayWnd->ActivateFrame((!pDisplayWnd->IsZoomed()) ? SW_SHOWNORMAL : SW_SHOW);
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayPage::IsActiveDisplay(UINT nID) CONST
{
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;

	return(((pDisplayWnd = (nID < (UINT)EnumDisplays(pDisplays, TRUE)) ? (CDisplayWnd *)pDisplays.GetAt(nID) : (CDisplayWnd *)NULL) && GetMainWnd()->MDIGetActive()->GetSafeHwnd() == pDisplayWnd->GetSafeHwnd()) ? TRUE : FALSE);
}

CDisplayWnd *CDisplayPage::GetActiveDisplay() CONST
{
	POSITION  lPosition;
	PDISPLAYINFO  pDisplayInfo;

	for (lPosition = m_pDisplays.GetHeadPosition(); lPosition; m_pDisplays.GetNext(lPosition))
	{
		if ((pDisplayInfo = (PDISPLAYINFO)m_pDisplays.GetAt(lPosition)) && GetMainWnd()->MDIGetActive()->GetSafeHwnd() != pDisplayInfo->hWnd) continue;
		break;
	}
	return((lPosition) ? (CDisplayWnd *)CWnd::FromHandle(pDisplayInfo->hWnd) : (CDisplayWnd *)NULL);
}

CDisplayWnd *CDisplayPage::FindDisplay(INT nType) CONST
{
	POSITION  lPosition;
	PDISPLAYINFO  pDisplayInfo;
	CDisplayWnd  *pDisplayWnd;

	for (lPosition = m_pDisplays.GetHeadPosition(), pDisplayWnd = (CDisplayWnd *)NULL; lPosition; m_pDisplays.GetNext(lPosition))
	{
		if ((pDisplayInfo = (PDISPLAYINFO)m_pDisplays.GetAt(lPosition)) != (PDISPLAYINFO)NULL)
		{
			if ((pDisplayWnd = (CDisplayWnd *)CWnd::FromHandle(pDisplayInfo->hWnd)))
			{
				if (pDisplayWnd->GetScope() != DISPLAY_SCOPE_GLOBAL) continue;
				if (LOWORD(pDisplayWnd->GetType()) != nType) continue;
				break;
			}
		}
	}
	return((lPosition) ? pDisplayWnd : (CDisplayWnd *)NULL);
}

BOOL CDisplayPage::CloseDisplay()
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = GetActiveDisplay()))
	{
		if (pDisplayWnd->GetScope() == DISPLAY_SCOPE_GLOBAL)
		{
			pDisplayWnd->ActivateFrame(SW_HIDE);
			return TRUE;
		}
		if (!pDisplayWnd->IsProtected())
		{
			pDisplayWnd->DestroyWindow();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CDisplayPage::SaveDisplays(BOOL bAll, INT nPage, INT nMinProgress, INT nMaxProgress)
{
	INT  nOrder;
	INT  nCount;
	INT  nDisplay[2];
	INT  nDisplays[2];
	POSITION  lPosition;
	CString  szDisplayTitle;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  *pDisplayInfo;
	CPtrArray  pDisplays;
	CProfile  cProfile;

	for (nDisplay[0] = 0, nDisplays[0] = (!IsActivated() || Deactivate(FALSE)) ? (INT)m_pDisplays.GetCount() : 0, nOrder = 0, nCount = 0, ShowProgress(nMinProgress + ((nMaxProgress - nMinProgress)*(max(nDisplays[0], 1) - nDisplays[0] + nDisplay[0])) / max(nDisplays[0], 1)); nDisplay[0] < nDisplays[0]; nDisplay[0]++, ShowProgress(nMinProgress + ((nMaxProgress - nMinProgress)*(max(nDisplays[0], 1) - nDisplays[0] + nDisplay[0])) / max(nDisplays[0], 1)))
	{
		for (pDisplayInfo = ((lPosition = m_pDisplays.GetHeadPosition())) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL; pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
		{
			if ((pDisplayWnd = (CDisplayWnd *)CWnd::FromHandle(pDisplayInfo->hWnd)) != (CDisplayWnd *)NULL  &&  pDisplayInfo->nOrder == nOrder)
			{
				for (nDisplay[1] = 0, nDisplays[1] = (INT)pDisplays.GetSize(), pDisplayWnd->GetWindowText(szDisplayTitle); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
				{
					if (pDisplayWnd == (CDisplayWnd *)pDisplays.GetAt(nDisplay[1])) break;
					continue;
				}
				if (nDisplay[1] == nDisplays[1])
				{
					if (!bAll  &&  pDisplayWnd->GetScope() == DISPLAY_SCOPE_GLOBAL  &&  LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_EVENTBOX)
					{
						if (pDisplayWnd->SaveInfo(nPage, nDisplay[0], szDisplayTitle, pDisplayInfo))
						{
							pDisplays.Add(pDisplayWnd);
							nCount++;
							break;
						}
						pDisplays.Add(pDisplayWnd);
						nDisplays[0]--;
						nDisplay[0]--;
						break;
					}
					if (bAll && (pDisplayWnd->GetScope() != DISPLAY_SCOPE_GLOBAL || LOWORD(pDisplayWnd->GetType()) != DISPLAY_TYPE_EVENTBOX))
					{
						if (pDisplayWnd->SaveInfo(nPage, nDisplay[0], szDisplayTitle, pDisplayInfo))
						{
							pDisplays.Add(pDisplayWnd);
							nCount++;
							break;
						}
						pDisplays.Add(pDisplayWnd);
						nDisplays[0]--;
						nDisplay[0]--;
						break;
					}
					pDisplays.Add(pDisplayWnd);
					nCount++;
					break;
				}
			}
		}
		if (!pDisplayInfo)
		{
			nDisplay[0]--;
			nOrder++;
		}
	}
	for (nDisplay[1] = nDisplay[0], nDisplays[1] = (cProfile.GetDisplayPageWindowCount(nPage, nDisplays[1])) ? nDisplays[1] : -1; nDisplay[1] < nDisplays[1]; nDisplay[1]++)
	{
		cProfile.DeleteDisplayWindowInfo(nPage, nDisplay[1]);
		continue;
	}
	if (!cProfile.SetDisplayPageWindowCount(nPage, (nDisplays[1] > 0 && !bAll) ? min(min(nDisplay[0], nDisplays[1]), nCount) : min(nDisplay[0], nCount)) || !cProfile.SetDisplayPageScrollInfo(nPage, &m_sScrollInfo[0], &m_sScrollInfo[1]) || !cProfile.SetDisplayPagePassword(nPage, m_szPassword) || !cProfile.SetDisplayPageUsers(nPage, m_szUsers) || !cProfile.SetDisplayPageFlags(nPage, m_nFlags))
	{
		cProfile.DeleteDisplayPageInfo(nPage);
		return FALSE;
	}
	return((nCount == m_pDisplays.GetCount()) ? TRUE : FALSE);
}

BOOL CDisplayPage::LoadDisplays(BOOL bAll, INT nPage, INT nMinProgress, INT nMaxProgress)
{
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	INT  nDisplayType;
	INT  nDisplayScope;
	HWND  hDisplayWnd;
	CString  szDisplayTitle;
	CDisplayWnd  *pDisplayWnd[2];
	DISPLAYINFO  sDisplayInfo;
	CPtrArray  pDisplays;
	CProfile  cProfile;

	for (nDisplays = ((bAll || Deactivate()) && cProfile.GetDisplayPageWindowCount(nPage, nDisplays)) ? nDisplays : 0, nCount = 0, nDisplay = nDisplays - 1, sDisplayInfo.nOrder = nDisplay, ShowProgress(nMinProgress + ((nMaxProgress - nMinProgress)*(max(nDisplays, 1) - nDisplay - 1)) / max(nDisplays, 1)); nDisplay >= 0; nDisplay--, sDisplayInfo.nOrder = nDisplay, ShowProgress(nMinProgress + ((nMaxProgress - nMinProgress)*(max(nDisplays, 1) - nDisplay - 1)) / max(nDisplays, 1)))
	{
		if (cProfile.GetDisplayWindowType(nPage, nDisplay, nDisplayType) && cProfile.GetDisplayWindowScope(nPage, nDisplay, nDisplayScope))
		{
			if ((!bAll  &&  nDisplayScope == DISPLAY_SCOPE_GLOBAL  &&  LOWORD(nDisplayType) == DISPLAY_TYPE_EVENTBOX) || (bAll && (nDisplayScope != DISPLAY_SCOPE_GLOBAL || LOWORD(nDisplayType) != DISPLAY_TYPE_EVENTBOX)))
			{
				switch (LOWORD(nDisplayType))
				{
				case DISPLAY_TYPE_AND:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = new CANDWnd))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_GRD:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = new CGRDWnd))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_HEX:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = new CHEXWnd))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_OOL:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = (!(pDisplayWnd[1] = FindDefaultDisplay(DISPLAY_TYPE_OOL)) || nDisplayScope != DISPLAY_SCOPE_GLOBAL) ? new COOLWnd : pDisplayWnd[1]))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						if (!pDisplayWnd[1]) delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_MMD:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = new CMMDWnd))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_POD:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = new CPODWnd))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_TPEP:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = new CTPEPWnd))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_SATELLITETRACKINGTOOL:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = (!(pDisplayWnd[1] = FindDefaultDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL))) ? new CSatelliteTrackingToolWnd : pDisplayWnd[1]))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						if (!pDisplayWnd[1]) delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_EVENTBOX:
				{ if ((pDisplayWnd[0] = (!(pDisplayWnd[1] = FindDefaultDisplay(DISPLAY_TYPE_EVENTBOX)) || nDisplayScope != DISPLAY_SCOPE_GLOBAL) ? new CEventBoxWnd : pDisplayWnd[1]))
				{
					if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
					{
						nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
						break;
					}
					if (!pDisplayWnd[1]) delete pDisplayWnd[0];
				}
				break;
				}
				case DISPLAY_TYPE_MAILBOX:
				{
					break;
				}
				case DISPLAY_TYPE_LOGBOOK:
				{
					break;
				}
				case DISPLAY_TYPE_TCMANUALSTACK:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = (!(pDisplayWnd[1] = FindDefaultDisplay(DISPLAY_TYPE_TCMANUALSTACK))) ? new CTCManualStackWnd : pDisplayWnd[1]))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						if (!pDisplayWnd[1]) delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_TCAUTOMATICSTACK:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = (!(pDisplayWnd[1] = FindDefaultDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK))) ? new CTCAutomaticStackWnd : pDisplayWnd[1]))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						if (!pDisplayWnd[1]) delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_TCPROCEDURESMONITOR:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = (!(pDisplayWnd[1] = FindDefaultDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR))) ? new CTCProceduresMonitorWnd : pDisplayWnd[1]))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						if (!pDisplayWnd[1]) delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = (!(pDisplayWnd[1] = FindDefaultDisplay(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP)) || nDisplayScope != DISPLAY_SCOPE_GLOBAL) ? new CTCDiagnosticsOversamplingDumpWnd : pDisplayWnd[1]))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						if (!pDisplayWnd[1]) delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_TCONBOARDBUFFERQUEUES:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = (!(pDisplayWnd[1] = FindDefaultDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES))) ? new CTCOnBoardBufferQueuesWnd : pDisplayWnd[1]))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						if (!pDisplayWnd[1]) delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_TCONBOARDMEMORYIMAGES:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = (!(pDisplayWnd[1] = FindDefaultDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES))) ? new CTCOnBoardMemoryImagesWnd : pDisplayWnd[1]))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						if (!pDisplayWnd[1]) delete pDisplayWnd[0];
					}
				}
				break;
				}
				case DISPLAY_TYPE_TCHISTORY:
				{ if (GetDatabase()->IsInitialized())
				{
					if ((pDisplayWnd[0] = (!(pDisplayWnd[1] = FindDefaultDisplay(DISPLAY_TYPE_TCHISTORY)) || nDisplayScope != DISPLAY_SCOPE_GLOBAL) ? new CTCHistoryWnd : pDisplayWnd[1]))
					{
						if (pDisplayWnd[0]->SetType(nDisplayType) && pDisplayWnd[0]->LoadInfo(nPage, nDisplay, szDisplayTitle, &sDisplayInfo))
						{
							nCount = (AddDisplay(pDisplayWnd[0], szDisplayTitle, &sDisplayInfo, FALSE)) ? (nCount + 1) : nCount;
							break;
						}
						if (!pDisplayWnd[1]) delete pDisplayWnd[0];
					}
				}
				break;
				}
				}
				continue;
			}
			nCount++;
		}
	}
	if (!bAll)
	{
		if (!CheckDisplays(bAll))
		{
			if ((pDisplayWnd[1] = (!FindDefaultDisplay(DISPLAY_TYPE_EVENTBOX)) ? new CEventBoxWnd : ((!FindDisplay(DISPLAY_TYPE_EVENTBOX)) ? FindDefaultDisplay(DISPLAY_TYPE_EVENTBOX) : (CEventBoxWnd *)NULL)))
			{
				if ((!IsWindow(pDisplayWnd[1]->GetSafeHwnd()) && QueryDefaultDisplayInfo(&sDisplayInfo)) || (IsWindow(pDisplayWnd[1]->GetSafeHwnd()) && QueryDefaultDisplayInfo(pDisplayWnd[1], &sDisplayInfo)))
				{
					if (AddDisplay(pDisplayWnd[1], STRING(IDS_DISPLAY_TITLE_GLOBALEVENTBOX), &sDisplayInfo, FALSE))
					{
						cProfile.GetDisplayPagePassword(nPage, m_szPassword);
						cProfile.GetDisplayPageUsers(nPage, m_szUsers);
						cProfile.GetDisplayPageFlags(nPage, m_nFlags);
						return((!nDisplays) ? TRUE : FALSE);
					}
				}
				else  delete pDisplayWnd[1];
			}
		}
	}
	if (bAll)
	{
		if (!CheckDisplays(bAll))
		{
			if ((pDisplayWnd[0] = (GetDatabase()->IsInitialized() && !FindDefaultDisplay(DISPLAY_TYPE_OOL)) ? new COOLWnd : ((!FindDisplay(DISPLAY_TYPE_OOL)) ? FindDefaultDisplay(DISPLAY_TYPE_OOL) : (COOLWnd *)NULL)))
			{
				if ((!IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(&sDisplayInfo)) || (IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(pDisplayWnd[0], &sDisplayInfo)))
				{
					if (!AddDisplay(pDisplayWnd[0], STRING(IDS_DISPLAY_TITLE_GLOBALOOL), &sDisplayInfo, FALSE))
					{
						cProfile.GetDisplayPagePassword(nPage, m_szPassword);
						cProfile.GetDisplayPageUsers(nPage, m_szUsers);
						cProfile.GetDisplayPageFlags(nPage, m_nFlags);
						return FALSE;
					}
				}
				else  delete pDisplayWnd[0];
			}
			if ((pDisplayWnd[0] = (GetDatabase()->IsInitialized() && !FindDefaultDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL)) ? new CSatelliteTrackingToolWnd : ((!FindDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL)) ? FindDefaultDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL) : (CSatelliteTrackingToolWnd *)NULL)))
			{
				if ((!IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(&sDisplayInfo)) || (IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(pDisplayWnd[0], &sDisplayInfo)))
				{
					if (!AddDisplay(pDisplayWnd[0], STRING(IDS_DISPLAY_TITLE_SATELLITETRACKINGTOOL), &sDisplayInfo, TRUE))
					{
						cProfile.GetDisplayPagePassword(nPage, m_szPassword);
						cProfile.GetDisplayPageUsers(nPage, m_szUsers);
						cProfile.GetDisplayPageFlags(nPage, m_nFlags);
						return FALSE;
					}
				}
				else  delete pDisplayWnd[0];
			}
			if ((pDisplayWnd[0] = (GetDatabase()->IsInitialized() && !FindDefaultDisplay(DISPLAY_TYPE_TCMANUALSTACK)) ? new CTCManualStackWnd : ((!FindDisplay(DISPLAY_TYPE_TCMANUALSTACK)) ? FindDefaultDisplay(DISPLAY_TYPE_TCMANUALSTACK) : (CTCManualStackWnd *)NULL)))
			{
				if ((!IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(&sDisplayInfo)) || (IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(pDisplayWnd[0], &sDisplayInfo)))
				{
					if (!AddDisplay(pDisplayWnd[0], STRING(IDS_DISPLAY_TITLE_TCMANUALSTACK), &sDisplayInfo, TRUE))
					{
						cProfile.GetDisplayPagePassword(nPage, m_szPassword);
						cProfile.GetDisplayPageUsers(nPage, m_szUsers);
						cProfile.GetDisplayPageFlags(nPage, m_nFlags);
						return FALSE;
					}
				}
				else  delete pDisplayWnd[0];
			}
			if ((pDisplayWnd[0] = (GetDatabase()->IsInitialized() && !FindDefaultDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK)) ? new CTCAutomaticStackWnd : ((!FindDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK)) ? FindDefaultDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK) : (CTCAutomaticStackWnd *)NULL)))
			{
				if ((!IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(&sDisplayInfo)) || (IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(pDisplayWnd[0], &sDisplayInfo)))
				{
					if (!AddDisplay(pDisplayWnd[0], STRING(IDS_DISPLAY_TITLE_TCAUTOMATICSTACK), &sDisplayInfo, TRUE))
					{
						cProfile.GetDisplayPagePassword(nPage, m_szPassword);
						cProfile.GetDisplayPageUsers(nPage, m_szUsers);
						cProfile.GetDisplayPageFlags(nPage, m_nFlags);
						return FALSE;
					}
				}
				else  delete pDisplayWnd[0];
			}
			if ((pDisplayWnd[0] = (GetDatabase()->IsInitialized() && !FindDefaultDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR)) ? new CTCProceduresMonitorWnd : ((!FindDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR)) ? FindDefaultDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR) : (CTCProceduresMonitorWnd *)NULL)))
			{
				if ((!IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(&sDisplayInfo)) || (IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(pDisplayWnd[0], &sDisplayInfo)))
				{
					if (!AddDisplay(pDisplayWnd[0], STRING(IDS_DISPLAY_TITLE_TCPROCEDURESMONITOR), &sDisplayInfo, TRUE))
					{
						cProfile.GetDisplayPagePassword(nPage, m_szPassword);
						cProfile.GetDisplayPageUsers(nPage, m_szUsers);
						cProfile.GetDisplayPageFlags(nPage, m_nFlags);
						return FALSE;
					}
				}
				else  delete pDisplayWnd[0];
			}
			if ((pDisplayWnd[0] = (GetDatabase()->IsInitialized() && !FindDefaultDisplay(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP)) ? new CTCDiagnosticsOversamplingDumpWnd : ((!FindDisplay(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP)) ? FindDefaultDisplay(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP) : (CTCDiagnosticsOversamplingDumpWnd *)NULL)))
			{
				if ((!IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(&sDisplayInfo)) || (IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(pDisplayWnd[0], &sDisplayInfo)))
				{
					if (!AddDisplay(pDisplayWnd[0], STRING(IDS_DISPLAY_TITLE_GLOBALTCDIAGNOSTICSOVERSAMPLINGDUMP), &sDisplayInfo, FALSE))
					{
						cProfile.GetDisplayPagePassword(nPage, m_szPassword);
						cProfile.GetDisplayPageUsers(nPage, m_szUsers);
						cProfile.GetDisplayPageFlags(nPage, m_nFlags);
						return FALSE;
					}
				}
				else  delete pDisplayWnd[0];
			}
			if ((pDisplayWnd[0] = (GetDatabase()->IsInitialized() && !FindDefaultDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES)) ? new CTCOnBoardBufferQueuesWnd : ((!FindDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES)) ? FindDefaultDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES) : (CTCOnBoardBufferQueuesWnd *)NULL)))
			{
				if ((!IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(&sDisplayInfo)) || (IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(pDisplayWnd[0], &sDisplayInfo)))
				{
					if (!AddDisplay(pDisplayWnd[0], STRING(IDS_DISPLAY_TITLE_TCONBOARDBUFFERQUEUES), &sDisplayInfo, TRUE))
					{
						cProfile.GetDisplayPagePassword(nPage, m_szPassword);
						cProfile.GetDisplayPageUsers(nPage, m_szUsers);
						cProfile.GetDisplayPageFlags(nPage, m_nFlags);
						return FALSE;
					}
				}
				else  delete pDisplayWnd[0];
			}
			if ((pDisplayWnd[0] = (GetDatabase()->IsInitialized() && !FindDefaultDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES)) ? new CTCOnBoardMemoryImagesWnd : ((!FindDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES)) ? FindDefaultDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES) : (CTCOnBoardMemoryImagesWnd *)NULL)))
			{
				if ((!IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(&sDisplayInfo)) || (IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(pDisplayWnd[0], &sDisplayInfo)))
				{
					if (!AddDisplay(pDisplayWnd[0], STRING(IDS_DISPLAY_TITLE_TCONBOARDMEMORYIMAGES), &sDisplayInfo, TRUE))
					{
						cProfile.GetDisplayPagePassword(nPage, m_szPassword);
						cProfile.GetDisplayPageUsers(nPage, m_szUsers);
						cProfile.GetDisplayPageFlags(nPage, m_nFlags);
						return FALSE;
					}
				}
				else  delete pDisplayWnd[0];
			}
			if ((pDisplayWnd[0] = (GetDatabase()->IsInitialized() && !FindDefaultDisplay(DISPLAY_TYPE_TCHISTORY)) ? new CTCHistoryWnd : ((!FindDisplay(DISPLAY_TYPE_TCHISTORY)) ? FindDefaultDisplay(DISPLAY_TYPE_TCHISTORY) : (CTCHistoryWnd *)NULL)))
			{
				if ((!IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(&sDisplayInfo)) || (IsWindow(pDisplayWnd[0]->GetSafeHwnd()) && QueryDefaultDisplayInfo(pDisplayWnd[0], &sDisplayInfo)))
				{
					if (!AddDisplay(pDisplayWnd[0], STRING(IDS_DISPLAY_TITLE_GLOBALTCHISTORY), &sDisplayInfo, FALSE))
					{
						cProfile.GetDisplayPagePassword(nPage, m_szPassword);
						cProfile.GetDisplayPageUsers(nPage, m_szUsers);
						cProfile.GetDisplayPageFlags(nPage, m_nFlags);
						return FALSE;
					}
				}
				else  delete pDisplayWnd[0];
			}
		}
		for (EnumDisplays(pDisplays); pDisplays.GetSize() > 0; pDisplays.RemoveAt(0))
		{
			if ((pDisplayWnd[0] = (CDisplayWnd *)pDisplays.GetAt(0)) && !pDisplayWnd[0]->GetLinkByName().IsEmpty())
			{
				if ((hDisplayWnd = FindWindowEx(pDisplayWnd[0]->GetParent()->GetSafeHwnd(), (HWND)NULL, (LPCTSTR)NULL, pDisplayWnd[0]->GetLinkByName())->GetSafeHwnd()))
				{
					if ((pDisplayWnd[1] = (CDisplayWnd *)CWnd::FromHandle(hDisplayWnd)) && pDisplayWnd[1]->IsKindOf(RUNTIME_CLASS(CDisplayWnd)))
					{
						pDisplayWnd[0]->SetLink(pDisplayWnd[1]);
						pDisplayWnd[1]->AddLink(pDisplayWnd[0]);
						continue;
					}
				}
				pDisplayWnd[0]->DestroyWindow();
				nCount--;
			}
		}
	}
	return(((!bAll && ((!nDisplays || nDisplays != nCount || cProfile.GetDisplayPageScrollInfo(nPage, &m_sScrollInfo[0], &m_sScrollInfo[1]) >= 0) && cProfile.GetDisplayPagePassword(nPage, m_szPassword) >= 0 && cProfile.GetDisplayPageUsers(nPage, m_szUsers) >= 0 && cProfile.GetDisplayPageFlags(nPage, m_nFlags) >= 0)) || (bAll && (!IsActivated() || Activate()))) ? ((nDisplays <= nCount) ? TRUE : FALSE) : FALSE);
}

BOOL CDisplayPage::StartDisplays(BOOL bAll)
{
	BOOL  bSuccess;
	POSITION  lPosition;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  *pDisplayInfo;

	for (pDisplayInfo = ((lPosition = m_pDisplays.GetHeadPosition())) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL, bSuccess = TRUE; pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
	{
		if ((pDisplayWnd = (CDisplayWnd *)CWnd::FromHandle(pDisplayInfo->hWnd)) && ((!bAll  &&  pDisplayWnd->GetScope() == DISPLAY_SCOPE_GLOBAL  &&  LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_EVENTBOX) || (bAll && (pDisplayWnd->GetScope() == DISPLAY_SCOPE_LOCAL || LOWORD(pDisplayWnd->GetType()) != DISPLAY_TYPE_EVENTBOX))) && !pDisplayWnd->Start())
		{
			if (pDisplayWnd->GetScope() == DISPLAY_SCOPE_LOCAL)
			{
				pDisplayWnd->DestroyWindow();
				bSuccess = FALSE;
				continue;
			}
			bSuccess = FALSE;
		}
	}
	return bSuccess;
}

BOOL CDisplayPage::StopDisplays(BOOL bAll)
{
	BOOL  bSuccess;
	POSITION  lPosition;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  *pDisplayInfo;

	for (pDisplayInfo = ((lPosition = m_pDisplays.GetHeadPosition())) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL, bSuccess = TRUE; pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
	{
		if ((pDisplayWnd = (CDisplayWnd *)CWnd::FromHandle(pDisplayInfo->hWnd)) && ((!bAll  &&  pDisplayWnd->GetScope() == DISPLAY_SCOPE_GLOBAL  &&  LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_EVENTBOX) || (bAll && (pDisplayWnd->GetScope() == DISPLAY_SCOPE_LOCAL || LOWORD(pDisplayWnd->GetType()) != DISPLAY_TYPE_EVENTBOX))) && !pDisplayWnd->Stop())
		{
			bSuccess = FALSE;
			continue;
		}
	}
	return bSuccess;
}

BOOL CDisplayPage::CheckDisplays(BOOL bAll) CONST
{
	return((!bAll || (FindDisplay(DISPLAY_TYPE_OOL) && FindDisplay(DISPLAY_TYPE_SATELLITETRACKINGTOOL) && FindDisplay(DISPLAY_TYPE_TCMANUALSTACK) && FindDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK) && FindDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR) && FindDisplay(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP) && FindDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES) && FindDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES) && FindDisplay(DISPLAY_TYPE_TCHISTORY))) && FindDisplay(DISPLAY_TYPE_EVENTBOX));
}

UINT CDisplayPage::QueryDisplays() CONST
{
	UINT  nCount;
	POSITION  lPosition;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  *pDisplayInfo;

	for (pDisplayInfo = ((lPosition = m_pDisplays.GetHeadPosition())) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL, nCount = 0; pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
	{
		if ((pDisplayWnd = (CDisplayWnd *)CWnd::FromHandle(pDisplayInfo->hWnd)) && pDisplayWnd->IsWindowVisible())
		{
			nCount++;
			continue;
		}
	}
	return MAKELONG(m_pDisplays.GetCount(), nCount);
}

VOID CDisplayPage::UpdateDisplays()
{
	POSITION  lPosition;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  *pDisplayInfo;

	for (pDisplayInfo = ((lPosition = m_pDisplays.GetHeadPosition())) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL; pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
	{
		if ((pDisplayWnd = (CDisplayWnd *)CWnd::FromHandle(pDisplayInfo->hWnd)))
		{
			pDisplayWnd->Update();
			continue;
		}
	}
}

VOID CDisplayPage::CloseDisplays(BOOL bAll)
{
	POSITION  lPosition;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  *pDisplayInfo;

	for (pDisplayInfo = ((lPosition = m_pDisplays.GetHeadPosition())) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL; pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
	{
		if ((pDisplayWnd = (CDisplayWnd *)CWnd::FromHandle(pDisplayInfo->hWnd)))
		{
			if (pDisplayWnd->GetScope() == DISPLAY_SCOPE_GLOBAL)
			{
				if (IsActivated()) pDisplayWnd->ActivateFrame(SW_HIDE);
				continue;
			}
			if (!pDisplayWnd->IsProtected() || bAll)
			{
				pDisplayWnd->DestroyWindow();
				continue;
			}
		}
	}
}

VOID CDisplayPage::DestroyDisplays(UINT nCode, BOOL bAll)
{
	POSITION  lPosition;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  *pDisplayInfo;

	for (pDisplayInfo = ((lPosition = ((bAll && (nCode == CDesktopApp::ChangeArea || nCode == CDesktopApp::ChangeDatabase || nCode == CDesktopApp::ReloadDatabase || nCode == CDesktopApp::ChangeUser)) || (nCode != CDesktopApp::ChangeArea && nCode != CDesktopApp::ChangeDatabase && nCode != CDesktopApp::ReloadDatabase && nCode != CDesktopApp::ChangeUser && nCode != CDesktopApp::Exit)) ? m_pDisplays.GetHeadPosition() : (POSITION)NULL)) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL; pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
	{
		if ((pDisplayWnd = (CDisplayWnd *)CWnd::FromHandle(pDisplayInfo->hWnd)))
		{
			if (pDisplayWnd->GetScope() == DISPLAY_SCOPE_GLOBAL)
			{
				if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_OOL)
				{
					pDisplayWnd->DestroyWindow();
					continue;
				}
				if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP)
				{
					pDisplayWnd->DestroyWindow();
					continue;
				}
				if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCHISTORY)
				{
					pDisplayWnd->DestroyWindow();
					continue;
				}
				if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_SATELLITETRACKINGTOOL && nCode != CDesktopApp::Exit) continue;
			}
			if (pDisplayWnd->GetScope() == DISPLAY_SCOPE_LOCAL || bAll)
			{
				pDisplayWnd->DestroyWindow();
				continue;
			}
		}
	}
}

BOOL CDisplayPage::InitializeDisplays(CTMEnvironment *pTMEnvironment, BOOL bReset)
{
	INT  nDisplay;
	INT  nDisplays;
	CDisplayWnd  *pDisplayWnd;
	CDisplayLock  cLock(this);

	for (nDisplay = 0, nDisplays = (INT)m_pwndDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pwndDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
		{
			if (pDisplayWnd->GetMode() == DISPLAY_MODE_REALTIME  &&  !bReset)
			{
				pDisplayWnd->Initialize(pTMEnvironment);
				continue;
			}
			if ((LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_AND || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_GRD || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_HEX || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_OOL || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_MMD || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_POD) && bReset)
			{
				if (pDisplayWnd->Initialize(TRUE))
				{
					pDisplayWnd->Reset(pTMEnvironment);
					pDisplayWnd->Initialize(FALSE);
					continue;
				}
			}
			if (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TPEP || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCMANUALSTACK || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCAUTOMATICSTACK || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCPROCEDURESMONITOR || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCONBOARDBUFFERQUEUES || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCONBOARDMEMORYIMAGES || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCHISTORY)
			{
				pDisplayWnd->UpdateBars();
				continue;
			}
		}
	}
	return((nDisplay == nDisplays) ? TRUE : FALSE);
}

BOOL CDisplayPage::UpdateDisplays(CTMEnvironment *pTMEnvironment)
{
	INT  nDisplay;
	INT  nDisplays;
	CDisplayWnd  *pDisplayWnd;
	CDisplayLock  cLock(this);

	for (nDisplay = 0, nDisplays = (INT)m_pwndDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pwndDisplays.GetAt(nDisplay)) != (CDisplayWnd *)NULL)
		{
			for (pDisplayWnd->Lock(), pTMEnvironment->Lock(); pDisplayWnd->IsInitialized() && pDisplayWnd->GetMode() == DISPLAY_MODE_REALTIME && (LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_AND || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_GRD || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_HEX || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_OOL || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_MMD || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_POD || LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP) && !pDisplayWnd->GetLink(); )
			{
				pDisplayWnd->Update(pTMEnvironment->GetTMUnit()->GetTimeTag().GetTimeInSeconds(), pTMEnvironment);
				break;
			}
			pTMEnvironment->Unlock();
			pDisplayWnd->Unlock();
		}
	}
	return TRUE;
}

INT CDisplayPage::EnumDisplays(CPtrArray &pDisplays, BOOL bOrder) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  nDisplay;
	INT  nDisplays;
	POSITION  lPosition;
	CUIntArray  nPositions;
	CDisplayWnd  *pDisplayWnd;
	DISPLAYINFO  *pDisplayInfo;
	CDisplayLock  cLock(this);

	for (pDisplayInfo = ((lPosition = m_pDisplays.GetHeadPosition())) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL, pDisplays.RemoveAll(); pDisplayInfo; pDisplayInfo = (lPosition) ? (PDISPLAYINFO)m_pDisplays.GetNext(lPosition) : (PDISPLAYINFO)NULL)
	{
		for (nDisplay = 0, nDisplays = (INT)m_pwndDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)m_pwndDisplays.GetAt(nDisplay)))
			{
				if (pDisplayWnd->GetSafeHwnd() == pDisplayInfo->hWnd)
				{
					for (nIndex = (!bOrder) ? (INT)nPositions.GetSize() : 0, nCount = (INT)nPositions.GetSize(); nIndex < nCount; nIndex++)
					{
						if (pDisplayInfo->nOrder < (INT)nPositions.GetAt(nIndex)) break;
						continue;
					}
					pDisplays.InsertAt(nIndex, pDisplayWnd, 1);
					nPositions.InsertAt(nIndex, pDisplayInfo->nOrder);
					break;
				}
			}
		}
	}
	return((INT)pDisplays.GetSize());
}

BOOL CDisplayPage::SetPassword(LPCTSTR pszPassword)
{
	m_szPassword = pszPassword;
	return TRUE;
}

BOOL CDisplayPage::GetPassword(CString &szPassword) CONST
{
	szPassword = m_szPassword;
	return TRUE;
}

BOOL CDisplayPage::SetUsers(CONST CStringArray &szUsers)
{
	m_szUsers.Copy(szUsers);
	return TRUE;
}

INT CDisplayPage::GetUsers(CStringArray &szUsers) CONST
{
	szUsers.Copy(m_szUsers);
	return((INT)szUsers.GetSize());
}

BOOL CDisplayPage::SetBehavior(UINT nFlags)
{
	m_nFlags = nFlags;
	return TRUE;
}

BOOL CDisplayPage::GetBehavior(UINT &nFlags) CONST
{
	nFlags = m_nFlags;
	return TRUE;
}

INT CDisplayPage::IsAlerted() CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CDisplayWnd  *pDisplayWnd;
	CDisplayLock  cLock(this);

	for (nDisplay = 0, nDisplays = (INT)m_pwndDisplays.GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pwndDisplays.GetAt(nDisplay)) && pDisplayWnd->GetScope() == DISPLAY_SCOPE_LOCAL  &&  pDisplayWnd->IsAlerted()) break;
		continue;
	}
	return((nDisplay < nDisplays) ? TRUE : FALSE);
}

CDisplayWnd *CDisplayPage::FindDefaultDisplay(UINT nType) CONST
{
	CDisplayWnd  *pDisplayWnd;

	for (pDisplayWnd = (CDisplayWnd *)GetMainWnd()->GetDisplayFrame()->GetWindow(GW_CHILD); pDisplayWnd; pDisplayWnd = (CDisplayWnd *)pDisplayWnd->GetNextWindow())
	{
		if ((pDisplayWnd->GetExStyle() & WS_EX_MDICHILD) && LOWORD(pDisplayWnd->GetType()) == nType  &&  pDisplayWnd->GetScope() == DISPLAY_SCOPE_GLOBAL) break;
		continue;
	}
	return pDisplayWnd;
}

BOOL CDisplayPage::QueryDefaultDisplayInfo(PDISPLAYINFO pDisplayInfo) CONST
{
	SetRect(&pDisplayInfo->rWnd, GetSystemMetrics(SM_CXFRAME), GetSystemMetrics(SM_CYFRAME), (3 * GetSystemMetrics(SM_CXSCREEN)) / 4, GetSystemMetrics(SM_CYSCREEN) / 2);
	pDisplayInfo->ptWnd.x = pDisplayInfo->ptWnd.y = 0;
	pDisplayInfo->nScope = DISPLAY_SCOPE_GLOBAL;
	pDisplayInfo->nMode = DISPLAY_MODE_REALTIME;
	pDisplayInfo->nNumber = (INT)m_pDisplays.GetCount();
	pDisplayInfo->nOrder = (INT)m_pDisplays.GetCount();
	pDisplayInfo->pData = (LPVOID)NULL;
	pDisplayInfo->nShow = SW_SHOWNORMAL;
	pDisplayInfo->bShow = TRUE;
	return TRUE;
}

BOOL CDisplayPage::QueryDefaultDisplayInfo(CDisplayWnd *pDisplayWnd, PDISPLAYINFO pDisplayInfo) CONST
{
	WINDOWPLACEMENT  sDisplayPlacement = { sizeof(WINDOWPLACEMENT) };

	if (pDisplayWnd->GetWindowPlacement(&sDisplayPlacement))
	{
		CopyMemory(&pDisplayInfo->rWnd, &sDisplayPlacement.rcNormalPosition, sizeof(RECT));
		CopyMemory(&pDisplayInfo->ptWnd, &sDisplayPlacement.ptMinPosition, sizeof(POINT));
		pDisplayInfo->hWnd = pDisplayWnd->GetSafeHwnd();
		pDisplayInfo->nScope = pDisplayWnd->GetScope();
		pDisplayInfo->nMode = pDisplayWnd->GetMode();
		pDisplayInfo->nNumber = (INT)m_pDisplays.GetCount();
		pDisplayInfo->nOrder = (INT)m_pDisplays.GetCount();
		pDisplayInfo->pData = (LPVOID)NULL;
		pDisplayInfo->nShow = LOWORD(pDisplayWnd->GetState());
		pDisplayInfo->bShow = pDisplayWnd->IsWindowVisible();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayPage::IsActivated() CONST
{
	return((GetParent()->GetWindow(GW_CHILD) == (CWnd *) this) ? TRUE : FALSE);
}

BOOL CDisplayPage::Lock()
{
	return(GetDisplayArea()->Lock() && GetLock()->Lock());
}

BOOL CDisplayPage::Unlock()
{
	return(GetLock()->Unlock() && GetDisplayArea()->Unlock());
}

BEGIN_MESSAGE_MAP(CDisplayPage, CWnd)
	//{{AFX_MSG_MAP(CDisplayPage)
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayPage message handlers

BOOL CDisplayPage::OnEraseBkgnd(CDC *pDC)
{
	CRect  rDisplayPage;

	GetClientRect(rDisplayPage);
	pDC->DrawEdge(rDisplayPage, EDGE_SUNKEN, BF_RECT);
	pDC->ExcludeClipRect(rDisplayPage.left, rDisplayPage.top, rDisplayPage.left + GetSystemMetrics(SM_CXEDGE), rDisplayPage.bottom);
	pDC->ExcludeClipRect(rDisplayPage.left, rDisplayPage.top, rDisplayPage.right, rDisplayPage.top + GetSystemMetrics(SM_CYEDGE));
	pDC->ExcludeClipRect(rDisplayPage.right - GetSystemMetrics(SM_CXEDGE), rDisplayPage.top, rDisplayPage.right, rDisplayPage.bottom);
	pDC->ExcludeClipRect(rDisplayPage.left, rDisplayPage.bottom - GetSystemMetrics(SM_CYEDGE), rDisplayPage.right, rDisplayPage.bottom);
	return CWnd::OnEraseBkgnd(pDC);
}

void CDisplayPage::OnDestroy()
{
	m_pDisplays.RemoveAll();
	m_pwndDisplays.RemoveAll();
	m_szUsers.RemoveAll();
	CWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayFolderAlertThread

IMPLEMENT_DYNCREATE(CDisplayFolderAlertThread, CThread)

BOOL CDisplayFolderAlertThread::Start(CDisplayFolder *pFolder)
{
	return CreateThread(pFolder);
}

BOOL CDisplayFolderAlertThread::Stop()
{
	return((DestroyThread(FALSE) >= 0) ? TRUE : FALSE);
}

int CDisplayFolderAlertThread::Run()
{
	BOOL  bStatus;
	CDisplayFolder  *pDisplayFolder = (CDisplayFolder *)GetThreadInfo();

	for (bStatus = TRUE; Wait(DISPLAYFOLDER_ALERT_INTERVAL) == WAIT_TIMEOUT; bStatus = !bStatus)
	{
		pDisplayFolder->UpdateLamps(bStatus);
		continue;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CDisplayFolderAlertThread, CThread)
	//{{AFX_MSG_MAP(CDisplayFolderAlertThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayFolderAlertThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CDisplayFolder

IMPLEMENT_DYNCREATE(CDisplayFolder, CTabCtrl)

CDisplayFolder::CDisplayFolder() : CTabCtrl(), CDisplayLockable()
{
	m_nPage = -1;
}

BOOL CDisplayFolder::Create(CWnd *pParentWnd, CBasePane *pBar)
{
	INT  nPage;
	INT  nPages;
	CString  szPage;
	CProfile  cProfile;

	for (m_pPanesBar = pBar; CTabCtrl::Create(TCS_TABS | TCS_SINGLELINE | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(0, 0, 0, 0), pParentWnd, 0); )
	{
		for (nPage = 0, nPages = (cProfile.GetDisplayAreaPageCount(nPages)) ? nPages : 0; nPage < nPages || !nPage; nPage++)
		{
			if (!cProfile.GetDisplayPageTitle(nPage, szPage)) szPage.Format(STRING(IDS_DISPLAYFOLDER_TITLE), nPage + 1);
			if (AddPage(szPage, nPage)) continue;
			break;
		}
		if (nPage == nPages || !nPages)
		{
			if (ActivatePage((cProfile.GetDisplayAreaActivePage(nPage)) ? nPage : 0, FALSE) && m_cAlertThread.Start(this))
			{
				UpdateLamps(TRUE);
				return TRUE;
			}
		}
		DestroyWindow();
		break;
	}
	return FALSE;
}

BOOL CDisplayFolder::AddPage(LPCTSTR pszTitle, INT nPage)
{
	CRect  rPage;
	TC_ITEM  sPage;
	CDisplayPage  *pPage;
	CDisplayLock  cLock(this);

	sPage.iImage = 1;
	sPage.mask = TCIF_TEXT;
	sPage.mask |= TCIF_IMAGE;
	m_szPages.InsertAt(nPage, pszTitle);
	sPage.pszText = (LPTSTR)(LPCTSTR)m_szPages[nPage];
	sPage.cchTextMax = lstrlen(pszTitle) + 1;
	if (InsertItem(nPage, &sPage) >= 0)
	{
		if ((pPage = new CDisplayPage))
		{
			if (pPage->Create(this))
			{
				RecalcLayout(rPage);
				m_pwndPages.InsertAt(nPage, pPage, 1);
				m_nPageMode.InsertAt(nPage, IDP_ALARMLAMPOFF);
				SetActivePage((GetActivePage() >= nPage) ? (GetActivePage() + 1) : GetActivePage());
				pPage->SetWindowText(pszTitle);
				pPage->MoveWindow(rPage);
				pPage->Initialize();
				pPage->Invalidate();
				pPage->UpdateWindow();
				RepositionLamps();
				return TRUE;
			}
			delete pPage;
		}
	}
	return FALSE;
}

BOOL CDisplayFolder::ModifyPage(LPCTSTR pszTitle, INT nPage)
{
	TC_ITEM  sPage;
	CDisplayPage  *pPage;
	CDisplayLock  cLock(this);

	if ((pPage = GetPage(nPage)))
	{
		for (m_szPages.SetAt(nPage, pszTitle), sPage.mask = TCIF_TEXT, sPage.pszText = (LPTSTR)(LPCTSTR)m_szPages[nPage], sPage.cchTextMax = lstrlen(pszTitle) + 1; SetItem(nPage, &sPage); )
		{
			pPage->SetWindowText(pszTitle);
			pPage->Invalidate(TRUE);
			pPage->UpdateWindow();
			RepositionLamps();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CDisplayFolder::ActivatePage(INT nPage, BOOL bQuery)
{
	INT  nIndex[3];
	CDisplayPage  *pPage;

	if ((nIndex[0] = (nPage < 0) ? (abs(nPage) - 1) : nPage) != (nIndex[1] = GetActivePage()) && CheckPage(nIndex[0]))
	{
		if ((pPage = GetPage(((nIndex[2] = GetMainWnd()->GetDisplayFrame()->IsWindowVisible())) ? GetActivePage() : -1))) pPage->Deactivate();
		if ((pPage = GetPage(nIndex[0])) && SetActivePage(nIndex[0]) && (nPage < 0 || !bQuery || AccessPage(nIndex[0]) == IDOK))
		{
			pPage->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			pPage->Activate();
			return TRUE;
		}
		if ((pPage = GetPage(nIndex[1])) && nIndex[2] != 0)
		{
			SetActivePage(nIndex[1]);
			pPage->Activate();
		}
		return FALSE;
	}
	if (nIndex[0] != nIndex[1])
	{
		ReportEvent(USER_INFORMATIONAL_ACCESS_VIOLATION);
		return FALSE;
	}
	return TRUE;
}

BOOL CDisplayFolder::RemovePage(INT nPage)
{
	CDisplayPage  *pPage;
	CDisplayLock  cLock(this);

	if ((pPage = GetPage(nPage)))
	{
		if (GetActivePage() != nPage || ActivatePage((!nPage) ? (nPage + 1) : 0, FALSE))
		{
			pPage->CloseDisplays(TRUE);
			pPage->DestroyWindow();
			m_nPageMode.RemoveAt(nPage);
			m_pwndPages.RemoveAt(nPage);
			m_nPage = (m_nPage >= nPage) ? (m_nPage - 1) : m_nPage;
			DeleteItem(nPage);
			RepositionLamps();
			delete pPage;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CDisplayFolder::SetActivePage(INT nPage)
{
	if (nPage < m_pwndPages.GetSize())
	{
		SetCurSel((m_nPage = nPage));
		return TRUE;
	}
	return FALSE;
}

INT CDisplayFolder::GetActivePage() CONST
{
	return m_nPage;
}

INT CDisplayFolder::GetPageCount() CONST
{
	return((INT)m_pwndPages.GetSize());
}

INT CDisplayFolder::EnumPages(CPtrArray &pwndPages) CONST
{
	pwndPages.Copy(m_pwndPages);
	return((INT)pwndPages.GetSize());
}
INT CDisplayFolder::EnumPages(CStringArray &szPages) CONST
{
	INT  nPage;
	INT  nPages;
	CString  szPage;
	CDisplayPage  *pPage;

	for (nPage = 0, nPages = GetPageCount(), szPages.RemoveAll(); nPage < nPages; nPage++)
	{
		if ((pPage = GetPage(nPage)) != (CDisplayPage *)NULL)
		{
			pPage->GetWindowText(szPage);
			szPages.Add(szPage);
			continue;
		}
		break;
	}
	return((nPages == szPages.GetSize()) ? nPages : -1);
}

BOOL CDisplayFolder::AddDisplay(CDisplayWnd *pDisplayWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	return AddDisplay(GetActivePage(), pDisplayWnd, pszTitle, pDefaultInfo, bDefault);
}
BOOL CDisplayFolder::AddDisplay(INT nPage, CDisplayWnd *pDisplayWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(nPage))) ? pPage->AddDisplay(pDisplayWnd, pszTitle, pDefaultInfo, bDefault) : FALSE);
}

BOOL CDisplayFolder::RemoveDisplay(CDisplayWnd *pDisplayWnd)
{
	INT  nPage;
	INT  nPages;
	BOOL  bPage;
	CDisplayPage  *pPage;

	for (nPage = 0, nPages = GetPageCount(), bPage = FALSE; nPage < nPages; nPage++)
	{
		bPage |= ((pPage = GetPage(nPage))) ? pPage->RemoveDisplay(pDisplayWnd) : FALSE;
		continue;
	}
	return bPage;
}
BOOL CDisplayFolder::RemoveDisplay(INT nPage, CDisplayWnd *pDisplayWnd)
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(nPage))) ? pPage->RemoveDisplay(pDisplayWnd) : FALSE);
}

BOOL CDisplayFolder::ActivateDisplay(CDisplayWnd *pDisplayWnd)
{
	INT  nPage;
	INT  nPages;
	INT  nDisplay;
	INT  nDisplays;
	CPtrArray  pDisplays;
	CDisplayPage  *pPage;

	for (nPage = (pDisplayWnd->GetScope() == DISPLAY_SCOPE_GLOBAL) ? GetActivePage() : 0, nPages = GetPageCount(); nPage < nPages; nPage++)
	{
		for (nDisplay = 0, nDisplays = EnumDisplays(nPage, pDisplays); nDisplay < nDisplays; nDisplay++)
		{
			if (pDisplayWnd != (CDisplayWnd *)pDisplays.GetAt(nDisplay)) continue;
			break;
		}
		if (nDisplay < nDisplays) break;
	}
	return(((pPage = (nPage < nPages) ? GetPage(nPage) : (CDisplayPage *)NULL)) ? ((pPage != GetPage(GetActivePage())) ? (ActivatePage(nPage) && pPage->ActivateDisplay(pDisplayWnd)) : pPage->ActivateDisplay(pDisplayWnd)) : FALSE);
}
BOOL CDisplayFolder::ActivateDisplay(BOOL bNext)
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(GetActivePage()))) ? pPage->ActivateDisplay(bNext) : FALSE);
}
BOOL CDisplayFolder::ActivateDisplay(UINT nID)
{
	INT  nPage;
	INT  nPages;
	INT  nCount[2];
	CPtrArray  pDisplays;
	CDisplayPage  *pPage;

	for (nPage = 0, nPages = GetPageCount(), nCount[0] = 0; nPage < nPages; nPage++)
	{
		if ((nCount[1] = EnumDisplays(nPage, pDisplays, TRUE)) + nCount[0] >(INT) nID) break;
		nCount[0] += nCount[1];
	}
	return(((pPage = (nPage < nPages) ? GetPage(nPage) : (CDisplayPage *)NULL)) ? ((pPage != GetPage(GetActivePage())) ? (ActivatePage(nPage) && pPage->ActivateDisplay(nID - nCount[0])) : pPage->ActivateDisplay(nID - nCount[0])) : FALSE);
}

BOOL CDisplayFolder::IsActiveDisplay(UINT nID) CONST
{
	INT  nPage;
	INT  nPages;
	INT  nCount[2];
	CPtrArray  pDisplays;
	CDisplayPage  *pPage;

	for (nPage = 0, nPages = GetPageCount(), nCount[0] = 0; nPage < nPages; nPage++)
	{
		if ((nCount[1] = EnumDisplays(nPage, pDisplays, TRUE)) + nCount[0] >(INT) nID) break;
		nCount[0] += nCount[1];
	}
	return(((pPage = (nPage < nPages) ? GetPage(nPage) : (CDisplayPage *)NULL)) ? ((pPage == GetPage(GetActivePage())) ? pPage->IsActiveDisplay(nID - nCount[0]) : FALSE) : FALSE);
}

CDisplayWnd *CDisplayFolder::GetActiveDisplay() CONST
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(GetActivePage()))) ? pPage->GetActiveDisplay() : (CDisplayWnd *)NULL);
}

CDisplayWnd *CDisplayFolder::FindDisplay(INT nType) CONST
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(GetActivePage()))) ? pPage->FindDisplay(nType) : (CDisplayWnd *)NULL);
}

BOOL CDisplayFolder::CloseDisplay()
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(GetActivePage()))) ? pPage->CloseDisplay() : FALSE);
}

BOOL CDisplayFolder::SaveDisplays(BOOL bAll)
{
	INT  nPage;
	INT  nPages;
	INT  nCount;
	BOOL  bPages;
	CString  szPage;
	CDisplayPage  *pPage;
	CProfile  cProfile;

	for (nPage = 0, nPages = GetPageCount(), nCount = 0, bPages = TRUE; nPage < nPages; nPage++)
	{
		if ((pPage = GetPage(nPage)))
		{
			pPage->GetWindowText(szPage);
			if (cProfile.SetDisplayPageTitle(nCount, szPage))
			{
				bPages &= pPage->SaveDisplays(bAll, nCount, (100 * nPage) / nPages, (100 * (nPage + 1)) / nPages);
				nCount++;
				continue;
			}
		}
		cProfile.DeleteDisplayPageInfo(nCount);
		bPages = FALSE;
	}
	for (nPage = nCount, nPages = (cProfile.GetDisplayAreaPageCount(nPages)) ? nPages : -1; nPage < nPages; nPage++)
	{
		cProfile.DeleteDisplayPageInfo(nPage);
		continue;
	}
	if (!cProfile.SetDisplayAreaPageCount(nCount) || !cProfile.SetDisplayAreaActivePage((nCount > GetActivePage()) ? GetActivePage() : 0))
	{
		cProfile.SetDisplayAreaActivePage();
		cProfile.SetDisplayAreaPageCount();
		return FALSE;
	}
	return bPages;
}

BOOL CDisplayFolder::LoadDisplays(BOOL bAll)
{
	INT  nPage;
	INT  nPages;
	CString  szPage;
	CDisplayPage  *pPage;

	for (nPage = nPages = 0; nPage < GetPageCount(); nPage++)
	{
		if ((pPage = GetPage(nPage)) && pPage->LoadDisplays(bAll, nPage, (100 * nPage) / GetPageCount(), (100 * (nPage + 1)) / GetPageCount()))
		{
			nPages++;
			continue;
		}
	}
	for (nPage = (bAll || (CheckPage(GetActivePage()) && AccessPage(GetActivePage()) == IDOK)) ? nPages : 0; nPage < nPages; nPage++)
	{
		if (nPage != GetActivePage() && CheckPage(nPage) && AccessPage(nPage) == IDOK)
		{
			ActivatePage(nPage, FALSE);
			break;
		}
		if (nPage == nPages - 1)
		{
			szPage.Format(STRING(IDS_DISPLAYFOLDER_TITLE), nPages);
			if (AddPage(szPage, nPages))
			{
				SetActivePage(nPages);
				nPages++;
				break;
			}
		}
	}
	return((nPages == GetPageCount()) ? TRUE : FALSE);
}

BOOL CDisplayFolder::StartDisplays(BOOL bAll)
{
	INT  nPage;
	INT  nPages;
	INT  nCount;
	CDisplayPage  *pPage;

	for (nPage = nPages = 0, nCount = GetPageCount(); nPage < nCount; nPage++)
	{
		if ((pPage = (CDisplayPage *)GetPage(nPage)) != (CDisplayPage *)NULL)
		{
			nPages = (pPage->StartDisplays(bAll)) ? (nPages + 1) : nPages;
			continue;
		}
	}
	return((nPages == nCount) ? TRUE : FALSE);
}

BOOL CDisplayFolder::StopDisplays(BOOL bAll)
{
	INT  nPage;
	INT  nPages;
	INT  nCount;
	CDisplayPage  *pPage;

	for (nPage = nPages = 0, nCount = GetPageCount(); nPage < nCount; nPage++)
	{
		if ((pPage = (CDisplayPage *)GetPage(nPage)) != (CDisplayPage *)NULL)
		{
			nPages = (pPage->StopDisplays(bAll)) ? (nPages + 1) : nPages;
			continue;
		}
	}
	return((nPages == nCount) ? TRUE : FALSE);
}

BOOL CDisplayFolder::CheckDisplays(BOOL bAll) CONST
{
	INT  nPage;
	INT  nPages;
	CDisplayPage  *pPage;

	for (nPage = 0, nPages = GetPageCount(); nPage < nPages; nPage++)
	{
		if ((pPage = GetPage(nPage)) && pPage->CheckDisplays(bAll)) continue;
		break;
	}
	return((nPage == nPages) ? TRUE : FALSE);
}

UINT CDisplayFolder::QueryDisplays() CONST
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(GetActivePage()))) ? pPage->QueryDisplays() : 0);
}

VOID CDisplayFolder::UpdateDisplays()
{
	INT  nPage;
	INT  nPages;
	CDisplayPage  *pPage;

	for (nPage = 0, nPages = GetPageCount(); nPage < nPages; nPage++)
	{
		if ((pPage = GetPage(nPage)))
		{
			pPage->UpdateDisplays();
			continue;
		}
	}
}

VOID CDisplayFolder::CloseDisplays()
{
	CDisplayPage  *pPage;

	if ((pPage = GetPage(GetActivePage())))
	{
		pPage->CloseDisplays();
		return;
	}
}

VOID CDisplayFolder::DestroyDisplays(UINT nCode, BOOL bAll)
{
	INT  nPage;
	INT  nPages;
	CDisplayPage  *pPage;

	for (nPage = 0, nPages = GetPageCount(); nPage <= nPages; nPage++)
	{
		if ((pPage = (nPage < nPages  &&  nPage != GetActivePage()) ? GetPage(nPage) : ((nPage == nPages) ? GetPage(GetActivePage()) : (CDisplayPage *)NULL)))
		{
			pPage->DestroyDisplays(nCode, bAll);
			continue;
		}
	}
}

BOOL CDisplayFolder::InitializeDisplays(CTMEnvironment *pTMEnvironment, BOOL bReset)
{
	INT  nPage;
	INT  nPages;
	CDisplayPage  *pPage;
	CDisplayLock  cLock(this);

	for (nPage = 0, nPages = GetPageCount(); nPage < nPages; nPage++)
	{
		if ((pPage = GetPage(nPage)) && !pPage->InitializeDisplays(pTMEnvironment, bReset)) break;
		continue;
	}
	return((nPage == nPages) ? TRUE : FALSE);
}

BOOL CDisplayFolder::UpdateDisplays(CTMEnvironment *pTMEnvironment)
{
	INT  nPage;
	INT  nPages;
	CDisplayPage  *pPage;
	CDisplayLock  cLock(this);

	for (nPage = 0, nPages = GetPageCount(); nPage < nPages; nPage++)
	{
		if ((pPage = GetPage(nPage)) != (CDisplayPage *)NULL)
		{
			pPage->UpdateDisplays(pTMEnvironment);
			continue;
		}
	}
	return TRUE;
}

INT CDisplayFolder::EnumDisplays(CPtrArray &pDisplays, BOOL bOrder) CONST
{
	return EnumDisplays(GetActivePage(), pDisplays, bOrder);
}
INT CDisplayFolder::EnumDisplays(INT nPage, CPtrArray &pDisplays, BOOL bOrder) CONST
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(nPage))) ? pPage->EnumDisplays(pDisplays, bOrder) : -1);
}

BOOL CDisplayFolder::SetPassword(LPCTSTR pszPassword)
{
	return SetPassword(GetActivePage(), pszPassword);
}
BOOL CDisplayFolder::SetPassword(INT nPage, LPCTSTR pszPassword)
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(nPage))) ? pPage->SetPassword(pszPassword) : FALSE);
}

BOOL CDisplayFolder::GetPassword(CString &szPassword) CONST
{
	return GetPassword(GetActivePage(), szPassword);
}
BOOL CDisplayFolder::GetPassword(INT nPage, CString &szPassword) CONST
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(nPage))) ? pPage->GetPassword(szPassword) : FALSE);
}

BOOL CDisplayFolder::SetUsers(CONST CStringArray &szUsers)
{
	return SetUsers(GetActivePage(), szUsers);
}
BOOL CDisplayFolder::SetUsers(INT nPage, CONST CStringArray &szUsers)
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(nPage))) ? pPage->SetUsers(szUsers) : FALSE);
}

INT CDisplayFolder::GetUsers(CStringArray &szUsers) CONST
{
	return GetUsers(GetActivePage(), szUsers);
}
INT CDisplayFolder::GetUsers(INT nPage, CStringArray &szUsers) CONST
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(nPage))) ? pPage->GetUsers(szUsers) : -1);
}

BOOL CDisplayFolder::SetBehavior(UINT nFlags)
{
	return SetBehavior(GetActivePage(), nFlags);
}
BOOL CDisplayFolder::SetBehavior(INT nPage, UINT nFlags)
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(nPage))) ? pPage->SetBehavior(nFlags) : FALSE);
}

BOOL CDisplayFolder::GetBehavior(UINT &nFlags) CONST
{
	return GetBehavior(GetActivePage(), nFlags);
}
BOOL CDisplayFolder::GetBehavior(INT nPage, UINT &nFlags) CONST
{
	CDisplayPage  *pPage;

	return(((pPage = GetPage(nPage))) ? pPage->GetBehavior(nFlags) : FALSE);
}

VOID CDisplayFolder::UpdateLamps(BOOL bStatus)
{
	CDC  *pDC;
	INT  nPage;
	INT  nPages;
	CDisplayPage  *pPage;
	CDisplayLock  cLock(this);

	if ((pDC = GetDC()))
	{
		for (nPage = 0, nPages = GetPageCount(); nPage < nPages; nPage++)
		{
			if ((pPage = GetPage(nPage)) != (CDisplayPage *)NULL)
			{
				m_nPageMode.SetAt(nPage, (pPage->IsAlerted() > 0) ? ((bStatus) ? IDP_ALARMLAMPON : IDP_ALARMLAMP) : IDP_ALARMLAMPOFF);
				DrawLamp(pDC, nPage);
			}
		}
		ReleaseDC(pDC);
	}
}

VOID CDisplayFolder::RecalcLayout(LPRECT lpRect)
{
	CRect  rPage;
	CRect  rFolder;
	CDisplayLock  cLock(this);

	for (GetClientRect(rFolder), SetRectEmpty(lpRect); GetItemRect(0, &rPage); )
	{
		SetRect(lpRect, rFolder.left + GetSystemMetrics(SM_CXFRAME), rFolder.top + rPage.Height() + GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYEDGE), rFolder.right - GetSystemMetrics(SM_CXFRAME), rFolder.bottom - GetSystemMetrics(SM_CYFRAME));
		break;
	}
	RepositionLamps();
}

CDisplayPage *CDisplayFolder::GetPage(INT nPage) CONST
{
	return((nPage >= 0 && nPage < GetPageCount()) ? (CDisplayPage *)m_pwndPages.GetAt(nPage) : (CDisplayPage *)NULL);
}

INT CDisplayFolder::AccessPage(INT nPage)
{
	INT  nAccess;
	CString  szFacility;
	CString  szPassword;
	CStringArray  szPages;
	CAccountToken  cAccountToken;
	CPasswordDialog  cPasswordDialog;

	for (GetAccount(&cAccountToken); GetPassword(nPage, szPassword); )
	{
		szFacility.Format(STRING(IDS_PASSWORDDIALOG_DISPLAYPAGE), (nPage < EnumPages(szPages)) ? (LPCTSTR)szPages.GetAt(nPage) : EMPTYSTRING);
		nAccess = ((szPassword = (szPassword == CString(EOL)) ? cAccountToken.GetPassword() : szPassword).IsEmpty() || cPasswordDialog.DoModal(szFacility, szPassword) == IDOK) ? IDOK : IDCANCEL;
		break;
	}
	for (RestoreWaitCursor(); !szPassword.IsEmpty(); )
	{
		GetMainWnd()->UpdateStatusBar();
		break;
	}
	return nAccess;
}

BOOL CDisplayFolder::CheckPage(INT nPage) CONST
{
	INT  nUser;
	INT  nUsers;
	CStringArray  szUsers;

	for (nUser = 0, nUsers = GetUsers(nPage, szUsers); nUser < nUsers; nUser++)
	{
		if (szUsers.GetAt(nUser) == GetAccountUserName()) break;
		continue;
	}
	return((nUser < nUsers || !nUsers) ? TRUE : FALSE);
}

VOID CDisplayFolder::DrawLamps(CDC *pDC)
{
	INT  nPage;
	INT  nPages;

	for (nPage = 0, nPages = (m_nPageMode.GetSize() == GetPageCount()) ? GetPageCount() : 0; nPage < nPages; nPage++)
	{
		DrawLamp(pDC, nPage);
		continue;
	}
}

VOID CDisplayFolder::DrawLamp(CDC *pDC, INT nPage)
{
	LPRECT  prLamp;

	if ((prLamp = (nPage < m_prLamps.GetSize()) ? (LPRECT)m_prLamps.GetAt(nPage) : (LPRECT)NULL))
	{
		m_cLamps[m_nPageMode.GetAt(nPage) - FIRSTALARMLAMPID].Draw(pDC->GetSafeHdc(), prLamp->left, (GetActivePage() != nPage) ? (prLamp->top + 1) : (prLamp->top - 1));
		return;
	}
}

VOID CDisplayFolder::RepositionLamps()
{
	INT  nLamp;
	INT  nLamps;
	CPoint  ptLamp;
	LPRECT  prLamp;

	for (nLamp = GetPageCount(), nLamps = (INT)m_prLamps.GetSize(); nLamp < nLamps; nLamp++)
	{
		if ((prLamp = (LPRECT)m_prLamps.GetAt(nLamp))) delete prLamp;
		continue;
	}
	for (nLamp = 0, nLamps = GetPageCount(), ptLamp = RecalcLamps(); nLamp < nLamps; nLamp++)
	{
		if ((prLamp = (nLamp < m_prLamps.GetSize()) ? (LPRECT)m_prLamps.GetAt(nLamp) : new RECT))
		{
			if (GetItemRect(nLamp, prLamp))
			{
				prLamp->left += ptLamp.x;
				prLamp->top = (prLamp->top + prLamp->bottom) / 2 - m_cLamps[0].GetHeight() / 2 - 1;
				prLamp->right = prLamp->left + m_cLamps[0].GetWidth();
				prLamp->bottom = prLamp->top + m_cLamps[0].GetHeight();
				m_prLamps.SetAtGrow(nLamp, prLamp);
				continue;
			}
			SetRect(prLamp, 0, 0, 0, 0);
			m_prLamps.SetAtGrow(nLamp, prLamp);
		}
	}
	m_prLamps.SetSize(GetPageCount());
}

CPoint CDisplayFolder::RecalcLamps()
{
	CPoint  ptLamp;
	LOGFONT  lfFont;

	if (m_cTabFont.GetLogFont(&lfFont) > 0)
	{
		ptLamp.x = ptLamp.y = max(lfFont.lfHeight / 3, m_cLamps[0].GetHeight() / 3);
		return ptLamp;
	}
	return CPoint(0, 0);
}

BOOL CDisplayFolder::LoadLamps()
{
	INT  nLamp[2];
	INT  nLamps[2];
	ULONG  cbSymbol;
	HRSRC  hResource;
	LPVOID  pResource;
	HMODULE  hModule;
	HGLOBAL  hMemResource[2];
	LPSTREAM  pIStream;

	for (nLamp[0] = 0, nLamps[0] = sizeof(m_cLamps) / sizeof(m_cLamps[0]); nLamp[0] < nLamps[0]; nLamp[0]++)
	{
		if ((hResource = FindResource((hModule = GetModuleHandle((LPCTSTR)NULL)), MAKEINTRESOURCE(FIRSTALARMLAMPID + nLamp[0]), STRING(IDS_RESOURCETYPE_PICTURE))))
		{
			if ((hMemResource[0] = LoadResource(hModule, hResource)))
			{
				if ((pResource = LockResource(hMemResource[0])))
				{
					if ((hMemResource[1] = GlobalAlloc(GMEM_MOVEABLE, 0)))
					{
						if (SUCCEEDED(CreateStreamOnHGlobal(hMemResource[1], TRUE, &pIStream)))
						{
							if (SUCCEEDED(pIStream->Write(pResource, SizeofResource(hModule, hResource), &cbSymbol)) && SUCCEEDED(m_cLamps[nLamp[0]].Load(pIStream)))
							{
								pIStream->Release();
								continue;
							}
							pIStream->Release();
						}
					}
				}
			}
		}
		break;
	}
	if (nLamp[0] == nLamps[0])
	{
		if (m_pPageLamps.Create(m_cLamps[0].GetWidth(), m_cLamps[0].GetHeight(), ILC_COLOR32, 0, 1))
		{
			for (nLamp[1] = 0, nLamps[1] = nLamps[0]; nLamp[1] < nLamps[1]; nLamp[1] = nLamp[1] + 1)
			{
				if (ImageList_Add(m_pPageLamps, m_cLamps[nLamp[1]], (HBITMAP)NULL) < 0) break;
				continue;
			}
			if (nLamp[1] == nLamps[1])
			{
				SetImageList(&m_pPageLamps);
				return TRUE;
			}
			m_pPageLamps.DeleteImageList();
		}
	}
	return FALSE;
}

VOID CDisplayFolder::FreeLamps()
{
	INT  nLamp;
	INT  nLamps;

	for (nLamp = 0, nLamps = sizeof(m_cLamps) / sizeof(m_cLamps[0]); nLamp < nLamps; nLamp++)
	{
		m_cLamps[nLamp].Destroy();
		continue;
	}
	m_pPageLamps.DeleteImageList();
}

BOOL CDisplayFolder::Lock()
{
	return(GetDisplayArea()->Lock() && GetLock()->Lock());
}

BOOL CDisplayFolder::Unlock()
{
	return(GetLock()->Unlock() && GetDisplayArea()->Unlock());
}

void CDisplayFolder::PostNcDestroy()
{
	INT  nPage;
	INT  nPages;
	LPRECT  prLamp;

	for (nPage = 0, nPages = GetPageCount(), FreeLamps(); nPage < nPages; nPage++)
	{
		if ((prLamp = (LPRECT)m_prLamps.GetAt(nPage))) delete prLamp;
		delete GetPage(nPage);
	}
	m_prLamps.RemoveAll();
	m_szPages.RemoveAll();
	m_pwndPages.RemoveAll();
	m_nPageMode.RemoveAll();
	CTabCtrl::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDisplayFolder, CTabCtrl)
	//{{AFX_MSG_MAP(CDisplayFolder)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_HSCROLL()
	ON_WM_DESTROY()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayFolder message handlers

int CDisplayFolder::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFontTools  cFontTools(&m_cTabFont);

	if (CTabCtrl::OnCreate(lpCreateStruct) != -1 && LoadLamps())
	{
		SetFont(&m_cTabFont);
		return 0;
	}
	return -1;
}

void CDisplayFolder::OnSize(UINT nType, int cx, int cy)
{
	INT  nPage;
	INT  nPages;
	CRect  rPage;
	CDisplayPage  *pPage;
	CDisplayLock  cLock(this);

	for (nPage = 0, nPages = GetPageCount(), RecalcLayout(rPage); nPage < nPages; nPage++)
	{
		if ((pPage = GetPage(nPage)))
		{
			pPage->MoveWindow(rPage);
			continue;
		}
	}
	CTabCtrl::OnSize(nType, cx, cy);
}

void CDisplayFolder::OnPaint()
{
	CDC  *pDC;
	CRect  rFolder;
	CRect  rPage[3];
	CDisplayLock  cLock(this);

	for (GetClientRect(rFolder), GetItemRect(0, rPage[0]), GetItemRect(GetCurSel(), rPage[1]), GetItemRect(GetItemCount() - 1, rPage[2]), rPage[0].InflateRect((!GetCurSel()) ? GetSystemMetrics(SM_CXEDGE) : 0, 0, 0, 0), rPage[1].InflateRect(0, GetSystemMetrics(SM_CYEDGE)), rPage[2].DeflateRect(0, 0, (GetCurSel() != GetItemCount() - 1) ? GetSystemMetrics(SM_CXEDGE) : 0, 0), rFolder.SetRect((GetCurSel() == GetItemCount() - 1) ? (GetSystemMetrics(SM_CXEDGE) + rPage[2].right) : rPage[2].right, rFolder.top, rFolder.right, rPage[2].bottom), ValidateRect(rFolder), CTabCtrl::OnPaint(); (pDC = GetDC()); )
	{
		for (DrawLamps(pDC), pDC->ExcludeClipRect(rPage[0].left, rPage[0].top, rPage[2].right, rPage[2].bottom), pDC->ExcludeClipRect(rPage[1].left, rPage[1].top, rPage[1].right, rPage[1].bottom); !rFolder.IsRectEmpty(); )
		{
			CMFCVisualManager::GetInstance()->OnFillBarBackground(pDC, m_pPanesBar, rFolder, rFolder);
			break;
		}
		ReleaseDC(pDC);
		break;
	}
}

UINT CDisplayFolder::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void CDisplayFolder::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	INT  nTab;

	if ((nChar == VK_LEFT  &&  GetActivePage() > 0) || (nChar == VK_RIGHT  &&  GetActivePage() < GetPageCount() - 1))
	{
		if (!CheckPage((nTab = (nChar == VK_RIGHT) ? (GetActivePage() + 1) : (GetActivePage() - 1))))
		{
			ReportEvent(USER_INFORMATIONAL_ACCESS_VIOLATION);
			return;
		}
		ActivatePage(nTab);
		return;
	}
	CTabCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDisplayFolder::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CDisplayWnd  *pDisplayWnd;

	if ((pDisplayWnd = (CDisplayWnd *)GetMainWnd()->MDIGetActive()) && pDisplayWnd->IsWindowVisible() && nChar == VK_TAB  &&  !HIBYTE(GetKeyState(VK_SHIFT)))
	{
		pDisplayWnd->SetFocus();
		return;
	}
	CTabCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CDisplayFolder::OnLButtonDown(UINT nFlags, CPoint point)
{
	INT  nTab;
	INT  nTabs;
	CRect  rTab;

	for (nTab = 0, nTabs = GetItemCount(); nTab < nTabs; nTab++)
	{
		GetItemRect(nTab, rTab);
		if (rTab.PtInRect(point)) break;
	}
	if (nTab < nTabs)
	{
		if (!CheckPage(nTab))
		{
			ReportEvent(USER_INFORMATIONAL_ACCESS_VIOLATION);
			return;
		}
		ActivatePage(nTab);
		SetFocus();
		return;
	}
	CTabCtrl::OnLButtonDown(nFlags, point);
}

void CDisplayFolder::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar)
{
	INT  nTab;
	INT  nTabs;
	CRect  rTab;
	CRect  rFolder;

	if (GetItemCount() > 0)
	{
		GetClientRect(rFolder);
		for (nTab = 0, nTabs = GetItemCount(); nTab < nTabs; nTab++)
		{
			GetItemRect(nTab, rTab);
			if (rTab.left >= 0) break;
		}
		InvalidateRect(CRect(rFolder.left, rFolder.top, rTab.left - 1, rTab.bottom), TRUE);
		InvalidateRect(CRect(rTab.left, rFolder.top, rFolder.right, rTab.bottom), FALSE);
		UpdateWindow();
	}
	CTabCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

LRESULT CDisplayFolder::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	INT  nPage;
	INT  nPages;
	CRect  rPage;
	CFont  cFont;
	LOGFONT  lfFont;
	LRESULT  lResult;
	CDisplayPage  *pPage;
	CDisplayLock  cLock(this);

	for (lResult = Default(); wParam != (WPARAM)NULL; )
	{
		if (m_cTabFont.GetSafeHandle() != (HANDLE)wParam)
		{
			if (GetObject((HGDIOBJ)wParam, sizeof(LOGFONT), &lfFont) > 0 && cFont.CreateFontIndirect(&lfFont))
			{
				m_cTabFont.DeleteObject();
				m_cTabFont.Attach(cFont.Detach());
			}
		}
		SetPadding(CSize(RecalcLamps().x, RecalcLamps().y));
		SetImageList(&m_pPageLamps);
		Invalidate(FALSE);
		UpdateWindow();
		break;
	}
	for (RecalcLayout(rPage), ClientToScreen(rPage), GetMainWnd()->ScreenToClient(rPage); !rPage.IsRectEmpty(); )
	{
		GetMainWnd()->GetDisplayFrame()->MoveWindow(rPage);
		break;
	}
	for (nPage = 0, nPages = GetPageCount(), RecalcLayout(rPage); nPage < nPages; nPage++)
	{
		if ((pPage = GetPage(nPage)))
		{
			pPage->MoveWindow(rPage);
			continue;
		}
	}
	return lResult;
}

void CDisplayFolder::OnDestroy()
{
	m_cAlertThread.Stop();
	m_cTabFont.DeleteObject();
	CTabCtrl::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayArea

IMPLEMENT_DYNCREATE(CDisplayArea, CWnd)

CDisplayArea::CDisplayArea() : CWnd(), CDisplayLockable()
{
	m_nType = (UINT)-1;
	m_rFrame.SetRectEmpty();
	m_bFrame = FALSE;
}

BOOL CDisplayArea::Create(CWnd *pParentWnd, CBasePane *pBar)
{
	UINT  nType;
	CProfile  cProfile;

	if (GetType() == DISPLAYAREA_TYPE_STANDARD || GetType() == DISPLAYAREA_TYPE_FOLDER)
	{
		for (m_pPanesBar = pBar, nType = (cProfile.GetDisplayAreaType(nType)) ? nType : DISPLAYAREA_TYPE_STANDARD; (nType == DISPLAYAREA_TYPE_STANDARD && m_wndPage.Create(this)) || (nType == DISPLAYAREA_TYPE_FOLDER && m_wndFolder.Create(this, pBar)); )
		{
			SetType(nType);
			RecalcLayout();
			RedrawWindow();
			return TRUE;
		}
		return FALSE;
	}
	for (m_pPanesBar = pBar; CWnd::Create(AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW), GetSysColorBrush(COLOR_3DFACE)), (LPCTSTR)NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(0, 0, 0, 0), pParentWnd, 0); )
	{
		RecalcLayout();
		RedrawWindow();
		return TRUE;
	}
	return FALSE;
}

VOID CDisplayArea::SetType(UINT nType)
{
	m_nType = nType;
}

UINT CDisplayArea::GetType() CONST
{
	return m_nType;
}

BOOL CDisplayArea::AddPage(LPCTSTR pszTitle, INT nPage)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.AddPage(pszTitle, nPage)) ? TRUE : FALSE);
}

BOOL CDisplayArea::ModifyPage(LPCTSTR pszTitle, INT nPage)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.ModifyPage(pszTitle, nPage)) ? TRUE : FALSE);
}

BOOL CDisplayArea::ActivatePage(INT nPage)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.ActivatePage(nPage)) ? TRUE : FALSE);
}

BOOL CDisplayArea::RemovePage(INT nPage)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.RemovePage(nPage)) ? TRUE : FALSE);
}

INT CDisplayArea::GetActivePage() CONST
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.GetActivePage() : 0);
}

INT CDisplayArea::GetPageCount() CONST
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.GetPageCount() : 0);
}

INT CDisplayArea::EnumPages(CStringArray &szPages) CONST
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.EnumPages(szPages) : -1);
}

BOOL CDisplayArea::AddDisplay(CDisplayWnd *pDisplayWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.AddDisplay(pDisplayWnd, pszTitle, pDefaultInfo, bDefault)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.AddDisplay(pDisplayWnd, pszTitle, pDefaultInfo, bDefault))) ? TRUE : FALSE);
}
BOOL CDisplayArea::AddDisplay(INT nPage, CDisplayWnd *pDisplayWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.AddDisplay(nPage, pDisplayWnd, pszTitle, pDefaultInfo, bDefault)) ? TRUE : FALSE);
}

BOOL CDisplayArea::RemoveDisplay(CDisplayWnd *pDisplayWnd)
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.RemoveDisplay(pDisplayWnd)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.RemoveDisplay(pDisplayWnd))) ? TRUE : FALSE);
}
BOOL CDisplayArea::RemoveDisplay(INT nPage, CDisplayWnd *pDisplayWnd)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.RemoveDisplay(nPage, pDisplayWnd)) ? TRUE : FALSE);
}

BOOL CDisplayArea::ActivateDisplay(CDisplayWnd *pDisplayWnd)
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.ActivateDisplay(pDisplayWnd)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.ActivateDisplay(pDisplayWnd))) ? TRUE : FALSE);
}
BOOL CDisplayArea::ActivateDisplay(BOOL bNext)
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.ActivateDisplay(bNext)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.ActivateDisplay(bNext))) ? TRUE : FALSE);
}
BOOL CDisplayArea::ActivateDisplay(UINT nID)
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.ActivateDisplay(nID)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.ActivateDisplay(nID))) ? TRUE : FALSE);
}

BOOL CDisplayArea::IsActiveDisplay(UINT nID) CONST
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.IsActiveDisplay(nID)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.IsActiveDisplay(nID))) ? TRUE : FALSE);
}

CDisplayWnd *CDisplayArea::GetActiveDisplay() CONST
{
	return((GetType() == DISPLAYAREA_TYPE_STANDARD) ? m_wndPage.GetActiveDisplay() : ((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.GetActiveDisplay() : (CDisplayWnd *)NULL));
}

CDisplayWnd *CDisplayArea::FindDisplay(INT nType) CONST
{
	return((GetType() == DISPLAYAREA_TYPE_STANDARD) ? m_wndPage.FindDisplay(nType) : ((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.FindDisplay(nType) : (CDisplayWnd *)NULL));
}

BOOL CDisplayArea::CloseDisplay()
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.CloseDisplay()) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.CloseDisplay())) ? TRUE : FALSE);
}

BOOL CDisplayArea::SaveDisplays(BOOL bAll)
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.SaveDisplays(bAll)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.SaveDisplays(bAll))) ? TRUE : FALSE);
}

BOOL CDisplayArea::LoadDisplays(BOOL bAll)
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.LoadDisplays(bAll)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.LoadDisplays(bAll))) ? TRUE : FALSE);
}

BOOL CDisplayArea::StartDisplays(BOOL bAll)
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.StartDisplays(bAll)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.StartDisplays(bAll))) ? TRUE : FALSE);
}

BOOL CDisplayArea::StopDisplays(BOOL bAll)
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.StopDisplays(bAll)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.StopDisplays(bAll))) ? TRUE : FALSE);
}

BOOL CDisplayArea::CheckDisplays(BOOL bAll) CONST
{
	return(((GetType() == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.CheckDisplays(bAll)) || (GetType() == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.CheckDisplays(bAll))) ? TRUE : FALSE);
}

UINT CDisplayArea::QueryDisplays() CONST
{
	return((GetType() == DISPLAYAREA_TYPE_STANDARD) ? m_wndPage.QueryDisplays() : ((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.QueryDisplays() : 0));
}

VOID CDisplayArea::UpdateDisplays()
{
	switch (GetType())
	{
	case DISPLAYAREA_TYPE_STANDARD:
	{ m_wndPage.UpdateDisplays();
	break;
	}
	case DISPLAYAREA_TYPE_FOLDER:
	{ m_wndFolder.UpdateDisplays();
	break;
	}
	}
}

VOID CDisplayArea::CloseDisplays()
{
	switch (GetType())
	{
	case DISPLAYAREA_TYPE_STANDARD:
	{ m_wndPage.CloseDisplays();
	break;
	}
	case DISPLAYAREA_TYPE_FOLDER:
	{ m_wndFolder.CloseDisplays();
	break;
	}
	}
}

VOID CDisplayArea::DestroyDisplays(UINT nCode, BOOL bAll)
{
	switch (GetType())
	{
	case DISPLAYAREA_TYPE_STANDARD:
	{ if (nCode != CDesktopApp::Exit) GetMainWnd()->GetDisplayFrame()->Close();
	m_wndPage.DestroyDisplays(nCode, bAll);
	break;
	}
	case DISPLAYAREA_TYPE_FOLDER:
	{ if (nCode != CDesktopApp::Exit) GetMainWnd()->GetDisplayFrame()->Close();
	m_wndFolder.DestroyDisplays(nCode, bAll);
	break;
	}
	}
	if ((nCode == CDesktopApp::ChangeArea || nCode == CDesktopApp::ChangeDatabase || nCode == CDesktopApp::ReloadDatabase || nCode == CDesktopApp::ChangeUser) && bAll)
	{
		for (m_bFrame = TRUE; GetType() == DISPLAYAREA_TYPE_STANDARD; )
		{
			m_wndPage.DestroyWindow();
			break;
		}
		for (; GetType() == DISPLAYAREA_TYPE_FOLDER; )
		{
			m_wndFolder.DestroyWindow();
			break;
		}
		m_bFrame = FALSE;
	}
}

BOOL CDisplayArea::InitializeDisplays(CTMEnvironment *pTMEnvironment, BOOL bReset)
{
	switch (GetType())
	{
	case DISPLAYAREA_TYPE_STANDARD: return m_wndPage.InitializeDisplays(pTMEnvironment, bReset);
	case DISPLAYAREA_TYPE_FOLDER: return m_wndFolder.InitializeDisplays(pTMEnvironment, bReset);
	}
	return FALSE;
}

BOOL CDisplayArea::UpdateDisplays(CTMEnvironment *pTMEnvironment)
{
	switch (GetType())
	{
	case DISPLAYAREA_TYPE_STANDARD:
	{ m_wndPage.UpdateDisplays(pTMEnvironment);
	return TRUE;
	}
	case DISPLAYAREA_TYPE_FOLDER:
	{ m_wndFolder.UpdateDisplays(pTMEnvironment);
	return TRUE;
	}
	}
	return FALSE;
}

INT CDisplayArea::EnumDisplays(CPtrArray &pDisplays, BOOL bOrder) CONST
{
	return((GetType() == DISPLAYAREA_TYPE_STANDARD) ? m_wndPage.EnumDisplays(pDisplays, bOrder) : ((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.EnumDisplays(pDisplays, bOrder) : -1));
}
INT CDisplayArea::EnumDisplays(INT nPage, CPtrArray &pDisplays, BOOL bOrder) CONST
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.EnumDisplays(nPage, pDisplays, bOrder) : -1);
}

BOOL CDisplayArea::SetPassword(LPCTSTR pszPassword)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.SetPassword(pszPassword) : FALSE);
}
BOOL CDisplayArea::SetPassword(INT nPage, LPCTSTR pszPassword)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.SetPassword(nPage, pszPassword) : FALSE);
}

BOOL CDisplayArea::GetPassword(CString &szPassword) CONST
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.GetPassword(szPassword) : FALSE);
}
BOOL CDisplayArea::GetPassword(INT nPage, CString &szPassword) CONST
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.GetPassword(nPage, szPassword) : FALSE);
}

BOOL CDisplayArea::SetUsers(CONST CStringArray &szUsers)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.SetUsers(szUsers) : FALSE);
}
BOOL CDisplayArea::SetUsers(INT nPage, CONST CStringArray &szUsers)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.SetUsers(nPage, szUsers) : FALSE);
}

INT CDisplayArea::GetUsers(CStringArray &szUsers) CONST
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.GetUsers(szUsers) : -1);
}
INT CDisplayArea::GetUsers(INT nPage, CStringArray &szUsers) CONST
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.GetUsers(nPage, szUsers) : -1);
}

BOOL CDisplayArea::SetBehavior(UINT nFlags)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.SetBehavior(nFlags) : FALSE);
}
BOOL CDisplayArea::SetBehavior(INT nPage, UINT nFlags)
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.SetBehavior(nPage, nFlags) : FALSE);
}

BOOL CDisplayArea::GetBehavior(UINT &nFlags) CONST
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.GetBehavior(nFlags) : FALSE);
}
BOOL CDisplayArea::GetBehavior(INT nPage, UINT &nFlags) CONST
{
	return((GetType() == DISPLAYAREA_TYPE_FOLDER) ? m_wndFolder.GetBehavior(nPage, nFlags) : FALSE);
}

VOID CDisplayArea::RecalcLayout(LPRECT pRect)
{
	CWnd  *pWnd;
	CRect  rWnd;
	CRect  rDisplayArea;
	CRect  rDisplayFrame;

	if (GetType() == DISPLAYAREA_TYPE_STANDARD || GetType() == DISPLAYAREA_TYPE_FOLDER)
	{
		for (pWnd = GetParent()->GetWindow(GW_CHILD), GetParent()->GetClientRect(rDisplayArea); pWnd != (CWnd *)NULL; pWnd = pWnd->GetNextWindow())
		{
			if (pWnd != GetDisplayFrame() && pWnd != GetDisplayArea())
			{
				pWnd->GetWindowRect(rWnd);
				GetParent()->ScreenToClient(rWnd);
				rWnd.left = rDisplayArea.left;
				rWnd.right = rDisplayArea.right;
				rDisplayArea.SubtractRect(rDisplayArea, rWnd);
			}
		}
		if (!pRect)
		{
			for (MoveWindow(rDisplayArea); GetType() == DISPLAYAREA_TYPE_STANDARD; )
			{
				m_wndPage.MoveWindow(0, 0, rDisplayArea.Width(), rDisplayArea.Height());
				return;
			}
			if (GetType() == DISPLAYAREA_TYPE_FOLDER)
			{
				m_wndFolder.MoveWindow(GetSystemMetrics(SM_CXFRAME), GetSystemMetrics(SM_CYFRAME), rDisplayArea.Width() - 2 * GetSystemMetrics(SM_CXFRAME), rDisplayArea.Height() - 2 * GetSystemMetrics(SM_CYFRAME));
				return;
			}
		}
	}
	if (GetType() == DISPLAYAREA_TYPE_STANDARD)
	{
		SetRect(pRect, rDisplayArea.left, rDisplayArea.top, rDisplayArea.right, rDisplayArea.bottom);
		return;
	}
	if (GetType() == DISPLAYAREA_TYPE_FOLDER)
	{
		for (RecalcLayout(), m_wndFolder.RecalcLayout(m_rFrame), rDisplayFrame = m_rFrame, m_wndFolder.ClientToScreen(rDisplayFrame), GetParent()->ScreenToClient(rDisplayFrame); rDisplayFrame.Width() >= 0 && rDisplayFrame.Height() >= 0; )
		{
			SetRect(pRect, rDisplayFrame.left, rDisplayFrame.top, rDisplayFrame.right, rDisplayFrame.bottom);
			return;
		}
	}
	m_rFrame.SetRectEmpty();
	SetRect(pRect, 0, 0, 0, 0);
}

BOOL CDisplayArea::Lock()
{
	return GetLock()->Lock();
}

BOOL CDisplayArea::Unlock()
{
	return GetLock()->Unlock();
}

BEGIN_MESSAGE_MAP(CDisplayArea, CWnd)
	//{{AFX_MSG_MAP(CDisplayArea)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_NCDESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayArea message handlers

int CDisplayArea::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	UINT  nType;
	CProfile  cProfile;

	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (nType = DISPLAYAREA_TYPE_STANDARD; cProfile.GetDisplayAreaType(nType); )
		{
			if ((nType == DISPLAYAREA_TYPE_STANDARD  &&  m_wndPage.Create(this)) || (nType == DISPLAYAREA_TYPE_FOLDER  &&  m_wndFolder.Create(this, m_pPanesBar)))
			{
				SetType(nType);
				return 0;
			}
			break;
		}
		if (m_wndPage.Create(this))
		{
			SetType(DISPLAYAREA_TYPE_STANDARD);
			return 0;
		}
	}
	return -1;
}

void CDisplayArea::OnSize(UINT nType, int cx, int cy)
{
	CRect  rDisplayFrame;

	CWnd::OnSize(nType, cx, cy);
	RecalcLayout(rDisplayFrame);
	GetDisplayFrame()->MoveWindow(rDisplayFrame);
}

BOOL CDisplayArea::OnEraseBkgnd(CDC *pDC)
{
	CRect  rDisplayArea;

	for (GetClientRect(rDisplayArea), pDC->ExcludeClipRect(m_rFrame); !m_bFrame; )
	{
		CMFCVisualManager::GetInstance()->OnFillBarBackground(pDC, m_pPanesBar, rDisplayArea, rDisplayArea);
		break;
	}
	return TRUE;
}

void CDisplayArea::OnSetFocus(CWnd *pOldWnd)
{
	if (GetType() == DISPLAYAREA_TYPE_FOLDER)
	{
		if (IsWindow(m_wndFolder.GetSafeHwnd()))
		{
			m_wndFolder.SetFocus();
			return;
		}
	}
	CWnd::OnSetFocus(pOldWnd);
}

BOOL CDisplayArea::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	LPNMHDR  pNotifyInfo = (LPNMHDR)lParam;

	return((GetType() != DISPLAYAREA_TYPE_FOLDER || (GetType() == DISPLAYAREA_TYPE_FOLDER && (pNotifyInfo->code != TCN_SELCHANGE || (pNotifyInfo->code == TCN_SELCHANGE  &&  m_wndFolder.ActivatePage(m_wndFolder.GetCurSel()))))) ? CWnd::OnNotify(wParam, lParam, pResult) : TRUE);
}

void CDisplayArea::OnNcDestroy()
{
	CDisplayFrame  *pDisplayFrame;

	if ((pDisplayFrame = GetMainWnd()->GetDisplayFrame()))
	{
		pDisplayFrame->SetScrollRange(SB_HORZ, 0, 0);
		pDisplayFrame->SetScrollRange(SB_VERT, 0, 0);
	}
	CWnd::OnNcDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayFrame

IMPLEMENT_DYNCREATE(CDisplayFrame, CMDIClientAreaWnd)

BOOL CDisplayFrame::Create(CMainWnd *pParentWnd)
{
	return SubclassWindow(pParentWnd->m_hWndMDIClient);
}

VOID CDisplayFrame::Destroy(CMainWnd *pParentWnd)
{
	pParentWnd->m_hWndMDIClient = (HWND)NULL;
	UnsubclassWindow();
}

BOOL CDisplayFrame::BeginPage(BOOL bPage)
{
	if (bPage  &&  GetParent()->IsWindowVisible())
	{
		ShowWindow(SW_HIDE);
		BeginWaitCursor();
		return TRUE;
	}
	return FALSE;
}

BOOL CDisplayFrame::EndPage(BOOL bPage)
{
	if (bPage  &&  GetParent()->IsWindowVisible() && !IsWindowVisible())
	{
		ShowWindow(SW_SHOWNORMAL);
		EndWaitCursor();
		return TRUE;
	}
	return FALSE;
}

VOID CDisplayFrame::RecalcBars()
{
	CWnd  *pWnd;
	CRect  rDisplayFrame;

	for (pWnd = GetWindow(GW_CHILD); pWnd; pWnd = pWnd->GetNextWindow())
	{
		if ((pWnd->GetExStyle() & WS_EX_MDICHILD) && pWnd->IsZoomed()) break;
		continue;
	}
	if (!pWnd)
	{
		GetWindowRect(rDisplayFrame);
		GetParent()->ScreenToClient(rDisplayFrame);
		MoveWindow(rDisplayFrame);
	}
}

VOID CDisplayFrame::Close()
{
	ShowWindow(SW_HIDE);
}

BEGIN_MESSAGE_MAP(CDisplayFrame, CMDIClientAreaWnd)
	//{{AFX_MSG_MAP(CDisplayFrame)
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisplayFrame message handlers

void CDisplayFrame::OnWindowPosChanging(LPWINDOWPOS lpwndpos)
{
	CRect  rDisplayArea;
	CDisplayArea  *pDisplayArea;

	if ((pDisplayArea = GetDisplayArea()))
	{
		for (pDisplayArea->RecalcLayout(rDisplayArea); !rDisplayArea.IsRectEmpty(); )
		{
			lpwndpos->x = rDisplayArea.left;
			lpwndpos->y = rDisplayArea.top;
			lpwndpos->cx = rDisplayArea.Width();
			lpwndpos->cy = rDisplayArea.Height();
			break;
		}
		lpwndpos->flags |= (rDisplayArea.IsRectEmpty()) ? (SWP_NOMOVE | SWP_NOSIZE) : 0;
	}
	CMDIClientAreaWnd::OnWindowPosChanging(lpwndpos);
}

void CDisplayFrame::OnSetFocus(CWnd *pOldWnd)
{
	CDisplayArea  *pDisplayArea;

	if ((pDisplayArea = GetDisplayArea()) && pDisplayArea->GetType() == DISPLAYAREA_TYPE_FOLDER)
	{
		pDisplayArea->SetFocus();
		return;
	}
	CMDIClientAreaWnd::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayLock

CDisplayLock::CDisplayLock(CONST CDisplayArea *pDisplayArea)
{
	if ((m_pLockable = (CDisplayLockable *)pDisplayArea))
	{
		m_pLockable->Lock();
		return;
	}
}
CDisplayLock::CDisplayLock(CONST CDisplayFolder *pDisplayFolder)
{
	if ((m_pLockable = (CDisplayLockable *)pDisplayFolder))
	{
		m_pLockable->Lock();
		return;
	}
}
CDisplayLock::CDisplayLock(CONST CDisplayPage *pDisplayPage)
{
	if ((m_pLockable = (CDisplayLockable *)pDisplayPage))
	{
		m_pLockable->Lock();
		return;
	}
}
CDisplayLock::CDisplayLock(CONST CDisplayWnd *pDisplayWnd)
{
	if ((m_pLockable = (CDisplayLockable *)pDisplayWnd))
	{
		m_pLockable->Lock();
		return;
	}
}
CDisplayLock::CDisplayLock(CONST CDisplayToolBar *pDisplayToolBar)
{
	if ((m_pLockable = (CDisplayLockable *)pDisplayToolBar))
	{
		m_pLockable->Lock();
		return;
	}
}
CDisplayLock::CDisplayLock(CONST CDisplayStatusBar *pDisplayStatusBar)
{
	if ((m_pLockable = (CDisplayLockable *)pDisplayStatusBar))
	{
		m_pLockable->Lock();
		return;
	}
}
CDisplayLock::CDisplayLock(CONST CDisplayToolTip *pDisplayToolTip)
{
	if ((m_pLockable = (CDisplayLockable *)pDisplayToolTip))
	{
		m_pLockable->Lock();
		return;
	}
}
CDisplayLock::CDisplayLock(CONST CDisplayLockable *pDisplayLockable)
{
	if ((m_pLockable = (CDisplayLockable *)pDisplayLockable))
	{
		m_pLockable->Lock();
		return;
	}
}

CDisplayLock::~CDisplayLock()
{
	if (m_pLockable != (CDisplayLockable *)NULL)
	{
		m_pLockable->Unlock();
		return;
	}
}

BOOL CDisplayLock::Release()
{
	if (m_pLockable != (CDisplayLockable *)NULL)
	{
		m_pLockable->Unlock();
		m_pLockable = (CDisplayLockable *)NULL;
		return TRUE;
	}
	return FALSE;
}
