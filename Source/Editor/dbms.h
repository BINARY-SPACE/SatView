// DBMS.H : Database Management System Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the database management system related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2011/06/25 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DBMS_H__
#define __DBMS_H__


/////////////////////////////////////////////////////////////////////////////
// CDatabasesRecordset recordset

class CDatabasesRecordset : public CRecordset
{
	DECLARE_DYNAMIC(CDatabasesRecordset)

	// Construction
public:
	CDatabasesRecordset(CDatabase *pDatabase);

	// Attributes
private:
	CString  m_szName;

	// Field/Param Data
	//{{AFX_FIELD(CDatabasesRecordset, CRecordset)
	//}}AFX_FIELD

	// Operations
public:
	CString GetName() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabasesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDatabaseTablesRecordset recordset

class CDatabaseTablesRecordset : public CRecordset
{
	DECLARE_DYNAMIC(CDatabaseTablesRecordset)

	// Construction
public:
	CDatabaseTablesRecordset(CDatabase *pDatabase);

	// Attributes
private:
	CString  m_szTable;

	// Field/Param Data
	//{{AFX_FIELD(CDatabaseTablesRecordset, CRecordset)
	//}}AFX_FIELD

	// Operations
public:
	CString GetTable() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatabaseTablesRecordset)
public:
	virtual void DoFieldExchange(CFieldExchange *pFX);  // RFX support
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDBMS

class CDBMS : public CDatabase
{
	// Construction
public:
	CDBMS();

	// Attributes
public:

	// Operations
public:
	INT CreateDatabase(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, LPCTSTR pszDataFileName, LPCTSTR pszDataFilePath, UINT nDataFileSize, UINT nDataFileMaxSize, UINT nDataFileGrowth, LPCTSTR pszLogsFileName, LPCTSTR pszLogsFilePath, UINT nLogsFileSize, UINT nLogsFileMaxSize, UINT nLogsFileGrowth, BOOL bReadOnly, BOOL bTables = TRUE);
	INT ImportDatabase(CONST CDatabaseProfileInfo *pSourceDatabaseProfileInfo, CONST CDatabaseProfileInfo *pDestinationDatabaseProfileInfo, LPCTSTR pszDataFileName, LPCTSTR pszDataFilePath, UINT nDataFileSize, UINT nDataFileMaxSize, UINT nDataFileGrowth, LPCTSTR pszLogsFileName, LPCTSTR pszLogsFilePath, UINT nLogsFileSize, UINT nLogsFileMaxSize, UINT nLogsFileGrowth, BOOL bReadOnly);
	BOOL ImportDatabase(CONST CDatabaseProfileInfo *pSourceDatabaseProfileInfo, CONST CDatabaseProfileInfo *pDestinationDatabaseProfileInfo, BOOL bDeleteOnFailure = FALSE);
	BOOL ImportDatabase(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, LPCTSTR pszFilesLocation, LPCTSTR pszFilesPrefix, LPCTSTR pszFilesExtension, LPCTSTR pszStringDelimiter, LPCTSTR pszFieldDelimiter, LPCTSTR pszRowDelimiter, CStringArray &szFailures);
	BOOL ExportDatabase(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, CONST CStringArray &szTables, LPCTSTR pszFilesLocation, LPCTSTR pszFilesPrefix, LPCTSTR pszFilesExtension, LPCTSTR pszStringDelimiter, LPCTSTR pszFieldDelimiter, LPCTSTR pszRowDelimiter, BOOL bUnicode, CStringArray &szFailures);
	BOOL DeleteDatabase(CONST CDatabaseProfileInfo *pDatabaseProfileInfo);

	INT EnumDatabaseTables(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, CStringArray &szTables);

private:
	BOOL Connect(LPCTSTR pszServer);
	BOOL Connect(LPCTSTR pszServer, LPCTSTR pszDatabase);
	CString GetConnectCredentials(LPCTSTR pszServer) CONST;
	CString GetConnectCredentials(LPCTSTR pszServer, LPCTSTR pszDatabase) CONST;

	CString ConvertDataFile(LPCTSTR pszFileName, LPCTSTR pszStringDelimiter, LPCTSTR pszFieldDelimiter) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DBMS_H__
