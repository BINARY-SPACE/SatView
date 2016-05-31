// COMPILER.CPP : Database Compiler Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the database compiler
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/04/08 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CSourceDatabaseCompileThread

IMPLEMENT_DYNAMIC(CSourceDatabaseCompileThread, CThread)

CSourceDatabaseCompileThread::CSourceDatabaseCompileThread() : CThread()
{
	m_nErrors = 0;
	m_nWarnings = 0;
	m_nComponents = 0;
	m_bAborted = FALSE;
}

BOOL CSourceDatabaseCompileThread::StartCompiling(ULONGLONG nComponents)
{
	for (m_nComponents = nComponents, m_bAborted = FALSE; CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL); )
	{
		WaitForSingleObject(m_bCompiling, INFINITE);
		return TRUE;
	}
	return FALSE;
}

BOOL CSourceDatabaseCompileThread::IsCompiling() CONST
{
	return IsThreadActive();
}

BOOL CSourceDatabaseCompileThread::StopCompiling()
{
	if (IsCompiling())
	{
		ShowMessage(STRING(IDS_COMPILER_MESSAGE_BREAKCOMPILING));
		m_bAborted = TRUE;
		return TRUE;
	}
	return FALSE;
}

int CSourceDatabaseCompileThread::Run()
{
	INT  nScript;
	INT  nScripts;
	INT  nDisplay;
	INT  nDisplays;
	INT  nErrors;
	INT  nWarnings;
	INT  nProcedure;
	INT  nProcedures;
	BOOL  bDatabase;
	BOOL  bBatchAbort;
	BOOL  bSyntaxCheck;
	CString  szMessage;
	CString  szDatabase;
	ULONGLONG  nComponents;
	CDatabases  cDatabases;
	CUIntArray  nPrivileges;
	CMMDLayout  *pMMDLayout;
	CMMDLayouts  pMMDLayouts;
	CStringArray  szUsers[2];
	CStringArray  szPasswords;
	CAutomationScript  *pScript;
	CAutomationScripts  pScripts;
	CDatabaseTCProcedure  *pTCProcedure;
	CDatabaseTCProcedures  pTCProcedures;
	CDatabaseProfileInfo  *pDatabaseProfileInfo;
	CDatabaseProfiles  pDatabases;
	CBinaryDatabase  cDatabase;
	CUpdateUI  cUpdateUI;

	for (ShowStartMessages(); GetDatabase()->OpenDBMS(CDatabase::noOdbcDialog); )
	{
		for (cDatabase.Attach(GetDatabase()), szDatabase = GetAccountDatabase(), nComponents = ((m_nComponents & SOURCEDATABASECOMPILETHREAD_COMPONENTS_ALL) == SOURCEDATABASECOMPILETHREAD_COMPONENTS_ALL) ? DATABASE_COMPONENTS_ALL : DATABASE_COMPONENTS_ANY, bSyntaxCheck = (m_nComponents & SOURCEDATABASECOMPILETHREAD_ACTION_SYNTAXCHECK) ? TRUE : FALSE; (m_nComponents & SOURCEDATABASECOMPILETHREAD_ACTION_COMPILATION) == SOURCEDATABASECOMPILETHREAD_ACTION_COMPILATION; )
		{
			UpdateDatabase(nComponents, szDatabase);
			break;
		}
		if (!m_bAborted)
		{
			for (cDatabase.GetUsers(szUsers[0], szUsers[1], nPrivileges), GetDatabase()->Compile(&cDatabase, ShowMessage, (m_nComponents & SOURCEDATABASECOMPILETHREAD_COMPONENT_AND) ? ((m_nComponents & SOURCEDATABASECOMPILETHREAD_COMPONENTS_ALL) | DATABASE_SUBCOMPONENT_AND_NORMAL | DATABASE_SUBCOMPONENT_AND_GENERIC) : (m_nComponents & SOURCEDATABASECOMPILETHREAD_COMPONENTS_ALL)), cDatabase.SetUsers(szUsers[0], szUsers[1], nPrivileges); (m_nComponents & SOURCEDATABASECOMPILETHREAD_COMPONENT_DERIVEDPARAMETERS) && !m_bAborted; )
			{
				CompileDerivedParameters(&cDatabase);
				break;
			}
		}
		for (nDisplay = 0, nDisplays = (m_nComponents & SOURCEDATABASECOMPILETHREAD_COMPONENT_MMD) ? GetDatabase()->EnumMMDs(pMMDLayouts) : 0, bBatchAbort = FALSE; nDisplay < nDisplays && !m_bAborted; nDisplay++)
		{
			if ((pMMDLayout = (!m_bAborted) ? pMMDLayouts.GetAt(nDisplay) : (CMMDLayout *)NULL) != (CMMDLayout *)NULL)
			{
				CMMDWnd::StartCompilingMMD(&cDatabase, pMMDLayout->GetName(), bSyntaxCheck, TRUE, nErrors, nWarnings, bBatchAbort);
				SetWarningCount(GetWarningCount() + nWarnings);
				SetErrorCount(GetErrorCount() + nErrors);
				m_bAborted |= bBatchAbort;
				continue;
			}
			break;
		}
		for (nProcedure = 0, nProcedures = (m_nComponents & SOURCEDATABASECOMPILETHREAD_COMPONENT_TCPROCEDURES) ? GetDatabase()->EnumProcedures(pTCProcedures) : 0; nProcedure < nProcedures && !m_bAborted; nProcedure++)
		{
			if ((pTCProcedure = (!m_bAborted) ? pTCProcedures.GetAt(nProcedure) : (CDatabaseTCProcedure *)NULL))
			{
				CTCProcedureWnd::StartCompilingProcedure(&cDatabase, pTCProcedure, bSyntaxCheck, TRUE, nErrors, nWarnings, bBatchAbort);
				SetWarningCount(GetWarningCount() + nWarnings);
				SetErrorCount(GetErrorCount() + nErrors);
				m_bAborted |= bBatchAbort;
				continue;
			}
			break;
		}
		for (nScript = 0, nScripts = (m_nComponents & SOURCEDATABASECOMPILETHREAD_COMPONENT_SCRIPT) ? GetDatabase()->EnumScripts(pScripts) : 0; nScript < nScripts && !m_bAborted; nScript++)
		{
			if ((pScript = (!m_bAborted) ? pScripts.GetAt(nScript) : (CAutomationScript *)NULL) != (CAutomationScript *)NULL)
			{
				CScriptWnd::StartCompilingScript(&cDatabase, pScript, bSyntaxCheck, TRUE, nErrors, nWarnings, bBatchAbort);
				SetWarningCount(GetWarningCount() + nWarnings);
				SetErrorCount(GetErrorCount() + nErrors);
				m_bAborted |= bBatchAbort;
				continue;
			}
			break;
		}
		if (!GetErrorCount() && !m_bAborted)
		{
			if ((m_nComponents & SOURCEDATABASECOMPILETHREAD_ACTION_COMPILATION) && ((m_nComponents & SOURCEDATABASECOMPILETHREAD_COMPONENTS_ALL) & (SOURCEDATABASECOMPILETHREAD_COMPONENTS_ALL & ~(SOURCEDATABASECOMPILETHREAD_COMPONENT_MMD | SOURCEDATABASECOMPILETHREAD_COMPONENT_TCPROCEDURES | SOURCEDATABASECOMPILETHREAD_COMPONENT_SCRIPT))))
			{
				for (ShowMessage(STRING(IDS_DATABASE_SAVING)); (bDatabase = cDatabase.Save((DATABASE_COMPONENTS_ALL | DATABASE_SUBCOMPONENTS_ALL) & ~(DATABASE_COMPONENT_MMD | DATABASE_COMPONENT_TCPROCEDURE | DATABASE_COMPONENT_SCRIPT))); )
				{
					for (GetDatabase()->Attach(&cDatabase); (pDatabaseProfileInfo = (cDatabases.GetDatabases(pDatabases, TRUE)) ? pDatabases.GetAt(pDatabases.Find(cDatabase.GetServer(), cDatabase.GetName())) : (CDatabaseProfileInfo *)NULL); )
					{
						pDatabaseProfileInfo->Copy(&cDatabase);
						cDatabases.SetDatabases(pDatabases);
						break;
					}
					break;
				}
				if (!bDatabase) ShowError(STRING(IDS_DATABASE_SAVE_FAILURE));
			}
		}
		if ((m_nComponents & SOURCEDATABASECOMPILETHREAD_ACTION_COMPILATION) == SOURCEDATABASECOMPILETHREAD_ACTION_COMPILATION  &&  m_bAborted) UpdateDatabase(((m_nComponents & SOURCEDATABASECOMPILETHREAD_COMPONENTS_ALL) == SOURCEDATABASECOMPILETHREAD_COMPONENTS_ALL) ? ~DATABASE_COMPONENTS_ALL : ~DATABASE_COMPONENTS_ANY, szDatabase);
		GetDatabase()->CloseDBMS();
		break;
	}
	ShowStopMessages();
	return 0;
}

