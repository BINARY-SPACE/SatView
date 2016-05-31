// TMPARAMETER.CPP : Telemetry Parameter Form Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telemetry parameter
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
	ID_TMPARAMETER_STATUSBAR_DETAILSPANE,
	ID_TMPARAMETER_STATUSBAR_FLAGPANE,
	ID_TMPARAMETER_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CTMParameterOpenDialog dialog

IMPLEMENT_DYNCREATE(CTMParameterOpenDialog, CLocaleDialog)

CTMParameterOpenDialog::CTMParameterOpenDialog(CWnd *pParentWnd) : CLocaleDialog(CTMParameterOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTMParameterOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTMParameterOpenDialog::Initialize()
{
	m_pDatabaseTMParameters.Copy(GetDatabase()->GetTMParameters());
	return TRUE;
}

VOID CTMParameterOpenDialog::EnumTMParameters()
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	CString  szItem;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = (INT)m_pDatabaseTMParameters.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = m_pDatabaseTMParameters.GetAt(nParameter)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_TAG); )
				{
					szItem = pDatabaseTMParameter->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTMParameter->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY), nParameter, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY), nParameter, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY), 0);
	GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CTMParameterOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void CTMParameterOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTMParameterOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTMParameterOpenDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTMParameters.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTMParameterOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTMParameterOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TMPARAMETER_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMParameterOpenDialog message handlers

BOOL CTMParameterOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TMPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TMPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TMPARAMETER_OPEN_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (2 * rColumns.Width()) / 9; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumTMParameters();
	GetDlgItem(IDC_TMPARAMETER_OPEN_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_TMPARAMETER_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_OPEN_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_OPEN_DATABASE)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY)->SetFocus();
	return FALSE;
}

BOOL CTMParameterOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TMPARAMETER_OPEN_DIRECTORY)
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

void CTMParameterOpenDialog::OnOK()
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
	CTMParameterWnd  *pTMParameterWnd;
	CHourglassCursor  cCursor;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_TMPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_TAG))
		{
			szTag = Listview_GetText(GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY)), nColumn);
			continue;
		}
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_TMPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
		{
			szDescription = Listview_GetText(GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_TMPARAMETER_OPEN_DIRECTORY)), nColumn);
			continue;
		}
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPARAMETER)
		{
			if ((pTMParameterWnd = (CTMParameterWnd *)pDisplayWnd)->GetName() == szTag)
			{
				pTMParameterWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		if ((pTMParameterWnd = new CTMParameterWnd(szTag)))
		{
			if (pTMParameterWnd->Create(GetMainWnd()))
			{
				EndDialog(IDOK);
				return;
			}
		}
		szMessage.Format(STRING(IDS_TMPARAMETER_FAILURE_LOAD), (LPCTSTR)szDescription);
		ShowMessage(szMessage);
	}
	EndDialog(IDOK);
}

void CTMParameterOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTMParameterOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPARAMETEROPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTMParameterOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPARAMETEROPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTMParameterImportDialog dialog

IMPLEMENT_DYNCREATE(CTMParameterImportDialog, CLocaleDialog)

