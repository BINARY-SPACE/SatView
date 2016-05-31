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
* 2003/07/07 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#define NOSTDLIB
#include "SatView.h"
#undef NOSTDLIB

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#using <mscorlib.dll>

#using <System.dll>

using namespace System;
using namespace System::Reflection;



/////////////////////////////////////////////////////////////////////////////
// CJScriptCodeExecutor

IMPLEMENT_DYNCREATE(CJScriptCodeExecutor, CThread)

CJScriptCodeExecutor::CJScriptCodeExecutor() : CThread()
{
	return;
}

CJScriptCodeExecutor::~CJScriptCodeExecutor()
{
	Stop();
}

BOOL CJScriptCodeExecutor::Start()
{
	return CreateThread();
}

BOOL CJScriptCodeExecutor::Stop()
{
	if (Lock())
	{
		m_szNames.RemoveAll();
		m_szAlerts.RemoveAll();
		m_szEvents.RemoveAll();
		m_szMessages.RemoveAll();
		m_szFileNames.RemoveAll();
		m_szExtraInfos.RemoveAll();
		m_tTimestamps.RemoveAll();
		m_pScripts.RemoveAll();
		Unlock();
	}
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CJScriptCodeExecutor::Run(LPCTSTR pszName, CONST CAutomationScript *pScript)
{
	return Run(pszName, pScript, EMPTYSTRING, EMPTYSTRING, EMPTYSTRING, EMPTYSTRING, 0);
}
BOOL CJScriptCodeExecutor::Run(LPCTSTR pszName, CAutomationScript *pScript, CString &szError)
{
	return Run(pszName, pScript, EMPTYSTRING, EMPTYSTRING, EMPTYSTRING, EMPTYSTRING, 0, szError);
}
BOOL CJScriptCodeExecutor::Run(LPCTSTR pszName, CONST CAutomationScript *pScript, LPCTSTR pszAlert, LPCTSTR pszEvent, LPCTSTR pszMessage, LPCTSTR pszExtraInfo, CONST CTimeTag &tTime)
{
	CAutomationScript  *pAutomationScript;

	if (Lock())
	{
		if ((pAutomationScript = new CAutomationScript))
		{
			if (pAutomationScript->Copy(pScript))
			{
				m_szNames.InsertAt(m_szNames.GetSize(), pszName, 1);
				m_szAlerts.InsertAt(m_szAlerts.GetSize(), pszAlert, 1);
				m_szEvents.InsertAt(m_szEvents.GetSize(), pszEvent, 1);
				m_szMessages.InsertAt(m_szMessages.GetSize(), pszMessage, 1);
				m_szFileNames.InsertAt(m_szFileNames.GetSize(), EMPTYSTRING, 1);
				m_szExtraInfos.InsertAt(m_szExtraInfos.GetSize(), pszExtraInfo, 1);
				m_pScripts.InsertAt(m_pScripts.GetSize(), pAutomationScript, 1);
				m_tTimestamps.InsertAt((INT)m_tTimestamps.GetSize(), tTime);
				m_cUpdate.SetEvent();
				Unlock();
				return TRUE;
			}
			delete pAutomationScript;
		}
		Unlock();
	}
	return FALSE;
}
BOOL CJScriptCodeExecutor::Run(LPCTSTR pszName, CAutomationScript *pScript, LPCTSTR pszAlert, LPCTSTR pszEvent, LPCTSTR pszMessage, LPCTSTR pszExtraInfo, CONST CTimeTag &tTime, CString &szError)
{
	INT  nPos;
	Object^  pClass;
	CString  szEvent;
	CString  szDomain;
	CString  szDirectory;
	CString  szTypeName[2];
	CString  szFileName[3];
	AppDomain^  pAppDomain;
	CFileFindEx  cFileFind[3];
	CStringTools  cStringTools;
	CVersionInfo  cVersionInfo;
	CLogicalDrives  cLogicalDrives;
	array<Object^>^  pArguments;
	array<String^>^  pszResults;
	CSecurityDescriptor  cSecurityDescriptor;

	for (szFileName[0] = GetDatabase()->GetFileName(), szFileName[1] = GetDatabase()->GetUpdateFileName(), szError.Empty(); (cFileFind[0].FindFile(szFileName[0]) || cFileFind[0].FindFile(szFileName[1])) && !cFileFind[0].FindNextFile(); )
	{
		szFileName[0].Format(STRING(IDS_SCRIPTDISPLAYCODE_NORMAL_FILENAME), (LPCTSTR)pScript->GetName());
		szFileName[1].Format(STRING(IDS_SCRIPTDISPLAYCODE_UPDATE_FILENAME), (LPCTSTR)pScript->GetName());
		szFileName[0] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szFileName[0];
		szFileName[1] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szFileName[1];
		if (cFileFind[1].FindFile(szFileName[1]) && !cFileFind[1].FindNextFile())
		{
			CFileEx::SetAttributes(szFileName[0], CFileEx::GetAttributes(szFileName[0]) & ~FILE_ATTRIBUTE_READONLY);
			CFileEx::SetAttributes(szFileName[1], CFileEx::GetAttributes(szFileName[1]) & ~FILE_ATTRIBUTE_READONLY);
			if (CFileEx::Copy(szFileName[1], szFileName[0]) && cFileFind[2].FindFile(szFileName[0]) && !cFileFind[2].FindNextFile())
			{
				if (cSecurityDescriptor.SetRightsOfSystem(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfAdministrators(FILE_ALL_ACCESS) && (cSecurityDescriptor.SetRightsOfSystemOperators(FILE_GENERIC_READ | FILE_GENERIC_WRITE) || cSecurityDescriptor.SetRightsOfPowerUsers(FILE_GENERIC_READ | FILE_GENERIC_WRITE)) && cSecurityDescriptor.SetRightsOfAuthenticatedUsers(FILE_GENERIC_READ) && cSecurityDescriptor.SetRightsOfEveryone(FILE_GENERIC_READ))
				{
					CSecurity::SecureFile(cFileFind[2].GetFilePath(), cSecurityDescriptor);
					CFileEx::Remove(szFileName[1]);
				}
				cFileFind[2].Close();
			}
			CFileEx::SetAttributes(szFileName[0], CFileEx::GetAttributes(szFileName[0]) | FILE_ATTRIBUTE_READONLY);
			CFileEx::SetAttributes(szFileName[1], CFileEx::GetAttributes(szFileName[1]) | FILE_ATTRIBUTE_READONLY);
			cFileFind[1].Close();
		}
		if (cFileFind[1].FindFile(szFileName[0]) && !cFileFind[1].FindNextFile())
		{
			try
			{
				pArguments = gcnew array<Object^>(13);
				for (szDomain.Format(STRING(IDS_SCRIPTASSEMBLY_EXECUTION_DOMAINNAME), (LPCTSTR)cFileFind[1].GetFileTitle(), (LPCTSTR)cVersionInfo.QueryFileDescription()), pAppDomain = AppDomain::CreateDomain(gcnew String(szDomain)), szDirectory = pAppDomain->BaseDirectory; szDirectory.GetAt(szDirectory.GetLength() - 1) == cLogicalDrives.GetPathDelimiter(); )
				{
					szDirectory = szDirectory.Left(szDirectory.GetLength() - 1);
					break;
				}
				szFileName[2].Format(STRING(IDS_SCRIPTLOADERCODE_FILENAME), (LPCTSTR)szDirectory);
				szTypeName[0].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_NAME), (LPCTSTR)pScript->GetName());
				szTypeName[1].Format(STRING(IDS_SCRIPTLANGUAGE_CODE_HEADERTYPENAME), (LPCTSTR)szTypeName[0]);
				pArguments[0] = gcnew String(szFileName[2]);
				pArguments[1] = gcnew String(cFileFind[1].GetFilePath());
				pArguments[2] = gcnew String(szTypeName[1]);
				pArguments[3] = gcnew String(STRING(IDS_SCRIPTLANGUAGE_CODE_FUNCTION_RUN));
				pArguments[4] = gcnew String(pszName);
				pArguments[5] = gcnew String(pScript->GetName() + TAB + pScript->GetTitle());
				pArguments[6] = gcnew String(pScript->GetInputFileName());
				pArguments[7] = gcnew String(pScript->GetOutputFileName());
				pArguments[8] = gcnew String(pszAlert);
				pArguments[9] = gcnew String(pszEvent);
				pArguments[10] = gcnew String(pszMessage);
				pArguments[11] = gcnew String(pszExtraInfo);
				pArguments[12] = gcnew String(cStringTools.ConvertLongIntToString(tTime.GetTimeInSeconds()));
			}
			catch (...)
			{
				AppDomain::Unload(pAppDomain);
				cFileFind[0].Close();
				cFileFind[1].Close();
				delete pArguments;
				return FALSE;
			}
			try
			{
				if ((pClass = pAppDomain->CreateInstanceFromAndUnwrap(gcnew String(szFileName[2]), gcnew String(STRING(IDS_SCRIPTLOADERCODE_CLASSNAME)))))
				{
					if ((pszResults = (array<String^>^) pClass->GetType()->InvokeMember(gcnew String(STRING(IDS_SCRIPTLOADERCODE_METHODNAME)), BindingFlags::InvokeMethod, nullptr, pClass, pArguments)) && !pszResults[2]->ToString()->Length)
					{
						pScript->SetOutputFileName(CString(pszResults[0]->ToString()));
						szEvent = CString(pszResults[1]->ToString());
						AppDomain::Unload(pAppDomain);
						cFileFind[0].Close();
						cFileFind[1].Close();
						delete pArguments;
						delete pszResults;
						return Show(szEvent);
					}
					for (szEvent = CString(pszResults[1]->ToString()), szError = (pszResults[2]->ToString() != gcnew String(SPACE)) ? pszResults[2]->ToString() : gcnew String(EMPTYSTRING); (nPos = szError.Find(EOL)) >= 0; )
					{
						for (szError = szError.Left(nPos) + SPACE + szError.Mid(nPos + 1); szError.GetAt((nPos = nPos + 1)) == EOL; )
						{
							szError = szError.Left(nPos) + szError.Mid(nPos + 1);
							continue;
						}
					}
					Show(szEvent);
				}
				AppDomain::Unload(pAppDomain);
				cFileFind[0].Close();
				cFileFind[1].Close();
				delete pArguments;
				return FALSE;
			}
			catch (...)
			{
				AppDomain::Unload(pAppDomain);
				delete pArguments;
			}
			cFileFind[1].Close();
		}
		cFileFind[0].Close();
		break;
	}
	return FALSE;
}
BOOL CJScriptCodeExecutor::Run(LPCTSTR pszName, LPCTSTR pszFileName, LPCTSTR pszMessage)
{
	if (Lock())
	{
		m_szNames.Add(pszName);
		m_szAlerts.Add(EMPTYSTRING);
		m_szEvents.Add(EMPTYSTRING);
		m_szMessages.Add(pszMessage);
		m_szFileNames.Add(pszFileName);
		m_szExtraInfos.Add(EMPTYSTRING);
		m_pScripts.InsertAt(m_pScripts.GetSize(), NULL, 1);
		m_tTimestamps.Add(0);
		m_cUpdate.SetEvent();
		Unlock();
		return TRUE;
	}
	return FALSE;
}
BOOL CJScriptCodeExecutor::Run(LPCTSTR pszFileName, LPCTSTR pszMessage, CString &szError)
{
	DWORD  cbData;
	CFileEx  cFile;
	CByteArray  nMessage;
	OVERLAPPED  fOverlapped = { 0,0,0,0,0 };

	if (cFile.Open(pszFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite | CFile::shareDenyNone))
	{
		if (LockFileEx(cFile.m_hFile, LOCKFILE_EXCLUSIVE_LOCK, 0, MAXDWORD, MAXDWORD, (LPOVERLAPPED)&fOverlapped))
		{
			nMessage.SetSize(lstrlen(pszMessage));
#ifndef UNICODE
			CopyMemory(nMessage.GetData(), pszMessage, nMessage.GetSize());
#else
			WideCharToMultiByte(CP_ACP, 0, pszMessage, -1, (LPSTR)nMessage.GetData(), (INT)nMessage.GetSize(), (LPCSTR)NULL, (LPBOOL)NULL);
#endif
			for (cFile.SeekToEnd(); WriteFile(cFile.m_hFile, nMessage.GetData(), (DWORD)nMessage.GetSize(), &cbData, (LPOVERLAPPED)NULL); )
			{
				UnlockFileEx(cFile.m_hFile, 0, MAXDWORD, MAXDWORD, &fOverlapped);
				szError.Empty();
				cFile.Close();
				return TRUE;
			}
			UnlockFileEx(cFile.m_hFile, 0, MAXDWORD, MAXDWORD, &fOverlapped);
		}
		cFile.Close();
	}
	szError.Empty();
	return FALSE;
}
int CJScriptCodeExecutor::Run()
{
	INT  nIndex;
	INT  nCount;
	CString  szName;
	CString  szAlert;
	CString  szEvent;
	CString  szMessage;
	CString  szError[2];
	CString  szFileName;
	CString  szExtraInfo;
	CTimeTag  tTimestamp;
	CAutomationScript  *pScript;

	do
	{
		if (Lock())
		{
			for (nIndex = 0, pScript = (CAutomationScript *)NULL; (nCount = (INT)m_pScripts.GetSize()) > 0; )
			{
				szName = m_szNames.GetAt(nIndex);
				szAlert = m_szAlerts.GetAt(nIndex);
				szEvent = m_szEvents.GetAt(nIndex);
				szMessage = m_szMessages.GetAt(nIndex);
				szFileName = m_szFileNames.GetAt(nIndex);
				szExtraInfo = m_szExtraInfos.GetAt(nIndex);
				tTimestamp = m_tTimestamps.GetAt(nIndex);
				pScript = m_pScripts.GetAt(nIndex);
				m_szNames.RemoveAt(nIndex);
				m_szAlerts.RemoveAt(nIndex);
				m_szEvents.RemoveAt(nIndex);
				m_szMessages.RemoveAt(nIndex);
				m_szFileNames.RemoveAt(nIndex);
				m_szExtraInfos.RemoveAt(nIndex);
				m_tTimestamps.RemoveAt(nIndex);
				m_pScripts.RemoveAt(nIndex);
				break;
			}
			Unlock();
		}
		if (nCount > 0)
		{
			if ((pScript != (CAutomationScript *)NULL  &&  !Run(szName, pScript, szAlert, szEvent, szMessage, szExtraInfo, tTimestamp, szError[0])) || (!pScript  &&  !Run(szFileName, szMessage, szError[0])))
			{
				szError[1].Format((pScript != (CAutomationScript *)NULL) ? ((!szError[0].IsEmpty()) ? STRING(IDS_TELEMETRYREPORTS_UPDATEBYSCRIPT_ERROR) : STRING(IDS_TELEMETRYREPORTS_UPDATEBYSCRIPT_FAILURE)) : STRING(IDS_TELEMETRYREPORTS_UPDATEBYDEFAULT_FAILURE), (LPCTSTR)szName, (pScript != (CAutomationScript *)NULL) ? (LPCTSTR)pScript->GetName() : EMPTYSTRING, (pScript != (CAutomationScript *)NULL) ? (LPCTSTR)szError[0] : EMPTYSTRING);
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError[1]);
			}
			m_cUpdate.SetEvent();
			delete pScript;
		}
	} while (Wait(m_cUpdate, FALSE) == WAIT_OBJECT_0 + 1);
	return 0;
}

