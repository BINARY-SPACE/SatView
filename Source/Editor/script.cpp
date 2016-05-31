// SCRIPT.CPP : Automation Script Display Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the automation script
// display related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2003/06/20 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nStatusBarIndicators[] =
{
	ID_SCRIPT_STATUSBAR_SIZEPANE,
	ID_SCRIPT_STATUSBAR_LINEPANE,
	ID_SCRIPT_STATUSBAR_COLUMNPANE
};



/////////////////////////////////////////////////////////////////////////////
// CScriptDocumentItem

IMPLEMENT_DYNCREATE(CScriptDocumentItem, COleClientItem)

CScriptDocumentItem::CScriptDocumentItem(CScriptDocument *pContainerDoc) : COleClientItem(pContainerDoc)
{
	return;
}

LPDISPATCH CScriptDocumentItem::GetIDispatch() CONST
{
	LPUNKNOWN  pIUnknown;
	LPDISPATCH  pIDispatch;

	return(((pIUnknown = m_lpObject)) ? ((pIUnknown->QueryInterface(IID_IDispatch, (LPVOID *)&pIDispatch) == NOERROR) ? pIDispatch : (LPDISPATCH)NULL) : (LPDISPATCH)NULL);
}

BEGIN_MESSAGE_MAP(CScriptDocumentItem, COleClientItem)
	//{{AFX_MSG_MAP(CScriptDocumentItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptDocumentItem commands


/////////////////////////////////////////////////////////////////////////////
// CScriptDocument

IMPLEMENT_DYNCREATE(CScriptDocument, COleDocument)

CScriptDocument::CScriptDocument() : COleDocument()
{
	m_bAutoDelete = FALSE;
}

CScriptDocument::~CScriptDocument()
{
	DeleteContents();
}

BOOL CScriptDocument::SaveModified()
{
	return TRUE;
}

BOOL CScriptDocument::OnNewDocument()
{
	return COleDocument::OnNewDocument();
}

void CScriptDocument::OnCloseDocument()
{
	DeleteContents();
}

BOOL CScriptDocument::CanCloseFrame(CFrameWnd *pFrame)
{
	return TRUE;
}

VOID CScriptDocument::DeleteContents()
{
	POSITION  lPosition;
	CScriptDocumentItem  *pItem;

	for (lPosition = m_docItemList.GetHeadPosition(); lPosition; )
	{
		if ((pItem = (CScriptDocumentItem *)m_docItemList.GetNext(lPosition)))
		{
			pItem->Release();
			pItem->Delete();
		}
	}
	SetModifiedFlag(FALSE);
	COleDocument::DeleteContents();
}

BEGIN_MESSAGE_MAP(CScriptDocument, COleDocument)
	//{{AFX_MSG_MAP(CScriptDocument)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptDocument serialization

void CScriptDocument::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScriptDocument commands


/////////////////////////////////////////////////////////////////////////////
// CScriptSaveDialog dialog

IMPLEMENT_DYNCREATE(CScriptSaveDialog, CDisplayDialog)

CScriptSaveDialog::CScriptSaveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CScriptSaveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CScriptSaveDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CScriptSaveDialog::IDD);
}

BOOL CScriptSaveDialog::Initialize()
{
	m_pLayouts.Copy(GetDatabase()->GetScripts());
	return TRUE;
}

CScriptWnd *CScriptSaveDialog::GetParentDisplay() CONST
{
	return((CScriptWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CScriptSaveDialog::EnumScripts()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	CString  szItem;
	CStringTools  cStringTools;
	CAutomationScript  *pScript;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(), nDigits = 0; nLayout < nLayouts; nLayout++)
	{
		nDigits = ((pScript = m_pLayouts.GetAt(nLayout))) ? max(pScript->GetName().GetLength(), nDigits) : nDigits;
		continue;
	}
	for (nLayout = 0; nLayout < nLayouts; nLayout++)
	{
		if ((pScript = m_pLayouts.GetAt(nLayout)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTSAVEDIALOG_DIRECTORYTITLEITEM_NUMBER); )
				{
					szItem = cStringTools.ConvertUIntToPaddedString(_ttoi(pScript->GetName()), nDigits);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pScript->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_SCRIPT_SAVE_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_SCRIPT_SAVE_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_SCRIPT_SAVE_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_SAVE_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_SAVE_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_SAVE_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CScriptSaveDialog::FindScript(LPCTSTR pszNumber) CONST
{
	INT  nLayout;
	INT  nLayouts;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(); nLayout < nLayouts; nLayout++)
	{
		if (_ttoi(m_pLayouts.GetAt(nLayout)->GetName()) == _ttoi(pszNumber)) break;
		continue;
	}
	return((nLayout < nLayouts) ? TRUE : FALSE);
}

BOOL CScriptSaveDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_SCRIPT_SAVE_NUMBER)->GetWindowTextLength() > 0 && GetDlgItem(IDC_SCRIPT_SAVE_TITLE)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CScriptSaveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptSaveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CScriptSaveDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CScriptSaveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CScriptSaveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCRIPT_SAVE_HELP, OnHelp)
	ON_EN_CHANGE(IDC_SCRIPT_SAVE_TITLE, OnEditchangeTitle)
	ON_EN_CHANGE(IDC_SCRIPT_SAVE_NUMBER, OnEditchangeNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptSaveDialog message handlers

BOOL CScriptSaveDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_SCRIPT_SAVE_NUMBER)->GetWindowRect(rColumns[0]);
	GetDlgItem(IDC_SCRIPT_SAVE_DIRECTORY)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_SCRIPTSAVEDIALOG_DIRECTORYTITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_SCRIPTSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[0].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[1].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_SCRIPT_SAVE_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumScripts();
	SendDlgItemMessage(IDC_SCRIPT_SAVE_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_SCRIPT_SAVE_NUMBER, EM_LIMITTEXT, cStringTools.ConvertUIntToString(-1).GetLength(), (LPARAM)NULL);
	SendDlgItemMessage(IDC_SCRIPT_SAVE_TITLE, EM_SETSEL, 0, (LPARAM)-1);
	GetDlgItem(IDC_SCRIPT_SAVE_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_SCRIPT_SAVE_NUMBER)->SetWindowText(GetParentDisplay()->GetName());
	GetDlgItem(IDC_SCRIPT_SAVE_TITLE)->SetWindowText(GetParentDisplay()->GetTitle());
	GetDlgItem(IDC_SCRIPT_SAVE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_SAVE_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_SAVE_DATABASE)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_SAVE_TITLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_SAVE_TITLE)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_SAVE_NUMBER_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_SAVE_NUMBER)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_SAVE_TITLE)->SetFocus();
	return FALSE;
}

BOOL CScriptSaveDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nColumn;
	INT  nColumns;
	BOOL  bNumber;
	CString  szNumber;
	CStringTools  cStringTools;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_SCRIPT_SAVE_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (pNotifyListView->uNewState & LVIS_SELECTED)
			{
				for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
				{
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTSAVEDIALOG_DIRECTORYTITLEITEM_NUMBER))
					{
						GetDlgItem(IDC_SCRIPT_SAVE_NUMBER)->SetWindowText(cStringTools.ConvertIntToString(_ttoi(Listview_GetText(GetDlgItem(IDC_SCRIPT_SAVE_DIRECTORY), pNotifyListView->iItem, nColumn))));
						continue;
					}
					if (m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTSAVEDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
					{
						GetDlgItem(IDC_SCRIPT_SAVE_TITLE)->SetWindowText(Listview_GetText(GetDlgItem(IDC_SCRIPT_SAVE_DIRECTORY), pNotifyListView->iItem, nColumn));
						continue;
					}
				}
				GetDlgItem(IDC_SCRIPT_SAVE_NUMBER)->GetWindowText(szNumber);
				GetDlgItem(IDC_SCRIPT_SAVE_COMMENT_STATIC)->ShowWindow(((bNumber = FindScript(szNumber) && GetParentDisplay()->GetName() != szNumber)) ? SW_SHOW : SW_HIDE);
				GetDlgItem(IDC_SCRIPT_SAVE_COMMENT)->ShowWindow((bNumber) ? SW_SHOW : SW_HIDE);
				GetDlgItem(IDC_SCRIPT_SAVE_COMMENT_STATIC)->EnableWindow(bNumber);
				GetDlgItem(IDC_SCRIPT_SAVE_COMMENT)->EnableWindow(bNumber);
			}
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			if (!GetDlgItem(IDC_SCRIPT_SAVE_COMMENT)->IsWindowVisible())
			{
				OnOK();
				return TRUE;
			}
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CScriptSaveDialog::OnEditchangeTitle()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptSaveDialog::OnEditchangeNumber()
{
	BOOL  bNumber;
	CString  szNumber;

	GetDlgItem(IDC_SCRIPT_SAVE_NUMBER)->GetWindowText(szNumber);
	GetDlgItem(IDC_SCRIPT_SAVE_COMMENT_STATIC)->ShowWindow(((bNumber = FindScript(szNumber) && GetParentDisplay()->GetName() != szNumber)) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_SCRIPT_SAVE_COMMENT)->ShowWindow((bNumber) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_SCRIPT_SAVE_COMMENT_STATIC)->EnableWindow(bNumber);
	GetDlgItem(IDC_SCRIPT_SAVE_COMMENT)->EnableWindow(bNumber);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptSaveDialog::OnOK()
{
	CString  szTitle;
	CString  szNumber;
	CStringTools  cStringTools;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_SCRIPT_SAVE_NUMBER)->GetWindowText(szNumber);
	GetDlgItem(IDC_SCRIPT_SAVE_TITLE)->GetWindowText(szTitle);
	GetParentDisplay()->SetName(cStringTools.ConvertIntToString(_ttoi(szNumber)));
	GetParentDisplay()->SetTitle(szTitle);
	CDisplayDialog::OnOK();
}

BOOL CScriptSaveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTSAVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CScriptSaveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTSAVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptOpenDialog dialog

IMPLEMENT_DYNCREATE(CScriptOpenDialog, CLocaleDialog)

CScriptOpenDialog::CScriptOpenDialog(CWnd *pParentWnd) : CLocaleDialog(CScriptOpenDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CScriptOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CScriptOpenDialog::Initialize()
{
	m_pLayouts.Copy(GetDatabase()->GetScripts());
	return TRUE;
}

VOID CScriptOpenDialog::EnumScripts()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	CString  szItem;
	CStringTools  cStringTools;
	CAutomationScript  *pScript;

	for (nLayout = 0, nLayouts = (INT)m_pLayouts.GetSize(), nDigits = 0; nLayout < nLayouts; nLayout++)
	{
		nDigits = ((pScript = m_pLayouts.GetAt(nLayout))) ? max(pScript->GetName().GetLength(), nDigits) : nDigits;
		continue;
	}
	for (nLayout = 0; nLayout < nLayouts; nLayout++)
	{
		if ((pScript = m_pLayouts.GetAt(nLayout)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTOPENDIALOG_DIRECTORYTITLEITEM_NUMBER); )
				{
					szItem = cStringTools.ConvertUIntToPaddedString(_ttoi(pScript->GetName()), nDigits);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pScript->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY), 0);
	GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_OPEN_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CScriptOpenDialog::Check(BOOL bModified) CONST
{
	return((Listview_GetCurText(GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY)) >= 0) ? TRUE : FALSE);
}

void CScriptOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CScriptOpenDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CScriptOpenDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CScriptOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCRIPT_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptOpenDialog message handlers

BOOL CScriptOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_SCRIPTOPENDIALOG_DIRECTORYTITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_SCRIPTOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_SCRIPT_OPEN_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 7; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns.Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumScripts();
	GetDlgItem(IDC_SCRIPT_OPEN_DATABASE)->SetWindowText(GetAccountDatabase());
	GetDlgItem(IDC_SCRIPT_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_OPEN_DATABASE_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_OPEN_DATABASE)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY)->SetFocus();
	return FALSE;
}

BOOL CScriptOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_SCRIPT_OPEN_DIRECTORY)
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

void CScriptOpenDialog::OnOK()
{
	INT  nColumn;
	INT  nColumns;
	INT  nDisplay;
	INT  nDisplays;
	CString  szTitle;
	CString  szNumber;
	CString  szMessage;
	CPtrArray  pDisplays;
	CScriptWnd  *pScriptWnd;
	CDisplayWnd  *pDisplayWnd;
	CHourglassCursor  cCursor;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTOPENDIALOG_DIRECTORYTITLEITEM_NUMBER))
		{
			szNumber = Listview_GetText(GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY)), nColumn);
			continue;
		}
		if (m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTOPENDIALOG_DIRECTORYTITLEITEM_DESCRIPTION))
		{
			szTitle = Listview_GetText(GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY), Listview_GetCurText(GetDlgItem(IDC_SCRIPT_OPEN_DIRECTORY)), nColumn);
			continue;
		}
	}
	for (nDisplay = 0, nDisplays = EnumDisplayWindows(pDisplays); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && pDisplayWnd->GetType() == DISPLAY_TYPE_SCRIPT)
		{
			if ((pScriptWnd = (CScriptWnd *)pDisplayWnd)->GetName() == szNumber)
			{
				pScriptWnd->MDIActivate();
				break;
			}
		}
	}
	if (nDisplay == nDisplays)
	{
		if ((pScriptWnd = new CScriptWnd(szNumber)))
		{
			if (pScriptWnd->Create(GetMainWnd()))
			{
				EndDialog(IDOK);
				return;
			}
		}
		szMessage.Format(STRING(IDS_SCRIPT_FAILURE_LOAD), (LPCTSTR)szTitle);
		ShowMessage(szMessage);
	}
	EndDialog(IDOK);
}

void CScriptOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CScriptOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CScriptOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptImportDialog dialog

IMPLEMENT_DYNCREATE(CScriptImportDialog, CLocaleDialog)

CScriptImportDialog::CScriptImportDialog(CWnd *pParentWnd) : CLocaleDialog(CScriptImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CScriptImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CScriptImportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

VOID CScriptImportDialog::EnumScripts()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szItem;
	CString  szFileName;
	CByteArray  cFileBuffer;
	CFileFindEx  cFileFind;
	CStringTools  cStringTools;
	CAutomationScript  *pScript;

	SendDlgItemMessage(IDC_SCRIPT_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_SCRIPT_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				for (nLayout = 0, nLayouts = (m_pLayouts.Unmap(cFileBuffer)) ? (INT)m_pLayouts.GetSize() : 0, nDigits = 0; nLayout < nLayouts; nLayout++)
				{
					nDigits = ((pScript = m_pLayouts.GetAt(nLayout))) ? max(pScript->GetName().GetLength(), nDigits) : nDigits;
					continue;
				}
				for (nLayout = 0; nLayout < nLayouts; nLayout++)
				{
					if ((pScript = m_pLayouts.GetAt(nLayout)))
					{
						for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
						{
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTIMPORTDIALOG_DIRECTORYTITLEITEM_NUMBER); )
							{
								szItem = cStringTools.ConvertUIntToPaddedString(_ttoi(pScript->GetName()), nDigits);
								break;
							}
							for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
							{
								szItem = pScript->GetTitle();
								break;
							}
							if (!nColumn)
							{
								Listview_InsertText(GetDlgItem(IDC_SCRIPT_IMPORT_DIRECTORY), nLayout, szItem);
								continue;
							}
							Listview_SetText(GetDlgItem(IDC_SCRIPT_IMPORT_DIRECTORY), nLayout, nColumn, szItem);
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
	GetDlgItem(IDC_SCRIPT_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CScriptImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_SCRIPT_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_SCRIPT_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_SCRIPT_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_SCRIPT_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER)->GetWindowTextLength() > 0 && GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))) ? TRUE : FALSE);
}

void CScriptImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CScriptImportDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CScriptImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CScriptImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCRIPT_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_SCRIPT_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_SCRIPT_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_SCRIPT_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_SCRIPT_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER, OnEditchangeNumber)
	ON_EN_CHANGE(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptImportDialog message handlers

BOOL CScriptImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_SCRIPT_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_SCRIPTIMPORTDIALOG_DIRECTORYTITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_SCRIPTIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_SCRIPT_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_SCRIPT_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_SCRIPT_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_SCRIPT_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CScriptImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_SCRIPT_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_SCRIPT_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM)->EnableWindow();
			}
			else
			{
				CheckDlgButton(IDC_SCRIPT_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_SCRIPT_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER)->EnableWindow(FALSE);
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
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

void CScriptImportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_SCRIPT_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_SCRIPT_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumScripts();
	}
	SendDlgItemMessage(IDC_SCRIPT_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_SCRIPT_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptImportDialog::OnDefault()
{
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptImportDialog::OnCustom()
{
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptImportDialog::OnEditchangeFileName()
{
	EnumScripts();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptImportDialog::OnEditchangeNumber()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptImportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptImportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nLayout;
	INT  nLayouts;
	CString  szTitle;
	CString  szNumber;
	CPtrArray  pLayoutIDs;
	CUIntArray  nLayoutIDs;
	CScriptWnd  cScriptWnd;
	CAutomationScript  *pLayout[2];
	CAutomationScripts  pLayouts;
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_SCRIPT_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_SCRIPT_IMPORT_DIRECTORY), nLayout))
		{
			delete m_pLayouts.GetAt(nLayout);
			m_pLayouts.SetAt(nLayout, NULL);
		}
	}
	for (nLayout = 0, nLayouts = (pLayouts.Copy(GetDatabase()->GetScripts())) ? nLayouts : -1; nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pLayouts.GetAt(nLayout)))
		{
			if (IsDlgButtonChecked(IDC_SCRIPT_IMPORT_TYPE_CUSTOM))
			{
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER)->GetWindowText(szNumber);
				GetDlgItem(IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szTitle);
				pLayout[0]->SetName(szNumber);
				pLayout[0]->SetTitle(szTitle);
			}
			if ((pLayout[1] = pLayouts.GetAt((nIndex = pLayouts.Find(pLayout[0]->GetName())))))
			{
				if (pLayout[1]->Copy(pLayout[0]))
				{
					pLayoutIDs.Add(pLayout[1]);
					nLayoutIDs.Add(nIndex);
					continue;
				}
				break;
			}
			if ((pLayout[1] = new CAutomationScript))
			{
				if (pLayout[1]->Copy(pLayout[0]))
				{
					if ((nIndex = pLayouts.Add(pLayout[1])) >= 0)
					{
						pLayoutIDs.Add(pLayout[1]);
						nLayoutIDs.Add(-(nIndex + 1));
						continue;
					}
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
		if (GetDatabase()->GetScripts()->Copy(&pLayouts) && GetDatabase()->Save(DATABASE_COMPONENT_SCRIPT))
		{
			for (nItem = 0, nItems = (INT)pLayoutIDs.GetSize(); nItem < nItems; nItem++)
			{
				if ((pLayout[0] = (CAutomationScript *)pLayoutIDs.GetAt(nItem)))
				{
					cScriptWnd.SetName(pLayout[0]->GetName());
					cScriptWnd.SetTitle(pLayout[0]->GetTitle());
					UpdateDatabase(&cScriptWnd, (INT)nLayoutIDs.GetAt(nItem));
					continue;
				}
			}
			if (nItem == nItems) break;
		}
		nLayouts = -1;
		break;
	}
	for (; nLayout != nLayouts; )
	{
		ShowMessage((SendDlgItemMessage(IDC_SCRIPT_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_AUTOMATIONSCRIPTDIRECTORY_IMPORT_FAILURE : SYSTEM_WARNING_AUTOMATIONSCRIPT_IMPORT_FAILURE);
		break;
	}
	EndDialog(IDOK);
}

void CScriptImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CScriptImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CScriptImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptExportDialog dialog

IMPLEMENT_DYNCREATE(CScriptExportDialog, CLocaleDialog)

CScriptExportDialog::CScriptExportDialog(CWnd *pParentWnd) : CLocaleDialog(CScriptExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CScriptExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT_PTR CScriptExportDialog::DoModal()
{
	return CLocaleDialog::DoModal();
}

BOOL CScriptExportDialog::EnumScripts()
{
	INT  nLayout;
	INT  nLayouts;
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	CString  szItem;
	CStringTools  cStringTools;
	CAutomationScript  *pScript;

	for (nLayout = 0, nLayouts = GetDatabase()->EnumScripts(m_pLayouts, FALSE), nDigits = 0; nLayout < nLayouts; nLayout++)
	{
		nDigits = ((pScript = m_pLayouts.GetAt(nLayout))) ? max(pScript->GetName().GetLength(), nDigits) : nDigits;
		continue;
	}
	for (nLayout = 0; nLayout < nLayouts; nLayout++)
	{
		if ((pScript = m_pLayouts.GetAt(nLayout)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTEXPORTDIALOG_DIRECTORYTITLEITEM_NUMBER); )
				{
					szItem = cStringTools.ConvertUIntToPaddedString(_ttoi(pScript->GetName()), nDigits);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
				{
					szItem = pScript->GetTitle();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_SCRIPT_EXPORT_DIRECTORY), nLayout, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_SCRIPT_EXPORT_DIRECTORY), nLayout, nColumn, szItem);
			}
		}
	}
	GetDlgItem(IDC_SCRIPT_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_SCRIPT_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CScriptExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_SCRIPT_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_SCRIPT_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_SCRIPT_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_SCRIPT_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->GetWindowTextLength() > 0 && GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0) || IsDlgButtonChecked(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE))) ? TRUE : FALSE);
}

void CScriptExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CScriptExportDialog::PostNcDestroy()
{
	m_pLayouts.RemoveAll();
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CScriptExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CScriptExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCRIPT_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_SCRIPT_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_SCRIPT_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE, OnSourceCode)
	ON_BN_CLICKED(IDC_SCRIPT_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_SCRIPT_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER, OnEditchangeNumber)
	ON_EN_CHANGE(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptExportDialog message handlers

BOOL CScriptExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_SCRIPT_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_SCRIPTEXPORTDIALOG_DIRECTORYTITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_SCRIPTEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_SCRIPT_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width(); nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_SCRIPT_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumScripts())
	{
		CheckDlgButton(IDC_SCRIPT_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_SCRIPT_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL CScriptExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_SCRIPT_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_SCRIPT_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) > 0)
			{
				if (SendDlgItemMessage(IDC_SCRIPT_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
				{
					GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM)->EnableWindow();
					GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE)->EnableWindow();
				}
				else
				{
					CheckDlgButton(IDC_SCRIPT_EXPORT_TYPE_DEFAULT, TRUE);
					CheckDlgButton(IDC_SCRIPT_EXPORT_TYPE_CUSTOM, FALSE);
					CheckDlgButton(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE, FALSE);
					GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->SetWindowText(EMPTYSTRING);
					GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
					GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
					GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->EnableWindow(FALSE);
					GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow(FALSE);
					GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
					GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
					GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE)->EnableWindow(FALSE);
				}
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