CTMParameterImportDialog::CTMParameterImportDialog(CWnd *pParentWnd) : CLocaleDialog(CTMParameterImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTMParameterImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CTMParameterImportDialog::DoModal(CDatabaseTMParameters &pDatabaseTMParameters)
{
	INT_PTR  nResult;

	for (m_pDatabaseTMParameters.RemoveAll(); (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMParameters.Copy(&m_pDatabaseTMParameters);
		break;
	}
	return nResult;
}

VOID CTMParameterImportDialog::EnumTMParameters()
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szItem;
	CString  szFileName;
	CByteArray  cFileBuffer;
	CFileFindEx  cFileFind;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	SendDlgItemMessage(IDC_TMPARAMETER_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TMPARAMETER_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				for (nParameter = 0, nParameters = (m_pDatabaseTMParameters.Unmap(cFileBuffer, FALSE)) ? (INT)m_pDatabaseTMParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
				{
					if ((pDatabaseTMParameter = m_pDatabaseTMParameters.GetAt(nParameter)))
					{
						for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPARAMETERIMPORTDIALOG_DIRECTORYTITLEITEM_TAG); )
							{
								szItem = pDatabaseTMParameter->GetTag();
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPARAMETERIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
							{
								szItem = pDatabaseTMParameter->GetDescription();
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_TMPARAMETER_IMPORT_DIRECTORY), nParameter, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_TMPARAMETER_IMPORT_DIRECTORY), nParameter, nColumn, szItem);
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
	GetDlgItem(IDC_TMPARAMETER_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTMParameterImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TMPARAMETER_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPARAMETER_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_TMPARAMETER_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CTMParameterImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTMParameterImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTMParameterImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTMParameterImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTMParameterImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TMPARAMETER_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_TMPARAMETER_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_TMPARAMETER_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TMPARAMETER_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG, OnEditchangeTag)
	ON_EN_CHANGE(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMParameterImportDialog message handlers

BOOL CTMParameterImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_TMPARAMETERIMPORTDIALOG_DIRECTORYTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TMPARAMETERIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TMPARAMETER_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG, EM_LIMITTEXT, GetDatabase()->GetTMParameterTagLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TMPARAMETER_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_TMPARAMETER_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_TMPARAMETER_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CTMParameterImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TMPARAMETER_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_TMPARAMETER_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM)->EnableWindow();
			}
			else
			{
				CheckDlgButton(IDC_TMPARAMETER_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CTMParameterImportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TMPARAMETER_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_TMPARAMETER_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumTMParameters();
	}
	SendDlgItemMessage(IDC_TMPARAMETER_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TMPARAMETER_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterImportDialog::OnDefault()
{
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterImportDialog::OnCustom()
{
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterImportDialog::OnEditchangeFileName()
{
	EnumTMParameters();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterImportDialog::OnEditchangeTag()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterImportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterImportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nParameter;
	INT  nParameters;
	CString  szTag;
	CString  szDescription;
	CPtrArray  pParameters;
	CUIntArray  nParameterIDs;
	CDatabaseTMParameter  *pDatabaseTMParameter[2];
	CDatabaseTMParameters  pDatabaseTMParameters;
	CHourglassCursor  cCursor;

	for (nParameter = 0, nParameters = (INT)SendDlgItemMessage(IDC_TMPARAMETER_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nParameter < nParameters; nParameter++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_TMPARAMETER_IMPORT_DIRECTORY), nParameter))
		{
			delete m_pDatabaseTMParameters.GetAt(nParameter);
			m_pDatabaseTMParameters.SetAt(nParameter, NULL);
		}
	}
	for (nParameter = 0, nParameters = (pDatabaseTMParameters.Copy(GetDatabase()->GetTMParameters())) ? nParameters : -1; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter[0] = m_pDatabaseTMParameters.GetAt(nParameter)))
		{
			if (IsDlgButtonChecked(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM))
			{
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->GetWindowText(szTag);
				GetDlgItem(IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
				pDatabaseTMParameter[0]->SetDescription(szDescription);
				pDatabaseTMParameter[0]->SetTag(szTag);
			}
			if ((pDatabaseTMParameter[1] = pDatabaseTMParameters.GetAt((nIndex = pDatabaseTMParameters.Find(pDatabaseTMParameter[0]->GetTag())))))
			{
				pDatabaseTMParameter[1]->Copy(pDatabaseTMParameter[0]);
				pParameters.Add(pDatabaseTMParameter[1]);
				nParameterIDs.Add(nIndex);
				continue;
			}
			if ((pDatabaseTMParameter[1] = new CDatabaseTMParameter))
			{
				pDatabaseTMParameter[1]->Copy(pDatabaseTMParameter[0]);
				if ((nIndex = pDatabaseTMParameters.Add(pDatabaseTMParameter[1])) >= 0)
				{
					pParameters.Add(pDatabaseTMParameter[1]);
					nParameterIDs.Add(-(nIndex + 1));
					continue;
				}
				delete pDatabaseTMParameter[1];
			}
			break;
		}
		m_pDatabaseTMParameters.RemoveAt(nParameter);
		nParameters--;
		nParameter--;
	}
	for (; nParameter == nParameters; )
	{
		if (GetDatabase()->GetTMParameters()->Copy(&pDatabaseTMParameters))
		{
			for (nItem = 0, nItems = (INT)pParameters.GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMParameter[0] = (CDatabaseTMParameter *)pParameters.GetAt(nItem)))
				{
					if (GetDatabase()->Save(pDatabaseTMParameter[0]))
					{
						nIndex = (INT)nParameterIDs.GetAt(nItem);
						UpdateDatabase(pDatabaseTMParameter[0], nIndex);
						continue;
					}
				}
				break;
			}
			if (nItem == nItems) break;
		}
		nParameters = -1;
		break;
	}
	for (; nParameter != nParameters; )
	{
		ShowMessage((SendDlgItemMessage(IDC_TMPARAMETER_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_TMPARAMETERDIRECTORY_IMPORT_FAILURE : SYSTEM_WARNING_TMPARAMETER_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CTMParameterImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTMParameterImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPARAMETERIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTMParameterImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPARAMETERIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTMParameterExportDialog dialog

IMPLEMENT_DYNCREATE(CTMParameterExportDialog, CLocaleDialog)

CTMParameterExportDialog::CTMParameterExportDialog(CWnd *pParentWnd) : CLocaleDialog(CTMParameterExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTMParameterExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CTMParameterExportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

BOOL CTMParameterExportDialog::EnumTMParameters()
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	CString  szItem;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = (m_pDatabaseTMParameters.Copy(GetDatabase()->GetTMParameters())) ? (INT)m_pDatabaseTMParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = m_pDatabaseTMParameters.GetAt(nParameter)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPARAMETEREXPORTDIALOG_DIRECTORYTITLEITEM_TAG); )
				{
					szItem = m_pDatabaseTMParameters.GetAt(nParameter)->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPARAMETEREXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = m_pDatabaseTMParameters.GetAt(nParameter)->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TMPARAMETER_EXPORT_DIRECTORY), nParameter, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TMPARAMETER_EXPORT_DIRECTORY), nParameter, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_TMPARAMETER_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPARAMETER_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TMPARAMETER_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTMParameterExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TMPARAMETER_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPARAMETER_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_TMPARAMETER_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CTMParameterExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTMParameterExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTMParameterExportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTMParameters.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTMParameterExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTMParameterExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TMPARAMETER_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_TMPARAMETER_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_TMPARAMETER_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TMPARAMETER_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG, OnEditchangeTag)
	ON_EN_CHANGE(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMParameterExportDialog message handlers

BOOL CTMParameterExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TMPARAMETER_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_TMPARAMETEREXPORTDIALOG_DIRECTORYTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TMPARAMETEREXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TMPARAMETER_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG, EM_LIMITTEXT, GetDatabase()->GetTMParameterTagLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TMPARAMETER_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumTMParameters())
	{
		CheckDlgButton(IDC_TMPARAMETER_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_TMPARAMETER_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TMPARAMETER_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_TMPARAMETER_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_TMPARAMETER_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM)->EnableWindow();
		GetDlgItem(IDC_TMPARAMETER_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL CTMParameterExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TMPARAMETER_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_TMPARAMETER_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM)->EnableWindow();
				CheckDlgButton(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM, FALSE);
			}
			else
			{
				CheckDlgButton(IDC_TMPARAMETER_EXPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CTMParameterExportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TMPARAMETER_EXPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_TMPARAMETER_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_TMPARAMETER_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TMPARAMETER_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterExportDialog::OnDefault()
{
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterExportDialog::OnCustom()
{
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterExportDialog::OnEditchangeTag()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterExportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterExportDialog::OnOK()
{
	INT  nParameter;
	INT  nParameters;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szTag;
	CString  szFileName;
	CString  szDescription;
	CByteArray  cFileBuffer;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CHourglassCursor  cCursor;

	for (nParameter = 0, nParameters = (INT)SendDlgItemMessage(IDC_TMPARAMETER_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nParameter < nParameters; nParameter++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_TMPARAMETER_EXPORT_DIRECTORY), nParameter))
		{
			delete m_pDatabaseTMParameters.GetAt(nParameter);
			m_pDatabaseTMParameters.SetAt(nParameter, NULL);
		}
	}
	for (nParameter = 0; nParameter < nParameters; nParameter++)
	{
		if (!m_pDatabaseTMParameters.GetAt(nParameter))
		{
			m_pDatabaseTMParameters.RemoveAt(nParameter);
			nParameters--;
			nParameter--;
		}
	}
	if ((pDatabaseTMParameter = (IsDlgButtonChecked(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTMParameters.GetAt(nParameter) : (CDatabaseTMParameter *)NULL))
	{
		GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
		GetDlgItem(IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->GetWindowText(szTag);
		pDatabaseTMParameter->SetDescription(szDescription);
		pDatabaseTMParameter->SetTag(szTag);
	}
	for (; nParameter == nParameters; )
	{
		if (m_pDatabaseTMParameters.Map(cFileBuffer, FALSE))
		{
			GetDlgItem(IDC_TMPARAMETER_EXPORT_FILENAME)->GetWindowText(szFileName);
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
		nParameters = -1;
		break;
	}
	for (; nParameter != nParameters; )
	{
		ShowMessage((SendDlgItemMessage(IDC_TMPARAMETER_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_TMPARAMETERDIRECTORY_EXPORT_FAILURE : SYSTEM_WARNING_TMPARAMETER_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CTMParameterExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTMParameterExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPARAMETEREXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTMParameterExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPARAMETEREXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTMParameterPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CTMParameterPropertiesDialog, CLocaleDialog)

CTMParameterPropertiesDialog::CTMParameterPropertiesDialog(CWnd *pParentWnd) : CLocaleDialog(CTMParameterPropertiesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTMParameterPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTMParameterPropertiesDialog::Initialize()
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

INT_PTR CTMParameterPropertiesDialog::DoModal(CTMParameterWnd *pParentWnd)
{
	INT_PTR  nResult;

	for (m_pParentWnd = (CWnd *)pParentWnd; (nResult = CLocaleDialog::DoModal()); ) break;
	return nResult;
}

VOID CTMParameterPropertiesDialog::ShowFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_RESETCONTENT); (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE) && cFontTools.EnumerateFont(m_lfTable[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS) && cFontTools.EnumerateFont(m_lfTable[0][1].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE))
	{
		SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][0])), 0));
		SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][0])), max(SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][0])), 0)));
		SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS))
	{
		SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][1])), 0));
		SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][1])), max(SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][1])), 0)));
		SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]);
	}
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTMParameterPropertiesDialog::ShowFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

