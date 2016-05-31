// DISPLAYS.H : Displays Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the displays related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __DISPLAYS_H__
#define __DISPLAYS_H__


/////////////////////////////////////////////////////////////////////////////
// CDisplayLockable

class CDisplayLockable
{
	// Construction
public:
	CDisplayLockable();
	~CDisplayLockable();

	// Attributes
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	CCriticalSection *GetLock() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayLockable)
public:
	virtual BOOL Lock();
	virtual BOOL Unlock();
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CDisplayWnd

class CDisplayWnd : public CLocaleMDIChildWnd, public CDisplayLockable
{
	DECLARE_DYNCREATE(CDisplayWnd)

	// Construction
public:
	CDisplayWnd();

	// Attributes
protected:
	UINT  m_nState;

	// Operations
public:
	class CMainWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayWnd)
public:
	virtual BOOL Start();
	virtual BOOL CanStart() CONST;
	virtual BOOL Suspend();
	virtual BOOL CanSuspend() CONST;
	virtual BOOL IsSuspended() CONST;
	virtual BOOL Stop();
	virtual BOOL CanStop() CONST;
	virtual BOOL Reload();
	virtual BOOL CanReload() CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CDisplayWnd)
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnUpdateContentSave(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleThread

class CSimulatorDataConsoleThread : public CThread
{
	DECLARE_DYNCREATE(CSimulatorDataConsoleThread)

	// Construction
public:

	// Attributes
public:

	// Operations
public:
	BOOL Start(class CSimulatorDataConsoleWnd *pDataConsoleWnd);
	BOOL Stop();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimulatorDataConsoleThread)
public:
	virtual int Run();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSimulatorDataConsoleThread)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleDocument

class CSimulatorDataConsoleDocument : public CDocument
{
	DECLARE_DYNCREATE(CSimulatorDataConsoleDocument)

	// Construction
public:
	CSimulatorDataConsoleDocument();

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimulatorDataConsoleDocument)
protected:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSimulatorDataConsoleDocument)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleView

// Specify the simulator data console view related timer identifiers
#define SIMULATORDATACONSOLEVIEW_DEVICEDATA_TIMERID   100
#define SIMULATORDATACONSOLEVIEW_DEVICEDATA_TIMEOUT   0

class CSimulatorDataConsoleView : public CRichEditView
{
	DECLARE_DYNCREATE(CSimulatorDataConsoleView)

	// Construction
public:
	CSimulatorDataConsoleView();
	~CSimulatorDataConsoleView();

	// Attributes
private:
	CString  m_szData;
	CString  m_szDataSource;
	UINT  m_nDataType;
	UINT  m_nDataFormat;
	UINT  m_nDataOBRTPerSecond;
	BOOL  m_bData;
private:
	CTMUnits  m_pTMUnits;
	CTMTransferUnits  m_pTMTransferUnits;
private:
	CRect  m_rUpdate;
	CFont  m_cFont;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	VOID SetData(LPCTSTR pszData);
	VOID SetData(CONST CTMUnits &pTMUnits);
	VOID SetData(CONST CTMTransferUnits &pTMTransferUnits);
	CString GetData() CONST;
	INT GetData(CTMUnits &pTMUnits) CONST;
	INT GetData(CTMTransferUnits &pTMTransferUnits) CONST;
	CString TranslateData(LPCTSTR pszData, CTMUnits &pTMUnits) CONST;
	CString TranslateData(LPCTSTR pszData, CTMTransferUnits &pTMTransferUnits) CONST;
	CString UpdateData();

	CString GetDataSource() CONST;
	UINT GetDataType() CONST;
	UINT GetDataFormat() CONST;
	UINT GetDataOBRTPerSecond() CONST;

	BOOL CanSave() CONST;

	CSimulatorDataConsoleDocument *GetDocument() const;

	class CSimulatorDataConsoleWnd *GetParent() CONST;

private:
	VOID FormatLines();
	VOID FormatLine(INT nLine);

	BOOL ReadDataLine(LPCTSTR pszData, INT &nPos, CString &szDataLine, BOOL &bFinalLine) CONST;
	BOOL CollectLineData(LPCTSTR pszDataLine, INT &nOffset, INT &nSkipBytes, CByteArray &nLineData, UINT &nOBRT, BOOL &bOBRT) CONST;
	UINT ReadDataOffset(LPCTSTR pszDataLine, INT nLength) CONST;
	VOID SkipSpaces(LPCTSTR pszDataLine, INT &nPos) CONST;

	BOOL ReadDataKeyword(LPCTSTR pszData, INT nPos, CString &szValue) CONST;
	BOOL ReadDataKeyword(LPCTSTR pszData, INT nPos, UINT &nValue) CONST;

