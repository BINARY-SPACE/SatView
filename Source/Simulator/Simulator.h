// SIMULATOR.H : SatView Simulator Application.
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
* 2010/12/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SIMULATOR_H__
#define __SIMULATOR_H__

#ifndef RC_INVOKED
#include <afxwin.h>
#include <afxwinappex.h>
#include <afxdialogex.h>
#include <afxcontrolbars.h>
#include <afxcview.h>
#include <afxrich.h>
#include <afxsock.h>
#include <afxdb.h>
#include <afxmt.h>

#include <atlsecurity.h>

#include <evntprov.h>

#include <mmsystem.h>

#include <tom.h>


#include "macros.h"
#include "devices.h"
#include "strings.h"
#include "version.h"
#include "accounts.h"
#endif

#include "resource.h"       // main symbols
#include "Simulator.rh"

#include "dialogs.h"
#include "profile.h"
#include "displays.h"


/////////////////////////////////////////////////////////////////////////////
// CIODeviceToolBarComboBoxButton

class CIODeviceToolBarComboBoxButton : public CMFCToolBarComboBoxButton
{
	DECLARE_SERIAL(CIODeviceToolBarComboBoxButton)

public:
	CIODeviceToolBarComboBoxButton();
	CIODeviceToolBarComboBoxButton(UINT uiID, int iImage, DWORD dwStyle = CBS_DROPDOWNLIST, int iWidth = 0);

	// Attributes
public:

	// Operations
private:
	CString ConvertText(LPCTSTR pszText) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIODeviceToolBarComboBoxButton)
protected:
	virtual void OnDraw(CDC *pDC, const CRect &rect, CMFCToolBarImages *pImages, BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE);
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CIODevicesToolBar window

class CIODevicesToolBar : public CMFCToolBar
{
	DECLARE_DYNAMIC(CIODevicesToolBar)

public:
	CIODevicesToolBar();
	~CIODevicesToolBar();

	// Attributes
private:
	CUIntArray  m_nLabelIDs;
	CPtrArray  m_pwndLabels;

	// Operations
public:
	INT EnumIODevices(CStringArray &szDevices) CONST;

	BOOL SetIODevice(LPCTSTR pszDevice, BOOL bAdd = FALSE);
	CString GetIODevice() CONST;

	INT FindIODevice(LPCTSTR pszDevice) CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIODevicesToolBar)
public:
	virtual BOOL Customize();
	virtual CSize CalcSize(BOOL bVertDock);
	//}}AFX_VIRTUAL

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CMainWnd frame

class CMainWnd : public CLocaleMDIFrameWnd
{
	DECLARE_DYNCREATE(CMainWnd)

public:
	CMainWnd();
	~CMainWnd();

	// Attributes
private:
	CIODevices  m_pIODevices;
	CStringArray  m_szIODevices;
	CStringArray  m_szIODeviceMessages;
	UINT_PTR  m_nIODeviceTimerID;
private:
	CMFCMenuBar  m_wndMenuBar;
	CMFCToolBar  m_wndToolBar;
	CIODevicesToolBar  m_wndIODevicesToolBar;
	CSimulatorMessagesConsoleWnd  *m_pwndMessages;
	CMFCStatusBar  m_wndStatusBar;
private:
	UINT  m_nExitID;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	VOID Initialize(LPCTSTR pszSpacecraft, LPCTSTR pszDevice);

	VOID UpdateTitle(LPCTSTR pszDocument);

	BOOL SetIODevice(CONST CIODevice *pDevice);
	BOOL SetIODevice(LPCTSTR pszDevice);
	BOOL GetIODevice(CIODevice *pDevice) CONST;
	CString GetIODevice() CONST;

	INT EnumIODevices(CStringArray &szDevices) CONST;

	VOID ShowMessage(LPCTSTR pszMessage);
	VOID ShowMessage(LPCTSTR pszType, LPCTSTR pszMessage);
	VOID ShowMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage);

public:
	static VOID CALLBACK ShowIODeviceStatus(LPCTSTR pszStatus, UINT nStatus);
	static VOID CALLBACK ShowIODeviceMessage(LPCTSTR pszMessage, UINT nMessageType = IODEVICE_MESSAGETYPE_ERROR);

