// TMPACKET.CPP : Telemetry Packet Form Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telemetry packet
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
	ID_TMPACKET_STATUSBAR_DETAILSPANE,
	ID_TMPACKET_STATUSBAR_FLAGPANE,
	ID_TMPACKET_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CTMPacketOpenDialog dialog

IMPLEMENT_DYNCREATE(CTMPacketOpenDialog, CLocaleDialog)

CTMPacketOpenDialog::CTMPacketOpenDialog(CWnd *pParentWnd) : CLocaleDialog(CTMPacketOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTMPacketOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTMPacketOpenDialog::Initialize()
{
	m_pDatabaseTMPackets.Copy(GetDatabase()->GetTMPackets());
	return TRUE;
}

VOID CTMPacketOpenDialog::EnumTMPackets()
{
	INT  nPacket;
	INT  nPackets;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	for (nPacket = 0, nPackets = (INT)m_pDatabaseTMPackets.GetSize(); nPacket < nPackets; nPacket++)
	{
		if ((pDatabaseTMPacket = m_pDatabaseTMPackets.GetAt(nPacket)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPACKETOPENDIALOG_DIRECTORYTITLEITEM_TAG); )
				{
					szItem = pDatabaseTMPacket->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPACKETOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTMPacket->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY), nPacket, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY), nPacket, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY), 0);
	GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CTMPacketOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void CTMPacketOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTMPacketOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTMPacketOpenDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTMPackets.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTMPacketOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTMPacketOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TMPACKET_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMPacketOpenDialog message handlers

BOOL CTMPacketOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TMPACKETOPENDIALOG_DIRECTORYTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TMPACKETOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TMPACKET_OPEN_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 7; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumTMPackets();
	GetDlgItem(IDC_TMPACKET_OPEN_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_TMPACKET_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_OPEN_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_OPEN_DATABASE)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY)->SetFocus();
	return FALSE;
}

BOOL CTMPacketOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TMPACKET_OPEN_DIRECTORY)
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

void CTMPacketOpenDialog::OnOK()
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
	CTMPacketWnd  *pTMPacketWnd;
	CHourglassCursor  cCursor;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_TMPACKETOPENDIALOG_DIRECTORYTITLEITEM_TAG))
		{
			szTag = Listview_GetText(GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY)), nColumn);
			continue;
		}
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_TMPACKETOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
		{
			szDescription = Listview_GetText(GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_TMPACKET_OPEN_DIRECTORY)), nColumn);
			continue;
		}
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_TMPACKET)
		{
			if ((pTMPacketWnd = (CTMPacketWnd *)pDisplayWnd)->GetName() == szTag)
			{
				pTMPacketWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		if ((pTMPacketWnd = new CTMPacketWnd(szTag)))
		{
			if (pTMPacketWnd->Create(GetMainWnd()))
			{
				EndDialog(IDOK);
				return;
			}
		}
		szMessage.Format(STRING(IDS_TMPACKET_FAILURE_LOAD), (LPCTSTR)szDescription);
		ShowMessage(szMessage);
	}
	EndDialog(IDOK);
}

void CTMPacketOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTMPacketOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPACKETOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTMPacketOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPACKETOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTMPacketImportDialog dialog

IMPLEMENT_DYNCREATE(CTMPacketImportDialog, CLocaleDialog)

