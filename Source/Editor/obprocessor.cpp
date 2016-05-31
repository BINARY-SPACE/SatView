// OBPROCESSOR.CPP : On-Board Processor Form Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the on-board processor
// form related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2006/04/16 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nStatusBarIndicators[] =
{
	ID_OBPROCESSOR_STATUSBAR_DETAILSPANE,
	ID_OBPROCESSOR_STATUSBAR_FLAGPANE,
	ID_OBPROCESSOR_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// COBProcessorOpenDialog dialog

IMPLEMENT_DYNCREATE(COBProcessorOpenDialog, CLocaleDialog)

COBProcessorOpenDialog::COBProcessorOpenDialog(CWnd *pParentWnd) : CLocaleDialog(COBProcessorOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(COBProcessorOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COBProcessorOpenDialog::Initialize()
{
	m_pDatabaseOBProcessors.Copy(GetDatabase()->GetOBProcessors());
	return TRUE;
}

VOID COBProcessorOpenDialog::EnumOBProcessors()
{
	INT  nColumn;
	INT  nColumns;
	INT  nProcessor;
	INT  nProcessors;
	CString  szItem;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	for (nProcessor = 0, nProcessors = (INT)m_pDatabaseOBProcessors.GetSize(); nProcessor < nProcessors; nProcessor++)
	{
		if ((pDatabaseOBProcessor = m_pDatabaseOBProcessors.GetAt(nProcessor)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OBPROCESSOROPENDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pDatabaseOBProcessor->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OBPROCESSOROPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? pDatabaseOBProcessor->GetDescription() : pDatabaseOBProcessor->GetDetails();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY), nProcessor, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY), nProcessor, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY), 0);
	GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL COBProcessorOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void COBProcessorOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COBProcessorOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COBProcessorOpenDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseOBProcessors.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COBProcessorOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(COBProcessorOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OBPROCESSOR_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBProcessorOpenDialog message handlers

BOOL COBProcessorOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_OBPROCESSOROPENDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_OBPROCESSOROPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_OBPROCESSOR_OPEN_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (2 * rColumns.Width()) / 9; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumOBProcessors();
	GetDlgItem(IDC_OBPROCESSOR_OPEN_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_OBPROCESSOR_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_OPEN_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_OPEN_DATABASE)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY)->SetFocus();
	return FALSE;
}

BOOL COBProcessorOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_OBPROCESSOR_OPEN_DIRECTORY)
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

void COBProcessorOpenDialog::OnOK()
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
	COBProcessorWnd  *pOBProcessorWnd;
	CHourglassCursor  cCursor;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_OBPROCESSOROPENDIALOG_DIRECTORYTITLEITEM_NAME))
		{
			szTag = Listview_GetText(GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY)), nColumn);
			continue;
		}
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_OBPROCESSOROPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
		{
			szDescription = Listview_GetText(GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_OBPROCESSOR_OPEN_DIRECTORY)), nColumn);
			continue;
		}
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_OBPROCESSOR)
		{
			if ((pOBProcessorWnd = (COBProcessorWnd *)pDisplayWnd)->GetName() == szTag)
			{
				pOBProcessorWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		if ((pOBProcessorWnd = new COBProcessorWnd(szTag)))
		{
			if (pOBProcessorWnd->Create(GetMainWnd()))
			{
				EndDialog(IDOK);
				return;
			}
		}
		szMessage.Format(STRING(IDS_OBPROCESSOR_FAILURE_LOAD), (LPCTSTR)szDescription);
		ShowMessage(szMessage);
	}
	EndDialog(IDOK);
}

void COBProcessorOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL COBProcessorOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_OBPROCESSOROPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COBProcessorOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_OBPROCESSOROPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COBProcessorImportDialog dialog

IMPLEMENT_DYNCREATE(COBProcessorImportDialog, CLocaleDialog)

