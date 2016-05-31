// TCSEQUENCE.CPP : Telecommand Sequence Form Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telecommand
// sequence form related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2005/06/05 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nStatusBarIndicators[] =
{
	ID_TCSEQUENCE_STATUSBAR_DETAILSPANE,
	ID_TCSEQUENCE_STATUSBAR_FLAGPANE,
	ID_TCSEQUENCE_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CTCSequenceSaveDialog dialog

IMPLEMENT_DYNCREATE(CTCSequenceSaveDialog, CDisplayDialog)

CTCSequenceSaveDialog::CTCSequenceSaveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCSequenceSaveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTCSequenceSaveDialog::Create(CWnd *pParentWnd, CString &szFileName)
{
	INT  nResult;

	for (szFileName.Empty(); (nResult = CDisplayDialog::Create(pParentWnd, CTCSequenceSaveDialog::IDD)) == IDOK; )
	{
		szFileName = m_szFileName;
		break;
	}
	return nResult;
}

BOOL CTCSequenceSaveDialog::Initialize()
{
	m_pDatabaseTCSequences.Copy(GetDatabase()->GetTCSequences());
	m_szFileName.Empty();
	return TRUE;
}

CTCSequenceWnd *CTCSequenceSaveDialog::GetParentDisplay() CONST
{
	return((CTCSequenceWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CTCSequenceSaveDialog::EnumTCSequences()
{
	INT  nColumn;
	INT  nColumns;
	INT  nSequence;
	INT  nSequences;
	CString  szItem;
	CStringTools  cStringTools;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	for (nSequence = 0, nSequences = (INT)m_pDatabaseTCSequences.GetSize(); nSequence < nSequences; nSequence++)
	{
		if ((pDatabaseTCSequence = m_pDatabaseTCSequences.GetAt(nSequence)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCESAVEDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pDatabaseTCSequence->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCESAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCSequence->GetDescription();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCESAVEDIALOG_DIRECTORYTITLEITEM_LOCATION); )
				{
					szItem = pDatabaseTCSequence->GetFileName();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCSEQUENCE_SAVE_DIRECTORY), nSequence, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCSEQUENCE_SAVE_DIRECTORY), nSequence, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_TCSEQUENCE_SAVE_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_SAVE_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_SAVE_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_SAVE_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCSequenceSaveDialog::FindTCSequence(LPCTSTR pszName) CONST
{
	INT  nSequence;
	INT  nSequences;

	for (nSequence = 0, nSequences = (INT)m_pDatabaseTCSequences.GetSize(); nSequence < nSequences; nSequence++)
	{
		if (m_pDatabaseTCSequences.GetAt(nSequence)->GetName() == pszName) break;
		continue;
	}
	return((nSequence < nSequences) ? TRUE : FALSE);
}

BOOL CTCSequenceSaveDialog::CheckFileName(LPCTSTR pszFileName) CONST
{
	INT  nSequence;
	INT  nSequences;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	for (nSequence = 0, nSequences = (INT)m_pDatabaseTCSequences.GetSize(); nSequence < nSequences; nSequence++)
	{
		if ((pDatabaseTCSequence = m_pDatabaseTCSequences.GetAt(nSequence)) && !pDatabaseTCSequence->GetFileName().CompareNoCase(pszFileName)) break;
		continue;
	}
	return((nSequence == nSequences) ? TRUE : FALSE);
}

BOOL CTCSequenceSaveDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TCSEQUENCE_SAVE_FILENAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CTCSequenceSaveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCSequenceSaveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCSequenceSaveDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTCSequences.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCSequenceSaveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCSequenceSaveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCSEQUENCE_SAVE_FILENAME_BROWSE, OnBrowseFileName)
	ON_BN_CLICKED(IDC_TCSEQUENCE_SAVE_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TCSEQUENCE_SAVE_FILENAME, OnEditchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceSaveDialog message handlers

BOOL CTCSequenceSaveDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TCSEQUENCE_SAVE_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCSEQUENCESAVEDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCSEQUENCESAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_TCSEQUENCESAVEDIALOG_DIRECTORYTITLEITEM_LOCATION));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_TCSEQUENCE_SAVE_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT), rColumns.DeflateRect(0, 0, GetSystemMetrics(SM_CXVSCROLL), 0); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCSEQUENCE_SAVE_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCESAVEDIALOG_DIRECTORYTITLEITEM_NAME)) ? (rColumns.Width() / 4) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCESAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION)) ? (rColumns.Width() / 2) : (3 * rColumns.Width()) / 4));
		continue;
	}
	EnumTCSequences();
	GetDlgItem(IDC_TCSEQUENCE_SAVE_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_TCSEQUENCE_SAVE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_SAVE_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_SAVE_DATABASE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_SAVE_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_SAVE_FILENAME)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_SAVE_FILENAME_BROWSE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_SAVE_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return FALSE;
}

BOOL CTCSequenceSaveDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nColumn;
	INT  nColumns;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCSEQUENCE_SAVE_DIRECTORY)
	{
		if (pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK)
		{
			for (nColumn = 0, nColumns = (pNotifyListView->iItem >= 0) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
			{
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCESAVEDIALOG_DIRECTORYTITLEITEM_LOCATION)) break;
				continue;
			}
			if (pNotifyListView->iItem < 0)
			{
				Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
				SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
				return TRUE;
			}
			GetDlgItem(IDC_TCSEQUENCE_SAVE_FILENAME)->SetWindowText(Listview_GetText(GetDlgItem(IDC_TCSEQUENCE_SAVE_DIRECTORY), pNotifyListView->iItem, nColumn));
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CTCSequenceSaveDialog::OnBrowseFileName()
{
	BOOL  bFileName;
	CString  szFileName;
	CFileBrowseDialog  *pFileBrowseDialog;

	if ((pFileBrowseDialog = new CFileBrowseDialog(this, szFileName, STRING(IDS_FILEBROWSEDIALOG_DATABASEXMLFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEXMLFILTER))) && pFileBrowseDialog->DoModal() == IDOK)
	{
		GetDlgItem(IDC_TCSEQUENCE_SAVE_FILENAME)->SetWindowText((szFileName = pFileBrowseDialog->GetPathName()));
		GetDlgItem(IDC_TCSEQUENCE_SAVE_COMMENT_STATIC)->ShowWindow(((bFileName = !CheckFileName(szFileName))) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_TCSEQUENCE_SAVE_COMMENT)->ShowWindow((bFileName) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_TCSEQUENCE_SAVE_COMMENT_STATIC)->EnableWindow(bFileName);
		GetDlgItem(IDC_TCSEQUENCE_SAVE_COMMENT)->EnableWindow(bFileName);
	}
	delete pFileBrowseDialog;
	SendDlgItemMessage(IDC_TCSEQUENCE_SAVE_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TCSEQUENCE_SAVE_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceSaveDialog::OnEditchangeFileName()
{
	BOOL  bFileName;
	CString  szFileName;

	GetDlgItem(IDC_TCSEQUENCE_SAVE_FILENAME)->GetWindowText(szFileName);
	GetDlgItem(IDC_TCSEQUENCE_SAVE_COMMENT_STATIC)->ShowWindow(((bFileName = !CheckFileName(szFileName))) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCSEQUENCE_SAVE_COMMENT)->ShowWindow((bFileName) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_TCSEQUENCE_SAVE_COMMENT_STATIC)->EnableWindow(bFileName);
	GetDlgItem(IDC_TCSEQUENCE_SAVE_COMMENT)->EnableWindow(bFileName);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceSaveDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCSEQUENCE_SAVE_FILENAME)->GetWindowText(m_szFileName);
	CDisplayDialog::OnOK();
}

BOOL CTCSequenceSaveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCESAVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCSequenceSaveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCESAVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceOpenDialog dialog

IMPLEMENT_DYNCREATE(CTCSequenceOpenDialog, CLocaleDialog)

CTCSequenceOpenDialog::CTCSequenceOpenDialog(CWnd *pParentWnd) : CLocaleDialog(CTCSequenceOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCSequenceOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCSequenceOpenDialog::Initialize()
{
	m_pDatabaseTCSequences.Copy(GetDatabase()->GetTCSequences());
	return TRUE;
}

VOID CTCSequenceOpenDialog::EnumTCSequences()
{
	INT  nColumn;
	INT  nColumns;
	INT  nSequence;
	INT  nSequences;
	CString  szItem;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	for (nSequence = 0, nSequences = (INT)m_pDatabaseTCSequences.GetSize(); nSequence < nSequences; nSequence++)
	{
		if ((pDatabaseTCSequence = m_pDatabaseTCSequences.GetAt(nSequence)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCEOPENDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pDatabaseTCSequence->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCEOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCSequence->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY), nSequence, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY), nSequence, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY), 0);
	GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CTCSequenceOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void CTCSequenceOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCSequenceOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCSequenceOpenDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTCSequences.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCSequenceOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCSequenceOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCSEQUENCE_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceOpenDialog message handlers

BOOL CTCSequenceOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCSEQUENCEOPENDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCSEQUENCEOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TCSEQUENCE_OPEN_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (2 * rColumns.Width()) / 9; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumTCSequences();
	GetDlgItem(IDC_TCSEQUENCE_OPEN_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_TCSEQUENCE_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_OPEN_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_OPEN_DATABASE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY)->SetFocus();
	return FALSE;
}

BOOL CTCSequenceOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCSEQUENCE_OPEN_DIRECTORY)
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

void CTCSequenceOpenDialog::OnOK()
{
	INT  nColumn;
	INT  nColumns;
	INT  nDisplay;
	INT  nDisplays;
	CString  szTag;
	CString  szMessage;
	CString  szDescription;
	CPtrArray  pDisplays;
	CDisplayWnd  *pDisplayWnd;
	CTCSequenceWnd  *pTCSequenceWnd;
	CHourglassCursor  cCursor;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCEOPENDIALOG_DIRECTORYTITLEITEM_NAME))
		{
			szTag = Listview_GetText(GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY)), nColumn);
			continue;
		}
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCEOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
		{
			szDescription = Listview_GetText(GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_TCSEQUENCE_OPEN_DIRECTORY)), nColumn);
			continue;
		}
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCSEQUENCE)
		{
			if ((pTCSequenceWnd = (CTCSequenceWnd *)pDisplayWnd)->GetName() == szTag)
			{
				pTCSequenceWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		if ((pTCSequenceWnd = new CTCSequenceWnd(szTag)))
		{
			if (pTCSequenceWnd->Create(GetMainWnd()))
			{
				EndDialog(IDOK);
				return;
			}
		}
		szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_LOAD), (LPCTSTR)szDescription);
		ShowMessage(szMessage);
	}
	EndDialog(IDOK);
}

void CTCSequenceOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCSequenceOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCSequenceOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceImportDialog dialog

IMPLEMENT_DYNCREATE(CTCSequenceImportDialog, CLocaleDialog)

CTCSequenceImportDialog::CTCSequenceImportDialog(CWnd *pParentWnd) : CLocaleDialog(CTCSequenceImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCSequenceImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CTCSequenceImportDialog::DoModal(CDatabaseTCSequences &pDatabaseTCSequences)
{
	INT_PTR  nResult;

	for (m_pDatabaseTCSequences.RemoveAll(); (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCSequences.Copy(&m_pDatabaseTCSequences);
		break;
	}
	return nResult;
}

VOID CTCSequenceImportDialog::EnumTCSequences()
{
	INT  nColumn;
	INT  nColumns;
	INT  nSequence;
	INT  nSequences;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szItem;
	CString  szFileName;
	CByteArray  cFileBuffer;
	CFileFindEx  cFileFind;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	SendDlgItemMessage(IDC_TCSEQUENCE_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				for (nSequence = 0, nSequences = (m_pDatabaseTCSequences.Unmap(cFileBuffer, FALSE)) ? (INT)m_pDatabaseTCSequences.GetSize() : 0; nSequence < nSequences; nSequence++)
				{
					if ((pDatabaseTCSequence = m_pDatabaseTCSequences.GetAt(nSequence)))
					{
						for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCEIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
							{
								szItem = pDatabaseTCSequence->GetName();
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCEIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
							{
								szItem = pDatabaseTCSequence->GetDescription();
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_TCSEQUENCE_IMPORT_DIRECTORY), nSequence, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_TCSEQUENCE_IMPORT_DIRECTORY), nSequence, nColumn, szItem);
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
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCSequenceImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TCSEQUENCE_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCSEQUENCE_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_TCSEQUENCE_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CTCSequenceImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCSequenceImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCSequenceImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCSequenceImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCSequenceImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCSEQUENCE_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_TCSEQUENCE_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_TCSEQUENCE_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TCSEQUENCE_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceImportDialog message handlers

BOOL CTCSequenceImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_TCSEQUENCEIMPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCSEQUENCEIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TCSEQUENCE_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME, EM_LIMITTEXT, GetDatabase()->GetTCSequenceNameLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCSEQUENCE_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_TCSEQUENCE_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CTCSequenceImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCSEQUENCE_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_TCSEQUENCE_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM)->EnableWindow();
			}
			else
			{
				CheckDlgButton(IDC_TCSEQUENCE_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CTCSequenceImportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TCSEQUENCE_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_TCSEQUENCE_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumTCSequences();
	}
	SendDlgItemMessage(IDC_TCSEQUENCE_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceImportDialog::OnDefault()
{
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceImportDialog::OnCustom()
{
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceImportDialog::OnEditchangeFileName()
{
	EnumTCSequences();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceImportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceImportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceImportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nSequence;
	INT  nSequences;
	CString  szName;
	CString  szDescription;
	CPtrArray  pSequences;
	CUIntArray  nSequenceIDs;
	CDatabaseTCSequence  *pDatabaseTCSequence[2];
	CDatabaseTCSequences  pDatabaseTCSequences;
	CHourglassCursor  cCursor;

	for (nSequence = 0, nSequences = (INT)SendDlgItemMessage(IDC_TCSEQUENCE_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nSequence < nSequences; nSequence++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_TCSEQUENCE_IMPORT_DIRECTORY), nSequence))
		{
			delete m_pDatabaseTCSequences.GetAt(nSequence);
			m_pDatabaseTCSequences.SetAt(nSequence, NULL);
		}
	}
	for (nSequence = 0, nSequences = (pDatabaseTCSequences.Copy(GetDatabase()->GetTCSequences())) ? nSequences : -1; nSequence < nSequences; nSequence++)
	{
		if ((pDatabaseTCSequence[0] = m_pDatabaseTCSequences.GetAt(nSequence)))
		{
			if (IsDlgButtonChecked(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM))
			{
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
				GetDlgItem(IDC_TCSEQUENCE_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
				pDatabaseTCSequence[0]->SetDescription(szDescription);
				pDatabaseTCSequence[0]->SetName(szName);
			}
			if ((pDatabaseTCSequence[1] = pDatabaseTCSequences.GetAt((nIndex = pDatabaseTCSequences.Find(pDatabaseTCSequence[0]->GetName())))))
			{
				pDatabaseTCSequence[1]->Copy(pDatabaseTCSequence[0]);
				pSequences.Add(pDatabaseTCSequence[1]);
				nSequenceIDs.Add(nIndex);
				continue;
			}
			if ((pDatabaseTCSequence[1] = new CDatabaseTCSequence))
			{
				pDatabaseTCSequence[1]->Copy(pDatabaseTCSequence[0]);
				if ((nIndex = pDatabaseTCSequences.Add(pDatabaseTCSequence[1])) >= 0)
				{
					pSequences.Add(pDatabaseTCSequence[1]);
					nSequenceIDs.Add(-(nIndex + 1));
					continue;
				}
				delete pDatabaseTCSequence[1];
			}
			break;
		}
		m_pDatabaseTCSequences.RemoveAt(nSequence);
		nSequences--;
		nSequence--;
	}
	for (; nSequence == nSequences; )
	{
		if (GetDatabase()->GetTCSequences()->Copy(&pDatabaseTCSequences))
		{
			for (nItem = 0, nItems = (INT)pSequences.GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTCSequence[0] = (CDatabaseTCSequence *)pSequences.GetAt(nItem)))
				{
					if (GetDatabase()->Save(pDatabaseTCSequence[0]))
					{
						nIndex = (INT)nSequenceIDs.GetAt(nItem);
						UpdateDatabase(pDatabaseTCSequence[0], nIndex);
						continue;
					}
				}
				break;
			}
			if (nItem == nItems) break;
		}
		nSequences = -1;
		break;
	}
	for (; nSequence != nSequences; )
	{
		ShowMessage((SendDlgItemMessage(IDC_TCSEQUENCE_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_TCSEQUENCEDIRECTORY_IMPORT_FAILURE : SYSTEM_WARNING_TCSEQUENCE_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CTCSequenceImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCSequenceImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCSequenceImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceExportDialog dialog

IMPLEMENT_DYNCREATE(CTCSequenceExportDialog, CLocaleDialog)

CTCSequenceExportDialog::CTCSequenceExportDialog(CWnd *pParentWnd) : CLocaleDialog(CTCSequenceExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCSequenceExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CTCSequenceExportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

BOOL CTCSequenceExportDialog::EnumTCSequences()
{
	INT  nColumn;
	INT  nColumns;
	INT  nSequence;
	INT  nSequences;
	CString  szItem;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	for (nSequence = 0, nSequences = (m_pDatabaseTCSequences.Copy(GetDatabase()->GetTCSequences())) ? (INT)m_pDatabaseTCSequences.GetSize() : 0; nSequence < nSequences; nSequence++)
	{
		if ((pDatabaseTCSequence = m_pDatabaseTCSequences.GetAt(nSequence)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCEEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pDatabaseTCSequence->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCSEQUENCEEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCSequence->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCSEQUENCE_EXPORT_DIRECTORY), nSequence, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCSEQUENCE_EXPORT_DIRECTORY), nSequence, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCSEQUENCE_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCSequenceExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TCSEQUENCE_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCSEQUENCE_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_TCSEQUENCE_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CTCSequenceExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCSequenceExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCSequenceExportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTCSequences.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCSequenceExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCSequenceExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCSEQUENCE_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_TCSEQUENCE_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_TCSEQUENCE_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TCSEQUENCE_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceExportDialog message handlers

BOOL CTCSequenceExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_TCSEQUENCEEXPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCSEQUENCEEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TCSEQUENCE_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME, EM_LIMITTEXT, GetDatabase()->GetTCSequenceNameLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCSEQUENCE_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumTCSequences())
	{
		CheckDlgButton(IDC_TCSEQUENCE_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_TCSEQUENCE_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TCSEQUENCE_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCSEQUENCE_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_TCSEQUENCE_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM)->EnableWindow();
		GetDlgItem(IDC_TCSEQUENCE_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL CTCSequenceExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCSEQUENCE_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_TCSEQUENCE_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM)->EnableWindow();
				CheckDlgButton(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM, FALSE);
			}
			else
			{
				CheckDlgButton(IDC_TCSEQUENCE_EXPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CTCSequenceExportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TCSEQUENCE_EXPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_TCSEQUENCE_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_TCSEQUENCE_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceExportDialog::OnDefault()
{
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceExportDialog::OnCustom()
{
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceExportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceExportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceExportDialog::OnOK()
{
	INT  nSequence;
	INT  nSequences;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szName;
	CString  szFileName;
	CString  szDescription;
	CByteArray  cFileBuffer;
	CDatabaseTCSequence  *pDatabaseTCSequence;
	CHourglassCursor  cCursor;

	for (nSequence = 0, nSequences = (INT)SendDlgItemMessage(IDC_TCSEQUENCE_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nSequence < nSequences; nSequence++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_TCSEQUENCE_EXPORT_DIRECTORY), nSequence))
		{
			delete m_pDatabaseTCSequences.GetAt(nSequence);
			m_pDatabaseTCSequences.SetAt(nSequence, NULL);
		}
	}
	for (nSequence = 0; nSequence < nSequences; nSequence++)
	{
		if (!m_pDatabaseTCSequences.GetAt(nSequence))
		{
			m_pDatabaseTCSequences.RemoveAt(nSequence);
			nSequences--;
			nSequence--;
		}
	}
	if ((pDatabaseTCSequence = (IsDlgButtonChecked(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCSequences.GetAt(nSequence) : (CDatabaseTCSequence *)NULL))
	{
		GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
		GetDlgItem(IDC_TCSEQUENCE_EXPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
		pDatabaseTCSequence->SetDescription(szDescription);
		pDatabaseTCSequence->SetName(szName);
	}
	for (; nSequence == nSequences; )
	{
		if (m_pDatabaseTCSequences.Map(cFileBuffer, FALSE))
		{
			GetDlgItem(IDC_TCSEQUENCE_EXPORT_FILENAME)->GetWindowText(szFileName);
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
		nSequences = -1;
		break;
	}
	for (; nSequence != nSequences; )
	{
		ShowMessage((SendDlgItemMessage(IDC_TCSEQUENCE_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_TCSEQUENCEDIRECTORY_EXPORT_FAILURE : SYSTEM_WARNING_TCSEQUENCE_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CTCSequenceExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCSequenceExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCSequenceExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequencePropertiesDialog dialog

IMPLEMENT_DYNCREATE(CTCSequencePropertiesDialog, CLocaleDialog)

CTCSequencePropertiesDialog::CTCSequencePropertiesDialog(CWnd *pParentWnd) : CLocaleDialog(CTCSequencePropertiesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCSequencePropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCSequencePropertiesDialog::Initialize()
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

INT_PTR CTCSequencePropertiesDialog::DoModal(CTCSequenceWnd *pParentWnd)
{
	INT_PTR  nResult;

	for (m_pParentWnd = (CWnd *)pParentWnd; (nResult = CLocaleDialog::DoModal()); ) break;
	return nResult;
}

VOID CTCSequencePropertiesDialog::ShowFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_RESETCONTENT); (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE) && cFontTools.EnumerateFont(m_lfTable[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_ITEMS) && cFontTools.EnumerateFont(m_lfTable[0][1].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE))
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][0])), 0));
		SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][0])), max(SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][0])), 0)));
		SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_ITEMS))
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][1])), 0));
		SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][1])), max(SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][1])), 0)));
		SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]);
	}
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCSequencePropertiesDialog::ShowFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

