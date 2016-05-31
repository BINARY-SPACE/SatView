// TCPARAMETER.CPP : Telecommand Parameter Form Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telecommand
// parameter form related interface.
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
	ID_TCPARAMETER_STATUSBAR_DETAILSPANE,
	ID_TCPARAMETER_STATUSBAR_FLAGPANE,
	ID_TCPARAMETER_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CTCParameterOpenDialog dialog

IMPLEMENT_DYNCREATE(CTCParameterOpenDialog, CLocaleDialog)

CTCParameterOpenDialog::CTCParameterOpenDialog(CWnd *pParentWnd) : CLocaleDialog(CTCParameterOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCParameterOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCParameterOpenDialog::Initialize()
{
	m_pDatabaseTCParameters.Copy(GetDatabase()->GetTCParameters());
	return TRUE;
}

VOID CTCParameterOpenDialog::EnumTCParameters()
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	CString  szItem;
	CDatabaseTCParameter  *pDatabaseTCParameter;

	for (nParameter = 0, nParameters = (INT)m_pDatabaseTCParameters.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTCParameter = m_pDatabaseTCParameters.GetAt(nParameter)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_TAG); )
				{
					szItem = pDatabaseTCParameter->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCParameter->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY), nParameter, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY), nParameter, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY), 0);
	GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CTCParameterOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void CTCParameterOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCParameterOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCParameterOpenDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTCParameters.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCParameterOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCParameterOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPARAMETER_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCParameterOpenDialog message handlers

BOOL CTCParameterOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TCPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TCPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TCPARAMETER_OPEN_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (2 * rColumns.Width()) / 9; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumTCParameters();
	GetDlgItem(IDC_TCPARAMETER_OPEN_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_TCPARAMETER_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_OPEN_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_OPEN_DATABASE)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY)->SetFocus();
	return FALSE;
}

BOOL CTCParameterOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPARAMETER_OPEN_DIRECTORY)
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

void CTCParameterOpenDialog::OnOK()
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
	CTCParameterWnd  *pTCParameterWnd;
	CHourglassCursor  cCursor;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_TAG))
		{
			szTag = Listview_GetText(GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY)), nColumn);
			continue;
		}
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_TCPARAMETEROPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
		{
			szDescription = Listview_GetText(GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_TCPARAMETER_OPEN_DIRECTORY)), nColumn);
			continue;
		}
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TCPARAMETER)
		{
			if ((pTCParameterWnd = (CTCParameterWnd *)pDisplayWnd)->GetName() == szTag)
			{
				pTCParameterWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		if ((pTCParameterWnd = new CTCParameterWnd(szTag)))
		{
			if (pTCParameterWnd->Create(GetMainWnd()))
			{
				EndDialog(IDOK);
				return;
			}
		}
		szMessage.Format(STRING(IDS_TCPARAMETER_FAILURE_LOAD), (LPCTSTR)szDescription);
		ShowMessage(szMessage);
	}
	EndDialog(IDOK);
}

void CTCParameterOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCParameterOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCPARAMETEROPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCParameterOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCPARAMETEROPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCParameterImportDialog dialog

IMPLEMENT_DYNCREATE(CTCParameterImportDialog, CLocaleDialog)

