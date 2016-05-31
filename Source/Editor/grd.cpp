// GRD.CPP : Graphic Display Form Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the graphic display
// form related interface.
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
	ID_GRD_STATUSBAR_DETAILSPANE,
	ID_GRD_STATUSBAR_FLAGPANE,
	ID_GRD_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CGRDSaveDialog dialog

IMPLEMENT_DYNCREATE(CGRDSaveDialog, CDisplayDialog)

CGRDSaveDialog::CGRDSaveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CGRDSaveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CGRDSaveDialog::Create(CWnd *pParentWnd, CString &szFileName)
{
	INT  nResult;

	for (szFileName.Empty(); (nResult = CDisplayDialog::Create(pParentWnd, CGRDSaveDialog::IDD)) == IDOK; )
	{
		szFileName = m_szFileName;
		break;
	}
	return nResult;
}

BOOL CGRDSaveDialog::Initialize()
{
	m_pLayouts.Copy(GetDatabase()->GetGRDs());
	m_szFileName.Empty();
	return TRUE;
}

CGRDWnd *CGRDSaveDialog::GetParentDisplay() CONST
{
	return((CGRDWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CGRDSaveDialog::EnumGRDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	CString  szItem;
	CStringTools  cStringTools;
	CGRDLayout  *pLayout;

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
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSAVEDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pLayout->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pLayout->GetTitle();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSAVEDIALOG_DIRECTORYTITLEITEM_LOCATION); )
				{
					szItem = pLayout->GetFileName();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_GRD_SAVE_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_GRD_SAVE_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_GRD_SAVE_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_SAVE_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_SAVE_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_GRD_SAVE_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CGRDSaveDialog::FindGRD(LPCTSTR pszName) CONST
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

BOOL CGRDSaveDialog::CheckFileName(LPCTSTR pszFileName) CONST
{
	INT  nLayout;
	INT  nLayouts;
	CGRDLayout  *pLayout;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = m_pLayouts.GetAt(nLayout)) && !pLayout->GetFileName().CompareNoCase(pszFileName)) break;
		continue;
	}
	return((nLayout == nLayouts) ? TRUE : FALSE);
}

BOOL CGRDSaveDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_GRD_SAVE_FILENAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CGRDSaveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDSaveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDSaveDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDSaveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CGRDSaveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_SAVE_FILENAME_BROWSE, OnBrowseFileName)
	ON_BN_CLICKED(IDC_GRD_SAVE_HELP, OnHelp)
	ON_EN_CHANGE(IDC_GRD_SAVE_FILENAME, OnEditchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDSaveDialog message handlers

BOOL CGRDSaveDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_GRD_SAVE_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_GRDSAVEDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_GRDSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_GRDSAVEDIALOG_DIRECTORYTITLEITEM_LOCATION));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_GRD_SAVE_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT), rColumns.DeflateRect(0, 0, GetSystemMetrics(SM_CXVSCROLL), 0); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_GRD_SAVE_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSAVEDIALOG_DIRECTORYTITLEITEM_NAME)) ? (rColumns.Width() / 4) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION)) ? (rColumns.Width() / 2) : (3 * rColumns.Width()) / 4));
		continue;
	}
	EnumGRDs();
	GetDlgItem(IDC_GRD_SAVE_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_GRD_SAVE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRD_SAVE_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_SAVE_DATABASE)->EnableWindow();
	GetDlgItem(IDC_GRD_SAVE_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_SAVE_FILENAME)->EnableWindow();
	GetDlgItem(IDC_GRD_SAVE_FILENAME_BROWSE)->EnableWindow();
	GetDlgItem(IDC_GRD_SAVE_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return FALSE;
}

BOOL CGRDSaveDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nColumn;
	INT  nColumns;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_GRD_SAVE_DIRECTORY)
	{
		if (pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK)
		{
			for (nColumn = 0, nColumns = (pNotifyListView->iItem >= 0) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
			{
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSAVEDIALOG_DIRECTORYTITLEITEM_LOCATION)) break;
				continue;
			}
			if (pNotifyListView->iItem < 0)
			{
				Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
				SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
				return TRUE;
			}
			GetDlgItem(IDC_GRD_SAVE_FILENAME)->SetWindowText(Listview_GetText(GetDlgItem(IDC_GRD_SAVE_DIRECTORY), pNotifyListView->iItem, nColumn));
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CGRDSaveDialog::OnBrowseFileName()
{
	BOOL  bFileName;
	CString  szFileName;
	CFileBrowseDialog  *pFileBrowseDialog;

	if ((pFileBrowseDialog = new CFileBrowseDialog(this, szFileName, STRING(IDS_FILEBROWSEDIALOG_DATABASEXMLFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEXMLFILTER))) && pFileBrowseDialog->DoModal() == IDOK)
	{
		GetDlgItem(IDC_GRD_SAVE_FILENAME)->SetWindowText((szFileName = pFileBrowseDialog->GetPathName()));
		GetDlgItem(IDC_GRD_SAVE_COMMENT_STATIC)->ShowWindow(((bFileName = !CheckFileName(szFileName))) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_GRD_SAVE_COMMENT)->ShowWindow((bFileName) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_GRD_SAVE_COMMENT_STATIC)->EnableWindow(bFileName);
		GetDlgItem(IDC_GRD_SAVE_COMMENT)->EnableWindow(bFileName);
	}
	delete pFileBrowseDialog;
	SendDlgItemMessage(IDC_GRD_SAVE_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_GRD_SAVE_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSaveDialog::OnEditchangeFileName()
{
	BOOL  bFileName;
	CString  szFileName;

	GetDlgItem(IDC_GRD_SAVE_FILENAME)->GetWindowText(szFileName);
	GetDlgItem(IDC_GRD_SAVE_COMMENT_STATIC)->ShowWindow(((bFileName = !CheckFileName(szFileName))) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_GRD_SAVE_COMMENT)->ShowWindow((bFileName) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_GRD_SAVE_COMMENT_STATIC)->EnableWindow(bFileName);
	GetDlgItem(IDC_GRD_SAVE_COMMENT)->EnableWindow(bFileName);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSaveDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_GRD_SAVE_FILENAME)->GetWindowText(m_szFileName);
	CDisplayDialog::OnOK();
}

BOOL CGRDSaveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDSAVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDSaveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDSAVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDOpenDialog dialog

IMPLEMENT_DYNCREATE(CGRDOpenDialog, CLocaleDialog)

CGRDOpenDialog::CGRDOpenDialog(CWnd *pParentWnd) : CLocaleDialog(CGRDOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CGRDOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDOpenDialog::Initialize()
{
	m_pLayouts.Copy(GetDatabase()->GetGRDs());
	return TRUE;
}

VOID CGRDOpenDialog::EnumGRDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CGRDLayout  *pGRDLayout;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pGRDLayout = m_pLayouts.GetAt(nLayout)) != (CGRDLayout *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDOPENDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pGRDLayout->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pGRDLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_GRD_OPEN_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_GRD_OPEN_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_GRD_OPEN_DIRECTORY), 0);
	GetDlgItem(IDC_GRD_OPEN_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_OPEN_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_GRD_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CGRDOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_GRD_OPEN_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void CGRDOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDOpenDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CGRDOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDOpenDialog message handlers

BOOL CGRDOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_GRD_OPEN_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_GRDOPENDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_GRDOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_GRD_OPEN_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 7; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_GRD_OPEN_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumGRDs();
	GetDlgItem(IDC_GRD_OPEN_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_GRD_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRD_OPEN_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_OPEN_DATABASE)->EnableWindow();
	GetDlgItem(IDC_GRD_OPEN_DIRECTORY)->SetFocus();
	return FALSE;
}

BOOL CGRDOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_GRD_OPEN_DIRECTORY)
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

void CGRDOpenDialog::OnOK()
{
	INT  nColumn;
	INT  nColumns;
	INT  nDisplay;
	INT  nDisplays;
	CString  szName;
	CString  szTitle;
	CString  szMessage;
	CGRDWnd  *pGRDWnd;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_GRDOPENDIALOG_DIRECTORYTITLEITEM_NAME))
		{
			szName = Listview_GetText(GetDlgItem(IDC_GRD_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_GRD_OPEN_DIRECTORY)), nColumn);
			continue;
		}
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_GRDOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
		{
			szTitle = Listview_GetText(GetDlgItem(IDC_GRD_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_GRD_OPEN_DIRECTORY)), nColumn);
			continue;
		}
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_GRD)
		{
			if ((pGRDWnd = (CGRDWnd *)pDisplayWnd)->GetName() == szName)
			{
				pGRDWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		if ((pGRDWnd = new CGRDWnd(szName)))
		{
			if (pGRDWnd->Create(GetMainWnd()))
			{
				EndDialog(IDOK);
				return;
			}
		}
		szMessage.Format(STRING(IDS_GRD_FAILURE_LOAD), (LPCTSTR)szTitle);
		ShowMessage(szMessage);
	}
	EndDialog(IDOK);
}

void CGRDOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CGRDOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDImportDialog dialog

IMPLEMENT_DYNCREATE(CGRDImportDialog, CLocaleDialog)

