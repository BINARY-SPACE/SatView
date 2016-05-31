// TCPROCEDURE.H : Telecommand Procedure Display Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the telecommand procedure display related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2006/06/09 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __TCPROCEDURE_H__
#define __TCPROCEDURE_H__

#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CTCProcedureItem

class CTCProcedureItem : public CObject
{
	DECLARE_DYNCREATE(CTCProcedureItem)

	// Construction
public:
	CTCProcedureItem();
	CTCProcedureItem(LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszSequence, CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bProcedure, INT nEntry, INT nEntries, CONST CTimeTag &tScheduleTime, CONST CTimeTag &tReleaseTime, DWORD dwReleaseOffset, CONST CTimeTag &tExecutionTime, DWORD dwExecutionOffset, BOOL bEarlierExecution, INT nBlockID, BOOL bGrouped, BOOL bCritical, ULONGLONG nAckFlags, HANDLE hSuccess, HANDLE hFailure);

	// Attributes
private:
	CString  m_szName[3];
	CTimeTag  m_tTime[4];
	ULONGLONG  m_nAckFlags;
	HANDLE  m_hEvent[2];
	DWORD  m_dwOffset[2];
	BOOL  m_bExeEarlier;
	UINT  m_nEntries;
	UINT  m_nEntryID;
	UINT  m_nBlockID;
	UINT  m_nStages;
	BYTE  m_bFlag[4];
private:
	CDatabaseTCFunction  m_cDatabaseTCFunction;
	CDatabaseTCPacket  m_cDatabaseTCPacket;

	// Operations
public:
	VOID SetThread(LPCTSTR pszThread);
	CString GetThread() CONST;
	VOID SetStep(LPCTSTR pszStep);
	CString GetStep() CONST;
	VOID SetSequence(LPCTSTR pszSequence);
	CString GetSequence() CONST;
	BOOL SetFunction(CONST CDatabaseTCFunction *pDatabaseTCFunction);
	BOOL GetFunction(CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	CString GetFunction() CONST;
	BOOL SetPacket(CONST CDatabaseTCPacket *pDatabaseTCPacket);
	BOOL GetPacket(CDatabaseTCPacket *pDatabaseTCPacket) CONST;
	CString GetPacket() CONST;
	VOID SetEntryID(INT nID);
	INT GetEntryID() CONST;
	VOID SetEntryCount(INT nCount);
	INT GetEntryCount() CONST;
	VOID SetScheduleTime(CONST CTimeTag &tTime);
	CTimeTag GetScheduleTime() CONST;
	VOID SetReleaseTime(CONST CTimeTag &tTime);
	CTimeTag GetReleaseTime() CONST;
	VOID SetReleaseTimeOffset(DWORD dwOffset);
	DWORD GetReleaseTimeOffset() CONST;
	VOID SetExecutionTime(CONST CTimeTag &tTime);
	CTimeTag GetExecutionTime() CONST;
	VOID SetExecutionTimeOffset(DWORD dwOffset, BOOL bEarlier = FALSE);
	DWORD GetExecutionTimeOffset(BOOL &bEarlier) CONST;
	DWORD GetExecutionTimeOffset() CONST;
	BOOL IsEarlierExecutionTimeOffset() CONST;
	VOID SetBlockID(INT nID);
	INT GetBlockID() CONST;
	VOID SetProcedureFlag(BOOL bFlag);
	BOOL GetProcedureFlag() CONST;
	VOID SetGroupFlag(BOOL bFlag);
	BOOL GetGroupFlag() CONST;
	VOID SetCriticalFlag(BOOL bFlag);
	BOOL GetCriticalFlag() CONST;
	VOID SetAckFlags(ULONGLONG nFlags);
	ULONGLONG GetAckFlags() CONST;
	VOID SetVerificationTime(CONST CTimeTag &tTime);
	CTimeTag GetVerificationTime() CONST;
	VOID SetVerificationFlag(BOOL bFlag);
	BOOL GetVerificationFlag() CONST;
	VOID SetVerificationStages(UINT nStages);
	UINT GetVerificationStages() CONST;
	VOID SetHandles(HANDLE hSuccess, HANDLE hFailure);
	BOOL GetHandles(HANDLE &hSuccess, HANDLE &hFailure) CONST;

	VOID Copy(CONST CTCProcedureItem *pItem);
	BOOL Compare(CONST CTCProcedureItem *pItem) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureItems

class CTCProcedureItems : public CPtrArray
{
	// Construction
public:
	CTCProcedureItems();
	~CTCProcedureItems();

	// Attributes
public:

	// Operations
public:
	INT Add(CTCProcedureItem *pItem);

	INT Find(LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszSequence, LPCTSTR pszFunction, INT nEntry, CONST CTimeTag &tScheduleTime) CONST;
	INT Find(LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszSequence, INT nEntry, CONST CTimeTag &tScheduleTime) CONST;
	INT Find(LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszSequence, CONST CTimeTag &tScheduleTime) CONST;

	INT Collect(INT nIndex, CUIntArray &nItemIDs) CONST;

	CTCProcedureItem *GetAt(INT nIndex) CONST;
	CTCProcedureItem *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CTCProcedureItems *pItems);
	BOOL Compare(CONST CTCProcedureItems *pItems) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentUndoItem

#define TCPROCEDUREDOCUMENTUNDOITEM_ACTION_NONE   0
#define TCPROCEDUREDOCUMENTUNDOITEM_ACTION_INSERT   1
#define TCPROCEDUREDOCUMENTUNDOITEM_ACTION_ACTIVATE   2
#define TCPROCEDUREDOCUMENTUNDOITEM_ACTION_PROPERTIES   3
#define TCPROCEDUREDOCUMENTUNDOITEM_ACTION_RELOCATE   4
#define TCPROCEDUREDOCUMENTUNDOITEM_ACTION_EXPAND   5
#define TCPROCEDUREDOCUMENTUNDOITEM_ACTION_COLLAPSE   6
#define TCPROCEDUREDOCUMENTUNDOITEM_ACTION_DELETE   7

class CTCProcedureDocumentUndoItem : public CObject
{
	DECLARE_DYNCREATE(CTCProcedureDocumentUndoItem)

	// Construction
public:
	CTCProcedureDocumentUndoItem();
	~CTCProcedureDocumentUndoItem();

	// Attributes
private:
	UINT  m_nAction;
	CTCProcedureDocumentItem  m_cStep[2];
private:
	BOOL  m_bCollected;

	// Operations
public:
	BOOL SetInfo(UINT nAction, CONST CTCProcedureDocumentItem *pStep = NULL, CONST CTCProcedureDocumentItem *pOldStep = NULL);
	UINT GetInfo(CTCProcedureDocumentItem *pStep = NULL, CTCProcedureDocumentItem *pOldStep = NULL) CONST;

	VOID Collect(BOOL bEnable = TRUE);
	BOOL IsCollected() CONST;

	BOOL Copy(CONST CTCProcedureDocumentUndoItem *pItem);
	BOOL Compare(CONST CTCProcedureDocumentUndoItem *pItem) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureDocumentUndoList

class CTCProcedureDocumentUndoList : public CPtrArray
{
	// Construction
public:
	CTCProcedureDocumentUndoList();
	~CTCProcedureDocumentUndoList();

	// Attributes
private:
	INT  m_nIndex[2];
private:
	INT  m_bLocked;

	// Operations
public:
	BOOL Add(CONST CTCProcedureDocumentUndoItem *pItem);

	BOOL Undo(CTCProcedureDocumentUndoItem *pItem);
	BOOL Redo(CTCProcedureDocumentUndoItem *pItem);
	BOOL CanUndo(BOOL bCollected = FALSE) CONST;
	BOOL CanRedo(BOOL bCollected = FALSE) CONST;

	CTCProcedureDocumentUndoItem *GetAt(INT nIndex) CONST;
	CTCProcedureDocumentUndoItem *operator[](INT nIndex) CONST;

	VOID Reset();

	VOID Lock();
	BOOL IsLocked() CONST;
	VOID Unlock();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSaveDialog dialog

#define IDC_TCPROCEDURE_SAVE_DETAILS   1001
#define IDC_TCPROCEDURE_SAVE_DATABASE_STATIC   1002
#define IDC_TCPROCEDURE_SAVE_DATABASE   1003
#define IDC_TCPROCEDURE_SAVE_TITLE_STATIC   1004
#define IDC_TCPROCEDURE_SAVE_TITLE   1005
#define IDC_TCPROCEDURE_SAVE_NAME_STATIC   1006
#define IDC_TCPROCEDURE_SAVE_NAME   1007
#define IDC_TCPROCEDURE_SAVE_COMMENT_STATIC   1008
#define IDC_TCPROCEDURE_SAVE_COMMENT   1009
#define IDC_TCPROCEDURE_SAVE_DIRECTORY_STATIC   1010
#define IDC_TCPROCEDURE_SAVE_DIRECTORY   1011
#define IDC_TCPROCEDURE_SAVE_HELP   1012

class CTCProcedureSaveDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedureSaveDialog)

	// Construction
public:
	CTCProcedureSaveDialog();   // standard constructor

	// Attributes
private:
	CDatabaseTCProcedures  m_pDatabaseTCProcedures;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureSaveDialog)
	enum { IDD = IDD_TCPROCEDURE_SAVE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID EnumProcedures();

	BOOL FindProcedure(LPCTSTR pszName) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureSaveDialog)
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
	//{{AFX_MSG(CTCProcedureSaveDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeTitle();
	afx_msg void OnEditchangeName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureOpenDialog dialog

#define IDC_TCPROCEDURE_OPEN_DETAILS   1001
#define IDC_TCPROCEDURE_OPEN_DATABASE_STATIC   1002
#define IDC_TCPROCEDURE_OPEN_DATABASE   1003
#define IDC_TCPROCEDURE_OPEN_DIRECTORY_STATIC   1004
#define IDC_TCPROCEDURE_OPEN_DIRECTORY   1005
#define IDC_TCPROCEDURE_OPEN_HELP   1006

class CTCProcedureOpenDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedureOpenDialog)

	// Construction
public:
	CTCProcedureOpenDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseTCProcedures  m_pDatabaseTCProcedures;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureOpenDialog)
	enum { IDD = IDD_TCPROCEDURE_OPEN_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumProcedures();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureOpenDialog)
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
	//{{AFX_MSG(CTCProcedureOpenDialog)
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
// CTCProcedureImportDialog dialog

#define IDC_TCPROCEDURE_IMPORT_DETAILS   1001
#define IDC_TCPROCEDURE_IMPORT_FILENAME_STATIC   1002
#define IDC_TCPROCEDURE_IMPORT_FILENAME   1003
#define IDC_TCPROCEDURE_IMPORT_BROWSE   1004
#define IDC_TCPROCEDURE_IMPORT_DIRECTORY   1005
#define IDC_TCPROCEDURE_IMPORT_TYPE   1006
#define IDC_TCPROCEDURE_IMPORT_TYPE_DEFAULT   1007
#define IDC_TCPROCEDURE_IMPORT_TYPE_CUSTOM   1008
#define IDC_TCPROCEDURE_IMPORT_TYPE_CUSTOM_NAME   1009
#define IDC_TCPROCEDURE_IMPORT_TYPE_CUSTOM_NAME_STATIC   1010
#define IDC_TCPROCEDURE_IMPORT_TYPE_CUSTOM_DESCRIPTION_STATIC   1011
#define IDC_TCPROCEDURE_IMPORT_TYPE_CUSTOM_DESCRIPTION    1012
#define IDC_TCPROCEDURE_IMPORT_HELP   1013

class CTCProcedureImportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedureImportDialog)

	// Construction
public:
	CTCProcedureImportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseTCProcedures  m_pDatabaseTCProcedures;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureImportDialog)
	enum { IDD = IDD_TCPROCEDURE_IMPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	VOID EnumProcedures();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureImportDialog)
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
	//{{AFX_MSG(CTCProcedureImportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureExportDialog dialog

#define IDC_TCPROCEDURE_EXPORT_DETAILS   1001
#define IDC_TCPROCEDURE_EXPORT_DIRECTORY_STATIC   1002
#define IDC_TCPROCEDURE_EXPORT_DIRECTORY   1003
#define IDC_TCPROCEDURE_EXPORT_FILENAME_STATIC   1004
#define IDC_TCPROCEDURE_EXPORT_FILENAME   1005
#define IDC_TCPROCEDURE_EXPORT_BROWSE   1006
#define IDC_TCPROCEDURE_EXPORT_TYPE   1007
#define IDC_TCPROCEDURE_EXPORT_TYPE_DEFAULT   1008
#define IDC_TCPROCEDURE_EXPORT_TYPE_CUSTOM   1009
#define IDC_TCPROCEDURE_EXPORT_TYPE_CUSTOM_NAME   1010
#define IDC_TCPROCEDURE_EXPORT_TYPE_CUSTOM_NAME_STATIC   1011
#define IDC_TCPROCEDURE_EXPORT_TYPE_CUSTOM_DESCRIPTION_STATIC   1012
#define IDC_TCPROCEDURE_EXPORT_TYPE_CUSTOM_DESCRIPTION   1013
#define IDC_TCPROCEDURE_EXPORT_TYPE_CUSTOM_SOURCECODE   1014
#define IDC_TCPROCEDURE_EXPORT_HELP   1015

class CTCProcedureExportDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedureExportDialog)

	// Construction
public:
	CTCProcedureExportDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseTCProcedures  m_pDatabaseTCProcedures;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureExportDialog)
	enum { IDD = IDD_TCPROCEDURE_EXPORT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
private:
	BOOL EnumProcedures();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureExportDialog)
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
	//{{AFX_MSG(CTCProcedureExportDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBrowse();
	afx_msg void OnDefault();
	afx_msg void OnCustom();
	afx_msg void OnSourceCode();
	afx_msg void OnEditchangeFileName();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeDescription();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_NAME_STATIC   1003
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_NAME   1004
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_STYLE_STATIC   1005
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_STYLE   1006
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_SIZE_STATIC   1007
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_SIZE   1008
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_COLOR_STATIC   1009
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_COLOR   1010
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_SAMPLE   1011
#define IDC_TCPROCEDURE_PROPERTIES_FONTS_SAMPLETEXT   1012
#define IDC_TCPROCEDURE_PROPERTIES_BACKGROUND_COLOR_STATIC   1013
#define IDC_TCPROCEDURE_PROPERTIES_BACKGROUND_COLOR   1014
#define IDC_TCPROCEDURE_PROPERTIES_HELP   1015

class CTCProcedurePropertiesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesDialog)

	// Construction
public:
	CTCProcedurePropertiesDialog();   // standard constructor

	// Attributes
private:
	LOGFONT  m_lfFont[2];
	COLORREF  m_nFontColor[2];
	COLORREF  m_nBackgroundColor[2];
	CString  m_szFontSampleText;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd);

	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID ShowFontDetails();
	VOID ShowFontSample();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesDialog)
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
	//{{AFX_MSG(CTCProcedurePropertiesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnEditchangeFontName();
	afx_msg void OnSelchangeFontName();
	afx_msg void OnSelchangeFontStyle();
	afx_msg void OnSelchangeFontSize();
	afx_msg void OnSelchangeFontColor();
	afx_msg void OnSelchangeBackgroundColor();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureFindDialog dialog

#define IDC_TCPROCEDURE_FIND_TEXT_STATIC   1001
#define IDC_TCPROCEDURE_FIND_TEXT   1002
#define IDC_TCPROCEDURE_FIND_DIRECTION   1003
#define IDC_TCPROCEDURE_FIND_DIRECTION_UP   1004
#define IDC_TCPROCEDURE_FIND_DIRECTION_DOWN   1005
#define IDC_TCPROCEDURE_FIND_ALL   1006
#define IDC_TCPROCEDURE_FIND_CASE   1007
#define IDC_TCPROCEDURE_FIND_WORD   1008
#define IDC_TCPROCEDURE_FIND_NEXT   1009
#define IDC_TCPROCEDURE_FIND_HELP   1010

class CTCProcedureFindDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedureFindDialog)

	// Construction
public:
	CTCProcedureFindDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szSearchItems;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureFindDialog)
	enum { IDD = IDD_TCPROCEDURE_FIND_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCProcedurePropertiesCodeDialog *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureFindDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureFindDialog)
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
// CTCProcedureReplaceDialog dialog

#define IDC_TCPROCEDURE_REPLACE_FINDTEXT_STATIC   1001
#define IDC_TCPROCEDURE_REPLACE_FINDTEXT   1002
#define IDC_TCPROCEDURE_REPLACE_TEXT_STATIC   1003
#define IDC_TCPROCEDURE_REPLACE_TEXT   1004
#define IDC_TCPROCEDURE_REPLACE_DIRECTION   1005
#define IDC_TCPROCEDURE_REPLACE_DIRECTION_UP   1006
#define IDC_TCPROCEDURE_REPLACE_DIRECTION_DOWN   1007
#define IDC_TCPROCEDURE_REPLACE_ALL   1008
#define IDC_TCPROCEDURE_REPLACE_CASE   1009
#define IDC_TCPROCEDURE_REPLACE_WORD   1010
#define IDC_TCPROCEDURE_REPLACE_FINDNEXT   1011
#define IDC_TCPROCEDURE_REPLACE_NEXT   1012
#define IDC_TCPROCEDURE_REPLACE_ALLNEXT   1013
#define IDC_TCPROCEDURE_REPLACE_HELP   1014

class CTCProcedureReplaceDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedureReplaceDialog)

	// Construction
public:
	CTCProcedureReplaceDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szItems[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedureReplaceDialog)
	enum { IDD = IDD_TCPROCEDURE_REPLACE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCProcedurePropertiesCodeDialog *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureReplaceDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureReplaceDialog)
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
// CTCProcedureGoToDialog dialog

#define IDC_TCPROCEDURE_GOTO_LINE_STATIC   1001
#define IDC_TCPROCEDURE_GOTO_LINE   1002
#define IDC_TCPROCEDURE_GOTO_LINENUMBER   1003
#define IDC_TCPROCEDURE_GOTO_JUMPDOWN   1004
#define IDC_TCPROCEDURE_GOTO_JUMPDOWNLINE   1005
#define IDC_TCPROCEDURE_GOTO_JUMPDOWN_STATIC   1006
#define IDC_TCPROCEDURE_GOTO_JUMPUP   1007
#define IDC_TCPROCEDURE_GOTO_JUMPUPLINE   1008
#define IDC_TCPROCEDURE_GOTO_JUMPUP_STATIC   1009
#define IDC_TCPROCEDURE_GOTO_JUMP   1010
#define IDC_TCPROCEDURE_GOTO_HELP   1011

class CTCProcedureGoToDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedureGoToDialog)

	// Construction
public:
	CTCProcedureGoToDialog();   // standard constructor

	// Attributes
public:

	// Dialog Data
	//{{AFX_DATA(CTCProcedureGoToDialog)
	enum { IDD = IDD_TCPROCEDURE_GOTO_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCProcedurePropertiesCodeDialog *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureGoToDialog)
public:
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureGoToDialog)
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
// CTCProcedureFlowchartFindStepDialog dialog

