// AND.CPP : Alphanumeric Display Form Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the alphanumeric
// display form related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2003/10/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nStatusBarIndicators[] =
{
	ID_AND_STATUSBAR_DETAILSPANE,
	ID_AND_STATUSBAR_FLAGPANE,
	ID_AND_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CANDSaveDialog dialog

IMPLEMENT_DYNCREATE(CANDSaveDialog, CDisplayDialog)

CANDSaveDialog::CANDSaveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CANDSaveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CANDSaveDialog::Create(CWnd *pParentWnd, CString &szFileName)
{
	INT  nResult;

	for (szFileName.Empty(); (nResult = CDisplayDialog::Create(pParentWnd, CANDSaveDialog::IDD)) == IDOK; )
	{
		szFileName = m_szFileName;
		break;
	}
	return nResult;
}

BOOL CANDSaveDialog::Initialize()
{
	m_pLayouts.Copy(GetDatabase()->GetANDs());
	m_szFileName.Empty();
	return TRUE;
}

CANDWnd *CANDSaveDialog::GetParentDisplay() CONST
{
	return((CANDWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CANDSaveDialog::EnumANDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	CString  szItem;
	CStringTools  cStringTools;
	CANDLayout  *pLayout;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(), nDigits = 0; nLayout < nLayouts; nLayout++)
	{
		nDigits = ((pLayout = m_pLayouts.GetAt(nLayout))) ? max(pLayout->GetName().GetLength(), nDigits) : nDigits;
		continue;
	}
	for (nLayout = 0; nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = m_pLayouts.GetAt(nLayout)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDSAVEDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pLayout->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pLayout->GetTitle();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDSAVEDIALOG_DIRECTORYTITLEITEM_LOCATION); )
				{
					szItem = pLayout->GetFileName();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_AND_SAVE_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_AND_SAVE_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_AND_SAVE_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_SAVE_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_SAVE_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_AND_SAVE_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CANDSaveDialog::FindAND(LPCTSTR pszName) CONST
{
	INT  nLayout;
	INT  nLayouts;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(); nLayout < nLayouts; nLayout++)
	{
		if (m_pLayouts.GetAt(nLayout)->GetName() == pszName) break;
		continue;
	}
	return((nLayout < nLayouts) ? TRUE : FALSE);
}

BOOL CANDSaveDialog::CheckFileName(LPCTSTR pszFileName) CONST
{
	INT  nLayout;
	INT  nLayouts;
	CANDLayout  *pLayout;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = m_pLayouts.GetAt(nLayout)) && !pLayout->GetFileName().CompareNoCase(pszFileName)) break;
		continue;
	}
	return((nLayout == nLayouts) ? TRUE : FALSE);
}

BOOL CANDSaveDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_AND_SAVE_FILENAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CANDSaveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDSaveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDSaveDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDSaveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CANDSaveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_SAVE_FILENAME_BROWSE, OnBrowseFileName)
	ON_BN_CLICKED(IDC_AND_SAVE_HELP, OnHelp)
	ON_EN_CHANGE(IDC_AND_SAVE_FILENAME, OnEditchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDSaveDialog message handlers

BOOL CANDSaveDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_AND_SAVE_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_ANDSAVEDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_ANDSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_ANDSAVEDIALOG_DIRECTORYTITLEITEM_LOCATION));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_AND_SAVE_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT), rColumns.DeflateRect(0, 0, GetSystemMetrics(SM_CXVSCROLL), 0); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_AND_SAVE_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_ANDSAVEDIALOG_DIRECTORYTITLEITEM_NAME)) ? (rColumns.Width() / 4) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_ANDSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION)) ? (rColumns.Width() / 2) : (3 * rColumns.Width()) / 4));
		continue;
	}
	EnumANDs();
	GetDlgItem(IDC_AND_SAVE_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_AND_SAVE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_AND_SAVE_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_SAVE_DATABASE)->EnableWindow();
	GetDlgItem(IDC_AND_SAVE_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_SAVE_FILENAME)->EnableWindow();
	GetDlgItem(IDC_AND_SAVE_FILENAME_BROWSE)->EnableWindow();
	GetDlgItem(IDC_AND_SAVE_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return FALSE;
}

BOOL CANDSaveDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nColumn;
	INT  nColumns;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_AND_SAVE_DIRECTORY)
	{
		if (pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK)
		{
			for (nColumn = 0, nColumns = (pNotifyListView->iItem >= 0) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
			{
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_ANDSAVEDIALOG_DIRECTORYTITLEITEM_LOCATION)) break;
				continue;
			}
			if (pNotifyListView->iItem < 0)
			{
				Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
				SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
				return TRUE;
			}
			GetDlgItem(IDC_AND_SAVE_FILENAME)->SetWindowText(Listview_GetText(GetDlgItem(IDC_AND_SAVE_DIRECTORY), pNotifyListView->iItem, nColumn));
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CANDSaveDialog::OnBrowseFileName()
{
	BOOL  bFileName;
	CString  szFileName;
	CFileBrowseDialog  *pFileBrowseDialog;

	if ((pFileBrowseDialog = new CFileBrowseDialog(this, szFileName, STRING(IDS_FILEBROWSEDIALOG_DATABASEXMLFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEXMLFILTER))) && pFileBrowseDialog->DoModal() == IDOK)
	{
		GetDlgItem(IDC_AND_SAVE_FILENAME)->SetWindowText((szFileName = pFileBrowseDialog->GetPathName()));
		GetDlgItem(IDC_AND_SAVE_COMMENT_STATIC)->ShowWindow(((bFileName = !CheckFileName(szFileName))) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_AND_SAVE_COMMENT)->ShowWindow((bFileName) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_AND_SAVE_COMMENT_STATIC)->EnableWindow(bFileName);
		GetDlgItem(IDC_AND_SAVE_COMMENT)->EnableWindow(bFileName);
	}
	delete pFileBrowseDialog;
	SendDlgItemMessage(IDC_AND_SAVE_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_AND_SAVE_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSaveDialog::OnEditchangeFileName()
{
	BOOL  bFileName;
	CString  szFileName;

	GetDlgItem(IDC_AND_SAVE_FILENAME)->GetWindowText(szFileName);
	GetDlgItem(IDC_AND_SAVE_COMMENT_STATIC)->ShowWindow(((bFileName = !CheckFileName(szFileName))) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_AND_SAVE_COMMENT)->ShowWindow((bFileName) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_AND_SAVE_COMMENT_STATIC)->EnableWindow(bFileName);
	GetDlgItem(IDC_AND_SAVE_COMMENT)->EnableWindow(bFileName);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSaveDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_AND_SAVE_FILENAME)->GetWindowText(m_szFileName);
	CDisplayDialog::OnOK();
}

BOOL CANDSaveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDSAVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDSaveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDSAVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDOpenDialog dialog

IMPLEMENT_DYNCREATE(CANDOpenDialog, CLocaleDialog)

CANDOpenDialog::CANDOpenDialog(CWnd *pParentWnd) : CLocaleDialog(CANDOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CANDOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDOpenDialog::Initialize()
{
	m_pLayouts.Copy(GetDatabase()->GetANDs());
	return TRUE;
}

VOID CANDOpenDialog::EnumANDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CANDLayout  *pANDLayout;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pANDLayout = m_pLayouts.GetAt(nLayout)) != (CANDLayout *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDOPENDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pANDLayout->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pANDLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_AND_OPEN_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_AND_OPEN_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_AND_OPEN_DIRECTORY), 0);
	GetDlgItem(IDC_AND_OPEN_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_OPEN_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_AND_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CANDOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_AND_OPEN_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void CANDOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDOpenDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CANDOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDOpenDialog message handlers

BOOL CANDOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_AND_OPEN_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_ANDOPENDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_ANDOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_AND_OPEN_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 7; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_AND_OPEN_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumANDs();
	GetDlgItem(IDC_AND_OPEN_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_AND_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_AND_OPEN_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_OPEN_DATABASE)->EnableWindow();
	GetDlgItem(IDC_AND_OPEN_DIRECTORY)->SetFocus();
	return FALSE;
}

BOOL CANDOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_AND_OPEN_DIRECTORY)
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

void CANDOpenDialog::OnOK()
{
	INT  nColumn;
	INT  nColumns;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CString  szTitle;
	CString  szMessage;
	CANDWnd  *pANDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_ANDOPENDIALOG_DIRECTORYTITLEITEM_NAME))
		{
			szName = Listview_GetText(GetDlgItem(IDC_AND_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_AND_OPEN_DIRECTORY)), nColumn);
			continue;
		}
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_ANDOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
		{
			szTitle = Listview_GetText(GetDlgItem(IDC_AND_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_AND_OPEN_DIRECTORY)), nColumn);
			continue;
		}
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_AND)
		{
			if ((pANDWnd = (CANDWnd *)pDisplayWnd)->GetName() == szName)
			{
				pANDWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		if ((pANDWnd = new CANDWnd(szName)))
		{
			if (pANDWnd->Create(GetMainWnd()))
			{
				EndDialog(IDOK);
				return;
			}
		}
		szMessage.Format(STRING(IDS_AND_FAILURE_LOAD), (LPCTSTR)szTitle);
		ShowMessage(szMessage);
	}
	EndDialog(IDOK);
}

void CANDOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CANDOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDImportDialog dialog

IMPLEMENT_DYNCREATE(CANDImportDialog, CLocaleDialog)

