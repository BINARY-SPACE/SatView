// DBMS.CPP : Database management System Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the database management
// system related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2011/06/25 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDatabasesRecordset recordset

IMPLEMENT_DYNAMIC(CDatabasesRecordset, CRecordset)

CDatabasesRecordset::CDatabasesRecordset(CDatabase *pDatabase) : CRecordset(pDatabase)
{
	//{{AFX_FIELD_INIT(CDatabasesRecordset)
	m_szName = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT

}

CString CDatabasesRecordset::GetName() CONST
{
	return m_szName;
}

void CDatabasesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CDatabasesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NAME]"), m_szName);
	//}}AFX_FIELD_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesRecordset recordset

IMPLEMENT_DYNAMIC(CDatabaseTablesRecordset, CRecordset)

CDatabaseTablesRecordset::CDatabaseTablesRecordset(CDatabase *pDatabase) : CRecordset(pDatabase)
{
	//{{AFX_FIELD_INIT(CDatabaseTablesRecordset)
	m_szTable = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT

}

CString CDatabaseTablesRecordset::GetTable() CONST
{
	return m_szTable;
}

void CDatabaseTablesRecordset::DoFieldExchange(CFieldExchange *pFX)
{
	CRecordset::DoFieldExchange(pFX);
	//{{AFX_FIELD_MAP(CDatabaseTablesRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NAME]"), m_szTable);
	//}}AFX_FIELD_MAP
}


/////////////////////////////////////////////////////////////////////////////
// CDBMS

CDBMS::CDBMS() : CDatabase()
{
	return;
}

