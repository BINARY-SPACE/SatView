// SCRIPT.H : Automation Script Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the automation script display related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2003/06/20 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SCRIPT_H__
#define __SCRIPT_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CScriptDocumentItem

class CScriptDocumentItem : public COleClientItem
{
	DECLARE_DYNCREATE(CScriptDocumentItem)

	// Construction
public:
	CScriptDocumentItem(class CScriptDocument *pContainerDoc = NULL);

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptDocumentItem)
	//}}AFX_VIRTUAL

	// Implementation
public:
	LPDISPATCH GetIDispatch() CONST;

	// Generated message map functions
protected:
	//{{AFX_MSG(CScriptDocumentItem)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptDocument document

class CScriptDocument : public COleDocument
{
	DECLARE_DYNCREATE(CScriptDocument)

	// Construction
public:
	CScriptDocument();
	virtual ~CScriptDocument();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptDocument)
public:
	virtual void Serialize(CArchive &ar);   // overridden for document i/o
	virtual BOOL SaveModified();
	virtual BOOL OnNewDocument();
	virtual void OnCloseDocument();
	virtual BOOL CanCloseFrame(CFrameWnd *pFrame);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CScriptDocument)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptSaveDialog dialog

#define IDC_SCRIPT_SAVE_DETAILS   1001
#define IDC_SCRIPT_SAVE_DATABASE_STATIC   1002
#define IDC_SCRIPT_SAVE_DATABASE   1003
#define IDC_SCRIPT_SAVE_TITLE_STATIC   1004
#define IDC_SCRIPT_SAVE_TITLE   1005
#define IDC_SCRIPT_SAVE_NUMBER_STATIC   1006
#define IDC_SCRIPT_SAVE_NUMBER   1007
#define IDC_SCRIPT_SAVE_COMMENT_STATIC   1008
#define IDC_SCRIPT_SAVE_COMMENT   1009
#define IDC_SCRIPT_SAVE_DIRECTORY_STATIC   1010
#define IDC_SCRIPT_SAVE_DIRECTORY   1011
#define IDC_SCRIPT_SAVE_HELP   1012

class CScriptSaveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CScriptSaveDialog)

	// Construction
public:
	CScriptSaveDialog();   // standard constructor

	// Attributes
private:
	CAutomationScripts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CScriptSaveDialog)
	enum { IDD = IDD_SCRIPT_SAVE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CScriptWnd *GetParentDisplay() CONST;

private:
	VOID EnumScripts();

	BOOL FindScript(LPCTSTR pszNumber) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptSaveDialog)
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
	//{{AFX_MSG(CScriptSaveDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeTitle();
	afx_msg void OnEditchangeNumber();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptOpenDialog dialog

#define IDC_SCRIPT_OPEN_DETAILS   1001
#define IDC_SCRIPT_OPEN_DATABASE_STATIC   1002
#define IDC_SCRIPT_OPEN_DATABASE   1003
#define IDC_SCRIPT_OPEN_DIRECTORY_STATIC   1004
#define IDC_SCRIPT_OPEN_DIRECTORY   1005
#define IDC_SCRIPT_OPEN_HELP   1006

class CScriptOpenDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CScriptOpenDialog)

	// Construction
public:
	CScriptOpenDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CAutomationScripts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CScriptOpenDialog)
	enum { IDD = IDD_SCRIPT_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumScripts();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptOpenDialog)
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
	//{{AFX_MSG(CScriptOpenDialog)
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
// CScriptImportDialog dialog

#define IDC_SCRIPT_IMPORT_DETAILS   1001
#define IDC_SCRIPT_IMPORT_FILENAME_STATIC   1002
#define IDC_SCRIPT_IMPORT_FILENAME   1003
#define IDC_SCRIPT_IMPORT_BROWSE   1004
#define IDC_SCRIPT_IMPORT_DIRECTORY   1005
#define IDC_SCRIPT_IMPORT_TYPE   1006
#define IDC_SCRIPT_IMPORT_TYPE_DEFAULT   1007
#define IDC_SCRIPT_IMPORT_TYPE_CUSTOM   1008
#define IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER   1009
#define IDC_SCRIPT_IMPORT_TYPE_CUSTOM_NUMBER_STATIC   1010
#define IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC   1011
#define IDC_SCRIPT_IMPORT_TYPE_CUSTOM_DESCRIPTION    1012
#define IDC_SCRIPT_IMPORT_HELP   1013

class CScriptImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CScriptImportDialog)

	// Construction
public:
	CScriptImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CAutomationScripts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CScriptImportDialog)
	enum { IDD = IDD_SCRIPT_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumScripts();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptImportDialog)
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
	//{{AFX_MSG(CScriptImportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeNumber();
	afx_msg void OnEditchangeDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptExportDialog dialog

#define IDC_SCRIPT_EXPORT_DETAILS   1001
#define IDC_SCRIPT_EXPORT_DIRECTORY_STATIC   1002
#define IDC_SCRIPT_EXPORT_DIRECTORY   1003
#define IDC_SCRIPT_EXPORT_FILENAME_STATIC   1004
#define IDC_SCRIPT_EXPORT_FILENAME   1005
#define IDC_SCRIPT_EXPORT_BROWSE   1006
#define IDC_SCRIPT_EXPORT_TYPE   1007
#define IDC_SCRIPT_EXPORT_TYPE_DEFAULT   1008
#define IDC_SCRIPT_EXPORT_TYPE_CUSTOM   1009
#define IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER   1010
#define IDC_SCRIPT_EXPORT_TYPE_CUSTOM_NUMBER_STATIC   1011
#define IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC   1012
#define IDC_SCRIPT_EXPORT_TYPE_CUSTOM_DESCRIPTION   1013
#define IDC_SCRIPT_EXPORT_TYPE_CUSTOM_SOURCECODE   1014
#define IDC_SCRIPT_EXPORT_HELP   1015

class CScriptExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CScriptExportDialog)

	// Construction
public:
	CScriptExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CAutomationScripts  m_pLayouts;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CScriptExportDialog)
	enum { IDD = IDD_SCRIPT_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumScripts();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptExportDialog)
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
	//{{AFX_MSG(CScriptExportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	afx_msg void OnSourceCode();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeNumber();
	afx_msg void OnEditchangeDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesDialog dialog

#define IDC_SCRIPT_PROPERTIES_DETAILS   1001
#define IDC_SCRIPT_PROPERTIES_NAME_STATIC  1002
#define IDC_SCRIPT_PROPERTIES_NAME   1003
#define IDC_SCRIPT_PROPERTIES_TYPE_STATIC   1004
#define IDC_SCRIPT_PROPERTIES_TYPE_EXCEL   1005
#define IDC_SCRIPT_PROPERTIES_TYPE_WORD   1006
#define IDC_SCRIPT_PROPERTIES_TYPE_ACCESS   1007
#define IDC_SCRIPT_PROPERTIES_TYPE_OUTLOOK   1008
#define IDC_SCRIPT_PROPERTIES_TYPE_POWERPOINT   1009
#define IDC_SCRIPT_PROPERTIES_TYPE_OTHER   1010
#define IDC_SCRIPT_PROPERTIES_INPUTFILENAME_STATIC   1011
#define IDC_SCRIPT_PROPERTIES_INPUTFILENAME   1012
#define IDC_SCRIPT_PROPERTIES_INPUTFILENAME_BROWSE   1013
#define IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME_STATIC   1014
#define IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME   1015
#define IDC_SCRIPT_PROPERTIES_OUTPUTFILENAME_BROWSE   1016
#define IDC_SCRIPT_PROPERTIES_PARAMETERS   1017
#define IDC_SCRIPT_PROPERTIES_HELP   1018

class CScriptPropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CScriptPropertiesDialog)

	// Construction
public:
	CScriptPropertiesDialog();   // standard constructor

	// Attributes
private:
	CAutomationScript  m_cScript[2];
	CTMParameters  *m_pTMParameters;
	BOOL  m_bTMParameters;

	// Dialog Data
	//{{AFX_DATA(CScriptPropertiesDialog)
	enum { IDD = IDD_SCRIPT_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTMParameters *pTMParameters);

	class CScriptWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptPropertiesDialog)