#define IDC_TCPROCEDURE_FLOWCHART_FINDSTEP_NAME_STATIC   1001
#define IDC_TCPROCEDURE_FLOWCHART_FINDSTEP_NAME   1002
#define IDC_TCPROCEDURE_FLOWCHART_FINDSTEP_SEARCHHIDDENNAMES   1003
#define IDC_TCPROCEDURE_FLOWCHART_FINDSTEP   1004
#define IDC_TCPROCEDURE_FLOWCHART_FINDSTEP_HELP   1005

class CTCProcedureFlowchartFindStepDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedureFlowchartFindStepDialog)

	// Construction
public:
	CTCProcedureFlowchartFindStepDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szSearchItems;

	// Dialog Data
	//{{AFX_DATA(CTCProcedureFlowchartFindStepDialog)
	enum { IDD = IDD_TCPROCEDURE_FLOWCHART_FINDSTEP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureFlowchartFindStepDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureFlowchartFindStepDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnFindStepName();
	afx_msg void OnSelchangeStepName();
	afx_msg void OnEditchangeStepName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureStatusBar window

class CTCProcedureStatusBar : public CMFCStatusBar
{
	DECLARE_DYNCREATE(CTCProcedureStatusBar)

	// Construction
public:
	CTCProcedureStatusBar();
	~CTCProcedureStatusBar();

	// Attributes
private:
	CUIntArray  m_nPanesID;
	CStringArray  m_szPanesText;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL SetIndicators(CONST UINT *pIDs, INT nCount);

	BOOL SetPaneText(UINT nID, LPCTSTR pszText);
	BOOL GetPaneText(UINT nID, CString &szText) CONST;
	CString GetPaneText(UINT nID) CONST;

	INT CommandToIndex(UINT nID) CONST;

private:
	INT CalcPaneWidth(INT nIndex) CONST;
	INT CalcPaneWidth(INT nIndex, LPCTSTR pszText) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureStatusBar)
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
private:
	virtual VOID Initialize();
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureStatusBar)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureFlowchartThreadViewToolTip window

// Specify the telecommand procedure flowchart thread view tooltip timer identifiers
#define TCPROCEDUREFLOWCHARTTHREADVIEW_TOOLTIP_TIMERID   100
#define TCPROCEDUREFLOWCHARTTHREADVIEW_TOOLTIP_TIMEOUT   5000

class CTCProcedureFlowchartThreadViewToolTip : public CWnd
{
	DECLARE_DYNCREATE(CTCProcedureFlowchartThreadViewToolTip)

	// Construction
public:

	// Attributes
private:
	CFont  m_cFont[2];
	CString  m_szText;
	CString  m_szTitle;
	CUIntArray  m_nTabs;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST POINT &point, LPCTSTR pszTitle, LPCTSTR pszText, BOOL bAutoDestroy = FALSE);
	BOOL Destroy();

	BOOL SetTitleFont(CFont *pFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL SetTextFont(CFont *pFont);
	BOOL GetTextFont(CFont *pFont) CONST;

	VOID SetTabstops(CONST CUIntArray &nTabs);
	INT GetTabstops(CUIntArray &nTabs) CONST;

	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;

	VOID Update();
	VOID Update(LPCTSTR pszTitle, LPCTSTR pszText, BOOL bForced = FALSE);

private:
	VOID CalcTabstops(LPCTSTR pszTitle, LPCTSTR pszText);
	CSize CalcExtent(LPCTSTR pszTitle, LPCTSTR pszText, CPoint &ptTitle, CPoint &ptText);
	CSize CalcMargin();

	CString TranslateText(LPCTSTR pszText) CONST;

	VOID DrawContent(CDC *pDC);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureFlowchartThreadViewToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureFlowchartThreadViewToolTip)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureFlowchartThreadDocument

class CTCProcedureFlowchartThreadDocument : public CDocument
{
	DECLARE_DYNAMIC(CTCProcedureFlowchartThreadDocument)

	// Construction
public:
	CTCProcedureFlowchartThreadDocument();
	virtual ~CTCProcedureFlowchartThreadDocument();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureFlowchartThreadViewDebugPane window

class CTCProcedureFlowchartThreadViewDebugPane : public CWnd
{
	DECLARE_DYNCREATE(CTCProcedureFlowchartThreadViewDebugPane)

	// Construction
public:
	CTCProcedureFlowchartThreadViewDebugPane();

	// Attributes
private:
	CString  m_szToolTip;
	CStringArray  m_szBreakpoints;
	CDatabaseTCProcedureThreadBreakpoints  m_pDatabaseTCProcedureThreadBreakpoints;
	CTCProcedureFlowchartThreadViewToolTip  m_wndToolTip;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID SetBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;

	VOID Update();

	class CTCProcedureFlowchartThreadView *GetParent() CONST;

private:
	VOID DrawContent();
	VOID DrawContent(CDC *pDC);
	VOID DrawBreakpoints(CDC *pDC);
	VOID DrawExecutionpoint(CDC *pDC);

	CTCProcedureDocumentItem *FindBreakpoint(CTCProcedureDocumentItem *pStep) CONST;
	CTCProcedureDocumentItem *FindBreakpoint(CTCProcedureDocument *pSubSteps, CTCProcedureDocumentItem *pStep) CONST;

	CRect CalcBreakpointPosition(CTCProcedureDocumentItem *pStep) CONST;
	INT CalcBreakpointRadius() CONST;
	INT CalcBreakpointIndent() CONST;
	CRect CalcExecutionpointPosition() CONST;
	INT CalcExecutionpointExtent() CONST;
	INT CalcExecutionpointIndent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureFlowchartThreadViewDebugPane)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureFlowchartThreadViewDebugPane)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureFlowchartThreadView view

// Specify the telecommand procedure flowchart thread view timer related identifiers
#define TCPROCEDUREFLOWCHARTTHREADVIEW_DROP_TIMERID   0
#define TCPROCEDUREFLOWCHARTTHREADVIEW_DROP_TIMEOUT   100

class CTCProcedureFlowchartThreadView : public CScrollView
{
	DECLARE_DYNCREATE(CTCProcedureFlowchartThreadView)

	// Construction
public:
	CTCProcedureFlowchartThreadView();

	// Attributes
private:
	UINT  m_nStepID;
	UINT  m_nExecState;
	CPoint  m_ptDropStep;
	CString  m_szExecStep;
	HCURSOR  m_hPointCursor;
	HCURSOR  m_hToolTipCursor;
	LOGFONT  m_lfStepsLabelFont;
	COLORREF  m_nStepsLabelColor;
	COLORREF  m_nBackgroundColor[2];
	CTCProcedureDocument  *m_pFlowchart[2];
	CPoint  m_ptScroll;
private:
	BOOL  m_bUndo[2];
	CTCProcedureDocumentUndoList  m_cUndoList;
private:
	CTCProcedureFlowchartThreadViewToolTip  m_wndToolTip;
	CTCProcedureFlowchartThreadViewDebugPane  m_wndDebugPane;
private:
	CTCProcedureFlowchartFindStepDialog  m_dlgFind;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, BOOL bVisible = TRUE);

	BOOL SetSteps(CONST CTCProcedureDocument *pFlowchart, BOOL bNew = TRUE);
	BOOL GetSteps(CTCProcedureDocument *pFlowchart) CONST;
	INT EnumSteps(INT nY, CPtrArray &pSteps, CStringArray &szSteps) CONST;
	BOOL SetActiveStep(CONST CTCProcedureDocumentItem *pStep = NULL);
	CTCProcedureDocumentItem *GetActiveStep(BOOL bAll = FALSE) CONST;
	CTCProcedureDocumentItem *FindStep(LPCTSTR pszName) CONST;
	INT GetTotalSteps() CONST;

	VOID SetBreakpoints(CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;
	VOID SetExecutionpoint(LPCTSTR pszStep);
	CPoint GetExecutionpoint() CONST;
	VOID SetExecutionState(UINT nState);
	UINT GetExecutionState() CONST;

	VOID SetStepsLabelFont(CONST LOGFONT *plfFont, INT nFlags = TRUE);
	BOOL GetStepsLabelFont(LOGFONT *plfFont) CONST;
	VOID SetStepsLabelColor(COLORREF nColor, INT nFlags = TRUE);
	COLORREF GetStepsLabelColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor, INT nFlags = TRUE);
	COLORREF GetBackgroundColor() CONST;

	VOID UpdateAllSteps();
	VOID UpdateAllSteps(CPtrArray &pSteps);
	VOID UpdateAllSteps(UINT nState, CONST CStringArray &szSteps, CONST CUIntArray &nStates);

	VOID UpdateAllBreakpoints();

	BOOL UpdateUndoList(UINT nAction, CTCProcedureDocumentUndoItem *pItem, CONST CTCProcedureDocumentItem *pStep = NULL, CONST CTCProcedureDocumentItem *pOldStep = NULL);

	VOID GetPrintProperties(CMetaFileDC *pMetaDC);

	VOID SetSelectedStepID(UINT nStepID = -1);
	UINT GetSelectedStepID() CONST;

	BOOL SearchStep(LPCTSTR pszName, BOOL bHiddenNames);

	VOID DoUndo();
	BOOL CanUndo() CONST;
	BOOL IsUndoing() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;
	BOOL IsRedoing() CONST;

	VOID DoFindStep();
	BOOL CanFindStep() CONST;

	VOID DoCutStep();
	BOOL CanCutStep() CONST;
	VOID DoCopyStep();
	BOOL CanCopyStep() CONST;
	VOID DoPasteStep();
	BOOL CanPasteStep() CONST;
	VOID DoDeleteStep();
	BOOL CanDeleteStep() CONST;

	VOID UnSelectAllSteps();

	BOOL HasImage() CONST;

	CTCProcedureDocument *GetDocument() CONST;

	class CTCProcedureFlowchartTabCtrl *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID DrawContent();
	VOID DrawContent(CDC *pDC);

	VOID AdjustSteps(CONST CTCProcedureDocumentItem *pStep, INT nOffset);
	VOID AdjustSteps(CONST CTCProcedureDocumentItem *pSteps, CONST CTCProcedureDocumentItem *pStep, INT nOffset);

	POSITION InsertStep(CTCProcedureDocumentItem *pStep, CONST CTCProcedureDocumentItem *pPosition, BOOL bBefore = TRUE);
	POSITION FindStep(CONST CTCProcedureDocumentItem *pStep, BOOL bAll = FALSE) CONST;
	POSITION FindStep(CONST CTCProcedureDocumentItem *pSteps, CONST CTCProcedureDocumentItem *pStep, BOOL bAll = FALSE) CONST;
	CTCProcedureDocumentItem *FindStep(CONST POINT &pt, BOOL bImage = TRUE, BOOL bTreeSymbol = TRUE, BOOL bAll = FALSE) CONST;
	CTCProcedureDocumentItem *FindStep(CONST CTCProcedureDocumentItem *pSteps, CONST POINT &pt, BOOL bImage = TRUE, BOOL bTreeSymbol = TRUE, BOOL bAll = FALSE) CONST;
	CTCProcedureDocumentItem *FindStep(POSITION &lPosition) CONST;
	CTCProcedureDocumentItem *FindStep(CONST CTCProcedureDocumentItem *pSteps, POSITION &lPosition) CONST;
	BOOL DeleteStep(CTCProcedureDocumentItem *pStep);

	BOOL ShowStepProperties(CTCProcedureDocumentItem *pStep);

	VOID DrawDropStep(CONST POINT &pt);

	CTCProcedureDocumentItem *FindDropStep(UINT nType, CONST POINT &pt) CONST;
	CTCProcedureDocumentItem *FindContainerStep(CONST CTCProcedureDocumentItem *pStep) CONST;

	CPoint CalcDropPoint(UINT nType, CONST POINT &pt) CONST;
	CPoint CalcDropPoint(UINT nType, CONST POINT &pt, POSITION &lDropPosition) CONST;
	CPoint CalcDropPoint(UINT nType, CONST CTCProcedureDocumentItem *pSteps, CONST SIZE &sizeStep, CONST POINT &pt, CONST POINT &ptDrop, POSITION &lDropPosition) CONST;

	CRect CalcExecutionpointPosition(CTCProcedureDocumentItem *pStep) CONST;

	BOOL ConvertUndoItem(UINT nAction, CTCProcedureDocumentUndoItem *pItem, CONST CTCProcedureDocumentItem *pStep = NULL, CONST CTCProcedureDocumentItem *pOldStep = NULL);
	BOOL ConvertUndoItem(CONST CTCProcedureDocumentUndoItem *pItem, BOOL bUndo = TRUE);

	BOOL CopyToClipboard(CONST CTCProcedureDocumentItem *pStep);
	CTCProcedureDocumentItem *PasteFromClipboard();

	UINT TranslateStepIDToType(UINT nStepID) CONST;

	CRect CalcDebugPanePosition() CONST;
	CRect CalcDebugPanePosition(INT cx, INT cy) CONST;
	INT CalcDebugPaneMarginSize() CONST;

	CSize CalcScrollSizes() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureFlowchartThreadView)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureFlowchartThreadView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureFlowchartTabCtrl

class CTCProcedureFlowchartTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProcedureFlowchartTabCtrl)

	// Construction
public:
	CTCProcedureFlowchartTabCtrl();

	// Attributes
private:
	INT  m_nIndex;
	UINT  m_nClipboardFormat;
	CPtrArray  m_pViews;
private:
	CSize  m_sizeTabMargins;
	CFont  m_cTabFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, CONST CStringArray &szTabs);

	BOOL SetFlowcharts(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nFlags = TRUE);
	BOOL GetFlowcharts(CDatabaseTCProcedure *pDatabaseTCProcedure, INT nFlags = TRUE) CONST;

	BOOL SetBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(LPCTSTR pszThread, CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;

	INT EnumFlowchartViews(CStringArray &szThreads, CPtrArray &pViews) CONST;

	INT EnumSynchronizationObjects(CStringArray &szObjects) CONST;

	BOOL SetActiveStep(CONST CTCProcedureDocumentItem *pStep = NULL);
	CTCProcedureDocumentItem *GetActiveStep(BOOL bAll = FALSE) CONST;
	INT GetTotalSteps() CONST;

	VOID SetStepsLabelFont(CONST LOGFONT *plfFont, INT nFlags = TRUE);
	BOOL GetStepsLabelFont(LOGFONT *pFont) CONST;
	VOID SetStepsLabelColor(COLORREF nColor, INT nFlags = TRUE);
	COLORREF GetStepsLabelColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor, INT nFlags = TRUE);
	COLORREF GetBackgroundColor() CONST;

	VOID UpdateSteps();
	VOID UpdateSteps(LPCTSTR pszThread, CPtrArray &pSteps);

	BOOL UpdateUndoList(UINT nAction, CTCProcedureDocumentUndoItem *pItem, CONST CTCProcedureDocumentItem *pStep = NULL, CONST CTCProcedureDocumentItem *pOldStep = NULL);

	BOOL GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs);

	VOID SetSelectedThreadID(UINT nThreadID = 0);
	UINT GetSelectedThreadID() CONST;
	VOID SetSelectedStepID(UINT nStepID = -1);
	UINT GetSelectedStepID() CONST;
	BOOL IsSelected(CView *pThreadView) CONST;

	BOOL CanUndo() CONST;
	VOID DoUndo();
	BOOL CanRedo() CONST;
	VOID DoRedo();

	BOOL CanFindStep() CONST;
	VOID DoFindStep();

	BOOL CanCutStep() CONST;
	VOID DoCutStep();
	BOOL CanCopyStep() CONST;
	VOID DoCopyStep();
	BOOL CanPasteStep() CONST;
	VOID DoPasteStep();
	BOOL CanDeleteStep() CONST;
	VOID DoDeleteStep();

	VOID UnSelectAllSteps();

	VOID SetClipboardFormat(UINT nFormat);
	UINT GetClipboardFormat() CONST;

	CSize GetMargins() CONST;

	BOOL HasImage() CONST;

	class CTCProcedureFlowchartView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureFlowchartTabCtrl)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureFlowchartTabCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnSelchange(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureFlowchartView view

class CTCProcedureFlowchartView : public CView
{
	DECLARE_DYNCREATE(CTCProcedureFlowchartView)

	// Construction
public:
	CTCProcedureFlowchartView();

	// Attributes
private:
	CTCProcedureFlowchartTabCtrl  m_wndTabCtrl;

	// Operations
public:
	BOOL SetFlowcharts(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nFlags = TRUE);
	BOOL GetFlowcharts(CDatabaseTCProcedure *pDatabaseTCProcedure, INT nFlags = TRUE) CONST;

	BOOL SetBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(LPCTSTR pszThread, CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;

	INT EnumFlowchartViews(CStringArray &szThreads, CPtrArray &pViews) CONST;

	INT EnumSynchronizationObjects(CStringArray &szObjects) CONST;

	BOOL SetActiveStep(CONST CTCProcedureDocumentItem *pStep = NULL);
	CTCProcedureDocumentItem *GetActiveStep(BOOL bAll = FALSE) CONST;
	INT GetTotalSteps() CONST;

	VOID SetStepsLabelFont(CONST LOGFONT *plfFont, INT nFlags = TRUE);
	BOOL GetStepsLabelFont(LOGFONT *plfFont) CONST;
	VOID SetStepsLabelColor(COLORREF nColor, INT nFlags = TRUE);
	COLORREF GetStepsLabelColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor, INT nFlags = TRUE);
	COLORREF GetBackgroundColor() CONST;

	VOID UpdateSteps();
	VOID UpdateSteps(LPCTSTR pszThread, CPtrArray &pSteps);

	BOOL UpdateUndoList(UINT nAction, CTCProcedureDocumentUndoItem *pItem, CONST CTCProcedureDocumentItem *pStep = NULL, CONST CTCProcedureDocumentItem *pOldStep = NULL);

	BOOL GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs);

	VOID SetSelectedThreadID(UINT nThreadID = 0);
	UINT GetSelectedThreadID() CONST;
	VOID SetSelectedStepID(UINT nStepID = -1);
	UINT GetSelectedStepID() CONST;

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoFindStep();
	BOOL CanFindStep() CONST;

	VOID DoCutStep();
	BOOL CanCutStep() CONST;
	VOID DoCopyStep();
	BOOL CanCopyStep() CONST;
	VOID DoPasteStep();
	BOOL CanPasteStep() CONST;
	VOID DoDeleteStep();
	BOOL CanDeleteStep() CONST;

	VOID UnSelectAllSteps();

	BOOL HasImage() CONST;

	class CTCProcedureSplitterWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureFlowchartView)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedureFlowchartView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesOverviewDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_DESCRIPTION_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_DESCRIPTION   1005
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_COMMENTS_STATIC   1006
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_COMMENTS   1007
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_AUTHOR_STATIC   1008
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_AUTHOR   1009
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_CREATIONDATETIME_STATIC   1010
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_CREATIONDATETIME   1011
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_MODIFICATIONDATETIME_STATIC   1012
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_MODIFICATIONDATETIME   1013
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_DESTINATIONSUBSYSTEM_STATIC   1014
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_DESTINATIONSUBSYSTEM   1015
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_EXECUTIONMODE_STATIC   1016
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_EXECUTIONMODE   1017
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_VERIFICATIONSTATUS_STATIC   1018
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_VERIFICATIONSTATUS   1019
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_NOGRAPHICALINTERFACE   1020
#define IDC_TCPROCEDURE_PROPERTIES_OVERVIEW_HELP   1021