INT CDBMS::CreateDatabase(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, LPCTSTR pszDataFileName, LPCTSTR pszDataFilePath, UINT nDataFileSize, UINT nDataFileMaxSize, UINT nDataFileGrowth, LPCTSTR pszLogsFileName, LPCTSTR pszLogsFilePath, UINT nLogsFileSize, UINT nLogsFileMaxSize, UINT nLogsFileGrowth, BOOL bReadOnly, BOOL bTables)
{
	INT  nPos;
	INT  nTable;
	INT  nTables;
	INT  nColumn;
	INT  nColumns;
	CString  szQuery;
	CString  szColumn;
	CString  szDefault;
	CString  szCommand[4];
	CString  szFilePath[2];
	CString  szFileSize[2][3];
	CFileFind  cFileFind[2];
	CByteArray  bTableColumns;
	CStringArray  szTables[2];
	CStringArray  szTableColumns[3];
	CLogicalDrives  cDrives;
	CDatabaseEngine  cDatabase;

	if (Connect(pDatabaseProfileInfo->GetServer()))
	{
		CDatabasesRecordset  cDatabasesRecordset(this);
		try
		{
			szQuery.Format(STRING(IDS_ODBC_DATABASE_SEARCH), (LPCTSTR)pDatabaseProfileInfo->GetName());
			cDatabasesRecordset.Open(CRecordset::dynamic, szQuery, CRecordset::none);
		}
		catch (CException *pException)
		{
			pException->Delete();
			Close();
			return FALSE;
		}
		if (cDatabasesRecordset.IsBOF() || cDatabasesRecordset.IsEOF())
		{
			for (szFilePath[0] = pszDataFilePath; szFilePath[0].GetLength() > 0 && szFilePath[0].GetAt(szFilePath[0].GetLength() - 1) != cDrives.GetDriveDelimiter(); )
			{
				szFilePath[0] += cDrives.GetPathDelimiter();
				break;
			}
			for (; cFileFind[0].FindFile(pszDataFilePath) || CreateDirectory(pszDataFilePath, (LPSECURITY_ATTRIBUTES)NULL); )
			{
				CDatabaseEngine::SecureDirectoryOrFile(pszDataFilePath);
				break;
			}
			for (szFilePath[1] = pszLogsFilePath; szFilePath[1].GetLength() > 0 && szFilePath[1].GetAt(szFilePath[1].GetLength() - 1) != cDrives.GetDriveDelimiter(); )
			{
				szFilePath[1] += cDrives.GetPathDelimiter();
				break;
			}
			for (; cFileFind[1].FindFile(pszLogsFilePath) || CreateDirectory(pszLogsFilePath, (LPSECURITY_ATTRIBUTES)NULL); )
			{
				CDatabaseEngine::SecureDirectoryOrFile(pszLogsFilePath);
				break;
			}
			for (szFileSize[0][0].Format(STRING(IDS_ODBC_DATABASE_FILESIZE_FORMAT), nDataFileSize), szFileSize[0][1].Format(STRING(IDS_ODBC_DATABASE_FILESIZE_FORMAT), nDataFileMaxSize), szFileSize[0][2].Format(STRING(IDS_ODBC_DATABASE_FILESIZE_FORMAT), nDataFileGrowth); nDataFileMaxSize == (UINT)-1; )
			{
				szFileSize[0][1] = STRING(IDS_ODBC_DATABASE_OPTION_UNLIMITED);
				break;
			}
			for (szFileSize[1][0].Format(STRING(IDS_ODBC_DATABASE_FILESIZE_FORMAT), nLogsFileSize), szFileSize[1][1].Format(STRING(IDS_ODBC_DATABASE_FILESIZE_FORMAT), nLogsFileMaxSize), szFileSize[1][2].Format(STRING(IDS_ODBC_DATABASE_FILESIZE_FORMAT), nLogsFileGrowth); nLogsFileMaxSize == (UINT)-1; )
			{
				szFileSize[1][1] = STRING(IDS_ODBC_DATABASE_OPTION_UNLIMITED);
				break;
			}
			if (cDatabase.Open(pDatabaseProfileInfo, FALSE))
			{
				for (nTable = 0, nTables = (bTables) ? cDatabase.EnumDBMSTables(szTables[0], szTables[1]) : 0, szCommand[0].Format(STRING(IDS_ODBC_DATABASE_CREATE), (LPCTSTR)pDatabaseProfileInfo->GetName(), pszDataFileName, (LPCTSTR)(szFilePath[0] + pszDataFileName), (LPCTSTR)szFileSize[0][0], (LPCTSTR)szFileSize[0][1], (LPCTSTR)szFileSize[0][2], pszLogsFileName, (LPCTSTR)(szFilePath[1] + pszLogsFileName), (LPCTSTR)szFileSize[1][0], (LPCTSTR)szFileSize[1][1], (LPCTSTR)szFileSize[1][2], (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (bReadOnly) ? STRING(IDS_ODBC_DATABASE_OPTION_UNCHANGEABLE) : STRING(IDS_ODBC_DATABASE_OPTION_CHANGEABLE), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)pDatabaseProfileInfo->GetName()), szCommand[1].Empty(); nTable < nTables; nTable++)
				{
					for (nColumn = 0, nColumns = (cDatabase.GetDBMSTableCharacteristics(szTables[0].GetAt(nTable), szTableColumns[0], szTableColumns[1], szTableColumns[2], bTableColumns)) ? (INT)szTableColumns[0].GetSize() : -1, szCommand[2].Empty(); nColumn < nColumns; nColumn++)
					{
						for (nPos = 0; nPos < szTableColumns[1].GetAt(nColumn).GetLength(); nPos++)
						{
							if (!_istalpha(szTableColumns[1].GetAt(nColumn).GetAt(nPos))) break;
							continue;
						}
						for (szColumn.Format(STRING(IDS_ODBC_DATABASE_TABLECOLUMN_FORMAT), (LPCTSTR)szTableColumns[0].GetAt(nColumn), (LPCTSTR)szTableColumns[1].GetAt(nColumn).Left(nPos), (nPos < szTableColumns[1].GetAt(nColumn).GetLength()) ? (LPCTSTR)szTableColumns[1].GetAt(nColumn).Mid(nPos) : EMPTYSTRING, (!bTableColumns.GetAt(nColumn)) ? STRING(IDS_ODBC_DATABASE_TABLECOLUMN_FLAG_NOTNULL) : STRING(IDS_ODBC_DATABASE_TABLECOLUMN_FLAG_NULL)); !szTableColumns[2].GetAt(nColumn).IsEmpty(); )
						{
							szDefault.Format(STRING(IDS_ODBC_DATABASE_TABLECOLUMN_DEFAULT_VALUE), (LPCTSTR)szTableColumns[2].GetAt(nColumn));
							szColumn += SPACE + szDefault;
							break;
						}
						szCommand[2] += (nColumn > 0) ? (STRING(IDS_ODBC_DATABASE_TABLECOLUMN_SEPARATOR) + szColumn) : szColumn;
					}
					if (nColumn == nColumns)
					{
						szCommand[3].Format(STRING(IDS_ODBC_DATABASE_TABLE), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)szTables[0].GetAt(nTable), (LPCTSTR)szCommand[2]);
						szCommand[1] += (nTable > 0) ? (CString(CR) + CString(EOL) + szCommand[3]) : szCommand[3];
						continue;
					}
					break;
				}
				if (nTable == nTables)
				{
					try
					{
						ExecuteSQL(szCommand[0]);
					}
					catch (CException *pException)
					{
						pException->Delete();
						cDatabase.Close();
						Close();
						return FALSE;
					}
					if (bTables)
					{
						try
						{
							ExecuteSQL(szCommand[1]);
						}
						catch (CException *pException)
						{
							try
							{
								szCommand[2].Format(STRING(IDS_ODBC_DATABASE_DELETE), (LPCTSTR)pDatabaseProfileInfo->GetName());
								ExecuteSQL(szCommand[2]);
							}
							catch (CException *pFailure)
							{
								pFailure->Delete();
							}
							pException->Delete();
							cDatabase.Close();
							Close();
							return FALSE;
						}
					}
					cDatabase.Close();
					Close();
					return TRUE;
				}
				cDatabase.Close();
			}
			return FALSE;
		}
		Close();
		return -1;
	}
	return FALSE;
}

