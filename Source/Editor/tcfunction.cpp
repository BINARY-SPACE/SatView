// TCFUNCTION.CPP : Telecommand Function Form Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telecommand
// function form related interface.
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
	ID_TCFUNCTION_STATUSBAR_DETAILSPANE,
	ID_TCFUNCTION_STATUSBAR_FLAGPANE,
	ID_TCFUNCTION_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CTCFunctionOpenDialog dialog

IMPLEMENT_DYNCREATE(CTCFunctionOpenDialog, CLocaleDialog)

CTCFunctionOpenDialog::CTCFunctionOpenDialog(CWnd *pParentWnd) : CLocaleDialog(CTCFunctionOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCFunctionOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCFunctionOpenDialog::Initialize()
{
	m_pDatabaseTCFunctions.Copy(GetDatabase()->GetTCFunctions());
	return TRUE;
}

VOID CTCFunctionOpenDialog::EnumTCFunctions()
{
	INT  nColumn;
	INT  nColumns;
	INT  nFunction;
	INT  nFunctions;
	CString  szItem;
	CDatabaseTCFunction  *pDatabaseTCFunction;

	for (nFunction = 0, nFunctions = (INT)m_pDatabaseTCFunctions.GetSize(); nFunction < nFunctions; nFunction++)
	{
		if ((pDatabaseTCFunction = m_pDatabaseTCFunctions.GetAt(nFunction)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCFUNCTIONOPENDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pDatabaseTCFunction->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCFUNCTIONOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCFunction->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY), nFunction, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY), nFunction, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY), 0);
	GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CTCFunctionOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void CTCFunctionOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCFunctionOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCFunctionOpenDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTCFunctions.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCFunctionOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCFunctionOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCFUNCTION_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCFunctionOpenDialog message handlers

BOOL CTCFunctionOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCFUNCTIONOPENDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCFUNCTIONOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TCFUNCTION_OPEN_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (2 * rColumns.Width()) / 9; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumTCFunctions();
	GetDlgItem(IDC_TCFUNCTION_OPEN_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_TCFUNCTION_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_OPEN_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_OPEN_DATABASE)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY)->SetFocus();
	return FALSE;
}

BOOL CTCFunctionOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCFUNCTION_OPEN_DIRECTORY)
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

void CTCFunctionOpenDialog::OnOK()
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
	CTCFunctionWnd  *pTCFunctionWnd;
	CHourglassCursor  cCursor;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCFUNCTIONOPENDIALOG_DIRECTORYTITLEITEM_NAME))
		{
			szTag = Listview_GetText(GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY)), nColumn);
			continue;
		}
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCFUNCTIONOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
		{
			szDescription = Listview_GetText(GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_TCFUNCTION_OPEN_DIRECTORY)), nColumn);
			continue;
		}
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCFUNCTION)
		{
			if ((pTCFunctionWnd = (CTCFunctionWnd *)pDisplayWnd)->GetName() == szTag)
			{
				pTCFunctionWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		if ((pTCFunctionWnd = new CTCFunctionWnd(szTag)))
		{
			if (pTCFunctionWnd->Create(GetMainWnd()))
			{
				EndDialog(IDOK);
				return;
			}
		}
		szMessage.Format(STRING(IDS_TCFUNCTION_FAILURE_LOAD), (LPCTSTR)szDescription);
		ShowMessage(szMessage);
	}
	EndDialog(IDOK);
}

void CTCFunctionOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCFunctionOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCFUNCTIONOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCFunctionOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCFUNCTIONOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCFunctionImportDialog dialog

IMPLEMENT_DYNCREATE(CTCFunctionImportDialog, CLocaleDialog)