public:
	virtual BOOL Initialize();
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScriptPropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTypeExcel();
	afx_msg void OnTypeWord();
	afx_msg void OnTypeAccess();
	afx_msg void OnTypeOutlook();
	afx_msg void OnTypePowerPoint();
	afx_msg void OnTypeOther();
	afx_msg void OnBrowseInputFileName();
	afx_msg void OnBrowseOutputFileName();
	afx_msg void OnParameters();
	afx_msg void OnEditchangeInputFileName();
	afx_msg void OnEditchangeOutputFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParametersDialog dialog

#define IDC_SCRIPT_PROPERTIES_PARAMETERS_DETAILS   1001
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG_STATIC   1002
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_TAG   1003
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_ADD   1004
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVE   1005
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_REMOVEALL   1006
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST_STATIC   1007
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_LIST   1008
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_REMARK   1009
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE_STATIC   1010
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_VALUE   1011
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_STATIC   1012
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE   1013
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_PAST   1014
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE_STATIC   1015
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_TABLE   1016
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_SAMPLE_RAW   1017
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_STATIC   1018
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_NOLIMIT   1019
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_SOFTLIMIT   1020
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_HARDLIMIT   1021
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_DELTALIMIT   1022
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_CONSISTENCYLIMIT   1023
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_VALID   1024
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_STATUS_INVALID   1025
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_STATIC   1026
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_GOOD   1027
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_QUALITY_BAD   1028
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_SET   1029
#define IDC_SCRIPT_PROPERTIES_PARAMETERS_HELP   1030

// Specify the automation script properties parameters dialog related identifiers
#define SCRIPTPROPERTIESPARAMETERS_MINIMUMSAMPLE   0
#define SCRIPTPROPERTIESPARAMETERS_MAXIMUMSAMPLE   100
#define SCRIPTPROPERTIESPARAMETERS_DEFAULTSAMPLE   0

class CScriptPropertiesParametersDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CScriptPropertiesParametersDialog)

	// Construction
public:
	CScriptPropertiesParametersDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTMParameters  m_pTMParameters[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CScriptPropertiesParametersDialog)
	enum { IDD = IDD_SCRIPT_PROPERTIES_PARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumParameters();
	BOOL EnumCalibrationTables();
	BOOL EnumCalibrationTables(CONST CDatabaseTMParameter *pDatabaseTMParameter);
	BOOL EnumCalibrationTableValues();

	VOID ShowProperties(INT nIndex = -1);
	VOID ShowParameterDetails();

	BOOL UpdateParameter(CTMParameter *pTMParameter) CONST;
	BOOL UpdateParameter(CTMParameter *pTMParameter, LPCTSTR pszValue) CONST;
	BOOL UpdateParameter(CTMParameter *pTMParameter, LPCTSTR pszValue, INT nSample, UINT nStatus, LPCTSTR pszTable) CONST;
	BOOL UpdateParameter(CTMParameter *pTMParameter, ULONGLONG nRawValue, INT nSample, UINT nStatus, LPCTSTR pszTable) CONST;

	BOOL CheckParameter() CONST;
	BOOL CheckParameter(CONST CTMParameter *pTMParameter) CONST;
	BOOL CheckParameterValue(CONST CDatabaseTMParameter *pDatabaseTMParameter, LPCTSTR pszValue) CONST;
	BOOL CheckParameterValue(CONST CTMParameter *pTMParameter, LPCTSTR pszValue) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptPropertiesParametersDialog)
public:
	virtual INT DoModal(CTMParameters *pTMParameters);
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScriptPropertiesParametersDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnRawValue();
	afx_msg void OnPastSample();
	afx_msg void OnNoLimit();
	afx_msg void OnSoftLimit();
	afx_msg void OnHardLimit();
	afx_msg void OnDeltaLimit();
	afx_msg void OnConsistencyLimit();
	afx_msg void OnValidStatus();
	afx_msg void OnInvalidStatus();
	afx_msg void OnGoodQuality();
	afx_msg void OnBadQuality();
	afx_msg void OnSetParameter();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeValue();
	afx_msg void OnSelchangeTable();
	afx_msg void OnEditchangeValue();
	afx_msg void OnSpinchangeSample();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsCalibrationPage dialog

#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_NAME   1002
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_ID   1004
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_TYPE   1006
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE_POINTS   1008

class CScriptPropertiesParameterDetailsCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CScriptPropertiesParameterDetailsCalibrationPage)

	// Construction