CANDImportDialog::CANDImportDialog(CWnd *pParentWnd) : CLocaleDialog(CANDImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CANDImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CANDImportDialog::DoModal(CANDLayouts &pLayouts)
{
	INT_PTR  nResult;

	for (m_pLayouts.RemoveAll(); (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		pLayouts.Copy(&m_pLayouts);
		break;
	}
	return nResult;
}

VOID CANDImportDialog::EnumANDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szItem;
	CString  szFileName;
	CByteArray  cFileBuffer;
	CFileFindEx  cFileFind;
	CANDLayout  *pANDLayout;

	SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_AND_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				for (nLayout = 0, nLayouts = (m_pLayouts.Unmap(cFileBuffer)) ? (INT)m_pLayouts.GetSize() : 0; nLayout < nLayouts; nLayout++)
				{
					if ((pANDLayout = m_pLayouts.GetAt(nLayout)) != (CANDLayout *)NULL)
					{
						for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
							{
								szItem = pANDLayout->GetName();
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
							{
								szItem = pANDLayout->GetTitle();
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_AND_IMPORT_DIRECTORY), nLayout, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_AND_IMPORT_DIRECTORY), nLayout, nColumn, szItem);
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
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CANDImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_AND_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_AND_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_AND_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CANDImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CANDImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_AND_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_AND_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_AND_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_AND_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_AND_IMPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeTitle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDImportDialog message handlers

BOOL CANDImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_ANDIMPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_ANDIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_AND_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_AND_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_AND_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CANDImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_AND_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_AND_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM)->EnableWindow();
			}
			else
			{
				CheckDlgButton(IDC_AND_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_AND_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CANDImportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_AND_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_AND_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumANDs();
	}
	SendDlgItemMessage(IDC_AND_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_AND_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDImportDialog::OnDefault()
{
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDImportDialog::OnCustom()
{
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDImportDialog::OnEditchangeFileName()
{
	EnumANDs();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDImportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDImportDialog::OnEditchangeTitle()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDImportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nLayout;
	INT  nLayouts;
	CString  szName;
	CString  szTitle;
	CANDWnd  cANDWnd;
	CPtrArray  pLayoutIDs;
	CUIntArray  nLayoutIDs;
	CANDLayout  *pLayout[2];
	CANDLayouts  pLayouts;
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_AND_IMPORT_DIRECTORY), nLayout))
		{
			delete m_pLayouts.GetAt(nLayout);
			m_pLayouts.SetAt(nLayout, NULL);
		}
	}
	for (nLayout = 0, nLayouts = (pLayouts.Copy(GetDatabase()->GetANDs())) ? nLayouts : -1; nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pLayouts.GetAt(nLayout)))
		{
			if (IsDlgButtonChecked(IDC_AND_IMPORT_TYPE_CUSTOM))
			{
				GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
				GetDlgItem(IDC_AND_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szTitle);
				pLayout[0]->SetName(szName);
				pLayout[0]->SetTitle(szTitle);
			}
			if ((pLayout[1] = pLayouts.GetAt((nIndex = pLayouts.Find(pLayout[0]->GetName())))))
			{
				pLayout[1]->Copy(pLayout[0]);
				pLayoutIDs.Add(pLayout[1]);
				nLayoutIDs.Add(nIndex);
				continue;
			}
			if ((pLayout[1] = new CANDLayout))
			{
				pLayout[1]->Copy(pLayout[0]);
				if ((nIndex = pLayouts.Add(pLayout[1])) >= 0)
				{
					pLayoutIDs.Add(pLayout[1]);
					nLayoutIDs.Add(-(nIndex + 1));
					continue;
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
		if (GetDatabase()->GetANDs()->Copy(&pLayouts))
		{
			for (nItem = 0, nItems = (INT)pLayoutIDs.GetSize(); nItem < nItems; nItem++)
			{
				if ((pLayout[0] = (CANDLayout *)pLayoutIDs.GetAt(nItem)))
				{
					if (GetDatabase()->Save(pLayout[0]))
					{
						cANDWnd.SetName(pLayout[0]->GetName());
						cANDWnd.SetTitle(pLayout[0]->GetTitle());
						UpdateDatabase(&cANDWnd, (INT)nLayoutIDs.GetAt(nItem));
						continue;
					}
				}
				break;
			}
			if (nItem == nItems) break;
		}
		nLayouts = -1;
		break;
	}
	for (; nLayout != nLayouts; )
	{
		ShowMessage((SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_ANDDIRECTORY_IMPORT_FAILURE : SYSTEM_WARNING_AND_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CANDImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CANDImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDExportDialog dialog

IMPLEMENT_DYNCREATE(CANDExportDialog, CLocaleDialog)

CANDExportDialog::CANDExportDialog(CWnd *pParentWnd) : CLocaleDialog(CANDExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CANDExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CANDExportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

BOOL CANDExportDialog::EnumANDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CANDLayout  *pANDLayout;

	for (nLayout = 0, nLayouts = GetDatabase()->EnumANDs(m_pLayouts, DATABASE_SUBCOMPONENT_AND_NORMAL, FALSE); nLayout < nLayouts; nLayout++)
	{
		if ((pANDLayout = m_pLayouts.GetAt(nLayout)) != (CANDLayout *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pANDLayout->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pANDLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_AND_EXPORT_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_AND_EXPORT_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_AND_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CANDExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_AND_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_AND_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_AND_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CANDExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDExportDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CANDExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_AND_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_AND_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_AND_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_AND_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_AND_EXPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeTitle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDExportDialog message handlers

BOOL CANDExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_ANDEXPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_ANDEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_AND_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumANDs())
	{
		CheckDlgButton(IDC_AND_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_AND_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL CANDExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_AND_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM)->EnableWindow();
				CheckDlgButton(IDC_AND_EXPORT_TYPE_CUSTOM, FALSE);
			}
			else
			{
				CheckDlgButton(IDC_AND_EXPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_AND_EXPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CANDExportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_AND_EXPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_AND_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_AND_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_AND_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnDefault()
{
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnCustom()
{
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnEditchangeTitle()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnOK()
{
	INT  nLayout;
	INT  nLayouts;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szName;
	CString  szTitle;
	CString  szFileName;
	CANDLayout  *pLayout;
	CByteArray  cFileBuffer;
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_AND_EXPORT_DIRECTORY), nLayout))
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
	if ((pLayout = (IsDlgButtonChecked(IDC_AND_EXPORT_TYPE_CUSTOM)) ? m_pLayouts.GetAt(nLayout) : (CANDLayout *)NULL))
	{
		GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szTitle);
		GetDlgItem(IDC_AND_EXPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
		pLayout->SetName(szName);
		pLayout->SetTitle(szTitle);
	}
	for (; nLayout == nLayouts; )
	{
		if (m_pLayouts.Map(cFileBuffer))
		{
			GetDlgItem(IDC_AND_EXPORT_FILENAME)->GetWindowText(szFileName);
			if (cFile.Open(szFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyWrite))
			{
				if (WriteFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFileBuffer.GetSize(), &dwBytes, (LPOVERLAPPED)NULL))
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
	for (; nLayout != nLayouts; )
	{
		ShowMessage((SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_ANDDIRECTORY_EXPORT_FAILURE : SYSTEM_WARNING_AND_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CANDExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CANDExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CANDPropertiesDialog, CLocaleDialog)

CANDPropertiesDialog::CANDPropertiesDialog(CWnd *pParentWnd) : CLocaleDialog(CANDPropertiesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CANDPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDPropertiesDialog::Initialize()
{
	if (GetParent()->GetProperties(&m_lfTable[0][0], &m_lfTable[0][1], m_nTableFontColors[0][0], m_nTableFontColors[0][1], m_nTableColors[0][0], m_nTableColors[0][1]))
	{
		CopyMemory(&m_lfTable[1][0], &m_lfTable[0][0], sizeof(LOGFONT));
		CopyMemory(&m_lfTable[1][1], &m_lfTable[0][1], sizeof(LOGFONT));
		m_nTableFontColors[1][0] = m_nTableFontColors[0][0];
		m_nTableFontColors[1][1] = m_nTableFontColors[0][1];
		m_nTableColors[1][0] = m_nTableColors[0][0];
		m_nTableColors[1][1] = m_nTableColors[0][1];
		return TRUE;
	}
	return FALSE;
}

INT_PTR CANDPropertiesDialog::DoModal(CANDWnd *pParentWnd)
{
	INT_PTR  nResult;

	for (m_pParentWnd = (CWnd *)pParentWnd; (nResult = CLocaleDialog::DoModal()); ) break;
	return nResult;
}

VOID CANDPropertiesDialog::ShowFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_RESETCONTENT); (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_TITLE) && cFontTools.EnumerateFont(m_lfTable[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_ITEMS) && cFontTools.EnumerateFont(m_lfTable[0][1].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_TITLE))
	{
		SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][0])), 0));
		SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][0])), max(SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][0])), 0)));
		SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]);
	}
	if (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_ITEMS))
	{
		SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][1])), 0));
		SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][1])), max(SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][1])), 0)));
		SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]);
	}
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_COLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_COLOR)->EnableWindow((SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CANDPropertiesDialog::ShowFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_AND_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

CANDWnd *CANDPropertiesDialog::GetParent() CONST
{
	return((CANDWnd *)CLocaleDialog::GetParent());
}

BOOL CANDPropertiesDialog::IsModified() CONST
{
	CFontTools  cFontTools;

	return((lstrcmp(m_lfTable[0][0].lfFaceName, m_lfTable[1][0].lfFaceName) || (m_lfTable[0][0].lfHeight != m_lfTable[1][0].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][0]))) || m_lfTable[0][0].lfWeight != m_lfTable[1][0].lfWeight || m_lfTable[0][0].lfItalic != m_lfTable[1][0].lfItalic || lstrcmp(m_lfTable[0][1].lfFaceName, m_lfTable[1][1].lfFaceName) || (m_lfTable[0][1].lfHeight != m_lfTable[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][1])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][1]))) || m_lfTable[0][1].lfWeight != m_lfTable[1][1].lfWeight || m_lfTable[0][1].lfItalic != m_lfTable[1][1].lfItalic || GetDlgItem(IDC_AND_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]) != GetDlgItem(IDC_AND_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][0]) || GetDlgItem(IDC_AND_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]) != GetDlgItem(IDC_AND_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][1]) || GetDlgItem(IDC_AND_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]) != GetDlgItem(IDC_AND_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][0]) || GetDlgItem(IDC_AND_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]) != GetDlgItem(IDC_AND_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][1])) ? TRUE : FALSE);
}

BOOL CANDPropertiesDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_AND_PROPERTIES_FONTS_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_AND_PROPERTIES_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_AND_PROPERTIES_FONTS_SIZE)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void CANDPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CANDPropertiesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CANDPropertiesDialog)
	ON_WM_PAINT()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_PROPERTIES_FONTS_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_AND_PROPERTIES_FONTS_ITEMS, OnItemsFont)
	ON_BN_CLICKED(IDC_AND_PROPERTIES_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_AND_PROPERTIES_FONTS_NAME, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_AND_PROPERTIES_FONTS_NAME, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_AND_PROPERTIES_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_AND_PROPERTIES_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_AND_PROPERTIES_FONTS_COLOR, OnSelchangeFontColor)
	ON_CBN_SELCHANGE(IDC_AND_PROPERTIES_COLORS_TITLE, OnSelchangeTitleBackgroundColor)
	ON_CBN_SELCHANGE(IDC_AND_PROPERTIES_COLORS_KEYS, OnSelchangeKeysBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDPropertiesDialog message handlers

BOOL CANDPropertiesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	CheckDlgButton(IDC_AND_PROPERTIES_FONTS_TITLE, TRUE);
	CheckDlgButton(IDC_AND_PROPERTIES_FONTS_ITEMS, FALSE);
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_NAME, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_COLOR, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_COLOR, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_AND_PROPERTIES_COLORS_TITLE, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_AND_PROPERTIES_COLORS_TITLE, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_AND_PROPERTIES_COLORS_KEYS, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_AND_PROPERTIES_COLORS_KEYS, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_AND_PROPERTIES_COLORS_TITLE, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]);
	SendDlgItemMessage(IDC_AND_PROPERTIES_COLORS_KEYS, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]);
	AccessControl(IDC_AND_PROPERTIES_FONTS_NAME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE));
	AccessControl(IDC_AND_PROPERTIES_FONTS_STYLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE));
	AccessControl(IDC_AND_PROPERTIES_FONTS_SIZE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE));
	AccessControl(IDC_AND_PROPERTIES_FONTS_COLOR, CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE));
	AccessControl(IDC_AND_PROPERTIES_COLORS_TITLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE));
	AccessControl(IDC_AND_PROPERTIES_COLORS_KEYS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE));
	GetDlgItem(IDC_AND_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_TITLE)->EnableWindow();
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_ITEMS)->EnableWindow();
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_PROPERTIES_FONTS_NAME)->EnableWindow();
	GetDlgItem(IDC_AND_PROPERTIES_COLORS_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_PROPERTIES_COLORS_TITLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_PROPERTIES_COLORS_TITLE)->EnableWindow();
	GetDlgItem(IDC_AND_PROPERTIES_COLORS_KEYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_PROPERTIES_COLORS_KEYS)->EnableWindow();
	ShowFontDetails();
	return TRUE;
}