CTCSequenceWnd *CTCSequencePropertiesDialog::GetParent() CONST
{
	return((CTCSequenceWnd *)CLocaleDialog::GetParent());
}

BOOL CTCSequencePropertiesDialog::IsModified() CONST
{
	CFontTools  cFontTools;

	return((lstrcmp(m_lfTable[0][0].lfFaceName, m_lfTable[1][0].lfFaceName) || (m_lfTable[0][0].lfHeight != m_lfTable[1][0].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][0]))) || m_lfTable[0][0].lfWeight != m_lfTable[1][0].lfWeight || m_lfTable[0][0].lfItalic != m_lfTable[1][0].lfItalic || lstrcmp(m_lfTable[0][1].lfFaceName, m_lfTable[1][1].lfFaceName) || (m_lfTable[0][1].lfHeight != m_lfTable[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][1])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][1]))) || m_lfTable[0][1].lfWeight != m_lfTable[1][1].lfWeight || m_lfTable[0][1].lfItalic != m_lfTable[1][1].lfItalic || GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]) != GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][0]) || GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]) != GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][1]) || GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]) != GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][0]) || GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]) != GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][1])) ? TRUE : FALSE);
}

BOOL CTCSequencePropertiesDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void CTCSequencePropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCSequencePropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCSequencePropertiesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCSequencePropertiesDialog)
	ON_WM_PAINT()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_TCSEQUENCE_PROPERTIES_FONTS_ITEMS, OnItemsFont)
	ON_BN_CLICKED(IDC_TCSEQUENCE_PROPERTIES_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR, OnSelchangeFontColor)
	ON_CBN_SELCHANGE(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE, OnSelchangeTitleBackgroundColor)
	ON_CBN_SELCHANGE(IDC_TCSEQUENCE_PROPERTIES_COLORS_KEYS, OnSelchangeKeysBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequencePropertiesDialog message handlers

BOOL CTCSequencePropertiesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	CheckDlgButton(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE, TRUE);
	CheckDlgButton(IDC_TCSEQUENCE_PROPERTIES_FONTS_ITEMS, FALSE);
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_COLORS_KEYS, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_COLORS_KEYS, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]);
	SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_COLORS_KEYS, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]);
	AccessControl(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE));
	AccessControl(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE));
	AccessControl(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE));
	AccessControl(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE));
	AccessControl(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE));
	AccessControl(IDC_TCSEQUENCE_PROPERTIES_COLORS_KEYS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE));
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_ITEMS)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_COLORS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_COLORS_KEYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_COLORS_KEYS)->EnableWindow();
	ShowFontDetails();
	return TRUE;
}

void CTCSequencePropertiesDialog::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE)) ? &m_lfTable[0][0] : &m_lfTable[0][1]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE)) ? m_nTableFontColors[0][0] : m_nTableFontColors[0][1]) : GetSysColor(COLOR_GRAYTEXT));
			cDC.FillSolidRect(rSampleText, (SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE)) ? m_nTableColors[0][0] : GetSysColor(COLOR_3DFACE)) : GetSysColor(COLOR_3DFACE));
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

void CTCSequencePropertiesDialog::OnTitleFont()
{
	SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CTCSequencePropertiesDialog::OnItemsFont()
{
	SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][1].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CTCSequencePropertiesDialog::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequencePropertiesDialog::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE))
	{
		lstrcpy(m_lfTable[0][0].lfFaceName, Combobox_GetText(GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_ITEMS))
	{
		lstrcpy(m_lfTable[0][1].lfFaceName, Combobox_GetText(GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][1]);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequencePropertiesDialog::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequencePropertiesDialog::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TCSEQUENCE_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequencePropertiesDialog::OnSelchangeFontColor()
{
	for (; IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_TITLE); )
	{
		m_nTableFontColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	for (; IsDlgButtonChecked(IDC_TCSEQUENCE_PROPERTIES_FONTS_ITEMS); )
	{
		m_nTableFontColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequencePropertiesDialog::OnSelchangeTitleBackgroundColor()
{
	for (m_nTableColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_COLORS_TITLE, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequencePropertiesDialog::OnSelchangeKeysBackgroundColor()
{
	for (m_nTableColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_COLORS_KEYS, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCSEQUENCE_PROPERTIES_COLORS_KEYS, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequencePropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParent()->SetProperties(&m_lfTable[0][0], &m_lfTable[0][1], m_nTableFontColors[0][0], m_nTableFontColors[0][1], m_nTableColors[0][0], m_nTableColors[0][1]);
	EndDialog(IDOK);
}

void CTCSequencePropertiesDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCSequencePropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCSequencePropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceFindDialog dialog

IMPLEMENT_DYNCREATE(CTCSequenceFindDialog, CDisplayDialog)

CTCSequenceFindDialog::CTCSequenceFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCSequenceFindDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCSequenceFindDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCSequenceFindDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCSequenceWnd *CTCSequenceFindDialog::GetParent() CONST
{
	return((CTCSequenceWnd *)CDisplayDialog::GetParent());
}

void CTCSequenceFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCSequenceFindDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCSequenceFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCSequenceFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCSEQUENCE_FIND_NEXT, OnFindText)
	ON_BN_CLICKED(IDC_TCSEQUENCE_FIND_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCSEQUENCE_FIND_TEXT, OnSelchangeText)
	ON_CBN_EDITCHANGE(IDC_TCSEQUENCE_FIND_TEXT, OnEditchangeText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceFindDialog message handlers

BOOL CTCSequenceFindDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	BOOL  bFindDefaults[4];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szSearchItems.GetSize(), GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_FIND_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szSearchItems.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_TCSEQUENCE_FIND_DIRECTION_DOWN, bFindDefaults[0]);
	CheckDlgButton(IDC_TCSEQUENCE_FIND_DIRECTION_UP, !bFindDefaults[0]);
	CheckDlgButton(IDC_TCSEQUENCE_FIND_ALL, bFindDefaults[1]);
	CheckDlgButton(IDC_TCSEQUENCE_FIND_CASE, bFindDefaults[2]);
	CheckDlgButton(IDC_TCSEQUENCE_FIND_WORD, bFindDefaults[3]);
	GetDlgItem(IDC_TCSEQUENCE_FIND_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_FIND_TEXT)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_FIND_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_FIND_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_FIND_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_FIND_ALL)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_FIND_CASE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_FIND_WORD)->EnableWindow();
	return TRUE;
}

void CTCSequenceFindDialog::OnFindText()
{
	CString  szText;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TCSEQUENCE_FIND_TEXT)->GetWindowText(szText); SendDlgItemMessage(IDC_TCSEQUENCE_FIND_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText) == CB_ERR; )
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_FIND_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText);
		m_szSearchItems.Add(szText);
		break;
	}
	if (!GetParent()->Search(szText, IsDlgButtonChecked(IDC_TCSEQUENCE_FIND_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCSEQUENCE_FIND_ALL), IsDlgButtonChecked(IDC_TCSEQUENCE_FIND_CASE), IsDlgButtonChecked(IDC_TCSEQUENCE_FIND_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_TCSEQUENCE_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
		return;
	}
	CheckDlgButton(IDC_TCSEQUENCE_FIND_ALL, FALSE);
}

void CTCSequenceFindDialog::OnSelchangeText()
{
	GetDlgItem(IDC_TCSEQUENCE_FIND_NEXT)->EnableWindow((SendDlgItemMessage(IDC_TCSEQUENCE_FIND_TEXT, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CTCSequenceFindDialog::OnEditchangeText()
{
	GetDlgItem(IDC_TCSEQUENCE_FIND_NEXT)->EnableWindow((GetDlgItem(IDC_TCSEQUENCE_FIND_TEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CTCSequenceFindDialog::OnCancel()
{
	GetParent()->SetFocus();
	CDisplayDialog::OnCancel();
}

BOOL CTCSequenceFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCSequenceFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceReplaceDialog dialog

IMPLEMENT_DYNCREATE(CTCSequenceReplaceDialog, CDisplayDialog)

CTCSequenceReplaceDialog::CTCSequenceReplaceDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCSequenceReplaceDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCSequenceReplaceDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCSequenceReplaceDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCSequenceWnd *CTCSequenceReplaceDialog::GetParent() CONST
{
	return((CTCSequenceWnd *)CDisplayDialog::GetParent());
}

void CTCSequenceReplaceDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCSequenceReplaceDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCSequenceReplaceDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCSequenceReplaceDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCSEQUENCE_REPLACE_FINDNEXT, OnFindNextText)
	ON_BN_CLICKED(IDC_TCSEQUENCE_REPLACE_NEXT, OnReplaceText)
	ON_BN_CLICKED(IDC_TCSEQUENCE_REPLACE_ALLNEXT, OnReplaceAllText)
	ON_BN_CLICKED(IDC_TCSEQUENCE_REPLACE_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TCSEQUENCE_REPLACE_FINDTEXT, OnSelchangeFindText)
	ON_CBN_EDITCHANGE(IDC_TCSEQUENCE_REPLACE_FINDTEXT, OnEditchangeFindText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceReplaceDialog message handlers

BOOL CTCSequenceReplaceDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szItems[0].GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szItems[0].GetAt(nItem));
		continue;
	}
	for (nItem = 0, nItems = (INT)m_szItems[1].GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szItems[1].GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_TCSEQUENCE_REPLACE_ALL, TRUE);
	CheckDlgButton(IDC_TCSEQUENCE_REPLACE_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_TEXT)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_ALL)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_CASE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_WORD)->EnableWindow();
	return TRUE;
}

void CTCSequenceReplaceDialog::OnFindNextText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->Search(szText[0], IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_ALL), IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_CASE), IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_TCSEQUENCE_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
		return;
	}
	CheckDlgButton(IDC_TCSEQUENCE_REPLACE_ALL, FALSE);
}

void CTCSequenceReplaceDialog::OnReplaceText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->Replace(szText[0], szText[1], IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_ALL), IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_CASE), IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_TCSEQUENCE_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
	}
}

