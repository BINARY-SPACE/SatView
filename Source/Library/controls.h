// CONTROLS.H : Custom Control Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the custom control related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1993/07/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include "timekey.h"


/////////////////////////////////////////////////////////////////////////////
// CMimicsControls

class AFX_EXT_CLASS CMimicsControls : public CObject
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	static BOOL RegisterMimicsControls();
	static BOOL UnregisterMimicsControls();
};

// Specify the associated inline definitions
inline BOOL RegisterMimicsControls()
{
	return CMimicsControls::RegisterMimicsControls();
}
inline BOOL UnregisterMimicsControls()
{
	return CMimicsControls::UnregisterMimicsControls();
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CCustomControls

class AFX_EXT_CLASS CCustomControls : public CObject
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	static BOOL RegisterCustomControls();
	static BOOL UnregisterCustomControls();

	static CRuntimeClass* GetCustomControlBaseClass(CRuntimeClass* pClass);

	static CFont* GetCustomControlFont(CONST CWnd* pControl);
};

// Specify the associated inline definitions
inline BOOL RegisterCustomControls()
{
	return CCustomControls::RegisterCustomControls();
}
inline BOOL UnregisterCustomControls()
{
	return CCustomControls::UnregisterCustomControls();
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimpleEdit window

class AFX_EXT_CLASS CSimpleEdit : public CEdit
{
	DECLARE_DYNCREATE(CSimpleEdit)

	// Construction
public:
	CSimpleEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	CString  m_szContents;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_MULTILINE | WS_BORDER | WS_VISIBLE | WS_VSCROLL);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSimpleEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceSimpleEdit window

class CResourceSimpleEdit : public CSimpleEdit
{
	DECLARE_DYNCREATE(CResourceSimpleEdit)

	// Construction
public:
	CResourceSimpleEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceSimpleEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceSimpleEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CNumberEdit window

// Specify the numerical edit control message identifiers
#define NEM_SETBASE   (WM_USER+1)
#define NEM_GETBASE   (WM_USER+2)
#define NEM_SETRANGE   (WM_USER+3)
#define NEM_GETRANGE   (WM_USER+4)
#define NEM_SETPOS   (WM_USER+5)
#define NEM_GETPOS   (WM_USER+6)
#define NEM_SETSEL   (WM_USER+7)
#define NEM_GETSEL   (WM_USER+8)
#define NEM_CHECK   (WM_USER+9)

class AFX_EXT_CLASS CNumberEdit : public CEdit
{
	DECLARE_DYNCREATE(CNumberEdit)

	// Construction
public:
	CNumberEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	UINT  m_nBase;
	UINT  m_nDigits;
	BOOL  m_bMinusZero;
	BOOL  m_bAutoCompletion;
	LONGLONG  m_nMin;
	LONGLONG  m_nMax;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_LEFT | WS_BORDER | WS_VISIBLE | WS_TABSTOP, BOOL bMinusZero = FALSE);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	BOOL SetBase(UINT nBase, UINT nDigits = 0);
	BOOL GetBase(UINT& nBase, UINT& nDigits) CONST;
	BOOL SetRange(LONGLONG nMin, LONGLONG nMax);
	BOOL GetRange(LONGLONG& nMin, LONGLONG& nMax) CONST;
	BOOL SetPos(LONGLONG nPos, BOOL bNotify = FALSE);
	LONGLONG GetPos(BOOL bLimits = TRUE) CONST;
	BOOL SetSel(INT nStartPos, INT nStopPos);
	BOOL GetSel(INT& nStartPos, INT& nStopPos) CONST;
	DWORD GetSel() CONST;

	VOID EnableMinusZero(BOOL bEnable = TRUE);
	BOOL IsMinusZeroEnabled() CONST;
	BOOL IsMinusZero() CONST;
	VOID EnableAutoCompletion(BOOL bEnable = TRUE);
	BOOL IsAutoCompletionEnabled() CONST;

	BOOL Check() CONST;

private:
	VOID Format();

	BOOL CheckMinusZero(LPCTSTR pszNumber) CONST;
	CString ConstructMinusZero(UINT nDigits = 0) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumberEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CNumberEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg LRESULT OnFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNumber(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBase(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetBase(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetPos(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetPos(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCheck(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated helper functions
__declspec(dllexport) BOOL Numberedit_SetBase(CWnd* pCtrl, UINT nBase, UINT nDigits);
__declspec(dllexport) BOOL Numberedit_GetBase(CWnd* pCtrl, UINT& nBase, UINT& nDigits);
__declspec(dllexport) BOOL Numberedit_SetRange(CWnd* pCtrl, LONGLONG nMin, LONGLONG nMax);
__declspec(dllexport) BOOL Numberedit_GetRange(CWnd* pCtrl, LONGLONG& nMin, LONGLONG& nMax);
__declspec(dllexport) BOOL Numberedit_SetPos(CWnd* pCtrl, LONGLONG nPos, BOOL bNotify = FALSE);
__declspec(dllexport) LONGLONG Numberedit_GetPos(CWnd* pCtrl, BOOL bLimits = TRUE);
__declspec(dllexport) BOOL Numberedit_SetSel(CWnd* pCtrl, INT nStartPos, INT nStopPos);
__declspec(dllexport) BOOL Numberedit_GetSel(CWnd* pCtrl, INT& nStartPos, INT& nStopPos);
__declspec(dllexport) DWORD Numberedit_GetSel(CWnd* pCtrl);
__declspec(dllexport) BOOL Numberedit_Check(CWnd* pCtrl);

// Specify the associated inline definitions
inline BOOL CNumberEdit::SetBase(UINT nBase, UINT nDigits)
{
	return(Numberedit_SetBase(CNumberEdit::FromHandle(GetSafeHwnd()), nBase, nDigits));
}
inline BOOL CNumberEdit::GetBase(UINT& nBase, UINT& nDigits) CONST
{
	return(Numberedit_GetBase(CNumberEdit::FromHandle(GetSafeHwnd()), nBase, nDigits));
}
inline BOOL CNumberEdit::SetRange(LONGLONG nMin, LONGLONG nMax)
{
	return(Numberedit_SetRange(CNumberEdit::FromHandle(GetSafeHwnd()), nMin, nMax));
}
inline BOOL CNumberEdit::GetRange(LONGLONG& nMin, LONGLONG& nMax) CONST
{
	return(Numberedit_GetRange(CNumberEdit::FromHandle(GetSafeHwnd()), nMin, nMax));
}
inline BOOL CNumberEdit::SetPos(LONGLONG nPos, BOOL bNotify)
{
	return(Numberedit_SetPos(CNumberEdit::FromHandle(GetSafeHwnd()), nPos, bNotify));
}
inline LONGLONG CNumberEdit::GetPos(BOOL bLimits) CONST
{
	return(Numberedit_GetPos(CNumberEdit::FromHandle(GetSafeHwnd()), bLimits));
}
inline BOOL CNumberEdit::SetSel(INT nStartPos, INT nStopPos)
{
	return(Numberedit_SetSel(CNumberEdit::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}
inline BOOL CNumberEdit::GetSel(INT& nStartPos, INT& nStopPos) CONST
{
	return(Numberedit_GetSel(CNumberEdit::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}
inline DWORD CNumberEdit::GetSel() CONST
{
	return(Numberedit_GetSel(CNumberEdit::FromHandle(GetSafeHwnd())));
}
inline BOOL CNumberEdit::Check() CONST
{
	return(Numberedit_Check(CNumberEdit::FromHandle(GetSafeHwnd())));
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceNumberEdit window

class CResourceNumberEdit : public CNumberEdit
{
	DECLARE_DYNCREATE(CResourceNumberEdit)

	// Construction
public:
	CResourceNumberEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceNumberEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceNumberEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTextEdit window

// Specify the text edit control message identifiers
#define TEM_ADDTEXT   (WM_USER+10)
#define TEM_INSERTTEXT   (WM_USER+11)
#define TEM_FINDTEXT   (WM_USER+12)
#define TEM_SELECTTEXT   (WM_USER+13)
#define TEM_DELETETEXT   (WM_USER+14)
#define TEM_RESETTEXT   (WM_USER+15)
#define TEM_SETPOS   (WM_USER+16)
#define TEM_GETPOS   (WM_USER+17)
#define TEM_SETSEL   (WM_USER+18)
#define TEM_GETSEL   (WM_USER+19)
#define TEM_CHECK   (WM_USER+20)

class AFX_EXT_CLASS CTextEdit : public CEdit
{
	DECLARE_DYNCREATE(CTextEdit)

	// Construction
public:
	CTextEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	CStringArray  m_szNames;
	BOOL  m_bAutoCompletion;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_LEFT | WS_BORDER | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	INT AddText(LPCTSTR pszText);
	VOID InsertText(INT nIndex, LPCTSTR pszText);
	INT FindText(INT nIndex, LPCTSTR pszText) CONST;
	BOOL SelectText(INT nIndex, LPCTSTR pszText);
	BOOL DeleteText(LPCTSTR pszText);
	VOID ResetText();
	BOOL SetPos(INT nPos, BOOL bNotify = FALSE);
	INT GetPos() CONST;
	BOOL SetSel(INT nStartPos, INT nStopPos);
	VOID GetSel(INT& nStartPos, INT& nStopPos) CONST;
	DWORD GetSel() CONST;

	VOID EnableAutoCompletion(BOOL bEnable = TRUE);
	BOOL IsAutoCompletionEnabled() CONST;

	BOOL Check() CONST;

private:
	VOID Format();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTextEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg LRESULT OnFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAddText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInsertText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFindText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelectText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDeleteText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnResetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetPos(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetPos(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCheck(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline INT CTextEdit::AddText(LPCTSTR pszText)
{
	return((INT)SendMessage(TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)pszText));
}
inline VOID CTextEdit::InsertText(INT nIndex, LPCTSTR pszText)
{
	SendMessage(TEM_INSERTTEXT, nIndex, (LPARAM)pszText);
}
inline INT CTextEdit::FindText(INT nIndex, LPCTSTR pszText) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), TEM_FINDTEXT, nIndex, (LPARAM)pszText));
}
inline BOOL CTextEdit::SelectText(INT nIndex, LPCTSTR pszText)
{
	return((BOOL)SendMessage(TEM_SELECTTEXT, nIndex, (LPARAM)pszText));
}
inline BOOL CTextEdit::DeleteText(LPCTSTR pszText)
{
	return((BOOL)SendMessage(TEM_DELETETEXT, (WPARAM)NULL, (LPARAM)pszText));
}
inline VOID CTextEdit::ResetText()
{
	SendMessage(TEM_RESETTEXT);
}
inline BOOL CTextEdit::SetPos(INT nPos, BOOL bNotify)
{
	return((BOOL)SendMessage(TEM_SETPOS, nPos, bNotify));
}
inline INT CTextEdit::GetPos() CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), TEM_GETPOS, (WPARAM)NULL, (LPARAM)NULL));
}
inline BOOL CTextEdit::SetSel(INT nStartPos, INT nStopPos)
{
	return((BOOL)SendMessage(TEM_SETSEL, nStartPos, nStopPos));
}
inline VOID CTextEdit::GetSel(INT& nStartPos, INT& nStopPos) CONST
{
	::SendMessage(GetSafeHwnd(), TEM_GETSEL, (WPARAM)& nStartPos, (LPARAM)& nStopPos);
}
inline DWORD CTextEdit::GetSel() CONST
{
	return CEdit::GetSel();
}
inline BOOL CTextEdit::Check() CONST
{
	return((BOOL) ::SendMessage(GetSafeHwnd(), TEM_CHECK, (WPARAM)NULL, (LPARAM)NULL));
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceTextEdit window

class CResourceTextEdit : public CTextEdit
{
	DECLARE_DYNCREATE(CResourceTextEdit)

	// Construction
public:
	CResourceTextEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceTextEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceTextEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDPLCodeEdit window

#define DPLCODEEDIT_TYPE_DEFAULT   0
#define DPLCODEEDIT_TYPE_PLAIN   1
#define DPLCODEEDIT_TYPE_OL   2

class AFX_EXT_CLASS CDPLCodeEdit : public CRichEditCtrl
{
	DECLARE_DYNCREATE(CDPLCodeEdit)

	// Construction
public:
	CDPLCodeEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	UINT  m_nType;
	BOOL  m_bSelection;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP);

	VOID SetRenderType(UINT nType = DPLCODEEDIT_TYPE_DEFAULT);
	UINT GetRenderType() CONST;

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

protected:
	VOID RenderCode();

public:
	static VOID RenderCode(CRichEditCtrl* pEdit, CFont* pFont, UINT nType = DPLCODEEDIT_TYPE_DEFAULT, BOOL bSelection = TRUE);
private:
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat);
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDPLCodeEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDPLCodeEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEditchange();
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceDPLCodeEdit window

class CResourceDPLCodeEdit : public CDPLCodeEdit
{
	DECLARE_DYNCREATE(CResourceDPLCodeEdit)

	// Construction
public:
	CResourceDPLCodeEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceDPLCodeEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceDPLCodeEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMDLCodeEdit window

class AFX_EXT_CLASS CMDLCodeEdit : public CRichEditCtrl
{
	DECLARE_DYNCREATE(CMDLCodeEdit)

	// Construction
public:
	CMDLCodeEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	BOOL  m_bSelection;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

protected:
	VOID RenderCode();

public:
	static VOID RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection = TRUE);
private:
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat);
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDLCodeEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMDLCodeEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEditchange();
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMDLCodeEdit window

class CResourceMDLCodeEdit : public CMDLCodeEdit
{
	DECLARE_DYNCREATE(CResourceMDLCodeEdit)

	// Construction
public:
	CResourceMDLCodeEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMDLCodeEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMDLCodeEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTPLCodeEdit window

// Specify the telecommand procedure language edit control styles
#define TPLS_STANDARD   0x0000
#define TPLS_EXPRESSION   0x4000

class AFX_EXT_CLASS CTPLCodeEdit : public CRichEditCtrl
{
	DECLARE_DYNCREATE(CTPLCodeEdit)

	// Construction
public:
	CTPLCodeEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	BOOL  m_bSelection;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

protected:
	VOID RenderCode();

public:
	static VOID RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection = TRUE);
private:
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat);
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTPLCodeEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTPLCodeEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEditchange();
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceTPLCodeEdit window

class CResourceTPLCodeEdit : public CTPLCodeEdit
{
	DECLARE_DYNCREATE(CResourceTPLCodeEdit)

	// Construction
public:
	CResourceTPLCodeEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceTPLCodeEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceTPLCodeEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptCodeEdit window

class AFX_EXT_CLASS CScriptCodeEdit : public CRichEditCtrl
{
	DECLARE_DYNCREATE(CScriptCodeEdit)

	// Construction
public:
	CScriptCodeEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	BOOL  m_bSelection;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

protected:
	VOID RenderCode();

public:
	static VOID RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection = TRUE);
private:
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat);
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptCodeEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CScriptCodeEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEditchange();
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceScriptCodeEdit window

class CResourceScriptCodeEdit : public CScriptCodeEdit
{
	DECLARE_DYNCREATE(CResourceScriptCodeEdit)

	// Construction
public:
	CResourceScriptCodeEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceScriptCodeEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceScriptCodeEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCSequenceXmlEdit window

class AFX_EXT_CLASS CTCSequenceXmlEdit : public CRichEditCtrl
{
	DECLARE_DYNCREATE(CTCSequenceXmlEdit)

	// Construction
public:
	CTCSequenceXmlEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	BOOL  m_bSelection;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

protected:
	VOID RenderCode();

public:
	static VOID RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection = TRUE);
private:
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat);
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCSequenceXmlEdit)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCSequenceXmlEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEditchange();
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceTCSequenceXmlEdit window

class CResourceTCSequenceXmlEdit : public CTCSequenceXmlEdit
{
	DECLARE_DYNCREATE(CResourceTCSequenceXmlEdit)

	// Construction
public:
	CResourceTCSequenceXmlEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceTCSequenceXmlEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceTCSequenceXmlEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CANDXmlEdit window

class AFX_EXT_CLASS CANDXmlEdit : public CRichEditCtrl
{
	DECLARE_DYNCREATE(CANDXmlEdit)

	// Construction
public:
	CANDXmlEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	BOOL  m_bSelection;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

protected:
	VOID RenderCode();

public:
	static VOID RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection = TRUE);
private:
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat);
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CANDXmlEdit)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CANDXmlEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEditchange();
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceANDXmlEdit window

class CResourceANDXmlEdit : public CANDXmlEdit
{
	DECLARE_DYNCREATE(CResourceANDXmlEdit)

	// Construction
public:
	CResourceANDXmlEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceANDXmlEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceANDXmlEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDXmlEdit window

class AFX_EXT_CLASS CGRDXmlEdit : public CRichEditCtrl
{
	DECLARE_DYNCREATE(CGRDXmlEdit)

	// Construction
public:
	CGRDXmlEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	BOOL  m_bSelection;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

protected:
	VOID RenderCode();

public:
	static VOID RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection = TRUE);
private:
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat);
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGRDXmlEdit)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDXmlEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEditchange();
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceGRDXmlEdit window

class CResourceGRDXmlEdit : public CGRDXmlEdit
{
	DECLARE_DYNCREATE(CResourceGRDXmlEdit)

	// Construction
public:
	CResourceGRDXmlEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceGRDXmlEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceGRDXmlEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPODXmlEdit window

class AFX_EXT_CLASS CPODXmlEdit : public CRichEditCtrl
{
	DECLARE_DYNCREATE(CPODXmlEdit)

	// Construction
public:
	CPODXmlEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	BOOL  m_bSelection;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN | WS_BORDER | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

protected:
	VOID RenderCode();

public:
	static VOID RenderCode(CRichEditCtrl* pEdit, CFont* pFont, BOOL bSelection = TRUE);
private:
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat);
	static VOID RenderCode(CRichEditCtrl* pEdit, INT nStartPos, INT nStopPos, CONST CHARFORMAT2* pFormat, CONST PARAFORMAT2* pParagraph);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPODXmlEdit)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPODXmlEdit)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEditchange();
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourcePODXmlEdit window

class CResourcePODXmlEdit : public CPODXmlEdit
{
	DECLARE_DYNCREATE(CResourcePODXmlEdit)

	// Construction
public:
	CResourcePODXmlEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourcePODXmlEdit)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourcePODXmlEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimpleListBox window

class AFX_EXT_CLASS CSimpleListBox : public CListBox
{
	DECLARE_DYNCREATE(CSimpleListBox)

	// Construction
public:
	CSimpleListBox();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	CStringArray  m_szItems;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, INT nID, DWORD dwStyle = LBS_DISABLENOSCROLL | LBS_NOINTEGRALHEIGHT | LBS_SORT | WS_BORDER | WS_VISIBLE);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleListBox)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSimpleListBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceSimpleListBox window

class CResourceSimpleListBox : public CSimpleListBox
{
	DECLARE_DYNCREATE(CResourceSimpleListBox)

	// Construction
public:
	CResourceSimpleListBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceSimpleListBox)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceSimpleListBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CColorsComboBox window

// Specify the colors combobox control message identifiers
#define CCB_ADDCOLOR   (WM_USER+21)
#define CCB_INSERTCOLOR   (WM_USER+22)
#define CCB_GETCOLOR   (WM_USER+23)
#define CCB_FINDCOLOR   (WM_USER+24)
#define CCB_SELECTCOLOR   (WM_USER+25)
#define CCB_DELETECOLOR   (WM_USER+26)
#define CCB_RESETCOLORS   (WM_USER+27)
// Specify the colors combobox control styles
#define CCBS_STANDARD   0x0000
#define CCBS_CUSTOM   0x0004

class AFX_EXT_CLASS CColorsComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CColorsComboBox)

	// Construction
public:
	CColorsComboBox();

	// Attributes
protected:
	DWORD  m_dwStyle;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	INT AddColor(COLORREF nColor);
	INT InsertColor(INT nIndex, COLORREF nColor);
	COLORREF GetColor(INT nIndex) CONST;
	INT FindColor(INT nIndex, COLORREF nColor) CONST;
	INT SelectColor(INT nIndex, COLORREF nColor);
	INT DeleteColor(COLORREF nColor);
	VOID ResetColors();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorsComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorsComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnColor();
	afx_msg LRESULT OnAddColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInsertColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFindColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelectColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDeleteColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnResetColors(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline INT CColorsComboBox::AddColor(COLORREF nColor)
{
	return((INT)SendMessage(CCB_ADDCOLOR, (WPARAM)NULL, (LPARAM)nColor));
}
inline INT CColorsComboBox::InsertColor(INT nIndex, COLORREF nColor)
{
	return((INT)SendMessage(CCB_INSERTCOLOR, nIndex, (LPARAM)nColor));
}
inline COLORREF CColorsComboBox::GetColor(INT nIndex) CONST
{
	return((COLORREF) ::SendMessage(GetSafeHwnd(), CCB_GETCOLOR, nIndex, (LPARAM)NULL));
}
inline INT CColorsComboBox::FindColor(INT nIndex, COLORREF nColor) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), CCB_FINDCOLOR, nIndex, (LPARAM)nColor));
}
inline INT CColorsComboBox::SelectColor(INT nIndex, COLORREF nColor)
{
	return((INT)SendMessage(CCB_SELECTCOLOR, nIndex, (LPARAM)nColor));
}
inline INT CColorsComboBox::DeleteColor(COLORREF nColor)
{
	return((INT)SendMessage(CCB_DELETECOLOR, (WPARAM)NULL, (LPARAM)nColor));
}
inline VOID CColorsComboBox::ResetColors()
{
	SendMessage(CCB_RESETCOLORS);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceColorsComboBox window

class CResourceColorsComboBox : public CColorsComboBox
{
	DECLARE_DYNCREATE(CResourceColorsComboBox)

	// Construction
public:
	CResourceColorsComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceColorsComboBox)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceColorsComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLineStylesComboBox window

// Specify the line styles combobox control flags
#define LS_SOLID   PS_SOLID
#define LS_DASH   PS_DASH
#define LS_DOT   PS_DOT
#define LS_DASHDOT   PS_DASHDOT
#define LS_DASHDOTDOT   PS_DASHDOTDOT
// Specify the line styles combobox control message identifiers
#define LSCB_ADDLINESTYLE   (WM_USER+28)
#define LSCB_INSERTLINESTYLE   (WM_USER+29)
#define LSCB_GETLINESTYLE   (WM_USER+30)
#define LSCB_FINDLINESTYLE   (WM_USER+31)
#define LSCB_SELECTLINESTYLE   (WM_USER+32)
#define LSCB_DELETELINESTYLE   (WM_USER+33)
#define LSCB_RESETLINESTYLES   (WM_USER+34)

class AFX_EXT_CLASS CLineStylesComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CLineStylesComboBox)

	// Construction
public:
	CLineStylesComboBox();

	// Attributes
protected:
	DWORD  m_dwStyle;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	INT AddLineStyle(INT nStyle);
	INT InsertLineStyle(INT nIndex, INT nStyle);
	INT GetLineStyle(INT nIndex) CONST;
	INT FindLineStyle(INT nIndex, INT nStyle) CONST;
	INT SelectLineStyle(INT nIndex, INT nStyle);
	INT DeleteLineStyle(INT nStyle);
	VOID ResetLineStyles();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineStylesComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CLineStylesComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnAddLineStyle(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInsertLineStyle(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetLineStyle(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFindLineStyle(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelectLineStyle(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDeleteLineStyle(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnResetLineStyles(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline INT CLineStylesComboBox::AddLineStyle(INT nStyle)
{
	return((INT)SendMessage(LSCB_ADDLINESTYLE, (WPARAM)NULL, (LPARAM)nStyle));
}
inline INT CLineStylesComboBox::InsertLineStyle(INT nIndex, INT nStyle)
{
	return((INT)SendMessage(LSCB_INSERTLINESTYLE, nIndex, (LPARAM)nStyle));
}
inline INT CLineStylesComboBox::GetLineStyle(INT nIndex) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), LSCB_GETLINESTYLE, nIndex, (LPARAM)NULL));
}
inline INT CLineStylesComboBox::FindLineStyle(INT nIndex, INT nStyle) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), LSCB_FINDLINESTYLE, nIndex, (LPARAM)nStyle));
}
inline INT CLineStylesComboBox::SelectLineStyle(INT nIndex, INT nStyle)
{
	return((INT)SendMessage(LSCB_SELECTLINESTYLE, nIndex, (LPARAM)nStyle));
}
inline INT CLineStylesComboBox::DeleteLineStyle(INT nStyle)
{
	return((INT)SendMessage(LSCB_DELETELINESTYLE, (WPARAM)NULL, (LPARAM)nStyle));
}
inline VOID CLineStylesComboBox::ResetLineStyles()
{
	SendMessage(LSCB_RESETLINESTYLES);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceLineStylesComboBox window

class CResourceLineStylesComboBox : public CLineStylesComboBox
{
	DECLARE_DYNCREATE(CResourceLineStylesComboBox)

	// Construction
public:
	CResourceLineStylesComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceLineStylesComboBox)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceLineStylesComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLineSymbolsComboBox window

// Specify the line symbols combobox control flags
#define LS_NONE   0
#define LS_POINT   1
#define LS_STROKE   2
#define LS_CROSS   3
#define LS_SQUARE   4
// Specify the line symbols combobox control message identifiers
#define LSCB_ADDLINESYMBOL   (WM_USER+35)
#define LSCB_INSERTLINESYMBOL   (WM_USER+36)
#define LSCB_GETLINESYMBOL   (WM_USER+37)
#define LSCB_FINDLINESYMBOL   (WM_USER+38)
#define LSCB_SELECTLINESYMBOL   (WM_USER+39)
#define LSCB_DELETELINESYMBOL   (WM_USER+40)
#define LSCB_RESETLINESYMBOLS   (WM_USER+41)

class AFX_EXT_CLASS CLineSymbolsComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CLineSymbolsComboBox)

	// Construction