BOOL CJScriptCodeExecutor::Show(LPCTSTR pszEvent)
{
	CEventObject  *pEvent;

	if ((pEvent = (lstrlen(pszEvent) > 0) ? new CEventObject : (CEventObject *)NULL))
	{
		Translate(pszEvent, pEvent);
		ReportEvent(pEvent);
		return TRUE;
	}
	return((!lstrlen(pszEvent)) ? TRUE : FALSE);
}

BOOL CJScriptCodeExecutor::Translate(LPCTSTR pszEvent, CEventObject *pEvent) CONST
{
	INT  nPos;
	INT  nFlag;
	INT  nFlags;
	WORD  wAge;
	WORD  wGender;
	DWORD  dwPitch;
	DWORD  dwVolume;
	DWORD  dwPlayback;
	CString  szEvent;
	CString  szOption;
	CString  szAdapter;
	CString  szSpeaker;
	CString  szMessage;
	CStringArray  szRecipients;
	CAuditionProfiles  pAuditionProfiles;
	CAuditionProfileInfo  *pAuditionProfileInfo;
	CNotificationProfiles  pNotificationProfiles;
	CNotificationProfileInfo  *pNotificationProfileInfo;

	for (nFlag = 0, nFlags = MAXTELEMETRYREPORTFLAGS - MINTELEMETRYREPORTFLAGS + 1, szEvent = pszEvent, szEvent.MakeUpper(), pEvent->SetCategory(EVENT_CATEGORY_SYSTEM), pEvent->SetType(STRING(IDS_EVENTTYPE_INFORMATIONAL)), pEvent->SetSubtype(EMPTYSTRING), pEvent->SetMessage(pszEvent), pEvent->SetComments(EMPTYSTRING), pEvent->SetUser(GetAccountUserName()), pEvent->SetAudition(AUDIO_NO_SOUND), pEvent->SetNotification(NOTIFICATIONINFO_TYPE_NONE, EMPTYSTRING), pEvent->SetAuditTime(CTime::GetCurrentTime().GetTime()), pEvent->SetAuditColor(VGA_COLOR_BLACK), pEvent->Acknowledge(); nFlag < nFlags; nFlag++)
	{
		if ((nPos = szEvent.Find(STRING(MINTELEMETRYREPORTFLAGS + nFlag))) >= 0 && szEvent.Mid(nPos + lstrlen(STRING(MINTELEMETRYREPORTFLAGS + nFlag))).Find(STRING(MINTELEMETRYREPORTFLAGS + nFlag)) < 0)
		{
			if (!_tcsncmp(STRING(MINTELEMETRYREPORTFLAGS + nFlag), STRING(IDS_TELEMETRYREPORTS_FLAG_CATEGORY), lstrlen(STRING(IDS_TELEMETRYREPORTS_FLAG_CATEGORY))))
			{
				if (!_tcsicmp((szOption = Parse(pszEvent, STRING(MINTELEMETRYREPORTFLAGS + nFlag), nPos)), STRING(IDS_EVENTCATEGORY_SYSTEM)) || !_tcsicmp(szOption, STRING(IDS_EVENTCATEGORY_SPACECRAFT)) || !_tcsicmp(szOption, STRING(IDS_EVENTCATEGORY_USER)))
				{
					pEvent->SetCategory((!_tcsicmp(szOption, STRING(IDS_EVENTCATEGORY_SYSTEM))) ? EVENT_CATEGORY_SYSTEM : ((!_tcsicmp(szOption, STRING(IDS_EVENTCATEGORY_SPACECRAFT))) ? EVENT_CATEGORY_SPACECRAFT : EVENT_CATEGORY_USER));
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTELEMETRYREPORTFLAGS + nFlag), STRING(IDS_TELEMETRYREPORTS_FLAG_TYPE)))
			{
				if (lstrlen((szOption = Parse(pszEvent, STRING(MINTELEMETRYREPORTFLAGS + nFlag), nPos))) > 0)
				{
					pEvent->SetType(szOption);
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTELEMETRYREPORTFLAGS + nFlag), STRING(IDS_TELEMETRYREPORTS_FLAG_SUBTYPE)))
			{
				if (lstrlen((szOption = Parse(pszEvent, STRING(MINTELEMETRYREPORTFLAGS + nFlag), nPos))) > 0)
				{
					pEvent->SetSubtype(szOption);
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTELEMETRYREPORTFLAGS + nFlag), STRING(IDS_TELEMETRYREPORTS_FLAG_MESSAGE)))
			{
				if (lstrlen((szOption = Parse(pszEvent, STRING(MINTELEMETRYREPORTFLAGS + nFlag), nPos))) > 0)
				{
					pEvent->SetMessage(szOption);
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTELEMETRYREPORTFLAGS + nFlag), STRING(IDS_TELEMETRYREPORTS_FLAG_COMMENT)))
			{
				if (lstrlen((szOption = Parse(pszEvent, STRING(MINTELEMETRYREPORTFLAGS + nFlag), nPos))) > 0)
				{
					pEvent->SetComments(szOption);
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTELEMETRYREPORTFLAGS + nFlag), STRING(IDS_TELEMETRYREPORTS_FLAG_AUDITION)))
			{
				if ((pAuditionProfileInfo = (GetAuditionProfiles(pAuditionProfiles) && lstrlen((szOption = Parse(pszEvent, STRING(MINTELEMETRYREPORTFLAGS + nFlag), nPos))) > 0) ? pAuditionProfiles.GetAt(pAuditionProfiles.Find(szOption)) : (CAuditionProfileInfo *)NULL))
				{
					for (pAuditionProfileInfo->GetAdapterInfo(szAdapter, dwVolume, dwPitch, dwPlayback), pAuditionProfileInfo->GetVoiceSound(szSpeaker, wGender, wAge); TRUE; )
					{
						pEvent->SetAudition(pAuditionProfileInfo->GetAudition());
						pEvent->SetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
						pEvent->SetAuditBeep(pAuditionProfileInfo->GetBeepSound());
						pEvent->SetAuditWave(pAuditionProfileInfo->GetWaveSound());
						pEvent->SetAuditVoice(szSpeaker, wGender, wAge);
						break;
					}
					continue;
				}
				pEvent->SetAudition(AUDIO_NO_SOUND);
				continue;
			}
			if (!_tcscmp(STRING(MINTELEMETRYREPORTFLAGS + nFlag), STRING(IDS_TELEMETRYREPORTS_FLAG_NOTIFICATION)))
			{
				if ((pNotificationProfileInfo = (GetNotificationProfiles(pNotificationProfiles) && lstrlen((szOption = Parse(pszEvent, STRING(MINTELEMETRYREPORTFLAGS + nFlag), nPos))) > 0) ? pNotificationProfiles.GetAt(pNotificationProfiles.Find(szOption)) : (CNotificationProfileInfo *)NULL) && pNotificationProfileInfo->GetRecipients(szRecipients) > 0)
				{
					pEvent->SetNotification(pNotificationProfileInfo->GetType(), pNotificationProfileInfo->GetName());
					pEvent->SetNotificationRecipients(szRecipients);
					continue;
				}
				pEvent->SetNotification(NOTIFICATIONINFO_TYPE_NONE, EMPTYSTRING);
				continue;
			}
			if (!_tcscmp(STRING(MINTELEMETRYREPORTFLAGS + nFlag), STRING(IDS_TELEMETRYREPORTS_FLAG_COLOR)))
			{
				if (lstrlen((szOption = Parse(pszEvent, STRING(MINTELEMETRYREPORTFLAGS + nFlag), nPos))) > 0)
				{
					pEvent->SetAuditColor(_ttoi(szOption));
					continue;
				}
				break;
			}
			if (!_tcscmp(STRING(MINTELEMETRYREPORTFLAGS + nFlag), STRING(IDS_TELEMETRYREPORTS_FLAG_BLINK)))
			{
				pEvent->Acknowledge(FALSE);
				continue;
			}
		}
	}
	for (szMessage.Format(STRING(IDS_TELEMETRYREPORTS_FLAG_ERROR), pszEvent); nFlag < nFlags; )
	{
		pEvent->SetCategory(EVENT_CATEGORY_SYSTEM);
		pEvent->SetType(STRING(IDS_EVENTTYPE_WARNING));
		pEvent->SetSubtype(EMPTYSTRING);
		pEvent->SetMessage(szMessage);
		pEvent->SetComments(EMPTYSTRING);
		pEvent->SetUser(GetAccountUserName());
		pEvent->SetAudition(AUDIO_NO_SOUND);
		pEvent->SetNotification(NOTIFICATIONINFO_TYPE_NONE, EMPTYSTRING);
		pEvent->SetAuditTime(CTime::GetCurrentTime().GetTime());
		pEvent->SetAuditColor(VGA_COLOR_BLACK);
		pEvent->Acknowledge();
		return FALSE;
	}
	return TRUE;
}