void CTCSequenceReplaceDialog::OnReplaceAllText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_TCSEQUENCE_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->ReplaceAll(szText[0], szText[1], IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_ALL), IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_CASE), IsDlgButtonChecked(IDC_TCSEQUENCE_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_TCSEQUENCE_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
	}
}

void CTCSequenceReplaceDialog::OnSelchangeFindText()
{
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDNEXT)->EnableWindow((GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_NEXT)->EnableWindow((GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_ALLNEXT)->EnableWindow((GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CTCSequenceReplaceDialog::OnEditchangeFindText()
{
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDNEXT)->EnableWindow((GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_NEXT)->EnableWindow((GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCSEQUENCE_REPLACE_ALLNEXT)->EnableWindow((GetDlgItem(IDC_TCSEQUENCE_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CTCSequenceReplaceDialog::OnCancel()
{
	GetParent()->SetFocus();
	CDisplayDialog::OnCancel();
}

BOOL CTCSequenceReplaceDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEREPLACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCSequenceReplaceDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEREPLACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceGoToDialog dialog

IMPLEMENT_DYNCREATE(CTCSequenceGoToDialog, CDisplayDialog)

CTCSequenceGoToDialog::CTCSequenceGoToDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTCSequenceGoToDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCSequenceGoToDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CTCSequenceGoToDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CTCSequenceWnd *CTCSequenceGoToDialog::GetParent() CONST
{
	return((CTCSequenceWnd *)CDisplayDialog::GetParent());
}

BOOL CTCSequenceGoToDialog::Check(BOOL bModified) CONST
{
	return(((IsDlgButtonChecked(IDC_TCSEQUENCE_GOTO_LINE) && GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->GetWindowTextLength() > 0) || IsDlgButtonChecked(IDC_TCSEQUENCE_GOTO_JUMPDOWN) || IsDlgButtonChecked(IDC_TCSEQUENCE_GOTO_JUMPUP)) ? TRUE : FALSE);
}

void CTCSequenceGoToDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCSequenceGoToDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCSequenceGoToDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTCSequenceGoToDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCSEQUENCE_GOTO_LINE, OnLineNumber)
	ON_BN_CLICKED(IDC_TCSEQUENCE_GOTO_JUMPDOWN, OnJumpLineDown)
	ON_BN_CLICKED(IDC_TCSEQUENCE_GOTO_JUMPUP, OnJumpLineUp)
	ON_BN_CLICKED(IDC_TCSEQUENCE_GOTO_JUMP, OnJump)
	ON_BN_CLICKED(IDC_TCSEQUENCE_GOTO_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TCSEQUENCE_GOTO_LINENUMBER, OnEditchangeLineNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceGoToDialog message handlers

BOOL CTCSequenceGoToDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_TCSEQUENCE_GOTO_LINE, TRUE);
	Spinbox_SetRange(GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWNLINE), 1, INT_MAX);
	Spinbox_SetRange(GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUPLINE), 1, INT_MAX);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWN)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUP)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->SetFocus();
	return FALSE;
}

void CTCSequenceGoToDialog::OnLineNumber()
{
	CheckDlgButton(IDC_TCSEQUENCE_GOTO_LINE, TRUE);
	CheckDlgButton(IDC_TCSEQUENCE_GOTO_JUMPDOWN, FALSE);
	CheckDlgButton(IDC_TCSEQUENCE_GOTO_JUMPUP, FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWNLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUPLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceGoToDialog::OnJumpLineDown()
{
	CheckDlgButton(IDC_TCSEQUENCE_GOTO_LINE, FALSE);
	CheckDlgButton(IDC_TCSEQUENCE_GOTO_JUMPDOWN, TRUE);
	CheckDlgButton(IDC_TCSEQUENCE_GOTO_JUMPUP, FALSE);
	Spinbox_SetPos(GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWNLINE), 10);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWN_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWNLINE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUPLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWNLINE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceGoToDialog::OnJumpLineUp()
{
	CheckDlgButton(IDC_TCSEQUENCE_GOTO_LINE, FALSE);
	CheckDlgButton(IDC_TCSEQUENCE_GOTO_JUMPDOWN, FALSE);
	CheckDlgButton(IDC_TCSEQUENCE_GOTO_JUMPUP, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUPLINE), 10);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWNLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUP_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUPLINE)->EnableWindow();
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUPLINE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceGoToDialog::OnJump()
{
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_TCSEQUENCE_GOTO_LINE)) ShowMessage((!GetParent()->GoTo(GetDlgItemInt(IDC_TCSEQUENCE_GOTO_LINENUMBER, (LPBOOL)NULL, FALSE), FALSE, FALSE)) ? USER_INFORMATIONAL_TCSEQUENCE_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_GOTO_JUMPDOWN)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWNLINE)), TRUE, FALSE)) ? USER_INFORMATIONAL_TCSEQUENCE_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_GOTO_JUMPUP)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUPLINE)), FALSE, TRUE)) ? USER_INFORMATIONAL_TCSEQUENCE_GOTO_LINE_FAILURE : USER_NOERROR);
}

void CTCSequenceGoToDialog::OnEditchangeLineNumber()
{
	GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMP)->EnableWindow((GetDlgItem(IDC_TCSEQUENCE_GOTO_LINENUMBER)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCSequenceGoToDialog::OnOK()
{
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_TCSEQUENCE_GOTO_LINE)) ShowMessage((!GetParent()->GoTo(GetDlgItemInt(IDC_TCSEQUENCE_GOTO_LINENUMBER, (LPBOOL)NULL, FALSE), FALSE, FALSE)) ? USER_INFORMATIONAL_TCSEQUENCE_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_GOTO_JUMPDOWN)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPDOWNLINE)), TRUE, FALSE)) ? USER_INFORMATIONAL_TCSEQUENCE_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_TCSEQUENCE_GOTO_JUMPUP)) ShowMessage((!GetParent()->GoTo((UINT)Spinbox_GetPos(GetDlgItem(IDC_TCSEQUENCE_GOTO_JUMPUPLINE)), FALSE, TRUE)) ? USER_INFORMATIONAL_TCSEQUENCE_GOTO_LINE_FAILURE : USER_NOERROR);
	GetParent()->SetFocus();
	CDisplayDialog::OnOK();
}

BOOL CTCSequenceGoToDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEGOTODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCSequenceGoToDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCSEQUENCEGOTODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceStatusBar

IMPLEMENT_DYNCREATE(CTCSequenceStatusBar, CMFCStatusBar)

BOOL CTCSequenceStatusBar::SetIndicators(CONST UINT *pIDs, INT nCount)
{
	INT  nIndex;
	CString  szText;

	for (Initialize(); CMFCStatusBar::SetIndicators(pIDs, nCount); )
	{
		if ((nIndex = CommandToIndex(ID_TCSEQUENCE_STATUSBAR_DETAILSPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TCSEQUENCE_STATUSBAR_DETAILS), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TCSEQUENCE_STATUSBAR_DETAILSPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(nIndex, szText));
		}
		if ((nIndex = CommandToIndex(ID_TCSEQUENCE_STATUSBAR_FLAGPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TCSEQUENCE_STATUSBAR_FLAG), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TCSEQUENCE_STATUSBAR_FLAGPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_TCSEQUENCE_STATUSBAR_FLAGPANE));
		}
		if ((nIndex = CommandToIndex(ID_TCSEQUENCE_STATUSBAR_TYPEPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TCSEQUENCE_STATUSBAR_TYPE), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TCSEQUENCE_STATUSBAR_TYPEPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_TCSEQUENCE_STATUSBAR_TYPEPANE));
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCSequenceStatusBar::SetPaneText(UINT nID, LPCTSTR pszText)
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

BOOL CTCSequenceStatusBar::GetPaneText(UINT nID, CString &szText) CONST
{
	INT  nIndex;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		szText = CMFCStatusBar::GetPaneText(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString CTCSequenceStatusBar::GetPaneText(UINT nID) CONST
{
	CString  szText;

	return((GetPaneText(nID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

INT CTCSequenceStatusBar::CalcPaneWidth(INT nIndex) CONST
{
	return CalcPaneWidth(nIndex, CMFCStatusBar::GetPaneText(nIndex));
}
INT CTCSequenceStatusBar::CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST
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

VOID CTCSequenceStatusBar::Initialize()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = GetCount(); nIndex < nCount; nIndex++)
	{
		SetTipText(nIndex, (LPCTSTR)NULL);
		continue;
	}
}

BEGIN_MESSAGE_MAP(CTCSequenceStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CTCSequenceStatusBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceStatusBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceTableView

IMPLEMENT_DYNCREATE(CTCSequenceTableView, CDisplayTableView)

CTCSequenceTableView::CTCSequenceTableView() : CDisplayTableView(DATABASE_COMPONENT_TCSEQUENCE, IDR_TCSEQUENCEFRAMEMENU)
{
	return;
}

VOID CTCSequenceTableView::SetTitle(LPCTSTR pszName, LPCTSTR pszTitle)
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	if ((pDatabaseTCSequence = m_pDatabaseTCSequences[0].GetAt(m_pDatabaseTCSequences[0].Find(pszName))))
	{
		for (pDatabaseTCSequence->SetDescription(pszTitle); !m_szName.Compare(pszName); )
		{
			UpdateTables();
			break;
		}
	}
	m_szName = pszName;
	m_szTitle = pszTitle;
}

BOOL CTCSequenceTableView::GetTitle(CString &szName, CString &szTitle) CONST
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	for (szName.Empty(), szTitle.Empty(); (pDatabaseTCSequence = m_pDatabaseTCSequences[0].GetAt(m_pDatabaseTCSequences[0].Find(GetName()))); )
	{
		szTitle = pDatabaseTCSequence->GetDescription();
		szName = pDatabaseTCSequence->GetName();
		return TRUE;
	}
	szName = m_szName;
	szTitle = m_szTitle;
	return !szName.IsEmpty();
}

BOOL CTCSequenceTableView::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	for (SetTablesFonts(plfTitle, plfItems), SetTablesFontColors(nTitleColor, nItemsColor), SetTablesColors(nTitleBackground, nKeysBackground); IsWindow(GetSafeHwnd()); )
	{
		RepositionTables();
		break;
	}
	return TRUE;
}

BOOL CTCSequenceTableView::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	GetTablesFonts(plfTitle, plfItems);
	GetTablesFontColors(nTitleColor, nItemsColor);
	GetTablesColors(nTitleBackground, nKeysBackground);
	return TRUE;
}

VOID CTCSequenceTableView::UpdateTableForms(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nIndex, BOOL bDelete)
{
	UpdateDatabase(pDatabaseTCSequence, (nIndex > 0) ? (nIndex - 1) : nIndex, bDelete);
	UpdateForms(GetParent(), pDatabaseTCSequence, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCSequenceTableView::UpdateTableForms(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCFunctionBlock, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK);
}
VOID CTCSequenceTableView::UpdateTableForms(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCParameterSet, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCPARAMETERSET);
}
VOID CTCSequenceTableView::UpdateTableForms(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCParameterValueSet, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET);
}

CTCSequenceWnd *CTCSequenceTableView::GetParent() CONST
{
	return((CTCSequenceWnd *)CDisplayTableView::GetParent());
}

BOOL CTCSequenceTableView::CheckPrivilege() CONST
{
	return CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE);
}