void CScriptExportDialog::OnBrowse()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_SCRIPT_EXPORT_FILENAME, (!IsDlgButtonChecked(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE)) ? STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION) : STRING(IDS_FILEBROWSEDIALOG_DOCUMENTFILEEXTENSION), (!IsDlgButtonChecked(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE)) ? STRING(IDS_FILEBROWSEDIALOG_DATABASEFILTER) : STRING(IDS_FILEBROWSEDIALOG_DOCUMENTFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_SCRIPT_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_SCRIPT_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_SCRIPT_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptExportDialog::OnDefault()
{
	CheckDlgButton(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE, FALSE);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptExportDialog::OnCustom()
{
	CheckDlgButton(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE, FALSE);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptExportDialog::OnSourceCode()
{
	CheckDlgButton(IDC_SCRIPT_EXPORT_TYPE_CUSTOM, FALSE);
	CheckDlgButton(IDC_SCRIPT_EXPORT_TYPE_DEFAULT, FALSE);
	CheckDlgButton(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE, TRUE);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptExportDialog::OnEditchangeNumber()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptExportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptExportDialog::OnOK()
{
	INT  nLayout;
	INT  nLayouts;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szTitle;
	CString  szNumber;
	CString  szFileName;
	CString  szSourceCode;
	CByteArray  nLayoutsData;
	CAutomationScript  *pLayout;
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_SCRIPT_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_SCRIPT_EXPORT_DIRECTORY), nLayout))
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
	if ((pLayout = (IsDlgButtonChecked(IDC_SCRIPT_EXPORT_TYPE_CUSTOM) || IsDlgButtonChecked(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE)) ? m_pLayouts.GetAt(nLayout - 1) : (CAutomationScript *)NULL))
	{
		for (GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szTitle), GetDlgItem(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER)->GetWindowText(szNumber), szSourceCode = pLayout->GetSourceCode(); IsDlgButtonChecked(IDC_SCRIPT_EXPORT_TYPE_CUSTOM); )
		{
			pLayout->SetName(szNumber);
			pLayout->SetTitle(szTitle);
			break;
		}
	}
	for (; nLayout == nLayouts; )
	{
		if (m_pLayouts.Map(nLayoutsData))
		{
			for (GetDlgItem(IDC_SCRIPT_EXPORT_FILENAME)->GetWindowText(szFileName); IsDlgButtonChecked(IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE); )
			{
				nLayoutsData.SetSize(szSourceCode.GetLength());
#ifndef UNICODE
				CopyMemory(nLayoutsData.GetData(), (LPCTSTR)szSourceCode, nLayoutsData.GetSize());
#else
				WideCharToMultiByte(CP_ACP, 0, szSourceCode, -1, (LPSTR)nLayoutsData.GetData(), (INT)nLayoutsData.GetSize(), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
				break;
			}
			if (cFile.Open(szFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareDenyWrite))
			{
				if (WriteFile(cFile.m_hFile, nLayoutsData.GetData(), (DWORD)nLayoutsData.GetSize(), &dwBytes, (LPOVERLAPPED)NULL))
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
	if (nLayout != nLayouts) ShowMessage((SendDlgItemMessage(IDC_SCRIPT_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 1) ? SYSTEM_WARNING_AUTOMATIONSCRIPTDIRECTORY_EXPORT_FAILURE : SYSTEM_WARNING_AUTOMATIONSCRIPT_IMPORT_FAILURE);
	EndDialog(IDOK);
}

void CScriptExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CScriptExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CScriptExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesDialog dialog

IMPLEMENT_DYNCREATE(CScriptPropertiesDialog, CDisplayDialog)

CScriptPropertiesDialog::CScriptPropertiesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CScriptPropertiesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CScriptPropertiesDialog::Create(CWnd *pParentWnd, CTMParameters *pTMParameters)
{
	INT  nResult;

	for (m_pTMParameters = pTMParameters, m_bTMParameters = FALSE; (nResult = CDisplayDialog::Create(pParentWnd, CScriptPropertiesDialog::IDD)) == IDOK; ) break;
	return nResult;
}

BOOL CScriptPropertiesDialog::Initialize()
{
	for (GetParentDisplay()->GetScript(&m_cScript[0]); m_cScript[0].GetType() == AUTOMATIONSCRIPT_TYPE_NONE; )
	{
		m_cScript[0].SetType(AUTOMATIONSCRIPT_TYPE_EXCEL);
		break;
	}
	return m_cScript[1].Copy(&m_cScript[0]);
}

CScriptWnd *CScriptPropertiesDialog::GetParentDisplay() CONST
{
	return((CScriptWnd *)CDisplayDialog::GetParentDisplay());
}

VOID CScriptPropertiesDialog::ShowProperties()
{
	UINT  nType;
	CString  szName;

	szName.Format(STRING(IDS_SCRIPTPROPERTIESDIALOG_NAME_FORMAT), (LPCTSTR)m_cScript[0].GetTitle(), (LPCTSTR)m_cScript[0].GetName());
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_TYPE_EXCEL, ((nType = m_cScript[0].GetType()) == AUTOMATIONSCRIPT_TYPE_EXCEL) ? TRUE : FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_TYPE_WORD, (nType == AUTOMATIONSCRIPT_TYPE_WORD) ? TRUE : FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_TYPE_ACCESS, (nType == AUTOMATIONSCRIPT_TYPE_ACCESS) ? TRUE : FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_TYPE_OUTLOOK, (nType == AUTOMATIONSCRIPT_TYPE_OUTLOOK) ? TRUE : FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_TYPE_POWERPOINT, (nType == AUTOMATIONSCRIPT_TYPE_POWERPOINT) ? TRUE : FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_TYPE_OTHER, (nType == AUTOMATIONSCRIPT_TYPE_OTHER) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_NAME)->SetWindowText((!m_cScript[0].GetTitle().IsEmpty()) ? szName : m_cScript[0].GetName());
	GetDlgItem(IDC_SCRIPT_PROPERTIES_INPUTFILENAME)->SetWindowText(m_cScript[0].GetInputFileName());
	GetDlgItem(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME)->SetWindowText(m_cScript[0].GetOutputFileName());
	GetDlgItem(IDC_SCRIPT_PROPERTIES_DETAILS)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_NAME)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_TYPE_EXCEL)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_TYPE_WORD)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_TYPE_ACCESS)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_TYPE_OUTLOOK)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_TYPE_POWERPOINT)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_TYPE_OTHER)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_INPUTFILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_INPUTFILENAME)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_INPUTFILENAME_BROWSE)->EnableWindow(CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
	GetDlgItem(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME_BROWSE)->EnableWindow(CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS)->EnableWindow();
}

BOOL CScriptPropertiesDialog::IsModified() CONST
{
	return((!m_cScript[0].Compare(&m_cScript[1]) || m_bTMParameters) ? TRUE : FALSE);
}

void CScriptPropertiesDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptPropertiesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptPropertiesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CScriptPropertiesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_TYPE_EXCEL, OnTypeExcel)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_TYPE_WORD, OnTypeWord)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_TYPE_ACCESS, OnTypeAccess)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_TYPE_OUTLOOK, OnTypeOutlook)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_TYPE_POWERPOINT, OnTypePowerPoint)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_TYPE_OTHER, OnTypeOther)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_INPUTFILENAME_BROWSE, OnBrowseInputFileName)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME_BROWSE, OnBrowseOutputFileName)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS, OnParameters)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_HELP, OnHelp)
	ON_EN_CHANGE(IDC_SCRIPT_PROPERTIES_INPUTFILENAME, OnEditchangeInputFileName)
	ON_EN_CHANGE(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME, OnEditchangeOutputFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesDialog message handlers

BOOL CScriptPropertiesDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	AccessControl(IDC_SCRIPT_PROPERTIES_TYPE_EXCEL, CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
	AccessControl(IDC_SCRIPT_PROPERTIES_TYPE_WORD, CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
	AccessControl(IDC_SCRIPT_PROPERTIES_TYPE_ACCESS, CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
	AccessControl(IDC_SCRIPT_PROPERTIES_TYPE_OUTLOOK, CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
	AccessControl(IDC_SCRIPT_PROPERTIES_TYPE_POWERPOINT, CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
	AccessControl(IDC_SCRIPT_PROPERTIES_TYPE_OTHER, CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
	AccessControl(IDC_SCRIPT_PROPERTIES_INPUTFILENAME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
	AccessControl(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME, CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
	ShowProperties();
	return TRUE;
}

void CScriptPropertiesDialog::OnTypeExcel()
{
	m_cScript[0].SetType(AUTOMATIONSCRIPT_TYPE_EXCEL);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnTypeWord()
{
	m_cScript[0].SetType(AUTOMATIONSCRIPT_TYPE_WORD);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnTypeAccess()
{
	m_cScript[0].SetType(AUTOMATIONSCRIPT_TYPE_ACCESS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnTypeOutlook()
{
	m_cScript[0].SetType(AUTOMATIONSCRIPT_TYPE_OUTLOOK);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnTypePowerPoint()
{
	m_cScript[0].SetType(AUTOMATIONSCRIPT_TYPE_POWERPOINT);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnTypeOther()
{
	m_cScript[0].SetType(AUTOMATIONSCRIPT_TYPE_OTHER);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnBrowseInputFileName()
{
	CString  szFileName;
	CFileBrowseDialog  cFileBrowseDialog(this, m_cScript[0].GetInputFileName(), (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_EXCEL)) ? STRING(IDS_FILEBROWSEDIALOG_EXCELFILEEXTENSION) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_WORD)) ? STRING(IDS_FILEBROWSEDIALOG_WORDFILEEXTENSION) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_ACCESS)) ? STRING(IDS_FILEBROWSEDIALOG_ACCESSFILEEXTENSION) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_OUTLOOK)) ? STRING(IDS_FILEBROWSEDIALOG_OUTLOOKFILEEXTENSION) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_POWERPOINT)) ? STRING(IDS_FILEBROWSEDIALOG_POWERPOINTFILEEXTENSION) : STRING(IDS_FILEBROWSEDIALOG_DOCUMENTFILEEXTENSION))))), (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_EXCEL)) ? STRING(IDS_FILEBROWSEDIALOG_EXCELFILEFILTER) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_WORD)) ? STRING(IDS_FILEBROWSEDIALOG_WORDFILEFILTER) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_ACCESS)) ? STRING(IDS_FILEBROWSEDIALOG_ACCESSFILEFILTER) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_OUTLOOK)) ? STRING(IDS_FILEBROWSEDIALOG_OUTLOOKFILEFILTER) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_POWERPOINT)) ? STRING(IDS_FILEBROWSEDIALOG_POWERPOINTFILEFILTER) : STRING(IDS_FILEBROWSEDIALOG_DOCUMENTFILTER))))));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		m_cScript[0].SetInputFileName((szFileName = cFileBrowseDialog.GetPathName()));
		GetDlgItem(IDC_SCRIPT_PROPERTIES_INPUTFILENAME)->SetWindowText(szFileName);
	}
	SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_INPUTFILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_INPUTFILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnBrowseOutputFileName()
{
	CString  szFileName;
	CFileBrowseDialog  cFileBrowseDialog(this, m_cScript[0].GetOutputFileName(), (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_EXCEL)) ? STRING(IDS_FILEBROWSEDIALOG_EXCELFILEEXTENSION) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_WORD)) ? STRING(IDS_FILEBROWSEDIALOG_WORDFILEEXTENSION) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_ACCESS)) ? STRING(IDS_FILEBROWSEDIALOG_ACCESSFILEEXTENSION) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_OUTLOOK)) ? STRING(IDS_FILEBROWSEDIALOG_OUTLOOKFILEEXTENSION) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_POWERPOINT)) ? STRING(IDS_FILEBROWSEDIALOG_POWERPOINTFILEEXTENSION) : STRING(IDS_FILEBROWSEDIALOG_DOCUMENTFILEEXTENSION))))), (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_EXCEL)) ? STRING(IDS_FILEBROWSEDIALOG_EXCELFILEFILTER) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_WORD)) ? STRING(IDS_FILEBROWSEDIALOG_WORDFILEFILTER) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_ACCESS)) ? STRING(IDS_FILEBROWSEDIALOG_ACCESSFILEFILTER) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_OUTLOOK)) ? STRING(IDS_FILEBROWSEDIALOG_OUTLOOKFILEFILTER) : ((IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_TYPE_POWERPOINT)) ? STRING(IDS_FILEBROWSEDIALOG_POWERPOINTFILEFILTER) : STRING(IDS_FILEBROWSEDIALOG_DOCUMENTFILTER))))));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		m_cScript[0].SetOutputFileName((szFileName = cFileBrowseDialog.GetPathName()));
		GetDlgItem(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME)->SetWindowText(szFileName);
	}
	SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnParameters()
{
	CScriptPropertiesParametersDialog  cTestParameters(this);

	m_bTMParameters |= (cTestParameters.DoModal(m_pTMParameters) == IDOK) ? TRUE : FALSE;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnEditchangeInputFileName()
{
	CString  szFileName;

	GetDlgItem(IDC_SCRIPT_PROPERTIES_INPUTFILENAME)->GetWindowText(szFileName);
	m_cScript[0].SetInputFileName(szFileName);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnEditchangeOutputFileName()
{
	CString  szFileName;

	GetDlgItem(IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME)->GetWindowText(szFileName);
	m_cScript[0].SetOutputFileName(szFileName);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParentDisplay()->SetScript(&m_cScript[0]);
	CDisplayDialog::OnOK();
}

BOOL CScriptPropertiesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CScriptPropertiesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTPROPERTIESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParametersDialog dialog

IMPLEMENT_DYNCREATE(CScriptPropertiesParametersDialog, CLocaleDialog)

CScriptPropertiesParametersDialog::CScriptPropertiesParametersDialog(CWnd *pParentWnd) : CLocaleDialog(CScriptPropertiesParametersDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CScriptPropertiesParametersDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CScriptPropertiesParametersDialog::DoModal(CTMParameters *pTMParameters)
{
	INT  nParameter;
	INT  nParameters;
	UINT  nStatus;
	ULONGLONG  nValue;
	CTMParameter  *pTMParameter[2];

	for (nParameter = 0, nParameters = (INT)pTMParameters->GetSize(), m_pTMParameters[0].RemoveAll(), m_pTMParameters[1].RemoveAll(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter[0] = pTMParameters->GetAt(nParameter)) && pTMParameter[0]->GetLastUpdateTMUnit() == STRING(IDS_TMUNIT_INTERACTIVE) && pTMParameter[0]->GetRawValue(0, nValue, nStatus))
		{
			if ((pTMParameter[1] = new CTMParameter))
			{
				pTMParameter[1]->Copy(pTMParameter[0]);
				if (m_pTMParameters[0].Add(pTMParameter[1]) >= 0) continue;
				delete pTMParameter[1];
			}
		}
	}
	for (m_pTMParameters[1].Copy(&m_pTMParameters[0]); CLocaleDialog::DoModal() == IDOK; )
	{
		for (nParameter = 0, nParameters = (INT)m_pTMParameters[0].GetSize(); nParameter < nParameters; nParameter = nParameter + 1)
		{
			if ((pTMParameter[1] = ((pTMParameter[0] = m_pTMParameters[0].GetAt(nParameter))) ? pTMParameters->GetAt(pTMParameters->Find(pTMParameter[0]->GetTag())) : (CTMParameter *)NULL))
			{
				pTMParameter[1]->Copy(pTMParameter[0]);
				continue;
			}
		}
		for (nParameter = 0, nParameters = (INT)m_pTMParameters[1].GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pTMParameter[0] = m_pTMParameters[1].GetAt(nParameter)) && m_pTMParameters[0].Find(pTMParameter[0]->GetTag()) < 0)
			{
				if ((pTMParameter[1] = pTMParameters->GetAt(pTMParameters->Find(pTMParameter[0]->GetTag()))))
				{
					pTMParameter[1]->Reset();
					continue;
				}
			}
		}
		return IDOK;
	}
	return IDCANCEL;
}

BOOL CScriptPropertiesParametersDialog::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
		{
			szParameter.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TAG_FORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)((pDatabaseTMParameter->GetDescription().IsEmpty()) ? (LPCTSTR)pDatabaseTMParameter->GetTag() : (LPCTSTR)szParameter));
		}
	}
	return((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

BOOL CScriptPropertiesParametersDialog::EnumCalibrationTables()
{
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt((INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, CB_GETCURSEL))) == (CDatabaseTMParameter *)NULL)
	{
		SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_RESETCONTENT);
		SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_RESETCONTENT);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE)->EnableWindow(FALSE);
		return FALSE;
	}
	return EnumCalibrationTables(pDatabaseTMParameter);
}
BOOL CScriptPropertiesParametersDialog::EnumCalibrationTables(CONST CDatabaseTMParameter *pDatabaseTMParameter)
{
	INT  nTable;
	INT  nTables;
	CString  szTable;
	CStringArray  szTables[2];
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	for (nTable = 0, nTables = pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1]), SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_RESETCONTENT); nTable < nTables; nTable++)
	{
		if ((pDatabaseTMNumCalTable = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTMNumCalTables()->GetAt(GetDatabase()->GetTMNumCalTables()->Find(szTables[0].GetAt(nTable))) : (CDatabaseTMNumCalTable *)NULL))
		{
			szTable.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TABLE_FORMAT), (LPCTSTR)pDatabaseTMNumCalTable->GetName(), (LPCTSTR)pDatabaseTMNumCalTable->GetDescription());
			SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
			continue;
		}
		if ((pDatabaseTMTxtCalTable = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTMTxtCalTables()->GetAt(GetDatabase()->GetTMTxtCalTables()->Find(szTables[0].GetAt(nTable))) : (CDatabaseTMTxtCalTable *)NULL))
		{
			szTable.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TABLE_FORMAT), (LPCTSTR)pDatabaseTMTxtCalTable->GetName(), (LPCTSTR)pDatabaseTMTxtCalTable->GetDescription());
			SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable);
			continue;
		}
	}
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CScriptPropertiesParametersDialog::EnumCalibrationTableValues()
{
	INT  nIndex;
	INT  nPoint;
	INT  nPoints;
	double  fX[2];
	CString  szValue;
	CString  szPoint;
	CString  szRange;
	CStringArray  szTables[2];
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTMTxtCalPoint  *pDatabaseTMTxtCalPoint;

	SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_RESETCONTENT);
	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt((INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, CB_GETCURSEL))))
	{
		for (nPoint = 0, nPoints = ((pDatabaseTMTxtCalTable = ((((pTMParameter = m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(pDatabaseTMParameter->GetTag()))) && (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)) || (m_pTMParameters[0].Find(pDatabaseTMParameter->GetTag()) < 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS))) && (nIndex = (INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCURSEL)) >= 0 && nIndex < pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1])) ? GetDatabase()->GetTMTxtCalTables()->GetAt(GetDatabase()->GetTMTxtCalTables()->Find(szTables[0].GetAt(nIndex))) : (CDatabaseTMTxtCalTable *)NULL)) ? (INT)pDatabaseTMTxtCalTable->GetSize() : 0; nPoint < nPoints; nPoint++)
		{
			if ((pDatabaseTMTxtCalPoint = pDatabaseTMTxtCalTable->GetAt(nPoint)))
			{
				if (pDatabaseTMTxtCalPoint->GetPoint(fX[0], szValue))
				{
					szPoint.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_POINTVALUE_FORMAT), (LPCTSTR)szValue, (LONGLONG)fX[0]);
					SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szPoint);
					continue;
				}
				if (pDatabaseTMTxtCalPoint->GetRange(fX[0], fX[1], szValue))
				{
					szPoint.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_RANGEVALUE_FORMAT), (LPCTSTR)szValue, (LONGLONG)fX[0], (LONGLONG)fX[1]);
					SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szRange);
					continue;
				}
			}
		}
	}
	return((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CScriptPropertiesParametersDialog::ShowProperties(INT nIndex)
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	UINT  nStatus;
	CString  szItem;
	CString  szValue;
	ULONGLONG  nValue;
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = (nIndex >= 0) ? nIndex : 0, nParameters = (INT)m_pTMParameters[0].GetSize(); nParameter < nParameters; nParameter = (nIndex < 0) ? (nParameter + 1) : nParameters)
	{
		if ((pTMParameter = m_pTMParameters[0].GetAt(nParameter)) != (CTMParameter *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG); )
				{
					szItem = pTMParameter->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_DESCRIPTION); )
				{
					szItem = ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())))) ? pDatabaseTMParameter->GetDescription() : EMPTYSTRING;
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TYPE))
				{
					szItem = (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TYPE_RAW) : EMPTYSTRING;
					szItem = (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TYPE_NUMERICAL) : szItem;
					szItem = (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TYPE_STATUS) : szItem;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_CODING))
				{
					szItem = (pTMParameter->GetAttributes() & TMPARAMETER_CODING_BITPATTERN) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_CODING_BITPATTERN) : EMPTYSTRING;
					szItem = (pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_CODING_SIGNEDINTEGER) : szItem;
					szItem = (pTMParameter->GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_CODING_UNSIGNEDINTEGER) : szItem;
					szItem = (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_CODING_FLOATINGPOINT) : szItem;
					szItem = ((pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0) ? (((pTMParameter->GetAttributes() & TMPARAMETER_RADIX_DECIMAL) || (pTMParameter->GetAttributes() & (TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) == 0) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_CODING_UNSIGNEDINTEGER) : STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_CODING_BITPATTERN)) : szItem;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_VALUE); )
				{
					szItem = (pTMParameter->GetValueAsText(GetDatabase(), 0, szValue)) ? szValue : EMPTYSTRING;
					break;
				}
				for (nStatus = TMPARAMETER_STATUS_NONE; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_STATUS); )
				{
					szItem = (pTMParameter->GetRawValue(0, nValue, nStatus) && (nStatus & TMPARAMETER_STATUS_NOLIMIT)) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_STATUS_NOLIMIT) : EMPTYSTRING;
					szItem = (nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_STATUS_SOFTLIMIT) : szItem;
					szItem = (nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_STATUS_HARDLIMIT) : szItem;
					szItem = (nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_STATUS_DELTALIMIT) : szItem;
					szItem = (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_STATUS_CONSISTENCYLIMIT) : szItem;
					szItem += (nStatus & TMPARAMETER_STATUS_VALID) ? (CString(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_STATUS_DELIMITER)) + STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_STATUS_VALID)) : EMPTYSTRING;
					szItem += (nStatus & TMPARAMETER_STATUS_INVALID) ? (CString(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_STATUS_DELIMITER)) + STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_STATUS_INVALID)) : EMPTYSTRING;
					break;
				}
				if (m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_QUALITY))
				{
					szItem = (pTMParameter->GetRawValue(0, nValue, nStatus) && (nStatus & TMPARAMETER_STATUS_GOOD)) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_QUALITY_GOOD) : EMPTYSTRING;
					szItem = (nStatus & TMPARAMETER_STATUS_BAD) ? STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_QUALITY_BAD) : szItem;
				}
				if (!nColumn  &&  nParameter >= SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST, LVM_GETITEMCOUNT))
				{
					Listview_InsertText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nParameter, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nParameter, nColumn, szItem);
			}
		}
	}
	if (nIndex < 0)
	{
		while (nParameters < SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST, LVM_GETITEMCOUNT))
		{
			SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST, LVM_DELETEITEM, nParameters);
			continue;
		}
		if (SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST, LVM_GETITEMCOUNT) > 0)
		{
			Listview_SetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), 0);
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST_STATIC)->EnableWindow();
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST)->EnableWindow();
			ShowParameterDetails();
			return;
		}
		SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST, LVM_DELETEALLITEMS);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST)->EnableWindow(FALSE);
		ShowParameterDetails();
	}
}

VOID CScriptPropertiesParametersDialog::ShowParameterDetails()
{
	INT  nIndex;
	INT  nTable;
	INT  nTables;
	UINT  nStatus;
	CString  szValue;
	CString  szTable;
	CString  szParameter;
	ULONGLONG  nValue;
	CStringArray  szTables[2];
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if ((pDatabaseTMParameter = ((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL)) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())) : (CDatabaseTMParameter *)NULL))
	{
		for (nTable = 0, nTables = (pTMParameter->GetRawValue(SCRIPTPROPERTIESPARAMETERS_DEFAULTSAMPLE, nValue, nStatus, szTable)) ? pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1]) : 0, szParameter.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TAG_FORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription()), SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szParameter = (pDatabaseTMParameter->GetDescription().IsEmpty()) ? pDatabaseTMParameter->GetTag() : szParameter))), EnumCalibrationTables(pDatabaseTMParameter); nTable < nTables; nTable++)
		{
			if (szTable == szTables[0].GetAt(nTable)) break;
			continue;
		}
		if (nTable < nTables)
		{
			SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_SETCURSEL, (pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) ? nTable : -1);
			EnumCalibrationTableValues();
		}
		Spinbox_SetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE), SCRIPTPROPERTIESPARAMETERS_DEFAULTSAMPLE);
		AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW, (SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST, (Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)) < 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW, ((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT, (nStatus & TMPARAMETER_STATUS_NOLIMIT) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT, (nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT, (nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT, (nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT, (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_VALID, (nStatus & TMPARAMETER_STATUS_VALID) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_INVALID, (nStatus & TMPARAMETER_STATUS_INVALID) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_GOOD, (nStatus & TMPARAMETER_STATUS_GOOD) ? TRUE : FALSE);
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_BAD, (nStatus & TMPARAMETER_STATUS_BAD) ? TRUE : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMARK)->ShowWindow((pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMARK)->EnableWindow((pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) ? TRUE : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetWindowText((pTMParameter->GetValueAsText(GetDatabase(), (INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)), szValue, IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST))) ? szValue : EMPTYSTRING);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? !IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW) : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? !IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW) : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST)->EnableWindow((Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)) > 0 && pTMParameter->GetValueCount() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVE)->EnableWindow(CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVEALL)->EnableWindow(CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
		return;
	}
	for (EnumCalibrationTables(); SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_SETCURSEL) >= 0; )
	{
		EnumCalibrationTableValues();
		break;
	}
	Spinbox_SetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE), SCRIPTPROPERTIESPARAMETERS_DEFAULTSAMPLE);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW, (SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW, (!SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT)) ? TRUE : FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT, TRUE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_VALID, TRUE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_INVALID, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_GOOD, TRUE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_BAD, FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMARK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMARK)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVEALL)->EnableWindow(FALSE);
}