CTCParameterImportDialog::CTCParameterImportDialog(CWnd *pParentWnd) : CLocaleDialog(CTCParameterImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCParameterImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CTCParameterImportDialog::DoModal(CDatabaseTCParameters &pDatabaseTCParameters)
{
	INT_PTR  nResult;

	for (m_pDatabaseTCParameters.RemoveAll(); (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCParameters.Copy(&m_pDatabaseTCParameters);
		break;
	}
	return nResult;
}

VOID CTCParameterImportDialog::EnumTCParameters()
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
	CDatabaseTCParameter  *pDatabaseTCParameter;

	SendDlgItemMessage(IDC_TCPARAMETER_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TCPARAMETER_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				for (nParameter = 0, nParameters = (m_pDatabaseTCParameters.Unmap(cFileBuffer, FALSE)) ? (INT)m_pDatabaseTCParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
				{
					if ((pDatabaseTCParameter = m_pDatabaseTCParameters.GetAt(nParameter)))
					{
						for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPARAMETERIMPORTDIALOG_DIRECTORYTITLEITEM_TAG); )
							{
								szItem = pDatabaseTCParameter->GetTag();
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPARAMETERIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
							{
								szItem = pDatabaseTCParameter->GetDescription();
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_TCPARAMETER_IMPORT_DIRECTORY), nParameter, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_TCPARAMETER_IMPORT_DIRECTORY), nParameter, nColumn, szItem);
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
	GetDlgItem(IDC_TCPARAMETER_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCParameterImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TCPARAMETER_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCPARAMETER_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_TCPARAMETER_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CTCParameterImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCParameterImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCParameterImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCParameterImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCParameterImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPARAMETER_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_TCPARAMETER_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_TCPARAMETER_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TCPARAMETER_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG, OnEditchangeTag)
	ON_EN_CHANGE(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCParameterImportDialog message handlers

BOOL CTCParameterImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_TCPARAMETERIMPORTDIALOG_DIRECTORYTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TCPARAMETERIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TCPARAMETER_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG, EM_LIMITTEXT, GetDatabase()->GetTCParameterTagLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPARAMETER_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_TCPARAMETER_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_TCPARAMETER_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CTCParameterImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPARAMETER_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_TCPARAMETER_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM)->EnableWindow();
			}
			else
			{
				CheckDlgButton(IDC_TCPARAMETER_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CTCParameterImportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TCPARAMETER_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_TCPARAMETER_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumTCParameters();
	}
	SendDlgItemMessage(IDC_TCPARAMETER_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TCPARAMETER_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterImportDialog::OnDefault()
{
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterImportDialog::OnCustom()
{
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterImportDialog::OnEditchangeFileName()
{
	EnumTCParameters();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterImportDialog::OnEditchangeTag()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterImportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterImportDialog::OnOK()
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
	CDatabaseTCParameter  *pDatabaseTCParameter[2];
	CDatabaseTCParameters  pDatabaseTCParameters;
	CHourglassCursor  cCursor;

	for (nParameter = 0, nParameters = (INT)SendDlgItemMessage(IDC_TCPARAMETER_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nParameter < nParameters; nParameter++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_TCPARAMETER_IMPORT_DIRECTORY), nParameter))
		{
			delete m_pDatabaseTCParameters.GetAt(nParameter);
			m_pDatabaseTCParameters.SetAt(nParameter, NULL);
		}
	}
	for (nParameter = 0, nParameters = (pDatabaseTCParameters.Copy(GetDatabase()->GetTCParameters())) ? nParameters : -1; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTCParameter[0] = m_pDatabaseTCParameters.GetAt(nParameter)))
		{
			if (IsDlgButtonChecked(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM))
			{
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_TAG)->GetWindowText(szTag);
				GetDlgItem(IDC_TCPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
				pDatabaseTCParameter[0]->SetDescription(szDescription);
				pDatabaseTCParameter[0]->SetTag(szTag);
			}
			if ((pDatabaseTCParameter[1] = pDatabaseTCParameters.GetAt((nIndex = pDatabaseTCParameters.Find(pDatabaseTCParameter[0]->GetTag())))))
			{
				pDatabaseTCParameter[1]->Copy(pDatabaseTCParameter[0]);
				pParameters.Add(pDatabaseTCParameter[1]);
				nParameterIDs.Add(nIndex);
				continue;
			}
			if ((pDatabaseTCParameter[1] = new CDatabaseTCParameter))
			{
				pDatabaseTCParameter[1]->Copy(pDatabaseTCParameter[0]);
				if ((nIndex = pDatabaseTCParameters.Add(pDatabaseTCParameter[1])) >= 0)
				{
					pParameters.Add(pDatabaseTCParameter[1]);
					nParameterIDs.Add(-(nIndex + 1));
					continue;
				}
				delete pDatabaseTCParameter[1];
			}
			break;
		}
		m_pDatabaseTCParameters.RemoveAt(nParameter);
		nParameters--;
		nParameter--;
	}
	for (; nParameter == nParameters; )
	{
		if (GetDatabase()->GetTCParameters()->Copy(&pDatabaseTCParameters))
		{
			for (nItem = 0, nItems = (INT)pParameters.GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTCParameter[0] = (CDatabaseTCParameter *)pParameters.GetAt(nItem)))
				{
					if (GetDatabase()->Save(pDatabaseTCParameter[0]))
					{
						nIndex = (INT)nParameterIDs.GetAt(nItem);
						UpdateDatabase(pDatabaseTCParameter[0], nIndex);
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
		ShowMessage((SendDlgItemMessage(IDC_TCPARAMETER_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_TCPARAMETERDIRECTORY_IMPORT_FAILURE : SYSTEM_WARNING_TCPARAMETER_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CTCParameterImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCParameterImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCPARAMETERIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCParameterImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCPARAMETERIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCParameterExportDialog dialog

IMPLEMENT_DYNCREATE(CTCParameterExportDialog, CLocaleDialog)

CTCParameterExportDialog::CTCParameterExportDialog(CWnd *pParentWnd) : CLocaleDialog(CTCParameterExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCParameterExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CTCParameterExportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

BOOL CTCParameterExportDialog::EnumTCParameters()
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	CString  szItem;
	CDatabaseTCParameter  *pDatabaseTCParameter;

	for (nParameter = 0, nParameters = (m_pDatabaseTCParameters.Copy(GetDatabase()->GetTCParameters())) ? (INT)m_pDatabaseTCParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTCParameter = m_pDatabaseTCParameters.GetAt(nParameter)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPARAMETEREXPORTDIALOG_DIRECTORYTITLEITEM_TAG); )
				{
					szItem = pDatabaseTCParameter->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TCPARAMETEREXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTCParameter->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TCPARAMETER_EXPORT_DIRECTORY), nParameter, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TCPARAMETER_EXPORT_DIRECTORY), nParameter, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_TCPARAMETER_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPARAMETER_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TCPARAMETER_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTCParameterExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TCPARAMETER_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCPARAMETER_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_TCPARAMETER_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CTCParameterExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCParameterExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTCParameterExportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTCParameters.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTCParameterExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCParameterExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPARAMETER_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_TCPARAMETER_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_TCPARAMETER_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TCPARAMETER_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG, OnEditchangeTag)
	ON_EN_CHANGE(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCParameterExportDialog message handlers

BOOL CTCParameterExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TCPARAMETER_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_TCPARAMETEREXPORTDIALOG_DIRECTORYTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TCPARAMETEREXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TCPARAMETER_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG, EM_LIMITTEXT, GetDatabase()->GetTCParameterTagLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TCPARAMETER_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumTCParameters())
	{
		CheckDlgButton(IDC_TCPARAMETER_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_TCPARAMETER_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TCPARAMETER_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_TCPARAMETER_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_TCPARAMETER_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM)->EnableWindow();
		GetDlgItem(IDC_TCPARAMETER_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL CTCParameterExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TCPARAMETER_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_TCPARAMETER_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM)->EnableWindow();
				CheckDlgButton(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM, FALSE);
			}
			else
			{
				CheckDlgButton(IDC_TCPARAMETER_EXPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CTCParameterExportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TCPARAMETER_EXPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_TCPARAMETER_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_TCPARAMETER_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TCPARAMETER_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterExportDialog::OnDefault()
{
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterExportDialog::OnCustom()
{
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterExportDialog::OnEditchangeTag()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterExportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterExportDialog::OnOK()
{
	INT  nParameter;
	INT  nParameters;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szTag;
	CString  szFileName;
	CString  szDescription;
	CByteArray  cFileBuffer;
	CDatabaseTCParameter  *pDatabaseTCParameter;
	CHourglassCursor  cCursor;

	for (nParameter = 0, nParameters = (INT)SendDlgItemMessage(IDC_TCPARAMETER_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nParameter < nParameters; nParameter++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_TCPARAMETER_EXPORT_DIRECTORY), nParameter))
		{
			delete m_pDatabaseTCParameters.GetAt(nParameter);
			m_pDatabaseTCParameters.SetAt(nParameter, NULL);
		}
	}
	for (nParameter = 0; nParameter < nParameters; nParameter++)
	{
		if (!m_pDatabaseTCParameters.GetAt(nParameter))
		{
			m_pDatabaseTCParameters.RemoveAt(nParameter);
			nParameters--;
			nParameter--;
		}
	}
	if ((pDatabaseTCParameter = (IsDlgButtonChecked(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCParameters.GetAt(nParameter) : (CDatabaseTCParameter *)NULL))
	{
		GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
		GetDlgItem(IDC_TCPARAMETER_EXPORT_TYPE_CUSTOM_TAG)->GetWindowText(szTag);
		pDatabaseTCParameter->SetDescription(szDescription);
		pDatabaseTCParameter->SetTag(szTag);
	}
	for (; nParameter == nParameters; )
	{
		if (m_pDatabaseTCParameters.Map(cFileBuffer, FALSE))
		{
			GetDlgItem(IDC_TCPARAMETER_EXPORT_FILENAME)->GetWindowText(szFileName);
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
		ShowMessage((SendDlgItemMessage(IDC_TCPARAMETER_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_TCPARAMETERDIRECTORY_EXPORT_FAILURE : SYSTEM_WARNING_TCPARAMETER_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CTCParameterExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCParameterExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCPARAMETEREXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCParameterExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCPARAMETEREXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCParameterPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CTCParameterPropertiesDialog, CLocaleDialog)

CTCParameterPropertiesDialog::CTCParameterPropertiesDialog(CWnd *pParentWnd) : CLocaleDialog(CTCParameterPropertiesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTCParameterPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTCParameterPropertiesDialog::Initialize()
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

INT_PTR CTCParameterPropertiesDialog::DoModal(CTCParameterWnd *pParentWnd)
{
	INT_PTR  nResult;

	for (m_pParentWnd = (CWnd *)pParentWnd; (nResult = CLocaleDialog::DoModal()); ) break;
	return nResult;
}

VOID CTCParameterPropertiesDialog::ShowFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_RESETCONTENT); (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE) && cFontTools.EnumerateFont(m_lfTable[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_ITEMS) && cFontTools.EnumerateFont(m_lfTable[0][1].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE))
	{
		SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][0])), 0));
		SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][0])), max(SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][0])), 0)));
		SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_ITEMS))
	{
		SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][1])), 0));
		SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][1])), max(SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][1])), 0)));
		SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]);
	}
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTCParameterPropertiesDialog::ShowFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