VOID CSourceDatabaseCompileThread::CompileDerivedParameters(CONST CBinaryDatabase *pDatabase)
{
	INT  nIndex;
	INT  nSample;
	INT  nSamples;
	INT  nTrigger;
	INT  nTriggers;
	INT  nOperator;
	INT  nOperators;
	INT  nParameter;
	INT  nParameters;
	INT  nDataPos[9];
	INT  nStaticParameter;
	INT  nStaticParameters;
	CHAR  szOut[8192];
	TCHAR  szDataPos;
	DWORD  dwBuf;
	DWORD  dwOut;
	DWORD  cbOut;
	CFileEx  cFile;
	HANDLE  hStdIn[3];
	HANDLE  hStdOut[3];
	HANDLE  hStdError;
	LPCTSTR  pDataPos;
	LPCTSTR  pKeyPos[2];
	CString  szData[2];
	CString  szCheck;
	CString  szError;
	CString  szErrors;
	CString  szHeader;
	CString  szTrailer;
	CString  szMessage;
	CString  szWarning;
	CString  szOptions;
	CString  szInitCode;
	CString  szExecCode;
	CString  szVariable;
	CString  szArgument;
	CString  szParameter;
	CString  szProcedure;
	CString  szProcedures;
	CString  szAssignment;
	CString  szStatements;
	CString  szOutputName;
	CString  szFileName[3];
	ULONGLONG  nAttributes;
	CFileFindEx  cFileFind;
	CByteArray  nFileData;
	CUIntArray  nTriggerRefs[2];
	CUIntArray  nPastSamples[2];
	CStringArray  szParameters[5];
	CStringArray  szPastProcedures;
	CStringArray  szPastParameters;
	CStringArray  szStaticParameters;
	CStringArray  szVolatileParameters;
	CStringArray  szPastProcedureParameters;
	CDatabaseTMParameter  *pDatabaseTMParameter[2];
	SECURITY_ATTRIBUTES  sCompilerSecurityAttributes = { 0 };
	PROCESS_INFORMATION  sCompilerInformation = { 0 };
	STARTUPINFO  sCompilerStartupInformation = { 0 };

	ShowMessage(STRING(IDS_COMPILER_MESSAGE_COMPILING_DERIVEDPARAMETERS));
	if (((m_nComponents & SOURCEDATABASECOMPILETHREAD_ACTION_COMPILATION) && SaveDerivedParametersFile(pDatabase)) || (m_nComponents & SOURCEDATABASECOMPILETHREAD_ACTION_SYNTAXCHECK))
	{
		if (LoadDerivedParametersFile(pDatabase, szData[0]) && TranslateDerivedParametersFile(pDatabase, szData[0], szData[1], szParameters[0], szParameters[1], szStaticParameters, szVolatileParameters, szPastProcedures, szPastProcedureParameters, szPastParameters, nPastSamples[0]))
		{
			if (cFile.Open(GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_COMPILENAME)), CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
			{
				for (nParameter = 0, nParameters = (INT)pDatabase->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
				{
					if ((pDatabaseTMParameter[0] = pDatabase->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
					{
						for (nTrigger = 0, nTriggers = pDatabaseTMParameter[0]->GetTriggerRefs(nTriggerRefs[0], nTriggerRefs[1]); nTrigger < nTriggers; nTrigger++)
						{
							if ((pDatabaseTMParameter[1] = pDatabase->GetTMParameters()->GetAt(nTriggerRefs[0].GetAt(nTrigger))) && (pDatabaseTMParameter[1]->GetAttributes() & TMPARAMETER_NATURE_DERIVED_SAVED)) continue;
							nTriggerRefs[0].RemoveAt(nTrigger);
							nTriggerRefs[1].RemoveAt(nTrigger);
							nTriggers--;
							nTrigger--;
						}
						pDatabaseTMParameter[0]->SetTriggerRefs(nTriggerRefs[0], nTriggerRefs[1]);
					}
				}
				for (nParameter = 0, nParameters = (INT)szParameters[0].GetSize(); nParameter < nParameters || (!nParameter && !nParameters); nParameter++)
				{
					for (szHeader = (!nParameter) ? (CString(STRING(IDS_DERIVEDPARAMETERFILE_INCLUDES)) + STRING(IDS_DERIVEDPARAMETERFILE_EXTERNALS)) : EMPTYSTRING, szParameter.Empty(); nParameter < nParameters; )
					{
						szParameter.Format(STRING(IDS_DERIVEDPARAMETERFILE_VARIABLES), (LPCTSTR)szParameters[0].GetAt(nParameter));
						break;
					}
					if (!ConvertDerivedParameterFileLineToData((nParameter == nParameters - 1) ? (szHeader + szParameter + CR + EOL + CR + EOL) : (szHeader + szParameter), nFileData))
					{
						ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_GENERAL));
						break;
					}
					if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
					{
						ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_OPERATEFILE));
						break;
					}
				}
				if (nParameter < nParameters)
				{
					CleanupDerivedParametersBuildOutput(pDatabase);
					return;
				}
				for (szStatements = STRING(IDS_DERIVEDPARAMETERFILE_HELPERPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_CHECKLONGLONGPARAMETERPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_CHECKULONGLONGPARAMETERPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_CHECKFLOATINGPOINTPARAMETERPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_CHECKSTRINGPARAMETERPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_CHECKPARAMETERSTATUSPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_UPDATEPARAMETERPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_GETVALUEPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_SETRAWVALUEPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_GETRAWVALUEPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_GETVALUETIMEPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_GETPASTVALUEPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_GETPASTRAWVALUEPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_GETPASTVALUETIMEPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_CALCULATEAVERAGEVALUEPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_GETSTATUSPROCEDURES), szStatements += STRING(IDS_DERIVEDPARAMETERFILE_GETTMBANDWIDTHPROCEDURES), szStatements += (GetDatabase()->ConstructCustomDerivationCode(pDatabase, szProcedures, szInitCode, szExecCode)) ? szProcedures : EMPTYSTRING, szStatements += STRING(IDS_DERIVEDPARAMETERFILE_INITIALIZATIONPROCEDUREHEADER); !szStatements.IsEmpty(); )
				{
					if (!ConvertDerivedParameterFileLineToData(szStatements, nFileData))
					{
						ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_GENERAL));
						CleanupDerivedParametersBuildOutput(pDatabase);
						return;
					}
					if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
					{
						ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_OPERATEFILE));
						CleanupDerivedParametersBuildOutput(pDatabase);
						return;
					}
					break;
				}
				for (nParameter = 0, nParameters = (INT)pDatabase->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
				{
					if ((pDatabaseTMParameter[0] = pDatabase->GetTMParameters()->GetAt(nParameter)) && (pDatabaseTMParameter[0]->GetAttributes() & (TMPARAMETER_NATURE_DERIVED | TMPARAMETER_NATURE_DERIVED_OL | TMPARAMETER_NATURE_DERIVED_SPEL | TMPARAMETER_NATURE_DERIVED_HARDCODED)))
					{
						szParameter.Format(STRING(IDS_DERIVEDPARAMETERFILE_INITIALIZATIONPROCEDUREREGISTRATION), (LPCTSTR)pDatabaseTMParameter[0]->GetTag());
						if (!ConvertDerivedParameterFileLineToData(szParameter, nFileData))
						{
							ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_GENERAL));
							break;
						}
						if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
						{
							ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_OPERATEFILE));
							break;
						}
					}
				}
				if (nParameter < nParameters)
				{
					CleanupDerivedParametersBuildOutput(pDatabase);
					return;
				}
				for (nParameter = 0, nParameters = (INT)szParameters[0].GetSize(); nParameter < nParameters || (!nParameter && !nParameters); nParameter++)
				{
					for (szTrailer = (nParameter == nParameters - 1 || !nParameters) ? STRING(IDS_DERIVEDPARAMETERFILE_INITIALIZATIONPROCEDURETRAILER) : EMPTYSTRING; nParameter < nParameters; nParameter++)
					{
						szParameter.Format(STRING(IDS_DERIVEDPARAMETERFILE_INITIALIZATIONPROCEDURESTATEMENT), (LPCTSTR)szParameters[0].GetAt(nParameter), (LPCTSTR)szParameters[0].GetAt(nParameter), (LPCTSTR)szParameters[0].GetAt(nParameter), (LPCTSTR)szParameters[0].GetAt(nParameter), (LPCTSTR)szParameters[0].GetAt(nParameter));
						break;
					}
					if (!ConvertDerivedParameterFileLineToData((!nParameter) ? (STRING(IDS_DERIVEDPARAMETERFILE_INITIALIZATIONPROCEDUREBODY) + szParameter + szTrailer) : (szParameter + szTrailer), nFileData))
					{
						ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_GENERAL));
						break;
					}
					if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
					{
						ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_OPERATEFILE));
						break;
					}
				}
				if (nParameter < nParameters)
				{
					CleanupDerivedParametersBuildOutput(pDatabase);
					return;
				}
				for (nParameter = 0, nParameters = (INT)szPastParameters.GetSize(), szStatements = STRING(IDS_DERIVEDPARAMETERFILE_INITIALIZEPARAMETERSPROCEDUREHEADER); (!nParameter && !nParameters) || nParameter < nParameters; nParameter++)
				{
					szParameter.Format(STRING(IDS_DERIVEDPARAMETERFILE_INITIALIZEPARAMETERSPROCEDUREBODY), (nParameters > 0) ? (LPCTSTR)szPastParameters.GetAt(nParameter) : EMPTYSTRING, (nParameters > 0) ? nPastSamples[0].GetAt(nParameter) : 0);
					szParameter = (nParameters > 0) ? ((nParameter == nParameters - 1) ? (LPCTSTR)(szParameter + szInitCode + STRING(IDS_DERIVEDPARAMETERFILE_INITIALIZEPARAMETERSPROCEDURETRAILER)) : (LPCTSTR)szParameter) : (szInitCode + STRING(IDS_DERIVEDPARAMETERFILE_INITIALIZEPARAMETERSPROCEDURETRAILER));
					szParameter = (!nParameter) ? (szStatements + szParameter) : szParameter;
					if (!ConvertDerivedParameterFileLineToData(szParameter, nFileData))
					{
						ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_GENERAL));
						break;
					}
					if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
					{
						ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_OPERATEFILE));
						break;
					}
				}
				if (nParameter < nParameters)
				{
					CleanupDerivedParametersBuildOutput(pDatabase);
					return;
				}
				for (nDataPos[0] = nDataPos[1] = 0, szParameters[2].RemoveAll(), szParameters[3].RemoveAll(), szParameters[4].RemoveAll(); (nDataPos[1] = ((pDataPos = FindDerivedParameterLanguageSourceCodeKeyword((LPCTSTR)szData[1], nDataPos[0], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE)))) ? (INT)(pDataPos - (LPCTSTR)szData[1]) : -1) >= 0; nDataPos[0] = nDataPos[1], szParameters[2].RemoveAll(), szParameters[3].RemoveAll(), szParameters[4].RemoveAll())
				{
					for (nDataPos[1] = nDataPos[1] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE)); nDataPos[1] < szData[1].GetLength() && ((szDataPos = szData[1].GetAt(nDataPos[1])) == SPACE[0] || szDataPos == TAB || szDataPos == CR || szDataPos == EOL); nDataPos[1]++);
					for (nDataPos[2] = nDataPos[1], szParameter.Empty(); nDataPos[2] - nDataPos[1] <= GetDatabase()->GetTMParameterTagLength(); nDataPos[2]++)
					{
						if (GetDatabase()->CheckTMParameterTag(szParameter + szData[1].GetAt(nDataPos[2])))
						{
							szParameter += szData[1].GetAt(nDataPos[2]);
							continue;
						}
						break;
					}
					szProcedure.Format(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREHEADER), (LPCTSTR)szParameter, (LPCTSTR)szParameter);
					if (pDatabase->GetTMParameters()->Find((szParameter = (_tcsncmp((LPCTSTR)szData[1] + nDataPos[1], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS))) && _tcsncmp((LPCTSTR)szData[1] + nDataPos[1], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN)))) ? (LPCTSTR)szParameter : EMPTYSTRING)) >= 0)
					{
						if ((pKeyPos[0] = FindDerivedParameterLanguageSourceCodeKeyword((LPCTSTR)szData[1], nDataPos[2], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN))))
						{
							if ((pKeyPos[1] = FindDerivedParameterLanguageSourceCodeKeyword((LPCTSTR)szData[1], nDataPos[2], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_END))) && pKeyPos[0] <= pKeyPos[1] - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN)))
							{
								for (CopyMemory(szStatements.GetBufferSetLength((INT)(pKeyPos[1] - pKeyPos[0] - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN)))), pKeyPos[0] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN)), (pKeyPos[1] - pKeyPos[0] - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN)))*sizeof(TCHAR)); TRUE; )
								{
									szStatements.ReleaseBuffer();
									break;
								}
								if ((szStatements = (_tcsspn(szStatements, CString(SPACE) + TAB + CR + EOL) < (size_t)szStatements.GetLength()) ? (LPCTSTR)szStatements : EMPTYSTRING).GetLength() > 0)
								{
									for (nParameter = FindDerivedParameter(szParameters[1], szParameter), nParameters = (INT)szParameters[1].GetSize(); nParameter >= 0 && nParameter < nParameters; nParameter++)
									{
										if (szParameters[1].GetAt(nParameter).Left(szParameter.GetLength() + 1) == szParameter + EOL)
										{
											for (nDataPos[3] = 0, szArgument.Format(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_PARAMETERARGUMENT), (LPCTSTR)szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)); nDataPos[3] < szStatements.GetLength(); nDataPos[3] += nDataPos[4] + 1)
											{
												if ((nDataPos[4] = szStatements.Mid(nDataPos[3]).Find(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1))) >= 0)
												{
													if (((nDataPos[3] + nDataPos[4] == 0 || !GetDatabase()->CheckTMParameterTag(szStatements.Mid(nDataPos[3] + nDataPos[4] - 1, szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1).GetLength()))) && (nDataPos[3] + nDataPos[4] + szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1).GetLength() == szStatements.GetLength() || !GetDatabase()->CheckTMParameterTag(szStatements.Mid(nDataPos[3] + nDataPos[4] + 1, szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1).GetLength())))) || (nDataPos[3] + nDataPos[4] - szArgument.Find(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) >= 0 && szStatements.Mid(nDataPos[3] + nDataPos[4] - szArgument.Find(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)), szArgument.GetLength()) == szArgument))
													{
														for (nDataPos[5] = nDataPos[3] + nDataPos[4] + szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1).GetLength(); nDataPos[5] < szStatements.GetLength(); nDataPos[5]++)
														{
															if ((szDataPos = szStatements.GetAt(nDataPos[5])) != SPACE[0] && szDataPos != TAB  &&  szDataPos != CR  &&  szDataPos != EOL)
															{
																for (nOperator = 0, nOperators = MAXDERIVEDPARAMETERLANGUAGEOPERATOR - MINDERIVEDPARAMETERLANGUAGEOPERATOR; nOperator <= nOperators; nOperator++)
																{
																	if (szStatements.Mid(nDataPos[5], lstrlen(STRING(MAXDERIVEDPARAMETERLANGUAGEOPERATOR - nOperator))) == STRING(MAXDERIVEDPARAMETERLANGUAGEOPERATOR - nOperator) && szStatements.Mid(nDataPos[5] + 1, lstrlen(STRING(MAXDERIVEDPARAMETERLANGUAGEOPERATOR - nOperator))) != STRING(MAXDERIVEDPARAMETERLANGUAGEOPERATOR - nOperator))
																	{
																		if (!szParameters[2].GetSize() || szParameters[2].GetAt(szParameters[2].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[2].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																		if ((pDatabaseTMParameter[0] = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)))) && (pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT))
																		{
																			if ((nDataPos[6] = szStatements.Mid(nDataPos[5] + lstrlen(STRING(MAXDERIVEDPARAMETERLANGUAGEOPERATOR - nOperator))).Find(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREFLOATCONVERSION)[lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREFLOATCONVERSION)) - 1])) >= 0)
																			{
																				for (nDataPos[7] = nDataPos[5] + lstrlen(STRING(MAXDERIVEDPARAMETERLANGUAGEOPERATOR - nOperator)); nDataPos[7] < szStatements.GetLength(); nDataPos[7]++)
																				{
																					if (!_istspace(szStatements.GetAt(nDataPos[7]))) break;
																					continue;
																				}
																				szAssignment.Format(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREFLOATCONVERSION), (LPCTSTR)szStatements.Left(nDataPos[5] + lstrlen(STRING(MAXDERIVEDPARAMETERLANGUAGEOPERATOR - nOperator))), (LPCTSTR)szStatements.Mid(nDataPos[7], nDataPos[6] - (nDataPos[7] - (nDataPos[5] + lstrlen(STRING(MAXDERIVEDPARAMETERLANGUAGEOPERATOR - nOperator))))));
																				szStatements = szAssignment + szStatements.Mid(nDataPos[5] + lstrlen(STRING(MAXDERIVEDPARAMETERLANGUAGEOPERATOR - nOperator)) + nDataPos[6] + 1);
																			}
																		}
																		szStatements = szStatements.Left(nDataPos[3] + nDataPos[4]) + STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREPREFIXVARIABLE) + szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1) + szStatements.Mid(nDataPos[3] + nDataPos[4] + szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1).GetLength());
																		nDataPos[4] += lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREPREFIXVARIABLE));
																		break;
																	}
																	if (nOperator == nOperators)
																	{
																		if ((nDataPos[3] + nDataPos[4] > 0 && GetDatabase()->CheckTMParameterTag(szStatements.Mid(nDataPos[3] + nDataPos[4] - 1, szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1).GetLength()))) || (nDataPos[3] + nDataPos[4] + szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1).GetLength() < szStatements.GetLength() && GetDatabase()->CheckTMParameterTag(szStatements.Mid(nDataPos[3] + nDataPos[4] + 1, szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1).GetLength()))))
																		{
																			if ((nDataPos[7] = (nDataPos[6] = nDataPos[3] + nDataPos[4] - szArgument.Find(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1))) - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTINTVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTINTVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTUINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTUINTVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTUINTVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTFLOATVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTFLOATVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTFLOATVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTSTRINGVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTSTRINGVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTSTRINGVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALINTVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALINTVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALUINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALUINTVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALUINTVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALFLOATVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALFLOATVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALFLOATVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWINTVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWINTVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWUINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWUINTVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWUINTVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWFLOATVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWFLOATVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWFLOATVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTVALUETIME))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTVALUETIME), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTVALUETIME))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEINTVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEINTVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEUINTVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEUINTVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEUINTVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																			if ((nDataPos[7] = nDataPos[6] - lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEFLOATVALUE))) >= 0 && !_tcsncmp(szStatements.Mid(nDataPos[7]), STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEFLOATVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEFLOATVALUE))))
																			{
																				if (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[4].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																				break;
																			}
																		}
																		if (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) szParameters[3].Add(szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
																		break;
																	}
																}
																break;
															}
														}
													}
													continue;
												}
												break;
											}
											if ((!szParameters[2].GetSize() || szParameters[2].GetAt(szParameters[2].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) && (!szParameters[3].GetSize() || szParameters[3].GetAt(szParameters[3].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)) && (!szParameters[4].GetSize() || szParameters[4].GetAt(szParameters[4].GetUpperBound()) != szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1)))
											{
												szWarning.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEWARNING_UNUSEDPARAMETER), (LPCTSTR)szParameter, (LPCTSTR)szParameters[1].GetAt(nParameter).Mid(szParameter.GetLength() + 1));
												ShowWarning(szWarning);
											}
											continue;
										}
										break;
									}
									for (nParameter = 0, nParameters = (INT)szParameters[2].GetSize(); nParameter < nParameters; nParameter++)
									{
										if (szParameter != szParameters[2].GetAt(nParameter))
										{
											szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALASSIGNMENT), (LPCTSTR)szParameter, (LPCTSTR)szParameters[2].GetAt(nParameter));
											ShowError(szError);
										}
									}
									for (nParameter = 0, nParameters = (INT)szParameters[3].GetSize(), nAttributes = ((pDatabaseTMParameter[0] = ((nIndex = pDatabase->GetTMParameters()->Find(szParameter)) >= 0) ? pDatabase->GetTMParameters()->GetAt(nIndex) : (CDatabaseTMParameter *)NULL)) ? pDatabaseTMParameter[0]->GetAttributes() : 0; nParameter < nParameters; nParameter++)
									{
										if ((pDatabaseTMParameter[0] = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szParameters[3].GetAt(nParameter)))))
										{
											if ((pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_TRIGGERTYPE_CONSTANT) != TMPARAMETER_TRIGGERTYPE_CONSTANT)
											{
												for (nTrigger = 0, nTriggers = pDatabaseTMParameter[0]->GetTriggerRefs(nTriggerRefs[0], nTriggerRefs[1]); nTrigger < nTriggers; nTrigger++)
												{
													if (nIndex == (INT)nTriggerRefs[0].GetAt(nTrigger)) break;
													continue;
												}
												if (nIndex >= 0 && nTrigger == nTriggers)
												{
													if (pDatabaseTMParameter[0]->GetTag() != szParameter)
													{
														for (nStaticParameter = 0, nStaticParameters = (INT)szStaticParameters.GetSize(); nStaticParameter < nStaticParameters; nStaticParameter++)
														{
															if (szStaticParameters.GetAt(nStaticParameter) == szParameter + EOL + pDatabaseTMParameter[0]->GetTag()) break;
															continue;
														}
														if (nStaticParameter == nStaticParameters)
														{
															nTriggerRefs[0].Add(nIndex);
															nTriggerRefs[1].Add(-1);
															pDatabaseTMParameter[0]->SetTriggerRefs(nTriggerRefs[0], nTriggerRefs[1]);
														}
													}
												}
											}
											if ((pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || ((pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && !(pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)))
											{
												szVariable.Format(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREFLOATVARIABLE), (LPCTSTR)szParameters[3].GetAt(nParameter));
												szProcedure += szVariable;
												continue;
											}
											if (pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
											{
												szVariable.Format(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURESTRINGVARIABLE), (LPCTSTR)szParameters[3].GetAt(nParameter));
												szProcedure += szVariable;
												continue;
											}
											if ((pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
											{
												szVariable.Format(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREINTVARIABLE), (LPCTSTR)szParameters[3].GetAt(nParameter));
												szProcedure += szVariable;
												continue;
											}
											szVariable.Format(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREUINTVARIABLE), (LPCTSTR)szParameters[3].GetAt(nParameter));
											szProcedure += szVariable;
										}
									}
									for (nParameter = 0, nParameters = (INT)szParameters[4].GetSize(); nParameter < nParameters; nParameter++)
									{
										if ((pDatabaseTMParameter[0] = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szParameters[4].GetAt(nParameter)))))
										{
											if ((pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_TRIGGERTYPE_CONSTANT) != TMPARAMETER_TRIGGERTYPE_CONSTANT)
											{
												for (nTrigger = 0, nTriggers = pDatabaseTMParameter[0]->GetTriggerRefs(nTriggerRefs[0], nTriggerRefs[1]); nTrigger < nTriggers; nTrigger++)
												{
													if (nIndex == (INT)nTriggerRefs[0].GetAt(nTrigger)) break;
													continue;
												}
												if (nIndex >= 0 && nTrigger == nTriggers)
												{
													if (pDatabaseTMParameter[0]->GetTag() != szParameter)
													{
														for (nStaticParameter = 0, nStaticParameters = (INT)szStaticParameters.GetSize(); nStaticParameter < nStaticParameters; nStaticParameter++)
														{
															if (szStaticParameters.GetAt(nStaticParameter) == szParameter + EOL + pDatabaseTMParameter[0]->GetTag()) break;
															continue;
														}
														if (nStaticParameter == nStaticParameters)
														{
															nTriggerRefs[0].Add(nIndex);
															nTriggerRefs[1].Add(-1);
															pDatabaseTMParameter[0]->SetTriggerRefs(nTriggerRefs[0], nTriggerRefs[1]);
														}
													}
												}
											}
										}
									}
									for (nParameter = 0, nParameters = (INT)szParameters[2].GetSize(); nParameter < nParameters; nParameter++)
									{
										if ((pDatabaseTMParameter[0] = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szParameters[2].GetAt(nParameter)))))
										{
											if ((pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
											{
												szVariable.Format(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREINTVARIABLE), (LPCTSTR)(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREPREFIXVARIABLE) + szParameters[2].GetAt(nParameter)));
												szProcedure += szVariable;
												continue;
											}
											if (pDatabaseTMParameter[0]->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)
											{
												szVariable.Format(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREFLOATVARIABLE), (LPCTSTR)(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREPREFIXVARIABLE) + szParameters[2].GetAt(nParameter)));
												szProcedure += szVariable;
												continue;
											}
											szVariable.Format(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREUINTVARIABLE), (LPCTSTR)(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREPREFIXVARIABLE) + szParameters[2].GetAt(nParameter)));
											szProcedure += szVariable;
											continue;
										}
									}
									if (szParameters[2].GetSize() + szParameters[3].GetSize() + szParameters[4].GetSize() > 0)
									{
										szProcedure += STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURESTATUSVARIABLE);
										szProcedure += STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREOCCURRENCEVARIABLE);
										szProcedure += CString(CR) + CString(EOL);
									}
									for (nParameter = 0, nParameters = (INT)szParameters[3].GetSize(); nParameter < nParameters; nParameter++)
									{
										if ((pDatabaseTMParameter[0] = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szParameters[3].GetAt(nParameter)))))
										{
											szCheck.Format((FindDerivedParameter(szVolatileParameters, szParameter + EOL + pDatabaseTMParameter[0]->GetTag(), FALSE) < 0) ? STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURECHECKSOURCEVARIABLE) : STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURECHECKVOLATILESOURCEVARIABLE), (LPCTSTR)szParameters[3].GetAt(nParameter), (LPCTSTR)szParameters[3].GetAt(nParameter));
											szProcedure += szCheck;
										}
									}
									for (nParameter = 0, nParameters = (INT)szParameters[4].GetSize(); nParameter < nParameters; nParameter++)
									{
										if ((pDatabaseTMParameter[0] = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szParameters[4].GetAt(nParameter)))))
										{
											for (nSample = 0, nSamples = GetDerivedParameterPastSamples(szParameter, szParameters[4].GetAt(nParameter), szPastProcedures, szPastProcedureParameters, nPastSamples[1]); nSample < nSamples; nSample++)
											{
												szCheck.Format((FindDerivedParameter(szVolatileParameters, szParameter + EOL + pDatabaseTMParameter[0]->GetTag(), FALSE) < 0) ? STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURECHECKPASTSOURCEVARIABLE) : STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURECHECKVOLATILEPASTSOURCEVARIABLE), (LPCTSTR)szParameters[4].GetAt(nParameter), nPastSamples[1].GetAt(nSample));
												szProcedure += szCheck;
											}
										}
									}
									for (nDataPos[3] = nDataPos[4] = 0; nDataPos[3] < szStatements.GetLength() && ((szDataPos = szStatements.GetAt(nDataPos[3])) == SPACE[0] || szDataPos == CR || szDataPos == EOL); nDataPos[3]++)
									{
										if (szDataPos == CR || szDataPos == EOL)
										{
											nDataPos[4] = nDataPos[3] + 1;
											continue;
										}
									}
									for (nDataPos[3] = nDataPos[5] = szStatements.GetLength() - 1; nDataPos[3] > nDataPos[4] && ((szDataPos = szStatements.GetAt(nDataPos[3])) == SPACE[0] || szDataPos == CR || szDataPos == EOL); nDataPos[3]--)
									{
										if (szDataPos == CR || szDataPos == EOL)
										{
											nDataPos[5] = nDataPos[3] - 1;
											continue;
										}
									}
									for (nParameter = 0, nParameters = (INT)szParameters[2].GetSize(), szProcedure += STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURESTATEMENTSPROLOG) + FormatDerivedParameterCode(szStatements.Mid(nDataPos[4], nDataPos[5] - nDataPos[4] + 1)) + CString(CR) + CString(EOL); nParameter < nParameters; nParameter++)
									{
										szVariable.Format(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREUPDATEVARIABLE), (LPCTSTR)szParameters[2].GetAt(nParameter), (LPCTSTR)szParameters[2].GetAt(nParameter));
										szProcedure += CString(SPACE) + CString(SPACE) + szVariable;
									}
									szProcedure += STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURESTATEMENTSEPILOG);
								}
								else
								{
									if ((nParameter = (ExamineDerivedParameter(pDatabase, szParameter)) ? FindDerivedParameter(szParameters[1], szParameter) : -1) >= 0 && nParameter < szParameters[1].GetSize() - 1 && szParameters[1].GetAt(nParameter + 1).Left(szParameter.GetLength()) == szParameter)
									{
										szWarning.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEWARNING_EMPTYPROCEDURE), (LPCTSTR)szParameter);
										ShowWarning(szWarning);
									}
								}
								if (ConvertDerivedParameterFileLineToData(szProcedure + STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURETRAILER), nFileData))
								{
									if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL))
									{
										ShowError((szError = STRING(IDS_DERIVEDPARAMETERFILE_ERROR_OPERATEFILE)));
										break;
									}
									continue;
								}
							}
						}
						ShowError((szError = STRING(IDS_DERIVEDPARAMETERFILE_ERROR_GENERAL)));
						break;
					}
				}
				if (!szExecCode.IsEmpty())
				{
					for (; ConvertDerivedParameterFileLineToData(szExecCode, nFileData); )
					{
						if (!WriteFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &dwBuf, (LPOVERLAPPED)NULL)) ShowError((szError = STRING(IDS_DERIVEDPARAMETERFILE_ERROR_OPERATEFILE)));
						break;
					}
				}
				cFile.Close();
			}
			else  ShowError((szError = STRING(IDS_DERIVEDPARAMETERFILE_ERROR_OPERATEFILE)));
		}
		else
		{
			CleanupDerivedParametersBuildOutput(pDatabase);
			return;
		}
	}
	if (!szError.IsEmpty())
	{
		CleanupDerivedParametersBuildOutput(pDatabase);
		return;
	}
	sCompilerSecurityAttributes.bInheritHandle = TRUE;
	sCompilerSecurityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	if (CreatePipe(&hStdOut[0], &hStdOut[1], &sCompilerSecurityAttributes, 0))
	{
		if (CreatePipe(&hStdIn[0], &hStdIn[1], &sCompilerSecurityAttributes, 0))
		{
			if (DuplicateHandle(GetCurrentProcess(), hStdOut[1], GetCurrentProcess(), &hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS) && DuplicateHandle(GetCurrentProcess(), hStdOut[0], GetCurrentProcess(), &hStdOut[2], 0, FALSE, DUPLICATE_SAME_ACCESS) && DuplicateHandle(GetCurrentProcess(), hStdIn[1], GetCurrentProcess(), &hStdIn[2], 0, FALSE, DUPLICATE_SAME_ACCESS))
			{
				sCompilerStartupInformation.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
				sCompilerStartupInformation.cb = sizeof(STARTUPINFO);
				sCompilerStartupInformation.hStdOutput = hStdOut[1];
				sCompilerStartupInformation.hStdInput = hStdIn[0];
				sCompilerStartupInformation.hStdError = hStdError;
				sCompilerStartupInformation.wShowWindow = SW_HIDE;
				for (szFileName[0] = GetDerivedParametersCompilerFileName(), szOptions = GetDerivedParametersCompileOptions(pDatabase), CloseHandle(hStdOut[0]), CloseHandle(hStdIn[1]); CreateProcess(szFileName[0], (LPTSTR)(LPCTSTR)szOptions, (LPSECURITY_ATTRIBUTES)NULL, (LPSECURITY_ATTRIBUTES)NULL, TRUE, CREATE_NEW_CONSOLE | IDLE_PRIORITY_CLASS, (LPVOID)NULL, (LPCTSTR)NULL, &sCompilerStartupInformation, &sCompilerInformation); )
				{
					for (CloseHandle(hStdIn[0]), CloseHandle(hStdOut[1]), CloseHandle(hStdError), cbOut = 0; WaitForSingleObject(sCompilerInformation.hProcess, 0) == WAIT_TIMEOUT; )
					{
						if (ReadFile(hStdOut[2], szOut, sizeof(szOut), &dwOut, (LPOVERLAPPED)NULL) && dwOut > 0)
						{
							cbOut += dwOut;
#ifndef UNICODE
							CopyMemory(szError.GetBufferSetLength(dwOut), szOut, dwOut);
							szError.ReleaseBuffer();
#else
							MultiByteToWideChar(CP_ACP, 0, szOut, dwOut, szError.GetBufferSetLength(dwOut), dwOut + 1);
							szError.ReleaseBuffer();
#endif
							if (szErrors.IsEmpty())
							{
								if (cFileFind.FindFile(GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_COMPILENAME))) && !cFileFind.FindNextFile())
								{
									szMessage = szError;
									szMessage.MakeLower();
									szFileName[1] = cFileFind.GetFilePath();
									szFileName[2] = cFileFind.GetFileName();
									szFileName[1].MakeLower();
									szFileName[2].MakeLower();
									if ((nDataPos[8] = szMessage.Find(szFileName[2])) >= 0 && (szError.GetAt(nDataPos[8] + szFileName[2].GetLength()) == CR || szError.GetAt(nDataPos[8] + szFileName[2].GetLength()) == EOL))
									{
										for (szError = szError.Mid(nDataPos[8] + szFileName[2].GetLength()); szError.GetLength() > 0; )
										{
											if (szError.GetAt(0) == CR || szError.GetAt(0) == EOL)
											{
												szError = szError.Mid(1);
												continue;
											}
											break;
										}
										szErrors = szError;
										cFileFind.Close();
										continue;
									}
									if ((nDataPos[8] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILECOMMANDLINEPREFIX))) >= 0)
									{
										szErrors = szError.Mid(nDataPos[8]);
										cFileFind.Close();
										continue;
									}
									if ((nDataPos[8] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILEFATALERRORPREFIX))) >= 0)
									{
										szErrors = szError.Mid(nDataPos[8]);
										cFileFind.Close();
										continue;
									}
									if ((nDataPos[8] = szMessage.Find(szFileName[1])) >= 0)
									{
										szErrors = szError.Mid(nDataPos[8]);
										cFileFind.Close();
										continue;
									}
									for (; _tcsstr(szMessage, STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILEFATALERRORPREFIX)) || _tcsstr(szMessage, STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILEERRORPREFIX)) || _tcsstr(szMessage, STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILEWARNINGPREFIX)); )
									{
										szErrors = szError;
										break;
									}
									cFileFind.Close();
									continue;
								}
								szMessage = szError;
								szMessage.MakeLower();
								szErrors = (szErrors.IsEmpty()) ? (((nDataPos[8] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILECOMMANDLINEPREFIX))) >= 0) ? szError.Mid(nDataPos[8]) : szErrors) : szErrors;
								szErrors = (szErrors.IsEmpty()) ? (((nDataPos[8] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILEFATALERRORPREFIX))) >= 0) ? szError.Mid(nDataPos[8]) : szErrors) : szErrors;
								continue;
							}
							szErrors += szError;
						}
					}
					if (!cbOut)
					{
						szError = STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILERENVIRONMENT);
						ShowError(szError);
					}
					for (ShowDerivedParametersCompilerErrors(pDatabase, szErrors); !szErrors.IsEmpty() || !cbOut; )
					{
						CleanupDerivedParametersBuildOutput(pDatabase);
						CloseHandle(hStdOut[2]);
						CloseHandle(hStdIn[2]);
						return;
					}
					CloseHandle(hStdIn[2]);
					CloseHandle(hStdOut[2]);
					if (CreatePipe(&hStdOut[0], &hStdOut[1], &sCompilerSecurityAttributes, 0))
					{
						if (CreatePipe(&hStdIn[0], &hStdIn[1], &sCompilerSecurityAttributes, 0))
						{
							if (DuplicateHandle(GetCurrentProcess(), hStdOut[1], GetCurrentProcess(), &hStdError, 0, TRUE, DUPLICATE_SAME_ACCESS) && DuplicateHandle(GetCurrentProcess(), hStdOut[0], GetCurrentProcess(), &hStdOut[2], 0, FALSE, DUPLICATE_SAME_ACCESS) && DuplicateHandle(GetCurrentProcess(), hStdIn[1], GetCurrentProcess(), &hStdIn[2], 0, FALSE, DUPLICATE_SAME_ACCESS))
							{
								sCompilerStartupInformation.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
								sCompilerStartupInformation.cb = sizeof(STARTUPINFO);
								sCompilerStartupInformation.hStdOutput = hStdOut[1];
								sCompilerStartupInformation.hStdInput = hStdIn[0];
								sCompilerStartupInformation.hStdError = hStdError;
								sCompilerStartupInformation.wShowWindow = SW_HIDE;
								for (szFileName[0] = GetDerivedParametersLinkerFileName(), szOptions = GetDerivedParametersLinkOptions(pDatabase, szOutputName, (m_nComponents & SOURCEDATABASECOMPILETHREAD_ACTION_SYNTAXCHECK) ? TRUE : FALSE), CFileEx::SetAttributes(szOutputName, CFileEx::GetAttributes(szOutputName) & ~FILE_ATTRIBUTE_READONLY), CloseHandle(hStdOut[0]), CloseHandle(hStdIn[1]); CreateProcess(szFileName[0], (LPTSTR)(LPCTSTR)szOptions, (LPSECURITY_ATTRIBUTES)NULL, (LPSECURITY_ATTRIBUTES)NULL, TRUE, CREATE_NEW_CONSOLE | IDLE_PRIORITY_CLASS, (LPVOID)NULL, (LPCTSTR)NULL, &sCompilerStartupInformation, &sCompilerInformation); )
								{
									for (CloseHandle(hStdIn[0]), CloseHandle(hStdOut[1]), CloseHandle(hStdError), szErrors.Empty(), szError.Empty(), cbOut = 0; WaitForSingleObject(sCompilerInformation.hProcess, 0) == WAIT_TIMEOUT; )
									{
										if (ReadFile(hStdOut[2], szOut, sizeof(szOut) - 1, &dwOut, (LPOVERLAPPED)NULL) && dwOut > 0)
										{
											cbOut += dwOut;
#ifndef UNICODE
											CopyMemory(szError.GetBufferSetLength(dwOut), szOut, dwOut);
											szError.ReleaseBuffer();
#else
											MultiByteToWideChar(CP_ACP, 0, szOut, dwOut, szError.GetBufferSetLength(dwOut), dwOut + 1);
											szError.ReleaseBuffer();
#endif
											szOut[dwOut] = EOS;
											szErrors += szOut;
										}
									}
									if (!cbOut)
									{
										szError = STRING(IDS_DERIVEDPARAMETERFILE_ERROR_LINKERENVIRONMENT);
										ShowError(szError);
									}
									if (cFileFind.FindFile(GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_OBJECTNAME))) && !cFileFind.FindNextFile())
									{
										szMessage = szErrors;
										szMessage.MakeLower();
										szFileName[1] = cFileFind.GetFileName();
										szFileName[1].MakeLower();
										szError = ((nDataPos[8] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_LINKFATALERRORPREFIX))) >= 0) ? (LPCTSTR)szErrors.Mid(nDataPos[8]) : EMPTYSTRING;
										szError = ((nDataPos[8] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_LINKERRORPREFIX))) >= 0) ? szErrors.Mid(nDataPos[8]) : szError;
										szError = ((nDataPos[8] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_LINKWARNINGPREFIX))) >= 0) ? szErrors.Mid(nDataPos[8]) : szError;
										szError = ((nDataPos[8] = szMessage.Find(szFileName[1])) >= 0) ? szErrors.Mid(nDataPos[8]) : szError;
										cFileFind.Close();
									}
									for (ShowDerivedParametersLinkerErrors(pDatabase, (szErrors = (cbOut > 0) ? (LPCTSTR)szError : EMPTYSTRING)); m_nComponents & SOURCEDATABASECOMPILETHREAD_ACTION_COMPILATION; )
									{
										CFileEx::SetAttributes(szOutputName, CFileEx::GetAttributes(szOutputName) | FILE_ATTRIBUTE_READONLY);
										SecureDerivedParametersFile(szOutputName);
										break;
									}
									if (m_nComponents & SOURCEDATABASECOMPILETHREAD_ACTION_SYNTAXCHECK) CFileEx::Remove(szOutputName);
									CleanupDerivedParametersBuildOutput(pDatabase);
									CloseHandle(hStdOut[2]);
									CloseHandle(hStdIn[2]);
									return;
								}
								CloseHandle(hStdIn[0]);
								CloseHandle(hStdIn[2]);
								CloseHandle(hStdOut[1]);
								CloseHandle(hStdOut[2]);
								CloseHandle(hStdError);
								ShowError((!cFileFind.FindFile(szFileName[0])) ? STRING(IDS_DERIVEDPARAMETERFILE_ERROR_LINKERPATH) : STRING(IDS_DERIVEDPARAMETERFILE_ERROR_STDINOUT));
								CleanupDerivedParametersBuildOutput(pDatabase);
								return;
							}
							CloseHandle(hStdIn[0]);
							CloseHandle(hStdIn[1]);
						}
						CloseHandle(hStdOut[0]);
						CloseHandle(hStdOut[1]);
					}
					ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_STDINOUT));
					CleanupDerivedParametersBuildOutput(pDatabase);
					return;
				}
				CloseHandle(hStdIn[0]);
				CloseHandle(hStdIn[2]);
				CloseHandle(hStdOut[1]);
				CloseHandle(hStdOut[2]);
				CloseHandle(hStdError);
				ShowError((!cFileFind.FindFile(szFileName[0])) ? STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILERPATH) : STRING(IDS_DERIVEDPARAMETERFILE_ERROR_STDINOUT));
				CleanupDerivedParametersBuildOutput(pDatabase);
				return;
			}
			CloseHandle(hStdIn[0]);
			CloseHandle(hStdIn[1]);
		}
		CloseHandle(hStdOut[0]);
		CloseHandle(hStdOut[1]);
	}
	ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_STDINOUT));
	CleanupDerivedParametersBuildOutput(pDatabase);
}