BOOL CScriptPropertiesParametersDialog::UpdateParameter(CTMParameter *pTMParameter) CONST
{
	CString  szValue;

	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->GetWindowText(szValue);
	return UpdateParameter(pTMParameter, szValue);
}
BOOL CScriptPropertiesParametersDialog::UpdateParameter(CTMParameter *pTMParameter, LPCTSTR pszValue) CONST
{
	INT  nIndex;
	BYTE  nStatus;
	CString  szTable;
	CStringArray  szTables[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;

	szTable = ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag()))) && (nIndex = (INT)GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE)->SendMessage(CB_GETCURSEL)) >= 0 && nIndex < pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1])) ? szTables[0].GetAt(nIndex) : EMPTYSTRING;
	nStatus = (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT)) ? TMPARAMETER_STATUS_NOLIMIT : TMPARAMETER_STATUS_NONE;
	nStatus = (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT)) ? TMPARAMETER_STATUS_SOFTLIMIT : nStatus;
	nStatus = (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT)) ? TMPARAMETER_STATUS_HARDLIMIT : nStatus;
	nStatus = (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT)) ? TMPARAMETER_STATUS_DELTALIMIT : nStatus;
	nStatus = (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT)) ? TMPARAMETER_STATUS_CONSISTENCYLIMIT : nStatus;
	nStatus |= (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_VALID)) ? TMPARAMETER_STATUS_VALID : 0;
	nStatus |= (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_INVALID)) ? TMPARAMETER_STATUS_INVALID : 0;
	nStatus |= (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_GOOD)) ? TMPARAMETER_STATUS_GOOD : 0;
	nStatus |= (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_BAD)) ? TMPARAMETER_STATUS_BAD : 0;
	return UpdateParameter(pTMParameter, pszValue, (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST)) ? -(INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)) : (INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)), nStatus, szTable);
}
BOOL CScriptPropertiesParametersDialog::UpdateParameter(CTMParameter *pTMParameter, LPCTSTR pszValue, INT nSample, UINT nStatus, LPCTSTR pszTable) CONST
{
	INT  nPoint;
	INT  nPoints;
	double  fX[2];
	double  fValue;
	double  fRawValue;
	CString  szValue;
	CString  szPoint;
	CString  szRange;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMNumCalPoint  *pDatabaseTMNumCalPoint[2];
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTMTxtCalPoint  *pDatabaseTMTxtCalPoint;

	if (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW))
	{
		pTMParameter->SetAttributes(pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS));
		pTMParameter->SetAttributes(pTMParameter->GetAttributes() | TMPARAMETER_CALIBRATION_NONE);
	}
	if (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)
	{
		if ((pDatabaseTMNumCalTable = ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())))) ? GetDatabase()->GetTMNumCalTables()->GetAt(GetDatabase()->GetTMNumCalTables()->Find(pszTable)) : (CDatabaseTMNumCalTable *)NULL))
		{
			for (nPoint = 0, nPoints = (GetDatabase()->CheckTMParameterConstValue(pTMParameter->GetAttributes() | TMPARAMETER_NATURE_CONSTANT, pszValue)) ? (INT)(pDatabaseTMNumCalTable->GetSize() - 1) : -1, fValue = _tstof(pszValue); nPoint < nPoints; nPoint++)
			{
				if ((pDatabaseTMNumCalPoint[0] = pDatabaseTMNumCalTable->GetAt(nPoint)))
				{
					if ((pDatabaseTMNumCalPoint[1] = pDatabaseTMNumCalTable->GetAt(nPoint + 1)))
					{
						if ((fValue >= pDatabaseTMNumCalPoint[0]->GetY() && fValue <= pDatabaseTMNumCalPoint[1]->GetY()) || (fValue <= pDatabaseTMNumCalPoint[0]->GetY() && fValue >= pDatabaseTMNumCalPoint[1]->GetY()))
						{
							fRawValue = pDatabaseTMNumCalPoint[0]->GetX() + ((fValue - pDatabaseTMNumCalPoint[0]->GetY()) / (pDatabaseTMNumCalPoint[1]->GetY() - pDatabaseTMNumCalPoint[0]->GetY()))*(pDatabaseTMNumCalPoint[1]->GetX() - pDatabaseTMNumCalPoint[0]->GetX());
							break;
						}
					}
				}
			}
			if (nPoint < nPoints)
			{
				UpdateParameter(pTMParameter, (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), fRawValue, FALSE) : CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (ULONGLONG)fRawValue, FALSE), nSample, nStatus, pDatabaseTMNumCalTable->GetName());
				return TRUE;
			}
			if (nPoint == nPoints)
			{
				if ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_INTERPRETATION_FULL) != TMPARAMETER_INTERPRETATION_FULL)
				{
					if ((pDatabaseTMNumCalPoint[0] = pDatabaseTMNumCalTable->GetAt(0)))
					{
						if ((pDatabaseTMNumCalPoint[1] = pDatabaseTMNumCalTable->GetAt(1)))
						{
							if ((fRawValue = pDatabaseTMNumCalPoint[0]->GetX() + ((fValue - pDatabaseTMNumCalPoint[0]->GetY()) / (pDatabaseTMNumCalPoint[1]->GetY() - pDatabaseTMNumCalPoint[0]->GetY()))*(pDatabaseTMNumCalPoint[1]->GetX() - pDatabaseTMNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pDatabaseTMParameter->GetWidth()))
							{
								UpdateParameter(pTMParameter, (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), fRawValue, FALSE) : CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (ULONGLONG)fRawValue, FALSE), nSample, nStatus, pDatabaseTMNumCalTable->GetName());
								return TRUE;
							}
						}
					}
					if ((pDatabaseTMNumCalPoint[0] = pDatabaseTMNumCalTable->GetAt((INT)pDatabaseTMNumCalTable->GetUpperBound() - 1)))
					{
						if ((pDatabaseTMNumCalPoint[1] = pDatabaseTMNumCalTable->GetAt((INT)pDatabaseTMNumCalTable->GetUpperBound())))
						{
							if ((fRawValue = pDatabaseTMNumCalPoint[0]->GetX() + ((fValue - pDatabaseTMNumCalPoint[0]->GetY()) / (pDatabaseTMNumCalPoint[1]->GetY() - pDatabaseTMNumCalPoint[0]->GetY()))*(pDatabaseTMNumCalPoint[1]->GetX() - pDatabaseTMNumCalPoint[0]->GetX())) >= 0.0  &&  fRawValue < pow(2.0, pDatabaseTMParameter->GetWidth()))
							{
								UpdateParameter(pTMParameter, (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), fRawValue, FALSE) : CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (ULONGLONG)fRawValue, FALSE), nSample, nStatus, pDatabaseTMNumCalTable->GetName());
								return TRUE;
							}
						}
					}
				}
			}
			return FALSE;
		}
	}
	if (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
	{
		if ((pDatabaseTMTxtCalTable = ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())))) ? GetDatabase()->GetTMTxtCalTables()->GetAt(GetDatabase()->GetTMTxtCalTables()->Find(pszTable)) : (CDatabaseTMTxtCalTable *)NULL))
		{
			for (nPoint = 0, nPoints = (INT)pDatabaseTMTxtCalTable->GetSize(); nPoint < nPoints; nPoint++)
			{
				if ((pDatabaseTMTxtCalPoint = pDatabaseTMTxtCalTable->GetAt(nPoint)))
				{
					if (pDatabaseTMTxtCalPoint->GetPoint(fX[0], szValue))
					{
						szPoint.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_POINTVALUE_FORMAT), (LPCTSTR)szValue, (LONGLONG)fX[0]);
						if (szValue == pszValue || szPoint == pszValue) break;
					}
					if (pDatabaseTMTxtCalPoint->GetRange(fX[0], fX[1], szValue))
					{
						szRange.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_RANGEVALUE_FORMAT), (LPCTSTR)szValue, (LONGLONG)fX[0], (LONGLONG)fX[1]);
						if (szValue == pszValue || szRange == pszValue) break;
					}
				}
			}
			if (nPoint < nPoints)
			{
				UpdateParameter(pTMParameter, (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), fX[0], FALSE) : CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (UINT)fX[0], FALSE), nSample, nStatus, pDatabaseTMTxtCalTable->GetName());
				return TRUE;
			}
			return FALSE;
		}
	}
	if (GetDatabase()->CheckTMParameterConstValue(pTMParameter->GetAttributes() | TMPARAMETER_NATURE_CONSTANT, pszValue))
	{
		for (fValue = _tstof(pszValue); (pDatabaseTMParameter = (pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())) : (CDatabaseTMParameter *)NULL); )
		{
			for (; pTMParameter->GetAttributes() & TMPARAMETER_RADIX_BINARY; )
			{
				fValue = (double)CDatabaseEngine::ParseValue(pszValue, 2);
				break;
			}
			for (; pTMParameter->GetAttributes() & TMPARAMETER_RADIX_OCTAL; )
			{
				fValue = (double)CDatabaseEngine::ParseValue(pszValue, 8);
				break;
			}
			for (; pTMParameter->GetAttributes() & TMPARAMETER_RADIX_HEXADECIMAL; )
			{
				fValue = (double)CDatabaseEngine::ParseValue(pszValue, 16);
				break;
			}
			UpdateParameter(pTMParameter, CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (UINT)fValue, FALSE), nSample, nStatus, EMPTYSTRING);
			return TRUE;
		}
		if ((pDatabaseTMParameter = (pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())) : (CDatabaseTMParameter *)NULL))
		{
			UpdateParameter(pTMParameter, CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), pDatabaseTMParameter->GetWidth(), (UINT)fValue, FALSE), nSample, nStatus, EMPTYSTRING);
			return TRUE;
		}
		if (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)
		{
			UpdateParameter(pTMParameter, CDatabaseEngine::EncodeValue(GetDatabase()->GetType(), pTMParameter->GetAttributes(), fValue, FALSE), nSample, nStatus, EMPTYSTRING);
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CScriptPropertiesParametersDialog::UpdateParameter(CTMParameter *pTMParameter, ULONGLONG nRawValue, INT nSample, UINT nStatus, LPCTSTR pszTable) CONST
{
	INT  nIndex[2];
	INT  nCount[2];
	UINT  nSampleStatus;
	CString  szSampleTable;
	ULONGLONG  nSampleValue;
	CByteArray  nSampleValueStatus;
	CLongUIntArray  nSampleValues;
	CStringArray  szTables;
	CTimeTag  tTMUnit;
	CTMUnit  cTMUnit;

	for (cTMUnit.SetTag(STRING(IDS_TMUNIT_INTERACTIVE)), cTMUnit.SetTimeTag((pTMParameter->GetLastUpdateTime() > 0) ? pTMParameter->GetLastUpdateTime() : tTMUnit.GetTime()); nSample < 0; )
	{
		for (nIndex[0] = 0, nCount[0] = max(pTMParameter->GetPastValueCount(), abs(nSample)), pTMParameter->SetPastValueSamples(nCount[0]); nIndex[0] < nCount[0]; nIndex[0]++)
		{
			if (nCount[0] - nIndex[0] != abs(nSample) && pTMParameter->GetRawValue(nCount[0] - nIndex[0], nSampleValue, nSampleStatus, szSampleTable, TRUE))
			{
				nSampleValues.SetAtGrow(nIndex[0], nSampleValue);
				nSampleValueStatus.SetAtGrow(nIndex[0], nSampleStatus);
				szTables.SetAtGrow(nIndex[0], szSampleTable);
			}
			if (nCount[0] - nIndex[0] == abs(nSample))
			{
				nSampleValues.SetAtGrow(nIndex[0], nRawValue);
				nSampleValueStatus.SetAtGrow(nIndex[0], nStatus);
				szTables.SetAtGrow(nIndex[0], pszTable);
			}
		}
		for (nIndex[1] = 0, nCount[1] = pTMParameter->GetValueCount(); nIndex[1] < nCount[1]; nIndex[1]++)
		{
			if (pTMParameter->GetRawValue(nIndex[1], nSampleValue, nSampleStatus, szSampleTable))
			{
				nSampleValues.SetAtGrow(nCount[0] + nIndex[1], nSampleValue);
				nSampleValueStatus.SetAtGrow(nCount[0] + nIndex[1], nSampleStatus);
				szTables.SetAtGrow(nCount[0] + nIndex[1], szSampleTable);
			}
		}
		for (nIndex[0] = 0, cTMUnit.SetTimeTag(cTMUnit.GetTimeTag().GetTime() - 1), nSampleValues.SetSize(nCount[0] + nCount[1]), nSampleValueStatus.SetSize(nCount[0] + nCount[1]), szTables.SetSize(nCount[0] + nCount[1]); nIndex[0] < nCount[0]; nIndex[0]++)
		{
			if (nSampleValueStatus.GetAt(nIndex[0]) != TMPARAMETER_STATUS_NONE)
			{
				if (!pTMParameter->SetRawValue(&cTMUnit, nIndex[0], nSampleValues.GetAt(nIndex[0]), nSampleValueStatus.GetAt(nIndex[0]), szTables.GetAt(nIndex[0]))) break;
				continue;
			}
		}
		for (nIndex[1] = 0, cTMUnit.SetTimeTag(cTMUnit.GetTimeTag().GetTime() + 1); nIndex[1] < nCount[1]; nIndex[1]++)
		{
			if (nSampleValueStatus.GetAt(nCount[0] + nIndex[1]) != TMPARAMETER_STATUS_NONE)
			{
				if (!pTMParameter->SetRawValue(&cTMUnit, nIndex[1], nSampleValues.GetAt(nCount[0] + nIndex[1]), nSampleValueStatus.GetAt(nCount[0] + nIndex[1]), szTables.GetAt(nCount[0] + nIndex[1]))) break;
				continue;
			}
		}
		return((nIndex[0] == nCount[0] && nIndex[1] == nCount[1]) ? TRUE : FALSE);
	}
	return pTMParameter->SetRawValue(&cTMUnit, nSample, nRawValue, nStatus, pszTable);
}

BOOL CScriptPropertiesParametersDialog::CheckParameter() CONST
{
	INT  nIndex;
	CTMParameter  *pTMParameter;

	return(((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL)) ? CheckParameter(pTMParameter) : FALSE);
}
BOOL CScriptPropertiesParametersDialog::CheckParameter(CONST CTMParameter *pTMParameter) CONST
{
	CString  szValue;

	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->GetWindowText(szValue);
	return CheckParameterValue(pTMParameter, szValue);
}

BOOL CScriptPropertiesParametersDialog::CheckParameterValue(CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValue) CONST
{
	CTMParameter  cTMParameter;

	cTMParameter.SetTag(pDatabaseTMParameter->GetTag());
	cTMParameter.SetAttributes(pDatabaseTMParameter->GetAttributes());
	return CheckParameterValue(&cTMParameter, pszValue);
}
BOOL CScriptPropertiesParametersDialog::CheckParameterValue(CONST CTMParameter *pTMParameter, LPCTSTR pszValue) CONST
{
	CTMParameter  cTMParameter;

	cTMParameter.Copy(pTMParameter);
	return((UpdateParameter(&cTMParameter, pszValue)) ? !cTMParameter.Compare(pTMParameter) : FALSE);
}

INT CScriptPropertiesParametersDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

VOID CScriptPropertiesParametersDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, (bCheck = CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE)));
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_VALID, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_INVALID, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_GOOD, bCheck);
	AccessControl(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_BAD, bCheck);
}

BOOL CScriptPropertiesParametersDialog::IsModified() CONST
{
	return !m_pTMParameters[0].Compare(&m_pTMParameters[1]);
}

void CScriptPropertiesParametersDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptPropertiesParametersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CScriptPropertiesParametersDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CScriptPropertiesParametersDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CScriptPropertiesParametersDialog)
	ON_WM_TIMER()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_ADD, OnAdd)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVEALL, OnRemoveAll)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW, OnRawValue)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST, OnPastSample)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT, OnNoLimit)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT, OnSoftLimit)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT, OnHardLimit)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT, OnDeltaLimit)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT, OnConsistencyLimit)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_VALID, OnValidStatus)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_INVALID, OnInvalidStatus)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_GOOD, OnGoodQuality)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_BAD, OnBadQuality)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET, OnSetParameter)
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, OnSelchangeParameter)
	ON_CBN_SELCHANGE(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, OnSelchangeValue)
	ON_CBN_SELCHANGE(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, OnSelchangeTable)
	ON_CBN_EDITCHANGE(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, OnEditchangeValue)
	ON_CONTROL(SBXN_CHANGE, IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE, OnSpinchangeSample)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParametersDialog message handlers

BOOL CScriptPropertiesParametersDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG));
	m_szColumns.Add(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TYPE));
	m_szColumns.Add(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_CODING));
	m_szColumns.Add(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_VALUE));
	m_szColumns.Add(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_STATUS));
	m_szColumns.Add(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_QUALITY));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT), Spinbox_SetRange(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE), SCRIPTPROPERTIESPARAMETERS_MINIMUMSAMPLE, SCRIPTPROPERTIESPARAMETERS_MAXIMUMSAMPLE); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG)) ? (rColumns.Width() / 5) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_DESCRIPTION)) ? (rColumns.Width() / 2) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TYPE)) ? (rColumns.Width() / 6) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_CODING) || m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_VALUE)) ? (9 * rColumns.Width() / 35) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_STATUS)) ? (rColumns.Width() / 3) : (rColumns.Width() / 8))))));
		continue;
	}
	if (EnumParameters())
	{
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_DETAILS)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG_STATIC)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_STATIC)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_STATIC)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_VALID)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_INVALID)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_STATIC)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_GOOD)->EnableWindow();
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_BAD)->EnableWindow();
		ShowProperties();
	}
	AdjustToPrivileges();
	return TRUE;
}

BOOL CScriptPropertiesParametersDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CString  szValue;
	CString  szTable;
	CTMParameter  *pTMParameter;
	CScriptPropertiesParameterDetailsDialog  cParameterDetailsDialog;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		for (; pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED); )
		{
			ShowParameterDetails();
			break;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			if ((pTMParameter = m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), pNotifyListView->iItem, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG)))))) && (pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) && !IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW) && cParameterDetailsDialog.DoModal(pTMParameter, szTable, szValue) == IDOK)
			{
				for (SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szTable)), EnumCalibrationTableValues(), GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetWindowText(szValue); UpdateParameter(pTMParameter, szValue); )
				{
					ShowProperties(pNotifyListView->iItem);
					break;
				}
				SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
				GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetFocus();
				GetDlgItem(IDOK)->EnableWindow(Check());
			}
		}
	}
	return CLocaleDialog::OnNotify(wParam, lParam, pResult);
}

void CScriptPropertiesParametersDialog::OnTimer(UINT_PTR nEventID)
{
	if (nEventID == IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)
	{
		SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetFocus();
		KillTimer(nEventID);
		return;
	}
	CLocaleDialog::OnTimer(nEventID);
}

void CScriptPropertiesParametersDialog::OnAdd()
{
	INT  nIndex;
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CHourglassCursor  cCursor;

	for (; (pTMParameter = new CTMParameter); )
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt((INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, CB_GETCURSEL))))
		{
			for (pTMParameter->SetTag(pDatabaseTMParameter->GetTag()), pTMParameter->SetAttributes(pDatabaseTMParameter->GetAttributes()); (nIndex = (UpdateParameter(pTMParameter)) ? m_pTMParameters[0].Add(pTMParameter) : -1) >= 0; )
			{
				ShowProperties();
				break;
			}
			if (nIndex >= 0)
			{
				Listview_SetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex);
				GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST_STATIC)->EnableWindow();
				GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST)->EnableWindow();
				GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST)->SetFocus();
				break;
			}
		}
		delete pTMParameter;
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesParametersDialog::OnRemove()
{
	INT  nIndex;
	CTMParameter  *pTMParameter;
	CHourglassCursor  cCursor;

	if ((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL))
	{
		m_pTMParameters[0].RemoveAt(nIndex);
		delete pTMParameter;
		ShowProperties();
	}
	if (Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST)) >= 0)
	{
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVE)->EnableWindow(CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVEALL)->EnableWindow(CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE));
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST)->SetFocus();
	}
	else
	{
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVEALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesParametersDialog::OnRemoveAll()
{
	CHourglassCursor  cCursor;

	if (SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST, LVM_GETITEMCOUNT) > 0)
	{
		m_pTMParameters[0].RemoveAll();
		ShowProperties();
	}
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesParametersDialog::OnRawValue()
{
	INT  nIndex;
	CString  szValue;
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if ((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL))
	{
		for (pTMParameter->SetAttributes((pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) | TMPARAMETER_CALIBRATION_NONE); !IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW); )
		{
			for (; (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag()))) && (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)); )
			{
				pTMParameter->SetAttributes((pTMParameter->GetAttributes() & ~TMPARAMETER_CALIBRATION_NONE) | (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)));
				break;
			}
			break;
		}
		ShowProperties(nIndex);
	}
	if (!IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW))
	{
		SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_SETCURSEL);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		EnumCalibrationTableValues();
	}
	else
	{
		SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_SETCURSEL, (WPARAM)-1);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE)->EnableWindow(FALSE);
		EnumCalibrationTableValues();
	}
	if ((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL))
	{
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetWindowText((pTMParameter->GetValueAsText(GetDatabase(), (INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)), szValue, IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST))) ? szValue : EMPTYSTRING);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMARK)->ShowWindow(((pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) && !IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW)) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_REMARK)->EnableWindow(((pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) && !IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW)) ? TRUE : FALSE);
	}
	SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesParametersDialog::OnPastSample()
{
	INT  nIndex;
	CString  szValue;
	CTMParameter  *pTMParameter;

	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetWindowText(((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL) && pTMParameter->GetValueAsText(GetDatabase(), (INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)), szValue, IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST))) ? szValue : EMPTYSTRING);
	SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetFocus();
}

void CScriptPropertiesParametersDialog::OnNoLimit()
{
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT, TRUE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT, FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(CheckParameter());
}

void CScriptPropertiesParametersDialog::OnSoftLimit()
{
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT, TRUE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT, FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(CheckParameter());
}

void CScriptPropertiesParametersDialog::OnHardLimit()
{
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT, TRUE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT, FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(CheckParameter());
}

void CScriptPropertiesParametersDialog::OnDeltaLimit()
{
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT, TRUE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT, FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(CheckParameter());
}

void CScriptPropertiesParametersDialog::OnConsistencyLimit()
{
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT, TRUE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(CheckParameter());
}

void CScriptPropertiesParametersDialog::OnValidStatus()
{
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_VALID, TRUE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_INVALID, FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(CheckParameter());
}

void CScriptPropertiesParametersDialog::OnInvalidStatus()
{
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_VALID, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_INVALID, TRUE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(CheckParameter());
}

void CScriptPropertiesParametersDialog::OnGoodQuality()
{
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_GOOD, TRUE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_BAD, FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(CheckParameter());
}

void CScriptPropertiesParametersDialog::OnBadQuality()
{
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_GOOD, FALSE);
	CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_BAD, TRUE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(CheckParameter());
}