CTCParameterWnd *CTCParameterPropertiesDialog::GetParent() CONST
{
	return((CTCParameterWnd *)CLocaleDialog::GetParent());
}

BOOL CTCParameterPropertiesDialog::IsModified() CONST
{
	CFontTools  cFontTools;

	return((lstrcmp(m_lfTable[0][0].lfFaceName, m_lfTable[1][0].lfFaceName) || (m_lfTable[0][0].lfHeight != m_lfTable[1][0].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][0]))) || m_lfTable[0][0].lfWeight != m_lfTable[1][0].lfWeight || m_lfTable[0][0].lfItalic != m_lfTable[1][0].lfItalic || lstrcmp(m_lfTable[0][1].lfFaceName, m_lfTable[1][1].lfFaceName) || (m_lfTable[0][1].lfHeight != m_lfTable[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][1])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][1]))) || m_lfTable[0][1].lfWeight != m_lfTable[1][1].lfWeight || m_lfTable[0][1].lfItalic != m_lfTable[1][1].lfItalic || GetDlgItem(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]) != GetDlgItem(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][0]) || GetDlgItem(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]) != GetDlgItem(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][1]) || GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]) != GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][0]) || GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]) != GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][1])) ? TRUE : FALSE);
}

BOOL CTCParameterPropertiesDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void CTCParameterPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCParameterPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCParameterPropertiesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTCParameterPropertiesDialog)
	ON_WM_PAINT()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_TCPARAMETER_PROPERTIES_FONTS_ITEMS, OnItemsFont)
	ON_BN_CLICKED(IDC_TCPARAMETER_PROPERTIES_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR, OnSelchangeFontColor)
	ON_CBN_SELCHANGE(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE, OnSelchangeTitleBackgroundColor)
	ON_CBN_SELCHANGE(IDC_TCPARAMETER_PROPERTIES_COLORS_KEYS, OnSelchangeKeysBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCParameterPropertiesDialog message handlers

BOOL CTCParameterPropertiesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	CheckDlgButton(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE, TRUE);
	CheckDlgButton(IDC_TCPARAMETER_PROPERTIES_FONTS_ITEMS, FALSE);
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_COLORS_KEYS, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_COLORS_KEYS, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]);
	SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_COLORS_KEYS, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]);
	AccessControl(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE));
	AccessControl(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE));
	AccessControl(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE));
	AccessControl(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE));
	AccessControl(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE));
	AccessControl(IDC_TCPARAMETER_PROPERTIES_COLORS_KEYS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE));
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_ITEMS)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_COLORS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_COLORS_KEYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TCPARAMETER_PROPERTIES_COLORS_KEYS)->EnableWindow();
	ShowFontDetails();
	return TRUE;
}