void CANDPropertiesDialog::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_AND_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_TITLE)) ? &m_lfTable[0][0] : &m_lfTable[0][1]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_TITLE)) ? m_nTableFontColors[0][0] : m_nTableFontColors[0][1]) : GetSysColor(COLOR_GRAYTEXT));
			cDC.FillSolidRect(rSampleText, (SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_TITLE)) ? m_nTableColors[0][0] : GetSysColor(COLOR_3DFACE)) : GetSysColor(COLOR_3DFACE));
			cDC.DrawText(m_szFontSampleText, rSampleText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			cDC.SetTextColor(nOldColor);
			cDC.SelectObject(pOldFont);
			cDC.SetBkMode(nBkMode);
			ValidateRect(rSampleText);
		}
		cFont.DeleteObject();
		break;
	}
}

void CANDPropertiesDialog::OnTitleFont()
{
	SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CANDPropertiesDialog::OnItemsFont()
{
	SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][1].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CANDPropertiesDialog::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDPropertiesDialog::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_TITLE))
	{
		lstrcpy(m_lfTable[0][0].lfFaceName, Combobox_GetText(GetDlgItem(IDC_AND_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_ITEMS))
	{
		lstrcpy(m_lfTable[0][1].lfFaceName, Combobox_GetText(GetDlgItem(IDC_AND_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_AND_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_AND_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][0]);
	}
	if (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_AND_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_AND_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][1]);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDPropertiesDialog::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_AND_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_AND_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDPropertiesDialog::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_AND_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_AND_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDPropertiesDialog::OnSelchangeFontColor()
{
	for (; IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_TITLE); )
	{
		m_nTableFontColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	for (; IsDlgButtonChecked(IDC_AND_PROPERTIES_FONTS_ITEMS); )
	{
		m_nTableFontColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_AND_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDPropertiesDialog::OnSelchangeTitleBackgroundColor()
{
	for (m_nTableColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_AND_PROPERTIES_COLORS_TITLE, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_AND_PROPERTIES_COLORS_TITLE, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDPropertiesDialog::OnSelchangeKeysBackgroundColor()
{
	for (m_nTableColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_AND_PROPERTIES_COLORS_KEYS, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_AND_PROPERTIES_COLORS_KEYS, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParent()->SetProperties(&m_lfTable[0][0], &m_lfTable[0][1], m_nTableFontColors[0][0], m_nTableFontColors[0][1], m_nTableColors[0][0], m_nTableColors[0][1]);
	EndDialog(IDOK);
}

void CANDPropertiesDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CANDPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDFindDialog dialog

IMPLEMENT_DYNCREATE(CANDFindDialog, CDisplayDialog)

CANDFindDialog::CANDFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CANDFindDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDFindDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CANDFindDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CANDWnd *CANDFindDialog::GetParent() CONST
{
	return((CANDWnd *)CDisplayDialog::GetParent());
}

void CANDFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDFindDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CANDFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CANDFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_FIND_NEXT, OnFindText)
	ON_BN_CLICKED(IDC_AND_FIND_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_AND_FIND_TEXT, OnSelchangeText)
	ON_CBN_EDITCHANGE(IDC_AND_FIND_TEXT, OnEditchangeText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDFindDialog message handlers

BOOL CANDFindDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	BOOL  bFindDefaults[4];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szSearchItems.GetSize(), GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_AND_FIND_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szSearchItems.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_AND_FIND_DIRECTION_DOWN, bFindDefaults[0]);
	CheckDlgButton(IDC_AND_FIND_DIRECTION_UP, !bFindDefaults[0]);
	CheckDlgButton(IDC_AND_FIND_ALL, bFindDefaults[1]);
	CheckDlgButton(IDC_AND_FIND_CASE, bFindDefaults[2]);
	CheckDlgButton(IDC_AND_FIND_WORD, bFindDefaults[3]);
	GetDlgItem(IDC_AND_FIND_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_FIND_TEXT)->EnableWindow();
	GetDlgItem(IDC_AND_FIND_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_AND_FIND_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_AND_FIND_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_AND_FIND_ALL)->EnableWindow();
	GetDlgItem(IDC_AND_FIND_CASE)->EnableWindow();
	GetDlgItem(IDC_AND_FIND_WORD)->EnableWindow();
	return TRUE;
}

void CANDFindDialog::OnFindText()
{
	CString  szText;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_AND_FIND_TEXT)->GetWindowText(szText); SendDlgItemMessage(IDC_AND_FIND_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText) == CB_ERR; )
	{
		SendDlgItemMessage(IDC_AND_FIND_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText);
		m_szSearchItems.Add(szText);
		break;
	}
	if (!GetParent()->Search(szText, IsDlgButtonChecked(IDC_AND_FIND_DIRECTION_DOWN), IsDlgButtonChecked(IDC_AND_FIND_ALL), IsDlgButtonChecked(IDC_AND_FIND_CASE), IsDlgButtonChecked(IDC_AND_FIND_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_AND_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
		return;
	}
	CheckDlgButton(IDC_AND_FIND_ALL, FALSE);
}

void CANDFindDialog::OnSelchangeText()
{
	GetDlgItem(IDC_AND_FIND_NEXT)->EnableWindow((SendDlgItemMessage(IDC_AND_FIND_TEXT, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CANDFindDialog::OnEditchangeText()
{
	GetDlgItem(IDC_AND_FIND_NEXT)->EnableWindow((GetDlgItem(IDC_AND_FIND_TEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CANDFindDialog::OnCancel()
{
	GetParent()->SetFocus();
	CDisplayDialog::OnCancel();
}

BOOL CANDFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDReplaceDialog dialog

IMPLEMENT_DYNCREATE(CANDReplaceDialog, CDisplayDialog)

CANDReplaceDialog::CANDReplaceDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CANDReplaceDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDReplaceDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CANDReplaceDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CANDWnd *CANDReplaceDialog::GetParent() CONST
{
	return((CANDWnd *)CDisplayDialog::GetParent());
}

void CANDReplaceDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDReplaceDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CANDReplaceDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CANDReplaceDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_REPLACE_FINDNEXT, OnFindNextText)
	ON_BN_CLICKED(IDC_AND_REPLACE_NEXT, OnReplaceText)
	ON_BN_CLICKED(IDC_AND_REPLACE_ALLNEXT, OnReplaceAllText)
	ON_BN_CLICKED(IDC_AND_REPLACE_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_AND_REPLACE_FINDTEXT, OnSelchangeFindText)
	ON_CBN_EDITCHANGE(IDC_AND_REPLACE_FINDTEXT, OnEditchangeFindText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDReplaceDialog message handlers

BOOL CANDReplaceDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szItems[0].GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_AND_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szItems[0].GetAt(nItem));
		continue;
	}
	for (nItem = 0, nItems = (INT)m_szItems[1].GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_AND_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szItems[1].GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_AND_REPLACE_ALL, TRUE);
	CheckDlgButton(IDC_AND_REPLACE_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_AND_REPLACE_FINDTEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_REPLACE_FINDTEXT)->EnableWindow();
	GetDlgItem(IDC_AND_REPLACE_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_REPLACE_TEXT)->EnableWindow();
	GetDlgItem(IDC_AND_REPLACE_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_AND_REPLACE_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_AND_REPLACE_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_AND_REPLACE_ALL)->EnableWindow();
	GetDlgItem(IDC_AND_REPLACE_CASE)->EnableWindow();
	GetDlgItem(IDC_AND_REPLACE_WORD)->EnableWindow();
	return TRUE;
}

void CANDReplaceDialog::OnFindNextText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_AND_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_AND_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_AND_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_AND_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_AND_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_AND_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->Search(szText[0], IsDlgButtonChecked(IDC_AND_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_AND_REPLACE_ALL), IsDlgButtonChecked(IDC_AND_REPLACE_CASE), IsDlgButtonChecked(IDC_AND_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_AND_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
		return;
	}
	CheckDlgButton(IDC_AND_REPLACE_ALL, FALSE);
}

void CANDReplaceDialog::OnReplaceText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_AND_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_AND_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_AND_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_AND_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_AND_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_AND_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->Replace(szText[0], szText[1], IsDlgButtonChecked(IDC_AND_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_AND_REPLACE_ALL), IsDlgButtonChecked(IDC_AND_REPLACE_CASE), IsDlgButtonChecked(IDC_AND_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_AND_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
	}
}

void CANDReplaceDialog::OnReplaceAllText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_AND_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_AND_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_AND_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_AND_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_AND_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_AND_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->ReplaceAll(szText[0], szText[1], IsDlgButtonChecked(IDC_AND_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_AND_REPLACE_ALL), IsDlgButtonChecked(IDC_AND_REPLACE_CASE), IsDlgButtonChecked(IDC_AND_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_AND_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
	}
}

void CANDReplaceDialog::OnSelchangeFindText()
{
	GetDlgItem(IDC_AND_REPLACE_FINDNEXT)->EnableWindow((GetDlgItem(IDC_AND_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_REPLACE_NEXT)->EnableWindow((GetDlgItem(IDC_AND_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_REPLACE_ALLNEXT)->EnableWindow((GetDlgItem(IDC_AND_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CANDReplaceDialog::OnEditchangeFindText()
{
	GetDlgItem(IDC_AND_REPLACE_FINDNEXT)->EnableWindow((GetDlgItem(IDC_AND_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_REPLACE_NEXT)->EnableWindow((GetDlgItem(IDC_AND_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_REPLACE_ALLNEXT)->EnableWindow((GetDlgItem(IDC_AND_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CANDReplaceDialog::OnCancel()
{
	GetParent()->SetFocus();
	CDisplayDialog::OnCancel();
}

BOOL CANDReplaceDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDREPLACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDReplaceDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDREPLACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDGoToDialog dialog

IMPLEMENT_DYNCREATE(CANDGoToDialog, CDisplayDialog)

CANDGoToDialog::CANDGoToDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CANDGoToDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDGoToDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CANDGoToDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CANDWnd *CANDGoToDialog::GetParent() CONST
{
	return((CANDWnd *)CDisplayDialog::GetParent());
}

BOOL CANDGoToDialog::Check(BOOL bModified) CONST
{
	return(((IsDlgButtonChecked(IDC_AND_GOTO_LINE) && GetDlgItem(IDC_AND_GOTO_LINENUMBER)->GetWindowTextLength() > 0) || IsDlgButtonChecked(IDC_AND_GOTO_JUMPDOWN) || IsDlgButtonChecked(IDC_AND_GOTO_JUMPUP)) ? TRUE : FALSE);
}

void CANDGoToDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDGoToDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CANDGoToDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CANDGoToDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_GOTO_LINE, OnLineNumber)
	ON_BN_CLICKED(IDC_AND_GOTO_JUMPDOWN, OnJumpLineDown)
	ON_BN_CLICKED(IDC_AND_GOTO_JUMPUP, OnJumpLineUp)
	ON_BN_CLICKED(IDC_AND_GOTO_JUMP, OnJump)
	ON_BN_CLICKED(IDC_AND_GOTO_HELP, OnHelp)
	ON_EN_CHANGE(IDC_AND_GOTO_LINENUMBER, OnEditchangeLineNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDGoToDialog message handlers

BOOL CANDGoToDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_AND_GOTO_LINE, TRUE);
	Spinbox_SetRange(GetDlgItem(IDC_AND_GOTO_JUMPDOWNLINE), 1, INT_MAX);
	Spinbox_SetRange(GetDlgItem(IDC_AND_GOTO_JUMPUPLINE), 1, INT_MAX);
	GetDlgItem(IDC_AND_GOTO_LINE_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_GOTO_LINE)->EnableWindow();
	GetDlgItem(IDC_AND_GOTO_LINENUMBER)->EnableWindow();
	GetDlgItem(IDC_AND_GOTO_JUMPDOWN)->EnableWindow();
	GetDlgItem(IDC_AND_GOTO_JUMPUP)->EnableWindow();
	GetDlgItem(IDC_AND_GOTO_LINENUMBER)->SetFocus();
	return FALSE;
}

void CANDGoToDialog::OnLineNumber()
{
	CheckDlgButton(IDC_AND_GOTO_LINE, TRUE);
	CheckDlgButton(IDC_AND_GOTO_JUMPDOWN, FALSE);
	CheckDlgButton(IDC_AND_GOTO_JUMPUP, FALSE);
	GetDlgItem(IDC_AND_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_AND_GOTO_LINENUMBER)->EnableWindow();
	GetDlgItem(IDC_AND_GOTO_JUMPDOWN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_JUMPDOWNLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_JUMPUP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_JUMPUPLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_JUMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_LINENUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDGoToDialog::OnJumpLineDown()
{
	CheckDlgButton(IDC_AND_GOTO_LINE, FALSE);
	CheckDlgButton(IDC_AND_GOTO_JUMPDOWN, TRUE);
	CheckDlgButton(IDC_AND_GOTO_JUMPUP, FALSE);
	Spinbox_SetPos(GetDlgItem(IDC_AND_GOTO_JUMPDOWNLINE), 10);
	GetDlgItem(IDC_AND_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_AND_GOTO_LINENUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_JUMPDOWN_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_GOTO_JUMPDOWNLINE)->EnableWindow();
	GetDlgItem(IDC_AND_GOTO_JUMPUP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_JUMPUPLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_AND_GOTO_JUMPDOWNLINE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDGoToDialog::OnJumpLineUp()
{
	CheckDlgButton(IDC_AND_GOTO_LINE, FALSE);
	CheckDlgButton(IDC_AND_GOTO_JUMPDOWN, FALSE);
	CheckDlgButton(IDC_AND_GOTO_JUMPUP, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_AND_GOTO_JUMPUPLINE), 10);
	GetDlgItem(IDC_AND_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_AND_GOTO_LINENUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_JUMPDOWN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_JUMPDOWNLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_GOTO_JUMPUP_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_GOTO_JUMPUPLINE)->EnableWindow();
	GetDlgItem(IDC_AND_GOTO_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_AND_GOTO_JUMPUPLINE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDGoToDialog::OnJump()
{
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_AND_GOTO_LINE)) ShowMessage((!GetParent()->GoTo(GetDlgItemInt(IDC_AND_GOTO_LINENUMBER, (LPBOOL)NULL, FALSE), FALSE, FALSE)) ? USER_INFORMATIONAL_AND_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_AND_GOTO_JUMPDOWN)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_AND_GOTO_JUMPDOWNLINE)), TRUE, FALSE)) ? USER_INFORMATIONAL_AND_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_AND_GOTO_JUMPUP)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_AND_GOTO_JUMPUPLINE)), FALSE, TRUE)) ? USER_INFORMATIONAL_AND_GOTO_LINE_FAILURE : USER_NOERROR);
}

void CANDGoToDialog::OnEditchangeLineNumber()
{
	GetDlgItem(IDC_AND_GOTO_JUMP)->EnableWindow((GetDlgItem(IDC_AND_GOTO_LINENUMBER)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDGoToDialog::OnOK()
{
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_AND_GOTO_LINE)) ShowMessage((!GetParent()->GoTo(GetDlgItemInt(IDC_AND_GOTO_LINENUMBER, (LPBOOL)NULL, FALSE), FALSE, FALSE)) ? USER_INFORMATIONAL_AND_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_AND_GOTO_JUMPDOWN)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_AND_GOTO_JUMPDOWNLINE)), TRUE, FALSE)) ? USER_INFORMATIONAL_AND_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_AND_GOTO_JUMPUP)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_AND_GOTO_JUMPUPLINE)), FALSE, TRUE)) ? USER_INFORMATIONAL_AND_GOTO_LINE_FAILURE : USER_NOERROR);
	GetParent()->SetFocus();
	CDisplayDialog::OnOK();
}

BOOL CANDGoToDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDGOTODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDGoToDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_ANDGOTODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDStatusBar

IMPLEMENT_DYNCREATE(CANDStatusBar, CMFCStatusBar)

BOOL CANDStatusBar::SetIndicators(CONST UINT *pIDs, INT nCount)
{
	INT  nIndex;
	CString  szText;

	for (Initialize(); CMFCStatusBar::SetIndicators(pIDs, nCount); )
	{
		if ((nIndex = CommandToIndex(ID_AND_STATUSBAR_DETAILSPANE)) >= 0)
		{
			szText.Format(STRING(IDS_AND_STATUSBAR_DETAILS), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_AND_STATUSBAR_DETAILSPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(nIndex, szText));
		}
		if ((nIndex = CommandToIndex(ID_AND_STATUSBAR_FLAGPANE)) >= 0)
		{
			szText.Format(STRING(IDS_AND_STATUSBAR_FLAG), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_AND_STATUSBAR_FLAGPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_AND_STATUSBAR_FLAGPANE));
		}
		if ((nIndex = CommandToIndex(ID_AND_STATUSBAR_TYPEPANE)) >= 0)
		{
			szText.Format(STRING(IDS_AND_STATUSBAR_TYPE), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_AND_STATUSBAR_TYPEPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_AND_STATUSBAR_TYPEPANE));
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CANDStatusBar::SetPaneText(UINT nID, LPCTSTR pszText)
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

BOOL CANDStatusBar::GetPaneText(UINT nID, CString &szText) CONST
{
	INT  nIndex;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		szText = CMFCStatusBar::GetPaneText(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString CANDStatusBar::GetPaneText(UINT nID) CONST
{
	CString  szText;

	return((GetPaneText(nID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

INT CANDStatusBar::CalcPaneWidth(INT nIndex) CONST
{
	return CalcPaneWidth(nIndex, CMFCStatusBar::GetPaneText(nIndex));
}
INT CANDStatusBar::CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST
{
	INT  nWidth;
	CFont  *pOldFont;
	CClientDC  cDC(NULL);

	if ((pOldFont = cDC.SelectObject(GetFont())))
	{
		nWidth = cDC.GetTextExtent(SPACE + CString(pszText) + SPACE).cx;
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

VOID CANDStatusBar::Initialize()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = GetCount(); nIndex < nCount; nIndex++)
	{
		SetTipText(nIndex, (LPCTSTR)NULL);
		continue;
	}
}

BEGIN_MESSAGE_MAP(CANDStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CANDStatusBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDStatusBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CANDTableView

IMPLEMENT_DYNCREATE(CANDTableView, CDisplayTableView)

CANDTableView::CANDTableView() : CDisplayTableView(DATABASE_COMPONENT_AND, IDR_ANDFRAMEMENU)
{
	return;
}

VOID CANDTableView::SetTitle(LPCTSTR pszName, LPCTSTR pszTitle)
{
	CANDLayout  *pANDLayout;

	if ((pANDLayout = m_pANDLayouts[0].GetAt(m_pANDLayouts[0].Find(pszName))))
	{
		for (pANDLayout->SetTitle(pszTitle); !m_szName.Compare(pszName); )
		{
			UpdateTables();
			break;
		}
	}
	m_szName = pszName;
	m_szTitle = pszTitle;
}

BOOL CANDTableView::GetTitle(CString &szName, CString &szTitle) CONST
{
	CANDLayout  *pANDLayout;

	for (szName.Empty(), szTitle.Empty(); (pANDLayout = m_pANDLayouts[0].GetAt(m_pANDLayouts[0].Find(GetName()))); )
	{
		szTitle = pANDLayout->GetTitle();
		szName = pANDLayout->GetName();
		return TRUE;
	}
	szName = m_szName;
	szTitle = m_szTitle;
	return !szName.IsEmpty();
}

BOOL CANDTableView::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	for (SetTablesFonts(plfTitle, plfItems), SetTablesFontColors(nTitleColor, nItemsColor), SetTablesColors(nTitleBackground, nKeysBackground); IsWindow(GetSafeHwnd()); )
	{
		RepositionTables();
		break;
	}
	return TRUE;
}

BOOL CANDTableView::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	GetTablesFonts(plfTitle, plfItems);
	GetTablesFontColors(nTitleColor, nItemsColor);
	GetTablesColors(nTitleBackground, nKeysBackground);
	return TRUE;
}

VOID CANDTableView::UpdateTableForms(CONST CANDLayout *pANDLayout, INT nIndex, BOOL bDelete)
{
	UpdateDatabase(GetParent(), (nIndex > 0) ? (nIndex - 1) : nIndex, bDelete);
	UpdateForms(GetParent(), pANDLayout, bDelete);
}

CANDWnd *CANDTableView::GetParent() CONST
{
	return((CANDWnd *)CDisplayTableView::GetParent());
}

BOOL CANDTableView::CheckPrivilege() CONST
{
	return CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE);
}

BEGIN_MESSAGE_MAP(CANDTableView, CDisplayTableView)
	//{{AFX_MSG_MAP(CANDTableView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDTableView message handlers

int CANDTableView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayTableView::OnCreate(lpCreateStruct) != -1 && GetDatabase()->CreateTables(this, GetComponent())) ? 0 : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CANDXmlViewDocument

IMPLEMENT_DYNAMIC(CANDXmlViewDocument, CDocument)

CANDXmlViewDocument::CANDXmlViewDocument() : CDocument()
{
	return;
}

CANDXmlViewDocument::~CANDXmlViewDocument()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CANDXmlView

IMPLEMENT_DYNCREATE(CANDXmlView, CRichEditView)

CANDXmlView::CANDXmlView() : CRichEditView()
{
	m_nWordWrap = WrapNone;
}

BOOL CANDXmlView::Create(CWnd *pParentWnd, LPCTSTR pszName, CONST RECT &rect)
{
	CString  szHeader;
	CString  szXmlCode;
	CANDLayout  *pANDLayout;
	CCreateContext  cContext;

	for (cContext.m_pCurrentDoc = new CANDXmlViewDocument; CRichEditView::Create((LPCTSTR)NULL, EMPTYSTRING, ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | ES_NOHIDESEL | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP, rect, pParentWnd, 0, &cContext); )
	{
		for (m_szXmlCode = szHeader = ConstructXmlHeader(); (pANDLayout = GetDatabase()->GetANDs()->GetAt(GetDatabase()->GetANDs()->Find(pszName))) && !pANDLayout->GetXmlCode().IsEmpty(); )
		{
			m_szName = pANDLayout->GetName();
			m_szTitle = pANDLayout->GetTitle();
			szXmlCode = pANDLayout->GetXmlCode();
			break;
		}
		SetWindowText((m_szXmlCode = m_szXmlCode + szXmlCode));
		GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), CalculateXmlHeaderLength());
		return TRUE;
	}
	return FALSE;
}

VOID CANDXmlView::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CANDXmlView::GetName() CONST
{
	return m_szName;
}

VOID CANDXmlView::SetTitle(LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
}

CString CANDXmlView::GetTitle() CONST
{
	return m_szTitle;
}

INT CANDXmlView::DoSave()
{
	INT  nIndex;
	CString  szXmlCode;
	CANDLayout  *pLayout[2];

	for (GetWindowText(szXmlCode); (pLayout[1] = ((pLayout[0] = GetDatabase()->GetANDs()->GetAt(GetDatabase()->GetANDs()->Find(GetName())))) ? new CANDLayout : (CANDLayout *)NULL); )
	{
		for (pLayout[1]->Copy(pLayout[0]), pLayout[1]->SetXmlCode(szXmlCode); (pLayout[0] = (GetDatabase()->Save(pLayout[1])) ? GetDatabase()->GetANDs()->GetAt((nIndex = GetDatabase()->GetANDs()->Find(pLayout[1]->GetName()))) : (CANDLayout *)NULL); )
		{
			GetParent()->SetName(pLayout[0]->GetName());
			GetParent()->SetTitle(pLayout[0]->GetTitle());
			m_szXmlCode = szXmlCode;
			delete pLayout[1];
			return nIndex;
		}
		delete pLayout[1];
		break;
	}
	return -1;
}

BOOL CANDXmlView::CanSave() CONST
{
	CString  szXmlCode;
	CANDLayout  *pLayout;
	CANDLayouts  pLayouts;

	GetWindowText(szXmlCode);
	return(((pLayout = (GetDatabase()->EnumANDs(szXmlCode, pLayouts) == 1) ? pLayouts.GetAt((INT)pLayouts.GetUpperBound()) : (CANDLayout *)NULL) && pLayout->GetName() == GetName()) ? (IsModified() && Check()) : FALSE);
}

INT CANDXmlView::DoSaveAs(LPCTSTR pszFileName)
{
	INT  nIndex;
	CString  szXmlCode;
	CANDLayout  *pLayout[2];
	CANDLayouts  pLayouts;

	for (GetWindowText(szXmlCode); (pLayout[0] = (GetDatabase()->EnumANDs(szXmlCode, pLayouts) == 1) ? pLayouts.GetAt((INT)pLayouts.GetUpperBound()) : (CANDLayout *)NULL); )
	{
		for (pLayout[0]->SetXmlCode(szXmlCode), pLayout[0]->SetFileName(pszFileName); (pLayout[1] = (GetDatabase()->Save(pLayout[0])) ? GetDatabase()->GetANDs()->GetAt((nIndex = GetDatabase()->GetANDs()->Find(pLayout[0]->GetName()))) : (CANDLayout *)NULL); )
		{
			GetParent()->SetName(pLayout[1]->GetName());
			GetParent()->SetTitle(pLayout[1]->GetTitle());
			m_szXmlCode = szXmlCode;
			return nIndex;
		}
		break;
	}
	return -1;
}

BOOL CANDXmlView::CanSaveAs() CONST
{
	CString  szXmlCode;
	CANDLayout  *pLayout;
	CANDLayouts  pLayouts;

	GetWindowText(szXmlCode);
	return(((pLayout = (GetDatabase()->EnumANDs(szXmlCode, pLayouts) == 1) ? pLayouts.GetAt((INT)pLayouts.GetUpperBound()) : (CANDLayout *)NULL)) ? Check() : FALSE);
}

BOOL CANDXmlView::CanPrint() CONST
{
	return((GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

INT CANDXmlView::DoDelete()
{
	INT  nIndex;
	CANDLayout  *pLayout;

	return(((pLayout = GetDatabase()->GetANDs()->GetAt((nIndex = GetDatabase()->GetANDs()->Find(GetName())))) && GetDatabase()->Delete(pLayout)) ? nIndex : -1);
}

BOOL CANDXmlView::CanDelete() CONST
{
	CString  szXmlCode;
	CANDLayout  *pLayout;
	CANDLayouts  pLayouts;

	GetWindowText(szXmlCode);
	return(((pLayout = (GetDatabase()->EnumANDs(szXmlCode, pLayouts) == 1) ? pLayouts.GetAt((INT)pLayouts.GetUpperBound()) : (CANDLayout *)NULL) && pLayout->GetName() == GetName()) ? TRUE : FALSE);
}

VOID CANDXmlView::DoSelectAll()
{
	GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), GetTextLength());
}

BOOL CANDXmlView::CanSelectAll() CONST
{
	return((GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CANDXmlView::UnSelectAll()
{
	GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), CalculateXmlHeaderLength());
}

VOID CANDXmlView::DoCutSel()
{
	GetRichEditCtrl().Cut();
}

BOOL CANDXmlView::CanCutSel() CONST
{
	return !GetRichEditCtrl().GetSelText().IsEmpty();
}

VOID CANDXmlView::DoCopySel()
{
	GetRichEditCtrl().Copy();
}

BOOL CANDXmlView::CanCopySel() CONST
{
	return !GetRichEditCtrl().GetSelText().IsEmpty();
}

VOID CANDXmlView::DoPasteSel()
{
	GetRichEditCtrl().Paste();
}

BOOL CANDXmlView::CanPasteSel() CONST
{
	return GetRichEditCtrl().CanPaste(CF_TEXT);
}

VOID CANDXmlView::DoDeleteSel()
{
	GetRichEditCtrl().ReplaceSel(EMPTYSTRING, TRUE);
}

BOOL CANDXmlView::CanDeleteSel() CONST
{
	long  nSel[2];

	GetRichEditCtrl().GetSel(nSel[0], nSel[1]);
	return((nSel[0] >= CalculateXmlHeaderLength() && !GetRichEditCtrl().GetSelText().IsEmpty()) ? TRUE : FALSE);
}

VOID CANDXmlView::DoUndo()
{
	GetRichEditCtrl().Undo();
}

BOOL CANDXmlView::CanUndo() CONST
{
	return GetRichEditCtrl().CanUndo();
}

VOID CANDXmlView::DoRedo()
{
	GetRichEditCtrl().Redo();
}

BOOL CANDXmlView::CanRedo() CONST
{
	return GetRichEditCtrl().CanRedo();
}

BOOL CANDXmlView::DoEmpty()
{
	DoSelectAll();
	DoDeleteSel();
	return TRUE;
}

BOOL CANDXmlView::IsEmpty() CONST
{
	return((!GetTextLength()) ? TRUE : FALSE);
}

VOID CANDXmlView::DoFind()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgFind.Create(GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CANDXmlView::CanFind() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CANDXmlView::DoFindNext()
{
	LONG  nPos[2];
	CString  szText;

	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.GetDlgItem(IDC_AND_FIND_TEXT)->GetWindowText(szText), GetRichEditCtrl().GetSel(nPos[0], nPos[1]), nPos[0] = nPos[1] = nPos[0] + szText.GetLength(), GetRichEditCtrl().SetSel(nPos[0], nPos[1]); !szText.IsEmpty(); )
		{
			ShowMessage((!Search(szText, TRUE, FALSE, m_dlgFind.IsDlgButtonChecked(IDC_AND_FIND_CASE), m_dlgFind.IsDlgButtonChecked(IDC_AND_FIND_WORD))) ? USER_INFORMATIONAL_AND_FIND_TEXT_NOTHING : USER_NOERROR);
			break;
		}
	}
}
VOID CANDXmlView::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(GetRichEditCtrl().GetSelText(), TRUE, FALSE, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_AND_FIND_TEXT_NOTHING : USER_NOERROR);
}
VOID CANDXmlView::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(pszText, TRUE, bSearchAll, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_AND_FIND_TEXT_NOTHING : USER_NOERROR);
}

BOOL CANDXmlView::CanFindNext() CONST
{
	return(((IsWindow(m_dlgFind.GetSafeHwnd()) || !GetRichEditCtrl().GetSelText().IsEmpty()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CANDXmlView::DoFindPrevious()
{
	CString  szText;

	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.GetDlgItem(IDC_AND_FIND_TEXT)->GetWindowText(szText); !szText.IsEmpty(); )
		{
			ShowMessage((!Search(szText, FALSE, FALSE, m_dlgFind.IsDlgButtonChecked(IDC_AND_FIND_CASE), m_dlgFind.IsDlgButtonChecked(IDC_AND_FIND_WORD))) ? USER_INFORMATIONAL_AND_FIND_TEXT_NOTHING : USER_NOERROR);
			break;
		}
	}
}
VOID CANDXmlView::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(GetRichEditCtrl().GetSelText(), FALSE, FALSE, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_AND_FIND_TEXT_NOTHING : USER_NOERROR);
}
VOID CANDXmlView::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(pszText, FALSE, bSearchAll, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_AND_FIND_TEXT_NOTHING : USER_NOERROR);
}

BOOL CANDXmlView::CanFindPrevious() CONST
{
	return(((IsWindow(m_dlgFind.GetSafeHwnd()) || !GetRichEditCtrl().GetSelText().IsEmpty()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CANDXmlView::DoReplace()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgReplace.Create(GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CANDXmlView::CanReplace() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CANDXmlView::DoGoTo()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgGoTo.Create(GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CANDXmlView::CanGoTo() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

BOOL CANDXmlView::Search(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
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

BOOL CANDXmlView::Replace(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	LONG  nSel[2];
	CString  szText;

	for (GetRichEditCtrl().GetSel(nSel[0], nSel[1]); nSel[0] < nSel[1] && nSel[0] >= CalculateXmlHeaderLength() && nSel[1] - nSel[0] == lstrlen(pszText); )
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
	return Search(pszText, bDown, bAll, bCase, bWord);
}

BOOL CANDXmlView::ReplaceAll(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	LONG  nSel[2];

	for (GetRichEditCtrl().HideSelection(TRUE, TRUE), GetRichEditCtrl().GetSel(nSel[0], nSel[1]), GetRichEditCtrl().SetSel((bAll) ? ((!bDown) ? (GetRichEditCtrl().GetTextLength() - 1) : 0) : nSel[0], (bAll) ? ((!bDown) ? (GetRichEditCtrl().GetTextLength() - 1) : 0) : nSel[1]); TRUE; )
	{
		if (!Replace(pszText, pszReplaceText, bDown, FALSE, bCase, bWord)) break;
		continue;
	}
	GetRichEditCtrl().HideSelection(FALSE, TRUE);
	return TRUE;
}

BOOL CANDXmlView::GoTo(UINT nLine, BOOL bDown, BOOL bUp)
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
	return GoTo((bDown) ? (GetRichEditCtrl().LineFromChar(-1) + nLine + 1) : (GetRichEditCtrl().LineFromChar(-1) - nLine + 1), FALSE, FALSE);
}
BOOL CANDXmlView::GoTo(LPCTSTR pszLine)
{
	INT  nPos;
	INT  nLength;
	CString  szKey;

	for (nPos = 0, nLength = lstrlen(pszLine); nPos < nLength; nPos++)
	{
		szKey.Format(STRING(IDS_AUTOMATIONSCRIPTLANGUAGE_COMPILEROUTPUT_SEARCHKEY), _ttoi(&pszLine[nPos]));
		if (_tcsstr(pszLine, szKey)) break;
	}
	return((nPos < nLength) ? GoTo(_ttoi(&pszLine[nPos])) : FALSE);
}

BOOL CANDXmlView::IsModified() CONST
{
	CString  szXmlCode;

	GetWindowText(szXmlCode);
	return((m_szXmlCode.Compare(szXmlCode) != 0) ? TRUE : FALSE);
}

BOOL CANDXmlView::Check() CONST
{
	return !IsEmpty();
}

CANDWnd *CANDXmlView::GetParent() CONST
{
	return((CANDWnd *)CRichEditView::GetParent());
}

void CANDXmlView::PostNcDestroy()
{
	return;
}

CString CANDXmlView::ConstructXmlHeader() CONST
{
	return(CString(STRING(IDS_XMLHEADER_VERSION)) + CR + EOL + STRING(IDS_AND_XMLHEADER_DOCTYPE) + CR + EOL + CR + EOL);
}

INT CANDXmlView::CalculateXmlHeaderLength() CONST
{
	return(ConstructXmlHeader().GetLength() - 1 - 1 - 1);
}

BOOL CANDXmlView::IsMouseOnXmlHeader(CONST POINT &point) CONST
{
	INT  nPos;

	return(((nPos = GetRichEditCtrl().CharFromPos(point)) >= 0 && nPos < CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CANDXmlView, CRichEditView)
	//{{AFX_MSG_MAP(CANDXmlView)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_CONTROL_REFLECT(EN_CHANGE, OnEditchangeCode)
	ON_CONTROL_REFLECT(EN_UPDATE, OnEditupdateCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDXmlView drawing

void CANDXmlView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CANDXmlView message handlers

int CANDXmlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

void CANDXmlView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point)) SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
	CRichEditView::OnMouseMove(nFlags, point);
}

BOOL CANDXmlView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	POINT  ptCursor;

	for (GetCursorPos(&ptCursor); IsMouseOnXmlHeader(ptCursor); )
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return TRUE;
	}
	return CRichEditView::OnSetCursor(pWnd, nHitTest, message);
}

void CANDXmlView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnLButtonDown(nFlags, point);
}

void CANDXmlView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnLButtonDblClk(nFlags, point);
}

void CANDXmlView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnLButtonUp(nFlags, point);
}

void CANDXmlView::OnMButtonDown(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnMButtonDown(nFlags, point);
}

void CANDXmlView::OnMButtonUp(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnMButtonUp(nFlags, point);
}

void CANDXmlView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnRButtonDown(nFlags, point);
}

void CANDXmlView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnRButtonUp(nFlags, point);
}

void CANDXmlView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	long  nSel[2];

	for (GetRichEditCtrl().GetSel(nSel[0], nSel[1]); ((nSel[0] < CalculateXmlHeaderLength() || (nSel[0] == CalculateXmlHeaderLength() && nSel[0] == nSel[1])) && (nChar == VK_LEFT || nChar == VK_UP || nChar == VK_PRIOR || nChar == VK_BACK || nChar == VK_DELETE)) || (nSel[0] == CalculateXmlHeaderLength() && nSel[0] < nSel[1] && (nChar == VK_LEFT || nChar == VK_UP || nChar == VK_PRIOR)); )
	{
		CAudioDevice::AlertBySound();
		return;
	}
	for (CRichEditView::OnKeyDown(nChar, nRepCnt, nFlags), GetRichEditCtrl().GetSel(nSel[0], nSel[1]); nSel[0] < CalculateXmlHeaderLength(); )
	{
		GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), max(nSel[1], CalculateXmlHeaderLength()));
		return;
	}
}

void CANDXmlView::OnEditchangeCode()
{
	CANDXmlEdit::RenderCode(&GetRichEditCtrl(), &m_cCodeFont);
	GetParent()->UpdateBars();
}

void CANDXmlView::OnEditupdateCode()
{
	long  nSel[2];

	for (GetRichEditCtrl().GetSel(nSel[0], nSel[1]); !IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && nSel[0] < CalculateXmlHeaderLength(); )
	{
		GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), max(nSel[1], CalculateXmlHeaderLength()));
		Invalidate(FALSE);
		break;
	}
	Default();
}


/////////////////////////////////////////////////////////////////////////////
// CANDWnd

IMPLEMENT_DYNCREATE(CANDWnd, CDisplayWnd)

CANDWnd::CANDWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_AND);
}
CANDWnd::CANDWnd(LPCTSTR pszName) : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_AND);
	SetName(pszName);
}

