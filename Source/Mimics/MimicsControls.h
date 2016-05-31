// MIMICSCONTROLS.H : Mimics Custom Control Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics custom control related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/09/22 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSCONTROLS_H__
#define __MIMICSCONTROLS_H__


/////////////////////////////////////////////////////////////////////////////
// CMimicsCustomControls

class CMimicsCustomControls : public CObject
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
	static BOOL RegisterCustomControls();
	static BOOL UnregisterCustomControls();

	static CRuntimeClass *GetCustomControlBaseClass(CRuntimeClass *pClass);

	static CFont *GetCustomControlFont(CONST CWnd *pControl);
};

// Specify the associated inline definitions
inline BOOL RegisterCustomControls()
{
	return CMimicsCustomControls::RegisterCustomControls();
}
inline BOOL UnregisterCustomControls()
{
	return CMimicsCustomControls::UnregisterCustomControls();
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsSimpleEdit window

class CMimicsSimpleEdit : public CEdit
{
	DECLARE_DYNCREATE(CMimicsSimpleEdit)

	// Construction
public:

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	CString  m_szContents;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, INT nID, DWORD dwStyle = ES_MULTILINE | WS_BORDER | WS_VISIBLE | WS_VSCROLL);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsSimpleEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsSimpleEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
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
// CResourceMimicsSimpleEdit window

class CResourceMimicsSimpleEdit : public CMimicsSimpleEdit
{
	DECLARE_DYNCREATE(CResourceMimicsSimpleEdit)

	// Construction
public:
	CResourceMimicsSimpleEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsSimpleEdit)
protected:
	virtual WNDPROC *GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsSimpleEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsNumberEdit window

// Specify the mimics numerical edit control message identifiers
#define NEM_SETBASE   (WM_USER+1)
#define NEM_GETBASE   (WM_USER+2)
#define NEM_SETRANGE   (WM_USER+3)
#define NEM_GETRANGE   (WM_USER+4)
#define NEM_SETPOS   (WM_USER+5)
#define NEM_GETPOS   (WM_USER+6)
#define NEM_SETSEL   (WM_USER+7)
#define NEM_GETSEL   (WM_USER+8)
#define NEM_CHECK   (WM_USER+9)

class CMimicsNumberEdit : public CEdit
{
	DECLARE_DYNCREATE(CMimicsNumberEdit)

	// Construction
public:
	CMimicsNumberEdit();

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
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, INT nID, DWORD dwStyle = ES_LEFT | WS_BORDER | WS_VISIBLE | WS_TABSTOP, BOOL bMinusZero = FALSE);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	BOOL SetBase(UINT nBase, UINT nDigits = 0);
	BOOL GetBase(UINT &nBase, UINT &nDigits) CONST;
	BOOL SetRange(LONGLONG nMin, LONGLONG nMax);
	BOOL GetRange(LONGLONG &nMin, LONGLONG &nMax) CONST;
	BOOL SetPos(LONGLONG nPos, BOOL bNotify = FALSE);
	LONGLONG GetPos(BOOL bLimits = TRUE) CONST;
	BOOL SetSel(INT nStartPos, INT nStopPos);
	BOOL GetSel(INT &nStartPos, INT &nStopPos) CONST;
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
	//{{AFX_VIRTUAL(CMimicsNumberEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsNumberEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
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
__declspec(dllexport) BOOL MimicsNumberedit_SetBase(CWnd *pCtrl, UINT nBase, UINT nDigits);
__declspec(dllexport) BOOL MimicsNumberedit_GetBase(CWnd *pCtrl, UINT &nBase, UINT &nDigits);
__declspec(dllexport) BOOL MimicsNumberedit_SetRange(CWnd *pCtrl, LONGLONG nMin, LONGLONG nMax);
__declspec(dllexport) BOOL MimicsNumberedit_GetRange(CWnd *pCtrl, LONGLONG &nMin, LONGLONG &nMax);
__declspec(dllexport) BOOL MimicsNumberedit_SetPos(CWnd *pCtrl, LONGLONG nPos, BOOL bNotify = FALSE);
__declspec(dllexport) LONGLONG MimicsNumberedit_GetPos(CWnd *pCtrl, BOOL bLimits = TRUE);
__declspec(dllexport) BOOL MimicsNumberedit_SetSel(CWnd *pCtrl, INT nStartPos, INT nStopPos);
__declspec(dllexport) BOOL MimicsNumberedit_GetSel(CWnd *pCtrl, INT &nStartPos, INT &nStopPos);
__declspec(dllexport) DWORD MimicsNumberedit_GetSel(CWnd *pCtrl);
__declspec(dllexport) BOOL MimicsNumberedit_Check(CWnd *pCtrl);

// Specify the associated inline definitions
inline BOOL CMimicsNumberEdit::SetBase(UINT nBase, UINT nDigits)
{
	return(MimicsNumberedit_SetBase(CMimicsNumberEdit::FromHandle(GetSafeHwnd()), nBase, nDigits));
}
inline BOOL CMimicsNumberEdit::GetBase(UINT &nBase, UINT &nDigits) CONST
{
	return(MimicsNumberedit_GetBase(CMimicsNumberEdit::FromHandle(GetSafeHwnd()), nBase, nDigits));
}
inline BOOL CMimicsNumberEdit::SetRange(LONGLONG nMin, LONGLONG nMax)
{
	return(MimicsNumberedit_SetRange(CMimicsNumberEdit::FromHandle(GetSafeHwnd()), nMin, nMax));
}
inline BOOL CMimicsNumberEdit::GetRange(LONGLONG &nMin, LONGLONG &nMax) CONST
{
	return(MimicsNumberedit_GetRange(CMimicsNumberEdit::FromHandle(GetSafeHwnd()), nMin, nMax));
}
inline BOOL CMimicsNumberEdit::SetPos(LONGLONG nPos, BOOL bNotify)
{
	return(MimicsNumberedit_SetPos(CMimicsNumberEdit::FromHandle(GetSafeHwnd()), nPos, bNotify));
}
inline LONGLONG CMimicsNumberEdit::GetPos(BOOL bLimits) CONST
{
	return(MimicsNumberedit_GetPos(CMimicsNumberEdit::FromHandle(GetSafeHwnd()), bLimits));
}
inline BOOL CMimicsNumberEdit::SetSel(INT nStartPos, INT nStopPos)
{
	return(MimicsNumberedit_SetSel(CMimicsNumberEdit::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}
inline BOOL CMimicsNumberEdit::GetSel(INT &nStartPos, INT &nStopPos) CONST
{
	return(MimicsNumberedit_GetSel(CMimicsNumberEdit::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}
inline DWORD CMimicsNumberEdit::GetSel() CONST
{
	return(MimicsNumberedit_GetSel(CMimicsNumberEdit::FromHandle(GetSafeHwnd())));
}
inline BOOL CMimicsNumberEdit::Check() CONST
{
	return(MimicsNumberedit_Check(CMimicsNumberEdit::FromHandle(GetSafeHwnd())));
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsNumberEdit window

class CResourceMimicsNumberEdit : public CMimicsNumberEdit
{
	DECLARE_DYNCREATE(CResourceMimicsNumberEdit)

	// Construction
public:
	CResourceMimicsNumberEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsNumberEdit)
protected:
	virtual WNDPROC *GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsNumberEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextEdit window

// Specify the mimics text edit control message identifiers
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

class CMimicsTextEdit : public CEdit
{
	DECLARE_DYNCREATE(CMimicsTextEdit)

	// Construction
public:
	CMimicsTextEdit();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	CStringArray  m_szNames;
	BOOL  m_bAutoCompletion;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, INT nID, DWORD dwStyle = ES_LEFT | WS_BORDER | WS_VISIBLE | WS_TABSTOP);

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
	VOID GetSel(INT &nStartPos, INT &nStopPos) CONST;
	DWORD GetSel() CONST;

	VOID EnableAutoCompletion(BOOL bEnable = TRUE);
	BOOL IsAutoCompletionEnabled() CONST;

	BOOL Check() CONST;

private:
	VOID Format();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsTextEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsTextEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
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
inline INT CMimicsTextEdit::AddText(LPCTSTR pszText)
{
	return((INT)SendMessage(TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)pszText));
}
inline VOID CMimicsTextEdit::InsertText(INT nIndex, LPCTSTR pszText)
{
	SendMessage(TEM_INSERTTEXT, nIndex, (LPARAM)pszText);
}
inline INT CMimicsTextEdit::FindText(INT nIndex, LPCTSTR pszText) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), TEM_FINDTEXT, nIndex, (LPARAM)pszText));
}
inline BOOL CMimicsTextEdit::SelectText(INT nIndex, LPCTSTR pszText)
{
	return((BOOL)SendMessage(TEM_SELECTTEXT, nIndex, (LPARAM)pszText));
}
inline BOOL CMimicsTextEdit::DeleteText(LPCTSTR pszText)
{
	return((BOOL)SendMessage(TEM_DELETETEXT, (WPARAM)NULL, (LPARAM)pszText));
}
inline VOID CMimicsTextEdit::ResetText()
{
	SendMessage(TEM_RESETTEXT);
}
inline BOOL CMimicsTextEdit::SetPos(INT nPos, BOOL bNotify)
{
	return((BOOL)SendMessage(TEM_SETPOS, nPos, bNotify));
}
inline INT CMimicsTextEdit::GetPos() CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), TEM_GETPOS, (WPARAM)NULL, (LPARAM)NULL));
}
inline BOOL CMimicsTextEdit::SetSel(INT nStartPos, INT nStopPos)
{
	return((BOOL)SendMessage(TEM_SETSEL, nStartPos, nStopPos));
}
inline VOID CMimicsTextEdit::GetSel(INT &nStartPos, INT &nStopPos) CONST
{
	::SendMessage(GetSafeHwnd(), TEM_GETSEL, (WPARAM)&nStartPos, (LPARAM)&nStopPos);
}
inline DWORD CMimicsTextEdit::GetSel() CONST
{
	return CEdit::GetSel();
}
inline BOOL CMimicsTextEdit::Check() CONST
{
	return((BOOL) ::SendMessage(GetSafeHwnd(), TEM_CHECK, (WPARAM)NULL, (LPARAM)NULL));
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsTextEdit window

class CResourceMimicsTextEdit : public CMimicsTextEdit
{
	DECLARE_DYNCREATE(CResourceMimicsTextEdit)

	// Construction
public:
	CResourceMimicsTextEdit(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsTextEdit)
protected:
	virtual WNDPROC *GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsTextEdit)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsSimpleListBox window

class CMimicsSimpleListBox : public CListBox
{
	DECLARE_DYNCREATE(CMimicsSimpleListBox)

	// Construction
public:

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	CStringArray  m_szItems;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, INT nID, DWORD dwStyle = LBS_DISABLENOSCROLL | LBS_NOINTEGRALHEIGHT | LBS_SORT | WS_BORDER | WS_VISIBLE);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsSimpleListBox)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsSimpleListBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnEnable(BOOL bEnable);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsSimpleListBox window