BEGIN_MESSAGE_MAP(CTCSequenceTableView, CDisplayTableView)
	//{{AFX_MSG_MAP(CTCSequenceTableView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceTableView message handlers

int CTCSequenceTableView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayTableView::OnCreate(lpCreateStruct) != -1 && GetDatabase()->CreateTables(this, GetComponent())) ? 0 : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceXmlViewDocument

IMPLEMENT_DYNAMIC(CTCSequenceXmlViewDocument, CDocument)

CTCSequenceXmlViewDocument::CTCSequenceXmlViewDocument() : CDocument()
{
	return;
}

CTCSequenceXmlViewDocument::~CTCSequenceXmlViewDocument()
{
	return;
}


/////////////////////////////////////////////////////////////////////////////
// CTCSequenceXmlView

IMPLEMENT_DYNCREATE(CTCSequenceXmlView, CRichEditView)

CTCSequenceXmlView::CTCSequenceXmlView() : CRichEditView()
{
	m_nWordWrap = WrapNone;
}

BOOL CTCSequenceXmlView::Create(CWnd *pParentWnd, LPCTSTR pszName, CONST RECT &rect)
{
	CString  szHeader;
	CString  szXmlCode;
	CDatabaseTCSequence  *pDatabaseTCSequence;
	CCreateContext  cContext;

	for (cContext.m_pCurrentDoc = new CTCSequenceXmlViewDocument; CRichEditView::Create((LPCTSTR)NULL, EMPTYSTRING, ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | ES_NOHIDESEL | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP, rect, pParentWnd, 0, &cContext); )
	{
		for (m_szXmlCode = szHeader = ConstructXmlHeader(); (pDatabaseTCSequence = GetDatabase()->GetTCSequences()->GetAt(GetDatabase()->GetTCSequences()->Find(pszName))) && !pDatabaseTCSequence->GetXmlCode().IsEmpty(); )
		{
			m_szName = pDatabaseTCSequence->GetName();
			m_szTitle = pDatabaseTCSequence->GetDescription();
			szXmlCode = pDatabaseTCSequence->GetXmlCode();
			break;
		}
		SetWindowText((m_szXmlCode = m_szXmlCode + szXmlCode));
		GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), CalculateXmlHeaderLength());
		return TRUE;
	}
	return FALSE;
}

VOID CTCSequenceXmlView::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCSequenceXmlView::GetName() CONST
{
	return m_szName;
}

VOID CTCSequenceXmlView::SetTitle(LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
}

CString CTCSequenceXmlView::GetTitle() CONST
{
	return m_szTitle;
}

INT CTCSequenceXmlView::DoSave()
{
	INT  nIndex;
	CString  szXmlCode;
	CDatabaseTCSequence  *pDatabaseTCSequence[2];

	for (GetWindowText(szXmlCode); (pDatabaseTCSequence[1] = ((pDatabaseTCSequence[0] = GetDatabase()->GetTCSequences()->GetAt(GetDatabase()->GetTCSequences()->Find(GetName())))) ? new CDatabaseTCSequence : (CDatabaseTCSequence *)NULL); )
	{
		for (pDatabaseTCSequence[1]->Copy(pDatabaseTCSequence[0]), pDatabaseTCSequence[1]->SetXmlCode(szXmlCode); (pDatabaseTCSequence[0] = (GetDatabase()->Save(pDatabaseTCSequence[1])) ? GetDatabase()->GetTCSequences()->GetAt((nIndex = GetDatabase()->GetTCSequences()->Find(pDatabaseTCSequence[1]->GetName()))) : (CDatabaseTCSequence *)NULL); )
		{
			GetParent()->SetName(pDatabaseTCSequence[0]->GetName());
			GetParent()->SetTitle(pDatabaseTCSequence[0]->GetDescription());
			m_szXmlCode = szXmlCode;
			delete pDatabaseTCSequence[1];
			return nIndex;
		}
		delete pDatabaseTCSequence[1];
		break;
	}
	return -1;
}

BOOL CTCSequenceXmlView::CanSave() CONST
{
	CString  szXmlCode;
	CDatabaseTCSequence  *pDatabaseTCSequence;
	CDatabaseTCSequences  pDatabaseTCSequences;

	GetWindowText(szXmlCode);
	return(((pDatabaseTCSequence = (GetDatabase()->EnumTCSequences(szXmlCode, pDatabaseTCSequences) == 1) ? pDatabaseTCSequences.GetAt((INT)pDatabaseTCSequences.GetUpperBound()) : (CDatabaseTCSequence *)NULL) && pDatabaseTCSequence->GetName() == GetName()) ? (IsModified() && Check()) : FALSE);
}

INT CTCSequenceXmlView::DoSaveAs(LPCTSTR pszFileName)
{
	INT  nIndex;
	CString  szXmlCode;
	CDatabaseTCSequence  *pDatabaseTCSequence[2];
	CDatabaseTCSequences  pDatabaseTCSequences;

	for (GetWindowText(szXmlCode); (pDatabaseTCSequence[0] = (GetDatabase()->EnumTCSequences(szXmlCode, pDatabaseTCSequences) == 1) ? pDatabaseTCSequences.GetAt((INT)pDatabaseTCSequences.GetUpperBound()) : (CDatabaseTCSequence *)NULL); )
	{
		for (pDatabaseTCSequence[0]->SetXmlCode(szXmlCode), pDatabaseTCSequence[0]->SetFileName(pszFileName); (pDatabaseTCSequence[1] = (GetDatabase()->Save(pDatabaseTCSequence[0])) ? GetDatabase()->GetTCSequences()->GetAt((nIndex = GetDatabase()->GetTCSequences()->Find(pDatabaseTCSequence[0]->GetName()))) : (CDatabaseTCSequence *)NULL); )
		{
			GetParent()->SetName(pDatabaseTCSequence[1]->GetName());
			GetParent()->SetTitle(pDatabaseTCSequence[1]->GetDescription());
			m_szXmlCode = szXmlCode;
			return nIndex;
		}
		break;
	}
	return -1;
}

BOOL CTCSequenceXmlView::CanSaveAs() CONST
{
	CString  szXmlCode;
	CDatabaseTCSequence  *pDatabaseTCSequence;
	CDatabaseTCSequences  pDatabaseTCSequences;

	GetWindowText(szXmlCode);
	return(((pDatabaseTCSequence = (GetDatabase()->EnumTCSequences(szXmlCode, pDatabaseTCSequences) == 1) ? pDatabaseTCSequences.GetAt((INT)pDatabaseTCSequences.GetUpperBound()) : (CDatabaseTCSequence *)NULL)) ? Check() : FALSE);
}