void CTCParameterPropertiesDialog::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE)) ? &m_lfTable[0][0] : &m_lfTable[0][1]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE)) ? m_nTableFontColors[0][0] : m_nTableFontColors[0][1]) : GetSysColor(COLOR_GRAYTEXT));
			cDC.FillSolidRect(rSampleText, (SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE)) ? m_nTableColors[0][0] : GetSysColor(COLOR_3DFACE)) : GetSysColor(COLOR_3DFACE));
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

void CTCParameterPropertiesDialog::OnTitleFont()
{
	SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CTCParameterPropertiesDialog::OnItemsFont()
{
	SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][1].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CTCParameterPropertiesDialog::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterPropertiesDialog::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE))
	{
		lstrcpy(m_lfTable[0][0].lfFaceName, Combobox_GetText(GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_ITEMS))
	{
		lstrcpy(m_lfTable[0][1].lfFaceName, Combobox_GetText(GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][1]);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterPropertiesDialog::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterPropertiesDialog::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TCPARAMETER_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterPropertiesDialog::OnSelchangeFontColor()
{
	for (; IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_TITLE); )
	{
		m_nTableFontColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	for (; IsDlgButtonChecked(IDC_TCPARAMETER_PROPERTIES_FONTS_ITEMS); )
	{
		m_nTableFontColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterPropertiesDialog::OnSelchangeTitleBackgroundColor()
{
	for (m_nTableColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_COLORS_TITLE, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterPropertiesDialog::OnSelchangeKeysBackgroundColor()
{
	for (m_nTableColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_COLORS_KEYS, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TCPARAMETER_PROPERTIES_COLORS_KEYS, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTCParameterPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParent()->SetProperties(&m_lfTable[0][0], &m_lfTable[0][1], m_nTableFontColors[0][0], m_nTableFontColors[0][1], m_nTableColors[0][0], m_nTableColors[0][1]);
	EndDialog(IDOK);
}

void CTCParameterPropertiesDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTCParameterPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCPARAMETERPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTCParameterPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TCPARAMETERPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTCParameterStatusBar

IMPLEMENT_DYNCREATE(CTCParameterStatusBar, CMFCStatusBar)

BOOL CTCParameterStatusBar::SetIndicators(CONST UINT *pIDs, INT nCount)
{
	INT  nIndex;
	CString  szText;

	for (Initialize(); CMFCStatusBar::SetIndicators(pIDs, nCount); )
	{
		if ((nIndex = CommandToIndex(ID_TCPARAMETER_STATUSBAR_DETAILSPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TCPARAMETER_STATUSBAR_DETAILS), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TCPARAMETER_STATUSBAR_DETAILSPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(nIndex, szText));
		}
		if ((nIndex = CommandToIndex(ID_TCPARAMETER_STATUSBAR_FLAGPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TCPARAMETER_STATUSBAR_FLAG), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TCPARAMETER_STATUSBAR_FLAGPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_TCPARAMETER_STATUSBAR_FLAGPANE));
		}
		if ((nIndex = CommandToIndex(ID_TCPARAMETER_STATUSBAR_TYPEPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TCPARAMETER_STATUSBAR_TYPE), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TCPARAMETER_STATUSBAR_TYPEPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_TCPARAMETER_STATUSBAR_TYPEPANE));
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCParameterStatusBar::SetPaneText(UINT nID, LPCTSTR pszText)
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

BOOL CTCParameterStatusBar::GetPaneText(UINT nID, CString &szText) CONST
{
	INT  nIndex;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		szText = CMFCStatusBar::GetPaneText(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString CTCParameterStatusBar::GetPaneText(UINT nID) CONST
{
	CString  szText;

	return((GetPaneText(nID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

INT CTCParameterStatusBar::CalcPaneWidth(INT nIndex) CONST
{
	return CalcPaneWidth(nIndex, CMFCStatusBar::GetPaneText(nIndex));
}
INT CTCParameterStatusBar::CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST
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

VOID CTCParameterStatusBar::Initialize()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = GetCount(); nIndex < nCount; nIndex++)
	{
		SetTipText(nIndex, (LPCTSTR)NULL);
		continue;
	}
}

BEGIN_MESSAGE_MAP(CTCParameterStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CTCParameterStatusBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCParameterStatusBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCParameterView

IMPLEMENT_DYNCREATE(CTCParameterView, CDisplayTableView)

CTCParameterView::CTCParameterView() : CDisplayTableView(DATABASE_COMPONENT_TCPARAMETER, IDR_TCPARAMETERFRAMEMENU)
{
	return;
}

VOID CTCParameterView::SetTitle(LPCTSTR pszName, LPCTSTR pszTitle)
{
	CDatabaseTCParameter  *pDatabaseTCParameter;

	if ((pDatabaseTCParameter = m_pDatabaseTCParameters[0].GetAt(m_pDatabaseTCParameters[0].Find(pszName))))
	{
		for (pDatabaseTCParameter->SetDescription(pszTitle); !m_szName.Compare(pszName); )
		{
			UpdateTables();
			break;
		}
	}
	m_szName = pszName;
	m_szTitle = pszTitle;
}

BOOL CTCParameterView::GetTitle(CString &szName, CString &szTitle) CONST
{
	CDatabaseTCParameter  *pDatabaseTCParameter;

	for (szName.Empty(), szTitle.Empty(); (pDatabaseTCParameter = m_pDatabaseTCParameters[0].GetAt(m_pDatabaseTCParameters[0].Find(GetName()))); )
	{
		szTitle = pDatabaseTCParameter->GetDescription();
		szName = pDatabaseTCParameter->GetTag();
		return TRUE;
	}
	szName = m_szName;
	szTitle = m_szTitle;
	return !szName.IsEmpty();
}

BOOL CTCParameterView::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	for (SetTablesFonts(plfTitle, plfItems), SetTablesFontColors(nTitleColor, nItemsColor), SetTablesColors(nTitleBackground, nKeysBackground); IsWindow(GetSafeHwnd()); )
	{
		RepositionTables();
		break;
	}
	return TRUE;
}

BOOL CTCParameterView::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	GetTablesFonts(plfTitle, plfItems);
	GetTablesFontColors(nTitleColor, nItemsColor);
	GetTablesColors(nTitleBackground, nKeysBackground);
	return TRUE;
}

VOID CTCParameterView::UpdateTableForms(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nIndex, BOOL bDelete)
{
	UpdateDatabase(pDatabaseTCParameter, (nIndex > 0) ? (nIndex - 1) : nIndex, bDelete);
	UpdateForms(GetParent(), pDatabaseTCParameter, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCParameterView::UpdateTableForms(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCNumCalTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE);
}
VOID CTCParameterView::UpdateTableForms(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCTxtCalTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE);
}
VOID CTCParameterView::UpdateTableForms(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCNumOolTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE);
}
VOID CTCParameterView::UpdateTableForms(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTCTxtOolTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE);
}
VOID CTCParameterView::UpdateTableForms(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	UpdateForms((CTMParameterWnd *)NULL, pDatabaseTMNumCalTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE);
}
VOID CTCParameterView::UpdateTableForms(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	UpdateForms((CTMParameterWnd *)NULL, pDatabaseTMTxtCalTable, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE);
}

CTCParameterWnd *CTCParameterView::GetParent() CONST
{
	return((CTCParameterWnd *)CDisplayTableView::GetParent());
}

BOOL CTCParameterView::CheckPrivilege() CONST
{
	return CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE);
}

BEGIN_MESSAGE_MAP(CTCParameterView, CDisplayTableView)
	//{{AFX_MSG_MAP(CTCParameterView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCParameterView message handlers

int CTCParameterView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayTableView::OnCreate(lpCreateStruct) != -1 && GetDatabase()->CreateTables(this, GetComponent())) ? 0 : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTCParameterWnd

IMPLEMENT_DYNCREATE(CTCParameterWnd, CDisplayWnd)

CTCParameterWnd::CTCParameterWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TCPARAMETER);
}
CTCParameterWnd::CTCParameterWnd(LPCTSTR pszName) : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TCPARAMETER);
	SetName(pszName);
}

BOOL CTCParameterWnd::Create(CMDIFrameWnd *pParentWnd, UINT nShow)
{
	return Create(pParentWnd, GetName(), nShow);
}
BOOL CTCParameterWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszName, UINT nShow)
{
	CRect  rPosition;

	for (SetName(pszName), rPosition = m_rPosition; CDisplayWnd::Create(pParentWnd, STRING(IDS_DISPLAY_TITLE_TCPARAMETER), (nShow == (UINT)-1) ? CRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) : CRect(0, 0, 0, 0), IDR_TCPARAMETERFRAME, (nShow != SW_SHOWMINIMIZED || nShow != SW_SHOWMAXIMIZED) ? (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE) : (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW)); )
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

VOID CTCParameterWnd::SetName(LPCTSTR pszName)
{
	m_wndView.SetName(pszName);
}

CString CTCParameterWnd::GetName() CONST
{
	return m_wndView.GetName();
}

VOID CTCParameterWnd::SetTitle(LPCTSTR pszTitle)
{
	m_wndView.SetTitle(GetName(), pszTitle);
}

CString CTCParameterWnd::GetTitle() CONST
{
	CString  szName;
	CString  szTitle;

	return((m_wndView.GetTitle(szName, szTitle)) ? szTitle : STRING(IDS_DISPLAY_TITLE_TCPARAMETER));
}

BOOL CTCParameterWnd::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	return m_wndView.SetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CTCParameterWnd::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	return m_wndView.GetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CTCParameterWnd::IsModified() CONST
{
	return((m_wndView.Check()) ? m_wndView.IsModified() : FALSE);
}

BOOL CTCParameterWnd::Save(INT nPosition) CONST
{
	UINT  nShowFlags;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	cProfile.DeleteDisplayWindowInfo(nPosition);
	return((GetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && cProfile.SetDisplayWindowType(nPosition, GetType()) && cProfile.SetDisplayWindowName(nPosition, GetName()) && cProfile.SetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, (nShowFlags = (!IsIconic()) ? ((!IsZoomed()) ? SW_SHOWNORMAL : SW_SHOWMAXIMIZED) : SW_SHOWMINIMIZED)) && cProfile.SetTCParametersFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? TRUE : FALSE);
}

INT CTCParameterWnd::Load(INT nPosition)
{
	UINT  nShowFlags;
	CString  szName;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	return((cProfile.GetDisplayWindowName(nPosition, szName) && cProfile.GetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, nShowFlags) && cProfile.GetTCParametersFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && SetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? CTCParameterWnd::Create(GetMainWnd(), szName, nShowFlags) : -1);
}

BOOL CTCParameterWnd::UpdateProperties()
{
	return((m_dlgProperties.DoModal(this) == IDOK) ? TRUE : FALSE);
}

BOOL CTCParameterWnd::IsUpdatingProperties() CONST
{
	return IsWindow(m_dlgProperties.GetSafeHwnd());
}

BOOL CTCParameterWnd::HasProperties() CONST
{
	return TRUE;
}

BOOL CTCParameterWnd::CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST
{
	return m_wndView.CheckTableDropTarget(pszTable, nComponent, point);
}

BOOL CTCParameterWnd::DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point)
{
	return m_wndView.DropOnTableTarget(pszTable, nComponent, point);
}

VOID CTCParameterWnd::UpdateAllPanes(LPCTSTR pszDetails, LPCTSTR pszFlag, LPCTSTR pszType)
{
	m_wndStatusBar.SetPaneText(ID_TCPARAMETER_STATUSBAR_DETAILSPANE, pszDetails);
	m_wndStatusBar.SetPaneText(ID_TCPARAMETER_STATUSBAR_FLAGPANE, pszFlag);
	m_wndStatusBar.SetPaneText(ID_TCPARAMETER_STATUSBAR_TYPEPANE, pszType);
}

BOOL CTCParameterWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
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
				if (PrintJob(cDC, &m_wndView, STRING(IDS_DISPLAY_TITLE_TCPARAMETER), cPrintProfileInfo.GetPrinterName(), rtMargin[0], bMetrics, nFlags))
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
					if (PrintJob(cDC, &m_wndView, STRING(IDS_DISPLAY_TITLE_TCPARAMETER), (LPCTSTR)pDevMode->dmDeviceName, rtMargin[0], bMetrics, nFlags, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : -1, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : -1))
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

VOID CTCParameterWnd::DoSave()
{
	if (m_wndView.DoSave())
	{
		GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_TCPARAMETER);
		return;
	}
}