CTCFunctionImportDialog::CTCFunctionImportDialog(CWnd *pParentWnd) : CLocaleDialog(CTCFunctionImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCFunctionImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CTCFunctionImportDialog::DoModal(CDatabaseTCFunctions &pDatabaseTCFunctions)
{
	INT_PTR  nResult;

	for (m_pDatabaseTCFunctions.RemoveAll(); (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCFunctions.Copy(&m_pDatabaseTCFunctions);
		break;
	}
	return nResult;
}

VOID CTCFunctionImportDialog::EnumTCFunctions()
{
	INT  nColumn;
	INT  nColumns;
	INT  nFunction;
	INT  nFunctions;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szItem;
	CString  szFileName;
	CByteArray  cFileBuffer;
	CFileFindEx  cFileFind;
	CDatabaseTCFunction  *pDatabaseTCFunction;

	SendDlgItemMessage(IDC_TCFUNCTION_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCFUNCTION_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				for (nFunction = 0, nFunctions = (m_pDatabaseTCFunctions.Unmap(cFileBuffer, FALSE)) ? (INT)m_pDatabaseTCFunctions.GetSize() : 0; nFunction < nFunctions; nFunction++)
				{
					if ((pDatabaseTCFunction = m_pDatabaseTCFunctions.GetAt(nFunction)))
					{
						for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCFUNCTIONIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
							{
								szItem = pDatabaseTCFunction->GetName();
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCFUNCTIONIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
							{
								szItem = pDatabaseTCFunction->GetDescription();
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_TCFUNCTION_IMPORT_DIRECTORY), nFunction, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_TCFUNCTION_IMPORT_DIRECTORY), nFunction, nColumn, szItem);
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
	GetDlgItem(IDC_TCFUNCTION_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCFunctionImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TCFUNCTION_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCFUNCTION_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_TCFUNCTION_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CTCFunctionImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCFunctionImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCFunctionImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCFunctionImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCFunctionImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCFUNCTION_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_TCFUNCTION_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_TCFUNCTION_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TCFUNCTION_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCFunctionImportDialog message handlers

BOOL CTCFunctionImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_TCFUNCTIONIMPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCFUNCTIONIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TCFUNCTION_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME, EM_LIMITTEXT, GetDatabase()->GetTCFunctionNameLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCFUNCTION_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_TCFUNCTION_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_TCFUNCTION_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CTCFunctionImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCFUNCTION_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_TCFUNCTION_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM)->EnableWindow();
			}
			else
			{
				CheckDlgButton(IDC_TCFUNCTION_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CTCFunctionImportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TCFUNCTION_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_TCFUNCTION_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumTCFunctions();
	}
	SendDlgItemMessage(IDC_TCFUNCTION_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TCFUNCTION_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionImportDialog::OnDefault()
{
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionImportDialog::OnCustom()
{
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionImportDialog::OnEditchangeFileName()
{
	EnumTCFunctions();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionImportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionImportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionImportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nFunction;
	INT  nFunctions;
	CString  szName;
	CString  szDescription;
	CPtrArray  pFunctions;
	CUIntArray  nFunctionIDs;
	CDatabaseTCFunction  *pDatabaseTCFunction[2];
	CDatabaseTCFunctions  pDatabaseTCFunctions;
	CHourglassCursor  cCursor;

	for (nFunction = 0, nFunctions = (INT)SendDlgItemMessage(IDC_TCFUNCTION_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nFunction < nFunctions; nFunction++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_TCFUNCTION_IMPORT_DIRECTORY), nFunction))
		{
			delete m_pDatabaseTCFunctions.GetAt(nFunction);
			m_pDatabaseTCFunctions.SetAt(nFunction, NULL);
		}
	}
	for (nFunction = 0, nFunctions = (pDatabaseTCFunctions.Copy(GetDatabase()->GetTCFunctions())) ? nFunctions : -1; nFunction < nFunctions; nFunction++)
	{
		if ((pDatabaseTCFunction[0] = m_pDatabaseTCFunctions.GetAt(nFunction)))
		{
			if (IsDlgButtonChecked(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM))
			{
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
				GetDlgItem(IDC_TCFUNCTION_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
				pDatabaseTCFunction[0]->SetDescription(szDescription);
				pDatabaseTCFunction[0]->SetName(szName);
			}
			if ((pDatabaseTCFunction[1] = pDatabaseTCFunctions.GetAt((nIndex = pDatabaseTCFunctions.Find(pDatabaseTCFunction[0]->GetName())))))
			{
				pDatabaseTCFunction[1]->Copy(pDatabaseTCFunction[0]);
				pFunctions.Add(pDatabaseTCFunction[1]);
				nFunctionIDs.Add(nIndex);
				continue;
			}
			if ((pDatabaseTCFunction[1] = new CDatabaseTCFunction))
			{
				pDatabaseTCFunction[1]->Copy(pDatabaseTCFunction[0]);
				if ((nIndex = pDatabaseTCFunctions.Add(pDatabaseTCFunction[1])) >= 0)
				{
					pFunctions.Add(pDatabaseTCFunction[1]);
					nFunctionIDs.Add(-(nIndex + 1));
					continue;
				}
				delete pDatabaseTCFunction[1];
			}
			break;
		}
		m_pDatabaseTCFunctions.RemoveAt(nFunction);
		nFunctions--;
		nFunction--;
	}
	for (; nFunction == nFunctions; )
	{
		if (GetDatabase()->GetTCFunctions()->Copy(&pDatabaseTCFunctions))
		{
			for (nItem = 0, nItems = (INT)pFunctions.GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTCFunction[0] = (CDatabaseTCFunction *)pFunctions.GetAt(nItem)))
				{
					if (GetDatabase()->Save(pDatabaseTCFunction[0]))
					{
						nIndex = (INT)nFunctionIDs.GetAt(nItem);
						UpdateDatabase(pDatabaseTCFunction[0], nIndex);
						continue;
					}
				}
				break;
			}
			if (nItem == nItems) break;
		}
		nFunctions = -1;
		break;
	}
	for (; nFunction != nFunctions; )
	{
		ShowMessage((SendDlgItemMessage(IDC_TCFUNCTION_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_TCFUNCTIONDIRECTORY_IMPORT_FAILURE : SYSTEM_WARNING_TCFUNCTION_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CTCFunctionImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCFunctionImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCFUNCTIONIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCFunctionImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCFUNCTIONIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCFunctionExportDialog dialog

IMPLEMENT_DYNCREATE(CTCFunctionExportDialog, CLocaleDialog)

CTCFunctionExportDialog::CTCFunctionExportDialog(CWnd *pParentWnd) : CLocaleDialog(CTCFunctionExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCFunctionExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CTCFunctionExportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

BOOL CTCFunctionExportDialog::EnumTCFunctions()
{
	INT  nColumn;
	INT  nColumns;
	INT  nFunction;
	INT  nFunctions;
	CString  szItem;
	CDatabaseTCFunction  *pDatabaseTCFunction;

	for (nFunction = 0, nFunctions = (m_pDatabaseTCFunctions.Copy(GetDatabase()->GetTCFunctions())) ? (INT)m_pDatabaseTCFunctions.GetSize() : 0; nFunction < nFunctions; nFunction++)
	{
		if ((pDatabaseTCFunction = m_pDatabaseTCFunctions.GetAt(nFunction)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCFUNCTIONEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
				{
					szItem = pDatabaseTCFunction->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCFUNCTIONEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCFunction->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCFUNCTION_EXPORT_DIRECTORY), nFunction, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCFUNCTION_EXPORT_DIRECTORY), nFunction, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_TCFUNCTION_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCFUNCTION_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCFUNCTION_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCFunctionExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TCFUNCTION_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCFUNCTION_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_TCFUNCTION_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CTCFunctionExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCFunctionExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCFunctionExportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTCFunctions.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCFunctionExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCFunctionExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCFUNCTION_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_TCFUNCTION_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_TCFUNCTION_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TCFUNCTION_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCFunctionExportDialog message handlers

BOOL CTCFunctionExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TCFUNCTION_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_TCFUNCTIONEXPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TCFUNCTIONEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TCFUNCTION_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME, EM_LIMITTEXT, GetDatabase()->GetTCFunctionNameLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCFUNCTION_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumTCFunctions())
	{
		CheckDlgButton(IDC_TCFUNCTION_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_TCFUNCTION_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TCFUNCTION_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCFUNCTION_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_TCFUNCTION_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM)->EnableWindow();
		GetDlgItem(IDC_TCFUNCTION_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL CTCFunctionExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCFUNCTION_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_TCFUNCTION_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM)->EnableWindow();
				CheckDlgButton(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM, FALSE);
			}
			else
			{
				CheckDlgButton(IDC_TCFUNCTION_EXPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CTCFunctionExportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TCFUNCTION_EXPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_TCFUNCTION_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_TCFUNCTION_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TCFUNCTION_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionExportDialog::OnDefault()
{
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionExportDialog::OnCustom()
{
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionExportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionExportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionExportDialog::OnOK()
{
	INT  nFunction;
	INT  nFunctions;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szName;
	CString  szFileName;
	CString  szDescription;
	CByteArray  cFileBuffer;
	CDatabaseTCFunction  *pDatabaseTCFunction;
	CHourglassCursor  cCursor;

	for (nFunction = 0, nFunctions = (INT)SendDlgItemMessage(IDC_TCFUNCTION_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nFunction < nFunctions; nFunction++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_TCFUNCTION_EXPORT_DIRECTORY), nFunction))
		{
			delete m_pDatabaseTCFunctions.GetAt(nFunction);
			m_pDatabaseTCFunctions.SetAt(nFunction, NULL);
		}
	}
	for (nFunction = 0; nFunction < nFunctions; nFunction++)
	{
		if (!m_pDatabaseTCFunctions.GetAt(nFunction))
		{
			m_pDatabaseTCFunctions.RemoveAt(nFunction);
			nFunctions--;
			nFunction--;
		}
	}
	if ((pDatabaseTCFunction = (IsDlgButtonChecked(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCFunctions.GetAt(nFunction) : (CDatabaseTCFunction *)NULL))
	{
		GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
		GetDlgItem(IDC_TCFUNCTION_EXPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
		pDatabaseTCFunction->SetDescription(szDescription);
		pDatabaseTCFunction->SetName(szName);
	}
	for (; nFunction == nFunctions; )
	{
		if (m_pDatabaseTCFunctions.Map(cFileBuffer, FALSE))
		{
			GetDlgItem(IDC_TCFUNCTION_EXPORT_FILENAME)->GetWindowText(szFileName);
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
		nFunctions = -1;
		break;
	}
	for (; nFunction != nFunctions; )
	{
		ShowMessage((SendDlgItemMessage(IDC_TCFUNCTION_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_TCFUNCTIONDIRECTORY_EXPORT_FAILURE : SYSTEM_WARNING_TCFUNCTION_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CTCFunctionExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCFunctionExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCFUNCTIONEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCFunctionExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCFUNCTIONEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCFunctionPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CTCFunctionPropertiesDialog, CLocaleDialog)

CTCFunctionPropertiesDialog::CTCFunctionPropertiesDialog(CWnd *pParentWnd) : CLocaleDialog(CTCFunctionPropertiesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCFunctionPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCFunctionPropertiesDialog::Initialize()
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

INT_PTR CTCFunctionPropertiesDialog::DoModal(CTCFunctionWnd *pParentWnd)
{
	INT_PTR  nResult;

	for (m_pParentWnd = (CWnd *)pParentWnd; (nResult = CLocaleDialog::DoModal()); ) break;
	return nResult;
}

VOID CTCFunctionPropertiesDialog::ShowFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_RESETCONTENT); (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE) && cFontTools.EnumerateFont(m_lfTable[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_ITEMS) && cFontTools.EnumerateFont(m_lfTable[0][1].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE))
	{
		SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][0])), 0));
		SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][0])), max(SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][0])), 0)));
		SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_ITEMS))
	{
		SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][1])), 0));
		SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][1])), max(SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][1])), 0)));
		SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]);
	}
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCFunctionPropertiesDialog::ShowFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