BOOL CTCSequenceXmlView::CanPrint() CONST
{
	return((GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

INT CTCSequenceXmlView::DoDelete()
{
	INT  nIndex;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	return(((pDatabaseTCSequence = GetDatabase()->GetTCSequences()->GetAt((nIndex = GetDatabase()->GetTCSequences()->Find(GetName())))) && GetDatabase()->Delete(pDatabaseTCSequence)) ? nIndex : -1);
}

BOOL CTCSequenceXmlView::CanDelete() CONST
{
	CString  szXmlCode;
	CDatabaseTCSequence  *pDatabaseTCSequence;
	CDatabaseTCSequences  pDatabaseTCSequences;

	GetWindowText(szXmlCode);
	return(((pDatabaseTCSequence = (GetDatabase()->EnumTCSequences(szXmlCode, pDatabaseTCSequences) == 1) ? pDatabaseTCSequences.GetAt((INT)pDatabaseTCSequences.GetUpperBound()) : (CDatabaseTCSequence *)NULL) && pDatabaseTCSequence->GetName() == GetName()) ? TRUE : FALSE);
}

VOID CTCSequenceXmlView::DoSelectAll()
{
	GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), GetTextLength());
}

BOOL CTCSequenceXmlView::CanSelectAll() CONST
{
	return((GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CTCSequenceXmlView::UnSelectAll()
{
	GetRichEditCtrl().SetSel(CalculateXmlHeaderLength(), CalculateXmlHeaderLength());
}

VOID CTCSequenceXmlView::DoCutSel()
{
	GetRichEditCtrl().Cut();
}

BOOL CTCSequenceXmlView::CanCutSel() CONST
{
	return !GetRichEditCtrl().GetSelText().IsEmpty();
}

VOID CTCSequenceXmlView::DoCopySel()
{
	GetRichEditCtrl().Copy();
}

BOOL CTCSequenceXmlView::CanCopySel() CONST
{
	return !GetRichEditCtrl().GetSelText().IsEmpty();
}

VOID CTCSequenceXmlView::DoPasteSel()
{
	GetRichEditCtrl().Paste();
}

BOOL CTCSequenceXmlView::CanPasteSel() CONST
{
	return GetRichEditCtrl().CanPaste(CF_TEXT);
}

VOID CTCSequenceXmlView::DoDeleteSel()
{
	GetRichEditCtrl().ReplaceSel(EMPTYSTRING, TRUE);
}

BOOL CTCSequenceXmlView::CanDeleteSel() CONST
{
	long  nSel[2];

	GetRichEditCtrl().GetSel(nSel[0], nSel[1]);
	return((nSel[0] >= CalculateXmlHeaderLength() && !GetRichEditCtrl().GetSelText().IsEmpty()) ? TRUE : FALSE);
}

VOID CTCSequenceXmlView::DoUndo()
{
	GetRichEditCtrl().Undo();
}

BOOL CTCSequenceXmlView::CanUndo() CONST
{
	return GetRichEditCtrl().CanUndo();
}

VOID CTCSequenceXmlView::DoRedo()
{
	GetRichEditCtrl().Redo();
}

BOOL CTCSequenceXmlView::CanRedo() CONST
{
	return GetRichEditCtrl().CanRedo();
}

BOOL CTCSequenceXmlView::DoEmpty()
{
	DoSelectAll();
	DoDeleteSel();
	return TRUE;
}

BOOL CTCSequenceXmlView::IsEmpty() CONST
{
	return((!GetTextLength()) ? TRUE : FALSE);
}

VOID CTCSequenceXmlView::DoFind()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgFind.Create(GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CTCSequenceXmlView::CanFind() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CTCSequenceXmlView::DoFindNext()
{
	LONG  nPos[2];
	CString  szText;

	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.GetDlgItem(IDC_TCSEQUENCE_FIND_TEXT)->GetWindowText(szText), GetRichEditCtrl().GetSel(nPos[0], nPos[1]), nPos[0] = nPos[1] = nPos[0] + szText.GetLength(), GetRichEditCtrl().SetSel(nPos[0], nPos[1]); !szText.IsEmpty(); )
		{
			ShowMessage((!Search(szText, TRUE, FALSE, m_dlgFind.IsDlgButtonChecked(IDC_TCSEQUENCE_FIND_CASE), m_dlgFind.IsDlgButtonChecked(IDC_TCSEQUENCE_FIND_WORD))) ? USER_INFORMATIONAL_TCSEQUENCE_FIND_TEXT_NOTHING : USER_NOERROR);
			break;
		}
	}
}
VOID CTCSequenceXmlView::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(GetRichEditCtrl().GetSelText(), TRUE, FALSE, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_TCSEQUENCE_FIND_TEXT_NOTHING : USER_NOERROR);
}
VOID CTCSequenceXmlView::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(pszText, TRUE, bSearchAll, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_TCSEQUENCE_FIND_TEXT_NOTHING : USER_NOERROR);
}

BOOL CTCSequenceXmlView::CanFindNext() CONST
{
	return(((IsWindow(m_dlgFind.GetSafeHwnd()) || !GetRichEditCtrl().GetSelText().IsEmpty()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CTCSequenceXmlView::DoFindPrevious()
{
	CString  szText;

	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.GetDlgItem(IDC_TCSEQUENCE_FIND_TEXT)->GetWindowText(szText); !szText.IsEmpty(); )
		{
			ShowMessage((!Search(szText, FALSE, FALSE, m_dlgFind.IsDlgButtonChecked(IDC_TCSEQUENCE_FIND_CASE), m_dlgFind.IsDlgButtonChecked(IDC_TCSEQUENCE_FIND_WORD))) ? USER_INFORMATIONAL_TCSEQUENCE_FIND_TEXT_NOTHING : USER_NOERROR);
			break;
		}
	}
}
VOID CTCSequenceXmlView::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(GetRichEditCtrl().GetSelText(), FALSE, FALSE, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_TCSEQUENCE_FIND_TEXT_NOTHING : USER_NOERROR);
}
VOID CTCSequenceXmlView::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!Search(pszText, FALSE, bSearchAll, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_TCSEQUENCE_FIND_TEXT_NOTHING : USER_NOERROR);
}

BOOL CTCSequenceXmlView::CanFindPrevious() CONST
{
	return(((IsWindow(m_dlgFind.GetSafeHwnd()) || !GetRichEditCtrl().GetSelText().IsEmpty()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CTCSequenceXmlView::DoReplace()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgReplace.Create(GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CTCSequenceXmlView::CanReplace() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

VOID CTCSequenceXmlView::DoGoTo()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgGoTo.Create(GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CTCSequenceXmlView::CanGoTo() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetTextLength() > CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

BOOL CTCSequenceXmlView::Search(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
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

BOOL CTCSequenceXmlView::Replace(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
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

BOOL CTCSequenceXmlView::ReplaceAll(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
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

BOOL CTCSequenceXmlView::GoTo(UINT nLine, BOOL bDown, BOOL bUp)
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
BOOL CTCSequenceXmlView::GoTo(LPCTSTR pszLine)
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

BOOL CTCSequenceXmlView::IsModified() CONST
{
	CString  szXmlCode;

	GetWindowText(szXmlCode);
	return((m_szXmlCode.Compare(szXmlCode) != 0) ? TRUE : FALSE);
}

BOOL CTCSequenceXmlView::Check() CONST
{
	return !IsEmpty();
}

CTCSequenceWnd *CTCSequenceXmlView::GetParent() CONST
{
	return((CTCSequenceWnd *)CRichEditView::GetParent());
}

void CTCSequenceXmlView::PostNcDestroy()
{
	return;
}

CString CTCSequenceXmlView::ConstructXmlHeader() CONST
{
	return(CString(STRING(IDS_XMLHEADER_VERSION)) + CR + EOL + CR + EOL);
}

INT CTCSequenceXmlView::CalculateXmlHeaderLength() CONST
{
	return(ConstructXmlHeader().GetLength() - 1 - 1 - 1);
}

BOOL CTCSequenceXmlView::IsMouseOnXmlHeader(CONST POINT &point) CONST
{
	INT  nPos;

	return(((nPos = GetRichEditCtrl().CharFromPos(point)) >= 0 && nPos < CalculateXmlHeaderLength()) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CTCSequenceXmlView, CRichEditView)
	//{{AFX_MSG_MAP(CTCSequenceXmlView)
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
// CTCSequenceXmlView drawing

void CTCSequenceXmlView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceXmlView message handlers

int CTCSequenceXmlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

void CTCSequenceXmlView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point)) SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
	CRichEditView::OnMouseMove(nFlags, point);
}

BOOL CTCSequenceXmlView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	POINT  ptCursor;

	for (GetCursorPos(&ptCursor); IsMouseOnXmlHeader(ptCursor); )
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return TRUE;
	}
	return CRichEditView::OnSetCursor(pWnd, nHitTest, message);
}

void CTCSequenceXmlView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnLButtonDown(nFlags, point);
}

void CTCSequenceXmlView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnLButtonDblClk(nFlags, point);
}

void CTCSequenceXmlView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnLButtonUp(nFlags, point);
}

void CTCSequenceXmlView::OnMButtonDown(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnMButtonDown(nFlags, point);
}

void CTCSequenceXmlView::OnMButtonUp(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnMButtonUp(nFlags, point);
}

void CTCSequenceXmlView::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnRButtonDown(nFlags, point);
}

void CTCSequenceXmlView::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (IsMouseOnXmlHeader(point))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
		return;
	}
	CRichEditView::OnRButtonUp(nFlags, point);
}

void CTCSequenceXmlView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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

void CTCSequenceXmlView::OnEditchangeCode()
{
	CTCSequenceXmlEdit::RenderCode(&GetRichEditCtrl(), &m_cCodeFont);
	GetParent()->UpdateBars();
}

void CTCSequenceXmlView::OnEditupdateCode()
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
// CTCSequenceWnd

IMPLEMENT_DYNCREATE(CTCSequenceWnd, CDisplayWnd)

CTCSequenceWnd::CTCSequenceWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TCSEQUENCE);
}
CTCSequenceWnd::CTCSequenceWnd(LPCTSTR pszName) : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TCSEQUENCE);
	SetName(pszName);
}

BOOL CTCSequenceWnd::Create(CMDIFrameWnd *pParentWnd, UINT nShow)
{
	return Create(pParentWnd, GetName(), nShow);
}
BOOL CTCSequenceWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszName, UINT nShow)
{
	CRect  rPosition;

	for (SetName(pszName), rPosition = m_rPosition; CDisplayWnd::Create(pParentWnd, STRING(IDS_DISPLAY_TITLE_TCSEQUENCE), (nShow == (UINT)-1) ? CRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) : CRect(0, 0, 0, 0), IDR_TCSEQUENCEFRAME, (nShow != SW_SHOWMINIMIZED || nShow != SW_SHOWMAXIMIZED) ? (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE) : (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW)); )
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

VOID CTCSequenceWnd::SetName(LPCTSTR pszName)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.SetName(pszName);
		return;
	}
	m_wndXmlView.SetName(pszName);
}

CString CTCSequenceWnd::GetName() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.GetName() : m_wndXmlView.GetName());
}

VOID CTCSequenceWnd::SetTitle(LPCTSTR pszTitle)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.SetTitle(GetName(), pszTitle);
		return;
	}
	m_wndXmlView.SetTitle(pszTitle);
}

CString CTCSequenceWnd::GetTitle() CONST
{
	CString  szName;
	CString  szTitle;

	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? ((!m_wndTableView.GetTitle(szName, szTitle)) ? STRING(IDS_DISPLAY_TITLE_TCSEQUENCE) : szTitle) : ((m_wndXmlView.GetTitle().IsEmpty()) ? STRING(IDS_DISPLAY_TITLE_XML_TCSEQUENCE) : m_wndXmlView.GetTitle()));
}

BOOL CTCSequenceWnd::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	return m_wndTableView.SetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CTCSequenceWnd::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	return m_wndTableView.GetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CTCSequenceWnd::IsModified() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.Check() && m_wndTableView.IsModified()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.Check() && m_wndXmlView.IsModified())) ? TRUE : FALSE);
}