CGRDImportDialog::CGRDImportDialog(CWnd *pParentWnd) : CLocaleDialog(CGRDImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CGRDImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CGRDImportDialog::DoModal(CGRDLayouts &pLayouts)
{
	INT_PTR  nResult;

	for (m_pLayouts.RemoveAll(); (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		pLayouts.Copy(&m_pLayouts);
		break;
	}
	return nResult;
}

VOID CGRDImportDialog::EnumGRDs()
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
	CGRDLayout  *pGRDLayout;

	SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_GRD_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				for (nLayout = 0, nLayouts = (m_pLayouts.Unmap(cFileBuffer)) ? (INT)m_pLayouts.GetSize() : 0; nLayout < nLayouts; nLayout++)
				{
					if ((pGRDLayout = m_pLayouts.GetAt(nLayout)) != (CGRDLayout *)NULL)
					{
						for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
							{
								szItem = pGRDLayout->GetName();
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
							{
								szItem = pGRDLayout->GetTitle();
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_GRD_IMPORT_DIRECTORY), nLayout, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_GRD_IMPORT_DIRECTORY), nLayout, nColumn, szItem);
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
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CGRDImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_GRD_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_GRD_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_GRD_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CGRDImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CGRDImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_GRD_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_GRD_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_GRD_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_GRD_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeTitle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDImportDialog message handlers

BOOL CGRDImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_GRDIMPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_GRDIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_GRD_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_GRD_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_GRD_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CGRDImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_GRD_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_GRD_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM)->EnableWindow();
			}
			else
			{
				CheckDlgButton(IDC_GRD_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_GRD_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CGRDImportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_GRD_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_GRD_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumGRDs();
	}
	SendDlgItemMessage(IDC_GRD_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_GRD_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDImportDialog::OnDefault()
{
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDImportDialog::OnCustom()
{
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDImportDialog::OnEditchangeFileName()
{
	EnumGRDs();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDImportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDImportDialog::OnEditchangeTitle()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDImportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nLayout;
	INT  nLayouts;
	CString  szName;
	CString  szTitle;
	CGRDWnd  cGRDWnd;
	CPtrArray  pLayoutIDs;
	CUIntArray  nLayoutIDs;
	CGRDLayout  *pLayout[2];
	CGRDLayouts  pLayouts;
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_GRD_IMPORT_DIRECTORY), nLayout))
		{
			delete m_pLayouts.GetAt(nLayout);
			m_pLayouts.SetAt(nLayout, NULL);
		}
	}
	for (nLayout = 0, nLayouts = (pLayouts.Copy(GetDatabase()->GetGRDs())) ? nLayouts : -1; nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pLayouts.GetAt(nLayout)))
		{
			if (IsDlgButtonChecked(IDC_GRD_IMPORT_TYPE_CUSTOM))
			{
				GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
				GetDlgItem(IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szTitle);
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
			if ((pLayout[1] = new CGRDLayout))
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
		if (GetDatabase()->GetGRDs()->Copy(&pLayouts))
		{
			for (nItem = 0, nItems = (INT)pLayoutIDs.GetSize(); nItem < nItems; nItem++)
			{
				if ((pLayout[0] = (CGRDLayout *)pLayoutIDs.GetAt(nItem)))
				{
					if (GetDatabase()->Save(pLayout[0]))
					{
						cGRDWnd.SetName(pLayout[0]->GetName());
						cGRDWnd.SetTitle(pLayout[0]->GetTitle());
						UpdateDatabase(&cGRDWnd, (INT)nLayoutIDs.GetAt(nItem));
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
		ShowMessage((SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_GRDDIRECTORY_IMPORT_FAILURE : SYSTEM_WARNING_GRD_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CGRDImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CGRDImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDExportDialog dialog

IMPLEMENT_DYNCREATE(CGRDExportDialog, CLocaleDialog)

CGRDExportDialog::CGRDExportDialog(CWnd *pParentWnd) : CLocaleDialog(CGRDExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CGRDExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CGRDExportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

BOOL CGRDExportDialog::EnumGRDs()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CGRDLayout  *pGRDLayout;

	for (nLayout = 0, nLayouts = GetDatabase()->EnumGRDs(m_pLayouts, FALSE); nLayout < nLayouts; nLayout++)
	{
		if ((pGRDLayout = m_pLayouts.GetAt(nLayout)) != (CGRDLayout *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pGRDLayout->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pGRDLayout->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_GRD_EXPORT_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_GRD_EXPORT_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CGRDExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_GRD_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_GRD_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_GRD_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CGRDExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDExportDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CGRDExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_GRD_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_GRD_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_GRD_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_GRD_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeTitle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDExportDialog message handlers

BOOL CGRDExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_GRDEXPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_GRDEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_GRD_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumGRDs())
	{
		CheckDlgButton(IDC_GRD_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_GRD_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL CGRDExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_GRD_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM)->EnableWindow();
				CheckDlgButton(IDC_GRD_EXPORT_TYPE_CUSTOM, FALSE);
			}
			else
			{
				CheckDlgButton(IDC_GRD_EXPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_GRD_EXPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CGRDExportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_GRD_EXPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_GRD_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_GRD_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_GRD_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnDefault()
{
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnCustom()
{
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnEditchangeTitle()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnOK()
{
	INT  nLayout;
	INT  nLayouts;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szName;
	CString  szTitle;
	CString  szFileName;
	CGRDLayout  *pLayout;
	CByteArray  cFileBuffer;
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_GRD_EXPORT_DIRECTORY), nLayout))
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
	if ((pLayout = (IsDlgButtonChecked(IDC_GRD_EXPORT_TYPE_CUSTOM)) ? m_pLayouts.GetAt(nLayout) : (CGRDLayout *)NULL))
	{
		GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szTitle);
		GetDlgItem(IDC_GRD_EXPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
		pLayout->SetName(szName);
		pLayout->SetTitle(szTitle);
	}
	for (; nLayout == nLayouts; )
	{
		if (m_pLayouts.Map(cFileBuffer))
		{
			GetDlgItem(IDC_GRD_EXPORT_FILENAME)->GetWindowText(szFileName);
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
		ShowMessage((SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_GRDDIRECTORY_EXPORT_FAILURE : SYSTEM_WARNING_GRD_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CGRDExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CGRDExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CGRDPropertiesDialog, CLocaleDialog)

CGRDPropertiesDialog::CGRDPropertiesDialog(CWnd *pParentWnd) : CLocaleDialog(CGRDPropertiesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CGRDPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDPropertiesDialog::Initialize()
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

INT_PTR CGRDPropertiesDialog::DoModal(CGRDWnd *pParentWnd)
{
	INT_PTR  nResult;

	for (m_pParentWnd = (CWnd *)pParentWnd; (nResult = CLocaleDialog::DoModal()); ) break;
	return nResult;
}

VOID CGRDPropertiesDialog::ShowFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_RESETCONTENT); (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_TITLE) && cFontTools.EnumerateFont(m_lfTable[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_ITEMS) && cFontTools.EnumerateFont(m_lfTable[0][1].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_TITLE))
	{
		SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][0])), 0));
		SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][0])), max(SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][0])), 0)));
		SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]);
	}
	if (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_ITEMS))
	{
		SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][1])), 0));
		SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][1])), max(SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][1])), 0)));
		SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]);
	}
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_COLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_COLOR)->EnableWindow((SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CGRDPropertiesDialog::ShowFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

CGRDWnd *CGRDPropertiesDialog::GetParent() CONST
{
	return((CGRDWnd *)CLocaleDialog::GetParent());
}

BOOL CGRDPropertiesDialog::IsModified() CONST
{
	CFontTools  cFontTools;

	return((lstrcmp(m_lfTable[0][0].lfFaceName, m_lfTable[1][0].lfFaceName) || (m_lfTable[0][0].lfHeight != m_lfTable[1][0].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][0]))) || m_lfTable[0][0].lfWeight != m_lfTable[1][0].lfWeight || m_lfTable[0][0].lfItalic != m_lfTable[1][0].lfItalic || lstrcmp(m_lfTable[0][1].lfFaceName, m_lfTable[1][1].lfFaceName) || (m_lfTable[0][1].lfHeight != m_lfTable[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][1])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][1]))) || m_lfTable[0][1].lfWeight != m_lfTable[1][1].lfWeight || m_lfTable[0][1].lfItalic != m_lfTable[1][1].lfItalic || GetDlgItem(IDC_GRD_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]) != GetDlgItem(IDC_GRD_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][0]) || GetDlgItem(IDC_GRD_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]) != GetDlgItem(IDC_GRD_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][1]) || GetDlgItem(IDC_GRD_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]) != GetDlgItem(IDC_GRD_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][0]) || GetDlgItem(IDC_GRD_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]) != GetDlgItem(IDC_GRD_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][1])) ? TRUE : FALSE);
}