CTCFunctionWnd *CTCFunctionPropertiesDialog::GetParent() CONST
{
	return((CTCFunctionWnd *)CLocaleDialog::GetParent());
}

BOOL CTCFunctionPropertiesDialog::IsModified() CONST
{
	CFontTools  cFontTools;

	return((lstrcmp(m_lfTable[0][0].lfFaceName, m_lfTable[1][0].lfFaceName) || (m_lfTable[0][0].lfHeight != m_lfTable[1][0].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][0]))) || m_lfTable[0][0].lfWeight != m_lfTable[1][0].lfWeight || m_lfTable[0][0].lfItalic != m_lfTable[1][0].lfItalic || lstrcmp(m_lfTable[0][1].lfFaceName, m_lfTable[1][1].lfFaceName) || (m_lfTable[0][1].lfHeight != m_lfTable[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][1])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][1]))) || m_lfTable[0][1].lfWeight != m_lfTable[1][1].lfWeight || m_lfTable[0][1].lfItalic != m_lfTable[1][1].lfItalic || GetDlgItem(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]) != GetDlgItem(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][0]) || GetDlgItem(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]) != GetDlgItem(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][1]) || GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]) != GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][0]) || GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]) != GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][1])) ? TRUE : FALSE);
}

BOOL CTCFunctionPropertiesDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void CTCFunctionPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCFunctionPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCFunctionPropertiesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCFunctionPropertiesDialog)
	ON_WM_PAINT()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_TCFUNCTION_PROPERTIES_FONTS_ITEMS, OnItemsFont)
	ON_BN_CLICKED(IDC_TCFUNCTION_PROPERTIES_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR, OnSelchangeFontColor)
	ON_CBN_SELCHANGE(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE, OnSelchangeTitleBackgroundColor)
	ON_CBN_SELCHANGE(IDC_TCFUNCTION_PROPERTIES_COLORS_KEYS, OnSelchangeKeysBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCFunctionPropertiesDialog message handlers

BOOL CTCFunctionPropertiesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	CheckDlgButton(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE, TRUE);
	CheckDlgButton(IDC_TCFUNCTION_PROPERTIES_FONTS_ITEMS, FALSE);
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_COLORS_KEYS, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_COLORS_KEYS, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]);
	SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_COLORS_KEYS, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]);
	AccessControl(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE));
	AccessControl(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE));
	AccessControl(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE));
	AccessControl(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE));
	AccessControl(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE));
	AccessControl(IDC_TCFUNCTION_PROPERTIES_COLORS_KEYS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE));
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_ITEMS)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_COLORS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_COLORS_KEYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCFUNCTION_PROPERTIES_COLORS_KEYS)->EnableWindow();
	ShowFontDetails();
	return TRUE;
}

