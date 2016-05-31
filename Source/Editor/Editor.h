// EDITOR.H : SatView Editor Application.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the application related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/02/07 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __EDITOR_H__
#define __EDITOR_H__

#define _USE_MATH_DEFINES

#ifndef RC_INVOKED
#include <afxwin.h>
#include <afxext.h>
#include <afxwinappex.h>
#include <afxdialogex.h>
#include <afxsplitterwndex.h>
#include <afxcontrolbars.h>
#include <afxheaderctrl.h>
#include <afxctl.h>
#include <afxdisp.h>
#include <afxpriv.h>
#include <afxrich.h>
#include <afxcmn.h>
#include <afxdb.h>
#include <afxmt.h>

#include <atlsecurity.h>

#include <comdef.h>

#include <evntprov.h>

#include <float.h>

#include <lmcons.h>
#include <lmshare.h>
#include <lmapibuf.h>
#include <lmerr.h>

#include <math.h>

#include <mmsystem.h>


#include "audio.h"
#include "books.h"
#include "event.h"
#include "mutex.h"
#include "views.h"
#include "token.h"
#include "tools.h"
#include "macros.h"
#include "mimics.h"
#include "thread.h"
#include "archive.h"
#include "jscript.h"
#include "logfile.h"
#include "network.h"
#include "strings.h"
#include "timekey.h"
#include "version.h"
#include "accounts.h"
#include "controls.h"
#include "database.h"
#include "eventlog.h"
#include "language.h"
#include "messages.h"
#include "profiles.h"
#include "registry.h"
#include "security.h"
#include "assistant.h"
#include "ttcprocess.h"
#include "tcprocedures.h"

#include "MimicsCtlEnum.h"
#endif

#include "resource.h"       // main symbols
#include "Editor.rh"

#include "and.h"
#include "grd.h"
#include "mmd.h"
#include "pod.h"
#include "dbms.h"
#include "jcode.h"
#include "script.h"
#include "dialogs.h"
#include "profile.h"
#include "compiler.h"
#include "displays.h"
#include "tmpacket.h"
#include "tcfunction.h"
#include "tcsequence.h"
#include "tcprocedure.h"
#include "tmparameter.h"
#include "tcparameter.h"
#include "obprocessor.h"


/////////////////////////////////////////////////////////////////////////////
// CRecentDocumentInfo

class CRecentDocumentInfo : public CObject
{
	// Construction
public:
	CRecentDocumentInfo();

	// Attributes
private:
	typedef struct tagDATA {
		INT  cbSize;
		INT  cbName;
		INT  cbTitle;
		ULONGLONG  nComponent;
	} DATA, *PDATA, *LPDATA;
private:
	CString  m_szName;
	CString  m_szTitle;
	ULONGLONG  m_nComponent;

	// Operations
public:
	VOID SetDocument(LPCTSTR pszName, LPCTSTR pszTitle, ULONGLONG nComponent);
	BOOL GetDocument(CString &szName, CString &szTitle, ULONGLONG &nComponent) CONST;

	VOID Reset();

	VOID Copy(CONST CRecentDocumentInfo *pDocumentInfo);
	BOOL Compare(CONST CRecentDocumentInfo *pDocumentInfo) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRecentDocuments

class CRecentDocuments : public CPtrArray
{
	// Construction
public:
	CRecentDocuments();
	~CRecentDocuments();

	// Attributes
public:

	// Operations
public:
	INT Add(CRecentDocumentInfo *pDocumentInfo);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CRecentDocumentInfo *GetAt(INT nIndex) CONST;
	CRecentDocumentInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CRecentDocuments *pDocuments);
	BOOL Compare(CONST CRecentDocuments *pDocuments) CONST;

	BOOL Map(CByteArray &nInfo) CONST;
	BOOL Unmap(CONST CByteArray &nInfo);
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRecentDatabaseInfo

class CRecentDatabaseInfo : public CDatabaseProfileInfo
{
	// Construction
public:
	CRecentDatabaseInfo();

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CRecentDatabases

class CRecentDatabases : public CDatabaseProfiles
{
	// Construction
public:
	CRecentDatabases();
	~CRecentDatabases();

	// Attributes
public:

	// Operations
public:
	INT Add(CRecentDatabaseInfo *pDatabase);

	INT Find(LPCTSTR pszName) CONST;
	INT Enum(CStringArray &szNames) CONST;

	CRecentDatabaseInfo *GetAt(INT nIndex) CONST;
	CRecentDatabaseInfo *operator[](INT nIndex) CONST;

	VOID RemoveAll();

	BOOL Copy(CONST CRecentDatabases *pDatabases);
	BOOL Compare(CONST CRecentDatabases *pDatabases) CONST;
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolButton window

class CToolButton : public CBitmapButton
{
	DECLARE_DYNCREATE(CToolButton)

	// Construction
public:

	// Attributes
public:

	// Operations
private:
	VOID DrawButton(CDC *pDC);

	VOID DrawButtonSymbol(CDC *pDC, CBitmap *pBitmap);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolButton)
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolButton)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolSizeBarCtrl window

class CToolSizeBarCtrl : public CWnd
{
	DECLARE_DYNCREATE(CToolSizeBarCtrl)

	// Construction
public:
	CToolSizeBarCtrl();

	// Attributes
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	VOID Activate(CONST RECT &rect);
	VOID Deactivate();

	class CToolWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolSizeBarCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolSizeBarCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CToolWnd window

// Specify the tool window sizes
#define TOOLWINDOW_SIZE_DOCKED   0
#define TOOLWINDOW_SIZE_MULTIDOCKED   1
#define TOOLWINDOW_SIZE_FLOATING   2
#define TOOLWINDOW_SIZES   3
// Specify the tool window default sizes
#define TOOLWINDOW_SIZE_WIDTH   300
#define TOOLWINDOW_SIZE_HEIGHT   150
// Specify the tool window dock states
#define TOOLWINDOW_DOCKSTATE_LEFT   (1<<0)
#define TOOLWINDOW_DOCKSTATE_TOP   (1<<1)
#define TOOLWINDOW_DOCKSTATE_RIGHT   (1<<2)
#define TOOLWINDOW_DOCKSTATE_BOTTOM   (1<<3)
#define TOOLWINDOW_DOCKSTATE_HIDDEN   (1<<4)
#define TOOLWINDOW_DOCKSTATE_EXPANDED   (1<<5)
#define TOOLWINDOW_DOCKSTATE_SHRINKED   (1<<6)
#define TOOLWINDOW_DOCKSTATE_LOCKED   (1<<7)
// Specify the tool window layout settings
#define TOOLWINDOW_FRAME_SIZE   5
#define TOOLWINDOW_BORDER_SIZE   3
#define TOOLWINDOW_CAPTION_SIZE   16
// Specify the tool window button identifiers
#define TOOLWINDOW_EXPANDBUTTON_ID   1
#define TOOLWINDOW_HIDEBUTTON_ID   2
// Specify the tool window styles
#define TWS_DOCKED   (0<<0)
#define TWS_FLOATING   (1<<0)
#define TWS_NOEXPANDBUTTON   (1<<1)
#define TWS_NOHIDEBUTTON   (1<<2)

class CToolWnd : public CMiniFrameWnd
{
	DECLARE_DYNCREATE(CToolWnd)

	// Construction
public:
	CToolWnd(CToolWnd *pToolWnd = NULL);

	// Attributes
private:
	CString  m_szTitle;
private:
	BOOL  m_bVisible;
	BOOL  m_bDragFull;
	BOOL  m_bDockFull;
	BOOL  m_bDockDrag;
	BOOL  m_bDockSize;
	UINT  m_nDockState;
	CRect  m_rDockRect;
	CRect  m_rDockArea;
	CRect  m_rDockDrag;
	POINT  m_ptDockDrag;
	CSize  m_sizeDefault[TOOLWINDOW_SIZES];
	CToolButton  m_wndExpandButtonCtrl;
	CToolButton  m_wndHideButtonCtrl;
	CToolSizeBarCtrl  m_wndSizeCtrl;
protected:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, LPCTSTR pszTitle, DWORD dwStyle, CONST RECT &rect, UINT nID = 0);

	VOID SetTitle(LPCTSTR pszTitle);
	CString GetTitle() CONST;

	VOID SetDockState(UINT nState = 0);
	UINT GetDockState(BOOL bAll = FALSE) CONST;
	VOID SetDraggedDockState(UINT nState = 0);
	UINT GetDraggedDockState(BOOL bAll = FALSE) CONST;

	UINT GetDockSide() CONST;

	BOOL IsDocked(BOOL bAll = FALSE) CONST;

	VOID SetDockRect();
	VOID SetDockRect(CONST RECT &rect);
	VOID GetDockRect(LPRECT lpRect) CONST;

	VOID SetDefaultSize(CONST SIZE &size);
	CSize GetDefaultSize(UINT nState) CONST;
	CSize GetDefaultSize() CONST;

	VOID Show();
	VOID Hide();
	BOOL IsVisible() CONST;
	VOID Expand(BOOL bContract);
	BOOL IsExpanded() CONST;
	VOID Shrink(LPCRECT pRect);
	BOOL IsShrinked() CONST;

	VOID StartDragging();
	BOOL IsDragged() CONST;
	VOID StopDragging();

	VOID StartSizing();
	BOOL IsSized() CONST;
	VOID StopSizing();

	VOID AdjustDragFrame(CONST POINT &pt, LPRECT lpRect);
	VOID AdjustSizeBar(CONST POINT &pt, LPRECT lpRect);
	BOOL CalcDragCaption(LPRECT lpRect) CONST;
	BOOL CalcSizeBorder(UINT nSide, LPRECT lpRect) CONST;
	BOOL IsPointOnDragCaption(CONST POINT &pt) CONST;
	UINT IsPointOnSizeBorder(CONST POINT &pt) CONST;

	INT CalcTrackExtent(UINT nSide) CONST;
	CSize CalcExtent() CONST;

	virtual VOID SetData(CONST CByteArray &nData);
	virtual VOID GetData(CByteArray &nData) CONST;

	class CMainWnd *GetParent() CONST;

public:
	VOID CalcClientRect(LPRECT pRect) CONST;

private:
	VOID SetButtonBitmaps(UINT nState = 0);
	VOID RepositionButtons();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolWnd)
public:
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CToolWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnWindowPosChanging(WINDOWPOS *lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnToolTip(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	afx_msg LRESULT OnEnterSizeMove(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnExitSizeMove(WPARAM wParam, LPARAM lParam);
	afx_msg void OnExpand();
	afx_msg void OnHide();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewPage window

class CWorkspaceViewPage : public CWnd
{
	DECLARE_DYNCREATE(CWorkspaceViewPage)

	// Construction
public:
	CWorkspaceViewPage();

	// Attributes
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect);

	class CWorkspaceView *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceViewPage)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceViewPage)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewDatabasePageToolTip window

// Specify the workspace view database page tool-tip timer related identifiers
#define WORKSPACEVIEWDATABASEPAGE_TOOLTIP_TIMERID   100
#define WORKSPACEVIEWDATABASEPAGE_TOOLTIP_TIMEOUT   5000

class CWorkspaceViewDatabasePageToolTip : public CWnd
{
	DECLARE_DYNCREATE(CWorkspaceViewDatabasePageToolTip)

	// Construction
public:
	CWorkspaceViewDatabasePageToolTip();

	// Attributes
private:
	CRect  m_rText;
	CString  m_szText;
	BOOL  m_bBoldText;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL ShowTip(CWnd *pParentWnd, LPCTSTR pszText, CONST RECT &rect, BOOL bBold);
	BOOL DeleteTip();

	class CWorkspaceViewDatabasePageTreeCtrl *GetParent() CONST;

private:
	VOID DrawContent(CDC *pDC);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceViewDatabasePageToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceViewDatabasePageToolTip)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewDatabasePageTreeCtrl window

class CWorkspaceViewDatabasePageTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNCREATE(CWorkspaceViewDatabasePageTreeCtrl)

	// Construction
public:
	CWorkspaceViewDatabasePageTreeCtrl();

	// Attributes
public:

	// Operations
public:
	VOID OpenDatabaseItem(CONST POINT &ptItem);

	VOID ShowFloatingMenu(CONST POINT &ptItem);

	class CWorkspaceViewDatabasePage *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceViewDatabasePageTreeCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceViewDatabasePageTreeCtrl)
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewDatabasePage window

// Specify the workspace view database page item symbols
#define WORKSPACEDATABASEPAGE_ROOTSYMBOL   0
#define WORKSPACEDATABASEPAGE_ROOTNOSYMBOL   1
#define WORKSPACEDATABASEPAGE_FOLDERSYMBOL   2
#define WORKSPACEDATABASEPAGE_FOLDEROPENSYMBOL   3
#define WORKSPACEDATABASEPAGE_TMPACKETSYMBOL   4
#define WORKSPACEDATABASEPAGE_TCFUNCTIONSYMBOL   5
#define WORKSPACEDATABASEPAGE_TMPARAMETERSYMBOL   6
#define WORKSPACEDATABASEPAGE_TCPARAMETERSYMBOL   7
#define WORKSPACEDATABASEPAGE_OBPROCESSORSYMBOL   8
#define WORKSPACEDATABASEPAGE_ANDSYMBOL   9
#define WORKSPACEDATABASEPAGE_GRDSYMBOL   10
#define WORKSPACEDATABASEPAGE_MMDSYMBOL   11
#define WORKSPACEDATABASEPAGE_PODSYMBOL   12
#define WORKSPACEDATABASEPAGE_SCRIPTSYMBOL   13
#define WORKSPACEDATABASEPAGE_SYMBOLS   14

class CWorkspaceViewDatabasePage : public CWorkspaceViewPage
{
	DECLARE_DYNCREATE(CWorkspaceViewDatabasePage)