CString CJScriptCodeExecutor::Parse(LPCTSTR pszEvent, LPCTSTR pszOption, INT &nPos) CONST
{
	INT  nFlag;
	INT  nFlags;
	INT  nLength;
	CString  szOption;

	for (nPos += lstrlen(pszOption), nLength = lstrlen(pszEvent); nPos < nLength; nPos++)
	{
		if (!_istspace(pszEvent[nPos])) break;
		continue;
	}
	if (nPos < nLength  &&  pszEvent[nPos] == STRINGCHAR(IDS_TELEMETRYREPORTS_FLAG_DELIMITER))
	{
		for (szOption.Empty(), nPos = nPos + 1; nPos < nLength; nPos++)
		{
			if (pszEvent[nPos] != pszOption[0])
			{
				szOption += pszEvent[nPos];
				continue;
			}
			for (nFlag = 0, nFlags = MAXTELEMETRYREPORTFLAGS - MINTELEMETRYREPORTFLAGS + 1; nFlag < nFlags; nFlag++)
			{
				if (!_tcsncmp(&pszEvent[nPos], STRING(MINTELEMETRYREPORTFLAGS + nFlag), lstrlen(STRING(MINTELEMETRYREPORTFLAGS + nFlag)))) break;
				continue;
			}
			if (nFlag == nFlags)
			{
				szOption += pszEvent[nPos];
				continue;
			}
			break;
		}
		while (szOption.GetLength() > 0)
		{
			if (szOption.Right(1).GetAt(0) != STRINGCHAR(IDS_TELEMETRYREPORTS_FLAG_DELIMITER))
			{
				szOption = szOption.Left(szOption.GetLength() - 1);
				continue;
			}
			szOption = szOption.Left(szOption.GetLength() - 1);
			break;
		}
		return szOption;
	}
	if (nPos < nLength  &&  pszEvent[nPos] != STRINGCHAR(IDS_TELEMETRYREPORTS_FLAG_DELIMITER))
	{
		for (szOption.Empty(); nPos < nLength; nPos++)
		{
			if (_istdigit(pszEvent[nPos]))
			{
				szOption += pszEvent[nPos];
				continue;
			}
			break;
		}
		return szOption;
	}
	return EMPTYSTRING;
}

BEGIN_MESSAGE_MAP(CJScriptCodeExecutor, CThread)
	//{{AFX_MSG_MAP(CJScriptCodeExecutor)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJScriptCodeExecutor message handlers
