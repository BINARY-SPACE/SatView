// SCRIPTS.CPP : Scripts Code Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the automation script
// assemblies related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2005/02/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "scripts.h"

#using <System.dll>
#using <Microsoft.JScript.dll>

using namespace System;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Reflection;
using namespace System::Collections;
using namespace System::CodeDom::Compiler;
using namespace System::Runtime::InteropServices;
using namespace Microsoft::JScript;


[DllImport("SatView")]
extern "C" int EnumJScriptTaskSchedulerTelemetryReports(const wchar_t **pszNames[], unsigned int *nIDs[], __int64 *tStartTimes[], __int64 *tIntervals[], __int64 *tStopTimes[]);
extern "C" unsigned int AddJScriptTaskSchedulerTelemetryReport(const wchar_t *pszName, __int64 tStartTime, __int64 tInterval, __int64 tStopTime);
extern "C" bool DeleteJScriptTaskSchedulerTelemetryReport(unsigned int nID);
extern "C" int EnumJScriptTaskSchedulerTelemetryDataExtractions(const wchar_t **pszNames[], unsigned int *nIDs[], __int64 *tScheduleTimes[], __int64 *tStartTimes[], __int64 *tStopTimes[]);
extern "C" unsigned int AddJScriptTaskSchedulerTelemetryDataExtraction(const wchar_t *pszName, __int64 tScheduleTime, __int64 tStartTime, __int64 tStopTime);
extern "C" bool DeleteJScriptTaskSchedulerTelemetryDataExtraction(unsigned int nID);
extern "C" bool GetJScriptTelemetryInterfaceParameterIntValue(const wchar_t *pszTag, int nSample, __int64 &nValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterUIntValue(const wchar_t *pszTag, int nSample, unsigned __int64 &nValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterFloatValue(const wchar_t *pszTag, int nSample, double &fValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterStringValue(const wchar_t *pszTag, int nSample, wchar_t **pszValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterRawIntValue(const wchar_t *pszTag, int nSample, __int64 &nValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterRawUIntValue(const wchar_t *pszTag, int nSample, unsigned __int64 &nValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterRawFloatValue(const wchar_t *pszTag, int nSample, double &fValue);
extern "C" __int64 GetJScriptTelemetryInterfaceParameterValueTime(const wchar_t *pszTag, int nSample);
extern "C" bool SetJScriptTelemetryInterfaceParameterPastValueSamples(const wchar_t *pszTag, unsigned short wSamples);
extern "C" unsigned short GetJScriptTelemetryInterfaceParameterPastValueSamples(const wchar_t *pszTag);
extern "C" bool GetJScriptTelemetryInterfaceParameterPastIntValue(const wchar_t *pszTag, int nSample, __int64 &nValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterPastUIntValue(const wchar_t *pszTag, int nSample, unsigned __int64 &nValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterPastFloatValue(const wchar_t *pszTag, int nSample, double &fValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterPastStringValue(const wchar_t *pszTag, int nSample, wchar_t **pszValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterPastRawIntValue(const wchar_t *pszTag, int nSample, __int64 &nValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterPastRawUIntValue(const wchar_t *pszTag, int nSample, unsigned __int64 &nValue);
extern "C" bool GetJScriptTelemetryInterfaceParameterPastRawFloatValue(const wchar_t *pszTag, int nSample, double &fValue);
extern "C" __int64 GetJScriptTelemetryInterfaceParameterPastValueTime(const wchar_t *pszTag, int nSample);
extern "C" __int64 GetJScriptTelemetryInterfaceParameterLastUpdateTime(const wchar_t *pszTag);
extern "C" __int64 GetJScriptTelemetryInterfaceParameterLastChangeTime(const wchar_t *pszTag);
extern "C" unsigned int GetJScriptTelemetryInterfaceParameterStatus(const wchar_t *pszTag, int nSample);
extern "C" bool LockJScriptTelemetryInterface(const wchar_t *pszName);
extern "C" bool UnlockJScriptTelemetryInterface(const wchar_t *pszName);
extern "C" bool ExitJScriptTelemetryInterface(const wchar_t *pszName, bool bCode);

#ifdef SATELLITETRACKING
[DllImport("SpaceEngine")]
extern "C" double CalculateSpacecraftOrbitLongitude(const wchar_t *pszSpacecraft, unsigned int nNORADID, __int64 tTime);
extern "C" double CalculateSpacecraftOrbitLatitude(const wchar_t *pszSpacecraft, unsigned int nNORADID, __int64 tTime);
extern "C" double CalculateSpacecraftOrbitAltitude(const wchar_t *pszSpacecraft, unsigned int nNORADID, __int64 tTime);
extern "C" double CalculateSpacecraftOrbitVelocity(const wchar_t *pszSpacecraft, unsigned int nNORADID, __int64 tTime);
extern "C" bool CalculateSpacecraftPosition(const wchar_t *pszSpacecraft, unsigned int nNORADID, __int64 tTime, double *x, double *y, double *z);
extern "C" bool CalculateSpacecraftVelocity(const wchar_t *pszSpacecraft, unsigned int nNORADID, __int64 tTime, double *vx, double *vy, double *vz);
extern "C" __int64 CalculateSpacecraftPassStartTime(const wchar_t *pszSpacecraft, unsigned int nNORADID, const wchar_t *pszLocation, double fLocationLongitude, double fLocationLatitude, double fLocationAltitude, __int64 tStartTime, __int64 tInterval);
extern "C" __int64 CalculateSpacecraftPassStopTime(const wchar_t *pszSpacecraft, unsigned int nNORADID, const wchar_t *pszLocation, double fLocationLongitude, double fLocationLatitude, double fLocationAltitude, __int64 tStartTime, __int64 tInterval);
extern "C" __int64 CalculateSpacecraftInterlinkStartTime(const wchar_t *pszSpacecraftA, unsigned int nNORADIDA, const wchar_t *pszSpacecraftB, unsigned int nNORADIDB, __int64 tStartTime, __int64 tInterval);
extern "C" __int64 CalculateSpacecraftInterlinkStopTime(const wchar_t *pszSpacecraftA, unsigned int nNORADIDA, const wchar_t *pszSpacecraftB, unsigned int nNORADIDB, __int64 tStartTime, __int64 tInterval);
extern "C" __int64 CalculateSpacecraftRelaidInterlinkStartTime(const wchar_t *pszSpacecraftA, unsigned int nNORADIDA, const wchar_t *pszSpacecraftVia, unsigned int nNORADIDVia, const wchar_t *pszSpacecraftB, unsigned int nNORADIDB, __int64 tStartTime, __int64 tInterval);
extern "C" __int64 CalculateSpacecraftRelaidInterlinkStopTime(const wchar_t *pszSpacecraftA, unsigned int nNORADIDA, const wchar_t *pszSpacecraftVia, unsigned int nNORADIDVia, const wchar_t *pszSpacecraftB, unsigned int nNORADIDB, __int64 tStartTime, __int64 tInterval);
#endif



namespace ScriptsAssemblyCompiler
{
	public ref class ScriptsCompiler : public MarshalByRefObject
	{
	public:
		array<ArrayList^>^ CompileAndLink(String^ pszCode, String^ pszOutput, String^ pszOptions, String^ pszResource, array<String^>^ pszAssemblies)
		{
			int  nItem;
			int  nItems;
			int  nError;
			int  nErrors;
			String^  pszError;
			String^  pszWarning;
			ArrayList^  pszErrors;
			ArrayList^  pszWarnings;
			array<ArrayList^>^ pResults;
			CodeDomProvider^  pJScriptCodeProvider;
			CompilerResults^  pJScriptCompilerResults;
			CompilerParameters^  pJScriptCompilerParameters;

			try
			{
				if ((pJScriptCodeProvider = gcnew JScriptCodeProvider))
				{
					if ((pJScriptCompilerParameters = gcnew CompilerParameters))
					{
						pJScriptCompilerParameters->OutputAssembly = pszOutput;
						pJScriptCompilerParameters->CompilerOptions = pszOptions;
						pJScriptCompilerParameters->Win32Resource = pszResource;
						pJScriptCompilerParameters->GenerateExecutable = false;
						pJScriptCompilerParameters->IncludeDebugInformation = false;
						for (nItem = 0, nItems = pszAssemblies->Length; nItem < nItems; nItem++)
						{
							pJScriptCompilerParameters->ReferencedAssemblies->Add(pszAssemblies[nItem]);
							continue;
						}
						if ((pJScriptCompilerResults = pJScriptCodeProvider->CompileAssemblyFromSource(pJScriptCompilerParameters, pszCode)))
						{
							for (nError = 0, nErrors = pJScriptCompilerResults->Errors->Count, pszError = gcnew String(EMPTYSTRING), pszWarning = gcnew String(EMPTYSTRING), pszErrors = gcnew ArrayList, pszWarnings = gcnew ArrayList; nError < nErrors; nError++)
							{
								if (!pJScriptCompilerResults->Errors -> default[nError]->IsWarning  &&  !pJScriptCompilerResults->Errors -> default[nError]->Line)
								{
									pszError = String::Format(SCRIPTSCOMPILER_ERROR_FORMAT, pJScriptCompilerResults->Errors -> default[nError]->ErrorNumber, pJScriptCompilerResults->Errors -> default[nError]->ErrorText);
									pszErrors->Add(pszError);
									continue;
								}
								if (!pJScriptCompilerResults->Errors -> default[nError]->IsWarning  &&  pJScriptCompilerResults->Errors -> default[nError]->Line > 0)
								{
									pszError = String::Format(SCRIPTSCOMPILER_ERROR_LINEFORMAT, pJScriptCompilerResults->Errors -> default[nError]->ErrorNumber, pJScriptCompilerResults->Errors -> default[nError]->Line, pJScriptCompilerResults->Errors -> default[nError]->ErrorText);
									pszErrors->Add(pszError);
									continue;
								}
								if (!pJScriptCompilerResults->Errors -> default[nError]->Line)
								{
									pszWarning = String::Format(SCRIPTSCOMPILER_WARNING_FORMAT, pJScriptCompilerResults->Errors -> default[nError]->ErrorNumber, pJScriptCompilerResults->Errors -> default[nError]->ErrorText);
									pszWarnings->Add(pszWarning);
									continue;
								}
								pszWarning = String::Format(SCRIPTSCOMPILER_WARNING_LINEFORMAT, pJScriptCompilerResults->Errors -> default[nError]->ErrorNumber, pJScriptCompilerResults->Errors -> default[nError]->Line, pJScriptCompilerResults->Errors -> default[nError]->ErrorText);
								pszWarnings->Add(pszWarning);
							}
							pResults = gcnew array<ArrayList^>(2);
							pResults[0] = pszErrors;
							pResults[1] = pszWarnings;
							return pResults;
						}
					}
				}
			}
			catch (Exception^ e)
			{
				pResults = gcnew array<ArrayList^>(2);
				pszErrors = gcnew ArrayList;
				pszWarnings = gcnew ArrayList;
				pszErrors->Add(e->Message);
				pResults[0] = pszErrors;
				pResults[1] = pszWarnings;
				return pResults;
			}
			pResults = gcnew array<ArrayList^>(2);
			pResults[0] = gcnew ArrayList;
			pResults[1] = gcnew ArrayList;
			return pResults;
		}
	};
}


namespace ScriptsAssemblyLoader
{
	public ref class AssemblyLoader : public MarshalByRefObject
	{
	public:
		array<String^>^ LoadAndExecute(String^ pszCallingModule, String^ pszFileName, String^ pszClass, String^ pszMethod, String^ pszName, String^ pszScript, String^ pszInputFile, String^ pszOutputFile, String^ pszAlert, String^ pszEvent, String^ pszMessage, String^ pszExtraInfo, String^ pszTime)
		{
			Mutex^  pMutex;
			Object^  pClass;
			Object^  pResult;
			Assembly^  pAssembly;
			StringBuilder^  pszOutput;
			array<Object^>^  pArguments;
			array<String^>^  pszResults;

			try
			{
				for (pMutex = gcnew Mutex(false, pszClass); true; )
				{
					pMutex->WaitOne();
					break;
				}
				pArguments = gcnew array<Object^>(12);
				pArguments[0] = gcnew String(pszCallingModule->ToCharArray());
				pArguments[1] = gcnew String(pszName->ToCharArray());
				pArguments[2] = gcnew String(pszScript->ToCharArray());
				pArguments[3] = gcnew String(pszInputFile->ToCharArray());
				pArguments[4] = gcnew StringBuilder(pszOutputFile);
				pArguments[5] = gcnew String(pszAlert->ToCharArray());
				pArguments[6] = gcnew String(pszEvent->ToCharArray());
				pArguments[7] = gcnew String(pszMessage->ToCharArray());
				pArguments[8] = gcnew String(pszExtraInfo->ToCharArray());
				pArguments[9] = gcnew String(pszTime->ToCharArray());
				pArguments[10] = gcnew StringBuilder(EMPTYSTRING);
				pArguments[11] = gcnew StringBuilder(EMPTYSTRING);
				if ((pAssembly = Assembly::LoadFrom(pszFileName)))
				{
					if ((pResult = ((pClass = pAssembly->CreateInstance(pszClass))) ? pClass->GetType()->InvokeMember(pszMethod, BindingFlags::InvokeMethod, nullptr, pClass, pArguments) : (Object^)NULL) && System::Convert::ToBoolean(pResult))
					{
						for (pszOutput = gcnew StringBuilder(pArguments[4]->ToString()); pszOutput->Length > 0; )
						{
							if (pszOutput -> default[0] == SPACE)
							{
								pszOutput->Remove(0, 1);
								continue;
							}
							break;
						}
						for (; pszOutput->Length > 0; )
						{
							if (pszOutput -> default[pszOutput->Length - 1] == SPACE)
							{
								pszOutput->Remove(pszOutput->Length - 1, 1);
								continue;
							}
							break;
						}
						pszResults = gcnew array<String^>(3);
						pszResults[0] = gcnew String(pszOutput->ToString()->ToCharArray());
						pszResults[1] = gcnew String(pArguments[10]->ToString()->ToCharArray());
						pszResults[2] = gcnew String(EMPTYSTRING);
						pMutex->ReleaseMutex();
						delete pArguments;
						return pszResults;
					}
				}
			}
			catch (Exception^ e)
			{
				pszResults = gcnew array<String^>(3);
				pszResults[0] = gcnew String(EMPTYSTRING);
				pszResults[1] = gcnew String(EMPTYSTRING);
				pszResults[2] = (e->Message->Length > 0) ? gcnew String(e->Message->ToCharArray()) : gcnew String(SPACESTRING);
				pMutex->ReleaseMutex();
				delete pArguments;
				return pszResults;
			}
			pszResults = gcnew array<String^>(3);
			pszResults[0] = gcnew String(EMPTYSTRING);
			pszResults[1] = gcnew String(EMPTYSTRING);
			pszResults[2] = (pArguments[11]->ToString()->Length > 0) ? gcnew String(pArguments[11]->ToString()->ToCharArray()) : gcnew String(SPACESTRING);
			pMutex->ReleaseMutex();
			return pszResults;
		}
	};
}


namespace ScriptsTaskScheduler
{
	public ref class TelemetryReports : public MarshalByRefObject
	{
	public:
		int Enum(ArrayList^ szNames, ArrayList^ nIDs, ArrayList^ tStartTimes, ArrayList^ tIntervals, ArrayList^ tStopTimes)
		{
			int  nItem;
			int  nItems;
			__int64  *tTaskStartTimes = NULL;
			__int64  *tTaskStopTimes = NULL;
			__int64  *tTaskIntervals = NULL;
			unsigned int  *nTaskIDs = NULL;
			const wchar_t  **pszTaskNames = NULL;
			DateTime  sDateTime(1970, 1, 1);

			for (nItem = 0, nItems = EnumJScriptTaskSchedulerTelemetryReports(&pszTaskNames, &nTaskIDs, &tTaskStartTimes, &tTaskIntervals, &tTaskStopTimes); nItem < nItems; nItem++)
			{
				szNames->Add(gcnew String(pszTaskNames[nItem]));
				nIDs->Add(nTaskIDs[nItem]);
				tStartTimes->Add(DateTime(sDateTime.Ticks + 10000000 * tTaskStartTimes[nItem]));
				tIntervals->Add(TimeSpan((tTaskIntervals[nItem] > 0) ? (10000000 * tTaskIntervals[nItem]) : 0));
				tStopTimes->Add(DateTime((tTaskStopTimes[nItem] > 0) ? (sDateTime.Ticks + 10000000 * tTaskStopTimes[nItem]) : 0));
				delete[] pszTaskNames[nItem];
			}
			delete nTaskIDs;
			delete pszTaskNames;
			delete tTaskStartTimes;
			delete tTaskIntervals;
			delete tTaskStopTimes;
			return nItems;
		}
		unsigned int Add(String^ szName, DateTime^ tStartTime, TimeSpan^ tInterval, DateTime^ tStopTime)
		{
			unsigned int  nID;
			const wchar_t  *pszName;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszName = AllocString(szName)))
			{
				if ((nID = AddJScriptTaskSchedulerTelemetryReport(pszName, (tStartTime->Ticks - sDateTime.Ticks) / 10000000, tInterval->Ticks / 10000000, (tStopTime->Ticks > 0) ? ((tStopTime->Ticks - sDateTime.Ticks) / 10000000) : 0)) != (unsigned int)-1)
				{
					FreeString(pszName);
					return nID;
				}
				FreeString(pszName);
			}
			return -1;
		}
		bool Delete(unsigned int nID)
		{
			return((DeleteJScriptTaskSchedulerTelemetryReport(nID)) ? true : false);
		}
	private:
		const wchar_t *AllocString(String^ sz)
		{
			int  nPos;
			int  nLength;
			wchar_t  *psz;

			if ((psz = new wchar_t[sz->Length + 1]))
			{
				for (nPos = 0, nLength = sz->Length, psz[nLength] = EOS; nPos < nLength; nPos++)
				{
					psz[nPos] = sz -> default[nPos];
					continue;
				}
			}
			return psz;
		}
		void FreeString(const wchar_t *psz)
		{
			delete[] psz;
		}
	};
	public ref class TelemetryDataExtractions : public MarshalByRefObject
	{
	public:
		int Enum(ArrayList^ szNames, ArrayList^ nIDs, ArrayList^ tScheduleTimes, ArrayList^ tStartTimes, ArrayList^ tStopTimes)
		{
			int  nItem;
			int  nItems;
			__int64  *tTaskScheduleTimes = NULL;
			__int64  *tTaskStartTimes = NULL;
			__int64  *tTaskStopTimes = NULL;
			unsigned int  *nTaskIDs = NULL;
			const wchar_t  **pszTaskNames = NULL;
			DateTime  sDateTime(1970, 1, 1);

			for (nItem = 0, nItems = EnumJScriptTaskSchedulerTelemetryDataExtractions(&pszTaskNames, &nTaskIDs, &tTaskScheduleTimes, &tTaskStartTimes, &tTaskStopTimes); nItem < nItems; nItem++)
			{
				szNames->Add(gcnew String(pszTaskNames[nItem]));
				nIDs->Add(nTaskIDs[nItem]);
				tScheduleTimes->Add(DateTime(sDateTime.Ticks + 10000000 * tTaskScheduleTimes[nItem]));
				tStartTimes->Add(DateTime(sDateTime.Ticks + 10000000 * tTaskStartTimes[nItem]));
				tStopTimes->Add(DateTime(sDateTime.Ticks + 10000000 * tTaskStopTimes[nItem]));
				delete[] pszTaskNames[nItem];
			}
			delete nTaskIDs;
			delete pszTaskNames;
			delete tTaskScheduleTimes;
			delete tTaskStartTimes;
			delete tTaskStopTimes;
			return nItems;
		}
		unsigned int Add(String^ szName, DateTime^ tScheduleTime, DateTime^ tStartTime, DateTime^ tStopTime)
		{
			unsigned int  nID;
			const wchar_t  *pszName;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszName = AllocString(szName)))
			{
				if ((nID = AddJScriptTaskSchedulerTelemetryDataExtraction(pszName, (tScheduleTime->Ticks - sDateTime.Ticks) / 10000000, (tStartTime->Ticks - sDateTime.Ticks) / 10000000, (tStopTime->Ticks - sDateTime.Ticks) / 10000000)) != (unsigned int)-1)
				{
					FreeString(pszName);
					return nID;
				}
				FreeString(pszName);
			}
			return -1;
		}
		bool Delete(unsigned int nID)
		{
			return((DeleteJScriptTaskSchedulerTelemetryDataExtraction(nID)) ? true : false);
		}
	private:
		const wchar_t *AllocString(String^sz)
		{
			int  nPos;
			int  nLength;
			wchar_t  *psz;

			if ((psz = new wchar_t[sz->Length + 1]))
			{
				for (nPos = 0, nLength = sz->Length, psz[nLength] = EOS; nPos < nLength; nPos++)
				{
					psz[nPos] = sz -> default[nPos];
					continue;
				}
			}
			return psz;
		}
		void FreeString(const wchar_t *psz)
		{
			delete[] psz;
		}
	};
}


namespace ScriptsTelemetryInterface
{
	public ref class TelemetryParameters : public MarshalByRefObject
	{
	public:
		Object^ GetValue(String^ szTag, int nSample)
		{
			double  fValue;
			__int64  nValue;
			wchar_t  *pszValue;
			unsigned __int64  uValue;
			const wchar_t  *pszTag;

			if ((pszTag = AllocString(szTag)))
			{
				if (GetJScriptTelemetryInterfaceParameterIntValue(pszTag, nSample, nValue))
				{
					FreeString(pszTag);
					return nValue;
				}
				if (GetJScriptTelemetryInterfaceParameterUIntValue(pszTag, nSample, uValue))
				{
					FreeString(pszTag);
					return uValue;
				}
				if (GetJScriptTelemetryInterfaceParameterFloatValue(pszTag, nSample, fValue))
				{
					FreeString(pszTag);
					return fValue;
				}
				if (GetJScriptTelemetryInterfaceParameterStringValue(pszTag, nSample, &pszValue))
				{
					FreeString(pszTag);
					return gcnew String(pszValue);
				}
				FreeString(pszTag);
			}
			return nullptr;
		}
		Object^ GetRawValue(String^ szTag, int nSample)
		{
			double  fValue;
			__int64  nValue;
			unsigned __int64  uValue;
			const wchar_t  *pszTag;

			if ((pszTag = AllocString(szTag)))
			{
				if (GetJScriptTelemetryInterfaceParameterRawIntValue(pszTag, nSample, nValue))
				{
					FreeString(pszTag);
					return nValue;
				}
				if (GetJScriptTelemetryInterfaceParameterRawUIntValue(pszTag, nSample, uValue))
				{
					FreeString(pszTag);
					return uValue;
				}
				if (GetJScriptTelemetryInterfaceParameterRawFloatValue(pszTag, nSample, fValue))
				{
					FreeString(pszTag);
					return fValue;
				}
				FreeString(pszTag);
			}
			return nullptr;
		}
		DateTime GetValueTime(String^ szTag, int nSample)
		{
			__int64  tUpdate;
			const wchar_t  *pszTag;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszTag = AllocString(szTag)))
			{
				tUpdate = GetJScriptTelemetryInterfaceParameterValueTime(pszTag, nSample);
				FreeString(pszTag);
				return DateTime(sDateTime.Ticks + 10 * tUpdate);
			}
			return DateTime(0);
		}
		bool SetPastValueSamples(String^ szTag, unsigned short wSamples)
		{
			const wchar_t  *pszTag;

			if ((pszTag = AllocString(szTag)))
			{
				if (SetJScriptTelemetryInterfaceParameterPastValueSamples(pszTag, wSamples))
				{
					FreeString(pszTag);
					return true;
				}
				FreeString(pszTag);
			}
			return false;
		}
		unsigned short GetPastValueSamples(String^ szTag)
		{
			const wchar_t  *pszTag;
			unsigned short  wSamples;

			if ((pszTag = AllocString(szTag)))
			{
				wSamples = GetJScriptTelemetryInterfaceParameterPastValueSamples(pszTag);
				FreeString(pszTag);
				return wSamples;
			}
			return 0;
		}
		Object^ GetPastValue(String^ szTag, int nSample)
		{
			double  fValue;
			__int64  nValue;
			wchar_t  *pszValue;
			unsigned __int64  uValue;
			const wchar_t  *pszTag;

			if ((pszTag = AllocString(szTag)))
			{
				if (GetJScriptTelemetryInterfaceParameterPastIntValue(pszTag, nSample, nValue))
				{
					FreeString(pszTag);
					return nValue;
				}
				if (GetJScriptTelemetryInterfaceParameterPastUIntValue(pszTag, nSample, uValue))
				{
					FreeString(pszTag);
					return uValue;
				}
				if (GetJScriptTelemetryInterfaceParameterPastFloatValue(pszTag, nSample, fValue))
				{
					FreeString(pszTag);
					return fValue;
				}
				if (GetJScriptTelemetryInterfaceParameterPastStringValue(pszTag, nSample, &pszValue))
				{
					FreeString(pszTag);
					return gcnew String(pszValue);
				}
				FreeString(pszTag);
			}
			return nullptr;
		}
		Object^ GetPastRawValue(String^ szTag, int nSample)
		{
			double  fValue;
			__int64  nValue;
			unsigned __int64  uValue;
			const wchar_t  *pszTag;

			if ((pszTag = AllocString(szTag)))
			{
				if (GetJScriptTelemetryInterfaceParameterPastRawIntValue(pszTag, nSample, nValue))
				{
					FreeString(pszTag);
					return nValue;
				}
				if (GetJScriptTelemetryInterfaceParameterPastRawUIntValue(pszTag, nSample, uValue))
				{
					FreeString(pszTag);
					return uValue;
				}
				if (GetJScriptTelemetryInterfaceParameterPastRawFloatValue(pszTag, nSample, fValue))
				{
					FreeString(pszTag);
					return fValue;
				}
				FreeString(pszTag);
			}
			return nullptr;
		}
		DateTime GetPastValueTime(String^ szTag, int nSample)
		{
			__int64  tUpdate;
			const wchar_t  *pszTag;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszTag = AllocString(szTag)))
			{
				tUpdate = GetJScriptTelemetryInterfaceParameterPastValueTime(pszTag, nSample);
				FreeString(pszTag);
				return DateTime(sDateTime.Ticks + 10 * tUpdate);
			}
			return DateTime(0);
		}
		DateTime GetLastUpdateTime(String^ szTag)
		{
			__int64  tUpdate;
			const wchar_t  *pszTag;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszTag = AllocString(szTag)))
			{
				tUpdate = GetJScriptTelemetryInterfaceParameterLastUpdateTime(pszTag);
				FreeString(pszTag);
				return DateTime(sDateTime.Ticks + 10 * tUpdate);
			}
			return DateTime(0);
		}
		DateTime GetLastChangeTime(String^ szTag)
		{
			__int64  tChange;
			const wchar_t  *pszTag;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszTag = AllocString(szTag)))
			{
				tChange = GetJScriptTelemetryInterfaceParameterLastChangeTime(pszTag);
				FreeString(pszTag);
				return DateTime(sDateTime.Ticks + 10 * tChange);
			}
			return DateTime(0);
		}
		unsigned int GetStatus(String^ szTag, int nSample)
		{
			const wchar_t  *pszTag;
			unsigned int  nStatus;

			if ((pszTag = AllocString(szTag)))
			{
				nStatus = GetJScriptTelemetryInterfaceParameterStatus(pszTag, nSample);
				FreeString(pszTag);
				return nStatus;
			}
			return 0;
		}
		bool Lock(String^ szName)
		{
			const wchar_t  *pszName;
			bool  bSuccess;

			if ((pszName = AllocString(szName)))
			{
				bSuccess = LockJScriptTelemetryInterface(pszName);
				FreeString(pszName);
				return bSuccess;
			}
			return false;
		}
		bool Unlock(String^ szName)
		{
			const wchar_t  *pszName;
			bool  bSuccess;

			if ((pszName = AllocString(szName)))
			{
				bSuccess = UnlockJScriptTelemetryInterface(pszName);
				FreeString(pszName);
				return bSuccess;
			}
			return false;
		}
		bool Exit(String^ szName, bool bCode)
		{
			const wchar_t  *pszName;

			if ((pszName = AllocString(szName)))
			{
				ExitJScriptTelemetryInterface(pszName, bCode);
				FreeString(pszName);
				return bCode;
			}
			return false;
		}
	private:
		const wchar_t *AllocString(String^ sz)
		{
			int  nPos;
			int  nLength;
			wchar_t  *psz;

			if ((psz = new wchar_t[sz->Length + 1]))
			{
				for (nPos = 0, nLength = sz->Length, psz[nLength] = EOS; nPos < nLength; nPos++)
				{
					psz[nPos] = sz -> default[nPos];
					continue;
				}
			}
			return psz;
		}
		void FreeString(const wchar_t *psz)
		{
			delete[] psz;
		}
	};
}


