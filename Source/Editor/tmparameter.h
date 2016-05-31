// TMPARAMETER.H : Telemetry Parameter Form Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telemetry parameter form related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2003/10/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TMPARAMETER_H__
#define __TMPARAMETER_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CTMParameterOpenDialog dialog

#define IDC_TMPARAMETER_OPEN_DETAILS   1001
#define IDC_TMPARAMETER_OPEN_DATABASE_STATIC   1002
#define IDC_TMPARAMETER_OPEN_DATABASE   1003
#define IDC_TMPARAMETER_OPEN_DIRECTORY_STATIC   1004
#define IDC_TMPARAMETER_OPEN_DIRECTORY   1005
#define IDC_TMPARAMETER_OPEN_HELP   1006

class CTMParameterOpenDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTMParameterOpenDialog)

	// Construction
public:
	CTMParameterOpenDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseTMParameters  m_pDatabaseTMParameters;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTMParametersOpenDialog)
	enum { IDD = IDD_TMPARAMETER_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumTMParameters();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTMParameterOpenDialog)
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
	//{{AFX_MSG(CTMParameterOpenDialog)
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
// CTMParameterImportDialog dialog

#define IDC_TMPARAMETER_IMPORT_DETAILS   1001
#define IDC_TMPARAMETER_IMPORT_FILENAME_STATIC   1002
#define IDC_TMPARAMETER_IMPORT_FILENAME   1003
#define IDC_TMPARAMETER_IMPORT_BROWSE   1004
#define IDC_TMPARAMETER_IMPORT_DIRECTORY   1005
#define IDC_TMPARAMETER_IMPORT_TYPE   1006
#define IDC_TMPARAMETER_IMPORT_TYPE_DEFAULT   1007
#define IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM   1008
#define IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG   1009
#define IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_TAG_STATIC   1010
#define IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC   1011
#define IDC_TMPARAMETER_IMPORT_TYPE_CUSTOM_DESCRIPTION    1012
#define IDC_TMPARAMETER_IMPORT_HELP   1013

class CTMParameterImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTMParameterImportDialog)

	// Construction
public:
	CTMParameterImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseTMParameters  m_pDatabaseTMParameters;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTMParameterImportDialog)
	enum { IDD = IDD_TMPARAMETER_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumTMParameters();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTMParameterImportDialog)
public:
	virtual INT_PTR DoModal(CDatabaseTMParameters &pDatabaseTMParameters);
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTMParameterImportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeTag();
	afx_msg void OnEditchangeDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMParameterExportDialog dialog

#define IDC_TMPARAMETER_EXPORT_DETAILS   1001
#define IDC_TMPARAMETER_EXPORT_DIRECTORY_STATIC   1002
#define IDC_TMPARAMETER_EXPORT_DIRECTORY   1003
#define IDC_TMPARAMETER_EXPORT_FILENAME_STATIC   1004
#define IDC_TMPARAMETER_EXPORT_FILENAME   1005
#define IDC_TMPARAMETER_EXPORT_BROWSE   1006
#define IDC_TMPARAMETER_EXPORT_TYPE   1007
#define IDC_TMPARAMETER_EXPORT_TYPE_DEFAULT   1008
#define IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM   1009
#define IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG   1010
#define IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_TAG_STATIC   1011
#define IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC   1012
#define IDC_TMPARAMETER_EXPORT_TYPE_CUSTOM_DESCRIPTION   1013
#define IDC_TMPARAMETER_EXPORT_HELP   1014

class CTMParameterExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTMParameterExportDialog)

	// Construction
public:
	CTMParameterExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseTMParameters  m_pDatabaseTMParameters;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTMParameterExportDialog)
	enum { IDD = IDD_TMPARAMETER_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumTMParameters();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTMParameterExportDialog)
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
	//{{AFX_MSG(CTMParameterExportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeTag();
	afx_msg void OnEditchangeDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMParameterPropertiesDialog dialog

#define IDC_TMPARAMETER_PROPERTIES_DETAILS   1001
#define IDC_TMPARAMETER_PROPERTIES_FONTS_STATIC   1002
#define IDC_TMPARAMETER_PROPERTIES_FONTS_TITLE   1003
#define IDC_TMPARAMETER_PROPERTIES_FONTS_ITEMS   1004
#define IDC_TMPARAMETER_PROPERTIES_FONTS_NAME_STATIC   1005
#define IDC_TMPARAMETER_PROPERTIES_FONTS_NAME   1006
#define IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE_STATIC   1007
#define IDC_TMPARAMETER_PROPERTIES_FONTS_STYLE   1008
#define IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE_STATIC   1009
#define IDC_TMPARAMETER_PROPERTIES_FONTS_SIZE   1010
#define IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR_STATIC   1011
#define IDC_TMPARAMETER_PROPERTIES_FONTS_COLOR   1012
#define IDC_TMPARAMETER_PROPERTIES_FONTS_SAMPLE   1013
#define IDC_TMPARAMETER_PROPERTIES_FONTS_SAMPLETEXT   1014
#define IDC_TMPARAMETER_PROPERTIES_COLORS_STATIC   1015
#define IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE_STATIC 1016
#define IDC_TMPARAMETER_PROPERTIES_COLORS_TITLE   1017
#define IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS_STATIC   1018
#define IDC_TMPARAMETER_PROPERTIES_COLORS_KEYS   1019
#define IDC_TMPARAMETER_PROPERTIES_HELP   1020

class CTMParameterPropertiesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTMParameterPropertiesDialog)

	// Construction
public:
	CTMParameterPropertiesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	LOGFONT  m_lfTable[2][2];
	COLORREF  m_nTableColors[2][2];
	COLORREF  m_nTableFontColors[2][2];
	CString  m_szFontSampleText;

	// Dialog Data
	//{{AFX_DATA(CTMParameterPropertiesDialog)
	enum { IDD = IDD_TMPARAMETER_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID ShowFontDetails();
	VOID ShowFontSample();

	class CTMParameterWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTMParameterPropertiesDialog)
public:
	virtual INT_PTR DoModal(class CTMParameterWnd *pParentWnd);
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
	//{{AFX_MSG(CTMParameterPropertiesDialog)
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
// CTMParameterStatusBar window

class CTMParameterStatusBar : public CMFCStatusBar
{
	DECLARE_DYNCREATE(CTMParameterStatusBar)

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
	//{{AFX_VIRTUAL(CTMParameterStatusBar)
private:
	virtual VOID Initialize();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTMParameterStatusBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMParameterView view

class CTMParameterView : public CDisplayTableView
{
	DECLARE_DYNCREATE(CTMParameterView)

	// Construction
public:
	CTMParameterView();

	// Attributes
public:

	// Operations
public:
	VOID SetTitle(LPCTSTR pszName, LPCTSTR pszTitle);
	BOOL GetTitle(CString &szName, CString &szTitle) CONST;
	BOOL SetProperties(CONST LOGFONT *plfTitle, CONST LOGFONT *plfItems, COLORREF nTitleColor, COLORREF nItemsColor, COLORREF nTitleBackground, COLORREF nKeysBackground);
	BOOL GetProperties(LOGFONT *plfTitle, LOGFONT *plfItems, COLORREF &nTitleColor, COLORREF &nItemsColor, COLORREF &nTitleBackground, COLORREF &nKeysBackground) CONST;

	class CTMParameterWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTMParameterView)
public:
	virtual VOID UpdateTableForms(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nIndex, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTableForms(CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete = FALSE);
private:
	virtual BOOL CheckPrivilege() CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTMParameterView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTMParameterWnd

// Specify the telemetry parameter form statusbar pane identifiers
#define ID_TMPARAMETER_STATUSBAR_DETAILSPANE   ID_SEPARATOR
#define ID_TMPARAMETER_STATUSBAR_FLAGPANE   ID_STATUSBAR_PANE1
#define ID_TMPARAMETER_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2

class CTMParameterWnd : public CDisplayWnd
{
	DECLARE_DYNCREATE(CTMParameterWnd)

	// Construction
public:
	CTMParameterWnd();
	CTMParameterWnd(LPCTSTR pszName);

	// Attributes
private:
	CTMParameterView  m_wndView;
	CTMParameterStatusBar  m_wndStatusBar;
private:
	CTMParameterPropertiesDialog  m_dlgProperties;

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

private:
	VOID UpdateTitle();
	VOID UpdateMenus();
	VOID UpdateStatusBar();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTMParameterWnd)
public:
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
	virtual VOID DoCheck();
	virtual BOOL CanCheck() CONST;
	virtual VOID DoDelete();
	virtual BOOL CanDelete() CONST;
	virtual VOID DoUndo();
	virtual BOOL CanUndo() CONST;
	virtual VOID DoRedo();
	virtual BOOL CanRedo() CONST;
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
	virtual VOID UpdateTables(CONST CDatabaseTMParameters &pDatabaseTMParameters);
	virtual VOID UpdateTables(CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete = FALSE);
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
	virtual VOID UpdateTables(CONST CGRDLayout *pLayout, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(CONST CPODLayout *pLayout, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(ULONGLONG nComponent, LPCTSTR pszName, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(ULONGLONG nComponent, INT nID, BOOL bDelete = FALSE);
	virtual VOID UpdateTables(ULONGLONG nComponent);
	virtual VOID UpdateTables();
protected:
	virtual CString GetPrintDocTitle(LPCTSTR pszTag, UINT nFlags) CONST;
	virtual CString GetPrintDocInfoTitle() CONST;
public:
	virtual VOID AdjustToPrivileges();
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CTMParameterWnd)
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


#endif // __TMPARAMETER_H__
