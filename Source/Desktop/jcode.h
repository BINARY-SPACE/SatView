// JCODE.H : JScript Code Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the automation script related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2003/07/07 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __JCODE_H__
#define __JCODE_H__


/////////////////////////////////////////////////////////////////////////////
// CJScriptCodeExecutor thread

class CJScriptCodeExecutor : public CThread
{
	DECLARE_DYNCREATE(CJScriptCodeExecutor)

	// Construction
public:
	CJScriptCodeExecutor();
	~CJScriptCodeExecutor();

	// Attributes
private:
	CStringArray  m_szNames;
	CStringArray  m_szAlerts;
	CStringArray  m_szEvents;
	CStringArray  m_szMessages;
	CStringArray  m_szFileNames;
	CStringArray  m_szExtraInfos;
	CTimeTagArray  m_tTimestamps;
	CAutomationScripts  m_pScripts;
private:
	CEvent  m_cUpdate;

	// Operations
public:
	BOOL Start();
	BOOL Stop();

	BOOL Run(LPCTSTR pszName, CONST CAutomationScript *pScript);
	BOOL Run(LPCTSTR pszName, CAutomationScript *pScript, CString &szError);
	BOOL Run(LPCTSTR pszName, CONST CAutomationScript *pScript, LPCTSTR pszAlert, LPCTSTR pszEvent, LPCTSTR pszMessage, LPCTSTR pszExtraInfo, CONST CTimeTag &tTime);
	BOOL Run(LPCTSTR pszName, CAutomationScript *pScript, LPCTSTR pszAlert, LPCTSTR pszEvent, LPCTSTR pszMessage, LPCTSTR pszExtraInfo, CONST CTimeTag &tTime, CString &szError);
	BOOL Run(LPCTSTR pszName, LPCTSTR pszFileName, LPCTSTR pszMessage);
	BOOL Run(LPCTSTR pszFileName, LPCTSTR pszMessage, CString &szError);

private:
	BOOL Show(LPCTSTR pszEvent);
	BOOL Translate(LPCTSTR pszEvent, CEventObject *pEvent) CONST;
	CString Parse(LPCTSTR pszEvent, LPCTSTR pszOption, INT &nPos) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJScriptCodeExecutor)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJScriptCodeExecutor)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __JCODE_H__