BOOL CGRDPropertiesDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_GRD_PROPERTIES_FONTS_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRD_PROPERTIES_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SIZE)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void CGRDPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGRDPropertiesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CGRDPropertiesDialog)
	ON_WM_PAINT()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_PROPERTIES_FONTS_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_GRD_PROPERTIES_FONTS_ITEMS, OnItemsFont)
	ON_BN_CLICKED(IDC_GRD_PROPERTIES_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_GRD_PROPERTIES_FONTS_NAME, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_GRD_PROPERTIES_FONTS_NAME, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_GRD_PROPERTIES_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_GRD_PROPERTIES_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_GRD_PROPERTIES_FONTS_COLOR, OnSelchangeFontColor)
	ON_CBN_SELCHANGE(IDC_GRD_PROPERTIES_COLORS_TITLE, OnSelchangeTitleBackgroundColor)
	ON_CBN_SELCHANGE(IDC_GRD_PROPERTIES_COLORS_KEYS, OnSelchangeKeysBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDPropertiesDialog message handlers

BOOL CGRDPropertiesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	CheckDlgButton(IDC_GRD_PROPERTIES_FONTS_TITLE, TRUE);
	CheckDlgButton(IDC_GRD_PROPERTIES_FONTS_ITEMS, FALSE);
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_NAME, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_COLOR, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_COLOR, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_GRD_PROPERTIES_COLORS_TITLE, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRD_PROPERTIES_COLORS_TITLE, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_GRD_PROPERTIES_COLORS_KEYS, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRD_PROPERTIES_COLORS_KEYS, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_GRD_PROPERTIES_COLORS_TITLE, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]);
	SendDlgItemMessage(IDC_GRD_PROPERTIES_COLORS_KEYS, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]);
	AccessControl(IDC_GRD_PROPERTIES_FONTS_NAME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE));
	AccessControl(IDC_GRD_PROPERTIES_FONTS_STYLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE));
	AccessControl(IDC_GRD_PROPERTIES_FONTS_SIZE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE));
	AccessControl(IDC_GRD_PROPERTIES_FONTS_COLOR, CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE));
	AccessControl(IDC_GRD_PROPERTIES_COLORS_TITLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE));
	AccessControl(IDC_GRD_PROPERTIES_COLORS_KEYS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE));
	GetDlgItem(IDC_GRD_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_TITLE)->EnableWindow();
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_ITEMS)->EnableWindow();
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_PROPERTIES_FONTS_NAME)->EnableWindow();
	GetDlgItem(IDC_GRD_PROPERTIES_COLORS_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_PROPERTIES_COLORS_TITLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_PROPERTIES_COLORS_TITLE)->EnableWindow();
	GetDlgItem(IDC_GRD_PROPERTIES_COLORS_KEYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_PROPERTIES_COLORS_KEYS)->EnableWindow();
	ShowFontDetails();
	return TRUE;
}

void CGRDPropertiesDialog::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_TITLE)) ? &m_lfTable[0][0] : &m_lfTable[0][1]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_TITLE)) ? m_nTableFontColors[0][0] : m_nTableFontColors[0][1]) : GetSysColor(COLOR_GRAYTEXT));
			cDC.FillSolidRect(rSampleText, (SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_TITLE)) ? m_nTableColors[0][0] : GetSysColor(COLOR_3DFACE)) : GetSysColor(COLOR_3DFACE));
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