class CResourceMimicsSimpleListBox : public CMimicsSimpleListBox
{
	DECLARE_DYNCREATE(CResourceMimicsSimpleListBox)

	// Construction
public:
	CResourceMimicsSimpleListBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsSimpleListBox)
protected:
	virtual WNDPROC *GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsSimpleListBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsColorsComboBox window

// Specify the mimics colors combobox control message identifiers
#define CCB_ADDCOLOR   (WM_USER+21)
#define CCB_INSERTCOLOR   (WM_USER+22)
#define CCB_GETCOLOR   (WM_USER+23)
#define CCB_FINDCOLOR   (WM_USER+24)
#define CCB_SELECTCOLOR   (WM_USER+25)
#define CCB_DELETECOLOR   (WM_USER+26)
#define CCB_RESETCOLORS   (WM_USER+27)
// Specify the mimics colors combobox control styles
#define CCBS_STANDARD   0x0000
#define CCBS_CUSTOM   0x0004

class CMimicsColorsComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CMimicsColorsComboBox)

	// Construction
public:

	// Attributes
protected:
	DWORD  m_dwStyle;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_TABSTOP);

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
	//{{AFX_VIRTUAL(CMimicsColorsComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsColorsComboBox)
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
inline INT CMimicsColorsComboBox::AddColor(COLORREF nColor)
{
	return((INT)SendMessage(CCB_ADDCOLOR, (WPARAM)NULL, (LPARAM)nColor));
}
inline INT CMimicsColorsComboBox::InsertColor(INT nIndex, COLORREF nColor)
{
	return((INT)SendMessage(CCB_INSERTCOLOR, nIndex, (LPARAM)nColor));
}
inline COLORREF CMimicsColorsComboBox::GetColor(INT nIndex) CONST
{
	return((COLORREF) ::SendMessage(GetSafeHwnd(), CCB_GETCOLOR, nIndex, (LPARAM)NULL));
}
inline INT CMimicsColorsComboBox::FindColor(INT nIndex, COLORREF nColor) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), CCB_FINDCOLOR, nIndex, (LPARAM)nColor));
}
inline INT CMimicsColorsComboBox::SelectColor(INT nIndex, COLORREF nColor)
{
	return((INT)SendMessage(CCB_SELECTCOLOR, nIndex, (LPARAM)nColor));
}
inline INT CMimicsColorsComboBox::DeleteColor(COLORREF nColor)
{
	return((INT)SendMessage(CCB_DELETECOLOR, (WPARAM)NULL, (LPARAM)nColor));
}
inline VOID CMimicsColorsComboBox::ResetColors()
{
	SendMessage(CCB_RESETCOLORS);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsColorsComboBox window

class CResourceMimicsColorsComboBox : public CMimicsColorsComboBox
{
	DECLARE_DYNCREATE(CResourceMimicsColorsComboBox)

	// Construction
public:
	CResourceMimicsColorsComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsColorsComboBox)
protected:
	virtual WNDPROC *GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsColorsComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineStylesComboBox window

// Specify the mimics line styles combobox control flags
#define LS_SOLID   PS_SOLID
#define LS_DASH   PS_DASH
#define LS_DOT   PS_DOT
#define LS_DASHDOT   PS_DASHDOT
#define LS_DASHDOTDOT   PS_DASHDOTDOT
// Specify the mimics line styles combobox control message identifiers
#define LSCB_ADDLINESTYLE   (WM_USER+28)
#define LSCB_INSERTLINESTYLE   (WM_USER+29)
#define LSCB_GETLINESTYLE   (WM_USER+30)
#define LSCB_FINDLINESTYLE   (WM_USER+31)
#define LSCB_SELECTLINESTYLE   (WM_USER+32)
#define LSCB_DELETELINESTYLE   (WM_USER+33)
#define LSCB_RESETLINESTYLES   (WM_USER+34)

class CMimicsLineStylesComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CMimicsLineStylesComboBox)

	// Construction