INT CDBMS::ImportDatabase(CONST CDatabaseProfileInfo *pSourceDatabaseProfileInfo, CONST CDatabaseProfileInfo *pDestinationDatabaseProfileInfo, LPCTSTR pszDataFileName, LPCTSTR pszDataFilePath, UINT nDataFileSize, UINT nDataFileMaxSize, UINT nDataFileGrowth, LPCTSTR pszLogsFileName, LPCTSTR pszLogsFilePath, UINT nLogsFileSize, UINT nLogsFileMaxSize, UINT nLogsFileGrowth, BOOL bReadOnly)
{
	INT  nResult;

	return(((nResult = CreateDatabase(pDestinationDatabaseProfileInfo, pszDataFileName, pszDataFilePath, nDataFileSize, nDataFileMaxSize, nDataFileGrowth, pszLogsFileName, pszLogsFilePath, nLogsFileSize, nLogsFileMaxSize, nLogsFileGrowth, bReadOnly, FALSE)) > 0) ? ImportDatabase(pSourceDatabaseProfileInfo, pDestinationDatabaseProfileInfo, TRUE) : nResult);
}
BOOL CDBMS::ImportDatabase(CONST CDatabaseProfileInfo *pSourceDatabaseProfileInfo, CONST CDatabaseProfileInfo *pDestinationDatabaseProfileInfo, BOOL bDeleteOnFailure)
{
	CString  szCommand[2];
	CString  szCredentials;

	if (Connect(pDestinationDatabaseProfileInfo->GetServer()))
	{
		try
		{
			ExecuteSQL(STRING(IDS_ODBC_DATABASE_UNLINK));
		}
		catch (CException *pException)
		{
			pException->Delete();
		}
		try
		{
			for (szCommand[0].Format(STRING(IDS_ODBC_DATABASE_LINK), (LPCTSTR)(szCredentials = GetConnectCredentials(pSourceDatabaseProfileInfo->GetServer()))); szCredentials.IsEmpty(); )
			{
				if (bDeleteOnFailure)
				{
					try
					{
						szCommand[1].Format(STRING(IDS_ODBC_DATABASE_DELETE), (LPCTSTR)pDestinationDatabaseProfileInfo->GetName());
						ExecuteSQL(szCommand[1]);
					}
					catch (CException *pFailure)
					{
						pFailure->Delete();
					}
				}
				Close();
				return FALSE;
			}
			ExecuteSQL(szCommand[0]);
		}
		catch (CException *pException)
		{
			if (bDeleteOnFailure)
			{
				try
				{
					szCommand[1].Format(STRING(IDS_ODBC_DATABASE_DELETE), (LPCTSTR)pDestinationDatabaseProfileInfo->GetName());
					ExecuteSQL(szCommand[1]);
				}
				catch (CException *pFailure)
				{
					pFailure->Delete();
				}
			}
			pException->Delete();
			Close();
			return FALSE;
		}
		CDatabaseTablesRecordset  cDatabaseTablesRecordset(this);
		try
		{
			szCommand[0].Format(STRING(IDS_ODBC_DATABASE_TABLE_ENUMERATE), (LPCTSTR)pDestinationDatabaseProfileInfo->GetName());
			cDatabaseTablesRecordset.Open(CRecordset::dynamic, szCommand[0], CRecordset::none);
		}
		catch (CException *pException)
		{
			if (bDeleteOnFailure)
			{
				try
				{
					szCommand[1].Format(STRING(IDS_ODBC_DATABASE_DELETE), (LPCTSTR)pDestinationDatabaseProfileInfo->GetName());
					ExecuteSQL(szCommand[1]);
				}
				catch (CException *pFailure)
				{
					pFailure->Delete();
				}
			}
			try
			{
				ExecuteSQL(STRING(IDS_ODBC_DATABASE_UNLINK));
			}
			catch (CException *pException)
			{
				pException->Delete();
			}
			pException->Delete();
			Close();
			return FALSE;
		}
		while (!cDatabaseTablesRecordset.IsBOF() && !cDatabaseTablesRecordset.IsEOF())
		{
			try
			{
				szCommand[0].Format(STRING(IDS_ODBC_DATABASE_TABLE_DELETE), (LPCTSTR)pDestinationDatabaseProfileInfo->GetName(), (LPCTSTR)cDatabaseTablesRecordset.GetTable());
				ExecuteSQL(szCommand[0]);
			}
			catch (CException *pException)
			{
				pException->Delete();
				break;
			}
			try
			{
				cDatabaseTablesRecordset.MoveNext();
			}
			catch (CException *pException)
			{
				pException->Delete();
				break;
			}
		}
		if (!cDatabaseTablesRecordset.IsBOF() && !cDatabaseTablesRecordset.IsEOF())
		{
			cDatabaseTablesRecordset.Close();
			if (bDeleteOnFailure)
			{
				try
				{
					szCommand[0].Format(STRING(IDS_ODBC_DATABASE_DELETE), (LPCTSTR)pDestinationDatabaseProfileInfo->GetName());
					ExecuteSQL(szCommand[0]);
				}
				catch (CException *pException)
				{
					pException->Delete();
				}
			}
			try
			{
				ExecuteSQL(STRING(IDS_ODBC_DATABASE_UNLINK));
			}
			catch (CException *pException)
			{
				pException->Delete();
			}
			Close();
			return FALSE;
		}
		cDatabaseTablesRecordset.Close();
		try
		{
			szCommand[0].Format(STRING(IDS_ODBC_DATABASE_TABLE_SEARCH), (LPCTSTR)pSourceDatabaseProfileInfo->GetName());
			cDatabaseTablesRecordset.Open(CRecordset::dynamic, szCommand[0], CRecordset::none);
		}
		catch (CException *pException)
		{
			if (bDeleteOnFailure)
			{
				try
				{
					szCommand[1].Format(STRING(IDS_ODBC_DATABASE_DELETE), (LPCTSTR)pDestinationDatabaseProfileInfo->GetName());
					ExecuteSQL(szCommand[1]);
				}
				catch (CException *pFailure)
				{
					pFailure->Delete();
				}
			}
			try
			{
				ExecuteSQL(STRING(IDS_ODBC_DATABASE_UNLINK));
			}
			catch (CException *pException)
			{
				pException->Delete();
			}
			pException->Delete();
			Close();
			return FALSE;
		}
		while (!cDatabaseTablesRecordset.IsBOF() && !cDatabaseTablesRecordset.IsEOF())
		{
			try
			{
				szCommand[0].Format(STRING(IDS_ODBC_DATABASE_TABLE_IMPORT), (LPCTSTR)pDestinationDatabaseProfileInfo->GetName(), (LPCTSTR)cDatabaseTablesRecordset.GetTable(), (LPCTSTR)pSourceDatabaseProfileInfo->GetName(), (LPCTSTR)cDatabaseTablesRecordset.GetTable());
				ExecuteSQL(szCommand[0]);
			}
			catch (CException *pException)
			{
				pException->Delete();
				break;
			}
			try
			{
				cDatabaseTablesRecordset.MoveNext();
			}
			catch (CException *pException)
			{
				pException->Delete();
				break;
			}
		}
		if (!cDatabaseTablesRecordset.IsBOF() && !cDatabaseTablesRecordset.IsEOF())
		{
			cDatabaseTablesRecordset.Close();
			if (bDeleteOnFailure)
			{
				try
				{
					szCommand[0].Format(STRING(IDS_ODBC_DATABASE_DELETE), (LPCTSTR)pDestinationDatabaseProfileInfo->GetName());
					ExecuteSQL(szCommand[0]);
				}
				catch (CException *pException)
				{
					pException->Delete();
				}
			}
			try
			{
				ExecuteSQL(STRING(IDS_ODBC_DATABASE_UNLINK));
			}
			catch (CException *pException)
			{
				pException->Delete();
			}
			Close();
			return FALSE;
		}
		try
		{
			ExecuteSQL(STRING(IDS_ODBC_DATABASE_UNLINK));
		}
		catch (CException *pException)
		{
			pException->Delete();
		}
		cDatabaseTablesRecordset.Close();
		Close();
		return TRUE;
	}
	if (bDeleteOnFailure)
	{
		try
		{
			szCommand[0].Format(STRING(IDS_ODBC_DATABASE_DELETE), (LPCTSTR)pDestinationDatabaseProfileInfo->GetName());
			ExecuteSQL(szCommand[0]);
		}
		catch (CException *pException)
		{
			pException->Delete();
		}
	}
	return FALSE;
}
BOOL CDBMS::ImportDatabase(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, LPCTSTR pszFilesLocation, LPCTSTR pszFilesPrefix, LPCTSTR pszFilesExtension, LPCTSTR pszStringDelimiter, LPCTSTR pszFieldDelimiter, LPCTSTR pszRowDelimiter, CStringArray &szFailures)
{
	CString  szCommand;
	CString  szLocation;
	CString  szExtension;
	CString  szFileName[2];
	CFileFindEx  cFileFind;
	CLogicalDrives  cDrives;

	for (szFailures.RemoveAll(); Connect(pDatabaseProfileInfo->GetServer()); )
	{
		for (szLocation = (lstrlen(pszFilesLocation) > 0 && pszFilesLocation[lstrlen(pszFilesLocation) - 1] != cDrives.GetPathDelimiter()) ? (CString(pszFilesLocation) + cDrives.GetPathDelimiter()) : pszFilesLocation, szExtension = (lstrlen(pszFilesExtension) > 0 && pszFilesExtension[0] != cDrives.GetFileExtensionDelimiter()) ? (CString(cDrives.GetFileExtensionDelimiter()) + pszFilesExtension) : pszFilesExtension; cFileFind.FindFile((szFileName[0] = szLocation + pszFilesPrefix + szExtension)) && !cFileFind.FindNextFile(); )
		{
			if ((szFileName[1] = ConvertDataFile(szFileName[0], pszStringDelimiter, pszFieldDelimiter)).GetLength() > 0)
			{
				try
				{
					szCommand.Format(STRING(IDS_ODBC_DATABASE_FILES_IMPORT), (LPCTSTR)pDatabaseProfileInfo->GetName(), pszFilesPrefix, (LPCTSTR)pDatabaseProfileInfo->GetName(), pszFilesPrefix, (LPCTSTR)szFileName[1], STRING(IDS_ODBC_DATABASE_FILEFIELD_DELIMITER), pszRowDelimiter);
					ExecuteSQL(szCommand);
				}
				catch (CException *pException)
				{
					pException->Delete();
					szFailures.Add(pszFilesPrefix);
				}
				Close();
				cFileFind.Close();
				CFileEx::Remove(szFileName[1]);
				return((!szFailures.GetSize()) ? TRUE : FALSE);
			}
			Close();
			cFileFind.Close();
			szFailures.Add(pszFilesPrefix);
			return FALSE;
		}
		CDatabaseTablesRecordset  cDatabaseTablesRecordset(this);
		try
		{
			szCommand.Format(STRING(IDS_ODBC_DATABASE_TABLE_ENUMERATE), (LPCTSTR)pDatabaseProfileInfo->GetName());
			cDatabaseTablesRecordset.Open(CRecordset::dynamic, szCommand, CRecordset::none);
		}
		catch (CException *pException)
		{
			pException->Delete();
			Close();
			return FALSE;
		}
		for (szLocation = (lstrlen(pszFilesLocation) > 0 && pszFilesLocation[lstrlen(pszFilesLocation) - 1] != cDrives.GetPathDelimiter()) ? (CString(pszFilesLocation) + cDrives.GetPathDelimiter()) : pszFilesLocation, szExtension = (lstrlen(pszFilesExtension) > 0 && pszFilesExtension[0] != cDrives.GetFileExtensionDelimiter()) ? (CString(cDrives.GetFileExtensionDelimiter()) + pszFilesExtension) : pszFilesExtension; !cDatabaseTablesRecordset.IsBOF() && !cDatabaseTablesRecordset.IsEOF(); )
		{
			if ((szFileName[1] = ConvertDataFile((szFileName[0] = szLocation + pszFilesPrefix + cDatabaseTablesRecordset.GetTable() + szExtension), pszStringDelimiter, pszFieldDelimiter)).GetLength() > 0)
			{
				try
				{
					szCommand.Format(STRING(IDS_ODBC_DATABASE_FILES_IMPORT), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)cDatabaseTablesRecordset.GetTable(), (LPCTSTR)pDatabaseProfileInfo->GetName(), (LPCTSTR)cDatabaseTablesRecordset.GetTable(), (LPCTSTR)szFileName[1], STRING(IDS_ODBC_DATABASE_FILEFIELD_DELIMITER), pszRowDelimiter);
					ExecuteSQL(szCommand);
				}
				catch (CException *pException)
				{
					pException->Delete();
					szFailures.Add(cDatabaseTablesRecordset.GetTable());
				}
				try
				{
					cDatabaseTablesRecordset.MoveNext();
				}
				catch (CException *pException)
				{
					for (pException->Delete(); !szFailures.GetSize() || szFailures.GetAt(szFailures.GetUpperBound()) != cDatabaseTablesRecordset.GetTable(); )
					{
						szFailures.Add(cDatabaseTablesRecordset.GetTable());
						break;
					}
					CFileEx::Remove(szFileName[1]);
					break;
				}
				CFileEx::Remove(szFileName[1]);
				continue;
			}
			if (!szFailures.GetSize() || szFailures.GetAt(szFailures.GetUpperBound()) != cDatabaseTablesRecordset.GetTable()) szFailures.Add(cDatabaseTablesRecordset.GetTable());
			try
			{
				cDatabaseTablesRecordset.MoveNext();
			}
			catch (CException *pException)
			{
				pException->Delete();
				break;
			}
		}
		if (cDatabaseTablesRecordset.IsBOF() || cDatabaseTablesRecordset.IsEOF())
		{
			cDatabaseTablesRecordset.Close();
			Close();
			return TRUE;
		}
		cDatabaseTablesRecordset.Close();
		Close();
	}
	return FALSE;
}