void CGRDPropertiesDialog::OnTitleFont()
{
	SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CGRDPropertiesDialog::OnItemsFont()
{
	SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][1].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CGRDPropertiesDialog::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDPropertiesDialog::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_TITLE))
	{
		lstrcpy(m_lfTable[0][0].lfFaceName, Combobox_GetText(GetDlgItem(IDC_GRD_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_ITEMS))
	{
		lstrcpy(m_lfTable[0][1].lfFaceName, Combobox_GetText(GetDlgItem(IDC_GRD_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_GRD_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][0]);
	}
	if (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_GRD_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][1]);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDPropertiesDialog::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_GRD_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_GRD_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDPropertiesDialog::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_GRD_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDPropertiesDialog::OnSelchangeFontColor()
{
	for (; IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_TITLE); )
	{
		m_nTableFontColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	for (; IsDlgButtonChecked(IDC_GRD_PROPERTIES_FONTS_ITEMS); )
	{
		m_nTableFontColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRD_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDPropertiesDialog::OnSelchangeTitleBackgroundColor()
{
	for (m_nTableColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_GRD_PROPERTIES_COLORS_TITLE, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRD_PROPERTIES_COLORS_TITLE, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDPropertiesDialog::OnSelchangeKeysBackgroundColor()
{
	for (m_nTableColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_GRD_PROPERTIES_COLORS_KEYS, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRD_PROPERTIES_COLORS_KEYS, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParent()->SetProperties(&m_lfTable[0][0], &m_lfTable[0][1], m_nTableFontColors[0][0], m_nTableFontColors[0][1], m_nTableColors[0][0], m_nTableColors[0][1]);
	EndDialog(IDOK);
}

void CGRDPropertiesDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CGRDPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDFindDialog dialog

IMPLEMENT_DYNCREATE(CGRDFindDialog, CDisplayDialog)

CGRDFindDialog::CGRDFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CGRDFindDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDFindDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CGRDFindDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CGRDWnd *CGRDFindDialog::GetParent() CONST
{
	return((CGRDWnd *)CDisplayDialog::GetParent());
}

void CGRDFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDFindDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGRDFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CGRDFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_FIND_NEXT, OnFindText)
	ON_BN_CLICKED(IDC_GRD_FIND_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_GRD_FIND_TEXT, OnSelchangeText)
	ON_CBN_EDITCHANGE(IDC_GRD_FIND_TEXT, OnEditchangeText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDFindDialog message handlers

BOOL CGRDFindDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	BOOL  bFindDefaults[4];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szSearchItems.GetSize(), GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_GRD_FIND_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szSearchItems.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_GRD_FIND_DIRECTION_DOWN, bFindDefaults[0]);
	CheckDlgButton(IDC_GRD_FIND_DIRECTION_UP, !bFindDefaults[0]);
	CheckDlgButton(IDC_GRD_FIND_ALL, bFindDefaults[1]);
	CheckDlgButton(IDC_GRD_FIND_CASE, bFindDefaults[2]);
	CheckDlgButton(IDC_GRD_FIND_WORD, bFindDefaults[3]);
	GetDlgItem(IDC_GRD_FIND_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_FIND_TEXT)->EnableWindow();
	GetDlgItem(IDC_GRD_FIND_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_GRD_FIND_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_GRD_FIND_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_GRD_FIND_ALL)->EnableWindow();
	GetDlgItem(IDC_GRD_FIND_CASE)->EnableWindow();
	GetDlgItem(IDC_GRD_FIND_WORD)->EnableWindow();
	return TRUE;
}

void CGRDFindDialog::OnFindText()
{
	CString  szText;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_GRD_FIND_TEXT)->GetWindowText(szText); SendDlgItemMessage(IDC_GRD_FIND_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText) == CB_ERR; )
	{
		SendDlgItemMessage(IDC_GRD_FIND_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText);
		m_szSearchItems.Add(szText);
		break;
	}
	if (!GetParent()->Search(szText, IsDlgButtonChecked(IDC_GRD_FIND_DIRECTION_DOWN), IsDlgButtonChecked(IDC_GRD_FIND_ALL), IsDlgButtonChecked(IDC_GRD_FIND_CASE), IsDlgButtonChecked(IDC_GRD_FIND_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_GRD_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
		return;
	}
	CheckDlgButton(IDC_GRD_FIND_ALL, FALSE);
}

void CGRDFindDialog::OnSelchangeText()
{
	GetDlgItem(IDC_GRD_FIND_NEXT)->EnableWindow((SendDlgItemMessage(IDC_GRD_FIND_TEXT, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CGRDFindDialog::OnEditchangeText()
{
	GetDlgItem(IDC_GRD_FIND_NEXT)->EnableWindow((GetDlgItem(IDC_GRD_FIND_TEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CGRDFindDialog::OnCancel()
{
	GetParent()->SetFocus();
	CDisplayDialog::OnCancel();
}

BOOL CGRDFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDReplaceDialog dialog

IMPLEMENT_DYNCREATE(CGRDReplaceDialog, CDisplayDialog)

CGRDReplaceDialog::CGRDReplaceDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CGRDReplaceDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDReplaceDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CGRDReplaceDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CGRDWnd *CGRDReplaceDialog::GetParent() CONST
{
	return((CGRDWnd *)CDisplayDialog::GetParent());
}

void CGRDReplaceDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDReplaceDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGRDReplaceDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CGRDReplaceDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_REPLACE_FINDNEXT, OnFindNextText)
	ON_BN_CLICKED(IDC_GRD_REPLACE_NEXT, OnReplaceText)
	ON_BN_CLICKED(IDC_GRD_REPLACE_ALLNEXT, OnReplaceAllText)
	ON_BN_CLICKED(IDC_GRD_REPLACE_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_GRD_REPLACE_FINDTEXT, OnSelchangeFindText)
	ON_CBN_EDITCHANGE(IDC_GRD_REPLACE_FINDTEXT, OnEditchangeFindText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDReplaceDialog message handlers

BOOL CGRDReplaceDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szItems[0].GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_GRD_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szItems[0].GetAt(nItem));
		continue;
	}
	for (nItem = 0, nItems = (INT)m_szItems[1].GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_GRD_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szItems[1].GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_GRD_REPLACE_ALL, TRUE);
	CheckDlgButton(IDC_GRD_REPLACE_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_GRD_REPLACE_FINDTEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_REPLACE_FINDTEXT)->EnableWindow();
	GetDlgItem(IDC_GRD_REPLACE_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_REPLACE_TEXT)->EnableWindow();
	GetDlgItem(IDC_GRD_REPLACE_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_GRD_REPLACE_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_GRD_REPLACE_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_GRD_REPLACE_ALL)->EnableWindow();
	GetDlgItem(IDC_GRD_REPLACE_CASE)->EnableWindow();
	GetDlgItem(IDC_GRD_REPLACE_WORD)->EnableWindow();
	return TRUE;
}

void CGRDReplaceDialog::OnFindNextText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_GRD_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_GRD_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_GRD_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_GRD_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_GRD_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_GRD_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->Search(szText[0], IsDlgButtonChecked(IDC_GRD_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_GRD_REPLACE_ALL), IsDlgButtonChecked(IDC_GRD_REPLACE_CASE), IsDlgButtonChecked(IDC_GRD_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_GRD_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
		return;
	}
	CheckDlgButton(IDC_GRD_REPLACE_ALL, FALSE);
}

void CGRDReplaceDialog::OnReplaceText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_GRD_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_GRD_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_GRD_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_GRD_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_GRD_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_GRD_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->Replace(szText[0], szText[1], IsDlgButtonChecked(IDC_GRD_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_GRD_REPLACE_ALL), IsDlgButtonChecked(IDC_GRD_REPLACE_CASE), IsDlgButtonChecked(IDC_GRD_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_GRD_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
	}
}

void CGRDReplaceDialog::OnReplaceAllText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_GRD_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_GRD_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_GRD_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_GRD_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_GRD_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_GRD_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->ReplaceAll(szText[0], szText[1], IsDlgButtonChecked(IDC_GRD_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_GRD_REPLACE_ALL), IsDlgButtonChecked(IDC_GRD_REPLACE_CASE), IsDlgButtonChecked(IDC_GRD_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_GRD_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
	}
}

void CGRDReplaceDialog::OnSelchangeFindText()
{
	GetDlgItem(IDC_GRD_REPLACE_FINDNEXT)->EnableWindow((GetDlgItem(IDC_GRD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_REPLACE_NEXT)->EnableWindow((GetDlgItem(IDC_GRD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_REPLACE_ALLNEXT)->EnableWindow((GetDlgItem(IDC_GRD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CGRDReplaceDialog::OnEditchangeFindText()
{
	GetDlgItem(IDC_GRD_REPLACE_FINDNEXT)->EnableWindow((GetDlgItem(IDC_GRD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_REPLACE_NEXT)->EnableWindow((GetDlgItem(IDC_GRD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_REPLACE_ALLNEXT)->EnableWindow((GetDlgItem(IDC_GRD_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CGRDReplaceDialog::OnCancel()
{
	GetParent()->SetFocus();
	CDisplayDialog::OnCancel();
}

BOOL CGRDReplaceDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDREPLACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDReplaceDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDREPLACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDGoToDialog dialog

IMPLEMENT_DYNCREATE(CGRDGoToDialog, CDisplayDialog)

CGRDGoToDialog::CGRDGoToDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CGRDGoToDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDGoToDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CGRDGoToDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CGRDWnd *CGRDGoToDialog::GetParent() CONST
{
	return((CGRDWnd *)CDisplayDialog::GetParent());
}

BOOL CGRDGoToDialog::Check(BOOL bModified) CONST
{
	return(((IsDlgButtonChecked(IDC_GRD_GOTO_LINE) && GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->GetWindowTextLength() > 0) || IsDlgButtonChecked(IDC_GRD_GOTO_JUMPDOWN) || IsDlgButtonChecked(IDC_GRD_GOTO_JUMPUP)) ? TRUE : FALSE);
}

void CGRDGoToDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDGoToDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGRDGoToDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CGRDGoToDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_GOTO_LINE, OnLineNumber)
	ON_BN_CLICKED(IDC_GRD_GOTO_JUMPDOWN, OnJumpLineDown)
	ON_BN_CLICKED(IDC_GRD_GOTO_JUMPUP, OnJumpLineUp)
	ON_BN_CLICKED(IDC_GRD_GOTO_JUMP, OnJump)
	ON_BN_CLICKED(IDC_GRD_GOTO_HELP, OnHelp)
	ON_EN_CHANGE(IDC_GRD_GOTO_LINENUMBER, OnEditchangeLineNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDGoToDialog message handlers

BOOL CGRDGoToDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_GRD_GOTO_LINE, TRUE);
	Spinbox_SetRange(GetDlgItem(IDC_GRD_GOTO_JUMPDOWNLINE), 1, INT_MAX);
	Spinbox_SetRange(GetDlgItem(IDC_GRD_GOTO_JUMPUPLINE), 1, INT_MAX);
	GetDlgItem(IDC_GRD_GOTO_LINE_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_GOTO_LINE)->EnableWindow();
	GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->EnableWindow();
	GetDlgItem(IDC_GRD_GOTO_JUMPDOWN)->EnableWindow();
	GetDlgItem(IDC_GRD_GOTO_JUMPUP)->EnableWindow();
	GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->SetFocus();
	return FALSE;
}

void CGRDGoToDialog::OnLineNumber()
{
	CheckDlgButton(IDC_GRD_GOTO_LINE, TRUE);
	CheckDlgButton(IDC_GRD_GOTO_JUMPDOWN, FALSE);
	CheckDlgButton(IDC_GRD_GOTO_JUMPUP, FALSE);
	GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->EnableWindow();
	GetDlgItem(IDC_GRD_GOTO_JUMPDOWN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_JUMPDOWNLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_JUMPUP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_JUMPUPLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_JUMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDGoToDialog::OnJumpLineDown()
{
	CheckDlgButton(IDC_GRD_GOTO_LINE, FALSE);
	CheckDlgButton(IDC_GRD_GOTO_JUMPDOWN, TRUE);
	CheckDlgButton(IDC_GRD_GOTO_JUMPUP, FALSE);
	Spinbox_SetPos(GetDlgItem(IDC_GRD_GOTO_JUMPDOWNLINE), 10);
	GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_JUMPDOWN_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_GOTO_JUMPDOWNLINE)->EnableWindow();
	GetDlgItem(IDC_GRD_GOTO_JUMPUP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_JUMPUPLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_GRD_GOTO_JUMPDOWNLINE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDGoToDialog::OnJumpLineUp()
{
	CheckDlgButton(IDC_GRD_GOTO_LINE, FALSE);
	CheckDlgButton(IDC_GRD_GOTO_JUMPDOWN, FALSE);
	CheckDlgButton(IDC_GRD_GOTO_JUMPUP, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_GRD_GOTO_JUMPUPLINE), 10);
	GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_JUMPDOWN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_JUMPDOWNLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_GOTO_JUMPUP_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_GOTO_JUMPUPLINE)->EnableWindow();
	GetDlgItem(IDC_GRD_GOTO_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_GRD_GOTO_JUMPUPLINE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDGoToDialog::OnJump()
{
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_GRD_GOTO_LINE)) ShowMessage((!GetParent()->GoTo(GetDlgItemInt(IDC_GRD_GOTO_LINENUMBER, (LPBOOL)NULL, FALSE), FALSE, FALSE)) ? USER_INFORMATIONAL_GRD_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_GRD_GOTO_JUMPDOWN)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_GRD_GOTO_JUMPDOWNLINE)), TRUE, FALSE)) ? USER_INFORMATIONAL_GRD_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_GRD_GOTO_JUMPUP)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_GRD_GOTO_JUMPUPLINE)), FALSE, TRUE)) ? USER_INFORMATIONAL_GRD_GOTO_LINE_FAILURE : USER_NOERROR);
}

void CGRDGoToDialog::OnEditchangeLineNumber()
{
	GetDlgItem(IDC_GRD_GOTO_JUMP)->EnableWindow((GetDlgItem(IDC_GRD_GOTO_LINENUMBER)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDGoToDialog::OnOK()
{
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_GRD_GOTO_LINE)) ShowMessage((!GetParent()->GoTo(GetDlgItemInt(IDC_GRD_GOTO_LINENUMBER, (LPBOOL)NULL, FALSE), FALSE, FALSE)) ? USER_INFORMATIONAL_GRD_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_GRD_GOTO_JUMPDOWN)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_GRD_GOTO_JUMPDOWNLINE)), TRUE, FALSE)) ? USER_INFORMATIONAL_GRD_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_GRD_GOTO_JUMPUP)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_GRD_GOTO_JUMPUPLINE)), FALSE, TRUE)) ? USER_INFORMATIONAL_GRD_GOTO_LINE_FAILURE : USER_NOERROR);
	GetParent()->SetFocus();
	CDisplayDialog::OnOK();
}

BOOL CGRDGoToDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDGOTODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDGoToDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_GRDGOTODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDStatusBar

IMPLEMENT_DYNCREATE(CGRDStatusBar, CMFCStatusBar)

BOOL CGRDStatusBar::SetIndicators(CONST UINT *pIDs, INT nCount)
{
	INT  nIndex;
	CString  szText;

	for (Initialize(); CMFCStatusBar::SetIndicators(pIDs, nCount); )
	{
		if ((nIndex = CommandToIndex(ID_GRD_STATUSBAR_DETAILSPANE)) >= 0)
		{
			szText.Format(STRING(IDS_GRD_STATUSBAR_DETAILS), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_GRD_STATUSBAR_DETAILSPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(nIndex, szText));
		}
		if ((nIndex = CommandToIndex(ID_GRD_STATUSBAR_FLAGPANE)) >= 0)
		{
			szText.Format(STRING(IDS_GRD_STATUSBAR_FLAG), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_GRD_STATUSBAR_FLAGPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_GRD_STATUSBAR_FLAGPANE));
		}
		if ((nIndex = CommandToIndex(ID_GRD_STATUSBAR_TYPEPANE)) >= 0)
		{
			szText.Format(STRING(IDS_GRD_STATUSBAR_TYPE), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_GRD_STATUSBAR_TYPEPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_GRD_STATUSBAR_TYPEPANE));
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDStatusBar::SetPaneText(UINT nID, LPCTSTR pszText)
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

BOOL CGRDStatusBar::GetPaneText(UINT nID, CString &szText) CONST
{
	INT  nIndex;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		szText = CMFCStatusBar::GetPaneText(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString CGRDStatusBar::GetPaneText(UINT nID) CONST
{
	CString  szText;

	return((GetPaneText(nID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

INT CGRDStatusBar::CalcPaneWidth(INT nIndex) CONST
{
	return CalcPaneWidth(nIndex, CMFCStatusBar::GetPaneText(nIndex));
}
INT CGRDStatusBar::CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST
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

VOID CGRDStatusBar::Initialize()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = GetCount(); nIndex < nCount; nIndex++)
	{
		SetTipText(nIndex, (LPCTSTR)NULL);
		continue;
	}
}

BEGIN_MESSAGE_MAP(CGRDStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CGRDStatusBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDStatusBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CGRDTableView

IMPLEMENT_DYNCREATE(CGRDTableView, CDisplayTableView)

CGRDTableView::CGRDTableView() : CDisplayTableView(DATABASE_COMPONENT_GRD, IDR_GRDFRAMEMENU)
{
	return;
}

VOID CGRDTableView::SetTitle(LPCTSTR pszName, LPCTSTR pszTitle)
{
	CGRDLayout  *pGRDLayout;

	if ((pGRDLayout = m_pGRDLayouts[0].GetAt(m_pGRDLayouts[0].Find(pszName))))
	{
		for (pGRDLayout->SetTitle(pszTitle); !m_szName.Compare(pszName); )
		{
			UpdateTables();
			break;
		}
	}
	m_szName = pszName;
	m_szTitle = pszTitle;
}

BOOL CGRDTableView::GetTitle(CString &szName, CString &szTitle) CONST
{
	CGRDLayout  *pGRDLayout;

	for (szName.Empty(), szTitle.Empty(); (pGRDLayout = m_pGRDLayouts[0].GetAt(m_pGRDLayouts[0].Find(GetName()))); )
	{
		szTitle = pGRDLayout->GetTitle();
		szName = pGRDLayout->GetName();
		return TRUE;
	}
	szName = m_szName;
	szTitle = m_szTitle;
	return !szName.IsEmpty();
}

BOOL CGRDTableView::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	for (SetTablesFonts(plfTitle, plfItems), SetTablesFontColors(nTitleColor, nItemsColor), SetTablesColors(nTitleBackground, nKeysBackground); IsWindow(GetSafeHwnd()); )
	{
		RepositionTables();
		break;
	}
	return TRUE;
}

BOOL CGRDTableView::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	GetTablesFonts(plfTitle, plfItems);
	GetTablesFontColors(nTitleColor, nItemsColor);
	GetTablesColors(nTitleBackground, nKeysBackground);
	return TRUE;
}

VOID CGRDTableView::UpdateTableForms(CONST CGRDLayout *pGRDLayout, INT nIndex, BOOL bDelete)
{
	UpdateDatabase(GetParent(), (nIndex > 0) ? (nIndex - 1) : nIndex, bDelete);
	UpdateForms(GetParent(), pGRDLayout, bDelete);
}

CGRDWnd *CGRDTableView::GetParent() CONST
{
	return((CGRDWnd *)CDisplayTableView::GetParent());
}

BOOL CGRDTableView::CheckPrivilege() CONST
{
	return CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE);
}

BEGIN_MESSAGE_MAP(CGRDTableView, CDisplayTableView)
	//{{AFX_MSG_MAP(CGRDTableView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDTableView message handlers

int CGRDTableView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayTableView::OnCreate(lpCreateStruct) != -1 && GetDatabase()->CreateTables(this, GetComponent())) ? 0 : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDXmlViewDocument

IMPLEMENT_DYNAMIC(CGRDXmlViewDocument, CDocument)

CGRDXmlViewDocument::CGRDXmlViewDocument() : CDocument()
{
	return;
}

CGRDXmlViewDocument::~CGRDXmlViewDocument()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CGRDXmlView

IMPLEMENT_DYNCREATE(CGRDXmlView, CRichEditView)

CGRDXmlView::CGRDXmlView() : CRichEditView()
{
	m_nWordWrap = WrapNone;
}

BOOL CGRDXmlView::Create(CWnd *pParentWnd, LPCTSTR pszName, CONST RECT &rect)
{
	CString  szHeader;
	CString  szXmlCode;
	CGRDLayout  *pGRDLayout;
	CCreateContext  cContext;

	for (cContext.m_pCurrentDoc = new CGRDXmlViewDocument; CRichEditView::Create((LPCTSTR)NULL, EMPTYSTRING, ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | ES_NOHIDESEL | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP, rect, pParentWnd, 0, &cContext); )
	{
		for (m_szXmlCode = szHeader = ConstructXmlHeader(); (pGRDLayout = GetDatabase()->GetGRDs()->GetAt(GetDatabase()->GetGRDs()->Find(pszName))) && !pGRDLayout->GetXmlCode().IsEmpty(); )
		{
			m_szName = pGRDLayout->GetName();
			m_szTitle = pGRDLayout->GetTitle();
			szXmlCode = pGRDLayout->GetXmlCode();
			break;
		}
		SetWindowText((m_szXmlCode = m_szXmlCode + szXmlCode));
		GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), CalculateXmlHeaderLength());
		return TRUE;
	}
	return FALSE;
}

VOID CGRDXmlView::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CGRDXmlView::GetName() CONST
{
	return m_szName;
}

VOID CGRDXmlView::SetTitle(LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
}

CString CGRDXmlView::GetTitle() CONST
{
	return m_szTitle;
}

INT CGRDXmlView::DoSave()
{
	INT  nIndex;
	CString  szXmlCode;
	CGRDLayout  *pLayout[2];

	for (GetWindowText(szXmlCode); (pLayout[1] = ((pLayout[0] = GetDatabase()->GetGRDs()->GetAt(GetDatabase()->GetGRDs()->Find(GetName())))) ? new CGRDLayout : (CGRDLayout *)NULL); )
	{
		for (pLayout[1]->Copy(pLayout[0]), pLayout[1]->SetXmlCode(szXmlCode); (pLayout[0] = (GetDatabase()->Save(pLayout[1])) ? GetDatabase()->GetGRDs()->GetAt((nIndex = GetDatabase()->GetGRDs()->Find(pLayout[1]->GetName()))) : (CGRDLayout *)NULL); )
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

BOOL CGRDXmlView::CanSave() CONST
{
	CString  szXmlCode;
	CGRDLayout  *pLayout;
	CGRDLayouts  pLayouts;

	GetWindowText(szXmlCode);
	return(((pLayout = (GetDatabase()->EnumGRDs(szXmlCode, pLayouts) == 1) ? pLayouts.GetAt((INT)pLayouts.GetUpperBound()) : (CGRDLayout *)NULL) && pLayout->GetName() == GetName()) ? (IsModified() && Check()) : FALSE);
}

INT CGRDXmlView::DoSaveAs(LPCTSTR pszFileName)
{
	INT  nIndex;
	CString  szXmlCode;
	CGRDLayout  *pLayout[2];
	CGRDLayouts  pLayouts;

	for (GetWindowText(szXmlCode); (pLayout[0] = (GetDatabase()->EnumGRDs(szXmlCode, pLayouts) == 1) ? pLayouts.GetAt((INT)pLayouts.GetUpperBound()) : (CGRDLayout *)NULL); )
	{
		for (pLayout[0]->SetXmlCode(szXmlCode), pLayout[0]->SetFileName(pszFileName); (pLayout[1] = (GetDatabase()->Save(pLayout[0])) ? GetDatabase()->GetGRDs()->GetAt((nIndex = GetDatabase()->GetGRDs()->Find(pLayout[0]->GetName()))) : (CGRDLayout *)NULL); )
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

BOOL CGRDXmlView::CanSaveAs() CONST
{
	CString  szXmlCode;
	CGRDLayout  *pLayout;
	CGRDLayouts  pLayouts;

	GetWindowText(szXmlCode);
	return(((pLayout = (GetDatabase()->EnumGRDs(szXmlCode, pLayouts) == 1) ? pLayouts.GetAt((INT)pLayouts.GetUpperBound()) : (CGRDLayout *)NULL)) ? Check() : FALSE);
}

BOOL CGRDXmlView::CanPrint() CONST
{
	return((GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

INT CGRDXmlView::DoDelete()
{
	INT  nIndex;
	CGRDLayout  *pLayout;

	return(((pLayout = GetDatabase()->GetGRDs()->GetAt((nIndex = GetDatabase()->GetGRDs()->Find(GetName())))) && GetDatabase()->Delete(pLayout)) ? nIndex : -1);
}

BOOL CGRDXmlView::CanDelete() CONST
{
	CString  szXmlCode;
	CGRDLayout  *pLayout;
	CGRDLayouts  pLayouts;

	GetWindowText(szXmlCode);
	return(((pLayout = (GetDatabase()->EnumGRDs(szXmlCode, pLayouts) == 1) ? pLayouts.GetAt((INT)pLayouts.GetUpperBound()) : (CGRDLayout *)NULL) && pLayout->GetName() == GetName()) ? TRUE : FALSE);
}

VOID CGRDXmlView::DoSelectAll()
{
	GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), GetTextLength());
}

BOOL CGRDXmlView::CanSelectAll() CONST
{
	return((GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CGRDXmlView::UnSelectAll()
{
	GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), CalculateXmlHeaderLength());
}

VOID CGRDXmlView::DoCutSel()
{
	GetRichEditCtrl().Cut();
}

BOOL CGRDXmlView::CanCutSel() CONST
{
	return !GetRichEditCtrl().GetSelText().IsEmpty();
}

VOID CGRDXmlView::DoCopySel()
{
	GetRichEditCtrl().Copy();
}

BOOL CGRDXmlView::CanCopySel() CONST
{
	return !GetRichEditCtrl().GetSelText().IsEmpty();
}

VOID CGRDXmlView::DoPasteSel()
{
	GetRichEditCtrl().Paste();
}

BOOL CGRDXmlView::CanPasteSel() CONST
{
	return GetRichEditCtrl().CanPaste(CF_TEXT);
}

VOID CGRDXmlView::DoDeleteSel()
{
	GetRichEditCtrl().ReplaceSel(EMPTYSTRING, TRUE);
}

BOOL CGRDXmlView::CanDeleteSel() CONST
{
	long  nSel[2];

	GetRichEditCtrl().GetSel(nSel[0], nSel[1]);
	return((nSel[0] >= CalculateXmlHeaderLength() && !GetRichEditCtrl().GetSelText().IsEmpty()) ? TRUE : FALSE);
}

VOID CGRDXmlView::DoUndo()
{
	GetRichEditCtrl().Undo();
}

BOOL CGRDXmlView::CanUndo() CONST
{
	return GetRichEditCtrl().CanUndo();
}

VOID CGRDXmlView::DoRedo()
{
	GetRichEditCtrl().Redo();
}

BOOL CGRDXmlView::CanRedo() CONST
{
	return GetRichEditCtrl().CanRedo();
}

BOOL CGRDXmlView::DoEmpty()
{
	DoSelectAll();
	DoDeleteSel();
	return TRUE;
}

BOOL CGRDXmlView::IsEmpty() CONST
{
	return((!GetTextLength()) ? TRUE : FALSE);
}

VOID CGRDXmlView::DoFind()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgFind.Create(GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CGRDXmlView::CanFind() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CGRDXmlView::DoFindNext()
{
	LONG  nPos[2];
	CString  szText;

	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.GetDlgItem(IDC_GRD_FIND_TEXT)->GetWindowText(szText), GetRichEditCtrl().GetSel(nPos[0], nPos[1]), nPos[0] = nPos[1] = nPos[0] + szText.GetLength(), GetRichEditCtrl().SetSel(nPos[0], nPos[1]); !szText.IsEmpty(); )
		{
			ShowMessage((!Search(szText, TRUE, FALSE, m_dlgFind.IsDlgButtonChecked(IDC_GRD_FIND_CASE), m_dlgFind.IsDlgButtonChecked(IDC_GRD_FIND_WORD))) ? USER_INFORMATIONAL_GRD_FIND_TEXT_NOTHING : USER_NOERROR);
			break;
		}
	}
}
VOID CGRDXmlView::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(GetRichEditCtrl().GetSelText(), TRUE, FALSE, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_GRD_FIND_TEXT_NOTHING : USER_NOERROR);
}
VOID CGRDXmlView::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(pszText, TRUE, bSearchAll, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_GRD_FIND_TEXT_NOTHING : USER_NOERROR);
}

BOOL CGRDXmlView::CanFindNext() CONST
{
	return(((IsWindow(m_dlgFind.GetSafeHwnd()) || !GetRichEditCtrl().GetSelText().IsEmpty()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CGRDXmlView::DoFindPrevious()
{
	CString  szText;

	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.GetDlgItem(IDC_GRD_FIND_TEXT)->GetWindowText(szText); !szText.IsEmpty(); )
		{
			ShowMessage((!Search(szText, FALSE, FALSE, m_dlgFind.IsDlgButtonChecked(IDC_GRD_FIND_CASE), m_dlgFind.IsDlgButtonChecked(IDC_GRD_FIND_WORD))) ? USER_INFORMATIONAL_GRD_FIND_TEXT_NOTHING : USER_NOERROR);
			break;
		}
	}
}
VOID CGRDXmlView::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(GetRichEditCtrl().GetSelText(), FALSE, FALSE, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_GRD_FIND_TEXT_NOTHING : USER_NOERROR);
}
VOID CGRDXmlView::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(pszText, FALSE, bSearchAll, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_GRD_FIND_TEXT_NOTHING : USER_NOERROR);
}

BOOL CGRDXmlView::CanFindPrevious() CONST
{
	return(((IsWindow(m_dlgFind.GetSafeHwnd()) || !GetRichEditCtrl().GetSelText().IsEmpty()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CGRDXmlView::DoReplace()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgReplace.Create(GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CGRDXmlView::CanReplace() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CGRDXmlView::DoGoTo()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgGoTo.Create(GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CGRDXmlView::CanGoTo() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

BOOL CGRDXmlView::Search(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
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

BOOL CGRDXmlView::Replace(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
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

BOOL CGRDXmlView::ReplaceAll(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
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

BOOL CGRDXmlView::GoTo(UINT nLine, BOOL bDown, BOOL bUp)
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
BOOL CGRDXmlView::GoTo(LPCTSTR pszLine)
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

BOOL CGRDXmlView::IsModified() CONST
{
	CString  szXmlCode;

	GetWindowText(szXmlCode);
	return((m_szXmlCode.Compare(szXmlCode) != 0) ? TRUE : FALSE);
}

BOOL CGRDXmlView::Check() CONST
{
	return !IsEmpty();
}

CGRDWnd *CGRDXmlView::GetParent() CONST
{
	return((CGRDWnd *)CRichEditView::GetParent());
}

void CGRDXmlView::PostNcDestroy()
{
	return;
}

CString CGRDXmlView::ConstructXmlHeader() CONST
{
	return(CString(STRING(IDS_XMLHEADER_VERSION)) + CR + EOL + STRING(IDS_GRD_XMLHEADER_DOCTYPE) + CR + EOL + CR + EOL);
}

INT CGRDXmlView::CalculateXmlHeaderLength() CONST
{
	return(ConstructXmlHeader().GetLength() - 1 - 1 - 1);
}

BOOL CGRDXmlView::IsMouseOnXmlHeader(CONST POINT &point) CONST
{
	INT  nPos;

	return(((nPos = GetRichEditCtrl().CharFromPos(point)) >= 0 && nPos < CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CGRDXmlView, CRichEditView)
	//{{AFX_MSG_MAP(CGRDXmlView)
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
// CGRDXmlView drawing

void CGRDXmlView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CGRDXmlView message handlers

int CGRDXmlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

void CGRDXmlView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point)) SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
	CRichEditView::OnMouseMove(nFlags, point);
}

BOOL CGRDXmlView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	POINT  ptCursor;

	for (GetCursorPos(&ptCursor); IsMouseOnXmlHeader(ptCursor); )
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return TRUE;
	}
	return CRichEditView::OnSetCursor(pWnd, nHitTest, message);
}

void CGRDXmlView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnLButtonDown(nFlags, point);
}

void CGRDXmlView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnLButtonDblClk(nFlags, point);
}

void CGRDXmlView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnLButtonUp(nFlags, point);
}

void CGRDXmlView::OnMButtonDown(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnMButtonDown(nFlags, point);
}

void CGRDXmlView::OnMButtonUp(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnMButtonUp(nFlags, point);
}

void CGRDXmlView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnRButtonDown(nFlags, point);
}

void CGRDXmlView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnRButtonUp(nFlags, point);
}

void CGRDXmlView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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

void CGRDXmlView::OnEditchangeCode()
{
	CGRDXmlEdit::RenderCode(&GetRichEditCtrl(), &m_cCodeFont);
	GetParent()->UpdateBars();
}

void CGRDXmlView::OnEditupdateCode()
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
// CGRDWnd

IMPLEMENT_DYNCREATE(CGRDWnd, CDisplayWnd)

CGRDWnd::CGRDWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_GRD);
}
CGRDWnd::CGRDWnd(LPCTSTR pszName) : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_GRD);
	SetName(pszName);
}

BOOL CGRDWnd::Create(CMDIFrameWnd *pParentWnd, UINT nShow)
{
	return Create(pParentWnd, GetName(), nShow);
}
BOOL CGRDWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszName, UINT nShow)
{
	CRect  rPosition;

	for (SetName(pszName), rPosition = m_rPosition; CDisplayWnd::Create(pParentWnd, STRING(IDS_DISPLAY_TITLE_GRD), (nShow == (UINT)-1) ? CRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) : CRect(0, 0, 0, 0), IDR_GRDFRAME, (nShow != SW_SHOWMINIMIZED || nShow != SW_SHOWMAXIMIZED) ? (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE) : (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW)); )
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

VOID CGRDWnd::SetName(LPCTSTR pszName)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.SetName(pszName);
		return;
	}
	m_wndXmlView.SetName(pszName);
}

CString CGRDWnd::GetName() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.GetName() : m_wndXmlView.GetName());
}

VOID CGRDWnd::SetTitle(LPCTSTR pszTitle)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.SetTitle(GetName(), pszTitle);
		return;
	}
	m_wndXmlView.SetTitle(pszTitle);
}