public:

	// Attributes
protected:
	DWORD  m_dwStyle;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_TABSTOP);

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
	//{{AFX_VIRTUAL(CMimicsLineStylesComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsLineStylesComboBox)
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
inline INT CMimicsLineStylesComboBox::AddLineStyle(INT nStyle)
{
	return((INT)SendMessage(LSCB_ADDLINESTYLE, (WPARAM)NULL, (LPARAM)nStyle));
}
inline INT CMimicsLineStylesComboBox::InsertLineStyle(INT nIndex, INT nStyle)
{
	return((INT)SendMessage(LSCB_INSERTLINESTYLE, nIndex, (LPARAM)nStyle));
}
inline INT CMimicsLineStylesComboBox::GetLineStyle(INT nIndex) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), LSCB_GETLINESTYLE, nIndex, (LPARAM)NULL));
}
inline INT CMimicsLineStylesComboBox::FindLineStyle(INT nIndex, INT nStyle) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), LSCB_FINDLINESTYLE, nIndex, (LPARAM)nStyle));
}
inline INT CMimicsLineStylesComboBox::SelectLineStyle(INT nIndex, INT nStyle)
{
	return((INT)SendMessage(LSCB_SELECTLINESTYLE, nIndex, (LPARAM)nStyle));
}
inline INT CMimicsLineStylesComboBox::DeleteLineStyle(INT nStyle)
{
	return((INT)SendMessage(LSCB_DELETELINESTYLE, (WPARAM)NULL, (LPARAM)nStyle));
}
inline VOID CMimicsLineStylesComboBox::ResetLineStyles()
{
	SendMessage(LSCB_RESETLINESTYLES);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsLineStylesComboBox window

class CResourceMimicsLineStylesComboBox : public CMimicsLineStylesComboBox
{
	DECLARE_DYNCREATE(CResourceMimicsLineStylesComboBox)

	// Construction
public:
	CResourceMimicsLineStylesComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsLineStylesComboBox)
protected:
	virtual WNDPROC *GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsLineStylesComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineSymbolsComboBox window

// Specify the mimics line symbols combobox control flags
#define LS_NONE   0
#define LS_POINT   1
#define LS_STROKE   2
#define LS_CROSS   3
#define LS_SQUARE   4
// Specify the mimics line symbols combobox control message identifiers
#define LSCB_ADDLINESYMBOL   (WM_USER+35)
#define LSCB_INSERTLINESYMBOL   (WM_USER+36)
#define LSCB_GETLINESYMBOL   (WM_USER+37)
#define LSCB_FINDLINESYMBOL   (WM_USER+38)
#define LSCB_SELECTLINESYMBOL   (WM_USER+39)
#define LSCB_DELETELINESYMBOL   (WM_USER+40)
#define LSCB_RESETLINESYMBOLS   (WM_USER+41)

class CMimicsLineSymbolsComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CMimicsLineSymbolsComboBox)

	// Construction