// Specify the telecommand procedure properties overview page related identifiers
#define TCPROCEDUREPROPERTIESOVERVIEW_UPDATE_TIMERID   100
#define TCPROCEDUREPROPERTIESOVERVIEW_UPDATE_TIMEOUT   0

class CTCProcedurePropertiesOverviewDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesOverviewDialog)

	// Construction
public:
	CTCProcedurePropertiesOverviewDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseTCProcedure  m_cDatabaseTCProcedure[2];
private:
	BOOL  m_bUpdate;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesOverviewDialog)
public:
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_OVERVIEW_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetInfo(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL GetInfo(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;

	class CTCProcedurePropertiesThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

public:
	VOID AdjustToPrivileges();

private:
	BOOL EnumExecutionModes();

	VOID ShowInfo();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesOverviewDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesOverviewDialog)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnNoGraphicalInterface();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeComments();
	afx_msg void OnEditchangeAuthor();
	afx_msg void OnEditchangeSubSystem();
	afx_msg void OnEditchangeVerificationStatus();
	afx_msg void OnSelchangeExecutionMode();
	afx_msg void OnSpinchangeCreationDate();
	afx_msg void OnSpinchangeModificationDate();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesArgumentsDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_LIST_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_LIST   1003
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_ADD   1004
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_REMOVE   1005
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_REMOVEALL   1006
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION   1007
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_NAME_STATIC   1008
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_NAME   1009
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_DESCRIPTION_STATIC   1010
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_DESCRIPTION   1011
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_TYPE_STATIC   1012
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_TYPE   1013
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_DEFAULTVALUE_STATIC   1014
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_DEFAULTVALUE   1015
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_FIXEDVALUE   1016
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_MINIMUMVALUE_STATIC   1017
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_MINIMUMVALUE   1018
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_MAXIMUMVALUE_STATIC   1019
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_MAXIMUMVALUE   1020
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_VALUE   1021
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_VALUE_RAW   1022
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_VALUE_CALIBRATED   1023
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_VALUE_CODING_STATIC   1024
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_VALUE_CODING   1025
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_VALUE_RADIX_STATIC   1026
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_VALUE_RADIX   1027
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_VALUE_CALTABLE_STATIC   1028
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_SPECIFICATION_VALUE_CALTABLE   1029
#define IDC_TCPROCEDURE_PROPERTIES_ARGUMENTS_HELP   1030

class CTCProcedurePropertiesArgumentsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesArgumentsDialog)

	// Construction
public:
	CTCProcedurePropertiesArgumentsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseTCProcedureArguments  m_pDatabaseTCProcedureArguments[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesArgumentsDialog)
public:
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_ARGUMENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetInfo(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL GetInfo(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;

	class CTCProcedurePropertiesThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

public:
	VOID AdjustToPrivileges();

private:
	BOOL EnumParameters();
	BOOL EnumParameterTypes();
	BOOL EnumValueCodings();
	BOOL EnumValueRadixes();
	BOOL EnumCalibrationTables();
	BOOL EnumDefaultValues();

	VOID ShowInfo();
	VOID ShowArgumentDetails();

	CString TranslateToIdentifierName(LPCTSTR pszName) CONST;

	BOOL CheckButton(UINT nButtonID) CONST;

	CDatabaseTCProcedureArgument *GetArgument() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesArgumentsDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesArgumentsDialog)	
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnFixedValue();
	afx_msg void OnRawValue();
	afx_msg void OnCalibratedValue();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeDefaultValue();
	afx_msg void OnEditchangeMinimumValue();
	afx_msg void OnEditchangeMaximumValue();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeDefaultValue();
	afx_msg void OnSelchangeMinimumValue();
	afx_msg void OnSelchangeMaximumValue();
	afx_msg void OnSelchangeValueCoding();
	afx_msg void OnSelchangeValueRadix();
	afx_msg void OnSelchangeCalibrationTable();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesVariablesDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_LIST_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_LIST   1003
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_ADD   1004
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_REMOVE   1005
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_REMOVEALL   1006
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION   1007
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_NAME_STATIC   1008
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_NAME   1009
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_DESCRIPTION_STATIC   1010
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_DESCRIPTION   1011
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_TYPE_STATIC   1012
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_TYPE   1013
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_DEFAULTVALUE_STATIC   1014
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_DEFAULTVALUE   1015
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_MINIMUMVALUE_STATIC   1016
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_MINIMUMVALUE   1017
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_MAXIMUMVALUE_STATIC   1018
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_MAXIMUMVALUE   1019
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_VALUE   1020
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_VALUE_CODING_STATIC   1021
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_VALUE_CODING   1022
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_VALUE_RADIX_STATIC   1023
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_SPECIFICATION_VALUE_RADIX   1024
#define IDC_TCPROCEDURE_PROPERTIES_VARIABLES_HELP   1025

class CTCProcedurePropertiesVariablesDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesVariablesDialog)

	// Construction
public:
	CTCProcedurePropertiesVariablesDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CDatabaseTCProcedureVariables  m_pDatabaseTCProcedureVariables[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesVariablesDialog)
public:
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_VARIABLES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetInfo(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL GetInfo(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;

	class CTCProcedurePropertiesThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

public:
	VOID AdjustToPrivileges();

private:
	BOOL EnumValueTypes();
	BOOL EnumValueCodings();
	BOOL EnumValueRadixes();

	VOID ShowInfo();
	VOID ShowVariableDetails();

	CString TranslateToIdentifierName(LPCTSTR pszName) CONST;

	BOOL CheckButton(UINT nButtonID) CONST;

	CDatabaseTCProcedureVariable *GetVariable() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesVariablesDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesVariablesDialog)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeDefaultValue();
	afx_msg void OnEditchangeMinimumValue();
	afx_msg void OnEditchangeMaximumValue();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeValueCoding();
	afx_msg void OnSelchangeValueRadix();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesThreadsDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_THREADS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_ADD   1004
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_REMOVE   1005
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_REMOVEALL   1006
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_DESCRIPTION_STATIC   1007
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_DESCRIPTION   1008
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_COMMENTS_STATIC   1009
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_COMMENTS   1010
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_ACTIVATIONEXPRESSION_STATIC   1011
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_ACTIVATIONEXPRESSION   1012
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_AUTOENABLED   1013
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_STATE   1014
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_STATE_EXECUTIONMODE_STATIC   1015
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_STATE_EXECUTIONMODE   1016
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_STATE_AUTHORITY_STATIC   1017
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_STATE_AUTHORITY   1018
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_STATE_RUNSTATE_STATIC   1019
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_STATE_RUNSTATE   1020
#define IDC_TCPROCEDURE_PROPERTIES_THREADS_HELP   1021

// Specify the telecommand procedure properties thread page related identifiers
#define TCPROCEDUREPROPERTIESTHREADS_UPDATE_TIMERID   100
#define TCPROCEDUREPROPERTIESTHREADS_UPDATE_TIMEOUT   1000

class CTCProcedurePropertiesThreadsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesThreadsDialog)

	// Construction
public:
	CTCProcedurePropertiesThreadsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CString  m_szStatus[3];
	CDatabaseTCProcedure  m_cDatabaseTCProcedure[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesThreadsDialog)
public:
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_THREADS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetInfo(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL GetInfo(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;

	class CTCProcedurePropertiesThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

public:
	VOID AdjustToPrivileges();

private:
	BOOL EnumThreads();

	VOID ShowInfo();
	VOID ShowThreadDetails();

	BOOL CheckButton(UINT nButtonID) CONST;

	CDatabaseTCProcedureThread *GetThread() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesThreadsDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesThreadsDialog)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnAutoEnabled();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeComments();
	afx_msg void OnEditchangeActivationExpression();
	afx_msg void OnSelchangeName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesStepsDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_STEPS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_DESCRIPTION_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_DESCRIPTION   1005
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_COMMENTS_STATIC   1006
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_COMMENTS   1007
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION   1008
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TYPE_STATIC   1009
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TYPE   1010
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIME_STATIC   1011
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIME   1012
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIMEOFFSET_STATIC   1013
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIMEOFFSET   1014
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIMEOFFSET_SECONDS_STATIC   1015
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIMEDELAY_STATIC   1016
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIMEDELAY   1017
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIMEDELAY_SECONDS_STATIC   1018
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_SYNCOBJECT_STATIC   1019
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_SYNCOBJECT   1020
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_MESSAGE_STATIC   1021
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_MESSAGE   1022
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIMEWINDOW_STATIC   1023
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIMEWINDOW   1024
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_TIMEWINDOW_SECONDS_STATIC   1025
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_EXPRESSION_STATIC   1026
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_EXPRESSION   1027
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_PREEXECUTIONEXPRESSION_STATIC   1028
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_TRIGGERINFORMATION_PREEXECUTIONEXPRESSION   1029
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_CONFIRMATIONINFORMATION   1030
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_CONFIRMATIONINFORMATION_TYPE_STATIC   1031
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_CONFIRMATIONINFORMATION_TYPE   1032
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_CONFIRMATIONINFORMATION_MESSAGE_STATIC   1033
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_CONFIRMATIONINFORMATION_MESSAGE   1034
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_CONFIRMATIONINFORMATION_TIMEWINDOW_STATIC   1035
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_CONFIRMATIONINFORMATION_TIMEWINDOW   1036
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_CONFIRMATIONINFORMATION_TIMEWINDOW_SECONDS_STATIC   1037
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_CONFIRMATIONINFORMATION_EXPRESSION_STATIC   1038
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_CONFIRMATIONINFORMATION_EXPRESSION   1039
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_FAILUREINFORMATION   1040
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_FAILUREINFORMATION_FORCE   1041
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_FAILUREINFORMATION_FORCE_STATE   1042
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_FAILUREINFORMATION_FORCE_STATIC   1043
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_FAILUREINFORMATION_FORCE_ACTION   1044
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_FAILUREINFORMATION_STATE_STATIC   1045
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_FAILUREINFORMATION_STATE   1046
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_FAILUREINFORMATION_GOTO   1047
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_FAILUREINFORMATION_GOTOLABEL   1048
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_FAILUREINFORMATION_EXITPROCEDURE   1049
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_SPECIFICPROPERTIES   1050
#define IDC_TCPROCEDURE_PROPERTIES_STEPS_HELP   1051

// Specify the telecommand procedure steps page related identifiers
#define TCPROCEDUREPROPERTIESSTEPS_TRIGGERTIME_MINIMUMINTERVAL   0
#define TCPROCEDUREPROPERTIESSTEPS_TRIGGERTIME_MAXIMUMINTERVAL   (SECONDSPERMINUTE*MINUTESPERHOUR*HOURSPERDAY)
#define TCPROCEDUREPROPERTIESSTEPS_TRIGGERTIME_DEFAULTINTERVAL   SECONDSPERMINUTE
#define TCPROCEDUREPROPERTIESSTEPS_TRIGGERWINDOW_MINIMUMINTERVAL   -1
#define TCPROCEDUREPROPERTIESSTEPS_TRIGGERWINDOW_MAXIMUMINTERVAL   (SECONDSPERMINUTE*MINUTESPERHOUR*HOURSPERDAY)
#define TCPROCEDUREPROPERTIESSTEPS_TRIGGERWINDOW_DEFAULTINTERVAL   SECONDSPERMINUTE
#define TCPROCEDUREPROPERTIESSTEPS_CONFIRMATIONWINDOW_MINIMUMINTERVAL   -1
#define TCPROCEDUREPROPERTIESSTEPS_CONFIRMATIONWINDOW_MAXIMUMINTERVAL   (SECONDSPERMINUTE*MINUTESPERHOUR*HOURSPERDAY)
#define TCPROCEDUREPROPERTIESSTEPS_CONFIRMATIONWINDOW_DEFAULTINTERVAL   SECONDSPERMINUTE

class CTCProcedurePropertiesStepsDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesStepsDialog)

	// Construction
public:
	CTCProcedurePropertiesStepsDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CPtrArray  m_pSteps;
	BOOL  m_bUpdate;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesStepsDialog)
public:
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_STEPS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetInfo(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL GetInfo(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;

	VOID UpdateSteps(CONST CPtrArray &pSteps);

	class CTCProcedurePropertiesThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

public:
	VOID AdjustToPrivileges();

private:
	BOOL EnumSteps();
	BOOL EnumStepStates();
	BOOL EnumTriggerTypes();
	BOOL EnumConfirmationTypes();
	BOOL EnumSynchronizationObjects();
	BOOL EnumFailureStates();
	BOOL EnumFailureOptions();

	VOID ShowInfo();

	VOID UpdateAllSteps();

	CTCProcedureDocumentItem *GetStep() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesStepsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesStepsDialog)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFailureOptions();
	afx_msg void OnFailureGoto();
	afx_msg void OnFailureExit();
	afx_msg void OnProperties();
	afx_msg void OnEditchangeName();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeComments();
	afx_msg void OnEditchangeTriggerMessage();
	afx_msg void OnEditchangeTriggerExpression();
	afx_msg void OnEditchangePreexecutionExpression();
	afx_msg void OnEditchangeConfirmationMessage();
	afx_msg void OnEditchangeConfirmationExpression();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeTriggerType();
	afx_msg void OnSelchangeTriggerSynchronizationObject();
	afx_msg void OnSelchangeConfirmationType();
	afx_msg void OnSelchangeFailureOptionsState();
	afx_msg void OnSelchangeFailureOptionsAction();
	afx_msg void OnSelchangeFailureState();
	afx_msg void OnSelchangeFailureLabel();
	afx_msg void OnSpinchangeTriggerTime();
	afx_msg void OnSpinchangeTriggerTimeOffset();
	afx_msg void OnSpinchangeTriggerTimeDelay();
	afx_msg void OnSpinchangeTriggerTimeWindow();
	afx_msg void OnSpinchangeConfirmationTimeWindow();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesTestTMParametersCalibrationPage dialog

#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCProcedurePropertiesTestTMParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTestTMParametersCalibrationPage)

	// Construction
public:
	CTCProcedurePropertiesTestTMParametersCalibrationPage();

	// Attributes
private:
	INT  m_nCalTableID;
	ULONGLONG  m_nCalTableType;
	CUIntArray  m_nCalTableRefs;
	CUIntArray  m_nCalValidityRefs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesTestTMParametersCalibrationPage)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter);
	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesTestTMParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTestTMParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesTestTMParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesTestTMParametersFolderTabCtrl window

class CTCProcedurePropertiesTestTMParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTestTMParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCProcedurePropertiesTestTMParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTestTMParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesTestTMParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesTestTMParametersFolder

class CTCProcedurePropertiesTestTMParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTestTMParametersFolder)

	// Construction
public:
	CTCProcedurePropertiesTestTMParametersFolder();

	// Attributes
private:
	CTCProcedurePropertiesTestTMParametersFolderTabCtrl  m_wndTabCtrl;
	CTCProcedurePropertiesTestTMParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CTMParameter *pTMParameter);

	BOOL GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesTestTMParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTestTMParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesTestTMParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesTestTMParametersDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_ITEM_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_ITEM   1003
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_FOLDER   1004
#define IDC_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_HELP   1005

class CTCProcedurePropertiesTestTMParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTestTMParametersDialog)

	// Construction
public:
	CTCProcedurePropertiesTestTMParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szTable;
	CTMParameter  m_cTMParameter;
private:
	CTCProcedurePropertiesTestTMParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesTestTMParametersDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_TESTTMPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST CTMParameter *pTMParameter, CString &szTable, CString &szValue);

	VOID SetSelectedCalibrationPoint(LPCTSTR pszTable, LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesDebugDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTestTMParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesTestTMParametersDialog)
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
// CTCProcedurePropertiesTestTCParametersCalibrationPage dialog

#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCProcedurePropertiesTestTCParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTestTCParametersCalibrationPage)

	// Construction
public:
	CTCProcedurePropertiesTestTCParametersCalibrationPage();

	// Attributes
private:
	UINT  m_nCalTableType;
	CStringArray  m_szCalTableIDs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesTestTCParametersCalibrationPage)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CTCParameter *pTCParameter);
	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesTestTCParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTestTCParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesTestTCParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesTestTCParametersFolderTabCtrl window

class CTCProcedurePropertiesTestTCParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTestTCParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCProcedurePropertiesTestTCParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTestTCParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesTestTCParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesTestTCParametersFolder

class CTCProcedurePropertiesTestTCParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTestTCParametersFolder)

	// Construction
public:
	CTCProcedurePropertiesTestTCParametersFolder();

	// Attributes
private:
	CTCProcedurePropertiesTestTCParametersFolderTabCtrl  m_wndTabCtrl;
	CTCProcedurePropertiesTestTCParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CTCParameter *pTCParameter);

	BOOL GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesTestTCParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTestTCParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesTestTCParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesTestTCParametersDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_ITEM_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_ITEM   1003
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_FOLDER   1004
#define IDC_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_HELP   1005

class CTCProcedurePropertiesTestTCParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTestTCParametersDialog)

	// Construction
public:
	CTCProcedurePropertiesTestTCParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szTable;
	CTCParameter  m_cTCParameter;
private:
	CTCProcedurePropertiesTestTCParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesTestTCParametersDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_TESTTCPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST CTCParameter *pTCParameter, CString &szTable, CString &szValue);

	VOID SetSelectedCalibrationPoint(LPCTSTR pszTable, LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szTable, CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesDebugDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTestTCParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesTestTCParametersDialog)
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
// CTCProcedurePropertiesTestProfileParametersDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_LIST_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_LIST   1003
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_ADD   1004
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_REMOVE   1005
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_REMOVEALL   1006
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_PARAMETER_STATIC   1007
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_PARAMETER   1008
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUE_STATIC   1009
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUE   1010
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUE_SAMPLE_STATIC   1011
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUE_SAMPLE   1012
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUEINTERPRETATION   1013
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUEINTERPRETATION_RAW   1014
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUEINTERPRETATION_CALIBRATED   1015
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUEINTERPRETATION_CODING_STATIC   1016
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUEINTERPRETATION_CODING   1017
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUEINTERPRETATION_RADIX_STATIC   1018
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUEINTERPRETATION_RADIX   1019
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUEINTERPRETATION_TABLE_STATIC   1020
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_VALUEINTERPRETATION_TABLE   1021
#define IDC_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_HELP   1022

// Specify the telecommand procedure test profile parameters related identifiers
#define TCPROCEDUREPROPERTIESTESTPROFILEPARAMETERS_MINIMUMSAMPLE   0
#define TCPROCEDUREPROPERTIESTESTPROFILEPARAMETERS_MAXIMUMSAMPLE   100
#define TCPROCEDUREPROPERTIESTESTPROFILEPARAMETERS_DEFAULTSAMPLE   0

class CTCProcedurePropertiesTestProfileParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTestProfileParametersDialog)

	// Construction