COBProcessorImportDialog::COBProcessorImportDialog(CWnd *pParentWnd) : CLocaleDialog(COBProcessorImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(COBProcessorImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR COBProcessorImportDialog::DoModal(CDatabaseOBProcessors &pDatabaseOBProcessors)
{
	INT_PTR  nResult;

	for (m_pDatabaseOBProcessors.RemoveAll(); (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		pDatabaseOBProcessors.Copy(&m_pDatabaseOBProcessors);
		break;
	}
	return nResult;
}

VOID COBProcessorImportDialog::EnumOBProcessors()
{
	INT  nColumn;
	INT  nColumns;
	INT  nProcessor;
	INT  nProcessors;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szItem;
	CString  szFileName;
	CByteArray  cFileBuffer;
	CFileFindEx  cFileFind;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	SendDlgItemMessage(IDC_OBPROCESSOR_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				for (nProcessor = 0, nProcessors = (m_pDatabaseOBProcessors.Unmap(cFileBuffer, FALSE)) ? (INT)m_pDatabaseOBProcessors.GetSize() : 0; nProcessor < nProcessors; nProcessor++)
				{
					if ((pDatabaseOBProcessor = m_pDatabaseOBProcessors.GetAt(nProcessor)))
					{
						for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OBPROCESSORIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
							{
								szItem = pDatabaseOBProcessor->GetName();
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OBPROCESSORIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
							{
								szItem = (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? pDatabaseOBProcessor->GetDescription() : pDatabaseOBProcessor->GetDetails();
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_OBPROCESSOR_IMPORT_DIRECTORY), nProcessor, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_OBPROCESSOR_IMPORT_DIRECTORY), nProcessor, nColumn, szItem);
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
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL COBProcessorImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_OBPROCESSOR_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OBPROCESSOR_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_OBPROCESSOR_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void COBProcessorImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COBProcessorImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COBProcessorImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COBProcessorImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(COBProcessorImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OBPROCESSOR_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_OBPROCESSOR_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_OBPROCESSOR_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_OBPROCESSOR_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBProcessorImportDialog message handlers

BOOL COBProcessorImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_OBPROCESSORIMPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_OBPROCESSORIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_OBPROCESSOR_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME, EM_LIMITTEXT, GetDatabase()->GetOBProcessorNameLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_OBPROCESSOR_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_OBPROCESSOR_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL COBProcessorImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_OBPROCESSOR_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_OBPROCESSOR_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM)->EnableWindow();
			}
			else
			{
				CheckDlgButton(IDC_OBPROCESSOR_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void COBProcessorImportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_OBPROCESSOR_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_OBPROCESSOR_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumOBProcessors();
	}
	SendDlgItemMessage(IDC_OBPROCESSOR_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorImportDialog::OnDefault()
{
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorImportDialog::OnCustom()
{
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorImportDialog::OnEditchangeFileName()
{
	EnumOBProcessors();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorImportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorImportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorImportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nProcessor;
	INT  nProcessors;
	CString  szName;
	CString  szDescription;
	CPtrArray  pParameters;
	CUIntArray  nProcessorIDs;
	CDatabaseOBProcessor  *pDatabaseOBProcessor[2];
	CDatabaseOBProcessors  pDatabaseOBProcessors;
	CHourglassCursor  cCursor;

	for (nProcessor = 0, nProcessors = (INT)SendDlgItemMessage(IDC_OBPROCESSOR_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nProcessor < nProcessors; nProcessor++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_OBPROCESSOR_IMPORT_DIRECTORY), nProcessor))
		{
			delete m_pDatabaseOBProcessors.GetAt(nProcessor);
			m_pDatabaseOBProcessors.SetAt(nProcessor, NULL);
		}
	}
	for (nProcessor = 0, nProcessors = (pDatabaseOBProcessors.Copy(GetDatabase()->GetOBProcessors())) ? nProcessors : -1; nProcessor < nProcessors; nProcessor++)
	{
		if ((pDatabaseOBProcessor[0] = m_pDatabaseOBProcessors.GetAt(nProcessor)))
		{
			if (IsDlgButtonChecked(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM))
			{
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
				GetDlgItem(IDC_OBPROCESSOR_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
				pDatabaseOBProcessor[0]->SetName(szName);
				pDatabaseOBProcessor[0]->SetDescription(szDescription);
			}
			if ((pDatabaseOBProcessor[1] = pDatabaseOBProcessors.GetAt((nIndex = pDatabaseOBProcessors.Find(pDatabaseOBProcessor[0]->GetName())))))
			{
				pDatabaseOBProcessor[1]->Copy(pDatabaseOBProcessor[0]);
				pParameters.Add(pDatabaseOBProcessor[1]);
				nProcessorIDs.Add(nIndex);
				continue;
			}
			if ((pDatabaseOBProcessor[1] = new CDatabaseOBProcessor))
			{
				pDatabaseOBProcessor[1]->Copy(pDatabaseOBProcessor[0]);
				if ((nIndex = pDatabaseOBProcessors.Add(pDatabaseOBProcessor[1])) >= 0)
				{
					pParameters.Add(pDatabaseOBProcessor[1]);
					nProcessorIDs.Add(-(nIndex + 1));
					continue;
				}
				delete pDatabaseOBProcessor[1];
			}
			break;
		}
		m_pDatabaseOBProcessors.RemoveAt(nProcessor);
		nProcessors--;
		nProcessor--;
	}
	for (; nProcessor == nProcessors; )
	{
		if (GetDatabase()->GetOBProcessors()->Copy(&pDatabaseOBProcessors))
		{
			for (nItem = 0, nItems = (INT)pParameters.GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseOBProcessor[0] = (CDatabaseOBProcessor *)pParameters.GetAt(nItem)))
				{
					if (GetDatabase()->Save(pDatabaseOBProcessor[0]))
					{
						nIndex = (INT)nProcessorIDs.GetAt(nItem);
						UpdateDatabase(pDatabaseOBProcessor[0], nIndex);
						continue;
					}
				}
				break;
			}
			if (nItem == nItems) break;
		}
		nProcessors = -1;
		break;
	}
	for (; nProcessor != nProcessors; )
	{
		ShowMessage((SendDlgItemMessage(IDC_OBPROCESSOR_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_OBPROCESSORDIRECTORY_IMPORT_FAILURE : SYSTEM_WARNING_OBPROCESSOR_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void COBProcessorImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL COBProcessorImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_OBPROCESSORIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COBProcessorImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_OBPROCESSORIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COBProcessorExportDialog dialog

IMPLEMENT_DYNCREATE(COBProcessorExportDialog, CLocaleDialog)

COBProcessorExportDialog::COBProcessorExportDialog(CWnd *pParentWnd) : CLocaleDialog(COBProcessorExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(COBProcessorExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR COBProcessorExportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

BOOL COBProcessorExportDialog::EnumOBProcessors()
{
	INT  nColumn;
	INT  nColumns;
	INT  nProcessor;
	INT  nProcessors;
	CString  szItem;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	for (nProcessor = 0, nProcessors = (m_pDatabaseOBProcessors.Copy(GetDatabase()->GetOBProcessors())) ? (INT)m_pDatabaseOBProcessors.GetSize() : 0; nProcessor < nProcessors; nProcessor++)
	{
		if ((pDatabaseOBProcessor = m_pDatabaseOBProcessors.GetAt(nProcessor)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OBPROCESSOREXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pDatabaseOBProcessor->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OBPROCESSOREXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? pDatabaseOBProcessor->GetDescription() : pDatabaseOBProcessor->GetDetails();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_OBPROCESSOR_EXPORT_DIRECTORY), nProcessor, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_OBPROCESSOR_EXPORT_DIRECTORY), nProcessor, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_OBPROCESSOR_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL COBProcessorExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_OBPROCESSOR_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OBPROCESSOR_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_OBPROCESSOR_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void COBProcessorExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COBProcessorExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COBProcessorExportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseOBProcessors.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COBProcessorExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(COBProcessorExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OBPROCESSOR_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_OBPROCESSOR_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_OBPROCESSOR_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_OBPROCESSOR_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBProcessorExportDialog message handlers

BOOL COBProcessorExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_OBPROCESSOREXPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_OBPROCESSOREXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_OBPROCESSOR_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME, EM_LIMITTEXT, GetDatabase()->GetOBProcessorNameLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_OBPROCESSOR_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumOBProcessors())
	{
		CheckDlgButton(IDC_OBPROCESSOR_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_OBPROCESSOR_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_OBPROCESSOR_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_OBPROCESSOR_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_OBPROCESSOR_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM)->EnableWindow();
		GetDlgItem(IDC_OBPROCESSOR_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL COBProcessorExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_OBPROCESSOR_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_OBPROCESSOR_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM)->EnableWindow();
				CheckDlgButton(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM, FALSE);
			}
			else
			{
				CheckDlgButton(IDC_OBPROCESSOR_EXPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void COBProcessorExportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_OBPROCESSOR_EXPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_OBPROCESSOR_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_OBPROCESSOR_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorExportDialog::OnDefault()
{
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorExportDialog::OnCustom()
{
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorExportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorExportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorExportDialog::OnOK()
{
	INT  nProcessor;
	INT  nProcessors;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szName;
	CString  szFileName;
	CString  szDescription;
	CByteArray  cFileBuffer;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;
	CHourglassCursor  cCursor;

	for (nProcessor = 0, nProcessors = (INT)SendDlgItemMessage(IDC_OBPROCESSOR_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nProcessor < nProcessors; nProcessor++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_OBPROCESSOR_EXPORT_DIRECTORY), nProcessor))
		{
			delete m_pDatabaseOBProcessors.GetAt(nProcessor);
			m_pDatabaseOBProcessors.SetAt(nProcessor, NULL);
		}
	}
	for (nProcessor = 0; nProcessor < nProcessors; nProcessor++)
	{
		if (!m_pDatabaseOBProcessors.GetAt(nProcessor))
		{
			m_pDatabaseOBProcessors.RemoveAt(nProcessor);
			nProcessors--;
			nProcessor--;
		}
	}
	if ((pDatabaseOBProcessor = (IsDlgButtonChecked(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseOBProcessors.GetAt(nProcessor) : (CDatabaseOBProcessor *)NULL))
	{
		GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_OBPROCESSOR_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
		pDatabaseOBProcessor->SetName(szName);
		pDatabaseOBProcessor->SetDescription(szDescription);
	}
	for (; nProcessor == nProcessors; )
	{
		if (m_pDatabaseOBProcessors.Map(cFileBuffer, FALSE))
		{
			GetDlgItem(IDC_OBPROCESSOR_EXPORT_FILENAME)->GetWindowText(szFileName);
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
		nProcessors = -1;
		break;
	}
	for (; nProcessor != nProcessors; )
	{
		ShowMessage((SendDlgItemMessage(IDC_OBPROCESSOR_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_OBPROCESSORDIRECTORY_EXPORT_FAILURE : SYSTEM_WARNING_OBPROCESSOR_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void COBProcessorExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL COBProcessorExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_OBPROCESSOREXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COBProcessorExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_OBPROCESSOREXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COBProcessorPropertiesDialog dialog

IMPLEMENT_DYNCREATE(COBProcessorPropertiesDialog, CLocaleDialog)

COBProcessorPropertiesDialog::COBProcessorPropertiesDialog(CWnd *pParentWnd) : CLocaleDialog(COBProcessorPropertiesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(COBProcessorPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COBProcessorPropertiesDialog::Initialize()
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

INT_PTR COBProcessorPropertiesDialog::DoModal(COBProcessorWnd *pParentWnd)
{
	INT_PTR  nResult;

	for (m_pParentWnd = (CWnd *)pParentWnd; (nResult = CLocaleDialog::DoModal()); ) break;
	return nResult;
}

VOID COBProcessorPropertiesDialog::ShowFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_RESETCONTENT); (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE) && cFontTools.EnumerateFont(m_lfTable[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_ITEMS) && cFontTools.EnumerateFont(m_lfTable[0][1].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE))
	{
		SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][0])), 0));
		SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][0])), max(SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][0])), 0)));
		SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]);
	}
	if (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_ITEMS))
	{
		SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][1])), 0));
		SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][1])), max(SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][1])), 0)));
		SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]);
	}
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID COBProcessorPropertiesDialog::ShowFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

