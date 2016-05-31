// DIALOGS.CPP : Dialogs Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the dialogs related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2012/08/29 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#define LIBRARYENVIRONMENT
#define SCOS2000ENVIRONMENT

#include "SCOS-2000.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseTablesDialog, CLocaleDialog)

CDatabaseTablesDialog::CDatabaseTablesDialog(CDatabaseEngine *pDatabaseEngine) : CLocaleDialog()
{
	m_pDatabaseEngine = pDatabaseEngine;
}

BOOL CDatabaseTablesDialog::ShowMessage(CONST EVENT_DESCRIPTOR nMessageID)
{
	return((m_pDatabaseEngine != (CDatabaseEngine *)NULL) ? m_pDatabaseEngine->ShowMessage(nMessageID) : FALSE);
}

BOOL CDatabaseTablesDialog::ShowHelp(LPCTSTR pszTopic)
{
	return((m_pDatabaseEngine != (CDatabaseEngine *)NULL) ? m_pDatabaseEngine->ShowHelp(pszTopic) : FALSE);
}

CDatabaseEngine *CDatabaseTablesDialog::GetDatabase() CONST
{
	return m_pDatabaseEngine;
}

HGLOBAL CDatabaseTablesDialog::LoadLocaleDialogTemplate(UINT nDialogID) CONST
{
	return LoadLocaleDialogTemplate(MAKEINTRESOURCE(nDialogID));
}
HGLOBAL CDatabaseTablesDialog::LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST
{
	HMODULE  hModule;
	HRSRC  hDialogTemplate;

	return(((hDialogTemplate = FindResourceEx((hModule = CSCOS2000LibraryApp::GetLibraryApp()->m_hInstance), RT_DIALOG, pszDialogName, GetLanguageID())) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hDialogTemplate) : (LPVOID)NULL);
}

void CDatabaseTablesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseTablesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatabaseTablesDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CDatabaseTablesDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesDialog message handlers


/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorsImportDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseOBProcessorsImportDialog, CDatabaseTablesDialog)

CDatabaseOBProcessorsImportDialog::CDatabaseOBProcessorsImportDialog(CWnd *pParentWnd, CDatabaseEngine *pDatabaseEngine) : CDatabaseTablesDialog(pDatabaseEngine)
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CDatabaseOBProcessorsImportDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT_PTR CDatabaseOBProcessorsImportDialog::DoModal(CDatabaseOBProcessors &pDatabaseOBProcessors)
{
	INT_PTR  nResult;

	for (m_pDatabaseOBProcessors[0].Copy(&pDatabaseOBProcessors), m_pDatabaseOBProcessors[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseOBProcessors.Copy(&m_pDatabaseOBProcessors[1]);
		break;
	}
	return nResult;
}

VOID CDatabaseOBProcessorsImportDialog::EnumOBProcessors()
{
	INT  nColumn;
	INT  nColumns;
	INT  nProcessor;
	INT  nProcessors;
	CString  szItem;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;

	for (nProcessor = 0, nProcessors = (INT)m_pDatabaseOBProcessors[0].GetSize(); nProcessor < nProcessors; nProcessor++)
	{
		if ((pDatabaseOBProcessor = m_pDatabaseOBProcessors[0].GetAt(nProcessor)))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_NAME); )
				{
					szItem = pDatabaseOBProcessor->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseOBProcessor->GetDescription();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_ADDRESS); )
				{
					szItem = pDatabaseOBProcessor->GetDetails();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_CATEGORY); )
				{
					szItem = GetDatabase()->TranslateOBProcessorAddressBase(pDatabaseOBProcessor->GetAttributes(), FALSE);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST), nProcessor, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST), nProcessor, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST), 0);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseOBProcessorsImportDialog::ImportData(LPCTSTR pszFileName, CDatabaseOBProcessor *pDatabaseOBProcessor) CONST
{
	INT  nLine;
	INT  nLines;
	INT  nIndex;
	INT  nCount;
	INT  nArea;
	INT  nAreas;
	INT  nBlock;
	INT  nBlocks;
	INT  nPos[2];
	BOOL  bName;
	BOOL  bLines;
	UINT  nAddressPage[2];
	UINT  nAddressOffset[2];
	UINT  nAddress[2][2];
	DWORD  cbData;
	DWORD  cbBuffer;
	LPSTR  pszBuffer;
	CFileEx  cFile;
	CString  szData;
	CString  szLine;
	CStringArray  szLines;
	CDatabaseOBProcessorMemoryArea  *pDatabaseOBProcessorMemoryArea;
	CDatabaseOBProcessorMemoryAreaBlock  *pDatabaseOBProcessorMemoryAreaBlock;

	if (cFile.Open(pszFileName, CFile::modeRead | CFile::shareDenyWrite))
	{
		if ((pszBuffer = (LPSTR)GlobalAlloc(GPTR, (SIZE_T)(cFile.GetLength() + 1))))
		{
			if (ReadFile(cFile.m_hFile, pszBuffer, (cbData = (DWORD)cFile.GetLength()), &cbBuffer, (LPOVERLAPPED)NULL))
			{
#ifndef UNICODE
				szData = pszBuffer;
#else
				MultiByteToWideChar(CP_ACP, 0, pszBuffer, -1, szData.GetBufferSetLength(cbData), cbData + 1);
				szData.ReleaseBuffer();
#endif
				for (nPos[0] = 0; (nPos[1] = szData.Mid(nPos[0]).Find(CR)) >= 0; nPos[0] += nPos[1] + 1)
				{
					for (szLines.Add(szData.Mid(nPos[0], nPos[1])); !szData.Mid(nPos[0] + nPos[1] + 1).Find(EOL); )
					{
						nPos[1]++;
						break;
					}
				}
				if (!szData.Mid(nPos[0]).IsEmpty()) szLines.Add(szData.Mid(nPos[0]));
				for (nLine = 0, nLines = (INT)szLines.GetSize(), nIndex = 0; nLine < nLines; nLine++)
				{
					if (szLines.GetAt(nLine).Find(TAB) >= 0)
					{
						nIndex = nLine;
						break;
					}
				}
				for (nLine = 0, nAddress[0][0] = nAddress[0][1] = 0, nCount = -1, bName = ((nLines = (INT)szLines.GetSize()) >= 3 && (szLines.GetAt(2) == STRINGCHAR(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_CATEGORY_CONFIGURATION) || szLines.GetAt(2) == STRINGCHAR(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_CATEGORY_SYMBOLIC))) ? TRUE : FALSE; nLine < nIndex; nLine++)
				{
					if (nLine == 0 && bName) pDatabaseOBProcessor->SetName(szLines.GetAt(nLine));
					if ((nLine == 1 && bName) || (nLine == 0 && !bName)) pDatabaseOBProcessor->SetDescription(szLines.GetAt(nLine));
					if ((nLine == 2 && bName) || (nLine == 1 && !bName)) pDatabaseOBProcessor->SetDetails(szLines.GetAt(nLine));
					if ((nLine == 3 && bName) || (nLine == 2 && !bName)) pDatabaseOBProcessor->SetMasterImage(szLines.GetAt(nLine));
					if ((nLine == 4 && bName) || (nLine == 3 && !bName)) pDatabaseOBProcessor->SetAttributes(GetDatabase()->TranslateOBProcessorAddressBase(szLines.GetAt(nLine)));
					if ((nLine == 6 && bName) || (nLine == 5 && !bName)) pDatabaseOBProcessor->SetAddressRange(0, (nAddress[0][1] = (UINT)_ttoi64(szLines.GetAt(nLine))), 0, 0);
					if ((nLine == 7 && bName) || (nLine == 6 && !bName)) pDatabaseOBProcessor->SetAddressRange(0, nAddress[0][1], 0, (nAddress[1][1] = (UINT)_ttoi64(szLines.GetAt(nLine))));
					if ((nLine == 8 && bName) || (nLine == 7 && !bName)) nCount = _ttoi(szLines.GetAt(nLine));
				}
				for (nLines = (nCount >= 0) ? min(nLine + nCount, nLines) : nLines, bLines = TRUE; nLine < nLines && bLines; nLine++)
				{
					if ((pDatabaseOBProcessorMemoryArea = new CDatabaseOBProcessorMemoryArea) != (CDatabaseOBProcessorMemoryArea *)NULL)
					{
						for (szLine = szLines.GetAt(nLine), nAddress[0][0] = nAddress[0][1] = 0, nPos[0] = 0; (bLines = ((nPos[1] = szLine.Mid(nPos[0]).Find(TAB)) > 0)); )
						{
							for (pDatabaseOBProcessorMemoryArea->SetName(szLine.Mid(nPos[0], nPos[1])), nPos[0] += nPos[1] + 1; (bLines = ((nPos[1] = szLine.Mid(nPos[0]).Find(TAB)) > 0)); )
							{
								for (nAddress[0][0] = (UINT)_ttoi64(szLine.Mid(nPos[0], nPos[1])), nPos[0] += nPos[1] + 1; (bLines = ((nPos[1] = szLine.Mid(nPos[0]).Find(TAB)) > 0)); )
								{
									for (nAddress[0][1] = (UINT)_ttoi64(szLine.Mid(nPos[0], nPos[1])), nPos[0] += nPos[1] + 1; (nPos[1] = ((nPos[1] = szLine.Mid(nPos[0]).Find(TAB)) >= 0) ? szLine.Mid((nPos[0] = nPos[0] + nPos[1] + 1)).Find(TAB) : -1) > 0; )
									{
										for (pDatabaseOBProcessorMemoryArea->SetAttributes(GetDatabase()->TranslateOBProcessorMemoryAreaPatchFlag(szLine.Mid(nPos[0], nPos[1]))), nPos[0] += nPos[1] + 1; (nPos[1] = szLine.Mid(nPos[0]).Find(TAB)) > 0; )
										{
											pDatabaseOBProcessorMemoryArea->SetAttributes(pDatabaseOBProcessorMemoryArea->GetAttributes() | GetDatabase()->TranslateOBProcessorMemoryAreaDumpFlag(szLine.Mid(nPos[0], nPos[1])));
											pDatabaseOBProcessorMemoryArea->SetDescription(szLine.Mid(nPos[0] + nPos[1] + 1));
											break;
										}
										break;
									}
									for (nBlock = 0, nBlocks = nAddress[0][1], pDatabaseOBProcessorMemoryArea->SetAttributes(pDatabaseOBProcessorMemoryArea->GetAttributes() | OBPROCESSORMEMORYAREA_TYPE_MEMORY); nBlock < nBlocks; nBlock++)
									{
										if ((pDatabaseOBProcessorMemoryAreaBlock = new CDatabaseOBProcessorMemoryAreaBlock))
										{
											pDatabaseOBProcessorMemoryAreaBlock->SetAddress(0, nAddress[0][0] + nBlock);
											pDatabaseOBProcessorMemoryAreaBlock->SetBitOffset(0);
											pDatabaseOBProcessorMemoryAreaBlock->SetBitWidth((pDatabaseOBProcessor->GetAttributes() & OBPROCESSOR_ADDRESSWIDTH_DWORDS) ? (8 * sizeof(DWORD)) : ((pDatabaseOBProcessor->GetAttributes() & OBPROCESSOR_ADDRESSWIDTH_WORDS) ? (8 * sizeof(WORD)) : (8 * sizeof(BYTE))));
											if (pDatabaseOBProcessorMemoryArea->Add(pDatabaseOBProcessorMemoryAreaBlock) >= 0) continue;
											delete pDatabaseOBProcessorMemoryAreaBlock;
										}
										break;
									}
									if (nBlock == nBlocks)
									{
										if ((pDatabaseOBProcessorMemoryArea->GetAttributes() & (OBPROCESSORMEMORYAREA_FLAG_NONPATCHABLE | OBPROCESSORMEMORYAREA_FLAG_PATCHABLE | OBPROCESSORMEMORYAREA_FLAG_PATCHALWAYS)) == 0) pDatabaseOBProcessorMemoryArea->SetAttributes((pDatabaseOBProcessor->GetDetails() == STRINGCHAR(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_CATEGORY_CONFIGURATION)) ? (pDatabaseOBProcessorMemoryArea->GetAttributes() | OBPROCESSORMEMORYAREA_FLAG_PATCHABLE | OBPROCESSORMEMORYAREA_FLAG_NOINHIBIT) : (pDatabaseOBProcessorMemoryArea->GetAttributes() | OBPROCESSORMEMORYAREA_FLAG_NONPATCHABLE | OBPROCESSORMEMORYAREA_FLAG_INHIBIT));
										if ((pDatabaseOBProcessorMemoryArea->GetAttributes() & (OBPROCESSORMEMORYAREA_FLAG_NONDUMPABLE | OBPROCESSORMEMORYAREA_FLAG_DUMPABLE | OBPROCESSORMEMORYAREA_FLAG_DUMPALWAYS)) == 0) pDatabaseOBProcessorMemoryArea->SetAttributes((pDatabaseOBProcessor->GetDetails() == STRINGCHAR(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_CATEGORY_CONFIGURATION)) ? (pDatabaseOBProcessorMemoryArea->GetAttributes() | OBPROCESSORMEMORYAREA_FLAG_DUMPABLE | OBPROCESSORMEMORYAREA_FLAG_UPDATE) : (pDatabaseOBProcessorMemoryArea->GetAttributes() | OBPROCESSORMEMORYAREA_FLAG_NONDUMPABLE | OBPROCESSORMEMORYAREA_FLAG_NOUPDATE));
										if (pDatabaseOBProcessor->Add(pDatabaseOBProcessorMemoryArea) >= 0) break;
									}
									bLines = FALSE;
									break;
								}
								break;
							}
							break;
						}
						if (!bLines) delete pDatabaseOBProcessorMemoryArea;
					}
					else bLines = FALSE;
				}
				if (bLines)
				{
					for (pDatabaseOBProcessor->GetAddressRange(nAddress[0][0], nAddress[0][1], nAddress[1][0], nAddress[1][1]), pDatabaseOBProcessor->SetDetails(GetDatabase()->TranslateOBProcessorAddressRange(nAddress[0][0], nAddress[0][1], nAddress[1][0], nAddress[1][1])); nAddress[0][0] + nAddress[0][1] >= nAddress[1][0] + nAddress[1][1]; )
					{
						for (nArea = 0, nAreas = (INT)pDatabaseOBProcessor->GetSize(), nAddressPage[0] = nAddressPage[1] = nAddressOffset[0] = nAddressOffset[1] = 0; nArea < nAreas; nArea++)
						{
							if ((pDatabaseOBProcessorMemoryArea = pDatabaseOBProcessor->GetAt(nArea)) && pDatabaseOBProcessorMemoryArea->GetSize() > 0)
							{
								if ((pDatabaseOBProcessorMemoryAreaBlock = pDatabaseOBProcessorMemoryArea->GetAt(0)) && pDatabaseOBProcessorMemoryAreaBlock->GetAddress(nAddress[1][0], nAddress[1][1]) && (!nArea || nAddressPage[0] + nAddressOffset[0] > nAddress[1][0] + nAddress[1][1]))
								{
									nAddressPage[0] = nAddress[1][0];
									nAddressOffset[0] = nAddress[1][1];
								}
								if ((pDatabaseOBProcessorMemoryAreaBlock = pDatabaseOBProcessorMemoryArea->GetAt((INT)pDatabaseOBProcessorMemoryArea->GetSize() - 1)) && pDatabaseOBProcessorMemoryAreaBlock->GetAddress(nAddress[1][0], nAddress[1][1]) && (!nArea || nAddressPage[1] + nAddressOffset[1] < nAddress[1][0] + nAddress[1][1]))
								{
									nAddressPage[1] = nAddress[1][0];
									nAddressOffset[1] = nAddress[1][1];
								}
							}
						}
						if (nAreas > 0)
						{
							pDatabaseOBProcessor->SetAddressRange(nAddressPage[0], nAddressOffset[0], nAddressPage[1], nAddressOffset[1]);
							pDatabaseOBProcessor->SetDetails(GetDatabase()->TranslateOBProcessorAddressRange(nAddressPage[0], nAddressOffset[0], nAddressPage[1], nAddressOffset[1]));
							break;
						}
						pDatabaseOBProcessor->SetAddressRange(0, 0, 0, 0);
						pDatabaseOBProcessor->SetDetails(EMPTYSTRING);
						break;
					}
					GlobalFree(pszBuffer);
					cFile.Close();
					return TRUE;
				}
			}
			GlobalFree(pszBuffer);
		}
		cFile.Close();
	}
	return FALSE;
}