public:
	CScriptPropertiesParameterDetailsCalibrationPage();

	// Attributes
private:
	INT  m_nCalTableID;
	ULONGLONG  m_nCalTableType;
	CUIntArray  m_nCalTableRefs;
	CUIntArray  m_nCalValidityRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CScriptPropertiesParameterDetailsCalibrationPage)
	enum { IDD = IDD_SCRIPT_PROPERTIES_PARAMETERDETAILS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter);
	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST;

	class CScriptPropertiesParameterDetailsFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CScriptPropertiesParameterDetailsCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CScriptPropertiesParameterDetailsCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsFolderTabCtrl window

class CScriptPropertiesParameterDetailsFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CScriptPropertiesParameterDetailsFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CScriptPropertiesParameterDetailsFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptPropertiesParameterDetailsFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CScriptPropertiesParameterDetailsFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsFolder

class CScriptPropertiesParameterDetailsFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CScriptPropertiesParameterDetailsFolder)

	// Construction
public:
	CScriptPropertiesParameterDetailsFolder();

	// Attributes
private:
	CScriptPropertiesParameterDetailsFolderTabCtrl  m_wndTabCtrl;
	CScriptPropertiesParameterDetailsCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter = NULL);

	BOOL GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST;

	class CScriptPropertiesParameterDetailsDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptPropertiesParameterDetailsFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CScriptPropertiesParameterDetailsFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptPropertiesParameterDetailsDialog dialog

#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_DETAILS   1001
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM_STATIC   1002
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_ITEM   1003
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_FOLDER   1004
#define IDC_SCRIPT_PROPERTIES_PARAMETERDETAILS_HELP   1005

class CScriptPropertiesParameterDetailsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CScriptPropertiesParameterDetailsDialog)

	// Construction
public:
	CScriptPropertiesParameterDetailsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szTable;
	CTMParameter  m_cTMParameter;
private:
	CScriptPropertiesParameterDetailsFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CScriptPropertiesParameterDetailsDialog)
	enum { IDD = IDD_SCRIPT_PROPERTIES_PARAMETERDETAILS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	VOID SetSelectedCalibrationPoint(LPCTSTR pszTable, LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST;

	class CScriptPropertiesParametersDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptPropertiesParameterDetailsDialog)
public:
	virtual INT DoModal(CONST CTMParameter *pTMParameter, CString &szTable, CString &szValue);
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScriptPropertiesParameterDetailsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeParameter();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptFindDialog dialog

#define IDC_SCRIPT_FIND_TEXT_STATIC   1001
#define IDC_SCRIPT_FIND_TEXT   1002
#define IDC_SCRIPT_FIND_DIRECTION   1003
#define IDC_SCRIPT_FIND_DIRECTION_UP   1004
#define IDC_SCRIPT_FIND_DIRECTION_DOWN   1005
#define IDC_SCRIPT_FIND_ALL   1006
#define IDC_SCRIPT_FIND_CASE   1007
#define IDC_SCRIPT_FIND_WORD   1008
#define IDC_SCRIPT_FIND_NEXT   1009
#define IDC_SCRIPT_FIND_HELP   1010

class CScriptFindDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CScriptFindDialog)

	// Construction
public:
	CScriptFindDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szSearchItems;

	// Dialog Data
	//{{AFX_DATA(CScriptFindDialog)
	enum { IDD = IDD_SCRIPT_FIND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CScriptWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScriptFindDialog)
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
// CScriptReplaceDialog dialog

#define IDC_SCRIPT_REPLACE_FINDTEXT_STATIC   1001
#define IDC_SCRIPT_REPLACE_FINDTEXT   1002
#define IDC_SCRIPT_REPLACE_TEXT_STATIC   1003
#define IDC_SCRIPT_REPLACE_TEXT   1004
#define IDC_SCRIPT_REPLACE_DIRECTION   1005
#define IDC_SCRIPT_REPLACE_DIRECTION_UP   1006
#define IDC_SCRIPT_REPLACE_DIRECTION_DOWN   1007
#define IDC_SCRIPT_REPLACE_ALL   1008
#define IDC_SCRIPT_REPLACE_CASE   1009
#define IDC_SCRIPT_REPLACE_WORD   1010
#define IDC_SCRIPT_REPLACE_FINDNEXT   1011
#define IDC_SCRIPT_REPLACE_NEXT   1012
#define IDC_SCRIPT_REPLACE_ALLNEXT   1013
#define IDC_SCRIPT_REPLACE_HELP   1014

class CScriptReplaceDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CScriptReplaceDialog)

	// Construction
public:
	CScriptReplaceDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szItems[2];

	// Dialog Data
	//{{AFX_DATA(CScriptReplaceDialog)
	enum { IDD = IDD_SCRIPT_REPLACE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CScriptWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptReplaceDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScriptReplaceDialog)
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
// CScriptGoToDialog dialog

#define IDC_SCRIPT_GOTO_LINE_STATIC   1001
#define IDC_SCRIPT_GOTO_LINE   1002
#define IDC_SCRIPT_GOTO_LINENUMBER   1003
#define IDC_SCRIPT_GOTO_JUMPDOWN   1004
#define IDC_SCRIPT_GOTO_JUMPDOWNLINE   1005
#define IDC_SCRIPT_GOTO_JUMPDOWN_STATIC   1006
#define IDC_SCRIPT_GOTO_JUMPUP   1007
#define IDC_SCRIPT_GOTO_JUMPUPLINE   1008
#define IDC_SCRIPT_GOTO_JUMPUP_STATIC   1009
#define IDC_SCRIPT_GOTO_JUMP   1010
#define IDC_SCRIPT_GOTO_HELP   1011

class CScriptGoToDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CScriptGoToDialog)

	// Construction
public:
	CScriptGoToDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CScriptGoToDialog)
	enum { IDD = IDD_SCRIPT_GOTO_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CScriptWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptGoToDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScriptGoToDialog)
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
// CScriptStatusBar window

class CScriptStatusBar : public CMFCStatusBar
{
	DECLARE_DYNCREATE(CScriptStatusBar)

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
	//{{AFX_VIRTUAL(CScriptStatusBar)
private:
	virtual VOID Initialize();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CScriptStatusBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptCodeView view

class CScriptCodeView : public CRichEditView
{
	DECLARE_DYNCREATE(CScriptCodeView)

	// Construction
public:
	CScriptCodeView();

	// Attributes
private:
	CScriptFindDialog  m_dlgFind;
	CScriptGoToDialog  m_dlgGoTo;
	CScriptReplaceDialog  m_dlgReplace;
private:
	CString  m_szCode;
private:
	CFont  m_cCodeFont;
	BOOL  m_bModified;