CTMPacketImportDialog::CTMPacketImportDialog(CWnd *pParentWnd) : CLocaleDialog(CTMPacketImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTMPacketImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CTMPacketImportDialog::DoModal(CDatabaseTMPackets &pDatabaseTMPackets)
{
	INT_PTR  nResult;

	for (m_pDatabaseTMPackets.RemoveAll(); (nResult = CLocaleDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMPackets.Copy(&m_pDatabaseTMPackets);
		break;
	}
	return nResult;
}

VOID CTMPacketImportDialog::EnumTMPackets()
{
	INT  nPacket;
	INT  nPackets;
	INT  nColumn;
	INT  nColumns;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szItem;
	CString  szFileName;
	CByteArray  cFileBuffer;
	CFileFindEx  cFileFind;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	SendDlgItemMessage(IDC_TMPACKET_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TMPACKET_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				for (nPacket = 0, nPackets = (m_pDatabaseTMPackets.Unmap(cFileBuffer, FALSE)) ? (INT)m_pDatabaseTMPackets.GetSize() : 0; nPacket < nPackets; nPacket++)
				{
					if ((pDatabaseTMPacket = m_pDatabaseTMPackets.GetAt(nPacket)))
					{
						for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPACKETIMPORTDIALOG_DIRECTORYTITLEITEM_TAG); )
							{
								szItem = pDatabaseTMPacket->GetTag();
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPACKETIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
							{
								szItem = pDatabaseTMPacket->GetDescription();
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_TMPACKET_IMPORT_DIRECTORY), nPacket, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_TMPACKET_IMPORT_DIRECTORY), nPacket, nColumn, szItem);
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
	GetDlgItem(IDC_TMPACKET_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTMPacketImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TMPACKET_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPACKET_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_TMPACKET_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_TMPACKET_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CTMPacketImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTMPacketImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTMPacketImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTMPacketImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTMPacketImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TMPACKET_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_TMPACKET_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TMPACKET_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_TMPACKET_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TMPACKET_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG, OnEditchangeTag)
	ON_EN_CHANGE(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMPacketImportDialog message handlers

BOOL CTMPacketImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TMPACKET_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_TMPACKETIMPORTDIALOG_DIRECTORYTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TMPACKETIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TMPACKET_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG, EM_LIMITTEXT, GetDatabase()->GetTMPacketTagLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TMPACKET_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_TMPACKET_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_TMPACKET_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CTMPacketImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TMPACKET_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_TMPACKET_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM)->EnableWindow();
			}
			else
			{
				CheckDlgButton(IDC_TMPACKET_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_TMPACKET_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CTMPacketImportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TMPACKET_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_TMPACKET_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumTMPackets();
	}
	SendDlgItemMessage(IDC_TMPACKET_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TMPACKET_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketImportDialog::OnDefault()
{
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketImportDialog::OnCustom()
{
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketImportDialog::OnEditchangeFileName()
{
	EnumTMPackets();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketImportDialog::OnEditchangeTag()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketImportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketImportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nPacket;
	INT  nPackets;
	CString  szTag;
	CString  szDescription;
	CPtrArray  pPackets;
	CUIntArray  nPacketIDs;
	CDatabaseTMPacket  *pDatabaseTMPacket[2];
	CDatabaseTMPackets  pDatabaseTMPackets;
	CHourglassCursor  cCursor;

	for (nPacket = 0, nPackets = (INT)SendDlgItemMessage(IDC_TMPACKET_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nPacket < nPackets; nPacket++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_TMPACKET_IMPORT_DIRECTORY), nPacket))
		{
			delete m_pDatabaseTMPackets.GetAt(nPacket);
			m_pDatabaseTMPackets.SetAt(nPacket, NULL);
		}
	}
	for (nPacket = 0, nPackets = (pDatabaseTMPackets.Copy(GetDatabase()->GetTMPackets())) ? nPackets : -1; nPacket < nPackets; nPacket++)
	{
		if ((pDatabaseTMPacket[0] = m_pDatabaseTMPackets.GetAt(nPacket)))
		{
			if (IsDlgButtonChecked(IDC_TMPACKET_IMPORT_TYPE_CUSTOM))
			{
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_TAG)->GetWindowText(szTag);
				GetDlgItem(IDC_TMPACKET_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
				pDatabaseTMPacket[0]->SetDescription(szDescription);
				pDatabaseTMPacket[0]->SetTag(szTag);
			}
			if ((pDatabaseTMPacket[1] = pDatabaseTMPackets.GetAt((nIndex = pDatabaseTMPackets.Find(pDatabaseTMPacket[0]->GetTag())))))
			{
				if (pDatabaseTMPacket[1]->Copy(pDatabaseTMPacket[0]))
				{
					pPackets.Add(pDatabaseTMPacket[1]);
					nPacketIDs.Add(nIndex);
					continue;
				}
				break;
			}
			if ((pDatabaseTMPacket[1] = new CDatabaseTMPacket))
			{
				if (pDatabaseTMPacket[1]->Copy(pDatabaseTMPacket[0]))
				{
					if ((nIndex = pDatabaseTMPackets.Add(pDatabaseTMPacket[1])) >= 0)
					{
						pPackets.Add(pDatabaseTMPacket[1]);
						nPacketIDs.Add(-(nIndex + 1));
						continue;
					}
				}
				delete pDatabaseTMPacket[1];
			}
			break;
		}
		m_pDatabaseTMPackets.RemoveAt(nPacket);
		nPackets--;
		nPacket--;
	}
	for (; nPacket == nPackets; )
	{
		if (GetDatabase()->GetTMPackets()->Copy(&pDatabaseTMPackets))
		{
			for (nItem = 0, nItems = (INT)pPackets.GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMPacket[0] = (CDatabaseTMPacket *)pPackets.GetAt(nItem)))
				{
					if (GetDatabase()->Save(pDatabaseTMPacket[0]))
					{
						nIndex = (INT)nPacketIDs.GetAt(nItem);
						UpdateDatabase(pDatabaseTMPacket[0], nIndex);
						continue;
					}
				}
				break;
			}
			if (nItem == nItems) break;
		}
		nPackets = -1;
		break;
	}
	for (; nPacket != nPackets; )
	{
		ShowMessage((SendDlgItemMessage(IDC_TMPACKET_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_TMPACKETDIRECTORY_IMPORT_FAILURE : SYSTEM_WARNING_TMPACKET_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CTMPacketImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTMPacketImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPACKETIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTMPacketImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPACKETIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTMPacketExportDialog dialog

IMPLEMENT_DYNCREATE(CTMPacketExportDialog, CLocaleDialog)

CTMPacketExportDialog::CTMPacketExportDialog(CWnd *pParentWnd) : CLocaleDialog(CTMPacketExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTMPacketExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CTMPacketExportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

BOOL CTMPacketExportDialog::EnumTMPackets()
{
	INT  nPacket;
	INT  nPackets;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	for (nPacket = 0, nPackets = (m_pDatabaseTMPackets.Copy(GetDatabase()->GetTMPackets())) ? (INT)m_pDatabaseTMPackets.GetSize() : 0; nPacket < nPackets; nPacket++)
	{
		if ((pDatabaseTMPacket = m_pDatabaseTMPackets.GetAt(nPacket)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPACKETEXPORTDIALOG_DIRECTORYTITLEITEM_TAG); )
				{
					szItem = pDatabaseTMPacket->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TMPACKETEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTMPacket->GetDescription();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TMPACKET_EXPORT_DIRECTORY), nPacket, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TMPACKET_EXPORT_DIRECTORY), nPacket, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_TMPACKET_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPACKET_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TMPACKET_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CTMPacketExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TMPACKET_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPACKET_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_TMPACKET_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_TMPACKET_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CTMPacketExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTMPacketExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTMPacketExportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTMPackets.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTMPacketExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTMPacketExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TMPACKET_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_TMPACKET_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_TMPACKET_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_TMPACKET_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_TMPACKET_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG, OnEditchangeTag)
	ON_EN_CHANGE(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMPacketExportDialog message handlers

BOOL CTMPacketExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_TMPACKET_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_TMPACKETEXPORTDIALOG_DIRECTORYTITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_TMPACKETEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TMPACKET_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG, EM_LIMITTEXT, GetDatabase()->GetTMPacketTagLength(), (LPARAM)NULL);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TMPACKET_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumTMPackets())
	{
		CheckDlgButton(IDC_TMPACKET_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_TMPACKET_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TMPACKET_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_TMPACKET_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_TMPACKET_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_TMPACKET_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM)->EnableWindow();
		GetDlgItem(IDC_TMPACKET_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL CTMPacketExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TMPACKET_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_TMPACKET_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM)->EnableWindow();
				CheckDlgButton(IDC_TMPACKET_EXPORT_TYPE_CUSTOM, FALSE);
			}
			else
			{
				CheckDlgButton(IDC_TMPACKET_EXPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_TMPACKET_EXPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CTMPacketExportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_TMPACKET_EXPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_TMPACKET_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_TMPACKET_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TMPACKET_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketExportDialog::OnDefault()
{
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketExportDialog::OnCustom()
{
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketExportDialog::OnEditchangeTag()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketExportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketExportDialog::OnOK()
{
	INT  nPacket;
	INT  nPackets;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szTag;
	CString  szFileName;
	CString  szDescription;
	CByteArray  cFileBuffer;
	CDatabaseTMPacket  *pDatabaseTMPacket;
	CHourglassCursor  cCursor;

	for (nPacket = 0, nPackets = (INT)SendDlgItemMessage(IDC_TMPACKET_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nPacket < nPackets; nPacket++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_TMPACKET_EXPORT_DIRECTORY), nPacket))
		{
			delete m_pDatabaseTMPackets.GetAt(nPacket);
			m_pDatabaseTMPackets.SetAt(nPacket, NULL);
		}
	}
	for (nPacket = 0; nPacket < nPackets; nPacket++)
	{
		if (!m_pDatabaseTMPackets.GetAt(nPacket))
		{
			m_pDatabaseTMPackets.RemoveAt(nPacket);
			nPackets--;
			nPacket--;
		}
	}
	if ((pDatabaseTMPacket = (IsDlgButtonChecked(IDC_TMPACKET_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTMPackets.GetAt(nPacket) : (CDatabaseTMPacket *)NULL))
	{
		GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
		GetDlgItem(IDC_TMPACKET_EXPORT_TYPE_CUSTOM_TAG)->GetWindowText(szTag);
		pDatabaseTMPacket->SetDescription(szDescription);
		pDatabaseTMPacket->SetTag(szTag);
	}
	for (; nPacket == nPackets; )
	{
		if (m_pDatabaseTMPackets.Map(cFileBuffer, FALSE))
		{
			GetDlgItem(IDC_TMPACKET_EXPORT_FILENAME)->GetWindowText(szFileName);
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
		nPackets = -1;
		break;
	}
	for (; nPacket != nPackets; )
	{
		ShowMessage((SendDlgItemMessage(IDC_TMPACKET_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_TMPACKETDIRECTORY_EXPORT_FAILURE : SYSTEM_WARNING_TMPACKET_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CTMPacketExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTMPacketExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPACKETEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTMPacketExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPACKETEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTMPacketPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CTMPacketPropertiesDialog, CLocaleDialog)

CTMPacketPropertiesDialog::CTMPacketPropertiesDialog(CWnd *pParentWnd) : CLocaleDialog(CTMPacketPropertiesDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CTMPacketPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTMPacketPropertiesDialog::Initialize()
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

INT_PTR CTMPacketPropertiesDialog::DoModal(CTMPacketWnd *pParentWnd)
{
	INT_PTR  nResult;

	for (m_pParentWnd = (CWnd *)pParentWnd; (nResult = CLocaleDialog::DoModal()); ) break;
	return nResult;
}

VOID CTMPacketPropertiesDialog::ShowFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_RESETCONTENT); (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_TITLE) && cFontTools.EnumerateFont(m_lfTable[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_ITEMS) && cFontTools.EnumerateFont(m_lfTable[0][1].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_TITLE))
	{
		SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][0])), 0));
		SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][0])), max(SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][0])), 0)));
		SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_ITEMS))
	{
		SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_lfTable[0][1])), 0));
		SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[0][1])), max(SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_lfTable[1][1])), 0)));
		SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]);
	}
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_COLOR_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_COLOR)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTMPacketPropertiesDialog::ShowFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