BOOL CTCSequenceWnd::Save(INT nPosition) CONST
{
	UINT  nShowFlags;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	cProfile.DeleteDisplayWindowInfo(nPosition);
	return((GetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && cProfile.SetDisplayWindowType(nPosition, GetType()) && cProfile.SetDisplayWindowName(nPosition, GetName()) && cProfile.SetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, (nShowFlags = (!IsIconic()) ? ((!IsZoomed()) ? SW_SHOWNORMAL : SW_SHOWMAXIMIZED) : SW_SHOWMINIMIZED)) && cProfile.SetTCSequencesFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? TRUE : FALSE);
}

INT CTCSequenceWnd::Load(INT nPosition)
{
	UINT  nShowFlags;
	CString  szName;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	return((cProfile.GetDisplayWindowName(nPosition, szName) && cProfile.GetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, nShowFlags) && cProfile.GetTCSequencesFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && SetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? CTCSequenceWnd::Create(GetMainWnd(), szName, nShowFlags) : -1);
}

BOOL CTCSequenceWnd::UpdateProperties()
{
	return((m_dlgProperties.DoModal(this) == IDOK) ? TRUE : FALSE);
}

BOOL CTCSequenceWnd::IsUpdatingProperties() CONST
{
	return IsWindow(m_dlgProperties.GetSafeHwnd());
}

BOOL CTCSequenceWnd::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCSequenceWnd::CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST
{
	return m_wndTableView.CheckTableDropTarget(pszTable, nComponent, point);
}

BOOL CTCSequenceWnd::DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point)
{
	return m_wndTableView.DropOnTableTarget(pszTable, nComponent, point);
}

VOID CTCSequenceWnd::UpdateAllPanes(LPCTSTR pszDetails, LPCTSTR pszFlag, LPCTSTR pszType)
{
	m_wndStatusBar.SetPaneText(ID_TCSEQUENCE_STATUSBAR_DETAILSPANE, pszDetails);
	m_wndStatusBar.SetPaneText(ID_TCSEQUENCE_STATUSBAR_FLAGPANE, pszFlag);
	m_wndStatusBar.SetPaneText(ID_TCSEQUENCE_STATUSBAR_TYPEPANE, pszType);
}

BOOL CTCSequenceWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
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
				if (PrintJob(cDC, STRING(IDS_DISPLAY_TITLE_TCSEQUENCE), cPrintProfileInfo.GetPrinterName(), rtMargin[0], bMetrics, nFlags))
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
					if (PrintJob(cDC, STRING(IDS_DISPLAY_TITLE_TCSEQUENCE), (LPCTSTR)pDevMode->dmDeviceName, rtMargin[0], bMetrics, nFlags, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : -1, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : -1))
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

VOID CTCSequenceWnd::DoSave()
{
	INT  nPosition;
	CString  szMessage;

	if (IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.DoSave())
	{
		GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_TCSEQUENCE);
		return;
	}
	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		if ((nPosition = m_wndXmlView.DoSave()) >= 0)
		{
			GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_TCSEQUENCE);
			UpdateDatabase(this, nPosition);
			UpdateTitle();
			return;
		}
		szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_SAVE), (LPCTSTR)GetTitle());
		ShowMessage(szMessage);
	}
}

BOOL CTCSequenceWnd::CanSave() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanSave()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanSave())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

VOID CTCSequenceWnd::DoSaveAs()
{
	INT  nResult;
	INT  nPosition;
	CString  szMessage;
	CString  szFileName;
	CTCSequenceSaveDialog  cSaveDialog;

	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		if ((nResult = cSaveDialog.Create(this, szFileName)) == IDOK && (nPosition = m_wndXmlView.DoSaveAs(szFileName)) >= 0)
		{
			GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_TCSEQUENCE);
			UpdateDatabase(this, -(nPosition + 1));
			UpdateTitle();
			UpdateMenus();
			return;
		}
		if (nResult == IDOK)
		{
			szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_SAVE), (LPCTSTR)GetTitle());
			ShowMessage(szMessage);
		}
	}
}

BOOL CTCSequenceWnd::CanSaveAs() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanSaveAs()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

VOID CTCSequenceWnd::DoCheck()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoCheck();
		return;
	}
}

BOOL CTCSequenceWnd::CanCheck() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCheck()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

VOID CTCSequenceWnd::DoDelete()
{
	INT  nPosition;
	CString  szName;
	CString  szTitle;
	CString  szMessage;

	for (szName = GetName(), szTitle = GetTitle(); IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.DoDelete(); )
	{
		GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_TCSEQUENCE);
		return;
	}
	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		for (szMessage.Format(STRING(IDS_TCSEQUENCE_QUESTION_DELETE), (LPCTSTR)GetTitle()); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES; )
		{
			if ((nPosition = m_wndXmlView.DoDelete()) >= 0)
			{
				GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_TCSEQUENCE);
				UpdateDatabase(this, nPosition, TRUE);
				DestroyWindow();
				return;
			}
			szMessage.Format(STRING(IDS_TCSEQUENCE_FAILURE_DELETE), (LPCTSTR)szTitle);
			ShowMessage(szMessage);
			break;
		}
	}
}

BOOL CTCSequenceWnd::CanDelete() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDelete()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanDelete())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

VOID CTCSequenceWnd::DoUndo()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoUndo();
		return;
	}
	m_wndXmlView.DoUndo();
}

BOOL CTCSequenceWnd::CanUndo() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanUndo()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanUndo())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

VOID CTCSequenceWnd::DoRedo()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoRedo();
		return;
	}
	m_wndXmlView.DoRedo();
}

BOOL CTCSequenceWnd::CanRedo() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanRedo()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanRedo())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

VOID CTCSequenceWnd::DoFind()
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFind();
}

BOOL CTCSequenceWnd::CanFind() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanFind() : FALSE);
}

VOID CTCSequenceWnd::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindNext(bMatchCase, bMatchWord);
}
VOID CTCSequenceWnd::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindNext(pszText, bSearchAll, bMatchCase, bMatchWord);
}

BOOL CTCSequenceWnd::CanFindNext() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanFindNext() : FALSE);
}

VOID CTCSequenceWnd::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindPrevious(bMatchCase, bMatchWord);
}
VOID CTCSequenceWnd::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoFindPrevious(pszText, bSearchAll, bMatchCase, bMatchWord);
}

BOOL CTCSequenceWnd::CanFindPrevious() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanFindPrevious() : FALSE);
}

VOID CTCSequenceWnd::DoReplace()
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoReplace();
}

BOOL CTCSequenceWnd::CanReplace() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanReplace()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

VOID CTCSequenceWnd::DoGoTo()
{
	if (IsWindow(m_wndXmlView.GetSafeHwnd())) m_wndXmlView.DoGoTo();
}

BOOL CTCSequenceWnd::CanGoTo() CONST
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.CanGoTo() : FALSE);
}

VOID CTCSequenceWnd::DoSelectAll()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoSelectAll();
		return;
	}
	m_wndXmlView.DoSelectAll();
}

BOOL CTCSequenceWnd::CanSelectAll() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanSelectAll()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanSelectAll())) ? TRUE : FALSE);
}

VOID CTCSequenceWnd::DoCutSel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoCutSel();
		return;
	}
	m_wndXmlView.DoCutSel();
}

BOOL CTCSequenceWnd::CanCutSel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCutSel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanCutSel())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

VOID CTCSequenceWnd::DoCopySel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoCopySel();
		return;
	}
	m_wndXmlView.DoCopySel();
}

BOOL CTCSequenceWnd::CanCopySel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCopySel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanCopySel())) ? TRUE : FALSE);
}

VOID CTCSequenceWnd::DoPasteSel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoPasteSel();
		return;
	}
	m_wndXmlView.DoPasteSel();
}

BOOL CTCSequenceWnd::CanPasteSel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanPasteSel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanPaste())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

VOID CTCSequenceWnd::DoDeleteSel()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoDeleteSel();
		return;
	}
	m_wndXmlView.DoDeleteSel();
}

BOOL CTCSequenceWnd::CanDeleteSel() CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteSel()) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanDeleteSel())) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::CanPrint(UINT nFlags) CONST
{
	return(((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanPrint(nFlags)) || (IsWindow(m_wndXmlView.GetSafeHwnd()) && m_wndXmlView.CanPrint())) ? TRUE : FALSE);
}

VOID CTCSequenceWnd::DoClose()
{
	CString  szMessage;

	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.DoClose();
		return;
	}
	for (szMessage.Format(STRING(IDS_TCSEQUENCE_QUESTION_SAVE), (LPCTSTR)GetName()); CanSave(); )
	{
		if (MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES) DoSave();
		return;
	}
	if (IsNew())
	{
		for (szMessage = STRING(IDS_TCSEQUENCE_QUESTION_SAVE); CanSaveAs(); )
		{
			if (MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES) DoSaveAs();
			return;
		}
	}
}

BOOL CTCSequenceWnd::DoSaveTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoSaveTable() : FALSE);
}

BOOL CTCSequenceWnd::CanSaveTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanSaveTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoCheckTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoCheckTable() : FALSE);
}

BOOL CTCSequenceWnd::CanCheckTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanCheckTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoDeleteTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDeleteTable() : FALSE);
}

BOOL CTCSequenceWnd::CanDeleteTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoPrintTable()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE) : FALSE);
}

BOOL CTCSequenceWnd::CanPrintTable() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE) : FALSE);
}

BOOL CTCSequenceWnd::DoPrintAllTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL) : FALSE);
}

BOOL CTCSequenceWnd::CanPrintAllTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL) : FALSE);
}

BOOL CTCSequenceWnd::DoImportTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoImportTables() : FALSE);
}

BOOL CTCSequenceWnd::CanImportTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanImportTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoExportTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoExportTables() : FALSE);
}

BOOL CTCSequenceWnd::CanExportTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.CanExportTables() : FALSE);
}

BOOL CTCSequenceWnd::DoDiscardTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDiscardTables() : FALSE);
}

BOOL CTCSequenceWnd::CanDiscardTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDiscardTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoDiscardAllTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDiscardAllTables() : FALSE);
}

BOOL CTCSequenceWnd::CanDiscardAllTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDiscardAllTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoResetTables()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoResetTables() : FALSE);
}

BOOL CTCSequenceWnd::CanResetTables() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanResetTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoInsertTableRowAbove()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableRowAbove() : FALSE);
}

