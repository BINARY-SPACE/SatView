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
#define ALTELENVIRONMENT

#include "ALTEL.h"

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

HGLOBAL CDatabaseTablesDialog::LoadLocaleDialogTemplate(UINT nDialogID) CONST
{
	return LoadLocaleDialogTemplate(MAKEINTRESOURCE(nDialogID));
}
HGLOBAL CDatabaseTablesDialog::LoadLocaleDialogTemplate(LPCTSTR pszDialogName) CONST
{
	HMODULE  hModule;
	HRSRC  hDialogTemplate;

	return(((hDialogTemplate = FindResourceEx((hModule = CALTELLibraryApp::GetLibraryApp()->m_hInstance), RT_DIALOG, pszDialogName, GetLanguageID())) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL))) || (hDialogTemplate = FindResourceEx(hModule, RT_DIALOG, pszDialogName, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)))) ? LoadResource(hModule, hDialogTemplate) : (LPVOID)NULL);
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
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTMNumOolTables &pDatabaseTMNumOolTables)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE, m_pDatabaseTMNumOolTables[0].Copy(&pDatabaseTMNumOolTables), m_pDatabaseTMNumOolTables[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMNumOolTables.Copy(&m_pDatabaseTMNumOolTables[1]);
		break;
	}
	return nResult;
}
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTMTxtOolTables &pDatabaseTMTxtOolTables)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE, m_pDatabaseTMTxtOolTables[0].Copy(&pDatabaseTMTxtOolTables), m_pDatabaseTMTxtOolTables[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTMTxtOolTables.Copy(&m_pDatabaseTMTxtOolTables[1]);
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
INT_PTR CDatabaseTablesImportDialog::DoModal(CDatabaseTCPreExeGroups &pDatabaseTCPreExeGroups)
{
	INT_PTR  nResult;

	for (m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP, m_pDatabaseTCPreExeGroups[0].Copy(&pDatabaseTCPreExeGroups), m_pDatabaseTCPreExeGroups[1].RemoveAll(); (nResult = CDatabaseTablesDialog::DoModal()) == IDOK; )
	{
		pDatabaseTCPreExeGroups.Copy(&m_pDatabaseTCPreExeGroups[1]);
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
				case DATABASE_SUBCOMPONENT_TMPACKETHEADER:
				{ EnumTMPacketHeaders(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TMPACKETSTREAM:
				{ EnumTMPacketStreams(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET:
				{ EnumTCPackets(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP:
				{ EnumTCPreExeGroups(cFileBuffer);
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
				case DATABASE_SUBCOMPONENT_TCPARAMETERSET:
				{ EnumTCParameterSets(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE:
				{ EnumOBProcessorMemoryImages(cFileBuffer);
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
				case DATABASE_SUBCOMPONENT_TMNUMOOLTABLE:
				{ EnumTMNumOolTables(cFileBuffer);
				break;
				}
				case DATABASE_SUBCOMPONENT_TMTXTOOLTABLE:
				{ EnumTMTxtOolTables(cFileBuffer);
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

VOID CDatabaseTablesImportDialog::EnumTMNumOolTables(CONST CByteArray &nData)
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	for (nTable = 0, nTables = (m_pDatabaseTMNumOolTables[1].Unmap(nData)) ? (INT)m_pDatabaseTMNumOolTables[1].GetSize() : 0; nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMNumOolTable = m_pDatabaseTMNumOolTables[1].GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMNumOolTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
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

VOID CDatabaseTablesImportDialog::EnumTMTxtOolTables(CONST CByteArray &nData)
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	for (nTable = 0, nTables = (m_pDatabaseTMTxtOolTables[1].Unmap(nData)) ? (INT)m_pDatabaseTMTxtOolTables[1].GetSize() : 0; nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMTxtOolTable = m_pDatabaseTMTxtOolTables[1].GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMTxtOolTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
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
				szItem.Empty();
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
				szItem.Empty();
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

VOID CDatabaseTablesImportDialog::EnumTCPreExeGroups(CONST CByteArray &nData)
{
	INT  nGroup;
	INT  nGroups;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCPreExeGroup  *pDatabaseTCPreExeGroup;

	for (nGroup = 0, nGroups = (m_pDatabaseTCPreExeGroups[1].Unmap(nData, FALSE)) ? (INT)m_pDatabaseTCPreExeGroups[1].GetSize() : 0; nGroup < nGroups; nGroup++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCPreExeGroup = m_pDatabaseTCPreExeGroups[1].GetAt(nGroup))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCPreExeGroup->GetID();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESIMPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCPreExeGroup->GetDescription();
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
	return((GetDlgItem(IDC_DATABASE_TABLES_IMPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM) && GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && (((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETHEADER || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETSTREAM || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMOOLTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTOOLTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMOOLTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTOOLTABLE) && !GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength()) || ((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE) && GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))))) ? TRUE : FALSE);
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
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)->EnableWindow();
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
				GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)->EnableWindow();
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
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE) ? TRUE : FALSE);
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
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;
	CDatabaseTCPreExeGroup  *pDatabaseTCPreExeGroup;
	CDatabaseTCExeVerGroup  *pDatabaseTCExeVerGroup;
	CDatabaseTMPacketHeader  *pDatabaseTMPacketHeader;
	CDatabaseTMPacketStream  *pDatabaseTMPacketStream;
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;
	CDatabaseTCFunctionBlock  *pDatabaseTCFunctionBlock;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
	for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_DATABASE_TABLES_IMPORT_DIRECTORY, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_DATABASE_TABLES_IMPORT_DIRECTORY), nItem))
		{
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
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET)
			{
				delete m_pDatabaseTCPackets[1].GetAt(nItem);
				m_pDatabaseTCPackets[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP)
			{
				delete m_pDatabaseTCPreExeGroups[1].GetAt(nItem);
				m_pDatabaseTCPreExeGroups[1].SetAt(nItem, NULL);
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
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET)
			{
				delete m_pDatabaseTCParameterSets[1].GetAt(nItem);
				m_pDatabaseTCParameterSets[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE)
			{
				delete m_pDatabaseOBProcessorMemoryImages[1].GetAt(nItem);
				m_pDatabaseOBProcessorMemoryImages[1].SetAt(nItem, NULL);
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
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMOOLTABLE)
			{
				delete m_pDatabaseTMNumOolTables[1].GetAt(nItem);
				m_pDatabaseTMNumOolTables[1].SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTOOLTABLE)
			{
				delete m_pDatabaseTMTxtOolTables[1].GetAt(nItem);
				m_pDatabaseTMTxtOolTables[1].SetAt(nItem, NULL);
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
	case DATABASE_SUBCOMPONENT_TMPACKETHEADER:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTMPacketHeader = m_pDatabaseTMPacketHeaders[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)) pDatabaseTMPacketHeader->SetName(szName);
			continue;
		}
		m_pDatabaseTMPacketHeaders[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TMPACKETSTREAM:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTMPacketStream = m_pDatabaseTMPacketStreams[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)) pDatabaseTMPacketStream->SetName(szName);
			continue;
		}
		m_pDatabaseTMPacketStreams[1].RemoveAt(nItem);
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
	case DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if ((pDatabaseTCPreExeGroup = m_pDatabaseTCPreExeGroups[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM))
			{
				pDatabaseTCPreExeGroup->SetID(szName);
				pDatabaseTCPreExeGroup->SetDescription(szDescription);
			}
			continue;
		}
		m_pDatabaseTCPreExeGroups[1].RemoveAt(nItem);
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
	case DATABASE_SUBCOMPONENT_TMNUMOOLTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTMNumOolTable = m_pDatabaseTMNumOolTables[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)) pDatabaseTMNumOolTable->SetName(szName);
			continue;
		}
		m_pDatabaseTMNumOolTables[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	break;
	}
	case DATABASE_SUBCOMPONENT_TMTXTOOLTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if ((pDatabaseTMTxtOolTable = m_pDatabaseTMTxtOolTables[1].GetAt(nItem)))
		{
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)) pDatabaseTMTxtOolTable->SetName(szName);
			continue;
		}
		m_pDatabaseTMTxtOolTables[1].RemoveAt(nItem);
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
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)) pDatabaseTCNumOolTable->SetName(szName);
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
			if (IsDlgButtonChecked(IDC_DATABASE_TABLES_IMPORT_TYPE_CUSTOM)) pDatabaseTCTxtOolTable->SetName(szName);
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
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTMNumOolTables &pDatabaseTMNumOolTables)
{
	m_nComponent = DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMNUMOOLTABLE;
	m_pDatabaseTMNumOolTables.Copy(&pDatabaseTMNumOolTables);
	return CLocaleDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTMTxtOolTables &pDatabaseTMTxtOolTables)
{
	m_nComponent = DATABASE_COMPONENT_TMPARAMETER | DATABASE_SUBCOMPONENT_TMTXTOOLTABLE;
	m_pDatabaseTMTxtOolTables.Copy(&pDatabaseTMTxtOolTables);
	return CLocaleDialog::DoModal();
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
	return CLocaleDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCTxtOolTables &pDatabaseTCTxtOolTables)
{
	m_nComponent = DATABASE_COMPONENT_TCPARAMETER | DATABASE_SUBCOMPONENT_TCTXTOOLTABLE;
	m_pDatabaseTCTxtOolTables.Copy(&pDatabaseTCTxtOolTables);
	return CLocaleDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCPreExeGroups &pDatabaseTCPreExeGroups)
{
	m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP;
	m_pDatabaseTCPreExeGroups.Copy(&pDatabaseTCPreExeGroups);
	return CDatabaseTablesDialog::DoModal();
}
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseTCExeVerGroups &pDatabaseTCExeVerGroups)
{
	m_nComponent = DATABASE_COMPONENT_TCFUNCTION | DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP;
	m_pDatabaseTCExeVerGroups.Copy(&pDatabaseTCExeVerGroups);
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
INT_PTR CDatabaseTablesExportDialog::DoModal(CONST CDatabaseOBProcessorMemoryImages &pDatabaseOBProcessorMemoryImages)
{
	m_nComponent = DATABASE_COMPONENT_OBPROCESSOR | DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE;
	m_pDatabaseOBProcessorMemoryImages.Copy(&pDatabaseOBProcessorMemoryImages);
	return CDatabaseTablesDialog::DoModal();
}

BOOL CDatabaseTablesExportDialog::EnumDatabaseTables()
{
	return(((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETHEADER  &&  EnumTMPacketHeaders()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETSTREAM  &&  EnumTMPacketStreams()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET  &&  EnumTCPackets()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP  &&  EnumTCPreExeGroups()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP  &&  EnumTCExeVerGroups()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK  &&  EnumTCFunctionBlocks()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET  &&  EnumTCParameterSets()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE  &&  EnumOBProcessorMemoryImages()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE  &&  EnumTMNumCalTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE  &&  EnumTMTxtCalTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMOOLTABLE  &&  EnumTMNumOolTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTOOLTABLE  &&  EnumTMTxtOolTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE  &&  EnumTCNumCalTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE  &&  EnumTCTxtCalTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMOOLTABLE  &&  EnumTCNumOolTables()) || (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTOOLTABLE  &&  EnumTCTxtOolTables())) ? TRUE : FALSE);
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

BOOL CDatabaseTablesExportDialog::EnumTMNumOolTables()
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;

	for (nTable = 0, nTables = (INT)m_pDatabaseTMNumOolTables.GetSize(); nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMNumOolTable = m_pDatabaseTMNumOolTables.GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMNumOolTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
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

BOOL CDatabaseTablesExportDialog::EnumTMTxtOolTables()
{
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	for (nTable = 0, nTables = (INT)m_pDatabaseTMTxtOolTables.GetSize(); nTable < nTables; nTable++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTMTxtOolTable = m_pDatabaseTMTxtOolTables.GetAt(nTable))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTMTxtOolTable->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem.Empty();
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
				szItem.Empty();
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
				szItem.Empty();
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

BOOL CDatabaseTablesExportDialog::EnumTCPreExeGroups()
{
	INT  nGroup;
	INT  nGroups;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CDatabaseTCPreExeGroup  *pDatabaseTCPreExeGroup;

	for (nGroup = 0, nGroups = (INT)m_pDatabaseTCPreExeGroups.GetSize(); nGroup < nGroups; nGroup++)
	{
		for (nColumn = 0, nColumns = ((pDatabaseTCPreExeGroup = m_pDatabaseTCPreExeGroups.GetAt(nGroup))) ? (INT)m_szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_NAME); )
			{
				szItem = pDatabaseTCPreExeGroup->GetID();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_DATABASETABLESEXPORTDIALOG_DIRECTORYTITLEITEM_DESCRIPTION); )
			{
				szItem = pDatabaseTCPreExeGroup->GetDescription();
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
	return((GetDlgItem(IDC_DATABASE_TABLES_EXPORT_FILENAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY)->SendMessage(LVM_GETSELECTEDCOUNT) > 0 && (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_DEFAULT) || (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM) && GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->GetWindowTextLength() > 0 && (((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETHEADER || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMPACKETSTREAM || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONBLOCK || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMOOLTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTOOLTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMOOLTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTOOLTABLE) && !GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength()) || ((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE) && GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowTextLength() > 0))))) ? TRUE : FALSE);
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
	m_pDatabaseTMNumOolTables.RemoveAll();
	m_pDatabaseTMTxtOolTables.RemoveAll();
	m_pDatabaseTCNumCalTables.RemoveAll();
	m_pDatabaseTCTxtCalTables.RemoveAll();
	m_pDatabaseTCNumOolTables.RemoveAll();
	m_pDatabaseTCTxtOolTables.RemoveAll();
	m_pDatabaseTCPreExeGroups.RemoveAll();
	m_pDatabaseTCExeVerGroups.RemoveAll();
	m_pDatabaseTMPacketHeaders.RemoveAll();
	m_pDatabaseTMPacketStreams.RemoveAll();
	m_pDatabaseTCParameterSets.RemoveAll();
	m_pDatabaseTCFunctionBlocks.RemoveAll();
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
		GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)->EnableWindow();
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
				GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)->EnableWindow();
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
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE) ? TRUE : FALSE);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->EnableWindow((DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONEXEVERGROUP || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCNUMCALTABLE || DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCTXTCALTABLE) ? TRUE : FALSE);
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
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;
	CDatabaseTCNumCalTable  *pDatabaseTCNumCalTable;
	CDatabaseTCTxtCalTable  *pDatabaseTCTxtCalTable;
	CDatabaseTCNumOolTable  *pDatabaseTCNumOolTable;
	CDatabaseTCTxtOolTable  *pDatabaseTCTxtOolTable;
	CDatabaseTCPreExeGroup  *pDatabaseTCPreExeGroup;
	CDatabaseTCExeVerGroup  *pDatabaseTCExeVerGroup;
	CDatabaseTMPacketHeader  *pDatabaseTMPacketHeader;
	CDatabaseTMPacketStream  *pDatabaseTMPacketStream;
	CDatabaseTCParameterSet  *pDatabaseTCParameterSet;
	CDatabaseTCFunctionBlock  *pDatabaseTCFunctionBlock;
	CDatabaseOBProcessorMemoryImage  *pDatabaseOBProcessorMemoryImage;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_FILENAME)->GetWindowText(szFileName);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_NAME)->GetWindowText(szName);
	GetDlgItem(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM_DESCRIPTION)->GetWindowText(szDescription);
	for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_DATABASE_TABLES_EXPORT_DIRECTORY, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
	{
		if (!Listview_IsSelText(GetDlgItem(IDC_DATABASE_TABLES_EXPORT_DIRECTORY), nItem))
		{
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
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPACKET)
			{
				delete m_pDatabaseTCPackets.GetAt(nItem);
				m_pDatabaseTCPackets.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP)
			{
				delete m_pDatabaseTCPreExeGroups.GetAt(nItem);
				m_pDatabaseTCPreExeGroups.SetAt(nItem, NULL);
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
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TCPARAMETERSET)
			{
				delete m_pDatabaseTCParameterSets.GetAt(nItem);
				m_pDatabaseTCParameterSets.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_OBPROCESSORMEMORYIMAGE)
			{
				delete m_pDatabaseOBProcessorMemoryImages.GetAt(nItem);
				m_pDatabaseOBProcessorMemoryImages.SetAt(nItem, NULL);
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
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMNUMOOLTABLE)
			{
				delete m_pDatabaseTMNumOolTables.GetAt(nItem);
				m_pDatabaseTMNumOolTables.SetAt(nItem, NULL);
			}
			if (DATABASESUBCOMPONENTFROMCODE(m_nComponent) == DATABASE_SUBCOMPONENT_TMTXTOOLTABLE)
			{
				delete m_pDatabaseTMTxtOolTables.GetAt(nItem);
				m_pDatabaseTMTxtOolTables.SetAt(nItem, NULL);
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
	for (; (pDatabaseTMPacketHeader = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTMPacketHeaders.GetAt(nItem - 1) : (CDatabaseTMPacketHeader *)NULL); )
	{
		pDatabaseTMPacketHeader->SetName(szName);
		break;
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
	for (; (pDatabaseTMPacketStream = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTMPacketStreams.GetAt(nItem - 1) : (CDatabaseTMPacketStream *)NULL); )
	{
		pDatabaseTMPacketStream->SetName(szName);
		break;
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
	case DATABASE_SUBCOMPONENT_TCFUNCTIONPREEXEGROUP:
	{ for (nItem = 0; nItem < nItems; nItem = nItem + 1)
	{
		if (!m_pDatabaseTCPreExeGroups.GetAt(nItem))
		{
			m_pDatabaseTCPreExeGroups.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if ((pDatabaseTCPreExeGroup = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCPreExeGroups.GetAt(nItem - 1) : (CDatabaseTCPreExeGroup *)NULL))
	{
		pDatabaseTCPreExeGroup->SetID(szName);
		pDatabaseTCPreExeGroup->SetDescription(szDescription);
	}
	if (m_pDatabaseTCPreExeGroups.Map(cFileBuffer, FALSE))
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
	case DATABASE_SUBCOMPONENT_TMNUMOOLTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMNumOolTables.GetAt(nItem))
		{
			m_pDatabaseTMNumOolTables.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	for (; (pDatabaseTMNumOolTable = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTMNumOolTables.GetAt(nItem - 1) : (CDatabaseTMNumOolTable *)NULL); )
	{
		pDatabaseTMNumOolTable->SetName(szName);
		break;
	}
	if (m_pDatabaseTMNumOolTables.Map(cFileBuffer))
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
	case DATABASE_SUBCOMPONENT_TMTXTOOLTABLE:
	{ for (nItem = 0; nItem < nItems; nItem++)
	{
		if (!m_pDatabaseTMTxtOolTables.GetAt(nItem))
		{
			m_pDatabaseTMTxtOolTables.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	for (; (pDatabaseTMTxtOolTable = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTMTxtOolTables.GetAt(nItem - 1) : (CDatabaseTMTxtOolTable *)NULL); )
	{
		pDatabaseTMTxtOolTable->SetName(szName);
		break;
	}
	if (m_pDatabaseTMTxtOolTables.Map(cFileBuffer))
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
	for (; (pDatabaseTCNumOolTable = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCNumOolTables.GetAt(nItem - 1) : (CDatabaseTCNumOolTable *)NULL); )
	{
		pDatabaseTCNumOolTable->SetName(szName);
		break;
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
	for (; (pDatabaseTCTxtOolTable = (IsDlgButtonChecked(IDC_DATABASE_TABLES_EXPORT_TYPE_CUSTOM)) ? m_pDatabaseTCTxtOolTables.GetAt(nItem - 1) : (CDatabaseTCTxtOolTable *)NULL); )
	{
		pDatabaseTCTxtOolTable->SetName(szName);
		break;
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