COBProcessorWnd *COBProcessorPropertiesDialog::GetParent() CONST
{
	return((COBProcessorWnd *)CLocaleDialog::GetParent());
}

BOOL COBProcessorPropertiesDialog::IsModified() CONST
{
	CFontTools  cFontTools;

	return((lstrcmp(m_lfTable[0][0].lfFaceName, m_lfTable[1][0].lfFaceName) || (m_lfTable[0][0].lfHeight != m_lfTable[1][0].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][0]))) || m_lfTable[0][0].lfWeight != m_lfTable[1][0].lfWeight || m_lfTable[0][0].lfItalic != m_lfTable[1][0].lfItalic || lstrcmp(m_lfTable[0][1].lfFaceName, m_lfTable[1][1].lfFaceName) || (m_lfTable[0][1].lfHeight != m_lfTable[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][1])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][1]))) || m_lfTable[0][1].lfWeight != m_lfTable[1][1].lfWeight || m_lfTable[0][1].lfItalic != m_lfTable[1][1].lfItalic || GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]) != GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][0]) || GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]) != GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][1]) || GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]) != GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][0]) || GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]) != GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][1])) ? TRUE : FALSE);
}

BOOL COBProcessorPropertiesDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void COBProcessorPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COBProcessorPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COBProcessorPropertiesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(COBProcessorPropertiesDialog)
	ON_WM_PAINT()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_OBPROCESSOR_PROPERTIES_FONTS_ITEMS, OnItemsFont)
	ON_BN_CLICKED(IDC_OBPROCESSOR_PROPERTIES_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR, OnSelchangeFontColor)
	ON_CBN_SELCHANGE(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE, OnSelchangeTitleBackgroundColor)
	ON_CBN_SELCHANGE(IDC_OBPROCESSOR_PROPERTIES_COLORS_KEYS, OnSelchangeKeysBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBProcessorPropertiesDialog message handlers

BOOL COBProcessorPropertiesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	CheckDlgButton(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE, TRUE);
	CheckDlgButton(IDC_OBPROCESSOR_PROPERTIES_FONTS_ITEMS, FALSE);
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_COLORS_KEYS, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_COLORS_KEYS, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]);
	SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_COLORS_KEYS, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]);
	AccessControl(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE));
	AccessControl(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE));
	AccessControl(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE));
	AccessControl(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR, CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE));
	AccessControl(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE));
	AccessControl(IDC_OBPROCESSOR_PROPERTIES_COLORS_KEYS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE));
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_ITEMS)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_COLORS_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_COLORS_KEYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_COLORS_KEYS)->EnableWindow();
	ShowFontDetails();
	return TRUE;
}