void CTCFunctionPropertiesDialog::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE)) ? &m_lfTable[0][0] : &m_lfTable[0][1]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE)) ? m_nTableFontColors[0][0] : m_nTableFontColors[0][1]) : GetSysColor(COLOR_GRAYTEXT));
			cDC.FillSolidRect(rSampleText, (SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE)) ? m_nTableColors[0][0] : GetSysColor(COLOR_3DFACE)) : GetSysColor(COLOR_3DFACE));
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

void CTCFunctionPropertiesDialog::OnTitleFont()
{
	SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CTCFunctionPropertiesDialog::OnItemsFont()
{
	SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][1].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CTCFunctionPropertiesDialog::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionPropertiesDialog::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE))
	{
		lstrcpy(m_lfTable[0][0].lfFaceName, Combobox_GetText(GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_ITEMS))
	{
		lstrcpy(m_lfTable[0][1].lfFaceName, Combobox_GetText(GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][1]);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionPropertiesDialog::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionPropertiesDialog::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TCFUNCTION_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionPropertiesDialog::OnSelchangeFontColor()
{
	for (; IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_TITLE); )
	{
		m_nTableFontColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	for (; IsDlgButtonChecked(IDC_TCFUNCTION_PROPERTIES_FONTS_ITEMS); )
	{
		m_nTableFontColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionPropertiesDialog::OnSelchangeTitleBackgroundColor()
{
	for (m_nTableColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_COLORS_TITLE, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionPropertiesDialog::OnSelchangeKeysBackgroundColor()
{
	for (m_nTableColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_COLORS_KEYS, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCFUNCTION_PROPERTIES_COLORS_KEYS, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCFunctionPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParent()->SetProperties(&m_lfTable[0][0], &m_lfTable[0][1], m_nTableFontColors[0][0], m_nTableFontColors[0][1], m_nTableColors[0][0], m_nTableColors[0][1]);
	EndDialog(IDOK);
}

void CTCFunctionPropertiesDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCFunctionPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCFUNCTIONPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCFunctionPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCFUNCTIONPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCFunctionStatusBar

IMPLEMENT_DYNCREATE(CTCFunctionStatusBar, CMFCStatusBar)

BOOL CTCFunctionStatusBar::SetIndicators(CONST UINT *pIDs, INT nCount)
{
	INT  nIndex;
	CString  szText;

	for (Initialize(); CMFCStatusBar::SetIndicators(pIDs, nCount); )
	{
		if ((nIndex = CommandToIndex(ID_TCFUNCTION_STATUSBAR_DETAILSPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TCFUNCTION_STATUSBAR_DETAILS), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TCFUNCTION_STATUSBAR_DETAILSPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(nIndex, szText));
		}
		if ((nIndex = CommandToIndex(ID_TCFUNCTION_STATUSBAR_FLAGPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TCFUNCTION_STATUSBAR_FLAG), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TCFUNCTION_STATUSBAR_FLAGPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_TCFUNCTION_STATUSBAR_FLAGPANE));
		}
		if ((nIndex = CommandToIndex(ID_TCFUNCTION_STATUSBAR_TYPEPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TCFUNCTION_STATUSBAR_TYPE), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TCFUNCTION_STATUSBAR_TYPEPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_TCFUNCTION_STATUSBAR_TYPEPANE));
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCFunctionStatusBar::SetPaneText(UINT nID, LPCTSTR pszText)
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

BOOL CTCFunctionStatusBar::GetPaneText(UINT nID, CString &szText) CONST
{
	INT  nIndex;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		szText = CMFCStatusBar::GetPaneText(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString CTCFunctionStatusBar::GetPaneText(UINT nID) CONST
{
	CString  szText;

	return((GetPaneText(nID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

INT CTCFunctionStatusBar::CalcPaneWidth(INT nIndex) CONST
{
	return CalcPaneWidth(nIndex, CMFCStatusBar::GetPaneText(nIndex));
}
INT CTCFunctionStatusBar::CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST
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

VOID CTCFunctionStatusBar::Initialize()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = GetCount(); nIndex < nCount; nIndex++)
	{
		SetTipText(nIndex, (LPCTSTR)NULL);
		continue;
	}
}

BEGIN_MESSAGE_MAP(CTCFunctionStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CTCFunctionStatusBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCFunctionStatusBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCFunctionView

IMPLEMENT_DYNCREATE(CTCFunctionView, CDisplayTableView)

CTCFunctionView::CTCFunctionView() : CDisplayTableView(DATABASE_COMPONENT_TCFUNCTION, IDR_TCFUNCTIONFRAMEMENU)
{
	return;
}

VOID CTCFunctionView::SetTitle(LPCTSTR pszName, LPCTSTR pszTitle)
{
	CDatabaseTCFunction  *pDatabaseTCFunction;

	if ((pDatabaseTCFunction = m_pDatabaseTCFunctions[0].GetAt(m_pDatabaseTCFunctions[0].Find(pszName))))
	{
		for (pDatabaseTCFunction->SetDescription(pszTitle); !m_szName.Compare(pszName); )
		{
			UpdateTables();
			break;
		}
	}
	m_szName = pszName;
	m_szTitle = pszTitle;
}

BOOL CTCFunctionView::GetTitle(CString &szName, CString &szTitle) CONST
{
	CDatabaseTCFunction  *pDatabaseTCFunction;

	for (szName.Empty(), szTitle.Empty(); (pDatabaseTCFunction = m_pDatabaseTCFunctions[0].GetAt(m_pDatabaseTCFunctions[0].Find(GetName()))); )
	{
		szTitle = pDatabaseTCFunction->GetDescription();
		szName = pDatabaseTCFunction->GetName();
		return TRUE;
	}
	szName = m_szName;
	szTitle = m_szTitle;
	return !szName.IsEmpty();
}

BOOL CTCFunctionView::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	for (SetTablesFonts(plfTitle, plfItems), SetTablesFontColors(nTitleColor, nItemsColor), SetTablesColors(nTitleBackground, nKeysBackground); IsWindow(GetSafeHwnd()); )
	{
		RepositionTables();
		break;
	}
	return TRUE;
}

BOOL CTCFunctionView::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	GetTablesFonts(plfTitle, plfItems);
	GetTablesFontColors(nTitleColor, nItemsColor);
	GetTablesColors(nTitleBackground, nKeysBackground);
	return TRUE;
}

VOID CTCFunctionView::UpdateTableForms(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nIndex, BOOL bDelete)
{
	UpdateDatabase(pDatabaseTCFunction, (nIndex > 0) ? (nIndex - 1) : nIndex, bDelete);
	UpdateForms(GetParent(), pDatabaseTCFunction, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCFunctionView::UpdateTableForms(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCPacket, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET);
}
VOID CTCFunctionView::UpdateTableForms(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCPacketParameter, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER);
}
VOID CTCFunctionView::UpdateTableForms(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCPreExeGroup, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP);
}
VOID CTCFunctionView::UpdateTableForms(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCExeVerStage, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE);
}
VOID CTCFunctionView::UpdateTableForms(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCExeVerGroup, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP);
}
VOID CTCFunctionView::UpdateTableForms(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCParameterSet, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET);
}
VOID CTCFunctionView::UpdateTableForms(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCParameterValueSet, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET);
}
VOID CTCFunctionView::UpdateTableForms(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCFunctionRoutingPath, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH);
}

CTCFunctionWnd *CTCFunctionView::GetParent() CONST
{
	return((CTCFunctionWnd *)CDisplayTableView::GetParent());
}

BOOL CTCFunctionView::CheckPrivilege() CONST
{
	return CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE);
}

BEGIN_MESSAGE_MAP(CTCFunctionView, CDisplayTableView)
	//{{AFX_MSG_MAP(CTCFunctionView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCFunctionView message handlers

int CTCFunctionView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayTableView::OnCreate(lpCreateStruct) != -1 && GetDatabase()->CreateTables(this, GetComponent())) ? 0 : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTCFunctionWnd

IMPLEMENT_DYNCREATE(CTCFunctionWnd, CDisplayWnd)

CTCFunctionWnd::CTCFunctionWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TCFUNCTION);
}
CTCFunctionWnd::CTCFunctionWnd(LPCTSTR pszName) : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TCFUNCTION);
	SetName(pszName);
}