BOOL CTCSequenceWnd::CanInsertTableRowAbove() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableRowAbove()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoInsertTableRowBelow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableRowBelow() : FALSE);
}

BOOL CTCSequenceWnd::CanInsertTableRowBelow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableRowBelow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoInsertTableColumnBefore()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableColumnBefore() : FALSE);
}

BOOL CTCSequenceWnd::CanInsertTableColumnBefore() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableColumnBefore()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoInsertTableColumnAfter()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoInsertTableColumnAfter() : FALSE);
}

BOOL CTCSequenceWnd::CanInsertTableColumnAfter() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanInsertTableColumnAfter()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoClearTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoClearTableRow() : FALSE);
}

BOOL CTCSequenceWnd::CanClearTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanClearTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoDeleteTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDeleteTableRow() : FALSE);
}

BOOL CTCSequenceWnd::CanDeleteTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoDeleteTableColumn()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoDeleteTableColumn() : FALSE);
}

BOOL CTCSequenceWnd::CanDeleteTableColumn() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanDeleteTableColumn()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

BOOL CTCSequenceWnd::DoCopyTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoCopyTableRow() : FALSE);
}

BOOL CTCSequenceWnd::CanCopyTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.CanCopyTableRow() : FALSE);
}

BOOL CTCSequenceWnd::DoPasteTableRow()
{
	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? m_wndTableView.DoPasteTableRow() : FALSE);
}

BOOL CTCSequenceWnd::CanPasteTableRow() CONST
{
	return((IsWindow(m_wndTableView.GetSafeHwnd()) && m_wndTableView.CanPasteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE) : FALSE);
}

VOID CTCSequenceWnd::GotoTable(ULONGLONG nComponent, LPCTSTR pszName)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.GotoTable(nComponent, pszName);
}

VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pDatabaseTCParameterSet->GetName(), bDelete);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET, pDatabaseTCParameterValueSet->GetName(), bDelete);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCSequences &pDatabaseTCSequences)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(pDatabaseTCSequences);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE, pDatabaseTCSequence->GetName(), bDelete);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK, pDatabaseTCFunctionBlock->GetName(), bDelete);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCSequenceWnd::UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCSequenceWnd::UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.UpdateTables(nComponent, pszName, bDelete);
		m_wndTableView.ClearUndo();
	}
}
VOID CTCSequenceWnd::UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		m_wndTableView.UpdateTables(nComponent, nID, bDelete);
		m_wndTableView.ClearUndo();
	}
}
VOID CTCSequenceWnd::UpdateTables(ULONGLONG nComponent)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables(nComponent);
}
VOID CTCSequenceWnd::UpdateTables()
{
	if (IsWindow(m_wndTableView.GetSafeHwnd())) m_wndTableView.UpdateTables();
}

BOOL CTCSequenceWnd::Search(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.Search(pszText, bDown, bAll, bCase, bWord) : FALSE);
}

BOOL CTCSequenceWnd::Replace(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.Replace(pszText, pszReplaceText, bDown, bAll, bCase, bWord) : FALSE);
}

BOOL CTCSequenceWnd::ReplaceAll(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.ReplaceAll(pszText, pszReplaceText, bDown, bAll, bCase, bWord) : FALSE);
}

BOOL CTCSequenceWnd::GoTo(UINT nLine, BOOL bDown, BOOL bUp)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.GoTo(nLine, bDown, bUp) : FALSE);
}
BOOL CTCSequenceWnd::GoTo(LPCTSTR pszLine)
{
	return((IsWindow(m_wndXmlView.GetSafeHwnd())) ? m_wndXmlView.GoTo(pszLine) : FALSE);
}

VOID CTCSequenceWnd::UpdateBars()
{
	CString  szText;
	CStringTools  cStringTools;

	if (IsWindow(m_wndXmlView.GetSafeHwnd()))
	{
		szText.Format(STRING(IDS_TCSEQUENCE_STATUSBAR_SIZE), (LPCTSTR)cStringTools.ConvertLongUIntToStructuredString(m_wndXmlView.GetWindowTextLength()));
		m_wndStatusBar.SetPaneText(ID_TCSEQUENCE_STATUSBAR_DETAILSPANE, szText);
	}
}

VOID CTCSequenceWnd::UpdateTitle()
{
	INT  nPos;
	CString  szName;
	CString  szTitle[2];

	if (IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		SetWindowText(STRING(IDS_DISPLAY_TITLE_TCSEQUENCE));
		return;
	}
	for (szName = GetName(), szTitle[0] = STRING(IDS_DISPLAY_TITLE_XML_TCSEQUENCE); szName.IsEmpty(); )
	{
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_WINDOW_UNTITLED), ((nPos = szTitle[0].ReverseFind(SPACE[0])) >= 0) ? (LPCTSTR)szTitle[0].Left(nPos) : (LPCTSTR)szTitle[0]);
		break;
	}
	for (szTitle[0] = GetTitle(); !szName.IsEmpty() && szTitle[0] == STRING(IDS_DISPLAY_TITLE_XML_TCSEQUENCE); )
	{
		szTitle[1].Format(STRING(IDS_DISPLAY_TITLE_XML_TCSEQUENCE), (LPCTSTR)szName);
		szTitle[0].Empty();
		break;
	}
	if (!szName.IsEmpty() && !szTitle[0].IsEmpty())
	{
		szTitle[0].Format(STRING(IDS_DISPLAY_TITLE_XML_TCSEQUENCE), (LPCTSTR)szName);
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), (LPCTSTR)GetTitle(), (LPCTSTR)szTitle[0]);
	}
	SetWindowText(szTitle[1]);
}

VOID CTCSequenceWnd::UpdateMenus()
{
	GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
}

VOID CTCSequenceWnd::UpdateStatusBar()
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

BOOL CTCSequenceWnd::StartPrintJob(CDC &cDC)
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

BOOL CTCSequenceWnd::PrintJob(CDC &cDC, LPCTSTR pszForm, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, WORD wFromPage, WORD wToPage)
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

BOOL CTCSequenceWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndPage() >= 0 && cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CTCSequenceWnd::DrawPrintDocPage(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CPtrArray &pFonts, LPRECT prClip, UINT nFlags, INT nPage, BOOL bCalc)
{
	return((DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(EMPTYSTRING, 0), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_TITLE), nFlags, bCalc) && DrawPrintDocInfoTitle(cDC, prClip, GetPrintDocInfoTitle(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_INFOTITLE), bCalc) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_LOGO), bCalc) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPage), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_FOOTER), bCalc)) ? TRUE : FALSE);
}

BOOL CTCSequenceWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nFlags, BOOL bCalc)
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

CString CTCSequenceWnd::GetPrintDocTitle(LPCTSTR pszName, UINT nFlags) CONST
{
	CDatabaseTCSequence  *pDatabaseTCSequence;

	return((IsWindow(m_wndTableView.GetSafeHwnd())) ? (((pDatabaseTCSequence = (nFlags & DISPLAYTABLEVIEW_PRINT_TABLE) ? GetDatabase()->GetTCSequences()->GetAt(GetDatabase()->GetTCSequences()->Find(pszName)) : (CDatabaseTCSequence *)NULL) && !pDatabaseTCSequence->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseTCSequence->GetDescription() : pszName) : GetTitle());
}

CString CTCSequenceWnd::GetPrintDocInfoTitle() CONST
{
	INT  nPos;
	CString  szTitle[2];

	if (!IsWindow(m_wndTableView.GetSafeHwnd()))
	{
		for (szTitle[0].Format(STRING(IDS_DISPLAY_TITLE_XML_TCSEQUENCE), (LPCTSTR)(szTitle[1] = GetName())); (nPos = (szTitle[1].IsEmpty()) ? szTitle[0].Find(SPACE) : -1) >= 0; )
		{
			szTitle[0] = szTitle[0].Left(nPos);
			break;
		}
		return szTitle[0];
	}
	return STRING(IDS_DISPLAY_TITLE_TCSEQUENCE);
}

INT CTCSequenceWnd::Delete(LPCTSTR pszName)
{
	INT  nIndex;
	CDatabaseTCSequence  *pDatabaseTCSequence;

	return(((pDatabaseTCSequence = GetDatabase()->GetTCSequences()->GetAt((nIndex = GetDatabase()->GetTCSequences()->Find(pszName)))) && GetDatabase()->Delete(pDatabaseTCSequence)) ? nIndex : -1);
}

VOID CTCSequenceWnd::AdjustToPrivileges()
{
	if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCSEQUENCE_CHANGE))
	{
		if (IsWindow(m_wndTableView.GetSafeHwnd()))
		{
			m_wndTableView.UnSelectAll();
			return;
		}
		m_wndXmlView.UnSelectAll();
	}
}

BEGIN_MESSAGE_MAP(CTCSequenceWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CTCSequenceWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_TCSEQUENCE_STATUSBAR_DETAILSPANE, OnUpdateStatusBarDetailsPane)
	ON_UPDATE_COMMAND_UI(ID_TCSEQUENCE_STATUSBAR_FLAGPANE, OnUpdateStatusBarFlagPane)
	ON_UPDATE_COMMAND_UI(ID_TCSEQUENCE_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceWnd message handlers

int CTCSequenceWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayWnd::OnCreate(lpCreateStruct) != -1 && LoadAccelTable(IDR_TCSEQUENCEFRAME)) ? 0 : -1);
}

BOOL CTCSequenceWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	CRect  rBar;

	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1))
	{
		for (m_wndStatusBar.GetWindowRect(rBar); GetDatabase()->UsesDBMSTables(DATABASE_COMPONENT_TCSEQUENCE); ) return m_wndTableView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
		return m_wndXmlView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
	}
	return FALSE;
}

void CTCSequenceWnd::OnSize(UINT nType, int cx, int cy)
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

void CTCSequenceWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()) && !bActivate) m_wndTableView.UnSelectAll();
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CTCSequenceWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (IsWindow(m_wndTableView.GetSafeHwnd()) && nChar == VK_DOWN) m_wndTableView.ActivateTable();
	CDisplayWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTCSequenceWnd::OnClose()
{
	CHourglassCursor  cCursor;

	DoClose();
	CDisplayWnd::OnClose();
}

void CTCSequenceWnd::OnUpdateStatusBarDetailsPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCSequenceWnd::OnUpdateStatusBarFlagPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCSequenceWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