public:
	CTCProcedurePropertiesTestProfileParametersDialog();   // standard constructor

	// Attributes
private:
	CDatabaseTMParameters  m_pDatabaseTMParameters[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesTestProfileParametersDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_TESTPROFILEPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CDatabaseTMParameters &pDatabaseTMParameters);

	class CTCProcedurePropertiesDebugDialog *GetParent() CONST;

private:
	BOOL EnumParameters();
	BOOL EnumValueCodings();
	BOOL EnumValueRadixes();
	BOOL EnumCalibrationTables();

	VOID ShowParameterDetails();
	VOID ShowParameterDetails(CONST CDatabaseTMParameter *pDatabaseTMParameter);

	CString CollectValueSample(LPCTSTR pszValues, LPCTSTR pszValue, INT nSample) CONST;
	CString ExtractValueSample(LPCTSTR pszValues, INT nSample) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	CDatabaseTMParameter *FindParameter() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTestProfileParametersDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesTestProfileParametersDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnValueInterpretationRaw();
	afx_msg void OnValueInterpretationCalibrated();
	afx_msg void OnEditchangeValue();
	afx_msg void OnSelchangeParameter();
	afx_msg void OnSelchangeValue();
	afx_msg void OnSelchangeValueInterpretationRadix();
	afx_msg void OnSelchangeValueInterpretationTable();
	afx_msg void OnSpinchangeValueSample();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesDebugDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_DETAILS   1001
#define FIRSTNONDEBUGWATCHCTRLID   1002
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_THREAD_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_THREAD   1003
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINTS_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINTS   1005
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_ADD   1006
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_REMOVE   1007
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_REMOVEALL   1008
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT   1009
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_LOCATION_STATIC   1010
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_LOCATIONSTEP_STATIC   1011
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_LOCATION   1012
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_STATIC   1013
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_ALWAYS   1014
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_FAILEDTRIGGER   1015
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_FAILEDBODY   1016
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_FAILEDCONFIRMATION   1017
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_BREAKPOINT_DISABLED   1018
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILES_STATIC   1019
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILES   1020
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ADD   1021
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_REMOVE   1022
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_REMOVEALL   1023
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE   1024
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_NAME_STATIC   1025
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_NAME   1026
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_PARAMETERS_STATIC   1027
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_PARAMETERS   1028
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_PARAMETER_ADD   1029
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_PARAMETER_REMOVE   1030
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_PARAMETER_REMOVEALL   1031
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION   1032
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_LOCATION_STATIC   1033
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_LOCATIONSTEP_STATIC   1034
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_LOCATION   1035
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_TIME_STATIC   1036
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_TIME_IMMEDIATELY   1037
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_TIME_AFTERSTART   1038
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_TIME_AFTERSTART_SECONDS   1039
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_TIME_AFTERSTART_SECONDS_STATIC   1040
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_TIME_AFTERSTEP   1041
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_TIME_AFTERSTEP_SECONDS   1042
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_TIME_AFTERSTEP_SECONDS_STATIC   1043
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_TESTPROFILE_ACTIVATION_DISABLED   1044
#define LASTNONDEBUGWATCHCTRLID   1044
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_STATIC   1045
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS   1046
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_REMARK   1047
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_VALUE_STATIC   1048
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_VALUE   1049
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_SAMPLE_STATIC   1050
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_SAMPLE   1051
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_VALUE_SET   1052
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_TABLE_STATIC   1053
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_TABLE   1054
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_STATUS_STATIC   1055
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_STATUS_NOLIMIT   1056
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_STATUS_HARDLIMIT   1057
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_STATUS_SOFTLIMIT   1058
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_STATUS_DELTALIMIT   1059
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_STATUS_CONSISTENCYLIMIT   1060
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_STATUS_VALID   1061
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_STATUS_INVALID   1062
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_QUALITY_STATIC   1063
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_QUALITY_GOOD   1064
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_WATCH_IDENTIFIERS_QUALITY_BAD   1065
#define IDC_TCPROCEDURE_PROPERTIES_DEBUG_HELP   1066

// Specify the telecommand procedure debug page related identifiers
#define TCPROCEDUREPROPERTIESDEBUG_TESTPROFILEDELAY_MINIMUMINTERVAL   1
#define TCPROCEDUREPROPERTIESDEBUG_TESTPROFILEDELAY_MAXIMUMINTERVAL   (SECONDSPERMINUTE*MINUTESPERHOUR*HOURSPERDAY)
#define TCPROCEDUREPROPERTIESDEBUG_TESTPROFILEDELAY_DEFAULTINTERVAL   SECONDSPERMINUTE
#define TCPROCEDUREPROPERTIESDEBUG_WATCHIDENTIFIERS_MINIMUMSAMPLE   0
#define TCPROCEDUREPROPERTIESDEBUG_WATCHIDENTIFIERS_MAXIMUMSAMPLE   100
#define TCPROCEDUREPROPERTIESDEBUG_WATCHIDENTIFIERS_DEFAULTSAMPLE   0

class CTCProcedurePropertiesDebugDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesDebugDialog)

	// Construction
public:
	CTCProcedurePropertiesDebugDialog(CWnd *pParentWnd = NULL);   // standard constructor
	~CTCProcedurePropertiesDebugDialog();

	// Attributes
private:
	CRect  m_rCtrl[2];
	CPtrArray  m_pSteps;
	CPtrArray  m_pIdentifiers;
	CUIntArray  m_nIdentifierTypes;
	CStringArray  m_szIdentifiers;
	CTMParameters  m_pTMParameters;
	CTCParameters  m_pTCParameters;
	CLongUIntArray  m_nIdentifierAttributes;
	CDatabaseTCProcedure  m_cDatabaseTCProcedure[2];
	CDatabaseTMParameters  m_pDatabaseTMParameters;
private:
	CStringArray  m_szColumns[4];
private:
	CCriticalSection  *m_pCriticalSection;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesDebugDialog)
public:
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_DEBUG_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetInfo(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL GetInfo(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;

	BOOL SetBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(LPCTSTR pszThread, CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;

	VOID UpdateSteps(LPCTSTR pszThread, CONST CPtrArray &pSteps);
	VOID UpdateBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	VOID UpdateIdentifiers(CTMEnvironment *pTMEnvironment, CTCEnvironment *pTCEnvironment, CONST CStringArray &szIdentifiers, CONST CUIntArray &nIdentifierTypes, CONST CLongUIntArray &nIdentifierAttributes, CONST CPtrArray &pIdentifiers);

	class CTCProcedurePropertiesThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

public:
	VOID AdjustToPrivileges();

private:
	BOOL EnumThreads();
	BOOL EnumBreakpoints();
	BOOL EnumBreakpointLocations();
	BOOL EnumTestProfiles();
	BOOL EnumTestProfileLocations();
	BOOL EnumTestProfileParameters();

	VOID ShowInfo();
	VOID ShowBreakpointProperties();
	VOID ShowTestProfileProperties();
	VOID ShowWatchIdentifierProperties();

	VOID UpdateIdentifiers();

	BOOL UpdateParameterValue(LPCTSTR pszTag, UINT nType, ULONGLONG nAttributes, LPCTSTR pszValue, INT nSample, BYTE nStatus, LPCTSTR pszTable);
	BOOL UpdateParameterValue(CTMParameter *pTMParameter, ULONGLONG nRawValue, INT nSample, BYTE nStatus, LPCTSTR pszTable);
	BOOL UpdateParameterValue(CTCParameter *pTCParameter, ULONGLONG nRawValue, INT nSample, BYTE nStatus);
	BOOL UpdateParameterValue(CTCParameter *pTCParameter, TIMETAG tRawValue, INT nSample, BYTE nStatus);

	CString ConvertTestProfileParameterValues(LPCTSTR pszValues) CONST;

	INT FindColumnIndex(UINT nCtrlID, LPCTSTR pszColumn) CONST;

	CDatabaseTCProcedureThread *GetThread() CONST;

	BOOL Lock();
	BOOL Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesDebugDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesDebugDialog)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnAddBreakpoint();
	afx_msg void OnRemoveBreakpoint();
	afx_msg void OnRemoveAllBreakpoints();
	afx_msg void OnAddTestProfile();
	afx_msg void OnRemoveTestProfile();
	afx_msg void OnRemoveAllTestProfiles();
	afx_msg void OnAddTestProfileParameter();
	afx_msg void OnRemoveTestProfileParameter();
	afx_msg void OnRemoveAllTestProfileParameters();
	afx_msg void OnBreakAlways();
	afx_msg void OnBreakAtFailedTrigger();
	afx_msg void OnBreakAtFailedBody();
	afx_msg void OnBreakAtFailedConfirmation();
	afx_msg void OnDisableBreakpoint();
	afx_msg void OnExecuteImmediately();
	afx_msg void OnExecuteDelayedAfterStart();
	afx_msg void OnExecuteDelayedAfterStep();
	afx_msg void OnDisableTestProfile();
	afx_msg void OnSetWatchIdentifierValue();
	afx_msg void OnWatchIdentifierStatusNoLimit();
	afx_msg void OnWatchIdentifierStatusSoftLimit();
	afx_msg void OnWatchIdentifierStatusHardLimit();
	afx_msg void OnWatchIdentifierStatusDeltaLimit();
	afx_msg void OnWatchIdentifierStatusConsistencyLimit();
	afx_msg void OnWatchIdentifierStatusValid();
	afx_msg void OnWatchIdentifierStatusInvalid();
	afx_msg void OnWatchIdentifierQualityGood();
	afx_msg void OnWatchIdentifierQualityBad();
	afx_msg void OnSelchangeThread();
	afx_msg void OnSelchangeBreakpointLocation();
	afx_msg void OnSelchangeTestProfileLocation();
	afx_msg void OnSelchangeWatchIdentifierTable();
	afx_msg void OnSelchangeWatchIdentifierValue();
	afx_msg void OnEditchangeTestProfileName();
	afx_msg void OnEditchangeWatchIdentifierValue();
	afx_msg void OnSpinchangeDelayAfterStart();
	afx_msg void OnSpinchangeDelayAfterStep();
	afx_msg void OnSpinchangeWatchIdentifierSample();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesCodeEditToolTip window

// Specify the telecommand procedure properties code edit tooltip timer identifiers
#define TCPROCEDUREPROPERTIESCODEEDIT_TOOLTIP_TIMERID   100
#define TCPROCEDUREPROPERTIESCODEEDIT_TOOLTIP_TIMEOUT   5000

class CTCProcedurePropertiesCodeEditToolTip : public CWnd
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesCodeEditToolTip)

	// Construction
public:

	// Attributes
private:
	CFont  m_cFont[2];
	CString  m_szText;
	CString  m_szTitle;
	CUIntArray  m_nTabs;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST POINT &point, LPCTSTR pszTitle, LPCTSTR pszText, BOOL bAutoDestroy = FALSE);
	BOOL Destroy();

	BOOL SetTitleFont(CFont *pFont);
	BOOL GetTitleFont(CFont *pFont) CONST;
	BOOL SetTextFont(CFont *pFont);
	BOOL GetTextFont(CFont *pFont) CONST;

	VOID SetTabstops(CONST CUIntArray &nTabs);
	INT GetTabstops(CUIntArray &nTabs) CONST;

	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	VOID SetText(LPCTSTR pszText);
	CString GetText() CONST;

	VOID Update();
	VOID Update(LPCTSTR pszTitle, LPCTSTR pszText, BOOL bForced = FALSE);

private:
	VOID CalcTabstops(LPCTSTR pszTitle, LPCTSTR pszText);
	CSize CalcExtent(LPCTSTR pszTitle, LPCTSTR pszText, CPoint &ptTitle, CPoint &ptText);
	CSize CalcMargin();

	CString TranslateText(LPCTSTR pszText) CONST;

	VOID DrawContent(CDC *pDC);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesCodeEditToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesCodeEditToolTip)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesCodeEdit window

#define TCPROCEDUREPROPERTIESCODEEDIT_UPDATE_TIMERID   100
#define TCPROCEDUREPROPERTIESCODEEDIT_UPDATE_TIMEOUT   0
#define TCPROCEDUREPROPERTIESCODEEDIT_SCROLL_TIMERID   101
#define TCPROCEDUREPROPERTIESCODEEDIT_SCROLL_TIMEOUT   250

class CTCProcedurePropertiesCodeEdit : public CTPLCodeEdit
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesCodeEdit)

	// Construction
public:
	CTCProcedurePropertiesCodeEdit();

	// Attributes
private:
	CStringArray  m_szBreakpoints;
	CDatabaseTCProcedureThreadBreakpoints  m_pDatabaseTCProcedureThreadBreakpoints;
private:
	CStringArray  m_szExecutionThreads;
	CUIntArray  m_nExecutionStates;
	CUIntArray  m_nExecutionLines;
private:
	INT  m_nCodeLines;
	CFont  m_cCodeFont;
	CSize  m_sizeCodeFont;
	CPoint  m_ptCodeScroll;
	BOOL  m_bCodeProtection;
private:
	UINT_PTR  m_nTimerID;
private:
	CString  m_szToolTip;
	CTCProcedurePropertiesCodeEditToolTip  m_wndToolTip;
private:
	CCriticalSection  m_cCriticalSection;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, UINT nID);

	BOOL SetCode(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL GetCode(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;
	INT GetCodeSize() CONST;

	VOID SetBreakpoints(CONST CStringArray &szBreakpoints, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(CStringArray &szBreakpoints, CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;

	VOID UpdateBreakpoints();
	VOID UpdateExecutionpoint(LPCTSTR pszThread, UINT nState = TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING, UINT nLine = 0);

	BOOL SetFont(CFont *pFont, BOOL bRedraw = TRUE);
	BOOL GetFont(CFont *pFont) CONST;

	VOID Protect(BOOL bProtect = TRUE);
	BOOL IsProtected() CONST;

	class CTCProcedurePropertiesCodeDialog *GetParent() CONST;

private:
	VOID DrawMargin();
	VOID DrawMargin(CDC *pDC);
	VOID DrawBreakpoints(CDC *pDC);
	VOID DrawExecutionpoint(CDC *pDC);

	CString CheckLine(UINT nLine) CONST;

	INT FindKeyword(LPCTSTR pszSourceCode, LPCTSTR pszKeyword, INT nPos) CONST;
	LPCTSTR FindKeyword(LPCTSTR pszSourceCode, LPCTSTR pszKeyword) CONST;

	VOID RelocateBreakpoints(INT nLine, INT nOffset);

	CRect CalcBreakpointPosition(INT nLine) CONST;
	INT CalcBreakpointRadius() CONST;
	INT CalcBreakpointIndent() CONST;
	CRect CalcExecutionpointPosition(INT nLine) CONST;
	INT CalcExecutionpointExtent() CONST;
	INT CalcExecutionpointIndent() CONST;

	CRect CalcMargin() CONST;

	BOOL Lock();
	BOOL Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesCodeEdit)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesCodeEdit)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnKillFocus(CWnd *pNewWnd);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg LRESULT OnSetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUndo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRedo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPaste(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCut(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClear(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesCodeDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_CODE_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_CODE_TEXT   1002
#define IDC_TCPROCEDURE_PROPERTIES_CODE_GENERATECODE   1003
#define IDC_TCPROCEDURE_PROPERTIES_CODE_USECUSTOMCODE   1004
#define IDC_TCPROCEDURE_PROPERTIES_CODE_HELP   1005

class CTCProcedurePropertiesCodeDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesCodeDialog)

	// Construction
public:
	CTCProcedurePropertiesCodeDialog(CWnd *pParentWnd = NULL);   // standard constructor

	// Attributes
private:
	CTCProcedureFindDialog  m_dlgFind;
	CTCProcedureGoToDialog  m_dlgGoTo;
	CTCProcedureReplaceDialog  m_dlgReplace;
private:
	CTCProcedurePropertiesCodeEdit  m_wndCode;
private:
	CDatabaseTCProcedureThreadBreakpoints  m_pDatabaseTCProcedureThreadBreakpoints;
	CStringArray  m_szBreakpoints;
	CString  m_szCode[2];
	BOOL  m_bCustomCode;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesCodeDialog)
public:
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_CODE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetInfo(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL GetInfo(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;

	VOID SetBreakpoints(CONST CStringArray &szBreakpoints, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(CStringArray &szBreakpoints, CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;

	VOID UpdateBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	VOID UpdateExecutionpoint(LPCTSTR pszThread, UINT nState = TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING, UINT nLine = 0);

	BOOL SearchCode(LPCTSTR pszText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL ReplaceAllCode(LPCTSTR pszText, LPCTSTR pszReplaceText, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord);
	BOOL GoToCode(UINT nLine, BOOL bDown = FALSE, BOOL bUp = FALSE);
	BOOL GoToCode(LPCTSTR pszLine);
	VOID UpdateCode(LPCTSTR pszText);
	BOOL HasCode() CONST;

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

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoCutSel();
	BOOL CanCutSel() CONST;
	VOID DoCopySel();
	BOOL CanCopySel() CONST;
	VOID DoPasteSel();
	BOOL CanPasteSel() CONST;
	VOID DoDeleteSel();
	BOOL CanDeleteSel() CONST;

	VOID DoSelectAllCode();
	VOID UnSelectAllCode();
	BOOL CanSelectAllCode() CONST;

	VOID ShowDialogs(BOOL bShow);
	BOOL HasDialogs() CONST;

	BOOL GetPrintProperties(CRichEditCtrl **pEditCtrl) CONST;

	class CTCProcedurePropertiesThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

public:
	VOID AdjustToPrivileges();

private:
	VOID ShowInfo();

	INT FindKeyword(LPCTSTR pszSourceCode, LPCTSTR pszKeyword, INT nPos) CONST;
	LPCTSTR FindKeyword(LPCTSTR pszSourceCode, LPCTSTR pszKeyword) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesCodeDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesCodeDialog)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnGenerateCode();
	afx_msg void OnUseCustomCode();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesTCStackList window

class CTCProcedurePropertiesTCStackList : public CTextView
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTCStackList)

	// Construction
public:
	CTCProcedurePropertiesTCStackList();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTCStackList)
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesTCStackList)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesTCStackDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_LIST_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_LIST   1003
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_RELEASEWAITMODE   1004
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_RELEASEWAITINTERVAL   1005
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_RELEASEWAITINTERVAL_STATIC   1006
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_NOPREEXECUTIONCHECKS   1007
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_NOEXECUTIONCHECKS   1008
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_SUSPEND   1009
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_RESUME   1010
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_REMOVE   1011
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_REMOVEALL   1012
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_MESSAGE   1013
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_LOGFILE   1014
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_LOGFILE_FILENAME   1015
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_LOGFILE_BROWSE   1016
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_LOGFILE_RESET   1017
#define IDC_TCPROCEDURE_PROPERTIES_TCSTACK_HELP   1018

// Specify the telecommand procedure tcstack page related identifiers
#define TCPROCEDUREPROPERTIESTCSTACK_RELEASEWAIT_MINIMUMINTERVAL   1
#define TCPROCEDUREPROPERTIESTCSTACK_RELEASEWAIT_MAXIMUMINTERVAL   SECONDSPERHOUR
#define TCPROCEDUREPROPERTIESTCSTACK_RELEASEWAIT_DEFAULTINTERVAL   (5*SECONDSPERMINUTE)

class CTCProcedurePropertiesTCStackDialog : public CLocaleDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTCStackDialog)

	// Construction
public:
	CTCProcedurePropertiesTCStackDialog(CWnd *pParentWnd = NULL);   // standard constructor
	~CTCProcedurePropertiesTCStackDialog();

	// Attributes
private:
	CTCProcedurePropertiesTCStackList  m_wndList;
private:
	CTCProcedureItems  m_pTCProcedureItems;
	CTimeSpan  m_tReleaseWaitInterval;
	CString  m_szTCFunctionsLogFileName;
	BOOL  m_bTCFunctionChecks[3];
	BOOL  m_bTCFunctionsLogReset;
private:
	CCriticalSection  *m_pCriticalSection;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesTCStackDialog)
public:
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_TCSTACK_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL SetInfo(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL GetInfo(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;

	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem);
	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem, LPCTSTR pszStatus, LPCTSTR pszResult);
	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem, CONST CTCPacket *pTCPacket, BOOL &bLogging);
	VOID UpdateTCStack(BOOL bRunning, BOOL bSuspended);
	VOID UpdateTCStack(BOOL bAll = TRUE);
	VOID ResetTCStack();

	VOID UpdateTCStackItem(INT nIndex);

	BOOL IsTCStackReleaseWaitModeEnabled() CONST;
	CTimeSpan GetTCStackReleaseWaitInterval() CONST;
	BOOL IsTCStackPreexecutionVerificationEnabled() CONST;
	BOOL IsTCStackExecutionVerificationEnabled() CONST;

	class CTCProcedurePropertiesThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

public:
	VOID AdjustToPrivileges();

private:
	BOOL LogTCStackItem(LPCTSTR pszSequence, LPCTSTR pszFunction, CONST CTCUnit *pTCUnit, CONST CTimeTag &tReleaseTime);
	CString EnumTCStackItemArguments(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn);

	INT CalcColumnWidth(LPCTSTR pszColumn);

	BOOL Lock();
	BOOL Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTCStackDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesTCStackDialog)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnGetDefID(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnReleaseWaitMode();
	afx_msg void OnNoPreexecutionChecks();
	afx_msg void OnNoExecutionChecks();
	afx_msg void OnSuspendTCStack();
	afx_msg void OnResumeTCStack();
	afx_msg void OnRemoveCommand();
	afx_msg void OnRemoveAllCommands();
	afx_msg void OnUseLogFile();
	afx_msg void OnBrowseLogFile();
	afx_msg void OnResetLogFile();
	afx_msg void OnEditchangeLogFileName();
	afx_msg void OnSpinchangeReleaseWaitInterval();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesBranchDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_BRANCH_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_BRANCH_INVARIANTCONDITION_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_BRANCH_INVARIANTCONDITION   1003
#define IDC_TCPROCEDURE_PROPERTIES_BRANCH_TESTEXPRESSION_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_BRANCH_TESTEXPRESSION   1005
#define IDC_TCPROCEDURE_PROPERTIES_BRANCH_HELP   1006

class CTCProcedurePropertiesBranchDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesBranchDialog)

	// Construction