BOOL CTCFunctionWnd::Create(CMDIFrameWnd *pParentWnd, UINT nShow)
{
	return Create(pParentWnd, GetName(), nShow);
}
BOOL CTCFunctionWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszName, UINT nShow)
{
	CRect  rPosition;

	for (SetName(pszName), rPosition = m_rPosition; CDisplayWnd::Create(pParentWnd, STRING(IDS_DISPLAY_TITLE_TCFUNCTION), (nShow == (UINT)-1) ? CRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) : CRect(0, 0, 0, 0), IDR_TCFUNCTIONFRAME, (nShow != SW_SHOWMINIMIZED || nShow != SW_SHOWMAXIMIZED) ? (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE) : (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW)); )
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

VOID CTCFunctionWnd::SetName(LPCTSTR pszName)
{
	m_wndView.SetName(pszName);
}

CString CTCFunctionWnd::GetName() CONST
{
	return m_wndView.GetName();
}

VOID CTCFunctionWnd::SetTitle(LPCTSTR pszTitle)
{
	m_wndView.SetTitle(GetName(), pszTitle);
}

CString CTCFunctionWnd::GetTitle() CONST
{
	CString  szName;
	CString  szTitle;

	return((m_wndView.GetTitle(szName, szTitle)) ? szTitle : STRING(IDS_DISPLAY_TITLE_TCFUNCTION));
}