void CScriptPropertiesParametersDialog::OnSetParameter()
{
	INT  nIndex;
	CString  szValue;
	CTMParameter  *pTMParameter;
	CHourglassCursor  cCursor;

	if ((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL))
	{
		for (; UpdateParameter(pTMParameter); )
		{
			ShowProperties(nIndex);
			break;
		}
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetWindowText((pTMParameter->GetValueAsText(GetDatabase(), (INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)), szValue, IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST))) ? szValue : EMPTYSTRING);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST)->EnableWindow((Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)) > 0 && pTMParameter->GetValueCount() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesParametersDialog::OnSelchangeParameter()
{
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt((INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, CB_GETCURSEL))))
	{
		Listview_SetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), m_pTMParameters[0].Find(pDatabaseTMParameter->GetTag()));
		ShowParameterDetails();
	}
}

void CScriptPropertiesParametersDialog::OnSelchangeValue()
{
	INT  nIndex;
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if ((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL))
	{
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow((CheckParameterValue(pTMParameter, Combobox_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE), (INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_GETCURSEL)))) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_ADD)->EnableWindow(FALSE);
		return;
	}
	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt((INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, CB_GETCURSEL))))
	{
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_ADD)->EnableWindow((CheckParameterValue(pDatabaseTMParameter, Combobox_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE), (INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_GETCURSEL)))) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(FALSE);
	}
}

void CScriptPropertiesParametersDialog::OnSelchangeTable()
{
	INT  nIndex;
	UINT  nStatus;
	CString  szValue;
	ULONGLONG  nValue;
	CStringArray  szTables[2];
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (EnumCalibrationTableValues(); (pDatabaseTMParameter = ((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL)) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag())) : (CDatabaseTMParameter *)NULL) && SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCURSEL) < pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1]) && pTMParameter->GetRawValue((INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)), nValue, nStatus, IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST)); )
	{
		UpdateParameter(pTMParameter, nValue, (IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST)) ? -(INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)) : (INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)), nStatus, szTables[0].GetAt(SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE, CB_GETCURSEL)));
		ShowProperties(nIndex);
		break;
	}
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetWindowText(((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL) && pTMParameter->GetValueAsText(GetDatabase(), (INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)), szValue, IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST))) ? szValue : EMPTYSTRING);
	SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE, CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptPropertiesParametersDialog::OnEditchangeValue()
{
	INT  nIndex;
	CString  szValue;
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->GetWindowText(szValue);
	if ((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL))
	{
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow((CheckParameterValue(pTMParameter, szValue)) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_ADD)->EnableWindow(FALSE);
		return;
	}
	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt((INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG, CB_GETCURSEL))))
	{
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_ADD)->EnableWindow((CheckParameterValue(pDatabaseTMParameter, szValue)) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
		GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SET)->EnableWindow(FALSE);
	}
}

void CScriptPropertiesParametersDialog::OnSpinchangeSample()
{
	INT  nIndex;
	CString  szValue;
	CTMParameter  *pTMParameter;

	for (SetTimer(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE, 0, NULL); !Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)); )
	{
		CheckDlgButton(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST, FALSE);
		break;
	}
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE)->SetWindowText(((pTMParameter = ((nIndex = Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST))) >= 0) ? m_pTMParameters[0].GetAt(m_pTMParameters[0].Find(Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST), nIndex, FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERSDIALOG_TITLEITEM_TAG))))) : (CTMParameter *)NULL) && pTMParameter->GetValueAsText(GetDatabase(), (INT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)), szValue, IsDlgButtonChecked(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST))) ? szValue : EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST)->EnableWindow((Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE)) > 0) ? TRUE : FALSE);
}

BOOL CScriptPropertiesParametersDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTPROPERTIESPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CScriptPropertiesParametersDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTPROPERTIESPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsCalibrationPage property page

IMPLEMENT_DYNCREATE(CScriptPropertiesParameterDetailsCalibrationPage, CLocalePropertyPage)

CScriptPropertiesParameterDetailsCalibrationPage::CScriptPropertiesParameterDetailsCalibrationPage() : CLocalePropertyPage(CScriptPropertiesParameterDetailsCalibrationPage::IDD)
{
	//{{AFX_DATA_INIT(CScriptPropertiesParameterDetailsCalibrationPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CScriptPropertiesParameterDetailsCalibrationPage::ShowParameterInfo(CONST CTMParameter *pTMParameter)
{
	INT  nIndex;
	INT  nTable;
	INT  nTables;
	UINT  nStatus;
	CString  szName;
	CString  szTable;
	ULONGLONG  nValue;
	CStringArray  szTables[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	for (SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT), nIndex = -1; (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag()))); )
	{
		for (nTable = 0, nTables = pDatabaseTMParameter->GetCalTables(szTables[0], szTables[1]), szTable = (pTMParameter->GetRawValue(pTMParameter->GetValueCount() - 1, nValue, nStatus, szTable)) ? szTable : EMPTYSTRING; nTable < nTables; nTable++)
		{
			if ((m_nCalTableType = (pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS))) == TMPARAMETER_CALIBRATION_NUMERICAL)
			{
				if ((pDatabaseTMNumCalTable = GetDatabase()->GetTMNumCalTables()->GetAt(GetDatabase()->GetTMNumCalTables()->Find(szTables[0].GetAt(nTable)))))
				{
					for (szName.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTMNumCalTable->GetDescription(), (LPCTSTR)pDatabaseTMNumCalTable->GetName()); pDatabaseTMNumCalTable->GetDescription().IsEmpty(); )
					{
						szName = pDatabaseTMNumCalTable->GetName();
						break;
					}
					for (SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName); pDatabaseTMNumCalTable->GetName() == szTable; )
					{
						nIndex = nTable;
						break;
					}
					m_nCalTableRefs.SetAtGrow(nTable, GetDatabase()->GetTMNumCalTables()->Find(szTables[0].GetAt(nTable)));
					m_nCalValidityRefs.SetAtGrow(nTable, GetDatabase()->GetTMParameters()->Find(szTables[1].GetAt(nTable)));
					continue;
				}
			}
			if (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
			{
				if ((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(GetDatabase()->GetTMTxtCalTables()->Find(szTables[0].GetAt(nTable)))))
				{
					for (szName.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTMTxtCalTable->GetDescription(), (LPCTSTR)pDatabaseTMTxtCalTable->GetName()); pDatabaseTMTxtCalTable->GetDescription().IsEmpty(); )
					{
						szName = pDatabaseTMTxtCalTable->GetName();
						break;
					}
					for (SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName); pDatabaseTMTxtCalTable->GetName() == szTable; )
					{
						nIndex = nTable;
						break;
					}
					m_nCalTableRefs.SetAtGrow(nTable, GetDatabase()->GetTMTxtCalTables()->Find(szTables[0].GetAt(nTable)));
					m_nCalValidityRefs.SetAtGrow(nTable, GetDatabase()->GetTMParameters()->Find(szTables[1].GetAt(nTable)));
					continue;
				}
			}
		}
		break;
	}
	m_nCalTableID = (INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME, CB_SETCURSEL, max(nIndex, 0));
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	ShowCalibrationInfo();
}

VOID CScriptPropertiesParameterDetailsCalibrationPage::ShowCalibrationInfo()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	double  fCalPtX;
	double  fCalPtY;
	CString  szItem;
	CString  szCalPtX;
	CString  szCalPtY;
	CString  szCalText;
	CStringTools  cStringTools;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMNumCalPoint  *pDatabaseTMNumCalPoint;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTMTxtCalPoint  *pDatabaseTMTxtCalPoint;

	SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME, CB_GETCURSEL)) >= 0 && nIndex < m_nCalTableRefs.GetSize())
	{
		if ((pDatabaseTMNumCalTable = (m_nCalTableType == TMPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTMNumCalTables()->GetAt(m_nCalTableRefs.GetAt(nIndex)) : (CDatabaseTMNumCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTMNumCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMNumCalPoint = pDatabaseTMNumCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							szItem = cStringTools.ConvertFloatToTruncatedString(pDatabaseTMNumCalPoint->GetX(), -1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = cStringTools.ConvertFloatToString(pDatabaseTMNumCalPoint->GetY(), -1);
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTMNumCalTable->GetName());
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TYPE_NUMERICAL));
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
		if ((pDatabaseTMTxtCalTable = (m_nCalTableType == TMPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTMTxtCalTables()->GetAt(m_nCalTableRefs.GetAt(nIndex)) : (CDatabaseTMTxtCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTMTxtCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMTxtCalPoint = pDatabaseTMTxtCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							if (pDatabaseTMTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText) || pDatabaseTMTxtCalPoint->GetPoint(fCalPtX, szCalText))
							{
								for (szCalPtX = szItem = cStringTools.ConvertFloatToTruncatedString(fCalPtX, -1), szCalPtY = cStringTools.ConvertFloatToTruncatedString(fCalPtY, -1); fCalPtX != fCalPtY; )
								{
									szItem.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_POINT_RANGE), (LPCTSTR)szCalPtX, (LPCTSTR)szCalPtY);
									break;
								}
								break;
							}
							szItem.Empty();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = (pDatabaseTMTxtCalPoint->GetPoint(fCalPtX, szCalText) || pDatabaseTMTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText)) ? (LPCTSTR)szCalText : EMPTYSTRING;
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTMTxtCalTable->GetName());
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TYPE_STATUS));
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
	}
	SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS)->EnableWindow(FALSE);
}

BOOL CScriptPropertiesParameterDetailsCalibrationPage::GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST
{
	CString  szTableID;
	CString  szTableName;

	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID)->GetWindowText(szTableID);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME)->GetWindowText(szTableName);
	szTable.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILSDIALOG_FORMAT), (LPCTSTR)szTableID, (LPCTSTR)szTableName);
	szX = Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS), Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS)), FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_X)));
	szY = Listview_GetText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS), Listview_GetCurText(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS)), FindColumnIndex(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_Y)));
	return((!szTable.IsEmpty() && !szX.IsEmpty() && !szY.IsEmpty()) ? TRUE : FALSE);
}

CScriptPropertiesParameterDetailsFolder *CScriptPropertiesParameterDetailsCalibrationPage::GetParent() CONST
{
	return((CScriptPropertiesParameterDetailsFolder *)CLocalePropertyPage::GetParent());
}

INT CScriptPropertiesParameterDetailsCalibrationPage::FindColumnIndex(LPCTSTR pszColumn) CONST
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_szColumns.GetAt(nColumn) == pszColumn) break;
		continue;
	}
	return((nColumn < nColumns) ? nColumn : -1);
}

void CScriptPropertiesParameterDetailsCalibrationPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptPropertiesParameterDetailsCalibrationPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CScriptPropertiesParameterDetailsCalibrationPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nCalTableRefs.RemoveAll();
	m_nCalValidityRefs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CScriptPropertiesParameterDetailsCalibrationPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CScriptPropertiesParameterDetailsCalibrationPage)
	ON_CBN_SELCHANGE(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsCalibrationPage message handlers

BOOL CScriptPropertiesParameterDetailsCalibrationPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_X));
	m_szColumns.Add(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILS_CALIBRATIONPAGE_TITLEITEM_Y));
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5; nColumn < nColumns; nWidth = (++nColumn > 0) ? (2 * (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	return TRUE;
}

BOOL CScriptPropertiesParameterDetailsCalibrationPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CString  szX;
	CString  szY;
	CString  szTable;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			if (GetSelectedCalibrationPoint(szTable, szX, szY))
			{
				GetParent()->GetParent()->SetSelectedCalibrationPoint(szTable, szX, szY);
				GetParent()->GetParent()->EndDialog(IDOK);
				return TRUE;
			}
		}
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CScriptPropertiesParameterDetailsCalibrationPage::OnSelchangeName()
{
	ShowCalibrationInfo();
}


/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsFolderTabCtrl

IMPLEMENT_DYNCREATE(CScriptPropertiesParameterDetailsFolderTabCtrl, CTabCtrl)

CScriptPropertiesParameterDetailsFolder *CScriptPropertiesParameterDetailsFolderTabCtrl::GetParent() CONST
{
	return((CScriptPropertiesParameterDetailsFolder *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CScriptPropertiesParameterDetailsFolderTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CScriptPropertiesParameterDetailsFolderTabCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsFolderTabCtrl message handlers

UINT CScriptPropertiesParameterDetailsFolderTabCtrl::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void CScriptPropertiesParameterDetailsFolderTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd  *pWnd;

	if (nChar == VK_TAB)
	{
		if ((pWnd = GetParent()->GetParent()->GetNextDlgTabItem(GetParent(), (HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE)))
		{
			pWnd->SetFocus();
			return;
		}
	}
	if (nChar == VK_DOWN)
	{
		if ((pWnd = GetParent()->GetActivePage()->GetNextDlgTabItem((CWnd *)NULL)))
		{
			pWnd->SetFocus();
			return;
		}
	}
	CTabCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsFolder

IMPLEMENT_DYNCREATE(CScriptPropertiesParameterDetailsFolder, CLocalePropertySheetDialog)

CScriptPropertiesParameterDetailsFolder::CScriptPropertiesParameterDetailsFolder() : CLocalePropertySheetDialog()
{
	AddPage(&m_pageCalibration);
}

BOOL CScriptPropertiesParameterDetailsFolder::Create(CWnd *pParentWnd, CONST RECT &rect)
{
	INT  nPage;

	if (CLocalePropertySheetDialog::Create(pParentWnd, WS_CHILD | WS_TABSTOP | WS_DISABLED))
	{
		for (nPage = GetPageCount() - 1, m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nPage >= 0; nPage--)
		{
			SetActivePage(nPage);
			continue;
		}
		MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		ShowWindow(SW_SHOWNORMAL);
		return TRUE;
	}
	return FALSE;
}

VOID CScriptPropertiesParameterDetailsFolder::ShowParameterInfo(CONST CTMParameter *pTMParameter)
{
	m_pageCalibration.ShowParameterInfo(pTMParameter);
}

BOOL CScriptPropertiesParameterDetailsFolder::GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST
{
	return m_pageCalibration.GetSelectedCalibrationPoint(szTable, szX, szY);
}

CScriptPropertiesParameterDetailsDialog *CScriptPropertiesParameterDetailsFolder::GetParent() CONST
{
	return((CScriptPropertiesParameterDetailsDialog *)CLocalePropertySheetDialog::GetParent());
}

BEGIN_MESSAGE_MAP(CScriptPropertiesParameterDetailsFolder, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CScriptPropertiesParameterDetailsFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsFolder message handlers

void CScriptPropertiesParameterDetailsFolder::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_wndTabCtrl.GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return;
	}
	CLocalePropertySheetDialog::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsDialog dialog

IMPLEMENT_DYNCREATE(CScriptPropertiesParameterDetailsDialog, CDisplayDialog)

CScriptPropertiesParameterDetailsDialog::CScriptPropertiesParameterDetailsDialog(CWnd *pParentWnd) : CLocaleDialog(CScriptPropertiesParameterDetailsDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CScriptPropertiesParameterDetailsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CScriptPropertiesParameterDetailsDialog::DoModal(CONST CTMParameter *pTMParameter, CString &szTable, CString &szValue)
{
	INT  nResult;
	CString  szX;
	CString  szY;

	for (m_cTMParameter.Copy(pTMParameter), szTable.Empty(), szValue.Empty(); (nResult = (INT)CLocaleDialog::DoModal()) == IDOK; )
	{
		szValue = (GetSelectedCalibrationPoint(szTable, szX, szY)) ? szY : EMPTYSTRING;
		break;
	}
	return nResult;
}

VOID CScriptPropertiesParameterDetailsDialog::SetSelectedCalibrationPoint(LPCTSTR pszTable, LPCTSTR pszX, LPCTSTR pszY)
{
	m_szX = pszX;
	m_szY = pszY;
	m_szTable = pszTable;
}

BOOL CScriptPropertiesParameterDetailsDialog::GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST
{
	szX = m_szX;
	szY = m_szY;
	szTable = m_szTable;
	return((!szTable.IsEmpty() && !szX.IsEmpty() && !szY.IsEmpty()) ? TRUE : FALSE);
}

CScriptPropertiesParametersDialog *CScriptPropertiesParameterDetailsDialog::GetParent() CONST
{
	return((CScriptPropertiesParametersDialog *)CLocaleDialog::GetParent());
}

BOOL CScriptPropertiesParameterDetailsDialog::EnumParameters()
{
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_cTMParameter.GetTag()))))
	{
		if (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS))
		{
			szParameter.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILSDIALOG_FORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	szParameter.Format(STRING(IDS_SCRIPTPROPERTIESPARAMETERDETAILSDIALOG_FORMAT), (LPCTSTR)m_cTMParameter.GetTag(), EMPTYSTRING);
	SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter), 0));
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM_STATIC)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	m_wndFolderCtrl.EnableWindow((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CScriptPropertiesParameterDetailsDialog::ShowParameterInfo()
{
	m_wndFolderCtrl.ShowParameterInfo(&m_cTMParameter);
}

CRect CScriptPropertiesParameterDetailsDialog::CalcFolderSize() CONST
{
	CRect  rFolder;

	GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_FOLDER)->GetWindowRect(rFolder);
	ScreenToClient(rFolder);
	return rFolder;
}

void CScriptPropertiesParameterDetailsDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptPropertiesParameterDetailsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptPropertiesParameterDetailsDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CScriptPropertiesParameterDetailsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM, OnSelchangeParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsDialog message handlers

BOOL CScriptPropertiesParameterDetailsDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	if (m_wndFolderCtrl.Create(this, CalcFolderSize()) && SetChildSheet(&m_wndFolderCtrl, GetDlgItem(IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_FOLDER - 1)))
	{
		for (; EnumParameters(); )
		{
			ShowParameterInfo();
			break;
		}
	}
	return TRUE;
}

void CScriptPropertiesParameterDetailsDialog::OnSelchangeParameter()
{
	ShowParameterInfo();
}

void CScriptPropertiesParameterDetailsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_wndFolderCtrl.GetSelectedCalibrationPoint(m_szTable, m_szX, m_szY);
	CLocaleDialog::OnOK();
}

BOOL CScriptPropertiesParameterDetailsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTPROPERTIESPARAMETERDETAILSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CScriptPropertiesParameterDetailsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTPROPERTIESPARAMETERDETAILSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptFindDialog dialog

IMPLEMENT_DYNCREATE(CScriptFindDialog, CDisplayDialog)

CScriptFindDialog::CScriptFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CScriptFindDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CScriptFindDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CScriptFindDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CScriptWnd *CScriptFindDialog::GetParent() CONST
{
	return((CScriptWnd *)CDisplayDialog::GetParent());
}

void CScriptFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptFindDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CScriptFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCRIPT_FIND_NEXT, OnFindText)
	ON_BN_CLICKED(IDC_SCRIPT_FIND_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_SCRIPT_FIND_TEXT, OnSelchangeText)
	ON_CBN_EDITCHANGE(IDC_SCRIPT_FIND_TEXT, OnEditchangeText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptFindDialog message handlers

BOOL CScriptFindDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	BOOL  bFindDefaults[4];
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szSearchItems.GetSize(), GetFindDefaults(bFindDefaults[0], bFindDefaults[1], bFindDefaults[2], bFindDefaults[3]); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_SCRIPT_FIND_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szSearchItems.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_SCRIPT_FIND_DIRECTION_DOWN, bFindDefaults[0]);
	CheckDlgButton(IDC_SCRIPT_FIND_DIRECTION_UP, !bFindDefaults[0]);
	CheckDlgButton(IDC_SCRIPT_FIND_ALL, bFindDefaults[1]);
	CheckDlgButton(IDC_SCRIPT_FIND_CASE, bFindDefaults[2]);
	CheckDlgButton(IDC_SCRIPT_FIND_WORD, bFindDefaults[3]);
	GetDlgItem(IDC_SCRIPT_FIND_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_FIND_TEXT)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_FIND_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_FIND_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_FIND_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_FIND_ALL)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_FIND_CASE)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_FIND_WORD)->EnableWindow();
	return TRUE;
}