CTMParameterWnd *CTMParameterPropertiesDialog::GetParent() CONST
{
	return((CTMParameterWnd *)CLocaleDialog::GetParent());
}

BOOL CTMParameterPropertiesDialog::IsModified() CONST
{
	CFontTools  cFontTools;

	return((lstrcmp(m_lfTable[0][0].lfFaceName, m_lfTable[1][0].lfFaceName) || (m_lfTable[0][0].lfHeight != m_lfTable[1][0].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][0]))) || m_lfTable[0][0].lfWeight != m_lfTable[1][0].lfWeight || m_lfTable[0][0].lfItalic != m_lfTable[1][0].lfItalic || lstrcmp(m_lfTable[0][1].lfFaceName, m_lfTable[1][1].lfFaceName) || (m_lfTable[0][1].lfHeight != m_lfTable[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][1])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][1]))) || m_lfTable[0][1].lfWeight != m_lfTable[1][1].lfWeight || m_lfTable[0][1].lfItalic != m_lfTable[1][1].lfItalic || GetDlgItem(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]) != GetDlgItem(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][0]) || GetDlgItem(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]) != GetDlgItem(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][1]) || GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]) != GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][0]) || GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]) != GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][1])) ? TRUE : FALSE);
}

BOOL CTMParameterPropertiesDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void CTMParameterPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTMParameterPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTMParameterPropertiesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTMParameterPropertiesDialog)
	ON_WM_PAINT()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS, OnItemsFont)
	ON_BN_CLICKED(IDC_TMPARAMETER_PROPERTIES_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR, OnSelchangeFontColor)
	ON_CBN_SELCHANGE(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE, OnSelchangeTitleBackgroundColor)
	ON_CBN_SELCHANGE(IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS, OnSelchangeKeysBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMParameterPropertiesDialog message handlers

BOOL CTMParameterPropertiesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	CheckDlgButton(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE, TRUE);
	CheckDlgButton(IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS, FALSE);
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]);
	SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]);
	AccessControl(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE));
	AccessControl(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE));
	AccessControl(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE));
	AccessControl(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE));
	AccessControl(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE));
	AccessControl(IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE));
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_COLORS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS)->EnableWindow();
	ShowFontDetails();
	return TRUE;
}