private:
	VOID EnumIODevices();
	VOID EnumIODevices(LPCTSTR pszDirectory);
	VOID EnumIODevices(LPCTSTR pszDirectory, LPCTSTR pszFileName);

	BOOL AddMessageToBuffer(LPCTSTR pszMessage);
	BOOL AddMessageToBuffer(LPCTSTR pszType, LPCTSTR pszMessage);
	BOOL AddMessageToBuffer(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage);
	BOOL RemoveMessageFromBuffer(CString &szMessage);
	BOOL RemoveMessageFromBuffer(CString &szType, CString &szMessage);
	BOOL RemoveMessageFromBuffer(CString &szType, CString &szSource, CString &szMessage);

	CString EncodeMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage) CONST;
	BOOL DecodeMessage(LPCTSTR pszItem, CString &szType, CString &szSource, CString &szMessage) CONST;

	CString FindSatelliteData(LPCTSTR pszSatellite) CONST;
	CString FindSatelliteData(LPCTSTR pszDirectory, LPCTSTR pszSatellite) CONST;

	static CString TranslateMessageType(UINT nMessageType);

	UINT GetSubMenuState(CMenu *pMenu) CONST;

	BOOL IsSameThread() CONST;

private:
	static BOOL CALLBACK EnumDisplayWindows(HWND hWnd, LPARAM lParam);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainWnd)
public:
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd *pParentWnd = NULL, CCreateContext *pContext = NULL);
	virtual HMENU GetWindowMenuPopup(HMENU hMenuBar);
	virtual void GetMessageString(UINT nID, CString &rMessage) const;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnToolbarReset(WPARAM wParam, LPARAM lParam);
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnDeviceConfiguration();
	afx_msg void OnDeviceReload();
	afx_msg void OnDeviceStart();
	afx_msg void OnDeviceSuspend();
	afx_msg void OnDeviceStop();
	afx_msg void OnViewToolbars();
	afx_msg void OnHelp();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nTimerID);
	afx_msg void OnUpdateDeviceLabel(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDevice(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeviceConfiguration(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeviceReload(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeviceStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeviceSuspend(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeviceStop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIODevices(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewToolbars(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNewWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCascadeWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTileWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateArrangeWindow(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHelp(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimulatorAppCommandLineInfo

class CSimulatorAppCommandLineInfo : public CCommandLineInfo
{
	// Constructors
public:
	CSimulatorAppCommandLineInfo();

	// Attributes
private:
	CString  m_szSpacecraft;
	CString  m_szDevice;
	BOOL  m_bSpacecraft;
	BOOL  m_bDevice;

	// Operations
public:
	CString GetSpacecraft() CONST;
	CString GetDevice() CONST;

	BOOL IsValid() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimulatorAppCommandLineInfo)
	virtual void ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast);
	//}}AFX_VIRTUAL
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSimulatorApp application

class CSimulatorApp : public CAccountsApp
{
	DECLARE_DYNAMIC(CSimulatorApp)

	// Construction
public:
	CSimulatorApp();

	// Attributes
public:

	//Operations
public:
	BOOL SetIODevice(LPCTSTR pszDevice);
	CString GetIODevice() CONST;

	INT EnumIODevices(CStringArray &szDevices) CONST;

	VOID ShowMessage(LPCTSTR pszMessage);
	VOID ShowMessage(LPCTSTR pszType, LPCTSTR pszMessage);
	VOID ShowMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage);

	BOOL ShowHelp(LPCTSTR pszTopic = NULL);
	BOOL IsHelpAvailable() CONST;

	CMainWnd *GetMainWnd() CONST;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimulatorApp)
public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSimulatorApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileNew(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline CSimulatorApp *GetSimulatorApp()
{
	return((CSimulatorApp *)AfxGetApp());
}
inline BOOL SetIODevice(LPCTSTR pszDevice)
{
	return(GetSimulatorApp()->SetIODevice(pszDevice));
}
inline CString GetIODevice()
{
	return(GetSimulatorApp()->GetIODevice());
}
inline INT EnumIODevices(CStringArray &szDevices)
{
	return(GetSimulatorApp()->EnumIODevices(szDevices));
}
inline VOID ShowMessage(LPCTSTR pszMessage)
{
	GetSimulatorApp()->ShowMessage(pszMessage);
}
inline VOID ShowMessage(LPCTSTR pszType, LPCTSTR pszMessage)
{
	GetSimulatorApp()->ShowMessage(pszType, pszMessage);
}
inline VOID ShowMessage(LPCTSTR pszType, LPCTSTR pszSource, LPCTSTR pszMessage)
{
	GetSimulatorApp()->ShowMessage(pszType, pszSource, pszMessage);
}
inline BOOL ShowHelp(LPCTSTR pszTopic = NULL)
{
	return(GetSimulatorApp()->ShowHelp(pszTopic));
}
inline BOOL IsHelpAvailable()
{
	return(GetSimulatorApp()->IsHelpAvailable());
}
inline CMainWnd *GetMainWnd()
{
	return(GetSimulatorApp()->GetMainWnd());
}

/////////////////////////////////////////////////////////////////////////////


#endif // __SIMULATOR_H__