BOOL CDatabaseOBProcessorsImportDialog::TranslateCategory(CONST CDatabaseOBProcessor *pDatabaseOBProcssor) CONST
{
	INT  nMemoryArea;
	INT  nMemoryAreas;
	CDatabaseOBProcessorMemoryArea  *pDatabaseOBProcessorMemoryArea;

	for (nMemoryArea = 0, nMemoryAreas = (INT)pDatabaseOBProcssor->GetSize(); nMemoryArea < nMemoryAreas; nMemoryArea++)
	{
		if ((pDatabaseOBProcessorMemoryArea = pDatabaseOBProcssor->GetAt(nMemoryArea)) != (CDatabaseOBProcessorMemoryArea *)NULL)
		{
			if (pDatabaseOBProcessorMemoryArea->GetAttributes() & (OBPROCESSORMEMORYAREA_FLAG_PATCHABLE | OBPROCESSORMEMORYAREA_FLAG_PATCHALWAYS | OBPROCESSORMEMORYAREA_FLAG_DUMPABLE | OBPROCESSORMEMORYAREA_FLAG_DUMPALWAYS)) break;
			continue;
		}
	}
	return(nMemoryArea < nMemoryAreas);
}

BOOL CDatabaseOBProcessorsImportDialog::Check(BOOL bModified) CONST
{
	return(GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_NAME)->GetWindowTextLength() > 0);
}

void CDatabaseOBProcessorsImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CDatabaseTablesDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseOBProcessorsImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseOBProcessorsImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CDatabaseTablesDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseOBProcessorsImportDialog, CDatabaseTablesDialog)
	//{{AFX_MSG_MAP(CDatabaseOBProcessorsImportDialog)
	ON_BN_CLICKED(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME_BROWSE, OnFileNameBrowse)
	ON_BN_CLICKED(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME_INSPECT, OnFileNameInspect)
	ON_EN_CHANGE(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_NAME, OnEditchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorsImportDialog message handlers

BOOL CDatabaseOBProcessorsImportDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDatabaseTablesDialog::OnInitDialog();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_ADDRESS)->GetWindowText(m_szText);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_ADDRESS));
	m_szColumns.Add(STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_CATEGORY));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_NAME)) ? (rColumns.Width() / 3) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_DESCRIPTION) || m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_TITLEITEM_ADDRESS)) ? (rColumns.Width() / 2) : ((7 * rColumns.Width()) / 24)));
		continue;
	}
	EnumOBProcessors();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME_BROWSE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_ADDRESS_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_ADDRESS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_CATEGORY_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_CATEGORY_CONFIGURATION)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_CATEGORY_SYMBOLIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST_STATIC)->EnableWindow();
	return TRUE;
}

void CDatabaseOBProcessorsImportDialog::OnFileNameBrowse()
{
	CDatabaseTablesFileBrowseDialog  cFileBrowseDialog(this, IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME, STRING(IDS_DATABASEOBPROCESSORSFILEBROWSEDIALOG_FILEEXTENSION), STRING(IDS_DATABASEOBPROCESSORSFILEBROWSEDIALOG_FILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME_INSPECT)->EnableWindow(GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME)->GetWindowTextLength() > 0);
	SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CDatabaseOBProcessorsImportDialog::OnFileNameInspect()
{
	INT  nIndex;
	CString  szFileName;
	CDatabaseOBProcessor  cDatabaseOBProcessor;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME)->GetWindowText(szFileName); ImportData(szFileName, &cDatabaseOBProcessor); )
	{
		CheckDlgButton(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_CATEGORY_CONFIGURATION, TranslateCategory(&cDatabaseOBProcessor));
		CheckDlgButton(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_CATEGORY_SYMBOLIC, !IsDlgButtonChecked(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_CATEGORY_CONFIGURATION));
		GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_NAME)->SetWindowText(cDatabaseOBProcessor.GetName());
		GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_ADDRESS)->SetWindowText(cDatabaseOBProcessor.GetDetails());
		GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_COMMENT)->ShowWindow(((nIndex = m_pDatabaseOBProcessors[0].Find(cDatabaseOBProcessor.GetName())) >= 0) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_COMMENT)->EnableWindow((nIndex >= 0) ? TRUE : FALSE);
		GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_NAME)->EnableWindow(TRUE);
		for (Listview_SetCurText(GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST), nIndex); nIndex >= 0; )
		{
			GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST)->SetFocus();
			break;
		}
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	CheckDlgButton(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_CATEGORY_CONFIGURATION, FALSE);
	CheckDlgButton(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_CATEGORY_SYMBOLIC, FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_ADDRESS)->SetWindowText(m_szText);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_COMMENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_COMMENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_NAME)->EnableWindow(FALSE);
	Listview_SetCurText(GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_LIST), -1);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CDatabaseOBProcessorsImportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME_INSPECT)->EnableWindow(GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME)->GetWindowTextLength() > 0);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CDatabaseOBProcessorsImportDialog::OnEditchangeName()
{
	INT  nIndex;
	CString  szName;
	CString  szFileName;
	CDatabaseOBProcessor  cDatabaseOBProcessor;

	for (GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_NAME)->GetWindowText(szName), GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME)->GetWindowText(szFileName); ImportData(szFileName, &cDatabaseOBProcessor); )
	{
		GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_COMMENT)->ShowWindow(((nIndex = m_pDatabaseOBProcessors[0].Find(szName)) >= 0) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_COMMENT)->EnableWindow((nIndex >= 0) ? TRUE : FALSE);
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_COMMENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_COMMENT)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CDatabaseOBProcessorsImportDialog::OnOK()
{
	CString  szName;
	CString  szMessage;
	CString  szFileName;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_PROPERTIES_NAME)->GetWindowText(szName), GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME)->GetWindowText(szFileName); (pDatabaseOBProcessor = new CDatabaseOBProcessor); )
	{
		if (ImportData(szFileName, pDatabaseOBProcessor))
		{
			pDatabaseOBProcessor->SetName(szName);
			m_pDatabaseOBProcessors[1].Add(pDatabaseOBProcessor);
			break;
		}
		szMessage.Format(STRING(IDS_DATABASEOBPROCESSORSIMPORTDIALOG_FILEIMPORT_FAILURE), (LPCTSTR)pDatabaseOBProcessor->GetName(), (LPCTSTR)szFileName);
		GetDatabase()->ShowMessage(szMessage);
		delete pDatabaseOBProcessor;
		EndDialog(IDCANCEL);
		return;
	}
	EndDialog(IDOK);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorsExportDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseOBProcessorsExportDialog, CDatabaseTablesDialog)

CDatabaseOBProcessorsExportDialog::CDatabaseOBProcessorsExportDialog(CWnd *pParentWnd, CDatabaseEngine *pDatabaseEngine) : CDatabaseTablesDialog(pDatabaseEngine)
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CDatabaseOBProcessorsExportDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT_PTR CDatabaseOBProcessorsExportDialog::DoModal(CDatabaseOBProcessors &pDatabaseOBProcessors)
{
	m_pDatabaseOBProcessors.Copy(&pDatabaseOBProcessors);
	return CDatabaseTablesDialog::DoModal();
}

VOID CDatabaseOBProcessorsExportDialog::EnumOBProcessors()
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
				for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_NAME); )
				{
					szItem = pDatabaseOBProcessor->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseOBProcessor->GetDescription();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_ADDRESS); )
				{
					szItem = pDatabaseOBProcessor->GetDetails();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_CATEGORY); )
				{
					szItem = GetDatabase()->TranslateOBProcessorAddressBase(pDatabaseOBProcessor->GetAttributes(), FALSE);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST), nProcessor, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST), nProcessor, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST), 0);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseOBProcessorsExportDialog::ExportData(LPCTSTR pszFileName, LPCTSTR pszData) CONST
{
	DWORD  cbBuffer;
	LPSTR  pszBuffer;
	CFileEx  cFile;

	if (cFile.Open(pszFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
	{
		if ((pszBuffer = (LPSTR)GlobalAlloc(GPTR, lstrlen(pszData) + 1)))
		{
#ifndef UNICODE
			strcpy_s(pszBuffer, lstrlen(pszData) + 1, pszData);
#else
			WideCharToMultiByte(CP_ACP, 0, pszData, -1, pszBuffer, lstrlen(pszData) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#endif
			if (WriteFile(cFile.m_hFile, pszBuffer, (DWORD)strlen(pszBuffer), &cbBuffer, (LPOVERLAPPED)NULL))
			{
				GlobalFree(pszBuffer);
				cFile.Close();
				return TRUE;
			}
			GlobalFree(pszBuffer);
		}
		cFile.Close();
		CFileEx::Remove(pszFileName);
	}
	return FALSE;
}

CString CDatabaseOBProcessorsExportDialog::TranslateCategory(CONST CDatabaseOBProcessor *pDatabaseOBProcssor) CONST
{
	INT  nMemoryArea;
	INT  nMemoryAreas;
	CDatabaseOBProcessorMemoryArea  *pDatabaseOBProcessorMemoryArea;

	for (nMemoryArea = 0, nMemoryAreas = (INT)pDatabaseOBProcssor->GetSize(); nMemoryArea < nMemoryAreas; nMemoryArea++)
	{
		if ((pDatabaseOBProcessorMemoryArea = pDatabaseOBProcssor->GetAt(nMemoryArea)) != (CDatabaseOBProcessorMemoryArea *)NULL)
		{
			if (pDatabaseOBProcessorMemoryArea->GetAttributes() & (OBPROCESSORMEMORYAREA_FLAG_PATCHABLE | OBPROCESSORMEMORYAREA_FLAG_PATCHALWAYS | OBPROCESSORMEMORYAREA_FLAG_DUMPABLE | OBPROCESSORMEMORYAREA_FLAG_DUMPALWAYS)) break;
			continue;
		}
	}
	return((nMemoryArea < nMemoryAreas) ? STRINGCHAR(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_CATEGORY_CONFIGURATION) : STRINGCHAR(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_CATEGORY_SYMBOLIC));
}

CString CDatabaseOBProcessorsExportDialog::TranslateStartAddress(CONST CDatabaseOBProcessor *pDatabaseOBProcssor) CONST
{
	UINT  nAddress[2][2];
	CStringTools  cStringTools;

	return((pDatabaseOBProcssor->GetAddressRange(nAddress[0][0], nAddress[0][1], nAddress[1][0], nAddress[1][1])) ? cStringTools.ConvertUIntToPaddedString(nAddress[0][0] + nAddress[0][1], 8, 16) : EMPTYSTRING);
}
CString CDatabaseOBProcessorsExportDialog::TranslateStartAddress(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcssorMemoryArea) CONST
{
	UINT  nAddress[2];
	CStringTools  cStringTools;
	CDatabaseOBProcessorMemoryAreaBlock  *pDatabaseOBProcessorMemoryAreaBlock;

	return(((pDatabaseOBProcessorMemoryAreaBlock = pDatabaseOBProcssorMemoryArea->GetAt(0)) && pDatabaseOBProcessorMemoryAreaBlock->GetAddress(nAddress[0], nAddress[1])) ? cStringTools.ConvertUIntToPaddedString(nAddress[0] + nAddress[1], 8, 16) : EMPTYSTRING);
}

CString CDatabaseOBProcessorsExportDialog::TranslateEndAddress(CONST CDatabaseOBProcessor *pDatabaseOBProcssor) CONST
{
	UINT  nAddress[2][2];
	CStringTools  cStringTools;

	return((pDatabaseOBProcssor->GetAddressRange(nAddress[0][0], nAddress[0][1], nAddress[1][0], nAddress[1][1])) ? cStringTools.ConvertUIntToPaddedString(nAddress[1][0] + nAddress[1][1], 8, 16) : EMPTYSTRING);
}

CString CDatabaseOBProcessorsExportDialog::TranslateAddressLength(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcssorMemoryArea) CONST
{
	UINT  nAddress[2][2];
	CStringTools  cStringTools;
	CDatabaseOBProcessorMemoryAreaBlock  *pDatabaseOBProcessorMemoryAreaBlock[2];

	return((((pDatabaseOBProcessorMemoryAreaBlock[1] = ((pDatabaseOBProcessorMemoryAreaBlock[0] = pDatabaseOBProcssorMemoryArea->GetAt(0))) ? pDatabaseOBProcssorMemoryArea->GetAt((INT)pDatabaseOBProcssorMemoryArea->GetUpperBound()) : (CDatabaseOBProcessorMemoryAreaBlock *)NULL)) && pDatabaseOBProcessorMemoryAreaBlock[0]->GetAddress(nAddress[0][0], nAddress[0][1]) && pDatabaseOBProcessorMemoryAreaBlock[1]->GetAddress(nAddress[1][0], nAddress[1][1])) ? cStringTools.ConvertUIntToPaddedString(nAddress[1][0] + nAddress[1][1] - nAddress[0][0] - nAddress[0][1] + 1, 8, 16) : EMPTYSTRING);
}

CString CDatabaseOBProcessorsExportDialog::TranslatePatchFlag(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcssorMemoryArea) CONST
{
	return GetDatabase()->TranslateOBProcessorMemoryAreaPatchFlag(pDatabaseOBProcssorMemoryArea->GetAttributes());
}

CString CDatabaseOBProcessorsExportDialog::TranslateDumpFlag(CONST CDatabaseOBProcessorMemoryArea *pDatabaseOBProcssorMemoryArea) CONST
{
	return GetDatabase()->TranslateOBProcessorMemoryAreaDumpFlag(pDatabaseOBProcssorMemoryArea->GetAttributes());
}

CString CDatabaseOBProcessorsExportDialog::ConstructDefaultDirectory() CONST
{
	TCHAR  szPath[MAX_PATH];

	for (_tcscpy_s(szPath, sizeof(szPath) / sizeof(TCHAR), GetDatabase()->GetFileName()); !PathRemoveFileSpec(szPath); )
	{
		_tcscpy_s(szPath, sizeof(szPath) / sizeof(TCHAR), EMPTYSTRING);
		break;
	}
	return szPath;
}

CString CDatabaseOBProcessorsExportDialog::ConstructFileName(CONST CDatabaseOBProcessor *pDatabaseOBProcssor, LPCTSTR pszDirectory, LPCTSTR pszFileName) CONST
{
	CString  szFileName;
	CTimeKey  tFileTime;
	CLogicalDrives  cDrives;

	if (!lstrlen(pszFileName))
	{
		for (szFileName = pszDirectory; !szFileName.IsEmpty() && szFileName.Right(1) != cDrives.GetPathDelimiter(); )
		{
			szFileName += cDrives.GetPathDelimiter();
			break;
		}
		szFileName += pDatabaseOBProcssor->GetName() + STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_FILENAME_SEPARATOR);
		szFileName += (!pDatabaseOBProcssor->GetMasterImage().IsEmpty()) ? (pDatabaseOBProcssor->GetMasterImage() + STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_FILENAME_SEPARATOR)) : EMPTYSTRING;
		szFileName += TranslateCategory(pDatabaseOBProcssor) + STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_FILENAME_SEPARATOR);
		szFileName += tFileTime.FormatGmt(STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_FILENAME_TIMEFORMAT)) + STRING(IDS_DATABASEOBPROCESSORSFILEBROWSEDIALOG_FILEEXTENSION);
		return szFileName;
	}
	return pszFileName;
}

BOOL CDatabaseOBProcessorsExportDialog::Check(BOOL bModified) CONST
{
	return((((IsDlgButtonChecked(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_CUSTOM) && GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->GetWindowTextLength() > 0) || IsDlgButtonChecked(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_STANDARD)) && Listview_GetCurText(GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST)) >= 0) ? TRUE : FALSE);
}

void CDatabaseOBProcessorsExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CDatabaseTablesDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseOBProcessorsExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseOBProcessorsExportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseOBProcessors.RemoveAll();
	CDatabaseTablesDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseOBProcessorsExportDialog, CDatabaseTablesDialog)
	//{{AFX_MSG_MAP(CDatabaseOBProcessorsExportDialog)
	ON_BN_CLICKED(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_CUSTOM, OnCustomExport)
	ON_BN_CLICKED(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_STANDARD, OnStandardExport)
	ON_BN_CLICKED(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_BROWSE, OnFileNameBrowse)
	ON_BN_CLICKED(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY_BROWSE, OnDirectoryBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseOBProcessorsExportDialog message handlers

BOOL CDatabaseOBProcessorsExportDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDatabaseTablesDialog::OnInitDialog();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_ADDRESS));
	m_szColumns.Add(STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_CATEGORY));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_NAME)) ? (rColumns.Width() / 3) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_DESCRIPTION) || m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_TITLEITEM_ADDRESS)) ? (rColumns.Width() / 2) : ((7 * rColumns.Width()) / 24)));
		continue;
	}
	EnumOBProcessors();
	CheckDlgButton(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_CUSTOM, TRUE);
	CheckDlgButton(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_STANDARD, FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_STANDARD)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_BROWSE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CDatabaseOBProcessorsExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_DATABASE_OBPROCESSORS_EXPORT_LIST)
	{
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST, LVM_GETSELECTEDCOUNT) > 1)

			{
				CheckDlgButton(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_CUSTOM, FALSE);
				CheckDlgButton(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_STANDARD, TRUE);
				GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY)->SetWindowText(ConstructDefaultDirectory());
				GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_BROWSE)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY_STATIC)->EnableWindow();
				GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY)->EnableWindow();
				GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY_BROWSE)->EnableWindow();
				SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY, EM_SETSEL, 0, -1);
			}
			else  GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_CUSTOM)->EnableWindow();
			GetDlgItem(IDOK)->EnableWindow(Check());
		}
	}
	return CDatabaseTablesDialog::OnNotify(wParam, lParam, pResult);
}