CTMPacketWnd *CTMPacketPropertiesDialog::GetParent() CONST
{
	return((CTMPacketWnd *)CLocaleDialog::GetParent());
}

BOOL CTMPacketPropertiesDialog::IsModified() CONST
{
	CFontTools  cFontTools;

	return((lstrcmp(m_lfTable[0][0].lfFaceName, m_lfTable[1][0].lfFaceName) || (m_lfTable[0][0].lfHeight != m_lfTable[1][0].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][0]))) || m_lfTable[0][0].lfWeight != m_lfTable[1][0].lfWeight || m_lfTable[0][0].lfItalic != m_lfTable[1][0].lfItalic || lstrcmp(m_lfTable[0][1].lfFaceName, m_lfTable[1][1].lfFaceName) || (m_lfTable[0][1].lfHeight != m_lfTable[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[0][1])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_lfTable[1][1]))) || m_lfTable[0][1].lfWeight != m_lfTable[1][1].lfWeight || m_lfTable[0][1].lfItalic != m_lfTable[1][1].lfItalic || GetDlgItem(IDC_TMPACKET_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]) != GetDlgItem(IDC_TMPACKET_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][0]) || GetDlgItem(IDC_TMPACKET_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]) != GetDlgItem(IDC_TMPACKET_PROPERTIES_COLORS_TITLE)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[1][1]) || GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][0]) != GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][0]) || GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[0][1]) != GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)m_nTableFontColors[1][1])) ? TRUE : FALSE);
}