BOOL CANDWnd::Create(CMDIFrameWnd *pParentWnd, UINT nShow)
{
	return Create(pParentWnd, GetName(), nShow);
}
BOOL CANDWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszName, UINT nShow)
{
	CRect  rPosition;

	for (SetName(pszName), rPosition = m_rPosition; CDisplayWnd::Create(pParentWnd, STRING(IDS_DISPLAY_TITLE_AND), (nShow == (UINT)-1) ? CRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) : CRect(0, 0, 0, 0), IDR_ANDFRAME, (nShow != SW_SHOWMINIMIZED || nShow != SW_SHOWMAXIMIZED) ? (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE) : (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW)); )
	{
		for (ShowWindow((nShow == SW_SHOWMAXIMIZED || nShow == SW_SHOWMINIMIZED || nShow == (UINT)-1) ? SW_SHOWNORMAL : nShow); nShow != (UINT)-1; )
		{
			MoveWindow(rPosition);
			break;
		}
		for (; nShow == SW_SHOWMAXIMIZED || nShow == SW_SHOWMINIMIZED; )
		{
			ShowWindow(nShow);
			break;
		}
		UpdateTitle();
		UpdateMenus();
		UpdateStatusBar();
		return TRUE;
	}
	return FALSE;
}

VOID CANDWnd::SetName(LPCTSTR pszName)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.SetName(pszName);
		return;
	}
	m_wndXmlView.SetName(pszName);
}