CString CGRDWnd::GetTitle() CONST
{
	CString  szName;
	CString  szTitle;

	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? ((!m_wndTableView.GetTitle(szName, szTitle)) ? STRING(IDS_DISPLAY_TITLE_GRD) : szTitle) : ((m_wndXmlView.GetTitle().IsEmpty()) ? STRING(IDS_DISPLAY_TITLE_XML_GRD) : m_wndXmlView.GetTitle()));
}

BOOL CGRDWnd::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	return m_wndTableView.SetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CGRDWnd::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	return m_wndTableView.GetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CGRDWnd::IsNew() CONST
{
	return GetName().IsEmpty();
}

BOOL CGRDWnd::IsModified() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.Check() && m_wndTableView.IsModified()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.Check() && m_wndXmlView.IsModified())) ? TRUE : FALSE);
}

BOOL CGRDWnd::Save(INT nPosition) CONST
{
	UINT  nShowFlags;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	cProfile.DeleteDisplayWindowInfo(nPosition);
	return((cProfile.SetDisplayWindowType(nPosition, GetType()) && cProfile.SetDisplayWindowName(nPosition, GetName()) && cProfile.SetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, (nShowFlags = (!IsIconic()) ? ((!IsZoomed()) ? SW_SHOWNORMAL : SW_SHOWMAXIMIZED) : SW_SHOWMINIMIZED)) && (!GetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) || cProfile.SetGRDsFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]))) ? TRUE : FALSE);
}