BOOL CTMPacketPropertiesDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SIZE)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void CTMPacketPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTMPacketPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTMPacketPropertiesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CTMPacketPropertiesDialog)
	ON_WM_PAINT()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TMPACKET_PROPERTIES_FONTS_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_TMPACKET_PROPERTIES_FONTS_ITEMS, OnItemsFont)
	ON_BN_CLICKED(IDC_TMPACKET_PROPERTIES_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TMPACKET_PROPERTIES_FONTS_NAME, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_TMPACKET_PROPERTIES_FONTS_NAME, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, OnSelchangeFontSize)
	ON_CBN_SELCHANGE(IDC_TMPACKET_PROPERTIES_FONTS_COLOR, OnSelchangeFontColor)
	ON_CBN_SELCHANGE(IDC_TMPACKET_PROPERTIES_COLORS_TITLE, OnSelchangeTitleBackgroundColor)
	ON_CBN_SELCHANGE(IDC_TMPACKET_PROPERTIES_COLORS_KEYS, OnSelchangeKeysBackgroundColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMPacketPropertiesDialog message handlers

BOOL CTMPacketPropertiesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	CheckDlgButton(IDC_TMPACKET_PROPERTIES_FONTS_TITLE, TRUE);
	CheckDlgButton(IDC_TMPACKET_PROPERTIES_FONTS_ITEMS, FALSE);
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_NAME, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_COLOR, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_COLOR, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_COLORS_TITLE, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_COLORS_TITLE, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_COLORS_KEYS, CCB_INSERTCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_COLORS_KEYS, CB_GETCOUNT) - 1, (LPARAM)VGA_COLOR_WHITE);
	SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_COLORS_TITLE, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][0]);
	SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_COLORS_KEYS, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nTableColors[0][1]);
	AccessControl(IDC_TMPACKET_PROPERTIES_FONTS_NAME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE));
	AccessControl(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE));
	AccessControl(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE));
	AccessControl(IDC_TMPACKET_PROPERTIES_FONTS_COLOR, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE));
	AccessControl(IDC_TMPACKET_PROPERTIES_COLORS_TITLE, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE));
	AccessControl(IDC_TMPACKET_PROPERTIES_COLORS_KEYS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE));
	GetDlgItem(IDC_TMPACKET_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_TITLE)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_ITEMS)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_NAME)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_PROPERTIES_COLORS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_PROPERTIES_COLORS_TITLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_PROPERTIES_COLORS_TITLE)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_PROPERTIES_COLORS_KEYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TMPACKET_PROPERTIES_COLORS_KEYS)->EnableWindow();
	ShowFontDetails();
	return TRUE;
}

void CTMPacketPropertiesDialog::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_TITLE)) ? &m_lfTable[0][0] : &m_lfTable[0][1]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_TITLE)) ? m_nTableFontColors[0][0] : m_nTableFontColors[0][1]) : GetSysColor(COLOR_GRAYTEXT));
			cDC.FillSolidRect(rSampleText, (SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_SIZE, CB_GETCOUNT) > 0) ? ((IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_TITLE)) ? m_nTableColors[0][0] : GetSysColor(COLOR_3DFACE)) : GetSysColor(COLOR_3DFACE));
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

void CTMPacketPropertiesDialog::OnTitleFont()
{
	SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][0].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CTMPacketPropertiesDialog::OnItemsFont()
{
	SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_lfTable[0][1].lfFaceName));
	ShowFontDetails();
	ShowFontSample();
}