public:
	CLineSymbolsComboBox();

	// Attributes
protected:
	DWORD  m_dwStyle;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	INT AddLineSymbol(INT nSymbol);
	INT InsertLineSymbol(INT nIndex, INT nSymbol);
	INT GetLineSymbol(INT nIndex) CONST;
	INT FindLineSymbol(INT nIndex, INT nSymbol) CONST;
	INT SelectLineSymbol(INT nIndex, INT nSymbol);
	INT DeleteLineSymbol(INT nSymbol);
	VOID ResetLineSymbols();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineSymbolsComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CLineSymbolsComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnAddLineSymbol(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInsertLineSymbol(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetLineSymbol(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFindLineSymbol(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelectLineSymbol(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDeleteLineSymbol(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnResetLineSymbols(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline INT CLineSymbolsComboBox::AddLineSymbol(INT nSymbol)
{
	return((INT)SendMessage(LSCB_ADDLINESYMBOL, (WPARAM)NULL, (LPARAM)nSymbol));
}
inline INT CLineSymbolsComboBox::InsertLineSymbol(INT nIndex, INT nSymbol)
{
	return((INT)SendMessage(LSCB_INSERTLINESYMBOL, nIndex, (LPARAM)nSymbol));
}
inline INT CLineSymbolsComboBox::GetLineSymbol(INT nIndex) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), LSCB_GETLINESYMBOL, nIndex, (LPARAM)NULL));
}
inline INT CLineSymbolsComboBox::FindLineSymbol(INT nIndex, INT nSymbol) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), LSCB_FINDLINESYMBOL, nIndex, (LPARAM)nSymbol));
}
inline INT CLineSymbolsComboBox::SelectLineSymbol(INT nIndex, INT nSymbol)
{
	return((INT)SendMessage(LSCB_SELECTLINESYMBOL, nIndex, (LPARAM)nSymbol));
}
inline INT CLineSymbolsComboBox::DeleteLineSymbol(INT nSymbol)
{
	return((INT)SendMessage(LSCB_DELETELINESYMBOL, (WPARAM)NULL, (LPARAM)nSymbol));
}
inline VOID CLineSymbolsComboBox::ResetLineSymbols()
{
	SendMessage(LSCB_RESETLINESYMBOLS);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceLineSymbolsComboBox window

class CResourceLineSymbolsComboBox : public CLineSymbolsComboBox
{
	DECLARE_DYNCREATE(CResourceLineSymbolsComboBox)

	// Construction
public:
	CResourceLineSymbolsComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceLineSymbolsComboBox)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceLineSymbolsComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CHatchesComboBox window

// Specify the hatches combobox control flags
#define HT_SOLID   0
#define HT_HORIZONTAL   1
#define HT_VERTICAL   2
#define HT_BDIAGONAL   3
#define HT_FDIAGONAL   4
#define HT_CROSS   5
#define HT_DIAGCROSS   6
#define HT_LPOINTS   7
#define HT_MPOINTS   8
#define HT_HPOINTS   9
// Specify the hatches combobox control message identifiers
#define HCB_ADDHATCH   (WM_USER+42)
#define HCB_INSERTHATCH   (WM_USER+43)
#define HCB_GETHATCH   (WM_USER+44)
#define HCB_FINDHATCH   (WM_USER+45)
#define HCB_SELECTHATCH   (WM_USER+46)
#define HCB_DELETEHATCH   (WM_USER+47)
#define HCB_RESETHATCHES   (WM_USER+48)

class AFX_EXT_CLASS CHatchesComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CHatchesComboBox)

	// Construction
