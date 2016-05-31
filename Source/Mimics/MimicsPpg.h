// MIMICSPPG.H : Mimics Control Dialog Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the mimics control dialog related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/17 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICSPPG_H__
#define __MIMICSPPG_H__


/////////////////////////////////////////////////////////////////////////////
// CLocalePropertySheetDialog dialog

class CLocalePropertySheetDialog : public CMFCPropertySheet
{
	DECLARE_DYNCREATE(CLocalePropertySheetDialog)

	// Construction
public:
	CLocalePropertySheetDialog();
	CLocalePropertySheetDialog(LPCTSTR pszTitle, CWnd *pParentWnd = NULL);

	// Attributes
private:
	CMFCButton  m_wndButton[3];

	// Operations
public:
	BOOL Create(CWnd *pParentWnd = NULL, DWORD dwStyle = (DWORD)-1, DWORD dwExStyle = 0);

	BOOL Attach(HWND hDlg);
	HWND Detach();

	CWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLocalePropertySheetDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual VOID RepositionButtons();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLocalePropertySheetDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg BOOL OnHelpInfo(HELPINFO *lpHelpInfo);
	afx_msg void OnHelp();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CLocalePropertyPage dialog

class CLocalePropertyPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CLocalePropertyPage)

	// Construction
public:
	CLocalePropertyPage(LPCTSTR pszTitle = NULL, UINT nTemplateID = 0, UINT nCaptionID = 0);

	// Attributes
private:
	UINT  m_nCaptionID;
	UINT  m_nTemplateID;
	CString  m_szTitle;
	CPtrArray  m_pCtrls[2];
	CUIntArray  m_nCtrlIDs[2];
	CUIntArray  m_nCtrlPositions;
private:
	CLocalePropertySheetDialog  *m_pDialog;
	LPDISPATCH  *m_pDispatch;
	HWND  m_hChildSheet;
	HWND  m_hChildWnd;
	HWND  m_hCtrlWnd;
	BOOL  m_bDialog;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;

	COleControl *GetOleControl() CONST;

	CWnd *GetDlgItem(UINT nCtrlID) CONST;

	CLocalePropertySheetDialog *GetParent() CONST;

protected:
	BOOL AccessControl(UINT nCtrlID, BOOL bAccess, BOOL bVisible = TRUE, BOOL bSelections = TRUE);

	HGLOBAL LoadLocalePropertyPageTemplate(UINT nPropertyPageID) CONST;
	HGLOBAL LoadLocalePropertyPageTemplate(LPCTSTR pszPropertyPageName) CONST;

	BOOL SetChildSheet(CPropertySheet *pSheet, CWnd *pItem);
	CPropertySheet *GetChildSheet() CONST;

private:
	BOOL IsControlOfType(CWnd *pCtrl, CRuntimeClass *pClass) CONST;

	VOID UpdateControlContents(CWnd *pCtrl, CComboBox *pComboBox);

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLocalePropertyPage)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified(BOOL bAll = TRUE) CONST;
	virtual BOOL Check(BOOL bAll = TRUE) CONST;
	virtual VOID Update();
protected:
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLocalePropertyPage)
	virtual BOOL OnInitDialog();
	virtual void OnSetPageSite();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd *pWndOther, BOOL bMinimized);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICSPPG_H__