BOOL CDBMS::ExportDatabase(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, CONST CStringArray &szTables, LPCTSTR pszFilesLocation, LPCTSTR pszFilesPrefix, LPCTSTR pszFilesExtension, LPCTSTR pszStringDelimiter, LPCTSTR pszFieldDelimiter, LPCTSTR pszRowDelimiter, BOOL bUnicode, CStringArray &szFailures)
{
	INT  nRow;
	INT  nRows;
	INT  nTable;
	INT  nTables;
	INT  nField;
	INT  nFields;
	BOOL  bSuccess;
	DWORD  cbData;
	CFile  cFile;
	CString  szRow;
	CString  szQuery;
	CString  szValue;
	CString  szLocation;
	CString  szExtension;
	CString  szFileName;
	CByteArray  nData;
	CDBVariant  cValue;
	CDWordArray  dwTypes;
	CStringArray  szRows;
	CLogicalDrives  cDrives;
	CRecordset  cRecordset(this);

	if (Connect(pDatabaseProfileInfo->GetServer(), pDatabaseProfileInfo->GetName()))
	{
		for (nTable = 0, nTables = (INT)szTables.GetSize(), szFailures.RemoveAll(); nTable < nTables; nTable++)
		{
			try
			{
				szQuery.Format(STRING(IDS_ODBC_DATABASE_TABLE_EXPORT), (LPCTSTR)szTables.GetAt(nTable));
				cRecordset.Open(CRecordset::dynamic, szQuery, CRecordset::none);
			}
			catch (CException *pException)
			{
				pException->Delete();
				szFailures.Add(szTables.GetAt(nTable));
				continue;
			}
			for (szRows.RemoveAll(); !cRecordset.IsEOF(); )
			{
				try
				{
					for (nField = 0, nFields = cRecordset.GetODBCFieldCount(), dwTypes.RemoveAll(); nField < nFields; nField++)
					{
						cRecordset.GetFieldValue(nField, cValue);
						dwTypes.Add(cValue.m_dwType);
					}
					for (nField = 0, cRecordset.MovePrev(), cRecordset.MoveNext(), szRow.Empty(); nField < nFields; nField++)
					{
						for (cRecordset.GetFieldValue(nField, szValue); nField > 0; )
						{
							szRow += pszFieldDelimiter;
							break;
						}
						szRow += (dwTypes.GetAt(nField) == DBVT_STRING || dwTypes.GetAt(nField) == DBVT_ASTRING || dwTypes.GetAt(nField) == DBVT_WSTRING) ? (pszStringDelimiter + szValue + pszStringDelimiter) : szValue;
					}
					szRows.Add(szRow);
				}
				catch (CException *pException)
				{
					pException->Delete();
					break;
				}
				try
				{
					cRecordset.MoveNext();
				}
				catch (CException *pException)
				{
					pException->Delete();
					break;
				}
			}
			if (cRecordset.IsEOF())
			{
				for (szLocation = (lstrlen(pszFilesLocation) > 0 && pszFilesLocation[lstrlen(pszFilesLocation) - 1] != cDrives.GetPathDelimiter()) ? (CString(pszFilesLocation) + cDrives.GetPathDelimiter()) : pszFilesLocation, szExtension = (lstrlen(pszFilesExtension) > 0 && pszFilesExtension[0] != cDrives.GetFileExtensionDelimiter()) ? (CString(cDrives.GetFileExtensionDelimiter()) + pszFilesExtension) : pszFilesExtension, bSuccess = FALSE; cFile.Open((szFileName = szLocation + pszFilesPrefix + szTables.GetAt(nTable) + szExtension), CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive); )
				{
					for (nRow = 0, nRows = (INT)szRows.GetSize(); nRow < nRows; nRow++)
					{
						szRow = (nRow > 0) ? (pszRowDelimiter + szRows.GetAt(nRow)) : szRows.GetAt(nRow);
						szRow = (nRow == nRows - 1) ? (szRow + pszRowDelimiter) : szRow;
#ifndef UNICODE
						if (!bUnicode)
						{
							if (!WriteFile(cFile.m_hFile, (LPCTSTR)szRow, szRow.GetLength(), &cbData, (LPOVERLAPPED)NULL)) break;
							continue;
						}
						nData.SetSize((szRow.GetLength() + 1)*sizeof(WCHAR));
						MultiByteToWideChar(CP_ACP, 0, szRow, -1, (LPWSTR)nData.GetData(), szRow.GetLength() + 1);
						if (!WriteFile(cFile.m_hFile, nData.GetData(), (DWORD)(nData.GetSize() - sizeof(WCHAR)), &cbData, (LPOVERLAPPED)NULL)) break;
						continue;
#else
						if (!bUnicode)
						{
							nData.SetSize(szRow.GetLength() + 1);
							WideCharToMultiByte(CP_ACP, 0, szRow, -1, (LPSTR)nData.GetData(), szRow.GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
							if (!WriteFile(cFile.m_hFile, nData.GetData(), (DWORD)nData.GetSize() - 1, &cbData, (LPOVERLAPPED)NULL)) break;
							continue;
						}
						if (!WriteFile(cFile.m_hFile, (LPCTSTR)szRow, szRow.GetLength()*sizeof(WCHAR), &cbData, (LPOVERLAPPED)NULL)) break;
						continue;
#endif
					}
					for (cFile.Close(); nRow < nRows; )
					{
						CFileEx::Remove(szFileName);
						break;
					}
					bSuccess = (nRow == nRows);
					break;
				}
				if (bSuccess)
				{
					cRecordset.Close();
					continue;
				}
			}
			szFailures.Add(szTables.GetAt(nTable));
			cRecordset.Close();
		}
		Close();
		return((!szFailures.GetSize()) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CDBMS::DeleteDatabase(CONST CDatabaseProfileInfo *pDatabaseProfileInfo)
{
	CString  szQuery;
	CString  szCommand;

	if (Connect(pDatabaseProfileInfo->GetServer()))
	{
		CDatabasesRecordset  cDatabasesRecordset(this);
		try
		{
			szQuery.Format(STRING(IDS_ODBC_DATABASE_SEARCH), (LPCTSTR)pDatabaseProfileInfo->GetName());
			cDatabasesRecordset.Open(CRecordset::dynamic, szQuery, CRecordset::none);
		}
		catch (CException *pException)
		{
			pException->Delete();
			Close();
			return FALSE;
		}
		if (!cDatabasesRecordset.IsBOF() && !cDatabasesRecordset.IsEOF())
		{
			try
			{
				szCommand.Format(STRING(IDS_ODBC_DATABASE_DELETE), (LPCTSTR)pDatabaseProfileInfo->GetName());
				ExecuteSQL(szCommand);
			}
			catch (CException *pException)
			{
				pException->Delete();
				Close();
				return FALSE;
			}
			Close();
			return TRUE;
		}
		Close();
	}
	return FALSE;
}

INT CDBMS::EnumDatabaseTables(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, CStringArray &szTables)
{
	CString  szCommand;

	for (szTables.RemoveAll(); Connect(pDatabaseProfileInfo->GetServer()); )
	{
		CDatabaseTablesRecordset  cDatabaseTablesRecordset(this);
		try
		{
			szCommand.Format(STRING(IDS_ODBC_DATABASE_TABLE_ENUMERATE), (LPCTSTR)pDatabaseProfileInfo->GetName());
			cDatabaseTablesRecordset.Open(CRecordset::dynamic, szCommand, CRecordset::none);
		}
		catch (CException *pException)
		{
			pException->Delete();
			Close();
			return 0;
		}
		while (!cDatabaseTablesRecordset.IsBOF() && !cDatabaseTablesRecordset.IsEOF())
		{
			try
			{
				szTables.Add(cDatabaseTablesRecordset.GetTable());
			}
			catch (CException *pException)
			{
				pException->Delete();
				break;
			}
			try
			{
				cDatabaseTablesRecordset.MoveNext();
			}
			catch (CException *pException)
			{
				pException->Delete();
				break;
			}
		}
		cDatabaseTablesRecordset.Close();
		Close();
		break;
	}
	return((INT)szTables.GetSize());
}

BOOL CDBMS::Connect(LPCTSTR pszServer)
{
	return Connect(pszServer, EMPTYSTRING);
}
BOOL CDBMS::Connect(LPCTSTR pszServer, LPCTSTR pszDatabase)
{
	try
	{
		OpenEx(GetConnectCredentials(pszServer, pszDatabase), CDatabase::noOdbcDialog);
	}
	catch (CException *pException)
	{
		pException->Delete();
		return FALSE;
	}
	return TRUE;
}

CString CDBMS::GetConnectCredentials(LPCTSTR pszServer) CONST
{
	return GetConnectCredentials(pszServer, EMPTYSTRING);
}
CString CDBMS::GetConnectCredentials(LPCTSTR pszServer, LPCTSTR pszDatabase) CONST
{
	INT  nUser;
	INT  nUsers;
	CString  szCredentials;
	CUserAccounts  cUserAccounts;
	CAccountToken  *pAccountToken;
	CAccountTokens  pAccountTokens;

	for (nUser = 0, nUsers = (cUserAccounts.SetComputerName(pszServer)) ? cUserAccounts.EnumAccounts(pAccountTokens) : 0; nUser < nUsers; nUser++)
	{
		if ((pAccountToken = pAccountTokens.GetAt(nUser)) != (CAccountToken *)NULL  &&  pAccountToken->IsAdministrator(TRUE))
		{
			szCredentials.Format((!lstrlen(pszDatabase)) ? STRING(IDS_DATABASE_DBMS_ODBCCONNECT) : STRING(IDS_DATABASE_DBMS_ODBCDATABASECONNECT), STRING(IDS_DATABASE_DBMS_ODBCDRIVERSQLSERVER), pszServer, (LPCTSTR)pAccountToken->GetPassword(), pszDatabase);
			return szCredentials;
		}
	}
	return EMPTYSTRING;
}

CString CDBMS::ConvertDataFile(LPCTSTR pszFileName, LPCTSTR pszStringDelimiter, LPCTSTR pszFieldDelimiter) CONST
{
	INT  i, j;
	INT  nPos;
	BOOL  bUnicode;
	DWORD  cbData;
	LPSTR  pszFile;
	LPBYTE  pszData;
	LPCTSTR  pPos[3];
	CString  szFileData[2];
	CUIntArray  nFileDataPos;
	TCHAR  szFileName[MAX_PATH];
	CFileFindEx  cFileFind;
	CFileEx  cFile[2];

	if (cFile[0].Open(pszFileName, CFile::modeRead | CFile::shareDenyWrite))
	{
		if ((pszData = (LPBYTE)GlobalAlloc(GPTR, (SIZE_T)(cFile[0].GetLength() + 1))))
		{
			if (ReadFile(cFile[0].m_hFile, pszData, (DWORD)cFile[0].GetLength(), &cbData, (LPOVERLAPPED)NULL))
			{
				if ((pszFile = (LPSTR)GlobalAlloc(GPTR, (!(bUnicode = IsTextUnicode(pszData, cbData, (LPINT)NULL))) ? (SIZE_T)(cFile[0].GetLength() + 1) : (SIZE_T)(cFile[0].GetLength() / sizeof(WCHAR) + 1))))
				{
					if (bUnicode) WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pszData, -1, pszFile, (INT)(cFile[0].GetLength() / sizeof(WCHAR) + 1), (LPCSTR)NULL, (LPBOOL)NULL);
					else  strcpy_s(pszFile, (size_t)cFile[0].GetLength() + 1, (LPCSTR)pszData);
#ifndef UNICODE
					szFileData[0] = pszFile;
#else
					MultiByteToWideChar(CP_ACP, 0, pszFile, -1, szFileData[0].GetBufferSetLength((INT)strlen(pszFile)), (INT)strlen(pszFile) + 1);
					szFileData[0].ReleaseBuffer();
#endif
					if (lstrlen(pszStringDelimiter) > 0)
					{
						for (pPos[0] = pPos[1] = (LPCTSTR)szFileData[0]; (pPos[2] = _tcsstr(pPos[1], pszStringDelimiter)); pPos[1] = pPos[2] + lstrlen(pszStringDelimiter))
						{
							nFileDataPos.Add((UINT)(pPos[2] - pPos[0]));
							continue;
						}
					}
					for (pPos[0] = pPos[1] = (LPCTSTR)szFileData[0]; (pPos[2] = _tcsstr(pPos[1], pszFieldDelimiter)); pPos[1] = pPos[2] + lstrlen(pszFieldDelimiter))
					{
						for (i = 0, j = (INT)nFileDataPos.GetSize() - 1, nPos = (INT)(pPos[2] - pPos[0]); i < j; i = i + 2)
						{
							if (nPos <= (INT)nFileDataPos.GetAt(i))
							{
								i = j;
								break;
							}
							if (nPos < (INT)nFileDataPos.GetAt(i + 1)) break;
						}
						CIdle  cIdle;
						if (i >= j)
						{
							szFileData[0].SetAt(nPos, STRINGCHAR(IDS_ODBC_DATABASE_FILEFIELD_DELIMITER));
							continue;
						}
					}
					if (lstrlen(pszStringDelimiter) > 0)
					{
						for (i = 0, j = (INT)nFileDataPos.GetSize(), nPos = 0; i < j; i++)
						{
							szFileData[1] += szFileData[0].Mid(nPos, nFileDataPos.GetAt(i) - nPos);
							nPos = nFileDataPos.GetAt(i) + lstrlen(pszStringDelimiter);
						}
						szFileData[1] += szFileData[0].Mid(nPos);
					}
#ifndef UNICODE
					CopyMemory(pszData, (LPCTSTR)szFileData[1], szFileData[1].GetLength() + 1);
#else
					WideCharToMultiByte(CP_ACP, 0, szFileData[1], -1, (LPSTR)pszData, szFileData[1].GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#endif
					if (cFileFind.FindFile(pszFileName) && !cFileFind.FindNextFile())
					{
						if (GetTempFileName(cFileFind.GetRoot(), (LPCTSTR)NULL, 0, szFileName) > 0)
						{
							if (cFile[1].Open(szFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
							{
								for (cFile[1].SeekToBegin(); WriteFile(cFile[1].m_hFile, pszData, szFileData[1].GetLength(), &cbData, (LPOVERLAPPED)NULL); )
								{
									cFile[1].SetLength(szFileData[1].GetLength());
									GlobalFree(pszFile);
									GlobalFree(pszData);
									cFileFind.Close();
									cFile[1].Close();
									cFile[0].Close();
									return szFileName;
								}
								cFile[1].Close();
								CFileEx::Remove(szFileName);
							}
						}
						cFileFind.Close();
					}
					GlobalFree(pszFile);
				}
			}
			GlobalFree(pszData);
		}
		cFile[0].Close();
	}
	return EMPTYSTRING;
}