public:
	CHatchesComboBox();

	// Attributes
protected:
	DWORD  m_dwStyle;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	INT AddHatch(INT nHatch);
	INT InsertHatch(INT nIndex, INT nHatch);
	INT GetHatch(INT nIndex) CONST;
	INT FindHatch(INT nIndex, INT nHatch) CONST;
	INT SelectHatch(INT nIndex, INT nHatch);
	INT DeleteHatch(INT nHatch);
	VOID ResetHatches();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHatchesComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CHatchesComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnAddHatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInsertHatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetHatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFindHatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelectHatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDeleteHatch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnResetHatches(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline INT CHatchesComboBox::AddHatch(INT nHatch)
{
	return((INT)SendMessage(HCB_ADDHATCH, (WPARAM)NULL, (LPARAM)nHatch));
}
inline INT CHatchesComboBox::InsertHatch(INT nIndex, INT nHatch)
{
	return((INT)SendMessage(HCB_INSERTHATCH, nIndex, (LPARAM)nHatch));
}
inline INT CHatchesComboBox::GetHatch(INT nIndex) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), HCB_GETHATCH, nIndex, (LPARAM)NULL));
}
inline INT CHatchesComboBox::FindHatch(INT nIndex, INT nHatch) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), HCB_FINDHATCH, nIndex, (LPARAM)nHatch));
}
inline INT CHatchesComboBox::SelectHatch(INT nIndex, INT nHatch)
{
	return((INT)SendMessage(HCB_SELECTHATCH, nIndex, (LPARAM)nHatch));
}
inline INT CHatchesComboBox::DeleteHatch(INT nHatch)
{
	return((INT)SendMessage(HCB_DELETEHATCH, (WPARAM)NULL, (LPARAM)nHatch));
}
inline VOID CHatchesComboBox::ResetHatches()
{
	SendMessage(HCB_RESETHATCHES);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceHatchesComboBox window

class CResourceHatchesComboBox : public CHatchesComboBox
{
	DECLARE_DYNCREATE(CResourceHatchesComboBox)

	// Construction
public:
	CResourceHatchesComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceHatchesComboBox)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceHatchesComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CFontsComboBox window

// Specify the fonts combobox control message identifiers
#define FCB_DIR   (WM_USER+49)

class AFX_EXT_CLASS CFontsComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CFontsComboBox)

	// Construction