public:

	// Attributes
protected:
	DWORD  m_dwStyle;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_TABSTOP);

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
	//{{AFX_VIRTUAL(CMimicsLineSymbolsComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsLineSymbolsComboBox)
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
inline INT CMimicsLineSymbolsComboBox::AddLineSymbol(INT nSymbol)
{
	return((INT)SendMessage(LSCB_ADDLINESYMBOL, (WPARAM)NULL, (LPARAM)nSymbol));
}
inline INT CMimicsLineSymbolsComboBox::InsertLineSymbol(INT nIndex, INT nSymbol)
{
	return((INT)SendMessage(LSCB_INSERTLINESYMBOL, nIndex, (LPARAM)nSymbol));
}
inline INT CMimicsLineSymbolsComboBox::GetLineSymbol(INT nIndex) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), LSCB_GETLINESYMBOL, nIndex, (LPARAM)NULL));
}
inline INT CMimicsLineSymbolsComboBox::FindLineSymbol(INT nIndex, INT nSymbol) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), LSCB_FINDLINESYMBOL, nIndex, (LPARAM)nSymbol));
}
inline INT CMimicsLineSymbolsComboBox::SelectLineSymbol(INT nIndex, INT nSymbol)
{
	return((INT)SendMessage(LSCB_SELECTLINESYMBOL, nIndex, (LPARAM)nSymbol));
}
inline INT CMimicsLineSymbolsComboBox::DeleteLineSymbol(INT nSymbol)
{
	return((INT)SendMessage(LSCB_DELETELINESYMBOL, (WPARAM)NULL, (LPARAM)nSymbol));
}
inline VOID CMimicsLineSymbolsComboBox::ResetLineSymbols()
{
	SendMessage(LSCB_RESETLINESYMBOLS);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsLineSymbolsComboBox window

class CResourceMimicsLineSymbolsComboBox : public CMimicsLineSymbolsComboBox
{
	DECLARE_DYNCREATE(CResourceMimicsLineSymbolsComboBox)

	// Construction
public:
	CResourceMimicsLineSymbolsComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsLineSymbolsComboBox)
protected:
	virtual WNDPROC *GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsLineSymbolsComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsHatchesComboBox window

// Specify the mimics hatches combobox control flags
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
// Specify the mimics hatches combobox control message identifiers
#define HCB_ADDHATCH   (WM_USER+42)
#define HCB_INSERTHATCH   (WM_USER+43)
#define HCB_GETHATCH   (WM_USER+44)
#define HCB_FINDHATCH   (WM_USER+45)
#define HCB_SELECTHATCH   (WM_USER+46)
#define HCB_DELETEHATCH   (WM_USER+47)
#define HCB_RESETHATCHES   (WM_USER+48)

class CMimicsHatchesComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CMimicsHatchesComboBox)

	// Construction
public:

	// Attributes
protected:
	DWORD  m_dwStyle;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_TABSTOP);

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
	//{{AFX_VIRTUAL(CMimicsHatchesComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsHatchesComboBox)
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
inline INT CMimicsHatchesComboBox::AddHatch(INT nHatch)
{
	return((INT)SendMessage(HCB_ADDHATCH, (WPARAM)NULL, (LPARAM)nHatch));
}
inline INT CMimicsHatchesComboBox::InsertHatch(INT nIndex, INT nHatch)
{
	return((INT)SendMessage(HCB_INSERTHATCH, nIndex, (LPARAM)nHatch));
}
inline INT CMimicsHatchesComboBox::GetHatch(INT nIndex) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), HCB_GETHATCH, nIndex, (LPARAM)NULL));
}
inline INT CMimicsHatchesComboBox::FindHatch(INT nIndex, INT nHatch) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), HCB_FINDHATCH, nIndex, (LPARAM)nHatch));
}
inline INT CMimicsHatchesComboBox::SelectHatch(INT nIndex, INT nHatch)
{
	return((INT)SendMessage(HCB_SELECTHATCH, nIndex, (LPARAM)nHatch));
}
inline INT CMimicsHatchesComboBox::DeleteHatch(INT nHatch)
{
	return((INT)SendMessage(HCB_DELETEHATCH, (WPARAM)NULL, (LPARAM)nHatch));
}
inline VOID CMimicsHatchesComboBox::ResetHatches()
{
	SendMessage(HCB_RESETHATCHES);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsHatchesComboBox window

class CResourceMimicsHatchesComboBox : public CMimicsHatchesComboBox
{
	DECLARE_DYNCREATE(CResourceMimicsHatchesComboBox)

	// Construction
public:
	CResourceMimicsHatchesComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsHatchesComboBox)
protected:
	virtual WNDPROC *GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsHatchesComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsFontsComboBox window

// Specify the mimics fonts combobox control message identifiers
#define FCB_DIR   (WM_USER+49)

class CMimicsFontsComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CMimicsFontsComboBox)

	// Construction
