// THREAD.H : Thread Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the thread related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/11/27 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __THREAD_H__
#define __THREAD_H__


/////////////////////////////////////////////////////////////////////////////
// CThread thread

class AFX_EXT_CLASS CThread : public CWinThread
{
	DECLARE_DYNCREATE(CThread)

	// Construction
public:
	CThread();
	~CThread();

	// Attributes
protected:
	DWORD  m_dwTime;
	DWORD  m_dwTimeout;
	BOOL  m_bInWait;
protected:
	HANDLE  m_hObject;
protected:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL CreateThread(LPVOID pInfo = NULL, INT nPriority = THREAD_PRIORITY_NORMAL, BOOL bSuspended = FALSE);
	DWORD DestroyThread(BOOL bQueue = TRUE);

	DWORD GetThreadID() CONST;
	HANDLE GetThreadHandle() CONST;
	LPVOID GetThreadInfo() CONST;
	DWORD GetThreadStatus() CONST;

	BOOL IsThreadActive() CONST;
	BOOL IsThreadHealthy() CONST;

	DWORD Wait(DWORD dwTimeout = INFINITE, BOOL bQueue = FALSE);
	DWORD Wait(CEvent *pObject, BOOL bAll, DWORD dwTimeout = INFINITE, BOOL bQueue = FALSE);
	DWORD Wait(CEvent *pObjects, DWORD nCount, BOOL bAll, DWORD dwTimeout = INFINITE, BOOL bQueue = FALSE);
	DWORD Wait(HANDLE hObject, BOOL bAll, DWORD dwTimeout = INFINITE, BOOL bQueue = FALSE);
	DWORD Wait(LPHANDLE phObjects, DWORD nCount, BOOL bAll, DWORD dwTimeout = INFINITE, BOOL bQueue = FALSE);

public:
	static BOOL IsSameThread(CWnd *pWnd);

private:
	VOID Initialize();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThread)
public:
	virtual BOOL InitInstance();
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __THREAD_H__