void CScriptFindDialog::OnFindText()
{
	CString  szText;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_SCRIPT_FIND_TEXT)->GetWindowText(szText); SendDlgItemMessage(IDC_SCRIPT_FIND_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText) == CB_ERR; )
	{
		SendDlgItemMessage(IDC_SCRIPT_FIND_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText);
		m_szSearchItems.Add(szText);
		break;
	}
	if (!GetParent()->SearchScriptCode(szText, IsDlgButtonChecked(IDC_SCRIPT_FIND_DIRECTION_DOWN), IsDlgButtonChecked(IDC_SCRIPT_FIND_ALL), IsDlgButtonChecked(IDC_SCRIPT_FIND_CASE), IsDlgButtonChecked(IDC_SCRIPT_FIND_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_SCRIPT_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
		return;
	}
	CheckDlgButton(IDC_SCRIPT_FIND_ALL, FALSE);
}

void CScriptFindDialog::OnSelchangeText()
{
	GetDlgItem(IDC_SCRIPT_FIND_NEXT)->EnableWindow((SendDlgItemMessage(IDC_SCRIPT_FIND_TEXT, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CScriptFindDialog::OnEditchangeText()
{
	GetDlgItem(IDC_SCRIPT_FIND_NEXT)->EnableWindow((GetDlgItem(IDC_SCRIPT_FIND_TEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CScriptFindDialog::OnCancel()
{
	GetParent()->SetFocus();
	CDisplayDialog::OnCancel();
}

BOOL CScriptFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CScriptFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptReplaceDialog dialog

IMPLEMENT_DYNCREATE(CScriptReplaceDialog, CDisplayDialog)

CScriptReplaceDialog::CScriptReplaceDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CScriptReplaceDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CScriptReplaceDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CScriptReplaceDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CScriptWnd *CScriptReplaceDialog::GetParent() CONST
{
	return((CScriptWnd *)CDisplayDialog::GetParent());
}

void CScriptReplaceDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptReplaceDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptReplaceDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CScriptReplaceDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCRIPT_REPLACE_FINDNEXT, OnFindNextText)
	ON_BN_CLICKED(IDC_SCRIPT_REPLACE_NEXT, OnReplaceText)
	ON_BN_CLICKED(IDC_SCRIPT_REPLACE_ALLNEXT, OnReplaceAllText)
	ON_BN_CLICKED(IDC_SCRIPT_REPLACE_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_SCRIPT_REPLACE_FINDTEXT, OnSelchangeFindText)
	ON_CBN_EDITCHANGE(IDC_SCRIPT_REPLACE_FINDTEXT, OnEditchangeFindText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptReplaceDialog message handlers

BOOL CScriptReplaceDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szItems[0].GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_SCRIPT_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szItems[0].GetAt(nItem));
		continue;
	}
	for (nItem = 0, nItems = (INT)m_szItems[1].GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_SCRIPT_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szItems[1].GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_SCRIPT_REPLACE_ALL, TRUE);
	CheckDlgButton(IDC_SCRIPT_REPLACE_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_REPLACE_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_REPLACE_TEXT)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_REPLACE_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_REPLACE_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_REPLACE_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_REPLACE_ALL)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_REPLACE_CASE)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_REPLACE_WORD)->EnableWindow();
	return TRUE;
}

void CScriptReplaceDialog::OnFindNextText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_SCRIPT_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_SCRIPT_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_SCRIPT_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_SCRIPT_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_SCRIPT_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->SearchScriptCode(szText[0], IsDlgButtonChecked(IDC_SCRIPT_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_SCRIPT_REPLACE_ALL), IsDlgButtonChecked(IDC_SCRIPT_REPLACE_CASE), IsDlgButtonChecked(IDC_SCRIPT_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_SCRIPT_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
		return;
	}
	CheckDlgButton(IDC_SCRIPT_REPLACE_ALL, FALSE);
}

void CScriptReplaceDialog::OnReplaceText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_SCRIPT_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_SCRIPT_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_SCRIPT_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_SCRIPT_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_SCRIPT_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->ReplaceScriptCode(szText[0], szText[1], IsDlgButtonChecked(IDC_SCRIPT_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_SCRIPT_REPLACE_ALL), IsDlgButtonChecked(IDC_SCRIPT_REPLACE_CASE), IsDlgButtonChecked(IDC_SCRIPT_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_SCRIPT_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
	}
}

void CScriptReplaceDialog::OnReplaceAllText()
{
	CString  szText[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT)->GetWindowText(szText[0]);
	if (SendDlgItemMessage(IDC_SCRIPT_REPLACE_FINDTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[0]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_SCRIPT_REPLACE_FINDTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[0]);
		m_szItems[0].Add(szText[0]);
	}
	GetDlgItem(IDC_SCRIPT_REPLACE_TEXT)->GetWindowText(szText[1]);
	if (SendDlgItemMessage(IDC_SCRIPT_REPLACE_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szText[1]) == CB_ERR)
	{
		SendDlgItemMessage(IDC_SCRIPT_REPLACE_TEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szText[1]);
		m_szItems[1].Add(szText[1]);
	}
	if (!GetParent()->ReplaceAllScriptCode(szText[0], szText[1], IsDlgButtonChecked(IDC_SCRIPT_REPLACE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_SCRIPT_REPLACE_ALL), IsDlgButtonChecked(IDC_SCRIPT_REPLACE_CASE), IsDlgButtonChecked(IDC_SCRIPT_REPLACE_WORD)))
	{
		ShowMessage(USER_INFORMATIONAL_SCRIPT_FIND_TEXT_NOTHING);
		GetParent()->SetFocus();
		DestroyWindow();
	}
}

void CScriptReplaceDialog::OnSelchangeFindText()
{
	GetDlgItem(IDC_SCRIPT_REPLACE_FINDNEXT)->EnableWindow((GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_REPLACE_NEXT)->EnableWindow((GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_REPLACE_ALLNEXT)->EnableWindow((GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CScriptReplaceDialog::OnEditchangeFindText()
{
	GetDlgItem(IDC_SCRIPT_REPLACE_FINDNEXT)->EnableWindow((GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_REPLACE_NEXT)->EnableWindow((GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_SCRIPT_REPLACE_ALLNEXT)->EnableWindow((GetDlgItem(IDC_SCRIPT_REPLACE_FINDTEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CScriptReplaceDialog::OnCancel()
{
	GetParent()->SetFocus();
	CDisplayDialog::OnCancel();
}

BOOL CScriptReplaceDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTREPLACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CScriptReplaceDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTREPLACEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptGoToDialog dialog

IMPLEMENT_DYNCREATE(CScriptGoToDialog, CDisplayDialog)

CScriptGoToDialog::CScriptGoToDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CScriptGoToDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CScriptGoToDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CScriptGoToDialog::IDD, FALSE)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CScriptWnd *CScriptGoToDialog::GetParent() CONST
{
	return((CScriptWnd *)CDisplayDialog::GetParent());
}

BOOL CScriptGoToDialog::Check(BOOL bModified) CONST
{
	return(((IsDlgButtonChecked(IDC_SCRIPT_GOTO_LINE) && GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->GetWindowTextLength() > 0) || IsDlgButtonChecked(IDC_SCRIPT_GOTO_JUMPDOWN) || IsDlgButtonChecked(IDC_SCRIPT_GOTO_JUMPUP)) ? TRUE : FALSE);
}

void CScriptGoToDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptGoToDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptGoToDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CScriptGoToDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_SCRIPT_GOTO_LINE, OnLineNumber)
	ON_BN_CLICKED(IDC_SCRIPT_GOTO_JUMPDOWN, OnJumpLineDown)
	ON_BN_CLICKED(IDC_SCRIPT_GOTO_JUMPUP, OnJumpLineUp)
	ON_BN_CLICKED(IDC_SCRIPT_GOTO_JUMP, OnJump)
	ON_BN_CLICKED(IDC_SCRIPT_GOTO_HELP, OnHelp)
	ON_EN_CHANGE(IDC_SCRIPT_GOTO_LINENUMBER, OnEditchangeLineNumber)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptGoToDialog message handlers

BOOL CScriptGoToDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_SCRIPT_GOTO_LINE, TRUE);
	Spinbox_SetRange(GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWNLINE), 1, INT_MAX);
	Spinbox_SetRange(GetDlgItem(IDC_SCRIPT_GOTO_JUMPUPLINE), 1, INT_MAX);
	GetDlgItem(IDC_SCRIPT_GOTO_LINE_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_GOTO_LINE)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWN)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPUP)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->SetFocus();
	return FALSE;
}

void CScriptGoToDialog::OnLineNumber()
{
	CheckDlgButton(IDC_SCRIPT_GOTO_LINE, TRUE);
	CheckDlgButton(IDC_SCRIPT_GOTO_JUMPDOWN, FALSE);
	CheckDlgButton(IDC_SCRIPT_GOTO_JUMPUP, FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWNLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPUP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPUPLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptGoToDialog::OnJumpLineDown()
{
	CheckDlgButton(IDC_SCRIPT_GOTO_LINE, FALSE);
	CheckDlgButton(IDC_SCRIPT_GOTO_JUMPDOWN, TRUE);
	CheckDlgButton(IDC_SCRIPT_GOTO_JUMPUP, FALSE);
	Spinbox_SetPos(GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWNLINE), 10);
	GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWN_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWNLINE)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPUP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPUPLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWNLINE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptGoToDialog::OnJumpLineUp()
{
	CheckDlgButton(IDC_SCRIPT_GOTO_LINE, FALSE);
	CheckDlgButton(IDC_SCRIPT_GOTO_JUMPDOWN, FALSE);
	CheckDlgButton(IDC_SCRIPT_GOTO_JUMPUP, TRUE);
	Spinbox_SetPos(GetDlgItem(IDC_SCRIPT_GOTO_JUMPUPLINE), 10);
	GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWNLINE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPUP_STATIC)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPUPLINE)->EnableWindow();
	GetDlgItem(IDC_SCRIPT_GOTO_JUMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_SCRIPT_GOTO_JUMPUPLINE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptGoToDialog::OnJump()
{
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_SCRIPT_GOTO_LINE)) ShowMessage((!GetParent()->GoToScriptCode(GetDlgItemInt(IDC_SCRIPT_GOTO_LINENUMBER, (LPBOOL)NULL, FALSE), FALSE, FALSE)) ? USER_INFORMATIONAL_SCRIPT_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_SCRIPT_GOTO_JUMPDOWN)) ShowMessage((!GetParent()->GoToScriptCode((UINT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWNLINE)), TRUE, FALSE)) ? USER_INFORMATIONAL_SCRIPT_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_SCRIPT_GOTO_JUMPUP)) ShowMessage((!GetParent()->GoToScriptCode((UINT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_GOTO_JUMPUPLINE)), FALSE, TRUE)) ? USER_INFORMATIONAL_SCRIPT_GOTO_LINE_FAILURE : USER_NOERROR);
}

void CScriptGoToDialog::OnEditchangeLineNumber()
{
	GetDlgItem(IDC_SCRIPT_GOTO_JUMP)->EnableWindow((GetDlgItem(IDC_SCRIPT_GOTO_LINENUMBER)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CScriptGoToDialog::OnOK()
{
	CHourglassCursor  cCursor;

	if (IsDlgButtonChecked(IDC_SCRIPT_GOTO_LINE)) ShowMessage((!GetParent()->GoToScriptCode(GetDlgItemInt(IDC_SCRIPT_GOTO_LINENUMBER, (LPBOOL)NULL, FALSE), FALSE, FALSE)) ? USER_INFORMATIONAL_SCRIPT_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_SCRIPT_GOTO_JUMPDOWN)) ShowMessage((!GetParent()->GoToScriptCode((UINT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_GOTO_JUMPDOWNLINE)), TRUE, FALSE)) ? USER_INFORMATIONAL_SCRIPT_GOTO_LINE_FAILURE : USER_NOERROR);
	if (IsDlgButtonChecked(IDC_SCRIPT_GOTO_JUMPUP)) ShowMessage((!GetParent()->GoToScriptCode((UINT)Spinbox_GetPos(GetDlgItem(IDC_SCRIPT_GOTO_JUMPUPLINE)), FALSE, TRUE)) ? USER_INFORMATIONAL_SCRIPT_GOTO_LINE_FAILURE : USER_NOERROR);
	GetParent()->SetFocus();
	CDisplayDialog::OnOK();
}

BOOL CScriptGoToDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTGOTODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CScriptGoToDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_SCRIPTGOTODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CScriptStatusBar

IMPLEMENT_DYNCREATE(CScriptStatusBar, CMFCStatusBar)

BOOL CScriptStatusBar::SetIndicators(CONST UINT *pIDs, INT nCount)
{
	INT  nIndex;
	CString  szText;

	for (Initialize(); CMFCStatusBar::SetIndicators(pIDs, nCount); )
	{
		if ((nIndex = CommandToIndex(ID_SCRIPT_STATUSBAR_SIZEPANE)) >= 0)
		{
			szText.Format(STRING(IDS_SCRIPT_STATUSBAR_SIZE), EMPTYSTRING);
			SetPaneInfo(nIndex, ID_SCRIPT_STATUSBAR_SIZEPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(nIndex, szText));
		}
		if ((nIndex = CommandToIndex(ID_SCRIPT_STATUSBAR_LINEPANE)) >= 0)
		{
			szText.Format(STRING(IDS_SCRIPT_STATUSBAR_LINE), 0);
			SetPaneInfo(nIndex, ID_SCRIPT_STATUSBAR_LINEPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_SCRIPT_STATUSBAR_LINEPANE));
		}
		if ((nIndex = CommandToIndex(ID_SCRIPT_STATUSBAR_COLUMNPANE)) >= 0)
		{
			szText.Format(STRING(IDS_SCRIPT_STATUSBAR_COLUMN), 0);
			SetPaneInfo(nIndex, ID_SCRIPT_STATUSBAR_COLUMNPANE, SBPS_NORMAL, CalcPaneWidth(nIndex, szText));
			SetTipText(nIndex, STRING(IDS_SCRIPT_STATUSBAR_COLUMNPANE));
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CScriptStatusBar::SetPaneText(UINT nID, LPCTSTR pszText)
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

BOOL CScriptStatusBar::GetPaneText(UINT nID, CString &szText) CONST
{
	INT  nIndex;

	if ((nIndex = CommandToIndex(nID)) >= 0)
	{
		szText = CMFCStatusBar::GetPaneText(nIndex);
		return TRUE;
	}
	return FALSE;
}
CString CScriptStatusBar::GetPaneText(UINT nID) CONST
{
	CString  szText;

	return((GetPaneText(nID, szText)) ? (LPCTSTR)szText : EMPTYSTRING);
}

INT CScriptStatusBar::CalcPaneWidth(INT nIndex) CONST
{
	return CalcPaneWidth(nIndex, CMFCStatusBar::GetPaneText(nIndex));
}
INT CScriptStatusBar::CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST
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

VOID CScriptStatusBar::Initialize()
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = GetCount(); nIndex < nCount; nIndex++)
	{
		SetTipText(nIndex, (LPCTSTR)NULL);
		continue;
	}
}

BEGIN_MESSAGE_MAP(CScriptStatusBar, CMFCStatusBar)
	//{{AFX_MSG_MAP(CScriptStatusBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptStatusBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CScriptCodeView

IMPLEMENT_DYNCREATE(CScriptCodeView, CRichEditView)

CScriptCodeView::CScriptCodeView() : CRichEditView()
{
	m_nWordWrap = WrapNone;
	m_bModified = FALSE;
}

BOOL CScriptCodeView::SetCode(CONST CAutomationScript *pScript)
{
	CString  szCode;
	CByteArray  nCode;

	for (GetWindowText(szCode); pScript->GetSourceCode() != szCode; )
	{
		pScript->GetSourceCode(nCode);
		return SetCode(nCode);
	}
	return TRUE;
}
BOOL CScriptCodeView::SetCode(CONST CByteArray &nCode)
{
	EDITSTREAM  sStream;

	for (sStream.dwCookie = (DWORD_PTR)&nCode, sStream.pfnCallback = SetCodeCallback, GetRichEditCtrl().StreamIn(SF_RTF, sStream); TRUE; )
	{
		GetWindowText(m_szCode);
		break;
	}
	return((!sStream.dwError) ? TRUE : FALSE);
}

BOOL CScriptCodeView::GetCode(CAutomationScript *pScript) CONST
{
	CString  szCode;
	CByteArray  nCode;

	if (GetCode(nCode))
	{
		GetWindowText(szCode);
		pScript->SetSourceCode(nCode);
		pScript->SetSourceCode(szCode);
		return TRUE;
	}
	return FALSE;
}
BOOL CScriptCodeView::GetCode(CByteArray &nCode) CONST
{
	EDITSTREAM  sStream;

	sStream.dwCookie = (DWORD_PTR)&nCode;
	sStream.pfnCallback = GetCodeCallback;
	GetRichEditCtrl().StreamOut(SF_RTF, sStream);
	return((!sStream.dwError) ? TRUE : FALSE);
}

INT CScriptCodeView::GetCodeSize() CONST
{
	return GetTextLength();
}

VOID CScriptCodeView::DoUndo()
{
	GetRichEditCtrl().Undo();
}

BOOL CScriptCodeView::CanUndo() CONST
{
	return((GetRichEditCtrl().CanUndo()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

VOID CScriptCodeView::DoRedo()
{
	GetRichEditCtrl().Redo();
}

BOOL CScriptCodeView::CanRedo() CONST
{
	return((GetRichEditCtrl().CanRedo()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

VOID CScriptCodeView::DoFindCode()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgFind.Create(GetParent()->GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CScriptCodeView::CanFindCode() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetCodeSize() > 0) ? TRUE : FALSE);
}

VOID CScriptCodeView::DoFindNextCode()
{
	LONG  nPos[2];
	CString  szText;

	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.GetDlgItem(IDC_SCRIPT_FIND_TEXT)->GetWindowText(szText), GetRichEditCtrl().GetSel(nPos[0], nPos[1]), nPos[0] = nPos[1] = nPos[0] + szText.GetLength(), GetRichEditCtrl().SetSel(nPos[0], nPos[1]); !szText.IsEmpty(); )
		{
			ShowMessage((!SearchCode(szText, TRUE, FALSE, m_dlgFind.IsDlgButtonChecked(IDC_SCRIPT_FIND_CASE), m_dlgFind.IsDlgButtonChecked(IDC_SCRIPT_FIND_WORD))) ? USER_INFORMATIONAL_SCRIPT_FIND_TEXT_NOTHING : USER_NOERROR);
			break;
		}
	}
}
VOID CScriptCodeView::DoFindNextCode(BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!SearchCode(GetRichEditCtrl().GetSelText(), TRUE, FALSE, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_SCRIPT_FIND_TEXT_NOTHING : USER_NOERROR);
}
VOID CScriptCodeView::DoFindNextCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!SearchCode(pszText, TRUE, bSearchAll, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_SCRIPT_FIND_TEXT_NOTHING : USER_NOERROR);
}

BOOL CScriptCodeView::CanFindNextCode() CONST
{
	return(((IsWindow(m_dlgFind.GetSafeHwnd()) || !GetRichEditCtrl().GetSelText().IsEmpty()) && GetCodeSize() > 0) ? TRUE : FALSE);
}

VOID CScriptCodeView::DoFindPreviousCode()
{
	CString  szText;

	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.GetDlgItem(IDC_SCRIPT_FIND_TEXT)->GetWindowText(szText); !szText.IsEmpty(); )
		{
			ShowMessage((!SearchCode(szText, FALSE, FALSE, m_dlgFind.IsDlgButtonChecked(IDC_SCRIPT_FIND_CASE), m_dlgFind.IsDlgButtonChecked(IDC_SCRIPT_FIND_WORD))) ? USER_INFORMATIONAL_SCRIPT_FIND_TEXT_NOTHING : USER_NOERROR);
			break;
		}
	}
}
VOID CScriptCodeView::DoFindPreviousCode(BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!SearchCode(GetRichEditCtrl().GetSelText(), FALSE, FALSE, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_SCRIPT_FIND_TEXT_NOTHING : USER_NOERROR);
}
VOID CScriptCodeView::DoFindPreviousCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	ShowMessage((!SearchCode(pszText, FALSE, bSearchAll, bMatchCase, bMatchWord)) ? USER_INFORMATIONAL_SCRIPT_FIND_TEXT_NOTHING : USER_NOERROR);
}

BOOL CScriptCodeView::CanFindPreviousCode() CONST
{
	return(((IsWindow(m_dlgFind.GetSafeHwnd()) || !GetRichEditCtrl().GetSelText().IsEmpty()) && GetCodeSize() > 0) ? TRUE : FALSE);
}

VOID CScriptCodeView::DoReplaceCode()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgReplace.Create(GetParent()->GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CScriptCodeView::CanReplaceCode() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetCodeSize() > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

VOID CScriptCodeView::DoGoToCode()
{
	CHourglassCursor  cCursor;

	ShowMessage((!m_dlgGoTo.Create(GetParent()->GetParent())) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CScriptCodeView::CanGoToCode() CONST
{
	return((!IsWindow(m_dlgFind.GetSafeHwnd()) && !IsWindow(m_dlgReplace.GetSafeHwnd()) && !IsWindow(m_dlgGoTo.GetSafeHwnd()) && GetCodeSize() > 0) ? TRUE : FALSE);
}

VOID CScriptCodeView::DoCutCode()
{
	GetRichEditCtrl().Cut();
}

BOOL CScriptCodeView::CanCutCode() CONST
{
	return((GetRichEditCtrl().GetSelectionType() != SEL_EMPTY) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

VOID CScriptCodeView::DoCopyCode()
{
	GetRichEditCtrl().Copy();
}

BOOL CScriptCodeView::CanCopyCode() CONST
{
	return((GetRichEditCtrl().GetSelectionType() != SEL_EMPTY) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

VOID CScriptCodeView::DoPasteCode()
{
	GetRichEditCtrl().Paste();
}

BOOL CScriptCodeView::CanPasteCode() CONST
{
	return((GetRichEditCtrl().CanPaste(CF_TEXT)) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

VOID CScriptCodeView::DoDeleteCode()
{
	LONG  nSel[2];

	for (GetRichEditCtrl().GetSel(nSel[0], nSel[1]); GetRichEditCtrl().GetSelectionType() == SEL_EMPTY; )
	{
		GetRichEditCtrl().SetSel(nSel[0], nSel[0] + 1);
		break;
	}
	GetRichEditCtrl().Clear();
}

BOOL CScriptCodeView::CanDeleteCode() CONST
{
	LONG  nSel[2];

	GetRichEditCtrl().GetSel(nSel[0], nSel[1]);
	return((GetRichEditCtrl().GetSelectionType() != SEL_EMPTY || nSel[0] < GetRichEditCtrl().GetTextLengthEx(GTL_PRECISE | GTL_NUMCHARS)) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

VOID CScriptCodeView::DoSelectAllCode()
{
	GetRichEditCtrl().SetSel(0, -1);
}

VOID CScriptCodeView::UnSelectAllCode()
{
	GetRichEditCtrl().SetSel(0, 0);
}

BOOL CScriptCodeView::CanSelectAllCode() CONST
{
	return((GetTextLength() > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

BOOL CScriptCodeView::SearchCode(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
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

BOOL CScriptCodeView::ReplaceCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	LONG  nSel[2];
	CString  szText;

	for (GetRichEditCtrl().GetSel(nSel[0], nSel[1]); nSel[0] < nSel[1] && nSel[1] - nSel[0] == lstrlen(pszText); )
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
	return SearchCode(pszText, bDown, bAll, bCase, bWord);
}

BOOL CScriptCodeView::ReplaceAllCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	LONG  nSel[2];

	for (GetRichEditCtrl().HideSelection(TRUE, TRUE), GetRichEditCtrl().GetSel(nSel[0], nSel[1]), GetRichEditCtrl().SetSel((bAll) ? ((!bDown) ? (GetRichEditCtrl().GetTextLength() - 1) : 0) : nSel[0], (bAll) ? ((!bDown) ? (GetRichEditCtrl().GetTextLength() - 1) : 0) : nSel[1]); TRUE; )
	{
		if (!ReplaceCode(pszText, pszReplaceText, bDown, FALSE, bCase, bWord)) break;
		continue;
	}
	GetRichEditCtrl().HideSelection(FALSE, TRUE);
	return TRUE;
}

BOOL CScriptCodeView::GoToCode(UINT nLine, BOOL bDown, BOOL bUp)
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
	return GoToCode((bDown) ? (GetRichEditCtrl().LineFromChar(-1) + nLine + 1) : (GetRichEditCtrl().LineFromChar(-1) - nLine + 1), FALSE, FALSE);
}
BOOL CScriptCodeView::GoToCode(LPCTSTR pszLine)
{
	INT  nPos;
	INT  nLength;
	CString  szKey;

	for (nPos = 0, nLength = lstrlen(pszLine); nPos < nLength; nPos++)
	{
		szKey.Format(STRING(IDS_AUTOMATIONSCRIPTLANGUAGE_COMPILEROUTPUT_SEARCHKEY), _ttoi(&pszLine[nPos]));
		if (_tcsstr(pszLine, szKey)) break;
	}
	return((nPos < nLength) ? GoToCode(_ttoi(&pszLine[nPos])) : FALSE);
}

INT CScriptCodeView::GetLinePosition() CONST
{
	LONG  nPos[2];

	GetRichEditCtrl().GetSel(nPos[0], nPos[1]);
	return((nPos[0] >= 0) ? (GetRichEditCtrl().LineFromChar(nPos[0]) + 1) : 1);
}

INT CScriptCodeView::GetColumnPosition() CONST
{
	INT  nIndex;
	LONG  nPos[2];

	GetRichEditCtrl().GetSel(nPos[0], nPos[1]);
	nIndex = GetRichEditCtrl().LineIndex(max(GetLinePosition() - 1, 0));
	return((nPos[0] >= 0) ? max(nPos[0] - nIndex + 1, 1) : 1);
}

VOID CScriptCodeView::ShowDialogs(BOOL bShow)
{
	if (IsWindow(m_dlgFind.GetSafeHwnd()))
	{
		for (m_dlgFind.ShowWindow((bShow) ? SW_SHOW : SW_HIDE); bShow; )
		{
			m_dlgFind.SetFocus();
			break;
		}
		return;
	}
	if (IsWindow(m_dlgReplace.GetSafeHwnd()))
	{
		for (m_dlgReplace.ShowWindow((bShow) ? SW_SHOW : SW_HIDE); bShow; )
		{
			m_dlgReplace.SetFocus();
			break;
		}
		return;
	}
	if (IsWindow(m_dlgGoTo.GetSafeHwnd()))
	{
		for (m_dlgGoTo.ShowWindow((bShow) ? SW_SHOW : SW_HIDE); bShow; )
		{
			m_dlgGoTo.SetFocus();
			break;
		}
		return;
	}
}

BOOL CScriptCodeView::HasDialogs() CONST
{
	return((IsWindow(m_dlgFind.GetSafeHwnd()) || IsWindow(m_dlgReplace.GetSafeHwnd()) || IsWindow(m_dlgGoTo.GetSafeHwnd())) ? TRUE : FALSE);
}

VOID CScriptCodeView::SetModified(BOOL bFlag)
{
	for (m_bModified = bFlag; !bFlag; )
	{
		GetWindowText(m_szCode);
		break;
	}
}

BOOL CScriptCodeView::IsModified() CONST
{
	CString  szCode;

	GetWindowText(szCode);
	return((m_szCode != szCode || m_bModified) ? TRUE : FALSE);
}

CScriptSplitterWnd *CScriptCodeView::GetParent() CONST
{
	return((CScriptSplitterWnd *)CRichEditView::GetParent());
}

DWORD CALLBACK CScriptCodeView::SetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	LONG  cbCode;
	CByteArray  *pCode = (CByteArray *)dwCookie;
	static LONG  nCode = 0;

	CopyMemory(pbBuff, pCode->GetData() + nCode, (cbCode = (LONG)max(min(pCode->GetSize() - nCode, cb), 0)));
	CopyMemory(pcb, &cbCode, sizeof(LONG));
	nCode = (nCode + cbCode < pCode->GetSize()) ? (nCode + cbCode) : 0;
	return 0;
}

DWORD CALLBACK CScriptCodeView::GetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	LONG  cbCode;
	CByteArray  *pCode = (CByteArray *)dwCookie;

	pCode->SetSize((cbCode = (LONG)pCode->GetSize()) + cb);
	CopyMemory(pCode->GetData() + cbCode, pbBuff, cb);
	CopyMemory(pcb, &cb, sizeof(LONG));
	return 0;
}

LRESULT CScriptCodeView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT  lResult;

	switch (message)
	{
	case WM_SETCURSOR:
	{ if (message == WM_SETCURSOR)
	{
		if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE))
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_ARROW));
			return TRUE;
		}
		break;
	}
	}
	case WM_SETFOCUS:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	{ if (CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE))
	{
		if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP || message == WM_KEYDOWN || message == WM_KEYUP)
		{
			lResult = CRichEditView::WindowProc(message, wParam, lParam);
			return lResult;
		}
		break;
	}
	if ((message != WM_KEYDOWN  &&  message != WM_KEYUP  &&  message != WM_CHAR) || (wParam != VK_HOME  &&  wParam != VK_END  &&  wParam != VK_UP  &&  wParam != VK_DOWN  &&  wParam != VK_PRIOR  &&  wParam != VK_NEXT  &&  wParam != VK_LEFT  &&  wParam != VK_RIGHT))
	{
		UnSelectAllCode();
		return FALSE;
	}
	}
	default: break;
	}
	return CRichEditView::WindowProc(message, wParam, lParam);
}

BEGIN_MESSAGE_MAP(CScriptCodeView, CRichEditView)
	//{{AFX_MSG_MAP(CScriptCodeView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_CONTROL_REFLECT(EN_CHANGE, OnEditchangeCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptCodeView drawing

void CScriptCodeView::OnDraw(CDC *pDC)
{
	return;
}

/////////////////////////////////////////////////////////////////////////////
// CScriptCodeView message handlers

int CScriptCodeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

void CScriptCodeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRichEditView::OnLButtonDown(nFlags, point);
	GetParent()->GetParent()->UpdateBars();
}

void CScriptCodeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_F3)
	{
		if (CanFindNextCode() && !HIBYTE(GetKeyState(VK_SHIFT))) DoFindNextCode();
		if (CanFindPreviousCode() && HIBYTE(GetKeyState(VK_SHIFT))) DoFindPreviousCode();
	}
	if (nChar == VK_UP)
	{
		if (HIBYTE(GetAsyncKeyState(VK_CONTROL)))
		{
			GetParent()->ActivateNext(TRUE);
			return;
		}
	}
	for (; nChar == VK_INSERT; )
	{
		GetParent()->GetParent()->DoToggleKey();
		return;
	}
	CRichEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CScriptCodeView::OnEditchangeCode()
{
	CScriptCodeEdit::RenderCode(&GetRichEditCtrl(), &m_cCodeFont);
	GetParent()->GetParent()->UpdateBars();
}


/////////////////////////////////////////////////////////////////////////////
// CScriptImageView

IMPLEMENT_DYNCREATE(CScriptImageView, CScrollView)

CScriptImageView::CScriptImageView() : CScrollView()
{
	m_nScriptType = AUTOMATIONSCRIPT_TYPE_NONE;
	m_rScriptOutput[0].SetRectEmpty();
	m_rScriptOutput[1].SetRectEmpty();
	m_bModified = FALSE;
}

BOOL CScriptImageView::SetImage(CONST CAutomationScript *pScript)
{
	m_nScriptType = pScript->GetType();
	m_szScriptFileName = pScript->GetOutputFileName();
	return TRUE;
}

BOOL CScriptImageView::GetImage(CAutomationScript *pScript) CONST
{
	pScript->SetType(m_nScriptType);
	pScript->SetOutputFileName(m_szScriptFileName);
	return TRUE;
}

VOID CScriptImageView::UpdateImage()
{
	CAutomationScript  cScript;

	cScript.SetType(m_nScriptType);
	cScript.SetOutputFileName(m_szScriptFileName);
	UpdateImage(&cScript);
}
VOID CScriptImageView::UpdateImage(CONST CAutomationScript *pScript)
{
	CLSID  clsid;
	CString  szMessage;
	CFileFindEx  cFileFind;
	CScriptDocumentItem  *pItem;

	if (pScript->GetType() == AUTOMATIONSCRIPT_TYPE_NONE || m_nScriptType != AUTOMATIONSCRIPT_TYPE_NONE)
	{
		if (pScript->GetType() == AUTOMATIONSCRIPT_TYPE_NONE)
		{
			m_nScriptType = AUTOMATIONSCRIPT_TYPE_NONE;
			m_szScriptFileName = EMPTYSTRING;
		}
		SetScrollSizes(MM_TEXT, CSize(0, 0));
		GetDocument()->DeleteContents();
	}
	if (cFileFind.FindFile(pScript->GetOutputFileName()) && !cFileFind.FindNextFile())
	{
		if (pScript->GetType() == AUTOMATIONSCRIPT_TYPE_EXCEL)
		{
			if ((pItem = new CScriptDocumentItem(GetDocument())))
			{
				if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName()))
				{
					SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
					GetDocument()->UpdateAllViews(NULL);
					SetImage(pScript);
					cFileFind.Close();
					Invalidate(TRUE);
					UpdateWindow();
					return;
				}
				if (SUCCEEDED(CLSIDFromProgID(COleVariant(STRING(IDS_AUTOMATIONSCRIPT_OBJECTTYPE_EXCEL)).bstrVal, &clsid)))
				{
					if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName(), clsid))
					{
						SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
						GetDocument()->UpdateAllViews(NULL);
						SetImage(pScript);
						cFileFind.Close();
						Invalidate(TRUE);
						UpdateWindow();
						return;
					}
				}
				delete pItem;
			}
			szMessage.Format(STRING(IDS_AUTOMATIONSCRIPT_RENDERING_ERROR), (LPCTSTR)pScript->GetTitle());
			ShowMessage(szMessage);
		}
		if (pScript->GetType() == AUTOMATIONSCRIPT_TYPE_WORD)
		{
			if ((pItem = new CScriptDocumentItem(GetDocument())))
			{
				if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName()))
				{
					SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
					GetDocument()->UpdateAllViews(NULL);
					SetImage(pScript);
					cFileFind.Close();
					Invalidate(TRUE);
					UpdateWindow();
					return;
				}
				if (SUCCEEDED(CLSIDFromProgID(COleVariant(STRING(IDS_AUTOMATIONSCRIPT_OBJECTTYPE_WORD)).bstrVal, &clsid)))
				{
					if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName(), clsid))
					{
						SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
						GetDocument()->UpdateAllViews(NULL);
						SetImage(pScript);
						cFileFind.Close();
						Invalidate(TRUE);
						UpdateWindow();
						return;
					}
				}
				delete pItem;
			}
			szMessage.Format(STRING(IDS_AUTOMATIONSCRIPT_RENDERING_ERROR), (LPCTSTR)pScript->GetTitle());
			ShowMessage(szMessage);
		}
		if (pScript->GetType() == AUTOMATIONSCRIPT_TYPE_ACCESS)
		{
			if ((pItem = new CScriptDocumentItem(GetDocument())))
			{
				if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName()))
				{
					SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
					GetDocument()->UpdateAllViews(NULL);
					SetImage(pScript);
					cFileFind.Close();
					Invalidate(TRUE);
					UpdateWindow();
					return;
				}
				if (SUCCEEDED(CLSIDFromProgID(COleVariant(STRING(IDS_AUTOMATIONSCRIPT_OBJECTTYPE_ACCESS)).bstrVal, &clsid)))
				{
					if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName(), clsid))
					{
						SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
						GetDocument()->UpdateAllViews(NULL);
						SetImage(pScript);
						cFileFind.Close();
						Invalidate(TRUE);
						UpdateWindow();
						return;
					}
				}
				delete pItem;
			}
			szMessage.Format(STRING(IDS_AUTOMATIONSCRIPT_RENDERING_ERROR), (LPCTSTR)pScript->GetTitle());
			ShowMessage(szMessage);
		}
		if (pScript->GetType() == AUTOMATIONSCRIPT_TYPE_OUTLOOK)
		{
			if ((pItem = new CScriptDocumentItem(GetDocument())))
			{
				if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName()))
				{
					SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
					GetDocument()->UpdateAllViews(NULL);
					SetImage(pScript);
					cFileFind.Close();
					Invalidate(TRUE);
					UpdateWindow();
					return;
				}
				if (SUCCEEDED(CLSIDFromProgID(COleVariant(STRING(IDS_AUTOMATIONSCRIPT_OBJECTTYPE_OUTLOOK)).bstrVal, &clsid)))
				{
					if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName(), clsid))
					{
						SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
						GetDocument()->UpdateAllViews(NULL);
						SetImage(pScript);
						cFileFind.Close();
						Invalidate(TRUE);
						UpdateWindow();
						return;
					}
				}
				delete pItem;
			}
			szMessage.Format(STRING(IDS_AUTOMATIONSCRIPT_RENDERING_ERROR), (LPCTSTR)pScript->GetTitle());
			ShowMessage(szMessage);
		}
		if (pScript->GetType() == AUTOMATIONSCRIPT_TYPE_POWERPOINT)
		{
			if ((pItem = new CScriptDocumentItem(GetDocument())))
			{
				if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName()))
				{
					SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
					GetDocument()->UpdateAllViews(NULL);
					SetImage(pScript);
					cFileFind.Close();
					Invalidate(TRUE);
					UpdateWindow();
					return;
				}
				if (SUCCEEDED(CLSIDFromProgID(COleVariant(STRING(IDS_AUTOMATIONSCRIPT_OBJECTTYPE_POWERPOINT)).bstrVal, &clsid)))
				{
					if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName(), clsid))
					{
						SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
						GetDocument()->UpdateAllViews(NULL);
						SetImage(pScript);
						cFileFind.Close();
						Invalidate(TRUE);
						UpdateWindow();
						return;
					}
				}
				delete pItem;
			}
			szMessage.Format(STRING(IDS_AUTOMATIONSCRIPT_RENDERING_ERROR), (LPCTSTR)pScript->GetTitle());
			ShowMessage(szMessage);
		}
		if (pScript->GetType() == AUTOMATIONSCRIPT_TYPE_OTHER)
		{
			if ((pItem = new CScriptDocumentItem(GetDocument())))
			{
				if (CheckImageFile(pScript) && pItem->CreateFromFile(pScript->GetOutputFileName()))
				{
					SetScrollSizes(MM_TEXT, CalcImageSize(pItem));
					GetDocument()->UpdateAllViews(NULL);
					SetImage(pScript);
					cFileFind.Close();
					Invalidate(TRUE);
					UpdateWindow();
					return;
				}
				delete pItem;
			}
			szMessage.Format(STRING(IDS_AUTOMATIONSCRIPT_RENDERING_ERROR), (LPCTSTR)pScript->GetTitle());
			ShowMessage(szMessage);
		}
		cFileFind.Close();
	}
	GetDocument()->UpdateAllViews(NULL);
	Invalidate(TRUE);
	UpdateWindow();
}

