// COMPILER.H : Database Compiler Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the database compiler related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/04/08 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __COMPILER_H__
#define __COMPILER_H__

#include "dialogs.h"


/////////////////////////////////////////////////////////////////////////////
// CSourceDatabaseCompileThread thread

// Specify the source database compilation flags
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_TMPACKETS   DATABASE_COMPONENT_TMPACKET
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_TCFUNCTIONS   DATABASE_COMPONENT_TCFUNCTION
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_TCSEQUENCES   DATABASE_COMPONENT_TCSEQUENCE
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_TCPROCEDURES   DATABASE_COMPONENT_TCPROCEDURE
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_OBPROCESSORS   DATABASE_COMPONENT_OBPROCESSOR
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_TMPARAMETERS   DATABASE_COMPONENT_TMPARAMETER
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_TCPARAMETERS   DATABASE_COMPONENT_TCPARAMETER
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_AND   DATABASE_COMPONENT_AND
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_GRD   DATABASE_COMPONENT_GRD
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_MMD   DATABASE_COMPONENT_MMD
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_POD   DATABASE_COMPONENT_POD
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_SCRIPT   DATABASE_COMPONENT_SCRIPT
#define SOURCEDATABASECOMPILETHREAD_COMPONENT_DERIVEDPARAMETERS   (DATABASE_COMPONENTS_ANY<<1)
#define SOURCEDATABASECOMPILETHREAD_ACTION_COMPILATION   (DATABASE_COMPONENTS_ANY<<2)
#define SOURCEDATABASECOMPILETHREAD_ACTION_SYNTAXCHECK   (DATABASE_COMPONENTS_ANY<<3)
#ifndef RC_INVOKED
#define SOURCEDATABASECOMPILETHREAD_COMPONENTS_ALL   (SOURCEDATABASECOMPILETHREAD_COMPONENT_TMPACKETS | SOURCEDATABASECOMPILETHREAD_COMPONENT_TCFUNCTIONS | SOURCEDATABASECOMPILETHREAD_COMPONENT_TCSEQUENCES | SOURCEDATABASECOMPILETHREAD_COMPONENT_TCPROCEDURES | SOURCEDATABASECOMPILETHREAD_COMPONENT_OBPROCESSORS | SOURCEDATABASECOMPILETHREAD_COMPONENT_TMPARAMETERS | SOURCEDATABASECOMPILETHREAD_COMPONENT_TCPARAMETERS | SOURCEDATABASECOMPILETHREAD_COMPONENT_DERIVEDPARAMETERS | SOURCEDATABASECOMPILETHREAD_COMPONENT_AND | SOURCEDATABASECOMPILETHREAD_COMPONENT_GRD | SOURCEDATABASECOMPILETHREAD_COMPONENT_MMD | SOURCEDATABASECOMPILETHREAD_COMPONENT_POD | SOURCEDATABASECOMPILETHREAD_COMPONENT_SCRIPT)
#endif
// Specify the source database compilation timer related settings
#define SOURCEDATABASECOMPILETHREAD_DEFAULT_TIMERID   100
#define SOURCEDATABASECOMPILETHREAD_DEFAULT_TIMEOUT   1000

class CSourceDatabaseCompileThread : public CThread
{
	DECLARE_DYNAMIC(CSourceDatabaseCompileThread)

	friend class  CSourceDatabase;

	// Construction
public:
	CSourceDatabaseCompileThread();

	// Attributes
private:
	UINT  m_nErrors;
	UINT  m_nWarnings;
	ULONGLONG  m_nComponents;
	CCompileDirectives  m_pDirectives;
	CStringArray  m_szLines;
	CEvent  m_bCompiling;
	BOOL  m_bAborted;

