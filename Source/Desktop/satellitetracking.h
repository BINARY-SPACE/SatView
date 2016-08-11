// SATELLITETRACKING.H : Satellite Tracking Tool Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the satellite tracking tool related
// interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2013/08/26 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SATELLITETRACKING_H__
#define __SATELLITETRACKING_H__

#ifdef SATELLITETRACKING
#include "Space.h"

#ifndef min
#define min(a,b)   (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a,b)   (((a) > (b)) ? (a) : (b))
#endif


/////////////////////////////////////////////////////////////////////////////
// CSpaceSceneViewMessageBar window

// Specify the space scene view message bar outline
#define SPACESCENEVIEWMESSAGEBAR_COLOR_BORDER   RGB(200,210,220)
#define SPACESCENEVIEWMESSAGEBAR_COLOR_BACKGROUND   RGB(229,238,251)
// Specify an additional space scene view message bar type
#define MB_NEWS   (max(MB_ICONINFORMATION,max(MB_ICONWARNING,max(MB_ICONERROR,MB_ICONQUESTION)))+1)

class CSpaceSceneViewMessageBar : public CMFCCaptionBar
{
	DECLARE_DYNCREATE(CSpaceSceneViewMessageBar)

	// Construction
public:
	CSpaceSceneViewMessageBar();

	// Attributes
private:
	CByteArray  m_bTextParts[2];
	CSize  m_sizeSymbol;
	BOOL  m_bContent;

	// Operations
public:
	BOOL Create(CFrameWnd *pParentWnd);

	VOID SetBorderColor(COLORREF nColor);
	COLORREF GetBorderColor() CONST;
	VOID SetBackgroundColor(COLORREF nColor);
	COLORREF GetBackgroundColor() CONST;
	VOID SetIconSize();
	VOID SetIconSize(CONST SIZE &size);
	CSize GetIconSize() CONST;

	VOID ShowMessage(LPCTSTR pszMessage = NULL, UINT nType = MB_ICONINFORMATION, BarElementAlignment nAlignment = ALIGN_CENTER, BOOL bSound = TRUE);
	BOOL HasContent() CONST;

	VOID UpdateBar();
	VOID UpdateBar(BOOL bShow);

	class CSatelliteTrackingToolWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpaceSceneViewMessageBar)
protected:
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual CSize GetTextSize(CDC *pDC, const CString &strText);
	virtual void OnDrawBorder(CDC* pDC, CRect rect);
	virtual void OnDrawBackground(CDC* pDC, CRect rect);
	virtual void OnDrawText(CDC *pDC, CRect rect, const CString &strText);
	virtual void RecalcLayout();
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
	//{{AFX_MSG(CSpaceSceneViewMessageBar)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpaceSceneView window

class CSpaceSceneView : public CSpaceView
{
	DECLARE_DYNCREATE(CSpaceSceneView)

	// Construction
public:
	CSpaceSceneView();

	// Attributes
public:

	// Operations
public:
	class CSatelliteTrackingToolWnd *GetParent() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpaceSceneView)
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSpaceSceneView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSatelliteTrackingToolWnd frame

// Specify the satellite tracking tool related identifiers
#define SATELLITETRACKINGTOOL_MIN_WIDTH   480
#define SATELLITETRACKINGTOOL_MIN_HEIGHT  360

class CSatelliteTrackingToolWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CSatelliteTrackingToolWnd)

	// Construction
public:
	CSatelliteTrackingToolWnd();
	~CSatelliteTrackingToolWnd();

	// Attributes
private:
	CSpaceSceneView  *m_pwndSceneView;
	CSpaceSceneViewMessageBar  m_wndMessageBar;
private:
	CString  m_szConfigurationFileName;
	CString  m_szHelpFileName;
	BOOL  m_bInitialized;
	BOOL  m_bRunning;
	BOOL  m_bEnabled;

	// Operations
public:
	VOID SetConfigurationFileName(LPCTSTR pszFileName);
	CString GetConfigurationFileName() CONST;
	VOID SetHelpFileName(LPCTSTR pszFileName);
	CString GetHelpFileName() CONST;

	BOOL CalculateSpacecraftPasses(CSpacecraftPasses &pPasses) CONST;
	BOOL CalculateSpacecraftInterlinks(CSpacecraftInterlinks &pInterlinks) CONST;
	BOOL CalculateSpacecraftOrbit(CSpacecraft *pSpacecraft, CONST CTimeKey &tTime) CONST;
	BOOL CalculateSpacecraftState(CONST CSpacecraft *pSpacecraft, CONST CTimeKey &tTime, StateVector &sState) CONST;

	VOID ShowSideBars(BOOL bShow = TRUE);

	BOOL ShowMessage(LPCTSTR pszMessage, UINT nType = -1, CMFCCaptionBar::BarElementAlignment nAlignment = CMFCCaptionBar::ALIGN_CENTER, BOOL bSound = TRUE);
	BOOL ShowProgress(LPCTSTR pszAction, INT nProgress = 0);

	VOID Enable(BOOL bEnable = TRUE);
	BOOL IsEnabled() CONST;

private:
	CString ConstructConfiguratonFileName() CONST;
	CString ConstructHelpFileName() CONST;

public:
	static BOOL CALLBACK ShowMessageProc(LPCTSTR pszMessage, UINT nType = -1, CMFCCaptionBar::BarElementAlignment nAlignment = CMFCCaptionBar::ALIGN_CENTER, BOOL bSound = TRUE);
	static BOOL CALLBACK ShowProgressProc(LPCTSTR pszMessage, INT nProgress = 0);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSatelliteTrackingToolWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Check() CONST;
	virtual VOID Update();
	virtual BOOL Stop();
public:
	virtual BOOL SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo);
	virtual BOOL LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo);
	virtual BOOL QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST;
	virtual BOOL QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:
	void OnMenuID(UINT nID);
	void OnUpdateMenuID(CCmdUI *pCmdUI);

	// Generated message map functions
protected:
	//{{AFX_MSG(CSatelliteTrackingToolWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO *lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnInitMenu(CMenu *pMenu);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd *pActivateWnd, CWnd *pDeactivateWnd);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#else

/////////////////////////////////////////////////////////////////////////////
// CSatelliteTrackingToolWnd frame

class CSatelliteTrackingToolWnd : public CDisplayWnd
{
	DECLARE_DYNAMIC(CSatelliteTrackingToolWnd)

	// Construction
public:
	CSatelliteTrackingToolWnd();
	~CSatelliteTrackingToolWnd();

	// Attributes
public:

	// Operations
public:
	VOID SetConfigurationFileName(LPCTSTR pszFileName);
	CString GetConfigurationFileName() CONST;
	VOID SetHelpFileName(LPCTSTR pszFileName);
	CString GetHelpFileName() CONST;

	VOID ShowSideBars(BOOL bShow = TRUE);

	VOID Enable(BOOL bEnable = TRUE);
	BOOL IsEnabled() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSatelliteTrackingToolWnd)
public:
	virtual BOOL Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault = TRUE);
public:
	virtual BOOL Start();
	virtual BOOL Prepare(BOOL bDialog);
	virtual BOOL Check() CONST;
	virtual VOID Update();
	virtual BOOL Stop();
public:
	virtual BOOL QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST;
	virtual BOOL QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST;
	//}}AFX_VIRTUAL

	// Implementation
public:

	// Generated message map functions
protected:
	//{{AFX_MSG(CSatelliteTrackingToolWnd)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif


#endif // __SATELLITETRACKING_H__