public:
	CMimicsFontsComboBox();

	// Attributes
private:
	typedef struct tagFONTINFO {
		DWORD  dwType;
		LOGFONT  logFont;
	} FONTINFO, *PFONTINFO, *LPFONTINFO;
	typedef struct tagFONTENUMINFO {
		HDC  hDC;
		HWND  hWnd;
		DWORD  dwTypes;
	} FONTENUMINFO, *PFONTENUMINFO, *LPFONTENUMINFO;
protected:
	DWORD  m_dwStyle;
private:
	INT  m_nItem;
	CObList  m_pItems;
	HBITMAP  m_hPrinterFontBitmap;
	HBITMAP  m_hTrueTypeFontBitmap;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle = CBS_SIMPLE | CBS_AUTOHSCROLL | CBS_DISABLENOSCROLL | CBS_NOINTEGRALHEIGHT | CBS_SORT | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	INT Dir(DWORD dwFlags = CF_EFFECTS | CF_SCREENFONTS, BOOL bSymbolCharSets = FALSE, CDC *pDC = NULL);

	static INT CALLBACK EnumFontsProc(CONST LOGFONT *pLogFont, CONST TEXTMETRIC *pTextMetric, DWORD dwFontType, LPARAM pData);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsFontsComboBox)
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
	//{{AFX_MSG(CMimicsFontsComboBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg LRESULT OnDir(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline INT CMimicsFontsComboBox::Dir(DWORD dwFlags, BOOL bSymbolCharSets, CDC *pDC)
{
	return((INT)SendMessage(FCB_DIR, (dwFlags & 0x7FFFFFFF) | ((bSymbolCharSets) ? 0x80000000 : 0), (LPARAM)((AfxIsValidAddress(pDC, sizeof(CDC))) ? pDC->GetSafeHdc() : (HDC)NULL)));
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsFontsComboBox window

class CResourceMimicsFontsComboBox : public CMimicsFontsComboBox
{
	DECLARE_DYNCREATE(CResourceMimicsFontsComboBox)

	// Construction
public:
	CResourceMimicsFontsComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsFontsComboBox)
protected:
	virtual WNDPROC *GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsFontsComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsAlignmentComboBox window

// Specify the mimics alignment combobox control flags
#define AL_HLEFTVTOP   0
#define AL_HLEFTVCENTER   1
#define AL_HLEFTVBOTTOM   2
#define AL_HCENTERVTOP   3
#define AL_HCENTERVCENTER   4
#define AL_HCENTERVBOTTOM   5
#define AL_HRIGHTVTOP   6
#define AL_HRIGHTVCENTER   7
#define AL_HRIGHTVBOTTOM   8
// Specify the mimics alignment combobox control message identifiers
#define ALCB_ADDALIGNMENT   (WM_USER+50)
#define ALCB_INSERTALIGNMENT   (WM_USER+51)
#define ALCB_GETALIGNMENT   (WM_USER+52)
#define ALCB_FINDALIGNMENT   (WM_USER+53)
#define ALCB_SELECTALIGNMENT   (WM_USER+54)
#define ALCB_DELETEALIGNMENT   (WM_USER+55)
#define ALCB_RESETALIGNMENTS   (WM_USER+56)
// Specify the mimics alignment combobox control styles
#define ALCBS_LEFT   0x0000
#define ALCBS_CENTER   0x0004
#define ALCBS_RIGHT   0x0008

class CMimicsAlignmentComboBox : public CComboBox
{
	DECLARE_DYNCREATE(CMimicsAlignmentComboBox)

	// Construction
public:
	CMimicsAlignmentComboBox();

	// Attributes
protected:
	DWORD  m_dwStyle;
private:
	HBITMAP  m_hImageBitmap[9];

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle = WS_VISIBLE | WS_TABSTOP);

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
	//{{AFX_VIRTUAL(CMimicsAlignmentComboBox)
public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsAlignmentComboBox)
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
inline INT CMimicsAlignmentComboBox::AddAlignment(UINT nAlignment)
{
	return((INT)SendMessage(ALCB_ADDALIGNMENT, (WPARAM)NULL, (LPARAM)nAlignment));
}
inline INT CMimicsAlignmentComboBox::InsertAlignment(INT nIndex, UINT nAlignment)
{
	return((INT)SendMessage(ALCB_INSERTALIGNMENT, nIndex, (LPARAM)nAlignment));
}
inline UINT CMimicsAlignmentComboBox::GetAlignment(INT nIndex) CONST
{
	return((COLORREF) ::SendMessage(GetSafeHwnd(), ALCB_GETALIGNMENT, nIndex, (LPARAM)NULL));
}
inline INT CMimicsAlignmentComboBox::FindAlignment(INT nIndex, UINT nAlignment) CONST
{
	return((INT) ::SendMessage(GetSafeHwnd(), ALCB_FINDALIGNMENT, nIndex, (LPARAM)nAlignment));
}
inline INT CMimicsAlignmentComboBox::SelectAlignment(INT nIndex, UINT nAlignment)
{
	return((INT)SendMessage(ALCB_SELECTALIGNMENT, nIndex, (LPARAM)nAlignment));
}
inline INT CMimicsAlignmentComboBox::DeleteAlignment(UINT nAlignment)
{
	return((INT)SendMessage(ALCB_DELETEALIGNMENT, (WPARAM)NULL, (LPARAM)nAlignment));
}
inline VOID CMimicsAlignmentComboBox::ResetAlignments()
{
	SendMessage(ALCB_RESETALIGNMENTS);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsAlignmentComboBox window

class CResourceMimicsAlignmentComboBox : public CMimicsAlignmentComboBox
{
	DECLARE_DYNCREATE(CResourceMimicsAlignmentComboBox)

	// Construction
public:
	CResourceMimicsAlignmentComboBox(HWND hWnd = NULL);

	// Attributes
public:
	static WNDPROC  m_lpfnSuperWndProc;

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsAlignmentComboBox)
protected:
	virtual WNDPROC *GetSuperWndProcAddr();
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsAlignmentComboBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsSpinButtons window

class CMimicsSpinButtons : public CSpinButtonCtrl
{
	DECLARE_DYNCREATE(CMimicsSpinButtons)

	// Construction
public:
	CMimicsSpinButtons();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsSpinButtons)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsSpinButtons)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsSpinBox window

