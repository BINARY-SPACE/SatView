// GRD.H : Graphic Display Form Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the graphic display form related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2003/10/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __GRD_H__
#define __GRD_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CGRDSaveDialog dialog

#define IDC_GRD_SAVE_DETAILS   1001
#define IDC_GRD_SAVE_DATABASE_STATIC   1002
#define IDC_GRD_SAVE_DATABASE   1003
#define IDC_GRD_SAVE_FILENAME_STATIC   1004
#define IDC_GRD_SAVE_FILENAME   1005
#define IDC_GRD_SAVE_FILENAME_BROWSE   1006
#define IDC_GRD_SAVE_COMMENT_STATIC   1007
#define IDC_GRD_SAVE_COMMENT   1008
#define IDC_GRD_SAVE_DIRECTORY_STATIC   1009
#define IDC_GRD_SAVE_DIRECTORY   1010
#define IDC_GRD_SAVE_HELP   1011

class CGRDSaveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CGRDSaveDialog)

	// Construction
public:
	CGRDSaveDialog();   // standard constructor

	// Attributes
private:
	CString  m_szFileName;
	CGRDLayouts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CGRDSaveDialog)
	enum { IDD = IDD_GRD_SAVE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CString &szFileName);

	class CGRDWnd *GetParentDisplay() CONST;

private:
	VOID EnumGRDs();

	BOOL FindGRD(LPCTSTR pszName) CONST;

	BOOL CheckFileName(LPCTSTR pszFileName) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDSaveDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDSaveDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBrowseFileName();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDOpenDialog dialog

#define IDC_GRD_OPEN_DETAILS   1001
#define IDC_GRD_OPEN_DATABASE_STATIC   1002
#define IDC_GRD_OPEN_DATABASE   1003
#define IDC_GRD_OPEN_DIRECTORY_STATIC   1004
#define IDC_GRD_OPEN_DIRECTORY   1005
#define IDC_GRD_OPEN_HELP   1006

class CGRDOpenDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CGRDOpenDialog)

	// Construction
public:
	CGRDOpenDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CGRDLayouts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CGRDsOpenDialog)
	enum { IDD = IDD_GRD_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumGRDs();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDOpenDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDOpenDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDImportDialog dialog

#define IDC_GRD_IMPORT_DETAILS   1001
#define IDC_GRD_IMPORT_FILENAME_STATIC   1002
#define IDC_GRD_IMPORT_FILENAME   1003
#define IDC_GRD_IMPORT_BROWSE   1004
#define IDC_GRD_IMPORT_DIRECTORY   1005
#define IDC_GRD_IMPORT_TYPE   1006
#define IDC_GRD_IMPORT_TYPE_DEFAULT   1007
#define IDC_GRD_IMPORT_TYPE_CUSTOM   1008
#define IDC_GRD_IMPORT_TYPE_CUSTOM_NAME   1009
#define IDC_GRD_IMPORT_TYPE_CUSTOM_NAME_STATIC   1010
#define IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC   1011
#define IDC_GRD_IMPORT_TYPE_CUSTOM_DESCRIPTION    1012
#define IDC_GRD_IMPORT_HELP   1013

class CGRDImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CGRDImportDialog)

	// Construction
public:
	CGRDImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CGRDLayouts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CGRDImportDialog)
	enum { IDD = IDD_GRD_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumGRDs();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDImportDialog)
public:
	virtual INT_PTR DoModal(CGRDLayouts &pLayouts);
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDImportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeTitle();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDExportDialog dialog

#define IDC_GRD_EXPORT_DETAILS   1001
#define IDC_GRD_EXPORT_DIRECTORY_STATIC   1002
#define IDC_GRD_EXPORT_DIRECTORY   1003
#define IDC_GRD_EXPORT_FILENAME_STATIC   1004
#define IDC_GRD_EXPORT_FILENAME   1005
#define IDC_GRD_EXPORT_BROWSE   1006
#define IDC_GRD_EXPORT_TYPE   1007
#define IDC_GRD_EXPORT_TYPE_DEFAULT   1008
#define IDC_GRD_EXPORT_TYPE_CUSTOM   1009
#define IDC_GRD_EXPORT_TYPE_CUSTOM_NAME   1010
#define IDC_GRD_EXPORT_TYPE_CUSTOM_NAME_STATIC   1011
#define IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC   1012
#define IDC_GRD_EXPORT_TYPE_CUSTOM_DESCRIPTION   1013
#define IDC_GRD_EXPORT_HELP   1014

class CGRDExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CGRDExportDialog)

	// Construction
public:
	CGRDExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CGRDLayouts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CGRDExportDialog)
	enum { IDD = IDD_GRD_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumGRDs();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDExportDialog)
public:
	virtual INT_PTR DoModal();
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDExportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeTitle();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDPropertiesDialog dialog

#define IDC_GRD_PROPERTIES_DETAILS   1001
#define IDC_GRD_PROPERTIES_FONTS_STATIC   1002
#define IDC_GRD_PROPERTIES_FONTS_TITLE   1003
#define IDC_GRD_PROPERTIES_FONTS_ITEMS   1004
#define IDC_GRD_PROPERTIES_FONTS_NAME_STATIC   1005
#define IDC_GRD_PROPERTIES_FONTS_NAME   1006
#define IDC_GRD_PROPERTIES_FONTS_STYLE_STATIC   1007
#define IDC_GRD_PROPERTIES_FONTS_STYLE   1008
#define IDC_GRD_PROPERTIES_FONTS_SIZE_STATIC   1009
#define IDC_GRD_PROPERTIES_FONTS_SIZE   1010
#define IDC_GRD_PROPERTIES_FONTS_COLOR_STATIC   1011
#define IDC_GRD_PROPERTIES_FONTS_COLOR   1012
#define IDC_GRD_PROPERTIES_FONTS_SAMPLE   1013
#define IDC_GRD_PROPERTIES_FONTS_SAMPLETEXT   1014
#define IDC_GRD_PROPERTIES_COLORS_STATIC   1015
#define IDC_GRD_PROPERTIES_COLORS_TITLE_STATIC 1016
#define IDC_GRD_PROPERTIES_COLORS_TITLE   1017
#define IDC_GRD_PROPERTIES_COLORS_KEYS_STATIC   1018
#define IDC_GRD_PROPERTIES_COLORS_KEYS   1019
#define IDC_GRD_PROPERTIES_HELP   1020

class CGRDPropertiesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CGRDPropertiesDialog)

	// Construction
public:
	CGRDPropertiesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	LOGFONT  m_lfTable[2][2];
	COLORREF  m_nTableColors[2][2];
	COLORREF  m_nTableFontColors[2][2];
	CString  m_szFontSampleText;

	// Dialog Data
	//{{AFX_DATA(CGRDPropertiesDialog)
	enum { IDD = IDD_GRD_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID ShowFontDetails();
	VOID ShowFontSample();

	class CGRDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDPropertiesDialog)
public:
	virtual INT_PTR DoModal(class CGRDWnd *pParentWnd);
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg void OnTitleFont();
	afx_msg void OnItemsFont();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeFontColor();
	afx_msg void OnSelchangeTitleBackgroundColor();
	afx_msg void OnSelchangeKeysBackgroundColor();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDFindDialog dialog

#define IDC_GRD_FIND_TEXT_STATIC   1001
#define IDC_GRD_FIND_TEXT   1002
#define IDC_GRD_FIND_DIRECTION   1003
#define IDC_GRD_FIND_DIRECTION_UP   1004
#define IDC_GRD_FIND_DIRECTION_DOWN   1005
#define IDC_GRD_FIND_ALL   1006
#define IDC_GRD_FIND_CASE   1007
#define IDC_GRD_FIND_WORD   1008
#define IDC_GRD_FIND_NEXT   1009
#define IDC_GRD_FIND_HELP   1010

class CGRDFindDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CGRDFindDialog)

	// Construction
public:
	CGRDFindDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szSearchItems;

	// Dialog Data
	//{{AFX_DATA(CGRDFindDialog)
	enum { IDD = IDD_GRD_FIND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CGRDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDFindDialog)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnFindText();
	afx_msg void OnSelchangeText();
	afx_msg void OnEditchangeText();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDReplaceDialog dialog