	BOOL DrawPrintDocPage(CDC *pDC, CPrintInfo *pPrintInfo);
	BOOL DrawPrintDocTitle(CDC *pDC, LPRECT prClip, LPCTSTR pszTitle, CFont &cFont);
	BOOL DrawPrintDocInfoTitle(CDC *pDC, LPRECT prClip, LPCTSTR pszTitle, CFont &cFont);
	BOOL DrawPrintDocNotice(CDC *pDC, LPRECT prClip, LPCTSTR pszNotice, CFont &cFont, CFont &cLogoFont);
	BOOL DrawPrintDocFooter(CDC *pDC, LPRECT prClip, LPCTSTR pszFooter, CFont &cFont);
	BOOL CalcPrintDocTitleFont(CDC *pDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocInfoTitleFont(CDC *pDC, CONST RECT &rArea, CFont &cFont) CONST;
	BOOL CalcPrintDocNoticeFont(CDC *pDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST;
	BOOL CalcPrintDocFooterFont(CDC *pDC, CONST RECT &rArea, CFont &cFont) CONST;
	CString GetPrintDocTitle() CONST;
	CString GetPrintDocInfoTitle() CONST;
	CString GetPrintDocNotice() CONST;
	CString GetPrintDocFooter(CONST CPrintInfo *pPrintInfo) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimulatorDataConsoleView)
protected:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC *pDC);
	virtual void OnPrint(CDC *pDC, CPrintInfo *pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo *pInfo);
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSimulatorDataConsoleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEditchangeData();
	afx_msg void OnTimer(UINT_PTR nTimerID);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimulatorDataConsoleWnd

// Specify the data console state identifiers
#define DATACONSOLE_STATE_NONE   0
#define DATACONSOLE_STATE_READY   (1<<0)
#define DATACONSOLE_STATE_RUNNING   (1<<2)
#define DATACONSOLE_STATE_SUSPENDED   (1<<3)
#define DATACONSOLE_STATE_STOPPED   (1<<4)
// Specify the data console status bar pane identifiers
#define ID_DATACONSOLE_PANE_SATELLITE   1
#define ID_DATACONSOLE_PANE_IODEVICE   2
#define ID_DATACONSOLE_PANE_IODEVICESTATE   3

class CSimulatorDataConsoleWnd : public CDisplayWnd
{
	DECLARE_DYNCREATE(CSimulatorDataConsoleWnd)

	// Construction
public:
	CSimulatorDataConsoleWnd();

	// Attributes
private:
	CIODevice  m_cIODevice;
	CStringArray  m_szIODeviceLogins;
	CStringArray  m_szIODeviceClients;
	CTimeTagArray  m_tIODeviceClients;
	CSimulatorDataConsoleThread  m_cDataDeliveryThread;
private:
	CStatusBar  m_wndStatusBar;

	// Operations
public:
	BOOL StartDataDistribution();
	BOOL DistributeData(CONST CTMUnit *pTMUnit);
	BOOL DistributeData(CONST CTMTransferUnit *pTMTransferUnit);
	BOOL StopDataDistribution();

	INT GetData(CTMUnits &pTMUnits) CONST;
	INT GetData(CTMTransferUnits &pTMTransferUnits) CONST;

	INT GetClients(CStringArray &szClients) CONST;
	INT GetClients(CStringArray &szClients, CTimeTagArray &tClients) CONST;

	VOID UpdateAllPanes(CDocument *pDocument = NULL, INT cbDocument = 0);
	VOID UpdatePane(UINT nPaneID, LPCTSTR pszText);

	CSimulatorDataConsoleView *GetView() CONST;

public:
	static VOID CALLBACK TrackIODeviceLogins(UINT nFlags, LPCTSTR pszClient, TIMETAG tConnectTime, LPVOID pData);

private:
	CString TranslateDeviceState() CONST;
	CString TranslateDeviceState(UINT nState) CONST;

	CString TranslateToClientName(LPCTSTR pszFullName) CONST;
	CString TranslateToClientAddress(LPCTSTR pszFullName) CONST;

	CSize CalcPaneExtent(LPCTSTR pszText);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimulatorDataConsoleWnd)
public:
	virtual BOOL Start();
	virtual BOOL CanStart() CONST;
	virtual BOOL Suspend();
	virtual BOOL CanSuspend() CONST;
	virtual BOOL IsSuspended() CONST;
	virtual BOOL Stop();
	virtual BOOL CanStop() CONST;
	virtual BOOL Reload();
	virtual BOOL CanReload() CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSimulatorDataConsoleWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateContentSave(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimulatorMessagesConsoleDocument

class CSimulatorMessagesConsoleDocument : public CDocument
{
	DECLARE_DYNCREATE(CSimulatorMessagesConsoleDocument)

	// Construction
public:
	CSimulatorMessagesConsoleDocument();
	~CSimulatorMessagesConsoleDocument();

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimulatorMessagesConsoleView

class CSimulatorMessagesConsoleView : public CListView
{
	DECLARE_DYNCREATE(CSimulatorMessagesConsoleView)

	// Construction
public:
	CSimulatorMessagesConsoleView();

	// Attributes
public:

	// Operations
public:
	VOID ShowMessage(LPCTSTR pszMessage);
	VOID ShowMessage(LPCTSTR pszType, LPCTSTR pszMessage);
	VOID ShowMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage);

	INT GetMessageCount() CONST;

private:
	INT FindColumnIndex(LPCTSTR pszColumn) CONST;

	CSize CalcColumnExtent(LPCTSTR pszColumn);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimulatorMessagesConsoleView)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CSimulatorMessagesConsoleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimulatorMessagesConsoleWnd

class CSimulatorMessagesConsoleWnd : public CDisplayWnd
{
	DECLARE_DYNCREATE(CSimulatorMessagesConsoleWnd)

	// Construction
public:
	CSimulatorMessagesConsoleWnd();

	// Attributes
private:
	CSimulatorMessagesConsoleView  *m_pwndView;
	CStatusBar  m_wndStatusBar;

	// Operations
public:
	VOID ShowMessage(LPCTSTR pszMessage);
	VOID ShowMessage(LPCTSTR pszType, LPCTSTR pszMessage);
	VOID ShowMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage);

	INT GetMessageCount() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimulatorMessagesConsoleWnd)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT &cs);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CSimulatorMessagesConsoleWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


#endif // __DISPLAYS_H__