BOOL CTCFunctionWnd::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	return m_wndView.SetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CTCFunctionWnd::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	return m_wndView.GetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CTCFunctionWnd::IsModified() CONST
{
	return((m_wndView.Check()) ? m_wndView.IsModified() : FALSE);
}

BOOL CTCFunctionWnd::Save(INT nPosition) CONST
{
	UINT  nShowFlags;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	cProfile.DeleteDisplayWindowInfo(nPosition);
	return((GetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && cProfile.SetDisplayWindowType(nPosition, GetType()) && cProfile.SetDisplayWindowName(nPosition, GetName()) && cProfile.SetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, (nShowFlags = (!IsIconic()) ? ((!IsZoomed()) ? SW_SHOWNORMAL : SW_SHOWMAXIMIZED) : SW_SHOWMINIMIZED)) && cProfile.SetTCFunctionsFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? TRUE : FALSE);
}

INT CTCFunctionWnd::Load(INT nPosition)
{
	UINT  nShowFlags;
	CString  szName;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	return((cProfile.GetDisplayWindowName(nPosition, szName) && cProfile.GetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, nShowFlags) && cProfile.GetTCFunctionsFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && SetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? CTCFunctionWnd::Create(GetMainWnd(), szName, nShowFlags) : -1);
}

BOOL CTCFunctionWnd::UpdateProperties()
{
	return((m_dlgProperties.DoModal(this) == IDOK) ? TRUE : FALSE);
}

BOOL CTCFunctionWnd::IsUpdatingProperties() CONST
{
	return IsWindow(m_dlgProperties.GetSafeHwnd());
}

BOOL CTCFunctionWnd::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCFunctionWnd::CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST
{
	return m_wndView.CheckTableDropTarget(pszTable, nComponent, point);
}

BOOL CTCFunctionWnd::DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point)
{
	return m_wndView.DropOnTableTarget(pszTable, nComponent, point);
}

VOID CTCFunctionWnd::UpdateAllPanes(LPCTSTR pszDetails, LPCTSTR pszFlag, LPCTSTR pszType)
{
	m_wndStatusBar.SetPaneText(ID_TCFUNCTION_STATUSBAR_DETAILSPANE, pszDetails);
	m_wndStatusBar.SetPaneText(ID_TCFUNCTION_STATUSBAR_FLAGPANE, pszFlag);
	m_wndStatusBar.SetPaneText(ID_TCFUNCTION_STATUSBAR_TYPEPANE, pszType);
}

BOOL CTCFunctionWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
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
				if (PrintJob(cDC, &m_wndView, STRING(IDS_DISPLAY_TITLE_TCFUNCTION), cPrintProfileInfo.GetPrinterName(), rtMargin[0], bMetrics, nFlags))
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
					if (PrintJob(cDC, &m_wndView, STRING(IDS_DISPLAY_TITLE_TCFUNCTION), (LPCTSTR)pDevMode->dmDeviceName, rtMargin[0], bMetrics, nFlags, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : -1, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : -1))
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

VOID CTCFunctionWnd::DoSave()
{
	if (m_wndView.DoSave())
	{
		GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_TCFUNCTION);
		return;
	}
}