#ifdef SATELLITETRACKING
namespace ScriptsSatellitesInterface
{
	public ref class SatelliteTracking : public MarshalByRefObject
	{
	public:
		double CalculateSpacecraftOrbitLongitude(String^ szSpacecraft, unsigned int nNORADID, DateTime tTime)
		{
			double  fLongitude;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraft = AllocString(szSpacecraft)))
			{
				fLongitude = ::CalculateSpacecraftOrbitLongitude(pszSpacecraft, nNORADID, (__int64)(tTime.Ticks - sDateTime.Ticks) / 10000000);
				FreeString(pszSpacecraft);
				return fLongitude;
			}
			return NAN;
		}
		double CalculateSpacecraftOrbitLatitude(String^ szSpacecraft, unsigned int nNORADID, DateTime tTime)
		{
			double  fLongitude;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraft = AllocString(szSpacecraft)))
			{
				fLongitude = ::CalculateSpacecraftOrbitLatitude(pszSpacecraft, nNORADID, (__int64)(tTime.Ticks - sDateTime.Ticks) / 10000000);
				FreeString(pszSpacecraft);
				return fLongitude;
			}
			return NAN;
		}
		double CalculateSpacecraftOrbitAltitude(String^ szSpacecraft, unsigned int nNORADID, DateTime tTime)
		{
			double  fLongitude;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraft = AllocString(szSpacecraft)))
			{
				fLongitude = ::CalculateSpacecraftOrbitAltitude(pszSpacecraft, nNORADID, (__int64)(tTime.Ticks - sDateTime.Ticks) / 10000000);
				FreeString(pszSpacecraft);
				return fLongitude;
			}
			return NAN;
		}
		double CalculateSpacecraftOrbitVelocity(String^ szSpacecraft, unsigned int nNORADID, DateTime tTime)
		{
			double  fLongitude;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraft = AllocString(szSpacecraft)))
			{
				fLongitude = ::CalculateSpacecraftOrbitVelocity(pszSpacecraft, nNORADID, (__int64)(tTime.Ticks - sDateTime.Ticks) / 10000000);
				FreeString(pszSpacecraft);
				return fLongitude;
			}
			return NAN;
		}
		double CalculateSpacecraftPositionX(String^ szSpacecraft, unsigned int nNORADID, DateTime tTime)
		{
			double  x;
			double  y;
			double  z;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraft = AllocString(szSpacecraft)))
			{
				if (::CalculateSpacecraftPosition(pszSpacecraft, nNORADID, (__int64)(tTime.Ticks - sDateTime.Ticks) / 10000000, &x, &y, &z))
				{
					FreeString(pszSpacecraft);
					return x;
				}
				FreeString(pszSpacecraft);
			}
			return NAN;
		}
		double CalculateSpacecraftPositionY(String^ szSpacecraft, unsigned int nNORADID, DateTime tTime)
		{
			double  x;
			double  y;
			double  z;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraft = AllocString(szSpacecraft)))
			{
				if (::CalculateSpacecraftPosition(pszSpacecraft, nNORADID, (__int64)(tTime.Ticks - sDateTime.Ticks) / 10000000, &x, &y, &z))
				{
					FreeString(pszSpacecraft);
					return y;
				}
				FreeString(pszSpacecraft);
			}
			return NAN;
		}
		double CalculateSpacecraftPositionZ(String^ szSpacecraft, unsigned int nNORADID, DateTime tTime)
		{
			double  x;
			double  y;
			double  z;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraft = AllocString(szSpacecraft)))
			{
				if (::CalculateSpacecraftPosition(pszSpacecraft, nNORADID, (__int64)(tTime.Ticks - sDateTime.Ticks) / 10000000, &x, &y, &z))
				{
					FreeString(pszSpacecraft);
					return z;
				}
				FreeString(pszSpacecraft);
			}
			return NAN;
		}
		double CalculateSpacecraftVelocityX(String^ szSpacecraft, unsigned int nNORADID, DateTime tTime)
		{
			double  x;
			double  y;
			double  z;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraft = AllocString(szSpacecraft)))
			{
				if (::CalculateSpacecraftVelocity(pszSpacecraft, nNORADID, (__int64)(tTime.Ticks - sDateTime.Ticks) / 10000000, &x, &y, &z))
				{
					FreeString(pszSpacecraft);
					return x;
				}
				FreeString(pszSpacecraft);
			}
			return NAN;
		}
		double CalculateSpacecraftVelocityY(String^ szSpacecraft, unsigned int nNORADID, DateTime tTime)
		{
			double  x;
			double  y;
			double  z;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraft = AllocString(szSpacecraft)))
			{
				if (::CalculateSpacecraftVelocity(pszSpacecraft, nNORADID, (__int64)(tTime.Ticks - sDateTime.Ticks) / 10000000, &x, &y, &z))
				{
					FreeString(pszSpacecraft);
					return y;
				}
				FreeString(pszSpacecraft);
			}
			return NAN;
		}
		double CalculateSpacecraftVelocityZ(String^ szSpacecraft, unsigned int nNORADID, DateTime tTime)
		{
			double  x;
			double  y;
			double  z;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraft = AllocString(szSpacecraft)))
			{
				if (::CalculateSpacecraftVelocity(pszSpacecraft, nNORADID, (__int64)(tTime.Ticks - sDateTime.Ticks) / 10000000, &x, &y, &z))
				{
					FreeString(pszSpacecraft);
					return z;
				}
				FreeString(pszSpacecraft);
			}
			return NAN;
		}
		DateTime CalculateSpacecraftPassStartTime(String^ szSpacecraft, unsigned int nNORADID, String^ szLocation, double fLocationLongitude, double fLocationLatitude, double fLocationAltitude, DateTime tStartTime, TimeSpan tTimeInterval)
		{
			__int64  tPassStartTime;
			const wchar_t  *pszLocation;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszLocation = AllocString(szLocation)))
			{
				if ((pszSpacecraft = AllocString(szSpacecraft)))
				{
					if ((tPassStartTime = ::CalculateSpacecraftPassStartTime(pszSpacecraft, nNORADID, pszLocation, fLocationLongitude, fLocationLatitude, fLocationAltitude, (__int64)(tStartTime.Ticks - sDateTime.Ticks) / 10000000, (__int64)(tTimeInterval.Ticks / 10000000))) > 0)
					{
						FreeString(pszLocation);
						FreeString(pszSpacecraft);
						return DateTime(sDateTime.Ticks + tPassStartTime * 10);
					}
					FreeString(pszSpacecraft);
				}
				FreeString(pszLocation);
			}
			return DateTime(0);
		}
		DateTime CalculateSpacecraftPassStopTime(String^ szSpacecraft, unsigned int nNORADID, String^ szLocation, double fLocationLongitude, double fLocationLatitude, double fLocationAltitude, DateTime tStartTime, TimeSpan tTimeInterval)
		{
			__int64  tPassStopTime;
			const wchar_t  *pszLocation;
			const wchar_t  *pszSpacecraft;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszLocation = AllocString(szLocation)))
			{
				if ((pszSpacecraft = AllocString(szSpacecraft)))
				{
					if ((tPassStopTime = ::CalculateSpacecraftPassStopTime(pszSpacecraft, nNORADID, pszLocation, fLocationLongitude, fLocationLatitude, fLocationAltitude, (__int64)(tStartTime.Ticks - sDateTime.Ticks) / 10000000, (__int64)(tTimeInterval.Ticks / 10000000))) > 0)
					{
						FreeString(pszLocation);
						FreeString(pszSpacecraft);
						return DateTime(sDateTime.Ticks + tPassStopTime * 10);
					}
					FreeString(pszSpacecraft);
				}
				FreeString(pszLocation);
			}
			return DateTime(0);
		}
		DateTime CalculateSpacecraftInterlinkStartTime(String^ szSpacecraftA, unsigned int nNORADIDA, String^ szSpacecraftB, unsigned int nNORADIDB, DateTime tStartTime, TimeSpan tTimeInterval)
		{
			__int64  tInterlinkStartTime;
			const wchar_t  *pszSpacecraftA;
			const wchar_t  *pszSpacecraftB;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraftA = AllocString(szSpacecraftA)))
			{
				if ((pszSpacecraftB = AllocString(szSpacecraftB)))
				{
					if ((tInterlinkStartTime = ::CalculateSpacecraftInterlinkStartTime(pszSpacecraftA, nNORADIDA, pszSpacecraftB, nNORADIDB, (__int64)(tStartTime.Ticks - sDateTime.Ticks) / 10000000, (__int64)(tTimeInterval.Ticks / 10000000))))
					{
						FreeString(pszSpacecraftA);
						FreeString(pszSpacecraftB);
						return DateTime(sDateTime.Ticks + tInterlinkStartTime * 10);
					}
					FreeString(pszSpacecraftB);
				}
				FreeString(pszSpacecraftA);
			}
			return DateTime(0);
		}
		DateTime CalculateSpacecraftInterlinkStopTime(String^ szSpacecraftA, unsigned int nNORADIDA, String^ szSpacecraftB, unsigned int nNORADIDB, DateTime tStartTime, TimeSpan tTimeInterval)
		{
			__int64  tInterlinkStopTime;
			const wchar_t  *pszSpacecraftA;
			const wchar_t  *pszSpacecraftB;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraftA = AllocString(szSpacecraftA)))
			{
				if ((pszSpacecraftB = AllocString(szSpacecraftB)))
				{
					if ((tInterlinkStopTime = ::CalculateSpacecraftInterlinkStopTime(pszSpacecraftA, nNORADIDA, pszSpacecraftB, nNORADIDB, (__int64)(tStartTime.Ticks - sDateTime.Ticks) / 10000000, (__int64)(tTimeInterval.Ticks / 10000000))))
					{
						FreeString(pszSpacecraftA);
						FreeString(pszSpacecraftB);
						return DateTime(sDateTime.Ticks + tInterlinkStopTime * 10);
					}
					FreeString(pszSpacecraftB);
				}
				FreeString(pszSpacecraftA);
			}
			return DateTime(0);
		}
		DateTime CalculateSpacecraftInterlinkStartTime(String^ szSpacecraftA, unsigned int nNORADIDA, String^ szSpacecraftVia, unsigned int nNORADIDVia, String^ szSpacecraftB, unsigned int nNORADIDB, DateTime tStartTime, TimeSpan tTimeInterval)
		{
			__int64  tInterlinkStartTime;
			const wchar_t  *pszSpacecraftA;
			const wchar_t  *pszSpacecraftB;
			const wchar_t  *pszSpacecraftVia;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraftA = AllocString(szSpacecraftA)))
			{
				if ((pszSpacecraftVia = AllocString(szSpacecraftVia)))
				{
					if ((pszSpacecraftB = AllocString(szSpacecraftB)))
					{
						if ((tInterlinkStartTime = ::CalculateSpacecraftRelaidInterlinkStartTime(pszSpacecraftA, nNORADIDA, pszSpacecraftVia, nNORADIDVia, pszSpacecraftB, nNORADIDB, (__int64)(tStartTime.Ticks - sDateTime.Ticks) / 10000000, (__int64)(tTimeInterval.Ticks / 10000000))))
						{
							FreeString(pszSpacecraftA);
							FreeString(pszSpacecraftB);
							FreeString(pszSpacecraftVia);
							return DateTime(sDateTime.Ticks + tInterlinkStartTime * 10);
						}
						FreeString(pszSpacecraftB);
					}
					FreeString(pszSpacecraftVia);
				}
				FreeString(pszSpacecraftA);
			}
			return DateTime(0);
		}
		DateTime CalculateSpacecraftInterlinkStopTime(String^ szSpacecraftA, unsigned int nNORADIDA, String^ szSpacecraftVia, unsigned int nNORADIDVia, String^ szSpacecraftB, unsigned int nNORADIDB, DateTime tStartTime, TimeSpan tTimeInterval)
		{
			__int64  tInterlinkStopTime;
			const wchar_t  *pszSpacecraftA;
			const wchar_t  *pszSpacecraftB;
			const wchar_t  *pszSpacecraftVia;
			DateTime  sDateTime(1970, 1, 1);

			if ((pszSpacecraftA = AllocString(szSpacecraftA)))
			{
				if ((pszSpacecraftVia = AllocString(szSpacecraftVia)))
				{
					if ((pszSpacecraftB = AllocString(szSpacecraftB)))
					{
						if ((tInterlinkStopTime = ::CalculateSpacecraftRelaidInterlinkStopTime(pszSpacecraftA, nNORADIDA, pszSpacecraftVia, nNORADIDVia, pszSpacecraftB, nNORADIDB, (__int64)(tStartTime.Ticks - sDateTime.Ticks) / 10000000, (__int64)(tTimeInterval.Ticks / 10000000))))
						{
							FreeString(pszSpacecraftA);
							FreeString(pszSpacecraftB);
							FreeString(pszSpacecraftVia);
							return DateTime(sDateTime.Ticks + tInterlinkStopTime * 10);
						}
						FreeString(pszSpacecraftB);
					}
					FreeString(pszSpacecraftVia);
				}
				FreeString(pszSpacecraftA);
			}
			return DateTime(0);
		}
	private:
		const wchar_t *AllocString(String^ sz)
		{
			int  nPos;
			int  nLength;
			wchar_t  *psz;

			if ((psz = new wchar_t[sz->Length + 1]))
			{
				for (nPos = 0, nLength = sz->Length, psz[nLength] = EOS; nPos < nLength; nPos++)
				{
					psz[nPos] = sz -> default[nPos];
					continue;
				}
			}
			return psz;
		}
		void FreeString(const wchar_t *psz)
		{
			delete[] psz;
		}
	};
}
#endif