#define IDC_GRD_REPLACE_FINDTEXT_STATIC   1001
#define IDC_GRD_REPLACE_FINDTEXT   1002
#define IDC_GRD_REPLACE_TEXT_STATIC   1003
#define IDC_GRD_REPLACE_TEXT   1004
#define IDC_GRD_REPLACE_DIRECTION   1005
#define IDC_GRD_REPLACE_DIRECTION_UP   1006
#define IDC_GRD_REPLACE_DIRECTION_DOWN   1007
#define IDC_GRD_REPLACE_ALL   1008
#define IDC_GRD_REPLACE_CASE   1009
#define IDC_GRD_REPLACE_WORD   1010
#define IDC_GRD_REPLACE_FINDNEXT   1011
#define IDC_GRD_REPLACE_NEXT   1012
#define IDC_GRD_REPLACE_ALLNEXT   1013
#define IDC_GRD_REPLACE_HELP   1014

class CGRDReplaceDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CGRDReplaceDialog)

	// Construction
public:
	CGRDReplaceDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szItems[2];

	// Dialog Data
	//{{AFX_DATA(CGRDReplaceDialog)
	enum { IDD = IDD_GRD_REPLACE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CGRDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDReplaceDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDReplaceDialog)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnFindNextText();
	afx_msg void OnReplaceText();
	afx_msg void OnReplaceAllText();
	afx_msg void OnSelchangeFindText();
	afx_msg void OnEditchangeFindText();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDGoToDialog dialog

#define IDC_GRD_GOTO_LINE_STATIC   1001
#define IDC_GRD_GOTO_LINE   1002
#define IDC_GRD_GOTO_LINENUMBER   1003
#define IDC_GRD_GOTO_JUMPDOWN   1004
#define IDC_GRD_GOTO_JUMPDOWNLINE   1005
#define IDC_GRD_GOTO_JUMPDOWN_STATIC   1006
#define IDC_GRD_GOTO_JUMPUP   1007
#define IDC_GRD_GOTO_JUMPUPLINE   1008
#define IDC_GRD_GOTO_JUMPUP_STATIC   1009
#define IDC_GRD_GOTO_JUMP   1010
#define IDC_GRD_GOTO_HELP   1011

class CGRDGoToDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CGRDGoToDialog)

	// Construction
public:
	CGRDGoToDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CGRDGoToDialog)
	enum { IDD = IDD_GRD_GOTO_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CGRDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDGoToDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGRDGoToDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLineNumber();
	afx_msg void OnJumpLineDown();
	afx_msg void OnJumpLineUp();
	afx_msg void OnJump();
	afx_msg void OnEditchangeLineNumber();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDStatusBar window

class CGRDStatusBar : public CMFCStatusBar
{
	DECLARE_DYNCREATE(CGRDStatusBar)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pIDs, INT nCount);

	BOOL SetPaneText(UINT nID, LPCTSTR pszText);
	BOOL GetPaneText(UINT nID, CString &szText) CONST;
	CString GetPaneText(UINT nID) CONST;

private:
	INT CalcPaneWidth(INT nIndex) CONST;
	INT CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDStatusBar)
private:
	virtual VOID Initialize();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDStatusBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDTableView view

class CGRDTableView : public CDisplayTableView
{
	DECLARE_DYNCREATE(CGRDTableView)

	// Construction
public:
	CGRDTableView();

	// Attributes
public:

	// Operations
public:
	VOID SetTitle(LPCTSTR pszName, LPCTSTR pszTitle);
	BOOL GetTitle(CString &szName, CString &szTitle) CONST;
	BOOL SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground);
	BOOL GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;

	class CGRDWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDTableView)
public:
	virtual VOID UpdateTableForms(CONST CGRDLayout *pGRDLayout, INT nIndex, BOOL bDelete = FALSE);
private:
	virtual BOOL CheckPrivilege() CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDTableView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDXmlViewDocument

class CGRDXmlViewDocument : public CDocument
{
	DECLARE_DYNAMIC(CGRDXmlViewDocument)

	// Construction
public:
	CGRDXmlViewDocument();
	virtual ~CGRDXmlViewDocument();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDXmlView view

class CGRDXmlView : public CRichEditView
{
	DECLARE_DYNCREATE(CGRDXmlView)

	// Construction
public:
	CGRDXmlView();

	// Attributes
private:
	CGRDFindDialog  m_dlgFind;
	CGRDGoToDialog  m_dlgGoTo;
	CGRDReplaceDialog  m_dlgReplace;
private:
	CString  m_szName;
	CString  m_szCode;
	CString  m_szTitle;
	CString  m_szXmlCode;
private:
	CFont  m_cCodeFont;

	// Operations
public:
	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;