void CDatabaseOBProcessorsExportDialog::OnCustomExport()
{
	CheckDlgButton(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_CUSTOM, TRUE);
	CheckDlgButton(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_STANDARD, FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_BROWSE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY_BROWSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseOBProcessorsExportDialog::OnStandardExport()
{
	CheckDlgButton(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_CUSTOM, FALSE);
	CheckDlgButton(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_STANDARD, TRUE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY)->SetWindowText(ConstructDefaultDirectory());
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME_BROWSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY)->EnableWindow();
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY_BROWSE)->EnableWindow();
	SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseOBProcessorsExportDialog::OnFileNameBrowse()
{
	CDatabaseTablesFileBrowseDialog  cFileBrowseDialog(this, IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME, STRING(IDS_DATABASEOBPROCESSORSFILEBROWSEDIALOG_FILEEXTENSION), STRING(IDS_DATABASEOBPROCESSORSFILEBROWSEDIALOG_FILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseOBProcessorsExportDialog::OnDirectoryBrowse()
{
	LPMALLOC  pIMalloc;
	LPITEMIDLIST  pItemIDList;
	TCHAR  szItemBuffer[MAX_PATH];
	TCHAR  szDisplayName[MAX_PATH];
	BROWSEINFO  sBrowseInfo = { 0 };

	if (SHGetMalloc(&pIMalloc) == NOERROR)
	{
		for (sBrowseInfo.hwndOwner = GetSafeHwnd(), sBrowseInfo.pszDisplayName = szDisplayName, sBrowseInfo.lpszTitle = STRING(IDS_DIRECTORYBROWSEDIALOG_TITLE); (pItemIDList = SHBrowseForFolder(&sBrowseInfo)); )
		{
			if (SHGetPathFromIDList(pItemIDList, szItemBuffer)) GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY)->SetWindowText(szItemBuffer);
			pIMalloc->Free(pItemIDList);
			break;
		}
		pIMalloc->Release();
	}
	SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseOBProcessorsExportDialog::OnOK()
{
	INT  nIndex;
	INT  nCount;
	INT  nProcessor;
	INT  nProcessors;
	INT  nMemoryArea;
	INT  nMemoryAreas;
	CString  szMessage;
	CString  szAddress;
	CString  szFileName;
	CString  szDirectory;
	CString  szProcessor;
	CUIntArray  nIndexes;
	CStringArray  szAddresses;
	CStringTools  cStringTools;
	CDatabaseOBProcessor  *pDatabaseOBProcessor;
	CDatabaseOBProcessorMemoryArea  *pDatabaseOBProcessorMemoryArea;
	CHourglassCursor  cCursor;

	for (nProcessor = 0, nProcessors = (INT)SendDlgItemMessage(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST, LVM_GETITEMCOUNT); nProcessor < nProcessors; nProcessor++)
	{
		if ((pDatabaseOBProcessor = (Listview_IsSelText(GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_LIST), nProcessor)) ? m_pDatabaseOBProcessors.GetAt(nProcessor) : (CDatabaseOBProcessor *)NULL))
		{
			for (nMemoryArea = 0, nMemoryAreas = (INT)pDatabaseOBProcessor->GetSize(), szProcessor = pDatabaseOBProcessor->GetName() + CR + pDatabaseOBProcessor->GetDescription() + CR + TranslateCategory(pDatabaseOBProcessor) + CR + pDatabaseOBProcessor->GetMasterImage() + CR + GetDatabase()->TranslateOBProcessorAddressBase(pDatabaseOBProcessor->GetAttributes()) + CR + CR + TranslateStartAddress(pDatabaseOBProcessor) + CR + TranslateEndAddress(pDatabaseOBProcessor) + CR + cStringTools.ConvertLongIntToString(pDatabaseOBProcessor->GetSize()) + CR, szAddresses.RemoveAll(), nIndexes.RemoveAll(); nMemoryArea < nMemoryAreas; nMemoryArea++)
			{
				if ((pDatabaseOBProcessorMemoryArea = pDatabaseOBProcessor->GetAt(nMemoryArea)))
				{
					szAddress = TranslateStartAddress(pDatabaseOBProcessorMemoryArea);
					for (nIndex = 0, nCount = (INT)szAddresses.GetSize(); nIndex < nCount; nIndex++)
					{
						if (szAddress < szAddresses.GetAt(nIndex)) break;
						continue;
					}
					szAddresses.InsertAt(nIndex, szAddress);
					nIndexes.InsertAt(nIndex, nMemoryArea);
				}
			}
			for (nMemoryArea = 0; nMemoryArea < nIndexes.GetSize(); nMemoryArea++)
			{
				if ((pDatabaseOBProcessorMemoryArea = pDatabaseOBProcessor->GetAt(nIndexes.GetAt(nMemoryArea))))
				{
					szProcessor += pDatabaseOBProcessorMemoryArea->GetName() + TAB;
					szProcessor += TranslateStartAddress(pDatabaseOBProcessorMemoryArea) + TAB;
					szProcessor += TranslateAddressLength(pDatabaseOBProcessorMemoryArea) + TAB + TAB;
					szProcessor += TranslatePatchFlag(pDatabaseOBProcessorMemoryArea) + TAB;
					szProcessor += TranslateDumpFlag(pDatabaseOBProcessorMemoryArea) + TAB;
					szProcessor += pDatabaseOBProcessorMemoryArea->GetDescription() + CR;
				}
			}
			GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_FILENAME)->GetWindowText(szFileName);
			GetDlgItem(IDC_DATABASE_OBPROCESSORS_EXPORT_DIRECTORY)->GetWindowText(szDirectory);
			if (!ExportData((szFileName = ConstructFileName(pDatabaseOBProcessor, szDirectory, szFileName)), szProcessor))
			{
				szMessage.Format(STRING(IDS_DATABASEOBPROCESSORSEXPORTDIALOG_FILEEXPORT_FAILURE), (LPCTSTR)pDatabaseOBProcessor->GetName(), (LPCTSTR)szFileName);
				GetDatabase()->ShowMessage(szMessage);
			}
		}
	}
	EndDialog(IDOK);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseMemoryImagesImportDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseMemoryImagesImportDialog, CDatabaseTablesDialog)

CDatabaseMemoryImagesImportDialog::CDatabaseMemoryImagesImportDialog(CWnd *pParentWnd, CDatabaseEngine *pDatabaseEngine) : CDatabaseTablesDialog(pDatabaseEngine)
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CDatabaseMemoryImagesImportDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT_PTR CDatabaseMemoryImagesImportDialog::DoModal(CDatabaseOBProcessorMemoryImages &pDatabaseOBProcessorMemoryImages)
{
	INT_PTR  nResult;

	for (m_pDatabaseOBProcessorMemoryImages[0].Copy(&pDatabaseOBProcessorMemoryImages), m_pDatabaseOBProcessorMemoryImages[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseOBProcessorMemoryImages.Copy(&m_pDatabaseOBProcessorMemoryImages[1]);
		break;
	}
	return nResult;
}

VOID CDatabaseMemoryImagesImportDialog::EnumMemoryImages()
{
	INT  nImage;
	INT  nImages;
	INT  nBlock;
	INT  nBlocks;
	INT  nColumn;
	INT  nColumns;
	UINT  nSize;
	UINT  nAddressPage;
	UINT  nAddressOffset;
	UINT  nAddress[2];
	CString  szItem;
	CString  szVersion;
	CByteArray  nData;
	CByteArray  nMask;
	CStringTools  cStringTools;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;
	CDatabaseOBProcessorMemoryImageBlock  *pDatabaseOBProcessorMemoryImageBlock;

	for (nImage = 0, nImages = (INT)m_pDatabaseOBProcessorMemoryImages[0].GetSize(); nImage < nImages; nImage++)
	{
		if ((pDatabaseOBProcessorMemoryImage = m_pDatabaseOBProcessorMemoryImages[0].GetAt(nImage)))
		{
			for (nBlock = 0, nBlocks = (INT)pDatabaseOBProcessorMemoryImage->GetSize(), nAddressPage = nAddressOffset = 0, nSize = 0; nBlock < nBlocks; nBlock++)
			{
				if ((pDatabaseOBProcessorMemoryImageBlock = pDatabaseOBProcessorMemoryImage->GetAt(nBlock)))
				{
					if (pDatabaseOBProcessorMemoryImageBlock->GetVersion() == szVersion || szVersion.IsEmpty())
					{
						if (pDatabaseOBProcessorMemoryImageBlock->GetAddress(nAddress[0], nAddress[1]))
						{
							if (nAddress[0] + nAddress[1] < nAddressPage + nAddressOffset || szVersion.IsEmpty())
							{
								nAddressPage = nAddress[0];
								nAddressOffset = nAddress[1];
							}
							nSize += GetDatabase()->TranslateOBProcessorMemoryImageBlockData(pDatabaseOBProcessorMemoryImageBlock->GetData(), nData, nMask, FALSE);
						}
						szVersion = pDatabaseOBProcessorMemoryImageBlock->GetVersion();
						if (nBlock < nBlocks - 1) continue;
					}
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_NAME); )
						{
							szItem = pDatabaseOBProcessorMemoryImage->GetName();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_VERSION); )
						{
							szItem = szVersion;
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_ADDRESS); )
						{
							szItem = GetDatabase()->TranslateOBProcessorMemoryImageBlockAddress(nAddressPage, nAddressOffset);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_SIZE); )
						{
							szItem = cStringTools.ConvertUIntToStructuredString(nSize);
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST), nImage, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST), nImage, nColumn, szItem);
					}
					nBlock = (nBlock < nBlocks - 1) ? (nBlock - 1) : nBlock;
					szVersion.Empty();
					nSize = 0;
				}
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST), 0);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseMemoryImagesImportDialog::ImportData(LPCTSTR pszFileName, CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage) CONST
{
	DWORD  cbData;
	DWORD  cbBuffer;
	LPSTR  pszBuffer;
	CString  szVersion;
	CString  szValue[3];
	CString  szUnit;
	CString  szData;
	CFileEx  cFile;
	CDatabaseOBProcessorMemoryImageBlock  *pDatabaseOBProcessorMemoryImageBlock;

	if (cFile.Open(pszFileName, CFile::modeRead | CFile::shareDenyWrite))
	{
		if ((pszBuffer = (LPSTR)GlobalAlloc(GPTR, (SIZE_T)(cFile.GetLength() + 1))))
		{
			if (ReadFile(cFile.m_hFile, pszBuffer, (cbData = (DWORD)cFile.GetLength()), &cbBuffer, (LPOVERLAPPED)NULL))
			{
#ifndef UNICODE
				szData = pszBuffer;
#else
				MultiByteToWideChar(CP_ACP, 0, pszBuffer, -1, szData.GetBufferSetLength(cbData), cbData + 1);
				szData.ReleaseBuffer();
#endif
				for (pDatabaseOBProcessorMemoryImage->SetName(ExtractTokenValue(szData, STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TOKEN_DEVICE))), szVersion = ExtractTokenValue(szData, STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TOKEN_VERSION)), szUnit = ExtractTokenValue(szData, STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TOKEN_UNIT)); !(szValue[0] = ExtractTokenValue(szData, STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TOKEN_START))).IsEmpty(); )
				{
					szValue[1] = ExtractTokenValue(szData, STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TOKEN_COUNT));
					szValue[2] = ExtractTokenValue(szData, STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TOKEN_DATA));
					if ((pDatabaseOBProcessorMemoryImageBlock = (!szValue[1].IsEmpty() && !szValue[2].IsEmpty()) ? new CDatabaseOBProcessorMemoryImageBlock : (CDatabaseOBProcessorMemoryImageBlock *)NULL))
					{
						pDatabaseOBProcessorMemoryImageBlock->SetVersion(szVersion);
						pDatabaseOBProcessorMemoryImageBlock->SetAddress(0, (UINT)_ttoi64(szValue[0]));
						pDatabaseOBProcessorMemoryImageBlock->SetData(GetDatabase()->TranslateOBProcessorMemoryImageBlockData(szValue[2]));
						if (pDatabaseOBProcessorMemoryImage->Add(pDatabaseOBProcessorMemoryImageBlock) >= 0) continue;
						delete pDatabaseOBProcessorMemoryImageBlock;
					}
					break;
				}
				if (szValue[0].IsEmpty())
				{
					GlobalFree(pszBuffer);
					cFile.Close();
					return TRUE;
				}
			}
			GlobalFree(pszBuffer);
		}
		cFile.Close();
	}
	return FALSE;
}

CString CDatabaseMemoryImagesImportDialog::TranslateImageVersion(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage) CONST
{
	CDatabaseOBProcessorMemoryImageBlock  *pDatabaseOBProcessorMemoryImageBlock;

	return(((pDatabaseOBProcessorMemoryImageBlock = pDatabaseOBProcessorMemoryImage->GetAt(0))) ? pDatabaseOBProcessorMemoryImageBlock->GetVersion() : EMPTYSTRING);
}

CString CDatabaseMemoryImagesImportDialog::TranslateImageAddress(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage) CONST
{
	UINT  nAddress[2];
	CDatabaseOBProcessorMemoryImageBlock  *pDatabaseOBProcessorMemoryImageBlock;

	return(((pDatabaseOBProcessorMemoryImageBlock = pDatabaseOBProcessorMemoryImage->GetAt(0)) && pDatabaseOBProcessorMemoryImageBlock->GetAddress(nAddress[0], nAddress[1])) ? GetDatabase()->TranslateOBProcessorMemoryImageBlockAddress(nAddress[0], nAddress[1]) : EMPTYSTRING);
}

CString CDatabaseMemoryImagesImportDialog::TranslateImageSize(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage) CONST
{
	INT  nBlock;
	INT  nBlocks;
	UINT  nSize;
	CString  szVersion;
	CByteArray  nData;
	CByteArray  nMask;
	CStringTools  cStringTools;
	CDatabaseOBProcessorMemoryImageBlock  *pDatabaseOBProcessorMemoryImageBlock;

	for (nBlock = 0, nBlocks = (INT)pDatabaseOBProcessorMemoryImage->GetSize(), nSize = 0; nBlock < nBlocks; nBlock++)
	{
		if ((pDatabaseOBProcessorMemoryImageBlock = pDatabaseOBProcessorMemoryImage->GetAt(nBlock)) && (pDatabaseOBProcessorMemoryImageBlock->GetVersion() == szVersion || szVersion.IsEmpty()))
		{
			nSize += GetDatabase()->TranslateOBProcessorMemoryImageBlockData(pDatabaseOBProcessorMemoryImageBlock->GetData(), nData, nMask, FALSE);
			szVersion = pDatabaseOBProcessorMemoryImageBlock->GetVersion();
			continue;
		}
		break;
	}
	return cStringTools.ConvertUIntToStructuredString(nSize);
}

CString CDatabaseMemoryImagesImportDialog::ExtractTokenValue(CString &szData, LPCTSTR pszToken) CONST
{
	INT  nPos[2];
	TCHAR  szChar;
	CString  szValue;

	if ((nPos[0] = szData.Find(pszToken)) >= 0)
	{
		for (nPos[1] = nPos[0] + lstrlen(pszToken); nPos[1] < szData.GetLength(); nPos[1]++)
		{
			if ((szChar = szData.GetAt(nPos[1])) == STRINGCHAR(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TOKEN_SEPARATOR) || szChar == CR || szChar == EOL) break;
			szValue += szChar;
		}
		szData = szData.Left(nPos[0]) + szData.Mid(nPos[1]);
	}
	return szValue;
}

BOOL CDatabaseMemoryImagesImportDialog::Check(BOOL bModified) CONST
{
	return(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_VERSION)->GetWindowTextLength() > 0);
}

void CDatabaseMemoryImagesImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CDatabaseTablesDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseMemoryImagesImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseMemoryImagesImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CDatabaseTablesDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseMemoryImagesImportDialog, CDatabaseTablesDialog)
	//{{AFX_MSG_MAP(CDatabaseMemoryImagesImportDialog)
	ON_BN_CLICKED(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME_BROWSE, OnFileNameBrowse)
	ON_BN_CLICKED(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME_INSPECT, OnFileNameInspect)
	ON_EN_CHANGE(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_NAME, OnEditchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseMemoryImagesImportDialog message handlers

BOOL CDatabaseMemoryImagesImportDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDatabaseTablesDialog::OnInitDialog();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_ADDRESS)->GetWindowText(m_szText);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_VERSION));
	m_szColumns.Add(STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_ADDRESS));
	m_szColumns.Add(STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_SIZE));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_NAME) || m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_VERSION)) ? (rColumns.Width() / 3) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_TITLEITEM_ADDRESS)) ? (rColumns.Width() / 3) : (rColumns.Width() / 4)));
		continue;
	}
	EnumMemoryImages();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME_BROWSE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_NAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_VERSION_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_VERSION)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_ADDRESS_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_ADDRESS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_SIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_SIZE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST_STATIC)->EnableWindow();
	return TRUE;
}