	// Operations
public:
	BOOL SetCode(CONST CAutomationScript *pScript);
	BOOL SetCode(CONST CByteArray &nCode);
	BOOL GetCode(CAutomationScript *pScript) CONST;
	BOOL GetCode(CByteArray &nCode) CONST;
	INT GetCodeSize() CONST;

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoFindCode();
	BOOL CanFindCode() CONST;
	VOID DoFindNextCode();
	VOID DoFindNextCode(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindNextCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindNextCode() CONST;
	VOID DoFindPreviousCode();
	VOID DoFindPreviousCode(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindPreviousCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindPreviousCode() CONST;
	VOID DoReplaceCode();
	BOOL CanReplaceCode() CONST;
	VOID DoGoToCode();
	BOOL CanGoToCode() CONST;

	VOID DoCutCode();
	BOOL CanCutCode() CONST;
	VOID DoCopyCode();
	BOOL CanCopyCode() CONST;
	VOID DoPasteCode();
	BOOL CanPasteCode() CONST;
	VOID DoDeleteCode();
	BOOL CanDeleteCode() CONST;

	VOID DoSelectAllCode();
	VOID UnSelectAllCode();
	BOOL CanSelectAllCode() CONST;

	BOOL SearchCode(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceAllCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL GoToCode(UINT nLine, BOOL bDown = FALSE, BOOL bUp = FALSE);
	BOOL GoToCode(LPCTSTR pszLine);

	INT GetLinePosition() CONST;
	INT GetColumnPosition() CONST;

	VOID ShowDialogs(BOOL bShow);
	BOOL HasDialogs() CONST;

	VOID SetModified(BOOL bFlag = TRUE);
	BOOL IsModified() CONST;

	class CScriptSplitterWnd *GetParent() CONST;

private:
	static DWORD CALLBACK SetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	static DWORD CALLBACK GetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptCodeView)
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CScriptCodeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditchangeCode();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptImageView view

class CScriptImageView : public CScrollView
{
	DECLARE_DYNCREATE(CScriptImageView)

	// Construction
public:
	CScriptImageView();

	// Attributes
private:
	CString  m_szScriptFileName;
	CRect  m_rScriptOutput[2];
	UINT  m_nScriptType;
	BOOL  m_bModified;

	// Operations
public:
	BOOL SetImage(CONST CAutomationScript *pScript);
	BOOL GetImage(CAutomationScript *pScript) CONST;

	VOID UpdateImage();
	VOID UpdateImage(CONST CAutomationScript *pScript);

	BOOL HasImage() CONST;

	VOID PrintInsideRect(CDC *pDC, CONST RECT &rect);

	VOID SetModified(BOOL bFlag = TRUE);
	BOOL IsModified() CONST;

	CScriptDocument *GetDocument() CONST;

	class CScriptSplitterWnd *GetParent() CONST;

private:
	BOOL CheckImageFile(CONST CAutomationScript *pScript);

	CSize CalcImageSize(CScriptDocumentItem *pItem);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptImageView)
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScriptImageView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptSplitterWnd window

class CScriptSplitterWnd : public CSplitterWndEx
{
	DECLARE_DYNCREATE(CScriptSplitterWnd)

	// Construction
public:
	CScriptSplitterWnd();

	// Attributes
private:
	CScriptDocument  *m_pDocument;

	// Operations
public:
	BOOL Create(class CScriptWnd *pParentWnd);

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoFind();
	BOOL CanFind() CONST;
	VOID DoFindNext(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindNext(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindNext() CONST;
	VOID DoFindPrevious(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindPrevious(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindPrevious() CONST;
	VOID DoReplace();
	BOOL CanReplace() CONST;
	VOID DoGoTo();
	BOOL CanGoTo() CONST;

	VOID DoCutSel();
	BOOL CanCutSel() CONST;
	VOID DoCopySel();
	BOOL CanCopySel() CONST;
	VOID DoPasteSel();
	BOOL CanPasteSel() CONST;
	VOID DoDeleteSel();
	BOOL CanDeleteSel() CONST;

	VOID DoSelectAll();
	VOID UnSelectAll();
	BOOL CanSelectAll() CONST;

	CView *GetActivePane() CONST;

	CScriptCodeView *GetCodeView() CONST;
	CScriptImageView *GetImageView() CONST;

	class CScriptWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptSplitterWnd)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CScriptSplitterWnd)
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptCompileThread thread

class CScriptCompileThread : public CThread
{
	DECLARE_DYNAMIC(CScriptCompileThread)

	// Construction
public:
	CScriptCompileThread();

	// Attributes
private:
	LONG  m_bStop;
	LONG  m_bAbort;
	BOOL  m_bBatch;
	BOOL  m_bSyntax;
	UINT  m_nErrors;
	UINT  m_nWarnings;
	CAutomationScript  m_cScript;
	CEvent  m_bCompilation[2];

	// Operations
public:
	BOOL StartCompiling(CBinaryDatabase *pDatabase, CONST CAutomationScript *pScript);
	BOOL StartCompiling(CBinaryDatabase *pDatabase, CONST CAutomationScript *pScript, BOOL bSyntax, BOOL bBatch, INT &nErrors, INT &nWarnings, BOOL &bAbort);
	BOOL IsCompiling() CONST;
	BOOL StopCompiling();

	VOID SetCompileTarget(CONST CBinaryDatabase *pDatabase, CONST CAutomationScript *pScript, BOOL bSyntax, BOOL bBatch);
	VOID GetCompileTarget(CAutomationScript *pScript) CONST;
	BOOL IsSyntaxCompileTarget() CONST;
	BOOL IsBatchCompileTarget() CONST;

private:
	VOID CompileTarget();

	VOID ShowStartCompileMessages();
	VOID ShowStopCompileMessages();
	VOID ShowCompileMessage(LPCTSTR pszMessage, BOOL bTimestamp = TRUE, BOOL bAudition = FALSE);

	VOID ShowError(LPCTSTR pszError);
	VOID ShowWarning(LPCTSTR pszWarning);

	VOID SetErrorCount(UINT nCount = 0);
	UINT GetErrorCount() CONST;
	VOID SetWarningCount(UINT nCount = 0);
	UINT GetWarningCount() CONST;

	VOID SetAbortStatus(BOOL bAbort = FALSE);
	BOOL GetAbortStatus() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptCompileThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScriptCompileThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CScriptWnd frame with splitter

// Specify the script display statusbar pane identifiers
#define ID_SCRIPT_STATUSBAR_SIZEPANE   ID_SEPARATOR
#define ID_SCRIPT_STATUSBAR_LINEPANE   ID_STATUSBAR_PANE1
#define ID_SCRIPT_STATUSBAR_COLUMNPANE   ID_STATUSBAR_PANE2

class CScriptWnd : public CDisplayWnd
{
	DECLARE_DYNCREATE(CScriptWnd)

	// Construction
public:
	CScriptWnd();
	CScriptWnd(LPCTSTR pszName);

	// Attributes
private:
	CString  m_szName;
	CString  m_szTitle;
	CAutomationScript  m_cScript;
private:
	CScriptSplitterWnd  m_wndSplitter;
	CScriptStatusBar  m_wndStatusBar;
private:
	CScriptPropertiesDialog  m_dlgProperties;
private:
	CTMEnvironment  m_cTMEnvironment;
public:
	static CScriptCompileThread  m_cCompileThread;

	// Operations
public:
	BOOL Create(CMDIFrameWnd *pParentWnd, UINT nShow = -1);

	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetScript(CONST CAutomationScript *pScript);
	BOOL GetScript(CAutomationScript *pScript) CONST;

	BOOL SearchScriptCode(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceScriptCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceAllScriptCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL GoToScriptCode(UINT nLine, BOOL bDown = FALSE, BOOL bUp = FALSE);
	BOOL GoToScriptCode(LPCTSTR pszLine);

	VOID UpdateBars();

	CScriptCodeView *GetCodeView() CONST;
	CScriptImageView *GetImageView() CONST;

private:
	VOID UpdateTitle();
	VOID UpdateMenus();

	VOID UpdateImage();
	VOID UpdateImage(CONST CAutomationScript *pScript);

	INT SaveToDatabase();
	BOOL LoadFromDatabase();
	INT DeleteFromDatabase();

	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, WORD wFromPage = -1, WORD wToPage = -1);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CPtrArray &pFonts, LPRECT prClip, UINT nFlags, INT nPage = -1, BOOL bCalc = FALSE);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nFlags, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocInfoTitle() CONST;

public:
	static BOOL StartCompilingScript(CBinaryDatabase *pDatabase, CONST CAutomationScript *pScript);
	static BOOL StartCompilingScript(CBinaryDatabase *pDatabase, CONST CAutomationScript *pScript, BOOL bSyntax, BOOL bBatch, INT &nErrors, INT &nWarnings, BOOL &bAbort);
	static BOOL IsCompilingScript();
	static BOOL IsAbortingScriptCompilation();
	static VOID StopCompilingScript();

	static INT Delete(LPCTSTR pszName);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptWnd)
public:
	virtual BOOL IsNew() CONST;
	virtual BOOL IsModified() CONST;
	virtual BOOL Save(INT nPosition) CONST;
	virtual INT Load(INT nPosition);
	virtual BOOL UpdateProperties();
	virtual BOOL IsUpdatingProperties() CONST;
	virtual BOOL HasProperties() CONST;
	virtual BOOL Print(PRINTDLG *pPrintInfo, UINT nFlags);
public:
	virtual VOID DoSave();
	virtual BOOL CanSave() CONST;
	virtual VOID DoSaveAs();
	virtual BOOL CanSaveAs() CONST;
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
	virtual BOOL DoCompile();
	virtual BOOL IsCompiling() CONST;
	virtual BOOL CanCompile() CONST;
	virtual BOOL StopCompiling();
	virtual VOID DoTest();
	virtual BOOL IsTesting() CONST;
	virtual BOOL CanTest() CONST;
	virtual VOID DoClose();
public:
	virtual VOID AdjustToPrivileges();
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CScriptWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateStatusBarSizePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarLinePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarColumnPane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __SCRIPT_H__