public:
	CTCProcedurePropertiesBranchDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentBranchItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesBranchDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_BRANCH_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentBranchItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesBranchDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesBranchDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeInvariantCondition();
	afx_msg void OnEditchangeTestExpression();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesSwitchDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_INVARIANTCONDITION_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_INVARIANTCONDITION   1003
#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_BRANCHCOUNT_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_BRANCHCOUNT   1005
#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_BRANCHINFORMATION   1006
#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_BRANCHINFORMATION_NUMBER_STATIC   1007
#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_BRANCHINFORMATION_NUMBER   1008
#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_BRANCHINFORMATION_TESTEXPRESSION_STATIC   1009
#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_BRANCHINFORMATION_TESTEXPRESSION   1010
#define IDC_TCPROCEDURE_PROPERTIES_SWITCH_HELP   1011

// Specify the telecommand procedure switch dialog related identifiers
#define TCPROCEDUREPROPERTIESSWITCHSTEP_BRANCHCOUNT_MINIMUMNUMBER   0
#define TCPROCEDUREPROPERTIESSWITCHSTEP_BRANCHCOUNT_MAXIMUMNUMBER   256
#define TCPROCEDUREPROPERTIESSWITCHSTEP_BRANCHCOUNT_DEFAULTNUMBER   3

class CTCProcedurePropertiesSwitchDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSwitchDialog)

	// Construction
public:
	CTCProcedurePropertiesSwitchDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentSwitchItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesSwitchDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_SWITCH_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentSwitchItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSwitchDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesSwitchDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeInvariantCondition();
	afx_msg void OnEditchangeTextExpression();
	afx_msg void OnSelchangeBranchNumber();
	afx_msg void OnSpinchangeBranchCount();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesForLoopDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_FORLOOP_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_FORLOOP_INVARIANTCONDITION_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_FORLOOP_INVARIANTCONDITION   1003
#define IDC_TCPROCEDURE_PROPERTIES_FORLOOP_ITERATIONS_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_FORLOOP_ITERATIONS   1005
#define IDC_TCPROCEDURE_PROPERTIES_FORLOOP_HELP   1006

// Specify the telecommand procedure for-loop dialog related identifiers
#define TCPROCEDUREPROPERTIESFORLOOPSTEP_INTERATIONCOUNT_MINIMUMNUMBER   0
#define TCPROCEDUREPROPERTIESFORLOOPSTEP_INTERATIONCOUNT_MAXIMUMNUMBER   INT_MAX
#define TCPROCEDUREPROPERTIESFORLOOPSTEP_INTERATIONCOUNT_DEFAULTNUMBER   1

class CTCProcedurePropertiesForLoopDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesForLoopDialog)

	// Construction
public:
	CTCProcedurePropertiesForLoopDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentForLoopItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesForLoopDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_FORLOOP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentForLoopItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesForLoopDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesForLoopDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeInvariantCondition();
	afx_msg void OnSpinchangeIterations();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesWhileLoopDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_WHILELOOP_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_WHILELOOP_INVARIANTCONDITION_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_WHILELOOP_INVARIANTCONDITION   1003
#define IDC_TCPROCEDURE_PROPERTIES_WHILELOOP_TESTEXPRESSION_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_WHILELOOP_TESTEXPRESSION   1005
#define IDC_TCPROCEDURE_PROPERTIES_WHILELOOP_HELP   1006

class CTCProcedurePropertiesWhileLoopDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesWhileLoopDialog)

	// Construction
public:
	CTCProcedurePropertiesWhileLoopDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentWhileLoopItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesWhileLoopDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_WHILELOOP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentWhileLoopItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesWhileLoopDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesWhileLoopDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeInvariantCondition();
	afx_msg void OnEditchangeTestExpression();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesDoLoopDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_DOLOOP_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_DOLOOP_INVARIANTCONDITION_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_DOLOOP_INVARIANTCONDITION   1003
#define IDC_TCPROCEDURE_PROPERTIES_DOLOOP_TESTEXPRESSION_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_DOLOOP_TESTEXPRESSION   1005
#define IDC_TCPROCEDURE_PROPERTIES_DOLOOP_HELP   1006

class CTCProcedurePropertiesDoLoopDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesDoLoopDialog)

	// Construction
public:
	CTCProcedurePropertiesDoLoopDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentDoLoopItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesDoLoopDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_DOLOOP_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentDoLoopItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesDoLoopDialog)
public:
	virtual BOOL IsModified() CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesDoLoopDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeInvariantCondition();
	afx_msg void OnEditchangeTestExpression();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesGotoDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_GOTO_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_GOTO_LABEL_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_GOTO_LABEL   1003
#define IDC_TCPROCEDURE_PROPERTIES_GOTO_HELP   1004

class CTCProcedurePropertiesGotoDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesGotoDialog)

	// Construction
public:
	CTCProcedurePropertiesGotoDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentGotoItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesGotoDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_GOTO_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentGotoItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesGotoDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesGotoDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeLabelText();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesLabelDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_LABEL_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_LABEL_TEXT_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_LABEL_TEXT   1003
#define IDC_TCPROCEDURE_PROPERTIES_LABEL_HELP   1004

class CTCProcedurePropertiesLabelDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesLabelDialog)

	// Construction
public:
	CTCProcedurePropertiesLabelDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentLabelItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesLabelDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_LABEL_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentLabelItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesLabelDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesLabelDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeLabelText();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesParametersCalibrationPage dialog

#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCProcedurePropertiesParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesParametersCalibrationPage)

	// Construction
public:
	CTCProcedurePropertiesParametersCalibrationPage();

	// Attributes
private:
	UINT  m_nCalTableType;
	CStringArray  m_szCalTableIDs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesParametersCalibrationPage)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_PARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);
	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesParametersFolderTabCtrl window

class CTCProcedurePropertiesParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCProcedurePropertiesParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesParametersFolder

class CTCProcedurePropertiesParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesParametersFolder)

	// Construction
public:
	CTCProcedurePropertiesParametersFolder();

	// Attributes
private:
	CTCProcedurePropertiesParametersFolderTabCtrl  m_wndTabCtrl;
	CTCProcedurePropertiesParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter = NULL);

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesParametersDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_ITEM_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_ITEM   1003
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_FOLDER   1004
#define IDC_TCPROCEDURE_PROPERTIES_PARAMETERS_HELP   1005

class CTCProcedurePropertiesParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesParametersDialog)

	// Construction
public:
	CTCProcedurePropertiesParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szParameter;
private:
	CTCProcedurePropertiesParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesParametersDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_PARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, LPCTSTR pszParameter, CString &szValue);

	VOID SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesSetParametersDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesParametersDialog)
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
// CTCProcedurePropertiesSetArgumentsDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_AUTHORIZATION   1004
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_EXPRESSION_STATIC   1005
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_EXPRESSION   1006
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_ADD   1007
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_REMOVE   1008
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_REMOVEALL   1009
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_LIST_STATIC   1010
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_LIST   1011
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_REMARK   1012
#define IDC_TCPROCEDURE_PROPERTIES_SETARGUMENTS_HELP   1013

class CTCProcedurePropertiesSetArgumentsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSetArgumentsDialog)

	// Construction
public:
	CTCProcedurePropertiesSetArgumentsDialog();   // standard constructor

	// Attributes
private:
	CDatabaseTCProcedureArguments  m_pDatabaseTCProcedureArguments;
	CTCProcedureDocumentSetArgumentsItem  *m_pStep[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesSetArgumentsDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_SETARGUMENTS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentSetArgumentsItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumArguments();

	VOID ShowProperties();
	VOID ShowArgumentDetails();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSetArgumentsDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesSetArgumentsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnAuthorization();
	afx_msg void OnSelchangeName();
	afx_msg void OnEditchangeExpression();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesSetVariablesDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_AUTHORIZATION   1004
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_EXPRESSION_STATIC   1005
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_EXPRESSION   1006
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_ADD   1007
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_REMOVE   1008
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_REMOVEALL   1009
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_LIST_STATIC   1010
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_LIST   1011
#define IDC_TCPROCEDURE_PROPERTIES_SETVARIABLES_HELP   1012

class CTCProcedurePropertiesSetVariablesDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSetVariablesDialog)

	// Construction
public:
	CTCProcedurePropertiesSetVariablesDialog();   // standard constructor

	// Attributes
private:
	CDatabaseTCProcedureVariables  m_pDatabaseTCProcedureVariables;
	CTCProcedureDocumentSetVariablesItem  *m_pStep[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesSetVariablesDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_SETVARIABLES_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentSetVariablesItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumVariables();

	VOID ShowProperties();
	VOID ShowVariableDetails();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSetVariablesDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesSetVariablesDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnAuthorization();
	afx_msg void OnSelchangeName();
	afx_msg void OnEditchangeExpression();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesSetParametersDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_TAG_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_TAG   1003
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_AUTHORIZATION   1004
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_EXPRESSION_STATIC   1005
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_EXPRESSION   1006
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_SAMPLE_STATIC   1007
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_SAMPLE   1008
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_ADD   1009
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_REMOVE   1010
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_REMOVEALL   1011
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_LIST_STATIC   1012
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_LIST   1013
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_REMARK   1014
#define IDC_TCPROCEDURE_PROPERTIES_SETPARAMETERS_HELP   1015

// Specify the telecommand procedure set-parameters dialog related identifiers
#define TCPROCEDUREPROPERTIESSETPARAMETERSSTEP_MINIMUMSAMPLE   0
#define TCPROCEDUREPROPERTIESSETPARAMETERSSTEP_MAXIMUMSAMPLE   100
#define TCPROCEDUREPROPERTIESSETPARAMETERSSTEP_DEFAULTSAMPLE   0

class CTCProcedurePropertiesSetParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSetParametersDialog)

	// Construction
public:
	CTCProcedurePropertiesSetParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szExpressions;
	CDatabaseTCParameters  m_pDatabaseTCParameters;
	CTCProcedureDocumentSetParametersItem  *m_pStep[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesSetParametersDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_SETPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentSetParametersItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumParameters();

	VOID ShowProperties();
	VOID ShowParameterDetails();

	CString CollectParameterExpression(INT nSample, LPCTSTR pszExpressions, LPCTSTR pszExpression) CONST;
	CString ExtractParameterExpression(INT nSample, LPCTSTR pszExpressions) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSetParametersDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesSetParametersDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	afx_msg void OnRemoveAll();
	afx_msg void OnAuthorization();
	afx_msg void OnSelchangeTag();
	afx_msg void OnEditchangeExpression();
	afx_msg void OnSpinchangeSample();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesSetSynchronizationObjectDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_SETSYNCOBJECT_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_SETSYNCOBJECT_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_SETSYNCOBJECT_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_SETSYNCOBJECT_HELP   1004

class CTCProcedurePropertiesSetSynchronizationObjectDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSetSynchronizationObjectDialog)

	// Construction
public:
	CTCProcedurePropertiesSetSynchronizationObjectDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szObjects;
	CTCProcedureDocumentSetSynchronizationObjectItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesSetSynchronizationObjectDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_SETSYNCOBJECT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CStringArray &szObjects, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentSetSynchronizationObjectItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumSynchronizationObjects();

	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSetSynchronizationObjectDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesSetSynchronizationObjectDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnEditchangeSynchronizationObjectName();
	afx_msg void OnSelchangeSynchronizationObjectName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesInjectAlertDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_CATEGORY_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_CATEGORY   1003
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_TYPE_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_TYPE   1005
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_SUBTYPE_STATIC   1006
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_SUBTYPE   1007
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_MESSAGE_STATIC   1008
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_MESSAGE   1009
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_COMMENTS_STATIC   1010
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_COMMENTS   1011
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_AUDITION_STATIC   1012
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_AUDITION   1013
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_NOTIFICATION_STATIC   1014
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_NOTIFICATION   1015
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_COLOR_STATIC   1016
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_COLOR   1017
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_BLINKING   1018
#define IDC_TCPROCEDURE_PROPERTIES_INJECTALERT_HELP   1019

class CTCProcedurePropertiesInjectAlertDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesInjectAlertDialog)

	// Construction
public:
	CTCProcedurePropertiesInjectAlertDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentInjectAlertItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesInjectAlertDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_INJECTALERT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentInjectAlertItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumCategories();
	BOOL EnumTypes();

	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesInjectAlertDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesInjectAlertDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBlinking();
	afx_msg void OnEditchangeSubtype();
	afx_msg void OnEditchangeMessage();
	afx_msg void OnEditchangeComments();
	afx_msg void OnEditchangeAudition();
	afx_msg void OnEditchangeNotification();
	afx_msg void OnEditchangeType();
	afx_msg void OnSelchangeCategory();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeColor();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesCallProcedureDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_AUTHORIZATION   1004
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_DESCRIPTION_STATIC   1005
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_DESCRIPTION   1006
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_INVARIANTCONDITION_STATIC   1007
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_INVARIANTCONDITION   1008
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_ARGUMENTS   1009
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_ARGUMENTS_LIST   1010
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_ARGUMENTS_VALUE_STATIC   1011
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_ARGUMENTS_VALUE   1012
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_ARGUMENTS_SETVALUE   1013
#define IDC_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_HELP   1014

class CTCProcedurePropertiesCallProcedureDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesCallProcedureDialog)

	// Construction
public:
	CTCProcedurePropertiesCallProcedureDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentCallProcedureItem  *m_pStep[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesCallProcedureDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_CALLPROCEDURE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentCallProcedureItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumProcedures();

	VOID ShowProperties();
	VOID ShowArguments();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesCallProcedureDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesCallProcedureDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAuthorization();
	afx_msg void OnSetArgumentValue();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeInvariantCondition();
	afx_msg void OnEditchangeArgumentValue();
	afx_msg void OnSelchangeProcedureName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesStartProcedureDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_AUTHORIZATION   1004
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_DESCRIPTION_STATIC   1005
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_DESCRIPTION   1006
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_INVARIANTCONDITION_STATIC   1007
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_INVARIANTCONDITION   1008
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_ARGUMENTS   1009
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_ARGUMENTS_LIST   1010
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_ARGUMENTS_VALUE_STATIC   1011
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_ARGUMENTS_VALUE   1012
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_ARGUMENTS_SETVALUE   1013
#define IDC_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_HELP   1014

class CTCProcedurePropertiesStartProcedureDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesStartProcedureDialog)

	// Construction
public:
	CTCProcedurePropertiesStartProcedureDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentStartProcedureItem  *m_pStep[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesStartProcedureDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_STARTPROCEDURE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentStartProcedureItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumProcedures();

	VOID ShowProperties();
	VOID ShowArguments();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesStartProcedureDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesStartProcedureDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAuthorization();
	afx_msg void OnSetArgumentValue();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangeInvariantCondition();
	afx_msg void OnEditchangeArgumentValue();
	afx_msg void OnSelchangeProcedureName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesControlProcedureDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_CONTROLPROCEDURE_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_CONTROLPROCEDURE_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_CONTROLPROCEDURE_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_CONTROLPROCEDURE_STATE_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_CONTROLPROCEDURE_STATE   1005
#define IDC_TCPROCEDURE_PROPERTIES_CONTROLPROCEDURE_HELP   1006

class CTCProcedurePropertiesControlProcedureDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesControlProcedureDialog)

	// Construction
public:
	CTCProcedurePropertiesControlProcedureDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentControlProcedureItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesControlProcedureDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_CONTROLPROCEDURE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentControlProcedureItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumProcedures();
	BOOL EnumActionStates();

	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesControlProcedureDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesControlProcedureDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeState();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesControlThreadDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_CONTROLTHREAD_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_CONTROLTHREAD_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_CONTROLTHREAD_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_CONTROLTHREAD_STATE_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_CONTROLTHREAD_STATE   1005
#define IDC_TCPROCEDURE_PROPERTIES_CONTROLTHREAD_HELP   1006

class CTCProcedurePropertiesControlThreadDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesControlThreadDialog)

	// Construction