INT CGRDWnd::Load(INT nPosition)
{
	UINT  nShowFlags;
	CString  szName;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	return((cProfile.GetDisplayWindowName(nPosition, szName) && cProfile.GetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, nShowFlags) && (!cProfile.GetGRDsFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) || SetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]))) ? CGRDWnd::Create(GetMainWnd(), szName, nShowFlags) : -1);
}

BOOL CGRDWnd::UpdateProperties()
{
	return((m_dlgProperties.DoModal(this) == IDOK) ? TRUE : FALSE);
}

BOOL CGRDWnd::IsUpdatingProperties() CONST
{
	return IsWindow(m_dlgProperties.GetSafeHwnd());
}

BOOL CGRDWnd::HasProperties() CONST
{
	return IsWindow(m_wndTableView.GetSafeHwnd());
}

BOOL CGRDWnd::CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.CheckTableDropTarget(pszTable, nComponent, point) : FALSE);
}

BOOL CGRDWnd::DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point)
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DropOnTableTarget(pszTable, nComponent, point) : FALSE);
}

VOID CGRDWnd::UpdateAllPanes(LPCTSTR pszDetails, LPCTSTR pszFlag, LPCTSTR pszType)
{
	m_wndStatusBar.SetPaneText(ID_GRD_STATUSBAR_DETAILSPANE, pszDetails);
	m_wndStatusBar.SetPaneText(ID_GRD_STATUSBAR_FLAGPANE, pszFlag);
	m_wndStatusBar.SetPaneText(ID_GRD_STATUSBAR_TYPEPANE, pszType);
}