void COBProcessorPropertiesDialog::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE)) ? &m_lfTable[0][0] : &m_lfTable[0][1]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE)) ? m_nTableFontColors[0][0] : m_nTableFontColors[0][1]) : GetSysColor(COLOR_GRAYTEXT));
			cDC.FillSolidRect(rSampleText, (SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE)) ? m_nTableColors[0][0] : GetSysColor(COLOR_3DFACE)) : GetSysColor(COLOR_3DFACE));
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

void COBProcessorPropertiesDialog::OnTitleFont()
{
	SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void COBProcessorPropertiesDialog::OnItemsFont()
{
	SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][1].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void COBProcessorPropertiesDialog::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorPropertiesDialog::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE))
	{
		lstrcpy(m_lfTable[0][0].lfFaceName, Combobox_GetText(GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_ITEMS))
	{
		lstrcpy(m_lfTable[0][1].lfFaceName, Combobox_GetText(GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][0]);
	}
	if (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][1]);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorPropertiesDialog::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorPropertiesDialog::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_OBPROCESSOR_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorPropertiesDialog::OnSelchangeFontColor()
{
	for (; IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_TITLE); )
	{
		m_nTableFontColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	for (; IsDlgButtonChecked(IDC_OBPROCESSOR_PROPERTIES_FONTS_ITEMS); )
	{
		m_nTableFontColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorPropertiesDialog::OnSelchangeTitleBackgroundColor()
{
	for (m_nTableColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_COLORS_TITLE, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorPropertiesDialog::OnSelchangeKeysBackgroundColor()
{
	for (m_nTableColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_COLORS_KEYS, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_OBPROCESSOR_PROPERTIES_COLORS_KEYS, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COBProcessorPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParent()->SetProperties(&m_lfTable[0][0], &m_lfTable[0][1], m_nTableFontColors[0][0], m_nTableFontColors[0][1], m_nTableColors[0][0], m_nTableColors[0][1]);
	EndDialog(IDOK);
}

void COBProcessorPropertiesDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL COBProcessorPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_OBPROCESSORPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COBProcessorPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_OBPROCESSORPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COBProcessorStatusBar

IMPLEMENT_DYNCREATE(COBProcessorStatusBar, CMFCStatusBar)

BOOL COBProcessorStatusBar::SetIndicators(CONST UINT *pIDs, INT nCount)
{
	INT  nIndex;
	CString  szText;

	for (Initialize(); CMFCStatusBar::SetIndicators(pIDs, nCount); )
	{
		if ((nIndex = CommandToIndex(ID_OBPROCESSOR_STATUSBAR_DETAILSPANE)) >= 0)
		{
			szText.Format(STRING(IDS_OBPROCESSOR_STATUSBAR_DETAILS), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_OBPROCESSOR_STATUSBAR_DETAILSPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(nIndex, szText));
		}
		if ((nIndex = CommandToIndex(ID_OBPROCESSOR_STATUSBAR_FLAGPANE)) >= 0)
		{
			szText.Format(STRING(IDS_OBPROCESSOR_STATUSBAR_FLAG), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_OBPROCESSOR_STATUSBAR_FLAGPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_OBPROCESSOR_STATUSBAR_FLAGPANE));
		}
		if ((nIndex = CommandToIndex(ID_OBPROCESSOR_STATUSBAR_TYPEPANE)) >= 0)
		{
			szText.Format(STRING(IDS_OBPROCESSOR_STATUSBAR_TYPE), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_OBPROCESSOR_STATUSBAR_TYPEPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_OBPROCESSOR_STATUSBAR_TYPEPANE));
		}
		return TRUE;
	}
	return FALSE;
}

BOOL COBProcessorStatusBar::SetPaneText(UINT nID, LPCTSTR pszText)
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

BOOL COBProcessorStatusBar::GetPaneText(UINT nID, CString &szText) CONST
{
	INT  nIndex;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		szText = CMFCStatusBar::GetPaneText(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString COBProcessorStatusBar::GetPaneText(UINT nID) CONST
{
	CString  szText;

	return((GetPaneText(nID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

INT COBProcessorStatusBar::CalcPaneWidth(INT nIndex) CONST
{
	return CalcPaneWidth(nIndex, CMFCStatusBar::GetPaneText(nIndex));
}
INT COBProcessorStatusBar::CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST
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

VOID COBProcessorStatusBar::Initialize()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = GetCount(); nIndex < nCount; nIndex++)
	{
		SetTipText(nIndex, (LPCTSTR)NULL);
		continue;
	}
}

BEGIN_MESSAGE_MAP(COBProcessorStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(COBProcessorStatusBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBProcessorStatusBar message handlers


/////////////////////////////////////////////////////////////////////////////
// COBProcessorView

IMPLEMENT_DYNCREATE(COBProcessorView, CDisplayTableView)

COBProcessorView::COBProcessorView() : CDisplayTableView(DATABASE_COMPONENT_OBPROCESSOR, IDR_OBPROCESSORFRAMEMENU)
{
	return;
}

VOID COBProcessorView::SetTitle(LPCTSTR pszName, LPCTSTR pszTitle)
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	if ((pDatabaseOBProcessor = m_pDatabaseOBProcessors[0].GetAt(m_pDatabaseOBProcessors[0].Find(pszName))))
	{
		for (pDatabaseOBProcessor->SetDescription(pszTitle); !m_szName.Compare(pszName); )
		{
			UpdateTables();
			break;
		}
	}
	m_szName = pszName;
	m_szTitle = pszTitle;
}

BOOL COBProcessorView::GetTitle(CString &szName, CString &szTitle) CONST
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	for (szName.Empty(), szTitle.Empty(); (pDatabaseOBProcessor = m_pDatabaseOBProcessors[0].GetAt(m_pDatabaseOBProcessors[0].Find(GetName()))); )
	{
		szTitle = (!pDatabaseOBProcessor->GetDescription().IsEmpty()) ? pDatabaseOBProcessor->GetDescription() : pDatabaseOBProcessor->GetDetails();
		szName = pDatabaseOBProcessor->GetName();
		return TRUE;
	}
	szName = m_szName;
	szTitle = m_szTitle;
	return !szName.IsEmpty();
}

BOOL COBProcessorView::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	for (SetTablesFonts(plfTitle, plfItems), SetTablesFontColors(nTitleColor, nItemsColor), SetTablesColors(nTitleBackground, nKeysBackground); IsWindow(GetSafeHwnd()); )
	{
		RepositionTables();
		break;
	}
	return TRUE;
}

BOOL COBProcessorView::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	GetTablesFonts(plfTitle, plfItems);
	GetTablesFontColors(nTitleColor, nItemsColor);
	GetTablesColors(nTitleBackground, nKeysBackground);
	return TRUE;
}

VOID COBProcessorView::UpdateTableForms(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nIndex, BOOL bDelete)
{
	UpdateDatabase(pDatabaseOBProcessor, (nIndex > 0) ? (nIndex - 1) : nIndex, bDelete);
	UpdateForms(GetParent(), pDatabaseOBProcessor, bDelete);
	UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE);
}
VOID COBProcessorView::UpdateTableForms(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseOBProcessorMemoryImage, bDelete);
	UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE);
}

COBProcessorWnd *COBProcessorView::GetParent() CONST
{
	return((COBProcessorWnd *)CDisplayTableView::GetParent());
}

BOOL COBProcessorView::CheckPrivilege() CONST
{
	return CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE);
}

BEGIN_MESSAGE_MAP(COBProcessorView, CDisplayTableView)
	//{{AFX_MSG_MAP(COBProcessorView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBProcessorView message handlers

int COBProcessorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayTableView::OnCreate(lpCreateStruct) != -1 && GetDatabase()->CreateTables(this, GetComponent())) ? 0 : -1);
}