public:
	CTCProcedurePropertiesControlThreadDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentControlThreadItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesControlThreadDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_CONTROLTHREAD_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentControlThreadItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumThreads();
	BOOL EnumActionStates();

	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesControlThreadDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesControlThreadDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeName();
	afx_msg void OnSelchangeState();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesWaitTimeIntervalDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_WAITTIMEINTERVAL_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_WAITTIMEINTERVAL_NUMBER_USE   1002
#define IDC_TCPROCEDURE_PROPERTIES_WAITTIMEINTERVAL_NUMBER   1003
#define IDC_TCPROCEDURE_PROPERTIES_WAITTIMEINTERVAL_NUMBER_MILLISECONDS_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_WAITTIMEINTERVAL_ABSOLUTE_USE   1005
#define IDC_TCPROCEDURE_PROPERTIES_WAITTIMEINTERVAL_ABSOLUTE   1006
#define IDC_TCPROCEDURE_PROPERTIES_WAITTIMEINTERVAL_HELP   1007

// Specify the telecommand procedure wait-time interval dialog related identifiers
#define TCPROCEDUREPROPERTIESWAITTIMEINTERVALSTEP_MINIMUMINTERVAL   0
#define TCPROCEDUREPROPERTIESWAITTIMEINTERVALSTEP_MAXIMUMINTERVAL   (1000*SECONDSPERDAY)
#define TCPROCEDUREPROPERTIESWAITTIMEINTERVALSTEP_DEFAULTINTERVAL   1000

class CTCProcedurePropertiesWaitTimeIntervalDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesWaitTimeIntervalDialog)

	// Construction
public:
	CTCProcedurePropertiesWaitTimeIntervalDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentWaitTimeIntervalItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesWaitTimeIntervalDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_WAITTIMEINTERVAL_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentWaitTimeIntervalItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesWaitTimeIntervalDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesWaitTimeIntervalDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnUseInterval();
	afx_msg void OnUseAbsoluteTime();
	afx_msg void OnSpinchangeWaitInterval();
	afx_msg void OnSpinchangeAbsoluteTime();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesWaitSynchronizationObjectDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_WAITSYNCOBJECT_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_WAITSYNCOBJECT_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_WAITSYNCOBJECT_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_WAITSYNCOBJECT_INTERVAL   1004
#define IDC_TCPROCEDURE_PROPERTIES_WAITSYNCOBJECT_INTERVAL_NUMBER   1005
#define IDC_TCPROCEDURE_PROPERTIES_WAITSYNCOBJECT_INTERVAL_NUMBER_STATIC   1006
#define IDC_TCPROCEDURE_PROPERTIES_WAITSYNCOBJECT_HELP   1007

// Specify the telecommand procedure wait-synchronization object interval dialog related identifiers
#define TCPROCEDUREPROPERTIESWAITSYNCOBJECTSTEP_MINIMUMINTERVAL   0
#define TCPROCEDUREPROPERTIESWAITSYNCOBJECTSTEP_MAXIMUMINTERVAL   (1000*SECONDSPERMINUTE*MINUTESPERHOUR*HOURSPERDAY)
#define TCPROCEDUREPROPERTIESWAITSYNCOBJECTSTEP_DEFAULTINTERVAL   1000

class CTCProcedurePropertiesWaitSynchronizationObjectDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesWaitSynchronizationObjectDialog)

	// Construction
public:
	CTCProcedurePropertiesWaitSynchronizationObjectDialog();   // standard constructor

	// Attributes
private:
	CStringArray  m_szObjects;
	CTCProcedureDocumentWaitSynchronizationObjectItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesWaitSynchronizationObjectDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_WAITSYNCOBJECT_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CONST CStringArray &szObjects, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentWaitSynchronizationObjectItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumSynchronizationObjects();

	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesWaitSynchronizationObjectDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesWaitSynchronizationObjectDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTimeout();
	afx_msg void OnEditchangeSynchronizationObjectName();
	afx_msg void OnSelchangeSynchronizationObjectName();
	afx_msg void OnSpinchangeTimeout();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesSendTCFunctionParametersCalibrationPage dialog

#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME_STATIC   1001
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_NAME   1002
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID_STATIC   1003
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_ID   1004
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE_STATIC   1005
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_TYPE   1006
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS_STATIC  1007
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE_POINTS   1008

class CTCProcedurePropertiesSendTCFunctionParametersCalibrationPage : public CLocalePropertyPage
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSendTCFunctionParametersCalibrationPage)

	// Construction
public:
	CTCProcedurePropertiesSendTCFunctionParametersCalibrationPage();

	// Attributes
private:
	UINT  m_nCalTableType;
	CStringArray  m_szCalTableIDs;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesSendTCFunctionParametersCalibrationPage)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_CALIBRATIONPAGE };
	// NOTE - ClassWizard will add data members here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

	// Operations
public:
	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter);
	VOID ShowCalibrationInfo();

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesSendTCFunctionParametersFolder *GetParent() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSendTCFunctionParametersCalibrationPage)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesSendTCFunctionParametersCalibrationPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeName();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesSendTCFunctionParametersFolderTabCtrl window

class CTCProcedurePropertiesSendTCFunctionParametersFolderTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSendTCFunctionParametersFolderTabCtrl)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	class CTCProcedurePropertiesSendTCFunctionParametersFolder *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSendTCFunctionParametersFolderTabCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesSendTCFunctionParametersFolderTabCtrl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesSendTCFunctionParametersFolder

class CTCProcedurePropertiesSendTCFunctionParametersFolder : public CLocalePropertySheetDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSendTCFunctionParametersFolder)

	// Construction
public:
	CTCProcedurePropertiesSendTCFunctionParametersFolder();

	// Attributes
private:
	CTCProcedurePropertiesSendTCFunctionParametersFolderTabCtrl  m_wndTabCtrl;
	CTCProcedurePropertiesSendTCFunctionParametersCalibrationPage  m_pageCalibration;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	VOID ShowParameterInfo(CONST CDatabaseTCParameter *pDatabaseTCParameter = NULL);

	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CTCProcedurePropertiesSendTCFunctionParametersDialog *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSendTCFunctionParametersFolder)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesSendTCFunctionParametersFolder)
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesSendTCFunctionParametersDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_ITEM_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_ITEM   1003
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_FOLDER   1004
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_HELP   1005

class CTCProcedurePropertiesSendTCFunctionParametersDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSendTCFunctionParametersDialog)

	// Construction
public:
	CTCProcedurePropertiesSendTCFunctionParametersDialog();   // standard constructor

	// Attributes
private:
	CString  m_szX;
	CString  m_szY;
	CString  m_szFunction;
	CString  m_szParameter;
private:
	CTCProcedurePropertiesSendTCFunctionParametersFolder  m_wndFolderCtrl;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesSendTCFunctionParametersDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, LPCTSTR pszFunction, LPCTSTR pszParameter, CString &szValue);

	VOID SetSelectedCalibrationPoint(LPCTSTR pszX, LPCTSTR pszY);
	BOOL GetSelectedCalibrationPoint(CString &szX, CString &szY) CONST;

	class CDisplayDialog *GetParent() CONST;

private:
	BOOL EnumParameters();

	VOID ShowParameterInfo();

	CRect CalcFolderSize() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSendTCFunctionParametersDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesSendTCFunctionParametersDialog)
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
// CTCProcedurePropertiesSendTCFunctionParameterSetsDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERSETS_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERSETS_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERSETS_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERSETS_CONTENTS_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERSETS_CONTENTS   1005
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERSETS_HELP   1006

class CTCProcedurePropertiesSendTCFunctionParameterSetsDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSendTCFunctionParameterSetsDialog)

	// Construction
public:
	CTCProcedurePropertiesSendTCFunctionParameterSetsDialog();   // standard constructor

	// Attributes
private:
	CDatabaseTCFunction  m_cDatabaseTCFunction;
	CStringArray  m_szParameterSets;
	CString  m_szParameterSet;
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesSendTCFunctionParameterSetsDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_SENDTCFUNCTIONPARAMETERSETS_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST CDatabaseTCFunction *pDatabaseTCFunction, CString &szParameterSet);

private:
	BOOL EnumParameterSets();

	VOID ShowParameterSetContents();

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSendTCFunctionParameterSetsDialog)
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesSendTCFunctionParameterSetsDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeSet();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesSendTCFunctionDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_DESCRIPTION_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_DESCRIPTION   1005
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS   1006
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_RELEASEATTIME   1007
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_RELEASETIME   1008
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_RELEASEATOFFSET   1009
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_RELEASEOFFSET   1010
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_EXECUTEATTIME   1011
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_EXECUTIONTIME   1012
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_EXECUTEATOFFSET   1013
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_EXECUTIONOFFSET   1014
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_TWOSTEPS_STATIC   1015
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_FIRSTSTEP   1016
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_SECONDSTEP   1017
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_IGNOREPREEXEVERIFICATION   1018
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_PREEXEVERIFICATION   1019
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_IGNOREEXEVERIFICATION   1020
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_EXEVERIFICATION   1021
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_EXEVERIFICATION_TIMEWINDOW_STATIC   1022
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_EXEVERIFICATION_TIMEWINDOW   1023
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_EXEVERIFICATION_TIMEWINDOW_SECONDS   1024
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_CRITICAL   1025
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_OPTIONS_AUTHORIZATION   1026
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_ACKFLAG_STATIC   1027
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_ACKFLAG_ACCEPTANCE   1028
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_ACKFLAG_START   1029
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_ACKFLAG_PROGRESS   1030
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_ACKFLAG_COMPLETION   1031
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_PARAMETERS   1032
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_PARAMETERS_LIST   1033
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_PARAMETERS_REMARK   1034
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_PARAMETERS_NOEXTRAPOLATION   1035
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_PARAMETERS_SHOWALL   1036
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_PARAMETERS_VALUE_STATIC   1037
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_PARAMETERS_VALUE   1038
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_PARAMETERS_SETVALUE   1039
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_PARAMETERS_LOADVALUES   1040
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_HELP   1041

// Specify the telecommand procedure send-function dialog related identifiers
#define TCPROCEDUREPROPERTIESSENDTCFUNCTIONSTEP_MINIMUMRELEASETIMEOFFSET   0
#define TCPROCEDUREPROPERTIESSENDTCFUNCTIONSTEP_MAXIMUMRELEASETIMEOFFSET   (SECONDSPERDAY-1)
#define TCPROCEDUREPROPERTIESSENDTCFUNCTIONSTEP_DEFAULTRELEASETIMEOFFSET   (SECONDSPERMINUTE*MINUTESPERHOUR)
#define TCPROCEDUREPROPERTIESSENDTCFUNCTIONSTEP_MINIMUMEXECUTIONTIMEOFFSET   0
#define TCPROCEDUREPROPERTIESSENDTCFUNCTIONSTEP_MAXIMUMEXECUTIONTIMEOFFSET   (365*SECONDSPERDAY)
#define TCPROCEDUREPROPERTIESSENDTCFUNCTIONSTEP_DEFAULTEXECUTIONTIMEOFFSET   0
#define TCPROCEDUREPROPERTIESSENDTCFUNCTIONSTEP_MINIMUMTIMEWINDOW   1
#define TCPROCEDUREPROPERTIESSENDTCFUNCTIONSTEP_MAXIMUMTIMEWINDOW   (SECONDSPERMINUTE*MINUTESPERHOUR)
#define TCPROCEDUREPROPERTIESSENDTCFUNCTIONSTEP_DEFAULTTIMEWINDOW   SECONDSPERMINUTE

class CTCProcedurePropertiesSendTCFunctionDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSendTCFunctionDialog)

	// Construction
public:
	CTCProcedurePropertiesSendTCFunctionDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentSendTCFunctionItem  *m_pStep[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesSendTCFunctionDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_SENDTCFUNCTION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentSendTCFunctionItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTCFunctions();

	VOID ShowProperties();
	VOID ShowParameters();

	VOID EvaluateParameters();

	BOOL CheckTCExecutionType(ULONGLONG nAttributes) CONST;
	BOOL CheckTCExecutionTime(CONST CTimeTag &tExecutionTime = 0) CONST;
	BOOL CheckTCParameterOolStatus(CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement, BYTE &nStatus) CONST;
	BOOL CheckTCParameterOolStatus(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BYTE &nStatus) CONST;
	BOOL CheckTCVerificationStage(UINT nStage) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSendTCFunctionDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesSendTCFunctionDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnReleaseAtOffset();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnExecuteAtOffset();
	afx_msg void OnSendAsFirstStep();
	afx_msg void OnSendAsSecondStep();
	afx_msg void OnIgnorePreexecutionVerification();
	afx_msg void OnIgnoreExecutionVerification();
	afx_msg void OnCritical();
	afx_msg void OnAuthorization();
	afx_msg void OnAcknowledgeAtAcceptance();
	afx_msg void OnAcknowledgeAtStart();
	afx_msg void OnAcknowledgeAtProgress();
	afx_msg void OnAcknowledgeAtCompletion();
	afx_msg void OnNoExtrapolation();
	afx_msg void OnShowAll();
	afx_msg void OnSetParameterValue();
	afx_msg void OnLoadParameterValues();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangePreexecutionCondition();
	afx_msg void OnEditchangeExecutionCondition();
	afx_msg void OnEditchangeParameterValue();
	afx_msg void OnSelchangeFunction();
	afx_msg void OnSpinchangeReleaseTime();
	afx_msg void OnSpinchangeReleaseOffset();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg void OnSpinchangeExecutionOffset();
	afx_msg void OnSpinchangeTimeWindow();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesSendTCSequenceDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_NAME_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_NAME   1003
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_ENTRY_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_ENTRY   1005
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_DESCRIPTION_STATIC   1006
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_DESCRIPTION   1007
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS   1008
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_RELEASEATTIME   1009
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_RELEASETIME   1010
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_RELEASEATOFFSET   1011
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_RELEASEOFFSET   1012
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_EXECUTEATTIME   1013
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_EXECUTIONTIME   1014
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_EXECUTEATOFFSET   1015
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_EXECUTIONOFFSET   1016
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_TWOSTEPS_STATIC   1017
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_FIRSTSTEP   1018
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_SECONDSTEP   1019
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_RELEASEASGROUP   1020
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_IGNOREPREEXEVERIFICATION   1021
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_PREEXEVERIFICATION   1022
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_IGNOREEXEVERIFICATION   1023
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_EXEVERIFICATION   1024
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_EXEVERIFICATION_TIMEWINDOW_STATIC   1025
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_EXEVERIFICATION_TIMEWINDOW   1026
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_EXEVERIFICATION_TIMEWINDOW_SECONDS   1027
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_CRITICAL   1028
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_OPTIONS_AUTHORIZATION   1029
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_ACKFLAG_STATIC   1030
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_ACKFLAG_ACCEPTANCE   1031
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_ACKFLAG_START   1032
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_ACKFLAG_PROGRESS   1033
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_ACKFLAG_COMPLETION   1034
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_PARAMETERS   1035
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_PARAMETERS_SHOWFORMALLIST   1036
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_PARAMETERS_LIST   1037
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_PARAMETERS_REMARK   1038
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_PARAMETERS_NOEXTRAPOLATION   1039
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_PARAMETERS_SHOWALL   1040
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_PARAMETERS_VALUE_STATIC   1041
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_PARAMETERS_VALUE   1042
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_PARAMETERS_SETVALUE   1043
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_PARAMETERS_LOADVALUES   1044
#define IDC_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_HELP   1045

// Specify the telecommand procedure send-sequence dialog related identifiers
#define TCPROCEDUREPROPERTIESSENDTCSEQUENCESTEP_MINIMUMRELEASETIMEOFFSET   0
#define TCPROCEDUREPROPERTIESSENDTCSEQUENCESTEP_MAXIMUMRELEASETIMEOFFSET   (SECONDSPERDAY-1)
#define TCPROCEDUREPROPERTIESSENDTCSEQUENCESTEP_DEFAULTRELEASETIMEOFFSET   (SECONDSPERMINUTE*MINUTESPERHOUR)
#define TCPROCEDUREPROPERTIESSENDTCSEQUENCESTEP_MINIMUMEXECUTIONTIMEOFFSET   -(365*SECONDSPERDAY)
#define TCPROCEDUREPROPERTIESSENDTCSEQUENCESTEP_MAXIMUMEXECUTIONTIMEOFFSET   (365*SECONDSPERDAY)
#define TCPROCEDUREPROPERTIESSENDTCSEQUENCESTEP_DEFAULTEXECUTIONTIMEOFFSET   0
#define TCPROCEDUREPROPERTIESSENDTCSEQUENCESTEP_MINIMUMTIMEWINDOW   1
#define TCPROCEDUREPROPERTIESSENDTCSEQUENCESTEP_MAXIMUMTIMEWINDOW   (SECONDSPERMINUTE*MINUTESPERHOUR)
#define TCPROCEDUREPROPERTIESSENDTCSEQUENCESTEP_DEFAULTTIMEWINDOW   SECONDSPERMINUTE

class CTCProcedurePropertiesSendTCSequenceDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesSendTCSequenceDialog)

	// Construction
public:
	CTCProcedurePropertiesSendTCSequenceDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentSendTCSequenceItem  *m_pStep[2];
private:
	CStringArray  m_szColumns;

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesSendTCSequenceDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_SENDTCSEQUENCE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentSendTCSequenceItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTCSequences();
	BOOL EnumTCSequenceEntries();

	VOID ShowProperties();
	VOID ShowEntryProperties();
	VOID ShowFormalParameters();
	VOID ShowParameters();

	VOID EvaluateParameters();

	BOOL CheckTCExecutionType(ULONGLONG nAttributes) CONST;
	BOOL CheckTCExecutionTime(CONST CTCProcedureDocumentSendTCFunctionItem *pEntry, CONST CTimeTag &tExecutionTime = 0) CONST;
	BOOL CheckTCParameterOolStatus(CONST CDatabaseTCParameter *pDatabaseTCParameter, BYTE &nStatus) CONST;
	BOOL CheckTCParameterOolStatus(CONST CDatabaseTCFunctionElement *pDatabaseTCFunctionElement, BYTE &nStatus) CONST;
	BOOL CheckTCParameterOolStatus(CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BYTE &nStatus) CONST;
	BOOL CheckTCVerificationStage(UINT nStage) CONST;

	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesSendTCSequenceDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesSendTCSequenceDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnReleaseAtTime();
	afx_msg void OnReleaseAtOffset();
	afx_msg void OnExecuteAtTime();
	afx_msg void OnExecuteAtOffset();
	afx_msg void OnSendAsFirstStep();
	afx_msg void OnSendAsSecondStep();
	afx_msg void OnReleaseAsGroup();
	afx_msg void OnIgnorePreexecutionVerification();
	afx_msg void OnIgnoreExecutionVerification();
	afx_msg void OnCritical();
	afx_msg void OnAuthorization();
	afx_msg void OnAcknowledgeAtAcceptance();
	afx_msg void OnAcknowledgeAtStart();
	afx_msg void OnAcknowledgeAtProgress();
	afx_msg void OnAcknowledgeAtCompletion();
	afx_msg void OnShowFormalParameters();
	afx_msg void OnNoExtrapolation();
	afx_msg void OnShowAll();
	afx_msg void OnSetParameterValue();
	afx_msg void OnLoadParameterValues();
	afx_msg void OnEditchangeDescription();
	afx_msg void OnEditchangePreexecutionCondition();
	afx_msg void OnEditchangeExecutionCondition();
	afx_msg void OnEditchangeParameterValue();
	afx_msg void OnSelchangeSequence();
	afx_msg void OnSelchangeSequenceEntry();
	afx_msg void OnSpinchangeReleaseTime();
	afx_msg void OnSpinchangeReleaseOffset();
	afx_msg void OnSpinchangeExecutionTime();
	afx_msg void OnSpinchangeExecutionOffset();
	afx_msg void OnSpinchangeTimeWindow();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesLogMessageDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_LOGMESSAGE_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_LOGMESSAGE_MESSAGE_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_LOGMESSAGE_MESSAGE   1003