BOOL CGRDWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
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
				if (PrintJob(cDC, STRING(IDS_DISPLAY_TITLE_GRD), cPrintProfileInfo.GetPrinterName(), rtMargin[0], bMetrics, nFlags))
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
					if (PrintJob(cDC, STRING(IDS_DISPLAY_TITLE_GRD), (LPCTSTR)pDevMode->dmDeviceName, rtMargin[0], bMetrics, nFlags, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : -1, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : -1))
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

VOID CGRDWnd::DoSave()
{
	INT  nPosition;
	CString  szMessage;

	if (IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.DoSave())
	{
		GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_GRD);
		return;
	}
	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		if ((nPosition = m_wndXmlView.DoSave()) >= 0)
		{
			GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_GRD);
			UpdateDatabase(this, nPosition);
			UpdateTitle();
			return;
		}
		szMessage.Format(STRING(IDS_GRD_FAILURE_SAVE), (LPCTSTR)GetTitle());
		ShowMessage(szMessage);
	}
}

BOOL CGRDWnd::CanSave() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanSave()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanSave())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

VOID CGRDWnd::DoSaveAs()
{
	INT  nResult;
	INT  nPosition;
	CString  szMessage;
	CString  szFileName;
	CGRDSaveDialog  cSaveDialog;

	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		if ((nResult = cSaveDialog.Create(this, szFileName)) == IDOK && (nPosition = m_wndXmlView.DoSaveAs(szFileName)) >= 0)
		{
			GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_GRD);
			UpdateDatabase(this, -(nPosition + 1));
			UpdateTitle();
			UpdateMenus();
			return;
		}
		if (nResult == IDOK)
		{
			szMessage.Format(STRING(IDS_GRD_FAILURE_SAVE), (LPCTSTR)GetTitle());
			ShowMessage(szMessage);
		}
	}
}

BOOL CGRDWnd::CanSaveAs() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanSaveAs()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

VOID CGRDWnd::DoCheck()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoCheck();
		return;
	}
}

BOOL CGRDWnd::CanCheck() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCheck()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

VOID CGRDWnd::DoDelete()
{
	INT  nPosition;
	CString  szName;
	CString  szTitle;
	CString  szMessage;

	for (szName = GetName(), szTitle = GetTitle(); IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.DoDelete(); )
	{
		GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_GRD);
		return;
	}
	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		for (szMessage.Format(STRING(IDS_GRD_QUESTION_DELETE), (LPCTSTR)GetTitle()); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES; )
		{
			if ((nPosition = m_wndXmlView.DoDelete()) >= 0)
			{
				GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_GRD);
				UpdateDatabase(this, nPosition, TRUE);
				DestroyWindow();
				return;
			}
			szMessage.Format(STRING(IDS_GRD_FAILURE_DELETE), (LPCTSTR)szTitle);
			ShowMessage(szMessage);
			break;
		}
	}
}

BOOL CGRDWnd::CanDelete() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDelete()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanDelete())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

VOID CGRDWnd::DoUndo()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoUndo();
		return;
	}
	m_wndXmlView.DoUndo();
}

BOOL CGRDWnd::CanUndo() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanUndo()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanUndo())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

VOID CGRDWnd::DoRedo()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoRedo();
		return;
	}
	m_wndXmlView.DoRedo();
}

BOOL CGRDWnd::CanRedo() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanRedo()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanRedo())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

VOID CGRDWnd::DoFind()
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFind();
}

BOOL CGRDWnd::CanFind() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanFind() : FALSE);
}

VOID CGRDWnd::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindNext(bMatchCase, bMatchWord);
}
VOID CGRDWnd::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindNext(pszText, bSearchAll, bMatchCase, bMatchWord);
}

BOOL CGRDWnd::CanFindNext() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanFindNext() : FALSE);
}

VOID CGRDWnd::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindPrevious(bMatchCase, bMatchWord);
}
VOID CGRDWnd::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindPrevious(pszText, bSearchAll, bMatchCase, bMatchWord);
}

BOOL CGRDWnd::CanFindPrevious() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanFindPrevious() : FALSE);
}

VOID CGRDWnd::DoReplace()
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoReplace();
}

BOOL CGRDWnd::CanReplace() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanReplace()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

VOID CGRDWnd::DoGoTo()
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoGoTo();
}

BOOL CGRDWnd::CanGoTo() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanGoTo() : FALSE);
}

VOID CGRDWnd::DoSelectAll()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoSelectAll();
		return;
	}
	m_wndXmlView.DoSelectAll();
}

BOOL CGRDWnd::CanSelectAll() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanSelectAll()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanSelectAll())) ? TRUE : FALSE);
}

VOID CGRDWnd::DoCutSel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoCutSel();
		return;
	}
	m_wndXmlView.DoCutSel();
}

BOOL CGRDWnd::CanCutSel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCutSel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanCutSel())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

VOID CGRDWnd::DoCopySel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoCopySel();
		return;
	}
	m_wndXmlView.DoCopySel();
}

BOOL CGRDWnd::CanCopySel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCopySel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanCopySel())) ? TRUE : FALSE);
}

VOID CGRDWnd::DoPasteSel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoPasteSel();
		return;
	}
	m_wndXmlView.DoPasteSel();
}

BOOL CGRDWnd::CanPasteSel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanPasteSel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanPaste())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

VOID CGRDWnd::DoDeleteSel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoDeleteSel();
		return;
	}
	m_wndXmlView.DoDeleteSel();
}

BOOL CGRDWnd::CanDeleteSel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteSel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanDeleteSel())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::CanPrint(UINT nFlags) CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanPrint(nFlags)) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanPrint())) ? TRUE : FALSE);
}

VOID CGRDWnd::DoClose()
{
	CString  szMessage;

	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoClose();
		return;
	}
	for (szMessage.Format(STRING(IDS_GRD_QUESTION_SAVE), (LPCTSTR)GetName()); CanSave(); )
	{
		if (MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES) DoSave();
		return;
	}
	if (IsNew())
	{
		for (szMessage = STRING(IDS_GRD_QUESTION_SAVEONCLOSE); CanSaveAs(); )
		{
			if (MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES) DoSaveAs();
			return;
		}
	}
}

BOOL CGRDWnd::DoSaveTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoSaveTable() : FALSE);
}

BOOL CGRDWnd::CanSaveTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanSaveTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoCheckTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoCheckTable() : FALSE);
}

BOOL CGRDWnd::CanCheckTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCheckTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoDeleteTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDeleteTable() : FALSE);
}

BOOL CGRDWnd::CanDeleteTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoPrintTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE) : FALSE);
}

BOOL CGRDWnd::CanPrintTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE) : FALSE);
}

BOOL CGRDWnd::DoPrintAllTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL) : FALSE);
}

BOOL CGRDWnd::CanPrintAllTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL) : FALSE);
}

BOOL CGRDWnd::DoImportTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoImportTables() : FALSE);
}

BOOL CGRDWnd::CanImportTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanImportTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoExportTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoExportTables() : FALSE);
}

BOOL CGRDWnd::CanExportTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.CanExportTables() : FALSE);
}