/////////////////////////////////////////////////////////////////////////////
// COBProcessorWnd

IMPLEMENT_DYNCREATE(COBProcessorWnd, CDisplayWnd)

COBProcessorWnd::COBProcessorWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_OBPROCESSOR);
}
COBProcessorWnd::COBProcessorWnd(LPCTSTR pszName) : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_OBPROCESSOR);
	SetName(pszName);
}

BOOL COBProcessorWnd::Create(CMDIFrameWnd *pParentWnd, UINT nShow)
{
	return Create(pParentWnd, GetName(), nShow);
}
BOOL COBProcessorWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszName, UINT nShow)
{
	CRect  rPosition;

	for (SetName(pszName), rPosition = m_rPosition; CDisplayWnd::Create(pParentWnd, STRING(IDS_DISPLAY_TITLE_OBPROCESSOR), (nShow == (UINT)-1) ? CRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) : CRect(0, 0, 0, 0), IDR_OBPROCESSORFRAME, (nShow != SW_SHOWMINIMIZED || nShow != SW_SHOWMAXIMIZED) ? (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE) : (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW)); )
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

VOID COBProcessorWnd::SetName(LPCTSTR pszName)
{
	m_wndView.SetName(pszName);
}

CString COBProcessorWnd::GetName() CONST
{
	return m_wndView.GetName();
}