	// Construction
public:
	CWorkspaceViewDatabasePage();

	// Attributes
private:
	CString  m_szItem;
	HTREEITEM  m_hItem;
	CImageList  m_pItems;
	CWorkspaceViewDatabasePageToolTip  m_wndToolTip;
	CWorkspaceViewDatabasePageTreeCtrl  m_wndView;
private:
	UINT  m_nDragItem;
	BOOL  m_bDragItem;
	CString  m_szDragItem;
	CImageList  m_cDragItem;
private:
	INT  m_nCount[WORKSPACEDATABASEPAGE_SYMBOLS];
	UINT_PTR  m_nTimerID;

	// Operations
public:
	VOID UpdateDatabaseContents(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents();

	BOOL CreateDatabaseItem();
	BOOL OpenDatabaseItem();
	VOID OpenDatabaseItem(CONST POINT &ptItem);
	BOOL HasDatabaseItem(INT nType) CONST;
	BOOL RenameDatabaseItem();
	BOOL DeleteDatabaseItem();

	VOID ShowFloatingMenu(CONST POINT &ptItem);
	VOID ShowFloatingMenu(HTREEITEM hItem, CPoint point);
	VOID ShowFloatingMenu(HTREEITEM hItem, LPCTSTR pszItem, CPoint point);

	BOOL CanDeleteSel() CONST;
	VOID DoDeleteSel();

private:
	VOID EnumTMPackets(HTREEITEM hParentItem);
	VOID EnumTCFunctions(HTREEITEM hParentItem);
	VOID EnumTMParameters(HTREEITEM hParentItem);
	VOID EnumTCParameters(HTREEITEM hParentItem);
	VOID EnumOBProcessors(HTREEITEM hParentItem);
	VOID EnumANDs(HTREEITEM hParentItem);
	VOID EnumGRDs(HTREEITEM hParentItem);
	VOID EnumMMDs(HTREEITEM hParentItem);
	VOID EnumPODs(HTREEITEM hParentItem);
	VOID EnumScripts(HTREEITEM hParentItem);

	HTREEITEM FindTMPacketFolder() CONST;
	HTREEITEM FindTCFunctionFolder() CONST;
	HTREEITEM FindTMParameterFolder() CONST;
	HTREEITEM FindTCParameterFolder() CONST;
	HTREEITEM FindOBProcessorFolder() CONST;
	HTREEITEM FindANDFolder() CONST;
	HTREEITEM FindGRDFolder() CONST;
	HTREEITEM FindMMDFolder() CONST;
	HTREEITEM FindPODFolder() CONST;
	HTREEITEM FindScriptFolder() CONST;
	HTREEITEM FindFolder(LPCTSTR pszFolder) CONST;

	BOOL FindTMPacketItem(HTREEITEM hItem) CONST;
	BOOL FindTCFunctionItem(HTREEITEM hItem) CONST;
	BOOL FindTMParameterItem(HTREEITEM hItem) CONST;
	BOOL FindTCParameterItem(HTREEITEM hItem) CONST;
	BOOL FindOBProcessorItem(HTREEITEM hItem) CONST;
	BOOL FindANDItem(HTREEITEM hItem) CONST;
	BOOL FindGRDItem(HTREEITEM hItem) CONST;
	BOOL FindMMDItem(HTREEITEM hItem) CONST;
	BOOL FindPODItem(HTREEITEM hItem) CONST;
	BOOL FindScriptItem(HTREEITEM hItem) CONST;
	BOOL FindItem(LPCTSTR pszItem, HTREEITEM hItem) CONST;

	BOOL CreateTMPacket();
	BOOL OpenTMPacket(HTREEITEM hItem);
	BOOL RenameTMPacket(HTREEITEM hItem);
	BOOL RenameTMPacket(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteTMPacket(HTREEITEM hItem);

	BOOL CreateTCFunction();
	BOOL OpenTCFunction(HTREEITEM hItem);
	BOOL RenameTCFunction(HTREEITEM hItem);
	BOOL RenameTCFunction(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteTCFunction(HTREEITEM hItem);

	BOOL CreateTMParameter();
	BOOL OpenTMParameter(HTREEITEM hItem);
	BOOL RenameTMParameter(HTREEITEM hItem);
	BOOL RenameTMParameter(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteTMParameter(HTREEITEM hItem);

	BOOL CreateTCParameter();
	BOOL OpenTCParameter(HTREEITEM hItem);
	BOOL RenameTCParameter(HTREEITEM hItem);
	BOOL RenameTCParameter(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteTCParameter(HTREEITEM hItem);

	BOOL CreateOBProcessor();
	BOOL OpenOBProcessor(HTREEITEM hItem);
	BOOL RenameOBProcessor(HTREEITEM hItem);
	BOOL RenameOBProcessor(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteOBProcessor(HTREEITEM hItem);

	BOOL CreateAND();
	BOOL OpenAND(HTREEITEM hItem);
	BOOL RenameAND(HTREEITEM hItem);
	BOOL RenameAND(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteAND(HTREEITEM hItem);

	BOOL CreateGRD();
	BOOL OpenGRD(HTREEITEM hItem);
	BOOL RenameGRD(HTREEITEM hItem);
	BOOL RenameGRD(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteGRD(HTREEITEM hItem);

	BOOL CreateMMD();
	BOOL OpenMMD(HTREEITEM hItem);
	BOOL RenameMMD(HTREEITEM hItem);
	BOOL RenameMMD(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteMMD(HTREEITEM hItem);

	BOOL CreatePOD();
	BOOL OpenPOD(HTREEITEM hItem);
	BOOL RenamePOD(HTREEITEM hItem);
	BOOL RenamePOD(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeletePOD(HTREEITEM hItem);

	BOOL CreateScript();
	BOOL OpenScript(HTREEITEM hItem);
	BOOL RenameScript(HTREEITEM hItem);
	BOOL RenameScript(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteScript(HTREEITEM hItem);

	BOOL IsDraggingDatabaseItem() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceViewDatabasePage)
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceViewDatabasePage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewProceduresPageToolTip window

// Specify the workspace view procedures page tool-tip timer related identifiers
#define WORKSPACEVIEWPROCEDURESPAGE_TOOLTIP_TIMERID   100
#define WORKSPACEVIEWPROCEDURESPAGE_TOOLTIP_TIMEOUT   5000

class CWorkspaceViewProceduresPageToolTip : public CWnd
{
	DECLARE_DYNCREATE(CWorkspaceViewProceduresPageToolTip)

	// Construction
public:
	CWorkspaceViewProceduresPageToolTip();

	// Attributes
private:
	CRect  m_rText;
	CString  m_szText;
	BOOL  m_bBoldText;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL ShowTip(CWnd *pParentWnd, LPCTSTR pszText, CONST RECT &rect, BOOL bBold);
	BOOL DeleteTip();

	class CWorkspaceViewProceduresPageTreeCtrl *GetParent() CONST;

private:
	VOID DrawContent(CDC *pDC);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceViewProceduresPageToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceViewProceduresPageToolTip)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewProceduresPageTreeCtrl window

class CWorkspaceViewProceduresPageTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNCREATE(CWorkspaceViewProceduresPageTreeCtrl)

	// Construction
public:
	CWorkspaceViewProceduresPageTreeCtrl();

	// Attributes
public:

	// Operations
public:
	VOID OpenProceduresItem(CONST POINT &ptItem);

	VOID ShowFloatingMenu(CONST POINT &ptItem);

	class CWorkspaceViewProceduresPage *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceViewProceduresPageTreeCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceViewProceduresPageTreeCtrl)
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewProceduresPage window

// Specify the workspace view procedures page item symbols
#define WORKSPACEPROCEDURESPAGE_ROOTSYMBOL   0
#define WORKSPACEPROCEDURESPAGE_ROOTNOSYMBOL   1
#define WORKSPACEPROCEDURESPAGE_FOLDERSYMBOL   2
#define WORKSPACEPROCEDURESPAGE_FOLDEROPENSYMBOL   3
#define WORKSPACEPROCEDURESPAGE_TCSEQUENCESYMBOL   4
#define WORKSPACEPROCEDURESPAGE_TCPROCEDURESYMBOL   5
#define WORKSPACEPROCEDURESPAGE_SYMBOLS   6

class CWorkspaceViewProceduresPage : public CWorkspaceViewPage
{
	DECLARE_DYNCREATE(CWorkspaceViewProceduresPage)

	// Construction
public:
	CWorkspaceViewProceduresPage();

	// Attributes
private:
	CString  m_szItem;
	HTREEITEM  m_hItem;
	CImageList  m_pItems;
	CWorkspaceViewProceduresPageToolTip  m_wndToolTip;
	CWorkspaceViewProceduresPageTreeCtrl  m_wndView;
private:
	UINT  m_nDragItem;
	BOOL  m_bDragItem;
	CString  m_szDragItem;
	CImageList  m_cDragItem;
private:
	INT  m_nCount[WORKSPACEPROCEDURESPAGE_SYMBOLS];
	UINT_PTR  m_nTimerID;

	// Operations
public:
	VOID UpdateDatabaseProcedures(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseProcedures(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseProcedures(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseProcedures();

	BOOL CreateProceduresItem();
	BOOL OpenProceduresItem();
	VOID OpenProceduresItem(CONST POINT &ptItem);
	BOOL HasProceduresItem(INT nType) CONST;
	BOOL RenameProceduresItem();
	BOOL DeleteProceduresItem();

	VOID ShowFloatingMenu(CONST POINT &ptItem);
	VOID ShowFloatingMenu(HTREEITEM hItem, CPoint point);
	VOID ShowFloatingMenu(HTREEITEM hItem, LPCTSTR pszItem, CPoint point);

	BOOL CanDeleteSel() CONST;
	VOID DoDeleteSel();

private:
	VOID EnumTCSequences(HTREEITEM hParentItem);
	VOID EnumTCProcedures(HTREEITEM hParentItem);

	HTREEITEM FindTCSequenceFolder() CONST;
	HTREEITEM FindTCProcedureFolder() CONST;
	HTREEITEM FindFolder(LPCTSTR pszFolder) CONST;

	BOOL FindTCSequenceItem(HTREEITEM hItem) CONST;
	BOOL FindTCProcedureItem(HTREEITEM hItem) CONST;
	BOOL FindItem(LPCTSTR pszItem, HTREEITEM hItem) CONST;

	BOOL CreateTCSequence();
	BOOL OpenTCSequence(HTREEITEM hItem);
	BOOL RenameTCSequence(HTREEITEM hItem);
	BOOL RenameTCSequence(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteTCSequence(HTREEITEM hItem);

	BOOL CreateTCProcedure();
	BOOL OpenTCProcedure(HTREEITEM hItem);
	BOOL RenameTCProcedure(HTREEITEM hItem);
	BOOL RenameTCProcedure(HTREEITEM hItem, LPCTSTR pszItem, CString &szItem);
	BOOL DeleteTCProcedure(HTREEITEM hItem);

	BOOL IsDraggingDatabaseItem() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceViewProceduresPage)
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceViewProceduresPage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewLogsPageToolTip window

// Specify the workspace view logs page tool-tip timer related identifiers
#define WORKSPACEVIEWLOGSPAGE_TOOLTIP_TIMERID   100
#define WORKSPACEVIEWLOGSPAGE_TOOLTIP_TIMEOUT   5000

class CWorkspaceViewLogsPageToolTip : public CWnd
{
	DECLARE_DYNCREATE(CWorkspaceViewLogsPageToolTip)

	// Construction
public:
	CWorkspaceViewLogsPageToolTip();

	// Attributes
private:
	CRect  m_rText;
	CString  m_szText;
	BOOL  m_bBoldText;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL ShowTip(CWnd *pParentWnd, LPCTSTR pszText, CONST RECT &rect, BOOL bBold);
	BOOL DeleteTip();

	class CWorkspaceViewLogsPageTreeCtrl *GetParent() CONST;

private:
	VOID DrawContent(CDC *pDC);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceViewLogsPageToolTip)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceViewLogsPageToolTip)
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewLogsPageTreeCtrl window

class CWorkspaceViewLogsPageTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNCREATE(CWorkspaceViewLogsPageTreeCtrl)

	// Construction
public:
	CWorkspaceViewLogsPageTreeCtrl();

	// Attributes
public:

	// Operations
public:
	class CWorkspaceViewLogsPage *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceViewLogsPageTreeCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceViewLogsPageTreeCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceViewLogsPage window

// Specify the workspace view logs page item symbols
#define WORKSPACELOGSPAGE_ROOTSYMBOL   0
#define WORKSPACELOGSPAGE_ROOTNOSYMBOL   1
#define WORKSPACELOGSPAGE_FOLDERSYMBOL   2
#define WORKSPACELOGSPAGE_FOLDEROPENSYMBOL   3
#define WORKSPACELOGSPAGE_ENTRYSYMBOL   4
#define WORKSPACELOGSPAGE_SYMBOLS   5

class CWorkspaceViewLogsPage : public CWorkspaceViewPage
{
	DECLARE_DYNCREATE(CWorkspaceViewLogsPage)

	// Construction
public:
	CWorkspaceViewLogsPage();

	// Attributes
private:
	CImageList  m_pItems;
	CWorkspaceViewLogsPageToolTip  m_wndToolTip;
	CWorkspaceViewLogsPageTreeCtrl  m_wndView;
private:
	CDatabaseLogs  m_pLogs;
private:
	typedef struct tagWORKSPACELOGENTRY {
		HTREEITEM  hItem;
		LPBYTE  pData;
	} WORKSPACELOGENTRY, *PWORKSPACELOGENTRY, *LPWORKSPACELOGENTRY;

	// Operations
public:
	VOID UpdateDatabaseLogs(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(ULONGLONG nComponent, LPCTSTR pszName = NULL);
	VOID UpdateDatabaseLogs();

private:
	VOID EnumTMPacketLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumTCFunctionLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumTCSequenceLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumTCProcedureLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumTMParameterLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumTCParameterLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumOBProcessorLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumANDLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumGRDLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumMMDLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumPODLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumScriptLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);
	VOID EnumLogs(HTREEITEM hParentItem, CONST CDatabaseLogs &pLogs);

	HTREEITEM FindTMPacketFolder() CONST;
	HTREEITEM FindTCFunctionFolder() CONST;
	HTREEITEM FindTCSequenceFolder() CONST;
	HTREEITEM FindTCProcedureFolder() CONST;
	HTREEITEM FindTMParameterFolder() CONST;
	HTREEITEM FindTCParameterFolder() CONST;
	HTREEITEM FindOBProcessorFolder() CONST;
	HTREEITEM FindANDFolder() CONST;
	HTREEITEM FindGRDFolder() CONST;
	HTREEITEM FindMMDFolder() CONST;
	HTREEITEM FindPODFolder() CONST;
	HTREEITEM FindScriptFolder() CONST;
	HTREEITEM FindFolder(LPCTSTR pszFolder) CONST;

	INT CalcLines(LPCTSTR pszName, LPCTSTR pszText, LPCTSTR pszUser) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceViewLogsPage)
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceViewLogsPage)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceView window

// Specify the workspace view page symbol identifiers
#define WORKSPACEVIEW_DATABASEPAGE_SYMBOL   0
#define WORKSPACEVIEW_PROCEDURESPAGE_SYMBOL   1
#define WORKSPACEVIEW_LOGSPAGE_SYMBOL   2
// Specify the workspace view frame size
#define WORKSPACEVIEW_FRAME_SIZE   6
#define WORKSPACEVIEW_TABBORDER_SIZE   3
// Specify the workspace view scroll bar and button control identifiers
#define WORKSPACEVIEW_SCROLLLEFT_BUTTON_ID   0
#define WORKSPACEVIEW_SCROLLRIGHT_BUTTON_ID   1
#define WORKSPACEVIEW_SCROLLBAR_ID   2
// Specify the workspace view scroll button identifiers
#define WORKSPACEVIEW_SCROLLLBUTTON_DEFAULT   0
#define WORKSPACEVIEW_SCROLLLBUTTON_PRESSED   1
#define WORKSPACEVIEW_SCROLLLBUTTON_DISABLED   2
#define WORKSPACEVIEW_SCROLLRBUTTON_DEFAULT   3
#define WORKSPACEVIEW_SCROLLRBUTTON_PRESSED   4
#define WORKSPACEVIEW_SCROLLRBUTTON_DISABLED   5
// Specify the workspace view scroll tabs timer related identifiers
#define WORKSPACEVIEW_SCROLL_TIMERID   0
#define WORKSPACEVIEW_SCROLL_TIMEOUT   500

class CWorkspaceView : public CWnd
{
	DECLARE_DYNCREATE(CWorkspaceView)

	// Construction
public:
	CWorkspaceView();

	// Attributes
private:
	INT  m_nPage;
	INT  m_nPagePos;
	UINT  m_nState[2];
	CFont  m_fntPages;
	CImage  m_cSymbol[3];
	CBitmap  m_bmpButton[6];
	CPtrArray  m_pwndPages;
	CStringArray  m_szPages;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	VOID SetCurPage(LPCTSTR pszPage);
	VOID SetCurPage(INT nPage);
	INT GetCurPage(CString &szPage) CONST;
	INT GetCurPage() CONST;

	VOID UpdateDatabaseContents(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents();

	VOID UpdateDatabaseProcedures(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseProcedures(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseProcedures(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseProcedures();

	VOID UpdateDatabaseLogs(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(ULONGLONG nComponent, LPCTSTR pszName = NULL);
	VOID UpdateDatabaseLogs();

	BOOL CreateDatabaseItem();
	BOOL OpenDatabaseItem();
	BOOL HasDatabaseItem(INT nType) CONST;
	BOOL RenameDatabaseItem();
	BOOL DeleteDatabaseItem();

	BOOL CreateProceduresItem();
	BOOL OpenProceduresItem();
	BOOL HasProceduresItem(INT nType) CONST;
	BOOL RenameProceduresItem();
	BOOL DeleteProceduresItem();

	BOOL CanDeleteSel() CONST;
	VOID DoDeleteSel();

	CWorkspaceViewDatabasePage *GetDatabasePage() CONST;
	CWorkspaceViewProceduresPage *GetProceduresPage() CONST;
	CWorkspaceViewLogsPage *GetLogsPage() CONST;

	VOID SetParent(class CWorkspaceWnd *pParentWnd);
	class CWorkspaceWnd *GetParent() CONST;

public:
	VOID CalcClientRect(LPRECT lpRect, BOOL bMargin = FALSE);

private:
	CWorkspaceViewPage *FindPage(LPCTSTR pszPage) CONST;

	CSize CalcTabsExtent();
	CSize CalcTabsExtent(CUIntArray &nTabsPos);
	CSize CalcTabExtent(INT nTab);

	CSize CalcScrollButtonSize() CONST;
	VOID CalcScrollLButtonPosition(LPRECT pRect);
	VOID CalcScrollRButtonPosition(LPRECT pRect);
	INT CalcScrollPosition();

	VOID DrawViewPages(CDC *pDC);
	VOID DrawScrollLButton(CDC *pDC);
	VOID DrawScrollLButton(CPoint point, UINT bPushed = -1);
	VOID DrawScrollRButton(CDC *pDC);
	VOID DrawScrollRButton(CPoint point, UINT bPushed = -1);

	BOOL IsPointOnScrollLButton(CPoint point);
	BOOL IsPointOnScrollRButton(CPoint point);
	UINT IsPointOnTab(CPoint point);

	BOOL IsScrollLButtonDown() CONST;
	BOOL IsScrollRButtonDown() CONST;
	BOOL IsScrollLButtonEnabled();
	BOOL IsScrollRButtonEnabled();

	VOID StartTabsScrolling();
	VOID ScrollTabs(BOOL bLeft = TRUE);
	VOID StopTabsScrolling();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceView)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CWorkspaceView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceWnd frame

// Specify the workspace window default settings
#define WORKSPACEWINDOW_DEFAULT_WIDTH   275

class CWorkspaceWnd : public CToolWnd
{
	DECLARE_DYNCREATE(CWorkspaceWnd)

	// Construction
public:
	CWorkspaceWnd(CWorkspaceWnd *pWorkspaceWnd = NULL);

	// Attributes
private:
	CWorkspaceView  *m_pwndView;

	// Operations
public:
	VOID SetPage(LPCTSTR pszPage);
	CString GetPage() CONST;

	VOID UpdateDatabaseContents(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseContents();

	VOID UpdateDatabaseProcedures(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseProcedures(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseProcedures(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseProcedures();

	VOID UpdateDatabaseLogs(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabaseLogs(ULONGLONG nComponent, LPCTSTR pszName = NULL);
	VOID UpdateDatabaseLogs();

	BOOL CreateDatabaseItem();
	BOOL OpenDatabaseItem();
	BOOL HasDatabaseItem(INT nType) CONST;
	BOOL RenameDatabaseItem();
	BOOL DeleteDatabaseItem();

	BOOL CreateProceduresItem();
	BOOL OpenProceduresItem();
	BOOL HasProceduresItem(INT nType) CONST;
	BOOL RenameProceduresItem();
	BOOL DeleteProceduresItem();

	BOOL CanDeleteSel() CONST;
	VOID DoDeleteSel();

	VOID Copy(CWorkspaceWnd *pWorkspaceWnd);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceWnd)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWorkspaceWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COutputViewScrollBar window

class COutputViewScrollBar : public CScrollBar
{
	DECLARE_DYNCREATE(COutputViewScrollBar)

	// Construction
public:
	COutputViewScrollBar();
	~COutputViewScrollBar();

	// Attributes
private:
	SCROLLINFO  m_sScrollInfo;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	VOID SetScrollInfo(CONST SCROLLINFO *pScrollInfo, BOOL bRedraw = TRUE);
	VOID GetScrollInfo(SCROLLINFO *pScrollInfo) CONST;

private:
	BOOL Lock();
	BOOL Unlock();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputViewScrollBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputViewScrollBar)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COutputViewBar window

// Specify the output view scroll bar and button control identifiers
#define OUTPUTVIEWBAR_SCROLLLEFT_BUTTON_ID   0
#define OUTPUTVIEWBAR_SCROLLRIGHT_BUTTON_ID   1
#define OUTPUTVIEWBAR_SCROLLBAR_ID   2
// Specify the output view scroll button identifiers
#define OUTPUTVIEWBAR_SCROLLLBUTTON_DEFAULT   0
#define OUTPUTVIEWBAR_SCROLLLBUTTON_PRESSED   1
#define OUTPUTVIEWBAR_SCROLLLBUTTON_DISABLED   2
#define OUTPUTVIEWBAR_SCROLLRBUTTON_DEFAULT   3
#define OUTPUTVIEWBAR_SCROLLRBUTTON_PRESSED   4
#define OUTPUTVIEWBAR_SCROLLRBUTTON_DISABLED   5
// Specify the output view scroll tabs shift interval
#define OUTPUTVIEWBAR_SCROLL_INTERVAL   20
// Specify the output view scroll tabs timer related identifiers
#define OUTPUTVIEWBAR_SCROLL_TIMERID   0
#define OUTPUTVIEWBAR_SCROLL_TIMEOUT   100
// Specify the output view split bar width
#define OUTPUTVIEWBAR_SPLITBAR_WIDTH   4

class COutputViewBar : public CWnd
{
	DECLARE_DYNCREATE(COutputViewBar)

	// Construction
public:
	COutputViewBar();

	// Attributes
private:
	INT  m_nTab;
	INT  m_nTabPos;
	INT  m_nSplitPos;
	BOOL  m_bSplitBar;
	UINT  m_nState[2];
	CFont  m_fntTabs;
	CBitmap  m_bmpButton[6];
	CUIntArray  m_nTabsPos;
	CStringArray  m_szTabs;
	COutputViewScrollBar  m_wndScrollBar;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, CStringArray &szTabs);

	VOID SetCurTab(INT nTab);
	INT GetCurTab() CONST;

	VOID SetScrollInfo(CONST SCROLLINFO *pScrollInfo);
	VOID GetScrollInfo(SCROLLINFO *pScrollInfo);

	class COutputView *GetParent() CONST;

private:
	CSize CalcExtent();
	CSize CalcTabsExtent() CONST;
	CSize CalcTabItemExtent(INT nItem);

	CSize CalcScrollExtent() CONST;
	CSize CalcScrollButtonSize() CONST;
	VOID CalcScrollLButtonPosition(LPRECT pRect) CONST;
	VOID CalcScrollRButtonPosition(LPRECT pRect) CONST;
	VOID CalcSplitBarPosition(LPRECT pRect) CONST;

	VOID AdjustSplitPosition();

	VOID DrawViewBar(CDC *pDC);
	VOID DrawScrollLButton(CDC *pDC);
	VOID DrawScrollLButton(CPoint point, UINT bPushed = -1);
	VOID DrawScrollRButton(CDC *pDC);
	VOID DrawScrollRButton(CPoint point, UINT bPushed = -1);

	BOOL IsPointOnScrollLButton(CPoint point) CONST;
	BOOL IsPointOnScrollRButton(CPoint point) CONST;
	BOOL IsPointOnSplitBar(CPoint point) CONST;
	UINT IsPointOnTab(CPoint point) CONST;

	BOOL IsScrollLButtonDown() CONST;
	BOOL IsScrollRButtonDown() CONST;
	BOOL IsScrollLButtonEnabled();
	BOOL IsScrollRButtonEnabled();

	VOID StartTabsScrolling();
	VOID ScrollTabs(BOOL bLeft = TRUE);
	VOID StopTabsScrolling();

	VOID StartSplitBarDragging();
	BOOL IsSplitBarDragged() CONST;
	VOID StopSplitBarDragging();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputViewBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputViewBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COutputViewConsoleWnd window

class COutputViewConsoleWnd : public CTextView
{
	DECLARE_DYNCREATE(COutputViewConsoleWnd)

	// Construction
public:
	COutputViewConsoleWnd();

	// Attributes
private:
	CRecentDocuments  m_pDocuments;
	CRecentDocumentInfo  m_cDocument;
private:
	SCROLLINFO  m_sScrollInfo[2];

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, CONST RECT &rect, BOOL bIndent = TRUE);

	VOID Activate();

	BOOL SetLine(INT nLine, LPCTSTR pszText);
	BOOL SetLine(INT nLine, LPCTSTR pszText, CONST CRecentDocumentInfo *pDocumentInfo);
	CString GetLine(INT nLine) CONST;
	CString GetLine(INT nLine, CRecentDocumentInfo *pDocumentInfo) CONST;
	BOOL InsertLine(INT nLine, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL);
	BOOL DeleteLine(INT nLine);
	BOOL SetCurLine(INT nLine);
	INT GetCurLine() CONST;
	INT GetLineCount() CONST;
	VOID ResetContent();

	BOOL SetContext(CONST CRecentDocumentInfo *pDocument);
	BOOL GetContext(CRecentDocumentInfo *pDocument) CONST;

	VOID SetScrollInfo(UINT nBar, CONST SCROLLINFO *pScrollInfo);
	VOID GetScrollInfo(UINT nBar, SCROLLINFO *pScrollInfo) CONST;

	class COutputView *GetParent() CONST;

private:
	VOID UpdateScrollBars();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputViewConsoleWnd)
public:
	virtual BOOL OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputViewConsoleWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COutputView window

class COutputView : public CWnd
{
	DECLARE_DYNCREATE(COutputView)

	// Construction
public:
	COutputView();

	// Attributes
private:
	CPtrArray  m_pwndConsoles;
	CStringArray  m_szConsoles;
	COutputViewBar  m_wndViewBar;
	COutputViewScrollBar  m_wndScrollBar;
private:
	CWnd  *m_pParentWnd;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd);

	VOID SetConsole(LPCTSTR pszConsole);
	VOID SetConsole(INT nConsole);
	INT GetConsole(CString &szConsole) CONST;
	INT GetConsole() CONST;

	BOOL SetLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText);
	BOOL SetLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText, CONST CRecentDocumentInfo *pDocumentInfo);
	CString GetLine(LPCTSTR pszConsole, INT nLine) CONST;
	CString GetLine(LPCTSTR pszConsole, INT nLine, CRecentDocumentInfo *pDocumentInfo) CONST;
	BOOL InsertLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL);
	BOOL DeleteLine(LPCTSTR pszConsole, INT nLine);
	BOOL SetCurLine(LPCTSTR pszConsole, INT nLine);
	INT GetCurLine(LPCTSTR pszConsole) CONST;
	INT GetLineCount(LPCTSTR pszConsole) CONST;
	VOID ResetContent(LPCTSTR pszConsole);
	VOID ResetAllContent();

	BOOL SetContext(LPCTSTR pszConsole, CONST CRecentDocumentInfo *pDocument);
	BOOL GetContext(LPCTSTR pszConsole, CRecentDocumentInfo *pDocument) CONST;

	BOOL StartBlinking(LPCTSTR pszConsole, INT nLine);
	BOOL StopBlinking(LPCTSTR pszConsole, INT nLine);

	VOID ScrollTo(UINT nBar, INT nPos);
	VOID ScrollTo(UINT nBar, UINT nCode);
	VOID ScrollUp(UINT nBar, BOOL bPage = FALSE);
	VOID ScrollDown(UINT nBar, BOOL bPage = FALSE);
	VOID SetScrollInfo(UINT nBar, CONST SCROLLINFO *pScrollInfo);
	VOID GetScrollInfo(UINT nBar, SCROLLINFO *pScrollInfo) CONST;

	VOID SetParent(class COutputWnd *pParentWnd);
	class COutputWnd *GetParent() CONST;

public:
	VOID CalcClientRect(LPRECT pRect) CONST;

private:
	COutputViewConsoleWnd *FindConsole() CONST;
	COutputViewConsoleWnd *FindConsole(LPCTSTR pszConsole) CONST;
	COutputViewConsoleWnd *FindConsoleIndex(INT nConsole) CONST;
	INT FindConsoleIndex(LPCTSTR pszConsole) CONST;

	VOID CalcViewBarRect(LPRECT pRect) CONST;
	VOID CalcScrollBarRect(LPRECT pRect) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputView)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// COutputWnd frame

// Specify the output window default settings
#define OUTPUTWINDOW_DEFAULT_HEIGHT   125

class COutputWnd : public CToolWnd
{
	DECLARE_DYNCREATE(COutputWnd)

	// Construction
public:
	COutputWnd(COutputWnd *pOutputWnd = NULL);

	// Attributes
private:
	COutputView  *m_pwndView;

	// Operations
public:
	VOID SetConsole(LPCTSTR pszConsole);
	CString GetConsole() CONST;

	BOOL SetLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText);
	BOOL SetLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText, CONST CRecentDocumentInfo *pDocumentInfo);
	CString GetLine(LPCTSTR pszConsole, INT nLine) CONST;
	CString GetLine(LPCTSTR pszConsole, INT nLine, CRecentDocumentInfo *pDocumentInfo) CONST;
	BOOL InsertLine(LPCTSTR pszConsole, INT nLine, LPCTSTR pszText, CONST CTextViewAttribute *pAttribute = NULL);
	BOOL DeleteLine(LPCTSTR pszConsole, INT nLine);
	BOOL SetCurLine(LPCTSTR pszConsole, INT nLine);
	INT GetCurLine(LPCTSTR pszConsole) CONST;
	INT GetLineCount(LPCTSTR pszConsole) CONST;
	VOID ResetContent(LPCTSTR pszConsole);
	VOID ResetAllContent();

	BOOL SetContext(LPCTSTR pszConsole, CONST CRecentDocumentInfo *pDocument);
	BOOL GetContext(LPCTSTR pszConsole, CRecentDocumentInfo *pDocument) CONST;

	BOOL StartBlinking(LPCTSTR pszConsole, INT nLine);
	BOOL StopBlinking(LPCTSTR pszConsole, INT nLine);

	VOID Copy(COutputWnd *pOutputWnd);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputWnd)
protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COutputWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CZoomWnd window

// Specify the zoom window default sizes
#define ZOOMWINDOW_SIZE_WIDTH   150
#define ZOOMWINDOW_SIZE_HEIGHT   150

class CZoomWnd : public CMiniFrameWnd
{
	DECLARE_DYNCREATE(CZoomWnd)

	// Construction
public:
	CZoomWnd();

	// Attributes
private:
	CRect  m_rDrag;
	CPoint  m_ptDrag;
	HCURSOR  m_hDragCursor;
	HCURSOR  m_hPointCursor;

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, LPCTSTR pszTitle, DWORD dwStyle, CONST RECT &rect, UINT nID = 0);

	VOID AdjustZoomFactor(CONST RECT &rect);

	VOID Connect();
	VOID Clear();

	class CMainWnd *GetParent() CONST;

private:
	VOID StartDragging(CONST POINT &point);
	VOID StopDragging();

	VOID DrawDraggingFrame(CONST RECT &rect);
	VOID DrawDraggingFrame(CONST POINT &point);

	VOID DrawHotSpot(CONST RECT &rect);

	CMMDWnd *GetZoomedWindow() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomWnd)
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoomWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainRibbonBar window

class CMainRibbonBar : public CMFCRibbonBar
{
	DECLARE_DYNCREATE(CMainRibbonBar)

	// Construction
public:
	CMainRibbonBar();

	// Attributes
private:
	BOOL  m_bFindDefaults[4];

	// Operations
public:
	VOID SetFindDefaults(BOOL bForward, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord, BOOL bToggle = FALSE);
	VOID GetFindDefaults(BOOL &bForward, BOOL &bSearchAll, BOOL &bMatchCase, BOOL &bMatchWord) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainRibbonBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainRibbonBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainRibbonButton

class CMainRibbonButton : public CMFCRibbonButton
{
	DECLARE_DYNCREATE(CMainRibbonButton)

	// Construction
public:
	CMainRibbonButton(UINT nID = 0, LPCTSTR pszText = NULL, HICON hIcon = NULL, HICON hSmallIcon = NULL);
	CMainRibbonButton(UINT nID, LPCTSTR pszText, INT nSmallImageIndex, INT nLargeImageIndex = -1, BOOL bDescription = FALSE);
	~CMainRibbonButton();

	// Attributes
private:
	HICON  m_hIcon[2];

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainRibbonBar)
public:
	virtual void OnDraw(CDC *pDC);
	virtual CSize GetImageSize(RibbonImageType type) const;
	virtual CSize GetIntermediateSize(CDC *pDC);
	virtual BOOL HasLargeMode() const;
protected:
	virtual void OnUpdateCmdUI(CMFCRibbonCmdUI *pCmdUI, CFrameWnd *pTarget, BOOL bDisableIfNoHndler);
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainMimicsObjectsToolBar

#define ID_MIMICSOBJECTS_TOOLBAR   (AFX_IDW_CONTROLBAR_LAST-1)

class CMainMimicsObjectsToolBar : public CMFCToolBar
{
	DECLARE_DYNCREATE(CMainMimicsObjectsToolBar)

	// Construction
public:
	CMainMimicsObjectsToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainMimicsObjectsToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainMimicsObjectsToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainTCStepsToolBar

#define ID_TCSTEPS_TOOLBAR   (AFX_IDW_CONTROLBAR_LAST-2)

class CMainTCStepsToolBar : public CMFCToolBar
{
	DECLARE_DYNCREATE(CMainTCStepsToolBar)

	// Construction
public:
	CMainTCStepsToolBar();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainTCStepsToolBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainTCStepsToolBar)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainStatusBarToolTipCtrl window

class CMainStatusBarToolTipCtrl : public CToolTipCtrl
{
	DECLARE_DYNCREATE(CMainStatusBarToolTipCtrl)

	// Construction
public:

	// Attributes
private:
	CString  m_szText;
	TOOLINFO  m_sInfo;

	// Operations
public:
	BOOL UpdateTipText(LPCTSTR pszText, CWnd *pWnd, UINT nToolID = 0);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainStatusBarToolTipCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainStatusBarToolTipCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainStatusBar window

// Specify the statusbar pane identifiers
#define ID_STATUSBAR_MESSAGEPANE   ID_SEPARATOR
#define ID_STATUSBAR_SERVERPANE   ID_STATUSBAR_PANE1
#define ID_STATUSBAR_SPACECRAFTPANE   ID_STATUSBAR_PANE2
#define ID_STATUSBAR_USERPANE   ID_STATUSBAR_PANE3
#define ID_STATUSBAR_DATABASEPANE   ID_STATUSBAR_PANE4
#define ID_STATUSBAR_CAPSKEYPANE   ID_STATUSBAR_PANE5
#define ID_STATUSBAR_NUMKEYPANE   ID_STATUSBAR_PANE6
#define ID_STATUSBAR_SCRLKEYPANE   ID_STATUSBAR_PANE7
#define ID_STATUSBAR_OVRKEYPANE   ID_STATUSBAR_PANE8

class CMainStatusBar : public CMFCStatusBar
{
	DECLARE_DYNCREATE(CMainStatusBar)

	// Construction
public:

	// Attributes
private:
	CFont  m_cPanesFont;
	CUIntArray  m_nPaneIDs;
private:
	CString  m_szToolTipText[4];
	CMainStatusBarToolTipCtrl  m_wndToolTip[8];

	// Operations
public:
	BOOL Create(CWnd *pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, UINT nID = AFX_IDW_STATUS_BAR);

	BOOL SetIndicators();
	BOOL SetIndicators(CONST UINT *pID, INT nSize);
	VOID SetIndicators(CONST CUIntArray &nPaneIDs);
	INT GetIndicators(CUIntArray &nPaneIDs) CONST;

	BOOL UpdateAllPanes();

	class CMainWnd *GetParent() CONST;

private:
	INT CalcPaneWidth(LPCTSTR pszText);

	VOID RecalcPanes();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainStatusBar)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainWnd frame

class CMainWnd : public CLocaleMDIFrameWnd
{
	DECLARE_DYNCREATE(CMainWnd)

	// Construction
public:
	CMainWnd();
	~CMainWnd();

	// Attributes
private:
	CMainRibbonBar  m_wndRibbonBar;
	CMainStatusBar  m_wndStatusBar;
	CMainMimicsObjectsToolBar  m_wndMimicsObjectsToolBar;
	CMainTCStepsToolBar  m_wndTCStepsToolBar;
private:
	CDisplayFrame  *m_pDisplayFrame;
	CPtrArray  m_pwndTools;
	CZoomWnd  *m_pZoomWnd;
private:
	CAboutDialog  m_dlgAbout;
	CNewDialog  m_dlgNewDocuments;
	COpenDialog  m_dlgOpenDocuments;
	CDatabaseOpenDialog  m_dlgDatabaseOpen;
	CDatabaseFindDialog  m_dlgDatabaseFind;
	CDatabaseUsersDialog  m_dlgDatabaseUsers;
	CDatabaseImportDialog  m_dlgDatabaseImport;
	CDatabaseExportDialog  m_dlgDatabaseExport;
	CDatabaseDeleteDialog  m_dlgDatabaseDelete;
	CDatabaseValidityDialog  m_dlgDatabaseValidity;
	CDatabasePrivilegesDialog  m_dlgDatabasePrivileges;
	CDatabaseVersioningDialog  m_dlgDatabaseVersioning;
	CPrintPagePrepareDialog  m_dlgPrintPagePrepare;
	CPrintPageSetupDialog  m_dlgPrintPageSetup;
	CCompileBatchesDialog  m_dlgCompileBatches;
	CCompileOptionsDialog  m_dlgCompileOptions;
	CCompileDirectivesDialog  m_dlgCompileDirectives;
	CDisplayWindowsDialog  m_dlgDisplayWindows;
private:
	CTMPacketOpenDialog  m_dlgOpenTMPacket;
	CTMPacketImportDialog  m_dlgImportTMPacket;
	CTMPacketExportDialog  m_dlgExportTMPacket;
private:
	CTCFunctionOpenDialog  m_dlgOpenTCFunction;
	CTCFunctionImportDialog  m_dlgImportTCFunction;
	CTCFunctionExportDialog  m_dlgExportTCFunction;
private:
	CTCSequenceOpenDialog  m_dlgOpenTCSequence;
	CTCSequenceImportDialog  m_dlgImportTCSequence;
	CTCSequenceExportDialog  m_dlgExportTCSequence;
private:
	CTCProcedureOpenDialog  m_dlgOpenTCProcedure;
	CTCProcedureImportDialog  m_dlgImportTCProcedure;
	CTCProcedureExportDialog  m_dlgExportTCProcedure;
private:
	CTMParameterOpenDialog  m_dlgOpenTMParameter;
	CTMParameterImportDialog  m_dlgImportTMParameter;
	CTMParameterExportDialog  m_dlgExportTMParameter;
private:
	CTCParameterOpenDialog  m_dlgOpenTCParameter;
	CTCParameterImportDialog  m_dlgImportTCParameter;
	CTCParameterExportDialog  m_dlgExportTCParameter;
private:
	COBProcessorOpenDialog  m_dlgOpenOBProcessor;
	COBProcessorImportDialog  m_dlgImportOBProcessor;
	COBProcessorExportDialog  m_dlgExportOBProcessor;
private:
	CANDOpenDialog  m_dlgOpenAND;
	CANDImportDialog  m_dlgImportAND;
	CANDExportDialog  m_dlgExportAND;
private:
	CGRDOpenDialog  m_dlgOpenGRD;
	CGRDImportDialog  m_dlgImportGRD;
	CGRDExportDialog  m_dlgExportGRD;
private:
	CMMDOpenDialog  m_dlgOpenMMD;
	CMMDImportDialog  m_dlgImportMMD;
	CMMDExportDialog  m_dlgExportMMD;
	CMMDCreateMimicsGroupDialog  m_dlgCreateMimicsGroup;
	CMMDInsertMimicsGroupDialog  m_dlgInsertMimicsGroup;
	CMMDDeleteMimicsGroupDialog  m_dlgDeleteMimicsGroup;
	CMMDImportMimicsGroupDialog  m_dlgImportMimicsGroup;
	CMMDExportMimicsGroupDialog  m_dlgExportMimicsGroup;
	CMMDRotateMimicsObjectDialog  m_dlgRotateMimicsObject;
private:
	CPODOpenDialog  m_dlgOpenPOD;
	CPODImportDialog  m_dlgImportPOD;
	CPODExportDialog  m_dlgExportPOD;
private:
	CScriptOpenDialog  m_dlgOpenScript;
	CScriptImportDialog  m_dlgImportScript;
	CScriptExportDialog  m_dlgExportScript;
private:
	CToolsOptionsDialog  m_dlgToolsOptions;
private:
	CRecentDocuments  m_pRecentDocuments;
	CRecentDatabases  m_pRecentDatabases;
	UINT  m_nRecentPrintJobs;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	VOID SaveEnvironment();
	VOID LoadEnvironment();

	BOOL SelectDatabase(BOOL bReset = FALSE);

	VOID UpdateDatabase(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(ULONGLONG nComponent, LPCTSTR pszName = NULL);
	VOID UpdateDatabase();

	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST COBProcessorWnd *pOBProcessorWnd, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST COBProcessorWnd *pOBProcessorWnd, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CANDWnd *pANDWnd, CONST CANDLayout *pLayout, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CGRDWnd *pGRDWnd, CONST CGRDLayout *pLayout, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CPODWnd *pPODWnd, CONST CPODLayout *pLayout, BOOL bDelete = FALSE);

	VOID SaveToolWindows();
	VOID ArrangeToolWindows();
	VOID ArrangeToolWindows(CToolWnd *pToolWnd, LPCRECT pRect);
	VOID DeleteToolWindows();

	INT EnumToolWindows(UINT nSide) CONST;
	INT EnumToolWindows(UINT nSide, CPtrArray &pwndTools) CONST;
	INT EnumToolWindows(CToolWnd *pToolWnd) CONST;
	INT EnumToolWindows(CToolWnd *pToolWnd, CPtrArray &pwndTools) CONST;
	INT EnumToolWindows(CToolWnd *pToolWnd, LPCRECT pRect, BOOL bAll = FALSE);
	INT EnumToolWindows(CToolWnd *pToolWnd, UINT nSide, LPCRECT pRect, BOOL bAll = FALSE);
	INT EnumToolWindows(CToolWnd *pToolWnd, LPCRECT pRect, BOOL bAll, CPtrArray &pwndTools);
	INT EnumToolWindows(CToolWnd *pToolWnd, UINT nSide, LPCRECT pRect, BOOL bAll, CPtrArray &pwndTools);

	VOID RegisterToolWindow(CToolWnd *pToolWnd);
	VOID UnregisterToolWindow(CToolWnd *pToolWnd);
	BOOL RepositionToolWindow(CToolWnd *pToolWnd, LPCRECT pRect);
	VOID DockToolWindow(CToolWnd *pToolWnd, LPCRECT pRect);
	INT FindToolWindow(CToolWnd *pToolWnd) CONST;
	CToolWnd *FindToolWindow(LPCTSTR pszTitle) CONST;
	VOID DestroyToolWindow(CToolWnd *pToolWnd);

	INT FindToolPane(UINT nSide, LPCRECT pRect) CONST;
	INT EnumToolPane(UINT nSide, INT nPane, CPtrArray &pwndTools) CONST;
	INT EnumToolPane(UINT nSide, INT nPane, LPRECT pRect, CPtrArray &pwndTools) CONST;
	INT EnumToolPane(UINT nSide, INT nPane, LPRECT pRect, INT &dx, INT &dy, CPtrArray &pwndTools) CONST;
	VOID RecalcToolPane(UINT nSide, LPCRECT prPane, CToolWnd *pWnd, LPCRECT prWnd, CONST CPtrArray &pwndTools);
	VOID RecalcToolPane(UINT nSide, LPCRECT prPane, INT dx, INT dy, CONST CPtrArray &pwndTools);
	INT GetToolPaneCount(UINT nSide, CUIntArray &nPanesPos) CONST;
	INT GetToolPaneCount(UINT nSide) CONST;

	VOID SaveDisplayWindows();
	VOID LoadDisplayWindows();
	INT EnumDisplayWindows() CONST;
	INT EnumDisplayWindows(CPtrArray &pDisplays) CONST;

	VOID ActivateDisplayWindow(CWnd *pWnd);
	CDisplayWnd *GetActiveDisplayWindow() CONST;

	VOID DoSelectAll();
	BOOL CanSelectAll() CONST;

	VOID DoUndo();
	BOOL CanUndo() CONST;
	VOID DoRedo();
	BOOL CanRedo() CONST;

	VOID DoFind();
	VOID DoFind(LPCTSTR pszQuery);
	BOOL CanFind() CONST;
	VOID DoFindNext();
	BOOL CanFindNext() CONST;
	VOID DoFindPrevious();
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

	VOID ActivateWindow(BOOL bNext = TRUE);
	VOID CloseWindow();
	VOID CloseAllWindows();

	BOOL ShowMessage(LPCTSTR pszMessage, BOOL bAudition = TRUE);
	BOOL ShowMessage(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition = TRUE);
	BOOL ResetMessages();

	BOOL SetConsoleContext(LPCTSTR pszConsole, CONST CRecentDocumentInfo *pDocument);
	BOOL GetConsoleContext(LPCTSTR pszConsole, CRecentDocumentInfo *pDocument) CONST;
	BOOL ShowConsoleText(LPCTSTR pszConsole, LPCTSTR pszText, BOOL bTimestamp = TRUE, BOOL bAudition = TRUE);
	BOOL ReadConsoleText(LPCTSTR pszConsole, CStringArray &szText, BOOL bTimestamp = TRUE, BOOL bAll = TRUE) CONST;
	INT AlertConsoleText(LPCTSTR pszConsole, LPCTSTR pszText, COLORREF nColor, BOOL bTimestamp = TRUE);
	BOOL AcknowledgeConsoleText(LPCTSTR pszConsole, INT nLine);
	BOOL ResetConsoleContent(LPCTSTR pszConsole);
	BOOL ResetAllConsoles();

	VOID SetFindDefaults(BOOL bForward, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord, BOOL bToggle = FALSE);
	VOID GetFindDefaults(BOOL &bForward, BOOL &bSearchAll, BOOL &bMatchCase, BOOL &bMatchWord) CONST;

	VOID UpdateBars();
	VOID UpdateBars(CDisplayWnd *pDisplayWnd, BOOL bActivate);
	VOID UpdateMenus();
	VOID UpdateMenus(CDisplayWnd *pDisplayWnd);
	VOID UpdateLayout();

	VOID AddMRUMenuItem(LPCTSTR pszName, LPCTSTR pszTitle, ULONGLONG nType);
	VOID AddMRUMenuItem(CONST CDatabaseProfileInfo *pDatabaseInfo);
	VOID RemoveMRUMenuItem(LPCTSTR pszName, LPCTSTR pszTitle, ULONGLONG nType);
	VOID RemoveMRUMenuItem(CONST CDatabaseProfileInfo *pDatabaseInfo);
	VOID UpdateMRUMenus();

	BOOL CheckKeyState(INT nVirtKey) CONST;

	BOOL IsCompiling() CONST;
	BOOL IsTesting() CONST;
	BOOL IsPrinting() CONST;

public:
	CDisplayFrame *GetDisplayFrame() CONST;

	CWorkspaceWnd *GetWorkspaceWindow() CONST;
	COutputWnd *GetOutputWindow() CONST;
	CZoomWnd *GetZoomWindow() CONST;

private:
	BOOL CreateRibbonBar();
	BOOL CreateToolBars();
	BOOL CreateStatusBar();
	BOOL CreateWorkspaceWindow();
	BOOL CreateOutputWindow();
	BOOL CreateZoomWindow();

	VOID UpdateTitle();
	VOID UpdateStatusBar();
	VOID UpdateWorkspaceWindow();
	VOID UpdateOutputWindow();

private:
	INT EnumMRUDocuments(CRecentDocuments &pRecentDocuments);
	INT EnumMRUDatabases(CRecentDatabases &pRecentDatabases);
	VOID SaveMRULists();
	VOID LoadMRULists();

	BOOL ShowPrintStatus(BOOL bPrinting);

	BOOL ShowBarMessage(INT nMessageID);

	UINT GetSubMenuState(CMenu *pMenu) CONST;

	VOID DoCleanDatabaseFiles();
	BOOL CanCleanDatabaseFiles() CONST;

	BOOL StartAssistant();
	VOID StopAssistant();

private:
	static BOOL CALLBACK EnumDisplayWindows(HWND hWnd, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainWnd)
public:
	virtual BOOL LoadFrame(UINT nResourceID, DWORD dwDefaultStyle);
	virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
	virtual CRect CalcClientRect(BOOL bFrame = TRUE) CONST;
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	virtual void GetMessageString(UINT nID, CString &szMessage) CONST;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL CanUpdateUI() CONST;
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT pcs, CCreateContext *pContext);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnEnterIdle(UINT nType, CWnd *pWnd);
	afx_msg void OnTimer(UINT_PTR nEventID);
	afx_msg LRESULT OnSystemSettingsChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOnlineHelp(WPARAM wParam, LPARAM lParam);
	afx_msg void OnNew();
	afx_msg void OnNewItemTMPacket();
	afx_msg void OnNewItemTCFunction();
	afx_msg void OnNewItemTCSequence();
	afx_msg void OnNewItemTCProcedure();
	afx_msg void OnNewItemTMParameter();
	afx_msg void OnNewItemTCParameter();
	afx_msg void OnNewItemOBProcessor();
	afx_msg void OnNewItemAND();
	afx_msg void OnNewItemGRD();
	afx_msg void OnNewItemMMD();
	afx_msg void OnNewItemPOD();
	afx_msg void OnNewItemScript();
	afx_msg void OnOpenItemTMPacket();
	afx_msg void OnOpenItemTCFunction();
	afx_msg void OnOpenItemTCSequence();
	afx_msg void OnOpenItemTCProcedure();
	afx_msg void OnOpenItemTMParameter();
	afx_msg void OnOpenItemTCParameter();
	afx_msg void OnOpenItemOBProcessor();
	afx_msg void OnOpenItemAND();
	afx_msg void OnOpenItemGRD();
	afx_msg void OnOpenItemMMD();
	afx_msg void OnOpenItemPOD();
	afx_msg void OnOpenItemScript();
	afx_msg void OnRenameItemTMPacket();
	afx_msg void OnRenameItemTCFunction();
	afx_msg void OnRenameItemTCSequence();
	afx_msg void OnRenameItemTCProcedure();
	afx_msg void OnRenameItemTMParameter();
	afx_msg void OnRenameItemTCParameter();
	afx_msg void OnRenameItemOBProcessor();
	afx_msg void OnRenameItemAND();
	afx_msg void OnRenameItemGRD();
	afx_msg void OnRenameItemMMD();
	afx_msg void OnRenameItemPOD();
	afx_msg void OnRenameItemScript();
	afx_msg void OnDeleteItemTMPacket();
	afx_msg void OnDeleteItemTCFunction();
	afx_msg void OnDeleteItemTCSequence();
	afx_msg void OnDeleteItemTCProcedure();
	afx_msg void OnDeleteItemTMParameter();
	afx_msg void OnDeleteItemTCParameter();
	afx_msg void OnDeleteItemOBProcessor();
	afx_msg void OnDeleteItemAND();
	afx_msg void OnDeleteItemGRD();
	afx_msg void OnDeleteItemMMD();
	afx_msg void OnDeleteItemPOD();
	afx_msg void OnDeleteItemScript();
	afx_msg void OnOpenTMPacket();
	afx_msg void OnImportTMPacket();
	afx_msg void OnExportTMPacket();
	afx_msg void OnOpenTCFunction();
	afx_msg void OnImportTCFunction();
	afx_msg void OnExportTCFunction();
	afx_msg void OnOpenTCSequence();
	afx_msg void OnImportTCSequence();
	afx_msg void OnExportTCSequence();
	afx_msg void OnOpenTCProcedure();
	afx_msg void OnImportTCProcedure();
	afx_msg void OnExportTCProcedure();
	afx_msg void OnOpenTMParameter();
	afx_msg void OnImportTMParameter();
	afx_msg void OnExportTMParameter();
	afx_msg void OnOpenTCParameter();
	afx_msg void OnImportTCParameter();
	afx_msg void OnExportTCParameter();
	afx_msg void OnOpenOBProcessor();
	afx_msg void OnImportOBProcessor();
	afx_msg void OnExportOBProcessor();
	afx_msg void OnCustomImportOBProcessor();
	afx_msg void OnCustomExportOBProcessor();
	afx_msg void OnCustomImportMemoryImage();
	afx_msg void OnCustomExportMemoryImage();
	afx_msg void OnOpenAND();
	afx_msg void OnImportAND();
	afx_msg void OnExportAND();
	afx_msg void OnOpenGRD();
	afx_msg void OnImportGRD();
	afx_msg void OnExportGRD();
	afx_msg void OnOpenMMD();
	afx_msg void OnImportMMD();
	afx_msg void OnExportMMD();
	afx_msg void OnOpenPOD();
	afx_msg void OnImportPOD();
	afx_msg void OnExportPOD();
	afx_msg void OnOpenScript();
	afx_msg void OnImportScript();
	afx_msg void OnExportScript();
	afx_msg void OnDatabaseNew();
	afx_msg void OnDatabaseOpen();
	afx_msg void OnDatabaseImport();
	afx_msg void OnDatabaseExport();
	afx_msg void OnDatabaseDelete();
	afx_msg void OnDatabaseVersioning();
	afx_msg void OnDocumentNew();
	afx_msg void OnDocumentOpen();
	afx_msg void OnDocumentSave();
	afx_msg void OnDocumentSaveAs();
	afx_msg void OnDocumentSaveAll();
	afx_msg void OnDocumentCheck();
	afx_msg void OnDocumentDelete();
	afx_msg void OnDocumentClose();
	afx_msg void OnPrintSetup();
	afx_msg void OnPrint();
	afx_msg void OnPrintSourceCode();
	afx_msg void OnPrintAllItems();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnEditFind();
	afx_msg void OnEditFindSearchForward();
	afx_msg void OnEditFindSearchAll();
	afx_msg void OnEditFindMatchCase();
	afx_msg void OnEditFindMatchWord();
	afx_msg void OnEditFindNext();
	afx_msg void OnEditFindPrevious();
	afx_msg void OnEditReplace();
	afx_msg void OnEditGoTo();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditDelete();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditSaveTable();
	afx_msg void OnEditCheckTable();
	afx_msg void OnEditDeleteTable();
	afx_msg void OnEditImportTables();
	afx_msg void OnEditExportTables();
	afx_msg void OnEditPrintTable();
	afx_msg void OnEditPrintAllTables();
	afx_msg void OnEditInsertTableRowAbove();
	afx_msg void OnEditInsertTableRowBelow();
	afx_msg void OnEditInsertTableColumnBefore();
	afx_msg void OnEditInsertTableColumnAfter();
	afx_msg void OnEditClearTableRow();
	afx_msg void OnEditDeleteTableRow();
	afx_msg void OnEditDeleteTableColumn();
	afx_msg void OnEditCopyTableRow();
	afx_msg void OnEditPasteTableRow();
	afx_msg void OnEditDiscardAllTables();
	afx_msg void OnEditDiscardTables();
	afx_msg void OnEditResetTables();
	afx_msg void OnEditCreateMimicsGroup();
	afx_msg void OnEditDeleteMimicsGroup();
	afx_msg void OnEditCollectMimicsGroup();
	afx_msg void OnEditDiscardMimicsGroup();
	afx_msg void OnEditStepIntoMimicsGroup();
	afx_msg void OnEditStepOutMimicsGroup();
	afx_msg void OnEditImportMimicsGroup();
	afx_msg void OnEditExportMimicsGroup();
	afx_msg void OnEditHorzAlignMimicsObjects();
	afx_msg void OnEditVertAlignMimicsObjects();
	afx_msg void OnEditMoveMimicsObjectToTop();
	afx_msg void OnEditMoveMimicsObjectToBottom();
	afx_msg void OnEditMoveMimicsObjectUp();
	afx_msg void OnEditMoveMimicsObjectDown();
	afx_msg void OnEditShowHideMimicsObject();
	afx_msg void OnEditHorzFlipMimicsObject();
	afx_msg void OnEditVertFlipMimicsObject();
	afx_msg void OnEditRotateMimicsObject();
	afx_msg void OnEditTurnMimicsObject();
	afx_msg void OnViewMimicsObjectProperties();
	afx_msg void OnViewMimicsObjectItem();
	afx_msg void OnViewMimicsObjectCode();
	afx_msg void OnProperties();
	afx_msg void OnSourceCode();
	afx_msg void OnLinkInformation();
	afx_msg void OnWorkspaceWindow();
	afx_msg void OnOutputWindow();
	afx_msg void OnZoomWindow();
	afx_msg void OnMimicsObjectsToolBar();
	afx_msg void OnMimicsObjects(UINT nID);
	afx_msg void OnMimicsGroup();
	afx_msg void OnTCStepsToolBar();
	afx_msg void OnTCSteps(UINT nID);
	afx_msg void OnBuildOptions();
	afx_msg void OnBuildDirectives();
	afx_msg void OnBuildDownload();
	afx_msg void OnBuildCompile();
	afx_msg void OnBuildCompileAll();
	afx_msg void OnBuildCompileBatches();
	afx_msg void OnBuildCompileStop();
	afx_msg void OnBuildClean();
	afx_msg void OnBuildTest();
	afx_msg void OnBuildTestBreak();
	afx_msg void OnBuildTestContinue();
	afx_msg void OnBuildTestStepInto();
	afx_msg void OnBuildTestStepOver();
	afx_msg void OnBuildTestStepOut();
	afx_msg void OnBuildTestStop();
	afx_msg void OnBuildTestReset();
	afx_msg void OnToolsOptions();
	afx_msg void OnUsers();
	afx_msg void OnPrivileges();
	afx_msg void OnValidity();
	afx_msg void OnNextWindow();
	afx_msg void OnPreviousWindow();
	afx_msg void OnCloseWindow();
	afx_msg void OnCloseAllWindows();
	afx_msg void OnWindows();
	afx_msg void OnAssistantSupportDateConversions();
	afx_msg void OnAssistantListen();
	afx_msg void OnMRUDocument(UINT nID);
	afx_msg void OnMRUDatabase(UINT nID);
	afx_msg void OnAbout();
	afx_msg void OnHelp();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemTMPacket(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemTCFunction(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemTCSequence(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemTCProcedure(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemTMParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemTCParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemOBProcessor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemAND(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemGRD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemMMD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemPOD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewItemScript(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemTMPacket(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemTCFunction(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemTCSequence(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemTCProcedure(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemTMParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemTCParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemOBProcessor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemAND(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemGRD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemMMD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemPOD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenItemScript(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemTMPacket(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemTCFunction(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemTCSequence(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemTCProcedure(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemTMParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemTCParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemOBProcessor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemAND(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemGRD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemMMD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemPOD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenameItemScript(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemTMPacket(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemTCFunction(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemTCSequence(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemTCProcedure(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemTMParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemTCParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemOBProcessor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemAND(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemGRD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemMMD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemPOD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteItemScript(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenTMPacket(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportTMPacket(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportTMPacket(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenTCFunction(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportTCFunction(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportTCFunction(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenTCSequence(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportTCSequence(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportTCSequence(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenTCProcedure(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportTCProcedure(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportTCProcedure(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenTMParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportTMParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportTMParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenTCParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportTCParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportTCParameter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenOBProcessor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportOBProcessor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportOBProcessor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCustomImportOBProcessor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCustomExportOBProcessor(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCustomImportMemoryImage(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCustomExportMemoryImage(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenAND(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportAND(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportAND(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenGRD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportGRD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportGRD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenMMD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportMMD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportMMD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenPOD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportPOD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportPOD(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpenScript(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImportScript(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExportScript(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDatabaseNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDatabaseOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDatabaseImport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDatabaseExport(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDatabaseDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDatabaseVersioning(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDocumentNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDocumentOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDocumentSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDocumentSaveAs(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDocumentSaveAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDocumentCheck(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDocumentDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDocumentClose(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrintSetup(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrint(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrintSourceCode(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrintAllItems(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMRUDocuments(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMRUDatabases(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditFind(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditFindSearchForward(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditFindSearchAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditFindMatchCase(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditFindMatchWord(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditFindNext(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditFindPrevious(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditReplace(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditGoTo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditDelete(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditSelectAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditSaveTable(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditCheckTable(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditDeleteTable(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditImportTables(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditExportTables(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditPrintTable(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditPrintAllTables(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditInsertTableRowAbove(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditInsertTableRowBelow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditInsertTableColumnBefore(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditInsertTableColumnAfter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditClearTableRow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditDeleteTableRow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditDeleteTableColumn(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditCopyTableRow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditPasteTableRow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditDiscardAllTables(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditDiscardTables(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditResetTables(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditCreateMimicsGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditDeleteMimicsGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditCollectMimicsGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditDiscardMimicsGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditStepIntoMimicsGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditStepOutMimicsGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditImportMimicsGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditExportMimicsGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditHorzAlignMimicsObjects(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditVertAlignMimicsObjects(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditMoveMimicsObjectToTop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditMoveMimicsObjectToBottom(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditMoveMimicsObjectUp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditMoveMimicsObjectDown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditShowHideMimicsObject(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditHorzFlipMimicsObject(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditVertFlipMimicsObject(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditRotateMimicsObject(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditTurnMimicsObject(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewMimicsObjectProperties(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewMimicsObjectItem(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewMimicsObjectCode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProperties(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSourceCode(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLinkInformation(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWorkspaceWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOutputWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZoomWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMimicsObjectsToolBar(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMimicsObjectsMenu(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMimicsObjects(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMimicsGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCStepsToolBar(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCStepsMenu(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCSteps(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTCStepBreakpointOptions(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildOptions(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildDirectives(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildDownload(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildCompile(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildCompileAll(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildCompileBatches(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildCompileStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildClean(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildTest(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildTestBreak(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildTestContinue(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildTestStepInto(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildTestStepOver(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildTestStepOut(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildTestStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBuildTestReset(CCmdUI *pCmdUI);
	afx_msg void OnUpdateToolsOptions(CCmdUI *pCmdUI);
	afx_msg void OnUpdateUsers(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePrivileges(CCmdUI *pCmdUI);
	afx_msg void OnUpdateValidity(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNextWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePreviousWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCloseWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCloseAllWindows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateWindows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDisplayWindows(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDisplayWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAssistantSupportDateConversions(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAssistantListen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMRUDocument(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMRUDatabase(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarServerPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarSpacecraftPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarUserPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarDatabasePane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarCAPSKeyPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarNUMKeyPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarSCRLKeyPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStatusBarOVRKeyPane(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAbout(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHelp(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExit(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEditorAppCommandLineInfo

class CEditorAppCommandLineInfo : public CCommandLineInfo
{
	// Constructors
public:
	CEditorAppCommandLineInfo();

	// Attributes
private:
	CAccountToken  m_cAccountToken;
	BOOL  m_bServer;
	BOOL  m_bSpacecraft;
	BOOL  m_bDatabase;
	BOOL  m_bPassword;
	BOOL  m_bUser;

	// Operations
public:
	CString GetServer() CONST;
	CString GetSpacecraft() CONST;
	CString GetDatabase() CONST;
	CString GetPassword() CONST;
	CString GetUser() CONST;

	BOOL IsValid() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditorAppCommandLineInfo)
	virtual void ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast);
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CEditorApp application

class CEditorApp : public CAccountsApp
{
	DECLARE_DYNAMIC(CEditorApp)

	// Construction
public:
	CEditorApp();
	~CEditorApp();

	// Attributes
private:
	CSourceDatabase  *m_pDatabase;
private:
	CNetworkBrowseService  *m_pNetworkBrowseService;
private:
	CPrintProfileInfo  m_cPrintProfile;
	CDefaultPrinter  m_cDefaultPrinter;

	// Operations
public:
	BOOL SetDatabase();
	BOOL SetDatabase(LPCTSTR pszSpacecraft);
	BOOL SetDatabase(LPCTSTR pszSpacecraft, LPCTSTR pszDatabase);
	BOOL SetDatabase(LPCTSTR pszServer, LPCTSTR pszSpacecraft, LPCTSTR pszDatabase, BOOL bLoad = TRUE, BOOL bBinary = TRUE);
	CSourceDatabase *GetDatabase() CONST;

	VOID UpdateDatabase(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete = FALSE);
	VOID UpdateDatabase(ULONGLONG nComponent, LPCTSTR pszName = NULL);
	VOID UpdateDatabase();

	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST COBProcessorWnd *pOBProcessorWnd, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST COBProcessorWnd *pOBProcessorWnd, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CANDWnd *pANDWnd, CONST CANDLayout *pLayout, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CGRDWnd *pGRDWnd, CONST CGRDLayout *pLayout, BOOL bDelete = FALSE);
	VOID UpdateForms(CONST CPODWnd *pPODWnd, CONST CPODLayout *pLayout, BOOL bDelete = FALSE);

	BOOL CreateDatabaseItem();
	BOOL OpenDatabaseItem();
	BOOL HasDatabaseItem(INT nType) CONST;
	BOOL RenameDatabaseItem();
	BOOL DeleteDatabaseItem();

	BOOL CreateProceduresItem();
	BOOL OpenProceduresItem();
	BOOL HasProceduresItem(INT nType) CONST;
	BOOL RenameProceduresItem();
	BOOL DeleteProceduresItem();

	INT EnumDisplayWindows();
	INT EnumDisplayWindows(CPtrArray &pDisplays);

	VOID ActivateDisplayWindow(CWnd *pWnd);
	CDisplayWnd *GetActiveDisplayWindow() CONST;

	BOOL ShowMessage(LPCTSTR pszMessage, BOOL bAudition = TRUE);
	BOOL ShowMessage(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition = TRUE);
	BOOL ResetMessages();

	BOOL SetConsoleContext(LPCTSTR pszConsole, CONST CRecentDocumentInfo *pDocument);
	BOOL GetConsoleContext(LPCTSTR pszConsole, CRecentDocumentInfo *pDocument);
	BOOL ShowConsoleText(LPCTSTR pszConsole, LPCTSTR pszText, BOOL bTimestamp = TRUE, BOOL bAudition = TRUE);
	BOOL ReadConsoleText(LPCTSTR pszConsole, CStringArray &szText, BOOL bTimestamp = TRUE, BOOL bAll = TRUE);
	INT AlertConsoleText(LPCTSTR pszConsole, LPCTSTR pszText, COLORREF nColor, BOOL bTimestamp = TRUE);
	BOOL AcknowledgeConsoleText(LPCTSTR pszConsole, INT nLine);
	BOOL ResetConsoleContent(LPCTSTR pszConsole);
	BOOL ResetAllConsoles();

	VOID SetFindDefaults(BOOL bForward, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord, BOOL bToggle = FALSE);
	VOID GetFindDefaults(BOOL &bForward, BOOL &bSearchAll, BOOL &bMatchCase, BOOL &bMatchWord) CONST;

	VOID SaveProfiles();
	VOID LoadProfiles();
	BOOL SetCompileBatchProfiles(CONST CCompileBatches &pBatches);
	BOOL GetCompileBatchProfiles(CCompileBatches &pBatches);
	BOOL SetPrintProfile(CONST CPrintProfileInfo &cProfileInfo);
	BOOL GetPrintProfile(CPrintProfileInfo &cProfileInfo);

	BOOL InitializeDefaultPrinter();
	BOOL IsDefaultPrinterAvailable() CONST;
	BOOL SetDefaultPrinterInfo(CONST PAGESETUPDLG *pPrinterInfo);
	BOOL GetDefaultPrinterInfo(PAGESETUPDLG *pPrinterInfo);
	BOOL CreatePrinterDC(CONST CPrintProfileInfo *pProfileInfo, CDC &cDC);
	BOOL CreatePrinterDC(HANDLE hDevNames, HANDLE hDevMode, CDC &cDC);

	BOOL IsCompiling() CONST;
	BOOL IsTesting() CONST;
	BOOL IsPrinting() CONST;

	BOOL CheckDatabasePrivilege(UINT nPrivilege);

	BOOL ShowHelp(LPCTSTR pszTopic = NULL);
	BOOL IsHelpAvailable() CONST;

public:
	CNetworkBrowseService *GetNetworkBrowseService() CONST;

	CDisplayFrame *GetDisplayFrame() CONST;

	CMainWnd *GetMainWnd() CONST;

private:
	INT RegisterApp();
	BOOL UnregisterApp();

	BOOL RunAccount(CONST CEditorAppCommandLineInfo &cStartupInfo);
	BOOL EvaluateAccount(CONST CEditorAppCommandLineInfo &cStartupInfo);

	BOOL StartNetworkBrowseService();
	BOOL StopNetworkBrowseService();

	BOOL SaveCompileBatchProfiles();
	BOOL LoadCompileBatchProfiles();
	BOOL SavePrintProfile();
	BOOL LoadPrintProfile();

public:
	static BOOL CALLBACK ReportID(CONST EVENT_DESCRIPTOR nMessageID);
	static BOOL CALLBACK ReportMessage(LPCTSTR pszMessage, BOOL bAudition);

	static BOOL CALLBACK HelpTopic(LPCTSTR pszTopic);

	static BOOL CALLBACK EnumTopLevelWindows(HWND hWnd, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditorApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL SaveState(LPCTSTR lpszSectionName = (LPCTSTR)NULL, CFrameImpl *pFrameImpl = (CFrameImpl *)NULL);
	virtual BOOL LoadState(LPCTSTR lpszSectionName = (LPCTSTR)NULL, CFrameImpl *pFrameImpl = (CFrameImpl *)NULL);
	virtual BOOL PreTranslateMessage(MSG *pMsg);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditorApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline CEditorApp *GetEditorApp()
{
	return((CEditorApp *)AfxGetApp());
}
inline BOOL SetDatabase()
{
	return(GetEditorApp()->SetDatabase());
}
inline BOOL SetDatabase(LPCTSTR pszSpacecraft)
{
	return(GetEditorApp()->SetDatabase(pszSpacecraft));
}
inline BOOL SetDatabase(LPCTSTR pszSpacecraft, LPCTSTR pszDatabase)
{
	return(GetEditorApp()->SetDatabase(pszSpacecraft, pszDatabase));
}
inline BOOL SetDatabase(LPCTSTR pszServer, LPCTSTR pszSpacecraft, LPCTSTR pszDatabase, BOOL bLoad = TRUE, BOOL bBinary = TRUE)
{
	return(GetEditorApp()->SetDatabase(pszServer, pszSpacecraft, pszDatabase, bLoad, bBinary));
}
inline CSourceDatabase *GetDatabase()
{
	return(GetEditorApp()->GetDatabase());
}
inline VOID UpdateDatabase(CONST CDatabaseTMPacket *pDatabaseTMPacket, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pDatabaseTMPacket, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CDatabaseTCFunction *pDatabaseTCFunction, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pDatabaseTCFunction, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CDatabaseTCSequence *pDatabaseTCSequence, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pDatabaseTCSequence, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CDatabaseTCProcedure *pDatabaseTCProcedure, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pDatabaseTCProcedure, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CDatabaseOBProcessor *pDatabaseOBProcessor, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pDatabaseOBProcessor, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CDatabaseTMParameter *pDatabaseTMParameter, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pDatabaseTMParameter, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CDatabaseTCParameter *pDatabaseTCParameter, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pDatabaseTCParameter, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CTCSequenceWnd *pTCSequenceWnd, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pTCSequenceWnd, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CANDWnd *pANDWnd, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pANDWnd, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CGRDWnd *pGRDWnd, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pGRDWnd, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CMMDWnd *pMMDWnd, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pMMDWnd, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CPODWnd *pPODWnd, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pPODWnd, nPosition, bDelete));
}
inline VOID UpdateDatabase(CONST CScriptWnd *pScriptWnd, INT nPosition, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateDatabase(pScriptWnd, nPosition, bDelete));
}
inline VOID UpdateDatabase(ULONGLONG nComponent, LPCTSTR pszName)
{
	return(GetEditorApp()->UpdateDatabase(nComponent, pszName));
}
inline VOID UpdateDatabase()
{
	return(GetEditorApp()->UpdateDatabase());
}
inline VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacket *pDatabaseTMPacket, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMPacketWnd, pDatabaseTMPacket, bDelete));
}
inline VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketIdentification *pDatabaseTMPacketIdentification, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMPacketWnd, pDatabaseTMPacketIdentification, bDelete));
}
inline VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketIdentificationCriterion *pDatabaseTMPacketIdentificationCriterion, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMPacketWnd, pDatabaseTMPacketIdentificationCriterion, bDelete));
}
inline VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketHeader *pDatabaseTMPacketHeader, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMPacketWnd, pDatabaseTMPacketHeader, bDelete));
}
inline VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketStream *pDatabaseTMPacketStream, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMPacketWnd, pDatabaseTMPacketStream, bDelete));
}
inline VOID UpdateForms(CONST CTMPacketWnd *pTMPacketWnd, CONST CDatabaseTMPacketGroup *pDatabaseTMPacketGroup, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMPacketWnd, pDatabaseTMPacketGroup, bDelete));
}
inline VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCFunction *pDatabaseTCFunction, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCFunctionWnd, pDatabaseTCFunction, bDelete));
}
inline VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPacket *pDatabaseTCPacket, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCFunctionWnd, pDatabaseTCPacket, bDelete));
}
inline VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPacketParameter *pDatabaseTCPacketParameter, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCFunctionWnd, pDatabaseTCPacketParameter, bDelete));
}
inline VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCPreExeGroup *pDatabaseTCPreExeGroup, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCFunctionWnd, pDatabaseTCPreExeGroup, bDelete));
}
inline VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCExeVerStage *pDatabaseTCExeVerStage, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCFunctionWnd, pDatabaseTCExeVerStage, bDelete));
}
inline VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCExeVerGroup *pDatabaseTCExeVerGroup, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCFunctionWnd, pDatabaseTCExeVerGroup, bDelete));
}
inline VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCFunctionWnd, pDatabaseTCParameterSet, bDelete));
}
inline VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCFunctionWnd, pDatabaseTCParameterValueSet, bDelete));
}
inline VOID UpdateForms(CONST CTCFunctionWnd *pTCFunctionWnd, CONST CDatabaseTCFunctionRoutingPath *pDatabaseTCFunctionRoutingPath, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCFunctionWnd, pDatabaseTCFunctionRoutingPath, bDelete));
}
inline VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCSequence *pDatabaseTCSequence, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCSequenceWnd, pDatabaseTCSequence, bDelete));
}
inline VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCFunctionBlock *pDatabaseTCFunctionBlock, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCSequenceWnd, pDatabaseTCFunctionBlock, bDelete));
}
inline VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCParameterSet *pDatabaseTCParameterSet, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCSequenceWnd, pDatabaseTCParameterSet, bDelete));
}
inline VOID UpdateForms(CONST CTCSequenceWnd *pTCSequenceWnd, CONST CDatabaseTCParameterValueSet *pDatabaseTCParameterValueSet, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCSequenceWnd, pDatabaseTCParameterValueSet, bDelete));
}
inline VOID UpdateForms(CONST COBProcessorWnd *pOBProcessorWnd, CONST CDatabaseOBProcessor *pDatabaseOBProcessor, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pOBProcessorWnd, pDatabaseOBProcessor, bDelete));
}
inline VOID UpdateForms(CONST COBProcessorWnd *pOBProcessorWnd, CONST CDatabaseOBProcessorMemoryImage *pDatabaseOBProcessorMemoryImage, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pOBProcessorWnd, pDatabaseOBProcessorMemoryImage, bDelete));
}
inline VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMParameter *pDatabaseTMParameter, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMParameterWnd, pDatabaseTMParameter, bDelete));
}
inline VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMNumCalTable *pDatabaseTMNumCalTable, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMParameterWnd, pDatabaseTMNumCalTable, bDelete));
}
inline VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMTxtCalTable *pDatabaseTMTxtCalTable, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMParameterWnd, pDatabaseTMTxtCalTable, bDelete));
}
inline VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMNumOolTable *pDatabaseTMNumOolTable, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMParameterWnd, pDatabaseTMNumOolTable, bDelete));
}
inline VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMTxtOolTable *pDatabaseTMTxtOolTable, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMParameterWnd, pDatabaseTMTxtOolTable, bDelete));
}
inline VOID UpdateForms(CONST CTMParameterWnd *pTMParameterWnd, CONST CDatabaseTMParameterGroup *pDatabaseTMParameterGroup, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTMParameterWnd, pDatabaseTMParameterGroup, bDelete));
}
inline VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCParameter *pDatabaseTCParameter, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCParameterWnd, pDatabaseTCParameter, bDelete));
}
inline VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCNumCalTable *pDatabaseTCNumCalTable, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCParameterWnd, pDatabaseTCNumCalTable, bDelete));
}
inline VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCTxtCalTable *pDatabaseTCTxtCalTable, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCParameterWnd, pDatabaseTCTxtCalTable, bDelete));
}
inline VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCNumOolTable *pDatabaseTCNumOolTable, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCParameterWnd, pDatabaseTCNumOolTable, bDelete));
}
inline VOID UpdateForms(CONST CTCParameterWnd *pTCParameterWnd, CONST CDatabaseTCTxtOolTable *pDatabaseTCTxtOolTable, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pTCParameterWnd, pDatabaseTCTxtOolTable, bDelete));
}
inline VOID UpdateForms(CONST CANDWnd *pANDWnd, CONST CANDLayout *pLayout, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pANDWnd, pLayout, bDelete));
}
inline VOID UpdateForms(CONST CGRDWnd *pGRDWnd, CONST CGRDLayout *pLayout, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pGRDWnd, pLayout, bDelete));
}
inline VOID UpdateForms(CONST CPODWnd *pPODWnd, CONST CPODLayout *pLayout, BOOL bDelete = FALSE)
{
	return(GetEditorApp()->UpdateForms(pPODWnd, pLayout, bDelete));
}
inline BOOL CreateDatabaseItem()
{
	return(GetEditorApp()->CreateDatabaseItem());
}
inline BOOL OpenDatabaseItem()
{
	return(GetEditorApp()->OpenDatabaseItem());
}
inline BOOL HasDatabaseItem(INT nType)
{
	return(GetEditorApp()->HasDatabaseItem(nType));
}
inline BOOL RenameDatabaseItem()
{
	return(GetEditorApp()->RenameDatabaseItem());
}
inline BOOL DeleteDatabaseItem()
{
	return(GetEditorApp()->DeleteDatabaseItem());
}
inline BOOL CreateProceduresItem()
{
	return(GetEditorApp()->CreateProceduresItem());
}
inline BOOL OpenProceduresItem()
{
	return(GetEditorApp()->OpenProceduresItem());
}
inline BOOL HasProceduresItem(INT nType)
{
	return(GetEditorApp()->HasProceduresItem(nType));
}
inline BOOL RenameProceduresItem()
{
	return(GetEditorApp()->RenameProceduresItem());
}
inline BOOL DeleteProceduresItem()
{
	return(GetEditorApp()->DeleteProceduresItem());
}
inline INT EnumDisplayWindows()
{
	return(GetEditorApp()->EnumDisplayWindows());
}
inline INT EnumDisplayWindows(CPtrArray &pDisplays)
{
	return(GetEditorApp()->EnumDisplayWindows(pDisplays));
}
inline VOID ActivateDisplayWindow(CWnd *pWnd)
{
	return(GetEditorApp()->ActivateDisplayWindow(pWnd));
}
inline CDisplayWnd *GetActiveDisplayWindow()
{
	return(GetEditorApp()->GetActiveDisplayWindow());
}
inline BOOL ShowMessage(LPCTSTR pszMessage, BOOL bAudition = TRUE)
{
	return(GetEditorApp()->ShowMessage(pszMessage, bAudition));
}
inline BOOL ShowMessage(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition = TRUE)
{
	return(GetEditorApp()->ShowMessage(sEvent, bAudition));
}
inline BOOL ResetMessages()
{
	return(GetEditorApp()->ResetMessages());
}
inline BOOL SetConsoleContext(LPCTSTR pszConsole, CONST CRecentDocumentInfo *pDocument)
{
	return(GetEditorApp()->SetConsoleContext(pszConsole, pDocument));
}
inline BOOL GetConsoleContext(LPCTSTR pszConsole, CRecentDocumentInfo *pDocument)
{
	return(GetEditorApp()->GetConsoleContext(pszConsole, pDocument));
}
inline BOOL ShowConsoleText(LPCTSTR pszConsole, LPCTSTR pszText, BOOL bTimestamp = TRUE, BOOL bAudition = TRUE)
{
	return(GetEditorApp()->ShowConsoleText(pszConsole, pszText, bTimestamp, bAudition));
}
inline BOOL ReadConsoleText(LPCTSTR pszConsole, CStringArray &szText, BOOL bTimestamp = TRUE, BOOL bAll = TRUE)
{
	return(GetEditorApp()->ReadConsoleText(pszConsole, szText, bTimestamp, bAll));
}
inline INT AlertConsoleText(LPCTSTR pszConsole, LPCTSTR pszText, COLORREF nColor, BOOL bTimestamp = TRUE)
{
	return(GetEditorApp()->AlertConsoleText(pszConsole, pszText, nColor, bTimestamp));
}
inline BOOL AcknowledgeConsoleText(LPCTSTR pszConsole, INT nLine)
{
	return(GetEditorApp()->AcknowledgeConsoleText(pszConsole, nLine));
}
inline BOOL ResetConsoleContent(LPCTSTR pszConsole)
{
	return(GetEditorApp()->ResetConsoleContent(pszConsole));
}
inline BOOL ResetAllConsoles()
{
	return(GetEditorApp()->ResetAllConsoles());
}
inline VOID SetFindDefaults(BOOL bForward, BOOL bSearchAll, BOOL bMatchCase, BOOL bMatchWord, BOOL bToggle = FALSE)
{
	return(GetEditorApp()->SetFindDefaults(bForward, bSearchAll, bMatchCase, bMatchWord, bToggle));
}
inline VOID GetFindDefaults(BOOL &bForward, BOOL &bSearchAll, BOOL &bMatchCase, BOOL &bMatchWord)
{
	return(GetEditorApp()->GetFindDefaults(bForward, bSearchAll, bMatchCase, bMatchWord));
}
inline VOID SaveProfiles()
{
	return(GetEditorApp()->SaveProfiles());
}
inline VOID LoadProfiles()
{
	return(GetEditorApp()->LoadProfiles());
}
inline BOOL SetCompileBatchProfiles(CONST CCompileBatches &pBatches)
{
	return(GetEditorApp()->SetCompileBatchProfiles(pBatches));
}
inline BOOL GetCompileBatchProfiles(CCompileBatches &pBatches)
{
	return(GetEditorApp()->GetCompileBatchProfiles(pBatches));
}
inline BOOL SetPrintProfile(CONST CPrintProfileInfo &cProfileInfo)
{
	return(GetEditorApp()->SetPrintProfile(cProfileInfo));
}
inline BOOL GetPrintProfile(CPrintProfileInfo &cProfileInfo)
{
	return(GetEditorApp()->GetPrintProfile(cProfileInfo));
}
inline BOOL InitializeDefaultPrinter()
{
	return(GetEditorApp()->InitializeDefaultPrinter());
}
inline BOOL IsDefaultPrinterAvailable()
{
	return(GetEditorApp()->IsDefaultPrinterAvailable());
}
inline BOOL SetDefaultPrinterInfo(CONST PAGESETUPDLG *pPrinterInfo)
{
	return(GetEditorApp()->SetDefaultPrinterInfo(pPrinterInfo));
}
inline BOOL GetDefaultPrinterInfo(PAGESETUPDLG *pPrinterInfo)
{
	return(GetEditorApp()->GetDefaultPrinterInfo(pPrinterInfo));
}
inline BOOL CreatePrinterDC(CONST CPrintProfileInfo *pProfileInfo, CDC &cDC)
{
	return(GetEditorApp()->CreatePrinterDC(pProfileInfo, cDC));
}
inline BOOL CreatePrinterDC(HANDLE hDevNames, HANDLE hDevMode, CDC &cDC)
{
	return(GetEditorApp()->CreatePrinterDC(hDevNames, hDevMode, cDC));
}
inline BOOL IsCompiling()
{
	return(GetEditorApp()->IsCompiling());
}
inline BOOL IsTesting()
{
	return(GetEditorApp()->IsTesting());
}
inline BOOL IsPrinting()
{
	return(GetEditorApp()->IsPrinting());
}
inline BOOL CheckDatabasePrivilege(UINT nPrivilege)
{
	return(GetEditorApp()->CheckDatabasePrivilege(nPrivilege));
}
inline BOOL ShowHelp(LPCTSTR pszTopic = NULL)
{
	return(GetEditorApp()->ShowHelp(pszTopic));
}
inline BOOL IsHelpAvailable()
{
	return(GetEditorApp()->IsHelpAvailable());
}
inline CNetworkBrowseService *GetNetworkBrowseService()
{
	return(GetEditorApp()->GetNetworkBrowseService());
}
inline CDisplayFrame *GetDisplayFrame()
{
	return(GetEditorApp()->GetDisplayFrame());
}
inline CMainWnd *GetMainWnd()
{
	return(GetEditorApp()->GetMainWnd());
}

/////////////////////////////////////////////////////////////////////////////


#endif // __EDITOR_H__