void CDatabaseMemoryImagesImportDialog::OnFileNameBrowse()
{
	CDatabaseTablesFileBrowseDialog  cFileBrowseDialog(this, IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME, STRING(IDS_DATABASEMEMORYIMAGESFILEBROWSEDIALOG_FILEEXTENSION), STRING(IDS_DATABASEMEMORYIMAGESFILEBROWSEDIALOG_FILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME_INSPECT)->EnableWindow(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME)->GetWindowTextLength() > 0);
	SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CDatabaseMemoryImagesImportDialog::OnFileNameInspect()
{
	INT  nIndex;
	CString  szName;
	CString  szVersion;
	CString  szFileName;
	CDatabaseOBProcessorMemoryImage  cDatabaseOBProcessorMemoryImage;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME)->GetWindowText(szFileName); ImportData(szFileName, &cDatabaseOBProcessorMemoryImage); )
	{
		GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_NAME)->SetWindowText((szName = cDatabaseOBProcessorMemoryImage.GetName()));
		GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_VERSION)->SetWindowText((szVersion = TranslateImageVersion(&cDatabaseOBProcessorMemoryImage)));
		GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_ADDRESS)->SetWindowText(TranslateImageAddress(&cDatabaseOBProcessorMemoryImage));
		GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_SIZE)->SetWindowText(TranslateImageSize(&cDatabaseOBProcessorMemoryImage));
		GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_COMMENT)->ShowWindow(((nIndex = m_pDatabaseOBProcessorMemoryImages[0].Find(szName)) >= 0 && m_pDatabaseOBProcessorMemoryImages[0].GetAt(nIndex)->Find(szVersion) >= 0) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_COMMENT)->EnableWindow(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_COMMENT)->IsWindowVisible());
		GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_NAME)->EnableWindow(TRUE);
		for (Listview_SetCurText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST), nIndex); nIndex >= 0; )
		{
			GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST)->SetFocus();
			break;
		}
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_VERSION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_ADDRESS)->SetWindowText(m_szText);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_SIZE)->SetWindowText(m_szText);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_COMMENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_COMMENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_NAME)->EnableWindow(FALSE);
	Listview_SetCurText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_LIST), -1);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CDatabaseMemoryImagesImportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME_INSPECT)->EnableWindow(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME)->GetWindowTextLength() > 0);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CDatabaseMemoryImagesImportDialog::OnEditchangeName()
{
	INT  nIndex;
	CString  szName;
	CString  szFileName;
	CDatabaseOBProcessorMemoryImage  cDatabaseOBProcessorMemoryImage;

	for (GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_NAME)->GetWindowText(szName), GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_FILENAME)->GetWindowText(szFileName); ImportData(szFileName, &cDatabaseOBProcessorMemoryImage); )
	{
		GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_COMMENT)->ShowWindow(((nIndex = m_pDatabaseOBProcessorMemoryImages[0].Find(szName)) >= 0) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_COMMENT)->EnableWindow((nIndex >= 0) ? TRUE : FALSE);
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_COMMENT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_COMMENT)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CDatabaseMemoryImagesImportDialog::OnOK()
{
	INT  nBlock;
	INT  nBlocks;
	CString  szName;
	CString  szVersion;
	CString  szMessage;
	CString  szFileName;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;
	CDatabaseOBProcessorMemoryImageBlock  *pDatabaseOBProcessorMemoryImageBlock;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_NAME)->GetWindowText(szName), GetDlgItem(IDC_DATABASE_MEMORYIMAGES_IMPORT_PROPERTIES_VERSION)->GetWindowText(szVersion), GetDlgItem(IDC_DATABASE_OBPROCESSORS_IMPORT_FILENAME)->GetWindowText(szFileName); (pDatabaseOBProcessorMemoryImage = new CDatabaseOBProcessorMemoryImage); )
	{
		if (ImportData(szFileName, pDatabaseOBProcessorMemoryImage))
		{
			pDatabaseOBProcessorMemoryImage->SetName(szName);
			for (nBlock = 0, nBlocks = (INT)pDatabaseOBProcessorMemoryImage->GetSize(); nBlock < nBlocks; nBlock++)
			{
				if ((pDatabaseOBProcessorMemoryImageBlock = pDatabaseOBProcessorMemoryImage->GetAt(nBlock)))
				{
					pDatabaseOBProcessorMemoryImageBlock->SetVersion(szVersion);
					continue;
				}
			}
			m_pDatabaseOBProcessorMemoryImages[1].Add(pDatabaseOBProcessorMemoryImage);
			break;
		}
		szMessage.Format(STRING(IDS_DATABASEMEMORYIMAGESIMPORTDIALOG_FILEIMPORT_FAILURE), (LPCTSTR)szName, (LPCTSTR)szFileName);
		GetDatabase()->ShowMessage(szMessage);
		delete pDatabaseOBProcessorMemoryImage;
		EndDialog(IDCANCEL);
		return;
	}
	EndDialog(IDOK);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseMemoryImagesExportDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseMemoryImagesExportDialog, CDatabaseTablesDialog)

CDatabaseMemoryImagesExportDialog::CDatabaseMemoryImagesExportDialog(CWnd *pParentWnd, CDatabaseEngine *pDatabaseEngine) : CDatabaseTablesDialog(pDatabaseEngine)
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CDatabaseMemoryImagesExportDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT_PTR CDatabaseMemoryImagesExportDialog::DoModal(CDatabaseOBProcessorMemoryImages &pDatabaseOBProcessorMemoryImages)
{
	m_pDatabaseOBProcessorMemoryImages.Copy(&pDatabaseOBProcessorMemoryImages);
	return CDatabaseTablesDialog::DoModal();
}

VOID CDatabaseMemoryImagesExportDialog::EnumMemoryImages()
{
	INT  nImage;
	INT  nImages;
	INT  nBlock;
	INT  nBlocks;
	INT  nColumn;
	INT  nColumns;
	UINT  nSize;
	UINT  nAddressPage;
	UINT  nAddressOffset;
	UINT  nAddress[2];
	CString  szItem;
	CString  szVersion;
	CByteArray  nData;
	CByteArray  nMask;
	CStringTools  cStringTools;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;
	CDatabaseOBProcessorMemoryImageBlock  *pDatabaseOBProcessorMemoryImageBlock;

	for (nImage = 0, nImages = (INT)m_pDatabaseOBProcessorMemoryImages.GetSize(); nImage < nImages; nImage++)
	{
		if ((pDatabaseOBProcessorMemoryImage = m_pDatabaseOBProcessorMemoryImages.GetAt(nImage)))
		{
			for (nBlock = 0, nBlocks = (INT)pDatabaseOBProcessorMemoryImage->GetSize(), nAddressPage = nAddressOffset = 0, nSize = 0; nBlock < nBlocks; nBlock++)
			{
				if ((pDatabaseOBProcessorMemoryImageBlock = pDatabaseOBProcessorMemoryImage->GetAt(nBlock)))
				{
					if (pDatabaseOBProcessorMemoryImageBlock->GetVersion() == szVersion || szVersion.IsEmpty())
					{
						if (pDatabaseOBProcessorMemoryImageBlock->GetAddress(nAddress[0], nAddress[1]))
						{
							if (nAddress[0] + nAddress[1] < nAddressPage + nAddressOffset || szVersion.IsEmpty())
							{
								nAddressPage = nAddress[0];
								nAddressOffset = nAddress[1];
							}
							nSize += GetDatabase()->TranslateOBProcessorMemoryImageBlockData(pDatabaseOBProcessorMemoryImageBlock->GetData(), nData, nMask, FALSE);
						}
						szVersion = pDatabaseOBProcessorMemoryImageBlock->GetVersion();
						if (nBlock < nBlocks - 1) continue;
					}
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_NAME); )
						{
							szItem = pDatabaseOBProcessorMemoryImage->GetName();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_VERSION); )
						{
							szItem = szVersion;
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_ADDRESS); )
						{
							szItem = GetDatabase()->TranslateOBProcessorMemoryImageBlockAddress(nAddressPage, nAddressOffset);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_SIZE); )
						{
							szItem = cStringTools.ConvertUIntToStructuredString(nSize);
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST), nImage, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST), nImage, nColumn, szItem);
					}
					nBlock = (nBlock < nBlocks - 1) ? (nBlock - 1) : nBlock;
					szVersion.Empty();
					nSize = 0;
				}
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST), 0);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

VOID CDatabaseMemoryImagesExportDialog::EnumAddressBases()
{
	INT  nIndex;
	INT  nCount;
	CUIntArray  nBases;
	CStringArray  szBases;

	for (nIndex = 0, nCount = GetDatabase()->EnumOBProcessorAddressBases(szBases, nBases); nIndex < nCount; nIndex++)
	{
		SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_ADDRESSBASE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szBases.GetAt(nIndex));
		continue;
	}
	SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_ADDRESSBASE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_ADDRESSBASE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetDatabase()->TranslateOBProcessorAddressBase(OBPROCESSOR_ADDRESSWIDTH_WORDS, FALSE)));
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_ADDRESSBASE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_ADDRESSBASE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_ADDRESSBASE)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_ADDRESSBASE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseMemoryImagesExportDialog::ExportData(LPCTSTR pszFileName, LPCTSTR pszData) CONST
{
	DWORD  cbBuffer;
	LPSTR  pszBuffer;
	CFileEx  cFile;

	if (cFile.Open(pszFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
	{
		if ((pszBuffer = (LPSTR)GlobalAlloc(GPTR, lstrlen(pszData) + 1)))
		{
#ifndef UNICODE
			strcpy_s(pszBuffer, lstrlen(pszData) + 1, pszData);
#else
			WideCharToMultiByte(CP_ACP, 0, pszData, -1, pszBuffer, lstrlen(pszData) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#endif
			if (WriteFile(cFile.m_hFile, pszBuffer, (DWORD)strlen(pszBuffer), &cbBuffer, (LPOVERLAPPED)NULL))
			{
				GlobalFree(pszBuffer);
				cFile.Close();
				return TRUE;
			}
			GlobalFree(pszBuffer);
		}
		cFile.Close();
		CFileEx::Remove(pszFileName);
	}
	return FALSE;
}

CString CDatabaseMemoryImagesExportDialog::ConstructDefaultDirectory() CONST
{
	TCHAR  szPath[MAX_PATH];

	for (_tcscpy_s(szPath, sizeof(szPath) / sizeof(TCHAR), GetDatabase()->GetFileName()); !PathRemoveFileSpec(szPath); )
	{
		_tcscpy_s(szPath, sizeof(szPath) / sizeof(TCHAR), EMPTYSTRING);
		break;
	}
	return szPath;
}

CString CDatabaseMemoryImagesExportDialog::ConstructFileName(LPCTSTR pszName, LPCTSTR pszVersion, LPCTSTR pszDirectory, LPCTSTR pszFileName) CONST
{
	CString  szFileName;
	CTimeKey  tFileTime;
	CLogicalDrives  cDrives;

	if (!lstrlen(pszFileName))
	{
		for (szFileName = pszDirectory; !szFileName.IsEmpty() && szFileName.Right(1) != cDrives.GetPathDelimiter(); )
		{
			szFileName += cDrives.GetPathDelimiter();
			break;
		}
		szFileName += CString(pszName) + STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_FILENAME_SEPARATOR) + pszVersion + STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_FILENAME_SEPARATOR);
		szFileName += tFileTime.FormatGmt(STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_FILENAME_TIMEFORMAT)) + STRING(IDS_DATABASEMEMORYIMAGESFILEBROWSEDIALOG_FILEEXTENSION);
		return szFileName;
	}
	return pszFileName;
}

INT CDatabaseMemoryImagesExportDialog::FindColumnIndex(LPCTSTR pszColumn) CONST
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

BOOL CDatabaseMemoryImagesExportDialog::Check(BOOL bModified) CONST
{
	return((((IsDlgButtonChecked(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_CUSTOM) && GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->GetWindowTextLength() > 0) || IsDlgButtonChecked(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_STANDARD)) && Listview_GetCurText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST)) >= 0) ? TRUE : FALSE);
}

void CDatabaseMemoryImagesExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CDatabaseTablesDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseMemoryImagesExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseMemoryImagesExportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseOBProcessorMemoryImages.RemoveAll();
	CDatabaseTablesDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseMemoryImagesExportDialog, CDatabaseTablesDialog)
	//{{AFX_MSG_MAP(CDatabaseMemoryImagesExportDialog)
	ON_BN_CLICKED(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_CUSTOM, OnCustomExport)
	ON_BN_CLICKED(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_STANDARD, OnStandardExport)
	ON_BN_CLICKED(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_BROWSE, OnFileNameBrowse)
	ON_BN_CLICKED(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY_BROWSE, OnDirectoryBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseMemoryImagesExportDialog message handlers

BOOL CDatabaseMemoryImagesExportDialog::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDatabaseTablesDialog::OnInitDialog();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_VERSION));
	m_szColumns.Add(STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_ADDRESS));
	m_szColumns.Add(STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_SIZE));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST), nColumn, m_szColumns.GetAt(nColumn), (m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_NAME) || m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_VERSION)) ? (rColumns.Width() / 3) : ((m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_ADDRESS)) ? (rColumns.Width() / 3) : (rColumns.Width() / 4)));
		continue;
	}
	EnumMemoryImages();
	EnumAddressBases();
	CheckDlgButton(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_CUSTOM, TRUE);
	CheckDlgButton(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_STANDARD, FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_CUSTOM)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_STANDARD)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_BROWSE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CDatabaseMemoryImagesExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST)
	{
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST, LVM_GETSELECTEDCOUNT) > 1)
			{
				CheckDlgButton(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_CUSTOM, FALSE);
				CheckDlgButton(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_STANDARD, TRUE);
				GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY)->SetWindowText(ConstructDefaultDirectory());
				GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_BROWSE)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY_STATIC)->EnableWindow();
				GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY)->EnableWindow();
				GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY_BROWSE)->EnableWindow();
				SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY, EM_SETSEL, 0, -1);
			}
			else  GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_CUSTOM)->EnableWindow();
			GetDlgItem(IDOK)->EnableWindow(Check());
		}
	}
	return CDatabaseTablesDialog::OnNotify(wParam, lParam, pResult);
}