BOOL CTCParameterWnd::CanSave() CONST
{
	return((m_wndView.CanSave()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

VOID CTCParameterWnd::DoCheck()
{
	m_wndView.DoCheck();
}

BOOL CTCParameterWnd::CanCheck() CONST
{
	return((m_wndView.CanCheck()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

VOID CTCParameterWnd::DoDelete()
{
	CString  szName;
	CString  szTitle;

	for (szName = GetName(), szTitle = GetTitle(); m_wndView.DoDelete(); )
	{
		GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_TCPARAMETER);
		break;
	}
}

BOOL CTCParameterWnd::CanDelete() CONST
{
	return((m_wndView.CanDelete()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

VOID CTCParameterWnd::DoUndo()
{
	m_wndView.DoUndo();
}

BOOL CTCParameterWnd::CanUndo() CONST
{
	return m_wndView.CanUndo();
}

VOID CTCParameterWnd::DoRedo()
{
	m_wndView.DoRedo();
}

BOOL CTCParameterWnd::CanRedo() CONST
{
	return m_wndView.CanRedo();
}

VOID CTCParameterWnd::DoSelectAll()
{
	m_wndView.DoSelectAll();
}

BOOL CTCParameterWnd::CanSelectAll() CONST
{
	return m_wndView.CanSelectAll();
}

VOID CTCParameterWnd::DoCutSel()
{
	m_wndView.DoCutSel();
}

BOOL CTCParameterWnd::CanCutSel() CONST
{
	return m_wndView.CanCutSel();
}

VOID CTCParameterWnd::DoCopySel()
{
	m_wndView.DoCopySel();
}

BOOL CTCParameterWnd::CanCopySel() CONST
{
	return m_wndView.CanCopySel();
}

VOID CTCParameterWnd::DoPasteSel()
{
	m_wndView.DoPasteSel();
}

BOOL CTCParameterWnd::CanPasteSel() CONST
{
	return m_wndView.CanPasteSel();
}

VOID CTCParameterWnd::DoDeleteSel()
{
	m_wndView.DoDeleteSel();
}

BOOL CTCParameterWnd::CanDeleteSel() CONST
{
	return m_wndView.CanDeleteSel();
}

BOOL CTCParameterWnd::CanPrint(UINT nFlags) CONST
{
	return m_wndView.CanPrint(nFlags);
}

VOID CTCParameterWnd::DoClose()
{
	m_wndView.DoClose();
}

BOOL CTCParameterWnd::DoSaveTable()
{
	return m_wndView.DoSaveTable();
}

BOOL CTCParameterWnd::CanSaveTable() CONST
{
	return((m_wndView.CanSaveTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoCheckTable()
{
	return m_wndView.DoCheckTable();
}

BOOL CTCParameterWnd::CanCheckTable() CONST
{
	return((m_wndView.CanCheckTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoDeleteTable()
{
	return m_wndView.DoDeleteTable();
}

BOOL CTCParameterWnd::CanDeleteTable() CONST
{
	return((m_wndView.CanDeleteTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoPrintTable()
{
	return Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE);
}

BOOL CTCParameterWnd::CanPrintTable() CONST
{
	return CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE);
}

BOOL CTCParameterWnd::DoPrintAllTables()
{
	return Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL);
}

BOOL CTCParameterWnd::CanPrintAllTables() CONST
{
	return CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL);
}

BOOL CTCParameterWnd::DoImportTables()
{
	return m_wndView.DoImportTables();
}

BOOL CTCParameterWnd::CanImportTables() CONST
{
	return((m_wndView.CanImportTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoExportTables()
{
	return m_wndView.DoExportTables();
}

BOOL CTCParameterWnd::CanExportTables() CONST
{
	return m_wndView.CanExportTables();
}

BOOL CTCParameterWnd::DoDiscardTables()
{
	return m_wndView.DoDiscardTables();
}

BOOL CTCParameterWnd::CanDiscardTables() CONST
{
	return((m_wndView.CanDiscardTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoDiscardAllTables()
{
	return m_wndView.DoDiscardAllTables();
}

BOOL CTCParameterWnd::CanDiscardAllTables() CONST
{
	return((m_wndView.CanDiscardAllTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoResetTables()
{
	return m_wndView.DoResetTables();
}

BOOL CTCParameterWnd::CanResetTables() CONST
{
	return((m_wndView.CanResetTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoInsertTableRowAbove()
{
	return m_wndView.DoInsertTableRowAbove();
}

BOOL CTCParameterWnd::CanInsertTableRowAbove() CONST
{
	return((m_wndView.CanInsertTableRowAbove()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoInsertTableRowBelow()
{
	return m_wndView.DoInsertTableRowBelow();
}

BOOL CTCParameterWnd::CanInsertTableRowBelow() CONST
{
	return((m_wndView.CanInsertTableRowBelow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoInsertTableColumnBefore()
{
	return m_wndView.DoInsertTableColumnBefore();
}

BOOL CTCParameterWnd::CanInsertTableColumnBefore() CONST
{
	return((m_wndView.CanInsertTableColumnBefore()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoInsertTableColumnAfter()
{
	return m_wndView.DoInsertTableColumnAfter();
}

BOOL CTCParameterWnd::CanInsertTableColumnAfter() CONST
{
	return((m_wndView.CanInsertTableColumnAfter()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoClearTableRow()
{
	return m_wndView.DoClearTableRow();
}

BOOL CTCParameterWnd::CanClearTableRow() CONST
{
	return((m_wndView.CanClearTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoDeleteTableRow()
{
	return m_wndView.DoDeleteTableRow();
}

BOOL CTCParameterWnd::CanDeleteTableRow() CONST
{
	return((m_wndView.CanDeleteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoDeleteTableColumn()
{
	return m_wndView.DoDeleteTableColumn();
}

BOOL CTCParameterWnd::CanDeleteTableColumn() CONST
{
	return((m_wndView.CanDeleteTableColumn()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

BOOL CTCParameterWnd::DoCopyTableRow()
{
	return m_wndView.DoCopyTableRow();
}

BOOL CTCParameterWnd::CanCopyTableRow() CONST
{
	return m_wndView.CanCopyTableRow();
}

BOOL CTCParameterWnd::DoPasteTableRow()
{
	return m_wndView.DoPasteTableRow();
}

BOOL CTCParameterWnd::CanPasteTableRow() CONST
{
	return((m_wndView.CanPasteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE) : FALSE);
}

VOID CTCParameterWnd::GotoTable(ULONGLONG nComponent, LPCTSTR pszName)
{
	m_wndView.GotoTable(nComponent, pszName);
}

VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCParameters &pDatabaseTCParameters)
{
	m_wndView.UpdateTables(pDatabaseTCParameters);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE, pDatabaseTCParameter->GetTag(), bDelete);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE, pDatabaseTCNumCalTable->GetName(), bDelete);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE, pDatabaseTCTxtCalTable->GetName(), bDelete);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE, pDatabaseTCNumOolTable->GetName(), bDelete);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE, pDatabaseTCTxtOolTable->GetName(), bDelete);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCParameterWnd::UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE);
}
VOID CTCParameterWnd::UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCParameterWnd::UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCParameterWnd::UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTCParameterWnd::UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete)
{
	m_wndView.UpdateTables(nComponent, pszName, bDelete);
	m_wndView.ClearUndo();
}
VOID CTCParameterWnd::UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete)
{
	m_wndView.UpdateTables(nComponent, nID, bDelete);
	m_wndView.ClearUndo();
}
VOID CTCParameterWnd::UpdateTables(ULONGLONG nComponent)
{
	m_wndView.UpdateTables(nComponent);
}
VOID CTCParameterWnd::UpdateTables()
{
	m_wndView.UpdateTables();
}

VOID CTCParameterWnd::UpdateTitle()
{
	SetWindowText(STRING(IDS_DISPLAY_TITLE_TCPARAMETER));
}

VOID CTCParameterWnd::UpdateMenus()
{
	GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
}

VOID CTCParameterWnd::UpdateStatusBar()
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

CString CTCParameterWnd::GetPrintDocTitle(LPCTSTR pszTag, UINT nFlags) CONST
{
	CDatabaseTCParameter  *pDatabaseTCParameter;

	return(((pDatabaseTCParameter = (nFlags & DISPLAYTABLEVIEW_PRINT_TABLE) ? GetDatabase()->GetTCParameters()->GetAt(GetDatabase()->GetTCParameters()->Find(pszTag)) : (CDatabaseTCParameter *)NULL) && !pDatabaseTCParameter->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseTCParameter->GetDescription() : pszTag);
}

CString CTCParameterWnd::GetPrintDocInfoTitle() CONST
{
	return STRING(IDS_DISPLAY_TITLE_TCPARAMETER);
}

VOID CTCParameterWnd::AdjustToPrivileges()
{
	if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_TCPARAMETER_CHANGE))
	{
		m_wndView.UnSelectAll();
		return;
	}
}

BEGIN_MESSAGE_MAP(CTCParameterWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CTCParameterWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_TCPARAMETER_STATUSBAR_DETAILSPANE, OnUpdateStatusBarDetailsPane)
	ON_UPDATE_COMMAND_UI(ID_TCPARAMETER_STATUSBAR_FLAGPANE, OnUpdateStatusBarFlagPane)
	ON_UPDATE_COMMAND_UI(ID_TCPARAMETER_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCParameterWnd message handlers

int CTCParameterWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayWnd::OnCreate(lpCreateStruct) != -1 && LoadAccelTable(IDR_TCPARAMETERFRAME)) ? 0 : -1);
}

BOOL CTCParameterWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	CRect  rBar;

	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1))
	{
		m_wndStatusBar.GetWindowRect(rBar);
		return m_wndView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
	}
	return FALSE;
}

void CTCParameterWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rBar;

	m_wndStatusBar.GetWindowRect(rBar);
	m_wndView.MoveWindow(0, 0, cx, cy - rBar.Height());
	CDisplayWnd::OnSize(nType, cx, cy);
}

void CTCParameterWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	if (!bActivate) m_wndView.UnSelectAll();
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CTCParameterWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN) m_wndView.ActivateTable();
	CDisplayWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTCParameterWnd::OnClose()
{
	CHourglassCursor  cCursor;

	DoClose();
	CDisplayWnd::OnClose();
}

void CTCParameterWnd::OnUpdateStatusBarDetailsPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCParameterWnd::OnUpdateStatusBarFlagPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTCParameterWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
