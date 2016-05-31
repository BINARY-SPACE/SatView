// THREAD.CPP : Thread Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the thread related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/11/27 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CThread

IMPLEMENT_DYNCREATE(CThread, CWinThread)

CThread::CThread() : CWinThread()
{
	m_dwTime = m_dwTimeout = 0;
	m_bInWait = m_bAutoDelete = FALSE;
	m_hObject = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, TRUE, FALSE, (LPCTSTR)NULL);
	m_pCriticalSection = new CCriticalSection;
}

CThread::~CThread()
{
	DestroyThread();
	CloseHandle(m_hObject);
	delete m_pCriticalSection;
}

BOOL CThread::CreateThread(LPVOID pInfo, INT nPriority, BOOL bSuspended)
{
	for (Initialize(); CWinThread::CreateThread(CREATE_SUSPENDED); )
	{
		if (SetThreadPriority(nPriority))
		{
			if (ResetEvent(m_hObject))
			{
				m_pThreadParams = pInfo;
				return((bSuspended || ResumeThread() != (DWORD)-1) ? TRUE : FALSE);
			}
		}
		TerminateThread(m_hThread, -1);
		CloseHandle(m_hThread);
		CommonConstruct();
		m_bAutoDelete = 0;
		break;
	}
	return FALSE;
}

DWORD CThread::DestroyThread(BOOL bQueue)
{
	MSG  sMsg;
	DWORD  dwExitCode;

	if (IsThreadActive())
	{
		for (SetEvent(m_hObject), PostThreadMessage(WM_QUIT, 0, 0); GetThreadID() != GetCurrentThreadId() && ((!bQueue && WaitForSingleObject(m_hThread, INFINITE)) || (bQueue && MsgWaitForMultipleObjects(1, &m_hThread, FALSE, INFINITE, QS_PAINT | QS_TIMER | QS_POSTMESSAGE | QS_SENDMESSAGE) == WAIT_OBJECT_0 + 1)); )
		{
			if (PeekMessage(&sMsg, (HWND)NULL, 0, 0, PM_QS_PAINT | PM_QS_POSTMESSAGE | PM_QS_SENDMESSAGE | PM_REMOVE))
			{
				if (!AfxPreTranslateMessage(&sMsg))
				{
					TranslateMessage(&sMsg);
					DispatchMessage(&sMsg);
				}
			}
			RestoreWaitCursor();
		}
		dwExitCode = GetThreadStatus();
		CloseHandle(m_hThread);
		CommonConstruct();
		m_bAutoDelete = 0;
		return dwExitCode;
	}
	return 0;
}

BOOL CThread::InitInstance()
{
	return TRUE;
}

DWORD CThread::GetThreadID() CONST
{
	return m_nThreadID;
}

HANDLE CThread::GetThreadHandle() CONST
{
	return m_hThread;
}

LPVOID CThread::GetThreadInfo() CONST
{
	return m_pThreadParams;
}

DWORD CThread::GetThreadStatus() CONST
{
	DWORD  dwExitCode;

	return((GetExitCodeThread(m_hThread, &dwExitCode)) ? dwExitCode : (DWORD)-1);
}

BOOL CThread::IsThreadActive() CONST
{
	return((GetThreadStatus() == STILL_ACTIVE) ? TRUE : FALSE);
}

BOOL CThread::IsThreadHealthy() CONST
{
	DWORD  dwTime;

	return((IsThreadActive()) ? ((m_dwTimeout > 0 && !m_bInWait) ? ((dwTime = GetCurrentTime()) < m_dwTime) ? (MAXDWORD - m_dwTime + dwTime + 1 < m_dwTimeout) : (dwTime - m_dwTime < m_dwTimeout) : TRUE) : FALSE);
}

BOOL CThread::IsSameThread(CWnd *pWnd)
{
	return((GetWindowThreadProcessId(pWnd->GetSafeHwnd(), (LPDWORD)NULL) == GetCurrentThreadId()) ? TRUE : FALSE);
}