BOOL CScriptImageView::HasImage() CONST
{
	CScriptDocument  *pDocument;

	return(((pDocument = GetDocument()) && pDocument->GetStartPosition() != (POSITION)NULL) ? TRUE : FALSE);
}

VOID CScriptImageView::PrintInsideRect(CDC *pDC, CONST RECT &rect)
{
	CSize  sizeItem;
	double  fHorzScale;
	double  fVertScale;
	POSITION  lPosition;
	CScriptDocument  *pDocument;
	CScriptDocumentItem  *pItem;

	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CScriptDocumentItem *)pDocument->GetNextClientItem(lPosition)))
		{
			sizeItem = CalcImageSize(pItem);
			fHorzScale = (double)(rect.right - rect.left) / (double)sizeItem.cx;
			fVertScale = (double)(rect.bottom - rect.top) / (double)sizeItem.cy;
			sizeItem.cx = (fHorzScale <= fVertScale) ? (INT)(sizeItem.cx*fHorzScale) : (INT)(sizeItem.cx*fVertScale);
			sizeItem.cy = (fHorzScale <= fVertScale) ? (INT)(sizeItem.cy*fHorzScale) : (INT)(sizeItem.cy*fVertScale);
			pItem->Draw(pDC, CRect(rect.left, rect.top, rect.left + sizeItem.cx, rect.top + sizeItem.cy));
			break;
		}
	}
}

VOID CScriptImageView::SetModified(BOOL bFlag)
{
	m_bModified = bFlag;
}

BOOL CScriptImageView::IsModified() CONST
{
	return m_bModified;
}

CScriptDocument *CScriptImageView::GetDocument() CONST
{
	return((CScriptDocument *)CScrollView::GetDocument());
}

CScriptSplitterWnd *CScriptImageView::GetParent() CONST
{
	return((CScriptSplitterWnd *)CScrollView::GetParent());
}

BOOL CScriptImageView::CheckImageFile(CONST CAutomationScript *pScript)
{
	CFileEx  cFile;

	if (cFile.Open(pScript->GetOutputFileName(), CFile::modeRead))
	{
		if (cFile.GetLength() > 0)
		{
			cFile.Close();
			return TRUE;
		}
		cFile.Close();
	}
	return FALSE;
}

CSize CScriptImageView::CalcImageSize(CScriptDocumentItem *pItem)
{
	CDC  *pDC;
	CSize  sizeItem;

	if ((pDC = GetDC()))
	{
		if (pItem->GetExtent(&sizeItem))
		{
			sizeItem.cx = (INT)(((double)sizeItem.cx*(double)pDC->GetDeviceCaps(HORZRES)) / (100.0*(double)pDC->GetDeviceCaps(HORZSIZE)));
			sizeItem.cy = (INT)(((double)sizeItem.cy*(double)pDC->GetDeviceCaps(VERTRES)) / (100.0*(double)pDC->GetDeviceCaps(VERTSIZE)));
			ReleaseDC(pDC);
			return sizeItem;
		}
		ReleaseDC(pDC);
	}
	return CSize(0, 0);
}

LRESULT CScriptImageView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDBLCLK:
	{ if (CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE)) break;
	return FALSE;
	}
	default: break;
	}
	return CScrollView::WindowProc(message, wParam, lParam);
}

BEGIN_MESSAGE_MAP(CScriptImageView, CScrollView)
	//{{AFX_MSG_MAP(CScriptImageView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptImageView drawing

void CScriptImageView::OnDraw(CDC *pDC)
{
	POSITION  lPosition;
	CScriptDocument  *pDocument;
	CScriptDocumentItem  *pItem;

	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CScriptDocumentItem *)pDocument->GetNextClientItem(lPosition)))
		{
			pItem->Draw(pDC, CRect(0, 0, GetTotalSize().cx, GetTotalSize().cy));
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScriptImageView message handlers

int CScriptImageView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) != -1)
	{
		UpdateImage();
		return 0;
	}
	return -1;
}

void CScriptImageView::OnSize(UINT nType, int cx, int cy)
{
	CRect  rView;

	for (GetWindowRect(rView); m_rScriptOutput[1].TopLeft() == rView.TopLeft(); )
	{
		InvalidateRect((LPCRECT)NULL);
		ValidateRect(m_rScriptOutput[0]);
		break;
	}
	UpdateWindow();
	m_rScriptOutput[1] = rView;
	m_rScriptOutput[0].SetRect(0, 0, cx, cy);
	CScrollView::OnSize(nType, cx, cy);
}

void CScriptImageView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CRect  rItem;
	POSITION  lPosition;
	CScriptDocument  *pDocument;
	CScriptDocumentItem  *pItem;

	for (rItem.SetRect(0, 0, GetTotalSize().cx, GetTotalSize().cy), lPosition = ((pDocument = GetDocument()) && rItem.PtInRect(point)) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CScriptDocumentItem *)pDocument->GetNextClientItem(lPosition)))
		{
			pItem->Activate(OLEIVERB_OPEN, (CView *)NULL);
			break;
		}
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CScriptImageView::OnDestroy()
{
	delete GetDocument();
	CScrollView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CScriptSplitterWnd

IMPLEMENT_DYNCREATE(CScriptSplitterWnd, CSplitterWndEx)

CScriptSplitterWnd::CScriptSplitterWnd() : CSplitterWndEx()
{
	m_pDocument = (CScriptDocument *)NULL;
}

BOOL CScriptSplitterWnd::Create(CScriptWnd *pParentWnd)
{
	CRect  rPanes;
	CCreateContext  cContext;

	if (CreateStatic(pParentWnd, 2, 1))
	{
		if ((m_pDocument = new CScriptDocument))
		{
			for (pParentWnd->GetClientRect(rPanes), cContext.m_pCurrentDoc = m_pDocument; CreateView(0, 0, RUNTIME_CLASS(CScriptCodeView), CSize(rPanes.Width(), 3 * rPanes.Height() / 4), &cContext) && CreateView(1, 0, RUNTIME_CLASS(CScriptImageView), CSize(rPanes.Width(), rPanes.Height() - 3 * rPanes.Height() / 4), &cContext); )
			{
				SetActivePane(0, 0, GetCodeView());
				return TRUE;
			}
			delete m_pDocument;
			m_pDocument = (CScriptDocument *)NULL;
		}
	}
	return FALSE;
}

VOID CScriptSplitterWnd::DoUndo()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoUndo();
		return;
	}
}

BOOL CScriptSplitterWnd::CanUndo() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanUndo() : FALSE);
}

VOID CScriptSplitterWnd::DoRedo()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoRedo();
		return;
	}
}

BOOL CScriptSplitterWnd::CanRedo() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanRedo() : FALSE);
}

VOID CScriptSplitterWnd::DoFind()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoFindCode();
		return;
	}
}

BOOL CScriptSplitterWnd::CanFind() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanFindCode() : FALSE);
}

VOID CScriptSplitterWnd::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoFindNextCode(bMatchCase, bMatchWord);
		return;
	}
}
VOID CScriptSplitterWnd::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoFindNextCode(pszText, bSearchAll, bMatchCase, bMatchWord);
		return;
	}
}

BOOL CScriptSplitterWnd::CanFindNext() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanFindNextCode() : FALSE);
}

VOID CScriptSplitterWnd::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoFindPreviousCode(bMatchCase, bMatchWord);
		return;
	}
}
VOID CScriptSplitterWnd::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoFindPreviousCode(pszText, bSearchAll, bMatchCase, bMatchWord);
		return;
	}
}

BOOL CScriptSplitterWnd::CanFindPrevious() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanFindPreviousCode() : FALSE);
}

VOID CScriptSplitterWnd::DoReplace()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoReplaceCode();
		return;
	}
}

BOOL CScriptSplitterWnd::CanReplace() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanReplaceCode() : FALSE);
}

VOID CScriptSplitterWnd::DoGoTo()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoGoToCode();
		return;
	}
}

BOOL CScriptSplitterWnd::CanGoTo() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanGoToCode() : FALSE);
}

VOID CScriptSplitterWnd::DoCutSel()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoCutCode();
		return;
	}
}

BOOL CScriptSplitterWnd::CanCutSel() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanCutCode() : FALSE);
}

VOID CScriptSplitterWnd::DoCopySel()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoCopyCode();
		return;
	}
}

BOOL CScriptSplitterWnd::CanCopySel() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanCopyCode() : FALSE);
}

VOID CScriptSplitterWnd::DoPasteSel()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoPasteCode();
		return;
	}
}

BOOL CScriptSplitterWnd::CanPasteSel() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanPasteCode() : FALSE);
}

VOID CScriptSplitterWnd::DoDeleteSel()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoDeleteCode();
		return;
	}
}

BOOL CScriptSplitterWnd::CanDeleteSel() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanDeleteCode() : FALSE);
}

VOID CScriptSplitterWnd::DoSelectAll()
{
	CView  *pView;

	if ((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView)))
	{
		GetCodeView()->DoSelectAllCode();
		return;
	}
}

VOID CScriptSplitterWnd::UnSelectAll()
{
	GetCodeView()->UnSelectAllCode();
	GetParent()->UpdateBars();
}

BOOL CScriptSplitterWnd::CanSelectAll() CONST
{
	CView  *pView;

	return(((pView = GetActivePane()) && pView->IsKindOf(RUNTIME_CLASS(CScriptCodeView))) ? GetCodeView()->CanSelectAllCode() : FALSE);
}

CView *CScriptSplitterWnd::GetActivePane() CONST
{
	CView  *pView;

	return(((pView = (GetParentFrame()->GetActiveView()) ? (CView *)GetParentFrame()->GetActiveView() : (CView *)GetFocus()) && (pView == GetCodeView() || pView == GetImageView())) ? pView : (CView *)NULL);
}

CScriptCodeView *CScriptSplitterWnd::GetCodeView() CONST
{
	return((IsWindow(GetDlgItem(IdFromRowCol(0, 0))->GetSafeHwnd())) ? (CScriptCodeView *)GetPane(0, 0) : (CScriptCodeView *)NULL);
}

CScriptImageView *CScriptSplitterWnd::GetImageView() CONST
{
	return((IsWindow(GetDlgItem(IdFromRowCol(1, 0))->GetSafeHwnd())) ? (CScriptImageView *)GetPane(1, 0) : (CScriptImageView *)NULL);
}

CScriptWnd *CScriptSplitterWnd::GetParent() CONST
{
	return((CScriptWnd *)CSplitterWndEx::GetParent());
}

BEGIN_MESSAGE_MAP(CScriptSplitterWnd, CSplitterWndEx)
	//{{AFX_MSG_MAP(CScriptSplitterWnd)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptSplitterWnd message handlers