CString CANDWnd::GetName() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.GetName() : m_wndXmlView.GetName());
}

VOID CANDWnd::SetTitle(LPCTSTR pszTitle)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.SetTitle(GetName(), pszTitle);
		return;
	}
	m_wndXmlView.SetTitle(pszTitle);
}

CString CANDWnd::GetTitle() CONST
{
	CString  szName;
	CString  szTitle;

	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? ((!m_wndTableView.GetTitle(szName, szTitle)) ? STRING(IDS_DISPLAY_TITLE_AND) : szTitle) : ((m_wndXmlView.GetTitle().IsEmpty()) ? STRING(IDS_DISPLAY_TITLE_XML_AND) : m_wndXmlView.GetTitle()));
}

BOOL CANDWnd::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	return m_wndTableView.SetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CANDWnd::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	return m_wndTableView.GetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CANDWnd::IsNew() CONST
{
	return GetName().IsEmpty();
}

BOOL CANDWnd::IsModified() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.Check() && m_wndTableView.IsModified()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.Check() && m_wndXmlView.IsModified())) ? TRUE : FALSE);
}

BOOL CANDWnd::Save(INT nPosition) CONST
{
	UINT  nShowFlags;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	cProfile.DeleteDisplayWindowInfo(nPosition);
	return((cProfile.SetDisplayWindowType(nPosition, GetType()) && cProfile.SetDisplayWindowName(nPosition, GetName()) && cProfile.SetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, (nShowFlags = (!IsIconic()) ? ((!IsZoomed()) ? SW_SHOWNORMAL : SW_SHOWMAXIMIZED) : SW_SHOWMINIMIZED)) && (!GetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) || cProfile.SetANDsFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]))) ? TRUE : FALSE);
}