void CDatabaseMemoryImagesExportDialog::OnCustomExport()
{
	CheckDlgButton(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_CUSTOM, TRUE);
	CheckDlgButton(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_STANDARD, FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_BROWSE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY_BROWSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseMemoryImagesExportDialog::OnStandardExport()
{
	CheckDlgButton(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_CUSTOM, FALSE);
	CheckDlgButton(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_STANDARD, TRUE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY)->SetWindowText(ConstructDefaultDirectory());
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME_BROWSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY)->EnableWindow();
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY_BROWSE)->EnableWindow();
	SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseMemoryImagesExportDialog::OnFileNameBrowse()
{
	CDatabaseTablesFileBrowseDialog  cFileBrowseDialog(this, IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME, STRING(IDS_DATABASEMEMORYIMAGESFILEBROWSEDIALOG_FILEEXTENSION), STRING(IDS_DATABASEMEMORYIMAGESFILEBROWSEDIALOG_FILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseMemoryImagesExportDialog::OnDirectoryBrowse()
{
	LPMALLOC  pIMalloc;
	LPITEMIDLIST  pItemIDList;
	TCHAR  szItemBuffer[MAX_PATH];
	TCHAR  szDisplayName[MAX_PATH];
	BROWSEINFO  sBrowseInfo = { 0 };

	if (SHGetMalloc(&pIMalloc) == NOERROR)
	{
		for (sBrowseInfo.hwndOwner = GetSafeHwnd(), sBrowseInfo.pszDisplayName = szDisplayName, sBrowseInfo.lpszTitle = STRING(IDS_DIRECTORYBROWSEDIALOG_TITLE); (pItemIDList = SHBrowseForFolder(&sBrowseInfo)); )
		{
			if (SHGetPathFromIDList(pItemIDList, szItemBuffer)) GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY)->SetWindowText(szItemBuffer);
			pIMalloc->Free(pItemIDList);
			break;
		}
		pIMalloc->Release();
	}
	SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseMemoryImagesExportDialog::OnOK()
{
	INT  nImage;
	INT  nImages;
	INT  nBlock;
	INT  nBlocks;
	UINT  nAddress[2];
	CString  szName;
	CString  szData;
	CString  szBase;
	CString  szImage;
	CString  szVersion;
	CString  szMessage;
	CString  szFileName;
	CString  szDirectory;
	CStringTools  cStringTools;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;
	CDatabaseOBProcessorMemoryImageBlock  *pDatabaseOBProcessorMemoryImageBlock;
	CHourglassCursor  cCursor;

	for (nImage = 0, nImages = (INT)SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST, LVM_GETITEMCOUNT); nImage < nImages; nImage++)
	{
		if ((pDatabaseOBProcessorMemoryImage = (Listview_IsSelText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST), nImage)) ? m_pDatabaseOBProcessorMemoryImages.GetAt(m_pDatabaseOBProcessorMemoryImages.Find((szName = Listview_GetText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST), nImage, FindColumnIndex(STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_NAME)))))) : (CDatabaseOBProcessorMemoryImage *)NULL))
		{
			for (nBlock = pDatabaseOBProcessorMemoryImage->Find((szVersion = Listview_GetText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_LIST), nImage, FindColumnIndex(STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TITLEITEM_VERSION))))), nBlocks = (INT)pDatabaseOBProcessorMemoryImage->GetSize(), szImage = STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TOKEN_DEVICE) + pDatabaseOBProcessorMemoryImage->GetName() + CR + STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TOKEN_VERSION) + szVersion + CR + STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TOKEN_UNIT) + (szBase = GetDatabase()->TranslateOBProcessorAddressBase(GetDatabase()->TranslateOBProcessorAddressBase(Combobox_GetText(GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_ADDRESSBASE), (INT)SendDlgItemMessage(IDC_DATABASE_MEMORYIMAGES_EXPORT_ADDRESSBASE, CB_GETCURSEL)), FALSE))) + CR; nBlock < nBlocks; nBlock++)
			{
				if ((pDatabaseOBProcessorMemoryImageBlock = pDatabaseOBProcessorMemoryImage->GetAt(nBlock)) && pDatabaseOBProcessorMemoryImageBlock->GetVersion() == szVersion  &&  pDatabaseOBProcessorMemoryImageBlock->GetAddress(nAddress[0], nAddress[1]))
				{
					szImage += STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TOKEN_START) + cStringTools.ConvertUIntToPaddedString(nAddress[0] + nAddress[1], 8, 16) + STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TOKEN_SEPARATOR);
					szImage += STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TOKEN_COUNT) + cStringTools.ConvertLongUIntToString((szData = GetDatabase()->TranslateOBProcessorMemoryImageBlockData(pDatabaseOBProcessorMemoryImageBlock->GetData())).GetLength() / (2 * _ttoi(szBase))) + STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TOKEN_SEPARATOR);
					szImage += STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_TOKEN_DATA) + szData + CR;
					continue;
				}
				break;
			}
			GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_FILENAME)->GetWindowText(szFileName);
			GetDlgItem(IDC_DATABASE_MEMORYIMAGES_EXPORT_DIRECTORY)->GetWindowText(szDirectory);
			if (!ExportData((szFileName = ConstructFileName(szName, szVersion, szDirectory, szFileName)), szImage))
			{
				szMessage.Format(STRING(IDS_DATABASEMEMORYIMAGESEXPORTDIALOG_FILEEXPORT_FAILURE), (LPCTSTR)szName, (LPCTSTR)szFileName);
				GetDatabase()->ShowMessage(szMessage);
			}
		}
	}
	EndDialog(IDOK);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesImportDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseTablesImportDialog, CDatabaseTablesDialog)