BOOL CSourceDatabaseCompileThread::SaveDerivedParametersFile(CONST CBinaryDatabase *pDatabase)
{
	INT  nPos;
	INT  nLength;
	INT  nMarginPos;
	INT  nParameter;
	INT  nParameters;
	DWORD  cbDerivedFile;
	CFileEx  cDerivedFile;
	CString  szFileName;
	CString  szHeader[2];
	CString  szExpression;
	CString  szHeaderLine;
	CString  szHeaderFormat;
	CTimeKey  tDerivedFile;
	CByteArray  nHeaderData;
	CStringArray  szParameters;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if (cDerivedFile.Open((szFileName = GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_SOURCENAME))), CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
	{
		for (nParameter = 0, nParameters = (INT)pDatabase->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
			{
				if (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_NATURE_DERIVED | TMPARAMETER_NATURE_DERIVED_OL | TMPARAMETER_NATURE_DERIVED_SPEL | TMPARAMETER_NATURE_DERIVED_HARDCODED))
				{
					if (!ExamineDerivedParameter(pDatabase, pDatabaseTMParameter->GetTag()))
					{
						szParameters.Add(pDatabaseTMParameter->GetTag());
						continue;
					}
				}
			}
		}
		if ((nPos = CString((szHeader[0] = szHeader[1] = STRING(IDS_DERIVEDPARAMETERFILE_HEADER))).Find(TAB)) >= 0)
		{
			if ((nLength = ((nLength = szHeader[0].Mid(nPos).Find(EOL)) >= 0) ? szHeader[0].Mid(nPos + nLength + 1).Find(EOL) : -1) >= 0)
			{
				for (nParameter = 0, nParameters = (INT)szParameters.GetSize(), szHeaderFormat = szHeader[0].Mid(nPos + 1, szHeader[0].Mid(nPos + 1).Find(EOL) + 1), szHeader[1] = szHeader[0].Left(nPos) + szHeader[0].Mid(nPos + szHeader[0].Mid(nPos).Find(EOL) + 1); nParameter < nParameters; nParameter++)
				{
					if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szParameters.GetAt(nParameter)))) != (CDatabaseTMParameter *)NULL)
					{
						szHeaderLine.Format(szHeaderFormat, (!nParameter) ? (LPCTSTR)tDerivedFile.Format(STRING(IDS_DERIVEDPARAMETERFILE_TIMEFORMAT)) : CString(SPACE[0], tDerivedFile.Format(STRING(IDS_DERIVEDPARAMETERFILE_TIMEFORMAT)).GetLength()), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
						szHeaderLine = (!pDatabaseTMParameter->GetDescription().IsEmpty()) ? (((nMarginPos = szHeaderLine.Find(pDatabaseTMParameter->GetDescription())) >= 0 && szHeaderLine.GetLength() < nLength) ? (szHeaderLine.Left(nMarginPos + pDatabaseTMParameter->GetDescription().GetLength()) + CString(SPACE[0], nLength - szHeaderLine.GetLength()) + szHeaderLine.Right(szHeaderLine.GetLength() - nMarginPos - pDatabaseTMParameter->GetDescription().GetLength())) : szHeaderLine) : (((nMarginPos = szHeaderLine.ReverseFind(SPACE[0])) >= 0 && szHeaderLine.GetLength() < nLength) ? (szHeaderLine.Left(nMarginPos + 1) + CString(SPACE[0], nLength - szHeaderLine.GetLength()) + szHeaderLine.Right(szHeaderLine.GetLength() - nMarginPos - 1)) : szHeaderLine);
						szHeader[1] = szHeader[1].Left(nPos) + szHeaderLine + szHeader[1].Mid(nPos);
						nPos += szHeaderLine.GetLength();
					}
				}
				if (!nParameters)
				{
					szHeaderLine.Format(szHeaderFormat, (LPCTSTR)tDerivedFile.Format(STRING(IDS_DERIVEDPARAMETERFILE_TIMEFORMAT)), EMPTYSTRING, EMPTYSTRING);
					szHeaderLine = ((nMarginPos = szHeaderLine.Find(CString(SPACE[0], 2))) >= 0 && szHeaderLine.GetLength() < nLength) ? (szHeaderLine.Left(nMarginPos - 1) + CString(SPACE[0], nLength - szHeaderLine.GetLength() + 1) + szHeaderLine.Right(szHeaderLine.GetLength() - nMarginPos)) : szHeaderLine;
					szHeader[1] = szHeader[1].Left(nPos) + szHeaderLine + szHeader[1].Mid(nPos);
				}
				szHeader[0].Format(szHeader[1], (LPCTSTR)pDatabase->GetSpacecraft(), tDerivedFile.GetYear());
				nHeaderData.SetSize(szHeader[0].GetLength());
				if (nHeaderData.GetSize() == szHeader[0].GetLength())
				{
#ifndef UNICODE
					CopyMemory(nHeaderData.GetData(), (LPCTSTR)szHeader[0], nHeaderData.GetSize());
#else
					WideCharToMultiByte(CP_ACP, 0, szHeader[0], szHeader[0].GetLength(), (LPSTR)nHeaderData.GetData(), (INT)nHeaderData.GetSize(), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
					if (!WriteFile(cDerivedFile.m_hFile, nHeaderData.GetData(), (DWORD)nHeaderData.GetSize(), &cbDerivedFile, (LPOVERLAPPED)NULL))
					{
						ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_SAVE));
						cDerivedFile.Close();
						cDerivedFile.Remove(szFileName);
						return FALSE;
					}
				}
				else
				{
					ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_MEMORY));
					cDerivedFile.Close();
					cDerivedFile.Remove(szFileName);
					return FALSE;
				}
			}
		}
		for (nParameter = 0, nParameters = (INT)pDatabase->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
			{
				if (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_NATURE_DERIVED | TMPARAMETER_NATURE_DERIVED_OL | TMPARAMETER_NATURE_DERIVED_SPEL | TMPARAMETER_NATURE_DERIVED_HARDCODED))
				{
					for (szExpression = pDatabaseTMParameter->GetDerivationExpression(); nParameter > 0; )
					{
						szExpression = CString(CR) + CString(EOL) + szExpression;
						break;
					}
					nHeaderData.SetSize(szExpression.GetLength());
					if (nHeaderData.GetSize() == szExpression.GetLength())
					{
#ifndef UNICODE
						CopyMemory(nHeaderData.GetData(), (LPCTSTR)szExpression, nHeaderData.GetSize());
#else
						WideCharToMultiByte(CP_ACP, 0, szExpression, szExpression.GetLength(), (LPSTR)nHeaderData.GetData(), (INT)nHeaderData.GetSize(), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
						if (!WriteFile(cDerivedFile.m_hFile, nHeaderData.GetData(), (DWORD)nHeaderData.GetSize(), &cbDerivedFile, (LPOVERLAPPED)NULL))
						{
							ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_SAVE));
							break;
						}
					}
					else
					{
						ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_MEMORY));
						break;
					}
				}
			}
		}
		if (nParameter < nParameters)
		{
			cDerivedFile.Close();
			cDerivedFile.Remove(szFileName);
			return FALSE;
		}
		cDerivedFile.Close();
		return TRUE;
	}
	ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_SAVE));
	return FALSE;
}