DWORD CThread::Wait(DWORD dwTimeout, BOOL bQueue)
{
	MSG  sMsg;
	BOOL  bMessage;
	DWORD  dwTime[2];
	DWORD  dwWaitCode;
	DWORD  dwWaitDelay;
	DWORD  dwWaitTime[2];
	DWORD  dwWaitInterval[2];

	for (dwWaitInterval[0] = dwTimeout, dwWaitTime[0] = dwTime[0] = GetTickCount(), SwitchToThread(), dwTime[1] = GetTickCount(), m_bInWait = TRUE, dwWaitCode = WaitForSingleObject(m_hObject, (dwWaitDelay = (dwTime[1] >= dwTime[0]) ? (dwTime[1] - dwTime[0]) : (MAXDWORD - dwTime[0] + dwTime[1] + 1))), dwWaitInterval[0] = (dwWaitInterval[0] != INFINITE) ? ((dwWaitInterval[0] > 2 * dwWaitDelay) ? (dwWaitInterval[0] - 2 * dwWaitDelay) : 0) : dwWaitInterval[0]; (dwWaitCode = ((dwWaitCode == WAIT_TIMEOUT || dwWaitCode == WAIT_OBJECT_0 + 1) && (dwWaitInterval[0] > 0 || bQueue)) ? MsgWaitForMultipleObjectsEx(1, &m_hObject, dwWaitInterval[0], QS_ALLINPUT, MWMO_INPUTAVAILABLE) : ((dwWaitCode != WAIT_TIMEOUT && dwWaitCode != WAIT_OBJECT_0 + 1) ? dwWaitCode : WAIT_TIMEOUT)) == WAIT_OBJECT_0 + 1; dwWaitInterval[1] = ((dwWaitTime[1] = GetTickCount()) >= dwWaitTime[0]) ? (dwWaitTime[1] - dwWaitTime[0]) : (MAXDWORD - dwWaitTime[0] + dwWaitTime[1] + 1), dwWaitInterval[0] = (dwTimeout != INFINITE) ? ((dwWaitInterval[0] >= dwWaitInterval[1]) ? (dwWaitInterval[0] - dwWaitInterval[1]) : 0) : dwTimeout, dwWaitTime[0] = dwWaitTime[1], m_bInWait = TRUE)
	{
		for (m_dwTime = GetCurrentTime(), m_bInWait = FALSE; (bMessage = PeekMessage(&sMsg, (HWND)NULL, 0, 0, PM_REMOVE)); )
		{
			if (!AfxPreTranslateMessage(&sMsg))
			{
				TranslateMessage(&sMsg);
				DispatchMessage(&sMsg);
			}
			break;
		}
		if (dwWaitCode == WAIT_TIMEOUT  &&  !bMessage  &&  bQueue) break;
	}
	return(((m_dwTime = GetCurrentTime()) >= 0) ? dwWaitCode : WAIT_FAILED);
}
DWORD CThread::Wait(CEvent *pObject, BOOL bAll, DWORD dwTimeout, BOOL bQueue)
{
	return Wait(pObject->m_hObject, bAll, dwTimeout, bQueue);
}
DWORD CThread::Wait(CEvent *pObjects, DWORD nCount, BOOL bAll, DWORD dwTimeout, BOOL bQueue)
{
	DWORD  nObject;
	DWORD  nObjects;
	HANDLE  hObjects[MAXIMUM_WAIT_OBJECTS];

	for (nObject = 0, nObjects = min(nCount, sizeof(hObjects) / sizeof(HANDLE)); nObject < nObjects; nObject++)
	{
		hObjects[nObject] = pObjects[nObject].m_hObject;
		continue;
	}
	return Wait(hObjects, nObjects, bAll, dwTimeout, bQueue);
}
DWORD CThread::Wait(HANDLE hObject, BOOL bAll, DWORD dwTimeout, BOOL bQueue)
{
	HANDLE  hObjects[1] = { hObject };

	return Wait(hObjects, 1, bAll, dwTimeout, bQueue);
}
DWORD CThread::Wait(LPHANDLE phObjects, DWORD nCount, BOOL bAll, DWORD dwTimeout, BOOL bQueue)
{
	MSG  sMsg;
	BOOL  bMessage;
	DWORD  nObjects;
	DWORD  dwTime[2];
	DWORD  dwWaitCode;
	DWORD  dwWaitDelay;
	DWORD  dwWaitTime[2];
	DWORD  dwWaitInterval[2];
	HANDLE  hObjects[MAXIMUM_WAIT_OBJECTS + 1] = { m_hObject };

	for (dwWaitInterval[0] = dwTimeout, dwWaitTime[0] = dwTime[0] = GetTickCount(), SwitchToThread(), dwTime[1] = GetTickCount(), CopyMemory(&hObjects[1], phObjects, (nObjects = min(nCount, sizeof(hObjects) / sizeof(HANDLE) - 1))*sizeof(HANDLE)), m_bInWait = TRUE, dwWaitCode = WaitForMultipleObjects(nObjects + 1, hObjects, bAll, (dwWaitDelay = (dwTime[1] >= dwTime[0]) ? (dwTime[1] - dwTime[0]) : (MAXDWORD - dwTime[0] + dwTime[1] + 1))), dwWaitInterval[0] = (dwWaitInterval[0] != INFINITE) ? ((dwWaitInterval[0] > 2 * dwWaitDelay) ? (dwWaitInterval[0] - 2 * dwWaitDelay) : 0) : dwWaitInterval[0]; (dwWaitCode = ((dwWaitCode == WAIT_TIMEOUT || dwWaitCode == WAIT_OBJECT_0 + nObjects + 1) && (dwWaitInterval[0] > 0 || bQueue) && !bAll) ? MsgWaitForMultipleObjectsEx(nObjects + 1, hObjects, dwWaitInterval[0], QS_ALLINPUT, MWMO_INPUTAVAILABLE) : (((dwWaitCode != WAIT_TIMEOUT && dwWaitCode != WAIT_OBJECT_0 + nObjects + 1) || bAll) ? dwWaitCode : WAIT_TIMEOUT)) == WAIT_OBJECT_0 + nObjects + 1 || (bAll && dwWaitInterval[0] > 0 && dwWaitCode == WAIT_TIMEOUT); dwWaitInterval[1] = ((dwWaitTime[1] = GetTickCount()) >= dwWaitTime[0]) ? (dwWaitTime[1] - dwWaitTime[0]) : (MAXDWORD - dwWaitTime[0] + dwWaitTime[1] + 1), dwWaitInterval[0] = (dwTimeout != INFINITE) ? ((dwWaitInterval[0] >= dwWaitInterval[1]) ? (dwWaitInterval[0] - dwWaitInterval[1]) : 0) : dwTimeout, dwWaitTime[0] = dwWaitTime[1], dwWaitCode = (bAll) ? WaitForMultipleObjects(nObjects + 1, hObjects, bAll, (!HIWORD(GetQueueStatus(QS_ALLINPUT))) ? min(dwWaitDelay, dwWaitInterval[0]) : 0) : dwWaitCode, m_bInWait = TRUE)
	{
		for (m_dwTime = GetCurrentTime(), m_bInWait = FALSE; (bMessage = PeekMessage(&sMsg, (HWND)NULL, 0, 0, PM_REMOVE)); )
		{
			if (!AfxPreTranslateMessage(&sMsg))
			{
				TranslateMessage(&sMsg);
				DispatchMessage(&sMsg);
			}
			break;
		}
		if (dwWaitCode == WAIT_TIMEOUT  &&  !bMessage  &&  bQueue) break;
	}
	return(((m_dwTime = GetCurrentTime()) >= 0) ? dwWaitCode : WAIT_FAILED);
}

BOOL CThread::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CThread::Unlock()
{
	return m_pCriticalSection->Unlock();
}

VOID CThread::Initialize()
{
	INT  nTimeout;

	for (m_dwTime = GetCurrentTime(), m_dwTimeout = (SystemParametersInfo(SPI_GETHUNGAPPTIMEOUT, 0, &nTimeout, 0)) ? (DWORD)nTimeout : 0; m_hThread != (HANDLE)NULL; )
	{
		CloseHandle(m_hThread);
		break;
	}
	CommonConstruct();
	m_bAutoDelete = FALSE;
}

BEGIN_MESSAGE_MAP(CThread, CWinThread)
	//{{AFX_MSG_MAP(CThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThread message handlers