public:
	CFontsComboBox();

	// Attributes
private:
	typedef struct tagFONTINFO {
		DWORD  dwType;
		LOGFONT  logFont;
	} FONTINFO, * PFONTINFO, * LPFONTINFO;
	typedef struct tagFONTENUMINFO {
		HDC  hDC;
		HWND  hWnd;
		DWORD  dwTypes;
	} FONTENUMINFO, * PFONTENUMINFO, * LPFONTENUMINFO;
protected:
	DWORD  m_dwStyle;
private:
	INT  m_nItem;
	CObList  m_pItems;
	HBITMAP  m_hPrinterFontBitmap;
	HBITMAP  m_hTrueTypeFontBitmap;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle = CBS_SIMPLE | CBS_AUTOHSCROLL | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	INT Dir(DWORD dwFlags = CF_EFFECTS | CF_SCREENFONTS, BOOL bSymbolCharSets = FALSE, CDC* pDC = NULL);

	static INT CALLBACK EnumFontsProc(CONST LOGFONT* pLogFont, CONST TEXTMETRIC* pTextMetric, DWORD dwFontType, LPARAM pData);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontsComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void DeleteItem(LPDELETEITEMSTRUCT lpDeleteItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CFontsComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg LRESULT OnDir(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline INT CFontsComboBox::Dir(DWORD dwFlags, BOOL bSymbolCharSets, CDC* pDC)
{
	return((INT)SendMessage(FCB_DIR, (dwFlags & 0x7FFFFFFF) | ((bSymbolCharSets) ? 0x80000000 : 0), (LPARAM)((AfxIsValidAddress(pDC, sizeof(CDC))) ? pDC->GetSafeHdc() : (HDC)NULL)));
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceFontsComboBox window

class CResourceFontsComboBox : public CFontsComboBox
{
	DECLARE_DYNCREATE(CResourceFontsComboBox)

	// Construction
public:
	CResourceFontsComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceFontsComboBox)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceFontsComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CAlignmentComboBox window

// Specify the alignment combobox control flags
#define AL_HLEFTVTOP   0
#define AL_HLEFTVCENTER   1
#define AL_HLEFTVBOTTOM   2
#define AL_HCENTERVTOP   3
#define AL_HCENTERVCENTER   4
#define AL_HCENTERVBOTTOM   5
#define AL_HRIGHTVTOP   6
#define AL_HRIGHTVCENTER   7
#define AL_HRIGHTVBOTTOM   8
// Specify the alignment combobox control message identifiers
#define ALCB_ADDALIGNMENT   (WM_USER+50)
#define ALCB_INSERTALIGNMENT   (WM_USER+51)
#define ALCB_GETALIGNMENT   (WM_USER+52)
#define ALCB_FINDALIGNMENT   (WM_USER+53)
#define ALCB_SELECTALIGNMENT   (WM_USER+54)
#define ALCB_DELETEALIGNMENT   (WM_USER+55)
#define ALCB_RESETALIGNMENTS   (WM_USER+56)
// Specify the alignment combobox control styles
#define ALCBS_LEFT   0x0000
#define ALCBS_CENTER   0x0004
#define ALCBS_RIGHT   0x0008

class AFX_EXT_CLASS CAlignmentComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CAlignmentComboBox)

	// Construction
public:
	CAlignmentComboBox();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	HBITMAP  m_hImageBitmap[9];

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	INT AddAlignment(UINT nAlignment);
	INT InsertAlignment(INT nIndex, UINT nAlignment);
	UINT GetAlignment(INT nIndex) CONST;
	INT FindAlignment(INT nIndex, UINT nAlignment) CONST;
	INT SelectAlignment(INT nIndex, UINT nAlignment);
	INT DeleteAlignment(UINT nAlignment);
	VOID ResetAlignments();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAlignmentComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CAlignmentComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnAddAlignment(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnInsertAlignment(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetAlignment(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFindAlignment(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSelectAlignment(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDeleteAlignment(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnResetAlignments(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline INT CAlignmentComboBox::AddAlignment(UINT nAlignment)
{
	return((INT)SendMessage(ALCB_ADDALIGNMENT, (WPARAM)NULL, (LPARAM)nAlignment));
}
inline INT CAlignmentComboBox::InsertAlignment(INT nIndex, UINT nAlignment)
{
	return((INT)SendMessage(ALCB_INSERTALIGNMENT, nIndex, (LPARAM)nAlignment));
}
inline UINT CAlignmentComboBox::GetAlignment(INT nIndex) CONST
{
	return((COLORREF) ::SendMessage(GetSafeHwnd(), ALCB_GETALIGNMENT, nIndex, (LPARAM)NULL));
}
inline INT CAlignmentComboBox::FindAlignment(INT nIndex, UINT nAlignment) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), ALCB_FINDALIGNMENT, nIndex, (LPARAM)nAlignment));
}
inline INT CAlignmentComboBox::SelectAlignment(INT nIndex, UINT nAlignment)
{
	return((INT)SendMessage(ALCB_SELECTALIGNMENT, nIndex, (LPARAM)nAlignment));
}
inline INT CAlignmentComboBox::DeleteAlignment(UINT nAlignment)
{
	return((INT)SendMessage(ALCB_DELETEALIGNMENT, (WPARAM)NULL, (LPARAM)nAlignment));
}
inline VOID CAlignmentComboBox::ResetAlignments()
{
	SendMessage(ALCB_RESETALIGNMENTS);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceAlignmentComboBox window

class CResourceAlignmentComboBox : public CAlignmentComboBox
{
	DECLARE_DYNCREATE(CResourceAlignmentComboBox)

	// Construction
public:
	CResourceAlignmentComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceAlignmentComboBox)
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceAlignmentComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpinButtons window

class CSpinButtons : public CSpinButtonCtrl
{
	DECLARE_DYNCREATE(CSpinButtons)

	// Construction
public:
	CSpinButtons();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpinButtons)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSpinButtons)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpinBox window

// Specify the spin box control message identifiers
#define SBXM_SETPOS   (WM_USER+57)
#define SBXM_GETPOS   (WM_USER+58)
#define SBXM_SETBASE   (WM_USER+59)
#define SBXM_GETBASE   (WM_USER+60)
#define SBXM_SETRANGE   (WM_USER+61)
#define SBXM_GETRANGE   (WM_USER+62)
#define SBXM_SETACCEL   (WM_USER+63)
#define SBXM_GETACCEL   (WM_USER+64)
#define SBXM_SETSEL   (WM_USER+65)
#define SBXM_GETSEL   (WM_USER+66)
// Specify the spin box control notification identifiers
#define SBXN_SETFOCUS   0x10
#define SBXN_KILLFOCUS   0x11
#define SBXN_CHANGE   0x12
#define SBXN_UPDATE   0x13
// Specify the spin control timer related identifiers
#define SPINBOX_UI_TIMERID   100
#define SPINBOX_UI_TIMEOUT   500

class AFX_EXT_CLASS CSpinBox : public CWnd
{
	DECLARE_DYNCREATE(CSpinBox)

	// Construction
public:
	CSpinBox();

	// Attributes
protected:
	DWORD  m_dwStyle;
	CNumberEdit  m_wndEditCtrl;
	CSpinButtons  m_wndSpinCtrl;
	CFont  m_cFont;
	BOOL  m_bState[2];

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle = ES_LEFT | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	BOOL SetPos(LONGLONG nPos);
	LONGLONG GetPos() CONST;
	BOOL SetBase(UINT nBase, UINT nDigits = 0);
	BOOL GetBase(UINT& nBase, UINT& nDigits) CONST;
	BOOL SetRange(LONGLONG nMin, LONGLONG nMax);
	BOOL GetRange(LONGLONG& nMin, LONGLONG& nMax) CONST;
	BOOL SetAccel(INT nAccel, CONST UDACCEL* pAccel);
	UINT GetAccel(INT nAccel, UDACCEL* pAccel) CONST;

	BOOL SetSel(INT nStartPos, INT nStopPos);
	BOOL GetSel(INT& nStartPos, INT& nStopPos) CONST;

private:
	VOID RecalcLayout(INT cx, INT cy);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpinBox)
public:
	virtual void UpdateUI();
	virtual void UpdateUI(CONST POINT& point);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSpinBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnTimer(UINT_PTR nTimerID);
	afx_msg LRESULT OnSetPos(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetPos(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBase(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetBase(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetAccel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetAccel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated helper functions
__declspec(dllexport) BOOL Spinbox_SetPos(CWnd* pCtrl, LONGLONG nPos);
__declspec(dllexport) LONGLONG Spinbox_GetPos(CWnd* pCtrl);
__declspec(dllexport) BOOL Spinbox_SetBase(CWnd* pCtrl, UINT nBase, UINT nDigits);
__declspec(dllexport) BOOL Spinbox_GetBase(CWnd* pCtrl, UINT& nBase, UINT& nDigits);
__declspec(dllexport) BOOL Spinbox_SetRange(CWnd* pCtrl, LONGLONG nMin, LONGLONG nMax);
__declspec(dllexport) BOOL Spinbox_GetRange(CWnd* pCtrl, LONGLONG& nMin, LONGLONG& nMax);
__declspec(dllexport) BOOL Spinbox_SetAccel(CWnd* pCtrl, INT nAccel, CONST UDACCEL* pAccel);
__declspec(dllexport) UINT Spinbox_GetAccel(CWnd* pCtrl, INT nAccel, UDACCEL* pAccel);
__declspec(dllexport) BOOL Spinbox_SetSel(CWnd* pCtrl, INT nStartPos, INT nStopPos);
__declspec(dllexport) BOOL Spinbox_GetSel(CWnd* pCtrl, INT& nStartPos, INT& nStopPos);

// Specify the associated inline definitions
inline BOOL CSpinBox::SetPos(LONGLONG nPos)
{
	return(Spinbox_SetPos(CSpinBox::FromHandle(GetSafeHwnd()), nPos));
}
inline LONGLONG CSpinBox::GetPos() CONST
{
	return(Spinbox_GetPos(CSpinBox::FromHandle(GetSafeHwnd())));
}
inline BOOL CSpinBox::SetBase(UINT nBase, UINT nDigits)
{
	return(Spinbox_SetBase(CSpinBox::FromHandle(GetSafeHwnd()), nBase, nDigits));
}
inline BOOL CSpinBox::GetBase(UINT& nBase, UINT& nDigits) CONST
{
	return(Spinbox_GetBase(CSpinBox::FromHandle(GetSafeHwnd()), nBase, nDigits));
}
inline BOOL CSpinBox::SetRange(LONGLONG nMin, LONGLONG nMax)
{
	return(Spinbox_SetRange(CSpinBox::FromHandle(GetSafeHwnd()), nMin, nMax));
}
inline BOOL CSpinBox::GetRange(LONGLONG& nMin, LONGLONG& nMax) CONST
{
	return(Spinbox_GetRange(CSpinBox::FromHandle(GetSafeHwnd()), nMin, nMax));
}
inline BOOL CSpinBox::SetAccel(INT nAccel, CONST UDACCEL* pAccel)
{
	return(Spinbox_SetAccel(CSpinBox::FromHandle(GetSafeHwnd()), nAccel, pAccel));
}
inline UINT CSpinBox::GetAccel(INT nAccel, UDACCEL* pAccel) CONST
{
	return(Spinbox_GetAccel(CSpinBox::FromHandle(GetSafeHwnd()), nAccel, pAccel));
}
inline BOOL CSpinBox::SetSel(INT nStartPos, INT nStopPos)
{
	return(Spinbox_SetSel(CSpinBox::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}
inline BOOL CSpinBox::GetSel(INT& nStartPos, INT& nStopPos) CONST
{
	return(Spinbox_GetSel(CSpinBox::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceSpinBox window

class CResourceSpinBox : public CSpinBox
{
	DECLARE_DYNCREATE(CResourceSpinBox)

	// Construction
public:
	CResourceSpinBox(HWND hWnd = NULL);

	// Attributes
public:

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceSpinBox)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceSpinBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTimeSpinBox window

// Specify the time spin box control message identifiers
#define TSBXM_SETTIME   (WM_USER+67)
#define TSBXM_GETTIME   (WM_USER+68)
#define TSBXM_SETRANGE   (WM_USER+69)
#define TSBXM_GETRANGE   (WM_USER+70)
#define TSBXM_SETSEL   (WM_USER+71)
#define TSBXM_GETSEL   (WM_USER+72)
// Specify the time spin box control notification identifiers
#define TSBXN_SETFOCUS   0x20
#define TSBXN_KILLFOCUS   0x21
#define TSBXN_CHANGE   0x22
#define TSBXN_UPDATE   0x23
// Specify the time spin box control styles
#define TSBXS_ANY_TIME   0
#define TSBXS_PAST_TIME   (1<<0)
#define TSBXS_FUTURE_TIME   (1<<1)
#define TSBXS_UTC_TIME   (1<<2)
#define TSBXS_SPAN_TIME   (1<<3)
#define TSBXS_HIDE_TIME   (1<<4)
// Specify the time spin box control related macros
#define MAKETIMESPINBOXLIMITS(l,h)   ((LONGLONG) (((ULONGLONG) (DWORD) (INT) (l)) | (((ULONGLONG) (DWORD) (INT) (h)) << 32)))
#define TIMESPINBOXLOWLIMIT(x)   ((INT) (x))
#define TIMESPINBOXHIGHLIMIT(x)   ((INT) (((ULONGLONG) (x)) >> 32))
// Specify the time spin box control timer related identifiers
#define TIMESPINBOX_UI_TIMERID   100
#define TIMESPINBOX_UI_TIMEOUT   500

class AFX_EXT_CLASS CTimeSpinBox : public CWnd
{
	DECLARE_DYNCREATE(CTimeSpinBox)

	// Construction
public:
	CTimeSpinBox();

	// Attributes
protected:
	DWORD  m_dwStyle;
	CPtrArray  m_pwndEditCtrls;
	CPtrArray  m_pwndStaticCtrls;
	CSpinButtons  m_wndSpinCtrl;
	CUIntArray  m_nCtrlFormat;
	CFont  m_cFont;
	BOOL  m_bState[2];
	BOOL  m_bVisible;
protected:
	CTimeTag  m_tTime;
	CTimeTag  m_tStartTime;
	CTimeTag  m_tStopTime;

	// Operations
public:
	BOOL Create(CWnd* pParentWnd, CONST RECT& rect, UINT nID, DWORD dwStyle = TSBXS_ANY_TIME | TSBXS_UTC_TIME | WS_VISIBLE | WS_TABSTOP, LPCTSTR pszFormat = NULL, CONST CTimeTag& tStartTime = 0, CONST CTimeTag & StopTime = 0);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	VOID SetTime(CONST CTimeTag& tTime);
	VOID SetTime(CONST CTimeKey& tTime);
	BOOL GetTime(CTimeTag& tTime) CONST;
	BOOL GetTime(CTimeKey& tTime) CONST;
	CTimeKey GetTime() CONST;
	BOOL SetRange(CONST CTimeTag& tStartTime, CONST CTimeTag& tStopTime);
	BOOL SetRange(CONST CTimeKey& tStartTime, CONST CTimeKey& tStopTime);
	BOOL GetRange(CTimeTag& tStartTime, CTimeTag& tStopTime) CONST;
	BOOL GetRange(CTimeKey& tStartTime, CTimeKey& tStopTime) CONST;
	BOOL SetSel(INT nStartPos, INT nStopPos);
	BOOL GetSel(INT& nStartPos, INT& nStopPos) CONST;

protected:
	VOID EnableAutoCompletion(BOOL bEnable = TRUE);
	BOOL IsAutoCompletionEnabled() CONST;

	INT TranslateSubFormat(LPCTSTR pszFormat) CONST;
	BOOL TranslateSubFormatDelimiter(LPCTSTR pszFormat, CString& szDelimiter) CONST;
	BOOL TranslateSubFormatPosition(LPCTSTR pszFormat, CONST RECT& rect, CRect& rSubFormat);

private:
	BOOL ShowSubControls(BOOL bShow = TRUE);

	BOOL IsSubFormatNumericalEditCtrl(INT nSubFormatID) CONST;
	BOOL IsSubFormatEditCtrl(INT nSubFormatID) CONST;
	BOOL IsSubFormatDelimiterCtrl(INT nSubFormatID) CONST;

	BOOL IsTimespanSubFormatID(INT nSubFormatID, BOOL bRightAligned = FALSE) CONST;
	BOOL IsExistingSubFormatID(INT nSubFormatID) CONST;

	INT CalcIndent();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeSpinBox)
public:
	virtual VOID SetTime();
public:
	virtual void UpdateUI();
	virtual void UpdateUI(CONST POINT& point);
protected:
	virtual LONGLONG EnumSubFormatLimits(INT nSubFormatID) CONST;
	virtual INT EnumSubFormatLimits(INT nSubFormatID, CStringArray& szNames) CONST;
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTimeSpinBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnTimer(UINT_PTR nTimerID);
	afx_msg LRESULT OnSetTime(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetTime(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetRange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated helper functions
__declspec(dllexport) VOID Timespinbox_SetTime(CWnd* pCtrl);
__declspec(dllexport) VOID Timespinbox_SetTime(CWnd* pCtrl, CONST CTimeTag& tTime);
__declspec(dllexport) VOID Timespinbox_SetTime(CWnd* pCtrl, CONST CTimeKey& tTime);
__declspec(dllexport) CTimeKey Timespinbox_GetTime(CWnd* pCtrl);
__declspec(dllexport) BOOL Timespinbox_GetTime(CWnd* pCtrl, CTimeTag& tTime);
__declspec(dllexport) BOOL Timespinbox_GetTime(CWnd* pCtrl, CTimeKey& tTime);
__declspec(dllexport) BOOL Timespinbox_SetRange(CWnd* pCtrl, CONST CTimeTag& tStartTime, CONST CTimeTag& tStopTime);
__declspec(dllexport) BOOL Timespinbox_SetRange(CWnd* pCtrl, CONST CTimeKey& tStartTime, CONST CTimeKey& tStopTime);
__declspec(dllexport) BOOL Timespinbox_GetRange(CWnd* pCtrl, CTimeTag& tStartTime, CTimeTag& tStopTime);
__declspec(dllexport) BOOL Timespinbox_GetRange(CWnd* pCtrl, CTimeKey& tStartTime, CTimeKey& tStopTime);
__declspec(dllexport) BOOL Timespinbox_SetSel(CWnd* pCtrl, INT nStartPos, INT nStopPos);
__declspec(dllexport) BOOL Timespinbox_GetSel(CWnd* pCtrl, INT& nStartPos, INT& nStopPos);

// Specify the associated inline definitions
inline VOID CTimeSpinBox::SetTime()
{
	return(Timespinbox_SetTime(CTimeSpinBox::FromHandle(GetSafeHwnd())));
}
inline VOID CTimeSpinBox::SetTime(CONST CTimeTag& tTime)
{
	return(Timespinbox_SetTime(CTimeSpinBox::FromHandle(GetSafeHwnd()), tTime));
}
inline VOID CTimeSpinBox::SetTime(CONST CTimeKey& tTime)
{
	return(Timespinbox_SetTime(CTimeSpinBox::FromHandle(GetSafeHwnd()), tTime));
}
inline BOOL CTimeSpinBox::GetTime(CTimeTag& tTime) CONST
{
	return(Timespinbox_GetTime(CTimeSpinBox::FromHandle(GetSafeHwnd()), tTime));
}
inline BOOL CTimeSpinBox::GetTime(CTimeKey& tTime) CONST
{
	return(Timespinbox_GetTime(CTimeSpinBox::FromHandle(GetSafeHwnd()), tTime));
}
inline CTimeKey CTimeSpinBox::GetTime() CONST
{
	return(Timespinbox_GetTime(CTimeSpinBox::FromHandle(GetSafeHwnd())));
}
inline BOOL CTimeSpinBox::SetRange(CONST CTimeTag& tStartTime, CONST CTimeTag& tStopTime)
{
	return(Timespinbox_SetRange(CTimeSpinBox::FromHandle(GetSafeHwnd()), tStartTime, tStopTime));
}
inline BOOL CTimeSpinBox::SetRange(CONST CTimeKey& tStartTime, CONST CTimeKey& tStopTime)
{
	return(Timespinbox_SetRange(CTimeSpinBox::FromHandle(GetSafeHwnd()), tStartTime, tStopTime));
}
inline BOOL CTimeSpinBox::GetRange(CTimeTag& tStartTime, CTimeTag& tStopTime) CONST
{
	return(Timespinbox_GetRange(CTimeSpinBox::FromHandle(GetSafeHwnd()), tStartTime, tStopTime));
}
inline BOOL CTimeSpinBox::GetRange(CTimeKey& tStartTime, CTimeKey& tStopTime) CONST
{
	return(Timespinbox_GetRange(CTimeSpinBox::FromHandle(GetSafeHwnd()), tStartTime, tStopTime));
}
inline BOOL CTimeSpinBox::SetSel(INT nStartPos, INT nStopPos)
{
	return(Timespinbox_SetSel(CTimeSpinBox::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}
inline BOOL CTimeSpinBox::GetSel(INT& nStartPos, INT& nStopPos) CONST
{
	return(Timespinbox_GetSel(CTimeSpinBox::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceTimeSpinBox window

class CResourceTimeSpinBox : public CTimeSpinBox
{
	DECLARE_DYNCREATE(CResourceTimeSpinBox)

	// Construction
public:
	CResourceTimeSpinBox(HWND hWnd = NULL);

	// Attributes
public:

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceTimeSpinBox)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceTimeSpinBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Listbox helpers

__declspec(dllexport) BOOL Listbox_SetText(CWnd* pCtrl, INT nItem, LPCTSTR pszText);
__declspec(dllexport) CString Listbox_GetText(CWnd* pCtrl, INT nItem);

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Combobox helpers

__declspec(dllexport) BOOL Combobox_SetText(CWnd* pCtrl, INT nItem, LPCTSTR pszText);
__declspec(dllexport) CString Combobox_GetText(CWnd* pCtrl, INT nItem);

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Listview helpers

__declspec(dllexport) BOOL Listview_InsertColumn(CWnd* pCtrl, INT nColumn, LPCTSTR pszColumn, INT nWidth);
__declspec(dllexport) BOOL Listview_SetColumn(CWnd* pCtrl, INT nColumn, LPCTSTR pszColumn, INT nWidth = -1);
__declspec(dllexport) BOOL Listview_GetColumn(CWnd* pCtrl, INT nColumn, CString& szColumn, INT& nWidth);
__declspec(dllexport) BOOL Listview_DeleteColumn(CWnd* pCtrl, INT nColumn);
__declspec(dllexport) BOOL Listview_InsertText(CWnd* pCtrl, INT nItem, LPCTSTR pszText);
__declspec(dllexport) BOOL Listview_SetText(CWnd* pCtrl, INT nItem, INT nSubItem, LPCTSTR pszText);
__declspec(dllexport) CString Listview_GetText(CWnd* pCtrl, INT nItem, INT nSubItem);
__declspec(dllexport) BOOL Listview_SetCurText(CWnd* pCtrl, INT nItem);
__declspec(dllexport) INT Listview_GetCurText(CWnd* pCtrl);
__declspec(dllexport) BOOL Listview_SetSelText(CWnd* pCtrl, CONST CUIntArray& nItems);
__declspec(dllexport) BOOL Listview_IsSelText(CWnd* pCtrl, INT nItem);
__declspec(dllexport) INT Listview_GetSelText(CWnd* pCtrl, CUIntArray& nItems);
__declspec(dllexport) BOOL Listview_DeleteText(CWnd* pCtrl, INT nItem);

/////////////////////////////////////////////////////////////////////////////


#endif // __CONTROLS_H__