void CScriptSplitterWnd::OnDestroy()
{
	delete m_pDocument;
	CSplitterWndEx::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CScriptCompileThread

IMPLEMENT_DYNAMIC(CScriptCompileThread, CThread)

CScriptCompileThread::CScriptCompileThread() : CThread()
{
	m_nErrors = 0;
	m_nWarnings = 0;
	m_bAbort = FALSE;
	m_bStop = FALSE;
}

BOOL CScriptCompileThread::StartCompiling(CBinaryDatabase *pDatabase, CONST CAutomationScript *pScript)
{
	for (SetAbortStatus(), SetCompileTarget(pDatabase, pScript, FALSE, FALSE), m_bCompilation[0].ResetEvent(), m_bCompilation[1].ResetEvent(); CreateThread((LPVOID)pDatabase, THREAD_PRIORITY_BELOW_NORMAL); )
	{
		WaitForSingleObject(m_bCompilation[0], INFINITE);
		return TRUE;
	}
	return FALSE;
}
BOOL CScriptCompileThread::StartCompiling(CBinaryDatabase *pDatabase, CONST CAutomationScript *pScript, BOOL bSyntax, BOOL bBatch, INT &nErrors, INT &nWarnings, BOOL &bAbort)
{
	for (SetAbortStatus(), SetCompileTarget(pDatabase, pScript, bSyntax, bBatch), m_bCompilation[0].ResetEvent(), m_bCompilation[1].ResetEvent(), nErrors = nWarnings = 0; CreateThread((LPVOID)pDatabase, THREAD_PRIORITY_BELOW_NORMAL); )
	{
		for (WaitForSingleObject(m_bCompilation[0], INFINITE); bBatch; )
		{
			WaitForSingleObject(m_bCompilation[1], INFINITE);
			break;
		}
		nErrors = GetErrorCount();
		nWarnings = GetWarningCount();
		bAbort = GetAbortStatus();
		return TRUE;
	}
	return FALSE;
}

BOOL CScriptCompileThread::IsCompiling() CONST
{
	return((IsThreadActive()) ? (!m_bStop  &&  !m_bAbort) : FALSE);
}

BOOL CScriptCompileThread::StopCompiling()
{
	if (IsCompiling())
	{
		ShowCompileMessage(STRING(IDS_COMPILER_MESSAGE_BREAKCOMPILING));
		SetAbortStatus(TRUE);
		DestroyThread();
		return TRUE;
	}
	return FALSE;
}

VOID CScriptCompileThread::SetCompileTarget(CONST CBinaryDatabase *pDatabase, CONST CAutomationScript *pScript, BOOL bSyntax, BOOL bBatch)
{
	CString  szFileName[3];
	CFileFindEx  cFileFind[2];

	for (m_cScript.Copy(pScript), m_cScript.SetExecutableFileName(EMPTYSTRING), m_bSyntax = bSyntax, m_bBatch = bBatch, szFileName[0] = pDatabase->GetFileName(), szFileName[1] = pDatabase->GetUpdateFileName(); (cFileFind[0].FindFile(szFileName[0]) || cFileFind[0].FindFile(szFileName[1])) && !cFileFind[0].FindNextFile(); )
	{
		szFileName[0].Format(STRING(IDS_SCRIPTDISPLAYCODE_NORMAL_FILENAME), (LPCTSTR)pScript->GetName());
		szFileName[1].Format(STRING(IDS_SCRIPTDISPLAYCODE_UPDATE_FILENAME), (LPCTSTR)pScript->GetName());
		szFileName[2].Format(STRING(IDS_SCRIPTDISPLAYCODE_TEMPORARY_FILENAME), (LPCTSTR)pScript->GetName());
		szFileName[0] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szFileName[0];
		szFileName[1] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szFileName[1];
		szFileName[2] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szFileName[2];
		if (cFileFind[1].FindFile(szFileName[0]) && !cFileFind[1].FindNextFile())
		{
			szFileName[1] = (!bSyntax) ? szFileName[1] : szFileName[2];
			m_cScript.SetExecutableFileName(szFileName[1]);
			cFileFind[1].Close();
			cFileFind[0].Close();
			break;
		}
		szFileName[0] = (!bSyntax) ? szFileName[0] : szFileName[2];
		m_cScript.SetExecutableFileName(szFileName[0]);
		cFileFind[0].Close();
		break;
	}
}

VOID CScriptCompileThread::GetCompileTarget(CAutomationScript *pScript) CONST
{
	pScript->Copy(&m_cScript);
}

BOOL CScriptCompileThread::IsSyntaxCompileTarget() CONST
{
	return m_bSyntax;
}

BOOL CScriptCompileThread::IsBatchCompileTarget() CONST
{
	return m_bBatch;
}

int CScriptCompileThread::Run()
{
	CUpdateUI  cUpdateUI;

	for (SetErrorCount(), SetWarningCount(), ShowStartCompileMessages(); TRUE; )
	{
		CompileTarget();
		break;
	}
	ShowStopCompileMessages();
	return 0;
}

VOID CScriptCompileThread::CompileTarget()
{
	INT  nError;
	INT  nErrors;
	INT  nWarning;
	INT  nWarnings;
	CString  szName;
	CString  szCode;
	CString  szError;
	CString  szExports;
	CString  szFileName;
	LPCTSTR  pszKeyword;
	CStringArray  szErrors;
	CStringArray  szWarnings;
	CJScriptCodeGenerator  cJScriptCodeGenerator;

	for (m_bCompilation[0].SetEvent(), szName.Format(STRING(IDS_SCRIPTLANGUAGE_CODE_NAME), (LPCTSTR)m_cScript.GetName()), szCode = szExports = m_cScript.GetSourceCode(), szFileName = m_cScript.GetExecutableFileName(); (pszKeyword = _tcsstr(szExports, STRING(IDS_SCRIPTLANGUAGE_KEYWORD_EXPORTSLIBRARY))); )
	{
		szExports = szExports.Left(lstrlen(szExports) - lstrlen(pszKeyword)) + CString(SPACE[0], lstrlen(STRING(IDS_SCRIPTLANGUAGE_KEYWORD_EXPORTSLIBRARY))) + szExports.Mid(lstrlen(szExports) - lstrlen(pszKeyword) + lstrlen(STRING(IDS_SCRIPTLANGUAGE_KEYWORD_EXPORTSLIBRARY)));
		szCode.Empty();
	}
	if (cJScriptCodeGenerator.Compile(szName, szCode, szExports, EMPTYSTRING, szFileName, szErrors, szWarnings))
	{
		for (nError = 0, nErrors = (INT)szErrors.GetSize(); nError < nErrors; nError++)
		{
			ShowError(szErrors.GetAt(nError));
			continue;
		}
		for (nWarning = 0, nWarnings = (INT)szWarnings.GetSize(); nWarning < nWarnings; nWarning++)
		{
			ShowWarning(szWarnings.GetAt(nWarning));
			continue;
		}
		if (IsSyntaxCompileTarget())
		{
			CFileEx::SetAttributes(m_cScript.GetExecutableFileName(), CFileEx::GetAttributes(m_cScript.GetExecutableFileName()) & ~FILE_ATTRIBUTE_READONLY);
			CFileEx::Remove(m_cScript.GetExecutableFileName());
		}
		m_bCompilation[1].SetEvent();
		return;
	}
	for (szError.Format(STRING(IDS_AUTOMATIONSCRIPTLANGUAGE_COMPILERERROR_GENERAL), (LPCTSTR)m_cScript.GetName()); TRUE; )
	{
		ShowError(szError);
		break;
	}
	if (IsSyntaxCompileTarget())
	{
		CFileEx::SetAttributes(m_cScript.GetExecutableFileName(), CFileEx::GetAttributes(m_cScript.GetExecutableFileName()) & ~FILE_ATTRIBUTE_READONLY);
		CFileEx::Remove(m_cScript.GetExecutableFileName());
	}
	m_bCompilation[1].SetEvent();
}

VOID CScriptCompileThread::ShowStartCompileMessages()
{
	CString  szMessage[2];
	CRecentDocumentInfo  cDocument;
	CUpdateUI  cUpdateUI;

	for (SetConsoleContext(STRING(IDS_OUTPUTWINDOW_BUILDTAB), &cDocument), szMessage[0].Format(STRING(IDS_COMPILER_MESSAGE_FORMAT), (LPCTSTR)GetDatabase()->GetName()), szMessage[1].Format(STRING(IDS_COMPILER_MESSAGE_COMPILING_AUTOMATIONSCRIPT), (LPCTSTR)m_cScript.GetName()); !IsBatchCompileTarget(); )
	{
		ResetConsoleContent(STRING(IDS_OUTPUTWINDOW_BUILDTAB));
		ShowCompileMessage(szMessage[0]);
		break;
	}
	ShowCompileMessage(szMessage[1]);
	cDocument.SetDocument(m_cScript.GetName(), EMPTYSTRING, DATABASE_COMPONENT_SCRIPT);
	SetConsoleContext(STRING(IDS_OUTPUTWINDOW_BUILDTAB), &cDocument);
}

VOID CScriptCompileThread::ShowStopCompileMessages()
{
	CString  szMessage;
	CRecentDocumentInfo  cDocument;
	CUpdateUI  cUpdateUI;

	for (SetConsoleContext(STRING(IDS_OUTPUTWINDOW_BUILDTAB), &cDocument), szMessage.Format(STRING(IDS_COMPILER_MESSAGE_STOPCOMPILING), GetErrorCount(), GetWarningCount()), InterlockedExchange(&m_bStop, TRUE); !IsBatchCompileTarget(); )
	{
		ShowCompileMessage((!GetAbortStatus()) ? (LPCTSTR)szMessage : STRING(IDS_COMPILER_MESSAGE_ABORTCOMPILING), TRUE, TRUE);
		break;
	}
}

VOID CScriptCompileThread::ShowCompileMessage(LPCTSTR pszMessage, BOOL bTimestamp, BOOL bAudition)
{
	ShowConsoleText(STRING(IDS_OUTPUTWINDOW_BUILDTAB), pszMessage, bTimestamp, (!IsBatchCompileTarget()) ? bAudition : FALSE);
}

VOID CScriptCompileThread::ShowError(LPCTSTR pszError)
{
	ShowCompileMessage(CString(STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX)) + pszError);
	SetErrorCount(GetErrorCount() + 1);
}

VOID CScriptCompileThread::ShowWarning(LPCTSTR pszWarning)
{
	ShowCompileMessage(CString(STRING(IDS_COMPILER_MESSAGE_WARNING_PREFIX)) + pszWarning);
	SetWarningCount(GetWarningCount() + 1);
}

VOID CScriptCompileThread::SetErrorCount(UINT nCount)
{
	m_nErrors = nCount;
}

UINT CScriptCompileThread::GetErrorCount() CONST
{
	return m_nErrors;
}

VOID CScriptCompileThread::SetWarningCount(UINT nCount)
{
	m_nWarnings = nCount;
}

UINT CScriptCompileThread::GetWarningCount() CONST
{
	return m_nWarnings;
}

VOID CScriptCompileThread::SetAbortStatus(BOOL bAbort)
{
	InterlockedExchange(&m_bAbort, bAbort);
	InterlockedExchange(&m_bStop, (bAbort) ? m_bStop : FALSE);
}

BOOL CScriptCompileThread::GetAbortStatus() CONST
{
	return m_bAbort;
}

BEGIN_MESSAGE_MAP(CScriptCompileThread, CThread)
	//{{AFX_MSG_MAP(CScriptCompileThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptCompileThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CScriptWnd

CScriptCompileThread  CScriptWnd::m_cCompileThread;

IMPLEMENT_DYNCREATE(CScriptWnd, CDisplayWnd)

CScriptWnd::CScriptWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_SCRIPT);
	SetTitle(STRING(IDS_WINDOW_UNTITLED));
}
CScriptWnd::CScriptWnd(LPCTSTR pszName) : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_SCRIPT);
	SetTitle(STRING(IDS_WINDOW_UNTITLED));
	SetName(pszName);
}

BOOL CScriptWnd::Create(CMDIFrameWnd *pParentWnd, UINT nShow)
{
	CRect  rPosition[2];

	for (rPosition[0] = m_rPosition; CDisplayWnd::Create(pParentWnd, EMPTYSTRING, (nShow == (UINT)-1) ? CRect(CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT) : CRect(0, 0, 0, 0), IDR_SCRIPTFRAME, (nShow != SW_SHOWMINIMIZED || nShow != SW_SHOWMAXIMIZED) ? (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE) : (WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW)); )
	{
		for (GetWindowRect(rPosition[1]), GetParent()->ScreenToClient(rPosition[1]), MoveWindow(0, 0, 0, 0), MoveWindow((nShow != (UINT)-1) ? rPosition[0] : rPosition[1]), ShowWindow((nShow == SW_SHOWMAXIMIZED || nShow == SW_SHOWMINIMIZED || nShow == (UINT)-1) ? SW_SHOWNORMAL : nShow); nShow == SW_SHOWMAXIMIZED || nShow == SW_SHOWMINIMIZED; )
		{
			ShowWindow(nShow);
			break;
		}
		UpdateTitle();
		UpdateImage();
		UpdateMenus();
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}

VOID CScriptWnd::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CScriptWnd::GetName() CONST
{
	return m_szName;
}

VOID CScriptWnd::SetTitle(LPCTSTR pszTitle)
{
	for (m_szTitle = pszTitle; IsWindow(GetSafeHwnd()); )
	{
		m_cScript.SetTitle(pszTitle);
		UpdateTitle();
		break;
	}
}

CString CScriptWnd::GetTitle() CONST
{
	return m_szTitle;
}

VOID CScriptWnd::SetScript(CONST CAutomationScript *pScript)
{
	if (!m_cScript.Compare(pScript))
	{
		for (; GetCodeView()->SetCode(pScript) && GetImageView()->SetImage(pScript); )
		{
			GetImageView()->UpdateImage(pScript);
			m_cScript.Copy(pScript);
			break;
		}
		GetCodeView()->SetModified();
		GetImageView()->SetModified();
	}
}

BOOL CScriptWnd::GetScript(CAutomationScript *pScript) CONST
{
	return((pScript->Copy(&m_cScript) && GetCodeView()->GetCode(pScript) && GetImageView()->GetImage(pScript)) ? TRUE : FALSE);
}

BOOL CScriptWnd::SearchScriptCode(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return GetCodeView()->SearchCode(pszText, bDown, bAll, bCase, bWord);
}

BOOL CScriptWnd::ReplaceScriptCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return GetCodeView()->ReplaceCode(pszText, pszReplaceText, bDown, bAll, bCase, bWord);
}

BOOL CScriptWnd::ReplaceAllScriptCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return GetCodeView()->ReplaceAllCode(pszText, pszReplaceText, bDown, bAll, bCase, bWord);
}

BOOL CScriptWnd::GoToScriptCode(UINT nLine, BOOL bDown, BOOL bUp)
{
	return GetCodeView()->GoToCode(nLine, bDown, bUp);
}
BOOL CScriptWnd::GoToScriptCode(LPCTSTR pszLine)
{
	return GetCodeView()->GoToCode(pszLine);
}

BOOL CScriptWnd::IsNew() CONST
{
	return m_szName.IsEmpty();
}

BOOL CScriptWnd::IsModified() CONST
{
	return GetCodeView()->IsModified() || GetImageView()->IsModified();
}

BOOL CScriptWnd::Save(INT nPosition) CONST
{
	INT  nPane[2][2];
	UINT  nShowFlags;
	CProfile  cProfile;

	cProfile.DeleteDisplayWindowInfo(nPosition);
	m_wndSplitter.GetRowInfo(0, nPane[0][0], nPane[0][1]);
	m_wndSplitter.GetRowInfo(1, nPane[1][0], nPane[1][1]);
	return((cProfile.SetDisplayWindowType(nPosition, GetType()) && cProfile.SetDisplayWindowName(nPosition, GetName()) && cProfile.SetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, (nShowFlags = (!IsIconic()) ? ((!IsZoomed()) ? SW_SHOWNORMAL : SW_SHOWMAXIMIZED) : SW_SHOWMINIMIZED)) && cProfile.SetScriptWindowPropertyInfo(nPosition, nPane[0][0], nPane[0][1], nPane[1][0], nPane[1][1])) ? TRUE : FALSE);
}

INT CScriptWnd::Load(INT nPosition)
{
	INT  nPane[2][2];
	UINT  nShowFlags;
	CProfile  cProfile;

	if (cProfile.GetDisplayWindowName(nPosition, m_szName) && cProfile.GetDisplayWindowPlacement(nPosition, m_rPosition, &m_ptPosition, nShowFlags) && cProfile.GetScriptWindowPropertyInfo(nPosition, nPane[0][0], nPane[0][1], nPane[1][0], nPane[1][1]))
	{
		if (CScriptWnd::Create(GetMainWnd(), nShowFlags))
		{
			m_wndSplitter.SetRowInfo(0, nPane[0][0], nPane[0][1]);
			m_wndSplitter.SetRowInfo(1, nPane[1][0], nPane[1][1]);
			m_wndSplitter.RecalcLayout();
			return TRUE;
		}
		return FALSE;
	}
	return -1;
}

BOOL CScriptWnd::UpdateProperties()
{
	if (m_dlgProperties.Create(this, m_cTMEnvironment.GetTMParameters()) == IDOK)
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}

BOOL CScriptWnd::IsUpdatingProperties() CONST
{
	return IsWindow(m_dlgProperties.GetSafeHwnd());
}

BOOL CScriptWnd::HasProperties() CONST
{
	return TRUE;
}

BOOL CScriptWnd::Print(PRINTDLG *pPrintInfo, UINT nFlags)
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
				if (PrintJob(cDC, cPrintProfileInfo.GetPrinterName(), rtMargin[0], bMetrics, nFlags))
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
					if (PrintJob(cDC, (LPCTSTR)pDevMode->dmDeviceName, rtMargin[0], bMetrics, nFlags, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : -1, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : -1))
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

VOID CScriptWnd::DoSave()
{
	INT  nPosition;
	CString  szMessage;

	if (CanSave())
	{
		if ((nPosition = SaveToDatabase()) >= 0)
		{
			GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_SCRIPT);
			UpdateDatabase(this, nPosition);
			UpdateTitle();
			return;
		}
		szMessage.Format(STRING(IDS_SCRIPT_FAILURE_SAVE), (LPCTSTR)GetTitle());
		ShowMessage(szMessage);
	}
}

BOOL CScriptWnd::CanSave() CONST
{
	return((IsModified() && !GetDatabase()->IsCompiling() && !IsCompilingScript()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

VOID CScriptWnd::DoSaveAs()
{
	INT  nIndex;
	INT  nResult;
	INT  nPosition;
	CString  szName;
	CString  szMessage;
	CScriptSaveDialog  cSaveDialog;

	if (CanSaveAs())
	{
		if ((nResult = ((szName = GetName()).GetLength() >= 0) ? cSaveDialog.Create(this) : IDCANCEL) == IDOK && (nPosition = ((nIndex = GetDatabase()->GetScripts()->Find(GetName())) >= 0 || nIndex < 0) ? SaveToDatabase() : -1) >= 0)
		{
			GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_SCRIPT);
			UpdateDatabase(this, (nIndex < 0) ? -(nPosition + 1) : nPosition);
			UpdateTitle();
			UpdateMenus();
			return;
		}
		if (nResult == IDOK)
		{
			szMessage.Format(STRING(IDS_SCRIPT_FAILURE_SAVE), (LPCTSTR)GetTitle());
			ShowMessage(szMessage);
		}
	}
}

BOOL CScriptWnd::CanSaveAs() CONST
{
	return CanSave();
}

VOID CScriptWnd::DoDelete()
{
	INT  nPosition;
	CString  szMessage;

	if (!IsNew())
	{
		for (szMessage.Format(STRING(IDS_SCRIPT_QUESTION_DELETE), (LPCTSTR)GetTitle()); MessageBox(szMessage, GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES; )
		{
			if ((nPosition = DeleteFromDatabase()) >= 0)
			{
				GetTopLevelFrame()->RemoveMRUMenuItem(GetName(), GetTitle(), DISPLAY_TYPE_SCRIPT);
				UpdateDatabase(this, nPosition, TRUE);
				DestroyWindow();
				return;
			}
			szMessage.Format(STRING(IDS_SCRIPT_FAILURE_DELETE), (LPCTSTR)GetTitle());
			ShowMessage(szMessage);
			break;
		}
	}
}

BOOL CScriptWnd::CanDelete() CONST
{
	return((!IsNew()) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

VOID CScriptWnd::DoUndo()
{
	m_wndSplitter.DoUndo();
}

BOOL CScriptWnd::CanUndo() CONST
{
	return m_wndSplitter.CanUndo();
}

VOID CScriptWnd::DoRedo()
{
	m_wndSplitter.DoRedo();
}

BOOL CScriptWnd::CanRedo() CONST
{
	return m_wndSplitter.CanRedo();
}

VOID CScriptWnd::DoFind()
{
	m_wndSplitter.DoFind();
}

BOOL CScriptWnd::CanFind() CONST
{
	return m_wndSplitter.CanFind();
}

VOID CScriptWnd::DoFindNext(BOOL bMatchCase, BOOL bMatchWord)
{
	m_wndSplitter.DoFindNext(bMatchCase, bMatchWord);
}
VOID CScriptWnd::DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	m_wndSplitter.DoFindNext(pszText, bSearchAll, bMatchCase, bMatchWord);
}

BOOL CScriptWnd::CanFindNext() CONST
{
	return m_wndSplitter.CanFindNext();
}

VOID CScriptWnd::DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord)
{
	m_wndSplitter.DoFindPrevious(bMatchCase, bMatchWord);
}
VOID CScriptWnd::DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord)
{
	m_wndSplitter.DoFindPrevious(pszText, bSearchAll, bMatchCase, bMatchWord);
}

BOOL CScriptWnd::CanFindPrevious() CONST
{
	return m_wndSplitter.CanFindPrevious();
}

VOID CScriptWnd::DoReplace()
{
	m_wndSplitter.DoReplace();
}

BOOL CScriptWnd::CanReplace() CONST
{
	return m_wndSplitter.CanReplace();
}

VOID CScriptWnd::DoGoTo()
{
	m_wndSplitter.DoGoTo();
}

BOOL CScriptWnd::CanGoTo() CONST
{
	return m_wndSplitter.CanGoTo();
}

VOID CScriptWnd::DoSelectAll()
{
	m_wndSplitter.DoSelectAll();
}

BOOL CScriptWnd::CanSelectAll() CONST
{
	return m_wndSplitter.CanSelectAll();
}

VOID CScriptWnd::DoCutSel()
{
	m_wndSplitter.DoCutSel();
}

BOOL CScriptWnd::CanCutSel() CONST
{
	return m_wndSplitter.CanCutSel();
}

VOID CScriptWnd::DoCopySel()
{
	m_wndSplitter.DoCopySel();
}

BOOL CScriptWnd::CanCopySel() CONST
{
	return m_wndSplitter.CanCopySel();
}

VOID CScriptWnd::DoPasteSel()
{
	m_wndSplitter.DoPasteSel();
}

BOOL CScriptWnd::CanPasteSel() CONST
{
	return m_wndSplitter.CanPasteSel();
}

VOID CScriptWnd::DoDeleteSel()
{
	m_wndSplitter.DoDeleteSel();
}

BOOL CScriptWnd::CanDeleteSel() CONST
{
	return m_wndSplitter.CanDeleteSel();
}

BOOL CScriptWnd::CanPrint(UINT nFlags) CONST
{
	return(((nFlags == DISPLAY_PRINTTYPE_CODE  &&  GetCodeView()->GetCodeSize() > 0) || (nFlags == DISPLAY_PRINTTYPE_IMAGE  &&  GetImageView()->HasImage())) ? TRUE : FALSE);
}

BOOL CScriptWnd::DoCompile()
{
	INT  nResult;
	INT  nPosition;
	CString  szName;
	CString  szMessage[3];
	CScriptSaveDialog  cSaveDialog;

	if (IsNew())
	{
		for (szMessage[0].Format(STRING(IDS_SCRIPT_QUESTION_SAVE), (LPCTSTR)GetTitle()); MessageBox(szMessage[0], GetAppTitle(), MB_ICONQUESTION | MB_YESNO) == IDYES; )
		{
			if ((nResult = cSaveDialog.Create(this)) == IDOK)
			{
				if ((nPosition = SaveToDatabase()) >= 0)
				{
					UpdateDatabase(this, -(nPosition + 1));
					UpdateTitle();
					UpdateMenus();
				}
			}
			if (nResult == IDOK  &&  nPosition < 0)
			{
				szMessage[1].Format(STRING(IDS_SCRIPT_FAILURE_SAVE), (LPCTSTR)GetTitle());
				szMessage[2].Format(STRING(IDS_SCRIPT_FAILURE_COMPILE), (LPCTSTR)GetTitle());
				ShowMessage(szMessage[1]);
				ShowMessage(szMessage[2]);
				return FALSE;
			}
			if (nResult == IDOK) return StartCompilingScript(GetDatabase()->GetDatabaseEngine(), &m_cScript);
			break;
		}
		szMessage[1].Format(STRING(IDS_SCRIPT_FAILURE_COMPILE), (LPCTSTR)GetTitle());
		ShowMessage(szMessage[1]);
		return FALSE;
	}
	if (IsModified())
	{
		if (SaveToDatabase() < 0)
		{
			szMessage[1].Format(STRING(IDS_SCRIPT_FAILURE_SAVE), (LPCTSTR)GetTitle());
			szMessage[2].Format(STRING(IDS_SCRIPT_FAILURE_COMPILE), (LPCTSTR)GetTitle());
			ShowMessage(szMessage[1]);
			ShowMessage(szMessage[2]);
			return FALSE;
		}
		UpdateTitle();
	}
	return StartCompilingScript(GetDatabase()->GetDatabaseEngine(), &m_cScript);
}

BOOL CScriptWnd::IsCompiling() CONST
{
	return IsCompilingScript();
}

BOOL CScriptWnd::CanCompile() CONST
{
	return((GetCodeView()->GetCodeSize() > 0) ? CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) : FALSE);
}

BOOL CScriptWnd::StopCompiling()
{
	if (IsCompilingScript())
	{
		StopCompilingScript();
		return TRUE;
	}
	return FALSE;
}

VOID CScriptWnd::DoTest()
{
	INT  nItem[2];
	INT  nItems[2];
	UINT  *nIDs[2];
	LPCWSTR  *pszNames[2];
	TIMEKEY  *tScheduleTimes;
	TIMEKEY  *tStartTimes[2];
	TIMEKEY  *tStopTimes[2];
	TIMEKEY  *tIntervals;
	CString  szName;
	CString  szTitle;
	CString  szError;
	CString  szMessage[2];
	CString  szFileName[2];
	CFileFindEx  cFileFind[2];
	CJScriptCodeExecutor  cJScriptCodeExecutor;

	for (szFileName[0] = GetDatabase()->GetFileName(), szFileName[1] = GetDatabase()->GetUpdateFileName(); (cFileFind[0].FindFile(szFileName[0]) || cFileFind[0].FindFile(szFileName[1])) && !cFileFind[0].FindNextFile(); )
	{
		szFileName[0].Format(STRING(IDS_SCRIPTDISPLAYCODE_NORMAL_FILENAME), (LPCTSTR)m_cScript.GetName());
		szFileName[1].Format(STRING(IDS_SCRIPTDISPLAYCODE_UPDATE_FILENAME), (LPCTSTR)m_cScript.GetName());
		szFileName[0] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szFileName[0];
		szFileName[1] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szFileName[1];
		for (InitializeJScriptTaskScheduler((HANDLE)NULL, (HANDLE)NULL), InitializeJScriptTelemetryInterface(GetDatabase(), &m_cTMEnvironment), m_cScript.SetExecutableFileName((cFileFind[1].FindFile(szFileName[1]) && !cFileFind[1].FindNextFile()) ? szFileName[1] : szFileName[0]), pszNames[0] = (LPCWSTR *)NULL, pszNames[1] = (LPCWSTR *)NULL, nIDs[0] = (UINT *)NULL, nIDs[1] = (UINT *)NULL, tScheduleTimes = (TIMEKEY *)NULL, tStartTimes[0] = (TIMEKEY *)NULL, tStartTimes[1] = (TIMEKEY *)NULL, tIntervals = (TIMEKEY *)NULL, tStopTimes[0] = (TIMEKEY *)NULL, tStopTimes[1] = (TIMEKEY *)NULL; cJScriptCodeExecutor.Run(m_cScript.GetName(), m_cScript.GetTitle(), m_cScript.GetExecutableFileName(), m_cScript.GetInputFileName(), m_cScript.GetOutputFileName(), szError); )
		{
			for (nItem[0] = 0, nItems[0] = EnumJScriptTaskSchedulerTelemetryReports(&pszNames[0], &nIDs[0], &tStartTimes[0], &tIntervals, &tStopTimes[0]), ResetConsoleContent(STRING(IDS_OUTPUTWINDOW_DEBUGTAB)), szTitle.Format(STRING(IDS_SCRIPT_MESSAGE_TASKSCHEDULER), (LPCTSTR)m_cScript.GetName()); nItem[0] < nItems[0]; nItem[0]++)
			{
#ifndef UNICODE
				WideCharToMultiByte(CP_ACP, 0, pszNames[0][nItem[0]], -1, szName.GetBufferSetLength((INT)wcslen(pszNames[0][nItem[0]])), (INT)wcslen(pszNames[0][nItem[0]]) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				szName.ReleaseBuffer();
#else
				szName = pszNames[0][nItem[0]];
#endif
				for (; nItem[0] == 0; )
				{
					ShowConsoleText(STRING(IDS_OUTPUTWINDOW_DEBUGTAB), szTitle, FALSE, FALSE);
					break;
				}
				szMessage[0].Format(STRING(IDS_SCRIPT_MESSAGE_TELEMETRYREPORT), (LPCTSTR)szName, (LPCTSTR)(CTimeKey(tStartTimes[0][nItem[0]]).FormatGmt(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + CTimeKey(tStartTimes[0][nItem[0]]).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT))));
				szMessage[1].Format(STRING(IDS_SCRIPT_MESSAGE_TELEMETRYREPORTS), (LPCTSTR)szName, (LPCTSTR)(CTimeKey(tStartTimes[0][nItem[0]]).FormatGmt(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + CTimeKey(tStartTimes[0][nItem[0]]).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT))), tIntervals[nItem[0]], (LPCTSTR)(CTimeKey(tStopTimes[0][nItem[0]]).FormatGmt(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + CTimeKey(tStopTimes[0][nItem[0]]).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT))));
				ShowConsoleText(STRING(IDS_OUTPUTWINDOW_DEBUGTAB), (!tIntervals[nItem[0]]) ? szMessage[0] : szMessage[1], FALSE, FALSE);
				delete[] pszNames[0][nItem[0]];
			}
			for (nItem[1] = 0, nItems[1] = EnumJScriptTaskSchedulerTelemetryDataExtractions(&pszNames[1], &nIDs[1], &tScheduleTimes, &tStartTimes[1], &tStopTimes[1]); nItem[1] < nItems[1]; nItem[1]++)
			{
#ifndef UNICODE
				WideCharToMultiByte(CP_ACP, 0, pszNames[1][nItem[1]], -1, szName.GetBufferSetLength((INT)wcslen(pszNames[1][nItem[1]])), (INT)wcslen(pszNames[1][nItem[1]]) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				szName.ReleaseBuffer();
#else
				szName = pszNames[1][nItem[1]];
#endif
				for (; nItems[0] + nItem[1] == 0; )
				{
					ShowConsoleText(STRING(IDS_OUTPUTWINDOW_DEBUGTAB), szTitle, FALSE, FALSE);
					break;
				}
				szMessage[0].Format(STRING(IDS_SCRIPT_MESSAGE_TELEMETRYDATAEXTRACTION), (LPCTSTR)szName, (LPCTSTR)(CTimeKey(tScheduleTimes[nItem[1]]).FormatGmt(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + CTimeKey(tScheduleTimes[nItem[1]]).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT))), (LPCTSTR)(CTimeKey(tStartTimes[1][nItem[1]]).FormatGmt(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + CTimeKey(tStartTimes[1][nItem[1]]).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT))), (LPCTSTR)(CTimeKey(tStopTimes[1][nItem[1]]).FormatGmt(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + CTimeKey(tStopTimes[1][nItem[1]]).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT))));
				ShowConsoleText(STRING(IDS_OUTPUTWINDOW_DEBUGTAB), szMessage[0], FALSE, FALSE);
				delete[] pszNames[1][nItem[1]];
			}
			delete nIDs[0];
			delete nIDs[1];
			delete pszNames[0];
			delete pszNames[1];
			delete tIntervals;
			delete tScheduleTimes;
			delete tStartTimes[0];
			delete tStartTimes[1];
			delete tStopTimes[0];
			delete tStopTimes[1];
			UninitializeJScriptTelemetryInterface();
			UninitializeJScriptTaskScheduler();
			UpdateImage(&m_cScript);
			cFileFind[0].Close();
			cFileFind[1].Close();
			return;
		}
		UninitializeJScriptTelemetryInterface();
		UninitializeJScriptTaskScheduler();
		break;
	}
	if (!szError.IsEmpty())
	{
		szMessage[0].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_ERROR), (LPCTSTR)m_cScript.GetName(), (LPCTSTR)szError);
		ShowMessage(szMessage[0]);
	}
	else
	{
		szMessage[1].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_INTERNALERROR), (LPCTSTR)m_cScript.GetName());
		ShowMessage(szMessage[1]);
	}
}