BOOL CTCFunctionWnd::CanSave() CONST
{
	return((m_wndView.CanSave()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

VOID CTCFunctionWnd::DoCheck()
{
	m_wndView.DoCheck();
}

BOOL CTCFunctionWnd::CanCheck() CONST
{
	return((m_wndView.CanCheck()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

VOID CTCFunctionWnd::DoDelete()
{
	CString  szName;
	CString  szTitle;

	for (szName = GetName(), szTitle = GetTitle(); m_wndView.DoDelete(); )
	{
		GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_TCFUNCTION);
		break;
	}
}

BOOL CTCFunctionWnd::CanDelete() CONST
{
	return((m_wndView.CanDelete()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

VOID CTCFunctionWnd::DoUndo()
{
	m_wndView.DoUndo();
}

BOOL CTCFunctionWnd::CanUndo() CONST
{
	return m_wndView.CanUndo();
}

VOID CTCFunctionWnd::DoRedo()
{
	m_wndView.DoRedo();
}

BOOL CTCFunctionWnd::CanRedo() CONST
{
	return m_wndView.CanRedo();
}

VOID CTCFunctionWnd::DoSelectAll()
{
	m_wndView.DoSelectAll();
}

BOOL CTCFunctionWnd::CanSelectAll() CONST
{
	return m_wndView.CanSelectAll();
}

VOID CTCFunctionWnd::DoCutSel()
{
	m_wndView.DoCutSel();
}

BOOL CTCFunctionWnd::CanCutSel() CONST
{
	return m_wndView.CanCutSel();
}

VOID CTCFunctionWnd::DoCopySel()
{
	m_wndView.DoCopySel();
}

BOOL CTCFunctionWnd::CanCopySel() CONST
{
	return m_wndView.CanCopySel();
}

VOID CTCFunctionWnd::DoPasteSel()
{
	m_wndView.DoPasteSel();
}

BOOL CTCFunctionWnd::CanPasteSel() CONST
{
	return m_wndView.CanPasteSel();
}

VOID CTCFunctionWnd::DoDeleteSel()
{
	m_wndView.DoDeleteSel();
}

BOOL CTCFunctionWnd::CanDeleteSel() CONST
{
	return m_wndView.CanDeleteSel();
}

BOOL CTCFunctionWnd::CanPrint(UINT nFlags) CONST
{
	return m_wndView.CanPrint(nFlags);
}

VOID CTCFunctionWnd::DoClose()
{
	m_wndView.DoClose();
}

BOOL CTCFunctionWnd::DoSaveTable()
{
	return m_wndView.DoSaveTable();
}

BOOL CTCFunctionWnd::CanSaveTable() CONST
{
	return((m_wndView.CanSaveTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoCheckTable()
{
	return m_wndView.DoCheckTable();
}

BOOL CTCFunctionWnd::CanCheckTable() CONST
{
	return((m_wndView.CanCheckTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoDeleteTable()
{
	return m_wndView.DoDeleteTable();
}

BOOL CTCFunctionWnd::CanDeleteTable() CONST
{
	return((m_wndView.CanDeleteTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoPrintTable()
{
	return Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE);
}

BOOL CTCFunctionWnd::CanPrintTable() CONST
{
	return CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE);
}

BOOL CTCFunctionWnd::DoPrintAllTables()
{
	return Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL);
}

BOOL CTCFunctionWnd::CanPrintAllTables() CONST
{
	return CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL);
}

BOOL CTCFunctionWnd::DoImportTables()
{
	return m_wndView.DoImportTables();
}

BOOL CTCFunctionWnd::CanImportTables() CONST
{
	return((m_wndView.CanImportTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoExportTables()
{
	return m_wndView.DoExportTables();
}

BOOL CTCFunctionWnd::CanExportTables() CONST
{
	return m_wndView.CanExportTables();
}

BOOL CTCFunctionWnd::DoDiscardTables()
{
	return m_wndView.DoDiscardTables();
}

BOOL CTCFunctionWnd::CanDiscardTables() CONST
{
	return((m_wndView.CanDiscardTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoDiscardAllTables()
{
	return m_wndView.DoDiscardAllTables();
}

BOOL CTCFunctionWnd::CanDiscardAllTables() CONST
{
	return((m_wndView.CanDiscardAllTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoResetTables()
{
	return m_wndView.DoResetTables();
}

BOOL CTCFunctionWnd::CanResetTables() CONST
{
	return((m_wndView.CanResetTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoInsertTableRowAbove()
{
	return m_wndView.DoInsertTableRowAbove();
}

BOOL CTCFunctionWnd::CanInsertTableRowAbove() CONST
{
	return((m_wndView.CanInsertTableRowAbove()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoInsertTableRowBelow()
{
	return m_wndView.DoInsertTableRowBelow();
}

BOOL CTCFunctionWnd::CanInsertTableRowBelow() CONST
{
	return((m_wndView.CanInsertTableRowBelow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoInsertTableColumnBefore()
{
	return m_wndView.DoInsertTableColumnBefore();
}

BOOL CTCFunctionWnd::CanInsertTableColumnBefore() CONST
{
	return((m_wndView.CanInsertTableColumnBefore()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoInsertTableColumnAfter()
{
	return m_wndView.DoInsertTableColumnAfter();
}

BOOL CTCFunctionWnd::CanInsertTableColumnAfter() CONST
{
	return((m_wndView.CanInsertTableColumnAfter()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoClearTableRow()
{
	return m_wndView.DoClearTableRow();
}

BOOL CTCFunctionWnd::CanClearTableRow() CONST
{
	return((m_wndView.CanClearTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoDeleteTableRow()
{
	return m_wndView.DoDeleteTableRow();
}

BOOL CTCFunctionWnd::CanDeleteTableRow() CONST
{
	return((m_wndView.CanDeleteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoDeleteTableColumn()
{
	return m_wndView.DoDeleteTableColumn();
}

BOOL CTCFunctionWnd::CanDeleteTableColumn() CONST
{
	return((m_wndView.CanDeleteTableColumn()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

BOOL CTCFunctionWnd::DoCopyTableRow()
{
	return m_wndView.DoCopyTableRow();
}

BOOL CTCFunctionWnd::CanCopyTableRow() CONST
{
	return m_wndView.CanCopyTableRow();
}

BOOL CTCFunctionWnd::DoPasteTableRow()
{
	return m_wndView.DoPasteTableRow();
}

BOOL CTCFunctionWnd::CanPasteTableRow() CONST
{
	return((m_wndView.CanPasteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE) : FALSE);
}

VOID CTCFunctionWnd::GotoTable(ULONGLONG nComponent, LPCTSTR pszName)
{
	m_wndView.GotoTable(nComponent, pszName);
}

VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCFunctions &pDatabaseTCFunctions)
{
	m_wndView.UpdateTables(pDatabaseTCFunctions);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE, pDatabaseTCFunction->GetName(), bDelete);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET, pDatabaseTCPacket->GetTag(), bDelete);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER, pDatabaseTCPacketParameter->GetTag(), bDelete);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP, pDatabaseTCPreExeGroup->GetID(), bDelete);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE, pDatabaseTCExeVerStage->GetID(), bDelete);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP, pDatabaseTCExeVerGroup->GetID(), bDelete);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, pDatabaseTCParameterSet->GetName(), bDelete);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET, pDatabaseTCParameterValueSet->GetName(), bDelete);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH, pDatabaseTCFunctionRoutingPath->GetAPID(), bDelete);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCFunctionWnd::UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCFunctionWnd::UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete)
{
	m_wndView.UpdateTables(nComponent, pszName, bDelete);
	m_wndView.ClearUndo();
}
VOID CTCFunctionWnd::UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete)
{
	m_wndView.UpdateTables(nComponent, nID, bDelete);
	m_wndView.ClearUndo();
}
VOID CTCFunctionWnd::UpdateTables(ULONGLONG nComponent)
{
	m_wndView.UpdateTables(nComponent);
}
VOID CTCFunctionWnd::UpdateTables()
{
	m_wndView.UpdateTables();
}

VOID CTCFunctionWnd::UpdateTitle()
{
	SetWindowText(STRING(IDS_DISPLAY_TITLE_TCFUNCTION));
}

VOID CTCFunctionWnd::UpdateMenus()
{
	GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
}

VOID CTCFunctionWnd::UpdateStatusBar()
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

CString CTCFunctionWnd::GetPrintDocTitle(LPCTSTR pszName, UINT nFlags) CONST
{
	CDatabaseTCFunction  *pDatabaseTCFunction;

	return(((pDatabaseTCFunction = (nFlags & DISPLAYTABLEVIEW_PRINT_TABLE) ? GetDatabase()->GetTCFunctions()->GetAt(GetDatabase()->GetTCFunctions()->Find(pszName)) : (CDatabaseTCFunction *)NULL) && !pDatabaseTCFunction->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseTCFunction->GetDescription() : pszName);
}

CString CTCFunctionWnd::GetPrintDocInfoTitle() CONST
{
	return STRING(IDS_DISPLAY_TITLE_TCFUNCTION);
}

VOID CTCFunctionWnd::AdjustToPrivileges()
{
	if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCFUNCTION_CHANGE))
	{
		m_wndView.UnSelectAll();
		return;
	}
}

BEGIN_MESSAGE_MAP(CTCFunctionWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CTCFunctionWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_TCFUNCTION_STATUSBAR_DETAILSPANE, OnUpdateStatusBarDetailsPane)
	ON_UPDATE_COMMAND_UI(ID_TCFUNCTION_STATUSBAR_FLAGPANE, OnUpdateStatusBarFlagPane)
	ON_UPDATE_COMMAND_UI(ID_TCFUNCTION_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCFunctionWnd message handlers

int CTCFunctionWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayWnd::OnCreate(lpCreateStruct) != -1 && LoadAccelTable(IDR_TCFUNCTIONFRAME)) ? 0 : -1);
}

BOOL CTCFunctionWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	CRect  rBar;

	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1))
	{
		m_wndStatusBar.GetWindowRect(rBar);
		return m_wndView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
	}
	return FALSE;
}

void CTCFunctionWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rBar;

	m_wndStatusBar.GetWindowRect(rBar);
	m_wndView.MoveWindow(0, 0, cx, cy - rBar.Height());
	CDisplayWnd::OnSize(nType, cx, cy);
}

void CTCFunctionWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	if (!bActivate) m_wndView.UnSelectAll();
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CTCFunctionWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN) m_wndView.ActivateTable();
	CDisplayWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTCFunctionWnd::OnClose()
{
	CHourglassCursor  cCursor;

	DoClose();
	CDisplayWnd::OnClose();
}

void CTCFunctionWnd::OnUpdateStatusBarDetailsPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCFunctionWnd::OnUpdateStatusBarFlagPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCFunctionWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