INT CANDWnd::Load(INT nPosition)
{
	UINT  nShowFlags;
	CString  szName;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	return((cProfile.GetDisplayWindowName(nPosition, szName) && cProfile.GetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, nShowFlags) && (!cProfile.GetANDsFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) || SetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]))) ? CANDWnd::Create(GetMainWnd(), szName, nShowFlags) : -1);
}

BOOL CANDWnd::UpdateProperties()
{
	return((m_dlgProperties.DoModal(this) == IDOK) ? TRUE : FALSE);
}

BOOL CANDWnd::IsUpdatingProperties() CONST
{
	return IsWindow(m_dlgProperties.GetSafeHwnd());
}

BOOL CANDWnd::HasProperties() CONST
{
	return IsWindow(m_wndTableView.GetSafeHwnd());
}

BOOL CANDWnd::CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.CheckTableDropTarget(pszTable, nComponent, point) : FALSE);
}

BOOL CANDWnd::DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point)
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DropOnTableTarget(pszTable, nComponent, point) : FALSE);
}

VOID CANDWnd::UpdateAllPanes(LPCTSTR pszDetails, LPCTSTR pszFlag, LPCTSTR pszType)
{
	m_wndStatusBar.SetPaneText(ID_AND_STATUSBAR_DETAILSPANE, pszDetails);
	m_wndStatusBar.SetPaneText(ID_AND_STATUSBAR_FLAGPANE, pszFlag);
	m_wndStatusBar.SetPaneText(ID_AND_STATUSBAR_TYPEPANE, pszType);
}