BOOL CGRDWnd::DoDiscardTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDiscardTables() : FALSE);
}

BOOL CGRDWnd::CanDiscardTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDiscardTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoDiscardAllTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDiscardAllTables() : FALSE);
}

BOOL CGRDWnd::CanDiscardAllTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDiscardAllTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoResetTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoResetTables() : FALSE);
}

BOOL CGRDWnd::CanResetTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanResetTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoInsertTableRowAbove()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableRowAbove() : FALSE);
}

BOOL CGRDWnd::CanInsertTableRowAbove() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableRowAbove()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoInsertTableRowBelow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableRowBelow() : FALSE);
}

BOOL CGRDWnd::CanInsertTableRowBelow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableRowBelow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoInsertTableColumnBefore()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableColumnBefore() : FALSE);
}

BOOL CGRDWnd::CanInsertTableColumnBefore() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableColumnBefore()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoInsertTableColumnAfter()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableColumnAfter() : FALSE);
}

BOOL CGRDWnd::CanInsertTableColumnAfter() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableColumnAfter()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoClearTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoClearTableRow() : FALSE);
}

BOOL CGRDWnd::CanClearTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanClearTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoDeleteTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDeleteTableRow() : FALSE);
}

BOOL CGRDWnd::CanDeleteTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoDeleteTableColumn()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDeleteTableColumn() : FALSE);
}

BOOL CGRDWnd::CanDeleteTableColumn() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteTableColumn()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

BOOL CGRDWnd::DoCopyTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoCopyTableRow() : FALSE);
}

BOOL CGRDWnd::CanCopyTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.CanCopyTableRow() : FALSE);
}

BOOL CGRDWnd::DoPasteTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoPasteTableRow() : FALSE);
}

BOOL CGRDWnd::CanPasteTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanPasteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE) : FALSE);
}

VOID CGRDWnd::GotoTable(ULONGLONG nComponent, LPCTSTR pszName)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.GotoTable(nComponent, pszName);
}

VOID CGRDWnd::UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE);
}
VOID CGRDWnd::UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE);
}
VOID CGRDWnd::UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE);
}
VOID CGRDWnd::UpdateTables(CONST CGRDLayouts &pLayouts)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(pLayouts);
}
VOID CGRDWnd::UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE, pLayout->GetName(), bDelete);
}
VOID CGRDWnd::UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CGRDWnd::UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.UpdateTables(nComponent, pszName, bDelete);
		m_wndTableView.ClearUndo();
	}
}
VOID CGRDWnd::UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.UpdateTables(nComponent, nID, bDelete);
		m_wndTableView.ClearUndo();
	}
}
VOID CGRDWnd::UpdateTables(ULONGLONG nComponent)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(nComponent);
}
VOID CGRDWnd::UpdateTables()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables();
}

BOOL CGRDWnd::Search(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.Search(pszText, bDown, bAll, bCase, bWord) : FALSE);
}

BOOL CGRDWnd::Replace(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.Replace(pszText, pszReplaceText, bDown, bAll, bCase, bWord) : FALSE);
}

BOOL CGRDWnd::ReplaceAll(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.ReplaceAll(pszText, pszReplaceText, bDown, bAll, bCase, bWord) : FALSE);
}

BOOL CGRDWnd::GoTo(UINT nLine, BOOL bDown, BOOL bUp)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.GoTo(nLine, bDown, bUp) : FALSE);
}
BOOL CGRDWnd::GoTo(LPCTSTR pszLine)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.GoTo(pszLine) : FALSE);
}

VOID CGRDWnd::UpdateBars()
{
	CString  szText;
	CStringTools  cStringTools;

	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		szText.Format(STRING(IDS_GRD_STATUSBAR_SIZE), (LPCTSTR)cStringTools.ConvertLongUIntToStructuredString(m_wndXmlView.GetWindowTextLength()));
		m_wndStatusBar.SetPaneText(ID_GRD_STATUSBAR_DETAILSPANE, szText);
	}
}

VOID CGRDWnd::UpdateTitle()
{
	INT  nPos;
	CString  szName;
	CString  szTitle[2];

	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		SetWindowText(STRING(IDS_DISPLAY_TITLE_GRD));
		return;
	}
	for (szName = GetName(), szTitle[0] = STRING(IDS_DISPLAY_TITLE_XML_GRD); szName.IsEmpty(); )
	{
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_WINDOW_UNTITLED), ((nPos = szTitle[0].ReverseFind(SPACE[0])) >= 0) ? (LPCTSTR)szTitle[0].Left(nPos) : (LPCTSTR)szTitle[0]);
		break;
	}
	for (szTitle[0] = GetTitle(); !szName.IsEmpty() && szTitle[0] == STRING(IDS_DISPLAY_TITLE_XML_GRD); )
	{
		szTitle[1].Format(STRING(IDS_DISPLAY_TITLE_XML_GRD), (LPCTSTR)szName);
		szTitle[0].Empty();
		break;
	}
	if (!szName.IsEmpty() && !szTitle[0].IsEmpty())
	{
		szTitle[0].Format(STRING(IDS_DISPLAY_TITLE_XML_GRD), (LPCTSTR)szName);
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), (LPCTSTR)GetTitle(), (LPCTSTR)szTitle[0]);
	}
	SetWindowText(szTitle[1]);
}

VOID CGRDWnd::UpdateMenus()
{
	GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
}

VOID CGRDWnd::UpdateStatusBar()
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

BOOL CGRDWnd::StartPrintJob(CDC &cDC)
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

BOOL CGRDWnd::PrintJob(CDC &cDC, LPCTSTR pszForm, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, WORD wFromPage, WORD wToPage)
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

BOOL CGRDWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndPage() >= 0 && cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CGRDWnd::DrawPrintDocPage(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CPtrArray &pFonts, LPRECT prClip, UINT nFlags, INT nPage, BOOL bCalc)
{
	return((DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(EMPTYSTRING, 0), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_TITLE), nFlags, bCalc) && DrawPrintDocInfoTitle(cDC, prClip, GetPrintDocInfoTitle(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_INFOTITLE), bCalc) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_LOGO), bCalc) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPage), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_FOOTER), bCalc)) ? TRUE : FALSE);
}

BOOL CGRDWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nFlags, BOOL bCalc)
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

CString CGRDWnd::GetPrintDocTitle(LPCTSTR pszName, UINT nFlags) CONST
{
	CGRDLayout  *pGRDLayout;

	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? (((pGRDLayout = (nFlags & DISPLAYTABLEVIEW_PRINT_TABLE) ? GetDatabase()->GetGRDs()->GetAt(GetDatabase()->GetGRDs()->Find(pszName)) : (CGRDLayout *)NULL) && !pGRDLayout->GetTitle().IsEmpty()) ? (LPCTSTR)pGRDLayout->GetTitle() : pszName) : GetTitle());
}

CString CGRDWnd::GetPrintDocInfoTitle() CONST
{
	INT  nPos;
	CString  szTitle[2];

	if (!IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		for (szTitle[0].Format(STRING(IDS_DISPLAY_TITLE_XML_GRD), (LPCTSTR)(szTitle[1] = GetName())); (nPos = (szTitle[1].IsEmpty()) ? szTitle[0].Find(SPACE) : -1) >= 0; )
		{
			szTitle[0] = szTitle[0].Left(nPos);
			break;
		}
		return szTitle[0];
	}
	return STRING(IDS_DISPLAY_TITLE_GRD);
}

INT CGRDWnd::Delete(LPCTSTR pszName)
{
	INT  nIndex;
	CGRDLayout  *pLayout;

	return(((pLayout = GetDatabase()->GetGRDs()->GetAt((nIndex = GetDatabase()->GetGRDs()->Find(pszName)))) && GetDatabase()->Delete(pLayout)) ? nIndex : -1);
}

VOID CGRDWnd::AdjustToPrivileges()
{
	if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_GRD_CHANGE))
	{
		if (IsWindow(m_wndTableView.GetSafeHwnd()))
		{
			m_wndTableView.UnSelectAll();
			return;
		}
		m_wndXmlView.UnSelectAll();
	}
}

BEGIN_MESSAGE_MAP(CGRDWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CGRDWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_GRD_STATUSBAR_DETAILSPANE, OnUpdateStatusBarDetailsPane)
	ON_UPDATE_COMMAND_UI(ID_GRD_STATUSBAR_FLAGPANE, OnUpdateStatusBarFlagPane)
	ON_UPDATE_COMMAND_UI(ID_GRD_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDWnd message handlers

int CGRDWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayWnd::OnCreate(lpCreateStruct) != -1 && LoadAccelTable(IDR_GRDFRAME)) ? 0 : -1);
}

BOOL CGRDWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	CRect  rBar;

	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1))
	{
		for (m_wndStatusBar.GetWindowRect(rBar); GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_GRD); ) return m_wndTableView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
		return m_wndXmlView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
	}
	return FALSE;
}

void CGRDWnd::OnSize(UINT nType, int cx, int cy)
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

void CGRDWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()) && !bActivate) m_wndTableView.UnSelectAll();
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CGRDWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()) && nChar == VK_DOWN) m_wndTableView.ActivateTable();
	CDisplayWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGRDWnd::OnClose()
{
	CHourglassCursor  cCursor;

	DoClose();
	CDisplayWnd::OnClose();
}

void CGRDWnd::OnUpdateStatusBarDetailsPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CGRDWnd::OnUpdateStatusBarFlagPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CGRDWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