VOID COBProcessorWnd::SetTitle(LPCTSTR pszTitle)
{
	m_wndView.SetTitle(GetName(), pszTitle);
}

CString COBProcessorWnd::GetTitle() CONST
{
	CString  szName;
	CString  szTitle;

	return((m_wndView.GetTitle(szName, szTitle)) ? szTitle : STRING(IDS_DISPLAY_TITLE_OBPROCESSOR));
}

BOOL COBProcessorWnd::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	return m_wndView.SetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL COBProcessorWnd::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	return m_wndView.GetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL COBProcessorWnd::IsModified() CONST
{
	return((m_wndView.Check()) ? m_wndView.IsModified() : FALSE);
}

BOOL COBProcessorWnd::Save(INT nPosition) CONST
{
	UINT  nShowFlags;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	cProfile.DeleteDisplayWindowInfo(nPosition);
	return((GetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && cProfile.SetDisplayWindowType(nPosition, GetType()) && cProfile.SetDisplayWindowName(nPosition, GetName()) && cProfile.SetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, (nShowFlags = (!IsIconic()) ? ((!IsZoomed()) ? SW_SHOWNORMAL : SW_SHOWMAXIMIZED) : SW_SHOWMINIMIZED)) && cProfile.SetOBProcessorsFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? TRUE : FALSE);
}

INT COBProcessorWnd::Load(INT nPosition)
{
	UINT  nShowFlags;
	CString  szName;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	return((cProfile.GetDisplayWindowName(nPosition, szName) && cProfile.GetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, nShowFlags) && cProfile.GetOBProcessorsFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && SetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? COBProcessorWnd::Create(GetMainWnd(), szName, nShowFlags) : -1);
}

BOOL COBProcessorWnd::UpdateProperties()
{
	return((m_dlgProperties.DoModal(this) == IDOK) ? TRUE : FALSE);
}

BOOL COBProcessorWnd::IsUpdatingProperties() CONST
{
	return IsWindow(m_dlgProperties.GetSafeHwnd());
}

BOOL COBProcessorWnd::HasProperties() CONST
{
	return TRUE;
}

BOOL COBProcessorWnd::CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST
{
	return m_wndView.CheckTableDropTarget(pszTable, nComponent, point);
}

BOOL COBProcessorWnd::DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point)
{
	return m_wndView.DropOnTableTarget(pszTable, nComponent, point);
}

VOID COBProcessorWnd::UpdateAllPanes(LPCTSTR pszDetails, LPCTSTR pszFlag, LPCTSTR pszType)
{
	m_wndStatusBar.SetPaneText(ID_OBPROCESSOR_STATUSBAR_DETAILSPANE, pszDetails);
	m_wndStatusBar.SetPaneText(ID_OBPROCESSOR_STATUSBAR_FLAGPANE, pszFlag);
	m_wndStatusBar.SetPaneText(ID_OBPROCESSOR_STATUSBAR_TYPEPANE, pszType);
}

BOOL COBProcessorWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
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
				if (PrintJob(cDC, &m_wndView, STRING(IDS_DISPLAY_TITLE_OBPROCESSOR), cPrintProfileInfo.GetPrinterName(), rtMargin[0], bMetrics, nFlags))
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
					if (PrintJob(cDC, &m_wndView, STRING(IDS_DISPLAY_TITLE_OBPROCESSOR), (LPCTSTR)pDevMode->dmDeviceName, rtMargin[0], bMetrics, nFlags, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : -1, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : -1))
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

VOID COBProcessorWnd::DoSave()
{
	if (m_wndView.DoSave())
	{
		GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_OBPROCESSOR);
		return;
	}
}