#define IDC_TCPROCEDURE_PROPERTIES_LOGMESSAGE_FILENAME_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_LOGMESSAGE_FILENAME   1005
#define IDC_TCPROCEDURE_PROPERTIES_LOGMESSAGE_FILENAME_BROWSE   1006
#define IDC_TCPROCEDURE_PROPERTIES_LOGMESSAGE_PLAINTEXT   1007
#define IDC_TCPROCEDURE_PROPERTIES_LOGMESSAGE_UNICODE   1008
#define IDC_TCPROCEDURE_PROPERTIES_LOGMESSAGE_RESET   1009
#define IDC_TCPROCEDURE_PROPERTIES_LOGMESSAGE_HELP   1010

class CTCProcedurePropertiesLogMessageDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesLogMessageDialog)

	// Construction
public:
	CTCProcedurePropertiesLogMessageDialog();   // standard constructor

	// Attributes
private:
	CTCProcedureDocumentLogMessageItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesLogMessageDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_LOGMESSAGE_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentLogMessageItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	VOID ShowProperties();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesLogMessageDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesLogMessageDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPlainText();
	afx_msg void OnUnicode();
	afx_msg void OnReset();
	afx_msg void OnBrowseFileName();
	afx_msg void OnEditchangeMessage();
	afx_msg void OnEditchangeFileName();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesUserInteractionDialog dialog

#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_DETAILS   1001
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_TYPE_STATIC   1002
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_TYPE   1003
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_MESSAGE_STATIC   1004
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_MESSAGE   1005
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_AVAILABLEVARIABLES_STATIC   1006
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_AVAILABLEVARIABLES   1007
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_VARIABLE_ADD   1008
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_VARIABLE_REMOVE   1009
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_SELECTEDVARIABLES_STATIC   1010
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_SELECTEDVARIABLES   1011
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_VALUES   1012
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_VALUES_NUMBER_STATIC   1013
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_VALUES_NUMBER   1014
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_VALUES_NUMBER_ADD   1015
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_VALUES_NUMBER_REMOVE   1016
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_VALUES_NUMBER_REMOVEALL   1017
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_VALUES_NUMBERS   1018
#define IDC_TCPROCEDURE_PROPERTIES_USERINTERACTION_HELP   1019

class CTCProcedurePropertiesUserInteractionDialog : public CDisplayDialog
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesUserInteractionDialog)

	// Construction
public:
	CTCProcedurePropertiesUserInteractionDialog();   // standard constructor

	// Attributes
private:
	CDatabaseTCProcedureVariables  m_pDatabaseTCProcedureVariables;
	CTCProcedureDocumentUserInteractionItem  *m_pStep[2];

	// Dialog Data
	//{{AFX_DATA(CTCProcedurePropertiesUserInteractionDialog)
	enum { IDD = IDD_TCPROCEDURE_PROPERTIES_USERINTERACTION_DIALOG };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// Operations
public:
	INT Create(CWnd *pParentWnd, CTCProcedureDocumentItem *pStep);

	CTCProcedureDocumentUserInteractionItem *GetStep() CONST;

	class CTCProcedureFlowchartThreadView *GetParent() CONST;
	class CTCProcedureWnd *GetParentDisplay() CONST;