CDatabaseTablesImportDialog::CDatabaseTablesImportDialog(CWnd *pParentWnd, CDatabaseEngine *pDatabaseEngine) : CDatabaseTablesDialog(pDatabaseEngine)
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CDatabaseTablesImportDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCPackets &pDatabaseTCPackets)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET, m_pDatabaseTCPackets[0].Copy(&pDatabaseTCPackets), m_pDatabaseTCPackets[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCPackets.Copy(&m_pDatabaseTCPackets[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTMNumCalTables &pDatabaseTMNumCalTables)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE, m_pDatabaseTMNumCalTables[0].Copy(&pDatabaseTMNumCalTables), m_pDatabaseTMNumCalTables[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMNumCalTables.Copy(&m_pDatabaseTMNumCalTables[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTMTxtCalTables &pDatabaseTMTxtCalTables)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE, m_pDatabaseTMTxtCalTables[0].Copy(&pDatabaseTMTxtCalTables), m_pDatabaseTMTxtCalTables[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMTxtCalTables.Copy(&m_pDatabaseTMTxtCalTables[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCNumCalTables &pDatabaseTCNumCalTables)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE, m_pDatabaseTCNumCalTables[0].Copy(&pDatabaseTCNumCalTables), m_pDatabaseTCNumCalTables[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCNumCalTables.Copy(&m_pDatabaseTCNumCalTables[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCTxtCalTables &pDatabaseTCTxtCalTables)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE, m_pDatabaseTCTxtCalTables[0].Copy(&pDatabaseTCTxtCalTables), m_pDatabaseTCTxtCalTables[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCTxtCalTables.Copy(&m_pDatabaseTCTxtCalTables[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCNumOolTables &pDatabaseTCNumOolTables)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE, m_pDatabaseTCNumOolTables[0].Copy(&pDatabaseTCNumOolTables), m_pDatabaseTCNumOolTables[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCNumOolTables.Copy(&m_pDatabaseTCNumOolTables[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCTxtOolTables &pDatabaseTCTxtOolTables)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE, m_pDatabaseTCTxtOolTables[0].Copy(&pDatabaseTCTxtOolTables), m_pDatabaseTCTxtOolTables[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCTxtOolTables.Copy(&m_pDatabaseTCTxtOolTables[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCExeVerStages &pDatabaseTCExeVerStages)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE, m_pDatabaseTCExeVerStages[0].Copy(&pDatabaseTCExeVerStages), m_pDatabaseTCExeVerStages[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCExeVerStages.Copy(&m_pDatabaseTCExeVerStages[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCExeVerGroups &pDatabaseTCExeVerGroups)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP, m_pDatabaseTCExeVerGroups[0].Copy(&pDatabaseTCExeVerGroups), m_pDatabaseTCExeVerGroups[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCExeVerGroups.Copy(&m_pDatabaseTCExeVerGroups[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTMPacketGroups &pDatabaseTMPacketGroups)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP, m_pDatabaseTMPacketGroups[0].Copy(&pDatabaseTMPacketGroups), m_pDatabaseTMPacketGroups[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMPacketGroups.Copy(&m_pDatabaseTMPacketGroups[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTMPacketHeaders &pDatabaseTMPacketHeaders)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER, m_pDatabaseTMPacketHeaders[0].Copy(&pDatabaseTMPacketHeaders), m_pDatabaseTMPacketHeaders[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMPacketHeaders.Copy(&m_pDatabaseTMPacketHeaders[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTMPacketStreams &pDatabaseTMPacketStreams)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM, m_pDatabaseTMPacketStreams[0].Copy(&pDatabaseTMPacketStreams), m_pDatabaseTMPacketStreams[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMPacketStreams.Copy(&m_pDatabaseTMPacketStreams[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCParameterSets &pDatabaseTCParameterSets)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET, m_pDatabaseTCParameterSets[0].Copy(&pDatabaseTCParameterSets), m_pDatabaseTCParameterSets[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCParameterSets.Copy(&m_pDatabaseTCParameterSets[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCFunctionBlocks &pDatabaseTCFunctionBlocks)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK, m_pDatabaseTCFunctionBlocks[0].Copy(&pDatabaseTCFunctionBlocks), m_pDatabaseTCFunctionBlocks[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCFunctionBlocks.Copy(&m_pDatabaseTCFunctionBlocks[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTMParameterGroups &pDatabaseTMParameterGroups)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP, m_pDatabaseTMParameterGroups[0].Copy(&pDatabaseTMParameterGroups), m_pDatabaseTMParameterGroups[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMParameterGroups.Copy(&m_pDatabaseTMParameterGroups[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCPacketParameters &pDatabaseTCPacketParameters)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER, m_pDatabaseTCPacketParameters[0].Copy(&pDatabaseTCPacketParameters), m_pDatabaseTCPacketParameters[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCPacketParameters.Copy(&m_pDatabaseTCPacketParameters[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCParameterValueSets &pDatabaseTCParameterValueSets)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET, m_pDatabaseTCParameterValueSets[0].Copy(&pDatabaseTCParameterValueSets), m_pDatabaseTCParameterValueSets[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCParameterValueSets.Copy(&m_pDatabaseTCParameterValueSets[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCFunctionRoutingPaths &pDatabaseTCFunctionRoutingPaths)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH, m_pDatabaseTCFunctionRoutingPaths[0].Copy(&pDatabaseTCFunctionRoutingPaths), m_pDatabaseTCFunctionRoutingPaths[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCFunctionRoutingPaths.Copy(&m_pDatabaseTCFunctionRoutingPaths[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTMPacketIdentifications &pDatabaseTMPacketIdentifications)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION, m_pDatabaseTMPacketIdentifications[0].Copy(&pDatabaseTMPacketIdentifications), m_pDatabaseTMPacketIdentifications[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMPacketIdentifications.Copy(&m_pDatabaseTMPacketIdentifications[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTMPacketIdentificationCriteria &pDatabaseTMPacketIdentificationCriteria)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION, m_pDatabaseTMPacketIdentificationCriteria[0].Copy(&pDatabaseTMPacketIdentificationCriteria), m_pDatabaseTMPacketIdentificationCriteria[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMPacketIdentificationCriteria.Copy(&m_pDatabaseTMPacketIdentificationCriteria[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseOBProcessorMemoryImages &pDatabaseOBProcessorMemoryImages)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE, m_pDatabaseOBProcessorMemoryImages[0].Copy(&pDatabaseOBProcessorMemoryImages), m_pDatabaseOBProcessorMemoryImages[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseOBProcessorMemoryImages.Copy(&m_pDatabaseOBProcessorMemoryImages[1]);
		break;
	}
	return nResult;
}

VOID CDatabaseTablesImportDialog::EnumDatabaseTables()
{
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szFileName;
	CByteArray  cFileBuffer;
	CFileFindEx  cFileFind;

	SendDlgItemMessage(IDC_DATABASE_TABLES_IMPORT_DIRECTORY, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_FILENAME)->GetWindowText(szFileName);
	for (; cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
	{
		if (cFile.Open(szFileName, CFile::modeRead | CFile::shareDenyWrite))
		{
			for (cFileBuffer.SetSize((INT_PTR)cFile.GetLength()); ReadFile(cFile.m_hFile, cFileBuffer.GetData(), (DWORD)cFile.GetLength(), &dwBytes, (LPOVERLAPPED)NULL); )
			{
				switch (DATABASESUBCOMPONENTFROMCODE(m_nComponent))
				{
				case DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION:
				{ EnumTMPacketIdentifications(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION:
				{ EnumTMPacketIdentificationCriteria(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TMPACKETHEADER:
				{ EnumTMPacketHeaders(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TMPACKETSTREAM:
				{ EnumTMPacketStreams(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TMPACKETGROUP:
				{ EnumTMPacketGroups(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET:
				{ EnumTCPackets(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER:
				{ EnumTCPacketParameters(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE:
				{ EnumTCExeVerStages(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP:
				{ EnumTCExeVerGroups(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK:
				{ EnumTCFunctionBlocks(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH:
				{ EnumTCFunctionRoutingPaths(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCPARAMETERSET:
				{ EnumTCParameterSets(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET:
				{ EnumTCParameterValueSets(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE:
				{ EnumOBProcessorMemoryImages(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TMPARAMETERGROUP:
				{ EnumTMParameterGroups(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TMNUMCALTABLE:
				{ EnumTMNumCalTables(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TMTXTCALTABLE:
				{ EnumTMTxtCalTables(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCNUMCALTABLE:
				{ EnumTCNumCalTables(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCTXTCALTABLE:
				{ EnumTCTxtCalTables(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCNUMOOLTABLE:
				{ EnumTCNumOolTables(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCTXTOOLTABLE:
				{ EnumTCTxtOolTables(cFileBuffer);
				break;
				}
				}
				break;
			}
			cFile.Close();
		}
		cFileFind.Close();
		break;
	}
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_IMPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

VOID CDatabaseTablesImportDialog::EnumTCPackets(CONST CByteArray &nData)
{
	INT  nPacket;
	INT  nPackets;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCPacket  *pDatabaseTCPacket;

	for (nPacket = 0, nPackets = (m_pDatabaseTCPackets[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseTCPackets[1].GetSize() : 0; nPacket < nPackets; nPacket++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCPacket = m_pDatabaseTCPackets[1].GetAt(nPacket))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCPacket->GetTag();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCPacket->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nPacket, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nPacket, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTMNumCalTables(CONST CByteArray &nData)
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	for (nTable = 0, nTables = (m_pDatabaseTMNumCalTables[1].Unmap(nData)) ? (INT)m_pDatabaseTMNumCalTables[1].GetSize() : 0; nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMNumCalTable = m_pDatabaseTMNumCalTables[1].GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMNumCalTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTMNumCalTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTMTxtCalTables(CONST CByteArray &nData)
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	for (nTable = 0, nTables = (m_pDatabaseTMTxtCalTables[1].Unmap(nData)) ? (INT)m_pDatabaseTMTxtCalTables[1].GetSize() : 0; nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMTxtCalTable = m_pDatabaseTMTxtCalTables[1].GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMTxtCalTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTMTxtCalTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCNumCalTables(CONST CByteArray &nData)
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;

	for (nTable = 0, nTables = (m_pDatabaseTCNumCalTables[1].Unmap(nData)) ? (INT)m_pDatabaseTCNumCalTables[1].GetSize() : 0; nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCNumCalTable = m_pDatabaseTCNumCalTables[1].GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCNumCalTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCNumCalTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCTxtCalTables(CONST CByteArray &nData)
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	for (nTable = 0, nTables = (m_pDatabaseTCTxtCalTables[1].Unmap(nData)) ? (INT)m_pDatabaseTCTxtCalTables[1].GetSize() : 0; nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCTxtCalTable = m_pDatabaseTCTxtCalTables[1].GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCTxtCalTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCTxtCalTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCNumOolTables(CONST CByteArray &nData)
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;

	for (nTable = 0, nTables = (m_pDatabaseTCNumOolTables[1].Unmap(nData)) ? (INT)m_pDatabaseTCNumOolTables[1].GetSize() : 0; nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCNumOolTable = m_pDatabaseTCNumOolTables[1].GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCNumOolTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCNumOolTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCTxtOolTables(CONST CByteArray &nData)
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;

	for (nTable = 0, nTables = (m_pDatabaseTCTxtOolTables[1].Unmap(nData)) ? (INT)m_pDatabaseTCTxtOolTables[1].GetSize() : 0; nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCTxtOolTable = m_pDatabaseTCTxtOolTables[1].GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCTxtOolTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCTxtOolTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCExeVerStages(CONST CByteArray &nData)
{
	INT  nStage;
	INT  nStages;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCExeVerStage  *pDatabaseTCExeVerStage;

	for (nStage = 0, nStages = (m_pDatabaseTCExeVerStages[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseTCExeVerStages[1].GetSize() : 0; nStage < nStages; nStage++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCExeVerStage = m_pDatabaseTCExeVerStages[1].GetAt(nStage))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCExeVerStage->GetID();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nStage, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nStage, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCExeVerGroups(CONST CByteArray &nData)
{
	INT  nGroup;
	INT  nGroups;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCExeVerGroup  *pDatabaseTCExeVerGroup;

	for (nGroup = 0, nGroups = (m_pDatabaseTCExeVerGroups[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseTCExeVerGroups[1].GetSize() : 0; nGroup < nGroups; nGroup++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCExeVerGroup = m_pDatabaseTCExeVerGroups[1].GetAt(nGroup))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCExeVerGroup->GetID();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCExeVerGroup->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nGroup, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nGroup, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTMPacketGroups(CONST CByteArray &nData)
{
	INT  nGroup;
	INT  nGroups;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacketGroup  *pDatabaseTMPacketGroup;

	for (nGroup = 0, nGroups = (m_pDatabaseTMPacketGroups[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseTMPacketGroups[1].GetSize() : 0; nGroup < nGroups; nGroup++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMPacketGroup = m_pDatabaseTMPacketGroups[1].GetAt(nGroup))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMPacketGroup->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTMPacketGroup->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nGroup, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nGroup, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTMPacketHeaders(CONST CByteArray &nData)
{
	INT  nHeader;
	INT  nHeaders;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacketHeader  *pDatabaseTMPacketHeader;

	for (nHeader = 0, nHeaders = (m_pDatabaseTMPacketHeaders[1].Unmap(nData)) ? (INT)m_pDatabaseTMPacketHeaders[1].GetSize() : 0; nHeader < nHeaders; nHeader++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMPacketHeader = m_pDatabaseTMPacketHeaders[1].GetAt(nHeader))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMPacketHeader->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nHeader, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nHeader, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTMPacketStreams(CONST CByteArray &nData)
{
	INT  nStream;
	INT  nStreams;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacketStream  *pDatabaseTMPacketStream;

	for (nStream = 0, nStreams = (m_pDatabaseTMPacketStreams[1].Unmap(nData)) ? (INT)m_pDatabaseTMPacketStreams[1].GetSize() : 0; nStream < nStreams; nStream++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMPacketStream = m_pDatabaseTMPacketStreams[1].GetAt(nStream))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMPacketStream->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nStream, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nStream, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCParameterSets(CONST CByteArray &nData)
{
	INT  nSet;
	INT  nSets;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	for (nSet = 0, nSets = (m_pDatabaseTCParameterSets[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseTCParameterSets[1].GetSize() : 0; nSet < nSets; nSet++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCParameterSet = m_pDatabaseTCParameterSets[1].GetAt(nSet))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCParameterSet->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCParameterSet->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nSet, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nSet, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCFunctionBlocks(CONST CByteArray &nData)
{
	INT  nBlock;
	INT  nBlocks;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCFunctionBlock  *pDatabaseTCFunctionBlock;

	for (nBlock = 0, nBlocks = (m_pDatabaseTCFunctionBlocks[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseTCFunctionBlocks[1].GetSize() : 0; nBlock < nBlocks; nBlock++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCFunctionBlock = m_pDatabaseTCFunctionBlocks[1].GetAt(nBlock))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCFunctionBlock->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = EMPTYSTRING;
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nBlock, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nBlock, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTMParameterGroups(CONST CByteArray &nData)
{
	INT  nGroup;
	INT  nGroups;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMParameterGroup  *pDatabaseTMParameterGroup;

	for (nGroup = 0, nGroups = (m_pDatabaseTMParameterGroups[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseTMParameterGroups[1].GetSize() : 0; nGroup < nGroups; nGroup++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMParameterGroup = m_pDatabaseTMParameterGroups[1].GetAt(nGroup))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMParameterGroup->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTMParameterGroup->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nGroup, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nGroup, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCPacketParameters(CONST CByteArray &nData)
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	CString  szItem;
	CDatabaseTCPacketParameter  *pDatabaseTCPacketParameter;

	for (nParameter = 0, nParameters = (m_pDatabaseTCPacketParameters[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseTCPacketParameters[1].GetSize() : 0; nParameter < nParameters; nParameter++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCPacketParameter = m_pDatabaseTCPacketParameters[1].GetAt(nParameter))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCPacketParameter->GetTag();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCPacketParameter->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nParameter, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nParameter, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCParameterValueSets(CONST CByteArray &nData)
{
	INT  nSet;
	INT  nSets;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCParameterValueSet  *pDatabaseTCParameterValueSet;

	for (nSet = 0, nSets = (m_pDatabaseTCParameterValueSets[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseTCParameterValueSets[1].GetSize() : 0; nSet < nSets; nSet++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCParameterValueSet = m_pDatabaseTCParameterValueSets[1].GetAt(nSet))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCParameterValueSet->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCParameterValueSet->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nSet, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nSet, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTCFunctionRoutingPaths(CONST CByteArray &nData)
{
	INT  nPath;
	INT  nPaths;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CStringTools  cStringTools;
	CDatabaseTCFunctionRoutingPath  *pDatabaseTCFunctionRoutingPath;

	for (nPath = 0, nPaths = (m_pDatabaseTCFunctionRoutingPaths[1].Unmap(nData)) ? (INT)m_pDatabaseTCFunctionRoutingPaths[1].GetSize() : 0; nPath < nPaths; nPath++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCFunctionRoutingPath = m_pDatabaseTCFunctionRoutingPaths[1].GetAt(nPath))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = cStringTools.ConvertIntToString(pDatabaseTCFunctionRoutingPath->GetAPID());
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCFunctionRoutingPath->GetPath();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nPath, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nPath, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTMPacketIdentifications(CONST CByteArray &nData)
{
	INT  nID;
	INT  nIDs;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacketIdentification  *pDatabaseTMPacketIdentification;

	for (nID = 0, nIDs = (m_pDatabaseTMPacketIdentifications[1].Unmap(nData)) ? (INT)m_pDatabaseTMPacketIdentifications[1].GetSize() : 0; nID < nIDs; nID++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMPacketIdentification = m_pDatabaseTMPacketIdentifications[1].GetAt(nID))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMPacketIdentification->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTMPacketIdentification->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nID, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nID, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumTMPacketIdentificationCriteria(CONST CByteArray &nData)
{
	INT  nID;
	INT  nIDs;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacketIdentificationCriterion  *pDatabaseTMPacketIdentificationCriterion;

	for (nID = 0, nIDs = (m_pDatabaseTMPacketIdentificationCriteria[1].Unmap(nData)) ? (INT)m_pDatabaseTMPacketIdentificationCriteria[1].GetSize() : 0; nID < nIDs; nID++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMPacketIdentificationCriterion = m_pDatabaseTMPacketIdentificationCriteria[1].GetAt(nID))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMPacketIdentificationCriterion->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nID, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nID, nColumn, szItem);
		}
	}
}

VOID CDatabaseTablesImportDialog::EnumOBProcessorMemoryImages(CONST CByteArray &nData)
{
	INT  nImage;
	INT  nImages;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;

	for (nImage = 0, nImages = (m_pDatabaseOBProcessorMemoryImages[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseOBProcessorMemoryImages[1].GetSize() : 0; nImage < nImages; nImage++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseOBProcessorMemoryImage = m_pDatabaseOBProcessorMemoryImages[1].GetAt(nImage))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseOBProcessorMemoryImage->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = EMPTYSTRING;
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nImage, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nImage, nColumn, szItem);
		}
	}
}

BOOL CDatabaseTablesImportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_DATABASE_TABLES_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && (((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE) && !GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE  &&  GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))))) ? TRUE : FALSE);
}

void CDatabaseTablesImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CDatabaseTablesDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseTablesImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseTablesImportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CDatabaseTablesDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseTablesImportDialog, CDatabaseTablesDialog)
	//{{AFX_MSG_MAP(CDatabaseTablesImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_TABLES_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_DATABASE_TABLES_IMPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_DATABASE_TABLES_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_DATABASE_TABLES_IMPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesImportDialog message handlers

BOOL CDatabaseTablesImportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CDatabaseTablesDialog::OnInitDialog();
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_DATABASE_TABLES_IMPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width() / 2; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	CheckDlgButton(IDC_DATABASE_TABLES_IMPORT_TYPE_DEFAULT, TRUE);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE)->EnableWindow();
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETHEADER  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETSTREAM  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

BOOL CDatabaseTablesImportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_DATABASE_TABLES_IMPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_DATABASE_TABLES_IMPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_DEFAULT)->EnableWindow();
				GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETHEADER  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETSTREAM  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH) ? TRUE : FALSE);
			}
			else
			{
				CheckDlgButton(IDC_DATABASE_TABLES_IMPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
			}
			GetDlgItem(IDOK)->EnableWindow(Check());
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			OnOK();
			return TRUE;
		}
	}
	return CDatabaseTablesDialog::OnNotify(wParam, lParam, pResult);
}

void CDatabaseTablesImportDialog::OnBrowse()
{
	CDatabaseTablesFileBrowseDialog  cFileBrowseDialog(this, IDC_DATABASE_TABLES_IMPORT_FILENAME, STRING(IDS_DATABASETABLESFILEBROWSEDIALOG_FILEEXTENSION), STRING(IDS_DATABASETABLESFILEBROWSEDIALOG_FILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_DATABASE_TABLES_IMPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
		EnumDatabaseTables();
	}
	SendDlgItemMessage(IDC_DATABASE_TABLES_IMPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesImportDialog::OnDefault()
{
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesImportDialog::OnCustom()
{
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPARAMETERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMOOLTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTOOLTABLE) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPARAMETERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMOOLTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTOOLTABLE) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesImportDialog::OnEditchangeFileName()
{
	EnumDatabaseTables();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesImportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesImportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesImportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	CString  szName;
	CString  szDescription;
	CDatabaseTCPacket  *pDatabaseTCPacket;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;
	CDatabaseTCExeVerStage  *pDatabaseTCExeVerStage;
	CDatabaseTCExeVerGroup  *pDatabaseTCExeVerGroup;
	CDatabaseTMPacketGroup  *pDatabaseTMPacketGroup;
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;
	CDatabaseTCFunctionBlock  *pDatabaseTCFunctionBlock;
	CDatabaseTMParameterGroup  *pDatabaseTMParameterGroup;
	CDatabaseTCPacketParameter  *pDatabaseTCPacketParameter;
	CDatabaseTCParameterValueSet  *pDatabaseTCParameterValueSet;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
	for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_DATABASE_TABLES_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nItem))
		{
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION)
			{
				delete m_pDatabaseTMPacketIdentifications[1].GetAt(nItem);
				m_pDatabaseTMPacketIdentifications[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION)
			{
				delete m_pDatabaseTMPacketIdentificationCriteria[1].GetAt(nItem);
				m_pDatabaseTMPacketIdentificationCriteria[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETHEADER)
			{
				delete m_pDatabaseTMPacketHeaders[1].GetAt(nItem);
				m_pDatabaseTMPacketHeaders[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETSTREAM)
			{
				delete m_pDatabaseTMPacketStreams[1].GetAt(nItem);
				m_pDatabaseTMPacketStreams[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETGROUP)
			{
				delete m_pDatabaseTMPacketGroups[1].GetAt(nItem);
				m_pDatabaseTMPacketGroups[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET)
			{
				delete m_pDatabaseTCPackets[1].GetAt(nItem);
				m_pDatabaseTCPackets[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER)
			{
				delete m_pDatabaseTCPacketParameters[1].GetAt(nItem);
				m_pDatabaseTCPacketParameters[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE)
			{
				delete m_pDatabaseTCExeVerStages[1].GetAt(nItem);
				m_pDatabaseTCExeVerStages[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP)
			{
				delete m_pDatabaseTCExeVerGroups[1].GetAt(nItem);
				m_pDatabaseTCExeVerGroups[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK)
			{
				delete m_pDatabaseTCFunctionBlocks[1].GetAt(nItem);
				m_pDatabaseTCFunctionBlocks[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH)
			{
				delete m_pDatabaseTCFunctionRoutingPaths[1].GetAt(nItem);
				m_pDatabaseTCFunctionRoutingPaths[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET)
			{
				delete m_pDatabaseTCParameterSets[1].GetAt(nItem);
				m_pDatabaseTCParameterSets[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET)
			{
				delete m_pDatabaseTCParameterValueSets[1].GetAt(nItem);
				m_pDatabaseTCParameterValueSets[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE)
			{
				delete m_pDatabaseOBProcessorMemoryImages[1].GetAt(nItem);
				m_pDatabaseOBProcessorMemoryImages[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPARAMETERGROUP)
			{
				delete m_pDatabaseTMParameterGroups[1].GetAt(nItem);
				m_pDatabaseTMParameterGroups[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE)
			{
				delete m_pDatabaseTMNumCalTables[1].GetAt(nItem);
				m_pDatabaseTMNumCalTables[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE)
			{
				delete m_pDatabaseTMTxtCalTables[1].GetAt(nItem);
				m_pDatabaseTMTxtCalTables[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE)
			{
				delete m_pDatabaseTCNumCalTables[1].GetAt(nItem);
				m_pDatabaseTCNumCalTables[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE)
			{
				delete m_pDatabaseTCTxtCalTables[1].GetAt(nItem);
				m_pDatabaseTCTxtCalTables[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMOOLTABLE)
			{
				delete m_pDatabaseTCNumOolTables[1].GetAt(nItem);
				m_pDatabaseTCNumOolTables[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTOOLTABLE)
			{
				delete m_pDatabaseTCTxtOolTables[1].GetAt(nItem);
				m_pDatabaseTCTxtOolTables[1].SetAt(nItem, NULL);
			}
		}
	}
	switch (DATABASESUBCOMPONENTFROMCODE(m_nComponent))
	{
	case DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMPacketIdentifications[1].GetAt(nItem))
		{
			m_pDatabaseTMPacketIdentifications[1].RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMPacketIdentificationCriteria[1].GetAt(nItem))
		{
			m_pDatabaseTMPacketIdentificationCriteria[1].RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPACKETHEADER:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMPacketHeaders[1].GetAt(nItem))
		{
			m_pDatabaseTMPacketHeaders[1].RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPACKETSTREAM:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMPacketStreams[1].GetAt(nItem))
		{
			m_pDatabaseTMPacketStreams[1].RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPACKETGROUP:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTMPacketGroup = m_pDatabaseTMPacketGroups[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTMPacketGroup->SetName(szName);
				pDatabaseTMPacketGroup->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTMPacketGroups[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTCPacket = m_pDatabaseTCPackets[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTCPacket->SetTag(szName);
				pDatabaseTCPacket->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTCPackets[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTCPacketParameter = m_pDatabaseTCPacketParameters[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTCPacketParameter->SetTag(szName);
				pDatabaseTCPacketParameter->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTCPacketParameters[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if ((pDatabaseTCExeVerStage = m_pDatabaseTCExeVerStages[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)) pDatabaseTCExeVerStage->SetID(szName);
			continue;
		}
		m_pDatabaseTCExeVerStages[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if ((pDatabaseTCExeVerGroup = m_pDatabaseTCExeVerGroups[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTCExeVerGroup->SetID(szName);
				pDatabaseTCExeVerGroup->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTCExeVerGroups[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if ((pDatabaseTCFunctionBlock = m_pDatabaseTCFunctionBlocks[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)) pDatabaseTCFunctionBlock->SetName(szName);
			continue;
		}
		m_pDatabaseTCFunctionBlocks[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseTCFunctionRoutingPaths[1].GetAt(nItem))
		{
			m_pDatabaseTCFunctionRoutingPaths[1].RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCPARAMETERSET:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if ((pDatabaseTCParameterSet = m_pDatabaseTCParameterSets[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTCParameterSet->SetName(szName);
				pDatabaseTCParameterSet->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTCParameterSets[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if ((pDatabaseTCParameterValueSet = m_pDatabaseTCParameterValueSets[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTCParameterValueSet->SetName(szName);
				pDatabaseTCParameterValueSet->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTCParameterValueSets[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if ((pDatabaseOBProcessorMemoryImage = m_pDatabaseOBProcessorMemoryImages[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)) pDatabaseOBProcessorMemoryImage->SetName(szName);
			continue;
		}
		m_pDatabaseOBProcessorMemoryImages[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPARAMETERGROUP:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTMParameterGroup = m_pDatabaseTMParameterGroups[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTMParameterGroup->SetName(szName);
				pDatabaseTMParameterGroup->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTMParameterGroups[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TMNUMCALTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTMNumCalTable = m_pDatabaseTMNumCalTables[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTMNumCalTable->SetName(szName);
				pDatabaseTMNumCalTable->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTMNumCalTables[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TMTXTCALTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTMTxtCalTable = m_pDatabaseTMTxtCalTables[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTMTxtCalTable->SetName(szName);
				pDatabaseTMTxtCalTable->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTMTxtCalTables[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCNUMCALTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTCNumCalTable = m_pDatabaseTCNumCalTables[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTCNumCalTable->SetName(szName);
				pDatabaseTCNumCalTable->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTCNumCalTables[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCTXTCALTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTCTxtCalTable = m_pDatabaseTCTxtCalTables[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTCTxtCalTable->SetName(szName);
				pDatabaseTCTxtCalTable->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTCTxtCalTables[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCNUMOOLTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTCNumOolTable = m_pDatabaseTCNumOolTables[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTCNumOolTable->SetName(szName);
				pDatabaseTCNumOolTable->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTCNumOolTables[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TCTXTOOLTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTCTxtOolTable = m_pDatabaseTCTxtOolTables[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTCTxtOolTable->SetName(szName);
				pDatabaseTCTxtOolTable->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTCTxtOolTables[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	}
	EndDialog(IDOK);
}

void CDatabaseTablesImportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabaseTablesImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASETABLESIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseTablesImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASETABLESIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesExportDialog dialog

IMPLEMENT_DYNCREATE(CDatabaseTablesExportDialog, CDatabaseTablesDialog)

CDatabaseTablesExportDialog::CDatabaseTablesExportDialog(CWnd *pParentWnd, CDatabaseEngine *pDatabaseEngine) : CDatabaseTablesDialog(pDatabaseEngine)
{
	LPVOID  pDialogTemplate;

	for (m_pParentWnd = pParentWnd; (pDialogTemplate = LoadLocaleDialogTemplate(MAKEINTRESOURCE(CDatabaseTablesExportDialog::IDD))); )
	{
		InitModalIndirect(pDialogTemplate);
		break;
	}
}

INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCPackets &pDatabaseTCPackets)
{
	m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET;
	m_pDatabaseTCPackets.Copy(&pDatabaseTCPackets);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTMNumCalTables &pDatabaseTMNumCalTables)
{
	m_nComponent = DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMCALTABLE;
	m_pDatabaseTMNumCalTables.Copy(&pDatabaseTMNumCalTables);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTMTxtCalTables &pDatabaseTMTxtCalTables)
{
	m_nComponent = DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTCALTABLE;
	m_pDatabaseTMTxtCalTables.Copy(&pDatabaseTMTxtCalTables);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCNumCalTables &pDatabaseTCNumCalTables)
{
	m_nComponent = DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMCALTABLE;
	m_pDatabaseTCNumCalTables.Copy(&pDatabaseTCNumCalTables);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCTxtCalTables &pDatabaseTCTxtCalTables)
{
	m_nComponent = DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTCALTABLE;
	m_pDatabaseTCTxtCalTables.Copy(&pDatabaseTCTxtCalTables);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCNumOolTables &pDatabaseTCNumOolTables)
{
	m_nComponent = DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCNUMOOLTABLE;
	m_pDatabaseTCNumOolTables.Copy(&pDatabaseTCNumOolTables);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCTxtOolTables &pDatabaseTCTxtOolTables)
{
	m_nComponent = DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE;
	m_pDatabaseTCTxtOolTables.Copy(&pDatabaseTCTxtOolTables);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCExeVerStages &pDatabaseTCExeVerStages)
{
	m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE;
	m_pDatabaseTCExeVerStages.Copy(&pDatabaseTCExeVerStages);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCExeVerGroups &pDatabaseTCExeVerGroups)
{
	m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP;
	m_pDatabaseTCExeVerGroups.Copy(&pDatabaseTCExeVerGroups);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTMPacketGroups &pDatabaseTMPacketGroups)
{
	m_nComponent = DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETGROUP;
	m_pDatabaseTMPacketGroups.Copy(&pDatabaseTMPacketGroups);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTMPacketHeaders &pDatabaseTMPacketHeaders)
{
	m_nComponent = DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETHEADER;
	m_pDatabaseTMPacketHeaders.Copy(&pDatabaseTMPacketHeaders);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTMPacketStreams &pDatabaseTMPacketStreams)
{
	m_nComponent = DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETSTREAM;
	m_pDatabaseTMPacketStreams.Copy(&pDatabaseTMPacketStreams);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCParameterSets &pDatabaseTCParameterSets)
{
	m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERSET;
	m_pDatabaseTCParameterSets.Copy(&pDatabaseTCParameterSets);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCFunctionBlocks &pDatabaseTCFunctionBlocks)
{
	m_nComponent = DATABASE_COMPONENT_TCSEQUENCE | DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK;
	m_pDatabaseTCFunctionBlocks.Copy(&pDatabaseTCFunctionBlocks);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTMParameterGroups &pDatabaseTMParameterGroups)
{
	m_nComponent = DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMPARAMETERGROUP;
	m_pDatabaseTMParameterGroups.Copy(&pDatabaseTMParameterGroups);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCPacketParameters &pDatabaseTCPacketParameters)
{
	m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER;
	m_pDatabaseTCPacketParameters.Copy(&pDatabaseTCPacketParameters);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCParameterValueSets &pDatabaseTCParameterValueSets)
{
	m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET;
	m_pDatabaseTCParameterValueSets.Copy(&pDatabaseTCParameterValueSets);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCFunctionRoutingPaths &pDatabaseTCFunctionRoutingPaths)
{
	m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH;
	m_pDatabaseTCFunctionRoutingPaths.Copy(&pDatabaseTCFunctionRoutingPaths);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTMPacketIdentifications &pDatabaseTMPacketIdentifications)
{
	m_nComponent = DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION;
	m_pDatabaseTMPacketIdentifications.Copy(&pDatabaseTMPacketIdentifications);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTMPacketIdentificationCriteria &pDatabaseTMPacketIdentificationCriteria)
{
	m_nComponent = DATABASE_COMPONENT_TMPACKET | DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION;
	m_pDatabaseTMPacketIdentificationCriteria.Copy(&pDatabaseTMPacketIdentificationCriteria);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseOBProcessorMemoryImages &pDatabaseOBProcessorMemoryImages)
{
	m_nComponent = DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE;
	m_pDatabaseOBProcessorMemoryImages.Copy(&pDatabaseOBProcessorMemoryImages);
	return CDatabaseTablesDialog::DoModal();
}

BOOL CDatabaseTablesExportDialog::EnumDatabaseTables()
{
	return(((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION  &&  EnumTMPacketIdentifications()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION  &&  EnumTMPacketIdentificationCriteria()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETHEADER  &&  EnumTMPacketHeaders()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETSTREAM  &&  EnumTMPacketStreams()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETGROUP  &&  EnumTMPacketGroups()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET  &&  EnumTCPackets()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER  &&  EnumTCPacketParameters()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE  &&  EnumTCExeVerStages()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP  &&  EnumTCExeVerGroups()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK  &&  EnumTCFunctionBlocks()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH  &&  EnumTCFunctionRoutingPaths()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET  &&  EnumTCParameterSets()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET  &&  EnumTCParameterValueSets()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE  &&  EnumOBProcessorMemoryImages()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPARAMETERGROUP  &&  EnumTMParameterGroups()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE  &&  EnumTMNumCalTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE  &&  EnumTMTxtCalTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE  &&  EnumTCNumCalTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE  &&  EnumTCTxtCalTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMOOLTABLE  &&  EnumTCNumOolTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTOOLTABLE  &&  EnumTCTxtOolTables())) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCPackets()
{
	INT  nPacket;
	INT  nPackets;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCPacket  *pDatabaseTCPacket;

	for (nPacket = 0, nPackets = (INT)m_pDatabaseTCPackets.GetSize(); nPacket < nPackets; nPacket++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCPacket = m_pDatabaseTCPackets.GetAt(nPacket))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCPacket->GetTag();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCPacket->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nPacket, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nPacket, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTMNumCalTables()
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;

	for (nTable = 0, nTables = (INT)m_pDatabaseTMNumCalTables.GetSize(); nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMNumCalTable = m_pDatabaseTMNumCalTables.GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMNumCalTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTMNumCalTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTMTxtCalTables()
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	for (nTable = 0, nTables = (INT)m_pDatabaseTMTxtCalTables.GetSize(); nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMTxtCalTable = m_pDatabaseTMTxtCalTables.GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMTxtCalTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTMTxtCalTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCNumCalTables()
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;

	for (nTable = 0, nTables = (INT)m_pDatabaseTCNumCalTables.GetSize(); nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCNumCalTable = m_pDatabaseTCNumCalTables.GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCNumCalTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCNumCalTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCTxtCalTables()
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;

	for (nTable = 0, nTables = (INT)m_pDatabaseTCTxtCalTables.GetSize(); nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCTxtCalTable = m_pDatabaseTCTxtCalTables.GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCTxtCalTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCTxtCalTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCNumOolTables()
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;

	for (nTable = 0, nTables = (INT)m_pDatabaseTCNumOolTables.GetSize(); nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCNumOolTable = m_pDatabaseTCNumOolTables.GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCNumOolTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCNumOolTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCTxtOolTables()
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;

	for (nTable = 0, nTables = (INT)m_pDatabaseTCTxtOolTables.GetSize(); nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCTxtOolTable = m_pDatabaseTCTxtOolTables.GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCTxtOolTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCTxtOolTable->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nTable, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCExeVerStages()
{
	INT  nStage;
	INT  nStages;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCExeVerStage  *pDatabaseTCExeVerStage;

	for (nStage = 0, nStages = (INT)m_pDatabaseTCExeVerStages.GetSize(); nStage < nStages; nStage++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCExeVerStage = m_pDatabaseTCExeVerStages.GetAt(nStage))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCExeVerStage->GetID();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nStage, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nStage, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCExeVerGroups()
{
	INT  nGroup;
	INT  nGroups;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCExeVerGroup  *pDatabaseTCExeVerGroup;

	for (nGroup = 0, nGroups = (INT)m_pDatabaseTCExeVerGroups.GetSize(); nGroup < nGroups; nGroup++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCExeVerGroup = m_pDatabaseTCExeVerGroups.GetAt(nGroup))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCExeVerGroup->GetID();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCExeVerGroup->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nGroup, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nGroup, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTMPacketGroups()
{
	INT  nGroup;
	INT  nGroups;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacketGroup  *pDatabaseTMPacketGroup;

	for (nGroup = 0, nGroups = (INT)m_pDatabaseTMPacketGroups.GetSize(); nGroup < nGroups; nGroup++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMPacketGroup = m_pDatabaseTMPacketGroups.GetAt(nGroup))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMPacketGroup->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTMPacketGroup->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nGroup, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nGroup, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTMPacketHeaders()
{
	INT  nHeader;
	INT  nHeaders;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacketHeader  *pDatabaseTMPacketHeader;

	for (nHeader = 0, nHeaders = (INT)m_pDatabaseTMPacketHeaders.GetSize(); nHeader < nHeaders; nHeader++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMPacketHeader = m_pDatabaseTMPacketHeaders.GetAt(nHeader))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMPacketHeader->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nHeader, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nHeader, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTMPacketStreams()
{
	INT  nStream;
	INT  nStreams;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacketStream  *pDatabaseTMPacketStream;

	for (nStream = 0, nStreams = (INT)m_pDatabaseTMPacketStreams.GetSize(); nStream < nStreams; nStream++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMPacketStream = m_pDatabaseTMPacketStreams.GetAt(nStream))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMPacketStream->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nStream, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nStream, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCParameterSets()
{
	INT  nSet;
	INT  nSets;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;

	for (nSet = 0, nSets = (INT)m_pDatabaseTCParameterSets.GetSize(); nSet < nSets; nSet++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCParameterSet = m_pDatabaseTCParameterSets.GetAt(nSet))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCParameterSet->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCParameterSet->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nSet, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nSet, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCFunctionBlocks()
{
	INT  nBlock;
	INT  nBlocks;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCFunctionBlock  *pDatabaseTCFunctionBlock;

	for (nBlock = 0, nBlocks = (INT)m_pDatabaseTCFunctionBlocks.GetSize(); nBlock < nBlocks; nBlock++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCFunctionBlock = m_pDatabaseTCFunctionBlocks.GetAt(nBlock))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCFunctionBlock->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = EMPTYSTRING;
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nBlock, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nBlock, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTMParameterGroups()
{
	INT  nGroup;
	INT  nGroups;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMParameterGroup  *pDatabaseTMParameterGroup;

	for (nGroup = 0, nGroups = (INT)m_pDatabaseTMParameterGroups.GetSize(); nGroup < nGroups; nGroup++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMParameterGroup = m_pDatabaseTMParameterGroups.GetAt(nGroup))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMParameterGroup->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTMParameterGroup->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nGroup, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nGroup, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCPacketParameters()
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	CString  szItem;
	CDatabaseTCPacketParameter  *pDatabaseTCPacketParameter;

	for (nParameter = 0, nParameters = (INT)m_pDatabaseTCPacketParameters.GetSize(); nParameter < nParameters; nParameter++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCPacketParameter = m_pDatabaseTCPacketParameters.GetAt(nParameter))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCPacketParameter->GetTag();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCPacketParameter->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nParameter, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nParameter, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCParameterValueSets()
{
	INT  nSet;
	INT  nSets;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCParameterValueSet  *pDatabaseTCParameterValueSet;

	for (nSet = 0, nSets = (INT)m_pDatabaseTCParameterValueSets.GetSize(); nSet < nSets; nSet++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCParameterValueSet = m_pDatabaseTCParameterValueSets.GetAt(nSet))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCParameterValueSet->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCParameterValueSet->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nSet, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nSet, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTCFunctionRoutingPaths()
{
	INT  nPath;
	INT  nPaths;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CStringTools  cStringTools;
	CDatabaseTCFunctionRoutingPath  *pDatabaseTCFunctionRoutingPath;

	for (nPath = 0, nPaths = (INT)m_pDatabaseTCFunctionRoutingPaths.GetSize(); nPath < nPaths; nPath++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCFunctionRoutingPath = m_pDatabaseTCFunctionRoutingPaths.GetAt(nPath))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = cStringTools.ConvertIntToString(pDatabaseTCFunctionRoutingPath->GetAPID());
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCFunctionRoutingPath->GetPath();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nPath, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nPath, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTMPacketIdentifications()
{
	INT  nID;
	INT  nIDs;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacketIdentification  *pDatabaseTMPacketIdentification;

	for (nID = 0, nIDs = (INT)m_pDatabaseTMPacketIdentifications.GetSize(); nID < nIDs; nID++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMPacketIdentification = m_pDatabaseTMPacketIdentifications.GetAt(nID))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMPacketIdentification->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTMPacketIdentification->GetDescription();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nID, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nID, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumTMPacketIdentificationCriteria()
{
	INT  nID;
	INT  nIDs;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMPacketIdentificationCriterion  *pDatabaseTMPacketIdentificationCriterion;

	for (nID = 0, nIDs = (INT)m_pDatabaseTMPacketIdentificationCriteria.GetSize(); nID < nIDs; nID++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMPacketIdentificationCriterion = m_pDatabaseTMPacketIdentificationCriteria.GetAt(nID))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMPacketIdentificationCriterion->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nID, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nID, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::EnumOBProcessorMemoryImages()
{
	INT  nImage;
	INT  nImages;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;

	for (nImage = 0, nImages = (INT)m_pDatabaseOBProcessorMemoryImages.GetSize(); nImage < nImages; nImage++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseOBProcessorMemoryImage = m_pDatabaseOBProcessorMemoryImages.GetAt(nImage))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseOBProcessorMemoryImage->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = EMPTYSTRING;
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nImage, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nImage, nColumn, szItem);
		}
	}
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->EnableWindow((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CDatabaseTablesExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_DATABASE_TABLES_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && (((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE) && !GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE  &&  GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))))) ? TRUE : FALSE);
}

void CDatabaseTablesExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CDatabaseTablesDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatabaseTablesExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CDatabaseTablesExportDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pDatabaseTCPackets.RemoveAll();
	m_pDatabaseTMNumCalTables.RemoveAll();
	m_pDatabaseTMTxtCalTables.RemoveAll();
	m_pDatabaseTCNumCalTables.RemoveAll();
	m_pDatabaseTCTxtCalTables.RemoveAll();
	m_pDatabaseTCNumOolTables.RemoveAll();
	m_pDatabaseTCTxtOolTables.RemoveAll();
	m_pDatabaseTCExeVerStages.RemoveAll();
	m_pDatabaseTCExeVerGroups.RemoveAll();
	m_pDatabaseTMPacketGroups.RemoveAll();
	m_pDatabaseTMPacketHeaders.RemoveAll();
	m_pDatabaseTMPacketStreams.RemoveAll();
	m_pDatabaseTCParameterSets.RemoveAll();
	m_pDatabaseTCFunctionBlocks.RemoveAll();
	m_pDatabaseTMParameterGroups.RemoveAll();
	m_pDatabaseTCPacketParameters.RemoveAll();
	m_pDatabaseTCParameterValueSets.RemoveAll();
	m_pDatabaseTCFunctionRoutingPaths.RemoveAll();
	m_pDatabaseTMPacketIdentifications.RemoveAll();
	m_pDatabaseTMPacketIdentificationCriteria.RemoveAll();
	m_pDatabaseOBProcessorMemoryImages.RemoveAll();
	CDatabaseTablesDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseTablesExportDialog, CDatabaseTablesDialog)
	//{{AFX_MSG_MAP(CDatabaseTablesExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DATABASE_TABLES_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_DATABASE_TABLES_EXPORT_TYPE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM, OnCustom)
	ON_BN_CLICKED(IDC_DATABASE_TABLES_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_DATABASE_TABLES_EXPORT_FILENAME, OnEditchangeFileName)
	ON_EN_CHANGE(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesExportDialog message handlers

BOOL CDatabaseTablesExportDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns[2];
	CHourglassCursor  cCursor;

	CDatabaseTablesDialog::OnInitDialog();
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->GetClientRect(rColumns[0]);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->GetClientRect(rColumns[1]);
	m_szColumns.Add(STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns[1].Width() / 2; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (rColumns[0].Width() - nColumn*nWidth - GetSystemMetrics(SM_CXVSCROLL)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (EnumDatabaseTables())
	{
		CheckDlgButton(IDC_DATABASE_TABLES_EXPORT_TYPE_DEFAULT, TRUE);
		GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DETAILS)->EnableWindow();
		GetDlgItem(IDC_DATABASE_TABLES_EXPORT_FILENAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_DATABASE_TABLES_EXPORT_FILENAME)->EnableWindow();
		GetDlgItem(IDC_DATABASE_TABLES_EXPORT_BROWSE)->EnableWindow();
		GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE)->EnableWindow();
		GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETHEADER  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETSTREAM  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH) ? TRUE : FALSE);
		GetDlgItem(IDC_DATABASE_TABLES_EXPORT_FILENAME)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

BOOL CDatabaseTablesExportDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_DATABASE_TABLES_EXPORT_DIRECTORY)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			if (SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETSELECTEDCOUNT) == 1)
			{
				GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETHEADER  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TMPACKETSTREAM  &&  DATABASESUBCOMPONENTFROMCODE(m_nComponent) != DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH) ? TRUE : FALSE);
				CheckDlgButton(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM, FALSE);
			}
			else
			{
				CheckDlgButton(IDC_DATABASE_TABLES_EXPORT_TYPE_DEFAULT, TRUE);
				CheckDlgButton(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM, FALSE);
				GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
				GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
				GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
			}
			GetDlgItem(IDOK)->EnableWindow(Check());
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			OnOK();
			return TRUE;
		}
	}
	return CDatabaseTablesDialog::OnNotify(wParam, lParam, pResult);
}

void CDatabaseTablesExportDialog::OnBrowse()
{
	CDatabaseTablesFileBrowseDialog  cFileBrowseDialog(this, IDC_DATABASE_TABLES_EXPORT_FILENAME, STRING(IDS_DATABASETABLESFILEBROWSEDIALOG_FILEEXTENSION), STRING(IDS_DATABASETABLESFILEBROWSEDIALOG_FILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK) GetDlgItem(IDC_DATABASE_TABLES_EXPORT_FILENAME)->SetWindowText(cFileBrowseDialog.GetPathName());
	SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_FILENAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesExportDialog::OnDefault()
{
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesExportDialog::OnCustom()
{
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->EnableWindow();
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPARAMETERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMOOLTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTOOLTABLE) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPARAMETERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMOOLTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTOOLTABLE) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesExportDialog::OnEditchangeName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesExportDialog::OnEditchangeDescription()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CDatabaseTablesExportDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	DWORD  dwBytes;
	CFileEx  cFile;
	CString  szName;
	CString  szFileName;
	CString  szDescription;
	CByteArray  cFileBuffer;
	CDatabaseTCPacket  *pDatabaseTCPacket;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;
	CDatabaseTCExeVerStage  *pDatabaseTCExeVerStage;
	CDatabaseTCExeVerGroup  *pDatabaseTCExeVerGroup;
	CDatabaseTMPacketGroup  *pDatabaseTMPacketGroup;
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;
	CDatabaseTCFunctionBlock  *pDatabaseTCFunctionBlock;
	CDatabaseTMParameterGroup  *pDatabaseTMParameterGroup;
	CDatabaseTCPacketParameter  *pDatabaseTCPacketParameter;
	CDatabaseTCParameterValueSet  *pDatabaseTCParameterValueSet;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_FILENAME)->GetWindowText(szFileName);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
	for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nItem))
		{
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION)
			{
				delete m_pDatabaseTMPacketIdentifications.GetAt(nItem);
				m_pDatabaseTMPacketIdentifications.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION)
			{
				delete m_pDatabaseTMPacketIdentificationCriteria.GetAt(nItem);
				m_pDatabaseTMPacketIdentificationCriteria.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETHEADER)
			{
				delete m_pDatabaseTMPacketHeaders.GetAt(nItem);
				m_pDatabaseTMPacketHeaders.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETSTREAM)
			{
				delete m_pDatabaseTMPacketStreams.GetAt(nItem);
				m_pDatabaseTMPacketStreams.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETGROUP)
			{
				delete m_pDatabaseTMPacketGroups.GetAt(nItem);
				m_pDatabaseTMPacketGroups.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET)
			{
				delete m_pDatabaseTCPackets.GetAt(nItem);
				m_pDatabaseTCPackets.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER)
			{
				delete m_pDatabaseTCPacketParameters.GetAt(nItem);
				m_pDatabaseTCPacketParameters.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE)
			{
				delete m_pDatabaseTCExeVerStages.GetAt(nItem);
				m_pDatabaseTCExeVerStages.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP)
			{
				delete m_pDatabaseTCExeVerGroups.GetAt(nItem);
				m_pDatabaseTCExeVerGroups.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK)
			{
				delete m_pDatabaseTCFunctionBlocks.GetAt(nItem);
				m_pDatabaseTCFunctionBlocks.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH)
			{
				delete m_pDatabaseTCFunctionRoutingPaths.GetAt(nItem);
				m_pDatabaseTCFunctionRoutingPaths.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET)
			{
				delete m_pDatabaseTCParameterSets.GetAt(nItem);
				m_pDatabaseTCParameterSets.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET)
			{
				delete m_pDatabaseTCParameterValueSets.GetAt(nItem);
				m_pDatabaseTCParameterValueSets.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE)
			{
				delete m_pDatabaseOBProcessorMemoryImages.GetAt(nItem);
				m_pDatabaseOBProcessorMemoryImages.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPARAMETERGROUP)
			{
				delete m_pDatabaseTMParameterGroups.GetAt(nItem);
				m_pDatabaseTMParameterGroups.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE)
			{
				delete m_pDatabaseTMNumCalTables.GetAt(nItem);
				m_pDatabaseTMNumCalTables.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE)
			{
				delete m_pDatabaseTMTxtCalTables.GetAt(nItem);
				m_pDatabaseTMTxtCalTables.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE)
			{
				delete m_pDatabaseTCNumCalTables.GetAt(nItem);
				m_pDatabaseTCNumCalTables.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE)
			{
				delete m_pDatabaseTCTxtCalTables.GetAt(nItem);
				m_pDatabaseTCTxtCalTables.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMOOLTABLE)
			{
				delete m_pDatabaseTCNumOolTables.GetAt(nItem);
				m_pDatabaseTCNumOolTables.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTOOLTABLE)
			{
				delete m_pDatabaseTCTxtOolTables.GetAt(nItem);
				m_pDatabaseTCTxtOolTables.SetAt(nItem, NULL);
			}
		}
	}
	switch (DATABASESUBCOMPONENTFROMCODE(m_nComponent))
	{
	case DATABASE_SUBCOMPONENT_TMPACKETIDENTIFICATION:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseTMPacketIdentifications.GetAt(nItem))
		{
			m_pDatabaseTMPacketIdentifications.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if (m_pDatabaseTMPacketIdentifications.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPACKETIDENTCRITERION:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseTMPacketIdentificationCriteria.GetAt(nItem))
		{
			m_pDatabaseTMPacketIdentificationCriteria.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if (m_pDatabaseTMPacketIdentificationCriteria.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPACKETHEADER:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMPacketHeaders.GetAt(nItem))
		{
			m_pDatabaseTMPacketHeaders.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if (m_pDatabaseTMPacketHeaders.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPACKETSTREAM:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMPacketStreams.GetAt(nItem))
		{
			m_pDatabaseTMPacketStreams.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if (m_pDatabaseTMPacketStreams.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPACKETGROUP:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMPacketGroups.GetAt(nItem))
		{
			m_pDatabaseTMPacketGroups.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTMPacketGroup = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTMPacketGroups.GetAt(nItem - 1) : (CDatabaseTMPacketGroup *)NULL))
	{
		pDatabaseTMPacketGroup->SetName(szName);
		pDatabaseTMPacketGroup->SetDescription(szDescription);
	}
	if (m_pDatabaseTMPacketGroups.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTCPackets.GetAt(nItem))
		{
			m_pDatabaseTCPackets.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTCPacket = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCPackets.GetAt(nItem - 1) : (CDatabaseTCPacket *)NULL))
	{
		pDatabaseTCPacket->SetTag(szName);
		pDatabaseTCPacket->SetDescription(szDescription);
	}
	if (m_pDatabaseTCPackets.Map(cFileBuffer, FALSE))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONPACKETPARAMETER:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTCPacketParameters.GetAt(nItem))
		{
			m_pDatabaseTCPacketParameters.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTCPacketParameter = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCPacketParameters.GetAt(nItem - 1) : (CDatabaseTCPacketParameter *)NULL))
	{
		pDatabaseTCPacketParameter->SetTag(szName);
		pDatabaseTCPacketParameter->SetDescription(szDescription);
	}
	if (m_pDatabaseTCPacketParameters.Map(cFileBuffer, FALSE))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERSTAGE:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseTCExeVerStages.GetAt(nItem))
		{
			m_pDatabaseTCExeVerStages.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	for (; (pDatabaseTCExeVerStage = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCExeVerStages.GetAt(nItem - 1) : (CDatabaseTCExeVerStage *)NULL); )
	{
		pDatabaseTCExeVerStage->SetID(szName);
		break;
	}
	if (m_pDatabaseTCExeVerStages.Map(cFileBuffer, FALSE))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseTCExeVerGroups.GetAt(nItem))
		{
			m_pDatabaseTCExeVerGroups.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTCExeVerGroup = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCExeVerGroups.GetAt(nItem - 1) : (CDatabaseTCExeVerGroup *)NULL))
	{
		pDatabaseTCExeVerGroup->SetID(szName);
		pDatabaseTCExeVerGroup->SetDescription(szDescription);
	}
	if (m_pDatabaseTCExeVerGroups.Map(cFileBuffer, FALSE))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseTCFunctionBlocks.GetAt(nItem))
		{
			m_pDatabaseTCFunctionBlocks.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	for (; (pDatabaseTCFunctionBlock = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCFunctionBlocks.GetAt(nItem - 1) : (CDatabaseTCFunctionBlock *)NULL); )
	{
		pDatabaseTCFunctionBlock->SetName(szName);
		break;
	}
	if (m_pDatabaseTCFunctionBlocks.Map(cFileBuffer, FALSE))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCFUNCTIONROUTINGPATH:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseTCFunctionRoutingPaths.GetAt(nItem))
		{
			m_pDatabaseTCFunctionRoutingPaths.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if (m_pDatabaseTCFunctionRoutingPaths.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCPARAMETERSET:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseTCParameterSets.GetAt(nItem))
		{
			m_pDatabaseTCParameterSets.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTCParameterSet = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCParameterSets.GetAt(nItem - 1) : (CDatabaseTCParameterSet *)NULL))
	{
		pDatabaseTCParameterSet->SetName(szName);
		pDatabaseTCParameterSet->SetDescription(szDescription);
	}
	if (m_pDatabaseTCParameterSets.Map(cFileBuffer, FALSE))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCPARAMETERVALUESET:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseTCParameterValueSets.GetAt(nItem))
		{
			m_pDatabaseTCParameterValueSets.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTCParameterValueSet = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCParameterValueSets.GetAt(nItem - 1) : (CDatabaseTCParameterValueSet *)NULL))
	{
		pDatabaseTCParameterValueSet->SetName(szName);
		pDatabaseTCParameterValueSet->SetDescription(szDescription);
	}
	if (m_pDatabaseTCParameterValueSets.Map(cFileBuffer, FALSE))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseOBProcessorMemoryImages.GetAt(nItem))
		{
			m_pDatabaseOBProcessorMemoryImages.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	for (; (pDatabaseOBProcessorMemoryImage = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseOBProcessorMemoryImages.GetAt(nItem - 1) : (CDatabaseOBProcessorMemoryImage *)NULL); )
	{
		pDatabaseOBProcessorMemoryImage->SetName(szName);
		break;
	}
	if (m_pDatabaseOBProcessorMemoryImages.Map(cFileBuffer, FALSE))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPARAMETERGROUP:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMParameterGroups.GetAt(nItem))
		{
			m_pDatabaseTMParameterGroups.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTMParameterGroup = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTMParameterGroups.GetAt(nItem - 1) : (CDatabaseTMParameterGroup *)NULL))
	{
		pDatabaseTMParameterGroup->SetName(szName);
		pDatabaseTMParameterGroup->SetDescription(szDescription);
	}
	if (m_pDatabaseTMParameterGroups.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TMNUMCALTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMNumCalTables.GetAt(nItem))
		{
			m_pDatabaseTMNumCalTables.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTMNumCalTable = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTMNumCalTables.GetAt(nItem - 1) : (CDatabaseTMNumCalTable *)NULL))
	{
		pDatabaseTMNumCalTable->SetName(szName);
		pDatabaseTMNumCalTable->SetDescription(szDescription);
	}
	if (m_pDatabaseTMNumCalTables.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TMTXTCALTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMTxtCalTables.GetAt(nItem))
		{
			m_pDatabaseTMTxtCalTables.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTMTxtCalTable = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTMTxtCalTables.GetAt(nItem - 1) : (CDatabaseTMTxtCalTable *)NULL))
	{
		pDatabaseTMTxtCalTable->SetName(szName);
		pDatabaseTMTxtCalTable->SetDescription(szDescription);
	}
	if (m_pDatabaseTMTxtCalTables.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCNUMCALTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTCNumCalTables.GetAt(nItem))
		{
			m_pDatabaseTCNumCalTables.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTCNumCalTable = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCNumCalTables.GetAt(nItem - 1) : (CDatabaseTCNumCalTable *)NULL))
	{
		pDatabaseTCNumCalTable->SetName(szName);
		pDatabaseTCNumCalTable->SetDescription(szDescription);
	}
	if (m_pDatabaseTCNumCalTables.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCTXTCALTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTCTxtCalTables.GetAt(nItem))
		{
			m_pDatabaseTCTxtCalTables.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTCTxtCalTable = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCTxtCalTables.GetAt(nItem - 1) : (CDatabaseTCTxtCalTable *)NULL))
	{
		pDatabaseTCTxtCalTable->SetName(szName);
		pDatabaseTCTxtCalTable->SetDescription(szDescription);
	}
	if (m_pDatabaseTCTxtCalTables.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCNUMOOLTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTCNumOolTables.GetAt(nItem))
		{
			m_pDatabaseTCNumOolTables.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTCNumOolTable = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCNumOolTables.GetAt(nItem - 1) : (CDatabaseTCNumOolTable *)NULL))
	{
		pDatabaseTCNumOolTable->SetName(szName);
		pDatabaseTCNumOolTable->SetDescription(szDescription);
	}
	if (m_pDatabaseTCNumOolTables.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	case DATABASE_SUBCOMPONENT_TCTXTOOLTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTCTxtOolTables.GetAt(nItem))
		{
			m_pDatabaseTCTxtOolTables.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTCTxtOolTable = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCTxtOolTables.GetAt(nItem - 1) : (CDatabaseTCTxtOolTable *)NULL))
	{
		pDatabaseTCTxtOolTable->SetName(szName);
		pDatabaseTCTxtOolTable->SetDescription(szDescription);
	}
	if (m_pDatabaseTCTxtOolTables.Map(cFileBuffer))
	{
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
	nItems = -1;
	break;
	}
	}
	EndDialog((nItems >= 0) ? IDOK : IDABORT);
}

void CDatabaseTablesExportDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	EndDialog(IDCANCEL);
}

BOOL CDatabaseTablesExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASETABLESEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CDatabaseTablesExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ShowMessage((!ShowHelp(STRING(IDS_ONLINEHELP_DATABASETABLESEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesFileBrowseDialog

IMPLEMENT_DYNCREATE(CDatabaseTablesFileBrowseDialog, CFileDialog)

CDatabaseTablesFileBrowseDialog::CDatabaseTablesFileBrowseDialog(CWnd *pParentWnd, LPCTSTR pszFileName, LPCTSTR pszDefaultExtension, LPCTSTR pszFilter, DWORD dwFlags) : CFileDialog(TRUE, pszDefaultExtension, pszFileName, dwFlags, pszFilter, pParentWnd)
{
	m_ofn.lpstrTitle = STRING(IDS_DATABASETABLESFILEBROWSEDIALOG_TITLE);
	GetCurrentDirectory(sizeof(m_szDirectory) / sizeof(TCHAR), m_szDirectory);
}
CDatabaseTablesFileBrowseDialog::CDatabaseTablesFileBrowseDialog(CWnd *pParentWnd, UINT nCtrlID, LPCTSTR pszDefaultExtension, LPCTSTR pszFilter, DWORD dwFlags) : CFileDialog(TRUE, pszDefaultExtension, (LPCTSTR)NULL, dwFlags, pszFilter, pParentWnd)
{
	CWnd  *pWnd;
	CString  szFileName;

	for (m_ofn.lpstrTitle = STRING(IDS_DATABASETABLESFILEBROWSEDIALOG_TITLE), GetCurrentDirectory(sizeof(m_szDirectory) / sizeof(TCHAR), m_szDirectory); (pWnd = (IsWindow(pParentWnd->GetSafeHwnd())) ? pParentWnd->GetDlgItem(nCtrlID) : (CWnd *)NULL); )
	{
		for (pWnd->GetWindowText(szFileName); !szFileName.IsEmpty(); )
		{
			_tcscpy_s(m_szFileName, sizeof(m_szFileName) / sizeof(TCHAR), szFileName);
			break;
		}
		break;
	}
}

void CDatabaseTablesFileBrowseDialog::PostNcDestroy()
{
	SetCurrentDirectory(m_szDirectory);
	CFileDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CDatabaseTablesFileBrowseDialog, CFileDialog)
	//{{AFX_MSG_MAP(CDatabaseTablesFileBrowseDialog)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesFileBrowseDialog message handlers