// Specify the mimics spin box control message identifiers
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
// Specify the mimics spin box control notification identifiers
#define SBXN_SETFOCUS   0x10
#define SBXN_KILLFOCUS   0x11
#define SBXN_CHANGE   0x12
#define SBXN_UPDATE   0x13
// Specify the mimics spin control timer related identifiers
#define SPINBOX_UI_TIMERID   100
#define SPINBOX_UI_TIMEOUT   500

class CMimicsSpinBox : public CWnd
{
	DECLARE_DYNCREATE(CMimicsSpinBox)

	// Construction
public:
	CMimicsSpinBox();

	// Attributes
protected:
	DWORD  m_dwStyle;
	CMimicsNumberEdit  m_wndEditCtrl;
	CMimicsSpinButtons  m_wndSpinCtrl;
	CFont  m_cFont;
	BOOL  m_bState[2];

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle = ES_LEFT | WS_VISIBLE | WS_TABSTOP);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	BOOL SetPos(LONGLONG nPos);
	LONGLONG GetPos() CONST;
	BOOL SetBase(UINT nBase, UINT nDigits = 0);
	BOOL GetBase(UINT &nBase, UINT &nDigits) CONST;
	BOOL SetRange(LONGLONG nMin, LONGLONG nMax);
	BOOL GetRange(LONGLONG &nMin, LONGLONG &nMax) CONST;
	BOOL SetAccel(INT nAccel, CONST UDACCEL *pAccel);
	UINT GetAccel(INT nAccel, UDACCEL *pAccel) CONST;

	BOOL SetSel(INT nStartPos, INT nStopPos);
	BOOL GetSel(INT &nStartPos, INT &nStopPos) CONST;

private:
	INT CalcIndent();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsSpinBox)
public:
	virtual void UpdateUI();
	virtual void UpdateUI(CONST POINT &point);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsSpinBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
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
__declspec(dllexport) BOOL MimicsSpinbox_SetPos(CWnd *pCtrl, LONGLONG nPos);
__declspec(dllexport) LONGLONG MimicsSpinbox_GetPos(CWnd *pCtrl);
__declspec(dllexport) BOOL MimicsSpinbox_SetBase(CWnd *pCtrl, UINT nBase, UINT nDigits);
__declspec(dllexport) BOOL MimicsSpinbox_GetBase(CWnd *pCtrl, UINT &nBase, UINT &nDigits);
__declspec(dllexport) BOOL MimicsSpinbox_SetRange(CWnd *pCtrl, LONGLONG nMin, LONGLONG nMax);
__declspec(dllexport) BOOL MimicsSpinbox_GetRange(CWnd *pCtrl, LONGLONG &nMin, LONGLONG &nMax);
__declspec(dllexport) BOOL MimicsSpinbox_SetAccel(CWnd *pCtrl, INT nAccel, CONST UDACCEL *pAccel);
__declspec(dllexport) UINT MimicsSpinbox_GetAccel(CWnd *pCtrl, INT nAccel, UDACCEL *pAccel);
__declspec(dllexport) BOOL MimicsSpinbox_SetSel(CWnd *pCtrl, INT nStartPos, INT nStopPos);
__declspec(dllexport) BOOL MimicsSpinbox_GetSel(CWnd *pCtrl, INT &nStartPos, INT &nStopPos);