BOOL CSourceDatabaseCompileThread::LoadDerivedParametersFile(CONST CBinaryDatabase *pDatabase, CString &szData)
{
	DWORD  cbDerivedFile;
	CFileEx  cDerivedFile;
	CByteArray  nDerivedData;

	if (cDerivedFile.Open(GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_SOURCENAME)), CFile::modeRead))
	{
		nDerivedData.SetSize((cbDerivedFile = (DWORD)cDerivedFile.GetLength()));
		if (cbDerivedFile == (DWORD)nDerivedData.GetSize())
		{
			if (ReadFile(cDerivedFile.m_hFile, nDerivedData.GetData(), cbDerivedFile, &cbDerivedFile, (LPOVERLAPPED)NULL))
			{
#ifndef UNICODE
				CopyMemory(szData.GetBufferSetLength((INT)nDerivedData.GetSize()), nDerivedData.GetData(), nDerivedData.GetSize());
				szData.ReleaseBuffer();
#else
				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)nDerivedData.GetData(), (INT)nDerivedData.GetSize(), szData.GetBufferSetLength((INT)nDerivedData.GetSize()), (INT)nDerivedData.GetSize());
				szData.ReleaseBuffer();
#endif
				cDerivedFile.Close();
				return TRUE;
			}
		}
		cDerivedFile.Close();
	}
	ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_LOAD));
	szData.Empty();
	return FALSE;
}