BOOL COBProcessorWnd::CanSave() CONST
{
	return((m_wndView.CanSave()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

VOID COBProcessorWnd::DoCheck()
{
	m_wndView.DoCheck();
}

BOOL COBProcessorWnd::CanCheck() CONST
{
	return((m_wndView.CanCheck()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

VOID COBProcessorWnd::DoDelete()
{
	CString  szName;
	CString  szTitle;

	for (szName = GetName(), szTitle = GetTitle(); m_wndView.DoDelete(); )
	{
		GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_OBPROCESSOR);
		break;
	}
}

BOOL COBProcessorWnd::CanDelete() CONST
{
	return((m_wndView.CanDelete()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

VOID COBProcessorWnd::DoUndo()
{
	m_wndView.DoUndo();
}

BOOL COBProcessorWnd::CanUndo() CONST
{
	return m_wndView.CanUndo();
}

VOID COBProcessorWnd::DoRedo()
{
	m_wndView.DoRedo();
}

BOOL COBProcessorWnd::CanRedo() CONST
{
	return m_wndView.CanRedo();
}

VOID COBProcessorWnd::DoSelectAll()
{
	m_wndView.DoSelectAll();
}

BOOL COBProcessorWnd::CanSelectAll() CONST
{
	return m_wndView.CanSelectAll();
}

VOID COBProcessorWnd::DoCutSel()
{
	m_wndView.DoCutSel();
}

BOOL COBProcessorWnd::CanCutSel() CONST
{
	return m_wndView.CanCutSel();
}

VOID COBProcessorWnd::DoCopySel()
{
	m_wndView.DoCopySel();
}

BOOL COBProcessorWnd::CanCopySel() CONST
{
	return m_wndView.CanCopySel();
}

VOID COBProcessorWnd::DoPasteSel()
{
	m_wndView.DoPasteSel();
}

BOOL COBProcessorWnd::CanPasteSel() CONST
{
	return m_wndView.CanPasteSel();
}

VOID COBProcessorWnd::DoDeleteSel()
{
	m_wndView.DoDeleteSel();
}

BOOL COBProcessorWnd::CanDeleteSel() CONST
{
	return m_wndView.CanDeleteSel();
}

BOOL COBProcessorWnd::CanPrint(UINT nFlags) CONST
{
	return m_wndView.CanPrint(nFlags);
}

VOID COBProcessorWnd::DoClose()
{
	m_wndView.DoClose();
}

BOOL COBProcessorWnd::DoSaveTable()
{
	return m_wndView.DoSaveTable();
}

BOOL COBProcessorWnd::CanSaveTable() CONST
{
	return((m_wndView.CanSaveTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoCheckTable()
{
	return m_wndView.DoCheckTable();
}

BOOL COBProcessorWnd::CanCheckTable() CONST
{
	return((m_wndView.CanCheckTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoDeleteTable()
{
	return m_wndView.DoDeleteTable();
}

BOOL COBProcessorWnd::CanDeleteTable() CONST
{
	return((m_wndView.CanDeleteTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoPrintTable()
{
	return Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE);
}

BOOL COBProcessorWnd::CanPrintTable() CONST
{
	return CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE);
}

BOOL COBProcessorWnd::DoPrintAllTables()
{
	return Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL);
}

BOOL COBProcessorWnd::CanPrintAllTables() CONST
{
	return CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL);
}

BOOL COBProcessorWnd::DoImportTables()
{
	return m_wndView.DoImportTables();
}

BOOL COBProcessorWnd::CanImportTables() CONST
{
	return((m_wndView.CanImportTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoExportTables()
{
	return m_wndView.DoExportTables();
}

BOOL COBProcessorWnd::CanExportTables() CONST
{
	return m_wndView.CanExportTables();
}

BOOL COBProcessorWnd::DoDiscardTables()
{
	return m_wndView.DoDiscardTables();
}

BOOL COBProcessorWnd::CanDiscardTables() CONST
{
	return((m_wndView.CanDiscardTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoDiscardAllTables()
{
	return m_wndView.DoDiscardAllTables();
}

BOOL COBProcessorWnd::CanDiscardAllTables() CONST
{
	return((m_wndView.CanDiscardAllTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoResetTables()
{
	return m_wndView.DoResetTables();
}

BOOL COBProcessorWnd::CanResetTables() CONST
{
	return((m_wndView.CanResetTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoInsertTableRowAbove()
{
	return m_wndView.DoInsertTableRowAbove();
}

BOOL COBProcessorWnd::CanInsertTableRowAbove() CONST
{
	return((m_wndView.CanInsertTableRowAbove()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoInsertTableRowBelow()
{
	return m_wndView.DoInsertTableRowBelow();
}

BOOL COBProcessorWnd::CanInsertTableRowBelow() CONST
{
	return((m_wndView.CanInsertTableRowBelow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoInsertTableColumnBefore()
{
	return m_wndView.DoInsertTableColumnBefore();
}

BOOL COBProcessorWnd::CanInsertTableColumnBefore() CONST
{
	return((m_wndView.CanInsertTableColumnBefore()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoInsertTableColumnAfter()
{
	return m_wndView.DoInsertTableColumnAfter();
}

BOOL COBProcessorWnd::CanInsertTableColumnAfter() CONST
{
	return((m_wndView.CanInsertTableColumnAfter()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoClearTableRow()
{
	return m_wndView.DoClearTableRow();
}

BOOL COBProcessorWnd::CanClearTableRow() CONST
{
	return((m_wndView.CanClearTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoDeleteTableRow()
{
	return m_wndView.DoDeleteTableRow();
}

BOOL COBProcessorWnd::CanDeleteTableRow() CONST
{
	return((m_wndView.CanDeleteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoDeleteTableColumn()
{
	return m_wndView.DoDeleteTableColumn();
}

BOOL COBProcessorWnd::CanDeleteTableColumn() CONST
{
	return((m_wndView.CanDeleteTableColumn()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

BOOL COBProcessorWnd::DoCopyTableRow()
{
	return m_wndView.DoCopyTableRow();
}

BOOL COBProcessorWnd::CanCopyTableRow() CONST
{
	return m_wndView.CanCopyTableRow();
}

BOOL COBProcessorWnd::DoPasteTableRow()
{
	return m_wndView.DoPasteTableRow();
}

BOOL COBProcessorWnd::CanPasteTableRow() CONST
{
	return((m_wndView.CanPasteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE) : FALSE);
}

VOID COBProcessorWnd::GotoTable(ULONGLONG nComponent, LPCTSTR pszName)
{
	m_wndView.GotoTable(nComponent, pszName);
}

VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseOBProcessors &pDatabaseOBProcessors)
{
	m_wndView.UpdateTables(pDatabaseOBProcessors);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE, pDatabaseOBProcessor->GetName(), bDelete);
}
VOID COBProcessorWnd::UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE, pDatabaseOBProcessorMemoryImage->GetName(), bDelete);
}
VOID COBProcessorWnd::UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE);
}
VOID COBProcessorWnd::UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE);
}
VOID COBProcessorWnd::UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE);
}
VOID COBProcessorWnd::UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete)
{
	m_wndView.UpdateTables(nComponent, pszName, bDelete);
	m_wndView.ClearUndo();
}
VOID COBProcessorWnd::UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete)
{
	m_wndView.UpdateTables(nComponent, nID, bDelete);
	m_wndView.ClearUndo();
}
VOID COBProcessorWnd::UpdateTables(ULONGLONG nComponent)
{
	m_wndView.UpdateTables(nComponent);
}
VOID COBProcessorWnd::UpdateTables()
{
	m_wndView.UpdateTables();
}

VOID COBProcessorWnd::UpdateTitle()
{
	SetWindowText(STRING(IDS_DISPLAY_TITLE_OBPROCESSOR));
}

VOID COBProcessorWnd::UpdateMenus()
{
	GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
}

VOID COBProcessorWnd::UpdateStatusBar()
{
	CString  szFlag;
	CString  szType;
	CString  szDetails;

	for (m_wndStatusBar.SetIndicators(nStatusBarIndicators, sizeof(nStatusBarIndicators) / sizeof(UINT)); m_wndView.GetPanesInfo(szDetails, szFlag, szType); )
	{
		UpdateAllPanes(szDetails, szFlag, szType);
		break;
	}
}

CString COBProcessorWnd::GetPrintDocTitle(LPCTSTR pszName, UINT nFlags) CONST
{
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	return(((pDatabaseOBProcessor = (nFlags & DISPLAYTABLEVIEW_PRINT_TABLE) ? GetDatabase()->GetOBProcessors()->GetAt(GetDatabase()->GetOBProcessors()->Find(pszName)) : (CDatabaseOBProcessor *)NULL) && !pDatabaseOBProcessor->GetName().IsEmpty()) ? (LPCTSTR)pDatabaseOBProcessor->GetName() : pszName);
}

CString COBProcessorWnd::GetPrintDocInfoTitle() CONST
{
	return STRING(IDS_DISPLAY_TITLE_OBPROCESSOR);
}

VOID COBProcessorWnd::AdjustToPrivileges()
{
	if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_OBPROCESSOR_CHANGE))
	{
		m_wndView.UnSelectAll();
		return;
	}
}

BEGIN_MESSAGE_MAP(COBProcessorWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(COBProcessorWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_OBPROCESSOR_STATUSBAR_DETAILSPANE, OnUpdateStatusBarDetailsPane)
	ON_UPDATE_COMMAND_UI(ID_OBPROCESSOR_STATUSBAR_FLAGPANE, OnUpdateStatusBarFlagPane)
	ON_UPDATE_COMMAND_UI(ID_OBPROCESSOR_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COBProcessorWnd message handlers

int COBProcessorWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayWnd::OnCreate(lpCreateStruct) != -1 && LoadAccelTable(IDR_OBPROCESSORFRAME)) ? 0 : -1);
}

BOOL COBProcessorWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	CRect  rBar;

	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1))
	{
		m_wndStatusBar.GetWindowRect(rBar);
		return m_wndView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
	}
	return FALSE;
}

void COBProcessorWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rBar;

	m_wndStatusBar.GetWindowRect(rBar);
	m_wndView.MoveWindow(0, 0, cx, cy - rBar.Height());
	CDisplayWnd::OnSize(nType, cx, cy);
}

void COBProcessorWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	if (!bActivate) m_wndView.UnSelectAll();
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void COBProcessorWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN) m_wndView.ActivateTable();
	CDisplayWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void COBProcessorWnd::OnClose()
{
	CHourglassCursor  cCursor;

	DoClose();
	CDisplayWnd::OnClose();
}

void COBProcessorWnd::OnUpdateStatusBarDetailsPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void COBProcessorWnd::OnUpdateStatusBarFlagPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void COBProcessorWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