// Specify the associated inline definitions
inline BOOL CMimicsSpinBox::SetPos(LONGLONG nPos)
{
	return(MimicsSpinbox_SetPos(CMimicsSpinBox::FromHandle(GetSafeHwnd()), nPos));
}
inline LONGLONG CMimicsSpinBox::GetPos() CONST
{
	return(MimicsSpinbox_GetPos(CMimicsSpinBox::FromHandle(GetSafeHwnd())));
}
inline BOOL CMimicsSpinBox::SetBase(UINT nBase, UINT nDigits)
{
	return(MimicsSpinbox_SetBase(CMimicsSpinBox::FromHandle(GetSafeHwnd()), nBase, nDigits));
}
inline BOOL CMimicsSpinBox::GetBase(UINT &nBase, UINT &nDigits) CONST
{
	return(MimicsSpinbox_GetBase(CMimicsSpinBox::FromHandle(GetSafeHwnd()), nBase, nDigits));
}
inline BOOL CMimicsSpinBox::SetRange(LONGLONG nMin, LONGLONG nMax)
{
	return(MimicsSpinbox_SetRange(CMimicsSpinBox::FromHandle(GetSafeHwnd()), nMin, nMax));
}
inline BOOL CMimicsSpinBox::GetRange(LONGLONG &nMin, LONGLONG &nMax) CONST
{
	return(MimicsSpinbox_GetRange(CMimicsSpinBox::FromHandle(GetSafeHwnd()), nMin, nMax));
}
inline BOOL CMimicsSpinBox::SetAccel(INT nAccel, CONST UDACCEL *pAccel)
{
	return(MimicsSpinbox_SetAccel(CMimicsSpinBox::FromHandle(GetSafeHwnd()), nAccel, pAccel));
}
inline UINT CMimicsSpinBox::GetAccel(INT nAccel, UDACCEL *pAccel) CONST
{
	return(MimicsSpinbox_GetAccel(CMimicsSpinBox::FromHandle(GetSafeHwnd()), nAccel, pAccel));
}
inline BOOL CMimicsSpinBox::SetSel(INT nStartPos, INT nStopPos)
{
	return(MimicsSpinbox_SetSel(CMimicsSpinBox::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}
inline BOOL CMimicsSpinBox::GetSel(INT &nStartPos, INT &nStopPos) CONST
{
	return(MimicsSpinbox_GetSel(CMimicsSpinBox::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsSpinBox window

class CResourceMimicsSpinBox : public CMimicsSpinBox
{
	DECLARE_DYNCREATE(CResourceMimicsSpinBox)

	// Construction
public:
	CResourceMimicsSpinBox(HWND hWnd = NULL);

	// Attributes
public:

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsSpinBox)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsSpinBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMimicsTimeSpinBox window

// Specify the mimics time spin box control message identifiers
#define TSBXM_SETTIME   (WM_USER+67)
#define TSBXM_GETTIME   (WM_USER+68)
#define TSBXM_SETRANGE   (WM_USER+69)
#define TSBXM_GETRANGE   (WM_USER+70)
#define TSBXM_SETSEL   (WM_USER+71)
#define TSBXM_GETSEL   (WM_USER+72)
// Specify the mimics time spin box control notification identifiers
#define TSBXN_SETFOCUS   0x20
#define TSBXN_KILLFOCUS   0x21
#define TSBXN_CHANGE   0x22
#define TSBXN_UPDATE   0x23
// Specify the mimics time spin box control styles
#define TSBXS_ANY_TIME   0
#define TSBXS_PAST_TIME   (1<<0)
#define TSBXS_FUTURE_TIME   (1<<1)
#define TSBXS_UTC_TIME   (1<<2)
#define TSBXS_SPAN_TIME   (1<<3)
#define TSBXS_HIDE_TIME   (1<<4)
// Specify the mimics time spin box control related macros
#define MAKETIMESPINBOXLIMITS(l,h)   ((LONGLONG) (((ULONGLONG) (DWORD) (INT) (l)) | (((ULONGLONG) (DWORD) (INT) (h)) << 32)))
#define TIMESPINBOXLOWLIMIT(x)   ((INT) (x))
#define TIMESPINBOXHIGHLIMIT(x)   ((INT) (((ULONGLONG) (x)) >> 32))
// Specify the mimics time spin box control timer related identifiers
#define TIMESPINBOX_UI_TIMERID   100
#define TIMESPINBOX_UI_TIMEOUT   500

class CMimicsTimeSpinBox : public CWnd
{
	DECLARE_DYNCREATE(CMimicsTimeSpinBox)

	// Construction
public:
	CMimicsTimeSpinBox();

	// Attributes
protected:
	DWORD  m_dwStyle;
	CPtrArray  m_pwndEditCtrls;
	CPtrArray  m_pwndStaticCtrls;
	CMimicsSpinButtons  m_wndSpinCtrl;
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
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, UINT nID, DWORD dwStyle = TSBXS_ANY_TIME | TSBXS_UTC_TIME | WS_VISIBLE | WS_TABSTOP, LPCTSTR pszFormat = NULL, CONST CTimeTag &tStartTime = 0, CONST CTimeTag &StopTime = 0);

	static BOOL RegisterClass();
	static BOOL UnregisterClass();

	VOID SetTime(CONST CTimeTag &tTime);
	VOID SetTime(CONST CTimeKey &tTime);
	BOOL GetTime(CTimeTag &tTime) CONST;
	BOOL GetTime(CTimeKey &tTime) CONST;
	CTimeKey GetTime() CONST;
	BOOL SetRange(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime);
	BOOL SetRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL GetRange(CTimeTag &tStartTime, CTimeTag &tStopTime) CONST;
	BOOL GetRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST;
	BOOL SetSel(INT nStartPos, INT nStopPos);
	BOOL GetSel(INT &nStartPos, INT &nStopPos) CONST;

protected:
	VOID EnableAutoCompletion(BOOL bEnable = TRUE);
	BOOL IsAutoCompletionEnabled() CONST;

	INT TranslateSubFormat(LPCTSTR pszFormat) CONST;
	BOOL TranslateSubFormatDelimiter(LPCTSTR pszFormat, CString &szDelimiter) CONST;
	BOOL TranslateSubFormatPosition(LPCTSTR pszFormat, CONST RECT &rect, CRect &rSubFormat);

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
	//{{AFX_VIRTUAL(CMimicsTimeSpinBox)
public:
	virtual VOID SetTime();
public:
	virtual void UpdateUI();
	virtual void UpdateUI(CONST POINT &point);
protected:
	virtual LONGLONG EnumSubFormatLimits(INT nSubFormatID) CONST;
	virtual INT EnumSubFormatLimits(INT nSubFormatID, CStringArray &szNames) CONST;
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMimicsTimeSpinBox)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
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
__declspec(dllexport) VOID MimicsTimespinbox_SetTime(CWnd *pCtrl);
__declspec(dllexport) VOID MimicsTimespinbox_SetTime(CWnd *pCtrl, CONST CTimeTag &tTime);
__declspec(dllexport) VOID MimicsTimespinbox_SetTime(CWnd *pCtrl, CONST CTimeKey &tTime);
__declspec(dllexport) CTimeKey MimicsTimespinbox_GetTime(CWnd *pCtrl);
__declspec(dllexport) BOOL MimicsTimespinbox_GetTime(CWnd *pCtrl, CTimeTag &tTime);
__declspec(dllexport) BOOL MimicsTimespinbox_GetTime(CWnd *pCtrl, CTimeKey &tTime);
__declspec(dllexport) BOOL MimicsTimespinbox_SetRange(CWnd *pCtrl, CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime);
__declspec(dllexport) BOOL MimicsTimespinbox_SetRange(CWnd *pCtrl, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
__declspec(dllexport) BOOL MimicsTimespinbox_GetRange(CWnd *pCtrl, CTimeTag &tStartTime, CTimeTag &tStopTime);
__declspec(dllexport) BOOL MimicsTimespinbox_GetRange(CWnd *pCtrl, CTimeKey &tStartTime, CTimeKey &tStopTime);
__declspec(dllexport) BOOL MimicsTimespinbox_SetSel(CWnd *pCtrl, INT nStartPos, INT nStopPos);
__declspec(dllexport) BOOL MimicsTimespinbox_GetSel(CWnd *pCtrl, INT &nStartPos, INT &nStopPos);

// Specify the associated inline definitions
inline VOID CMimicsTimeSpinBox::SetTime()
{
	return(MimicsTimespinbox_SetTime(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd())));
}
inline VOID CMimicsTimeSpinBox::SetTime(CONST CTimeTag &tTime)
{
	return(MimicsTimespinbox_SetTime(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd()), tTime));
}
inline VOID CMimicsTimeSpinBox::SetTime(CONST CTimeKey &tTime)
{
	return(MimicsTimespinbox_SetTime(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd()), tTime));
}
inline BOOL CMimicsTimeSpinBox::GetTime(CTimeTag &tTime) CONST
{
	return(MimicsTimespinbox_GetTime(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd()), tTime));
}
inline BOOL CMimicsTimeSpinBox::GetTime(CTimeKey &tTime) CONST
{
	return(MimicsTimespinbox_GetTime(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd()), tTime));
}
inline CTimeKey CMimicsTimeSpinBox::GetTime() CONST
{
	return(MimicsTimespinbox_GetTime(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd())));
}
inline BOOL CMimicsTimeSpinBox::SetRange(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime)
{
	return(MimicsTimespinbox_SetRange(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd()), tStartTime, tStopTime));
}
inline BOOL CMimicsTimeSpinBox::SetRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	return(MimicsTimespinbox_SetRange(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd()), tStartTime, tStopTime));
}
inline BOOL CMimicsTimeSpinBox::GetRange(CTimeTag &tStartTime, CTimeTag &tStopTime) CONST
{
	return(MimicsTimespinbox_GetRange(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd()), tStartTime, tStopTime));
}
inline BOOL CMimicsTimeSpinBox::GetRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	return(MimicsTimespinbox_GetRange(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd()), tStartTime, tStopTime));
}
inline BOOL CMimicsTimeSpinBox::SetSel(INT nStartPos, INT nStopPos)
{
	return(MimicsTimespinbox_SetSel(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}
inline BOOL CMimicsTimeSpinBox::GetSel(INT &nStartPos, INT &nStopPos) CONST
{
	return(MimicsTimespinbox_GetSel(CMimicsTimeSpinBox::FromHandle(GetSafeHwnd()), nStartPos, nStopPos));
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CResourceMimicsTimeSpinBox window

class CResourceMimicsTimeSpinBox : public CMimicsTimeSpinBox
{
	DECLARE_DYNCREATE(CResourceMimicsTimeSpinBox)

	// Construction
public:
	CResourceMimicsTimeSpinBox(HWND hWnd = NULL);

	// Attributes
public:

	// Operations
public:
	static LRESULT CALLBACK WndProcHook(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResourceMimicsTimeSpinBox)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CResourceMimicsTimeSpinBox)
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Listbox helpers

__declspec(dllexport) BOOL Listbox_SetText(CWnd *pCtrl, INT nItem, LPCTSTR pszText);
__declspec(dllexport) CString Listbox_GetText(CWnd *pCtrl, INT nItem);

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Combobox helpers

__declspec(dllexport) BOOL Combobox_SetText(CWnd *pCtrl, INT nItem, LPCTSTR pszText);
__declspec(dllexport) CString Combobox_GetText(CWnd *pCtrl, INT nItem);

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Listview helpers

__declspec(dllexport) BOOL Listview_InsertColumn(CWnd *pCtrl, INT nColumn, LPCTSTR pszColumn, INT nWidth);
__declspec(dllexport) BOOL Listview_SetColumn(CWnd *pCtrl, INT nColumn, LPCTSTR pszColumn, INT nWidth = -1);
__declspec(dllexport) BOOL Listview_GetColumn(CWnd *pCtrl, INT nColumn, CString &szColumn, INT &nWidth);
__declspec(dllexport) BOOL Listview_DeleteColumn(CWnd *pCtrl, INT nColumn);
__declspec(dllexport) BOOL Listview_InsertText(CWnd *pCtrl, INT nItem, LPCTSTR pszText);
__declspec(dllexport) BOOL Listview_SetText(CWnd *pCtrl, INT nItem, INT nSubItem, LPCTSTR pszText);
__declspec(dllexport) CString Listview_GetText(CWnd *pCtrl, INT nItem, INT nSubItem);
__declspec(dllexport) BOOL Listview_SetCurText(CWnd *pCtrl, INT nItem);
__declspec(dllexport) INT Listview_GetCurText(CWnd *pCtrl);
__declspec(dllexport) BOOL Listview_SetSelText(CWnd *pCtrl, CONST CUIntArray &nItems);
__declspec(dllexport) BOOL Listview_IsSelText(CWnd *pCtrl, INT nItem);
__declspec(dllexport) INT Listview_GetSelText(CWnd *pCtrl, CUIntArray &nItems);
__declspec(dllexport) BOOL Listview_DeleteText(CWnd *pCtrl, INT nItem);

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSCONTROLS_H__