void CTMParameterPropertiesDialog::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE)) ? &m_lfTable[0][0] : &m_lfTable[0][1]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE)) ? m_nTableFontColors[0][0] : m_nTableFontColors[0][1]) : GetSysColor(COLOR_GRAYTEXT));
			cDC.FillSolidRect(rSampleText, (SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE)) ? m_nTableColors[0][0] : GetSysColor(COLOR_3DFACE)) : GetSysColor(COLOR_3DFACE));
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

void CTMParameterPropertiesDialog::OnTitleFont()
{
	SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CTMParameterPropertiesDialog::OnItemsFont()
{
	SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][1].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CTMParameterPropertiesDialog::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterPropertiesDialog::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE))
	{
		lstrcpy(m_lfTable[0][0].lfFaceName, Combobox_GetText(GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS))
	{
		lstrcpy(m_lfTable[0][1].lfFaceName, Combobox_GetText(GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][1]);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterPropertiesDialog::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterPropertiesDialog::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterPropertiesDialog::OnSelchangeFontColor()
{
	for (; IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE); )
	{
		m_nTableFontColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	for (; IsDlgButtonChecked(IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS); )
	{
		m_nTableFontColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterPropertiesDialog::OnSelchangeTitleBackgroundColor()
{
	for (m_nTableColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterPropertiesDialog::OnSelchangeKeysBackgroundColor()
{
	for (m_nTableColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMParameterPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParent()->SetProperties(&m_lfTable[0][0], &m_lfTable[0][1], m_nTableFontColors[0][0], m_nTableFontColors[0][1], m_nTableColors[0][0], m_nTableColors[0][1]);
	EndDialog(IDOK);
}

void CTMParameterPropertiesDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTMParameterPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPARAMETERPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTMParameterPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPARAMETERPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTMParameterStatusBar

IMPLEMENT_DYNCREATE(CTMParameterStatusBar, CMFCStatusBar)

BOOL CTMParameterStatusBar::SetIndicators(CONST UINT *pIDs, INT nCount)
{
	INT  nIndex;
	CString  szText;

	for (Initialize(); CMFCStatusBar::SetIndicators(pIDs, nCount); )
	{
		if ((nIndex = CommandToIndex(ID_TMPARAMETER_STATUSBAR_DETAILSPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TMPARAMETER_STATUSBAR_DETAILS), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TMPARAMETER_STATUSBAR_DETAILSPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(nIndex, szText));
		}
		if ((nIndex = CommandToIndex(ID_TMPARAMETER_STATUSBAR_FLAGPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TMPARAMETER_STATUSBAR_FLAG), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TMPARAMETER_STATUSBAR_FLAGPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_TMPARAMETER_STATUSBAR_FLAGPANE));
		}
		if ((nIndex = CommandToIndex(ID_TMPARAMETER_STATUSBAR_TYPEPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TMPARAMETER_STATUSBAR_TYPE), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TMPARAMETER_STATUSBAR_TYPEPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_TMPARAMETER_STATUSBAR_TYPEPANE));
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTMParameterStatusBar::SetPaneText(UINT nID, LPCTSTR pszText)
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

BOOL CTMParameterStatusBar::GetPaneText(UINT nID, CString &szText) CONST
{
	INT  nIndex;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		szText = CMFCStatusBar::GetPaneText(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString CTMParameterStatusBar::GetPaneText(UINT nID) CONST
{
	CString  szText;

	return((GetPaneText(nID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

INT CTMParameterStatusBar::CalcPaneWidth(INT nIndex) CONST
{
	return CalcPaneWidth(nIndex, CMFCStatusBar::GetPaneText(nIndex));
}
INT CTMParameterStatusBar::CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST
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

VOID CTMParameterStatusBar::Initialize()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = GetCount(); nIndex < nCount; nIndex++)
	{
		SetTipText(nIndex, (LPCTSTR)NULL);
		continue;
	}
}

BEGIN_MESSAGE_MAP(CTMParameterStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CTMParameterStatusBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMParameterStatusBar message handler


/////////////////////////////////////////////////////////////////////////////
// CTMParameterView

IMPLEMENT_DYNCREATE(CTMParameterView, CDisplayTableView)

CTMParameterView::CTMParameterView() : CDisplayTableView(DATABASE_COMPONENT_TMPARAMETER, IDR_TMPARAMETERFRAMEMENU)
{
	return;
}

VOID CTMParameterView::SetTitle(LPCTSTR pszName, LPCTSTR pszTitle)
{
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if ((pDatabaseTMParameter = m_pDatabaseTMParameters[0].GetAt(m_pDatabaseTMParameters[0].Find(pszName))))
	{
		for (pDatabaseTMParameter->SetDescription(pszTitle); !m_szName.Compare(pszName); )
		{
			UpdateTables();
			break;
		}
	}
	m_szName = pszName;
	m_szTitle = pszTitle;
}

BOOL CTMParameterView::GetTitle(CString &szName, CString &szTitle) CONST
{
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (szName.Empty(), szTitle.Empty(); (pDatabaseTMParameter = m_pDatabaseTMParameters[0].GetAt(m_pDatabaseTMParameters[0].Find(GetName()))); )
	{
		szTitle = pDatabaseTMParameter->GetDescription();
		szName = pDatabaseTMParameter->GetTag();
		return TRUE;
	}
	szName = m_szName;
	szTitle = m_szTitle;
	return !szName.IsEmpty();
}

BOOL CTMParameterView::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	for (SetTablesFonts(plfTitle, plfItems), SetTablesFontColors(nTitleColor, nItemsColor), SetTablesColors(nTitleBackground, nKeysBackground); IsWindow(GetSafeHwnd()); )
	{
		RepositionTables();
		break;
	}
	return TRUE;
}

BOOL CTMParameterView::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	GetTablesFonts(plfTitle, plfItems);
	GetTablesFontColors(nTitleColor, nItemsColor);
	GetTablesColors(nTitleBackground, nKeysBackground);
	return TRUE;
}

VOID CTMParameterView::UpdateTableForms(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nIndex, BOOL bDelete)
{
	UpdateDatabase(pDatabaseTMParameter, (nIndex > 0) ? (nIndex - 1) : nIndex, bDelete);
	UpdateForms(GetParent(), pDatabaseTMParameter, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMParameterView::UpdateTableForms(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTMNumCalTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE);
}
VOID CTMParameterView::UpdateTableForms(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTMTxtCalTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE);
}
VOID CTMParameterView::UpdateTableForms(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTMNumOolTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE);
}
VOID CTMParameterView::UpdateTableForms(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTMTxtOolTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE);
}
VOID CTMParameterView::UpdateTableForms(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTMParameterGroup, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP);
}
VOID CTMParameterView::UpdateTableForms(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	UpdateForms((CTCParameterWnd *)NULL, pDatabaseTCNumCalTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE);
}
VOID CTMParameterView::UpdateTableForms(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	UpdateForms((CTCParameterWnd *)NULL, pDatabaseTCTxtCalTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE);
}

CTMParameterWnd *CTMParameterView::GetParent() CONST
{
	return((CTMParameterWnd *)CDisplayTableView::GetParent());
}

BOOL CTMParameterView::CheckPrivilege() CONST
{
	return CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE);
}

BEGIN_MESSAGE_MAP(CTMParameterView, CDisplayTableView)
	//{{AFX_MSG_MAP(CTMParameterView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMParameterView message handlers

int CTMParameterView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayTableView::OnCreate(lpCreateStruct) != -1 && GetDatabase()->CreateTables(this, GetComponent())) ? 0 : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTMParameterWnd

IMPLEMENT_DYNCREATE(CTMParameterWnd, CDisplayWnd)

CTMParameterWnd::CTMParameterWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TMPARAMETER);
}
CTMParameterWnd::CTMParameterWnd(LPCTSTR pszName) : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TMPARAMETER);
	SetName(pszName);
}

BOOL CTMParameterWnd::Create(CMDIFrameWnd *pParentWnd, UINT nShow)
{
	return Create(pParentWnd, GetName(), nShow);
}
BOOL CTMParameterWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszName, UINT nShow)
{
	CRect  rPosition;

	for (SetName(pszName), rPosition = m_rPosition; CDisplayWnd::Create(pParentWnd, STRING(IDS_DISPLAY_TITLE_TMPARAMETER), (nShow == (UINT)-1) ? CRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) : CRect(0, 0, 0, 0), IDR_TMPARAMETERFRAME, (nShow != SW_SHOWMINIMIZED || nShow != SW_SHOWMAXIMIZED) ? (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE) : (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW)); )
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

VOID CTMParameterWnd::SetName(LPCTSTR pszName)
{
	m_wndView.SetName(pszName);
}

CString CTMParameterWnd::GetName() CONST
{
	return m_wndView.GetName();
}

VOID CTMParameterWnd::SetTitle(LPCTSTR pszTitle)
{
	m_wndView.SetTitle(GetName(), pszTitle);
}

CString CTMParameterWnd::GetTitle() CONST
{
	CString  szName;
	CString  szTitle;

	return((m_wndView.GetTitle(szName, szTitle)) ? szTitle : STRING(IDS_DISPLAY_TITLE_TMPARAMETER));
}

BOOL CTMParameterWnd::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	return m_wndView.SetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CTMParameterWnd::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	return m_wndView.GetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CTMParameterWnd::IsModified() CONST
{
	return((m_wndView.Check()) ? m_wndView.IsModified() : FALSE);
}

BOOL CTMParameterWnd::Save(INT nPosition) CONST
{
	UINT  nFlags;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	cProfile.DeleteDisplayWindowInfo(nPosition);
	return((GetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && cProfile.SetDisplayWindowType(nPosition, GetType()) && cProfile.SetDisplayWindowName(nPosition, GetName()) && cProfile.SetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, (nFlags = (!IsIconic()) ? ((!IsZoomed()) ? SW_SHOWNORMAL : SW_SHOWMAXIMIZED) : SW_SHOWMINIMIZED)) && cProfile.SetTMParametersFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? TRUE : FALSE);
}

INT CTMParameterWnd::Load(INT nPosition)
{
	UINT  nFlags;
	CString  szName;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	return((cProfile.GetDisplayWindowName(nPosition, szName) && cProfile.GetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, nFlags) && cProfile.GetTMParametersFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && SetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? CTMParameterWnd::Create(GetMainWnd(), szName, nFlags) : -1);
}

BOOL CTMParameterWnd::UpdateProperties()
{
	return((m_dlgProperties.DoModal(this) == IDOK) ? TRUE : FALSE);
}

BOOL CTMParameterWnd::IsUpdatingProperties() CONST
{
	return IsWindow(m_dlgProperties.GetSafeHwnd());
}

BOOL CTMParameterWnd::HasProperties() CONST
{
	return TRUE;
}

BOOL CTMParameterWnd::CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST
{
	return m_wndView.CheckTableDropTarget(pszTable, nComponent, point);
}

BOOL CTMParameterWnd::DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point)
{
	return m_wndView.DropOnTableTarget(pszTable, nComponent, point);
}