BOOL CSourceDatabaseCompileThread::TranslateDerivedParametersFile(CONST CBinaryDatabase *pDatabase, LPCTSTR pszData, CString &szData, CStringArray &szGlobalParameters, CStringArray &szLocalParameters, CStringArray &szStaticParameters, CStringArray &szVolatileParameters, CStringArray &szPastProcedures, CStringArray &szPastProcedureParameters, CStringArray &szPastParameters, CUIntArray &nPastSamples)
{
	INT  nIndex;
	INT  nPos[10];
	INT  nDiff[2];
	INT  nLevels;
	INT  nErrors;
	INT  nSamples;
	INT  nPacket;
	INT  nPackets;
	INT  nProcedure;
	INT  nProcedures;
	INT  nParameter;
	INT  nParameters;
	BOOL  bStatic;
	TCHAR  szChar;
	LPCTSTR  pPos;
	CString  szError;
	CString  szMacro;
	CString  szDigit[2];
	CString  szProcedure;
	CString  szParameter;
	CString  szSeparator;
	CString  szArgument[2];
	CStringTools  cStringTools;
	CDatabaseTMPacket  *pDatabaseTMPacket;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CUIntArray  nSourceCodeLines;
	CUIntArray  nTriggerRefs;

	for (CalculateDerivedParameterFileLines(pszData, nSourceCodeLines), szData = pszData, szGlobalParameters.RemoveAll(), szLocalParameters.RemoveAll(), szStaticParameters.RemoveAll(), szVolatileParameters.RemoveAll(), szPastProcedures.RemoveAll(), szPastProcedureParameters.RemoveAll(), szPastParameters.RemoveAll(), nPastSamples.RemoveAll(), m_szLines.RemoveAll(), nPos[0] = nPos[1] = 0, nDiff[0] = nDiff[1] = 0, nLevels = 0, nErrors = 0; TRUE; )
	{
		nPos[2] = szData.Mid(nPos[1]).Find(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_BEGINCOMMENTS));
		nPos[3] = szData.Mid(nPos[1]).Find(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_ENDCOMMENTS));
		if (nPos[2] >= 0 && (nPos[2] < nPos[3] || nPos[3] < 0))
		{
			nPos[0] = (!nLevels) ? (nPos[1] + nPos[2]) : nPos[0];
			nPos[1] += nPos[2] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_BEGINCOMMENTS));
			nLevels++;
			continue;
		}
		if (nPos[3] >= 0 && nLevels > 0)
		{
			szData = (--nLevels == 0) ? (szData.Left(nPos[0]) + CString(SPACE[0], nPos[1] + nPos[3] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_ENDCOMMENTS)) - nPos[0]) + szData.Mid(nPos[1] + nPos[3] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_ENDCOMMENTS)))) : szData;
			nPos[1] += nPos[3] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_ENDCOMMENTS));
			continue;
		}
		if ((nPos[3] < 0 && nLevels > 0) || (nPos[3] >= 0 && !nLevels))
		{
			szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_MISMATCHINGCOMMENTSYMBOL), DetermineDerivedParameterFileLine(nSourceCodeLines, (nPos[3] < 0 && nLevels > 0) ? (lstrlen(pszData) - 1) : nPos[3]), DetermineDerivedParameterFileColumn(nSourceCodeLines, (nPos[3] < 0 && nLevels > 0) ? (lstrlen(pszData) - 1) : nPos[3]));
			ShowError(szError);
			nErrors++;
		}
		break;
	}
	for (nPos[0] = 0; TRUE; )
	{
		if ((nPos[1] = szData.Mid(nPos[0]).Find(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_LINECOMMENTS))) >= 0)
		{
			if ((nPos[2] = szData.Mid(nPos[0] + nPos[1]).Find(CString(CR) + CString(EOL))) >= 0)
			{
				szData = szData.Left(nPos[0] + nPos[1]) + CString(SPACE[0], nPos[2]) + szData.Mid(nPos[0] + nPos[1] + nPos[2]);
				nPos[0] += nPos[1] + nPos[2] + 2;
				continue;
			}
			if ((nPos[2] = szData.Mid(nPos[0] + nPos[1]).Find(CString(CR))) >= 0)
			{
				szData = szData.Left(nPos[0] + nPos[1]) + CString(SPACE[0], nPos[2]) + szData.Mid(nPos[0] + nPos[1] + nPos[2]);
				nPos[0] += nPos[1] + nPos[2] + 1;
				continue;
			}
			if ((nPos[2] = szData.Mid(nPos[0] + nPos[1]).Find(CString(EOL))) >= 0)
			{
				szData = szData.Left(nPos[0] + nPos[1]) + CString(SPACE[0], nPos[2]) + szData.Mid(nPos[0] + nPos[1] + nPos[2]);
				nPos[0] += nPos[1] + nPos[2] + 1;
				continue;
			}
			szData = szData.Left(nPos[0] + nPos[1]);
		}
		break;
	}
	for (nPos[0] = 0; (nPos[1] = ((pPos = FindDerivedParameterLanguageSourceCodeKeyword((LPCTSTR)szData, nPos[0], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE)))) ? (INT)(pPos - (LPCTSTR)szData - nPos[0]) : -1) >= 0; )
	{
		nPos[2] = ((pPos = FindDerivedParameterLanguageSourceCodeKeyword((LPCTSTR)szData, nPos[0], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS)))) ? (INT)(pPos - (LPCTSTR)szData - nPos[0]) : -1;
		nPos[3] = ((pPos = FindDerivedParameterLanguageSourceCodeKeyword((LPCTSTR)szData, nPos[0], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN)))) ? (INT)(pPos - (LPCTSTR)szData - nPos[0]) : -1;
		nPos[4] = ((pPos = FindDerivedParameterLanguageSourceCodeKeyword((LPCTSTR)szData, nPos[0], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_END)))) ? (INT)(pPos - (LPCTSTR)szData - nPos[0]) : -1;
		nPos[5] = ((pPos = FindDerivedParameterLanguageSourceCodeKeyword((LPCTSTR)szData, nPos[0] + nPos[1] + 1, STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE)))) ? (INT)(pPos - (LPCTSTR)szData - nPos[0]) : -1;
		if (nPos[1] < nPos[2] || nPos[2] < 0)
		{
			if (nPos[1] < nPos[3] && (nPos[2] < 0 || nPos[2] > nPos[4] || nPos[2] < nPos[3]))
			{
				if (nPos[1] < nPos[4] && (nPos[2] < 0 || nPos[2] > nPos[4] || nPos[2] < nPos[4]) && nPos[3] < nPos[4] && (nPos[4] < nPos[5] || nPos[5] < 0))
				{
					for (nPos[5] = nPos[0] + nPos[1] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE)), szProcedure.Empty(); (nPos[2] < 0 || nPos[5] < nPos[0] + nPos[2]) && nPos[5] < nPos[0] + nPos[3]; nPos[5]++)
					{
						if ((szChar = szData.GetAt(nPos[5])) != SPACE[0] && szChar != TAB  &&  szChar != CR  &&  szChar != EOL)
						{
							szProcedure += szData.GetAt(nPos[5]);
							continue;
						}
						if (!szProcedure.IsEmpty())
						{
							for (CollectDerivedParameter(szProcedure, TRUE, szGlobalParameters); !CollectDerivedParameter(szProcedure + EOL + szProcedure, (pDatabase->GetTMParameters()->Find(szProcedure) >= 0) ? TRUE : FALSE, szLocalParameters); )
							{
								szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_DUPLICATEPROCEDURE), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1] - szProcedure.GetLength()), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1] - szProcedure.GetLength()));
								ShowError(szError);
								nErrors++;
								break;
							}
							break;
						}
					}
					if (pDatabase->GetTMParameters()->Find(szProcedure) < 0)
					{
						szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALPROCEDURENAME), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1] - szProcedure.GetLength()), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1] - szProcedure.GetLength()), (LPCTSTR)szProcedure);
						ShowError(szError);
						nErrors++;
					}
					for (nPos[5] = nPos[0] + nPos[1] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE)); (nPos[2] < 0 || nPos[5] < nPos[0] + nPos[2]) && nPos[5] < nPos[0] + nPos[3]; nPos[5]++)
					{
						if ((szChar = szData.GetAt(nPos[5])) != SPACE[0] && szChar != TAB  &&  szChar != CR  &&  szChar != EOL) break;
						continue;
					}
					for (nPos[5] += szProcedure.GetLength(); (nPos[2] < 0 || nPos[5] < nPos[0] + nPos[2]) && nPos[5] < nPos[0] + nPos[3]; nPos[5]++)
					{
						if ((szChar = szData.GetAt(nPos[5])) != SPACE[0] && szChar != TAB  &&  szChar != CR  &&  szChar != EOL) break;
						continue;
					}
					if (!_tcsncmp((LPCTSTR)szData + nPos[5], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS))) || !_tcsncmp((LPCTSTR)szData + nPos[5], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN))))
					{
						for (nPos[5] = nPos[0] + nPos[2] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS)), szSeparator.Empty(); nPos[2] >= 0 && nPos[2] < nPos[3] && nPos[5] < nPos[0] + nPos[3]; )
						{
							while ((szChar = szData.GetAt(nPos[5])) == SPACE[0] || szChar == TAB || szChar == CR || szChar == EOL)
							{
								if (++nPos[5] >= nPos[0] + nPos[3]) break;
								continue;
							}
							if (szData.GetAt(nPos[5]) != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_TERMINATOR))
							{
								for (nPos[6] = nPos[5], szParameter.Empty(), bStatic = FALSE; nPos[6] < nPos[0] + nPos[3] && ((!bStatic && szParameter.GetLength() <= max(GetDatabase()->GetTMParameterTagLength(), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_STATIC)) + 1)) || (bStatic && szParameter.GetLength() <= GetDatabase()->GetTMParameterTagLength())); nPos[6]++)
								{
									if (szData.Mid(nPos[5], nPos[6] - nPos[5] + 1) == STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_STATIC) && !bStatic)
									{
										if ((szChar = szData.GetAt(++nPos[6])) == SPACE[0] || szChar == TAB || szChar == CR || szChar == EOL)
										{
											for (szParameter.Empty(), bStatic = TRUE; nPos[6] < nPos[0] + nPos[3]; nPos[6]++)
											{
												if ((szChar = szData.GetAt(++nPos[6])) == SPACE[0]) continue;
												if (szChar == TAB || szChar == CR || szChar == EOL) continue;
												break;
											}
										}
									}
									if (GetDatabase()->CheckTMParameterTag(szParameter + szData.GetAt(nPos[6])))
									{
										szParameter += szData.GetAt(nPos[6]);
										continue;
									}
									break;
								}
								if (pDatabase->GetTMParameters()->Find(szParameter) >= 0)
								{
									for (CollectDerivedParameter(szParameter, TRUE, szGlobalParameters); !CollectDerivedParameter(szProcedure + EOL + szParameter, TRUE, szLocalParameters); )
									{
										szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_DUPLICATEPARAMETER), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
										ShowError(szError);
										nErrors++;
										break;
									}
									for (nParameter = 0, nParameters = (INT)szStaticParameters.GetSize(); nParameter < nParameters; nParameter++)
									{
										if (szStaticParameters.GetAt(nParameter) == szProcedure + EOL + szParameter) break;
										continue;
									}
									if (nParameter == nParameters  &&  bStatic) szStaticParameters.Add(szProcedure + EOL + szParameter);
									if (nParameter < nParameters  &&  !bStatic) szStaticParameters.RemoveAt(nParameter);
								}
								else
								{
									szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALPARAMETER), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
									ShowError(szError);
									nErrors++;
								}
								for (nPos[5] = nPos[6]; (szChar = szData.GetAt(nPos[5])) == SPACE[0] || szChar == TAB || szChar == CR || szChar == EOL; )
								{
									if (++nPos[5] >= nPos[0] + nPos[3]) break;
									continue;
								}
								if (szChar != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SEPARATOR) && szChar != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_TERMINATOR))
								{
									szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_MISSINGSEPARATORSYMBOL), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
									ShowError(szError);
									nErrors++;
									break;
								}
								nPos[5] = (szChar == STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SEPARATOR)) ? (nPos[5] + 1) : nPos[5];
								szSeparator = (szChar == STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SEPARATOR)) ? STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SEPARATOR) : EMPTYSTRING;
								continue;
							}
							else
							{
								if (!szSeparator.IsEmpty())
								{
									szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALPARAMETER), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
									ShowError(szError);
									nErrors++;
								}
							}
							break;
						}
						for (nPos[5] = (szData.GetAt(nPos[5]) == STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_TERMINATOR)) ? (nPos[5] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_TERMINATOR))) : nPos[5]; nPos[2] >= 0 && nPos[2] < nPos[3] && nPos[5] < nPos[0] + nPos[3]; nPos[5]++)
						{
							if ((szChar = szData.GetAt(nPos[5])) != SPACE[0] && szChar != TAB  &&  szChar != CR  &&  szChar != EOL) break;
							continue;
						}
						if (!_tcsncmp((LPCTSTR)szData + nPos[5], STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_VOLATILE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_VOLATILE))))
						{
							for (nPos[5] = nPos[5] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_VOLATILE)); nPos[2] >= 0 && nPos[2] < nPos[3] && nPos[5] < nPos[0] + nPos[3]; )
							{
								while ((szChar = szData.GetAt(nPos[5])) == SPACE[0] || szChar == TAB || szChar == CR || szChar == EOL)
								{
									if (++nPos[5] >= nPos[0] + nPos[3]) break;
									continue;
								}
								if (szData.GetAt(nPos[5]) != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_TERMINATOR))
								{
									for (nPos[6] = nPos[5], szParameter.Empty(); nPos[6] < nPos[0] + nPos[3] && nPos[6] - nPos[5] <= GetDatabase()->GetTMParameterTagLength(); nPos[6]++)
									{
										if (GetDatabase()->CheckTMParameterTag(szParameter + szData.GetAt(nPos[6])))
										{
											szParameter += szData.GetAt(nPos[6]);
											continue;
										}
										break;
									}
									if (pDatabase->GetTMParameters()->Find(szParameter) >= 0)
									{
										if (FindDerivedParameter(szLocalParameters, szProcedure + EOL + szParameter) >= 0)
										{
											if (!CollectDerivedParameter(szProcedure + EOL + szParameter, TRUE, szVolatileParameters))
											{
												szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_DUPLICATEPARAMETER), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
												ShowError(szError);
												nErrors++;
											}
										}
										else
										{
											szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALPARAMETER), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
											ShowError(szError);
											nErrors++;
										}
									}
									else
									{
										szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALPARAMETER), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
										ShowError(szError);
										nErrors++;
									}
									for (nPos[5] = nPos[6]; (szChar = szData.GetAt(nPos[5])) == SPACE[0] || szChar == TAB || szChar == CR || szChar == EOL; )
									{
										if (++nPos[5] >= nPos[0] + nPos[3]) break;
										continue;
									}
									if (szChar != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SEPARATOR) && szChar != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_TERMINATOR))
									{
										szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_MISSINGSEPARATORSYMBOL), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
										ShowError(szError);
										nErrors++;
										break;
									}
									nPos[5] = (szChar == STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SEPARATOR)) ? (nPos[5] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SEPARATOR))) : nPos[5];
									continue;
								}
								break;
							}
						}
						for (nProcedure = 0, nProcedures = MAXDERIVEDPARAMETERLANGUAGEPROCEDURE - MINDERIVEDPARAMETERLANGUAGEPROCEDURE, szData.SetAt(nPos[0] + nPos[4], EOS); nProcedure <= nProcedures; nProcedure++)
						{
							for (nPos[6] = nPos[0] + nPos[3]; nPos[6] < nPos[0] + nPos[4]; nPos[6] = nPos[7] + lstrlen(STRING(MINDERIVEDPARAMETERLANGUAGEPROCEDURE + nProcedure)))
							{
								if ((nPos[7] = ((pPos = _tcsstr((LPCTSTR)szData + nPos[6], STRING(MINDERIVEDPARAMETERLANGUAGEPROCEDURE + nProcedure)))) ? (INT)(pPos - (LPCTSTR)szData) : -1) >= 0)
								{
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITTAG), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITTAG))))
									{
										szData = szData.Left(nPos[7]) + STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTMUNITTAG) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITTAG)));
										nDiff[0] = lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTMUNITTAG)) - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITTAG));
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITTIME), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITTIME))))
									{
										szData = szData.Left(nPos[7]) + STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTMUNITTIME) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITTIME)));
										nDiff[0] = lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTMUNITTIME)) - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITTIME));
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITID), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITID))))
									{
										szData = szData.Left(nPos[7]) + STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTMUNITID) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITID)));
										nDiff[0] = lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTMUNITID)) - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITID));
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITDATA), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITDATA))))
									{
										szData = szData.Left(nPos[7]) + STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTMUNITDATA) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITDATA)));
										nDiff[0] = lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTMUNITDATA)) - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITDATA));
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITQUALITY), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITQUALITY))))
									{
										szData = szData.Left(nPos[7]) + STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTMUNITQUALITY) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITQUALITY)));
										nDiff[0] = lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTMUNITQUALITY)) - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTMUNITQUALITY));
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTOTALTMBANDWIDTH), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTOTALTMBANDWIDTH))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME))))
									{
										if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt((nIndex = pDatabase->GetTMParameters()->Find(szProcedure)))))
										{
											for (nPacket = 0, nPackets = (INT)pDatabase->GetTMPackets()->GetSize(); nPacket < nPackets; nPacket = nPacket + 1)
											{
												if ((pDatabaseTMPacket = pDatabase->GetTMPackets()->GetAt(nPacket)) && pDatabaseTMPacket->GetTriggerRefs(nTriggerRefs) >= 0)
												{
													for (nParameter = 0, nParameters = (INT)nTriggerRefs.GetSize(); nParameter < nParameters; nParameter++)
													{
														if (nTriggerRefs.GetAt(nParameter) == nIndex) break;
														continue;
													}
													if (nParameter == nParameters)
													{
														nTriggerRefs.Add(nIndex);
														pDatabaseTMPacket->SetTriggerRefs(nTriggerRefs);
													}
												}
											}
										}
										for (nDiff[0] = 0; !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTOTALTMBANDWIDTH), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTOTALTMBANDWIDTH))); )
										{
											szData = szData.Left(nPos[7]) + STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTOTALTMBANDWIDTH) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTOTALTMBANDWIDTH)));
											nDiff[0] = lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETTOTALTMBANDWIDTH)) - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETTOTALTMBANDWIDTH));
											break;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH))))
										{
											szData = szData.Left(nPos[7]) + STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETAVAILABLETMBANDWIDTH) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH)));
											nDiff[0] = lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETAVAILABLETMBANDWIDTH)) - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLETMBANDWIDTH));
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH))))
										{
											szData = szData.Left(nPos[7]) + STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH)));
											nDiff[0] = lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH)) - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETMAXDIAGNOSTICTMBANDWIDTH));
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH))))
										{
											szData = szData.Left(nPos[7]) + STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH)));
											nDiff[0] = lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH)) - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETAVAILABLEDIAGNOSTICTMBANDWIDTH));
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME))))
										{
											szData = szData.Left(nPos[7]) + STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME) + szData.Mid(nPos[7] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME)));
											nDiff[0] = lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME)) - lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETLASTTMBANDWIDTHMEASUREMENTTIME));
										}
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									for (nPos[8] = nPos[7] + lstrlen(STRING(MINDERIVEDPARAMETERLANGUAGEPROCEDURE + nProcedure)); nPos[8] < nPos[0] + nPos[4]; nPos[8]++)
									{
										if ((szChar = szData.GetAt(nPos[8])) != SPACE[0] && szChar != TAB  &&  szChar != CR  &&  szChar != EOL) break;
										continue;
									}
									for (szMacro.Empty(), szArgument[0].Empty(); nPos[8] < nPos[0] + nPos[4] && szArgument[0].GetLength() < GetDatabase()->GetTMParameterTagLength(); nPos[8]++)
									{
										if (GetDatabase()->CheckTMParameterTag(szArgument[0] + szData.GetAt(nPos[8])))
										{
											szArgument[0] += szData.GetAt(nPos[8]);
											continue;
										}
										break;
									}
									if ((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(szArgument[0]))) && FindDerivedParameter(szLocalParameters, szProcedure + EOL + szArgument[0]) >= 0)
									{
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETVALUE))))
										{
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS))) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETFLOATVALUE) : EMPTYSTRING;
											szMacro = (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETSTRINGVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETNUMERICALVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETNUMERICALVALUE))))
										{
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETNUMERICALFLOATVALUE) : EMPTYSTRING;
											szMacro = (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETNUMERICALINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETNUMERICALUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_SETRAWVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_SETRAWVALUE))))
										{
											szMacro = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_SETRAWFLOATVALUE) : EMPTYSTRING;
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_SETRAWINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_SETRAWUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETRAWVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETRAWVALUE))))
										{
											szMacro = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETRAWFLOATVALUE) : EMPTYSTRING;
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETRAWINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETRAWUINTVALUE) : (LPCTSTR)szMacro;
										}
										for (; !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETVALUETIME), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETVALUETIME))); )
										{
											szMacro = STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETVALUETIME);
											break;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTVALUE))))
										{
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS))) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTFLOATVALUE) : EMPTYSTRING;
											szMacro = (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTSTRINGVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTNUMERICALVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTNUMERICALVALUE))))
										{
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALFLOATVALUE) : EMPTYSTRING;
											szMacro = (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTNUMERICALUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTRAWVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTRAWVALUE))))
										{
											szMacro = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWFLOATVALUE) : EMPTYSTRING;
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTRAWUINTVALUE) : (LPCTSTR)szMacro;
										}
										for (; !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTVALUETIME), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTVALUETIME))); )
										{
											szMacro = STRING(IDS_DERIVEDPARAMETERFILE_MACRO_GETPASTVALUETIME);
											break;
										}
										if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_CALCULATEVALUEAVERAGE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_CALCULATEVALUEAVERAGE))))
										{
											szMacro = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEFLOATVALUE) : EMPTYSTRING;
											szMacro = (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)) && !(pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEINTVALUE) : (LPCTSTR)szMacro;
											szMacro = (szMacro.IsEmpty()) ? STRING(IDS_DERIVEDPARAMETERFILE_MACRO_CALCULATEAVERAGEUINTVALUE) : (LPCTSTR)szMacro;
										}
										if (!szMacro.IsEmpty())
										{
											if (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTVALUE))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTNUMERICALVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTNUMERICALVALUE))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTRAWVALUE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTRAWVALUE))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTVALUETIME), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_GETPASTVALUETIME))) || !_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_CALCULATEVALUEAVERAGE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_CALCULATEVALUEAVERAGE))))
											{
												for (nPos[9] = nPos[8], szDigit[0] = cStringTools.ConvertUIntToString(0), szDigit[1] = cStringTools.ConvertUIntToString(10, 16); nPos[9] < nPos[0] + nPos[4] && !_istdigit(szData.GetAt(nPos[9])) && _tcsncmp((LPCTSTR)szData + nPos[9], STRING(IDS_CHARSET_HEXADECIMALNUMBERPREFIX), lstrlen(STRING(IDS_CHARSET_HEXADECIMALNUMBERPREFIX))); nPos[9]++);
												if (!_tcsncmp((LPCTSTR)szData + nPos[9], STRING(IDS_CHARSET_HEXADECIMALNUMBERPREFIX), lstrlen(STRING(IDS_CHARSET_HEXADECIMALNUMBERPREFIX))))
												{
													for (nPos[9] += lstrlen(STRING(IDS_CHARSET_HEXADECIMALNUMBERPREFIX)), nSamples = 0; nPos[9] < nPos[0] + nPos[4]; nPos[9]++)
													{
														if (_istdigit((szChar = szData.GetAt(nPos[9]))))
														{
															nSamples = 16 * nSamples + szChar - szDigit[0].GetAt(0);
															continue;
														}
														if (_istxdigit(szChar))
														{
															nSamples = 16 * nSamples + _totupper(szChar) - szDigit[1].GetAt(0) + 10;
															continue;
														}
														break;
													}
												}
												else
												{
													for (nSamples = 0; nPos[9] < nPos[0] + nPos[4]; nPos[9]++)
													{
														if (_istdigit((szChar = szData.GetAt(nPos[9]))))
														{
															nSamples = 10 * nSamples + szChar - szDigit[0].GetAt(0);
															continue;
														}
														break;
													}
												}
												if (!SetDerivedParameterPastSamples(szArgument[0], szPastParameters, nPastSamples, nSamples) || !SetDerivedParameterPastSamples(szProcedure, szArgument[0], szPastProcedures, szPastProcedureParameters, nSamples, (!_tcsncmp((LPCTSTR)szData + nPos[7], STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_CALCULATEVALUEAVERAGE), lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_MACRO_CALCULATEVALUEAVERAGE)))) ? TRUE : FALSE))
												{
													ShowError(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_GENERAL));
													nErrors++;
												}
											}
											szArgument[1].Format(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_PARAMETERARGUMENT), (LPCTSTR)szArgument[0]);
											szData = szData.Left(nPos[7]) + szMacro + szArgument[1] + szData.Mid(nPos[8]);
											nDiff[0] = nPos[7] + szMacro.GetLength() + szArgument[1].GetLength() - nPos[8];
											nDiff[1] -= nDiff[0];
											nPos[4] += nDiff[0];
											nPos[5] += nDiff[0];
											continue;
										}
										szArgument[1].Format(STRING(IDS_DERIVEDPARAMETERFILE_MACRO_PARAMETERARGUMENT), (LPCTSTR)szArgument[0]);
										szData = szData.Left(nPos[7] + lstrlen(STRING(MINDERIVEDPARAMETERLANGUAGEPROCEDURE + nProcedure))) + szArgument[1] + szData.Mid(nPos[8]);
										nDiff[0] = nPos[7] + lstrlen(STRING(MINDERIVEDPARAMETERLANGUAGEPROCEDURE + nProcedure)) + szArgument[1].GetLength() - nPos[8];
										nDiff[1] -= nDiff[0];
										nPos[4] += nDiff[0];
										nPos[5] += nDiff[0];
										continue;
									}
									szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALPARAMETER), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[8] + nDiff[1] - szArgument[0].GetLength()), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[8] + nDiff[1] - szArgument[0].GetLength()));
									ShowError(szError);
									nErrors++;
									continue;
								}
								break;
							}
						}
						szData.SetAt(nPos[0] + nPos[4], STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_END));
					}
					else
					{
						if (!szProcedure.IsEmpty())
						{
							szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALBODYKEYWORD), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[5] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[5] + nDiff[1]));
							ShowError(szError);
							nErrors++;
						}
					}
					nPos[0] += nPos[4] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_END));
					continue;
				}
				else
				{
					if (nPos[1] >= nPos[4] && nPos[4] >= 0)
					{
						szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALENDKEYWORD), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[0] + nPos[4] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[0] + nPos[4] + nDiff[1]));
						nPos[0] += nPos[1];
					}
					if (nPos[1] < nPos[4] && nPos[3] >= nPos[4])
					{
						szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_MISSINGBEGINKEYWORD), DetermineDerivedParameterFileLine(nSourceCodeLines, (nPos[2] < 0) ? (nPos[0] + nPos[1] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE)) + nDiff[1] + 1) : (nPos[0] + nPos[2] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS)) + nDiff[1] + 1)), DetermineDerivedParameterFileColumn(nSourceCodeLines, (nPos[2] < 0) ? (nPos[0] + nPos[1] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE)) + nDiff[1] + 1) : (nPos[0] + nPos[2] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS)) + nDiff[1] + 1)));
						nPos[0] += nPos[4] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_END));
					}
					if (nPos[4] >= nPos[5] && nPos[5] >= 0)
					{
						szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_MISSINGENDKEYWORD), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[0] + nPos[5] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[0] + nPos[5] + nDiff[1]));
						nPos[0] += nPos[5];
					}
					if (nPos[4] < 0)
					{
						szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_MISSINGENDKEYWORD), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[0] + nPos[3] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN)) + nDiff[1] + 1), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[0] + nPos[3] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN)) + nDiff[1] + 1));
						nPos[0] += nPos[3] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_BEGIN));
					}
				}
			}
			else
			{
				if (nPos[1] >= nPos[3] && nPos[3] >= 0)
				{
					szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALBEGINKEYWORD), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[0] + nPos[3] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[0] + nPos[3] + nDiff[1]));
					nPos[0] += nPos[1];
				}
				else
				{
					szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_MISSINGBEGINKEYWORD), DetermineDerivedParameterFileLine(nSourceCodeLines, (nPos[2] < 0 || nPos[2] >= nPos[4]) ? (nPos[0] + nPos[1] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE)) + nDiff[1] + 1) : (nPos[0] + nPos[2] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS)) + nDiff[1] + 1)), DetermineDerivedParameterFileColumn(nSourceCodeLines, (nPos[2] < 0 || nPos[2] >= nPos[4]) ? (nPos[0] + nPos[1] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE)) + nDiff[1] + 1) : (nPos[0] + nPos[2] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS)) + nDiff[1] + 1)));
					nPos[0] += (nPos[2] < 0 || nPos[2] >= nPos[4]) ? (nPos[1] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PROCEDURE))) : (nPos[2] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_PARAMETERS)));
					nPos[0] = (nPos[1] < nPos[4]) ? (nPos[0] + nPos[4] + lstrlen(STRING(IDS_DERIVEDPARAMETERLANGUAGE_KEYWORD_END))) : nPos[0];
				}
			}
		}
		else
		{
			szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_ILLEGALPARAMETERSKEYWORD), DetermineDerivedParameterFileLine(nSourceCodeLines, nPos[0] + nPos[2] + nDiff[1]), DetermineDerivedParameterFileColumn(nSourceCodeLines, nPos[0] + nPos[2] + nDiff[1]));
			nPos[0] += nPos[1];
		}
		ShowError(szError);
		nErrors++;
		continue;
	}
	return((!nErrors) ? TRUE : FALSE);
}

VOID CSourceDatabaseCompileThread::CalculateDerivedParameterFileLines(LPCTSTR pszData, CUIntArray &nLines) CONST
{
	INT  nPos;
	INT  cbData;
	UINT  nLine;
	LPCTSTR  pPos;

	for (nLine = 1, nLines.SetAtGrow(0, (nPos = 0)), nLines.SetSize(1), cbData = lstrlen(pszData); nPos < cbData; nLine++)
	{
		if ((pPos = _tcsstr(&pszData[nPos], CString(CR) + CString(EOL))))
		{
			nLines.InsertAt(nLine, (nPos = (INT)(pPos - pszData) + 2));
			continue;
		}
		if ((pPos = _tcsstr(&pszData[nPos], CString(CR))))
		{
			nLines.InsertAt(nLine, (nPos = (INT)(pPos - pszData) + 1));
			continue;
		}
		if ((pPos = _tcsstr(&pszData[nPos], CString(EOL))))
		{
			nLines.InsertAt(nLine, (nPos = (INT)(pPos - pszData) + 1));
			continue;
		}
		break;
	}
}

UINT CSourceDatabaseCompileThread::DetermineDerivedParameterFileLine(CONST CUIntArray &nLines, INT nPos) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)nLines.GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if (nLines.GetAt(nIndex) <= (UINT)nPos && (nIndex == nLines.GetUpperBound() || nLines.GetAt(nIndex + 1) > (UINT)nPos)) break;
		if (nLines.GetAt(nIndex) > (UINT)nPos)
		{
			nMaxIndex = nIndex;
			continue;
		}
		nMinIndex = nIndex + 1;
	}
	return((nIndex < nLines.GetSize() && nLines.GetAt(nIndex) <= (UINT)nPos && (nIndex == nLines.GetUpperBound() || nLines.GetAt(nIndex + 1) >(UINT) nPos)) ? (nIndex + 1) : -1);
}

