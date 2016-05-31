// JCODE.CPP : JScript Code Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the automation script
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2003/06/30 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "Editor.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#using <mscorlib.dll>

#using <System.dll>

using namespace System;
using namespace System::Reflection;
using namespace System::Collections;



/////////////////////////////////////////////////////////////////////////////
// CJScriptCodeGenerator

CJScriptCodeGenerator::CJScriptCodeGenerator() : CObject()
{
	return;
}

BOOL CJScriptCodeGenerator::Compile(LPCTSTR pszName, LPCTSTR pszSourceCode, LPCTSTR pszExportCode, LPCTSTR pszOptions, LPCTSTR pszOutput, CStringArray &szErrors, CStringArray &szWarnings)
{
	INT  nError;
	INT  nErrors;
	INT  nWarning;
	INT  nWarnings;
	INT  nAssembly;
	INT  nAssemblies;
	Object^  pClass;
	CString  szDomain;
	CString  szOutput;
	CString  szTempPath;
	CString  szFileName;
	CString  szDirectory;
	CString  szResourceFile;
	CString  szSourceCode[8];
	AppDomain^  pAppDomain;
	ArrayList^  pszErrors;
	ArrayList^  pszWarnings;
	CFileFindEx  cFileFind;
	CVersionInfo  cVersionInfo;
	CLogicalDrives  cLogicalDrives;
	array<String^>^  pszAssemblies;
	array<Object^>^  pArguments;
	array<ArrayList^>^  pResults;
	CSecurityDescriptor  cSecurityDescriptor;

	for (szDomain.Format(STRING(IDS_SCRIPTASSEMBLY_COMPILATION_DOMAINNAME), pszName, (LPCTSTR)cVersionInfo.QueryFileDescription()), szSourceCode[0].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_HEADERBLOCK), pszName, STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_RUN), pszSourceCode, STRING(IDS_SCRIPTLANGUAGE_CODE_HEADERTYPEEXTENSION)), szSourceCode[1].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_TASKSCHDULERBLOCK), STRING(IDS_SCRIPTLANGUAGE_CODE_TASKSCHEDULERTELEMETRYREPORTSTYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_ENUM), STRING(IDS_SCRIPTLANGUAGE_CODE_TASKSCHEDULERTELEMETRYREPORTSTYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_ADD), STRING(IDS_SCRIPTLANGUAGE_CODE_TASKSCHEDULERTELEMETRYREPORTSTYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_DELETE), STRING(IDS_SCRIPTLANGUAGE_CODE_TASKSCHEDULERTELEMETRYDATAEXTRACTIONSTYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_ENUM), STRING(IDS_SCRIPTLANGUAGE_CODE_TASKSCHEDULERTELEMETRYDATAEXTRACTIONSTYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_ADD), STRING(IDS_SCRIPTLANGUAGE_CODE_TASKSCHEDULERTELEMETRYDATAEXTRACTIONSTYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_DELETE)), szSourceCode[2].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYINTERFACEBLOCK), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_GETVALUE), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_GETRAWVALUE), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_GETVALUETIME), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_SETPASTVALUESAMPLES), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_GETPASTVALUESAMPLES), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_GETPASTVALUE), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_GETPASTRAWVALUE), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_GETPASTVALUETIME), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_GETLASTUPDATETIME), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_GETLASTCHANGETIME), STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_GETSTATUS), pszName, STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_LOCK), pszName, STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_UNLOCK), pszName, STRING(IDS_SCRIPTLANGUAGE_CODE_TELEMETRYPARAMETERSINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_EXIT)), szSourceCode[3].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITESINTERFACEBLOCK), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTORBITLONGITUDE), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTORBITLATITUDE), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTORBITALTITUDE), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTORBITVELOCITY), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTPOSITION_X), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTPOSITION_Y), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTPOSITION_Z), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTVELOCITY_X), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTVELOCITY_Y), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTVELOCITY_Z)), szSourceCode[4].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITEPASSESINTERFACEBLOCK), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTPASSSTARTTIME), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTPASSSTOPTIME)), szSourceCode[5].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITEINTERLINKSINTERFACEBLOCK), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTINTERLINKSTARTTIME), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTINTERLINKSTOPTIME), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTINTERLINKSTARTTIME), STRING(IDS_SCRIPTLANGUAGE_CODE_SATELLITETRACKINGINTERFACETYPENAME), STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_CALCULATESPACECRAFTINTERLINKSTOPTIME)), szSourceCode[6].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_LIBRARYBLOCK), pszName, pszExportCode, STRING(IDS_SCRIPTLANGUAGE_CODE_HEADERTYPEEXTENSION)), szSourceCode[7] = (lstrlen(pszSourceCode) > 0) ? (szSourceCode[0] + szSourceCode[1] + szSourceCode[2] + szSourceCode[3] + szSourceCode[4] + szSourceCode[5]) : szSourceCode[6], szResourceFile.Format(STRING(IDS_AUTOMATIONSCRIPTLANGUAGE_COMPILER_OPTIONS), (LPCTSTR)CString(pszOutput).Left(CString(pszOutput).Find(pszName) - 1)), GetTempPath(MAX_PATH, szTempPath.GetBufferSetLength(MAX_PATH)), szTempPath.ReleaseBuffer(), szErrors.RemoveAll(), szWarnings.RemoveAll(); GetTempFileName(szTempPath, STRING(IDS_SCRIPTLANGUAGE_CODE_NAME), 0, szOutput.GetBufferSetLength(MAX_PATH)) > 0; )
	{
		try
		{
			pArguments = gcnew array<Object^>(5);
			pArguments[0] = gcnew String(szSourceCode[7]);
			pArguments[1] = gcnew String(szOutput);
			pArguments[2] = gcnew String(pszOptions);
			pArguments[3] = gcnew String(szResourceFile);
			pArguments[4] = pszAssemblies = gcnew array<String^>(MAXSCRIPTASSEMBLYNAME - MINSCRIPTASSEMBLYNAME + 1);
			for (nAssembly = 0, nAssemblies = pszAssemblies->Length; nAssembly < nAssemblies; nAssembly++)
			{
				pszAssemblies[nAssembly] = gcnew String(STRING(MINSCRIPTASSEMBLYNAME + nAssembly));
				continue;
			}
			if ((pAppDomain = AppDomain::CreateDomain(gcnew String(szDomain))))
			{
				for (szDirectory = pAppDomain->BaseDirectory; szDirectory.GetAt(szDirectory.GetLength() - 1) == cLogicalDrives.GetPathDelimiter(); )
				{
					szDirectory = szDirectory.Left(szDirectory.GetLength() - 1);
					break;
				}
				for (szFileName.Format(STRING(IDS_SCRIPTCOMPILERCODE_FILENAME), (LPCTSTR)szDirectory); (pClass = pAppDomain->CreateInstanceFromAndUnwrap(gcnew String(szFileName), gcnew String(STRING(IDS_SCRIPTCOMPILERCODE_CLASSNAME)))); )
				{
					if ((pResults = static_cast<array<ArrayList^>^>(pClass->GetType()->InvokeMember(gcnew String(STRING(IDS_SCRIPTCOMPILERCODE_METHODNAME)), BindingFlags::InvokeMethod, nullptr, pClass, pArguments))) != (array<ArrayList^>^) nullptr)
					{
						for (nError = 0, nErrors = (pszErrors = pResults[0])->Count; nError < nErrors; nError++)
						{
							szErrors.Add(pszErrors[nError]->ToString());
							continue;
						}
						for (nWarning = 0, nWarnings = (pszWarnings = pResults[1])->Count; nWarning < nWarnings; nWarning++)
						{
							szWarnings.Add(pszWarnings[nWarning]->ToString());
							continue;
						}
						if (!nErrors)
						{
							for (CFileEx::SetAttributes(pszOutput, CFileEx::GetAttributes(pszOutput) & ~FILE_ATTRIBUTE_READONLY); CFileEx::Move(szOutput, pszOutput, MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING); )
							{
								if (cSecurityDescriptor.SetRightsOfSystem(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfNetworkService(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfAdministrators(FILE_ALL_ACCESS) && (cSecurityDescriptor.SetRightsOfSystemOperators(FILE_GENERIC_READ | FILE_GENERIC_WRITE) || cSecurityDescriptor.SetRightsOfPowerUsers(FILE_GENERIC_READ | FILE_GENERIC_WRITE)) && cSecurityDescriptor.SetRightsOfAuthenticatedUsers(FILE_GENERIC_READ) && cSecurityDescriptor.SetRightsOfEveryone(FILE_GENERIC_READ) && cFileFind.FindFile(pszOutput) && !cFileFind.FindNextFile() && CSecurity::SecureDirectory(cFileFind.GetRoot(), cSecurityDescriptor) && CSecurity::SecureFile(cFileFind.GetFilePath(), cSecurityDescriptor))
								{
									CFileEx::SetAttributes(pszOutput, CFileEx::GetAttributes(pszOutput) | FILE_ATTRIBUTE_READONLY);
									AppDomain::Unload(pAppDomain);
									delete pArguments;
									delete pResults;
									cFileFind.Close();
									return TRUE;
								}
							}
							CFileEx::SetAttributes(pszOutput, CFileEx::GetAttributes(pszOutput) | FILE_ATTRIBUTE_READONLY);
						}
						AppDomain::Unload(pAppDomain);
						CFileEx::Remove(szOutput);
						delete pArguments;
						delete pResults;
						return(nErrors > 0);
					}
					break;
				}
				AppDomain::Unload(pAppDomain);
			}
			delete pArguments;
		}
		catch (...)
		{
			AppDomain::Unload(pAppDomain);
			delete pArguments;
		}
		break;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CJScriptCodeExecutor

CJScriptCodeExecutor::CJScriptCodeExecutor() : CObject()
{
	return;
}

BOOL CJScriptCodeExecutor::Run(LPCTSTR pszName, LPCTSTR pszTitle, LPCTSTR pszFileName, LPCTSTR pszInputFileName, LPCTSTR pszOutputFileName, CString &szError)
{
	INT  nPos;
	Object^  pClass;
	CString  szDomain;
	CString  szFileName;
	CString  szDirectory;
	CString  szTypeName[2];
	AppDomain^  pAppDomain;
	CFileFindEx  cFileFind;
	CStringTools  cStringTools;
	CVersionInfo  cVersionInfo;
	CLogicalDrives  cLogicalDrives;
	array<Object^>^  pArguments;
	array<String^>^  pszResults;

	for (szError.Empty(); cFileFind.FindFile(pszFileName) && !cFileFind.FindNextFile(); )
	{
		try
		{
			pArguments = gcnew array<Object^>(13);
			for (szDomain.Format(STRING(IDS_SCRIPTASSEMBLY_EXECUTION_DOMAINNAME), (LPCTSTR)cFileFind.GetFileTitle(), (LPCTSTR)cVersionInfo.QueryFileDescription()), pAppDomain = AppDomain::CreateDomain(gcnew String(szDomain)), szDirectory = pAppDomain->BaseDirectory; szDirectory.GetAt(szDirectory.GetLength() - 1) == cLogicalDrives.GetPathDelimiter(); )
			{
				szDirectory = szDirectory.Left(szDirectory.GetLength() - 1);
				break;
			}
			szFileName.Format(STRING(IDS_SCRIPTLOADERCODE_FILENAME), (LPCTSTR)szDirectory);
			szTypeName[0].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_NAME), (LPCTSTR)pszName);
			szTypeName[1].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_HEADERTYPENAME), (LPCTSTR)szTypeName[0]);
			pArguments[0] = gcnew String(szFileName);
			pArguments[1] = gcnew String(pszFileName);
			pArguments[2] = gcnew String(szTypeName[1]);
			pArguments[3] = gcnew String(STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_RUN));
			pArguments[4] = gcnew String(EMPTYSTRING);
			pArguments[5] = gcnew String(CString(pszName) + TAB + CString(pszTitle));
			pArguments[6] = gcnew String(pszInputFileName);
			pArguments[7] = gcnew String(pszOutputFileName);
			pArguments[8] = gcnew String(EMPTYSTRING);
			pArguments[9] = gcnew String(EMPTYSTRING);
			pArguments[10] = gcnew String(EMPTYSTRING);
			pArguments[11] = gcnew String(EMPTYSTRING);
			pArguments[12] = gcnew String(cStringTools.ConvertLongIntToString(CTime::GetCurrentTime().GetTime()));
		}
		catch (...)
		{
			AppDomain::Unload(pAppDomain);
			delete pArguments;
			cFileFind.Close();
			return FALSE;
		}
		try
		{
			if ((pClass = pAppDomain->CreateInstanceFromAndUnwrap(gcnew String(szFileName), gcnew String(STRING(IDS_SCRIPTLOADERCODE_CLASSNAME)))))
			{
				if ((pszResults = (array<String^>^) pClass->GetType()->InvokeMember(gcnew String(STRING(IDS_SCRIPTLOADERCODE_METHODNAME)), BindingFlags::InvokeMethod, nullptr, pClass, pArguments)) && !pszResults[2]->ToString()->Length)
				{
					AppDomain::Unload(pAppDomain);
					delete pArguments;
					cFileFind.Close();
					return TRUE;
				}
				for (szError = (pszResults[2]->ToString() != gcnew String(SPACE)) ? pszResults[2]->ToString() : gcnew String(EMPTYSTRING); (nPos = szError.Find(EOL)) >= 0; )
				{
					for (szError = szError.Left(nPos) + SPACE + szError.Mid(nPos + 1); szError.GetAt((nPos = nPos + 1)) == EOL; )
					{
						szError = szError.Left(nPos) + szError.Mid(nPos + 1);
						continue;
					}
				}
			}
			AppDomain::Unload(pAppDomain);
			delete pArguments;
			cFileFind.Close();
			return FALSE;
		}
		catch (...)
		{
			AppDomain::Unload(pAppDomain);
			delete pArguments;
		}
		cFileFind.Close();
		break;
	}
	return FALSE;
}