VOID CTMParameterWnd::UpdateAllPanes(LPCTSTR pszDetails, LPCTSTR pszFlag, LPCTSTR pszType)
{
	m_wndStatusBar.SetPaneText(ID_TMPARAMETER_STATUSBAR_DETAILSPANE, pszDetails);
	m_wndStatusBar.SetPaneText(ID_TMPARAMETER_STATUSBAR_FLAGPANE, pszFlag);
	m_wndStatusBar.SetPaneText(ID_TMPARAMETER_STATUSBAR_TYPEPANE, pszType);
}

BOOL CTMParameterWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
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
				if (PrintJob(cDC, &m_wndView, STRING(IDS_DISPLAY_TITLE_TMPARAMETER), cPrintProfileInfo.GetPrinterName(), rtMargin[0], bMetrics, nFlags))
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
					if (PrintJob(cDC, &m_wndView, STRING(IDS_DISPLAY_TITLE_TMPARAMETER), (LPCTSTR)pDevMode->dmDeviceName, rtMargin[0], bMetrics, nFlags, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : -1, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : -1))
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

VOID CTMParameterWnd::DoSave()
{
	if (m_wndView.DoSave())
	{
		GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_TMPARAMETER);
		return;
	}
}

BOOL CTMParameterWnd::CanSave() CONST
{
	return((m_wndView.CanSave()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

VOID CTMParameterWnd::DoCheck()
{
	m_wndView.DoCheck();
}

BOOL CTMParameterWnd::CanCheck() CONST
{
	return((m_wndView.CanCheck()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

VOID CTMParameterWnd::DoDelete()
{
	CString  szName;
	CString  szTitle;

	for (szName = GetName(), szTitle = GetTitle(); m_wndView.DoDelete(); )
	{
		GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_TMPARAMETER);
		break;
	}
}

BOOL CTMParameterWnd::CanDelete() CONST
{
	return((m_wndView.CanDelete()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

VOID CTMParameterWnd::DoUndo()
{
	m_wndView.DoUndo();
}

BOOL CTMParameterWnd::CanUndo() CONST
{
	return m_wndView.CanUndo();
}

VOID CTMParameterWnd::DoRedo()
{
	m_wndView.DoRedo();
}

BOOL CTMParameterWnd::CanRedo() CONST
{
	return m_wndView.CanRedo();
}

VOID CTMParameterWnd::DoSelectAll()
{
	m_wndView.DoSelectAll();
}

BOOL CTMParameterWnd::CanSelectAll() CONST
{
	return m_wndView.CanSelectAll();
}

VOID CTMParameterWnd::DoCutSel()
{
	m_wndView.DoCutSel();
}

BOOL CTMParameterWnd::CanCutSel() CONST
{
	return m_wndView.CanCutSel();
}

VOID CTMParameterWnd::DoCopySel()
{
	m_wndView.DoCopySel();
}

BOOL CTMParameterWnd::CanCopySel() CONST
{
	return m_wndView.CanCopySel();
}

VOID CTMParameterWnd::DoPasteSel()
{
	m_wndView.DoPasteSel();
}

BOOL CTMParameterWnd::CanPasteSel() CONST
{
	return m_wndView.CanPasteSel();
}

VOID CTMParameterWnd::DoDeleteSel()
{
	m_wndView.DoDeleteSel();
}

BOOL CTMParameterWnd::CanDeleteSel() CONST
{
	return m_wndView.CanDeleteSel();
}

BOOL CTMParameterWnd::CanPrint(UINT nFlags) CONST
{
	return m_wndView.CanPrint(nFlags);
}

VOID CTMParameterWnd::DoClose()
{
	m_wndView.DoClose();
}

BOOL CTMParameterWnd::DoSaveTable()
{
	return m_wndView.DoSaveTable();
}

BOOL CTMParameterWnd::CanSaveTable() CONST
{
	return((m_wndView.CanSaveTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoCheckTable()
{
	return m_wndView.DoCheckTable();
}

BOOL CTMParameterWnd::CanCheckTable() CONST
{
	return((m_wndView.CanCheckTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoDeleteTable()
{
	return m_wndView.DoDeleteTable();
}

BOOL CTMParameterWnd::CanDeleteTable() CONST
{
	return((m_wndView.CanDeleteTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoPrintTable()
{
	return Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE);
}

BOOL CTMParameterWnd::CanPrintTable() CONST
{
	return CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE);
}

BOOL CTMParameterWnd::DoPrintAllTables()
{
	return Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL);
}

BOOL CTMParameterWnd::CanPrintAllTables() CONST
{
	return CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL);
}

BOOL CTMParameterWnd::DoImportTables()
{
	return m_wndView.DoImportTables();
}

BOOL CTMParameterWnd::CanImportTables() CONST
{
	return((m_wndView.CanImportTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoExportTables()
{
	return m_wndView.DoExportTables();
}

BOOL CTMParameterWnd::CanExportTables() CONST
{
	return m_wndView.CanExportTables();
}

BOOL CTMParameterWnd::DoDiscardTables()
{
	return m_wndView.DoDiscardTables();
}

BOOL CTMParameterWnd::CanDiscardTables() CONST
{
	return((m_wndView.CanDiscardTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoDiscardAllTables()
{
	return m_wndView.DoDiscardAllTables();
}

BOOL CTMParameterWnd::CanDiscardAllTables() CONST
{
	return((m_wndView.CanDiscardAllTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoResetTables()
{
	return m_wndView.DoResetTables();
}

BOOL CTMParameterWnd::CanResetTables() CONST
{
	return((m_wndView.CanResetTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoInsertTableRowAbove()
{
	return m_wndView.DoInsertTableRowAbove();
}

BOOL CTMParameterWnd::CanInsertTableRowAbove() CONST
{
	return((m_wndView.CanInsertTableRowAbove()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoInsertTableRowBelow()
{
	return m_wndView.DoInsertTableRowBelow();
}

BOOL CTMParameterWnd::CanInsertTableRowBelow() CONST
{
	return((m_wndView.CanInsertTableRowBelow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoInsertTableColumnBefore()
{
	return m_wndView.DoInsertTableColumnBefore();
}

BOOL CTMParameterWnd::CanInsertTableColumnBefore() CONST
{
	return((m_wndView.CanInsertTableColumnBefore()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoInsertTableColumnAfter()
{
	return m_wndView.DoInsertTableColumnAfter();
}

BOOL CTMParameterWnd::CanInsertTableColumnAfter() CONST
{
	return((m_wndView.CanInsertTableColumnAfter()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoClearTableRow()
{
	return m_wndView.DoClearTableRow();
}

BOOL CTMParameterWnd::CanClearTableRow() CONST
{
	return((m_wndView.CanClearTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoDeleteTableRow()
{
	return m_wndView.DoDeleteTableRow();
}

BOOL CTMParameterWnd::CanDeleteTableRow() CONST
{
	return((m_wndView.CanDeleteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoDeleteTableColumn()
{
	return m_wndView.DoDeleteTableColumn();
}

BOOL CTMParameterWnd::CanDeleteTableColumn() CONST
{
	return((m_wndView.CanDeleteTableColumn()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

BOOL CTMParameterWnd::DoCopyTableRow()
{
	return m_wndView.DoCopyTableRow();
}

BOOL CTMParameterWnd::CanCopyTableRow() CONST
{
	return m_wndView.CanCopyTableRow();
}

BOOL CTMParameterWnd::DoPasteTableRow()
{
	return m_wndView.DoPasteTableRow();
}

BOOL CTMParameterWnd::CanPasteTableRow() CONST
{
	return((m_wndView.CanPasteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE) : FALSE);
}

VOID CTMParameterWnd::GotoTable(ULONGLONG nComponent, LPCTSTR pszName)
{
	m_wndView.GotoTable(nComponent, pszName);
}

VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMParameters &pDatabaseTMParameters)
{
	m_wndView.UpdateTables(pDatabaseTMParameters);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE, pDatabaseTMParameter->GetTag(), bDelete);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, pDatabaseTMNumCalTable->GetName(), bDelete);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, pDatabaseTMTxtCalTable->GetName(), bDelete);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, pDatabaseTMNumOolTable->GetName(), bDelete);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, pDatabaseTMTxtOolTable->GetName(), bDelete);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP, pDatabaseTMParameterGroup->GetName(), bDelete);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMParameterWnd::UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE);
}
VOID CTMParameterWnd::UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMParameterWnd::UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMParameterWnd::UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMParameterWnd::UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete)
{
	m_wndView.UpdateTables(nComponent, pszName, bDelete);
	m_wndView.ClearUndo();
}
VOID CTMParameterWnd::UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete)
{
	m_wndView.UpdateTables(nComponent, nID, bDelete);
	m_wndView.ClearUndo();
}
VOID CTMParameterWnd::UpdateTables(ULONGLONG nComponent)
{
	m_wndView.UpdateTables(nComponent);
}
VOID CTMParameterWnd::UpdateTables()
{
	m_wndView.UpdateTables();
}

VOID CTMParameterWnd::UpdateTitle()
{
	SetWindowText(STRING(IDS_DISPLAY_TITLE_TMPARAMETER));
}

VOID CTMParameterWnd::UpdateMenus()
{
	GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
}

VOID CTMParameterWnd::UpdateStatusBar()
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

CString CTMParameterWnd::GetPrintDocTitle(LPCTSTR pszTag, UINT nFlags) CONST
{
	CDatabaseTMParameter  *pDatabaseTMParameter;

	return(((pDatabaseTMParameter = (nFlags & DISPLAYTABLEVIEW_PRINT_TABLE) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pszTag)) : (CDatabaseTMParameter *)NULL) && !pDatabaseTMParameter->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseTMParameter->GetDescription() : pszTag);
}

CString CTMParameterWnd::GetPrintDocInfoTitle() CONST
{
	return STRING(IDS_DISPLAY_TITLE_TMPARAMETER);
}

VOID CTMParameterWnd::AdjustToPrivileges()
{
	if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPARAMETER_CHANGE))
	{
		m_wndView.UnSelectAll();
		return;
	}
}

BEGIN_MESSAGE_MAP(CTMParameterWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CTMParameterWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_TMPARAMETER_STATUSBAR_DETAILSPANE, OnUpdateStatusBarDetailsPane)
	ON_UPDATE_COMMAND_UI(ID_TMPARAMETER_STATUSBAR_FLAGPANE, OnUpdateStatusBarFlagPane)
	ON_UPDATE_COMMAND_UI(ID_TMPARAMETER_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMParameterWnd message handlers

int CTMParameterWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayWnd::OnCreate(lpCreateStruct) != -1 && LoadAccelTable(IDR_TMPARAMETERFRAME)) ? 0 : -1);
}

BOOL CTMParameterWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	CRect  rBar;

	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1))
	{
		m_wndStatusBar.GetWindowRect(rBar);
		return m_wndView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
	}
	return FALSE;
}

void CTMParameterWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rBar;

	m_wndStatusBar.GetWindowRect(rBar);
	m_wndView.MoveWindow(0, 0, cx, cy - rBar.Height());
	CDisplayWnd::OnSize(nType, cx, cy);
}

void CTMParameterWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	if (!bActivate) m_wndView.UnSelectAll();
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CTMParameterWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN) m_wndView.ActivateTable();
	CDisplayWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTMParameterWnd::OnClose()
{
	CHourglassCursor  cCursor;

	DoClose();
	CDisplayWnd::OnClose();
}

void CTMParameterWnd::OnUpdateStatusBarDetailsPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTMParameterWnd::OnUpdateStatusBarFlagPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTMParameterWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