UINT CSourceDatabaseCompileThread::DetermineDerivedParameterFileColumn(CONST CUIntArray &nLines, INT nPos) CONST
{
	UINT  nLine;
	UINT  nColumn;

	if ((nLine = DetermineDerivedParameterFileLine(nLines, nPos)) > 0 && nLine <= (UINT)nLines.GetSize())
	{
		nColumn = nPos - nLines.GetAt(nLine - 1) + 1;
		return nColumn;
	}
	return -1;
}

BOOL CSourceDatabaseCompileThread::ConvertDerivedParameterFileLineToData(LPCTSTR pszText, CByteArray &nData) CONST
{
#ifndef UNICODE
	nData.SetSize(strlen(pszText));
	if (nData.GetSize() == strlen(pszText))
	{
		CopyMemory(nData.GetData(), pszText, strlen(pszText));
		return TRUE;
	}
#else
	nData.SetSize(lstrlen(pszText));
	if (nData.GetSize() == lstrlen(pszText))
	{
		WideCharToMultiByte(CP_ACP, 0, pszText, lstrlen(pszText), (LPSTR)nData.GetData(), (INT)nData.GetSize(), (LPCSTR)NULL, (LPBOOL)NULL);
		return TRUE;
	}
#endif
	return FALSE;
}

BOOL CSourceDatabaseCompileThread::CollectDerivedParameter(LPCTSTR pszParameter, BOOL bParameter, CStringArray &szParameters) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)szParameters.GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if (szParameters.GetAt(nIndex) < pszParameter)
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	if (nIndex <= szParameters.GetSize() && (!szParameters.GetSize() || (szParameters.GetAt(max(nIndex - 1, 0)) != pszParameter  &&  szParameters.GetAt(min(nIndex, szParameters.GetUpperBound())) != pszParameter  &&  lstrlen(pszParameter) > 0)))
	{
		if (bParameter) szParameters.InsertAt(nIndex, pszParameter);
		return TRUE;
	}
	return FALSE;
}

BOOL CSourceDatabaseCompileThread::ExamineDerivedParameter(CONST CBinaryDatabase *pDatabase, LPCTSTR pszParameter)
{
	INT  nPos;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	return(((pDatabaseTMParameter = pDatabase->GetTMParameters()->GetAt(pDatabase->GetTMParameters()->Find(pszParameter)))) ? (((nPos = pDatabaseTMParameter->GetDerivationExpression().Find(pszParameter)) >= 0 && pDatabaseTMParameter->GetDerivationExpression().Mid(nPos + pDatabaseTMParameter->GetTag().GetLength()).Find(pszParameter) >= 0) ? TRUE : FALSE) : FALSE);
}

INT CSourceDatabaseCompileThread::FindDerivedParameter(CONST CStringArray &szParameters, LPCTSTR pszParameter, BOOL bScope) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;
	CString  szParameter;

	for (nMinIndex = 0, nMaxIndex = (INT)szParameters.GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2, szParameter = (!_tcsstr(pszParameter, CString(EOL)) && bScope) ? (pszParameter + CString(EOL)) : pszParameter; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if (szParameters.GetAt(nIndex).Left(szParameter.GetLength()) < szParameter)
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	return((nIndex < szParameters.GetSize() && szParameters.GetAt(nIndex).Left(szParameter.GetLength()) == szParameter) ? nIndex : -1);
}

BOOL CSourceDatabaseCompileThread::SetDerivedParameterPastSamples(LPCTSTR pszProcedure, LPCTSTR pszParameter, CStringArray &szPastProcedures, CStringArray &szPastProcedureParameters, INT nSamples, BOOL bAll) CONST
{
	INT  nPos;
	INT  nIndex;
	INT  nSample;
	CString  szSample;
	CString  szSamples[2];
	CStringTools  cStringTools;

	if ((nIndex = FindDerivedParameterPastSamples(pszProcedure, szPastProcedures)) >= 0)
	{
		if ((nPos = (szSamples[0] = szPastProcedureParameters.GetAt(nIndex)).Find(pszParameter)) >= 0)
		{
			for (nPos += lstrlen(pszParameter), nSample = 1; nPos < szSamples[0].GetLength(); nPos++)
			{
				for (; szSamples[0].GetAt(nPos) == SPACE[0]; nPos++);
				if (!bAll && (nSamples < _ttoi(szSamples[0].Mid(nPos)) || szSamples[0].GetAt(nPos) == TAB))
				{
					szSample = cStringTools.ConvertIntToString(nSamples);
					szSamples[1] = szSamples[0].Left(nPos) + szSample;
					szSamples[1] += SPACE;
					szSamples[0] = szSamples[1] + szSamples[0].Mid(nPos);
					break;
				}
				if (bAll && (nSample < _ttoi(szSamples[0].Mid(nPos)) || szSamples[0].GetAt(nPos) == TAB))
				{
					szSample = cStringTools.ConvertIntToString(nSample);
					szSamples[1] = szSamples[0].Left(nPos) + szSample;
					szSamples[1] += SPACE;
					szSamples[0] = szSamples[1] + szSamples[0].Mid(nPos);
					if ((nSample = nSample + 1) <= nSamples)
					{
						nPos += szSample.GetLength();
						continue;
					}
					break;
				}
				for (; _istdigit(szSamples[0].GetAt(nPos)); nPos++);
				nSample = (bAll) ? (nSample + 1) : nSample;
			}
			szPastProcedureParameters.SetAt(nIndex, szSamples[0]);
			return TRUE;
		}
	}
	for (nSample = 1, szSamples[0] += pszParameter; bAll && nSample < nSamples; nSample++)
	{
		szSample = cStringTools.ConvertIntToString(nSample);
		szSamples[0] += SPACE;
		szSamples[0] += szSample;
	}
	szSample = cStringTools.ConvertIntToString(nSamples);
	szSamples[0] += SPACE + szSample;
	szSamples[0] += SPACE + CString(TAB);
	if ((nIndex = FindDerivedParameterPastSamples(pszProcedure, szPastProcedures)) < 0)
	{
		if ((nIndex = FindDerivedParameterPastSamples(pszProcedure, szPastProcedures, TRUE)) >= 0)
		{
			szPastProcedureParameters.InsertAt(nIndex, szSamples[0]);
			szPastProcedures.InsertAt(nIndex, pszProcedure);
			return TRUE;
		}
		return FALSE;
	}
	szPastProcedureParameters.SetAt(nIndex, szSamples[0]);
	return TRUE;
}
BOOL CSourceDatabaseCompileThread::SetDerivedParameterPastSamples(LPCTSTR pszArgument, CStringArray &szPastParameters, CUIntArray &nPastSamples, INT nSamples) CONST
{
	INT  nIndex;

	if ((nIndex = FindDerivedParameterPastSamples(pszArgument, szPastParameters)) >= 0)
	{
		nPastSamples.SetAt(nIndex, max((INT)nPastSamples.GetAt(nIndex), nSamples));
		return TRUE;
	}
	if ((nIndex = FindDerivedParameterPastSamples(pszArgument, szPastParameters, TRUE)) >= 0)
	{
		szPastParameters.InsertAt(nIndex, pszArgument);
		nPastSamples.InsertAt(nIndex, nSamples);
		return TRUE;
	}
	return FALSE;
}

INT CSourceDatabaseCompileThread::GetDerivedParameterPastSamples(LPCTSTR pszProcedure, LPCTSTR pszParameter, CONST CStringArray &szPastProcedures, CONST CStringArray &szPastProcedureParameters, CUIntArray &nPastSamples) CONST
{
	INT  nPos;
	INT  nIndex;
	CString  szSamples;

	if ((nIndex = FindDerivedParameterPastSamples(pszProcedure, szPastProcedures)) >= 0)
	{
		if ((nPos = (szSamples = szPastProcedureParameters.GetAt(nIndex)).Find(pszParameter)) >= 0)
		{
			for (nPos += lstrlen(pszParameter), nPastSamples.RemoveAll(); szSamples.GetAt(nPos) != TAB; nPos++)
			{
				for (; szSamples.GetAt(nPos) == SPACE[0]; nPos++);
				nPastSamples.Add(_ttoi(szSamples.Mid(nPos)));
				for (; _istdigit(szSamples.GetAt(nPos)); nPos++);
			}
			return((INT)nPastSamples.GetSize());
		}
	}
	return -1;
}
INT CSourceDatabaseCompileThread::GetDerivedParameterPastSamples(LPCTSTR pszArgument, CONST CStringArray &szPastParameters, CONST CUIntArray &nPastSamples) CONST
{
	INT  nIndex;

	return(((nIndex = FindDerivedParameterPastSamples(pszArgument, szPastParameters)) >= 0) ? (INT)nPastSamples.GetAt(nIndex) : -1);
}

INT CSourceDatabaseCompileThread::FindDerivedParameterPastSamples(LPCTSTR pszProcedureOrArgument, CONST CStringArray &szPastParameters, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)szPastParameters.GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if (szPastParameters.GetAt(nIndex) < pszProcedureOrArgument)
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	return(((!bInsert  &&  nIndex < szPastParameters.GetSize() && szPastParameters.GetAt(nIndex) == pszProcedureOrArgument) || (bInsert  &&  nIndex <= szPastParameters.GetSize() && (!szPastParameters.GetSize() || (szPastParameters.GetAt(max(nIndex - 1, 0)) != pszProcedureOrArgument  &&  szPastParameters.GetAt(min(nIndex, szPastParameters.GetUpperBound())) != pszProcedureOrArgument  &&  lstrlen(pszProcedureOrArgument) > 0)))) ? nIndex : -1);
}

CString CSourceDatabaseCompileThread::FormatDerivedParameterCode(LPCTSTR pszCode, INT nBlockLevel) CONST
{
	INT  nLine;
	INT  nLines;
	INT  nPos[2];
	INT  nLength;
	CString  szCode;
	CStringArray  szLines;

	for (szCode = pszCode; nBlockLevel >= 0; )
	{
		while (!szCode.IsEmpty())
		{
			nPos[0] = szCode.Find(CR);
			nPos[1] = szCode.Find(EOL);
			szLines.Add(((nLength = min(nPos[0], nPos[1])) >= 0) ? (CString(SPACE[0], 2 * (nBlockLevel + 1)) + szCode.Left(nLength)) : (((nLength = max(nPos[0], nPos[1])) >= 0) ? (CString(SPACE[0], 2 * (nBlockLevel + 1)) + szCode.Left(nLength)) : (CString(SPACE[0], 2 * (nBlockLevel + 1)) + szCode)));
			szCode = (nPos[0] >= 0 && nPos[1] == nPos[0] + 1) ? szCode.Mid(nPos[1] + 1) : (((nLength = min(nPos[0], nPos[1])) >= 0) ? szCode.Mid(nLength + 1) : ((nLength = max(nPos[0], nPos[1])) >= 0) ? szCode.Mid(nLength + 1) : EMPTYSTRING);
		}
		for (nLine = 0, nLines = (INT)szLines.GetSize(); nLine < nLines; nLine++)
		{
			szCode += (!szCode.IsEmpty()) ? (CString(CR) + EOL + szLines.GetAt(nLine)) : szLines.GetAt(nLine);
			continue;
		}
		break;
	}
	return szCode;
}

CString CSourceDatabaseCompileThread::GetDerivedParametersFileName(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFormat) CONST
{
	INT  nPos;
	INT  cbTitle;
	CString  szFileTitle;
	CString  szFileName[2];

	if (!GetFileTitle((szFileName[0] = pDatabase->GetFileName()), szFileTitle.GetBufferSetLength(cbTitle), (cbTitle = max(GetFileTitle((szFileName[0] = pDatabase->GetFileName()), (LPTSTR)NULL, 0), 0))))
	{
		for (nPos = szFileName[0].GetLength() - lstrlen(szFileTitle), szFileTitle.ReleaseBuffer(); nPos >= 0; nPos--)
		{
			if (!szFileName[0].Mid(nPos, lstrlen(szFileTitle)).CompareNoCase(szFileTitle)) break;
			continue;
		}
		for (; nPos >= 0; )
		{
			szFileName[1].Format(pszFormat, (LPCTSTR)(szFileName[0].Left(nPos) + pDatabase->GetName()));
			break;
		}
		return szFileName[1];
	}
	szFileTitle.ReleaseBuffer();
	return EMPTYSTRING;
}

BOOL CSourceDatabaseCompileThread::SecureDerivedParametersFile(LPCTSTR pszFileName) CONST
{
	CFileFindEx  cFileFind;
	CSecurityDescriptor  cSecurityDescriptor;

	if (cFileFind.FindFile(pszFileName) && !cFileFind.FindNextFile())
	{
		if (cSecurityDescriptor.SetRightsOfSystem(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfNetworkService(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfAdministrators(FILE_ALL_ACCESS) && (cSecurityDescriptor.SetRightsOfSystemOperators(FILE_GENERIC_READ | FILE_GENERIC_WRITE) || cSecurityDescriptor.SetRightsOfPowerUsers(FILE_GENERIC_READ | FILE_GENERIC_WRITE)) && cSecurityDescriptor.SetRightsOfAuthenticatedUsers(FILE_GENERIC_READ) && cSecurityDescriptor.SetRightsOfEveryone(FILE_GENERIC_READ) && CSecurity::SecureDirectory(cFileFind.GetRoot(), cSecurityDescriptor) && CSecurity::SecureFile(cFileFind.GetFilePath(), cSecurityDescriptor))
		{
			cFileFind.Close();
			return TRUE;
		}
		cFileFind.Close();
	}
	return FALSE;
}

CString CSourceDatabaseCompileThread::GetDerivedParametersCompilerFileName() CONST
{
	INT  nDrive;
	INT  nDrives;
	CString  szPlatForm;
	CString  szFileName[2];
	CString  szDirectory[2];
	CString  szOptions[3];
	CProfile  cProfile;
	CStringArray  szDrives;
	CLogicalDrives  cDrives;
	CCompileOptionsDialog  cCompileOptionsDialog;

	if (!cProfile.GetCompileOptions(szFileName[0], szFileName[1], szPlatForm, szDirectory[0], szDirectory[1], szOptions[0], szOptions[1], szOptions[2]))
	{
		for (nDrive = 0, nDrives = cDrives.EnumDrives(szDrives); nDrive < nDrives; nDrive = nDrive + 1)
		{
			if (GetDriveType(szDrives.GetAt(nDrive)) == DRIVE_FIXED || GetDriveType(szDrives.GetAt(nDrive)) == DRIVE_REMOTE)
			{
				if ((szFileName[0] = GetDerivedParametersCompilerFileName(szDrives.GetAt(nDrive))).GetLength() > 0) break;
				continue;
			}
		}
		return((cCompileOptionsDialog.DoModal(szFileName[0]) == IDOK) ? (LPCTSTR)szFileName[0] : EMPTYSTRING);
	}
	return szFileName[0];
}
CString CSourceDatabaseCompileThread::GetDerivedParametersCompilerFileName(LPCTSTR pszDirectory) CONST
{
	CString  szFileName;
	CFileFindEx  cFileFind[2];

	if (cFileFind[0].FindFile(CString(pszDirectory) + STRING(IDS_FILENAME_ALL)))
	{
		while (cFileFind[0].FindNextFile())
		{
			if (cFileFind[0].IsDirectory() && !cFileFind[0].IsDots())
			{
				if ((szFileName = GetDerivedParametersCompilerFileName(cFileFind[0].GetFilePath())).GetLength() > 0) break;
				continue;
			}
			if (!cFileFind[0].GetFileName().CompareNoCase(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILER_FILENAME)))
			{
				if (cFileFind[1].FindFile(cFileFind[0].GetRoot() + STRINGCHAR(IDS_FILENAME_ALL) + STRING(IDS_DERIVEDPARAMETERLANGUAGE_LINKER_FILENAME)))
				{
					szFileName = cFileFind[0].GetFilePath();
					cFileFind[1].Close();
					break;
				}
			}
		}
		cFileFind[0].Close();
	}
	return szFileName;
}

CString CSourceDatabaseCompileThread::GetDerivedParametersLinkerFileName() CONST
{
	CString  szPlatForm;
	CString  szFileName[2];
	CString  szDirectory[2];
	CString  szOptions[3];
	CProfile  cProfile;

	return((cProfile.GetCompileOptions(szFileName[0], szFileName[1], szPlatForm, szDirectory[0], szDirectory[1], szOptions[0], szOptions[1], szOptions[2])) ? (LPCTSTR)szFileName[1] : EMPTYSTRING);
}

CString CSourceDatabaseCompileThread::GetDerivedParametersCompileOptions(CONST CBinaryDatabase *pDatabase) CONST
{
	INT  nPos[2];
	CString  szPlatForm;
	CString  szOptions[5];
	CString  szFileName[2];
	CString  szDirectory[2];
	CString  szIncludeDirectories;
	CProfile  cProfile;

	for (szOptions[0] = (!cProfile.GetCompileOptions(szFileName[0], szFileName[1], szPlatForm, szDirectory[0], szDirectory[1], szOptions[0], szOptions[1], szOptions[2])) ? (CString(STRING(IDS_COMPILER_OPTION_OPTIMIZATION_DEFAULT)) + CString(SPACE) + CString(STRING(IDS_COMPILER_OPTION_WARNING3))) : szOptions[0], nPos[0] = 0; nPos[0] + (nPos[1] = (INT)_tcscspn(szDirectory[0].Mid(nPos[0]), STRING(IDS_COMPILER_OPTION_PATH_SEPARATORS))) < szDirectory[0].GetLength() || nPos[0] < szDirectory[0].GetLength(); nPos[0] += nPos[1] + 1)
	{
		for (szOptions[3].Format(STRING(IDS_COMPILER_OPTION_INCLUDEDIRECTORY), (LPCTSTR)szDirectory[0].Mid(nPos[0], nPos[1])); !szIncludeDirectories.IsEmpty(); )
		{
			szIncludeDirectories += SPACE;
			break;
		}
		szIncludeDirectories += szOptions[3];
	}
	szOptions[3] = (!szIncludeDirectories.IsEmpty()) ? (szOptions[0] + SPACE + szIncludeDirectories) : szOptions[0];
	szOptions[4].Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILER_OPTIONS), (LPCTSTR)szOptions[3], (LPCTSTR)GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_OBJECTNAME)), (LPCTSTR)GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_COMPILENAME)));
	return szOptions[4];
}