BOOL CScriptWnd::IsTesting() CONST
{
	return FALSE;
}

BOOL CScriptWnd::CanTest() CONST
{
	CString  szCode[2];
	CString  szFileName[2];
	CFileFindEx  cFileFind[2];

	for (szFileName[0] = GetDatabase()->GetFileName(), szFileName[1] = GetDatabase()->GetUpdateFileName(); (cFileFind[0].FindFile(szFileName[0]) || cFileFind[0].FindFile(szFileName[1])) && !cFileFind[0].FindNextFile(); )
	{
		szCode[0].Format(STRING(IDS_SCRIPTDISPLAYCODE_NORMAL_FILENAME), (LPCTSTR)m_cScript.GetName());
		szCode[1].Format(STRING(IDS_SCRIPTDISPLAYCODE_UPDATE_FILENAME), (LPCTSTR)m_cScript.GetName());
		szCode[0] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[0];
		szCode[1] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[1];
		if ((cFileFind[1].FindFile(szCode[0]) || cFileFind[1].FindFile(szCode[1])) && !cFileFind[1].FindNextFile())
		{
			cFileFind[1].Close();
			cFileFind[0].Close();
			return CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE);
		}
		cFileFind[0].Close();
		break;
	}
	return FALSE;
}

VOID CScriptWnd::DoClose()
{
	INT  nResult;
	INT  nPosition;
	CString  szName;
	CString  szMessage[2];
	CScriptSaveDialog  cSaveDialog;

	if (IsNew() || IsModified())
	{
		for (szMessage[0].Format(STRING(IDS_SCRIPT_QUESTION_SAVEONCLOSE), (LPCTSTR)GetTitle()); CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE) && MessageBox(szMessage[0], GetAppTitle(), MB_ICONWARNING | MB_YESNO) == IDYES; )
		{
			if ((nResult = ((szName = GetName()).IsEmpty() || IsNew()) ? cSaveDialog.Create(this) : IDOK) == IDOK && (nPosition = SaveToDatabase()) >= 0)
			{
				GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
				UpdateDatabase(this, (szName != GetName()) ? -(nPosition + 1) : nPosition);
				UpdateTitle();
			}
			if (nResult == IDOK  &&  nPosition < 0)
			{
				szMessage[1].Format(STRING(IDS_SCRIPT_FAILURE_SAVE), (LPCTSTR)GetTitle());
				ShowMessage(szMessage[1]);
			}
			break;
		}
	}
}

VOID CScriptWnd::UpdateBars()
{
	CString  szMessage;
	CStringTools  cStringTools;

	if (m_wndStatusBar.SetIndicators(nStatusBarIndicators, sizeof(nStatusBarIndicators) / sizeof(UINT)))
	{
		szMessage.Format(STRING(IDS_SCRIPT_STATUSBAR_SIZE), (LPCTSTR)cStringTools.ConvertIntToStructuredString(GetCodeView()->GetCodeSize()));
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_SCRIPT_STATUSBAR_SIZEPANE), szMessage);
		szMessage.Format(STRING(IDS_SCRIPT_STATUSBAR_LINE), GetCodeView()->GetLinePosition());
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_SCRIPT_STATUSBAR_LINEPANE), szMessage);
		szMessage.Format(STRING(IDS_SCRIPT_STATUSBAR_COLUMN), GetCodeView()->GetColumnPosition());
		m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_SCRIPT_STATUSBAR_COLUMNPANE), szMessage);
	}
}

CScriptCodeView *CScriptWnd::GetCodeView() CONST
{
	return m_wndSplitter.GetCodeView();
}

CScriptImageView *CScriptWnd::GetImageView() CONST
{
	return m_wndSplitter.GetImageView();
}

VOID CScriptWnd::UpdateTitle()
{
	INT  nPos;
	CString  szName;
	CString  szTitle[2];

	for (szName = GetName(), szTitle[0] = STRING(IDS_DISPLAY_TITLE_SCRIPT); szName.IsEmpty(); )
	{
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_WINDOW_UNTITLED), ((nPos = szTitle[0].ReverseFind(SPACE[0])) >= 0) ? (LPCTSTR)szTitle[0].Left(nPos) : (LPCTSTR)szTitle[0]);
		break;
	}
	for (szTitle[0] = GetTitle(); !szName.IsEmpty() && szTitle[0].IsEmpty(); )
	{
		szTitle[1].Format(STRING(IDS_DISPLAY_TITLE_SCRIPT), (LPCTSTR)szName);
		szTitle[0].Empty();
		break;
	}
	if (!szName.IsEmpty() && !szTitle[0].IsEmpty())
	{
		szTitle[0].Format(STRING(IDS_DISPLAY_TITLE_SCRIPT), (LPCTSTR)szName);
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), (LPCTSTR)GetTitle(), (LPCTSTR)szTitle[0]);
	}
	SetWindowText(szTitle[1]);
}

VOID CScriptWnd::UpdateMenus()
{
	GetTopLevelFrame()->AddMRUMenuItem(GetName(), GetTitle(), GetType());
}

VOID CScriptWnd::UpdateImage()
{
	UpdateImage(&m_cScript);
}
VOID CScriptWnd::UpdateImage(CONST CAutomationScript *pScript)
{
	GetImageView()->UpdateImage(pScript);
}

INT CScriptWnd::SaveToDatabase()
{
	INT  nResultCode;

	for (m_cScript.SetName(GetName()), m_cScript.SetTitle(GetTitle()); GetCodeView()->GetCode(&m_cScript); )
	{
		if ((nResultCode = GetDatabase()->SaveScript(m_cScript)) >= 0)
		{
			GetImageView()->SetModified(FALSE);
			GetCodeView()->SetModified(FALSE);
		}
		return nResultCode;
	}
	return -1;
}

BOOL CScriptWnd::LoadFromDatabase()
{
	CAutomationScript  cScript;

	if (GetDatabase()->LoadScript(GetName(), m_cScript))
	{
		if (GetCodeView()->SetCode(&m_cScript) && GetImageView()->SetImage(&m_cScript) && GetScript(&cScript))
		{
			SetTitle(cScript.GetTitle());
			SetName(cScript.GetName());
			return m_cScript.Copy(&cScript);
		}
	}
	return FALSE;
}

INT CScriptWnd::DeleteFromDatabase()
{
	return Delete(GetName());
}

BOOL CScriptWnd::StartPrintJob(CDC &cDC)
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

BOOL CScriptWnd::PrintJob(CDC &cDC, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, WORD wFromPage, WORD wToPage)
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

	if (StartPrintJob(cDC))
	{
		if (nFlags == DISPLAY_PRINTTYPE_CODE)
		{
			if (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rPrintArea[0]) != ERROR  &&  CalcPrintDocTitleFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_TITLE]) && CalcPrintDocInfoTitleFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_INFOTITLE]) && CalcPrintDocNoticeFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_NOTICE], cFont[DISPLAY_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_FOOTER]))
			{
				for (nPos = 0, nPage = 1, nPrintLength = GetCodeView()->GetTextLengthEx(GTL_PRECISE | GTL_NUMCHARS), pFonts.SetAtGrow(DISPLAY_PRINTFONT_TITLE, &cFont[DISPLAY_PRINTFONT_TITLE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_INFOTITLE, &cFont[DISPLAY_PRINTFONT_INFOTITLE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_FOOTER, &cFont[DISPLAY_PRINTFONT_FOOTER]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_NOTICE, &cFont[DISPLAY_PRINTFONT_NOTICE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_LOGO, &cFont[DISPLAY_PRINTFONT_LOGO]), fPrintScale = (rPrintArea[0].Height() > 0) ? min((double)rPrintArea[0].Width() / (double)rPrintArea[0].Height(), 1.0) : 1.0, bPrintOutput[0] = bPrintOutput[1] = FALSE; nPos < nPrintLength && wFromPage <= wToPage; nPage++)
				{
					if (DrawPrintDocPage(cDC, tPrintTime, pszPrinterName, pFonts, (rPrintArea[1] = rPrintArea[0]), nFlags, nPage, !(bPrintOutput[0] = ((nPage >= (INT)wFromPage  &&  nPage <= (INT)wToPage) || wFromPage == (WORD)-1 || wToPage == (WORD)-1) ? TRUE : FALSE)))
					{
						for (nOldMapMode = cDC.SetMapMode(MM_ISOTROPIC), cDC.SetViewportExt((INT)(10000.0*fPrintScale), (INT)(10000.0*fPrintScale)), cDC.SetWindowExt(10000, 10000), rPrintArea[2].left = (INT)(1440.0*(double)rPrintArea[1].left / ((double)cDC.GetDeviceCaps(LOGPIXELSX)*fPrintScale)), rPrintArea[2].top = (INT)(1440.0*(double)rPrintArea[1].top / ((double)cDC.GetDeviceCaps(LOGPIXELSY)*fPrintScale)), rPrintArea[2].right = (INT)(1440.0*(double)rPrintArea[1].right / ((double)cDC.GetDeviceCaps(LOGPIXELSX)*fPrintScale)), rPrintArea[2].bottom = (INT)(1440.0*(double)rPrintArea[1].bottom / ((double)cDC.GetDeviceCaps(LOGPIXELSY)*fPrintScale)); (nPos = GetCodeView()->PrintInsideRect(&cDC, rPrintArea[2], nPos, -1, bPrintOutput[0])) >= 0; )
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
		if (nFlags == DISPLAY_PRINTTYPE_IMAGE)
		{
			if ((wFromPage < 1 || wToPage > 1) && wFromPage != (WORD)-1 && wToPage != (WORD)-1)
			{
				cDC.AbortDoc();
				return TRUE;
			}
			if (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rPrintArea[0]) != ERROR  &&  CalcPrintDocTitleFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_TITLE]) && CalcPrintDocInfoTitleFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_INFOTITLE]) && CalcPrintDocNoticeFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_NOTICE], cFont[DISPLAY_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rPrintArea[0], cFont[DISPLAY_PRINTFONT_FOOTER]))
			{
				for (pFonts.SetAtGrow(DISPLAY_PRINTFONT_TITLE, &cFont[DISPLAY_PRINTFONT_TITLE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_INFOTITLE, &cFont[DISPLAY_PRINTFONT_INFOTITLE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_FOOTER, &cFont[DISPLAY_PRINTFONT_FOOTER]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_NOTICE, &cFont[DISPLAY_PRINTFONT_NOTICE]), pFonts.SetAtGrow(DISPLAY_PRINTFONT_LOGO, &cFont[DISPLAY_PRINTFONT_LOGO]); DrawPrintDocPage(cDC, tPrintTime, pszPrinterName, pFonts, (rPrintArea[1] = rPrintArea[0]), nFlags, 1); )
				{
					GetImageView()->PrintInsideRect(&cDC, rPrintArea[1]);
					EndPrintJob(cDC);
					return TRUE;
				}
			}
		}
		cDC.AbortDoc();
	}
	return FALSE;
}

BOOL CScriptWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndPage() >= 0 && cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CScriptWnd::DrawPrintDocPage(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CPtrArray &pFonts, LPRECT prClip, UINT nFlags, INT nPage, BOOL bCalc)
{
	return((DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_TITLE), nFlags, bCalc) && (nFlags == DISPLAY_PRINTTYPE_IMAGE || DrawPrintDocInfoTitle(cDC, prClip, GetPrintDocInfoTitle(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_INFOTITLE), bCalc)) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_LOGO), bCalc) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPage), (CFont *)pFonts.GetAt(DISPLAY_PRINTFONT_FOOTER), bCalc)) ? TRUE : FALSE);
}

BOOL CScriptWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nFlags, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += (nFlags == DISPLAY_PRINTTYPE_IMAGE) ? ((3 * rCalc.Height()) / 2) : rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

CString CScriptWnd::GetPrintDocTitle() CONST
{
	return GetTitle();
}

CString CScriptWnd::GetPrintDocInfoTitle() CONST
{
	return STRING(IDS_PRINTDOCUMENT_TITLE_SOURCECODE);
}

BOOL CScriptWnd::StartCompilingScript(CBinaryDatabase *pDatabase, CONST CAutomationScript *pScript)
{
	if (m_cCompileThread.StartCompiling(pDatabase, pScript))
	{
		UpdateDatabase(DATABASE_COMPONENT_SCRIPT, pScript->GetName());
		return TRUE;
	}
	return FALSE;
}
BOOL CScriptWnd::StartCompilingScript(CBinaryDatabase *pDatabase, CONST CAutomationScript *pScript, BOOL bSyntax, BOOL bBatch, INT &nErrors, INT &nWarnings, BOOL &bAbort)
{
	if (m_cCompileThread.StartCompiling(pDatabase, pScript, bSyntax, bBatch, nErrors, nWarnings, bAbort))
	{
		UpdateDatabase(DATABASE_COMPONENT_SCRIPT, pScript->GetName());
		return TRUE;
	}
	return FALSE;
}

BOOL CScriptWnd::IsCompilingScript()
{
	return m_cCompileThread.IsCompiling();
}

VOID CScriptWnd::StopCompilingScript()
{
	CAutomationScript  cScript;

	for (m_cCompileThread.GetCompileTarget(&cScript); IsCompilingScript(); )
	{
		UpdateDatabase(~DATABASE_COMPONENT_SCRIPT, cScript.GetName());
		break;
	}
	m_cCompileThread.StopCompiling();
}

INT CScriptWnd::Delete(LPCTSTR pszName)
{
	INT  nIndex;
	CString  szFilePath;
	CString  szFileName[3];
	CFileFindEx  cFileFind[2];
	CAutomationScript  cScript;

	for (cScript.SetName(pszName), szFileName[0] = GetDatabase()->GetFileName(), szFileName[1] = GetDatabase()->GetUpdateFileName(); (nIndex = GetDatabase()->DeleteScript(cScript)) >= 0; )
	{
		if ((cFileFind[0].FindFile(szFileName[0]) || cFileFind[0].FindFile(szFileName[1])) && cFileFind[0].FindNextFile() >= 0)
		{
			szFilePath = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength());
			for (szFileName[2].Format(STRING(IDS_SCRIPTDISPLAYCODE_SEARCH_FILENAME), pszName), szFileName[2] = szFilePath + szFileName[2]; cFileFind[1].FindFile(szFileName[2]); )
			{
				while (cFileFind[1].FindNextFile())
				{
					CFileEx::SetAttributes(cFileFind[1].GetFilePath(), CFileEx::GetAttributes(cFileFind[1].GetFilePath()) & ~FILE_ATTRIBUTE_READONLY);
					CFileEx::Remove(cFileFind[1].GetFilePath());
				}
				CFileEx::SetAttributes(cFileFind[1].GetFilePath(), CFileEx::GetAttributes(cFileFind[1].GetFilePath()) & ~FILE_ATTRIBUTE_READONLY);
				CFileEx::Remove(cFileFind[1].GetFilePath());
				cFileFind[1].Close();
				break;
			}
			cFileFind[0].Close();
		}
		return nIndex;
	}
	return -1;
}

VOID CScriptWnd::AdjustToPrivileges()
{
	if (!CheckDatabasePrivilege(DATABASE_PRIVILEGE_SCRIPT_CHANGE))
	{
		m_wndSplitter.UnSelectAll();
		return;
	}
}

BEGIN_MESSAGE_MAP(CScriptWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CScriptWnd)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_SCRIPT_STATUSBAR_SIZEPANE, OnUpdateStatusBarSizePane)
	ON_UPDATE_COMMAND_UI(ID_SCRIPT_STATUSBAR_LINEPANE, OnUpdateStatusBarLinePane)
	ON_UPDATE_COMMAND_UI(ID_SCRIPT_STATUSBAR_COLUMNPANE, OnUpdateStatusBarColumnPane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptWnd message handlers

int CScriptWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CDisplayWnd::OnCreate(lpCreateStruct) != -1 && LoadAccelTable(MAKEINTRESOURCE(IDR_SCRIPTFRAME))) ? (((IsNew() || LoadFromDatabase()) && m_cTMEnvironment.Create(GetDatabase())) ? 0 : -1) : -1);
}

BOOL CScriptWnd::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	return(m_wndSplitter.Create(this) && m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nStatusBarIndicators, 1));
}

void CScriptWnd::OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd)
{
	CWnd  *pWnd;

	for (pWnd = CWnd::GetFocus(); GetCodeView()->HasDialogs(); )
	{
		for (GetCodeView()->ShowDialogs(bActivate); !bActivate; )
		{
			pWnd->SetFocus();
			break;
		}
		break;
	}
	CDisplayWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
}

void CScriptWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DOWN)
	{
		SetActiveView(GetCodeView());
		GetCodeView()->SetFocus();
		return;
	}
	if (nChar == VK_UP)
	{
		SetActiveView(GetImageView());
		GetImageView()->SetFocus();
		return;
	}
	CDisplayWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CScriptWnd::OnClose()
{
	CHourglassCursor  cCursor;

	DoClose();
	CDisplayWnd::OnClose();
}

void CScriptWnd::OnDestroy()
{
	m_wndSplitter.UnSelectAll();
	m_cTMEnvironment.Destroy();
	CDisplayWnd::OnDestroy();
}

void CScriptWnd::OnUpdateStatusBarSizePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CScriptWnd::OnUpdateStatusBarLinePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CScriptWnd::OnUpdateStatusBarColumnPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