void CTMPacketPropertiesDialog::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketPropertiesDialog::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_TITLE))
	{
		lstrcpy(m_lfTable[0][0].lfFaceName, Combobox_GetText(GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_ITEMS))
	{
		lstrcpy(m_lfTable[0][1].lfFaceName, Combobox_GetText(GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_NAME), (INT)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_NAME, CB_GETCURSEL)));
		ShowFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][0]);
	}
	if (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_lfTable[0][1]);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketPropertiesDialog::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][0].lfWeight, m_lfTable[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_lfTable[0][1].lfWeight, m_lfTable[0][1].lfItalic);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketPropertiesDialog::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_TITLE))
	{
		GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_ITEMS))
	{
		GetDlgItem(IDC_TMPACKET_PROPERTIES_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_lfTable[0][1].lfHeight);
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketPropertiesDialog::OnSelchangeFontColor()
{
	for (; IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_TITLE); )
	{
		m_nTableFontColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	for (; IsDlgButtonChecked(IDC_TMPACKET_PROPERTIES_FONTS_ITEMS); )
	{
		m_nTableFontColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_FONTS_COLOR, CB_GETCURSEL));
		break;
	}
	ShowFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketPropertiesDialog::OnSelchangeTitleBackgroundColor()
{
	for (m_nTableColors[0][0] = (COLORREF)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_COLORS_TITLE, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_COLORS_TITLE, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketPropertiesDialog::OnSelchangeKeysBackgroundColor()
{
	for (m_nTableColors[0][1] = (COLORREF)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_COLORS_KEYS, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TMPACKET_PROPERTIES_COLORS_KEYS, CB_GETCURSEL)); TRUE; )
	{
		ShowFontSample();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTMPacketPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParent()->SetProperties(&m_lfTable[0][0], &m_lfTable[0][1], m_nTableFontColors[0][0], m_nTableFontColors[0][1], m_nTableColors[0][0], m_nTableColors[0][1]);
	EndDialog(IDOK);
}

void CTMPacketPropertiesDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CTMPacketPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPACKETPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTMPacketPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_TMPACKETPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTMPacketStatusBar

IMPLEMENT_DYNCREATE(CTMPacketStatusBar, CMFCStatusBar)

BOOL CTMPacketStatusBar::SetIndicators(CONST UINT *pIDs, INT nCount)
{
	INT  nIndex;
	CString  szText;

	for (Initialize(); CMFCStatusBar::SetIndicators(pIDs, nCount); )
	{
		if ((nIndex = CommandToIndex(ID_TMPACKET_STATUSBAR_DETAILSPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TMPACKET_STATUSBAR_DETAILS), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TMPACKET_STATUSBAR_DETAILSPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(nIndex, szText));
		}
		if ((nIndex = CommandToIndex(ID_TMPACKET_STATUSBAR_FLAGPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TMPACKET_STATUSBAR_FLAG), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TMPACKET_STATUSBAR_FLAGPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_TMPACKET_STATUSBAR_FLAGPANE));
		}
		if ((nIndex = CommandToIndex(ID_TMPACKET_STATUSBAR_TYPEPANE)) >= 0)
		{
			szText.Format(STRING(IDS_TMPACKET_STATUSBAR_TYPE), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_TMPACKET_STATUSBAR_TYPEPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_TMPACKET_STATUSBAR_TYPEPANE));
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTMPacketStatusBar::SetPaneText(UINT nID, LPCTSTR pszText)
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

BOOL CTMPacketStatusBar::GetPaneText(UINT nID, CString &szText) CONST
{
	INT  nIndex;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		szText = CMFCStatusBar::GetPaneText(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString CTMPacketStatusBar::GetPaneText(UINT nID) CONST
{
	CString  szText;

	return((GetPaneText(nID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

INT CTMPacketStatusBar::CalcPaneWidth(INT nIndex) CONST
{
	return CalcPaneWidth(nIndex, CMFCStatusBar::GetPaneText(nIndex));
}
INT CTMPacketStatusBar::CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST
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

VOID CTMPacketStatusBar::Initialize()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = GetCount(); nIndex < nCount; nIndex++)
	{
		SetTipText(nIndex, (LPCTSTR)NULL);
		continue;
	}
}

BEGIN_MESSAGE_MAP(CTMPacketStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CTMPacketStatusBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMPacketStatusBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CTMPacketView

IMPLEMENT_DYNCREATE(CTMPacketView, CDisplayTableView)

CTMPacketView::CTMPacketView() : CDisplayTableView(DATABASE_COMPONENT_TMPACKET, IDR_TMPACKETFRAMEMENU)
{
	return;
}

VOID CTMPacketView::SetTitle(LPCTSTR pszName, LPCTSTR pszTitle)
{
	CDatabaseTMPacket  *pDatabaseTMPacket;

	if ((pDatabaseTMPacket = m_pDatabaseTMPackets[0].GetAt(m_pDatabaseTMPackets[0].Find(pszName))))
	{
		for (pDatabaseTMPacket->SetDescription(pszTitle); !m_szName.Compare(pszName); )
		{
			UpdateTables();
			break;
		}
	}
	m_szName = pszName;
	m_szTitle = pszTitle;
}

BOOL CTMPacketView::GetTitle(CString &szName, CString &szTitle) CONST
{
	CDatabaseTMPacket  *pDatabaseTMPacket;

	for (szName.Empty(), szTitle.Empty(); (pDatabaseTMPacket = m_pDatabaseTMPackets[0].GetAt(m_pDatabaseTMPackets[0].Find(GetName()))); )
	{
		szTitle = pDatabaseTMPacket->GetDescription();
		szName = pDatabaseTMPacket->GetTag();
		return TRUE;
	}
	szName = m_szName;
	szTitle = m_szTitle;
	return !szName.IsEmpty();
}

BOOL CTMPacketView::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	for (SetTablesFonts(plfTitle, plfItems), SetTablesFontColors(nTitleColor, nItemsColor), SetTablesColors(nTitleBackground, nKeysBackground); IsWindow(GetSafeHwnd()); )
	{
		RepositionTables();
		break;
	}
	return TRUE;
}

BOOL CTMPacketView::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	GetTablesFonts(plfTitle, plfItems);
	GetTablesFontColors(nTitleColor, nItemsColor);
	GetTablesColors(nTitleBackground, nKeysBackground);
	return TRUE;
}

VOID CTMPacketView::UpdateTableForms(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nIndex, BOOL bDelete)
{
	UpdateDatabase(pDatabaseTMPacket, (nIndex > 0) ? (nIndex - 1) : nIndex, bDelete);
	UpdateForms(GetParent(), pDatabaseTMPacket, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMPacketView::UpdateTableForms(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTMPacketIdentification, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION);
}
VOID CTMPacketView::UpdateTableForms(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTMPacketIdentificationCriterion, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION);
}
VOID CTMPacketView::UpdateTableForms(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTMPacketHeader, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER);
}
VOID CTMPacketView::UpdateTableForms(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTMPacketStream, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM);
}
VOID CTMPacketView::UpdateTableForms(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	UpdateForms(GetParent(), pDatabaseTMPacketGroup, bDelete);
	UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP);
}

CTMPacketWnd *CTMPacketView::GetParent() CONST
{
	return((CTMPacketWnd *)CDisplayTableView::GetParent());
}

BOOL CTMPacketView::CheckPrivilege() CONST
{
	return CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE);
}

BEGIN_MESSAGE_MAP(CTMPacketView, CDisplayTableView)
	//{{AFX_MSG_MAP(CTMPacketView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMPacketView message handlers

int CTMPacketView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayTableView::OnCreate(lpCreateStruct) != -1 && GetDatabase()->CreateTables(this, GetComponent())) ? 0 : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTMPacketWnd

IMPLEMENT_DYNCREATE(CTMPacketWnd, CDisplayWnd)

CTMPacketWnd::CTMPacketWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TMPACKET);
}
CTMPacketWnd::CTMPacketWnd(LPCTSTR pszName) : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TMPACKET);
	SetName(pszName);
}

BOOL CTMPacketWnd::Create(CMDIFrameWnd *pParentWnd, UINT nShow)
{
	return Create(pParentWnd, GetName(), nShow);
}
BOOL CTMPacketWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszName, UINT nShow)
{
	CRect  rPosition;

	for (SetName(pszName), rPosition = m_rPosition; CDisplayWnd::Create(pParentWnd, STRING(IDS_DISPLAY_TITLE_TMPACKET), (nShow == (UINT)-1) ? CRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) : CRect(0, 0, 0, 0), IDR_TMPACKETFRAME, (nShow != SW_SHOWMINIMIZED || nShow != SW_SHOWMAXIMIZED) ? (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE) : (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW)); )
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

VOID CTMPacketWnd::SetName(LPCTSTR pszName)
{
	m_wndView.SetName(pszName);
}

CString CTMPacketWnd::GetName() CONST
{
	return m_wndView.GetName();
}

VOID CTMPacketWnd::SetTitle(LPCTSTR pszTitle)
{
	m_wndView.SetTitle(GetName(), pszTitle);
}

CString CTMPacketWnd::GetTitle() CONST
{
	CString  szName;
	CString  szTitle;

	return((m_wndView.GetTitle(szName, szTitle)) ? szTitle : STRING(IDS_DISPLAY_TITLE_TMPACKET));
}

BOOL CTMPacketWnd::SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground)
{
	return m_wndView.SetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CTMPacketWnd::GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST
{
	return m_wndView.GetProperties(plfTitle, plfItems, nTitleColor, nItemsColor, nTitleBackground, nKeysBackground);
}

BOOL CTMPacketWnd::IsModified() CONST
{
	return((m_wndView.Check()) ? m_wndView.IsModified() : FALSE);
}

BOOL CTMPacketWnd::Save(INT nPosition) CONST
{
	UINT  nFlags;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	cProfile.DeleteDisplayWindowInfo(nPosition);
	return((GetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && cProfile.SetDisplayWindowType(nPosition, GetType()) && cProfile.SetDisplayWindowName(nPosition, GetName()) && cProfile.SetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, (nFlags = (!IsIconic()) ? ((!IsZoomed()) ? SW_SHOWNORMAL : SW_SHOWMAXIMIZED) : SW_SHOWMINIMIZED)) && cProfile.SetTMPacketsFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? TRUE : FALSE);
}

INT CTMPacketWnd::Load(INT nPosition)
{
	UINT  nFlags;
	CString  szName;
	LOGFONT  lfTable[2];
	COLORREF  nColors[4];
	CProfile  cProfile;

	return((cProfile.GetDisplayWindowName(nPosition, szName) && cProfile.GetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, nFlags) && cProfile.GetTMPacketsFormPropertyInfo(nPosition, &lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3]) && SetProperties(&lfTable[0], &lfTable[1], nColors[0], nColors[1], nColors[2], nColors[3])) ? CTMPacketWnd::Create(GetMainWnd(), szName, nFlags) : -1);
}

BOOL CTMPacketWnd::UpdateProperties()
{
	return((m_dlgProperties.DoModal(this) == IDOK) ? TRUE : FALSE);
}

BOOL CTMPacketWnd::IsUpdatingProperties() CONST
{
	return IsWindow(m_dlgProperties.GetSafeHwnd());
}

BOOL CTMPacketWnd::HasProperties() CONST
{
	return TRUE;
}

BOOL CTMPacketWnd::CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST
{
	return m_wndView.CheckTableDropTarget(pszTable, nComponent, point);
}

BOOL CTMPacketWnd::DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point)
{
	return m_wndView.DropOnTableTarget(pszTable, nComponent, point);
}

VOID CTMPacketWnd::UpdateAllPanes(LPCTSTR pszDetails, LPCTSTR pszFlag, LPCTSTR pszType)
{
	m_wndStatusBar.SetPaneText(ID_TMPACKET_STATUSBAR_DETAILSPANE, pszDetails);
	m_wndStatusBar.SetPaneText(ID_TMPACKET_STATUSBAR_FLAGPANE, pszFlag);
	m_wndStatusBar.SetPaneText(ID_TMPACKET_STATUSBAR_TYPEPANE, pszType);
}

BOOL CTMPacketWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
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
				if (PrintJob(cDC, &m_wndView, STRING(IDS_DISPLAY_TITLE_TMPACKET), cPrintProfileInfo.GetPrinterName(), rtMargin[0], bMetrics, nFlags))
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
					if (PrintJob(cDC, &m_wndView, STRING(IDS_DISPLAY_TITLE_TMPACKET), (LPCTSTR)pDevMode->dmDeviceName, rtMargin[0], bMetrics, nFlags, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : -1, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : -1))
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

VOID CTMPacketWnd::DoSave()
{
	if (m_wndView.DoSave())
	{
		GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_TMPACKET);
		return;
	}
}