CString CSourceDatabaseCompileThread::GetDerivedParametersLinkOptions(CONST CBinaryDatabase *pDatabase, CString &szOutputName, BOOL bTemporary) CONST
{
	INT  nPos[2];
	CString  szPlatForm;
	CString  szOptions[4];
	CString  szFileName[5];
	CString  szDirectory[2];
	CString  szLibraryFiles;
	CLogicalDrives  cDrives;
	CVersionInfo  cVersionInfo;
	CFileFindEx  cFileFind;
	CProfile  cProfile;

	if (cProfile.GetCompileOptions(szFileName[0], szFileName[1], szPlatForm, szDirectory[0], szDirectory[1], szOptions[0], szOptions[1], szOptions[2]))
	{
		for (nPos[0] = 0; nPos[0] + (nPos[1] = (INT)_tcscspn(szDirectory[1].Mid(nPos[0]), STRING(IDS_COMPILER_OPTION_PATH_SEPARATORS))) < szDirectory[1].GetLength() || nPos[0] < szDirectory[1].GetLength() || szDirectory[1].IsEmpty(); nPos[0] += nPos[1] + 1)
		{
			if (cFileFind.FindFile(szDirectory[1].Mid(nPos[0], nPos[1])))
			{
				for (cFileFind.FindNextFile(); !cFileFind.IsDirectory(); )
				{
					szFileName[2].Format(STRING(IDS_DERIVEDPARAMETERFILE_LIBRARYNAME), (LPCTSTR)szDirectory[1].Mid(nPos[0], nPos[1]));
					break;
				}
				for (; cFileFind.IsDirectory(); )
				{
					szFileName[2].Format(STRING(IDS_DERIVEDPARAMETERFILE_DEFAULTLIBRARYNAME), (LPCTSTR)(cFileFind.GetFilePath() + cDrives.GetPathDelimiter() + cVersionInfo.QueryInternalName()));
					break;
				}
				szLibraryFiles += (!szLibraryFiles.IsEmpty()) ? (SPACE + szFileName[2]) : szFileName[2];
				cFileFind.Close();
				continue;
			}
			if (szDirectory[1].IsEmpty())
			{
				szLibraryFiles.Format(STRING(IDS_DERIVEDPARAMETERFILE_DEFAULTLIBRARYNAME), (LPCTSTR)cVersionInfo.QueryInternalName());
				break;
			}
		}
		szFileName[3].Format(STRING(IDS_DATABASE_LIBRARY_UPDATENAME), EMPTYSTRING);
		szFileName[4].Format(STRING(IDS_DATABASE_LIBRARY_TEMPORARYNAME), EMPTYSTRING);
		szOutputName = (bTemporary) ? (pDatabase->GetLibraryUpdateFileName().Left(pDatabase->GetLibraryUpdateFileName().GetLength() - szFileName[3].GetLength()) + szFileName[4]) : pDatabase->GetLibraryUpdateFileName();
		szOptions[3].Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_LINKER_OPTIONS), (LPCTSTR)szPlatForm, (LPCTSTR)szOutputName, (LPCTSTR)szLibraryFiles, (LPCTSTR)GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_OBJECTNAME)));
		return szOptions[3];
	}
	return EMPTYSTRING;
}

LPCTSTR CSourceDatabaseCompileThread::FindDerivedParameterLanguageSourceCodeKeyword(LPCTSTR pszSourceCode, INT nPos, LPCTSTR pszKeyword) CONST
{
	LPCTSTR  pPos[2];

	for (pPos[0] = pszSourceCode + nPos; (pPos[1] = _tcsstr(pPos[0], pszKeyword)); pPos[0] = pPos[1] + lstrlen(pszKeyword))
	{
		if ((pPos[1] == pszSourceCode || (!_istalnum(pPos[1][-1]) && pPos[1][-1] != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SUBSTITUTE))) && (pPos[1] == pszSourceCode + lstrlen(pszSourceCode) - lstrlen(pszKeyword) || (!_istalnum(pPos[1][lstrlen(pszKeyword)]) && pPos[1][lstrlen(pszKeyword)] != STRINGCHAR(IDS_DERIVEDPARAMETERLANGUAGE_SYMBOL_SUBSTITUTE)))) break;
		continue;
	}
	return pPos[1];
}

CString CSourceDatabaseCompileThread::FormatDerivedParametersCompilerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszError, INT nLine)
{
	INT  nPos;
	INT  nLines;
	INT  nIndex;
	INT  nLength;
	INT  nOffset;
	DWORD  dwCode;
	LPSTR  pszCode;
	CFileEx  cFile;
	CString  szName;
	CString  szData;
	CString  szLine;
	CString  szError;
	LPCTSTR  pData[5];

	if (nLine > 0)
	{
		if (!m_szLines.GetSize())
		{
			if (cFile.Open(GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_COMPILENAME)), CFile::modeRead))
			{
				if ((pszCode = (LPSTR)GlobalAlloc(GPTR, (SIZE_T)cFile.GetLength() + 1)) != (LPSTR)NULL)
				{
					if (ReadFile(cFile.m_hFile, pszCode, (DWORD)cFile.GetLength(), &dwCode, (LPOVERLAPPED)NULL))
					{
#ifndef UNICODE
						szData = pszCode;
#else
						MultiByteToWideChar(CP_ACP, 0, pszCode, (INT)strlen(pszCode), szData.GetBufferSetLength((INT)strlen(pszCode)), (INT)strlen(pszCode));
						szData.ReleaseBuffer();
#endif
						for (nPos = 0, pData[0] = szData; nPos < szData.GetLength(); )
						{
							pData[1] = _tcsstr(pData[0] + nPos, CString(CR) + CString(EOL));
							pData[2] = _tcsstr(pData[0] + nPos, CString(CR));
							pData[3] = _tcsstr(pData[0] + nPos, CString(EOL));
							pData[4] = (pData[1]) ? ((pData[2]) ? ((pData[1] <= pData[2]) ? pData[1] : pData[2]) : pData[1]) : pData[2];
							pData[4] = (pData[4]) ? ((pData[3]) ? ((pData[4] <= pData[3]) ? pData[4] : pData[3]) : pData[4]) : pData[3];
							if (pData[4] && (pData[4] != pData[2] || pData[4] - pData[0] < szData.GetLength() - 1))
							{
								if (!_tcsncpy_s(szLine.GetBufferSetLength((INT)(pData[4] - pData[0] - nPos)), (INT)(pData[4] - pData[0] - nPos) + 1, pData[0] + nPos, pData[4] - pData[0] - nPos))
								{
									szLine.ReleaseBuffer();
									m_szLines.Add(szLine);
								}
								nPos += (pData[1] == pData[4]) ? (szLine.GetLength() + lstrlen(CString(CR) + CString(EOL))) : (szLine.GetLength() + max(lstrlen(CString(CR)), lstrlen(CString(EOL))));
								szLine.ReleaseBuffer();
								continue;
							}
							m_szLines.Add(pData[0] + nPos);
							break;
						}
						szData.Empty();
					}
					GlobalFree(pszCode);
				}
				cFile.Close();
			}
		}
		if (nLine < m_szLines.GetSize())
		{
			for (nIndex = nLine - 1, nOffset = 1; nIndex >= 0; nIndex--, nOffset = (nOffset > 0) ? (nOffset + 1) : nOffset)
			{
				for (nLines = (nOffset < 0) ? (INT)m_szLines.GetSize() : nIndex, szLine.Empty(); nLines < (INT)m_szLines.GetSize() && szLine.GetLength() < (INT)lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURESTATEMENTSPROLOG)); nLines++)
				{
					szLine += m_szLines.GetAt(nLines) + CR + EOL;
					continue;
				}
				if (!szLine.Find(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURESTATEMENTSPROLOG)))
				{
					nOffset = -nOffset;
					continue;
				}
				if ((nPos = (szLine = m_szLines.GetAt(nIndex)).Find(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREHEADERTAG))) >= 0)
				{
					for (nPos += lstrlen(STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDUREHEADERTAG)), szLine = m_szLines.GetAt(nIndex), nLength = szLine.GetLength(), szName.Empty(); nPos < nLength; nPos++)
					{
						if (GetDatabase()->CheckTMParameterTag(szName + szLine.GetAt(nPos)))
						{
							szName += szLine.GetAt(nPos);
							continue;
						}
						if (!szName.IsEmpty()) break;
					}
					if (nOffset < 0)
					{
						for (nPos = 0, nOffset = -nOffset, szLine = STRING(IDS_DERIVEDPARAMETERFILE_DERIVATIONPROCEDURESTATEMENTSPROLOG); nOffset > 1; nOffset--)
						{
							if ((nPos = szLine.Find(CString(CR) + CString(EOL))) < 0) break;
							szLine = szLine.Mid(nPos + 1);
						}
						szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_GENERICFORMAT), (LPCTSTR)szName, nOffset, pszError);
						break;
					}
					szError.Format(STRING(IDS_DERIVEDPARAMETERLANGUAGE_COMPILEERROR_SIMPLEFORMAT), (LPCTSTR)szName, pszError);
					break;
				}
			}
		}
	}
	return((!szError.IsEmpty()) ? (LPCTSTR)szError : pszError);
}

VOID CSourceDatabaseCompileThread::ShowDerivedParametersCompilerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszErrors)
{
	INT  nLine;
	INT  nPos[3];
	TCHAR  szChar;
	CString  szDigit;
	CString  szError;
	CString  szErrors;
	CString  szPrefix;
	CString  szMessage;
	CString  szDatabase;
	CString  szFileName;
	CFileFindEx  cFileFind;
	CStringTools  cStringTools;

	for (szErrors = szMessage = pszErrors, szMessage.MakeLower(), nLine = 0; szErrors.GetLength() > 0; szMessage = szErrors, szMessage.MakeLower(), nLine = 0)
	{
		nPos[0] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILEFATALERRORPREFIX));
		nPos[0] = nPos[1] = ((nPos[1] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_COMPILECOMMANDLINEPREFIX))) >= 0) ? ((nPos[0] >= 0) ? min(nPos[0], nPos[1]) : nPos[1]) : nPos[0];
		if (cFileFind.FindFile(GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_COMPILENAME))) && !cFileFind.FindNextFile() && (nPos[0] > szMessage.Find((!_tcslwr_s((szFileName = cFileFind.GetFileName()).GetBufferSetLength(cFileFind.GetFileName().GetLength()), cFileFind.GetFileName().GetLength() + 1)) ? szFileName : EMPTYSTRING) || nPos[0] < 0))
		{
			for (szFileName.ReleaseBuffer(), nPos[1] = ((nPos[0] = szMessage.Find(szFileName)) >= 0) ? (nPos[0] + szFileName.GetLength() + 1) : -1, szDigit = cStringTools.ConvertUIntToString(0); nPos[1] >= 0 && nPos[1] < szErrors.GetLength(); nPos[1]++)
			{
				if (_istdigit((szChar = szErrors.GetAt(nPos[1]))))
				{
					nLine = 10 * nLine + szChar - szDigit.GetAt(0);
					continue;
				}
				if (nLine > 0) break;
			}
		}
		if (nPos[1] >= 0)
		{
			for (szError.Empty(); nPos[1] < szErrors.GetLength() && nLine > 0; nPos[1]++)
			{
				if (_istalpha(szErrors.GetAt(nPos[1]))) break;
				continue;
			}
			while (nPos[1] < szErrors.GetLength())
			{
				if (szErrors.GetAt(nPos[1]) != CR  &&  szErrors.GetAt(nPos[1]) != EOL)
				{
					szError += szErrors.GetAt(nPos[1]);
					nPos[1]++;
					continue;
				}
				break;
			}
			if (!(szMessage = FormatDerivedParametersCompilerErrors(pDatabase, szError, nLine)).IsEmpty())
			{
				szMessage = szMessage.Left(szMessage.GetLength());
				ShowMessage(szMessage);
			}
			for (; nPos[1] < szErrors.GetLength(); )
			{
				if (szErrors.GetAt(nPos[1]) == CR || szErrors.GetAt(nPos[1]) == EOL)
				{
					nPos[1]++;
					continue;
				}
				break;
			}
			for (nPos[2] = 0, szError.MakeUpper(), szPrefix = STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX), szPrefix.MakeUpper(); nPos[2] < szPrefix.GetLength(); nPos[2]++)
			{
				if (!_istalpha(szPrefix.GetAt(nPos[2])))
				{
					szPrefix = szPrefix.Left(nPos[2]);
					break;
				}
			}
			if (_tcsstr(szError, szPrefix))
			{
				SetErrorCount(GetErrorCount() + 1);
				szErrors = szErrors.Mid(nPos[1]);
				continue;
			}
			SetWarningCount((!szErrors.IsEmpty()) ? (GetWarningCount() + 1) : GetWarningCount());
			szFileName.Format(STRING(IDS_DERIVEDPARAMETERFILE_COMPILENAME), (LPCTSTR)pDatabase->GetName());
			if (!szErrors.Mid(nPos[1]).Left(szFileName.GetLength()).CompareNoCase(szFileName) && (szErrors.GetAt(nPos[1] + szFileName.GetLength()) == CR || szErrors.GetAt(nPos[1] + szFileName.GetLength()) == EOL))
			{
				for (nPos[1] = nPos[1] + szFileName.GetLength(); nPos[1] < szErrors.GetLength(); nPos[1]++)
				{
					if (szErrors.GetAt(nPos[1]) == CR || szErrors.GetAt(nPos[1]) == EOL) continue;
					break;
				}
			}
			szErrors = szErrors.Mid(nPos[1]);
			continue;
		}
		for (nPos[0] = 0, szError.Empty(); nPos[0] < szErrors.GetLength(); nPos[0]++)
		{
			if (szErrors.GetAt(nPos[0]) != CR  &&  szErrors.GetAt(nPos[0]) != EOL)
			{
				szError += szErrors.GetAt(nPos[0]);
				continue;
			}
			break;
		}
		if (!_istspace(szError.GetAt(0)))
		{
			SetErrorCount(GetErrorCount() + 1);
			ShowMessage(szError);
		}
		else  ShowMessage(szError, FALSE);
		while (nPos[0] < szErrors.GetLength())
		{
			if (szErrors.GetAt(nPos[0]) == CR || szErrors.GetAt(nPos[0]) == EOL)
			{
				nPos[0]++;
				continue;
			}
			break;
		}
		szFileName.Format(STRING(IDS_DERIVEDPARAMETERFILE_COMPILENAME), (LPCTSTR)pDatabase->GetName());
		if (!szErrors.Mid(nPos[0]).Left(szFileName.GetLength()).CompareNoCase(szFileName) && (szErrors.GetAt(nPos[0] + szFileName.GetLength()) == CR || szErrors.GetAt(nPos[0] + szFileName.GetLength()) == EOL))
		{
			for (nPos[0] = nPos[0] + szFileName.GetLength(); nPos[0] < szErrors.GetLength(); nPos[0]++)
			{
				if (szErrors.GetAt(nPos[0]) == CR || szErrors.GetAt(nPos[0]) == EOL) continue;
				break;
			}
		}
		szErrors = szErrors.Mid(nPos[0]);
		continue;
	}
	cFileFind.Close();
}

VOID CSourceDatabaseCompileThread::ShowDerivedParametersLinkerErrors(CONST CBinaryDatabase *pDatabase, LPCTSTR pszErrors)
{
	INT  nPos[3];
	CString  szError;
	CString  szErrors;
	CString  szPrefix;
	CString  szMessage;
	CString  szFileName;
	CFileFindEx  cFileFind;

	for (szErrors = szMessage = pszErrors, szMessage.MakeLower(); szErrors.GetLength() > 0; szMessage = szErrors, szMessage.MakeLower())
	{
		nPos[0] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_LINKFATALERRORPREFIX));
		nPos[1] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_LINKERRORPREFIX));
		nPos[2] = szMessage.Find(STRING(IDS_DERIVEDPARAMETERFILE_ERROR_LINKWARNINGPREFIX));
		nPos[0] = nPos[1] = (nPos[0] >= 0) ? ((nPos[1] >= 0) ? min(nPos[0], nPos[1]) : nPos[0]) : nPos[1];
		nPos[0] = nPos[1] = (nPos[0] >= 0) ? ((nPos[2] >= 0) ? min(nPos[0], nPos[2]) : nPos[0]) : nPos[2];
		if ((cFileFind.FindFile(GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_OBJECTNAME))) && !cFileFind.FindNextFile()) && nPos[0] < 0)
		{
			for (szFileName = cFileFind.GetFileName(), szFileName.MakeLower(), nPos[1] = ((nPos[0] = szMessage.Find(szFileName)) >= 0) ? (nPos[0] + szFileName.GetLength()) : -1; nPos[1] >= 0 && nPos[1] < szErrors.GetLength(); nPos[1]++)
			{
				if (_istalpha(szErrors.GetAt(nPos[1]))) break;
				continue;
			}
		}
		if (nPos[1] >= 0)
		{
			for (szError.Empty(); nPos[1] < szErrors.GetLength(); nPos[1]++)
			{
				if (szErrors.GetAt(nPos[1]) != CR  &&  szErrors.GetAt(nPos[1]) != EOL)
				{
					szError += szErrors.GetAt(nPos[1]);
					continue;
				}
				break;
			}
			for (ShowMessage(szError); nPos[1] < szErrors.GetLength(); )
			{
				if (szErrors.GetAt(nPos[1]) == CR || szErrors.GetAt(nPos[1]) == EOL)
				{
					nPos[1]++;
					continue;
				}
				break;
			}
			for (nPos[2] = 0, szError.MakeUpper(), szPrefix = STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX), szPrefix.MakeUpper(); nPos[2] < szPrefix.GetLength(); nPos[2]++)
			{
				if (!_istalpha(szPrefix.GetAt(nPos[2])))
				{
					szPrefix = szPrefix.Left(nPos[2]);
					break;
				}
			}
			if (_tcsstr(szError, szPrefix))
			{
				SetErrorCount(GetErrorCount() + 1);
				szErrors = szErrors.Mid(nPos[1]);
				continue;
			}
			SetWarningCount((!szErrors.IsEmpty()) ? (GetWarningCount() + 1) : GetWarningCount());
			szErrors = szErrors.Mid(nPos[1]);
			continue;
		}
		for (nPos[0] = 0, szError.Empty(); nPos[0] < szErrors.GetLength(); nPos[0]++)
		{
			if (szErrors.GetAt(nPos[0]) != CR  &&  szErrors.GetAt(nPos[0]) != EOL)
			{
				szError += szErrors.GetAt(nPos[0]);
				continue;
			}
			break;
		}
		if (!_istspace(szError.GetAt(0)))
		{
			SetErrorCount(GetErrorCount() + 1);
			ShowMessage(szError);
		}
		else  ShowMessage(szError, FALSE);
		while (nPos[0] < szErrors.GetLength())
		{
			if (szErrors.GetAt(nPos[0]) == CR || szErrors.GetAt(nPos[0]) == EOL)
			{
				nPos[0]++;
				continue;
			}
			break;
		}
		szErrors = szErrors.Mid(nPos[0]);
		continue;
	}
	cFileFind.Close();
}