BOOL CANDWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
{
	CDC  cDC;
	BOOL  bMetrics;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	DEVMODE  *pDevMode;
	DEVNAMES  *pDevNames;
	CPrintProfileInfo  cPrintProfileInfo;

	if (GetPrintProfile(cPrintProfileInfo) && cPrintProfileInfo.GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetrics))
	{
		if (!AfxIsValidAddress(pPrintInfo, sizeof(PRINTDLG)))
		{
			if (CreatePrinterDC(&cPrintProfileInfo, cDC))
			{
				if (PrintJob(cDC, STRING(IDS_DISPLAY_TITLE_AND), cPrintProfileInfo.GetPrinterName(), rtMargin[0], bMetrics, nFlags))
				{
					cDC.DeleteDC();
					return TRUE;
				}
				cDC.DeleteDC();
			}
			return FALSE;
		}
		if ((pDevNames = (DEVNAMES *)GlobalLock(pPrintInfo->hDevNames)))
		{
			if ((pDevMode = (DEVMODE *)GlobalLock(pPrintInfo->hDevMode)))
			{
				if (CreatePrinterDC(pPrintInfo->hDevNames, pPrintInfo->hDevMode, cDC))
				{
					if (PrintJob(cDC, STRING(IDS_DISPLAY_TITLE_AND), (LPCTSTR)pDevMode->dmDeviceName, rtMargin[0], bMetrics, nFlags, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : -1, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : -1))
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
	return FALSE;
}

VOID CANDWnd::DoSave()
{
	INT  nPosition;
	CString  szMessage;

	if (IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.DoSave())
	{
		GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_AND);
		return;
	}
	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		if ((nPosition = m_wndXmlView.DoSave()) >= 0)
		{
			GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_AND);
			UpdateDatabase(this, nPosition);
			UpdateTitle();
			return;
		}
		szMessage.Format(STRING(IDS_AND_FAILURE_SAVE), (LPCTSTR)GetTitle());
		ShowMessage(szMessage);
	}
}

BOOL CANDWnd::CanSave() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanSave()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanSave())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

VOID CANDWnd::DoSaveAs()
{
	INT  nResult;
	INT  nPosition;
	CString  szMessage;
	CString  szFileName;
	CANDSaveDialog  cSaveDialog;

	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		if ((nResult = cSaveDialog.Create(this, szFileName)) == IDOK && (nPosition = m_wndXmlView.DoSaveAs(szFileName)) >= 0)
		{
			GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_AND);
			UpdateDatabase(this, -(nPosition + 1));
			UpdateTitle();
			UpdateMenus();
			return;
		}
		if (nResult == IDOK)
		{
			szMessage.Format(STRING(IDS_AND_FAILURE_SAVE), (LPCTSTR)GetTitle());
			ShowMessage(szMessage);
		}
	}
}

BOOL CANDWnd::CanSaveAs() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanSaveAs()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

VOID CANDWnd::DoCheck()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoCheck();
		return;
	}
}

BOOL CANDWnd::CanCheck() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCheck()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

VOID CANDWnd::DoDelete()
{
	INT  nPosition;
	CString  szName;
	CString  szTitle;
	CString  szMessage;

	for (szName = GetName(), szTitle = GetTitle(); IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.DoDelete(); )
	{
		GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_AND);
		return;
	}
	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		for (szMessage.Format(STRING(IDS_AND_QUESTION_DELETE), (LPCTSTR)GetTitle()); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES; )
		{
			if ((nPosition = m_wndXmlView.DoDelete()) >= 0)
			{
				GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_AND);
				UpdateDatabase(this, nPosition, TRUE);
				DestroyWindow();
				return;
			}
			szMessage.Format(STRING(IDS_AND_FAILURE_DELETE), (LPCTSTR)szTitle);
			ShowMessage(szMessage);
			break;
		}
	}
}

BOOL CANDWnd::CanDelete() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDelete()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanDelete())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

VOID CANDWnd::DoUndo()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoUndo();
		return;
	}
	m_wndXmlView.DoUndo();
}

BOOL CANDWnd::CanUndo() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanUndo()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanUndo())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

VOID CANDWnd::DoRedo()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoRedo();
		return;
	}
	m_wndXmlView.DoRedo();
}

BOOL CANDWnd::CanRedo() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanRedo()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanRedo())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

VOID CANDWnd::DoFind()
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFind();
}

BOOL CANDWnd::CanFind() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanFind() : FALSE);
}

VOID CANDWnd::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindNext(bMatchCase, bMatchWord);
}
VOID CANDWnd::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindNext(pszText, bSearchAll, bMatchCase, bMatchWord);
}

BOOL CANDWnd::CanFindNext() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanFindNext() : FALSE);
}

VOID CANDWnd::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindPrevious(bMatchCase, bMatchWord);
}
VOID CANDWnd::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindPrevious(pszText, bSearchAll, bMatchCase, bMatchWord);
}

BOOL CANDWnd::CanFindPrevious() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanFindPrevious() : FALSE);
}

VOID CANDWnd::DoReplace()
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoReplace();
}

BOOL CANDWnd::CanReplace() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanReplace()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

VOID CANDWnd::DoGoTo()
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoGoTo();
}

BOOL CANDWnd::CanGoTo() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanGoTo() : FALSE);
}

VOID CANDWnd::DoSelectAll()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoSelectAll();
		return;
	}
	m_wndXmlView.DoSelectAll();
}

BOOL CANDWnd::CanSelectAll() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanSelectAll()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanSelectAll())) ? TRUE : FALSE);
}

VOID CANDWnd::DoCutSel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoCutSel();
		return;
	}
	m_wndXmlView.DoCutSel();
}

BOOL CANDWnd::CanCutSel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCutSel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanCutSel())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

VOID CANDWnd::DoCopySel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoCopySel();
		return;
	}
	m_wndXmlView.DoCopySel();
}

BOOL CANDWnd::CanCopySel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCopySel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanCopySel())) ? TRUE : FALSE);
}

VOID CANDWnd::DoPasteSel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoPasteSel();
		return;
	}
	m_wndXmlView.DoPasteSel();
}

BOOL CANDWnd::CanPasteSel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanPasteSel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanPaste())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

VOID CANDWnd::DoDeleteSel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoDeleteSel();
		return;
	}
	m_wndXmlView.DoDeleteSel();
}

BOOL CANDWnd::CanDeleteSel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteSel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanDeleteSel())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::CanPrint(UINT nFlags) CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanPrint(nFlags)) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanPrint())) ? TRUE : FALSE);
}

VOID CANDWnd::DoClose()
{
	CString  szMessage;

	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoClose();
		return;
	}
	for (szMessage.Format(STRING(IDS_AND_QUESTION_SAVE), (LPCTSTR)GetName()); CanSave(); )
	{
		if (MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES) DoSave();
		return;
	}
	if (IsNew())
	{
		for (szMessage = STRING(IDS_AND_QUESTION_SAVEONCLOSE); CanSaveAs(); )
		{
			if (MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES) DoSaveAs();
			return;
		}
	}
}

BOOL CANDWnd::DoSaveTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoSaveTable() : FALSE);
}

BOOL CANDWnd::CanSaveTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanSaveTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoCheckTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoCheckTable() : FALSE);
}

BOOL CANDWnd::CanCheckTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCheckTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoDeleteTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDeleteTable() : FALSE);
}

BOOL CANDWnd::CanDeleteTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoPrintTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE) : FALSE);
}

BOOL CANDWnd::CanPrintTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE) : FALSE);
}

BOOL CANDWnd::DoPrintAllTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL) : FALSE);
}

BOOL CANDWnd::CanPrintAllTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL) : FALSE);
}

BOOL CANDWnd::DoImportTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoImportTables() : FALSE);
}

BOOL CANDWnd::CanImportTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanImportTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoExportTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoExportTables() : FALSE);
}

BOOL CANDWnd::CanExportTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.CanExportTables() : FALSE);
}

BOOL CANDWnd::DoDiscardTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDiscardTables() : FALSE);
}

BOOL CANDWnd::CanDiscardTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDiscardTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoDiscardAllTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDiscardAllTables() : FALSE);
}

BOOL CANDWnd::CanDiscardAllTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDiscardAllTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoResetTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoResetTables() : FALSE);
}

BOOL CANDWnd::CanResetTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanResetTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoInsertTableRowAbove()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableRowAbove() : FALSE);
}

BOOL CANDWnd::CanInsertTableRowAbove() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableRowAbove()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoInsertTableRowBelow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableRowBelow() : FALSE);
}

BOOL CANDWnd::CanInsertTableRowBelow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableRowBelow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoInsertTableColumnBefore()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableColumnBefore() : FALSE);
}

BOOL CANDWnd::CanInsertTableColumnBefore() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableColumnBefore()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoInsertTableColumnAfter()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableColumnAfter() : FALSE);
}

BOOL CANDWnd::CanInsertTableColumnAfter() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableColumnAfter()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoClearTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoClearTableRow() : FALSE);
}

BOOL CANDWnd::CanClearTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanClearTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoDeleteTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDeleteTableRow() : FALSE);
}

BOOL CANDWnd::CanDeleteTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoDeleteTableColumn()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDeleteTableColumn() : FALSE);
}

BOOL CANDWnd::CanDeleteTableColumn() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteTableColumn()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

BOOL CANDWnd::DoCopyTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoCopyTableRow() : FALSE);
}

BOOL CANDWnd::CanCopyTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.CanCopyTableRow() : FALSE);
}

BOOL CANDWnd::DoPasteTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoPasteTableRow() : FALSE);
}

BOOL CANDWnd::CanPasteTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanPasteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE) : FALSE);
}

VOID CANDWnd::GotoTable(ULONGLONG nComponent, LPCTSTR pszName)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.GotoTable(nComponent, pszName);
}

VOID CANDWnd::UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE);
}
VOID CANDWnd::UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE);
}
VOID CANDWnd::UpdateTables(CONST CANDLayouts &pLayouts)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(pLayouts);
}
VOID CANDWnd::UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE, pLayout->GetName(), bDelete);
}
VOID CANDWnd::UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CANDWnd::UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CANDWnd::UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.UpdateTables(nComponent, pszName, bDelete);
		m_wndTableView.ClearUndo();
	}
}
VOID CANDWnd::UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.UpdateTables(nComponent, nID, bDelete);
		m_wndTableView.ClearUndo();
	}
}
VOID CANDWnd::UpdateTables(ULONGLONG nComponent)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(nComponent);
}
VOID CANDWnd::UpdateTables()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables();
}