	// Operations
public:
	BOOL StartCompiling(ULONGLONG nComponents);
	BOOL IsCompiling() CONST;
	BOOL StopCompiling();

private:
	VOID CompileDerivedParameters(CONST CBinaryDatabase *pDatabase);
	BOOL SaveDerivedParametersFile(CONST CBinaryDatabase *pDatabase);
	BOOL LoadDerivedParametersFile(CONST CBinaryDatabase *pDatabase, CString &szData);
	BOOL TranslateDerivedParametersFile(CONST CBinaryDatabase *pDatabase, LPCTSTR pszData, CString &szData, CStringArray &szGlobalParameters, CStringArray &szLocalParameters, CStringArray &szStaticParameters, CStringArray &szVolatileParameters, CStringArray &szPastProcedures, CStringArray &szPastProcedureParameters, CStringArray &szPastParameters, CUIntArray &nPastSamples);
	VOID CalculateDerivedParameterFileLines(LPCTSTR pszData, CUIntArray &nLines) CONST;
	UINT DetermineDerivedParameterFileLine(CONST CUIntArray &nLines, INT nPos) CONST;
	UINT DetermineDerivedParameterFileColumn(CONST CUIntArray &nLines, INT nPos) CONST;
	BOOL ConvertDerivedParameterFileLineToData(LPCTSTR pszText, CByteArray &nData) CONST;
	BOOL CollectDerivedParameter(LPCTSTR pszParameter, BOOL bParameter, CStringArray &szParameters) CONST;
	BOOL ExamineDerivedParameter(CONST CBinaryDatabase *pDatabase, LPCTSTR pszParameter);
	INT FindDerivedParameter(CONST CStringArray &szParameters, LPCTSTR pszParameter, BOOL bScope = TRUE) CONST;
	BOOL SetDerivedParameterPastSamples(LPCTSTR pszProcedure, LPCTSTR pszParameter, CStringArray &szPastProcedures, CStringArray &szPastProcedureParameters, INT nSamples, BOOL bAll) CONST;
	BOOL SetDerivedParameterPastSamples(LPCTSTR pszArgument, CStringArray &szPastParameters, CUIntArray &nPastSamples, INT nSamples) CONST;
	INT GetDerivedParameterPastSamples(LPCTSTR pszProcedure, LPCTSTR pszParameter, CONST CStringArray &szPastProcedures, CONST CStringArray &szPastProcedureParameters, CUIntArray &nPastSamples) CONST;
	INT GetDerivedParameterPastSamples(LPCTSTR pszArgument, CONST CStringArray &szPastParameters, CONST CUIntArray &nPastSamples) CONST;
	INT FindDerivedParameterPastSamples(LPCTSTR pszProcedureOrArgument, CONST CStringArray &szPastParameters, BOOL bInsert = FALSE) CONST;
	CString FormatDerivedParameterCode(LPCTSTR pszCode, INT nBlockLevel = 0) CONST;
	CString GetDerivedParametersFileName(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFormat) CONST;
	BOOL SecureDerivedParametersFile(LPCTSTR pszFileName) CONST;
	CString GetDerivedParametersCompilerFileName() CONST;
	CString GetDerivedParametersCompilerFileName(LPCTSTR pszDirectory) CONST;
	CString GetDerivedParametersLinkerFileName() CONST;
	CString GetDerivedParametersCompileOptions(CONST CBinaryDatabase *pDatabase) CONST;
	CString GetDerivedParametersLinkOptions(CONST CBinaryDatabase *pDatabase, CString &szOutputName, BOOL bTemporary = FALSE) CONST;
	LPCTSTR FindDerivedParameterLanguageSourceCodeKeyword(LPCTSTR pszSourceCode, INT nPos, LPCTSTR pszKeyword) CONST;
	CString FormatDerivedParametersCompilerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszError, INT nLine);
	VOID ShowDerivedParametersCompilerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszErrors);
	VOID ShowDerivedParametersLinkerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszErrors);
	VOID CleanupDerivedParametersBuildOutput(CONST CBinaryDatabase *pDatabase);

	VOID ShowStartMessages();
	VOID ShowStopMessages();
	VOID ShowMessage(LPCTSTR pszMessage, BOOL bTimestamp = TRUE, BOOL bAudition = FALSE);
	VOID ShowError(LPCTSTR pszError);
	VOID ShowError(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);
	VOID ShowWarning(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszWarning);
	VOID SetErrorCount(UINT nCount = 0);
	UINT GetErrorCount() CONST;
	VOID SetWarningCount(UINT nCount = 0);
	UINT GetWarningCount() CONST;

private:
	static BOOL CALLBACK ShowMessage(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszMessage, BOOL bWarning, BOOL bTimestamp, BOOL bAudition);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSourceDatabaseCompileThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSourceDatabaseCompileThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSourceDatabase

class CSourceDatabase : public CDatabaseEngine
{
	// Construction
public:
	CSourceDatabase();
	CSourceDatabase(CDatabaseProfileInfo *pDatabaseInfo);
	~CSourceDatabase();

	// Attributes
private:
	UINT_PTR  m_nTimerID;
	CCompileBatches  m_pBatches;
private:
	CSourceDatabaseCompileThread  *m_pCompileThread;

	// Operations
public:
	BOOL Open(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, BOOL bLoad = TRUE, BOOL bBinary = TRUE);
	BOOL Open(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, LPCTSTR pszDBMS, BOOL bLoad = TRUE, BOOL bBinary = TRUE);
	VOID Close();

	BOOL SetCompileBatches(CONST CCompileBatches &pBatches);
	INT GetCompileBatches(CCompileBatches &pBatches) CONST;

	BOOL StartCompiling(ULONGLONG nComponents = SOURCEDATABASECOMPILETHREAD_ACTION_COMPILATION | SOURCEDATABASECOMPILETHREAD_COMPONENTS_ALL);
	BOOL IsCompiling() CONST;
	VOID ScheduleCompiling();
	BOOL StopCompiling();

	CSourceDatabaseCompileThread *GetCompileThread() CONST;

public:
	static VOID CALLBACK CompileTimerProc(HWND hWnd, UINT uMsg, UINT_PTR nEventID, DWORD dwTime);
};

/////////////////////////////////////////////////////////////////////////////


#endif // __COMPILER_H__