VOID CSourceDatabaseCompileThread::CleanupDerivedParametersBuildOutput(CONST CBinaryDatabase *pDatabase)
{
	BOOL  bFileFound;
	CString  szFileName[2];
	CFileFindEx  cFileFind;

	szFileName[0] = pDatabase->GetLibraryFileName();
	szFileName[1] = pDatabase->GetLibraryUpdateFileName();
	if (cFileFind.FindFile(GetDerivedParametersFileName(pDatabase, STRING(IDS_DATABASE_LIBRARY_SEARCHNAME))))
	{
		while ((bFileFound = cFileFind.FindNextFile()) == TRUE || !bFileFound)
		{
			if (cFileFind.GetFilePath().CompareNoCase(szFileName[0]) && cFileFind.GetFilePath().CompareNoCase(szFileName[1])) CFileEx::Remove(cFileFind.GetFilePath());
			if (!bFileFound) break;
		}
	}
	//CFileEx::Remove(GetDerivedParametersFileName(pDatabase,STRING(IDS_DERIVEDPARAMETERFILE_COMPILENAME)));
	CFileEx::Remove(GetDerivedParametersFileName(pDatabase, STRING(IDS_DERIVEDPARAMETERFILE_OBJECTNAME)));
}

VOID CSourceDatabaseCompileThread::ShowStartMessages()
{
	CString  szMessage;
	CProfile  cProfile;
	CByteArray  nInfo;
	CUpdateUI  cUpdateUI;

	for (ShowMessage((LPCTSTR) this, (LPCTSTR)NULL, -1, (LPCTSTR)NULL, FALSE, FALSE, FALSE), szMessage.Format(STRING(IDS_COMPILER_MESSAGE_FORMAT), (LPCTSTR)GetDatabase()->GetName()), ResetConsoleContent(STRING(IDS_OUTPUTWINDOW_BUILDTAB)), ShowMessage(szMessage), ShowMessage(STRING(IDS_COMPILER_MESSAGE_STARTCOMPILING)), m_bCompiling.SetEvent(), m_nErrors = m_nWarnings = 0; !cProfile.GetCompileDirectivesInfo(nInfo) || !m_pDirectives.Unmap(nInfo); )
	{
		m_pDirectives.RemoveAll();
		break;
	}
}

VOID CSourceDatabaseCompileThread::ShowStopMessages()
{
	CString  szMessage;
	CUpdateUI  cUpdateUI;

	for (szMessage.Format(STRING(IDS_COMPILER_MESSAGE_STOPCOMPILING), m_nErrors, m_nWarnings), ShowMessage((!m_bAborted) ? szMessage : STRING(IDS_COMPILER_MESSAGE_ABORTCOMPILING), TRUE, TRUE), m_bCompiling.ResetEvent(); m_pDirectives.GetSize() > 0; )
	{
		m_pDirectives.RemoveAll();
		break;
	}
}

VOID CSourceDatabaseCompileThread::ShowMessage(LPCTSTR pszMessage, BOOL bTimestamp, BOOL bAudition)
{
	CRecentDocumentInfo  cDocumentInfo;

	SetConsoleContext(STRING(IDS_OUTPUTWINDOW_BUILDTAB), &cDocumentInfo);
	ShowConsoleText(STRING(IDS_OUTPUTWINDOW_BUILDTAB), pszMessage, bTimestamp, bAudition);
}
BOOL CALLBACK CSourceDatabaseCompileThread::ShowMessage(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszMessage, BOOL bWarning, BOOL bTimestamp, BOOL bAudition)
{
	static CSourceDatabaseCompileThread  *pCompileThread = (CSourceDatabaseCompileThread *)NULL;

	if (nComponent == DATABASE_COMPONENT_NONE)
	{
		if (pCompileThread != (CSourceDatabaseCompileThread *)NULL)
		{
			pCompileThread->ShowMessage(pszMessage, bTimestamp, bAudition);
			return TRUE;
		}
		return FALSE;
	}
	if (nComponent != (ULONGLONG)-1)
	{
		if (pCompileThread != (CSourceDatabaseCompileThread *)NULL  &&  !bWarning)
		{
			pCompileThread->ShowError(pszName, pszInfo, nComponent, pszMessage);
			return TRUE;
		}
		if (pCompileThread != (CSourceDatabaseCompileThread *)NULL  &&  bWarning)
		{
			pCompileThread->ShowWarning(pszName, pszInfo, nComponent, pszMessage);
			return TRUE;
		}
		return FALSE;
	}
	pCompileThread = (CSourceDatabaseCompileThread *)pszName;
	return TRUE;
}

VOID CSourceDatabaseCompileThread::ShowError(LPCTSTR pszError)
{
	ShowError(EMPTYSTRING, EMPTYSTRING, 0, pszError);
}
VOID CSourceDatabaseCompileThread::ShowError(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszError)
{
	INT  nIndex;
	CString  szError;
	CRecentDocumentInfo  cDocumentInfo;
	CCompileDirectivesInfo  *pDirectivesInfo;

	for (szError = CString(STRING(IDS_COMPILER_MESSAGE_ERROR_PREFIX)) + pszError, cDocumentInfo.SetDocument(pszName, pszInfo, nComponent), SetConsoleContext(STRING(IDS_OUTPUTWINDOW_BUILDTAB), &cDocumentInfo); (((pDirectivesInfo = m_pDirectives.GetAt((nIndex = m_pDirectives.Find(m_pDirectives.GetActiveDirectives())))) && pDirectivesInfo->Find(szError) < 0) || nIndex < 0) && !m_bAborted; )
	{
		ShowConsoleText(STRING(IDS_OUTPUTWINDOW_BUILDTAB), szError, TRUE, FALSE);
		SetErrorCount(GetErrorCount() + 1);
		break;
	}
}

VOID CSourceDatabaseCompileThread::ShowWarning(LPCTSTR pszWarning)
{
	ShowWarning(EMPTYSTRING, EMPTYSTRING, 0, pszWarning);
}
VOID CSourceDatabaseCompileThread::ShowWarning(LPCTSTR pszName, LPCTSTR pszInfo, ULONGLONG nComponent, LPCTSTR pszWarning)
{
	INT  nIndex;
	CString  szWarning;
	CRecentDocumentInfo  cDocumentInfo;
	CCompileDirectivesInfo  *pDirectivesInfo;

	for (szWarning = CString(STRING(IDS_COMPILER_MESSAGE_WARNING_PREFIX)) + pszWarning, cDocumentInfo.SetDocument(pszName, pszInfo, nComponent), SetConsoleContext(STRING(IDS_OUTPUTWINDOW_BUILDTAB), &cDocumentInfo); (((pDirectivesInfo = m_pDirectives.GetAt((nIndex = m_pDirectives.Find(m_pDirectives.GetActiveDirectives())))) && (pDirectivesInfo->GetFlags() & COMPILEDIRECTIVES_FLAGS_NOWARNINGS) != COMPILEDIRECTIVES_FLAGS_NOWARNINGS && pDirectivesInfo->Find(szWarning) < 0) || nIndex < 0) && !m_bAborted; )
	{
		ShowConsoleText(STRING(IDS_OUTPUTWINDOW_BUILDTAB), szWarning, TRUE, FALSE);
		SetWarningCount(GetWarningCount() + 1);
		break;
	}
}

VOID CSourceDatabaseCompileThread::SetErrorCount(UINT nCount)
{
	m_nErrors = nCount;
}

UINT CSourceDatabaseCompileThread::GetErrorCount() CONST
{
	return m_nErrors;
}

VOID CSourceDatabaseCompileThread::SetWarningCount(UINT nCount)
{
	m_nWarnings = nCount;
}

UINT CSourceDatabaseCompileThread::GetWarningCount() CONST
{
	return m_nWarnings;
}

BEGIN_MESSAGE_MAP(CSourceDatabaseCompileThread, CThread)
	//{{AFX_MSG_MAP(CSourceDatabaseCompileThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSourceDatabaseCompileThread message handlers


//////////////////////////////////////////////////////////////////////////////
// CSourceDatabase

CSourceDatabase::CSourceDatabase() : CDatabaseEngine()
{
	m_pCompileThread = new CSourceDatabaseCompileThread();
	m_nTimerID = 0;
}
CSourceDatabase::CSourceDatabase(CDatabaseProfileInfo *pDatabaseInfo)
{
	Copy(pDatabaseInfo);
	m_pCompileThread = new CSourceDatabaseCompileThread();
	m_nTimerID = 0;
}

CSourceDatabase::~CSourceDatabase()
{
	if (m_nTimerID != 0)
	{
		KillTimer((HWND)NULL, m_nTimerID);
		m_nTimerID = 0;
	}
	delete m_pCompileThread;
}

BOOL CSourceDatabase::Open(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, BOOL bLoad, BOOL bBinary)
{
	return CDatabaseEngine::Open(pDatabaseProfileInfo, bLoad, bBinary);
}
BOOL CSourceDatabase::Open(CONST CDatabaseProfileInfo *pDatabaseProfileInfo, LPCTSTR pszDBMS, BOOL bLoad, BOOL bBinary)
{
	return CDatabaseEngine::Open(pDatabaseProfileInfo, pszDBMS, bLoad, bBinary);
}

VOID CSourceDatabase::Close()
{
	StopCompiling();
	CDatabaseEngine::Close();
}

BOOL CSourceDatabase::SetCompileBatches(CONST CCompileBatches &pBatches)
{
	INT  nBatch;
	INT  nBatches;
	CCompileBatchInfo  *pBatchInfo[2];

	for (nBatch = 0, nBatches = (INT)pBatches.GetSize(); nBatch < nBatches; nBatch++)
	{
		if ((pBatchInfo[0] = pBatches.GetAt(nBatch)) != (CCompileBatchInfo *)NULL)
		{
			if ((pBatchInfo[1] = m_pBatches.GetAt(m_pBatches.Find(pBatchInfo[0]->GetName()))))
			{
				if (pBatchInfo[0]->IsModified()) pBatchInfo[1]->Copy(pBatchInfo[0]);
				continue;
			}
			if ((pBatchInfo[1] = new CCompileBatchInfo))
			{
				for (pBatchInfo[1]->Copy(pBatchInfo[0]); m_pBatches.Add(pBatchInfo[1]) < 0; )
				{
					delete pBatchInfo[1];
					break;
				}
			}
		}
	}
	for (nBatch = 0, nBatches = (INT)m_pBatches.GetSize(); nBatch < nBatches; nBatch++)
	{
		if ((pBatchInfo[0] = m_pBatches.GetAt(nBatch)) != (CCompileBatchInfo *)NULL)
		{
			if (pBatches.Find(pBatchInfo[0]->GetName()) < 0)
			{
				m_pBatches.RemoveAt(nBatch);
				delete pBatchInfo[0];
				nBatches--;
				nBatch--;
			}
		}
	}
	ScheduleCompiling();
	return TRUE;
}

INT CSourceDatabase::GetCompileBatches(CCompileBatches &pBatches) CONST
{
	return((pBatches.Copy(&m_pBatches)) ? (INT)pBatches.GetSize() : 0);
}

BOOL CSourceDatabase::StartCompiling(ULONGLONG nFlags)
{
	return m_pCompileThread->StartCompiling(nFlags);
}

BOOL CSourceDatabase::IsCompiling() CONST
{
	return m_pCompileThread->IsCompiling();
}

VOID CSourceDatabase::ScheduleCompiling()
{
	INT  nIndex;
	INT  nBatch;
	INT  nBatches;
	CTimeKey  tBatchTime;
	CTimeKey  tExecutionTime;
	CTimeKey  tScheduledTime;
	ULONGLONG  nComponents;
	CCompileBatchInfo  *pBatchInfo;

	if (!IsOpen() || !IsValid() || IsCompiling())
	{
		m_nTimerID = (!m_nTimerID || KillTimer((HWND)NULL, m_nTimerID)) ? SetTimer((HWND)NULL, SOURCEDATABASECOMPILETHREAD_DEFAULT_TIMERID, SOURCEDATABASECOMPILETHREAD_DEFAULT_TIMEOUT, CompileTimerProc) : 0;
		return;
	}
	for (nBatch = 0, nBatches = (INT)m_pBatches.GetSize(), m_nTimerID = (!m_nTimerID || !KillTimer((HWND)NULL, m_nTimerID)) ? m_nTimerID : 0, tExecutionTime = 0, nIndex = -1; nBatch < nBatches; nBatch++)
	{
		if ((pBatchInfo = m_pBatches.GetAt(nBatch)) != (CCompileBatchInfo *)NULL)
		{
			if (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_IMMEDIATELY)
			{
				if (!pBatchInfo->GetLastExecutionTime().GetTime())
				{
					nIndex = nBatch;
					break;
				}
			}
			if (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_ATTIME)
			{
				if (pBatchInfo->GetExecutionTime() < tExecutionTime || !tExecutionTime.GetTime())
				{
					if (!pBatchInfo->GetLastExecutionTime().GetTime())
					{
						tExecutionTime = pBatchInfo->GetExecutionTime();
						nIndex = nBatch;
					}
				}
				continue;
			}
			if (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_DAILY)
			{
				for (tScheduledTime = ((tScheduledTime = (pBatchInfo->GetLastExecutionTime() > 0) ? (SECONDSPERDAY*(pBatchInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY) + pBatchInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY) : (SECONDSPERDAY*(tBatchTime.GetTime() / SECONDSPERDAY) + pBatchInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY)) < tBatchTime) ? (tScheduledTime.GetTime() + SECONDSPERDAY) : tScheduledTime; tScheduledTime < tExecutionTime || tExecutionTime == 0; )
				{
					tExecutionTime = tScheduledTime;
					nIndex = nBatch;
					break;
				}
				continue;
			}
		}
	}
	if ((pBatchInfo = m_pBatches.GetAt(nIndex)))
	{
		nComponents = (pBatchInfo->GetAction() == COMPILEBATCH_ACTION_COMPILATION) ? SOURCEDATABASECOMPILETHREAD_ACTION_COMPILATION : 0;
		nComponents |= (pBatchInfo->GetAction() == COMPILEBATCH_ACTION_SYNTAXCHECK) ? SOURCEDATABASECOMPILETHREAD_ACTION_SYNTAXCHECK : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_TMPACKETS) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_TMPACKETS : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_TCFUNCTIONS) ? (SOURCEDATABASECOMPILETHREAD_COMPONENT_TCFUNCTIONS | SOURCEDATABASECOMPILETHREAD_COMPONENT_TCSEQUENCES) : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_TCPROCEDURES) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_TCPROCEDURES : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_TMPARAMETERS) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_TMPARAMETERS : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_TCPARAMETERS) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_TCPARAMETERS : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_OBPROCESSORS) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_OBPROCESSORS : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_DERIVEDPARAMETERS) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_DERIVEDPARAMETERS : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_ANDS) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_AND : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_GRDS) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_GRD : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_MMDS) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_MMD : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_PODS) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_POD : nComponents;
		nComponents |= (pBatchInfo->GetComponents() & COMPILEBATCH_COMPONENT_SCRIPTS) ? SOURCEDATABASECOMPILETHREAD_COMPONENT_SCRIPT : nComponents;
		if (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_IMMEDIATELY || (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_ATTIME  &&  pBatchInfo->GetExecutionTime() <= tBatchTime) || (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_DAILY  &&  pBatchInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY <= tBatchTime.GetTime() % SECONDSPERDAY  &&  pBatchInfo->GetLastExecutionTime().GetTime() / SECONDSPERDAY < tBatchTime.GetTime() / SECONDSPERDAY))
		{
			pBatchInfo->SetLastExecutionTime(tBatchTime);
			StartCompiling(nComponents);
			ScheduleCompiling();
			return;
		}
		if (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_ATTIME)
		{
			m_nTimerID = SetTimer((HWND)NULL, SOURCEDATABASECOMPILETHREAD_DEFAULT_TIMERID, (UINT)(1000 * min(pBatchInfo->GetExecutionTime().GetTime() - tBatchTime.GetTime(), SECONDSPERDAY)), CompileTimerProc);
			return;
		}
		if (pBatchInfo->GetScheduleOptions() == COMPILEBATCH_SCHEDULE_DAILY)
		{
			m_nTimerID = SetTimer((HWND)NULL, SOURCEDATABASECOMPILETHREAD_DEFAULT_TIMERID, (pBatchInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY <= tBatchTime.GetTime() % SECONDSPERDAY) ? (UINT)(1000 * (SECONDSPERDAY - tBatchTime.GetTime() % SECONDSPERDAY + pBatchInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY)) : (UINT)(1000 * (pBatchInfo->GetDailyExecutionTime().GetTotalSeconds() % SECONDSPERDAY - tBatchTime.GetTime() % SECONDSPERDAY)), CompileTimerProc);
			return;
		}
	}
}

BOOL CSourceDatabase::StopCompiling()
{
	return((m_pCompileThread->StopCompiling()) ? GetDatabase()->CDatabaseEngine::StopCompiling() : FALSE);
}

CSourceDatabaseCompileThread *CSourceDatabase::GetCompileThread() CONST
{
	return m_pCompileThread;
}

VOID CALLBACK CSourceDatabase::CompileTimerProc(HWND hWnd, UINT uMsg, UINT_PTR nEventID, DWORD dwTime)
{
	GetDatabase()->ScheduleCompiling();
}