BOOL CTMPacketWnd::CanSave() CONST
{
	return((m_wndView.CanSave()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

VOID CTMPacketWnd::DoCheck()
{
	m_wndView.DoCheck();
}

BOOL CTMPacketWnd::CanCheck() CONST
{
	return((m_wndView.CanCheck()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

VOID CTMPacketWnd::DoDelete()
{
	CString  szName;
	CString  szTitle;

	for (szName = GetName(), szTitle = GetTitle(); m_wndView.DoDelete(); )
	{
		GetTopLevelFrame()->RemoveMRUMenuItem(szName, szTitle, DISPLAY_TYPE_TMPACKET);
		break;
	}
}

BOOL CTMPacketWnd::CanDelete() CONST
{
	return((m_wndView.CanDelete()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

VOID CTMPacketWnd::DoUndo()
{
	m_wndView.DoUndo();
}

BOOL CTMPacketWnd::CanUndo() CONST
{
	return m_wndView.CanUndo();
}

VOID CTMPacketWnd::DoRedo()
{
	m_wndView.DoRedo();
}

BOOL CTMPacketWnd::CanRedo() CONST
{
	return m_wndView.CanRedo();
}

VOID CTMPacketWnd::DoSelectAll()
{
	m_wndView.DoSelectAll();
}

BOOL CTMPacketWnd::CanSelectAll() CONST
{
	return m_wndView.CanSelectAll();
}

VOID CTMPacketWnd::DoCutSel()
{
	m_wndView.DoCutSel();
}

BOOL CTMPacketWnd::CanCutSel() CONST
{
	return m_wndView.CanCutSel();
}

VOID CTMPacketWnd::DoCopySel()
{
	m_wndView.DoCopySel();
}

BOOL CTMPacketWnd::CanCopySel() CONST
{
	return m_wndView.CanCopySel();
}

VOID CTMPacketWnd::DoPasteSel()
{
	m_wndView.DoPasteSel();
}

BOOL CTMPacketWnd::CanPasteSel() CONST
{
	return m_wndView.CanPasteSel();
}

VOID CTMPacketWnd::DoDeleteSel()
{
	m_wndView.DoDeleteSel();
}

BOOL CTMPacketWnd::CanDeleteSel() CONST
{
	return m_wndView.CanDeleteSel();
}

BOOL CTMPacketWnd::CanPrint(UINT nFlags) CONST
{
	return m_wndView.CanPrint(nFlags);
}

VOID CTMPacketWnd::DoClose()
{
	m_wndView.DoClose();
}

BOOL CTMPacketWnd::DoSaveTable()
{
	return m_wndView.DoSaveTable();
}

BOOL CTMPacketWnd::CanSaveTable() CONST
{
	return((m_wndView.CanSaveTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoCheckTable()
{
	return m_wndView.DoCheckTable();
}

BOOL CTMPacketWnd::CanCheckTable() CONST
{
	return((m_wndView.CanCheckTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoDeleteTable()
{
	return m_wndView.DoDeleteTable();
}

BOOL CTMPacketWnd::CanDeleteTable() CONST
{
	return((m_wndView.CanDeleteTable()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoPrintTable()
{
	return Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE);
}

BOOL CTMPacketWnd::CanPrintTable() CONST
{
	return CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE);
}

BOOL CTMPacketWnd::DoPrintAllTables()
{
	return Print((PRINTDLG *)NULL, DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL);
}

BOOL CTMPacketWnd::CanPrintAllTables() CONST
{
	return CanPrint(DISPLAYTABLEVIEW_PRINT_SUBTABLE | DISPLAYTABLEVIEW_PRINT_ALL);
}

BOOL CTMPacketWnd::DoImportTables()
{
	return m_wndView.DoImportTables();
}

BOOL CTMPacketWnd::CanImportTables() CONST
{
	return((m_wndView.CanImportTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoExportTables()
{
	return m_wndView.DoExportTables();
}

BOOL CTMPacketWnd::CanExportTables() CONST
{
	return m_wndView.CanExportTables();
}

BOOL CTMPacketWnd::DoDiscardTables()
{
	return m_wndView.DoDiscardTables();
}

BOOL CTMPacketWnd::CanDiscardTables() CONST
{
	return((m_wndView.CanDiscardTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoDiscardAllTables()
{
	return m_wndView.DoDiscardAllTables();
}

BOOL CTMPacketWnd::CanDiscardAllTables() CONST
{
	return((m_wndView.CanDiscardAllTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoResetTables()
{
	return m_wndView.DoResetTables();
}

BOOL CTMPacketWnd::CanResetTables() CONST
{
	return((m_wndView.CanResetTables()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoInsertTableRowAbove()
{
	return m_wndView.DoInsertTableRowAbove();
}

BOOL CTMPacketWnd::CanInsertTableRowAbove() CONST
{
	return((m_wndView.CanInsertTableRowAbove()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoInsertTableRowBelow()
{
	return m_wndView.DoInsertTableRowBelow();
}

BOOL CTMPacketWnd::CanInsertTableRowBelow() CONST
{
	return((m_wndView.CanInsertTableRowBelow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoInsertTableColumnBefore()
{
	return m_wndView.DoInsertTableColumnBefore();
}

BOOL CTMPacketWnd::CanInsertTableColumnBefore() CONST
{
	return((m_wndView.CanInsertTableColumnBefore()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoInsertTableColumnAfter()
{
	return m_wndView.DoInsertTableColumnAfter();
}

BOOL CTMPacketWnd::CanInsertTableColumnAfter() CONST
{
	return((m_wndView.CanInsertTableColumnAfter()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoClearTableRow()
{
	return m_wndView.DoClearTableRow();
}

BOOL CTMPacketWnd::CanClearTableRow() CONST
{
	return((m_wndView.CanClearTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoDeleteTableRow()
{
	return m_wndView.DoDeleteTableRow();
}

BOOL CTMPacketWnd::CanDeleteTableRow() CONST
{
	return((m_wndView.CanDeleteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoDeleteTableColumn()
{
	return m_wndView.DoDeleteTableColumn();
}

BOOL CTMPacketWnd::CanDeleteTableColumn() CONST
{
	return((m_wndView.CanDeleteTableColumn()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

BOOL CTMPacketWnd::DoCopyTableRow()
{
	return m_wndView.DoCopyTableRow();
}

BOOL CTMPacketWnd::CanCopyTableRow() CONST
{
	return m_wndView.CanCopyTableRow();
}

BOOL CTMPacketWnd::DoPasteTableRow()
{
	return m_wndView.DoPasteTableRow();
}

BOOL CTMPacketWnd::CanPasteTableRow() CONST
{
	return((m_wndView.CanPasteTableRow()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE) : FALSE);
}

VOID CTMPacketWnd::GotoTable(ULONGLONG nComponent, LPCTSTR pszName)
{
	m_wndView.GotoTable(nComponent, pszName);
}

VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMPackets &pDatabaseTMPackets)
{
	m_wndView.UpdateTables(pDatabaseTMPackets);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_NONE, pDatabaseTMPacket->GetTag(), bDelete);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION, pDatabaseTMPacketIdentification->GetName(), bDelete);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION, pDatabaseTMPacketIdentificationCriterion->GetName(), bDelete);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER, pDatabaseTMPacketHeader->GetName(), bDelete);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM, pDatabaseTMPacketStream->GetName(), bDelete);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP, pDatabaseTMPacketGroup->GetName(), bDelete);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelet)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMPacketWnd::UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE);
}
VOID CTMPacketWnd::UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_AND | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMPacketWnd::UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_GRD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMPacketWnd::UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete)
{
	m_wndView.UpdateTables(DATABASE_COMPONENT_POD | DATABASE_SUBCOMPONENT_NONE);
}
VOID CTMPacketWnd::UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete)
{
	m_wndView.UpdateTables(nComponent, pszName, bDelete);
	m_wndView.ClearUndo();
}
VOID CTMPacketWnd::UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete)
{
	m_wndView.UpdateTables(nComponent, nID, bDelete);
	m_wndView.ClearUndo();
}
VOID CTMPacketWnd::UpdateTables(ULONGLONG nComponent)
{
	m_wndView.UpdateTables(nComponent);
}
VOID CTMPacketWnd::UpdateTables()
{
	m_wndView.UpdateTables();
}

VOID CTMPacketWnd::UpdateTitle()
{
	SetWindowText(STRING(IDS_DISPLAY_TITLE_TMPACKET));
}

VOID CTMPacketWnd::UpdateMenus()
{
	GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
}

VOID CTMPacketWnd::UpdateStatusBar()
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

CString CTMPacketWnd::GetPrintDocTitle(LPCTSTR pszTag, UINT nFlags) CONST
{
	CDatabaseTMPacket  *pDatabaseTMPacket;

	return(((pDatabaseTMPacket = (nFlags & DISPLAYTABLEVIEW_PRINT_TABLE) ? GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(pszTag)) : (CDatabaseTMPacket *)NULL) && !pDatabaseTMPacket->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseTMPacket->GetDescription() : pszTag);
}

CString CTMPacketWnd::GetPrintDocInfoTitle() CONST
{
	return STRING(IDS_DISPLAY_TITLE_TMPACKET);
}

VOID CTMPacketWnd::AdjustToPrivileges()
{
	if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_TMPACKET_CHANGE))
	{
		m_wndView.UnSelectAll();
		return;
	}
}

BEGIN_MESSAGE_MAP(CTMPacketWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CTMPacketWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MDIACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_UPDATE_COMMAND_UI(ID_TMPACKET_STATUSBAR_DETAILSPANE, OnUpdateStatusBarDetailsPane)
	ON_UPDATE_COMMAND_UI(ID_TMPACKET_STATUSBAR_FLAGPANE, OnUpdateStatusBarFlagPane)
	ON_UPDATE_COMMAND_UI(ID_TMPACKET_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTMPacketWnd message handlers

int CTMPacketWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayWnd::OnCreate(lpCreateStruct) != -1 && LoadAccelTable(IDR_TMPACKETFRAME)) ? 0 : -1);
}

BOOL CTMPacketWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	CRect  rBar;

	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1))
	{
		m_wndStatusBar.GetWindowRect(rBar);
		return m_wndView.Create(this, GetName(), CRect(0, 0, lpcs->cx, lpcs->cy - rBar.Height()));
	}
	return FALSE;
}

void CTMPacketWnd::OnSize(UINT nType, int cx, int cy)
{
	CRect  rBar;

	m_wndStatusBar.GetWindowRect(rBar);
	m_wndView.MoveWindow(0, 0, cx, cy - rBar.Height());
	CDisplayWnd::OnSize(nType, cx, cy);
}

void CTMPacketWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	if (!bActivate) m_wndView.UnSelectAll();
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CTMPacketWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN) m_wndView.ActivateTable();
	CDisplayWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTMPacketWnd::OnClose()
{
	CHourglassCursor  cCursor;

	DoClose();
	CDisplayWnd::OnClose();
}

void CTMPacketWnd::OnUpdateStatusBarDetailsPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTMPacketWnd::OnUpdateStatusBarFlagPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTMPacketWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