private:
	BOOL EnumTypes();
	BOOL EnumVariables();

	VOID ShowProperties();
	VOID ShowValues();

	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesUserInteractionDialog)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void DoDataExchange(CDataExchange *pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedurePropertiesUserInteractionDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAddVariable();
	afx_msg void OnRemoveVariable();
	afx_msg void OnAddVariableValue();
	afx_msg void OnRemoveVariableValue();
	afx_msg void OnRemoveAllVariableValues();
	afx_msg void OnEditchangeMessage();
	afx_msg void OnEditchangeVariableValue();
	afx_msg void OnSelchangeType();
	afx_msg void OnSelchangeAvailableVariable();
	afx_msg void OnSelchangeSelectedVariable();
	afx_msg void OnSelchangeVariableValue();
	afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
	afx_msg void OnHelp();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesThreadDocument

class CTCProcedurePropertiesThreadDocument : public CDocument
{
	DECLARE_DYNAMIC(CTCProcedurePropertiesThreadDocument)

	// Construction
public:
	CTCProcedurePropertiesThreadDocument();
	virtual ~CTCProcedurePropertiesThreadDocument();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesThreadView view

class CTCProcedurePropertiesThreadView : public CScrollView
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesThreadView)

	// Construction
public:
	CTCProcedurePropertiesThreadView();

	// Attributes
private:
	CLocaleDialog  *m_pDialog;
	CRect  m_rDialog[2];

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, UINT nDialogID, BOOL bVisible = TRUE);

	BOOL SetProperties(CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL GetProperties(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;

	BOOL SetBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(LPCTSTR pszThread, CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;

	VOID UpdateSteps(LPCTSTR pszThread, CONST CPtrArray &pSteps);
	VOID UpdateIdentifiers(CTMEnvironment *pTMEnvironment, CTCEnvironment *pTCEnvironment, CONST CStringArray &szIdentifiers, CONST CUIntArray &nIdentifierTypes, CONST CLongUIntArray &nIdentifierAttributes, CONST CPtrArray &pIdentifiers);
	VOID UpdateExecutionpoint(LPCTSTR pszThread, UINT nState = TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING, UINT nLine = 0);

	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem);
	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem, LPCTSTR pszStatus, LPCTSTR pszResult);
	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem, CONST CTCPacket *pTCPacket, BOOL &bLogging);
	VOID UpdateTCStack(BOOL bRunning, BOOL bSuspended);
	BOOL IsTCStackReleaseWaitModeEnabled() CONST;
	CTimeSpan GetTCStackReleaseWaitInterval() CONST;
	BOOL IsTCStackPreexecutionVerificationEnabled() CONST;
	BOOL IsTCStackExecutionVerificationEnabled() CONST;
	VOID ResetTCStack();

	BOOL GetPrintProperties(CRichEditCtrl **pEditCtrl) CONST;

	VOID DoFindCode();
	BOOL CanFindCode() CONST;
	VOID DoFindNextCode(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindNextCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindNextCode() CONST;
	VOID DoFindPreviousCode(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindPreviousCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindPreviousCode() CONST;
	VOID DoReplaceCode();
	BOOL CanReplaceCode() CONST;
	VOID DoGoToCode();
	BOOL DoGoToCode(LPCTSTR pszLine);
	BOOL CanGoToCode() CONST;

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoCutSel();
	BOOL CanCutSel() CONST;
	VOID DoCopySel();
	BOOL CanCopySel() CONST;
	VOID DoPasteSel();
	BOOL CanPasteSel() CONST;
	VOID DoDeleteSel();
	BOOL CanDeleteSel() CONST;

	VOID DoSelectAllCode();
	VOID UnSelectAllCode();
	BOOL CanSelectAllCode() CONST;

	BOOL HasCode() CONST;

	VOID ShowDialogs(BOOL bShow);
	BOOL HasDialogs() CONST;

	VOID UpdateLayout(BOOL bActivate);

	class CTCProcedurePropertiesTabCtrl *GetParent() CONST;

public:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesThreadView)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesThreadView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int OnMouseActivate(CWnd *pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesDocument

class CTCProcedurePropertiesDocument : public CDocument
{
	DECLARE_DYNAMIC(CTCProcedurePropertiesDocument)

	// Construction
public:
	CTCProcedurePropertiesDocument();
	virtual ~CTCProcedurePropertiesDocument();
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesTabCtrl

class CTCProcedurePropertiesTabCtrl : public CTabCtrl
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesTabCtrl)

	// Construction
public:
	CTCProcedurePropertiesTabCtrl();

	// Attributes
private:
	CPtrArray  m_pViews;
private:
	CSize  m_sizeTabMargins;
	CFont  m_cTabFont;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	BOOL SetProperties(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nFlags = TRUE);
	BOOL GetProperties(CDatabaseTCProcedure *pDatabaseTCProcedure, INT nFlags = TRUE) CONST;

	BOOL SetBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(LPCTSTR pszThread, CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;

	VOID UpdateSteps(LPCTSTR pszThread, CONST CPtrArray &pSteps);
	VOID UpdateIdentifiers(CTMEnvironment *pTMEnvironment, CTCEnvironment *pTCEnvironment, CONST CStringArray &szIdentifiers, CONST CUIntArray &nIdentifierTypes, CONST CLongUIntArray &nIdentifierAttributes, CONST CPtrArray &pIdentifiers);
	VOID UpdateExecutionpoint(LPCTSTR pszThread, UINT nState = TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING, UINT nLine = 0);

	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem);
	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem, LPCTSTR pszStatus, LPCTSTR pszResult);
	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem, CONST CTCPacket *pTCPacket, BOOL &bLogging);
	VOID UpdateTCStack(BOOL bRunning, BOOL bSuspended);
	BOOL IsTCStackReleaseWaitModeEnabled() CONST;
	CTimeSpan GetTCStackReleaseWaitInterval() CONST;
	BOOL IsTCStackPreexecutionVerificationEnabled() CONST;
	BOOL IsTCStackExecutionVerificationEnabled() CONST;
	VOID ResetTCStack();

	BOOL GetPrintProperties(CRichEditCtrl **pEditCtrl) CONST;

	VOID DoFindCode();
	BOOL CanFindCode() CONST;
	VOID DoFindNextCode(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindNextCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindNextCode() CONST;
	VOID DoFindPreviousCode(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindPreviousCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindPreviousCode() CONST;
	VOID DoReplaceCode();
	BOOL CanReplaceCode() CONST;
	VOID DoGoToCode();
	BOOL DoGoToCode(LPCTSTR pszLine);
	BOOL CanGoToCode() CONST;

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoCutSel();
	BOOL CanCutSel() CONST;
	VOID DoCopySel();
	BOOL CanCopySel() CONST;
	VOID DoPasteSel();
	BOOL CanPasteSel() CONST;
	VOID DoDeleteSel();
	BOOL CanDeleteSel() CONST;

	VOID DoSelectAllCode();
	VOID UnSelectAllCode();
	BOOL CanSelectAllCode() CONST;

	BOOL HasCode() CONST;

	VOID ShowDialogs(BOOL bShow);
	BOOL HasDialogs() CONST;

	VOID UpdateLayout(BOOL bActivate);

	CSize GetMargins() CONST;

	class CTCProcedurePropertiesView *GetParent() CONST;

public:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesTabCtrl)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesTabCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg LRESULT OnSelectTab(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelchange(NMHDR *pNotifyStruct, LRESULT *pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedurePropertiesView view

// Specify the telecommand procedure properties tab identifiers
#define TCPROCEDUREPROPERTIESVIEW_OVERVIEWTAB   0
#define TCPROCEDUREPROPERTIESVIEW_ARGUMENTSTAB   1
#define TCPROCEDUREPROPERTIESVIEW_VARIABLESTAB   2
#define TCPROCEDUREPROPERTIESVIEW_THREADSTAB   3
#define TCPROCEDUREPROPERTIESVIEW_STEPSTAB   4
#define TCPROCEDUREPROPERTIESVIEW_DEBUGTAB   5
#define TCPROCEDUREPROPERTIESVIEW_CODETAB   6
#define TCPROCEDUREPROPERTIESVIEW_TCSTACKTAB   7

class CTCProcedurePropertiesView : public CView
{
	DECLARE_DYNCREATE(CTCProcedurePropertiesView)

	// Construction
public:
	CTCProcedurePropertiesView();

	// Attributes
private:
	CTCProcedurePropertiesTabCtrl  m_wndTabCtrl;

	// Operations
public:
	VOID SetProperties(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nFlags = TRUE);
	BOOL GetProperties(CDatabaseTCProcedure *pDatabaseTCProcedure, INT nFlags = TRUE) CONST;

	BOOL SetBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	INT GetBreakpoints(LPCTSTR pszThread, CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints) CONST;

	VOID UpdateSteps(LPCTSTR pszThread, CONST CPtrArray &pSteps);
	VOID UpdateIdentifiers(CTMEnvironment *pTMEnvironment, CTCEnvironment *pTCEnvironment, CONST CStringArray &szIdentifiers, CONST CUIntArray &nIdentifierTypes, CONST CLongUIntArray &nIdentifierAttributes, CONST CPtrArray &pIdentifiers);
	VOID UpdateExecutionpoint(LPCTSTR pszThread, UINT nState = TCPROCEDURETHREAD_RUNNINGSTATE_NOTRUNNING, UINT nLine = 0);

	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem);
	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem, LPCTSTR pszStatus, LPCTSTR pszResult);
	BOOL UpdateTCStack(CONST CTCProcedureItem *pItem, CONST CTCPacket *pTCPacket, BOOL &bLogging);
	VOID UpdateTCStack(BOOL bRunning, BOOL bSuspended);
	BOOL IsTCStackReleaseWaitModeEnabled() CONST;
	CTimeSpan GetTCStackReleaseWaitInterval() CONST;
	BOOL IsTCStackPreexecutionVerificationEnabled() CONST;
	BOOL IsTCStackExecutionVerificationEnabled() CONST;
	VOID ResetTCStack();

	BOOL GetPrintProperties(CRichEditCtrl **pEditCtrl) CONST;

	VOID DoFindCode();
	BOOL CanFindCode() CONST;
	VOID DoFindNextCode(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindNextCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindNextCode() CONST;
	VOID DoFindPreviousCode(BOOL bMatchCase, BOOL bMatchWord);
	VOID DoFindPreviousCode(LPCTSTR pszText, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord);
	BOOL CanFindPreviousCode() CONST;
	VOID DoReplaceCode();
	BOOL CanReplaceCode() CONST;
	VOID DoGoToCode();
	BOOL DoGoToCode(LPCTSTR pszLine);
	BOOL CanGoToCode() CONST;

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoCutSel();
	BOOL CanCutSel() CONST;
	VOID DoCopySel();
	BOOL CanCopySel() CONST;
	VOID DoPasteSel();
	BOOL CanPasteSel() CONST;
	VOID DoDeleteSel();
	BOOL CanDeleteSel() CONST;

	VOID DoSelectAllCode();
	VOID UnSelectAllCode();
	BOOL CanSelectAllCode() CONST;

	BOOL HasCode() CONST;

	VOID ShowDialogs(BOOL bShow);
	BOOL HasDialogs() CONST;

	VOID UpdateLayout(BOOL bActivate);

	class CTCProcedureSplitterWnd *GetParent() CONST;

public:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedurePropertiesView)
public:
	virtual BOOL IsModified() CONST;
	virtual BOOL Check(BOOL bModified = TRUE) CONST;
protected:
	virtual void OnDraw(CDC *pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CTCProcedurePropertiesView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureSplitterWnd window

class CTCProcedureSplitterWnd : public CSplitterWndEx
{
	DECLARE_DYNCREATE(CTCProcedureSplitterWnd)

	// Construction
public:
	CTCProcedureSplitterWnd();

	// Attributes
private:
	BOOL  m_bTracking;

	// Operations
public:
	BOOL Create(class CTCProcedureWnd *pParentWnd);

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

	VOID SetPaneWidths(INT nFlowchartPaneWidth, INT nPropertiesPaneWidth);
	VOID GetPaneWidths(INT &nFlowchartPaneWidth, INT &nPropertiesPaneWidth) CONST;

	VOID EnableGraphicalInterface(BOOL bEnable = TRUE);

	VOID UpdateLayout(BOOL bActivate);

	CTCProcedureFlowchartView *GetFlowchartView() CONST;
	CTCProcedurePropertiesView *GetPropertiesView() CONST;

	class CTCProcedureWnd *GetParent() CONST;

public:
	VOID AdjustToPrivileges();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureSplitterWnd)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureSplitterWnd)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureCompileThread thread

// Specify the telecommand procedure compile thread timer related identifers
#define TCPROCEDURECOMPILETHREAD_UPDATE_TIMERID   101
#define TCPROCEDURECOMPILETHREAD_UPDATE_TIMEOUT   100

class CTCProcedureCompileThread : public CThread
{
	DECLARE_DYNAMIC(CTCProcedureCompileThread)

	// Construction
public:
	CTCProcedureCompileThread();

	// Attributes
private:
	LONG  m_bStop;
	LONG  m_bAbort;
	BOOL  m_bBatch;
	BOOL  m_bSyntax;
	UINT  m_nErrors;
	UINT  m_nWarnings;
	CStringArray  m_szLines;
	CDatabaseTCProcedure  m_cDatabaseTCProcedure;
	CEvent  m_bCompilation[2];

	// Operations
public:
	BOOL StartCompiling(CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	BOOL StartCompiling(CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, BOOL bSyntax, BOOL bBatch, INT &nErrors, INT &nWarnings, BOOL &bAbort);
	BOOL IsCompiling() CONST;
	BOOL StopCompiling();

	VOID SetCompileTarget(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, BOOL bSyntax, BOOL bBatch);
	VOID GetCompileTarget(CDatabaseTCProcedure *pDatabaseTCProcedure) CONST;
	BOOL IsSyntaxCompileTarget() CONST;
	BOOL IsBatchCompileTarget() CONST;

	BOOL GenerateSourceCode(CONST CBinaryDatabase *pDatabase, CDatabaseTCProcedure *pDatabaseTCProcedure, CString &szSourceCode, INT nFlags = 0);

private:
	BOOL OpenCompileTarget(CBinaryDatabase *pDatabase);
	VOID CompileTarget(CBinaryDatabase *pDatabase);
	VOID CloseCompileTarget();

	CString GenerateStepSourceCode(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, CONST CTCProcedureDocumentItem *pStep, LPCTSTR pszLabel, LPCTSTR pszIndent) CONST;
	CString GenerateSubStepsSourceCode(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, CONST CTCProcedureDocumentItem *pStep, UINT nSubThreadID, LPCTSTR pszInvariantCondition, LPCTSTR pszLabel, LPCTSTR pszIndent) CONST;
	BOOL TranslateSourceCode(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszSourceCode, LPCTSTR pszPrecompileCode, CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CONST CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables, CString &szCompileCode);
	BOOL LoadSourceCodeTemplate(UINT nTemplateID, CString &szTemplate) CONST;

	CString GetTelecommandProcedureFileName(CONST CBinaryDatabase *pDatabase, LPCTSTR pszFormat, BOOL bTemporary = FALSE) CONST;
	BOOL SecureTelecommandProcedureFile(LPCTSTR pszFileName) CONST;
	CString GetTelecommandProcedureCompilerFileName() CONST;
	CString GetTelecommandProcedureCompilerFileName(LPCTSTR pszDirectory) CONST;
	CString GetTelecommandProcedureCompileOptions(CONST CBinaryDatabase *pDatabase) CONST;
	CString GetTelecommandProcedureLinkerFileName() CONST;
	CString GetTelecommandProcedureLinkOptions(CONST CBinaryDatabase *pDatabase) CONST;

	INT EnumThreads(CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszSourceCode) CONST;
	INT EnumExpressionParameters(CONST CBinaryDatabase *pDatabase, LPCTSTR pszSourceCode, CStringArray &szTMParameters, CStringArray &szTCParameters) CONST;
	INT ExtractExpressionParameters(CONST CBinaryDatabase *pDatabase, LPCTSTR pszExpression, CStringArray &szTMParameters, CStringArray &szTCParameters) CONST;
	INT CollectArguments(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszSourceCode, CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CStringArray &szArguments) CONST;
	INT CollectVariables(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszSourceCode, CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables, CStringArray &szVariables) CONST;
	INT CollectExpressionParameters(CONST CStringArray &szNewParameters, CStringArray &szParameters) CONST;
	CString EnumArgumentIdentifiers(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments) CONST;
	CString EnumVariableIdentifiers(CONST CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables) CONST;
	CString EnumParameterIdentifiers(CONST CStringArray &szParameters) CONST;
	CString EnumArgumentAssignments(CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, BOOL bFormal) CONST;
	CString EnumVariableAssignments(CONST CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables) CONST;
	CString EnumSynchronizationObjectIdentifiers(CONST CStringArray &szSyncObjects) CONST;
	CString EnumExpressionTMParameterDeclarations(CONST CStringArray &szTMParameters) CONST;
	CString EnumExpressionTCParameterDeclarations(CONST CStringArray &szTCParameters) CONST;
	CString EnumExpressionTMParameterInitializations(CONST CStringArray &szTMParameters) CONST;
	CString EnumExpressionTCParameterInitializations(CONST CStringArray &szTCParameters) CONST;
	CString EnumIdentifierReferences(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedureArguments &pDatabaseTCProcedureArguments, CONST CDatabaseTCProcedureVariables &pDatabaseTCProcedureVariables, CONST CStringArray &szTMParameters, CONST CStringArray &szTCParameters) CONST;
	CString EnumSynchronizationObjectReferences(CONST CStringArray &szSyncObjects) CONST;
	CString ExtractThreadTriggerExpressions(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszThread) CONST;
	CString ExtractThreadBodyExpressions(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszThread) CONST;
	CString ExtractThreadConfirmationExpressions(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszThread) CONST;
	CString ExtractThreadTCFunctionInitializations(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszThread, BOOL bExpanded) CONST;
	CString ExtractThreadTCFunctionPreexecutionExpressions(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszThread, CString &szParameters) CONST;
	CString ExtractThreadTCFunctionExecutionVerificationTimeWindows(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszThread) CONST;
	CString ExtractThreadTCFunctionExecutionExpressions(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszThread, CString &szParameters) CONST;
	CString ExtractThreadCode(LPCTSTR pszSourceCode, LPCTSTR pszThread) CONST;
	CString ExtractFunctions(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszSourceCode) CONST;

	INT CalculateTCFunctionElementOffset(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCFunction *pDatabaseTCFunction) CONST;
	INT CalculateTCFunctionElementCount(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCFunction *pDatabaseTCFunction) CONST;

	BOOL CheckArgumentIdentifierName(LPCTSTR pszName) CONST;
	BOOL CheckVariableIdentifierName(LPCTSTR pszName) CONST;
	CString TranslateToIdentifierName(LPCTSTR pszName) CONST;
	CString TranslateIdentifierDataType(ULONGLONG nAttributes, INT nWidth = 0, BOOL bDeclaration = TRUE) CONST;
	CString TranslateConditionExpression(LPCTSTR pszExpression) CONST;

	INT FindTelecommandProcedureLangaugeSourceCodeKeyword(LPCTSTR pszSourceCode, LPCTSTR pszKeyword, INT nPos) CONST;
	LPCTSTR FindTelecommandProcedureLangaugeSourceCodeKeyword(LPCTSTR pszSourceCode, LPCTSTR pszKeyword) CONST;

	BOOL CheckSourceCode(LPCTSTR pszSourceCode, INT nCodePos, BOOL bCommentsOnly = FALSE) CONST;
	BOOL CheckSourceCodeLine(LPCTSTR pszSourceCode, LPCTSTR pszLine, INT nLinePos) CONST;
	VOID ConvertSourceCodeToData(LPCTSTR pszSourceCode, CByteArray &nData) CONST;

	CString FormatTelecommandProcedureCompilerErrors(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszSourceCode, LPCTSTR pszError, INT nLine);
	VOID ShowTelecommandProcedureCompilerErrors(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszSourceCode, LPCTSTR pszErrors);
	VOID ShowTelecommandProcedureLinkerErrors(CONST CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, LPCTSTR pszSourceCode, LPCTSTR pszErrors);

	VOID CleanupTelecommandProcedureBuildOutput(CONST CBinaryDatabase *pDatabase);

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
	//{{AFX_VIRTUAL(CTCProcedureCompileThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureCompileThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureTestThread thread

// Specify the telecommand procedure test thread related identifiers
#define TCPROCEDURETESTTHREAD_EVENT_LAUNCH   1
#define TCPROCEDURETESTTHREAD_EVENT_COMMAND   2
#define TCPROCEDURETESTTHREAD_EVENT_UPDATE   3
#define TCPROCEDURETESTTHREAD_EVENT_EXIT   4
// Specify the telecommand procedure test thread timer related identifers
#define TCPROCEDURETESTTHREAD_TESTPROFILE_TIMERID   102
#define TCPROCEDURETESTTHREAD_TESTPROFILE_TIMEOUT   1000
#define TCPROCEDURETESTTHREAD_TESTDISPLAY_TIMERID   103
#define TCPROCEDURETESTTHREAD_TESTDISPLAY_TIMEOUT   1000
#define TCPROCEDURETESTTHREAD_LAUNCHDISPLAY_TIMERID   104
#define TCPROCEDURETESTTHREAD_LAUNCHDISPLAY_TIMEOUT   0

class CTCProcedureTestThread : public CThread
{
	DECLARE_DYNAMIC(CTCProcedureTestThread)

	// Construction
public:
	CTCProcedureTestThread();

	// Attributes
private:
	CString  m_szTCProcedureName;
	CPtrArray  m_hTCProcedureEvents;
	CTCEnvironment  *m_pTCEnvironment;
private:
	class CTCProcedureWnd  *m_pTCProcedureWnd;

	// Operations
public:
	BOOL Start(class CTCProcedureWnd *pTCProcedureWnd, LPCTSTR pszName, CTCEnvironment *pTCEnvironment, CONST CPtrArray &hTCProcedureEvents);
	BOOL Stop();

private:
	VOID ShowTestMessage(LPCTSTR pszMessage);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureTestThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureTestThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureScheduleThread

class CTCProcedureScheduleThread : public CThread
{
	DECLARE_DYNAMIC(CTCProcedureScheduleThread)

	// Construction
public:
	CTCProcedureScheduleThread();
	~CTCProcedureScheduleThread();

	// Attributes
private:
	CONST CDatabaseEngine  *m_pDatabase;
	CTMEnvironment  *m_pTMEnvironment;
	CTCEnvironment  *m_pTCEnvironment;
	CTCProcessEngine  *m_pTCProcessEngine;
private:
	INT  m_nTCProcedureID;
	CString  m_szTCProcedureName;
	HINSTANCE  m_hTCProcedureCode;
	CTCProcedureItems  m_pTCProcedureItems;
private:
	CTCPacket  m_cTCPacket;
private:
	CTimeTag  m_tReleaseAttempt;
private:
	CEvent  m_bUpdate;
	BOOL  m_bIdle;
private:
	class CTCProcedureWnd  *m_pTCProcedureWnd;

	// Operations
public:
	BOOL Start(class CTCProcedureWnd *pTCProcedureWnd, LPCTSTR pszName, CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTMEnvironment *pTMEnvironment, CTCEnvironment *pTCEnvironment, INT nTCProcedureID, HINSTANCE hTCProcedureCode);
	BOOL Stop();

	BOOL Initialize(CONST CTCProcedureItem *pItem, CDatabaseTCFunction *pDatabaseTCFunction, CDatabaseTCPacket *pDatabaseTCPacket);

	BOOL Schedule(CONST CTCProcedureItem *pItem);
	BOOL Unschedule(CONST CTCProcedureItem *pItem);

	BOOL Update();

	BOOL IsIdle() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureScheduleThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureScheduleThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureVerificationThread

class CTCProcedureVerificationThread : public CThread
{
	DECLARE_DYNAMIC(CTCProcedureVerificationThread)

	// Construction
public:
	CTCProcedureVerificationThread();
	~CTCProcedureVerificationThread();

	// Attributes
private:
	CONST CDatabaseEngine  *m_pDatabase;
	CTCProcessEngine  *m_pTCProcessEngine;
	CTCEnvironment  *m_pTCEnvironment;
private:
	INT  m_nTCProcedureID;
	CString  m_szTCProcedureName;
	HINSTANCE  m_hTCProcedureCode;
	CTCProcedureItems  m_pTCProcedureItems;
private:
	CEvent  m_bUpdate;
	BOOL  m_bIdle;
private:
	class CTCProcedureWnd  *m_pTCProcedureWnd;

	// Operations
public:
	BOOL Start(class CTCProcedureWnd *pTCProcedureWnd, LPCTSTR pszName, CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, INT nTCProcedureID, HINSTANCE hTCProcedureCode);
	BOOL Stop();

	BOOL Verify(CONST CTCProcedureItem *pItem);
	BOOL Update();

	BOOL IsIdle() CONST;

private:
	VOID ShowVerificationMessage(LPCTSTR pszType, LPCTSTR pszMessage);
	VOID ShowVerificationMessages();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureVerificationThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureVerificationThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCProcedureWnd frame with splitter

// Specify the telecommand procedure display statusbar pane identifiers
#define ID_TCPROCEDURE_STATUSBAR_STEPSPANE   ID_SEPARATOR
#define ID_TCPROCEDURE_STATUSBAR_MODEPANE   ID_STATUSBAR_PANE1
#define ID_TCPROCEDURE_STATUSBAR_TYPEPANE   ID_STATUSBAR_PANE2
#define ID_TCPROCEDURE_STATUSBAR_NAMEPANE   ID_STATUSBAR_PANE3

class CTCProcedureWnd : public CDisplayWnd
{
	DECLARE_DYNCREATE(CTCProcedureWnd)

	// Construction
public:
	CTCProcedureWnd();
	CTCProcedureWnd(LPCTSTR pszName);

	// Attributes
private:
	CString  m_szName;
	CString  m_szTitle;
	CDatabaseTCProcedure  m_cDatabaseTCProcedure;
private:
	UINT  m_nTCProcedureID;
	UINT  m_nTCProcedureMode;
	UINT  m_nTCProcedureCount;
	UINT  m_nTCProcedureStepID;
	BOOL  m_bTCProcedureStepInto;
	BOOL  m_bTCProcedureStepOver;
	BOOL  m_bTCProcedureStepOut;
	BOOL  m_bTCProcedureStepBreak;
	BOOL  m_bTCProcedureLineBreak;
	BOOL  m_bTCProcedureBreak;
	BOOL  m_bTCProcedureDirty;
	BOOL  m_bTCProcedureExit;
	HANDLE  m_hTCProcedureExit;
	CString  m_szTCProcedureStep;
	HINSTANCE  m_hTCProcedureCode;
	CPtrArray  m_hTCProcedureEvents;
	CPtrArray  m_pTCProcedureViews;
	CUIntArray  m_nTCProcedureLines;
	CStringArray  m_szTCProcedureViews;
	CTCProcedureTestThread  m_cTCTestThread;
	CTCProcedureScheduleThread  m_cTCScheduleThread;
	CTCProcedureVerificationThread  m_cTCVerificationThread;
private:
	CTCProcedureSplitterWnd  m_wndSplitter;
	CTCProcedureStatusBar  m_wndStatusBar;
private:
	CTCProcedureFlowchartView  *m_pFlowchartView;
	CTCProcedurePropertiesView  *m_pPropertiesView;
private:
	CTCProcedurePropertiesDialog  m_dlgProperties;
public:
	static CTMEnvironment  m_cTMEnvironment;
	static CTCEnvironment  m_cTCEnvironment;
	static CTCProcessEngine  m_cTCProcessEngine;
public:
	static CByteArray  m_cTCCommandQueueInfo;
	static CCriticalSection  m_cCriticalTCCommandQueueInfoSection;
public:
	static CTCProcedureCompileThread  m_cCompileThread;

	// Operations
public:
	BOOL Create(CMDIFrameWnd *pParentWnd, UINT nShow = -1);

	VOID SetName(LPCTSTR pszName);
	CString GetName() CONST;
	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;
	BOOL SetProcedure(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nFlags = TRUE);
	BOOL GetProcedure(CDatabaseTCProcedure *pDatabaseTCProcedure, INT nFlags = TRUE) CONST;
	VOID SetProperties(CONST LOGFONT *plfStepsLabelFont, COLORREF nStepsLabelColor, COLORREF nBackgroundColor);
	BOOL GetProperties(LOGFONT *plfStepsLabelFont, COLORREF &nStepsLabelColor, COLORREF &nBackgroundColor) CONST;
	VOID SetMode(UINT nMode);
	UINT GetMode() CONST;

	BOOL GenerateSourceCode(CString &szSourceCode, INT nFlags = 0) CONST;
	BOOL GotoSourceCode(LPCTSTR pszLine);

	VOID SetSelectedTCThreadID(UINT nThreadID = 0);
	UINT GetSelectedTCThreadID() CONST;
	VOID SetSelectedTCStepID(UINT nStepID = -1);
	UINT GetSelectedTCStepID() CONST;

	BOOL StartTestingProcedure();
	BOOL StartTestingProcedure(va_list pDatabaseTCProcedureArguments, CONST CPtrArray &pEvents);
	BOOL LaunchTestingProcedure();
	BOOL SuspendTestingProcedure();
	BOOL ResumeTestingProcedure(BOOL bAuto = TRUE);
	BOOL IsProcedureTestRunning() CONST;
	BOOL IsProcedureTestSuspended() CONST;
	BOOL IsProcedureTestStopping() CONST;
	BOOL PrepareProcedureForTesting(BOOL bFeedback = TRUE);
	BOOL CheckProcedureTestState(LPCTSTR pszThread, UINT &nState, CStringArray &szStepNames, CUIntArray &nStepStates, UINT &nLine) CONST;
	BOOL UpdateProcedureTestState();
	BOOL TerminateTestingProcedure(BOOL bAuto = TRUE);
	BOOL StopTestingProcedure();

	BOOL UpdateProcedureThreadBreakpoints(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadBreakpoints &pDatabaseTCProcedureThreadBreakpoints);
	BOOL InjectProcedureThreadTestProfile(LPCTSTR pszThread, CONST CDatabaseTCProcedureThreadTestProfile *pDatabaseTCProcedureThreadTestProfile);

	BOOL SetProcedureTestParameterValues(CONST CTMParameters &pTMParameters);
	BOOL SetProcedureTestParameterValues(CONST CTCParameters &pTCParameters);
	BOOL GetProcedureTestParameterValues(CTMParameters &pTMParameters);
	BOOL GetProcedureTestParameterValues(CTCParameters &pTCParameters);

	BOOL ScheduleProcedureCommand();
	BOOL UnscheduleProcedureCommand(CONST CTCProcedureItem *pItem);
	BOOL SendProcedureCommand(CONST CTCProcedureItem *pItem, CONST CTCPacket *pTCPacket, INT nSubEntryID);
	BOOL SuspendProcedureCommandScheduling(BOOL bSuspend = TRUE);

	VOID EnableGraphicalInterface(BOOL bEnable = TRUE);

	BOOL GetPrintProperties(CStringArray &szThreads, CPtrArray &pThreadMetaDCs, CRichEditCtrl **pEditCtrl, UINT nFlags) CONST;

	VOID UpdateBars();

	CTCProcedureFlowchartView *GetFlowchartView() CONST;
	CTCProcedurePropertiesView *GetPropertiesView() CONST;

private:
	VOID UpdateTitle();
	VOID UpdateMenus();
	VOID UpdateContents();

	INT SaveToDatabase();
	BOOL LoadFromDatabase();
	INT DeleteFromDatabase();

	BOOL StartPrintJob(CDC &cDC);
	BOOL PrintJob(CDC &cDC, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nFlags, CONST CStringArray &szThreads, CONST CPtrArray &pThreadMetaDCs, CRichEditCtrl *pEditCtrl, WORD wFromPage = -1, WORD wToPage = -1);
	BOOL EndPrintJob(CDC &cDC);

	BOOL DrawPrintDocPage(CDC &cDC, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, LPCTSTR pszTitle, CONST CPtrArray &pFonts, LPRECT prClip, INT nPage = -1, BOOL bCalc = FALSE);
	BOOL DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc = FALSE);

	CString GetPrintDocTitle() CONST;
	CString GetPrintDocInfoTitle(LPCTSTR pszTitle) CONST;

public:
	static BOOL StartCompilingProcedure(CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure);
	static BOOL StartCompilingProcedure(CBinaryDatabase *pDatabase, CONST CDatabaseTCProcedure *pDatabaseTCProcedure, BOOL bSyntax, BOOL bBatch, INT &nErrors, INT &nWarnings, BOOL &bAbort);
	static BOOL IsCompilingProcedure();
	static VOID StopCompilingProcedure();

	static BOOL LockProcedureCommandQueue(CTCEnvironment *pTCEnvironment);
	static BOOL UnlockProcedureCommandQueue(CONST CTCEnvironment *pTCEnvironment);

	static INT Delete(LPCTSTR pszName);

	static VOID Clean();

private:
	BOOL UpdateParameterValue(CONST CDatabaseTMParameter *pDatabaseTMParameter);

	VOID ShowTestMessage(LPCTSTR pszType, LPCTSTR pszMessage, BOOL bAudition = FALSE);
	VOID ShowTestMessages();

	BOOL HasTestDialogs() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCProcedureWnd)
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
	virtual VOID DoTestBreak();
	virtual BOOL CanBreakTesting() CONST;
	virtual VOID DoTestContinue();
	virtual BOOL CanContinueTesting() CONST;
	virtual VOID DoTestStepInto();
	virtual BOOL CanTestStepInto() CONST;
	virtual VOID DoTestStepOver();
	virtual BOOL CanTestStepOver() CONST;
	virtual VOID DoTestStepOut();
	virtual BOOL CanTestStepOut() CONST;
	virtual VOID DoTestReset();
	virtual BOOL CanResetTesting() CONST;
	virtual VOID DoTestStop();
	virtual VOID DoClose();
public:
	virtual VOID AdjustToPrivileges();
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CTCProcedureWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateStatusBarStepsPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarRunningModePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarStepTypePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarStepNamePane(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __TCPROCEDURE_H__