	INT DoSave();
	BOOL CanSave() CONST;
	INT DoSaveAs(LPCTSTR pszFileName);
	BOOL CanSaveAs() CONST;
	BOOL CanPrint() CONST;
	INT DoDelete();
	BOOL CanDelete() CONST;

	VOID DoSelectAll();
	BOOL CanSelectAll() CONST;
	VOID UnSelectAll();
	VOID DoCutSel();
	BOOL CanCutSel() CONST;
	VOID DoCopySel();
	BOOL CanCopySel() CONST;
	VOID DoPasteSel();
	BOOL CanPasteSel() CONST;
	VOID DoDeleteSel();
	BOOL CanDeleteSel() CONST;
	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;
	BOOL DoEmpty();
	BOOL IsEmpty() CONST;

	VOID DoFind();
	BOOL CanFind() CONST;
	VOID DoFindNext();
	VOID DoFindNext(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindNext() CONST;
	VOID DoFindPrevious();
	VOID DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindPrevious() CONST;
	VOID DoReplace();
	BOOL CanReplace() CONST;
	VOID DoGoTo();
	BOOL CanGoTo() CONST;

	BOOL Search(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL Replace(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceAll(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL GoTo(UINT nLine, BOOL bDown = FALSE, BOOL bUp = FALSE);
	BOOL GoTo(LPCTSTR pszLine);

	BOOL IsModified() CONST;
	BOOL Check() CONST;

	class CGRDWnd *GetParent() CONST;

private:
	CString ConstructXmlHeader() CONST;
	INT CalculateXmlHeaderLength() CONST;

	BOOL IsMouseOnXmlHeader(CONST POINT &point) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDXmlView)
public:
	virtual BOOL Create(CWnd *pParentWnd, LPCTSTR pszName, CONST RECT &rect);
	virtual void PostNcDestroy();
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CGRDXmlView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditchangeCode();
	afx_msg void OnEditupdateCode();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGRDWnd

// Specify the graphic display form statusbar pane identifiers
#define ID_GRD_STATUSBAR_DETAILSPANE   ID_SEPARATOR
#define ID_GRD_STATUSBAR_FLAGPANE   ID_STATUSBAR_PANE1
#define ID_GRD_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class CGRDWnd : public CDisplayWnd
{
	DECLARE_DYNCREATE(CGRDWnd)

	// Construction
public:
	CGRDWnd();
	CGRDWnd(LPCTSTR pszName);

	// Attributes
private:
	CGRDXmlView  m_wndXmlView;
	CGRDTableView  m_wndTableView;
	CGRDStatusBar  m_wndStatusBar;
private:
	CGRDPropertiesDialog  m_dlgProperties;

	// Operations
public:
	BOOL Create(CMDIFrameWnd *pParentWnd, UINT nShow = -1);
	BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszName, UINT nShow = -1);

	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	BOOL SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground);
	BOOL GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;

	BOOL Search(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL Replace(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceAll(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL GoTo(UINT nLine, BOOL bDown = FALSE, BOOL bUp = FALSE);
	BOOL GoTo(LPCTSTR pszLine);

	VOID UpdateBars();

private:
	VOID UpdateTitle();
	VOID UpdateMenus();
	VOID UpdateStatusBar();

	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, LPCTSTR pszForm, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, WORD wFromPage = -1, WORD wToPage = -1);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CPtrArray &pFonts, LPRECT prClip, UINT nFlags, INT nPage = -1, BOOL bCalc = FALSE);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nFlags, BOOL bCalc = FALSE);

public:
	static INT Delete(LPCTSTR pszName);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGRDWnd)
public:
	virtual BOOL IsNew() CONST;
	virtual BOOL IsModified() CONST;
	virtual BOOL Save(INT nPosition) CONST;
	virtual INT Load(INT nPosition);
	virtual BOOL UpdateProperties();
	virtual BOOL IsUpdatingProperties() CONST;
	virtual BOOL HasProperties() CONST;
	virtual BOOL CheckTableDropTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point) CONST;
	virtual BOOL DropOnTableTarget(LPCTSTR pszTable, ULONGLONG nComponent, CONST POINT &point);
	virtual VOID UpdateAllPanes(LPCTSTR pszDetails, LPCTSTR pszFlag, LPCTSTR pszType);
	virtual BOOL Print(PRINTDLG *pPrintInfo, UINT nFlags);
public:
	virtual VOID DoSave();
	virtual BOOL CanSave() CONST;
	virtual VOID DoSaveAs();
	virtual BOOL CanSaveAs() CONST;
	virtual VOID DoCheck();
	virtual BOOL CanCheck() CONST;
	virtual VOID DoDelete();
	virtual BOOL CanDelete() CONST;
	virtual VOID DoUndo();
	virtual BOOL CanUndo() CONST;
	virtual VOID DoRedo();
	virtual BOOL CanRedo() CONST;
	virtual VOID DoFind();
	virtual BOOL CanFind() CONST;
	virtual VOID DoFindNext(BOOL bMatchCase, BOOL bMatchWord);
	virtual VOID DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	virtual BOOL CanFindNext() CONST;
	virtual VOID DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord);
	virtual VOID DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	virtual BOOL CanFindPrevious() CONST;
	virtual VOID DoReplace();
	virtual BOOL CanReplace() CONST;
	virtual VOID DoGoTo();
	virtual BOOL CanGoTo() CONST;
	virtual VOID DoSelectAll();
	virtual BOOL CanSelectAll() CONST;
	virtual VOID DoCutSel();
	virtual BOOL CanCutSel() CONST;
	virtual VOID DoCopySel();
	virtual BOOL CanCopySel() CONST;
	virtual VOID DoPasteSel();
	virtual BOOL CanPasteSel() CONST;
	virtual VOID DoDeleteSel();
	virtual BOOL CanDeleteSel() CONST;
	virtual BOOL CanPrint(UINT nFlags) CONST;
	virtual VOID DoClose();
public:
	virtual BOOL DoSaveTable();
	virtual BOOL CanSaveTable() CONST;
	virtual BOOL DoCheckTable();
	virtual BOOL CanCheckTable() CONST;
	virtual BOOL DoDeleteTable();
	virtual BOOL CanDeleteTable() CONST;
	virtual BOOL DoPrintTable();
	virtual BOOL CanPrintTable() CONST;
	virtual BOOL DoPrintAllTables();
	virtual BOOL CanPrintAllTables() CONST;
	virtual BOOL DoImportTables();
	virtual BOOL CanImportTables() CONST;
	virtual BOOL DoExportTables();
	virtual BOOL CanExportTables() CONST;
	virtual BOOL DoDiscardTables();
	virtual BOOL CanDiscardTables() CONST;
	virtual BOOL DoDiscardAllTables();
	virtual BOOL CanDiscardAllTables() CONST;
	virtual BOOL DoResetTables();
	virtual BOOL CanResetTables() CONST;
	virtual BOOL DoInsertTableRowAbove();
	virtual BOOL CanInsertTableRowAbove() CONST;
	virtual BOOL DoInsertTableRowBelow();
	virtual BOOL CanInsertTableRowBelow() CONST;
	virtual BOOL DoInsertTableColumnBefore();
	virtual BOOL CanInsertTableColumnBefore() CONST;
	virtual BOOL DoInsertTableColumnAfter();
	virtual BOOL CanInsertTableColumnAfter() CONST;
	virtual BOOL DoClearTableRow();
	virtual BOOL CanClearTableRow() CONST;
	virtual BOOL DoDeleteTableRow();
	virtual BOOL CanDeleteTableRow() CONST;
	virtual BOOL DoDeleteTableColumn();
	virtual BOOL CanDeleteTableColumn() CONST;
	virtual BOOL DoCopyTableRow();
	virtual BOOL CanCopyTableRow() CONST;
	virtual BOOL DoPasteTableRow();
	virtual BOOL CanPasteTableRow() CONST;
public:
	virtual VOID GotoTable(ULONGLONG nComponent, LPCTSTR pszName);
public:
	virtual VOID UpdateTables(CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabasevTxtCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CANDLayout *pLayout, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CGRDLayouts &pLayouts);
	virtual VOID UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(ULONGLONG nComponent);
	virtual VOID UpdateTables();
protected:
	virtual CString GetPrintDocTitle(LPCTSTR pszName, UINT nFlags) CONST;
	virtual CString GetPrintDocInfoTitle() CONST;
public:
	virtual VOID AdjustToPrivileges();
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CGRDWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
	afx_msg void OnUpdateStatusBarDetailsPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarFlagPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarTypePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __GRD_H__