BOOL CANDWnd::Search(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.Search(pszText, bDown, bAll, bCase, bWord) : FALSE);
}

BOOL CANDWnd::Replace(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.Replace(pszText, pszReplaceText, bDown, bAll, bCase, bWord) : FALSE);
}

BOOL CANDWnd::ReplaceAll(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.ReplaceAll(pszText, pszReplaceText, bDown, bAll, bCase, bWord) : FALSE);
}

BOOL CANDWnd::GoTo(UINT nLine, BOOL bDown, BOOL bUp)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.GoTo(nLine, bDown, bUp) : FALSE);
}
BOOL CANDWnd::GoTo(LPCTSTR pszLine)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.GoTo(pszLine) : FALSE);
}

VOID CANDWnd::UpdateBars()
{
	CString  szText;
	CStringTools  cStringTools;

	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		szText.Format(STRING(IDS_AND_STATUSBAR_SIZE), (LPCTSTR)cStringTools.ConvertLongUIntToStructuredString(m_wndXmlView.GetWindowTextLength()));
		m_wndStatusBar.SetPaneText(ID_AND_STATUSBAR_DETAILSPANE, szText);
	}
}

VOID CANDWnd::UpdateTitle()
{
	INT  nPos;
	CString  szName;
	CString  szTitle[2];

	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		SetWindowText(STRING(IDS_DISPLAY_TITLE_AND));
		return;
	}
	for (szName = GetName(), szTitle[0] = STRING(IDS_DISPLAY_TITLE_XML_AND); szName.IsEmpty(); )
	{
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_WINDOW_UNTITLED), ((nPos = szTitle[0].ReverseFind(SPACE[0])) >= 0) ? (LPCTSTR)szTitle[0].Left(nPos) : (LPCTSTR)szTitle[0]);
		break;
	}
	for (szTitle[0] = GetTitle(); !szName.IsEmpty() && szTitle[0] == STRING(IDS_DISPLAY_TITLE_XML_AND); )
	{
		szTitle[1].Format(STRING(IDS_DISPLAY_TITLE_XML_AND), (LPCTSTR)szName);
		szTitle[0].Empty();
		break;
	}
	if (!szName.IsEmpty() && !szTitle[0].IsEmpty())
	{
		szTitle[0].Format(STRING(IDS_DISPLAY_TITLE_XML_AND), (LPCTSTR)szName);
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), (LPCTSTR)GetTitle(), (LPCTSTR)szTitle[0]);
	}
	SetWindowText(szTitle[1]);
}

VOID CANDWnd::UpdateMenus()
{
	GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
}

VOID CANDWnd::UpdateStatusBar()
{
	CString  szFlag;
	CString  szType;
	CString  szDetails;

	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		for (m_wndStatusBar.SetIndicators(nStatusBarIndicators, sizeof(nStatusBarIndicators) / sizeof(UINT)); m_wndTableView.GetPanesInfo(szDetails, szFlag, szType); )
		{
			UpdateAllPanes(szDetails, szFlag, szType);
			break;
		}
		return;
	}
	UpdateBars();
}

BOOL CANDWnd::StartPrintJob(CDC &cDC)
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

BOOL CANDWnd::PrintJob(CDC &cDC, LPCTSTR pszForm, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, WORD wFromPage, WORD wToPage)
{
	INT  nPos;
	INT  nPage;
	INT  nOldMapMode;
	INT  nPrintLength;
	BOOL  bPrintOutput[2];
	CRect  rPrintArea[3];
	CFont  cFont[DISPLAY_PRINTFONTS];
	double  fPrintScale;
	CTimeKey  tPrintTime;
	CPtrArray  pFonts;

	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		if (CDisplayWnd::PrintJob(cDC, &m_wndTableView, pszForm, pszPrinterName, rtMargin, bMetric, nFlags, wFromPage, wToPage)) return TRUE;
		return FALSE;
	}
	if (StartPrintJob(cDC))
	{
		if (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rPrintArea[0]) != ERROR  &&  CalcPrintDocTitleFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_TITLE]) && CalcPrintDocInfoTitleFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_INFOTITLE]) && CalcPrintDocNoticeFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_NOTICE], cFont[DISPLAY_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_FOOTER]))
		{
			for (nPos = 0, nPage = 1, nPrintLength = m_wndXmlView.GetTextLengthEx(GTL_PRECISE | GTL_NUMCHARS), pFonts.SetAtGrow(DISPLAY_PRINTFONT_TITLE, &cFont[DISPLAY_PRINTFONT_TITLE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_INFOTITLE, &cFont[DISPLAY_PRINTFONT_INFOTITLE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_FOOTER, &cFont[DISPLAY_PRINTFONT_FOOTER]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_NOTICE, &cFont[DISPLAY_PRINTFONT_NOTICE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_LOGO, &cFont[DISPLAY_PRINTFONT_LOGO]), fPrintScale = (rPrintArea[0].Height() > 0) ? min((double)rPrintArea[0].Width() / (double)rPrintArea[0].Height(), 1.0) : 1.0, bPrintOutput[0] = bPrintOutput[1] = FALSE; nPos < nPrintLength && wFromPage <= wToPage; nPage++)
			{
				if (DrawPrintDocPage(cDC, tPrintTime, pszPrinterName, pFonts, (rPrintArea[1] = rPrintArea[0]), nFlags, nPage, !(bPrintOutput[0] = ((nPage >= (INT)wFromPage  &&  nPage <= (INT)wToPage) || wFromPage == (WORD)-1 || wToPage == (WORD)-1) ? TRUE : FALSE)))
				{
					for (nOldMapMode = cDC.SetMapMode(MM_ISOTROPIC), cDC.SetViewportExt((INT)(10000.0*fPrintScale), (INT)(10000.0*fPrintScale)), cDC.SetWindowExt(10000, 10000), rPrintArea[2].left = (INT)(1440.0*(double)rPrintArea[1].left / ((double)cDC.GetDeviceCaps(LOGPIXELSX)*fPrintScale)), rPrintArea[2].top = (INT)(1440.0*(double)rPrintArea[1].top / ((double)cDC.GetDeviceCaps(LOGPIXELSY)*fPrintScale)), rPrintArea[2].right = (INT)(1440.0*(double)rPrintArea[1].right / ((double)cDC.GetDeviceCaps(LOGPIXELSX)*fPrintScale)), rPrintArea[2].bottom = (INT)(1440.0*(double)rPrintArea[1].bottom / ((double)cDC.GetDeviceCaps(LOGPIXELSY)*fPrintScale)); (nPos = m_wndXmlView.PrintInsideRect(&cDC, rPrintArea[2], nPos, -1, bPrintOutput[0])) >= 0; )
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
	return FALSE;
}

BOOL CANDWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndPage() >= 0 && cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CANDWnd::DrawPrintDocPage(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CPtrArray &pFonts, LPRECT prClip, UINT nFlags, INT nPage, BOOL bCalc)
{
	return((DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(EMPTYSTRING, 0), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_TITLE), nFlags, bCalc) && DrawPrintDocInfoTitle(cDC, prClip, GetPrintDocInfoTitle(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_INFOTITLE), bCalc) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_LOGO), bCalc) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPage), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_FOOTER), bCalc)) ? TRUE : FALSE);
}

BOOL CANDWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nFlags, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

CString CANDWnd::GetPrintDocTitle(LPCTSTR pszName, UINT nFlags) CONST
{
	CANDLayout  *pANDLayout;

	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? (((pANDLayout = (nFlags & DISPLAYTABLEVIEW_PRINT_TABLE) ? GetDatabase()->GetANDs()->GetAt(GetDatabase()->GetANDs()->Find(pszName)) : (CANDLayout *)NULL) && !pANDLayout->GetTitle().IsEmpty()) ? (LPCTSTR)pANDLayout->GetTitle() : pszName) : GetTitle());
}

CString CANDWnd::GetPrintDocInfoTitle() CONST
{
	INT  nPos;
	CString  szTitle[2];

	if (!IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		for (szTitle[0].Format(STRING(IDS_DISPLAY_TITLE_XML_AND), (LPCTSTR)(szTitle[1] = GetName())); (nPos = (szTitle[1].IsEmpty()) ? szTitle[0].Find(SPACE) : -1) >= 0; )
		{
			szTitle[0] = szTitle[0].Left(nPos);
			break;
		}
		return szTitle[0];
	}
	return STRING(IDS_DISPLAY_TITLE_AND);
}

INT CANDWnd::Delete(LPCTSTR pszName)
{
	INT  nIndex;
	CANDLayout  *pLayout;

	return(((pLayout = GetDatabase()->GetANDs()->GetAt((nIndex = GetDatabase()->GetANDs()->Find(pszName)))) && GetDatabase()->Delete(pLayout)) ? nIndex : -1);
}

VOID CANDWnd::AdjustToPrivileges()
{
	if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_AND_CHANGE))
	{
		if (IsWindow(m_wndTableView.GetSafeHwnd()))
		{
			m_wndTableView.UnSelectAll();
			return;
		}
		m_wndXmlView.UnSelectAll();
	}
}

BEGIN_MESSAGE_MAP(CANDWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CANDWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_AND_STATUSBAR_DETAILSPANE, OnUpdateStatusBarDetailsPane)
	ON_UPDATE_COMMAND_UI(ID_AND_STATUSBAR_FLAGPANE, OnUpdateStatusBarFlagPane)
	ON_UPDATE_COMMAND_UI(ID_AND_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDWnd message handlers

int CANDWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayWnd::OnCreate(lpCreateStruct) != -1 && LoadAccelTable(IDR_ANDFRAME)) ? 0 : -1);
}

BOOL CANDWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	CRect  rBar;

	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1))
	{
		for (m_wndStatusBar.GetWindowRect(rBar); GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_AND); ) return m_wndTableView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
		return m_wndXmlView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
	}
	return FALSE;
}

void CANDWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rBar;

	for (m_wndStatusBar.GetWindowRect(rBar); IsWindow(m_wndTableView.GetSafeHwnd()); )
	{
		m_wndTableView.MoveWindow(0, 0, cx, cy - rBar.Height());
		break;
	}
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.MoveWindow(0, 0, cx, cy - rBar.Height());
	CDisplayWnd::OnSize(nType, cx, cy);
}

void CANDWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()) && !bActivate) m_wndTableView.UnSelectAll();
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CANDWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()) && nChar == VK_DOWN) m_wndTableView.ActivateTable();
	CDisplayWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CANDWnd::OnClose()
{
	CHourglassCursor  cCursor;

	DoClose();
	CDisplayWnd::OnClose();
}

void CANDWnd::OnUpdateStatusBarDetailsPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CANDWnd::OnUpdateStatusBarFlagPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CANDWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
